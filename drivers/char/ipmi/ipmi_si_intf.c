<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_si.c
 *
 * The पूर्णांकerface to the IPMI driver क्रम the प्रणाली पूर्णांकerfaces (KCS, SMIC,
 * BT).
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 * Copyright 2006 IBM Corp., Christian Krafft <krafft@de.ibm.com>
 */

/*
 * This file holds the "policy" क्रम the पूर्णांकerface to the SMI state
 * machine.  It करोes the configuration, handles समयrs and पूर्णांकerrupts,
 * and drives the real SMI state machine.
 */

#घोषणा pr_fmt(fmt) "ipmi_si: " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/ipmi.h>
#समावेश <linux/ipmi_smi.h>
#समावेश "ipmi_si.h"
#समावेश "ipmi_si_sm.h"
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>

/* Measure बार between events in the driver. */
#अघोषित DEBUG_TIMING

/* Call every 10 ms. */
#घोषणा SI_TIMEOUT_TIME_USEC	10000
#घोषणा SI_USEC_PER_JIFFY	(1000000/HZ)
#घोषणा SI_TIMEOUT_JIFFIES	(SI_TIMEOUT_TIME_USEC/SI_USEC_PER_JIFFY)
#घोषणा SI_SHORT_TIMEOUT_USEC  250 /* .25ms when the SM request a
				      लघु समयout */

क्रमागत si_पूर्णांकf_state अणु
	SI_NORMAL,
	SI_GETTING_FLAGS,
	SI_GETTING_EVENTS,
	SI_CLEARING_FLAGS,
	SI_GETTING_MESSAGES,
	SI_CHECKING_ENABLES,
	SI_SETTING_ENABLES
	/* FIXME - add watchकरोg stuff. */
पूर्ण;

/* Some BT-specअगरic defines we need here. */
#घोषणा IPMI_BT_INTMASK_REG		2
#घोषणा IPMI_BT_INTMASK_CLEAR_IRQ_BIT	2
#घोषणा IPMI_BT_INTMASK_ENABLE_IRQ_BIT	1

/* 'invalid' to allow a firmware-specअगरied पूर्णांकerface to be disabled */
स्थिर अक्षर *स्थिर si_to_str[] = अणु "invalid", "kcs", "smic", "bt", शून्य पूर्ण;

अटल bool initialized;

/*
 * Indexes पूर्णांकo stats[] in smi_info below.
 */
क्रमागत si_stat_indexes अणु
	/*
	 * Number of बार the driver requested a समयr जबतक an operation
	 * was in progress.
	 */
	SI_STAT_लघु_समयouts = 0,

	/*
	 * Number of बार the driver requested a समयr जबतक nothing was in
	 * progress.
	 */
	SI_STAT_दीर्घ_समयouts,

	/* Number of बार the पूर्णांकerface was idle जबतक being polled. */
	SI_STAT_idles,

	/* Number of पूर्णांकerrupts the driver handled. */
	SI_STAT_पूर्णांकerrupts,

	/* Number of समय the driver got an ATTN from the hardware. */
	SI_STAT_attentions,

	/* Number of बार the driver requested flags from the hardware. */
	SI_STAT_flag_fetches,

	/* Number of बार the hardware didn't follow the state machine. */
	SI_STAT_hosed_count,

	/* Number of completed messages. */
	SI_STAT_complete_transactions,

	/* Number of IPMI events received from the hardware. */
	SI_STAT_events,

	/* Number of watchकरोg preसमयouts. */
	SI_STAT_watchकरोg_preसमयouts,

	/* Number of asynchronous messages received. */
	SI_STAT_incoming_messages,


	/* This *must* reमुख्य last, add new values above this. */
	SI_NUM_STATS
पूर्ण;

काष्ठा smi_info अणु
	पूर्णांक                    si_num;
	काष्ठा ipmi_smi        *पूर्णांकf;
	काष्ठा si_sm_data      *si_sm;
	स्थिर काष्ठा si_sm_handlers *handlers;
	spinlock_t             si_lock;
	काष्ठा ipmi_smi_msg    *रुकोing_msg;
	काष्ठा ipmi_smi_msg    *curr_msg;
	क्रमागत si_पूर्णांकf_state     si_state;

	/*
	 * Used to handle the various types of I/O that can occur with
	 * IPMI
	 */
	काष्ठा si_sm_io io;

	/*
	 * Per-OEM handler, called from handle_flags().  Returns 1
	 * when handle_flags() needs to be re-run or 0 indicating it
	 * set si_state itself.
	 */
	पूर्णांक (*oem_data_avail_handler)(काष्ठा smi_info *smi_info);

	/*
	 * Flags from the last GET_MSG_FLAGS command, used when an ATTN
	 * is set to hold the flags until we are करोne handling everything
	 * from the flags.
	 */
#घोषणा RECEIVE_MSG_AVAIL	0x01
#घोषणा EVENT_MSG_BUFFER_FULL	0x02
#घोषणा WDT_PRE_TIMEOUT_INT	0x08
#घोषणा OEM0_DATA_AVAIL     0x20
#घोषणा OEM1_DATA_AVAIL     0x40
#घोषणा OEM2_DATA_AVAIL     0x80
#घोषणा OEM_DATA_AVAIL      (OEM0_DATA_AVAIL | \
			     OEM1_DATA_AVAIL | \
			     OEM2_DATA_AVAIL)
	अचिन्हित अक्षर       msg_flags;

	/* Does the BMC have an event buffer? */
	bool		    has_event_buffer;

	/*
	 * If set to true, this will request events the next समय the
	 * state machine is idle.
	 */
	atomic_t            req_events;

	/*
	 * If true, run the state machine to completion on every send
	 * call.  Generally used after a panic to make sure stuff goes
	 * out.
	 */
	bool                run_to_completion;

	/* The समयr क्रम this si. */
	काष्ठा समयr_list   si_समयr;

	/* This flag is set, अगर the समयr can be set */
	bool		    समयr_can_start;

	/* This flag is set, अगर the समयr is running (समयr_pending() isn't enough) */
	bool		    समयr_running;

	/* The समय (in jअगरfies) the last समयout occurred at. */
	अचिन्हित दीर्घ       last_समयout_jअगरfies;

	/* Are we रुकोing क्रम the events, preसमयouts, received msgs? */
	atomic_t            need_watch;

	/*
	 * The driver will disable पूर्णांकerrupts when it माला_लो पूर्णांकo a
	 * situation where it cannot handle messages due to lack of
	 * memory.  Once that situation clears up, it will re-enable
	 * पूर्णांकerrupts.
	 */
	bool पूर्णांकerrupt_disabled;

	/*
	 * Does the BMC support events?
	 */
	bool supports_event_msg_buff;

	/*
	 * Can we disable पूर्णांकerrupts the global enables receive irq
	 * bit?  There are currently two क्रमms of brokenness, some
	 * प्रणालीs cannot disable the bit (which is technically within
	 * the spec but a bad idea) and some प्रणालीs have the bit
	 * क्रमced to zero even though पूर्णांकerrupts work (which is
	 * clearly outside the spec).  The next bool tells which क्रमm
	 * of brokenness is present.
	 */
	bool cannot_disable_irq;

	/*
	 * Some प्रणालीs are broken and cannot set the irq enable
	 * bit, even अगर they support पूर्णांकerrupts.
	 */
	bool irq_enable_broken;

	/* Is the driver in मुख्यtenance mode? */
	bool in_मुख्यtenance_mode;

	/*
	 * Did we get an attention that we did not handle?
	 */
	bool got_attn;

	/* From the get device id response... */
	काष्ठा ipmi_device_id device_id;

	/* Have we added the device group to the device? */
	bool dev_group_added;

	/* Counters and things क्रम the proc fileप्रणाली. */
	atomic_t stats[SI_NUM_STATS];

	काष्ठा task_काष्ठा *thपढ़ो;

	काष्ठा list_head link;
पूर्ण;

#घोषणा smi_inc_stat(smi, stat) \
	atomic_inc(&(smi)->stats[SI_STAT_ ## stat])
#घोषणा smi_get_stat(smi, stat) \
	((अचिन्हित पूर्णांक) atomic_पढ़ो(&(smi)->stats[SI_STAT_ ## stat]))

#घोषणा IPMI_MAX_INTFS 4
अटल पूर्णांक क्रमce_kipmid[IPMI_MAX_INTFS];
अटल पूर्णांक num_क्रमce_kipmid;

अटल अचिन्हित पूर्णांक kipmid_max_busy_us[IPMI_MAX_INTFS];
अटल पूर्णांक num_max_busy_us;

अटल bool unload_when_empty = true;

अटल पूर्णांक try_smi_init(काष्ठा smi_info *smi);
अटल व्योम cleanup_one_si(काष्ठा smi_info *smi_info);
अटल व्योम cleanup_ipmi_si(व्योम);

#अगर_घोषित DEBUG_TIMING
व्योम debug_बारtamp(अक्षर *msg)
अणु
	काष्ठा बारpec64 t;

	kसमय_get_ts64(&t);
	pr_debug("**%s: %lld.%9.9ld\n", msg, t.tv_sec, t.tv_nsec);
पूर्ण
#अन्यथा
#घोषणा debug_बारtamp(x)
#पूर्ण_अगर

अटल ATOMIC_NOTIFIER_HEAD(xaction_notअगरier_list);
अटल पूर्णांक रेजिस्टर_xaction_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&xaction_notअगरier_list, nb);
पूर्ण

अटल व्योम deliver_recv_msg(काष्ठा smi_info *smi_info,
			     काष्ठा ipmi_smi_msg *msg)
अणु
	/* Deliver the message to the upper layer. */
	ipmi_smi_msg_received(smi_info->पूर्णांकf, msg);
पूर्ण

अटल व्योम वापस_hosed_msg(काष्ठा smi_info *smi_info, पूर्णांक cCode)
अणु
	काष्ठा ipmi_smi_msg *msg = smi_info->curr_msg;

	अगर (cCode < 0 || cCode > IPMI_ERR_UNSPECIFIED)
		cCode = IPMI_ERR_UNSPECIFIED;
	/* अन्यथा use it as is */

	/* Make it a response */
	msg->rsp[0] = msg->data[0] | 4;
	msg->rsp[1] = msg->data[1];
	msg->rsp[2] = cCode;
	msg->rsp_size = 3;

	smi_info->curr_msg = शून्य;
	deliver_recv_msg(smi_info, msg);
पूर्ण

अटल क्रमागत si_sm_result start_next_msg(काष्ठा smi_info *smi_info)
अणु
	पूर्णांक              rv;

	अगर (!smi_info->रुकोing_msg) अणु
		smi_info->curr_msg = शून्य;
		rv = SI_SM_IDLE;
	पूर्ण अन्यथा अणु
		पूर्णांक err;

		smi_info->curr_msg = smi_info->रुकोing_msg;
		smi_info->रुकोing_msg = शून्य;
		debug_बारtamp("Start2");
		err = atomic_notअगरier_call_chain(&xaction_notअगरier_list,
				0, smi_info);
		अगर (err & NOTIFY_STOP_MASK) अणु
			rv = SI_SM_CALL_WITHOUT_DELAY;
			जाओ out;
		पूर्ण
		err = smi_info->handlers->start_transaction(
			smi_info->si_sm,
			smi_info->curr_msg->data,
			smi_info->curr_msg->data_size);
		अगर (err)
			वापस_hosed_msg(smi_info, err);

		rv = SI_SM_CALL_WITHOUT_DELAY;
	पूर्ण
out:
	वापस rv;
पूर्ण

अटल व्योम smi_mod_समयr(काष्ठा smi_info *smi_info, अचिन्हित दीर्घ new_val)
अणु
	अगर (!smi_info->समयr_can_start)
		वापस;
	smi_info->last_समयout_jअगरfies = jअगरfies;
	mod_समयr(&smi_info->si_समयr, new_val);
	smi_info->समयr_running = true;
पूर्ण

/*
 * Start a new message and (re)start the समयr and thपढ़ो.
 */
अटल व्योम start_new_msg(काष्ठा smi_info *smi_info, अचिन्हित अक्षर *msg,
			  अचिन्हित पूर्णांक size)
अणु
	smi_mod_समयr(smi_info, jअगरfies + SI_TIMEOUT_JIFFIES);

	अगर (smi_info->thपढ़ो)
		wake_up_process(smi_info->thपढ़ो);

	smi_info->handlers->start_transaction(smi_info->si_sm, msg, size);
पूर्ण

अटल व्योम start_check_enables(काष्ठा smi_info *smi_info)
अणु
	अचिन्हित अक्षर msg[2];

	msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg[1] = IPMI_GET_BMC_GLOBAL_ENABLES_CMD;

	start_new_msg(smi_info, msg, 2);
	smi_info->si_state = SI_CHECKING_ENABLES;
पूर्ण

अटल व्योम start_clear_flags(काष्ठा smi_info *smi_info)
अणु
	अचिन्हित अक्षर msg[3];

	/* Make sure the watchकरोg pre-समयout flag is not set at startup. */
	msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg[1] = IPMI_CLEAR_MSG_FLAGS_CMD;
	msg[2] = WDT_PRE_TIMEOUT_INT;

	start_new_msg(smi_info, msg, 3);
	smi_info->si_state = SI_CLEARING_FLAGS;
पूर्ण

अटल व्योम start_getting_msg_queue(काष्ठा smi_info *smi_info)
अणु
	smi_info->curr_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	smi_info->curr_msg->data[1] = IPMI_GET_MSG_CMD;
	smi_info->curr_msg->data_size = 2;

	start_new_msg(smi_info, smi_info->curr_msg->data,
		      smi_info->curr_msg->data_size);
	smi_info->si_state = SI_GETTING_MESSAGES;
पूर्ण

अटल व्योम start_getting_events(काष्ठा smi_info *smi_info)
अणु
	smi_info->curr_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	smi_info->curr_msg->data[1] = IPMI_READ_EVENT_MSG_BUFFER_CMD;
	smi_info->curr_msg->data_size = 2;

	start_new_msg(smi_info, smi_info->curr_msg->data,
		      smi_info->curr_msg->data_size);
	smi_info->si_state = SI_GETTING_EVENTS;
पूर्ण

/*
 * When we have a situtaion where we run out of memory and cannot
 * allocate messages, we just leave them in the BMC and run the प्रणाली
 * polled until we can allocate some memory.  Once we have some
 * memory, we will re-enable the पूर्णांकerrupt.
 *
 * Note that we cannot just use disable_irq(), since the पूर्णांकerrupt may
 * be shared.
 */
अटल अंतरभूत bool disable_si_irq(काष्ठा smi_info *smi_info)
अणु
	अगर ((smi_info->io.irq) && (!smi_info->पूर्णांकerrupt_disabled)) अणु
		smi_info->पूर्णांकerrupt_disabled = true;
		start_check_enables(smi_info);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool enable_si_irq(काष्ठा smi_info *smi_info)
अणु
	अगर ((smi_info->io.irq) && (smi_info->पूर्णांकerrupt_disabled)) अणु
		smi_info->पूर्णांकerrupt_disabled = false;
		start_check_enables(smi_info);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Allocate a message.  If unable to allocate, start the पूर्णांकerrupt
 * disable process and वापस शून्य.  If able to allocate but
 * पूर्णांकerrupts are disabled, मुक्त the message and वापस शून्य after
 * starting the पूर्णांकerrupt enable process.
 */
अटल काष्ठा ipmi_smi_msg *alloc_msg_handle_irq(काष्ठा smi_info *smi_info)
अणु
	काष्ठा ipmi_smi_msg *msg;

	msg = ipmi_alloc_smi_msg();
	अगर (!msg) अणु
		अगर (!disable_si_irq(smi_info))
			smi_info->si_state = SI_NORMAL;
	पूर्ण अन्यथा अगर (enable_si_irq(smi_info)) अणु
		ipmi_मुक्त_smi_msg(msg);
		msg = शून्य;
	पूर्ण
	वापस msg;
पूर्ण

अटल व्योम handle_flags(काष्ठा smi_info *smi_info)
अणु
retry:
	अगर (smi_info->msg_flags & WDT_PRE_TIMEOUT_INT) अणु
		/* Watchकरोg pre-समयout */
		smi_inc_stat(smi_info, watchकरोg_preसमयouts);

		start_clear_flags(smi_info);
		smi_info->msg_flags &= ~WDT_PRE_TIMEOUT_INT;
		ipmi_smi_watchकरोg_preसमयout(smi_info->पूर्णांकf);
	पूर्ण अन्यथा अगर (smi_info->msg_flags & RECEIVE_MSG_AVAIL) अणु
		/* Messages available. */
		smi_info->curr_msg = alloc_msg_handle_irq(smi_info);
		अगर (!smi_info->curr_msg)
			वापस;

		start_getting_msg_queue(smi_info);
	पूर्ण अन्यथा अगर (smi_info->msg_flags & EVENT_MSG_BUFFER_FULL) अणु
		/* Events available. */
		smi_info->curr_msg = alloc_msg_handle_irq(smi_info);
		अगर (!smi_info->curr_msg)
			वापस;

		start_getting_events(smi_info);
	पूर्ण अन्यथा अगर (smi_info->msg_flags & OEM_DATA_AVAIL &&
		   smi_info->oem_data_avail_handler) अणु
		अगर (smi_info->oem_data_avail_handler(smi_info))
			जाओ retry;
	पूर्ण अन्यथा
		smi_info->si_state = SI_NORMAL;
पूर्ण

/*
 * Global enables we care about.
 */
#घोषणा GLOBAL_ENABLES_MASK (IPMI_BMC_EVT_MSG_BUFF | IPMI_BMC_RCV_MSG_INTR | \
			     IPMI_BMC_EVT_MSG_INTR)

अटल u8 current_global_enables(काष्ठा smi_info *smi_info, u8 base,
				 bool *irq_on)
अणु
	u8 enables = 0;

	अगर (smi_info->supports_event_msg_buff)
		enables |= IPMI_BMC_EVT_MSG_BUFF;

	अगर (((smi_info->io.irq && !smi_info->पूर्णांकerrupt_disabled) ||
	     smi_info->cannot_disable_irq) &&
	    !smi_info->irq_enable_broken)
		enables |= IPMI_BMC_RCV_MSG_INTR;

	अगर (smi_info->supports_event_msg_buff &&
	    smi_info->io.irq && !smi_info->पूर्णांकerrupt_disabled &&
	    !smi_info->irq_enable_broken)
		enables |= IPMI_BMC_EVT_MSG_INTR;

	*irq_on = enables & (IPMI_BMC_EVT_MSG_INTR | IPMI_BMC_RCV_MSG_INTR);

	वापस enables;
पूर्ण

अटल व्योम check_bt_irq(काष्ठा smi_info *smi_info, bool irq_on)
अणु
	u8 irqstate = smi_info->io.inputb(&smi_info->io, IPMI_BT_INTMASK_REG);

	irqstate &= IPMI_BT_INTMASK_ENABLE_IRQ_BIT;

	अगर ((bool)irqstate == irq_on)
		वापस;

	अगर (irq_on)
		smi_info->io.outputb(&smi_info->io, IPMI_BT_INTMASK_REG,
				     IPMI_BT_INTMASK_ENABLE_IRQ_BIT);
	अन्यथा
		smi_info->io.outputb(&smi_info->io, IPMI_BT_INTMASK_REG, 0);
पूर्ण

अटल व्योम handle_transaction_करोne(काष्ठा smi_info *smi_info)
अणु
	काष्ठा ipmi_smi_msg *msg;

	debug_बारtamp("Done");
	चयन (smi_info->si_state) अणु
	हाल SI_NORMAL:
		अगर (!smi_info->curr_msg)
			अवरोध;

		smi_info->curr_msg->rsp_size
			= smi_info->handlers->get_result(
				smi_info->si_sm,
				smi_info->curr_msg->rsp,
				IPMI_MAX_MSG_LENGTH);

		/*
		 * Do this here beहाल deliver_recv_msg() releases the
		 * lock, and a new message can be put in during the
		 * समय the lock is released.
		 */
		msg = smi_info->curr_msg;
		smi_info->curr_msg = शून्य;
		deliver_recv_msg(smi_info, msg);
		अवरोध;

	हाल SI_GETTING_FLAGS:
	अणु
		अचिन्हित अक्षर msg[4];
		अचिन्हित पूर्णांक  len;

		/* We got the flags from the SMI, now handle them. */
		len = smi_info->handlers->get_result(smi_info->si_sm, msg, 4);
		अगर (msg[2] != 0) अणु
			/* Error fetching flags, just give up क्रम now. */
			smi_info->si_state = SI_NORMAL;
		पूर्ण अन्यथा अगर (len < 4) अणु
			/*
			 * Hmm, no flags.  That's technically illegal, but
			 * करोn't use uninitialized data.
			 */
			smi_info->si_state = SI_NORMAL;
		पूर्ण अन्यथा अणु
			smi_info->msg_flags = msg[3];
			handle_flags(smi_info);
		पूर्ण
		अवरोध;
	पूर्ण

	हाल SI_CLEARING_FLAGS:
	अणु
		अचिन्हित अक्षर msg[3];

		/* We cleared the flags. */
		smi_info->handlers->get_result(smi_info->si_sm, msg, 3);
		अगर (msg[2] != 0) अणु
			/* Error clearing flags */
			dev_warn(smi_info->io.dev,
				 "Error clearing flags: %2.2x\n", msg[2]);
		पूर्ण
		smi_info->si_state = SI_NORMAL;
		अवरोध;
	पूर्ण

	हाल SI_GETTING_EVENTS:
	अणु
		smi_info->curr_msg->rsp_size
			= smi_info->handlers->get_result(
				smi_info->si_sm,
				smi_info->curr_msg->rsp,
				IPMI_MAX_MSG_LENGTH);

		/*
		 * Do this here beहाल deliver_recv_msg() releases the
		 * lock, and a new message can be put in during the
		 * समय the lock is released.
		 */
		msg = smi_info->curr_msg;
		smi_info->curr_msg = शून्य;
		अगर (msg->rsp[2] != 0) अणु
			/* Error getting event, probably करोne. */
			msg->करोne(msg);

			/* Take off the event flag. */
			smi_info->msg_flags &= ~EVENT_MSG_BUFFER_FULL;
			handle_flags(smi_info);
		पूर्ण अन्यथा अणु
			smi_inc_stat(smi_info, events);

			/*
			 * Do this beक्रमe we deliver the message
			 * because delivering the message releases the
			 * lock and something अन्यथा can mess with the
			 * state.
			 */
			handle_flags(smi_info);

			deliver_recv_msg(smi_info, msg);
		पूर्ण
		अवरोध;
	पूर्ण

	हाल SI_GETTING_MESSAGES:
	अणु
		smi_info->curr_msg->rsp_size
			= smi_info->handlers->get_result(
				smi_info->si_sm,
				smi_info->curr_msg->rsp,
				IPMI_MAX_MSG_LENGTH);

		/*
		 * Do this here beहाल deliver_recv_msg() releases the
		 * lock, and a new message can be put in during the
		 * समय the lock is released.
		 */
		msg = smi_info->curr_msg;
		smi_info->curr_msg = शून्य;
		अगर (msg->rsp[2] != 0) अणु
			/* Error getting event, probably करोne. */
			msg->करोne(msg);

			/* Take off the msg flag. */
			smi_info->msg_flags &= ~RECEIVE_MSG_AVAIL;
			handle_flags(smi_info);
		पूर्ण अन्यथा अणु
			smi_inc_stat(smi_info, incoming_messages);

			/*
			 * Do this beक्रमe we deliver the message
			 * because delivering the message releases the
			 * lock and something अन्यथा can mess with the
			 * state.
			 */
			handle_flags(smi_info);

			deliver_recv_msg(smi_info, msg);
		पूर्ण
		अवरोध;
	पूर्ण

	हाल SI_CHECKING_ENABLES:
	अणु
		अचिन्हित अक्षर msg[4];
		u8 enables;
		bool irq_on;

		/* We got the flags from the SMI, now handle them. */
		smi_info->handlers->get_result(smi_info->si_sm, msg, 4);
		अगर (msg[2] != 0) अणु
			dev_warn(smi_info->io.dev,
				 "Couldn't get irq info: %x.\n", msg[2]);
			dev_warn(smi_info->io.dev,
				 "Maybe ok, but ipmi might run very slowly.\n");
			smi_info->si_state = SI_NORMAL;
			अवरोध;
		पूर्ण
		enables = current_global_enables(smi_info, 0, &irq_on);
		अगर (smi_info->io.si_type == SI_BT)
			/* BT has its own पूर्णांकerrupt enable bit. */
			check_bt_irq(smi_info, irq_on);
		अगर (enables != (msg[3] & GLOBAL_ENABLES_MASK)) अणु
			/* Enables are not correct, fix them. */
			msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
			msg[1] = IPMI_SET_BMC_GLOBAL_ENABLES_CMD;
			msg[2] = enables | (msg[3] & ~GLOBAL_ENABLES_MASK);
			smi_info->handlers->start_transaction(
				smi_info->si_sm, msg, 3);
			smi_info->si_state = SI_SETTING_ENABLES;
		पूर्ण अन्यथा अगर (smi_info->supports_event_msg_buff) अणु
			smi_info->curr_msg = ipmi_alloc_smi_msg();
			अगर (!smi_info->curr_msg) अणु
				smi_info->si_state = SI_NORMAL;
				अवरोध;
			पूर्ण
			start_getting_events(smi_info);
		पूर्ण अन्यथा अणु
			smi_info->si_state = SI_NORMAL;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल SI_SETTING_ENABLES:
	अणु
		अचिन्हित अक्षर msg[4];

		smi_info->handlers->get_result(smi_info->si_sm, msg, 4);
		अगर (msg[2] != 0)
			dev_warn(smi_info->io.dev,
				 "Could not set the global enables: 0x%x.\n",
				 msg[2]);

		अगर (smi_info->supports_event_msg_buff) अणु
			smi_info->curr_msg = ipmi_alloc_smi_msg();
			अगर (!smi_info->curr_msg) अणु
				smi_info->si_state = SI_NORMAL;
				अवरोध;
			पूर्ण
			start_getting_events(smi_info);
		पूर्ण अन्यथा अणु
			smi_info->si_state = SI_NORMAL;
		पूर्ण
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

/*
 * Called on समयouts and events.  Timeouts should pass the elapsed
 * समय, पूर्णांकerrupts should pass in zero.  Must be called with
 * si_lock held and पूर्णांकerrupts disabled.
 */
अटल क्रमागत si_sm_result smi_event_handler(काष्ठा smi_info *smi_info,
					   पूर्णांक समय)
अणु
	क्रमागत si_sm_result si_sm_result;

restart:
	/*
	 * There used to be a loop here that रुकोed a little जबतक
	 * (around 25us) beक्रमe giving up.  That turned out to be
	 * poपूर्णांकless, the minimum delays I was seeing were in the 300us
	 * range, which is far too दीर्घ to रुको in an पूर्णांकerrupt.  So
	 * we just run until the state machine tells us something
	 * happened or it needs a delay.
	 */
	si_sm_result = smi_info->handlers->event(smi_info->si_sm, समय);
	समय = 0;
	जबतक (si_sm_result == SI_SM_CALL_WITHOUT_DELAY)
		si_sm_result = smi_info->handlers->event(smi_info->si_sm, 0);

	अगर (si_sm_result == SI_SM_TRANSACTION_COMPLETE) अणु
		smi_inc_stat(smi_info, complete_transactions);

		handle_transaction_करोne(smi_info);
		जाओ restart;
	पूर्ण अन्यथा अगर (si_sm_result == SI_SM_HOSED) अणु
		smi_inc_stat(smi_info, hosed_count);

		/*
		 * Do the beक्रमe वापस_hosed_msg, because that
		 * releases the lock.
		 */
		smi_info->si_state = SI_NORMAL;
		अगर (smi_info->curr_msg != शून्य) अणु
			/*
			 * If we were handling a user message, क्रमmat
			 * a response to send to the upper layer to
			 * tell it about the error.
			 */
			वापस_hosed_msg(smi_info, IPMI_ERR_UNSPECIFIED);
		पूर्ण
		जाओ restart;
	पूर्ण

	/*
	 * We prefer handling attn over new messages.  But करोn't करो
	 * this अगर there is not yet an upper layer to handle anything.
	 */
	अगर (si_sm_result == SI_SM_ATTN || smi_info->got_attn) अणु
		अचिन्हित अक्षर msg[2];

		अगर (smi_info->si_state != SI_NORMAL) अणु
			/*
			 * We got an ATTN, but we are करोing something अन्यथा.
			 * Handle the ATTN later.
			 */
			smi_info->got_attn = true;
		पूर्ण अन्यथा अणु
			smi_info->got_attn = false;
			smi_inc_stat(smi_info, attentions);

			/*
			 * Got a attn, send करोwn a get message flags to see
			 * what's causing it.  It would be better to handle
			 * this in the upper layer, but due to the way
			 * पूर्णांकerrupts work with the SMI, that's not really
			 * possible.
			 */
			msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
			msg[1] = IPMI_GET_MSG_FLAGS_CMD;

			start_new_msg(smi_info, msg, 2);
			smi_info->si_state = SI_GETTING_FLAGS;
			जाओ restart;
		पूर्ण
	पूर्ण

	/* If we are currently idle, try to start the next message. */
	अगर (si_sm_result == SI_SM_IDLE) अणु
		smi_inc_stat(smi_info, idles);

		si_sm_result = start_next_msg(smi_info);
		अगर (si_sm_result != SI_SM_IDLE)
			जाओ restart;
	पूर्ण

	अगर ((si_sm_result == SI_SM_IDLE)
	    && (atomic_पढ़ो(&smi_info->req_events))) अणु
		/*
		 * We are idle and the upper layer requested that I fetch
		 * events, so करो so.
		 */
		atomic_set(&smi_info->req_events, 0);

		/*
		 * Take this opportunity to check the पूर्णांकerrupt and
		 * message enable state क्रम the BMC.  The BMC can be
		 * asynchronously reset, and may thus get पूर्णांकerrupts
		 * disable and messages disabled.
		 */
		अगर (smi_info->supports_event_msg_buff || smi_info->io.irq) अणु
			start_check_enables(smi_info);
		पूर्ण अन्यथा अणु
			smi_info->curr_msg = alloc_msg_handle_irq(smi_info);
			अगर (!smi_info->curr_msg)
				जाओ out;

			start_getting_events(smi_info);
		पूर्ण
		जाओ restart;
	पूर्ण

	अगर (si_sm_result == SI_SM_IDLE && smi_info->समयr_running) अणु
		/* Ok it अगर fails, the समयr will just go off. */
		अगर (del_समयr(&smi_info->si_समयr))
			smi_info->समयr_running = false;
	पूर्ण

out:
	वापस si_sm_result;
पूर्ण

अटल व्योम check_start_समयr_thपढ़ो(काष्ठा smi_info *smi_info)
अणु
	अगर (smi_info->si_state == SI_NORMAL && smi_info->curr_msg == शून्य) अणु
		smi_mod_समयr(smi_info, jअगरfies + SI_TIMEOUT_JIFFIES);

		अगर (smi_info->thपढ़ो)
			wake_up_process(smi_info->thपढ़ो);

		start_next_msg(smi_info);
		smi_event_handler(smi_info, 0);
	पूर्ण
पूर्ण

अटल व्योम flush_messages(व्योम *send_info)
अणु
	काष्ठा smi_info *smi_info = send_info;
	क्रमागत si_sm_result result;

	/*
	 * Currently, this function is called only in run-to-completion
	 * mode.  This means we are single-thपढ़ोed, no need क्रम locks.
	 */
	result = smi_event_handler(smi_info, 0);
	जबतक (result != SI_SM_IDLE) अणु
		udelay(SI_SHORT_TIMEOUT_USEC);
		result = smi_event_handler(smi_info, SI_SHORT_TIMEOUT_USEC);
	पूर्ण
पूर्ण

अटल व्योम sender(व्योम                *send_info,
		   काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा smi_info   *smi_info = send_info;
	अचिन्हित दीर्घ     flags;

	debug_बारtamp("Enqueue");

	अगर (smi_info->run_to_completion) अणु
		/*
		 * If we are running to completion, start it.  Upper
		 * layer will call flush_messages to clear it out.
		 */
		smi_info->रुकोing_msg = msg;
		वापस;
	पूर्ण

	spin_lock_irqsave(&smi_info->si_lock, flags);
	/*
	 * The following two lines करोn't need to be under the lock क्रम
	 * the lock's sake, but they करो need SMP memory barriers to
	 * aव्योम getting things out of order.  We are alपढ़ोy claiming
	 * the lock, anyway, so just करो it under the lock to aव्योम the
	 * ordering problem.
	 */
	BUG_ON(smi_info->रुकोing_msg);
	smi_info->रुकोing_msg = msg;
	check_start_समयr_thपढ़ो(smi_info);
	spin_unlock_irqrestore(&smi_info->si_lock, flags);
पूर्ण

अटल व्योम set_run_to_completion(व्योम *send_info, bool i_run_to_completion)
अणु
	काष्ठा smi_info   *smi_info = send_info;

	smi_info->run_to_completion = i_run_to_completion;
	अगर (i_run_to_completion)
		flush_messages(smi_info);
पूर्ण

/*
 * Use -1 as a special स्थिरant to tell that we are spinning in kipmid
 * looking क्रम something and not delaying between checks
 */
#घोषणा IPMI_TIME_NOT_BUSY ns_to_kसमय(-1ull)
अटल अंतरभूत bool ipmi_thपढ़ो_busy_रुको(क्रमागत si_sm_result smi_result,
					 स्थिर काष्ठा smi_info *smi_info,
					 kसमय_प्रकार *busy_until)
अणु
	अचिन्हित पूर्णांक max_busy_us = 0;

	अगर (smi_info->si_num < num_max_busy_us)
		max_busy_us = kipmid_max_busy_us[smi_info->si_num];
	अगर (max_busy_us == 0 || smi_result != SI_SM_CALL_WITH_DELAY)
		*busy_until = IPMI_TIME_NOT_BUSY;
	अन्यथा अगर (*busy_until == IPMI_TIME_NOT_BUSY) अणु
		*busy_until = kसमय_get() + max_busy_us * NSEC_PER_USEC;
	पूर्ण अन्यथा अणु
		अगर (unlikely(kसमय_get() > *busy_until)) अणु
			*busy_until = IPMI_TIME_NOT_BUSY;
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण


/*
 * A busy-रुकोing loop क्रम speeding up IPMI operation.
 *
 * Lousy hardware makes this hard.  This is only enabled क्रम प्रणालीs
 * that are not BT and करो not have पूर्णांकerrupts.  It starts spinning
 * when an operation is complete or until max_busy tells it to stop
 * (अगर that is enabled).  See the paragraph on kimid_max_busy_us in
 * Documentation/driver-api/ipmi.rst क्रम details.
 */
अटल पूर्णांक ipmi_thपढ़ो(व्योम *data)
अणु
	काष्ठा smi_info *smi_info = data;
	अचिन्हित दीर्घ flags;
	क्रमागत si_sm_result smi_result;
	kसमय_प्रकार busy_until = IPMI_TIME_NOT_BUSY;

	set_user_nice(current, MAX_NICE);
	जबतक (!kthपढ़ो_should_stop()) अणु
		पूर्णांक busy_रुको;

		spin_lock_irqsave(&(smi_info->si_lock), flags);
		smi_result = smi_event_handler(smi_info, 0);

		/*
		 * If the driver is करोing something, there is a possible
		 * race with the समयr.  If the समयr handler see idle,
		 * and the thपढ़ो here sees something अन्यथा, the समयr
		 * handler won't restart the समयr even though it is
		 * required.  So start it here अगर necessary.
		 */
		अगर (smi_result != SI_SM_IDLE && !smi_info->समयr_running)
			smi_mod_समयr(smi_info, jअगरfies + SI_TIMEOUT_JIFFIES);

		spin_unlock_irqrestore(&(smi_info->si_lock), flags);
		busy_रुको = ipmi_thपढ़ो_busy_रुको(smi_result, smi_info,
						  &busy_until);
		अगर (smi_result == SI_SM_CALL_WITHOUT_DELAY) अणु
			; /* करो nothing */
		पूर्ण अन्यथा अगर (smi_result == SI_SM_CALL_WITH_DELAY && busy_रुको) अणु
			/*
			 * In मुख्यtenance mode we run as fast as
			 * possible to allow firmware updates to
			 * complete as fast as possible, but normally
			 * करोn't bang on the scheduler.
			 */
			अगर (smi_info->in_मुख्यtenance_mode)
				schedule();
			अन्यथा
				usleep_range(100, 200);
		पूर्ण अन्यथा अगर (smi_result == SI_SM_IDLE) अणु
			अगर (atomic_पढ़ो(&smi_info->need_watch)) अणु
				schedule_समयout_पूर्णांकerruptible(100);
			पूर्ण अन्यथा अणु
				/* Wait to be woken up when we are needed. */
				__set_current_state(TASK_INTERRUPTIBLE);
				schedule();
			पूर्ण
		पूर्ण अन्यथा अणु
			schedule_समयout_पूर्णांकerruptible(1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम poll(व्योम *send_info)
अणु
	काष्ठा smi_info *smi_info = send_info;
	अचिन्हित दीर्घ flags = 0;
	bool run_to_completion = smi_info->run_to_completion;

	/*
	 * Make sure there is some delay in the poll loop so we can
	 * drive समय क्रमward and समयout things.
	 */
	udelay(10);
	अगर (!run_to_completion)
		spin_lock_irqsave(&smi_info->si_lock, flags);
	smi_event_handler(smi_info, 10);
	अगर (!run_to_completion)
		spin_unlock_irqrestore(&smi_info->si_lock, flags);
पूर्ण

अटल व्योम request_events(व्योम *send_info)
अणु
	काष्ठा smi_info *smi_info = send_info;

	अगर (!smi_info->has_event_buffer)
		वापस;

	atomic_set(&smi_info->req_events, 1);
पूर्ण

अटल व्योम set_need_watch(व्योम *send_info, अचिन्हित पूर्णांक watch_mask)
अणु
	काष्ठा smi_info *smi_info = send_info;
	अचिन्हित दीर्घ flags;
	पूर्णांक enable;

	enable = !!watch_mask;

	atomic_set(&smi_info->need_watch, enable);
	spin_lock_irqsave(&smi_info->si_lock, flags);
	check_start_समयr_thपढ़ो(smi_info);
	spin_unlock_irqrestore(&smi_info->si_lock, flags);
पूर्ण

अटल व्योम smi_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा smi_info   *smi_info = from_समयr(smi_info, t, si_समयr);
	क्रमागत si_sm_result smi_result;
	अचिन्हित दीर्घ     flags;
	अचिन्हित दीर्घ     jअगरfies_now;
	दीर्घ              समय_dअगरf;
	दीर्घ		  समयout;

	spin_lock_irqsave(&(smi_info->si_lock), flags);
	debug_बारtamp("Timer");

	jअगरfies_now = jअगरfies;
	समय_dअगरf = (((दीर्घ)jअगरfies_now - (दीर्घ)smi_info->last_समयout_jअगरfies)
		     * SI_USEC_PER_JIFFY);
	smi_result = smi_event_handler(smi_info, समय_dअगरf);

	अगर ((smi_info->io.irq) && (!smi_info->पूर्णांकerrupt_disabled)) अणु
		/* Running with पूर्णांकerrupts, only करो दीर्घ समयouts. */
		समयout = jअगरfies + SI_TIMEOUT_JIFFIES;
		smi_inc_stat(smi_info, दीर्घ_समयouts);
		जाओ करो_mod_समयr;
	पूर्ण

	/*
	 * If the state machine asks क्रम a लघु delay, then लघुen
	 * the समयr समयout.
	 */
	अगर (smi_result == SI_SM_CALL_WITH_DELAY) अणु
		smi_inc_stat(smi_info, लघु_समयouts);
		समयout = jअगरfies + 1;
	पूर्ण अन्यथा अणु
		smi_inc_stat(smi_info, दीर्घ_समयouts);
		समयout = jअगरfies + SI_TIMEOUT_JIFFIES;
	पूर्ण

करो_mod_समयr:
	अगर (smi_result != SI_SM_IDLE)
		smi_mod_समयr(smi_info, समयout);
	अन्यथा
		smi_info->समयr_running = false;
	spin_unlock_irqrestore(&(smi_info->si_lock), flags);
पूर्ण

irqवापस_t ipmi_si_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा smi_info *smi_info = data;
	अचिन्हित दीर्घ   flags;

	अगर (smi_info->io.si_type == SI_BT)
		/* We need to clear the IRQ flag क्रम the BT पूर्णांकerface. */
		smi_info->io.outputb(&smi_info->io, IPMI_BT_INTMASK_REG,
				     IPMI_BT_INTMASK_CLEAR_IRQ_BIT
				     | IPMI_BT_INTMASK_ENABLE_IRQ_BIT);

	spin_lock_irqsave(&(smi_info->si_lock), flags);

	smi_inc_stat(smi_info, पूर्णांकerrupts);

	debug_बारtamp("Interrupt");

	smi_event_handler(smi_info, 0);
	spin_unlock_irqrestore(&(smi_info->si_lock), flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक smi_start_processing(व्योम            *send_info,
				काष्ठा ipmi_smi *पूर्णांकf)
अणु
	काष्ठा smi_info *new_smi = send_info;
	पूर्णांक             enable = 0;

	new_smi->पूर्णांकf = पूर्णांकf;

	/* Set up the समयr that drives the पूर्णांकerface. */
	समयr_setup(&new_smi->si_समयr, smi_समयout, 0);
	new_smi->समयr_can_start = true;
	smi_mod_समयr(new_smi, jअगरfies + SI_TIMEOUT_JIFFIES);

	/* Try to claim any पूर्णांकerrupts. */
	अगर (new_smi->io.irq_setup) अणु
		new_smi->io.irq_handler_data = new_smi;
		new_smi->io.irq_setup(&new_smi->io);
	पूर्ण

	/*
	 * Check अगर the user क्रमcefully enabled the daemon.
	 */
	अगर (new_smi->si_num < num_क्रमce_kipmid)
		enable = क्रमce_kipmid[new_smi->si_num];
	/*
	 * The BT पूर्णांकerface is efficient enough to not need a thपढ़ो,
	 * and there is no need क्रम a thपढ़ो अगर we have पूर्णांकerrupts.
	 */
	अन्यथा अगर ((new_smi->io.si_type != SI_BT) && (!new_smi->io.irq))
		enable = 1;

	अगर (enable) अणु
		new_smi->thपढ़ो = kthपढ़ो_run(ipmi_thपढ़ो, new_smi,
					      "kipmi%d", new_smi->si_num);
		अगर (IS_ERR(new_smi->thपढ़ो)) अणु
			dev_notice(new_smi->io.dev,
				   "Could not start kernel thread due to error %ld, only using timers to drive the interface\n",
				   PTR_ERR(new_smi->thपढ़ो));
			new_smi->thपढ़ो = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_smi_info(व्योम *send_info, काष्ठा ipmi_smi_info *data)
अणु
	काष्ठा smi_info *smi = send_info;

	data->addr_src = smi->io.addr_source;
	data->dev = smi->io.dev;
	data->addr_info = smi->io.addr_info;
	get_device(smi->io.dev);

	वापस 0;
पूर्ण

अटल व्योम set_मुख्यtenance_mode(व्योम *send_info, bool enable)
अणु
	काष्ठा smi_info   *smi_info = send_info;

	अगर (!enable)
		atomic_set(&smi_info->req_events, 0);
	smi_info->in_मुख्यtenance_mode = enable;
पूर्ण

अटल व्योम shutकरोwn_smi(व्योम *send_info);
अटल स्थिर काष्ठा ipmi_smi_handlers handlers = अणु
	.owner                  = THIS_MODULE,
	.start_processing       = smi_start_processing,
	.shutकरोwn               = shutकरोwn_smi,
	.get_smi_info		= get_smi_info,
	.sender			= sender,
	.request_events		= request_events,
	.set_need_watch		= set_need_watch,
	.set_मुख्यtenance_mode   = set_मुख्यtenance_mode,
	.set_run_to_completion  = set_run_to_completion,
	.flush_messages		= flush_messages,
	.poll			= poll,
पूर्ण;

अटल LIST_HEAD(smi_infos);
अटल DEFINE_MUTEX(smi_infos_lock);
अटल पूर्णांक smi_num; /* Used to sequence the SMIs */

अटल स्थिर अक्षर * स्थिर addr_space_to_str[] = अणु "i/o", "mem" पूर्ण;

module_param_array(क्रमce_kipmid, पूर्णांक, &num_क्रमce_kipmid, 0);
MODULE_PARM_DESC(क्रमce_kipmid,
		 "Force the kipmi daemon to be enabled (1) or disabled(0).  Normally the IPMI driver auto-detects this, but the value may be overridden by this parm.");
module_param(unload_when_empty, bool, 0);
MODULE_PARM_DESC(unload_when_empty,
		 "Unload the module if no interfaces are specified or found, default is 1.  Setting to 0 is useful for hot add of devices using hotmod.");
module_param_array(kipmid_max_busy_us, uपूर्णांक, &num_max_busy_us, 0644);
MODULE_PARM_DESC(kipmid_max_busy_us,
		 "Max time (in microseconds) to busy-wait for IPMI data before sleeping. 0 (default) means to wait forever. Set to 100-500 if kipmid is using up a lot of CPU time.");

व्योम ipmi_irq_finish_setup(काष्ठा si_sm_io *io)
अणु
	अगर (io->si_type == SI_BT)
		/* Enable the पूर्णांकerrupt in the BT पूर्णांकerface. */
		io->outputb(io, IPMI_BT_INTMASK_REG,
			    IPMI_BT_INTMASK_ENABLE_IRQ_BIT);
पूर्ण

व्योम ipmi_irq_start_cleanup(काष्ठा si_sm_io *io)
अणु
	अगर (io->si_type == SI_BT)
		/* Disable the पूर्णांकerrupt in the BT पूर्णांकerface. */
		io->outputb(io, IPMI_BT_INTMASK_REG, 0);
पूर्ण

अटल व्योम std_irq_cleanup(काष्ठा si_sm_io *io)
अणु
	ipmi_irq_start_cleanup(io);
	मुक्त_irq(io->irq, io->irq_handler_data);
पूर्ण

पूर्णांक ipmi_std_irq_setup(काष्ठा si_sm_io *io)
अणु
	पूर्णांक rv;

	अगर (!io->irq)
		वापस 0;

	rv = request_irq(io->irq,
			 ipmi_si_irq_handler,
			 IRQF_SHARED,
			 SI_DEVICE_NAME,
			 io->irq_handler_data);
	अगर (rv) अणु
		dev_warn(io->dev, "%s unable to claim interrupt %d, running polled\n",
			 SI_DEVICE_NAME, io->irq);
		io->irq = 0;
	पूर्ण अन्यथा अणु
		io->irq_cleanup = std_irq_cleanup;
		ipmi_irq_finish_setup(io);
		dev_info(io->dev, "Using irq %d\n", io->irq);
	पूर्ण

	वापस rv;
पूर्ण

अटल पूर्णांक रुको_क्रम_msg_करोne(काष्ठा smi_info *smi_info)
अणु
	क्रमागत si_sm_result     smi_result;

	smi_result = smi_info->handlers->event(smi_info->si_sm, 0);
	क्रम (;;) अणु
		अगर (smi_result == SI_SM_CALL_WITH_DELAY ||
		    smi_result == SI_SM_CALL_WITH_TICK_DELAY) अणु
			schedule_समयout_unपूर्णांकerruptible(1);
			smi_result = smi_info->handlers->event(
				smi_info->si_sm, jअगरfies_to_usecs(1));
		पूर्ण अन्यथा अगर (smi_result == SI_SM_CALL_WITHOUT_DELAY) अणु
			smi_result = smi_info->handlers->event(
				smi_info->si_sm, 0);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	अगर (smi_result == SI_SM_HOSED)
		/*
		 * We couldn't get the state machine to run, so whatever's at
		 * the port is probably not an IPMI SMI पूर्णांकerface.
		 */
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक try_get_dev_id(काष्ठा smi_info *smi_info)
अणु
	अचिन्हित अक्षर         msg[2];
	अचिन्हित अक्षर         *resp;
	अचिन्हित दीर्घ         resp_len;
	पूर्णांक                   rv = 0;
	अचिन्हित पूर्णांक          retry_count = 0;

	resp = kदो_स्मृति(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	/*
	 * Do a Get Device ID command, since it comes back with some
	 * useful info.
	 */
	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_DEVICE_ID_CMD;

retry:
	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 2);

	rv = रुको_क्रम_msg_करोne(smi_info);
	अगर (rv)
		जाओ out;

	resp_len = smi_info->handlers->get_result(smi_info->si_sm,
						  resp, IPMI_MAX_MSG_LENGTH);

	/* Check and record info from the get device id, in हाल we need it. */
	rv = ipmi_demangle_device_id(resp[0] >> 2, resp[1],
			resp + 2, resp_len - 2, &smi_info->device_id);
	अगर (rv) अणु
		/* record completion code */
		अचिन्हित अक्षर cc = *(resp + 2);

		अगर (cc != IPMI_CC_NO_ERROR &&
		    ++retry_count <= GET_DEVICE_ID_MAX_RETRY) अणु
			dev_warn(smi_info->io.dev,
			    "BMC returned 0x%2.2x, retry get bmc device id\n",
			    cc);
			जाओ retry;
		पूर्ण
	पूर्ण

out:
	kमुक्त(resp);
	वापस rv;
पूर्ण

अटल पूर्णांक get_global_enables(काष्ठा smi_info *smi_info, u8 *enables)
अणु
	अचिन्हित अक्षर         msg[3];
	अचिन्हित अक्षर         *resp;
	अचिन्हित दीर्घ         resp_len;
	पूर्णांक                   rv;

	resp = kदो_स्मृति(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_BMC_GLOBAL_ENABLES_CMD;
	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 2);

	rv = रुको_क्रम_msg_करोne(smi_info);
	अगर (rv) अणु
		dev_warn(smi_info->io.dev,
			 "Error getting response from get global enables command: %d\n",
			 rv);
		जाओ out;
	पूर्ण

	resp_len = smi_info->handlers->get_result(smi_info->si_sm,
						  resp, IPMI_MAX_MSG_LENGTH);

	अगर (resp_len < 4 ||
			resp[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2 ||
			resp[1] != IPMI_GET_BMC_GLOBAL_ENABLES_CMD   ||
			resp[2] != 0) अणु
		dev_warn(smi_info->io.dev,
			 "Invalid return from get global enables command: %ld %x %x %x\n",
			 resp_len, resp[0], resp[1], resp[2]);
		rv = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अणु
		*enables = resp[3];
	पूर्ण

out:
	kमुक्त(resp);
	वापस rv;
पूर्ण

/*
 * Returns 1 अगर it माला_लो an error from the command.
 */
अटल पूर्णांक set_global_enables(काष्ठा smi_info *smi_info, u8 enables)
अणु
	अचिन्हित अक्षर         msg[3];
	अचिन्हित अक्षर         *resp;
	अचिन्हित दीर्घ         resp_len;
	पूर्णांक                   rv;

	resp = kदो_स्मृति(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_SET_BMC_GLOBAL_ENABLES_CMD;
	msg[2] = enables;
	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 3);

	rv = रुको_क्रम_msg_करोne(smi_info);
	अगर (rv) अणु
		dev_warn(smi_info->io.dev,
			 "Error getting response from set global enables command: %d\n",
			 rv);
		जाओ out;
	पूर्ण

	resp_len = smi_info->handlers->get_result(smi_info->si_sm,
						  resp, IPMI_MAX_MSG_LENGTH);

	अगर (resp_len < 3 ||
			resp[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2 ||
			resp[1] != IPMI_SET_BMC_GLOBAL_ENABLES_CMD) अणु
		dev_warn(smi_info->io.dev,
			 "Invalid return from set global enables command: %ld %x %x\n",
			 resp_len, resp[0], resp[1]);
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (resp[2] != 0)
		rv = 1;

out:
	kमुक्त(resp);
	वापस rv;
पूर्ण

/*
 * Some BMCs करो not support clearing the receive irq bit in the global
 * enables (even अगर they करोn't support पूर्णांकerrupts on the BMC).  Check
 * क्रम this and handle it properly.
 */
अटल व्योम check_clr_rcv_irq(काष्ठा smi_info *smi_info)
अणु
	u8 enables = 0;
	पूर्णांक rv;

	rv = get_global_enables(smi_info, &enables);
	अगर (!rv) अणु
		अगर ((enables & IPMI_BMC_RCV_MSG_INTR) == 0)
			/* Alपढ़ोy clear, should work ok. */
			वापस;

		enables &= ~IPMI_BMC_RCV_MSG_INTR;
		rv = set_global_enables(smi_info, enables);
	पूर्ण

	अगर (rv < 0) अणु
		dev_err(smi_info->io.dev,
			"Cannot check clearing the rcv irq: %d\n", rv);
		वापस;
	पूर्ण

	अगर (rv) अणु
		/*
		 * An error when setting the event buffer bit means
		 * clearing the bit is not supported.
		 */
		dev_warn(smi_info->io.dev,
			 "The BMC does not support clearing the recv irq bit, compensating, but the BMC needs to be fixed.\n");
		smi_info->cannot_disable_irq = true;
	पूर्ण
पूर्ण

/*
 * Some BMCs करो not support setting the पूर्णांकerrupt bits in the global
 * enables even अगर they support पूर्णांकerrupts.  Clearly bad, but we can
 * compensate.
 */
अटल व्योम check_set_rcv_irq(काष्ठा smi_info *smi_info)
अणु
	u8 enables = 0;
	पूर्णांक rv;

	अगर (!smi_info->io.irq)
		वापस;

	rv = get_global_enables(smi_info, &enables);
	अगर (!rv) अणु
		enables |= IPMI_BMC_RCV_MSG_INTR;
		rv = set_global_enables(smi_info, enables);
	पूर्ण

	अगर (rv < 0) अणु
		dev_err(smi_info->io.dev,
			"Cannot check setting the rcv irq: %d\n", rv);
		वापस;
	पूर्ण

	अगर (rv) अणु
		/*
		 * An error when setting the event buffer bit means
		 * setting the bit is not supported.
		 */
		dev_warn(smi_info->io.dev,
			 "The BMC does not support setting the recv irq bit, compensating, but the BMC needs to be fixed.\n");
		smi_info->cannot_disable_irq = true;
		smi_info->irq_enable_broken = true;
	पूर्ण
पूर्ण

अटल पूर्णांक try_enable_event_buffer(काष्ठा smi_info *smi_info)
अणु
	अचिन्हित अक्षर         msg[3];
	अचिन्हित अक्षर         *resp;
	अचिन्हित दीर्घ         resp_len;
	पूर्णांक                   rv = 0;

	resp = kदो_स्मृति(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_BMC_GLOBAL_ENABLES_CMD;
	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 2);

	rv = रुको_क्रम_msg_करोne(smi_info);
	अगर (rv) अणु
		pr_warn("Error getting response from get global enables command, the event buffer is not enabled\n");
		जाओ out;
	पूर्ण

	resp_len = smi_info->handlers->get_result(smi_info->si_sm,
						  resp, IPMI_MAX_MSG_LENGTH);

	अगर (resp_len < 4 ||
			resp[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2 ||
			resp[1] != IPMI_GET_BMC_GLOBAL_ENABLES_CMD   ||
			resp[2] != 0) अणु
		pr_warn("Invalid return from get global enables command, cannot enable the event buffer\n");
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (resp[3] & IPMI_BMC_EVT_MSG_BUFF) अणु
		/* buffer is alपढ़ोy enabled, nothing to करो. */
		smi_info->supports_event_msg_buff = true;
		जाओ out;
	पूर्ण

	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_SET_BMC_GLOBAL_ENABLES_CMD;
	msg[2] = resp[3] | IPMI_BMC_EVT_MSG_BUFF;
	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 3);

	rv = रुको_क्रम_msg_करोne(smi_info);
	अगर (rv) अणु
		pr_warn("Error getting response from set global, enables command, the event buffer is not enabled\n");
		जाओ out;
	पूर्ण

	resp_len = smi_info->handlers->get_result(smi_info->si_sm,
						  resp, IPMI_MAX_MSG_LENGTH);

	अगर (resp_len < 3 ||
			resp[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2 ||
			resp[1] != IPMI_SET_BMC_GLOBAL_ENABLES_CMD) अणु
		pr_warn("Invalid return from get global, enables command, not enable the event buffer\n");
		rv = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (resp[2] != 0)
		/*
		 * An error when setting the event buffer bit means
		 * that the event buffer is not supported.
		 */
		rv = -ENOENT;
	अन्यथा
		smi_info->supports_event_msg_buff = true;

out:
	kमुक्त(resp);
	वापस rv;
पूर्ण

#घोषणा IPMI_SI_ATTR(name) \
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,			\
			   काष्ठा device_attribute *attr,		\
			   अक्षर *buf)					\
अणु									\
	काष्ठा smi_info *smi_info = dev_get_drvdata(dev);		\
									\
	वापस snम_लिखो(buf, 10, "%u\n", smi_get_stat(smi_info, name));	\
पूर्ण									\
अटल DEVICE_ATTR(name, 0444, name##_show, शून्य)

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा smi_info *smi_info = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, 10, "%s\n", si_to_str[smi_info->io.si_type]);
पूर्ण
अटल DEVICE_ATTR(type, 0444, type_show, शून्य);

अटल sमाप_प्रकार पूर्णांकerrupts_enabled_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा smi_info *smi_info = dev_get_drvdata(dev);
	पूर्णांक enabled = smi_info->io.irq && !smi_info->पूर्णांकerrupt_disabled;

	वापस snम_लिखो(buf, 10, "%d\n", enabled);
पूर्ण
अटल DEVICE_ATTR(पूर्णांकerrupts_enabled, 0444,
		   पूर्णांकerrupts_enabled_show, शून्य);

IPMI_SI_ATTR(लघु_समयouts);
IPMI_SI_ATTR(दीर्घ_समयouts);
IPMI_SI_ATTR(idles);
IPMI_SI_ATTR(पूर्णांकerrupts);
IPMI_SI_ATTR(attentions);
IPMI_SI_ATTR(flag_fetches);
IPMI_SI_ATTR(hosed_count);
IPMI_SI_ATTR(complete_transactions);
IPMI_SI_ATTR(events);
IPMI_SI_ATTR(watchकरोg_preसमयouts);
IPMI_SI_ATTR(incoming_messages);

अटल sमाप_प्रकार params_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा smi_info *smi_info = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, 200,
			"%s,%s,0x%lx,rsp=%d,rsi=%d,rsh=%d,irq=%d,ipmb=%d\n",
			si_to_str[smi_info->io.si_type],
			addr_space_to_str[smi_info->io.addr_space],
			smi_info->io.addr_data,
			smi_info->io.regspacing,
			smi_info->io.regsize,
			smi_info->io.regshअगरt,
			smi_info->io.irq,
			smi_info->io.slave_addr);
पूर्ण
अटल DEVICE_ATTR(params, 0444, params_show, शून्य);

अटल काष्ठा attribute *ipmi_si_dev_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_पूर्णांकerrupts_enabled.attr,
	&dev_attr_लघु_समयouts.attr,
	&dev_attr_दीर्घ_समयouts.attr,
	&dev_attr_idles.attr,
	&dev_attr_पूर्णांकerrupts.attr,
	&dev_attr_attentions.attr,
	&dev_attr_flag_fetches.attr,
	&dev_attr_hosed_count.attr,
	&dev_attr_complete_transactions.attr,
	&dev_attr_events.attr,
	&dev_attr_watchकरोg_preसमयouts.attr,
	&dev_attr_incoming_messages.attr,
	&dev_attr_params.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ipmi_si_dev_attr_group = अणु
	.attrs		= ipmi_si_dev_attrs,
पूर्ण;

/*
 * oem_data_avail_to_receive_msg_avail
 * @info - smi_info काष्ठाure with msg_flags set
 *
 * Converts flags from OEM_DATA_AVAIL to RECEIVE_MSG_AVAIL
 * Returns 1 indicating need to re-run handle_flags().
 */
अटल पूर्णांक oem_data_avail_to_receive_msg_avail(काष्ठा smi_info *smi_info)
अणु
	smi_info->msg_flags = ((smi_info->msg_flags & ~OEM_DATA_AVAIL) |
			       RECEIVE_MSG_AVAIL);
	वापस 1;
पूर्ण

/*
 * setup_dell_घातeredge_oem_data_handler
 * @info - smi_info.device_id must be populated
 *
 * Systems that match, but have firmware version < 1.40 may निश्चित
 * OEM0_DATA_AVAIL on their own, without being told via Set Flags that
 * it's safe to करो so.  Such प्रणालीs will de-निश्चित OEM1_DATA_AVAIL
 * upon receipt of IPMI_GET_MSG_CMD, so we should treat these flags
 * as RECEIVE_MSG_AVAIL instead.
 *
 * As Dell has no plans to release IPMI 1.5 firmware that *ever*
 * निश्चित the OEM[012] bits, and अगर it did, the driver would have to
 * change to handle that properly, we करोn't actually check क्रम the
 * firmware version.
 * Device ID = 0x20                BMC on PowerEdge 8G servers
 * Device Revision = 0x80
 * Firmware Revision1 = 0x01       BMC version 1.40
 * Firmware Revision2 = 0x40       BCD encoded
 * IPMI Version = 0x51             IPMI 1.5
 * Manufacturer ID = A2 02 00      Dell IANA
 *
 * Additionally, PowerEdge प्रणालीs with IPMI < 1.5 may also निश्चित
 * OEM0_DATA_AVAIL and needs to be treated as RECEIVE_MSG_AVAIL.
 *
 */
#घोषणा DELL_POWEREDGE_8G_BMC_DEVICE_ID  0x20
#घोषणा DELL_POWEREDGE_8G_BMC_DEVICE_REV 0x80
#घोषणा DELL_POWEREDGE_8G_BMC_IPMI_VERSION 0x51
#घोषणा DELL_IANA_MFR_ID 0x0002a2
अटल व्योम setup_dell_घातeredge_oem_data_handler(काष्ठा smi_info *smi_info)
अणु
	काष्ठा ipmi_device_id *id = &smi_info->device_id;
	अगर (id->manufacturer_id == DELL_IANA_MFR_ID) अणु
		अगर (id->device_id       == DELL_POWEREDGE_8G_BMC_DEVICE_ID  &&
		    id->device_revision == DELL_POWEREDGE_8G_BMC_DEVICE_REV &&
		    id->ipmi_version   == DELL_POWEREDGE_8G_BMC_IPMI_VERSION) अणु
			smi_info->oem_data_avail_handler =
				oem_data_avail_to_receive_msg_avail;
		पूर्ण अन्यथा अगर (ipmi_version_major(id) < 1 ||
			   (ipmi_version_major(id) == 1 &&
			    ipmi_version_minor(id) < 5)) अणु
			smi_info->oem_data_avail_handler =
				oem_data_avail_to_receive_msg_avail;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा CANNOT_RETURN_REQUESTED_LENGTH 0xCA
अटल व्योम वापस_hosed_msg_badsize(काष्ठा smi_info *smi_info)
अणु
	काष्ठा ipmi_smi_msg *msg = smi_info->curr_msg;

	/* Make it a response */
	msg->rsp[0] = msg->data[0] | 4;
	msg->rsp[1] = msg->data[1];
	msg->rsp[2] = CANNOT_RETURN_REQUESTED_LENGTH;
	msg->rsp_size = 3;
	smi_info->curr_msg = शून्य;
	deliver_recv_msg(smi_info, msg);
पूर्ण

/*
 * dell_घातeredge_bt_xaction_handler
 * @info - smi_info.device_id must be populated
 *
 * Dell PowerEdge servers with the BT पूर्णांकerface (x6xx and 1750) will
 * not respond to a Get SDR command अगर the length of the data
 * requested is exactly 0x3A, which leads to command समयouts and no
 * data वापसed.  This पूर्णांकercepts such commands, and causes userspace
 * callers to try again with a dअगरferent-sized buffer, which succeeds.
 */

#घोषणा STORAGE_NETFN 0x0A
#घोषणा STORAGE_CMD_GET_SDR 0x23
अटल पूर्णांक dell_घातeredge_bt_xaction_handler(काष्ठा notअगरier_block *self,
					     अचिन्हित दीर्घ unused,
					     व्योम *in)
अणु
	काष्ठा smi_info *smi_info = in;
	अचिन्हित अक्षर *data = smi_info->curr_msg->data;
	अचिन्हित पूर्णांक size   = smi_info->curr_msg->data_size;
	अगर (size >= 8 &&
	    (data[0]>>2) == STORAGE_NETFN &&
	    data[1] == STORAGE_CMD_GET_SDR &&
	    data[7] == 0x3A) अणु
		वापस_hosed_msg_badsize(smi_info);
		वापस NOTIFY_STOP;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block dell_घातeredge_bt_xaction_notअगरier = अणु
	.notअगरier_call	= dell_घातeredge_bt_xaction_handler,
पूर्ण;

/*
 * setup_dell_घातeredge_bt_xaction_handler
 * @info - smi_info.device_id must be filled in alपढ़ोy
 *
 * Fills in smi_info.device_id.start_transaction_pre_hook
 * when we know what function to use there.
 */
अटल व्योम
setup_dell_घातeredge_bt_xaction_handler(काष्ठा smi_info *smi_info)
अणु
	काष्ठा ipmi_device_id *id = &smi_info->device_id;
	अगर (id->manufacturer_id == DELL_IANA_MFR_ID &&
	    smi_info->io.si_type == SI_BT)
		रेजिस्टर_xaction_notअगरier(&dell_घातeredge_bt_xaction_notअगरier);
पूर्ण

/*
 * setup_oem_data_handler
 * @info - smi_info.device_id must be filled in alपढ़ोy
 *
 * Fills in smi_info.device_id.oem_data_available_handler
 * when we know what function to use there.
 */

अटल व्योम setup_oem_data_handler(काष्ठा smi_info *smi_info)
अणु
	setup_dell_घातeredge_oem_data_handler(smi_info);
पूर्ण

अटल व्योम setup_xaction_handlers(काष्ठा smi_info *smi_info)
अणु
	setup_dell_घातeredge_bt_xaction_handler(smi_info);
पूर्ण

अटल व्योम check_क्रम_broken_irqs(काष्ठा smi_info *smi_info)
अणु
	check_clr_rcv_irq(smi_info);
	check_set_rcv_irq(smi_info);
पूर्ण

अटल अंतरभूत व्योम stop_समयr_and_thपढ़ो(काष्ठा smi_info *smi_info)
अणु
	अगर (smi_info->thपढ़ो != शून्य) अणु
		kthपढ़ो_stop(smi_info->thपढ़ो);
		smi_info->thपढ़ो = शून्य;
	पूर्ण

	smi_info->समयr_can_start = false;
	del_समयr_sync(&smi_info->si_समयr);
पूर्ण

अटल काष्ठा smi_info *find_dup_si(काष्ठा smi_info *info)
अणु
	काष्ठा smi_info *e;

	list_क्रम_each_entry(e, &smi_infos, link) अणु
		अगर (e->io.addr_space != info->io.addr_space)
			जारी;
		अगर (e->io.addr_data == info->io.addr_data) अणु
			/*
			 * This is a cheap hack, ACPI करोesn't have a defined
			 * slave address but SMBIOS करोes.  Pick it up from
			 * any source that has it available.
			 */
			अगर (info->io.slave_addr && !e->io.slave_addr)
				e->io.slave_addr = info->io.slave_addr;
			वापस e;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक ipmi_si_add_smi(काष्ठा si_sm_io *io)
अणु
	पूर्णांक rv = 0;
	काष्ठा smi_info *new_smi, *dup;

	/*
	 * If the user gave us a hard-coded device at the same
	 * address, they presumably want us to use it and not what is
	 * in the firmware.
	 */
	अगर (io->addr_source != SI_HARDCODED && io->addr_source != SI_HOTMOD &&
	    ipmi_si_hardcode_match(io->addr_space, io->addr_data)) अणु
		dev_info(io->dev,
			 "Hard-coded device at this address already exists");
		वापस -ENODEV;
	पूर्ण

	अगर (!io->io_setup) अणु
		अगर (io->addr_space == IPMI_IO_ADDR_SPACE) अणु
			io->io_setup = ipmi_si_port_setup;
		पूर्ण अन्यथा अगर (io->addr_space == IPMI_MEM_ADDR_SPACE) अणु
			io->io_setup = ipmi_si_mem_setup;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	new_smi = kzalloc(माप(*new_smi), GFP_KERNEL);
	अगर (!new_smi)
		वापस -ENOMEM;
	spin_lock_init(&new_smi->si_lock);

	new_smi->io = *io;

	mutex_lock(&smi_infos_lock);
	dup = find_dup_si(new_smi);
	अगर (dup) अणु
		अगर (new_smi->io.addr_source == SI_ACPI &&
		    dup->io.addr_source == SI_SMBIOS) अणु
			/* We prefer ACPI over SMBIOS. */
			dev_info(dup->io.dev,
				 "Removing SMBIOS-specified %s state machine in favor of ACPI\n",
				 si_to_str[new_smi->io.si_type]);
			cleanup_one_si(dup);
		पूर्ण अन्यथा अणु
			dev_info(new_smi->io.dev,
				 "%s-specified %s state machine: duplicate\n",
				 ipmi_addr_src_to_str(new_smi->io.addr_source),
				 si_to_str[new_smi->io.si_type]);
			rv = -EBUSY;
			kमुक्त(new_smi);
			जाओ out_err;
		पूर्ण
	पूर्ण

	pr_info("Adding %s-specified %s state machine\n",
		ipmi_addr_src_to_str(new_smi->io.addr_source),
		si_to_str[new_smi->io.si_type]);

	list_add_tail(&new_smi->link, &smi_infos);

	अगर (initialized)
		rv = try_smi_init(new_smi);
out_err:
	mutex_unlock(&smi_infos_lock);
	वापस rv;
पूर्ण

/*
 * Try to start up an पूर्णांकerface.  Must be called with smi_infos_lock
 * held, primarily to keep smi_num consistent, we only one to करो these
 * one at a समय.
 */
अटल पूर्णांक try_smi_init(काष्ठा smi_info *new_smi)
अणु
	पूर्णांक rv = 0;
	पूर्णांक i;

	pr_info("Trying %s-specified %s state machine at %s address 0x%lx, slave address 0x%x, irq %d\n",
		ipmi_addr_src_to_str(new_smi->io.addr_source),
		si_to_str[new_smi->io.si_type],
		addr_space_to_str[new_smi->io.addr_space],
		new_smi->io.addr_data,
		new_smi->io.slave_addr, new_smi->io.irq);

	चयन (new_smi->io.si_type) अणु
	हाल SI_KCS:
		new_smi->handlers = &kcs_smi_handlers;
		अवरोध;

	हाल SI_SMIC:
		new_smi->handlers = &smic_smi_handlers;
		अवरोध;

	हाल SI_BT:
		new_smi->handlers = &bt_smi_handlers;
		अवरोध;

	शेष:
		/* No support क्रम anything अन्यथा yet. */
		rv = -EIO;
		जाओ out_err;
	पूर्ण

	new_smi->si_num = smi_num;

	/* Do this early so it's available क्रम logs. */
	अगर (!new_smi->io.dev) अणु
		pr_err("IPMI interface added with no device\n");
		rv = -EIO;
		जाओ out_err;
	पूर्ण

	/* Allocate the state machine's data and initialize it. */
	new_smi->si_sm = kदो_स्मृति(new_smi->handlers->size(), GFP_KERNEL);
	अगर (!new_smi->si_sm) अणु
		rv = -ENOMEM;
		जाओ out_err;
	पूर्ण
	new_smi->io.io_size = new_smi->handlers->init_data(new_smi->si_sm,
							   &new_smi->io);

	/* Now that we know the I/O size, we can set up the I/O. */
	rv = new_smi->io.io_setup(&new_smi->io);
	अगर (rv) अणु
		dev_err(new_smi->io.dev, "Could not set up I/O space\n");
		जाओ out_err;
	पूर्ण

	/* Do low-level detection first. */
	अगर (new_smi->handlers->detect(new_smi->si_sm)) अणु
		अगर (new_smi->io.addr_source)
			dev_err(new_smi->io.dev,
				"Interface detection failed\n");
		rv = -ENODEV;
		जाओ out_err;
	पूर्ण

	/*
	 * Attempt a get device id command.  If it fails, we probably
	 * करोn't have a BMC here.
	 */
	rv = try_get_dev_id(new_smi);
	अगर (rv) अणु
		अगर (new_smi->io.addr_source)
			dev_err(new_smi->io.dev,
			       "There appears to be no BMC at this location\n");
		जाओ out_err;
	पूर्ण

	setup_oem_data_handler(new_smi);
	setup_xaction_handlers(new_smi);
	check_क्रम_broken_irqs(new_smi);

	new_smi->रुकोing_msg = शून्य;
	new_smi->curr_msg = शून्य;
	atomic_set(&new_smi->req_events, 0);
	new_smi->run_to_completion = false;
	क्रम (i = 0; i < SI_NUM_STATS; i++)
		atomic_set(&new_smi->stats[i], 0);

	new_smi->पूर्णांकerrupt_disabled = true;
	atomic_set(&new_smi->need_watch, 0);

	rv = try_enable_event_buffer(new_smi);
	अगर (rv == 0)
		new_smi->has_event_buffer = true;

	/*
	 * Start clearing the flags beक्रमe we enable पूर्णांकerrupts or the
	 * समयr to aव्योम racing with the समयr.
	 */
	start_clear_flags(new_smi);

	/*
	 * IRQ is defined to be set when non-zero.  req_events will
	 * cause a global flags check that will enable पूर्णांकerrupts.
	 */
	अगर (new_smi->io.irq) अणु
		new_smi->पूर्णांकerrupt_disabled = false;
		atomic_set(&new_smi->req_events, 1);
	पूर्ण

	dev_set_drvdata(new_smi->io.dev, new_smi);
	rv = device_add_group(new_smi->io.dev, &ipmi_si_dev_attr_group);
	अगर (rv) अणु
		dev_err(new_smi->io.dev,
			"Unable to add device attributes: error %d\n",
			rv);
		जाओ out_err;
	पूर्ण
	new_smi->dev_group_added = true;

	rv = ipmi_रेजिस्टर_smi(&handlers,
			       new_smi,
			       new_smi->io.dev,
			       new_smi->io.slave_addr);
	अगर (rv) अणु
		dev_err(new_smi->io.dev,
			"Unable to register device: error %d\n",
			rv);
		जाओ out_err;
	पूर्ण

	/* Don't increment till we know we have succeeded. */
	smi_num++;

	dev_info(new_smi->io.dev, "IPMI %s interface initialized\n",
		 si_to_str[new_smi->io.si_type]);

	WARN_ON(new_smi->io.dev->init_name != शून्य);

 out_err:
	अगर (rv && new_smi->io.io_cleanup) अणु
		new_smi->io.io_cleanup(&new_smi->io);
		new_smi->io.io_cleanup = शून्य;
	पूर्ण

	वापस rv;
पूर्ण

अटल पूर्णांक __init init_ipmi_si(व्योम)
अणु
	काष्ठा smi_info *e;
	क्रमागत ipmi_addr_src type = SI_INVALID;

	अगर (initialized)
		वापस 0;

	ipmi_hardcode_init();

	pr_info("IPMI System Interface driver\n");

	ipmi_si_platक्रमm_init();

	ipmi_si_pci_init();

	ipmi_si_parisc_init();

	/* We prefer devices with पूर्णांकerrupts, but in the हाल of a machine
	   with multiple BMCs we assume that there will be several instances
	   of a given type so अगर we succeed in रेजिस्टरing a type then also
	   try to रेजिस्टर everything अन्यथा of the same type */
	mutex_lock(&smi_infos_lock);
	list_क्रम_each_entry(e, &smi_infos, link) अणु
		/* Try to रेजिस्टर a device अगर it has an IRQ and we either
		   haven't successfully रेजिस्टरed a device yet or this
		   device has the same type as one we successfully रेजिस्टरed */
		अगर (e->io.irq && (!type || e->io.addr_source == type)) अणु
			अगर (!try_smi_init(e)) अणु
				type = e->io.addr_source;
			पूर्ण
		पूर्ण
	पूर्ण

	/* type will only have been set अगर we successfully रेजिस्टरed an si */
	अगर (type)
		जाओ skip_fallback_noirq;

	/* Fall back to the preferred device */

	list_क्रम_each_entry(e, &smi_infos, link) अणु
		अगर (!e->io.irq && (!type || e->io.addr_source == type)) अणु
			अगर (!try_smi_init(e)) अणु
				type = e->io.addr_source;
			पूर्ण
		पूर्ण
	पूर्ण

skip_fallback_noirq:
	initialized = true;
	mutex_unlock(&smi_infos_lock);

	अगर (type)
		वापस 0;

	mutex_lock(&smi_infos_lock);
	अगर (unload_when_empty && list_empty(&smi_infos)) अणु
		mutex_unlock(&smi_infos_lock);
		cleanup_ipmi_si();
		pr_warn("Unable to find any System Interface(s)\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		mutex_unlock(&smi_infos_lock);
		वापस 0;
	पूर्ण
पूर्ण
module_init(init_ipmi_si);

अटल व्योम shutकरोwn_smi(व्योम *send_info)
अणु
	काष्ठा smi_info *smi_info = send_info;

	अगर (smi_info->dev_group_added) अणु
		device_हटाओ_group(smi_info->io.dev, &ipmi_si_dev_attr_group);
		smi_info->dev_group_added = false;
	पूर्ण
	अगर (smi_info->io.dev)
		dev_set_drvdata(smi_info->io.dev, शून्य);

	/*
	 * Make sure that पूर्णांकerrupts, the समयr and the thपढ़ो are
	 * stopped and will not run again.
	 */
	smi_info->पूर्णांकerrupt_disabled = true;
	अगर (smi_info->io.irq_cleanup) अणु
		smi_info->io.irq_cleanup(&smi_info->io);
		smi_info->io.irq_cleanup = शून्य;
	पूर्ण
	stop_समयr_and_thपढ़ो(smi_info);

	/*
	 * Wait until we know that we are out of any पूर्णांकerrupt
	 * handlers might have been running beक्रमe we मुक्तd the
	 * पूर्णांकerrupt.
	 */
	synchronize_rcu();

	/*
	 * Timeouts are stopped, now make sure the पूर्णांकerrupts are off
	 * in the BMC.  Note that समयrs and CPU पूर्णांकerrupts are off,
	 * so no need क्रम locks.
	 */
	जबतक (smi_info->curr_msg || (smi_info->si_state != SI_NORMAL)) अणु
		poll(smi_info);
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	अगर (smi_info->handlers)
		disable_si_irq(smi_info);
	जबतक (smi_info->curr_msg || (smi_info->si_state != SI_NORMAL)) अणु
		poll(smi_info);
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	अगर (smi_info->handlers)
		smi_info->handlers->cleanup(smi_info->si_sm);

	अगर (smi_info->io.io_cleanup) अणु
		smi_info->io.io_cleanup(&smi_info->io);
		smi_info->io.io_cleanup = शून्य;
	पूर्ण

	kमुक्त(smi_info->si_sm);
	smi_info->si_sm = शून्य;

	smi_info->पूर्णांकf = शून्य;
पूर्ण

/*
 * Must be called with smi_infos_lock held, to serialize the
 * smi_info->पूर्णांकf check.
 */
अटल व्योम cleanup_one_si(काष्ठा smi_info *smi_info)
अणु
	अगर (!smi_info)
		वापस;

	list_del(&smi_info->link);

	अगर (smi_info->पूर्णांकf)
		ipmi_unरेजिस्टर_smi(smi_info->पूर्णांकf);

	kमुक्त(smi_info);
पूर्ण

पूर्णांक ipmi_si_हटाओ_by_dev(काष्ठा device *dev)
अणु
	काष्ठा smi_info *e;
	पूर्णांक rv = -ENOENT;

	mutex_lock(&smi_infos_lock);
	list_क्रम_each_entry(e, &smi_infos, link) अणु
		अगर (e->io.dev == dev) अणु
			cleanup_one_si(e);
			rv = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&smi_infos_lock);

	वापस rv;
पूर्ण

काष्ठा device *ipmi_si_हटाओ_by_data(पूर्णांक addr_space, क्रमागत si_type si_type,
				      अचिन्हित दीर्घ addr)
अणु
	/* हटाओ */
	काष्ठा smi_info *e, *पंचांगp_e;
	काष्ठा device *dev = शून्य;

	mutex_lock(&smi_infos_lock);
	list_क्रम_each_entry_safe(e, पंचांगp_e, &smi_infos, link) अणु
		अगर (e->io.addr_space != addr_space)
			जारी;
		अगर (e->io.si_type != si_type)
			जारी;
		अगर (e->io.addr_data == addr) अणु
			dev = get_device(e->io.dev);
			cleanup_one_si(e);
		पूर्ण
	पूर्ण
	mutex_unlock(&smi_infos_lock);

	वापस dev;
पूर्ण

अटल व्योम cleanup_ipmi_si(व्योम)
अणु
	काष्ठा smi_info *e, *पंचांगp_e;

	अगर (!initialized)
		वापस;

	ipmi_si_pci_shutकरोwn();

	ipmi_si_parisc_shutकरोwn();

	ipmi_si_platक्रमm_shutकरोwn();

	mutex_lock(&smi_infos_lock);
	list_क्रम_each_entry_safe(e, पंचांगp_e, &smi_infos, link)
		cleanup_one_si(e);
	mutex_unlock(&smi_infos_lock);

	ipmi_si_hardcode_निकास();
	ipmi_si_hoपंचांगod_निकास();
पूर्ण
module_निकास(cleanup_ipmi_si);

MODULE_ALIAS("platform:dmi-ipmi-si");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Corey Minyard <minyard@mvista.com>");
MODULE_DESCRIPTION("Interface to the IPMI driver for the KCS, SMIC, and BT system interfaces.");
