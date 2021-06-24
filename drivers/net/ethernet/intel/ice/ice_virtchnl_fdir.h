<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2021, Intel Corporation. */

#अगर_अघोषित _ICE_VIRTCHNL_Fसूची_H_
#घोषणा _ICE_VIRTCHNL_Fसूची_H_

काष्ठा ice_vf;
काष्ठा ice_pf;

क्रमागत ice_fdir_ctx_stat अणु
	ICE_Fसूची_CTX_READY,
	ICE_Fसूची_CTX_IRQ,
	ICE_Fसूची_CTX_TIMEOUT,
पूर्ण;

काष्ठा ice_vf_fdir_ctx अणु
	काष्ठा समयr_list rx_पंचांगr;
	क्रमागत virtchnl_ops v_opcode;
	क्रमागत ice_fdir_ctx_stat stat;
	जोड़ ice_32b_rx_flex_desc rx_desc;
#घोषणा ICE_VF_Fसूची_CTX_VALID		BIT(0)
	u32 flags;

	व्योम *conf;
पूर्ण;

/* VF Fसूची inक्रमmation काष्ठाure */
काष्ठा ice_vf_fdir अणु
	u16 fdir_fltr_cnt[ICE_FLTR_PTYPE_MAX][ICE_FD_HW_SEG_MAX];
	पूर्णांक prof_entry_cnt[ICE_FLTR_PTYPE_MAX][ICE_FD_HW_SEG_MAX];
	काष्ठा ice_fd_hw_prof **fdir_prof;

	काष्ठा idr fdir_rule_idr;
	काष्ठा list_head fdir_rule_list;

	spinlock_t ctx_lock; /* protects Fसूची context info */
	काष्ठा ice_vf_fdir_ctx ctx_irq;
	काष्ठा ice_vf_fdir_ctx ctx_करोne;
पूर्ण;

#अगर_घोषित CONFIG_PCI_IOV
पूर्णांक ice_vc_add_fdir_fltr(काष्ठा ice_vf *vf, u8 *msg);
पूर्णांक ice_vc_del_fdir_fltr(काष्ठा ice_vf *vf, u8 *msg);
व्योम ice_vf_fdir_init(काष्ठा ice_vf *vf);
व्योम ice_vf_fdir_निकास(काष्ठा ice_vf *vf);
व्योम
ice_vc_fdir_irq_handler(काष्ठा ice_vsi *ctrl_vsi,
			जोड़ ice_32b_rx_flex_desc *rx_desc);
व्योम ice_flush_fdir_ctx(काष्ठा ice_pf *pf);
#अन्यथा
अटल अंतरभूत व्योम
ice_vc_fdir_irq_handler(काष्ठा ice_vsi *ctrl_vsi, जोड़ ice_32b_rx_flex_desc *rx_desc) अणु पूर्ण
अटल अंतरभूत व्योम ice_flush_fdir_ctx(काष्ठा ice_pf *pf) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */
#पूर्ण_अगर /* _ICE_VIRTCHNL_Fसूची_H_ */
