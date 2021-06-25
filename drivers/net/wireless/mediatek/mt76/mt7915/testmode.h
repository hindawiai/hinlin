<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#अगर_अघोषित __MT7915_TESTMODE_H
#घोषणा __MT7915_TESTMODE_H

काष्ठा mt7915_पंचांग_trx अणु
	u8 type;
	u8 enable;
	u8 band;
	u8 rsv;
पूर्ण;

काष्ठा mt7915_पंचांग_freq_offset अणु
	u8 band;
	__le32 freq_offset;
पूर्ण;

काष्ठा mt7915_पंचांग_slot_समय अणु
	u8 slot_समय;
	u8 sअगरs;
	u8 rअगरs;
	u8 _rsv;
	__le16 eअगरs;
	u8 band;
	u8 _rsv1[5];
पूर्ण;

काष्ठा mt7915_पंचांग_clean_txq अणु
	bool sta_छोड़ो;
	u8 wcid;	/* 256 sta */
	u8 band;
	u8 rsv;
पूर्ण;

काष्ठा mt7915_पंचांग_cmd अणु
	u8 tesपंचांगode_en;
	u8 param_idx;
	u8 _rsv[2];
	जोड़ अणु
		__le32 data;
		काष्ठा mt7915_पंचांग_trx trx;
		काष्ठा mt7915_पंचांग_freq_offset freq;
		काष्ठा mt7915_पंचांग_slot_समय slot;
		काष्ठा mt7915_पंचांग_clean_txq clean;
		u8 test[72];
	पूर्ण param;
पूर्ण __packed;

क्रमागत अणु
	TM_MAC_TX = 1,
	TM_MAC_RX,
	TM_MAC_TXRX,
	TM_MAC_TXRX_RXV,
	TM_MAC_RXV,
	TM_MAC_RX_RXV,
पूर्ण;

काष्ठा पंचांग_tx_cont अणु
	u8 control_ch;
	u8 center_ch;
	u8 bw;
	u8 tx_ant;
	__le16 rateval;
	u8 band;
	u8 txfd_mode;
पूर्ण;

काष्ठा mt7915_पंचांग_rf_test अणु
	u8 action;
	u8 icap_len;
	u8 _rsv[2];
	जोड़ अणु
		__le32 op_mode;
		__le32 freq;

		काष्ठा अणु
			__le32 func_idx;
			जोड़ अणु
				__le32 func_data;
				__le32 cal_dump;

				काष्ठा पंचांग_tx_cont tx_cont;

				u8 _pad[80];
			पूर्ण param;
		पूर्ण rf;
	पूर्ण op;
पूर्ण __packed;

क्रमागत अणु
	RF_OPER_NORMAL,
	RF_OPER_RF_TEST,
	RF_OPER_ICAP,
	RF_OPER_ICAP_OVERLAP,
	RF_OPER_WIFI_SPECTRUM,
पूर्ण;

#पूर्ण_अगर
