<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2016-2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित BNXT_VFR_H
#घोषणा BNXT_VFR_H

#अगर_घोषित CONFIG_BNXT_SRIOV

#घोषणा	MAX_CFA_CODE			65536

व्योम bnxt_vf_reps_destroy(काष्ठा bnxt *bp);
व्योम bnxt_vf_reps_बंद(काष्ठा bnxt *bp);
व्योम bnxt_vf_reps_खोलो(काष्ठा bnxt *bp);
व्योम bnxt_vf_rep_rx(काष्ठा bnxt *bp, काष्ठा sk_buff *skb);
काष्ठा net_device *bnxt_get_vf_rep(काष्ठा bnxt *bp, u16 cfa_code);
पूर्णांक bnxt_vf_reps_alloc(काष्ठा bnxt *bp);
व्योम bnxt_vf_reps_मुक्त(काष्ठा bnxt *bp);

अटल अंतरभूत u16 bnxt_vf_rep_get_fid(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt_vf_rep *vf_rep = netdev_priv(dev);
	काष्ठा bnxt *bp = vf_rep->bp;

	वापस bp->pf.vf[vf_rep->vf_idx].fw_fid;
पूर्ण

bool bnxt_dev_is_vf_rep(काष्ठा net_device *dev);
पूर्णांक bnxt_dl_eचयन_mode_get(काष्ठा devlink *devlink, u16 *mode);
पूर्णांक bnxt_dl_eचयन_mode_set(काष्ठा devlink *devlink, u16 mode,
			     काष्ठा netlink_ext_ack *extack);

#अन्यथा

अटल अंतरभूत व्योम bnxt_vf_reps_बंद(काष्ठा bnxt *bp)
अणु
पूर्ण

अटल अंतरभूत व्योम bnxt_vf_reps_खोलो(काष्ठा bnxt *bp)
अणु
पूर्ण

अटल अंतरभूत व्योम bnxt_vf_rep_rx(काष्ठा bnxt *bp, काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत काष्ठा net_device *bnxt_get_vf_rep(काष्ठा bnxt *bp, u16 cfa_code)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत u16 bnxt_vf_rep_get_fid(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool bnxt_dev_is_vf_rep(काष्ठा net_device *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक bnxt_vf_reps_alloc(काष्ठा bnxt *bp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bnxt_vf_reps_मुक्त(काष्ठा bnxt *bp)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_BNXT_SRIOV */
#पूर्ण_अगर /* BNXT_VFR_H */
