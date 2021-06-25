<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित WMI_H
#घोषणा WMI_H

काष्ठा wmi_event_txrate अणु
	__be32 txrate;
	काष्ठा अणु
		u8 rssi_thresh;
		u8 per;
	पूर्ण rc_stats;
पूर्ण __packed;

काष्ठा wmi_cmd_hdr अणु
	__be16 command_id;
	__be16 seq_no;
पूर्ण __packed;

काष्ठा wmi_fw_version अणु
	__be16 major;
	__be16 minor;

पूर्ण __packed;

काष्ठा wmi_event_swba अणु
	__be64 tsf;
	u8 beacon_pending;
पूर्ण __packed;

/*
 * 64 - HTC header - WMI header - 1 / txstatus
 * And some other hdr. space is also accounted क्रम.
 * 12 seems to be the magic number.
 */
#घोषणा HTC_MAX_TX_STATUS 12

#घोषणा ATH9K_HTC_TXSTAT_ACK        BIT(0)
#घोषणा ATH9K_HTC_TXSTAT_FILT       BIT(1)
#घोषणा ATH9K_HTC_TXSTAT_RTC_CTS    BIT(2)
#घोषणा ATH9K_HTC_TXSTAT_MCS        BIT(3)
#घोषणा ATH9K_HTC_TXSTAT_CW40       BIT(4)
#घोषणा ATH9K_HTC_TXSTAT_SGI        BIT(5)

/*
 * Legacy rates are indicated as indices.
 * HT rates are indicated as करोt11 numbers.
 * This allows us to resrict the rate field
 * to 4 bits.
 */
#घोषणा ATH9K_HTC_TXSTAT_RATE       0x0f
#घोषणा ATH9K_HTC_TXSTAT_RATE_S     0

#घोषणा ATH9K_HTC_TXSTAT_EPID       0xf0
#घोषणा ATH9K_HTC_TXSTAT_EPID_S     4

काष्ठा __wmi_event_txstatus अणु
	u8 cookie;
	u8 ts_rate; /* Also holds EP ID */
	u8 ts_flags;
पूर्ण;

काष्ठा wmi_event_txstatus अणु
	u8 cnt;
	काष्ठा __wmi_event_txstatus txstatus[HTC_MAX_TX_STATUS];
पूर्ण __packed;

क्रमागत wmi_cmd_id अणु
	WMI_ECHO_CMDID = 0x0001,
	WMI_ACCESS_MEMORY_CMDID,

	/* Commands to Target */
	WMI_GET_FW_VERSION,
	WMI_DISABLE_INTR_CMDID,
	WMI_ENABLE_INTR_CMDID,
	WMI_ATH_INIT_CMDID,
	WMI_ABORT_TXQ_CMDID,
	WMI_STOP_TX_DMA_CMDID,
	WMI_ABORT_TX_DMA_CMDID,
	WMI_DRAIN_TXQ_CMDID,
	WMI_DRAIN_TXQ_ALL_CMDID,
	WMI_START_RECV_CMDID,
	WMI_STOP_RECV_CMDID,
	WMI_FLUSH_RECV_CMDID,
	WMI_SET_MODE_CMDID,
	WMI_NODE_CREATE_CMDID,
	WMI_NODE_REMOVE_CMDID,
	WMI_VAP_REMOVE_CMDID,
	WMI_VAP_CREATE_CMDID,
	WMI_REG_READ_CMDID,
	WMI_REG_WRITE_CMDID,
	WMI_RC_STATE_CHANGE_CMDID,
	WMI_RC_RATE_UPDATE_CMDID,
	WMI_TARGET_IC_UPDATE_CMDID,
	WMI_TX_AGGR_ENABLE_CMDID,
	WMI_TGT_DETACH_CMDID,
	WMI_NODE_UPDATE_CMDID,
	WMI_INT_STATS_CMDID,
	WMI_TX_STATS_CMDID,
	WMI_RX_STATS_CMDID,
	WMI_BITRATE_MASK_CMDID,
	WMI_REG_RMW_CMDID,
पूर्ण;

क्रमागत wmi_event_id अणु
	WMI_TGT_RDY_EVENTID = 0x1001,
	WMI_SWBA_EVENTID,
	WMI_FATAL_EVENTID,
	WMI_TXTO_EVENTID,
	WMI_BMISS_EVENTID,
	WMI_DELBA_EVENTID,
	WMI_TXSTATUS_EVENTID,
पूर्ण;

#घोषणा MAX_CMD_NUMBER 62
#घोषणा MAX_RMW_CMD_NUMBER 15

काष्ठा रेजिस्टर_ग_लिखो अणु
	__be32 reg;
	__be32 val;
पूर्ण;

काष्ठा रेजिस्टर_rmw अणु
	__be32 reg;
	__be32 set;
	__be32 clr;
पूर्ण __packed;

काष्ठा ath9k_htc_tx_event अणु
	पूर्णांक count;
	काष्ठा __wmi_event_txstatus txs;
	काष्ठा list_head list;
पूर्ण;

काष्ठा wmi अणु
	काष्ठा ath9k_htc_priv *drv_priv;
	काष्ठा htc_target *htc;
	क्रमागत htc_endpoपूर्णांक_id ctrl_epid;
	काष्ठा mutex op_mutex;
	काष्ठा completion cmd_रुको;
	u16 last_seq_id;
	काष्ठा sk_buff_head wmi_event_queue;
	काष्ठा tasklet_काष्ठा wmi_event_tasklet;
	u16 tx_seq_id;
	u8 *cmd_rsp_buf;
	u32 cmd_rsp_len;
	bool stopped;

	काष्ठा list_head pending_tx_events;
	spinlock_t event_lock;

	spinlock_t wmi_lock;

	/* multi ग_लिखो section */
	atomic_t mग_लिखो_cnt;
	काष्ठा रेजिस्टर_ग_लिखो multi_ग_लिखो[MAX_CMD_NUMBER];
	u32 multi_ग_लिखो_idx;
	काष्ठा mutex multi_ग_लिखो_mutex;

	/* multi rmw section */
	atomic_t m_rmw_cnt;
	काष्ठा रेजिस्टर_rmw multi_rmw[MAX_RMW_CMD_NUMBER];
	u32 multi_rmw_idx;
	काष्ठा mutex multi_rmw_mutex;

पूर्ण;

काष्ठा wmi *ath9k_init_wmi(काष्ठा ath9k_htc_priv *priv);
पूर्णांक ath9k_wmi_connect(काष्ठा htc_target *htc, काष्ठा wmi *wmi,
		      क्रमागत htc_endpoपूर्णांक_id *wmi_ctrl_epid);
पूर्णांक ath9k_wmi_cmd(काष्ठा wmi *wmi, क्रमागत wmi_cmd_id cmd_id,
		  u8 *cmd_buf, u32 cmd_len,
		  u8 *rsp_buf, u32 rsp_len,
		  u32 समयout);
व्योम ath9k_wmi_event_tasklet(काष्ठा tasklet_काष्ठा *t);
व्योम ath9k_fatal_work(काष्ठा work_काष्ठा *work);
व्योम ath9k_wmi_event_drain(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_stop_wmi(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_destroy_wmi(काष्ठा ath9k_htc_priv *priv);

#घोषणा WMI_CMD(_wmi_cmd)						\
	करो अणु								\
		ret = ath9k_wmi_cmd(priv->wmi, _wmi_cmd, शून्य, 0,	\
				    (u8 *) &cmd_rsp,			\
				    माप(cmd_rsp), HZ*2);		\
	पूर्ण जबतक (0)

#घोषणा WMI_CMD_BUF(_wmi_cmd, _buf)					\
	करो अणु								\
		ret = ath9k_wmi_cmd(priv->wmi, _wmi_cmd,		\
				    (u8 *) _buf, माप(*_buf),		\
				    &cmd_rsp, माप(cmd_rsp), HZ*2);	\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* WMI_H */
