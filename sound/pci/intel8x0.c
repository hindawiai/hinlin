<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम Intel ICH (i8x0) chipsets
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 *
 *   This code also contains alpha support क्रम SiS 735 chipsets provided
 *   by Mike Pieper <mptei@users.sourceक्रमge.net>. We have no datasheet
 *   क्रम SiS735, so the code is not fully functional.
 *

 */      

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/info.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Intel 82801AA,82901AB,i810,i820,i830,i840,i845,MX440; SiS 7012; Ali 5455");
MODULE_LICENSE("GPL");

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;	/* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
अटल पूर्णांक ac97_घड़ी;
अटल अक्षर *ac97_quirk;
अटल bool buggy_semaphore;
अटल पूर्णांक buggy_irq = -1; /* स्वतः-check */
अटल bool xbox;
अटल पूर्णांक spdअगर_aclink = -1;
अटल पूर्णांक inside_vm = -1;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for Intel i8x0 soundcard.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for Intel i8x0 soundcard.");
module_param(ac97_घड़ी, पूर्णांक, 0444);
MODULE_PARM_DESC(ac97_घड़ी, "AC'97 codec clock (0 = allowlist + auto-detect, 1 = force autodetect).");
module_param(ac97_quirk, अक्षरp, 0444);
MODULE_PARM_DESC(ac97_quirk, "AC'97 workaround for strange hardware.");
module_param(buggy_semaphore, bool, 0444);
MODULE_PARM_DESC(buggy_semaphore, "Enable workaround for hardwares with problematic codec semaphores.");
module_param(buggy_irq, bपूर्णांक, 0444);
MODULE_PARM_DESC(buggy_irq, "Enable workaround for buggy interrupts on some motherboards.");
module_param(xbox, bool, 0444);
MODULE_PARM_DESC(xbox, "Set to 1 for Xbox, if you have problems with the AC'97 codec detection.");
module_param(spdअगर_aclink, पूर्णांक, 0444);
MODULE_PARM_DESC(spdअगर_aclink, "S/PDIF over AC-link.");
module_param(inside_vm, bपूर्णांक, 0444);
MODULE_PARM_DESC(inside_vm, "KVM/Parallels optimization.");

/* just क्रम backward compatibility */
अटल bool enable;
module_param(enable, bool, 0444);
अटल पूर्णांक joystick;
module_param(joystick, पूर्णांक, 0444);

/*
 *  Direct रेजिस्टरs
 */
क्रमागत अणु DEVICE_INTEL, DEVICE_INTEL_ICH4, DEVICE_SIS, DEVICE_ALI, DEVICE_NFORCE पूर्ण;

#घोषणा ICHREG(x) ICH_REG_##x

#घोषणा DEFINE_REGSET(name,base) \
क्रमागत अणु \
	ICH_REG_##name##_BDBAR	= base + 0x0,	/* dword - buffer descriptor list base address */ \
	ICH_REG_##name##_CIV	= base + 0x04,	/* byte - current index value */ \
	ICH_REG_##name##_LVI	= base + 0x05,	/* byte - last valid index */ \
	ICH_REG_##name##_SR	= base + 0x06,	/* byte - status रेजिस्टर */ \
	ICH_REG_##name##_PICB	= base + 0x08,	/* word - position in current buffer */ \
	ICH_REG_##name##_PIV	= base + 0x0a,	/* byte - prefetched index value */ \
	ICH_REG_##name##_CR	= base + 0x0b,	/* byte - control रेजिस्टर */ \
पूर्ण;

/* busmaster blocks */
DEFINE_REGSET(OFF, 0);		/* offset */
DEFINE_REGSET(PI, 0x00);	/* PCM in */
DEFINE_REGSET(PO, 0x10);	/* PCM out */
DEFINE_REGSET(MC, 0x20);	/* Mic in */

/* ICH4 busmaster blocks */
DEFINE_REGSET(MC2, 0x40);	/* Mic in 2 */
DEFINE_REGSET(PI2, 0x50);	/* PCM in 2 */
DEFINE_REGSET(SP, 0x60);	/* SPDIF out */

/* values क्रम each busmaster block */

/* LVI */
#घोषणा ICH_REG_LVI_MASK		0x1f

/* SR */
#घोषणा ICH_FIFOE			0x10	/* FIFO error */
#घोषणा ICH_BCIS			0x08	/* buffer completion पूर्णांकerrupt status */
#घोषणा ICH_LVBCI			0x04	/* last valid buffer completion पूर्णांकerrupt */
#घोषणा ICH_CELV			0x02	/* current equals last valid */
#घोषणा ICH_DCH				0x01	/* DMA controller halted */

/* PIV */
#घोषणा ICH_REG_PIV_MASK		0x1f	/* mask */

/* CR */
#घोषणा ICH_IOCE			0x10	/* पूर्णांकerrupt on completion enable */
#घोषणा ICH_FEIE			0x08	/* fअगरo error पूर्णांकerrupt enable */
#घोषणा ICH_LVBIE			0x04	/* last valid buffer पूर्णांकerrupt enable */
#घोषणा ICH_RESETREGS			0x02	/* reset busmaster रेजिस्टरs */
#घोषणा ICH_STARTBM			0x01	/* start busmaster operation */


/* global block */
#घोषणा ICH_REG_GLOB_CNT		0x2c	/* dword - global control */
#घोषणा   ICH_PCM_SPDIF_MASK	0xc0000000	/* s/pdअगर pcm slot mask (ICH4) */
#घोषणा   ICH_PCM_SPDIF_NONE	0x00000000	/* reserved - undefined */
#घोषणा   ICH_PCM_SPDIF_78	0x40000000	/* s/pdअगर pcm on slots 7&8 */
#घोषणा   ICH_PCM_SPDIF_69	0x80000000	/* s/pdअगर pcm on slots 6&9 */
#घोषणा   ICH_PCM_SPDIF_1011	0xc0000000	/* s/pdअगर pcm on slots 10&11 */
#घोषणा   ICH_PCM_20BIT		0x00400000	/* 20-bit samples (ICH4) */
#घोषणा   ICH_PCM_246_MASK	0x00300000	/* chan mask (not all chips) */
#घोषणा   ICH_PCM_8		0x00300000      /* 8 channels (not all chips) */
#घोषणा   ICH_PCM_6		0x00200000	/* 6 channels (not all chips) */
#घोषणा   ICH_PCM_4		0x00100000	/* 4 channels (not all chips) */
#घोषणा   ICH_PCM_2		0x00000000	/* 2 channels (stereo) */
#घोषणा   ICH_SIS_PCM_246_MASK	0x000000c0	/* 6 channels (SIS7012) */
#घोषणा   ICH_SIS_PCM_6		0x00000080	/* 6 channels (SIS7012) */
#घोषणा   ICH_SIS_PCM_4		0x00000040	/* 4 channels (SIS7012) */
#घोषणा   ICH_SIS_PCM_2		0x00000000	/* 2 channels (SIS7012) */
#घोषणा   ICH_TRIE		0x00000040	/* tertiary resume पूर्णांकerrupt enable */
#घोषणा   ICH_SRIE		0x00000020	/* secondary resume पूर्णांकerrupt enable */
#घोषणा   ICH_PRIE		0x00000010	/* primary resume पूर्णांकerrupt enable */
#घोषणा   ICH_ACLINK		0x00000008	/* AClink shut off */
#घोषणा   ICH_AC97WARM		0x00000004	/* AC'97 warm reset */
#घोषणा   ICH_AC97COLD		0x00000002	/* AC'97 cold reset */
#घोषणा   ICH_GIE		0x00000001	/* GPI पूर्णांकerrupt enable */
#घोषणा ICH_REG_GLOB_STA		0x30	/* dword - global status */
#घोषणा   ICH_TRI		0x20000000	/* ICH4: tertiary (AC_SDIN2) resume पूर्णांकerrupt */
#घोषणा   ICH_TCR		0x10000000	/* ICH4: tertiary (AC_SDIN2) codec पढ़ोy */
#घोषणा   ICH_BCS		0x08000000	/* ICH4: bit घड़ी stopped */
#घोषणा   ICH_SPINT		0x04000000	/* ICH4: S/PDIF पूर्णांकerrupt */
#घोषणा   ICH_P2INT		0x02000000	/* ICH4: PCM2-In पूर्णांकerrupt */
#घोषणा   ICH_M2INT		0x01000000	/* ICH4: Mic2-In पूर्णांकerrupt */
#घोषणा   ICH_SAMPLE_CAP	0x00c00000	/* ICH4: sample capability bits (RO) */
#घोषणा   ICH_SAMPLE_16_20	0x00400000	/* ICH4: 16- and 20-bit samples */
#घोषणा   ICH_MULTICHAN_CAP	0x00300000	/* ICH4: multi-channel capability bits (RO) */
#घोषणा   ICH_SIS_TRI		0x00080000	/* SIS: tertiary resume irq */
#घोषणा   ICH_SIS_TCR		0x00040000	/* SIS: tertiary codec पढ़ोy */
#घोषणा   ICH_MD3		0x00020000	/* modem घातer करोwn semaphore */
#घोषणा   ICH_AD3		0x00010000	/* audio घातer करोwn semaphore */
#घोषणा   ICH_RCS		0x00008000	/* पढ़ो completion status */
#घोषणा   ICH_BIT3		0x00004000	/* bit 3 slot 12 */
#घोषणा   ICH_BIT2		0x00002000	/* bit 2 slot 12 */
#घोषणा   ICH_BIT1		0x00001000	/* bit 1 slot 12 */
#घोषणा   ICH_SRI		0x00000800	/* secondary (AC_SDIN1) resume पूर्णांकerrupt */
#घोषणा   ICH_PRI		0x00000400	/* primary (AC_SDIN0) resume पूर्णांकerrupt */
#घोषणा   ICH_SCR		0x00000200	/* secondary (AC_SDIN1) codec पढ़ोy */
#घोषणा   ICH_PCR		0x00000100	/* primary (AC_SDIN0) codec पढ़ोy */
#घोषणा   ICH_MCINT		0x00000080	/* MIC capture पूर्णांकerrupt */
#घोषणा   ICH_POINT		0x00000040	/* playback पूर्णांकerrupt */
#घोषणा   ICH_PIINT		0x00000020	/* capture पूर्णांकerrupt */
#घोषणा   ICH_NVSPINT		0x00000010	/* nक्रमce spdअगर पूर्णांकerrupt */
#घोषणा   ICH_MOINT		0x00000004	/* modem playback पूर्णांकerrupt */
#घोषणा   ICH_MIINT		0x00000002	/* modem capture पूर्णांकerrupt */
#घोषणा   ICH_GSCI		0x00000001	/* GPI status change पूर्णांकerrupt */
#घोषणा ICH_REG_ACC_SEMA		0x34	/* byte - codec ग_लिखो semaphore */
#घोषणा   ICH_CAS		0x01		/* codec access semaphore */
#घोषणा ICH_REG_SDM		0x80
#घोषणा   ICH_DI2L_MASK		0x000000c0	/* PCM In 2, Mic In 2 data in line */
#घोषणा   ICH_DI2L_SHIFT	6
#घोषणा   ICH_DI1L_MASK		0x00000030	/* PCM In 1, Mic In 1 data in line */
#घोषणा   ICH_DI1L_SHIFT	4
#घोषणा   ICH_SE		0x00000008	/* steer enable */
#घोषणा   ICH_LDI_MASK		0x00000003	/* last codec पढ़ो data input */

#घोषणा ICH_MAX_FRAGS		32		/* max hw frags */


/*
 * रेजिस्टरs क्रम Ali5455
 */

/* ALi 5455 busmaster blocks */
DEFINE_REGSET(AL_PI, 0x40);	/* ALi PCM in */
DEFINE_REGSET(AL_PO, 0x50);	/* Ali PCM out */
DEFINE_REGSET(AL_MC, 0x60);	/* Ali Mic in */
DEFINE_REGSET(AL_CDC_SPO, 0x70);	/* Ali Codec SPDIF out */
DEFINE_REGSET(AL_CENTER, 0x80);		/* Ali center out */
DEFINE_REGSET(AL_LFE, 0x90);		/* Ali center out */
DEFINE_REGSET(AL_CLR_SPI, 0xa0);	/* Ali Controller SPDIF in */
DEFINE_REGSET(AL_CLR_SPO, 0xb0);	/* Ali Controller SPDIF out */
DEFINE_REGSET(AL_I2S, 0xc0);	/* Ali I2S in */
DEFINE_REGSET(AL_PI2, 0xd0);	/* Ali PCM2 in */
DEFINE_REGSET(AL_MC2, 0xe0);	/* Ali Mic2 in */

क्रमागत अणु
	ICH_REG_ALI_SCR = 0x00,		/* System Control Register */
	ICH_REG_ALI_SSR = 0x04,		/* System Status Register  */
	ICH_REG_ALI_DMACR = 0x08,	/* DMA Control Register    */
	ICH_REG_ALI_FIFOCR1 = 0x0c,	/* FIFO Control Register 1  */
	ICH_REG_ALI_INTERFACECR = 0x10,	/* Interface Control Register */
	ICH_REG_ALI_INTERRUPTCR = 0x14,	/* Interrupt control Register */
	ICH_REG_ALI_INTERRUPTSR = 0x18,	/* Interrupt  Status Register */
	ICH_REG_ALI_FIFOCR2 = 0x1c,	/* FIFO Control Register 2   */
	ICH_REG_ALI_CPR = 0x20,		/* Command Port Register     */
	ICH_REG_ALI_CPR_ADDR = 0x22,	/* ac97 addr ग_लिखो */
	ICH_REG_ALI_SPR = 0x24,		/* Status Port Register      */
	ICH_REG_ALI_SPR_ADDR = 0x26,	/* ac97 addr पढ़ो */
	ICH_REG_ALI_FIFOCR3 = 0x2c,	/* FIFO Control Register 3  */
	ICH_REG_ALI_TTSR = 0x30,	/* Transmit Tag Slot Register */
	ICH_REG_ALI_RTSR = 0x34,	/* Receive Tag Slot  Register */
	ICH_REG_ALI_CSPSR = 0x38,	/* Command/Status Port Status Register */
	ICH_REG_ALI_CAS = 0x3c,		/* Codec Write Semaphore Register */
	ICH_REG_ALI_HWVOL = 0xf0,	/* hardware volume control/status */
	ICH_REG_ALI_I2SCR = 0xf4,	/* I2S control/status */
	ICH_REG_ALI_SPDIFCSR = 0xf8,	/* spdअगर channel status रेजिस्टर  */
	ICH_REG_ALI_SPDIFICS = 0xfc,	/* spdअगर पूर्णांकerface control/status  */
पूर्ण;

#घोषणा ALI_CAS_SEM_BUSY	0x80000000
#घोषणा ALI_CPR_ADDR_SECONDARY	0x100
#घोषणा ALI_CPR_ADDR_READ	0x80
#घोषणा ALI_CSPSR_CODEC_READY	0x08
#घोषणा ALI_CSPSR_READ_OK	0x02
#घोषणा ALI_CSPSR_WRITE_OK	0x01

/* पूर्णांकerrupts क्रम the whole chip by पूर्णांकerrupt status रेजिस्टर finish */
 
#घोषणा ALI_INT_MICIN2		(1<<26)
#घोषणा ALI_INT_PCMIN2		(1<<25)
#घोषणा ALI_INT_I2SIN		(1<<24)
#घोषणा ALI_INT_SPDIFOUT	(1<<23)	/* controller spdअगर out INTERRUPT */
#घोषणा ALI_INT_SPDIFIN		(1<<22)
#घोषणा ALI_INT_LFEOUT		(1<<21)
#घोषणा ALI_INT_CENTEROUT	(1<<20)
#घोषणा ALI_INT_CODECSPDIFOUT	(1<<19)
#घोषणा ALI_INT_MICIN		(1<<18)
#घोषणा ALI_INT_PCMOUT		(1<<17)
#घोषणा ALI_INT_PCMIN		(1<<16)
#घोषणा ALI_INT_CPRAIS		(1<<7)	/* command port available */
#घोषणा ALI_INT_SPRAIS		(1<<5)	/* status port available */
#घोषणा ALI_INT_GPIO		(1<<1)
#घोषणा ALI_INT_MASK		(ALI_INT_SPDIFOUT|ALI_INT_CODECSPDIFOUT|\
				 ALI_INT_MICIN|ALI_INT_PCMOUT|ALI_INT_PCMIN)

#घोषणा ICH_ALI_SC_RESET	(1<<31)	/* master reset */
#घोषणा ICH_ALI_SC_AC97_DBL	(1<<30)
#घोषणा ICH_ALI_SC_CODEC_SPDF	(3<<20)	/* 1=7/8, 2=6/9, 3=10/11 */
#घोषणा ICH_ALI_SC_IN_BITS	(3<<18)
#घोषणा ICH_ALI_SC_OUT_BITS	(3<<16)
#घोषणा ICH_ALI_SC_6CH_CFG	(3<<14)
#घोषणा ICH_ALI_SC_PCM_4	(1<<8)
#घोषणा ICH_ALI_SC_PCM_6	(2<<8)
#घोषणा ICH_ALI_SC_PCM_246_MASK	(3<<8)

#घोषणा ICH_ALI_SS_SEC_ID	(3<<5)
#घोषणा ICH_ALI_SS_PRI_ID	(3<<3)

#घोषणा ICH_ALI_IF_AC97SP	(1<<21)
#घोषणा ICH_ALI_IF_MC		(1<<20)
#घोषणा ICH_ALI_IF_PI		(1<<19)
#घोषणा ICH_ALI_IF_MC2		(1<<18)
#घोषणा ICH_ALI_IF_PI2		(1<<17)
#घोषणा ICH_ALI_IF_LINE_SRC	(1<<15)	/* 0/1 = slot 3/6 */
#घोषणा ICH_ALI_IF_MIC_SRC	(1<<14)	/* 0/1 = slot 3/6 */
#घोषणा ICH_ALI_IF_SPDF_SRC	(3<<12)	/* 00 = PCM, 01 = AC97-in, 10 = spdअगर-in, 11 = i2s */
#घोषणा ICH_ALI_IF_AC97_OUT	(3<<8)	/* 00 = PCM, 10 = spdअगर-in, 11 = i2s */
#घोषणा ICH_ALI_IF_PO_SPDF	(1<<3)
#घोषणा ICH_ALI_IF_PO		(1<<1)

/*
 *  
 */

क्रमागत अणु
	ICHD_PCMIN,
	ICHD_PCMOUT,
	ICHD_MIC,
	ICHD_MIC2,
	ICHD_PCM2IN,
	ICHD_SPBAR,
	ICHD_LAST = ICHD_SPBAR
पूर्ण;
क्रमागत अणु
	NVD_PCMIN,
	NVD_PCMOUT,
	NVD_MIC,
	NVD_SPBAR,
	NVD_LAST = NVD_SPBAR
पूर्ण;
क्रमागत अणु
	ALID_PCMIN,
	ALID_PCMOUT,
	ALID_MIC,
	ALID_AC97SPDIFOUT,
	ALID_SPDIFIN,
	ALID_SPDIFOUT,
	ALID_LAST = ALID_SPDIFOUT
पूर्ण;

#घोषणा get_ichdev(substream) (substream->runसमय->निजी_data)

काष्ठा ichdev अणु
	अचिन्हित पूर्णांक ichd;			/* ich device number */
	अचिन्हित दीर्घ reg_offset;		/* offset to bmaddr */
	__le32 *bdbar;				/* CPU address (32bit) */
	अचिन्हित पूर्णांक bdbar_addr;		/* PCI bus address (32bit) */
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित पूर्णांक physbuf;			/* physical address (32bit) */
        अचिन्हित पूर्णांक size;
        अचिन्हित पूर्णांक fragsize;
        अचिन्हित पूर्णांक fragsize1;
        अचिन्हित पूर्णांक position;
	अचिन्हित पूर्णांक pos_shअगरt;
	अचिन्हित पूर्णांक last_pos;
        पूर्णांक frags;
        पूर्णांक lvi;
        पूर्णांक lvi_frag;
	पूर्णांक civ;
	पूर्णांक ack;
	पूर्णांक ack_reload;
	अचिन्हित पूर्णांक ack_bit;
	अचिन्हित पूर्णांक roff_sr;
	अचिन्हित पूर्णांक roff_picb;
	अचिन्हित पूर्णांक पूर्णांक_sta_mask;		/* पूर्णांकerrupt status mask */
	अचिन्हित पूर्णांक ali_slot;			/* ALI DMA slot */
	काष्ठा ac97_pcm *pcm;
	पूर्णांक pcm_खोलो_flag;
	अचिन्हित पूर्णांक prepared:1;
	अचिन्हित पूर्णांक suspended: 1;
पूर्ण;

काष्ठा पूर्णांकel8x0 अणु
	अचिन्हित पूर्णांक device_type;

	पूर्णांक irq;

	व्योम __iomem *addr;
	व्योम __iomem *bmaddr;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;

	पूर्णांक pcm_devs;
	काष्ठा snd_pcm *pcm[6];
	काष्ठा ichdev ichd[6];

	अचिन्हित multi4: 1,
		 multi6: 1,
		 multi8 :1,
		 dra: 1,
		 smp20bit: 1;
	अचिन्हित in_ac97_init: 1,
		 in_sdin_init: 1;
	अचिन्हित in_measurement: 1;	/* during ac97 घड़ी measurement */
	अचिन्हित fix_nocache: 1; 	/* workaround क्रम 440MX */
	अचिन्हित buggy_irq: 1;		/* workaround क्रम buggy mobos */
	अचिन्हित xbox: 1;		/* workaround क्रम Xbox AC'97 detection */
	अचिन्हित buggy_semaphore: 1;	/* workaround क्रम buggy codec semaphore */
	अचिन्हित inside_vm: 1;		/* enable VM optimization */

	पूर्णांक spdअगर_idx;	/* SPDIF BAR index; *_SPBAR or -1 अगर use PCMOUT */
	अचिन्हित पूर्णांक sdm_saved;	/* SDM reg value */

	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97[3];
	अचिन्हित पूर्णांक ac97_sdin[3];
	अचिन्हित पूर्णांक max_codecs, ncodecs;
	स्थिर अचिन्हित पूर्णांक *codec_bit;
	अचिन्हित पूर्णांक codec_isr_bits;
	अचिन्हित पूर्णांक codec_पढ़ोy_bits;

	spinlock_t reg_lock;
	
	u32 bdbars_count;
	काष्ठा snd_dma_buffer bdbars;
	u32 पूर्णांक_sta_reg;		/* पूर्णांकerrupt status रेजिस्टर */
	u32 पूर्णांक_sta_mask;		/* पूर्णांकerrupt status mask */
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_पूर्णांकel8x0_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x2415), DEVICE_INTEL पूर्ण,	/* 82801AA */
	अणु PCI_VDEVICE(INTEL, 0x2425), DEVICE_INTEL पूर्ण,	/* 82901AB */
	अणु PCI_VDEVICE(INTEL, 0x2445), DEVICE_INTEL पूर्ण,	/* 82801BA */
	अणु PCI_VDEVICE(INTEL, 0x2485), DEVICE_INTEL पूर्ण,	/* ICH3 */
	अणु PCI_VDEVICE(INTEL, 0x24c5), DEVICE_INTEL_ICH4 पूर्ण, /* ICH4 */
	अणु PCI_VDEVICE(INTEL, 0x24d5), DEVICE_INTEL_ICH4 पूर्ण, /* ICH5 */
	अणु PCI_VDEVICE(INTEL, 0x25a6), DEVICE_INTEL_ICH4 पूर्ण, /* ESB */
	अणु PCI_VDEVICE(INTEL, 0x266e), DEVICE_INTEL_ICH4 पूर्ण, /* ICH6 */
	अणु PCI_VDEVICE(INTEL, 0x27de), DEVICE_INTEL_ICH4 पूर्ण, /* ICH7 */
	अणु PCI_VDEVICE(INTEL, 0x2698), DEVICE_INTEL_ICH4 पूर्ण, /* ESB2 */
	अणु PCI_VDEVICE(INTEL, 0x7195), DEVICE_INTEL पूर्ण,	/* 440MX */
	अणु PCI_VDEVICE(SI, 0x7012), DEVICE_SIS पूर्ण,	/* SI7012 */
	अणु PCI_VDEVICE(NVIDIA, 0x01b1), DEVICE_NFORCE पूर्ण,	/* NFORCE */
	अणु PCI_VDEVICE(NVIDIA, 0x003a), DEVICE_NFORCE पूर्ण,	/* MCP04 */
	अणु PCI_VDEVICE(NVIDIA, 0x006a), DEVICE_NFORCE पूर्ण,	/* NFORCE2 */
	अणु PCI_VDEVICE(NVIDIA, 0x0059), DEVICE_NFORCE पूर्ण,	/* CK804 */
	अणु PCI_VDEVICE(NVIDIA, 0x008a), DEVICE_NFORCE पूर्ण,	/* CK8 */
	अणु PCI_VDEVICE(NVIDIA, 0x00da), DEVICE_NFORCE पूर्ण,	/* NFORCE3 */
	अणु PCI_VDEVICE(NVIDIA, 0x00ea), DEVICE_NFORCE पूर्ण,	/* CK8S */
	अणु PCI_VDEVICE(NVIDIA, 0x026b), DEVICE_NFORCE पूर्ण,	/* MCP51 */
	अणु PCI_VDEVICE(AMD, 0x746d), DEVICE_INTEL पूर्ण,	/* AMD8111 */
	अणु PCI_VDEVICE(AMD, 0x7445), DEVICE_INTEL पूर्ण,	/* AMD768 */
	अणु PCI_VDEVICE(AL, 0x5455), DEVICE_ALI पूर्ण,   /* Ali5455 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_पूर्णांकel8x0_ids);

/*
 *  Lowlevel I/O - busmaster
 */

अटल अंतरभूत u8 igetbyte(काष्ठा पूर्णांकel8x0 *chip, u32 offset)
अणु
	वापस ioपढ़ो8(chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत u16 igetword(काष्ठा पूर्णांकel8x0 *chip, u32 offset)
अणु
	वापस ioपढ़ो16(chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत u32 igetdword(काष्ठा पूर्णांकel8x0 *chip, u32 offset)
अणु
	वापस ioपढ़ो32(chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत व्योम iputbyte(काष्ठा पूर्णांकel8x0 *chip, u32 offset, u8 val)
अणु
	ioग_लिखो8(val, chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत व्योम iputword(काष्ठा पूर्णांकel8x0 *chip, u32 offset, u16 val)
अणु
	ioग_लिखो16(val, chip->bmaddr + offset);
पूर्ण

अटल अंतरभूत व्योम iputdword(काष्ठा पूर्णांकel8x0 *chip, u32 offset, u32 val)
अणु
	ioग_लिखो32(val, chip->bmaddr + offset);
पूर्ण

/*
 *  Lowlevel I/O - AC'97 रेजिस्टरs
 */

अटल अंतरभूत u16 iagetword(काष्ठा पूर्णांकel8x0 *chip, u32 offset)
अणु
	वापस ioपढ़ो16(chip->addr + offset);
पूर्ण

अटल अंतरभूत व्योम iaputword(काष्ठा पूर्णांकel8x0 *chip, u32 offset, u16 val)
अणु
	ioग_लिखो16(val, chip->addr + offset);
पूर्ण

/*
 *  Basic I/O
 */

/*
 * access to AC97 codec via normal i/o (क्रम ICH and SIS7012)
 */

अटल पूर्णांक snd_पूर्णांकel8x0_codec_semaphore(काष्ठा पूर्णांकel8x0 *chip, अचिन्हित पूर्णांक codec)
अणु
	पूर्णांक समय;
	
	अगर (codec > 2)
		वापस -EIO;
	अगर (chip->in_sdin_init) अणु
		/* we करोn't know the पढ़ोy bit assignment at the moment */
		/* so we check any */
		codec = chip->codec_isr_bits;
	पूर्ण अन्यथा अणु
		codec = chip->codec_bit[chip->ac97_sdin[codec]];
	पूर्ण

	/* codec पढ़ोy ? */
	अगर ((igetdword(chip, ICHREG(GLOB_STA)) & codec) == 0)
		वापस -EIO;

	अगर (chip->buggy_semaphore)
		वापस 0; /* just ignore ... */

	/* Anyone holding a semaphore क्रम 1 msec should be shot... */
	समय = 100;
      	करो अणु
      		अगर (!(igetbyte(chip, ICHREG(ACC_SEMA)) & ICH_CAS))
      			वापस 0;
		udelay(10);
	पूर्ण जबतक (समय--);

	/* access to some क्रमbidden (non existent) ac97 रेजिस्टरs will not
	 * reset the semaphore. So even अगर you करोn't get the semaphore, still
	 * जारी the access. We करोn't need the semaphore anyway. */
	dev_err(chip->card->dev,
		"codec_semaphore: semaphore is not ready [0x%x][0x%x]\n",
			igetbyte(chip, ICHREG(ACC_SEMA)), igetdword(chip, ICHREG(GLOB_STA)));
	iagetword(chip, 0);	/* clear semaphore flag */
	/* I करोn't care about the semaphore */
	वापस -EBUSY;
पूर्ण
 
अटल व्योम snd_पूर्णांकel8x0_codec_ग_लिखो(काष्ठा snd_ac97 *ac97,
				     अचिन्हित लघु reg,
				     अचिन्हित लघु val)
अणु
	काष्ठा पूर्णांकel8x0 *chip = ac97->निजी_data;
	
	अगर (snd_पूर्णांकel8x0_codec_semaphore(chip, ac97->num) < 0) अणु
		अगर (! chip->in_ac97_init)
			dev_err(chip->card->dev,
				"codec_write %d: semaphore is not ready for register 0x%x\n",
				ac97->num, reg);
	पूर्ण
	iaputword(chip, reg + ac97->num * 0x80, val);
पूर्ण

अटल अचिन्हित लघु snd_पूर्णांकel8x0_codec_पढ़ो(काष्ठा snd_ac97 *ac97,
					      अचिन्हित लघु reg)
अणु
	काष्ठा पूर्णांकel8x0 *chip = ac97->निजी_data;
	अचिन्हित लघु res;
	अचिन्हित पूर्णांक पंचांगp;

	अगर (snd_पूर्णांकel8x0_codec_semaphore(chip, ac97->num) < 0) अणु
		अगर (! chip->in_ac97_init)
			dev_err(chip->card->dev,
				"codec_read %d: semaphore is not ready for register 0x%x\n",
				ac97->num, reg);
		res = 0xffff;
	पूर्ण अन्यथा अणु
		res = iagetword(chip, reg + ac97->num * 0x80);
		अगर ((पंचांगp = igetdword(chip, ICHREG(GLOB_STA))) & ICH_RCS) अणु
			/* reset RCS and preserve other R/WC bits */
			iputdword(chip, ICHREG(GLOB_STA), पंचांगp &
				  ~(chip->codec_पढ़ोy_bits | ICH_GSCI));
			अगर (! chip->in_ac97_init)
				dev_err(chip->card->dev,
					"codec_read %d: read timeout for register 0x%x\n",
					ac97->num, reg);
			res = 0xffff;
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम snd_पूर्णांकel8x0_codec_पढ़ो_test(काष्ठा पूर्णांकel8x0 *chip,
					 अचिन्हित पूर्णांक codec)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	अगर (snd_पूर्णांकel8x0_codec_semaphore(chip, codec) >= 0) अणु
		iagetword(chip, codec * 0x80);
		अगर ((पंचांगp = igetdword(chip, ICHREG(GLOB_STA))) & ICH_RCS) अणु
			/* reset RCS and preserve other R/WC bits */
			iputdword(chip, ICHREG(GLOB_STA), पंचांगp &
				  ~(chip->codec_पढ़ोy_bits | ICH_GSCI));
		पूर्ण
	पूर्ण
पूर्ण

/*
 * access to AC97 क्रम Ali5455
 */
अटल पूर्णांक snd_पूर्णांकel8x0_ali_codec_पढ़ोy(काष्ठा पूर्णांकel8x0 *chip, पूर्णांक mask)
अणु
	पूर्णांक count = 0;
	क्रम (count = 0; count < 0x7f; count++) अणु
		पूर्णांक val = igetbyte(chip, ICHREG(ALI_CSPSR));
		अगर (val & mask)
			वापस 0;
	पूर्ण
	अगर (! chip->in_ac97_init)
		dev_warn(chip->card->dev, "AC97 codec ready timeout.\n");
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_ali_codec_semaphore(काष्ठा पूर्णांकel8x0 *chip)
अणु
	पूर्णांक समय = 100;
	अगर (chip->buggy_semaphore)
		वापस 0; /* just ignore ... */
	जबतक (--समय && (igetdword(chip, ICHREG(ALI_CAS)) & ALI_CAS_SEM_BUSY))
		udelay(1);
	अगर (! समय && ! chip->in_ac97_init)
		dev_warn(chip->card->dev, "ali_codec_semaphore timeout\n");
	वापस snd_पूर्णांकel8x0_ali_codec_पढ़ोy(chip, ALI_CSPSR_CODEC_READY);
पूर्ण

अटल अचिन्हित लघु snd_पूर्णांकel8x0_ali_codec_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा पूर्णांकel8x0 *chip = ac97->निजी_data;
	अचिन्हित लघु data = 0xffff;

	अगर (snd_पूर्णांकel8x0_ali_codec_semaphore(chip))
		जाओ __err;
	reg |= ALI_CPR_ADDR_READ;
	अगर (ac97->num)
		reg |= ALI_CPR_ADDR_SECONDARY;
	iputword(chip, ICHREG(ALI_CPR_ADDR), reg);
	अगर (snd_पूर्णांकel8x0_ali_codec_पढ़ोy(chip, ALI_CSPSR_READ_OK))
		जाओ __err;
	data = igetword(chip, ICHREG(ALI_SPR));
 __err:
	वापस data;
पूर्ण

अटल व्योम snd_पूर्णांकel8x0_ali_codec_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
					 अचिन्हित लघु val)
अणु
	काष्ठा पूर्णांकel8x0 *chip = ac97->निजी_data;

	अगर (snd_पूर्णांकel8x0_ali_codec_semaphore(chip))
		वापस;
	iputword(chip, ICHREG(ALI_CPR), val);
	अगर (ac97->num)
		reg |= ALI_CPR_ADDR_SECONDARY;
	iputword(chip, ICHREG(ALI_CPR_ADDR), reg);
	snd_पूर्णांकel8x0_ali_codec_पढ़ोy(chip, ALI_CSPSR_WRITE_OK);
पूर्ण


/*
 * DMA I/O
 */
अटल व्योम snd_पूर्णांकel8x0_setup_periods(काष्ठा पूर्णांकel8x0 *chip, काष्ठा ichdev *ichdev) 
अणु
	पूर्णांक idx;
	__le32 *bdbar = ichdev->bdbar;
	अचिन्हित दीर्घ port = ichdev->reg_offset;

	iputdword(chip, port + ICH_REG_OFF_BDBAR, ichdev->bdbar_addr);
	अगर (ichdev->size == ichdev->fragsize) अणु
		ichdev->ack_reload = ichdev->ack = 2;
		ichdev->fragsize1 = ichdev->fragsize >> 1;
		क्रम (idx = 0; idx < (ICH_REG_LVI_MASK + 1) * 2; idx += 4) अणु
			bdbar[idx + 0] = cpu_to_le32(ichdev->physbuf);
			bdbar[idx + 1] = cpu_to_le32(0x80000000 | /* पूर्णांकerrupt on completion */
						     ichdev->fragsize1 >> ichdev->pos_shअगरt);
			bdbar[idx + 2] = cpu_to_le32(ichdev->physbuf + (ichdev->size >> 1));
			bdbar[idx + 3] = cpu_to_le32(0x80000000 | /* पूर्णांकerrupt on completion */
						     ichdev->fragsize1 >> ichdev->pos_shअगरt);
		पूर्ण
		ichdev->frags = 2;
	पूर्ण अन्यथा अणु
		ichdev->ack_reload = ichdev->ack = 1;
		ichdev->fragsize1 = ichdev->fragsize;
		क्रम (idx = 0; idx < (ICH_REG_LVI_MASK + 1) * 2; idx += 2) अणु
			bdbar[idx + 0] = cpu_to_le32(ichdev->physbuf +
						     (((idx >> 1) * ichdev->fragsize) %
						      ichdev->size));
			bdbar[idx + 1] = cpu_to_le32(0x80000000 | /* पूर्णांकerrupt on completion */
						     ichdev->fragsize >> ichdev->pos_shअगरt);
#अगर 0
			dev_dbg(chip->card->dev, "bdbar[%i] = 0x%x [0x%x]\n",
			       idx + 0, bdbar[idx + 0], bdbar[idx + 1]);
#पूर्ण_अगर
		पूर्ण
		ichdev->frags = ichdev->size / ichdev->fragsize;
	पूर्ण
	iputbyte(chip, port + ICH_REG_OFF_LVI, ichdev->lvi = ICH_REG_LVI_MASK);
	ichdev->civ = 0;
	iputbyte(chip, port + ICH_REG_OFF_CIV, 0);
	ichdev->lvi_frag = ICH_REG_LVI_MASK % ichdev->frags;
	ichdev->position = 0;
#अगर 0
	dev_dbg(chip->card->dev,
		"lvi_frag = %i, frags = %i, period_size = 0x%x, period_size1 = 0x%x\n",
	       ichdev->lvi_frag, ichdev->frags, ichdev->fragsize,
	       ichdev->fragsize1);
#पूर्ण_अगर
	/* clear पूर्णांकerrupts */
	iputbyte(chip, port + ichdev->roff_sr, ICH_FIFOE | ICH_BCIS | ICH_LVBCI);
पूर्ण

/*
 *  Interrupt handler
 */

अटल अंतरभूत व्योम snd_पूर्णांकel8x0_update(काष्ठा पूर्णांकel8x0 *chip, काष्ठा ichdev *ichdev)
अणु
	अचिन्हित दीर्घ port = ichdev->reg_offset;
	अचिन्हित दीर्घ flags;
	पूर्णांक status, civ, i, step;
	पूर्णांक ack = 0;

	अगर (!ichdev->prepared || ichdev->suspended)
		वापस;

	spin_lock_irqsave(&chip->reg_lock, flags);
	status = igetbyte(chip, port + ichdev->roff_sr);
	civ = igetbyte(chip, port + ICH_REG_OFF_CIV);
	अगर (!(status & ICH_BCIS)) अणु
		step = 0;
	पूर्ण अन्यथा अगर (civ == ichdev->civ) अणु
		// snd_prपूर्णांकd("civ same %d\n", civ);
		step = 1;
		ichdev->civ++;
		ichdev->civ &= ICH_REG_LVI_MASK;
	पूर्ण अन्यथा अणु
		step = civ - ichdev->civ;
		अगर (step < 0)
			step += ICH_REG_LVI_MASK + 1;
		// अगर (step != 1)
		//	snd_prपूर्णांकd("step = %d, %d -> %d\n", step, ichdev->civ, civ);
		ichdev->civ = civ;
	पूर्ण

	ichdev->position += step * ichdev->fragsize1;
	अगर (! chip->in_measurement)
		ichdev->position %= ichdev->size;
	ichdev->lvi += step;
	ichdev->lvi &= ICH_REG_LVI_MASK;
	iputbyte(chip, port + ICH_REG_OFF_LVI, ichdev->lvi);
	क्रम (i = 0; i < step; i++) अणु
		ichdev->lvi_frag++;
		ichdev->lvi_frag %= ichdev->frags;
		ichdev->bdbar[ichdev->lvi * 2] = cpu_to_le32(ichdev->physbuf + ichdev->lvi_frag * ichdev->fragsize1);
#अगर 0
	dev_dbg(chip->card->dev,
		"new: bdbar[%i] = 0x%x [0x%x], prefetch = %i, all = 0x%x, 0x%x\n",
	       ichdev->lvi * 2, ichdev->bdbar[ichdev->lvi * 2],
	       ichdev->bdbar[ichdev->lvi * 2 + 1], inb(ICH_REG_OFF_PIV + port),
	       inl(port + 4), inb(port + ICH_REG_OFF_CR));
#पूर्ण_अगर
		अगर (--ichdev->ack == 0) अणु
			ichdev->ack = ichdev->ack_reload;
			ack = 1;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	अगर (ack && ichdev->substream) अणु
		snd_pcm_period_elapsed(ichdev->substream);
	पूर्ण
	iputbyte(chip, port + ichdev->roff_sr,
		 status & (ICH_FIFOE | ICH_BCIS | ICH_LVBCI));
पूर्ण

अटल irqवापस_t snd_पूर्णांकel8x0_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा पूर्णांकel8x0 *chip = dev_id;
	काष्ठा ichdev *ichdev;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक i;

	status = igetdword(chip, chip->पूर्णांक_sta_reg);
	अगर (status == 0xffffffff)	/* we are not yet resumed */
		वापस IRQ_NONE;

	अगर ((status & chip->पूर्णांक_sta_mask) == 0) अणु
		अगर (status) अणु
			/* ack */
			iputdword(chip, chip->पूर्णांक_sta_reg, status);
			अगर (! chip->buggy_irq)
				status = 0;
		पूर्ण
		वापस IRQ_RETVAL(status);
	पूर्ण

	क्रम (i = 0; i < chip->bdbars_count; i++) अणु
		ichdev = &chip->ichd[i];
		अगर (status & ichdev->पूर्णांक_sta_mask)
			snd_पूर्णांकel8x0_update(chip, ichdev);
	पूर्ण

	/* ack them */
	iputdword(chip, chip->पूर्णांक_sta_reg, status & chip->पूर्णांक_sta_mask);
	
	वापस IRQ_HANDLED;
पूर्ण

/*
 *  PCM part
 */

अटल पूर्णांक snd_पूर्णांकel8x0_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	काष्ठा ichdev *ichdev = get_ichdev(substream);
	अचिन्हित अक्षर val = 0;
	अचिन्हित दीर्घ port = ichdev->reg_offset;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
		ichdev->suspended = 0;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = ICH_IOCE | ICH_STARTBM;
		ichdev->last_pos = ichdev->position;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		ichdev->suspended = 1;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_STOP:
		val = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = ICH_IOCE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	iputbyte(chip, port + ICH_REG_OFF_CR, val);
	अगर (cmd == SNDRV_PCM_TRIGGER_STOP) अणु
		/* रुको until DMA stopped */
		जबतक (!(igetbyte(chip, port + ichdev->roff_sr) & ICH_DCH)) ;
		/* reset whole DMA things */
		iputbyte(chip, port + ICH_REG_OFF_CR, ICH_RESETREGS);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_ali_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	काष्ठा ichdev *ichdev = get_ichdev(substream);
	अचिन्हित दीर्घ port = ichdev->reg_offset;
	अटल स्थिर पूर्णांक fअगरoreg[] = अणु
		ICHREG(ALI_FIFOCR1), ICHREG(ALI_FIFOCR2), ICHREG(ALI_FIFOCR3)
	पूर्ण;
	अचिन्हित पूर्णांक val, fअगरo;

	val = igetdword(chip, ICHREG(ALI_DMACR));
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
		ichdev->suspended = 0;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			/* clear FIFO क्रम synchronization of channels */
			fअगरo = igetdword(chip, fअगरoreg[ichdev->ali_slot / 4]);
			fअगरo &= ~(0xff << (ichdev->ali_slot % 4));  
			fअगरo |= 0x83 << (ichdev->ali_slot % 4); 
			iputdword(chip, fअगरoreg[ichdev->ali_slot / 4], fअगरo);
		पूर्ण
		iputbyte(chip, port + ICH_REG_OFF_CR, ICH_IOCE);
		val &= ~(1 << (ichdev->ali_slot + 16)); /* clear PAUSE flag */
		/* start DMA */
		iputdword(chip, ICHREG(ALI_DMACR), val | (1 << ichdev->ali_slot));
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		ichdev->suspended = 1;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/* छोड़ो */
		iputdword(chip, ICHREG(ALI_DMACR), val | (1 << (ichdev->ali_slot + 16)));
		iputbyte(chip, port + ICH_REG_OFF_CR, 0);
		जबतक (igetbyte(chip, port + ICH_REG_OFF_CR))
			;
		अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_PUSH)
			अवरोध;
		/* reset whole DMA things */
		iputbyte(chip, port + ICH_REG_OFF_CR, ICH_RESETREGS);
		/* clear पूर्णांकerrupts */
		iputbyte(chip, port + ICH_REG_OFF_SR,
			 igetbyte(chip, port + ICH_REG_OFF_SR) | 0x1e);
		iputdword(chip, ICHREG(ALI_INTERRUPTSR),
			  igetdword(chip, ICHREG(ALI_INTERRUPTSR)) & ichdev->पूर्णांक_sta_mask);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	काष्ठा ichdev *ichdev = get_ichdev(substream);
	पूर्णांक dbl = params_rate(hw_params) > 48000;
	पूर्णांक err;

	अगर (ichdev->pcm_खोलो_flag) अणु
		snd_ac97_pcm_बंद(ichdev->pcm);
		ichdev->pcm_खोलो_flag = 0;
		ichdev->prepared = 0;
	पूर्ण
	err = snd_ac97_pcm_खोलो(ichdev->pcm, params_rate(hw_params),
				params_channels(hw_params),
				ichdev->pcm->r[dbl].slots);
	अगर (err >= 0) अणु
		ichdev->pcm_खोलो_flag = 1;
		/* Force SPDIF setting */
		अगर (ichdev->ichd == ICHD_PCMOUT && chip->spdअगर_idx < 0)
			snd_ac97_set_rate(ichdev->pcm->r[0].codec[0], AC97_SPDIF,
					  params_rate(hw_params));
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ichdev *ichdev = get_ichdev(substream);

	अगर (ichdev->pcm_खोलो_flag) अणु
		snd_ac97_pcm_बंद(ichdev->pcm);
		ichdev->pcm_खोलो_flag = 0;
		ichdev->prepared = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snd_पूर्णांकel8x0_setup_pcm_out(काष्ठा पूर्णांकel8x0 *chip,
				       काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अचिन्हित पूर्णांक cnt;
	पूर्णांक dbl = runसमय->rate > 48000;

	spin_lock_irq(&chip->reg_lock);
	चयन (chip->device_type) अणु
	हाल DEVICE_ALI:
		cnt = igetdword(chip, ICHREG(ALI_SCR));
		cnt &= ~ICH_ALI_SC_PCM_246_MASK;
		अगर (runसमय->channels == 4 || dbl)
			cnt |= ICH_ALI_SC_PCM_4;
		अन्यथा अगर (runसमय->channels == 6)
			cnt |= ICH_ALI_SC_PCM_6;
		iputdword(chip, ICHREG(ALI_SCR), cnt);
		अवरोध;
	हाल DEVICE_SIS:
		cnt = igetdword(chip, ICHREG(GLOB_CNT));
		cnt &= ~ICH_SIS_PCM_246_MASK;
		अगर (runसमय->channels == 4 || dbl)
			cnt |= ICH_SIS_PCM_4;
		अन्यथा अगर (runसमय->channels == 6)
			cnt |= ICH_SIS_PCM_6;
		iputdword(chip, ICHREG(GLOB_CNT), cnt);
		अवरोध;
	शेष:
		cnt = igetdword(chip, ICHREG(GLOB_CNT));
		cnt &= ~(ICH_PCM_246_MASK | ICH_PCM_20BIT);
		अगर (runसमय->channels == 4 || dbl)
			cnt |= ICH_PCM_4;
		अन्यथा अगर (runसमय->channels == 6)
			cnt |= ICH_PCM_6;
		अन्यथा अगर (runसमय->channels == 8)
			cnt |= ICH_PCM_8;
		अगर (chip->device_type == DEVICE_NFORCE) अणु
			/* reset to 2ch once to keep the 6 channel data in alignment,
			 * to start from Front Left always
			 */
			अगर (cnt & ICH_PCM_246_MASK) अणु
				iputdword(chip, ICHREG(GLOB_CNT), cnt & ~ICH_PCM_246_MASK);
				spin_unlock_irq(&chip->reg_lock);
				msleep(50); /* grrr... */
				spin_lock_irq(&chip->reg_lock);
			पूर्ण
		पूर्ण अन्यथा अगर (chip->device_type == DEVICE_INTEL_ICH4) अणु
			अगर (runसमय->sample_bits > 16)
				cnt |= ICH_PCM_20BIT;
		पूर्ण
		iputdword(chip, ICHREG(GLOB_CNT), cnt);
		अवरोध;
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ichdev *ichdev = get_ichdev(substream);

	ichdev->physbuf = runसमय->dma_addr;
	ichdev->size = snd_pcm_lib_buffer_bytes(substream);
	ichdev->fragsize = snd_pcm_lib_period_bytes(substream);
	अगर (ichdev->ichd == ICHD_PCMOUT) अणु
		snd_पूर्णांकel8x0_setup_pcm_out(chip, runसमय);
		अगर (chip->device_type == DEVICE_INTEL_ICH4)
			ichdev->pos_shअगरt = (runसमय->sample_bits > 16) ? 2 : 1;
	पूर्ण
	snd_पूर्णांकel8x0_setup_periods(chip, ichdev);
	ichdev->prepared = 1;
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_पूर्णांकel8x0_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	काष्ठा ichdev *ichdev = get_ichdev(substream);
	माप_प्रकार ptr1, ptr;
	पूर्णांक civ, समयout = 10;
	अचिन्हित पूर्णांक position;

	spin_lock(&chip->reg_lock);
	करो अणु
		civ = igetbyte(chip, ichdev->reg_offset + ICH_REG_OFF_CIV);
		ptr1 = igetword(chip, ichdev->reg_offset + ichdev->roff_picb);
		position = ichdev->position;
		अगर (ptr1 == 0) अणु
			udelay(10);
			जारी;
		पूर्ण
		अगर (civ != igetbyte(chip, ichdev->reg_offset + ICH_REG_OFF_CIV))
			जारी;

		/* IO पढ़ो operation is very expensive inside भव machine
		 * as it is emulated. The probability that subsequent PICB पढ़ो
		 * will वापस dअगरferent result is high enough to loop till
		 * समयout here.
		 * Same CIV is strict enough condition to be sure that PICB
		 * is valid inside VM on emulated card. */
		अगर (chip->inside_vm)
			अवरोध;
		अगर (ptr1 == igetword(chip, ichdev->reg_offset + ichdev->roff_picb))
			अवरोध;
	पूर्ण जबतक (समयout--);
	ptr = ichdev->last_pos;
	अगर (ptr1 != 0) अणु
		ptr1 <<= ichdev->pos_shअगरt;
		ptr = ichdev->fragsize1 - ptr1;
		ptr += position;
		अगर (ptr < ichdev->last_pos) अणु
			अचिन्हित पूर्णांक pos_base, last_base;
			pos_base = position / ichdev->fragsize1;
			last_base = ichdev->last_pos / ichdev->fragsize1;
			/* another sanity check; ptr1 can go back to full
			 * beक्रमe the base position is updated
			 */
			अगर (pos_base == last_base)
				ptr = ichdev->last_pos;
		पूर्ण
	पूर्ण
	ichdev->last_pos = ptr;
	spin_unlock(&chip->reg_lock);
	अगर (ptr >= ichdev->size)
		वापस 0;
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_पूर्णांकel8x0_stream =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE |
				 SNDRV_PCM_INFO_RESUME),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		2,
	.channels_max =		2,
	.buffer_bytes_max =	128 * 1024,
	.period_bytes_min =	32,
	.period_bytes_max =	128 * 1024,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels4[] = अणु
	2, 4,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_channels4 = अणु
	.count = ARRAY_SIZE(channels4),
	.list = channels4,
	.mask = 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels6[] = अणु
	2, 4, 6,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_channels6 = अणु
	.count = ARRAY_SIZE(channels6),
	.list = channels6,
	.mask = 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels8[] = अणु
	2, 4, 6, 8,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_channels8 = अणु
	.count = ARRAY_SIZE(channels8),
	.list = channels8,
	.mask = 0,
पूर्ण;

अटल पूर्णांक snd_पूर्णांकel8x0_pcm_खोलो(काष्ठा snd_pcm_substream *substream, काष्ठा ichdev *ichdev)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	ichdev->substream = substream;
	runसमय->hw = snd_पूर्णांकel8x0_stream;
	runसमय->hw.rates = ichdev->pcm->rates;
	snd_pcm_limit_hw_rates(runसमय);
	अगर (chip->device_type == DEVICE_SIS) अणु
		runसमय->hw.buffer_bytes_max = 64*1024;
		runसमय->hw.period_bytes_max = 64*1024;
	पूर्ण
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;
	runसमय->निजी_data = ichdev;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	err = snd_पूर्णांकel8x0_pcm_खोलो(substream, &chip->ichd[ICHD_PCMOUT]);
	अगर (err < 0)
		वापस err;

	अगर (chip->multi8) अणु
		runसमय->hw.channels_max = 8;
		snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
						SNDRV_PCM_HW_PARAM_CHANNELS,
						&hw_स्थिरraपूर्णांकs_channels8);
	पूर्ण अन्यथा अगर (chip->multi6) अणु
		runसमय->hw.channels_max = 6;
		snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					   &hw_स्थिरraपूर्णांकs_channels6);
	पूर्ण अन्यथा अगर (chip->multi4) अणु
		runसमय->hw.channels_max = 4;
		snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					   &hw_स्थिरraपूर्णांकs_channels4);
	पूर्ण
	अगर (chip->dra) अणु
		snd_ac97_pcm_द्विगुन_rate_rules(runसमय);
	पूर्ण
	अगर (chip->smp20bit) अणु
		runसमय->hw.क्रमmats |= SNDRV_PCM_FMTBIT_S32_LE;
		snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 20);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ICHD_PCMOUT].substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	वापस snd_पूर्णांकel8x0_pcm_खोलो(substream, &chip->ichd[ICHD_PCMIN]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ICHD_PCMIN].substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_mic_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	वापस snd_पूर्णांकel8x0_pcm_खोलो(substream, &chip->ichd[ICHD_MIC]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_mic_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ICHD_MIC].substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_mic2_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	वापस snd_पूर्णांकel8x0_pcm_खोलो(substream, &chip->ichd[ICHD_MIC2]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_mic2_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ICHD_MIC2].substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_capture2_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	वापस snd_पूर्णांकel8x0_pcm_खोलो(substream, &chip->ichd[ICHD_PCM2IN]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_capture2_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ICHD_PCM2IN].substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	पूर्णांक idx = chip->device_type == DEVICE_NFORCE ? NVD_SPBAR : ICHD_SPBAR;

	वापस snd_पूर्णांकel8x0_pcm_खोलो(substream, &chip->ichd[idx]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_spdअगर_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	पूर्णांक idx = chip->device_type == DEVICE_NFORCE ? NVD_SPBAR : ICHD_SPBAR;

	chip->ichd[idx].substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_ali_ac97spdअगरout_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक val;

	spin_lock_irq(&chip->reg_lock);
	val = igetdword(chip, ICHREG(ALI_INTERFACECR));
	val |= ICH_ALI_IF_AC97SP;
	iputdword(chip, ICHREG(ALI_INTERFACECR), val);
	/* also needs to set ALI_SC_CODEC_SPDF correctly */
	spin_unlock_irq(&chip->reg_lock);

	वापस snd_पूर्णांकel8x0_pcm_खोलो(substream, &chip->ichd[ALID_AC97SPDIFOUT]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_ali_ac97spdअगरout_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक val;

	chip->ichd[ALID_AC97SPDIFOUT].substream = शून्य;
	spin_lock_irq(&chip->reg_lock);
	val = igetdword(chip, ICHREG(ALI_INTERFACECR));
	val &= ~ICH_ALI_IF_AC97SP;
	iputdword(chip, ICHREG(ALI_INTERFACECR), val);
	spin_unlock_irq(&chip->reg_lock);

	वापस 0;
पूर्ण

#अगर 0 // NYI
अटल पूर्णांक snd_पूर्णांकel8x0_ali_spdअगरin_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	वापस snd_पूर्णांकel8x0_pcm_खोलो(substream, &chip->ichd[ALID_SPDIFIN]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_ali_spdअगरin_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ALID_SPDIFIN].substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_ali_spdअगरout_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	वापस snd_पूर्णांकel8x0_pcm_खोलो(substream, &chip->ichd[ALID_SPDIFOUT]);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_ali_spdअगरout_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel8x0 *chip = snd_pcm_substream_chip(substream);

	chip->ichd[ALID_SPDIFOUT].substream = शून्य;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_playback_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_playback_खोलो,
	.बंद =	snd_पूर्णांकel8x0_playback_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_capture_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_capture_खोलो,
	.बंद =	snd_पूर्णांकel8x0_capture_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_capture_mic_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_mic_खोलो,
	.बंद =	snd_पूर्णांकel8x0_mic_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_capture_mic2_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_mic2_खोलो,
	.बंद =	snd_पूर्णांकel8x0_mic2_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_capture2_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_capture2_खोलो,
	.बंद =	snd_पूर्णांकel8x0_capture2_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_spdअगर_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_spdअगर_खोलो,
	.बंद =	snd_पूर्णांकel8x0_spdअगर_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_ali_playback_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_playback_खोलो,
	.बंद =	snd_पूर्णांकel8x0_playback_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_ali_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_ali_capture_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_capture_खोलो,
	.बंद =	snd_पूर्णांकel8x0_capture_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_ali_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_ali_capture_mic_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_mic_खोलो,
	.बंद =	snd_पूर्णांकel8x0_mic_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_ali_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_ali_ac97spdअगरout_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_ali_ac97spdअगरout_खोलो,
	.बंद =	snd_पूर्णांकel8x0_ali_ac97spdअगरout_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_ali_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

#अगर 0 // NYI
अटल काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_ali_spdअगरin_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_ali_spdअगरin_खोलो,
	.बंद =	snd_पूर्णांकel8x0_ali_spdअगरin_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;

अटल काष्ठा snd_pcm_ops snd_पूर्णांकel8x0_ali_spdअगरout_ops = अणु
	.खोलो =		snd_पूर्णांकel8x0_ali_spdअगरout_खोलो,
	.बंद =	snd_पूर्णांकel8x0_ali_spdअगरout_बंद,
	.hw_params =	snd_पूर्णांकel8x0_hw_params,
	.hw_मुक्त =	snd_पूर्णांकel8x0_hw_मुक्त,
	.prepare =	snd_पूर्णांकel8x0_pcm_prepare,
	.trigger =	snd_पूर्णांकel8x0_pcm_trigger,
	.poपूर्णांकer =	snd_पूर्णांकel8x0_pcm_poपूर्णांकer,
पूर्ण;
#पूर्ण_अगर // NYI

काष्ठा ich_pcm_table अणु
	अक्षर *suffix;
	स्थिर काष्ठा snd_pcm_ops *playback_ops;
	स्थिर काष्ठा snd_pcm_ops *capture_ops;
	माप_प्रकार pपुनः_स्मृति_size;
	माप_प्रकार pपुनः_स्मृति_max_size;
	पूर्णांक ac97_idx;
पूर्ण;

#घोषणा पूर्णांकel8x0_dma_type(chip) \
	((chip)->fix_nocache ? SNDRV_DMA_TYPE_DEV_UC : SNDRV_DMA_TYPE_DEV)

अटल पूर्णांक snd_पूर्णांकel8x0_pcm1(काष्ठा पूर्णांकel8x0 *chip, पूर्णांक device,
			     स्थिर काष्ठा ich_pcm_table *rec)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;
	अक्षर name[32];

	अगर (rec->suffix)
		प्र_लिखो(name, "Intel ICH - %s", rec->suffix);
	अन्यथा
		म_नकल(name, "Intel ICH");
	err = snd_pcm_new(chip->card, name, device,
			  rec->playback_ops ? 1 : 0,
			  rec->capture_ops ? 1 : 0, &pcm);
	अगर (err < 0)
		वापस err;

	अगर (rec->playback_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, rec->playback_ops);
	अगर (rec->capture_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, rec->capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	अगर (rec->suffix)
		प्र_लिखो(pcm->name, "%s - %s", chip->card->लघुname, rec->suffix);
	अन्यथा
		म_नकल(pcm->name, chip->card->लघुname);
	chip->pcm[device] = pcm;

	snd_pcm_set_managed_buffer_all(pcm, पूर्णांकel8x0_dma_type(chip),
				       &chip->pci->dev,
				       rec->pपुनः_स्मृति_size, rec->pपुनः_स्मृति_max_size);

	अगर (rec->playback_ops &&
	    rec->playback_ops->खोलो == snd_पूर्णांकel8x0_playback_खोलो) अणु
		काष्ठा snd_pcm_chmap *chmap;
		पूर्णांक chs = 2;
		अगर (chip->multi8)
			chs = 8;
		अन्यथा अगर (chip->multi6)
			chs = 6;
		अन्यथा अगर (chip->multi4)
			chs = 4;
		err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					     snd_pcm_alt_chmaps, chs, 0,
					     &chmap);
		अगर (err < 0)
			वापस err;
		chmap->channel_mask = SND_PCM_CHMAP_MASK_2468;
		chip->ac97[0]->chmaps[SNDRV_PCM_STREAM_PLAYBACK] = chmap;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ich_pcm_table पूर्णांकel_pcms[] = अणु
	अणु
		.playback_ops = &snd_पूर्णांकel8x0_playback_ops,
		.capture_ops = &snd_पूर्णांकel8x0_capture_ops,
		.pपुनः_स्मृति_size = 64 * 1024,
		.pपुनः_स्मृति_max_size = 128 * 1024,
	पूर्ण,
	अणु
		.suffix = "MIC ADC",
		.capture_ops = &snd_पूर्णांकel8x0_capture_mic_ops,
		.pपुनः_स्मृति_size = 0,
		.pपुनः_स्मृति_max_size = 128 * 1024,
		.ac97_idx = ICHD_MIC,
	पूर्ण,
	अणु
		.suffix = "MIC2 ADC",
		.capture_ops = &snd_पूर्णांकel8x0_capture_mic2_ops,
		.pपुनः_स्मृति_size = 0,
		.pपुनः_स्मृति_max_size = 128 * 1024,
		.ac97_idx = ICHD_MIC2,
	पूर्ण,
	अणु
		.suffix = "ADC2",
		.capture_ops = &snd_पूर्णांकel8x0_capture2_ops,
		.pपुनः_स्मृति_size = 0,
		.pपुनः_स्मृति_max_size = 128 * 1024,
		.ac97_idx = ICHD_PCM2IN,
	पूर्ण,
	अणु
		.suffix = "IEC958",
		.playback_ops = &snd_पूर्णांकel8x0_spdअगर_ops,
		.pपुनः_स्मृति_size = 64 * 1024,
		.pपुनः_स्मृति_max_size = 128 * 1024,
		.ac97_idx = ICHD_SPBAR,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ich_pcm_table nक्रमce_pcms[] = अणु
	अणु
		.playback_ops = &snd_पूर्णांकel8x0_playback_ops,
		.capture_ops = &snd_पूर्णांकel8x0_capture_ops,
		.pपुनः_स्मृति_size = 64 * 1024,
		.pपुनः_स्मृति_max_size = 128 * 1024,
	पूर्ण,
	अणु
		.suffix = "MIC ADC",
		.capture_ops = &snd_पूर्णांकel8x0_capture_mic_ops,
		.pपुनः_स्मृति_size = 0,
		.pपुनः_स्मृति_max_size = 128 * 1024,
		.ac97_idx = NVD_MIC,
	पूर्ण,
	अणु
		.suffix = "IEC958",
		.playback_ops = &snd_पूर्णांकel8x0_spdअगर_ops,
		.pपुनः_स्मृति_size = 64 * 1024,
		.pपुनः_स्मृति_max_size = 128 * 1024,
		.ac97_idx = NVD_SPBAR,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ich_pcm_table ali_pcms[] = अणु
	अणु
		.playback_ops = &snd_पूर्णांकel8x0_ali_playback_ops,
		.capture_ops = &snd_पूर्णांकel8x0_ali_capture_ops,
		.pपुनः_स्मृति_size = 64 * 1024,
		.pपुनः_स्मृति_max_size = 128 * 1024,
	पूर्ण,
	अणु
		.suffix = "MIC ADC",
		.capture_ops = &snd_पूर्णांकel8x0_ali_capture_mic_ops,
		.pपुनः_स्मृति_size = 0,
		.pपुनः_स्मृति_max_size = 128 * 1024,
		.ac97_idx = ALID_MIC,
	पूर्ण,
	अणु
		.suffix = "IEC958",
		.playback_ops = &snd_पूर्णांकel8x0_ali_ac97spdअगरout_ops,
		/* .capture_ops = &snd_पूर्णांकel8x0_ali_spdअगरin_ops, */
		.pपुनः_स्मृति_size = 64 * 1024,
		.pपुनः_स्मृति_max_size = 128 * 1024,
		.ac97_idx = ALID_AC97SPDIFOUT,
	पूर्ण,
#अगर 0 // NYI
	अणु
		.suffix = "HW IEC958",
		.playback_ops = &snd_पूर्णांकel8x0_ali_spdअगरout_ops,
		.pपुनः_स्मृति_size = 64 * 1024,
		.pपुनः_स्मृति_max_size = 128 * 1024,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक snd_पूर्णांकel8x0_pcm(काष्ठा पूर्णांकel8x0 *chip)
अणु
	पूर्णांक i, tblsize, device, err;
	स्थिर काष्ठा ich_pcm_table *tbl, *rec;

	चयन (chip->device_type) अणु
	हाल DEVICE_INTEL_ICH4:
		tbl = पूर्णांकel_pcms;
		tblsize = ARRAY_SIZE(पूर्णांकel_pcms);
		अगर (spdअगर_aclink)
			tblsize--;
		अवरोध;
	हाल DEVICE_NFORCE:
		tbl = nक्रमce_pcms;
		tblsize = ARRAY_SIZE(nक्रमce_pcms);
		अगर (spdअगर_aclink)
			tblsize--;
		अवरोध;
	हाल DEVICE_ALI:
		tbl = ali_pcms;
		tblsize = ARRAY_SIZE(ali_pcms);
		अवरोध;
	शेष:
		tbl = पूर्णांकel_pcms;
		tblsize = 2;
		अवरोध;
	पूर्ण

	device = 0;
	क्रम (i = 0; i < tblsize; i++) अणु
		rec = tbl + i;
		अगर (i > 0 && rec->ac97_idx) अणु
			/* activate PCM only when associated AC'97 codec */
			अगर (! chip->ichd[rec->ac97_idx].pcm)
				जारी;
		पूर्ण
		err = snd_पूर्णांकel8x0_pcm1(chip, device, rec);
		अगर (err < 0)
			वापस err;
		device++;
	पूर्ण

	chip->pcm_devs = device;
	वापस 0;
पूर्ण
	

/*
 *  Mixer part
 */

अटल व्योम snd_पूर्णांकel8x0_mixer_मुक्त_ac97_bus(काष्ठा snd_ac97_bus *bus)
अणु
	काष्ठा पूर्णांकel8x0 *chip = bus->निजी_data;
	chip->ac97_bus = शून्य;
पूर्ण

अटल व्योम snd_पूर्णांकel8x0_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा पूर्णांकel8x0 *chip = ac97->निजी_data;
	chip->ac97[ac97->num] = शून्य;
पूर्ण

अटल स्थिर काष्ठा ac97_pcm ac97_pcm_defs[] = अणु
	/* front PCM */
	अणु
		.exclusive = 1,
		.r = अणु	अणु
				.slots = (1 << AC97_SLOT_PCM_LEFT) |
					 (1 << AC97_SLOT_PCM_RIGHT) |
					 (1 << AC97_SLOT_PCM_CENTER) |
					 (1 << AC97_SLOT_PCM_SLEFT) |
					 (1 << AC97_SLOT_PCM_SRIGHT) |
					 (1 << AC97_SLOT_LFE)
			पूर्ण,
			अणु
				.slots = (1 << AC97_SLOT_PCM_LEFT) |
					 (1 << AC97_SLOT_PCM_RIGHT) |
					 (1 << AC97_SLOT_PCM_LEFT_0) |
					 (1 << AC97_SLOT_PCM_RIGHT_0)
			पूर्ण
		पूर्ण
	पूर्ण,
	/* PCM IN #1 */
	अणु
		.stream = 1,
		.exclusive = 1,
		.r = अणु	अणु
				.slots = (1 << AC97_SLOT_PCM_LEFT) |
					 (1 << AC97_SLOT_PCM_RIGHT)
			पूर्ण
		पूर्ण
	पूर्ण,
	/* MIC IN #1 */
	अणु
		.stream = 1,
		.exclusive = 1,
		.r = अणु	अणु
				.slots = (1 << AC97_SLOT_MIC)
			पूर्ण
		पूर्ण
	पूर्ण,
	/* S/PDIF PCM */
	अणु
		.exclusive = 1,
		.spdअगर = 1,
		.r = अणु	अणु
				.slots = (1 << AC97_SLOT_SPDIF_LEFT2) |
					 (1 << AC97_SLOT_SPDIF_RIGHT2)
			पूर्ण
		पूर्ण
	पूर्ण,
	/* PCM IN #2 */
	अणु
		.stream = 1,
		.exclusive = 1,
		.r = अणु	अणु
				.slots = (1 << AC97_SLOT_PCM_LEFT) |
					 (1 << AC97_SLOT_PCM_RIGHT)
			पूर्ण
		पूर्ण
	पूर्ण,
	/* MIC IN #2 */
	अणु
		.stream = 1,
		.exclusive = 1,
		.r = अणु	अणु
				.slots = (1 << AC97_SLOT_MIC)
			पूर्ण
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ac97_quirk ac97_quirks[] = अणु
        अणु
		.subvenकरोr = 0x0e11,
		.subdevice = 0x000e,
		.name = "Compaq Deskpro EN",	/* AD1885 */
		.type = AC97_TUNE_HP_ONLY
        पूर्ण,
	अणु
		.subvenकरोr = 0x0e11,
		.subdevice = 0x008a,
		.name = "Compaq Evo W4000",	/* AD1885 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x0e11,
		.subdevice = 0x00b8,
		.name = "Compaq Evo D510C",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
        अणु
		.subvenकरोr = 0x0e11,
		.subdevice = 0x0860,
		.name = "HP/Compaq nx7010",
		.type = AC97_TUNE_MUTE_LED
        पूर्ण,
	अणु
		.subvenकरोr = 0x1014,
		.subdevice = 0x0534,
		.name = "ThinkPad X31",
		.type = AC97_TUNE_INV_EAPD
	पूर्ण,
	अणु
		.subvenकरोr = 0x1014,
		.subdevice = 0x1f00,
		.name = "MS-9128",
		.type = AC97_TUNE_ALC_JACK
	पूर्ण,
	अणु
		.subvenकरोr = 0x1014,
		.subdevice = 0x0267,
		.name = "IBM NetVista A30p",	/* AD1981B */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1025,
		.subdevice = 0x0082,
		.name = "Acer Travelmate 2310",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1025,
		.subdevice = 0x0083,
		.name = "Acer Aspire 3003LCi",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x00d8,
		.name = "Dell Precision 530",	/* AD1885 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x010d,
		.name = "Dell",	/* which model?  AD1885 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x0126,
		.name = "Dell Optiplex GX260",	/* AD1981A */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x012c,
		.name = "Dell Precision 650",	/* AD1981A */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x012d,
		.name = "Dell Precision 450",	/* AD1981B*/
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x0147,
		.name = "Dell",	/* which model?  AD1981B*/
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x0151,
		.name = "Dell Optiplex GX270",  /* AD1981B */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x014e,
		.name = "Dell D800", /* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x0163,
		.name = "Dell Unknown",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x016a,
		.name = "Dell Inspiron 8600",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x0182,
		.name = "Dell Latitude D610",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x0186,
		.name = "Dell Latitude D810", /* cf. Malone #41015 */
		.type = AC97_TUNE_HP_MUTE_LED
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x0188,
		.name = "Dell Inspiron 6000",
		.type = AC97_TUNE_HP_MUTE_LED /* cf. Malone #41015 */
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x0189,
		.name = "Dell Inspiron 9300",
		.type = AC97_TUNE_HP_MUTE_LED
	पूर्ण,
	अणु
		.subvenकरोr = 0x1028,
		.subdevice = 0x0191,
		.name = "Dell Inspiron 8600",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x006d,
		.name = "HP zv5000",
		.type = AC97_TUNE_MUTE_LED	/*AD1981B*/
	पूर्ण,
	अणु	/* FIXME: which codec? */
		.subvenकरोr = 0x103c,
		.subdevice = 0x00c3,
		.name = "HP xw6000",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x088c,
		.name = "HP nc8000",
		.type = AC97_TUNE_HP_MUTE_LED
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x0890,
		.name = "HP nc6000",
		.type = AC97_TUNE_MUTE_LED
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x129d,
		.name = "HP xw8000",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x0938,
		.name = "HP nc4200",
		.type = AC97_TUNE_HP_MUTE_LED
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x099c,
		.name = "HP nx6110/nc6120",
		.type = AC97_TUNE_HP_MUTE_LED
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x0944,
		.name = "HP nc6220",
		.type = AC97_TUNE_HP_MUTE_LED
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x0934,
		.name = "HP nc8220",
		.type = AC97_TUNE_HP_MUTE_LED
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x12f1,
		.name = "HP xw8200",	/* AD1981B*/
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x12f2,
		.name = "HP xw6200",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x103c,
		.subdevice = 0x3008,
		.name = "HP xw4200",	/* AD1981B*/
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x104d,
		.subdevice = 0x8144,
		.name = "Sony",
		.type = AC97_TUNE_INV_EAPD
	पूर्ण,
	अणु
		.subvenकरोr = 0x104d,
		.subdevice = 0x8197,
		.name = "Sony S1XP",
		.type = AC97_TUNE_INV_EAPD
	पूर्ण,
	अणु
		.subvenकरोr = 0x104d,
		.subdevice = 0x81c0,
		.name = "Sony VAIO VGN-T350P", /*AD1981B*/
		.type = AC97_TUNE_INV_EAPD
	पूर्ण,
	अणु
		.subvenकरोr = 0x104d,
		.subdevice = 0x81c5,
		.name = "Sony VAIO VGN-B1VP", /*AD1981B*/
		.type = AC97_TUNE_INV_EAPD
	पूर्ण,
 	अणु
		.subvenकरोr = 0x1043,
		.subdevice = 0x80f3,
		.name = "ASUS ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	पूर्ण,
	अणु
		.subvenकरोr = 0x10cf,
		.subdevice = 0x11c3,
		.name = "Fujitsu-Siemens E4010",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x10cf,
		.subdevice = 0x1225,
		.name = "Fujitsu-Siemens T3010",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x10cf,
		.subdevice = 0x1253,
		.name = "Fujitsu S6210",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x10cf,
		.subdevice = 0x127d,
		.name = "Fujitsu Lifebook P7010",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x10cf,
		.subdevice = 0x127e,
		.name = "Fujitsu Lifebook C1211D",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x10cf,
		.subdevice = 0x12ec,
		.name = "Fujitsu-Siemens 4010",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x10cf,
		.subdevice = 0x12f2,
		.name = "Fujitsu-Siemens Celsius H320",
		.type = AC97_TUNE_SWAP_HP
	पूर्ण,
	अणु
		.subvenकरोr = 0x10f1,
		.subdevice = 0x2665,
		.name = "Fujitsu-Siemens Celsius",	/* AD1981? */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x10f1,
		.subdevice = 0x2885,
		.name = "AMD64 Mobo",	/* ALC650 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x10f1,
		.subdevice = 0x2895,
		.name = "Tyan Thunder K8WE",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x10f7,
		.subdevice = 0x834c,
		.name = "Panasonic CF-R4",
		.type = AC97_TUNE_HP_ONLY,
	पूर्ण,
	अणु
		.subvenकरोr = 0x110a,
		.subdevice = 0x0056,
		.name = "Fujitsu-Siemens Scenic",	/* AD1981? */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x11d4,
		.subdevice = 0x5375,
		.name = "ADI AD1985 (discrete)",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1462,
		.subdevice = 0x5470,
		.name = "MSI P4 ATX 645 Ultra",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x161f,
		.subdevice = 0x202f,
		.name = "Gateway M520",
		.type = AC97_TUNE_INV_EAPD
	पूर्ण,
	अणु
		.subvenकरोr = 0x161f,
		.subdevice = 0x203a,
		.name = "Gateway 4525GZ",		/* AD1981B */
		.type = AC97_TUNE_INV_EAPD
	पूर्ण,
	अणु
		.subvenकरोr = 0x1734,
		.subdevice = 0x0088,
		.name = "Fujitsu-Siemens D1522",	/* AD1981 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x8086,
		.subdevice = 0x2000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	पूर्ण,
	अणु
		.subvenकरोr = 0x8086,
		.subdevice = 0x4000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	पूर्ण,
	अणु
		.subvenकरोr = 0x8086,
		.subdevice = 0x4856,
		.name = "Intel D845WN (82801BA)",
		.type = AC97_TUNE_SWAP_HP
	पूर्ण,
	अणु
		.subvenकरोr = 0x8086,
		.subdevice = 0x4d44,
		.name = "Intel D850EMV2",	/* AD1885 */
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x8086,
		.subdevice = 0x4d56,
		.name = "Intel ICH/AD1885",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x8086,
		.subdevice = 0x6000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	पूर्ण,
	अणु
		.subvenकरोr = 0x8086,
		.subdevice = 0xe000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	पूर्ण,
#अगर 0 /* FIXME: this seems wrong on most boards */
	अणु
		.subvenकरोr = 0x8086,
		.subdevice = 0xa000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण /* terminator */
पूर्ण;

अटल पूर्णांक snd_पूर्णांकel8x0_mixer(काष्ठा पूर्णांकel8x0 *chip, पूर्णांक ac97_घड़ी,
			      स्थिर अक्षर *quirk_override)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अचिन्हित पूर्णांक i, codecs;
	अचिन्हित पूर्णांक glob_sta = 0;
	स्थिर काष्ठा snd_ac97_bus_ops *ops;
	अटल स्थिर काष्ठा snd_ac97_bus_ops standard_bus_ops = अणु
		.ग_लिखो = snd_पूर्णांकel8x0_codec_ग_लिखो,
		.पढ़ो = snd_पूर्णांकel8x0_codec_पढ़ो,
	पूर्ण;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ali_bus_ops = अणु
		.ग_लिखो = snd_पूर्णांकel8x0_ali_codec_ग_लिखो,
		.पढ़ो = snd_पूर्णांकel8x0_ali_codec_पढ़ो,
	पूर्ण;

	chip->spdअगर_idx = -1; /* use PCMOUT (or disabled) */
	अगर (!spdअगर_aclink) अणु
		चयन (chip->device_type) अणु
		हाल DEVICE_NFORCE:
			chip->spdअगर_idx = NVD_SPBAR;
			अवरोध;
		हाल DEVICE_ALI:
			chip->spdअगर_idx = ALID_AC97SPDIFOUT;
			अवरोध;
		हाल DEVICE_INTEL_ICH4:
			chip->spdअगर_idx = ICHD_SPBAR;
			अवरोध;
		पूर्ण
	पूर्ण

	chip->in_ac97_init = 1;
	
	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.निजी_मुक्त = snd_पूर्णांकel8x0_mixer_मुक्त_ac97;
	ac97.scaps = AC97_SCAP_SKIP_MODEM | AC97_SCAP_POWER_SAVE;
	अगर (chip->xbox)
		ac97.scaps |= AC97_SCAP_DETECT_BY_VENDOR;
	अगर (chip->device_type != DEVICE_ALI) अणु
		glob_sta = igetdword(chip, ICHREG(GLOB_STA));
		ops = &standard_bus_ops;
		chip->in_sdin_init = 1;
		codecs = 0;
		क्रम (i = 0; i < chip->max_codecs; i++) अणु
			अगर (! (glob_sta & chip->codec_bit[i]))
				जारी;
			अगर (chip->device_type == DEVICE_INTEL_ICH4) अणु
				snd_पूर्णांकel8x0_codec_पढ़ो_test(chip, codecs);
				chip->ac97_sdin[codecs] =
					igetbyte(chip, ICHREG(SDM)) & ICH_LDI_MASK;
				अगर (snd_BUG_ON(chip->ac97_sdin[codecs] >= 3))
					chip->ac97_sdin[codecs] = 0;
			पूर्ण अन्यथा
				chip->ac97_sdin[codecs] = i;
			codecs++;
		पूर्ण
		chip->in_sdin_init = 0;
		अगर (! codecs)
			codecs = 1;
	पूर्ण अन्यथा अणु
		ops = &ali_bus_ops;
		codecs = 1;
		/* detect the secondary codec */
		क्रम (i = 0; i < 100; i++) अणु
			अचिन्हित पूर्णांक reg = igetdword(chip, ICHREG(ALI_RTSR));
			अगर (reg & 0x40) अणु
				codecs = 2;
				अवरोध;
			पूर्ण
			iputdword(chip, ICHREG(ALI_RTSR), reg | 0x40);
			udelay(1);
		पूर्ण
	पूर्ण
	अगर ((err = snd_ac97_bus(chip->card, 0, ops, chip, &pbus)) < 0)
		जाओ __err;
	pbus->निजी_मुक्त = snd_पूर्णांकel8x0_mixer_मुक्त_ac97_bus;
	अगर (ac97_घड़ी >= 8000 && ac97_घड़ी <= 48000)
		pbus->घड़ी = ac97_घड़ी;
	/* FIXME: my test board करोesn't work well with VRA... */
	अगर (chip->device_type == DEVICE_ALI)
		pbus->no_vra = 1;
	अन्यथा
		pbus->dra = 1;
	chip->ac97_bus = pbus;
	chip->ncodecs = codecs;

	ac97.pci = chip->pci;
	क्रम (i = 0; i < codecs; i++) अणु
		ac97.num = i;
		अगर ((err = snd_ac97_mixer(pbus, &ac97, &chip->ac97[i])) < 0) अणु
			अगर (err != -EACCES)
				dev_err(chip->card->dev,
					"Unable to initialize codec #%d\n", i);
			अगर (i == 0)
				जाओ __err;
		पूर्ण
	पूर्ण
	/* tune up the primary codec */
	snd_ac97_tune_hardware(chip->ac97[0], ac97_quirks, quirk_override);
	/* enable separate SDINs क्रम ICH4 */
	अगर (chip->device_type == DEVICE_INTEL_ICH4)
		pbus->isdin = 1;
	/* find the available PCM streams */
	i = ARRAY_SIZE(ac97_pcm_defs);
	अगर (chip->device_type != DEVICE_INTEL_ICH4)
		i -= 2;		/* करो not allocate PCM2IN and MIC2 */
	अगर (chip->spdअगर_idx < 0)
		i--;		/* करो not allocate S/PDIF */
	err = snd_ac97_pcm_assign(pbus, i, ac97_pcm_defs);
	अगर (err < 0)
		जाओ __err;
	chip->ichd[ICHD_PCMOUT].pcm = &pbus->pcms[0];
	chip->ichd[ICHD_PCMIN].pcm = &pbus->pcms[1];
	chip->ichd[ICHD_MIC].pcm = &pbus->pcms[2];
	अगर (chip->spdअगर_idx >= 0)
		chip->ichd[chip->spdअगर_idx].pcm = &pbus->pcms[3];
	अगर (chip->device_type == DEVICE_INTEL_ICH4) अणु
		chip->ichd[ICHD_PCM2IN].pcm = &pbus->pcms[4];
		chip->ichd[ICHD_MIC2].pcm = &pbus->pcms[5];
	पूर्ण
	/* enable separate SDINs क्रम ICH4 */
	अगर (chip->device_type == DEVICE_INTEL_ICH4) अणु
		काष्ठा ac97_pcm *pcm = chip->ichd[ICHD_PCM2IN].pcm;
		u8 पंचांगp = igetbyte(chip, ICHREG(SDM));
		पंचांगp &= ~(ICH_DI2L_MASK|ICH_DI1L_MASK);
		अगर (pcm) अणु
			पंचांगp |= ICH_SE;	/* steer enable क्रम multiple SDINs */
			पंचांगp |= chip->ac97_sdin[0] << ICH_DI1L_SHIFT;
			क्रम (i = 1; i < 4; i++) अणु
				अगर (pcm->r[0].codec[i]) अणु
					पंचांगp |= chip->ac97_sdin[pcm->r[0].codec[1]->num] << ICH_DI2L_SHIFT;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			पंचांगp &= ~ICH_SE; /* steer disable */
		पूर्ण
		iputbyte(chip, ICHREG(SDM), पंचांगp);
	पूर्ण
	अगर (pbus->pcms[0].r[0].slots & (1 << AC97_SLOT_PCM_SLEFT)) अणु
		chip->multi4 = 1;
		अगर (pbus->pcms[0].r[0].slots & (1 << AC97_SLOT_LFE)) अणु
			chip->multi6 = 1;
			अगर (chip->ac97[0]->flags & AC97_HAS_8CH)
				chip->multi8 = 1;
		पूर्ण
	पूर्ण
	अगर (pbus->pcms[0].r[1].rslots[0]) अणु
		chip->dra = 1;
	पूर्ण
	अगर (chip->device_type == DEVICE_INTEL_ICH4) अणु
		अगर ((igetdword(chip, ICHREG(GLOB_STA)) & ICH_SAMPLE_CAP) == ICH_SAMPLE_16_20)
			chip->smp20bit = 1;
	पूर्ण
	अगर (chip->device_type == DEVICE_NFORCE && !spdअगर_aclink) अणु
		/* 48kHz only */
		chip->ichd[chip->spdअगर_idx].pcm->rates = SNDRV_PCM_RATE_48000;
	पूर्ण
	अगर (chip->device_type == DEVICE_INTEL_ICH4 && !spdअगर_aclink) अणु
		/* use slot 10/11 क्रम SPDIF */
		u32 val;
		val = igetdword(chip, ICHREG(GLOB_CNT)) & ~ICH_PCM_SPDIF_MASK;
		val |= ICH_PCM_SPDIF_1011;
		iputdword(chip, ICHREG(GLOB_CNT), val);
		snd_ac97_update_bits(chip->ac97[0], AC97_EXTENDED_STATUS, 0x03 << 4, 0x03 << 4);
	पूर्ण
	chip->in_ac97_init = 0;
	वापस 0;

 __err:
	/* clear the cold-reset bit क्रम the next chance */
	अगर (chip->device_type != DEVICE_ALI)
		iputdword(chip, ICHREG(GLOB_CNT),
			  igetdword(chip, ICHREG(GLOB_CNT)) & ~ICH_AC97COLD);
	वापस err;
पूर्ण


/*
 *
 */

अटल व्योम करो_ali_reset(काष्ठा पूर्णांकel8x0 *chip)
अणु
	iputdword(chip, ICHREG(ALI_SCR), ICH_ALI_SC_RESET);
	iputdword(chip, ICHREG(ALI_FIFOCR1), 0x83838383);
	iputdword(chip, ICHREG(ALI_FIFOCR2), 0x83838383);
	iputdword(chip, ICHREG(ALI_FIFOCR3), 0x83838383);
	iputdword(chip, ICHREG(ALI_INTERFACECR),
		  ICH_ALI_IF_PI|ICH_ALI_IF_PO);
	iputdword(chip, ICHREG(ALI_INTERRUPTCR), 0x00000000);
	iputdword(chip, ICHREG(ALI_INTERRUPTSR), 0x00000000);
पूर्ण

#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
अटल स्थिर काष्ठा snd_pci_quirk ich_chip_reset_mode[] = अणु
	SND_PCI_QUIRK(0x1014, 0x051f, "Thinkpad R32", 1),
	अणु पूर्ण /* end */
पूर्ण;

अटल पूर्णांक snd_पूर्णांकel8x0_ich_chip_cold_reset(काष्ठा पूर्णांकel8x0 *chip)
अणु
	अचिन्हित पूर्णांक cnt;
	/* ACLink on, 2 channels */

	अगर (snd_pci_quirk_lookup(chip->pci, ich_chip_reset_mode))
		वापस -EIO;

	cnt = igetdword(chip, ICHREG(GLOB_CNT));
	cnt &= ~(ICH_ACLINK | ICH_PCM_246_MASK);

	/* करो cold reset - the full ac97 घातerकरोwn may leave the controller
	 * in a warm state but actually it cannot communicate with the codec.
	 */
	iputdword(chip, ICHREG(GLOB_CNT), cnt & ~ICH_AC97COLD);
	cnt = igetdword(chip, ICHREG(GLOB_CNT));
	udelay(10);
	iputdword(chip, ICHREG(GLOB_CNT), cnt | ICH_AC97COLD);
	msleep(1);
	वापस 0;
पूर्ण
#घोषणा snd_पूर्णांकel8x0_ich_chip_can_cold_reset(chip) \
	(!snd_pci_quirk_lookup(chip->pci, ich_chip_reset_mode))
#अन्यथा
#घोषणा snd_पूर्णांकel8x0_ich_chip_cold_reset(chip)	0
#घोषणा snd_पूर्णांकel8x0_ich_chip_can_cold_reset(chip) (0)
#पूर्ण_अगर

अटल पूर्णांक snd_पूर्णांकel8x0_ich_chip_reset(काष्ठा पूर्णांकel8x0 *chip)
अणु
	अचिन्हित दीर्घ end_समय;
	अचिन्हित पूर्णांक cnt;
	/* ACLink on, 2 channels */
	cnt = igetdword(chip, ICHREG(GLOB_CNT));
	cnt &= ~(ICH_ACLINK | ICH_PCM_246_MASK);
	/* finish cold or करो warm reset */
	cnt |= (cnt & ICH_AC97COLD) == 0 ? ICH_AC97COLD : ICH_AC97WARM;
	iputdword(chip, ICHREG(GLOB_CNT), cnt);
	end_समय = (jअगरfies + (HZ / 4)) + 1;
	करो अणु
		अगर ((igetdword(chip, ICHREG(GLOB_CNT)) & ICH_AC97WARM) == 0)
			वापस 0;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	dev_err(chip->card->dev, "AC'97 warm reset still in progress? [0x%x]\n",
		   igetdword(chip, ICHREG(GLOB_CNT)));
	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_ich_chip_init(काष्ठा पूर्णांकel8x0 *chip, पूर्णांक probing)
अणु
	अचिन्हित दीर्घ end_समय;
	अचिन्हित पूर्णांक status, nstatus;
	अचिन्हित पूर्णांक cnt;
	पूर्णांक err;

	/* put logic to right state */
	/* first clear status bits */
	status = ICH_RCS | ICH_MCINT | ICH_POINT | ICH_PIINT;
	अगर (chip->device_type == DEVICE_NFORCE)
		status |= ICH_NVSPINT;
	cnt = igetdword(chip, ICHREG(GLOB_STA));
	iputdword(chip, ICHREG(GLOB_STA), cnt & status);

	अगर (snd_पूर्णांकel8x0_ich_chip_can_cold_reset(chip))
		err = snd_पूर्णांकel8x0_ich_chip_cold_reset(chip);
	अन्यथा
		err = snd_पूर्णांकel8x0_ich_chip_reset(chip);
	अगर (err < 0)
		वापस err;

	अगर (probing) अणु
		/* रुको क्रम any codec पढ़ोy status.
		 * Once it becomes पढ़ोy it should reमुख्य पढ़ोy
		 * as दीर्घ as we करो not disable the ac97 link.
		 */
		end_समय = jअगरfies + HZ;
		करो अणु
			status = igetdword(chip, ICHREG(GLOB_STA)) &
				chip->codec_isr_bits;
			अगर (status)
				अवरोध;
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
		अगर (! status) अणु
			/* no codec is found */
			dev_err(chip->card->dev,
				"codec_ready: codec is not ready [0x%x]\n",
				   igetdword(chip, ICHREG(GLOB_STA)));
			वापस -EIO;
		पूर्ण

		/* रुको क्रम other codecs पढ़ोy status. */
		end_समय = jअगरfies + HZ / 4;
		जबतक (status != chip->codec_isr_bits &&
		       समय_after_eq(end_समय, jअगरfies)) अणु
			schedule_समयout_unपूर्णांकerruptible(1);
			status |= igetdword(chip, ICHREG(GLOB_STA)) &
				chip->codec_isr_bits;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* resume phase */
		पूर्णांक i;
		status = 0;
		क्रम (i = 0; i < chip->ncodecs; i++)
			अगर (chip->ac97[i])
				status |= chip->codec_bit[chip->ac97_sdin[i]];
		/* रुको until all the probed codecs are पढ़ोy */
		end_समय = jअगरfies + HZ;
		करो अणु
			nstatus = igetdword(chip, ICHREG(GLOB_STA)) &
				chip->codec_isr_bits;
			अगर (status == nstatus)
				अवरोध;
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	पूर्ण

	अगर (chip->device_type == DEVICE_SIS) अणु
		/* unmute the output on SIS7012 */
		iputword(chip, 0x4c, igetword(chip, 0x4c) | 1);
	पूर्ण
	अगर (chip->device_type == DEVICE_NFORCE && !spdअगर_aclink) अणु
		/* enable SPDIF पूर्णांकerrupt */
		अचिन्हित पूर्णांक val;
		pci_पढ़ो_config_dword(chip->pci, 0x4c, &val);
		val |= 0x1000000;
		pci_ग_लिखो_config_dword(chip->pci, 0x4c, val);
	पूर्ण
      	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_ali_chip_init(काष्ठा पूर्णांकel8x0 *chip, पूर्णांक probing)
अणु
	u32 reg;
	पूर्णांक i = 0;

	reg = igetdword(chip, ICHREG(ALI_SCR));
	अगर ((reg & 2) == 0)	/* Cold required */
		reg |= 2;
	अन्यथा
		reg |= 1;	/* Warm */
	reg &= ~0x80000000;	/* ACLink on */
	iputdword(chip, ICHREG(ALI_SCR), reg);

	क्रम (i = 0; i < HZ / 2; i++) अणु
		अगर (! (igetdword(chip, ICHREG(ALI_INTERRUPTSR)) & ALI_INT_GPIO))
			जाओ __ok;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	dev_err(chip->card->dev, "AC'97 reset failed.\n");
	अगर (probing)
		वापस -EIO;

 __ok:
	क्रम (i = 0; i < HZ / 2; i++) अणु
		reg = igetdword(chip, ICHREG(ALI_RTSR));
		अगर (reg & 0x80) /* primary codec */
			अवरोध;
		iputdword(chip, ICHREG(ALI_RTSR), reg | 0x80);
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	करो_ali_reset(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_chip_init(काष्ठा पूर्णांकel8x0 *chip, पूर्णांक probing)
अणु
	अचिन्हित पूर्णांक i, समयout;
	पूर्णांक err;
	
	अगर (chip->device_type != DEVICE_ALI) अणु
		अगर ((err = snd_पूर्णांकel8x0_ich_chip_init(chip, probing)) < 0)
			वापस err;
		iagetword(chip, 0);	/* clear semaphore flag */
	पूर्ण अन्यथा अणु
		अगर ((err = snd_पूर्णांकel8x0_ali_chip_init(chip, probing)) < 0)
			वापस err;
	पूर्ण

	/* disable पूर्णांकerrupts */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, 0x00);
	/* reset channels */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, ICH_RESETREGS);
	क्रम (i = 0; i < chip->bdbars_count; i++) अणु
	        समयout = 100000;
	        जबतक (--समयout != 0) अणु
        		अगर ((igetbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset) & ICH_RESETREGS) == 0)
        		        अवरोध;
                पूर्ण
                अगर (समयout == 0)
			dev_err(chip->card->dev, "reset of registers failed?\n");
        पूर्ण
	/* initialize Buffer Descriptor Lists */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputdword(chip, ICH_REG_OFF_BDBAR + chip->ichd[i].reg_offset,
			  chip->ichd[i].bdbar_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_मुक्त(काष्ठा पूर्णांकel8x0 *chip)
अणु
	अचिन्हित पूर्णांक i;

	अगर (chip->irq < 0)
		जाओ __hw_end;
	/* disable पूर्णांकerrupts */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, 0x00);
	/* reset channels */
	क्रम (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, ICH_RESETREGS);
	अगर (chip->device_type == DEVICE_NFORCE && !spdअगर_aclink) अणु
		/* stop the spdअगर पूर्णांकerrupt */
		अचिन्हित पूर्णांक val;
		pci_पढ़ो_config_dword(chip->pci, 0x4c, &val);
		val &= ~0x1000000;
		pci_ग_लिखो_config_dword(chip->pci, 0x4c, val);
	पूर्ण
	/* --- */

      __hw_end:
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	अगर (chip->bdbars.area)
		snd_dma_मुक्त_pages(&chip->bdbars);
	अगर (chip->addr)
		pci_iounmap(chip->pci, chip->addr);
	अगर (chip->bmaddr)
		pci_iounmap(chip->pci, chip->bmaddr);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * घातer management
 */
अटल पूर्णांक पूर्णांकel8x0_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel8x0 *chip = card->निजी_data;
	पूर्णांक i;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	क्रम (i = 0; i < chip->ncodecs; i++)
		snd_ac97_suspend(chip->ac97[i]);
	अगर (chip->device_type == DEVICE_INTEL_ICH4)
		chip->sdm_saved = igetbyte(chip, ICHREG(SDM));

	अगर (chip->irq >= 0) अणु
		मुक्त_irq(chip->irq, chip);
		chip->irq = -1;
		card->sync_irq = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel8x0_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel8x0 *chip = card->निजी_data;
	पूर्णांक i;

	snd_पूर्णांकel8x0_chip_init(chip, 0);
	अगर (request_irq(pci->irq, snd_पूर्णांकel8x0_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
		dev_err(dev, "unable to grab IRQ %d, disabling device\n",
			pci->irq);
		snd_card_disconnect(card);
		वापस -EIO;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	/* re-initialize mixer stuff */
	अगर (chip->device_type == DEVICE_INTEL_ICH4 && !spdअगर_aclink) अणु
		/* enable separate SDINs क्रम ICH4 */
		iputbyte(chip, ICHREG(SDM), chip->sdm_saved);
		/* use slot 10/11 क्रम SPDIF */
		iputdword(chip, ICHREG(GLOB_CNT),
			  (igetdword(chip, ICHREG(GLOB_CNT)) & ~ICH_PCM_SPDIF_MASK) |
			  ICH_PCM_SPDIF_1011);
	पूर्ण

	क्रम (i = 0; i < chip->ncodecs; i++)
		snd_ac97_resume(chip->ac97[i]);

	/* resume status */
	क्रम (i = 0; i < chip->bdbars_count; i++) अणु
		काष्ठा ichdev *ichdev = &chip->ichd[i];
		अचिन्हित दीर्घ port = ichdev->reg_offset;
		अगर (! ichdev->substream || ! ichdev->suspended)
			जारी;
		अगर (ichdev->ichd == ICHD_PCMOUT)
			snd_पूर्णांकel8x0_setup_pcm_out(chip, ichdev->substream->runसमय);
		iputdword(chip, port + ICH_REG_OFF_BDBAR, ichdev->bdbar_addr);
		iputbyte(chip, port + ICH_REG_OFF_LVI, ichdev->lvi);
		iputbyte(chip, port + ICH_REG_OFF_CIV, ichdev->civ);
		iputbyte(chip, port + ichdev->roff_sr, ICH_FIFOE | ICH_BCIS | ICH_LVBCI);
	पूर्ण

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(पूर्णांकel8x0_pm, पूर्णांकel8x0_suspend, पूर्णांकel8x0_resume);
#घोषणा INTEL8X0_PM_OPS	&पूर्णांकel8x0_pm
#अन्यथा
#घोषणा INTEL8X0_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#घोषणा INTEL8X0_TESTBUF_SIZE	32768	/* enough large क्रम one shot */

अटल व्योम पूर्णांकel8x0_measure_ac97_घड़ी(काष्ठा पूर्णांकel8x0 *chip)
अणु
	काष्ठा snd_pcm_substream *subs;
	काष्ठा ichdev *ichdev;
	अचिन्हित दीर्घ port;
	अचिन्हित दीर्घ pos, pos1, t;
	पूर्णांक civ, समयout = 1000, attempt = 1;
	kसमय_प्रकार start_समय, stop_समय;

	अगर (chip->ac97_bus->घड़ी != 48000)
		वापस; /* specअगरied in module option */

      __again:
	subs = chip->pcm[0]->streams[0].substream;
	अगर (! subs || subs->dma_buffer.bytes < INTEL8X0_TESTBUF_SIZE) अणु
		dev_warn(chip->card->dev,
			 "no playback buffer allocated - aborting measure ac97 clock\n");
		वापस;
	पूर्ण
	ichdev = &chip->ichd[ICHD_PCMOUT];
	ichdev->physbuf = subs->dma_buffer.addr;
	ichdev->size = ichdev->fragsize = INTEL8X0_TESTBUF_SIZE;
	ichdev->substream = शून्य; /* करोn't process पूर्णांकerrupts */

	/* set rate */
	अगर (snd_ac97_set_rate(chip->ac97[0], AC97_PCM_FRONT_DAC_RATE, 48000) < 0) अणु
		dev_err(chip->card->dev, "cannot set ac97 rate: clock = %d\n",
			chip->ac97_bus->घड़ी);
		वापस;
	पूर्ण
	snd_पूर्णांकel8x0_setup_periods(chip, ichdev);
	port = ichdev->reg_offset;
	spin_lock_irq(&chip->reg_lock);
	chip->in_measurement = 1;
	/* trigger */
	अगर (chip->device_type != DEVICE_ALI)
		iputbyte(chip, port + ICH_REG_OFF_CR, ICH_IOCE | ICH_STARTBM);
	अन्यथा अणु
		iputbyte(chip, port + ICH_REG_OFF_CR, ICH_IOCE);
		iputdword(chip, ICHREG(ALI_DMACR), 1 << ichdev->ali_slot);
	पूर्ण
	start_समय = kसमय_get();
	spin_unlock_irq(&chip->reg_lock);
	msleep(50);
	spin_lock_irq(&chip->reg_lock);
	/* check the position */
	करो अणु
		civ = igetbyte(chip, ichdev->reg_offset + ICH_REG_OFF_CIV);
		pos1 = igetword(chip, ichdev->reg_offset + ichdev->roff_picb);
		अगर (pos1 == 0) अणु
			udelay(10);
			जारी;
		पूर्ण
		अगर (civ == igetbyte(chip, ichdev->reg_offset + ICH_REG_OFF_CIV) &&
		    pos1 == igetword(chip, ichdev->reg_offset + ichdev->roff_picb))
			अवरोध;
	पूर्ण जबतक (समयout--);
	अगर (pos1 == 0) अणु	/* oops, this value is not reliable */
		pos = 0;
	पूर्ण अन्यथा अणु
		pos = ichdev->fragsize1;
		pos -= pos1 << ichdev->pos_shअगरt;
		pos += ichdev->position;
	पूर्ण
	chip->in_measurement = 0;
	stop_समय = kसमय_get();
	/* stop */
	अगर (chip->device_type == DEVICE_ALI) अणु
		iputdword(chip, ICHREG(ALI_DMACR), 1 << (ichdev->ali_slot + 16));
		iputbyte(chip, port + ICH_REG_OFF_CR, 0);
		जबतक (igetbyte(chip, port + ICH_REG_OFF_CR))
			;
	पूर्ण अन्यथा अणु
		iputbyte(chip, port + ICH_REG_OFF_CR, 0);
		जबतक (!(igetbyte(chip, port + ichdev->roff_sr) & ICH_DCH))
			;
	पूर्ण
	iputbyte(chip, port + ICH_REG_OFF_CR, ICH_RESETREGS);
	spin_unlock_irq(&chip->reg_lock);

	अगर (pos == 0) अणु
		dev_err(chip->card->dev,
			"measure - unreliable DMA position..\n");
	      __retry:
		अगर (attempt < 3) अणु
			msleep(300);
			attempt++;
			जाओ __again;
		पूर्ण
		जाओ __end;
	पूर्ण

	pos /= 4;
	t = kसमय_us_delta(stop_समय, start_समय);
	dev_info(chip->card->dev,
		 "%s: measured %lu usecs (%lu samples)\n", __func__, t, pos);
	अगर (t == 0) अणु
		dev_err(chip->card->dev, "?? calculation error..\n");
		जाओ __retry;
	पूर्ण
	pos *= 1000;
	pos = (pos / t) * 1000 + ((pos % t) * 1000) / t;
	अगर (pos < 40000 || pos >= 60000) अणु
		/* abnormal value. hw problem? */
		dev_info(chip->card->dev, "measured clock %ld rejected\n", pos);
		जाओ __retry;
	पूर्ण अन्यथा अगर (pos > 40500 && pos < 41500)
		/* first exception - 41000Hz reference घड़ी */
		chip->ac97_bus->घड़ी = 41000;
	अन्यथा अगर (pos > 43600 && pos < 44600)
		/* second exception - 44100HZ reference घड़ी */
		chip->ac97_bus->घड़ी = 44100;
	अन्यथा अगर (pos < 47500 || pos > 48500)
		/* not 48000Hz, tuning the घड़ी.. */
		chip->ac97_bus->घड़ी = (chip->ac97_bus->घड़ी * 48000) / pos;
      __end:
	dev_info(chip->card->dev, "clocking to %d\n", chip->ac97_bus->घड़ी);
	snd_ac97_update_घातer(chip->ac97[0], AC97_PCM_FRONT_DAC_RATE, 0);
पूर्ण

अटल स्थिर काष्ठा snd_pci_quirk पूर्णांकel8x0_घड़ी_list[] = अणु
	SND_PCI_QUIRK(0x0e11, 0x008a, "AD1885", 41000),
	SND_PCI_QUIRK(0x1014, 0x0581, "AD1981B", 48000),
	SND_PCI_QUIRK(0x1028, 0x00be, "AD1885", 44100),
	SND_PCI_QUIRK(0x1028, 0x0177, "AD1980", 48000),
	SND_PCI_QUIRK(0x1028, 0x01ad, "AD1981B", 48000),
	SND_PCI_QUIRK(0x1043, 0x80f3, "AD1985", 48000),
	अणु पूर्ण	/* terminator */
पूर्ण;

अटल पूर्णांक पूर्णांकel8x0_in_घड़ी_list(काष्ठा पूर्णांकel8x0 *chip)
अणु
	काष्ठा pci_dev *pci = chip->pci;
	स्थिर काष्ठा snd_pci_quirk *wl;

	wl = snd_pci_quirk_lookup(pci, पूर्णांकel8x0_घड़ी_list);
	अगर (!wl)
		वापस 0;
	dev_info(chip->card->dev, "allow list rate for %04x:%04x is %i\n",
	       pci->subप्रणाली_venकरोr, pci->subप्रणाली_device, wl->value);
	chip->ac97_bus->घड़ी = wl->value;
	वापस 1;
पूर्ण

अटल व्योम snd_पूर्णांकel8x0_proc_पढ़ो(काष्ठा snd_info_entry * entry,
				   काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा पूर्णांकel8x0 *chip = entry->निजी_data;
	अचिन्हित पूर्णांक पंचांगp;

	snd_iम_लिखो(buffer, "Intel8x0\n\n");
	अगर (chip->device_type == DEVICE_ALI)
		वापस;
	पंचांगp = igetdword(chip, ICHREG(GLOB_STA));
	snd_iम_लिखो(buffer, "Global control        : 0x%08x\n", igetdword(chip, ICHREG(GLOB_CNT)));
	snd_iम_लिखो(buffer, "Global status         : 0x%08x\n", पंचांगp);
	अगर (chip->device_type == DEVICE_INTEL_ICH4)
		snd_iम_लिखो(buffer, "SDM                   : 0x%08x\n", igetdword(chip, ICHREG(SDM)));
	snd_iम_लिखो(buffer, "AC'97 codecs ready    :");
	अगर (पंचांगp & chip->codec_isr_bits) अणु
		पूर्णांक i;
		अटल स्थिर अक्षर *codecs[3] = अणु
			"primary", "secondary", "tertiary"
		पूर्ण;
		क्रम (i = 0; i < chip->max_codecs; i++)
			अगर (पंचांगp & chip->codec_bit[i])
				snd_iम_लिखो(buffer, " %s", codecs[i]);
	पूर्ण अन्यथा
		snd_iम_लिखो(buffer, " none");
	snd_iम_लिखो(buffer, "\n");
	अगर (chip->device_type == DEVICE_INTEL_ICH4 ||
	    chip->device_type == DEVICE_SIS)
		snd_iम_लिखो(buffer, "AC'97 codecs SDIN     : %i %i %i\n",
			chip->ac97_sdin[0],
			chip->ac97_sdin[1],
			chip->ac97_sdin[2]);
पूर्ण

अटल व्योम snd_पूर्णांकel8x0_proc_init(काष्ठा पूर्णांकel8x0 *chip)
अणु
	snd_card_ro_proc_new(chip->card, "intel8x0", chip,
			     snd_पूर्णांकel8x0_proc_पढ़ो);
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा पूर्णांकel8x0 *chip = device->device_data;
	वापस snd_पूर्णांकel8x0_मुक्त(chip);
पूर्ण

काष्ठा ich_reg_info अणु
	अचिन्हित पूर्णांक पूर्णांक_sta_mask;
	अचिन्हित पूर्णांक offset;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ich_codec_bits[3] = अणु
	ICH_PCR, ICH_SCR, ICH_TCR
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक sis_codec_bits[3] = अणु
	ICH_PCR, ICH_SCR, ICH_SIS_TCR
पूर्ण;

अटल पूर्णांक snd_पूर्णांकel8x0_inside_vm(काष्ठा pci_dev *pci)
अणु
	पूर्णांक result  = inside_vm;
	अक्षर *msg   = शून्य;

	/* check module parameter first (override detection) */
	अगर (result >= 0) अणु
		msg = result ? "enable (forced) VM" : "disable (forced) VM";
		जाओ fini;
	पूर्ण

	/* check क्रम known (emulated) devices */
	result = 0;
	अगर (pci->subप्रणाली_venकरोr == PCI_SUBVENDOR_ID_REDHAT_QUMRANET &&
	    pci->subप्रणाली_device == PCI_SUBDEVICE_ID_QEMU) अणु
		/* KVM emulated sound, PCI SSID: 1af4:1100 */
		msg = "enable KVM";
		result = 1;
	पूर्ण अन्यथा अगर (pci->subप्रणाली_venकरोr == 0x1ab8) अणु
		/* Parallels VM emulated sound, PCI SSID: 1ab8:xxxx */
		msg = "enable Parallels VM";
		result = 1;
	पूर्ण

fini:
	अगर (msg != शून्य)
		dev_info(&pci->dev, "%s optimization\n", msg);

	वापस result;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_create(काष्ठा snd_card *card,
			       काष्ठा pci_dev *pci,
			       अचिन्हित दीर्घ device_type,
			       काष्ठा पूर्णांकel8x0 **r_पूर्णांकel8x0)
अणु
	काष्ठा पूर्णांकel8x0 *chip;
	पूर्णांक err;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक पूर्णांक_sta_masks;
	काष्ठा ichdev *ichdev;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_पूर्णांकel8x0_dev_मुक्त,
	पूर्ण;

	अटल स्थिर अचिन्हित पूर्णांक bdbars[] = अणु
		3, /* DEVICE_INTEL */
		6, /* DEVICE_INTEL_ICH4 */
		3, /* DEVICE_SIS */
		6, /* DEVICE_ALI */
		4, /* DEVICE_NFORCE */
	पूर्ण;
	अटल स्थिर काष्ठा ich_reg_info पूर्णांकel_regs[6] = अणु
		अणु ICH_PIINT, 0 पूर्ण,
		अणु ICH_POINT, 0x10 पूर्ण,
		अणु ICH_MCINT, 0x20 पूर्ण,
		अणु ICH_M2INT, 0x40 पूर्ण,
		अणु ICH_P2INT, 0x50 पूर्ण,
		अणु ICH_SPINT, 0x60 पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा ich_reg_info nक्रमce_regs[4] = अणु
		अणु ICH_PIINT, 0 पूर्ण,
		अणु ICH_POINT, 0x10 पूर्ण,
		अणु ICH_MCINT, 0x20 पूर्ण,
		अणु ICH_NVSPINT, 0x70 पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा ich_reg_info ali_regs[6] = अणु
		अणु ALI_INT_PCMIN, 0x40 पूर्ण,
		अणु ALI_INT_PCMOUT, 0x50 पूर्ण,
		अणु ALI_INT_MICIN, 0x60 पूर्ण,
		अणु ALI_INT_CODECSPDIFOUT, 0x70 पूर्ण,
		अणु ALI_INT_SPDIFIN, 0xa0 पूर्ण,
		अणु ALI_INT_SPDIFOUT, 0xb0 पूर्ण,
	पूर्ण;
	स्थिर काष्ठा ich_reg_info *tbl;

	*r_पूर्णांकel8x0 = शून्य;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&chip->reg_lock);
	chip->device_type = device_type;
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	/* module parameters */
	chip->buggy_irq = buggy_irq;
	chip->buggy_semaphore = buggy_semaphore;
	अगर (xbox)
		chip->xbox = 1;

	chip->inside_vm = snd_पूर्णांकel8x0_inside_vm(pci);

	/*
	 * Intel 82443MX running a 100MHz processor प्रणाली bus has a hardware
	 * bug, which पातs PCI busmaster क्रम audio transfer.  A workaround
	 * is to set the pages as non-cached.  For details, see the errata in
	 *     http://करोwnload.पूर्णांकel.com/design/chipsets/specupdt/24505108.pdf
	 */
	अगर (pci->venकरोr == PCI_VENDOR_ID_INTEL &&
	    pci->device == PCI_DEVICE_ID_INTEL_440MX)
		chip->fix_nocache = 1; /* enable workaround */

	अगर ((err = pci_request_regions(pci, card->लघुname)) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण

	अगर (device_type == DEVICE_ALI) अणु
		/* ALI5455 has no ac97 region */
		chip->bmaddr = pci_iomap(pci, 0, 0);
		जाओ port_inited;
	पूर्ण

	अगर (pci_resource_flags(pci, 2) & IORESOURCE_MEM) /* ICH4 and Nक्रमce */
		chip->addr = pci_iomap(pci, 2, 0);
	अन्यथा
		chip->addr = pci_iomap(pci, 0, 0);
	अगर (!chip->addr) अणु
		dev_err(card->dev, "AC'97 space ioremap problem\n");
		snd_पूर्णांकel8x0_मुक्त(chip);
		वापस -EIO;
	पूर्ण
	अगर (pci_resource_flags(pci, 3) & IORESOURCE_MEM) /* ICH4 */
		chip->bmaddr = pci_iomap(pci, 3, 0);
	अन्यथा
		chip->bmaddr = pci_iomap(pci, 1, 0);

 port_inited:
	अगर (!chip->bmaddr) अणु
		dev_err(card->dev, "Controller space ioremap problem\n");
		snd_पूर्णांकel8x0_मुक्त(chip);
		वापस -EIO;
	पूर्ण
	chip->bdbars_count = bdbars[device_type];

	/* initialize offsets */
	चयन (device_type) अणु
	हाल DEVICE_NFORCE:
		tbl = nक्रमce_regs;
		अवरोध;
	हाल DEVICE_ALI:
		tbl = ali_regs;
		अवरोध;
	शेष:
		tbl = पूर्णांकel_regs;
		अवरोध;
	पूर्ण
	क्रम (i = 0; i < chip->bdbars_count; i++) अणु
		ichdev = &chip->ichd[i];
		ichdev->ichd = i;
		ichdev->reg_offset = tbl[i].offset;
		ichdev->पूर्णांक_sta_mask = tbl[i].पूर्णांक_sta_mask;
		अगर (device_type == DEVICE_SIS) अणु
			/* SiS 7012 swaps the रेजिस्टरs */
			ichdev->roff_sr = ICH_REG_OFF_PICB;
			ichdev->roff_picb = ICH_REG_OFF_SR;
		पूर्ण अन्यथा अणु
			ichdev->roff_sr = ICH_REG_OFF_SR;
			ichdev->roff_picb = ICH_REG_OFF_PICB;
		पूर्ण
		अगर (device_type == DEVICE_ALI)
			ichdev->ali_slot = (ichdev->reg_offset - 0x40) / 0x10;
		/* SIS7012 handles the pcm data in bytes, others are in samples */
		ichdev->pos_shअगरt = (device_type == DEVICE_SIS) ? 0 : 1;
	पूर्ण

	/* allocate buffer descriptor lists */
	/* the start of each lists must be aligned to 8 bytes */
	अगर (snd_dma_alloc_pages(पूर्णांकel8x0_dma_type(chip), &pci->dev,
				chip->bdbars_count * माप(u32) * ICH_MAX_FRAGS * 2,
				&chip->bdbars) < 0) अणु
		snd_पूर्णांकel8x0_मुक्त(chip);
		dev_err(card->dev, "cannot allocate buffer descriptors\n");
		वापस -ENOMEM;
	पूर्ण
	/* tables must be aligned to 8 bytes here, but the kernel pages
	   are much bigger, so we करोn't care (on i386) */
	पूर्णांक_sta_masks = 0;
	क्रम (i = 0; i < chip->bdbars_count; i++) अणु
		ichdev = &chip->ichd[i];
		ichdev->bdbar = ((__le32 *)chip->bdbars.area) +
			(i * ICH_MAX_FRAGS * 2);
		ichdev->bdbar_addr = chip->bdbars.addr +
			(i * माप(u32) * ICH_MAX_FRAGS * 2);
		पूर्णांक_sta_masks |= ichdev->पूर्णांक_sta_mask;
	पूर्ण
	chip->पूर्णांक_sta_reg = device_type == DEVICE_ALI ?
		ICH_REG_ALI_INTERRUPTSR : ICH_REG_GLOB_STA;
	chip->पूर्णांक_sta_mask = पूर्णांक_sta_masks;

	pci_set_master(pci);

	चयन(chip->device_type) अणु
	हाल DEVICE_INTEL_ICH4:
		/* ICH4 can have three codecs */
		chip->max_codecs = 3;
		chip->codec_bit = ich_codec_bits;
		chip->codec_पढ़ोy_bits = ICH_PRI | ICH_SRI | ICH_TRI;
		अवरोध;
	हाल DEVICE_SIS:
		/* recent SIS7012 can have three codecs */
		chip->max_codecs = 3;
		chip->codec_bit = sis_codec_bits;
		chip->codec_पढ़ोy_bits = ICH_PRI | ICH_SRI | ICH_SIS_TRI;
		अवरोध;
	शेष:
		/* others up to two codecs */
		chip->max_codecs = 2;
		chip->codec_bit = ich_codec_bits;
		chip->codec_पढ़ोy_bits = ICH_PRI | ICH_SRI;
		अवरोध;
	पूर्ण
	क्रम (i = 0; i < chip->max_codecs; i++)
		chip->codec_isr_bits |= chip->codec_bit[i];

	अगर ((err = snd_पूर्णांकel8x0_chip_init(chip, 1)) < 0) अणु
		snd_पूर्णांकel8x0_मुक्त(chip);
		वापस err;
	पूर्ण

	/* request irq after initializaing पूर्णांक_sta_mask, etc */
	अगर (request_irq(pci->irq, snd_पूर्णांकel8x0_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_पूर्णांकel8x0_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_पूर्णांकel8x0_मुक्त(chip);
		वापस err;
	पूर्ण

	*r_पूर्णांकel8x0 = chip;
	वापस 0;
पूर्ण

अटल काष्ठा लघुname_table अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *s;
पूर्ण लघुnames[] = अणु
	अणु PCI_DEVICE_ID_INTEL_82801AA_5, "Intel 82801AA-ICH" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801AB_5, "Intel 82901AB-ICH0" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801BA_4, "Intel 82801BA-ICH2" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_440MX, "Intel 440MX" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801CA_5, "Intel 82801CA-ICH3" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801DB_5, "Intel 82801DB-ICH4" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82801EB_5, "Intel ICH5" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_ESB_5, "Intel 6300ESB" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_ICH6_18, "Intel ICH6" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_ICH7_20, "Intel ICH7" पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_ESB2_14, "Intel ESB2" पूर्ण,
	अणु PCI_DEVICE_ID_SI_7012, "SiS SI7012" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_MCP1_AUDIO, "NVidia nForce" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_MCP2_AUDIO, "NVidia nForce2" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_MCP3_AUDIO, "NVidia nForce3" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_CK8S_AUDIO, "NVidia CK8S" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_CK804_AUDIO, "NVidia CK804" पूर्ण,
	अणु PCI_DEVICE_ID_NVIDIA_CK8_AUDIO, "NVidia CK8" पूर्ण,
	अणु 0x003a, "NVidia MCP04" पूर्ण,
	अणु 0x746d, "AMD AMD8111" पूर्ण,
	अणु 0x7445, "AMD AMD768" पूर्ण,
	अणु 0x5455, "ALi M5455" पूर्ण,
	अणु 0, शून्य पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk spdअगर_aclink_शेषs[] = अणु
	SND_PCI_QUIRK(0x147b, 0x1c1a, "ASUS KN8", 1),
	अणु पूर्ण /* end */
पूर्ण;

/* look up allow/deny list क्रम SPDIF over ac-link */
अटल पूर्णांक check_शेष_spdअगर_aclink(काष्ठा pci_dev *pci)
अणु
	स्थिर काष्ठा snd_pci_quirk *w;

	w = snd_pci_quirk_lookup(pci, spdअगर_aclink_शेषs);
	अगर (w) अणु
		अगर (w->value)
			dev_dbg(&pci->dev,
				"Using SPDIF over AC-Link for %s\n",
				    snd_pci_quirk_name(w));
		अन्यथा
			dev_dbg(&pci->dev,
				"Using integrated SPDIF DMA for %s\n",
				    snd_pci_quirk_name(w));
		वापस w->value;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_पूर्णांकel8x0_probe(काष्ठा pci_dev *pci,
			      स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा snd_card *card;
	काष्ठा पूर्णांकel8x0 *chip;
	पूर्णांक err;
	काष्ठा लघुname_table *name;

	err = snd_card_new(&pci->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	अगर (spdअगर_aclink < 0)
		spdअगर_aclink = check_शेष_spdअगर_aclink(pci);

	म_नकल(card->driver, "ICH");
	अगर (!spdअगर_aclink) अणु
		चयन (pci_id->driver_data) अणु
		हाल DEVICE_NFORCE:
			म_नकल(card->driver, "NFORCE");
			अवरोध;
		हाल DEVICE_INTEL_ICH4:
			म_नकल(card->driver, "ICH4");
		पूर्ण
	पूर्ण

	म_नकल(card->लघुname, "Intel ICH");
	क्रम (name = लघुnames; name->id; name++) अणु
		अगर (pci->device == name->id) अणु
			म_नकल(card->लघुname, name->s);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (buggy_irq < 0) अणु
		/* some Nक्रमce[2] and ICH boards have problems with IRQ handling.
		 * Needs to वापस IRQ_HANDLED क्रम unknown irqs.
		 */
		अगर (pci_id->driver_data == DEVICE_NFORCE)
			buggy_irq = 1;
		अन्यथा
			buggy_irq = 0;
	पूर्ण

	अगर ((err = snd_पूर्णांकel8x0_create(card, pci, pci_id->driver_data,
				       &chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = chip;

	अगर ((err = snd_पूर्णांकel8x0_mixer(chip, ac97_घड़ी, ac97_quirk)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_पूर्णांकel8x0_pcm(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	
	snd_पूर्णांकel8x0_proc_init(chip);

	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s with %s at irq %i", card->लघुname,
		 snd_ac97_get_लघु_name(chip->ac97[0]), chip->irq);

	अगर (ac97_घड़ी == 0 || ac97_घड़ी == 1) अणु
		अगर (ac97_घड़ी == 0) अणु
			अगर (पूर्णांकel8x0_in_घड़ी_list(chip) == 0)
				पूर्णांकel8x0_measure_ac97_घड़ी(chip);
		पूर्ण अन्यथा अणु
			पूर्णांकel8x0_measure_ac97_घड़ी(chip);
		पूर्ण
	पूर्ण

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	वापस 0;
पूर्ण

अटल व्योम snd_पूर्णांकel8x0_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver पूर्णांकel8x0_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_पूर्णांकel8x0_ids,
	.probe = snd_पूर्णांकel8x0_probe,
	.हटाओ = snd_पूर्णांकel8x0_हटाओ,
	.driver = अणु
		.pm = INTEL8X0_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(पूर्णांकel8x0_driver);
