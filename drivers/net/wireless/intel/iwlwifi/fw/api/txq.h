<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2019-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_txq_h__
#घोषणा __iwl_fw_api_txq_h__

/*
 * DQA queue numbers
 *
 * @IWL_MVM_DQA_CMD_QUEUE: a queue reserved क्रम sending HCMDs to the FW
 * @IWL_MVM_DQA_AUX_QUEUE: a queue reserved क्रम aux frames
 * @IWL_MVM_DQA_P2P_DEVICE_QUEUE: a queue reserved क्रम P2P device frames
 * @IWL_MVM_DQA_INJECT_MONITOR_QUEUE: a queue reserved क्रम injection using
 *	monitor mode. Note this queue is the same as the queue क्रम P2P device
 *	but we can't have active monitor mode aदीर्घ with P2P device anyway.
 * @IWL_MVM_DQA_GCAST_QUEUE: a queue reserved क्रम P2P GO/SoftAP GCAST frames
 * @IWL_MVM_DQA_BSS_CLIENT_QUEUE: a queue reserved क्रम BSS activity, to ensure
 *	that we are never left without the possibility to connect to an AP.
 * @IWL_MVM_DQA_MIN_MGMT_QUEUE: first TXQ in pool क्रम MGMT and non-QOS frames.
 *	Each MGMT queue is mapped to a single STA
 *	MGMT frames are frames that वापस true on ieee80211_is_mgmt()
 * @IWL_MVM_DQA_MAX_MGMT_QUEUE: last TXQ in pool क्रम MGMT frames
 * @IWL_MVM_DQA_AP_PROBE_RESP_QUEUE: a queue reserved क्रम P2P GO/SoftAP probe
 *	responses
 * @IWL_MVM_DQA_MIN_DATA_QUEUE: first TXQ in pool क्रम DATA frames.
 *	DATA frames are पूर्णांकended क्रम !ieee80211_is_mgmt() frames, but अगर
 *	the MGMT TXQ pool is exhausted, mgmt frames can be sent on DATA queues
 *	as well
 * @IWL_MVM_DQA_MAX_DATA_QUEUE: last TXQ in pool क्रम DATA frames
 */
क्रमागत iwl_mvm_dqa_txq अणु
	IWL_MVM_DQA_CMD_QUEUE = 0,
	IWL_MVM_DQA_AUX_QUEUE = 1,
	IWL_MVM_DQA_P2P_DEVICE_QUEUE = 2,
	IWL_MVM_DQA_INJECT_MONITOR_QUEUE = 2,
	IWL_MVM_DQA_GCAST_QUEUE = 3,
	IWL_MVM_DQA_BSS_CLIENT_QUEUE = 4,
	IWL_MVM_DQA_MIN_MGMT_QUEUE = 5,
	IWL_MVM_DQA_MAX_MGMT_QUEUE = 8,
	IWL_MVM_DQA_AP_PROBE_RESP_QUEUE = 9,
	IWL_MVM_DQA_MIN_DATA_QUEUE = 10,
	IWL_MVM_DQA_MAX_DATA_QUEUE = 30,
पूर्ण;

क्रमागत iwl_mvm_tx_fअगरo अणु
	IWL_MVM_TX_FIFO_BK = 0,
	IWL_MVM_TX_FIFO_BE,
	IWL_MVM_TX_FIFO_VI,
	IWL_MVM_TX_FIFO_VO,
	IWL_MVM_TX_FIFO_MCAST = 5,
	IWL_MVM_TX_FIFO_CMD = 7,
पूर्ण;

क्रमागत iwl_gen2_tx_fअगरo अणु
	IWL_GEN2_TX_FIFO_CMD = 0,
	IWL_GEN2_EDCA_TX_FIFO_BK,
	IWL_GEN2_EDCA_TX_FIFO_BE,
	IWL_GEN2_EDCA_TX_FIFO_VI,
	IWL_GEN2_EDCA_TX_FIFO_VO,
	IWL_GEN2_TRIG_TX_FIFO_BK,
	IWL_GEN2_TRIG_TX_FIFO_BE,
	IWL_GEN2_TRIG_TX_FIFO_VI,
	IWL_GEN2_TRIG_TX_FIFO_VO,
पूर्ण;

/**
 * क्रमागत iwl_tx_queue_cfg_actions - TXQ config options
 * @TX_QUEUE_CFG_ENABLE_QUEUE: enable a queue
 * @TX_QUEUE_CFG_TFD_SHORT_FORMAT: use लघु TFD क्रमmat
 */
क्रमागत iwl_tx_queue_cfg_actions अणु
	TX_QUEUE_CFG_ENABLE_QUEUE		= BIT(0),
	TX_QUEUE_CFG_TFD_SHORT_FORMAT		= BIT(1),
पूर्ण;

#घोषणा IWL_DEFAULT_QUEUE_SIZE 256
#घोषणा IWL_MGMT_QUEUE_SIZE 16
#घोषणा IWL_CMD_QUEUE_SIZE 32
/**
 * काष्ठा iwl_tx_queue_cfg_cmd - txq hw scheduler config command
 * @sta_id: station id
 * @tid: tid of the queue
 * @flags: see &क्रमागत iwl_tx_queue_cfg_actions
 * @cb_size: size of TFD cyclic buffer. Value is exponent - 3.
 *	Minimum value 0 (8 TFDs), maximum value 5 (256 TFDs)
 * @byte_cnt_addr: address of byte count table
 * @tfdq_addr: address of TFD circular buffer
 */
काष्ठा iwl_tx_queue_cfg_cmd अणु
	u8 sta_id;
	u8 tid;
	__le16 flags;
	__le32 cb_size;
	__le64 byte_cnt_addr;
	__le64 tfdq_addr;
पूर्ण __packed; /* TX_QUEUE_CFG_CMD_API_S_VER_2 */

/**
 * काष्ठा iwl_tx_queue_cfg_rsp - response to txq hw scheduler config
 * @queue_number: queue number asचिन्हित to this RA -TID
 * @flags: set on failure
 * @ग_लिखो_poपूर्णांकer: initial value क्रम ग_लिखो poपूर्णांकer
 * @reserved: reserved
 */
काष्ठा iwl_tx_queue_cfg_rsp अणु
	__le16 queue_number;
	__le16 flags;
	__le16 ग_लिखो_poपूर्णांकer;
	__le16 reserved;
पूर्ण __packed; /* TX_QUEUE_CFG_RSP_API_S_VER_2 */

#पूर्ण_अगर /* __iwl_fw_api_txq_h__ */
