<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 */
 
#अगर_अघोषित __SOUND_AU88X0_H
#घोषणा __SOUND_AU88X0_H

#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/tlv.h>

#अगर_अघोषित CHIP_AU8820
#समावेश "au88x0_eq.h"
#समावेश "au88x0_a3d.h"
#पूर्ण_अगर
#अगर_अघोषित CHIP_AU8810
#समावेश "au88x0_wt.h"
#पूर्ण_अगर

#घोषणा	hwपढ़ो(x,y) पढ़ोl((x)+(y))
#घोषणा	hwग_लिखो(x,y,z) ग_लिखोl((z),(x)+(y))

/* Vortex MPU401 defines. */
#घोषणा	MIDI_CLOCK_DIV		0x61
/* Standart MPU401 defines. */
#घोषणा	MPU401_RESET		0xff
#घोषणा	MPU401_ENTER_UART	0x3f
#घोषणा	MPU401_ACK		0xfe

// Get src रेजिस्टर value to convert from x to y.
#घोषणा	SRC_RATIO(x,y)		((((x<<15)/y) + 1)/2)

/* FIFO software state स्थिरants. */
#घोषणा FIFO_STOP 0
#घोषणा FIFO_START 1
#घोषणा FIFO_PAUSE 2

/* IRQ flags */
#घोषणा IRQ_ERR_MASK	0x00ff
#घोषणा IRQ_FATAL	0x0001
#घोषणा IRQ_PARITY	0x0002
#घोषणा IRQ_REG		0x0004
#घोषणा IRQ_FIFO	0x0008
#घोषणा IRQ_DMA		0x0010
#घोषणा IRQ_PCMOUT	0x0020	/* PCM OUT page crossing */
#घोषणा IRQ_TIMER	0x1000
#घोषणा IRQ_MIDI	0x2000
#घोषणा IRQ_MODEM	0x4000

/* ADB Resource */
#घोषणा VORTEX_RESOURCE_DMA	0x00000000
#घोषणा VORTEX_RESOURCE_SRC	0x00000001
#घोषणा VORTEX_RESOURCE_MIXIN	0x00000002
#घोषणा VORTEX_RESOURCE_MIXOUT	0x00000003
#घोषणा VORTEX_RESOURCE_A3D	0x00000004
#घोषणा VORTEX_RESOURCE_LAST	0x00000005

/* codec io: VORTEX_CODEC_IO bits */
#घोषणा VORTEX_CODEC_ID_SHIFT	24
#घोषणा VORTEX_CODEC_WRITE	0x00800000
#घोषणा VORTEX_CODEC_ADDSHIFT 	16
#घोषणा VORTEX_CODEC_ADDMASK	0x7f0000
#घोषणा VORTEX_CODEC_DATSHIFT	0
#घोषणा VORTEX_CODEC_DATMASK	0xffff

/* Check क्रम SDAC bit in "Extended audio ID" AC97 रेजिस्टर */
//#घोषणा VORTEX_IS_QUAD(x) (((x)->codec == शून्य) ?  0 : ((x)->codec->ext_id&0x80))
#घोषणा VORTEX_IS_QUAD(x) ((x)->isquad)
/* Check अगर chip has bug. */
#घोषणा IS_BAD_CHIP(x) (\
	(x->rev == 0xfe && x->device == PCI_DEVICE_ID_AUREAL_VORTEX_2) || \
	(x->rev == 0xfe && x->device == PCI_DEVICE_ID_AUREAL_ADVANTAGE))


/* PCM devices */
#घोषणा VORTEX_PCM_ADB		0
#घोषणा VORTEX_PCM_SPDIF	1
#घोषणा VORTEX_PCM_A3D		2
#घोषणा VORTEX_PCM_WT		3
#घोषणा VORTEX_PCM_I2S		4
#घोषणा VORTEX_PCM_LAST		5

#घोषणा MIX_CAPT(x) (vortex->mixcapt[x])
#घोषणा MIX_PLAYB(x) (vortex->mixplayb[x])
#घोषणा MIX_SPDIF(x) (vortex->mixspdअगर[x])

#घोषणा NR_WTPB 0x20		/* WT channels per each bank. */
#घोषणा NR_PCM	0x10

काष्ठा pcm_vol अणु
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक active;
	पूर्णांक dma;
	पूर्णांक mixin[4];
	पूर्णांक vol[4];
पूर्ण;

/* Structs */
प्रकार काष्ठा अणु
	//पूर्णांक this_08;          /* Still unknown */
	पूर्णांक fअगरo_enabled;	/* this_24 */
	पूर्णांक fअगरo_status;	/* this_1c */
	u32 dma_ctrl;		/* this_78 (ADB), this_7c (WT) */
	पूर्णांक dma_unknown;	/* this_74 (ADB), this_78 (WT). WDM: +8 */
	पूर्णांक cfg0;
	पूर्णांक cfg1;

	पूर्णांक nr_ch;		/* Nr of PCM channels in use */
	पूर्णांक type;		/* Output type (ac97, a3d, spdअगर, i2s, dsp) */
	पूर्णांक dma;		/* Hardware DMA index. */
	पूर्णांक dir;		/* Stream Direction. */
	u32 resources[5];

	/* Virtual page extender stuff */
	पूर्णांक nr_periods;
	पूर्णांक period_bytes;
	पूर्णांक period_real;
	पूर्णांक period_virt;

	काष्ठा snd_pcm_substream *substream;
पूर्ण stream_t;

प्रकार काष्ठा snd_vortex vortex_t;
काष्ठा snd_vortex अणु
	/* ALSA काष्ठाs. */
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm[VORTEX_PCM_LAST];

	काष्ठा snd_rawmidi *rmidi;	/* Legacy Midi पूर्णांकerface. */
	काष्ठा snd_ac97 *codec;

	/* Stream काष्ठाs. */
	stream_t dma_adb[NR_ADB];
	पूर्णांक spdअगर_sr;
#अगर_अघोषित CHIP_AU8810
	stream_t dma_wt[NR_WT];
	wt_voice_t wt_voice[NR_WT];	/* WT रेजिस्टर cache. */
	अक्षर mixwt[(NR_WT / NR_WTPB) * 6];	/* WT mixin objects */
#पूर्ण_अगर

	/* Global resources */
	s8 mixcapt[2];
	s8 mixplayb[4];
#अगर_अघोषित CHIP_AU8820
	s8 mixspdअगर[2];
	s8 mixa3d[2];	/* mixers which collect all a3d streams. */
	s8 mixxtlk[2];	/* crosstalk canceler mixer inमाला_दो. */
#पूर्ण_अगर
	u32 fixed_res[5];

#अगर_अघोषित CHIP_AU8820
	/* Hardware equalizer काष्ठाs */
	eqlzr_t eq;
	/* A3D काष्ठाs */
	a3dsrc_t a3d[NR_A3D];
	/* Xtalk canceler */
	पूर्णांक xt_mode;		/* 1: speakers, 0:headphones. */
#पूर्ण_अगर
	काष्ठा pcm_vol pcm_vol[NR_PCM];

	पूर्णांक isquad;		/* cache of extended ID codec flag. */

	/* Gameport stuff. */
	काष्ठा gameport *gameport;

	/* PCI hardware resources */
	अचिन्हित दीर्घ io;
	व्योम __iomem *mmio;
	अचिन्हित पूर्णांक irq;
	spinlock_t lock;

	/* PCI device */
	काष्ठा pci_dev *pci_dev;
	u16 venकरोr;
	u16 device;
	u8 rev;
पूर्ण;

/* Functions. */

/* SRC */
अटल व्योम vortex_adb_setsrc(vortex_t * vortex, पूर्णांक adbdma,
			      अचिन्हित पूर्णांक cvrt, पूर्णांक dir);

/* DMA Engines. */
अटल व्योम vortex_adbdma_रखो_बफfers(vortex_t * vortex, पूर्णांक adbdma,
				     पूर्णांक size, पूर्णांक count);
अटल व्योम vortex_adbdma_seपंचांगode(vortex_t * vortex, पूर्णांक adbdma, पूर्णांक ie,
				  पूर्णांक dir, पूर्णांक fmt, पूर्णांक d,
				  u32 offset);
अटल व्योम vortex_adbdma_setstartbuffer(vortex_t * vortex, पूर्णांक adbdma, पूर्णांक sb);
#अगर_अघोषित CHIP_AU8810
अटल व्योम vortex_wtdma_रखो_बफfers(vortex_t * vortex, पूर्णांक wtdma,
				    पूर्णांक size, पूर्णांक count);
अटल व्योम vortex_wtdma_seपंचांगode(vortex_t * vortex, पूर्णांक wtdma, पूर्णांक ie, पूर्णांक fmt, पूर्णांक d,	/*पूर्णांक e, */
				 u32 offset);
अटल व्योम vortex_wtdma_setstartbuffer(vortex_t * vortex, पूर्णांक wtdma, पूर्णांक sb);
#पूर्ण_अगर

अटल व्योम vortex_adbdma_startfअगरo(vortex_t * vortex, पूर्णांक adbdma);
//अटल व्योम vortex_adbdma_stopfअगरo(vortex_t *vortex, पूर्णांक adbdma);
अटल व्योम vortex_adbdma_छोड़ोfअगरo(vortex_t * vortex, पूर्णांक adbdma);
अटल व्योम vortex_adbdma_resumefअगरo(vortex_t * vortex, पूर्णांक adbdma);
अटल अंतरभूत पूर्णांक vortex_adbdma_getlinearpos(vortex_t * vortex, पूर्णांक adbdma);
अटल व्योम vortex_adbdma_resetup(vortex_t *vortex, पूर्णांक adbdma);

#अगर_अघोषित CHIP_AU8810
अटल व्योम vortex_wtdma_startfअगरo(vortex_t * vortex, पूर्णांक wtdma);
अटल व्योम vortex_wtdma_stopfअगरo(vortex_t * vortex, पूर्णांक wtdma);
अटल व्योम vortex_wtdma_छोड़ोfअगरo(vortex_t * vortex, पूर्णांक wtdma);
अटल व्योम vortex_wtdma_resumefअगरo(vortex_t * vortex, पूर्णांक wtdma);
अटल अंतरभूत पूर्णांक vortex_wtdma_getlinearpos(vortex_t * vortex, पूर्णांक wtdma);
#पूर्ण_अगर

/* global stuff. */
अटल व्योम vortex_codec_init(vortex_t * vortex);
अटल व्योम vortex_codec_ग_लिखो(काष्ठा snd_ac97 * codec, अचिन्हित लघु addr,
			       अचिन्हित लघु data);
अटल अचिन्हित लघु vortex_codec_पढ़ो(काष्ठा snd_ac97 * codec, अचिन्हित लघु addr);
अटल व्योम vortex_spdअगर_init(vortex_t * vortex, पूर्णांक spdअगर_sr, पूर्णांक spdअगर_mode);

अटल पूर्णांक vortex_core_init(vortex_t * card);
अटल पूर्णांक vortex_core_shutकरोwn(vortex_t * card);
अटल व्योम vortex_enable_पूर्णांक(vortex_t * card);
अटल irqवापस_t vortex_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक vortex_alsafmt_aspfmt(snd_pcm_क्रमmat_t alsafmt, vortex_t *v);

/* Connection  stuff. */
अटल व्योम vortex_connect_शेष(vortex_t * vortex, पूर्णांक en);
अटल पूर्णांक vortex_adb_allocroute(vortex_t * vortex, पूर्णांक dma, पूर्णांक nr_ch,
				 पूर्णांक dir, पूर्णांक type, पूर्णांक subdev);
अटल अक्षर vortex_adb_checkinout(vortex_t * vortex, पूर्णांक resmap[], पूर्णांक out,
				  पूर्णांक restype);
#अगर_अघोषित CHIP_AU8810
अटल पूर्णांक vortex_wt_allocroute(vortex_t * vortex, पूर्णांक dma, पूर्णांक nr_ch);
अटल व्योम vortex_wt_connect(vortex_t * vortex, पूर्णांक en);
अटल व्योम vortex_wt_init(vortex_t * vortex);
#पूर्ण_अगर

अटल व्योम vortex_route(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर channel,
			 अचिन्हित अक्षर source, अचिन्हित अक्षर dest);
#अगर 0
अटल व्योम vortex_routes(vortex_t * vortex, पूर्णांक en, अचिन्हित अक्षर channel,
			  अचिन्हित अक्षर source, अचिन्हित अक्षर dest0,
			  अचिन्हित अक्षर dest1);
#पूर्ण_अगर
अटल व्योम vortex_connection_mixin_mix(vortex_t * vortex, पूर्णांक en,
					अचिन्हित अक्षर mixin,
					अचिन्हित अक्षर mix, पूर्णांक a);
अटल व्योम vortex_mix_setinputvolumebyte(vortex_t * vortex,
					  अचिन्हित अक्षर mix, पूर्णांक mixin,
					  अचिन्हित अक्षर vol);
अटल व्योम vortex_mix_setvolumebyte(vortex_t * vortex, अचिन्हित अक्षर mix,
				     अचिन्हित अक्षर vol);

/* A3D functions. */
#अगर_अघोषित CHIP_AU8820
अटल व्योम vortex_Vort3D_enable(vortex_t * v);
अटल व्योम vortex_Vort3D_disable(vortex_t * v);
अटल व्योम vortex_Vort3D_connect(vortex_t * vortex, पूर्णांक en);
अटल व्योम vortex_Vort3D_InitializeSource(a3dsrc_t *a, पूर्णांक en, vortex_t *v);
#पूर्ण_अगर

/* Driver stuff. */
अटल पूर्णांक vortex_gameport_रेजिस्टर(vortex_t * card);
अटल व्योम vortex_gameport_unरेजिस्टर(vortex_t * card);
#अगर_अघोषित CHIP_AU8820
अटल पूर्णांक vortex_eq_init(vortex_t * vortex);
अटल पूर्णांक vortex_eq_मुक्त(vortex_t * vortex);
#पूर्ण_अगर
/* ALSA stuff. */
अटल पूर्णांक snd_vortex_new_pcm(vortex_t * vortex, पूर्णांक idx, पूर्णांक nr);
अटल पूर्णांक snd_vortex_mixer(vortex_t * vortex);
अटल पूर्णांक snd_vortex_midi(vortex_t * vortex);
#पूर्ण_अगर
