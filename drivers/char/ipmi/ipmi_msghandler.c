<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_msghandler.c
 *
 * Incoming and outgoing message routing क्रम an IPMI पूर्णांकerface.
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 */

#घोषणा pr_fmt(fmt) "%s" fmt, "IPMI message handler: "
#घोषणा dev_fmt pr_fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/ipmi.h>
#समावेश <linux/ipmi_smi.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/uuid.h>
#समावेश <linux/nospec.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>

#घोषणा IPMI_DRIVER_VERSION "39.2"

अटल काष्ठा ipmi_recv_msg *ipmi_alloc_recv_msg(व्योम);
अटल पूर्णांक ipmi_init_msghandler(व्योम);
अटल व्योम smi_recv_tasklet(काष्ठा tasklet_काष्ठा *t);
अटल व्योम handle_new_recv_msgs(काष्ठा ipmi_smi *पूर्णांकf);
अटल व्योम need_रुकोer(काष्ठा ipmi_smi *पूर्णांकf);
अटल पूर्णांक handle_one_recv_msg(काष्ठा ipmi_smi *पूर्णांकf,
			       काष्ठा ipmi_smi_msg *msg);

अटल bool initialized;
अटल bool drvरेजिस्टरed;

/* Numbers in this क्रमागतerator should be mapped to ipmi_panic_event_str */
क्रमागत ipmi_panic_event_op अणु
	IPMI_SEND_PANIC_EVENT_NONE,
	IPMI_SEND_PANIC_EVENT,
	IPMI_SEND_PANIC_EVENT_STRING,
	IPMI_SEND_PANIC_EVENT_MAX
पूर्ण;

/* Indices in this array should be mapped to क्रमागत ipmi_panic_event_op */
अटल स्थिर अक्षर *स्थिर ipmi_panic_event_str[] = अणु "none", "event", "string", शून्य पूर्ण;

#अगर_घोषित CONFIG_IPMI_PANIC_STRING
#घोषणा IPMI_PANIC_DEFAULT IPMI_SEND_PANIC_EVENT_STRING
#या_अगर defined(CONFIG_IPMI_PANIC_EVENT)
#घोषणा IPMI_PANIC_DEFAULT IPMI_SEND_PANIC_EVENT
#अन्यथा
#घोषणा IPMI_PANIC_DEFAULT IPMI_SEND_PANIC_EVENT_NONE
#पूर्ण_अगर

अटल क्रमागत ipmi_panic_event_op ipmi_send_panic_event = IPMI_PANIC_DEFAULT;

अटल पूर्णांक panic_op_ग_लिखो_handler(स्थिर अक्षर *val,
				  स्थिर काष्ठा kernel_param *kp)
अणु
	अक्षर valcp[16];
	पूर्णांक e;

	strscpy(valcp, val, माप(valcp));
	e = match_string(ipmi_panic_event_str, -1, म_मालाip(valcp));
	अगर (e < 0)
		वापस e;

	ipmi_send_panic_event = e;
	वापस 0;
पूर्ण

अटल पूर्णांक panic_op_पढ़ो_handler(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	स्थिर अक्षर *event_str;

	अगर (ipmi_send_panic_event >= IPMI_SEND_PANIC_EVENT_MAX)
		event_str = "???";
	अन्यथा
		event_str = ipmi_panic_event_str[ipmi_send_panic_event];

	वापस प्र_लिखो(buffer, "%s\n", event_str);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops panic_op_ops = अणु
	.set = panic_op_ग_लिखो_handler,
	.get = panic_op_पढ़ो_handler
पूर्ण;
module_param_cb(panic_op, &panic_op_ops, शून्य, 0600);
MODULE_PARM_DESC(panic_op, "Sets if the IPMI driver will attempt to store panic information in the event log in the event of a panic.  Set to 'none' for no, 'event' for a single event, or 'string' for a generic event and the panic string in IPMI OEM events.");


#घोषणा MAX_EVENTS_IN_QUEUE	25

/* Reमुख्य in स्वतः-मुख्यtenance mode क्रम this amount of समय (in ms). */
अटल अचिन्हित दीर्घ मुख्यtenance_mode_समयout_ms = 30000;
module_param(मुख्यtenance_mode_समयout_ms, uदीर्घ, 0644);
MODULE_PARM_DESC(मुख्यtenance_mode_समयout_ms,
		 "The time (milliseconds) after the last maintenance message that the connection stays in maintenance mode.");

/*
 * Don't let a message sit in a queue क्रमever, always समय it with at lest
 * the max message समयr.  This is in milliseconds.
 */
#घोषणा MAX_MSG_TIMEOUT		60000

/*
 * Timeout बार below are in milliseconds, and are करोne off a 1
 * second समयr.  So setting the value to 1000 would mean anything
 * between 0 and 1000ms.  So really the only reasonable minimum
 * setting it 2000ms, which is between 1 and 2 seconds.
 */

/* The शेष समयout क्रम message retries. */
अटल अचिन्हित दीर्घ शेष_retry_ms = 2000;
module_param(शेष_retry_ms, uदीर्घ, 0644);
MODULE_PARM_DESC(शेष_retry_ms,
		 "The time (milliseconds) between retry sends");

/* The शेष समयout क्रम मुख्यtenance mode message retries. */
अटल अचिन्हित दीर्घ शेष_मुख्यtenance_retry_ms = 3000;
module_param(शेष_मुख्यtenance_retry_ms, uदीर्घ, 0644);
MODULE_PARM_DESC(शेष_मुख्यtenance_retry_ms,
		 "The time (milliseconds) between retry sends in maintenance mode");

/* The शेष maximum number of retries */
अटल अचिन्हित पूर्णांक शेष_max_retries = 4;
module_param(शेष_max_retries, uपूर्णांक, 0644);
MODULE_PARM_DESC(शेष_max_retries,
		 "The time (milliseconds) between retry sends in maintenance mode");

/* Call every ~1000 ms. */
#घोषणा IPMI_TIMEOUT_TIME	1000

/* How many jअगरfies करोes it take to get to the समयout समय. */
#घोषणा IPMI_TIMEOUT_JIFFIES	((IPMI_TIMEOUT_TIME * HZ) / 1000)

/*
 * Request events from the queue every second (this is the number of
 * IPMI_TIMEOUT_TIMES between event requests).  Hopefully, in the
 * future, IPMI will add a way to know immediately अगर an event is in
 * the queue and this silliness can go away.
 */
#घोषणा IPMI_REQUEST_EV_TIME	(1000 / (IPMI_TIMEOUT_TIME))

/* How दीर्घ should we cache dynamic device IDs? */
#घोषणा IPMI_DYN_DEV_ID_EXPIRY	(10 * HZ)

/*
 * The मुख्य "user" data काष्ठाure.
 */
काष्ठा ipmi_user अणु
	काष्ठा list_head link;

	/*
	 * Set to शून्य when the user is destroyed, a poपूर्णांकer to myself
	 * so srcu_dereference can be used on it.
	 */
	काष्ठा ipmi_user *self;
	काष्ठा srcu_काष्ठा release_barrier;

	काष्ठा kref refcount;

	/* The upper layer that handles receive messages. */
	स्थिर काष्ठा ipmi_user_hndl *handler;
	व्योम             *handler_data;

	/* The पूर्णांकerface this user is bound to. */
	काष्ठा ipmi_smi *पूर्णांकf;

	/* Does this पूर्णांकerface receive IPMI events? */
	bool माला_लो_events;

	/* Free must run in process context क्रम RCU cleanup. */
	काष्ठा work_काष्ठा हटाओ_work;
पूर्ण;

अटल काष्ठा ipmi_user *acquire_ipmi_user(काष्ठा ipmi_user *user, पूर्णांक *index)
	__acquires(user->release_barrier)
अणु
	काष्ठा ipmi_user *ruser;

	*index = srcu_पढ़ो_lock(&user->release_barrier);
	ruser = srcu_dereference(user->self, &user->release_barrier);
	अगर (!ruser)
		srcu_पढ़ो_unlock(&user->release_barrier, *index);
	वापस ruser;
पूर्ण

अटल व्योम release_ipmi_user(काष्ठा ipmi_user *user, पूर्णांक index)
अणु
	srcu_पढ़ो_unlock(&user->release_barrier, index);
पूर्ण

काष्ठा cmd_rcvr अणु
	काष्ठा list_head link;

	काष्ठा ipmi_user *user;
	अचिन्हित अक्षर netfn;
	अचिन्हित अक्षर cmd;
	अचिन्हित पूर्णांक  chans;

	/*
	 * This is used to क्रमm a linked lised during mass deletion.
	 * Since this is in an RCU list, we cannot use the link above
	 * or change any data until the RCU period completes.  So we
	 * use this next variable during mass deletion so we can have
	 * a list and करोn't have to रुको and restart the search on
	 * every inभागidual deletion of a command.
	 */
	काष्ठा cmd_rcvr *next;
पूर्ण;

काष्ठा seq_table अणु
	अचिन्हित पूर्णांक         inuse : 1;
	अचिन्हित पूर्णांक         broadcast : 1;

	अचिन्हित दीर्घ        समयout;
	अचिन्हित दीर्घ        orig_समयout;
	अचिन्हित पूर्णांक         retries_left;

	/*
	 * To verअगरy on an incoming send message response that this is
	 * the message that the response is क्रम, we keep a sequence id
	 * and increment it every समय we send a message.
	 */
	दीर्घ                 seqid;

	/*
	 * This is held so we can properly respond to the message on a
	 * समयout, and it is used to hold the temporary data क्रम
	 * retransmission, too.
	 */
	काष्ठा ipmi_recv_msg *recv_msg;
पूर्ण;

/*
 * Store the inक्रमmation in a msgid (दीर्घ) to allow us to find a
 * sequence table entry from the msgid.
 */
#घोषणा STORE_SEQ_IN_MSGID(seq, seqid) \
	((((seq) & 0x3f) << 26) | ((seqid) & 0x3ffffff))

#घोषणा GET_SEQ_FROM_MSGID(msgid, seq, seqid) \
	करो अणु								\
		seq = (((msgid) >> 26) & 0x3f);				\
		seqid = ((msgid) & 0x3ffffff);				\
	पूर्ण जबतक (0)

#घोषणा NEXT_SEQID(seqid) (((seqid) + 1) & 0x3ffffff)

#घोषणा IPMI_MAX_CHANNELS       16
काष्ठा ipmi_channel अणु
	अचिन्हित अक्षर medium;
	अचिन्हित अक्षर protocol;
पूर्ण;

काष्ठा ipmi_channel_set अणु
	काष्ठा ipmi_channel c[IPMI_MAX_CHANNELS];
पूर्ण;

काष्ठा ipmi_my_addrinfo अणु
	/*
	 * My slave address.  This is initialized to IPMI_BMC_SLAVE_ADDR,
	 * but may be changed by the user.
	 */
	अचिन्हित अक्षर address;

	/*
	 * My LUN.  This should generally stay the SMS LUN, but just in
	 * हाल...
	 */
	अचिन्हित अक्षर lun;
पूर्ण;

/*
 * Note that the product id, manufacturer id, guid, and device id are
 * immutable in this काष्ठाure, so dyn_mutex is not required क्रम
 * accessing those.  If those change on a BMC, a new BMC is allocated.
 */
काष्ठा bmc_device अणु
	काष्ठा platक्रमm_device pdev;
	काष्ठा list_head       पूर्णांकfs; /* Interfaces on this BMC. */
	काष्ठा ipmi_device_id  id;
	काष्ठा ipmi_device_id  fetch_id;
	पूर्णांक                    dyn_id_set;
	अचिन्हित दीर्घ          dyn_id_expiry;
	काष्ठा mutex           dyn_mutex; /* Protects id, पूर्णांकfs, & dyn* */
	guid_t                 guid;
	guid_t                 fetch_guid;
	पूर्णांक                    dyn_guid_set;
	काष्ठा kref	       usecount;
	काष्ठा work_काष्ठा     हटाओ_work;
	अचिन्हित अक्षर	       cc; /* completion code */
पूर्ण;
#घोषणा to_bmc_device(x) container_of((x), काष्ठा bmc_device, pdev.dev)

अटल पूर्णांक bmc_get_device_id(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा bmc_device *bmc,
			     काष्ठा ipmi_device_id *id,
			     bool *guid_set, guid_t *guid);

/*
 * Various statistics क्रम IPMI, these index stats[] in the ipmi_smi
 * काष्ठाure.
 */
क्रमागत ipmi_stat_indexes अणु
	/* Commands we got from the user that were invalid. */
	IPMI_STAT_sent_invalid_commands = 0,

	/* Commands we sent to the MC. */
	IPMI_STAT_sent_local_commands,

	/* Responses from the MC that were delivered to a user. */
	IPMI_STAT_handled_local_responses,

	/* Responses from the MC that were not delivered to a user. */
	IPMI_STAT_unhandled_local_responses,

	/* Commands we sent out to the IPMB bus. */
	IPMI_STAT_sent_ipmb_commands,

	/* Commands sent on the IPMB that had errors on the SEND CMD */
	IPMI_STAT_sent_ipmb_command_errs,

	/* Each retransmit increments this count. */
	IPMI_STAT_retransmitted_ipmb_commands,

	/*
	 * When a message बार out (runs out of retransmits) this is
	 * incremented.
	 */
	IPMI_STAT_समयd_out_ipmb_commands,

	/*
	 * This is like above, but क्रम broadcasts.  Broadcasts are
	 * *not* included in the above count (they are expected to
	 * समय out).
	 */
	IPMI_STAT_समयd_out_ipmb_broadcasts,

	/* Responses I have sent to the IPMB bus. */
	IPMI_STAT_sent_ipmb_responses,

	/* The response was delivered to the user. */
	IPMI_STAT_handled_ipmb_responses,

	/* The response had invalid data in it. */
	IPMI_STAT_invalid_ipmb_responses,

	/* The response didn't have anyone रुकोing क्रम it. */
	IPMI_STAT_unhandled_ipmb_responses,

	/* Commands we sent out to the IPMB bus. */
	IPMI_STAT_sent_lan_commands,

	/* Commands sent on the IPMB that had errors on the SEND CMD */
	IPMI_STAT_sent_lan_command_errs,

	/* Each retransmit increments this count. */
	IPMI_STAT_retransmitted_lan_commands,

	/*
	 * When a message बार out (runs out of retransmits) this is
	 * incremented.
	 */
	IPMI_STAT_समयd_out_lan_commands,

	/* Responses I have sent to the IPMB bus. */
	IPMI_STAT_sent_lan_responses,

	/* The response was delivered to the user. */
	IPMI_STAT_handled_lan_responses,

	/* The response had invalid data in it. */
	IPMI_STAT_invalid_lan_responses,

	/* The response didn't have anyone रुकोing क्रम it. */
	IPMI_STAT_unhandled_lan_responses,

	/* The command was delivered to the user. */
	IPMI_STAT_handled_commands,

	/* The command had invalid data in it. */
	IPMI_STAT_invalid_commands,

	/* The command didn't have anyone रुकोing क्रम it. */
	IPMI_STAT_unhandled_commands,

	/* Invalid data in an event. */
	IPMI_STAT_invalid_events,

	/* Events that were received with the proper क्रमmat. */
	IPMI_STAT_events,

	/* Retransmissions on IPMB that failed. */
	IPMI_STAT_dropped_rexmit_ipmb_commands,

	/* Retransmissions on LAN that failed. */
	IPMI_STAT_dropped_rexmit_lan_commands,

	/* This *must* reमुख्य last, add new values above this. */
	IPMI_NUM_STATS
पूर्ण;


#घोषणा IPMI_IPMB_NUM_SEQ	64
काष्ठा ipmi_smi अणु
	काष्ठा module *owner;

	/* What पूर्णांकerface number are we? */
	पूर्णांक पूर्णांकf_num;

	काष्ठा kref refcount;

	/* Set when the पूर्णांकerface is being unरेजिस्टरed. */
	bool in_shutकरोwn;

	/* Used क्रम a list of पूर्णांकerfaces. */
	काष्ठा list_head link;

	/*
	 * The list of upper layers that are using me.  seq_lock ग_लिखो
	 * protects this.  Read protection is with srcu.
	 */
	काष्ठा list_head users;
	काष्ठा srcu_काष्ठा users_srcu;

	/* Used क्रम wake ups at startup. */
	रुको_queue_head_t रुकोq;

	/*
	 * Prevents the पूर्णांकerface from being unरेजिस्टरed when the
	 * पूर्णांकerface is used by being looked up through the BMC
	 * काष्ठाure.
	 */
	काष्ठा mutex bmc_reg_mutex;

	काष्ठा bmc_device पंचांगp_bmc;
	काष्ठा bmc_device *bmc;
	bool bmc_रेजिस्टरed;
	काष्ठा list_head bmc_link;
	अक्षर *my_dev_name;
	bool in_bmc_रेजिस्टर;  /* Handle recursive situations.  Yuck. */
	काष्ठा work_काष्ठा bmc_reg_work;

	स्थिर काष्ठा ipmi_smi_handlers *handlers;
	व्योम                     *send_info;

	/* Driver-model device क्रम the प्रणाली पूर्णांकerface. */
	काष्ठा device          *si_dev;

	/*
	 * A table of sequence numbers क्रम this पूर्णांकerface.  We use the
	 * sequence numbers क्रम IPMB messages that go out of the
	 * पूर्णांकerface to match them up with their responses.  A routine
	 * is called periodically to समय the items in this list.
	 */
	spinlock_t       seq_lock;
	काष्ठा seq_table seq_table[IPMI_IPMB_NUM_SEQ];
	पूर्णांक curr_seq;

	/*
	 * Messages queued क्रम delivery.  If delivery fails (out of memory
	 * क्रम instance), They will stay in here to be processed later in a
	 * periodic समयr पूर्णांकerrupt.  The tasklet is क्रम handling received
	 * messages directly from the handler.
	 */
	spinlock_t       रुकोing_rcv_msgs_lock;
	काष्ठा list_head रुकोing_rcv_msgs;
	atomic_t	 watchकरोg_preसमयouts_to_deliver;
	काष्ठा tasklet_काष्ठा recv_tasklet;

	spinlock_t             xmit_msgs_lock;
	काष्ठा list_head       xmit_msgs;
	काष्ठा ipmi_smi_msg    *curr_msg;
	काष्ठा list_head       hp_xmit_msgs;

	/*
	 * The list of command receivers that are रेजिस्टरed क्रम commands
	 * on this पूर्णांकerface.
	 */
	काष्ठा mutex     cmd_rcvrs_mutex;
	काष्ठा list_head cmd_rcvrs;

	/*
	 * Events that were queues because no one was there to receive
	 * them.
	 */
	spinlock_t       events_lock; /* For dealing with event stuff. */
	काष्ठा list_head रुकोing_events;
	अचिन्हित पूर्णांक     रुकोing_events_count; /* How many events in queue? */
	अक्षर             delivering_events;
	अक्षर             event_msg_prपूर्णांकed;

	/* How many users are रुकोing क्रम events? */
	atomic_t         event_रुकोers;
	अचिन्हित पूर्णांक     ticks_to_req_ev;

	spinlock_t       watch_lock; /* For dealing with watch stuff below. */

	/* How many users are रुकोing क्रम commands? */
	अचिन्हित पूर्णांक     command_रुकोers;

	/* How many users are रुकोing क्रम watchकरोgs? */
	अचिन्हित पूर्णांक     watchकरोg_रुकोers;

	/* How many users are रुकोing क्रम message responses? */
	अचिन्हित पूर्णांक     response_रुकोers;

	/*
	 * Tells what the lower layer has last been asked to watch क्रम,
	 * messages and/or watchकरोgs.  Protected by watch_lock.
	 */
	अचिन्हित पूर्णांक     last_watch_mask;

	/*
	 * The event receiver क्रम my BMC, only really used at panic
	 * shutकरोwn as a place to store this.
	 */
	अचिन्हित अक्षर event_receiver;
	अचिन्हित अक्षर event_receiver_lun;
	अचिन्हित अक्षर local_sel_device;
	अचिन्हित अक्षर local_event_generator;

	/* For handling of मुख्यtenance mode. */
	पूर्णांक मुख्यtenance_mode;
	bool मुख्यtenance_mode_enable;
	पूर्णांक स्वतः_मुख्यtenance_समयout;
	spinlock_t मुख्यtenance_mode_lock; /* Used in a समयr... */

	/*
	 * If we are करोing मुख्यtenance on something on IPMB, extend
	 * the समयout समय to aव्योम समयouts writing firmware and
	 * such.
	 */
	पूर्णांक ipmb_मुख्यtenance_mode_समयout;

	/*
	 * A cheap hack, अगर this is non-null and a message to an
	 * पूर्णांकerface comes in with a शून्य user, call this routine with
	 * it.  Note that the message will still be मुक्तd by the
	 * caller.  This only works on the प्रणाली पूर्णांकerface.
	 *
	 * Protected by bmc_reg_mutex.
	 */
	व्योम (*null_user_handler)(काष्ठा ipmi_smi *पूर्णांकf,
				  काष्ठा ipmi_recv_msg *msg);

	/*
	 * When we are scanning the channels क्रम an SMI, this will
	 * tell which channel we are scanning.
	 */
	पूर्णांक curr_channel;

	/* Channel inक्रमmation */
	काष्ठा ipmi_channel_set *channel_list;
	अचिन्हित पूर्णांक curr_working_cset; /* First index पूर्णांकo the following. */
	काष्ठा ipmi_channel_set wchannels[2];
	काष्ठा ipmi_my_addrinfo addrinfo[IPMI_MAX_CHANNELS];
	bool channels_पढ़ोy;

	atomic_t stats[IPMI_NUM_STATS];

	/*
	 * run_to_completion duplicate of smb_info, smi_info
	 * and ipmi_serial_info काष्ठाures. Used to decrease numbers of
	 * parameters passed by "low" level IPMI code.
	 */
	पूर्णांक run_to_completion;
पूर्ण;
#घोषणा to_si_पूर्णांकf_from_dev(device) container_of(device, काष्ठा ipmi_smi, dev)

अटल व्योम __get_guid(काष्ठा ipmi_smi *पूर्णांकf);
अटल व्योम __ipmi_bmc_unरेजिस्टर(काष्ठा ipmi_smi *पूर्णांकf);
अटल पूर्णांक __ipmi_bmc_रेजिस्टर(काष्ठा ipmi_smi *पूर्णांकf,
			       काष्ठा ipmi_device_id *id,
			       bool guid_set, guid_t *guid, पूर्णांक पूर्णांकf_num);
अटल पूर्णांक __scan_channels(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा ipmi_device_id *id);


/**
 * The driver model view of the IPMI messaging driver.
 */
अटल काष्ठा platक्रमm_driver ipmidriver = अणु
	.driver = अणु
		.name = "ipmi",
		.bus = &platक्रमm_bus_type
	पूर्ण
पूर्ण;
/*
 * This mutex keeps us from adding the same BMC twice.
 */
अटल DEFINE_MUTEX(ipmidriver_mutex);

अटल LIST_HEAD(ipmi_पूर्णांकerfaces);
अटल DEFINE_MUTEX(ipmi_पूर्णांकerfaces_mutex);
#घोषणा ipmi_पूर्णांकerfaces_mutex_held() \
	lockdep_is_held(&ipmi_पूर्णांकerfaces_mutex)
अटल काष्ठा srcu_काष्ठा ipmi_पूर्णांकerfaces_srcu;

/*
 * List of watchers that want to know when smi's are added and deleted.
 */
अटल LIST_HEAD(smi_watchers);
अटल DEFINE_MUTEX(smi_watchers_mutex);

#घोषणा ipmi_inc_stat(पूर्णांकf, stat) \
	atomic_inc(&(पूर्णांकf)->stats[IPMI_STAT_ ## stat])
#घोषणा ipmi_get_stat(पूर्णांकf, stat) \
	((अचिन्हित पूर्णांक) atomic_पढ़ो(&(पूर्णांकf)->stats[IPMI_STAT_ ## stat]))

अटल स्थिर अक्षर * स्थिर addr_src_to_str[] = अणु
	"invalid", "hotmod", "hardcoded", "SPMI", "ACPI", "SMBIOS", "PCI",
	"device-tree", "platform"
पूर्ण;

स्थिर अक्षर *ipmi_addr_src_to_str(क्रमागत ipmi_addr_src src)
अणु
	अगर (src >= SI_LAST)
		src = 0; /* Invalid */
	वापस addr_src_to_str[src];
पूर्ण
EXPORT_SYMBOL(ipmi_addr_src_to_str);

अटल पूर्णांक is_lan_addr(काष्ठा ipmi_addr *addr)
अणु
	वापस addr->addr_type == IPMI_LAN_ADDR_TYPE;
पूर्ण

अटल पूर्णांक is_ipmb_addr(काष्ठा ipmi_addr *addr)
अणु
	वापस addr->addr_type == IPMI_IPMB_ADDR_TYPE;
पूर्ण

अटल पूर्णांक is_ipmb_bcast_addr(काष्ठा ipmi_addr *addr)
अणु
	वापस addr->addr_type == IPMI_IPMB_BROADCAST_ADDR_TYPE;
पूर्ण

अटल व्योम मुक्त_recv_msg_list(काष्ठा list_head *q)
अणु
	काष्ठा ipmi_recv_msg *msg, *msg2;

	list_क्रम_each_entry_safe(msg, msg2, q, link) अणु
		list_del(&msg->link);
		ipmi_मुक्त_recv_msg(msg);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_smi_msg_list(काष्ठा list_head *q)
अणु
	काष्ठा ipmi_smi_msg *msg, *msg2;

	list_क्रम_each_entry_safe(msg, msg2, q, link) अणु
		list_del(&msg->link);
		ipmi_मुक्त_smi_msg(msg);
	पूर्ण
पूर्ण

अटल व्योम clean_up_पूर्णांकerface_data(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	पूर्णांक              i;
	काष्ठा cmd_rcvr  *rcvr, *rcvr2;
	काष्ठा list_head list;

	tasklet_समाप्त(&पूर्णांकf->recv_tasklet);

	मुक्त_smi_msg_list(&पूर्णांकf->रुकोing_rcv_msgs);
	मुक्त_recv_msg_list(&पूर्णांकf->रुकोing_events);

	/*
	 * Wholesale हटाओ all the entries from the list in the
	 * पूर्णांकerface and रुको क्रम RCU to know that none are in use.
	 */
	mutex_lock(&पूर्णांकf->cmd_rcvrs_mutex);
	INIT_LIST_HEAD(&list);
	list_splice_init_rcu(&पूर्णांकf->cmd_rcvrs, &list, synchronize_rcu);
	mutex_unlock(&पूर्णांकf->cmd_rcvrs_mutex);

	list_क्रम_each_entry_safe(rcvr, rcvr2, &list, link)
		kमुक्त(rcvr);

	क्रम (i = 0; i < IPMI_IPMB_NUM_SEQ; i++) अणु
		अगर ((पूर्णांकf->seq_table[i].inuse)
					&& (पूर्णांकf->seq_table[i].recv_msg))
			ipmi_मुक्त_recv_msg(पूर्णांकf->seq_table[i].recv_msg);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकf_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा ipmi_smi *पूर्णांकf = container_of(ref, काष्ठा ipmi_smi, refcount);

	clean_up_पूर्णांकerface_data(पूर्णांकf);
	kमुक्त(पूर्णांकf);
पूर्ण

काष्ठा watcher_entry अणु
	पूर्णांक              पूर्णांकf_num;
	काष्ठा ipmi_smi  *पूर्णांकf;
	काष्ठा list_head link;
पूर्ण;

पूर्णांक ipmi_smi_watcher_रेजिस्टर(काष्ठा ipmi_smi_watcher *watcher)
अणु
	काष्ठा ipmi_smi *पूर्णांकf;
	पूर्णांक index, rv;

	/*
	 * Make sure the driver is actually initialized, this handles
	 * problems with initialization order.
	 */
	rv = ipmi_init_msghandler();
	अगर (rv)
		वापस rv;

	mutex_lock(&smi_watchers_mutex);

	list_add(&watcher->link, &smi_watchers);

	index = srcu_पढ़ो_lock(&ipmi_पूर्णांकerfaces_srcu);
	list_क्रम_each_entry_rcu(पूर्णांकf, &ipmi_पूर्णांकerfaces, link,
			lockdep_is_held(&smi_watchers_mutex)) अणु
		पूर्णांक पूर्णांकf_num = READ_ONCE(पूर्णांकf->पूर्णांकf_num);

		अगर (पूर्णांकf_num == -1)
			जारी;
		watcher->new_smi(पूर्णांकf_num, पूर्णांकf->si_dev);
	पूर्ण
	srcu_पढ़ो_unlock(&ipmi_पूर्णांकerfaces_srcu, index);

	mutex_unlock(&smi_watchers_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ipmi_smi_watcher_रेजिस्टर);

पूर्णांक ipmi_smi_watcher_unरेजिस्टर(काष्ठा ipmi_smi_watcher *watcher)
अणु
	mutex_lock(&smi_watchers_mutex);
	list_del(&watcher->link);
	mutex_unlock(&smi_watchers_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ipmi_smi_watcher_unरेजिस्टर);

/*
 * Must be called with smi_watchers_mutex held.
 */
अटल व्योम
call_smi_watchers(पूर्णांक i, काष्ठा device *dev)
अणु
	काष्ठा ipmi_smi_watcher *w;

	mutex_lock(&smi_watchers_mutex);
	list_क्रम_each_entry(w, &smi_watchers, link) अणु
		अगर (try_module_get(w->owner)) अणु
			w->new_smi(i, dev);
			module_put(w->owner);
		पूर्ण
	पूर्ण
	mutex_unlock(&smi_watchers_mutex);
पूर्ण

अटल पूर्णांक
ipmi_addr_equal(काष्ठा ipmi_addr *addr1, काष्ठा ipmi_addr *addr2)
अणु
	अगर (addr1->addr_type != addr2->addr_type)
		वापस 0;

	अगर (addr1->channel != addr2->channel)
		वापस 0;

	अगर (addr1->addr_type == IPMI_SYSTEM_INTERFACE_ADDR_TYPE) अणु
		काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *smi_addr1
		    = (काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *) addr1;
		काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *smi_addr2
		    = (काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *) addr2;
		वापस (smi_addr1->lun == smi_addr2->lun);
	पूर्ण

	अगर (is_ipmb_addr(addr1) || is_ipmb_bcast_addr(addr1)) अणु
		काष्ठा ipmi_ipmb_addr *ipmb_addr1
		    = (काष्ठा ipmi_ipmb_addr *) addr1;
		काष्ठा ipmi_ipmb_addr *ipmb_addr2
		    = (काष्ठा ipmi_ipmb_addr *) addr2;

		वापस ((ipmb_addr1->slave_addr == ipmb_addr2->slave_addr)
			&& (ipmb_addr1->lun == ipmb_addr2->lun));
	पूर्ण

	अगर (is_lan_addr(addr1)) अणु
		काष्ठा ipmi_lan_addr *lan_addr1
			= (काष्ठा ipmi_lan_addr *) addr1;
		काष्ठा ipmi_lan_addr *lan_addr2
		    = (काष्ठा ipmi_lan_addr *) addr2;

		वापस ((lan_addr1->remote_SWID == lan_addr2->remote_SWID)
			&& (lan_addr1->local_SWID == lan_addr2->local_SWID)
			&& (lan_addr1->session_handle
			    == lan_addr2->session_handle)
			&& (lan_addr1->lun == lan_addr2->lun));
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक ipmi_validate_addr(काष्ठा ipmi_addr *addr, पूर्णांक len)
अणु
	अगर (len < माप(काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr))
		वापस -EINVAL;

	अगर (addr->addr_type == IPMI_SYSTEM_INTERFACE_ADDR_TYPE) अणु
		अगर (addr->channel != IPMI_BMC_CHANNEL)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	अगर ((addr->channel == IPMI_BMC_CHANNEL)
	    || (addr->channel >= IPMI_MAX_CHANNELS)
	    || (addr->channel < 0))
		वापस -EINVAL;

	अगर (is_ipmb_addr(addr) || is_ipmb_bcast_addr(addr)) अणु
		अगर (len < माप(काष्ठा ipmi_ipmb_addr))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	अगर (is_lan_addr(addr)) अणु
		अगर (len < माप(काष्ठा ipmi_lan_addr))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(ipmi_validate_addr);

अचिन्हित पूर्णांक ipmi_addr_length(पूर्णांक addr_type)
अणु
	अगर (addr_type == IPMI_SYSTEM_INTERFACE_ADDR_TYPE)
		वापस माप(काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr);

	अगर ((addr_type == IPMI_IPMB_ADDR_TYPE)
			|| (addr_type == IPMI_IPMB_BROADCAST_ADDR_TYPE))
		वापस माप(काष्ठा ipmi_ipmb_addr);

	अगर (addr_type == IPMI_LAN_ADDR_TYPE)
		वापस माप(काष्ठा ipmi_lan_addr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ipmi_addr_length);

अटल पूर्णांक deliver_response(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा ipmi_recv_msg *msg)
अणु
	पूर्णांक rv = 0;

	अगर (!msg->user) अणु
		/* Special handling क्रम शून्य users. */
		अगर (पूर्णांकf->null_user_handler) अणु
			पूर्णांकf->null_user_handler(पूर्णांकf, msg);
		पूर्ण अन्यथा अणु
			/* No handler, so give up. */
			rv = -EINVAL;
		पूर्ण
		ipmi_मुक्त_recv_msg(msg);
	पूर्ण अन्यथा अगर (oops_in_progress) अणु
		/*
		 * If we are running in the panic context, calling the
		 * receive handler करोesn't much meaning and has a deadlock
		 * risk.  At this moment, simply skip it in that हाल.
		 */
		ipmi_मुक्त_recv_msg(msg);
	पूर्ण अन्यथा अणु
		पूर्णांक index;
		काष्ठा ipmi_user *user = acquire_ipmi_user(msg->user, &index);

		अगर (user) अणु
			user->handler->ipmi_recv_hndl(msg, user->handler_data);
			release_ipmi_user(user, index);
		पूर्ण अन्यथा अणु
			/* User went away, give up. */
			ipmi_मुक्त_recv_msg(msg);
			rv = -EINVAL;
		पूर्ण
	पूर्ण

	वापस rv;
पूर्ण

अटल व्योम deliver_local_response(काष्ठा ipmi_smi *पूर्णांकf,
				   काष्ठा ipmi_recv_msg *msg)
अणु
	अगर (deliver_response(पूर्णांकf, msg))
		ipmi_inc_stat(पूर्णांकf, unhandled_local_responses);
	अन्यथा
		ipmi_inc_stat(पूर्णांकf, handled_local_responses);
पूर्ण

अटल व्योम deliver_err_response(काष्ठा ipmi_smi *पूर्णांकf,
				 काष्ठा ipmi_recv_msg *msg, पूर्णांक err)
अणु
	msg->recv_type = IPMI_RESPONSE_RECV_TYPE;
	msg->msg_data[0] = err;
	msg->msg.netfn |= 1; /* Convert to a response. */
	msg->msg.data_len = 1;
	msg->msg.data = msg->msg_data;
	deliver_local_response(पूर्णांकf, msg);
पूर्ण

अटल व्योम smi_add_watch(काष्ठा ipmi_smi *पूर्णांकf, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित दीर्घ अगरlags;

	अगर (!पूर्णांकf->handlers->set_need_watch)
		वापस;

	spin_lock_irqsave(&पूर्णांकf->watch_lock, अगरlags);
	अगर (flags & IPMI_WATCH_MASK_CHECK_MESSAGES)
		पूर्णांकf->response_रुकोers++;

	अगर (flags & IPMI_WATCH_MASK_CHECK_WATCHDOG)
		पूर्णांकf->watchकरोg_रुकोers++;

	अगर (flags & IPMI_WATCH_MASK_CHECK_COMMANDS)
		पूर्णांकf->command_रुकोers++;

	अगर ((पूर्णांकf->last_watch_mask & flags) != flags) अणु
		पूर्णांकf->last_watch_mask |= flags;
		पूर्णांकf->handlers->set_need_watch(पूर्णांकf->send_info,
					       पूर्णांकf->last_watch_mask);
	पूर्ण
	spin_unlock_irqrestore(&पूर्णांकf->watch_lock, अगरlags);
पूर्ण

अटल व्योम smi_हटाओ_watch(काष्ठा ipmi_smi *पूर्णांकf, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित दीर्घ अगरlags;

	अगर (!पूर्णांकf->handlers->set_need_watch)
		वापस;

	spin_lock_irqsave(&पूर्णांकf->watch_lock, अगरlags);
	अगर (flags & IPMI_WATCH_MASK_CHECK_MESSAGES)
		पूर्णांकf->response_रुकोers--;

	अगर (flags & IPMI_WATCH_MASK_CHECK_WATCHDOG)
		पूर्णांकf->watchकरोg_रुकोers--;

	अगर (flags & IPMI_WATCH_MASK_CHECK_COMMANDS)
		पूर्णांकf->command_रुकोers--;

	flags = 0;
	अगर (पूर्णांकf->response_रुकोers)
		flags |= IPMI_WATCH_MASK_CHECK_MESSAGES;
	अगर (पूर्णांकf->watchकरोg_रुकोers)
		flags |= IPMI_WATCH_MASK_CHECK_WATCHDOG;
	अगर (पूर्णांकf->command_रुकोers)
		flags |= IPMI_WATCH_MASK_CHECK_COMMANDS;

	अगर (पूर्णांकf->last_watch_mask != flags) अणु
		पूर्णांकf->last_watch_mask = flags;
		पूर्णांकf->handlers->set_need_watch(पूर्णांकf->send_info,
					       पूर्णांकf->last_watch_mask);
	पूर्ण
	spin_unlock_irqrestore(&पूर्णांकf->watch_lock, अगरlags);
पूर्ण

/*
 * Find the next sequence number not being used and add the given
 * message with the given समयout to the sequence table.  This must be
 * called with the पूर्णांकerface's seq_lock held.
 */
अटल पूर्णांक पूर्णांकf_next_seq(काष्ठा ipmi_smi      *पूर्णांकf,
			 काष्ठा ipmi_recv_msg *recv_msg,
			 अचिन्हित दीर्घ        समयout,
			 पूर्णांक                  retries,
			 पूर्णांक                  broadcast,
			 अचिन्हित अक्षर        *seq,
			 दीर्घ                 *seqid)
अणु
	पूर्णांक          rv = 0;
	अचिन्हित पूर्णांक i;

	अगर (समयout == 0)
		समयout = शेष_retry_ms;
	अगर (retries < 0)
		retries = शेष_max_retries;

	क्रम (i = पूर्णांकf->curr_seq; (i+1)%IPMI_IPMB_NUM_SEQ != पूर्णांकf->curr_seq;
					i = (i+1)%IPMI_IPMB_NUM_SEQ) अणु
		अगर (!पूर्णांकf->seq_table[i].inuse)
			अवरोध;
	पूर्ण

	अगर (!पूर्णांकf->seq_table[i].inuse) अणु
		पूर्णांकf->seq_table[i].recv_msg = recv_msg;

		/*
		 * Start with the maximum समयout, when the send response
		 * comes in we will start the real समयr.
		 */
		पूर्णांकf->seq_table[i].समयout = MAX_MSG_TIMEOUT;
		पूर्णांकf->seq_table[i].orig_समयout = समयout;
		पूर्णांकf->seq_table[i].retries_left = retries;
		पूर्णांकf->seq_table[i].broadcast = broadcast;
		पूर्णांकf->seq_table[i].inuse = 1;
		पूर्णांकf->seq_table[i].seqid = NEXT_SEQID(पूर्णांकf->seq_table[i].seqid);
		*seq = i;
		*seqid = पूर्णांकf->seq_table[i].seqid;
		पूर्णांकf->curr_seq = (i+1)%IPMI_IPMB_NUM_SEQ;
		smi_add_watch(पूर्णांकf, IPMI_WATCH_MASK_CHECK_MESSAGES);
		need_रुकोer(पूर्णांकf);
	पूर्ण अन्यथा अणु
		rv = -EAGAIN;
	पूर्ण

	वापस rv;
पूर्ण

/*
 * Return the receive message क्रम the given sequence number and
 * release the sequence number so it can be reused.  Some other data
 * is passed in to be sure the message matches up correctly (to help
 * guard against message coming in after their समयout and the
 * sequence number being reused).
 */
अटल पूर्णांक पूर्णांकf_find_seq(काष्ठा ipmi_smi      *पूर्णांकf,
			 अचिन्हित अक्षर        seq,
			 लघु                channel,
			 अचिन्हित अक्षर        cmd,
			 अचिन्हित अक्षर        netfn,
			 काष्ठा ipmi_addr     *addr,
			 काष्ठा ipmi_recv_msg **recv_msg)
अणु
	पूर्णांक           rv = -ENODEV;
	अचिन्हित दीर्घ flags;

	अगर (seq >= IPMI_IPMB_NUM_SEQ)
		वापस -EINVAL;

	spin_lock_irqsave(&पूर्णांकf->seq_lock, flags);
	अगर (पूर्णांकf->seq_table[seq].inuse) अणु
		काष्ठा ipmi_recv_msg *msg = पूर्णांकf->seq_table[seq].recv_msg;

		अगर ((msg->addr.channel == channel) && (msg->msg.cmd == cmd)
				&& (msg->msg.netfn == netfn)
				&& (ipmi_addr_equal(addr, &msg->addr))) अणु
			*recv_msg = msg;
			पूर्णांकf->seq_table[seq].inuse = 0;
			smi_हटाओ_watch(पूर्णांकf, IPMI_WATCH_MASK_CHECK_MESSAGES);
			rv = 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&पूर्णांकf->seq_lock, flags);

	वापस rv;
पूर्ण


/* Start the समयr क्रम a specअगरic sequence table entry. */
अटल पूर्णांक पूर्णांकf_start_seq_समयr(काष्ठा ipmi_smi *पूर्णांकf,
				दीर्घ       msgid)
अणु
	पूर्णांक           rv = -ENODEV;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर seq;
	अचिन्हित दीर्घ seqid;


	GET_SEQ_FROM_MSGID(msgid, seq, seqid);

	spin_lock_irqsave(&पूर्णांकf->seq_lock, flags);
	/*
	 * We करो this verअगरication because the user can be deleted
	 * जबतक a message is outstanding.
	 */
	अगर ((पूर्णांकf->seq_table[seq].inuse)
				&& (पूर्णांकf->seq_table[seq].seqid == seqid)) अणु
		काष्ठा seq_table *ent = &पूर्णांकf->seq_table[seq];
		ent->समयout = ent->orig_समयout;
		rv = 0;
	पूर्ण
	spin_unlock_irqrestore(&पूर्णांकf->seq_lock, flags);

	वापस rv;
पूर्ण

/* Got an error क्रम the send message क्रम a specअगरic sequence number. */
अटल पूर्णांक पूर्णांकf_err_seq(काष्ठा ipmi_smi *पूर्णांकf,
			दीर्घ         msgid,
			अचिन्हित पूर्णांक err)
अणु
	पूर्णांक                  rv = -ENODEV;
	अचिन्हित दीर्घ        flags;
	अचिन्हित अक्षर        seq;
	अचिन्हित दीर्घ        seqid;
	काष्ठा ipmi_recv_msg *msg = शून्य;


	GET_SEQ_FROM_MSGID(msgid, seq, seqid);

	spin_lock_irqsave(&पूर्णांकf->seq_lock, flags);
	/*
	 * We करो this verअगरication because the user can be deleted
	 * जबतक a message is outstanding.
	 */
	अगर ((पूर्णांकf->seq_table[seq].inuse)
				&& (पूर्णांकf->seq_table[seq].seqid == seqid)) अणु
		काष्ठा seq_table *ent = &पूर्णांकf->seq_table[seq];

		ent->inuse = 0;
		smi_हटाओ_watch(पूर्णांकf, IPMI_WATCH_MASK_CHECK_MESSAGES);
		msg = ent->recv_msg;
		rv = 0;
	पूर्ण
	spin_unlock_irqrestore(&पूर्णांकf->seq_lock, flags);

	अगर (msg)
		deliver_err_response(पूर्णांकf, msg, err);

	वापस rv;
पूर्ण

अटल व्योम मुक्त_user_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipmi_user *user = container_of(work, काष्ठा ipmi_user,
					      हटाओ_work);

	cleanup_srcu_काष्ठा(&user->release_barrier);
	vमुक्त(user);
पूर्ण

पूर्णांक ipmi_create_user(अचिन्हित पूर्णांक          अगर_num,
		     स्थिर काष्ठा ipmi_user_hndl *handler,
		     व्योम                  *handler_data,
		     काष्ठा ipmi_user      **user)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ipmi_user *new_user;
	पूर्णांक           rv, index;
	काष्ठा ipmi_smi *पूर्णांकf;

	/*
	 * There is no module usecount here, because it's not
	 * required.  Since this can only be used by and called from
	 * other modules, they will implicitly use this module, and
	 * thus this can't be हटाओd unless the other modules are
	 * हटाओd.
	 */

	अगर (handler == शून्य)
		वापस -EINVAL;

	/*
	 * Make sure the driver is actually initialized, this handles
	 * problems with initialization order.
	 */
	rv = ipmi_init_msghandler();
	अगर (rv)
		वापस rv;

	new_user = vzalloc(माप(*new_user));
	अगर (!new_user)
		वापस -ENOMEM;

	index = srcu_पढ़ो_lock(&ipmi_पूर्णांकerfaces_srcu);
	list_क्रम_each_entry_rcu(पूर्णांकf, &ipmi_पूर्णांकerfaces, link) अणु
		अगर (पूर्णांकf->पूर्णांकf_num == अगर_num)
			जाओ found;
	पूर्ण
	/* Not found, वापस an error */
	rv = -EINVAL;
	जाओ out_kमुक्त;

 found:
	INIT_WORK(&new_user->हटाओ_work, मुक्त_user_work);

	rv = init_srcu_काष्ठा(&new_user->release_barrier);
	अगर (rv)
		जाओ out_kमुक्त;

	अगर (!try_module_get(पूर्णांकf->owner)) अणु
		rv = -ENODEV;
		जाओ out_kमुक्त;
	पूर्ण

	/* Note that each existing user holds a refcount to the पूर्णांकerface. */
	kref_get(&पूर्णांकf->refcount);

	kref_init(&new_user->refcount);
	new_user->handler = handler;
	new_user->handler_data = handler_data;
	new_user->पूर्णांकf = पूर्णांकf;
	new_user->माला_लो_events = false;

	rcu_assign_poपूर्णांकer(new_user->self, new_user);
	spin_lock_irqsave(&पूर्णांकf->seq_lock, flags);
	list_add_rcu(&new_user->link, &पूर्णांकf->users);
	spin_unlock_irqrestore(&पूर्णांकf->seq_lock, flags);
	अगर (handler->ipmi_watchकरोg_preसमयout)
		/* User wants preसमयouts, so make sure to watch क्रम them. */
		smi_add_watch(पूर्णांकf, IPMI_WATCH_MASK_CHECK_WATCHDOG);
	srcu_पढ़ो_unlock(&ipmi_पूर्णांकerfaces_srcu, index);
	*user = new_user;
	वापस 0;

out_kमुक्त:
	srcu_पढ़ो_unlock(&ipmi_पूर्णांकerfaces_srcu, index);
	vमुक्त(new_user);
	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_create_user);

पूर्णांक ipmi_get_smi_info(पूर्णांक अगर_num, काष्ठा ipmi_smi_info *data)
अणु
	पूर्णांक rv, index;
	काष्ठा ipmi_smi *पूर्णांकf;

	index = srcu_पढ़ो_lock(&ipmi_पूर्णांकerfaces_srcu);
	list_क्रम_each_entry_rcu(पूर्णांकf, &ipmi_पूर्णांकerfaces, link) अणु
		अगर (पूर्णांकf->पूर्णांकf_num == अगर_num)
			जाओ found;
	पूर्ण
	srcu_पढ़ो_unlock(&ipmi_पूर्णांकerfaces_srcu, index);

	/* Not found, वापस an error */
	वापस -EINVAL;

found:
	अगर (!पूर्णांकf->handlers->get_smi_info)
		rv = -ENOTTY;
	अन्यथा
		rv = पूर्णांकf->handlers->get_smi_info(पूर्णांकf->send_info, data);
	srcu_पढ़ो_unlock(&ipmi_पूर्णांकerfaces_srcu, index);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_get_smi_info);

अटल व्योम मुक्त_user(काष्ठा kref *ref)
अणु
	काष्ठा ipmi_user *user = container_of(ref, काष्ठा ipmi_user, refcount);

	/* SRCU cleanup must happen in task context. */
	schedule_work(&user->हटाओ_work);
पूर्ण

अटल व्योम _ipmi_destroy_user(काष्ठा ipmi_user *user)
अणु
	काष्ठा ipmi_smi  *पूर्णांकf = user->पूर्णांकf;
	पूर्णांक              i;
	अचिन्हित दीर्घ    flags;
	काष्ठा cmd_rcvr  *rcvr;
	काष्ठा cmd_rcvr  *rcvrs = शून्य;

	अगर (!acquire_ipmi_user(user, &i)) अणु
		/*
		 * The user has alपढ़ोy been cleaned up, just make sure
		 * nothing is using it and वापस.
		 */
		synchronize_srcu(&user->release_barrier);
		वापस;
	पूर्ण

	rcu_assign_poपूर्णांकer(user->self, शून्य);
	release_ipmi_user(user, i);

	synchronize_srcu(&user->release_barrier);

	अगर (user->handler->shutकरोwn)
		user->handler->shutकरोwn(user->handler_data);

	अगर (user->handler->ipmi_watchकरोg_preसमयout)
		smi_हटाओ_watch(पूर्णांकf, IPMI_WATCH_MASK_CHECK_WATCHDOG);

	अगर (user->माला_लो_events)
		atomic_dec(&पूर्णांकf->event_रुकोers);

	/* Remove the user from the पूर्णांकerface's sequence table. */
	spin_lock_irqsave(&पूर्णांकf->seq_lock, flags);
	list_del_rcu(&user->link);

	क्रम (i = 0; i < IPMI_IPMB_NUM_SEQ; i++) अणु
		अगर (पूर्णांकf->seq_table[i].inuse
		    && (पूर्णांकf->seq_table[i].recv_msg->user == user)) अणु
			पूर्णांकf->seq_table[i].inuse = 0;
			smi_हटाओ_watch(पूर्णांकf, IPMI_WATCH_MASK_CHECK_MESSAGES);
			ipmi_मुक्त_recv_msg(पूर्णांकf->seq_table[i].recv_msg);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&पूर्णांकf->seq_lock, flags);

	/*
	 * Remove the user from the command receiver's table.  First
	 * we build a list of everything (not using the standard link,
	 * since other things may be using it till we करो
	 * synchronize_srcu()) then मुक्त everything in that list.
	 */
	mutex_lock(&पूर्णांकf->cmd_rcvrs_mutex);
	list_क्रम_each_entry_rcu(rcvr, &पूर्णांकf->cmd_rcvrs, link,
				lockdep_is_held(&पूर्णांकf->cmd_rcvrs_mutex)) अणु
		अगर (rcvr->user == user) अणु
			list_del_rcu(&rcvr->link);
			rcvr->next = rcvrs;
			rcvrs = rcvr;
		पूर्ण
	पूर्ण
	mutex_unlock(&पूर्णांकf->cmd_rcvrs_mutex);
	synchronize_rcu();
	जबतक (rcvrs) अणु
		rcvr = rcvrs;
		rcvrs = rcvr->next;
		kमुक्त(rcvr);
	पूर्ण

	kref_put(&पूर्णांकf->refcount, पूर्णांकf_मुक्त);
	module_put(पूर्णांकf->owner);
पूर्ण

पूर्णांक ipmi_destroy_user(काष्ठा ipmi_user *user)
अणु
	_ipmi_destroy_user(user);

	kref_put(&user->refcount, मुक्त_user);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ipmi_destroy_user);

पूर्णांक ipmi_get_version(काष्ठा ipmi_user *user,
		     अचिन्हित अक्षर *major,
		     अचिन्हित अक्षर *minor)
अणु
	काष्ठा ipmi_device_id id;
	पूर्णांक rv, index;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	rv = bmc_get_device_id(user->पूर्णांकf, शून्य, &id, शून्य, शून्य);
	अगर (!rv) अणु
		*major = ipmi_version_major(&id);
		*minor = ipmi_version_minor(&id);
	पूर्ण
	release_ipmi_user(user, index);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_get_version);

पूर्णांक ipmi_set_my_address(काष्ठा ipmi_user *user,
			अचिन्हित पूर्णांक  channel,
			अचिन्हित अक्षर address)
अणु
	पूर्णांक index, rv = 0;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	अगर (channel >= IPMI_MAX_CHANNELS) अणु
		rv = -EINVAL;
	पूर्ण अन्यथा अणु
		channel = array_index_nospec(channel, IPMI_MAX_CHANNELS);
		user->पूर्णांकf->addrinfo[channel].address = address;
	पूर्ण
	release_ipmi_user(user, index);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_set_my_address);

पूर्णांक ipmi_get_my_address(काष्ठा ipmi_user *user,
			अचिन्हित पूर्णांक  channel,
			अचिन्हित अक्षर *address)
अणु
	पूर्णांक index, rv = 0;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	अगर (channel >= IPMI_MAX_CHANNELS) अणु
		rv = -EINVAL;
	पूर्ण अन्यथा अणु
		channel = array_index_nospec(channel, IPMI_MAX_CHANNELS);
		*address = user->पूर्णांकf->addrinfo[channel].address;
	पूर्ण
	release_ipmi_user(user, index);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_get_my_address);

पूर्णांक ipmi_set_my_LUN(काष्ठा ipmi_user *user,
		    अचिन्हित पूर्णांक  channel,
		    अचिन्हित अक्षर LUN)
अणु
	पूर्णांक index, rv = 0;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	अगर (channel >= IPMI_MAX_CHANNELS) अणु
		rv = -EINVAL;
	पूर्ण अन्यथा अणु
		channel = array_index_nospec(channel, IPMI_MAX_CHANNELS);
		user->पूर्णांकf->addrinfo[channel].lun = LUN & 0x3;
	पूर्ण
	release_ipmi_user(user, index);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_set_my_LUN);

पूर्णांक ipmi_get_my_LUN(काष्ठा ipmi_user *user,
		    अचिन्हित पूर्णांक  channel,
		    अचिन्हित अक्षर *address)
अणु
	पूर्णांक index, rv = 0;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	अगर (channel >= IPMI_MAX_CHANNELS) अणु
		rv = -EINVAL;
	पूर्ण अन्यथा अणु
		channel = array_index_nospec(channel, IPMI_MAX_CHANNELS);
		*address = user->पूर्णांकf->addrinfo[channel].lun;
	पूर्ण
	release_ipmi_user(user, index);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_get_my_LUN);

पूर्णांक ipmi_get_मुख्यtenance_mode(काष्ठा ipmi_user *user)
अणु
	पूर्णांक mode, index;
	अचिन्हित दीर्घ flags;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	spin_lock_irqsave(&user->पूर्णांकf->मुख्यtenance_mode_lock, flags);
	mode = user->पूर्णांकf->मुख्यtenance_mode;
	spin_unlock_irqrestore(&user->पूर्णांकf->मुख्यtenance_mode_lock, flags);
	release_ipmi_user(user, index);

	वापस mode;
पूर्ण
EXPORT_SYMBOL(ipmi_get_मुख्यtenance_mode);

अटल व्योम मुख्यtenance_mode_update(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	अगर (पूर्णांकf->handlers->set_मुख्यtenance_mode)
		पूर्णांकf->handlers->set_मुख्यtenance_mode(
			पूर्णांकf->send_info, पूर्णांकf->मुख्यtenance_mode_enable);
पूर्ण

पूर्णांक ipmi_set_मुख्यtenance_mode(काष्ठा ipmi_user *user, पूर्णांक mode)
अणु
	पूर्णांक rv = 0, index;
	अचिन्हित दीर्घ flags;
	काष्ठा ipmi_smi *पूर्णांकf = user->पूर्णांकf;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	spin_lock_irqsave(&पूर्णांकf->मुख्यtenance_mode_lock, flags);
	अगर (पूर्णांकf->मुख्यtenance_mode != mode) अणु
		चयन (mode) अणु
		हाल IPMI_MAINTEन_अंकCE_MODE_AUTO:
			पूर्णांकf->मुख्यtenance_mode_enable
				= (पूर्णांकf->स्वतः_मुख्यtenance_समयout > 0);
			अवरोध;

		हाल IPMI_MAINTEन_अंकCE_MODE_OFF:
			पूर्णांकf->मुख्यtenance_mode_enable = false;
			अवरोध;

		हाल IPMI_MAINTEन_अंकCE_MODE_ON:
			पूर्णांकf->मुख्यtenance_mode_enable = true;
			अवरोध;

		शेष:
			rv = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		पूर्णांकf->मुख्यtenance_mode = mode;

		मुख्यtenance_mode_update(पूर्णांकf);
	पूर्ण
 out_unlock:
	spin_unlock_irqrestore(&पूर्णांकf->मुख्यtenance_mode_lock, flags);
	release_ipmi_user(user, index);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_set_मुख्यtenance_mode);

पूर्णांक ipmi_set_माला_लो_events(काष्ठा ipmi_user *user, bool val)
अणु
	अचिन्हित दीर्घ        flags;
	काष्ठा ipmi_smi      *पूर्णांकf = user->पूर्णांकf;
	काष्ठा ipmi_recv_msg *msg, *msg2;
	काष्ठा list_head     msgs;
	पूर्णांक index;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	INIT_LIST_HEAD(&msgs);

	spin_lock_irqsave(&पूर्णांकf->events_lock, flags);
	अगर (user->माला_लो_events == val)
		जाओ out;

	user->माला_लो_events = val;

	अगर (val) अणु
		अगर (atomic_inc_वापस(&पूर्णांकf->event_रुकोers) == 1)
			need_रुकोer(पूर्णांकf);
	पूर्ण अन्यथा अणु
		atomic_dec(&पूर्णांकf->event_रुकोers);
	पूर्ण

	अगर (पूर्णांकf->delivering_events)
		/*
		 * Another thपढ़ो is delivering events क्रम this, so
		 * let it handle any new events.
		 */
		जाओ out;

	/* Deliver any queued events. */
	जबतक (user->माला_लो_events && !list_empty(&पूर्णांकf->रुकोing_events)) अणु
		list_क्रम_each_entry_safe(msg, msg2, &पूर्णांकf->रुकोing_events, link)
			list_move_tail(&msg->link, &msgs);
		पूर्णांकf->रुकोing_events_count = 0;
		अगर (पूर्णांकf->event_msg_prपूर्णांकed) अणु
			dev_warn(पूर्णांकf->si_dev, "Event queue no longer full\n");
			पूर्णांकf->event_msg_prपूर्णांकed = 0;
		पूर्ण

		पूर्णांकf->delivering_events = 1;
		spin_unlock_irqrestore(&पूर्णांकf->events_lock, flags);

		list_क्रम_each_entry_safe(msg, msg2, &msgs, link) अणु
			msg->user = user;
			kref_get(&user->refcount);
			deliver_local_response(पूर्णांकf, msg);
		पूर्ण

		spin_lock_irqsave(&पूर्णांकf->events_lock, flags);
		पूर्णांकf->delivering_events = 0;
	पूर्ण

 out:
	spin_unlock_irqrestore(&पूर्णांकf->events_lock, flags);
	release_ipmi_user(user, index);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ipmi_set_माला_लो_events);

अटल काष्ठा cmd_rcvr *find_cmd_rcvr(काष्ठा ipmi_smi *पूर्णांकf,
				      अचिन्हित अक्षर netfn,
				      अचिन्हित अक्षर cmd,
				      अचिन्हित अक्षर chan)
अणु
	काष्ठा cmd_rcvr *rcvr;

	list_क्रम_each_entry_rcu(rcvr, &पूर्णांकf->cmd_rcvrs, link,
				lockdep_is_held(&पूर्णांकf->cmd_rcvrs_mutex)) अणु
		अगर ((rcvr->netfn == netfn) && (rcvr->cmd == cmd)
					&& (rcvr->chans & (1 << chan)))
			वापस rcvr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक is_cmd_rcvr_exclusive(काष्ठा ipmi_smi *पूर्णांकf,
				 अचिन्हित अक्षर netfn,
				 अचिन्हित अक्षर cmd,
				 अचिन्हित पूर्णांक  chans)
अणु
	काष्ठा cmd_rcvr *rcvr;

	list_क्रम_each_entry_rcu(rcvr, &पूर्णांकf->cmd_rcvrs, link,
				lockdep_is_held(&पूर्णांकf->cmd_rcvrs_mutex)) अणु
		अगर ((rcvr->netfn == netfn) && (rcvr->cmd == cmd)
					&& (rcvr->chans & chans))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

पूर्णांक ipmi_रेजिस्टर_क्रम_cmd(काष्ठा ipmi_user *user,
			  अचिन्हित अक्षर netfn,
			  अचिन्हित अक्षर cmd,
			  अचिन्हित पूर्णांक  chans)
अणु
	काष्ठा ipmi_smi *पूर्णांकf = user->पूर्णांकf;
	काष्ठा cmd_rcvr *rcvr;
	पूर्णांक rv = 0, index;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	rcvr = kदो_स्मृति(माप(*rcvr), GFP_KERNEL);
	अगर (!rcvr) अणु
		rv = -ENOMEM;
		जाओ out_release;
	पूर्ण
	rcvr->cmd = cmd;
	rcvr->netfn = netfn;
	rcvr->chans = chans;
	rcvr->user = user;

	mutex_lock(&पूर्णांकf->cmd_rcvrs_mutex);
	/* Make sure the command/netfn is not alपढ़ोy रेजिस्टरed. */
	अगर (!is_cmd_rcvr_exclusive(पूर्णांकf, netfn, cmd, chans)) अणु
		rv = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	smi_add_watch(पूर्णांकf, IPMI_WATCH_MASK_CHECK_COMMANDS);

	list_add_rcu(&rcvr->link, &पूर्णांकf->cmd_rcvrs);

out_unlock:
	mutex_unlock(&पूर्णांकf->cmd_rcvrs_mutex);
	अगर (rv)
		kमुक्त(rcvr);
out_release:
	release_ipmi_user(user, index);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_रेजिस्टर_क्रम_cmd);

पूर्णांक ipmi_unरेजिस्टर_क्रम_cmd(काष्ठा ipmi_user *user,
			    अचिन्हित अक्षर netfn,
			    अचिन्हित अक्षर cmd,
			    अचिन्हित पूर्णांक  chans)
अणु
	काष्ठा ipmi_smi *पूर्णांकf = user->पूर्णांकf;
	काष्ठा cmd_rcvr *rcvr;
	काष्ठा cmd_rcvr *rcvrs = शून्य;
	पूर्णांक i, rv = -ENOENT, index;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	mutex_lock(&पूर्णांकf->cmd_rcvrs_mutex);
	क्रम (i = 0; i < IPMI_NUM_CHANNELS; i++) अणु
		अगर (((1 << i) & chans) == 0)
			जारी;
		rcvr = find_cmd_rcvr(पूर्णांकf, netfn, cmd, i);
		अगर (rcvr == शून्य)
			जारी;
		अगर (rcvr->user == user) अणु
			rv = 0;
			rcvr->chans &= ~chans;
			अगर (rcvr->chans == 0) अणु
				list_del_rcu(&rcvr->link);
				rcvr->next = rcvrs;
				rcvrs = rcvr;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&पूर्णांकf->cmd_rcvrs_mutex);
	synchronize_rcu();
	release_ipmi_user(user, index);
	जबतक (rcvrs) अणु
		smi_हटाओ_watch(पूर्णांकf, IPMI_WATCH_MASK_CHECK_COMMANDS);
		rcvr = rcvrs;
		rcvrs = rcvr->next;
		kमुक्त(rcvr);
	पूर्ण

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_unरेजिस्टर_क्रम_cmd);

अटल अचिन्हित अक्षर
ipmb_checksum(अचिन्हित अक्षर *data, पूर्णांक size)
अणु
	अचिन्हित अक्षर csum = 0;

	क्रम (; size > 0; size--, data++)
		csum += *data;

	वापस -csum;
पूर्ण

अटल अंतरभूत व्योम क्रमmat_ipmb_msg(काष्ठा ipmi_smi_msg   *smi_msg,
				   काष्ठा kernel_ipmi_msg *msg,
				   काष्ठा ipmi_ipmb_addr *ipmb_addr,
				   दीर्घ                  msgid,
				   अचिन्हित अक्षर         ipmb_seq,
				   पूर्णांक                   broadcast,
				   अचिन्हित अक्षर         source_address,
				   अचिन्हित अक्षर         source_lun)
अणु
	पूर्णांक i = broadcast;

	/* Format the IPMB header data. */
	smi_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	smi_msg->data[1] = IPMI_SEND_MSG_CMD;
	smi_msg->data[2] = ipmb_addr->channel;
	अगर (broadcast)
		smi_msg->data[3] = 0;
	smi_msg->data[i+3] = ipmb_addr->slave_addr;
	smi_msg->data[i+4] = (msg->netfn << 2) | (ipmb_addr->lun & 0x3);
	smi_msg->data[i+5] = ipmb_checksum(&smi_msg->data[i + 3], 2);
	smi_msg->data[i+6] = source_address;
	smi_msg->data[i+7] = (ipmb_seq << 2) | source_lun;
	smi_msg->data[i+8] = msg->cmd;

	/* Now tack on the data to the message. */
	अगर (msg->data_len > 0)
		स_नकल(&smi_msg->data[i + 9], msg->data, msg->data_len);
	smi_msg->data_size = msg->data_len + 9;

	/* Now calculate the checksum and tack it on. */
	smi_msg->data[i+smi_msg->data_size]
		= ipmb_checksum(&smi_msg->data[i + 6], smi_msg->data_size - 6);

	/*
	 * Add on the checksum size and the offset from the
	 * broadcast.
	 */
	smi_msg->data_size += 1 + i;

	smi_msg->msgid = msgid;
पूर्ण

अटल अंतरभूत व्योम क्रमmat_lan_msg(काष्ठा ipmi_smi_msg   *smi_msg,
				  काष्ठा kernel_ipmi_msg *msg,
				  काष्ठा ipmi_lan_addr  *lan_addr,
				  दीर्घ                  msgid,
				  अचिन्हित अक्षर         ipmb_seq,
				  अचिन्हित अक्षर         source_lun)
अणु
	/* Format the IPMB header data. */
	smi_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	smi_msg->data[1] = IPMI_SEND_MSG_CMD;
	smi_msg->data[2] = lan_addr->channel;
	smi_msg->data[3] = lan_addr->session_handle;
	smi_msg->data[4] = lan_addr->remote_SWID;
	smi_msg->data[5] = (msg->netfn << 2) | (lan_addr->lun & 0x3);
	smi_msg->data[6] = ipmb_checksum(&smi_msg->data[4], 2);
	smi_msg->data[7] = lan_addr->local_SWID;
	smi_msg->data[8] = (ipmb_seq << 2) | source_lun;
	smi_msg->data[9] = msg->cmd;

	/* Now tack on the data to the message. */
	अगर (msg->data_len > 0)
		स_नकल(&smi_msg->data[10], msg->data, msg->data_len);
	smi_msg->data_size = msg->data_len + 10;

	/* Now calculate the checksum and tack it on. */
	smi_msg->data[smi_msg->data_size]
		= ipmb_checksum(&smi_msg->data[7], smi_msg->data_size - 7);

	/*
	 * Add on the checksum size and the offset from the
	 * broadcast.
	 */
	smi_msg->data_size += 1;

	smi_msg->msgid = msgid;
पूर्ण

अटल काष्ठा ipmi_smi_msg *smi_add_send_msg(काष्ठा ipmi_smi *पूर्णांकf,
					     काष्ठा ipmi_smi_msg *smi_msg,
					     पूर्णांक priority)
अणु
	अगर (पूर्णांकf->curr_msg) अणु
		अगर (priority > 0)
			list_add_tail(&smi_msg->link, &पूर्णांकf->hp_xmit_msgs);
		अन्यथा
			list_add_tail(&smi_msg->link, &पूर्णांकf->xmit_msgs);
		smi_msg = शून्य;
	पूर्ण अन्यथा अणु
		पूर्णांकf->curr_msg = smi_msg;
	पूर्ण

	वापस smi_msg;
पूर्ण

अटल व्योम smi_send(काष्ठा ipmi_smi *पूर्णांकf,
		     स्थिर काष्ठा ipmi_smi_handlers *handlers,
		     काष्ठा ipmi_smi_msg *smi_msg, पूर्णांक priority)
अणु
	पूर्णांक run_to_completion = पूर्णांकf->run_to_completion;
	अचिन्हित दीर्घ flags = 0;

	अगर (!run_to_completion)
		spin_lock_irqsave(&पूर्णांकf->xmit_msgs_lock, flags);
	smi_msg = smi_add_send_msg(पूर्णांकf, smi_msg, priority);

	अगर (!run_to_completion)
		spin_unlock_irqrestore(&पूर्णांकf->xmit_msgs_lock, flags);

	अगर (smi_msg)
		handlers->sender(पूर्णांकf->send_info, smi_msg);
पूर्ण

अटल bool is_मुख्यtenance_mode_cmd(काष्ठा kernel_ipmi_msg *msg)
अणु
	वापस (((msg->netfn == IPMI_NETFN_APP_REQUEST)
		 && ((msg->cmd == IPMI_COLD_RESET_CMD)
		     || (msg->cmd == IPMI_WARM_RESET_CMD)))
		|| (msg->netfn == IPMI_NETFN_FIRMWARE_REQUEST));
पूर्ण

अटल पूर्णांक i_ipmi_req_sysपूर्णांकf(काष्ठा ipmi_smi        *पूर्णांकf,
			      काष्ठा ipmi_addr       *addr,
			      दीर्घ                   msgid,
			      काष्ठा kernel_ipmi_msg *msg,
			      काष्ठा ipmi_smi_msg    *smi_msg,
			      काष्ठा ipmi_recv_msg   *recv_msg,
			      पूर्णांक                    retries,
			      अचिन्हित पूर्णांक           retry_समय_ms)
अणु
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *smi_addr;

	अगर (msg->netfn & 1)
		/* Responses are not allowed to the SMI. */
		वापस -EINVAL;

	smi_addr = (काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *) addr;
	अगर (smi_addr->lun > 3) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EINVAL;
	पूर्ण

	स_नकल(&recv_msg->addr, smi_addr, माप(*smi_addr));

	अगर ((msg->netfn == IPMI_NETFN_APP_REQUEST)
	    && ((msg->cmd == IPMI_SEND_MSG_CMD)
		|| (msg->cmd == IPMI_GET_MSG_CMD)
		|| (msg->cmd == IPMI_READ_EVENT_MSG_BUFFER_CMD))) अणु
		/*
		 * We करोn't let the user करो these, since we manage
		 * the sequence numbers.
		 */
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EINVAL;
	पूर्ण

	अगर (is_मुख्यtenance_mode_cmd(msg)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&पूर्णांकf->मुख्यtenance_mode_lock, flags);
		पूर्णांकf->स्वतः_मुख्यtenance_समयout
			= मुख्यtenance_mode_समयout_ms;
		अगर (!पूर्णांकf->मुख्यtenance_mode
		    && !पूर्णांकf->मुख्यtenance_mode_enable) अणु
			पूर्णांकf->मुख्यtenance_mode_enable = true;
			मुख्यtenance_mode_update(पूर्णांकf);
		पूर्ण
		spin_unlock_irqrestore(&पूर्णांकf->मुख्यtenance_mode_lock,
				       flags);
	पूर्ण

	अगर (msg->data_len + 2 > IPMI_MAX_MSG_LENGTH) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EMSGSIZE;
	पूर्ण

	smi_msg->data[0] = (msg->netfn << 2) | (smi_addr->lun & 0x3);
	smi_msg->data[1] = msg->cmd;
	smi_msg->msgid = msgid;
	smi_msg->user_data = recv_msg;
	अगर (msg->data_len > 0)
		स_नकल(&smi_msg->data[2], msg->data, msg->data_len);
	smi_msg->data_size = msg->data_len + 2;
	ipmi_inc_stat(पूर्णांकf, sent_local_commands);

	वापस 0;
पूर्ण

अटल पूर्णांक i_ipmi_req_ipmb(काष्ठा ipmi_smi        *पूर्णांकf,
			   काष्ठा ipmi_addr       *addr,
			   दीर्घ                   msgid,
			   काष्ठा kernel_ipmi_msg *msg,
			   काष्ठा ipmi_smi_msg    *smi_msg,
			   काष्ठा ipmi_recv_msg   *recv_msg,
			   अचिन्हित अक्षर          source_address,
			   अचिन्हित अक्षर          source_lun,
			   पूर्णांक                    retries,
			   अचिन्हित पूर्णांक           retry_समय_ms)
अणु
	काष्ठा ipmi_ipmb_addr *ipmb_addr;
	अचिन्हित अक्षर ipmb_seq;
	दीर्घ seqid;
	पूर्णांक broadcast = 0;
	काष्ठा ipmi_channel *chans;
	पूर्णांक rv = 0;

	अगर (addr->channel >= IPMI_MAX_CHANNELS) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EINVAL;
	पूर्ण

	chans = READ_ONCE(पूर्णांकf->channel_list)->c;

	अगर (chans[addr->channel].medium != IPMI_CHANNEL_MEDIUM_IPMB) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EINVAL;
	पूर्ण

	अगर (addr->addr_type == IPMI_IPMB_BROADCAST_ADDR_TYPE) अणु
		/*
		 * Broadcasts add a zero at the beginning of the
		 * message, but otherwise is the same as an IPMB
		 * address.
		 */
		addr->addr_type = IPMI_IPMB_ADDR_TYPE;
		broadcast = 1;
		retries = 0; /* Don't retry broadcasts. */
	पूर्ण

	/*
	 * 9 क्रम the header and 1 क्रम the checksum, plus
	 * possibly one क्रम the broadcast.
	 */
	अगर ((msg->data_len + 10 + broadcast) > IPMI_MAX_MSG_LENGTH) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EMSGSIZE;
	पूर्ण

	ipmb_addr = (काष्ठा ipmi_ipmb_addr *) addr;
	अगर (ipmb_addr->lun > 3) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EINVAL;
	पूर्ण

	स_नकल(&recv_msg->addr, ipmb_addr, माप(*ipmb_addr));

	अगर (recv_msg->msg.netfn & 0x1) अणु
		/*
		 * It's a response, so use the user's sequence
		 * from msgid.
		 */
		ipmi_inc_stat(पूर्णांकf, sent_ipmb_responses);
		क्रमmat_ipmb_msg(smi_msg, msg, ipmb_addr, msgid,
				msgid, broadcast,
				source_address, source_lun);

		/*
		 * Save the receive message so we can use it
		 * to deliver the response.
		 */
		smi_msg->user_data = recv_msg;
	पूर्ण अन्यथा अणु
		/* It's a command, so get a sequence क्रम it. */
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&पूर्णांकf->seq_lock, flags);

		अगर (is_मुख्यtenance_mode_cmd(msg))
			पूर्णांकf->ipmb_मुख्यtenance_mode_समयout =
				मुख्यtenance_mode_समयout_ms;

		अगर (पूर्णांकf->ipmb_मुख्यtenance_mode_समयout && retry_समय_ms == 0)
			/* Dअगरferent शेष in मुख्यtenance mode */
			retry_समय_ms = शेष_मुख्यtenance_retry_ms;

		/*
		 * Create a sequence number with a 1 second
		 * समयout and 4 retries.
		 */
		rv = पूर्णांकf_next_seq(पूर्णांकf,
				   recv_msg,
				   retry_समय_ms,
				   retries,
				   broadcast,
				   &ipmb_seq,
				   &seqid);
		अगर (rv)
			/*
			 * We have used up all the sequence numbers,
			 * probably, so पात.
			 */
			जाओ out_err;

		ipmi_inc_stat(पूर्णांकf, sent_ipmb_commands);

		/*
		 * Store the sequence number in the message,
		 * so that when the send message response
		 * comes back we can start the समयr.
		 */
		क्रमmat_ipmb_msg(smi_msg, msg, ipmb_addr,
				STORE_SEQ_IN_MSGID(ipmb_seq, seqid),
				ipmb_seq, broadcast,
				source_address, source_lun);

		/*
		 * Copy the message पूर्णांकo the recv message data, so we
		 * can retransmit it later अगर necessary.
		 */
		स_नकल(recv_msg->msg_data, smi_msg->data,
		       smi_msg->data_size);
		recv_msg->msg.data = recv_msg->msg_data;
		recv_msg->msg.data_len = smi_msg->data_size;

		/*
		 * We करोn't unlock until here, because we need
		 * to copy the completed message पूर्णांकo the
		 * recv_msg beक्रमe we release the lock.
		 * Otherwise, race conditions may bite us.  I
		 * know that's pretty paranoid, but I prefer
		 * to be correct.
		 */
out_err:
		spin_unlock_irqrestore(&पूर्णांकf->seq_lock, flags);
	पूर्ण

	वापस rv;
पूर्ण

अटल पूर्णांक i_ipmi_req_lan(काष्ठा ipmi_smi        *पूर्णांकf,
			  काष्ठा ipmi_addr       *addr,
			  दीर्घ                   msgid,
			  काष्ठा kernel_ipmi_msg *msg,
			  काष्ठा ipmi_smi_msg    *smi_msg,
			  काष्ठा ipmi_recv_msg   *recv_msg,
			  अचिन्हित अक्षर          source_lun,
			  पूर्णांक                    retries,
			  अचिन्हित पूर्णांक           retry_समय_ms)
अणु
	काष्ठा ipmi_lan_addr  *lan_addr;
	अचिन्हित अक्षर ipmb_seq;
	दीर्घ seqid;
	काष्ठा ipmi_channel *chans;
	पूर्णांक rv = 0;

	अगर (addr->channel >= IPMI_MAX_CHANNELS) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EINVAL;
	पूर्ण

	chans = READ_ONCE(पूर्णांकf->channel_list)->c;

	अगर ((chans[addr->channel].medium
				!= IPMI_CHANNEL_MEDIUM_8023LAN)
			&& (chans[addr->channel].medium
			    != IPMI_CHANNEL_MEDIUM_ASYNC)) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EINVAL;
	पूर्ण

	/* 11 क्रम the header and 1 क्रम the checksum. */
	अगर ((msg->data_len + 12) > IPMI_MAX_MSG_LENGTH) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EMSGSIZE;
	पूर्ण

	lan_addr = (काष्ठा ipmi_lan_addr *) addr;
	अगर (lan_addr->lun > 3) अणु
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		वापस -EINVAL;
	पूर्ण

	स_नकल(&recv_msg->addr, lan_addr, माप(*lan_addr));

	अगर (recv_msg->msg.netfn & 0x1) अणु
		/*
		 * It's a response, so use the user's sequence
		 * from msgid.
		 */
		ipmi_inc_stat(पूर्णांकf, sent_lan_responses);
		क्रमmat_lan_msg(smi_msg, msg, lan_addr, msgid,
			       msgid, source_lun);

		/*
		 * Save the receive message so we can use it
		 * to deliver the response.
		 */
		smi_msg->user_data = recv_msg;
	पूर्ण अन्यथा अणु
		/* It's a command, so get a sequence क्रम it. */
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&पूर्णांकf->seq_lock, flags);

		/*
		 * Create a sequence number with a 1 second
		 * समयout and 4 retries.
		 */
		rv = पूर्णांकf_next_seq(पूर्णांकf,
				   recv_msg,
				   retry_समय_ms,
				   retries,
				   0,
				   &ipmb_seq,
				   &seqid);
		अगर (rv)
			/*
			 * We have used up all the sequence numbers,
			 * probably, so पात.
			 */
			जाओ out_err;

		ipmi_inc_stat(पूर्णांकf, sent_lan_commands);

		/*
		 * Store the sequence number in the message,
		 * so that when the send message response
		 * comes back we can start the समयr.
		 */
		क्रमmat_lan_msg(smi_msg, msg, lan_addr,
			       STORE_SEQ_IN_MSGID(ipmb_seq, seqid),
			       ipmb_seq, source_lun);

		/*
		 * Copy the message पूर्णांकo the recv message data, so we
		 * can retransmit it later अगर necessary.
		 */
		स_नकल(recv_msg->msg_data, smi_msg->data,
		       smi_msg->data_size);
		recv_msg->msg.data = recv_msg->msg_data;
		recv_msg->msg.data_len = smi_msg->data_size;

		/*
		 * We करोn't unlock until here, because we need
		 * to copy the completed message पूर्णांकo the
		 * recv_msg beक्रमe we release the lock.
		 * Otherwise, race conditions may bite us.  I
		 * know that's pretty paranoid, but I prefer
		 * to be correct.
		 */
out_err:
		spin_unlock_irqrestore(&पूर्णांकf->seq_lock, flags);
	पूर्ण

	वापस rv;
पूर्ण

/*
 * Separate from ipmi_request so that the user करोes not have to be
 * supplied in certain circumstances (मुख्यly at panic समय).  If
 * messages are supplied, they will be मुक्तd, even अगर an error
 * occurs.
 */
अटल पूर्णांक i_ipmi_request(काष्ठा ipmi_user     *user,
			  काष्ठा ipmi_smi      *पूर्णांकf,
			  काष्ठा ipmi_addr     *addr,
			  दीर्घ                 msgid,
			  काष्ठा kernel_ipmi_msg *msg,
			  व्योम                 *user_msg_data,
			  व्योम                 *supplied_smi,
			  काष्ठा ipmi_recv_msg *supplied_recv,
			  पूर्णांक                  priority,
			  अचिन्हित अक्षर        source_address,
			  अचिन्हित अक्षर        source_lun,
			  पूर्णांक                  retries,
			  अचिन्हित पूर्णांक         retry_समय_ms)
अणु
	काष्ठा ipmi_smi_msg *smi_msg;
	काष्ठा ipmi_recv_msg *recv_msg;
	पूर्णांक rv = 0;

	अगर (supplied_recv)
		recv_msg = supplied_recv;
	अन्यथा अणु
		recv_msg = ipmi_alloc_recv_msg();
		अगर (recv_msg == शून्य) अणु
			rv = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण
	recv_msg->user_msg_data = user_msg_data;

	अगर (supplied_smi)
		smi_msg = (काष्ठा ipmi_smi_msg *) supplied_smi;
	अन्यथा अणु
		smi_msg = ipmi_alloc_smi_msg();
		अगर (smi_msg == शून्य) अणु
			अगर (!supplied_recv)
				ipmi_मुक्त_recv_msg(recv_msg);
			rv = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_lock();
	अगर (पूर्णांकf->in_shutकरोwn) अणु
		rv = -ENODEV;
		जाओ out_err;
	पूर्ण

	recv_msg->user = user;
	अगर (user)
		/* The put happens when the message is मुक्तd. */
		kref_get(&user->refcount);
	recv_msg->msgid = msgid;
	/*
	 * Store the message to send in the receive message so समयout
	 * responses can get the proper response data.
	 */
	recv_msg->msg = *msg;

	अगर (addr->addr_type == IPMI_SYSTEM_INTERFACE_ADDR_TYPE) अणु
		rv = i_ipmi_req_sysपूर्णांकf(पूर्णांकf, addr, msgid, msg, smi_msg,
					recv_msg, retries, retry_समय_ms);
	पूर्ण अन्यथा अगर (is_ipmb_addr(addr) || is_ipmb_bcast_addr(addr)) अणु
		rv = i_ipmi_req_ipmb(पूर्णांकf, addr, msgid, msg, smi_msg, recv_msg,
				     source_address, source_lun,
				     retries, retry_समय_ms);
	पूर्ण अन्यथा अगर (is_lan_addr(addr)) अणु
		rv = i_ipmi_req_lan(पूर्णांकf, addr, msgid, msg, smi_msg, recv_msg,
				    source_lun, retries, retry_समय_ms);
	पूर्ण अन्यथा अणु
	    /* Unknown address type. */
		ipmi_inc_stat(पूर्णांकf, sent_invalid_commands);
		rv = -EINVAL;
	पूर्ण

	अगर (rv) अणु
out_err:
		ipmi_मुक्त_smi_msg(smi_msg);
		ipmi_मुक्त_recv_msg(recv_msg);
	पूर्ण अन्यथा अणु
		pr_debug("Send: %*ph\n", smi_msg->data_size, smi_msg->data);

		smi_send(पूर्णांकf, पूर्णांकf->handlers, smi_msg, priority);
	पूर्ण
	rcu_पढ़ो_unlock();

out:
	वापस rv;
पूर्ण

अटल पूर्णांक check_addr(काष्ठा ipmi_smi  *पूर्णांकf,
		      काष्ठा ipmi_addr *addr,
		      अचिन्हित अक्षर    *saddr,
		      अचिन्हित अक्षर    *lun)
अणु
	अगर (addr->channel >= IPMI_MAX_CHANNELS)
		वापस -EINVAL;
	addr->channel = array_index_nospec(addr->channel, IPMI_MAX_CHANNELS);
	*lun = पूर्णांकf->addrinfo[addr->channel].lun;
	*saddr = पूर्णांकf->addrinfo[addr->channel].address;
	वापस 0;
पूर्ण

पूर्णांक ipmi_request_समय_रखो(काष्ठा ipmi_user *user,
			 काष्ठा ipmi_addr *addr,
			 दीर्घ             msgid,
			 काष्ठा kernel_ipmi_msg  *msg,
			 व्योम             *user_msg_data,
			 पूर्णांक              priority,
			 पूर्णांक              retries,
			 अचिन्हित पूर्णांक     retry_समय_ms)
अणु
	अचिन्हित अक्षर saddr = 0, lun = 0;
	पूर्णांक rv, index;

	अगर (!user)
		वापस -EINVAL;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	rv = check_addr(user->पूर्णांकf, addr, &saddr, &lun);
	अगर (!rv)
		rv = i_ipmi_request(user,
				    user->पूर्णांकf,
				    addr,
				    msgid,
				    msg,
				    user_msg_data,
				    शून्य, शून्य,
				    priority,
				    saddr,
				    lun,
				    retries,
				    retry_समय_ms);

	release_ipmi_user(user, index);
	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_request_समय_रखो);

पूर्णांक ipmi_request_supply_msgs(काष्ठा ipmi_user     *user,
			     काष्ठा ipmi_addr     *addr,
			     दीर्घ                 msgid,
			     काष्ठा kernel_ipmi_msg *msg,
			     व्योम                 *user_msg_data,
			     व्योम                 *supplied_smi,
			     काष्ठा ipmi_recv_msg *supplied_recv,
			     पूर्णांक                  priority)
अणु
	अचिन्हित अक्षर saddr = 0, lun = 0;
	पूर्णांक rv, index;

	अगर (!user)
		वापस -EINVAL;

	user = acquire_ipmi_user(user, &index);
	अगर (!user)
		वापस -ENODEV;

	rv = check_addr(user->पूर्णांकf, addr, &saddr, &lun);
	अगर (!rv)
		rv = i_ipmi_request(user,
				    user->पूर्णांकf,
				    addr,
				    msgid,
				    msg,
				    user_msg_data,
				    supplied_smi,
				    supplied_recv,
				    priority,
				    saddr,
				    lun,
				    -1, 0);

	release_ipmi_user(user, index);
	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_request_supply_msgs);

अटल व्योम bmc_device_id_handler(काष्ठा ipmi_smi *पूर्णांकf,
				  काष्ठा ipmi_recv_msg *msg)
अणु
	पूर्णांक rv;

	अगर ((msg->addr.addr_type != IPMI_SYSTEM_INTERFACE_ADDR_TYPE)
			|| (msg->msg.netfn != IPMI_NETFN_APP_RESPONSE)
			|| (msg->msg.cmd != IPMI_GET_DEVICE_ID_CMD)) अणु
		dev_warn(पूर्णांकf->si_dev,
			 "invalid device_id msg: addr_type=%d netfn=%x cmd=%x\n",
			 msg->addr.addr_type, msg->msg.netfn, msg->msg.cmd);
		वापस;
	पूर्ण

	rv = ipmi_demangle_device_id(msg->msg.netfn, msg->msg.cmd,
			msg->msg.data, msg->msg.data_len, &पूर्णांकf->bmc->fetch_id);
	अगर (rv) अणु
		dev_warn(पूर्णांकf->si_dev, "device id demangle failed: %d\n", rv);
		/* record completion code when error */
		पूर्णांकf->bmc->cc = msg->msg.data[0];
		पूर्णांकf->bmc->dyn_id_set = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Make sure the id data is available beक्रमe setting
		 * dyn_id_set.
		 */
		smp_wmb();
		पूर्णांकf->bmc->dyn_id_set = 1;
	पूर्ण

	wake_up(&पूर्णांकf->रुकोq);
पूर्ण

अटल पूर्णांक
send_get_device_id_cmd(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr si;
	काष्ठा kernel_ipmi_msg msg;

	si.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	si.channel = IPMI_BMC_CHANNEL;
	si.lun = 0;

	msg.netfn = IPMI_NETFN_APP_REQUEST;
	msg.cmd = IPMI_GET_DEVICE_ID_CMD;
	msg.data = शून्य;
	msg.data_len = 0;

	वापस i_ipmi_request(शून्य,
			      पूर्णांकf,
			      (काष्ठा ipmi_addr *) &si,
			      0,
			      &msg,
			      पूर्णांकf,
			      शून्य,
			      शून्य,
			      0,
			      पूर्णांकf->addrinfo[0].address,
			      पूर्णांकf->addrinfo[0].lun,
			      -1, 0);
पूर्ण

अटल पूर्णांक __get_device_id(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा bmc_device *bmc)
अणु
	पूर्णांक rv;
	अचिन्हित पूर्णांक retry_count = 0;

	पूर्णांकf->null_user_handler = bmc_device_id_handler;

retry:
	bmc->cc = 0;
	bmc->dyn_id_set = 2;

	rv = send_get_device_id_cmd(पूर्णांकf);
	अगर (rv)
		जाओ out_reset_handler;

	रुको_event(पूर्णांकf->रुकोq, bmc->dyn_id_set != 2);

	अगर (!bmc->dyn_id_set) अणु
		अगर (bmc->cc != IPMI_CC_NO_ERROR &&
		    ++retry_count <= GET_DEVICE_ID_MAX_RETRY) अणु
			msleep(500);
			dev_warn(पूर्णांकf->si_dev,
			    "BMC returned 0x%2.2x, retry get bmc device id\n",
			    bmc->cc);
			जाओ retry;
		पूर्ण

		rv = -EIO; /* Something went wrong in the fetch. */
	पूर्ण

	/* dyn_id_set makes the id data available. */
	smp_rmb();

out_reset_handler:
	पूर्णांकf->null_user_handler = शून्य;

	वापस rv;
पूर्ण

/*
 * Fetch the device id क्रम the bmc/पूर्णांकerface.  You must pass in either
 * bmc or पूर्णांकf, this code will get the other one.  If the data has
 * been recently fetched, this will just use the cached data.  Otherwise
 * it will run a new fetch.
 *
 * Except क्रम the first समय this is called (in ipmi_add_smi()),
 * this will always वापस good data;
 */
अटल पूर्णांक __bmc_get_device_id(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा bmc_device *bmc,
			       काष्ठा ipmi_device_id *id,
			       bool *guid_set, guid_t *guid, पूर्णांक पूर्णांकf_num)
अणु
	पूर्णांक rv = 0;
	पूर्णांक prev_dyn_id_set, prev_guid_set;
	bool पूर्णांकf_set = पूर्णांकf != शून्य;

	अगर (!पूर्णांकf) अणु
		mutex_lock(&bmc->dyn_mutex);
retry_bmc_lock:
		अगर (list_empty(&bmc->पूर्णांकfs)) अणु
			mutex_unlock(&bmc->dyn_mutex);
			वापस -ENOENT;
		पूर्ण
		पूर्णांकf = list_first_entry(&bmc->पूर्णांकfs, काष्ठा ipmi_smi,
					bmc_link);
		kref_get(&पूर्णांकf->refcount);
		mutex_unlock(&bmc->dyn_mutex);
		mutex_lock(&पूर्णांकf->bmc_reg_mutex);
		mutex_lock(&bmc->dyn_mutex);
		अगर (पूर्णांकf != list_first_entry(&bmc->पूर्णांकfs, काष्ठा ipmi_smi,
					     bmc_link)) अणु
			mutex_unlock(&पूर्णांकf->bmc_reg_mutex);
			kref_put(&पूर्णांकf->refcount, पूर्णांकf_मुक्त);
			जाओ retry_bmc_lock;
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&पूर्णांकf->bmc_reg_mutex);
		bmc = पूर्णांकf->bmc;
		mutex_lock(&bmc->dyn_mutex);
		kref_get(&पूर्णांकf->refcount);
	पूर्ण

	/* If we have a valid and current ID, just वापस that. */
	अगर (पूर्णांकf->in_bmc_रेजिस्टर ||
	    (bmc->dyn_id_set && समय_is_after_jअगरfies(bmc->dyn_id_expiry)))
		जाओ out_noprocessing;

	prev_guid_set = bmc->dyn_guid_set;
	__get_guid(पूर्णांकf);

	prev_dyn_id_set = bmc->dyn_id_set;
	rv = __get_device_id(पूर्णांकf, bmc);
	अगर (rv)
		जाओ out;

	/*
	 * The guid, device id, manufacturer id, and product id should
	 * not change on a BMC.  If it करोes we have to करो some dancing.
	 */
	अगर (!पूर्णांकf->bmc_रेजिस्टरed
	    || (!prev_guid_set && bmc->dyn_guid_set)
	    || (!prev_dyn_id_set && bmc->dyn_id_set)
	    || (prev_guid_set && bmc->dyn_guid_set
		&& !guid_equal(&bmc->guid, &bmc->fetch_guid))
	    || bmc->id.device_id != bmc->fetch_id.device_id
	    || bmc->id.manufacturer_id != bmc->fetch_id.manufacturer_id
	    || bmc->id.product_id != bmc->fetch_id.product_id) अणु
		काष्ठा ipmi_device_id id = bmc->fetch_id;
		पूर्णांक guid_set = bmc->dyn_guid_set;
		guid_t guid;

		guid = bmc->fetch_guid;
		mutex_unlock(&bmc->dyn_mutex);

		__ipmi_bmc_unरेजिस्टर(पूर्णांकf);
		/* Fill in the temporary BMC क्रम good measure. */
		पूर्णांकf->bmc->id = id;
		पूर्णांकf->bmc->dyn_guid_set = guid_set;
		पूर्णांकf->bmc->guid = guid;
		अगर (__ipmi_bmc_रेजिस्टर(पूर्णांकf, &id, guid_set, &guid, पूर्णांकf_num))
			need_रुकोer(पूर्णांकf); /* Retry later on an error. */
		अन्यथा
			__scan_channels(पूर्णांकf, &id);


		अगर (!पूर्णांकf_set) अणु
			/*
			 * We weren't given the पूर्णांकerface on the
			 * command line, so restart the operation on
			 * the next पूर्णांकerface क्रम the BMC.
			 */
			mutex_unlock(&पूर्णांकf->bmc_reg_mutex);
			mutex_lock(&bmc->dyn_mutex);
			जाओ retry_bmc_lock;
		पूर्ण

		/* We have a new BMC, set it up. */
		bmc = पूर्णांकf->bmc;
		mutex_lock(&bmc->dyn_mutex);
		जाओ out_noprocessing;
	पूर्ण अन्यथा अगर (स_भेद(&bmc->fetch_id, &bmc->id, माप(bmc->id)))
		/* Version info changes, scan the channels again. */
		__scan_channels(पूर्णांकf, &bmc->fetch_id);

	bmc->dyn_id_expiry = jअगरfies + IPMI_DYN_DEV_ID_EXPIRY;

out:
	अगर (rv && prev_dyn_id_set) अणु
		rv = 0; /* Ignore failures अगर we have previous data. */
		bmc->dyn_id_set = prev_dyn_id_set;
	पूर्ण
	अगर (!rv) अणु
		bmc->id = bmc->fetch_id;
		अगर (bmc->dyn_guid_set)
			bmc->guid = bmc->fetch_guid;
		अन्यथा अगर (prev_guid_set)
			/*
			 * The guid used to be valid and it failed to fetch,
			 * just use the cached value.
			 */
			bmc->dyn_guid_set = prev_guid_set;
	पूर्ण
out_noprocessing:
	अगर (!rv) अणु
		अगर (id)
			*id = bmc->id;

		अगर (guid_set)
			*guid_set = bmc->dyn_guid_set;

		अगर (guid && bmc->dyn_guid_set)
			*guid =  bmc->guid;
	पूर्ण

	mutex_unlock(&bmc->dyn_mutex);
	mutex_unlock(&पूर्णांकf->bmc_reg_mutex);

	kref_put(&पूर्णांकf->refcount, पूर्णांकf_मुक्त);
	वापस rv;
पूर्ण

अटल पूर्णांक bmc_get_device_id(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा bmc_device *bmc,
			     काष्ठा ipmi_device_id *id,
			     bool *guid_set, guid_t *guid)
अणु
	वापस __bmc_get_device_id(पूर्णांकf, bmc, id, guid_set, guid, -1);
पूर्ण

अटल sमाप_प्रकार device_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	काष्ठा ipmi_device_id id;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
	अगर (rv)
		वापस rv;

	वापस snम_लिखो(buf, 10, "%u\n", id.device_id);
पूर्ण
अटल DEVICE_ATTR_RO(device_id);

अटल sमाप_प्रकार provides_device_sdrs_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	काष्ठा ipmi_device_id id;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
	अगर (rv)
		वापस rv;

	वापस snम_लिखो(buf, 10, "%u\n", (id.device_revision & 0x80) >> 7);
पूर्ण
अटल DEVICE_ATTR_RO(provides_device_sdrs);

अटल sमाप_प्रकार revision_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	काष्ठा ipmi_device_id id;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
	अगर (rv)
		वापस rv;

	वापस snम_लिखो(buf, 20, "%u\n", id.device_revision & 0x0F);
पूर्ण
अटल DEVICE_ATTR_RO(revision);

अटल sमाप_प्रकार firmware_revision_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	काष्ठा ipmi_device_id id;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
	अगर (rv)
		वापस rv;

	वापस snम_लिखो(buf, 20, "%u.%x\n", id.firmware_revision_1,
			id.firmware_revision_2);
पूर्ण
अटल DEVICE_ATTR_RO(firmware_revision);

अटल sमाप_प्रकार ipmi_version_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	काष्ठा ipmi_device_id id;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
	अगर (rv)
		वापस rv;

	वापस snम_लिखो(buf, 20, "%u.%u\n",
			ipmi_version_major(&id),
			ipmi_version_minor(&id));
पूर्ण
अटल DEVICE_ATTR_RO(ipmi_version);

अटल sमाप_प्रकार add_dev_support_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	काष्ठा ipmi_device_id id;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
	अगर (rv)
		वापस rv;

	वापस snम_लिखो(buf, 10, "0x%02x\n", id.additional_device_support);
पूर्ण
अटल DEVICE_ATTR(additional_device_support, S_IRUGO, add_dev_support_show,
		   शून्य);

अटल sमाप_प्रकार manufacturer_id_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	काष्ठा ipmi_device_id id;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
	अगर (rv)
		वापस rv;

	वापस snम_लिखो(buf, 20, "0x%6.6x\n", id.manufacturer_id);
पूर्ण
अटल DEVICE_ATTR_RO(manufacturer_id);

अटल sमाप_प्रकार product_id_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	काष्ठा ipmi_device_id id;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
	अगर (rv)
		वापस rv;

	वापस snम_लिखो(buf, 10, "0x%4.4x\n", id.product_id);
पूर्ण
अटल DEVICE_ATTR_RO(product_id);

अटल sमाप_प्रकार aux_firmware_rev_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	काष्ठा ipmi_device_id id;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
	अगर (rv)
		वापस rv;

	वापस snम_लिखो(buf, 21, "0x%02x 0x%02x 0x%02x 0x%02x\n",
			id.aux_firmware_revision[3],
			id.aux_firmware_revision[2],
			id.aux_firmware_revision[1],
			id.aux_firmware_revision[0]);
पूर्ण
अटल DEVICE_ATTR(aux_firmware_revision, S_IRUGO, aux_firmware_rev_show, शून्य);

अटल sमाप_प्रकार guid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	bool guid_set;
	guid_t guid;
	पूर्णांक rv;

	rv = bmc_get_device_id(शून्य, bmc, शून्य, &guid_set, &guid);
	अगर (rv)
		वापस rv;
	अगर (!guid_set)
		वापस -ENOENT;

	वापस snम_लिखो(buf, UUID_STRING_LEN + 1 + 1, "%pUl\n", &guid);
पूर्ण
अटल DEVICE_ATTR_RO(guid);

अटल काष्ठा attribute *bmc_dev_attrs[] = अणु
	&dev_attr_device_id.attr,
	&dev_attr_provides_device_sdrs.attr,
	&dev_attr_revision.attr,
	&dev_attr_firmware_revision.attr,
	&dev_attr_ipmi_version.attr,
	&dev_attr_additional_device_support.attr,
	&dev_attr_manufacturer_id.attr,
	&dev_attr_product_id.attr,
	&dev_attr_aux_firmware_revision.attr,
	&dev_attr_guid.attr,
	शून्य
पूर्ण;

अटल umode_t bmc_dev_attr_is_visible(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा bmc_device *bmc = to_bmc_device(dev);
	umode_t mode = attr->mode;
	पूर्णांक rv;

	अगर (attr == &dev_attr_aux_firmware_revision.attr) अणु
		काष्ठा ipmi_device_id id;

		rv = bmc_get_device_id(शून्य, bmc, &id, शून्य, शून्य);
		वापस (!rv && id.aux_firmware_revision_set) ? mode : 0;
	पूर्ण
	अगर (attr == &dev_attr_guid.attr) अणु
		bool guid_set;

		rv = bmc_get_device_id(शून्य, bmc, शून्य, &guid_set, शून्य);
		वापस (!rv && guid_set) ? mode : 0;
	पूर्ण
	वापस mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group bmc_dev_attr_group = अणु
	.attrs		= bmc_dev_attrs,
	.is_visible	= bmc_dev_attr_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *bmc_dev_attr_groups[] = अणु
	&bmc_dev_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा device_type bmc_device_type = अणु
	.groups		= bmc_dev_attr_groups,
पूर्ण;

अटल पूर्णांक __find_bmc_guid(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर guid_t *guid = data;
	काष्ठा bmc_device *bmc;
	पूर्णांक rv;

	अगर (dev->type != &bmc_device_type)
		वापस 0;

	bmc = to_bmc_device(dev);
	rv = bmc->dyn_guid_set && guid_equal(&bmc->guid, guid);
	अगर (rv)
		rv = kref_get_unless_zero(&bmc->usecount);
	वापस rv;
पूर्ण

/*
 * Returns with the bmc's usecount incremented, अगर it is non-शून्य.
 */
अटल काष्ठा bmc_device *ipmi_find_bmc_guid(काष्ठा device_driver *drv,
					     guid_t *guid)
अणु
	काष्ठा device *dev;
	काष्ठा bmc_device *bmc = शून्य;

	dev = driver_find_device(drv, शून्य, guid, __find_bmc_guid);
	अगर (dev) अणु
		bmc = to_bmc_device(dev);
		put_device(dev);
	पूर्ण
	वापस bmc;
पूर्ण

काष्ठा prod_dev_id अणु
	अचिन्हित पूर्णांक  product_id;
	अचिन्हित अक्षर device_id;
पूर्ण;

अटल पूर्णांक __find_bmc_prod_dev_id(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा prod_dev_id *cid = data;
	काष्ठा bmc_device *bmc;
	पूर्णांक rv;

	अगर (dev->type != &bmc_device_type)
		वापस 0;

	bmc = to_bmc_device(dev);
	rv = (bmc->id.product_id == cid->product_id
	      && bmc->id.device_id == cid->device_id);
	अगर (rv)
		rv = kref_get_unless_zero(&bmc->usecount);
	वापस rv;
पूर्ण

/*
 * Returns with the bmc's usecount incremented, अगर it is non-शून्य.
 */
अटल काष्ठा bmc_device *ipmi_find_bmc_prod_dev_id(
	काष्ठा device_driver *drv,
	अचिन्हित पूर्णांक product_id, अचिन्हित अक्षर device_id)
अणु
	काष्ठा prod_dev_id id = अणु
		.product_id = product_id,
		.device_id = device_id,
	पूर्ण;
	काष्ठा device *dev;
	काष्ठा bmc_device *bmc = शून्य;

	dev = driver_find_device(drv, शून्य, &id, __find_bmc_prod_dev_id);
	अगर (dev) अणु
		bmc = to_bmc_device(dev);
		put_device(dev);
	पूर्ण
	वापस bmc;
पूर्ण

अटल DEFINE_IDA(ipmi_bmc_ida);

अटल व्योम
release_bmc_device(काष्ठा device *dev)
अणु
	kमुक्त(to_bmc_device(dev));
पूर्ण

अटल व्योम cleanup_bmc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bmc_device *bmc = container_of(work, काष्ठा bmc_device,
					      हटाओ_work);
	पूर्णांक id = bmc->pdev.id; /* Unरेजिस्टर overग_लिखोs id */

	platक्रमm_device_unरेजिस्टर(&bmc->pdev);
	ida_simple_हटाओ(&ipmi_bmc_ida, id);
पूर्ण

अटल व्योम
cleanup_bmc_device(काष्ठा kref *ref)
अणु
	काष्ठा bmc_device *bmc = container_of(ref, काष्ठा bmc_device, usecount);

	/*
	 * Remove the platक्रमm device in a work queue to aव्योम issues
	 * with removing the device attributes जबतक पढ़ोing a device
	 * attribute.
	 */
	schedule_work(&bmc->हटाओ_work);
पूर्ण

/*
 * Must be called with पूर्णांकf->bmc_reg_mutex held.
 */
अटल व्योम __ipmi_bmc_unरेजिस्टर(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	काष्ठा bmc_device *bmc = पूर्णांकf->bmc;

	अगर (!पूर्णांकf->bmc_रेजिस्टरed)
		वापस;

	sysfs_हटाओ_link(&पूर्णांकf->si_dev->kobj, "bmc");
	sysfs_हटाओ_link(&bmc->pdev.dev.kobj, पूर्णांकf->my_dev_name);
	kमुक्त(पूर्णांकf->my_dev_name);
	पूर्णांकf->my_dev_name = शून्य;

	mutex_lock(&bmc->dyn_mutex);
	list_del(&पूर्णांकf->bmc_link);
	mutex_unlock(&bmc->dyn_mutex);
	पूर्णांकf->bmc = &पूर्णांकf->पंचांगp_bmc;
	kref_put(&bmc->usecount, cleanup_bmc_device);
	पूर्णांकf->bmc_रेजिस्टरed = false;
पूर्ण

अटल व्योम ipmi_bmc_unरेजिस्टर(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	mutex_lock(&पूर्णांकf->bmc_reg_mutex);
	__ipmi_bmc_unरेजिस्टर(पूर्णांकf);
	mutex_unlock(&पूर्णांकf->bmc_reg_mutex);
पूर्ण

/*
 * Must be called with पूर्णांकf->bmc_reg_mutex held.
 */
अटल पूर्णांक __ipmi_bmc_रेजिस्टर(काष्ठा ipmi_smi *पूर्णांकf,
			       काष्ठा ipmi_device_id *id,
			       bool guid_set, guid_t *guid, पूर्णांक पूर्णांकf_num)
अणु
	पूर्णांक               rv;
	काष्ठा bmc_device *bmc;
	काष्ठा bmc_device *old_bmc;

	/*
	 * platक्रमm_device_रेजिस्टर() can cause bmc_reg_mutex to
	 * be claimed because of the is_visible functions of
	 * the attributes.  Eliminate possible recursion and
	 * release the lock.
	 */
	पूर्णांकf->in_bmc_रेजिस्टर = true;
	mutex_unlock(&पूर्णांकf->bmc_reg_mutex);

	/*
	 * Try to find अगर there is an bmc_device काष्ठा
	 * representing the पूर्णांकerfaced BMC alपढ़ोy
	 */
	mutex_lock(&ipmidriver_mutex);
	अगर (guid_set)
		old_bmc = ipmi_find_bmc_guid(&ipmidriver.driver, guid);
	अन्यथा
		old_bmc = ipmi_find_bmc_prod_dev_id(&ipmidriver.driver,
						    id->product_id,
						    id->device_id);

	/*
	 * If there is alपढ़ोy an bmc_device, मुक्त the new one,
	 * otherwise रेजिस्टर the new BMC device
	 */
	अगर (old_bmc) अणु
		bmc = old_bmc;
		/*
		 * Note: old_bmc alपढ़ोy has usecount incremented by
		 * the BMC find functions.
		 */
		पूर्णांकf->bmc = old_bmc;
		mutex_lock(&bmc->dyn_mutex);
		list_add_tail(&पूर्णांकf->bmc_link, &bmc->पूर्णांकfs);
		mutex_unlock(&bmc->dyn_mutex);

		dev_info(पूर्णांकf->si_dev,
			 "interfacing existing BMC (man_id: 0x%6.6x, prod_id: 0x%4.4x, dev_id: 0x%2.2x)\n",
			 bmc->id.manufacturer_id,
			 bmc->id.product_id,
			 bmc->id.device_id);
	पूर्ण अन्यथा अणु
		bmc = kzalloc(माप(*bmc), GFP_KERNEL);
		अगर (!bmc) अणु
			rv = -ENOMEM;
			जाओ out;
		पूर्ण
		INIT_LIST_HEAD(&bmc->पूर्णांकfs);
		mutex_init(&bmc->dyn_mutex);
		INIT_WORK(&bmc->हटाओ_work, cleanup_bmc_work);

		bmc->id = *id;
		bmc->dyn_id_set = 1;
		bmc->dyn_guid_set = guid_set;
		bmc->guid = *guid;
		bmc->dyn_id_expiry = jअगरfies + IPMI_DYN_DEV_ID_EXPIRY;

		bmc->pdev.name = "ipmi_bmc";

		rv = ida_simple_get(&ipmi_bmc_ida, 0, 0, GFP_KERNEL);
		अगर (rv < 0) अणु
			kमुक्त(bmc);
			जाओ out;
		पूर्ण

		bmc->pdev.dev.driver = &ipmidriver.driver;
		bmc->pdev.id = rv;
		bmc->pdev.dev.release = release_bmc_device;
		bmc->pdev.dev.type = &bmc_device_type;
		kref_init(&bmc->usecount);

		पूर्णांकf->bmc = bmc;
		mutex_lock(&bmc->dyn_mutex);
		list_add_tail(&पूर्णांकf->bmc_link, &bmc->पूर्णांकfs);
		mutex_unlock(&bmc->dyn_mutex);

		rv = platक्रमm_device_रेजिस्टर(&bmc->pdev);
		अगर (rv) अणु
			dev_err(पूर्णांकf->si_dev,
				"Unable to register bmc device: %d\n",
				rv);
			जाओ out_list_del;
		पूर्ण

		dev_info(पूर्णांकf->si_dev,
			 "Found new BMC (man_id: 0x%6.6x, prod_id: 0x%4.4x, dev_id: 0x%2.2x)\n",
			 bmc->id.manufacturer_id,
			 bmc->id.product_id,
			 bmc->id.device_id);
	पूर्ण

	/*
	 * create symlink from प्रणाली पूर्णांकerface device to bmc device
	 * and back.
	 */
	rv = sysfs_create_link(&पूर्णांकf->si_dev->kobj, &bmc->pdev.dev.kobj, "bmc");
	अगर (rv) अणु
		dev_err(पूर्णांकf->si_dev, "Unable to create bmc symlink: %d\n", rv);
		जाओ out_put_bmc;
	पूर्ण

	अगर (पूर्णांकf_num == -1)
		पूर्णांकf_num = पूर्णांकf->पूर्णांकf_num;
	पूर्णांकf->my_dev_name = kaप्र_लिखो(GFP_KERNEL, "ipmi%d", पूर्णांकf_num);
	अगर (!पूर्णांकf->my_dev_name) अणु
		rv = -ENOMEM;
		dev_err(पूर्णांकf->si_dev, "Unable to allocate link from BMC: %d\n",
			rv);
		जाओ out_unlink1;
	पूर्ण

	rv = sysfs_create_link(&bmc->pdev.dev.kobj, &पूर्णांकf->si_dev->kobj,
			       पूर्णांकf->my_dev_name);
	अगर (rv) अणु
		dev_err(पूर्णांकf->si_dev, "Unable to create symlink to bmc: %d\n",
			rv);
		जाओ out_मुक्त_my_dev_name;
	पूर्ण

	पूर्णांकf->bmc_रेजिस्टरed = true;

out:
	mutex_unlock(&ipmidriver_mutex);
	mutex_lock(&पूर्णांकf->bmc_reg_mutex);
	पूर्णांकf->in_bmc_रेजिस्टर = false;
	वापस rv;


out_मुक्त_my_dev_name:
	kमुक्त(पूर्णांकf->my_dev_name);
	पूर्णांकf->my_dev_name = शून्य;

out_unlink1:
	sysfs_हटाओ_link(&पूर्णांकf->si_dev->kobj, "bmc");

out_put_bmc:
	mutex_lock(&bmc->dyn_mutex);
	list_del(&पूर्णांकf->bmc_link);
	mutex_unlock(&bmc->dyn_mutex);
	पूर्णांकf->bmc = &पूर्णांकf->पंचांगp_bmc;
	kref_put(&bmc->usecount, cleanup_bmc_device);
	जाओ out;

out_list_del:
	mutex_lock(&bmc->dyn_mutex);
	list_del(&पूर्णांकf->bmc_link);
	mutex_unlock(&bmc->dyn_mutex);
	पूर्णांकf->bmc = &पूर्णांकf->पंचांगp_bmc;
	put_device(&bmc->pdev.dev);
	जाओ out;
पूर्ण

अटल पूर्णांक
send_guid_cmd(काष्ठा ipmi_smi *पूर्णांकf, पूर्णांक chan)
अणु
	काष्ठा kernel_ipmi_msg            msg;
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr si;

	si.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	si.channel = IPMI_BMC_CHANNEL;
	si.lun = 0;

	msg.netfn = IPMI_NETFN_APP_REQUEST;
	msg.cmd = IPMI_GET_DEVICE_GUID_CMD;
	msg.data = शून्य;
	msg.data_len = 0;
	वापस i_ipmi_request(शून्य,
			      पूर्णांकf,
			      (काष्ठा ipmi_addr *) &si,
			      0,
			      &msg,
			      पूर्णांकf,
			      शून्य,
			      शून्य,
			      0,
			      पूर्णांकf->addrinfo[0].address,
			      पूर्णांकf->addrinfo[0].lun,
			      -1, 0);
पूर्ण

अटल व्योम guid_handler(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा ipmi_recv_msg *msg)
अणु
	काष्ठा bmc_device *bmc = पूर्णांकf->bmc;

	अगर ((msg->addr.addr_type != IPMI_SYSTEM_INTERFACE_ADDR_TYPE)
	    || (msg->msg.netfn != IPMI_NETFN_APP_RESPONSE)
	    || (msg->msg.cmd != IPMI_GET_DEVICE_GUID_CMD))
		/* Not क्रम me */
		वापस;

	अगर (msg->msg.data[0] != 0) अणु
		/* Error from getting the GUID, the BMC करोesn't have one. */
		bmc->dyn_guid_set = 0;
		जाओ out;
	पूर्ण

	अगर (msg->msg.data_len < UUID_SIZE + 1) अणु
		bmc->dyn_guid_set = 0;
		dev_warn(पूर्णांकf->si_dev,
			 "The GUID response from the BMC was too short, it was %d but should have been %d.  Assuming GUID is not available.\n",
			 msg->msg.data_len, UUID_SIZE + 1);
		जाओ out;
	पूर्ण

	import_guid(&bmc->fetch_guid, msg->msg.data + 1);
	/*
	 * Make sure the guid data is available beक्रमe setting
	 * dyn_guid_set.
	 */
	smp_wmb();
	bmc->dyn_guid_set = 1;
 out:
	wake_up(&पूर्णांकf->रुकोq);
पूर्ण

अटल व्योम __get_guid(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	पूर्णांक rv;
	काष्ठा bmc_device *bmc = पूर्णांकf->bmc;

	bmc->dyn_guid_set = 2;
	पूर्णांकf->null_user_handler = guid_handler;
	rv = send_guid_cmd(पूर्णांकf, 0);
	अगर (rv)
		/* Send failed, no GUID available. */
		bmc->dyn_guid_set = 0;
	अन्यथा
		रुको_event(पूर्णांकf->रुकोq, bmc->dyn_guid_set != 2);

	/* dyn_guid_set makes the guid data available. */
	smp_rmb();

	पूर्णांकf->null_user_handler = शून्य;
पूर्ण

अटल पूर्णांक
send_channel_info_cmd(काष्ठा ipmi_smi *पूर्णांकf, पूर्णांक chan)
अणु
	काष्ठा kernel_ipmi_msg            msg;
	अचिन्हित अक्षर                     data[1];
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr si;

	si.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	si.channel = IPMI_BMC_CHANNEL;
	si.lun = 0;

	msg.netfn = IPMI_NETFN_APP_REQUEST;
	msg.cmd = IPMI_GET_CHANNEL_INFO_CMD;
	msg.data = data;
	msg.data_len = 1;
	data[0] = chan;
	वापस i_ipmi_request(शून्य,
			      पूर्णांकf,
			      (काष्ठा ipmi_addr *) &si,
			      0,
			      &msg,
			      पूर्णांकf,
			      शून्य,
			      शून्य,
			      0,
			      पूर्णांकf->addrinfo[0].address,
			      पूर्णांकf->addrinfo[0].lun,
			      -1, 0);
पूर्ण

अटल व्योम
channel_handler(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा ipmi_recv_msg *msg)
अणु
	पूर्णांक rv = 0;
	पूर्णांक ch;
	अचिन्हित पूर्णांक set = पूर्णांकf->curr_working_cset;
	काष्ठा ipmi_channel *chans;

	अगर ((msg->addr.addr_type == IPMI_SYSTEM_INTERFACE_ADDR_TYPE)
	    && (msg->msg.netfn == IPMI_NETFN_APP_RESPONSE)
	    && (msg->msg.cmd == IPMI_GET_CHANNEL_INFO_CMD)) अणु
		/* It's the one we want */
		अगर (msg->msg.data[0] != 0) अणु
			/* Got an error from the channel, just go on. */
			अगर (msg->msg.data[0] == IPMI_INVALID_COMMAND_ERR) अणु
				/*
				 * If the MC करोes not support this
				 * command, that is legal.  We just
				 * assume it has one IPMB at channel
				 * zero.
				 */
				पूर्णांकf->wchannels[set].c[0].medium
					= IPMI_CHANNEL_MEDIUM_IPMB;
				पूर्णांकf->wchannels[set].c[0].protocol
					= IPMI_CHANNEL_PROTOCOL_IPMB;

				पूर्णांकf->channel_list = पूर्णांकf->wchannels + set;
				पूर्णांकf->channels_पढ़ोy = true;
				wake_up(&पूर्णांकf->रुकोq);
				जाओ out;
			पूर्ण
			जाओ next_channel;
		पूर्ण
		अगर (msg->msg.data_len < 4) अणु
			/* Message not big enough, just go on. */
			जाओ next_channel;
		पूर्ण
		ch = पूर्णांकf->curr_channel;
		chans = पूर्णांकf->wchannels[set].c;
		chans[ch].medium = msg->msg.data[2] & 0x7f;
		chans[ch].protocol = msg->msg.data[3] & 0x1f;

 next_channel:
		पूर्णांकf->curr_channel++;
		अगर (पूर्णांकf->curr_channel >= IPMI_MAX_CHANNELS) अणु
			पूर्णांकf->channel_list = पूर्णांकf->wchannels + set;
			पूर्णांकf->channels_पढ़ोy = true;
			wake_up(&पूर्णांकf->रुकोq);
		पूर्ण अन्यथा अणु
			पूर्णांकf->channel_list = पूर्णांकf->wchannels + set;
			पूर्णांकf->channels_पढ़ोy = true;
			rv = send_channel_info_cmd(पूर्णांकf, पूर्णांकf->curr_channel);
		पूर्ण

		अगर (rv) अणु
			/* Got an error somehow, just give up. */
			dev_warn(पूर्णांकf->si_dev,
				 "Error sending channel information for channel %d: %d\n",
				 पूर्णांकf->curr_channel, rv);

			पूर्णांकf->channel_list = पूर्णांकf->wchannels + set;
			पूर्णांकf->channels_पढ़ोy = true;
			wake_up(&पूर्णांकf->रुकोq);
		पूर्ण
	पूर्ण
 out:
	वापस;
पूर्ण

/*
 * Must be holding पूर्णांकf->bmc_reg_mutex to call this.
 */
अटल पूर्णांक __scan_channels(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा ipmi_device_id *id)
अणु
	पूर्णांक rv;

	अगर (ipmi_version_major(id) > 1
			|| (ipmi_version_major(id) == 1
			    && ipmi_version_minor(id) >= 5)) अणु
		अचिन्हित पूर्णांक set;

		/*
		 * Start scanning the channels to see what is
		 * available.
		 */
		set = !पूर्णांकf->curr_working_cset;
		पूर्णांकf->curr_working_cset = set;
		स_रखो(&पूर्णांकf->wchannels[set], 0,
		       माप(काष्ठा ipmi_channel_set));

		पूर्णांकf->null_user_handler = channel_handler;
		पूर्णांकf->curr_channel = 0;
		rv = send_channel_info_cmd(पूर्णांकf, 0);
		अगर (rv) अणु
			dev_warn(पूर्णांकf->si_dev,
				 "Error sending channel information for channel 0, %d\n",
				 rv);
			पूर्णांकf->null_user_handler = शून्य;
			वापस -EIO;
		पूर्ण

		/* Wait क्रम the channel info to be पढ़ो. */
		रुको_event(पूर्णांकf->रुकोq, पूर्णांकf->channels_पढ़ोy);
		पूर्णांकf->null_user_handler = शून्य;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक set = पूर्णांकf->curr_working_cset;

		/* Assume a single IPMB channel at zero. */
		पूर्णांकf->wchannels[set].c[0].medium = IPMI_CHANNEL_MEDIUM_IPMB;
		पूर्णांकf->wchannels[set].c[0].protocol = IPMI_CHANNEL_PROTOCOL_IPMB;
		पूर्णांकf->channel_list = पूर्णांकf->wchannels + set;
		पूर्णांकf->channels_पढ़ोy = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ipmi_poll(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	अगर (पूर्णांकf->handlers->poll)
		पूर्णांकf->handlers->poll(पूर्णांकf->send_info);
	/* In हाल something came in */
	handle_new_recv_msgs(पूर्णांकf);
पूर्ण

व्योम ipmi_poll_पूर्णांकerface(काष्ठा ipmi_user *user)
अणु
	ipmi_poll(user->पूर्णांकf);
पूर्ण
EXPORT_SYMBOL(ipmi_poll_पूर्णांकerface);

अटल व्योम reकरो_bmc_reg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ipmi_smi *पूर्णांकf = container_of(work, काष्ठा ipmi_smi,
					     bmc_reg_work);

	अगर (!पूर्णांकf->in_shutकरोwn)
		bmc_get_device_id(पूर्णांकf, शून्य, शून्य, शून्य, शून्य);

	kref_put(&पूर्णांकf->refcount, पूर्णांकf_मुक्त);
पूर्ण

पूर्णांक ipmi_add_smi(काष्ठा module         *owner,
		 स्थिर काष्ठा ipmi_smi_handlers *handlers,
		 व्योम		       *send_info,
		 काष्ठा device         *si_dev,
		 अचिन्हित अक्षर         slave_addr)
अणु
	पूर्णांक              i, j;
	पूर्णांक              rv;
	काष्ठा ipmi_smi *पूर्णांकf, *tपूर्णांकf;
	काष्ठा list_head *link;
	काष्ठा ipmi_device_id id;

	/*
	 * Make sure the driver is actually initialized, this handles
	 * problems with initialization order.
	 */
	rv = ipmi_init_msghandler();
	अगर (rv)
		वापस rv;

	पूर्णांकf = kzalloc(माप(*पूर्णांकf), GFP_KERNEL);
	अगर (!पूर्णांकf)
		वापस -ENOMEM;

	rv = init_srcu_काष्ठा(&पूर्णांकf->users_srcu);
	अगर (rv) अणु
		kमुक्त(पूर्णांकf);
		वापस rv;
	पूर्ण

	पूर्णांकf->owner = owner;
	पूर्णांकf->bmc = &पूर्णांकf->पंचांगp_bmc;
	INIT_LIST_HEAD(&पूर्णांकf->bmc->पूर्णांकfs);
	mutex_init(&पूर्णांकf->bmc->dyn_mutex);
	INIT_LIST_HEAD(&पूर्णांकf->bmc_link);
	mutex_init(&पूर्णांकf->bmc_reg_mutex);
	पूर्णांकf->पूर्णांकf_num = -1; /* Mark it invalid क्रम now. */
	kref_init(&पूर्णांकf->refcount);
	INIT_WORK(&पूर्णांकf->bmc_reg_work, reकरो_bmc_reg);
	पूर्णांकf->si_dev = si_dev;
	क्रम (j = 0; j < IPMI_MAX_CHANNELS; j++) अणु
		पूर्णांकf->addrinfo[j].address = IPMI_BMC_SLAVE_ADDR;
		पूर्णांकf->addrinfo[j].lun = 2;
	पूर्ण
	अगर (slave_addr != 0)
		पूर्णांकf->addrinfo[0].address = slave_addr;
	INIT_LIST_HEAD(&पूर्णांकf->users);
	पूर्णांकf->handlers = handlers;
	पूर्णांकf->send_info = send_info;
	spin_lock_init(&पूर्णांकf->seq_lock);
	क्रम (j = 0; j < IPMI_IPMB_NUM_SEQ; j++) अणु
		पूर्णांकf->seq_table[j].inuse = 0;
		पूर्णांकf->seq_table[j].seqid = 0;
	पूर्ण
	पूर्णांकf->curr_seq = 0;
	spin_lock_init(&पूर्णांकf->रुकोing_rcv_msgs_lock);
	INIT_LIST_HEAD(&पूर्णांकf->रुकोing_rcv_msgs);
	tasklet_setup(&पूर्णांकf->recv_tasklet,
		     smi_recv_tasklet);
	atomic_set(&पूर्णांकf->watchकरोg_preसमयouts_to_deliver, 0);
	spin_lock_init(&पूर्णांकf->xmit_msgs_lock);
	INIT_LIST_HEAD(&पूर्णांकf->xmit_msgs);
	INIT_LIST_HEAD(&पूर्णांकf->hp_xmit_msgs);
	spin_lock_init(&पूर्णांकf->events_lock);
	spin_lock_init(&पूर्णांकf->watch_lock);
	atomic_set(&पूर्णांकf->event_रुकोers, 0);
	पूर्णांकf->ticks_to_req_ev = IPMI_REQUEST_EV_TIME;
	INIT_LIST_HEAD(&पूर्णांकf->रुकोing_events);
	पूर्णांकf->रुकोing_events_count = 0;
	mutex_init(&पूर्णांकf->cmd_rcvrs_mutex);
	spin_lock_init(&पूर्णांकf->मुख्यtenance_mode_lock);
	INIT_LIST_HEAD(&पूर्णांकf->cmd_rcvrs);
	init_रुकोqueue_head(&पूर्णांकf->रुकोq);
	क्रम (i = 0; i < IPMI_NUM_STATS; i++)
		atomic_set(&पूर्णांकf->stats[i], 0);

	mutex_lock(&ipmi_पूर्णांकerfaces_mutex);
	/* Look क्रम a hole in the numbers. */
	i = 0;
	link = &ipmi_पूर्णांकerfaces;
	list_क्रम_each_entry_rcu(tपूर्णांकf, &ipmi_पूर्णांकerfaces, link,
				ipmi_पूर्णांकerfaces_mutex_held()) अणु
		अगर (tपूर्णांकf->पूर्णांकf_num != i) अणु
			link = &tपूर्णांकf->link;
			अवरोध;
		पूर्ण
		i++;
	पूर्ण
	/* Add the new पूर्णांकerface in numeric order. */
	अगर (i == 0)
		list_add_rcu(&पूर्णांकf->link, &ipmi_पूर्णांकerfaces);
	अन्यथा
		list_add_tail_rcu(&पूर्णांकf->link, link);

	rv = handlers->start_processing(send_info, पूर्णांकf);
	अगर (rv)
		जाओ out_err;

	rv = __bmc_get_device_id(पूर्णांकf, शून्य, &id, शून्य, शून्य, i);
	अगर (rv) अणु
		dev_err(si_dev, "Unable to get the device id: %d\n", rv);
		जाओ out_err_started;
	पूर्ण

	mutex_lock(&पूर्णांकf->bmc_reg_mutex);
	rv = __scan_channels(पूर्णांकf, &id);
	mutex_unlock(&पूर्णांकf->bmc_reg_mutex);
	अगर (rv)
		जाओ out_err_bmc_reg;

	/*
	 * Keep memory order straight क्रम RCU पढ़ोers.  Make
	 * sure everything अन्यथा is committed to memory beक्रमe
	 * setting पूर्णांकf_num to mark the पूर्णांकerface valid.
	 */
	smp_wmb();
	पूर्णांकf->पूर्णांकf_num = i;
	mutex_unlock(&ipmi_पूर्णांकerfaces_mutex);

	/* After this poपूर्णांक the पूर्णांकerface is legal to use. */
	call_smi_watchers(i, पूर्णांकf->si_dev);

	वापस 0;

 out_err_bmc_reg:
	ipmi_bmc_unरेजिस्टर(पूर्णांकf);
 out_err_started:
	अगर (पूर्णांकf->handlers->shutकरोwn)
		पूर्णांकf->handlers->shutकरोwn(पूर्णांकf->send_info);
 out_err:
	list_del_rcu(&पूर्णांकf->link);
	mutex_unlock(&ipmi_पूर्णांकerfaces_mutex);
	synchronize_srcu(&ipmi_पूर्णांकerfaces_srcu);
	cleanup_srcu_काष्ठा(&पूर्णांकf->users_srcu);
	kref_put(&पूर्णांकf->refcount, पूर्णांकf_मुक्त);

	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_add_smi);

अटल व्योम deliver_smi_err_response(काष्ठा ipmi_smi *पूर्णांकf,
				     काष्ठा ipmi_smi_msg *msg,
				     अचिन्हित अक्षर err)
अणु
	msg->rsp[0] = msg->data[0] | 4;
	msg->rsp[1] = msg->data[1];
	msg->rsp[2] = err;
	msg->rsp_size = 3;
	/* It's an error, so it will never requeue, no need to check वापस. */
	handle_one_recv_msg(पूर्णांकf, msg);
पूर्ण

अटल व्योम cleanup_smi_msgs(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	पूर्णांक              i;
	काष्ठा seq_table *ent;
	काष्ठा ipmi_smi_msg *msg;
	काष्ठा list_head *entry;
	काष्ठा list_head पंचांगplist;

	/* Clear out our transmit queues and hold the messages. */
	INIT_LIST_HEAD(&पंचांगplist);
	list_splice_tail(&पूर्णांकf->hp_xmit_msgs, &पंचांगplist);
	list_splice_tail(&पूर्णांकf->xmit_msgs, &पंचांगplist);

	/* Current message first, to preserve order */
	जबतक (पूर्णांकf->curr_msg && !list_empty(&पूर्णांकf->रुकोing_rcv_msgs)) अणु
		/* Wait क्रम the message to clear out. */
		schedule_समयout(1);
	पूर्ण

	/* No need क्रम locks, the पूर्णांकerface is करोwn. */

	/*
	 * Return errors क्रम all pending messages in queue and in the
	 * tables रुकोing क्रम remote responses.
	 */
	जबतक (!list_empty(&पंचांगplist)) अणु
		entry = पंचांगplist.next;
		list_del(entry);
		msg = list_entry(entry, काष्ठा ipmi_smi_msg, link);
		deliver_smi_err_response(पूर्णांकf, msg, IPMI_ERR_UNSPECIFIED);
	पूर्ण

	क्रम (i = 0; i < IPMI_IPMB_NUM_SEQ; i++) अणु
		ent = &पूर्णांकf->seq_table[i];
		अगर (!ent->inuse)
			जारी;
		deliver_err_response(पूर्णांकf, ent->recv_msg, IPMI_ERR_UNSPECIFIED);
	पूर्ण
पूर्ण

व्योम ipmi_unरेजिस्टर_smi(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	काष्ठा ipmi_smi_watcher *w;
	पूर्णांक पूर्णांकf_num = पूर्णांकf->पूर्णांकf_num, index;

	mutex_lock(&ipmi_पूर्णांकerfaces_mutex);
	पूर्णांकf->पूर्णांकf_num = -1;
	पूर्णांकf->in_shutकरोwn = true;
	list_del_rcu(&पूर्णांकf->link);
	mutex_unlock(&ipmi_पूर्णांकerfaces_mutex);
	synchronize_srcu(&ipmi_पूर्णांकerfaces_srcu);

	/* At this poपूर्णांक no users can be added to the पूर्णांकerface. */

	/*
	 * Call all the watcher पूर्णांकerfaces to tell them that
	 * an पूर्णांकerface is going away.
	 */
	mutex_lock(&smi_watchers_mutex);
	list_क्रम_each_entry(w, &smi_watchers, link)
		w->smi_gone(पूर्णांकf_num);
	mutex_unlock(&smi_watchers_mutex);

	index = srcu_पढ़ो_lock(&पूर्णांकf->users_srcu);
	जबतक (!list_empty(&पूर्णांकf->users)) अणु
		काष्ठा ipmi_user *user =
			container_of(list_next_rcu(&पूर्णांकf->users),
				     काष्ठा ipmi_user, link);

		_ipmi_destroy_user(user);
	पूर्ण
	srcu_पढ़ो_unlock(&पूर्णांकf->users_srcu, index);

	अगर (पूर्णांकf->handlers->shutकरोwn)
		पूर्णांकf->handlers->shutकरोwn(पूर्णांकf->send_info);

	cleanup_smi_msgs(पूर्णांकf);

	ipmi_bmc_unरेजिस्टर(पूर्णांकf);

	cleanup_srcu_काष्ठा(&पूर्णांकf->users_srcu);
	kref_put(&पूर्णांकf->refcount, पूर्णांकf_मुक्त);
पूर्ण
EXPORT_SYMBOL(ipmi_unरेजिस्टर_smi);

अटल पूर्णांक handle_ipmb_get_msg_rsp(काष्ठा ipmi_smi *पूर्णांकf,
				   काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा ipmi_ipmb_addr ipmb_addr;
	काष्ठा ipmi_recv_msg  *recv_msg;

	/*
	 * This is 11, not 10, because the response must contain a
	 * completion code.
	 */
	अगर (msg->rsp_size < 11) अणु
		/* Message not big enough, just ignore it. */
		ipmi_inc_stat(पूर्णांकf, invalid_ipmb_responses);
		वापस 0;
	पूर्ण

	अगर (msg->rsp[2] != 0) अणु
		/* An error getting the response, just ignore it. */
		वापस 0;
	पूर्ण

	ipmb_addr.addr_type = IPMI_IPMB_ADDR_TYPE;
	ipmb_addr.slave_addr = msg->rsp[6];
	ipmb_addr.channel = msg->rsp[3] & 0x0f;
	ipmb_addr.lun = msg->rsp[7] & 3;

	/*
	 * It's a response from a remote entity.  Look up the sequence
	 * number and handle the response.
	 */
	अगर (पूर्णांकf_find_seq(पूर्णांकf,
			  msg->rsp[7] >> 2,
			  msg->rsp[3] & 0x0f,
			  msg->rsp[8],
			  (msg->rsp[4] >> 2) & (~1),
			  (काष्ठा ipmi_addr *) &ipmb_addr,
			  &recv_msg)) अणु
		/*
		 * We were unable to find the sequence number,
		 * so just nuke the message.
		 */
		ipmi_inc_stat(पूर्णांकf, unhandled_ipmb_responses);
		वापस 0;
	पूर्ण

	स_नकल(recv_msg->msg_data, &msg->rsp[9], msg->rsp_size - 9);
	/*
	 * The other fields matched, so no need to set them, except
	 * क्रम netfn, which needs to be the response that was
	 * वापसed, not the request value.
	 */
	recv_msg->msg.netfn = msg->rsp[4] >> 2;
	recv_msg->msg.data = recv_msg->msg_data;
	recv_msg->msg.data_len = msg->rsp_size - 10;
	recv_msg->recv_type = IPMI_RESPONSE_RECV_TYPE;
	अगर (deliver_response(पूर्णांकf, recv_msg))
		ipmi_inc_stat(पूर्णांकf, unhandled_ipmb_responses);
	अन्यथा
		ipmi_inc_stat(पूर्णांकf, handled_ipmb_responses);

	वापस 0;
पूर्ण

अटल पूर्णांक handle_ipmb_get_msg_cmd(काष्ठा ipmi_smi *पूर्णांकf,
				   काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा cmd_rcvr          *rcvr;
	पूर्णांक                      rv = 0;
	अचिन्हित अक्षर            netfn;
	अचिन्हित अक्षर            cmd;
	अचिन्हित अक्षर            chan;
	काष्ठा ipmi_user         *user = शून्य;
	काष्ठा ipmi_ipmb_addr    *ipmb_addr;
	काष्ठा ipmi_recv_msg     *recv_msg;

	अगर (msg->rsp_size < 10) अणु
		/* Message not big enough, just ignore it. */
		ipmi_inc_stat(पूर्णांकf, invalid_commands);
		वापस 0;
	पूर्ण

	अगर (msg->rsp[2] != 0) अणु
		/* An error getting the response, just ignore it. */
		वापस 0;
	पूर्ण

	netfn = msg->rsp[4] >> 2;
	cmd = msg->rsp[8];
	chan = msg->rsp[3] & 0xf;

	rcu_पढ़ो_lock();
	rcvr = find_cmd_rcvr(पूर्णांकf, netfn, cmd, chan);
	अगर (rcvr) अणु
		user = rcvr->user;
		kref_get(&user->refcount);
	पूर्ण अन्यथा
		user = शून्य;
	rcu_पढ़ो_unlock();

	अगर (user == शून्य) अणु
		/* We didn't find a user, deliver an error response. */
		ipmi_inc_stat(पूर्णांकf, unhandled_commands);

		msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
		msg->data[1] = IPMI_SEND_MSG_CMD;
		msg->data[2] = msg->rsp[3];
		msg->data[3] = msg->rsp[6];
		msg->data[4] = ((netfn + 1) << 2) | (msg->rsp[7] & 0x3);
		msg->data[5] = ipmb_checksum(&msg->data[3], 2);
		msg->data[6] = पूर्णांकf->addrinfo[msg->rsp[3] & 0xf].address;
		/* rqseq/lun */
		msg->data[7] = (msg->rsp[7] & 0xfc) | (msg->rsp[4] & 0x3);
		msg->data[8] = msg->rsp[8]; /* cmd */
		msg->data[9] = IPMI_INVALID_CMD_COMPLETION_CODE;
		msg->data[10] = ipmb_checksum(&msg->data[6], 4);
		msg->data_size = 11;

		pr_debug("Invalid command: %*ph\n", msg->data_size, msg->data);

		rcu_पढ़ो_lock();
		अगर (!पूर्णांकf->in_shutकरोwn) अणु
			smi_send(पूर्णांकf, पूर्णांकf->handlers, msg, 0);
			/*
			 * We used the message, so वापस the value
			 * that causes it to not be मुक्तd or
			 * queued.
			 */
			rv = -1;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		recv_msg = ipmi_alloc_recv_msg();
		अगर (!recv_msg) अणु
			/*
			 * We couldn't allocate memory क्रम the
			 * message, so requeue it क्रम handling
			 * later.
			 */
			rv = 1;
			kref_put(&user->refcount, मुक्त_user);
		पूर्ण अन्यथा अणु
			/* Extract the source address from the data. */
			ipmb_addr = (काष्ठा ipmi_ipmb_addr *) &recv_msg->addr;
			ipmb_addr->addr_type = IPMI_IPMB_ADDR_TYPE;
			ipmb_addr->slave_addr = msg->rsp[6];
			ipmb_addr->lun = msg->rsp[7] & 3;
			ipmb_addr->channel = msg->rsp[3] & 0xf;

			/*
			 * Extract the rest of the message inक्रमmation
			 * from the IPMB header.
			 */
			recv_msg->user = user;
			recv_msg->recv_type = IPMI_CMD_RECV_TYPE;
			recv_msg->msgid = msg->rsp[7] >> 2;
			recv_msg->msg.netfn = msg->rsp[4] >> 2;
			recv_msg->msg.cmd = msg->rsp[8];
			recv_msg->msg.data = recv_msg->msg_data;

			/*
			 * We chop off 10, not 9 bytes because the checksum
			 * at the end also needs to be हटाओd.
			 */
			recv_msg->msg.data_len = msg->rsp_size - 10;
			स_नकल(recv_msg->msg_data, &msg->rsp[9],
			       msg->rsp_size - 10);
			अगर (deliver_response(पूर्णांकf, recv_msg))
				ipmi_inc_stat(पूर्णांकf, unhandled_commands);
			अन्यथा
				ipmi_inc_stat(पूर्णांकf, handled_commands);
		पूर्ण
	पूर्ण

	वापस rv;
पूर्ण

अटल पूर्णांक handle_lan_get_msg_rsp(काष्ठा ipmi_smi *पूर्णांकf,
				  काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा ipmi_lan_addr  lan_addr;
	काष्ठा ipmi_recv_msg  *recv_msg;


	/*
	 * This is 13, not 12, because the response must contain a
	 * completion code.
	 */
	अगर (msg->rsp_size < 13) अणु
		/* Message not big enough, just ignore it. */
		ipmi_inc_stat(पूर्णांकf, invalid_lan_responses);
		वापस 0;
	पूर्ण

	अगर (msg->rsp[2] != 0) अणु
		/* An error getting the response, just ignore it. */
		वापस 0;
	पूर्ण

	lan_addr.addr_type = IPMI_LAN_ADDR_TYPE;
	lan_addr.session_handle = msg->rsp[4];
	lan_addr.remote_SWID = msg->rsp[8];
	lan_addr.local_SWID = msg->rsp[5];
	lan_addr.channel = msg->rsp[3] & 0x0f;
	lan_addr.privilege = msg->rsp[3] >> 4;
	lan_addr.lun = msg->rsp[9] & 3;

	/*
	 * It's a response from a remote entity.  Look up the sequence
	 * number and handle the response.
	 */
	अगर (पूर्णांकf_find_seq(पूर्णांकf,
			  msg->rsp[9] >> 2,
			  msg->rsp[3] & 0x0f,
			  msg->rsp[10],
			  (msg->rsp[6] >> 2) & (~1),
			  (काष्ठा ipmi_addr *) &lan_addr,
			  &recv_msg)) अणु
		/*
		 * We were unable to find the sequence number,
		 * so just nuke the message.
		 */
		ipmi_inc_stat(पूर्णांकf, unhandled_lan_responses);
		वापस 0;
	पूर्ण

	स_नकल(recv_msg->msg_data, &msg->rsp[11], msg->rsp_size - 11);
	/*
	 * The other fields matched, so no need to set them, except
	 * क्रम netfn, which needs to be the response that was
	 * वापसed, not the request value.
	 */
	recv_msg->msg.netfn = msg->rsp[6] >> 2;
	recv_msg->msg.data = recv_msg->msg_data;
	recv_msg->msg.data_len = msg->rsp_size - 12;
	recv_msg->recv_type = IPMI_RESPONSE_RECV_TYPE;
	अगर (deliver_response(पूर्णांकf, recv_msg))
		ipmi_inc_stat(पूर्णांकf, unhandled_lan_responses);
	अन्यथा
		ipmi_inc_stat(पूर्णांकf, handled_lan_responses);

	वापस 0;
पूर्ण

अटल पूर्णांक handle_lan_get_msg_cmd(काष्ठा ipmi_smi *पूर्णांकf,
				  काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा cmd_rcvr          *rcvr;
	पूर्णांक                      rv = 0;
	अचिन्हित अक्षर            netfn;
	अचिन्हित अक्षर            cmd;
	अचिन्हित अक्षर            chan;
	काष्ठा ipmi_user         *user = शून्य;
	काष्ठा ipmi_lan_addr     *lan_addr;
	काष्ठा ipmi_recv_msg     *recv_msg;

	अगर (msg->rsp_size < 12) अणु
		/* Message not big enough, just ignore it. */
		ipmi_inc_stat(पूर्णांकf, invalid_commands);
		वापस 0;
	पूर्ण

	अगर (msg->rsp[2] != 0) अणु
		/* An error getting the response, just ignore it. */
		वापस 0;
	पूर्ण

	netfn = msg->rsp[6] >> 2;
	cmd = msg->rsp[10];
	chan = msg->rsp[3] & 0xf;

	rcu_पढ़ो_lock();
	rcvr = find_cmd_rcvr(पूर्णांकf, netfn, cmd, chan);
	अगर (rcvr) अणु
		user = rcvr->user;
		kref_get(&user->refcount);
	पूर्ण अन्यथा
		user = शून्य;
	rcu_पढ़ो_unlock();

	अगर (user == शून्य) अणु
		/* We didn't find a user, just give up. */
		ipmi_inc_stat(पूर्णांकf, unhandled_commands);

		/*
		 * Don't करो anything with these messages, just allow
		 * them to be मुक्तd.
		 */
		rv = 0;
	पूर्ण अन्यथा अणु
		recv_msg = ipmi_alloc_recv_msg();
		अगर (!recv_msg) अणु
			/*
			 * We couldn't allocate memory क्रम the
			 * message, so requeue it क्रम handling later.
			 */
			rv = 1;
			kref_put(&user->refcount, मुक्त_user);
		पूर्ण अन्यथा अणु
			/* Extract the source address from the data. */
			lan_addr = (काष्ठा ipmi_lan_addr *) &recv_msg->addr;
			lan_addr->addr_type = IPMI_LAN_ADDR_TYPE;
			lan_addr->session_handle = msg->rsp[4];
			lan_addr->remote_SWID = msg->rsp[8];
			lan_addr->local_SWID = msg->rsp[5];
			lan_addr->lun = msg->rsp[9] & 3;
			lan_addr->channel = msg->rsp[3] & 0xf;
			lan_addr->privilege = msg->rsp[3] >> 4;

			/*
			 * Extract the rest of the message inक्रमmation
			 * from the IPMB header.
			 */
			recv_msg->user = user;
			recv_msg->recv_type = IPMI_CMD_RECV_TYPE;
			recv_msg->msgid = msg->rsp[9] >> 2;
			recv_msg->msg.netfn = msg->rsp[6] >> 2;
			recv_msg->msg.cmd = msg->rsp[10];
			recv_msg->msg.data = recv_msg->msg_data;

			/*
			 * We chop off 12, not 11 bytes because the checksum
			 * at the end also needs to be हटाओd.
			 */
			recv_msg->msg.data_len = msg->rsp_size - 12;
			स_नकल(recv_msg->msg_data, &msg->rsp[11],
			       msg->rsp_size - 12);
			अगर (deliver_response(पूर्णांकf, recv_msg))
				ipmi_inc_stat(पूर्णांकf, unhandled_commands);
			अन्यथा
				ipmi_inc_stat(पूर्णांकf, handled_commands);
		पूर्ण
	पूर्ण

	वापस rv;
पूर्ण

/*
 * This routine will handle "Get Message" command responses with
 * channels that use an OEM Medium. The message क्रमmat beदीर्घs to
 * the OEM.  See IPMI 2.0 specअगरication, Chapter 6 and
 * Chapter 22, sections 22.6 and 22.24 क्रम more details.
 */
अटल पूर्णांक handle_oem_get_msg_cmd(काष्ठा ipmi_smi *पूर्णांकf,
				  काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा cmd_rcvr       *rcvr;
	पूर्णांक                   rv = 0;
	अचिन्हित अक्षर         netfn;
	अचिन्हित अक्षर         cmd;
	अचिन्हित अक्षर         chan;
	काष्ठा ipmi_user *user = शून्य;
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *smi_addr;
	काष्ठा ipmi_recv_msg  *recv_msg;

	/*
	 * We expect the OEM SW to perक्रमm error checking
	 * so we just करो some basic sanity checks
	 */
	अगर (msg->rsp_size < 4) अणु
		/* Message not big enough, just ignore it. */
		ipmi_inc_stat(पूर्णांकf, invalid_commands);
		वापस 0;
	पूर्ण

	अगर (msg->rsp[2] != 0) अणु
		/* An error getting the response, just ignore it. */
		वापस 0;
	पूर्ण

	/*
	 * This is an OEM Message so the OEM needs to know how
	 * handle the message. We करो no पूर्णांकerpretation.
	 */
	netfn = msg->rsp[0] >> 2;
	cmd = msg->rsp[1];
	chan = msg->rsp[3] & 0xf;

	rcu_पढ़ो_lock();
	rcvr = find_cmd_rcvr(पूर्णांकf, netfn, cmd, chan);
	अगर (rcvr) अणु
		user = rcvr->user;
		kref_get(&user->refcount);
	पूर्ण अन्यथा
		user = शून्य;
	rcu_पढ़ो_unlock();

	अगर (user == शून्य) अणु
		/* We didn't find a user, just give up. */
		ipmi_inc_stat(पूर्णांकf, unhandled_commands);

		/*
		 * Don't करो anything with these messages, just allow
		 * them to be मुक्तd.
		 */

		rv = 0;
	पूर्ण अन्यथा अणु
		recv_msg = ipmi_alloc_recv_msg();
		अगर (!recv_msg) अणु
			/*
			 * We couldn't allocate memory क्रम the
			 * message, so requeue it क्रम handling
			 * later.
			 */
			rv = 1;
			kref_put(&user->refcount, मुक्त_user);
		पूर्ण अन्यथा अणु
			/*
			 * OEM Messages are expected to be delivered via
			 * the प्रणाली पूर्णांकerface to SMS software.  We might
			 * need to visit this again depending on OEM
			 * requirements
			 */
			smi_addr = ((काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *)
				    &recv_msg->addr);
			smi_addr->addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
			smi_addr->channel = IPMI_BMC_CHANNEL;
			smi_addr->lun = msg->rsp[0] & 3;

			recv_msg->user = user;
			recv_msg->user_msg_data = शून्य;
			recv_msg->recv_type = IPMI_OEM_RECV_TYPE;
			recv_msg->msg.netfn = msg->rsp[0] >> 2;
			recv_msg->msg.cmd = msg->rsp[1];
			recv_msg->msg.data = recv_msg->msg_data;

			/*
			 * The message starts at byte 4 which follows the
			 * the Channel Byte in the "GET MESSAGE" command
			 */
			recv_msg->msg.data_len = msg->rsp_size - 4;
			स_नकल(recv_msg->msg_data, &msg->rsp[4],
			       msg->rsp_size - 4);
			अगर (deliver_response(पूर्णांकf, recv_msg))
				ipmi_inc_stat(पूर्णांकf, unhandled_commands);
			अन्यथा
				ipmi_inc_stat(पूर्णांकf, handled_commands);
		पूर्ण
	पूर्ण

	वापस rv;
पूर्ण

अटल व्योम copy_event_पूर्णांकo_recv_msg(काष्ठा ipmi_recv_msg *recv_msg,
				     काष्ठा ipmi_smi_msg  *msg)
अणु
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *smi_addr;

	recv_msg->msgid = 0;
	smi_addr = (काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *) &recv_msg->addr;
	smi_addr->addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr->channel = IPMI_BMC_CHANNEL;
	smi_addr->lun = msg->rsp[0] & 3;
	recv_msg->recv_type = IPMI_ASYNC_EVENT_RECV_TYPE;
	recv_msg->msg.netfn = msg->rsp[0] >> 2;
	recv_msg->msg.cmd = msg->rsp[1];
	स_नकल(recv_msg->msg_data, &msg->rsp[3], msg->rsp_size - 3);
	recv_msg->msg.data = recv_msg->msg_data;
	recv_msg->msg.data_len = msg->rsp_size - 3;
पूर्ण

अटल पूर्णांक handle_पढ़ो_event_rsp(काष्ठा ipmi_smi *पूर्णांकf,
				 काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा ipmi_recv_msg *recv_msg, *recv_msg2;
	काष्ठा list_head     msgs;
	काष्ठा ipmi_user     *user;
	पूर्णांक rv = 0, deliver_count = 0, index;
	अचिन्हित दीर्घ        flags;

	अगर (msg->rsp_size < 19) अणु
		/* Message is too small to be an IPMB event. */
		ipmi_inc_stat(पूर्णांकf, invalid_events);
		वापस 0;
	पूर्ण

	अगर (msg->rsp[2] != 0) अणु
		/* An error getting the event, just ignore it. */
		वापस 0;
	पूर्ण

	INIT_LIST_HEAD(&msgs);

	spin_lock_irqsave(&पूर्णांकf->events_lock, flags);

	ipmi_inc_stat(पूर्णांकf, events);

	/*
	 * Allocate and fill in one message क्रम every user that is
	 * getting events.
	 */
	index = srcu_पढ़ो_lock(&पूर्णांकf->users_srcu);
	list_क्रम_each_entry_rcu(user, &पूर्णांकf->users, link) अणु
		अगर (!user->माला_लो_events)
			जारी;

		recv_msg = ipmi_alloc_recv_msg();
		अगर (!recv_msg) अणु
			rcu_पढ़ो_unlock();
			list_क्रम_each_entry_safe(recv_msg, recv_msg2, &msgs,
						 link) अणु
				list_del(&recv_msg->link);
				ipmi_मुक्त_recv_msg(recv_msg);
			पूर्ण
			/*
			 * We couldn't allocate memory क्रम the
			 * message, so requeue it क्रम handling
			 * later.
			 */
			rv = 1;
			जाओ out;
		पूर्ण

		deliver_count++;

		copy_event_पूर्णांकo_recv_msg(recv_msg, msg);
		recv_msg->user = user;
		kref_get(&user->refcount);
		list_add_tail(&recv_msg->link, &msgs);
	पूर्ण
	srcu_पढ़ो_unlock(&पूर्णांकf->users_srcu, index);

	अगर (deliver_count) अणु
		/* Now deliver all the messages. */
		list_क्रम_each_entry_safe(recv_msg, recv_msg2, &msgs, link) अणु
			list_del(&recv_msg->link);
			deliver_local_response(पूर्णांकf, recv_msg);
		पूर्ण
	पूर्ण अन्यथा अगर (पूर्णांकf->रुकोing_events_count < MAX_EVENTS_IN_QUEUE) अणु
		/*
		 * No one to receive the message, put it in queue अगर there's
		 * not alपढ़ोy too many things in the queue.
		 */
		recv_msg = ipmi_alloc_recv_msg();
		अगर (!recv_msg) अणु
			/*
			 * We couldn't allocate memory क्रम the
			 * message, so requeue it क्रम handling
			 * later.
			 */
			rv = 1;
			जाओ out;
		पूर्ण

		copy_event_पूर्णांकo_recv_msg(recv_msg, msg);
		list_add_tail(&recv_msg->link, &पूर्णांकf->रुकोing_events);
		पूर्णांकf->रुकोing_events_count++;
	पूर्ण अन्यथा अगर (!पूर्णांकf->event_msg_prपूर्णांकed) अणु
		/*
		 * There's too many things in the queue, discard this
		 * message.
		 */
		dev_warn(पूर्णांकf->si_dev,
			 "Event queue full, discarding incoming events\n");
		पूर्णांकf->event_msg_prपूर्णांकed = 1;
	पूर्ण

 out:
	spin_unlock_irqrestore(&पूर्णांकf->events_lock, flags);

	वापस rv;
पूर्ण

अटल पूर्णांक handle_bmc_rsp(काष्ठा ipmi_smi *पूर्णांकf,
			  काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा ipmi_recv_msg *recv_msg;
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *smi_addr;

	recv_msg = (काष्ठा ipmi_recv_msg *) msg->user_data;
	अगर (recv_msg == शून्य) अणु
		dev_warn(पूर्णांकf->si_dev,
			 "IPMI message received with no owner. This could be because of a malformed message, or because of a hardware error.  Contact your hardware vendor for assistance.\n");
		वापस 0;
	पूर्ण

	recv_msg->recv_type = IPMI_RESPONSE_RECV_TYPE;
	recv_msg->msgid = msg->msgid;
	smi_addr = ((काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *)
		    &recv_msg->addr);
	smi_addr->addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr->channel = IPMI_BMC_CHANNEL;
	smi_addr->lun = msg->rsp[0] & 3;
	recv_msg->msg.netfn = msg->rsp[0] >> 2;
	recv_msg->msg.cmd = msg->rsp[1];
	स_नकल(recv_msg->msg_data, &msg->rsp[2], msg->rsp_size - 2);
	recv_msg->msg.data = recv_msg->msg_data;
	recv_msg->msg.data_len = msg->rsp_size - 2;
	deliver_local_response(पूर्णांकf, recv_msg);

	वापस 0;
पूर्ण

/*
 * Handle a received message.  Return 1 अगर the message should be requeued,
 * 0 अगर the message should be मुक्तd, or -1 अगर the message should not
 * be मुक्तd or requeued.
 */
अटल पूर्णांक handle_one_recv_msg(काष्ठा ipmi_smi *पूर्णांकf,
			       काष्ठा ipmi_smi_msg *msg)
अणु
	पूर्णांक requeue;
	पूर्णांक chan;

	pr_debug("Recv: %*ph\n", msg->rsp_size, msg->rsp);

	अगर ((msg->data_size >= 2)
	    && (msg->data[0] == (IPMI_NETFN_APP_REQUEST << 2))
	    && (msg->data[1] == IPMI_SEND_MSG_CMD)
	    && (msg->user_data == शून्य)) अणु

		अगर (पूर्णांकf->in_shutकरोwn)
			जाओ मुक्त_msg;

		/*
		 * This is the local response to a command send, start
		 * the समयr क्रम these.  The user_data will not be
		 * शून्य अगर this is a response send, and we will let
		 * response sends just go through.
		 */

		/*
		 * Check क्रम errors, अगर we get certain errors (ones
		 * that mean basically we can try again later), we
		 * ignore them and start the समयr.  Otherwise we
		 * report the error immediately.
		 */
		अगर ((msg->rsp_size >= 3) && (msg->rsp[2] != 0)
		    && (msg->rsp[2] != IPMI_NODE_BUSY_ERR)
		    && (msg->rsp[2] != IPMI_LOST_ARBITRATION_ERR)
		    && (msg->rsp[2] != IPMI_BUS_ERR)
		    && (msg->rsp[2] != IPMI_NAK_ON_WRITE_ERR)) अणु
			पूर्णांक ch = msg->rsp[3] & 0xf;
			काष्ठा ipmi_channel *chans;

			/* Got an error sending the message, handle it. */

			chans = READ_ONCE(पूर्णांकf->channel_list)->c;
			अगर ((chans[ch].medium == IPMI_CHANNEL_MEDIUM_8023LAN)
			    || (chans[ch].medium == IPMI_CHANNEL_MEDIUM_ASYNC))
				ipmi_inc_stat(पूर्णांकf, sent_lan_command_errs);
			अन्यथा
				ipmi_inc_stat(पूर्णांकf, sent_ipmb_command_errs);
			पूर्णांकf_err_seq(पूर्णांकf, msg->msgid, msg->rsp[2]);
		पूर्ण अन्यथा
			/* The message was sent, start the समयr. */
			पूर्णांकf_start_seq_समयr(पूर्णांकf, msg->msgid);
मुक्त_msg:
		requeue = 0;
		जाओ out;

	पूर्ण अन्यथा अगर (msg->rsp_size < 2) अणु
		/* Message is too small to be correct. */
		dev_warn(पूर्णांकf->si_dev,
			 "BMC returned too small a message for netfn %x cmd %x, got %d bytes\n",
			 (msg->data[0] >> 2) | 1, msg->data[1], msg->rsp_size);

		/* Generate an error response क्रम the message. */
		msg->rsp[0] = msg->data[0] | (1 << 2);
		msg->rsp[1] = msg->data[1];
		msg->rsp[2] = IPMI_ERR_UNSPECIFIED;
		msg->rsp_size = 3;
	पूर्ण अन्यथा अगर (((msg->rsp[0] >> 2) != ((msg->data[0] >> 2) | 1))
		   || (msg->rsp[1] != msg->data[1])) अणु
		/*
		 * The NetFN and Command in the response is not even
		 * marginally correct.
		 */
		dev_warn(पूर्णांकf->si_dev,
			 "BMC returned incorrect response, expected netfn %x cmd %x, got netfn %x cmd %x\n",
			 (msg->data[0] >> 2) | 1, msg->data[1],
			 msg->rsp[0] >> 2, msg->rsp[1]);

		/* Generate an error response क्रम the message. */
		msg->rsp[0] = msg->data[0] | (1 << 2);
		msg->rsp[1] = msg->data[1];
		msg->rsp[2] = IPMI_ERR_UNSPECIFIED;
		msg->rsp_size = 3;
	पूर्ण

	अगर ((msg->rsp[0] == ((IPMI_NETFN_APP_REQUEST|1) << 2))
	    && (msg->rsp[1] == IPMI_SEND_MSG_CMD)
	    && (msg->user_data != शून्य)) अणु
		/*
		 * It's a response to a response we sent.  For this we
		 * deliver a send message response to the user.
		 */
		काष्ठा ipmi_recv_msg *recv_msg = msg->user_data;

		requeue = 0;
		अगर (msg->rsp_size < 2)
			/* Message is too small to be correct. */
			जाओ out;

		chan = msg->data[2] & 0x0f;
		अगर (chan >= IPMI_MAX_CHANNELS)
			/* Invalid channel number */
			जाओ out;

		अगर (!recv_msg)
			जाओ out;

		recv_msg->recv_type = IPMI_RESPONSE_RESPONSE_TYPE;
		recv_msg->msg.data = recv_msg->msg_data;
		recv_msg->msg.data_len = 1;
		recv_msg->msg_data[0] = msg->rsp[2];
		deliver_local_response(पूर्णांकf, recv_msg);
	पूर्ण अन्यथा अगर ((msg->rsp[0] == ((IPMI_NETFN_APP_REQUEST|1) << 2))
		   && (msg->rsp[1] == IPMI_GET_MSG_CMD)) अणु
		काष्ठा ipmi_channel   *chans;

		/* It's from the receive queue. */
		chan = msg->rsp[3] & 0xf;
		अगर (chan >= IPMI_MAX_CHANNELS) अणु
			/* Invalid channel number */
			requeue = 0;
			जाओ out;
		पूर्ण

		/*
		 * We need to make sure the channels have been initialized.
		 * The channel_handler routine will set the "curr_channel"
		 * equal to or greater than IPMI_MAX_CHANNELS when all the
		 * channels क्रम this पूर्णांकerface have been initialized.
		 */
		अगर (!पूर्णांकf->channels_पढ़ोy) अणु
			requeue = 0; /* Throw the message away */
			जाओ out;
		पूर्ण

		chans = READ_ONCE(पूर्णांकf->channel_list)->c;

		चयन (chans[chan].medium) अणु
		हाल IPMI_CHANNEL_MEDIUM_IPMB:
			अगर (msg->rsp[4] & 0x04) अणु
				/*
				 * It's a response, so find the
				 * requesting message and send it up.
				 */
				requeue = handle_ipmb_get_msg_rsp(पूर्णांकf, msg);
			पूर्ण अन्यथा अणु
				/*
				 * It's a command to the SMS from some other
				 * entity.  Handle that.
				 */
				requeue = handle_ipmb_get_msg_cmd(पूर्णांकf, msg);
			पूर्ण
			अवरोध;

		हाल IPMI_CHANNEL_MEDIUM_8023LAN:
		हाल IPMI_CHANNEL_MEDIUM_ASYNC:
			अगर (msg->rsp[6] & 0x04) अणु
				/*
				 * It's a response, so find the
				 * requesting message and send it up.
				 */
				requeue = handle_lan_get_msg_rsp(पूर्णांकf, msg);
			पूर्ण अन्यथा अणु
				/*
				 * It's a command to the SMS from some other
				 * entity.  Handle that.
				 */
				requeue = handle_lan_get_msg_cmd(पूर्णांकf, msg);
			पूर्ण
			अवरोध;

		शेष:
			/* Check क्रम OEM Channels.  Clients had better
			   रेजिस्टर क्रम these commands. */
			अगर ((chans[chan].medium >= IPMI_CHANNEL_MEDIUM_OEM_MIN)
			    && (chans[chan].medium
				<= IPMI_CHANNEL_MEDIUM_OEM_MAX)) अणु
				requeue = handle_oem_get_msg_cmd(पूर्णांकf, msg);
			पूर्ण अन्यथा अणु
				/*
				 * We करोn't handle the channel type, so just
				 * मुक्त the message.
				 */
				requeue = 0;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर ((msg->rsp[0] == ((IPMI_NETFN_APP_REQUEST|1) << 2))
		   && (msg->rsp[1] == IPMI_READ_EVENT_MSG_BUFFER_CMD)) अणु
		/* It's an asynchronous event. */
		requeue = handle_पढ़ो_event_rsp(पूर्णांकf, msg);
	पूर्ण अन्यथा अणु
		/* It's a response from the local BMC. */
		requeue = handle_bmc_rsp(पूर्णांकf, msg);
	पूर्ण

 out:
	वापस requeue;
पूर्ण

/*
 * If there are messages in the queue or preसमयouts, handle them.
 */
अटल व्योम handle_new_recv_msgs(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	काष्ठा ipmi_smi_msg  *smi_msg;
	अचिन्हित दीर्घ        flags = 0;
	पूर्णांक                  rv;
	पूर्णांक                  run_to_completion = पूर्णांकf->run_to_completion;

	/* See अगर any रुकोing messages need to be processed. */
	अगर (!run_to_completion)
		spin_lock_irqsave(&पूर्णांकf->रुकोing_rcv_msgs_lock, flags);
	जबतक (!list_empty(&पूर्णांकf->रुकोing_rcv_msgs)) अणु
		smi_msg = list_entry(पूर्णांकf->रुकोing_rcv_msgs.next,
				     काष्ठा ipmi_smi_msg, link);
		list_del(&smi_msg->link);
		अगर (!run_to_completion)
			spin_unlock_irqrestore(&पूर्णांकf->रुकोing_rcv_msgs_lock,
					       flags);
		rv = handle_one_recv_msg(पूर्णांकf, smi_msg);
		अगर (!run_to_completion)
			spin_lock_irqsave(&पूर्णांकf->रुकोing_rcv_msgs_lock, flags);
		अगर (rv > 0) अणु
			/*
			 * To preserve message order, quit अगर we
			 * can't handle a message.  Add the message
			 * back at the head, this is safe because this
			 * tasklet is the only thing that pulls the
			 * messages.
			 */
			list_add(&smi_msg->link, &पूर्णांकf->रुकोing_rcv_msgs);
			अवरोध;
		पूर्ण अन्यथा अणु
			अगर (rv == 0)
				/* Message handled */
				ipmi_मुक्त_smi_msg(smi_msg);
			/* If rv < 0, fatal error, del but करोn't मुक्त. */
		पूर्ण
	पूर्ण
	अगर (!run_to_completion)
		spin_unlock_irqrestore(&पूर्णांकf->रुकोing_rcv_msgs_lock, flags);

	/*
	 * If the pretimout count is non-zero, decrement one from it and
	 * deliver preसमयouts to all the users.
	 */
	अगर (atomic_add_unless(&पूर्णांकf->watchकरोg_preसमयouts_to_deliver, -1, 0)) अणु
		काष्ठा ipmi_user *user;
		पूर्णांक index;

		index = srcu_पढ़ो_lock(&पूर्णांकf->users_srcu);
		list_क्रम_each_entry_rcu(user, &पूर्णांकf->users, link) अणु
			अगर (user->handler->ipmi_watchकरोg_preसमयout)
				user->handler->ipmi_watchकरोg_preसमयout(
					user->handler_data);
		पूर्ण
		srcu_पढ़ो_unlock(&पूर्णांकf->users_srcu, index);
	पूर्ण
पूर्ण

अटल व्योम smi_recv_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	अचिन्हित दीर्घ flags = 0; /* keep us warning-मुक्त. */
	काष्ठा ipmi_smi *पूर्णांकf = from_tasklet(पूर्णांकf, t, recv_tasklet);
	पूर्णांक run_to_completion = पूर्णांकf->run_to_completion;
	काष्ठा ipmi_smi_msg *newmsg = शून्य;

	/*
	 * Start the next message अगर available.
	 *
	 * Do this here, not in the actual receiver, because we may deadlock
	 * because the lower layer is allowed to hold locks जबतक calling
	 * message delivery.
	 */

	rcu_पढ़ो_lock();

	अगर (!run_to_completion)
		spin_lock_irqsave(&पूर्णांकf->xmit_msgs_lock, flags);
	अगर (पूर्णांकf->curr_msg == शून्य && !पूर्णांकf->in_shutकरोwn) अणु
		काष्ठा list_head *entry = शून्य;

		/* Pick the high priority queue first. */
		अगर (!list_empty(&पूर्णांकf->hp_xmit_msgs))
			entry = पूर्णांकf->hp_xmit_msgs.next;
		अन्यथा अगर (!list_empty(&पूर्णांकf->xmit_msgs))
			entry = पूर्णांकf->xmit_msgs.next;

		अगर (entry) अणु
			list_del(entry);
			newmsg = list_entry(entry, काष्ठा ipmi_smi_msg, link);
			पूर्णांकf->curr_msg = newmsg;
		पूर्ण
	पूर्ण

	अगर (!run_to_completion)
		spin_unlock_irqrestore(&पूर्णांकf->xmit_msgs_lock, flags);
	अगर (newmsg)
		पूर्णांकf->handlers->sender(पूर्णांकf->send_info, newmsg);

	rcu_पढ़ो_unlock();

	handle_new_recv_msgs(पूर्णांकf);
पूर्ण

/* Handle a new message from the lower layer. */
व्योम ipmi_smi_msg_received(काष्ठा ipmi_smi *पूर्णांकf,
			   काष्ठा ipmi_smi_msg *msg)
अणु
	अचिन्हित दीर्घ flags = 0; /* keep us warning-मुक्त. */
	पूर्णांक run_to_completion = पूर्णांकf->run_to_completion;

	/*
	 * To preserve message order, we keep a queue and deliver from
	 * a tasklet.
	 */
	अगर (!run_to_completion)
		spin_lock_irqsave(&पूर्णांकf->रुकोing_rcv_msgs_lock, flags);
	list_add_tail(&msg->link, &पूर्णांकf->रुकोing_rcv_msgs);
	अगर (!run_to_completion)
		spin_unlock_irqrestore(&पूर्णांकf->रुकोing_rcv_msgs_lock,
				       flags);

	अगर (!run_to_completion)
		spin_lock_irqsave(&पूर्णांकf->xmit_msgs_lock, flags);
	/*
	 * We can get an asynchronous event or receive message in addition
	 * to commands we send.
	 */
	अगर (msg == पूर्णांकf->curr_msg)
		पूर्णांकf->curr_msg = शून्य;
	अगर (!run_to_completion)
		spin_unlock_irqrestore(&पूर्णांकf->xmit_msgs_lock, flags);

	अगर (run_to_completion)
		smi_recv_tasklet(&पूर्णांकf->recv_tasklet);
	अन्यथा
		tasklet_schedule(&पूर्णांकf->recv_tasklet);
पूर्ण
EXPORT_SYMBOL(ipmi_smi_msg_received);

व्योम ipmi_smi_watchकरोg_preसमयout(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	अगर (पूर्णांकf->in_shutकरोwn)
		वापस;

	atomic_set(&पूर्णांकf->watchकरोg_preसमयouts_to_deliver, 1);
	tasklet_schedule(&पूर्णांकf->recv_tasklet);
पूर्ण
EXPORT_SYMBOL(ipmi_smi_watchकरोg_preसमयout);

अटल काष्ठा ipmi_smi_msg *
smi_from_recv_msg(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा ipmi_recv_msg *recv_msg,
		  अचिन्हित अक्षर seq, दीर्घ seqid)
अणु
	काष्ठा ipmi_smi_msg *smi_msg = ipmi_alloc_smi_msg();
	अगर (!smi_msg)
		/*
		 * If we can't allocate the message, then just वापस, we
		 * get 4 retries, so this should be ok.
		 */
		वापस शून्य;

	स_नकल(smi_msg->data, recv_msg->msg.data, recv_msg->msg.data_len);
	smi_msg->data_size = recv_msg->msg.data_len;
	smi_msg->msgid = STORE_SEQ_IN_MSGID(seq, seqid);

	pr_debug("Resend: %*ph\n", smi_msg->data_size, smi_msg->data);

	वापस smi_msg;
पूर्ण

अटल व्योम check_msg_समयout(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा seq_table *ent,
			      काष्ठा list_head *समयouts,
			      अचिन्हित दीर्घ समयout_period,
			      पूर्णांक slot, अचिन्हित दीर्घ *flags,
			      bool *need_समयr)
अणु
	काष्ठा ipmi_recv_msg *msg;

	अगर (पूर्णांकf->in_shutकरोwn)
		वापस;

	अगर (!ent->inuse)
		वापस;

	अगर (समयout_period < ent->समयout) अणु
		ent->समयout -= समयout_period;
		*need_समयr = true;
		वापस;
	पूर्ण

	अगर (ent->retries_left == 0) अणु
		/* The message has used all its retries. */
		ent->inuse = 0;
		smi_हटाओ_watch(पूर्णांकf, IPMI_WATCH_MASK_CHECK_MESSAGES);
		msg = ent->recv_msg;
		list_add_tail(&msg->link, समयouts);
		अगर (ent->broadcast)
			ipmi_inc_stat(पूर्णांकf, समयd_out_ipmb_broadcasts);
		अन्यथा अगर (is_lan_addr(&ent->recv_msg->addr))
			ipmi_inc_stat(पूर्णांकf, समयd_out_lan_commands);
		अन्यथा
			ipmi_inc_stat(पूर्णांकf, समयd_out_ipmb_commands);
	पूर्ण अन्यथा अणु
		काष्ठा ipmi_smi_msg *smi_msg;
		/* More retries, send again. */

		*need_समयr = true;

		/*
		 * Start with the max समयr, set to normal समयr after
		 * the message is sent.
		 */
		ent->समयout = MAX_MSG_TIMEOUT;
		ent->retries_left--;
		smi_msg = smi_from_recv_msg(पूर्णांकf, ent->recv_msg, slot,
					    ent->seqid);
		अगर (!smi_msg) अणु
			अगर (is_lan_addr(&ent->recv_msg->addr))
				ipmi_inc_stat(पूर्णांकf,
					      dropped_rexmit_lan_commands);
			अन्यथा
				ipmi_inc_stat(पूर्णांकf,
					      dropped_rexmit_ipmb_commands);
			वापस;
		पूर्ण

		spin_unlock_irqrestore(&पूर्णांकf->seq_lock, *flags);

		/*
		 * Send the new message.  We send with a zero
		 * priority.  It समयd out, I करोubt समय is that
		 * critical now, and high priority messages are really
		 * only क्रम messages to the local MC, which करोn't get
		 * resent.
		 */
		अगर (पूर्णांकf->handlers) अणु
			अगर (is_lan_addr(&ent->recv_msg->addr))
				ipmi_inc_stat(पूर्णांकf,
					      retransmitted_lan_commands);
			अन्यथा
				ipmi_inc_stat(पूर्णांकf,
					      retransmitted_ipmb_commands);

			smi_send(पूर्णांकf, पूर्णांकf->handlers, smi_msg, 0);
		पूर्ण अन्यथा
			ipmi_मुक्त_smi_msg(smi_msg);

		spin_lock_irqsave(&पूर्णांकf->seq_lock, *flags);
	पूर्ण
पूर्ण

अटल bool ipmi_समयout_handler(काष्ठा ipmi_smi *पूर्णांकf,
				 अचिन्हित दीर्घ समयout_period)
अणु
	काष्ठा list_head     समयouts;
	काष्ठा ipmi_recv_msg *msg, *msg2;
	अचिन्हित दीर्घ        flags;
	पूर्णांक                  i;
	bool                 need_समयr = false;

	अगर (!पूर्णांकf->bmc_रेजिस्टरed) अणु
		kref_get(&पूर्णांकf->refcount);
		अगर (!schedule_work(&पूर्णांकf->bmc_reg_work)) अणु
			kref_put(&पूर्णांकf->refcount, पूर्णांकf_मुक्त);
			need_समयr = true;
		पूर्ण
	पूर्ण

	/*
	 * Go through the seq table and find any messages that
	 * have समयd out, putting them in the समयouts
	 * list.
	 */
	INIT_LIST_HEAD(&समयouts);
	spin_lock_irqsave(&पूर्णांकf->seq_lock, flags);
	अगर (पूर्णांकf->ipmb_मुख्यtenance_mode_समयout) अणु
		अगर (पूर्णांकf->ipmb_मुख्यtenance_mode_समयout <= समयout_period)
			पूर्णांकf->ipmb_मुख्यtenance_mode_समयout = 0;
		अन्यथा
			पूर्णांकf->ipmb_मुख्यtenance_mode_समयout -= समयout_period;
	पूर्ण
	क्रम (i = 0; i < IPMI_IPMB_NUM_SEQ; i++)
		check_msg_समयout(पूर्णांकf, &पूर्णांकf->seq_table[i],
				  &समयouts, समयout_period, i,
				  &flags, &need_समयr);
	spin_unlock_irqrestore(&पूर्णांकf->seq_lock, flags);

	list_क्रम_each_entry_safe(msg, msg2, &समयouts, link)
		deliver_err_response(पूर्णांकf, msg, IPMI_TIMEOUT_COMPLETION_CODE);

	/*
	 * Maपूर्णांकenance mode handling.  Check the समयout
	 * optimistically beक्रमe we claim the lock.  It may
	 * mean a समयout माला_लो missed occasionally, but that
	 * only means the समयout माला_लो extended by one period
	 * in that हाल.  No big deal, and it aव्योमs the lock
	 * most of the समय.
	 */
	अगर (पूर्णांकf->स्वतः_मुख्यtenance_समयout > 0) अणु
		spin_lock_irqsave(&पूर्णांकf->मुख्यtenance_mode_lock, flags);
		अगर (पूर्णांकf->स्वतः_मुख्यtenance_समयout > 0) अणु
			पूर्णांकf->स्वतः_मुख्यtenance_समयout
				-= समयout_period;
			अगर (!पूर्णांकf->मुख्यtenance_mode
			    && (पूर्णांकf->स्वतः_मुख्यtenance_समयout <= 0)) अणु
				पूर्णांकf->मुख्यtenance_mode_enable = false;
				मुख्यtenance_mode_update(पूर्णांकf);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&पूर्णांकf->मुख्यtenance_mode_lock,
				       flags);
	पूर्ण

	tasklet_schedule(&पूर्णांकf->recv_tasklet);

	वापस need_समयr;
पूर्ण

अटल व्योम ipmi_request_event(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	/* No event requests when in मुख्यtenance mode. */
	अगर (पूर्णांकf->मुख्यtenance_mode_enable)
		वापस;

	अगर (!पूर्णांकf->in_shutकरोwn)
		पूर्णांकf->handlers->request_events(पूर्णांकf->send_info);
पूर्ण

अटल काष्ठा समयr_list ipmi_समयr;

अटल atomic_t stop_operation;

अटल व्योम ipmi_समयout(काष्ठा समयr_list *unused)
अणु
	काष्ठा ipmi_smi *पूर्णांकf;
	bool need_समयr = false;
	पूर्णांक index;

	अगर (atomic_पढ़ो(&stop_operation))
		वापस;

	index = srcu_पढ़ो_lock(&ipmi_पूर्णांकerfaces_srcu);
	list_क्रम_each_entry_rcu(पूर्णांकf, &ipmi_पूर्णांकerfaces, link) अणु
		अगर (atomic_पढ़ो(&पूर्णांकf->event_रुकोers)) अणु
			पूर्णांकf->ticks_to_req_ev--;
			अगर (पूर्णांकf->ticks_to_req_ev == 0) अणु
				ipmi_request_event(पूर्णांकf);
				पूर्णांकf->ticks_to_req_ev = IPMI_REQUEST_EV_TIME;
			पूर्ण
			need_समयr = true;
		पूर्ण

		need_समयr |= ipmi_समयout_handler(पूर्णांकf, IPMI_TIMEOUT_TIME);
	पूर्ण
	srcu_पढ़ो_unlock(&ipmi_पूर्णांकerfaces_srcu, index);

	अगर (need_समयr)
		mod_समयr(&ipmi_समयr, jअगरfies + IPMI_TIMEOUT_JIFFIES);
पूर्ण

अटल व्योम need_रुकोer(काष्ठा ipmi_smi *पूर्णांकf)
अणु
	/* Racy, but worst हाल we start the समयr twice. */
	अगर (!समयr_pending(&ipmi_समयr))
		mod_समयr(&ipmi_समयr, jअगरfies + IPMI_TIMEOUT_JIFFIES);
पूर्ण

अटल atomic_t smi_msg_inuse_count = ATOMIC_INIT(0);
अटल atomic_t recv_msg_inuse_count = ATOMIC_INIT(0);

अटल व्योम मुक्त_smi_msg(काष्ठा ipmi_smi_msg *msg)
अणु
	atomic_dec(&smi_msg_inuse_count);
	kमुक्त(msg);
पूर्ण

काष्ठा ipmi_smi_msg *ipmi_alloc_smi_msg(व्योम)
अणु
	काष्ठा ipmi_smi_msg *rv;
	rv = kदो_स्मृति(माप(काष्ठा ipmi_smi_msg), GFP_ATOMIC);
	अगर (rv) अणु
		rv->करोne = मुक्त_smi_msg;
		rv->user_data = शून्य;
		atomic_inc(&smi_msg_inuse_count);
	पूर्ण
	वापस rv;
पूर्ण
EXPORT_SYMBOL(ipmi_alloc_smi_msg);

अटल व्योम मुक्त_recv_msg(काष्ठा ipmi_recv_msg *msg)
अणु
	atomic_dec(&recv_msg_inuse_count);
	kमुक्त(msg);
पूर्ण

अटल काष्ठा ipmi_recv_msg *ipmi_alloc_recv_msg(व्योम)
अणु
	काष्ठा ipmi_recv_msg *rv;

	rv = kदो_स्मृति(माप(काष्ठा ipmi_recv_msg), GFP_ATOMIC);
	अगर (rv) अणु
		rv->user = शून्य;
		rv->करोne = मुक्त_recv_msg;
		atomic_inc(&recv_msg_inuse_count);
	पूर्ण
	वापस rv;
पूर्ण

व्योम ipmi_मुक्त_recv_msg(काष्ठा ipmi_recv_msg *msg)
अणु
	अगर (msg->user)
		kref_put(&msg->user->refcount, मुक्त_user);
	msg->करोne(msg);
पूर्ण
EXPORT_SYMBOL(ipmi_मुक्त_recv_msg);

अटल atomic_t panic_करोne_count = ATOMIC_INIT(0);

अटल व्योम dummy_smi_करोne_handler(काष्ठा ipmi_smi_msg *msg)
अणु
	atomic_dec(&panic_करोne_count);
पूर्ण

अटल व्योम dummy_recv_करोne_handler(काष्ठा ipmi_recv_msg *msg)
अणु
	atomic_dec(&panic_करोne_count);
पूर्ण

/*
 * Inside a panic, send a message and रुको क्रम a response.
 */
अटल व्योम ipmi_panic_request_and_रुको(काष्ठा ipmi_smi *पूर्णांकf,
					काष्ठा ipmi_addr *addr,
					काष्ठा kernel_ipmi_msg *msg)
अणु
	काष्ठा ipmi_smi_msg  smi_msg;
	काष्ठा ipmi_recv_msg recv_msg;
	पूर्णांक rv;

	smi_msg.करोne = dummy_smi_करोne_handler;
	recv_msg.करोne = dummy_recv_करोne_handler;
	atomic_add(2, &panic_करोne_count);
	rv = i_ipmi_request(शून्य,
			    पूर्णांकf,
			    addr,
			    0,
			    msg,
			    पूर्णांकf,
			    &smi_msg,
			    &recv_msg,
			    0,
			    पूर्णांकf->addrinfo[0].address,
			    पूर्णांकf->addrinfo[0].lun,
			    0, 1); /* Don't retry, and don't रुको. */
	अगर (rv)
		atomic_sub(2, &panic_करोne_count);
	अन्यथा अगर (पूर्णांकf->handlers->flush_messages)
		पूर्णांकf->handlers->flush_messages(पूर्णांकf->send_info);

	जबतक (atomic_पढ़ो(&panic_करोne_count) != 0)
		ipmi_poll(पूर्णांकf);
पूर्ण

अटल व्योम event_receiver_fetcher(काष्ठा ipmi_smi *पूर्णांकf,
				   काष्ठा ipmi_recv_msg *msg)
अणु
	अगर ((msg->addr.addr_type == IPMI_SYSTEM_INTERFACE_ADDR_TYPE)
	    && (msg->msg.netfn == IPMI_NETFN_SENSOR_EVENT_RESPONSE)
	    && (msg->msg.cmd == IPMI_GET_EVENT_RECEIVER_CMD)
	    && (msg->msg.data[0] == IPMI_CC_NO_ERROR)) अणु
		/* A get event receiver command, save it. */
		पूर्णांकf->event_receiver = msg->msg.data[1];
		पूर्णांकf->event_receiver_lun = msg->msg.data[2] & 0x3;
	पूर्ण
पूर्ण

अटल व्योम device_id_fetcher(काष्ठा ipmi_smi *पूर्णांकf, काष्ठा ipmi_recv_msg *msg)
अणु
	अगर ((msg->addr.addr_type == IPMI_SYSTEM_INTERFACE_ADDR_TYPE)
	    && (msg->msg.netfn == IPMI_NETFN_APP_RESPONSE)
	    && (msg->msg.cmd == IPMI_GET_DEVICE_ID_CMD)
	    && (msg->msg.data[0] == IPMI_CC_NO_ERROR)) अणु
		/*
		 * A get device id command, save अगर we are an event
		 * receiver or generator.
		 */
		पूर्णांकf->local_sel_device = (msg->msg.data[6] >> 2) & 1;
		पूर्णांकf->local_event_generator = (msg->msg.data[6] >> 5) & 1;
	पूर्ण
पूर्ण

अटल व्योम send_panic_events(काष्ठा ipmi_smi *पूर्णांकf, अक्षर *str)
अणु
	काष्ठा kernel_ipmi_msg msg;
	अचिन्हित अक्षर data[16];
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *si;
	काष्ठा ipmi_addr addr;
	अक्षर *p = str;
	काष्ठा ipmi_ipmb_addr *ipmb;
	पूर्णांक j;

	अगर (ipmi_send_panic_event == IPMI_SEND_PANIC_EVENT_NONE)
		वापस;

	si = (काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *) &addr;
	si->addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	si->channel = IPMI_BMC_CHANNEL;
	si->lun = 0;

	/* Fill in an event telling that we have failed. */
	msg.netfn = 0x04; /* Sensor or Event. */
	msg.cmd = 2; /* Platक्रमm event command. */
	msg.data = data;
	msg.data_len = 8;
	data[0] = 0x41; /* Kernel generator ID, IPMI table 5-4 */
	data[1] = 0x03; /* This is क्रम IPMI 1.0. */
	data[2] = 0x20; /* OS Critical Stop, IPMI table 36-3 */
	data[4] = 0x6f; /* Sensor specअगरic, IPMI table 36-1 */
	data[5] = 0xa1; /* Runसमय stop OEM bytes 2 & 3. */

	/*
	 * Put a few bपढ़ोcrumbs in.  Hopefully later we can add more things
	 * to make the panic events more useful.
	 */
	अगर (str) अणु
		data[3] = str[0];
		data[6] = str[1];
		data[7] = str[2];
	पूर्ण

	/* Send the event announcing the panic. */
	ipmi_panic_request_and_रुको(पूर्णांकf, &addr, &msg);

	/*
	 * On every पूर्णांकerface, dump a bunch of OEM event holding the
	 * string.
	 */
	अगर (ipmi_send_panic_event != IPMI_SEND_PANIC_EVENT_STRING || !str)
		वापस;

	/*
	 * पूर्णांकf_num is used as an marker to tell अगर the
	 * पूर्णांकerface is valid.  Thus we need a पढ़ो barrier to
	 * make sure data fetched beक्रमe checking पूर्णांकf_num
	 * won't be used.
	 */
	smp_rmb();

	/*
	 * First job here is to figure out where to send the
	 * OEM events.  There's no way in IPMI to send OEM
	 * events using an event send command, so we have to
	 * find the SEL to put them in and stick them in
	 * there.
	 */

	/* Get capabilities from the get device id. */
	पूर्णांकf->local_sel_device = 0;
	पूर्णांकf->local_event_generator = 0;
	पूर्णांकf->event_receiver = 0;

	/* Request the device info from the local MC. */
	msg.netfn = IPMI_NETFN_APP_REQUEST;
	msg.cmd = IPMI_GET_DEVICE_ID_CMD;
	msg.data = शून्य;
	msg.data_len = 0;
	पूर्णांकf->null_user_handler = device_id_fetcher;
	ipmi_panic_request_and_रुको(पूर्णांकf, &addr, &msg);

	अगर (पूर्णांकf->local_event_generator) अणु
		/* Request the event receiver from the local MC. */
		msg.netfn = IPMI_NETFN_SENSOR_EVENT_REQUEST;
		msg.cmd = IPMI_GET_EVENT_RECEIVER_CMD;
		msg.data = शून्य;
		msg.data_len = 0;
		पूर्णांकf->null_user_handler = event_receiver_fetcher;
		ipmi_panic_request_and_रुको(पूर्णांकf, &addr, &msg);
	पूर्ण
	पूर्णांकf->null_user_handler = शून्य;

	/*
	 * Validate the event receiver.  The low bit must not
	 * be 1 (it must be a valid IPMB address), it cannot
	 * be zero, and it must not be my address.
	 */
	अगर (((पूर्णांकf->event_receiver & 1) == 0)
	    && (पूर्णांकf->event_receiver != 0)
	    && (पूर्णांकf->event_receiver != पूर्णांकf->addrinfo[0].address)) अणु
		/*
		 * The event receiver is valid, send an IPMB
		 * message.
		 */
		ipmb = (काष्ठा ipmi_ipmb_addr *) &addr;
		ipmb->addr_type = IPMI_IPMB_ADDR_TYPE;
		ipmb->channel = 0; /* FIXME - is this right? */
		ipmb->lun = पूर्णांकf->event_receiver_lun;
		ipmb->slave_addr = पूर्णांकf->event_receiver;
	पूर्ण अन्यथा अगर (पूर्णांकf->local_sel_device) अणु
		/*
		 * The event receiver was not valid (or was
		 * me), but I am an SEL device, just dump it
		 * in my SEL.
		 */
		si = (काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr *) &addr;
		si->addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
		si->channel = IPMI_BMC_CHANNEL;
		si->lun = 0;
	पूर्ण अन्यथा
		वापस; /* No where to send the event. */

	msg.netfn = IPMI_NETFN_STORAGE_REQUEST; /* Storage. */
	msg.cmd = IPMI_ADD_SEL_ENTRY_CMD;
	msg.data = data;
	msg.data_len = 16;

	j = 0;
	जबतक (*p) अणु
		पूर्णांक size = म_माप(p);

		अगर (size > 11)
			size = 11;
		data[0] = 0;
		data[1] = 0;
		data[2] = 0xf0; /* OEM event without बारtamp. */
		data[3] = पूर्णांकf->addrinfo[0].address;
		data[4] = j++; /* sequence # */
		/*
		 * Always give 11 bytes, so म_नकलन will fill
		 * it with zeroes क्रम me.
		 */
		म_नकलन(data+5, p, 11);
		p += size;

		ipmi_panic_request_and_रुको(पूर्णांकf, &addr, &msg);
	पूर्ण
पूर्ण

अटल पूर्णांक has_panicked;

अटल पूर्णांक panic_event(काष्ठा notअगरier_block *this,
		       अचिन्हित दीर्घ         event,
		       व्योम                  *ptr)
अणु
	काष्ठा ipmi_smi *पूर्णांकf;
	काष्ठा ipmi_user *user;

	अगर (has_panicked)
		वापस NOTIFY_DONE;
	has_panicked = 1;

	/* For every रेजिस्टरed पूर्णांकerface, set it to run to completion. */
	list_क्रम_each_entry_rcu(पूर्णांकf, &ipmi_पूर्णांकerfaces, link) अणु
		अगर (!पूर्णांकf->handlers || पूर्णांकf->पूर्णांकf_num == -1)
			/* Interface is not पढ़ोy. */
			जारी;

		अगर (!पूर्णांकf->handlers->poll)
			जारी;

		/*
		 * If we were पूर्णांकerrupted जबतक locking xmit_msgs_lock or
		 * रुकोing_rcv_msgs_lock, the corresponding list may be
		 * corrupted.  In this हाल, drop items on the list क्रम
		 * the safety.
		 */
		अगर (!spin_trylock(&पूर्णांकf->xmit_msgs_lock)) अणु
			INIT_LIST_HEAD(&पूर्णांकf->xmit_msgs);
			INIT_LIST_HEAD(&पूर्णांकf->hp_xmit_msgs);
		पूर्ण अन्यथा
			spin_unlock(&पूर्णांकf->xmit_msgs_lock);

		अगर (!spin_trylock(&पूर्णांकf->रुकोing_rcv_msgs_lock))
			INIT_LIST_HEAD(&पूर्णांकf->रुकोing_rcv_msgs);
		अन्यथा
			spin_unlock(&पूर्णांकf->रुकोing_rcv_msgs_lock);

		पूर्णांकf->run_to_completion = 1;
		अगर (पूर्णांकf->handlers->set_run_to_completion)
			पूर्णांकf->handlers->set_run_to_completion(पूर्णांकf->send_info,
							      1);

		list_क्रम_each_entry_rcu(user, &पूर्णांकf->users, link) अणु
			अगर (user->handler->ipmi_panic_handler)
				user->handler->ipmi_panic_handler(
					user->handler_data);
		पूर्ण

		send_panic_events(पूर्णांकf, ptr);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/* Must be called with ipmi_पूर्णांकerfaces_mutex held. */
अटल पूर्णांक ipmi_रेजिस्टर_driver(व्योम)
अणु
	पूर्णांक rv;

	अगर (drvरेजिस्टरed)
		वापस 0;

	rv = driver_रेजिस्टर(&ipmidriver.driver);
	अगर (rv)
		pr_err("Could not register IPMI driver\n");
	अन्यथा
		drvरेजिस्टरed = true;
	वापस rv;
पूर्ण

अटल काष्ठा notअगरier_block panic_block = अणु
	.notअगरier_call	= panic_event,
	.next		= शून्य,
	.priority	= 200	/* priority: पूर्णांक_उच्च >= x >= 0 */
पूर्ण;

अटल पूर्णांक ipmi_init_msghandler(व्योम)
अणु
	पूर्णांक rv;

	mutex_lock(&ipmi_पूर्णांकerfaces_mutex);
	rv = ipmi_रेजिस्टर_driver();
	अगर (rv)
		जाओ out;
	अगर (initialized)
		जाओ out;

	init_srcu_काष्ठा(&ipmi_पूर्णांकerfaces_srcu);

	समयr_setup(&ipmi_समयr, ipmi_समयout, 0);
	mod_समयr(&ipmi_समयr, jअगरfies + IPMI_TIMEOUT_JIFFIES);

	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &panic_block);

	initialized = true;

out:
	mutex_unlock(&ipmi_पूर्णांकerfaces_mutex);
	वापस rv;
पूर्ण

अटल पूर्णांक __init ipmi_init_msghandler_mod(व्योम)
अणु
	पूर्णांक rv;

	pr_info("version " IPMI_DRIVER_VERSION "\n");

	mutex_lock(&ipmi_पूर्णांकerfaces_mutex);
	rv = ipmi_रेजिस्टर_driver();
	mutex_unlock(&ipmi_पूर्णांकerfaces_mutex);

	वापस rv;
पूर्ण

अटल व्योम __निकास cleanup_ipmi(व्योम)
अणु
	पूर्णांक count;

	अगर (initialized) अणु
		atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
						 &panic_block);

		/*
		 * This can't be called अगर any पूर्णांकerfaces exist, so no worry
		 * about shutting करोwn the पूर्णांकerfaces.
		 */

		/*
		 * Tell the समयr to stop, then रुको क्रम it to stop.  This
		 * aव्योमs problems with race conditions removing the समयr
		 * here.
		 */
		atomic_set(&stop_operation, 1);
		del_समयr_sync(&ipmi_समयr);

		initialized = false;

		/* Check क्रम buffer leaks. */
		count = atomic_पढ़ो(&smi_msg_inuse_count);
		अगर (count != 0)
			pr_warn("SMI message count %d at exit\n", count);
		count = atomic_पढ़ो(&recv_msg_inuse_count);
		अगर (count != 0)
			pr_warn("recv message count %d at exit\n", count);

		cleanup_srcu_काष्ठा(&ipmi_पूर्णांकerfaces_srcu);
	पूर्ण
	अगर (drvरेजिस्टरed)
		driver_unरेजिस्टर(&ipmidriver.driver);
पूर्ण
module_निकास(cleanup_ipmi);

module_init(ipmi_init_msghandler_mod);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Corey Minyard <minyard@mvista.com>");
MODULE_DESCRIPTION("Incoming and outgoing message routing for an IPMI interface.");
MODULE_VERSION(IPMI_DRIVER_VERSION);
MODULE_SOFTDEP("post: ipmi_devintf");
