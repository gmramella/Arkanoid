#pragma once
#include "libUnicornio.h"
#include "fftw3.h"
#include "AudioManager.h"
#include "Utils.h"
#include "Render.h"
#include "Wav.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

#define ABORT {gRecursos.descarregarTudo(); uniFinalizar(); return EXIT_FAILURE;}

int main(int argc, char* argv[])
{
	uniInicializar(800, 600, false);
	gMouse.esconderCursor();

	SpriteSheet* temp = NULL;
	temp = gRecursos.carregarSpriteSheet("player", "./Files/shuttle2.png", 1, 1); if (temp == NULL) ABORT;
	unsigned int playerSpriteWidth = gRecursos.getSpriteSheet("player")->getTextura()->getLargura();
	unsigned int playerSpriteHeight = gRecursos.getSpriteSheet("player")->getTextura()->getAltura();
	Player player("player", gJanela.getLargura() / 2, gJanela.getAltura() / 2, std::min(playerSpriteWidth, playerSpriteHeight) / 8);
	temp = gRecursos.carregarSpriteSheet("bullet", "./Files/bullet.png", 1, 1); if (temp == NULL) ABORT;
	unsigned int bulletSpriteWidth = gRecursos.getSpriteSheet("bullet")->getTextura()->getLargura();
	unsigned int bulletSpriteHeight = gRecursos.getSpriteSheet("bullet")->getTextura()->getAltura();
	std::vector<Bullet> bullets;
	temp = gRecursos.carregarSpriteSheet("enemy1", "./Files/Asteroids_32x32_001.png", 1, 1); if (temp == NULL) ABORT;
	temp = gRecursos.carregarSpriteSheet("enemy2", "./Files/Asteroids_32x32_002.png", 1, 1); if (temp == NULL) ABORT;
	temp = gRecursos.carregarSpriteSheet("enemy3", "./Files/Asteroids_32x32_003.png", 1, 1); if (temp == NULL) ABORT;
	temp = gRecursos.carregarSpriteSheet("enemy4", "./Files/Asteroids_32x32_004.png", 1, 1); if (temp == NULL) ABORT;
	temp = gRecursos.carregarSpriteSheet("enemy5", "./Files/Asteroids_32x32_005.png", 1, 1); if (temp == NULL) ABORT;
	temp = gRecursos.carregarSpriteSheet("enemy6", "./Files/Asteroids_32x32_006.png", 1, 1); if (temp == NULL) ABORT;
	temp = gRecursos.carregarSpriteSheet("enemy7", "./Files/Asteroids_32x32_007.png", 1, 1); if (temp == NULL) ABORT;
	temp = gRecursos.carregarSpriteSheet("enemy8", "./Files/Asteroids_32x32_008.png", 1, 1); if (temp == NULL) ABORT;
	unsigned int enemySpriteWidth = gRecursos.getSpriteSheet("enemy1")->getTextura()->getLargura();
	unsigned int enemySpriteHeight = gRecursos.getSpriteSheet("enemy1")->getTextura()->getAltura();
	unsigned int numEnemiesX = 10;
	unsigned int numEnemiesY = 5;
	numEnemiesX = std::min(numEnemiesX, (unsigned int)floor(gJanela.getLargura() / (float)enemySpriteWidth) - 2);
	numEnemiesY = std::min(numEnemiesY, (unsigned int)floor(gJanela.getAltura() / (float)enemySpriteHeight) - 2);
	std::vector<Enemy> enemies;
	for (unsigned int i = 0; i < numEnemiesX; i++)
	{
		for (unsigned int j = 0; j < numEnemiesY; j++)
		{
			enemies.push_back(Enemy("enemy1", gJanela.getLargura() / 2 - (numEnemiesX / 2) * enemySpriteWidth + i * enemySpriteWidth, (j + 1) * enemySpriteHeight, std::min(enemySpriteWidth, enemySpriteHeight) / 2));
		}
	}

	gRecursos.carregarFonte("font1", "./fonte_padrao.ttf", 32);
	gRecursos.carregarFonte("font2", "./fonte_padrao.ttf", 8);
	Texto score;
	score.setFonte("font1");
	score.setCor(blue);
	score.setAlinhamento(TEXTO_CENTRALIZADO);
	unsigned int points = 0;

	const char* path = "./Musics/Rock 'n' Roll Train.wav";
	std::string title(path);
	title = title.substr(title.find_last_of("/\\") + 1);
	gRecursos.carregarMusica("audio1", path);
	Wav* wav = AudioManager::loadWAV(path);

	if (wav == NULL)
	{
		gRecursos.descarregarTudo();
		uniFinalizar();
		return EXIT_FAILURE;
	}
	wav->printHeader();
	/*wav->writeHeader();
	wav->writeSamples();*/

	sample* samplesMono = NULL;
	sample* samplesLeft = NULL;
	sample* samplesRight = NULL;
	double* amplitudesMono = NULL;
	double* amplitudesLeft = NULL;
	double* amplitudesRight = NULL;
	double* phasesMono = NULL;
	double* phasesLeft = NULL;
	double* phasesRight = NULL;
	double highestAmplitudeMono = 0;
	double highestAmplitudeLeft = 0;
	double highestAmplitudeRight = 0;
	unsigned int chunkMono = (int)pow(2, 14);
	unsigned int chunkStereo = chunkMono / 2;
	sample* windowMono = new sample[chunkMono];
	sample* windowLeft = new sample[chunkStereo];
	sample* windowRight = new sample[chunkStereo];
	unsigned int numBinsMono = chunkMono / 2;
	float binWidthMono = 1.0 * wav->SampleRate / 2 / numBinsMono;
	unsigned int numBinsStereo = chunkStereo / 2;
	float binWidthStereo = 1.0 * wav->SampleRate / 2 / numBinsStereo;
	unsigned int frameSize;

	if (wav->NumChannels == 1)
	{
		cout << "NumBins " << numBinsMono << endl;
		cout << "BinWidth " << binWidthMono << endl;
		samplesMono = new sample[wav->NumSamples];
		amplitudesMono = new double[chunkMono / 2];
		phasesMono = new double[chunkMono / 2];

		for (int i = 0; i < wav->NumSamples; i++)
		{
			samplesMono[i] = wav->IntData[i];
		}
	}
	else
	{
		cout << "NumBins " << numBinsStereo << endl;
		cout << "BinWidth " << binWidthStereo << endl;
		samplesLeft = new sample[wav->NumSamples];
		samplesRight = new sample[wav->NumSamples];
		amplitudesLeft = new double[chunkStereo / 2];
		amplitudesRight = new double[chunkStereo / 2];
		phasesLeft = new double[chunkStereo / 2];
		phasesRight = new double[chunkStereo / 2];

		for (int i = 0; i < 2 * wav->NumSamples; i++)
		{
			if (i % 2 == 0)
			{
				samplesLeft[i / 2] = wav->IntData[i];
			}
			else
			{
				samplesRight[i / 2] = wav->IntData[i];
			}
		}
	}

	//beat-------------------------------------------------------------------------------------------------
	double variance = 0.0;
	float C = 1.3;
	unsigned int numSubBands;
	unsigned int widthSubBands;
	unsigned int sizeOfHistory;
	unsigned int samplesPerSecond;
	unsigned int numHigher = 0.0;
	bool wasBeat = false;
	double highestBeat = 0.0;

	if (wav->NumChannels == 1)
	{
		numSubBands = chunkMono / 2;
		widthSubBands = chunkMono / 2 / numSubBands;
		sizeOfHistory = (int)floor(wav->SampleRate / chunkMono);
		samplesPerSecond = sizeOfHistory * chunkMono;
	}
	else
	{
		numSubBands = chunkStereo / 2;
		widthSubBands = chunkStereo / 2 / numSubBands;
		sizeOfHistory = (int)floor(wav->SampleRate / chunkStereo);
		samplesPerSecond = sizeOfHistory * chunkStereo;
	}

	double** history = new double*[numSubBands];
	for (unsigned int i = 0; i < numSubBands; i++)
		history[i] = new double[sizeOfHistory];
	double* ratios = new double[numSubBands];
	double* average = new double[numSubBands];

	if (wav->NumChannels == 1)
	{
		for (unsigned int j = 0; j < sizeOfHistory; j++)
		{
			Utils::hamming(windowMono, samplesMono, j * chunkMono, chunkMono);
			Utils::fft(amplitudesMono, phasesMono, windowMono, chunkMono);
			for (unsigned int i = 0; i < numSubBands; i++)
			{
				history[i][j] = Utils::energy(amplitudesMono, i * widthSubBands, widthSubBands);
			}
		}

		for (unsigned int i = 0; i < numSubBands; i++)
		{
			average[i] = 0;
			for (unsigned int j = 0; j < sizeOfHistory; j++)
			{
				average[i] += history[i][j];
			}
			average[i] *= 1 / (float)sizeOfHistory;
		}
	}
	else
	{
		for (unsigned int j = 0; j < sizeOfHistory; j++)
		{
			Utils::hamming(windowLeft, samplesLeft, j * chunkStereo, chunkStereo);
			Utils::hamming(windowRight, samplesRight, j * chunkStereo, chunkStereo);
			Utils::fft(amplitudesLeft, phasesLeft, windowLeft, chunkStereo);
			Utils::fft(amplitudesRight, phasesRight, windowRight, chunkStereo);
			for (unsigned int i = 0; i < numSubBands; i++)
			{
				history[i][j] = Utils::energy(amplitudesLeft, amplitudesRight, i * widthSubBands, widthSubBands);
			}
		}

		for (unsigned int i = 0; i < numSubBands; i++)
		{
			average[i] = 0;
			for (unsigned int j = 0; j < sizeOfHistory; j++)
			{
				average[i] += history[i][j];
			}
			average[i] *= 1 / (float)sizeOfHistory;
		}
	}
	//-----------------------------------------------------------------------------------------------------
	float max = (float)pow(2, wav->BitsPerSample - 1);
	Timer timer;
	timer.start();
	gMusica.tocar("audio1", false);
	unsigned int frames = 0;

	while (!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();
		long double seconds = timer.update() / 1e9;

		unsigned int frameFirst = (int)round(wav->SampleRate * seconds);
		if (frameFirst <= wav->NumSamples)
		{
			if (wav->NumChannels == 1)
			{
				if (frameFirst <= wav->NumSamples - chunkMono)
				{
					frameSize = chunkMono;
				}
				else
				{
					frameSize = wav->NumSamples - frameFirst;
				}
				Utils::hamming(windowMono, samplesMono, frameFirst, frameSize);
				Utils::fft(amplitudesMono, phasesMono, windowMono, frameSize);

				highestAmplitudeMono = amplitudesMono[2];
				for (unsigned int i = 3; i < frameSize / 2; i++) {
					if (highestAmplitudeMono < amplitudesMono[i]) {
						highestAmplitudeMono = amplitudesMono[i];
					}
				}
				if (highestAmplitudeMono == 0) highestAmplitudeMono = 1;

				//beat-------------------------------------------------------------------------------------------------
				for (unsigned int i = 0; i < numSubBands; i++)
				{
					Utils::shiftAdd(history[i], sizeOfHistory, Utils::energy(amplitudesMono, i * widthSubBands, widthSubBands));

					average[i] = 0.0;
					for (unsigned int j = 0; j < sizeOfHistory; j++)
					{
						average[i] += history[i][j];
					}
					average[i] *= 1 / (float)sizeOfHistory;
				}

				variance = 0.0;
				for (unsigned int i = 0; i < numSubBands; i++)
				{
					for (unsigned int j = 0; j < sizeOfHistory; j++)
						variance += pow(history[i][j] - average[i], 2);
					variance *= 1 / (float)sizeOfHistory;
				}
				C = 1.4142857 - 0.0000015 * variance;

				for (unsigned int i = 0; i < numSubBands; i++)
				{
					if (history[i][0] > C * average[i])
						ratios[i] = history[i][0] / average[i];
					else
						ratios[i] = 0;
				}

				numHigher = 0;
				for (unsigned int i = 0; i < numSubBands; i++)
				{
					numHigher += (int)(ratios[i] != 0);
				}

				wasBeat = ((float)numHigher >= 0.5 * numSubBands);

				if (wasBeat)
				{
					cout << to_string(numHigher / (float)numSubBands) << endl;
				}

				highestBeat = ratios[0];
				for (unsigned int i = 1; i < numSubBands; i++)
				{
					if (highestBeat < ratios[i]) {
						highestBeat = ratios[i];
					}
				}
				if (highestBeat == 0) highestBeat = 1;
				//-----------------------------------------------------------------------------------------------------
			}
			else
			{
				if (frameFirst <= wav->NumSamples - chunkStereo)
				{
					frameSize = chunkStereo;
				}
				else
				{
					frameSize = wav->NumSamples - frameFirst;
				}
				Utils::hamming(windowLeft, samplesLeft, frameFirst, frameSize);
				Utils::hamming(windowRight, samplesRight, frameFirst, frameSize);
				Utils::fft(amplitudesLeft, phasesLeft, windowLeft, frameSize);
				Utils::fft(amplitudesRight, phasesRight, windowRight, frameSize);

				highestAmplitudeLeft = amplitudesLeft[2];
				highestAmplitudeRight = amplitudesRight[2];
				for (unsigned int i = 3; i < frameSize / 2; i++) {
					if (highestAmplitudeLeft < amplitudesLeft[i]) {
						highestAmplitudeLeft = amplitudesLeft[i];
					}
					if (highestAmplitudeRight < amplitudesRight[i]) {
						highestAmplitudeRight = amplitudesRight[i];
					}
				}
				if (highestAmplitudeLeft == 0) highestAmplitudeLeft = 1;
				if (highestAmplitudeRight == 0) highestAmplitudeRight = 1;

				//beat-------------------------------------------------------------------------------------------------
				for (unsigned int i = 0; i < numSubBands; i++)
				{
					Utils::shiftAdd(history[i], sizeOfHistory, Utils::energy(amplitudesLeft, amplitudesRight, i * widthSubBands, widthSubBands));

					average[i] = 0.0;
					for (unsigned int j = 0; j < sizeOfHistory; j++)
					{
						average[i] += history[i][j];
					}
					average[i] *= 1 / (float)sizeOfHistory;
				}

				variance = 0.0;
				for (unsigned int i = 0; i < numSubBands; i++)
				{
					for (unsigned int j = 0; j < sizeOfHistory; j++)
						variance += pow(history[i][j] - average[i], 2);
					variance *= 1 / (float)sizeOfHistory;
				}
				C = 1.4142857 - 0.0000015 * variance;

				for (unsigned int i = 0; i < numSubBands; i++)
				{
					if (history[i][0] > C * average[i])
						ratios[i] = history[i][0] / average[i];
					else
						ratios[i] = 0;
				}

				numHigher = 0;
				for (unsigned int i = 0; i < numSubBands; i++)
				{
					numHigher += (int)(ratios[i] != 0);
				}

				wasBeat = ((float)numHigher >= 0.5 * numSubBands);

				if (wasBeat)
				{
					cout << to_string(numHigher / (float)numSubBands) << endl;
				}
				
				highestBeat = ratios[0];
				for (unsigned int i = 1; i < numSubBands; i++)
				{
					if (highestBeat < ratios[i]) {
						highestBeat = ratios[i];
					}
				}
				if (highestBeat == 0) highestBeat = 1;
				//-----------------------------------------------------------------------------------------------------
			}
		}

		score.setString(to_string(points));
		score.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

		if (LOOP && !gMusica.estaTocando())
		{
			//restart audio and timer
			gMusica.tocar("audio1", false);
			timer.reset();
		}

		//game-------------------------------------------------------------------------------------------------
		bool won = false;
		bool lost = false;
		if (enemies.size() == 0)
			won = true;
		Render::Animate(player, bullets, enemies, wasBeat, points);
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			if (uniTestarColisao(enemies[i].getSprite(), enemies[i].getX(), enemies[i].getY(), 0, player.getSprite(), player.getX(), player.getY(), 0))
			{
				lost = true;
				break;
			}
			if (enemies[i].getY() + enemies[i].getSprite().getAltura() >= gJanela.getAltura() - player.getSprite().getAltura())
			{
				lost = true;
				break;
			}
		}
		//-----------------------------------------------------------------------------------------------------

		//Render::RenderDebug(title, wav, highestAmplitudeMono, highestAmplitudeLeft, highestAmplitudeRight, chunkMono, chunkStereo, numBinsMono, binWidthMono, numBinsStereo, binWidthStereo, frameSize, variance, C, numSubBands, widthSubBands, sizeOfHistory, samplesPerSecond, numHigher, wasBeat, highestBeat, ++frames, timer.since() / 1e9);

		uniTerminarFrame();

		if (won || lost)
			break;
	}

	if (samplesMono != NULL) delete[] samplesMono;
	if (samplesLeft != NULL) delete[] samplesLeft;
	if (samplesRight != NULL) delete[] samplesRight;
	if (amplitudesMono != NULL) delete[] amplitudesMono;
	if (amplitudesLeft != NULL) delete[] amplitudesLeft;
	if (amplitudesRight != NULL) delete[] amplitudesRight;
	if (phasesMono != NULL) delete[] phasesMono;
	if (phasesLeft != NULL) delete[] phasesLeft;
	if (phasesRight != NULL) delete[] phasesRight;
	highestAmplitudeMono = 0;
	highestAmplitudeLeft = 0;
	highestAmplitudeRight = 0;
	chunkMono = 0;
	chunkStereo = 0;
	if (windowMono != NULL) delete[] windowMono;
	if (windowLeft != NULL) delete[] windowLeft;
	if (windowRight != NULL) delete[] windowRight;
	numBinsMono = 0;
	binWidthMono = 0;
	numBinsStereo = 0;
	binWidthStereo = 0;
	frameSize = 0;

	//beat-------------------------------------------------------------------------------------------------
	variance = 0.0;
	C = 0;
	numSubBands = 0;
	widthSubBands = 0;
	sizeOfHistory = 0;
	samplesPerSecond = 0;
	numHigher = 0.0;
	wasBeat = false;
	highestBeat = 0.0;

	if (history != NULL)
	{
		for (int i = 0; i < numSubBands; ++i)
			delete[] history[i];
		if (history != NULL) delete[] history;
	}
	if (ratios != NULL) delete[] ratios;
	if (average != NULL) delete[] average;
	//-----------------------------------------------------------------------------------------------------

	gRecursos.descarregarTudo();
	uniFinalizar();

	return 0;
}