<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ENIC_CLSF_H_
#घोषणा _ENIC_CLSF_H_

#समावेश "vnic_dev.h"
#समावेश "enic.h"

#घोषणा ENIC_CLSF_EXPIRE_COUNT 128

पूर्णांक enic_addfltr_5t(काष्ठा enic *enic, काष्ठा flow_keys *keys, u16 rq);
पूर्णांक enic_delfltr(काष्ठा enic *enic, u16 filter_id);
व्योम enic_rfs_flw_tbl_init(काष्ठा enic *enic);
व्योम enic_rfs_flw_tbl_मुक्त(काष्ठा enic *enic);
काष्ठा enic_rfs_fltr_node *htbl_fltr_search(काष्ठा enic *enic, u16 fltr_id);

#अगर_घोषित CONFIG_RFS_ACCEL
पूर्णांक enic_rx_flow_steer(काष्ठा net_device *dev, स्थिर काष्ठा sk_buff *skb,
		       u16 rxq_index, u32 flow_id);
व्योम enic_flow_may_expire(काष्ठा समयr_list *t);

अटल अंतरभूत व्योम enic_rfs_समयr_start(काष्ठा enic *enic)
अणु
	समयr_setup(&enic->rfs_h.rfs_may_expire, enic_flow_may_expire, 0);
	mod_समयr(&enic->rfs_h.rfs_may_expire, jअगरfies + HZ/4);
पूर्ण

अटल अंतरभूत व्योम enic_rfs_समयr_stop(काष्ठा enic *enic)
अणु
	del_समयr_sync(&enic->rfs_h.rfs_may_expire);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम enic_rfs_समयr_start(काष्ठा enic *enic) अणुपूर्ण
अटल अंतरभूत व्योम enic_rfs_समयr_stop(काष्ठा enic *enic) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

#पूर्ण_अगर /* _ENIC_CLSF_H_ */
