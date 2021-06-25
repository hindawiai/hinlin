<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (c) 2004-2009 Silicon Graphics, Inc.  All Rights Reserved.
 */

/*
 * Cross Partition Communication (XPC) support - standard version.
 *
 *	XPC provides a message passing capability that crosses partition
 *	boundaries. This module is made up of two parts:
 *
 *	    partition	This part detects the presence/असलence of other
 *			partitions. It provides a heartbeat and monitors
 *			the heartbeats of other partitions.
 *
 *	    channel	This part manages the channels and sends/receives
 *			messages across them to/from other partitions.
 *
 *	There are a couple of additional functions residing in XP, which
 *	provide an पूर्णांकerface to XPC क्रम its users.
 *
 *
 *	Caveats:
 *
 *	  . Currently on sn2, we have no way to determine which nasid an IRQ
 *	    came from. Thus, xpc_send_IRQ_sn2() करोes a remote amo ग_लिखो
 *	    followed by an IPI. The amo indicates where data is to be pulled
 *	    from, so after the IPI arrives, the remote partition checks the amo
 *	    word. The IPI can actually arrive beक्रमe the amo however, so other
 *	    code must periodically check क्रम this हाल. Also, remote amo
 *	    operations करो not reliably समय out. Thus we करो a remote PIO पढ़ो
 *	    solely to know whether the remote partition is करोwn and whether we
 *	    should stop sending IPIs to it. This remote PIO पढ़ो operation is
 *	    set up in a special nofault region so SAL knows to ignore (and
 *	    cleanup) any errors due to the remote amo ग_लिखो, PIO पढ़ो, and/or
 *	    PIO ग_लिखो operations.
 *
 *	    If/when new hardware solves this IPI problem, we should abanकरोn
 *	    the current approach.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/reboot.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश "xpc.h"

#अगर_घोषित CONFIG_X86_64
#समावेश <यंत्र/traps.h>
#पूर्ण_अगर

/* define two XPC debug device काष्ठाures to be used with dev_dbg() et al */

अटल काष्ठा device_driver xpc_dbg_name = अणु
	.name = "xpc"
पूर्ण;

अटल काष्ठा device xpc_part_dbg_subname = अणु
	.init_name = "",	/* set to "part" at xpc_init() समय */
	.driver = &xpc_dbg_name
पूर्ण;

अटल काष्ठा device xpc_chan_dbg_subname = अणु
	.init_name = "",	/* set to "chan" at xpc_init() समय */
	.driver = &xpc_dbg_name
पूर्ण;

काष्ठा device *xpc_part = &xpc_part_dbg_subname;
काष्ठा device *xpc_chan = &xpc_chan_dbg_subname;

अटल पूर्णांक xpc_kdebug_ignore;

/* systune related variables क्रम /proc/sys directories */

अटल पूर्णांक xpc_hb_पूर्णांकerval = XPC_HB_DEFAULT_INTERVAL;
अटल पूर्णांक xpc_hb_min_पूर्णांकerval = 1;
अटल पूर्णांक xpc_hb_max_पूर्णांकerval = 10;

अटल पूर्णांक xpc_hb_check_पूर्णांकerval = XPC_HB_CHECK_DEFAULT_INTERVAL;
अटल पूर्णांक xpc_hb_check_min_पूर्णांकerval = 10;
अटल पूर्णांक xpc_hb_check_max_पूर्णांकerval = 120;

पूर्णांक xpc_disengage_समयlimit = XPC_DISENGAGE_DEFAULT_TIMELIMIT;
अटल पूर्णांक xpc_disengage_min_समयlimit;	/* = 0 */
अटल पूर्णांक xpc_disengage_max_समयlimit = 120;

अटल काष्ठा ctl_table xpc_sys_xpc_hb_dir[] = अणु
	अणु
	 .procname = "hb_interval",
	 .data = &xpc_hb_पूर्णांकerval,
	 .maxlen = माप(पूर्णांक),
	 .mode = 0644,
	 .proc_handler = proc_करोपूर्णांकvec_minmax,
	 .extra1 = &xpc_hb_min_पूर्णांकerval,
	 .extra2 = &xpc_hb_max_पूर्णांकervalपूर्ण,
	अणु
	 .procname = "hb_check_interval",
	 .data = &xpc_hb_check_पूर्णांकerval,
	 .maxlen = माप(पूर्णांक),
	 .mode = 0644,
	 .proc_handler = proc_करोपूर्णांकvec_minmax,
	 .extra1 = &xpc_hb_check_min_पूर्णांकerval,
	 .extra2 = &xpc_hb_check_max_पूर्णांकervalपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल काष्ठा ctl_table xpc_sys_xpc_dir[] = अणु
	अणु
	 .procname = "hb",
	 .mode = 0555,
	 .child = xpc_sys_xpc_hb_dirपूर्ण,
	अणु
	 .procname = "disengage_timelimit",
	 .data = &xpc_disengage_समयlimit,
	 .maxlen = माप(पूर्णांक),
	 .mode = 0644,
	 .proc_handler = proc_करोपूर्णांकvec_minmax,
	 .extra1 = &xpc_disengage_min_समयlimit,
	 .extra2 = &xpc_disengage_max_समयlimitपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल काष्ठा ctl_table xpc_sys_dir[] = अणु
	अणु
	 .procname = "xpc",
	 .mode = 0555,
	 .child = xpc_sys_xpc_dirपूर्ण,
	अणुपूर्ण
पूर्ण;
अटल काष्ठा ctl_table_header *xpc_sysctl;

/* non-zero अगर any remote partition disengage was समयd out */
पूर्णांक xpc_disengage_समयकरोut;

/* #of activate IRQs received and not yet processed */
पूर्णांक xpc_activate_IRQ_rcvd;
DEFINE_SPINLOCK(xpc_activate_IRQ_rcvd_lock);

/* IRQ handler notअगरies this रुको queue on receipt of an IRQ */
DECLARE_WAIT_QUEUE_HEAD(xpc_activate_IRQ_wq);

अटल अचिन्हित दीर्घ xpc_hb_check_समयout;
अटल काष्ठा समयr_list xpc_hb_समयr;

/* notअगरication that the xpc_hb_checker thपढ़ो has निकासed */
अटल DECLARE_COMPLETION(xpc_hb_checker_निकासed);

/* notअगरication that the xpc_discovery thपढ़ो has निकासed */
अटल DECLARE_COMPLETION(xpc_discovery_निकासed);

अटल व्योम xpc_kthपढ़ो_रुकोmsgs(काष्ठा xpc_partition *, काष्ठा xpc_channel *);

अटल पूर्णांक xpc_प्रणाली_reboot(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल काष्ठा notअगरier_block xpc_reboot_notअगरier = अणु
	.notअगरier_call = xpc_प्रणाली_reboot,
पूर्ण;

अटल पूर्णांक xpc_प्रणाली_die(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल काष्ठा notअगरier_block xpc_die_notअगरier = अणु
	.notअगरier_call = xpc_प्रणाली_die,
पूर्ण;

काष्ठा xpc_arch_operations xpc_arch_ops;

/*
 * Timer function to enक्रमce the समयlimit on the partition disengage.
 */
अटल व्योम
xpc_समयout_partition_disengage(काष्ठा समयr_list *t)
अणु
	काष्ठा xpc_partition *part = from_समयr(part, t, disengage_समयr);

	DBUG_ON(समय_is_after_jअगरfies(part->disengage_समयout));

	xpc_partition_disengaged_from_समयr(part);

	DBUG_ON(part->disengage_समयout != 0);
	DBUG_ON(xpc_arch_ops.partition_engaged(XPC_PARTID(part)));
पूर्ण

/*
 * Timer to produce the heartbeat.  The समयr काष्ठाures function is
 * alपढ़ोy set when this is initially called.  A tunable is used to
 * specअगरy when the next समयout should occur.
 */
अटल व्योम
xpc_hb_beater(काष्ठा समयr_list *unused)
अणु
	xpc_arch_ops.increment_heartbeat();

	अगर (समय_is_beक्रमe_eq_jअगरfies(xpc_hb_check_समयout))
		wake_up_पूर्णांकerruptible(&xpc_activate_IRQ_wq);

	xpc_hb_समयr.expires = jअगरfies + (xpc_hb_पूर्णांकerval * HZ);
	add_समयr(&xpc_hb_समयr);
पूर्ण

अटल व्योम
xpc_start_hb_beater(व्योम)
अणु
	xpc_arch_ops.heartbeat_init();
	समयr_setup(&xpc_hb_समयr, xpc_hb_beater, 0);
	xpc_hb_beater(शून्य);
पूर्ण

अटल व्योम
xpc_stop_hb_beater(व्योम)
अणु
	del_समयr_sync(&xpc_hb_समयr);
	xpc_arch_ops.heartbeat_निकास();
पूर्ण

/*
 * At periodic पूर्णांकervals, scan through all active partitions and ensure
 * their heartbeat is still active.  If not, the partition is deactivated.
 */
अटल व्योम
xpc_check_remote_hb(व्योम)
अणु
	काष्ठा xpc_partition *part;
	लघु partid;
	क्रमागत xp_retval ret;

	क्रम (partid = 0; partid < xp_max_npartitions; partid++) अणु

		अगर (xpc_निकासing)
			अवरोध;

		अगर (partid == xp_partition_id)
			जारी;

		part = &xpc_partitions[partid];

		अगर (part->act_state == XPC_P_AS_INACTIVE ||
		    part->act_state == XPC_P_AS_DEACTIVATING) अणु
			जारी;
		पूर्ण

		ret = xpc_arch_ops.get_remote_heartbeat(part);
		अगर (ret != xpSuccess)
			XPC_DEACTIVATE_PARTITION(part, ret);
	पूर्ण
पूर्ण

/*
 * This thपढ़ो is responsible क्रम nearly all of the partition
 * activation/deactivation.
 */
अटल पूर्णांक
xpc_hb_checker(व्योम *ignore)
अणु
	पूर्णांक क्रमce_IRQ = 0;

	/* this thपढ़ो was marked active by xpc_hb_init() */

	set_cpus_allowed_ptr(current, cpumask_of(XPC_HB_CHECK_CPU));

	/* set our heartbeating to other partitions पूर्णांकo motion */
	xpc_hb_check_समयout = jअगरfies + (xpc_hb_check_पूर्णांकerval * HZ);
	xpc_start_hb_beater();

	जबतक (!xpc_निकासing) अणु

		dev_dbg(xpc_part, "woke up with %d ticks rem; %d IRQs have "
			"been received\n",
			(पूर्णांक)(xpc_hb_check_समयout - jअगरfies),
			xpc_activate_IRQ_rcvd);

		/* checking of remote heartbeats is skewed by IRQ handling */
		अगर (समय_is_beक्रमe_eq_jअगरfies(xpc_hb_check_समयout)) अणु
			xpc_hb_check_समयout = jअगरfies +
			    (xpc_hb_check_पूर्णांकerval * HZ);

			dev_dbg(xpc_part, "checking remote heartbeats\n");
			xpc_check_remote_hb();
		पूर्ण

		/* check क्रम outstanding IRQs */
		अगर (xpc_activate_IRQ_rcvd > 0 || क्रमce_IRQ != 0) अणु
			क्रमce_IRQ = 0;
			dev_dbg(xpc_part, "processing activate IRQs "
				"received\n");
			xpc_arch_ops.process_activate_IRQ_rcvd();
		पूर्ण

		/* रुको क्रम IRQ or समयout */
		(व्योम)रुको_event_पूर्णांकerruptible(xpc_activate_IRQ_wq,
					       (समय_is_beक्रमe_eq_jअगरfies(
						xpc_hb_check_समयout) ||
						xpc_activate_IRQ_rcvd > 0 ||
						xpc_निकासing));
	पूर्ण

	xpc_stop_hb_beater();

	dev_dbg(xpc_part, "heartbeat checker is exiting\n");

	/* mark this thपढ़ो as having निकासed */
	complete(&xpc_hb_checker_निकासed);
	वापस 0;
पूर्ण

/*
 * This thपढ़ो will attempt to discover other partitions to activate
 * based on info provided by SAL. This new thपढ़ो is लघु lived and
 * will निकास once discovery is complete.
 */
अटल पूर्णांक
xpc_initiate_discovery(व्योम *ignore)
अणु
	xpc_discovery();

	dev_dbg(xpc_part, "discovery thread is exiting\n");

	/* mark this thपढ़ो as having निकासed */
	complete(&xpc_discovery_निकासed);
	वापस 0;
पूर्ण

/*
 * The first kthपढ़ो asचिन्हित to a newly activated partition is the one
 * created by XPC HB with which it calls xpc_activating(). XPC hangs on to
 * that kthपढ़ो until the partition is brought करोwn, at which समय that kthपढ़ो
 * वापसs back to XPC HB. (The वापस of that kthपढ़ो will signअगरy to XPC HB
 * that XPC has dismantled all communication infraकाष्ठाure क्रम the associated
 * partition.) This kthपढ़ो becomes the channel manager क्रम that partition.
 *
 * Each active partition has a channel manager, who, besides connecting and
 * disconnecting channels, will ensure that each of the partition's connected
 * channels has the required number of asचिन्हित kthपढ़ोs to get the work करोne.
 */
अटल व्योम
xpc_channel_mgr(काष्ठा xpc_partition *part)
अणु
	जबतक (part->act_state != XPC_P_AS_DEACTIVATING ||
	       atomic_पढ़ो(&part->nchannels_active) > 0 ||
	       !xpc_partition_disengaged(part)) अणु

		xpc_process_sent_chctl_flags(part);

		/*
		 * Wait until we've been requested to activate kthपढ़ोs or
		 * all of the channel's message queues have been torn करोwn or
		 * a संकेत is pending.
		 *
		 * The channel_mgr_requests is set to 1 after being awakened,
		 * This is करोne to prevent the channel mgr from making one pass
		 * through the loop क्रम each request, since he will
		 * be servicing all the requests in one pass. The reason it's
		 * set to 1 instead of 0 is so that other kthपढ़ोs will know
		 * that the channel mgr is running and won't bother trying to
		 * wake him up.
		 */
		atomic_dec(&part->channel_mgr_requests);
		(व्योम)रुको_event_पूर्णांकerruptible(part->channel_mgr_wq,
				(atomic_पढ़ो(&part->channel_mgr_requests) > 0 ||
				 part->chctl.all_flags != 0 ||
				 (part->act_state == XPC_P_AS_DEACTIVATING &&
				 atomic_पढ़ो(&part->nchannels_active) == 0 &&
				 xpc_partition_disengaged(part))));
		atomic_set(&part->channel_mgr_requests, 1);
	पूर्ण
पूर्ण

/*
 * Guarantee that the kzalloc'd memory is cacheline aligned.
 */
व्योम *
xpc_kzalloc_cacheline_aligned(माप_प्रकार size, gfp_t flags, व्योम **base)
अणु
	/* see अगर kzalloc will give us cachline aligned memory by शेष */
	*base = kzalloc(size, flags);
	अगर (*base == शून्य)
		वापस शून्य;

	अगर ((u64)*base == L1_CACHE_ALIGN((u64)*base))
		वापस *base;

	kमुक्त(*base);

	/* nope, we'll have to करो it ourselves */
	*base = kzalloc(size + L1_CACHE_BYTES, flags);
	अगर (*base == शून्य)
		वापस शून्य;

	वापस (व्योम *)L1_CACHE_ALIGN((u64)*base);
पूर्ण

/*
 * Setup the channel काष्ठाures necessary to support XPartition Communication
 * between the specअगरied remote partition and the local one.
 */
अटल क्रमागत xp_retval
xpc_setup_ch_काष्ठाures(काष्ठा xpc_partition *part)
अणु
	क्रमागत xp_retval ret;
	पूर्णांक ch_number;
	काष्ठा xpc_channel *ch;
	लघु partid = XPC_PARTID(part);

	/*
	 * Allocate all of the channel काष्ठाures as a contiguous chunk of
	 * memory.
	 */
	DBUG_ON(part->channels != शून्य);
	part->channels = kसुस्मृति(XPC_MAX_NCHANNELS,
				 माप(काष्ठा xpc_channel),
				 GFP_KERNEL);
	अगर (part->channels == शून्य) अणु
		dev_err(xpc_chan, "can't get memory for channels\n");
		वापस xpNoMemory;
	पूर्ण

	/* allocate the remote खोलो and बंद args */

	part->remote_खोलोबंद_args =
	    xpc_kzalloc_cacheline_aligned(XPC_OPENCLOSE_ARGS_SIZE,
					  GFP_KERNEL, &part->
					  remote_खोलोबंद_args_base);
	अगर (part->remote_खोलोबंद_args == शून्य) अणु
		dev_err(xpc_chan, "can't get memory for remote connect args\n");
		ret = xpNoMemory;
		जाओ out_1;
	पूर्ण

	part->chctl.all_flags = 0;
	spin_lock_init(&part->chctl_lock);

	atomic_set(&part->channel_mgr_requests, 1);
	init_रुकोqueue_head(&part->channel_mgr_wq);

	part->nchannels = XPC_MAX_NCHANNELS;

	atomic_set(&part->nchannels_active, 0);
	atomic_set(&part->nchannels_engaged, 0);

	क्रम (ch_number = 0; ch_number < part->nchannels; ch_number++) अणु
		ch = &part->channels[ch_number];

		ch->partid = partid;
		ch->number = ch_number;
		ch->flags = XPC_C_DISCONNECTED;

		atomic_set(&ch->kthपढ़ोs_asचिन्हित, 0);
		atomic_set(&ch->kthपढ़ोs_idle, 0);
		atomic_set(&ch->kthपढ़ोs_active, 0);

		atomic_set(&ch->references, 0);
		atomic_set(&ch->n_to_notअगरy, 0);

		spin_lock_init(&ch->lock);
		init_completion(&ch->wdisconnect_रुको);

		atomic_set(&ch->n_on_msg_allocate_wq, 0);
		init_रुकोqueue_head(&ch->msg_allocate_wq);
		init_रुकोqueue_head(&ch->idle_wq);
	पूर्ण

	ret = xpc_arch_ops.setup_ch_काष्ठाures(part);
	अगर (ret != xpSuccess)
		जाओ out_2;

	/*
	 * With the setting of the partition setup_state to XPC_P_SS_SETUP,
	 * we're declaring that this partition is पढ़ोy to go.
	 */
	part->setup_state = XPC_P_SS_SETUP;

	वापस xpSuccess;

	/* setup of ch काष्ठाures failed */
out_2:
	kमुक्त(part->remote_खोलोबंद_args_base);
	part->remote_खोलोबंद_args = शून्य;
out_1:
	kमुक्त(part->channels);
	part->channels = शून्य;
	वापस ret;
पूर्ण

/*
 * Tearकरोwn the channel काष्ठाures necessary to support XPartition Communication
 * between the specअगरied remote partition and the local one.
 */
अटल व्योम
xpc_tearकरोwn_ch_काष्ठाures(काष्ठा xpc_partition *part)
अणु
	DBUG_ON(atomic_पढ़ो(&part->nchannels_engaged) != 0);
	DBUG_ON(atomic_पढ़ो(&part->nchannels_active) != 0);

	/*
	 * Make this partition inaccessible to local processes by marking it
	 * as no दीर्घer setup. Then रुको beक्रमe proceeding with the tearकरोwn
	 * until all existing references cease.
	 */
	DBUG_ON(part->setup_state != XPC_P_SS_SETUP);
	part->setup_state = XPC_P_SS_WTEARDOWN;

	रुको_event(part->tearकरोwn_wq, (atomic_पढ़ो(&part->references) == 0));

	/* now we can begin tearing करोwn the infraकाष्ठाure */

	xpc_arch_ops.tearकरोwn_ch_काष्ठाures(part);

	kमुक्त(part->remote_खोलोबंद_args_base);
	part->remote_खोलोबंद_args = शून्य;
	kमुक्त(part->channels);
	part->channels = शून्य;

	part->setup_state = XPC_P_SS_TORNDOWN;
पूर्ण

/*
 * When XPC HB determines that a partition has come up, it will create a new
 * kthपढ़ो and that kthपढ़ो will call this function to attempt to set up the
 * basic infraकाष्ठाure used क्रम Cross Partition Communication with the newly
 * upped partition.
 *
 * The kthपढ़ो that was created by XPC HB and which setup the XPC
 * infraकाष्ठाure will reमुख्य asचिन्हित to the partition becoming the channel
 * manager क्रम that partition until the partition is deactivating, at which
 * समय the kthपढ़ो will tearकरोwn the XPC infraकाष्ठाure and then निकास.
 */
अटल पूर्णांक
xpc_activating(व्योम *__partid)
अणु
	लघु partid = (u64)__partid;
	काष्ठा xpc_partition *part = &xpc_partitions[partid];
	अचिन्हित दीर्घ irq_flags;

	DBUG_ON(partid < 0 || partid >= xp_max_npartitions);

	spin_lock_irqsave(&part->act_lock, irq_flags);

	अगर (part->act_state == XPC_P_AS_DEACTIVATING) अणु
		part->act_state = XPC_P_AS_INACTIVE;
		spin_unlock_irqrestore(&part->act_lock, irq_flags);
		part->remote_rp_pa = 0;
		वापस 0;
	पूर्ण

	/* indicate the thपढ़ो is activating */
	DBUG_ON(part->act_state != XPC_P_AS_ACTIVATION_REQ);
	part->act_state = XPC_P_AS_ACTIVATING;

	XPC_SET_REASON(part, 0, 0);
	spin_unlock_irqrestore(&part->act_lock, irq_flags);

	dev_dbg(xpc_part, "activating partition %d\n", partid);

	xpc_arch_ops.allow_hb(partid);

	अगर (xpc_setup_ch_काष्ठाures(part) == xpSuccess) अणु
		(व्योम)xpc_part_ref(part);	/* this will always succeed */

		अगर (xpc_arch_ops.make_first_contact(part) == xpSuccess) अणु
			xpc_mark_partition_active(part);
			xpc_channel_mgr(part);
			/* won't वापस until partition is deactivating */
		पूर्ण

		xpc_part_deref(part);
		xpc_tearकरोwn_ch_काष्ठाures(part);
	पूर्ण

	xpc_arch_ops.disallow_hb(partid);
	xpc_mark_partition_inactive(part);

	अगर (part->reason == xpReactivating) अणु
		/* पूर्णांकerrupting ourselves results in activating partition */
		xpc_arch_ops.request_partition_reactivation(part);
	पूर्ण

	वापस 0;
पूर्ण

व्योम
xpc_activate_partition(काष्ठा xpc_partition *part)
अणु
	लघु partid = XPC_PARTID(part);
	अचिन्हित दीर्घ irq_flags;
	काष्ठा task_काष्ठा *kthपढ़ो;

	spin_lock_irqsave(&part->act_lock, irq_flags);

	DBUG_ON(part->act_state != XPC_P_AS_INACTIVE);

	part->act_state = XPC_P_AS_ACTIVATION_REQ;
	XPC_SET_REASON(part, xpCloneKThपढ़ो, __LINE__);

	spin_unlock_irqrestore(&part->act_lock, irq_flags);

	kthपढ़ो = kthपढ़ो_run(xpc_activating, (व्योम *)((u64)partid), "xpc%02d",
			      partid);
	अगर (IS_ERR(kthपढ़ो)) अणु
		spin_lock_irqsave(&part->act_lock, irq_flags);
		part->act_state = XPC_P_AS_INACTIVE;
		XPC_SET_REASON(part, xpCloneKThपढ़ोFailed, __LINE__);
		spin_unlock_irqrestore(&part->act_lock, irq_flags);
	पूर्ण
पूर्ण

व्योम
xpc_activate_kthपढ़ोs(काष्ठा xpc_channel *ch, पूर्णांक needed)
अणु
	पूर्णांक idle = atomic_पढ़ो(&ch->kthपढ़ोs_idle);
	पूर्णांक asचिन्हित = atomic_पढ़ो(&ch->kthपढ़ोs_asचिन्हित);
	पूर्णांक wakeup;

	DBUG_ON(needed <= 0);

	अगर (idle > 0) अणु
		wakeup = (needed > idle) ? idle : needed;
		needed -= wakeup;

		dev_dbg(xpc_chan, "wakeup %d idle kthreads, partid=%d, "
			"channel=%d\n", wakeup, ch->partid, ch->number);

		/* only wakeup the requested number of kthपढ़ोs */
		wake_up_nr(&ch->idle_wq, wakeup);
	पूर्ण

	अगर (needed <= 0)
		वापस;

	अगर (needed + asचिन्हित > ch->kthपढ़ोs_asचिन्हित_limit) अणु
		needed = ch->kthपढ़ोs_asचिन्हित_limit - asचिन्हित;
		अगर (needed <= 0)
			वापस;
	पूर्ण

	dev_dbg(xpc_chan, "create %d new kthreads, partid=%d, channel=%d\n",
		needed, ch->partid, ch->number);

	xpc_create_kthपढ़ोs(ch, needed, 0);
पूर्ण

/*
 * This function is where XPC's kthपढ़ोs रुको क्रम messages to deliver.
 */
अटल व्योम
xpc_kthपढ़ो_रुकोmsgs(काष्ठा xpc_partition *part, काष्ठा xpc_channel *ch)
अणु
	पूर्णांक (*n_of_deliverable_payloads) (काष्ठा xpc_channel *) =
		xpc_arch_ops.n_of_deliverable_payloads;

	करो अणु
		/* deliver messages to their पूर्णांकended recipients */

		जबतक (n_of_deliverable_payloads(ch) > 0 &&
		       !(ch->flags & XPC_C_DISCONNECTING)) अणु
			xpc_deliver_payload(ch);
		पूर्ण

		अगर (atomic_inc_वापस(&ch->kthपढ़ोs_idle) >
		    ch->kthपढ़ोs_idle_limit) अणु
			/* too many idle kthपढ़ोs on this channel */
			atomic_dec(&ch->kthपढ़ोs_idle);
			अवरोध;
		पूर्ण

		dev_dbg(xpc_chan, "idle kthread calling "
			"wait_event_interruptible_exclusive()\n");

		(व्योम)रुको_event_पूर्णांकerruptible_exclusive(ch->idle_wq,
				(n_of_deliverable_payloads(ch) > 0 ||
				 (ch->flags & XPC_C_DISCONNECTING)));

		atomic_dec(&ch->kthपढ़ोs_idle);

	पूर्ण जबतक (!(ch->flags & XPC_C_DISCONNECTING));
पूर्ण

अटल पूर्णांक
xpc_kthपढ़ो_start(व्योम *args)
अणु
	लघु partid = XPC_UNPACK_ARG1(args);
	u16 ch_number = XPC_UNPACK_ARG2(args);
	काष्ठा xpc_partition *part = &xpc_partitions[partid];
	काष्ठा xpc_channel *ch;
	पूर्णांक n_needed;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक (*n_of_deliverable_payloads) (काष्ठा xpc_channel *) =
		xpc_arch_ops.n_of_deliverable_payloads;

	dev_dbg(xpc_chan, "kthread starting, partid=%d, channel=%d\n",
		partid, ch_number);

	ch = &part->channels[ch_number];

	अगर (!(ch->flags & XPC_C_DISCONNECTING)) अणु

		/* let रेजिस्टरer know that connection has been established */

		spin_lock_irqsave(&ch->lock, irq_flags);
		अगर (!(ch->flags & XPC_C_CONNECTEDCALLOUT)) अणु
			ch->flags |= XPC_C_CONNECTEDCALLOUT;
			spin_unlock_irqrestore(&ch->lock, irq_flags);

			xpc_connected_callout(ch);

			spin_lock_irqsave(&ch->lock, irq_flags);
			ch->flags |= XPC_C_CONNECTEDCALLOUT_MADE;
			spin_unlock_irqrestore(&ch->lock, irq_flags);

			/*
			 * It is possible that जबतक the callout was being
			 * made that the remote partition sent some messages.
			 * If that is the हाल, we may need to activate
			 * additional kthपढ़ोs to help deliver them. We only
			 * need one less than total #of messages to deliver.
			 */
			n_needed = n_of_deliverable_payloads(ch) - 1;
			अगर (n_needed > 0 && !(ch->flags & XPC_C_DISCONNECTING))
				xpc_activate_kthपढ़ोs(ch, n_needed);

		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&ch->lock, irq_flags);
		पूर्ण

		xpc_kthपढ़ो_रुकोmsgs(part, ch);
	पूर्ण

	/* let रेजिस्टरer know that connection is disconnecting */

	spin_lock_irqsave(&ch->lock, irq_flags);
	अगर ((ch->flags & XPC_C_CONNECTEDCALLOUT_MADE) &&
	    !(ch->flags & XPC_C_DISCONNECTINGCALLOUT)) अणु
		ch->flags |= XPC_C_DISCONNECTINGCALLOUT;
		spin_unlock_irqrestore(&ch->lock, irq_flags);

		xpc_disconnect_callout(ch, xpDisconnecting);

		spin_lock_irqsave(&ch->lock, irq_flags);
		ch->flags |= XPC_C_DISCONNECTINGCALLOUT_MADE;
	पूर्ण
	spin_unlock_irqrestore(&ch->lock, irq_flags);

	अगर (atomic_dec_वापस(&ch->kthपढ़ोs_asचिन्हित) == 0 &&
	    atomic_dec_वापस(&part->nchannels_engaged) == 0) अणु
		xpc_arch_ops.indicate_partition_disengaged(part);
	पूर्ण

	xpc_msgqueue_deref(ch);

	dev_dbg(xpc_chan, "kthread exiting, partid=%d, channel=%d\n",
		partid, ch_number);

	xpc_part_deref(part);
	वापस 0;
पूर्ण

/*
 * For each partition that XPC has established communications with, there is
 * a minimum of one kernel thपढ़ो asचिन्हित to perक्रमm any operation that
 * may potentially sleep or block (basically the callouts to the asynchronous
 * functions रेजिस्टरed via xpc_connect()).
 *
 * Additional kthपढ़ोs are created and destroyed by XPC as the workload
 * demands.
 *
 * A kthपढ़ो is asचिन्हित to one of the active channels that exists क्रम a given
 * partition.
 */
व्योम
xpc_create_kthपढ़ोs(काष्ठा xpc_channel *ch, पूर्णांक needed,
		    पूर्णांक ignore_disconnecting)
अणु
	अचिन्हित दीर्घ irq_flags;
	u64 args = XPC_PACK_ARGS(ch->partid, ch->number);
	काष्ठा xpc_partition *part = &xpc_partitions[ch->partid];
	काष्ठा task_काष्ठा *kthपढ़ो;
	व्योम (*indicate_partition_disengaged) (काष्ठा xpc_partition *) =
		xpc_arch_ops.indicate_partition_disengaged;

	जबतक (needed-- > 0) अणु

		/*
		 * The following is करोne on behalf of the newly created
		 * kthपढ़ो. That kthपढ़ो is responsible क्रम करोing the
		 * counterpart to the following beक्रमe it निकासs.
		 */
		अगर (ignore_disconnecting) अणु
			अगर (!atomic_inc_not_zero(&ch->kthपढ़ोs_asचिन्हित)) अणु
				/* kthपढ़ोs asचिन्हित had gone to zero */
				BUG_ON(!(ch->flags &
					 XPC_C_DISCONNECTINGCALLOUT_MADE));
				अवरोध;
			पूर्ण

		पूर्ण अन्यथा अगर (ch->flags & XPC_C_DISCONNECTING) अणु
			अवरोध;

		पूर्ण अन्यथा अगर (atomic_inc_वापस(&ch->kthपढ़ोs_asचिन्हित) == 1 &&
			   atomic_inc_वापस(&part->nchannels_engaged) == 1) अणु
			xpc_arch_ops.indicate_partition_engaged(part);
		पूर्ण
		(व्योम)xpc_part_ref(part);
		xpc_msgqueue_ref(ch);

		kthपढ़ो = kthपढ़ो_run(xpc_kthपढ़ो_start, (व्योम *)args,
				      "xpc%02dc%d", ch->partid, ch->number);
		अगर (IS_ERR(kthपढ़ो)) अणु
			/* the विभाजन failed */

			/*
			 * NOTE: अगर (ignore_disconnecting &&
			 * !(ch->flags & XPC_C_DISCONNECTINGCALLOUT)) is true,
			 * then we'll deadlock अगर all other kthपढ़ोs asचिन्हित
			 * to this channel are blocked in the channel's
			 * रेजिस्टरer, because the only thing that will unblock
			 * them is the xpDisconnecting callout that this
			 * failed kthपढ़ो_run() would have made.
			 */

			अगर (atomic_dec_वापस(&ch->kthपढ़ोs_asचिन्हित) == 0 &&
			    atomic_dec_वापस(&part->nchannels_engaged) == 0) अणु
				indicate_partition_disengaged(part);
			पूर्ण
			xpc_msgqueue_deref(ch);
			xpc_part_deref(part);

			अगर (atomic_पढ़ो(&ch->kthपढ़ोs_asचिन्हित) <
			    ch->kthपढ़ोs_idle_limit) अणु
				/*
				 * Flag this as an error only अगर we have an
				 * insufficient #of kthपढ़ोs क्रम the channel
				 * to function.
				 */
				spin_lock_irqsave(&ch->lock, irq_flags);
				XPC_DISCONNECT_CHANNEL(ch, xpLackOfResources,
						       &irq_flags);
				spin_unlock_irqrestore(&ch->lock, irq_flags);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
xpc_disconnect_रुको(पूर्णांक ch_number)
अणु
	अचिन्हित दीर्घ irq_flags;
	लघु partid;
	काष्ठा xpc_partition *part;
	काष्ठा xpc_channel *ch;
	पूर्णांक wakeup_channel_mgr;

	/* now रुको क्रम all callouts to the caller's function to cease */
	क्रम (partid = 0; partid < xp_max_npartitions; partid++) अणु
		part = &xpc_partitions[partid];

		अगर (!xpc_part_ref(part))
			जारी;

		ch = &part->channels[ch_number];

		अगर (!(ch->flags & XPC_C_WDISCONNECT)) अणु
			xpc_part_deref(part);
			जारी;
		पूर्ण

		रुको_क्रम_completion(&ch->wdisconnect_रुको);

		spin_lock_irqsave(&ch->lock, irq_flags);
		DBUG_ON(!(ch->flags & XPC_C_DISCONNECTED));
		wakeup_channel_mgr = 0;

		अगर (ch->delayed_chctl_flags) अणु
			अगर (part->act_state != XPC_P_AS_DEACTIVATING) अणु
				spin_lock(&part->chctl_lock);
				part->chctl.flags[ch->number] |=
				    ch->delayed_chctl_flags;
				spin_unlock(&part->chctl_lock);
				wakeup_channel_mgr = 1;
			पूर्ण
			ch->delayed_chctl_flags = 0;
		पूर्ण

		ch->flags &= ~XPC_C_WDISCONNECT;
		spin_unlock_irqrestore(&ch->lock, irq_flags);

		अगर (wakeup_channel_mgr)
			xpc_wakeup_channel_mgr(part);

		xpc_part_deref(part);
	पूर्ण
पूर्ण

अटल पूर्णांक
xpc_setup_partitions(व्योम)
अणु
	लघु partid;
	काष्ठा xpc_partition *part;

	xpc_partitions = kसुस्मृति(xp_max_npartitions,
				 माप(काष्ठा xpc_partition),
				 GFP_KERNEL);
	अगर (xpc_partitions == शून्य) अणु
		dev_err(xpc_part, "can't get memory for partition structure\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * The first few fields of each entry of xpc_partitions[] need to
	 * be initialized now so that calls to xpc_connect() and
	 * xpc_disconnect() can be made prior to the activation of any remote
	 * partition. NOTE THAT NONE OF THE OTHER FIELDS BELONGING TO THESE
	 * ENTRIES ARE MEANINGFUL UNTIL AFTER AN ENTRY'S CORRESPONDING
	 * PARTITION HAS BEEN ACTIVATED.
	 */
	क्रम (partid = 0; partid < xp_max_npartitions; partid++) अणु
		part = &xpc_partitions[partid];

		DBUG_ON((u64)part != L1_CACHE_ALIGN((u64)part));

		part->activate_IRQ_rcvd = 0;
		spin_lock_init(&part->act_lock);
		part->act_state = XPC_P_AS_INACTIVE;
		XPC_SET_REASON(part, 0, 0);

		समयr_setup(&part->disengage_समयr,
			    xpc_समयout_partition_disengage, 0);

		part->setup_state = XPC_P_SS_UNSET;
		init_रुकोqueue_head(&part->tearकरोwn_wq);
		atomic_set(&part->references, 0);
	पूर्ण

	वापस xpc_arch_ops.setup_partitions();
पूर्ण

अटल व्योम
xpc_tearकरोwn_partitions(व्योम)
अणु
	xpc_arch_ops.tearकरोwn_partitions();
	kमुक्त(xpc_partitions);
पूर्ण

अटल व्योम
xpc_करो_निकास(क्रमागत xp_retval reason)
अणु
	लघु partid;
	पूर्णांक active_part_count, prपूर्णांकed_रुकोing_msg = 0;
	काष्ठा xpc_partition *part;
	अचिन्हित दीर्घ prपूर्णांकmsg_समय, disengage_समयout = 0;

	/* a 'rmmod XPC' and a 'reboot' cannot both end up here together */
	DBUG_ON(xpc_निकासing == 1);

	/*
	 * Let the heartbeat checker thपढ़ो and the discovery thपढ़ो
	 * (अगर one is running) know that they should निकास. Also wake up
	 * the heartbeat checker thपढ़ो in हाल it's sleeping.
	 */
	xpc_निकासing = 1;
	wake_up_पूर्णांकerruptible(&xpc_activate_IRQ_wq);

	/* रुको क्रम the discovery thपढ़ो to निकास */
	रुको_क्रम_completion(&xpc_discovery_निकासed);

	/* रुको क्रम the heartbeat checker thपढ़ो to निकास */
	रुको_क्रम_completion(&xpc_hb_checker_निकासed);

	/* sleep क्रम a 1/3 of a second or so */
	(व्योम)msleep_पूर्णांकerruptible(300);

	/* रुको क्रम all partitions to become inactive */

	prपूर्णांकmsg_समय = jअगरfies + (XPC_DEACTIVATE_PRINTMSG_INTERVAL * HZ);
	xpc_disengage_समयकरोut = 0;

	करो अणु
		active_part_count = 0;

		क्रम (partid = 0; partid < xp_max_npartitions; partid++) अणु
			part = &xpc_partitions[partid];

			अगर (xpc_partition_disengaged(part) &&
			    part->act_state == XPC_P_AS_INACTIVE) अणु
				जारी;
			पूर्ण

			active_part_count++;

			XPC_DEACTIVATE_PARTITION(part, reason);

			अगर (part->disengage_समयout > disengage_समयout)
				disengage_समयout = part->disengage_समयout;
		पूर्ण

		अगर (xpc_arch_ops.any_partition_engaged()) अणु
			अगर (समय_is_beक्रमe_jअगरfies(prपूर्णांकmsg_समय)) अणु
				dev_info(xpc_part, "waiting for remote "
					 "partitions to deactivate, timeout in "
					 "%ld seconds\n", (disengage_समयout -
					 jअगरfies) / HZ);
				prपूर्णांकmsg_समय = jअगरfies +
				    (XPC_DEACTIVATE_PRINTMSG_INTERVAL * HZ);
				prपूर्णांकed_रुकोing_msg = 1;
			पूर्ण

		पूर्ण अन्यथा अगर (active_part_count > 0) अणु
			अगर (prपूर्णांकed_रुकोing_msg) अणु
				dev_info(xpc_part, "waiting for local partition"
					 " to deactivate\n");
				prपूर्णांकed_रुकोing_msg = 0;
			पूर्ण

		पूर्ण अन्यथा अणु
			अगर (!xpc_disengage_समयकरोut) अणु
				dev_info(xpc_part, "all partitions have "
					 "deactivated\n");
			पूर्ण
			अवरोध;
		पूर्ण

		/* sleep क्रम a 1/3 of a second or so */
		(व्योम)msleep_पूर्णांकerruptible(300);

	पूर्ण जबतक (1);

	DBUG_ON(xpc_arch_ops.any_partition_engaged());

	xpc_tearकरोwn_rsvd_page();

	अगर (reason == xpUnloading) अणु
		(व्योम)unरेजिस्टर_die_notअगरier(&xpc_die_notअगरier);
		(व्योम)unरेजिस्टर_reboot_notअगरier(&xpc_reboot_notअगरier);
	पूर्ण

	/* clear the पूर्णांकerface to XPC's functions */
	xpc_clear_पूर्णांकerface();

	अगर (xpc_sysctl)
		unरेजिस्टर_sysctl_table(xpc_sysctl);

	xpc_tearकरोwn_partitions();

	अगर (is_uv_प्रणाली())
		xpc_निकास_uv();
पूर्ण

/*
 * This function is called when the प्रणाली is being rebooted.
 */
अटल पूर्णांक
xpc_प्रणाली_reboot(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *unused)
अणु
	क्रमागत xp_retval reason;

	चयन (event) अणु
	हाल SYS_RESTART:
		reason = xpSystemReboot;
		अवरोध;
	हाल SYS_HALT:
		reason = xpSystemHalt;
		अवरोध;
	हाल SYS_POWER_OFF:
		reason = xpSystemPoweroff;
		अवरोध;
	शेष:
		reason = xpSystemGoingDown;
	पूर्ण

	xpc_करो_निकास(reason);
	वापस NOTIFY_DONE;
पूर्ण

/* Used to only allow one cpu to complete disconnect */
अटल अचिन्हित पूर्णांक xpc_die_disconnecting;

/*
 * Notअगरy other partitions to deactivate from us by first disengaging from all
 * references to our memory.
 */
अटल व्योम
xpc_die_deactivate(व्योम)
अणु
	काष्ठा xpc_partition *part;
	लघु partid;
	पूर्णांक any_engaged;
	दीर्घ keep_रुकोing;
	दीर्घ रुको_to_prपूर्णांक;

	अगर (cmpxchg(&xpc_die_disconnecting, 0, 1))
		वापस;

	/* keep xpc_hb_checker thपढ़ो from करोing anything (just in हाल) */
	xpc_निकासing = 1;

	xpc_arch_ops.disallow_all_hbs();   /*indicate we're deactivated */

	क्रम (partid = 0; partid < xp_max_npartitions; partid++) अणु
		part = &xpc_partitions[partid];

		अगर (xpc_arch_ops.partition_engaged(partid) ||
		    part->act_state != XPC_P_AS_INACTIVE) अणु
			xpc_arch_ops.request_partition_deactivation(part);
			xpc_arch_ops.indicate_partition_disengaged(part);
		पूर्ण
	पूर्ण

	/*
	 * Though we requested that all other partitions deactivate from us,
	 * we only रुको until they've all disengaged or we've reached the
	 * defined समयlimit.
	 *
	 * Given that one iteration through the following जबतक-loop takes
	 * approximately 200 microseconds, calculate the #of loops to take
	 * beक्रमe bailing and the #of loops beक्रमe prपूर्णांकing a रुकोing message.
	 */
	keep_रुकोing = xpc_disengage_समयlimit * 1000 * 5;
	रुको_to_prपूर्णांक = XPC_DEACTIVATE_PRINTMSG_INTERVAL * 1000 * 5;

	जबतक (1) अणु
		any_engaged = xpc_arch_ops.any_partition_engaged();
		अगर (!any_engaged) अणु
			dev_info(xpc_part, "all partitions have deactivated\n");
			अवरोध;
		पूर्ण

		अगर (!keep_रुकोing--) अणु
			क्रम (partid = 0; partid < xp_max_npartitions;
			     partid++) अणु
				अगर (xpc_arch_ops.partition_engaged(partid)) अणु
					dev_info(xpc_part, "deactivate from "
						 "remote partition %d timed "
						 "out\n", partid);
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (!रुको_to_prपूर्णांक--) अणु
			dev_info(xpc_part, "waiting for remote partitions to "
				 "deactivate, timeout in %ld seconds\n",
				 keep_रुकोing / (1000 * 5));
			रुको_to_prपूर्णांक = XPC_DEACTIVATE_PRINTMSG_INTERVAL *
			    1000 * 5;
		पूर्ण

		udelay(200);
	पूर्ण
पूर्ण

/*
 * This function is called when the प्रणाली is being restarted or halted due
 * to some sort of प्रणाली failure. If this is the हाल we need to notअगरy the
 * other partitions to disengage from all references to our memory.
 * This function can also be called when our heartbeater could be offlined
 * क्रम a समय. In this हाल we need to notअगरy other partitions to not worry
 * about the lack of a heartbeat.
 */
अटल पूर्णांक
xpc_प्रणाली_die(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *_die_args)
अणु
#अगर_घोषित CONFIG_IA64		/* !!! temporary kludge */
	चयन (event) अणु
	हाल DIE_MACHINE_RESTART:
	हाल DIE_MACHINE_HALT:
		xpc_die_deactivate();
		अवरोध;

	हाल DIE_KDEBUG_ENTER:
		/* Should lack of heartbeat be ignored by other partitions? */
		अगर (!xpc_kdebug_ignore)
			अवरोध;

		fallthrough;
	हाल DIE_MCA_MONARCH_ENTER:
	हाल DIE_INIT_MONARCH_ENTER:
		xpc_arch_ops.offline_heartbeat();
		अवरोध;

	हाल DIE_KDEBUG_LEAVE:
		/* Is lack of heartbeat being ignored by other partitions? */
		अगर (!xpc_kdebug_ignore)
			अवरोध;

		fallthrough;
	हाल DIE_MCA_MONARCH_LEAVE:
	हाल DIE_INIT_MONARCH_LEAVE:
		xpc_arch_ops.online_heartbeat();
		अवरोध;
	पूर्ण
#अन्यथा
	काष्ठा die_args *die_args = _die_args;

	चयन (event) अणु
	हाल DIE_TRAP:
		अगर (die_args->trapnr == X86_TRAP_DF)
			xpc_die_deactivate();

		अगर (((die_args->trapnr == X86_TRAP_MF) ||
		     (die_args->trapnr == X86_TRAP_XF)) &&
		    !user_mode(die_args->regs))
			xpc_die_deactivate();

		अवरोध;
	हाल DIE_INT3:
	हाल DIE_DEBUG:
		अवरोध;
	हाल DIE_OOPS:
	हाल DIE_GPF:
	शेष:
		xpc_die_deactivate();
	पूर्ण
#पूर्ण_अगर

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक __init
xpc_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा task_काष्ठा *kthपढ़ो;

	dev_set_name(xpc_part, "part");
	dev_set_name(xpc_chan, "chan");

	अगर (is_uv_प्रणाली()) अणु
		ret = xpc_init_uv();

	पूर्ण अन्यथा अणु
		ret = -ENODEV;
	पूर्ण

	अगर (ret != 0)
		वापस ret;

	ret = xpc_setup_partitions();
	अगर (ret != 0) अणु
		dev_err(xpc_part, "can't get memory for partition structure\n");
		जाओ out_1;
	पूर्ण

	xpc_sysctl = रेजिस्टर_sysctl_table(xpc_sys_dir);

	/*
	 * Fill the partition reserved page with the inक्रमmation needed by
	 * other partitions to discover we are alive and establish initial
	 * communications.
	 */
	ret = xpc_setup_rsvd_page();
	अगर (ret != 0) अणु
		dev_err(xpc_part, "can't setup our reserved page\n");
		जाओ out_2;
	पूर्ण

	/* add ourselves to the reboot_notअगरier_list */
	ret = रेजिस्टर_reboot_notअगरier(&xpc_reboot_notअगरier);
	अगर (ret != 0)
		dev_warn(xpc_part, "can't register reboot notifier\n");

	/* add ourselves to the die_notअगरier list */
	ret = रेजिस्टर_die_notअगरier(&xpc_die_notअगरier);
	अगर (ret != 0)
		dev_warn(xpc_part, "can't register die notifier\n");

	/*
	 * The real work-horse behind xpc.  This processes incoming
	 * पूर्णांकerrupts and monitors remote heartbeats.
	 */
	kthपढ़ो = kthपढ़ो_run(xpc_hb_checker, शून्य, XPC_HB_CHECK_THREAD_NAME);
	अगर (IS_ERR(kthपढ़ो)) अणु
		dev_err(xpc_part, "failed while forking hb check thread\n");
		ret = -EBUSY;
		जाओ out_3;
	पूर्ण

	/*
	 * Startup a thपढ़ो that will attempt to discover other partitions to
	 * activate based on info provided by SAL. This new thपढ़ो is लघु
	 * lived and will निकास once discovery is complete.
	 */
	kthपढ़ो = kthपढ़ो_run(xpc_initiate_discovery, शून्य,
			      XPC_DISCOVERY_THREAD_NAME);
	अगर (IS_ERR(kthपढ़ो)) अणु
		dev_err(xpc_part, "failed while forking discovery thread\n");

		/* mark this new thपढ़ो as a non-starter */
		complete(&xpc_discovery_निकासed);

		xpc_करो_निकास(xpUnloading);
		वापस -EBUSY;
	पूर्ण

	/* set the पूर्णांकerface to poपूर्णांक at XPC's functions */
	xpc_set_पूर्णांकerface(xpc_initiate_connect, xpc_initiate_disconnect,
			  xpc_initiate_send, xpc_initiate_send_notअगरy,
			  xpc_initiate_received, xpc_initiate_partid_to_nasids);

	वापस 0;

	/* initialization was not successful */
out_3:
	xpc_tearकरोwn_rsvd_page();

	(व्योम)unरेजिस्टर_die_notअगरier(&xpc_die_notअगरier);
	(व्योम)unरेजिस्टर_reboot_notअगरier(&xpc_reboot_notअगरier);
out_2:
	अगर (xpc_sysctl)
		unरेजिस्टर_sysctl_table(xpc_sysctl);

	xpc_tearकरोwn_partitions();
out_1:
	अगर (is_uv_प्रणाली())
		xpc_निकास_uv();
	वापस ret;
पूर्ण

module_init(xpc_init);

अटल व्योम __निकास
xpc_निकास(व्योम)
अणु
	xpc_करो_निकास(xpUnloading);
पूर्ण

module_निकास(xpc_निकास);

MODULE_AUTHOR("Silicon Graphics, Inc.");
MODULE_DESCRIPTION("Cross Partition Communication (XPC) support");
MODULE_LICENSE("GPL");

module_param(xpc_hb_पूर्णांकerval, पूर्णांक, 0);
MODULE_PARM_DESC(xpc_hb_पूर्णांकerval, "Number of seconds between "
		 "heartbeat increments.");

module_param(xpc_hb_check_पूर्णांकerval, पूर्णांक, 0);
MODULE_PARM_DESC(xpc_hb_check_पूर्णांकerval, "Number of seconds between "
		 "heartbeat checks.");

module_param(xpc_disengage_समयlimit, पूर्णांक, 0);
MODULE_PARM_DESC(xpc_disengage_समयlimit, "Number of seconds to wait "
		 "for disengage to complete.");

module_param(xpc_kdebug_ignore, पूर्णांक, 0);
MODULE_PARM_DESC(xpc_kdebug_ignore, "Should lack of heartbeat be ignored by "
		 "other partitions when dropping into kdebug.");
