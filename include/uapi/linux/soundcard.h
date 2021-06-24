<शैली गुरु>
/*
 * Copyright by Hannu Savolainen 1993-1997
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are
 * met: 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer. 2.
 * Redistributions in binary क्रमm must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the करोcumentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#अगर_अघोषित _UAPISOUNDCARD_H
#घोषणा _UAPISOUNDCARD_H


/*
 * OSS पूर्णांकerface version. With versions earlier than 3.6 this value is
 * an पूर्णांकeger with value less than 361. In versions 3.6 and later
 * it's a six digit hexadecimal value. For example value
 * of 0x030600 represents OSS version 3.6.0.
 * Use ioctl(fd, OSS_GETVERSION, &पूर्णांक) to get the version number of
 * the currently active driver.
 */
#घोषणा SOUND_VERSION	0x030802
#घोषणा OPEN_SOUND_SYSTEM

/* In Linux we need to be prepared क्रम cross compiling */
#समावेश <linux/ioctl.h>

/* Endian macros. */
#अगर_अघोषित __KERNEL__
#  include <endian.h>
#पूर्ण_अगर

/*
 *	Supported card ID numbers (Should be somewhere अन्यथा?)
 */

#घोषणा SNDCARD_ADLIB		1
#घोषणा SNDCARD_SB		2
#घोषणा SNDCARD_PAS		3
#घोषणा SNDCARD_GUS		4
#घोषणा SNDCARD_MPU401		5
#घोषणा SNDCARD_SB16		6
#घोषणा SNDCARD_SB16MIDI	7
#घोषणा SNDCARD_UART6850	8
#घोषणा SNDCARD_GUS16		9
#घोषणा SNDCARD_MSS		10
#घोषणा SNDCARD_PSS     	11
#घोषणा SNDCARD_SSCAPE		12
#घोषणा SNDCARD_PSS_MPU     	13
#घोषणा SNDCARD_PSS_MSS     	14
#घोषणा SNDCARD_SSCAPE_MSS	15
#घोषणा SNDCARD_TRXPRO		16
#घोषणा SNDCARD_TRXPRO_SB	17
#घोषणा SNDCARD_TRXPRO_MPU	18
#घोषणा SNDCARD_MAD16		19
#घोषणा SNDCARD_MAD16_MPU	20
#घोषणा SNDCARD_CS4232		21
#घोषणा SNDCARD_CS4232_MPU	22
#घोषणा SNDCARD_MAUI		23
#घोषणा SNDCARD_PSEUDO_MSS	24
#घोषणा SNDCARD_GUSPNP		25
#घोषणा SNDCARD_UART401		26
/* Sound card numbers 27 to N are reserved. Don't add more numbers here. */

/***********************************
 * IOCTL Commands क्रम /dev/sequencer
 */

#अगर_अघोषित _SIOWR
#अगर defined(_IOWR) && (defined(_AIX) || (!defined(sun) && !defined(sparc) && !defined(__sparc__) && !defined(__INCioctlh) && !defined(__Lynx__)))
/* Use alपढ़ोy defined ioctl defines अगर they exist (except with Sun or Sparc) */
#घोषणा	SIOCPARM_MASK	IOCPARM_MASK
#घोषणा	SIOC_VOID	IOC_VOID
#घोषणा	SIOC_OUT	IOC_OUT
#घोषणा	SIOC_IN		IOC_IN
#घोषणा	SIOC_INOUT	IOC_INOUT
#घोषणा _SIOC_SIZE	_IOC_SIZE
#घोषणा _SIOC_सूची	_IOC_सूची
#घोषणा _SIOC_NONE	_IOC_NONE
#घोषणा _SIOC_READ	_IOC_READ
#घोषणा _SIOC_WRITE	_IOC_WRITE
#घोषणा	_SIO		_IO
#घोषणा	_SIOR		_IOR
#घोषणा	_SIOW		_IOW
#घोषणा	_SIOWR		_IOWR
#अन्यथा

/* Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; क्रम now
 * we restrict parameters to at most 8191 bytes.
 */
/* #घोषणा	SIOCTYPE		(0xff<<8) */
#घोषणा	SIOCPARM_MASK	0x1fff		/* parameters must be < 8192 bytes */
#घोषणा	SIOC_VOID	0x00000000	/* no parameters */
#घोषणा	SIOC_OUT	0x20000000	/* copy out parameters */
#घोषणा	SIOC_IN		0x40000000	/* copy in parameters */
#घोषणा	SIOC_INOUT	(SIOC_IN|SIOC_OUT)
/* the 0x20000000 is so we can distinguish new ioctl's from old */
#घोषणा	_SIO(x,y)	((पूर्णांक)(SIOC_VOID|(x<<8)|y))
#घोषणा	_SIOR(x,y,t)	((पूर्णांक)(SIOC_OUT|((माप(t)&SIOCPARM_MASK)<<16)|(x<<8)|y))
#घोषणा	_SIOW(x,y,t)	((पूर्णांक)(SIOC_IN|((माप(t)&SIOCPARM_MASK)<<16)|(x<<8)|y))
/* this should be _SIORW, but stdio got there first */
#घोषणा	_SIOWR(x,y,t)	((पूर्णांक)(SIOC_INOUT|((माप(t)&SIOCPARM_MASK)<<16)|(x<<8)|y))
#घोषणा _SIOC_SIZE(x)	((x>>16)&SIOCPARM_MASK)	
#घोषणा _SIOC_सूची(x)	(x & 0xf0000000)
#घोषणा _SIOC_NONE	SIOC_VOID
#घोषणा _SIOC_READ	SIOC_OUT
#घोषणा _SIOC_WRITE	SIOC_IN
#  endअगर /* _IOWR */
#पूर्ण_अगर  /* !_SIOWR */

#घोषणा SNDCTL_SEQ_RESET		_SIO  ('Q', 0)
#घोषणा SNDCTL_SEQ_SYNC			_SIO  ('Q', 1)
#घोषणा SNDCTL_SYNTH_INFO		_SIOWR('Q', 2, काष्ठा synth_info)
#घोषणा SNDCTL_SEQ_CTRLRATE		_SIOWR('Q', 3, पूर्णांक)	/* Set/get समयr resolution (HZ) */
#घोषणा SNDCTL_SEQ_GETOUTCOUNT		_SIOR ('Q', 4, पूर्णांक)
#घोषणा SNDCTL_SEQ_GETINCOUNT		_SIOR ('Q', 5, पूर्णांक)
#घोषणा SNDCTL_SEQ_PERCMODE		_SIOW ('Q', 6, पूर्णांक)
#घोषणा SNDCTL_FM_LOAD_INSTR		_SIOW ('Q', 7, struct sbi_instrument)	/* Obsolete. Don't use!!!!!! */
#घोषणा SNDCTL_SEQ_TESTMIDI		_SIOW ('Q', 8, पूर्णांक)
#घोषणा SNDCTL_SEQ_RESETSAMPLES		_SIOW ('Q', 9, पूर्णांक)
#घोषणा SNDCTL_SEQ_NRSYNTHS		_SIOR ('Q',10, पूर्णांक)
#घोषणा SNDCTL_SEQ_NRMIDIS		_SIOR ('Q',11, पूर्णांक)
#घोषणा SNDCTL_MIDI_INFO		_SIOWR('Q',12, काष्ठा midi_info)
#घोषणा SNDCTL_SEQ_THRESHOLD		_SIOW ('Q',13, पूर्णांक)
#घोषणा SNDCTL_SYNTH_MEMAVL		_SIOWR('Q',14, पूर्णांक)	/* in=dev#, out=memsize */
#घोषणा SNDCTL_FM_4OP_ENABLE		_SIOW ('Q',15, पूर्णांक)	/* in=dev# */
#घोषणा SNDCTL_SEQ_PANIC		_SIO  ('Q',17)
#घोषणा SNDCTL_SEQ_OUTOFBAND		_SIOW ('Q',18, काष्ठा seq_event_rec)
#घोषणा SNDCTL_SEQ_GETTIME		_SIOR ('Q',19, पूर्णांक)
#घोषणा SNDCTL_SYNTH_ID			_SIOWR('Q',20, काष्ठा synth_info)
#घोषणा SNDCTL_SYNTH_CONTROL		_SIOWR('Q',21, काष्ठा synth_control)
#घोषणा SNDCTL_SYNTH_REMOVESAMPLE	_SIOWR('Q',22, काष्ठा हटाओ_sample)

प्रकार काष्ठा synth_control
अणु
	पूर्णांक devno;	/* Synthesizer # */
	अक्षर data[4000]; /* Device spesअगरic command/data record */
पूर्णsynth_control;

प्रकार काष्ठा हटाओ_sample
अणु
	पूर्णांक devno;	/* Synthesizer # */
	पूर्णांक bankno;	/* MIDI bank # (0=General MIDI) */
	पूर्णांक instrno;	/* MIDI instrument number */
पूर्ण हटाओ_sample;

प्रकार काष्ठा seq_event_rec अणु
		अचिन्हित अक्षर arr[8];
पूर्ण seq_event_rec;

#घोषणा SNDCTL_TMR_TIMEBASE		_SIOWR('T', 1, पूर्णांक)
#घोषणा SNDCTL_TMR_START		_SIO  ('T', 2)
#घोषणा SNDCTL_TMR_STOP			_SIO  ('T', 3)
#घोषणा SNDCTL_TMR_CONTINUE		_SIO  ('T', 4)
#घोषणा SNDCTL_TMR_TEMPO		_SIOWR('T', 5, पूर्णांक)
#घोषणा SNDCTL_TMR_SOURCE		_SIOWR('T', 6, पूर्णांक)
#	define TMR_INTERNAL		0x00000001
#	define TMR_EXTERNAL		0x00000002
#		define TMR_MODE_MIDI	0x00000010
#		define TMR_MODE_FSK	0x00000020
#		define TMR_MODE_CLS	0x00000040
#		define TMR_MODE_SMPTE	0x00000080
#घोषणा SNDCTL_TMR_METRONOME		_SIOW ('T', 7, पूर्णांक)
#घोषणा SNDCTL_TMR_SELECT		_SIOW ('T', 8, पूर्णांक)

/*
 * Some big endian/little endian handling macros
 */

#घोषणा _LINUX_PATCHKEY_H_INसूचीECT
#समावेश <linux/patchkey.h>
#अघोषित _LINUX_PATCHKEY_H_INसूचीECT

#अगर !defined(__KERNEL__)
# अगर defined(__BYTE_ORDER)
#  अगर __BYTE_ORDER == __BIG_ENDIAN
#    define AFMT_S16_NE AFMT_S16_BE
#  elअगर __BYTE_ORDER == __LITTLE_ENDIAN
#    define AFMT_S16_NE AFMT_S16_LE
#  अन्यथा
#    error "could not determine byte order"
#  endअगर
# endअगर
#पूर्ण_अगर

/*
 *	Sample loading mechanism क्रम पूर्णांकernal synthesizers (/dev/sequencer)
 *	The following patch_info काष्ठाure has been deचिन्हित to support
 *	Gravis UltraSound. It tries to be universal क्रमmat क्रम uploading
 *	sample based patches but is probably too limited.
 *
 *      (PBD) As Hannu guessed, the GUS काष्ठाure is too limited क्रम 
 *      the WaveFront, but this is the right place क्रम a स्थिरant definition.
 */

काष्ठा patch_info अणु
		अचिन्हित लघु key;		/* Use WAVE_PATCH here */
#घोषणा WAVE_PATCH	   _PATCHKEY(0x04)
#घोषणा GUS_PATCH	   WAVE_PATCH
#घोषणा WAVEFRONT_PATCH    _PATCHKEY(0x06)

		लघु device_no;	/* Synthesizer number */
		लघु instr_no;		/* Midi pgm# */

		अचिन्हित पूर्णांक mode;
/*
 * The least signअगरicant byte has the same क्रमmat than the GUS .PAT
 * files
 */
#घोषणा WAVE_16_BITS	0x01	/* bit 0 = 8 or 16 bit wave data. */
#घोषणा WAVE_UNSIGNED	0x02	/* bit 1 = Signed - Unचिन्हित data. */
#घोषणा WAVE_LOOPING	0x04	/* bit 2 = looping enabled-1. */
#घोषणा WAVE_BIसूची_LOOP	0x08	/* bit 3 = Set is bidirectional looping. */
#घोषणा WAVE_LOOP_BACK	0x10	/* bit 4 = Set is looping backward. */
#घोषणा WAVE_SUSTAIN_ON	0x20	/* bit 5 = Turn sustaining on. (Env. pts. 3)*/
#घोषणा WAVE_ENVELOPES	0x40	/* bit 6 = Enable envelopes - 1 */
#घोषणा WAVE_FAST_RELEASE 0x80	/* bit 7 = Shut off immediately after note off */
				/* 	(use the env_rate/env_offs fields). */
/* Linux specअगरic bits */
#घोषणा WAVE_VIBRATO	0x00010000	/* The vibrato info is valid */
#घोषणा WAVE_TREMOLO	0x00020000	/* The tremolo info is valid */
#घोषणा WAVE_SCALE	0x00040000	/* The scaling info is valid */
#घोषणा WAVE_FRACTIONS	0x00080000	/* Fraction inक्रमmation is valid */
/* Reserved bits */
#घोषणा WAVE_ROM	0x40000000	/* For future use */
#घोषणा WAVE_MULAW	0x20000000	/* For future use */
/* Other bits must be zeroed */

		पूर्णांक len;	/* Size of the wave data in bytes */
		पूर्णांक loop_start, loop_end; /* Byte offsets from the beginning */

/* 
 * The base_freq and base_note fields are used when computing the
 * playback speed क्रम a note. The base_note defines the tone frequency
 * which is heard अगर the sample is played using the base_freq as the
 * playback speed.
 *
 * The low_note and high_note fields define the minimum and maximum note
 * frequencies क्रम which this sample is valid. It is possible to define
 * more than one samples क्रम an instrument number at the same समय. The
 * low_note and high_note fields are used to select the most suitable one.
 *
 * The fields base_note, high_note and low_note should contain
 * the note frequency multiplied by 1000. For example value क्रम the
 * middle A is 440*1000.
 */

		अचिन्हित पूर्णांक base_freq;
		अचिन्हित पूर्णांक base_note;
		अचिन्हित पूर्णांक high_note;
		अचिन्हित पूर्णांक low_note;
		पूर्णांक panning;	/* -128=left, 127=right */
		पूर्णांक detuning;

/*	New fields पूर्णांकroduced in version 1.99.5	*/

       /* Envelope. Enabled by mode bit WAVE_ENVELOPES	*/
		अचिन्हित अक्षर	env_rate[ 6 ];	 /* GUS HW ramping rate */
		अचिन्हित अक्षर	env_offset[ 6 ]; /* 255 == 100% */

	/* 
	 * The tremolo, vibrato and scale info are not supported yet.
	 * Enable by setting the mode bits WAVE_TREMOLO, WAVE_VIBRATO or
	 * WAVE_SCALE
	 */

		अचिन्हित अक्षर	tremolo_sweep;
		अचिन्हित अक्षर	tremolo_rate;
		अचिन्हित अक्षर	tremolo_depth;
	
		अचिन्हित अक्षर	vibrato_sweep;
		अचिन्हित अक्षर	vibrato_rate;
		अचिन्हित अक्षर	vibrato_depth;

		पूर्णांक		scale_frequency;
		अचिन्हित पूर्णांक	scale_factor;		/* from 0 to 2048 or 0 to 2 */
	
	        पूर्णांक		volume;
		पूर्णांक		fractions;
		पूर्णांक		reserved1;
	        पूर्णांक		spare[2];
		अक्षर data[1];	/* The waveक्रमm data starts here */
	पूर्ण;

काष्ठा sysex_info अणु
		लघु key;		/* Use SYSEX_PATCH or MAUI_PATCH here */
#घोषणा SYSEX_PATCH	_PATCHKEY(0x05)
#घोषणा MAUI_PATCH	_PATCHKEY(0x06)
		लघु device_no;	/* Synthesizer number */
		पूर्णांक len;	/* Size of the sysex data in bytes */
		अचिन्हित अक्षर data[1];	/* Sysex data starts here */
	पूर्ण;

/*
 * /dev/sequencer input events.
 *
 * The data written to the /dev/sequencer is a stream of events. Events
 * are records of 4 or 8 bytes. The first byte defines the size. 
 * Any number of events can be written with a ग_लिखो call. There
 * is a set of macros क्रम sending these events. Use these macros अगर you
 * want to maximize portability of your program.
 *
 * Events SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO. Are also input events.
 * (All input events are currently 4 bytes दीर्घ. Be prepared to support
 * 8 byte events also. If you receive any event having first byte >= 128,
 * it's a 8 byte event.
 *
 * The events are करोcumented at the end of this file.
 *
 * Normal events (4 bytes)
 * There is also a 8 byte version of most of the 4 byte events. The
 * 8 byte one is recommended.
 */
#घोषणा SEQ_NOTखातापूर्णF		0
#घोषणा SEQ_FMNOTखातापूर्णF		SEQ_NOTखातापूर्णF	/* Just old name */
#घोषणा SEQ_NOTEON		1
#घोषणा	SEQ_FMNOTEON		SEQ_NOTEON
#घोषणा SEQ_WAIT		TMR_WAIT_ABS
#घोषणा SEQ_PGMCHANGE		3
#घोषणा SEQ_FMPGMCHANGE		SEQ_PGMCHANGE
#घोषणा SEQ_SYNCTIMER		TMR_START
#घोषणा SEQ_MIDIPUTC		5
#घोषणा SEQ_DRUMON		6	/*** OBSOLETE ***/
#घोषणा SEQ_DRUMOFF		7	/*** OBSOLETE ***/
#घोषणा SEQ_ECHO		TMR_ECHO	/* For synching programs with output */
#घोषणा SEQ_AFTERTOUCH		9
#घोषणा SEQ_CONTROLLER		10

/*******************************************
 *	Midi controller numbers
 *******************************************
 * Controllers 0 to 31 (0x00 to 0x1f) and
 * 32 to 63 (0x20 to 0x3f) are continuous
 * controllers.
 * In the MIDI 1.0 these controllers are sent using
 * two messages. Controller numbers 0 to 31 are used
 * to send the MSB and the controller numbers 32 to 63
 * are क्रम the LSB. Note that just 7 bits are used in MIDI bytes.
 */

#घोषणा	   CTL_BANK_SELECT		0x00
#घोषणा	   CTL_MODWHEEL			0x01
#घोषणा    CTL_BREATH			0x02
/*		undefined		0x03 */
#घोषणा    CTL_FOOT			0x04
#घोषणा    CTL_PORTAMENTO_TIME		0x05
#घोषणा    CTL_DATA_ENTRY		0x06
#घोषणा    CTL_MAIN_VOLUME		0x07
#घोषणा    CTL_BALANCE			0x08
/*		undefined		0x09 */
#घोषणा    CTL_PAN			0x0a
#घोषणा    CTL_EXPRESSION		0x0b
/*		undefined		0x0c */
/*		undefined		0x0d */
/*		undefined		0x0e */
/*		undefined		0x0f */
#घोषणा    CTL_GENERAL_PURPOSE1	0x10
#घोषणा    CTL_GENERAL_PURPOSE2	0x11
#घोषणा    CTL_GENERAL_PURPOSE3	0x12
#घोषणा    CTL_GENERAL_PURPOSE4	0x13
/*		undefined		0x14 - 0x1f */

/*		undefined		0x20 */
/* The controller numbers 0x21 to 0x3f are reserved क्रम the */
/* least signअगरicant bytes of the controllers 0x00 to 0x1f. */
/* These controllers are not recognised by the driver. */

/* Controllers 64 to 69 (0x40 to 0x45) are on/off चयनes. */
/* 0=OFF and 127=ON (पूर्णांकermediate values are possible) */
#घोषणा    CTL_DAMPER_PEDAL		0x40
#घोषणा    CTL_SUSTAIN			0x40	/* Alias */
#घोषणा    CTL_HOLD			0x40	/* Alias */
#घोषणा    CTL_PORTAMENTO		0x41
#घोषणा    CTL_SOSTENUTO		0x42
#घोषणा    CTL_SOFT_PEDAL		0x43
/*		undefined		0x44 */
#घोषणा    CTL_HOLD2			0x45
/*		undefined		0x46 - 0x4f */

#घोषणा    CTL_GENERAL_PURPOSE5	0x50
#घोषणा    CTL_GENERAL_PURPOSE6	0x51
#घोषणा    CTL_GENERAL_PURPOSE7	0x52
#घोषणा    CTL_GENERAL_PURPOSE8	0x53
/*		undefined		0x54 - 0x5a */
#घोषणा    CTL_EXT_EFF_DEPTH		0x5b
#घोषणा    CTL_TREMOLO_DEPTH		0x5c
#घोषणा    CTL_CHORUS_DEPTH		0x5d
#घोषणा    CTL_DETUNE_DEPTH		0x5e
#घोषणा    CTL_CELESTE_DEPTH		0x5e	/* Alias क्रम the above one */
#घोषणा    CTL_PHASER_DEPTH		0x5f
#घोषणा    CTL_DATA_INCREMENT		0x60
#घोषणा    CTL_DATA_DECREMENT		0x61
#घोषणा    CTL_NONREG_PARM_NUM_LSB	0x62
#घोषणा    CTL_NONREG_PARM_NUM_MSB	0x63
#घोषणा    CTL_REGIST_PARM_NUM_LSB	0x64
#घोषणा    CTL_REGIST_PARM_NUM_MSB	0x65
/*		undefined		0x66 - 0x78 */
/*		reserved		0x79 - 0x7f */

/* Pseuकरो controllers (not midi compatible) */
#घोषणा    CTRL_PITCH_BENDER		255
#घोषणा    CTRL_PITCH_BENDER_RANGE	254
#घोषणा    CTRL_EXPRESSION		253	/* Obsolete */
#घोषणा    CTRL_MAIN_VOLUME		252	/* Obsolete */
#घोषणा SEQ_BALANCE		11
#घोषणा SEQ_VOLMODE             12

/*
 * Volume mode decides how volumes are used
 */

#घोषणा VOL_METHOD_ADAGIO	1
#घोषणा VOL_METHOD_LINEAR	2

/*
 * Note! SEQ_WAIT, SEQ_MIDIPUTC and SEQ_ECHO are used also as
 *	 input events.
 */

/*
 * Event codes 0xf0 to 0xfc are reserved क्रम future extensions.
 */

#घोषणा SEQ_FULLSIZE		0xfd	/* Long events */
/*
 *	SEQ_FULLSIZE events are used क्रम loading patches/samples to the
 *	synthesizer devices. These events are passed directly to the driver
 *	of the associated synthesizer device. There is no limit to the size
 *	of the extended events. These events are not queued but executed
 *	immediately when the ग_लिखो() is called (execution can take several
 *	seconds of समय). 
 *
 *	When a SEQ_FULLSIZE message is written to the device, it must
 *	be written using exactly one ग_लिखो() call. Other events cannot
 *	be mixed to the same ग_लिखो.
 *	
 *	For FM synths (YM3812/OPL3) use काष्ठा sbi_instrument and ग_लिखो it to the 
 *	/dev/sequencer. Don't ग_लिखो other data together with the instrument काष्ठाure
 *	Set the key field of the काष्ठाure to FM_PATCH. The device field is used to
 *	route the patch to the corresponding device.
 *
 *	For wave table use काष्ठा patch_info. Initialize the key field
 *      to WAVE_PATCH.
 */
#घोषणा SEQ_PRIVATE		0xfe	/* Low level HW dependent events (8 bytes) */
#घोषणा SEQ_EXTENDED		0xff	/* Extended events (8 bytes) OBSOLETE */

/*
 * Record क्रम FM patches
 */

प्रकार अचिन्हित अक्षर sbi_instr_data[32];

काष्ठा sbi_instrument अणु
		अचिन्हित लघु	key;	/* FM_PATCH or OPL3_PATCH */
#घोषणा FM_PATCH	_PATCHKEY(0x01)
#घोषणा OPL3_PATCH	_PATCHKEY(0x03)
		लघु		device;		/*	Synth# (0-4)	*/
		पूर्णांक 		channel;	/*	Program# to be initialized 	*/
		sbi_instr_data	चालकs;	/*	Register settings क्रम चालक cells (.SBI क्रमmat)	*/
	पूर्ण;

काष्ठा synth_info अणु	/* Read only */
		अक्षर	name[30];
		पूर्णांक	device;		/* 0-N. INITIALIZE BEFORE CALLING */
		पूर्णांक	synth_type;
#घोषणा SYNTH_TYPE_FM			0
#घोषणा SYNTH_TYPE_SAMPLE		1
#घोषणा SYNTH_TYPE_MIDI			2	/* Midi पूर्णांकerface */

		पूर्णांक	synth_subtype;
#घोषणा FM_TYPE_ADLIB			0x00
#घोषणा FM_TYPE_OPL3			0x01
#घोषणा MIDI_TYPE_MPU401		0x401

#घोषणा SAMPLE_TYPE_BASIC		0x10
#घोषणा SAMPLE_TYPE_GUS			SAMPLE_TYPE_BASIC
#घोषणा SAMPLE_TYPE_WAVEFRONT           0x11

		पूर्णांक	perc_mode;	/* No दीर्घer supported */
		पूर्णांक	nr_voices;
		पूर्णांक	nr_drums;	/* Obsolete field */
		पूर्णांक	instr_bank_size;
		अचिन्हित पूर्णांक	capabilities;	
#घोषणा SYNTH_CAP_PERCMODE		0x00000001 /* No दीर्घer used */
#घोषणा SYNTH_CAP_OPL3			0x00000002 /* Set अगर OPL3 supported */
#घोषणा SYNTH_CAP_INPUT			0x00000004 /* Input (MIDI) device */
		पूर्णांक	dummies[19];	/* Reserve space */
	पूर्ण;

काष्ठा sound_समयr_info अणु
		अक्षर name[32];
		पूर्णांक caps;
	पूर्ण;

#घोषणा MIDI_CAP_MPU401		1		/* MPU-401 पूर्णांकelligent mode */

काष्ठा midi_info अणु
		अक्षर		name[30];
		पूर्णांक		device;		/* 0-N. INITIALIZE BEFORE CALLING */
		अचिन्हित पूर्णांक	capabilities;	/* To be defined later */
		पूर्णांक		dev_type;
		पूर्णांक		dummies[18];	/* Reserve space */
	पूर्ण;

/********************************************
 * ioctl commands क्रम the /dev/midi##
 */
प्रकार काष्ठा अणु
		अचिन्हित अक्षर cmd;
		अक्षर nr_args, nr_वापसs;
		अचिन्हित अक्षर data[30];
	पूर्ण mpu_command_rec;

#घोषणा SNDCTL_MIDI_PRETIME		_SIOWR('m', 0, पूर्णांक)
#घोषणा SNDCTL_MIDI_MPUMODE		_SIOWR('m', 1, पूर्णांक)
#घोषणा SNDCTL_MIDI_MPUCMD		_SIOWR('m', 2, mpu_command_rec)

/********************************************
 * IOCTL commands क्रम /dev/dsp and /dev/audio
 */

#घोषणा SNDCTL_DSP_RESET		_SIO  ('P', 0)
#घोषणा SNDCTL_DSP_SYNC			_SIO  ('P', 1)
#घोषणा SNDCTL_DSP_SPEED		_SIOWR('P', 2, पूर्णांक)
#घोषणा SNDCTL_DSP_STEREO		_SIOWR('P', 3, पूर्णांक)
#घोषणा SNDCTL_DSP_GETBLKSIZE		_SIOWR('P', 4, पूर्णांक)
#घोषणा SNDCTL_DSP_SAMPLESIZE		SNDCTL_DSP_SETFMT
#घोषणा SNDCTL_DSP_CHANNELS		_SIOWR('P', 6, पूर्णांक)
#घोषणा SOUND_PCM_WRITE_CHANNELS	SNDCTL_DSP_CHANNELS
#घोषणा SOUND_PCM_WRITE_FILTER		_SIOWR('P', 7, पूर्णांक)
#घोषणा SNDCTL_DSP_POST			_SIO  ('P', 8)
#घोषणा SNDCTL_DSP_SUBDIVIDE		_SIOWR('P', 9, पूर्णांक)
#घोषणा SNDCTL_DSP_SETFRAGMENT		_SIOWR('P',10, पूर्णांक)

/*	Audio data क्रमmats (Note! U8=8 and S16_LE=16 क्रम compatibility) */
#घोषणा SNDCTL_DSP_GETFMTS		_SIOR ('P',11, पूर्णांक) /* Returns a mask */
#घोषणा SNDCTL_DSP_SETFMT		_SIOWR('P',5, पूर्णांक) /* Selects ONE fmt*/
#	define AFMT_QUERY		0x00000000	/* Return current fmt */
#	define AFMT_MU_LAW		0x00000001
#	define AFMT_A_LAW		0x00000002
#	define AFMT_IMA_ADPCM		0x00000004
#	define AFMT_U8			0x00000008
#	define AFMT_S16_LE		0x00000010	/* Little endian चिन्हित 16*/
#	define AFMT_S16_BE		0x00000020	/* Big endian चिन्हित 16 */
#	define AFMT_S8			0x00000040
#	define AFMT_U16_LE		0x00000080	/* Little endian U16 */
#	define AFMT_U16_BE		0x00000100	/* Big endian U16 */
#	define AFMT_MPEG		0x00000200	/* MPEG (2) audio */
#	define AFMT_AC3		0x00000400	/* Dolby Digital AC3 */

/*
 * Buffer status queries.
 */
प्रकार काष्ठा audio_buf_info अणु
			पूर्णांक fragments;	/* # of available fragments (partially usend ones not counted) */
			पूर्णांक fragstotal;	/* Total # of fragments allocated */
			पूर्णांक fragsize;	/* Size of a fragment in bytes */

			पूर्णांक bytes;	/* Available space in bytes (includes partially used fragments) */
			/* Note! 'bytes' could be more than fragments*fragsize */
		पूर्ण audio_buf_info;

#घोषणा SNDCTL_DSP_GETOSPACE		_SIOR ('P',12, audio_buf_info)
#घोषणा SNDCTL_DSP_GETISPACE		_SIOR ('P',13, audio_buf_info)
#घोषणा SNDCTL_DSP_NONBLOCK		_SIO  ('P',14)
#घोषणा SNDCTL_DSP_GETCAPS		_SIOR ('P',15, पूर्णांक)
#	define DSP_CAP_REVISION		0x000000ff	/* Bits क्रम revision level (0 to 255) */
#	define DSP_CAP_DUPLEX		0x00000100	/* Full duplex record/playback */
#	define DSP_CAP_REALTIME		0x00000200	/* Real समय capability */
#	define DSP_CAP_BATCH		0x00000400	/* Device has some kind of */
							/* पूर्णांकernal buffers which may */
							/* cause some delays and */
							/* decrease precision of timing */
#	define DSP_CAP_COPROC		0x00000800	/* Has a coprocessor */
							/* Someबार it's a DSP */
							/* but usually not */
#	define DSP_CAP_TRIGGER		0x00001000	/* Supports SETTRIGGER */
#	define DSP_CAP_MMAP		0x00002000	/* Supports mmap() */
#	define DSP_CAP_MULTI		0x00004000	/* support multiple खोलो */
#	define DSP_CAP_BIND		0x00008000	/* channel binding to front/rear/cneter/lfe */


#घोषणा SNDCTL_DSP_GETTRIGGER		_SIOR ('P',16, पूर्णांक)
#घोषणा SNDCTL_DSP_SETTRIGGER		_SIOW ('P',16, पूर्णांक)
#	define PCM_ENABLE_INPUT		0x00000001
#	define PCM_ENABLE_OUTPUT		0x00000002

प्रकार काष्ठा count_info अणु
		पूर्णांक bytes;	/* Total # of bytes processed */
		पूर्णांक blocks;	/* # of fragment transitions since last समय */
		पूर्णांक ptr;	/* Current DMA poपूर्णांकer value */
	पूर्ण count_info;

#घोषणा SNDCTL_DSP_GETIPTR		_SIOR ('P',17, count_info)
#घोषणा SNDCTL_DSP_GETOPTR		_SIOR ('P',18, count_info)

प्रकार काष्ठा buffmem_desc अणु
		अचिन्हित *buffer;
		पूर्णांक size;
	पूर्ण buffmem_desc;
#घोषणा SNDCTL_DSP_MAPINBUF		_SIOR ('P', 19, buffmem_desc)
#घोषणा SNDCTL_DSP_MAPOUTBUF		_SIOR ('P', 20, buffmem_desc)
#घोषणा SNDCTL_DSP_SETSYNCRO		_SIO  ('P', 21)
#घोषणा SNDCTL_DSP_SETDUPLEX		_SIO  ('P', 22)
#घोषणा SNDCTL_DSP_GETODELAY		_SIOR ('P', 23, पूर्णांक)

#घोषणा SNDCTL_DSP_GETCHANNELMASK		_SIOWR('P', 64, पूर्णांक)
#घोषणा SNDCTL_DSP_BIND_CHANNEL		_SIOWR('P', 65, पूर्णांक)
#	define DSP_BIND_QUERY		0x00000000
#	define DSP_BIND_FRONT		0x00000001
#	define DSP_BIND_SURR		0x00000002
#	define DSP_BIND_CENTER_LFE	0x00000004
#	define DSP_BIND_HANDSET		0x00000008
#	define DSP_BIND_MIC		0x00000010
#	define DSP_BIND_MODEM1		0x00000020
#	define DSP_BIND_MODEM2		0x00000040
#	define DSP_BIND_I2S		0x00000080
#	define DSP_BIND_SPDIF		0x00000100

#घोषणा SNDCTL_DSP_SETSPDIF		_SIOW ('P', 66, पूर्णांक)
#घोषणा SNDCTL_DSP_GETSPDIF		_SIOR ('P', 67, पूर्णांक)
#	define SPDIF_PRO	0x0001
#	define SPDIF_N_AUD	0x0002
#	define SPDIF_COPY	0x0004
#	define SPDIF_PRE	0x0008
#	define SPDIF_CC		0x07f0
#	define SPDIF_L		0x0800
#	define SPDIF_DRS	0x4000
#	define SPDIF_V		0x8000

/*
 * Application's profile defines the way how playback underrun situations should be handled.
 * 
 *	APF_NORMAL (the शेष) and APF_NETWORK make the driver to cleanup the
 *	playback buffer whenever an underrun occurs. This consumes some समय
 *	prevents looping the existing buffer.
 *	APF_CPUINTENS is पूर्णांकended to be set by CPU पूर्णांकensive applications which
 *	are likely to run out of समय occasionally. In this mode the buffer cleanup is
 *	disabled which saves CPU समय but also let's the previous buffer content to
 *	be played during the "pause" after the underrun.
 */
#घोषणा SNDCTL_DSP_PROखाता		_SIOW ('P', 23, पूर्णांक)
#घोषणा	  APF_NORMAL	0	/* Normal applications */
#घोषणा	  APF_NETWORK	1	/* Underruns probably caused by an "external" delay */
#घोषणा   APF_CPUINTENS 2	/* Underruns probably caused by "overheating" the CPU */

#घोषणा SOUND_PCM_READ_RATE		_SIOR ('P', 2, पूर्णांक)
#घोषणा SOUND_PCM_READ_CHANNELS		_SIOR ('P', 6, पूर्णांक)
#घोषणा SOUND_PCM_READ_BITS		_SIOR ('P', 5, पूर्णांक)
#घोषणा SOUND_PCM_READ_FILTER		_SIOR ('P', 7, पूर्णांक)

/* Some alias names */
#घोषणा SOUND_PCM_WRITE_BITS		SNDCTL_DSP_SETFMT
#घोषणा SOUND_PCM_WRITE_RATE		SNDCTL_DSP_SPEED
#घोषणा SOUND_PCM_POST			SNDCTL_DSP_POST
#घोषणा SOUND_PCM_RESET			SNDCTL_DSP_RESET
#घोषणा SOUND_PCM_SYNC			SNDCTL_DSP_SYNC
#घोषणा SOUND_PCM_SUBDIVIDE		SNDCTL_DSP_SUBDIVIDE
#घोषणा SOUND_PCM_SETFRAGMENT		SNDCTL_DSP_SETFRAGMENT
#घोषणा SOUND_PCM_GETFMTS		SNDCTL_DSP_GETFMTS
#घोषणा SOUND_PCM_SETFMT		SNDCTL_DSP_SETFMT
#घोषणा SOUND_PCM_GETOSPACE		SNDCTL_DSP_GETOSPACE
#घोषणा SOUND_PCM_GETISPACE		SNDCTL_DSP_GETISPACE
#घोषणा SOUND_PCM_NONBLOCK		SNDCTL_DSP_NONBLOCK
#घोषणा SOUND_PCM_GETCAPS		SNDCTL_DSP_GETCAPS
#घोषणा SOUND_PCM_GETTRIGGER		SNDCTL_DSP_GETTRIGGER
#घोषणा SOUND_PCM_SETTRIGGER		SNDCTL_DSP_SETTRIGGER
#घोषणा SOUND_PCM_SETSYNCRO		SNDCTL_DSP_SETSYNCRO
#घोषणा SOUND_PCM_GETIPTR		SNDCTL_DSP_GETIPTR
#घोषणा SOUND_PCM_GETOPTR		SNDCTL_DSP_GETOPTR
#घोषणा SOUND_PCM_MAPINBUF		SNDCTL_DSP_MAPINBUF
#घोषणा SOUND_PCM_MAPOUTBUF		SNDCTL_DSP_MAPOUTBUF

/*
 * ioctl calls to be used in communication with coprocessors and
 * DSP chips.
 */

प्रकार काष्ठा copr_buffer अणु
		पूर्णांक command;	/* Set to 0 अगर not used */
		पूर्णांक flags;
#घोषणा CPF_NONE		0x0000
#घोषणा CPF_FIRST		0x0001	/* First block */
#घोषणा CPF_LAST		0x0002	/* Last block */
		पूर्णांक len;
		पूर्णांक offs;	/* If required by the device (0 अगर not used) */

		अचिन्हित अक्षर data[4000]; /* NOTE! 4000 is not 4k */
	पूर्ण copr_buffer;

प्रकार काष्ठा copr_debug_buf अणु
		पूर्णांक command;	/* Used पूर्णांकernally. Set to 0 */
		पूर्णांक parm1;
		पूर्णांक parm2;
		पूर्णांक flags;	
		पूर्णांक len;	/* Length of data in bytes */
	पूर्ण copr_debug_buf;

प्रकार काष्ठा copr_msg अणु
		पूर्णांक len;
		अचिन्हित अक्षर data[4000];
	पूर्ण copr_msg;

#घोषणा SNDCTL_COPR_RESET             _SIO  ('C',  0)
#घोषणा SNDCTL_COPR_LOAD	      _SIOWR('C',  1, copr_buffer)
#घोषणा SNDCTL_COPR_RDATA	      _SIOWR('C',  2, copr_debug_buf)
#घोषणा SNDCTL_COPR_RCODE	      _SIOWR('C',  3, copr_debug_buf)
#घोषणा SNDCTL_COPR_WDATA	      _SIOW ('C',  4, copr_debug_buf)
#घोषणा SNDCTL_COPR_WCODE	      _SIOW ('C',  5, copr_debug_buf)
#घोषणा SNDCTL_COPR_RUN		      _SIOWR('C',  6, copr_debug_buf)
#घोषणा SNDCTL_COPR_HALT	      _SIOWR('C',  7, copr_debug_buf)
#घोषणा SNDCTL_COPR_SENDMSG	      _SIOWR('C',  8, copr_msg)
#घोषणा SNDCTL_COPR_RCVMSG	      _SIOR ('C',  9, copr_msg)

/*********************************************
 * IOCTL commands क्रम /dev/mixer
 */
	
/* 
 * Mixer devices
 *
 * There can be up to 20 dअगरferent analog mixer channels. The
 * SOUND_MIXER_NRDEVICES gives the currently supported maximum. 
 * The SOUND_MIXER_READ_DEVMASK वापसs a biपंचांगask which tells
 * the devices supported by the particular mixer.
 */

#घोषणा SOUND_MIXER_NRDEVICES	25
#घोषणा SOUND_MIXER_VOLUME	0
#घोषणा SOUND_MIXER_BASS	1
#घोषणा SOUND_MIXER_TREBLE	2
#घोषणा SOUND_MIXER_SYNTH	3
#घोषणा SOUND_MIXER_PCM		4
#घोषणा SOUND_MIXER_SPEAKER	5
#घोषणा SOUND_MIXER_LINE	6
#घोषणा SOUND_MIXER_MIC		7
#घोषणा SOUND_MIXER_CD		8
#घोषणा SOUND_MIXER_IMIX	9	/*  Recording monitor  */
#घोषणा SOUND_MIXER_ALTPCM	10
#घोषणा SOUND_MIXER_RECLEV	11	/* Recording level */
#घोषणा SOUND_MIXER_IGAIN	12	/* Input gain */
#घोषणा SOUND_MIXER_OGAIN	13	/* Output gain */
/* 
 * The AD1848 codec and compatibles have three line level inमाला_दो
 * (line, aux1 and aux2). Since each card manufacturer have asचिन्हित
 * dअगरferent meanings to these inमाला_दो, it's inpractical to assign
 * specअगरic meanings (line, cd, synth etc.) to them.
 */
#घोषणा SOUND_MIXER_LINE1	14	/* Input source 1  (aux1) */
#घोषणा SOUND_MIXER_LINE2	15	/* Input source 2  (aux2) */
#घोषणा SOUND_MIXER_LINE3	16	/* Input source 3  (line) */
#घोषणा SOUND_MIXER_DIGITAL1	17	/* Digital (input) 1 */
#घोषणा SOUND_MIXER_DIGITAL2	18	/* Digital (input) 2 */
#घोषणा SOUND_MIXER_DIGITAL3	19	/* Digital (input) 3 */
#घोषणा SOUND_MIXER_PHONEIN	20	/* Phone input */
#घोषणा SOUND_MIXER_PHONEOUT	21	/* Phone output */
#घोषणा SOUND_MIXER_VIDEO	22	/* Video/TV (audio) in */
#घोषणा SOUND_MIXER_RADIO	23	/* Radio in */
#घोषणा SOUND_MIXER_MONITOR	24	/* Monitor (usually mic) volume */

/* Some on/off settings (SOUND_SPECIAL_MIN - SOUND_SPECIAL_MAX) */
/* Not counted to SOUND_MIXER_NRDEVICES, but use the same number space */
#घोषणा SOUND_ONOFF_MIN		28
#घोषणा SOUND_ONOFF_MAX		30

/* Note!	Number 31 cannot be used since the sign bit is reserved */
#घोषणा SOUND_MIXER_NONE	31

/*
 * The following unsupported macros are no दीर्घer functional.
 * Use SOUND_MIXER_PRIVATE# macros in future.
 */
#घोषणा SOUND_MIXER_ENHANCE	SOUND_MIXER_NONE
#घोषणा SOUND_MIXER_MUTE	SOUND_MIXER_NONE
#घोषणा SOUND_MIXER_LOUD	SOUND_MIXER_NONE


#घोषणा SOUND_DEVICE_LABELS	अणु"Vol  ", "Bass ", "Trebl", "Synth", "Pcm  ", "Spkr ", "Line ", \
				 "Mic  ", "CD   ", "Mix  ", "Pcm2 ", "Rec  ", "IGain", "OGain", \
				 "Line1", "Line2", "Line3", "Digital1", "Digital2", "Digital3", \
				 "PhoneIn", "PhoneOut", "Video", "Radio", "Monitor"पूर्ण

#घोषणा SOUND_DEVICE_NAMES	अणु"vol", "bass", "treble", "synth", "pcm", "speaker", "line", \
				 "mic", "cd", "mix", "pcm2", "rec", "igain", "ogain", \
				 "line1", "line2", "line3", "dig1", "dig2", "dig3", \
				 "phin", "phout", "video", "radio", "monitor"पूर्ण

/*	Device biपंचांगask identअगरiers	*/

#घोषणा SOUND_MIXER_RECSRC	0xff	/* Arg contains a bit क्रम each recording source */
#घोषणा SOUND_MIXER_DEVMASK	0xfe	/* Arg contains a bit क्रम each supported device */
#घोषणा SOUND_MIXER_RECMASK	0xfd	/* Arg contains a bit क्रम each supported recording source */
#घोषणा SOUND_MIXER_CAPS	0xfc
#	define SOUND_CAP_EXCL_INPUT	0x00000001	/* Only one recording source at a समय */
#घोषणा SOUND_MIXER_STEREODEVS	0xfb	/* Mixer channels supporting stereo */
#घोषणा SOUND_MIXER_OUTSRC	0xfa	/* Arg contains a bit क्रम each input source to output */
#घोषणा SOUND_MIXER_OUTMASK	0xf9	/* Arg contains a bit क्रम each supported input source to output */

/*	Device mask bits	*/

#घोषणा SOUND_MASK_VOLUME	(1 << SOUND_MIXER_VOLUME)
#घोषणा SOUND_MASK_BASS		(1 << SOUND_MIXER_BASS)
#घोषणा SOUND_MASK_TREBLE	(1 << SOUND_MIXER_TREBLE)
#घोषणा SOUND_MASK_SYNTH	(1 << SOUND_MIXER_SYNTH)
#घोषणा SOUND_MASK_PCM		(1 << SOUND_MIXER_PCM)
#घोषणा SOUND_MASK_SPEAKER	(1 << SOUND_MIXER_SPEAKER)
#घोषणा SOUND_MASK_LINE		(1 << SOUND_MIXER_LINE)
#घोषणा SOUND_MASK_MIC		(1 << SOUND_MIXER_MIC)
#घोषणा SOUND_MASK_CD		(1 << SOUND_MIXER_CD)
#घोषणा SOUND_MASK_IMIX		(1 << SOUND_MIXER_IMIX)
#घोषणा SOUND_MASK_ALTPCM	(1 << SOUND_MIXER_ALTPCM)
#घोषणा SOUND_MASK_RECLEV	(1 << SOUND_MIXER_RECLEV)
#घोषणा SOUND_MASK_IGAIN	(1 << SOUND_MIXER_IGAIN)
#घोषणा SOUND_MASK_OGAIN	(1 << SOUND_MIXER_OGAIN)
#घोषणा SOUND_MASK_LINE1	(1 << SOUND_MIXER_LINE1)
#घोषणा SOUND_MASK_LINE2	(1 << SOUND_MIXER_LINE2)
#घोषणा SOUND_MASK_LINE3	(1 << SOUND_MIXER_LINE3)
#घोषणा SOUND_MASK_DIGITAL1	(1 << SOUND_MIXER_DIGITAL1)
#घोषणा SOUND_MASK_DIGITAL2	(1 << SOUND_MIXER_DIGITAL2)
#घोषणा SOUND_MASK_DIGITAL3	(1 << SOUND_MIXER_DIGITAL3)
#घोषणा SOUND_MASK_PHONEIN	(1 << SOUND_MIXER_PHONEIN)
#घोषणा SOUND_MASK_PHONEOUT	(1 << SOUND_MIXER_PHONEOUT)
#घोषणा SOUND_MASK_RADIO	(1 << SOUND_MIXER_RADIO)
#घोषणा SOUND_MASK_VIDEO	(1 << SOUND_MIXER_VIDEO)
#घोषणा SOUND_MASK_MONITOR	(1 << SOUND_MIXER_MONITOR)

/* Obsolete macros */
#घोषणा SOUND_MASK_MUTE		(1 << SOUND_MIXER_MUTE)
#घोषणा SOUND_MASK_ENHANCE	(1 << SOUND_MIXER_ENHANCE)
#घोषणा SOUND_MASK_LOUD		(1 << SOUND_MIXER_LOUD)

#घोषणा MIXER_READ(dev)		_SIOR('M', dev, पूर्णांक)
#घोषणा SOUND_MIXER_READ_VOLUME		MIXER_READ(SOUND_MIXER_VOLUME)
#घोषणा SOUND_MIXER_READ_BASS		MIXER_READ(SOUND_MIXER_BASS)
#घोषणा SOUND_MIXER_READ_TREBLE		MIXER_READ(SOUND_MIXER_TREBLE)
#घोषणा SOUND_MIXER_READ_SYNTH		MIXER_READ(SOUND_MIXER_SYNTH)
#घोषणा SOUND_MIXER_READ_PCM		MIXER_READ(SOUND_MIXER_PCM)
#घोषणा SOUND_MIXER_READ_SPEAKER	MIXER_READ(SOUND_MIXER_SPEAKER)
#घोषणा SOUND_MIXER_READ_LINE		MIXER_READ(SOUND_MIXER_LINE)
#घोषणा SOUND_MIXER_READ_MIC		MIXER_READ(SOUND_MIXER_MIC)
#घोषणा SOUND_MIXER_READ_CD		MIXER_READ(SOUND_MIXER_CD)
#घोषणा SOUND_MIXER_READ_IMIX		MIXER_READ(SOUND_MIXER_IMIX)
#घोषणा SOUND_MIXER_READ_ALTPCM		MIXER_READ(SOUND_MIXER_ALTPCM)
#घोषणा SOUND_MIXER_READ_RECLEV		MIXER_READ(SOUND_MIXER_RECLEV)
#घोषणा SOUND_MIXER_READ_IGAIN		MIXER_READ(SOUND_MIXER_IGAIN)
#घोषणा SOUND_MIXER_READ_OGAIN		MIXER_READ(SOUND_MIXER_OGAIN)
#घोषणा SOUND_MIXER_READ_LINE1		MIXER_READ(SOUND_MIXER_LINE1)
#घोषणा SOUND_MIXER_READ_LINE2		MIXER_READ(SOUND_MIXER_LINE2)
#घोषणा SOUND_MIXER_READ_LINE3		MIXER_READ(SOUND_MIXER_LINE3)

/* Obsolete macros */
#घोषणा SOUND_MIXER_READ_MUTE		MIXER_READ(SOUND_MIXER_MUTE)
#घोषणा SOUND_MIXER_READ_ENHANCE	MIXER_READ(SOUND_MIXER_ENHANCE)
#घोषणा SOUND_MIXER_READ_LOUD		MIXER_READ(SOUND_MIXER_LOUD)

#घोषणा SOUND_MIXER_READ_RECSRC		MIXER_READ(SOUND_MIXER_RECSRC)
#घोषणा SOUND_MIXER_READ_DEVMASK	MIXER_READ(SOUND_MIXER_DEVMASK)
#घोषणा SOUND_MIXER_READ_RECMASK	MIXER_READ(SOUND_MIXER_RECMASK)
#घोषणा SOUND_MIXER_READ_STEREODEVS	MIXER_READ(SOUND_MIXER_STEREODEVS)
#घोषणा SOUND_MIXER_READ_CAPS		MIXER_READ(SOUND_MIXER_CAPS)

#घोषणा MIXER_WRITE(dev)		_SIOWR('M', dev, पूर्णांक)
#घोषणा SOUND_MIXER_WRITE_VOLUME	MIXER_WRITE(SOUND_MIXER_VOLUME)
#घोषणा SOUND_MIXER_WRITE_BASS		MIXER_WRITE(SOUND_MIXER_BASS)
#घोषणा SOUND_MIXER_WRITE_TREBLE	MIXER_WRITE(SOUND_MIXER_TREBLE)
#घोषणा SOUND_MIXER_WRITE_SYNTH		MIXER_WRITE(SOUND_MIXER_SYNTH)
#घोषणा SOUND_MIXER_WRITE_PCM		MIXER_WRITE(SOUND_MIXER_PCM)
#घोषणा SOUND_MIXER_WRITE_SPEAKER	MIXER_WRITE(SOUND_MIXER_SPEAKER)
#घोषणा SOUND_MIXER_WRITE_LINE		MIXER_WRITE(SOUND_MIXER_LINE)
#घोषणा SOUND_MIXER_WRITE_MIC		MIXER_WRITE(SOUND_MIXER_MIC)
#घोषणा SOUND_MIXER_WRITE_CD		MIXER_WRITE(SOUND_MIXER_CD)
#घोषणा SOUND_MIXER_WRITE_IMIX		MIXER_WRITE(SOUND_MIXER_IMIX)
#घोषणा SOUND_MIXER_WRITE_ALTPCM	MIXER_WRITE(SOUND_MIXER_ALTPCM)
#घोषणा SOUND_MIXER_WRITE_RECLEV	MIXER_WRITE(SOUND_MIXER_RECLEV)
#घोषणा SOUND_MIXER_WRITE_IGAIN		MIXER_WRITE(SOUND_MIXER_IGAIN)
#घोषणा SOUND_MIXER_WRITE_OGAIN		MIXER_WRITE(SOUND_MIXER_OGAIN)
#घोषणा SOUND_MIXER_WRITE_LINE1		MIXER_WRITE(SOUND_MIXER_LINE1)
#घोषणा SOUND_MIXER_WRITE_LINE2		MIXER_WRITE(SOUND_MIXER_LINE2)
#घोषणा SOUND_MIXER_WRITE_LINE3		MIXER_WRITE(SOUND_MIXER_LINE3)

/* Obsolete macros */
#घोषणा SOUND_MIXER_WRITE_MUTE		MIXER_WRITE(SOUND_MIXER_MUTE)
#घोषणा SOUND_MIXER_WRITE_ENHANCE	MIXER_WRITE(SOUND_MIXER_ENHANCE)
#घोषणा SOUND_MIXER_WRITE_LOUD		MIXER_WRITE(SOUND_MIXER_LOUD)

#घोषणा SOUND_MIXER_WRITE_RECSRC	MIXER_WRITE(SOUND_MIXER_RECSRC)

प्रकार काष्ठा mixer_info
अणु
  अक्षर id[16];
  अक्षर name[32];
  पूर्णांक  modअगरy_counter;
  पूर्णांक fillers[10];
पूर्ण mixer_info;

प्रकार काष्ठा _old_mixer_info /* Obsolete */
अणु
  अक्षर id[16];
  अक्षर name[32];
पूर्ण _old_mixer_info;

#घोषणा SOUND_MIXER_INFO		_SIOR ('M', 101, mixer_info)
#घोषणा SOUND_OLD_MIXER_INFO		_SIOR ('M', 101, _old_mixer_info)

/*
 * A mechanism क्रम accessing "proprietary" mixer features. This method
 * permits passing 128 bytes of arbitrary data between a mixer application
 * and the mixer driver. Interpretation of the record is defined by
 * the particular mixer driver.
 */
प्रकार अचिन्हित अक्षर mixer_record[128];

#घोषणा SOUND_MIXER_ACCESS		_SIOWR('M', 102, mixer_record)

/*
 * Two ioctls क्रम special souncard function
 */
#घोषणा SOUND_MIXER_AGC  _SIOWR('M', 103, पूर्णांक)
#घोषणा SOUND_MIXER_3DSE  _SIOWR('M', 104, पूर्णांक)

/*
 * The SOUND_MIXER_PRIVATE# commands can be redefined by low level drivers.
 * These features can be used when accessing device specअगरic features.
 */
#घोषणा SOUND_MIXER_PRIVATE1		_SIOWR('M', 111, पूर्णांक)
#घोषणा SOUND_MIXER_PRIVATE2		_SIOWR('M', 112, पूर्णांक)
#घोषणा SOUND_MIXER_PRIVATE3		_SIOWR('M', 113, पूर्णांक)
#घोषणा SOUND_MIXER_PRIVATE4		_SIOWR('M', 114, पूर्णांक)
#घोषणा SOUND_MIXER_PRIVATE5		_SIOWR('M', 115, पूर्णांक)

/*
 * SOUND_MIXER_GETLEVELS and SOUND_MIXER_SETLEVELS calls can be used
 * क्रम querying current mixer settings from the driver and क्रम loading
 * शेष volume settings _prior_ activating the mixer (loading
 * करोesn't affect current state of the mixer hardware). These calls
 * are क्रम पूर्णांकernal use only.
 */

प्रकार काष्ठा mixer_vol_table अणु
  पूर्णांक num;	/* Index to volume table */
  अक्षर name[32];
  पूर्णांक levels[32];
पूर्ण mixer_vol_table;

#घोषणा SOUND_MIXER_GETLEVELS		_SIOWR('M', 116, mixer_vol_table)
#घोषणा SOUND_MIXER_SETLEVELS		_SIOWR('M', 117, mixer_vol_table)

/* 
 * An ioctl क्रम identअगरying the driver version. It will वापस value
 * of the SOUND_VERSION macro used when compiling the driver.
 * This call was पूर्णांकroduced in OSS version 3.6 and it will not work
 * with earlier versions (वापसs EINVAL).
 */
#घोषणा OSS_GETVERSION			_SIOR ('M', 118, पूर्णांक)

/*
 * Level 2 event types क्रम /dev/sequencer
 */

/*
 * The 4 most signअगरicant bits of byte 0 specअगरy the class of
 * the event: 
 *
 *	0x8X = प्रणाली level events,
 *	0x9X = device/port specअगरic events, event[1] = device/port,
 *		The last 4 bits give the subtype:
 *			0x02	= Channel event (event[3] = chn).
 *			0x01	= note event (event[4] = note).
 *			(0x01 is not used alone but always with bit 0x02).
 *	       event[2] = MIDI message code (0x80=note off etc.)
 *
 */

#घोषणा EV_SEQ_LOCAL		0x80
#घोषणा EV_TIMING		0x81
#घोषणा EV_CHN_COMMON		0x92
#घोषणा EV_CHN_VOICE		0x93
#घोषणा EV_SYSEX		0x94
/*
 * Event types 200 to 220 are reserved क्रम application use.
 * These numbers will not be used by the driver.
 */

/*
 * Events क्रम event type EV_CHN_VOICE
 */

#घोषणा MIDI_NOTखातापूर्णF		0x80
#घोषणा MIDI_NOTEON		0x90
#घोषणा MIDI_KEY_PRESSURE	0xA0

/*
 * Events क्रम event type EV_CHN_COMMON
 */

#घोषणा MIDI_CTL_CHANGE		0xB0
#घोषणा MIDI_PGM_CHANGE		0xC0
#घोषणा MIDI_CHN_PRESSURE	0xD0
#घोषणा MIDI_PITCH_BEND		0xE0

#घोषणा MIDI_SYSTEM_PREFIX	0xF0

/*
 * Timer event types
 */
#घोषणा TMR_WAIT_REL		1	/* Time relative to the prev समय */
#घोषणा TMR_WAIT_ABS		2	/* Absolute समय since TMR_START */
#घोषणा TMR_STOP		3
#घोषणा TMR_START		4
#घोषणा TMR_CONTINUE		5
#घोषणा TMR_TEMPO		6
#घोषणा TMR_ECHO		8
#घोषणा TMR_CLOCK		9	/* MIDI घड़ी */
#घोषणा TMR_SPP			10	/* Song position poपूर्णांकer */
#घोषणा TMR_TIMESIG		11	/* Time signature */

/*
 *	Local event types
 */
#घोषणा LOCL_STARTAUDIO		1

#अगर !defined(__KERNEL__) || defined(USE_SEQ_MACROS)
/*
 *	Some convenience macros to simplअगरy programming of the
 *	/dev/sequencer पूर्णांकerface
 *
 *	This is a legacy पूर्णांकerface क्रम applications written against
 *	the OSSlib-3.8 style पूर्णांकerface. It is no दीर्घer possible
 *	to actually link against OSSlib with this header, but we
 *	still provide these macros क्रम programs using them.
 *
 *	If you want to use OSSlib, it is recommended that you get
 *	the GPL version of OSS-4.x and build against that version
 *	of the header.
 *
 *	We redefine the बाह्य keyword so that make headers_check
 *	करोes not complain about SEQ_USE_EXTBUF.
 */
#घोषणा SEQ_DECLAREBUF()		SEQ_USE_EXTBUF()

व्योम seqbuf_dump(व्योम);	/* This function must be provided by programs */

#घोषणा SEQ_PM_DEFINES पूर्णांक __foo_bar___

#घोषणा SEQ_LOAD_GMINSTR(dev, instr)
#घोषणा SEQ_LOAD_GMDRUM(dev, drum)

#घोषणा _SEQ_EXTERN बाह्य
#घोषणा SEQ_USE_EXTBUF() \
		_SEQ_EXTERN अचिन्हित अक्षर _seqbuf[]; \
		_SEQ_EXTERN पूर्णांक _seqbuflen; _SEQ_EXTERN पूर्णांक _seqbufptr

#अगर_अघोषित USE_SIMPLE_MACROS
/* Sample seqbuf_dump() implementation:
 *
 *	SEQ_DEFINEBUF (2048);	-- Defines a buffer क्रम 2048 bytes
 *
 *	पूर्णांक seqfd;		-- The file descriptor क्रम /dev/sequencer.
 *
 *	व्योम
 *	seqbuf_dump ()
 *	अणु
 *	  अगर (_seqbufptr)
 *	    अगर (ग_लिखो (seqfd, _seqbuf, _seqbufptr) == -1)
 *	      अणु
 *		लिखो_त्रुटि ("write /dev/sequencer");
 *		निकास (-1);
 *	      पूर्ण
 *	  _seqbufptr = 0;
 *	पूर्ण
 */

#घोषणा SEQ_DEFINEBUF(len)		अचिन्हित अक्षर _seqbuf[len]; पूर्णांक _seqbuflen = len;पूर्णांक _seqbufptr = 0
#घोषणा _SEQ_NEEDBUF(len)		अगर ((_seqbufptr+(len)) > _seqbuflen) seqbuf_dump()
#घोषणा _SEQ_ADVBUF(len)		_seqbufptr += len
#घोषणा SEQ_DUMPBUF			seqbuf_dump
#अन्यथा
/*
 * This variation of the sequencer macros is used just to क्रमmat one event
 * using fixed buffer.
 * 
 * The program using the macro library must define the following macros beक्रमe
 * using this library.
 *
 * #घोषणा _seqbuf 		 name of the buffer (अचिन्हित अक्षर[]) 
 * #घोषणा _SEQ_ADVBUF(len)	 If the applic needs to know the exact
 *				 size of the event, this macro can be used.
 *				 Otherwise this must be defined as empty.
 * #घोषणा _seqbufptr		 Define the name of index variable or 0 अगर
 *				 not required. 
 */
#घोषणा _SEQ_NEEDBUF(len)	/* empty */
#पूर्ण_अगर

#घोषणा SEQ_VOLUME_MODE(dev, mode)	अणु_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptr] = SEQ_EXTENDED;\
					_seqbuf[_seqbufptr+1] = SEQ_VOLMODE;\
					_seqbuf[_seqbufptr+2] = (dev);\
					_seqbuf[_seqbufptr+3] = (mode);\
					_seqbuf[_seqbufptr+4] = 0;\
					_seqbuf[_seqbufptr+5] = 0;\
					_seqbuf[_seqbufptr+6] = 0;\
					_seqbuf[_seqbufptr+7] = 0;\
					_SEQ_ADVBUF(8);पूर्ण

/*
 * Midi voice messages
 */

#घोषणा _CHN_VOICE(dev, event, chn, note, parm) \
					अणु_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptr] = EV_CHN_VOICE;\
					_seqbuf[_seqbufptr+1] = (dev);\
					_seqbuf[_seqbufptr+2] = (event);\
					_seqbuf[_seqbufptr+3] = (chn);\
					_seqbuf[_seqbufptr+4] = (note);\
					_seqbuf[_seqbufptr+5] = (parm);\
					_seqbuf[_seqbufptr+6] = (0);\
					_seqbuf[_seqbufptr+7] = 0;\
					_SEQ_ADVBUF(8);पूर्ण

#घोषणा SEQ_START_NOTE(dev, chn, note, vol) \
		_CHN_VOICE(dev, MIDI_NOTEON, chn, note, vol)

#घोषणा SEQ_STOP_NOTE(dev, chn, note, vol) \
		_CHN_VOICE(dev, MIDI_NOTखातापूर्णF, chn, note, vol)

#घोषणा SEQ_KEY_PRESSURE(dev, chn, note, pressure) \
		_CHN_VOICE(dev, MIDI_KEY_PRESSURE, chn, note, pressure)

/*
 * Midi channel messages
 */

#घोषणा _CHN_COMMON(dev, event, chn, p1, p2, w14) \
					अणु_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptr] = EV_CHN_COMMON;\
					_seqbuf[_seqbufptr+1] = (dev);\
					_seqbuf[_seqbufptr+2] = (event);\
					_seqbuf[_seqbufptr+3] = (chn);\
					_seqbuf[_seqbufptr+4] = (p1);\
					_seqbuf[_seqbufptr+5] = (p2);\
					*(लघु *)&_seqbuf[_seqbufptr+6] = (w14);\
					_SEQ_ADVBUF(8);पूर्ण
/*
 * SEQ_SYSEX permits sending of sysex messages. (It may look that it permits
 * sending any MIDI bytes but it's असलolutely not possible. Trying to करो
 * so _will_ cause problems with MPU401 पूर्णांकelligent mode).
 *
 * Sysex messages are sent in blocks of 1 to 6 bytes. Longer messages must be 
 * sent by calling SEQ_SYSEX() several बार (there must be no other events
 * between them). First sysex fragment must have 0xf0 in the first byte
 * and the last byte (buf[len-1] of the last fragment must be 0xf7. No byte
 * between these sysex start and end markers cannot be larger than 0x7f. Also
 * lengths of each fragments (except the last one) must be 6.
 *
 * Breaking the above rules may work with some MIDI ports but is likely to
 * cause fatal problems with some other devices (such as MPU401).
 */
#घोषणा SEQ_SYSEX(dev, buf, len) \
					अणुपूर्णांक ii, ll=(len); \
					 अचिन्हित अक्षर *bufp=buf;\
					 अगर (ll>6)ll=6;\
					_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptr] = EV_SYSEX;\
					_seqbuf[_seqbufptr+1] = (dev);\
					क्रम(ii=0;ii<ll;ii++)\
					   _seqbuf[_seqbufptr+ii+2] = bufp[ii];\
					क्रम(ii=ll;ii<6;ii++)\
					   _seqbuf[_seqbufptr+ii+2] = 0xff;\
					_SEQ_ADVBUF(8);पूर्ण

#घोषणा SEQ_CHN_PRESSURE(dev, chn, pressure) \
		_CHN_COMMON(dev, MIDI_CHN_PRESSURE, chn, pressure, 0, 0)

#घोषणा SEQ_SET_PATCH SEQ_PGM_CHANGE
#घोषणा SEQ_PGM_CHANGE(dev, chn, patch) \
		_CHN_COMMON(dev, MIDI_PGM_CHANGE, chn, patch, 0, 0)

#घोषणा SEQ_CONTROL(dev, chn, controller, value) \
		_CHN_COMMON(dev, MIDI_CTL_CHANGE, chn, controller, 0, value)

#घोषणा SEQ_BENDER(dev, chn, value) \
		_CHN_COMMON(dev, MIDI_PITCH_BEND, chn, 0, 0, value)


#घोषणा SEQ_V2_X_CONTROL(dev, voice, controller, value)	अणु_SEQ_NEEDBUF(8);\
					_seqbuf[_seqbufptr] = SEQ_EXTENDED;\
					_seqbuf[_seqbufptr+1] = SEQ_CONTROLLER;\
					_seqbuf[_seqbufptr+2] = (dev);\
					_seqbuf[_seqbufptr+3] = (voice);\
					_seqbuf[_seqbufptr+4] = (controller);\
					_seqbuf[_seqbufptr+5] = ((value)&0xff);\
					_seqbuf[_seqbufptr+6] = ((value>>8)&0xff);\
					_seqbuf[_seqbufptr+7] = 0;\
					_SEQ_ADVBUF(8);पूर्ण
/*
 * The following 5 macros are incorrectly implemented and obsolete.
 * Use SEQ_BENDER and SEQ_CONTROL (with proper controller) instead.
 */
#घोषणा SEQ_PITCHBEND(dev, voice, value) SEQ_V2_X_CONTROL(dev, voice, CTRL_PITCH_BENDER, value)
#घोषणा SEQ_BENDER_RANGE(dev, voice, value) SEQ_V2_X_CONTROL(dev, voice, CTRL_PITCH_BENDER_RANGE, value)
#घोषणा SEQ_EXPRESSION(dev, voice, value) SEQ_CONTROL(dev, voice, CTL_EXPRESSION, value*128)
#घोषणा SEQ_MAIN_VOLUME(dev, voice, value) SEQ_CONTROL(dev, voice, CTL_MAIN_VOLUME, (value*16383)/100)
#घोषणा SEQ_PANNING(dev, voice, pos) SEQ_CONTROL(dev, voice, CTL_PAN, (pos+128) / 2)

/*
 * Timing and synchronization macros
 */

#घोषणा _TIMER_EVENT(ev, parm)		अणु_SEQ_NEEDBUF(8);\
				 	_seqbuf[_seqbufptr+0] = EV_TIMING; \
				 	_seqbuf[_seqbufptr+1] = (ev); \
					_seqbuf[_seqbufptr+2] = 0;\
					_seqbuf[_seqbufptr+3] = 0;\
				 	*(अचिन्हित पूर्णांक *)&_seqbuf[_seqbufptr+4] = (parm); \
					_SEQ_ADVBUF(8);पूर्ण

#घोषणा SEQ_START_TIMER()		_TIMER_EVENT(TMR_START, 0)
#घोषणा SEQ_STOP_TIMER()		_TIMER_EVENT(TMR_STOP, 0)
#घोषणा SEQ_CONTINUE_TIMER()		_TIMER_EVENT(TMR_CONTINUE, 0)
#घोषणा SEQ_WAIT_TIME(ticks)		_TIMER_EVENT(TMR_WAIT_ABS, ticks)
#घोषणा SEQ_DELTA_TIME(ticks)		_TIMER_EVENT(TMR_WAIT_REL, ticks)
#घोषणा SEQ_ECHO_BACK(key)		_TIMER_EVENT(TMR_ECHO, key)
#घोषणा SEQ_SET_TEMPO(value)		_TIMER_EVENT(TMR_TEMPO, value)
#घोषणा SEQ_SONGPOS(pos)		_TIMER_EVENT(TMR_SPP, pos)
#घोषणा SEQ_TIME_SIGNATURE(sig)		_TIMER_EVENT(TMR_TIMESIG, sig)

/*
 * Local control events
 */

#घोषणा _LOCAL_EVENT(ev, parm)		अणु_SEQ_NEEDBUF(8);\
				 	_seqbuf[_seqbufptr+0] = EV_SEQ_LOCAL; \
				 	_seqbuf[_seqbufptr+1] = (ev); \
					_seqbuf[_seqbufptr+2] = 0;\
					_seqbuf[_seqbufptr+3] = 0;\
				 	*(अचिन्हित पूर्णांक *)&_seqbuf[_seqbufptr+4] = (parm); \
					_SEQ_ADVBUF(8);पूर्ण

#घोषणा SEQ_PLAYAUDIO(devmask)		_LOCAL_EVENT(LOCL_STARTAUDIO, devmask)
/*
 * Events क्रम the level 1 पूर्णांकerface only 
 */

#घोषणा SEQ_MIDIOUT(device, byte)	अणु_SEQ_NEEDBUF(4);\
					_seqbuf[_seqbufptr] = SEQ_MIDIPUTC;\
					_seqbuf[_seqbufptr+1] = (byte);\
					_seqbuf[_seqbufptr+2] = (device);\
					_seqbuf[_seqbufptr+3] = 0;\
					_SEQ_ADVBUF(4);पूर्ण

/*
 * Patch loading.
 */
#घोषणा SEQ_WRPATCH(patchx, len) \
		अणुअगर (_seqbufptr) SEQ_DUMPBUF();\
		 अगर (ग_लिखो(seqfd, (अक्षर*)(patchx), len)==-1) \
		    लिखो_त्रुटि("Write patch: /dev/sequencer");पूर्ण
#घोषणा SEQ_WRPATCH2(patchx, len) \
		(SEQ_DUMPBUF(), ग_लिखो(seqfd, (अक्षर*)(patchx), len))

#पूर्ण_अगर
#पूर्ण_अगर /* _UAPISOUNDCARD_H */
