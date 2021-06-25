<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RDMA Transport Layer
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */

#अगर_अघोषित RTRS_CLT_H
#घोषणा RTRS_CLT_H

#समावेश <linux/device.h>
#समावेश "rtrs-pri.h"

/**
 * क्रमागत rtrs_clt_state - Client states.
 */
क्रमागत rtrs_clt_state अणु
	RTRS_CLT_CONNECTING,
	RTRS_CLT_CONNECTING_ERR,
	RTRS_CLT_RECONNECTING,
	RTRS_CLT_CONNECTED,
	RTRS_CLT_CLOSING,
	RTRS_CLT_CLOSED,
	RTRS_CLT_DEAD,
पूर्ण;

क्रमागत rtrs_mp_policy अणु
	MP_POLICY_RR,
	MP_POLICY_MIN_INFLIGHT,
	MP_POLICY_MIN_LATENCY,
पूर्ण;

/* see Documentation/ABI/testing/sysfs-class-rtrs-client क्रम details */
काष्ठा rtrs_clt_stats_reconnects अणु
	पूर्णांक successful_cnt;
	पूर्णांक fail_cnt;
पूर्ण;

/* see Documentation/ABI/testing/sysfs-class-rtrs-client क्रम details */
काष्ठा rtrs_clt_stats_cpu_migr अणु
	atomic_t from;
	पूर्णांक to;
पूर्ण;

/* stats क्रम Read and ग_लिखो operation.
 * see Documentation/ABI/testing/sysfs-class-rtrs-client क्रम details
 */
काष्ठा rtrs_clt_stats_rdma अणु
	काष्ठा अणु
		u64 cnt;
		u64 माप_प्रकारotal;
	पूर्ण dir[2];

	u64 failover_cnt;
पूर्ण;

काष्ठा rtrs_clt_stats_pcpu अणु
	काष्ठा rtrs_clt_stats_cpu_migr		cpu_migr;
	काष्ठा rtrs_clt_stats_rdma		rdma;
पूर्ण;

काष्ठा rtrs_clt_stats अणु
	काष्ठा kobject				kobj_stats;
	काष्ठा rtrs_clt_stats_pcpu    __percpu	*pcpu_stats;
	काष्ठा rtrs_clt_stats_reconnects	reconnects;
	atomic_t				inflight;
पूर्ण;

काष्ठा rtrs_clt_con अणु
	काष्ठा rtrs_con	c;
	काष्ठा rtrs_iu		*rsp_ius;
	u32			queue_size;
	अचिन्हित पूर्णांक		cpu;
	काष्ठा mutex		con_mutex;
	atomic_t		io_cnt;
	पूर्णांक			cm_err;
पूर्ण;

/**
 * rtrs_permit - permits the memory allocation क्रम future RDMA operation.
 *		 Combine with irq pinning to keep IO on same CPU.
 */
काष्ठा rtrs_permit अणु
	क्रमागत rtrs_clt_con_type con_type;
	अचिन्हित पूर्णांक cpu_id;
	अचिन्हित पूर्णांक mem_id;
	अचिन्हित पूर्णांक mem_off;
पूर्ण;

/**
 * rtrs_clt_io_req - describes one inflight IO request
 */
काष्ठा rtrs_clt_io_req अणु
	काष्ठा list_head        list;
	काष्ठा rtrs_iu		*iu;
	काष्ठा scatterlist	*sglist; /* list holding user data */
	अचिन्हित पूर्णांक		sg_cnt;
	अचिन्हित पूर्णांक		sg_size;
	अचिन्हित पूर्णांक		data_len;
	अचिन्हित पूर्णांक		usr_len;
	व्योम			*priv;
	bool			in_use;
	काष्ठा rtrs_clt_con	*con;
	काष्ठा rtrs_sg_desc	*desc;
	काष्ठा ib_sge		*sge;
	काष्ठा rtrs_permit	*permit;
	क्रमागत dma_data_direction dir;
	व्योम			(*conf)(व्योम *priv, पूर्णांक त्रुटि_सं);
	अचिन्हित दीर्घ		start_jअगरfies;

	काष्ठा ib_mr		*mr;
	काष्ठा ib_cqe		inv_cqe;
	काष्ठा completion	inv_comp;
	पूर्णांक			inv_त्रुटि_सं;
	bool			need_inv_comp;
	bool			need_inv;
पूर्ण;

काष्ठा rtrs_rbuf अणु
	u64 addr;
	u32 rkey;
पूर्ण;

काष्ठा rtrs_clt_sess अणु
	काष्ठा rtrs_sess	s;
	काष्ठा rtrs_clt	*clt;
	रुको_queue_head_t	state_wq;
	क्रमागत rtrs_clt_state	state;
	atomic_t		connected_cnt;
	काष्ठा mutex		init_mutex;
	काष्ठा rtrs_clt_io_req	*reqs;
	काष्ठा delayed_work	reconnect_dwork;
	काष्ठा work_काष्ठा	बंद_work;
	अचिन्हित पूर्णांक		reconnect_attempts;
	bool			established;
	काष्ठा rtrs_rbuf	*rbufs;
	माप_प्रकार			max_io_size;
	u32			max_hdr_size;
	u32			chunk_size;
	माप_प्रकार			queue_depth;
	u32			max_pages_per_mr;
	पूर्णांक			max_send_sge;
	u32			flags;
	काष्ठा kobject		kobj;
	u8			क्रम_new_clt;
	काष्ठा rtrs_clt_stats	*stats;
	/* cache hca_port and hca_name to display in sysfs */
	u8			hca_port;
	अक्षर                    hca_name[IB_DEVICE_NAME_MAX];
	काष्ठा list_head __percpu
				*mp_skip_entry;
पूर्ण;

काष्ठा rtrs_clt अणु
	काष्ठा list_head	paths_list; /* rcu रक्षित list */
	माप_प्रकार			paths_num;
	काष्ठा rtrs_clt_sess
	__rcu * __percpu	*pcpu_path;
	uuid_t			paths_uuid;
	पूर्णांक			paths_up;
	काष्ठा mutex		paths_mutex;
	काष्ठा mutex		paths_ev_mutex;
	अक्षर			sessname[NAME_MAX];
	u16			port;
	अचिन्हित पूर्णांक		max_reconnect_attempts;
	अचिन्हित पूर्णांक		reconnect_delay_sec;
	अचिन्हित पूर्णांक		max_segments;
	व्योम			*permits;
	अचिन्हित दीर्घ		*permits_map;
	माप_प्रकार			queue_depth;
	माप_प्रकार			max_io_size;
	रुको_queue_head_t	permits_रुको;
	माप_प्रकार			pdu_sz;
	व्योम			*priv;
	व्योम			(*link_ev)(व्योम *priv,
					   क्रमागत rtrs_clt_link_ev ev);
	काष्ठा device		dev;
	काष्ठा kobject		*kobj_paths;
	क्रमागत rtrs_mp_policy	mp_policy;
पूर्ण;

अटल अंतरभूत काष्ठा rtrs_clt_con *to_clt_con(काष्ठा rtrs_con *c)
अणु
	वापस container_of(c, काष्ठा rtrs_clt_con, c);
पूर्ण

अटल अंतरभूत काष्ठा rtrs_clt_sess *to_clt_sess(काष्ठा rtrs_sess *s)
अणु
	वापस container_of(s, काष्ठा rtrs_clt_sess, s);
पूर्ण

अटल अंतरभूत पूर्णांक permit_size(काष्ठा rtrs_clt *clt)
अणु
	वापस माप(काष्ठा rtrs_permit) + clt->pdu_sz;
पूर्ण

अटल अंतरभूत काष्ठा rtrs_permit *get_permit(काष्ठा rtrs_clt *clt, पूर्णांक idx)
अणु
	वापस (काष्ठा rtrs_permit *)(clt->permits + permit_size(clt) * idx);
पूर्ण

पूर्णांक rtrs_clt_reconnect_from_sysfs(काष्ठा rtrs_clt_sess *sess);
पूर्णांक rtrs_clt_disconnect_from_sysfs(काष्ठा rtrs_clt_sess *sess);
पूर्णांक rtrs_clt_create_path_from_sysfs(काष्ठा rtrs_clt *clt,
				     काष्ठा rtrs_addr *addr);
पूर्णांक rtrs_clt_हटाओ_path_from_sysfs(काष्ठा rtrs_clt_sess *sess,
				     स्थिर काष्ठा attribute *sysfs_self);

व्योम rtrs_clt_set_max_reconnect_attempts(काष्ठा rtrs_clt *clt, पूर्णांक value);
पूर्णांक rtrs_clt_get_max_reconnect_attempts(स्थिर काष्ठा rtrs_clt *clt);
व्योम मुक्त_sess(काष्ठा rtrs_clt_sess *sess);

/* rtrs-clt-stats.c */

पूर्णांक rtrs_clt_init_stats(काष्ठा rtrs_clt_stats *stats);

व्योम rtrs_clt_inc_failover_cnt(काष्ठा rtrs_clt_stats *s);

व्योम rtrs_clt_update_wc_stats(काष्ठा rtrs_clt_con *con);
व्योम rtrs_clt_update_all_stats(काष्ठा rtrs_clt_io_req *req, पूर्णांक dir);

पूर्णांक rtrs_clt_reset_rdma_lat_distr_stats(काष्ठा rtrs_clt_stats *stats,
					 bool enable);
sमाप_प्रकार rtrs_clt_stats_rdma_lat_distr_to_str(काष्ठा rtrs_clt_stats *stats,
					      अक्षर *page, माप_प्रकार len);
पूर्णांक rtrs_clt_reset_cpu_migr_stats(काष्ठा rtrs_clt_stats *stats, bool enable);
पूर्णांक rtrs_clt_stats_migration_cnt_to_str(काष्ठा rtrs_clt_stats *stats, अक्षर *buf,
					 माप_प्रकार len);
पूर्णांक rtrs_clt_reset_reconnects_stat(काष्ठा rtrs_clt_stats *stats, bool enable);
पूर्णांक rtrs_clt_stats_reconnects_to_str(काष्ठा rtrs_clt_stats *stats, अक्षर *buf,
				      माप_प्रकार len);
पूर्णांक rtrs_clt_reset_wc_comp_stats(काष्ठा rtrs_clt_stats *stats, bool enable);
पूर्णांक rtrs_clt_stats_wc_completion_to_str(काष्ठा rtrs_clt_stats *stats, अक्षर *buf,
					 माप_प्रकार len);
पूर्णांक rtrs_clt_reset_rdma_stats(काष्ठा rtrs_clt_stats *stats, bool enable);
sमाप_प्रकार rtrs_clt_stats_rdma_to_str(काष्ठा rtrs_clt_stats *stats,
				    अक्षर *page, माप_प्रकार len);
पूर्णांक rtrs_clt_reset_all_stats(काष्ठा rtrs_clt_stats *stats, bool enable);
sमाप_प्रकार rtrs_clt_reset_all_help(काष्ठा rtrs_clt_stats *stats,
				 अक्षर *page, माप_प्रकार len);

/* rtrs-clt-sysfs.c */

पूर्णांक rtrs_clt_create_sysfs_root_files(काष्ठा rtrs_clt *clt);
व्योम rtrs_clt_destroy_sysfs_root(काष्ठा rtrs_clt *clt);

पूर्णांक rtrs_clt_create_sess_files(काष्ठा rtrs_clt_sess *sess);
व्योम rtrs_clt_destroy_sess_files(काष्ठा rtrs_clt_sess *sess,
				  स्थिर काष्ठा attribute *sysfs_self);

#पूर्ण_अगर /* RTRS_CLT_H */
