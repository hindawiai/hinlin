<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cec-adap.c - HDMI Consumer Electronics Control framework - CEC adapter
 *
 * Copyright 2016 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_file.h>

#समावेश "cec-priv.h"

अटल व्योम cec_fill_msg_report_features(काष्ठा cec_adapter *adap,
					 काष्ठा cec_msg *msg,
					 अचिन्हित पूर्णांक la_idx);

/*
 * 400 ms is the समय it takes क्रम one 16 byte message to be
 * transferred and 5 is the maximum number of retries. Add
 * another 100 ms as a margin. So अगर the transmit करोesn't
 * finish beक्रमe that समय something is really wrong and we
 * have to समय out.
 *
 * This is a sign that something it really wrong and a warning
 * will be issued.
 */
#घोषणा CEC_XFER_TIMEOUT_MS (5 * 400 + 100)

#घोषणा call_op(adap, op, arg...) \
	(adap->ops->op ? adap->ops->op(adap, ## arg) : 0)

#घोषणा call_व्योम_op(adap, op, arg...)			\
	करो अणु						\
		अगर (adap->ops->op)			\
			adap->ops->op(adap, ## arg);	\
	पूर्ण जबतक (0)

अटल पूर्णांक cec_log_addr2idx(स्थिर काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adap->log_addrs.num_log_addrs; i++)
		अगर (adap->log_addrs.log_addr[i] == log_addr)
			वापस i;
	वापस -1;
पूर्ण

अटल अचिन्हित पूर्णांक cec_log_addr2dev(स्थिर काष्ठा cec_adapter *adap, u8 log_addr)
अणु
	पूर्णांक i = cec_log_addr2idx(adap, log_addr);

	वापस adap->log_addrs.primary_device_type[i < 0 ? 0 : i];
पूर्ण

u16 cec_get_edid_phys_addr(स्थिर u8 *edid, अचिन्हित पूर्णांक size,
			   अचिन्हित पूर्णांक *offset)
अणु
	अचिन्हित पूर्णांक loc = cec_get_edid_spa_location(edid, size);

	अगर (offset)
		*offset = loc;
	अगर (loc == 0)
		वापस CEC_PHYS_ADDR_INVALID;
	वापस (edid[loc] << 8) | edid[loc + 1];
पूर्ण
EXPORT_SYMBOL_GPL(cec_get_edid_phys_addr);

व्योम cec_fill_conn_info_from_drm(काष्ठा cec_connector_info *conn_info,
				 स्थिर काष्ठा drm_connector *connector)
अणु
	स_रखो(conn_info, 0, माप(*conn_info));
	conn_info->type = CEC_CONNECTOR_TYPE_DRM;
	conn_info->drm.card_no = connector->dev->primary->index;
	conn_info->drm.connector_id = connector->base.id;
पूर्ण
EXPORT_SYMBOL_GPL(cec_fill_conn_info_from_drm);

/*
 * Queue a new event क्रम this filehandle. If ts == 0, then set it
 * to the current समय.
 *
 * We keep a queue of at most max_event events where max_event dअगरfers
 * per event. If the queue becomes full, then drop the oldest event and
 * keep track of how many events we've dropped.
 */
व्योम cec_queue_event_fh(काष्ठा cec_fh *fh,
			स्थिर काष्ठा cec_event *new_ev, u64 ts)
अणु
	अटल स्थिर u16 max_events[CEC_NUM_EVENTS] = अणु
		1, 1, 800, 800, 8, 8, 8, 8
	पूर्ण;
	काष्ठा cec_event_entry *entry;
	अचिन्हित पूर्णांक ev_idx = new_ev->event - 1;

	अगर (WARN_ON(ev_idx >= ARRAY_SIZE(fh->events)))
		वापस;

	अगर (ts == 0)
		ts = kसमय_get_ns();

	mutex_lock(&fh->lock);
	अगर (ev_idx < CEC_NUM_CORE_EVENTS)
		entry = &fh->core_events[ev_idx];
	अन्यथा
		entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (entry) अणु
		अगर (new_ev->event == CEC_EVENT_LOST_MSGS &&
		    fh->queued_events[ev_idx]) अणु
			entry->ev.lost_msgs.lost_msgs +=
				new_ev->lost_msgs.lost_msgs;
			जाओ unlock;
		पूर्ण
		entry->ev = *new_ev;
		entry->ev.ts = ts;

		अगर (fh->queued_events[ev_idx] < max_events[ev_idx]) अणु
			/* Add new msg at the end of the queue */
			list_add_tail(&entry->list, &fh->events[ev_idx]);
			fh->queued_events[ev_idx]++;
			fh->total_queued_events++;
			जाओ unlock;
		पूर्ण

		अगर (ev_idx >= CEC_NUM_CORE_EVENTS) अणु
			list_add_tail(&entry->list, &fh->events[ev_idx]);
			/* drop the oldest event */
			entry = list_first_entry(&fh->events[ev_idx],
						 काष्ठा cec_event_entry, list);
			list_del(&entry->list);
			kमुक्त(entry);
		पूर्ण
	पूर्ण
	/* Mark that events were lost */
	entry = list_first_entry_or_null(&fh->events[ev_idx],
					 काष्ठा cec_event_entry, list);
	अगर (entry)
		entry->ev.flags |= CEC_EVENT_FL_DROPPED_EVENTS;

unlock:
	mutex_unlock(&fh->lock);
	wake_up_पूर्णांकerruptible(&fh->रुको);
पूर्ण

/* Queue a new event क्रम all खोलो filehandles. */
अटल व्योम cec_queue_event(काष्ठा cec_adapter *adap,
			    स्थिर काष्ठा cec_event *ev)
अणु
	u64 ts = kसमय_get_ns();
	काष्ठा cec_fh *fh;

	mutex_lock(&adap->devnode.lock);
	list_क्रम_each_entry(fh, &adap->devnode.fhs, list)
		cec_queue_event_fh(fh, ev, ts);
	mutex_unlock(&adap->devnode.lock);
पूर्ण

/* Notअगरy userspace that the CEC pin changed state at the given समय. */
व्योम cec_queue_pin_cec_event(काष्ठा cec_adapter *adap, bool is_high,
			     bool dropped_events, kसमय_प्रकार ts)
अणु
	काष्ठा cec_event ev = अणु
		.event = is_high ? CEC_EVENT_PIN_CEC_HIGH :
				   CEC_EVENT_PIN_CEC_LOW,
		.flags = dropped_events ? CEC_EVENT_FL_DROPPED_EVENTS : 0,
	पूर्ण;
	काष्ठा cec_fh *fh;

	mutex_lock(&adap->devnode.lock);
	list_क्रम_each_entry(fh, &adap->devnode.fhs, list)
		अगर (fh->mode_follower == CEC_MODE_MONITOR_PIN)
			cec_queue_event_fh(fh, &ev, kसमय_प्रकारo_ns(ts));
	mutex_unlock(&adap->devnode.lock);
पूर्ण
EXPORT_SYMBOL_GPL(cec_queue_pin_cec_event);

/* Notअगरy userspace that the HPD pin changed state at the given समय. */
व्योम cec_queue_pin_hpd_event(काष्ठा cec_adapter *adap, bool is_high, kसमय_प्रकार ts)
अणु
	काष्ठा cec_event ev = अणु
		.event = is_high ? CEC_EVENT_PIN_HPD_HIGH :
				   CEC_EVENT_PIN_HPD_LOW,
	पूर्ण;
	काष्ठा cec_fh *fh;

	mutex_lock(&adap->devnode.lock);
	list_क्रम_each_entry(fh, &adap->devnode.fhs, list)
		cec_queue_event_fh(fh, &ev, kसमय_प्रकारo_ns(ts));
	mutex_unlock(&adap->devnode.lock);
पूर्ण
EXPORT_SYMBOL_GPL(cec_queue_pin_hpd_event);

/* Notअगरy userspace that the 5V pin changed state at the given समय. */
व्योम cec_queue_pin_5v_event(काष्ठा cec_adapter *adap, bool is_high, kसमय_प्रकार ts)
अणु
	काष्ठा cec_event ev = अणु
		.event = is_high ? CEC_EVENT_PIN_5V_HIGH :
				   CEC_EVENT_PIN_5V_LOW,
	पूर्ण;
	काष्ठा cec_fh *fh;

	mutex_lock(&adap->devnode.lock);
	list_क्रम_each_entry(fh, &adap->devnode.fhs, list)
		cec_queue_event_fh(fh, &ev, kसमय_प्रकारo_ns(ts));
	mutex_unlock(&adap->devnode.lock);
पूर्ण
EXPORT_SYMBOL_GPL(cec_queue_pin_5v_event);

/*
 * Queue a new message क्रम this filehandle.
 *
 * We keep a queue of at most CEC_MAX_MSG_RX_QUEUE_SZ messages. If the
 * queue becomes full, then drop the oldest message and keep track
 * of how many messages we've dropped.
 */
अटल व्योम cec_queue_msg_fh(काष्ठा cec_fh *fh, स्थिर काष्ठा cec_msg *msg)
अणु
	अटल स्थिर काष्ठा cec_event ev_lost_msgs = अणु
		.event = CEC_EVENT_LOST_MSGS,
		.flags = 0,
		अणु
			.lost_msgs = अणु 1 पूर्ण,
		पूर्ण,
	पूर्ण;
	काष्ठा cec_msg_entry *entry;

	mutex_lock(&fh->lock);
	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (entry) अणु
		entry->msg = *msg;
		/* Add new msg at the end of the queue */
		list_add_tail(&entry->list, &fh->msgs);

		अगर (fh->queued_msgs < CEC_MAX_MSG_RX_QUEUE_SZ) अणु
			/* All is fine अगर there is enough room */
			fh->queued_msgs++;
			mutex_unlock(&fh->lock);
			wake_up_पूर्णांकerruptible(&fh->रुको);
			वापस;
		पूर्ण

		/*
		 * अगर the message queue is full, then drop the oldest one and
		 * send a lost message event.
		 */
		entry = list_first_entry(&fh->msgs, काष्ठा cec_msg_entry, list);
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&fh->lock);

	/*
	 * We lost a message, either because kदो_स्मृति failed or the queue
	 * was full.
	 */
	cec_queue_event_fh(fh, &ev_lost_msgs, kसमय_get_ns());
पूर्ण

/*
 * Queue the message क्रम those filehandles that are in monitor mode.
 * If valid_la is true (this message is क्रम us or was sent by us),
 * then pass it on to any monitoring filehandle. If this message
 * isn't क्रम us or from us, then only give it to filehandles that
 * are in MONITOR_ALL mode.
 *
 * This can only happen अगर the CEC_CAP_MONITOR_ALL capability is
 * set and the CEC adapter was placed in 'monitor all' mode.
 */
अटल व्योम cec_queue_msg_monitor(काष्ठा cec_adapter *adap,
				  स्थिर काष्ठा cec_msg *msg,
				  bool valid_la)
अणु
	काष्ठा cec_fh *fh;
	u32 monitor_mode = valid_la ? CEC_MODE_MONITOR :
				      CEC_MODE_MONITOR_ALL;

	mutex_lock(&adap->devnode.lock);
	list_क्रम_each_entry(fh, &adap->devnode.fhs, list) अणु
		अगर (fh->mode_follower >= monitor_mode)
			cec_queue_msg_fh(fh, msg);
	पूर्ण
	mutex_unlock(&adap->devnode.lock);
पूर्ण

/*
 * Queue the message क्रम follower filehandles.
 */
अटल व्योम cec_queue_msg_followers(काष्ठा cec_adapter *adap,
				    स्थिर काष्ठा cec_msg *msg)
अणु
	काष्ठा cec_fh *fh;

	mutex_lock(&adap->devnode.lock);
	list_क्रम_each_entry(fh, &adap->devnode.fhs, list) अणु
		अगर (fh->mode_follower == CEC_MODE_FOLLOWER)
			cec_queue_msg_fh(fh, msg);
	पूर्ण
	mutex_unlock(&adap->devnode.lock);
पूर्ण

/* Notअगरy userspace of an adapter state change. */
अटल व्योम cec_post_state_event(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_event ev = अणु
		.event = CEC_EVENT_STATE_CHANGE,
	पूर्ण;

	ev.state_change.phys_addr = adap->phys_addr;
	ev.state_change.log_addr_mask = adap->log_addrs.log_addr_mask;
	ev.state_change.have_conn_info =
		adap->conn_info.type != CEC_CONNECTOR_TYPE_NO_CONNECTOR;
	cec_queue_event(adap, &ev);
पूर्ण

/*
 * A CEC transmit (and a possible रुको क्रम reply) completed.
 * If this was in blocking mode, then complete it, otherwise
 * queue the message क्रम userspace to dequeue later.
 *
 * This function is called with adap->lock held.
 */
अटल व्योम cec_data_completed(काष्ठा cec_data *data)
अणु
	/*
	 * Delete this transmit from the filehandle's xfer_list since
	 * we're करोne with it.
	 *
	 * Note that अगर the filehandle is बंदd beक्रमe this transmit
	 * finished, then the release() function will set data->fh to शून्य.
	 * Without that we would be referring to a बंदd filehandle.
	 */
	अगर (data->fh)
		list_del(&data->xfer_list);

	अगर (data->blocking) अणु
		/*
		 * Someone is blocking so mark the message as completed
		 * and call complete.
		 */
		data->completed = true;
		complete(&data->c);
	पूर्ण अन्यथा अणु
		/*
		 * No blocking, so just queue the message अगर needed and
		 * मुक्त the memory.
		 */
		अगर (data->fh)
			cec_queue_msg_fh(data->fh, &data->msg);
		kमुक्त(data);
	पूर्ण
पूर्ण

/*
 * A pending CEC transmit needs to be cancelled, either because the CEC
 * adapter is disabled or the transmit takes an impossibly दीर्घ समय to
 * finish.
 *
 * This function is called with adap->lock held.
 */
अटल व्योम cec_data_cancel(काष्ठा cec_data *data, u8 tx_status)
अणु
	/*
	 * It's either the current transmit, or it is a pending
	 * transmit. Take the appropriate action to clear it.
	 */
	अगर (data->adap->transmitting == data) अणु
		data->adap->transmitting = शून्य;
	पूर्ण अन्यथा अणु
		list_del_init(&data->list);
		अगर (!(data->msg.tx_status & CEC_TX_STATUS_OK))
			अगर (!WARN_ON(!data->adap->transmit_queue_sz))
				data->adap->transmit_queue_sz--;
	पूर्ण

	अगर (data->msg.tx_status & CEC_TX_STATUS_OK) अणु
		data->msg.rx_ts = kसमय_get_ns();
		data->msg.rx_status = CEC_RX_STATUS_ABORTED;
	पूर्ण अन्यथा अणु
		data->msg.tx_ts = kसमय_get_ns();
		data->msg.tx_status |= tx_status |
				       CEC_TX_STATUS_MAX_RETRIES;
		data->msg.tx_error_cnt++;
		data->attempts = 0;
	पूर्ण

	/* Queue transmitted message क्रम monitoring purposes */
	cec_queue_msg_monitor(data->adap, &data->msg, 1);

	cec_data_completed(data);
पूर्ण

/*
 * Flush all pending transmits and cancel any pending समयout work.
 *
 * This function is called with adap->lock held.
 */
अटल व्योम cec_flush(काष्ठा cec_adapter *adap)
अणु
	काष्ठा cec_data *data, *n;

	/*
	 * If the adapter is disabled, or we're asked to stop,
	 * then cancel any pending transmits.
	 */
	जबतक (!list_empty(&adap->transmit_queue)) अणु
		data = list_first_entry(&adap->transmit_queue,
					काष्ठा cec_data, list);
		cec_data_cancel(data, CEC_TX_STATUS_ABORTED);
	पूर्ण
	अगर (adap->transmitting)
		cec_data_cancel(adap->transmitting, CEC_TX_STATUS_ABORTED);

	/* Cancel the pending समयout work. */
	list_क्रम_each_entry_safe(data, n, &adap->रुको_queue, list) अणु
		अगर (cancel_delayed_work(&data->work))
			cec_data_cancel(data, CEC_TX_STATUS_OK);
		/*
		 * If cancel_delayed_work वापसed false, then
		 * the cec_रुको_समयout function is running,
		 * which will call cec_data_completed. So no
		 * need to करो anything special in that हाल.
		 */
	पूर्ण
	/*
	 * If something went wrong and this counter isn't what it should
	 * be, then this will reset it back to 0. Warn अगर it is not 0,
	 * since it indicates a bug, either in this framework or in a
	 * CEC driver.
	 */
	अगर (WARN_ON(adap->transmit_queue_sz))
		adap->transmit_queue_sz = 0;
पूर्ण

/*
 * Main CEC state machine
 *
 * Wait until the thपढ़ो should be stopped, or we are not transmitting and
 * a new transmit message is queued up, in which हाल we start transmitting
 * that message. When the adapter finished transmitting the message it will
 * call cec_transmit_करोne().
 *
 * If the adapter is disabled, then हटाओ all queued messages instead.
 *
 * If the current transmit बार out, then cancel that transmit.
 */
पूर्णांक cec_thपढ़ो_func(व्योम *_adap)
अणु
	काष्ठा cec_adapter *adap = _adap;

	क्रम (;;) अणु
		अचिन्हित पूर्णांक संकेत_मुक्त_समय;
		काष्ठा cec_data *data;
		bool समयout = false;
		u8 attempts;

		अगर (adap->transmit_in_progress) अणु
			पूर्णांक err;

			/*
			 * We are transmitting a message, so add a समयout
			 * to prevent the state machine to get stuck रुकोing
			 * क्रम this message to finalize and add a check to
			 * see अगर the adapter is disabled in which हाल the
			 * transmit should be canceled.
			 */
			err = रुको_event_पूर्णांकerruptible_समयout(adap->kthपढ़ो_रुकोq,
				(adap->needs_hpd &&
				 (!adap->is_configured && !adap->is_configuring)) ||
				kthपढ़ो_should_stop() ||
				(!adap->transmit_in_progress &&
				 !list_empty(&adap->transmit_queue)),
				msecs_to_jअगरfies(CEC_XFER_TIMEOUT_MS));
			समयout = err == 0;
		पूर्ण अन्यथा अणु
			/* Otherwise we just रुको क्रम something to happen. */
			रुको_event_पूर्णांकerruptible(adap->kthपढ़ो_रुकोq,
				kthपढ़ो_should_stop() ||
				(!adap->transmit_in_progress &&
				 !list_empty(&adap->transmit_queue)));
		पूर्ण

		mutex_lock(&adap->lock);

		अगर ((adap->needs_hpd &&
		     (!adap->is_configured && !adap->is_configuring)) ||
		    kthपढ़ो_should_stop()) अणु
			cec_flush(adap);
			जाओ unlock;
		पूर्ण

		अगर (adap->transmit_in_progress && समयout) अणु
			/*
			 * If we समयout, then log that. Normally this करोes
			 * not happen and it is an indication of a faulty CEC
			 * adapter driver, or the CEC bus is in some weird
			 * state. On rare occasions it can happen अगर there is
			 * so much traffic on the bus that the adapter was
			 * unable to transmit क्रम CEC_XFER_TIMEOUT_MS (2.1s).
			 */
			अगर (adap->transmitting) अणु
				pr_warn("cec-%s: message %*ph timed out\n", adap->name,
					adap->transmitting->msg.len,
					adap->transmitting->msg.msg);
				/* Just give up on this. */
				cec_data_cancel(adap->transmitting,
						CEC_TX_STATUS_TIMEOUT);
			पूर्ण अन्यथा अणु
				pr_warn("cec-%s: transmit timed out\n", adap->name);
			पूर्ण
			adap->transmit_in_progress = false;
			adap->tx_समयouts++;
			जाओ unlock;
		पूर्ण

		/*
		 * If we are still transmitting, or there is nothing new to
		 * transmit, then just जारी रुकोing.
		 */
		अगर (adap->transmit_in_progress || list_empty(&adap->transmit_queue))
			जाओ unlock;

		/* Get a new message to transmit */
		data = list_first_entry(&adap->transmit_queue,
					काष्ठा cec_data, list);
		list_del_init(&data->list);
		अगर (!WARN_ON(!data->adap->transmit_queue_sz))
			adap->transmit_queue_sz--;

		/* Make this the current transmitting message */
		adap->transmitting = data;

		/*
		 * Suggested number of attempts as per the CEC 2.0 spec:
		 * 4 attempts is the शेष, except क्रम 'secondary poll
		 * messages', i.e. poll messages not sent during the adapter
		 * configuration phase when it allocates logical addresses.
		 */
		अगर (data->msg.len == 1 && adap->is_configured)
			attempts = 2;
		अन्यथा
			attempts = 4;

		/* Set the suggested संकेत मुक्त समय */
		अगर (data->attempts) अणु
			/* should be >= 3 data bit periods क्रम a retry */
			संकेत_मुक्त_समय = CEC_SIGNAL_FREE_TIME_RETRY;
		पूर्ण अन्यथा अगर (adap->last_initiator !=
			   cec_msg_initiator(&data->msg)) अणु
			/* should be >= 5 data bit periods क्रम new initiator */
			संकेत_मुक्त_समय = CEC_SIGNAL_FREE_TIME_NEW_INITIATOR;
			adap->last_initiator = cec_msg_initiator(&data->msg);
		पूर्ण अन्यथा अणु
			/*
			 * should be >= 7 data bit periods क्रम sending another
			 * frame immediately after another.
			 */
			संकेत_मुक्त_समय = CEC_SIGNAL_FREE_TIME_NEXT_XFER;
		पूर्ण
		अगर (data->attempts == 0)
			data->attempts = attempts;

		/* Tell the adapter to transmit, cancel on error */
		अगर (adap->ops->adap_transmit(adap, data->attempts,
					     संकेत_मुक्त_समय, &data->msg))
			cec_data_cancel(data, CEC_TX_STATUS_ABORTED);
		अन्यथा
			adap->transmit_in_progress = true;

unlock:
		mutex_unlock(&adap->lock);

		अगर (kthपढ़ो_should_stop())
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Called by the CEC adapter अगर a transmit finished.
 */
व्योम cec_transmit_करोne_ts(काष्ठा cec_adapter *adap, u8 status,
			  u8 arb_lost_cnt, u8 nack_cnt, u8 low_drive_cnt,
			  u8 error_cnt, kसमय_प्रकार ts)
अणु
	काष्ठा cec_data *data;
	काष्ठा cec_msg *msg;
	अचिन्हित पूर्णांक attempts_made = arb_lost_cnt + nack_cnt +
				     low_drive_cnt + error_cnt;

	dprपूर्णांकk(2, "%s: status 0x%02x\n", __func__, status);
	अगर (attempts_made < 1)
		attempts_made = 1;

	mutex_lock(&adap->lock);
	data = adap->transmitting;
	अगर (!data) अणु
		/*
		 * This might happen अगर a transmit was issued and the cable is
		 * unplugged जबतक the transmit is ongoing. Ignore this
		 * transmit in that हाल.
		 */
		अगर (!adap->transmit_in_progress)
			dprपूर्णांकk(1, "%s was called without an ongoing transmit!\n",
				__func__);
		adap->transmit_in_progress = false;
		जाओ wake_thपढ़ो;
	पूर्ण
	adap->transmit_in_progress = false;

	msg = &data->msg;

	/* Drivers must fill in the status! */
	WARN_ON(status == 0);
	msg->tx_ts = kसमय_प्रकारo_ns(ts);
	msg->tx_status |= status;
	msg->tx_arb_lost_cnt += arb_lost_cnt;
	msg->tx_nack_cnt += nack_cnt;
	msg->tx_low_drive_cnt += low_drive_cnt;
	msg->tx_error_cnt += error_cnt;

	/* Mark that we're करोne with this transmit */
	adap->transmitting = शून्य;

	/*
	 * If there are still retry attempts left and there was an error and
	 * the hardware didn't संकेत that it retried itself (by setting
	 * CEC_TX_STATUS_MAX_RETRIES), then we will retry ourselves.
	 */
	अगर (data->attempts > attempts_made &&
	    !(status & (CEC_TX_STATUS_MAX_RETRIES | CEC_TX_STATUS_OK))) अणु
		/* Retry this message */
		data->attempts -= attempts_made;
		अगर (msg->समयout)
			dprपूर्णांकk(2, "retransmit: %*ph (attempts: %d, wait for 0x%02x)\n",
				msg->len, msg->msg, data->attempts, msg->reply);
		अन्यथा
			dprपूर्णांकk(2, "retransmit: %*ph (attempts: %d)\n",
				msg->len, msg->msg, data->attempts);
		/* Add the message in front of the transmit queue */
		list_add(&data->list, &adap->transmit_queue);
		adap->transmit_queue_sz++;
		जाओ wake_thपढ़ो;
	पूर्ण

	data->attempts = 0;

	/* Always set CEC_TX_STATUS_MAX_RETRIES on error */
	अगर (!(status & CEC_TX_STATUS_OK))
		msg->tx_status |= CEC_TX_STATUS_MAX_RETRIES;

	/* Queue transmitted message क्रम monitoring purposes */
	cec_queue_msg_monitor(adap, msg, 1);

	अगर ((status & CEC_TX_STATUS_OK) && adap->is_configured &&
	    msg->समयout) अणु
		/*
		 * Queue the message पूर्णांकo the रुको queue अगर we want to रुको
		 * क्रम a reply.
		 */
		list_add_tail(&data->list, &adap->रुको_queue);
		schedule_delayed_work(&data->work,
				      msecs_to_jअगरfies(msg->समयout));
	पूर्ण अन्यथा अणु
		/* Otherwise we're करोne */
		cec_data_completed(data);
	पूर्ण

wake_thपढ़ो:
	/*
	 * Wake up the मुख्य thपढ़ो to see अगर another message is पढ़ोy
	 * क्रम transmitting or to retry the current message.
	 */
	wake_up_पूर्णांकerruptible(&adap->kthपढ़ो_रुकोq);
	mutex_unlock(&adap->lock);
पूर्ण
EXPORT_SYMBOL_GPL(cec_transmit_करोne_ts);

व्योम cec_transmit_attempt_करोne_ts(काष्ठा cec_adapter *adap,
				  u8 status, kसमय_प्रकार ts)
अणु
	चयन (status & ~CEC_TX_STATUS_MAX_RETRIES) अणु
	हाल CEC_TX_STATUS_OK:
		cec_transmit_करोne_ts(adap, status, 0, 0, 0, 0, ts);
		वापस;
	हाल CEC_TX_STATUS_ARB_LOST:
		cec_transmit_करोne_ts(adap, status, 1, 0, 0, 0, ts);
		वापस;
	हाल CEC_TX_STATUS_NACK:
		cec_transmit_करोne_ts(adap, status, 0, 1, 0, 0, ts);
		वापस;
	हाल CEC_TX_STATUS_LOW_DRIVE:
		cec_transmit_करोne_ts(adap, status, 0, 0, 1, 0, ts);
		वापस;
	हाल CEC_TX_STATUS_ERROR:
		cec_transmit_करोne_ts(adap, status, 0, 0, 0, 1, ts);
		वापस;
	शेष:
		/* Should never happen */
		WARN(1, "cec-%s: invalid status 0x%02x\n", adap->name, status);
		वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cec_transmit_attempt_करोne_ts);

/*
 * Called when रुकोing क्रम a reply बार out.
 */
अटल व्योम cec_रुको_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cec_data *data = container_of(work, काष्ठा cec_data, work.work);
	काष्ठा cec_adapter *adap = data->adap;

	mutex_lock(&adap->lock);
	/*
	 * Sanity check in हाल the समयout and the arrival of the message
	 * happened at the same समय.
	 */
	अगर (list_empty(&data->list))
		जाओ unlock;

	/* Mark the message as समयd out */
	list_del_init(&data->list);
	data->msg.rx_ts = kसमय_get_ns();
	data->msg.rx_status = CEC_RX_STATUS_TIMEOUT;
	cec_data_completed(data);
unlock:
	mutex_unlock(&adap->lock);
पूर्ण

/*
 * Transmit a message. The fh argument may be शून्य अगर the transmit is not
 * associated with a specअगरic filehandle.
 *
 * This function is called with adap->lock held.
 */
पूर्णांक cec_transmit_msg_fh(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg,
			काष्ठा cec_fh *fh, bool block)
अणु
	काष्ठा cec_data *data;
	bool is_raw = msg_is_raw(msg);

	अगर (adap->devnode.unरेजिस्टरed)
		वापस -ENODEV;

	msg->rx_ts = 0;
	msg->tx_ts = 0;
	msg->rx_status = 0;
	msg->tx_status = 0;
	msg->tx_arb_lost_cnt = 0;
	msg->tx_nack_cnt = 0;
	msg->tx_low_drive_cnt = 0;
	msg->tx_error_cnt = 0;
	msg->sequence = 0;

	अगर (msg->reply && msg->समयout == 0) अणु
		/* Make sure the समयout isn't 0. */
		msg->समयout = 1000;
	पूर्ण
	msg->flags &= CEC_MSG_FL_REPLY_TO_FOLLOWERS | CEC_MSG_FL_RAW;

	अगर (!msg->समयout)
		msg->flags &= ~CEC_MSG_FL_REPLY_TO_FOLLOWERS;

	/* Sanity checks */
	अगर (msg->len == 0 || msg->len > CEC_MAX_MSG_SIZE) अणु
		dprपूर्णांकk(1, "%s: invalid length %d\n", __func__, msg->len);
		वापस -EINVAL;
	पूर्ण

	स_रखो(msg->msg + msg->len, 0, माप(msg->msg) - msg->len);

	अगर (msg->समयout)
		dprपूर्णांकk(2, "%s: %*ph (wait for 0x%02x%s)\n",
			__func__, msg->len, msg->msg, msg->reply,
			!block ? ", nb" : "");
	अन्यथा
		dprपूर्णांकk(2, "%s: %*ph%s\n",
			__func__, msg->len, msg->msg, !block ? " (nb)" : "");

	अगर (msg->समयout && msg->len == 1) अणु
		dprपूर्णांकk(1, "%s: can't reply to poll msg\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (is_raw) अणु
		अगर (!capable(CAP_SYS_RAWIO))
			वापस -EPERM;
	पूर्ण अन्यथा अणु
		/* A CDC-Only device can only send CDC messages */
		अगर ((adap->log_addrs.flags & CEC_LOG_ADDRS_FL_CDC_ONLY) &&
		    (msg->len == 1 || msg->msg[1] != CEC_MSG_CDC_MESSAGE)) अणु
			dprपूर्णांकk(1, "%s: not a CDC message\n", __func__);
			वापस -EINVAL;
		पूर्ण

		अगर (msg->len >= 4 && msg->msg[1] == CEC_MSG_CDC_MESSAGE) अणु
			msg->msg[2] = adap->phys_addr >> 8;
			msg->msg[3] = adap->phys_addr & 0xff;
		पूर्ण

		अगर (msg->len == 1) अणु
			अगर (cec_msg_destination(msg) == 0xf) अणु
				dprपूर्णांकk(1, "%s: invalid poll message\n",
					__func__);
				वापस -EINVAL;
			पूर्ण
			अगर (cec_has_log_addr(adap, cec_msg_destination(msg))) अणु
				/*
				 * If the destination is a logical address our
				 * adapter has alपढ़ोy claimed, then just NACK
				 * this. It depends on the hardware what it will
				 * करो with a POLL to itself (some OK this), so
				 * it is just as easy to handle it here so the
				 * behavior will be consistent.
				 */
				msg->tx_ts = kसमय_get_ns();
				msg->tx_status = CEC_TX_STATUS_NACK |
					CEC_TX_STATUS_MAX_RETRIES;
				msg->tx_nack_cnt = 1;
				msg->sequence = ++adap->sequence;
				अगर (!msg->sequence)
					msg->sequence = ++adap->sequence;
				वापस 0;
			पूर्ण
		पूर्ण
		अगर (msg->len > 1 && !cec_msg_is_broadcast(msg) &&
		    cec_has_log_addr(adap, cec_msg_destination(msg))) अणु
			dprपूर्णांकk(1, "%s: destination is the adapter itself\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
		अगर (msg->len > 1 && adap->is_configured &&
		    !cec_has_log_addr(adap, cec_msg_initiator(msg))) अणु
			dprपूर्णांकk(1, "%s: initiator has unknown logical address %d\n",
				__func__, cec_msg_initiator(msg));
			वापस -EINVAL;
		पूर्ण
		/*
		 * Special हाल: allow Ping and IMAGE/TEXT_VIEW_ON to be
		 * transmitted to a TV, even अगर the adapter is unconfigured.
		 * This makes it possible to detect or wake up displays that
		 * pull करोwn the HPD when in standby.
		 */
		अगर (!adap->is_configured && !adap->is_configuring &&
		    (msg->len > 2 ||
		     cec_msg_destination(msg) != CEC_LOG_ADDR_TV ||
		     (msg->len == 2 && msg->msg[1] != CEC_MSG_IMAGE_VIEW_ON &&
		      msg->msg[1] != CEC_MSG_TEXT_VIEW_ON))) अणु
			dprपूर्णांकk(1, "%s: adapter is unconfigured\n", __func__);
			वापस -ENONET;
		पूर्ण
	पूर्ण

	अगर (!adap->is_configured && !adap->is_configuring) अणु
		अगर (adap->needs_hpd) अणु
			dprपूर्णांकk(1, "%s: adapter is unconfigured and needs HPD\n",
				__func__);
			वापस -ENONET;
		पूर्ण
		अगर (msg->reply) अणु
			dprपूर्णांकk(1, "%s: invalid msg->reply\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (adap->transmit_queue_sz >= CEC_MAX_MSG_TX_QUEUE_SZ) अणु
		dprपूर्णांकk(2, "%s: transmit queue full\n", __func__);
		वापस -EBUSY;
	पूर्ण

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	msg->sequence = ++adap->sequence;
	अगर (!msg->sequence)
		msg->sequence = ++adap->sequence;

	data->msg = *msg;
	data->fh = fh;
	data->adap = adap;
	data->blocking = block;

	init_completion(&data->c);
	INIT_DELAYED_WORK(&data->work, cec_रुको_समयout);

	अगर (fh)
		list_add_tail(&data->xfer_list, &fh->xfer_list);

	list_add_tail(&data->list, &adap->transmit_queue);
	adap->transmit_queue_sz++;
	अगर (!adap->transmitting)
		wake_up_पूर्णांकerruptible(&adap->kthपढ़ो_रुकोq);

	/* All करोne अगर we करोn't need to block रुकोing क्रम completion */
	अगर (!block)
		वापस 0;

	/*
	 * Release the lock and रुको, retake the lock afterwards.
	 */
	mutex_unlock(&adap->lock);
	रुको_क्रम_completion_समाप्तable(&data->c);
	अगर (!data->completed)
		cancel_delayed_work_sync(&data->work);
	mutex_lock(&adap->lock);

	/* Cancel the transmit अगर it was पूर्णांकerrupted */
	अगर (!data->completed)
		cec_data_cancel(data, CEC_TX_STATUS_ABORTED);

	/* The transmit completed (possibly with an error) */
	*msg = data->msg;
	kमुक्त(data);
	वापस 0;
पूर्ण

/* Helper function to be used by drivers and this framework. */
पूर्णांक cec_transmit_msg(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg,
		     bool block)
अणु
	पूर्णांक ret;

	mutex_lock(&adap->lock);
	ret = cec_transmit_msg_fh(adap, msg, शून्य, block);
	mutex_unlock(&adap->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cec_transmit_msg);

/*
 * I करोn't like क्रमward references but without this the low-level
 * cec_received_msg() function would come after a bunch of high-level
 * CEC protocol handling functions. That was very confusing.
 */
अटल पूर्णांक cec_receive_notअगरy(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg,
			      bool is_reply);

#घोषणा सूचीECTED	0x80
#घोषणा BCAST1_4	0x40
#घोषणा BCAST2_0	0x20	/* broadcast only allowed क्रम >= 2.0 */
#घोषणा BCAST		(BCAST1_4 | BCAST2_0)
#घोषणा BOTH		(BCAST | सूचीECTED)

/*
 * Specअगरy minimum length and whether the message is directed, broadcast
 * or both. Messages that करो not match the criteria are ignored as per
 * the CEC specअगरication.
 */
अटल स्थिर u8 cec_msg_size[256] = अणु
	[CEC_MSG_ACTIVE_SOURCE] = 4 | BCAST,
	[CEC_MSG_IMAGE_VIEW_ON] = 2 | सूचीECTED,
	[CEC_MSG_TEXT_VIEW_ON] = 2 | सूचीECTED,
	[CEC_MSG_INACTIVE_SOURCE] = 4 | सूचीECTED,
	[CEC_MSG_REQUEST_ACTIVE_SOURCE] = 2 | BCAST,
	[CEC_MSG_ROUTING_CHANGE] = 6 | BCAST,
	[CEC_MSG_ROUTING_INFORMATION] = 4 | BCAST,
	[CEC_MSG_SET_STREAM_PATH] = 4 | BCAST,
	[CEC_MSG_STANDBY] = 2 | BOTH,
	[CEC_MSG_RECORD_OFF] = 2 | सूचीECTED,
	[CEC_MSG_RECORD_ON] = 3 | सूचीECTED,
	[CEC_MSG_RECORD_STATUS] = 3 | सूचीECTED,
	[CEC_MSG_RECORD_TV_SCREEN] = 2 | सूचीECTED,
	[CEC_MSG_CLEAR_ANALOGUE_TIMER] = 13 | सूचीECTED,
	[CEC_MSG_CLEAR_DIGITAL_TIMER] = 16 | सूचीECTED,
	[CEC_MSG_CLEAR_EXT_TIMER] = 13 | सूचीECTED,
	[CEC_MSG_SET_ANALOGUE_TIMER] = 13 | सूचीECTED,
	[CEC_MSG_SET_DIGITAL_TIMER] = 16 | सूचीECTED,
	[CEC_MSG_SET_EXT_TIMER] = 13 | सूचीECTED,
	[CEC_MSG_SET_TIMER_PROGRAM_TITLE] = 2 | सूचीECTED,
	[CEC_MSG_TIMER_CLEARED_STATUS] = 3 | सूचीECTED,
	[CEC_MSG_TIMER_STATUS] = 3 | सूचीECTED,
	[CEC_MSG_CEC_VERSION] = 3 | सूचीECTED,
	[CEC_MSG_GET_CEC_VERSION] = 2 | सूचीECTED,
	[CEC_MSG_GIVE_PHYSICAL_ADDR] = 2 | सूचीECTED,
	[CEC_MSG_GET_MENU_LANGUAGE] = 2 | सूचीECTED,
	[CEC_MSG_REPORT_PHYSICAL_ADDR] = 5 | BCAST,
	[CEC_MSG_SET_MENU_LANGUAGE] = 5 | BCAST,
	[CEC_MSG_REPORT_FEATURES] = 6 | BCAST,
	[CEC_MSG_GIVE_FEATURES] = 2 | सूचीECTED,
	[CEC_MSG_DECK_CONTROL] = 3 | सूचीECTED,
	[CEC_MSG_DECK_STATUS] = 3 | सूचीECTED,
	[CEC_MSG_GIVE_DECK_STATUS] = 3 | सूचीECTED,
	[CEC_MSG_PLAY] = 3 | सूचीECTED,
	[CEC_MSG_GIVE_TUNER_DEVICE_STATUS] = 3 | सूचीECTED,
	[CEC_MSG_SELECT_ANALOGUE_SERVICE] = 6 | सूचीECTED,
	[CEC_MSG_SELECT_DIGITAL_SERVICE] = 9 | सूचीECTED,
	[CEC_MSG_TUNER_DEVICE_STATUS] = 7 | सूचीECTED,
	[CEC_MSG_TUNER_STEP_DECREMENT] = 2 | सूचीECTED,
	[CEC_MSG_TUNER_STEP_INCREMENT] = 2 | सूचीECTED,
	[CEC_MSG_DEVICE_VENDOR_ID] = 5 | BCAST,
	[CEC_MSG_GIVE_DEVICE_VENDOR_ID] = 2 | सूचीECTED,
	[CEC_MSG_VENDOR_COMMAND] = 2 | सूचीECTED,
	[CEC_MSG_VENDOR_COMMAND_WITH_ID] = 5 | BOTH,
	[CEC_MSG_VENDOR_REMOTE_BUTTON_DOWN] = 2 | BOTH,
	[CEC_MSG_VENDOR_REMOTE_BUTTON_UP] = 2 | BOTH,
	[CEC_MSG_SET_OSD_STRING] = 3 | सूचीECTED,
	[CEC_MSG_GIVE_OSD_NAME] = 2 | सूचीECTED,
	[CEC_MSG_SET_OSD_NAME] = 2 | सूचीECTED,
	[CEC_MSG_MENU_REQUEST] = 3 | सूचीECTED,
	[CEC_MSG_MENU_STATUS] = 3 | सूचीECTED,
	[CEC_MSG_USER_CONTROL_PRESSED] = 3 | सूचीECTED,
	[CEC_MSG_USER_CONTROL_RELEASED] = 2 | सूचीECTED,
	[CEC_MSG_GIVE_DEVICE_POWER_STATUS] = 2 | सूचीECTED,
	[CEC_MSG_REPORT_POWER_STATUS] = 3 | सूचीECTED | BCAST2_0,
	[CEC_MSG_FEATURE_ABORT] = 4 | सूचीECTED,
	[CEC_MSG_ABORT] = 2 | सूचीECTED,
	[CEC_MSG_GIVE_AUDIO_STATUS] = 2 | सूचीECTED,
	[CEC_MSG_GIVE_SYSTEM_AUDIO_MODE_STATUS] = 2 | सूचीECTED,
	[CEC_MSG_REPORT_AUDIO_STATUS] = 3 | सूचीECTED,
	[CEC_MSG_REPORT_SHORT_AUDIO_DESCRIPTOR] = 2 | सूचीECTED,
	[CEC_MSG_REQUEST_SHORT_AUDIO_DESCRIPTOR] = 2 | सूचीECTED,
	[CEC_MSG_SET_SYSTEM_AUDIO_MODE] = 3 | BOTH,
	[CEC_MSG_SYSTEM_AUDIO_MODE_REQUEST] = 2 | सूचीECTED,
	[CEC_MSG_SYSTEM_AUDIO_MODE_STATUS] = 3 | सूचीECTED,
	[CEC_MSG_SET_AUDIO_RATE] = 3 | सूचीECTED,
	[CEC_MSG_INITIATE_ARC] = 2 | सूचीECTED,
	[CEC_MSG_REPORT_ARC_INITIATED] = 2 | सूचीECTED,
	[CEC_MSG_REPORT_ARC_TERMINATED] = 2 | सूचीECTED,
	[CEC_MSG_REQUEST_ARC_INITIATION] = 2 | सूचीECTED,
	[CEC_MSG_REQUEST_ARC_TERMINATION] = 2 | सूचीECTED,
	[CEC_MSG_TERMINATE_ARC] = 2 | सूचीECTED,
	[CEC_MSG_REQUEST_CURRENT_LATENCY] = 4 | BCAST,
	[CEC_MSG_REPORT_CURRENT_LATENCY] = 6 | BCAST,
	[CEC_MSG_CDC_MESSAGE] = 2 | BCAST,
पूर्ण;

/* Called by the CEC adapter अगर a message is received */
व्योम cec_received_msg_ts(काष्ठा cec_adapter *adap,
			 काष्ठा cec_msg *msg, kसमय_प्रकार ts)
अणु
	काष्ठा cec_data *data;
	u8 msg_init = cec_msg_initiator(msg);
	u8 msg_dest = cec_msg_destination(msg);
	u8 cmd = msg->msg[1];
	bool is_reply = false;
	bool valid_la = true;
	u8 min_len = 0;

	अगर (WARN_ON(!msg->len || msg->len > CEC_MAX_MSG_SIZE))
		वापस;

	अगर (adap->devnode.unरेजिस्टरed)
		वापस;

	/*
	 * Some CEC adapters will receive the messages that they transmitted.
	 * This test filters out those messages by checking अगर we are the
	 * initiator, and just वापसing in that हाल.
	 *
	 * Note that this won't work अगर this is an Unरेजिस्टरed device.
	 *
	 * It is bad practice अगर the hardware receives the message that it
	 * transmitted and luckily most CEC adapters behave correctly in this
	 * respect.
	 */
	अगर (msg_init != CEC_LOG_ADDR_UNREGISTERED &&
	    cec_has_log_addr(adap, msg_init))
		वापस;

	msg->rx_ts = kसमय_प्रकारo_ns(ts);
	msg->rx_status = CEC_RX_STATUS_OK;
	msg->sequence = msg->reply = msg->समयout = 0;
	msg->tx_status = 0;
	msg->tx_ts = 0;
	msg->tx_arb_lost_cnt = 0;
	msg->tx_nack_cnt = 0;
	msg->tx_low_drive_cnt = 0;
	msg->tx_error_cnt = 0;
	msg->flags = 0;
	स_रखो(msg->msg + msg->len, 0, माप(msg->msg) - msg->len);

	mutex_lock(&adap->lock);
	dprपूर्णांकk(2, "%s: %*ph\n", __func__, msg->len, msg->msg);

	adap->last_initiator = 0xff;

	/* Check अगर this message was क्रम us (directed or broadcast). */
	अगर (!cec_msg_is_broadcast(msg))
		valid_la = cec_has_log_addr(adap, msg_dest);

	/*
	 * Check अगर the length is not too लघु or अगर the message is a
	 * broadcast message where a directed message was expected or
	 * vice versa. If so, then the message has to be ignored (according
	 * to section CEC 7.3 and CEC 12.2).
	 */
	अगर (valid_la && msg->len > 1 && cec_msg_size[cmd]) अणु
		u8 dir_fl = cec_msg_size[cmd] & BOTH;

		min_len = cec_msg_size[cmd] & 0x1f;
		अगर (msg->len < min_len)
			valid_la = false;
		अन्यथा अगर (!cec_msg_is_broadcast(msg) && !(dir_fl & सूचीECTED))
			valid_la = false;
		अन्यथा अगर (cec_msg_is_broadcast(msg) && !(dir_fl & BCAST))
			valid_la = false;
		अन्यथा अगर (cec_msg_is_broadcast(msg) &&
			 adap->log_addrs.cec_version < CEC_OP_CEC_VERSION_2_0 &&
			 !(dir_fl & BCAST1_4))
			valid_la = false;
	पूर्ण
	अगर (valid_la && min_len) अणु
		/* These messages have special length requirements */
		चयन (cmd) अणु
		हाल CEC_MSG_TIMER_STATUS:
			अगर (msg->msg[2] & 0x10) अणु
				चयन (msg->msg[2] & 0xf) अणु
				हाल CEC_OP_PROG_INFO_NOT_ENOUGH_SPACE:
				हाल CEC_OP_PROG_INFO_MIGHT_NOT_BE_ENOUGH_SPACE:
					अगर (msg->len < 5)
						valid_la = false;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर ((msg->msg[2] & 0xf) == CEC_OP_PROG_ERROR_DUPLICATE) अणु
				अगर (msg->len < 5)
					valid_la = false;
			पूर्ण
			अवरोध;
		हाल CEC_MSG_RECORD_ON:
			चयन (msg->msg[2]) अणु
			हाल CEC_OP_RECORD_SRC_OWN:
				अवरोध;
			हाल CEC_OP_RECORD_SRC_DIGITAL:
				अगर (msg->len < 10)
					valid_la = false;
				अवरोध;
			हाल CEC_OP_RECORD_SRC_ANALOG:
				अगर (msg->len < 7)
					valid_la = false;
				अवरोध;
			हाल CEC_OP_RECORD_SRC_EXT_PLUG:
				अगर (msg->len < 4)
					valid_la = false;
				अवरोध;
			हाल CEC_OP_RECORD_SRC_EXT_PHYS_ADDR:
				अगर (msg->len < 5)
					valid_la = false;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/* It's a valid message and not a poll or CDC message */
	अगर (valid_la && msg->len > 1 && cmd != CEC_MSG_CDC_MESSAGE) अणु
		bool पात = cmd == CEC_MSG_FEATURE_ABORT;

		/* The पातed command is in msg[2] */
		अगर (पात)
			cmd = msg->msg[2];

		/*
		 * Walk over all transmitted messages that are रुकोing क्रम a
		 * reply.
		 */
		list_क्रम_each_entry(data, &adap->रुको_queue, list) अणु
			काष्ठा cec_msg *dst = &data->msg;

			/*
			 * The *only* CEC message that has two possible replies
			 * is CEC_MSG_INITIATE_ARC.
			 * In this हाल allow either of the two replies.
			 */
			अगर (!पात && dst->msg[1] == CEC_MSG_INITIATE_ARC &&
			    (cmd == CEC_MSG_REPORT_ARC_INITIATED ||
			     cmd == CEC_MSG_REPORT_ARC_TERMINATED) &&
			    (dst->reply == CEC_MSG_REPORT_ARC_INITIATED ||
			     dst->reply == CEC_MSG_REPORT_ARC_TERMINATED))
				dst->reply = cmd;

			/* Does the command match? */
			अगर ((पात && cmd != dst->msg[1]) ||
			    (!पात && cmd != dst->reply))
				जारी;

			/* Does the addressing match? */
			अगर (msg_init != cec_msg_destination(dst) &&
			    !cec_msg_is_broadcast(dst))
				जारी;

			/* We got a reply */
			स_नकल(dst->msg, msg->msg, msg->len);
			dst->len = msg->len;
			dst->rx_ts = msg->rx_ts;
			dst->rx_status = msg->rx_status;
			अगर (पात)
				dst->rx_status |= CEC_RX_STATUS_FEATURE_ABORT;
			msg->flags = dst->flags;
			/* Remove it from the रुको_queue */
			list_del_init(&data->list);

			/* Cancel the pending समयout work */
			अगर (!cancel_delayed_work(&data->work)) अणु
				mutex_unlock(&adap->lock);
				cancel_delayed_work_sync(&data->work);
				mutex_lock(&adap->lock);
			पूर्ण
			/*
			 * Mark this as a reply, provided someone is still
			 * रुकोing क्रम the answer.
			 */
			अगर (data->fh)
				is_reply = true;
			cec_data_completed(data);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&adap->lock);

	/* Pass the message on to any monitoring filehandles */
	cec_queue_msg_monitor(adap, msg, valid_la);

	/* We're करोne अगर it is not क्रम us or a poll message */
	अगर (!valid_la || msg->len <= 1)
		वापस;

	अगर (adap->log_addrs.log_addr_mask == 0)
		वापस;

	/*
	 * Process the message on the protocol level. If is_reply is true,
	 * then cec_receive_notअगरy() won't pass on the reply to the listener(s)
	 * since that was alपढ़ोy करोne by cec_data_completed() above.
	 */
	cec_receive_notअगरy(adap, msg, is_reply);
पूर्ण
EXPORT_SYMBOL_GPL(cec_received_msg_ts);

/* Logical Address Handling */

/*
 * Attempt to claim a specअगरic logical address.
 *
 * This function is called with adap->lock held.
 */
अटल पूर्णांक cec_config_log_addr(काष्ठा cec_adapter *adap,
			       अचिन्हित पूर्णांक idx,
			       अचिन्हित पूर्णांक log_addr)
अणु
	काष्ठा cec_log_addrs *las = &adap->log_addrs;
	काष्ठा cec_msg msg = अणु पूर्ण;
	स्थिर अचिन्हित पूर्णांक max_retries = 2;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (cec_has_log_addr(adap, log_addr))
		वापस 0;

	/* Send poll message */
	msg.len = 1;
	msg.msg[0] = (log_addr << 4) | log_addr;

	क्रम (i = 0; i < max_retries; i++) अणु
		err = cec_transmit_msg_fh(adap, &msg, शून्य, true);

		/*
		 * While trying to poll the physical address was reset
		 * and the adapter was unconfigured, so bail out.
		 */
		अगर (!adap->is_configuring)
			वापस -EINTR;

		अगर (err)
			वापस err;

		/*
		 * The message was पातed due to a disconnect or
		 * unconfigure, just bail out.
		 */
		अगर (msg.tx_status & CEC_TX_STATUS_ABORTED)
			वापस -EINTR;
		अगर (msg.tx_status & CEC_TX_STATUS_OK)
			वापस 0;
		अगर (msg.tx_status & CEC_TX_STATUS_NACK)
			अवरोध;
		/*
		 * Retry up to max_retries बार अगर the message was neither
		 * OKed or NACKed. This can happen due to e.g. a Lost
		 * Arbitration condition.
		 */
	पूर्ण

	/*
	 * If we are unable to get an OK or a NACK after max_retries attempts
	 * (and note that each attempt alपढ़ोy consists of four polls), then
	 * we assume that something is really weird and that it is not a
	 * good idea to try and claim this logical address.
	 */
	अगर (i == max_retries)
		वापस 0;

	/*
	 * Message not acknowledged, so this logical
	 * address is मुक्त to use.
	 */
	err = adap->ops->adap_log_addr(adap, log_addr);
	अगर (err)
		वापस err;

	las->log_addr[idx] = log_addr;
	las->log_addr_mask |= 1 << log_addr;
	वापस 1;
पूर्ण

/*
 * Unconfigure the adapter: clear all logical addresses and send
 * the state changed event.
 *
 * This function is called with adap->lock held.
 */
अटल व्योम cec_adap_unconfigure(काष्ठा cec_adapter *adap)
अणु
	अगर (!adap->needs_hpd ||
	    adap->phys_addr != CEC_PHYS_ADDR_INVALID)
		WARN_ON(adap->ops->adap_log_addr(adap, CEC_LOG_ADDR_INVALID));
	adap->log_addrs.log_addr_mask = 0;
	adap->is_configuring = false;
	adap->is_configured = false;
	cec_flush(adap);
	wake_up_पूर्णांकerruptible(&adap->kthपढ़ो_रुकोq);
	cec_post_state_event(adap);
पूर्ण

/*
 * Attempt to claim the required logical addresses.
 */
अटल पूर्णांक cec_config_thपढ़ो_func(व्योम *arg)
अणु
	/* The various LAs क्रम each type of device */
	अटल स्थिर u8 tv_log_addrs[] = अणु
		CEC_LOG_ADDR_TV, CEC_LOG_ADDR_SPECIFIC,
		CEC_LOG_ADDR_INVALID
	पूर्ण;
	अटल स्थिर u8 record_log_addrs[] = अणु
		CEC_LOG_ADDR_RECORD_1, CEC_LOG_ADDR_RECORD_2,
		CEC_LOG_ADDR_RECORD_3,
		CEC_LOG_ADDR_BACKUP_1, CEC_LOG_ADDR_BACKUP_2,
		CEC_LOG_ADDR_INVALID
	पूर्ण;
	अटल स्थिर u8 tuner_log_addrs[] = अणु
		CEC_LOG_ADDR_TUNER_1, CEC_LOG_ADDR_TUNER_2,
		CEC_LOG_ADDR_TUNER_3, CEC_LOG_ADDR_TUNER_4,
		CEC_LOG_ADDR_BACKUP_1, CEC_LOG_ADDR_BACKUP_2,
		CEC_LOG_ADDR_INVALID
	पूर्ण;
	अटल स्थिर u8 playback_log_addrs[] = अणु
		CEC_LOG_ADDR_PLAYBACK_1, CEC_LOG_ADDR_PLAYBACK_2,
		CEC_LOG_ADDR_PLAYBACK_3,
		CEC_LOG_ADDR_BACKUP_1, CEC_LOG_ADDR_BACKUP_2,
		CEC_LOG_ADDR_INVALID
	पूर्ण;
	अटल स्थिर u8 audioप्रणाली_log_addrs[] = अणु
		CEC_LOG_ADDR_AUDIOSYSTEM,
		CEC_LOG_ADDR_INVALID
	पूर्ण;
	अटल स्थिर u8 specअगरic_use_log_addrs[] = अणु
		CEC_LOG_ADDR_SPECIFIC,
		CEC_LOG_ADDR_BACKUP_1, CEC_LOG_ADDR_BACKUP_2,
		CEC_LOG_ADDR_INVALID
	पूर्ण;
	अटल स्थिर u8 *type2addrs[6] = अणु
		[CEC_LOG_ADDR_TYPE_TV] = tv_log_addrs,
		[CEC_LOG_ADDR_TYPE_RECORD] = record_log_addrs,
		[CEC_LOG_ADDR_TYPE_TUNER] = tuner_log_addrs,
		[CEC_LOG_ADDR_TYPE_PLAYBACK] = playback_log_addrs,
		[CEC_LOG_ADDR_TYPE_AUDIOSYSTEM] = audioप्रणाली_log_addrs,
		[CEC_LOG_ADDR_TYPE_SPECIFIC] = specअगरic_use_log_addrs,
	पूर्ण;
	अटल स्थिर u16 type2mask[] = अणु
		[CEC_LOG_ADDR_TYPE_TV] = CEC_LOG_ADDR_MASK_TV,
		[CEC_LOG_ADDR_TYPE_RECORD] = CEC_LOG_ADDR_MASK_RECORD,
		[CEC_LOG_ADDR_TYPE_TUNER] = CEC_LOG_ADDR_MASK_TUNER,
		[CEC_LOG_ADDR_TYPE_PLAYBACK] = CEC_LOG_ADDR_MASK_PLAYBACK,
		[CEC_LOG_ADDR_TYPE_AUDIOSYSTEM] = CEC_LOG_ADDR_MASK_AUDIOSYSTEM,
		[CEC_LOG_ADDR_TYPE_SPECIFIC] = CEC_LOG_ADDR_MASK_SPECIFIC,
	पूर्ण;
	काष्ठा cec_adapter *adap = arg;
	काष्ठा cec_log_addrs *las = &adap->log_addrs;
	पूर्णांक err;
	पूर्णांक i, j;

	mutex_lock(&adap->lock);
	dprपूर्णांकk(1, "physical address: %x.%x.%x.%x, claim %d logical addresses\n",
		cec_phys_addr_exp(adap->phys_addr), las->num_log_addrs);
	las->log_addr_mask = 0;

	अगर (las->log_addr_type[0] == CEC_LOG_ADDR_TYPE_UNREGISTERED)
		जाओ configured;

	क्रम (i = 0; i < las->num_log_addrs; i++) अणु
		अचिन्हित पूर्णांक type = las->log_addr_type[i];
		स्थिर u8 *la_list;
		u8 last_la;

		/*
		 * The TV functionality can only map to physical address 0.
		 * For any other address, try the Specअगरic functionality
		 * instead as per the spec.
		 */
		अगर (adap->phys_addr && type == CEC_LOG_ADDR_TYPE_TV)
			type = CEC_LOG_ADDR_TYPE_SPECIFIC;

		la_list = type2addrs[type];
		last_la = las->log_addr[i];
		las->log_addr[i] = CEC_LOG_ADDR_INVALID;
		अगर (last_la == CEC_LOG_ADDR_INVALID ||
		    last_la == CEC_LOG_ADDR_UNREGISTERED ||
		    !((1 << last_la) & type2mask[type]))
			last_la = la_list[0];

		err = cec_config_log_addr(adap, i, last_la);
		अगर (err > 0) /* Reused last LA */
			जारी;

		अगर (err < 0)
			जाओ unconfigure;

		क्रम (j = 0; la_list[j] != CEC_LOG_ADDR_INVALID; j++) अणु
			/* Tried this one alपढ़ोy, skip it */
			अगर (la_list[j] == last_la)
				जारी;
			/* The backup addresses are CEC 2.0 specअगरic */
			अगर ((la_list[j] == CEC_LOG_ADDR_BACKUP_1 ||
			     la_list[j] == CEC_LOG_ADDR_BACKUP_2) &&
			    las->cec_version < CEC_OP_CEC_VERSION_2_0)
				जारी;

			err = cec_config_log_addr(adap, i, la_list[j]);
			अगर (err == 0) /* LA is in use */
				जारी;
			अगर (err < 0)
				जाओ unconfigure;
			/* Done, claimed an LA */
			अवरोध;
		पूर्ण

		अगर (la_list[j] == CEC_LOG_ADDR_INVALID)
			dprपूर्णांकk(1, "could not claim LA %d\n", i);
	पूर्ण

	अगर (adap->log_addrs.log_addr_mask == 0 &&
	    !(las->flags & CEC_LOG_ADDRS_FL_ALLOW_UNREG_FALLBACK))
		जाओ unconfigure;

configured:
	अगर (adap->log_addrs.log_addr_mask == 0) अणु
		/* Fall back to unरेजिस्टरed */
		las->log_addr[0] = CEC_LOG_ADDR_UNREGISTERED;
		las->log_addr_mask = 1 << las->log_addr[0];
		क्रम (i = 1; i < las->num_log_addrs; i++)
			las->log_addr[i] = CEC_LOG_ADDR_INVALID;
	पूर्ण
	क्रम (i = las->num_log_addrs; i < CEC_MAX_LOG_ADDRS; i++)
		las->log_addr[i] = CEC_LOG_ADDR_INVALID;
	adap->is_configured = true;
	adap->is_configuring = false;
	cec_post_state_event(adap);

	/*
	 * Now post the Report Features and Report Physical Address broadcast
	 * messages. Note that these are non-blocking transmits, meaning that
	 * they are just queued up and once adap->lock is unlocked the मुख्य
	 * thपढ़ो will kick in and start transmitting these.
	 *
	 * If after this function is करोne (but beक्रमe one or more of these
	 * messages are actually transmitted) the CEC adapter is unconfigured,
	 * then any reमुख्यing messages will be dropped by the मुख्य thपढ़ो.
	 */
	क्रम (i = 0; i < las->num_log_addrs; i++) अणु
		काष्ठा cec_msg msg = अणुपूर्ण;

		अगर (las->log_addr[i] == CEC_LOG_ADDR_INVALID ||
		    (las->flags & CEC_LOG_ADDRS_FL_CDC_ONLY))
			जारी;

		msg.msg[0] = (las->log_addr[i] << 4) | 0x0f;

		/* Report Features must come first according to CEC 2.0 */
		अगर (las->log_addr[i] != CEC_LOG_ADDR_UNREGISTERED &&
		    adap->log_addrs.cec_version >= CEC_OP_CEC_VERSION_2_0) अणु
			cec_fill_msg_report_features(adap, &msg, i);
			cec_transmit_msg_fh(adap, &msg, शून्य, false);
		पूर्ण

		/* Report Physical Address */
		cec_msg_report_physical_addr(&msg, adap->phys_addr,
					     las->primary_device_type[i]);
		dprपूर्णांकk(1, "config: la %d pa %x.%x.%x.%x\n",
			las->log_addr[i],
			cec_phys_addr_exp(adap->phys_addr));
		cec_transmit_msg_fh(adap, &msg, शून्य, false);

		/* Report Venकरोr ID */
		अगर (adap->log_addrs.venकरोr_id != CEC_VENDOR_ID_NONE) अणु
			cec_msg_device_venकरोr_id(&msg,
						 adap->log_addrs.venकरोr_id);
			cec_transmit_msg_fh(adap, &msg, शून्य, false);
		पूर्ण
	पूर्ण
	adap->kthपढ़ो_config = शून्य;
	complete(&adap->config_completion);
	mutex_unlock(&adap->lock);
	वापस 0;

unconfigure:
	क्रम (i = 0; i < las->num_log_addrs; i++)
		las->log_addr[i] = CEC_LOG_ADDR_INVALID;
	cec_adap_unconfigure(adap);
	adap->kthपढ़ो_config = शून्य;
	mutex_unlock(&adap->lock);
	complete(&adap->config_completion);
	वापस 0;
पूर्ण

/*
 * Called from either __cec_s_phys_addr or __cec_s_log_addrs to claim the
 * logical addresses.
 *
 * This function is called with adap->lock held.
 */
अटल व्योम cec_claim_log_addrs(काष्ठा cec_adapter *adap, bool block)
अणु
	अगर (WARN_ON(adap->is_configuring || adap->is_configured))
		वापस;

	init_completion(&adap->config_completion);

	/* Ready to kick off the thपढ़ो */
	adap->is_configuring = true;
	adap->kthपढ़ो_config = kthपढ़ो_run(cec_config_thपढ़ो_func, adap,
					   "ceccfg-%s", adap->name);
	अगर (IS_ERR(adap->kthपढ़ो_config)) अणु
		adap->kthपढ़ो_config = शून्य;
	पूर्ण अन्यथा अगर (block) अणु
		mutex_unlock(&adap->lock);
		रुको_क्रम_completion(&adap->config_completion);
		mutex_lock(&adap->lock);
	पूर्ण
पूर्ण

/* Set a new physical address and send an event notअगरying userspace of this.
 *
 * This function is called with adap->lock held.
 */
व्योम __cec_s_phys_addr(काष्ठा cec_adapter *adap, u16 phys_addr, bool block)
अणु
	अगर (phys_addr == adap->phys_addr)
		वापस;
	अगर (phys_addr != CEC_PHYS_ADDR_INVALID && adap->devnode.unरेजिस्टरed)
		वापस;

	dprपूर्णांकk(1, "new physical address %x.%x.%x.%x\n",
		cec_phys_addr_exp(phys_addr));
	अगर (phys_addr == CEC_PHYS_ADDR_INVALID ||
	    adap->phys_addr != CEC_PHYS_ADDR_INVALID) अणु
		adap->phys_addr = CEC_PHYS_ADDR_INVALID;
		cec_post_state_event(adap);
		cec_adap_unconfigure(adap);
		/* Disabling monitor all mode should always succeed */
		अगर (adap->monitor_all_cnt)
			WARN_ON(call_op(adap, adap_monitor_all_enable, false));
		mutex_lock(&adap->devnode.lock);
		अगर (adap->needs_hpd || list_empty(&adap->devnode.fhs)) अणु
			WARN_ON(adap->ops->adap_enable(adap, false));
			adap->transmit_in_progress = false;
			wake_up_पूर्णांकerruptible(&adap->kthपढ़ो_रुकोq);
		पूर्ण
		mutex_unlock(&adap->devnode.lock);
		अगर (phys_addr == CEC_PHYS_ADDR_INVALID)
			वापस;
	पूर्ण

	mutex_lock(&adap->devnode.lock);
	adap->last_initiator = 0xff;
	adap->transmit_in_progress = false;

	अगर ((adap->needs_hpd || list_empty(&adap->devnode.fhs)) &&
	    adap->ops->adap_enable(adap, true)) अणु
		mutex_unlock(&adap->devnode.lock);
		वापस;
	पूर्ण

	अगर (adap->monitor_all_cnt &&
	    call_op(adap, adap_monitor_all_enable, true)) अणु
		अगर (adap->needs_hpd || list_empty(&adap->devnode.fhs))
			WARN_ON(adap->ops->adap_enable(adap, false));
		mutex_unlock(&adap->devnode.lock);
		वापस;
	पूर्ण
	mutex_unlock(&adap->devnode.lock);

	adap->phys_addr = phys_addr;
	cec_post_state_event(adap);
	अगर (adap->log_addrs.num_log_addrs)
		cec_claim_log_addrs(adap, block);
पूर्ण

व्योम cec_s_phys_addr(काष्ठा cec_adapter *adap, u16 phys_addr, bool block)
अणु
	अगर (IS_ERR_OR_शून्य(adap))
		वापस;

	mutex_lock(&adap->lock);
	__cec_s_phys_addr(adap, phys_addr, block);
	mutex_unlock(&adap->lock);
पूर्ण
EXPORT_SYMBOL_GPL(cec_s_phys_addr);

व्योम cec_s_phys_addr_from_edid(काष्ठा cec_adapter *adap,
			       स्थिर काष्ठा edid *edid)
अणु
	u16 pa = CEC_PHYS_ADDR_INVALID;

	अगर (edid && edid->extensions)
		pa = cec_get_edid_phys_addr((स्थिर u8 *)edid,
				EDID_LENGTH * (edid->extensions + 1), शून्य);
	cec_s_phys_addr(adap, pa, false);
पूर्ण
EXPORT_SYMBOL_GPL(cec_s_phys_addr_from_edid);

व्योम cec_s_conn_info(काष्ठा cec_adapter *adap,
		     स्थिर काष्ठा cec_connector_info *conn_info)
अणु
	अगर (IS_ERR_OR_शून्य(adap))
		वापस;

	अगर (!(adap->capabilities & CEC_CAP_CONNECTOR_INFO))
		वापस;

	mutex_lock(&adap->lock);
	अगर (conn_info)
		adap->conn_info = *conn_info;
	अन्यथा
		स_रखो(&adap->conn_info, 0, माप(adap->conn_info));
	cec_post_state_event(adap);
	mutex_unlock(&adap->lock);
पूर्ण
EXPORT_SYMBOL_GPL(cec_s_conn_info);

/*
 * Called from either the ioctl or a driver to set the logical addresses.
 *
 * This function is called with adap->lock held.
 */
पूर्णांक __cec_s_log_addrs(काष्ठा cec_adapter *adap,
		      काष्ठा cec_log_addrs *log_addrs, bool block)
अणु
	u16 type_mask = 0;
	पूर्णांक i;

	अगर (adap->devnode.unरेजिस्टरed)
		वापस -ENODEV;

	अगर (!log_addrs || log_addrs->num_log_addrs == 0) अणु
		cec_adap_unconfigure(adap);
		adap->log_addrs.num_log_addrs = 0;
		क्रम (i = 0; i < CEC_MAX_LOG_ADDRS; i++)
			adap->log_addrs.log_addr[i] = CEC_LOG_ADDR_INVALID;
		adap->log_addrs.osd_name[0] = '\0';
		adap->log_addrs.venकरोr_id = CEC_VENDOR_ID_NONE;
		adap->log_addrs.cec_version = CEC_OP_CEC_VERSION_2_0;
		वापस 0;
	पूर्ण

	अगर (log_addrs->flags & CEC_LOG_ADDRS_FL_CDC_ONLY) अणु
		/*
		 * Sanitize log_addrs fields अगर a CDC-Only device is
		 * requested.
		 */
		log_addrs->num_log_addrs = 1;
		log_addrs->osd_name[0] = '\0';
		log_addrs->venकरोr_id = CEC_VENDOR_ID_NONE;
		log_addrs->log_addr_type[0] = CEC_LOG_ADDR_TYPE_UNREGISTERED;
		/*
		 * This is just an पूर्णांकernal convention since a CDC-Only device
		 * करोesn't have to be a चयन. But चयनes alपढ़ोy use
		 * unरेजिस्टरed, so it makes some kind of sense to pick this
		 * as the primary device. Since a CDC-Only device never sends
		 * any 'normal' CEC messages this primary device type is never
		 * sent over the CEC bus.
		 */
		log_addrs->primary_device_type[0] = CEC_OP_PRIM_DEVTYPE_SWITCH;
		log_addrs->all_device_types[0] = 0;
		log_addrs->features[0][0] = 0;
		log_addrs->features[0][1] = 0;
	पूर्ण

	/* Ensure the osd name is 0-terminated */
	log_addrs->osd_name[माप(log_addrs->osd_name) - 1] = '\0';

	/* Sanity checks */
	अगर (log_addrs->num_log_addrs > adap->available_log_addrs) अणु
		dprपूर्णांकk(1, "num_log_addrs > %d\n", adap->available_log_addrs);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Venकरोr ID is a 24 bit number, so check अगर the value is
	 * within the correct range.
	 */
	अगर (log_addrs->venकरोr_id != CEC_VENDOR_ID_NONE &&
	    (log_addrs->venकरोr_id & 0xff000000) != 0) अणु
		dprपूर्णांकk(1, "invalid vendor ID\n");
		वापस -EINVAL;
	पूर्ण

	अगर (log_addrs->cec_version != CEC_OP_CEC_VERSION_1_4 &&
	    log_addrs->cec_version != CEC_OP_CEC_VERSION_2_0) अणु
		dprपूर्णांकk(1, "invalid CEC version\n");
		वापस -EINVAL;
	पूर्ण

	अगर (log_addrs->num_log_addrs > 1)
		क्रम (i = 0; i < log_addrs->num_log_addrs; i++)
			अगर (log_addrs->log_addr_type[i] ==
					CEC_LOG_ADDR_TYPE_UNREGISTERED) अणु
				dprपूर्णांकk(1, "num_log_addrs > 1 can't be combined with unregistered LA\n");
				वापस -EINVAL;
			पूर्ण

	क्रम (i = 0; i < log_addrs->num_log_addrs; i++) अणु
		स्थिर u8 feature_sz = ARRAY_SIZE(log_addrs->features[0]);
		u8 *features = log_addrs->features[i];
		bool op_is_dev_features = false;
		अचिन्हित पूर्णांक j;

		log_addrs->log_addr[i] = CEC_LOG_ADDR_INVALID;
		अगर (log_addrs->log_addr_type[i] > CEC_LOG_ADDR_TYPE_UNREGISTERED) अणु
			dprपूर्णांकk(1, "unknown logical address type\n");
			वापस -EINVAL;
		पूर्ण
		अगर (type_mask & (1 << log_addrs->log_addr_type[i])) अणु
			dprपूर्णांकk(1, "duplicate logical address type\n");
			वापस -EINVAL;
		पूर्ण
		type_mask |= 1 << log_addrs->log_addr_type[i];
		अगर ((type_mask & (1 << CEC_LOG_ADDR_TYPE_RECORD)) &&
		    (type_mask & (1 << CEC_LOG_ADDR_TYPE_PLAYBACK))) अणु
			/* Record alपढ़ोy contains the playback functionality */
			dprपूर्णांकk(1, "invalid record + playback combination\n");
			वापस -EINVAL;
		पूर्ण
		अगर (log_addrs->primary_device_type[i] >
					CEC_OP_PRIM_DEVTYPE_PROCESSOR) अणु
			dprपूर्णांकk(1, "unknown primary device type\n");
			वापस -EINVAL;
		पूर्ण
		अगर (log_addrs->primary_device_type[i] == 2) अणु
			dprपूर्णांकk(1, "invalid primary device type\n");
			वापस -EINVAL;
		पूर्ण
		क्रम (j = 0; j < feature_sz; j++) अणु
			अगर ((features[j] & 0x80) == 0) अणु
				अगर (op_is_dev_features)
					अवरोध;
				op_is_dev_features = true;
			पूर्ण
		पूर्ण
		अगर (!op_is_dev_features || j == feature_sz) अणु
			dprपूर्णांकk(1, "malformed features\n");
			वापस -EINVAL;
		पूर्ण
		/* Zero unused part of the feature array */
		स_रखो(features + j + 1, 0, feature_sz - j - 1);
	पूर्ण

	अगर (log_addrs->cec_version >= CEC_OP_CEC_VERSION_2_0) अणु
		अगर (log_addrs->num_log_addrs > 2) अणु
			dprपूर्णांकk(1, "CEC 2.0 allows no more than 2 logical addresses\n");
			वापस -EINVAL;
		पूर्ण
		अगर (log_addrs->num_log_addrs == 2) अणु
			अगर (!(type_mask & ((1 << CEC_LOG_ADDR_TYPE_AUDIOSYSTEM) |
					   (1 << CEC_LOG_ADDR_TYPE_TV)))) अणु
				dprपूर्णांकk(1, "two LAs is only allowed for audiosystem and TV\n");
				वापस -EINVAL;
			पूर्ण
			अगर (!(type_mask & ((1 << CEC_LOG_ADDR_TYPE_PLAYBACK) |
					   (1 << CEC_LOG_ADDR_TYPE_RECORD)))) अणु
				dprपूर्णांकk(1, "an audiosystem/TV can only be combined with record or playback\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Zero unused LAs */
	क्रम (i = log_addrs->num_log_addrs; i < CEC_MAX_LOG_ADDRS; i++) अणु
		log_addrs->primary_device_type[i] = 0;
		log_addrs->log_addr_type[i] = 0;
		log_addrs->all_device_types[i] = 0;
		स_रखो(log_addrs->features[i], 0,
		       माप(log_addrs->features[i]));
	पूर्ण

	log_addrs->log_addr_mask = adap->log_addrs.log_addr_mask;
	adap->log_addrs = *log_addrs;
	अगर (adap->phys_addr != CEC_PHYS_ADDR_INVALID)
		cec_claim_log_addrs(adap, block);
	वापस 0;
पूर्ण

पूर्णांक cec_s_log_addrs(काष्ठा cec_adapter *adap,
		    काष्ठा cec_log_addrs *log_addrs, bool block)
अणु
	पूर्णांक err;

	mutex_lock(&adap->lock);
	err = __cec_s_log_addrs(adap, log_addrs, block);
	mutex_unlock(&adap->lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(cec_s_log_addrs);

/* High-level core CEC message handling */

/* Fill in the Report Features message */
अटल व्योम cec_fill_msg_report_features(काष्ठा cec_adapter *adap,
					 काष्ठा cec_msg *msg,
					 अचिन्हित पूर्णांक la_idx)
अणु
	स्थिर काष्ठा cec_log_addrs *las = &adap->log_addrs;
	स्थिर u8 *features = las->features[la_idx];
	bool op_is_dev_features = false;
	अचिन्हित पूर्णांक idx;

	/* Report Features */
	msg->msg[0] = (las->log_addr[la_idx] << 4) | 0x0f;
	msg->len = 4;
	msg->msg[1] = CEC_MSG_REPORT_FEATURES;
	msg->msg[2] = adap->log_addrs.cec_version;
	msg->msg[3] = las->all_device_types[la_idx];

	/* Write RC Profiles first, then Device Features */
	क्रम (idx = 0; idx < ARRAY_SIZE(las->features[0]); idx++) अणु
		msg->msg[msg->len++] = features[idx];
		अगर ((features[idx] & CEC_OP_FEAT_EXT) == 0) अणु
			अगर (op_is_dev_features)
				अवरोध;
			op_is_dev_features = true;
		पूर्ण
	पूर्ण
पूर्ण

/* Transmit the Feature Abort message */
अटल पूर्णांक cec_feature_पात_reason(काष्ठा cec_adapter *adap,
				    काष्ठा cec_msg *msg, u8 reason)
अणु
	काष्ठा cec_msg tx_msg = अणु पूर्ण;

	/*
	 * Don't reply with CEC_MSG_FEATURE_ABORT to a CEC_MSG_FEATURE_ABORT
	 * message!
	 */
	अगर (msg->msg[1] == CEC_MSG_FEATURE_ABORT)
		वापस 0;
	/* Don't Feature Abort messages from 'Unregistered' */
	अगर (cec_msg_initiator(msg) == CEC_LOG_ADDR_UNREGISTERED)
		वापस 0;
	cec_msg_set_reply_to(&tx_msg, msg);
	cec_msg_feature_पात(&tx_msg, msg->msg[1], reason);
	वापस cec_transmit_msg(adap, &tx_msg, false);
पूर्ण

अटल पूर्णांक cec_feature_पात(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg)
अणु
	वापस cec_feature_पात_reason(adap, msg,
					CEC_OP_ABORT_UNRECOGNIZED_OP);
पूर्ण

अटल पूर्णांक cec_feature_refused(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg)
अणु
	वापस cec_feature_पात_reason(adap, msg,
					CEC_OP_ABORT_REFUSED);
पूर्ण

/*
 * Called when a CEC message is received. This function will करो any
 * necessary core processing. The is_reply bool is true अगर this message
 * is a reply to an earlier transmit.
 *
 * The message is either a broadcast message or a valid directed message.
 */
अटल पूर्णांक cec_receive_notअगरy(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg,
			      bool is_reply)
अणु
	bool is_broadcast = cec_msg_is_broadcast(msg);
	u8 dest_laddr = cec_msg_destination(msg);
	u8 init_laddr = cec_msg_initiator(msg);
	u8 devtype = cec_log_addr2dev(adap, dest_laddr);
	पूर्णांक la_idx = cec_log_addr2idx(adap, dest_laddr);
	bool from_unरेजिस्टरed = init_laddr == 0xf;
	काष्ठा cec_msg tx_cec_msg = अणु पूर्ण;

	dprपूर्णांकk(2, "%s: %*ph\n", __func__, msg->len, msg->msg);

	/* If this is a CDC-Only device, then ignore any non-CDC messages */
	अगर (cec_is_cdc_only(&adap->log_addrs) &&
	    msg->msg[1] != CEC_MSG_CDC_MESSAGE)
		वापस 0;

	अगर (adap->ops->received) अणु
		/* Allow drivers to process the message first */
		अगर (adap->ops->received(adap, msg) != -ENOMSG)
			वापस 0;
	पूर्ण

	/*
	 * REPORT_PHYSICAL_ADDR, CEC_MSG_USER_CONTROL_PRESSED and
	 * CEC_MSG_USER_CONTROL_RELEASED messages always have to be
	 * handled by the CEC core, even अगर the passthrough mode is on.
	 * The others are just ignored अगर passthrough mode is on.
	 */
	चयन (msg->msg[1]) अणु
	हाल CEC_MSG_GET_CEC_VERSION:
	हाल CEC_MSG_ABORT:
	हाल CEC_MSG_GIVE_DEVICE_POWER_STATUS:
	हाल CEC_MSG_GIVE_OSD_NAME:
		/*
		 * These messages reply with a directed message, so ignore अगर
		 * the initiator is Unरेजिस्टरed.
		 */
		अगर (!adap->passthrough && from_unरेजिस्टरed)
			वापस 0;
		fallthrough;
	हाल CEC_MSG_GIVE_DEVICE_VENDOR_ID:
	हाल CEC_MSG_GIVE_FEATURES:
	हाल CEC_MSG_GIVE_PHYSICAL_ADDR:
		/*
		 * Skip processing these messages अगर the passthrough mode
		 * is on.
		 */
		अगर (adap->passthrough)
			जाओ skip_processing;
		/* Ignore अगर addressing is wrong */
		अगर (is_broadcast)
			वापस 0;
		अवरोध;

	हाल CEC_MSG_USER_CONTROL_PRESSED:
	हाल CEC_MSG_USER_CONTROL_RELEASED:
		/* Wrong addressing mode: करोn't process */
		अगर (is_broadcast || from_unरेजिस्टरed)
			जाओ skip_processing;
		अवरोध;

	हाल CEC_MSG_REPORT_PHYSICAL_ADDR:
		/*
		 * This message is always processed, regardless of the
		 * passthrough setting.
		 *
		 * Exception: करोn't process अगर wrong addressing mode.
		 */
		अगर (!is_broadcast)
			जाओ skip_processing;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	cec_msg_set_reply_to(&tx_cec_msg, msg);

	चयन (msg->msg[1]) अणु
	/* The following messages are processed but still passed through */
	हाल CEC_MSG_REPORT_PHYSICAL_ADDR: अणु
		u16 pa = (msg->msg[2] << 8) | msg->msg[3];

		dprपूर्णांकk(1, "reported physical address %x.%x.%x.%x for logical address %d\n",
			cec_phys_addr_exp(pa), init_laddr);
		अवरोध;
	पूर्ण

	हाल CEC_MSG_USER_CONTROL_PRESSED:
		अगर (!(adap->capabilities & CEC_CAP_RC) ||
		    !(adap->log_addrs.flags & CEC_LOG_ADDRS_FL_ALLOW_RC_PASSTHRU))
			अवरोध;

#अगर_घोषित CONFIG_MEDIA_CEC_RC
		चयन (msg->msg[2]) अणु
		/*
		 * Play function, this message can have variable length
		 * depending on the specअगरic play function that is used.
		 */
		हाल CEC_OP_UI_CMD_PLAY_FUNCTION:
			अगर (msg->len == 2)
				rc_keyकरोwn(adap->rc, RC_PROTO_CEC,
					   msg->msg[2], 0);
			अन्यथा
				rc_keyकरोwn(adap->rc, RC_PROTO_CEC,
					   msg->msg[2] << 8 | msg->msg[3], 0);
			अवरोध;
		/*
		 * Other function messages that are not handled.
		 * Currently the RC framework करोes not allow to supply an
		 * additional parameter to a keypress. These "keys" contain
		 * other inक्रमmation such as channel number, an input number
		 * etc.
		 * For the समय being these messages are not processed by the
		 * framework and are simply क्रमwarded to the user space.
		 */
		हाल CEC_OP_UI_CMD_SELECT_BROADCAST_TYPE:
		हाल CEC_OP_UI_CMD_SELECT_SOUND_PRESENTATION:
		हाल CEC_OP_UI_CMD_TUNE_FUNCTION:
		हाल CEC_OP_UI_CMD_SELECT_MEDIA_FUNCTION:
		हाल CEC_OP_UI_CMD_SELECT_AV_INPUT_FUNCTION:
		हाल CEC_OP_UI_CMD_SELECT_AUDIO_INPUT_FUNCTION:
			अवरोध;
		शेष:
			rc_keyकरोwn(adap->rc, RC_PROTO_CEC, msg->msg[2], 0);
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		अवरोध;

	हाल CEC_MSG_USER_CONTROL_RELEASED:
		अगर (!(adap->capabilities & CEC_CAP_RC) ||
		    !(adap->log_addrs.flags & CEC_LOG_ADDRS_FL_ALLOW_RC_PASSTHRU))
			अवरोध;
#अगर_घोषित CONFIG_MEDIA_CEC_RC
		rc_keyup(adap->rc);
#पूर्ण_अगर
		अवरोध;

	/*
	 * The reमुख्यing messages are only processed अगर the passthrough mode
	 * is off.
	 */
	हाल CEC_MSG_GET_CEC_VERSION:
		cec_msg_cec_version(&tx_cec_msg, adap->log_addrs.cec_version);
		वापस cec_transmit_msg(adap, &tx_cec_msg, false);

	हाल CEC_MSG_GIVE_PHYSICAL_ADDR:
		/* Do nothing क्रम CEC चयनes using addr 15 */
		अगर (devtype == CEC_OP_PRIM_DEVTYPE_SWITCH && dest_laddr == 15)
			वापस 0;
		cec_msg_report_physical_addr(&tx_cec_msg, adap->phys_addr, devtype);
		वापस cec_transmit_msg(adap, &tx_cec_msg, false);

	हाल CEC_MSG_GIVE_DEVICE_VENDOR_ID:
		अगर (adap->log_addrs.venकरोr_id == CEC_VENDOR_ID_NONE)
			वापस cec_feature_पात(adap, msg);
		cec_msg_device_venकरोr_id(&tx_cec_msg, adap->log_addrs.venकरोr_id);
		वापस cec_transmit_msg(adap, &tx_cec_msg, false);

	हाल CEC_MSG_ABORT:
		/* Do nothing क्रम CEC चयनes */
		अगर (devtype == CEC_OP_PRIM_DEVTYPE_SWITCH)
			वापस 0;
		वापस cec_feature_refused(adap, msg);

	हाल CEC_MSG_GIVE_OSD_NAME: अणु
		अगर (adap->log_addrs.osd_name[0] == 0)
			वापस cec_feature_पात(adap, msg);
		cec_msg_set_osd_name(&tx_cec_msg, adap->log_addrs.osd_name);
		वापस cec_transmit_msg(adap, &tx_cec_msg, false);
	पूर्ण

	हाल CEC_MSG_GIVE_FEATURES:
		अगर (adap->log_addrs.cec_version < CEC_OP_CEC_VERSION_2_0)
			वापस cec_feature_पात(adap, msg);
		cec_fill_msg_report_features(adap, &tx_cec_msg, la_idx);
		वापस cec_transmit_msg(adap, &tx_cec_msg, false);

	शेष:
		/*
		 * Unprocessed messages are पातed अगर userspace isn't करोing
		 * any processing either.
		 */
		अगर (!is_broadcast && !is_reply && !adap->follower_cnt &&
		    !adap->cec_follower && msg->msg[1] != CEC_MSG_FEATURE_ABORT)
			वापस cec_feature_पात(adap, msg);
		अवरोध;
	पूर्ण

skip_processing:
	/* If this was a reply, then we're करोne, unless otherwise specअगरied */
	अगर (is_reply && !(msg->flags & CEC_MSG_FL_REPLY_TO_FOLLOWERS))
		वापस 0;

	/*
	 * Send to the exclusive follower अगर there is one, otherwise send
	 * to all followers.
	 */
	अगर (adap->cec_follower)
		cec_queue_msg_fh(adap->cec_follower, msg);
	अन्यथा
		cec_queue_msg_followers(adap, msg);
	वापस 0;
पूर्ण

/*
 * Helper functions to keep track of the 'monitor all' use count.
 *
 * These functions are called with adap->lock held.
 */
पूर्णांक cec_monitor_all_cnt_inc(काष्ठा cec_adapter *adap)
अणु
	पूर्णांक ret = 0;

	अगर (adap->monitor_all_cnt == 0)
		ret = call_op(adap, adap_monitor_all_enable, 1);
	अगर (ret == 0)
		adap->monitor_all_cnt++;
	वापस ret;
पूर्ण

व्योम cec_monitor_all_cnt_dec(काष्ठा cec_adapter *adap)
अणु
	adap->monitor_all_cnt--;
	अगर (adap->monitor_all_cnt == 0)
		WARN_ON(call_op(adap, adap_monitor_all_enable, 0));
पूर्ण

/*
 * Helper functions to keep track of the 'monitor pin' use count.
 *
 * These functions are called with adap->lock held.
 */
पूर्णांक cec_monitor_pin_cnt_inc(काष्ठा cec_adapter *adap)
अणु
	पूर्णांक ret = 0;

	अगर (adap->monitor_pin_cnt == 0)
		ret = call_op(adap, adap_monitor_pin_enable, 1);
	अगर (ret == 0)
		adap->monitor_pin_cnt++;
	वापस ret;
पूर्ण

व्योम cec_monitor_pin_cnt_dec(काष्ठा cec_adapter *adap)
अणु
	adap->monitor_pin_cnt--;
	अगर (adap->monitor_pin_cnt == 0)
		WARN_ON(call_op(adap, adap_monitor_pin_enable, 0));
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
/*
 * Log the current state of the CEC adapter.
 * Very useful क्रम debugging.
 */
पूर्णांक cec_adap_status(काष्ठा seq_file *file, व्योम *priv)
अणु
	काष्ठा cec_adapter *adap = dev_get_drvdata(file->निजी);
	काष्ठा cec_data *data;

	mutex_lock(&adap->lock);
	seq_म_लिखो(file, "configured: %d\n", adap->is_configured);
	seq_म_लिखो(file, "configuring: %d\n", adap->is_configuring);
	seq_म_लिखो(file, "phys_addr: %x.%x.%x.%x\n",
		   cec_phys_addr_exp(adap->phys_addr));
	seq_म_लिखो(file, "number of LAs: %d\n", adap->log_addrs.num_log_addrs);
	seq_म_लिखो(file, "LA mask: 0x%04x\n", adap->log_addrs.log_addr_mask);
	अगर (adap->cec_follower)
		seq_म_लिखो(file, "has CEC follower%s\n",
			   adap->passthrough ? " (in passthrough mode)" : "");
	अगर (adap->cec_initiator)
		seq_माला_दो(file, "has CEC initiator\n");
	अगर (adap->monitor_all_cnt)
		seq_म_लिखो(file, "file handles in Monitor All mode: %u\n",
			   adap->monitor_all_cnt);
	अगर (adap->tx_समयouts) अणु
		seq_म_लिखो(file, "transmit timeouts: %u\n",
			   adap->tx_समयouts);
		adap->tx_समयouts = 0;
	पूर्ण
	data = adap->transmitting;
	अगर (data)
		seq_म_लिखो(file, "transmitting message: %*ph (reply: %02x, timeout: %ums)\n",
			   data->msg.len, data->msg.msg, data->msg.reply,
			   data->msg.समयout);
	seq_म_लिखो(file, "pending transmits: %u\n", adap->transmit_queue_sz);
	list_क्रम_each_entry(data, &adap->transmit_queue, list) अणु
		seq_म_लिखो(file, "queued tx message: %*ph (reply: %02x, timeout: %ums)\n",
			   data->msg.len, data->msg.msg, data->msg.reply,
			   data->msg.समयout);
	पूर्ण
	list_क्रम_each_entry(data, &adap->रुको_queue, list) अणु
		seq_म_लिखो(file, "message waiting for reply: %*ph (reply: %02x, timeout: %ums)\n",
			   data->msg.len, data->msg.msg, data->msg.reply,
			   data->msg.समयout);
	पूर्ण

	call_व्योम_op(adap, adap_status, file);
	mutex_unlock(&adap->lock);
	वापस 0;
पूर्ण
#पूर्ण_अगर
