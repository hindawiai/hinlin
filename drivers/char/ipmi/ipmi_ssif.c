<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_ssअगर.c
 *
 * The पूर्णांकerface to the IPMI driver क्रम SMBus access to a SMBus
 * compliant device.  Called SSIF by the IPMI spec.
 *
 * Author: Intel Corporation
 *         Todd Davis <todd.c.davis@पूर्णांकel.com>
 *
 * Rewritten by Corey Minyard <minyard@acm.org> to support the
 * non-blocking I2C पूर्णांकerface, add support क्रम multi-part
 * transactions, add PEC support, and general clenaup.
 *
 * Copyright 2003 Intel Corporation
 * Copyright 2005 MontaVista Software
 */

/*
 * This file holds the "policy" क्रम the पूर्णांकerface to the SSIF state
 * machine.  It करोes the configuration, handles समयrs and पूर्णांकerrupts,
 * and drives the real SSIF state machine.
 */

#घोषणा pr_fmt(fmt) "ipmi_ssif: " fmt
#घोषणा dev_fmt(fmt) "ipmi_ssif: " fmt

#अगर defined(MODVERSIONS)
#समावेश <linux/modversions.h>
#पूर्ण_अगर

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/i2c.h>
#समावेश <linux/ipmi_smi.h>
#समावेश <linux/init.h>
#समावेश <linux/dmi.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/acpi.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/समय64.h>
#समावेश "ipmi_dmi.h"

#घोषणा DEVICE_NAME "ipmi_ssif"

#घोषणा IPMI_GET_SYSTEM_INTERFACE_CAPABILITIES_CMD	0x57

#घोषणा	SSIF_IPMI_REQUEST			2
#घोषणा	SSIF_IPMI_MULTI_PART_REQUEST_START	6
#घोषणा	SSIF_IPMI_MULTI_PART_REQUEST_MIDDLE	7
#घोषणा	SSIF_IPMI_MULTI_PART_REQUEST_END	8
#घोषणा	SSIF_IPMI_RESPONSE			3
#घोषणा	SSIF_IPMI_MULTI_PART_RESPONSE_MIDDLE	9

/* ssअगर_debug is a bit-field
 *	SSIF_DEBUG_MSG -	commands and their responses
 *	SSIF_DEBUG_STATES -	message states
 *	SSIF_DEBUG_TIMING -	 Measure बार between events in the driver
 */
#घोषणा SSIF_DEBUG_TIMING	4
#घोषणा SSIF_DEBUG_STATE	2
#घोषणा SSIF_DEBUG_MSG		1
#घोषणा SSIF_NODEBUG		0
#घोषणा SSIF_DEFAULT_DEBUG	(SSIF_NODEBUG)

/*
 * Timer values
 */
#घोषणा SSIF_MSG_USEC		20000	/* 20ms between message tries. */
#घोषणा SSIF_MSG_PART_USEC	5000	/* 5ms क्रम a message part */

/* How many बार to we retry sending/receiving the message. */
#घोषणा	SSIF_SEND_RETRIES	5
#घोषणा	SSIF_RECV_RETRIES	250

#घोषणा SSIF_MSG_MSEC		(SSIF_MSG_USEC / 1000)
#घोषणा SSIF_MSG_JIFFIES	((SSIF_MSG_USEC * 1000) / TICK_NSEC)
#घोषणा SSIF_MSG_PART_JIFFIES	((SSIF_MSG_PART_USEC * 1000) / TICK_NSEC)

/*
 * Timeout क्रम the watch, only used क्रम get flag समयr.
 */
#घोषणा SSIF_WATCH_MSG_TIMEOUT		msecs_to_jअगरfies(10)
#घोषणा SSIF_WATCH_WATCHDOG_TIMEOUT	msecs_to_jअगरfies(250)

क्रमागत ssअगर_पूर्णांकf_state अणु
	SSIF_NORMAL,
	SSIF_GETTING_FLAGS,
	SSIF_GETTING_EVENTS,
	SSIF_CLEARING_FLAGS,
	SSIF_GETTING_MESSAGES,
	/* FIXME - add watchकरोg stuff. */
पूर्ण;

#घोषणा SSIF_IDLE(ssअगर)	 ((ssअगर)->ssअगर_state == SSIF_NORMAL \
			  && (ssअगर)->curr_msg == शून्य)

/*
 * Indexes पूर्णांकo stats[] in ssअगर_info below.
 */
क्रमागत ssअगर_stat_indexes अणु
	/* Number of total messages sent. */
	SSIF_STAT_sent_messages = 0,

	/*
	 * Number of message parts sent.  Messages may be broken पूर्णांकo
	 * parts अगर they are दीर्घ.
	 */
	SSIF_STAT_sent_messages_parts,

	/*
	 * Number of समय a message was retried.
	 */
	SSIF_STAT_send_retries,

	/*
	 * Number of बार the send of a message failed.
	 */
	SSIF_STAT_send_errors,

	/*
	 * Number of message responses received.
	 */
	SSIF_STAT_received_messages,

	/*
	 * Number of message fragments received.
	 */
	SSIF_STAT_received_message_parts,

	/*
	 * Number of बार the receive of a message was retried.
	 */
	SSIF_STAT_receive_retries,

	/*
	 * Number of errors receiving messages.
	 */
	SSIF_STAT_receive_errors,

	/*
	 * Number of बार a flag fetch was requested.
	 */
	SSIF_STAT_flag_fetches,

	/*
	 * Number of बार the hardware didn't follow the state machine.
	 */
	SSIF_STAT_hosed,

	/*
	 * Number of received events.
	 */
	SSIF_STAT_events,

	/* Number of asyncronous messages received. */
	SSIF_STAT_incoming_messages,

	/* Number of watchकरोg preसमयouts. */
	SSIF_STAT_watchकरोg_preसमयouts,

	/* Number of alers received. */
	SSIF_STAT_alerts,

	/* Always add statistics beक्रमe this value, it must be last. */
	SSIF_NUM_STATS
पूर्ण;

काष्ठा ssअगर_addr_info अणु
	काष्ठा i2c_board_info binfo;
	अक्षर *adapter_name;
	पूर्णांक debug;
	पूर्णांक slave_addr;
	क्रमागत ipmi_addr_src addr_src;
	जोड़ ipmi_smi_info_जोड़ addr_info;
	काष्ठा device *dev;
	काष्ठा i2c_client *client;

	काष्ठा mutex clients_mutex;
	काष्ठा list_head clients;

	काष्ठा list_head link;
पूर्ण;

काष्ठा ssअगर_info;

प्रकार व्योम (*ssअगर_i2c_करोne)(काष्ठा ssअगर_info *ssअगर_info, पूर्णांक result,
			     अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len);

काष्ठा ssअगर_info अणु
	काष्ठा ipmi_smi     *पूर्णांकf;
	spinlock_t	    lock;
	काष्ठा ipmi_smi_msg *रुकोing_msg;
	काष्ठा ipmi_smi_msg *curr_msg;
	क्रमागत ssअगर_पूर्णांकf_state ssअगर_state;
	अचिन्हित दीर्घ       ssअगर_debug;

	काष्ठा ipmi_smi_handlers handlers;

	क्रमागत ipmi_addr_src addr_source; /* ACPI, PCI, SMBIOS, hardcode, etc. */
	जोड़ ipmi_smi_info_जोड़ addr_info;

	/*
	 * Flags from the last GET_MSG_FLAGS command, used when an ATTN
	 * is set to hold the flags until we are करोne handling everything
	 * from the flags.
	 */
#घोषणा RECEIVE_MSG_AVAIL	0x01
#घोषणा EVENT_MSG_BUFFER_FULL	0x02
#घोषणा WDT_PRE_TIMEOUT_INT	0x08
	अचिन्हित अक्षर       msg_flags;

	u8		    global_enables;
	bool		    has_event_buffer;
	bool		    supports_alert;

	/*
	 * Used to tell what we should करो with alerts.  If we are
	 * रुकोing on a response, पढ़ो the data immediately.
	 */
	bool		    got_alert;
	bool		    रुकोing_alert;

	/*
	 * If set to true, this will request events the next समय the
	 * state machine is idle.
	 */
	bool                req_events;

	/*
	 * If set to true, this will request flags the next समय the
	 * state machine is idle.
	 */
	bool                req_flags;

	/*
	 * Used to perक्रमm समयr operations when run-to-completion
	 * mode is on.  This is a countकरोwn समयr.
	 */
	पूर्णांक                 rtc_us_समयr;

	/* Used क्रम sending/receiving data.  +1 क्रम the length. */
	अचिन्हित अक्षर data[IPMI_MAX_MSG_LENGTH + 1];
	अचिन्हित पूर्णांक  data_len;

	/* Temp receive buffer, माला_लो copied पूर्णांकo data. */
	अचिन्हित अक्षर recv[I2C_SMBUS_BLOCK_MAX];

	काष्ठा i2c_client *client;
	ssअगर_i2c_करोne करोne_handler;

	/* Thपढ़ो पूर्णांकerface handling */
	काष्ठा task_काष्ठा *thपढ़ो;
	काष्ठा completion wake_thपढ़ो;
	bool stopping;
	पूर्णांक i2c_पढ़ो_ग_लिखो;
	पूर्णांक i2c_command;
	अचिन्हित अक्षर *i2c_data;
	अचिन्हित पूर्णांक i2c_size;

	काष्ठा समयr_list retry_समयr;
	पूर्णांक retries_left;

	दीर्घ watch_समयout;		/* Timeout क्रम flags check, 0 अगर off. */
	काष्ठा समयr_list watch_समयr;	/* Flag fetch समयr. */

	/* Info from SSIF cmd */
	अचिन्हित अक्षर max_xmit_msg_size;
	अचिन्हित अक्षर max_recv_msg_size;
	bool cmd8_works; /* See test_multipart_messages() क्रम details. */
	अचिन्हित पूर्णांक  multi_support;
	पूर्णांक           supports_pec;

#घोषणा SSIF_NO_MULTI		0
#घोषणा SSIF_MULTI_2_PART	1
#घोषणा SSIF_MULTI_n_PART	2
	अचिन्हित अक्षर *multi_data;
	अचिन्हित पूर्णांक  multi_len;
	अचिन्हित पूर्णांक  multi_pos;

	atomic_t stats[SSIF_NUM_STATS];
पूर्ण;

#घोषणा ssअगर_inc_stat(ssअगर, stat) \
	atomic_inc(&(ssअगर)->stats[SSIF_STAT_ ## stat])
#घोषणा ssअगर_get_stat(ssअगर, stat) \
	((अचिन्हित पूर्णांक) atomic_पढ़ो(&(ssअगर)->stats[SSIF_STAT_ ## stat]))

अटल bool initialized;
अटल bool platक्रमm_रेजिस्टरed;

अटल व्योम वापस_hosed_msg(काष्ठा ssअगर_info *ssअगर_info,
			     काष्ठा ipmi_smi_msg *msg);
अटल व्योम start_next_msg(काष्ठा ssअगर_info *ssअगर_info, अचिन्हित दीर्घ *flags);
अटल पूर्णांक start_send(काष्ठा ssअगर_info *ssअगर_info,
		      अचिन्हित अक्षर   *data,
		      अचिन्हित पूर्णांक    len);

अटल अचिन्हित दीर्घ *ipmi_ssअगर_lock_cond(काष्ठा ssअगर_info *ssअगर_info,
					  अचिन्हित दीर्घ *flags)
	__acquires(&ssअगर_info->lock)
अणु
	spin_lock_irqsave(&ssअगर_info->lock, *flags);
	वापस flags;
पूर्ण

अटल व्योम ipmi_ssअगर_unlock_cond(काष्ठा ssअगर_info *ssअगर_info,
				  अचिन्हित दीर्घ *flags)
	__releases(&ssअगर_info->lock)
अणु
	spin_unlock_irqrestore(&ssअगर_info->lock, *flags);
पूर्ण

अटल व्योम deliver_recv_msg(काष्ठा ssअगर_info *ssअगर_info,
			     काष्ठा ipmi_smi_msg *msg)
अणु
	अगर (msg->rsp_size < 0) अणु
		वापस_hosed_msg(ssअगर_info, msg);
		dev_err(&ssअगर_info->client->dev,
			"%s: Malformed message: rsp_size = %d\n",
		       __func__, msg->rsp_size);
	पूर्ण अन्यथा अणु
		ipmi_smi_msg_received(ssअगर_info->पूर्णांकf, msg);
	पूर्ण
पूर्ण

अटल व्योम वापस_hosed_msg(काष्ठा ssअगर_info *ssअगर_info,
			     काष्ठा ipmi_smi_msg *msg)
अणु
	ssअगर_inc_stat(ssअगर_info, hosed);

	/* Make it a response */
	msg->rsp[0] = msg->data[0] | 4;
	msg->rsp[1] = msg->data[1];
	msg->rsp[2] = 0xFF; /* Unknown error. */
	msg->rsp_size = 3;

	deliver_recv_msg(ssअगर_info, msg);
पूर्ण

/*
 * Must be called with the message lock held.  This will release the
 * message lock.  Note that the caller will check SSIF_IDLE and start a
 * new operation, so there is no need to check क्रम new messages to
 * start in here.
 */
अटल व्योम start_clear_flags(काष्ठा ssअगर_info *ssअगर_info, अचिन्हित दीर्घ *flags)
अणु
	अचिन्हित अक्षर msg[3];

	ssअगर_info->msg_flags &= ~WDT_PRE_TIMEOUT_INT;
	ssअगर_info->ssअगर_state = SSIF_CLEARING_FLAGS;
	ipmi_ssअगर_unlock_cond(ssअगर_info, flags);

	/* Make sure the watchकरोg pre-समयout flag is not set at startup. */
	msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg[1] = IPMI_CLEAR_MSG_FLAGS_CMD;
	msg[2] = WDT_PRE_TIMEOUT_INT;

	अगर (start_send(ssअगर_info, msg, 3) != 0) अणु
		/* Error, just go to normal state. */
		ssअगर_info->ssअगर_state = SSIF_NORMAL;
	पूर्ण
पूर्ण

अटल व्योम start_flag_fetch(काष्ठा ssअगर_info *ssअगर_info, अचिन्हित दीर्घ *flags)
अणु
	अचिन्हित अक्षर mb[2];

	ssअगर_info->req_flags = false;
	ssअगर_info->ssअगर_state = SSIF_GETTING_FLAGS;
	ipmi_ssअगर_unlock_cond(ssअगर_info, flags);

	mb[0] = (IPMI_NETFN_APP_REQUEST << 2);
	mb[1] = IPMI_GET_MSG_FLAGS_CMD;
	अगर (start_send(ssअगर_info, mb, 2) != 0)
		ssअगर_info->ssअगर_state = SSIF_NORMAL;
पूर्ण

अटल व्योम check_start_send(काष्ठा ssअगर_info *ssअगर_info, अचिन्हित दीर्घ *flags,
			     काष्ठा ipmi_smi_msg *msg)
अणु
	अगर (start_send(ssअगर_info, msg->data, msg->data_size) != 0) अणु
		अचिन्हित दीर्घ oflags;

		flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
		ssअगर_info->curr_msg = शून्य;
		ssअगर_info->ssअगर_state = SSIF_NORMAL;
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
		ipmi_मुक्त_smi_msg(msg);
	पूर्ण
पूर्ण

अटल व्योम start_event_fetch(काष्ठा ssअगर_info *ssअगर_info, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ipmi_smi_msg *msg;

	ssअगर_info->req_events = false;

	msg = ipmi_alloc_smi_msg();
	अगर (!msg) अणु
		ssअगर_info->ssअगर_state = SSIF_NORMAL;
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
		वापस;
	पूर्ण

	ssअगर_info->curr_msg = msg;
	ssअगर_info->ssअगर_state = SSIF_GETTING_EVENTS;
	ipmi_ssअगर_unlock_cond(ssअगर_info, flags);

	msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg->data[1] = IPMI_READ_EVENT_MSG_BUFFER_CMD;
	msg->data_size = 2;

	check_start_send(ssअगर_info, flags, msg);
पूर्ण

अटल व्योम start_recv_msg_fetch(काष्ठा ssअगर_info *ssअगर_info,
				 अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ipmi_smi_msg *msg;

	msg = ipmi_alloc_smi_msg();
	अगर (!msg) अणु
		ssअगर_info->ssअगर_state = SSIF_NORMAL;
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
		वापस;
	पूर्ण

	ssअगर_info->curr_msg = msg;
	ssअगर_info->ssअगर_state = SSIF_GETTING_MESSAGES;
	ipmi_ssअगर_unlock_cond(ssअगर_info, flags);

	msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg->data[1] = IPMI_GET_MSG_CMD;
	msg->data_size = 2;

	check_start_send(ssअगर_info, flags, msg);
पूर्ण

/*
 * Must be called with the message lock held.  This will release the
 * message lock.  Note that the caller will check SSIF_IDLE and start a
 * new operation, so there is no need to check क्रम new messages to
 * start in here.
 */
अटल व्योम handle_flags(काष्ठा ssअगर_info *ssअगर_info, अचिन्हित दीर्घ *flags)
अणु
	अगर (ssअगर_info->msg_flags & WDT_PRE_TIMEOUT_INT) अणु
		/* Watchकरोg pre-समयout */
		ssअगर_inc_stat(ssअगर_info, watchकरोg_preसमयouts);
		start_clear_flags(ssअगर_info, flags);
		ipmi_smi_watchकरोg_preसमयout(ssअगर_info->पूर्णांकf);
	पूर्ण अन्यथा अगर (ssअगर_info->msg_flags & RECEIVE_MSG_AVAIL)
		/* Messages available. */
		start_recv_msg_fetch(ssअगर_info, flags);
	अन्यथा अगर (ssअगर_info->msg_flags & EVENT_MSG_BUFFER_FULL)
		/* Events available. */
		start_event_fetch(ssअगर_info, flags);
	अन्यथा अणु
		ssअगर_info->ssअगर_state = SSIF_NORMAL;
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक ipmi_ssअगर_thपढ़ो(व्योम *data)
अणु
	काष्ठा ssअगर_info *ssअगर_info = data;

	जबतक (!kthपढ़ो_should_stop()) अणु
		पूर्णांक result;

		/* Wait क्रम something to करो */
		result = रुको_क्रम_completion_पूर्णांकerruptible(
						&ssअगर_info->wake_thपढ़ो);
		अगर (ssअगर_info->stopping)
			अवरोध;
		अगर (result == -ERESTARTSYS)
			जारी;
		init_completion(&ssअगर_info->wake_thपढ़ो);

		अगर (ssअगर_info->i2c_पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			result = i2c_smbus_ग_लिखो_block_data(
				ssअगर_info->client, ssअगर_info->i2c_command,
				ssअगर_info->i2c_data[0],
				ssअगर_info->i2c_data + 1);
			ssअगर_info->करोne_handler(ssअगर_info, result, शून्य, 0);
		पूर्ण अन्यथा अणु
			result = i2c_smbus_पढ़ो_block_data(
				ssअगर_info->client, ssअगर_info->i2c_command,
				ssअगर_info->i2c_data);
			अगर (result < 0)
				ssअगर_info->करोne_handler(ssअगर_info, result,
							शून्य, 0);
			अन्यथा
				ssअगर_info->करोne_handler(ssअगर_info, 0,
							ssअगर_info->i2c_data,
							result);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ssअगर_i2c_send(काष्ठा ssअगर_info *ssअगर_info,
			ssअगर_i2c_करोne handler,
			पूर्णांक पढ़ो_ग_लिखो, पूर्णांक command,
			अचिन्हित अक्षर *data, अचिन्हित पूर्णांक size)
अणु
	ssअगर_info->करोne_handler = handler;

	ssअगर_info->i2c_पढ़ो_ग_लिखो = पढ़ो_ग_लिखो;
	ssअगर_info->i2c_command = command;
	ssअगर_info->i2c_data = data;
	ssअगर_info->i2c_size = size;
	complete(&ssअगर_info->wake_thपढ़ो);
पूर्ण


अटल व्योम msg_करोne_handler(काष्ठा ssअगर_info *ssअगर_info, पूर्णांक result,
			     अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len);

अटल व्योम start_get(काष्ठा ssअगर_info *ssअगर_info)
अणु
	ssअगर_info->rtc_us_समयr = 0;
	ssअगर_info->multi_pos = 0;

	ssअगर_i2c_send(ssअगर_info, msg_करोne_handler, I2C_SMBUS_READ,
		  SSIF_IPMI_RESPONSE,
		  ssअगर_info->recv, I2C_SMBUS_BLOCK_DATA);
पूर्ण

अटल व्योम retry_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ssअगर_info *ssअगर_info = from_समयr(ssअगर_info, t, retry_समयr);
	अचिन्हित दीर्घ oflags, *flags;
	bool रुकोing;

	अगर (ssअगर_info->stopping)
		वापस;

	flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
	रुकोing = ssअगर_info->रुकोing_alert;
	ssअगर_info->रुकोing_alert = false;
	ipmi_ssअगर_unlock_cond(ssअगर_info, flags);

	अगर (रुकोing)
		start_get(ssअगर_info);
पूर्ण

अटल व्योम watch_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा ssअगर_info *ssअगर_info = from_समयr(ssअगर_info, t, watch_समयr);
	अचिन्हित दीर्घ oflags, *flags;

	अगर (ssअगर_info->stopping)
		वापस;

	flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
	अगर (ssअगर_info->watch_समयout) अणु
		mod_समयr(&ssअगर_info->watch_समयr,
			  jअगरfies + ssअगर_info->watch_समयout);
		अगर (SSIF_IDLE(ssअगर_info)) अणु
			start_flag_fetch(ssअगर_info, flags); /* Releases lock */
			वापस;
		पूर्ण
		ssअगर_info->req_flags = true;
	पूर्ण
	ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
पूर्ण

अटल व्योम ssअगर_alert(काष्ठा i2c_client *client, क्रमागत i2c_alert_protocol type,
		       अचिन्हित पूर्णांक data)
अणु
	काष्ठा ssअगर_info *ssअगर_info = i2c_get_clientdata(client);
	अचिन्हित दीर्घ oflags, *flags;
	bool करो_get = false;

	अगर (type != I2C_PROTOCOL_SMBUS_ALERT)
		वापस;

	ssअगर_inc_stat(ssअगर_info, alerts);

	flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
	अगर (ssअगर_info->रुकोing_alert) अणु
		ssअगर_info->रुकोing_alert = false;
		del_समयr(&ssअगर_info->retry_समयr);
		करो_get = true;
	पूर्ण अन्यथा अगर (ssअगर_info->curr_msg) अणु
		ssअगर_info->got_alert = true;
	पूर्ण
	ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
	अगर (करो_get)
		start_get(ssअगर_info);
पूर्ण

अटल पूर्णांक start_resend(काष्ठा ssअगर_info *ssअगर_info);

अटल व्योम msg_करोne_handler(काष्ठा ssअगर_info *ssअगर_info, पूर्णांक result,
			     अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ipmi_smi_msg *msg;
	अचिन्हित दीर्घ oflags, *flags;

	/*
	 * We are single-thपढ़ोed here, so no need क्रम a lock until we
	 * start messing with driver states or the queues.
	 */

	अगर (result < 0) अणु
		ssअगर_info->retries_left--;
		अगर (ssअगर_info->retries_left > 0) अणु
			ssअगर_inc_stat(ssअगर_info, receive_retries);

			flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
			ssअगर_info->रुकोing_alert = true;
			ssअगर_info->rtc_us_समयr = SSIF_MSG_USEC;
			अगर (!ssअगर_info->stopping)
				mod_समयr(&ssअगर_info->retry_समयr,
					  jअगरfies + SSIF_MSG_JIFFIES);
			ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
			वापस;
		पूर्ण

		ssअगर_inc_stat(ssअगर_info, receive_errors);

		अगर  (ssअगर_info->ssअगर_debug & SSIF_DEBUG_MSG)
			dev_dbg(&ssअगर_info->client->dev,
				"%s: Error %d\n", __func__, result);
		len = 0;
		जाओ जारी_op;
	पूर्ण

	अगर ((len > 1) && (ssअगर_info->multi_pos == 0)
				&& (data[0] == 0x00) && (data[1] == 0x01)) अणु
		/* Start of multi-part पढ़ो.  Start the next transaction. */
		पूर्णांक i;

		ssअगर_inc_stat(ssअगर_info, received_message_parts);

		/* Remove the multi-part पढ़ो marker. */
		len -= 2;
		data += 2;
		क्रम (i = 0; i < len; i++)
			ssअगर_info->data[i] = data[i];
		ssअगर_info->multi_len = len;
		ssअगर_info->multi_pos = 1;

		ssअगर_i2c_send(ssअगर_info, msg_करोne_handler, I2C_SMBUS_READ,
			 SSIF_IPMI_MULTI_PART_RESPONSE_MIDDLE,
			 ssअगर_info->recv, I2C_SMBUS_BLOCK_DATA);
		वापस;
	पूर्ण अन्यथा अगर (ssअगर_info->multi_pos) अणु
		/* Middle of multi-part पढ़ो.  Start the next transaction. */
		पूर्णांक i;
		अचिन्हित अक्षर blocknum;

		अगर (len == 0) अणु
			result = -EIO;
			अगर (ssअगर_info->ssअगर_debug & SSIF_DEBUG_MSG)
				dev_dbg(&ssअगर_info->client->dev,
					"Middle message with no data\n");

			जाओ जारी_op;
		पूर्ण

		blocknum = data[0];
		len--;
		data++;

		अगर (blocknum != 0xff && len != 31) अणु
		    /* All blocks but the last must have 31 data bytes. */
			result = -EIO;
			अगर (ssअगर_info->ssअगर_debug & SSIF_DEBUG_MSG)
				dev_dbg(&ssअगर_info->client->dev,
					"Received middle message <31\n");

			जाओ जारी_op;
		पूर्ण

		अगर (ssअगर_info->multi_len + len > IPMI_MAX_MSG_LENGTH) अणु
			/* Received message too big, पात the operation. */
			result = -E2BIG;
			अगर (ssअगर_info->ssअगर_debug & SSIF_DEBUG_MSG)
				dev_dbg(&ssअगर_info->client->dev,
					"Received message too big\n");

			जाओ जारी_op;
		पूर्ण

		क्रम (i = 0; i < len; i++)
			ssअगर_info->data[i + ssअगर_info->multi_len] = data[i];
		ssअगर_info->multi_len += len;
		अगर (blocknum == 0xff) अणु
			/* End of पढ़ो */
			len = ssअगर_info->multi_len;
			data = ssअगर_info->data;
		पूर्ण अन्यथा अगर (blocknum + 1 != ssअगर_info->multi_pos) अणु
			/*
			 * Out of sequence block, just पात.  Block
			 * numbers start at zero क्रम the second block,
			 * but multi_pos starts at one, so the +1.
			 */
			अगर (ssअगर_info->ssअगर_debug & SSIF_DEBUG_MSG)
				dev_dbg(&ssअगर_info->client->dev,
					"Received message out of sequence, expected %u, got %u\n",
					ssअगर_info->multi_pos - 1, blocknum);
			result = -EIO;
		पूर्ण अन्यथा अणु
			ssअगर_inc_stat(ssअगर_info, received_message_parts);

			ssअगर_info->multi_pos++;

			ssअगर_i2c_send(ssअगर_info, msg_करोne_handler,
				  I2C_SMBUS_READ,
				  SSIF_IPMI_MULTI_PART_RESPONSE_MIDDLE,
				  ssअगर_info->recv,
				  I2C_SMBUS_BLOCK_DATA);
			वापस;
		पूर्ण
	पूर्ण

 जारी_op:
	अगर (result < 0) अणु
		ssअगर_inc_stat(ssअगर_info, receive_errors);
	पूर्ण अन्यथा अणु
		ssअगर_inc_stat(ssअगर_info, received_messages);
		ssअगर_inc_stat(ssअगर_info, received_message_parts);
	पूर्ण

	अगर (ssअगर_info->ssअगर_debug & SSIF_DEBUG_STATE)
		dev_dbg(&ssअगर_info->client->dev,
			"DONE 1: state = %d, result=%d\n",
			ssअगर_info->ssअगर_state, result);

	flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
	msg = ssअगर_info->curr_msg;
	अगर (msg) अणु
		अगर (data) अणु
			अगर (len > IPMI_MAX_MSG_LENGTH)
				len = IPMI_MAX_MSG_LENGTH;
			स_नकल(msg->rsp, data, len);
		पूर्ण अन्यथा अणु
			len = 0;
		पूर्ण
		msg->rsp_size = len;
		ssअगर_info->curr_msg = शून्य;
	पूर्ण

	चयन (ssअगर_info->ssअगर_state) अणु
	हाल SSIF_NORMAL:
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
		अगर (!msg)
			अवरोध;

		अगर (result < 0)
			वापस_hosed_msg(ssअगर_info, msg);
		अन्यथा
			deliver_recv_msg(ssअगर_info, msg);
		अवरोध;

	हाल SSIF_GETTING_FLAGS:
		/* We got the flags from the SSIF, now handle them. */
		अगर ((result < 0) || (len < 4) || (data[2] != 0)) अणु
			/*
			 * Error fetching flags, or invalid length,
			 * just give up क्रम now.
			 */
			ssअगर_info->ssअगर_state = SSIF_NORMAL;
			ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
			dev_warn(&ssअगर_info->client->dev,
				 "Error getting flags: %d %d, %x\n",
				 result, len, (len >= 3) ? data[2] : 0);
		पूर्ण अन्यथा अगर (data[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2
			   || data[1] != IPMI_GET_MSG_FLAGS_CMD) अणु
			/*
			 * Don't पात here, maybe it was a queued
			 * response to a previous command.
			 */
			ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
			dev_warn(&ssअगर_info->client->dev,
				 "Invalid response getting flags: %x %x\n",
				 data[0], data[1]);
		पूर्ण अन्यथा अणु
			ssअगर_inc_stat(ssअगर_info, flag_fetches);
			ssअगर_info->msg_flags = data[3];
			handle_flags(ssअगर_info, flags);
		पूर्ण
		अवरोध;

	हाल SSIF_CLEARING_FLAGS:
		/* We cleared the flags. */
		अगर ((result < 0) || (len < 3) || (data[2] != 0)) अणु
			/* Error clearing flags */
			dev_warn(&ssअगर_info->client->dev,
				 "Error clearing flags: %d %d, %x\n",
				 result, len, (len >= 3) ? data[2] : 0);
		पूर्ण अन्यथा अगर (data[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2
			   || data[1] != IPMI_CLEAR_MSG_FLAGS_CMD) अणु
			dev_warn(&ssअगर_info->client->dev,
				 "Invalid response clearing flags: %x %x\n",
				 data[0], data[1]);
		पूर्ण
		ssअगर_info->ssअगर_state = SSIF_NORMAL;
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
		अवरोध;

	हाल SSIF_GETTING_EVENTS:
		अगर ((result < 0) || (len < 3) || (msg->rsp[2] != 0)) अणु
			/* Error getting event, probably करोne. */
			msg->करोne(msg);

			/* Take off the event flag. */
			ssअगर_info->msg_flags &= ~EVENT_MSG_BUFFER_FULL;
			handle_flags(ssअगर_info, flags);
		पूर्ण अन्यथा अगर (msg->rsp[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2
			   || msg->rsp[1] != IPMI_READ_EVENT_MSG_BUFFER_CMD) अणु
			dev_warn(&ssअगर_info->client->dev,
				 "Invalid response getting events: %x %x\n",
				 msg->rsp[0], msg->rsp[1]);
			msg->करोne(msg);
			/* Take off the event flag. */
			ssअगर_info->msg_flags &= ~EVENT_MSG_BUFFER_FULL;
			handle_flags(ssअगर_info, flags);
		पूर्ण अन्यथा अणु
			handle_flags(ssअगर_info, flags);
			ssअगर_inc_stat(ssअगर_info, events);
			deliver_recv_msg(ssअगर_info, msg);
		पूर्ण
		अवरोध;

	हाल SSIF_GETTING_MESSAGES:
		अगर ((result < 0) || (len < 3) || (msg->rsp[2] != 0)) अणु
			/* Error getting event, probably करोne. */
			msg->करोne(msg);

			/* Take off the msg flag. */
			ssअगर_info->msg_flags &= ~RECEIVE_MSG_AVAIL;
			handle_flags(ssअगर_info, flags);
		पूर्ण अन्यथा अगर (msg->rsp[0] != (IPMI_NETFN_APP_REQUEST | 1) << 2
			   || msg->rsp[1] != IPMI_GET_MSG_CMD) अणु
			dev_warn(&ssअगर_info->client->dev,
				 "Invalid response clearing flags: %x %x\n",
				 msg->rsp[0], msg->rsp[1]);
			msg->करोne(msg);

			/* Take off the msg flag. */
			ssअगर_info->msg_flags &= ~RECEIVE_MSG_AVAIL;
			handle_flags(ssअगर_info, flags);
		पूर्ण अन्यथा अणु
			ssअगर_inc_stat(ssअगर_info, incoming_messages);
			handle_flags(ssअगर_info, flags);
			deliver_recv_msg(ssअगर_info, msg);
		पूर्ण
		अवरोध;
	पूर्ण

	flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
	अगर (SSIF_IDLE(ssअगर_info) && !ssअगर_info->stopping) अणु
		अगर (ssअगर_info->req_events)
			start_event_fetch(ssअगर_info, flags);
		अन्यथा अगर (ssअगर_info->req_flags)
			start_flag_fetch(ssअगर_info, flags);
		अन्यथा
			start_next_msg(ssअगर_info, flags);
	पूर्ण अन्यथा
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);

	अगर (ssअगर_info->ssअगर_debug & SSIF_DEBUG_STATE)
		dev_dbg(&ssअगर_info->client->dev,
			"DONE 2: state = %d.\n", ssअगर_info->ssअगर_state);
पूर्ण

अटल व्योम msg_written_handler(काष्ठा ssअगर_info *ssअगर_info, पूर्णांक result,
				अचिन्हित अक्षर *data, अचिन्हित पूर्णांक len)
अणु
	/* We are single-thपढ़ोed here, so no need क्रम a lock. */
	अगर (result < 0) अणु
		ssअगर_info->retries_left--;
		अगर (ssअगर_info->retries_left > 0) अणु
			अगर (!start_resend(ssअगर_info)) अणु
				ssअगर_inc_stat(ssअगर_info, send_retries);
				वापस;
			पूर्ण
			/* request failed, just वापस the error. */
			ssअगर_inc_stat(ssअगर_info, send_errors);

			अगर (ssअगर_info->ssअगर_debug & SSIF_DEBUG_MSG)
				dev_dbg(&ssअगर_info->client->dev,
					"%s: Out of retries\n", __func__);
			msg_करोne_handler(ssअगर_info, -EIO, शून्य, 0);
			वापस;
		पूर्ण

		ssअगर_inc_stat(ssअगर_info, send_errors);

		/*
		 * Got an error on transmit, let the करोne routine
		 * handle it.
		 */
		अगर (ssअगर_info->ssअगर_debug & SSIF_DEBUG_MSG)
			dev_dbg(&ssअगर_info->client->dev,
				"%s: Error  %d\n", __func__, result);

		msg_करोne_handler(ssअगर_info, result, शून्य, 0);
		वापस;
	पूर्ण

	अगर (ssअगर_info->multi_data) अणु
		/*
		 * In the middle of a multi-data ग_लिखो.  See the comment
		 * in the SSIF_MULTI_n_PART हाल in the probe function
		 * क्रम details on the पूर्णांकricacies of this.
		 */
		पूर्णांक left, to_ग_लिखो;
		अचिन्हित अक्षर *data_to_send;
		अचिन्हित अक्षर cmd;

		ssअगर_inc_stat(ssअगर_info, sent_messages_parts);

		left = ssअगर_info->multi_len - ssअगर_info->multi_pos;
		to_ग_लिखो = left;
		अगर (to_ग_लिखो > 32)
			to_ग_लिखो = 32;
		/* Length byte. */
		ssअगर_info->multi_data[ssअगर_info->multi_pos] = to_ग_लिखो;
		data_to_send = ssअगर_info->multi_data + ssअगर_info->multi_pos;
		ssअगर_info->multi_pos += to_ग_लिखो;
		cmd = SSIF_IPMI_MULTI_PART_REQUEST_MIDDLE;
		अगर (ssअगर_info->cmd8_works) अणु
			अगर (left == to_ग_लिखो) अणु
				cmd = SSIF_IPMI_MULTI_PART_REQUEST_END;
				ssअगर_info->multi_data = शून्य;
			पूर्ण
		पूर्ण अन्यथा अगर (to_ग_लिखो < 32) अणु
			ssअगर_info->multi_data = शून्य;
		पूर्ण

		ssअगर_i2c_send(ssअगर_info, msg_written_handler,
			  I2C_SMBUS_WRITE, cmd,
			  data_to_send, I2C_SMBUS_BLOCK_DATA);
	पूर्ण अन्यथा अणु
		/* Ready to request the result. */
		अचिन्हित दीर्घ oflags, *flags;

		ssअगर_inc_stat(ssअगर_info, sent_messages);
		ssअगर_inc_stat(ssअगर_info, sent_messages_parts);

		flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
		अगर (ssअगर_info->got_alert) अणु
			/* The result is alपढ़ोy पढ़ोy, just start it. */
			ssअगर_info->got_alert = false;
			ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
			start_get(ssअगर_info);
		पूर्ण अन्यथा अणु
			/* Wait a jअगरfie then request the next message */
			ssअगर_info->रुकोing_alert = true;
			ssअगर_info->retries_left = SSIF_RECV_RETRIES;
			ssअगर_info->rtc_us_समयr = SSIF_MSG_PART_USEC;
			अगर (!ssअगर_info->stopping)
				mod_समयr(&ssअगर_info->retry_समयr,
					  jअगरfies + SSIF_MSG_PART_JIFFIES);
			ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक start_resend(काष्ठा ssअगर_info *ssअगर_info)
अणु
	पूर्णांक command;

	ssअगर_info->got_alert = false;

	अगर (ssअगर_info->data_len > 32) अणु
		command = SSIF_IPMI_MULTI_PART_REQUEST_START;
		ssअगर_info->multi_data = ssअगर_info->data;
		ssअगर_info->multi_len = ssअगर_info->data_len;
		/*
		 * Subtle thing, this is 32, not 33, because we will
		 * overग_लिखो the thing at position 32 (which was just
		 * transmitted) with the new length.
		 */
		ssअगर_info->multi_pos = 32;
		ssअगर_info->data[0] = 32;
	पूर्ण अन्यथा अणु
		ssअगर_info->multi_data = शून्य;
		command = SSIF_IPMI_REQUEST;
		ssअगर_info->data[0] = ssअगर_info->data_len;
	पूर्ण

	ssअगर_i2c_send(ssअगर_info, msg_written_handler, I2C_SMBUS_WRITE,
		   command, ssअगर_info->data, I2C_SMBUS_BLOCK_DATA);
	वापस 0;
पूर्ण

अटल पूर्णांक start_send(काष्ठा ssअगर_info *ssअगर_info,
		      अचिन्हित अक्षर   *data,
		      अचिन्हित पूर्णांक    len)
अणु
	अगर (len > IPMI_MAX_MSG_LENGTH)
		वापस -E2BIG;
	अगर (len > ssअगर_info->max_xmit_msg_size)
		वापस -E2BIG;

	ssअगर_info->retries_left = SSIF_SEND_RETRIES;
	स_नकल(ssअगर_info->data + 1, data, len);
	ssअगर_info->data_len = len;
	वापस start_resend(ssअगर_info);
पूर्ण

/* Must be called with the message lock held. */
अटल व्योम start_next_msg(काष्ठा ssअगर_info *ssअगर_info, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा ipmi_smi_msg *msg;
	अचिन्हित दीर्घ oflags;

 restart:
	अगर (!SSIF_IDLE(ssअगर_info)) अणु
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
		वापस;
	पूर्ण

	अगर (!ssअगर_info->रुकोing_msg) अणु
		ssअगर_info->curr_msg = शून्य;
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
	पूर्ण अन्यथा अणु
		पूर्णांक rv;

		ssअगर_info->curr_msg = ssअगर_info->रुकोing_msg;
		ssअगर_info->रुकोing_msg = शून्य;
		ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
		rv = start_send(ssअगर_info,
				ssअगर_info->curr_msg->data,
				ssअगर_info->curr_msg->data_size);
		अगर (rv) अणु
			msg = ssअगर_info->curr_msg;
			ssअगर_info->curr_msg = शून्य;
			वापस_hosed_msg(ssअगर_info, msg);
			flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
			जाओ restart;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sender(व्योम                *send_info,
		   काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा ssअगर_info *ssअगर_info = (काष्ठा ssअगर_info *) send_info;
	अचिन्हित दीर्घ oflags, *flags;

	BUG_ON(ssअगर_info->रुकोing_msg);
	ssअगर_info->रुकोing_msg = msg;

	flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
	start_next_msg(ssअगर_info, flags);

	अगर (ssअगर_info->ssअगर_debug & SSIF_DEBUG_TIMING) अणु
		काष्ठा बारpec64 t;

		kसमय_get_real_ts64(&t);
		dev_dbg(&ssअगर_info->client->dev,
			"**Enqueue %02x %02x: %lld.%6.6ld\n",
			msg->data[0], msg->data[1],
			(दीर्घ दीर्घ)t.tv_sec, (दीर्घ)t.tv_nsec / NSEC_PER_USEC);
	पूर्ण
पूर्ण

अटल पूर्णांक get_smi_info(व्योम *send_info, काष्ठा ipmi_smi_info *data)
अणु
	काष्ठा ssअगर_info *ssअगर_info = send_info;

	data->addr_src = ssअगर_info->addr_source;
	data->dev = &ssअगर_info->client->dev;
	data->addr_info = ssअगर_info->addr_info;
	get_device(data->dev);

	वापस 0;
पूर्ण

/*
 * Upper layer wants us to request events.
 */
अटल व्योम request_events(व्योम *send_info)
अणु
	काष्ठा ssअगर_info *ssअगर_info = (काष्ठा ssअगर_info *) send_info;
	अचिन्हित दीर्घ oflags, *flags;

	अगर (!ssअगर_info->has_event_buffer)
		वापस;

	flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
	ssअगर_info->req_events = true;
	ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
पूर्ण

/*
 * Upper layer is changing the flag saying whether we need to request
 * flags periodically or not.
 */
अटल व्योम ssअगर_set_need_watch(व्योम *send_info, अचिन्हित पूर्णांक watch_mask)
अणु
	काष्ठा ssअगर_info *ssअगर_info = (काष्ठा ssअगर_info *) send_info;
	अचिन्हित दीर्घ oflags, *flags;
	दीर्घ समयout = 0;

	अगर (watch_mask & IPMI_WATCH_MASK_CHECK_MESSAGES)
		समयout = SSIF_WATCH_MSG_TIMEOUT;
	अन्यथा अगर (watch_mask)
		समयout = SSIF_WATCH_WATCHDOG_TIMEOUT;

	flags = ipmi_ssअगर_lock_cond(ssअगर_info, &oflags);
	अगर (समयout != ssअगर_info->watch_समयout) अणु
		ssअगर_info->watch_समयout = समयout;
		अगर (ssअगर_info->watch_समयout)
			mod_समयr(&ssअगर_info->watch_समयr,
				  jअगरfies + ssअगर_info->watch_समयout);
	पूर्ण
	ipmi_ssअगर_unlock_cond(ssअगर_info, flags);
पूर्ण

अटल पूर्णांक ssअगर_start_processing(व्योम            *send_info,
				 काष्ठा ipmi_smi *पूर्णांकf)
अणु
	काष्ठा ssअगर_info *ssअगर_info = send_info;

	ssअगर_info->पूर्णांकf = पूर्णांकf;

	वापस 0;
पूर्ण

#घोषणा MAX_SSIF_BMCS 4

अटल अचिन्हित लघु addr[MAX_SSIF_BMCS];
अटल पूर्णांक num_addrs;
module_param_array(addr, uलघु, &num_addrs, 0);
MODULE_PARM_DESC(addr, "The addresses to scan for IPMI BMCs on the SSIFs.");

अटल अक्षर *adapter_name[MAX_SSIF_BMCS];
अटल पूर्णांक num_adapter_names;
module_param_array(adapter_name, अक्षरp, &num_adapter_names, 0);
MODULE_PARM_DESC(adapter_name, "The string name of the I2C device that has the BMC.  By default all devices are scanned.");

अटल पूर्णांक slave_addrs[MAX_SSIF_BMCS];
अटल पूर्णांक num_slave_addrs;
module_param_array(slave_addrs, पूर्णांक, &num_slave_addrs, 0);
MODULE_PARM_DESC(slave_addrs,
		 "The default IPMB slave address for the controller.");

अटल bool alerts_broken;
module_param(alerts_broken, bool, 0);
MODULE_PARM_DESC(alerts_broken, "Don't enable alerts for the controller.");

/*
 * Bit 0 enables message debugging, bit 1 enables state debugging, and
 * bit 2 enables timing debugging.  This is an array indexed by
 * पूर्णांकerface number"
 */
अटल पूर्णांक dbg[MAX_SSIF_BMCS];
अटल पूर्णांक num_dbg;
module_param_array(dbg, पूर्णांक, &num_dbg, 0);
MODULE_PARM_DESC(dbg, "Turn on debugging.");

अटल bool ssअगर_dbg_probe;
module_param_named(dbg_probe, ssअगर_dbg_probe, bool, 0);
MODULE_PARM_DESC(dbg_probe, "Enable debugging of probing of adapters.");

अटल bool ssअगर_tryacpi = true;
module_param_named(tryacpi, ssअगर_tryacpi, bool, 0);
MODULE_PARM_DESC(tryacpi, "Setting this to zero will disable the default scan of the interfaces identified via ACPI");

अटल bool ssअगर_trydmi = true;
module_param_named(trydmi, ssअगर_trydmi, bool, 0);
MODULE_PARM_DESC(trydmi, "Setting this to zero will disable the default scan of the interfaces identified via DMI (SMBIOS)");

अटल DEFINE_MUTEX(ssअगर_infos_mutex);
अटल LIST_HEAD(ssअगर_infos);

#घोषणा IPMI_SSIF_ATTR(name) \
अटल sमाप_प्रकार ipmi_##name##_show(काष्ठा device *dev,			\
				  काष्ठा device_attribute *attr,	\
				  अक्षर *buf)				\
अणु									\
	काष्ठा ssअगर_info *ssअगर_info = dev_get_drvdata(dev);		\
									\
	वापस snम_लिखो(buf, 10, "%u\n", ssअगर_get_stat(ssअगर_info, name));\
पूर्ण									\
अटल DEVICE_ATTR(name, S_IRUGO, ipmi_##name##_show, शून्य)

अटल sमाप_प्रकार ipmi_type_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस snम_लिखो(buf, 10, "ssif\n");
पूर्ण
अटल DEVICE_ATTR(type, S_IRUGO, ipmi_type_show, शून्य);

IPMI_SSIF_ATTR(sent_messages);
IPMI_SSIF_ATTR(sent_messages_parts);
IPMI_SSIF_ATTR(send_retries);
IPMI_SSIF_ATTR(send_errors);
IPMI_SSIF_ATTR(received_messages);
IPMI_SSIF_ATTR(received_message_parts);
IPMI_SSIF_ATTR(receive_retries);
IPMI_SSIF_ATTR(receive_errors);
IPMI_SSIF_ATTR(flag_fetches);
IPMI_SSIF_ATTR(hosed);
IPMI_SSIF_ATTR(events);
IPMI_SSIF_ATTR(watchकरोg_preसमयouts);
IPMI_SSIF_ATTR(alerts);

अटल काष्ठा attribute *ipmi_ssअगर_dev_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_sent_messages.attr,
	&dev_attr_sent_messages_parts.attr,
	&dev_attr_send_retries.attr,
	&dev_attr_send_errors.attr,
	&dev_attr_received_messages.attr,
	&dev_attr_received_message_parts.attr,
	&dev_attr_receive_retries.attr,
	&dev_attr_receive_errors.attr,
	&dev_attr_flag_fetches.attr,
	&dev_attr_hosed.attr,
	&dev_attr_events.attr,
	&dev_attr_watchकरोg_preसमयouts.attr,
	&dev_attr_alerts.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ipmi_ssअगर_dev_attr_group = अणु
	.attrs		= ipmi_ssअगर_dev_attrs,
पूर्ण;

अटल व्योम shutकरोwn_ssअगर(व्योम *send_info)
अणु
	काष्ठा ssअगर_info *ssअगर_info = send_info;

	device_हटाओ_group(&ssअगर_info->client->dev, &ipmi_ssअगर_dev_attr_group);
	dev_set_drvdata(&ssअगर_info->client->dev, शून्य);

	/* make sure the driver is not looking क्रम flags any more. */
	जबतक (ssअगर_info->ssअगर_state != SSIF_NORMAL)
		schedule_समयout(1);

	ssअगर_info->stopping = true;
	del_समयr_sync(&ssअगर_info->watch_समयr);
	del_समयr_sync(&ssअगर_info->retry_समयr);
	अगर (ssअगर_info->thपढ़ो) अणु
		complete(&ssअगर_info->wake_thपढ़ो);
		kthपढ़ो_stop(ssअगर_info->thपढ़ो);
	पूर्ण
पूर्ण

अटल पूर्णांक ssअगर_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ssअगर_info *ssअगर_info = i2c_get_clientdata(client);
	काष्ठा ssअगर_addr_info *addr_info;

	अगर (!ssअगर_info)
		वापस 0;

	/*
	 * After this poपूर्णांक, we won't deliver anything asychronously
	 * to the message handler.  We can unरेजिस्टर ourself.
	 */
	ipmi_unरेजिस्टर_smi(ssअगर_info->पूर्णांकf);

	list_क्रम_each_entry(addr_info, &ssअगर_infos, link) अणु
		अगर (addr_info->client == client) अणु
			addr_info->client = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(ssअगर_info);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_response(काष्ठा i2c_client *client, अचिन्हित अक्षर *resp)
अणु
	पूर्णांक ret = -ENODEV, retry_cnt = SSIF_RECV_RETRIES;

	जबतक (retry_cnt > 0) अणु
		ret = i2c_smbus_पढ़ो_block_data(client, SSIF_IPMI_RESPONSE,
						resp);
		अगर (ret > 0)
			अवरोध;
		msleep(SSIF_MSG_MSEC);
		retry_cnt--;
		अगर (retry_cnt <= 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक करो_cmd(काष्ठा i2c_client *client, पूर्णांक len, अचिन्हित अक्षर *msg,
		  पूर्णांक *resp_len, अचिन्हित अक्षर *resp)
अणु
	पूर्णांक retry_cnt;
	पूर्णांक ret;

	retry_cnt = SSIF_SEND_RETRIES;
 retry1:
	ret = i2c_smbus_ग_लिखो_block_data(client, SSIF_IPMI_REQUEST, len, msg);
	अगर (ret) अणु
		retry_cnt--;
		अगर (retry_cnt > 0)
			जाओ retry1;
		वापस -ENODEV;
	पूर्ण

	ret = पढ़ो_response(client, resp);
	अगर (ret > 0) अणु
		/* Validate that the response is correct. */
		अगर (ret < 3 ||
		    (resp[0] != (msg[0] | (1 << 2))) ||
		    (resp[1] != msg[1]))
			ret = -EINVAL;
		अन्यथा अगर (ret > IPMI_MAX_MSG_LENGTH) अणु
			ret = -E2BIG;
		पूर्ण अन्यथा अणु
			*resp_len = ret;
			ret = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ssअगर_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	अचिन्हित अक्षर *resp;
	अचिन्हित अक्षर msg[3];
	पूर्णांक           rv;
	पूर्णांक           len;

	resp = kदो_स्मृति(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	अगर (!resp)
		वापस -ENOMEM;

	/* Do a Get Device ID command, since it is required. */
	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_DEVICE_ID_CMD;
	rv = करो_cmd(client, 2, msg, &len, resp);
	अगर (rv)
		rv = -ENODEV;
	अन्यथा
		strlcpy(info->type, DEVICE_NAME, I2C_NAME_SIZE);
	kमुक्त(resp);
	वापस rv;
पूर्ण

अटल पूर्णांक म_भेद_nospace(अक्षर *s1, अक्षर *s2)
अणु
	जबतक (*s1 && *s2) अणु
		जबतक (है_खाली(*s1))
			s1++;
		जबतक (है_खाली(*s2))
			s2++;
		अगर (*s1 > *s2)
			वापस 1;
		अगर (*s1 < *s2)
			वापस -1;
		s1++;
		s2++;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ssअगर_addr_info *ssअगर_info_find(अचिन्हित लघु addr,
					     अक्षर *adapter_name,
					     bool match_null_name)
अणु
	काष्ठा ssअगर_addr_info *info, *found = शून्य;

restart:
	list_क्रम_each_entry(info, &ssअगर_infos, link) अणु
		अगर (info->binfo.addr == addr) अणु
			अगर (info->addr_src == SI_SMBIOS)
				info->adapter_name = kstrdup(adapter_name,
							     GFP_KERNEL);

			अगर (info->adapter_name || adapter_name) अणु
				अगर (!info->adapter_name != !adapter_name) अणु
					/* One is शून्य and one is not */
					जारी;
				पूर्ण
				अगर (adapter_name &&
				    म_भेद_nospace(info->adapter_name,
						   adapter_name))
					/* Names करो not match */
					जारी;
			पूर्ण
			found = info;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found && match_null_name) अणु
		/* Try to get an exact match first, then try with a शून्य name */
		adapter_name = शून्य;
		match_null_name = false;
		जाओ restart;
	पूर्ण

	वापस found;
पूर्ण

अटल bool check_acpi(काष्ठा ssअगर_info *ssअगर_info, काष्ठा device *dev)
अणु
#अगर_घोषित CONFIG_ACPI
	acpi_handle acpi_handle;

	acpi_handle = ACPI_HANDLE(dev);
	अगर (acpi_handle) अणु
		ssअगर_info->addr_source = SI_ACPI;
		ssअगर_info->addr_info.acpi_info.acpi_handle = acpi_handle;
		request_module("acpi_ipmi");
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल पूर्णांक find_slave_address(काष्ठा i2c_client *client, पूर्णांक slave_addr)
अणु
#अगर_घोषित CONFIG_IPMI_DMI_DECODE
	अगर (!slave_addr)
		slave_addr = ipmi_dmi_get_slave_addr(
			SI_TYPE_INVALID,
			i2c_adapter_id(client->adapter),
			client->addr);
#पूर्ण_अगर

	वापस slave_addr;
पूर्ण

अटल पूर्णांक start_multipart_test(काष्ठा i2c_client *client,
				अचिन्हित अक्षर *msg, bool करो_middle)
अणु
	पूर्णांक retry_cnt = SSIF_SEND_RETRIES, ret;

retry_ग_लिखो:
	ret = i2c_smbus_ग_लिखो_block_data(client,
					 SSIF_IPMI_MULTI_PART_REQUEST_START,
					 32, msg);
	अगर (ret) अणु
		retry_cnt--;
		अगर (retry_cnt > 0)
			जाओ retry_ग_लिखो;
		dev_err(&client->dev, "Could not write multi-part start, though the BMC said it could handle it.  Just limit sends to one part.\n");
		वापस ret;
	पूर्ण

	अगर (!करो_middle)
		वापस 0;

	ret = i2c_smbus_ग_लिखो_block_data(client,
					 SSIF_IPMI_MULTI_PART_REQUEST_MIDDLE,
					 32, msg + 32);
	अगर (ret) अणु
		dev_err(&client->dev, "Could not write multi-part middle, though the BMC said it could handle it.  Just limit sends to one part.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम test_multipart_messages(काष्ठा i2c_client *client,
				    काष्ठा ssअगर_info *ssअगर_info,
				    अचिन्हित अक्षर *resp)
अणु
	अचिन्हित अक्षर msg[65];
	पूर्णांक ret;
	bool करो_middle;

	अगर (ssअगर_info->max_xmit_msg_size <= 32)
		वापस;

	करो_middle = ssअगर_info->max_xmit_msg_size > 63;

	स_रखो(msg, 0, माप(msg));
	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_DEVICE_ID_CMD;

	/*
	 * The specअगरication is all messed up dealing with sending
	 * multi-part messages.  Per what the specअगरication says, it
	 * is impossible to send a message that is a multiple of 32
	 * bytes, except क्रम 32 itself.  It talks about a "start"
	 * transaction (cmd=6) that must be 32 bytes, "middle"
	 * transaction (cmd=7) that must be 32 bytes, and an "end"
	 * transaction.  The "end" transaction is shown as cmd=7 in
	 * the text, but अगर that's the हाल there is no way to
	 * dअगरferentiate between a middle and end part except the
	 * length being less than 32.  But there is a table at the far
	 * end of the section (that I had never noticed until someone
	 * poपूर्णांकed it out to me) that mentions it as cmd=8.
	 *
	 * After some thought, I think the example is wrong and the
	 * end transaction should be cmd=8.  But some प्रणालीs करोn't
	 * implement cmd=8, they use a zero-length end transaction,
	 * even though that violates the SMBus specअगरication.
	 *
	 * So, to work around this, this code tests अगर cmd=8 works.
	 * If it करोes, then we use that.  If not, it tests zero-
	 * byte end transactions.  If that works, good.  If not,
	 * we only allow 63-byte transactions max.
	 */

	ret = start_multipart_test(client, msg, करो_middle);
	अगर (ret)
		जाओ out_no_multi_part;

	ret = i2c_smbus_ग_लिखो_block_data(client,
					 SSIF_IPMI_MULTI_PART_REQUEST_END,
					 1, msg + 64);

	अगर (!ret)
		ret = पढ़ो_response(client, resp);

	अगर (ret > 0) अणु
		/* End transactions work, we are good. */
		ssअगर_info->cmd8_works = true;
		वापस;
	पूर्ण

	ret = start_multipart_test(client, msg, करो_middle);
	अगर (ret) अणु
		dev_err(&client->dev, "Second multipart test failed.\n");
		जाओ out_no_multi_part;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_block_data(client,
					 SSIF_IPMI_MULTI_PART_REQUEST_MIDDLE,
					 0, msg + 64);
	अगर (!ret)
		ret = पढ़ो_response(client, resp);
	अगर (ret > 0)
		/* Zero-size end parts work, use those. */
		वापस;

	/* Limit to 63 bytes and use a लघु middle command to mark the end. */
	अगर (ssअगर_info->max_xmit_msg_size > 63)
		ssअगर_info->max_xmit_msg_size = 63;
	वापस;

out_no_multi_part:
	ssअगर_info->max_xmit_msg_size = 32;
	वापस;
पूर्ण

/*
 * Global enables we care about.
 */
#घोषणा GLOBAL_ENABLES_MASK (IPMI_BMC_EVT_MSG_BUFF | IPMI_BMC_RCV_MSG_INTR | \
			     IPMI_BMC_EVT_MSG_INTR)

अटल व्योम ssअगर_हटाओ_dup(काष्ठा i2c_client *client)
अणु
	काष्ठा ssअगर_info *ssअगर_info = i2c_get_clientdata(client);

	ipmi_unरेजिस्टर_smi(ssअगर_info->पूर्णांकf);
	kमुक्त(ssअगर_info);
पूर्ण

अटल पूर्णांक ssअगर_add_infos(काष्ठा i2c_client *client)
अणु
	काष्ठा ssअगर_addr_info *info;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->addr_src = SI_ACPI;
	info->client = client;
	info->adapter_name = kstrdup(client->adapter->name, GFP_KERNEL);
	info->binfo.addr = client->addr;
	list_add_tail(&info->link, &ssअगर_infos);
	वापस 0;
पूर्ण

/*
 * Prefer ACPI over SMBIOS, अगर both are available.
 * So अगर we get an ACPI पूर्णांकerface and have alपढ़ोy रेजिस्टरed a SMBIOS
 * पूर्णांकerface at the same address, हटाओ the SMBIOS and add the ACPI one.
 */
अटल पूर्णांक ssअगर_check_and_हटाओ(काष्ठा i2c_client *client,
			      काष्ठा ssअगर_info *ssअगर_info)
अणु
	काष्ठा ssअगर_addr_info *info;

	list_क्रम_each_entry(info, &ssअगर_infos, link) अणु
		अगर (!info->client)
			वापस 0;
		अगर (!म_भेद(info->adapter_name, client->adapter->name) &&
		    info->binfo.addr == client->addr) अणु
			अगर (info->addr_src == SI_ACPI)
				वापस -EEXIST;

			अगर (ssअगर_info->addr_source == SI_ACPI &&
			    info->addr_src == SI_SMBIOS) अणु
				dev_info(&client->dev,
					 "Removing %s-specified SSIF interface in favor of ACPI\n",
					 ipmi_addr_src_to_str(info->addr_src));
				ssअगर_हटाओ_dup(info->client);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ssअगर_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	अचिन्हित अक्षर     msg[3];
	अचिन्हित अक्षर     *resp;
	काष्ठा ssअगर_info   *ssअगर_info;
	पूर्णांक               rv = 0;
	पूर्णांक               len;
	पूर्णांक               i;
	u8		  slave_addr = 0;
	काष्ठा ssअगर_addr_info *addr_info = शून्य;

	mutex_lock(&ssअगर_infos_mutex);
	resp = kदो_स्मृति(IPMI_MAX_MSG_LENGTH, GFP_KERNEL);
	अगर (!resp) अणु
		mutex_unlock(&ssअगर_infos_mutex);
		वापस -ENOMEM;
	पूर्ण

	ssअगर_info = kzalloc(माप(*ssअगर_info), GFP_KERNEL);
	अगर (!ssअगर_info) अणु
		kमुक्त(resp);
		mutex_unlock(&ssअगर_infos_mutex);
		वापस -ENOMEM;
	पूर्ण

	अगर (!check_acpi(ssअगर_info, &client->dev)) अणु
		addr_info = ssअगर_info_find(client->addr, client->adapter->name,
					   true);
		अगर (!addr_info) अणु
			/* Must have come in through sysfs. */
			ssअगर_info->addr_source = SI_HOTMOD;
		पूर्ण अन्यथा अणु
			ssअगर_info->addr_source = addr_info->addr_src;
			ssअगर_info->ssअगर_debug = addr_info->debug;
			ssअगर_info->addr_info = addr_info->addr_info;
			addr_info->client = client;
			slave_addr = addr_info->slave_addr;
		पूर्ण
	पूर्ण

	rv = ssअगर_check_and_हटाओ(client, ssअगर_info);
	/* If rv is 0 and addr source is not SI_ACPI, जारी probing */
	अगर (!rv && ssअगर_info->addr_source == SI_ACPI) अणु
		rv = ssअगर_add_infos(client);
		अगर (rv) अणु
			dev_err(&client->dev, "Out of memory!, exiting ..\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (rv) अणु
		dev_err(&client->dev, "Not probing, Interface already present\n");
		जाओ out;
	पूर्ण

	slave_addr = find_slave_address(client, slave_addr);

	dev_info(&client->dev,
		 "Trying %s-specified SSIF interface at i2c address 0x%x, adapter %s, slave address 0x%x\n",
		ipmi_addr_src_to_str(ssअगर_info->addr_source),
		client->addr, client->adapter->name, slave_addr);

	ssअगर_info->client = client;
	i2c_set_clientdata(client, ssअगर_info);

	/* Now check क्रम प्रणाली पूर्णांकerface capabilities */
	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_SYSTEM_INTERFACE_CAPABILITIES_CMD;
	msg[2] = 0; /* SSIF */
	rv = करो_cmd(client, 3, msg, &len, resp);
	अगर (!rv && (len >= 3) && (resp[2] == 0)) अणु
		अगर (len < 7) अणु
			अगर (ssअगर_dbg_probe)
				dev_dbg(&ssअगर_info->client->dev,
					"SSIF info too short: %d\n", len);
			जाओ no_support;
		पूर्ण

		/* Got a good SSIF response, handle it. */
		ssअगर_info->max_xmit_msg_size = resp[5];
		ssअगर_info->max_recv_msg_size = resp[6];
		ssअगर_info->multi_support = (resp[4] >> 6) & 0x3;
		ssअगर_info->supports_pec = (resp[4] >> 3) & 0x1;

		/* Sanitize the data */
		चयन (ssअगर_info->multi_support) अणु
		हाल SSIF_NO_MULTI:
			अगर (ssअगर_info->max_xmit_msg_size > 32)
				ssअगर_info->max_xmit_msg_size = 32;
			अगर (ssअगर_info->max_recv_msg_size > 32)
				ssअगर_info->max_recv_msg_size = 32;
			अवरोध;

		हाल SSIF_MULTI_2_PART:
			अगर (ssअगर_info->max_xmit_msg_size > 63)
				ssअगर_info->max_xmit_msg_size = 63;
			अगर (ssअगर_info->max_recv_msg_size > 62)
				ssअगर_info->max_recv_msg_size = 62;
			अवरोध;

		हाल SSIF_MULTI_n_PART:
			/* We take whatever size given, but करो some testing. */
			अवरोध;

		शेष:
			/* Data is not sane, just give up. */
			जाओ no_support;
		पूर्ण
	पूर्ण अन्यथा अणु
 no_support:
		/* Assume no multi-part or PEC support */
		dev_info(&ssअगर_info->client->dev,
			 "Error fetching SSIF: %d %d %2.2x, your system probably doesn't support this command so using defaults\n",
			rv, len, resp[2]);

		ssअगर_info->max_xmit_msg_size = 32;
		ssअगर_info->max_recv_msg_size = 32;
		ssअगर_info->multi_support = SSIF_NO_MULTI;
		ssअगर_info->supports_pec = 0;
	पूर्ण

	test_multipart_messages(client, ssअगर_info, resp);

	/* Make sure the NMI समयout is cleared. */
	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_CLEAR_MSG_FLAGS_CMD;
	msg[2] = WDT_PRE_TIMEOUT_INT;
	rv = करो_cmd(client, 3, msg, &len, resp);
	अगर (rv || (len < 3) || (resp[2] != 0))
		dev_warn(&ssअगर_info->client->dev,
			 "Unable to clear message flags: %d %d %2.2x\n",
			 rv, len, resp[2]);

	/* Attempt to enable the event buffer. */
	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_GET_BMC_GLOBAL_ENABLES_CMD;
	rv = करो_cmd(client, 2, msg, &len, resp);
	अगर (rv || (len < 4) || (resp[2] != 0)) अणु
		dev_warn(&ssअगर_info->client->dev,
			 "Error getting global enables: %d %d %2.2x\n",
			 rv, len, resp[2]);
		rv = 0; /* Not fatal */
		जाओ found;
	पूर्ण

	ssअगर_info->global_enables = resp[3];

	अगर (resp[3] & IPMI_BMC_EVT_MSG_BUFF) अणु
		ssअगर_info->has_event_buffer = true;
		/* buffer is alपढ़ोy enabled, nothing to करो. */
		जाओ found;
	पूर्ण

	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_SET_BMC_GLOBAL_ENABLES_CMD;
	msg[2] = ssअगर_info->global_enables | IPMI_BMC_EVT_MSG_BUFF;
	rv = करो_cmd(client, 3, msg, &len, resp);
	अगर (rv || (len < 2)) अणु
		dev_warn(&ssअगर_info->client->dev,
			 "Error setting global enables: %d %d %2.2x\n",
			 rv, len, resp[2]);
		rv = 0; /* Not fatal */
		जाओ found;
	पूर्ण

	अगर (resp[2] == 0) अणु
		/* A successful वापस means the event buffer is supported. */
		ssअगर_info->has_event_buffer = true;
		ssअगर_info->global_enables |= IPMI_BMC_EVT_MSG_BUFF;
	पूर्ण

	/* Some प्रणालीs करोn't behave well अगर you enable alerts. */
	अगर (alerts_broken)
		जाओ found;

	msg[0] = IPMI_NETFN_APP_REQUEST << 2;
	msg[1] = IPMI_SET_BMC_GLOBAL_ENABLES_CMD;
	msg[2] = ssअगर_info->global_enables | IPMI_BMC_RCV_MSG_INTR;
	rv = करो_cmd(client, 3, msg, &len, resp);
	अगर (rv || (len < 2)) अणु
		dev_warn(&ssअगर_info->client->dev,
			 "Error setting global enables: %d %d %2.2x\n",
			 rv, len, resp[2]);
		rv = 0; /* Not fatal */
		जाओ found;
	पूर्ण

	अगर (resp[2] == 0) अणु
		/* A successful वापस means the alert is supported. */
		ssअगर_info->supports_alert = true;
		ssअगर_info->global_enables |= IPMI_BMC_RCV_MSG_INTR;
	पूर्ण

 found:
	अगर (ssअगर_dbg_probe) अणु
		dev_dbg(&ssअगर_info->client->dev,
		       "%s: i2c_probe found device at i2c address %x\n",
		       __func__, client->addr);
	पूर्ण

	spin_lock_init(&ssअगर_info->lock);
	ssअगर_info->ssअगर_state = SSIF_NORMAL;
	समयr_setup(&ssअगर_info->retry_समयr, retry_समयout, 0);
	समयr_setup(&ssअगर_info->watch_समयr, watch_समयout, 0);

	क्रम (i = 0; i < SSIF_NUM_STATS; i++)
		atomic_set(&ssअगर_info->stats[i], 0);

	अगर (ssअगर_info->supports_pec)
		ssअगर_info->client->flags |= I2C_CLIENT_PEC;

	ssअगर_info->handlers.owner = THIS_MODULE;
	ssअगर_info->handlers.start_processing = ssअगर_start_processing;
	ssअगर_info->handlers.shutकरोwn = shutकरोwn_ssअगर;
	ssअगर_info->handlers.get_smi_info = get_smi_info;
	ssअगर_info->handlers.sender = sender;
	ssअगर_info->handlers.request_events = request_events;
	ssअगर_info->handlers.set_need_watch = ssअगर_set_need_watch;

	अणु
		अचिन्हित पूर्णांक thपढ़ो_num;

		thपढ़ो_num = ((i2c_adapter_id(ssअगर_info->client->adapter)
			       << 8) |
			      ssअगर_info->client->addr);
		init_completion(&ssअगर_info->wake_thपढ़ो);
		ssअगर_info->thपढ़ो = kthपढ़ो_run(ipmi_ssअगर_thपढ़ो, ssअगर_info,
					       "kssif%4.4x", thपढ़ो_num);
		अगर (IS_ERR(ssअगर_info->thपढ़ो)) अणु
			rv = PTR_ERR(ssअगर_info->thपढ़ो);
			dev_notice(&ssअगर_info->client->dev,
				   "Could not start kernel thread: error %d\n",
				   rv);
			जाओ out;
		पूर्ण
	पूर्ण

	dev_set_drvdata(&ssअगर_info->client->dev, ssअगर_info);
	rv = device_add_group(&ssअगर_info->client->dev,
			      &ipmi_ssअगर_dev_attr_group);
	अगर (rv) अणु
		dev_err(&ssअगर_info->client->dev,
			"Unable to add device attributes: error %d\n",
			rv);
		जाओ out;
	पूर्ण

	rv = ipmi_रेजिस्टर_smi(&ssअगर_info->handlers,
			       ssअगर_info,
			       &ssअगर_info->client->dev,
			       slave_addr);
	अगर (rv) अणु
		dev_err(&ssअगर_info->client->dev,
			"Unable to register device: error %d\n", rv);
		जाओ out_हटाओ_attr;
	पूर्ण

 out:
	अगर (rv) अणु
		अगर (addr_info)
			addr_info->client = शून्य;

		dev_err(&ssअगर_info->client->dev,
			"Unable to start IPMI SSIF: %d\n", rv);
		kमुक्त(ssअगर_info);
	पूर्ण
	kमुक्त(resp);
	mutex_unlock(&ssअगर_infos_mutex);
	वापस rv;

out_हटाओ_attr:
	device_हटाओ_group(&ssअगर_info->client->dev, &ipmi_ssअगर_dev_attr_group);
	dev_set_drvdata(&ssअगर_info->client->dev, शून्य);
	जाओ out;
पूर्ण

अटल पूर्णांक new_ssअगर_client(पूर्णांक addr, अक्षर *adapter_name,
			   पूर्णांक debug, पूर्णांक slave_addr,
			   क्रमागत ipmi_addr_src addr_src,
			   काष्ठा device *dev)
अणु
	काष्ठा ssअगर_addr_info *addr_info;
	पूर्णांक rv = 0;

	mutex_lock(&ssअगर_infos_mutex);
	अगर (ssअगर_info_find(addr, adapter_name, false)) अणु
		rv = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	addr_info = kzalloc(माप(*addr_info), GFP_KERNEL);
	अगर (!addr_info) अणु
		rv = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	अगर (adapter_name) अणु
		addr_info->adapter_name = kstrdup(adapter_name, GFP_KERNEL);
		अगर (!addr_info->adapter_name) अणु
			kमुक्त(addr_info);
			rv = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	म_नकलन(addr_info->binfo.type, DEVICE_NAME,
		माप(addr_info->binfo.type));
	addr_info->binfo.addr = addr;
	addr_info->binfo.platक्रमm_data = addr_info;
	addr_info->debug = debug;
	addr_info->slave_addr = slave_addr;
	addr_info->addr_src = addr_src;
	addr_info->dev = dev;

	अगर (dev)
		dev_set_drvdata(dev, addr_info);

	list_add_tail(&addr_info->link, &ssअगर_infos);

	/* Address list will get it */

out_unlock:
	mutex_unlock(&ssअगर_infos_mutex);
	वापस rv;
पूर्ण

अटल व्योम मुक्त_ssअगर_clients(व्योम)
अणु
	काष्ठा ssअगर_addr_info *info, *पंचांगp;

	mutex_lock(&ssअगर_infos_mutex);
	list_क्रम_each_entry_safe(info, पंचांगp, &ssअगर_infos, link) अणु
		list_del(&info->link);
		kमुक्त(info->adapter_name);
		kमुक्त(info);
	पूर्ण
	mutex_unlock(&ssअगर_infos_mutex);
पूर्ण

अटल अचिन्हित लघु *ssअगर_address_list(व्योम)
अणु
	काष्ठा ssअगर_addr_info *info;
	अचिन्हित पूर्णांक count = 0, i = 0;
	अचिन्हित लघु *address_list;

	list_क्रम_each_entry(info, &ssअगर_infos, link)
		count++;

	address_list = kसुस्मृति(count + 1, माप(*address_list),
			       GFP_KERNEL);
	अगर (!address_list)
		वापस शून्य;

	list_क्रम_each_entry(info, &ssअगर_infos, link) अणु
		अचिन्हित लघु addr = info->binfo.addr;
		पूर्णांक j;

		क्रम (j = 0; j < i; j++) अणु
			अगर (address_list[j] == addr)
				/* Found a dup. */
				अवरोध;
		पूर्ण
		अगर (j == i) /* Didn't find it in the list. */
			address_list[i++] = addr;
	पूर्ण
	address_list[i] = I2C_CLIENT_END;

	वापस address_list;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id ssअगर_acpi_match[] = अणु
	अणु "IPI0001", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ssअगर_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DMI
अटल पूर्णांक dmi_ipmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u8 slave_addr = 0;
	u16 i2c_addr;
	पूर्णांक rv;

	अगर (!ssअगर_trydmi)
		वापस -ENODEV;

	rv = device_property_पढ़ो_u16(&pdev->dev, "i2c-addr", &i2c_addr);
	अगर (rv) अणु
		dev_warn(&pdev->dev, "No i2c-addr property\n");
		वापस -ENODEV;
	पूर्ण

	rv = device_property_पढ़ो_u8(&pdev->dev, "slave-addr", &slave_addr);
	अगर (rv)
		slave_addr = 0x20;

	वापस new_ssअगर_client(i2c_addr, शून्य, 0,
			       slave_addr, SI_SMBIOS, &pdev->dev);
पूर्ण
#अन्यथा
अटल पूर्णांक dmi_ipmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id ssअगर_id[] = अणु
	अणु DEVICE_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ssअगर_id);

अटल काष्ठा i2c_driver ssअगर_i2c_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver		= अणु
		.name			= DEVICE_NAME
	पूर्ण,
	.probe		= ssअगर_probe,
	.हटाओ		= ssअगर_हटाओ,
	.alert		= ssअगर_alert,
	.id_table	= ssअगर_id,
	.detect		= ssअगर_detect
पूर्ण;

अटल पूर्णांक ssअगर_platक्रमm_probe(काष्ठा platक्रमm_device *dev)
अणु
	वापस dmi_ipmi_probe(dev);
पूर्ण

अटल पूर्णांक ssअगर_platक्रमm_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ssअगर_addr_info *addr_info = dev_get_drvdata(&dev->dev);

	अगर (!addr_info)
		वापस 0;

	mutex_lock(&ssअगर_infos_mutex);
	list_del(&addr_info->link);
	kमुक्त(addr_info);
	mutex_unlock(&ssअगर_infos_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id ssअगर_plat_ids[] = अणु
    अणु "dmi-ipmi-ssif", 0 पूर्ण,
    अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ipmi_driver = अणु
	.driver = अणु
		.name = DEVICE_NAME,
	पूर्ण,
	.probe		= ssअगर_platक्रमm_probe,
	.हटाओ		= ssअगर_platक्रमm_हटाओ,
	.id_table       = ssअगर_plat_ids
पूर्ण;

अटल पूर्णांक init_ipmi_ssअगर(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक rv;

	अगर (initialized)
		वापस 0;

	pr_info("IPMI SSIF Interface driver\n");

	/* build list क्रम i2c from addr list */
	क्रम (i = 0; i < num_addrs; i++) अणु
		rv = new_ssअगर_client(addr[i], adapter_name[i],
				     dbg[i], slave_addrs[i],
				     SI_HARDCODED, शून्य);
		अगर (rv)
			pr_err("Couldn't add hardcoded device at addr 0x%x\n",
			       addr[i]);
	पूर्ण

	अगर (ssअगर_tryacpi)
		ssअगर_i2c_driver.driver.acpi_match_table	=
			ACPI_PTR(ssअगर_acpi_match);

	अगर (ssअगर_trydmi) अणु
		rv = platक्रमm_driver_रेजिस्टर(&ipmi_driver);
		अगर (rv)
			pr_err("Unable to register driver: %d\n", rv);
		अन्यथा
			platक्रमm_रेजिस्टरed = true;
	पूर्ण

	ssअगर_i2c_driver.address_list = ssअगर_address_list();

	rv = i2c_add_driver(&ssअगर_i2c_driver);
	अगर (!rv)
		initialized = true;

	वापस rv;
पूर्ण
module_init(init_ipmi_ssअगर);

अटल व्योम cleanup_ipmi_ssअगर(व्योम)
अणु
	अगर (!initialized)
		वापस;

	initialized = false;

	i2c_del_driver(&ssअगर_i2c_driver);

	kमुक्त(ssअगर_i2c_driver.address_list);

	अगर (ssअगर_trydmi && platक्रमm_रेजिस्टरed)
		platक्रमm_driver_unरेजिस्टर(&ipmi_driver);

	मुक्त_ssअगर_clients();
पूर्ण
module_निकास(cleanup_ipmi_ssअगर);

MODULE_ALIAS("platform:dmi-ipmi-ssif");
MODULE_AUTHOR("Todd C Davis <todd.c.davis@intel.com>, Corey Minyard <minyard@acm.org>");
MODULE_DESCRIPTION("IPMI driver for management controllers on a SMBus");
MODULE_LICENSE("GPL");
