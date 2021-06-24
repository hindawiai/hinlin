<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* speakup_dtlk.h - header file क्रम speakups DoubleTalk driver. */

#घोषणा SYNTH_IO_EXTENT	0x02
#घोषणा SYNTH_CLEAR	0x18		/* stops speech */
	/* TTS Port Status Flags */
#घोषणा TTS_READABLE	0x80	/* mask क्रम bit which is nonzero अगर a
				 * byte can be पढ़ो from the TTS port
				 */
#घोषणा TTS_SPEAKING	0x40	/* mask क्रम SYNC bit, which is nonzero
				 * जबतक DoubleTalk is producing
				 * output with TTS, PCM or CVSD
				 * synthesizers or tone generators
				 * (that is, all but LPC)
				 */
#घोषणा TTS_SPEAKING2	0x20	/* mask क्रम SYNC2 bit,
				 * which falls to zero up to 0.4 sec
				 * beक्रमe speech stops
				 */
#घोषणा TTS_WRITABLE	0x10	/* mask क्रम RDY bit, which when set to
				 * 1, indicates the TTS port is पढ़ोy
				 * to accept a byte of data.  The RDY
				 * bit goes zero 2-3 usec after
				 * writing, and goes 1 again 180-190
				 * usec later.
				 */
#घोषणा TTS_ALMOST_FULL	0x08	/* mask क्रम AF bit: When set to 1,
				 * indicates that less than 300 bytes
				 * are available in the TTS input
				 * buffer. AF is always 0 in the PCM,
				 * TGN and CVSD modes.
				 */
#घोषणा TTS_ALMOST_EMPTY 0x04	/* mask क्रम AE bit: When set to 1,
				 * indicates that less than 300 bytes
				 * are reमुख्यing in DoubleTalk's input
				 * (TTS or PCM) buffer. AE is always 1
				 * in the TGN and CVSD modes.
				 */

				/* data वापसed by Interrogate command */
काष्ठा synth_settings अणु
	u_लघु serial_number;	/* 0-7Fh:0-7Fh */
	u_अक्षर rom_version[24]; /* null terminated string */
	u_अक्षर mode;		/* 0=Character; 1=Phoneme; 2=Text */
	u_अक्षर punc_level;	/* nB; 0-7 */
	u_अक्षर क्रमmant_freq;	/* nF; 0-9 */
	u_अक्षर pitch;		/* nP; 0-99 */
	u_अक्षर speed;		/* nS; 0-9 */
	u_अक्षर volume;		/* nV; 0-9 */
	u_अक्षर tone;		/* nX; 0-2 */
	u_अक्षर expression;	/* nE; 0-9 */
	u_अक्षर ext_dict_loaded; /* 1=exception dictionary loaded */
	u_अक्षर ext_dict_status; /* 1=exception dictionary enabled */
	u_अक्षर मुक्त_ram;	/* # pages (truncated) reमुख्यing क्रम
				 * text buffer
				 */
	u_अक्षर articulation;	/* nA; 0-9 */
	u_अक्षर reverb;		/* nR; 0-9 */
	u_अक्षर eob;		/* 7Fh value indicating end of
				 * parameter block
				 */
	u_अक्षर has_indexing;	/* nonzero अगर indexing is implemented */
पूर्ण;
