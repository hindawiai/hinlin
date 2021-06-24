<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2014-2016 Broadcom Corporation
 * Copyright (c) 2016-2018 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित BNXT_SRIOV_H
#घोषणा BNXT_SRIOV_H

#घोषणा BNXT_FWD_RESP_SIZE_ERR(n)					\
	((दुरत्व(काष्ठा hwrm_fwd_resp_input, encap_resp) + n) >	\
	 माप(काष्ठा hwrm_fwd_resp_input))

#घोषणा BNXT_EXEC_FWD_RESP_SIZE_ERR(n)					\
	((दुरत्व(काष्ठा hwrm_exec_fwd_resp_input, encap_request) + n) >\
	 दुरत्व(काष्ठा hwrm_exec_fwd_resp_input, encap_resp_target_id))

#घोषणा BNXT_REJ_FWD_RESP_SIZE_ERR(n)					\
	((दुरत्व(काष्ठा hwrm_reject_fwd_resp_input, encap_request) + n) >\
	 दुरत्व(काष्ठा hwrm_reject_fwd_resp_input, encap_resp_target_id))

#घोषणा BNXT_VF_MIN_RSS_CTX	1
#घोषणा BNXT_VF_MAX_RSS_CTX	1
#घोषणा BNXT_VF_MIN_L2_CTX	1
#घोषणा BNXT_VF_MAX_L2_CTX	4

पूर्णांक bnxt_get_vf_config(काष्ठा net_device *, पूर्णांक, काष्ठा अगरla_vf_info *);
पूर्णांक bnxt_set_vf_mac(काष्ठा net_device *, पूर्णांक, u8 *);
पूर्णांक bnxt_set_vf_vlan(काष्ठा net_device *, पूर्णांक, u16, u8, __be16);
पूर्णांक bnxt_set_vf_bw(काष्ठा net_device *, पूर्णांक, पूर्णांक, पूर्णांक);
पूर्णांक bnxt_set_vf_link_state(काष्ठा net_device *, पूर्णांक, पूर्णांक);
पूर्णांक bnxt_set_vf_spoofchk(काष्ठा net_device *, पूर्णांक, bool);
bool bnxt_is_trusted_vf(काष्ठा bnxt *bp, काष्ठा bnxt_vf_info *vf);
पूर्णांक bnxt_set_vf_trust(काष्ठा net_device *dev, पूर्णांक vf_id, bool trust);
पूर्णांक bnxt_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs);
पूर्णांक bnxt_cfg_hw_sriov(काष्ठा bnxt *bp, पूर्णांक *num_vfs, bool reset);
व्योम bnxt_sriov_disable(काष्ठा bnxt *);
व्योम bnxt_hwrm_exec_fwd_req(काष्ठा bnxt *);
व्योम bnxt_update_vf_mac(काष्ठा bnxt *);
पूर्णांक bnxt_approve_mac(काष्ठा bnxt *, u8 *, bool);
#पूर्ण_अगर
