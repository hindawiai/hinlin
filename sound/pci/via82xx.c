<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम VIA VT82xx (South Bridge)
 *
 *   VT82C686A/B/C, VT8233A/C, VT8235
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 *	                   Tjeerd.Mulder <Tjeerd.Mulder@fujitsu-siemens.com>
 *                    2002 Takashi Iwai <tiwai@suse.de>
 */

/*
 * Changes:
 *
 * Dec. 19, 2002	Takashi Iwai <tiwai@suse.de>
 *	- use the DSX channels क्रम the first pcm playback.
 *	  (on VIA8233, 8233C and 8235 only)
 *	  this will allow you play simultaneously up to 4 streams.
 *	  multi-channel playback is asचिन्हित to the second device
 *	  on these chips.
 *	- support the secondary capture (on VIA8233/C,8235)
 *	- SPDIF support
 *	  the DSX3 channel can be used क्रम SPDIF output.
 *	  on VIA8233A, this channel is asचिन्हित to the second pcm
 *	  playback.
 *	  the card config of alsa-lib will assign the correct
 *	  device क्रम applications.
 *	- clean up the code, separate low-level initialization
 *	  routines क्रम each chipset.
 *
 * Sep. 26, 2005	Karsten Wiese <annabellesgarden@yahoo.de>
 *	- Optimize position calculation क्रम the 823x chips. 
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/info.h>
#समावेश <sound/tlv.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/initval.h>

#अगर 0
#घोषणा POINTER_DEBUG
#पूर्ण_अगर

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("VIA VT82xx audio");
MODULE_LICENSE("GPL");

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK 1
#पूर्ण_अगर

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;	/* Index 0-MAX */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
अटल दीर्घ mpu_port;
#अगर_घोषित SUPPORT_JOYSTICK
अटल bool joystick;
#पूर्ण_अगर
अटल पूर्णांक ac97_घड़ी = 48000;
अटल अक्षर *ac97_quirk;
अटल पूर्णांक dxs_support;
अटल पूर्णांक dxs_init_volume = 31;
अटल पूर्णांक nodelay;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for VIA 82xx bridge.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for VIA 82xx bridge.");
module_param_hw(mpu_port, दीर्घ, ioport, 0444);
MODULE_PARM_DESC(mpu_port, "MPU-401 port. (VT82C686x only)");
#अगर_घोषित SUPPORT_JOYSTICK
module_param(joystick, bool, 0444);
MODULE_PARM_DESC(joystick, "Enable joystick. (VT82C686x only)");
#पूर्ण_अगर
module_param(ac97_घड़ी, पूर्णांक, 0444);
MODULE_PARM_DESC(ac97_घड़ी, "AC'97 codec clock (default 48000Hz).");
module_param(ac97_quirk, अक्षरp, 0444);
MODULE_PARM_DESC(ac97_quirk, "AC'97 workaround for strange hardware.");
module_param(dxs_support, पूर्णांक, 0444);
MODULE_PARM_DESC(dxs_support, "Support for DXS channels (0 = auto, 1 = enable, 2 = disable, 3 = 48k only, 4 = no VRA, 5 = enable any sample rate)");
module_param(dxs_init_volume, पूर्णांक, 0644);
MODULE_PARM_DESC(dxs_init_volume, "initial DXS volume (0-31)");
module_param(nodelay, पूर्णांक, 0444);
MODULE_PARM_DESC(nodelay, "Disable 500ms init delay");

/* just क्रम backward compatibility */
अटल bool enable;
module_param(enable, bool, 0444);


/* revision numbers क्रम via686 */
#घोषणा VIA_REV_686_A		0x10
#घोषणा VIA_REV_686_B		0x11
#घोषणा VIA_REV_686_C		0x12
#घोषणा VIA_REV_686_D		0x13
#घोषणा VIA_REV_686_E		0x14
#घोषणा VIA_REV_686_H		0x20

/* revision numbers क्रम via8233 */
#घोषणा VIA_REV_PRE_8233	0x10	/* not in market */
#घोषणा VIA_REV_8233C		0x20	/* 2 rec, 4 pb, 1 multi-pb */
#घोषणा VIA_REV_8233		0x30	/* 2 rec, 4 pb, 1 multi-pb, spdअगर */
#घोषणा VIA_REV_8233A		0x40	/* 1 rec, 1 multi-pb, spdf */
#घोषणा VIA_REV_8235		0x50	/* 2 rec, 4 pb, 1 multi-pb, spdअगर */
#घोषणा VIA_REV_8237		0x60
#घोषणा VIA_REV_8251		0x70

/*
 *  Direct रेजिस्टरs
 */

#घोषणा VIAREG(via, x) ((via)->port + VIA_REG_##x)
#घोषणा VIADEV_REG(viadev, x) ((viadev)->port + VIA_REG_##x)

/* common offsets */
#घोषणा VIA_REG_OFFSET_STATUS		0x00	/* byte - channel status */
#घोषणा   VIA_REG_STAT_ACTIVE		0x80	/* RO */
#घोषणा   VIA8233_SHADOW_STAT_ACTIVE	0x08	/* RO */
#घोषणा   VIA_REG_STAT_PAUSED		0x40	/* RO */
#घोषणा   VIA_REG_STAT_TRIGGER_QUEUED	0x08	/* RO */
#घोषणा   VIA_REG_STAT_STOPPED		0x04	/* RWC */
#घोषणा   VIA_REG_STAT_EOL		0x02	/* RWC */
#घोषणा   VIA_REG_STAT_FLAG		0x01	/* RWC */
#घोषणा VIA_REG_OFFSET_CONTROL		0x01	/* byte - channel control */
#घोषणा   VIA_REG_CTRL_START		0x80	/* WO */
#घोषणा   VIA_REG_CTRL_TERMINATE	0x40	/* WO */
#घोषणा   VIA_REG_CTRL_AUTOSTART	0x20
#घोषणा   VIA_REG_CTRL_PAUSE		0x08	/* RW */
#घोषणा   VIA_REG_CTRL_INT_STOP		0x04		
#घोषणा   VIA_REG_CTRL_INT_EOL		0x02
#घोषणा   VIA_REG_CTRL_INT_FLAG		0x01
#घोषणा   VIA_REG_CTRL_RESET		0x01	/* RW - probably reset? unकरोcumented */
#घोषणा   VIA_REG_CTRL_INT (VIA_REG_CTRL_INT_FLAG | VIA_REG_CTRL_INT_EOL | VIA_REG_CTRL_AUTOSTART)
#घोषणा VIA_REG_OFFSET_TYPE		0x02	/* byte - channel type (686 only) */
#घोषणा   VIA_REG_TYPE_AUTOSTART	0x80	/* RW - स्वतःstart at EOL */
#घोषणा   VIA_REG_TYPE_16BIT		0x20	/* RW */
#घोषणा   VIA_REG_TYPE_STEREO		0x10	/* RW */
#घोषणा   VIA_REG_TYPE_INT_LLINE	0x00
#घोषणा   VIA_REG_TYPE_INT_LSAMPLE	0x04
#घोषणा   VIA_REG_TYPE_INT_LESSONE	0x08
#घोषणा   VIA_REG_TYPE_INT_MASK		0x0c
#घोषणा   VIA_REG_TYPE_INT_EOL		0x02
#घोषणा   VIA_REG_TYPE_INT_FLAG		0x01
#घोषणा VIA_REG_OFFSET_TABLE_PTR	0x04	/* dword - channel table poपूर्णांकer */
#घोषणा VIA_REG_OFFSET_CURR_PTR		0x04	/* dword - channel current poपूर्णांकer */
#घोषणा VIA_REG_OFFSET_STOP_IDX		0x08	/* dword - stop index, channel type, sample rate */
#घोषणा   VIA8233_REG_TYPE_16BIT	0x00200000	/* RW */
#घोषणा   VIA8233_REG_TYPE_STEREO	0x00100000	/* RW */
#घोषणा VIA_REG_OFFSET_CURR_COUNT	0x0c	/* dword - channel current count (24 bit) */
#घोषणा VIA_REG_OFFSET_CURR_INDEX	0x0f	/* byte - channel current index (क्रम via8233 only) */

#घोषणा DEFINE_VIA_REGSET(name,val) \
क्रमागत अणु\
	VIA_REG_##name##_STATUS		= (val),\
	VIA_REG_##name##_CONTROL	= (val) + 0x01,\
	VIA_REG_##name##_TYPE		= (val) + 0x02,\
	VIA_REG_##name##_TABLE_PTR	= (val) + 0x04,\
	VIA_REG_##name##_CURR_PTR	= (val) + 0x04,\
	VIA_REG_##name##_STOP_IDX	= (val) + 0x08,\
	VIA_REG_##name##_CURR_COUNT	= (val) + 0x0c,\
पूर्ण

/* playback block */
DEFINE_VIA_REGSET(PLAYBACK, 0x00);
DEFINE_VIA_REGSET(CAPTURE, 0x10);
DEFINE_VIA_REGSET(FM, 0x20);

/* AC'97 */
#घोषणा VIA_REG_AC97			0x80	/* dword */
#घोषणा   VIA_REG_AC97_CODEC_ID_MASK	(3<<30)
#घोषणा   VIA_REG_AC97_CODEC_ID_SHIFT	30
#घोषणा   VIA_REG_AC97_CODEC_ID_PRIMARY	0x00
#घोषणा   VIA_REG_AC97_CODEC_ID_SECONDARY 0x01
#घोषणा   VIA_REG_AC97_SECONDARY_VALID	(1<<27)
#घोषणा   VIA_REG_AC97_PRIMARY_VALID	(1<<25)
#घोषणा   VIA_REG_AC97_BUSY		(1<<24)
#घोषणा   VIA_REG_AC97_READ		(1<<23)
#घोषणा   VIA_REG_AC97_CMD_SHIFT	16
#घोषणा   VIA_REG_AC97_CMD_MASK		0x7e
#घोषणा   VIA_REG_AC97_DATA_SHIFT	0
#घोषणा   VIA_REG_AC97_DATA_MASK	0xffff

#घोषणा VIA_REG_SGD_SHADOW		0x84	/* dword */
/* via686 */
#घोषणा   VIA_REG_SGD_STAT_PB_FLAG	(1<<0)
#घोषणा   VIA_REG_SGD_STAT_CP_FLAG	(1<<1)
#घोषणा   VIA_REG_SGD_STAT_FM_FLAG	(1<<2)
#घोषणा   VIA_REG_SGD_STAT_PB_EOL	(1<<4)
#घोषणा   VIA_REG_SGD_STAT_CP_EOL	(1<<5)
#घोषणा   VIA_REG_SGD_STAT_FM_EOL	(1<<6)
#घोषणा   VIA_REG_SGD_STAT_PB_STOP	(1<<8)
#घोषणा   VIA_REG_SGD_STAT_CP_STOP	(1<<9)
#घोषणा   VIA_REG_SGD_STAT_FM_STOP	(1<<10)
#घोषणा   VIA_REG_SGD_STAT_PB_ACTIVE	(1<<12)
#घोषणा   VIA_REG_SGD_STAT_CP_ACTIVE	(1<<13)
#घोषणा   VIA_REG_SGD_STAT_FM_ACTIVE	(1<<14)
/* via8233 */
#घोषणा   VIA8233_REG_SGD_STAT_FLAG	(1<<0)
#घोषणा   VIA8233_REG_SGD_STAT_EOL	(1<<1)
#घोषणा   VIA8233_REG_SGD_STAT_STOP	(1<<2)
#घोषणा   VIA8233_REG_SGD_STAT_ACTIVE	(1<<3)
#घोषणा VIA8233_INTR_MASK(chan) ((VIA8233_REG_SGD_STAT_FLAG|VIA8233_REG_SGD_STAT_EOL) << ((chan) * 4))
#घोषणा   VIA8233_REG_SGD_CHAN_SDX	0
#घोषणा   VIA8233_REG_SGD_CHAN_MULTI	4
#घोषणा   VIA8233_REG_SGD_CHAN_REC	6
#घोषणा   VIA8233_REG_SGD_CHAN_REC1	7

#घोषणा VIA_REG_GPI_STATUS		0x88
#घोषणा VIA_REG_GPI_INTR		0x8c

/* multi-channel and capture रेजिस्टरs क्रम via8233 */
DEFINE_VIA_REGSET(MULTPLAY, 0x40);
DEFINE_VIA_REGSET(CAPTURE_8233, 0x60);

/* via8233-specअगरic रेजिस्टरs */
#घोषणा VIA_REG_OFS_PLAYBACK_VOLUME_L	0x02	/* byte */
#घोषणा VIA_REG_OFS_PLAYBACK_VOLUME_R	0x03	/* byte */
#घोषणा VIA_REG_OFS_MULTPLAY_FORMAT	0x02	/* byte - क्रमmat and channels */
#घोषणा   VIA_REG_MULTPLAY_FMT_8BIT	0x00
#घोषणा   VIA_REG_MULTPLAY_FMT_16BIT	0x80
#घोषणा   VIA_REG_MULTPLAY_FMT_CH_MASK	0x70	/* # channels << 4 (valid = 1,2,4,6) */
#घोषणा VIA_REG_OFS_CAPTURE_FIFO	0x02	/* byte - bit 6 = fअगरo  enable */
#घोषणा   VIA_REG_CAPTURE_FIFO_ENABLE	0x40

#घोषणा VIA_DXS_MAX_VOLUME		31	/* max. volume (attenuation) of reg 0x32/33 */

#घोषणा VIA_REG_CAPTURE_CHANNEL		0x63	/* byte - input select */
#घोषणा   VIA_REG_CAPTURE_CHANNEL_MIC	0x4
#घोषणा   VIA_REG_CAPTURE_CHANNEL_LINE	0
#घोषणा   VIA_REG_CAPTURE_SELECT_CODEC	0x03	/* recording source codec (0 = primary) */

#घोषणा VIA_TBL_BIT_FLAG	0x40000000
#घोषणा VIA_TBL_BIT_EOL		0x80000000

/* pci space */
#घोषणा VIA_ACLINK_STAT		0x40
#घोषणा  VIA_ACLINK_C11_READY	0x20
#घोषणा  VIA_ACLINK_C10_READY	0x10
#घोषणा  VIA_ACLINK_C01_READY	0x04 /* secondary codec पढ़ोy */
#घोषणा  VIA_ACLINK_LOWPOWER	0x02 /* low-घातer state */
#घोषणा  VIA_ACLINK_C00_READY	0x01 /* primary codec पढ़ोy */
#घोषणा VIA_ACLINK_CTRL		0x41
#घोषणा  VIA_ACLINK_CTRL_ENABLE	0x80 /* 0: disable, 1: enable */
#घोषणा  VIA_ACLINK_CTRL_RESET	0x40 /* 0: निश्चित, 1: de-निश्चित */
#घोषणा  VIA_ACLINK_CTRL_SYNC	0x20 /* 0: release SYNC, 1: क्रमce SYNC hi */
#घोषणा  VIA_ACLINK_CTRL_SDO	0x10 /* 0: release SDO, 1: क्रमce SDO hi */
#घोषणा  VIA_ACLINK_CTRL_VRA	0x08 /* 0: disable VRA, 1: enable VRA */
#घोषणा  VIA_ACLINK_CTRL_PCM	0x04 /* 0: disable PCM, 1: enable PCM */
#घोषणा  VIA_ACLINK_CTRL_FM	0x02 /* via686 only */
#घोषणा  VIA_ACLINK_CTRL_SB	0x01 /* via686 only */
#घोषणा  VIA_ACLINK_CTRL_INIT	(VIA_ACLINK_CTRL_ENABLE|\
				 VIA_ACLINK_CTRL_RESET|\
				 VIA_ACLINK_CTRL_PCM|\
				 VIA_ACLINK_CTRL_VRA)
#घोषणा VIA_FUNC_ENABLE		0x42
#घोषणा  VIA_FUNC_MIDI_PNP	0x80 /* FIXME: it's 0x40 in the datasheet! */
#घोषणा  VIA_FUNC_MIDI_IRQMASK	0x40 /* FIXME: not करोcumented! */
#घोषणा  VIA_FUNC_RX2C_WRITE	0x20
#घोषणा  VIA_FUNC_SB_FIFO_EMPTY	0x10
#घोषणा  VIA_FUNC_ENABLE_GAME	0x08
#घोषणा  VIA_FUNC_ENABLE_FM	0x04
#घोषणा  VIA_FUNC_ENABLE_MIDI	0x02
#घोषणा  VIA_FUNC_ENABLE_SB	0x01
#घोषणा VIA_PNP_CONTROL		0x43
#घोषणा VIA_FM_NMI_CTRL		0x48
#घोषणा VIA8233_VOLCHG_CTRL	0x48
#घोषणा VIA8233_SPDIF_CTRL	0x49
#घोषणा  VIA8233_SPDIF_DX3	0x08
#घोषणा  VIA8233_SPDIF_SLOT_MASK	0x03
#घोषणा  VIA8233_SPDIF_SLOT_1011	0x00
#घोषणा  VIA8233_SPDIF_SLOT_34		0x01
#घोषणा  VIA8233_SPDIF_SLOT_78		0x02
#घोषणा  VIA8233_SPDIF_SLOT_69		0x03

/*
 */

#घोषणा VIA_DXS_AUTO	0
#घोषणा VIA_DXS_ENABLE	1
#घोषणा VIA_DXS_DISABLE	2
#घोषणा VIA_DXS_48K	3
#घोषणा VIA_DXS_NO_VRA	4
#घोषणा VIA_DXS_SRC	5


/*
 * pcm stream
 */

काष्ठा snd_via_sg_table अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;
पूर्ण ;

#घोषणा VIA_TABLE_SIZE	255
#घोषणा VIA_MAX_बफ_मानE	(1<<24)

काष्ठा viadev अणु
	अचिन्हित पूर्णांक reg_offset;
	अचिन्हित दीर्घ port;
	पूर्णांक direction;	/* playback = 0, capture = 1 */
        काष्ठा snd_pcm_substream *substream;
	पूर्णांक running;
	अचिन्हित पूर्णांक tbl_entries; /* # descriptors */
	काष्ठा snd_dma_buffer table;
	काष्ठा snd_via_sg_table *idx_table;
	/* क्रम recovery from the unexpected poपूर्णांकer */
	अचिन्हित पूर्णांक lastpos;
	अचिन्हित पूर्णांक fragsize;
	अचिन्हित पूर्णांक bufsize;
	अचिन्हित पूर्णांक bufsize2;
	पूर्णांक hwptr_करोne;		/* processed frame position in the buffer */
	पूर्णांक in_पूर्णांकerrupt;
	पूर्णांक shaकरोw_shअगरt;
पूर्ण;


क्रमागत अणु TYPE_CARD_VIA686 = 1, TYPE_CARD_VIA8233 पूर्ण;
क्रमागत अणु TYPE_VIA686, TYPE_VIA8233, TYPE_VIA8233A पूर्ण;

#घोषणा VIA_MAX_DEVS	7	/* 4 playback, 1 multi, 2 capture */

काष्ठा via_rate_lock अणु
	spinlock_t lock;
	पूर्णांक rate;
	पूर्णांक used;
पूर्ण;

काष्ठा via82xx अणु
	पूर्णांक irq;

	अचिन्हित दीर्घ port;
	काष्ठा resource *mpu_res;
	पूर्णांक chip_type;
	अचिन्हित अक्षर revision;

	अचिन्हित अक्षर old_legacy;
	अचिन्हित अक्षर old_legacy_cfg;
#अगर_घोषित CONFIG_PM_SLEEP
	अचिन्हित अक्षर legacy_saved;
	अचिन्हित अक्षर legacy_cfg_saved;
	अचिन्हित अक्षर spdअगर_ctrl_saved;
	अचिन्हित अक्षर capture_src_saved[2];
	अचिन्हित पूर्णांक mpu_port_saved;
#पूर्ण_अगर

	अचिन्हित अक्षर playback_volume[4][2]; /* क्रम VIA8233/C/8235; शेष = 0 */
	अचिन्हित अक्षर playback_volume_c[2]; /* क्रम VIA8233/C/8235; शेष = 0 */

	अचिन्हित पूर्णांक पूर्णांकr_mask; /* SGD_SHADOW mask to check पूर्णांकerrupts */

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;

	अचिन्हित पूर्णांक num_devs;
	अचिन्हित पूर्णांक playback_devno, multi_devno, capture_devno;
	काष्ठा viadev devs[VIA_MAX_DEVS];
	काष्ठा via_rate_lock rates[2]; /* playback and capture */
	अचिन्हित पूर्णांक dxs_fixed: 1;	/* DXS channel accepts only 48kHz */
	अचिन्हित पूर्णांक no_vra: 1;		/* no need to set VRA on DXS channels */
	अचिन्हित पूर्णांक dxs_src: 1;	/* use full SRC capabilities of DXS */
	अचिन्हित पूर्णांक spdअगर_on: 1;	/* only spdअगर rates work to बाह्यal DACs */

	काष्ठा snd_pcm *pcms[2];
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_kcontrol *dxs_controls[4];

	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97;
	अचिन्हित पूर्णांक ac97_घड़ी;
	अचिन्हित पूर्णांक ac97_secondary;	/* secondary AC'97 codec is present */

	spinlock_t reg_lock;
	काष्ठा snd_info_entry *proc_entry;

#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा gameport *gameport;
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_via82xx_ids[] = अणु
	/* 0x1106, 0x3058 */
	अणु PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_82C686_5), TYPE_CARD_VIA686, पूर्ण,	/* 686A */
	/* 0x1106, 0x3059 */
	अणु PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_8233_5), TYPE_CARD_VIA8233, पूर्ण,	/* VT8233 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_via82xx_ids);

/*
 */

/*
 * allocate and initialize the descriptor buffers
 * periods = number of periods
 * fragsize = period size in bytes
 */
अटल पूर्णांक build_via_table(काष्ठा viadev *dev, काष्ठा snd_pcm_substream *substream,
			   काष्ठा pci_dev *pci,
			   अचिन्हित पूर्णांक periods, अचिन्हित पूर्णांक fragsize)
अणु
	अचिन्हित पूर्णांक i, idx, ofs, rest;
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	__le32 *pgtbl;

	अगर (dev->table.area == शून्य) अणु
		/* the start of each lists must be aligned to 8 bytes,
		 * but the kernel pages are much bigger, so we करोn't care
		 */
		अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
					PAGE_ALIGN(VIA_TABLE_SIZE * 2 * 8),
					&dev->table) < 0)
			वापस -ENOMEM;
	पूर्ण
	अगर (! dev->idx_table) अणु
		dev->idx_table = kदो_स्मृति_array(VIA_TABLE_SIZE,
					       माप(*dev->idx_table),
					       GFP_KERNEL);
		अगर (! dev->idx_table)
			वापस -ENOMEM;
	पूर्ण

	/* fill the entries */
	idx = 0;
	ofs = 0;
	pgtbl = (__le32 *)dev->table.area;
	क्रम (i = 0; i < periods; i++) अणु
		rest = fragsize;
		/* fill descriptors क्रम a period.
		 * a period can be split to several descriptors अगर it's
		 * over page boundary.
		 */
		करो अणु
			अचिन्हित पूर्णांक r;
			अचिन्हित पूर्णांक flag;
			अचिन्हित पूर्णांक addr;

			अगर (idx >= VIA_TABLE_SIZE) अणु
				dev_err(&pci->dev, "too much table size!\n");
				वापस -EINVAL;
			पूर्ण
			addr = snd_pcm_sgbuf_get_addr(substream, ofs);
			pgtbl[idx << 1] = cpu_to_le32(addr);
			r = snd_pcm_sgbuf_get_chunk_size(substream, ofs, rest);
			rest -= r;
			अगर (! rest) अणु
				अगर (i == periods - 1)
					flag = VIA_TBL_BIT_EOL; /* buffer boundary */
				अन्यथा
					flag = VIA_TBL_BIT_FLAG; /* period boundary */
			पूर्ण अन्यथा
				flag = 0; /* period जारीs to the next */
			/*
			dev_dbg(&pci->dev,
				"tbl %d: at %d  size %d (rest %d)\n",
				idx, ofs, r, rest);
			*/
			pgtbl[(idx<<1) + 1] = cpu_to_le32(r | flag);
			dev->idx_table[idx].offset = ofs;
			dev->idx_table[idx].size = r;
			ofs += r;
			idx++;
		पूर्ण जबतक (rest > 0);
	पूर्ण
	dev->tbl_entries = idx;
	dev->bufsize = periods * fragsize;
	dev->bufsize2 = dev->bufsize / 2;
	dev->fragsize = fragsize;
	वापस 0;
पूर्ण


अटल पूर्णांक clean_via_table(काष्ठा viadev *dev, काष्ठा snd_pcm_substream *substream,
			   काष्ठा pci_dev *pci)
अणु
	अगर (dev->table.area) अणु
		snd_dma_मुक्त_pages(&dev->table);
		dev->table.area = शून्य;
	पूर्ण
	kमुक्त(dev->idx_table);
	dev->idx_table = शून्य;
	वापस 0;
पूर्ण

/*
 *  Basic I/O
 */

अटल अंतरभूत अचिन्हित पूर्णांक snd_via82xx_codec_xपढ़ो(काष्ठा via82xx *chip)
अणु
	वापस inl(VIAREG(chip, AC97));
पूर्ण
 
अटल अंतरभूत व्योम snd_via82xx_codec_xग_लिखो(काष्ठा via82xx *chip, अचिन्हित पूर्णांक val)
अणु
	outl(val, VIAREG(chip, AC97));
पूर्ण
 
अटल पूर्णांक snd_via82xx_codec_पढ़ोy(काष्ठा via82xx *chip, पूर्णांक secondary)
अणु
	अचिन्हित पूर्णांक समयout = 1000;	/* 1ms */
	अचिन्हित पूर्णांक val;
	
	जबतक (समयout-- > 0) अणु
		udelay(1);
		अगर (!((val = snd_via82xx_codec_xपढ़ो(chip)) & VIA_REG_AC97_BUSY))
			वापस val & 0xffff;
	पूर्ण
	dev_err(chip->card->dev, "codec_ready: codec %i is not ready [0x%x]\n",
		   secondary, snd_via82xx_codec_xपढ़ो(chip));
	वापस -EIO;
पूर्ण
 
अटल पूर्णांक snd_via82xx_codec_valid(काष्ठा via82xx *chip, पूर्णांक secondary)
अणु
	अचिन्हित पूर्णांक समयout = 1000;	/* 1ms */
	अचिन्हित पूर्णांक val, val1;
	अचिन्हित पूर्णांक stat = !secondary ? VIA_REG_AC97_PRIMARY_VALID :
					 VIA_REG_AC97_SECONDARY_VALID;
	
	जबतक (समयout-- > 0) अणु
		val = snd_via82xx_codec_xपढ़ो(chip);
		val1 = val & (VIA_REG_AC97_BUSY | stat);
		अगर (val1 == stat)
			वापस val & 0xffff;
		udelay(1);
	पूर्ण
	वापस -EIO;
पूर्ण
 
अटल व्योम snd_via82xx_codec_रुको(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा via82xx *chip = ac97->निजी_data;
	__always_unused पूर्णांक err;
	err = snd_via82xx_codec_पढ़ोy(chip, ac97->num);
	/* here we need to रुको fairly क्रम दीर्घ समय.. */
	अगर (!nodelay)
		msleep(500);
पूर्ण

अटल व्योम snd_via82xx_codec_ग_लिखो(काष्ठा snd_ac97 *ac97,
				    अचिन्हित लघु reg,
				    अचिन्हित लघु val)
अणु
	काष्ठा via82xx *chip = ac97->निजी_data;
	अचिन्हित पूर्णांक xval;

	xval = !ac97->num ? VIA_REG_AC97_CODEC_ID_PRIMARY : VIA_REG_AC97_CODEC_ID_SECONDARY;
	xval <<= VIA_REG_AC97_CODEC_ID_SHIFT;
	xval |= reg << VIA_REG_AC97_CMD_SHIFT;
	xval |= val << VIA_REG_AC97_DATA_SHIFT;
	snd_via82xx_codec_xग_लिखो(chip, xval);
	snd_via82xx_codec_पढ़ोy(chip, ac97->num);
पूर्ण

अटल अचिन्हित लघु snd_via82xx_codec_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg)
अणु
	काष्ठा via82xx *chip = ac97->निजी_data;
	अचिन्हित पूर्णांक xval, val = 0xffff;
	पूर्णांक again = 0;

	xval = ac97->num << VIA_REG_AC97_CODEC_ID_SHIFT;
	xval |= ac97->num ? VIA_REG_AC97_SECONDARY_VALID : VIA_REG_AC97_PRIMARY_VALID;
	xval |= VIA_REG_AC97_READ;
	xval |= (reg & 0x7f) << VIA_REG_AC97_CMD_SHIFT;
      	जबतक (1) अणु
      		अगर (again++ > 3) अणु
			dev_err(chip->card->dev,
				"codec_read: codec %i is not valid [0x%x]\n",
				   ac97->num, snd_via82xx_codec_xपढ़ो(chip));
		      	वापस 0xffff;
		पूर्ण
		snd_via82xx_codec_xग_लिखो(chip, xval);
		udelay (20);
		अगर (snd_via82xx_codec_valid(chip, ac97->num) >= 0) अणु
			udelay(25);
			val = snd_via82xx_codec_xपढ़ो(chip);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस val & 0xffff;
पूर्ण

अटल व्योम snd_via82xx_channel_reset(काष्ठा via82xx *chip, काष्ठा viadev *viadev)
अणु
	outb(VIA_REG_CTRL_PAUSE | VIA_REG_CTRL_TERMINATE | VIA_REG_CTRL_RESET,
	     VIADEV_REG(viadev, OFFSET_CONTROL));
	inb(VIADEV_REG(viadev, OFFSET_CONTROL));
	udelay(50);
	/* disable पूर्णांकerrupts */
	outb(0x00, VIADEV_REG(viadev, OFFSET_CONTROL));
	/* clear पूर्णांकerrupts */
	outb(0x03, VIADEV_REG(viadev, OFFSET_STATUS));
	outb(0x00, VIADEV_REG(viadev, OFFSET_TYPE)); /* क्रम via686 */
	// outl(0, VIADEV_REG(viadev, OFFSET_CURR_PTR));
	viadev->lastpos = 0;
	viadev->hwptr_करोne = 0;
पूर्ण


/*
 *  Interrupt handler
 *  Used क्रम 686 and 8233A
 */
अटल irqवापस_t snd_via686_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा via82xx *chip = dev_id;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक i;

	status = inl(VIAREG(chip, SGD_SHADOW));
	अगर (! (status & chip->पूर्णांकr_mask)) अणु
		अगर (chip->rmidi)
			/* check mpu401 पूर्णांकerrupt */
			वापस snd_mpu401_uart_पूर्णांकerrupt(irq, chip->rmidi->निजी_data);
		वापस IRQ_NONE;
	पूर्ण

	/* check status क्रम each stream */
	spin_lock(&chip->reg_lock);
	क्रम (i = 0; i < chip->num_devs; i++) अणु
		काष्ठा viadev *viadev = &chip->devs[i];
		अचिन्हित अक्षर c_status = inb(VIADEV_REG(viadev, OFFSET_STATUS));
		अगर (! (c_status & (VIA_REG_STAT_EOL|VIA_REG_STAT_FLAG|VIA_REG_STAT_STOPPED)))
			जारी;
		अगर (viadev->substream && viadev->running) अणु
			/*
			 * Update hwptr_करोne based on 'period elapsed'
			 * पूर्णांकerrupts. We'll use it, when the chip वापसs 0 
			 * क्रम OFFSET_CURR_COUNT.
			 */
			अगर (c_status & VIA_REG_STAT_EOL)
				viadev->hwptr_करोne = 0;
			अन्यथा
				viadev->hwptr_करोne += viadev->fragsize;
			viadev->in_पूर्णांकerrupt = c_status;
			spin_unlock(&chip->reg_lock);
			snd_pcm_period_elapsed(viadev->substream);
			spin_lock(&chip->reg_lock);
			viadev->in_पूर्णांकerrupt = 0;
		पूर्ण
		outb(c_status, VIADEV_REG(viadev, OFFSET_STATUS)); /* ack */
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 *  Interrupt handler
 */
अटल irqवापस_t snd_via8233_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा via82xx *chip = dev_id;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक i;
	पूर्णांक irqवापस = 0;

	/* check status क्रम each stream */
	spin_lock(&chip->reg_lock);
	status = inl(VIAREG(chip, SGD_SHADOW));

	क्रम (i = 0; i < chip->num_devs; i++) अणु
		काष्ठा viadev *viadev = &chip->devs[i];
		काष्ठा snd_pcm_substream *substream;
		अचिन्हित अक्षर c_status, shaकरोw_status;

		shaकरोw_status = (status >> viadev->shaकरोw_shअगरt) &
			(VIA8233_SHADOW_STAT_ACTIVE|VIA_REG_STAT_EOL|
			 VIA_REG_STAT_FLAG);
		c_status = shaकरोw_status & (VIA_REG_STAT_EOL|VIA_REG_STAT_FLAG);
		अगर (!c_status)
			जारी;

		substream = viadev->substream;
		अगर (substream && viadev->running) अणु
			/*
			 * Update hwptr_करोne based on 'period elapsed'
			 * पूर्णांकerrupts. We'll use it, when the chip वापसs 0 
			 * क्रम OFFSET_CURR_COUNT.
			 */
			अगर (c_status & VIA_REG_STAT_EOL)
				viadev->hwptr_करोne = 0;
			अन्यथा
				viadev->hwptr_करोne += viadev->fragsize;
			viadev->in_पूर्णांकerrupt = c_status;
			अगर (shaकरोw_status & VIA8233_SHADOW_STAT_ACTIVE)
				viadev->in_पूर्णांकerrupt |= VIA_REG_STAT_ACTIVE;
			spin_unlock(&chip->reg_lock);

			snd_pcm_period_elapsed(substream);

			spin_lock(&chip->reg_lock);
			viadev->in_पूर्णांकerrupt = 0;
		पूर्ण
		outb(c_status, VIADEV_REG(viadev, OFFSET_STATUS)); /* ack */
		irqवापस = 1;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस IRQ_RETVAL(irqवापस);
पूर्ण

/*
 *  PCM callbacks
 */

/*
 * trigger callback
 */
अटल पूर्णांक snd_via82xx_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	अचिन्हित अक्षर val;

	अगर (chip->chip_type != TYPE_VIA686)
		val = VIA_REG_CTRL_INT;
	अन्यथा
		val = 0;
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		val |= VIA_REG_CTRL_START;
		viadev->running = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		val = VIA_REG_CTRL_TERMINATE;
		viadev->running = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val |= VIA_REG_CTRL_PAUSE;
		viadev->running = 0;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		viadev->running = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	outb(val, VIADEV_REG(viadev, OFFSET_CONTROL));
	अगर (cmd == SNDRV_PCM_TRIGGER_STOP)
		snd_via82xx_channel_reset(chip, viadev);
	वापस 0;
पूर्ण


/*
 * poपूर्णांकer callbacks
 */

/*
 * calculate the linear position at the given sg-buffer index and the rest count
 */

#घोषणा check_invalid_pos(viadev,pos) \
	((pos) < viadev->lastpos && ((pos) >= viadev->bufsize2 ||\
				     viadev->lastpos < viadev->bufsize2))

अटल अंतरभूत अचिन्हित पूर्णांक calc_linear_pos(काष्ठा via82xx *chip,
					   काष्ठा viadev *viadev,
					   अचिन्हित पूर्णांक idx,
					   अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक size, base, res;

	size = viadev->idx_table[idx].size;
	base = viadev->idx_table[idx].offset;
	res = base + size - count;
	अगर (res >= viadev->bufsize)
		res -= viadev->bufsize;

	/* check the validity of the calculated position */
	अगर (size < count) अणु
		dev_dbg(chip->card->dev,
			"invalid via82xx_cur_ptr (size = %d, count = %d)\n",
			   (पूर्णांक)size, (पूर्णांक)count);
		res = viadev->lastpos;
	पूर्ण अन्यथा अणु
		अगर (! count) अणु
			/* Some mobos report count = 0 on the DMA boundary,
			 * i.e. count = size indeed.
			 * Let's check whether this step is above the expected size.
			 */
			पूर्णांक delta = res - viadev->lastpos;
			अगर (delta < 0)
				delta += viadev->bufsize;
			अगर ((अचिन्हित पूर्णांक)delta > viadev->fragsize)
				res = base;
		पूर्ण
		अगर (check_invalid_pos(viadev, res)) अणु
#अगर_घोषित POINTER_DEBUG
			dev_dbg(chip->card->dev,
				"fail: idx = %i/%i, lastpos = 0x%x, bufsize2 = 0x%x, offsize = 0x%x, size = 0x%x, count = 0x%x\n",
				idx, viadev->tbl_entries,
			       viadev->lastpos, viadev->bufsize2,
			       viadev->idx_table[idx].offset,
			       viadev->idx_table[idx].size, count);
#पूर्ण_अगर
			/* count रेजिस्टर वापसs full size when end of buffer is reached */
			res = base + size;
			अगर (check_invalid_pos(viadev, res)) अणु
				dev_dbg(chip->card->dev,
					"invalid via82xx_cur_ptr (2), using last valid pointer\n");
				res = viadev->lastpos;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

/*
 * get the current poपूर्णांकer on via686
 */
अटल snd_pcm_uframes_t snd_via686_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	अचिन्हित पूर्णांक idx, ptr, count, res;

	अगर (snd_BUG_ON(!viadev->tbl_entries))
		वापस 0;
	अगर (!(inb(VIADEV_REG(viadev, OFFSET_STATUS)) & VIA_REG_STAT_ACTIVE))
		वापस 0;

	spin_lock(&chip->reg_lock);
	count = inl(VIADEV_REG(viadev, OFFSET_CURR_COUNT)) & 0xffffff;
	/* The via686a करोes not have the current index रेजिस्टर,
	 * so we need to calculate the index from CURR_PTR.
	 */
	ptr = inl(VIADEV_REG(viadev, OFFSET_CURR_PTR));
	अगर (ptr <= (अचिन्हित पूर्णांक)viadev->table.addr)
		idx = 0;
	अन्यथा /* CURR_PTR holds the address + 8 */
		idx = ((ptr - (अचिन्हित पूर्णांक)viadev->table.addr) / 8 - 1) % viadev->tbl_entries;
	res = calc_linear_pos(chip, viadev, idx, count);
	viadev->lastpos = res; /* remember the last position */
	spin_unlock(&chip->reg_lock);

	वापस bytes_to_frames(substream->runसमय, res);
पूर्ण

/*
 * get the current poपूर्णांकer on via823x
 */
अटल snd_pcm_uframes_t snd_via8233_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	अचिन्हित पूर्णांक idx, count, res;
	पूर्णांक status;
	
	अगर (snd_BUG_ON(!viadev->tbl_entries))
		वापस 0;

	spin_lock(&chip->reg_lock);
	count = inl(VIADEV_REG(viadev, OFFSET_CURR_COUNT));
	status = viadev->in_पूर्णांकerrupt;
	अगर (!status)
		status = inb(VIADEV_REG(viadev, OFFSET_STATUS));

	/* An apparent bug in the 8251 is worked around by sending a 
	 * REG_CTRL_START. */
	अगर (chip->revision == VIA_REV_8251 && (status & VIA_REG_STAT_EOL))
		snd_via82xx_pcm_trigger(substream, SNDRV_PCM_TRIGGER_START);

	अगर (!(status & VIA_REG_STAT_ACTIVE)) अणु
		res = 0;
		जाओ unlock;
	पूर्ण
	अगर (count & 0xffffff) अणु
		idx = count >> 24;
		अगर (idx >= viadev->tbl_entries) अणु
#अगर_घोषित POINTER_DEBUG
			dev_dbg(chip->card->dev,
				"fail: invalid idx = %i/%i\n", idx,
			       viadev->tbl_entries);
#पूर्ण_अगर
			res = viadev->lastpos;
		पूर्ण अन्यथा अणु
			count &= 0xffffff;
			res = calc_linear_pos(chip, viadev, idx, count);
		पूर्ण
	पूर्ण अन्यथा अणु
		res = viadev->hwptr_करोne;
		अगर (!viadev->in_पूर्णांकerrupt) अणु
			अगर (status & VIA_REG_STAT_EOL) अणु
				res = 0;
			पूर्ण अन्यथा
				अगर (status & VIA_REG_STAT_FLAG) अणु
					res += viadev->fragsize;
				पूर्ण
		पूर्ण
	पूर्ण			    
unlock:
	viadev->lastpos = res;
	spin_unlock(&chip->reg_lock);

	वापस bytes_to_frames(substream->runसमय, res);
पूर्ण


/*
 * hw_params callback:
 * allocate the buffer and build up the buffer description table
 */
अटल पूर्णांक snd_via82xx_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;

	वापस build_via_table(viadev, substream, chip->pci,
			       params_periods(hw_params),
			       params_period_bytes(hw_params));
पूर्ण

/*
 * hw_मुक्त callback:
 * clean up the buffer description table and release the buffer
 */
अटल पूर्णांक snd_via82xx_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;

	clean_via_table(viadev, substream, chip->pci);
	वापस 0;
पूर्ण


/*
 * set up the table poपूर्णांकer
 */
अटल व्योम snd_via82xx_set_table_ptr(काष्ठा via82xx *chip, काष्ठा viadev *viadev)
अणु
	snd_via82xx_codec_पढ़ोy(chip, 0);
	outl((u32)viadev->table.addr, VIADEV_REG(viadev, OFFSET_TABLE_PTR));
	udelay(20);
	snd_via82xx_codec_पढ़ोy(chip, 0);
पूर्ण

/*
 * prepare callback क्रम playback and capture on via686
 */
अटल व्योम via686_setup_क्रमmat(काष्ठा via82xx *chip, काष्ठा viadev *viadev,
				काष्ठा snd_pcm_runसमय *runसमय)
अणु
	snd_via82xx_channel_reset(chip, viadev);
	/* this must be set after channel_reset */
	snd_via82xx_set_table_ptr(chip, viadev);
	outb(VIA_REG_TYPE_AUTOSTART |
	     (runसमय->क्रमmat == SNDRV_PCM_FORMAT_S16_LE ? VIA_REG_TYPE_16BIT : 0) |
	     (runसमय->channels > 1 ? VIA_REG_TYPE_STEREO : 0) |
	     ((viadev->reg_offset & 0x10) == 0 ? VIA_REG_TYPE_INT_LSAMPLE : 0) |
	     VIA_REG_TYPE_INT_EOL |
	     VIA_REG_TYPE_INT_FLAG, VIADEV_REG(viadev, OFFSET_TYPE));
पूर्ण

अटल पूर्णांक snd_via686_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_ac97_set_rate(chip->ac97, AC97_PCM_FRONT_DAC_RATE, runसमय->rate);
	snd_ac97_set_rate(chip->ac97, AC97_SPDIF, runसमय->rate);
	via686_setup_क्रमmat(chip, viadev, runसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via686_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_ac97_set_rate(chip->ac97, AC97_PCM_LR_ADC_RATE, runसमय->rate);
	via686_setup_क्रमmat(chip, viadev, runसमय);
	वापस 0;
पूर्ण

/*
 * lock the current rate
 */
अटल पूर्णांक via_lock_rate(काष्ठा via_rate_lock *rec, पूर्णांक rate)
अणु
	पूर्णांक changed = 0;

	spin_lock_irq(&rec->lock);
	अगर (rec->rate != rate) अणु
		अगर (rec->rate && rec->used > 1) /* alपढ़ोy set */
			changed = -EINVAL;
		अन्यथा अणु
			rec->rate = rate;
			changed = 1;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&rec->lock);
	वापस changed;
पूर्ण

/*
 * prepare callback क्रम DSX playback on via823x
 */
अटल पूर्णांक snd_via8233_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ac97_rate = chip->dxs_src ? 48000 : runसमय->rate;
	पूर्णांक rate_changed;
	u32 rbits;

	अगर ((rate_changed = via_lock_rate(&chip->rates[0], ac97_rate)) < 0)
		वापस rate_changed;
	अगर (rate_changed)
		snd_ac97_set_rate(chip->ac97, AC97_PCM_FRONT_DAC_RATE,
				  chip->no_vra ? 48000 : runसमय->rate);
	अगर (chip->spdअगर_on && viadev->reg_offset == 0x30)
		snd_ac97_set_rate(chip->ac97, AC97_SPDIF, runसमय->rate);

	अगर (runसमय->rate == 48000)
		rbits = 0xfffff;
	अन्यथा
		rbits = (0x100000 / 48000) * runसमय->rate +
			((0x100000 % 48000) * runसमय->rate) / 48000;
	snd_BUG_ON(rbits & ~0xfffff);
	snd_via82xx_channel_reset(chip, viadev);
	snd_via82xx_set_table_ptr(chip, viadev);
	outb(chip->playback_volume[viadev->reg_offset / 0x10][0],
	     VIADEV_REG(viadev, OFS_PLAYBACK_VOLUME_L));
	outb(chip->playback_volume[viadev->reg_offset / 0x10][1],
	     VIADEV_REG(viadev, OFS_PLAYBACK_VOLUME_R));
	outl((runसमय->क्रमmat == SNDRV_PCM_FORMAT_S16_LE ? VIA8233_REG_TYPE_16BIT : 0) | /* क्रमmat */
	     (runसमय->channels > 1 ? VIA8233_REG_TYPE_STEREO : 0) | /* stereo */
	     rbits | /* rate */
	     0xff000000,    /* STOP index is never reached */
	     VIADEV_REG(viadev, OFFSET_STOP_IDX));
	udelay(20);
	snd_via82xx_codec_पढ़ोy(chip, 0);
	वापस 0;
पूर्ण

/*
 * prepare callback क्रम multi-channel playback on via823x
 */
अटल पूर्णांक snd_via8233_multi_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक slots;
	पूर्णांक fmt;

	अगर (via_lock_rate(&chip->rates[0], runसमय->rate) < 0)
		वापस -EINVAL;
	snd_ac97_set_rate(chip->ac97, AC97_PCM_FRONT_DAC_RATE, runसमय->rate);
	snd_ac97_set_rate(chip->ac97, AC97_PCM_SURR_DAC_RATE, runसमय->rate);
	snd_ac97_set_rate(chip->ac97, AC97_PCM_LFE_DAC_RATE, runसमय->rate);
	snd_ac97_set_rate(chip->ac97, AC97_SPDIF, runसमय->rate);
	snd_via82xx_channel_reset(chip, viadev);
	snd_via82xx_set_table_ptr(chip, viadev);

	fmt = (runसमय->क्रमmat == SNDRV_PCM_FORMAT_S16_LE) ?
		VIA_REG_MULTPLAY_FMT_16BIT : VIA_REG_MULTPLAY_FMT_8BIT;
	fmt |= runसमय->channels << 4;
	outb(fmt, VIADEV_REG(viadev, OFS_MULTPLAY_FORMAT));
#अगर 0
	अगर (chip->revision == VIA_REV_8233A)
		slots = 0;
	अन्यथा
#पूर्ण_अगर
	अणु
		/* set sample number to slot 3, 4, 7, 8, 6, 9 (क्रम VIA8233/C,8235) */
		/* corresponding to FL, FR, RL, RR, C, LFE ?? */
		चयन (runसमय->channels) अणु
		हाल 1: slots = (1<<0) | (1<<4); अवरोध;
		हाल 2: slots = (1<<0) | (2<<4); अवरोध;
		हाल 3: slots = (1<<0) | (2<<4) | (5<<8); अवरोध;
		हाल 4: slots = (1<<0) | (2<<4) | (3<<8) | (4<<12); अवरोध;
		हाल 5: slots = (1<<0) | (2<<4) | (3<<8) | (4<<12) | (5<<16); अवरोध;
		हाल 6: slots = (1<<0) | (2<<4) | (3<<8) | (4<<12) | (5<<16) | (6<<20); अवरोध;
		शेष: slots = 0; अवरोध;
		पूर्ण
	पूर्ण
	/* STOP index is never reached */
	outl(0xff000000 | slots, VIADEV_REG(viadev, OFFSET_STOP_IDX));
	udelay(20);
	snd_via82xx_codec_पढ़ोy(chip, 0);
	वापस 0;
पूर्ण

/*
 * prepare callback क्रम capture on via823x
 */
अटल पूर्णांक snd_via8233_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (via_lock_rate(&chip->rates[1], runसमय->rate) < 0)
		वापस -EINVAL;
	snd_ac97_set_rate(chip->ac97, AC97_PCM_LR_ADC_RATE, runसमय->rate);
	snd_via82xx_channel_reset(chip, viadev);
	snd_via82xx_set_table_ptr(chip, viadev);
	outb(VIA_REG_CAPTURE_FIFO_ENABLE, VIADEV_REG(viadev, OFS_CAPTURE_FIFO));
	outl((runसमय->क्रमmat == SNDRV_PCM_FORMAT_S16_LE ? VIA8233_REG_TYPE_16BIT : 0) |
	     (runसमय->channels > 1 ? VIA8233_REG_TYPE_STEREO : 0) |
	     0xff000000,    /* STOP index is never reached */
	     VIADEV_REG(viadev, OFFSET_STOP_IDX));
	udelay(20);
	snd_via82xx_codec_पढ़ोy(chip, 0);
	वापस 0;
पूर्ण


/*
 * pcm hardware definition, identical क्रम both playback and capture
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_via82xx_hw =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 /* SNDRV_PCM_INFO_RESUME | */
				 SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_48000,
	.rate_min =		48000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	VIA_MAX_बफ_मानE,
	.period_bytes_min =	32,
	.period_bytes_max =	VIA_MAX_बफ_मानE / 2,
	.periods_min =		2,
	.periods_max =		VIA_TABLE_SIZE / 2,
	.fअगरo_size =		0,
पूर्ण;


/*
 * खोलो callback skeleton
 */
अटल पूर्णांक snd_via82xx_pcm_खोलो(काष्ठा via82xx *chip, काष्ठा viadev *viadev,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;
	काष्ठा via_rate_lock *ratep;
	bool use_src = false;

	runसमय->hw = snd_via82xx_hw;
	
	/* set the hw rate condition */
	ratep = &chip->rates[viadev->direction];
	spin_lock_irq(&ratep->lock);
	ratep->used++;
	अगर (chip->spdअगर_on && viadev->reg_offset == 0x30) अणु
		/* DXS#3 and spdअगर is on */
		runसमय->hw.rates = chip->ac97->rates[AC97_RATES_SPDIF];
		snd_pcm_limit_hw_rates(runसमय);
	पूर्ण अन्यथा अगर (chip->dxs_fixed && viadev->reg_offset < 0x40) अणु
		/* fixed DXS playback rate */
		runसमय->hw.rates = SNDRV_PCM_RATE_48000;
		runसमय->hw.rate_min = runसमय->hw.rate_max = 48000;
	पूर्ण अन्यथा अगर (chip->dxs_src && viadev->reg_offset < 0x40) अणु
		/* use full SRC capabilities of DXS */
		runसमय->hw.rates = (SNDRV_PCM_RATE_CONTINUOUS |
				     SNDRV_PCM_RATE_8000_48000);
		runसमय->hw.rate_min = 8000;
		runसमय->hw.rate_max = 48000;
		use_src = true;
	पूर्ण अन्यथा अगर (! ratep->rate) अणु
		पूर्णांक idx = viadev->direction ? AC97_RATES_ADC : AC97_RATES_FRONT_DAC;
		runसमय->hw.rates = chip->ac97->rates[idx];
		snd_pcm_limit_hw_rates(runसमय);
	पूर्ण अन्यथा अणु
		/* a fixed rate */
		runसमय->hw.rates = SNDRV_PCM_RATE_KNOT;
		runसमय->hw.rate_max = runसमय->hw.rate_min = ratep->rate;
	पूर्ण
	spin_unlock_irq(&ratep->lock);

	/* we may हटाओ following स्थिरaपूर्णांक when we modअगरy table entries
	   in पूर्णांकerrupt */
	अगर ((err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;

	अगर (use_src) अणु
		err = snd_pcm_hw_rule_noresample(runसमय, 48000);
		अगर (err < 0)
			वापस err;
	पूर्ण

	runसमय->निजी_data = viadev;
	viadev->substream = substream;

	वापस 0;
पूर्ण


/*
 * खोलो callback क्रम playback on via686
 */
अटल पूर्णांक snd_via686_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = &chip->devs[chip->playback_devno + substream->number];
	पूर्णांक err;

	अगर ((err = snd_via82xx_pcm_खोलो(chip, viadev, substream)) < 0)
		वापस err;
	वापस 0;
पूर्ण

/*
 * खोलो callback क्रम playback on via823x DXS
 */
अटल पूर्णांक snd_via8233_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev;
	अचिन्हित पूर्णांक stream;
	पूर्णांक err;

	viadev = &chip->devs[chip->playback_devno + substream->number];
	अगर ((err = snd_via82xx_pcm_खोलो(chip, viadev, substream)) < 0)
		वापस err;
	stream = viadev->reg_offset / 0x10;
	अगर (chip->dxs_controls[stream]) अणु
		chip->playback_volume[stream][0] =
				VIA_DXS_MAX_VOLUME - (dxs_init_volume & 31);
		chip->playback_volume[stream][1] =
				VIA_DXS_MAX_VOLUME - (dxs_init_volume & 31);
		chip->dxs_controls[stream]->vd[0].access &=
			~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO,
			       &chip->dxs_controls[stream]->id);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * खोलो callback क्रम playback on via823x multi-channel
 */
अटल पूर्णांक snd_via8233_multi_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = &chip->devs[chip->multi_devno];
	पूर्णांक err;
	/* channels स्थिरraपूर्णांक क्रम VIA8233A
	 * 3 and 5 channels are not supported
	 */
	अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
		1, 2, 4, 6
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_channels = अणु
		.count = ARRAY_SIZE(channels),
		.list = channels,
		.mask = 0,
	पूर्ण;

	अगर ((err = snd_via82xx_pcm_खोलो(chip, viadev, substream)) < 0)
		वापस err;
	substream->runसमय->hw.channels_max = 6;
	अगर (chip->revision == VIA_REV_8233A)
		snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					   SNDRV_PCM_HW_PARAM_CHANNELS,
					   &hw_स्थिरraपूर्णांकs_channels);
	वापस 0;
पूर्ण

/*
 * खोलो callback क्रम capture on via686 and via823x
 */
अटल पूर्णांक snd_via82xx_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = &chip->devs[chip->capture_devno + substream->pcm->device];

	वापस snd_via82xx_pcm_खोलो(chip, viadev, substream);
पूर्ण

/*
 * बंद callback
 */
अटल पूर्णांक snd_via82xx_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	काष्ठा via_rate_lock *ratep;

	/* release the rate lock */
	ratep = &chip->rates[viadev->direction];
	spin_lock_irq(&ratep->lock);
	ratep->used--;
	अगर (! ratep->used)
		ratep->rate = 0;
	spin_unlock_irq(&ratep->lock);
	अगर (! ratep->rate) अणु
		अगर (! viadev->direction) अणु
			snd_ac97_update_घातer(chip->ac97,
					      AC97_PCM_FRONT_DAC_RATE, 0);
			snd_ac97_update_घातer(chip->ac97,
					      AC97_PCM_SURR_DAC_RATE, 0);
			snd_ac97_update_घातer(chip->ac97,
					      AC97_PCM_LFE_DAC_RATE, 0);
		पूर्ण अन्यथा
			snd_ac97_update_घातer(chip->ac97,
					      AC97_PCM_LR_ADC_RATE, 0);
	पूर्ण
	viadev->substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via8233_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा via82xx *chip = snd_pcm_substream_chip(substream);
	काष्ठा viadev *viadev = substream->runसमय->निजी_data;
	अचिन्हित पूर्णांक stream;

	stream = viadev->reg_offset / 0x10;
	अगर (chip->dxs_controls[stream]) अणु
		chip->dxs_controls[stream]->vd[0].access |=
			SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(chip->card, SNDRV_CTL_EVENT_MASK_INFO,
			       &chip->dxs_controls[stream]->id);
	पूर्ण
	वापस snd_via82xx_pcm_बंद(substream);
पूर्ण


/* via686 playback callbacks */
अटल स्थिर काष्ठा snd_pcm_ops snd_via686_playback_ops = अणु
	.खोलो =		snd_via686_playback_खोलो,
	.बंद =	snd_via82xx_pcm_बंद,
	.hw_params =	snd_via82xx_hw_params,
	.hw_मुक्त =	snd_via82xx_hw_मुक्त,
	.prepare =	snd_via686_playback_prepare,
	.trigger =	snd_via82xx_pcm_trigger,
	.poपूर्णांकer =	snd_via686_pcm_poपूर्णांकer,
पूर्ण;

/* via686 capture callbacks */
अटल स्थिर काष्ठा snd_pcm_ops snd_via686_capture_ops = अणु
	.खोलो =		snd_via82xx_capture_खोलो,
	.बंद =	snd_via82xx_pcm_बंद,
	.hw_params =	snd_via82xx_hw_params,
	.hw_मुक्त =	snd_via82xx_hw_मुक्त,
	.prepare =	snd_via686_capture_prepare,
	.trigger =	snd_via82xx_pcm_trigger,
	.poपूर्णांकer =	snd_via686_pcm_poपूर्णांकer,
पूर्ण;

/* via823x DSX playback callbacks */
अटल स्थिर काष्ठा snd_pcm_ops snd_via8233_playback_ops = अणु
	.खोलो =		snd_via8233_playback_खोलो,
	.बंद =	snd_via8233_playback_बंद,
	.hw_params =	snd_via82xx_hw_params,
	.hw_मुक्त =	snd_via82xx_hw_मुक्त,
	.prepare =	snd_via8233_playback_prepare,
	.trigger =	snd_via82xx_pcm_trigger,
	.poपूर्णांकer =	snd_via8233_pcm_poपूर्णांकer,
पूर्ण;

/* via823x multi-channel playback callbacks */
अटल स्थिर काष्ठा snd_pcm_ops snd_via8233_multi_ops = अणु
	.खोलो =		snd_via8233_multi_खोलो,
	.बंद =	snd_via82xx_pcm_बंद,
	.hw_params =	snd_via82xx_hw_params,
	.hw_मुक्त =	snd_via82xx_hw_मुक्त,
	.prepare =	snd_via8233_multi_prepare,
	.trigger =	snd_via82xx_pcm_trigger,
	.poपूर्णांकer =	snd_via8233_pcm_poपूर्णांकer,
पूर्ण;

/* via823x capture callbacks */
अटल स्थिर काष्ठा snd_pcm_ops snd_via8233_capture_ops = अणु
	.खोलो =		snd_via82xx_capture_खोलो,
	.बंद =	snd_via82xx_pcm_बंद,
	.hw_params =	snd_via82xx_hw_params,
	.hw_मुक्त =	snd_via82xx_hw_मुक्त,
	.prepare =	snd_via8233_capture_prepare,
	.trigger =	snd_via82xx_pcm_trigger,
	.poपूर्णांकer =	snd_via8233_pcm_poपूर्णांकer,
पूर्ण;


अटल व्योम init_viadev(काष्ठा via82xx *chip, पूर्णांक idx, अचिन्हित पूर्णांक reg_offset,
			पूर्णांक shaकरोw_pos, पूर्णांक direction)
अणु
	chip->devs[idx].reg_offset = reg_offset;
	chip->devs[idx].shaकरोw_shअगरt = shaकरोw_pos * 4;
	chip->devs[idx].direction = direction;
	chip->devs[idx].port = chip->port + reg_offset;
पूर्ण

/*
 * create pcm instances क्रम VIA8233, 8233C and 8235 (not 8233A)
 */
अटल पूर्णांक snd_via8233_pcm_new(काष्ठा via82xx *chip)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_chmap *chmap;
	पूर्णांक i, err;

	chip->playback_devno = 0;	/* x 4 */
	chip->multi_devno = 4;		/* x 1 */
	chip->capture_devno = 5;	/* x 2 */
	chip->num_devs = 7;
	chip->पूर्णांकr_mask = 0x33033333; /* FLAG|EOL क्रम rec0-1, mc, sdx0-3 */

	/* PCM #0:  4 DSX playbacks and 1 capture */
	err = snd_pcm_new(chip->card, chip->card->लघुname, 0, 4, 1, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via8233_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_via8233_capture_ops);
	pcm->निजी_data = chip;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcms[0] = pcm;
	/* set up playbacks */
	क्रम (i = 0; i < 4; i++)
		init_viadev(chip, i, 0x10 * i, i, 0);
	/* capture */
	init_viadev(chip, chip->capture_devno, VIA_REG_CAPTURE_8233_STATUS, 6, 1);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_बफ_मानE);

	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_std_chmaps, 2, 0,
				     &chmap);
	अगर (err < 0)
		वापस err;

	/* PCM #1:  multi-channel playback and 2nd capture */
	err = snd_pcm_new(chip->card, chip->card->लघुname, 1, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via8233_multi_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_via8233_capture_ops);
	pcm->निजी_data = chip;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcms[1] = pcm;
	/* set up playback */
	init_viadev(chip, chip->multi_devno, VIA_REG_MULTPLAY_STATUS, 4, 0);
	/* set up capture */
	init_viadev(chip, chip->capture_devno + 1, VIA_REG_CAPTURE_8233_STATUS + 0x10, 7, 1);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_बफ_मानE);

	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_alt_chmaps, 6, 0,
				     &chmap);
	अगर (err < 0)
		वापस err;
	chip->ac97->chmaps[SNDRV_PCM_STREAM_PLAYBACK] = chmap;

	वापस 0;
पूर्ण

/*
 * create pcm instances क्रम VIA8233A
 */
अटल पूर्णांक snd_via8233a_pcm_new(काष्ठा via82xx *chip)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_chmap *chmap;
	पूर्णांक err;

	chip->multi_devno = 0;
	chip->playback_devno = 1;
	chip->capture_devno = 2;
	chip->num_devs = 3;
	chip->पूर्णांकr_mask = 0x03033000; /* FLAG|EOL क्रम rec0, mc, sdx3 */

	/* PCM #0:  multi-channel playback and capture */
	err = snd_pcm_new(chip->card, chip->card->लघुname, 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via8233_multi_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_via8233_capture_ops);
	pcm->निजी_data = chip;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcms[0] = pcm;
	/* set up playback */
	init_viadev(chip, chip->multi_devno, VIA_REG_MULTPLAY_STATUS, 4, 0);
	/* capture */
	init_viadev(chip, chip->capture_devno, VIA_REG_CAPTURE_8233_STATUS, 6, 1);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_बफ_मानE);

	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_alt_chmaps, 6, 0,
				     &chmap);
	अगर (err < 0)
		वापस err;
	chip->ac97->chmaps[SNDRV_PCM_STREAM_PLAYBACK] = chmap;

	/* SPDIF supported? */
	अगर (! ac97_can_spdअगर(chip->ac97))
		वापस 0;

	/* PCM #1:  DXS3 playback (क्रम spdअगर) */
	err = snd_pcm_new(chip->card, chip->card->लघुname, 1, 1, 0, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via8233_playback_ops);
	pcm->निजी_data = chip;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcms[1] = pcm;
	/* set up playback */
	init_viadev(chip, chip->playback_devno, 0x30, 3, 0);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_बफ_मानE);
	वापस 0;
पूर्ण

/*
 * create a pcm instance क्रम via686a/b
 */
अटल पूर्णांक snd_via686_pcm_new(काष्ठा via82xx *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	chip->playback_devno = 0;
	chip->capture_devno = 1;
	chip->num_devs = 2;
	chip->पूर्णांकr_mask = 0x77; /* FLAG | EOL क्रम PB, CP, FM */

	err = snd_pcm_new(chip->card, chip->card->लघुname, 0, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_via686_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_via686_capture_ops);
	pcm->निजी_data = chip;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcms[0] = pcm;
	init_viadev(chip, 0, VIA_REG_PLAYBACK_STATUS, 0, 0);
	init_viadev(chip, 1, VIA_REG_CAPTURE_STATUS, 0, 1);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev,
				       64*1024, VIA_MAX_बफ_मानE);
	वापस 0;
पूर्ण


/*
 *  Mixer part
 */

अटल पूर्णांक snd_via8233_capture_source_info(काष्ठा snd_kcontrol *kcontrol,
					   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	/* क्रमmerly they were "Line" and "Mic", but it looks like that they
	 * have nothing to करो with the actual physical connections...
	 */
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु
		"Input1", "Input2"
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक snd_via8233_capture_source_get(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा via82xx *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ port = chip->port + (kcontrol->id.index ? (VIA_REG_CAPTURE_CHANNEL + 0x10) : VIA_REG_CAPTURE_CHANNEL);
	ucontrol->value.क्रमागतerated.item[0] = inb(port) & VIA_REG_CAPTURE_CHANNEL_MIC ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via8233_capture_source_put(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा via82xx *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ port = chip->port + (kcontrol->id.index ? (VIA_REG_CAPTURE_CHANNEL + 0x10) : VIA_REG_CAPTURE_CHANNEL);
	u8 val, oval;

	spin_lock_irq(&chip->reg_lock);
	oval = inb(port);
	val = oval & ~VIA_REG_CAPTURE_CHANNEL_MIC;
	अगर (ucontrol->value.क्रमागतerated.item[0])
		val |= VIA_REG_CAPTURE_CHANNEL_MIC;
	अगर (val != oval)
		outb(val, port);
	spin_unlock_irq(&chip->reg_lock);
	वापस val != oval;
पूर्ण

अटल काष्ठा snd_kcontrol_new snd_via8233_capture_source = अणु
	.name = "Input Source Select",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = snd_via8233_capture_source_info,
	.get = snd_via8233_capture_source_get,
	.put = snd_via8233_capture_source_put,
पूर्ण;

#घोषणा snd_via8233_dxs3_spdअगर_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_via8233_dxs3_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा via82xx *chip = snd_kcontrol_chip(kcontrol);
	u8 val;

	pci_पढ़ो_config_byte(chip->pci, VIA8233_SPDIF_CTRL, &val);
	ucontrol->value.पूर्णांकeger.value[0] = (val & VIA8233_SPDIF_DX3) ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via8233_dxs3_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा via82xx *chip = snd_kcontrol_chip(kcontrol);
	u8 val, oval;

	pci_पढ़ो_config_byte(chip->pci, VIA8233_SPDIF_CTRL, &oval);
	val = oval & ~VIA8233_SPDIF_DX3;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= VIA8233_SPDIF_DX3;
	/* save the spdअगर flag क्रम rate filtering */
	chip->spdअगर_on = ucontrol->value.पूर्णांकeger.value[0] ? 1 : 0;
	अगर (val != oval) अणु
		pci_ग_लिखो_config_byte(chip->pci, VIA8233_SPDIF_CTRL, val);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_via8233_dxs3_spdअगर_control = अणु
	.name = SNDRV_CTL_NAME_IEC958("Output ",NONE,SWITCH),
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = snd_via8233_dxs3_spdअगर_info,
	.get = snd_via8233_dxs3_spdअगर_get,
	.put = snd_via8233_dxs3_spdअगर_put,
पूर्ण;

अटल पूर्णांक snd_via8233_dxs_volume_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = VIA_DXS_MAX_VOLUME;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via8233_dxs_volume_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा via82xx *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = kcontrol->id.subdevice;

	ucontrol->value.पूर्णांकeger.value[0] = VIA_DXS_MAX_VOLUME - chip->playback_volume[idx][0];
	ucontrol->value.पूर्णांकeger.value[1] = VIA_DXS_MAX_VOLUME - chip->playback_volume[idx][1];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via8233_pcmdxs_volume_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा via82xx *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = VIA_DXS_MAX_VOLUME - chip->playback_volume_c[0];
	ucontrol->value.पूर्णांकeger.value[1] = VIA_DXS_MAX_VOLUME - chip->playback_volume_c[1];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via8233_dxs_volume_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा via82xx *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx = kcontrol->id.subdevice;
	अचिन्हित दीर्घ port = chip->port + 0x10 * idx;
	अचिन्हित अक्षर val;
	पूर्णांक i, change = 0;

	क्रम (i = 0; i < 2; i++) अणु
		val = ucontrol->value.पूर्णांकeger.value[i];
		अगर (val > VIA_DXS_MAX_VOLUME)
			val = VIA_DXS_MAX_VOLUME;
		val = VIA_DXS_MAX_VOLUME - val;
		change |= val != chip->playback_volume[idx][i];
		अगर (change) अणु
			chip->playback_volume[idx][i] = val;
			outb(val, port + VIA_REG_OFS_PLAYBACK_VOLUME_L + i);
		पूर्ण
	पूर्ण
	वापस change;
पूर्ण

अटल पूर्णांक snd_via8233_pcmdxs_volume_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा via82xx *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक idx;
	अचिन्हित अक्षर val;
	पूर्णांक i, change = 0;

	क्रम (i = 0; i < 2; i++) अणु
		val = ucontrol->value.पूर्णांकeger.value[i];
		अगर (val > VIA_DXS_MAX_VOLUME)
			val = VIA_DXS_MAX_VOLUME;
		val = VIA_DXS_MAX_VOLUME - val;
		अगर (val != chip->playback_volume_c[i]) अणु
			change = 1;
			chip->playback_volume_c[i] = val;
			क्रम (idx = 0; idx < 4; idx++) अणु
				अचिन्हित दीर्घ port = chip->port + 0x10 * idx;
				chip->playback_volume[idx][i] = val;
				outb(val, port + VIA_REG_OFS_PLAYBACK_VOLUME_L + i);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_dxs, -4650, 150, 1);

अटल स्थिर काष्ठा snd_kcontrol_new snd_via8233_pcmdxs_volume_control = अणु
	.name = "PCM Playback Volume",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.info = snd_via8233_dxs_volume_info,
	.get = snd_via8233_pcmdxs_volume_get,
	.put = snd_via8233_pcmdxs_volume_put,
	.tlv = अणु .p = db_scale_dxs पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_via8233_dxs_volume_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.device = 0,
	/* .subdevice set later */
	.name = "PCM Playback Volume",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
		  SNDRV_CTL_ELEM_ACCESS_TLV_READ |
		  SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.info = snd_via8233_dxs_volume_info,
	.get = snd_via8233_dxs_volume_get,
	.put = snd_via8233_dxs_volume_put,
	.tlv = अणु .p = db_scale_dxs पूर्ण
पूर्ण;

/*
 */

अटल व्योम snd_via82xx_mixer_मुक्त_ac97_bus(काष्ठा snd_ac97_bus *bus)
अणु
	काष्ठा via82xx *chip = bus->निजी_data;
	chip->ac97_bus = शून्य;
पूर्ण

अटल व्योम snd_via82xx_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा via82xx *chip = ac97->निजी_data;
	chip->ac97 = शून्य;
पूर्ण

अटल स्थिर काष्ठा ac97_quirk ac97_quirks[] = अणु
	अणु
		.subvenकरोr = 0x1106,
		.subdevice = 0x4161,
		.codec_id = 0x56494161, /* VT1612A */
		.name = "Soltek SL-75DRV5",
		.type = AC97_TUNE_NONE
	पूर्ण,
	अणु	/* FIXME: which codec? */
		.subvenकरोr = 0x1106,
		.subdevice = 0x4161,
		.name = "ASRock K7VT2",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x110a,
		.subdevice = 0x0079,
		.name = "Fujitsu Siemens D1289",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1019,
		.subdevice = 0x0a81,
		.name = "ECS K7VTA3",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1019,
		.subdevice = 0x0a85,
		.name = "ECS L7VMM2",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1019,
		.subdevice = 0x1841,
		.name = "ECS K7VTA3",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु
		.subvenकरोr = 0x1849,
		.subdevice = 0x3059,
		.name = "ASRock K7VM2",
		.type = AC97_TUNE_HP_ONLY	/* VT1616 */
	पूर्ण,
	अणु
		.subvenकरोr = 0x14cd,
		.subdevice = 0x7002,
		.name = "Unknown",
		.type = AC97_TUNE_ALC_JACK
	पूर्ण,
	अणु
		.subvenकरोr = 0x1071,
		.subdevice = 0x8590,
		.name = "Mitac Mobo",
		.type = AC97_TUNE_ALC_JACK
	पूर्ण,
	अणु
		.subvenकरोr = 0x161f,
		.subdevice = 0x202b,
		.name = "Arima Notebook",
		.type = AC97_TUNE_HP_ONLY,
	पूर्ण,
	अणु
		.subvenकरोr = 0x161f,
		.subdevice = 0x2032,
		.name = "Targa Traveller 811",
		.type = AC97_TUNE_HP_ONLY,
	पूर्ण,
	अणु
		.subvenकरोr = 0x161f,
		.subdevice = 0x2032,
		.name = "m680x",
		.type = AC97_TUNE_HP_ONLY, /* http://launchpad.net/bugs/38546 */
	पूर्ण,
	अणु
		.subvenकरोr = 0x1297,
		.subdevice = 0xa232,
		.name = "Shuttle AK32VN",
		.type = AC97_TUNE_HP_ONLY
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;

अटल पूर्णांक snd_via82xx_mixer_new(काष्ठा via82xx *chip, स्थिर अक्षर *quirk_override)
अणु
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_via82xx_codec_ग_लिखो,
		.पढ़ो = snd_via82xx_codec_पढ़ो,
		.रुको = snd_via82xx_codec_रुको,
	पूर्ण;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, chip, &chip->ac97_bus)) < 0)
		वापस err;
	chip->ac97_bus->निजी_मुक्त = snd_via82xx_mixer_मुक्त_ac97_bus;
	chip->ac97_bus->घड़ी = chip->ac97_घड़ी;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.निजी_मुक्त = snd_via82xx_mixer_मुक्त_ac97;
	ac97.pci = chip->pci;
	ac97.scaps = AC97_SCAP_SKIP_MODEM | AC97_SCAP_POWER_SAVE;
	अगर ((err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97)) < 0)
		वापस err;

	snd_ac97_tune_hardware(chip->ac97, ac97_quirks, quirk_override);

	अगर (chip->chip_type != TYPE_VIA686) अणु
		/* use slot 10/11 */
		snd_ac97_update_bits(chip->ac97, AC97_EXTENDED_STATUS, 0x03 << 4, 0x03 << 4);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित SUPPORT_JOYSTICK
#घोषणा JOYSTICK_ADDR	0x200
अटल पूर्णांक snd_via686_create_gameport(काष्ठा via82xx *chip, अचिन्हित अक्षर *legacy)
अणु
	काष्ठा gameport *gp;
	काष्ठा resource *r;

	अगर (!joystick)
		वापस -ENODEV;

	r = request_region(JOYSTICK_ADDR, 8, "VIA686 gameport");
	अगर (!r) अणु
		dev_warn(chip->card->dev, "cannot reserve joystick port %#x\n",
		       JOYSTICK_ADDR);
		वापस -EBUSY;
	पूर्ण

	chip->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(chip->card->dev,
			"cannot allocate memory for gameport\n");
		release_and_मुक्त_resource(r);
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "VIA686 Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(chip->pci));
	gameport_set_dev_parent(gp, &chip->pci->dev);
	gp->io = JOYSTICK_ADDR;
	gameport_set_port_data(gp, r);

	/* Enable legacy joystick port */
	*legacy |= VIA_FUNC_ENABLE_GAME;
	pci_ग_लिखो_config_byte(chip->pci, VIA_FUNC_ENABLE, *legacy);

	gameport_रेजिस्टर_port(chip->gameport);

	वापस 0;
पूर्ण

अटल व्योम snd_via686_मुक्त_gameport(काष्ठा via82xx *chip)
अणु
	अगर (chip->gameport) अणु
		काष्ठा resource *r = gameport_get_port_data(chip->gameport);

		gameport_unरेजिस्टर_port(chip->gameport);
		chip->gameport = शून्य;
		release_and_मुक्त_resource(r);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_via686_create_gameport(काष्ठा via82xx *chip, अचिन्हित अक्षर *legacy)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत व्योम snd_via686_मुक्त_gameport(काष्ठा via82xx *chip) अणु पूर्ण
#पूर्ण_अगर


/*
 *
 */

अटल पूर्णांक snd_via8233_init_misc(काष्ठा via82xx *chip)
अणु
	पूर्णांक i, err, caps;
	अचिन्हित अक्षर val;

	caps = chip->chip_type == TYPE_VIA8233A ? 1 : 2;
	क्रम (i = 0; i < caps; i++) अणु
		snd_via8233_capture_source.index = i;
		err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_via8233_capture_source, chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (ac97_can_spdअगर(chip->ac97)) अणु
		err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_via8233_dxs3_spdअगर_control, chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (chip->chip_type != TYPE_VIA8233A) अणु
		/* when no h/w PCM volume control is found, use DXS volume control
		 * as the PCM vol control
		 */
		काष्ठा snd_ctl_elem_id sid;
		स_रखो(&sid, 0, माप(sid));
		म_नकल(sid.name, "PCM Playback Volume");
		sid.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
		अगर (! snd_ctl_find_id(chip->card, &sid)) अणु
			dev_info(chip->card->dev,
				 "Using DXS as PCM Playback\n");
			err = snd_ctl_add(chip->card, snd_ctl_new1(&snd_via8233_pcmdxs_volume_control, chip));
			अगर (err < 0)
				वापस err;
		पूर्ण
		अन्यथा /* Using DXS when PCM emulation is enabled is really weird */
		अणु
			क्रम (i = 0; i < 4; ++i) अणु
				काष्ठा snd_kcontrol *kctl;

				kctl = snd_ctl_new1(
					&snd_via8233_dxs_volume_control, chip);
				अगर (!kctl)
					वापस -ENOMEM;
				kctl->id.subdevice = i;
				err = snd_ctl_add(chip->card, kctl);
				अगर (err < 0)
					वापस err;
				chip->dxs_controls[i] = kctl;
			पूर्ण
		पूर्ण
	पूर्ण
	/* select spdअगर data slot 10/11 */
	pci_पढ़ो_config_byte(chip->pci, VIA8233_SPDIF_CTRL, &val);
	val = (val & ~VIA8233_SPDIF_SLOT_MASK) | VIA8233_SPDIF_SLOT_1011;
	val &= ~VIA8233_SPDIF_DX3; /* SPDIF off as शेष */
	pci_ग_लिखो_config_byte(chip->pci, VIA8233_SPDIF_CTRL, val);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_via686_init_misc(काष्ठा via82xx *chip)
अणु
	अचिन्हित अक्षर legacy, legacy_cfg;
	पूर्णांक rev_h = 0;

	legacy = chip->old_legacy;
	legacy_cfg = chip->old_legacy_cfg;
	legacy |= VIA_FUNC_MIDI_IRQMASK;	/* FIXME: correct? (disable MIDI) */
	legacy &= ~VIA_FUNC_ENABLE_GAME;	/* disable joystick */
	अगर (chip->revision >= VIA_REV_686_H) अणु
		rev_h = 1;
		अगर (mpu_port >= 0x200) अणु	/* क्रमce MIDI */
			mpu_port &= 0xfffc;
			pci_ग_लिखो_config_dword(chip->pci, 0x18, mpu_port | 0x01);
#अगर_घोषित CONFIG_PM_SLEEP
			chip->mpu_port_saved = mpu_port;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			mpu_port = pci_resource_start(chip->pci, 2);
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (mpu_port) अणु	/* क्रमce MIDI */
		हाल 0x300:
		हाल 0x310:
		हाल 0x320:
		हाल 0x330:
			legacy_cfg &= ~(3 << 2);
			legacy_cfg |= (mpu_port & 0x0030) >> 2;
			अवरोध;
		शेष:			/* no, use BIOS settings */
			अगर (legacy & VIA_FUNC_ENABLE_MIDI)
				mpu_port = 0x300 + ((legacy_cfg & 0x000c) << 2);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (mpu_port >= 0x200 &&
	    (chip->mpu_res = request_region(mpu_port, 2, "VIA82xx MPU401"))
	    != शून्य) अणु
		अगर (rev_h)
			legacy |= VIA_FUNC_MIDI_PNP;	/* enable PCI I/O 2 */
		legacy |= VIA_FUNC_ENABLE_MIDI;
	पूर्ण अन्यथा अणु
		अगर (rev_h)
			legacy &= ~VIA_FUNC_MIDI_PNP;	/* disable PCI I/O 2 */
		legacy &= ~VIA_FUNC_ENABLE_MIDI;
		mpu_port = 0;
	पूर्ण

	pci_ग_लिखो_config_byte(chip->pci, VIA_FUNC_ENABLE, legacy);
	pci_ग_लिखो_config_byte(chip->pci, VIA_PNP_CONTROL, legacy_cfg);
	अगर (chip->mpu_res) अणु
		अगर (snd_mpu401_uart_new(chip->card, 0, MPU401_HW_VIA686A,
					mpu_port, MPU401_INFO_INTEGRATED |
					MPU401_INFO_IRQ_HOOK, -1,
					&chip->rmidi) < 0) अणु
			dev_warn(chip->card->dev,
				 "unable to initialize MPU-401 at 0x%lx, skipping\n",
				 mpu_port);
			legacy &= ~VIA_FUNC_ENABLE_MIDI;
		पूर्ण अन्यथा अणु
			legacy &= ~VIA_FUNC_MIDI_IRQMASK;	/* enable MIDI पूर्णांकerrupt */
		पूर्ण
		pci_ग_लिखो_config_byte(chip->pci, VIA_FUNC_ENABLE, legacy);
	पूर्ण

	snd_via686_create_gameport(chip, &legacy);

#अगर_घोषित CONFIG_PM_SLEEP
	chip->legacy_saved = legacy;
	chip->legacy_cfg_saved = legacy_cfg;
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 * proc पूर्णांकerface
 */
अटल व्योम snd_via82xx_proc_पढ़ो(काष्ठा snd_info_entry *entry,
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा via82xx *chip = entry->निजी_data;
	पूर्णांक i;
	
	snd_iम_लिखो(buffer, "%s\n\n", chip->card->दीर्घname);
	क्रम (i = 0; i < 0xa0; i += 4) अणु
		snd_iम_लिखो(buffer, "%02x: %08x\n", i, inl(chip->port + i));
	पूर्ण
पूर्ण

अटल व्योम snd_via82xx_proc_init(काष्ठा via82xx *chip)
अणु
	snd_card_ro_proc_new(chip->card, "via82xx", chip,
			     snd_via82xx_proc_पढ़ो);
पूर्ण

/*
 *
 */

अटल पूर्णांक snd_via82xx_chip_init(काष्ठा via82xx *chip)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ end_समय;
	अचिन्हित अक्षर pval;

#अगर 0 /* broken on K7M? */
	अगर (chip->chip_type == TYPE_VIA686)
		/* disable all legacy ports */
		pci_ग_लिखो_config_byte(chip->pci, VIA_FUNC_ENABLE, 0);
#पूर्ण_अगर
	pci_पढ़ो_config_byte(chip->pci, VIA_ACLINK_STAT, &pval);
	अगर (! (pval & VIA_ACLINK_C00_READY)) अणु /* codec not पढ़ोy? */
		/* deनिश्चित ACLink reset, क्रमce SYNC */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL,
				      VIA_ACLINK_CTRL_ENABLE |
				      VIA_ACLINK_CTRL_RESET |
				      VIA_ACLINK_CTRL_SYNC);
		udelay(100);
#अगर 1 /* FIXME: should we करो full reset here क्रम all chip models? */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL, 0x00);
		udelay(100);
#अन्यथा
		/* deनिश्चित ACLink reset, क्रमce SYNC (warm AC'97 reset) */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL,
				      VIA_ACLINK_CTRL_RESET|VIA_ACLINK_CTRL_SYNC);
		udelay(2);
#पूर्ण_अगर
		/* ACLink on, deनिश्चित ACLink reset, VSR, SGD data out */
		/* note - FM data out has trouble with non VRA codecs !! */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL, VIA_ACLINK_CTRL_INIT);
		udelay(100);
	पूर्ण
	
	/* Make sure VRA is enabled, in हाल we didn't करो a
	 * complete codec reset, above */
	pci_पढ़ो_config_byte(chip->pci, VIA_ACLINK_CTRL, &pval);
	अगर ((pval & VIA_ACLINK_CTRL_INIT) != VIA_ACLINK_CTRL_INIT) अणु
		/* ACLink on, deनिश्चित ACLink reset, VSR, SGD data out */
		/* note - FM data out has trouble with non VRA codecs !! */
		pci_ग_लिखो_config_byte(chip->pci, VIA_ACLINK_CTRL, VIA_ACLINK_CTRL_INIT);
		udelay(100);
	पूर्ण

	/* रुको until codec पढ़ोy */
	end_समय = jअगरfies + msecs_to_jअगरfies(750);
	करो अणु
		pci_पढ़ो_config_byte(chip->pci, VIA_ACLINK_STAT, &pval);
		अगर (pval & VIA_ACLINK_C00_READY) /* primary codec पढ़ोy */
			अवरोध;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));

	अगर ((val = snd_via82xx_codec_xपढ़ो(chip)) & VIA_REG_AC97_BUSY)
		dev_err(chip->card->dev,
			"AC'97 codec is not ready [0x%x]\n", val);

#अगर 0 /* FIXME: we करोn't support the second codec yet so skip the detection now.. */
	snd_via82xx_codec_xग_लिखो(chip, VIA_REG_AC97_READ |
				 VIA_REG_AC97_SECONDARY_VALID |
				 (VIA_REG_AC97_CODEC_ID_SECONDARY << VIA_REG_AC97_CODEC_ID_SHIFT));
	end_समय = jअगरfies + msecs_to_jअगरfies(750);
	snd_via82xx_codec_xग_लिखो(chip, VIA_REG_AC97_READ |
				 VIA_REG_AC97_SECONDARY_VALID |
				 (VIA_REG_AC97_CODEC_ID_SECONDARY << VIA_REG_AC97_CODEC_ID_SHIFT));
	करो अणु
		अगर ((val = snd_via82xx_codec_xपढ़ो(chip)) & VIA_REG_AC97_SECONDARY_VALID) अणु
			chip->ac97_secondary = 1;
			जाओ __ac97_ok2;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));
	/* This is ok, the most of motherboards have only one codec */

      __ac97_ok2:
#पूर्ण_अगर

	अगर (chip->chip_type == TYPE_VIA686) अणु
		/* route FM trap to IRQ, disable FM trap */
		pci_ग_लिखो_config_byte(chip->pci, VIA_FM_NMI_CTRL, 0);
		/* disable all GPI पूर्णांकerrupts */
		outl(0, VIAREG(chip, GPI_INTR));
	पूर्ण

	अगर (chip->chip_type != TYPE_VIA686) अणु
		/* Workaround क्रम Award BIOS bug:
		 * DXS channels करोn't work properly with VRA अगर MC97 is disabled.
		 */
		काष्ठा pci_dev *pci;
		pci = pci_get_device(0x1106, 0x3068, शून्य); /* MC97 */
		अगर (pci) अणु
			अचिन्हित अक्षर data;
			pci_पढ़ो_config_byte(pci, 0x44, &data);
			pci_ग_लिखो_config_byte(pci, 0x44, data | 0x40);
			pci_dev_put(pci);
		पूर्ण
	पूर्ण

	अगर (chip->chip_type != TYPE_VIA8233A) अणु
		पूर्णांक i, idx;
		क्रम (idx = 0; idx < 4; idx++) अणु
			अचिन्हित दीर्घ port = chip->port + 0x10 * idx;
			क्रम (i = 0; i < 2; i++) अणु
				chip->playback_volume[idx][i]=chip->playback_volume_c[i];
				outb(chip->playback_volume_c[i],
				     port + VIA_REG_OFS_PLAYBACK_VOLUME_L + i);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * घातer management
 */
अटल पूर्णांक snd_via82xx_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा via82xx *chip = card->निजी_data;
	पूर्णांक i;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	क्रम (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);
	snd_ac97_suspend(chip->ac97);

	/* save misc values */
	अगर (chip->chip_type != TYPE_VIA686) अणु
		pci_पढ़ो_config_byte(chip->pci, VIA8233_SPDIF_CTRL, &chip->spdअगर_ctrl_saved);
		chip->capture_src_saved[0] = inb(chip->port + VIA_REG_CAPTURE_CHANNEL);
		chip->capture_src_saved[1] = inb(chip->port + VIA_REG_CAPTURE_CHANNEL + 0x10);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_via82xx_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा via82xx *chip = card->निजी_data;
	पूर्णांक i;

	snd_via82xx_chip_init(chip);

	अगर (chip->chip_type == TYPE_VIA686) अणु
		अगर (chip->mpu_port_saved)
			pci_ग_लिखो_config_dword(chip->pci, 0x18, chip->mpu_port_saved | 0x01);
		pci_ग_लिखो_config_byte(chip->pci, VIA_FUNC_ENABLE, chip->legacy_saved);
		pci_ग_लिखो_config_byte(chip->pci, VIA_PNP_CONTROL, chip->legacy_cfg_saved);
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_config_byte(chip->pci, VIA8233_SPDIF_CTRL, chip->spdअगर_ctrl_saved);
		outb(chip->capture_src_saved[0], chip->port + VIA_REG_CAPTURE_CHANNEL);
		outb(chip->capture_src_saved[1], chip->port + VIA_REG_CAPTURE_CHANNEL + 0x10);
	पूर्ण

	snd_ac97_resume(chip->ac97);

	क्रम (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_via82xx_pm, snd_via82xx_suspend, snd_via82xx_resume);
#घोषणा SND_VIA82XX_PM_OPS	&snd_via82xx_pm
#अन्यथा
#घोषणा SND_VIA82XX_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक snd_via82xx_मुक्त(काष्ठा via82xx *chip)
अणु
	अचिन्हित पूर्णांक i;

	अगर (chip->irq < 0)
		जाओ __end_hw;
	/* disable पूर्णांकerrupts */
	क्रम (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
 __end_hw:
	release_and_मुक्त_resource(chip->mpu_res);
	pci_release_regions(chip->pci);

	अगर (chip->chip_type == TYPE_VIA686) अणु
		snd_via686_मुक्त_gameport(chip);
		pci_ग_लिखो_config_byte(chip->pci, VIA_FUNC_ENABLE, chip->old_legacy);
		pci_ग_लिखो_config_byte(chip->pci, VIA_PNP_CONTROL, chip->old_legacy_cfg);
	पूर्ण
	pci_disable_device(chip->pci);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_via82xx_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा via82xx *chip = device->device_data;
	वापस snd_via82xx_मुक्त(chip);
पूर्ण

अटल पूर्णांक snd_via82xx_create(काष्ठा snd_card *card,
			      काष्ठा pci_dev *pci,
			      पूर्णांक chip_type,
			      पूर्णांक revision,
			      अचिन्हित पूर्णांक ac97_घड़ी,
			      काष्ठा via82xx **r_via)
अणु
	काष्ठा via82xx *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_via82xx_dev_मुक्त,
        पूर्ण;

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	अगर ((chip = kzalloc(माप(*chip), GFP_KERNEL)) == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	chip->chip_type = chip_type;
	chip->revision = revision;

	spin_lock_init(&chip->reg_lock);
	spin_lock_init(&chip->rates[0].lock);
	spin_lock_init(&chip->rates[1].lock);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;

	pci_पढ़ो_config_byte(pci, VIA_FUNC_ENABLE, &chip->old_legacy);
	pci_पढ़ो_config_byte(pci, VIA_PNP_CONTROL, &chip->old_legacy_cfg);
	pci_ग_लिखो_config_byte(chip->pci, VIA_FUNC_ENABLE,
			      chip->old_legacy & ~(VIA_FUNC_ENABLE_SB|VIA_FUNC_ENABLE_FM));

	अगर ((err = pci_request_regions(pci, card->driver)) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	chip->port = pci_resource_start(pci, 0);
	अगर (request_irq(pci->irq,
			chip_type == TYPE_VIA8233 ?
			snd_via8233_पूर्णांकerrupt :	snd_via686_पूर्णांकerrupt,
			IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_via82xx_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	अगर (ac97_घड़ी >= 8000 && ac97_घड़ी <= 48000)
		chip->ac97_घड़ी = ac97_घड़ी;

	अगर ((err = snd_via82xx_chip_init(chip)) < 0) अणु
		snd_via82xx_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_via82xx_मुक्त(chip);
		वापस err;
	पूर्ण

	/* The 8233 ac97 controller करोes not implement the master bit
	 * in the pci command रेजिस्टर. IMHO this is a violation of the PCI spec.
	 * We call pci_set_master here because it करोes not hurt. */
	pci_set_master(pci);

	*r_via = chip;
	वापस 0;
पूर्ण

काष्ठा via823x_info अणु
	पूर्णांक revision;
	अक्षर *name;
	पूर्णांक type;
पूर्ण;
अटल स्थिर काष्ठा via823x_info via823x_cards[] = अणु
	अणु VIA_REV_PRE_8233, "VIA 8233-Pre", TYPE_VIA8233 पूर्ण,
	अणु VIA_REV_8233C, "VIA 8233C", TYPE_VIA8233 पूर्ण,
	अणु VIA_REV_8233, "VIA 8233", TYPE_VIA8233 पूर्ण,
	अणु VIA_REV_8233A, "VIA 8233A", TYPE_VIA8233A पूर्ण,
	अणु VIA_REV_8235, "VIA 8235", TYPE_VIA8233 पूर्ण,
	अणु VIA_REV_8237, "VIA 8237", TYPE_VIA8233 पूर्ण,
	अणु VIA_REV_8251, "VIA 8251", TYPE_VIA8233 पूर्ण,
पूर्ण;

/*
 * स्वतः detection of DXS channel supports.
 */

अटल स्थिर काष्ठा snd_pci_quirk dxs_allowlist[] = अणु
	SND_PCI_QUIRK(0x1005, 0x4710, "Avance Logic Mobo", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x1019, 0x0996, "ESC Mobo", VIA_DXS_48K),
	SND_PCI_QUIRK(0x1019, 0x0a81, "ECS K7VTA3 v8.0", VIA_DXS_NO_VRA),
	SND_PCI_QUIRK(0x1019, 0x0a85, "ECS L7VMM2", VIA_DXS_NO_VRA),
	SND_PCI_QUIRK_VENDOR(0x1019, "ESC K8", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1019, 0xaa01, "ESC K8T890-A", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1025, 0x0033, "Acer Inspire 1353LM", VIA_DXS_NO_VRA),
	SND_PCI_QUIRK(0x1025, 0x0046, "Acer Aspire 1524 WLMi", VIA_DXS_SRC),
	SND_PCI_QUIRK_VENDOR(0x1043, "ASUS A7/A8", VIA_DXS_NO_VRA),
	SND_PCI_QUIRK_VENDOR(0x1071, "Diverse Notebook", VIA_DXS_NO_VRA),
	SND_PCI_QUIRK(0x10cf, 0x118e, "FSC Laptop", VIA_DXS_ENABLE),
	SND_PCI_QUIRK_VENDOR(0x1106, "ASRock", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1297, 0xa231, "Shuttle AK31v2", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1297, 0xa232, "Shuttle", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1297, 0xc160, "Shuttle Sk41G", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1458, 0xa002, "Gigabyte GA-7VAXP", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x1462, 0x3800, "MSI KT266", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x1462, 0x7120, "MSI KT4V", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x1462, 0x7142, "MSI K8MM-V", VIA_DXS_ENABLE),
	SND_PCI_QUIRK_VENDOR(0x1462, "MSI Mobo", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x147b, 0x1401, "ABIT KD7(-RAID)", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x147b, 0x1411, "ABIT VA-20", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x147b, 0x1413, "ABIT KV8 Pro", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x147b, 0x1415, "ABIT AV8", VIA_DXS_NO_VRA),
	SND_PCI_QUIRK(0x14ff, 0x0403, "Twinhead mobo", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x14ff, 0x0408, "Twinhead laptop", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1558, 0x4701, "Clevo D470", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1584, 0x8120, "Diverse Laptop", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x1584, 0x8123, "Targa/Uniwill", VIA_DXS_NO_VRA),
	SND_PCI_QUIRK(0x161f, 0x202b, "Amira Notebook", VIA_DXS_NO_VRA),
	SND_PCI_QUIRK(0x161f, 0x2032, "m680x machines", VIA_DXS_48K),
	SND_PCI_QUIRK(0x1631, 0xe004, "PB EasyNote 3174", VIA_DXS_ENABLE),
	SND_PCI_QUIRK(0x1695, 0x3005, "EPoX EP-8K9A", VIA_DXS_ENABLE),
	SND_PCI_QUIRK_VENDOR(0x1695, "EPoX mobo", VIA_DXS_SRC),
	SND_PCI_QUIRK_VENDOR(0x16f3, "Jetway K8", VIA_DXS_SRC),
	SND_PCI_QUIRK_VENDOR(0x1734, "FSC Laptop", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1849, 0x3059, "ASRock K7VM2", VIA_DXS_NO_VRA),
	SND_PCI_QUIRK_VENDOR(0x1849, "ASRock mobo", VIA_DXS_SRC),
	SND_PCI_QUIRK(0x1919, 0x200a, "Soltek SL-K8",  VIA_DXS_NO_VRA),
	SND_PCI_QUIRK(0x4005, 0x4710, "MSI K7T266", VIA_DXS_SRC),
	अणु पूर्ण /* terminator */
पूर्ण;

अटल पूर्णांक check_dxs_list(काष्ठा pci_dev *pci, पूर्णांक revision)
अणु
	स्थिर काष्ठा snd_pci_quirk *w;

	w = snd_pci_quirk_lookup(pci, dxs_allowlist);
	अगर (w) अणु
		dev_dbg(&pci->dev, "DXS allow list for %s found\n",
			    snd_pci_quirk_name(w));
		वापस w->value;
	पूर्ण

	/* क्रम newer revision, शेष to DXS_SRC */
	अगर (revision >= VIA_REV_8235)
		वापस VIA_DXS_SRC;

	/*
	 * not detected, try 48k rate only to be sure.
	 */
	dev_info(&pci->dev, "Assuming DXS channels with 48k fixed sample rate.\n");
	dev_info(&pci->dev, "         Please try dxs_support=5 option\n");
	dev_info(&pci->dev, "         and report if it works on your machine.\n");
	dev_info(&pci->dev, "         For more details, read ALSA-Configuration.txt.\n");
	वापस VIA_DXS_48K;
पूर्ण;

अटल पूर्णांक snd_via82xx_probe(काष्ठा pci_dev *pci,
			     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा snd_card *card;
	काष्ठा via82xx *chip;
	पूर्णांक chip_type = 0, card_type;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	err = snd_card_new(&pci->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	card_type = pci_id->driver_data;
	चयन (card_type) अणु
	हाल TYPE_CARD_VIA686:
		म_नकल(card->driver, "VIA686A");
		प्र_लिखो(card->लघुname, "VIA 82C686A/B rev%x", pci->revision);
		chip_type = TYPE_VIA686;
		अवरोध;
	हाल TYPE_CARD_VIA8233:
		chip_type = TYPE_VIA8233;
		प्र_लिखो(card->लघुname, "VIA 823x rev%x", pci->revision);
		क्रम (i = 0; i < ARRAY_SIZE(via823x_cards); i++) अणु
			अगर (pci->revision == via823x_cards[i].revision) अणु
				chip_type = via823x_cards[i].type;
				म_नकल(card->लघुname, via823x_cards[i].name);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (chip_type != TYPE_VIA8233A) अणु
			अगर (dxs_support == VIA_DXS_AUTO)
				dxs_support = check_dxs_list(pci, pci->revision);
			/* क्रमce to use VIA8233 or 8233A model according to
			 * dxs_support module option
			 */
			अगर (dxs_support == VIA_DXS_DISABLE)
				chip_type = TYPE_VIA8233A;
			अन्यथा
				chip_type = TYPE_VIA8233;
		पूर्ण
		अगर (chip_type == TYPE_VIA8233A)
			म_नकल(card->driver, "VIA8233A");
		अन्यथा अगर (pci->revision >= VIA_REV_8237)
			म_नकल(card->driver, "VIA8237"); /* no slog assignment */
		अन्यथा
			म_नकल(card->driver, "VIA8233");
		अवरोध;
	शेष:
		dev_err(card->dev, "invalid card type %d\n", card_type);
		err = -EINVAL;
		जाओ __error;
	पूर्ण
		
	अगर ((err = snd_via82xx_create(card, pci, chip_type, pci->revision,
				      ac97_घड़ी, &chip)) < 0)
		जाओ __error;
	card->निजी_data = chip;
	अगर ((err = snd_via82xx_mixer_new(chip, ac97_quirk)) < 0)
		जाओ __error;

	अगर (chip_type == TYPE_VIA686) अणु
		अगर ((err = snd_via686_pcm_new(chip)) < 0 ||
		    (err = snd_via686_init_misc(chip)) < 0)
			जाओ __error;
	पूर्ण अन्यथा अणु
		अगर (chip_type == TYPE_VIA8233A) अणु
			अगर ((err = snd_via8233a_pcm_new(chip)) < 0)
				जाओ __error;
			// chip->dxs_fixed = 1; /* FIXME: use 48k क्रम DXS #3? */
		पूर्ण अन्यथा अणु
			अगर ((err = snd_via8233_pcm_new(chip)) < 0)
				जाओ __error;
			अगर (dxs_support == VIA_DXS_48K)
				chip->dxs_fixed = 1;
			अन्यथा अगर (dxs_support == VIA_DXS_NO_VRA)
				chip->no_vra = 1;
			अन्यथा अगर (dxs_support == VIA_DXS_SRC) अणु
				chip->no_vra = 1;
				chip->dxs_src = 1;
			पूर्ण
		पूर्ण
		अगर ((err = snd_via8233_init_misc(chip)) < 0)
			जाओ __error;
	पूर्ण

	/* disable पूर्णांकerrupts */
	क्रम (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);

	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s with %s at %#lx, irq %d", card->लघुname,
		 snd_ac97_get_लघु_name(chip->ac97), chip->port, chip->irq);

	snd_via82xx_proc_init(chip);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	वापस 0;

 __error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_via82xx_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver via82xx_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_via82xx_ids,
	.probe = snd_via82xx_probe,
	.हटाओ = snd_via82xx_हटाओ,
	.driver = अणु
		.pm = SND_VIA82XX_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(via82xx_driver);
