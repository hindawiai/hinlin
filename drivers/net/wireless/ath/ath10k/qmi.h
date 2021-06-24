<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित _ATH10K_QMI_H_
#घोषणा _ATH10K_QMI_H_

#समावेश <linux/soc/qcom/qmi.h>
#समावेश <linux/qrtr.h>
#समावेश "qmi_wlfw_v01.h"

#घोषणा MAX_NUM_MEMORY_REGIONS			2
#घोषणा MAX_TIMESTAMP_LEN			32
#घोषणा MAX_BUILD_ID_LEN			128
#घोषणा MAX_NUM_CAL_V01			5

क्रमागत ath10k_qmi_driver_event_type अणु
	ATH10K_QMI_EVENT_SERVER_ARRIVE,
	ATH10K_QMI_EVENT_SERVER_EXIT,
	ATH10K_QMI_EVENT_FW_READY_IND,
	ATH10K_QMI_EVENT_FW_DOWN_IND,
	ATH10K_QMI_EVENT_MSA_READY_IND,
	ATH10K_QMI_EVENT_MAX,
पूर्ण;

काष्ठा ath10k_msa_mem_info अणु
	phys_addr_t addr;
	u32 size;
	bool secure;
पूर्ण;

काष्ठा ath10k_qmi_chip_info अणु
	u32 chip_id;
	u32 chip_family;
पूर्ण;

काष्ठा ath10k_qmi_board_info अणु
	u32 board_id;
पूर्ण;

काष्ठा ath10k_qmi_soc_info अणु
	u32 soc_id;
पूर्ण;

काष्ठा ath10k_qmi_cal_data अणु
	u32 cal_id;
	u32 total_size;
	u8 *data;
पूर्ण;

काष्ठा ath10k_tgt_pipe_cfg अणु
	__le32 pipe_num;
	__le32 pipe_dir;
	__le32 nentries;
	__le32 nbytes_max;
	__le32 flags;
	__le32 reserved;
पूर्ण;

काष्ठा ath10k_svc_pipe_cfg अणु
	__le32 service_id;
	__le32 pipe_dir;
	__le32 pipe_num;
पूर्ण;

काष्ठा ath10k_shaकरोw_reg_cfg अणु
	__le16 ce_id;
	__le16 reg_offset;
पूर्ण;

काष्ठा ath10k_qmi_wlan_enable_cfg अणु
	u32 num_ce_tgt_cfg;
	काष्ठा ath10k_tgt_pipe_cfg *ce_tgt_cfg;
	u32 num_ce_svc_pipe_cfg;
	काष्ठा ath10k_svc_pipe_cfg *ce_svc_cfg;
	u32 num_shaकरोw_reg_cfg;
	काष्ठा ath10k_shaकरोw_reg_cfg *shaकरोw_reg_cfg;
पूर्ण;

काष्ठा ath10k_qmi_driver_event अणु
	काष्ठा list_head list;
	क्रमागत ath10k_qmi_driver_event_type type;
	व्योम *data;
पूर्ण;

क्रमागत ath10k_qmi_state अणु
	ATH10K_QMI_STATE_INIT_DONE,
	ATH10K_QMI_STATE_DEINIT,
पूर्ण;

काष्ठा ath10k_qmi अणु
	काष्ठा ath10k *ar;
	काष्ठा qmi_handle qmi_hdl;
	काष्ठा sockaddr_qrtr sq;
	काष्ठा work_काष्ठा event_work;
	काष्ठा workqueue_काष्ठा *event_wq;
	काष्ठा list_head event_list;
	spinlock_t event_lock; /* spinlock क्रम qmi event list */
	u32 nr_mem_region;
	काष्ठा ath10k_msa_mem_info mem_region[MAX_NUM_MEMORY_REGIONS];
	काष्ठा ath10k_qmi_chip_info chip_info;
	काष्ठा ath10k_qmi_board_info board_info;
	काष्ठा ath10k_qmi_soc_info soc_info;
	अक्षर fw_build_id[MAX_BUILD_ID_LEN + 1];
	u32 fw_version;
	bool fw_पढ़ोy;
	अक्षर fw_build_बारtamp[MAX_TIMESTAMP_LEN + 1];
	काष्ठा ath10k_qmi_cal_data cal_data[MAX_NUM_CAL_V01];
	bool msa_fixed_perm;
	क्रमागत ath10k_qmi_state state;
पूर्ण;

पूर्णांक ath10k_qmi_wlan_enable(काष्ठा ath10k *ar,
			   काष्ठा ath10k_qmi_wlan_enable_cfg *config,
			   क्रमागत wlfw_driver_mode_क्रमागत_v01 mode,
			   स्थिर अक्षर *version);
पूर्णांक ath10k_qmi_wlan_disable(काष्ठा ath10k *ar);
पूर्णांक ath10k_qmi_init(काष्ठा ath10k *ar, u32 msa_size);
पूर्णांक ath10k_qmi_deinit(काष्ठा ath10k *ar);
पूर्णांक ath10k_qmi_set_fw_log_mode(काष्ठा ath10k *ar, u8 fw_log_mode);

#पूर्ण_अगर /* ATH10K_QMI_H */
