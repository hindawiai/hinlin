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

#अगर_अघोषित AR9003_MCI_H
#घोषणा AR9003_MCI_H

#घोषणा MCI_FLAG_DISABLE_TIMESTAMP      0x00000001      /* Disable समय stamp */
#घोषणा MCI_RECOVERY_DUR_TSF		(100 * 1000)    /* 100 ms */

/* Default remote BT device MCI COEX version */
#घोषणा MCI_GPM_COEX_MAJOR_VERSION_DEFAULT  3
#घोषणा MCI_GPM_COEX_MINOR_VERSION_DEFAULT  0

/* Local WLAN MCI COEX version */
#घोषणा MCI_GPM_COEX_MAJOR_VERSION_WLAN     3
#घोषणा MCI_GPM_COEX_MINOR_VERSION_WLAN     0

क्रमागत mci_gpm_coex_query_type अणु
	MCI_GPM_COEX_QUERY_BT_ALL_INFO      = BIT(0),
	MCI_GPM_COEX_QUERY_BT_TOPOLOGY      = BIT(1),
	MCI_GPM_COEX_QUERY_BT_DEBUG         = BIT(2),
पूर्ण;

क्रमागत mci_gpm_coex_halt_bt_gpm अणु
	MCI_GPM_COEX_BT_GPM_UNHALT,
	MCI_GPM_COEX_BT_GPM_HALT
पूर्ण;

क्रमागत mci_gpm_coex_bt_update_flags_op अणु
	MCI_GPM_COEX_BT_FLAGS_READ,
	MCI_GPM_COEX_BT_FLAGS_SET,
	MCI_GPM_COEX_BT_FLAGS_CLEAR
पूर्ण;

#घोषणा MCI_NUM_BT_CHANNELS     79

#घोषणा MCI_BT_MCI_FLAGS_UPDATE_CORR          0x00000002
#घोषणा MCI_BT_MCI_FLAGS_UPDATE_HDR           0x00000004
#घोषणा MCI_BT_MCI_FLAGS_UPDATE_PLD           0x00000008
#घोषणा MCI_BT_MCI_FLAGS_LNA_CTRL             0x00000010
#घोषणा MCI_BT_MCI_FLAGS_DEBUG                0x00000020
#घोषणा MCI_BT_MCI_FLAGS_SCHED_MSG            0x00000040
#घोषणा MCI_BT_MCI_FLAGS_CONT_MSG             0x00000080
#घोषणा MCI_BT_MCI_FLAGS_COEX_GPM             0x00000100
#घोषणा MCI_BT_MCI_FLAGS_CPU_INT_MSG          0x00000200
#घोषणा MCI_BT_MCI_FLAGS_MCI_MODE             0x00000400
#घोषणा MCI_BT_MCI_FLAGS_AR9462_MODE          0x00001000
#घोषणा MCI_BT_MCI_FLAGS_OTHER                0x00010000

#घोषणा MCI_DEFAULT_BT_MCI_FLAGS              0x00011dde

#घोषणा MCI_TOGGLE_BT_MCI_FLAGS  (MCI_BT_MCI_FLAGS_UPDATE_CORR | \
				  MCI_BT_MCI_FLAGS_UPDATE_HDR  | \
				  MCI_BT_MCI_FLAGS_UPDATE_PLD  | \
				  MCI_BT_MCI_FLAGS_MCI_MODE)

#घोषणा MCI_2G_FLAGS_CLEAR_MASK   0x00000000
#घोषणा MCI_2G_FLAGS_SET_MASK     MCI_TOGGLE_BT_MCI_FLAGS
#घोषणा MCI_2G_FLAGS              MCI_DEFAULT_BT_MCI_FLAGS

#घोषणा MCI_5G_FLAGS_CLEAR_MASK   MCI_TOGGLE_BT_MCI_FLAGS
#घोषणा MCI_5G_FLAGS_SET_MASK     0x00000000
#घोषणा MCI_5G_FLAGS              (MCI_DEFAULT_BT_MCI_FLAGS & \
				   ~MCI_TOGGLE_BT_MCI_FLAGS)

/*
 * Default value क्रम AR9462 is 0x00002201
 */
#घोषणा ATH_MCI_CONFIG_CONCUR_TX            0x00000003
#घोषणा ATH_MCI_CONFIG_MCI_OBS_MCI          0x00000004
#घोषणा ATH_MCI_CONFIG_MCI_OBS_TXRX         0x00000008
#घोषणा ATH_MCI_CONFIG_MCI_OBS_BT           0x00000010
#घोषणा ATH_MCI_CONFIG_DISABLE_MCI_CAL      0x00000020
#घोषणा ATH_MCI_CONFIG_DISABLE_OSLA         0x00000040
#घोषणा ATH_MCI_CONFIG_DISABLE_FTP_STOMP    0x00000080
#घोषणा ATH_MCI_CONFIG_AGGR_THRESH          0x00000700
#घोषणा ATH_MCI_CONFIG_AGGR_THRESH_S        8
#घोषणा ATH_MCI_CONFIG_DISABLE_AGGR_THRESH  0x00000800
#घोषणा ATH_MCI_CONFIG_CLK_DIV              0x00003000
#घोषणा ATH_MCI_CONFIG_CLK_DIV_S            12
#घोषणा ATH_MCI_CONFIG_DISABLE_TUNING       0x00004000
#घोषणा ATH_MCI_CONFIG_DISABLE_AIC          0x00008000
#घोषणा ATH_MCI_CONFIG_AIC_CAL_NUM_CHAN     0x007f0000
#घोषणा ATH_MCI_CONFIG_AIC_CAL_NUM_CHAN_S   16
#घोषणा ATH_MCI_CONFIG_NO_QUIET_ACK         0x00800000
#घोषणा ATH_MCI_CONFIG_NO_QUIET_ACK_S       23
#घोषणा ATH_MCI_CONFIG_ANT_ARCH             0x07000000
#घोषणा ATH_MCI_CONFIG_ANT_ARCH_S           24
#घोषणा ATH_MCI_CONFIG_FORCE_QUIET_ACK      0x08000000
#घोषणा ATH_MCI_CONFIG_FORCE_QUIET_ACK_S    27
#घोषणा ATH_MCI_CONFIG_FORCE_2CHAIN_ACK     0x10000000
#घोषणा ATH_MCI_CONFIG_MCI_STAT_DBG         0x20000000
#घोषणा ATH_MCI_CONFIG_MCI_WEIGHT_DBG       0x40000000
#घोषणा ATH_MCI_CONFIG_DISABLE_MCI          0x80000000

#घोषणा ATH_MCI_CONFIG_MCI_OBS_MASK     (ATH_MCI_CONFIG_MCI_OBS_MCI  | \
					 ATH_MCI_CONFIG_MCI_OBS_TXRX | \
					 ATH_MCI_CONFIG_MCI_OBS_BT)

#घोषणा ATH_MCI_CONFIG_MCI_OBS_GPIO     0x0000002F

#घोषणा ATH_MCI_ANT_ARCH_1_ANT_PA_LNA_NON_SHARED 0x00
#घोषणा ATH_MCI_ANT_ARCH_1_ANT_PA_LNA_SHARED     0x01
#घोषणा ATH_MCI_ANT_ARCH_2_ANT_PA_LNA_NON_SHARED 0x02
#घोषणा ATH_MCI_ANT_ARCH_2_ANT_PA_LNA_SHARED     0x03
#घोषणा ATH_MCI_ANT_ARCH_3_ANT                   0x04

#घोषणा MCI_ANT_ARCH_PA_LNA_SHARED(mci)					\
	((MS(mci->config, ATH_MCI_CONFIG_ANT_ARCH) == ATH_MCI_ANT_ARCH_1_ANT_PA_LNA_SHARED) || \
	 (MS(mci->config, ATH_MCI_CONFIG_ANT_ARCH) == ATH_MCI_ANT_ARCH_2_ANT_PA_LNA_SHARED))

क्रमागत mci_message_header अणु		/* length of payload */
	MCI_LNA_CTRL     = 0x10,        /* len = 0 */
	MCI_CONT_NACK    = 0x20,        /* len = 0 */
	MCI_CONT_INFO    = 0x30,        /* len = 4 */
	MCI_CONT_RST     = 0x40,        /* len = 0 */
	MCI_SCHD_INFO    = 0x50,        /* len = 16 */
	MCI_CPU_INT      = 0x60,        /* len = 4 */
	MCI_SYS_WAKING   = 0x70,        /* len = 0 */
	MCI_GPM          = 0x80,        /* len = 16 */
	MCI_LNA_INFO     = 0x90,        /* len = 1 */
	MCI_LNA_STATE    = 0x94,
	MCI_LNA_TAKE     = 0x98,
	MCI_LNA_TRANS    = 0x9c,
	MCI_SYS_SLEEPING = 0xa0,        /* len = 0 */
	MCI_REQ_WAKE     = 0xc0,        /* len = 0 */
	MCI_DEBUG_16     = 0xfe,        /* len = 2 */
	MCI_REMOTE_RESET = 0xff         /* len = 16 */
पूर्ण;

क्रमागत ath_mci_gpm_coex_profile_type अणु
	MCI_GPM_COEX_PROखाता_UNKNOWN,
	MCI_GPM_COEX_PROखाता_RFCOMM,
	MCI_GPM_COEX_PROखाता_A2DP,
	MCI_GPM_COEX_PROखाता_HID,
	MCI_GPM_COEX_PROखाता_BNEP,
	MCI_GPM_COEX_PROखाता_VOICE,
	MCI_GPM_COEX_PROखाता_A2DPVO,
	MCI_GPM_COEX_PROखाता_MAX
पूर्ण;

/* MCI GPM/Coex opcode/type definitions */
क्रमागत अणु
	MCI_GPM_COEX_W_GPM_PAYLOAD      = 1,
	MCI_GPM_COEX_B_GPM_TYPE         = 4,
	MCI_GPM_COEX_B_GPM_OPCODE       = 5,
	/* MCI_GPM_WLAN_CAL_REQ, MCI_GPM_WLAN_CAL_DONE */
	MCI_GPM_WLAN_CAL_W_SEQUENCE     = 2,

	/* MCI_GPM_COEX_VERSION_QUERY */
	/* MCI_GPM_COEX_VERSION_RESPONSE */
	MCI_GPM_COEX_B_MAJOR_VERSION    = 6,
	MCI_GPM_COEX_B_MINOR_VERSION    = 7,
	/* MCI_GPM_COEX_STATUS_QUERY */
	MCI_GPM_COEX_B_BT_BITMAP        = 6,
	MCI_GPM_COEX_B_WLAN_BITMAP      = 7,
	/* MCI_GPM_COEX_HALT_BT_GPM */
	MCI_GPM_COEX_B_HALT_STATE       = 6,
	/* MCI_GPM_COEX_WLAN_CHANNELS */
	MCI_GPM_COEX_B_CHANNEL_MAP      = 6,
	/* MCI_GPM_COEX_BT_PROखाता_INFO */
	MCI_GPM_COEX_B_PROखाता_TYPE     = 6,
	MCI_GPM_COEX_B_PROखाता_LINKID   = 7,
	MCI_GPM_COEX_B_PROखाता_STATE    = 8,
	MCI_GPM_COEX_B_PROखाता_ROLE     = 9,
	MCI_GPM_COEX_B_PROखाता_RATE     = 10,
	MCI_GPM_COEX_B_PROखाता_VOTYPE   = 11,
	MCI_GPM_COEX_H_PROखाता_T        = 12,
	MCI_GPM_COEX_B_PROखाता_W        = 14,
	MCI_GPM_COEX_B_PROखाता_A        = 15,
	/* MCI_GPM_COEX_BT_STATUS_UPDATE */
	MCI_GPM_COEX_B_STATUS_TYPE      = 6,
	MCI_GPM_COEX_B_STATUS_LINKID    = 7,
	MCI_GPM_COEX_B_STATUS_STATE     = 8,
	/* MCI_GPM_COEX_BT_UPDATE_FLAGS */
	MCI_GPM_COEX_W_BT_FLAGS         = 6,
	MCI_GPM_COEX_B_BT_FLAGS_OP      = 10
पूर्ण;

क्रमागत mci_gpm_subtype अणु
	MCI_GPM_BT_CAL_REQ      = 0,
	MCI_GPM_BT_CAL_GRANT    = 1,
	MCI_GPM_BT_CAL_DONE     = 2,
	MCI_GPM_WLAN_CAL_REQ    = 3,
	MCI_GPM_WLAN_CAL_GRANT  = 4,
	MCI_GPM_WLAN_CAL_DONE   = 5,
	MCI_GPM_COEX_AGENT      = 0x0c,
	MCI_GPM_RSVD_PATTERN    = 0xfe,
	MCI_GPM_RSVD_PATTERN32  = 0xfefefefe,
	MCI_GPM_BT_DEBUG        = 0xff
पूर्ण;

क्रमागत mci_bt_state अणु
	MCI_BT_SLEEP,
	MCI_BT_AWAKE,
	MCI_BT_CAL_START,
	MCI_BT_CAL
पूर्ण;

क्रमागत mci_ps_state अणु
	MCI_PS_DISABLE,
	MCI_PS_ENABLE,
	MCI_PS_ENABLE_OFF,
	MCI_PS_ENABLE_ON
पूर्ण;

/* Type of state query */
क्रमागत mci_state_type अणु
	MCI_STATE_ENABLE,
	MCI_STATE_INIT_GPM_OFFSET,
	MCI_STATE_CHECK_GPM_OFFSET,
	MCI_STATE_NEXT_GPM_OFFSET,
	MCI_STATE_LAST_GPM_OFFSET,
	MCI_STATE_BT,
	MCI_STATE_SET_BT_SLEEP,
	MCI_STATE_SET_BT_AWAKE,
	MCI_STATE_SET_BT_CAL_START,
	MCI_STATE_SET_BT_CAL,
	MCI_STATE_LAST_SCHD_MSG_OFFSET,
	MCI_STATE_REMOTE_SLEEP,
	MCI_STATE_CONT_STATUS,
	MCI_STATE_RESET_REQ_WAKE,
	MCI_STATE_SEND_WLAN_COEX_VERSION,
	MCI_STATE_SET_BT_COEX_VERSION,
	MCI_STATE_SEND_WLAN_CHANNELS,
	MCI_STATE_SEND_VERSION_QUERY,
	MCI_STATE_SEND_STATUS_QUERY,
	MCI_STATE_NEED_FLUSH_BT_INFO,
	MCI_STATE_SET_CONCUR_TX_PRI,
	MCI_STATE_RECOVER_RX,
	MCI_STATE_NEED_FTP_STOMP,
	MCI_STATE_NEED_TUNING,
	MCI_STATE_NEED_STAT_DEBUG,
	MCI_STATE_SHARED_CHAIN_CONCUR_TX,
	MCI_STATE_AIC_CAL,
	MCI_STATE_AIC_START,
	MCI_STATE_AIC_CAL_RESET,
	MCI_STATE_AIC_CAL_SINGLE,
	MCI_STATE_IS_AR9462,
	MCI_STATE_IS_AR9565_1ANT,
	MCI_STATE_IS_AR9565_2ANT,
	MCI_STATE_WLAN_WEAK_SIGNAL,
	MCI_STATE_SET_WLAN_PS_STATE,
	MCI_STATE_GET_WLAN_PS_STATE,
	MCI_STATE_DEBUG,
	MCI_STATE_STAT_DEBUG,
	MCI_STATE_ALLOW_FCS,
	MCI_STATE_SET_2G_CONTENTION,
	MCI_STATE_MAX
पूर्ण;

क्रमागत mci_gpm_coex_opcode अणु
	MCI_GPM_COEX_VERSION_QUERY,
	MCI_GPM_COEX_VERSION_RESPONSE,
	MCI_GPM_COEX_STATUS_QUERY,
	MCI_GPM_COEX_HALT_BT_GPM,
	MCI_GPM_COEX_WLAN_CHANNELS,
	MCI_GPM_COEX_BT_PROखाता_INFO,
	MCI_GPM_COEX_BT_STATUS_UPDATE,
	MCI_GPM_COEX_BT_UPDATE_FLAGS,
	MCI_GPM_COEX_NOOP,
पूर्ण;

#घोषणा MCI_GPM_NOMORE  0
#घोषणा MCI_GPM_MORE    1
#घोषणा MCI_GPM_INVALID 0xffffffff

#घोषणा MCI_GPM_RECYCLE(_p_gpm)	करो अणु			  \
	*(((u32 *)_p_gpm) + MCI_GPM_COEX_W_GPM_PAYLOAD) = \
				MCI_GPM_RSVD_PATTERN32;   \
पूर्ण जबतक (0)

#घोषणा MCI_GPM_TYPE(_p_gpm)	\
	(*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_TYPE) & 0xff)

#घोषणा MCI_GPM_OPCODE(_p_gpm)	\
	(*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_OPCODE) & 0xff)

#घोषणा MCI_GPM_SET_CAL_TYPE(_p_gpm, _cal_type)	करो अणु			   \
	*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_TYPE) = (_cal_type) & 0xff;\
पूर्ण जबतक (0)

#घोषणा MCI_GPM_SET_TYPE_OPCODE(_p_gpm, _type, _opcode) करो अणु		   \
	*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_TYPE) = (_type) & 0xff;	   \
	*(((u8 *)(_p_gpm)) + MCI_GPM_COEX_B_GPM_OPCODE) = (_opcode) & 0xff;\
पूर्ण जबतक (0)

#घोषणा MCI_GPM_IS_CAL_TYPE(_type) ((_type) <= MCI_GPM_WLAN_CAL_DONE)

/*
 * Functions that are available to the MCI driver core.
 */
bool ar9003_mci_send_message(काष्ठा ath_hw *ah, u8 header, u32 flag,
			     u32 *payload, u8 len, bool रुको_करोne,
			     bool check_bt);
u32 ar9003_mci_state(काष्ठा ath_hw *ah, u32 state_type);
पूर्णांक ar9003_mci_setup(काष्ठा ath_hw *ah, u32 gpm_addr, व्योम *gpm_buf,
		     u16 len, u32 sched_addr);
व्योम ar9003_mci_cleanup(काष्ठा ath_hw *ah);
व्योम ar9003_mci_get_पूर्णांकerrupt(काष्ठा ath_hw *ah, u32 *raw_पूर्णांकr,
			      u32 *rx_msg_पूर्णांकr);
u32 ar9003_mci_get_next_gpm_offset(काष्ठा ath_hw *ah, u32 *more);
व्योम ar9003_mci_set_bt_version(काष्ठा ath_hw *ah, u8 major, u8 minor);
व्योम ar9003_mci_send_wlan_channels(काष्ठा ath_hw *ah);
/*
 * These functions are used by ath9k_hw.
 */

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT

व्योम ar9003_mci_stop_bt(काष्ठा ath_hw *ah, bool save_fullsleep);
व्योम ar9003_mci_init_cal_req(काष्ठा ath_hw *ah, bool *is_reusable);
व्योम ar9003_mci_init_cal_करोne(काष्ठा ath_hw *ah);
व्योम ar9003_mci_set_full_sleep(काष्ठा ath_hw *ah);
व्योम ar9003_mci_2g5g_चयन(काष्ठा ath_hw *ah, bool क्रमce);
व्योम ar9003_mci_check_bt(काष्ठा ath_hw *ah);
bool ar9003_mci_start_reset(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan);
पूर्णांक ar9003_mci_end_reset(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			 काष्ठा ath9k_hw_cal_data *caldata);
पूर्णांक ar9003_mci_reset(काष्ठा ath_hw *ah, bool en_पूर्णांक, bool is_2g,
		     bool is_full_sleep);
व्योम ar9003_mci_get_isr(काष्ठा ath_hw *ah, क्रमागत ath9k_पूर्णांक *masked);
व्योम ar9003_mci_bt_gain_ctrl(काष्ठा ath_hw *ah);
व्योम ar9003_mci_set_घातer_awake(काष्ठा ath_hw *ah);
व्योम ar9003_mci_check_gpm_offset(काष्ठा ath_hw *ah);
u16 ar9003_mci_get_max_txघातer(काष्ठा ath_hw *ah, u8 ctlmode);

#अन्यथा

अटल अंतरभूत व्योम ar9003_mci_stop_bt(काष्ठा ath_hw *ah, bool save_fullsleep)
अणु
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_init_cal_req(काष्ठा ath_hw *ah, bool *is_reusable)
अणु
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_init_cal_करोne(काष्ठा ath_hw *ah)
अणु
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_set_full_sleep(काष्ठा ath_hw *ah)
अणु
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_2g5g_चयन(काष्ठा ath_hw *ah, bool रुको_करोne)
अणु
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_check_bt(काष्ठा ath_hw *ah)
अणु
पूर्ण
अटल अंतरभूत bool ar9003_mci_start_reset(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक ar9003_mci_end_reset(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
				       काष्ठा ath9k_hw_cal_data *caldata)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_reset(काष्ठा ath_hw *ah, bool en_पूर्णांक, bool is_2g,
				    bool is_full_sleep)
अणु
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_get_isr(काष्ठा ath_hw *ah, क्रमागत ath9k_पूर्णांक *masked)
अणु
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_bt_gain_ctrl(काष्ठा ath_hw *ah)
अणु
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_set_घातer_awake(काष्ठा ath_hw *ah)
अणु
पूर्ण
अटल अंतरभूत व्योम ar9003_mci_check_gpm_offset(काष्ठा ath_hw *ah)
अणु
पूर्ण
अटल अंतरभूत u16 ar9003_mci_get_max_txघातer(काष्ठा ath_hw *ah, u8 ctlmode)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_BTCOEX_SUPPORT */

#पूर्ण_अगर
