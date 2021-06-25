<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012 Broadcom Corporation
 */
#समावेश <linux/netdevice.h>

#समावेश "brcmu_wifi.h"
#समावेश "brcmu_utils.h"

#समावेश "cfg80211.h"
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "tracepoint.h"
#समावेश "fweh.h"
#समावेश "fwil.h"
#समावेश "proto.h"

/**
 * काष्ठा brcmf_fweh_queue_item - event item on event queue.
 *
 * @q: list element क्रम queuing.
 * @code: event code.
 * @अगरidx: पूर्णांकerface index related to this event.
 * @अगरaddr: ethernet address क्रम पूर्णांकerface.
 * @emsg: common parameters of the firmware event message.
 * @datalen: length of the data array
 * @data: event specअगरic data part of the firmware event.
 */
काष्ठा brcmf_fweh_queue_item अणु
	काष्ठा list_head q;
	क्रमागत brcmf_fweh_event_code code;
	u8 अगरidx;
	u8 अगरaddr[ETH_ALEN];
	काष्ठा brcmf_event_msg_be emsg;
	u32 datalen;
	u8 data[];
पूर्ण;

/*
 * काष्ठा brcmf_fweh_event_name - code, name mapping entry.
 */
काष्ठा brcmf_fweh_event_name अणु
	क्रमागत brcmf_fweh_event_code code;
	स्थिर अक्षर *name;
पूर्ण;

#अगर_घोषित DEBUG
#घोषणा BRCMF_ENUM_DEF(id, val) \
	अणु val, #id पूर्ण,

/* array क्रम mapping code to event name */
अटल काष्ठा brcmf_fweh_event_name fweh_event_names[] = अणु
	BRCMF_FWEH_EVENT_ENUM_DEFLIST
पूर्ण;
#अघोषित BRCMF_ENUM_DEF

/**
 * brcmf_fweh_event_name() - वापसs name क्रम given event code.
 *
 * @code: code to lookup.
 */
स्थिर अक्षर *brcmf_fweh_event_name(क्रमागत brcmf_fweh_event_code code)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(fweh_event_names); i++) अणु
		अगर (fweh_event_names[i].code == code)
			वापस fweh_event_names[i].name;
	पूर्ण
	वापस "unknown";
पूर्ण
#अन्यथा
स्थिर अक्षर *brcmf_fweh_event_name(क्रमागत brcmf_fweh_event_code code)
अणु
	वापस "nodebug";
पूर्ण
#पूर्ण_अगर

/**
 * brcmf_fweh_queue_event() - create and queue event.
 *
 * @fweh: firmware event handling info.
 * @event: event queue entry.
 */
अटल व्योम brcmf_fweh_queue_event(काष्ठा brcmf_fweh_info *fweh,
				   काष्ठा brcmf_fweh_queue_item *event)
अणु
	uदीर्घ flags;

	spin_lock_irqsave(&fweh->evt_q_lock, flags);
	list_add_tail(&event->q, &fweh->event_q);
	spin_unlock_irqrestore(&fweh->evt_q_lock, flags);
	schedule_work(&fweh->event_work);
पूर्ण

अटल पूर्णांक brcmf_fweh_call_event_handler(काष्ठा brcmf_pub *drvr,
					 काष्ठा brcmf_अगर *अगरp,
					 क्रमागत brcmf_fweh_event_code code,
					 काष्ठा brcmf_event_msg *emsg,
					 व्योम *data)
अणु
	काष्ठा brcmf_fweh_info *fweh;
	पूर्णांक err = -EINVAL;

	अगर (अगरp) अणु
		fweh = &अगरp->drvr->fweh;

		/* handle the event अगर valid पूर्णांकerface and handler */
		अगर (fweh->evt_handler[code])
			err = fweh->evt_handler[code](अगरp, emsg, data);
		अन्यथा
			bphy_err(drvr, "unhandled event %d ignored\n", code);
	पूर्ण अन्यथा अणु
		bphy_err(drvr, "no interface object\n");
	पूर्ण
	वापस err;
पूर्ण

/**
 * brcmf_fweh_handle_अगर_event() - handle IF event.
 *
 * @drvr: driver inक्रमmation object.
 * @emsg: event message object.
 * @data: event object.
 */
अटल व्योम brcmf_fweh_handle_अगर_event(काष्ठा brcmf_pub *drvr,
				       काष्ठा brcmf_event_msg *emsg,
				       व्योम *data)
अणु
	काष्ठा brcmf_अगर_event *अगरevent = data;
	काष्ठा brcmf_अगर *अगरp;
	bool is_p2pdev;

	brcmf_dbg(EVENT, "action: %u ifidx: %u bsscfgidx: %u flags: %u role: %u\n",
		  अगरevent->action, अगरevent->अगरidx, अगरevent->bsscfgidx,
		  अगरevent->flags, अगरevent->role);

	/* The P2P Device पूर्णांकerface event must not be ignored contrary to what
	 * firmware tells us. Older firmware uses p2p noअगर, with sta role.
	 * This should be accepted when p2pdev_setup is ongoing. TDLS setup will
	 * use the same अगरevent and should be ignored.
	 */
	is_p2pdev = ((अगरevent->flags & BRCMF_E_IF_FLAG_NOIF) &&
		     (अगरevent->role == BRCMF_E_IF_ROLE_P2P_CLIENT ||
		      ((अगरevent->role == BRCMF_E_IF_ROLE_STA) &&
		       (drvr->fweh.p2pdev_setup_ongoing))));
	अगर (!is_p2pdev && (अगरevent->flags & BRCMF_E_IF_FLAG_NOIF)) अणु
		brcmf_dbg(EVENT, "event can be ignored\n");
		वापस;
	पूर्ण
	अगर (अगरevent->अगरidx >= BRCMF_MAX_IFS) अणु
		bphy_err(drvr, "invalid interface index: %u\n", अगरevent->अगरidx);
		वापस;
	पूर्ण

	अगरp = drvr->अगरlist[अगरevent->bsscfgidx];

	अगर (अगरevent->action == BRCMF_E_IF_ADD) अणु
		brcmf_dbg(EVENT, "adding %s (%pM)\n", emsg->अगरname,
			  emsg->addr);
		अगरp = brcmf_add_अगर(drvr, अगरevent->bsscfgidx, अगरevent->अगरidx,
				   is_p2pdev, emsg->अगरname, emsg->addr);
		अगर (IS_ERR(अगरp))
			वापस;
		अगर (!is_p2pdev)
			brcmf_proto_add_अगर(drvr, अगरp);
		अगर (!drvr->fweh.evt_handler[BRCMF_E_IF])
			अगर (brcmf_net_attach(अगरp, false) < 0)
				वापस;
	पूर्ण

	अगर (अगरp && अगरevent->action == BRCMF_E_IF_CHANGE)
		brcmf_proto_reset_अगर(drvr, अगरp);

	brcmf_fweh_call_event_handler(drvr, अगरp, emsg->event_code, emsg,
				      data);

	अगर (अगरp && अगरevent->action == BRCMF_E_IF_DEL) अणु
		bool armed = brcmf_cfg80211_vअगर_event_armed(drvr->config);

		/* Default handling in हाल no-one रुकोs क्रम this event */
		अगर (!armed)
			brcmf_हटाओ_पूर्णांकerface(अगरp, false);
	पूर्ण
पूर्ण

/**
 * brcmf_fweh_dequeue_event() - get event from the queue.
 *
 * @fweh: firmware event handling info.
 */
अटल काष्ठा brcmf_fweh_queue_item *
brcmf_fweh_dequeue_event(काष्ठा brcmf_fweh_info *fweh)
अणु
	काष्ठा brcmf_fweh_queue_item *event = शून्य;
	uदीर्घ flags;

	spin_lock_irqsave(&fweh->evt_q_lock, flags);
	अगर (!list_empty(&fweh->event_q)) अणु
		event = list_first_entry(&fweh->event_q,
					 काष्ठा brcmf_fweh_queue_item, q);
		list_del(&event->q);
	पूर्ण
	spin_unlock_irqrestore(&fweh->evt_q_lock, flags);

	वापस event;
पूर्ण

/**
 * brcmf_fweh_event_worker() - firmware event worker.
 *
 * @work: worker object.
 */
अटल व्योम brcmf_fweh_event_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा brcmf_pub *drvr;
	काष्ठा brcmf_अगर *अगरp;
	काष्ठा brcmf_fweh_info *fweh;
	काष्ठा brcmf_fweh_queue_item *event;
	पूर्णांक err = 0;
	काष्ठा brcmf_event_msg_be *emsg_be;
	काष्ठा brcmf_event_msg emsg;

	fweh = container_of(work, काष्ठा brcmf_fweh_info, event_work);
	drvr = container_of(fweh, काष्ठा brcmf_pub, fweh);

	जबतक ((event = brcmf_fweh_dequeue_event(fweh))) अणु
		brcmf_dbg(EVENT, "event %s (%u) ifidx %u bsscfg %u addr %pM\n",
			  brcmf_fweh_event_name(event->code), event->code,
			  event->emsg.अगरidx, event->emsg.bsscfgidx,
			  event->emsg.addr);

		/* convert event message */
		emsg_be = &event->emsg;
		emsg.version = be16_to_cpu(emsg_be->version);
		emsg.flags = be16_to_cpu(emsg_be->flags);
		emsg.event_code = event->code;
		emsg.status = be32_to_cpu(emsg_be->status);
		emsg.reason = be32_to_cpu(emsg_be->reason);
		emsg.auth_type = be32_to_cpu(emsg_be->auth_type);
		emsg.datalen = be32_to_cpu(emsg_be->datalen);
		स_नकल(emsg.addr, emsg_be->addr, ETH_ALEN);
		स_नकल(emsg.अगरname, emsg_be->अगरname, माप(emsg.अगरname));
		emsg.अगरidx = emsg_be->अगरidx;
		emsg.bsscfgidx = emsg_be->bsscfgidx;

		brcmf_dbg(EVENT, "  version %u flags %u status %u reason %u\n",
			  emsg.version, emsg.flags, emsg.status, emsg.reason);
		brcmf_dbg_hex_dump(BRCMF_EVENT_ON(), event->data,
				   min_t(u32, emsg.datalen, 64),
				   "event payload, len=%d\n", emsg.datalen);

		/* special handling of पूर्णांकerface event */
		अगर (event->code == BRCMF_E_IF) अणु
			brcmf_fweh_handle_अगर_event(drvr, &emsg, event->data);
			जाओ event_मुक्त;
		पूर्ण

		अगर (event->code == BRCMF_E_TDLS_PEER_EVENT)
			अगरp = drvr->अगरlist[0];
		अन्यथा
			अगरp = drvr->अगरlist[emsg.bsscfgidx];
		err = brcmf_fweh_call_event_handler(drvr, अगरp, event->code,
						    &emsg, event->data);
		अगर (err) अणु
			bphy_err(drvr, "event handler failed (%d)\n",
				 event->code);
			err = 0;
		पूर्ण
event_मुक्त:
		kमुक्त(event);
	पूर्ण
पूर्ण

/**
 * brcmf_fweh_p2pdev_setup() - P2P device setup ongoing (or not).
 *
 * @अगरp: अगरp on which setup is taking place or finished.
 * @ongoing: p2p device setup in progress (or not).
 */
व्योम brcmf_fweh_p2pdev_setup(काष्ठा brcmf_अगर *अगरp, bool ongoing)
अणु
	अगरp->drvr->fweh.p2pdev_setup_ongoing = ongoing;
पूर्ण

/**
 * brcmf_fweh_attach() - initialize firmware event handling.
 *
 * @drvr: driver inक्रमmation object.
 */
व्योम brcmf_fweh_attach(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_fweh_info *fweh = &drvr->fweh;
	INIT_WORK(&fweh->event_work, brcmf_fweh_event_worker);
	spin_lock_init(&fweh->evt_q_lock);
	INIT_LIST_HEAD(&fweh->event_q);
पूर्ण

/**
 * brcmf_fweh_detach() - cleanup firmware event handling.
 *
 * @drvr: driver inक्रमmation object.
 */
व्योम brcmf_fweh_detach(काष्ठा brcmf_pub *drvr)
अणु
	काष्ठा brcmf_fweh_info *fweh = &drvr->fweh;

	/* cancel the worker अगर initialized */
	अगर (fweh->event_work.func) अणु
		cancel_work_sync(&fweh->event_work);
		WARN_ON(!list_empty(&fweh->event_q));
		स_रखो(fweh->evt_handler, 0, माप(fweh->evt_handler));
	पूर्ण
पूर्ण

/**
 * brcmf_fweh_रेजिस्टर() - रेजिस्टर handler क्रम given event code.
 *
 * @drvr: driver inक्रमmation object.
 * @code: event code.
 * @handler: handler क्रम the given event code.
 */
पूर्णांक brcmf_fweh_रेजिस्टर(काष्ठा brcmf_pub *drvr, क्रमागत brcmf_fweh_event_code code,
			brcmf_fweh_handler_t handler)
अणु
	अगर (drvr->fweh.evt_handler[code]) अणु
		bphy_err(drvr, "event code %d already registered\n", code);
		वापस -ENOSPC;
	पूर्ण
	drvr->fweh.evt_handler[code] = handler;
	brcmf_dbg(TRACE, "event handler registered for %s\n",
		  brcmf_fweh_event_name(code));
	वापस 0;
पूर्ण

/**
 * brcmf_fweh_unरेजिस्टर() - हटाओ handler क्रम given code.
 *
 * @drvr: driver inक्रमmation object.
 * @code: event code.
 */
व्योम brcmf_fweh_unरेजिस्टर(काष्ठा brcmf_pub *drvr,
			   क्रमागत brcmf_fweh_event_code code)
अणु
	brcmf_dbg(TRACE, "event handler cleared for %s\n",
		  brcmf_fweh_event_name(code));
	drvr->fweh.evt_handler[code] = शून्य;
पूर्ण

/**
 * brcmf_fweh_activate_events() - enables firmware events रेजिस्टरed.
 *
 * @अगरp: primary पूर्णांकerface object.
 */
पूर्णांक brcmf_fweh_activate_events(काष्ठा brcmf_अगर *अगरp)
अणु
	काष्ठा brcmf_pub *drvr = अगरp->drvr;
	पूर्णांक i, err;
	s8 evenपंचांगask[BRCMF_EVENTING_MASK_LEN];

	स_रखो(evenपंचांगask, 0, माप(evenपंचांगask));
	क्रम (i = 0; i < BRCMF_E_LAST; i++) अणु
		अगर (अगरp->drvr->fweh.evt_handler[i]) अणु
			brcmf_dbg(EVENT, "enable event %s\n",
				  brcmf_fweh_event_name(i));
			setbit(evenपंचांगask, i);
		पूर्ण
	पूर्ण

	/* want to handle IF event as well */
	brcmf_dbg(EVENT, "enable event IF\n");
	setbit(evenपंचांगask, BRCMF_E_IF);

	err = brcmf_fil_iovar_data_set(अगरp, "event_msgs",
				       evenपंचांगask, BRCMF_EVENTING_MASK_LEN);
	अगर (err)
		bphy_err(drvr, "Set event_msgs error (%d)\n", err);

	वापस err;
पूर्ण

/**
 * brcmf_fweh_process_event() - process skb as firmware event.
 *
 * @drvr: driver inक्रमmation object.
 * @event_packet: event packet to process.
 * @packet_len: length of the packet
 * @gfp: memory allocation flags.
 *
 * If the packet buffer contains a firmware event message it will
 * dispatch the event to a रेजिस्टरed handler (using worker).
 */
व्योम brcmf_fweh_process_event(काष्ठा brcmf_pub *drvr,
			      काष्ठा brcmf_event *event_packet,
			      u32 packet_len, gfp_t gfp)
अणु
	क्रमागत brcmf_fweh_event_code code;
	काष्ठा brcmf_fweh_info *fweh = &drvr->fweh;
	काष्ठा brcmf_fweh_queue_item *event;
	व्योम *data;
	u32 datalen;

	/* get event info */
	code = get_unaligned_be32(&event_packet->msg.event_type);
	datalen = get_unaligned_be32(&event_packet->msg.datalen);
	data = &event_packet[1];

	अगर (code >= BRCMF_E_LAST)
		वापस;

	अगर (code != BRCMF_E_IF && !fweh->evt_handler[code])
		वापस;

	अगर (datalen > BRCMF_DCMD_MAXLEN ||
	    datalen + माप(*event_packet) > packet_len)
		वापस;

	event = kzalloc(माप(*event) + datalen, gfp);
	अगर (!event)
		वापस;

	event->code = code;
	event->अगरidx = event_packet->msg.अगरidx;

	/* use स_नकल to get aligned event message */
	स_नकल(&event->emsg, &event_packet->msg, माप(event->emsg));
	स_नकल(event->data, data, datalen);
	event->datalen = datalen;
	स_नकल(event->अगरaddr, event_packet->eth.h_dest, ETH_ALEN);

	brcmf_fweh_queue_event(fweh, event);
पूर्ण
