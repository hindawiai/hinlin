<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * HD-audio codec verbs
 */

#अगर_अघोषित __SOUND_HDA_VERBS_H
#घोषणा __SOUND_HDA_VERBS_H

/*
 * nodes
 */
#घोषणा	AC_NODE_ROOT		0x00

/*
 * function group types
 */
क्रमागत अणु
	AC_GRP_AUDIO_FUNCTION = 0x01,
	AC_GRP_MODEM_FUNCTION = 0x02,
पूर्ण;

/*
 * widget types
 */
क्रमागत अणु
	AC_WID_AUD_OUT,		/* Audio Out */
	AC_WID_AUD_IN,		/* Audio In */
	AC_WID_AUD_MIX,		/* Audio Mixer */
	AC_WID_AUD_SEL,		/* Audio Selector */
	AC_WID_PIN,		/* Pin Complex */
	AC_WID_POWER,		/* Power */
	AC_WID_VOL_KNB,		/* Volume Knob */
	AC_WID_BEEP,		/* Beep Generator */
	AC_WID_VENDOR = 0x0f	/* Venकरोr specअगरic */
पूर्ण;

/*
 * GET verbs
 */
#घोषणा AC_VERB_GET_STREAM_FORMAT		0x0a00
#घोषणा AC_VERB_GET_AMP_GAIN_MUTE		0x0b00
#घोषणा AC_VERB_GET_PROC_COEF			0x0c00
#घोषणा AC_VERB_GET_COEF_INDEX			0x0d00
#घोषणा AC_VERB_PARAMETERS			0x0f00
#घोषणा AC_VERB_GET_CONNECT_SEL			0x0f01
#घोषणा AC_VERB_GET_CONNECT_LIST		0x0f02
#घोषणा AC_VERB_GET_PROC_STATE			0x0f03
#घोषणा AC_VERB_GET_SDI_SELECT			0x0f04
#घोषणा AC_VERB_GET_POWER_STATE			0x0f05
#घोषणा AC_VERB_GET_CONV			0x0f06
#घोषणा AC_VERB_GET_PIN_WIDGET_CONTROL		0x0f07
#घोषणा AC_VERB_GET_UNSOLICITED_RESPONSE	0x0f08
#घोषणा AC_VERB_GET_PIN_SENSE			0x0f09
#घोषणा AC_VERB_GET_BEEP_CONTROL		0x0f0a
#घोषणा AC_VERB_GET_EAPD_BTLENABLE		0x0f0c
#घोषणा AC_VERB_GET_DIGI_CONVERT_1		0x0f0d
#घोषणा AC_VERB_GET_DIGI_CONVERT_2		0x0f0e /* unused */
#घोषणा AC_VERB_GET_VOLUME_KNOB_CONTROL		0x0f0f
/* f10-f1a: GPIO */
#घोषणा AC_VERB_GET_GPIO_DATA			0x0f15
#घोषणा AC_VERB_GET_GPIO_MASK			0x0f16
#घोषणा AC_VERB_GET_GPIO_सूचीECTION		0x0f17
#घोषणा AC_VERB_GET_GPIO_WAKE_MASK		0x0f18
#घोषणा AC_VERB_GET_GPIO_UNSOLICITED_RSP_MASK	0x0f19
#घोषणा AC_VERB_GET_GPIO_STICKY_MASK		0x0f1a
#घोषणा AC_VERB_GET_CONFIG_DEFAULT		0x0f1c
/* f20: AFG/MFG */
#घोषणा AC_VERB_GET_SUBSYSTEM_ID		0x0f20
#घोषणा AC_VERB_GET_STRIPE_CONTROL		0x0f24
#घोषणा AC_VERB_GET_CVT_CHAN_COUNT		0x0f2d
#घोषणा AC_VERB_GET_HDMI_DIP_SIZE		0x0f2e
#घोषणा AC_VERB_GET_HDMI_ELDD			0x0f2f
#घोषणा AC_VERB_GET_HDMI_DIP_INDEX		0x0f30
#घोषणा AC_VERB_GET_HDMI_DIP_DATA		0x0f31
#घोषणा AC_VERB_GET_HDMI_DIP_XMIT		0x0f32
#घोषणा AC_VERB_GET_HDMI_CP_CTRL		0x0f33
#घोषणा AC_VERB_GET_HDMI_CHAN_SLOT		0x0f34
#घोषणा AC_VERB_GET_DEVICE_SEL			0xf35
#घोषणा AC_VERB_GET_DEVICE_LIST			0xf36

/*
 * SET verbs
 */
#घोषणा AC_VERB_SET_STREAM_FORMAT		0x200
#घोषणा AC_VERB_SET_AMP_GAIN_MUTE		0x300
#घोषणा AC_VERB_SET_PROC_COEF			0x400
#घोषणा AC_VERB_SET_COEF_INDEX			0x500
#घोषणा AC_VERB_SET_CONNECT_SEL			0x701
#घोषणा AC_VERB_SET_PROC_STATE			0x703
#घोषणा AC_VERB_SET_SDI_SELECT			0x704
#घोषणा AC_VERB_SET_POWER_STATE			0x705
#घोषणा AC_VERB_SET_CHANNEL_STREAMID		0x706
#घोषणा AC_VERB_SET_PIN_WIDGET_CONTROL		0x707
#घोषणा AC_VERB_SET_UNSOLICITED_ENABLE		0x708
#घोषणा AC_VERB_SET_PIN_SENSE			0x709
#घोषणा AC_VERB_SET_BEEP_CONTROL		0x70a
#घोषणा AC_VERB_SET_EAPD_BTLENABLE		0x70c
#घोषणा AC_VERB_SET_DIGI_CONVERT_1		0x70d
#घोषणा AC_VERB_SET_DIGI_CONVERT_2		0x70e
#घोषणा AC_VERB_SET_DIGI_CONVERT_3		0x73e
#घोषणा AC_VERB_SET_VOLUME_KNOB_CONTROL		0x70f
#घोषणा AC_VERB_SET_GPIO_DATA			0x715
#घोषणा AC_VERB_SET_GPIO_MASK			0x716
#घोषणा AC_VERB_SET_GPIO_सूचीECTION		0x717
#घोषणा AC_VERB_SET_GPIO_WAKE_MASK		0x718
#घोषणा AC_VERB_SET_GPIO_UNSOLICITED_RSP_MASK	0x719
#घोषणा AC_VERB_SET_GPIO_STICKY_MASK		0x71a
#घोषणा AC_VERB_SET_CONFIG_DEFAULT_BYTES_0	0x71c
#घोषणा AC_VERB_SET_CONFIG_DEFAULT_BYTES_1	0x71d
#घोषणा AC_VERB_SET_CONFIG_DEFAULT_BYTES_2	0x71e
#घोषणा AC_VERB_SET_CONFIG_DEFAULT_BYTES_3	0x71f
#घोषणा AC_VERB_SET_EAPD				0x788
#घोषणा AC_VERB_SET_CODEC_RESET			0x7ff
#घोषणा AC_VERB_SET_STRIPE_CONTROL		0x724
#घोषणा AC_VERB_SET_CVT_CHAN_COUNT		0x72d
#घोषणा AC_VERB_SET_HDMI_DIP_INDEX		0x730
#घोषणा AC_VERB_SET_HDMI_DIP_DATA		0x731
#घोषणा AC_VERB_SET_HDMI_DIP_XMIT		0x732
#घोषणा AC_VERB_SET_HDMI_CP_CTRL		0x733
#घोषणा AC_VERB_SET_HDMI_CHAN_SLOT		0x734
#घोषणा AC_VERB_SET_DEVICE_SEL			0x735

/*
 * Parameter IDs
 */
#घोषणा AC_PAR_VENDOR_ID		0x00
#घोषणा AC_PAR_SUBSYSTEM_ID		0x01
#घोषणा AC_PAR_REV_ID			0x02
#घोषणा AC_PAR_NODE_COUNT		0x04
#घोषणा AC_PAR_FUNCTION_TYPE		0x05
#घोषणा AC_PAR_AUDIO_FG_CAP		0x08
#घोषणा AC_PAR_AUDIO_WIDGET_CAP		0x09
#घोषणा AC_PAR_PCM			0x0a
#घोषणा AC_PAR_STREAM			0x0b
#घोषणा AC_PAR_PIN_CAP			0x0c
#घोषणा AC_PAR_AMP_IN_CAP		0x0d
#घोषणा AC_PAR_CONNLIST_LEN		0x0e
#घोषणा AC_PAR_POWER_STATE		0x0f
#घोषणा AC_PAR_PROC_CAP			0x10
#घोषणा AC_PAR_GPIO_CAP			0x11
#घोषणा AC_PAR_AMP_OUT_CAP		0x12
#घोषणा AC_PAR_VOL_KNB_CAP		0x13
#घोषणा AC_PAR_DEVLIST_LEN		0x15
#घोषणा AC_PAR_HDMI_LPCM_CAP		0x20

/*
 * AC_VERB_PARAMETERS results (32bit)
 */

/* Function Group Type */
#घोषणा AC_FGT_TYPE			(0xff<<0)
#घोषणा AC_FGT_TYPE_SHIFT		0
#घोषणा AC_FGT_UNSOL_CAP		(1<<8)

/* Audio Function Group Capabilities */
#घोषणा AC_AFG_OUT_DELAY		(0xf<<0)
#घोषणा AC_AFG_IN_DELAY			(0xf<<8)
#घोषणा AC_AFG_BEEP_GEN			(1<<16)

/* Audio Widget Capabilities */
#घोषणा AC_WCAP_STEREO			(1<<0)	/* stereo I/O */
#घोषणा AC_WCAP_IN_AMP			(1<<1)	/* AMP-in present */
#घोषणा AC_WCAP_OUT_AMP			(1<<2)	/* AMP-out present */
#घोषणा AC_WCAP_AMP_OVRD		(1<<3)	/* AMP-parameter override */
#घोषणा AC_WCAP_FORMAT_OVRD		(1<<4)	/* क्रमmat override */
#घोषणा AC_WCAP_STRIPE			(1<<5)	/* stripe */
#घोषणा AC_WCAP_PROC_WID		(1<<6)	/* Proc Widget */
#घोषणा AC_WCAP_UNSOL_CAP		(1<<7)	/* Unsol capable */
#घोषणा AC_WCAP_CONN_LIST		(1<<8)	/* connection list */
#घोषणा AC_WCAP_DIGITAL			(1<<9)	/* digital I/O */
#घोषणा AC_WCAP_POWER			(1<<10)	/* घातer control */
#घोषणा AC_WCAP_LR_SWAP			(1<<11)	/* L/R swap */
#घोषणा AC_WCAP_CP_CAPS			(1<<12) /* content protection */
#घोषणा AC_WCAP_CHAN_CNT_EXT		(7<<13)	/* channel count ext */
#घोषणा AC_WCAP_DELAY			(0xf<<16)
#घोषणा AC_WCAP_DELAY_SHIFT		16
#घोषणा AC_WCAP_TYPE			(0xf<<20)
#घोषणा AC_WCAP_TYPE_SHIFT		20

/* supported PCM rates and bits */
#घोषणा AC_SUPPCM_RATES			(0xfff << 0)
#घोषणा AC_SUPPCM_BITS_8		(1<<16)
#घोषणा AC_SUPPCM_BITS_16		(1<<17)
#घोषणा AC_SUPPCM_BITS_20		(1<<18)
#घोषणा AC_SUPPCM_BITS_24		(1<<19)
#घोषणा AC_SUPPCM_BITS_32		(1<<20)

/* supported PCM stream क्रमmat */
#घोषणा AC_SUPFMT_PCM			(1<<0)
#घोषणा AC_SUPFMT_FLOAT32		(1<<1)
#घोषणा AC_SUPFMT_AC3			(1<<2)

/* GP I/O count */
#घोषणा AC_GPIO_IO_COUNT		(0xff<<0)
#घोषणा AC_GPIO_O_COUNT			(0xff<<8)
#घोषणा AC_GPIO_O_COUNT_SHIFT		8
#घोषणा AC_GPIO_I_COUNT			(0xff<<16)
#घोषणा AC_GPIO_I_COUNT_SHIFT		16
#घोषणा AC_GPIO_UNSOLICITED		(1<<30)
#घोषणा AC_GPIO_WAKE			(1<<31)

/* Converter stream, channel */
#घोषणा AC_CONV_CHANNEL			(0xf<<0)
#घोषणा AC_CONV_STREAM			(0xf<<4)
#घोषणा AC_CONV_STREAM_SHIFT		4

/* Input converter SDI select */
#घोषणा AC_SDI_SELECT			(0xf<<0)

/* stream क्रमmat id */
#घोषणा AC_FMT_CHAN_SHIFT		0
#घोषणा AC_FMT_CHAN_MASK		(0x0f << 0)
#घोषणा AC_FMT_BITS_SHIFT		4
#घोषणा AC_FMT_BITS_MASK		(7 << 4)
#घोषणा AC_FMT_BITS_8			(0 << 4)
#घोषणा AC_FMT_BITS_16			(1 << 4)
#घोषणा AC_FMT_BITS_20			(2 << 4)
#घोषणा AC_FMT_BITS_24			(3 << 4)
#घोषणा AC_FMT_BITS_32			(4 << 4)
#घोषणा AC_FMT_DIV_SHIFT		8
#घोषणा AC_FMT_DIV_MASK			(7 << 8)
#घोषणा AC_FMT_MULT_SHIFT		11
#घोषणा AC_FMT_MULT_MASK		(7 << 11)
#घोषणा AC_FMT_BASE_SHIFT		14
#घोषणा AC_FMT_BASE_48K			(0 << 14)
#घोषणा AC_FMT_BASE_44K			(1 << 14)
#घोषणा AC_FMT_TYPE_SHIFT		15
#घोषणा AC_FMT_TYPE_PCM			(0 << 15)
#घोषणा AC_FMT_TYPE_NON_PCM		(1 << 15)

/* Unsolicited response control */
#घोषणा AC_UNSOL_TAG			(0x3f<<0)
#घोषणा AC_UNSOL_ENABLED		(1<<7)
#घोषणा AC_USRSP_EN			AC_UNSOL_ENABLED

/* Unsolicited responses */
#घोषणा AC_UNSOL_RES_TAG		(0x3f<<26)
#घोषणा AC_UNSOL_RES_TAG_SHIFT		26
#घोषणा AC_UNSOL_RES_SUBTAG		(0x1f<<21)
#घोषणा AC_UNSOL_RES_SUBTAG_SHIFT	21
#घोषणा AC_UNSOL_RES_DE			(0x3f<<15)  /* Device Entry
						     * (क्रम DP1.2 MST)
						     */
#घोषणा AC_UNSOL_RES_DE_SHIFT		15
#घोषणा AC_UNSOL_RES_IA			(1<<2)	/* Inactive (क्रम DP1.2 MST) */
#घोषणा AC_UNSOL_RES_ELDV		(1<<1)	/* ELD Data valid (क्रम HDMI) */
#घोषणा AC_UNSOL_RES_PD			(1<<0)	/* pinsense detect */
#घोषणा AC_UNSOL_RES_CP_STATE		(1<<1)	/* content protection */
#घोषणा AC_UNSOL_RES_CP_READY		(1<<0)	/* content protection */

/* Pin widget capabilies */
#घोषणा AC_PINCAP_IMP_SENSE		(1<<0)	/* impedance sense capable */
#घोषणा AC_PINCAP_TRIG_REQ		(1<<1)	/* trigger required */
#घोषणा AC_PINCAP_PRES_DETECT		(1<<2)	/* presence detect capable */
#घोषणा AC_PINCAP_HP_DRV		(1<<3)	/* headphone drive capable */
#घोषणा AC_PINCAP_OUT			(1<<4)	/* output capable */
#घोषणा AC_PINCAP_IN			(1<<5)	/* input capable */
#घोषणा AC_PINCAP_BALANCE		(1<<6)	/* balanced I/O capable */
/* Note: This LR_SWAP pincap is defined in the Realtek ALC883 specअगरication,
 *       but is marked reserved in the Intel HDA specअगरication.
 */
#घोषणा AC_PINCAP_LR_SWAP		(1<<7)	/* L/R swap */
/* Note: The same bit as LR_SWAP is newly defined as HDMI capability
 *       in HD-audio specअगरication
 */
#घोषणा AC_PINCAP_HDMI			(1<<7)	/* HDMI pin */
#घोषणा AC_PINCAP_DP			(1<<24)	/* DisplayPort pin, can
						 * coexist with AC_PINCAP_HDMI
						 */
#घोषणा AC_PINCAP_VREF			(0x37<<8)
#घोषणा AC_PINCAP_VREF_SHIFT		8
#घोषणा AC_PINCAP_EAPD			(1<<16)	/* EAPD capable */
#घोषणा AC_PINCAP_HBR			(1<<27)	/* High Bit Rate */
/* Vref status (used in pin cap) */
#घोषणा AC_PINCAP_VREF_HIZ		(1<<0)	/* Hi-Z */
#घोषणा AC_PINCAP_VREF_50		(1<<1)	/* 50% */
#घोषणा AC_PINCAP_VREF_GRD		(1<<2)	/* ground */
#घोषणा AC_PINCAP_VREF_80		(1<<4)	/* 80% */
#घोषणा AC_PINCAP_VREF_100		(1<<5)	/* 100% */

/* Amplअगरier capabilities */
#घोषणा AC_AMPCAP_OFFSET		(0x7f<<0)  /* 0dB offset */
#घोषणा AC_AMPCAP_OFFSET_SHIFT		0
#घोषणा AC_AMPCAP_NUM_STEPS		(0x7f<<8)  /* number of steps */
#घोषणा AC_AMPCAP_NUM_STEPS_SHIFT	8
#घोषणा AC_AMPCAP_STEP_SIZE		(0x7f<<16) /* step size 0-32dB
						    * in 0.25dB
						    */
#घोषणा AC_AMPCAP_STEP_SIZE_SHIFT	16
#घोषणा AC_AMPCAP_MUTE			(1<<31)    /* mute capable */
#घोषणा AC_AMPCAP_MUTE_SHIFT		31

/* driver-specअगरic amp-caps: using bits 24-30 */
#घोषणा AC_AMPCAP_MIN_MUTE		(1 << 30) /* min-volume = mute */

/* Connection list */
#घोषणा AC_CLIST_LENGTH			(0x7f<<0)
#घोषणा AC_CLIST_LONG			(1<<7)

/* Supported घातer status */
#घोषणा AC_PWRST_D0SUP			(1<<0)
#घोषणा AC_PWRST_D1SUP			(1<<1)
#घोषणा AC_PWRST_D2SUP			(1<<2)
#घोषणा AC_PWRST_D3SUP			(1<<3)
#घोषणा AC_PWRST_D3COLDSUP		(1<<4)
#घोषणा AC_PWRST_S3D3COLDSUP		(1<<29)
#घोषणा AC_PWRST_CLKSTOP		(1<<30)
#घोषणा AC_PWRST_EPSS			(1U<<31)

/* Power state values */
#घोषणा AC_PWRST_SETTING		(0xf<<0)
#घोषणा AC_PWRST_ACTUAL			(0xf<<4)
#घोषणा AC_PWRST_ACTUAL_SHIFT		4
#घोषणा AC_PWRST_D0			0x00
#घोषणा AC_PWRST_D1			0x01
#घोषणा AC_PWRST_D2			0x02
#घोषणा AC_PWRST_D3			0x03
#घोषणा AC_PWRST_ERROR                  (1<<8)
#घोषणा AC_PWRST_CLK_STOP_OK            (1<<9)
#घोषणा AC_PWRST_SETTING_RESET          (1<<10)

/* Processing capabilies */
#घोषणा AC_PCAP_BENIGN			(1<<0)
#घोषणा AC_PCAP_NUM_COEF		(0xff<<8)
#घोषणा AC_PCAP_NUM_COEF_SHIFT		8

/* Volume knobs capabilities */
#घोषणा AC_KNBCAP_NUM_STEPS		(0x7f<<0)
#घोषणा AC_KNBCAP_DELTA			(1<<7)

/* HDMI LPCM capabilities */
#घोषणा AC_LPCMCAP_48K_CP_CHNS		(0x0f<<0) /* max channels w/ CP-on */
#घोषणा AC_LPCMCAP_48K_NO_CHNS		(0x0f<<4) /* max channels w/o CP-on */
#घोषणा AC_LPCMCAP_48K_20BIT		(1<<8)	/* 20b bitrate supported */
#घोषणा AC_LPCMCAP_48K_24BIT		(1<<9)	/* 24b bitrate supported */
#घोषणा AC_LPCMCAP_96K_CP_CHNS		(0x0f<<10) /* max channels w/ CP-on */
#घोषणा AC_LPCMCAP_96K_NO_CHNS		(0x0f<<14) /* max channels w/o CP-on */
#घोषणा AC_LPCMCAP_96K_20BIT		(1<<18)	/* 20b bitrate supported */
#घोषणा AC_LPCMCAP_96K_24BIT		(1<<19)	/* 24b bitrate supported */
#घोषणा AC_LPCMCAP_192K_CP_CHNS		(0x0f<<20) /* max channels w/ CP-on */
#घोषणा AC_LPCMCAP_192K_NO_CHNS		(0x0f<<24) /* max channels w/o CP-on */
#घोषणा AC_LPCMCAP_192K_20BIT		(1<<28)	/* 20b bitrate supported */
#घोषणा AC_LPCMCAP_192K_24BIT		(1<<29)	/* 24b bitrate supported */
#घोषणा AC_LPCMCAP_44K			(1<<30)	/* 44.1kHz support */
#घोषणा AC_LPCMCAP_44K_MS		(1<<31)	/* 44.1kHz-multiplies support */

/* Display pin's device list length */
#घोषणा AC_DEV_LIST_LEN_MASK		0x3f
#घोषणा AC_MAX_DEV_LIST_LEN		64

/*
 * Control Parameters
 */

/* Amp gain/mute */
#घोषणा AC_AMP_MUTE			(1<<7)
#घोषणा AC_AMP_GAIN			(0x7f)
#घोषणा AC_AMP_GET_INDEX		(0xf<<0)

#घोषणा AC_AMP_GET_LEFT			(1<<13)
#घोषणा AC_AMP_GET_RIGHT		(0<<13)
#घोषणा AC_AMP_GET_OUTPUT		(1<<15)
#घोषणा AC_AMP_GET_INPUT		(0<<15)

#घोषणा AC_AMP_SET_INDEX		(0xf<<8)
#घोषणा AC_AMP_SET_INDEX_SHIFT		8
#घोषणा AC_AMP_SET_RIGHT		(1<<12)
#घोषणा AC_AMP_SET_LEFT			(1<<13)
#घोषणा AC_AMP_SET_INPUT		(1<<14)
#घोषणा AC_AMP_SET_OUTPUT		(1<<15)

/* DIGITAL1 bits */
#घोषणा AC_DIG1_ENABLE			(1<<0)
#घोषणा AC_DIG1_V			(1<<1)
#घोषणा AC_DIG1_VCFG			(1<<2)
#घोषणा AC_DIG1_EMPHASIS		(1<<3)
#घोषणा AC_DIG1_COPYRIGHT		(1<<4)
#घोषणा AC_DIG1_NONAUDIO		(1<<5)
#घोषणा AC_DIG1_PROFESSIONAL		(1<<6)
#घोषणा AC_DIG1_LEVEL			(1<<7)

/* DIGITAL2 bits */
#घोषणा AC_DIG2_CC			(0x7f<<0)

/* DIGITAL3 bits */
#घोषणा AC_DIG3_ICT			(0xf<<0)
#घोषणा AC_DIG3_KAE			(1<<7)

/* Pin widget control - 8bit */
#घोषणा AC_PINCTL_EPT			(0x3<<0)
#घोषणा AC_PINCTL_EPT_NATIVE		0
#घोषणा AC_PINCTL_EPT_HBR		3
#घोषणा AC_PINCTL_VREFEN		(0x7<<0)
#घोषणा AC_PINCTL_VREF_HIZ		0	/* Hi-Z */
#घोषणा AC_PINCTL_VREF_50		1	/* 50% */
#घोषणा AC_PINCTL_VREF_GRD		2	/* ground */
#घोषणा AC_PINCTL_VREF_80		4	/* 80% */
#घोषणा AC_PINCTL_VREF_100		5	/* 100% */
#घोषणा AC_PINCTL_IN_EN			(1<<5)
#घोषणा AC_PINCTL_OUT_EN		(1<<6)
#घोषणा AC_PINCTL_HP_EN			(1<<7)

/* Pin sense - 32bit */
#घोषणा AC_PINSENSE_IMPEDANCE_MASK	(0x7fffffff)
#घोषणा AC_PINSENSE_PRESENCE		(1<<31)
#घोषणा AC_PINSENSE_ELDV		(1<<30)	/* ELD valid (HDMI) */

/* EAPD/BTL enable - 32bit */
#घोषणा AC_EAPDBTL_BALANCED		(1<<0)
#घोषणा AC_EAPDBTL_EAPD			(1<<1)
#घोषणा AC_EAPDBTL_LR_SWAP		(1<<2)

/* HDMI ELD data */
#घोषणा AC_ELDD_ELD_VALID		(1<<31)
#घोषणा AC_ELDD_ELD_DATA		0xff

/* HDMI DIP size */
#घोषणा AC_DIPSIZE_ELD_BUF		(1<<3) /* ELD buf size of packet size */
#घोषणा AC_DIPSIZE_PACK_IDX		(0x07<<0) /* packet index */

/* HDMI DIP index */
#घोषणा AC_DIPIDX_PACK_IDX		(0x07<<5) /* packet idnex */
#घोषणा AC_DIPIDX_BYTE_IDX		(0x1f<<0) /* byte index */

/* HDMI DIP xmit (transmit) control */
#घोषणा AC_DIPXMIT_MASK			(0x3<<6)
#घोषणा AC_DIPXMIT_DISABLE		(0x0<<6) /* disable xmit */
#घोषणा AC_DIPXMIT_ONCE			(0x2<<6) /* xmit once then disable */
#घोषणा AC_DIPXMIT_BEST			(0x3<<6) /* best efक्रमt */

/* HDMI content protection (CP) control */
#घोषणा AC_CPCTRL_CES			(1<<9) /* current encryption state */
#घोषणा AC_CPCTRL_READY			(1<<8) /* पढ़ोy bit */
#घोषणा AC_CPCTRL_SUBTAG		(0x1f<<3) /* subtag क्रम unsol-resp */
#घोषणा AC_CPCTRL_STATE			(3<<0) /* current CP request state */

/* Converter channel <-> HDMI slot mapping */
#घोषणा AC_CVTMAP_HDMI_SLOT		(0xf<<0) /* HDMI slot number */
#घोषणा AC_CVTMAP_CHAN			(0xf<<4) /* converter channel number */

/* configuration शेष - 32bit */
#घोषणा AC_DEFCFG_SEQUENCE		(0xf<<0)
#घोषणा AC_DEFCFG_DEF_ASSOC		(0xf<<4)
#घोषणा AC_DEFCFG_ASSOC_SHIFT		4
#घोषणा AC_DEFCFG_MISC			(0xf<<8)
#घोषणा AC_DEFCFG_MISC_SHIFT		8
#घोषणा AC_DEFCFG_MISC_NO_PRESENCE	(1<<0)
#घोषणा AC_DEFCFG_COLOR			(0xf<<12)
#घोषणा AC_DEFCFG_COLOR_SHIFT		12
#घोषणा AC_DEFCFG_CONN_TYPE		(0xf<<16)
#घोषणा AC_DEFCFG_CONN_TYPE_SHIFT	16
#घोषणा AC_DEFCFG_DEVICE		(0xf<<20)
#घोषणा AC_DEFCFG_DEVICE_SHIFT		20
#घोषणा AC_DEFCFG_LOCATION		(0x3f<<24)
#घोषणा AC_DEFCFG_LOCATION_SHIFT	24
#घोषणा AC_DEFCFG_PORT_CONN		(0x3<<30)
#घोषणा AC_DEFCFG_PORT_CONN_SHIFT	30

/* Display pin's device list entry */
#घोषणा AC_DE_PD			(1<<0)
#घोषणा AC_DE_ELDV			(1<<1)
#घोषणा AC_DE_IA			(1<<2)

/* device device types (0x0-0xf) */
क्रमागत अणु
	AC_JACK_LINE_OUT,
	AC_JACK_SPEAKER,
	AC_JACK_HP_OUT,
	AC_JACK_CD,
	AC_JACK_SPDIF_OUT,
	AC_JACK_DIG_OTHER_OUT,
	AC_JACK_MODEM_LINE_SIDE,
	AC_JACK_MODEM_HAND_SIDE,
	AC_JACK_LINE_IN,
	AC_JACK_AUX,
	AC_JACK_MIC_IN,
	AC_JACK_TELEPHONY,
	AC_JACK_SPDIF_IN,
	AC_JACK_DIG_OTHER_IN,
	AC_JACK_OTHER = 0xf,
पूर्ण;

/* jack connection types (0x0-0xf) */
क्रमागत अणु
	AC_JACK_CONN_UNKNOWN,
	AC_JACK_CONN_1_8,
	AC_JACK_CONN_1_4,
	AC_JACK_CONN_ATAPI,
	AC_JACK_CONN_RCA,
	AC_JACK_CONN_OPTICAL,
	AC_JACK_CONN_OTHER_DIGITAL,
	AC_JACK_CONN_OTHER_ANALOG,
	AC_JACK_CONN_DIN,
	AC_JACK_CONN_XLR,
	AC_JACK_CONN_RJ11,
	AC_JACK_CONN_COMB,
	AC_JACK_CONN_OTHER = 0xf,
पूर्ण;

/* jack colors (0x0-0xf) */
क्रमागत अणु
	AC_JACK_COLOR_UNKNOWN,
	AC_JACK_COLOR_BLACK,
	AC_JACK_COLOR_GREY,
	AC_JACK_COLOR_BLUE,
	AC_JACK_COLOR_GREEN,
	AC_JACK_COLOR_RED,
	AC_JACK_COLOR_ORANGE,
	AC_JACK_COLOR_YELLOW,
	AC_JACK_COLOR_PURPLE,
	AC_JACK_COLOR_PINK,
	AC_JACK_COLOR_WHITE = 0xe,
	AC_JACK_COLOR_OTHER,
पूर्ण;

/* Jack location (0x0-0x3f) */
/* common हाल */
क्रमागत अणु
	AC_JACK_LOC_NONE,
	AC_JACK_LOC_REAR,
	AC_JACK_LOC_FRONT,
	AC_JACK_LOC_LEFT,
	AC_JACK_LOC_RIGHT,
	AC_JACK_LOC_TOP,
	AC_JACK_LOC_BOTTOM,
पूर्ण;
/* bits 4-5 */
क्रमागत अणु
	AC_JACK_LOC_EXTERNAL = 0x00,
	AC_JACK_LOC_INTERNAL = 0x10,
	AC_JACK_LOC_SEPARATE = 0x20,
	AC_JACK_LOC_OTHER    = 0x30,
पूर्ण;
क्रमागत अणु
	/* बाह्यal on primary chasis */
	AC_JACK_LOC_REAR_PANEL = 0x07,
	AC_JACK_LOC_DRIVE_BAY,
	/* पूर्णांकernal */
	AC_JACK_LOC_RISER = 0x17,
	AC_JACK_LOC_HDMI,
	AC_JACK_LOC_ATAPI,
	/* others */
	AC_JACK_LOC_MOBILE_IN = 0x37,
	AC_JACK_LOC_MOBILE_OUT,
पूर्ण;

/* Port connectivity (0-3) */
क्रमागत अणु
	AC_JACK_PORT_COMPLEX,
	AC_JACK_PORT_NONE,
	AC_JACK_PORT_FIXED,
	AC_JACK_PORT_BOTH,
पूर्ण;

/* max. codec address */
#घोषणा HDA_MAX_CODEC_ADDRESS	0x0f

#पूर्ण_अगर /* __SOUND_HDA_VERBS_H */
