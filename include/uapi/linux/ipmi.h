<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * ipmi.h
 *
 * MontaVista IPMI पूर्णांकerface
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 *
 */

#अगर_अघोषित _UAPI__LINUX_IPMI_H
#घोषणा _UAPI__LINUX_IPMI_H

#समावेश <linux/ipmi_msgdefs.h>
#समावेश <linux/compiler.h>

/*
 * This file describes an पूर्णांकerface to an IPMI driver.  You have to
 * have a fairly good understanding of IPMI to use this, so go पढ़ो
 * the specs first beक्रमe actually trying to करो anything.
 *
 * With that said, this driver provides a multi-user पूर्णांकerface to the
 * IPMI driver, and it allows multiple IPMI physical पूर्णांकerfaces below
 * the driver.  The physical पूर्णांकerfaces bind as a lower layer on the
 * driver.  They appear as पूर्णांकerfaces to the application using this
 * पूर्णांकerface.
 *
 * Multi-user means that multiple applications may use the driver,
 * send commands, receive responses, etc.  The driver keeps track of
 * commands the user sends and tracks the responses.  The responses
 * will go back to the application that send the command.  If the
 * response करोesn't come back in समय, the driver will वापस a
 * समयout error response to the application.  Asynchronous events
 * from the BMC event queue will go to all users bound to the driver.
 * The incoming event queue in the BMC will स्वतःmatically be flushed
 * अगर it becomes full and it is queried once a second to see अगर
 * anything is in it.  Incoming commands to the driver will get
 * delivered as commands.
 */

/*
 * This is an overlay क्रम all the address types, so it's easy to
 * determine the actual address type.  This is kind of like addresses
 * work क्रम sockets.
 */
#घोषणा IPMI_MAX_ADDR_SIZE 32
काष्ठा ipmi_addr अणु
	 /* Try to take these from the "Channel Medium Type" table
	    in section 6.5 of the IPMI 1.5 manual. */
	पूर्णांक   addr_type;
	लघु channel;
	अक्षर  data[IPMI_MAX_ADDR_SIZE];
पूर्ण;

/*
 * When the address is not used, the type will be set to this value.
 * The channel is the BMC's channel number क्रम the channel (usually
 * 0), or IPMC_BMC_CHANNEL अगर communicating directly with the BMC.
 */
#घोषणा IPMI_SYSTEM_INTERFACE_ADDR_TYPE	0x0c
काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr अणु
	पूर्णांक           addr_type;
	लघु         channel;
	अचिन्हित अक्षर lun;
पूर्ण;

/* An IPMB Address. */
#घोषणा IPMI_IPMB_ADDR_TYPE		0x01
/* Used क्रम broadcast get device id as described in section 17.9 of the
   IPMI 1.5 manual. */
#घोषणा IPMI_IPMB_BROADCAST_ADDR_TYPE	0x41
काष्ठा ipmi_ipmb_addr अणु
	पूर्णांक           addr_type;
	लघु         channel;
	अचिन्हित अक्षर slave_addr;
	अचिन्हित अक्षर lun;
पूर्ण;

/*
 * A LAN Address.  This is an address to/from a LAN पूर्णांकerface bridged
 * by the BMC, not an address actually out on the LAN.
 *
 * A conscious decision was made here to deviate slightly from the IPMI
 * spec.  We करो not use rqSWID and rsSWID like it shows in the
 * message.  Instead, we use remote_SWID and local_SWID.  This means
 * that any message (a request or response) from another device will
 * always have exactly the same address.  If you didn't करो this,
 * requests and responses from the same device would have dअगरferent
 * addresses, and that's not too cool.
 *
 * In this address, the remote_SWID is always the SWID the remote
 * message came from, or the SWID we are sending the message to.
 * local_SWID is always our SWID.  Note that having our SWID in the
 * message is a little weird, but this is required.
 */
#घोषणा IPMI_LAN_ADDR_TYPE		0x04
काष्ठा ipmi_lan_addr अणु
	पूर्णांक           addr_type;
	लघु         channel;
	अचिन्हित अक्षर privilege;
	अचिन्हित अक्षर session_handle;
	अचिन्हित अक्षर remote_SWID;
	अचिन्हित अक्षर local_SWID;
	अचिन्हित अक्षर lun;
पूर्ण;


/*
 * Channel क्रम talking directly with the BMC.  When using this
 * channel, This is क्रम the प्रणाली पूर्णांकerface address type only.  FIXME
 * - is this right, or should we use -1?
 */
#घोषणा IPMI_BMC_CHANNEL  0xf
#घोषणा IPMI_NUM_CHANNELS 0x10

/*
 * Used to signअगरy an "all channel" biपंचांगask.  This is more than the
 * actual number of channels because this is used in userland and
 * will cover us अगर the number of channels is extended.
 */
#घोषणा IPMI_CHAN_ALL     (~0)


/*
 * A raw IPMI message without any addressing.  This covers both
 * commands and responses.  The completion code is always the first
 * byte of data in the response (as the spec shows the messages laid
 * out).
 */
काष्ठा ipmi_msg अणु
	अचिन्हित अक्षर  netfn;
	अचिन्हित अक्षर  cmd;
	अचिन्हित लघु data_len;
	अचिन्हित अक्षर  __user *data;
पूर्ण;

काष्ठा kernel_ipmi_msg अणु
	अचिन्हित अक्षर  netfn;
	अचिन्हित अक्षर  cmd;
	अचिन्हित लघु data_len;
	अचिन्हित अक्षर  *data;
पूर्ण;

/*
 * Various defines that are useful क्रम IPMI applications.
 */
#घोषणा IPMI_INVALID_CMD_COMPLETION_CODE	0xC1
#घोषणा IPMI_TIMEOUT_COMPLETION_CODE		0xC3
#घोषणा IPMI_UNKNOWN_ERR_COMPLETION_CODE	0xff


/*
 * Receive types क्रम messages coming from the receive पूर्णांकerface.  This
 * is used क्रम the receive in-kernel पूर्णांकerface and in the receive
 * IOCTL.
 *
 * The "IPMI_RESPONSE_RESPNOSE_TYPE" is a little strange sounding, but
 * it allows you to get the message results when you send a response
 * message.
 */
#घोषणा IPMI_RESPONSE_RECV_TYPE		1 /* A response to a command */
#घोषणा IPMI_ASYNC_EVENT_RECV_TYPE	2 /* Something from the event queue */
#घोषणा IPMI_CMD_RECV_TYPE		3 /* A command from somewhere अन्यथा */
#घोषणा IPMI_RESPONSE_RESPONSE_TYPE	4 /* The response क्रम
					      a sent response, giving any
					      error status क्रम sending the
					      response.  When you send a
					      response message, this will
					      be वापसed. */
#घोषणा IPMI_OEM_RECV_TYPE		5 /* The response क्रम OEM Channels */

/* Note that async events and received commands करो not have a completion
   code as the first byte of the incoming data, unlike a response. */


/*
 * Modes क्रम ipmi_set_मुख्यt_mode() and the userland IOCTL.  The AUTO
 * setting is the शेष and means it will be set on certain
 * commands.  Hard setting it on and off will override स्वतःmatic
 * operation.
 */
#घोषणा IPMI_MAINTEन_अंकCE_MODE_AUTO	0
#घोषणा IPMI_MAINTEन_अंकCE_MODE_OFF	1
#घोषणा IPMI_MAINTEन_अंकCE_MODE_ON	2



/*
 * The userland पूर्णांकerface
 */

/*
 * The userland पूर्णांकerface क्रम the IPMI driver is a standard अक्षरacter
 * device, with each instance of an पूर्णांकerface रेजिस्टरed as a minor
 * number under the major अक्षरacter device.
 *
 * The पढ़ो and ग_लिखो calls करो not work, to get messages in and out
 * requires ioctl calls because of the complनिकासy of the data.  select
 * and poll करो work, so you can रुको क्रम input using the file
 * descriptor, you just can use पढ़ो to get it.
 *
 * In general, you send a command करोwn to the पूर्णांकerface and receive
 * responses back.  You can use the msgid value to correlate commands
 * and responses, the driver will take care of figuring out which
 * incoming messages are क्रम which command and find the proper msgid
 * value to report.  You will only receive reponses क्रम commands you
 * send.  Asynchronous events, however, go to all खोलो users, so you
 * must be पढ़ोy to handle these (or ignore them अगर you करोn't care).
 *
 * The address type depends upon the channel type.  When talking
 * directly to the BMC (IPMC_BMC_CHANNEL), the address is ignored
 * (IPMI_UNUSED_ADDR_TYPE).  When talking to an IPMB channel, you must
 * supply a valid IPMB address with the addr_type set properly.
 *
 * When talking to normal channels, the driver takes care of the
 * details of क्रमmatting and sending messages on that channel.  You करो
 * not, क्रम instance, have to क्रमmat a send command, you just send
 * whatever command you want to the channel, the driver will create
 * the send command, स्वतःmatically issue receive command and get even
 * commands, and pass those up to the proper user.
 */


/* The magic IOCTL value क्रम this पूर्णांकerface. */
#घोषणा IPMI_IOC_MAGIC 'i'


/* Messages sent to the पूर्णांकerface are this क्रमmat. */
काष्ठा ipmi_req अणु
	अचिन्हित अक्षर __user *addr; /* Address to send the message to. */
	अचिन्हित पूर्णांक  addr_len;

	दीर्घ    msgid; /* The sequence number क्रम the message.  This
			  exact value will be reported back in the
			  response to this request अगर it is a command.
			  If it is a response, this will be used as
			  the sequence value क्रम the response.  */

	काष्ठा ipmi_msg msg;
पूर्ण;
/*
 * Send a message to the पूर्णांकerfaces.  error values are:
 *   - EFAULT - an address supplied was invalid.
 *   - EINVAL - The address supplied was not valid, or the command
 *              was not allowed.
 *   - EMSGSIZE - The message to was too large.
 *   - ENOMEM - Buffers could not be allocated क्रम the command.
 */
#घोषणा IPMICTL_SEND_COMMAND		_IOR(IPMI_IOC_MAGIC, 13,	\
					     काष्ठा ipmi_req)

/* Messages sent to the पूर्णांकerface with timing parameters are this
   क्रमmat. */
काष्ठा ipmi_req_समय_रखो अणु
	काष्ठा ipmi_req req;

	/* See ipmi_request_समय_रखो() above क्रम details on these
	   values. */
	पूर्णांक          retries;
	अचिन्हित पूर्णांक retry_समय_ms;
पूर्ण;
/*
 * Send a message to the पूर्णांकerfaces with timing parameters.  error values
 * are:
 *   - EFAULT - an address supplied was invalid.
 *   - EINVAL - The address supplied was not valid, or the command
 *              was not allowed.
 *   - EMSGSIZE - The message to was too large.
 *   - ENOMEM - Buffers could not be allocated क्रम the command.
 */
#घोषणा IPMICTL_SEND_COMMAND_SETTIME	_IOR(IPMI_IOC_MAGIC, 21,	\
					     काष्ठा ipmi_req_समय_रखो)

/* Messages received from the पूर्णांकerface are this क्रमmat. */
काष्ठा ipmi_recv अणु
	पूर्णांक     recv_type; /* Is this a command, response or an
			      asyncronous event. */

	अचिन्हित अक्षर __user *addr;    /* Address the message was from is put
				   here.  The caller must supply the
				   memory. */
	अचिन्हित पूर्णांक  addr_len; /* The size of the address buffer.
				   The caller supplies the full buffer
				   length, this value is updated to
				   the actual message length when the
				   message is received. */

	दीर्घ    msgid; /* The sequence number specअगरied in the request
			  अगर this is a response.  If this is a command,
			  this will be the sequence number from the
			  command. */

	काष्ठा ipmi_msg msg; /* The data field must poपूर्णांक to a buffer.
				The data_size field must be set to the
				size of the message buffer.  The
				caller supplies the full buffer
				length, this value is updated to the
				actual message length when the message
				is received. */
पूर्ण;

/*
 * Receive a message.  error values:
 *  - EAGAIN - no messages in the queue.
 *  - EFAULT - an address supplied was invalid.
 *  - EINVAL - The address supplied was not valid.
 *  - EMSGSIZE - The message to was too large to fit पूर्णांकo the message buffer,
 *               the message will be left in the buffer. */
#घोषणा IPMICTL_RECEIVE_MSG		_IOWR(IPMI_IOC_MAGIC, 12,	\
					      काष्ठा ipmi_recv)

/*
 * Like RECEIVE_MSG, but अगर the message won't fit in the buffer, it
 * will truncate the contents instead of leaving the data in the
 * buffer.
 */
#घोषणा IPMICTL_RECEIVE_MSG_TRUNC	_IOWR(IPMI_IOC_MAGIC, 11,	\
					      काष्ठा ipmi_recv)

/* Register to get commands from other entities on this पूर्णांकerface. */
काष्ठा ipmi_cmdspec अणु
	अचिन्हित अक्षर netfn;
	अचिन्हित अक्षर cmd;
पूर्ण;

/*
 * Register to receive a specअगरic command.  error values:
 *   - EFAULT - an address supplied was invalid.
 *   - EBUSY - The netfn/cmd supplied was alपढ़ोy in use.
 *   - ENOMEM - could not allocate memory क्रम the entry.
 */
#घोषणा IPMICTL_REGISTER_FOR_CMD	_IOR(IPMI_IOC_MAGIC, 14,	\
					     काष्ठा ipmi_cmdspec)
/*
 * Unरेजिस्टर a रेजिस्टरed command.  error values:
 *  - EFAULT - an address supplied was invalid.
 *  - ENOENT - The netfn/cmd was not found रेजिस्टरed क्रम this user.
 */
#घोषणा IPMICTL_UNREGISTER_FOR_CMD	_IOR(IPMI_IOC_MAGIC, 15,	\
					     काष्ठा ipmi_cmdspec)

/*
 * Register to get commands from other entities on specअगरic channels.
 * This way, you can only listen on specअगरic channels, or have messages
 * from some channels go to one place and other channels to someplace
 * अन्यथा.  The chans field is a biपंचांगask, (1 << channel) क्रम each channel.
 * It may be IPMI_CHAN_ALL क्रम all channels.
 */
काष्ठा ipmi_cmdspec_chans अणु
	अचिन्हित पूर्णांक netfn;
	अचिन्हित पूर्णांक cmd;
	अचिन्हित पूर्णांक chans;
पूर्ण;

/*
 * Register to receive a specअगरic command on specअगरic channels.  error values:
 *   - EFAULT - an address supplied was invalid.
 *   - EBUSY - One of the netfn/cmd/chans supplied was alपढ़ोy in use.
 *   - ENOMEM - could not allocate memory क्रम the entry.
 */
#घोषणा IPMICTL_REGISTER_FOR_CMD_CHANS	_IOR(IPMI_IOC_MAGIC, 28,	\
					     काष्ठा ipmi_cmdspec_chans)
/*
 * Unरेजिस्टर some netfn/cmd/chans.  error values:
 *  - EFAULT - an address supplied was invalid.
 *  - ENOENT - None of the netfn/cmd/chans were found रेजिस्टरed क्रम this user.
 */
#घोषणा IPMICTL_UNREGISTER_FOR_CMD_CHANS _IOR(IPMI_IOC_MAGIC, 29,	\
					     काष्ठा ipmi_cmdspec_chans)

/*
 * Set whether this पूर्णांकerface receives events.  Note that the first
 * user रेजिस्टरed क्रम events will get all pending events क्रम the
 * पूर्णांकerface.  error values:
 *  - EFAULT - an address supplied was invalid.
 */
#घोषणा IPMICTL_SET_GETS_EVENTS_CMD	_IOR(IPMI_IOC_MAGIC, 16, पूर्णांक)

/*
 * Set and get the slave address and LUN that we will use क्रम our
 * source messages.  Note that this affects the पूर्णांकerface, not just
 * this user, so it will affect all users of this पूर्णांकerface.  This is
 * so some initialization code can come in and करो the OEM-specअगरic
 * things it takes to determine your address (अगर not the BMC) and set
 * it क्रम everyone अन्यथा.  You should probably leave the LUN alone.
 */
काष्ठा ipmi_channel_lun_address_set अणु
	अचिन्हित लघु channel;
	अचिन्हित अक्षर  value;
पूर्ण;
#घोषणा IPMICTL_SET_MY_CHANNEL_ADDRESS_CMD \
	_IOR(IPMI_IOC_MAGIC, 24, काष्ठा ipmi_channel_lun_address_set)
#घोषणा IPMICTL_GET_MY_CHANNEL_ADDRESS_CMD \
	_IOR(IPMI_IOC_MAGIC, 25, काष्ठा ipmi_channel_lun_address_set)
#घोषणा IPMICTL_SET_MY_CHANNEL_LUN_CMD \
	_IOR(IPMI_IOC_MAGIC, 26, काष्ठा ipmi_channel_lun_address_set)
#घोषणा IPMICTL_GET_MY_CHANNEL_LUN_CMD \
	_IOR(IPMI_IOC_MAGIC, 27, काष्ठा ipmi_channel_lun_address_set)
/* Legacy पूर्णांकerfaces, these only set IPMB 0. */
#घोषणा IPMICTL_SET_MY_ADDRESS_CMD	_IOR(IPMI_IOC_MAGIC, 17, अचिन्हित पूर्णांक)
#घोषणा IPMICTL_GET_MY_ADDRESS_CMD	_IOR(IPMI_IOC_MAGIC, 18, अचिन्हित पूर्णांक)
#घोषणा IPMICTL_SET_MY_LUN_CMD		_IOR(IPMI_IOC_MAGIC, 19, अचिन्हित पूर्णांक)
#घोषणा IPMICTL_GET_MY_LUN_CMD		_IOR(IPMI_IOC_MAGIC, 20, अचिन्हित पूर्णांक)

/*
 * Get/set the शेष timing values क्रम an पूर्णांकerface.  You shouldn't
 * generally mess with these.
 */
काष्ठा ipmi_timing_parms अणु
	पूर्णांक          retries;
	अचिन्हित पूर्णांक retry_समय_ms;
पूर्ण;
#घोषणा IPMICTL_SET_TIMING_PARMS_CMD	_IOR(IPMI_IOC_MAGIC, 22, \
					     काष्ठा ipmi_timing_parms)
#घोषणा IPMICTL_GET_TIMING_PARMS_CMD	_IOR(IPMI_IOC_MAGIC, 23, \
					     काष्ठा ipmi_timing_parms)

/*
 * Set the मुख्यtenance mode.  See ipmi_set_मुख्यtenance_mode() above
 * क्रम a description of what this करोes.
 */
#घोषणा IPMICTL_GET_MAINTEन_अंकCE_MODE_CMD	_IOR(IPMI_IOC_MAGIC, 30, पूर्णांक)
#घोषणा IPMICTL_SET_MAINTEन_अंकCE_MODE_CMD	_IOW(IPMI_IOC_MAGIC, 31, पूर्णांक)

#पूर्ण_अगर /* _UAPI__LINUX_IPMI_H */
