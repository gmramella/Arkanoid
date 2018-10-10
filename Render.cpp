#include "Render.h"

void Render::RenderMono(unsigned int frameSize, unsigned int NumSamples, unsigned int frameFirst, unsigned int NumChannels, sample* samplesMono, float max, double* amplitudesMono, double highestAmplitudeMono, unsigned short scaleStep, Texto* scale, float binWidthMono)
{
	//samples
	for (unsigned int i = 0; i < frameSize; i++)
	{
		int x1 = i;
		int x2 = x1;
		int y1 = 0.83 * gJanela.getAltura();
		int y2 = y1 - (NumSamples >= (frameFirst + NumChannels * i) ? (gJanela.getAltura() / 8) * samplesMono[frameFirst + NumChannels * i] / max : 0);
		if (POINT_OR_LINE)
		{
			gGraficos.desenharLinha(x1, y1, x2, y2, samplesColor.r, samplesColor.g, samplesColor.b, samplesColor.a);
		}
		else
		{
			gGraficos.desenharPixel(x1, y1, samplesColor.r, samplesColor.g, samplesColor.b, samplesColor.a);
			gGraficos.desenharPixel(x2, y2, samplesColor.r, samplesColor.g, samplesColor.b, samplesColor.a);
		}
	}

	//amplitudes
	for (unsigned int i = 2; i < frameSize / 2; i++)
	{
		int x3 = i;
		int x4 = x3;
		int y3 = 0.98 * gJanela.getAltura();
		int y4 = y3 - (gJanela.getAltura() / 8) * amplitudesMono[i] / highestAmplitudeMono;
		if (POINT_OR_LINE)
		{
			gGraficos.desenharLinha(x3, y3, x4, y4, amplitudesColor.r, amplitudesColor.g, amplitudesColor.b, amplitudesColor.a);
		}
		else
		{
			gGraficos.desenharPixel(x3, y3, amplitudesColor.r, amplitudesColor.g, amplitudesColor.b, amplitudesColor.a);
			gGraficos.desenharPixel(x4, y4, amplitudesColor.r, amplitudesColor.g, amplitudesColor.b, amplitudesColor.a);
		}
	}

	//middle red lines
	gGraficos.desenharLinha(0, 0.83 * gJanela.getAltura(), gJanela.getLargura(), 0.83 * gJanela.getAltura(), centerColor.r, centerColor.g, centerColor.b, centerColor.a);
	gGraficos.desenharLinha(0, 0.98 * gJanela.getAltura(), gJanela.getLargura(), 0.98 * gJanela.getAltura(), centerColor.r, centerColor.g, centerColor.b, centerColor.a);

	for (unsigned int i = 0; i < gJanela.getLargura() / scaleStep; i++)
	{
		scale[i].setString(to_string(binWidthMono * scaleStep * i));
		scale[i].desenhar(scaleStep * i, 0.99 * gJanela.getAltura());
	}
}

void Render::RenderStereo(unsigned int frameSize, unsigned int NumSamples, unsigned int frameFirst, unsigned int NumChannels, sample* samplesLeft, sample* samplesRight, float max, double* amplitudesLeft, double* amplitudesRight, double highestAmplitudeLeft, double highestAmplitudeRight, unsigned short scaleStep, Texto* scale, float binWidthStereo)
{
	//samples
	for (unsigned int i = 0; i < frameSize; i++)
	{
		int x1 = i;
		int x2 = x1;
		int y1 = 0.30 * gJanela.getAltura();
		int y2 = y1 - (NumSamples >= (frameFirst + NumChannels * i) ? (gJanela.getAltura() / 8) * samplesLeft[frameFirst + NumChannels * i] / max : 0);
		if (POINT_OR_LINE)
		{
			gGraficos.desenharLinha(x1, y1, x2, y2, samplesColor.r, samplesColor.g, samplesColor.b, samplesColor.a);
		}
		else
		{
			gGraficos.desenharPixel(x1, y1, samplesColor.r, samplesColor.g, samplesColor.b, samplesColor.a);
			gGraficos.desenharPixel(x2, y2, samplesColor.r, samplesColor.g, samplesColor.b, samplesColor.a);
		}

		int x3 = i;
		int x4 = x3;
		int y3 = 0.60 * gJanela.getAltura();
		int y4 = y3 - (NumSamples >= (frameFirst + NumChannels * i) ? (gJanela.getAltura() / 8) * samplesRight[frameFirst + NumChannels * i] / max : 0);
		if (POINT_OR_LINE)
		{
			gGraficos.desenharLinha(x3, y3, x4, y4, samplesColor.r, samplesColor.g, samplesColor.b, samplesColor.a);
		}
		else
		{
			gGraficos.desenharPixel(x3, y3, samplesColor.r, samplesColor.g, samplesColor.b, samplesColor.a);
			gGraficos.desenharPixel(x4, y4, samplesColor.r, samplesColor.g, samplesColor.b, samplesColor.a);
		}
	}

	//amplitudes
	for (unsigned int i = 2; i < frameSize / 2; i++)
	{
		int x1 = i;
		int x2 = x1;
		int y1 = 0.83 * gJanela.getAltura();
		int y2 = y1 - (gJanela.getAltura() / 8) * amplitudesLeft[i] / highestAmplitudeLeft;
		if (POINT_OR_LINE)
		{
			gGraficos.desenharLinha(x1, y1, x2, y2, amplitudesColor.r, amplitudesColor.g, amplitudesColor.b, amplitudesColor.a);
		}
		else
		{
			gGraficos.desenharPixel(x1, y1, amplitudesColor.r, amplitudesColor.g, amplitudesColor.b, amplitudesColor.a);
			gGraficos.desenharPixel(x2, y2, amplitudesColor.r, amplitudesColor.g, amplitudesColor.b, amplitudesColor.a);
		}

		int x3 = i;
		int x4 = x3;
		int y3 = 0.98 * gJanela.getAltura();
		int y4 = y3 - (gJanela.getAltura() / 8) * amplitudesRight[i] / highestAmplitudeRight;
		if (POINT_OR_LINE)
		{
			gGraficos.desenharLinha(x3, y3, x4, y4, amplitudesColor.r, amplitudesColor.g, amplitudesColor.b, amplitudesColor.a);
		}
		else
		{
			gGraficos.desenharPixel(x3, y3, amplitudesColor.r, amplitudesColor.g, amplitudesColor.b, amplitudesColor.a);
			gGraficos.desenharPixel(x4, y4, amplitudesColor.r, amplitudesColor.g, amplitudesColor.b, amplitudesColor.a);
		}
	}

	//middle red lines
	gGraficos.desenharLinha(0, 0.30 * gJanela.getAltura(), gJanela.getLargura(), 0.30 * gJanela.getAltura(), centerColor.r, centerColor.g, centerColor.b, centerColor.a);
	gGraficos.desenharLinha(0, 0.60 * gJanela.getAltura(), gJanela.getLargura(), 0.60 * gJanela.getAltura(), centerColor.r, centerColor.g, centerColor.b, centerColor.a);
	gGraficos.desenharLinha(0, 0.83 * gJanela.getAltura(), gJanela.getLargura(), 0.83 * gJanela.getAltura(), centerColor.r, centerColor.g, centerColor.b, centerColor.a);
	gGraficos.desenharLinha(0, 0.98 * gJanela.getAltura(), gJanela.getLargura(), 0.98 * gJanela.getAltura(), centerColor.r, centerColor.g, centerColor.b, centerColor.a);

	for (unsigned int i = 0; i < gJanela.getLargura() / scaleStep; i++)
	{
		scale[i].setString(to_string((int)binWidthStereo * scaleStep * i));
		scale[i].desenhar(scaleStep * i, 0.99 * gJanela.getAltura());
	}
}

void Render::RenderBeatsMono(double* beats, unsigned int numSubBands, double highestBeat)
{
	for (unsigned int i = 0; i < numSubBands; i++)
	{
		int x1 = i + gJanela.getLargura() / 2;
		int x2 = x1;
		int y1 = 0.98 * gJanela.getAltura();
		int y2 = y1 - (gJanela.getAltura() / 8) * beats[i] / highestBeat;
		if (POINT_OR_LINE)
		{
			gGraficos.desenharLinha(x1, y1, x2, y2, beatsColor.r, beatsColor.g, beatsColor.b, beatsColor.a);
		}
		else
		{
			gGraficos.desenharPixel(x1, y1, beatsColor.r, beatsColor.g, beatsColor.b, beatsColor.a);
			gGraficos.desenharPixel(x2, y2, beatsColor.r, beatsColor.g, beatsColor.b, beatsColor.a);
		}
	}
}

void Render::RenderBeatsStereo(double* beats, unsigned int numSubBands, double highestBeat)
{
	for (unsigned int i = 0; i < numSubBands; i++)
	{
		int x1 = i + gJanela.getLargura() / 2;
		int x2 = x1;
		int y1 = 0.98 * gJanela.getAltura();
		int y2 = y1 - (gJanela.getAltura() / 8) * beats[i] / highestBeat;
		if (POINT_OR_LINE)
		{
			gGraficos.desenharLinha(x1, y1, x2, y2, beatsColor.r, beatsColor.g, beatsColor.b, beatsColor.a);
		}
		else
		{
			gGraficos.desenharPixel(x1, y1, beatsColor.r, beatsColor.g, beatsColor.b, beatsColor.a);
			gGraficos.desenharPixel(x2, y2, beatsColor.r, beatsColor.g, beatsColor.b, beatsColor.a);
		}

		int x3 = i + gJanela.getLargura() / 2;
		int x4 = x3;
		int y3 = 0.98 * gJanela.getAltura();
		int y4 = y3 - (gJanela.getAltura() / 8) * beats[i] / highestBeat;
		if (POINT_OR_LINE)
		{
			gGraficos.desenharLinha(x3, y3, x4, y4, beatsColor.r, beatsColor.g, beatsColor.b, beatsColor.a);
		}
		else
		{
			gGraficos.desenharPixel(x3, y3, beatsColor.r, beatsColor.g, beatsColor.b, beatsColor.a);
			gGraficos.desenharPixel(x4, y4, beatsColor.r, beatsColor.g, beatsColor.b, beatsColor.a);
		}
	}
}

void Render::RenderDebug(std::string title, Wav* wav, double highestAmplitudeMono, double highestAmplitudeLeft, double highestAmplitudeRight, unsigned int chunkMono, unsigned int chunkStereo, unsigned int numBinsMono, float binWidthMono, unsigned int numBinsStereo, float binWidthStereo, unsigned int frameSize, double variance, float C, unsigned int numSubBands, unsigned int widthSubBands, unsigned int sizeOfHistory, unsigned int samplesPerSecond, unsigned int numHigher, bool wasBeat, double highestBeat, unsigned int frames, double seconds)
{
	//WAV file parsing information
	gDebug.depurar("Title", title);
	gDebug.depurar("Chunk ID", wav->ChunkID);
	gDebug.depurar("Chunk Size", wav->ChunkSize);
	gDebug.depurar("Format", wav->Format);
	gDebug.depurar("Subchunk1 ID", wav->Subchunk1ID);
	gDebug.depurar("Subchunk1 Size", wav->Subchunk1Size);
	gDebug.depurar("Audio Format", wav->AudioFormat);
	gDebug.depurar("Num Channels", wav->NumChannels);
	gDebug.depurar("Sample Rate", wav->SampleRate);
	gDebug.depurar("Byte Rate", wav->ByteRate);
	gDebug.depurar("Block Align", wav->BlockAlign);
	gDebug.depurar("Bits Per Sample", wav->BitsPerSample);
	gDebug.depurar("Subchunk2 ID", wav->Subchunk2ID);
	gDebug.depurar("Subchunk2 Size", wav->Subchunk2Size);
	gDebug.depurar("Num Samples Per Channel", wav->NumSamples);
	gDebug.depurar(" ", "");
	//FFT information
	gDebug.depurar("Highest Amplitude Mono", highestAmplitudeMono);
	gDebug.depurar("Highest Amplitude Left", highestAmplitudeLeft);
	gDebug.depurar("Highest Amplitude Right", highestAmplitudeRight);
	gDebug.depurar("Chunk Mono", chunkMono);
	gDebug.depurar("Chunk Stereo", chunkStereo);
	gDebug.depurar("Num Bins Mono", numBinsMono);
	gDebug.depurar("Bin Width Mono", binWidthMono);
	gDebug.depurar("Num Bins Stereo", numBinsStereo);
	gDebug.depurar("Bin Width Stereo", binWidthStereo);
	gDebug.depurar("Frame Size", frameSize);
	gDebug.depurar("  ", "");
	//Beat information
	gDebug.depurar("Variance", variance);
	gDebug.depurar("C", C);
	gDebug.depurar("Num Sub-bands", numSubBands);
	gDebug.depurar("Width Sub-bands", widthSubBands);
	gDebug.depurar("Size Of History", sizeOfHistory);
	gDebug.depurar("Samples Per Second", samplesPerSecond);
	gDebug.depurar("Num Higher", numHigher);
	gDebug.depurar("Was Beat", wasBeat);
	gDebug.depurar("Highest Beat", highestBeat);
	gDebug.depurar("   ", "");
	//Rendering information
	gDebug.depurar("dt", gTempo.getDeltaTempo());
	gDebug.depurar("fps", gTempo.getFPS());
	gDebug.depurar("frames", frames);
	gDebug.depurar("seconds", seconds);
	gDebug.depurar("avg fps", ((double)(frames / seconds)));
}

void Render::Animate(Player& player, std::vector<Bullet>& bullets, std::vector<Enemy>& enemies, bool wasBeat, unsigned int& points)
{
	gJanela.setCorDeFundo(Cor(wasBeat * 128, wasBeat * 128, wasBeat * 128));
	
	int dirX = 0, dirY = 0;
	if (gTeclado.segurando[TECLA_DIR] || gTeclado.segurando[TECLA_D])
		dirX++;
	if (gTeclado.segurando[TECLA_ESQ] || gTeclado.segurando[TECLA_A])
		dirX--;
	if (gTeclado.segurando[TECLA_CIMA] || gTeclado.segurando[TECLA_W])
		dirY--;
	if (gTeclado.segurando[TECLA_BAIXO] || gTeclado.segurando[TECLA_S])
		dirY++;
	float l = sqrt(dirX * dirX + dirY * dirY);
	if (l == 0) l = 1;
	float dir[] = { dirX / l , dirY / l };
	player.mover(dir);

	player.desenhar();

	if ((gTeclado.pressionou[TECLA_ESPACO] || gTeclado.segurando[TECLA_ESPACO]) && player.reloaded())
	{
		unsigned int playerSpriteHeight = gRecursos.getSpriteSheet("player")->getTextura()->getAltura();
		unsigned int bulletSpriteWidth = gRecursos.getSpriteSheet("bullet")->getTextura()->getLargura();
		unsigned int bulletSpriteHeight = gRecursos.getSpriteSheet("bullet")->getTextura()->getAltura();
		bullets.push_back(Bullet("bullet", player.getX(), player.getY() - playerSpriteHeight / 2 - bulletSpriteHeight / 2, std::min(bulletSpriteWidth, bulletSpriteHeight) / 2));
		player.reload();
	}

	unsigned int i = 0;
	while (i < bullets.size())
	{
		unsigned int j = 0;
		bool deleted = false;
		while (j < enemies.size())
		{
			if (uniTestarColisao(bullets[i].getSprite(), bullets[i].getX(), bullets[i].getY(), 0, enemies[j].getSprite(), enemies[j].getX(), enemies[j].getY(), 0)) {
				enemies.erase(enemies.begin() + j);
				bullets.erase(bullets.begin() + i);
				points += 10;
				deleted = true;
				break;
			}
			else
				j++;
		}
		if (!deleted)
			i++;
	}

	i = 0;
	while (i < bullets.size())
	{
		if (bullets[i].getY() < -bullets[i].getSprite().getAltura())
		{
			bullets.erase(bullets.begin() + i);
			unsigned int before = points;
			points -= 10;
			if (points > before)
				points = 0;
		}
		else
			i++;
	}
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i].mover();
		bullets[i].desenhar();
	}

	if (wasBeat)
	{
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			enemies[i].mover();
		}
	}

	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		enemies[i].desenhar();
	}

	if (enemies.size() > 0)
	{
		int leftMostEnemyX = 2 * gJanela.getLargura();
		int leftMostEnemyIndex = -1;
		int rightMostEnemyX = -2 * gJanela.getLargura();
		int rightMostEnemyIndex = -1;
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			if (leftMostEnemyX > enemies[i].getX())
			{
				leftMostEnemyX = enemies[i].getX();
				leftMostEnemyIndex = i;
			}

			if (rightMostEnemyX < enemies[i].getX())
			{
				rightMostEnemyX = enemies[i].getX();
				rightMostEnemyIndex = i;
			}
		}
		if (leftMostEnemyX < enemies[leftMostEnemyIndex].getLargura())
		{
			int dx = enemies[leftMostEnemyIndex].getLargura() - enemies[leftMostEnemyIndex].getX();
			for (unsigned int i = 0; i < enemies.size(); i++)
			{
				enemies[i].toggleDir();
				enemies[i].descer();
				enemies[i].incX(dx);
			}
		}
		else if (rightMostEnemyX > (gJanela.getLargura() - enemies[rightMostEnemyIndex].getLargura()))
		{
			int dx = (gJanela.getLargura() - enemies[rightMostEnemyIndex].getLargura()) - enemies[rightMostEnemyIndex].getX();
			for (unsigned int i = 0; i < enemies.size(); i++)
			{
				enemies[i].toggleDir();
				enemies[i].descer();
				enemies[i].incX(dx);
			}
		}
	}
}