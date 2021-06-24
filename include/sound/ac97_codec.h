<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+
 *
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal पूर्णांकerface क्रम Audio Codec '97
 *
 *  For more details look to AC '97 component specअगरication revision 2.1
 *  by Intel Corporation (http://developer.पूर्णांकel.com).
 */

#अगर_अघोषित __SOUND_AC97_CODEC_H
#घोषणा __SOUND_AC97_CODEC_H

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/ac97/regs.h>
#समावेश <sound/pcm.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>

/* maximum number of devices on the AC97 bus */
#घोषणा	AC97_BUS_MAX_DEVICES	4

/* specअगरic - SigmaTel */
#घोषणा AC97_SIGMATEL_OUTSEL	0x64	/* Output Select, STAC9758 */
#घोषणा AC97_SIGMATEL_INSEL	0x66	/* Input Select, STAC9758 */
#घोषणा AC97_SIGMATEL_IOMISC	0x68	/* STAC9758 */
#घोषणा AC97_SIGMATEL_ANALOG	0x6c	/* Analog Special */
#घोषणा AC97_SIGMATEL_DAC2INVERT 0x6e
#घोषणा AC97_SIGMATEL_BIAS1	0x70
#घोषणा AC97_SIGMATEL_BIAS2	0x72
#घोषणा AC97_SIGMATEL_VARIOUS	0x72	/* STAC9758 */
#घोषणा AC97_SIGMATEL_MULTICHN	0x74	/* Multi-Channel programming */
#घोषणा AC97_SIGMATEL_CIC1	0x76
#घोषणा AC97_SIGMATEL_CIC2	0x78

/* specअगरic - Analog Devices */
#घोषणा AC97_AD_TEST		0x5a	/* test रेजिस्टर */
#घोषणा AC97_AD_TEST2		0x5c	/* unकरोcumented test रेजिस्टर 2 */
#घोषणा AC97_AD_HPFD_SHIFT	12	/* High Pass Filter Disable */
#घोषणा AC97_AD_CODEC_CFG	0x70	/* codec configuration */
#घोषणा AC97_AD_JACK_SPDIF	0x72	/* Jack Sense & S/PDIF */
#घोषणा AC97_AD_SERIAL_CFG	0x74	/* Serial Configuration */
#घोषणा AC97_AD_MISC		0x76	/* Misc Control Bits */
#घोषणा AC97_AD_VREFD_SHIFT	2	/* V_REFOUT Disable (AD1888) */

/* specअगरic - Cirrus Logic */
#घोषणा AC97_CSR_ACMODE		0x5e	/* AC Mode Register */
#घोषणा AC97_CSR_MISC_CRYSTAL	0x60	/* Misc Crystal Control */
#घोषणा AC97_CSR_SPDIF		0x68	/* S/PDIF Register */
#घोषणा AC97_CSR_SERIAL		0x6a	/* Serial Port Control */
#घोषणा AC97_CSR_SPECF_ADDR	0x6c	/* Special Feature Address */
#घोषणा AC97_CSR_SPECF_DATA	0x6e	/* Special Feature Data */
#घोषणा AC97_CSR_BDI_STATUS	0x7a	/* BDI Status */

/* specअगरic - Conexant */
#घोषणा AC97_CXR_AUDIO_MISC	0x5c
#घोषणा AC97_CXR_SPDIFEN	(1<<3)
#घोषणा AC97_CXR_COPYRGT	(1<<2)
#घोषणा AC97_CXR_SPDIF_MASK	(3<<0)
#घोषणा AC97_CXR_SPDIF_PCM	0x0
#घोषणा AC97_CXR_SPDIF_AC3	0x2

/* specअगरic - ALC */
#घोषणा AC97_ALC650_SPDIF_INPUT_STATUS1	0x60
/* S/PDIF input status 1 bit defines */
#घोषणा AC97_ALC650_PRO             0x0001  /* Professional status */
#घोषणा AC97_ALC650_NAUDIO          0x0002  /* Non audio stream */
#घोषणा AC97_ALC650_COPY            0x0004  /* Copyright status */
#घोषणा AC97_ALC650_PRE             0x0038  /* Preemphasis status */
#घोषणा AC97_ALC650_PRE_SHIFT       3
#घोषणा AC97_ALC650_MODE            0x00C0  /* Preemphasis status */
#घोषणा AC97_ALC650_MODE_SHIFT      6
#घोषणा AC97_ALC650_CC_MASK         0x7f00  /* Category Code mask */
#घोषणा AC97_ALC650_CC_SHIFT        8
#घोषणा AC97_ALC650_L               0x8000  /* Generation Level status */

#घोषणा AC97_ALC650_SPDIF_INPUT_STATUS2	0x62
/* S/PDIF input status 2 bit defines */
#घोषणा AC97_ALC650_SOUCE_MASK      0x000f  /* Source number */
#घोषणा AC97_ALC650_CHANNEL_MASK    0x00f0  /* Channel number */
#घोषणा AC97_ALC650_CHANNEL_SHIFT   4 
#घोषणा AC97_ALC650_SPSR_MASK       0x0f00  /* S/PDIF Sample Rate bits */
#घोषणा AC97_ALC650_SPSR_SHIFT      8
#घोषणा AC97_ALC650_SPSR_44K        0x0000  /* Use 44.1kHz Sample rate */
#घोषणा AC97_ALC650_SPSR_48K        0x0200  /* Use 48kHz Sample rate */
#घोषणा AC97_ALC650_SPSR_32K        0x0300  /* Use 32kHz Sample rate */
#घोषणा AC97_ALC650_CLOCK_ACCURACY  0x3000  /* Clock accuracy */
#घोषणा AC97_ALC650_CLOCK_SHIFT     12
#घोषणा AC97_ALC650_CLOCK_LOCK      0x4000  /* Clock locked status */
#घोषणा AC97_ALC650_V               0x8000  /* Validity status */

#घोषणा AC97_ALC650_SURR_DAC_VOL	0x64
#घोषणा AC97_ALC650_LFE_DAC_VOL		0x66
#घोषणा AC97_ALC650_UNKNOWN1		0x68
#घोषणा AC97_ALC650_MULTICH		0x6a
#घोषणा AC97_ALC650_UNKNOWN2		0x6c
#घोषणा AC97_ALC650_REVISION		0x6e
#घोषणा AC97_ALC650_UNKNOWN3		0x70
#घोषणा AC97_ALC650_UNKNOWN4		0x72
#घोषणा AC97_ALC650_MISC		0x74
#घोषणा AC97_ALC650_GPIO_SETUP		0x76
#घोषणा AC97_ALC650_GPIO_STATUS		0x78
#घोषणा AC97_ALC650_CLOCK		0x7a

/* specअगरic - Yamaha YMF7x3 */
#घोषणा AC97_YMF7X3_DIT_CTRL	0x66	/* DIT Control (YMF743) / 2 (YMF753) */
#घोषणा AC97_YMF7X3_3D_MODE_SEL	0x68	/* 3D Mode Select */

/* specअगरic - C-Media */
#घोषणा AC97_CM9738_VENDOR_CTRL	0x5a
#घोषणा AC97_CM9739_MULTI_CHAN	0x64
#घोषणा AC97_CM9739_SPDIF_IN_STATUS	0x68 /* 32bit */
#घोषणा AC97_CM9739_SPDIF_CTRL	0x6c

/* specअगरic - wolfson */
#घोषणा AC97_WM97XX_FMIXER_VOL  0x72
#घोषणा AC97_WM9704_RMIXER_VOL  0x74
#घोषणा AC97_WM9704_TEST        0x5a
#घोषणा AC97_WM9704_RPCM_VOL    0x70
#घोषणा AC97_WM9711_OUT3VOL     0x16


/* ac97->scaps */
#घोषणा AC97_SCAP_AUDIO		(1<<0)	/* audio codec 97 */
#घोषणा AC97_SCAP_MODEM		(1<<1)	/* modem codec 97 */
#घोषणा AC97_SCAP_SURROUND_DAC	(1<<2)	/* surround L&R DACs are present */
#घोषणा AC97_SCAP_CENTER_LFE_DAC (1<<3)	/* center and LFE DACs are present */
#घोषणा AC97_SCAP_SKIP_AUDIO	(1<<4)	/* skip audio part of codec */
#घोषणा AC97_SCAP_SKIP_MODEM	(1<<5)	/* skip modem part of codec */
#घोषणा AC97_SCAP_INDEP_SDIN	(1<<6)	/* independent SDIN */
#घोषणा AC97_SCAP_INV_EAPD	(1<<7)	/* inverted EAPD */
#घोषणा AC97_SCAP_DETECT_BY_VENDOR (1<<8) /* use venकरोr रेजिस्टरs क्रम पढ़ो tests */
#घोषणा AC97_SCAP_NO_SPDIF	(1<<9)	/* करोn't build SPDIF controls */
#घोषणा AC97_SCAP_EAPD_LED	(1<<10)	/* EAPD as mute LED */
#घोषणा AC97_SCAP_POWER_SAVE	(1<<11)	/* capable क्रम aggressive घातer-saving */

/* ac97->flags */
#घोषणा AC97_HAS_PC_BEEP	(1<<0)	/* क्रमce PC Speaker usage */
#घोषणा AC97_AD_MULTI		(1<<1)	/* Analog Devices - multi codecs */
#घोषणा AC97_CS_SPDIF		(1<<2)	/* Cirrus Logic uses funky SPDIF */
#घोषणा AC97_CX_SPDIF		(1<<3)	/* Conexant's spdअगर पूर्णांकerface */
#घोषणा AC97_STEREO_MUTES	(1<<4)	/* has stereo mute bits */
#घोषणा AC97_DOUBLE_RATE	(1<<5)	/* supports द्विगुन rate playback */
#घोषणा AC97_HAS_NO_MASTER_VOL	(1<<6)	/* no Master volume */
#घोषणा AC97_HAS_NO_PCM_VOL	(1<<7)	/* no PCM volume */
#घोषणा AC97_DEFAULT_POWER_OFF	(1<<8)	/* no RESET ग_लिखो */
#घोषणा AC97_MODEM_PATCH	(1<<9)	/* modem patch */
#घोषणा AC97_HAS_NO_REC_GAIN	(1<<10) /* no Record gain */
#घोषणा AC97_HAS_NO_PHONE	(1<<11) /* no PHONE volume */
#घोषणा AC97_HAS_NO_PC_BEEP	(1<<12) /* no PC Beep volume */
#घोषणा AC97_HAS_NO_VIDEO	(1<<13) /* no Video volume */
#घोषणा AC97_HAS_NO_CD		(1<<14) /* no CD volume */
#घोषणा AC97_HAS_NO_MIC	(1<<15) /* no MIC volume */
#घोषणा AC97_HAS_NO_TONE	(1<<16) /* no Tone volume */
#घोषणा AC97_HAS_NO_STD_PCM	(1<<17)	/* no standard AC97 PCM volume and mute */
#घोषणा AC97_HAS_NO_AUX		(1<<18) /* no standard AC97 AUX volume and mute */
#घोषणा AC97_HAS_8CH		(1<<19) /* supports 8-channel output */

/* rates indexes */
#घोषणा AC97_RATES_FRONT_DAC	0
#घोषणा AC97_RATES_SURR_DAC	1
#घोषणा AC97_RATES_LFE_DAC	2
#घोषणा AC97_RATES_ADC		3
#घोषणा AC97_RATES_MIC_ADC	4
#घोषणा AC97_RATES_SPDIF	5

#घोषणा AC97_NUM_GPIOS		16
/*
 *
 */

काष्ठा snd_ac97;
काष्ठा snd_ac97_gpio_priv;
काष्ठा snd_pcm_chmap;

काष्ठा snd_ac97_build_ops अणु
	पूर्णांक (*build_3d) (काष्ठा snd_ac97 *ac97);
	पूर्णांक (*build_specअगरic) (काष्ठा snd_ac97 *ac97);
	पूर्णांक (*build_spdअगर) (काष्ठा snd_ac97 *ac97);
	पूर्णांक (*build_post_spdअगर) (काष्ठा snd_ac97 *ac97);
#अगर_घोषित CONFIG_PM
	व्योम (*suspend) (काष्ठा snd_ac97 *ac97);
	व्योम (*resume) (काष्ठा snd_ac97 *ac97);
#पूर्ण_अगर
	व्योम (*update_jacks) (काष्ठा snd_ac97 *ac97);	/* क्रम jack-sharing */
पूर्ण;

काष्ठा snd_ac97_bus_ops अणु
	व्योम (*reset) (काष्ठा snd_ac97 *ac97);
	व्योम (*warm_reset)(काष्ठा snd_ac97 *ac97);
	व्योम (*ग_लिखो) (काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु val);
	अचिन्हित लघु (*पढ़ो) (काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg);
	व्योम (*रुको) (काष्ठा snd_ac97 *ac97);
	व्योम (*init) (काष्ठा snd_ac97 *ac97);
पूर्ण;

काष्ठा snd_ac97_bus अणु
	/* -- lowlevel (hardware) driver specअगरic -- */
	स्थिर काष्ठा snd_ac97_bus_ops *ops;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त) (काष्ठा snd_ac97_bus *bus);
	/* --- */
	काष्ठा snd_card *card;
	अचिन्हित लघु num;	/* bus number */
	अचिन्हित लघु no_vra: 1, /* bridge करोesn't support VRA */
		       dra: 1,	/* bridge supports द्विगुन rate */
		       isdin: 1;/* independent SDIN */
	अचिन्हित पूर्णांक घड़ी;	/* AC'97 base घड़ी (usually 48000Hz) */
	spinlock_t bus_lock;	/* used मुख्यly क्रम slot allocation */
	अचिन्हित लघु used_slots[2][4]; /* actually used PCM slots */
	अचिन्हित लघु pcms_count; /* count of PCMs */
	काष्ठा ac97_pcm *pcms;
	काष्ठा snd_ac97 *codec[4];
	काष्ठा snd_info_entry *proc;
पूर्ण;

/* अटल resolution table */
काष्ठा snd_ac97_res_table अणु
	अचिन्हित लघु reg;	/* रेजिस्टर */
	अचिन्हित लघु bits;	/* resolution biपंचांगask */
पूर्ण;

काष्ठा snd_ac97_ढाँचा अणु
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त) (काष्ठा snd_ac97 *ac97);
	काष्ठा pci_dev *pci;	/* asचिन्हित PCI device - used क्रम quirks */
	अचिन्हित लघु num;	/* number of codec: 0 = primary, 1 = secondary */
	अचिन्हित लघु addr;	/* physical address of codec [0-3] */
	अचिन्हित पूर्णांक scaps;	/* driver capabilities */
	स्थिर काष्ठा snd_ac97_res_table *res_table;	/* अटल resolution */
पूर्ण;

काष्ठा snd_ac97 अणु
	/* -- lowlevel (hardware) driver specअगरic -- */
	स्थिर काष्ठा snd_ac97_build_ops *build_ops;
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त) (काष्ठा snd_ac97 *ac97);
	/* --- */
	काष्ठा snd_ac97_bus *bus;
	काष्ठा pci_dev *pci;	/* asचिन्हित PCI device - used क्रम quirks */
	काष्ठा snd_info_entry *proc;
	काष्ठा snd_info_entry *proc_regs;
	अचिन्हित लघु subप्रणाली_venकरोr;
	अचिन्हित लघु subप्रणाली_device;
	काष्ठा mutex reg_mutex;
	काष्ठा mutex page_mutex;	/* mutex क्रम AD18xx multi-codecs and paging (2.3) */
	अचिन्हित लघु num;	/* number of codec: 0 = primary, 1 = secondary */
	अचिन्हित लघु addr;	/* physical address of codec [0-3] */
	अचिन्हित पूर्णांक id;	/* identअगरication of codec */
	अचिन्हित लघु caps;	/* capabilities (रेजिस्टर 0) */
	अचिन्हित लघु ext_id;	/* extended feature identअगरication (रेजिस्टर 28) */
	अचिन्हित लघु ext_mid;	/* extended modem ID (रेजिस्टर 3C) */
	स्थिर काष्ठा snd_ac97_res_table *res_table;	/* अटल resolution */
	अचिन्हित पूर्णांक scaps;	/* driver capabilities */
	अचिन्हित पूर्णांक flags;	/* specअगरic code */
	अचिन्हित पूर्णांक rates[6];	/* see AC97_RATES_* defines */
	अचिन्हित पूर्णांक spdअगर_status;
	अचिन्हित लघु regs[0x80]; /* रेजिस्टर cache */
	DECLARE_BITMAP(reg_accessed, 0x80); /* bit flags */
	जोड़ अणु			/* venकरोr specअगरic code */
		काष्ठा अणु
			अचिन्हित लघु unchained[3];	// 0 = C34, 1 = C79, 2 = C69
			अचिन्हित लघु chained[3];	// 0 = C34, 1 = C79, 2 = C69
			अचिन्हित लघु id[3];		// codec IDs (lower 16-bit word)
			अचिन्हित लघु pcmreg[3];	// PCM रेजिस्टरs
			अचिन्हित लघु codec_cfg[3];	// CODEC_CFG bits
			अचिन्हित अक्षर swap_mic_linein;	// AD1986/AD1986A only
			अचिन्हित अक्षर lo_as_master;	/* LO as master */
		पूर्ण ad18xx;
		अचिन्हित पूर्णांक dev_flags;		/* device specअगरic */
	पूर्ण spec;
	/* jack-sharing info */
	अचिन्हित अक्षर indep_surround;
	अचिन्हित अक्षर channel_mode;

#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
	अचिन्हित पूर्णांक घातer_up;	/* घातer states */
	काष्ठा delayed_work घातer_work;
#पूर्ण_अगर
	काष्ठा device dev;
	काष्ठा snd_ac97_gpio_priv *gpio_priv;

	काष्ठा snd_pcm_chmap *chmaps[2]; /* channel-maps (optional) */
पूर्ण;

#घोषणा to_ac97_t(d) container_of(d, काष्ठा snd_ac97, dev)

/* conditions */
अटल अंतरभूत पूर्णांक ac97_is_audio(काष्ठा snd_ac97 * ac97)
अणु
	वापस (ac97->scaps & AC97_SCAP_AUDIO);
पूर्ण
अटल अंतरभूत पूर्णांक ac97_is_modem(काष्ठा snd_ac97 * ac97)
अणु
	वापस (ac97->scaps & AC97_SCAP_MODEM);
पूर्ण
अटल अंतरभूत पूर्णांक ac97_is_rev22(काष्ठा snd_ac97 * ac97)
अणु
	वापस (ac97->ext_id & AC97_EI_REV_MASK) >= AC97_EI_REV_22;
पूर्ण
अटल अंतरभूत पूर्णांक ac97_can_amap(काष्ठा snd_ac97 * ac97)
अणु
	वापस (ac97->ext_id & AC97_EI_AMAP) != 0;
पूर्ण
अटल अंतरभूत पूर्णांक ac97_can_spdअगर(काष्ठा snd_ac97 * ac97)
अणु
	वापस (ac97->ext_id & AC97_EI_SPDIF) != 0;
पूर्ण

/* functions */
/* create new AC97 bus */
पूर्णांक snd_ac97_bus(काष्ठा snd_card *card, पूर्णांक num,
		 स्थिर काष्ठा snd_ac97_bus_ops *ops,
		 व्योम *निजी_data, काष्ठा snd_ac97_bus **rbus);
/* create mixer controls */
पूर्णांक snd_ac97_mixer(काष्ठा snd_ac97_bus *bus, काष्ठा snd_ac97_ढाँचा *ढाँचा,
		   काष्ठा snd_ac97 **rac97);
स्थिर अक्षर *snd_ac97_get_लघु_name(काष्ठा snd_ac97 *ac97);

व्योम snd_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु value);
अचिन्हित लघु snd_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg);
व्योम snd_ac97_ग_लिखो_cache(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु value);
पूर्णांक snd_ac97_update(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु value);
पूर्णांक snd_ac97_update_bits(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु mask, अचिन्हित लघु value);
#अगर_घोषित CONFIG_SND_AC97_POWER_SAVE
पूर्णांक snd_ac97_update_घातer(काष्ठा snd_ac97 *ac97, पूर्णांक reg, पूर्णांक घातerup);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_ac97_update_घातer(काष्ठा snd_ac97 *ac97, पूर्णांक reg,
					पूर्णांक घातerup)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PM
व्योम snd_ac97_suspend(काष्ठा snd_ac97 *ac97);
व्योम snd_ac97_resume(काष्ठा snd_ac97 *ac97);
#पूर्ण_अगर
पूर्णांक snd_ac97_reset(काष्ठा snd_ac97 *ac97, bool try_warm, अचिन्हित पूर्णांक id,
	अचिन्हित पूर्णांक id_mask);

/* quirk types */
क्रमागत अणु
	AC97_TUNE_DEFAULT = -1,	/* use शेष from quirk list (not valid in list) */
	AC97_TUNE_NONE = 0,	/* nothing extra to करो */
	AC97_TUNE_HP_ONLY,	/* headphone (true line-out) control as master only */
	AC97_TUNE_SWAP_HP,	/* swap headphone and master controls */
	AC97_TUNE_SWAP_SURROUND, /* swap master and surround controls */
	AC97_TUNE_AD_SHARING,	/* क्रम AD1985, turn on OMS bit and use headphone */
	AC97_TUNE_ALC_JACK,	/* क्रम Realtek, enable JACK detection */
	AC97_TUNE_INV_EAPD,	/* inverted EAPD implementation */
	AC97_TUNE_MUTE_LED,	/* EAPD bit works as mute LED */
	AC97_TUNE_HP_MUTE_LED,  /* EAPD bit works as mute LED, use headphone control as master */
पूर्ण;

काष्ठा ac97_quirk अणु
	अचिन्हित लघु subvenकरोr; /* PCI subप्रणाली venकरोr id */
	अचिन्हित लघु subdevice; /* PCI subप्रणाली device id */
	अचिन्हित लघु mask;	/* device id bit mask, 0 = accept all */
	अचिन्हित पूर्णांक codec_id;	/* codec id (अगर any), 0 = accept all */
	स्थिर अक्षर *name;	/* name shown as info */
	पूर्णांक type;		/* quirk type above */
पूर्ण;

पूर्णांक snd_ac97_tune_hardware(काष्ठा snd_ac97 *ac97,
			   स्थिर काष्ठा ac97_quirk *quirk,
			   स्थिर अक्षर *override);
पूर्णांक snd_ac97_set_rate(काष्ठा snd_ac97 *ac97, पूर्णांक reg, अचिन्हित पूर्णांक rate);

/*
 * PCM allocation
 */

क्रमागत ac97_pcm_cfg अणु
	AC97_PCM_CFG_FRONT = 2,
	AC97_PCM_CFG_REAR = 10,		/* alias surround */
	AC97_PCM_CFG_LFE = 11,		/* center + lfe */
	AC97_PCM_CFG_40 = 4,		/* front + rear */
	AC97_PCM_CFG_51 = 6,		/* front + rear + center/lfe */
	AC97_PCM_CFG_SPDIF = 20
पूर्ण;

काष्ठा ac97_pcm अणु
	काष्ठा snd_ac97_bus *bus;
	अचिन्हित पूर्णांक stream: 1,	   	   /* stream type: 1 = capture */
		     exclusive: 1,	   /* exclusive mode, करोn't override with other pcms */
		     copy_flag: 1,	   /* lowlevel driver must fill all entries */
		     spdअगर: 1;		   /* spdअगर pcm */
	अचिन्हित लघु aslots;		   /* active slots */
	अचिन्हित लघु cur_dbl;		   /* current द्विगुन-rate state */
	अचिन्हित पूर्णांक rates;		   /* available rates */
	काष्ठा अणु
		अचिन्हित लघु slots;	   /* driver input: requested AC97 slot numbers */
		अचिन्हित लघु rslots[4];  /* allocated slots per codecs */
		अचिन्हित अक्षर rate_table[4];
		काष्ठा snd_ac97 *codec[4];	   /* allocated codecs */
	पूर्ण r[2];				   /* 0 = standard rates, 1 = द्विगुन rates */
	अचिन्हित दीर्घ निजी_value;	   /* used by the hardware driver */
पूर्ण;

पूर्णांक snd_ac97_pcm_assign(काष्ठा snd_ac97_bus *ac97,
			अचिन्हित लघु pcms_count,
			स्थिर काष्ठा ac97_pcm *pcms);
पूर्णांक snd_ac97_pcm_खोलो(काष्ठा ac97_pcm *pcm, अचिन्हित पूर्णांक rate,
		      क्रमागत ac97_pcm_cfg cfg, अचिन्हित लघु slots);
पूर्णांक snd_ac97_pcm_बंद(काष्ठा ac97_pcm *pcm);
पूर्णांक snd_ac97_pcm_द्विगुन_rate_rules(काष्ठा snd_pcm_runसमय *runसमय);

/* ad hoc AC97 device driver access */
बाह्य काष्ठा bus_type ac97_bus_type;

/* AC97 platक्रमm_data adding function */
अटल अंतरभूत व्योम snd_ac97_dev_add_pdata(काष्ठा snd_ac97 *ac97, व्योम *data)
अणु
	ac97->dev.platक्रमm_data = data;
पूर्ण

#पूर्ण_अगर /* __SOUND_AC97_CODEC_H */
