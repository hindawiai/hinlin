<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015 QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_DEBUGFS_H
#घोषणा _QED_DEBUGFS_H

क्रमागत qed_dbg_features अणु
	DBG_FEATURE_GRC,
	DBG_FEATURE_IDLE_CHK,
	DBG_FEATURE_MCP_TRACE,
	DBG_FEATURE_REG_FIFO,
	DBG_FEATURE_IGU_FIFO,
	DBG_FEATURE_PROTECTION_OVERRIDE,
	DBG_FEATURE_FW_ASSERTS,
	DBG_FEATURE_ILT,
	DBG_FEATURE_NUM
पूर्ण;

/* Forward Declaration */
काष्ठा qed_dev;
काष्ठा qed_hwfn;

पूर्णांक qed_dbg_grc(काष्ठा qed_dev *cdev, व्योम *buffer, u32 *num_dumped_bytes);
पूर्णांक qed_dbg_grc_size(काष्ठा qed_dev *cdev);
पूर्णांक qed_dbg_idle_chk(काष्ठा qed_dev *cdev, व्योम *buffer,
		     u32 *num_dumped_bytes);
पूर्णांक qed_dbg_idle_chk_size(काष्ठा qed_dev *cdev);
पूर्णांक qed_dbg_reg_fअगरo(काष्ठा qed_dev *cdev, व्योम *buffer,
		     u32 *num_dumped_bytes);
पूर्णांक qed_dbg_reg_fअगरo_size(काष्ठा qed_dev *cdev);
पूर्णांक qed_dbg_igu_fअगरo(काष्ठा qed_dev *cdev, व्योम *buffer,
		     u32 *num_dumped_bytes);
पूर्णांक qed_dbg_igu_fअगरo_size(काष्ठा qed_dev *cdev);
पूर्णांक qed_dbg_protection_override(काष्ठा qed_dev *cdev, व्योम *buffer,
				u32 *num_dumped_bytes);
पूर्णांक qed_dbg_protection_override_size(काष्ठा qed_dev *cdev);
पूर्णांक qed_dbg_fw_निश्चितs(काष्ठा qed_dev *cdev, व्योम *buffer,
		       u32 *num_dumped_bytes);
पूर्णांक qed_dbg_fw_निश्चितs_size(काष्ठा qed_dev *cdev);
पूर्णांक qed_dbg_ilt(काष्ठा qed_dev *cdev, व्योम *buffer, u32 *num_dumped_bytes);
पूर्णांक qed_dbg_ilt_size(काष्ठा qed_dev *cdev);
पूर्णांक qed_dbg_mcp_trace(काष्ठा qed_dev *cdev, व्योम *buffer,
		      u32 *num_dumped_bytes);
पूर्णांक qed_dbg_mcp_trace_size(काष्ठा qed_dev *cdev);
पूर्णांक qed_dbg_all_data(काष्ठा qed_dev *cdev, व्योम *buffer);
पूर्णांक qed_dbg_all_data_size(काष्ठा qed_dev *cdev);
u8 qed_get_debug_engine(काष्ठा qed_dev *cdev);
व्योम qed_set_debug_engine(काष्ठा qed_dev *cdev, पूर्णांक engine_number);
पूर्णांक qed_dbg_feature(काष्ठा qed_dev *cdev, व्योम *buffer,
		    क्रमागत qed_dbg_features feature, u32 *num_dumped_bytes);
पूर्णांक qed_dbg_feature_size(काष्ठा qed_dev *cdev, क्रमागत qed_dbg_features feature);

व्योम qed_dbg_pf_init(काष्ठा qed_dev *cdev);
व्योम qed_dbg_pf_निकास(काष्ठा qed_dev *cdev);

#पूर्ण_अगर
