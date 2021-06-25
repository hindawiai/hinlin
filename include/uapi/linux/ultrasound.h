<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ULTRASOUND_H_
#घोषणा _ULTRASOUND_H_
/*
 *	ultrasound.h - Macros क्रम programming the Gravis Ultrasound
 *			These macros are extremely device dependent
 *			and not portable.
 */
/*
 * Copyright (C) by Hannu Savolainen 1993-1997
 *
 * OSS/Free क्रम Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)
 * Version 2 (June 1991). See the "COPYING" file distributed with this software
 * क्रम more info.
 */


/*
 *	Private events क्रम Gravis Ultrasound (GUS)
 *
 *	Format:
 *		byte 0 		- SEQ_PRIVATE (0xfe)
 *		byte 1 		- Synthesizer device number (0-N)
 *		byte 2 		- Command (see below)
 *		byte 3 		- Voice number (0-31)
 *		bytes 4 and 5	- parameter P1 (अचिन्हित लघु)
 *		bytes 6 and 7	- parameter P2 (अचिन्हित लघु)
 *
 *	Commands:
 *		Each command affects one voice defined in byte 3.
 *		Unused parameters (P1 and/or P2 *MUST* be initialized to zero).
 *		_GUS_NUMVOICES	- Sets max. number of concurrent voices (P1=14-31, शेष 16)
 *		_GUS_VOICESAMPLE- ************ OBSOLETE *************
 *		_GUS_VOICEON	- Starts voice (P1=voice mode)
 *		_GUS_VOICखातापूर्णF	- Stops voice (no parameters)
 *		_GUS_VOICEFADE	- Stops the voice smoothly.
 *		_GUS_VOICEMODE	- Alters the voice mode, करोn't start or stop voice (P1=voice mode)
 *		_GUS_VOICEBALA	- Sets voice balance (P1, 0=left, 7=middle and 15=right, शेष 7)
 *		_GUS_VOICEFREQ	- Sets voice (sample) playback frequency (P1=Hz)
 *		_GUS_VOICEVOL	- Sets voice volume (P1=volume, 0xfff=max, 0xeff=half, 0x000=off)
 *		_GUS_VOICEVOL2	- Sets voice volume (P1=volume, 0xfff=max, 0xeff=half, 0x000=off)
 *				  (Like GUS_VOICEVOL but करोesn't change the hw
 *				  volume. It just updates volume in the voice table).
 *
 *		_GUS_RAMPRANGE	- Sets limits क्रम volume ramping (P1=low volume, P2=high volume)
 *		_GUS_RAMPRATE	- Sets the speed क्रम volume ramping (P1=scale, P2=rate)
 *		_GUS_RAMPMODE	- Sets the volume ramping mode (P1=ramping mode)
 *		_GUS_RAMPON	- Starts volume ramping (no parameters)
 *		_GUS_RAMPOFF	- Stops volume ramping (no parameters)
 *		_GUS_VOLUME_SCALE - Changes the volume calculation स्थिरants
 *				  क्रम all voices.
 */

#घोषणा _GUS_NUMVOICES		0x00
#घोषणा _GUS_VOICESAMPLE	0x01	/* OBSOLETE */
#घोषणा _GUS_VOICEON		0x02
#घोषणा _GUS_VOICखातापूर्णF		0x03
#घोषणा _GUS_VOICEMODE		0x04
#घोषणा _GUS_VOICEBALA		0x05
#घोषणा _GUS_VOICEFREQ		0x06
#घोषणा _GUS_VOICEVOL		0x07
#घोषणा _GUS_RAMPRANGE		0x08
#घोषणा _GUS_RAMPRATE		0x09
#घोषणा _GUS_RAMPMODE		0x0a
#घोषणा _GUS_RAMPON		0x0b
#घोषणा _GUS_RAMPOFF		0x0c
#घोषणा _GUS_VOICEFADE		0x0d
#घोषणा _GUS_VOLUME_SCALE	0x0e
#घोषणा _GUS_VOICEVOL2		0x0f
#घोषणा _GUS_VOICE_POS		0x10

/*
 *	GUS API macros
 */

#घोषणा _GUS_CMD(chn, voice, cmd, p1, p2) \
					अणु_SEQ_NEEDBUF(8); _seqbuf[_seqbufptr] = SEQ_PRIVATE;\
					_seqbuf[_seqbufptr+1] = (chn); _seqbuf[_seqbufptr+2] = cmd;\
					_seqbuf[_seqbufptr+3] = voice;\
					*(अचिन्हित लघु*)&_seqbuf[_seqbufptr+4] = p1;\
					*(अचिन्हित लघु*)&_seqbuf[_seqbufptr+6] = p2;\
					_SEQ_ADVBUF(8);पूर्ण

#घोषणा GUS_NUMVOICES(chn, p1)			_GUS_CMD(chn, 0, _GUS_NUMVOICES, (p1), 0)
#घोषणा GUS_VOICESAMPLE(chn, voice, p1)		_GUS_CMD(chn, voice, _GUS_VOICESAMPLE, (p1), 0)	/* OBSOLETE */
#घोषणा GUS_VOICEON(chn, voice, p1)		_GUS_CMD(chn, voice, _GUS_VOICEON, (p1), 0)
#घोषणा GUS_VOICखातापूर्णF(chn, voice)		_GUS_CMD(chn, voice, _GUS_VOICखातापूर्णF, 0, 0)
#घोषणा GUS_VOICEFADE(chn, voice)		_GUS_CMD(chn, voice, _GUS_VOICEFADE, 0, 0)
#घोषणा GUS_VOICEMODE(chn, voice, p1)		_GUS_CMD(chn, voice, _GUS_VOICEMODE, (p1), 0)
#घोषणा GUS_VOICEBALA(chn, voice, p1)		_GUS_CMD(chn, voice, _GUS_VOICEBALA, (p1), 0)
#घोषणा GUS_VOICEFREQ(chn, voice, p)		_GUS_CMD(chn, voice, _GUS_VOICEFREQ, \
							(p) & 0xffff, ((p) >> 16) & 0xffff)
#घोषणा GUS_VOICEVOL(chn, voice, p1)		_GUS_CMD(chn, voice, _GUS_VOICEVOL, (p1), 0)
#घोषणा GUS_VOICEVOL2(chn, voice, p1)		_GUS_CMD(chn, voice, _GUS_VOICEVOL2, (p1), 0)
#घोषणा GUS_RAMPRANGE(chn, voice, low, high)	_GUS_CMD(chn, voice, _GUS_RAMPRANGE, (low), (high))
#घोषणा GUS_RAMPRATE(chn, voice, p1, p2)	_GUS_CMD(chn, voice, _GUS_RAMPRATE, (p1), (p2))
#घोषणा GUS_RAMPMODE(chn, voice, p1)		_GUS_CMD(chn, voice, _GUS_RAMPMODE, (p1), 0)
#घोषणा GUS_RAMPON(chn, voice, p1)		_GUS_CMD(chn, voice, _GUS_RAMPON, (p1), 0)
#घोषणा GUS_RAMPOFF(chn, voice)			_GUS_CMD(chn, voice, _GUS_RAMPOFF, 0, 0)
#घोषणा GUS_VOLUME_SCALE(chn, voice, p1, p2)	_GUS_CMD(chn, voice, _GUS_VOLUME_SCALE, (p1), (p2))
#घोषणा GUS_VOICE_POS(chn, voice, p)		_GUS_CMD(chn, voice, _GUS_VOICE_POS, \
							(p) & 0xffff, ((p) >> 16) & 0xffff)

#पूर्ण_अगर
