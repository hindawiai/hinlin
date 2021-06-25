<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा DTLK_MINOR	0
#घोषणा DTLK_IO_EXTENT	0x02

	/* ioctl's use magic number of 0xa3 */
#घोषणा DTLK_INTERROGATE 0xa390	/* get settings from the DoubleTalk */
#घोषणा DTLK_STATUS 0xa391	/* get status from the DoubleTalk */


#घोषणा DTLK_CLEAR 0x18		/* stops speech */

#घोषणा DTLK_MAX_RETRIES (loops_per_jअगरfy/(10000/HZ))

	/* TTS Port Status Flags */
#घोषणा TTS_READABLE     0x80	/* mask क्रम bit which is nonzero अगर a
				   byte can be पढ़ो from the TTS port */
#घोषणा TTS_SPEAKING     0x40	/* mask क्रम SYNC bit, which is nonzero
				   जबतक DoubleTalk is producing
				   output with TTS, PCM or CVSD
				   synthesizers or tone generators
				   (that is, all but LPC) */
#घोषणा TTS_SPEAKING2    0x20	/* mask क्रम SYNC2 bit,
				   which falls to zero up to 0.4 sec
				   beक्रमe speech stops */
#घोषणा TTS_WRITABLE     0x10	/* mask क्रम RDY bit, which when set to
             			   1, indicates the TTS port is पढ़ोy
             			   to accept a byte of data.  The RDY
             			   bit goes zero 2-3 usec after
             			   writing, and goes 1 again 180-190
             			   usec later. */
#घोषणा TTS_ALMOST_FULL  0x08	/* mask क्रम AF bit: When set to 1,
				   indicates that less than 300 मुक्त
				   bytes are available in the TTS
				   input buffer. AF is always 0 in the
				   PCM, TGN and CVSD modes. */
#घोषणा TTS_ALMOST_EMPTY 0x04	/* mask क्रम AE bit: When set to 1,
				   indicates that less than 300 bytes
				   of data reमुख्य in DoubleTalk's
				   input (TTS or PCM) buffer. AE is
				   always 1 in the TGN and CVSD
				   modes. */

	/* LPC speak commands */
#घोषणा LPC_5220_NORMAL 0x60	/* 5220 क्रमmat decoding table, normal rate */
#घोषणा LPC_5220_FAST 0x64	/* 5220 क्रमmat decoding table, fast rate */
#घोषणा LPC_D6_NORMAL 0x20	/* D6 क्रमmat decoding table, normal rate */
#घोषणा LPC_D6_FAST 0x24	/* D6 क्रमmat decoding table, fast rate */

	/* LPC Port Status Flags (valid only after one of the LPC
           speak commands) */
#घोषणा LPC_SPEAKING     0x80	/* mask क्रम TS bit: When set to 1,
				   indicates the LPC synthesizer is
				   producing speech.*/
#घोषणा LPC_BUFFER_LOW   0x40	/* mask क्रम BL bit: When set to 1,
				   indicates that the hardware LPC
				   data buffer has less than 30 bytes
				   reमुख्यing. (Total पूर्णांकernal buffer
				   size = 4096 bytes.) */
#घोषणा LPC_BUFFER_EMPTY 0x20	/* mask क्रम BE bit: When set to 1,
				   indicates that the LPC data buffer
				   ran out of data (error condition अगर
				   TS is also 1).  */

				/* data वापसed by Interrogate command */
काष्ठा dtlk_settings
अणु
  अचिन्हित लघु serial_number;	/* 0-7Fh:0-7Fh */
  अचिन्हित अक्षर rom_version[24]; /* null terminated string */
  अचिन्हित अक्षर mode;		/* 0=Character; 1=Phoneme; 2=Text */
  अचिन्हित अक्षर punc_level;	/* nB; 0-7 */
  अचिन्हित अक्षर क्रमmant_freq;	/* nF; 0-9 */
  अचिन्हित अक्षर pitch;		/* nP; 0-99 */
  अचिन्हित अक्षर speed;		/* nS; 0-9 */
  अचिन्हित अक्षर volume;		/* nV; 0-9 */
  अचिन्हित अक्षर tone;		/* nX; 0-2 */
  अचिन्हित अक्षर expression;	/* nE; 0-9 */
  अचिन्हित अक्षर ext_dict_loaded; /* 1=exception dictionary loaded */
  अचिन्हित अक्षर ext_dict_status; /* 1=exception dictionary enabled */
  अचिन्हित अक्षर मुक्त_ram;	/* # pages (truncated) reमुख्यing क्रम
                                   text buffer */
  अचिन्हित अक्षर articulation;	/* nA; 0-9 */
  अचिन्हित अक्षर reverb;		/* nR; 0-9 */
  अचिन्हित अक्षर eob;		/* 7Fh value indicating end of
                                   parameter block */
  अचिन्हित अक्षर has_indexing;	/* nonzero अगर indexing is implemented */
पूर्ण;
