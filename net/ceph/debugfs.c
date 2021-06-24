<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/mon_client.h>
#समावेश <linux/ceph/auth.h>
#समावेश <linux/ceph/debugfs.h>

#अगर_घोषित CONFIG_DEBUG_FS

/*
 * Implement /sys/kernel/debug/ceph fun
 *
 * /sys/kernel/debug/ceph/client*  - an instance of the ceph client
 *      .../osdmap      - current osdmap
 *      .../monmap      - current monmap
 *      .../osdc        - active osd requests
 *      .../monc        - mon client state
 *      .../client_options - libceph-only (i.e. not rbd or cephfs) options
 *      .../dentry_lru  - dump contents of dentry lru
 *      .../caps        - expose cap (reservation) stats
 *      .../bdi         - symlink to ../../bdi/something
 */

अटल काष्ठा dentry *ceph_debugfs_dir;

अटल पूर्णांक monmap_show(काष्ठा seq_file *s, व्योम *p)
अणु
	पूर्णांक i;
	काष्ठा ceph_client *client = s->निजी;

	अगर (client->monc.monmap == शून्य)
		वापस 0;

	seq_म_लिखो(s, "epoch %d\n", client->monc.monmap->epoch);
	क्रम (i = 0; i < client->monc.monmap->num_mon; i++) अणु
		काष्ठा ceph_entity_inst *inst =
			&client->monc.monmap->mon_inst[i];

		seq_म_लिखो(s, "\t%s%lld\t%s\n",
			   ENTITY_NAME(inst->name),
			   ceph_pr_addr(&inst->addr));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक osdmap_show(काष्ठा seq_file *s, व्योम *p)
अणु
	पूर्णांक i;
	काष्ठा ceph_client *client = s->निजी;
	काष्ठा ceph_osd_client *osdc = &client->osdc;
	काष्ठा ceph_osdmap *map = osdc->osdmap;
	काष्ठा rb_node *n;

	अगर (map == शून्य)
		वापस 0;

	करोwn_पढ़ो(&osdc->lock);
	seq_म_लिखो(s, "epoch %u barrier %u flags 0x%x\n", map->epoch,
			osdc->epoch_barrier, map->flags);

	क्रम (n = rb_first(&map->pg_pools); n; n = rb_next(n)) अणु
		काष्ठा ceph_pg_pool_info *pi =
			rb_entry(n, काष्ठा ceph_pg_pool_info, node);

		seq_म_लिखो(s, "pool %lld '%s' type %d size %d min_size %d pg_num %u pg_num_mask %d flags 0x%llx lfor %u read_tier %lld write_tier %lld\n",
			   pi->id, pi->name, pi->type, pi->size, pi->min_size,
			   pi->pg_num, pi->pg_num_mask, pi->flags,
			   pi->last_क्रमce_request_resend, pi->पढ़ो_tier,
			   pi->ग_लिखो_tier);
	पूर्ण
	क्रम (i = 0; i < map->max_osd; i++) अणु
		काष्ठा ceph_entity_addr *addr = &map->osd_addr[i];
		u32 state = map->osd_state[i];
		अक्षर sb[64];

		seq_म_लिखो(s, "osd%d\t%s\t%3d%%\t(%s)\t%3d%%\t%2d\n",
			   i, ceph_pr_addr(addr),
			   ((map->osd_weight[i]*100) >> 16),
			   ceph_osdmap_state_str(sb, माप(sb), state),
			   ((ceph_get_primary_affinity(map, i)*100) >> 16),
			   ceph_get_crush_locality(map, i,
					   &client->options->crush_locs));
	पूर्ण
	क्रम (n = rb_first(&map->pg_temp); n; n = rb_next(n)) अणु
		काष्ठा ceph_pg_mapping *pg =
			rb_entry(n, काष्ठा ceph_pg_mapping, node);

		seq_म_लिखो(s, "pg_temp %llu.%x [", pg->pgid.pool,
			   pg->pgid.seed);
		क्रम (i = 0; i < pg->pg_temp.len; i++)
			seq_म_लिखो(s, "%s%d", (i == 0 ? "" : ","),
				   pg->pg_temp.osds[i]);
		seq_म_लिखो(s, "]\n");
	पूर्ण
	क्रम (n = rb_first(&map->primary_temp); n; n = rb_next(n)) अणु
		काष्ठा ceph_pg_mapping *pg =
			rb_entry(n, काष्ठा ceph_pg_mapping, node);

		seq_म_लिखो(s, "primary_temp %llu.%x %d\n", pg->pgid.pool,
			   pg->pgid.seed, pg->primary_temp.osd);
	पूर्ण
	क्रम (n = rb_first(&map->pg_upmap); n; n = rb_next(n)) अणु
		काष्ठा ceph_pg_mapping *pg =
			rb_entry(n, काष्ठा ceph_pg_mapping, node);

		seq_म_लिखो(s, "pg_upmap %llu.%x [", pg->pgid.pool,
			   pg->pgid.seed);
		क्रम (i = 0; i < pg->pg_upmap.len; i++)
			seq_म_लिखो(s, "%s%d", (i == 0 ? "" : ","),
				   pg->pg_upmap.osds[i]);
		seq_म_लिखो(s, "]\n");
	पूर्ण
	क्रम (n = rb_first(&map->pg_upmap_items); n; n = rb_next(n)) अणु
		काष्ठा ceph_pg_mapping *pg =
			rb_entry(n, काष्ठा ceph_pg_mapping, node);

		seq_म_लिखो(s, "pg_upmap_items %llu.%x [", pg->pgid.pool,
			   pg->pgid.seed);
		क्रम (i = 0; i < pg->pg_upmap_items.len; i++)
			seq_म_लिखो(s, "%s%d->%d", (i == 0 ? "" : ","),
				   pg->pg_upmap_items.from_to[i][0],
				   pg->pg_upmap_items.from_to[i][1]);
		seq_म_लिखो(s, "]\n");
	पूर्ण

	up_पढ़ो(&osdc->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक monc_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा ceph_client *client = s->निजी;
	काष्ठा ceph_mon_generic_request *req;
	काष्ठा ceph_mon_client *monc = &client->monc;
	काष्ठा rb_node *rp;
	पूर्णांक i;

	mutex_lock(&monc->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(monc->subs); i++) अणु
		seq_म_लिखो(s, "have %s %u", ceph_sub_str[i],
			   monc->subs[i].have);
		अगर (monc->subs[i].want)
			seq_म_लिखो(s, " want %llu%s",
				   le64_to_cpu(monc->subs[i].item.start),
				   (monc->subs[i].item.flags &
					CEPH_SUBSCRIBE_ONETIME ?  "" : "+"));
		seq_अ_दो(s, '\n');
	पूर्ण
	seq_म_लिखो(s, "fs_cluster_id %d\n", monc->fs_cluster_id);

	क्रम (rp = rb_first(&monc->generic_request_tree); rp; rp = rb_next(rp)) अणु
		__u16 op;
		req = rb_entry(rp, काष्ठा ceph_mon_generic_request, node);
		op = le16_to_cpu(req->request->hdr.type);
		अगर (op == CEPH_MSG_STATFS)
			seq_म_लिखो(s, "%llu statfs\n", req->tid);
		अन्यथा अगर (op == CEPH_MSG_MON_GET_VERSION)
			seq_म_लिखो(s, "%llu mon_get_version", req->tid);
		अन्यथा
			seq_म_लिखो(s, "%llu unknown\n", req->tid);
	पूर्ण

	mutex_unlock(&monc->mutex);
	वापस 0;
पूर्ण

अटल व्योम dump_spgid(काष्ठा seq_file *s, स्थिर काष्ठा ceph_spg *spgid)
अणु
	seq_म_लिखो(s, "%llu.%x", spgid->pgid.pool, spgid->pgid.seed);
	अगर (spgid->shard != CEPH_SPG_NOSHARD)
		seq_म_लिखो(s, "s%d", spgid->shard);
पूर्ण

अटल व्योम dump_target(काष्ठा seq_file *s, काष्ठा ceph_osd_request_target *t)
अणु
	पूर्णांक i;

	seq_म_लिखो(s, "osd%d\t%llu.%x\t", t->osd, t->pgid.pool, t->pgid.seed);
	dump_spgid(s, &t->spgid);
	seq_माला_दो(s, "\t[");
	क्रम (i = 0; i < t->up.size; i++)
		seq_म_लिखो(s, "%s%d", (!i ? "" : ","), t->up.osds[i]);
	seq_म_लिखो(s, "]/%d\t[", t->up.primary);
	क्रम (i = 0; i < t->acting.size; i++)
		seq_म_लिखो(s, "%s%d", (!i ? "" : ","), t->acting.osds[i]);
	seq_म_लिखो(s, "]/%d\te%u\t", t->acting.primary, t->epoch);
	अगर (t->target_oloc.pool_ns) अणु
		seq_म_लिखो(s, "%*pE/%*pE\t0x%x",
			(पूर्णांक)t->target_oloc.pool_ns->len,
			t->target_oloc.pool_ns->str,
			t->target_oid.name_len, t->target_oid.name, t->flags);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(s, "%*pE\t0x%x", t->target_oid.name_len,
			t->target_oid.name, t->flags);
	पूर्ण
	अगर (t->छोड़ोd)
		seq_माला_दो(s, "\tP");
पूर्ण

अटल व्योम dump_request(काष्ठा seq_file *s, काष्ठा ceph_osd_request *req)
अणु
	पूर्णांक i;

	seq_म_लिखो(s, "%llu\t", req->r_tid);
	dump_target(s, &req->r_t);

	seq_म_लिखो(s, "\t%d", req->r_attempts);

	क्रम (i = 0; i < req->r_num_ops; i++) अणु
		काष्ठा ceph_osd_req_op *op = &req->r_ops[i];

		seq_म_लिखो(s, "%s%s", (i == 0 ? "\t" : ","),
			   ceph_osd_op_name(op->op));
		अगर (op->op == CEPH_OSD_OP_WATCH)
			seq_म_लिखो(s, "-%s",
				   ceph_osd_watch_op_name(op->watch.op));
		अन्यथा अगर (op->op == CEPH_OSD_OP_CALL)
			seq_म_लिखो(s, "-%s/%s", op->cls.class_name,
				   op->cls.method_name);
	पूर्ण

	seq_अ_दो(s, '\n');
पूर्ण

अटल व्योम dump_requests(काष्ठा seq_file *s, काष्ठा ceph_osd *osd)
अणु
	काष्ठा rb_node *n;

	mutex_lock(&osd->lock);
	क्रम (n = rb_first(&osd->o_requests); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd_request *req =
		    rb_entry(n, काष्ठा ceph_osd_request, r_node);

		dump_request(s, req);
	पूर्ण

	mutex_unlock(&osd->lock);
पूर्ण

अटल व्योम dump_linger_request(काष्ठा seq_file *s,
				काष्ठा ceph_osd_linger_request *lreq)
अणु
	seq_म_लिखो(s, "%llu\t", lreq->linger_id);
	dump_target(s, &lreq->t);

	seq_म_लिखो(s, "\t%u\t%s%s/%d\n", lreq->रेजिस्टर_gen,
		   lreq->is_watch ? "W" : "N", lreq->committed ? "C" : "",
		   lreq->last_error);
पूर्ण

अटल व्योम dump_linger_requests(काष्ठा seq_file *s, काष्ठा ceph_osd *osd)
अणु
	काष्ठा rb_node *n;

	mutex_lock(&osd->lock);
	क्रम (n = rb_first(&osd->o_linger_requests); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd_linger_request *lreq =
		    rb_entry(n, काष्ठा ceph_osd_linger_request, node);

		dump_linger_request(s, lreq);
	पूर्ण

	mutex_unlock(&osd->lock);
पूर्ण

अटल व्योम dump_snapid(काष्ठा seq_file *s, u64 snapid)
अणु
	अगर (snapid == CEPH_NOSNAP)
		seq_माला_दो(s, "head");
	अन्यथा अगर (snapid == CEPH_SNAPसूची)
		seq_माला_दो(s, "snapdir");
	अन्यथा
		seq_म_लिखो(s, "%llx", snapid);
पूर्ण

अटल व्योम dump_name_escaped(काष्ठा seq_file *s, अचिन्हित अक्षर *name,
			      माप_प्रकार len)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (name[i] == '%' || name[i] == ':' || name[i] == '/' ||
		    name[i] < 32 || name[i] >= 127) अणु
			seq_म_लिखो(s, "%%%02x", name[i]);
		पूर्ण अन्यथा अणु
			seq_अ_दो(s, name[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dump_hoid(काष्ठा seq_file *s, स्थिर काष्ठा ceph_hobject_id *hoid)
अणु
	अगर (hoid->snapid == 0 && hoid->hash == 0 && !hoid->is_max &&
	    hoid->pool == S64_MIN) अणु
		seq_माला_दो(s, "MIN");
		वापस;
	पूर्ण
	अगर (hoid->is_max) अणु
		seq_माला_दो(s, "MAX");
		वापस;
	पूर्ण
	seq_म_लिखो(s, "%lld:%08x:", hoid->pool, hoid->hash_reverse_bits);
	dump_name_escaped(s, hoid->nspace, hoid->nspace_len);
	seq_अ_दो(s, ':');
	dump_name_escaped(s, hoid->key, hoid->key_len);
	seq_अ_दो(s, ':');
	dump_name_escaped(s, hoid->oid, hoid->oid_len);
	seq_अ_दो(s, ':');
	dump_snapid(s, hoid->snapid);
पूर्ण

अटल व्योम dump_backoffs(काष्ठा seq_file *s, काष्ठा ceph_osd *osd)
अणु
	काष्ठा rb_node *n;

	mutex_lock(&osd->lock);
	क्रम (n = rb_first(&osd->o_backoffs_by_id); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd_backoff *backoff =
		    rb_entry(n, काष्ठा ceph_osd_backoff, id_node);

		seq_म_लिखो(s, "osd%d\t", osd->o_osd);
		dump_spgid(s, &backoff->spgid);
		seq_म_लिखो(s, "\t%llu\t", backoff->id);
		dump_hoid(s, backoff->begin);
		seq_अ_दो(s, '\t');
		dump_hoid(s, backoff->end);
		seq_अ_दो(s, '\n');
	पूर्ण

	mutex_unlock(&osd->lock);
पूर्ण

अटल पूर्णांक osdc_show(काष्ठा seq_file *s, व्योम *pp)
अणु
	काष्ठा ceph_client *client = s->निजी;
	काष्ठा ceph_osd_client *osdc = &client->osdc;
	काष्ठा rb_node *n;

	करोwn_पढ़ो(&osdc->lock);
	seq_म_लिखो(s, "REQUESTS %d homeless %d\n",
		   atomic_पढ़ो(&osdc->num_requests),
		   atomic_पढ़ो(&osdc->num_homeless));
	क्रम (n = rb_first(&osdc->osds); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd *osd = rb_entry(n, काष्ठा ceph_osd, o_node);

		dump_requests(s, osd);
	पूर्ण
	dump_requests(s, &osdc->homeless_osd);

	seq_माला_दो(s, "LINGER REQUESTS\n");
	क्रम (n = rb_first(&osdc->osds); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd *osd = rb_entry(n, काष्ठा ceph_osd, o_node);

		dump_linger_requests(s, osd);
	पूर्ण
	dump_linger_requests(s, &osdc->homeless_osd);

	seq_माला_दो(s, "BACKOFFS\n");
	क्रम (n = rb_first(&osdc->osds); n; n = rb_next(n)) अणु
		काष्ठा ceph_osd *osd = rb_entry(n, काष्ठा ceph_osd, o_node);

		dump_backoffs(s, osd);
	पूर्ण

	up_पढ़ो(&osdc->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक client_options_show(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा ceph_client *client = s->निजी;
	पूर्णांक ret;

	ret = ceph_prपूर्णांक_client_options(s, client, true);
	अगर (ret)
		वापस ret;

	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(monmap);
DEFINE_SHOW_ATTRIBUTE(osdmap);
DEFINE_SHOW_ATTRIBUTE(monc);
DEFINE_SHOW_ATTRIBUTE(osdc);
DEFINE_SHOW_ATTRIBUTE(client_options);

व्योम __init ceph_debugfs_init(व्योम)
अणु
	ceph_debugfs_dir = debugfs_create_dir("ceph", शून्य);
पूर्ण

व्योम ceph_debugfs_cleanup(व्योम)
अणु
	debugfs_हटाओ(ceph_debugfs_dir);
पूर्ण

व्योम ceph_debugfs_client_init(काष्ठा ceph_client *client)
अणु
	अक्षर name[80];

	snम_लिखो(name, माप(name), "%pU.client%lld", &client->fsid,
		 client->monc.auth->global_id);

	करोut("ceph_debugfs_client_init %p %s\n", client, name);

	client->debugfs_dir = debugfs_create_dir(name, ceph_debugfs_dir);

	client->monc.debugfs_file = debugfs_create_file("monc",
						      0400,
						      client->debugfs_dir,
						      client,
						      &monc_fops);

	client->osdc.debugfs_file = debugfs_create_file("osdc",
						      0400,
						      client->debugfs_dir,
						      client,
						      &osdc_fops);

	client->debugfs_monmap = debugfs_create_file("monmap",
					0400,
					client->debugfs_dir,
					client,
					&monmap_fops);

	client->debugfs_osdmap = debugfs_create_file("osdmap",
					0400,
					client->debugfs_dir,
					client,
					&osdmap_fops);

	client->debugfs_options = debugfs_create_file("client_options",
					0400,
					client->debugfs_dir,
					client,
					&client_options_fops);
पूर्ण

व्योम ceph_debugfs_client_cleanup(काष्ठा ceph_client *client)
अणु
	करोut("ceph_debugfs_client_cleanup %p\n", client);
	debugfs_हटाओ(client->debugfs_options);
	debugfs_हटाओ(client->debugfs_osdmap);
	debugfs_हटाओ(client->debugfs_monmap);
	debugfs_हटाओ(client->osdc.debugfs_file);
	debugfs_हटाओ(client->monc.debugfs_file);
	debugfs_हटाओ(client->debugfs_dir);
पूर्ण

#अन्यथा  /* CONFIG_DEBUG_FS */

व्योम __init ceph_debugfs_init(व्योम)
अणु
पूर्ण

व्योम ceph_debugfs_cleanup(व्योम)
अणु
पूर्ण

व्योम ceph_debugfs_client_init(काष्ठा ceph_client *client)
अणु
पूर्ण

व्योम ceph_debugfs_client_cleanup(काष्ठा ceph_client *client)
अणु
पूर्ण

#पूर्ण_अगर  /* CONFIG_DEBUG_FS */
