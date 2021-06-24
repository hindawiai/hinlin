<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
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
#अगर_अघोषित __LINUX_IPMI_H
#घोषणा __LINUX_IPMI_H

#समावेश <uapi/linux/ipmi.h>

#समावेश <linux/list.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/acpi.h> /* For acpi_handle */

काष्ठा module;
काष्ठा device;

/*
 * Opaque type क्रम a IPMI message user.  One of these is needed to
 * send and receive messages.
 */
काष्ठा ipmi_user;

/*
 * Stuff coming from the receive पूर्णांकerface comes as one of these.
 * They are allocated, the receiver must मुक्त them with
 * ipmi_मुक्त_recv_msg() when करोne with the message.  The link is not
 * used after the message is delivered, so the upper layer may use the
 * link to build a linked list, अगर it likes.
 */
काष्ठा ipmi_recv_msg अणु
	काष्ठा list_head link;

	/*
	 * The type of message as defined in the "Receive Types"
	 * defines above.
	 */
	पूर्णांक              recv_type;

	काष्ठा ipmi_user *user;
	काष्ठा ipmi_addr addr;
	दीर्घ             msgid;
	काष्ठा kernel_ipmi_msg  msg;

	/*
	 * The user_msg_data is the data supplied when a message was
	 * sent, अगर this is a response to a sent message.  If this is
	 * not a response to a sent message, then user_msg_data will
	 * be शून्य.  If the user above is शून्य, then this will be the
	 * पूर्णांकf.
	 */
	व्योम             *user_msg_data;

	/*
	 * Call this when करोne with the message.  It will presumably मुक्त
	 * the message and करो any other necessary cleanup.
	 */
	व्योम (*करोne)(काष्ठा ipmi_recv_msg *msg);

	/*
	 * Place-holder क्रम the data, करोn't make any assumptions about
	 * the size or existence of this, since it may change.
	 */
	अचिन्हित अक्षर   msg_data[IPMI_MAX_MSG_LENGTH];
पूर्ण;

/* Allocate and मुक्त the receive message. */
व्योम ipmi_मुक्त_recv_msg(काष्ठा ipmi_recv_msg *msg);

काष्ठा ipmi_user_hndl अणु
	/*
	 * Routine type to call when a message needs to be routed to
	 * the upper layer.  This will be called with some locks held,
	 * the only IPMI routines that can be called are ipmi_request
	 * and the alloc/मुक्त operations.  The handler_data is the
	 * variable supplied when the receive handler was रेजिस्टरed.
	 */
	व्योम (*ipmi_recv_hndl)(काष्ठा ipmi_recv_msg *msg,
			       व्योम                 *user_msg_data);

	/*
	 * Called when the पूर्णांकerface detects a watchकरोg pre-समयout.  If
	 * this is शून्य, it will be ignored क्रम the user.
	 */
	व्योम (*ipmi_watchकरोg_preसमयout)(व्योम *handler_data);

	/*
	 * If not शून्य, called at panic समय after the पूर्णांकerface has
	 * been set up to handle run to completion.
	 */
	व्योम (*ipmi_panic_handler)(व्योम *handler_data);

	/*
	 * Called when the पूर्णांकerface has been हटाओd.  After this वापसs
	 * the user handle will be invalid.  The पूर्णांकerface may or may
	 * not be usable when this is called, but it will वापस errors
	 * अगर it is not usable.
	 */
	व्योम (*shutकरोwn)(व्योम *handler_data);
पूर्ण;

/* Create a new user of the IPMI layer on the given पूर्णांकerface number. */
पूर्णांक ipmi_create_user(अचिन्हित पूर्णांक          अगर_num,
		     स्थिर काष्ठा ipmi_user_hndl *handler,
		     व्योम                  *handler_data,
		     काष्ठा ipmi_user      **user);

/*
 * Destroy the given user of the IPMI layer.  Note that after this
 * function वापसs, the प्रणाली is guaranteed to not call any
 * callbacks क्रम the user.  Thus as दीर्घ as you destroy all the users
 * beक्रमe you unload a module, you will be safe.  And अगर you destroy
 * the users beक्रमe you destroy the callback काष्ठाures, it should be
 * safe, too.
 */
पूर्णांक ipmi_destroy_user(काष्ठा ipmi_user *user);

/* Get the IPMI version of the BMC we are talking to. */
पूर्णांक ipmi_get_version(काष्ठा ipmi_user *user,
		     अचिन्हित अक्षर *major,
		     अचिन्हित अक्षर *minor);

/*
 * Set and get the slave address and LUN that we will use क्रम our
 * source messages.  Note that this affects the पूर्णांकerface, not just
 * this user, so it will affect all users of this पूर्णांकerface.  This is
 * so some initialization code can come in and करो the OEM-specअगरic
 * things it takes to determine your address (अगर not the BMC) and set
 * it क्रम everyone अन्यथा.  Note that each channel can have its own
 * address.
 */
पूर्णांक ipmi_set_my_address(काष्ठा ipmi_user *user,
			अचिन्हित पूर्णांक  channel,
			अचिन्हित अक्षर address);
पूर्णांक ipmi_get_my_address(काष्ठा ipmi_user *user,
			अचिन्हित पूर्णांक  channel,
			अचिन्हित अक्षर *address);
पूर्णांक ipmi_set_my_LUN(काष्ठा ipmi_user *user,
		    अचिन्हित पूर्णांक  channel,
		    अचिन्हित अक्षर LUN);
पूर्णांक ipmi_get_my_LUN(काष्ठा ipmi_user *user,
		    अचिन्हित पूर्णांक  channel,
		    अचिन्हित अक्षर *LUN);

/*
 * Like ipmi_request, but lets you specअगरy the number of retries and
 * the retry समय.  The retries is the number of बार the message
 * will be resent अगर no reply is received.  If set to -1, the शेष
 * value will be used.  The retry समय is the समय in milliseconds
 * between retries.  If set to zero, the शेष value will be
 * used.
 *
 * Don't use this unless you *really* have to.  It's primarily क्रम the
 * IPMI over LAN converter; since the LAN stuff करोes its own retries,
 * it makes no sense to करो it here.  However, this can be used अगर you
 * have unusual requirements.
 */
पूर्णांक ipmi_request_समय_रखो(काष्ठा ipmi_user *user,
			 काष्ठा ipmi_addr *addr,
			 दीर्घ             msgid,
			 काष्ठा kernel_ipmi_msg  *msg,
			 व्योम             *user_msg_data,
			 पूर्णांक              priority,
			 पूर्णांक              max_retries,
			 अचिन्हित पूर्णांक     retry_समय_ms);

/*
 * Like ipmi_request, but with messages supplied.  This will not
 * allocate any memory, and the messages may be अटलally allocated
 * (just make sure to करो the "done" handling on them).  Note that this
 * is primarily क्रम the watchकरोg समयr, since it should be able to
 * send messages even अगर no memory is available.  This is subject to
 * change as the प्रणाली changes, so करोn't use it unless you REALLY
 * have to.
 */
पूर्णांक ipmi_request_supply_msgs(काष्ठा ipmi_user     *user,
			     काष्ठा ipmi_addr     *addr,
			     दीर्घ                 msgid,
			     काष्ठा kernel_ipmi_msg *msg,
			     व्योम                 *user_msg_data,
			     व्योम                 *supplied_smi,
			     काष्ठा ipmi_recv_msg *supplied_recv,
			     पूर्णांक                  priority);

/*
 * Poll the IPMI पूर्णांकerface क्रम the user.  This causes the IPMI code to
 * करो an immediate check क्रम inक्रमmation from the driver and handle
 * anything that is immediately pending.  This will not block in any
 * way.  This is useful अगर you need to spin रुकोing क्रम something to
 * happen in the IPMI driver.
 */
व्योम ipmi_poll_पूर्णांकerface(काष्ठा ipmi_user *user);

/*
 * When commands come in to the SMS, the user can रेजिस्टर to receive
 * them.  Only one user can be listening on a specअगरic netfn/cmd/chan tuple
 * at a समय, you will get an EBUSY error अगर the command is alपढ़ोy
 * रेजिस्टरed.  If a command is received that करोes not have a user
 * रेजिस्टरed, the driver will स्वतःmatically वापस the proper
 * error.  Channels are specअगरied as a bitfield, use IPMI_CHAN_ALL to
 * mean all channels.
 */
पूर्णांक ipmi_रेजिस्टर_क्रम_cmd(काष्ठा ipmi_user *user,
			  अचिन्हित अक्षर netfn,
			  अचिन्हित अक्षर cmd,
			  अचिन्हित पूर्णांक  chans);
पूर्णांक ipmi_unरेजिस्टर_क्रम_cmd(काष्ठा ipmi_user *user,
			    अचिन्हित अक्षर netfn,
			    अचिन्हित अक्षर cmd,
			    अचिन्हित पूर्णांक  chans);

/*
 * Go पूर्णांकo a mode where the driver will not स्वतःnomously attempt to करो
 * things with the पूर्णांकerface.  It will still respond to attentions and
 * पूर्णांकerrupts, and it will expect that commands will complete.  It
 * will not स्वतःmatcially check क्रम flags, events, or things of that
 * nature.
 *
 * This is primarily used क्रम firmware upgrades.  The idea is that
 * when you go पूर्णांकo firmware upgrade mode, you करो this operation
 * and the driver will not attempt to करो anything but what you tell
 * it or what the BMC asks क्रम.
 *
 * Note that अगर you send a command that resets the BMC, the driver
 * will still expect a response from that command.  So the BMC should
 * reset itself *after* the response is sent.  Resetting beक्रमe the
 * response is just silly.
 *
 * If in स्वतः मुख्यtenance mode, the driver will स्वतःmatically go पूर्णांकo
 * मुख्यtenance mode क्रम 30 seconds अगर it sees a cold reset, a warm
 * reset, or a firmware NetFN.  This means that code that uses only
 * firmware NetFN commands to करो upgrades will work स्वतःmatically
 * without change, assuming it sends a message every 30 seconds or
 * less.
 *
 * See the IPMI_MAINTEन_अंकCE_MODE_xxx defines क्रम what the mode means.
 */
पूर्णांक ipmi_get_मुख्यtenance_mode(काष्ठा ipmi_user *user);
पूर्णांक ipmi_set_मुख्यtenance_mode(काष्ठा ipmi_user *user, पूर्णांक mode);

/*
 * When the user is created, it will not receive IPMI events by
 * शेष.  The user must set this to TRUE to get incoming events.
 * The first user that sets this to TRUE will receive all events that
 * have been queued जबतक no one was रुकोing क्रम events.
 */
पूर्णांक ipmi_set_माला_लो_events(काष्ठा ipmi_user *user, bool val);

/*
 * Called when a new SMI is रेजिस्टरed.  This will also be called on
 * every existing पूर्णांकerface when a new watcher is रेजिस्टरed with
 * ipmi_smi_watcher_रेजिस्टर().
 */
काष्ठा ipmi_smi_watcher अणु
	काष्ठा list_head link;

	/*
	 * You must set the owner to the current module, अगर you are in
	 * a module (generally just set it to "THIS_MODULE").
	 */
	काष्ठा module *owner;

	/*
	 * These two are called with पढ़ो locks held क्रम the पूर्णांकerface
	 * the watcher list.  So you can add and हटाओ users from the
	 * IPMI पूर्णांकerface, send messages, etc., but you cannot add
	 * or हटाओ SMI watchers or SMI पूर्णांकerfaces.
	 */
	व्योम (*new_smi)(पूर्णांक अगर_num, काष्ठा device *dev);
	व्योम (*smi_gone)(पूर्णांक अगर_num);
पूर्ण;

पूर्णांक ipmi_smi_watcher_रेजिस्टर(काष्ठा ipmi_smi_watcher *watcher);
पूर्णांक ipmi_smi_watcher_unरेजिस्टर(काष्ठा ipmi_smi_watcher *watcher);

/*
 * The following are various helper functions क्रम dealing with IPMI
 * addresses.
 */

/* Return the maximum length of an IPMI address given it's type. */
अचिन्हित पूर्णांक ipmi_addr_length(पूर्णांक addr_type);

/* Validate that the given IPMI address is valid. */
पूर्णांक ipmi_validate_addr(काष्ठा ipmi_addr *addr, पूर्णांक len);

/*
 * How did the IPMI driver find out about the device?
 */
क्रमागत ipmi_addr_src अणु
	SI_INVALID = 0, SI_HOTMOD, SI_HARDCODED, SI_SPMI, SI_ACPI, SI_SMBIOS,
	SI_PCI,	SI_DEVICETREE, SI_PLATFORM, SI_LAST
पूर्ण;
स्थिर अक्षर *ipmi_addr_src_to_str(क्रमागत ipmi_addr_src src);

जोड़ ipmi_smi_info_जोड़ अणु
#अगर_घोषित CONFIG_ACPI
	/*
	 * the acpi_info element is defined क्रम the SI_ACPI
	 * address type
	 */
	काष्ठा अणु
		acpi_handle acpi_handle;
	पूर्ण acpi_info;
#पूर्ण_अगर
पूर्ण;

काष्ठा ipmi_smi_info अणु
	क्रमागत ipmi_addr_src addr_src;

	/*
	 * Base device क्रम the पूर्णांकerface.  Don't क्रमget to put this when
	 * you are करोne.
	 */
	काष्ठा device *dev;

	/*
	 * The addr_info provides more detailed info क्रम some IPMI
	 * devices, depending on the addr_src.  Currently only SI_ACPI
	 * info is provided.
	 */
	जोड़ ipmi_smi_info_जोड़ addr_info;
पूर्ण;

/* This is to get the निजी info of काष्ठा ipmi_smi */
बाह्य पूर्णांक ipmi_get_smi_info(पूर्णांक अगर_num, काष्ठा ipmi_smi_info *data);

#घोषणा GET_DEVICE_ID_MAX_RETRY		5

#पूर्ण_अगर /* __LINUX_IPMI_H */
