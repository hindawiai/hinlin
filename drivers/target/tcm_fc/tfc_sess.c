<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010 Cisco Systems, Inc.
 */

/* XXX TBD some includes may be extraneous */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/utsname.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/configfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/hash.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rculist.h>
#समावेश <linux/kref.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/libfc.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश "tcm_fc.h"

#घोषणा TFC_SESS_DBG(lport, fmt, args...) \
	pr_debug("host%u: rport %6.6x: " fmt,	   \
		 (lport)->host->host_no,	   \
		 (lport)->port_id, ##args )

अटल व्योम ft_sess_delete_all(काष्ठा ft_tport *);

/*
 * Lookup or allocate target local port.
 * Caller holds ft_lport_lock.
 */
अटल काष्ठा ft_tport *ft_tport_get(काष्ठा fc_lport *lport)
अणु
	काष्ठा ft_tpg *tpg;
	काष्ठा ft_tport *tport;
	पूर्णांक i;

	tport = rcu_dereference_रक्षित(lport->prov[FC_TYPE_FCP],
					  lockdep_is_held(&ft_lport_lock));
	अगर (tport && tport->tpg)
		वापस tport;

	tpg = ft_lport_find_tpg(lport);
	अगर (!tpg)
		वापस शून्य;

	अगर (tport) अणु
		tport->tpg = tpg;
		tpg->tport = tport;
		वापस tport;
	पूर्ण

	tport = kzalloc(माप(*tport), GFP_KERNEL);
	अगर (!tport)
		वापस शून्य;

	tport->lport = lport;
	tport->tpg = tpg;
	tpg->tport = tport;
	क्रम (i = 0; i < FT_SESS_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&tport->hash[i]);

	rcu_assign_poपूर्णांकer(lport->prov[FC_TYPE_FCP], tport);
	वापस tport;
पूर्ण

/*
 * Delete a target local port.
 * Caller holds ft_lport_lock.
 */
अटल व्योम ft_tport_delete(काष्ठा ft_tport *tport)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा ft_tpg *tpg;

	ft_sess_delete_all(tport);
	lport = tport->lport;
	lport->service_params &= ~FCP_SPPF_TARG_FCN;
	BUG_ON(tport != lport->prov[FC_TYPE_FCP]);
	RCU_INIT_POINTER(lport->prov[FC_TYPE_FCP], शून्य);

	tpg = tport->tpg;
	अगर (tpg) अणु
		tpg->tport = शून्य;
		tport->tpg = शून्य;
	पूर्ण
	kमुक्त_rcu(tport, rcu);
पूर्ण

/*
 * Add local port.
 * Called thru fc_lport_iterate().
 */
व्योम ft_lport_add(काष्ठा fc_lport *lport, व्योम *arg)
अणु
	mutex_lock(&ft_lport_lock);
	ft_tport_get(lport);
	lport->service_params |= FCP_SPPF_TARG_FCN;
	mutex_unlock(&ft_lport_lock);
पूर्ण

/*
 * Delete local port.
 * Called thru fc_lport_iterate().
 */
व्योम ft_lport_del(काष्ठा fc_lport *lport, व्योम *arg)
अणु
	काष्ठा ft_tport *tport;

	mutex_lock(&ft_lport_lock);
	tport = lport->prov[FC_TYPE_FCP];
	अगर (tport)
		ft_tport_delete(tport);
	mutex_unlock(&ft_lport_lock);
पूर्ण

/*
 * Notअगरication of local port change from libfc.
 * Create or delete local port and associated tport.
 */
पूर्णांक ft_lport_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *arg)
अणु
	काष्ठा fc_lport *lport = arg;

	चयन (event) अणु
	हाल FC_LPORT_EV_ADD:
		ft_lport_add(lport, शून्य);
		अवरोध;
	हाल FC_LPORT_EV_DEL:
		ft_lport_del(lport, शून्य);
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

/*
 * Hash function क्रम FC_IDs.
 */
अटल u32 ft_sess_hash(u32 port_id)
अणु
	वापस hash_32(port_id, FT_SESS_HASH_BITS);
पूर्ण

/*
 * Find session in local port.
 * Sessions and hash lists are RCU-रक्षित.
 * A reference is taken which must be eventually मुक्तd.
 */
अटल काष्ठा ft_sess *ft_sess_get(काष्ठा fc_lport *lport, u32 port_id)
अणु
	काष्ठा ft_tport *tport;
	काष्ठा hlist_head *head;
	काष्ठा ft_sess *sess;
	अक्षर *reason = "no session created";

	rcu_पढ़ो_lock();
	tport = rcu_dereference(lport->prov[FC_TYPE_FCP]);
	अगर (!tport) अणु
		reason = "not an FCP port";
		जाओ out;
	पूर्ण

	head = &tport->hash[ft_sess_hash(port_id)];
	hlist_क्रम_each_entry_rcu(sess, head, hash) अणु
		अगर (sess->port_id == port_id) अणु
			kref_get(&sess->kref);
			rcu_पढ़ो_unlock();
			TFC_SESS_DBG(lport, "port_id %x found %p\n",
				     port_id, sess);
			वापस sess;
		पूर्ण
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	TFC_SESS_DBG(lport, "port_id %x not found, %s\n",
		     port_id, reason);
	वापस शून्य;
पूर्ण

अटल पूर्णांक ft_sess_alloc_cb(काष्ठा se_portal_group *se_tpg,
			    काष्ठा se_session *se_sess, व्योम *p)
अणु
	काष्ठा ft_sess *sess = p;
	काष्ठा ft_tport *tport = sess->tport;
	काष्ठा hlist_head *head = &tport->hash[ft_sess_hash(sess->port_id)];

	TFC_SESS_DBG(tport->lport, "port_id %x sess %p\n", sess->port_id, sess);
	hlist_add_head_rcu(&sess->hash, head);
	tport->sess_count++;

	वापस 0;
पूर्ण

/*
 * Allocate session and enter it in the hash क्रम the local port.
 * Caller holds ft_lport_lock.
 */
अटल काष्ठा ft_sess *ft_sess_create(काष्ठा ft_tport *tport, u32 port_id,
				      काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा se_portal_group *se_tpg = &tport->tpg->se_tpg;
	काष्ठा ft_sess *sess;
	काष्ठा hlist_head *head;
	अचिन्हित अक्षर initiatorname[TRANSPORT_IQN_LEN];

	ft_क्रमmat_wwn(&initiatorname[0], TRANSPORT_IQN_LEN, rdata->ids.port_name);

	head = &tport->hash[ft_sess_hash(port_id)];
	hlist_क्रम_each_entry_rcu(sess, head, hash)
		अगर (sess->port_id == port_id)
			वापस sess;

	sess = kzalloc(माप(*sess), GFP_KERNEL);
	अगर (!sess)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&sess->kref); /* ref क्रम table entry */
	sess->tport = tport;
	sess->port_id = port_id;

	sess->se_sess = target_setup_session(se_tpg, TCM_FC_DEFAULT_TAGS,
					     माप(काष्ठा ft_cmd),
					     TARGET_PROT_NORMAL, &initiatorname[0],
					     sess, ft_sess_alloc_cb);
	अगर (IS_ERR(sess->se_sess)) अणु
		पूर्णांक rc = PTR_ERR(sess->se_sess);
		kमुक्त(sess);
		sess = ERR_PTR(rc);
	पूर्ण
	वापस sess;
पूर्ण

/*
 * Unhash the session.
 * Caller holds ft_lport_lock.
 */
अटल व्योम ft_sess_unhash(काष्ठा ft_sess *sess)
अणु
	काष्ठा ft_tport *tport = sess->tport;

	hlist_del_rcu(&sess->hash);
	BUG_ON(!tport->sess_count);
	tport->sess_count--;
	sess->port_id = -1;
	sess->params = 0;
पूर्ण

/*
 * Delete session from hash.
 * Caller holds ft_lport_lock.
 */
अटल काष्ठा ft_sess *ft_sess_delete(काष्ठा ft_tport *tport, u32 port_id)
अणु
	काष्ठा hlist_head *head;
	काष्ठा ft_sess *sess;

	head = &tport->hash[ft_sess_hash(port_id)];
	hlist_क्रम_each_entry_rcu(sess, head, hash) अणु
		अगर (sess->port_id == port_id) अणु
			ft_sess_unhash(sess);
			वापस sess;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम ft_बंद_sess(काष्ठा ft_sess *sess)
अणु
	target_stop_session(sess->se_sess);
	target_रुको_क्रम_sess_cmds(sess->se_sess);
	ft_sess_put(sess);
पूर्ण

/*
 * Delete all sessions from tport.
 * Caller holds ft_lport_lock.
 */
अटल व्योम ft_sess_delete_all(काष्ठा ft_tport *tport)
अणु
	काष्ठा hlist_head *head;
	काष्ठा ft_sess *sess;

	क्रम (head = tport->hash;
	     head < &tport->hash[FT_SESS_HASH_SIZE]; head++) अणु
		hlist_क्रम_each_entry_rcu(sess, head, hash) अणु
			ft_sess_unhash(sess);
			ft_बंद_sess(sess);	/* release from table */
		पूर्ण
	पूर्ण
पूर्ण

/*
 * TCM ops क्रम sessions.
 */

/*
 * Remove session and send PRLO.
 * This is called when the ACL is being deleted or queue depth is changing.
 */
व्योम ft_sess_बंद(काष्ठा se_session *se_sess)
अणु
	काष्ठा ft_sess *sess = se_sess->fabric_sess_ptr;
	u32 port_id;

	mutex_lock(&ft_lport_lock);
	port_id = sess->port_id;
	अगर (port_id == -1) अणु
		mutex_unlock(&ft_lport_lock);
		वापस;
	पूर्ण
	TFC_SESS_DBG(sess->tport->lport, "port_id %x close session\n", port_id);
	ft_sess_unhash(sess);
	mutex_unlock(&ft_lport_lock);
	ft_बंद_sess(sess);
	/* XXX Send LOGO or PRLO */
	synchronize_rcu();		/* let transport deरेजिस्टर happen */
पूर्ण

u32 ft_sess_get_index(काष्ठा se_session *se_sess)
अणु
	काष्ठा ft_sess *sess = se_sess->fabric_sess_ptr;

	वापस sess->port_id;	/* XXX TBD probably not what is needed */
पूर्ण

u32 ft_sess_get_port_name(काष्ठा se_session *se_sess,
			  अचिन्हित अक्षर *buf, u32 len)
अणु
	काष्ठा ft_sess *sess = se_sess->fabric_sess_ptr;

	वापस ft_क्रमmat_wwn(buf, len, sess->port_name);
पूर्ण

/*
 * libfc ops involving sessions.
 */

अटल पूर्णांक ft_prli_locked(काष्ठा fc_rport_priv *rdata, u32 spp_len,
			  स्थिर काष्ठा fc_els_spp *rspp, काष्ठा fc_els_spp *spp)
अणु
	काष्ठा ft_tport *tport;
	काष्ठा ft_sess *sess;
	u32 fcp_parm;

	tport = ft_tport_get(rdata->local_port);
	अगर (!tport)
		जाओ not_target;	/* not a target क्रम this local port */

	अगर (!rspp)
		जाओ fill;

	अगर (rspp->spp_flags & (FC_SPP_OPA_VAL | FC_SPP_RPA_VAL))
		वापस FC_SPP_RESP_NO_PA;

	/*
	 * If both target and initiator bits are off, the SPP is invalid.
	 */
	fcp_parm = ntohl(rspp->spp_params);
	अगर (!(fcp_parm & (FCP_SPPF_INIT_FCN | FCP_SPPF_TARG_FCN)))
		वापस FC_SPP_RESP_INVL;

	/*
	 * Create session (image pair) only अगर requested by
	 * EST_IMG_PAIR flag and अगर the requestor is an initiator.
	 */
	अगर (rspp->spp_flags & FC_SPP_EST_IMG_PAIR) अणु
		spp->spp_flags |= FC_SPP_EST_IMG_PAIR;
		अगर (!(fcp_parm & FCP_SPPF_INIT_FCN))
			वापस FC_SPP_RESP_CONF;
		sess = ft_sess_create(tport, rdata->ids.port_id, rdata);
		अगर (IS_ERR(sess)) अणु
			अगर (PTR_ERR(sess) == -EACCES) अणु
				spp->spp_flags &= ~FC_SPP_EST_IMG_PAIR;
				वापस FC_SPP_RESP_CONF;
			पूर्ण अन्यथा
				वापस FC_SPP_RESP_RES;
		पूर्ण
		अगर (!sess->params)
			rdata->prli_count++;
		sess->params = fcp_parm;
		sess->port_name = rdata->ids.port_name;
		sess->max_frame = rdata->maxframe_size;

		/* XXX TBD - clearing actions.  unit attn, see 4.10 */
	पूर्ण

	/*
	 * OR in our service parameters with other provider (initiator), अगर any.
	 */
fill:
	fcp_parm = ntohl(spp->spp_params);
	fcp_parm &= ~FCP_SPPF_RETRY;
	spp->spp_params = htonl(fcp_parm | FCP_SPPF_TARG_FCN);
	वापस FC_SPP_RESP_ACK;

not_target:
	fcp_parm = ntohl(spp->spp_params);
	fcp_parm &= ~FCP_SPPF_TARG_FCN;
	spp->spp_params = htonl(fcp_parm);
	वापस 0;
पूर्ण

/**
 * ft_prli() - Handle incoming or outgoing PRLI क्रम the FCP target
 * @rdata: remote port निजी
 * @spp_len: service parameter page length
 * @rspp: received service parameter page (शून्य क्रम outgoing PRLI)
 * @spp: response service parameter page
 *
 * Returns spp response code.
 */
अटल पूर्णांक ft_prli(काष्ठा fc_rport_priv *rdata, u32 spp_len,
		   स्थिर काष्ठा fc_els_spp *rspp, काष्ठा fc_els_spp *spp)
अणु
	पूर्णांक ret;

	mutex_lock(&ft_lport_lock);
	ret = ft_prli_locked(rdata, spp_len, rspp, spp);
	mutex_unlock(&ft_lport_lock);
	TFC_SESS_DBG(rdata->local_port, "port_id %x flags %x ret %x\n",
		     rdata->ids.port_id, rspp ? rspp->spp_flags : 0, ret);
	वापस ret;
पूर्ण

अटल व्योम ft_sess_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा ft_sess *sess = container_of(kref, काष्ठा ft_sess, kref);

	target_हटाओ_session(sess->se_sess);
	kमुक्त_rcu(sess, rcu);
पूर्ण

व्योम ft_sess_put(काष्ठा ft_sess *sess)
अणु
	पूर्णांक sess_held = kref_पढ़ो(&sess->kref);

	BUG_ON(!sess_held);
	kref_put(&sess->kref, ft_sess_मुक्त);
पूर्ण

अटल व्योम ft_prlo(काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा ft_sess *sess;
	काष्ठा ft_tport *tport;

	mutex_lock(&ft_lport_lock);
	tport = rcu_dereference_रक्षित(rdata->local_port->prov[FC_TYPE_FCP],
					  lockdep_is_held(&ft_lport_lock));

	अगर (!tport) अणु
		mutex_unlock(&ft_lport_lock);
		वापस;
	पूर्ण
	sess = ft_sess_delete(tport, rdata->ids.port_id);
	अगर (!sess) अणु
		mutex_unlock(&ft_lport_lock);
		वापस;
	पूर्ण
	mutex_unlock(&ft_lport_lock);
	ft_बंद_sess(sess);		/* release from table */
	rdata->prli_count--;
	/* XXX TBD - clearing actions.  unit attn, see 4.10 */
पूर्ण

/*
 * Handle incoming FCP request.
 * Caller has verअगरied that the frame is type FCP.
 */
अटल व्योम ft_recv(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा ft_sess *sess;
	u32 sid = fc_frame_sid(fp);

	TFC_SESS_DBG(lport, "recv sid %x\n", sid);

	sess = ft_sess_get(lport, sid);
	अगर (!sess) अणु
		TFC_SESS_DBG(lport, "sid %x sess lookup failed\n", sid);
		/* TBD XXX - अगर FCP_CMND, send PRLO */
		fc_frame_मुक्त(fp);
		वापस;
	पूर्ण
	ft_recv_req(sess, fp);	/* must करो ft_sess_put() */
पूर्ण

/*
 * Provider ops क्रम libfc.
 */
काष्ठा fc4_prov ft_prov = अणु
	.prli = ft_prli,
	.prlo = ft_prlo,
	.recv = ft_recv,
	.module = THIS_MODULE,
पूर्ण;
