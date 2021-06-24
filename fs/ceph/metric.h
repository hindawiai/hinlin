<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_MDS_METRIC_H
#घोषणा _FS_CEPH_MDS_METRIC_H

#समावेश <linux/types.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/kसमय.स>

बाह्य bool disable_send_metrics;

क्रमागत ceph_metric_type अणु
	CLIENT_METRIC_TYPE_CAP_INFO,
	CLIENT_METRIC_TYPE_READ_LATENCY,
	CLIENT_METRIC_TYPE_WRITE_LATENCY,
	CLIENT_METRIC_TYPE_METADATA_LATENCY,
	CLIENT_METRIC_TYPE_DENTRY_LEASE,
	CLIENT_METRIC_TYPE_OPENED_खाताS,
	CLIENT_METRIC_TYPE_PINNED_ICAPS,
	CLIENT_METRIC_TYPE_OPENED_INODES,

	CLIENT_METRIC_TYPE_MAX = CLIENT_METRIC_TYPE_OPENED_INODES,
पूर्ण;

/*
 * This will always have the highest metric bit value
 * as the last element of the array.
 */
#घोषणा CEPHFS_METRIC_SPEC_CLIENT_SUPPORTED अणु	\
	CLIENT_METRIC_TYPE_CAP_INFO,		\
	CLIENT_METRIC_TYPE_READ_LATENCY,	\
	CLIENT_METRIC_TYPE_WRITE_LATENCY,	\
	CLIENT_METRIC_TYPE_METADATA_LATENCY,	\
	CLIENT_METRIC_TYPE_DENTRY_LEASE,	\
	CLIENT_METRIC_TYPE_OPENED_खाताS,	\
	CLIENT_METRIC_TYPE_PINNED_ICAPS,	\
	CLIENT_METRIC_TYPE_OPENED_INODES,	\
						\
	CLIENT_METRIC_TYPE_MAX,			\
पूर्ण

/* metric caps header */
काष्ठा ceph_metric_cap अणु
	__le32 type;     /* ceph metric type */

	__u8  ver;
	__u8  compat;

	__le32 data_len; /* length of माप(hit + mis + total) */
	__le64 hit;
	__le64 mis;
	__le64 total;
पूर्ण __packed;

/* metric पढ़ो latency header */
काष्ठा ceph_metric_पढ़ो_latency अणु
	__le32 type;     /* ceph metric type */

	__u8  ver;
	__u8  compat;

	__le32 data_len; /* length of माप(sec + nsec) */
	__le32 sec;
	__le32 nsec;
पूर्ण __packed;

/* metric ग_लिखो latency header */
काष्ठा ceph_metric_ग_लिखो_latency अणु
	__le32 type;     /* ceph metric type */

	__u8  ver;
	__u8  compat;

	__le32 data_len; /* length of माप(sec + nsec) */
	__le32 sec;
	__le32 nsec;
पूर्ण __packed;

/* metric metadata latency header */
काष्ठा ceph_metric_metadata_latency अणु
	__le32 type;     /* ceph metric type */

	__u8  ver;
	__u8  compat;

	__le32 data_len; /* length of माप(sec + nsec) */
	__le32 sec;
	__le32 nsec;
पूर्ण __packed;

/* metric dentry lease header */
काष्ठा ceph_metric_dlease अणु
	__le32 type;     /* ceph metric type */

	__u8  ver;
	__u8  compat;

	__le32 data_len; /* length of माप(hit + mis + total) */
	__le64 hit;
	__le64 mis;
	__le64 total;
पूर्ण __packed;

/* metric खोलोed files header */
काष्ठा ceph_खोलोed_files अणु
	__le32 type;     /* ceph metric type */

	__u8  ver;
	__u8  compat;

	__le32 data_len; /* length of माप(खोलोed_files + total) */
	__le64 खोलोed_files;
	__le64 total;
पूर्ण __packed;

/* metric pinned i_caps header */
काष्ठा ceph_pinned_icaps अणु
	__le32 type;     /* ceph metric type */

	__u8  ver;
	__u8  compat;

	__le32 data_len; /* length of माप(pinned_icaps + total) */
	__le64 pinned_icaps;
	__le64 total;
पूर्ण __packed;

/* metric खोलोed inodes header */
काष्ठा ceph_खोलोed_inodes अणु
	__le32 type;     /* ceph metric type */

	__u8  ver;
	__u8  compat;

	__le32 data_len; /* length of माप(खोलोed_inodes + total) */
	__le64 खोलोed_inodes;
	__le64 total;
पूर्ण __packed;

काष्ठा ceph_metric_head अणु
	__le32 num;	/* the number of metrics that will be sent */
पूर्ण __packed;

/* This is the global metrics */
काष्ठा ceph_client_metric अणु
	atomic64_t            total_dentries;
	काष्ठा percpu_counter d_lease_hit;
	काष्ठा percpu_counter d_lease_mis;

	atomic64_t            total_caps;
	काष्ठा percpu_counter i_caps_hit;
	काष्ठा percpu_counter i_caps_mis;

	spinlock_t पढ़ो_metric_lock;
	u64 total_पढ़ोs;
	kसमय_प्रकार पढ़ो_latency_sum;
	kसमय_प्रकार पढ़ो_latency_sq_sum;
	kसमय_प्रकार पढ़ो_latency_min;
	kसमय_प्रकार पढ़ो_latency_max;

	spinlock_t ग_लिखो_metric_lock;
	u64 total_ग_लिखोs;
	kसमय_प्रकार ग_लिखो_latency_sum;
	kसमय_प्रकार ग_लिखो_latency_sq_sum;
	kसमय_प्रकार ग_लिखो_latency_min;
	kसमय_प्रकार ग_लिखो_latency_max;

	spinlock_t metadata_metric_lock;
	u64 total_metadatas;
	kसमय_प्रकार metadata_latency_sum;
	kसमय_प्रकार metadata_latency_sq_sum;
	kसमय_प्रकार metadata_latency_min;
	kसमय_प्रकार metadata_latency_max;

	/* The total number of directories and files that are खोलोed */
	atomic64_t खोलोed_files;

	/* The total number of inodes that have खोलोed files or directories */
	काष्ठा percpu_counter खोलोed_inodes;
	काष्ठा percpu_counter total_inodes;

	काष्ठा ceph_mds_session *session;
	काष्ठा delayed_work delayed_work;  /* delayed work */
पूर्ण;

अटल अंतरभूत व्योम metric_schedule_delayed(काष्ठा ceph_client_metric *m)
अणु
	अगर (disable_send_metrics)
		वापस;

	/* per second */
	schedule_delayed_work(&m->delayed_work, round_jअगरfies_relative(HZ));
पूर्ण

बाह्य पूर्णांक ceph_metric_init(काष्ठा ceph_client_metric *m);
बाह्य व्योम ceph_metric_destroy(काष्ठा ceph_client_metric *m);

अटल अंतरभूत व्योम ceph_update_cap_hit(काष्ठा ceph_client_metric *m)
अणु
	percpu_counter_inc(&m->i_caps_hit);
पूर्ण

अटल अंतरभूत व्योम ceph_update_cap_mis(काष्ठा ceph_client_metric *m)
अणु
	percpu_counter_inc(&m->i_caps_mis);
पूर्ण

बाह्य व्योम ceph_update_पढ़ो_metrics(काष्ठा ceph_client_metric *m,
				     kसमय_प्रकार r_start, kसमय_प्रकार r_end,
				     पूर्णांक rc);
बाह्य व्योम ceph_update_ग_लिखो_metrics(काष्ठा ceph_client_metric *m,
				      kसमय_प्रकार r_start, kसमय_प्रकार r_end,
				      पूर्णांक rc);
बाह्य व्योम ceph_update_metadata_metrics(काष्ठा ceph_client_metric *m,
				         kसमय_प्रकार r_start, kसमय_प्रकार r_end,
					 पूर्णांक rc);
#पूर्ण_अगर /* _FS_CEPH_MDS_METRIC_H */
