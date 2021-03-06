/*******************************************************************************
 *
 * Copyright (c) 2019 Gnarly Narwhal
 *
 * -----------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#ifndef GNARLY_GENOME_AUDIO_BUFFER
#define GNARLY_GENOME_AUDIO_BUFFER

#include "../GenoInts.h"
#include "../data/GenoWavFile.h"

class GenoAudioBuffer {
	private:
		uint32 buffer;

		void clean();
	public:
		GenoAudioBuffer(uint32 format, uint32 size, uint8 data[], uint32 frequency);
		GenoAudioBuffer(GenoWavFile * wavFile);
		GenoAudioBuffer(const char * path);
		void bufferData(uint32 format, uint32 size, uint8 data[], uint32 frequency);
		void loadWav(GenoWavFile * wavFile);
		void loadWav(const char * path);
		uint32 getBuffer();
		~GenoAudioBuffer();
};

#define GNARLY_GENOME_AUDIO_BUFFER_FORWARD
#endif // GNARLY_GENOME_AUDIO_BUFFER