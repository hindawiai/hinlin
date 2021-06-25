<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Definitions क्रम the SMC module (socket related)
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */
#अगर_अघोषित _SMC_H
#घोषणा _SMC_H

#घोषणा SMC_MAX_PNETID_LEN	16	/* Max. length of PNET id */

काष्ठा smc_hashinfo अणु
	rwlock_t lock;
	काष्ठा hlist_head ht;
पूर्ण;

पूर्णांक smc_hash_sk(काष्ठा sock *sk);
व्योम smc_unhash_sk(काष्ठा sock *sk);

/* SMCD/ISM device driver पूर्णांकerface */
काष्ठा smcd_dmb अणु
	u64 dmb_tok;
	u64 rgid;
	u32 dmb_len;
	u32 sba_idx;
	u32 vlan_valid;
	u32 vlan_id;
	व्योम *cpu_addr;
	dma_addr_t dma_addr;
पूर्ण;

#घोषणा ISM_EVENT_DMB	0
#घोषणा ISM_EVENT_GID	1
#घोषणा ISM_EVENT_SWR	2

#घोषणा ISM_RESERVED_VLANID	0x1FFF

#घोषणा ISM_ERROR	0xFFFF

काष्ठा smcd_event अणु
	u32 type;
	u32 code;
	u64 tok;
	u64 समय;
	u64 info;
पूर्ण;

काष्ठा smcd_dev;

काष्ठा smcd_ops अणु
	पूर्णांक (*query_remote_gid)(काष्ठा smcd_dev *dev, u64 rgid, u32 vid_valid,
				u32 vid);
	पूर्णांक (*रेजिस्टर_dmb)(काष्ठा smcd_dev *dev, काष्ठा smcd_dmb *dmb);
	पूर्णांक (*unरेजिस्टर_dmb)(काष्ठा smcd_dev *dev, काष्ठा smcd_dmb *dmb);
	पूर्णांक (*add_vlan_id)(काष्ठा smcd_dev *dev, u64 vlan_id);
	पूर्णांक (*del_vlan_id)(काष्ठा smcd_dev *dev, u64 vlan_id);
	पूर्णांक (*set_vlan_required)(काष्ठा smcd_dev *dev);
	पूर्णांक (*reset_vlan_required)(काष्ठा smcd_dev *dev);
	पूर्णांक (*संकेत_event)(काष्ठा smcd_dev *dev, u64 rgid, u32 trigger_irq,
			    u32 event_code, u64 info);
	पूर्णांक (*move_data)(काष्ठा smcd_dev *dev, u64 dmb_tok, अचिन्हित पूर्णांक idx,
			 bool sf, अचिन्हित पूर्णांक offset, व्योम *data,
			 अचिन्हित पूर्णांक size);
	व्योम (*get_प्रणाली_eid)(काष्ठा smcd_dev *dev, u8 **eid);
	u16 (*get_chid)(काष्ठा smcd_dev *dev);
पूर्ण;

काष्ठा smcd_dev अणु
	स्थिर काष्ठा smcd_ops *ops;
	काष्ठा device dev;
	व्योम *priv;
	u64 local_gid;
	काष्ठा list_head list;
	spinlock_t lock;
	काष्ठा smc_connection **conn;
	काष्ठा list_head vlan;
	काष्ठा workqueue_काष्ठा *event_wq;
	u8 pnetid[SMC_MAX_PNETID_LEN];
	bool pnetid_by_user;
	काष्ठा list_head lgr_list;
	spinlock_t lgr_lock;
	atomic_t lgr_cnt;
	रुको_queue_head_t lgrs_deleted;
	u8 going_away : 1;
पूर्ण;

काष्ठा smcd_dev *smcd_alloc_dev(काष्ठा device *parent, स्थिर अक्षर *name,
				स्थिर काष्ठा smcd_ops *ops, पूर्णांक max_dmbs);
पूर्णांक smcd_रेजिस्टर_dev(काष्ठा smcd_dev *smcd);
व्योम smcd_unरेजिस्टर_dev(काष्ठा smcd_dev *smcd);
व्योम smcd_मुक्त_dev(काष्ठा smcd_dev *smcd);
व्योम smcd_handle_event(काष्ठा smcd_dev *dev, काष्ठा smcd_event *event);
व्योम smcd_handle_irq(काष्ठा smcd_dev *dev, अचिन्हित पूर्णांक bit);
#पूर्ण_अगर	/* _SMC_H */
