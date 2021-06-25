<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2004-2009 Silicon Graphics, Inc.  All Rights Reserved.
 */

/*
 * Cross Partition Communication (XPC) channel support.
 *
 *	This is the part of XPC that manages the channels and
 *	sends/receives messages across them to/from other partitions.
 *
 */

#समावेश <linux/device.h>
#समावेश "xpc.h"

/*
 * Process a connect message from a remote partition.
 *
 * Note: xpc_process_connect() is expecting to be called with the
 * spin_lock_irqsave held and will leave it locked upon वापस.
 */
अटल व्योम
xpc_process_connect(काष्ठा xpc_channel *ch, अचिन्हित दीर्घ *irq_flags)
अणु
	क्रमागत xp_retval ret;

	lockdep_निश्चित_held(&ch->lock);

	अगर (!(ch->flags & XPC_C_OPENREQUEST) ||
	    !(ch->flags & XPC_C_ROPENREQUEST)) अणु
		/* nothing more to करो क्रम now */
		वापस;
	पूर्ण
	DBUG_ON(!(ch->flags & XPC_C_CONNECTING));

	अगर (!(ch->flags & XPC_C_SETUP)) अणु
		spin_unlock_irqrestore(&ch->lock, *irq_flags);
		ret = xpc_arch_ops.setup_msg_काष्ठाures(ch);
		spin_lock_irqsave(&ch->lock, *irq_flags);

		अगर (ret != xpSuccess)
			XPC_DISCONNECT_CHANNEL(ch, ret, irq_flags);
		अन्यथा
			ch->flags |= XPC_C_SETUP;

		अगर (ch->flags & XPC_C_DISCONNECTING)
			वापस;
	पूर्ण

	अगर (!(ch->flags & XPC_C_OPENREPLY)) अणु
		ch->flags |= XPC_C_OPENREPLY;
		xpc_arch_ops.send_chctl_खोलोreply(ch, irq_flags);
	पूर्ण

	अगर (!(ch->flags & XPC_C_ROPENREPLY))
		वापस;

	अगर (!(ch->flags & XPC_C_OPENCOMPLETE)) अणु
		ch->flags |= (XPC_C_OPENCOMPLETE | XPC_C_CONNECTED);
		xpc_arch_ops.send_chctl_खोलोcomplete(ch, irq_flags);
	पूर्ण

	अगर (!(ch->flags & XPC_C_ROPENCOMPLETE))
		वापस;

	dev_info(xpc_chan, "channel %d to partition %d connected\n",
		 ch->number, ch->partid);

	ch->flags = (XPC_C_CONNECTED | XPC_C_SETUP);	/* clear all अन्यथा */
पूर्ण

/*
 * spin_lock_irqsave() is expected to be held on entry.
 */
अटल व्योम
xpc_process_disconnect(काष्ठा xpc_channel *ch, अचिन्हित दीर्घ *irq_flags)
अणु
	काष्ठा xpc_partition *part = &xpc_partitions[ch->partid];
	u32 channel_was_connected = (ch->flags & XPC_C_WASCONNECTED);

	lockdep_निश्चित_held(&ch->lock);

	अगर (!(ch->flags & XPC_C_DISCONNECTING))
		वापस;

	DBUG_ON(!(ch->flags & XPC_C_CLOSEREQUEST));

	/* make sure all activity has settled करोwn first */

	अगर (atomic_पढ़ो(&ch->kthपढ़ोs_asचिन्हित) > 0 ||
	    atomic_पढ़ो(&ch->references) > 0) अणु
		वापस;
	पूर्ण
	DBUG_ON((ch->flags & XPC_C_CONNECTEDCALLOUT_MADE) &&
		!(ch->flags & XPC_C_DISCONNECTINGCALLOUT_MADE));

	अगर (part->act_state == XPC_P_AS_DEACTIVATING) अणु
		/* can't proceed until the other side disengages from us */
		अगर (xpc_arch_ops.partition_engaged(ch->partid))
			वापस;

	पूर्ण अन्यथा अणु

		/* as दीर्घ as the other side is up करो the full protocol */

		अगर (!(ch->flags & XPC_C_RCLOSEREQUEST))
			वापस;

		अगर (!(ch->flags & XPC_C_CLOSEREPLY)) अणु
			ch->flags |= XPC_C_CLOSEREPLY;
			xpc_arch_ops.send_chctl_बंदreply(ch, irq_flags);
		पूर्ण

		अगर (!(ch->flags & XPC_C_RCLOSEREPLY))
			वापस;
	पूर्ण

	/* wake those रुकोing क्रम notअगरy completion */
	अगर (atomic_पढ़ो(&ch->n_to_notअगरy) > 0) अणु
		/* we करो callout जबतक holding ch->lock, callout can't block */
		xpc_arch_ops.notअगरy_senders_of_disconnect(ch);
	पूर्ण

	/* both sides are disconnected now */

	अगर (ch->flags & XPC_C_DISCONNECTINGCALLOUT_MADE) अणु
		spin_unlock_irqrestore(&ch->lock, *irq_flags);
		xpc_disconnect_callout(ch, xpDisconnected);
		spin_lock_irqsave(&ch->lock, *irq_flags);
	पूर्ण

	DBUG_ON(atomic_पढ़ो(&ch->n_to_notअगरy) != 0);

	/* it's now safe to free the channel's message queues */
	xpc_arch_ops.tearकरोwn_msg_काष्ठाures(ch);

	ch->func = शून्य;
	ch->key = शून्य;
	ch->entry_size = 0;
	ch->local_nentries = 0;
	ch->remote_nentries = 0;
	ch->kthपढ़ोs_asचिन्हित_limit = 0;
	ch->kthपढ़ोs_idle_limit = 0;

	/*
	 * Mark the channel disconnected and clear all other flags, including
	 * XPC_C_SETUP (because of call to
	 * xpc_arch_ops.tearकरोwn_msg_काष्ठाures()) but not including
	 * XPC_C_WDISCONNECT (अगर it was set).
	 */
	ch->flags = (XPC_C_DISCONNECTED | (ch->flags & XPC_C_WDISCONNECT));

	atomic_dec(&part->nchannels_active);

	अगर (channel_was_connected) अणु
		dev_info(xpc_chan, "channel %d to partition %d disconnected, "
			 "reason=%d\n", ch->number, ch->partid, ch->reason);
	पूर्ण

	अगर (ch->flags & XPC_C_WDISCONNECT) अणु
		/* we won't lose the CPU since we're holding ch->lock */
		complete(&ch->wdisconnect_रुको);
	पूर्ण अन्यथा अगर (ch->delayed_chctl_flags) अणु
		अगर (part->act_state != XPC_P_AS_DEACTIVATING) अणु
			/* समय to take action on any delayed chctl flags */
			spin_lock(&part->chctl_lock);
			part->chctl.flags[ch->number] |=
			    ch->delayed_chctl_flags;
			spin_unlock(&part->chctl_lock);
		पूर्ण
		ch->delayed_chctl_flags = 0;
	पूर्ण
पूर्ण

/*
 * Process a change in the channel's remote connection state.
 */
अटल व्योम
xpc_process_खोलोबंद_chctl_flags(काष्ठा xpc_partition *part, पूर्णांक ch_number,
				  u8 chctl_flags)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा xpc_खोलोबंद_args *args =
	    &part->remote_खोलोबंद_args[ch_number];
	काष्ठा xpc_channel *ch = &part->channels[ch_number];
	क्रमागत xp_retval reason;
	क्रमागत xp_retval ret;
	पूर्णांक create_kthपढ़ो = 0;

	spin_lock_irqsave(&ch->lock, irq_flags);

again:

	अगर ((ch->flags & XPC_C_DISCONNECTED) &&
	    (ch->flags & XPC_C_WDISCONNECT)) अणु
		/*
		 * Delay processing chctl flags until thपढ़ो रुकोing disconnect
		 * has had a chance to see that the channel is disconnected.
		 */
		ch->delayed_chctl_flags |= chctl_flags;
		जाओ out;
	पूर्ण

	अगर (chctl_flags & XPC_CHCTL_CLOSEREQUEST) अणु

		dev_dbg(xpc_chan, "XPC_CHCTL_CLOSEREQUEST (reason=%d) received "
			"from partid=%d, channel=%d\n", args->reason,
			ch->partid, ch->number);

		/*
		 * If RCLOSEREQUEST is set, we're probably रुकोing क्रम
		 * RCLOSEREPLY. We should find it and a ROPENREQUEST packed
		 * with this RCLOSEREQUEST in the chctl_flags.
		 */

		अगर (ch->flags & XPC_C_RCLOSEREQUEST) अणु
			DBUG_ON(!(ch->flags & XPC_C_DISCONNECTING));
			DBUG_ON(!(ch->flags & XPC_C_CLOSEREQUEST));
			DBUG_ON(!(ch->flags & XPC_C_CLOSEREPLY));
			DBUG_ON(ch->flags & XPC_C_RCLOSEREPLY);

			DBUG_ON(!(chctl_flags & XPC_CHCTL_CLOSEREPLY));
			chctl_flags &= ~XPC_CHCTL_CLOSEREPLY;
			ch->flags |= XPC_C_RCLOSEREPLY;

			/* both sides have finished disconnecting */
			xpc_process_disconnect(ch, &irq_flags);
			DBUG_ON(!(ch->flags & XPC_C_DISCONNECTED));
			जाओ again;
		पूर्ण

		अगर (ch->flags & XPC_C_DISCONNECTED) अणु
			अगर (!(chctl_flags & XPC_CHCTL_OPENREQUEST)) अणु
				अगर (part->chctl.flags[ch_number] &
				    XPC_CHCTL_OPENREQUEST) अणु

					DBUG_ON(ch->delayed_chctl_flags != 0);
					spin_lock(&part->chctl_lock);
					part->chctl.flags[ch_number] |=
					    XPC_CHCTL_CLOSEREQUEST;
					spin_unlock(&part->chctl_lock);
				पूर्ण
				जाओ out;
			पूर्ण

			XPC_SET_REASON(ch, 0, 0);
			ch->flags &= ~XPC_C_DISCONNECTED;

			atomic_inc(&part->nchannels_active);
			ch->flags |= (XPC_C_CONNECTING | XPC_C_ROPENREQUEST);
		पूर्ण

		chctl_flags &= ~(XPC_CHCTL_OPENREQUEST | XPC_CHCTL_OPENREPLY |
		    XPC_CHCTL_OPENCOMPLETE);

		/*
		 * The meaningful CLOSEREQUEST connection state fields are:
		 *      reason = reason connection is to be बंदd
		 */

		ch->flags |= XPC_C_RCLOSEREQUEST;

		अगर (!(ch->flags & XPC_C_DISCONNECTING)) अणु
			reason = args->reason;
			अगर (reason <= xpSuccess || reason > xpUnknownReason)
				reason = xpUnknownReason;
			अन्यथा अगर (reason == xpUnरेजिस्टरing)
				reason = xpOtherUnरेजिस्टरing;

			XPC_DISCONNECT_CHANNEL(ch, reason, &irq_flags);

			DBUG_ON(chctl_flags & XPC_CHCTL_CLOSEREPLY);
			जाओ out;
		पूर्ण

		xpc_process_disconnect(ch, &irq_flags);
	पूर्ण

	अगर (chctl_flags & XPC_CHCTL_CLOSEREPLY) अणु

		dev_dbg(xpc_chan, "XPC_CHCTL_CLOSEREPLY received from partid="
			"%d, channel=%d\n", ch->partid, ch->number);

		अगर (ch->flags & XPC_C_DISCONNECTED) अणु
			DBUG_ON(part->act_state != XPC_P_AS_DEACTIVATING);
			जाओ out;
		पूर्ण

		DBUG_ON(!(ch->flags & XPC_C_CLOSEREQUEST));

		अगर (!(ch->flags & XPC_C_RCLOSEREQUEST)) अणु
			अगर (part->chctl.flags[ch_number] &
			    XPC_CHCTL_CLOSEREQUEST) अणु

				DBUG_ON(ch->delayed_chctl_flags != 0);
				spin_lock(&part->chctl_lock);
				part->chctl.flags[ch_number] |=
				    XPC_CHCTL_CLOSEREPLY;
				spin_unlock(&part->chctl_lock);
			पूर्ण
			जाओ out;
		पूर्ण

		ch->flags |= XPC_C_RCLOSEREPLY;

		अगर (ch->flags & XPC_C_CLOSEREPLY) अणु
			/* both sides have finished disconnecting */
			xpc_process_disconnect(ch, &irq_flags);
		पूर्ण
	पूर्ण

	अगर (chctl_flags & XPC_CHCTL_OPENREQUEST) अणु

		dev_dbg(xpc_chan, "XPC_CHCTL_OPENREQUEST (entry_size=%d, "
			"local_nentries=%d) received from partid=%d, "
			"channel=%d\n", args->entry_size, args->local_nentries,
			ch->partid, ch->number);

		अगर (part->act_state == XPC_P_AS_DEACTIVATING ||
		    (ch->flags & XPC_C_ROPENREQUEST)) अणु
			जाओ out;
		पूर्ण

		अगर (ch->flags & (XPC_C_DISCONNECTING | XPC_C_WDISCONNECT)) अणु
			ch->delayed_chctl_flags |= XPC_CHCTL_OPENREQUEST;
			जाओ out;
		पूर्ण
		DBUG_ON(!(ch->flags & (XPC_C_DISCONNECTED |
				       XPC_C_OPENREQUEST)));
		DBUG_ON(ch->flags & (XPC_C_ROPENREQUEST | XPC_C_ROPENREPLY |
				     XPC_C_OPENREPLY | XPC_C_CONNECTED));

		/*
		 * The meaningful OPENREQUEST connection state fields are:
		 *      entry_size = size of channel's messages in bytes
		 *      local_nentries = remote partition's local_nentries
		 */
		अगर (args->entry_size == 0 || args->local_nentries == 0) अणु
			/* assume OPENREQUEST was delayed by mistake */
			जाओ out;
		पूर्ण

		ch->flags |= (XPC_C_ROPENREQUEST | XPC_C_CONNECTING);
		ch->remote_nentries = args->local_nentries;

		अगर (ch->flags & XPC_C_OPENREQUEST) अणु
			अगर (args->entry_size != ch->entry_size) अणु
				XPC_DISCONNECT_CHANNEL(ch, xpUnequalMsgSizes,
						       &irq_flags);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			ch->entry_size = args->entry_size;

			XPC_SET_REASON(ch, 0, 0);
			ch->flags &= ~XPC_C_DISCONNECTED;

			atomic_inc(&part->nchannels_active);
		पूर्ण

		xpc_process_connect(ch, &irq_flags);
	पूर्ण

	अगर (chctl_flags & XPC_CHCTL_OPENREPLY) अणु

		dev_dbg(xpc_chan, "XPC_CHCTL_OPENREPLY (local_msgqueue_pa="
			"0x%lx, local_nentries=%d, remote_nentries=%d) "
			"received from partid=%d, channel=%d\n",
			args->local_msgqueue_pa, args->local_nentries,
			args->remote_nentries, ch->partid, ch->number);

		अगर (ch->flags & (XPC_C_DISCONNECTING | XPC_C_DISCONNECTED))
			जाओ out;

		अगर (!(ch->flags & XPC_C_OPENREQUEST)) अणु
			XPC_DISCONNECT_CHANNEL(ch, xpOpenCloseError,
					       &irq_flags);
			जाओ out;
		पूर्ण

		DBUG_ON(!(ch->flags & XPC_C_ROPENREQUEST));
		DBUG_ON(ch->flags & XPC_C_CONNECTED);

		/*
		 * The meaningful OPENREPLY connection state fields are:
		 *      local_msgqueue_pa = physical address of remote
		 *                          partition's local_msgqueue
		 *      local_nentries = remote partition's local_nentries
		 *      remote_nentries = remote partition's remote_nentries
		 */
		DBUG_ON(args->local_msgqueue_pa == 0);
		DBUG_ON(args->local_nentries == 0);
		DBUG_ON(args->remote_nentries == 0);

		ret = xpc_arch_ops.save_remote_msgqueue_pa(ch,
						      args->local_msgqueue_pa);
		अगर (ret != xpSuccess) अणु
			XPC_DISCONNECT_CHANNEL(ch, ret, &irq_flags);
			जाओ out;
		पूर्ण
		ch->flags |= XPC_C_ROPENREPLY;

		अगर (args->local_nentries < ch->remote_nentries) अणु
			dev_dbg(xpc_chan, "XPC_CHCTL_OPENREPLY: new "
				"remote_nentries=%d, old remote_nentries=%d, "
				"partid=%d, channel=%d\n",
				args->local_nentries, ch->remote_nentries,
				ch->partid, ch->number);

			ch->remote_nentries = args->local_nentries;
		पूर्ण
		अगर (args->remote_nentries < ch->local_nentries) अणु
			dev_dbg(xpc_chan, "XPC_CHCTL_OPENREPLY: new "
				"local_nentries=%d, old local_nentries=%d, "
				"partid=%d, channel=%d\n",
				args->remote_nentries, ch->local_nentries,
				ch->partid, ch->number);

			ch->local_nentries = args->remote_nentries;
		पूर्ण

		xpc_process_connect(ch, &irq_flags);
	पूर्ण

	अगर (chctl_flags & XPC_CHCTL_OPENCOMPLETE) अणु

		dev_dbg(xpc_chan, "XPC_CHCTL_OPENCOMPLETE received from "
			"partid=%d, channel=%d\n", ch->partid, ch->number);

		अगर (ch->flags & (XPC_C_DISCONNECTING | XPC_C_DISCONNECTED))
			जाओ out;

		अगर (!(ch->flags & XPC_C_OPENREQUEST) ||
		    !(ch->flags & XPC_C_OPENREPLY)) अणु
			XPC_DISCONNECT_CHANNEL(ch, xpOpenCloseError,
					       &irq_flags);
			जाओ out;
		पूर्ण

		DBUG_ON(!(ch->flags & XPC_C_ROPENREQUEST));
		DBUG_ON(!(ch->flags & XPC_C_ROPENREPLY));
		DBUG_ON(!(ch->flags & XPC_C_CONNECTED));

		ch->flags |= XPC_C_ROPENCOMPLETE;

		xpc_process_connect(ch, &irq_flags);
		create_kthपढ़ो = 1;
	पूर्ण

out:
	spin_unlock_irqrestore(&ch->lock, irq_flags);

	अगर (create_kthपढ़ो)
		xpc_create_kthपढ़ोs(ch, 1, 0);
पूर्ण

/*
 * Attempt to establish a channel connection to a remote partition.
 */
अटल क्रमागत xp_retval
xpc_connect_channel(काष्ठा xpc_channel *ch)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा xpc_registration *registration = &xpc_registrations[ch->number];

	अगर (mutex_trylock(&registration->mutex) == 0)
		वापस xpRetry;

	अगर (!XPC_CHANNEL_REGISTERED(ch->number)) अणु
		mutex_unlock(&registration->mutex);
		वापस xpUnरेजिस्टरed;
	पूर्ण

	spin_lock_irqsave(&ch->lock, irq_flags);

	DBUG_ON(ch->flags & XPC_C_CONNECTED);
	DBUG_ON(ch->flags & XPC_C_OPENREQUEST);

	अगर (ch->flags & XPC_C_DISCONNECTING) अणु
		spin_unlock_irqrestore(&ch->lock, irq_flags);
		mutex_unlock(&registration->mutex);
		वापस ch->reason;
	पूर्ण

	/* add info from the channel connect registration to the channel */

	ch->kthपढ़ोs_asचिन्हित_limit = registration->asचिन्हित_limit;
	ch->kthपढ़ोs_idle_limit = registration->idle_limit;
	DBUG_ON(atomic_पढ़ो(&ch->kthपढ़ोs_asचिन्हित) != 0);
	DBUG_ON(atomic_पढ़ो(&ch->kthपढ़ोs_idle) != 0);
	DBUG_ON(atomic_पढ़ो(&ch->kthपढ़ोs_active) != 0);

	ch->func = registration->func;
	DBUG_ON(registration->func == शून्य);
	ch->key = registration->key;

	ch->local_nentries = registration->nentries;

	अगर (ch->flags & XPC_C_ROPENREQUEST) अणु
		अगर (registration->entry_size != ch->entry_size) अणु
			/* the local and remote sides aren't the same */

			/*
			 * Because XPC_DISCONNECT_CHANNEL() can block we're
			 * क्रमced to up the registration sema beक्रमe we unlock
			 * the channel lock. But that's okay here because we're
			 * करोne with the part that required the registration
			 * sema. XPC_DISCONNECT_CHANNEL() requires that the
			 * channel lock be locked and will unlock and relock
			 * the channel lock as needed.
			 */
			mutex_unlock(&registration->mutex);
			XPC_DISCONNECT_CHANNEL(ch, xpUnequalMsgSizes,
					       &irq_flags);
			spin_unlock_irqrestore(&ch->lock, irq_flags);
			वापस xpUnequalMsgSizes;
		पूर्ण
	पूर्ण अन्यथा अणु
		ch->entry_size = registration->entry_size;

		XPC_SET_REASON(ch, 0, 0);
		ch->flags &= ~XPC_C_DISCONNECTED;

		atomic_inc(&xpc_partitions[ch->partid].nchannels_active);
	पूर्ण

	mutex_unlock(&registration->mutex);

	/* initiate the connection */

	ch->flags |= (XPC_C_OPENREQUEST | XPC_C_CONNECTING);
	xpc_arch_ops.send_chctl_खोलोrequest(ch, &irq_flags);

	xpc_process_connect(ch, &irq_flags);

	spin_unlock_irqrestore(&ch->lock, irq_flags);

	वापस xpSuccess;
पूर्ण

व्योम
xpc_process_sent_chctl_flags(काष्ठा xpc_partition *part)
अणु
	अचिन्हित दीर्घ irq_flags;
	जोड़ xpc_channel_ctl_flags chctl;
	काष्ठा xpc_channel *ch;
	पूर्णांक ch_number;
	u32 ch_flags;

	chctl.all_flags = xpc_arch_ops.get_chctl_all_flags(part);

	/*
	 * Initiate channel connections क्रम रेजिस्टरed channels.
	 *
	 * For each connected channel that has pending messages activate idle
	 * kthपढ़ोs and/or create new kthपढ़ोs as needed.
	 */

	क्रम (ch_number = 0; ch_number < part->nchannels; ch_number++) अणु
		ch = &part->channels[ch_number];

		/*
		 * Process any खोलो or बंद related chctl flags, and then deal
		 * with connecting or disconnecting the channel as required.
		 */

		अगर (chctl.flags[ch_number] & XPC_OPENCLOSE_CHCTL_FLAGS) अणु
			xpc_process_खोलोबंद_chctl_flags(part, ch_number,
							chctl.flags[ch_number]);
		पूर्ण

		ch_flags = ch->flags;	/* need an atomic snapshot of flags */

		अगर (ch_flags & XPC_C_DISCONNECTING) अणु
			spin_lock_irqsave(&ch->lock, irq_flags);
			xpc_process_disconnect(ch, &irq_flags);
			spin_unlock_irqrestore(&ch->lock, irq_flags);
			जारी;
		पूर्ण

		अगर (part->act_state == XPC_P_AS_DEACTIVATING)
			जारी;

		अगर (!(ch_flags & XPC_C_CONNECTED)) अणु
			अगर (!(ch_flags & XPC_C_OPENREQUEST)) अणु
				DBUG_ON(ch_flags & XPC_C_SETUP);
				(व्योम)xpc_connect_channel(ch);
			पूर्ण
			जारी;
		पूर्ण

		/*
		 * Process any message related chctl flags, this may involve
		 * the activation of kthपढ़ोs to deliver any pending messages
		 * sent from the other partition.
		 */

		अगर (chctl.flags[ch_number] & XPC_MSG_CHCTL_FLAGS)
			xpc_arch_ops.process_msg_chctl_flags(part, ch_number);
	पूर्ण
पूर्ण

/*
 * XPC's heartbeat code calls this function to inक्रमm XPC that a partition is
 * going करोwn.  XPC responds by tearing करोwn the XPartition Communication
 * infraकाष्ठाure used क्रम the just करोwned partition.
 *
 * XPC's heartbeat code will never call this function and xpc_partition_up()
 * at the same समय. Nor will it ever make multiple calls to either function
 * at the same समय.
 */
व्योम
xpc_partition_going_करोwn(काष्ठा xpc_partition *part, क्रमागत xp_retval reason)
अणु
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक ch_number;
	काष्ठा xpc_channel *ch;

	dev_dbg(xpc_chan, "deactivating partition %d, reason=%d\n",
		XPC_PARTID(part), reason);

	अगर (!xpc_part_ref(part)) अणु
		/* infraकाष्ठाure क्रम this partition isn't currently set up */
		वापस;
	पूर्ण

	/* disconnect channels associated with the partition going करोwn */

	क्रम (ch_number = 0; ch_number < part->nchannels; ch_number++) अणु
		ch = &part->channels[ch_number];

		xpc_msgqueue_ref(ch);
		spin_lock_irqsave(&ch->lock, irq_flags);

		XPC_DISCONNECT_CHANNEL(ch, reason, &irq_flags);

		spin_unlock_irqrestore(&ch->lock, irq_flags);
		xpc_msgqueue_deref(ch);
	पूर्ण

	xpc_wakeup_channel_mgr(part);

	xpc_part_deref(part);
पूर्ण

/*
 * Called by XP at the समय of channel connection registration to cause
 * XPC to establish connections to all currently active partitions.
 */
व्योम
xpc_initiate_connect(पूर्णांक ch_number)
अणु
	लघु partid;
	काष्ठा xpc_partition *part;

	DBUG_ON(ch_number < 0 || ch_number >= XPC_MAX_NCHANNELS);

	क्रम (partid = 0; partid < xp_max_npartitions; partid++) अणु
		part = &xpc_partitions[partid];

		अगर (xpc_part_ref(part)) अणु
			/*
			 * Initiate the establishment of a connection on the
			 * newly रेजिस्टरed channel to the remote partition.
			 */
			xpc_wakeup_channel_mgr(part);
			xpc_part_deref(part);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
xpc_connected_callout(काष्ठा xpc_channel *ch)
अणु
	/* let the रेजिस्टरer know that a connection has been established */

	अगर (ch->func != शून्य) अणु
		dev_dbg(xpc_chan, "ch->func() called, reason=xpConnected, "
			"partid=%d, channel=%d\n", ch->partid, ch->number);

		ch->func(xpConnected, ch->partid, ch->number,
			 (व्योम *)(u64)ch->local_nentries, ch->key);

		dev_dbg(xpc_chan, "ch->func() returned, reason=xpConnected, "
			"partid=%d, channel=%d\n", ch->partid, ch->number);
	पूर्ण
पूर्ण

/*
 * Called by XP at the समय of channel connection unregistration to cause
 * XPC to tearकरोwn all current connections क्रम the specअगरied channel.
 *
 * Beक्रमe वापसing xpc_initiate_disconnect() will रुको until all connections
 * on the specअगरied channel have been बंदd/tornकरोwn. So the caller can be
 * assured that they will not be receiving any more callouts from XPC to the
 * function they रेजिस्टरed via xpc_connect().
 *
 * Arguments:
 *
 *	ch_number - channel # to unरेजिस्टर.
 */
व्योम
xpc_initiate_disconnect(पूर्णांक ch_number)
अणु
	अचिन्हित दीर्घ irq_flags;
	लघु partid;
	काष्ठा xpc_partition *part;
	काष्ठा xpc_channel *ch;

	DBUG_ON(ch_number < 0 || ch_number >= XPC_MAX_NCHANNELS);

	/* initiate the channel disconnect क्रम every active partition */
	क्रम (partid = 0; partid < xp_max_npartitions; partid++) अणु
		part = &xpc_partitions[partid];

		अगर (xpc_part_ref(part)) अणु
			ch = &part->channels[ch_number];
			xpc_msgqueue_ref(ch);

			spin_lock_irqsave(&ch->lock, irq_flags);

			अगर (!(ch->flags & XPC_C_DISCONNECTED)) अणु
				ch->flags |= XPC_C_WDISCONNECT;

				XPC_DISCONNECT_CHANNEL(ch, xpUnरेजिस्टरing,
						       &irq_flags);
			पूर्ण

			spin_unlock_irqrestore(&ch->lock, irq_flags);

			xpc_msgqueue_deref(ch);
			xpc_part_deref(part);
		पूर्ण
	पूर्ण

	xpc_disconnect_रुको(ch_number);
पूर्ण

/*
 * To disconnect a channel, and reflect it back to all who may be रुकोing.
 *
 * An OPEN is not allowed until XPC_C_DISCONNECTING is cleared by
 * xpc_process_disconnect(), and अगर set, XPC_C_WDISCONNECT is cleared by
 * xpc_disconnect_रुको().
 *
 * THE CHANNEL IS TO BE LOCKED BY THE CALLER AND WILL REMAIN LOCKED UPON RETURN.
 */
व्योम
xpc_disconnect_channel(स्थिर पूर्णांक line, काष्ठा xpc_channel *ch,
		       क्रमागत xp_retval reason, अचिन्हित दीर्घ *irq_flags)
अणु
	u32 channel_was_connected = (ch->flags & XPC_C_CONNECTED);

	lockdep_निश्चित_held(&ch->lock);

	अगर (ch->flags & (XPC_C_DISCONNECTING | XPC_C_DISCONNECTED))
		वापस;

	DBUG_ON(!(ch->flags & (XPC_C_CONNECTING | XPC_C_CONNECTED)));

	dev_dbg(xpc_chan, "reason=%d, line=%d, partid=%d, channel=%d\n",
		reason, line, ch->partid, ch->number);

	XPC_SET_REASON(ch, reason, line);

	ch->flags |= (XPC_C_CLOSEREQUEST | XPC_C_DISCONNECTING);
	/* some of these may not have been set */
	ch->flags &= ~(XPC_C_OPENREQUEST | XPC_C_OPENREPLY |
		       XPC_C_ROPENREQUEST | XPC_C_ROPENREPLY |
		       XPC_C_CONNECTING | XPC_C_CONNECTED);

	xpc_arch_ops.send_chctl_बंदrequest(ch, irq_flags);

	अगर (channel_was_connected)
		ch->flags |= XPC_C_WASCONNECTED;

	spin_unlock_irqrestore(&ch->lock, *irq_flags);

	/* wake all idle kthपढ़ोs so they can निकास */
	अगर (atomic_पढ़ो(&ch->kthपढ़ोs_idle) > 0) अणु
		wake_up_all(&ch->idle_wq);

	पूर्ण अन्यथा अगर ((ch->flags & XPC_C_CONNECTEDCALLOUT_MADE) &&
		   !(ch->flags & XPC_C_DISCONNECTINGCALLOUT)) अणु
		/* start a kthपढ़ो that will करो the xpDisconnecting callout */
		xpc_create_kthपढ़ोs(ch, 1, 1);
	पूर्ण

	/* wake those रुकोing to allocate an entry from the local msg queue */
	अगर (atomic_पढ़ो(&ch->n_on_msg_allocate_wq) > 0)
		wake_up(&ch->msg_allocate_wq);

	spin_lock_irqsave(&ch->lock, *irq_flags);
पूर्ण

व्योम
xpc_disconnect_callout(काष्ठा xpc_channel *ch, क्रमागत xp_retval reason)
अणु
	/*
	 * Let the channel's रेजिस्टरer know that the channel is being
	 * disconnected. We करोn't want to करो this अगर the रेजिस्टरer was never
	 * inक्रमmed of a connection being made.
	 */

	अगर (ch->func != शून्य) अणु
		dev_dbg(xpc_chan, "ch->func() called, reason=%d, partid=%d, "
			"channel=%d\n", reason, ch->partid, ch->number);

		ch->func(reason, ch->partid, ch->number, शून्य, ch->key);

		dev_dbg(xpc_chan, "ch->func() returned, reason=%d, partid=%d, "
			"channel=%d\n", reason, ch->partid, ch->number);
	पूर्ण
पूर्ण

/*
 * Wait क्रम a message entry to become available क्रम the specअगरied channel,
 * but करोn't रुको any दीर्घer than 1 jअगरfy.
 */
क्रमागत xp_retval
xpc_allocate_msg_रुको(काष्ठा xpc_channel *ch)
अणु
	क्रमागत xp_retval ret;
	DEFINE_WAIT(रुको);

	अगर (ch->flags & XPC_C_DISCONNECTING) अणु
		DBUG_ON(ch->reason == xpInterrupted);
		वापस ch->reason;
	पूर्ण

	atomic_inc(&ch->n_on_msg_allocate_wq);
	prepare_to_रुको(&ch->msg_allocate_wq, &रुको, TASK_INTERRUPTIBLE);
	ret = schedule_समयout(1);
	finish_रुको(&ch->msg_allocate_wq, &रुको);
	atomic_dec(&ch->n_on_msg_allocate_wq);

	अगर (ch->flags & XPC_C_DISCONNECTING) अणु
		ret = ch->reason;
		DBUG_ON(ch->reason == xpInterrupted);
	पूर्ण अन्यथा अगर (ret == 0) अणु
		ret = xpTimeout;
	पूर्ण अन्यथा अणु
		ret = xpInterrupted;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Send a message that contains the user's payload on the specअगरied channel
 * connected to the specअगरied partition.
 *
 * NOTE that this routine can sleep रुकोing क्रम a message entry to become
 * available. To not sleep, pass in the XPC_NOWAIT flag.
 *
 * Once sent, this routine will not रुको क्रम the message to be received, nor
 * will notअगरication be given when it करोes happen.
 *
 * Arguments:
 *
 *	partid - ID of partition to which the channel is connected.
 *	ch_number - channel # to send message on.
 *	flags - see xp.h क्रम valid flags.
 *	payload - poपूर्णांकer to the payload which is to be sent.
 *	payload_size - size of the payload in bytes.
 */
क्रमागत xp_retval
xpc_initiate_send(लघु partid, पूर्णांक ch_number, u32 flags, व्योम *payload,
		  u16 payload_size)
अणु
	काष्ठा xpc_partition *part = &xpc_partitions[partid];
	क्रमागत xp_retval ret = xpUnknownReason;

	dev_dbg(xpc_chan, "payload=0x%p, partid=%d, channel=%d\n", payload,
		partid, ch_number);

	DBUG_ON(partid < 0 || partid >= xp_max_npartitions);
	DBUG_ON(ch_number < 0 || ch_number >= part->nchannels);
	DBUG_ON(payload == शून्य);

	अगर (xpc_part_ref(part)) अणु
		ret = xpc_arch_ops.send_payload(&part->channels[ch_number],
				  flags, payload, payload_size, 0, शून्य, शून्य);
		xpc_part_deref(part);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Send a message that contains the user's payload on the specअगरied channel
 * connected to the specअगरied partition.
 *
 * NOTE that this routine can sleep रुकोing क्रम a message entry to become
 * available. To not sleep, pass in the XPC_NOWAIT flag.
 *
 * This routine will not रुको क्रम the message to be sent or received.
 *
 * Once the remote end of the channel has received the message, the function
 * passed as an argument to xpc_initiate_send_notअगरy() will be called. This
 * allows the sender to मुक्त up or re-use any buffers referenced by the
 * message, but करोes NOT mean the message has been processed at the remote
 * end by a receiver.
 *
 * If this routine वापसs an error, the caller's function will NOT be called.
 *
 * Arguments:
 *
 *	partid - ID of partition to which the channel is connected.
 *	ch_number - channel # to send message on.
 *	flags - see xp.h क्रम valid flags.
 *	payload - poपूर्णांकer to the payload which is to be sent.
 *	payload_size - size of the payload in bytes.
 *	func - function to call with asynchronous notअगरication of message
 *		  receipt. THIS FUNCTION MUST BE NON-BLOCKING.
 *	key - user-defined key to be passed to the function when it's called.
 */
क्रमागत xp_retval
xpc_initiate_send_notअगरy(लघु partid, पूर्णांक ch_number, u32 flags, व्योम *payload,
			 u16 payload_size, xpc_notअगरy_func func, व्योम *key)
अणु
	काष्ठा xpc_partition *part = &xpc_partitions[partid];
	क्रमागत xp_retval ret = xpUnknownReason;

	dev_dbg(xpc_chan, "payload=0x%p, partid=%d, channel=%d\n", payload,
		partid, ch_number);

	DBUG_ON(partid < 0 || partid >= xp_max_npartitions);
	DBUG_ON(ch_number < 0 || ch_number >= part->nchannels);
	DBUG_ON(payload == शून्य);
	DBUG_ON(func == शून्य);

	अगर (xpc_part_ref(part)) अणु
		ret = xpc_arch_ops.send_payload(&part->channels[ch_number],
			  flags, payload, payload_size, XPC_N_CALL, func, key);
		xpc_part_deref(part);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Deliver a message's payload to its पूर्णांकended recipient.
 */
व्योम
xpc_deliver_payload(काष्ठा xpc_channel *ch)
अणु
	व्योम *payload;

	payload = xpc_arch_ops.get_deliverable_payload(ch);
	अगर (payload != शून्य) अणु

		/*
		 * This ref is taken to protect the payload itself from being
		 * मुक्तd beक्रमe the user is finished with it, which the user
		 * indicates by calling xpc_initiate_received().
		 */
		xpc_msgqueue_ref(ch);

		atomic_inc(&ch->kthपढ़ोs_active);

		अगर (ch->func != शून्य) अणु
			dev_dbg(xpc_chan, "ch->func() called, payload=0x%p "
				"partid=%d channel=%d\n", payload, ch->partid,
				ch->number);

			/* deliver the message to its पूर्णांकended recipient */
			ch->func(xpMsgReceived, ch->partid, ch->number, payload,
				 ch->key);

			dev_dbg(xpc_chan, "ch->func() returned, payload=0x%p "
				"partid=%d channel=%d\n", payload, ch->partid,
				ch->number);
		पूर्ण

		atomic_dec(&ch->kthपढ़ोs_active);
	पूर्ण
पूर्ण

/*
 * Acknowledge receipt of a delivered message's payload.
 *
 * This function, although called by users, करोes not call xpc_part_ref() to
 * ensure that the partition infraकाष्ठाure is in place. It relies on the
 * fact that we called xpc_msgqueue_ref() in xpc_deliver_payload().
 *
 * Arguments:
 *
 *	partid - ID of partition to which the channel is connected.
 *	ch_number - channel # message received on.
 *	payload - poपूर्णांकer to the payload area allocated via
 *			xpc_initiate_send() or xpc_initiate_send_notअगरy().
 */
व्योम
xpc_initiate_received(लघु partid, पूर्णांक ch_number, व्योम *payload)
अणु
	काष्ठा xpc_partition *part = &xpc_partitions[partid];
	काष्ठा xpc_channel *ch;

	DBUG_ON(partid < 0 || partid >= xp_max_npartitions);
	DBUG_ON(ch_number < 0 || ch_number >= part->nchannels);

	ch = &part->channels[ch_number];
	xpc_arch_ops.received_payload(ch, payload);

	/* the call to xpc_msgqueue_ref() was करोne by xpc_deliver_payload()  */
	xpc_msgqueue_deref(ch);
पूर्ण
