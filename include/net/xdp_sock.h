<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* AF_XDP पूर्णांकernal functions
 * Copyright(c) 2018 Intel Corporation.
 */

#अगर_अघोषित _LINUX_XDP_SOCK_H
#घोषणा _LINUX_XDP_SOCK_H

#समावेश <linux/workqueue.h>
#समावेश <linux/अगर_xdp.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <net/sock.h>

काष्ठा net_device;
काष्ठा xsk_queue;
काष्ठा xdp_buff;

काष्ठा xdp_umem अणु
	व्योम *addrs;
	u64 size;
	u32 headroom;
	u32 chunk_size;
	u32 chunks;
	u32 npgs;
	काष्ठा user_काष्ठा *user;
	refcount_t users;
	u8 flags;
	bool zc;
	काष्ठा page **pgs;
	पूर्णांक id;
	काष्ठा list_head xsk_dma_list;
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा xsk_map अणु
	काष्ठा bpf_map map;
	spinlock_t lock; /* Synchronize map updates */
	काष्ठा xdp_sock *xsk_map[];
पूर्ण;

काष्ठा xdp_sock अणु
	/* काष्ठा sock must be the first member of काष्ठा xdp_sock */
	काष्ठा sock sk;
	काष्ठा xsk_queue *rx ____cacheline_aligned_in_smp;
	काष्ठा net_device *dev;
	काष्ठा xdp_umem *umem;
	काष्ठा list_head flush_node;
	काष्ठा xsk_buff_pool *pool;
	u16 queue_id;
	bool zc;
	क्रमागत अणु
		XSK_READY = 0,
		XSK_BOUND,
		XSK_UNBOUND,
	पूर्ण state;

	काष्ठा xsk_queue *tx ____cacheline_aligned_in_smp;
	काष्ठा list_head tx_list;
	/* Protects generic receive. */
	spinlock_t rx_lock;

	/* Statistics */
	u64 rx_dropped;
	u64 rx_queue_full;

	काष्ठा list_head map_list;
	/* Protects map_list */
	spinlock_t map_list_lock;
	/* Protects multiple processes in the control path */
	काष्ठा mutex mutex;
	काष्ठा xsk_queue *fq_पंचांगp; /* Only as पंचांगp storage beक्रमe bind */
	काष्ठा xsk_queue *cq_पंचांगp; /* Only as पंचांगp storage beक्रमe bind */
पूर्ण;

#अगर_घोषित CONFIG_XDP_SOCKETS

पूर्णांक xsk_generic_rcv(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp);
पूर्णांक __xsk_map_redirect(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp);
व्योम __xsk_map_flush(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक xsk_generic_rcv(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक __xsk_map_redirect(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम __xsk_map_flush(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_XDP_SOCKETS */

#पूर्ण_अगर /* _LINUX_XDP_SOCK_H */
