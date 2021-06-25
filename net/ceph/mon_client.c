<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>

#समावेश <linux/ceph/ceph_features.h>
#समावेश <linux/ceph/mon_client.h>
#समावेश <linux/ceph/libceph.h>
#समावेश <linux/ceph/debugfs.h>
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/auth.h>

/*
 * Interact with Ceph monitor cluster.  Handle requests क्रम new map
 * versions, and periodically resend as needed.  Also implement
 * statfs() and umount().
 *
 * A small cluster of Ceph "monitors" are responsible क्रम managing critical
 * cluster configuration and state inक्रमmation.  An odd number (e.g., 3, 5)
 * of cmon daemons use a modअगरied version of the Paxos part-समय parliament
 * algorithm to manage the MDS map (mds cluster membership), OSD map, and
 * list of clients who have mounted the file प्रणाली.
 *
 * We मुख्यtain an खोलो, active session with a monitor at all बार in order to
 * receive समयly MDSMap updates.  We periodically send a keepalive byte on the
 * TCP socket to ensure we detect a failure.  If the connection करोes अवरोध, we
 * अक्रमomly hunt क्रम a new monitor.  Once the connection is reestablished, we
 * resend any outstanding requests.
 */

अटल स्थिर काष्ठा ceph_connection_operations mon_con_ops;

अटल पूर्णांक __validate_auth(काष्ठा ceph_mon_client *monc);

अटल पूर्णांक decode_mon_info(व्योम **p, व्योम *end, bool msgr2,
			   काष्ठा ceph_entity_addr *addr)
अणु
	व्योम *mon_info_end;
	u32 काष्ठा_len;
	u8 काष्ठा_v;
	पूर्णांक ret;

	ret = ceph_start_decoding(p, end, 1, "mon_info_t", &काष्ठा_v,
				  &काष्ठा_len);
	अगर (ret)
		वापस ret;

	mon_info_end = *p + काष्ठा_len;
	ceph_decode_skip_string(p, end, e_inval);  /* skip mon name */
	ret = ceph_decode_entity_addrvec(p, end, msgr2, addr);
	अगर (ret)
		वापस ret;

	*p = mon_info_end;
	वापस 0;

e_inval:
	वापस -EINVAL;
पूर्ण

/*
 * Decode a monmap blob (e.g., during mount).
 *
 * Assume MonMap v3 (i.e. encoding with MONNAMES and MONENC).
 */
अटल काष्ठा ceph_monmap *ceph_monmap_decode(व्योम **p, व्योम *end, bool msgr2)
अणु
	काष्ठा ceph_monmap *monmap = शून्य;
	काष्ठा ceph_fsid fsid;
	u32 काष्ठा_len;
	पूर्णांक blob_len;
	पूर्णांक num_mon;
	u8 काष्ठा_v;
	u32 epoch;
	पूर्णांक ret;
	पूर्णांक i;

	ceph_decode_32_safe(p, end, blob_len, e_inval);
	ceph_decode_need(p, end, blob_len, e_inval);

	ret = ceph_start_decoding(p, end, 6, "monmap", &काष्ठा_v, &काष्ठा_len);
	अगर (ret)
		जाओ fail;

	करोut("%s struct_v %d\n", __func__, काष्ठा_v);
	ceph_decode_copy_safe(p, end, &fsid, माप(fsid), e_inval);
	ceph_decode_32_safe(p, end, epoch, e_inval);
	अगर (काष्ठा_v >= 6) अणु
		u32 feat_काष्ठा_len;
		u8 feat_काष्ठा_v;

		*p += माप(काष्ठा ceph_बारpec);  /* skip last_changed */
		*p += माप(काष्ठा ceph_बारpec);  /* skip created */

		ret = ceph_start_decoding(p, end, 1, "mon_feature_t",
					  &feat_काष्ठा_v, &feat_काष्ठा_len);
		अगर (ret)
			जाओ fail;

		*p += feat_काष्ठा_len;  /* skip persistent_features */

		ret = ceph_start_decoding(p, end, 1, "mon_feature_t",
					  &feat_काष्ठा_v, &feat_काष्ठा_len);
		अगर (ret)
			जाओ fail;

		*p += feat_काष्ठा_len;  /* skip optional_features */
	पूर्ण
	ceph_decode_32_safe(p, end, num_mon, e_inval);

	करोut("%s fsid %pU epoch %u num_mon %d\n", __func__, &fsid, epoch,
	     num_mon);
	अगर (num_mon > CEPH_MAX_MON)
		जाओ e_inval;

	monmap = kदो_स्मृति(काष्ठा_size(monmap, mon_inst, num_mon), GFP_NOIO);
	अगर (!monmap) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	monmap->fsid = fsid;
	monmap->epoch = epoch;
	monmap->num_mon = num_mon;

	/* legacy_mon_addr map or mon_info map */
	क्रम (i = 0; i < num_mon; i++) अणु
		काष्ठा ceph_entity_inst *inst = &monmap->mon_inst[i];

		ceph_decode_skip_string(p, end, e_inval);  /* skip mon name */
		inst->name.type = CEPH_ENTITY_TYPE_MON;
		inst->name.num = cpu_to_le64(i);

		अगर (काष्ठा_v >= 6)
			ret = decode_mon_info(p, end, msgr2, &inst->addr);
		अन्यथा
			ret = ceph_decode_entity_addr(p, end, &inst->addr);
		अगर (ret)
			जाओ fail;

		करोut("%s mon%d addr %s\n", __func__, i,
		     ceph_pr_addr(&inst->addr));
	पूर्ण

	वापस monmap;

e_inval:
	ret = -EINVAL;
fail:
	kमुक्त(monmap);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * वापस true अगर *addr is included in the monmap.
 */
पूर्णांक ceph_monmap_contains(काष्ठा ceph_monmap *m, काष्ठा ceph_entity_addr *addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < m->num_mon; i++) अणु
		अगर (ceph_addr_equal_no_type(addr, &m->mon_inst[i].addr))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Send an auth request.
 */
अटल व्योम __send_prepared_auth_request(काष्ठा ceph_mon_client *monc, पूर्णांक len)
अणु
	monc->pending_auth = 1;
	monc->m_auth->front.iov_len = len;
	monc->m_auth->hdr.front_len = cpu_to_le32(len);
	ceph_msg_revoke(monc->m_auth);
	ceph_msg_get(monc->m_auth);  /* keep our ref */
	ceph_con_send(&monc->con, monc->m_auth);
पूर्ण

/*
 * Close monitor session, अगर any.
 */
अटल व्योम __बंद_session(काष्ठा ceph_mon_client *monc)
अणु
	करोut("__close_session closing mon%d\n", monc->cur_mon);
	ceph_msg_revoke(monc->m_auth);
	ceph_msg_revoke_incoming(monc->m_auth_reply);
	ceph_msg_revoke(monc->m_subscribe);
	ceph_msg_revoke_incoming(monc->m_subscribe_ack);
	ceph_con_बंद(&monc->con);

	monc->pending_auth = 0;
	ceph_auth_reset(monc->auth);
पूर्ण

/*
 * Pick a new monitor at अक्रमom and set cur_mon.  If we are repicking
 * (i.e. cur_mon is alपढ़ोy set), be sure to pick a dअगरferent one.
 */
अटल व्योम pick_new_mon(काष्ठा ceph_mon_client *monc)
अणु
	पूर्णांक old_mon = monc->cur_mon;

	BUG_ON(monc->monmap->num_mon < 1);

	अगर (monc->monmap->num_mon == 1) अणु
		monc->cur_mon = 0;
	पूर्ण अन्यथा अणु
		पूर्णांक max = monc->monmap->num_mon;
		पूर्णांक o = -1;
		पूर्णांक n;

		अगर (monc->cur_mon >= 0) अणु
			अगर (monc->cur_mon < monc->monmap->num_mon)
				o = monc->cur_mon;
			अगर (o >= 0)
				max--;
		पूर्ण

		n = pअक्रमom_u32() % max;
		अगर (o >= 0 && n >= o)
			n++;

		monc->cur_mon = n;
	पूर्ण

	करोut("%s mon%d -> mon%d out of %d mons\n", __func__, old_mon,
	     monc->cur_mon, monc->monmap->num_mon);
पूर्ण

/*
 * Open a session with a new monitor.
 */
अटल व्योम __खोलो_session(काष्ठा ceph_mon_client *monc)
अणु
	पूर्णांक ret;

	pick_new_mon(monc);

	monc->hunting = true;
	अगर (monc->had_a_connection) अणु
		monc->hunt_mult *= CEPH_MONC_HUNT_BACKOFF;
		अगर (monc->hunt_mult > CEPH_MONC_HUNT_MAX_MULT)
			monc->hunt_mult = CEPH_MONC_HUNT_MAX_MULT;
	पूर्ण

	monc->sub_renew_after = jअगरfies; /* i.e., expired */
	monc->sub_renew_sent = 0;

	करोut("%s opening mon%d\n", __func__, monc->cur_mon);
	ceph_con_खोलो(&monc->con, CEPH_ENTITY_TYPE_MON, monc->cur_mon,
		      &monc->monmap->mon_inst[monc->cur_mon].addr);

	/*
	 * Queue a keepalive to ensure that in हाल of an early fault
	 * the messenger करोesn't put us पूर्णांकo STANDBY state and instead
	 * retries.  This also ensures that our बारtamp is valid by
	 * the समय we finish hunting and delayed_work() checks it.
	 */
	ceph_con_keepalive(&monc->con);
	अगर (ceph_msgr2(monc->client)) अणु
		monc->pending_auth = 1;
		वापस;
	पूर्ण

	/* initiate authentication handshake */
	ret = ceph_auth_build_hello(monc->auth,
				    monc->m_auth->front.iov_base,
				    monc->m_auth->front_alloc_len);
	BUG_ON(ret <= 0);
	__send_prepared_auth_request(monc, ret);
पूर्ण

अटल व्योम reखोलो_session(काष्ठा ceph_mon_client *monc)
अणु
	अगर (!monc->hunting)
		pr_info("mon%d %s session lost, hunting for new mon\n",
		    monc->cur_mon, ceph_pr_addr(&monc->con.peer_addr));

	__बंद_session(monc);
	__खोलो_session(monc);
पूर्ण

व्योम ceph_monc_reखोलो_session(काष्ठा ceph_mon_client *monc)
अणु
	mutex_lock(&monc->mutex);
	reखोलो_session(monc);
	mutex_unlock(&monc->mutex);
पूर्ण

अटल व्योम un_backoff(काष्ठा ceph_mon_client *monc)
अणु
	monc->hunt_mult /= 2; /* reduce by 50% */
	अगर (monc->hunt_mult < 1)
		monc->hunt_mult = 1;
	करोut("%s hunt_mult now %d\n", __func__, monc->hunt_mult);
पूर्ण

/*
 * Reschedule delayed work समयr.
 */
अटल व्योम __schedule_delayed(काष्ठा ceph_mon_client *monc)
अणु
	अचिन्हित दीर्घ delay;

	अगर (monc->hunting)
		delay = CEPH_MONC_HUNT_INTERVAL * monc->hunt_mult;
	अन्यथा
		delay = CEPH_MONC_PING_INTERVAL;

	करोut("__schedule_delayed after %lu\n", delay);
	mod_delayed_work(प्रणाली_wq, &monc->delayed_work,
			 round_jअगरfies_relative(delay));
पूर्ण

स्थिर अक्षर *ceph_sub_str[] = अणु
	[CEPH_SUB_MONMAP] = "monmap",
	[CEPH_SUB_OSDMAP] = "osdmap",
	[CEPH_SUB_FSMAP]  = "fsmap.user",
	[CEPH_SUB_MDSMAP] = "mdsmap",
पूर्ण;

/*
 * Send subscribe request क्रम one or more maps, according to
 * monc->subs.
 */
अटल व्योम __send_subscribe(काष्ठा ceph_mon_client *monc)
अणु
	काष्ठा ceph_msg *msg = monc->m_subscribe;
	व्योम *p = msg->front.iov_base;
	व्योम *स्थिर end = p + msg->front_alloc_len;
	पूर्णांक num = 0;
	पूर्णांक i;

	करोut("%s sent %lu\n", __func__, monc->sub_renew_sent);

	BUG_ON(monc->cur_mon < 0);

	अगर (!monc->sub_renew_sent)
		monc->sub_renew_sent = jअगरfies | 1; /* never 0 */

	msg->hdr.version = cpu_to_le16(2);

	क्रम (i = 0; i < ARRAY_SIZE(monc->subs); i++) अणु
		अगर (monc->subs[i].want)
			num++;
	पूर्ण
	BUG_ON(num < 1); /* monmap sub is always there */
	ceph_encode_32(&p, num);
	क्रम (i = 0; i < ARRAY_SIZE(monc->subs); i++) अणु
		अक्षर buf[32];
		पूर्णांक len;

		अगर (!monc->subs[i].want)
			जारी;

		len = प्र_लिखो(buf, "%s", ceph_sub_str[i]);
		अगर (i == CEPH_SUB_MDSMAP &&
		    monc->fs_cluster_id != CEPH_FS_CLUSTER_ID_NONE)
			len += प्र_लिखो(buf + len, ".%d", monc->fs_cluster_id);

		करोut("%s %s start %llu flags 0x%x\n", __func__, buf,
		     le64_to_cpu(monc->subs[i].item.start),
		     monc->subs[i].item.flags);
		ceph_encode_string(&p, end, buf, len);
		स_नकल(p, &monc->subs[i].item, माप(monc->subs[i].item));
		p += माप(monc->subs[i].item);
	पूर्ण

	BUG_ON(p > end);
	msg->front.iov_len = p - msg->front.iov_base;
	msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);
	ceph_msg_revoke(msg);
	ceph_con_send(&monc->con, ceph_msg_get(msg));
पूर्ण

अटल व्योम handle_subscribe_ack(काष्ठा ceph_mon_client *monc,
				 काष्ठा ceph_msg *msg)
अणु
	अचिन्हित पूर्णांक seconds;
	काष्ठा ceph_mon_subscribe_ack *h = msg->front.iov_base;

	अगर (msg->front.iov_len < माप(*h))
		जाओ bad;
	seconds = le32_to_cpu(h->duration);

	mutex_lock(&monc->mutex);
	अगर (monc->sub_renew_sent) अणु
		/*
		 * This is only needed क्रम legacy (infernalis or older)
		 * MONs -- see delayed_work().
		 */
		monc->sub_renew_after = monc->sub_renew_sent +
					    (seconds >> 1) * HZ - 1;
		करोut("%s sent %lu duration %d renew after %lu\n", __func__,
		     monc->sub_renew_sent, seconds, monc->sub_renew_after);
		monc->sub_renew_sent = 0;
	पूर्ण अन्यथा अणु
		करोut("%s sent %lu renew after %lu, ignoring\n", __func__,
		     monc->sub_renew_sent, monc->sub_renew_after);
	पूर्ण
	mutex_unlock(&monc->mutex);
	वापस;
bad:
	pr_err("got corrupt subscribe-ack msg\n");
	ceph_msg_dump(msg);
पूर्ण

/*
 * Register पूर्णांकerest in a map
 *
 * @sub: one of CEPH_SUB_*
 * @epoch: X क्रम "every map since X", or 0 क्रम "just the latest"
 */
अटल bool __ceph_monc_want_map(काष्ठा ceph_mon_client *monc, पूर्णांक sub,
				 u32 epoch, bool continuous)
अणु
	__le64 start = cpu_to_le64(epoch);
	u8 flags = !continuous ? CEPH_SUBSCRIBE_ONETIME : 0;

	करोut("%s %s epoch %u continuous %d\n", __func__, ceph_sub_str[sub],
	     epoch, continuous);

	अगर (monc->subs[sub].want &&
	    monc->subs[sub].item.start == start &&
	    monc->subs[sub].item.flags == flags)
		वापस false;

	monc->subs[sub].item.start = start;
	monc->subs[sub].item.flags = flags;
	monc->subs[sub].want = true;

	वापस true;
पूर्ण

bool ceph_monc_want_map(काष्ठा ceph_mon_client *monc, पूर्णांक sub, u32 epoch,
			bool continuous)
अणु
	bool need_request;

	mutex_lock(&monc->mutex);
	need_request = __ceph_monc_want_map(monc, sub, epoch, continuous);
	mutex_unlock(&monc->mutex);

	वापस need_request;
पूर्ण
EXPORT_SYMBOL(ceph_monc_want_map);

/*
 * Keep track of which maps we have
 *
 * @sub: one of CEPH_SUB_*
 */
अटल व्योम __ceph_monc_got_map(काष्ठा ceph_mon_client *monc, पूर्णांक sub,
				u32 epoch)
अणु
	करोut("%s %s epoch %u\n", __func__, ceph_sub_str[sub], epoch);

	अगर (monc->subs[sub].want) अणु
		अगर (monc->subs[sub].item.flags & CEPH_SUBSCRIBE_ONETIME)
			monc->subs[sub].want = false;
		अन्यथा
			monc->subs[sub].item.start = cpu_to_le64(epoch + 1);
	पूर्ण

	monc->subs[sub].have = epoch;
पूर्ण

व्योम ceph_monc_got_map(काष्ठा ceph_mon_client *monc, पूर्णांक sub, u32 epoch)
अणु
	mutex_lock(&monc->mutex);
	__ceph_monc_got_map(monc, sub, epoch);
	mutex_unlock(&monc->mutex);
पूर्ण
EXPORT_SYMBOL(ceph_monc_got_map);

व्योम ceph_monc_renew_subs(काष्ठा ceph_mon_client *monc)
अणु
	mutex_lock(&monc->mutex);
	__send_subscribe(monc);
	mutex_unlock(&monc->mutex);
पूर्ण
EXPORT_SYMBOL(ceph_monc_renew_subs);

/*
 * Wait क्रम an osdmap with a given epoch.
 *
 * @epoch: epoch to रुको क्रम
 * @समयout: in jअगरfies, 0 means "wait forever"
 */
पूर्णांक ceph_monc_रुको_osdmap(काष्ठा ceph_mon_client *monc, u32 epoch,
			  अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ started = jअगरfies;
	दीर्घ ret;

	mutex_lock(&monc->mutex);
	जबतक (monc->subs[CEPH_SUB_OSDMAP].have < epoch) अणु
		mutex_unlock(&monc->mutex);

		अगर (समयout && समय_after_eq(jअगरfies, started + समयout))
			वापस -ETIMEDOUT;

		ret = रुको_event_पूर्णांकerruptible_समयout(monc->client->auth_wq,
				     monc->subs[CEPH_SUB_OSDMAP].have >= epoch,
				     ceph_समयout_jअगरfies(समयout));
		अगर (ret < 0)
			वापस ret;

		mutex_lock(&monc->mutex);
	पूर्ण

	mutex_unlock(&monc->mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_monc_रुको_osdmap);

/*
 * Open a session with a अक्रमom monitor.  Request monmap and osdmap,
 * which are रुकोed upon in __ceph_खोलो_session().
 */
पूर्णांक ceph_monc_खोलो_session(काष्ठा ceph_mon_client *monc)
अणु
	mutex_lock(&monc->mutex);
	__ceph_monc_want_map(monc, CEPH_SUB_MONMAP, 0, true);
	__ceph_monc_want_map(monc, CEPH_SUB_OSDMAP, 0, false);
	__खोलो_session(monc);
	__schedule_delayed(monc);
	mutex_unlock(&monc->mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_monc_खोलो_session);

अटल व्योम ceph_monc_handle_map(काष्ठा ceph_mon_client *monc,
				 काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_client *client = monc->client;
	काष्ठा ceph_monmap *monmap;
	व्योम *p, *end;

	mutex_lock(&monc->mutex);

	करोut("handle_monmap\n");
	p = msg->front.iov_base;
	end = p + msg->front.iov_len;

	monmap = ceph_monmap_decode(&p, end, ceph_msgr2(client));
	अगर (IS_ERR(monmap)) अणु
		pr_err("problem decoding monmap, %d\n",
		       (पूर्णांक)PTR_ERR(monmap));
		ceph_msg_dump(msg);
		जाओ out;
	पूर्ण

	अगर (ceph_check_fsid(client, &monmap->fsid) < 0) अणु
		kमुक्त(monmap);
		जाओ out;
	पूर्ण

	kमुक्त(monc->monmap);
	monc->monmap = monmap;

	__ceph_monc_got_map(monc, CEPH_SUB_MONMAP, monc->monmap->epoch);
	client->have_fsid = true;

out:
	mutex_unlock(&monc->mutex);
	wake_up_all(&client->auth_wq);
पूर्ण

/*
 * generic requests (currently statfs, mon_get_version)
 */
DEFINE_RB_FUNCS(generic_request, काष्ठा ceph_mon_generic_request, tid, node)

अटल व्योम release_generic_request(काष्ठा kref *kref)
अणु
	काष्ठा ceph_mon_generic_request *req =
		container_of(kref, काष्ठा ceph_mon_generic_request, kref);

	करोut("%s greq %p request %p reply %p\n", __func__, req, req->request,
	     req->reply);
	WARN_ON(!RB_EMPTY_NODE(&req->node));

	अगर (req->reply)
		ceph_msg_put(req->reply);
	अगर (req->request)
		ceph_msg_put(req->request);

	kमुक्त(req);
पूर्ण

अटल व्योम put_generic_request(काष्ठा ceph_mon_generic_request *req)
अणु
	अगर (req)
		kref_put(&req->kref, release_generic_request);
पूर्ण

अटल व्योम get_generic_request(काष्ठा ceph_mon_generic_request *req)
अणु
	kref_get(&req->kref);
पूर्ण

अटल काष्ठा ceph_mon_generic_request *
alloc_generic_request(काष्ठा ceph_mon_client *monc, gfp_t gfp)
अणु
	काष्ठा ceph_mon_generic_request *req;

	req = kzalloc(माप(*req), gfp);
	अगर (!req)
		वापस शून्य;

	req->monc = monc;
	kref_init(&req->kref);
	RB_CLEAR_NODE(&req->node);
	init_completion(&req->completion);

	करोut("%s greq %p\n", __func__, req);
	वापस req;
पूर्ण

अटल व्योम रेजिस्टर_generic_request(काष्ठा ceph_mon_generic_request *req)
अणु
	काष्ठा ceph_mon_client *monc = req->monc;

	WARN_ON(req->tid);

	get_generic_request(req);
	req->tid = ++monc->last_tid;
	insert_generic_request(&monc->generic_request_tree, req);
पूर्ण

अटल व्योम send_generic_request(काष्ठा ceph_mon_client *monc,
				 काष्ठा ceph_mon_generic_request *req)
अणु
	WARN_ON(!req->tid);

	करोut("%s greq %p tid %llu\n", __func__, req, req->tid);
	req->request->hdr.tid = cpu_to_le64(req->tid);
	ceph_con_send(&monc->con, ceph_msg_get(req->request));
पूर्ण

अटल व्योम __finish_generic_request(काष्ठा ceph_mon_generic_request *req)
अणु
	काष्ठा ceph_mon_client *monc = req->monc;

	करोut("%s greq %p tid %llu\n", __func__, req, req->tid);
	erase_generic_request(&monc->generic_request_tree, req);

	ceph_msg_revoke(req->request);
	ceph_msg_revoke_incoming(req->reply);
पूर्ण

अटल व्योम finish_generic_request(काष्ठा ceph_mon_generic_request *req)
अणु
	__finish_generic_request(req);
	put_generic_request(req);
पूर्ण

अटल व्योम complete_generic_request(काष्ठा ceph_mon_generic_request *req)
अणु
	अगर (req->complete_cb)
		req->complete_cb(req);
	अन्यथा
		complete_all(&req->completion);
	put_generic_request(req);
पूर्ण

अटल व्योम cancel_generic_request(काष्ठा ceph_mon_generic_request *req)
अणु
	काष्ठा ceph_mon_client *monc = req->monc;
	काष्ठा ceph_mon_generic_request *lookup_req;

	करोut("%s greq %p tid %llu\n", __func__, req, req->tid);

	mutex_lock(&monc->mutex);
	lookup_req = lookup_generic_request(&monc->generic_request_tree,
					    req->tid);
	अगर (lookup_req) अणु
		WARN_ON(lookup_req != req);
		finish_generic_request(req);
	पूर्ण

	mutex_unlock(&monc->mutex);
पूर्ण

अटल पूर्णांक रुको_generic_request(काष्ठा ceph_mon_generic_request *req)
अणु
	पूर्णांक ret;

	करोut("%s greq %p tid %llu\n", __func__, req, req->tid);
	ret = रुको_क्रम_completion_पूर्णांकerruptible(&req->completion);
	अगर (ret)
		cancel_generic_request(req);
	अन्यथा
		ret = req->result; /* completed */

	वापस ret;
पूर्ण

अटल काष्ठा ceph_msg *get_generic_reply(काष्ठा ceph_connection *con,
					 काष्ठा ceph_msg_header *hdr,
					 पूर्णांक *skip)
अणु
	काष्ठा ceph_mon_client *monc = con->निजी;
	काष्ठा ceph_mon_generic_request *req;
	u64 tid = le64_to_cpu(hdr->tid);
	काष्ठा ceph_msg *m;

	mutex_lock(&monc->mutex);
	req = lookup_generic_request(&monc->generic_request_tree, tid);
	अगर (!req) अणु
		करोut("get_generic_reply %lld dne\n", tid);
		*skip = 1;
		m = शून्य;
	पूर्ण अन्यथा अणु
		करोut("get_generic_reply %lld got %p\n", tid, req->reply);
		*skip = 0;
		m = ceph_msg_get(req->reply);
		/*
		 * we करोn't need to track the connection पढ़ोing पूर्णांकo
		 * this reply because we only have one खोलो connection
		 * at a समय, ever.
		 */
	पूर्ण
	mutex_unlock(&monc->mutex);
	वापस m;
पूर्ण

/*
 * statfs
 */
अटल व्योम handle_statfs_reply(काष्ठा ceph_mon_client *monc,
				काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_mon_generic_request *req;
	काष्ठा ceph_mon_statfs_reply *reply = msg->front.iov_base;
	u64 tid = le64_to_cpu(msg->hdr.tid);

	करोut("%s msg %p tid %llu\n", __func__, msg, tid);

	अगर (msg->front.iov_len != माप(*reply))
		जाओ bad;

	mutex_lock(&monc->mutex);
	req = lookup_generic_request(&monc->generic_request_tree, tid);
	अगर (!req) अणु
		mutex_unlock(&monc->mutex);
		वापस;
	पूर्ण

	req->result = 0;
	*req->u.st = reply->st; /* काष्ठा */
	__finish_generic_request(req);
	mutex_unlock(&monc->mutex);

	complete_generic_request(req);
	वापस;

bad:
	pr_err("corrupt statfs reply, tid %llu\n", tid);
	ceph_msg_dump(msg);
पूर्ण

/*
 * Do a synchronous statfs().
 */
पूर्णांक ceph_monc_करो_statfs(काष्ठा ceph_mon_client *monc, u64 data_pool,
			काष्ठा ceph_statfs *buf)
अणु
	काष्ठा ceph_mon_generic_request *req;
	काष्ठा ceph_mon_statfs *h;
	पूर्णांक ret = -ENOMEM;

	req = alloc_generic_request(monc, GFP_NOFS);
	अगर (!req)
		जाओ out;

	req->request = ceph_msg_new(CEPH_MSG_STATFS, माप(*h), GFP_NOFS,
				    true);
	अगर (!req->request)
		जाओ out;

	req->reply = ceph_msg_new(CEPH_MSG_STATFS_REPLY, 64, GFP_NOFS, true);
	अगर (!req->reply)
		जाओ out;

	req->u.st = buf;
	req->request->hdr.version = cpu_to_le16(2);

	mutex_lock(&monc->mutex);
	रेजिस्टर_generic_request(req);
	/* fill out request */
	h = req->request->front.iov_base;
	h->monhdr.have_version = 0;
	h->monhdr.session_mon = cpu_to_le16(-1);
	h->monhdr.session_mon_tid = 0;
	h->fsid = monc->monmap->fsid;
	h->contains_data_pool = (data_pool != CEPH_NOPOOL);
	h->data_pool = cpu_to_le64(data_pool);
	send_generic_request(monc, req);
	mutex_unlock(&monc->mutex);

	ret = रुको_generic_request(req);
out:
	put_generic_request(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_monc_करो_statfs);

अटल व्योम handle_get_version_reply(काष्ठा ceph_mon_client *monc,
				     काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_mon_generic_request *req;
	u64 tid = le64_to_cpu(msg->hdr.tid);
	व्योम *p = msg->front.iov_base;
	व्योम *end = p + msg->front_alloc_len;
	u64 handle;

	करोut("%s msg %p tid %llu\n", __func__, msg, tid);

	ceph_decode_need(&p, end, 2*माप(u64), bad);
	handle = ceph_decode_64(&p);
	अगर (tid != 0 && tid != handle)
		जाओ bad;

	mutex_lock(&monc->mutex);
	req = lookup_generic_request(&monc->generic_request_tree, handle);
	अगर (!req) अणु
		mutex_unlock(&monc->mutex);
		वापस;
	पूर्ण

	req->result = 0;
	req->u.newest = ceph_decode_64(&p);
	__finish_generic_request(req);
	mutex_unlock(&monc->mutex);

	complete_generic_request(req);
	वापस;

bad:
	pr_err("corrupt mon_get_version reply, tid %llu\n", tid);
	ceph_msg_dump(msg);
पूर्ण

अटल काष्ठा ceph_mon_generic_request *
__ceph_monc_get_version(काष्ठा ceph_mon_client *monc, स्थिर अक्षर *what,
			ceph_monc_callback_t cb, u64 निजी_data)
अणु
	काष्ठा ceph_mon_generic_request *req;

	req = alloc_generic_request(monc, GFP_NOIO);
	अगर (!req)
		जाओ err_put_req;

	req->request = ceph_msg_new(CEPH_MSG_MON_GET_VERSION,
				    माप(u64) + माप(u32) + म_माप(what),
				    GFP_NOIO, true);
	अगर (!req->request)
		जाओ err_put_req;

	req->reply = ceph_msg_new(CEPH_MSG_MON_GET_VERSION_REPLY, 32, GFP_NOIO,
				  true);
	अगर (!req->reply)
		जाओ err_put_req;

	req->complete_cb = cb;
	req->निजी_data = निजी_data;

	mutex_lock(&monc->mutex);
	रेजिस्टर_generic_request(req);
	अणु
		व्योम *p = req->request->front.iov_base;
		व्योम *स्थिर end = p + req->request->front_alloc_len;

		ceph_encode_64(&p, req->tid); /* handle */
		ceph_encode_string(&p, end, what, म_माप(what));
		WARN_ON(p != end);
	पूर्ण
	send_generic_request(monc, req);
	mutex_unlock(&monc->mutex);

	वापस req;

err_put_req:
	put_generic_request(req);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * Send MMonGetVersion and रुको क्रम the reply.
 *
 * @what: one of "mdsmap", "osdmap" or "monmap"
 */
पूर्णांक ceph_monc_get_version(काष्ठा ceph_mon_client *monc, स्थिर अक्षर *what,
			  u64 *newest)
अणु
	काष्ठा ceph_mon_generic_request *req;
	पूर्णांक ret;

	req = __ceph_monc_get_version(monc, what, शून्य, 0);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	ret = रुको_generic_request(req);
	अगर (!ret)
		*newest = req->u.newest;

	put_generic_request(req);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_monc_get_version);

/*
 * Send MMonGetVersion,
 *
 * @what: one of "mdsmap", "osdmap" or "monmap"
 */
पूर्णांक ceph_monc_get_version_async(काष्ठा ceph_mon_client *monc, स्थिर अक्षर *what,
				ceph_monc_callback_t cb, u64 निजी_data)
अणु
	काष्ठा ceph_mon_generic_request *req;

	req = __ceph_monc_get_version(monc, what, cb, निजी_data);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	put_generic_request(req);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_monc_get_version_async);

अटल व्योम handle_command_ack(काष्ठा ceph_mon_client *monc,
			       काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_mon_generic_request *req;
	व्योम *p = msg->front.iov_base;
	व्योम *स्थिर end = p + msg->front_alloc_len;
	u64 tid = le64_to_cpu(msg->hdr.tid);

	करोut("%s msg %p tid %llu\n", __func__, msg, tid);

	ceph_decode_need(&p, end, माप(काष्ठा ceph_mon_request_header) +
							    माप(u32), bad);
	p += माप(काष्ठा ceph_mon_request_header);

	mutex_lock(&monc->mutex);
	req = lookup_generic_request(&monc->generic_request_tree, tid);
	अगर (!req) अणु
		mutex_unlock(&monc->mutex);
		वापस;
	पूर्ण

	req->result = ceph_decode_32(&p);
	__finish_generic_request(req);
	mutex_unlock(&monc->mutex);

	complete_generic_request(req);
	वापस;

bad:
	pr_err("corrupt mon_command ack, tid %llu\n", tid);
	ceph_msg_dump(msg);
पूर्ण

अटल __म_लिखो(2, 0)
पूर्णांक करो_mon_command_vargs(काष्ठा ceph_mon_client *monc, स्थिर अक्षर *fmt,
			 बहु_सूची ap)
अणु
	काष्ठा ceph_mon_generic_request *req;
	काष्ठा ceph_mon_command *h;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक len;

	req = alloc_generic_request(monc, GFP_NOIO);
	अगर (!req)
		जाओ out;

	req->request = ceph_msg_new(CEPH_MSG_MON_COMMAND, 256, GFP_NOIO, true);
	अगर (!req->request)
		जाओ out;

	req->reply = ceph_msg_new(CEPH_MSG_MON_COMMAND_ACK, 512, GFP_NOIO,
				  true);
	अगर (!req->reply)
		जाओ out;

	mutex_lock(&monc->mutex);
	रेजिस्टर_generic_request(req);
	h = req->request->front.iov_base;
	h->monhdr.have_version = 0;
	h->monhdr.session_mon = cpu_to_le16(-1);
	h->monhdr.session_mon_tid = 0;
	h->fsid = monc->monmap->fsid;
	h->num_strs = cpu_to_le32(1);
	len = भम_लिखो(h->str, fmt, ap);
	h->str_len = cpu_to_le32(len);
	send_generic_request(monc, req);
	mutex_unlock(&monc->mutex);

	ret = रुको_generic_request(req);
out:
	put_generic_request(req);
	वापस ret;
पूर्ण

अटल __म_लिखो(2, 3)
पूर्णांक करो_mon_command(काष्ठा ceph_mon_client *monc, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	बहु_शुरू(ap, fmt);
	ret = करो_mon_command_vargs(monc, fmt, ap);
	बहु_पूर्ण(ap);
	वापस ret;
पूर्ण

पूर्णांक ceph_monc_blocklist_add(काष्ठा ceph_mon_client *monc,
			    काष्ठा ceph_entity_addr *client_addr)
अणु
	पूर्णांक ret;

	ret = करो_mon_command(monc,
			     "{ \"prefix\": \"osd blocklist\", \
				\"blocklistop\": \"add\", \
				\"addr\": \"%pISpc/%u\" }",
			     &client_addr->in_addr,
			     le32_to_cpu(client_addr->nonce));
	अगर (ret == -EINVAL) अणु
		/*
		 * The monitor वापसs EINVAL on an unrecognized command.
		 * Try the legacy command -- it is exactly the same except
		 * क्रम the name.
		 */
		ret = करो_mon_command(monc,
				     "{ \"prefix\": \"osd blacklist\", \
					\"blacklistop\": \"add\", \
					\"addr\": \"%pISpc/%u\" }",
				     &client_addr->in_addr,
				     le32_to_cpu(client_addr->nonce));
	पूर्ण
	अगर (ret)
		वापस ret;

	/*
	 * Make sure we have the osdmap that includes the blocklist
	 * entry.  This is needed to ensure that the OSDs pick up the
	 * new blocklist beक्रमe processing any future requests from
	 * this client.
	 */
	वापस ceph_रुको_क्रम_latest_osdmap(monc->client, 0);
पूर्ण
EXPORT_SYMBOL(ceph_monc_blocklist_add);

/*
 * Resend pending generic requests.
 */
अटल व्योम __resend_generic_request(काष्ठा ceph_mon_client *monc)
अणु
	काष्ठा ceph_mon_generic_request *req;
	काष्ठा rb_node *p;

	क्रम (p = rb_first(&monc->generic_request_tree); p; p = rb_next(p)) अणु
		req = rb_entry(p, काष्ठा ceph_mon_generic_request, node);
		ceph_msg_revoke(req->request);
		ceph_msg_revoke_incoming(req->reply);
		ceph_con_send(&monc->con, ceph_msg_get(req->request));
	पूर्ण
पूर्ण

/*
 * Delayed work.  If we haven't mounted yet, retry.  Otherwise,
 * renew/retry subscription as needed (in हाल it is timing out, or we
 * got an ENOMEM).  And keep the monitor connection alive.
 */
अटल व्योम delayed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_mon_client *monc =
		container_of(work, काष्ठा ceph_mon_client, delayed_work.work);

	करोut("monc delayed_work\n");
	mutex_lock(&monc->mutex);
	अगर (monc->hunting) अणु
		करोut("%s continuing hunt\n", __func__);
		reखोलो_session(monc);
	पूर्ण अन्यथा अणु
		पूर्णांक is_auth = ceph_auth_is_authenticated(monc->auth);
		अगर (ceph_con_keepalive_expired(&monc->con,
					       CEPH_MONC_PING_TIMEOUT)) अणु
			करोut("monc keepalive timeout\n");
			is_auth = 0;
			reखोलो_session(monc);
		पूर्ण

		अगर (!monc->hunting) अणु
			ceph_con_keepalive(&monc->con);
			__validate_auth(monc);
			un_backoff(monc);
		पूर्ण

		अगर (is_auth &&
		    !(monc->con.peer_features & CEPH_FEATURE_MON_STATEFUL_SUB)) अणु
			अचिन्हित दीर्घ now = jअगरfies;

			करोut("%s renew subs? now %lu renew after %lu\n",
			     __func__, now, monc->sub_renew_after);
			अगर (समय_after_eq(now, monc->sub_renew_after))
				__send_subscribe(monc);
		पूर्ण
	पूर्ण
	__schedule_delayed(monc);
	mutex_unlock(&monc->mutex);
पूर्ण

/*
 * On startup, we build a temporary monmap populated with the IPs
 * provided by mount(2).
 */
अटल पूर्णांक build_initial_monmap(काष्ठा ceph_mon_client *monc)
अणु
	__le32 my_type = ceph_msgr2(monc->client) ?
		CEPH_ENTITY_ADDR_TYPE_MSGR2 : CEPH_ENTITY_ADDR_TYPE_LEGACY;
	काष्ठा ceph_options *opt = monc->client->options;
	पूर्णांक num_mon = opt->num_mon;
	पूर्णांक i;

	/* build initial monmap */
	monc->monmap = kzalloc(काष्ठा_size(monc->monmap, mon_inst, num_mon),
			       GFP_KERNEL);
	अगर (!monc->monmap)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_mon; i++) अणु
		काष्ठा ceph_entity_inst *inst = &monc->monmap->mon_inst[i];

		स_नकल(&inst->addr.in_addr, &opt->mon_addr[i].in_addr,
		       माप(inst->addr.in_addr));
		inst->addr.type = my_type;
		inst->addr.nonce = 0;
		inst->name.type = CEPH_ENTITY_TYPE_MON;
		inst->name.num = cpu_to_le64(i);
	पूर्ण
	monc->monmap->num_mon = num_mon;
	वापस 0;
पूर्ण

पूर्णांक ceph_monc_init(काष्ठा ceph_mon_client *monc, काष्ठा ceph_client *cl)
अणु
	पूर्णांक err = 0;

	करोut("init\n");
	स_रखो(monc, 0, माप(*monc));
	monc->client = cl;
	monc->monmap = शून्य;
	mutex_init(&monc->mutex);

	err = build_initial_monmap(monc);
	अगर (err)
		जाओ out;

	/* connection */
	/* authentication */
	monc->auth = ceph_auth_init(cl->options->name, cl->options->key,
				    cl->options->con_modes);
	अगर (IS_ERR(monc->auth)) अणु
		err = PTR_ERR(monc->auth);
		जाओ out_monmap;
	पूर्ण
	monc->auth->want_keys =
		CEPH_ENTITY_TYPE_AUTH | CEPH_ENTITY_TYPE_MON |
		CEPH_ENTITY_TYPE_OSD | CEPH_ENTITY_TYPE_MDS;

	/* msgs */
	err = -ENOMEM;
	monc->m_subscribe_ack = ceph_msg_new(CEPH_MSG_MON_SUBSCRIBE_ACK,
				     माप(काष्ठा ceph_mon_subscribe_ack),
				     GFP_KERNEL, true);
	अगर (!monc->m_subscribe_ack)
		जाओ out_auth;

	monc->m_subscribe = ceph_msg_new(CEPH_MSG_MON_SUBSCRIBE, 128,
					 GFP_KERNEL, true);
	अगर (!monc->m_subscribe)
		जाओ out_subscribe_ack;

	monc->m_auth_reply = ceph_msg_new(CEPH_MSG_AUTH_REPLY, 4096,
					  GFP_KERNEL, true);
	अगर (!monc->m_auth_reply)
		जाओ out_subscribe;

	monc->m_auth = ceph_msg_new(CEPH_MSG_AUTH, 4096, GFP_KERNEL, true);
	monc->pending_auth = 0;
	अगर (!monc->m_auth)
		जाओ out_auth_reply;

	ceph_con_init(&monc->con, monc, &mon_con_ops,
		      &monc->client->msgr);

	monc->cur_mon = -1;
	monc->had_a_connection = false;
	monc->hunt_mult = 1;

	INIT_DELAYED_WORK(&monc->delayed_work, delayed_work);
	monc->generic_request_tree = RB_ROOT;
	monc->last_tid = 0;

	monc->fs_cluster_id = CEPH_FS_CLUSTER_ID_NONE;

	वापस 0;

out_auth_reply:
	ceph_msg_put(monc->m_auth_reply);
out_subscribe:
	ceph_msg_put(monc->m_subscribe);
out_subscribe_ack:
	ceph_msg_put(monc->m_subscribe_ack);
out_auth:
	ceph_auth_destroy(monc->auth);
out_monmap:
	kमुक्त(monc->monmap);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(ceph_monc_init);

व्योम ceph_monc_stop(काष्ठा ceph_mon_client *monc)
अणु
	करोut("stop\n");
	cancel_delayed_work_sync(&monc->delayed_work);

	mutex_lock(&monc->mutex);
	__बंद_session(monc);
	monc->cur_mon = -1;
	mutex_unlock(&monc->mutex);

	/*
	 * flush msgr queue beक्रमe we destroy ourselves to ensure that:
	 *  - any work that references our embedded con is finished.
	 *  - any osd_client or other work that may reference an authorizer
	 *    finishes beक्रमe we shut करोwn the auth subप्रणाली.
	 */
	ceph_msgr_flush();

	ceph_auth_destroy(monc->auth);

	WARN_ON(!RB_EMPTY_ROOT(&monc->generic_request_tree));

	ceph_msg_put(monc->m_auth);
	ceph_msg_put(monc->m_auth_reply);
	ceph_msg_put(monc->m_subscribe);
	ceph_msg_put(monc->m_subscribe_ack);

	kमुक्त(monc->monmap);
पूर्ण
EXPORT_SYMBOL(ceph_monc_stop);

अटल व्योम finish_hunting(काष्ठा ceph_mon_client *monc)
अणु
	अगर (monc->hunting) अणु
		करोut("%s found mon%d\n", __func__, monc->cur_mon);
		monc->hunting = false;
		monc->had_a_connection = true;
		un_backoff(monc);
		__schedule_delayed(monc);
	पूर्ण
पूर्ण

अटल व्योम finish_auth(काष्ठा ceph_mon_client *monc, पूर्णांक auth_err,
			bool was_authed)
अणु
	करोut("%s auth_err %d was_authed %d\n", __func__, auth_err, was_authed);
	WARN_ON(auth_err > 0);

	monc->pending_auth = 0;
	अगर (auth_err) अणु
		monc->client->auth_err = auth_err;
		wake_up_all(&monc->client->auth_wq);
		वापस;
	पूर्ण

	अगर (!was_authed && ceph_auth_is_authenticated(monc->auth)) अणु
		करोut("%s authenticated, starting session global_id %llu\n",
		     __func__, monc->auth->global_id);

		monc->client->msgr.inst.name.type = CEPH_ENTITY_TYPE_CLIENT;
		monc->client->msgr.inst.name.num =
					cpu_to_le64(monc->auth->global_id);

		__send_subscribe(monc);
		__resend_generic_request(monc);

		pr_info("mon%d %s session established\n", monc->cur_mon,
			ceph_pr_addr(&monc->con.peer_addr));
	पूर्ण
पूर्ण

अटल व्योम handle_auth_reply(काष्ठा ceph_mon_client *monc,
			      काष्ठा ceph_msg *msg)
अणु
	bool was_authed;
	पूर्णांक ret;

	mutex_lock(&monc->mutex);
	was_authed = ceph_auth_is_authenticated(monc->auth);
	ret = ceph_handle_auth_reply(monc->auth, msg->front.iov_base,
				     msg->front.iov_len,
				     monc->m_auth->front.iov_base,
				     monc->m_auth->front_alloc_len);
	अगर (ret > 0) अणु
		__send_prepared_auth_request(monc, ret);
	पूर्ण अन्यथा अणु
		finish_auth(monc, ret, was_authed);
		finish_hunting(monc);
	पूर्ण
	mutex_unlock(&monc->mutex);
पूर्ण

अटल पूर्णांक __validate_auth(काष्ठा ceph_mon_client *monc)
अणु
	पूर्णांक ret;

	अगर (monc->pending_auth)
		वापस 0;

	ret = ceph_build_auth(monc->auth, monc->m_auth->front.iov_base,
			      monc->m_auth->front_alloc_len);
	अगर (ret <= 0)
		वापस ret; /* either an error, or no need to authenticate */
	__send_prepared_auth_request(monc, ret);
	वापस 0;
पूर्ण

पूर्णांक ceph_monc_validate_auth(काष्ठा ceph_mon_client *monc)
अणु
	पूर्णांक ret;

	mutex_lock(&monc->mutex);
	ret = __validate_auth(monc);
	mutex_unlock(&monc->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ceph_monc_validate_auth);

अटल पूर्णांक mon_get_auth_request(काष्ठा ceph_connection *con,
				व्योम *buf, पूर्णांक *buf_len,
				व्योम **authorizer, पूर्णांक *authorizer_len)
अणु
	काष्ठा ceph_mon_client *monc = con->निजी;
	पूर्णांक ret;

	mutex_lock(&monc->mutex);
	ret = ceph_auth_get_request(monc->auth, buf, *buf_len);
	mutex_unlock(&monc->mutex);
	अगर (ret < 0)
		वापस ret;

	*buf_len = ret;
	*authorizer = शून्य;
	*authorizer_len = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक mon_handle_auth_reply_more(काष्ठा ceph_connection *con,
				      व्योम *reply, पूर्णांक reply_len,
				      व्योम *buf, पूर्णांक *buf_len,
				      व्योम **authorizer, पूर्णांक *authorizer_len)
अणु
	काष्ठा ceph_mon_client *monc = con->निजी;
	पूर्णांक ret;

	mutex_lock(&monc->mutex);
	ret = ceph_auth_handle_reply_more(monc->auth, reply, reply_len,
					  buf, *buf_len);
	mutex_unlock(&monc->mutex);
	अगर (ret < 0)
		वापस ret;

	*buf_len = ret;
	*authorizer = शून्य;
	*authorizer_len = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक mon_handle_auth_करोne(काष्ठा ceph_connection *con,
				u64 global_id, व्योम *reply, पूर्णांक reply_len,
				u8 *session_key, पूर्णांक *session_key_len,
				u8 *con_secret, पूर्णांक *con_secret_len)
अणु
	काष्ठा ceph_mon_client *monc = con->निजी;
	bool was_authed;
	पूर्णांक ret;

	mutex_lock(&monc->mutex);
	WARN_ON(!monc->hunting);
	was_authed = ceph_auth_is_authenticated(monc->auth);
	ret = ceph_auth_handle_reply_करोne(monc->auth, global_id,
					  reply, reply_len,
					  session_key, session_key_len,
					  con_secret, con_secret_len);
	finish_auth(monc, ret, was_authed);
	अगर (!ret)
		finish_hunting(monc);
	mutex_unlock(&monc->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक mon_handle_auth_bad_method(काष्ठा ceph_connection *con,
				      पूर्णांक used_proto, पूर्णांक result,
				      स्थिर पूर्णांक *allowed_protos, पूर्णांक proto_cnt,
				      स्थिर पूर्णांक *allowed_modes, पूर्णांक mode_cnt)
अणु
	काष्ठा ceph_mon_client *monc = con->निजी;
	bool was_authed;

	mutex_lock(&monc->mutex);
	WARN_ON(!monc->hunting);
	was_authed = ceph_auth_is_authenticated(monc->auth);
	ceph_auth_handle_bad_method(monc->auth, used_proto, result,
				    allowed_protos, proto_cnt,
				    allowed_modes, mode_cnt);
	finish_auth(monc, -EACCES, was_authed);
	mutex_unlock(&monc->mutex);
	वापस 0;
पूर्ण

/*
 * handle incoming message
 */
अटल व्योम mon_dispatch(काष्ठा ceph_connection *con, काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_mon_client *monc = con->निजी;
	पूर्णांक type = le16_to_cpu(msg->hdr.type);

	चयन (type) अणु
	हाल CEPH_MSG_AUTH_REPLY:
		handle_auth_reply(monc, msg);
		अवरोध;

	हाल CEPH_MSG_MON_SUBSCRIBE_ACK:
		handle_subscribe_ack(monc, msg);
		अवरोध;

	हाल CEPH_MSG_STATFS_REPLY:
		handle_statfs_reply(monc, msg);
		अवरोध;

	हाल CEPH_MSG_MON_GET_VERSION_REPLY:
		handle_get_version_reply(monc, msg);
		अवरोध;

	हाल CEPH_MSG_MON_COMMAND_ACK:
		handle_command_ack(monc, msg);
		अवरोध;

	हाल CEPH_MSG_MON_MAP:
		ceph_monc_handle_map(monc, msg);
		अवरोध;

	हाल CEPH_MSG_OSD_MAP:
		ceph_osdc_handle_map(&monc->client->osdc, msg);
		अवरोध;

	शेष:
		/* can the chained handler handle it? */
		अगर (monc->client->extra_mon_dispatch &&
		    monc->client->extra_mon_dispatch(monc->client, msg) == 0)
			अवरोध;

		pr_err("received unknown message type %d %s\n", type,
		       ceph_msg_type_name(type));
	पूर्ण
	ceph_msg_put(msg);
पूर्ण

/*
 * Allocate memory क्रम incoming message
 */
अटल काष्ठा ceph_msg *mon_alloc_msg(काष्ठा ceph_connection *con,
				      काष्ठा ceph_msg_header *hdr,
				      पूर्णांक *skip)
अणु
	काष्ठा ceph_mon_client *monc = con->निजी;
	पूर्णांक type = le16_to_cpu(hdr->type);
	पूर्णांक front_len = le32_to_cpu(hdr->front_len);
	काष्ठा ceph_msg *m = शून्य;

	*skip = 0;

	चयन (type) अणु
	हाल CEPH_MSG_MON_SUBSCRIBE_ACK:
		m = ceph_msg_get(monc->m_subscribe_ack);
		अवरोध;
	हाल CEPH_MSG_STATFS_REPLY:
	हाल CEPH_MSG_MON_COMMAND_ACK:
		वापस get_generic_reply(con, hdr, skip);
	हाल CEPH_MSG_AUTH_REPLY:
		m = ceph_msg_get(monc->m_auth_reply);
		अवरोध;
	हाल CEPH_MSG_MON_GET_VERSION_REPLY:
		अगर (le64_to_cpu(hdr->tid) != 0)
			वापस get_generic_reply(con, hdr, skip);

		/*
		 * Older OSDs करोn't set reply tid even अगर the orignal
		 * request had a non-zero tid.  Work around this weirdness
		 * by allocating a new message.
		 */
		fallthrough;
	हाल CEPH_MSG_MON_MAP:
	हाल CEPH_MSG_MDS_MAP:
	हाल CEPH_MSG_OSD_MAP:
	हाल CEPH_MSG_FS_MAP_USER:
		m = ceph_msg_new(type, front_len, GFP_NOFS, false);
		अगर (!m)
			वापस शून्य;	/* ENOMEM--वापस skip == 0 */
		अवरोध;
	पूर्ण

	अगर (!m) अणु
		pr_info("alloc_msg unknown type %d\n", type);
		*skip = 1;
	पूर्ण अन्यथा अगर (front_len > m->front_alloc_len) अणु
		pr_warn("mon_alloc_msg front %d > prealloc %d (%u#%llu)\n",
			front_len, m->front_alloc_len,
			(अचिन्हित पूर्णांक)con->peer_name.type,
			le64_to_cpu(con->peer_name.num));
		ceph_msg_put(m);
		m = ceph_msg_new(type, front_len, GFP_NOFS, false);
	पूर्ण

	वापस m;
पूर्ण

/*
 * If the monitor connection resets, pick a new monitor and resubmit
 * any pending requests.
 */
अटल व्योम mon_fault(काष्ठा ceph_connection *con)
अणु
	काष्ठा ceph_mon_client *monc = con->निजी;

	mutex_lock(&monc->mutex);
	करोut("%s mon%d\n", __func__, monc->cur_mon);
	अगर (monc->cur_mon >= 0) अणु
		अगर (!monc->hunting) अणु
			करोut("%s hunting for new mon\n", __func__);
			reखोलो_session(monc);
			__schedule_delayed(monc);
		पूर्ण अन्यथा अणु
			करोut("%s already hunting\n", __func__);
		पूर्ण
	पूर्ण
	mutex_unlock(&monc->mutex);
पूर्ण

/*
 * We can ignore refcounting on the connection काष्ठा, as all references
 * will come from the messenger workqueue, which is drained prior to
 * mon_client deकाष्ठाion.
 */
अटल काष्ठा ceph_connection *mon_get_con(काष्ठा ceph_connection *con)
अणु
	वापस con;
पूर्ण

अटल व्योम mon_put_con(काष्ठा ceph_connection *con)
अणु
पूर्ण

अटल स्थिर काष्ठा ceph_connection_operations mon_con_ops = अणु
	.get = mon_get_con,
	.put = mon_put_con,
	.alloc_msg = mon_alloc_msg,
	.dispatch = mon_dispatch,
	.fault = mon_fault,
	.get_auth_request = mon_get_auth_request,
	.handle_auth_reply_more = mon_handle_auth_reply_more,
	.handle_auth_करोne = mon_handle_auth_करोne,
	.handle_auth_bad_method = mon_handle_auth_bad_method,
पूर्ण;
