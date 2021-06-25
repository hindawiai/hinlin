<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम ESS Maestro 1/2/2E Sound Card (started 21.8.99)
 *  Copyright (c) by Matze Braun <MatzeBraun@gmx.de>.
 *                   Takashi Iwai <tiwai@suse.de>
 *                  
 *  Most of the driver code comes from Zach Brown(zab@redhat.com)
 *	Alan Cox OSS Driver
 *  Rewritted from card-es1938.c source.
 *
 *  TODO:
 *   Perhaps Synth
 *
 *  Notes from Zach Brown about the driver code
 *
 *  Hardware Description
 *
 *	A working Maestro setup contains the Maestro chip wired to a 
 *	codec or 2.  In the Maestro we have the APUs, the ASSP, and the
 *	Wavecache.  The APUs can be though of as भव audio routing
 *	channels.  They can take data from a number of sources and perक्रमm
 *	basic encodings of the data.  The wavecache is a storehouse क्रम
 *	PCM data.  Typically it deals with PCI and पूर्णांकerracts with the
 *	APUs.  The ASSP is a wacky DSP like device that ESS is loth
 *	to release करोcs on.  Thankfully it isn't required on the Maestro
 *	until you start करोing insane things like FM emulation and surround
 *	encoding.  The codecs are almost always AC-97 compliant codecs, 
 *	but it appears that early Maestros may have had PT101 (an ESS
 *	part?) wired to them.  The only real dअगरference in the Maestro
 *	families is बाह्यal goop like करोcking capability, memory क्रम
 *	the ASSP, and initialization dअगरferences.
 *
 *  Driver Operation
 *
 *	We only drive the APU/Wavecache as typical DACs and drive the
 *	mixers in the codecs.  There are 64 APUs.  We assign 6 to each
 *	/dev/dsp? device.  2 channels क्रम output, and 4 channels क्रम
 *	input.
 *
 *	Each APU can करो a number of things, but we only really use
 *	3 basic functions.  For playback we use them to convert PCM
 *	data fetched over PCI by the wavecahche पूर्णांकo analog data that
 *	is handed to the codec.  One APU क्रम mono, and a pair क्रम stereo.
 *	When in stereo, the combination of smarts in the APU and Wavecache
 *	decide which wavecache माला_लो the left or right channel.
 *
 *	For record we still use the old overly mono प्रणाली.  For each in
 *	coming channel the data comes in from the codec, through a 'input'
 *	APU, through another rate converter APU, and then पूर्णांकo memory via
 *	the wavecache and PCI.  If its stereo, we mash it back पूर्णांकo LRLR in
 *	software.  The pass between the 2 APUs is supposedly what requires us
 *	to have a 512 byte buffer sitting around in wavecache/memory.
 *
 *	The wavecache makes our lअगरe even more fun.  First off, it can
 *	only address the first 28 bits of PCI address space, making it
 *	useless on quite a few architectures.  Secondly, its insane.
 *	It claims to fetch from 4 regions of PCI space, each 4 meg in length.
 *	But that करोesn't really work.  You can only use 1 region.  So all our
 *	allocations have to be in 4meg of each other.  Booo.  Hiss.
 *	So we have a module parameter, dsps_order, that is the order of
 *	the number of dsps to provide.  All their buffer space is allocated
 *	on खोलो समय.  The sonicvibes OSS routines we inherited really want
 *	घातer of 2 buffers, so we have all those next to each other, then
 *	512 byte regions क्रम the recording wavecaches.  This ends up
 *	wasting quite a bit of memory.  The only fixes I can see would be 
 *	getting a kernel allocator that could work in zones, or figuring out
 *	just how to coerce the WP पूर्णांकo करोing what we want.
 *
 *	The indirection of the various रेजिस्टरs means we have to spinlock
 *	nearly all रेजिस्टर accesses.  We have the मुख्य रेजिस्टर indirection
 *	like the wave cache, maestro रेजिस्टरs, etc.  Then we have beasts
 *	like the APU पूर्णांकerface that is indirect रेजिस्टरs gotten at through
 *	the मुख्य maestro indirection.  Ouch.  We spinlock around the actual
 *	ports on a per card basis.  This means spinlock activity at each IO
 *	operation, but the only IO operation clusters are in non critical 
 *	paths and it makes the code far easier to follow.  Interrupts are
 *	blocked जबतक holding the locks because the पूर्णांक handler has to
 *	get at some of them :(.  The mixer पूर्णांकerface करोesn't, however.
 *	We also have an OSS state lock that is thrown around in a few
 *	places.
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/input.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>

#अगर_घोषित CONFIG_SND_ES1968_RADIO
#समावेश <media/drv-पूर्णांकf/tea575x.h>
#पूर्ण_अगर

#घोषणा CARD_NAME "ESS Maestro1/2"
#घोषणा DRIVER_NAME "ES1968"

MODULE_DESCRIPTION("ESS Maestro");
MODULE_LICENSE("GPL");

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK 1
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 1-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल पूर्णांक total_bufsize[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1024 पूर्ण;
अटल पूर्णांक pcm_substreams_p[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 4 पूर्ण;
अटल पूर्णांक pcm_substreams_c[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 1 पूर्ण;
अटल पूर्णांक घड़ी[SNDRV_CARDS];
अटल पूर्णांक use_pm[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 2पूर्ण;
अटल पूर्णांक enable_mpu[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = 2पूर्ण;
#अगर_घोषित SUPPORT_JOYSTICK
अटल bool joystick[SNDRV_CARDS];
#पूर्ण_अगर
अटल पूर्णांक radio_nr[SNDRV_CARDS] = अणु[0 ... (SNDRV_CARDS - 1)] = -1पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for " CARD_NAME " soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for " CARD_NAME " soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable " CARD_NAME " soundcard.");
module_param_array(total_bufsize, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(total_bufsize, "Total buffer size in kB.");
module_param_array(pcm_substreams_p, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_substreams_p, "PCM Playback substreams for " CARD_NAME " soundcard.");
module_param_array(pcm_substreams_c, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(pcm_substreams_c, "PCM Capture substreams for " CARD_NAME " soundcard.");
module_param_array(घड़ी, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(घड़ी, "Clock on " CARD_NAME " soundcard.  (0 = auto-detect)");
module_param_array(use_pm, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(use_pm, "Toggle power-management.  (0 = off, 1 = on, 2 = auto)");
module_param_array(enable_mpu, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(enable_mpu, "Enable MPU401.  (0 = off, 1 = on, 2 = auto)");
#अगर_घोषित SUPPORT_JOYSTICK
module_param_array(joystick, bool, शून्य, 0444);
MODULE_PARM_DESC(joystick, "Enable joystick.");
#पूर्ण_अगर
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Radio device numbers");



#घोषणा NR_APUS			64
#घोषणा NR_APU_REGS		16

/* NEC Versas ? */
#घोषणा NEC_VERSA_SUBID1	0x80581033
#घोषणा NEC_VERSA_SUBID2	0x803c1033

/* Mode Flags */
#घोषणा ESS_FMT_STEREO     	0x01
#घोषणा ESS_FMT_16BIT      	0x02

#घोषणा DAC_RUNNING		1
#घोषणा ADC_RUNNING		2

/* Values क्रम the ESM_LEGACY_AUDIO_CONTROL */

#घोषणा ESS_DISABLE_AUDIO	0x8000
#घोषणा ESS_ENABLE_SERIAL_IRQ	0x4000
#घोषणा IO_ADRESS_ALIAS		0x0020
#घोषणा MPU401_IRQ_ENABLE	0x0010
#घोषणा MPU401_IO_ENABLE	0x0008
#घोषणा GAME_IO_ENABLE		0x0004
#घोषणा FM_IO_ENABLE		0x0002
#घोषणा SB_IO_ENABLE		0x0001

/* Values क्रम the ESM_CONFIG_A */

#घोषणा PIC_SNOOP1		0x4000
#घोषणा PIC_SNOOP2		0x2000
#घोषणा SAFEGUARD		0x0800
#घोषणा DMA_CLEAR		0x0700
#घोषणा DMA_DDMA		0x0000
#घोषणा DMA_TDMA		0x0100
#घोषणा DMA_PCPCI		0x0200
#घोषणा POST_WRITE		0x0080
#घोषणा PCI_TIMING		0x0040
#घोषणा SWAP_LR			0x0020
#घोषणा SUBTR_DECODE		0x0002

/* Values क्रम the ESM_CONFIG_B */

#घोषणा SPDIF_CONFB		0x0100
#घोषणा HWV_CONFB		0x0080
#घोषणा DEBOUNCE		0x0040
#घोषणा GPIO_CONFB		0x0020
#घोषणा CHI_CONFB		0x0010
#घोषणा IDMA_CONFB		0x0008	/*unकरोc */
#घोषणा MIDI_FIX		0x0004	/*unकरोc */
#घोषणा IRQ_TO_ISA		0x0001	/*unकरोc */

/* Values क्रम Ring Bus Control B */
#घोषणा	RINGB_2CODEC_ID_MASK	0x0003
#घोषणा RINGB_DIS_VALIDATION	0x0008
#घोषणा RINGB_EN_SPDIF		0x0010
#घोषणा	RINGB_EN_2CODEC		0x0020
#घोषणा RINGB_SING_BIT_DUAL	0x0040

/* ****Port Addresses**** */

/*   Write & Read */
#घोषणा ESM_INDEX		0x02
#घोषणा ESM_DATA		0x00

/*   AC97 + RingBus */
#घोषणा ESM_AC97_INDEX		0x30
#घोषणा	ESM_AC97_DATA		0x32
#घोषणा ESM_RING_BUS_DEST	0x34
#घोषणा ESM_RING_BUS_CONTR_A	0x36
#घोषणा ESM_RING_BUS_CONTR_B	0x38
#घोषणा ESM_RING_BUS_SDO	0x3A

/*   WaveCache*/
#घोषणा WC_INDEX		0x10
#घोषणा WC_DATA			0x12
#घोषणा WC_CONTROL		0x14

/*   ASSP*/
#घोषणा ASSP_INDEX		0x80
#घोषणा ASSP_MEMORY		0x82
#घोषणा ASSP_DATA		0x84
#घोषणा ASSP_CONTROL_A		0xA2
#घोषणा ASSP_CONTROL_B		0xA4
#घोषणा ASSP_CONTROL_C		0xA6
#घोषणा ASSP_HOSTW_INDEX	0xA8
#घोषणा ASSP_HOSTW_DATA		0xAA
#घोषणा ASSP_HOSTW_IRQ		0xAC
/* Midi */
#घोषणा ESM_MPU401_PORT		0x98
/* Others */
#घोषणा ESM_PORT_HOST_IRQ	0x18

#घोषणा IDR0_DATA_PORT		0x00
#घोषणा IDR1_CRAM_POINTER	0x01
#घोषणा IDR2_CRAM_DATA		0x02
#घोषणा IDR3_WAVE_DATA		0x03
#घोषणा IDR4_WAVE_PTR_LOW	0x04
#घोषणा IDR5_WAVE_PTR_HI	0x05
#घोषणा IDR6_TIMER_CTRL		0x06
#घोषणा IDR7_WAVE_ROMRAM	0x07

#घोषणा WRITEABLE_MAP		0xEFFFFF
#घोषणा READABLE_MAP		0x64003F

/* PCI Register */

#घोषणा ESM_LEGACY_AUDIO_CONTROL 0x40
#घोषणा ESM_ACPI_COMMAND	0x54
#घोषणा ESM_CONFIG_A		0x50
#घोषणा ESM_CONFIG_B		0x52
#घोषणा ESM_DDMA		0x60

/* Bob Bits */
#घोषणा ESM_BOB_ENABLE		0x0001
#घोषणा ESM_BOB_START		0x0001

/* Host IRQ Control Bits */
#घोषणा ESM_RESET_MAESTRO	0x8000
#घोषणा ESM_RESET_सूचीECTSOUND   0x4000
#घोषणा ESM_HIRQ_ClkRun		0x0100
#घोषणा ESM_HIRQ_HW_VOLUME	0x0040
#घोषणा ESM_HIRQ_HARPO		0x0030	/* What's that? */
#घोषणा ESM_HIRQ_ASSP		0x0010
#घोषणा	ESM_HIRQ_DSIE		0x0004
#घोषणा ESM_HIRQ_MPU401		0x0002
#घोषणा ESM_HIRQ_SB		0x0001

/* Host IRQ Status Bits */
#घोषणा ESM_MPU401_IRQ		0x02
#घोषणा ESM_SB_IRQ		0x01
#घोषणा ESM_SOUND_IRQ		0x04
#घोषणा	ESM_ASSP_IRQ		0x10
#घोषणा ESM_HWVOL_IRQ		0x40

#घोषणा ESS_SYSCLK		50000000
#घोषणा ESM_BOB_FREQ 		200
#घोषणा ESM_BOB_FREQ_MAX	800

#घोषणा ESM_FREQ_ESM1  		(49152000L / 1024L)	/* शेष rate 48000 */
#घोषणा ESM_FREQ_ESM2  		(50000000L / 1024L)

/* APU Modes: reg 0x00, bit 4-7 */
#घोषणा ESM_APU_MODE_SHIFT	4
#घोषणा ESM_APU_MODE_MASK	(0xf << 4)
#घोषणा	ESM_APU_OFF		0x00
#घोषणा	ESM_APU_16BITLINEAR	0x01	/* 16-Bit Linear Sample Player */
#घोषणा	ESM_APU_16BITSTEREO	0x02	/* 16-Bit Stereo Sample Player */
#घोषणा	ESM_APU_8BITLINEAR	0x03	/* 8-Bit Linear Sample Player */
#घोषणा	ESM_APU_8BITSTEREO	0x04	/* 8-Bit Stereo Sample Player */
#घोषणा	ESM_APU_8BITDIFF	0x05	/* 8-Bit Dअगरferential Sample Playrer */
#घोषणा	ESM_APU_DIGITALDELAY	0x06	/* Digital Delay Line */
#घोषणा	ESM_APU_DUALTAP		0x07	/* Dual Tap Reader */
#घोषणा	ESM_APU_CORRELATOR	0x08	/* Correlator */
#घोषणा	ESM_APU_INPUTMIXER	0x09	/* Input Mixer */
#घोषणा	ESM_APU_WAVETABLE	0x0A	/* Wave Table Mode */
#घोषणा	ESM_APU_SRCONVERTOR	0x0B	/* Sample Rate Convertor */
#घोषणा	ESM_APU_16BITPINGPONG	0x0C	/* 16-Bit Ping-Pong Sample Player */
#घोषणा	ESM_APU_RESERVED1	0x0D	/* Reserved 1 */
#घोषणा	ESM_APU_RESERVED2	0x0E	/* Reserved 2 */
#घोषणा	ESM_APU_RESERVED3	0x0F	/* Reserved 3 */

/* reg 0x00 */
#घोषणा ESM_APU_FILTER_Q_SHIFT		0
#घोषणा ESM_APU_FILTER_Q_MASK		(3 << 0)
/* APU Filtey Q Control */
#घोषणा ESM_APU_FILTER_LESSQ	0x00
#घोषणा ESM_APU_FILTER_MOREQ	0x03

#घोषणा ESM_APU_FILTER_TYPE_SHIFT	2
#घोषणा ESM_APU_FILTER_TYPE_MASK	(3 << 2)
#घोषणा ESM_APU_ENV_TYPE_SHIFT		8
#घोषणा ESM_APU_ENV_TYPE_MASK		(3 << 8)
#घोषणा ESM_APU_ENV_STATE_SHIFT		10
#घोषणा ESM_APU_ENV_STATE_MASK		(3 << 10)
#घोषणा ESM_APU_END_CURVE		(1 << 12)
#घोषणा ESM_APU_INT_ON_LOOP		(1 << 13)
#घोषणा ESM_APU_DMA_ENABLE		(1 << 14)

/* reg 0x02 */
#घोषणा ESM_APU_SUBMIX_GROUP_SHIRT	0
#घोषणा ESM_APU_SUBMIX_GROUP_MASK	(7 << 0)
#घोषणा ESM_APU_SUBMIX_MODE		(1 << 3)
#घोषणा ESM_APU_6dB			(1 << 4)
#घोषणा ESM_APU_DUAL_EFFECT		(1 << 5)
#घोषणा ESM_APU_EFFECT_CHANNELS_SHIFT	6
#घोषणा ESM_APU_EFFECT_CHANNELS_MASK	(3 << 6)

/* reg 0x03 */
#घोषणा ESM_APU_STEP_SIZE_MASK		0x0fff

/* reg 0x04 */
#घोषणा ESM_APU_PHASE_SHIFT		0
#घोषणा ESM_APU_PHASE_MASK		(0xff << 0)
#घोषणा ESM_APU_WAVE64K_PAGE_SHIFT	8	/* most 8bit of wave start offset */
#घोषणा ESM_APU_WAVE64K_PAGE_MASK	(0xff << 8)

/* reg 0x05 - wave start offset */
/* reg 0x06 - wave end offset */
/* reg 0x07 - wave loop length */

/* reg 0x08 */
#घोषणा ESM_APU_EFFECT_GAIN_SHIFT	0
#घोषणा ESM_APU_EFFECT_GAIN_MASK	(0xff << 0)
#घोषणा ESM_APU_TREMOLO_DEPTH_SHIFT	8
#घोषणा ESM_APU_TREMOLO_DEPTH_MASK	(0xf << 8)
#घोषणा ESM_APU_TREMOLO_RATE_SHIFT	12
#घोषणा ESM_APU_TREMOLO_RATE_MASK	(0xf << 12)

/* reg 0x09 */
/* bit 0-7 amplitude dest? */
#घोषणा ESM_APU_AMPLITUDE_NOW_SHIFT	8
#घोषणा ESM_APU_AMPLITUDE_NOW_MASK	(0xff << 8)

/* reg 0x0a */
#घोषणा ESM_APU_POLAR_PAN_SHIFT		0
#घोषणा ESM_APU_POLAR_PAN_MASK		(0x3f << 0)
/* Polar Pan Control */
#घोषणा	ESM_APU_PAN_CENTER_CIRCLE		0x00
#घोषणा	ESM_APU_PAN_MIDDLE_RADIUS		0x01
#घोषणा	ESM_APU_PAN_OUTSIDE_RADIUS		0x02

#घोषणा ESM_APU_FILTER_TUNING_SHIFT	8
#घोषणा ESM_APU_FILTER_TUNING_MASK	(0xff << 8)

/* reg 0x0b */
#घोषणा ESM_APU_DATA_SRC_A_SHIFT	0
#घोषणा ESM_APU_DATA_SRC_A_MASK		(0x7f << 0)
#घोषणा ESM_APU_INV_POL_A		(1 << 7)
#घोषणा ESM_APU_DATA_SRC_B_SHIFT	8
#घोषणा ESM_APU_DATA_SRC_B_MASK		(0x7f << 8)
#घोषणा ESM_APU_INV_POL_B		(1 << 15)

#घोषणा ESM_APU_VIBRATO_RATE_SHIFT	0
#घोषणा ESM_APU_VIBRATO_RATE_MASK	(0xf << 0)
#घोषणा ESM_APU_VIBRATO_DEPTH_SHIFT	4
#घोषणा ESM_APU_VIBRATO_DEPTH_MASK	(0xf << 4)
#घोषणा ESM_APU_VIBRATO_PHASE_SHIFT	8
#घोषणा ESM_APU_VIBRATO_PHASE_MASK	(0xff << 8)

/* reg 0x0c */
#घोषणा ESM_APU_RADIUS_SELECT		(1 << 6)

/* APU Filter Control */
#घोषणा	ESM_APU_FILTER_2POLE_LOPASS	0x00
#घोषणा	ESM_APU_FILTER_2POLE_BANDPASS	0x01
#घोषणा	ESM_APU_FILTER_2POLE_HIPASS	0x02
#घोषणा	ESM_APU_FILTER_1POLE_LOPASS	0x03
#घोषणा	ESM_APU_FILTER_1POLE_HIPASS	0x04
#घोषणा	ESM_APU_FILTER_OFF		0x05

/* APU ATFP Type */
#घोषणा	ESM_APU_ATFP_AMPLITUDE			0x00
#घोषणा	ESM_APU_ATFP_TREMELO			0x01
#घोषणा	ESM_APU_ATFP_FILTER			0x02
#घोषणा	ESM_APU_ATFP_PAN			0x03

/* APU ATFP Flags */
#घोषणा	ESM_APU_ATFP_FLG_OFF			0x00
#घोषणा	ESM_APU_ATFP_FLG_WAIT			0x01
#घोषणा	ESM_APU_ATFP_FLG_DONE			0x02
#घोषणा	ESM_APU_ATFP_FLG_INPROCESS		0x03


/* capture mixing buffer size */
#घोषणा ESM_MEM_ALIGN		0x1000
#घोषणा ESM_MIXBUF_SIZE		0x400

#घोषणा ESM_MODE_PLAY		0
#घोषणा ESM_MODE_CAPTURE	1


/* APU use in the driver */
क्रमागत snd_क्रमागत_apu_type अणु
	ESM_APU_PCM_PLAY,
	ESM_APU_PCM_CAPTURE,
	ESM_APU_PCM_RATECONV,
	ESM_APU_FREE
पूर्ण;

/* chip type */
क्रमागत अणु
	TYPE_MAESTRO, TYPE_MAESTRO2, TYPE_MAESTRO2E
पूर्ण;

/* DMA Hack! */
काष्ठा esm_memory अणु
	काष्ठा snd_dma_buffer buf;
	पूर्णांक empty;	/* status */
	काष्ठा list_head list;
पूर्ण;

/* Playback Channel */
काष्ठा esschan अणु
	पूर्णांक running;

	u8 apu[4];
	u8 apu_mode[4];

	/* playback/capture pcm buffer */
	काष्ठा esm_memory *memory;
	/* capture mixer buffer */
	काष्ठा esm_memory *mixbuf;

	अचिन्हित पूर्णांक hwptr;	/* current hw poपूर्णांकer in bytes */
	अचिन्हित पूर्णांक count;	/* sample counter in bytes */
	अचिन्हित पूर्णांक dma_size;	/* total buffer size in bytes */
	अचिन्हित पूर्णांक frag_size;	/* period size in bytes */
	अचिन्हित पूर्णांक wav_shअगरt;
	u16 base[4];		/* offset क्रम ptr */

	/* stereo/16bit flag */
	अचिन्हित अक्षर fmt;
	पूर्णांक mode;	/* playback / capture */

	पूर्णांक bob_freq;	/* required समयr frequency */

	काष्ठा snd_pcm_substream *substream;

	/* linked list */
	काष्ठा list_head list;

#अगर_घोषित CONFIG_PM_SLEEP
	u16 wc_map[4];
#पूर्ण_अगर
पूर्ण;

काष्ठा es1968 अणु
	/* Module Config */
	पूर्णांक total_bufsize;			/* in bytes */

	पूर्णांक playback_streams, capture_streams;

	अचिन्हित पूर्णांक घड़ी;		/* घड़ी */
	/* क्रम घड़ी measurement */
	अचिन्हित पूर्णांक in_measurement: 1;
	अचिन्हित पूर्णांक measure_apu;
	अचिन्हित पूर्णांक measure_lastpos;
	अचिन्हित पूर्णांक measure_count;

	/* buffer */
	काष्ठा snd_dma_buffer dma;

	/* Resources... */
	पूर्णांक irq;
	अचिन्हित दीर्घ io_port;
	पूर्णांक type;
	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	पूर्णांक करो_pm;		/* घातer-management enabled */

	/* DMA memory block */
	काष्ठा list_head buf_list;

	/* ALSA Stuff */
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_rawmidi *rmidi;

	spinlock_t reg_lock;
	अचिन्हित पूर्णांक in_suspend;

	/* Maestro Stuff */
	u16 maestro_map[32];
	पूर्णांक bobclient;		/* active समयr instancs */
	पूर्णांक bob_freq;		/* समयr frequency */
	काष्ठा mutex memory_mutex;	/* memory lock */

	/* APU states */
	अचिन्हित अक्षर apu[NR_APUS];

	/* active substreams */
	काष्ठा list_head substream_list;
	spinlock_t substream_lock;

#अगर_घोषित CONFIG_PM_SLEEP
	u16 apu_map[NR_APUS][NR_APU_REGS];
#पूर्ण_अगर

#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा gameport *gameport;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SND_ES1968_INPUT
	काष्ठा input_dev *input_dev;
	अक्षर phys[64];			/* physical device path */
#अन्यथा
	काष्ठा snd_kcontrol *master_चयन; /* क्रम h/w volume control */
	काष्ठा snd_kcontrol *master_volume;
#पूर्ण_अगर
	काष्ठा work_काष्ठा hwvol_work;

#अगर_घोषित CONFIG_SND_ES1968_RADIO
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा snd_tea575x tea;
	अचिन्हित पूर्णांक tea575x_tuner;
#पूर्ण_अगर
पूर्ण;

अटल irqवापस_t snd_es1968_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

अटल स्थिर काष्ठा pci_device_id snd_es1968_ids[] = अणु
	/* Maestro 1 */
        अणु 0x1285, 0x0100, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, TYPE_MAESTRO पूर्ण,
	/* Maestro 2 */
	अणु 0x125d, 0x1968, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, TYPE_MAESTRO2 पूर्ण,
	/* Maestro 2E */
        अणु 0x125d, 0x1978, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_MULTIMEDIA_AUDIO << 8, 0xffff00, TYPE_MAESTRO2E पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_es1968_ids);

/* *********************
   * Low Level Funcs!  *
   *********************/

/* no spinlock */
अटल व्योम __maestro_ग_लिखो(काष्ठा es1968 *chip, u16 reg, u16 data)
अणु
	outw(reg, chip->io_port + ESM_INDEX);
	outw(data, chip->io_port + ESM_DATA);
	chip->maestro_map[reg] = data;
पूर्ण

अटल अंतरभूत व्योम maestro_ग_लिखो(काष्ठा es1968 *chip, u16 reg, u16 data)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&chip->reg_lock, flags);
	__maestro_ग_लिखो(chip, reg, data);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

/* no spinlock */
अटल u16 __maestro_पढ़ो(काष्ठा es1968 *chip, u16 reg)
अणु
	अगर (READABLE_MAP & (1 << reg)) अणु
		outw(reg, chip->io_port + ESM_INDEX);
		chip->maestro_map[reg] = inw(chip->io_port + ESM_DATA);
	पूर्ण
	वापस chip->maestro_map[reg];
पूर्ण

अटल अंतरभूत u16 maestro_पढ़ो(काष्ठा es1968 *chip, u16 reg)
अणु
	अचिन्हित दीर्घ flags;
	u16 result;
	spin_lock_irqsave(&chip->reg_lock, flags);
	result = __maestro_पढ़ो(chip, reg);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस result;
पूर्ण

/* Wait क्रम the codec bus to be मुक्त */
अटल पूर्णांक snd_es1968_ac97_रुको(काष्ठा es1968 *chip)
अणु
	पूर्णांक समयout = 100000;

	जबतक (समयout-- > 0) अणु
		अगर (!(inb(chip->io_port + ESM_AC97_INDEX) & 1))
			वापस 0;
		cond_resched();
	पूर्ण
	dev_dbg(chip->card->dev, "ac97 timeout\n");
	वापस 1; /* समयout */
पूर्ण

अटल पूर्णांक snd_es1968_ac97_रुको_poll(काष्ठा es1968 *chip)
अणु
	पूर्णांक समयout = 100000;

	जबतक (समयout-- > 0) अणु
		अगर (!(inb(chip->io_port + ESM_AC97_INDEX) & 1))
			वापस 0;
	पूर्ण
	dev_dbg(chip->card->dev, "ac97 timeout\n");
	वापस 1; /* समयout */
पूर्ण

अटल व्योम snd_es1968_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	काष्ठा es1968 *chip = ac97->निजी_data;

	snd_es1968_ac97_रुको(chip);

	/* Write the bus */
	outw(val, chip->io_port + ESM_AC97_DATA);
	/*msleep(1);*/
	outb(reg, chip->io_port + ESM_AC97_INDEX);
	/*msleep(1);*/
पूर्ण

अटल अचिन्हित लघु snd_es1968_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	u16 data = 0;
	काष्ठा es1968 *chip = ac97->निजी_data;

	snd_es1968_ac97_रुको(chip);

	outb(reg | 0x80, chip->io_port + ESM_AC97_INDEX);
	/*msleep(1);*/

	अगर (!snd_es1968_ac97_रुको_poll(chip)) अणु
		data = inw(chip->io_port + ESM_AC97_DATA);
		/*msleep(1);*/
	पूर्ण

	वापस data;
पूर्ण

/* no spinlock */
अटल व्योम apu_index_set(काष्ठा es1968 *chip, u16 index)
अणु
	पूर्णांक i;
	__maestro_ग_लिखो(chip, IDR1_CRAM_POINTER, index);
	क्रम (i = 0; i < 1000; i++)
		अगर (__maestro_पढ़ो(chip, IDR1_CRAM_POINTER) == index)
			वापस;
	dev_dbg(chip->card->dev, "APU register select failed. (Timeout)\n");
पूर्ण

/* no spinlock */
अटल व्योम apu_data_set(काष्ठा es1968 *chip, u16 data)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 1000; i++) अणु
		अगर (__maestro_पढ़ो(chip, IDR0_DATA_PORT) == data)
			वापस;
		__maestro_ग_लिखो(chip, IDR0_DATA_PORT, data);
	पूर्ण
	dev_dbg(chip->card->dev, "APU register set probably failed (Timeout)!\n");
पूर्ण

/* no spinlock */
अटल व्योम __apu_set_रेजिस्टर(काष्ठा es1968 *chip, u16 channel, u8 reg, u16 data)
अणु
	अगर (snd_BUG_ON(channel >= NR_APUS))
		वापस;
#अगर_घोषित CONFIG_PM_SLEEP
	chip->apu_map[channel][reg] = data;
#पूर्ण_अगर
	reg |= (channel << 4);
	apu_index_set(chip, reg);
	apu_data_set(chip, data);
पूर्ण

अटल व्योम apu_set_रेजिस्टर(काष्ठा es1968 *chip, u16 channel, u8 reg, u16 data)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&chip->reg_lock, flags);
	__apu_set_रेजिस्टर(chip, channel, reg, data);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल u16 __apu_get_रेजिस्टर(काष्ठा es1968 *chip, u16 channel, u8 reg)
अणु
	अगर (snd_BUG_ON(channel >= NR_APUS))
		वापस 0;
	reg |= (channel << 4);
	apu_index_set(chip, reg);
	वापस __maestro_पढ़ो(chip, IDR0_DATA_PORT);
पूर्ण

अटल u16 apu_get_रेजिस्टर(काष्ठा es1968 *chip, u16 channel, u8 reg)
अणु
	अचिन्हित दीर्घ flags;
	u16 v;
	spin_lock_irqsave(&chip->reg_lock, flags);
	v = __apu_get_रेजिस्टर(chip, channel, reg);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस v;
पूर्ण

#अगर 0 /* ASSP is not supported */

अटल व्योम assp_set_रेजिस्टर(काष्ठा es1968 *chip, u32 reg, u32 value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	outl(reg, chip->io_port + ASSP_INDEX);
	outl(value, chip->io_port + ASSP_DATA);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल u32 assp_get_रेजिस्टर(काष्ठा es1968 *chip, u32 reg)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&chip->reg_lock, flags);
	outl(reg, chip->io_port + ASSP_INDEX);
	value = inl(chip->io_port + ASSP_DATA);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	वापस value;
पूर्ण

#पूर्ण_अगर

अटल व्योम wave_set_रेजिस्टर(काष्ठा es1968 *chip, u16 reg, u16 value)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	outw(reg, chip->io_port + WC_INDEX);
	outw(value, chip->io_port + WC_DATA);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल u16 wave_get_रेजिस्टर(काष्ठा es1968 *chip, u16 reg)
अणु
	अचिन्हित दीर्घ flags;
	u16 value;

	spin_lock_irqsave(&chip->reg_lock, flags);
	outw(reg, chip->io_port + WC_INDEX);
	value = inw(chip->io_port + WC_DATA);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	वापस value;
पूर्ण

/* *******************
   * Bob the Timer!  *
   *******************/

अटल व्योम snd_es1968_bob_stop(काष्ठा es1968 *chip)
अणु
	u16 reg;

	reg = __maestro_पढ़ो(chip, 0x11);
	reg &= ~ESM_BOB_ENABLE;
	__maestro_ग_लिखो(chip, 0x11, reg);
	reg = __maestro_पढ़ो(chip, 0x17);
	reg &= ~ESM_BOB_START;
	__maestro_ग_लिखो(chip, 0x17, reg);
पूर्ण

अटल व्योम snd_es1968_bob_start(काष्ठा es1968 *chip)
अणु
	पूर्णांक prescale;
	पूर्णांक भागide;

	/* compute ideal पूर्णांकerrupt frequency क्रम buffer size & play rate */
	/* first, find best prescaler value to match freq */
	क्रम (prescale = 5; prescale < 12; prescale++)
		अगर (chip->bob_freq > (ESS_SYSCLK >> (prescale + 9)))
			अवरोध;

	/* next, back off prescaler whilst getting भागider पूर्णांकo optimum range */
	भागide = 1;
	जबतक ((prescale > 5) && (भागide < 32)) अणु
		prescale--;
		भागide <<= 1;
	पूर्ण
	भागide >>= 1;

	/* now fine-tune the भागider क्रम best match */
	क्रम (; भागide < 31; भागide++)
		अगर (chip->bob_freq >
		    ((ESS_SYSCLK >> (prescale + 9)) / (भागide + 1))) अवरोध;

	/* भागide = 0 is illegal, but करोn't let prescale = 4! */
	अगर (भागide == 0) अणु
		भागide++;
		अगर (prescale > 5)
			prescale--;
	पूर्ण अन्यथा अगर (भागide > 1)
		भागide--;

	__maestro_ग_लिखो(chip, 6, 0x9000 | (prescale << 5) | भागide);	/* set reg */

	/* Now set IDR 11/17 */
	__maestro_ग_लिखो(chip, 0x11, __maestro_पढ़ो(chip, 0x11) | 1);
	__maestro_ग_लिखो(chip, 0x17, __maestro_पढ़ो(chip, 0x17) | 1);
पूर्ण

/* call with substream spinlock */
अटल व्योम snd_es1968_bob_inc(काष्ठा es1968 *chip, पूर्णांक freq)
अणु
	chip->bobclient++;
	अगर (chip->bobclient == 1) अणु
		chip->bob_freq = freq;
		snd_es1968_bob_start(chip);
	पूर्ण अन्यथा अगर (chip->bob_freq < freq) अणु
		snd_es1968_bob_stop(chip);
		chip->bob_freq = freq;
		snd_es1968_bob_start(chip);
	पूर्ण
पूर्ण

/* call with substream spinlock */
अटल व्योम snd_es1968_bob_dec(काष्ठा es1968 *chip)
अणु
	chip->bobclient--;
	अगर (chip->bobclient <= 0)
		snd_es1968_bob_stop(chip);
	अन्यथा अगर (chip->bob_freq > ESM_BOB_FREQ) अणु
		/* check reduction of समयr frequency */
		पूर्णांक max_freq = ESM_BOB_FREQ;
		काष्ठा esschan *es;
		list_क्रम_each_entry(es, &chip->substream_list, list) अणु
			अगर (max_freq < es->bob_freq)
				max_freq = es->bob_freq;
		पूर्ण
		अगर (max_freq != chip->bob_freq) अणु
			snd_es1968_bob_stop(chip);
			chip->bob_freq = max_freq;
			snd_es1968_bob_start(chip);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
snd_es1968_calc_bob_rate(काष्ठा es1968 *chip, काष्ठा esschan *es,
			 काष्ठा snd_pcm_runसमय *runसमय)
अणु
	/* we acquire 4 पूर्णांकerrupts per period क्रम precise control.. */
	पूर्णांक freq = runसमय->rate * 4;
	अगर (es->fmt & ESS_FMT_STEREO)
		freq <<= 1;
	अगर (es->fmt & ESS_FMT_16BIT)
		freq <<= 1;
	freq /= es->frag_size;
	अगर (freq < ESM_BOB_FREQ)
		freq = ESM_BOB_FREQ;
	अन्यथा अगर (freq > ESM_BOB_FREQ_MAX)
		freq = ESM_BOB_FREQ_MAX;
	वापस freq;
पूर्ण


/*************
 *  PCM Part *
 *************/

अटल u32 snd_es1968_compute_rate(काष्ठा es1968 *chip, u32 freq)
अणु
	u32 rate = (freq << 16) / chip->घड़ी;
#अगर 0 /* XXX: करो we need this? */ 
	अगर (rate > 0x10000)
		rate = 0x10000;
#पूर्ण_अगर
	वापस rate;
पूर्ण

/* get current poपूर्णांकer */
अटल अंतरभूत अचिन्हित पूर्णांक
snd_es1968_get_dma_ptr(काष्ठा es1968 *chip, काष्ठा esschan *es)
अणु
	अचिन्हित पूर्णांक offset;

	offset = apu_get_रेजिस्टर(chip, es->apu[0], 5);

	offset -= es->base[0];

	वापस (offset & 0xFFFE);	/* hardware is in words */
पूर्ण

अटल व्योम snd_es1968_apu_set_freq(काष्ठा es1968 *chip, पूर्णांक apu, पूर्णांक freq)
अणु
	apu_set_रेजिस्टर(chip, apu, 2,
			   (apu_get_रेजिस्टर(chip, apu, 2) & 0x00FF) |
			   ((freq & 0xff) << 8) | 0x10);
	apu_set_रेजिस्टर(chip, apu, 3, freq >> 8);
पूर्ण

/* spin lock held */
अटल अंतरभूत व्योम snd_es1968_trigger_apu(काष्ठा es1968 *esm, पूर्णांक apu, पूर्णांक mode)
अणु
	/* set the APU mode */
	__apu_set_रेजिस्टर(esm, apu, 0,
			   (__apu_get_रेजिस्टर(esm, apu, 0) & 0xff0f) |
			   (mode << 4));
पूर्ण

अटल व्योम snd_es1968_pcm_start(काष्ठा es1968 *chip, काष्ठा esschan *es)
अणु
	spin_lock(&chip->reg_lock);
	__apu_set_रेजिस्टर(chip, es->apu[0], 5, es->base[0]);
	snd_es1968_trigger_apu(chip, es->apu[0], es->apu_mode[0]);
	अगर (es->mode == ESM_MODE_CAPTURE) अणु
		__apu_set_रेजिस्टर(chip, es->apu[2], 5, es->base[2]);
		snd_es1968_trigger_apu(chip, es->apu[2], es->apu_mode[2]);
	पूर्ण
	अगर (es->fmt & ESS_FMT_STEREO) अणु
		__apu_set_रेजिस्टर(chip, es->apu[1], 5, es->base[1]);
		snd_es1968_trigger_apu(chip, es->apu[1], es->apu_mode[1]);
		अगर (es->mode == ESM_MODE_CAPTURE) अणु
			__apu_set_रेजिस्टर(chip, es->apu[3], 5, es->base[3]);
			snd_es1968_trigger_apu(chip, es->apu[3], es->apu_mode[3]);
		पूर्ण
	पूर्ण
	spin_unlock(&chip->reg_lock);
पूर्ण

अटल व्योम snd_es1968_pcm_stop(काष्ठा es1968 *chip, काष्ठा esschan *es)
अणु
	spin_lock(&chip->reg_lock);
	snd_es1968_trigger_apu(chip, es->apu[0], 0);
	snd_es1968_trigger_apu(chip, es->apu[1], 0);
	अगर (es->mode == ESM_MODE_CAPTURE) अणु
		snd_es1968_trigger_apu(chip, es->apu[2], 0);
		snd_es1968_trigger_apu(chip, es->apu[3], 0);
	पूर्ण
	spin_unlock(&chip->reg_lock);
पूर्ण

/* set the wavecache control reg */
अटल व्योम snd_es1968_program_wavecache(काष्ठा es1968 *chip, काष्ठा esschan *es,
					 पूर्णांक channel, u32 addr, पूर्णांक capture)
अणु
	u32 पंचांगpval = (addr - 0x10) & 0xFFF8;

	अगर (! capture) अणु
		अगर (!(es->fmt & ESS_FMT_16BIT))
			पंचांगpval |= 4;	/* 8bit */
		अगर (es->fmt & ESS_FMT_STEREO)
			पंचांगpval |= 2;	/* stereo */
	पूर्ण

	/* set the wavecache control reg */
	wave_set_रेजिस्टर(chip, es->apu[channel] << 3, पंचांगpval);

#अगर_घोषित CONFIG_PM_SLEEP
	es->wc_map[channel] = पंचांगpval;
#पूर्ण_अगर
पूर्ण


अटल व्योम snd_es1968_playback_setup(काष्ठा es1968 *chip, काष्ठा esschan *es,
				      काष्ठा snd_pcm_runसमय *runसमय)
अणु
	u32 pa;
	पूर्णांक high_apu = 0;
	पूर्णांक channel, apu;
	पूर्णांक i, size;
	अचिन्हित दीर्घ flags;
	u32 freq;

	size = es->dma_size >> es->wav_shअगरt;

	अगर (es->fmt & ESS_FMT_STEREO)
		high_apu++;

	क्रम (channel = 0; channel <= high_apu; channel++) अणु
		apu = es->apu[channel];

		snd_es1968_program_wavecache(chip, es, channel, es->memory->buf.addr, 0);

		/* Offset to PCMBAR */
		pa = es->memory->buf.addr;
		pa -= chip->dma.addr;
		pa >>= 1;	/* words */

		pa |= 0x00400000;	/* System RAM (Bit 22) */

		अगर (es->fmt & ESS_FMT_STEREO) अणु
			/* Enable stereo */
			अगर (channel)
				pa |= 0x00800000;	/* (Bit 23) */
			अगर (es->fmt & ESS_FMT_16BIT)
				pa >>= 1;
		पूर्ण

		/* base offset of dma calcs when पढ़ोing the poपूर्णांकer
		   on this left one */
		es->base[channel] = pa & 0xFFFF;

		क्रम (i = 0; i < 16; i++)
			apu_set_रेजिस्टर(chip, apu, i, 0x0000);

		/* Load the buffer पूर्णांकo the wave engine */
		apu_set_रेजिस्टर(chip, apu, 4, ((pa >> 16) & 0xFF) << 8);
		apu_set_रेजिस्टर(chip, apu, 5, pa & 0xFFFF);
		apu_set_रेजिस्टर(chip, apu, 6, (pa + size) & 0xFFFF);
		/* setting loop == sample len */
		apu_set_रेजिस्टर(chip, apu, 7, size);

		/* clear effects/env.. */
		apu_set_रेजिस्टर(chip, apu, 8, 0x0000);
		/* set amp now to 0xd0 (?), low byte is 'amplitude dest'? */
		apu_set_रेजिस्टर(chip, apu, 9, 0xD000);

		/* clear routing stuff */
		apu_set_रेजिस्टर(chip, apu, 11, 0x0000);
		/* dma on, no envelopes, filter to all 1s) */
		apu_set_रेजिस्टर(chip, apu, 0, 0x400F);

		अगर (es->fmt & ESS_FMT_16BIT)
			es->apu_mode[channel] = ESM_APU_16BITLINEAR;
		अन्यथा
			es->apu_mode[channel] = ESM_APU_8BITLINEAR;

		अगर (es->fmt & ESS_FMT_STEREO) अणु
			/* set panning: left or right */
			/* Check: dअगरferent panning. On my Canyon 3D Chipset the
			   Channels are swapped. I करोn't know, about the output
			   to the SPDअगर Link. Perhaps you have to change this
			   and not the APU Regs 4-5. */
			apu_set_रेजिस्टर(chip, apu, 10,
					 0x8F00 | (channel ? 0 : 0x10));
			es->apu_mode[channel] += 1;	/* stereo */
		पूर्ण अन्यथा
			apu_set_रेजिस्टर(chip, apu, 10, 0x8F08);
	पूर्ण

	spin_lock_irqsave(&chip->reg_lock, flags);
	/* clear WP पूर्णांकerrupts */
	outw(1, chip->io_port + 0x04);
	/* enable WP पूर्णांकs */
	outw(inw(chip->io_port + ESM_PORT_HOST_IRQ) | ESM_HIRQ_DSIE, chip->io_port + ESM_PORT_HOST_IRQ);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	freq = runसमय->rate;
	/* set frequency */
	अगर (freq > 48000)
		freq = 48000;
	अगर (freq < 4000)
		freq = 4000;

	/* hmmm.. */
	अगर (!(es->fmt & ESS_FMT_16BIT) && !(es->fmt & ESS_FMT_STEREO))
		freq >>= 1;

	freq = snd_es1968_compute_rate(chip, freq);

	/* Load the frequency, turn on 6dB */
	snd_es1968_apu_set_freq(chip, es->apu[0], freq);
	snd_es1968_apu_set_freq(chip, es->apu[1], freq);
पूर्ण


अटल व्योम init_capture_apu(काष्ठा es1968 *chip, काष्ठा esschan *es, पूर्णांक channel,
			     अचिन्हित पूर्णांक pa, अचिन्हित पूर्णांक bsize,
			     पूर्णांक mode, पूर्णांक route)
अणु
	पूर्णांक i, apu = es->apu[channel];

	es->apu_mode[channel] = mode;

	/* set the wavecache control reg */
	snd_es1968_program_wavecache(chip, es, channel, pa, 1);

	/* Offset to PCMBAR */
	pa -= chip->dma.addr;
	pa >>= 1;	/* words */

	/* base offset of dma calcs when पढ़ोing the poपूर्णांकer
	   on this left one */
	es->base[channel] = pa & 0xFFFF;
	pa |= 0x00400000;	/* bit 22 -> System RAM */

	/* Begin loading the APU */
	क्रम (i = 0; i < 16; i++)
		apu_set_रेजिस्टर(chip, apu, i, 0x0000);

	/* need to enable subgroups.. and we should probably
	   have dअगरferent groups क्रम dअगरferent /dev/dsps..  */
	apu_set_रेजिस्टर(chip, apu, 2, 0x8);

	/* Load the buffer पूर्णांकo the wave engine */
	apu_set_रेजिस्टर(chip, apu, 4, ((pa >> 16) & 0xFF) << 8);
	apu_set_रेजिस्टर(chip, apu, 5, pa & 0xFFFF);
	apu_set_रेजिस्टर(chip, apu, 6, (pa + bsize) & 0xFFFF);
	apu_set_रेजिस्टर(chip, apu, 7, bsize);
	/* clear effects/env.. */
	apu_set_रेजिस्टर(chip, apu, 8, 0x00F0);
	/* amplitude now?  sure.  why not.  */
	apu_set_रेजिस्टर(chip, apu, 9, 0x0000);
	/* set filter tune, radius, polar pan */
	apu_set_रेजिस्टर(chip, apu, 10, 0x8F08);
	/* route input */
	apu_set_रेजिस्टर(chip, apu, 11, route);
	/* dma on, no envelopes, filter to all 1s) */
	apu_set_रेजिस्टर(chip, apu, 0, 0x400F);
पूर्ण

अटल व्योम snd_es1968_capture_setup(काष्ठा es1968 *chip, काष्ठा esschan *es,
				     काष्ठा snd_pcm_runसमय *runसमय)
अणु
	पूर्णांक size;
	u32 freq;
	अचिन्हित दीर्घ flags;

	size = es->dma_size >> es->wav_shअगरt;

	/* APU assignments:
	   0 = mono/left SRC
	   1 = right SRC
	   2 = mono/left Input Mixer
	   3 = right Input Mixer
	*/
	/* data seems to flow from the codec, through an apu पूर्णांकo
	   the 'mixbuf' bit of page, then through the SRC apu
	   and out to the real 'buffer'.  ok.  sure.  */

	/* input mixer (left/mono) */
	/* parallel in crap, see maestro reg 0xC [8-11] */
	init_capture_apu(chip, es, 2,
			 es->mixbuf->buf.addr, ESM_MIXBUF_SIZE/4, /* in words */
			 ESM_APU_INPUTMIXER, 0x14);
	/* SRC (left/mono); get input from inputing apu */
	init_capture_apu(chip, es, 0, es->memory->buf.addr, size,
			 ESM_APU_SRCONVERTOR, es->apu[2]);
	अगर (es->fmt & ESS_FMT_STEREO) अणु
		/* input mixer (right) */
		init_capture_apu(chip, es, 3,
				 es->mixbuf->buf.addr + ESM_MIXBUF_SIZE/2,
				 ESM_MIXBUF_SIZE/4, /* in words */
				 ESM_APU_INPUTMIXER, 0x15);
		/* SRC (right) */
		init_capture_apu(chip, es, 1,
				 es->memory->buf.addr + size*2, size,
				 ESM_APU_SRCONVERTOR, es->apu[3]);
	पूर्ण

	freq = runसमय->rate;
	/* Sample Rate conversion APUs करोn't like 0x10000 क्रम their rate */
	अगर (freq > 47999)
		freq = 47999;
	अगर (freq < 4000)
		freq = 4000;

	freq = snd_es1968_compute_rate(chip, freq);

	/* Load the frequency, turn on 6dB */
	snd_es1968_apu_set_freq(chip, es->apu[0], freq);
	snd_es1968_apu_set_freq(chip, es->apu[1], freq);

	/* fix mixer rate at 48khz.  and its _must_ be 0x10000. */
	freq = 0x10000;
	snd_es1968_apu_set_freq(chip, es->apu[2], freq);
	snd_es1968_apu_set_freq(chip, es->apu[3], freq);

	spin_lock_irqsave(&chip->reg_lock, flags);
	/* clear WP पूर्णांकerrupts */
	outw(1, chip->io_port + 0x04);
	/* enable WP पूर्णांकs */
	outw(inw(chip->io_port + ESM_PORT_HOST_IRQ) | ESM_HIRQ_DSIE, chip->io_port + ESM_PORT_HOST_IRQ);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

/*******************
 *  ALSA Interface *
 *******************/

अटल पूर्णांक snd_es1968_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1968 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा esschan *es = runसमय->निजी_data;

	es->dma_size = snd_pcm_lib_buffer_bytes(substream);
	es->frag_size = snd_pcm_lib_period_bytes(substream);

	es->wav_shअगरt = 1; /* maestro handles always 16bit */
	es->fmt = 0;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		es->fmt |= ESS_FMT_16BIT;
	अगर (runसमय->channels > 1) अणु
		es->fmt |= ESS_FMT_STEREO;
		अगर (es->fmt & ESS_FMT_16BIT) /* 8bit is alपढ़ोy word shअगरted */
			es->wav_shअगरt++;
	पूर्ण
	es->bob_freq = snd_es1968_calc_bob_rate(chip, es, runसमय);

	चयन (es->mode) अणु
	हाल ESM_MODE_PLAY:
		snd_es1968_playback_setup(chip, es, runसमय);
		अवरोध;
	हाल ESM_MODE_CAPTURE:
		snd_es1968_capture_setup(chip, es, runसमय);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1968_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा es1968 *chip = snd_pcm_substream_chip(substream);
	काष्ठा esschan *es = substream->runसमय->निजी_data;

	spin_lock(&chip->substream_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (es->running)
			अवरोध;
		snd_es1968_bob_inc(chip, es->bob_freq);
		es->count = 0;
		es->hwptr = 0;
		snd_es1968_pcm_start(chip, es);
		es->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (! es->running)
			अवरोध;
		snd_es1968_pcm_stop(chip, es);
		es->running = 0;
		snd_es1968_bob_dec(chip);
		अवरोध;
	पूर्ण
	spin_unlock(&chip->substream_lock);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_es1968_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1968 *chip = snd_pcm_substream_chip(substream);
	काष्ठा esschan *es = substream->runसमय->निजी_data;
	अचिन्हित पूर्णांक ptr;

	ptr = snd_es1968_get_dma_ptr(chip, es) << es->wav_shअगरt;
	
	वापस bytes_to_frames(substream->runसमय, ptr % es->dma_size);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_es1968_playback = अणु
	.info =			(SNDRV_PCM_INFO_MMAP |
               		         SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 /*SNDRV_PCM_INFO_PAUSE |*/
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	65536,
	.period_bytes_min =	256,
	.period_bytes_max =	65536,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_es1968_capture = अणु
	.info =			(SNDRV_PCM_INFO_NONINTERLEAVED |
				 SNDRV_PCM_INFO_MMAP |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 /*SNDRV_PCM_INFO_PAUSE |*/
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		/*SNDRV_PCM_FMTBIT_U8 |*/ SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	65536,
	.period_bytes_min =	256,
	.period_bytes_max =	65536,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/* *************************
   * DMA memory management *
   *************************/

/* Because the Maestro can only take addresses relative to the PCM base address
   रेजिस्टर :( */

अटल पूर्णांक calc_available_memory_size(काष्ठा es1968 *chip)
अणु
	पूर्णांक max_size = 0;
	काष्ठा esm_memory *buf;

	mutex_lock(&chip->memory_mutex);
	list_क्रम_each_entry(buf, &chip->buf_list, list) अणु
		अगर (buf->empty && buf->buf.bytes > max_size)
			max_size = buf->buf.bytes;
	पूर्ण
	mutex_unlock(&chip->memory_mutex);
	अगर (max_size >= 128*1024)
		max_size = 127*1024;
	वापस max_size;
पूर्ण

/* allocate a new memory chunk with the specअगरied size */
अटल काष्ठा esm_memory *snd_es1968_new_memory(काष्ठा es1968 *chip, पूर्णांक size)
अणु
	काष्ठा esm_memory *buf;

	size = ALIGN(size, ESM_MEM_ALIGN);
	mutex_lock(&chip->memory_mutex);
	list_क्रम_each_entry(buf, &chip->buf_list, list) अणु
		अगर (buf->empty && buf->buf.bytes >= size)
			जाओ __found;
	पूर्ण
	mutex_unlock(&chip->memory_mutex);
	वापस शून्य;

__found:
	अगर (buf->buf.bytes > size) अणु
		काष्ठा esm_memory *chunk = kदो_स्मृति(माप(*chunk), GFP_KERNEL);
		अगर (chunk == शून्य) अणु
			mutex_unlock(&chip->memory_mutex);
			वापस शून्य;
		पूर्ण
		chunk->buf = buf->buf;
		chunk->buf.bytes -= size;
		chunk->buf.area += size;
		chunk->buf.addr += size;
		chunk->empty = 1;
		buf->buf.bytes = size;
		list_add(&chunk->list, &buf->list);
	पूर्ण
	buf->empty = 0;
	mutex_unlock(&chip->memory_mutex);
	वापस buf;
पूर्ण

/* मुक्त a memory chunk */
अटल व्योम snd_es1968_मुक्त_memory(काष्ठा es1968 *chip, काष्ठा esm_memory *buf)
अणु
	काष्ठा esm_memory *chunk;

	mutex_lock(&chip->memory_mutex);
	buf->empty = 1;
	अगर (buf->list.prev != &chip->buf_list) अणु
		chunk = list_entry(buf->list.prev, काष्ठा esm_memory, list);
		अगर (chunk->empty) अणु
			chunk->buf.bytes += buf->buf.bytes;
			list_del(&buf->list);
			kमुक्त(buf);
			buf = chunk;
		पूर्ण
	पूर्ण
	अगर (buf->list.next != &chip->buf_list) अणु
		chunk = list_entry(buf->list.next, काष्ठा esm_memory, list);
		अगर (chunk->empty) अणु
			buf->buf.bytes += chunk->buf.bytes;
			list_del(&chunk->list);
			kमुक्त(chunk);
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->memory_mutex);
पूर्ण

अटल व्योम snd_es1968_मुक्त_dmabuf(काष्ठा es1968 *chip)
अणु
	काष्ठा list_head *p;

	अगर (! chip->dma.area)
		वापस;
	snd_dma_मुक्त_pages(&chip->dma);
	जबतक ((p = chip->buf_list.next) != &chip->buf_list) अणु
		काष्ठा esm_memory *chunk = list_entry(p, काष्ठा esm_memory, list);
		list_del(p);
		kमुक्त(chunk);
	पूर्ण
पूर्ण

अटल पूर्णांक
snd_es1968_init_dmabuf(काष्ठा es1968 *chip)
अणु
	पूर्णांक err;
	काष्ठा esm_memory *chunk;

	err = snd_dma_alloc_pages_fallback(SNDRV_DMA_TYPE_DEV,
					   &chip->pci->dev,
					   chip->total_bufsize, &chip->dma);
	अगर (err < 0 || ! chip->dma.area) अणु
		dev_err(chip->card->dev,
			"can't allocate dma pages for size %d\n",
			   chip->total_bufsize);
		वापस -ENOMEM;
	पूर्ण
	अगर ((chip->dma.addr + chip->dma.bytes - 1) & ~((1 << 28) - 1)) अणु
		snd_dma_मुक्त_pages(&chip->dma);
		dev_err(chip->card->dev, "DMA buffer beyond 256MB.\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&chip->buf_list);
	/* allocate an empty chunk */
	chunk = kदो_स्मृति(माप(*chunk), GFP_KERNEL);
	अगर (chunk == शून्य) अणु
		snd_es1968_मुक्त_dmabuf(chip);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(chip->dma.area, 0, ESM_MEM_ALIGN);
	chunk->buf = chip->dma;
	chunk->buf.area += ESM_MEM_ALIGN;
	chunk->buf.addr += ESM_MEM_ALIGN;
	chunk->buf.bytes -= ESM_MEM_ALIGN;
	chunk->empty = 1;
	list_add(&chunk->list, &chip->buf_list);

	वापस 0;
पूर्ण

/* setup the dma_areas */
/* buffer is extracted from the pre-allocated memory chunk */
अटल पूर्णांक snd_es1968_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा es1968 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा esschan *chan = runसमय->निजी_data;
	पूर्णांक size = params_buffer_bytes(hw_params);

	अगर (chan->memory) अणु
		अगर (chan->memory->buf.bytes >= size) अणु
			runसमय->dma_bytes = size;
			वापस 0;
		पूर्ण
		snd_es1968_मुक्त_memory(chip, chan->memory);
	पूर्ण
	chan->memory = snd_es1968_new_memory(chip, size);
	अगर (chan->memory == शून्य) अणु
		dev_dbg(chip->card->dev,
			"cannot allocate dma buffer: size = %d\n", size);
		वापस -ENOMEM;
	पूर्ण
	snd_pcm_set_runसमय_buffer(substream, &chan->memory->buf);
	वापस 1; /* area was changed */
पूर्ण

/* हटाओ dma areas अगर allocated */
अटल पूर्णांक snd_es1968_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1968 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा esschan *chan;
	
	अगर (runसमय->निजी_data == शून्य)
		वापस 0;
	chan = runसमय->निजी_data;
	अगर (chan->memory) अणु
		snd_es1968_मुक्त_memory(chip, chan->memory);
		chan->memory = शून्य;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * allocate APU pair
 */
अटल पूर्णांक snd_es1968_alloc_apu_pair(काष्ठा es1968 *chip, पूर्णांक type)
अणु
	पूर्णांक apu;

	क्रम (apu = 0; apu < NR_APUS; apu += 2) अणु
		अगर (chip->apu[apu] == ESM_APU_FREE &&
		    chip->apu[apu + 1] == ESM_APU_FREE) अणु
			chip->apu[apu] = chip->apu[apu + 1] = type;
			वापस apu;
		पूर्ण
	पूर्ण
	वापस -EBUSY;
पूर्ण

/*
 * release APU pair
 */
अटल व्योम snd_es1968_मुक्त_apu_pair(काष्ठा es1968 *chip, पूर्णांक apu)
अणु
	chip->apu[apu] = chip->apu[apu + 1] = ESM_APU_FREE;
पूर्ण


/******************
 * PCM खोलो/बंद *
 ******************/

अटल पूर्णांक snd_es1968_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1968 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा esschan *es;
	पूर्णांक apu1;

	/* search 2 APUs */
	apu1 = snd_es1968_alloc_apu_pair(chip, ESM_APU_PCM_PLAY);
	अगर (apu1 < 0)
		वापस apu1;

	es = kzalloc(माप(*es), GFP_KERNEL);
	अगर (!es) अणु
		snd_es1968_मुक्त_apu_pair(chip, apu1);
		वापस -ENOMEM;
	पूर्ण

	es->apu[0] = apu1;
	es->apu[1] = apu1 + 1;
	es->apu_mode[0] = 0;
	es->apu_mode[1] = 0;
	es->running = 0;
	es->substream = substream;
	es->mode = ESM_MODE_PLAY;

	runसमय->निजी_data = es;
	runसमय->hw = snd_es1968_playback;
	runसमय->hw.buffer_bytes_max = runसमय->hw.period_bytes_max =
		calc_available_memory_size(chip);

	spin_lock_irq(&chip->substream_lock);
	list_add(&es->list, &chip->substream_list);
	spin_unlock_irq(&chip->substream_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1968_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा es1968 *chip = snd_pcm_substream_chip(substream);
	काष्ठा esschan *es;
	पूर्णांक apu1, apu2;

	apu1 = snd_es1968_alloc_apu_pair(chip, ESM_APU_PCM_CAPTURE);
	अगर (apu1 < 0)
		वापस apu1;
	apu2 = snd_es1968_alloc_apu_pair(chip, ESM_APU_PCM_RATECONV);
	अगर (apu2 < 0) अणु
		snd_es1968_मुक्त_apu_pair(chip, apu1);
		वापस apu2;
	पूर्ण
	
	es = kzalloc(माप(*es), GFP_KERNEL);
	अगर (!es) अणु
		snd_es1968_मुक्त_apu_pair(chip, apu1);
		snd_es1968_मुक्त_apu_pair(chip, apu2);
		वापस -ENOMEM;
	पूर्ण

	es->apu[0] = apu1;
	es->apu[1] = apu1 + 1;
	es->apu[2] = apu2;
	es->apu[3] = apu2 + 1;
	es->apu_mode[0] = 0;
	es->apu_mode[1] = 0;
	es->apu_mode[2] = 0;
	es->apu_mode[3] = 0;
	es->running = 0;
	es->substream = substream;
	es->mode = ESM_MODE_CAPTURE;

	/* get mixbuffer */
	अगर ((es->mixbuf = snd_es1968_new_memory(chip, ESM_MIXBUF_SIZE)) == शून्य) अणु
		snd_es1968_मुक्त_apu_pair(chip, apu1);
		snd_es1968_मुक्त_apu_pair(chip, apu2);
		kमुक्त(es);
                वापस -ENOMEM;
        पूर्ण
	स_रखो(es->mixbuf->buf.area, 0, ESM_MIXBUF_SIZE);

	runसमय->निजी_data = es;
	runसमय->hw = snd_es1968_capture;
	runसमय->hw.buffer_bytes_max = runसमय->hw.period_bytes_max =
		calc_available_memory_size(chip) - 1024; /* keep MIXBUF size */
	snd_pcm_hw_स्थिरraपूर्णांक_घात2(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES);

	spin_lock_irq(&chip->substream_lock);
	list_add(&es->list, &chip->substream_list);
	spin_unlock_irq(&chip->substream_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1968_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1968 *chip = snd_pcm_substream_chip(substream);
	काष्ठा esschan *es;

	अगर (substream->runसमय->निजी_data == शून्य)
		वापस 0;
	es = substream->runसमय->निजी_data;
	spin_lock_irq(&chip->substream_lock);
	list_del(&es->list);
	spin_unlock_irq(&chip->substream_lock);
	snd_es1968_मुक्त_apu_pair(chip, es->apu[0]);
	kमुक्त(es);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1968_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा es1968 *chip = snd_pcm_substream_chip(substream);
	काष्ठा esschan *es;

	अगर (substream->runसमय->निजी_data == शून्य)
		वापस 0;
	es = substream->runसमय->निजी_data;
	spin_lock_irq(&chip->substream_lock);
	list_del(&es->list);
	spin_unlock_irq(&chip->substream_lock);
	snd_es1968_मुक्त_memory(chip, es->mixbuf);
	snd_es1968_मुक्त_apu_pair(chip, es->apu[0]);
	snd_es1968_मुक्त_apu_pair(chip, es->apu[2]);
	kमुक्त(es);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_es1968_playback_ops = अणु
	.खोलो =		snd_es1968_playback_खोलो,
	.बंद =	snd_es1968_playback_बंद,
	.hw_params =	snd_es1968_hw_params,
	.hw_मुक्त =	snd_es1968_hw_मुक्त,
	.prepare =	snd_es1968_pcm_prepare,
	.trigger =	snd_es1968_pcm_trigger,
	.poपूर्णांकer =	snd_es1968_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_es1968_capture_ops = अणु
	.खोलो =		snd_es1968_capture_खोलो,
	.बंद =	snd_es1968_capture_बंद,
	.hw_params =	snd_es1968_hw_params,
	.hw_मुक्त =	snd_es1968_hw_मुक्त,
	.prepare =	snd_es1968_pcm_prepare,
	.trigger =	snd_es1968_pcm_trigger,
	.poपूर्णांकer =	snd_es1968_pcm_poपूर्णांकer,
पूर्ण;


/*
 * measure घड़ी
 */
#घोषणा CLOCK_MEASURE_बफ_मानE	16768	/* enough large क्रम a single shot */

अटल व्योम es1968_measure_घड़ी(काष्ठा es1968 *chip)
अणु
	पूर्णांक i, apu;
	अचिन्हित पूर्णांक pa, offset, t;
	काष्ठा esm_memory *memory;
	kसमय_प्रकार start_समय, stop_समय;
	kसमय_प्रकार dअगरf;

	अगर (chip->घड़ी == 0)
		chip->घड़ी = 48000; /* शेष घड़ी value */

	/* search 2 APUs (although one apu is enough) */
	अगर ((apu = snd_es1968_alloc_apu_pair(chip, ESM_APU_PCM_PLAY)) < 0) अणु
		dev_err(chip->card->dev, "Hmm, cannot find empty APU pair!?\n");
		वापस;
	पूर्ण
	अगर ((memory = snd_es1968_new_memory(chip, CLOCK_MEASURE_बफ_मानE)) == शून्य) अणु
		dev_warn(chip->card->dev,
			 "cannot allocate dma buffer - using default clock %d\n",
			 chip->घड़ी);
		snd_es1968_मुक्त_apu_pair(chip, apu);
		वापस;
	पूर्ण

	स_रखो(memory->buf.area, 0, CLOCK_MEASURE_बफ_मानE);

	wave_set_रेजिस्टर(chip, apu << 3, (memory->buf.addr - 0x10) & 0xfff8);

	pa = (अचिन्हित पूर्णांक)((memory->buf.addr - chip->dma.addr) >> 1);
	pa |= 0x00400000;	/* System RAM (Bit 22) */

	/* initialize apu */
	क्रम (i = 0; i < 16; i++)
		apu_set_रेजिस्टर(chip, apu, i, 0x0000);

	apu_set_रेजिस्टर(chip, apu, 0, 0x400f);
	apu_set_रेजिस्टर(chip, apu, 4, ((pa >> 16) & 0xff) << 8);
	apu_set_रेजिस्टर(chip, apu, 5, pa & 0xffff);
	apu_set_रेजिस्टर(chip, apu, 6, (pa + CLOCK_MEASURE_बफ_मानE/2) & 0xffff);
	apu_set_रेजिस्टर(chip, apu, 7, CLOCK_MEASURE_बफ_मानE/2);
	apu_set_रेजिस्टर(chip, apu, 8, 0x0000);
	apu_set_रेजिस्टर(chip, apu, 9, 0xD000);
	apu_set_रेजिस्टर(chip, apu, 10, 0x8F08);
	apu_set_रेजिस्टर(chip, apu, 11, 0x0000);
	spin_lock_irq(&chip->reg_lock);
	outw(1, chip->io_port + 0x04); /* clear WP पूर्णांकerrupts */
	outw(inw(chip->io_port + ESM_PORT_HOST_IRQ) | ESM_HIRQ_DSIE, chip->io_port + ESM_PORT_HOST_IRQ); /* enable WP पूर्णांकs */
	spin_unlock_irq(&chip->reg_lock);

	snd_es1968_apu_set_freq(chip, apu, ((अचिन्हित पूर्णांक)48000 << 16) / chip->घड़ी); /* 48000 Hz */

	chip->in_measurement = 1;
	chip->measure_apu = apu;
	spin_lock_irq(&chip->reg_lock);
	snd_es1968_bob_inc(chip, ESM_BOB_FREQ);
	__apu_set_रेजिस्टर(chip, apu, 5, pa & 0xffff);
	snd_es1968_trigger_apu(chip, apu, ESM_APU_16BITLINEAR);
	start_समय = kसमय_get();
	spin_unlock_irq(&chip->reg_lock);
	msleep(50);
	spin_lock_irq(&chip->reg_lock);
	offset = __apu_get_रेजिस्टर(chip, apu, 5);
	stop_समय = kसमय_get();
	snd_es1968_trigger_apu(chip, apu, 0); /* stop */
	snd_es1968_bob_dec(chip);
	chip->in_measurement = 0;
	spin_unlock_irq(&chip->reg_lock);

	/* check the current position */
	offset -= (pa & 0xffff);
	offset &= 0xfffe;
	offset += chip->measure_count * (CLOCK_MEASURE_बफ_मानE/2);

	dअगरf = kसमय_sub(stop_समय, start_समय);
	t = kसमय_प्रकारo_us(dअगरf);
	अगर (t == 0) अणु
		dev_err(chip->card->dev, "?? calculation error..\n");
	पूर्ण अन्यथा अणु
		offset *= 1000;
		offset = (offset / t) * 1000 + ((offset % t) * 1000) / t;
		अगर (offset < 47500 || offset > 48500) अणु
			अगर (offset >= 40000 && offset <= 50000)
				chip->घड़ी = (chip->घड़ी * offset) / 48000;
		पूर्ण
		dev_info(chip->card->dev, "clocking to %d\n", chip->घड़ी);
	पूर्ण
	snd_es1968_मुक्त_memory(chip, memory);
	snd_es1968_मुक्त_apu_pair(chip, apu);
पूर्ण


/*
 */

अटल व्योम snd_es1968_pcm_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा es1968 *esm = pcm->निजी_data;
	snd_es1968_मुक्त_dmabuf(esm);
	esm->pcm = शून्य;
पूर्ण

अटल पूर्णांक
snd_es1968_pcm(काष्ठा es1968 *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	/* get DMA buffer */
	अगर ((err = snd_es1968_init_dmabuf(chip)) < 0)
		वापस err;

	/* set PCMBAR */
	wave_set_रेजिस्टर(chip, 0x01FC, chip->dma.addr >> 12);
	wave_set_रेजिस्टर(chip, 0x01FD, chip->dma.addr >> 12);
	wave_set_रेजिस्टर(chip, 0x01FE, chip->dma.addr >> 12);
	wave_set_रेजिस्टर(chip, 0x01FF, chip->dma.addr >> 12);

	अगर ((err = snd_pcm_new(chip->card, "ESS Maestro", device,
			       chip->playback_streams,
			       chip->capture_streams, &pcm)) < 0)
		वापस err;

	pcm->निजी_data = chip;
	pcm->निजी_मुक्त = snd_es1968_pcm_मुक्त;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_es1968_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_es1968_capture_ops);

	pcm->info_flags = 0;

	म_नकल(pcm->name, "ESS Maestro");

	chip->pcm = pcm;

	वापस 0;
पूर्ण
/*
 * suppress jitter on some maestros when playing stereo
 */
अटल व्योम snd_es1968_suppress_jitter(काष्ठा es1968 *chip, काष्ठा esschan *es)
अणु
	अचिन्हित पूर्णांक cp1;
	अचिन्हित पूर्णांक cp2;
	अचिन्हित पूर्णांक dअगरf;

	cp1 = __apu_get_रेजिस्टर(chip, 0, 5);
	cp2 = __apu_get_रेजिस्टर(chip, 1, 5);
	dअगरf = (cp1 > cp2 ? cp1 - cp2 : cp2 - cp1);

	अगर (dअगरf > 1)
		__maestro_ग_लिखो(chip, IDR0_DATA_PORT, cp1);
पूर्ण

/*
 * update poपूर्णांकer
 */
अटल व्योम snd_es1968_update_pcm(काष्ठा es1968 *chip, काष्ठा esschan *es)
अणु
	अचिन्हित पूर्णांक hwptr;
	अचिन्हित पूर्णांक dअगरf;
	काष्ठा snd_pcm_substream *subs = es->substream;
        
	अगर (subs == शून्य || !es->running)
		वापस;

	hwptr = snd_es1968_get_dma_ptr(chip, es) << es->wav_shअगरt;
	hwptr %= es->dma_size;

	dअगरf = (es->dma_size + hwptr - es->hwptr) % es->dma_size;

	es->hwptr = hwptr;
	es->count += dअगरf;

	अगर (es->count > es->frag_size) अणु
		spin_unlock(&chip->substream_lock);
		snd_pcm_period_elapsed(subs);
		spin_lock(&chip->substream_lock);
		es->count %= es->frag_size;
	पूर्ण
पूर्ण

/* The hardware volume works by incrementing / decrementing 2 counters
   (without wrap around) in response to volume button presses and then
   generating an पूर्णांकerrupt. The pair of counters is stored in bits 1-3 and 5-7
   of a byte wide रेजिस्टर. The meaning of bits 0 and 4 is unknown. */
अटल व्योम es1968_update_hw_volume(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा es1968 *chip = container_of(work, काष्ठा es1968, hwvol_work);
	पूर्णांक x, val;

	/* Figure out which volume control button was pushed,
	   based on dअगरferences from the शेष रेजिस्टर
	   values. */
	x = inb(chip->io_port + 0x1c) & 0xee;
	/* Reset the volume control रेजिस्टरs. */
	outb(0x88, chip->io_port + 0x1c);
	outb(0x88, chip->io_port + 0x1d);
	outb(0x88, chip->io_port + 0x1e);
	outb(0x88, chip->io_port + 0x1f);

	अगर (chip->in_suspend)
		वापस;

#अगर_अघोषित CONFIG_SND_ES1968_INPUT
	अगर (! chip->master_चयन || ! chip->master_volume)
		वापस;

	val = snd_ac97_पढ़ो(chip->ac97, AC97_MASTER);
	चयन (x) अणु
	हाल 0x88:
		/* mute */
		val ^= 0x8000;
		अवरोध;
	हाल 0xaa:
		/* volume up */
		अगर ((val & 0x7f) > 0)
			val--;
		अगर ((val & 0x7f00) > 0)
			val -= 0x0100;
		अवरोध;
	हाल 0x66:
		/* volume करोwn */
		अगर ((val & 0x7f) < 0x1f)
			val++;
		अगर ((val & 0x7f00) < 0x1f00)
			val += 0x0100;
		अवरोध;
	पूर्ण
	अगर (snd_ac97_update(chip->ac97, AC97_MASTER, val))
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->master_volume->id);
#अन्यथा
	अगर (!chip->input_dev)
		वापस;

	val = 0;
	चयन (x) अणु
	हाल 0x88:
		/* The counters have not changed, yet we've received a HV
		   पूर्णांकerrupt. According to tests run by various people this
		   happens when pressing the mute button. */
		val = KEY_MUTE;
		अवरोध;
	हाल 0xaa:
		/* counters increased by 1 -> volume up */
		val = KEY_VOLUMEUP;
		अवरोध;
	हाल 0x66:
		/* counters decreased by 1 -> volume करोwn */
		val = KEY_VOLUMEDOWN;
		अवरोध;
	पूर्ण

	अगर (val) अणु
		input_report_key(chip->input_dev, val, 1);
		input_sync(chip->input_dev);
		input_report_key(chip->input_dev, val, 0);
		input_sync(chip->input_dev);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * पूर्णांकerrupt handler
 */
अटल irqवापस_t snd_es1968_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा es1968 *chip = dev_id;
	u32 event;

	अगर (!(event = inb(chip->io_port + 0x1A)))
		वापस IRQ_NONE;

	outw(inw(chip->io_port + 4) & 1, chip->io_port + 4);

	अगर (event & ESM_HWVOL_IRQ)
		schedule_work(&chip->hwvol_work);

	/* अन्यथा ack 'em all, i imagine */
	outb(0xFF, chip->io_port + 0x1A);

	अगर ((event & ESM_MPU401_IRQ) && chip->rmidi) अणु
		snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rmidi->निजी_data);
	पूर्ण

	अगर (event & ESM_SOUND_IRQ) अणु
		काष्ठा esschan *es;
		spin_lock(&chip->substream_lock);
		list_क्रम_each_entry(es, &chip->substream_list, list) अणु
			अगर (es->running) अणु
				snd_es1968_update_pcm(chip, es);
				अगर (es->fmt & ESS_FMT_STEREO)
					snd_es1968_suppress_jitter(chip, es);
			पूर्ण
		पूर्ण
		spin_unlock(&chip->substream_lock);
		अगर (chip->in_measurement) अणु
			अचिन्हित पूर्णांक curp = __apu_get_रेजिस्टर(chip, chip->measure_apu, 5);
			अगर (curp < chip->measure_lastpos)
				chip->measure_count++;
			chip->measure_lastpos = curp;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 *  Mixer stuff
 */

अटल पूर्णांक
snd_es1968_mixer(काष्ठा es1968 *chip)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
#अगर_अघोषित CONFIG_SND_ES1968_INPUT
	काष्ठा snd_ctl_elem_id elem_id;
#पूर्ण_अगर
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_es1968_ac97_ग_लिखो,
		.पढ़ो = snd_es1968_ac97_पढ़ो,
	पूर्ण;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, शून्य, &pbus)) < 0)
		वापस err;
	pbus->no_vra = 1; /* ES1968 करोesn't need VRA */

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	अगर ((err = snd_ac97_mixer(pbus, &ac97, &chip->ac97)) < 0)
		वापस err;

#अगर_अघोषित CONFIG_SND_ES1968_INPUT
	/* attach master चयन / volumes क्रम h/w volume control */
	स_रखो(&elem_id, 0, माप(elem_id));
	elem_id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(elem_id.name, "Master Playback Switch");
	chip->master_चयन = snd_ctl_find_id(chip->card, &elem_id);
	स_रखो(&elem_id, 0, माप(elem_id));
	elem_id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	म_नकल(elem_id.name, "Master Playback Volume");
	chip->master_volume = snd_ctl_find_id(chip->card, &elem_id);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * reset ac97 codec
 */

अटल व्योम snd_es1968_ac97_reset(काष्ठा es1968 *chip)
अणु
	अचिन्हित दीर्घ ioaddr = chip->io_port;

	अचिन्हित लघु save_ringbus_a;
	अचिन्हित लघु save_68;
	अचिन्हित लघु w;
	अचिन्हित पूर्णांक vend;

	/* save configuration */
	save_ringbus_a = inw(ioaddr + 0x36);

	//outw(inw(ioaddr + 0x38) & 0xfffc, ioaddr + 0x38); /* clear second codec id? */
	/* set command/status address i/o to 1st codec */
	outw(inw(ioaddr + 0x3a) & 0xfffc, ioaddr + 0x3a);
	outw(inw(ioaddr + 0x3c) & 0xfffc, ioaddr + 0x3c);

	/* disable ac link */
	outw(0x0000, ioaddr + 0x36);
	save_68 = inw(ioaddr + 0x68);
	pci_पढ़ो_config_word(chip->pci, 0x58, &w);	/* something magical with gpio and bus arb. */
	pci_पढ़ो_config_dword(chip->pci, PCI_SUBSYSTEM_VENDOR_ID, &vend);
	अगर (w & 1)
		save_68 |= 0x10;
	outw(0xfffe, ioaddr + 0x64);	/* unmask gpio 0 */
	outw(0x0001, ioaddr + 0x68);	/* gpio ग_लिखो */
	outw(0x0000, ioaddr + 0x60);	/* ग_लिखो 0 to gpio 0 */
	udelay(20);
	outw(0x0001, ioaddr + 0x60);	/* ग_लिखो 1 to gpio 1 */
	msleep(20);

	outw(save_68 | 0x1, ioaddr + 0x68);	/* now restore .. */
	outw((inw(ioaddr + 0x38) & 0xfffc) | 0x1, ioaddr + 0x38);
	outw((inw(ioaddr + 0x3a) & 0xfffc) | 0x1, ioaddr + 0x3a);
	outw((inw(ioaddr + 0x3c) & 0xfffc) | 0x1, ioaddr + 0x3c);

	/* now the second codec */
	/* disable ac link */
	outw(0x0000, ioaddr + 0x36);
	outw(0xfff7, ioaddr + 0x64);	/* unmask gpio 3 */
	save_68 = inw(ioaddr + 0x68);
	outw(0x0009, ioaddr + 0x68);	/* gpio ग_लिखो 0 & 3 ?? */
	outw(0x0001, ioaddr + 0x60);	/* ग_लिखो 1 to gpio */
	udelay(20);
	outw(0x0009, ioaddr + 0x60);	/* ग_लिखो 9 to gpio */
	msleep(500);
	//outw(inw(ioaddr + 0x38) & 0xfffc, ioaddr + 0x38);
	outw(inw(ioaddr + 0x3a) & 0xfffc, ioaddr + 0x3a);
	outw(inw(ioaddr + 0x3c) & 0xfffc, ioaddr + 0x3c);

#अगर 0				/* the loop here needs to be much better अगर we want it.. */
	dev_info(chip->card->dev, "trying software reset\n");
	/* try and करो a software reset */
	outb(0x80 | 0x7c, ioaddr + 0x30);
	क्रम (w = 0;; w++) अणु
		अगर ((inw(ioaddr + 0x30) & 1) == 0) अणु
			अगर (inb(ioaddr + 0x32) != 0)
				अवरोध;

			outb(0x80 | 0x7d, ioaddr + 0x30);
			अगर (((inw(ioaddr + 0x30) & 1) == 0)
			    && (inb(ioaddr + 0x32) != 0))
				अवरोध;
			outb(0x80 | 0x7f, ioaddr + 0x30);
			अगर (((inw(ioaddr + 0x30) & 1) == 0)
			    && (inb(ioaddr + 0x32) != 0))
				अवरोध;
		पूर्ण

		अगर (w > 10000) अणु
			outb(inb(ioaddr + 0x37) | 0x08, ioaddr + 0x37);	/* करो a software reset */
			msleep(500);	/* oh my.. */
			outb(inb(ioaddr + 0x37) & ~0x08,
				ioaddr + 0x37);
			udelay(1);
			outw(0x80, ioaddr + 0x30);
			क्रम (w = 0; w < 10000; w++) अणु
				अगर ((inw(ioaddr + 0x30) & 1) == 0)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (vend == NEC_VERSA_SUBID1 || vend == NEC_VERSA_SUBID2) अणु
		/* turn on बाह्यal amp? */
		outw(0xf9ff, ioaddr + 0x64);
		outw(inw(ioaddr + 0x68) | 0x600, ioaddr + 0x68);
		outw(0x0209, ioaddr + 0x60);
	पूर्ण

	/* restore.. */
	outw(save_ringbus_a, ioaddr + 0x36);

	/* Turn on the 978 करोcking chip.
	   First frob the "master output enable" bit,
	   then set most of the playback volume control रेजिस्टरs to max. */
	outb(inb(ioaddr+0xc0)|(1<<5), ioaddr+0xc0);
	outb(0xff, ioaddr+0xc3);
	outb(0xff, ioaddr+0xc4);
	outb(0xff, ioaddr+0xc6);
	outb(0xff, ioaddr+0xc8);
	outb(0x3f, ioaddr+0xcf);
	outb(0x3f, ioaddr+0xd0);
पूर्ण

अटल व्योम snd_es1968_reset(काष्ठा es1968 *chip)
अणु
	/* Reset */
	outw(ESM_RESET_MAESTRO | ESM_RESET_सूचीECTSOUND,
	     chip->io_port + ESM_PORT_HOST_IRQ);
	udelay(10);
	outw(0x0000, chip->io_port + ESM_PORT_HOST_IRQ);
	udelay(10);
पूर्ण

/*
 * initialize maestro chip
 */
अटल व्योम snd_es1968_chip_init(काष्ठा es1968 *chip)
अणु
	काष्ठा pci_dev *pci = chip->pci;
	पूर्णांक i;
	अचिन्हित दीर्घ iobase  = chip->io_port;
	u16 w;
	u32 n;

	/* We used to muck around with pci config space that
	 * we had no business messing with.  We करोn't know enough
	 * about the machine to know which DMA mode is appropriate, 
	 * etc.  We were guessing wrong on some machines and making
	 * them unhappy.  We now trust in the BIOS to करो things right,
	 * which almost certainly means a new host of problems will
	 * arise with broken BIOS implementations.  screw 'em. 
	 * We're already intolerant of machines that don't assign
	 * IRQs.
	 */
	
	/* Config Reg A */
	pci_पढ़ो_config_word(pci, ESM_CONFIG_A, &w);

	w &= ~DMA_CLEAR;	/* Clear DMA bits */
	w &= ~(PIC_SNOOP1 | PIC_SNOOP2);	/* Clear Pic Snoop Mode Bits */
	w &= ~SAFEGUARD;	/* Safeguard off */
	w |= POST_WRITE;	/* Posted ग_लिखो */
	w |= PCI_TIMING;	/* PCI timing on */
	/* XXX huh?  claims to be reserved.. */
	w &= ~SWAP_LR;		/* swap left/right 
				   seems to only have effect on SB
				   Emulation */
	w &= ~SUBTR_DECODE;	/* Subtractive decode off */

	pci_ग_लिखो_config_word(pci, ESM_CONFIG_A, w);

	/* Config Reg B */

	pci_पढ़ो_config_word(pci, ESM_CONFIG_B, &w);

	w &= ~(1 << 15);	/* Turn off पूर्णांकernal घड़ी multiplier */
	/* XXX how करो we know which to use? */
	w &= ~(1 << 14);	/* External घड़ी */

	w &= ~SPDIF_CONFB;	/* disable S/PDIF output */
	w |= HWV_CONFB;		/* HWV on */
	w |= DEBOUNCE;		/* Debounce off: easier to push the HW buttons */
	w &= ~GPIO_CONFB;	/* GPIO 4:5 */
	w |= CHI_CONFB;		/* Disconnect from the CHI.  Enabling this made a dell 7500 work. */
	w &= ~IDMA_CONFB;	/* IDMA off (unकरोcumented) */
	w &= ~MIDI_FIX;		/* MIDI fix off (unकरोc) */
	w &= ~(1 << 1);		/* reserved, always ग_लिखो 0 */
	w &= ~IRQ_TO_ISA;	/* IRQ to ISA off (unकरोc) */

	pci_ग_लिखो_config_word(pci, ESM_CONFIG_B, w);

	/* DDMA off */

	pci_पढ़ो_config_word(pci, ESM_DDMA, &w);
	w &= ~(1 << 0);
	pci_ग_लिखो_config_word(pci, ESM_DDMA, w);

	/*
	 *	Legacy mode
	 */

	pci_पढ़ो_config_word(pci, ESM_LEGACY_AUDIO_CONTROL, &w);

	w |= ESS_DISABLE_AUDIO;	/* Disable Legacy Audio */
	w &= ~ESS_ENABLE_SERIAL_IRQ;	/* Disable SIRQ */
	w &= ~(0x1f);		/* disable mpu irq/io, game port, fm, SB */

	pci_ग_लिखो_config_word(pci, ESM_LEGACY_AUDIO_CONTROL, w);

	/* Set up 978 करोcking control chip. */
	pci_पढ़ो_config_word(pci, 0x58, &w);
	w|=1<<2;	/* Enable 978. */
	w|=1<<3;	/* Turn on 978 hardware volume control. */
	w&=~(1<<11);	/* Turn on 978 mixer volume control. */
	pci_ग_लिखो_config_word(pci, 0x58, w);
	
	/* Sound Reset */

	snd_es1968_reset(chip);

	/*
	 *	Ring Bus Setup
	 */

	/* setup usual 0x34 stuff.. 0x36 may be chip specअगरic */
	outw(0xC090, iobase + ESM_RING_BUS_DEST); /* direct sound, stereo */
	udelay(20);
	outw(0x3000, iobase + ESM_RING_BUS_CONTR_A); /* enable ringbus/serial */
	udelay(20);

	/*
	 *	Reset the CODEC
	 */
	 
	snd_es1968_ac97_reset(chip);

	/* Ring Bus Control B */

	n = inl(iobase + ESM_RING_BUS_CONTR_B);
	n &= ~RINGB_EN_SPDIF;	/* SPDIF off */
	//w |= RINGB_EN_2CODEC;	/* enable 2nd codec */
	outl(n, iobase + ESM_RING_BUS_CONTR_B);

	/* Set hardware volume control रेजिस्टरs to midpoपूर्णांकs.
	   We can tell which button was pushed based on how they change. */
	outb(0x88, iobase+0x1c);
	outb(0x88, iobase+0x1d);
	outb(0x88, iobase+0x1e);
	outb(0x88, iobase+0x1f);

	/* it appears some maestros (dell 7500) only work अगर these are set,
	   regardless of whether we use the assp or not. */

	outb(0, iobase + ASSP_CONTROL_B);
	outb(3, iobase + ASSP_CONTROL_A);	/* M: Reserved bits... */
	outb(0, iobase + ASSP_CONTROL_C);	/* M: Disable ASSP, ASSP IRQ's and FM Port */

	/*
	 * set up wavecache
	 */
	क्रम (i = 0; i < 16; i++) अणु
		/* Write 0 पूर्णांकo the buffer area 0x1E0->1EF */
		outw(0x01E0 + i, iobase + WC_INDEX);
		outw(0x0000, iobase + WC_DATA);

		/* The 1.10 test program seem to ग_लिखो 0 पूर्णांकo the buffer area
		 * 0x1D0-0x1DF too.*/
		outw(0x01D0 + i, iobase + WC_INDEX);
		outw(0x0000, iobase + WC_DATA);
	पूर्ण
	wave_set_रेजिस्टर(chip, IDR7_WAVE_ROMRAM,
			  (wave_get_रेजिस्टर(chip, IDR7_WAVE_ROMRAM) & 0xFF00));
	wave_set_रेजिस्टर(chip, IDR7_WAVE_ROMRAM,
			  wave_get_रेजिस्टर(chip, IDR7_WAVE_ROMRAM) | 0x100);
	wave_set_रेजिस्टर(chip, IDR7_WAVE_ROMRAM,
			  wave_get_रेजिस्टर(chip, IDR7_WAVE_ROMRAM) & ~0x200);
	wave_set_रेजिस्टर(chip, IDR7_WAVE_ROMRAM,
			  wave_get_रेजिस्टर(chip, IDR7_WAVE_ROMRAM) | ~0x400);


	maestro_ग_लिखो(chip, IDR2_CRAM_DATA, 0x0000);
	/* Now back to the DirectSound stuff */
	/* audio serial configuration.. ? */
	maestro_ग_लिखो(chip, 0x08, 0xB004);
	maestro_ग_लिखो(chip, 0x09, 0x001B);
	maestro_ग_लिखो(chip, 0x0A, 0x8000);
	maestro_ग_लिखो(chip, 0x0B, 0x3F37);
	maestro_ग_लिखो(chip, 0x0C, 0x0098);

	/* parallel in, has something to करो with recording :) */
	maestro_ग_लिखो(chip, 0x0C,
		      (maestro_पढ़ो(chip, 0x0C) & ~0xF000) | 0x8000);
	/* parallel out */
	maestro_ग_लिखो(chip, 0x0C,
		      (maestro_पढ़ो(chip, 0x0C) & ~0x0F00) | 0x0500);

	maestro_ग_लिखो(chip, 0x0D, 0x7632);

	/* Wave cache control on - test off, sg off, 
	   enable, enable extra chans 1Mb */

	w = inw(iobase + WC_CONTROL);

	w &= ~0xFA00;		/* Seems to be reserved? I करोn't know */
	w |= 0xA000;		/* reserved... I करोn't know */
	w &= ~0x0200;		/* Channels 56,57,58,59 as Extra Play,Rec Channel enable
				   Seems to crash the Computer अगर enabled... */
	w |= 0x0100;		/* Wave Cache Operation Enabled */
	w |= 0x0080;		/* Channels 60/61 as Placback/Record enabled */
	w &= ~0x0060;		/* Clear Wavtable Size */
	w |= 0x0020;		/* Wavetable Size : 1MB */
	/* Bit 4 is reserved */
	w &= ~0x000C;		/* DMA Stuff? I करोn't understand what the datasheet means */
	/* Bit 1 is reserved */
	w &= ~0x0001;		/* Test Mode off */

	outw(w, iobase + WC_CONTROL);

	/* Now clear the APU control ram */
	क्रम (i = 0; i < NR_APUS; i++) अणु
		क्रम (w = 0; w < NR_APU_REGS; w++)
			apu_set_रेजिस्टर(chip, i, w, 0);

	पूर्ण
पूर्ण

/* Enable IRQ's */
अटल व्योम snd_es1968_start_irq(काष्ठा es1968 *chip)
अणु
	अचिन्हित लघु w;
	w = ESM_HIRQ_DSIE | ESM_HIRQ_HW_VOLUME;
	अगर (chip->rmidi)
		w |= ESM_HIRQ_MPU401;
	outb(w, chip->io_port + 0x1A);
	outw(w, chip->io_port + ESM_PORT_HOST_IRQ);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * PM support
 */
अटल पूर्णांक es1968_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा es1968 *chip = card->निजी_data;

	अगर (! chip->करो_pm)
		वापस 0;

	chip->in_suspend = 1;
	cancel_work_sync(&chip->hwvol_work);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(chip->ac97);
	snd_es1968_bob_stop(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक es1968_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा es1968 *chip = card->निजी_data;
	काष्ठा esschan *es;

	अगर (! chip->करो_pm)
		वापस 0;

	snd_es1968_chip_init(chip);

	/* need to restore the base poपूर्णांकers.. */ 
	अगर (chip->dma.addr) अणु
		/* set PCMBAR */
		wave_set_रेजिस्टर(chip, 0x01FC, chip->dma.addr >> 12);
	पूर्ण

	snd_es1968_start_irq(chip);

	/* restore ac97 state */
	snd_ac97_resume(chip->ac97);

	list_क्रम_each_entry(es, &chip->substream_list, list) अणु
		चयन (es->mode) अणु
		हाल ESM_MODE_PLAY:
			snd_es1968_playback_setup(chip, es, es->substream->runसमय);
			अवरोध;
		हाल ESM_MODE_CAPTURE:
			snd_es1968_capture_setup(chip, es, es->substream->runसमय);
			अवरोध;
		पूर्ण
	पूर्ण

	/* start समयr again */
	अगर (chip->bobclient)
		snd_es1968_bob_start(chip);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	chip->in_suspend = 0;
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(es1968_pm, es1968_suspend, es1968_resume);
#घोषणा ES1968_PM_OPS	&es1968_pm
#अन्यथा
#घोषणा ES1968_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित SUPPORT_JOYSTICK
#घोषणा JOYSTICK_ADDR	0x200
अटल पूर्णांक snd_es1968_create_gameport(काष्ठा es1968 *chip, पूर्णांक dev)
अणु
	काष्ठा gameport *gp;
	काष्ठा resource *r;
	u16 val;

	अगर (!joystick[dev])
		वापस -ENODEV;

	r = request_region(JOYSTICK_ADDR, 8, "ES1968 gameport");
	अगर (!r)
		वापस -EBUSY;

	chip->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(chip->card->dev,
			"cannot allocate memory for gameport\n");
		release_and_मुक्त_resource(r);
		वापस -ENOMEM;
	पूर्ण

	pci_पढ़ो_config_word(chip->pci, ESM_LEGACY_AUDIO_CONTROL, &val);
	pci_ग_लिखो_config_word(chip->pci, ESM_LEGACY_AUDIO_CONTROL, val | 0x04);

	gameport_set_name(gp, "ES1968 Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(chip->pci));
	gameport_set_dev_parent(gp, &chip->pci->dev);
	gp->io = JOYSTICK_ADDR;
	gameport_set_port_data(gp, r);

	gameport_रेजिस्टर_port(gp);

	वापस 0;
पूर्ण

अटल व्योम snd_es1968_मुक्त_gameport(काष्ठा es1968 *chip)
अणु
	अगर (chip->gameport) अणु
		काष्ठा resource *r = gameport_get_port_data(chip->gameport);

		gameport_unरेजिस्टर_port(chip->gameport);
		chip->gameport = शून्य;

		release_and_मुक्त_resource(r);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_es1968_create_gameport(काष्ठा es1968 *chip, पूर्णांक dev) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम snd_es1968_मुक्त_gameport(काष्ठा es1968 *chip) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SND_ES1968_INPUT
अटल पूर्णांक snd_es1968_input_रेजिस्टर(काष्ठा es1968 *chip)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक err;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	snम_लिखो(chip->phys, माप(chip->phys), "pci-%s/input0",
		 pci_name(chip->pci));

	input_dev->name = chip->card->driver;
	input_dev->phys = chip->phys;
	input_dev->id.bustype = BUS_PCI;
	input_dev->id.venकरोr  = chip->pci->venकरोr;
	input_dev->id.product = chip->pci->device;
	input_dev->dev.parent = &chip->pci->dev;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(KEY_MUTE, input_dev->keybit);
	__set_bit(KEY_VOLUMEDOWN, input_dev->keybit);
	__set_bit(KEY_VOLUMEUP, input_dev->keybit);

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		input_मुक्त_device(input_dev);
		वापस err;
	पूर्ण

	chip->input_dev = input_dev;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_ES1968_INPUT */

#अगर_घोषित CONFIG_SND_ES1968_RADIO
#घोषणा GPIO_DATA	0x60
#घोषणा IO_MASK		4      /* mask      रेजिस्टर offset from GPIO_DATA
				bits 1=unmask ग_लिखो to given bit */
#घोषणा IO_सूची		8      /* direction रेजिस्टर offset from GPIO_DATA
				bits 0/1=पढ़ो/ग_लिखो direction */

/* GPIO to TEA575x maps */
काष्ठा snd_es1968_tea575x_gpio अणु
	u8 data, clk, wren, most;
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा snd_es1968_tea575x_gpio snd_es1968_tea575x_gpios[] = अणु
	अणु .data = 6, .clk = 7, .wren = 8, .most = 9, .name = "SF64-PCE2" पूर्ण,
	अणु .data = 7, .clk = 8, .wren = 6, .most = 10, .name = "M56VAP" पूर्ण,
पूर्ण;

#घोषणा get_tea575x_gpio(chip) \
	(&snd_es1968_tea575x_gpios[(chip)->tea575x_tuner])


अटल व्योम snd_es1968_tea575x_set_pins(काष्ठा snd_tea575x *tea, u8 pins)
अणु
	काष्ठा es1968 *chip = tea->निजी_data;
	काष्ठा snd_es1968_tea575x_gpio gpio = *get_tea575x_gpio(chip);
	u16 val = 0;

	val |= (pins & TEA575X_DATA) ? (1 << gpio.data) : 0;
	val |= (pins & TEA575X_CLK)  ? (1 << gpio.clk)  : 0;
	val |= (pins & TEA575X_WREN) ? (1 << gpio.wren) : 0;

	outw(val, chip->io_port + GPIO_DATA);
पूर्ण

अटल u8 snd_es1968_tea575x_get_pins(काष्ठा snd_tea575x *tea)
अणु
	काष्ठा es1968 *chip = tea->निजी_data;
	काष्ठा snd_es1968_tea575x_gpio gpio = *get_tea575x_gpio(chip);
	u16 val = inw(chip->io_port + GPIO_DATA);
	u8 ret = 0;

	अगर (val & (1 << gpio.data))
		ret |= TEA575X_DATA;
	अगर (val & (1 << gpio.most))
		ret |= TEA575X_MOST;

	वापस ret;
पूर्ण

अटल व्योम snd_es1968_tea575x_set_direction(काष्ठा snd_tea575x *tea, bool output)
अणु
	काष्ठा es1968 *chip = tea->निजी_data;
	अचिन्हित दीर्घ io = chip->io_port + GPIO_DATA;
	u16 odir = inw(io + IO_सूची);
	काष्ठा snd_es1968_tea575x_gpio gpio = *get_tea575x_gpio(chip);

	अगर (output) अणु
		outw(~((1 << gpio.data) | (1 << gpio.clk) | (1 << gpio.wren)),
			io + IO_MASK);
		outw(odir | (1 << gpio.data) | (1 << gpio.clk) | (1 << gpio.wren),
			io + IO_सूची);
	पूर्ण अन्यथा अणु
		outw(~((1 << gpio.clk) | (1 << gpio.wren) | (1 << gpio.data) | (1 << gpio.most)),
			io + IO_MASK);
		outw((odir & ~((1 << gpio.data) | (1 << gpio.most)))
			| (1 << gpio.clk) | (1 << gpio.wren), io + IO_सूची);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_tea575x_ops snd_es1968_tea_ops = अणु
	.set_pins = snd_es1968_tea575x_set_pins,
	.get_pins = snd_es1968_tea575x_get_pins,
	.set_direction = snd_es1968_tea575x_set_direction,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक snd_es1968_मुक्त(काष्ठा es1968 *chip)
अणु
	cancel_work_sync(&chip->hwvol_work);
#अगर_घोषित CONFIG_SND_ES1968_INPUT
	अगर (chip->input_dev)
		input_unरेजिस्टर_device(chip->input_dev);
#पूर्ण_अगर

	अगर (chip->io_port) अणु
		outw(1, chip->io_port + 0x04); /* clear WP पूर्णांकerrupts */
		outw(0, chip->io_port + ESM_PORT_HOST_IRQ); /* disable IRQ */
	पूर्ण

#अगर_घोषित CONFIG_SND_ES1968_RADIO
	snd_tea575x_निकास(&chip->tea);
	v4l2_device_unरेजिस्टर(&chip->v4l2_dev);
#पूर्ण_अगर

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	snd_es1968_मुक्त_gameport(chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1968_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा es1968 *chip = device->device_data;
	वापस snd_es1968_मुक्त(chip);
पूर्ण

काष्ठा ess_device_list अणु
	अचिन्हित लघु type;	/* chip type */
	अचिन्हित लघु venकरोr;	/* subप्रणाली venकरोr id */
पूर्ण;

अटल स्थिर काष्ठा ess_device_list pm_allowlist[] = अणु
	अणु TYPE_MAESTRO2E, 0x0e11 पूर्ण,	/* Compaq Armada */
	अणु TYPE_MAESTRO2E, 0x1028 पूर्ण,
	अणु TYPE_MAESTRO2E, 0x103c पूर्ण,
	अणु TYPE_MAESTRO2E, 0x1179 पूर्ण,
	अणु TYPE_MAESTRO2E, 0x14c0 पूर्ण,	/* HP omnibook 4150 */
	अणु TYPE_MAESTRO2E, 0x1558 पूर्ण,
	अणु TYPE_MAESTRO2E, 0x125d पूर्ण,	/* a PCI card, e.g. Terratec DMX */
	अणु TYPE_MAESTRO2, 0x125d पूर्ण,	/* a PCI card, e.g. SF64-PCE2 */
पूर्ण;

अटल स्थिर काष्ठा ess_device_list mpu_denylist[] = अणु
	अणु TYPE_MAESTRO2, 0x125d पूर्ण,
पूर्ण;

अटल पूर्णांक snd_es1968_create(काष्ठा snd_card *card,
			     काष्ठा pci_dev *pci,
			     पूर्णांक total_bufsize,
			     पूर्णांक play_streams,
			     पूर्णांक capt_streams,
			     पूर्णांक chip_type,
			     पूर्णांक करो_pm,
			     पूर्णांक radio_nr,
			     काष्ठा es1968 **chip_ret)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_es1968_dev_मुक्त,
	पूर्ण;
	काष्ठा es1968 *chip;
	पूर्णांक i, err;

	*chip_ret = शून्य;

	/* enable PCI device */
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	/* check, अगर we can restrict PCI DMA transfers to 28 bits */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(28))) अणु
		dev_err(card->dev,
			"architecture does not support 28bit PCI busmaster DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (! chip) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	/* Set Vars */
	chip->type = chip_type;
	spin_lock_init(&chip->reg_lock);
	spin_lock_init(&chip->substream_lock);
	INIT_LIST_HEAD(&chip->buf_list);
	INIT_LIST_HEAD(&chip->substream_list);
	mutex_init(&chip->memory_mutex);
	INIT_WORK(&chip->hwvol_work, es1968_update_hw_volume);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	chip->total_bufsize = total_bufsize;	/* in bytes */
	chip->playback_streams = play_streams;
	chip->capture_streams = capt_streams;

	अगर ((err = pci_request_regions(pci, "ESS Maestro")) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	chip->io_port = pci_resource_start(pci, 0);
	अगर (request_irq(pci->irq, snd_es1968_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_es1968_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	        
	/* Clear Maestro_map */
	क्रम (i = 0; i < 32; i++)
		chip->maestro_map[i] = 0;

	/* Clear Apu Map */
	क्रम (i = 0; i < NR_APUS; i++)
		chip->apu[i] = ESM_APU_FREE;

	/* just to be sure */
	pci_set_master(pci);

	अगर (करो_pm > 1) अणु
		/* disable घातer-management अगर not on the allowlist */
		अचिन्हित लघु vend;
		pci_पढ़ो_config_word(chip->pci, PCI_SUBSYSTEM_VENDOR_ID, &vend);
		क्रम (i = 0; i < (पूर्णांक)ARRAY_SIZE(pm_allowlist); i++) अणु
			अगर (chip->type == pm_allowlist[i].type &&
			    vend == pm_allowlist[i].venकरोr) अणु
				करो_pm = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (करो_pm > 1) अणु
			/* not matched; disabling pm */
			dev_info(card->dev, "not attempting power management.\n");
			करो_pm = 0;
		पूर्ण
	पूर्ण
	chip->करो_pm = करो_pm;

	snd_es1968_chip_init(chip);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_es1968_मुक्त(chip);
		वापस err;
	पूर्ण

#अगर_घोषित CONFIG_SND_ES1968_RADIO
	/* करोn't play with GPIOs on laptops */
	अगर (chip->pci->subप्रणाली_venकरोr != 0x125d)
		जाओ no_radio;
	err = v4l2_device_रेजिस्टर(&pci->dev, &chip->v4l2_dev);
	अगर (err < 0) अणु
		snd_es1968_मुक्त(chip);
		वापस err;
	पूर्ण
	chip->tea.v4l2_dev = &chip->v4l2_dev;
	chip->tea.निजी_data = chip;
	chip->tea.radio_nr = radio_nr;
	chip->tea.ops = &snd_es1968_tea_ops;
	प्र_लिखो(chip->tea.bus_info, "PCI:%s", pci_name(pci));
	क्रम (i = 0; i < ARRAY_SIZE(snd_es1968_tea575x_gpios); i++) अणु
		chip->tea575x_tuner = i;
		अगर (!snd_tea575x_init(&chip->tea, THIS_MODULE)) अणु
			dev_info(card->dev, "detected TEA575x radio type %s\n",
				   get_tea575x_gpio(chip)->name);
			strscpy(chip->tea.card, get_tea575x_gpio(chip)->name,
				माप(chip->tea.card));
			अवरोध;
		पूर्ण
	पूर्ण
no_radio:
#पूर्ण_अगर

	*chip_ret = chip;

	वापस 0;
पूर्ण


/*
 */
अटल पूर्णांक snd_es1968_probe(काष्ठा pci_dev *pci,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा es1968 *chip;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;
                
	अगर (total_bufsize[dev] < 128)
		total_bufsize[dev] = 128;
	अगर (total_bufsize[dev] > 4096)
		total_bufsize[dev] = 4096;
	अगर ((err = snd_es1968_create(card, pci,
				     total_bufsize[dev] * 1024, /* in bytes */
				     pcm_substreams_p[dev], 
				     pcm_substreams_c[dev],
				     pci_id->driver_data,
				     use_pm[dev],
				     radio_nr[dev],
				     &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = chip;

	चयन (chip->type) अणु
	हाल TYPE_MAESTRO2E:
		म_नकल(card->driver, "ES1978");
		म_नकल(card->लघुname, "ESS ES1978 (Maestro 2E)");
		अवरोध;
	हाल TYPE_MAESTRO2:
		म_नकल(card->driver, "ES1968");
		म_नकल(card->लघुname, "ESS ES1968 (Maestro 2)");
		अवरोध;
	हाल TYPE_MAESTRO:
		म_नकल(card->driver, "ESM1");
		म_नकल(card->लघुname, "ESS Maestro 1");
		अवरोध;
	पूर्ण

	अगर ((err = snd_es1968_pcm(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर ((err = snd_es1968_mixer(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	अगर (enable_mpu[dev] == 2) अणु
		/* check the deny list */
		अचिन्हित लघु vend;
		pci_पढ़ो_config_word(chip->pci, PCI_SUBSYSTEM_VENDOR_ID, &vend);
		क्रम (i = 0; i < ARRAY_SIZE(mpu_denylist); i++) अणु
			अगर (chip->type == mpu_denylist[i].type &&
			    vend == mpu_denylist[i].venकरोr) अणु
				enable_mpu[dev] = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (enable_mpu[dev]) अणु
		अगर ((err = snd_mpu401_uart_new(card, 0, MPU401_HW_MPU401,
					       chip->io_port + ESM_MPU401_PORT,
					       MPU401_INFO_INTEGRATED |
					       MPU401_INFO_IRQ_HOOK,
					       -1, &chip->rmidi)) < 0) अणु
			dev_warn(card->dev, "skipping MPU-401 MIDI support..\n");
		पूर्ण
	पूर्ण

	snd_es1968_create_gameport(chip, dev);

#अगर_घोषित CONFIG_SND_ES1968_INPUT
	err = snd_es1968_input_रेजिस्टर(chip);
	अगर (err)
		dev_warn(card->dev,
			 "Input device registration failed with error %i", err);
#पूर्ण_अगर

	snd_es1968_start_irq(chip);

	chip->घड़ी = घड़ी[dev];
	अगर (! chip->घड़ी)
		es1968_measure_घड़ी(chip);

	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i",
		card->लघुname, chip->io_port, chip->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_es1968_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver es1968_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_es1968_ids,
	.probe = snd_es1968_probe,
	.हटाओ = snd_es1968_हटाओ,
	.driver = अणु
		.pm = ES1968_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(es1968_driver);
