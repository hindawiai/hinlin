<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2007 - 2008 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

/*
 * RPORT GENERAL INFO
 *
 * This file contains all processing regarding fc_rports. It contains the
 * rport state machine and करोes all rport पूर्णांकeraction with the transport class.
 * There should be no other places in libfc that पूर्णांकeract directly with the
 * transport class in regards to adding and deleting rports.
 *
 * fc_rport's represent N_Port's within the fabric.
 */

/*
 * RPORT LOCKING
 *
 * The rport should never hold the rport mutex and then attempt to acquire
 * either the lport or disc mutexes. The rport's mutex is considered lesser
 * than both the lport's mutex and the disc mutex. Refer to fc_lport.c क्रम
 * more comments on the hierarchy.
 *
 * The locking strategy is similar to the lport's strategy. The lock protects
 * the rport's states and is held and released by the entry poपूर्णांकs to the rport
 * block. All _enter_* functions correspond to rport states and expect the rport
 * mutex to be locked beक्रमe calling them. This means that rports only handle
 * one request or response at a समय, since they're not critical क्रम the I/O
 * path this potential over-use of the mutex is acceptable.
 */

/*
 * RPORT REFERENCE COUNTING
 *
 * A rport reference should be taken when:
 * - an rport is allocated
 * - a workqueue item is scheduled
 * - an ELS request is send
 * The reference should be dropped when:
 * - the workqueue function has finished
 * - the ELS response is handled
 * - an rport is हटाओd
 */

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/export.h>
#समावेश <linux/rculist.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/libfc.h>

#समावेश "fc_encode.h"
#समावेश "fc_libfc.h"

अटल काष्ठा workqueue_काष्ठा *rport_event_queue;

अटल व्योम fc_rport_enter_flogi(काष्ठा fc_rport_priv *);
अटल व्योम fc_rport_enter_plogi(काष्ठा fc_rport_priv *);
अटल व्योम fc_rport_enter_prli(काष्ठा fc_rport_priv *);
अटल व्योम fc_rport_enter_rtv(काष्ठा fc_rport_priv *);
अटल व्योम fc_rport_enter_पढ़ोy(काष्ठा fc_rport_priv *);
अटल व्योम fc_rport_enter_logo(काष्ठा fc_rport_priv *);
अटल व्योम fc_rport_enter_adisc(काष्ठा fc_rport_priv *);

अटल व्योम fc_rport_recv_plogi_req(काष्ठा fc_lport *, काष्ठा fc_frame *);
अटल व्योम fc_rport_recv_prli_req(काष्ठा fc_rport_priv *, काष्ठा fc_frame *);
अटल व्योम fc_rport_recv_prlo_req(काष्ठा fc_rport_priv *, काष्ठा fc_frame *);
अटल व्योम fc_rport_recv_logo_req(काष्ठा fc_lport *, काष्ठा fc_frame *);
अटल व्योम fc_rport_समयout(काष्ठा work_काष्ठा *);
अटल व्योम fc_rport_error(काष्ठा fc_rport_priv *, पूर्णांक);
अटल व्योम fc_rport_error_retry(काष्ठा fc_rport_priv *, पूर्णांक);
अटल व्योम fc_rport_work(काष्ठा work_काष्ठा *);

अटल स्थिर अक्षर *fc_rport_state_names[] = अणु
	[RPORT_ST_INIT] = "Init",
	[RPORT_ST_FLOGI] = "FLOGI",
	[RPORT_ST_PLOGI_WAIT] = "PLOGI_WAIT",
	[RPORT_ST_PLOGI] = "PLOGI",
	[RPORT_ST_PRLI] = "PRLI",
	[RPORT_ST_RTV] = "RTV",
	[RPORT_ST_READY] = "Ready",
	[RPORT_ST_ADISC] = "ADISC",
	[RPORT_ST_DELETE] = "Delete",
पूर्ण;

/**
 * fc_rport_lookup() - Lookup a remote port by port_id
 * @lport:   The local port to lookup the remote port on
 * @port_id: The remote port ID to look up
 *
 * The reference count of the fc_rport_priv काष्ठाure is
 * increased by one.
 */
काष्ठा fc_rport_priv *fc_rport_lookup(स्थिर काष्ठा fc_lport *lport,
				      u32 port_id)
अणु
	काष्ठा fc_rport_priv *rdata = शून्य, *पंचांगp_rdata;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(पंचांगp_rdata, &lport->disc.rports, peers)
		अगर (पंचांगp_rdata->ids.port_id == port_id &&
		    kref_get_unless_zero(&पंचांगp_rdata->kref)) अणु
			rdata = पंचांगp_rdata;
			अवरोध;
		पूर्ण
	rcu_पढ़ो_unlock();
	वापस rdata;
पूर्ण
EXPORT_SYMBOL(fc_rport_lookup);

/**
 * fc_rport_create() - Create a new remote port
 * @lport: The local port this remote port will be associated with
 * @port_id:   The identअगरiers क्रम the new remote port
 *
 * The remote port will start in the INIT state.
 */
काष्ठा fc_rport_priv *fc_rport_create(काष्ठा fc_lport *lport, u32 port_id)
अणु
	काष्ठा fc_rport_priv *rdata;
	माप_प्रकार rport_priv_size = माप(*rdata);

	lockdep_निश्चित_held(&lport->disc.disc_mutex);

	rdata = fc_rport_lookup(lport, port_id);
	अगर (rdata) अणु
		kref_put(&rdata->kref, fc_rport_destroy);
		वापस rdata;
	पूर्ण

	अगर (lport->rport_priv_size > 0)
		rport_priv_size = lport->rport_priv_size;
	rdata = kzalloc(rport_priv_size, GFP_KERNEL);
	अगर (!rdata)
		वापस शून्य;

	rdata->ids.node_name = -1;
	rdata->ids.port_name = -1;
	rdata->ids.port_id = port_id;
	rdata->ids.roles = FC_RPORT_ROLE_UNKNOWN;

	kref_init(&rdata->kref);
	mutex_init(&rdata->rp_mutex);
	rdata->local_port = lport;
	rdata->rp_state = RPORT_ST_INIT;
	rdata->event = RPORT_EV_NONE;
	rdata->flags = FC_RP_FLAGS_REC_SUPPORTED;
	rdata->e_d_tov = lport->e_d_tov;
	rdata->r_a_tov = lport->r_a_tov;
	rdata->maxframe_size = FC_MIN_MAX_PAYLOAD;
	INIT_DELAYED_WORK(&rdata->retry_work, fc_rport_समयout);
	INIT_WORK(&rdata->event_work, fc_rport_work);
	अगर (port_id != FC_FID_सूची_SERV) अणु
		rdata->lld_event_callback = lport->tt.rport_event_callback;
		list_add_rcu(&rdata->peers, &lport->disc.rports);
	पूर्ण
	वापस rdata;
पूर्ण
EXPORT_SYMBOL(fc_rport_create);

/**
 * fc_rport_destroy() - Free a remote port after last reference is released
 * @kref: The remote port's kref
 */
व्योम fc_rport_destroy(काष्ठा kref *kref)
अणु
	काष्ठा fc_rport_priv *rdata;

	rdata = container_of(kref, काष्ठा fc_rport_priv, kref);
	kमुक्त_rcu(rdata, rcu);
पूर्ण
EXPORT_SYMBOL(fc_rport_destroy);

/**
 * fc_rport_state() - Return a string identअगरying the remote port's state
 * @rdata: The remote port
 */
अटल स्थिर अक्षर *fc_rport_state(काष्ठा fc_rport_priv *rdata)
अणु
	स्थिर अक्षर *cp;

	cp = fc_rport_state_names[rdata->rp_state];
	अगर (!cp)
		cp = "Unknown";
	वापस cp;
पूर्ण

/**
 * fc_set_rport_loss_पंचांगo() - Set the remote port loss समयout
 * @rport:   The remote port that माला_लो a new समयout value
 * @समयout: The new समयout value (in seconds)
 */
व्योम fc_set_rport_loss_पंचांगo(काष्ठा fc_rport *rport, u32 समयout)
अणु
	अगर (समयout)
		rport->dev_loss_पंचांगo = समयout;
	अन्यथा
		rport->dev_loss_पंचांगo = 1;
पूर्ण
EXPORT_SYMBOL(fc_set_rport_loss_पंचांगo);

/**
 * fc_plogi_get_maxframe() - Get the maximum payload from the common service
 *			     parameters in a FLOGI frame
 * @flp:    The FLOGI or PLOGI payload
 * @maxval: The maximum frame size upper limit; this may be less than what
 *	    is in the service parameters
 */
अटल अचिन्हित पूर्णांक fc_plogi_get_maxframe(काष्ठा fc_els_flogi *flp,
					  अचिन्हित पूर्णांक maxval)
अणु
	अचिन्हित पूर्णांक mfs;

	/*
	 * Get max payload from the common service parameters and the
	 * class 3 receive data field size.
	 */
	mfs = ntohs(flp->fl_csp.sp_bb_data) & FC_SP_BB_DATA_MASK;
	अगर (mfs >= FC_SP_MIN_MAX_PAYLOAD && mfs < maxval)
		maxval = mfs;
	mfs = ntohs(flp->fl_cssp[3 - 1].cp_rdfs);
	अगर (mfs >= FC_SP_MIN_MAX_PAYLOAD && mfs < maxval)
		maxval = mfs;
	वापस maxval;
पूर्ण

/**
 * fc_rport_state_enter() - Change the state of a remote port
 * @rdata: The remote port whose state should change
 * @new:   The new state
 */
अटल व्योम fc_rport_state_enter(काष्ठा fc_rport_priv *rdata,
				 क्रमागत fc_rport_state new)
अणु
	lockdep_निश्चित_held(&rdata->rp_mutex);

	अगर (rdata->rp_state != new)
		rdata->retries = 0;
	rdata->rp_state = new;
पूर्ण

/**
 * fc_rport_work() - Handler क्रम remote port events in the rport_event_queue
 * @work: Handle to the remote port being dequeued
 *
 * Reference counting: drops kref on वापस
 */
अटल व्योम fc_rport_work(काष्ठा work_काष्ठा *work)
अणु
	u32 port_id;
	काष्ठा fc_rport_priv *rdata =
		container_of(work, काष्ठा fc_rport_priv, event_work);
	काष्ठा fc_rport_libfc_priv *rpriv;
	क्रमागत fc_rport_event event;
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_rport_operations *rport_ops;
	काष्ठा fc_rport_identअगरiers ids;
	काष्ठा fc_rport *rport;
	काष्ठा fc4_prov *prov;
	u8 type;

	mutex_lock(&rdata->rp_mutex);
	event = rdata->event;
	rport_ops = rdata->ops;
	rport = rdata->rport;

	FC_RPORT_DBG(rdata, "work event %u\n", event);

	चयन (event) अणु
	हाल RPORT_EV_READY:
		ids = rdata->ids;
		rdata->event = RPORT_EV_NONE;
		rdata->major_retries = 0;
		kref_get(&rdata->kref);
		mutex_unlock(&rdata->rp_mutex);

		अगर (!rport) अणु
			FC_RPORT_DBG(rdata, "No rport!\n");
			rport = fc_remote_port_add(lport->host, 0, &ids);
		पूर्ण
		अगर (!rport) अणु
			FC_RPORT_DBG(rdata, "Failed to add the rport\n");
			fc_rport_logoff(rdata);
			kref_put(&rdata->kref, fc_rport_destroy);
			वापस;
		पूर्ण
		mutex_lock(&rdata->rp_mutex);
		अगर (rdata->rport)
			FC_RPORT_DBG(rdata, "rport already allocated\n");
		rdata->rport = rport;
		rport->maxframe_size = rdata->maxframe_size;
		rport->supported_classes = rdata->supported_classes;

		rpriv = rport->dd_data;
		rpriv->local_port = lport;
		rpriv->rp_state = rdata->rp_state;
		rpriv->flags = rdata->flags;
		rpriv->e_d_tov = rdata->e_d_tov;
		rpriv->r_a_tov = rdata->r_a_tov;
		mutex_unlock(&rdata->rp_mutex);

		अगर (rport_ops && rport_ops->event_callback) अणु
			FC_RPORT_DBG(rdata, "callback ev %d\n", event);
			rport_ops->event_callback(lport, rdata, event);
		पूर्ण
		अगर (rdata->lld_event_callback) अणु
			FC_RPORT_DBG(rdata, "lld callback ev %d\n", event);
			rdata->lld_event_callback(lport, rdata, event);
		पूर्ण
		kref_put(&rdata->kref, fc_rport_destroy);
		अवरोध;

	हाल RPORT_EV_FAILED:
	हाल RPORT_EV_LOGO:
	हाल RPORT_EV_STOP:
		अगर (rdata->prli_count) अणु
			mutex_lock(&fc_prov_mutex);
			क्रम (type = 1; type < FC_FC4_PROV_SIZE; type++) अणु
				prov = fc_passive_prov[type];
				अगर (prov && prov->prlo)
					prov->prlo(rdata);
			पूर्ण
			mutex_unlock(&fc_prov_mutex);
		पूर्ण
		port_id = rdata->ids.port_id;
		mutex_unlock(&rdata->rp_mutex);

		अगर (rport_ops && rport_ops->event_callback) अणु
			FC_RPORT_DBG(rdata, "callback ev %d\n", event);
			rport_ops->event_callback(lport, rdata, event);
		पूर्ण
		अगर (rdata->lld_event_callback) अणु
			FC_RPORT_DBG(rdata, "lld callback ev %d\n", event);
			rdata->lld_event_callback(lport, rdata, event);
		पूर्ण
		अगर (cancel_delayed_work_sync(&rdata->retry_work))
			kref_put(&rdata->kref, fc_rport_destroy);

		/*
		 * Reset any outstanding exchanges beक्रमe मुक्तing rport.
		 */
		lport->tt.exch_mgr_reset(lport, 0, port_id);
		lport->tt.exch_mgr_reset(lport, port_id, 0);

		अगर (rport) अणु
			rpriv = rport->dd_data;
			rpriv->rp_state = RPORT_ST_DELETE;
			mutex_lock(&rdata->rp_mutex);
			rdata->rport = शून्य;
			mutex_unlock(&rdata->rp_mutex);
			fc_remote_port_delete(rport);
		पूर्ण

		mutex_lock(&rdata->rp_mutex);
		अगर (rdata->rp_state == RPORT_ST_DELETE) अणु
			अगर (port_id == FC_FID_सूची_SERV) अणु
				rdata->event = RPORT_EV_NONE;
				mutex_unlock(&rdata->rp_mutex);
				kref_put(&rdata->kref, fc_rport_destroy);
			पूर्ण अन्यथा अगर ((rdata->flags & FC_RP_STARTED) &&
				   rdata->major_retries <
				   lport->max_rport_retry_count) अणु
				rdata->major_retries++;
				rdata->event = RPORT_EV_NONE;
				FC_RPORT_DBG(rdata, "work restart\n");
				fc_rport_enter_flogi(rdata);
				mutex_unlock(&rdata->rp_mutex);
			पूर्ण अन्यथा अणु
				mutex_unlock(&rdata->rp_mutex);
				FC_RPORT_DBG(rdata, "work delete\n");
				mutex_lock(&lport->disc.disc_mutex);
				list_del_rcu(&rdata->peers);
				mutex_unlock(&lport->disc.disc_mutex);
				kref_put(&rdata->kref, fc_rport_destroy);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Re-खोलो क्रम events.  Reissue READY event अगर पढ़ोy.
			 */
			rdata->event = RPORT_EV_NONE;
			अगर (rdata->rp_state == RPORT_ST_READY) अणु
				FC_RPORT_DBG(rdata, "work reopen\n");
				fc_rport_enter_पढ़ोy(rdata);
			पूर्ण
			mutex_unlock(&rdata->rp_mutex);
		पूर्ण
		अवरोध;

	शेष:
		mutex_unlock(&rdata->rp_mutex);
		अवरोध;
	पूर्ण
	kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

/**
 * fc_rport_login() - Start the remote port login state machine
 * @rdata: The remote port to be logged in to
 *
 * Initiates the RP state machine. It is called from the LP module.
 * This function will issue the following commands to the N_Port
 * identअगरied by the FC ID provided.
 *
 * - PLOGI
 * - PRLI
 * - RTV
 *
 * Locking Note: Called without the rport lock held. This
 * function will hold the rport lock, call an _enter_*
 * function and then unlock the rport.
 *
 * This indicates the पूर्णांकent to be logged पूर्णांकo the remote port.
 * If it appears we are alपढ़ोy logged in, ADISC is used to verअगरy
 * the setup.
 */
पूर्णांक fc_rport_login(काष्ठा fc_rport_priv *rdata)
अणु
	mutex_lock(&rdata->rp_mutex);

	अगर (rdata->flags & FC_RP_STARTED) अणु
		FC_RPORT_DBG(rdata, "port already started\n");
		mutex_unlock(&rdata->rp_mutex);
		वापस 0;
	पूर्ण

	rdata->flags |= FC_RP_STARTED;
	चयन (rdata->rp_state) अणु
	हाल RPORT_ST_READY:
		FC_RPORT_DBG(rdata, "ADISC port\n");
		fc_rport_enter_adisc(rdata);
		अवरोध;
	हाल RPORT_ST_DELETE:
		FC_RPORT_DBG(rdata, "Restart deleted port\n");
		अवरोध;
	हाल RPORT_ST_INIT:
		FC_RPORT_DBG(rdata, "Login to port\n");
		fc_rport_enter_flogi(rdata);
		अवरोध;
	शेष:
		FC_RPORT_DBG(rdata, "Login in progress, state %s\n",
			     fc_rport_state(rdata));
		अवरोध;
	पूर्ण
	mutex_unlock(&rdata->rp_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_rport_login);

/**
 * fc_rport_enter_delete() - Schedule a remote port to be deleted
 * @rdata: The remote port to be deleted
 * @event: The event to report as the reason क्रम deletion
 *
 * Allow state change पूर्णांकo DELETE only once.
 *
 * Call queue_work only अगर there's no event alपढ़ोy pending.
 * Set the new event so that the old pending event will not occur.
 * Since we have the mutex, even अगर fc_rport_work() is alपढ़ोy started,
 * it'll see the new event.
 *
 * Reference counting: करोes not modअगरy kref
 */
अटल व्योम fc_rport_enter_delete(काष्ठा fc_rport_priv *rdata,
				  क्रमागत fc_rport_event event)
अणु
	lockdep_निश्चित_held(&rdata->rp_mutex);

	अगर (rdata->rp_state == RPORT_ST_DELETE)
		वापस;

	FC_RPORT_DBG(rdata, "Delete port\n");

	fc_rport_state_enter(rdata, RPORT_ST_DELETE);

	अगर (rdata->event == RPORT_EV_NONE) अणु
		kref_get(&rdata->kref);
		अगर (!queue_work(rport_event_queue, &rdata->event_work))
			kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण

	rdata->event = event;
पूर्ण

/**
 * fc_rport_logoff() - Logoff and हटाओ a remote port
 * @rdata: The remote port to be logged off of
 *
 * Locking Note: Called without the rport lock held. This
 * function will hold the rport lock, call an _enter_*
 * function and then unlock the rport.
 */
पूर्णांक fc_rport_logoff(काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	u32 port_id = rdata->ids.port_id;

	mutex_lock(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Remove port\n");

	rdata->flags &= ~FC_RP_STARTED;
	अगर (rdata->rp_state == RPORT_ST_DELETE) अणु
		FC_RPORT_DBG(rdata, "Port in Delete state, not removing\n");
		जाओ out;
	पूर्ण
	/*
	 * FC-LS states:
	 * To explicitly Logout, the initiating Nx_Port shall terminate
	 * other खोलो Sequences that it initiated with the destination
	 * Nx_Port prior to perक्रमming Logout.
	 */
	lport->tt.exch_mgr_reset(lport, 0, port_id);
	lport->tt.exch_mgr_reset(lport, port_id, 0);

	fc_rport_enter_logo(rdata);

	/*
	 * Change the state to Delete so that we discard
	 * the response.
	 */
	fc_rport_enter_delete(rdata, RPORT_EV_STOP);
out:
	mutex_unlock(&rdata->rp_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_rport_logoff);

/**
 * fc_rport_enter_पढ़ोy() - Transition to the RPORT_ST_READY state
 * @rdata: The remote port that is पढ़ोy
 *
 * Reference counting: schedules workqueue, करोes not modअगरy kref
 */
अटल व्योम fc_rport_enter_पढ़ोy(काष्ठा fc_rport_priv *rdata)
अणु
	lockdep_निश्चित_held(&rdata->rp_mutex);

	fc_rport_state_enter(rdata, RPORT_ST_READY);

	FC_RPORT_DBG(rdata, "Port is Ready\n");

	kref_get(&rdata->kref);
	अगर (rdata->event == RPORT_EV_NONE &&
	    !queue_work(rport_event_queue, &rdata->event_work))
		kref_put(&rdata->kref, fc_rport_destroy);

	rdata->event = RPORT_EV_READY;
पूर्ण

/**
 * fc_rport_समयout() - Handler क्रम the retry_work समयr
 * @work: Handle to the remote port that has समयd out
 *
 * Locking Note: Called without the rport lock held. This
 * function will hold the rport lock, call an _enter_*
 * function and then unlock the rport.
 *
 * Reference counting: Drops kref on वापस.
 */
अटल व्योम fc_rport_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_rport_priv *rdata =
		container_of(work, काष्ठा fc_rport_priv, retry_work.work);

	mutex_lock(&rdata->rp_mutex);
	FC_RPORT_DBG(rdata, "Port timeout, state %s\n", fc_rport_state(rdata));

	चयन (rdata->rp_state) अणु
	हाल RPORT_ST_FLOGI:
		fc_rport_enter_flogi(rdata);
		अवरोध;
	हाल RPORT_ST_PLOGI:
		fc_rport_enter_plogi(rdata);
		अवरोध;
	हाल RPORT_ST_PRLI:
		fc_rport_enter_prli(rdata);
		अवरोध;
	हाल RPORT_ST_RTV:
		fc_rport_enter_rtv(rdata);
		अवरोध;
	हाल RPORT_ST_ADISC:
		fc_rport_enter_adisc(rdata);
		अवरोध;
	हाल RPORT_ST_PLOGI_WAIT:
	हाल RPORT_ST_READY:
	हाल RPORT_ST_INIT:
	हाल RPORT_ST_DELETE:
		अवरोध;
	पूर्ण

	mutex_unlock(&rdata->rp_mutex);
	kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

/**
 * fc_rport_error() - Error handler, called once retries have been exhausted
 * @rdata: The remote port the error is happened on
 * @err:   The error code
 *
 * Reference counting: करोes not modअगरy kref
 */
अटल व्योम fc_rport_error(काष्ठा fc_rport_priv *rdata, पूर्णांक err)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Error %d in state %s, retries %d\n",
		     -err, fc_rport_state(rdata), rdata->retries);

	चयन (rdata->rp_state) अणु
	हाल RPORT_ST_FLOGI:
		rdata->flags &= ~FC_RP_STARTED;
		fc_rport_enter_delete(rdata, RPORT_EV_FAILED);
		अवरोध;
	हाल RPORT_ST_PLOGI:
		अगर (lport->poपूर्णांक_to_multipoपूर्णांक) अणु
			rdata->flags &= ~FC_RP_STARTED;
			fc_rport_enter_delete(rdata, RPORT_EV_FAILED);
		पूर्ण अन्यथा
			fc_rport_enter_logo(rdata);
		अवरोध;
	हाल RPORT_ST_RTV:
		fc_rport_enter_पढ़ोy(rdata);
		अवरोध;
	हाल RPORT_ST_PRLI:
		fc_rport_enter_plogi(rdata);
		अवरोध;
	हाल RPORT_ST_ADISC:
		fc_rport_enter_logo(rdata);
		अवरोध;
	हाल RPORT_ST_PLOGI_WAIT:
	हाल RPORT_ST_DELETE:
	हाल RPORT_ST_READY:
	हाल RPORT_ST_INIT:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * fc_rport_error_retry() - Handler क्रम remote port state retries
 * @rdata: The remote port whose state is to be retried
 * @err:   The error code
 *
 * If the error was an exchange समयout retry immediately,
 * otherwise रुको क्रम E_D_TOV.
 *
 * Reference counting: increments kref when scheduling retry_work
 */
अटल व्योम fc_rport_error_retry(काष्ठा fc_rport_priv *rdata, पूर्णांक err)
अणु
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(rdata->e_d_tov);

	lockdep_निश्चित_held(&rdata->rp_mutex);

	/* make sure this isn't an FC_EX_CLOSED error, never retry those */
	अगर (err == -FC_EX_CLOSED)
		जाओ out;

	अगर (rdata->retries < rdata->local_port->max_rport_retry_count) अणु
		FC_RPORT_DBG(rdata, "Error %d in state %s, retrying\n",
			     err, fc_rport_state(rdata));
		rdata->retries++;
		/* no additional delay on exchange समयouts */
		अगर (err == -FC_EX_TIMEOUT)
			delay = 0;
		kref_get(&rdata->kref);
		अगर (!schedule_delayed_work(&rdata->retry_work, delay))
			kref_put(&rdata->kref, fc_rport_destroy);
		वापस;
	पूर्ण

out:
	fc_rport_error(rdata, err);
पूर्ण

/**
 * fc_rport_login_complete() - Handle parameters and completion of p-mp login.
 * @rdata:  The remote port which we logged पूर्णांकo or which logged पूर्णांकo us.
 * @fp:     The FLOGI or PLOGI request or response frame
 *
 * Returns non-zero error अगर a problem is detected with the frame.
 * Does not मुक्त the frame.
 *
 * This is only used in poपूर्णांक-to-multipoपूर्णांक mode क्रम FIP currently.
 */
अटल पूर्णांक fc_rport_login_complete(काष्ठा fc_rport_priv *rdata,
				   काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_els_flogi *flogi;
	अचिन्हित पूर्णांक e_d_tov;
	u16 csp_flags;

	flogi = fc_frame_payload_get(fp, माप(*flogi));
	अगर (!flogi)
		वापस -EINVAL;

	csp_flags = ntohs(flogi->fl_csp.sp_features);

	अगर (fc_frame_payload_op(fp) == ELS_FLOGI) अणु
		अगर (csp_flags & FC_SP_FT_FPORT) अणु
			FC_RPORT_DBG(rdata, "Fabric bit set in FLOGI\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु

		/*
		 * E_D_TOV is not valid on an incoming FLOGI request.
		 */
		e_d_tov = ntohl(flogi->fl_csp.sp_e_d_tov);
		अगर (csp_flags & FC_SP_FT_EDTR)
			e_d_tov /= 1000000;
		अगर (e_d_tov > rdata->e_d_tov)
			rdata->e_d_tov = e_d_tov;
	पूर्ण
	rdata->maxframe_size = fc_plogi_get_maxframe(flogi, lport->mfs);
	वापस 0;
पूर्ण

/**
 * fc_rport_flogi_resp() - Handle response to FLOGI request क्रम p-mp mode
 * @sp:	    The sequence that the FLOGI was on
 * @fp:	    The FLOGI response frame
 * @rp_arg: The remote port that received the FLOGI response
 */
अटल व्योम fc_rport_flogi_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
				व्योम *rp_arg)
अणु
	काष्ठा fc_rport_priv *rdata = rp_arg;
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_els_flogi *flogi;
	अचिन्हित पूर्णांक r_a_tov;
	u8 opcode;
	पूर्णांक err = 0;

	FC_RPORT_DBG(rdata, "Received a FLOGI %s\n",
		     IS_ERR(fp) ? "error" : fc_els_resp_type(fp));

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		जाओ put;

	mutex_lock(&rdata->rp_mutex);

	अगर (rdata->rp_state != RPORT_ST_FLOGI) अणु
		FC_RPORT_DBG(rdata, "Received a FLOGI response, but in state "
			     "%s\n", fc_rport_state(rdata));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_rport_error(rdata, PTR_ERR(fp));
		जाओ err;
	पूर्ण
	opcode = fc_frame_payload_op(fp);
	अगर (opcode == ELS_LS_RJT) अणु
		काष्ठा fc_els_ls_rjt *rjt;

		rjt = fc_frame_payload_get(fp, माप(*rjt));
		FC_RPORT_DBG(rdata, "FLOGI ELS rejected, reason %x expl %x\n",
			     rjt->er_reason, rjt->er_explan);
		err = -FC_EX_ELS_RJT;
		जाओ bad;
	पूर्ण अन्यथा अगर (opcode != ELS_LS_ACC) अणु
		FC_RPORT_DBG(rdata, "FLOGI ELS invalid opcode %x\n", opcode);
		err = -FC_EX_ELS_RJT;
		जाओ bad;
	पूर्ण
	अगर (fc_rport_login_complete(rdata, fp)) अणु
		FC_RPORT_DBG(rdata, "FLOGI failed, no login\n");
		err = -FC_EX_INV_LOGIN;
		जाओ bad;
	पूर्ण

	flogi = fc_frame_payload_get(fp, माप(*flogi));
	अगर (!flogi) अणु
		err = -FC_EX_ALLOC_ERR;
		जाओ bad;
	पूर्ण
	r_a_tov = ntohl(flogi->fl_csp.sp_r_a_tov);
	अगर (r_a_tov > rdata->r_a_tov)
		rdata->r_a_tov = r_a_tov;

	अगर (rdata->ids.port_name < lport->wwpn)
		fc_rport_enter_plogi(rdata);
	अन्यथा
		fc_rport_state_enter(rdata, RPORT_ST_PLOGI_WAIT);
out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
put:
	kref_put(&rdata->kref, fc_rport_destroy);
	वापस;
bad:
	FC_RPORT_DBG(rdata, "Bad FLOGI response\n");
	fc_rport_error_retry(rdata, err);
	जाओ out;
पूर्ण

/**
 * fc_rport_enter_flogi() - Send a FLOGI request to the remote port क्रम p-mp
 * @rdata: The remote port to send a FLOGI to
 *
 * Reference counting: increments kref when sending ELS
 */
अटल व्योम fc_rport_enter_flogi(काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_frame *fp;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	अगर (!lport->poपूर्णांक_to_multipoपूर्णांक)
		वापस fc_rport_enter_plogi(rdata);

	FC_RPORT_DBG(rdata, "Entered FLOGI state from %s state\n",
		     fc_rport_state(rdata));

	fc_rport_state_enter(rdata, RPORT_ST_FLOGI);

	fp = fc_frame_alloc(lport, माप(काष्ठा fc_els_flogi));
	अगर (!fp)
		वापस fc_rport_error_retry(rdata, -FC_EX_ALLOC_ERR);

	kref_get(&rdata->kref);
	अगर (!lport->tt.elsct_send(lport, rdata->ids.port_id, fp, ELS_FLOGI,
				  fc_rport_flogi_resp, rdata,
				  2 * lport->r_a_tov)) अणु
		fc_rport_error_retry(rdata, -FC_EX_XMIT_ERR);
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण
पूर्ण

/**
 * fc_rport_recv_flogi_req() - Handle Fabric Login (FLOGI) request in p-mp mode
 * @lport: The local port that received the PLOGI request
 * @rx_fp: The PLOGI request frame
 *
 * Reference counting: drops kref on वापस
 */
अटल व्योम fc_rport_recv_flogi_req(काष्ठा fc_lport *lport,
				    काष्ठा fc_frame *rx_fp)
अणु
	काष्ठा fc_els_flogi *flp;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा fc_frame *fp = rx_fp;
	काष्ठा fc_seq_els_data rjt_data;
	u32 sid;

	sid = fc_frame_sid(fp);

	FC_RPORT_ID_DBG(lport, sid, "Received FLOGI request\n");

	अगर (!lport->poपूर्णांक_to_multipoपूर्णांक) अणु
		rjt_data.reason = ELS_RJT_UNSUP;
		rjt_data.explan = ELS_EXPL_NONE;
		जाओ reject;
	पूर्ण

	flp = fc_frame_payload_get(fp, माप(*flp));
	अगर (!flp) अणु
		rjt_data.reason = ELS_RJT_LOGIC;
		rjt_data.explan = ELS_EXPL_INV_LEN;
		जाओ reject;
	पूर्ण

	rdata = fc_rport_lookup(lport, sid);
	अगर (!rdata) अणु
		rjt_data.reason = ELS_RJT_FIP;
		rjt_data.explan = ELS_EXPL_NOT_NEIGHBOR;
		जाओ reject;
	पूर्ण
	mutex_lock(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Received FLOGI in %s state\n",
		     fc_rport_state(rdata));

	चयन (rdata->rp_state) अणु
	हाल RPORT_ST_INIT:
		/*
		 * If received the FLOGI request on RPORT which is INIT state
		 * (means not transition to FLOGI either fc_rport समयout
		 * function didn;t trigger or this end hasn;t received
		 * beacon yet from other end. In that हाल only, allow RPORT
		 * state machine to जारी, otherwise fall through which
		 * causes the code to send reject response.
		 * NOTE; Not checking क्रम FIP->state such as VNMP_UP or
		 * VNMP_CLAIM because अगर FIP state is not one of those,
		 * RPORT wouldn;t have created and 'rport_lookup' would have
		 * failed anyway in that हाल.
		 */
		अवरोध;
	हाल RPORT_ST_DELETE:
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_FIP;
		rjt_data.explan = ELS_EXPL_NOT_NEIGHBOR;
		जाओ reject_put;
	हाल RPORT_ST_FLOGI:
	हाल RPORT_ST_PLOGI_WAIT:
	हाल RPORT_ST_PLOGI:
		अवरोध;
	हाल RPORT_ST_PRLI:
	हाल RPORT_ST_RTV:
	हाल RPORT_ST_READY:
	हाल RPORT_ST_ADISC:
		/*
		 * Set the remote port to be deleted and to then restart.
		 * This queues work to be sure exchanges are reset.
		 */
		fc_rport_enter_delete(rdata, RPORT_EV_LOGO);
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_BUSY;
		rjt_data.explan = ELS_EXPL_NONE;
		जाओ reject_put;
	पूर्ण
	अगर (fc_rport_login_complete(rdata, fp)) अणु
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_LOGIC;
		rjt_data.explan = ELS_EXPL_NONE;
		जाओ reject_put;
	पूर्ण

	fp = fc_frame_alloc(lport, माप(*flp));
	अगर (!fp)
		जाओ out;

	fc_flogi_fill(lport, fp);
	flp = fc_frame_payload_get(fp, माप(*flp));
	flp->fl_cmd = ELS_LS_ACC;

	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);

	/*
	 * Do not proceed with the state machine अगर our
	 * FLOGI has crossed with an FLOGI from the
	 * remote port; रुको क्रम the FLOGI response instead.
	 */
	अगर (rdata->rp_state != RPORT_ST_FLOGI) अणु
		अगर (rdata->ids.port_name < lport->wwpn)
			fc_rport_enter_plogi(rdata);
		अन्यथा
			fc_rport_state_enter(rdata, RPORT_ST_PLOGI_WAIT);
	पूर्ण
out:
	mutex_unlock(&rdata->rp_mutex);
	kref_put(&rdata->kref, fc_rport_destroy);
	fc_frame_मुक्त(rx_fp);
	वापस;

reject_put:
	kref_put(&rdata->kref, fc_rport_destroy);
reject:
	fc_seq_els_rsp_send(rx_fp, ELS_LS_RJT, &rjt_data);
	fc_frame_मुक्त(rx_fp);
पूर्ण

/**
 * fc_rport_plogi_resp() - Handler क्रम ELS PLOGI responses
 * @sp:	       The sequence the PLOGI is on
 * @fp:	       The PLOGI response frame
 * @rdata_arg: The remote port that sent the PLOGI response
 *
 * Locking Note: This function will be called without the rport lock
 * held, but it will lock, call an _enter_* function or fc_rport_error
 * and then unlock the rport.
 */
अटल व्योम fc_rport_plogi_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
				व्योम *rdata_arg)
अणु
	काष्ठा fc_rport_priv *rdata = rdata_arg;
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_els_flogi *plp = शून्य;
	u16 csp_seq;
	u16 cssp_seq;
	u8 op;

	FC_RPORT_DBG(rdata, "Received a PLOGI %s\n", fc_els_resp_type(fp));

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		जाओ put;

	mutex_lock(&rdata->rp_mutex);

	अगर (rdata->rp_state != RPORT_ST_PLOGI) अणु
		FC_RPORT_DBG(rdata, "Received a PLOGI response, but in state "
			     "%s\n", fc_rport_state(rdata));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_rport_error_retry(rdata, PTR_ERR(fp));
		जाओ err;
	पूर्ण

	op = fc_frame_payload_op(fp);
	अगर (op == ELS_LS_ACC &&
	    (plp = fc_frame_payload_get(fp, माप(*plp))) != शून्य) अणु
		rdata->ids.port_name = get_unaligned_be64(&plp->fl_wwpn);
		rdata->ids.node_name = get_unaligned_be64(&plp->fl_wwnn);

		/* save plogi response sp_features क्रम further reference */
		rdata->sp_features = ntohs(plp->fl_csp.sp_features);

		अगर (lport->poपूर्णांक_to_multipoपूर्णांक)
			fc_rport_login_complete(rdata, fp);
		csp_seq = ntohs(plp->fl_csp.sp_tot_seq);
		cssp_seq = ntohs(plp->fl_cssp[3 - 1].cp_con_seq);
		अगर (cssp_seq < csp_seq)
			csp_seq = cssp_seq;
		rdata->max_seq = csp_seq;
		rdata->maxframe_size = fc_plogi_get_maxframe(plp, lport->mfs);
		fc_rport_enter_prli(rdata);
	पूर्ण अन्यथा अणु
		काष्ठा fc_els_ls_rjt *rjt;

		rjt = fc_frame_payload_get(fp, माप(*rjt));
		अगर (!rjt)
			FC_RPORT_DBG(rdata, "PLOGI bad response\n");
		अन्यथा
			FC_RPORT_DBG(rdata, "PLOGI ELS rejected, reason %x expl %x\n",
				     rjt->er_reason, rjt->er_explan);
		fc_rport_error_retry(rdata, -FC_EX_ELS_RJT);
	पूर्ण
out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
put:
	kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

अटल bool
fc_rport_compatible_roles(काष्ठा fc_lport *lport, काष्ठा fc_rport_priv *rdata)
अणु
	अगर (rdata->ids.roles == FC_PORT_ROLE_UNKNOWN)
		वापस true;
	अगर ((rdata->ids.roles & FC_PORT_ROLE_FCP_TARGET) &&
	    (lport->service_params & FCP_SPPF_INIT_FCN))
		वापस true;
	अगर ((rdata->ids.roles & FC_PORT_ROLE_FCP_INITIATOR) &&
	    (lport->service_params & FCP_SPPF_TARG_FCN))
		वापस true;
	वापस false;
पूर्ण

/**
 * fc_rport_enter_plogi() - Send Port Login (PLOGI) request
 * @rdata: The remote port to send a PLOGI to
 *
 * Reference counting: increments kref when sending ELS
 */
अटल व्योम fc_rport_enter_plogi(काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_frame *fp;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	अगर (!fc_rport_compatible_roles(lport, rdata)) अणु
		FC_RPORT_DBG(rdata, "PLOGI suppressed for incompatible role\n");
		fc_rport_state_enter(rdata, RPORT_ST_PLOGI_WAIT);
		वापस;
	पूर्ण

	FC_RPORT_DBG(rdata, "Port entered PLOGI state from %s state\n",
		     fc_rport_state(rdata));

	fc_rport_state_enter(rdata, RPORT_ST_PLOGI);

	rdata->maxframe_size = FC_MIN_MAX_PAYLOAD;
	fp = fc_frame_alloc(lport, माप(काष्ठा fc_els_flogi));
	अगर (!fp) अणु
		FC_RPORT_DBG(rdata, "%s frame alloc failed\n", __func__);
		fc_rport_error_retry(rdata, -FC_EX_ALLOC_ERR);
		वापस;
	पूर्ण
	rdata->e_d_tov = lport->e_d_tov;

	kref_get(&rdata->kref);
	अगर (!lport->tt.elsct_send(lport, rdata->ids.port_id, fp, ELS_PLOGI,
				  fc_rport_plogi_resp, rdata,
				  2 * lport->r_a_tov)) अणु
		fc_rport_error_retry(rdata, -FC_EX_XMIT_ERR);
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण
पूर्ण

/**
 * fc_rport_prli_resp() - Process Login (PRLI) response handler
 * @sp:	       The sequence the PRLI response was on
 * @fp:	       The PRLI response frame
 * @rdata_arg: The remote port that sent the PRLI response
 *
 * Locking Note: This function will be called without the rport lock
 * held, but it will lock, call an _enter_* function or fc_rport_error
 * and then unlock the rport.
 */
अटल व्योम fc_rport_prli_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			       व्योम *rdata_arg)
अणु
	काष्ठा fc_rport_priv *rdata = rdata_arg;
	काष्ठा अणु
		काष्ठा fc_els_prli prli;
		काष्ठा fc_els_spp spp;
	पूर्ण *pp;
	काष्ठा fc_els_spp temp_spp;
	काष्ठा fc_els_ls_rjt *rjt;
	काष्ठा fc4_prov *prov;
	u32 roles = FC_RPORT_ROLE_UNKNOWN;
	u32 fcp_parm = 0;
	u8 op;
	क्रमागत fc_els_spp_resp resp_code;

	FC_RPORT_DBG(rdata, "Received a PRLI %s\n", fc_els_resp_type(fp));

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		जाओ put;

	mutex_lock(&rdata->rp_mutex);

	अगर (rdata->rp_state != RPORT_ST_PRLI) अणु
		FC_RPORT_DBG(rdata, "Received a PRLI response, but in state "
			     "%s\n", fc_rport_state(rdata));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_rport_error_retry(rdata, PTR_ERR(fp));
		जाओ err;
	पूर्ण

	/* reinitialize remote port roles */
	rdata->ids.roles = FC_RPORT_ROLE_UNKNOWN;

	op = fc_frame_payload_op(fp);
	अगर (op == ELS_LS_ACC) अणु
		pp = fc_frame_payload_get(fp, माप(*pp));
		अगर (!pp) अणु
			fc_rport_error_retry(rdata, -FC_EX_SEQ_ERR);
			जाओ out;
		पूर्ण

		resp_code = (pp->spp.spp_flags & FC_SPP_RESP_MASK);
		FC_RPORT_DBG(rdata, "PRLI spp_flags = 0x%x spp_type 0x%x\n",
			     pp->spp.spp_flags, pp->spp.spp_type);
		rdata->spp_type = pp->spp.spp_type;
		अगर (resp_code != FC_SPP_RESP_ACK) अणु
			अगर (resp_code == FC_SPP_RESP_CONF)
				fc_rport_error(rdata, -FC_EX_SEQ_ERR);
			अन्यथा
				fc_rport_error_retry(rdata, -FC_EX_SEQ_ERR);
			जाओ out;
		पूर्ण
		अगर (pp->prli.prli_spp_len < माप(pp->spp)) अणु
			fc_rport_error_retry(rdata, -FC_EX_SEQ_ERR);
			जाओ out;
		पूर्ण

		fcp_parm = ntohl(pp->spp.spp_params);
		अगर (fcp_parm & FCP_SPPF_RETRY)
			rdata->flags |= FC_RP_FLAGS_RETRY;
		अगर (fcp_parm & FCP_SPPF_CONF_COMPL)
			rdata->flags |= FC_RP_FLAGS_CONF_REQ;

		/*
		 * Call prli provider अगर we should act as a target
		 */
		prov = fc_passive_prov[rdata->spp_type];
		अगर (prov) अणु
			स_रखो(&temp_spp, 0, माप(temp_spp));
			prov->prli(rdata, pp->prli.prli_spp_len,
				   &pp->spp, &temp_spp);
		पूर्ण
		/*
		 * Check अगर the image pair could be established
		 */
		अगर (rdata->spp_type != FC_TYPE_FCP ||
		    !(pp->spp.spp_flags & FC_SPP_EST_IMG_PAIR)) अणु
			/*
			 * Nope; we can't use this port as a target.
			 */
			fcp_parm &= ~FCP_SPPF_TARG_FCN;
		पूर्ण
		rdata->supported_classes = FC_COS_CLASS3;
		अगर (fcp_parm & FCP_SPPF_INIT_FCN)
			roles |= FC_RPORT_ROLE_FCP_INITIATOR;
		अगर (fcp_parm & FCP_SPPF_TARG_FCN)
			roles |= FC_RPORT_ROLE_FCP_TARGET;

		rdata->ids.roles = roles;
		fc_rport_enter_rtv(rdata);

	पूर्ण अन्यथा अणु
		rjt = fc_frame_payload_get(fp, माप(*rjt));
		अगर (!rjt)
			FC_RPORT_DBG(rdata, "PRLI bad response\n");
		अन्यथा अणु
			FC_RPORT_DBG(rdata, "PRLI ELS rejected, reason %x expl %x\n",
				     rjt->er_reason, rjt->er_explan);
			अगर (rjt->er_reason == ELS_RJT_UNAB &&
			    rjt->er_explan == ELS_EXPL_PLOGI_REQD) अणु
				fc_rport_enter_plogi(rdata);
				जाओ out;
			पूर्ण
		पूर्ण
		fc_rport_error_retry(rdata, FC_EX_ELS_RJT);
	पूर्ण

out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
put:
	kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

/**
 * fc_rport_enter_prli() - Send Process Login (PRLI) request
 * @rdata: The remote port to send the PRLI request to
 *
 * Reference counting: increments kref when sending ELS
 */
अटल व्योम fc_rport_enter_prli(काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा अणु
		काष्ठा fc_els_prli prli;
		काष्ठा fc_els_spp spp;
	पूर्ण *pp;
	काष्ठा fc_frame *fp;
	काष्ठा fc4_prov *prov;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	/*
	 * If the rport is one of the well known addresses
	 * we skip PRLI and RTV and go straight to READY.
	 */
	अगर (rdata->ids.port_id >= FC_FID_DOM_MGR) अणु
		fc_rport_enter_पढ़ोy(rdata);
		वापस;
	पूर्ण

	/*
	 * And अगर the local port करोes not support the initiator function
	 * there's no need to send a PRLI, either.
	 */
	अगर (!(lport->service_params & FCP_SPPF_INIT_FCN)) अणु
		    fc_rport_enter_पढ़ोy(rdata);
		    वापस;
	पूर्ण

	FC_RPORT_DBG(rdata, "Port entered PRLI state from %s state\n",
		     fc_rport_state(rdata));

	fc_rport_state_enter(rdata, RPORT_ST_PRLI);

	fp = fc_frame_alloc(lport, माप(*pp));
	अगर (!fp) अणु
		fc_rport_error_retry(rdata, -FC_EX_ALLOC_ERR);
		वापस;
	पूर्ण

	fc_prli_fill(lport, fp);

	prov = fc_passive_prov[FC_TYPE_FCP];
	अगर (prov) अणु
		pp = fc_frame_payload_get(fp, माप(*pp));
		prov->prli(rdata, माप(pp->spp), शून्य, &pp->spp);
	पूर्ण

	fc_fill_fc_hdr(fp, FC_RCTL_ELS_REQ, rdata->ids.port_id,
		       fc_host_port_id(lport->host), FC_TYPE_ELS,
		       FC_FC_FIRST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT, 0);

	kref_get(&rdata->kref);
	अगर (!fc_exch_seq_send(lport, fp, fc_rport_prli_resp,
			      शून्य, rdata, 2 * lport->r_a_tov)) अणु
		fc_rport_error_retry(rdata, -FC_EX_XMIT_ERR);
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण
पूर्ण

/**
 * fc_rport_rtv_resp() - Handler क्रम Request Timeout Value (RTV) responses
 * @sp:	       The sequence the RTV was on
 * @fp:	       The RTV response frame
 * @rdata_arg: The remote port that sent the RTV response
 *
 * Many tarमाला_लो करोn't seem to support this.
 *
 * Locking Note: This function will be called without the rport lock
 * held, but it will lock, call an _enter_* function or fc_rport_error
 * and then unlock the rport.
 */
अटल व्योम fc_rport_rtv_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			      व्योम *rdata_arg)
अणु
	काष्ठा fc_rport_priv *rdata = rdata_arg;
	u8 op;

	FC_RPORT_DBG(rdata, "Received a RTV %s\n", fc_els_resp_type(fp));

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		जाओ put;

	mutex_lock(&rdata->rp_mutex);

	अगर (rdata->rp_state != RPORT_ST_RTV) अणु
		FC_RPORT_DBG(rdata, "Received a RTV response, but in state "
			     "%s\n", fc_rport_state(rdata));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_rport_error(rdata, PTR_ERR(fp));
		जाओ err;
	पूर्ण

	op = fc_frame_payload_op(fp);
	अगर (op == ELS_LS_ACC) अणु
		काष्ठा fc_els_rtv_acc *rtv;
		u32 toq;
		u32 tov;

		rtv = fc_frame_payload_get(fp, माप(*rtv));
		अगर (rtv) अणु
			toq = ntohl(rtv->rtv_toq);
			tov = ntohl(rtv->rtv_r_a_tov);
			अगर (tov == 0)
				tov = 1;
			अगर (tov > rdata->r_a_tov)
				rdata->r_a_tov = tov;
			tov = ntohl(rtv->rtv_e_d_tov);
			अगर (toq & FC_ELS_RTV_EDRES)
				tov /= 1000000;
			अगर (tov == 0)
				tov = 1;
			अगर (tov > rdata->e_d_tov)
				rdata->e_d_tov = tov;
		पूर्ण
	पूर्ण

	fc_rport_enter_पढ़ोy(rdata);

out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
put:
	kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

/**
 * fc_rport_enter_rtv() - Send Request Timeout Value (RTV) request
 * @rdata: The remote port to send the RTV request to
 *
 * Reference counting: increments kref when sending ELS
 */
अटल व्योम fc_rport_enter_rtv(काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_lport *lport = rdata->local_port;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Port entered RTV state from %s state\n",
		     fc_rport_state(rdata));

	fc_rport_state_enter(rdata, RPORT_ST_RTV);

	fp = fc_frame_alloc(lport, माप(काष्ठा fc_els_rtv));
	अगर (!fp) अणु
		fc_rport_error_retry(rdata, -FC_EX_ALLOC_ERR);
		वापस;
	पूर्ण

	kref_get(&rdata->kref);
	अगर (!lport->tt.elsct_send(lport, rdata->ids.port_id, fp, ELS_RTV,
				  fc_rport_rtv_resp, rdata,
				  2 * lport->r_a_tov)) अणु
		fc_rport_error_retry(rdata, -FC_EX_XMIT_ERR);
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण
पूर्ण

/**
 * fc_rport_recv_rtv_req() - Handler क्रम Read Timeout Value (RTV) requests
 * @rdata: The remote port that sent the RTV request
 * @in_fp: The RTV request frame
 */
अटल व्योम fc_rport_recv_rtv_req(काष्ठा fc_rport_priv *rdata,
				  काष्ठा fc_frame *in_fp)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_frame *fp;
	काष्ठा fc_els_rtv_acc *rtv;
	काष्ठा fc_seq_els_data rjt_data;

	lockdep_निश्चित_held(&rdata->rp_mutex);
	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_RPORT_DBG(rdata, "Received RTV request\n");

	fp = fc_frame_alloc(lport, माप(*rtv));
	अगर (!fp) अणु
		rjt_data.reason = ELS_RJT_UNAB;
		rjt_data.explan = ELS_EXPL_INSUF_RES;
		fc_seq_els_rsp_send(in_fp, ELS_LS_RJT, &rjt_data);
		जाओ drop;
	पूर्ण
	rtv = fc_frame_payload_get(fp, माप(*rtv));
	rtv->rtv_cmd = ELS_LS_ACC;
	rtv->rtv_r_a_tov = htonl(lport->r_a_tov);
	rtv->rtv_e_d_tov = htonl(lport->e_d_tov);
	rtv->rtv_toq = 0;
	fc_fill_reply_hdr(fp, in_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
drop:
	fc_frame_मुक्त(in_fp);
पूर्ण

/**
 * fc_rport_logo_resp() - Handler क्रम logout (LOGO) responses
 * @sp:	       The sequence the LOGO was on
 * @fp:	       The LOGO response frame
 * @rdata_arg: The remote port
 */
अटल व्योम fc_rport_logo_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			       व्योम *rdata_arg)
अणु
	काष्ठा fc_rport_priv *rdata = rdata_arg;
	काष्ठा fc_lport *lport = rdata->local_port;

	FC_RPORT_ID_DBG(lport, fc_seq_exch(sp)->did,
			"Received a LOGO %s\n", fc_els_resp_type(fp));
	अगर (!IS_ERR(fp))
		fc_frame_मुक्त(fp);
	kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

/**
 * fc_rport_enter_logo() - Send a logout (LOGO) request
 * @rdata: The remote port to send the LOGO request to
 *
 * Reference counting: increments kref when sending ELS
 */
अटल व्योम fc_rport_enter_logo(काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_frame *fp;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Port sending LOGO from %s state\n",
		     fc_rport_state(rdata));

	fp = fc_frame_alloc(lport, माप(काष्ठा fc_els_logo));
	अगर (!fp)
		वापस;
	kref_get(&rdata->kref);
	अगर (!lport->tt.elsct_send(lport, rdata->ids.port_id, fp, ELS_LOGO,
				  fc_rport_logo_resp, rdata, 0))
		kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

/**
 * fc_rport_adisc_resp() - Handler क्रम Address Discovery (ADISC) responses
 * @sp:	       The sequence the ADISC response was on
 * @fp:	       The ADISC response frame
 * @rdata_arg: The remote port that sent the ADISC response
 *
 * Locking Note: This function will be called without the rport lock
 * held, but it will lock, call an _enter_* function or fc_rport_error
 * and then unlock the rport.
 */
अटल व्योम fc_rport_adisc_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
				व्योम *rdata_arg)
अणु
	काष्ठा fc_rport_priv *rdata = rdata_arg;
	काष्ठा fc_els_adisc *adisc;
	u8 op;

	FC_RPORT_DBG(rdata, "Received a ADISC response\n");

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		जाओ put;

	mutex_lock(&rdata->rp_mutex);

	अगर (rdata->rp_state != RPORT_ST_ADISC) अणु
		FC_RPORT_DBG(rdata, "Received a ADISC resp but in state %s\n",
			     fc_rport_state(rdata));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_rport_error(rdata, PTR_ERR(fp));
		जाओ err;
	पूर्ण

	/*
	 * If address verअगरication failed.  Consider us logged out of the rport.
	 * Since the rport is still in discovery, we want to be
	 * logged in, so go to PLOGI state.  Otherwise, go back to READY.
	 */
	op = fc_frame_payload_op(fp);
	adisc = fc_frame_payload_get(fp, माप(*adisc));
	अगर (op != ELS_LS_ACC || !adisc ||
	    ntoh24(adisc->adisc_port_id) != rdata->ids.port_id ||
	    get_unaligned_be64(&adisc->adisc_wwpn) != rdata->ids.port_name ||
	    get_unaligned_be64(&adisc->adisc_wwnn) != rdata->ids.node_name) अणु
		FC_RPORT_DBG(rdata, "ADISC error or mismatch\n");
		fc_rport_enter_flogi(rdata);
	पूर्ण अन्यथा अणु
		FC_RPORT_DBG(rdata, "ADISC OK\n");
		fc_rport_enter_पढ़ोy(rdata);
	पूर्ण
out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
put:
	kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

/**
 * fc_rport_enter_adisc() - Send Address Discover (ADISC) request
 * @rdata: The remote port to send the ADISC request to
 *
 * Reference counting: increments kref when sending ELS
 */
अटल व्योम fc_rport_enter_adisc(काष्ठा fc_rport_priv *rdata)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_frame *fp;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "sending ADISC from %s state\n",
		     fc_rport_state(rdata));

	fc_rport_state_enter(rdata, RPORT_ST_ADISC);

	fp = fc_frame_alloc(lport, माप(काष्ठा fc_els_adisc));
	अगर (!fp) अणु
		fc_rport_error_retry(rdata, -FC_EX_ALLOC_ERR);
		वापस;
	पूर्ण
	kref_get(&rdata->kref);
	अगर (!lport->tt.elsct_send(lport, rdata->ids.port_id, fp, ELS_ADISC,
				  fc_rport_adisc_resp, rdata,
				  2 * lport->r_a_tov)) अणु
		fc_rport_error_retry(rdata, -FC_EX_XMIT_ERR);
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण
पूर्ण

/**
 * fc_rport_recv_adisc_req() - Handler क्रम Address Discovery (ADISC) requests
 * @rdata: The remote port that sent the ADISC request
 * @in_fp: The ADISC request frame
 */
अटल व्योम fc_rport_recv_adisc_req(काष्ठा fc_rport_priv *rdata,
				    काष्ठा fc_frame *in_fp)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_frame *fp;
	काष्ठा fc_els_adisc *adisc;
	काष्ठा fc_seq_els_data rjt_data;

	lockdep_निश्चित_held(&rdata->rp_mutex);
	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_RPORT_DBG(rdata, "Received ADISC request\n");

	adisc = fc_frame_payload_get(in_fp, माप(*adisc));
	अगर (!adisc) अणु
		rjt_data.reason = ELS_RJT_PROT;
		rjt_data.explan = ELS_EXPL_INV_LEN;
		fc_seq_els_rsp_send(in_fp, ELS_LS_RJT, &rjt_data);
		जाओ drop;
	पूर्ण

	fp = fc_frame_alloc(lport, माप(*adisc));
	अगर (!fp)
		जाओ drop;
	fc_adisc_fill(lport, fp);
	adisc = fc_frame_payload_get(fp, माप(*adisc));
	adisc->adisc_cmd = ELS_LS_ACC;
	fc_fill_reply_hdr(fp, in_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
drop:
	fc_frame_मुक्त(in_fp);
पूर्ण

/**
 * fc_rport_recv_rls_req() - Handle received Read Link Status request
 * @rdata: The remote port that sent the RLS request
 * @rx_fp: The PRLI request frame
 */
अटल व्योम fc_rport_recv_rls_req(काष्ठा fc_rport_priv *rdata,
				  काष्ठा fc_frame *rx_fp)

अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_frame *fp;
	काष्ठा fc_els_rls *rls;
	काष्ठा fc_els_rls_resp *rsp;
	काष्ठा fc_els_lesb *lesb;
	काष्ठा fc_seq_els_data rjt_data;
	काष्ठा fc_host_statistics *hst;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Received RLS request while in state %s\n",
		     fc_rport_state(rdata));

	rls = fc_frame_payload_get(rx_fp, माप(*rls));
	अगर (!rls) अणु
		rjt_data.reason = ELS_RJT_PROT;
		rjt_data.explan = ELS_EXPL_INV_LEN;
		जाओ out_rjt;
	पूर्ण

	fp = fc_frame_alloc(lport, माप(*rsp));
	अगर (!fp) अणु
		rjt_data.reason = ELS_RJT_UNAB;
		rjt_data.explan = ELS_EXPL_INSUF_RES;
		जाओ out_rjt;
	पूर्ण

	rsp = fc_frame_payload_get(fp, माप(*rsp));
	स_रखो(rsp, 0, माप(*rsp));
	rsp->rls_cmd = ELS_LS_ACC;
	lesb = &rsp->rls_lesb;
	अगर (lport->tt.get_lesb) अणु
		/* get LESB from LLD अगर it supports it */
		lport->tt.get_lesb(lport, lesb);
	पूर्ण अन्यथा अणु
		fc_get_host_stats(lport->host);
		hst = &lport->host_stats;
		lesb->lesb_link_fail = htonl(hst->link_failure_count);
		lesb->lesb_sync_loss = htonl(hst->loss_of_sync_count);
		lesb->lesb_sig_loss = htonl(hst->loss_of_संकेत_count);
		lesb->lesb_prim_err = htonl(hst->prim_seq_protocol_err_count);
		lesb->lesb_inv_word = htonl(hst->invalid_tx_word_count);
		lesb->lesb_inv_crc = htonl(hst->invalid_crc_count);
	पूर्ण

	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
	जाओ out;

out_rjt:
	fc_seq_els_rsp_send(rx_fp, ELS_LS_RJT, &rjt_data);
out:
	fc_frame_मुक्त(rx_fp);
पूर्ण

/**
 * fc_rport_recv_els_req() - Handler क्रम validated ELS requests
 * @lport: The local port that received the ELS request
 * @fp:	   The ELS request frame
 *
 * Handle incoming ELS requests that require port login.
 * The ELS opcode has alपढ़ोy been validated by the caller.
 *
 * Reference counting: करोes not modअगरy kref
 */
अटल व्योम fc_rport_recv_els_req(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_rport_priv *rdata;
	काष्ठा fc_seq_els_data els_data;

	lockdep_निश्चित_held(&lport->lp_mutex);

	rdata = fc_rport_lookup(lport, fc_frame_sid(fp));
	अगर (!rdata) अणु
		FC_RPORT_ID_DBG(lport, fc_frame_sid(fp),
				"Received ELS 0x%02x from non-logged-in port\n",
				fc_frame_payload_op(fp));
		जाओ reject;
	पूर्ण

	mutex_lock(&rdata->rp_mutex);

	चयन (rdata->rp_state) अणु
	हाल RPORT_ST_PRLI:
	हाल RPORT_ST_RTV:
	हाल RPORT_ST_READY:
	हाल RPORT_ST_ADISC:
		अवरोध;
	हाल RPORT_ST_PLOGI:
		अगर (fc_frame_payload_op(fp) == ELS_PRLI) अणु
			FC_RPORT_DBG(rdata, "Reject ELS PRLI "
				     "while in state %s\n",
				     fc_rport_state(rdata));
			mutex_unlock(&rdata->rp_mutex);
			kref_put(&rdata->kref, fc_rport_destroy);
			जाओ busy;
		पूर्ण
		fallthrough;
	शेष:
		FC_RPORT_DBG(rdata,
			     "Reject ELS 0x%02x while in state %s\n",
			     fc_frame_payload_op(fp), fc_rport_state(rdata));
		mutex_unlock(&rdata->rp_mutex);
		kref_put(&rdata->kref, fc_rport_destroy);
		जाओ reject;
	पूर्ण

	चयन (fc_frame_payload_op(fp)) अणु
	हाल ELS_PRLI:
		fc_rport_recv_prli_req(rdata, fp);
		अवरोध;
	हाल ELS_PRLO:
		fc_rport_recv_prlo_req(rdata, fp);
		अवरोध;
	हाल ELS_ADISC:
		fc_rport_recv_adisc_req(rdata, fp);
		अवरोध;
	हाल ELS_RRQ:
		fc_seq_els_rsp_send(fp, ELS_RRQ, शून्य);
		fc_frame_मुक्त(fp);
		अवरोध;
	हाल ELS_REC:
		fc_seq_els_rsp_send(fp, ELS_REC, शून्य);
		fc_frame_मुक्त(fp);
		अवरोध;
	हाल ELS_RLS:
		fc_rport_recv_rls_req(rdata, fp);
		अवरोध;
	हाल ELS_RTV:
		fc_rport_recv_rtv_req(rdata, fp);
		अवरोध;
	शेष:
		fc_frame_मुक्त(fp);	/* can't happen */
		अवरोध;
	पूर्ण

	mutex_unlock(&rdata->rp_mutex);
	kref_put(&rdata->kref, fc_rport_destroy);
	वापस;

reject:
	els_data.reason = ELS_RJT_UNAB;
	els_data.explan = ELS_EXPL_PLOGI_REQD;
	fc_seq_els_rsp_send(fp, ELS_LS_RJT, &els_data);
	fc_frame_मुक्त(fp);
	वापस;

busy:
	els_data.reason = ELS_RJT_BUSY;
	els_data.explan = ELS_EXPL_NONE;
	fc_seq_els_rsp_send(fp, ELS_LS_RJT, &els_data);
	fc_frame_मुक्त(fp);
	वापस;
पूर्ण

/**
 * fc_rport_recv_req() - Handler क्रम requests
 * @lport: The local port that received the request
 * @fp:	   The request frame
 *
 * Reference counting: करोes not modअगरy kref
 */
व्योम fc_rport_recv_req(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_seq_els_data els_data;

	lockdep_निश्चित_held(&lport->lp_mutex);

	/*
	 * Handle FLOGI, PLOGI and LOGO requests separately, since they
	 * करोn't require prior login.
	 * Check क्रम unsupported opcodes first and reject them.
	 * For some ops, it would be incorrect to reject with "PLOGI required".
	 */
	चयन (fc_frame_payload_op(fp)) अणु
	हाल ELS_FLOGI:
		fc_rport_recv_flogi_req(lport, fp);
		अवरोध;
	हाल ELS_PLOGI:
		fc_rport_recv_plogi_req(lport, fp);
		अवरोध;
	हाल ELS_LOGO:
		fc_rport_recv_logo_req(lport, fp);
		अवरोध;
	हाल ELS_PRLI:
	हाल ELS_PRLO:
	हाल ELS_ADISC:
	हाल ELS_RRQ:
	हाल ELS_REC:
	हाल ELS_RLS:
	हाल ELS_RTV:
		fc_rport_recv_els_req(lport, fp);
		अवरोध;
	शेष:
		els_data.reason = ELS_RJT_UNSUP;
		els_data.explan = ELS_EXPL_NONE;
		fc_seq_els_rsp_send(fp, ELS_LS_RJT, &els_data);
		fc_frame_मुक्त(fp);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fc_rport_recv_req);

/**
 * fc_rport_recv_plogi_req() - Handler क्रम Port Login (PLOGI) requests
 * @lport: The local port that received the PLOGI request
 * @rx_fp: The PLOGI request frame
 *
 * Reference counting: increments kref on वापस
 */
अटल व्योम fc_rport_recv_plogi_req(काष्ठा fc_lport *lport,
				    काष्ठा fc_frame *rx_fp)
अणु
	काष्ठा fc_disc *disc;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा fc_frame *fp = rx_fp;
	काष्ठा fc_els_flogi *pl;
	काष्ठा fc_seq_els_data rjt_data;
	u32 sid;

	lockdep_निश्चित_held(&lport->lp_mutex);

	sid = fc_frame_sid(fp);

	FC_RPORT_ID_DBG(lport, sid, "Received PLOGI request\n");

	pl = fc_frame_payload_get(fp, माप(*pl));
	अगर (!pl) अणु
		FC_RPORT_ID_DBG(lport, sid, "Received PLOGI too short\n");
		rjt_data.reason = ELS_RJT_PROT;
		rjt_data.explan = ELS_EXPL_INV_LEN;
		जाओ reject;
	पूर्ण

	disc = &lport->disc;
	mutex_lock(&disc->disc_mutex);
	rdata = fc_rport_create(lport, sid);
	अगर (!rdata) अणु
		mutex_unlock(&disc->disc_mutex);
		rjt_data.reason = ELS_RJT_UNAB;
		rjt_data.explan = ELS_EXPL_INSUF_RES;
		जाओ reject;
	पूर्ण

	mutex_lock(&rdata->rp_mutex);
	mutex_unlock(&disc->disc_mutex);

	rdata->ids.port_name = get_unaligned_be64(&pl->fl_wwpn);
	rdata->ids.node_name = get_unaligned_be64(&pl->fl_wwnn);

	/*
	 * If the rport was just created, possibly due to the incoming PLOGI,
	 * set the state appropriately and accept the PLOGI.
	 *
	 * If we had also sent a PLOGI, and अगर the received PLOGI is from a
	 * higher WWPN, we accept it, otherwise an LS_RJT is sent with reason
	 * "command already in progress".
	 *
	 * XXX TBD: If the session was पढ़ोy beक्रमe, the PLOGI should result in
	 * all outstanding exchanges being reset.
	 */
	चयन (rdata->rp_state) अणु
	हाल RPORT_ST_INIT:
		FC_RPORT_DBG(rdata, "Received PLOGI in INIT state\n");
		अवरोध;
	हाल RPORT_ST_PLOGI_WAIT:
		FC_RPORT_DBG(rdata, "Received PLOGI in PLOGI_WAIT state\n");
		अवरोध;
	हाल RPORT_ST_PLOGI:
		FC_RPORT_DBG(rdata, "Received PLOGI in PLOGI state\n");
		अगर (rdata->ids.port_name < lport->wwpn) अणु
			mutex_unlock(&rdata->rp_mutex);
			rjt_data.reason = ELS_RJT_INPROG;
			rjt_data.explan = ELS_EXPL_NONE;
			जाओ reject;
		पूर्ण
		अवरोध;
	हाल RPORT_ST_PRLI:
	हाल RPORT_ST_RTV:
	हाल RPORT_ST_READY:
	हाल RPORT_ST_ADISC:
		FC_RPORT_DBG(rdata, "Received PLOGI in logged-in state %d "
			     "- ignored for now\n", rdata->rp_state);
		/* XXX TBD - should reset */
		अवरोध;
	हाल RPORT_ST_FLOGI:
	हाल RPORT_ST_DELETE:
		FC_RPORT_DBG(rdata, "Received PLOGI in state %s - send busy\n",
			     fc_rport_state(rdata));
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_BUSY;
		rjt_data.explan = ELS_EXPL_NONE;
		जाओ reject;
	पूर्ण
	अगर (!fc_rport_compatible_roles(lport, rdata)) अणु
		FC_RPORT_DBG(rdata, "Received PLOGI for incompatible role\n");
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_LOGIC;
		rjt_data.explan = ELS_EXPL_NONE;
		जाओ reject;
	पूर्ण

	/*
	 * Get session payload size from incoming PLOGI.
	 */
	rdata->maxframe_size = fc_plogi_get_maxframe(pl, lport->mfs);

	/*
	 * Send LS_ACC.	 If this fails, the originator should retry.
	 */
	fp = fc_frame_alloc(lport, माप(*pl));
	अगर (!fp)
		जाओ out;

	fc_plogi_fill(lport, fp, ELS_LS_ACC);
	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
	fc_rport_enter_prli(rdata);
out:
	mutex_unlock(&rdata->rp_mutex);
	fc_frame_मुक्त(rx_fp);
	वापस;

reject:
	fc_seq_els_rsp_send(fp, ELS_LS_RJT, &rjt_data);
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_rport_recv_prli_req() - Handler क्रम process login (PRLI) requests
 * @rdata: The remote port that sent the PRLI request
 * @rx_fp: The PRLI request frame
 */
अटल व्योम fc_rport_recv_prli_req(काष्ठा fc_rport_priv *rdata,
				   काष्ठा fc_frame *rx_fp)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_frame *fp;
	काष्ठा अणु
		काष्ठा fc_els_prli prli;
		काष्ठा fc_els_spp spp;
	पूर्ण *pp;
	काष्ठा fc_els_spp *rspp;	/* request service param page */
	काष्ठा fc_els_spp *spp;	/* response spp */
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक plen;
	क्रमागत fc_els_spp_resp resp;
	काष्ठा fc_seq_els_data rjt_data;
	काष्ठा fc4_prov *prov;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Received PRLI request while in state %s\n",
		     fc_rport_state(rdata));

	len = fr_len(rx_fp) - माप(काष्ठा fc_frame_header);
	pp = fc_frame_payload_get(rx_fp, माप(*pp));
	अगर (!pp)
		जाओ reject_len;
	plen = ntohs(pp->prli.prli_len);
	अगर ((plen % 4) != 0 || plen > len || plen < 16)
		जाओ reject_len;
	अगर (plen < len)
		len = plen;
	plen = pp->prli.prli_spp_len;
	अगर ((plen % 4) != 0 || plen < माप(*spp) ||
	    plen > len || len < माप(*pp) || plen < 12)
		जाओ reject_len;
	rspp = &pp->spp;

	fp = fc_frame_alloc(lport, len);
	अगर (!fp) अणु
		rjt_data.reason = ELS_RJT_UNAB;
		rjt_data.explan = ELS_EXPL_INSUF_RES;
		जाओ reject;
	पूर्ण
	pp = fc_frame_payload_get(fp, len);
	WARN_ON(!pp);
	स_रखो(pp, 0, len);
	pp->prli.prli_cmd = ELS_LS_ACC;
	pp->prli.prli_spp_len = plen;
	pp->prli.prli_len = htons(len);
	len -= माप(काष्ठा fc_els_prli);

	/*
	 * Go through all the service parameter pages and build
	 * response.  If plen indicates दीर्घer SPP than standard,
	 * use that.  The entire response has been pre-cleared above.
	 */
	spp = &pp->spp;
	mutex_lock(&fc_prov_mutex);
	जबतक (len >= plen) अणु
		rdata->spp_type = rspp->spp_type;
		spp->spp_type = rspp->spp_type;
		spp->spp_type_ext = rspp->spp_type_ext;
		resp = 0;

		अगर (rspp->spp_type < FC_FC4_PROV_SIZE) अणु
			क्रमागत fc_els_spp_resp active = 0, passive = 0;

			prov = fc_active_prov[rspp->spp_type];
			अगर (prov)
				active = prov->prli(rdata, plen, rspp, spp);
			prov = fc_passive_prov[rspp->spp_type];
			अगर (prov)
				passive = prov->prli(rdata, plen, rspp, spp);
			अगर (!active || passive == FC_SPP_RESP_ACK)
				resp = passive;
			अन्यथा
				resp = active;
			FC_RPORT_DBG(rdata, "PRLI rspp type %x "
				     "active %x passive %x\n",
				     rspp->spp_type, active, passive);
		पूर्ण
		अगर (!resp) अणु
			अगर (spp->spp_flags & FC_SPP_EST_IMG_PAIR)
				resp |= FC_SPP_RESP_CONF;
			अन्यथा
				resp |= FC_SPP_RESP_INVL;
		पूर्ण
		spp->spp_flags |= resp;
		len -= plen;
		rspp = (काष्ठा fc_els_spp *)((अक्षर *)rspp + plen);
		spp = (काष्ठा fc_els_spp *)((अक्षर *)spp + plen);
	पूर्ण
	mutex_unlock(&fc_prov_mutex);

	/*
	 * Send LS_ACC.	 If this fails, the originator should retry.
	 */
	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);

	जाओ drop;

reject_len:
	rjt_data.reason = ELS_RJT_PROT;
	rjt_data.explan = ELS_EXPL_INV_LEN;
reject:
	fc_seq_els_rsp_send(rx_fp, ELS_LS_RJT, &rjt_data);
drop:
	fc_frame_मुक्त(rx_fp);
पूर्ण

/**
 * fc_rport_recv_prlo_req() - Handler क्रम process logout (PRLO) requests
 * @rdata: The remote port that sent the PRLO request
 * @rx_fp: The PRLO request frame
 */
अटल व्योम fc_rport_recv_prlo_req(काष्ठा fc_rport_priv *rdata,
				   काष्ठा fc_frame *rx_fp)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	काष्ठा fc_frame *fp;
	काष्ठा अणु
		काष्ठा fc_els_prlo prlo;
		काष्ठा fc_els_spp spp;
	पूर्ण *pp;
	काष्ठा fc_els_spp *rspp;	/* request service param page */
	काष्ठा fc_els_spp *spp;		/* response spp */
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक plen;
	काष्ठा fc_seq_els_data rjt_data;

	lockdep_निश्चित_held(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Received PRLO request while in state %s\n",
		     fc_rport_state(rdata));

	len = fr_len(rx_fp) - माप(काष्ठा fc_frame_header);
	pp = fc_frame_payload_get(rx_fp, माप(*pp));
	अगर (!pp)
		जाओ reject_len;
	plen = ntohs(pp->prlo.prlo_len);
	अगर (plen != 20)
		जाओ reject_len;
	अगर (plen < len)
		len = plen;

	rspp = &pp->spp;

	fp = fc_frame_alloc(lport, len);
	अगर (!fp) अणु
		rjt_data.reason = ELS_RJT_UNAB;
		rjt_data.explan = ELS_EXPL_INSUF_RES;
		जाओ reject;
	पूर्ण

	pp = fc_frame_payload_get(fp, len);
	WARN_ON(!pp);
	स_रखो(pp, 0, len);
	pp->prlo.prlo_cmd = ELS_LS_ACC;
	pp->prlo.prlo_obs = 0x10;
	pp->prlo.prlo_len = htons(len);
	spp = &pp->spp;
	spp->spp_type = rspp->spp_type;
	spp->spp_type_ext = rspp->spp_type_ext;
	spp->spp_flags = FC_SPP_RESP_ACK;

	fc_rport_enter_prli(rdata);

	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
	जाओ drop;

reject_len:
	rjt_data.reason = ELS_RJT_PROT;
	rjt_data.explan = ELS_EXPL_INV_LEN;
reject:
	fc_seq_els_rsp_send(rx_fp, ELS_LS_RJT, &rjt_data);
drop:
	fc_frame_मुक्त(rx_fp);
पूर्ण

/**
 * fc_rport_recv_logo_req() - Handler क्रम logout (LOGO) requests
 * @lport: The local port that received the LOGO request
 * @fp:	   The LOGO request frame
 *
 * Reference counting: drops kref on वापस
 */
अटल व्योम fc_rport_recv_logo_req(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_rport_priv *rdata;
	u32 sid;

	lockdep_निश्चित_held(&lport->lp_mutex);

	fc_seq_els_rsp_send(fp, ELS_LS_ACC, शून्य);

	sid = fc_frame_sid(fp);

	rdata = fc_rport_lookup(lport, sid);
	अगर (rdata) अणु
		mutex_lock(&rdata->rp_mutex);
		FC_RPORT_DBG(rdata, "Received LOGO request while in state %s\n",
			     fc_rport_state(rdata));

		fc_rport_enter_delete(rdata, RPORT_EV_STOP);
		mutex_unlock(&rdata->rp_mutex);
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण अन्यथा
		FC_RPORT_ID_DBG(lport, sid,
				"Received LOGO from non-logged-in port\n");
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_rport_flush_queue() - Flush the rport_event_queue
 */
व्योम fc_rport_flush_queue(व्योम)
अणु
	flush_workqueue(rport_event_queue);
पूर्ण
EXPORT_SYMBOL(fc_rport_flush_queue);

/**
 * fc_rport_fcp_prli() - Handle incoming PRLI क्रम the FCP initiator.
 * @rdata: remote port निजी
 * @spp_len: service parameter page length
 * @rspp: received service parameter page
 * @spp: response service parameter page
 *
 * Returns the value क्रम the response code to be placed in spp_flags;
 * Returns 0 अगर not an initiator.
 */
अटल पूर्णांक fc_rport_fcp_prli(काष्ठा fc_rport_priv *rdata, u32 spp_len,
			     स्थिर काष्ठा fc_els_spp *rspp,
			     काष्ठा fc_els_spp *spp)
अणु
	काष्ठा fc_lport *lport = rdata->local_port;
	u32 fcp_parm;

	fcp_parm = ntohl(rspp->spp_params);
	rdata->ids.roles = FC_RPORT_ROLE_UNKNOWN;
	अगर (fcp_parm & FCP_SPPF_INIT_FCN)
		rdata->ids.roles |= FC_RPORT_ROLE_FCP_INITIATOR;
	अगर (fcp_parm & FCP_SPPF_TARG_FCN)
		rdata->ids.roles |= FC_RPORT_ROLE_FCP_TARGET;
	अगर (fcp_parm & FCP_SPPF_RETRY)
		rdata->flags |= FC_RP_FLAGS_RETRY;
	rdata->supported_classes = FC_COS_CLASS3;

	अगर (!(lport->service_params & FCP_SPPF_INIT_FCN))
		वापस 0;

	spp->spp_flags |= rspp->spp_flags & FC_SPP_EST_IMG_PAIR;

	/*
	 * OR in our service parameters with other providers (target), अगर any.
	 */
	fcp_parm = ntohl(spp->spp_params);
	spp->spp_params = htonl(fcp_parm | lport->service_params);
	वापस FC_SPP_RESP_ACK;
पूर्ण

/*
 * FC-4 provider ops क्रम FCP initiator.
 */
काष्ठा fc4_prov fc_rport_fcp_init = अणु
	.prli = fc_rport_fcp_prli,
पूर्ण;

/**
 * fc_rport_t0_prli() - Handle incoming PRLI parameters क्रम type 0
 * @rdata: remote port निजी
 * @spp_len: service parameter page length
 * @rspp: received service parameter page
 * @spp: response service parameter page
 */
अटल पूर्णांक fc_rport_t0_prli(काष्ठा fc_rport_priv *rdata, u32 spp_len,
			    स्थिर काष्ठा fc_els_spp *rspp,
			    काष्ठा fc_els_spp *spp)
अणु
	अगर (rspp->spp_flags & FC_SPP_EST_IMG_PAIR)
		वापस FC_SPP_RESP_INVL;
	वापस FC_SPP_RESP_ACK;
पूर्ण

/*
 * FC-4 provider ops क्रम type 0 service parameters.
 *
 * This handles the special हाल of type 0 which is always successful
 * but करोesn't करो anything otherwise.
 */
काष्ठा fc4_prov fc_rport_t0_prov = अणु
	.prli = fc_rport_t0_prli,
पूर्ण;

/**
 * fc_setup_rport() - Initialize the rport_event_queue
 */
पूर्णांक fc_setup_rport(व्योम)
अणु
	rport_event_queue = create_singlethपढ़ो_workqueue("fc_rport_eq");
	अगर (!rport_event_queue)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * fc_destroy_rport() - Destroy the rport_event_queue
 */
व्योम fc_destroy_rport(व्योम)
अणु
	destroy_workqueue(rport_event_queue);
पूर्ण

/**
 * fc_rport_terminate_io() - Stop all outstanding I/O on a remote port
 * @rport: The remote port whose I/O should be terminated
 */
व्योम fc_rport_terminate_io(काष्ठा fc_rport *rport)
अणु
	काष्ठा fc_rport_libfc_priv *rpriv = rport->dd_data;
	काष्ठा fc_lport *lport = rpriv->local_port;

	lport->tt.exch_mgr_reset(lport, 0, rport->port_id);
	lport->tt.exch_mgr_reset(lport, rport->port_id, 0);
पूर्ण
EXPORT_SYMBOL(fc_rport_terminate_io);
