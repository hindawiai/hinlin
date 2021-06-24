<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  FM Driver क्रम Connectivity chip of Texas Instruments.
 *  FM Common module header file
 *
 *  Copyright (C) 2011 Texas Instruments
 */

#अगर_अघोषित _FMDRV_COMMON_H
#घोषणा _FMDRV_COMMON_H

#घोषणा FM_ST_REG_TIMEOUT   msecs_to_jअगरfies(6000)	/* 6 sec */
#घोषणा FM_PKT_LOGICAL_CHAN_NUMBER  0x08   /* Logical channel 8 */

#घोषणा REG_RD       0x1
#घोषणा REG_WR      0x0

काष्ठा fm_reg_table अणु
	u8 opcode;
	u8 type;
	u8 *name;
पूर्ण;

#घोषणा STEREO_GET               0
#घोषणा RSSI_LVL_GET             1
#घोषणा IF_COUNT_GET             2
#घोषणा FLAG_GET                 3
#घोषणा RDS_SYNC_GET             4
#घोषणा RDS_DATA_GET             5
#घोषणा FREQ_SET                 10
#घोषणा AF_FREQ_SET              11
#घोषणा MOST_MODE_SET            12
#घोषणा MOST_BLEND_SET           13
#घोषणा DEMPH_MODE_SET           14
#घोषणा SEARCH_LVL_SET           15
#घोषणा BAND_SET                 16
#घोषणा MUTE_STATUS_SET          17
#घोषणा RDS_PAUSE_LVL_SET        18
#घोषणा RDS_PAUSE_DUR_SET        19
#घोषणा RDS_MEM_SET              20
#घोषणा RDS_BLK_B_SET            21
#घोषणा RDS_MSK_B_SET            22
#घोषणा RDS_PI_MASK_SET          23
#घोषणा RDS_PI_SET               24
#घोषणा RDS_SYSTEM_SET           25
#घोषणा INT_MASK_SET             26
#घोषणा SEARCH_सूची_SET           27
#घोषणा VOLUME_SET               28
#घोषणा AUDIO_ENABLE_SET         29
#घोषणा PCM_MODE_SET             30
#घोषणा I2S_MODE_CONFIG_SET      31
#घोषणा POWER_SET                32
#घोषणा INTX_CONFIG_SET          33
#घोषणा PULL_EN_SET              34
#घोषणा HILO_SET                 35
#घोषणा SWITCH2FREF              36
#घोषणा FREQ_DRIFT_REPORT        37

#घोषणा PCE_GET                  40
#घोषणा FIRM_VER_GET             41
#घोषणा ASIC_VER_GET             42
#घोषणा ASIC_ID_GET              43
#घोषणा MAN_ID_GET               44
#घोषणा TUNER_MODE_SET           45
#घोषणा STOP_SEARCH              46
#घोषणा RDS_CNTRL_SET            47

#घोषणा WRITE_HARDWARE_REG       100
#घोषणा CODE_DOWNLOAD            101
#घोषणा RESET                    102

#घोषणा FM_POWER_MODE            254
#घोषणा FM_INTERRUPT             255

/* Transmitter API */

#घोषणा CHANL_SET                55
#घोषणा CHANL_BW_SET		56
#घोषणा REF_SET                  57
#घोषणा POWER_ENB_SET            90
#घोषणा POWER_ATT_SET            58
#घोषणा POWER_LEV_SET            59
#घोषणा AUDIO_DEV_SET            60
#घोषणा PILOT_DEV_SET            61
#घोषणा RDS_DEV_SET              62
#घोषणा TX_BAND_SET              65
#घोषणा PUPD_SET                 91
#घोषणा AUDIO_IO_SET             63
#घोषणा PREMPH_SET               64
#घोषणा MONO_SET                 66
#घोषणा MUTE                     92
#घोषणा MPX_LMT_ENABLE           67
#घोषणा PI_SET                   93
#घोषणा ECC_SET                  69
#घोषणा PTY                      70
#घोषणा AF                       71
#घोषणा DISPLAY_MODE             74
#घोषणा RDS_REP_SET              77
#घोषणा RDS_CONFIG_DATA_SET      98
#घोषणा RDS_DATA_SET             99
#घोषणा RDS_DATA_ENB             94
#घोषणा TA_SET                   78
#घोषणा TP_SET                   79
#घोषणा DI_SET                   80
#घोषणा MS_SET                   81
#घोषणा PS_SCROLL_SPEED          82
#घोषणा TX_AUDIO_LEVEL_TEST      96
#घोषणा TX_AUDIO_LEVEL_TEST_THRESHOLD    73
#घोषणा TX_AUDIO_INPUT_LEVEL_RANGE_SET   54
#घोषणा RX_ANTENNA_SELECT        87
#घोषणा I2C_DEV_ADDR_SET         86
#घोषणा REF_ERR_CALIB_PARAM_SET          88
#घोषणा REF_ERR_CALIB_PERIODICITY_SET    89
#घोषणा SOC_INT_TRIGGER                  52
#घोषणा SOC_AUDIO_PATH_SET               83
#घोषणा SOC_PCMI_OVERRIDE                84
#घोषणा SOC_I2S_OVERRIDE         85
#घोषणा RSSI_BLOCK_SCAN_FREQ_SET 95
#घोषणा RSSI_BLOCK_SCAN_START    97
#घोषणा RSSI_BLOCK_SCAN_DATA_GET  5
#घोषणा READ_FMANT_TUNE_VALUE            104

/* SKB helpers */
काष्ठा fm_skb_cb अणु
	__u8 fm_op;
	काष्ठा completion *completion;
पूर्ण;

#घोषणा fm_cb(skb) ((काष्ठा fm_skb_cb *)(skb->cb))

/* FM Channel-8 command message क्रमmat */
काष्ठा fm_cmd_msg_hdr अणु
	__u8 hdr;		/* Logical Channel-8 */
	__u8 len;		/* Number of bytes follows */
	__u8 op;		/* FM Opcode */
	__u8 rd_wr;		/* Read/Write command */
	__u8 dlen;		/* Length of payload */
पूर्ण __attribute__ ((packed));

#घोषणा FM_CMD_MSG_HDR_SIZE    5	/* माप(काष्ठा fm_cmd_msg_hdr) */

/* FM Channel-8 event messgage क्रमmat */
काष्ठा fm_event_msg_hdr अणु
	__u8 header;		/* Logical Channel-8 */
	__u8 len;		/* Number of bytes follows */
	__u8 status;		/* Event status */
	__u8 num_fm_hci_cmds;	/* Number of pkts the host allowed to send */
	__u8 op;		/* FM Opcode */
	__u8 rd_wr;		/* Read/Write command */
	__u8 dlen;		/* Length of payload */
पूर्ण __attribute__ ((packed));

#घोषणा FM_EVT_MSG_HDR_SIZE     7	/* माप(काष्ठा fm_event_msg_hdr) */

/* TI's magic number in firmware file */
#घोषणा FM_FW_खाता_HEADER_MAGIC	     0x42535442

#घोषणा FM_ENABLE   1
#घोषणा FM_DISABLE  0

/* FLAG_GET रेजिस्टर bits */
#घोषणा FM_FR_EVENT		BIT(0)
#घोषणा FM_BL_EVENT		BIT(1)
#घोषणा FM_RDS_EVENT		BIT(2)
#घोषणा FM_BBLK_EVENT		BIT(3)
#घोषणा FM_LSYNC_EVENT		BIT(4)
#घोषणा FM_LEV_EVENT		BIT(5)
#घोषणा FM_IFFR_EVENT		BIT(6)
#घोषणा FM_PI_EVENT		BIT(7)
#घोषणा FM_PD_EVENT		BIT(8)
#घोषणा FM_STIC_EVENT		BIT(9)
#घोषणा FM_MAL_EVENT		BIT(10)
#घोषणा FM_POW_ENB_EVENT	BIT(11)

/*
 * Firmware files of FM. ASIC ID and ASIC version will be appened to this,
 * later.
 */
#घोषणा FM_FMC_FW_खाता_START      ("fmc_ch8")
#घोषणा FM_RX_FW_खाता_START       ("fm_rx_ch8")
#घोषणा FM_TX_FW_खाता_START       ("fm_tx_ch8")

#घोषणा FM_UNDEFINED_FREQ		   0xFFFFFFFF

/* Band types */
#घोषणा FM_BAND_EUROPE_US	0
#घोषणा FM_BAND_JAPAN		1

/* Seek directions */
#घोषणा FM_SEARCH_सूचीECTION_DOWN	0
#घोषणा FM_SEARCH_सूचीECTION_UP		1

/* Tunner modes */
#घोषणा FM_TUNER_STOP_SEARCH_MODE	0
#घोषणा FM_TUNER_PRESET_MODE		1
#घोषणा FM_TUNER_AUTONOMOUS_SEARCH_MODE	2
#घोषणा FM_TUNER_AF_JUMP_MODE		3

/* Min and Max volume */
#घोषणा FM_RX_VOLUME_MIN	0
#घोषणा FM_RX_VOLUME_MAX	70

/* Volume gain step */
#घोषणा FM_RX_VOLUME_GAIN_STEP	0x370

/* Mute modes */
#घोषणा	FM_MUTE_ON		0
#घोषणा FM_MUTE_OFF		1
#घोषणा	FM_MUTE_ATTENUATE	2

#घोषणा FM_RX_UNMUTE_MODE		0x00
#घोषणा FM_RX_RF_DEP_MODE		0x01
#घोषणा FM_RX_AC_MUTE_MODE		0x02
#घोषणा FM_RX_HARD_MUTE_LEFT_MODE	0x04
#घोषणा FM_RX_HARD_MUTE_RIGHT_MODE	0x08
#घोषणा FM_RX_SOFT_MUTE_FORCE_MODE	0x10

/* RF dependent mute mode */
#घोषणा FM_RX_RF_DEPENDENT_MUTE_ON	1
#घोषणा FM_RX_RF_DEPENDENT_MUTE_OFF	0

/* RSSI threshold min and max */
#घोषणा FM_RX_RSSI_THRESHOLD_MIN	-128
#घोषणा FM_RX_RSSI_THRESHOLD_MAX	127

/* Stereo/Mono mode */
#घोषणा FM_STEREO_MODE		0
#घोषणा FM_MONO_MODE		1
#घोषणा FM_STEREO_SOFT_BLEND	1

/* FM RX De-emphasis filter modes */
#घोषणा FM_RX_EMPHASIS_FILTER_50_USEC	0
#घोषणा FM_RX_EMPHASIS_FILTER_75_USEC	1

/* FM RDS modes */
#घोषणा FM_RDS_DISABLE	0
#घोषणा FM_RDS_ENABLE	1

#घोषणा FM_NO_PI_CODE	0

/* FM and RX RDS block enable/disable  */
#घोषणा FM_RX_PWR_SET_FM_ON_RDS_OFF		0x1
#घोषणा FM_RX_PWR_SET_FM_AND_RDS_BLK_ON		0x3
#घोषणा FM_RX_PWR_SET_FM_AND_RDS_BLK_OFF	0x0

/* RX RDS */
#घोषणा FM_RX_RDS_FLUSH_FIFO		0x1
#घोषणा FM_RX_RDS_FIFO_THRESHOLD	64	/* tuples */
#घोषणा FM_RDS_BLK_SIZE		3	/* 3 bytes */

/* RDS block types */
#घोषणा FM_RDS_BLOCK_A		0
#घोषणा FM_RDS_BLOCK_B		1
#घोषणा FM_RDS_BLOCK_C		2
#घोषणा FM_RDS_BLOCK_Ctag	3
#घोषणा FM_RDS_BLOCK_D		4
#घोषणा FM_RDS_BLOCK_E		5

#घोषणा FM_RDS_BLK_IDX_A		0
#घोषणा FM_RDS_BLK_IDX_B		1
#घोषणा FM_RDS_BLK_IDX_C		2
#घोषणा FM_RDS_BLK_IDX_D		3
#घोषणा FM_RDS_BLK_IDX_UNKNOWN	0xF0

#घोषणा FM_RDS_STATUS_ERR_MASK	0x18

/*
 * Represents an RDS group type & version.
 * There are 15 groups, each group has 2 versions: A and B.
 */
#घोषणा FM_RDS_GROUP_TYPE_MASK_0A	    BIT(0)
#घोषणा FM_RDS_GROUP_TYPE_MASK_0B	    BIT(1)
#घोषणा FM_RDS_GROUP_TYPE_MASK_1A	    BIT(2)
#घोषणा FM_RDS_GROUP_TYPE_MASK_1B	    BIT(3)
#घोषणा FM_RDS_GROUP_TYPE_MASK_2A	    BIT(4)
#घोषणा FM_RDS_GROUP_TYPE_MASK_2B	    BIT(5)
#घोषणा FM_RDS_GROUP_TYPE_MASK_3A	    BIT(6)
#घोषणा FM_RDS_GROUP_TYPE_MASK_3B	    BIT(7)
#घोषणा FM_RDS_GROUP_TYPE_MASK_4A	    BIT(8)
#घोषणा FM_RDS_GROUP_TYPE_MASK_4B	    BIT(9)
#घोषणा FM_RDS_GROUP_TYPE_MASK_5A	    BIT(10)
#घोषणा FM_RDS_GROUP_TYPE_MASK_5B	    BIT(11)
#घोषणा FM_RDS_GROUP_TYPE_MASK_6A	    BIT(12)
#घोषणा FM_RDS_GROUP_TYPE_MASK_6B	    BIT(13)
#घोषणा FM_RDS_GROUP_TYPE_MASK_7A	    BIT(14)
#घोषणा FM_RDS_GROUP_TYPE_MASK_7B	    BIT(15)
#घोषणा FM_RDS_GROUP_TYPE_MASK_8A	    BIT(16)
#घोषणा FM_RDS_GROUP_TYPE_MASK_8B	    BIT(17)
#घोषणा FM_RDS_GROUP_TYPE_MASK_9A	    BIT(18)
#घोषणा FM_RDS_GROUP_TYPE_MASK_9B	    BIT(19)
#घोषणा FM_RDS_GROUP_TYPE_MASK_10A	    BIT(20)
#घोषणा FM_RDS_GROUP_TYPE_MASK_10B	    BIT(21)
#घोषणा FM_RDS_GROUP_TYPE_MASK_11A	    BIT(22)
#घोषणा FM_RDS_GROUP_TYPE_MASK_11B	    BIT(23)
#घोषणा FM_RDS_GROUP_TYPE_MASK_12A	    BIT(24)
#घोषणा FM_RDS_GROUP_TYPE_MASK_12B	    BIT(25)
#घोषणा FM_RDS_GROUP_TYPE_MASK_13A	    BIT(26)
#घोषणा FM_RDS_GROUP_TYPE_MASK_13B	    BIT(27)
#घोषणा FM_RDS_GROUP_TYPE_MASK_14A	    BIT(28)
#घोषणा FM_RDS_GROUP_TYPE_MASK_14B	    BIT(29)
#घोषणा FM_RDS_GROUP_TYPE_MASK_15A	    BIT(30)
#घोषणा FM_RDS_GROUP_TYPE_MASK_15B	    BIT(31)

/* RX Alternate Frequency info */
#घोषणा FM_RDS_MIN_AF			  1
#घोषणा FM_RDS_MAX_AF			204
#घोषणा FM_RDS_MAX_AF_JAPAN		140
#घोषणा FM_RDS_1_AF_FOLLOWS		225
#घोषणा FM_RDS_25_AF_FOLLOWS		249

/* RDS प्रणाली type (RDS/RBDS) */
#घोषणा FM_RDS_SYSTEM_RDS		0
#घोषणा FM_RDS_SYSTEM_RBDS		1

/* AF on/off */
#घोषणा FM_RX_RDS_AF_SWITCH_MODE_ON	1
#घोषणा FM_RX_RDS_AF_SWITCH_MODE_OFF	0

/* Retry count when पूर्णांकerrupt process goes wrong */
#घोषणा FM_IRQ_TIMEOUT_RETRY_MAX	5	/* 5 बार */

/* Audio IO set values */
#घोषणा FM_RX_AUDIO_ENABLE_I2S	0x01
#घोषणा FM_RX_AUDIO_ENABLE_ANALOG	0x02
#घोषणा FM_RX_AUDIO_ENABLE_I2S_AND_ANALOG	0x03
#घोषणा FM_RX_AUDIO_ENABLE_DISABLE	0x00

/* HI/LO set values */
#घोषणा FM_RX_IFFREQ_TO_HI_SIDE		0x0
#घोषणा FM_RX_IFFREQ_TO_LO_SIDE		0x1
#घोषणा FM_RX_IFFREQ_HILO_AUTOMATIC	0x2

/*
 * Default RX mode configuration. Chip will be configured
 * with this शेष values after loading RX firmware.
 */
#घोषणा FM_DEFAULT_RX_VOLUME		10
#घोषणा FM_DEFAULT_RSSI_THRESHOLD	3

/* Range क्रम TX घातer level in units क्रम dB/uV */
#घोषणा FM_PWR_LVL_LOW			91
#घोषणा FM_PWR_LVL_HIGH			122

/* Chip specअगरic शेष TX घातer level value */
#घोषणा FM_PWR_LVL_DEF			4

/* FM TX Pre-emphasis filter values */
#घोषणा FM_TX_PREEMPH_OFF		1
#घोषणा FM_TX_PREEMPH_50US		0
#घोषणा FM_TX_PREEMPH_75US		2

/* FM TX antenna impedance values */
#घोषणा FM_TX_ANT_IMP_50		0
#घोषणा FM_TX_ANT_IMP_200		1
#घोषणा FM_TX_ANT_IMP_500		2

/* Functions exported by FM common sub-module */
पूर्णांक fmc_prepare(काष्ठा fmdev *);
पूर्णांक fmc_release(काष्ठा fmdev *);

व्योम fmc_update_region_info(काष्ठा fmdev *, u8);
पूर्णांक fmc_send_cmd(काष्ठा fmdev *, u8, u16,
				व्योम *, अचिन्हित पूर्णांक, व्योम *, पूर्णांक *);
पूर्णांक fmc_is_rds_data_available(काष्ठा fmdev *, काष्ठा file *,
				काष्ठा poll_table_काष्ठा *);
पूर्णांक fmc_transfer_rds_from_पूर्णांकernal_buff(काष्ठा fmdev *, काष्ठा file *,
					u8 __user *, माप_प्रकार);

पूर्णांक fmc_set_freq(काष्ठा fmdev *, u32);
पूर्णांक fmc_set_mode(काष्ठा fmdev *, u8);
पूर्णांक fmc_set_region(काष्ठा fmdev *, u8);
पूर्णांक fmc_set_mute_mode(काष्ठा fmdev *, u8);
पूर्णांक fmc_set_stereo_mono(काष्ठा fmdev *, u16);
पूर्णांक fmc_set_rds_mode(काष्ठा fmdev *, u8);

पूर्णांक fmc_get_freq(काष्ठा fmdev *, u32 *);
पूर्णांक fmc_get_region(काष्ठा fmdev *, u8 *);
पूर्णांक fmc_get_mode(काष्ठा fmdev *, u8 *);

/*
 * channel spacing
 */
#घोषणा FM_CHANNEL_SPACING_50KHZ 1
#घोषणा FM_CHANNEL_SPACING_100KHZ 2
#घोषणा FM_CHANNEL_SPACING_200KHZ 4
#घोषणा FM_FREQ_MUL 50

#पूर्ण_अगर

