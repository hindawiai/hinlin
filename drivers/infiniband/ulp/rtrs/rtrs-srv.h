<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RDMA Transport Layer
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */

#अगर_अघोषित RTRS_SRV_H
#घोषणा RTRS_SRV_H

#समावेश <linux/device.h>
#समावेश <linux/refcount.h>
#समावेश "rtrs-pri.h"

/*
 * क्रमागत rtrs_srv_state - Server states.
 */
क्रमागत rtrs_srv_state अणु
	RTRS_SRV_CONNECTING,
	RTRS_SRV_CONNECTED,
	RTRS_SRV_CLOSING,
	RTRS_SRV_CLOSED,
पूर्ण;

/* stats क्रम Read and ग_लिखो operation.
 * see Documentation/ABI/testing/sysfs-class-rtrs-server क्रम details
 */
काष्ठा rtrs_srv_stats_rdma_stats अणु
	काष्ठा अणु
		atomic64_t	cnt;
		atomic64_t	माप_प्रकारotal;
	पूर्ण dir[2];
पूर्ण;

काष्ठा rtrs_srv_stats अणु
	काष्ठा kobject				kobj_stats;
	काष्ठा rtrs_srv_stats_rdma_stats	rdma_stats;
	काष्ठा rtrs_srv_sess			*sess;
पूर्ण;

काष्ठा rtrs_srv_con अणु
	काष्ठा rtrs_con		c;
	atomic_t		wr_cnt;
	atomic_t		sq_wr_avail;
	काष्ठा list_head	rsp_wr_रुको_list;
	spinlock_t		rsp_wr_रुको_lock;
पूर्ण;

/* IO context in rtrs_srv, each io has one */
काष्ठा rtrs_srv_op अणु
	काष्ठा rtrs_srv_con		*con;
	u32				msg_id;
	u8				dir;
	काष्ठा rtrs_msg_rdma_पढ़ो	*rd_msg;
	काष्ठा ib_rdma_wr		tx_wr;
	काष्ठा ib_sge			tx_sg;
	काष्ठा list_head		रुको_list;
	पूर्णांक				status;
पूर्ण;

/*
 * server side memory region context, when always_invalidate=Y, we need
 * queue_depth of memory region to invalidate each memory region.
 */
काष्ठा rtrs_srv_mr अणु
	काष्ठा ib_mr	*mr;
	काष्ठा sg_table	sgt;
	काष्ठा ib_cqe	inv_cqe;	/* only क्रम always_invalidate=true */
	u32		msg_id;		/* only क्रम always_invalidate=true */
	u32		msg_off;	/* only क्रम always_invalidate=true */
	काष्ठा rtrs_iu	*iu;		/* send buffer क्रम new rkey msg */
पूर्ण;

काष्ठा rtrs_srv_sess अणु
	काष्ठा rtrs_sess	s;
	काष्ठा rtrs_srv	*srv;
	काष्ठा work_काष्ठा	बंद_work;
	क्रमागत rtrs_srv_state	state;
	spinlock_t		state_lock;
	पूर्णांक			cur_cq_vector;
	काष्ठा rtrs_srv_op	**ops_ids;
	atomic_t		ids_inflight;
	रुको_queue_head_t	ids_रुकोq;
	काष्ठा rtrs_srv_mr	*mrs;
	अचिन्हित पूर्णांक		mrs_num;
	dma_addr_t		*dma_addr;
	bool			established;
	अचिन्हित पूर्णांक		mem_bits;
	काष्ठा kobject		kobj;
	काष्ठा rtrs_srv_stats	*stats;
पूर्ण;

काष्ठा rtrs_srv अणु
	काष्ठा list_head	paths_list;
	पूर्णांक			paths_up;
	काष्ठा mutex		paths_ev_mutex;
	माप_प्रकार			paths_num;
	काष्ठा mutex		paths_mutex;
	uuid_t			paths_uuid;
	refcount_t		refcount;
	काष्ठा rtrs_srv_ctx	*ctx;
	काष्ठा list_head	ctx_list;
	व्योम			*priv;
	माप_प्रकार			queue_depth;
	काष्ठा page		**chunks;
	काष्ठा device		dev;
	अचिन्हित पूर्णांक		dev_ref;
	काष्ठा kobject		*kobj_paths;
पूर्ण;

काष्ठा rtrs_srv_ctx अणु
	काष्ठा rtrs_srv_ops ops;
	काष्ठा rdma_cm_id *cm_id_ip;
	काष्ठा rdma_cm_id *cm_id_ib;
	काष्ठा mutex srv_mutex;
	काष्ठा list_head srv_list;
पूर्ण;

काष्ठा rtrs_srv_ib_ctx अणु
	काष्ठा rtrs_srv_ctx	*srv_ctx;
	u16			port;
	काष्ठा mutex            ib_dev_mutex;
	पूर्णांक			ib_dev_count;
पूर्ण;

बाह्य काष्ठा class *rtrs_dev_class;

व्योम बंद_sess(काष्ठा rtrs_srv_sess *sess);

अटल अंतरभूत व्योम rtrs_srv_update_rdma_stats(काष्ठा rtrs_srv_stats *s,
					      माप_प्रकार size, पूर्णांक d)
अणु
	atomic64_inc(&s->rdma_stats.dir[d].cnt);
	atomic64_add(size, &s->rdma_stats.dir[d].माप_प्रकारotal);
पूर्ण

/* functions which are implemented in rtrs-srv-stats.c */
पूर्णांक rtrs_srv_reset_rdma_stats(काष्ठा rtrs_srv_stats *stats, bool enable);
sमाप_प्रकार rtrs_srv_stats_rdma_to_str(काष्ठा rtrs_srv_stats *stats,
				    अक्षर *page, माप_प्रकार len);
पूर्णांक rtrs_srv_reset_wc_completion_stats(काष्ठा rtrs_srv_stats *stats,
					bool enable);
पूर्णांक rtrs_srv_stats_wc_completion_to_str(काष्ठा rtrs_srv_stats *stats, अक्षर *buf,
					 माप_प्रकार len);
पूर्णांक rtrs_srv_reset_all_stats(काष्ठा rtrs_srv_stats *stats, bool enable);
sमाप_प्रकार rtrs_srv_reset_all_help(काष्ठा rtrs_srv_stats *stats,
				 अक्षर *page, माप_प्रकार len);

/* functions which are implemented in rtrs-srv-sysfs.c */
पूर्णांक rtrs_srv_create_sess_files(काष्ठा rtrs_srv_sess *sess);
व्योम rtrs_srv_destroy_sess_files(काष्ठा rtrs_srv_sess *sess);

#पूर्ण_अगर /* RTRS_SRV_H */
