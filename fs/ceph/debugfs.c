<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/math64.h>
#समावेश <linux/kसमय.स>

#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/mon_client.h>
#समावेश <linux/ceph/auth.h>
#समावेश <linux/ceph/debugfs.h>

#समावेश "super.h"

#अगर_घोषित CONFIG_DEBUG_FS

#समावेश "mds_client.h"
#समावेश "metric.h"

अटल पूर्णांक mdsmap_show(काष्ठा seq_file *s, व्योम *p)
अणु
	पूर्णांक i;
	काष्ठा ceph_fs_client *fsc = s->निजी;
	काष्ठा ceph_mdsmap *mdsmap;

	अगर (!fsc->mdsc || !fsc->mdsc->mdsmap)
		वापस 0;
	mdsmap = fsc->mdsc->mdsmap;
	seq_म_लिखो(s, "epoch %d\n", mdsmap->m_epoch);
	seq_म_लिखो(s, "root %d\n", mdsmap->m_root);
	seq_म_लिखो(s, "max_mds %d\n", mdsmap->m_max_mds);
	seq_म_लिखो(s, "session_timeout %d\n", mdsmap->m_session_समयout);
	seq_म_लिखो(s, "session_autoclose %d\n", mdsmap->m_session_स्वतःबंद);
	क्रम (i = 0; i < mdsmap->possible_max_rank; i++) अणु
		काष्ठा ceph_entity_addr *addr = &mdsmap->m_info[i].addr;
		पूर्णांक state = mdsmap->m_info[i].state;
		seq_म_लिखो(s, "\tmds%d\t%s\t(%s)\n", i,
			       ceph_pr_addr(addr),
			       ceph_mds_state_name(state));
	पूर्ण
	वापस 0;
पूर्ण

/*
 * mdsc debugfs
 */
अटल पूर्णांक mdsc_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा ceph_fs_client *fsc = s->निजी;
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_mds_request *req;
	काष्ठा rb_node *rp;
	पूर्णांक pathlen = 0;
	u64 pathbase;
	अक्षर *path;

	mutex_lock(&mdsc->mutex);
	क्रम (rp = rb_first(&mdsc->request_tree); rp; rp = rb_next(rp)) अणु
		req = rb_entry(rp, काष्ठा ceph_mds_request, r_node);

		अगर (req->r_request && req->r_session)
			seq_म_लिखो(s, "%lld\tmds%d\t", req->r_tid,
				   req->r_session->s_mds);
		अन्यथा अगर (!req->r_request)
			seq_म_लिखो(s, "%lld\t(no request)\t", req->r_tid);
		अन्यथा
			seq_म_लिखो(s, "%lld\t(no session)\t", req->r_tid);

		seq_म_लिखो(s, "%s", ceph_mds_op_name(req->r_op));

		अगर (test_bit(CEPH_MDS_R_GOT_UNSAFE, &req->r_req_flags))
			seq_माला_दो(s, "\t(unsafe)");
		अन्यथा
			seq_माला_दो(s, "\t");

		अगर (req->r_inode) अणु
			seq_म_लिखो(s, " #%llx", ceph_ino(req->r_inode));
		पूर्ण अन्यथा अगर (req->r_dentry) अणु
			path = ceph_mdsc_build_path(req->r_dentry, &pathlen,
						    &pathbase, 0);
			अगर (IS_ERR(path))
				path = शून्य;
			spin_lock(&req->r_dentry->d_lock);
			seq_म_लिखो(s, " #%llx/%pd (%s)",
				   ceph_ino(d_inode(req->r_dentry->d_parent)),
				   req->r_dentry,
				   path ? path : "");
			spin_unlock(&req->r_dentry->d_lock);
			ceph_mdsc_मुक्त_path(path, pathlen);
		पूर्ण अन्यथा अगर (req->r_path1) अणु
			seq_म_लिखो(s, " #%llx/%s", req->r_ino1.ino,
				   req->r_path1);
		पूर्ण अन्यथा अणु
			seq_म_लिखो(s, " #%llx", req->r_ino1.ino);
		पूर्ण

		अगर (req->r_old_dentry) अणु
			path = ceph_mdsc_build_path(req->r_old_dentry, &pathlen,
						    &pathbase, 0);
			अगर (IS_ERR(path))
				path = शून्य;
			spin_lock(&req->r_old_dentry->d_lock);
			seq_म_लिखो(s, " #%llx/%pd (%s)",
				   req->r_old_dentry_dir ?
				   ceph_ino(req->r_old_dentry_dir) : 0,
				   req->r_old_dentry,
				   path ? path : "");
			spin_unlock(&req->r_old_dentry->d_lock);
			ceph_mdsc_मुक्त_path(path, pathlen);
		पूर्ण अन्यथा अगर (req->r_path2 && req->r_op != CEPH_MDS_OP_SYMLINK) अणु
			अगर (req->r_ino2.ino)
				seq_म_लिखो(s, " #%llx/%s", req->r_ino2.ino,
					   req->r_path2);
			अन्यथा
				seq_म_लिखो(s, " %s", req->r_path2);
		पूर्ण

		seq_माला_दो(s, "\n");
	पूर्ण
	mutex_unlock(&mdsc->mutex);

	वापस 0;
पूर्ण

#घोषणा CEPH_METRIC_SHOW(name, total, avg, min, max, sq) अणु		\
	s64 _total, _avg, _min, _max, _sq, _st;				\
	_avg = kसमय_प्रकारo_us(avg);					\
	_min = kसमय_प्रकारo_us(min == KTIME_MAX ? 0 : min);			\
	_max = kसमय_प्रकारo_us(max);					\
	_total = total - 1;						\
	_sq = _total > 0 ? DIV64_U64_ROUND_CLOSEST(sq, _total) : 0;	\
	_st = पूर्णांक_वर्ग_मूल64(_sq);						\
	_st = kसमय_प्रकारo_us(_st);						\
	seq_म_लिखो(s, "%-14s%-12lld%-16lld%-16lld%-16lld%lld\n",	\
		   name, total, _avg, _min, _max, _st);			\
पूर्ण

अटल पूर्णांक metric_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा ceph_fs_client *fsc = s->निजी;
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_client_metric *m = &mdsc->metric;
	पूर्णांक nr_caps = 0;
	s64 total, sum, avg, min, max, sq;

	sum = percpu_counter_sum(&m->total_inodes);
	seq_म_लिखो(s, "item                               total\n");
	seq_म_लिखो(s, "------------------------------------------\n");
	seq_म_लिखो(s, "%-35s%lld / %lld\n", "opened files  / total inodes",
		   atomic64_पढ़ो(&m->खोलोed_files), sum);
	seq_म_लिखो(s, "%-35s%lld / %lld\n", "pinned i_caps / total inodes",
		   atomic64_पढ़ो(&m->total_caps), sum);
	seq_म_लिखो(s, "%-35s%lld / %lld\n", "opened inodes / total inodes",
		   percpu_counter_sum(&m->खोलोed_inodes), sum);

	seq_म_लिखो(s, "\n");
	seq_म_लिखो(s, "item          total       avg_lat(us)     min_lat(us)     max_lat(us)     stdev(us)\n");
	seq_म_लिखो(s, "-----------------------------------------------------------------------------------\n");

	spin_lock(&m->पढ़ो_metric_lock);
	total = m->total_पढ़ोs;
	sum = m->पढ़ो_latency_sum;
	avg = total > 0 ? DIV64_U64_ROUND_CLOSEST(sum, total) : 0;
	min = m->पढ़ो_latency_min;
	max = m->पढ़ो_latency_max;
	sq = m->पढ़ो_latency_sq_sum;
	spin_unlock(&m->पढ़ो_metric_lock);
	CEPH_METRIC_SHOW("read", total, avg, min, max, sq);

	spin_lock(&m->ग_लिखो_metric_lock);
	total = m->total_ग_लिखोs;
	sum = m->ग_लिखो_latency_sum;
	avg = total > 0 ? DIV64_U64_ROUND_CLOSEST(sum, total) : 0;
	min = m->ग_लिखो_latency_min;
	max = m->ग_लिखो_latency_max;
	sq = m->ग_लिखो_latency_sq_sum;
	spin_unlock(&m->ग_लिखो_metric_lock);
	CEPH_METRIC_SHOW("write", total, avg, min, max, sq);

	spin_lock(&m->metadata_metric_lock);
	total = m->total_metadatas;
	sum = m->metadata_latency_sum;
	avg = total > 0 ? DIV64_U64_ROUND_CLOSEST(sum, total) : 0;
	min = m->metadata_latency_min;
	max = m->metadata_latency_max;
	sq = m->metadata_latency_sq_sum;
	spin_unlock(&m->metadata_metric_lock);
	CEPH_METRIC_SHOW("metadata", total, avg, min, max, sq);

	seq_म_लिखो(s, "\n");
	seq_म_लिखो(s, "item          total           miss            hit\n");
	seq_म_लिखो(s, "-------------------------------------------------\n");

	seq_म_लिखो(s, "%-14s%-16lld%-16lld%lld\n", "d_lease",
		   atomic64_पढ़ो(&m->total_dentries),
		   percpu_counter_sum(&m->d_lease_mis),
		   percpu_counter_sum(&m->d_lease_hit));

	nr_caps = atomic64_पढ़ो(&m->total_caps);
	seq_म_लिखो(s, "%-14s%-16d%-16lld%lld\n", "caps", nr_caps,
		   percpu_counter_sum(&m->i_caps_mis),
		   percpu_counter_sum(&m->i_caps_hit));

	वापस 0;
पूर्ण

अटल पूर्णांक caps_show_cb(काष्ठा inode *inode, काष्ठा ceph_cap *cap, व्योम *p)
अणु
	काष्ठा seq_file *s = p;

	seq_म_लिखो(s, "0x%-17llx%-3d%-17s%-17s\n", ceph_ino(inode),
		   cap->session->s_mds,
		   ceph_cap_string(cap->issued),
		   ceph_cap_string(cap->implemented));
	वापस 0;
पूर्ण

अटल पूर्णांक caps_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा ceph_fs_client *fsc = s->निजी;
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	पूर्णांक total, avail, used, reserved, min, i;
	काष्ठा cap_रुको	*cw;

	ceph_reservation_status(fsc, &total, &avail, &used, &reserved, &min);
	seq_म_लिखो(s, "total\t\t%d\n"
		   "avail\t\t%d\n"
		   "used\t\t%d\n"
		   "reserved\t%d\n"
		   "min\t\t%d\n\n",
		   total, avail, used, reserved, min);
	seq_म_लिखो(s, "ino              mds  issued           implemented\n");
	seq_म_लिखो(s, "--------------------------------------------------\n");

	mutex_lock(&mdsc->mutex);
	क्रम (i = 0; i < mdsc->max_sessions; i++) अणु
		काष्ठा ceph_mds_session *session;

		session = __ceph_lookup_mds_session(mdsc, i);
		अगर (!session)
			जारी;
		mutex_unlock(&mdsc->mutex);
		mutex_lock(&session->s_mutex);
		ceph_iterate_session_caps(session, caps_show_cb, s);
		mutex_unlock(&session->s_mutex);
		ceph_put_mds_session(session);
		mutex_lock(&mdsc->mutex);
	पूर्ण
	mutex_unlock(&mdsc->mutex);

	seq_म_लिखो(s, "\n\nWaiters:\n--------\n");
	seq_म_लिखो(s, "tgid         ino                need             want\n");
	seq_म_लिखो(s, "-----------------------------------------------------\n");

	spin_lock(&mdsc->caps_list_lock);
	list_क्रम_each_entry(cw, &mdsc->cap_रुको_list, list) अणु
		seq_म_लिखो(s, "%-13d0x%-17llx%-17s%-17s\n", cw->tgid, cw->ino,
				ceph_cap_string(cw->need),
				ceph_cap_string(cw->want));
	पूर्ण
	spin_unlock(&mdsc->caps_list_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mds_sessions_show(काष्ठा seq_file *s, व्योम *ptr)
अणु
	काष्ठा ceph_fs_client *fsc = s->निजी;
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_auth_client *ac = fsc->client->monc.auth;
	काष्ठा ceph_options *opt = fsc->client->options;
	पूर्णांक mds;

	mutex_lock(&mdsc->mutex);

	/* The 'num' portion of an 'entity name' */
	seq_म_लिखो(s, "global_id %llu\n", ac->global_id);

	/* The -o name mount argument */
	seq_म_लिखो(s, "name \"%s\"\n", opt->name ? opt->name : "");

	/* The list of MDS session rank+state */
	क्रम (mds = 0; mds < mdsc->max_sessions; mds++) अणु
		काष्ठा ceph_mds_session *session =
			__ceph_lookup_mds_session(mdsc, mds);
		अगर (!session) अणु
			जारी;
		पूर्ण
		mutex_unlock(&mdsc->mutex);
		seq_म_लिखो(s, "mds.%d %s\n",
				session->s_mds,
				ceph_session_state_name(session->s_state));

		ceph_put_mds_session(session);
		mutex_lock(&mdsc->mutex);
	पूर्ण
	mutex_unlock(&mdsc->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक status_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा ceph_fs_client *fsc = s->निजी;
	काष्ठा ceph_entity_inst *inst = &fsc->client->msgr.inst;
	काष्ठा ceph_entity_addr *client_addr = ceph_client_addr(fsc->client);

	seq_म_लिखो(s, "instance: %s.%lld %s/%u\n", ENTITY_NAME(inst->name),
		   ceph_pr_addr(client_addr), le32_to_cpu(client_addr->nonce));
	seq_म_लिखो(s, "blocklisted: %s\n", fsc->blocklisted ? "true" : "false");

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mdsmap);
DEFINE_SHOW_ATTRIBUTE(mdsc);
DEFINE_SHOW_ATTRIBUTE(caps);
DEFINE_SHOW_ATTRIBUTE(mds_sessions);
DEFINE_SHOW_ATTRIBUTE(metric);
DEFINE_SHOW_ATTRIBUTE(status);


/*
 * debugfs
 */
अटल पूर्णांक congestion_kb_set(व्योम *data, u64 val)
अणु
	काष्ठा ceph_fs_client *fsc = (काष्ठा ceph_fs_client *)data;

	fsc->mount_options->congestion_kb = (पूर्णांक)val;
	वापस 0;
पूर्ण

अटल पूर्णांक congestion_kb_get(व्योम *data, u64 *val)
अणु
	काष्ठा ceph_fs_client *fsc = (काष्ठा ceph_fs_client *)data;

	*val = (u64)fsc->mount_options->congestion_kb;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(congestion_kb_fops, congestion_kb_get,
			congestion_kb_set, "%llu\n");


व्योम ceph_fs_debugfs_cleanup(काष्ठा ceph_fs_client *fsc)
अणु
	करोut("ceph_fs_debugfs_cleanup\n");
	debugfs_हटाओ(fsc->debugfs_bdi);
	debugfs_हटाओ(fsc->debugfs_congestion_kb);
	debugfs_हटाओ(fsc->debugfs_mdsmap);
	debugfs_हटाओ(fsc->debugfs_mds_sessions);
	debugfs_हटाओ(fsc->debugfs_caps);
	debugfs_हटाओ(fsc->debugfs_metric);
	debugfs_हटाओ(fsc->debugfs_mdsc);
पूर्ण

व्योम ceph_fs_debugfs_init(काष्ठा ceph_fs_client *fsc)
अणु
	अक्षर name[100];

	करोut("ceph_fs_debugfs_init\n");
	fsc->debugfs_congestion_kb =
		debugfs_create_file("writeback_congestion_kb",
				    0600,
				    fsc->client->debugfs_dir,
				    fsc,
				    &congestion_kb_fops);

	snम_लिखो(name, माप(name), "../../bdi/%s",
		 bdi_dev_name(fsc->sb->s_bdi));
	fsc->debugfs_bdi =
		debugfs_create_symlink("bdi",
				       fsc->client->debugfs_dir,
				       name);

	fsc->debugfs_mdsmap = debugfs_create_file("mdsmap",
					0400,
					fsc->client->debugfs_dir,
					fsc,
					&mdsmap_fops);

	fsc->debugfs_mds_sessions = debugfs_create_file("mds_sessions",
					0400,
					fsc->client->debugfs_dir,
					fsc,
					&mds_sessions_fops);

	fsc->debugfs_mdsc = debugfs_create_file("mdsc",
						0400,
						fsc->client->debugfs_dir,
						fsc,
						&mdsc_fops);

	fsc->debugfs_metric = debugfs_create_file("metrics",
						  0400,
						  fsc->client->debugfs_dir,
						  fsc,
						  &metric_fops);

	fsc->debugfs_caps = debugfs_create_file("caps",
						0400,
						fsc->client->debugfs_dir,
						fsc,
						&caps_fops);

	fsc->debugfs_status = debugfs_create_file("status",
						  0400,
						  fsc->client->debugfs_dir,
						  fsc,
						  &status_fops);
पूर्ण


#अन्यथा  /* CONFIG_DEBUG_FS */

व्योम ceph_fs_debugfs_init(काष्ठा ceph_fs_client *fsc)
अणु
पूर्ण

व्योम ceph_fs_debugfs_cleanup(काष्ठा ceph_fs_client *fsc)
अणु
पूर्ण

#पूर्ण_अगर  /* CONFIG_DEBUG_FS */
