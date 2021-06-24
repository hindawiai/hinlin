<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Support क्रम Digigram Lola PCI-e boards
 *
 *  Copyright (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#अगर_अघोषित _LOLA_H
#घोषणा _LOLA_H

#घोषणा DRVNAME	"snd-lola"
#घोषणा SFX	DRVNAME ": "

/*
 * Lola HD Audio Registers BAR0
 */
#घोषणा LOLA_BAR0_GCAP		0x00
#घोषणा LOLA_BAR0_VMIN		0x02
#घोषणा LOLA_BAR0_VMAJ		0x03
#घोषणा LOLA_BAR0_OUTPAY	0x04
#घोषणा LOLA_BAR0_INPAY		0x06
#घोषणा LOLA_BAR0_GCTL		0x08
#घोषणा LOLA_BAR0_WAKEEN	0x0c
#घोषणा LOLA_BAR0_STATESTS	0x0e
#घोषणा LOLA_BAR0_GSTS		0x10
#घोषणा LOLA_BAR0_OUTSTRMPAY	0x18
#घोषणा LOLA_BAR0_INSTRMPAY	0x1a
#घोषणा LOLA_BAR0_INTCTL	0x20
#घोषणा LOLA_BAR0_INTSTS	0x24
#घोषणा LOLA_BAR0_WALCLK	0x30
#घोषणा LOLA_BAR0_SSYNC		0x38

#घोषणा LOLA_BAR0_CORBLBASE	0x40
#घोषणा LOLA_BAR0_CORBUBASE	0x44
#घोषणा LOLA_BAR0_CORBWP	0x48	/* no ULONG access */
#घोषणा LOLA_BAR0_CORBRP	0x4a	/* no ULONG access */
#घोषणा LOLA_BAR0_CORBCTL	0x4c	/* no ULONG access */
#घोषणा LOLA_BAR0_CORBSTS	0x4d	/* UCHAR access only */
#घोषणा LOLA_BAR0_CORBSIZE	0x4e	/* no ULONG access */

#घोषणा LOLA_BAR0_RIRBLBASE	0x50
#घोषणा LOLA_BAR0_RIRBUBASE	0x54
#घोषणा LOLA_BAR0_RIRBWP	0x58
#घोषणा LOLA_BAR0_RINTCNT	0x5a	/* no ULONG access */
#घोषणा LOLA_BAR0_RIRBCTL	0x5c
#घोषणा LOLA_BAR0_RIRBSTS	0x5d	/* UCHAR access only */
#घोषणा LOLA_BAR0_RIRBSIZE	0x5e	/* no ULONG access */

#घोषणा LOLA_BAR0_ICW		0x60
#घोषणा LOLA_BAR0_IRR		0x64
#घोषणा LOLA_BAR0_ICS		0x68
#घोषणा LOLA_BAR0_DPLBASE	0x70
#घोषणा LOLA_BAR0_DPUBASE	0x74

/* stream रेजिस्टर offsets from stream base 0x80 */
#घोषणा LOLA_BAR0_SD0_OFFSET	0x80
#घोषणा LOLA_REG0_SD_CTL	0x00
#घोषणा LOLA_REG0_SD_STS	0x03
#घोषणा LOLA_REG0_SD_LPIB	0x04
#घोषणा LOLA_REG0_SD_CBL	0x08
#घोषणा LOLA_REG0_SD_LVI	0x0c
#घोषणा LOLA_REG0_SD_FIFOW	0x0e
#घोषणा LOLA_REG0_SD_FIFOSIZE	0x10
#घोषणा LOLA_REG0_SD_FORMAT	0x12
#घोषणा LOLA_REG0_SD_BDLPL	0x18
#घोषणा LOLA_REG0_SD_BDLPU	0x1c

/*
 * Lola Digigram Registers BAR1
 */
#घोषणा LOLA_BAR1_FPGAVER	0x00
#घोषणा LOLA_BAR1_DEVER		0x04
#घोषणा LOLA_BAR1_UCBMV		0x08
#घोषणा LOLA_BAR1_JTAG		0x0c
#घोषणा LOLA_BAR1_UARTRX	0x10
#घोषणा LOLA_BAR1_UARTTX	0x14
#घोषणा LOLA_BAR1_UARTCR	0x18
#घोषणा LOLA_BAR1_NVRAMVER	0x1c
#घोषणा LOLA_BAR1_CTRLSPI	0x20
#घोषणा LOLA_BAR1_DSPI		0x24
#घोषणा LOLA_BAR1_AISPI		0x28
#घोषणा LOLA_BAR1_GRAN		0x2c

#घोषणा LOLA_BAR1_DINTCTL	0x80
#घोषणा LOLA_BAR1_DIINTCTL	0x84
#घोषणा LOLA_BAR1_DOINTCTL	0x88
#घोषणा LOLA_BAR1_LRC		0x90
#घोषणा LOLA_BAR1_DINTSTS	0x94
#घोषणा LOLA_BAR1_DIINTSTS	0x98
#घोषणा LOLA_BAR1_DOINTSTS	0x9c

#घोषणा LOLA_BAR1_DSD0_OFFSET	0xa0
#घोषणा LOLA_BAR1_DSD_SIZE	0x18

#घोषणा LOLA_BAR1_DSDnSTS       0x00
#घोषणा LOLA_BAR1_DSDnLPIB      0x04
#घोषणा LOLA_BAR1_DSDnCTL       0x08
#घोषणा LOLA_BAR1_DSDnLVI       0x0c
#घोषणा LOLA_BAR1_DSDnBDPL      0x10
#घोषणा LOLA_BAR1_DSDnBDPU      0x14

#घोषणा LOLA_BAR1_SSYNC		0x03e8

#घोषणा LOLA_BAR1_BOARD_CTRL	0x0f00
#घोषणा LOLA_BAR1_BOARD_MODE	0x0f02

#घोषणा LOLA_BAR1_SOURCE_GAIN_ENABLE		0x1000
#घोषणा LOLA_BAR1_DEST00_MIX_GAIN_ENABLE	0x1004
#घोषणा LOLA_BAR1_DEST31_MIX_GAIN_ENABLE	0x1080
#घोषणा LOLA_BAR1_SOURCE00_01_GAIN		0x1084
#घोषणा LOLA_BAR1_SOURCE30_31_GAIN		0x10c0
#घोषणा LOLA_BAR1_SOURCE_GAIN(src) \
	(LOLA_BAR1_SOURCE00_01_GAIN + (src) * 2)
#घोषणा LOLA_BAR1_DEST00_MIX00_01_GAIN		0x10c4
#घोषणा LOLA_BAR1_DEST00_MIX30_31_GAIN		0x1100
#घोषणा LOLA_BAR1_DEST01_MIX00_01_GAIN		0x1104
#घोषणा LOLA_BAR1_DEST01_MIX30_31_GAIN		0x1140
#घोषणा LOLA_BAR1_DEST31_MIX00_01_GAIN		0x1884
#घोषणा LOLA_BAR1_DEST31_MIX30_31_GAIN		0x18c0
#घोषणा LOLA_BAR1_MIX_GAIN(dest, mix) \
	(LOLA_BAR1_DEST00_MIX00_01_GAIN + (dest) * 0x40 + (mix) * 2)
#घोषणा LOLA_BAR1_ANALOG_CLIP_IN		0x18c4
#घोषणा LOLA_BAR1_PEAKMETERS_SOURCE00_01	0x18c8
#घोषणा LOLA_BAR1_PEAKMETERS_SOURCE30_31	0x1904
#घोषणा LOLA_BAR1_PEAKMETERS_SOURCE(src) \
	(LOLA_BAR1_PEAKMETERS_SOURCE00_01 + (src) * 2)
#घोषणा LOLA_BAR1_PEAKMETERS_DEST00_01		0x1908
#घोषणा LOLA_BAR1_PEAKMETERS_DEST30_31		0x1944
#घोषणा LOLA_BAR1_PEAKMETERS_DEST(dest) \
	(LOLA_BAR1_PEAKMETERS_DEST00_01 + (dest) * 2)
#घोषणा LOLA_BAR1_PEAKMETERS_AGC00_01		0x1948
#घोषणा LOLA_BAR1_PEAKMETERS_AGC14_15		0x1964
#घोषणा LOLA_BAR1_PEAKMETERS_AGC(x) \
	(LOLA_BAR1_PEAKMETERS_AGC00_01 + (x) * 2)

/* GCTL reset bit */
#घोषणा LOLA_GCTL_RESET		(1 << 0)
/* GCTL unsolicited response enable bit */
#घोषणा LOLA_GCTL_UREN		(1 << 8)

/* CORB/RIRB control, पढ़ो/ग_लिखो poपूर्णांकer */
#घोषणा LOLA_RBCTL_DMA_EN	0x02	/* enable DMA */
#घोषणा LOLA_RBCTL_IRQ_EN	0x01	/* enable IRQ */
#घोषणा LOLA_RBRWP_CLR		0x8000	/* पढ़ो/ग_लिखो poपूर्णांकer clear */

#घोषणा LOLA_RIRB_EX_UNSOL_EV	0x40000000
#घोषणा LOLA_RIRB_EX_ERROR	0x80000000

/* CORB पूर्णांक mask: CMEI[0] */
#घोषणा LOLA_CORB_INT_CMEI	0x01
#घोषणा LOLA_CORB_INT_MASK	LOLA_CORB_INT_CMEI

/* RIRB पूर्णांक mask: overrun[2], response[0] */
#घोषणा LOLA_RIRB_INT_RESPONSE	0x01
#घोषणा LOLA_RIRB_INT_OVERRUN	0x04
#घोषणा LOLA_RIRB_INT_MASK	(LOLA_RIRB_INT_RESPONSE | LOLA_RIRB_INT_OVERRUN)

/* DINTCTL and DINTSTS */
#घोषणा LOLA_DINT_GLOBAL	0x80000000 /* global पूर्णांकerrupt enable bit */
#घोषणा LOLA_DINT_CTRL		0x40000000 /* controller पूर्णांकerrupt enable bit */
#घोषणा LOLA_DINT_FIFOERR	0x20000000 /* global fअगरo error enable bit */
#घोषणा LOLA_DINT_MUERR		0x10000000 /* global microcontroller underrun error */

/* DSDnCTL bits */
#घोषणा LOLA_DSD_CTL_SRST	0x01	/* stream reset bit */
#घोषणा LOLA_DSD_CTL_SRUN	0x02	/* stream DMA start bit */
#घोषणा LOLA_DSD_CTL_IOCE	0x04	/* पूर्णांकerrupt on completion enable */
#घोषणा LOLA_DSD_CTL_DEIE	0x10	/* descriptor error पूर्णांकerrupt enable */
#घोषणा LOLA_DSD_CTL_VLRCV	0x20	/* valid LRCountValue inक्रमmation in bits 8..31 */
#घोषणा LOLA_LRC_MASK		0xffffff00

/* DSDnSTS */
#घोषणा LOLA_DSD_STS_BCIS	0x04	/* buffer completion पूर्णांकerrupt status */
#घोषणा LOLA_DSD_STS_DESE	0x10	/* descriptor error पूर्णांकerrupt */
#घोषणा LOLA_DSD_STS_FIFORDY	0x20	/* fअगरo पढ़ोy */

#घोषणा LOLA_CORB_ENTRIES	256

#घोषणा MAX_STREAM_IN_COUNT	16
#घोषणा MAX_STREAM_OUT_COUNT	16
#घोषणा MAX_STREAM_COUNT	16
#घोषणा MAX_PINS		MAX_STREAM_COUNT
#घोषणा MAX_STREAM_BUFFER_COUNT	16
#घोषणा MAX_AUDIO_INOUT_COUNT	16

#घोषणा LOLA_CLOCK_TYPE_INTERNAL    0
#घोषणा LOLA_CLOCK_TYPE_AES         1
#घोषणा LOLA_CLOCK_TYPE_AES_SYNC    2
#घोषणा LOLA_CLOCK_TYPE_WORDCLOCK   3
#घोषणा LOLA_CLOCK_TYPE_ETHERSOUND  4
#घोषणा LOLA_CLOCK_TYPE_VIDEO       5

#घोषणा LOLA_CLOCK_FORMAT_NONE      0
#घोषणा LOLA_CLOCK_FORMAT_NTSC      1
#घोषणा LOLA_CLOCK_FORMAT_PAL       2

#घोषणा MAX_SAMPLE_CLOCK_COUNT  48

/* parameters used with mixer widget's mixer capabilities */
#घोषणा LOLA_PEAK_METER_CAN_AGC_MASK		1
#घोषणा LOLA_PEAK_METER_CAN_ANALOG_CLIP_MASK	2

काष्ठा lola_bar अणु
	अचिन्हित दीर्घ addr;
	व्योम __iomem *remap_addr;
पूर्ण;

/* CORB/RIRB */
काष्ठा lola_rb अणु
	__le32 *buf;		/* CORB/RIRB buffer, 8 byte per each entry */
	dma_addr_t addr;	/* physical address of CORB/RIRB buffer */
	अचिन्हित लघु rp, wp;	/* पढ़ो/ग_लिखो poपूर्णांकers */
	पूर्णांक cmds;		/* number of pending requests */
पूर्ण;

/* Pin widget setup */
काष्ठा lola_pin अणु
	अचिन्हित पूर्णांक nid;
	bool is_analog;
	अचिन्हित पूर्णांक amp_mute;
	अचिन्हित पूर्णांक amp_step_size;
	अचिन्हित पूर्णांक amp_num_steps;
	अचिन्हित पूर्णांक amp_offset;
	अचिन्हित पूर्णांक max_level;
	अचिन्हित पूर्णांक config_शेष_reg;
	अचिन्हित पूर्णांक fixed_gain_list_len;
	अचिन्हित पूर्णांक cur_gain_step;
पूर्ण;

काष्ठा lola_pin_array अणु
	अचिन्हित पूर्णांक num_pins;
	अचिन्हित पूर्णांक num_analog_pins;
	काष्ठा lola_pin pins[MAX_PINS];
पूर्ण;

/* Clock widget setup */
काष्ठा lola_sample_घड़ी अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक क्रमmat;
	अचिन्हित पूर्णांक freq;
पूर्ण;

काष्ठा lola_घड़ी_widget अणु
	अचिन्हित पूर्णांक nid;
	अचिन्हित पूर्णांक items;
	अचिन्हित पूर्णांक cur_index;
	अचिन्हित पूर्णांक cur_freq;
	bool cur_valid;
	काष्ठा lola_sample_घड़ी sample_घड़ी[MAX_SAMPLE_CLOCK_COUNT];
	अचिन्हित पूर्णांक idx_lookup[MAX_SAMPLE_CLOCK_COUNT];
पूर्ण;

#घोषणा LOLA_MIXER_DIM      32
काष्ठा lola_mixer_array अणु
	u32 src_gain_enable;
	u32 dest_mix_gain_enable[LOLA_MIXER_DIM];
	u16 src_gain[LOLA_MIXER_DIM];
	u16 dest_mix_gain[LOLA_MIXER_DIM][LOLA_MIXER_DIM];
पूर्ण;

/* Mixer widget setup */
काष्ठा lola_mixer_widget अणु
	अचिन्हित पूर्णांक nid;
	अचिन्हित पूर्णांक caps;
	काष्ठा lola_mixer_array __iomem *array;
	काष्ठा lola_mixer_array *array_saved;
	अचिन्हित पूर्णांक src_stream_outs;
	अचिन्हित पूर्णांक src_phys_ins;
	अचिन्हित पूर्णांक dest_stream_ins;
	अचिन्हित पूर्णांक dest_phys_outs;
	अचिन्हित पूर्णांक src_stream_out_ofs;
	अचिन्हित पूर्णांक dest_phys_out_ofs;
	अचिन्हित पूर्णांक src_mask;
	अचिन्हित पूर्णांक dest_mask;
पूर्ण;

/* Audio stream */
काष्ठा lola_stream अणु
	अचिन्हित पूर्णांक nid;	/* audio widget NID */
	अचिन्हित पूर्णांक index;	/* array index */
	अचिन्हित पूर्णांक dsd;	/* DSD index */
	bool can_भग्न;
	काष्ठा snd_pcm_substream *substream; /* asचिन्हित PCM substream */
	काष्ठा lola_stream *master;	/* master stream (क्रम multi-channel) */

	/* buffer setup */
	अचिन्हित पूर्णांक bufsize;
	अचिन्हित पूर्णांक period_bytes;
	अचिन्हित पूर्णांक frags;

	/* क्रमmat + channel setup */
	अचिन्हित पूर्णांक क्रमmat_verb;

	/* flags */
	अचिन्हित पूर्णांक खोलोed:1;
	अचिन्हित पूर्णांक prepared:1;
	अचिन्हित पूर्णांक छोड़ोd:1;
	अचिन्हित पूर्णांक running:1;
पूर्ण;

#घोषणा PLAY	SNDRV_PCM_STREAM_PLAYBACK
#घोषणा CAPT	SNDRV_PCM_STREAM_CAPTURE

काष्ठा lola_pcm अणु
	अचिन्हित पूर्णांक num_streams;
	काष्ठा snd_dma_buffer bdl; /* BDL buffer */
	काष्ठा lola_stream streams[MAX_STREAM_COUNT];
पूर्ण;

/* card instance */
काष्ठा lola अणु
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;

	/* pci resources */
	काष्ठा lola_bar bar[2];
	पूर्णांक irq;

	/* locks */
	spinlock_t reg_lock;
	काष्ठा mutex खोलो_mutex;

	/* CORB/RIRB */
	काष्ठा lola_rb corb;
	काष्ठा lola_rb rirb;
	अचिन्हित पूर्णांक res, res_ex;	/* last पढ़ो values */
	/* last command (क्रम debugging) */
	अचिन्हित पूर्णांक last_cmd_nid, last_verb, last_data, last_extdata;

	/* CORB/RIRB buffers */
	काष्ठा snd_dma_buffer rb;

	/* unsolicited events */
	अचिन्हित पूर्णांक last_unsol_res;

	/* streams */
	काष्ठा lola_pcm pcm[2];

	/* input src */
	अचिन्हित पूर्णांक input_src_caps_mask;
	अचिन्हित पूर्णांक input_src_mask;

	/* pins */
	काष्ठा lola_pin_array pin[2];

	/* घड़ी */
	काष्ठा lola_घड़ी_widget घड़ी;
	पूर्णांक ref_count_rate;
	अचिन्हित पूर्णांक sample_rate;

	/* mixer */
	काष्ठा lola_mixer_widget mixer;

	/* hw info */
	अचिन्हित पूर्णांक version;
	अचिन्हित पूर्णांक lola_caps;

	/* parameters */
	अचिन्हित पूर्णांक granularity;
	अचिन्हित पूर्णांक sample_rate_min;
	अचिन्हित पूर्णांक sample_rate_max;

	/* flags */
	अचिन्हित पूर्णांक initialized:1;
	अचिन्हित पूर्णांक cold_reset:1;
	अचिन्हित पूर्णांक polling_mode:1;

	/* क्रम debugging */
	अचिन्हित पूर्णांक debug_res;
	अचिन्हित पूर्णांक debug_res_ex;
पूर्ण;

#घोषणा BAR0	0
#घोषणा BAR1	1

/* Helper macros */
#घोषणा lola_पढ़ोl(chip, idx, name) \
	पढ़ोl((chip)->bar[idx].remap_addr + LOLA_##idx##_##name)
#घोषणा lola_पढ़ोw(chip, idx, name) \
	पढ़ोw((chip)->bar[idx].remap_addr + LOLA_##idx##_##name)
#घोषणा lola_पढ़ोb(chip, idx, name) \
	पढ़ोb((chip)->bar[idx].remap_addr + LOLA_##idx##_##name)
#घोषणा lola_ग_लिखोl(chip, idx, name, val) \
	ग_लिखोl((val), (chip)->bar[idx].remap_addr + LOLA_##idx##_##name)
#घोषणा lola_ग_लिखोw(chip, idx, name, val) \
	ग_लिखोw((val), (chip)->bar[idx].remap_addr + LOLA_##idx##_##name)
#घोषणा lola_ग_लिखोb(chip, idx, name, val) \
	ग_लिखोb((val), (chip)->bar[idx].remap_addr + LOLA_##idx##_##name)

#घोषणा lola_dsd_पढ़ो(chip, dsd, name) \
	पढ़ोl((chip)->bar[BAR1].remap_addr + LOLA_BAR1_DSD0_OFFSET + \
	      (LOLA_BAR1_DSD_SIZE * (dsd)) + LOLA_BAR1_DSDn##name)
#घोषणा lola_dsd_ग_लिखो(chip, dsd, name, val) \
	ग_लिखोl((val), (chip)->bar[BAR1].remap_addr + LOLA_BAR1_DSD0_OFFSET + \
	       (LOLA_BAR1_DSD_SIZE * (dsd)) + LOLA_BAR1_DSDn##name)

/* GET verbs HDAudio */
#घोषणा LOLA_VERB_GET_STREAM_FORMAT		0xa00
#घोषणा LOLA_VERB_GET_AMP_GAIN_MUTE		0xb00
#घोषणा LOLA_VERB_PARAMETERS			0xf00
#घोषणा LOLA_VERB_GET_POWER_STATE		0xf05
#घोषणा LOLA_VERB_GET_CONV			0xf06
#घोषणा LOLA_VERB_GET_UNSOLICITED_RESPONSE	0xf08
#घोषणा LOLA_VERB_GET_DIGI_CONVERT_1		0xf0d
#घोषणा LOLA_VERB_GET_CONFIG_DEFAULT		0xf1c
#घोषणा LOLA_VERB_GET_SUBSYSTEM_ID		0xf20
/* GET verbs Digigram */
#घोषणा LOLA_VERB_GET_FIXED_GAIN		0xfc0
#घोषणा LOLA_VERB_GET_GAIN_SELECT		0xfc1
#घोषणा LOLA_VERB_GET_MAX_LEVEL			0xfc2
#घोषणा LOLA_VERB_GET_CLOCK_LIST		0xfc3
#घोषणा LOLA_VERB_GET_CLOCK_SELECT		0xfc4
#घोषणा LOLA_VERB_GET_CLOCK_STATUS		0xfc5

/* SET verbs HDAudio */
#घोषणा LOLA_VERB_SET_STREAM_FORMAT		0x200
#घोषणा LOLA_VERB_SET_AMP_GAIN_MUTE		0x300
#घोषणा LOLA_VERB_SET_POWER_STATE		0x705
#घोषणा LOLA_VERB_SET_CHANNEL_STREAMID		0x706
#घोषणा LOLA_VERB_SET_UNSOLICITED_ENABLE	0x708
#घोषणा LOLA_VERB_SET_DIGI_CONVERT_1		0x70d
/* SET verbs Digigram */
#घोषणा LOLA_VERB_SET_GAIN_SELECT		0xf81
#घोषणा LOLA_VERB_SET_CLOCK_SELECT		0xf84
#घोषणा LOLA_VERB_SET_GRANULARITY_STEPS		0xf86
#घोषणा LOLA_VERB_SET_SOURCE_GAIN		0xf87
#घोषणा LOLA_VERB_SET_MIX_GAIN			0xf88
#घोषणा LOLA_VERB_SET_DESTINATION_GAIN		0xf89
#घोषणा LOLA_VERB_SET_SRC			0xf8a

/* Parameter IDs used with LOLA_VERB_PARAMETERS */
#घोषणा LOLA_PAR_VENDOR_ID			0x00
#घोषणा LOLA_PAR_FUNCTION_TYPE			0x05
#घोषणा LOLA_PAR_AUDIO_WIDGET_CAP		0x09
#घोषणा LOLA_PAR_PCM				0x0a
#घोषणा LOLA_PAR_STREAM_FORMATS			0x0b
#घोषणा LOLA_PAR_PIN_CAP			0x0c
#घोषणा LOLA_PAR_AMP_IN_CAP			0x0d
#घोषणा LOLA_PAR_CONNLIST_LEN			0x0e
#घोषणा LOLA_PAR_POWER_STATE			0x0f
#घोषणा LOLA_PAR_GPIO_CAP			0x11
#घोषणा LOLA_PAR_AMP_OUT_CAP			0x12
#घोषणा LOLA_PAR_SPECIFIC_CAPS			0x80
#घोषणा LOLA_PAR_FIXED_GAIN_LIST		0x81

/* extract results of LOLA_PAR_SPECIFIC_CAPS */
#घोषणा LOLA_AFG_MIXER_WIDGET_PRESENT(res)	((res & (1 << 21)) != 0)
#घोषणा LOLA_AFG_CLOCK_WIDGET_PRESENT(res)	((res & (1 << 20)) != 0)
#घोषणा LOLA_AFG_INPUT_PIN_COUNT(res)		((res >> 10) & 0x2ff)
#घोषणा LOLA_AFG_OUTPUT_PIN_COUNT(res)		((res) & 0x2ff)

/* extract results of LOLA_PAR_AMP_IN_CAP / LOLA_PAR_AMP_OUT_CAP */
#घोषणा LOLA_AMP_MUTE_CAPABLE(res)		((res & (1 << 31)) != 0)
#घोषणा LOLA_AMP_STEP_SIZE(res)			((res >> 24) & 0x7f)
#घोषणा LOLA_AMP_NUM_STEPS(res)			((res >> 12) & 0x3ff)
#घोषणा LOLA_AMP_OFFSET(res)			((res) & 0x3ff)

#घोषणा LOLA_GRANULARITY_MIN		8
#घोषणा LOLA_GRANULARITY_MAX		32
#घोषणा LOLA_GRANULARITY_STEP		8

/* parameters used with unsolicited command/response */
#घोषणा LOLA_UNSOLICITED_TAG_MASK	0x3f
#घोषणा LOLA_UNSOLICITED_TAG		0x1a
#घोषणा LOLA_UNSOLICITED_ENABLE		0x80
#घोषणा LOLA_UNSOL_RESP_TAG_OFFSET	26

/* count values in the Venकरोr Specअगरic Mixer Widget's Audio Widget Capabilities */
#घोषणा LOLA_MIXER_SRC_INPUT_PLAY_SEPARATION(res)   ((res >> 2) & 0x1f)
#घोषणा LOLA_MIXER_DEST_REC_OUTPUT_SEPARATION(res)  ((res >> 7) & 0x1f)

पूर्णांक lola_codec_ग_लिखो(काष्ठा lola *chip, अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक verb,
		     अचिन्हित पूर्णांक data, अचिन्हित पूर्णांक extdata);
पूर्णांक lola_codec_पढ़ो(काष्ठा lola *chip, अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक verb,
		    अचिन्हित पूर्णांक data, अचिन्हित पूर्णांक extdata,
		    अचिन्हित पूर्णांक *val, अचिन्हित पूर्णांक *extval);
पूर्णांक lola_codec_flush(काष्ठा lola *chip);
#घोषणा lola_पढ़ो_param(chip, nid, param, val) \
	lola_codec_पढ़ो(chip, nid, LOLA_VERB_PARAMETERS, param, 0, val, शून्य)

/* PCM */
पूर्णांक lola_create_pcm(काष्ठा lola *chip);
व्योम lola_मुक्त_pcm(काष्ठा lola *chip);
पूर्णांक lola_init_pcm(काष्ठा lola *chip, पूर्णांक dir, पूर्णांक *nidp);
व्योम lola_pcm_update(काष्ठा lola *chip, काष्ठा lola_pcm *pcm, अचिन्हित पूर्णांक bits);

/* घड़ी */
पूर्णांक lola_init_घड़ी_widget(काष्ठा lola *chip, पूर्णांक nid);
पूर्णांक lola_set_granularity(काष्ठा lola *chip, अचिन्हित पूर्णांक val, bool क्रमce);
पूर्णांक lola_enable_घड़ी_events(काष्ठा lola *chip);
पूर्णांक lola_set_घड़ी_index(काष्ठा lola *chip, अचिन्हित पूर्णांक idx);
पूर्णांक lola_set_घड़ी(काष्ठा lola *chip, पूर्णांक idx);
पूर्णांक lola_set_sample_rate(काष्ठा lola *chip, पूर्णांक rate);
bool lola_update_ext_घड़ी_freq(काष्ठा lola *chip, अचिन्हित पूर्णांक val);
अचिन्हित पूर्णांक lola_sample_rate_convert(अचिन्हित पूर्णांक coded);

/* mixer */
पूर्णांक lola_init_pins(काष्ठा lola *chip, पूर्णांक dir, पूर्णांक *nidp);
पूर्णांक lola_init_mixer_widget(काष्ठा lola *chip, पूर्णांक nid);
व्योम lola_मुक्त_mixer(काष्ठा lola *chip);
पूर्णांक lola_create_mixer(काष्ठा lola *chip);
पूर्णांक lola_setup_all_analog_gains(काष्ठा lola *chip, पूर्णांक dir, bool mute);
व्योम lola_save_mixer(काष्ठा lola *chip);
व्योम lola_restore_mixer(काष्ठा lola *chip);
पूर्णांक lola_set_src_config(काष्ठा lola *chip, अचिन्हित पूर्णांक src_mask, bool update);

/* proc */
#अगर_घोषित CONFIG_SND_DEBUG
व्योम lola_proc_debug_new(काष्ठा lola *chip);
#अन्यथा
#घोषणा lola_proc_debug_new(chip)
#पूर्ण_अगर

#पूर्ण_अगर /* _LOLA_H */
