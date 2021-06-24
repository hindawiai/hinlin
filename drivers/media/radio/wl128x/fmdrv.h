<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  FM Driver क्रम Connectivity chip of Texas Instruments.
 *
 *  Common header क्रम all FM driver sub-modules.
 *
 *  Copyright (C) 2011 Texas Instruments
 */

#अगर_अघोषित _FM_DRV_H
#घोषणा _FM_DRV_H

#समावेश <linux/skbuff.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <linux/समयr.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#घोषणा FM_DRV_VERSION            "0.1.1"
#घोषणा FM_DRV_NAME               "ti_fmdrv"
#घोषणा FM_DRV_CARD_SHORT_NAME    "TI FM Radio"
#घोषणा FM_DRV_CARD_LONG_NAME     "Texas Instruments FM Radio"

/* Flag info */
#घोषणा FM_INTTASK_RUNNING            0
#घोषणा FM_INTTASK_SCHEDULE_PENDING   1
#घोषणा FM_FW_DW_INPROGRESS     2
#घोषणा FM_CORE_READY                 3
#घोषणा FM_CORE_TRANSPORT_READY       4
#घोषणा FM_AF_SWITCH_INPROGRESS	      5
#घोषणा FM_CORE_TX_XMITING	      6

#घोषणा FM_TUNE_COMPLETE	      0x1
#घोषणा FM_BAND_LIMIT		      0x2

#घोषणा FM_DRV_TX_TIMEOUT      (5*HZ)	/* 5 seconds */
#घोषणा FM_DRV_RX_SEEK_TIMEOUT (20*HZ)	/* 20 seconds */

#घोषणा fmerr(क्रमmat, ...) \
	prपूर्णांकk(KERN_ERR "fmdrv: " क्रमmat, ## __VA_ARGS__)
#घोषणा fmwarn(क्रमmat, ...) \
	prपूर्णांकk(KERN_WARNING "fmdrv: " क्रमmat, ##__VA_ARGS__)
#अगर_घोषित DEBUG
#घोषणा fmdbg(क्रमmat, ...) \
	prपूर्णांकk(KERN_DEBUG "fmdrv: " क्रमmat, ## __VA_ARGS__)
#अन्यथा /* DEBUG */
#घोषणा fmdbg(क्रमmat, ...) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर
क्रमागत अणु
	FM_MODE_OFF,
	FM_MODE_TX,
	FM_MODE_RX,
	FM_MODE_ENTRY_MAX
पूर्ण;

#घोषणा FM_RX_RDS_INFO_FIELD_MAX	8	/* 4 Group * 2 Bytes */

/* RX RDS data क्रमmat */
काष्ठा fm_rdsdata_क्रमmat अणु
	जोड़ अणु
		काष्ठा अणु
			u8 buff[FM_RX_RDS_INFO_FIELD_MAX];
		पूर्ण groupdatabuff;
		काष्ठा अणु
			u16 pidata;
			u8 blk_b[2];
			u8 blk_c[2];
			u8 blk_d[2];
		पूर्ण groupgeneral;
		काष्ठा अणु
			u16 pidata;
			u8 blk_b[2];
			u8 af[2];
			u8 ps[2];
		पूर्ण group0A;
		काष्ठा अणु
			u16 pi[2];
			u8 blk_b[2];
			u8 ps[2];
		पूर्ण group0B;
	पूर्ण data;
पूर्ण;

/* FM region (Europe/US, Japan) info */
काष्ठा region_info अणु
	u32 chanl_space;
	u32 bot_freq;
	u32 top_freq;
	u8 fm_band;
पूर्ण;
काष्ठा fmdev;
प्रकार व्योम (*पूर्णांक_handler_prototype) (काष्ठा fmdev *);

/* FM Interrupt processing related info */
काष्ठा fm_irq अणु
	u8 stage;
	u16 flag;	/* FM पूर्णांकerrupt flag */
	u16 mask;	/* FM पूर्णांकerrupt mask */
	/* Interrupt process समयout handler */
	काष्ठा समयr_list समयr;
	u8 retry;
	पूर्णांक_handler_prototype *handlers;
पूर्ण;

/* RDS info */
काष्ठा fm_rds अणु
	u8 flag;	/* RX RDS on/off status */
	u8 last_blk_idx;	/* Last received RDS block */

	/* RDS buffer */
	रुको_queue_head_t पढ़ो_queue;
	u32 buf_size;	/* Size is always multiple of 3 */
	u32 wr_idx;
	u32 rd_idx;
	u8 *buff;
पूर्ण;

#घोषणा FM_RDS_MAX_AF_LIST		25

/*
 * Current RX channel Alternate Frequency cache.
 * This info is used to चयन to other freq (AF)
 * when current channel संकेत strength is below RSSI threshold.
 */
काष्ठा tuned_station_info अणु
	u16 picode;
	u32 af_cache[FM_RDS_MAX_AF_LIST];
	u8 afcache_size;
	u8 af_list_max;
पूर्ण;

/* FM RX mode info */
काष्ठा fm_rx अणु
	काष्ठा region_info region;	/* Current selected band */
	u32 freq;	/* Current RX frquency */
	u8 mute_mode;	/* Current mute mode */
	u8 deemphasis_mode; /* Current deemphasis mode */
	/* RF dependent soft mute mode */
	u8 rf_depend_mute;
	u16 volume;	/* Current volume level */
	u16 rssi_threshold;	/* Current RSSI threshold level */
	/* Holds the index of the current AF jump */
	u8 afjump_idx;
	/* Will hold the frequency beक्रमe the jump */
	u32 freq_beक्रमe_jump;
	u8 rds_mode;	/* RDS operation mode (RDS/RDBS) */
	u8 af_mode;	/* Alternate frequency on/off */
	काष्ठा tuned_station_info stat_info;
	काष्ठा fm_rds rds;
पूर्ण;

#घोषणा FMTX_RDS_TXT_STR_SIZE	25
/*
 * FM TX RDS data
 *
 * @ text_type: is the text following PS or RT
 * @ text: radio text string which could either be PS or RT
 * @ af_freq: alternate frequency क्रम Tx
 * TODO: to be declared in application
 */
काष्ठा tx_rds अणु
	u8 text_type;
	u8 text[FMTX_RDS_TXT_STR_SIZE];
	u8 flag;
	u32 af_freq;
पूर्ण;
/*
 * FM TX global data
 *
 * @ pwr_lvl: Power Level of the Transmission from mixer control
 * @ xmit_state: Transmission state = Updated locally upon Start/Stop
 * @ audio_io: i2S/Analog
 * @ tx_frq: Transmission frequency
 */
काष्ठा fmtx_data अणु
	u8 pwr_lvl;
	u8 xmit_state;
	u8 audio_io;
	u8 region;
	u16 aud_mode;
	u32 preemph;
	u32 tx_frq;
	काष्ठा tx_rds rds;
पूर्ण;

/* FM driver operation काष्ठाure */
काष्ठा fmdev अणु
	काष्ठा video_device *radio_dev;	/* V4L2 video device poपूर्णांकer */
	काष्ठा v4l2_device v4l2_dev;	/* V4L2 top level काष्ठा */
	काष्ठा snd_card *card;	/* Card which holds FM mixer controls */
	u16 asci_id;
	spinlock_t rds_buff_lock; /* To protect access to RDS buffer */
	spinlock_t resp_skb_lock; /* To protect access to received SKB */

	दीर्घ flag;		/*  FM driver state machine info */
	पूर्णांक streg_cbdata; /* status of ST registration */

	काष्ठा sk_buff_head rx_q;	/* RX queue */
	काष्ठा tasklet_काष्ठा rx_task;	/* RX Tasklet */

	काष्ठा sk_buff_head tx_q;	/* TX queue */
	काष्ठा tasklet_काष्ठा tx_task;	/* TX Tasklet */
	अचिन्हित दीर्घ last_tx_jअगरfies;	/* Timestamp of last pkt sent */
	atomic_t tx_cnt;	/* Number of packets can send at a समय */

	काष्ठा sk_buff *resp_skb;	/* Response from the chip */
	/* Main task completion handler */
	काष्ठा completion मुख्यtask_comp;
	/* Opcode of last command sent to the chip */
	u8 pre_op;
	/* Handler used क्रम wakeup when response packet is received */
	काष्ठा completion *resp_comp;
	काष्ठा fm_irq irq_info;
	u8 curr_fmmode; /* Current FM chip mode (TX, RX, OFF) */
	काष्ठा fm_rx rx;	/* FM receiver info */
	काष्ठा fmtx_data tx_data;

	/* V4L2 ctrl framework handler*/
	काष्ठा v4l2_ctrl_handler ctrl_handler;

	/* For core assisted locking */
	काष्ठा mutex mutex;
पूर्ण;
#पूर्ण_अगर
