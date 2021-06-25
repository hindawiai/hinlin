<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम DBRI sound chip found on Sparcs.
 * Copyright (C) 2004, 2005 Martin Habets (mhabets@users.sourceक्रमge.net)
 *
 * Converted to ring buffered version by Krzysztof Helt (krzysztof.h1@wp.pl)
 *
 * Based entirely upon drivers/sbus/audio/dbri.c which is:
 * Copyright (C) 1997 Ruकरोlf Koenig (rfkoenig@immd4.inक्रमmatik.uni-erlangen.de)
 * Copyright (C) 1998, 1999 Brent Baccala (baccala@मुक्तsoft.org)
 *
 * This is the low level driver क्रम the DBRI & MMCODEC duo used क्रम ISDN & AUDIO
 * on Sun SPARCStation 10, 20, LX and Voyager models.
 *
 * - DBRI: AT&T T5900FX Dual Basic Rates ISDN Interface. It is a 32 channel
 *   data समय multiplexer with ISDN support (aka T7259)
 *   Interfaces: SBus,ISDN NT & TE, CHI, 4 bits parallel.
 *   CHI: (spelled ki) Concentration Highway Interface (AT&T or Intel bus ?).
 *   Documentation:
 *   - "STP 4000SBus Dual Basic Rate ISDN (DBRI) Transceiver" from
 *     Sparc Technology Business (courtesy of Sun Support)
 *   - Data sheet of the T7903, a newer but very similar ISA bus equivalent
 *     available from the Lucent (क्रमmerly AT&T microelectronics) home
 *     page.
 *   - https://www.मुक्तsoft.org/Linux/DBRI/
 * - MMCODEC: Crystal Semiconductor CS4215 16 bit Mulसमयdia Audio Codec
 *   Interfaces: CHI, Audio In & Out, 2 bits parallel
 *   Documentation: from the Crystal Semiconductor home page.
 *
 * The DBRI is a 32 pipe machine, each pipe can transfer some bits between
 * memory and a serial device (दीर्घ pipes, no. 0-15) or between two serial
 * devices (लघु pipes, no. 16-31), or simply send a fixed data to a serial
 * device (लघु pipes).
 * A बारlot defines the bit-offset and no. of bits पढ़ो from a serial device.
 * The बारlots are linked to 6 circular lists, one क्रम each direction क्रम
 * each serial device (NT,TE,CHI). A बारlot is associated to 1 or 2 pipes
 * (the second one is a monitor/tee pipe, valid only क्रम serial input).
 *
 * The mmcodec is connected via the CHI bus and needs the data & some
 * parameters (volume, output selection) समय multiplexed in 8 byte
 * chunks. It also has a control mode, which serves क्रम audio क्रमmat setting.
 *
 * Looking at the CS4215 data sheet it is easy to set up 2 or 4 codecs on
 * the same CHI bus, so I thought perhaps it is possible to use the on-board
 * & the speakerbox codec simultaneously, giving 2 (not very independent :-)
 * audio devices. But the SUN HW group decided against it, at least on my
 * LX the speakerbox connector has at least 1 pin missing and 1 wrongly
 * connected.
 *
 * I've tried to stick to the following function naming conventions:
 * snd_*	ALSA stuff
 * cs4215_*	CS4215 codec specअगरic stuff
 * dbri_*	DBRI high-level stuff
 * other	DBRI low-level stuff
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gfp.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/initval.h>

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/atomic.h>
#समावेश <linux/module.h>

MODULE_AUTHOR("Rudolf Koenig, Brent Baccala and Martin Habets");
MODULE_DESCRIPTION("Sun DBRI");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
/* Enable this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Sun DBRI soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Sun DBRI soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Sun DBRI soundcard.");

#अघोषित DBRI_DEBUG

#घोषणा D_INT	(1<<0)
#घोषणा D_GEN	(1<<1)
#घोषणा D_CMD	(1<<2)
#घोषणा D_MM	(1<<3)
#घोषणा D_USR	(1<<4)
#घोषणा D_DESC	(1<<5)

अटल पूर्णांक dbri_debug;
module_param(dbri_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(dbri_debug, "Debug value for Sun DBRI soundcard.");

#अगर_घोषित DBRI_DEBUG
अटल स्थिर अक्षर * स्थिर cmds[] = अणु
	"WAIT", "PAUSE", "JUMP", "IIQ", "REX", "SDP", "CDP", "DTS",
	"SSP", "CHI", "NT", "TE", "CDEC", "TEST", "CDM", "RESRV"
पूर्ण;

#घोषणा dprपूर्णांकk(a, x...) अगर (dbri_debug & a) prपूर्णांकk(KERN_DEBUG x)

#अन्यथा
#घोषणा dprपूर्णांकk(a, x...) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर				/* DBRI_DEBUG */

#घोषणा DBRI_CMD(cmd, पूर्णांकr, value) ((cmd << 28) |	\
				    (पूर्णांकr << 27) |	\
				    value)

/***************************************************************************
	CS4215 specअगरic definitions and काष्ठाures
****************************************************************************/

काष्ठा cs4215 अणु
	__u8 data[4];		/* Data mode: Time slots 5-8 */
	__u8 ctrl[4];		/* Ctrl mode: Time slots 1-4 */
	__u8 onboard;
	__u8 offset;		/* Bit offset from frame sync to समय slot 1 */
	अस्थिर __u32 status;
	अस्थिर __u32 version;
	__u8 precision;		/* In bits, either 8 or 16 */
	__u8 channels;		/* 1 or 2 */
पूर्ण;

/*
 * Control mode first
 */

/* Time Slot 1, Status रेजिस्टर */
#घोषणा CS4215_CLB	(1<<2)	/* Control Latch Bit */
#घोषणा CS4215_OLB	(1<<3)	/* 1: line: 2.0V, speaker 4V */
				/* 0: line: 2.8V, speaker 8V */
#घोषणा CS4215_MLB	(1<<4)	/* 1: Microphone: 20dB gain disabled */
#घोषणा CS4215_RSRVD_1  (1<<5)

/* Time Slot 2, Data Format Register */
#घोषणा CS4215_DFR_LINEAR16	0
#घोषणा CS4215_DFR_ULAW		1
#घोषणा CS4215_DFR_ALAW		2
#घोषणा CS4215_DFR_LINEAR8	3
#घोषणा CS4215_DFR_STEREO	(1<<2)
अटल काष्ठा अणु
	अचिन्हित लघु freq;
	अचिन्हित अक्षर xtal;
	अचिन्हित अक्षर csval;
पूर्ण CS4215_FREQ[] = अणु
	अणु  8000, (1 << 4), (0 << 3) पूर्ण,
	अणु 16000, (1 << 4), (1 << 3) पूर्ण,
	अणु 27429, (1 << 4), (2 << 3) पूर्ण,	/* Actually 24428.57 */
	अणु 32000, (1 << 4), (3 << 3) पूर्ण,
     /* अणु    NA, (1 << 4), (4 << 3) पूर्ण, */
     /* अणु    NA, (1 << 4), (5 << 3) पूर्ण, */
	अणु 48000, (1 << 4), (6 << 3) पूर्ण,
	अणु  9600, (1 << 4), (7 << 3) पूर्ण,
	अणु  5512, (2 << 4), (0 << 3) पूर्ण,	/* Actually 5512.5 */
	अणु 11025, (2 << 4), (1 << 3) पूर्ण,
	अणु 18900, (2 << 4), (2 << 3) पूर्ण,
	अणु 22050, (2 << 4), (3 << 3) पूर्ण,
	अणु 37800, (2 << 4), (4 << 3) पूर्ण,
	अणु 44100, (2 << 4), (5 << 3) पूर्ण,
	अणु 33075, (2 << 4), (6 << 3) पूर्ण,
	अणु  6615, (2 << 4), (7 << 3) पूर्ण,
	अणु 0, 0, 0पूर्ण
पूर्ण;

#घोषणा CS4215_HPF	(1<<7)	/* High Pass Filter, 1: Enabled */

#घोषणा CS4215_12_MASK	0xfcbf	/* Mask off reserved bits in slot 1 & 2 */

/* Time Slot 3, Serial Port Control रेजिस्टर */
#घोषणा CS4215_XEN	(1<<0)	/* 0: Enable serial output */
#घोषणा CS4215_XCLK	(1<<1)	/* 1: Master mode: Generate SCLK */
#घोषणा CS4215_BSEL_64	(0<<2)	/* Bitrate: 64 bits per frame */
#घोषणा CS4215_BSEL_128	(1<<2)
#घोषणा CS4215_BSEL_256	(2<<2)
#घोषणा CS4215_MCK_MAST (0<<4)	/* Master घड़ी */
#घोषणा CS4215_MCK_XTL1 (1<<4)	/* 24.576 MHz घड़ी source */
#घोषणा CS4215_MCK_XTL2 (2<<4)	/* 16.9344 MHz घड़ी source */
#घोषणा CS4215_MCK_CLK1 (3<<4)	/* Clockin, 256 x Fs */
#घोषणा CS4215_MCK_CLK2 (4<<4)	/* Clockin, see DFR */

/* Time Slot 4, Test Register */
#घोषणा CS4215_DAD	(1<<0)	/* 0:Digital-Dig loop, 1:Dig-Analog-Dig loop */
#घोषणा CS4215_ENL	(1<<1)	/* Enable Loopback Testing */

/* Time Slot 5, Parallel Port Register */
/* Read only here and the same as the in data mode */

/* Time Slot 6, Reserved  */

/* Time Slot 7, Version Register  */
#घोषणा CS4215_VERSION_MASK 0xf	/* Known versions 0/C, 1/D, 2/E */

/* Time Slot 8, Reserved  */

/*
 * Data mode
 */
/* Time Slot 1-2: Left Channel Data, 2-3: Right Channel Data  */

/* Time Slot 5, Output Setting  */
#घोषणा CS4215_LO(v)	v	/* Left Output Attenuation 0x3f: -94.5 dB */
#घोषणा CS4215_LE	(1<<6)	/* Line Out Enable */
#घोषणा CS4215_HE	(1<<7)	/* Headphone Enable */

/* Time Slot 6, Output Setting  */
#घोषणा CS4215_RO(v)	v	/* Right Output Attenuation 0x3f: -94.5 dB */
#घोषणा CS4215_SE	(1<<6)	/* Speaker Enable */
#घोषणा CS4215_ADI	(1<<7)	/* A/D Data Invalid: Busy in calibration */

/* Time Slot 7, Input Setting */
#घोषणा CS4215_LG(v)	v	/* Left Gain Setting 0xf: 22.5 dB */
#घोषणा CS4215_IS	(1<<4)	/* Input Select: 1=Microphone, 0=Line */
#घोषणा CS4215_OVR	(1<<5)	/* 1: Over range condition occurred */
#घोषणा CS4215_PIO0	(1<<6)	/* Parallel I/O 0 */
#घोषणा CS4215_PIO1	(1<<7)

/* Time Slot 8, Input Setting */
#घोषणा CS4215_RG(v)	v	/* Right Gain Setting 0xf: 22.5 dB */
#घोषणा CS4215_MA(v)	(v<<4)	/* Monitor Path Attenuation 0xf: mute */

/***************************************************************************
		DBRI specअगरic definitions and काष्ठाures
****************************************************************************/

/* DBRI मुख्य रेजिस्टरs */
#घोषणा REG0	0x00		/* Status and Control */
#घोषणा REG1	0x04		/* Mode and Interrupt */
#घोषणा REG2	0x08		/* Parallel IO */
#घोषणा REG3	0x0c		/* Test */
#घोषणा REG8	0x20		/* Command Queue Poपूर्णांकer */
#घोषणा REG9	0x24		/* Interrupt Queue Poपूर्णांकer */

#घोषणा DBRI_NO_CMDS	64
#घोषणा DBRI_INT_BLK	64
#घोषणा DBRI_NO_DESCS	64
#घोषणा DBRI_NO_PIPES	32
#घोषणा DBRI_MAX_PIPE	(DBRI_NO_PIPES - 1)

#घोषणा DBRI_REC	0
#घोषणा DBRI_PLAY	1
#घोषणा DBRI_NO_STREAMS	2

/* One transmit/receive descriptor */
/* When ba != 0 descriptor is used */
काष्ठा dbri_mem अणु
	अस्थिर __u32 word1;
	__u32 ba;	/* Transmit/Receive Buffer Address */
	__u32 nda;	/* Next Descriptor Address */
	अस्थिर __u32 word4;
पूर्ण;

/* This काष्ठाure is in a DMA region where it can accessed by both
 * the CPU and the DBRI
 */
काष्ठा dbri_dma अणु
	s32 cmd[DBRI_NO_CMDS];			/* Place क्रम commands */
	अस्थिर s32 पूर्णांकr[DBRI_INT_BLK];	/* Interrupt field  */
	काष्ठा dbri_mem desc[DBRI_NO_DESCS];	/* Xmit/receive descriptors */
पूर्ण;

#घोषणा dbri_dma_off(member, elem)	\
	((u32)(अचिन्हित दीर्घ)		\
	 (&(((काष्ठा dbri_dma *)0)->member[elem])))

क्रमागत in_or_out अणु PIPEinput, PIPEoutput पूर्ण;

काष्ठा dbri_pipe अणु
	u32 sdp;		/* SDP command word */
	पूर्णांक nextpipe;		/* Next pipe in linked list */
	पूर्णांक length;		/* Length of बारlot (bits) */
	पूर्णांक first_desc;		/* Index of first descriptor */
	पूर्णांक desc;		/* Index of active descriptor */
	अस्थिर __u32 *recv_fixed_ptr;	/* Ptr to receive fixed data */
पूर्ण;

/* Per stream (playback or record) inक्रमmation */
काष्ठा dbri_streaminfo अणु
	काष्ठा snd_pcm_substream *substream;
	u32 dvma_buffer;	/* Device view of ALSA DMA buffer */
	पूर्णांक size;		/* Size of DMA buffer             */
	माप_प्रकार offset;		/* offset in user buffer          */
	पूर्णांक pipe;		/* Data pipe used                 */
	पूर्णांक left_gain;		/* mixer elements                 */
	पूर्णांक right_gain;
पूर्ण;

/* This काष्ठाure holds the inक्रमmation क्रम both chips (DBRI & CS4215) */
काष्ठा snd_dbri अणु
	पूर्णांक regs_size, irq;	/* Needed क्रम unload */
	काष्ठा platक्रमm_device *op;	/* OF device info */
	spinlock_t lock;

	काष्ठा dbri_dma *dma;	/* Poपूर्णांकer to our DMA block */
	dma_addr_t dma_dvma;	/* DBRI visible DMA address */

	व्योम __iomem *regs;	/* dbri HW regs */
	पूर्णांक dbri_irqp;		/* पूर्णांकr queue poपूर्णांकer */

	काष्ठा dbri_pipe pipes[DBRI_NO_PIPES];	/* DBRI's 32 data pipes */
	पूर्णांक next_desc[DBRI_NO_DESCS];		/* Index of next desc, or -1 */
	spinlock_t cmdlock;	/* Protects cmd queue accesses */
	s32 *cmdptr;		/* Poपूर्णांकer to the last queued cmd */

	पूर्णांक chi_bpf;

	काष्ठा cs4215 mm;	/* mmcodec special info */
				/* per stream (playback/record) info */
	काष्ठा dbri_streaminfo stream_info[DBRI_NO_STREAMS];
पूर्ण;

#घोषणा DBRI_MAX_VOLUME		63	/* Output volume */
#घोषणा DBRI_MAX_GAIN		15	/* Input gain */

/* DBRI Reg0 - Status Control Register - defines. (Page 17) */
#घोषणा D_P		(1<<15)	/* Program command & queue poपूर्णांकer valid */
#घोषणा D_G		(1<<14)	/* Allow 4-Word SBus Burst */
#घोषणा D_S		(1<<13)	/* Allow 16-Word SBus Burst */
#घोषणा D_E		(1<<12)	/* Allow 8-Word SBus Burst */
#घोषणा D_X		(1<<7)	/* Sanity Timer Disable */
#घोषणा D_T		(1<<6)	/* Permit activation of the TE पूर्णांकerface */
#घोषणा D_N		(1<<5)	/* Permit activation of the NT पूर्णांकerface */
#घोषणा D_C		(1<<4)	/* Permit activation of the CHI पूर्णांकerface */
#घोषणा D_F		(1<<3)	/* Force Sanity Timer Time-Out */
#घोषणा D_D		(1<<2)	/* Disable Master Mode */
#घोषणा D_H		(1<<1)	/* Halt क्रम Analysis */
#घोषणा D_R		(1<<0)	/* Soft Reset */

/* DBRI Reg1 - Mode and Interrupt Register - defines. (Page 18) */
#घोषणा D_LITTLE_END	(1<<8)	/* Byte Order */
#घोषणा D_BIG_END	(0<<8)	/* Byte Order */
#घोषणा D_MRR		(1<<4)	/* Multiple Error Ack on SBus (पढ़ो only) */
#घोषणा D_MLE		(1<<3)	/* Multiple Late Error on SBus (पढ़ो only) */
#घोषणा D_LBG		(1<<2)	/* Lost Bus Grant on SBus (पढ़ो only) */
#घोषणा D_MBE		(1<<1)	/* Burst Error on SBus (पढ़ो only) */
#घोषणा D_IR		(1<<0)	/* Interrupt Indicator (पढ़ो only) */

/* DBRI Reg2 - Parallel IO Register - defines. (Page 18) */
#घोषणा D_ENPIO3	(1<<7)	/* Enable Pin 3 */
#घोषणा D_ENPIO2	(1<<6)	/* Enable Pin 2 */
#घोषणा D_ENPIO1	(1<<5)	/* Enable Pin 1 */
#घोषणा D_ENPIO0	(1<<4)	/* Enable Pin 0 */
#घोषणा D_ENPIO		(0xf0)	/* Enable all the pins */
#घोषणा D_PIO3		(1<<3)	/* Pin 3: 1: Data mode, 0: Ctrl mode */
#घोषणा D_PIO2		(1<<2)	/* Pin 2: 1: Onboard PDN */
#घोषणा D_PIO1		(1<<1)	/* Pin 1: 0: Reset */
#घोषणा D_PIO0		(1<<0)	/* Pin 0: 1: Speakerbox PDN */

/* DBRI Commands (Page 20) */
#घोषणा D_WAIT		0x0	/* Stop execution */
#घोषणा D_PAUSE		0x1	/* Flush दीर्घ pipes */
#घोषणा D_JUMP		0x2	/* New command queue */
#घोषणा D_IIQ		0x3	/* Initialize Interrupt Queue */
#घोषणा D_REX		0x4	/* Report command execution via पूर्णांकerrupt */
#घोषणा D_SDP		0x5	/* Setup Data Pipe */
#घोषणा D_CDP		0x6	/* Continue Data Pipe (reपढ़ो शून्य Poपूर्णांकer) */
#घोषणा D_DTS		0x7	/* Define Time Slot */
#घोषणा D_SSP		0x8	/* Set लघु Data Pipe */
#घोषणा D_CHI		0x9	/* Set CHI Global Mode */
#घोषणा D_NT		0xa	/* NT Command */
#घोषणा D_TE		0xb	/* TE Command */
#घोषणा D_CDEC		0xc	/* Codec setup */
#घोषणा D_TEST		0xd	/* No comment */
#घोषणा D_CDM		0xe	/* CHI Data mode command */

/* Special bits क्रम some commands */
#घोषणा D_PIPE(v)      ((v)<<0)	/* Pipe No.: 0-15 दीर्घ, 16-21 लघु */

/* Setup Data Pipe */
/* IRM */
#घोषणा D_SDP_2SAME	(1<<18)	/* Report 2nd समय in a row value received */
#घोषणा D_SDP_CHANGE	(2<<18)	/* Report any changes */
#घोषणा D_SDP_EVERY	(3<<18)	/* Report any changes */
#घोषणा D_SDP_EOL	(1<<17)	/* EOL पूर्णांकerrupt enable */
#घोषणा D_SDP_IDLE	(1<<16)	/* HDLC idle पूर्णांकerrupt enable */

/* Pipe data MODE */
#घोषणा D_SDP_MEM	(0<<13)	/* To/from memory */
#घोषणा D_SDP_HDLC	(2<<13)
#घोषणा D_SDP_HDLC_D	(3<<13)	/* D Channel (prio control) */
#घोषणा D_SDP_SER	(4<<13)	/* Serial to serial */
#घोषणा D_SDP_FIXED	(6<<13)	/* Short only */
#घोषणा D_SDP_MODE(v)	((v)&(7<<13))

#घोषणा D_SDP_TO_SER	(1<<12)	/* Direction */
#घोषणा D_SDP_FROM_SER	(0<<12)	/* Direction */
#घोषणा D_SDP_MSB	(1<<11)	/* Bit order within Byte */
#घोषणा D_SDP_LSB	(0<<11)	/* Bit order within Byte */
#घोषणा D_SDP_P		(1<<10)	/* Poपूर्णांकer Valid */
#घोषणा D_SDP_A		(1<<8)	/* Abort */
#घोषणा D_SDP_C		(1<<7)	/* Clear */

/* Define Time Slot */
#घोषणा D_DTS_VI	(1<<17)	/* Valid Input Time-Slot Descriptor */
#घोषणा D_DTS_VO	(1<<16)	/* Valid Output Time-Slot Descriptor */
#घोषणा D_DTS_INS	(1<<15)	/* Insert Time Slot */
#घोषणा D_DTS_DEL	(0<<15)	/* Delete Time Slot */
#घोषणा D_DTS_PRVIN(v) ((v)<<10)	/* Previous In Pipe */
#घोषणा D_DTS_PRVOUT(v)        ((v)<<5)	/* Previous Out Pipe */

/* Time Slot defines */
#घोषणा D_TS_LEN(v)	((v)<<24)	/* Number of bits in this समय slot */
#घोषणा D_TS_CYCLE(v)	((v)<<14)	/* Bit Count at start of TS */
#घोषणा D_TS_DI		(1<<13)	/* Data Invert */
#घोषणा D_TS_1CHANNEL	(0<<10)	/* Single Channel / Normal mode */
#घोषणा D_TS_MONITOR	(2<<10)	/* Monitor pipe */
#घोषणा D_TS_NONCONTIG	(3<<10)	/* Non contiguous mode */
#घोषणा D_TS_ANCHOR	(7<<10)	/* Starting लघु pipes */
#घोषणा D_TS_MON(v)    ((v)<<5)	/* Monitor Pipe */
#घोषणा D_TS_NEXT(v)   ((v)<<0)	/* Pipe no.: 0-15 दीर्घ, 16-21 लघु */

/* Concentration Highway Interface Modes */
#घोषणा D_CHI_CHICM(v)	((v)<<16)	/* Clock mode */
#घोषणा D_CHI_IR	(1<<15)	/* Immediate Interrupt Report */
#घोषणा D_CHI_EN	(1<<14)	/* CHIL Interrupt enabled */
#घोषणा D_CHI_OD	(1<<13)	/* Open Drain Enable */
#घोषणा D_CHI_FE	(1<<12)	/* Sample CHIFS on Rising Frame Edge */
#घोषणा D_CHI_FD	(1<<11)	/* Frame Drive */
#घोषणा D_CHI_BPF(v)	((v)<<0)	/* Bits per Frame */

/* NT: These are here क्रम completeness */
#घोषणा D_NT_FBIT	(1<<17)	/* Frame Bit */
#घोषणा D_NT_NBF	(1<<16)	/* Number of bad frames to loose framing */
#घोषणा D_NT_IRM_IMM	(1<<15)	/* Interrupt Report & Mask: Immediate */
#घोषणा D_NT_IRM_EN	(1<<14)	/* Interrupt Report & Mask: Enable */
#घोषणा D_NT_ISNT	(1<<13)	/* Configure पूर्णांकerface as NT */
#घोषणा D_NT_FT		(1<<12)	/* Fixed Timing */
#घोषणा D_NT_EZ		(1<<11)	/* Echo Channel is Zeros */
#घोषणा D_NT_IFA	(1<<10)	/* Inhibit Final Activation */
#घोषणा D_NT_ACT	(1<<9)	/* Activate Interface */
#घोषणा D_NT_MFE	(1<<8)	/* Multअगरrame Enable */
#घोषणा D_NT_RLB(v)	((v)<<5)	/* Remote Loopback */
#घोषणा D_NT_LLB(v)	((v)<<2)	/* Local Loopback */
#घोषणा D_NT_FACT	(1<<1)	/* Force Activation */
#घोषणा D_NT_ABV	(1<<0)	/* Activate Bipolar Violation */

/* Codec Setup */
#घोषणा D_CDEC_CK(v)	((v)<<24)	/* Clock Select */
#घोषणा D_CDEC_FED(v)	((v)<<12)	/* FSCOD Falling Edge Delay */
#घोषणा D_CDEC_RED(v)	((v)<<0)	/* FSCOD Rising Edge Delay */

/* Test */
#घोषणा D_TEST_RAM(v)	((v)<<16)	/* RAM Poपूर्णांकer */
#घोषणा D_TEST_SIZE(v)	((v)<<11)	/* */
#घोषणा D_TEST_ROMONOFF	0x5	/* Toggle ROM opcode monitor on/off */
#घोषणा D_TEST_PROC	0x6	/* Microprocessor test */
#घोषणा D_TEST_SER	0x7	/* Serial-Controller test */
#घोषणा D_TEST_RAMREAD	0x8	/* Copy from Ram to प्रणाली memory */
#घोषणा D_TEST_RAMWRITE	0x9	/* Copy पूर्णांकo Ram from प्रणाली memory */
#घोषणा D_TEST_RAMBIST	0xa	/* RAM Built-In Self Test */
#घोषणा D_TEST_MCBIST	0xb	/* Microcontroller Built-In Self Test */
#घोषणा D_TEST_DUMP	0xe	/* ROM Dump */

/* CHI Data Mode */
#घोषणा D_CDM_THI	(1 << 8)	/* Transmit Data on CHIDR Pin */
#घोषणा D_CDM_RHI	(1 << 7)	/* Receive Data on CHIDX Pin */
#घोषणा D_CDM_RCE	(1 << 6)	/* Receive on Rising Edge of CHICK */
#घोषणा D_CDM_XCE	(1 << 2) /* Transmit Data on Rising Edge of CHICK */
#घोषणा D_CDM_XEN	(1 << 1)	/* Transmit Highway Enable */
#घोषणा D_CDM_REN	(1 << 0)	/* Receive Highway Enable */

/* The Interrupts */
#घोषणा D_INTR_BRDY	1	/* Buffer Ready क्रम processing */
#घोषणा D_INTR_MINT	2	/* Marked Interrupt in RD/TD */
#घोषणा D_INTR_IBEG	3	/* Flag to idle transition detected (HDLC) */
#घोषणा D_INTR_IEND	4	/* Idle to flag transition detected (HDLC) */
#घोषणा D_INTR_EOL	5	/* End of List */
#घोषणा D_INTR_CMDI	6	/* Command has bean पढ़ो */
#घोषणा D_INTR_XCMP	8	/* Transmission of frame complete */
#घोषणा D_INTR_SBRI	9	/* BRI status change info */
#घोषणा D_INTR_FXDT	10	/* Fixed data change */
#घोषणा D_INTR_CHIL	11	/* CHI lost frame sync (channel 36 only) */
#घोषणा D_INTR_COLL	11	/* Unrecoverable D-Channel collision */
#घोषणा D_INTR_DBYT	12	/* Dropped by frame slip */
#घोषणा D_INTR_RBYT	13	/* Repeated by frame slip */
#घोषणा D_INTR_LINT	14	/* Lost Interrupt */
#घोषणा D_INTR_UNDR	15	/* DMA underrun */

#घोषणा D_INTR_TE	32
#घोषणा D_INTR_NT	34
#घोषणा D_INTR_CHI	36
#घोषणा D_INTR_CMD	38

#घोषणा D_INTR_GETCHAN(v)	(((v) >> 24) & 0x3f)
#घोषणा D_INTR_GETCODE(v)	(((v) >> 20) & 0xf)
#घोषणा D_INTR_GETCMD(v)	(((v) >> 16) & 0xf)
#घोषणा D_INTR_GETVAL(v)	((v) & 0xffff)
#घोषणा D_INTR_GETRVAL(v)	((v) & 0xfffff)

#घोषणा D_P_0		0	/* TE receive anchor */
#घोषणा D_P_1		1	/* TE transmit anchor */
#घोषणा D_P_2		2	/* NT transmit anchor */
#घोषणा D_P_3		3	/* NT receive anchor */
#घोषणा D_P_4		4	/* CHI send data */
#घोषणा D_P_5		5	/* CHI receive data */
#घोषणा D_P_6		6	/* */
#घोषणा D_P_7		7	/* */
#घोषणा D_P_8		8	/* */
#घोषणा D_P_9		9	/* */
#घोषणा D_P_10		10	/* */
#घोषणा D_P_11		11	/* */
#घोषणा D_P_12		12	/* */
#घोषणा D_P_13		13	/* */
#घोषणा D_P_14		14	/* */
#घोषणा D_P_15		15	/* */
#घोषणा D_P_16		16	/* CHI anchor pipe */
#घोषणा D_P_17		17	/* CHI send */
#घोषणा D_P_18		18	/* CHI receive */
#घोषणा D_P_19		19	/* CHI receive */
#घोषणा D_P_20		20	/* CHI receive */
#घोषणा D_P_21		21	/* */
#घोषणा D_P_22		22	/* */
#घोषणा D_P_23		23	/* */
#घोषणा D_P_24		24	/* */
#घोषणा D_P_25		25	/* */
#घोषणा D_P_26		26	/* */
#घोषणा D_P_27		27	/* */
#घोषणा D_P_28		28	/* */
#घोषणा D_P_29		29	/* */
#घोषणा D_P_30		30	/* */
#घोषणा D_P_31		31	/* */

/* Transmit descriptor defines */
#घोषणा DBRI_TD_F	(1 << 31)	/* End of Frame */
#घोषणा DBRI_TD_D	(1 << 30)	/* Do not append CRC */
#घोषणा DBRI_TD_CNT(v)	((v) << 16) /* Number of valid bytes in the buffer */
#घोषणा DBRI_TD_B	(1 << 15)	/* Final पूर्णांकerrupt */
#घोषणा DBRI_TD_M	(1 << 14)	/* Marker पूर्णांकerrupt */
#घोषणा DBRI_TD_I	(1 << 13)	/* Transmit Idle Characters */
#घोषणा DBRI_TD_FCNT(v)	(v)		/* Flag Count */
#घोषणा DBRI_TD_UNR	(1 << 3) /* Underrun: transmitter is out of data */
#घोषणा DBRI_TD_ABT	(1 << 2)	/* Abort: frame पातed */
#घोषणा DBRI_TD_TBC	(1 << 0)	/* Transmit buffer Complete */
#घोषणा DBRI_TD_STATUS(v)       ((v) & 0xff)	/* Transmit status */
			/* Maximum buffer size per TD: almost 8KB */
#घोषणा DBRI_TD_MAXCNT	((1 << 13) - 4)

/* Receive descriptor defines */
#घोषणा DBRI_RD_F	(1 << 31)	/* End of Frame */
#घोषणा DBRI_RD_C	(1 << 30)	/* Completed buffer */
#घोषणा DBRI_RD_B	(1 << 15)	/* Final पूर्णांकerrupt */
#घोषणा DBRI_RD_M	(1 << 14)	/* Marker पूर्णांकerrupt */
#घोषणा DBRI_RD_BCNT(v)	(v)		/* Buffer size */
#घोषणा DBRI_RD_CRC	(1 << 7)	/* 0: CRC is correct */
#घोषणा DBRI_RD_BBC	(1 << 6)	/* 1: Bad Byte received */
#घोषणा DBRI_RD_ABT	(1 << 5)	/* Abort: frame पातed */
#घोषणा DBRI_RD_OVRN	(1 << 3)	/* Overrun: data lost */
#घोषणा DBRI_RD_STATUS(v)      ((v) & 0xff)	/* Receive status */
#घोषणा DBRI_RD_CNT(v) (((v) >> 16) & 0x1fff)	/* Valid bytes in the buffer */

/* stream_info[] access */
/* Translate the ALSA direction पूर्णांकo the array index */
#घोषणा DBRI_STREAMNO(substream)				\
		(substream->stream ==				\
		 SNDRV_PCM_STREAM_PLAYBACK ? DBRI_PLAY: DBRI_REC)

/* Return a poपूर्णांकer to dbri_streaminfo */
#घोषणा DBRI_STREAM(dbri, substream)	\
		&dbri->stream_info[DBRI_STREAMNO(substream)]

/*
 * Short data pipes transmit LSB first. The CS4215 receives MSB first. Grrr.
 * So we have to reverse the bits. Note: not all bit lengths are supported
 */
अटल __u32 reverse_bytes(__u32 b, पूर्णांक len)
अणु
	चयन (len) अणु
	हाल 32:
		b = ((b & 0xffff0000) >> 16) | ((b & 0x0000ffff) << 16);
		fallthrough;
	हाल 16:
		b = ((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8);
		fallthrough;
	हाल 8:
		b = ((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4);
		fallthrough;
	हाल 4:
		b = ((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2);
		fallthrough;
	हाल 2:
		b = ((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1);
	हाल 1:
	हाल 0:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "DBRI reverse_bytes: unsupported length\n");
	पूर्ण

	वापस b;
पूर्ण

/*
****************************************************************************
************** DBRI initialization and command synchronization *************
****************************************************************************

Commands are sent to the DBRI by building a list of them in memory,
then writing the address of the first list item to DBRI रेजिस्टर 8.
The list is terminated with a WAIT command, which generates a
CPU पूर्णांकerrupt to संकेत completion.

Since the DBRI can run in parallel with the CPU, several means of
synchronization present themselves. The method implemented here uses
the dbri_cmdरुको() to रुको क्रम execution of batch of sent commands.

A circular command buffer is used here. A new command is being added
जबतक another can be executed. The scheme works by adding two WAIT commands
after each sent batch of commands. When the next batch is prepared it is
added after the WAIT commands then the WAITs are replaced with single JUMP
command to the new batch. Then the DBRI is क्रमced to reपढ़ो the last WAIT
command (replaced by the JUMP by then). If the DBRI is still executing
previous commands the request to reपढ़ो the WAIT command is ignored.

Every समय a routine wants to ग_लिखो commands to the DBRI, it must
first call dbri_cmdlock() and get poपूर्णांकer to a मुक्त space in
dbri->dma->cmd buffer. After this, the commands can be written to
the buffer, and dbri_cmdsend() is called with the final poपूर्णांकer value
to send them to the DBRI.

*/

#घोषणा MAXLOOPS 20
/*
 * Wait क्रम the current command string to execute
 */
अटल व्योम dbri_cmdरुको(काष्ठा snd_dbri *dbri)
अणु
	पूर्णांक maxloops = MAXLOOPS;
	अचिन्हित दीर्घ flags;

	/* Delay अगर previous commands are still being processed */
	spin_lock_irqsave(&dbri->lock, flags);
	जबतक ((--maxloops) > 0 && (sbus_पढ़ोl(dbri->regs + REG0) & D_P)) अणु
		spin_unlock_irqrestore(&dbri->lock, flags);
		msleep_पूर्णांकerruptible(1);
		spin_lock_irqsave(&dbri->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&dbri->lock, flags);

	अगर (maxloops == 0)
		prपूर्णांकk(KERN_ERR "DBRI: Chip never completed command buffer\n");
	अन्यथा
		dprपूर्णांकk(D_CMD, "Chip completed command buffer (%d)\n",
			MAXLOOPS - maxloops - 1);
पूर्ण
/*
 * Lock the command queue and वापस poपूर्णांकer to space क्रम len cmd words
 * It locks the cmdlock spinlock.
 */
अटल s32 *dbri_cmdlock(काष्ठा snd_dbri *dbri, पूर्णांक len)
अणु
	u32 dvma_addr = (u32)dbri->dma_dvma;

	/* Space क्रम 2 WAIT cmds (replaced later by 1 JUMP cmd) */
	len += 2;
	spin_lock(&dbri->cmdlock);
	अगर (dbri->cmdptr - dbri->dma->cmd + len < DBRI_NO_CMDS - 2)
		वापस dbri->cmdptr + 2;
	अन्यथा अगर (len < sbus_पढ़ोl(dbri->regs + REG8) - dvma_addr)
		वापस dbri->dma->cmd;
	अन्यथा
		prपूर्णांकk(KERN_ERR "DBRI: no space for commands.");

	वापस शून्य;
पूर्ण

/*
 * Send prepared cmd string. It works by writing a JUMP cmd पूर्णांकo
 * the last WAIT cmd and क्रमce DBRI to reपढ़ो the cmd.
 * The JUMP cmd poपूर्णांकs to the new cmd string.
 * It also releases the cmdlock spinlock.
 *
 * Lock must be held beक्रमe calling this.
 */
अटल व्योम dbri_cmdsend(काष्ठा snd_dbri *dbri, s32 *cmd, पूर्णांक len)
अणु
	u32 dvma_addr = (u32)dbri->dma_dvma;
	s32 पंचांगp, addr;
	अटल पूर्णांक रुको_id = 0;

	रुको_id++;
	रुको_id &= 0xffff;	/* restrict it to a 16 bit counter. */
	*(cmd) = DBRI_CMD(D_WAIT, 1, रुको_id);
	*(cmd+1) = DBRI_CMD(D_WAIT, 1, रुको_id);

	/* Replace the last command with JUMP */
	addr = dvma_addr + (cmd - len - dbri->dma->cmd) * माप(s32);
	*(dbri->cmdptr+1) = addr;
	*(dbri->cmdptr) = DBRI_CMD(D_JUMP, 0, 0);

#अगर_घोषित DBRI_DEBUG
	अगर (cmd > dbri->cmdptr) अणु
		s32 *ptr;

		क्रम (ptr = dbri->cmdptr; ptr < cmd+2; ptr++)
			dprपूर्णांकk(D_CMD, "cmd: %lx:%08x\n",
				(अचिन्हित दीर्घ)ptr, *ptr);
	पूर्ण अन्यथा अणु
		s32 *ptr = dbri->cmdptr;

		dprपूर्णांकk(D_CMD, "cmd: %lx:%08x\n", (अचिन्हित दीर्घ)ptr, *ptr);
		ptr++;
		dprपूर्णांकk(D_CMD, "cmd: %lx:%08x\n", (अचिन्हित दीर्घ)ptr, *ptr);
		क्रम (ptr = dbri->dma->cmd; ptr < cmd+2; ptr++)
			dprपूर्णांकk(D_CMD, "cmd: %lx:%08x\n",
				(अचिन्हित दीर्घ)ptr, *ptr);
	पूर्ण
#पूर्ण_अगर

	/* Reपढ़ो the last command */
	पंचांगp = sbus_पढ़ोl(dbri->regs + REG0);
	पंचांगp |= D_P;
	sbus_ग_लिखोl(पंचांगp, dbri->regs + REG0);

	dbri->cmdptr = cmd;
	spin_unlock(&dbri->cmdlock);
पूर्ण

/* Lock must be held when calling this */
अटल व्योम dbri_reset(काष्ठा snd_dbri *dbri)
अणु
	पूर्णांक i;
	u32 पंचांगp;

	dprपूर्णांकk(D_GEN, "reset 0:%x 2:%x 8:%x 9:%x\n",
		sbus_पढ़ोl(dbri->regs + REG0),
		sbus_पढ़ोl(dbri->regs + REG2),
		sbus_पढ़ोl(dbri->regs + REG8), sbus_पढ़ोl(dbri->regs + REG9));

	sbus_ग_लिखोl(D_R, dbri->regs + REG0);	/* Soft Reset */
	क्रम (i = 0; (sbus_पढ़ोl(dbri->regs + REG0) & D_R) && i < 64; i++)
		udelay(10);

	/* A brute approach - DBRI falls back to working burst size by itself
	 * On SS20 D_S करोes not work, so करो not try so high. */
	पंचांगp = sbus_पढ़ोl(dbri->regs + REG0);
	पंचांगp |= D_G | D_E;
	पंचांगp &= ~D_S;
	sbus_ग_लिखोl(पंचांगp, dbri->regs + REG0);
पूर्ण

/* Lock must not be held beक्रमe calling this */
अटल व्योम dbri_initialize(काष्ठा snd_dbri *dbri)
अणु
	u32 dvma_addr = (u32)dbri->dma_dvma;
	s32 *cmd;
	u32 dma_addr;
	अचिन्हित दीर्घ flags;
	पूर्णांक n;

	spin_lock_irqsave(&dbri->lock, flags);

	dbri_reset(dbri);

	/* Initialize pipes */
	क्रम (n = 0; n < DBRI_NO_PIPES; n++)
		dbri->pipes[n].desc = dbri->pipes[n].first_desc = -1;

	spin_lock_init(&dbri->cmdlock);
	/*
	 * Initialize the पूर्णांकerrupt ring buffer.
	 */
	dma_addr = dvma_addr + dbri_dma_off(पूर्णांकr, 0);
	dbri->dma->पूर्णांकr[0] = dma_addr;
	dbri->dbri_irqp = 1;
	/*
	 * Set up the पूर्णांकerrupt queue
	 */
	spin_lock(&dbri->cmdlock);
	cmd = dbri->cmdptr = dbri->dma->cmd;
	*(cmd++) = DBRI_CMD(D_IIQ, 0, 0);
	*(cmd++) = dma_addr;
	*(cmd++) = DBRI_CMD(D_PAUSE, 0, 0);
	dbri->cmdptr = cmd;
	*(cmd++) = DBRI_CMD(D_WAIT, 1, 0);
	*(cmd++) = DBRI_CMD(D_WAIT, 1, 0);
	dma_addr = dvma_addr + dbri_dma_off(cmd, 0);
	sbus_ग_लिखोl(dma_addr, dbri->regs + REG8);
	spin_unlock(&dbri->cmdlock);

	spin_unlock_irqrestore(&dbri->lock, flags);
	dbri_cmdरुको(dbri);
पूर्ण

/*
****************************************************************************
************************** DBRI data pipe management ***********************
****************************************************************************

While DBRI control functions use the command and पूर्णांकerrupt buffers, the
मुख्य data path takes the क्रमm of data pipes, which can be लघु (command
and पूर्णांकerrupt driven), or दीर्घ (attached to DMA buffers).  These functions
provide a rudimentary means of setting up and managing the DBRI's pipes,
but the calling functions have to make sure they respect the pipes' linked
list ordering, among other things.  The transmit and receive functions
here पूर्णांकerface बंदly with the transmit and receive पूर्णांकerrupt code.

*/
अटल अंतरभूत पूर्णांक pipe_active(काष्ठा snd_dbri *dbri, पूर्णांक pipe)
अणु
	वापस ((pipe >= 0) && (dbri->pipes[pipe].desc != -1));
पूर्ण

/* reset_pipe(dbri, pipe)
 *
 * Called on an in-use pipe to clear anything being transmitted or received
 * Lock must be held beक्रमe calling this.
 */
अटल व्योम reset_pipe(काष्ठा snd_dbri *dbri, पूर्णांक pipe)
अणु
	पूर्णांक sdp;
	पूर्णांक desc;
	s32 *cmd;

	अगर (pipe < 0 || pipe > DBRI_MAX_PIPE) अणु
		prपूर्णांकk(KERN_ERR "DBRI: reset_pipe called with "
			"illegal pipe number\n");
		वापस;
	पूर्ण

	sdp = dbri->pipes[pipe].sdp;
	अगर (sdp == 0) अणु
		prपूर्णांकk(KERN_ERR "DBRI: reset_pipe called "
			"on uninitialized pipe\n");
		वापस;
	पूर्ण

	cmd = dbri_cmdlock(dbri, 3);
	*(cmd++) = DBRI_CMD(D_SDP, 0, sdp | D_SDP_C | D_SDP_P);
	*(cmd++) = 0;
	*(cmd++) = DBRI_CMD(D_PAUSE, 0, 0);
	dbri_cmdsend(dbri, cmd, 3);

	desc = dbri->pipes[pipe].first_desc;
	अगर (desc >= 0)
		करो अणु
			dbri->dma->desc[desc].ba = 0;
			dbri->dma->desc[desc].nda = 0;
			desc = dbri->next_desc[desc];
		पूर्ण जबतक (desc != -1 && desc != dbri->pipes[pipe].first_desc);

	dbri->pipes[pipe].desc = -1;
	dbri->pipes[pipe].first_desc = -1;
पूर्ण

/*
 * Lock must be held beक्रमe calling this.
 */
अटल व्योम setup_pipe(काष्ठा snd_dbri *dbri, पूर्णांक pipe, पूर्णांक sdp)
अणु
	अगर (pipe < 0 || pipe > DBRI_MAX_PIPE) अणु
		prपूर्णांकk(KERN_ERR "DBRI: setup_pipe called "
			"with illegal pipe number\n");
		वापस;
	पूर्ण

	अगर ((sdp & 0xf800) != sdp) अणु
		prपूर्णांकk(KERN_ERR "DBRI: setup_pipe called "
			"with strange SDP value\n");
		/* sdp &= 0xf800; */
	पूर्ण

	/* If this is a fixed receive pipe, arrange क्रम an पूर्णांकerrupt
	 * every समय its data changes
	 */
	अगर (D_SDP_MODE(sdp) == D_SDP_FIXED && !(sdp & D_SDP_TO_SER))
		sdp |= D_SDP_CHANGE;

	sdp |= D_PIPE(pipe);
	dbri->pipes[pipe].sdp = sdp;
	dbri->pipes[pipe].desc = -1;
	dbri->pipes[pipe].first_desc = -1;

	reset_pipe(dbri, pipe);
पूर्ण

/*
 * Lock must be held beक्रमe calling this.
 */
अटल व्योम link_समय_slot(काष्ठा snd_dbri *dbri, पूर्णांक pipe,
			   पूर्णांक prevpipe, पूर्णांक nextpipe,
			   पूर्णांक length, पूर्णांक cycle)
अणु
	s32 *cmd;
	पूर्णांक val;

	अगर (pipe < 0 || pipe > DBRI_MAX_PIPE
			|| prevpipe < 0 || prevpipe > DBRI_MAX_PIPE
			|| nextpipe < 0 || nextpipe > DBRI_MAX_PIPE) अणु
		prपूर्णांकk(KERN_ERR
		    "DBRI: link_time_slot called with illegal pipe number\n");
		वापस;
	पूर्ण

	अगर (dbri->pipes[pipe].sdp == 0
			|| dbri->pipes[prevpipe].sdp == 0
			|| dbri->pipes[nextpipe].sdp == 0) अणु
		prपूर्णांकk(KERN_ERR "DBRI: link_time_slot called "
			"on uninitialized pipe\n");
		वापस;
	पूर्ण

	dbri->pipes[prevpipe].nextpipe = pipe;
	dbri->pipes[pipe].nextpipe = nextpipe;
	dbri->pipes[pipe].length = length;

	cmd = dbri_cmdlock(dbri, 4);

	अगर (dbri->pipes[pipe].sdp & D_SDP_TO_SER) अणु
		/* Deal with CHI special हाल:
		 * "If transmission on edges 0 or 1 is desired, then cycle n
		 *  (where n = # of bit बार per frame...) must be used."
		 *                  - DBRI data sheet, page 11
		 */
		अगर (prevpipe == 16 && cycle == 0)
			cycle = dbri->chi_bpf;

		val = D_DTS_VO | D_DTS_INS | D_DTS_PRVOUT(prevpipe) | pipe;
		*(cmd++) = DBRI_CMD(D_DTS, 0, val);
		*(cmd++) = 0;
		*(cmd++) =
		    D_TS_LEN(length) | D_TS_CYCLE(cycle) | D_TS_NEXT(nextpipe);
	पूर्ण अन्यथा अणु
		val = D_DTS_VI | D_DTS_INS | D_DTS_PRVIN(prevpipe) | pipe;
		*(cmd++) = DBRI_CMD(D_DTS, 0, val);
		*(cmd++) =
		    D_TS_LEN(length) | D_TS_CYCLE(cycle) | D_TS_NEXT(nextpipe);
		*(cmd++) = 0;
	पूर्ण
	*(cmd++) = DBRI_CMD(D_PAUSE, 0, 0);

	dbri_cmdsend(dbri, cmd, 4);
पूर्ण

#अगर 0
/*
 * Lock must be held beक्रमe calling this.
 */
अटल व्योम unlink_समय_slot(काष्ठा snd_dbri *dbri, पूर्णांक pipe,
			     क्रमागत in_or_out direction, पूर्णांक prevpipe,
			     पूर्णांक nextpipe)
अणु
	s32 *cmd;
	पूर्णांक val;

	अगर (pipe < 0 || pipe > DBRI_MAX_PIPE
			|| prevpipe < 0 || prevpipe > DBRI_MAX_PIPE
			|| nextpipe < 0 || nextpipe > DBRI_MAX_PIPE) अणु
		prपूर्णांकk(KERN_ERR
		    "DBRI: unlink_time_slot called with illegal pipe number\n");
		वापस;
	पूर्ण

	cmd = dbri_cmdlock(dbri, 4);

	अगर (direction == PIPEinput) अणु
		val = D_DTS_VI | D_DTS_DEL | D_DTS_PRVIN(prevpipe) | pipe;
		*(cmd++) = DBRI_CMD(D_DTS, 0, val);
		*(cmd++) = D_TS_NEXT(nextpipe);
		*(cmd++) = 0;
	पूर्ण अन्यथा अणु
		val = D_DTS_VO | D_DTS_DEL | D_DTS_PRVOUT(prevpipe) | pipe;
		*(cmd++) = DBRI_CMD(D_DTS, 0, val);
		*(cmd++) = 0;
		*(cmd++) = D_TS_NEXT(nextpipe);
	पूर्ण
	*(cmd++) = DBRI_CMD(D_PAUSE, 0, 0);

	dbri_cmdsend(dbri, cmd, 4);
पूर्ण
#पूर्ण_अगर

/* xmit_fixed() / recv_fixed()
 *
 * Transmit/receive data on a "fixed" pipe - i.e, one whose contents are not
 * expected to change much, and which we करोn't need to buffer.
 * The DBRI only पूर्णांकerrupts us when the data changes (receive pipes),
 * or only changes the data when this function is called (transmit pipes).
 * Only लघु pipes (numbers 16-31) can be used in fixed data mode.
 *
 * These function operate on a 32-bit field, no matter how large
 * the actual समय slot is.  The पूर्णांकerrupt handler takes care of bit
 * ordering and alignment.  An 8-bit समय slot will always end up
 * in the low-order 8 bits, filled either MSB-first or LSB-first,
 * depending on the settings passed to setup_pipe().
 *
 * Lock must not be held beक्रमe calling it.
 */
अटल व्योम xmit_fixed(काष्ठा snd_dbri *dbri, पूर्णांक pipe, अचिन्हित पूर्णांक data)
अणु
	s32 *cmd;
	अचिन्हित दीर्घ flags;

	अगर (pipe < 16 || pipe > DBRI_MAX_PIPE) अणु
		prपूर्णांकk(KERN_ERR "DBRI: xmit_fixed: Illegal pipe number\n");
		वापस;
	पूर्ण

	अगर (D_SDP_MODE(dbri->pipes[pipe].sdp) == 0) अणु
		prपूर्णांकk(KERN_ERR "DBRI: xmit_fixed: "
			"Uninitialized pipe %d\n", pipe);
		वापस;
	पूर्ण

	अगर (D_SDP_MODE(dbri->pipes[pipe].sdp) != D_SDP_FIXED) अणु
		prपूर्णांकk(KERN_ERR "DBRI: xmit_fixed: Non-fixed pipe %d\n", pipe);
		वापस;
	पूर्ण

	अगर (!(dbri->pipes[pipe].sdp & D_SDP_TO_SER)) अणु
		prपूर्णांकk(KERN_ERR "DBRI: xmit_fixed: Called on receive pipe %d\n",
			pipe);
		वापस;
	पूर्ण

	/* DBRI लघु pipes always transmit LSB first */

	अगर (dbri->pipes[pipe].sdp & D_SDP_MSB)
		data = reverse_bytes(data, dbri->pipes[pipe].length);

	cmd = dbri_cmdlock(dbri, 3);

	*(cmd++) = DBRI_CMD(D_SSP, 0, pipe);
	*(cmd++) = data;
	*(cmd++) = DBRI_CMD(D_PAUSE, 0, 0);

	spin_lock_irqsave(&dbri->lock, flags);
	dbri_cmdsend(dbri, cmd, 3);
	spin_unlock_irqrestore(&dbri->lock, flags);
	dbri_cmdरुको(dbri);

पूर्ण

अटल व्योम recv_fixed(काष्ठा snd_dbri *dbri, पूर्णांक pipe, अस्थिर __u32 *ptr)
अणु
	अगर (pipe < 16 || pipe > DBRI_MAX_PIPE) अणु
		prपूर्णांकk(KERN_ERR "DBRI: recv_fixed called with "
			"illegal pipe number\n");
		वापस;
	पूर्ण

	अगर (D_SDP_MODE(dbri->pipes[pipe].sdp) != D_SDP_FIXED) अणु
		prपूर्णांकk(KERN_ERR "DBRI: recv_fixed called on "
			"non-fixed pipe %d\n", pipe);
		वापस;
	पूर्ण

	अगर (dbri->pipes[pipe].sdp & D_SDP_TO_SER) अणु
		prपूर्णांकk(KERN_ERR "DBRI: recv_fixed called on "
			"transmit pipe %d\n", pipe);
		वापस;
	पूर्ण

	dbri->pipes[pipe].recv_fixed_ptr = ptr;
पूर्ण

/* setup_descs()
 *
 * Setup transmit/receive data on a "long" pipe - i.e, one associated
 * with a DMA buffer.
 *
 * Only pipe numbers 0-15 can be used in this mode.
 *
 * This function takes a stream number poपूर्णांकing to a data buffer,
 * and work by building chains of descriptors which identअगरy the
 * data buffers.  Buffers too large क्रम a single descriptor will
 * be spपढ़ो across multiple descriptors.
 *
 * All descriptors create a ring buffer.
 *
 * Lock must be held beक्रमe calling this.
 */
अटल पूर्णांक setup_descs(काष्ठा snd_dbri *dbri, पूर्णांक streamno, अचिन्हित पूर्णांक period)
अणु
	काष्ठा dbri_streaminfo *info = &dbri->stream_info[streamno];
	u32 dvma_addr = (u32)dbri->dma_dvma;
	__u32 dvma_buffer;
	पूर्णांक desc;
	पूर्णांक len;
	पूर्णांक first_desc = -1;
	पूर्णांक last_desc = -1;

	अगर (info->pipe < 0 || info->pipe > 15) अणु
		prपूर्णांकk(KERN_ERR "DBRI: setup_descs: Illegal pipe number\n");
		वापस -2;
	पूर्ण

	अगर (dbri->pipes[info->pipe].sdp == 0) अणु
		prपूर्णांकk(KERN_ERR "DBRI: setup_descs: Uninitialized pipe %d\n",
		       info->pipe);
		वापस -2;
	पूर्ण

	dvma_buffer = info->dvma_buffer;
	len = info->size;

	अगर (streamno == DBRI_PLAY) अणु
		अगर (!(dbri->pipes[info->pipe].sdp & D_SDP_TO_SER)) अणु
			prपूर्णांकk(KERN_ERR "DBRI: setup_descs: "
				"Called on receive pipe %d\n", info->pipe);
			वापस -2;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dbri->pipes[info->pipe].sdp & D_SDP_TO_SER) अणु
			prपूर्णांकk(KERN_ERR
			    "DBRI: setup_descs: Called on transmit pipe %d\n",
			     info->pipe);
			वापस -2;
		पूर्ण
		/* Should be able to queue multiple buffers
		 * to receive on a pipe
		 */
		अगर (pipe_active(dbri, info->pipe)) अणु
			prपूर्णांकk(KERN_ERR "DBRI: recv_on_pipe: "
				"Called on active pipe %d\n", info->pipe);
			वापस -2;
		पूर्ण

		/* Make sure buffer size is multiple of four */
		len &= ~3;
	पूर्ण

	/* Free descriptors अगर pipe has any */
	desc = dbri->pipes[info->pipe].first_desc;
	अगर (desc >= 0)
		करो अणु
			dbri->dma->desc[desc].ba = 0;
			dbri->dma->desc[desc].nda = 0;
			desc = dbri->next_desc[desc];
		पूर्ण जबतक (desc != -1 &&
			 desc != dbri->pipes[info->pipe].first_desc);

	dbri->pipes[info->pipe].desc = -1;
	dbri->pipes[info->pipe].first_desc = -1;

	desc = 0;
	जबतक (len > 0) अणु
		पूर्णांक mylen;

		क्रम (; desc < DBRI_NO_DESCS; desc++) अणु
			अगर (!dbri->dma->desc[desc].ba)
				अवरोध;
		पूर्ण

		अगर (desc == DBRI_NO_DESCS) अणु
			prपूर्णांकk(KERN_ERR "DBRI: setup_descs: No descriptors\n");
			वापस -1;
		पूर्ण

		अगर (len > DBRI_TD_MAXCNT)
			mylen = DBRI_TD_MAXCNT;	/* 8KB - 4 */
		अन्यथा
			mylen = len;

		अगर (mylen > period)
			mylen = period;

		dbri->next_desc[desc] = -1;
		dbri->dma->desc[desc].ba = dvma_buffer;
		dbri->dma->desc[desc].nda = 0;

		अगर (streamno == DBRI_PLAY) अणु
			dbri->dma->desc[desc].word1 = DBRI_TD_CNT(mylen);
			dbri->dma->desc[desc].word4 = 0;
			dbri->dma->desc[desc].word1 |= DBRI_TD_F | DBRI_TD_B;
		पूर्ण अन्यथा अणु
			dbri->dma->desc[desc].word1 = 0;
			dbri->dma->desc[desc].word4 =
			    DBRI_RD_B | DBRI_RD_BCNT(mylen);
		पूर्ण

		अगर (first_desc == -1)
			first_desc = desc;
		अन्यथा अणु
			dbri->next_desc[last_desc] = desc;
			dbri->dma->desc[last_desc].nda =
			    dvma_addr + dbri_dma_off(desc, desc);
		पूर्ण

		last_desc = desc;
		dvma_buffer += mylen;
		len -= mylen;
	पूर्ण

	अगर (first_desc == -1 || last_desc == -1) अणु
		prपूर्णांकk(KERN_ERR "DBRI: setup_descs: "
			" Not enough descriptors available\n");
		वापस -1;
	पूर्ण

	dbri->dma->desc[last_desc].nda =
	    dvma_addr + dbri_dma_off(desc, first_desc);
	dbri->next_desc[last_desc] = first_desc;
	dbri->pipes[info->pipe].first_desc = first_desc;
	dbri->pipes[info->pipe].desc = first_desc;

#अगर_घोषित DBRI_DEBUG
	क्रम (desc = first_desc; desc != -1;) अणु
		dprपूर्णांकk(D_DESC, "DESC %d: %08x %08x %08x %08x\n",
			desc,
			dbri->dma->desc[desc].word1,
			dbri->dma->desc[desc].ba,
			dbri->dma->desc[desc].nda, dbri->dma->desc[desc].word4);
			desc = dbri->next_desc[desc];
			अगर (desc == first_desc)
				अवरोध;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
****************************************************************************
************************** DBRI - CHI पूर्णांकerface ****************************
****************************************************************************

The CHI is a four-wire (घड़ी, frame sync, data in, data out) समय-भागision
multiplexed serial पूर्णांकerface which the DBRI can operate in either master
(give घड़ी/frame sync) or slave (take घड़ी/frame sync) mode.

*/

क्रमागत master_or_slave अणु CHImaster, CHIslave पूर्ण;

/*
 * Lock must not be held beक्रमe calling it.
 */
अटल व्योम reset_chi(काष्ठा snd_dbri *dbri,
		      क्रमागत master_or_slave master_or_slave,
		      पूर्णांक bits_per_frame)
अणु
	s32 *cmd;
	पूर्णांक val;

	/* Set CHI Anchor: Pipe 16 */

	cmd = dbri_cmdlock(dbri, 4);
	val = D_DTS_VO | D_DTS_VI | D_DTS_INS
		| D_DTS_PRVIN(16) | D_PIPE(16) | D_DTS_PRVOUT(16);
	*(cmd++) = DBRI_CMD(D_DTS, 0, val);
	*(cmd++) = D_TS_ANCHOR | D_TS_NEXT(16);
	*(cmd++) = D_TS_ANCHOR | D_TS_NEXT(16);
	*(cmd++) = DBRI_CMD(D_PAUSE, 0, 0);
	dbri_cmdsend(dbri, cmd, 4);

	dbri->pipes[16].sdp = 1;
	dbri->pipes[16].nextpipe = 16;

	cmd = dbri_cmdlock(dbri, 4);

	अगर (master_or_slave == CHIslave) अणु
		/* Setup DBRI क्रम CHI Slave - receive घड़ी, frame sync (FS)
		 *
		 * CHICM  = 0 (slave mode, 8 kHz frame rate)
		 * IR     = give immediate CHI status पूर्णांकerrupt
		 * EN     = give CHI status पूर्णांकerrupt upon change
		 */
		*(cmd++) = DBRI_CMD(D_CHI, 0, D_CHI_CHICM(0));
	पूर्ण अन्यथा अणु
		/* Setup DBRI क्रम CHI Master - generate घड़ी, FS
		 *
		 * BPF				=  bits per 8 kHz frame
		 * 12.288 MHz / CHICM_भागisor	= घड़ी rate
		 * FD = 1 - drive CHIFS on rising edge of CHICK
		 */
		पूर्णांक घड़ीrate = bits_per_frame * 8;
		पूर्णांक भागisor = 12288 / घड़ीrate;

		अगर (भागisor > 255 || भागisor * घड़ीrate != 12288)
			prपूर्णांकk(KERN_ERR "DBRI: illegal bits_per_frame "
				"in setup_chi\n");

		*(cmd++) = DBRI_CMD(D_CHI, 0, D_CHI_CHICM(भागisor) | D_CHI_FD
				    | D_CHI_BPF(bits_per_frame));
	पूर्ण

	dbri->chi_bpf = bits_per_frame;

	/* CHI Data Mode
	 *
	 * RCE   =  0 - receive on falling edge of CHICK
	 * XCE   =  1 - transmit on rising edge of CHICK
	 * XEN   =  1 - enable transmitter
	 * REN   =  1 - enable receiver
	 */

	*(cmd++) = DBRI_CMD(D_PAUSE, 0, 0);
	*(cmd++) = DBRI_CMD(D_CDM, 0, D_CDM_XCE | D_CDM_XEN | D_CDM_REN);
	*(cmd++) = DBRI_CMD(D_PAUSE, 0, 0);

	dbri_cmdsend(dbri, cmd, 4);
पूर्ण

/*
****************************************************************************
*********************** CS4215 audio codec management **********************
****************************************************************************

In the standard SPARC audio configuration, the CS4215 codec is attached
to the DBRI via the CHI पूर्णांकerface and few of the DBRI's PIO pins.

 * Lock must not be held beक्रमe calling it.

*/
अटल व्योम cs4215_setup_pipes(काष्ठा snd_dbri *dbri)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dbri->lock, flags);
	/*
	 * Data mode:
	 * Pipe  4: Send बारlots 1-4 (audio data)
	 * Pipe 20: Send बारlots 5-8 (part of ctrl data)
	 * Pipe  6: Receive बारlots 1-4 (audio data)
	 * Pipe 21: Receive बारlots 6-7. We can only receive 20 bits via
	 *          पूर्णांकerrupt, and the rest of the data (slot 5 and 8) is
	 *          not relevant क्रम us (only क्रम द्विगुनchecking).
	 *
	 * Control mode:
	 * Pipe 17: Send बारlots 1-4 (slots 5-8 are पढ़ो only)
	 * Pipe 18: Receive बारlot 1 (clb).
	 * Pipe 19: Receive बारlot 7 (version).
	 */

	setup_pipe(dbri, 4, D_SDP_MEM | D_SDP_TO_SER | D_SDP_MSB);
	setup_pipe(dbri, 20, D_SDP_FIXED | D_SDP_TO_SER | D_SDP_MSB);
	setup_pipe(dbri, 6, D_SDP_MEM | D_SDP_FROM_SER | D_SDP_MSB);
	setup_pipe(dbri, 21, D_SDP_FIXED | D_SDP_FROM_SER | D_SDP_MSB);

	setup_pipe(dbri, 17, D_SDP_FIXED | D_SDP_TO_SER | D_SDP_MSB);
	setup_pipe(dbri, 18, D_SDP_FIXED | D_SDP_FROM_SER | D_SDP_MSB);
	setup_pipe(dbri, 19, D_SDP_FIXED | D_SDP_FROM_SER | D_SDP_MSB);
	spin_unlock_irqrestore(&dbri->lock, flags);

	dbri_cmdरुको(dbri);
पूर्ण

अटल पूर्णांक cs4215_init_data(काष्ठा cs4215 *mm)
अणु
	/*
	 * No action, memory resetting only.
	 *
	 * Data Time Slot 5-8
	 * Speaker,Line and Headphone enable. Gain set to the half.
	 * Input is mike.
	 */
	mm->data[0] = CS4215_LO(0x20) | CS4215_HE | CS4215_LE;
	mm->data[1] = CS4215_RO(0x20) | CS4215_SE;
	mm->data[2] = CS4215_LG(0x8) | CS4215_IS | CS4215_PIO0 | CS4215_PIO1;
	mm->data[3] = CS4215_RG(0x8) | CS4215_MA(0xf);

	/*
	 * Control Time Slot 1-4
	 * 0: Default I/O voltage scale
	 * 1: 8 bit ulaw, 8kHz, mono, high pass filter disabled
	 * 2: Serial enable, CHI master, 128 bits per frame, घड़ी 1
	 * 3: Tests disabled
	 */
	mm->ctrl[0] = CS4215_RSRVD_1 | CS4215_MLB;
	mm->ctrl[1] = CS4215_DFR_ULAW | CS4215_FREQ[0].csval;
	mm->ctrl[2] = CS4215_XCLK | CS4215_BSEL_128 | CS4215_FREQ[0].xtal;
	mm->ctrl[3] = 0;

	mm->status = 0;
	mm->version = 0xff;
	mm->precision = 8;	/* For ULAW */
	mm->channels = 1;

	वापस 0;
पूर्ण

अटल व्योम cs4215_setdata(काष्ठा snd_dbri *dbri, पूर्णांक muted)
अणु
	अगर (muted) अणु
		dbri->mm.data[0] |= 63;
		dbri->mm.data[1] |= 63;
		dbri->mm.data[2] &= ~15;
		dbri->mm.data[3] &= ~15;
	पूर्ण अन्यथा अणु
		/* Start by setting the playback attenuation. */
		काष्ठा dbri_streaminfo *info = &dbri->stream_info[DBRI_PLAY];
		पूर्णांक left_gain = info->left_gain & 0x3f;
		पूर्णांक right_gain = info->right_gain & 0x3f;

		dbri->mm.data[0] &= ~0x3f;	/* Reset the volume bits */
		dbri->mm.data[1] &= ~0x3f;
		dbri->mm.data[0] |= (DBRI_MAX_VOLUME - left_gain);
		dbri->mm.data[1] |= (DBRI_MAX_VOLUME - right_gain);

		/* Now set the recording gain. */
		info = &dbri->stream_info[DBRI_REC];
		left_gain = info->left_gain & 0xf;
		right_gain = info->right_gain & 0xf;
		dbri->mm.data[2] |= CS4215_LG(left_gain);
		dbri->mm.data[3] |= CS4215_RG(right_gain);
	पूर्ण

	xmit_fixed(dbri, 20, *(पूर्णांक *)dbri->mm.data);
पूर्ण

/*
 * Set the CS4215 to data mode.
 */
अटल व्योम cs4215_खोलो(काष्ठा snd_dbri *dbri)
अणु
	पूर्णांक data_width;
	u32 पंचांगp;
	अचिन्हित दीर्घ flags;

	dprपूर्णांकk(D_MM, "cs4215_open: %d channels, %d bits\n",
		dbri->mm.channels, dbri->mm.precision);

	/* Temporarily mute outमाला_दो, and रुको 1/8000 sec (125 us)
	 * to make sure this takes.  This aव्योमs clicking noises.
	 */

	cs4215_setdata(dbri, 1);
	udelay(125);

	/*
	 * Data mode:
	 * Pipe  4: Send बारlots 1-4 (audio data)
	 * Pipe 20: Send बारlots 5-8 (part of ctrl data)
	 * Pipe  6: Receive बारlots 1-4 (audio data)
	 * Pipe 21: Receive बारlots 6-7. We can only receive 20 bits via
	 *          पूर्णांकerrupt, and the rest of the data (slot 5 and 8) is
	 *          not relevant क्रम us (only क्रम द्विगुनchecking).
	 *
	 * Just like in control mode, the समय slots are all offset by eight
	 * bits.  The CS4215, it seems, observes TSIN (the delayed संकेत)
	 * even अगर it's the CHI master.  Don't ask me...
	 */
	spin_lock_irqsave(&dbri->lock, flags);
	पंचांगp = sbus_पढ़ोl(dbri->regs + REG0);
	पंचांगp &= ~(D_C);		/* Disable CHI */
	sbus_ग_लिखोl(पंचांगp, dbri->regs + REG0);

	/* Switch CS4215 to data mode - set PIO3 to 1 */
	sbus_ग_लिखोl(D_ENPIO | D_PIO1 | D_PIO3 |
		    (dbri->mm.onboard ? D_PIO0 : D_PIO2), dbri->regs + REG2);

	reset_chi(dbri, CHIslave, 128);

	/* Note: this next करोesn't work क्रम 8-bit stereo, because the two
	 * channels would be on बारlots 1 and 3, with 2 and 4 idle.
	 * (See CS4215 datasheet Fig 15)
	 *
	 * DBRI non-contiguous mode would be required to make this work.
	 */
	data_width = dbri->mm.channels * dbri->mm.precision;

	link_समय_slot(dbri, 4, 16, 16, data_width, dbri->mm.offset);
	link_समय_slot(dbri, 20, 4, 16, 32, dbri->mm.offset + 32);
	link_समय_slot(dbri, 6, 16, 16, data_width, dbri->mm.offset);
	link_समय_slot(dbri, 21, 6, 16, 16, dbri->mm.offset + 40);

	/* FIXME: enable CHI after _setdata? */
	पंचांगp = sbus_पढ़ोl(dbri->regs + REG0);
	पंचांगp |= D_C;		/* Enable CHI */
	sbus_ग_लिखोl(पंचांगp, dbri->regs + REG0);
	spin_unlock_irqrestore(&dbri->lock, flags);

	cs4215_setdata(dbri, 0);
पूर्ण

/*
 * Send the control inक्रमmation (i.e. audio क्रमmat)
 */
अटल पूर्णांक cs4215_setctrl(काष्ठा snd_dbri *dbri)
अणु
	पूर्णांक i, val;
	u32 पंचांगp;
	अचिन्हित दीर्घ flags;

	/* FIXME - let the CPU करो something useful during these delays */

	/* Temporarily mute outमाला_दो, and रुको 1/8000 sec (125 us)
	 * to make sure this takes.  This aव्योमs clicking noises.
	 */
	cs4215_setdata(dbri, 1);
	udelay(125);

	/*
	 * Enable Control mode: Set DBRI's PIO3 (4215's D/~C) to 0, then रुको
	 * 12 cycles <= 12/(5512.5*64) sec = 34.01 usec
	 */
	val = D_ENPIO | D_PIO1 | (dbri->mm.onboard ? D_PIO0 : D_PIO2);
	sbus_ग_लिखोl(val, dbri->regs + REG2);
	dprपूर्णांकk(D_MM, "cs4215_setctrl: reg2=0x%x\n", val);
	udelay(34);

	/* In Control mode, the CS4215 is a slave device, so the DBRI must
	 * operate as CHI master, supplying घड़ीing and frame synchronization.
	 *
	 * In Data mode, however, the CS4215 must be CHI master to insure
	 * that its data stream is synchronous with its codec.
	 *
	 * The upshot of all this?  We start by putting the DBRI पूर्णांकo master
	 * mode, program the CS4215 in Control mode, then चयन the CS4215
	 * पूर्णांकo Data mode and put the DBRI पूर्णांकo slave mode.  Various timing
	 * requirements must be observed aदीर्घ the way.
	 *
	 * Oh, and one more thing, on a SPARCStation 20 (and maybe
	 * others?), the addressing of the CS4215's समय slots is
	 * offset by eight bits, so we add eight to all the "cycle"
	 * values in the Define Time Slot (DTS) commands.  This is
	 * करोne in hardware by a TI 248 that delays the DBRI->4215
	 * frame sync संकेत by eight घड़ी cycles.  Anybody know why?
	 */
	spin_lock_irqsave(&dbri->lock, flags);
	पंचांगp = sbus_पढ़ोl(dbri->regs + REG0);
	पंचांगp &= ~D_C;		/* Disable CHI */
	sbus_ग_लिखोl(पंचांगp, dbri->regs + REG0);

	reset_chi(dbri, CHImaster, 128);

	/*
	 * Control mode:
	 * Pipe 17: Send बारlots 1-4 (slots 5-8 are पढ़ो only)
	 * Pipe 18: Receive बारlot 1 (clb).
	 * Pipe 19: Receive बारlot 7 (version).
	 */

	link_समय_slot(dbri, 17, 16, 16, 32, dbri->mm.offset);
	link_समय_slot(dbri, 18, 16, 16, 8, dbri->mm.offset);
	link_समय_slot(dbri, 19, 18, 16, 8, dbri->mm.offset + 48);
	spin_unlock_irqrestore(&dbri->lock, flags);

	/* Wait क्रम the chip to echo back CLB (Control Latch Bit) as zero */
	dbri->mm.ctrl[0] &= ~CS4215_CLB;
	xmit_fixed(dbri, 17, *(पूर्णांक *)dbri->mm.ctrl);

	spin_lock_irqsave(&dbri->lock, flags);
	पंचांगp = sbus_पढ़ोl(dbri->regs + REG0);
	पंचांगp |= D_C;		/* Enable CHI */
	sbus_ग_लिखोl(पंचांगp, dbri->regs + REG0);
	spin_unlock_irqrestore(&dbri->lock, flags);

	क्रम (i = 10; ((dbri->mm.status & 0xe4) != 0x20); --i)
		msleep_पूर्णांकerruptible(1);

	अगर (i == 0) अणु
		dprपूर्णांकk(D_MM, "CS4215 didn't respond to CLB (0x%02x)\n",
			dbri->mm.status);
		वापस -1;
	पूर्ण

	/* Disable changes to our copy of the version number, as we are about
	 * to leave control mode.
	 */
	recv_fixed(dbri, 19, शून्य);

	/* Terminate CS4215 control mode - data sheet says
	 * "Set CLB=1 and send two more frames of valid control info"
	 */
	dbri->mm.ctrl[0] |= CS4215_CLB;
	xmit_fixed(dbri, 17, *(पूर्णांक *)dbri->mm.ctrl);

	/* Two frames of control info @ 8kHz frame rate = 250 us delay */
	udelay(250);

	cs4215_setdata(dbri, 0);

	वापस 0;
पूर्ण

/*
 * Setup the codec with the sampling rate, audio क्रमmat and number of
 * channels.
 * As part of the process we resend the settings क्रम the data
 * बारlots as well.
 */
अटल पूर्णांक cs4215_prepare(काष्ठा snd_dbri *dbri, अचिन्हित पूर्णांक rate,
			  snd_pcm_क्रमmat_t क्रमmat, अचिन्हित पूर्णांक channels)
अणु
	पूर्णांक freq_idx;
	पूर्णांक ret = 0;

	/* Lookup index क्रम this rate */
	क्रम (freq_idx = 0; CS4215_FREQ[freq_idx].freq != 0; freq_idx++) अणु
		अगर (CS4215_FREQ[freq_idx].freq == rate)
			अवरोध;
	पूर्ण
	अगर (CS4215_FREQ[freq_idx].freq != rate) अणु
		prपूर्णांकk(KERN_WARNING "DBRI: Unsupported rate %d Hz\n", rate);
		वापस -1;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_MU_LAW:
		dbri->mm.ctrl[1] = CS4215_DFR_ULAW;
		dbri->mm.precision = 8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_A_LAW:
		dbri->mm.ctrl[1] = CS4215_DFR_ALAW;
		dbri->mm.precision = 8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_U8:
		dbri->mm.ctrl[1] = CS4215_DFR_LINEAR8;
		dbri->mm.precision = 8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		dbri->mm.ctrl[1] = CS4215_DFR_LINEAR16;
		dbri->mm.precision = 16;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "DBRI: Unsupported format %d\n", क्रमmat);
		वापस -1;
	पूर्ण

	/* Add rate parameters */
	dbri->mm.ctrl[1] |= CS4215_FREQ[freq_idx].csval;
	dbri->mm.ctrl[2] = CS4215_XCLK |
	    CS4215_BSEL_128 | CS4215_FREQ[freq_idx].xtal;

	dbri->mm.channels = channels;
	अगर (channels == 2)
		dbri->mm.ctrl[1] |= CS4215_DFR_STEREO;

	ret = cs4215_setctrl(dbri);
	अगर (ret == 0)
		cs4215_खोलो(dbri);	/* set codec to data mode */

	वापस ret;
पूर्ण

/*
 *
 */
अटल पूर्णांक cs4215_init(काष्ठा snd_dbri *dbri)
अणु
	u32 reg2 = sbus_पढ़ोl(dbri->regs + REG2);
	dprपूर्णांकk(D_MM, "cs4215_init: reg2=0x%x\n", reg2);

	/* Look क्रम the cs4215 chips */
	अगर (reg2 & D_PIO2) अणु
		dprपूर्णांकk(D_MM, "Onboard CS4215 detected\n");
		dbri->mm.onboard = 1;
	पूर्ण
	अगर (reg2 & D_PIO0) अणु
		dprपूर्णांकk(D_MM, "Speakerbox detected\n");
		dbri->mm.onboard = 0;

		अगर (reg2 & D_PIO2) अणु
			prपूर्णांकk(KERN_INFO "DBRI: Using speakerbox / "
			       "ignoring onboard mmcodec.\n");
			sbus_ग_लिखोl(D_ENPIO2, dbri->regs + REG2);
		पूर्ण
	पूर्ण

	अगर (!(reg2 & (D_PIO0 | D_PIO2))) अणु
		prपूर्णांकk(KERN_ERR "DBRI: no mmcodec found.\n");
		वापस -EIO;
	पूर्ण

	cs4215_setup_pipes(dbri);
	cs4215_init_data(&dbri->mm);

	/* Enable capture of the status & version बारlots. */
	recv_fixed(dbri, 18, &dbri->mm.status);
	recv_fixed(dbri, 19, &dbri->mm.version);

	dbri->mm.offset = dbri->mm.onboard ? 0 : 8;
	अगर (cs4215_setctrl(dbri) == -1 || dbri->mm.version == 0xff) अणु
		dprपूर्णांकk(D_MM, "CS4215 failed probe at offset %d\n",
			dbri->mm.offset);
		वापस -EIO;
	पूर्ण
	dprपूर्णांकk(D_MM, "Found CS4215 at offset %d\n", dbri->mm.offset);

	वापस 0;
पूर्ण

/*
****************************************************************************
*************************** DBRI पूर्णांकerrupt handler *************************
****************************************************************************

The DBRI communicates with the CPU मुख्यly via a circular पूर्णांकerrupt
buffer.  When an पूर्णांकerrupt is संकेतed, the CPU walks through the
buffer and calls dbri_process_one_पूर्णांकerrupt() क्रम each पूर्णांकerrupt word.
Complicated पूर्णांकerrupts are handled by dedicated functions (which
appear first in this file).  Any pending पूर्णांकerrupts can be serviced by
calling dbri_process_पूर्णांकerrupt_buffer(), which works even अगर the CPU's
पूर्णांकerrupts are disabled.

*/

/* xmit_descs()
 *
 * Starts transmitting the current TD's क्रम recording/playing.
 * For playback, ALSA has filled the DMA memory with new data (we hope).
 */
अटल व्योम xmit_descs(काष्ठा snd_dbri *dbri)
अणु
	काष्ठा dbri_streaminfo *info;
	u32 dvma_addr;
	s32 *cmd;
	अचिन्हित दीर्घ flags;
	पूर्णांक first_td;

	अगर (dbri == शून्य)
		वापस;		/* Disabled */

	dvma_addr = (u32)dbri->dma_dvma;
	info = &dbri->stream_info[DBRI_REC];
	spin_lock_irqsave(&dbri->lock, flags);

	अगर (info->pipe >= 0) अणु
		first_td = dbri->pipes[info->pipe].first_desc;

		dprपूर्णांकk(D_DESC, "xmit_descs rec @ TD %d\n", first_td);

		/* Stream could be बंदd by the समय we run. */
		अगर (first_td >= 0) अणु
			cmd = dbri_cmdlock(dbri, 2);
			*(cmd++) = DBRI_CMD(D_SDP, 0,
					    dbri->pipes[info->pipe].sdp
					    | D_SDP_P | D_SDP_EVERY | D_SDP_C);
			*(cmd++) = dvma_addr +
				   dbri_dma_off(desc, first_td);
			dbri_cmdsend(dbri, cmd, 2);

			/* Reset our admin of the pipe. */
			dbri->pipes[info->pipe].desc = first_td;
		पूर्ण
	पूर्ण

	info = &dbri->stream_info[DBRI_PLAY];

	अगर (info->pipe >= 0) अणु
		first_td = dbri->pipes[info->pipe].first_desc;

		dprपूर्णांकk(D_DESC, "xmit_descs play @ TD %d\n", first_td);

		/* Stream could be बंदd by the समय we run. */
		अगर (first_td >= 0) अणु
			cmd = dbri_cmdlock(dbri, 2);
			*(cmd++) = DBRI_CMD(D_SDP, 0,
					    dbri->pipes[info->pipe].sdp
					    | D_SDP_P | D_SDP_EVERY | D_SDP_C);
			*(cmd++) = dvma_addr +
				   dbri_dma_off(desc, first_td);
			dbri_cmdsend(dbri, cmd, 2);

			/* Reset our admin of the pipe. */
			dbri->pipes[info->pipe].desc = first_td;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&dbri->lock, flags);
पूर्ण

/* transmission_complete_पूर्णांकr()
 *
 * Called by मुख्य पूर्णांकerrupt handler when DBRI संकेतs transmission complete
 * on a pipe (पूर्णांकerrupt triggered by the B bit in a transmit descriptor).
 *
 * Walks through the pipe's list of transmit buffer descriptors and marks
 * them as available. Stops when the first descriptor is found without
 * TBC (Transmit Buffer Complete) set, or we've run through them all.
 *
 * The DMA buffers are not released. They क्रमm a ring buffer and
 * they are filled by ALSA जबतक others are transmitted by DMA.
 *
 */

अटल व्योम transmission_complete_पूर्णांकr(काष्ठा snd_dbri *dbri, पूर्णांक pipe)
अणु
	काष्ठा dbri_streaminfo *info = &dbri->stream_info[DBRI_PLAY];
	पूर्णांक td = dbri->pipes[pipe].desc;
	पूर्णांक status;

	जबतक (td >= 0) अणु
		अगर (td >= DBRI_NO_DESCS) अणु
			prपूर्णांकk(KERN_ERR "DBRI: invalid td on pipe %d\n", pipe);
			वापस;
		पूर्ण

		status = DBRI_TD_STATUS(dbri->dma->desc[td].word4);
		अगर (!(status & DBRI_TD_TBC))
			अवरोध;

		dprपूर्णांकk(D_INT, "TD %d, status 0x%02x\n", td, status);

		dbri->dma->desc[td].word4 = 0;	/* Reset it क्रम next समय. */
		info->offset += DBRI_RD_CNT(dbri->dma->desc[td].word1);

		td = dbri->next_desc[td];
		dbri->pipes[pipe].desc = td;
	पूर्ण

	/* Notअगरy ALSA */
	spin_unlock(&dbri->lock);
	snd_pcm_period_elapsed(info->substream);
	spin_lock(&dbri->lock);
पूर्ण

अटल व्योम reception_complete_पूर्णांकr(काष्ठा snd_dbri *dbri, पूर्णांक pipe)
अणु
	काष्ठा dbri_streaminfo *info;
	पूर्णांक rd = dbri->pipes[pipe].desc;
	s32 status;

	अगर (rd < 0 || rd >= DBRI_NO_DESCS) अणु
		prपूर्णांकk(KERN_ERR "DBRI: invalid rd on pipe %d\n", pipe);
		वापस;
	पूर्ण

	dbri->pipes[pipe].desc = dbri->next_desc[rd];
	status = dbri->dma->desc[rd].word1;
	dbri->dma->desc[rd].word1 = 0;	/* Reset it क्रम next समय. */

	info = &dbri->stream_info[DBRI_REC];
	info->offset += DBRI_RD_CNT(status);

	/* FIXME: Check status */

	dprपूर्णांकk(D_INT, "Recv RD %d, status 0x%02x, len %d\n",
		rd, DBRI_RD_STATUS(status), DBRI_RD_CNT(status));

	/* Notअगरy ALSA */
	spin_unlock(&dbri->lock);
	snd_pcm_period_elapsed(info->substream);
	spin_lock(&dbri->lock);
पूर्ण

अटल व्योम dbri_process_one_पूर्णांकerrupt(काष्ठा snd_dbri *dbri, पूर्णांक x)
अणु
	पूर्णांक val = D_INTR_GETVAL(x);
	पूर्णांक channel = D_INTR_GETCHAN(x);
	पूर्णांक command = D_INTR_GETCMD(x);
	पूर्णांक code = D_INTR_GETCODE(x);
#अगर_घोषित DBRI_DEBUG
	पूर्णांक rval = D_INTR_GETRVAL(x);
#पूर्ण_अगर

	अगर (channel == D_INTR_CMD) अणु
		dprपूर्णांकk(D_CMD, "INTR: Command: %-5s  Value:%d\n",
			cmds[command], val);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(D_INT, "INTR: Chan:%d Code:%d Val:%#x\n",
			channel, code, rval);
	पूर्ण

	चयन (code) अणु
	हाल D_INTR_CMDI:
		अगर (command != D_WAIT)
			prपूर्णांकk(KERN_ERR "DBRI: Command read interrupt\n");
		अवरोध;
	हाल D_INTR_BRDY:
		reception_complete_पूर्णांकr(dbri, channel);
		अवरोध;
	हाल D_INTR_XCMP:
	हाल D_INTR_MINT:
		transmission_complete_पूर्णांकr(dbri, channel);
		अवरोध;
	हाल D_INTR_UNDR:
		/* UNDR - Transmission underrun
		 * resend SDP command with clear pipe bit (C) set
		 */
		अणु
	/* FIXME: करो something useful in हाल of underrun */
			prपूर्णांकk(KERN_ERR "DBRI: Underrun error\n");
#अगर 0
			s32 *cmd;
			पूर्णांक pipe = channel;
			पूर्णांक td = dbri->pipes[pipe].desc;

			dbri->dma->desc[td].word4 = 0;
			cmd = dbri_cmdlock(dbri, NoGetLock);
			*(cmd++) = DBRI_CMD(D_SDP, 0,
					    dbri->pipes[pipe].sdp
					    | D_SDP_P | D_SDP_C | D_SDP_2SAME);
			*(cmd++) = dbri->dma_dvma + dbri_dma_off(desc, td);
			dbri_cmdsend(dbri, cmd);
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	हाल D_INTR_FXDT:
		/* FXDT - Fixed data change */
		अगर (dbri->pipes[channel].sdp & D_SDP_MSB)
			val = reverse_bytes(val, dbri->pipes[channel].length);

		अगर (dbri->pipes[channel].recv_fixed_ptr)
			*(dbri->pipes[channel].recv_fixed_ptr) = val;
		अवरोध;
	शेष:
		अगर (channel != D_INTR_CMD)
			prपूर्णांकk(KERN_WARNING
			       "DBRI: Ignored Interrupt: %d (0x%x)\n", code, x);
	पूर्ण
पूर्ण

/* dbri_process_पूर्णांकerrupt_buffer advances through the DBRI's पूर्णांकerrupt
 * buffer until it finds a zero word (indicating nothing more to करो
 * right now).  Non-zero words require processing and are handed off
 * to dbri_process_one_पूर्णांकerrupt AFTER advancing the poपूर्णांकer.
 */
अटल व्योम dbri_process_पूर्णांकerrupt_buffer(काष्ठा snd_dbri *dbri)
अणु
	s32 x;

	जबतक ((x = dbri->dma->पूर्णांकr[dbri->dbri_irqp]) != 0) अणु
		dbri->dma->पूर्णांकr[dbri->dbri_irqp] = 0;
		dbri->dbri_irqp++;
		अगर (dbri->dbri_irqp == DBRI_INT_BLK)
			dbri->dbri_irqp = 1;

		dbri_process_one_पूर्णांकerrupt(dbri, x);
	पूर्ण
पूर्ण

अटल irqवापस_t snd_dbri_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_dbri *dbri = dev_id;
	अटल पूर्णांक errcnt = 0;
	पूर्णांक x;

	अगर (dbri == शून्य)
		वापस IRQ_NONE;
	spin_lock(&dbri->lock);

	/*
	 * Read it, so the पूर्णांकerrupt goes away.
	 */
	x = sbus_पढ़ोl(dbri->regs + REG1);

	अगर (x & (D_MRR | D_MLE | D_LBG | D_MBE)) अणु
		u32 पंचांगp;

		अगर (x & D_MRR)
			prपूर्णांकk(KERN_ERR
			       "DBRI: Multiple Error Ack on SBus reg1=0x%x\n",
			       x);
		अगर (x & D_MLE)
			prपूर्णांकk(KERN_ERR
			       "DBRI: Multiple Late Error on SBus reg1=0x%x\n",
			       x);
		अगर (x & D_LBG)
			prपूर्णांकk(KERN_ERR
			       "DBRI: Lost Bus Grant on SBus reg1=0x%x\n", x);
		अगर (x & D_MBE)
			prपूर्णांकk(KERN_ERR
			       "DBRI: Burst Error on SBus reg1=0x%x\n", x);

		/* Some of these SBus errors cause the chip's SBus circuitry
		 * to be disabled, so just re-enable and try to keep going.
		 *
		 * The only one I've seen is MRR, which will be triggered
		 * अगर you let a transmit pipe underrun, then try to CDP it.
		 *
		 * If these things persist, we reset the chip.
		 */
		अगर ((++errcnt) % 10 == 0) अणु
			dprपूर्णांकk(D_INT, "Interrupt errors exceeded.\n");
			dbri_reset(dbri);
		पूर्ण अन्यथा अणु
			पंचांगp = sbus_पढ़ोl(dbri->regs + REG0);
			पंचांगp &= ~(D_D);
			sbus_ग_लिखोl(पंचांगp, dbri->regs + REG0);
		पूर्ण
	पूर्ण

	dbri_process_पूर्णांकerrupt_buffer(dbri);

	spin_unlock(&dbri->lock);

	वापस IRQ_HANDLED;
पूर्ण

/****************************************************************************
		PCM Interface
****************************************************************************/
अटल स्थिर काष्ठा snd_pcm_hardware snd_dbri_pcm_hw = अणु
	.info		= SNDRV_PCM_INFO_MMAP |
			  SNDRV_PCM_INFO_INTERLEAVED |
			  SNDRV_PCM_INFO_BLOCK_TRANSFER |
			  SNDRV_PCM_INFO_MMAP_VALID |
			  SNDRV_PCM_INFO_BATCH,
	.क्रमmats	= SNDRV_PCM_FMTBIT_MU_LAW |
			  SNDRV_PCM_FMTBIT_A_LAW |
			  SNDRV_PCM_FMTBIT_U8 |
			  SNDRV_PCM_FMTBIT_S16_BE,
	.rates		= SNDRV_PCM_RATE_8000_48000 | SNDRV_PCM_RATE_5512,
	.rate_min		= 5512,
	.rate_max		= 48000,
	.channels_min		= 1,
	.channels_max		= 2,
	.buffer_bytes_max	= 64 * 1024,
	.period_bytes_min	= 1,
	.period_bytes_max	= DBRI_TD_MAXCNT,
	.periods_min		= 1,
	.periods_max		= 1024,
पूर्ण;

अटल पूर्णांक snd_hw_rule_क्रमmat(काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params,
				SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *f = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_mask fmt;

	snd_mask_any(&fmt);
	अगर (c->min > 1) अणु
		fmt.bits[0] &= SNDRV_PCM_FMTBIT_S16_BE;
		वापस snd_mask_refine(f, &fmt);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_hw_rule_channels(काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params,
				SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *f = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_पूर्णांकerval ch;

	snd_पूर्णांकerval_any(&ch);
	अगर (!(f->bits[0] & SNDRV_PCM_FMTBIT_S16_BE)) अणु
		ch.min = 1;
		ch.max = 1;
		ch.पूर्णांकeger = 1;
		वापस snd_पूर्णांकerval_refine(c, &ch);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_dbri_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dbri *dbri = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा dbri_streaminfo *info = DBRI_STREAM(dbri, substream);
	अचिन्हित दीर्घ flags;

	dprपूर्णांकk(D_USR, "open audio output.\n");
	runसमय->hw = snd_dbri_pcm_hw;

	spin_lock_irqsave(&dbri->lock, flags);
	info->substream = substream;
	info->offset = 0;
	info->dvma_buffer = 0;
	info->pipe = -1;
	spin_unlock_irqrestore(&dbri->lock, flags);

	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			    snd_hw_rule_क्रमmat, शून्य, SNDRV_PCM_HW_PARAM_FORMAT,
			    -1);
	snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_FORMAT,
			    snd_hw_rule_channels, शून्य,
			    SNDRV_PCM_HW_PARAM_CHANNELS,
			    -1);

	cs4215_खोलो(dbri);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_dbri_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dbri *dbri = snd_pcm_substream_chip(substream);
	काष्ठा dbri_streaminfo *info = DBRI_STREAM(dbri, substream);

	dprपूर्णांकk(D_USR, "close audio output.\n");
	info->substream = शून्य;
	info->offset = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_dbri_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_dbri *dbri = snd_pcm_substream_chip(substream);
	काष्ठा dbri_streaminfo *info = DBRI_STREAM(dbri, substream);
	पूर्णांक direction;
	पूर्णांक ret;

	/* set sampling rate, audio क्रमmat and number of channels */
	ret = cs4215_prepare(dbri, params_rate(hw_params),
			     params_क्रमmat(hw_params),
			     params_channels(hw_params));
	अगर (ret != 0)
		वापस ret;

	/* hw_params can get called multiple बार. Only map the DMA once.
	 */
	अगर (info->dvma_buffer == 0) अणु
		अगर (DBRI_STREAMNO(substream) == DBRI_PLAY)
			direction = DMA_TO_DEVICE;
		अन्यथा
			direction = DMA_FROM_DEVICE;

		info->dvma_buffer =
			dma_map_single(&dbri->op->dev,
				       runसमय->dma_area,
				       params_buffer_bytes(hw_params),
				       direction);
	पूर्ण

	direction = params_buffer_bytes(hw_params);
	dprपूर्णांकk(D_USR, "hw_params: %d bytes, dvma=%x\n",
		direction, info->dvma_buffer);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_dbri_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dbri *dbri = snd_pcm_substream_chip(substream);
	काष्ठा dbri_streaminfo *info = DBRI_STREAM(dbri, substream);
	पूर्णांक direction;

	dprपूर्णांकk(D_USR, "hw_free.\n");

	/* hw_मुक्त can get called multiple बार. Only unmap the DMA once.
	 */
	अगर (info->dvma_buffer) अणु
		अगर (DBRI_STREAMNO(substream) == DBRI_PLAY)
			direction = DMA_TO_DEVICE;
		अन्यथा
			direction = DMA_FROM_DEVICE;

		dma_unmap_single(&dbri->op->dev, info->dvma_buffer,
				 substream->runसमय->buffer_size, direction);
		info->dvma_buffer = 0;
	पूर्ण
	अगर (info->pipe != -1) अणु
		reset_pipe(dbri, info->pipe);
		info->pipe = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_dbri_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dbri *dbri = snd_pcm_substream_chip(substream);
	काष्ठा dbri_streaminfo *info = DBRI_STREAM(dbri, substream);
	पूर्णांक ret;

	info->size = snd_pcm_lib_buffer_bytes(substream);
	अगर (DBRI_STREAMNO(substream) == DBRI_PLAY)
		info->pipe = 4;	/* Send pipe */
	अन्यथा
		info->pipe = 6;	/* Receive pipe */

	spin_lock_irq(&dbri->lock);
	info->offset = 0;

	/* Setup the all the transmit/receive descriptors to cover the
	 * whole DMA buffer.
	 */
	ret = setup_descs(dbri, DBRI_STREAMNO(substream),
			  snd_pcm_lib_period_bytes(substream));

	spin_unlock_irq(&dbri->lock);

	dprपूर्णांकk(D_USR, "prepare audio output. %d bytes\n", info->size);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_dbri_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_dbri *dbri = snd_pcm_substream_chip(substream);
	काष्ठा dbri_streaminfo *info = DBRI_STREAM(dbri, substream);
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		dprपूर्णांकk(D_USR, "start audio, period is %d bytes\n",
			(पूर्णांक)snd_pcm_lib_period_bytes(substream));
		/* Re-submit the TDs. */
		xmit_descs(dbri);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		dprपूर्णांकk(D_USR, "stop audio.\n");
		reset_pipe(dbri, info->pipe);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t snd_dbri_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_dbri *dbri = snd_pcm_substream_chip(substream);
	काष्ठा dbri_streaminfo *info = DBRI_STREAM(dbri, substream);
	snd_pcm_uframes_t ret;

	ret = bytes_to_frames(substream->runसमय, info->offset)
		% substream->runसमय->buffer_size;
	dprपूर्णांकk(D_USR, "I/O pointer: %ld frames of %ld.\n",
		ret, substream->runसमय->buffer_size);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_dbri_ops = अणु
	.खोलो = snd_dbri_खोलो,
	.बंद = snd_dbri_बंद,
	.hw_params = snd_dbri_hw_params,
	.hw_मुक्त = snd_dbri_hw_मुक्त,
	.prepare = snd_dbri_prepare,
	.trigger = snd_dbri_trigger,
	.poपूर्णांकer = snd_dbri_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_dbri_pcm(काष्ठा snd_card *card)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(card,
			       /* ID */		    "sun_dbri",
			       /* device */	    0,
			       /* playback count */ 1,
			       /* capture count */  1, &pcm)) < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_dbri_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_dbri_ops);

	pcm->निजी_data = card->निजी_data;
	pcm->info_flags = 0;
	म_नकल(pcm->name, card->लघुname);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य, 64 * 1024, 64 * 1024);
	वापस 0;
पूर्ण

/*****************************************************************************
			Mixer पूर्णांकerface
*****************************************************************************/

अटल पूर्णांक snd_cs4215_info_volume(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	अगर (kcontrol->निजी_value == DBRI_PLAY)
		uinfo->value.पूर्णांकeger.max = DBRI_MAX_VOLUME;
	अन्यथा
		uinfo->value.पूर्णांकeger.max = DBRI_MAX_GAIN;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4215_get_volume(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_dbri *dbri = snd_kcontrol_chip(kcontrol);
	काष्ठा dbri_streaminfo *info;

	अगर (snd_BUG_ON(!dbri))
		वापस -EINVAL;
	info = &dbri->stream_info[kcontrol->निजी_value];

	ucontrol->value.पूर्णांकeger.value[0] = info->left_gain;
	ucontrol->value.पूर्णांकeger.value[1] = info->right_gain;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4215_put_volume(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_dbri *dbri = snd_kcontrol_chip(kcontrol);
	काष्ठा dbri_streaminfo *info =
				&dbri->stream_info[kcontrol->निजी_value];
	अचिन्हित पूर्णांक vol[2];
	पूर्णांक changed = 0;

	vol[0] = ucontrol->value.पूर्णांकeger.value[0];
	vol[1] = ucontrol->value.पूर्णांकeger.value[1];
	अगर (kcontrol->निजी_value == DBRI_PLAY) अणु
		अगर (vol[0] > DBRI_MAX_VOLUME || vol[1] > DBRI_MAX_VOLUME)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (vol[0] > DBRI_MAX_GAIN || vol[1] > DBRI_MAX_GAIN)
			वापस -EINVAL;
	पूर्ण

	अगर (info->left_gain != vol[0]) अणु
		info->left_gain = vol[0];
		changed = 1;
	पूर्ण
	अगर (info->right_gain != vol[1]) अणु
		info->right_gain = vol[1];
		changed = 1;
	पूर्ण
	अगर (changed) अणु
		/* First mute outमाला_दो, and रुको 1/8000 sec (125 us)
		 * to make sure this takes.  This aव्योमs clicking noises.
		 */
		cs4215_setdata(dbri, 1);
		udelay(125);
		cs4215_setdata(dbri, 0);
	पूर्ण
	वापस changed;
पूर्ण

अटल पूर्णांक snd_cs4215_info_single(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = (mask == 1) ?
	    SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4215_get_single(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_dbri *dbri = snd_kcontrol_chip(kcontrol);
	पूर्णांक elem = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 1;

	अगर (snd_BUG_ON(!dbri))
		वापस -EINVAL;

	अगर (elem < 4)
		ucontrol->value.पूर्णांकeger.value[0] =
		    (dbri->mm.data[elem] >> shअगरt) & mask;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] =
		    (dbri->mm.ctrl[elem - 4] >> shअगरt) & mask;

	अगर (invert == 1)
		ucontrol->value.पूर्णांकeger.value[0] =
		    mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4215_put_single(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_dbri *dbri = snd_kcontrol_chip(kcontrol);
	पूर्णांक elem = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 1;
	पूर्णांक changed = 0;
	अचिन्हित लघु val;

	अगर (snd_BUG_ON(!dbri))
		वापस -EINVAL;

	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert == 1)
		val = mask - val;
	val <<= shअगरt;

	अगर (elem < 4) अणु
		dbri->mm.data[elem] = (dbri->mm.data[elem] &
				       ~(mask << shअगरt)) | val;
		changed = (val != dbri->mm.data[elem]);
	पूर्ण अन्यथा अणु
		dbri->mm.ctrl[elem - 4] = (dbri->mm.ctrl[elem - 4] &
					   ~(mask << shअगरt)) | val;
		changed = (val != dbri->mm.ctrl[elem - 4]);
	पूर्ण

	dprपूर्णांकk(D_GEN, "put_single: mask=0x%x, changed=%d, "
		"mixer-value=%ld, mm-value=0x%x\n",
		mask, changed, ucontrol->value.पूर्णांकeger.value[0],
		dbri->mm.data[elem & 3]);

	अगर (changed) अणु
		/* First mute outमाला_दो, and रुको 1/8000 sec (125 us)
		 * to make sure this takes.  This aव्योमs clicking noises.
		 */
		cs4215_setdata(dbri, 1);
		udelay(125);
		cs4215_setdata(dbri, 0);
	पूर्ण
	वापस changed;
पूर्ण

/* Entries 0-3 map to the 4 data बारlots, entries 4-7 map to the 4 control
   बारlots. Shअगरt is the bit offset in the बारlot, mask defines the
   number of bits. invert is a boolean क्रम use with attenuation.
 */
#घोषणा CS4215_SINGLE(xname, entry, shअगरt, mask, invert)	\
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),		\
  .info = snd_cs4215_info_single,				\
  .get = snd_cs4215_get_single, .put = snd_cs4215_put_single,	\
  .निजी_value = (entry) | ((shअगरt) << 8) | ((mask) << 16) |	\
			((invert) << 24) पूर्ण,

अटल स्थिर काष्ठा snd_kcontrol_new dbri_controls[] = अणु
	अणु
	 .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	 .name  = "Playback Volume",
	 .info  = snd_cs4215_info_volume,
	 .get   = snd_cs4215_get_volume,
	 .put   = snd_cs4215_put_volume,
	 .निजी_value = DBRI_PLAY,
	 पूर्ण,
	CS4215_SINGLE("Headphone switch", 0, 7, 1, 0)
	CS4215_SINGLE("Line out switch", 0, 6, 1, 0)
	CS4215_SINGLE("Speaker switch", 1, 6, 1, 0)
	अणु
	 .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	 .name  = "Capture Volume",
	 .info  = snd_cs4215_info_volume,
	 .get   = snd_cs4215_get_volume,
	 .put   = snd_cs4215_put_volume,
	 .निजी_value = DBRI_REC,
	 पूर्ण,
	/* FIXME: mic/line चयन */
	CS4215_SINGLE("Line in switch", 2, 4, 1, 0)
	CS4215_SINGLE("High Pass Filter switch", 5, 7, 1, 0)
	CS4215_SINGLE("Monitor Volume", 3, 4, 0xf, 1)
	CS4215_SINGLE("Mic boost", 4, 4, 1, 1)
पूर्ण;

अटल पूर्णांक snd_dbri_mixer(काष्ठा snd_card *card)
अणु
	पूर्णांक idx, err;
	काष्ठा snd_dbri *dbri;

	अगर (snd_BUG_ON(!card || !card->निजी_data))
		वापस -EINVAL;
	dbri = card->निजी_data;

	म_नकल(card->mixername, card->लघुname);

	क्रम (idx = 0; idx < ARRAY_SIZE(dbri_controls); idx++) अणु
		err = snd_ctl_add(card,
				snd_ctl_new1(&dbri_controls[idx], dbri));
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (idx = DBRI_REC; idx < DBRI_NO_STREAMS; idx++) अणु
		dbri->stream_info[idx].left_gain = 0;
		dbri->stream_info[idx].right_gain = 0;
	पूर्ण

	वापस 0;
पूर्ण

/****************************************************************************
			/proc पूर्णांकerface
****************************************************************************/
अटल व्योम dbri_regs_पढ़ो(काष्ठा snd_info_entry *entry,
			   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_dbri *dbri = entry->निजी_data;

	snd_iम_लिखो(buffer, "REG0: 0x%x\n", sbus_पढ़ोl(dbri->regs + REG0));
	snd_iम_लिखो(buffer, "REG2: 0x%x\n", sbus_पढ़ोl(dbri->regs + REG2));
	snd_iम_लिखो(buffer, "REG8: 0x%x\n", sbus_पढ़ोl(dbri->regs + REG8));
	snd_iम_लिखो(buffer, "REG9: 0x%x\n", sbus_पढ़ोl(dbri->regs + REG9));
पूर्ण

#अगर_घोषित DBRI_DEBUG
अटल व्योम dbri_debug_पढ़ो(काष्ठा snd_info_entry *entry,
			    काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_dbri *dbri = entry->निजी_data;
	पूर्णांक pipe;
	snd_iम_लिखो(buffer, "debug=%d\n", dbri_debug);

	क्रम (pipe = 0; pipe < 32; pipe++) अणु
		अगर (pipe_active(dbri, pipe)) अणु
			काष्ठा dbri_pipe *pptr = &dbri->pipes[pipe];
			snd_iम_लिखो(buffer,
				    "Pipe %d: %s SDP=0x%x desc=%d, "
				    "len=%d next %d\n",
				    pipe,
				   (pptr->sdp & D_SDP_TO_SER) ? "output" :
								 "input",
				    pptr->sdp, pptr->desc,
				    pptr->length, pptr->nextpipe);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम snd_dbri_proc(काष्ठा snd_card *card)
अणु
	काष्ठा snd_dbri *dbri = card->निजी_data;

	snd_card_ro_proc_new(card, "regs", dbri, dbri_regs_पढ़ो);
#अगर_घोषित DBRI_DEBUG
	snd_card_ro_proc_new(card, "debug", dbri, dbri_debug_पढ़ो);
#पूर्ण_अगर
पूर्ण

/*
****************************************************************************
**************************** Initialization ********************************
****************************************************************************
*/
अटल व्योम snd_dbri_मुक्त(काष्ठा snd_dbri *dbri);

अटल पूर्णांक snd_dbri_create(काष्ठा snd_card *card,
			   काष्ठा platक्रमm_device *op,
			   पूर्णांक irq, पूर्णांक dev)
अणु
	काष्ठा snd_dbri *dbri = card->निजी_data;
	पूर्णांक err;

	spin_lock_init(&dbri->lock);
	dbri->op = op;
	dbri->irq = irq;

	dbri->dma = dma_alloc_coherent(&op->dev, माप(काष्ठा dbri_dma),
				       &dbri->dma_dvma, GFP_KERNEL);
	अगर (!dbri->dma)
		वापस -ENOMEM;

	dprपूर्णांकk(D_GEN, "DMA Cmd Block 0x%p (%pad)\n",
		dbri->dma, dbri->dma_dvma);

	/* Map the रेजिस्टरs पूर्णांकo memory. */
	dbri->regs_size = resource_size(&op->resource[0]);
	dbri->regs = of_ioremap(&op->resource[0], 0,
				dbri->regs_size, "DBRI Registers");
	अगर (!dbri->regs) अणु
		prपूर्णांकk(KERN_ERR "DBRI: could not allocate registers\n");
		dma_मुक्त_coherent(&op->dev, माप(काष्ठा dbri_dma),
				  (व्योम *)dbri->dma, dbri->dma_dvma);
		वापस -EIO;
	पूर्ण

	err = request_irq(dbri->irq, snd_dbri_पूर्णांकerrupt, IRQF_SHARED,
			  "DBRI audio", dbri);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "DBRI: Can't get irq %d\n", dbri->irq);
		of_iounmap(&op->resource[0], dbri->regs, dbri->regs_size);
		dma_मुक्त_coherent(&op->dev, माप(काष्ठा dbri_dma),
				  (व्योम *)dbri->dma, dbri->dma_dvma);
		वापस err;
	पूर्ण

	/* Do low level initialization of the DBRI and CS4215 chips */
	dbri_initialize(dbri);
	err = cs4215_init(dbri);
	अगर (err) अणु
		snd_dbri_मुक्त(dbri);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम snd_dbri_मुक्त(काष्ठा snd_dbri *dbri)
अणु
	dprपूर्णांकk(D_GEN, "snd_dbri_free\n");
	dbri_reset(dbri);

	अगर (dbri->irq)
		मुक्त_irq(dbri->irq, dbri);

	अगर (dbri->regs)
		of_iounmap(&dbri->op->resource[0], dbri->regs, dbri->regs_size);

	अगर (dbri->dma)
		dma_मुक्त_coherent(&dbri->op->dev,
				  माप(काष्ठा dbri_dma),
				  (व्योम *)dbri->dma, dbri->dma_dvma);
पूर्ण

अटल पूर्णांक dbri_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा snd_dbri *dbri;
	काष्ठा resource *rp;
	काष्ठा snd_card *card;
	अटल पूर्णांक dev = 0;
	पूर्णांक irq;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	irq = op->archdata.irqs[0];
	अगर (irq <= 0) अणु
		prपूर्णांकk(KERN_ERR "DBRI-%d: No IRQ.\n", dev);
		वापस -ENODEV;
	पूर्ण

	err = snd_card_new(&op->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा snd_dbri), &card);
	अगर (err < 0)
		वापस err;

	म_नकल(card->driver, "DBRI");
	म_नकल(card->लघुname, "Sun DBRI");
	rp = &op->resource[0];
	प्र_लिखो(card->दीर्घname, "%s at 0x%02lx:0x%016Lx, irq %d",
		card->लघुname,
		rp->flags & 0xffL, (अचिन्हित दीर्घ दीर्घ)rp->start, irq);

	err = snd_dbri_create(card, op, irq, dev);
	अगर (err < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	dbri = card->निजी_data;
	err = snd_dbri_pcm(card);
	अगर (err < 0)
		जाओ _err;

	err = snd_dbri_mixer(card);
	अगर (err < 0)
		जाओ _err;

	/* /proc file handling */
	snd_dbri_proc(card);
	dev_set_drvdata(&op->dev, card);

	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ _err;

	prपूर्णांकk(KERN_INFO "audio%d at %p (irq %d) is DBRI(%c)+CS4215(%d)\n",
	       dev, dbri->regs,
	       dbri->irq, op->dev.of_node->name[9], dbri->mm.version);
	dev++;

	वापस 0;

_err:
	snd_dbri_मुक्त(dbri);
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल पूर्णांक dbri_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(&op->dev);

	snd_dbri_मुक्त(card->निजी_data);
	snd_card_मुक्त(card);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dbri_match[] = अणु
	अणु
		.name = "SUNW,DBRIe",
	पूर्ण,
	अणु
		.name = "SUNW,DBRIf",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dbri_match);

अटल काष्ठा platक्रमm_driver dbri_sbus_driver = अणु
	.driver = अणु
		.name = "dbri",
		.of_match_table = dbri_match,
	पूर्ण,
	.probe		= dbri_probe,
	.हटाओ		= dbri_हटाओ,
पूर्ण;

module_platक्रमm_driver(dbri_sbus_driver);
