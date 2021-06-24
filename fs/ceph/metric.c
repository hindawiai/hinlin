<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/types.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/math64.h>

#समावेश "metric.h"
#समावेश "mds_client.h"

अटल bool ceph_mdsc_send_metrics(काष्ठा ceph_mds_client *mdsc,
				   काष्ठा ceph_mds_session *s)
अणु
	काष्ठा ceph_metric_head *head;
	काष्ठा ceph_metric_cap *cap;
	काष्ठा ceph_metric_पढ़ो_latency *पढ़ो;
	काष्ठा ceph_metric_ग_लिखो_latency *ग_लिखो;
	काष्ठा ceph_metric_metadata_latency *meta;
	काष्ठा ceph_metric_dlease *dlease;
	काष्ठा ceph_खोलोed_files *files;
	काष्ठा ceph_pinned_icaps *icaps;
	काष्ठा ceph_खोलोed_inodes *inodes;
	काष्ठा ceph_client_metric *m = &mdsc->metric;
	u64 nr_caps = atomic64_पढ़ो(&m->total_caps);
	काष्ठा ceph_msg *msg;
	काष्ठा बारpec64 ts;
	s64 sum;
	s32 items = 0;
	s32 len;

	len = माप(*head) + माप(*cap) + माप(*पढ़ो) + माप(*ग_लिखो)
	      + माप(*meta) + माप(*dlease) + माप(*files)
	      + माप(*icaps) + माप(*inodes);

	msg = ceph_msg_new(CEPH_MSG_CLIENT_METRICS, len, GFP_NOFS, true);
	अगर (!msg) अणु
		pr_err("send metrics to mds%d, failed to allocate message\n",
		       s->s_mds);
		वापस false;
	पूर्ण

	head = msg->front.iov_base;

	/* encode the cap metric */
	cap = (काष्ठा ceph_metric_cap *)(head + 1);
	cap->type = cpu_to_le32(CLIENT_METRIC_TYPE_CAP_INFO);
	cap->ver = 1;
	cap->compat = 1;
	cap->data_len = cpu_to_le32(माप(*cap) - 10);
	cap->hit = cpu_to_le64(percpu_counter_sum(&m->i_caps_hit));
	cap->mis = cpu_to_le64(percpu_counter_sum(&m->i_caps_mis));
	cap->total = cpu_to_le64(nr_caps);
	items++;

	/* encode the पढ़ो latency metric */
	पढ़ो = (काष्ठा ceph_metric_पढ़ो_latency *)(cap + 1);
	पढ़ो->type = cpu_to_le32(CLIENT_METRIC_TYPE_READ_LATENCY);
	पढ़ो->ver = 1;
	पढ़ो->compat = 1;
	पढ़ो->data_len = cpu_to_le32(माप(*पढ़ो) - 10);
	sum = m->पढ़ो_latency_sum;
	jअगरfies_to_बारpec64(sum, &ts);
	पढ़ो->sec = cpu_to_le32(ts.tv_sec);
	पढ़ो->nsec = cpu_to_le32(ts.tv_nsec);
	items++;

	/* encode the ग_लिखो latency metric */
	ग_लिखो = (काष्ठा ceph_metric_ग_लिखो_latency *)(पढ़ो + 1);
	ग_लिखो->type = cpu_to_le32(CLIENT_METRIC_TYPE_WRITE_LATENCY);
	ग_लिखो->ver = 1;
	ग_लिखो->compat = 1;
	ग_लिखो->data_len = cpu_to_le32(माप(*ग_लिखो) - 10);
	sum = m->ग_लिखो_latency_sum;
	jअगरfies_to_बारpec64(sum, &ts);
	ग_लिखो->sec = cpu_to_le32(ts.tv_sec);
	ग_लिखो->nsec = cpu_to_le32(ts.tv_nsec);
	items++;

	/* encode the metadata latency metric */
	meta = (काष्ठा ceph_metric_metadata_latency *)(ग_लिखो + 1);
	meta->type = cpu_to_le32(CLIENT_METRIC_TYPE_METADATA_LATENCY);
	meta->ver = 1;
	meta->compat = 1;
	meta->data_len = cpu_to_le32(माप(*meta) - 10);
	sum = m->metadata_latency_sum;
	jअगरfies_to_बारpec64(sum, &ts);
	meta->sec = cpu_to_le32(ts.tv_sec);
	meta->nsec = cpu_to_le32(ts.tv_nsec);
	items++;

	/* encode the dentry lease metric */
	dlease = (काष्ठा ceph_metric_dlease *)(meta + 1);
	dlease->type = cpu_to_le32(CLIENT_METRIC_TYPE_DENTRY_LEASE);
	dlease->ver = 1;
	dlease->compat = 1;
	dlease->data_len = cpu_to_le32(माप(*dlease) - 10);
	dlease->hit = cpu_to_le64(percpu_counter_sum(&m->d_lease_hit));
	dlease->mis = cpu_to_le64(percpu_counter_sum(&m->d_lease_mis));
	dlease->total = cpu_to_le64(atomic64_पढ़ो(&m->total_dentries));
	items++;

	sum = percpu_counter_sum(&m->total_inodes);

	/* encode the खोलोed files metric */
	files = (काष्ठा ceph_खोलोed_files *)(dlease + 1);
	files->type = cpu_to_le32(CLIENT_METRIC_TYPE_OPENED_खाताS);
	files->ver = 1;
	files->compat = 1;
	files->data_len = cpu_to_le32(माप(*files) - 10);
	files->खोलोed_files = cpu_to_le64(atomic64_पढ़ो(&m->खोलोed_files));
	files->total = cpu_to_le64(sum);
	items++;

	/* encode the pinned icaps metric */
	icaps = (काष्ठा ceph_pinned_icaps *)(files + 1);
	icaps->type = cpu_to_le32(CLIENT_METRIC_TYPE_PINNED_ICAPS);
	icaps->ver = 1;
	icaps->compat = 1;
	icaps->data_len = cpu_to_le32(माप(*icaps) - 10);
	icaps->pinned_icaps = cpu_to_le64(nr_caps);
	icaps->total = cpu_to_le64(sum);
	items++;

	/* encode the खोलोed inodes metric */
	inodes = (काष्ठा ceph_खोलोed_inodes *)(icaps + 1);
	inodes->type = cpu_to_le32(CLIENT_METRIC_TYPE_OPENED_INODES);
	inodes->ver = 1;
	inodes->compat = 1;
	inodes->data_len = cpu_to_le32(माप(*inodes) - 10);
	inodes->खोलोed_inodes = cpu_to_le64(percpu_counter_sum(&m->खोलोed_inodes));
	inodes->total = cpu_to_le64(sum);
	items++;

	put_unaligned_le32(items, &head->num);
	msg->front.iov_len = len;
	msg->hdr.version = cpu_to_le16(1);
	msg->hdr.compat_version = cpu_to_le16(1);
	msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);
	करोut("client%llu send metrics to mds%d\n",
	     ceph_client_gid(mdsc->fsc->client), s->s_mds);
	ceph_con_send(&s->s_con, msg);

	वापस true;
पूर्ण


अटल व्योम metric_get_session(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_mds_session *s;
	पूर्णांक i;

	mutex_lock(&mdsc->mutex);
	क्रम (i = 0; i < mdsc->max_sessions; i++) अणु
		s = __ceph_lookup_mds_session(mdsc, i);
		अगर (!s)
			जारी;

		/*
		 * Skip it अगर MDS करोesn't support the metric collection,
		 * or the MDS will बंद the session's socket connection
		 * directly when it get this message.
		 */
		अगर (check_session_state(s) &&
		    test_bit(CEPHFS_FEATURE_METRIC_COLLECT, &s->s_features)) अणु
			mdsc->metric.session = s;
			अवरोध;
		पूर्ण

		ceph_put_mds_session(s);
	पूर्ण
	mutex_unlock(&mdsc->mutex);
पूर्ण

अटल व्योम metric_delayed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_client_metric *m =
		container_of(work, काष्ठा ceph_client_metric, delayed_work.work);
	काष्ठा ceph_mds_client *mdsc =
		container_of(m, काष्ठा ceph_mds_client, metric);

	अगर (mdsc->stopping)
		वापस;

	अगर (!m->session || !check_session_state(m->session)) अणु
		अगर (m->session) अणु
			ceph_put_mds_session(m->session);
			m->session = शून्य;
		पूर्ण
		metric_get_session(mdsc);
	पूर्ण
	अगर (m->session) अणु
		ceph_mdsc_send_metrics(mdsc, m->session);
		metric_schedule_delayed(m);
	पूर्ण
पूर्ण

पूर्णांक ceph_metric_init(काष्ठा ceph_client_metric *m)
अणु
	पूर्णांक ret;

	अगर (!m)
		वापस -EINVAL;

	atomic64_set(&m->total_dentries, 0);
	ret = percpu_counter_init(&m->d_lease_hit, 0, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	ret = percpu_counter_init(&m->d_lease_mis, 0, GFP_KERNEL);
	अगर (ret)
		जाओ err_d_lease_mis;

	atomic64_set(&m->total_caps, 0);
	ret = percpu_counter_init(&m->i_caps_hit, 0, GFP_KERNEL);
	अगर (ret)
		जाओ err_i_caps_hit;

	ret = percpu_counter_init(&m->i_caps_mis, 0, GFP_KERNEL);
	अगर (ret)
		जाओ err_i_caps_mis;

	spin_lock_init(&m->पढ़ो_metric_lock);
	m->पढ़ो_latency_sq_sum = 0;
	m->पढ़ो_latency_min = KTIME_MAX;
	m->पढ़ो_latency_max = 0;
	m->total_पढ़ोs = 0;
	m->पढ़ो_latency_sum = 0;

	spin_lock_init(&m->ग_लिखो_metric_lock);
	m->ग_लिखो_latency_sq_sum = 0;
	m->ग_लिखो_latency_min = KTIME_MAX;
	m->ग_लिखो_latency_max = 0;
	m->total_ग_लिखोs = 0;
	m->ग_लिखो_latency_sum = 0;

	spin_lock_init(&m->metadata_metric_lock);
	m->metadata_latency_sq_sum = 0;
	m->metadata_latency_min = KTIME_MAX;
	m->metadata_latency_max = 0;
	m->total_metadatas = 0;
	m->metadata_latency_sum = 0;

	atomic64_set(&m->खोलोed_files, 0);
	ret = percpu_counter_init(&m->खोलोed_inodes, 0, GFP_KERNEL);
	अगर (ret)
		जाओ err_खोलोed_inodes;
	ret = percpu_counter_init(&m->total_inodes, 0, GFP_KERNEL);
	अगर (ret)
		जाओ err_total_inodes;

	m->session = शून्य;
	INIT_DELAYED_WORK(&m->delayed_work, metric_delayed_work);

	वापस 0;

err_total_inodes:
	percpu_counter_destroy(&m->खोलोed_inodes);
err_खोलोed_inodes:
	percpu_counter_destroy(&m->i_caps_mis);
err_i_caps_mis:
	percpu_counter_destroy(&m->i_caps_hit);
err_i_caps_hit:
	percpu_counter_destroy(&m->d_lease_mis);
err_d_lease_mis:
	percpu_counter_destroy(&m->d_lease_hit);

	वापस ret;
पूर्ण

व्योम ceph_metric_destroy(काष्ठा ceph_client_metric *m)
अणु
	अगर (!m)
		वापस;

	percpu_counter_destroy(&m->total_inodes);
	percpu_counter_destroy(&m->खोलोed_inodes);
	percpu_counter_destroy(&m->i_caps_mis);
	percpu_counter_destroy(&m->i_caps_hit);
	percpu_counter_destroy(&m->d_lease_mis);
	percpu_counter_destroy(&m->d_lease_hit);

	cancel_delayed_work_sync(&m->delayed_work);

	अगर (m->session)
		ceph_put_mds_session(m->session);
पूर्ण

अटल अंतरभूत व्योम __update_latency(kसमय_प्रकार *totalp, kसमय_प्रकार *lsump,
				    kसमय_प्रकार *min, kसमय_प्रकार *max,
				    kसमय_प्रकार *sq_sump, kसमय_प्रकार lat)
अणु
	kसमय_प्रकार total, avg, sq, lsum;

	total = ++(*totalp);
	lsum = (*lsump += lat);

	अगर (unlikely(lat < *min))
		*min = lat;
	अगर (unlikely(lat > *max))
		*max = lat;

	अगर (unlikely(total == 1))
		वापस;

	/* the sq is (lat - old_avg) * (lat - new_avg) */
	avg = DIV64_U64_ROUND_CLOSEST((lsum - lat), (total - 1));
	sq = lat - avg;
	avg = DIV64_U64_ROUND_CLOSEST(lsum, total);
	sq = sq * (lat - avg);
	*sq_sump += sq;
पूर्ण

व्योम ceph_update_पढ़ो_metrics(काष्ठा ceph_client_metric *m,
			      kसमय_प्रकार r_start, kसमय_प्रकार r_end,
			      पूर्णांक rc)
अणु
	kसमय_प्रकार lat = kसमय_sub(r_end, r_start);

	अगर (unlikely(rc < 0 && rc != -ENOENT && rc != -ETIMEDOUT))
		वापस;

	spin_lock(&m->पढ़ो_metric_lock);
	__update_latency(&m->total_पढ़ोs, &m->पढ़ो_latency_sum,
			 &m->पढ़ो_latency_min, &m->पढ़ो_latency_max,
			 &m->पढ़ो_latency_sq_sum, lat);
	spin_unlock(&m->पढ़ो_metric_lock);
पूर्ण

व्योम ceph_update_ग_लिखो_metrics(काष्ठा ceph_client_metric *m,
			       kसमय_प्रकार r_start, kसमय_प्रकार r_end,
			       पूर्णांक rc)
अणु
	kसमय_प्रकार lat = kसमय_sub(r_end, r_start);

	अगर (unlikely(rc && rc != -ETIMEDOUT))
		वापस;

	spin_lock(&m->ग_लिखो_metric_lock);
	__update_latency(&m->total_ग_लिखोs, &m->ग_लिखो_latency_sum,
			 &m->ग_लिखो_latency_min, &m->ग_लिखो_latency_max,
			 &m->ग_लिखो_latency_sq_sum, lat);
	spin_unlock(&m->ग_लिखो_metric_lock);
पूर्ण

व्योम ceph_update_metadata_metrics(काष्ठा ceph_client_metric *m,
				  kसमय_प्रकार r_start, kसमय_प्रकार r_end,
				  पूर्णांक rc)
अणु
	kसमय_प्रकार lat = kसमय_sub(r_end, r_start);

	अगर (unlikely(rc && rc != -ENOENT))
		वापस;

	spin_lock(&m->metadata_metric_lock);
	__update_latency(&m->total_metadatas, &m->metadata_latency_sum,
			 &m->metadata_latency_min, &m->metadata_latency_max,
			 &m->metadata_latency_sq_sum, lat);
	spin_unlock(&m->metadata_metric_lock);
पूर्ण
