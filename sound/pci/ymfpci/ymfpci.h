<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_YMFPCI_H
#घोषणा __SOUND_YMFPCI_H

/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Definitions क्रम Yahama YMF724/740/744/754 chips
 */

#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/समयr.h>
#समावेश <linux/gameport.h>

/*
 *  Direct रेजिस्टरs
 */

#घोषणा YMFREG(chip, reg)		(chip->port + YDSXGR_##reg)

#घोषणा	YDSXGR_INTFLAG			0x0004
#घोषणा	YDSXGR_ACTIVITY			0x0006
#घोषणा	YDSXGR_GLOBALCTRL		0x0008
#घोषणा	YDSXGR_ZVCTRL			0x000A
#घोषणा	YDSXGR_TIMERCTRL		0x0010
#घोषणा	YDSXGR_TIMERCOUNT		0x0012
#घोषणा	YDSXGR_SPDIFOUTCTRL		0x0018
#घोषणा	YDSXGR_SPDIFOUTSTATUS		0x001C
#घोषणा	YDSXGR_EEPROMCTRL		0x0020
#घोषणा	YDSXGR_SPDIFINCTRL		0x0034
#घोषणा	YDSXGR_SPDIFINSTATUS		0x0038
#घोषणा	YDSXGR_DSPPROGRAMDL		0x0048
#घोषणा	YDSXGR_DLCNTRL			0x004C
#घोषणा	YDSXGR_GPIOININTFLAG		0x0050
#घोषणा	YDSXGR_GPIOININTENABLE		0x0052
#घोषणा	YDSXGR_GPIOINSTATUS		0x0054
#घोषणा	YDSXGR_GPIOOUTCTRL		0x0056
#घोषणा	YDSXGR_GPIOFUNCENABLE		0x0058
#घोषणा	YDSXGR_GPIOTYPECONFIG		0x005A
#घोषणा	YDSXGR_AC97CMDDATA		0x0060
#घोषणा	YDSXGR_AC97CMDADR		0x0062
#घोषणा	YDSXGR_PRISTATUSDATA		0x0064
#घोषणा	YDSXGR_PRISTATUSADR		0x0066
#घोषणा	YDSXGR_SECSTATUSDATA		0x0068
#घोषणा	YDSXGR_SECSTATUSADR		0x006A
#घोषणा	YDSXGR_SECCONFIG		0x0070
#घोषणा	YDSXGR_LEGACYOUTVOL		0x0080
#घोषणा	YDSXGR_LEGACYOUTVOLL		0x0080
#घोषणा	YDSXGR_LEGACYOUTVOLR		0x0082
#घोषणा	YDSXGR_NATIVEDACOUTVOL		0x0084
#घोषणा	YDSXGR_NATIVEDACOUTVOLL		0x0084
#घोषणा	YDSXGR_NATIVEDACOUTVOLR		0x0086
#घोषणा	YDSXGR_ZVOUTVOL			0x0088
#घोषणा	YDSXGR_ZVOUTVOLL		0x0088
#घोषणा	YDSXGR_ZVOUTVOLR		0x008A
#घोषणा	YDSXGR_SECADCOUTVOL		0x008C
#घोषणा	YDSXGR_SECADCOUTVOLL		0x008C
#घोषणा	YDSXGR_SECADCOUTVOLR		0x008E
#घोषणा	YDSXGR_PRIADCOUTVOL		0x0090
#घोषणा	YDSXGR_PRIADCOUTVOLL		0x0090
#घोषणा	YDSXGR_PRIADCOUTVOLR		0x0092
#घोषणा	YDSXGR_LEGACYLOOPVOL		0x0094
#घोषणा	YDSXGR_LEGACYLOOPVOLL		0x0094
#घोषणा	YDSXGR_LEGACYLOOPVOLR		0x0096
#घोषणा	YDSXGR_NATIVEDACLOOPVOL		0x0098
#घोषणा	YDSXGR_NATIVEDACLOOPVOLL	0x0098
#घोषणा	YDSXGR_NATIVEDACLOOPVOLR	0x009A
#घोषणा	YDSXGR_ZVLOOPVOL		0x009C
#घोषणा	YDSXGR_ZVLOOPVOLL		0x009E
#घोषणा	YDSXGR_ZVLOOPVOLR		0x009E
#घोषणा	YDSXGR_SECADCLOOPVOL		0x00A0
#घोषणा	YDSXGR_SECADCLOOPVOLL		0x00A0
#घोषणा	YDSXGR_SECADCLOOPVOLR		0x00A2
#घोषणा	YDSXGR_PRIADCLOOPVOL		0x00A4
#घोषणा	YDSXGR_PRIADCLOOPVOLL		0x00A4
#घोषणा	YDSXGR_PRIADCLOOPVOLR		0x00A6
#घोषणा	YDSXGR_NATIVEADCINVOL		0x00A8
#घोषणा	YDSXGR_NATIVEADCINVOLL		0x00A8
#घोषणा	YDSXGR_NATIVEADCINVOLR		0x00AA
#घोषणा	YDSXGR_NATIVEDACINVOL		0x00AC
#घोषणा	YDSXGR_NATIVEDACINVOLL		0x00AC
#घोषणा	YDSXGR_NATIVEDACINVOLR		0x00AE
#घोषणा	YDSXGR_BUF441OUTVOL		0x00B0
#घोषणा	YDSXGR_BUF441OUTVOLL		0x00B0
#घोषणा	YDSXGR_BUF441OUTVOLR		0x00B2
#घोषणा	YDSXGR_BUF441LOOPVOL		0x00B4
#घोषणा	YDSXGR_BUF441LOOPVOLL		0x00B4
#घोषणा	YDSXGR_BUF441LOOPVOLR		0x00B6
#घोषणा	YDSXGR_SPDIFOUTVOL		0x00B8
#घोषणा	YDSXGR_SPDIFOUTVOLL		0x00B8
#घोषणा	YDSXGR_SPDIFOUTVOLR		0x00BA
#घोषणा	YDSXGR_SPDIFLOOPVOL		0x00BC
#घोषणा	YDSXGR_SPDIFLOOPVOLL		0x00BC
#घोषणा	YDSXGR_SPDIFLOOPVOLR		0x00BE
#घोषणा	YDSXGR_ADCSLOTSR		0x00C0
#घोषणा	YDSXGR_RECSLOTSR		0x00C4
#घोषणा	YDSXGR_ADCFORMAT		0x00C8
#घोषणा	YDSXGR_RECFORMAT		0x00CC
#घोषणा	YDSXGR_P44SLOTSR		0x00D0
#घोषणा	YDSXGR_STATUS			0x0100
#घोषणा	YDSXGR_CTRLSELECT		0x0104
#घोषणा	YDSXGR_MODE			0x0108
#घोषणा	YDSXGR_SAMPLECOUNT		0x010C
#घोषणा	YDSXGR_NUMOFSAMPLES		0x0110
#घोषणा	YDSXGR_CONFIG			0x0114
#घोषणा	YDSXGR_PLAYCTRLSIZE		0x0140
#घोषणा	YDSXGR_RECCTRLSIZE		0x0144
#घोषणा	YDSXGR_EFFCTRLSIZE		0x0148
#घोषणा	YDSXGR_WORKSIZE			0x014C
#घोषणा	YDSXGR_MAPOFREC			0x0150
#घोषणा	YDSXGR_MAPOFEFFECT		0x0154
#घोषणा	YDSXGR_PLAYCTRLBASE		0x0158
#घोषणा	YDSXGR_RECCTRLBASE		0x015C
#घोषणा	YDSXGR_EFFCTRLBASE		0x0160
#घोषणा	YDSXGR_WORKBASE			0x0164
#घोषणा	YDSXGR_DSPINSTRAM		0x1000
#घोषणा	YDSXGR_CTRLINSTRAM		0x4000

#घोषणा YDSXG_AC97READCMD		0x8000
#घोषणा YDSXG_AC97WRITECMD		0x0000

#घोषणा PCIR_DSXG_LEGACY		0x40
#घोषणा PCIR_DSXG_ELEGACY		0x42
#घोषणा PCIR_DSXG_CTRL			0x48
#घोषणा PCIR_DSXG_PWRCTRL1		0x4a
#घोषणा PCIR_DSXG_PWRCTRL2		0x4e
#घोषणा PCIR_DSXG_FMBASE		0x60
#घोषणा PCIR_DSXG_SBBASE		0x62
#घोषणा PCIR_DSXG_MPU401BASE		0x64
#घोषणा PCIR_DSXG_JOYBASE		0x66

#घोषणा YDSXG_DSPLENGTH			0x0080
#घोषणा YDSXG_CTRLLENGTH		0x3000

#घोषणा YDSXG_DEFAULT_WORK_SIZE		0x0400

#घोषणा YDSXG_PLAYBACK_VOICES		64
#घोषणा YDSXG_CAPTURE_VOICES		2
#घोषणा YDSXG_EFFECT_VOICES		5

#घोषणा YMFPCI_LEGACY_SBEN	(1 << 0)	/* soundblaster enable */
#घोषणा YMFPCI_LEGACY_FMEN	(1 << 1)	/* OPL3 enable */
#घोषणा YMFPCI_LEGACY_JPEN	(1 << 2)	/* joystick enable */
#घोषणा YMFPCI_LEGACY_MEN	(1 << 3)	/* MPU401 enable */
#घोषणा YMFPCI_LEGACY_MIEN	(1 << 4)	/* MPU RX irq enable */
#घोषणा YMFPCI_LEGACY_IOBITS	(1 << 5)	/* i/o bits range, 0 = 16bit, 1 =10bit */
#घोषणा YMFPCI_LEGACY_SDMA	(3 << 6)	/* SB DMA select */
#घोषणा YMFPCI_LEGACY_SBIRQ	(7 << 8)	/* SB IRQ select */
#घोषणा YMFPCI_LEGACY_MPUIRQ	(7 << 11)	/* MPU IRQ select */
#घोषणा YMFPCI_LEGACY_SIEN	(1 << 14)	/* serialized IRQ */
#घोषणा YMFPCI_LEGACY_LAD	(1 << 15)	/* legacy audio disable */

#घोषणा YMFPCI_LEGACY2_FMIO	(3 << 0)	/* OPL3 i/o address (724/740) */
#घोषणा YMFPCI_LEGACY2_SBIO	(3 << 2)	/* SB i/o address (724/740) */
#घोषणा YMFPCI_LEGACY2_MPUIO	(3 << 4)	/* MPU401 i/o address (724/740) */
#घोषणा YMFPCI_LEGACY2_JSIO	(3 << 6)	/* joystick i/o address (724/740) */
#घोषणा YMFPCI_LEGACY2_MAIM	(1 << 8)	/* MPU401 ack पूर्णांकr mask */
#घोषणा YMFPCI_LEGACY2_SMOD	(3 << 11)	/* SB DMA mode */
#घोषणा YMFPCI_LEGACY2_SBVER	(3 << 13)	/* SB version select */
#घोषणा YMFPCI_LEGACY2_IMOD	(1 << 15)	/* legacy IRQ mode */
/* SIEN:IMOD 0:0 = legacy irq, 0:1 = INTA, 1:0 = serialized IRQ */

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK
#पूर्ण_अगर

/*
 *
 */

काष्ठा snd_ymfpci_playback_bank अणु
	__le32 क्रमmat;
	__le32 loop_शेष;
	__le32 base;			/* 32-bit address */
	__le32 loop_start;		/* 32-bit offset */
	__le32 loop_end;		/* 32-bit offset */
	__le32 loop_frac;		/* 8-bit fraction - loop_start */
	__le32 delta_end;		/* pitch delta end */
	__le32 lpfK_end;
	__le32 eg_gain_end;
	__le32 left_gain_end;
	__le32 right_gain_end;
	__le32 eff1_gain_end;
	__le32 eff2_gain_end;
	__le32 eff3_gain_end;
	__le32 lpfQ;
	__le32 status;
	__le32 num_of_frames;
	__le32 loop_count;
	__le32 start;
	__le32 start_frac;
	__le32 delta;
	__le32 lpfK;
	__le32 eg_gain;
	__le32 left_gain;
	__le32 right_gain;
	__le32 eff1_gain;
	__le32 eff2_gain;
	__le32 eff3_gain;
	__le32 lpfD1;
	__le32 lpfD2;
 पूर्ण;

काष्ठा snd_ymfpci_capture_bank अणु
	__le32 base;			/* 32-bit address */
	__le32 loop_end;		/* 32-bit offset */
	__le32 start;			/* 32-bit offset */
	__le32 num_of_loops;		/* counter */
पूर्ण;

काष्ठा snd_ymfpci_effect_bank अणु
	__le32 base;			/* 32-bit address */
	__le32 loop_end;		/* 32-bit offset */
	__le32 start;			/* 32-bit offset */
	__le32 temp;
पूर्ण;

काष्ठा snd_ymfpci_pcm;
काष्ठा snd_ymfpci;

क्रमागत snd_ymfpci_voice_type अणु
	YMFPCI_PCM,
	YMFPCI_SYNTH,
	YMFPCI_MIDI
पूर्ण;

काष्ठा snd_ymfpci_voice अणु
	काष्ठा snd_ymfpci *chip;
	पूर्णांक number;
	अचिन्हित पूर्णांक use: 1,
	    pcm: 1,
	    synth: 1,
	    midi: 1;
	काष्ठा snd_ymfpci_playback_bank *bank;
	dma_addr_t bank_addr;
	व्योम (*पूर्णांकerrupt)(काष्ठा snd_ymfpci *chip, काष्ठा snd_ymfpci_voice *voice);
	काष्ठा snd_ymfpci_pcm *ypcm;
पूर्ण;

क्रमागत snd_ymfpci_pcm_type अणु
	PLAYBACK_VOICE,
	CAPTURE_REC,
	CAPTURE_AC97,
	EFFECT_DRY_LEFT,
	EFFECT_DRY_RIGHT,
	EFFECT_EFF1,
	EFFECT_EFF2,
	EFFECT_EFF3
पूर्ण;

काष्ठा snd_ymfpci_pcm अणु
	काष्ठा snd_ymfpci *chip;
	क्रमागत snd_ymfpci_pcm_type type;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_ymfpci_voice *voices[2];	/* playback only */
	अचिन्हित पूर्णांक running: 1,
		     use_441_slot: 1,
	             output_front: 1,
	             output_rear: 1,
	             swap_rear: 1;
	अचिन्हित पूर्णांक update_pcm_vol;
	u32 period_size;		/* cached from runसमय->period_size */
	u32 buffer_size;		/* cached from runसमय->buffer_size */
	u32 period_pos;
	u32 last_pos;
	u32 capture_bank_number;
	u32 shअगरt;
पूर्ण;

काष्ठा snd_ymfpci अणु
	पूर्णांक irq;

	अचिन्हित पूर्णांक device_id;	/* PCI device ID */
	अचिन्हित अक्षर rev;	/* PCI revision */
	अचिन्हित दीर्घ reg_area_phys;
	व्योम __iomem *reg_area_virt;
	काष्ठा resource *res_reg_area;
	काष्ठा resource *fm_res;
	काष्ठा resource *mpu_res;

	अचिन्हित लघु old_legacy_ctrl;
#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा gameport *gameport;
#पूर्ण_अगर

	काष्ठा snd_dma_buffer work_ptr;

	अचिन्हित पूर्णांक bank_size_playback;
	अचिन्हित पूर्णांक bank_size_capture;
	अचिन्हित पूर्णांक bank_size_effect;
	अचिन्हित पूर्णांक work_size;

	व्योम *bank_base_playback;
	व्योम *bank_base_capture;
	व्योम *bank_base_effect;
	व्योम *work_base;
	dma_addr_t bank_base_playback_addr;
	dma_addr_t bank_base_capture_addr;
	dma_addr_t bank_base_effect_addr;
	dma_addr_t work_base_addr;
	काष्ठा snd_dma_buffer ac3_पंचांगp_base;

	__le32 *ctrl_playback;
	काष्ठा snd_ymfpci_playback_bank *bank_playback[YDSXG_PLAYBACK_VOICES][2];
	काष्ठा snd_ymfpci_capture_bank *bank_capture[YDSXG_CAPTURE_VOICES][2];
	काष्ठा snd_ymfpci_effect_bank *bank_effect[YDSXG_EFFECT_VOICES][2];

	पूर्णांक start_count;

	u32 active_bank;
	काष्ठा snd_ymfpci_voice voices[64];
	पूर्णांक src441_used;

	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_rawmidi *rawmidi;
	काष्ठा snd_समयr *समयr;
	अचिन्हित पूर्णांक समयr_ticks;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm *pcm2;
	काष्ठा snd_pcm *pcm_spdअगर;
	काष्ठा snd_pcm *pcm_4ch;
	काष्ठा snd_pcm_substream *capture_substream[YDSXG_CAPTURE_VOICES];
	काष्ठा snd_pcm_substream *effect_substream[YDSXG_EFFECT_VOICES];
	काष्ठा snd_kcontrol *ctl_vol_recsrc;
	काष्ठा snd_kcontrol *ctl_vol_adcrec;
	काष्ठा snd_kcontrol *ctl_vol_spdअगरrec;
	अचिन्हित लघु spdअगर_bits, spdअगर_pcm_bits;
	काष्ठा snd_kcontrol *spdअगर_pcm_ctl;
	पूर्णांक mode_dup4ch;
	पूर्णांक rear_खोलोed;
	पूर्णांक spdअगर_खोलोed;
	काष्ठा snd_ymfpci_pcm_mixer अणु
		u16 left;
		u16 right;
		काष्ठा snd_kcontrol *ctl;
	पूर्ण pcm_mixer[32];

	spinlock_t reg_lock;
	spinlock_t voice_lock;
	रुको_queue_head_t पूर्णांकerrupt_sleep;
	atomic_t पूर्णांकerrupt_sleep_count;
	काष्ठा snd_info_entry *proc_entry;
	स्थिर काष्ठा firmware *dsp_microcode;
	स्थिर काष्ठा firmware *controller_microcode;

#अगर_घोषित CONFIG_PM_SLEEP
	u32 *saved_regs;
	u32 saved_ydsxgr_mode;
	u16 saved_dsxg_legacy;
	u16 saved_dsxg_elegacy;
#पूर्ण_अगर
पूर्ण;

पूर्णांक snd_ymfpci_create(काष्ठा snd_card *card,
		      काष्ठा pci_dev *pci,
		      अचिन्हित लघु old_legacy_ctrl,
		      काष्ठा snd_ymfpci ** rcodec);
व्योम snd_ymfpci_मुक्त_gameport(काष्ठा snd_ymfpci *chip);

बाह्य स्थिर काष्ठा dev_pm_ops snd_ymfpci_pm;

पूर्णांक snd_ymfpci_pcm(काष्ठा snd_ymfpci *chip, पूर्णांक device);
पूर्णांक snd_ymfpci_pcm2(काष्ठा snd_ymfpci *chip, पूर्णांक device);
पूर्णांक snd_ymfpci_pcm_spdअगर(काष्ठा snd_ymfpci *chip, पूर्णांक device);
पूर्णांक snd_ymfpci_pcm_4ch(काष्ठा snd_ymfpci *chip, पूर्णांक device);
पूर्णांक snd_ymfpci_mixer(काष्ठा snd_ymfpci *chip, पूर्णांक rear_चयन);
पूर्णांक snd_ymfpci_समयr(काष्ठा snd_ymfpci *chip, पूर्णांक device);

#पूर्ण_अगर /* __SOUND_YMFPCI_H */
