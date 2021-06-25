<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * ipmi_smi.h
 *
 * MontaVista IPMI प्रणाली management पूर्णांकerface
 *
 * Author: MontaVista Software, Inc.
 *         Corey Minyard <minyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002 MontaVista Software Inc.
 *
 */

#अगर_अघोषित __LINUX_IPMI_SMI_H
#घोषणा __LINUX_IPMI_SMI_H

#समावेश <linux/ipmi_msgdefs.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ipmi.h>

काष्ठा device;

/*
 * This files describes the पूर्णांकerface क्रम IPMI प्रणाली management पूर्णांकerface
 * drivers to bind पूर्णांकo the IPMI message handler.
 */

/* Structure क्रम the low-level drivers. */
काष्ठा ipmi_smi;

/*
 * Flags क्रम set_check_watch() below.  Tells अगर the SMI should be
 * रुकोing क्रम watchकरोg समयouts, commands and/or messages.
 */
#घोषणा IPMI_WATCH_MASK_CHECK_MESSAGES	(1 << 0)
#घोषणा IPMI_WATCH_MASK_CHECK_WATCHDOG	(1 << 1)
#घोषणा IPMI_WATCH_MASK_CHECK_COMMANDS	(1 << 2)

/*
 * Messages to/from the lower layer.  The smi पूर्णांकerface will take one
 * of these to send. After the send has occurred and a response has
 * been received, it will report this same data काष्ठाure back up to
 * the upper layer.  If an error occurs, it should fill in the
 * response with an error code in the completion code location. When
 * asynchronous data is received, one of these is allocated, the
 * data_size is set to zero and the response holds the data from the
 * get message or get event command that the पूर्णांकerface initiated.
 * Note that it is the पूर्णांकerfaces responsibility to detect
 * asynchronous data and messages and request them from the
 * पूर्णांकerface.
 */
काष्ठा ipmi_smi_msg अणु
	काष्ठा list_head link;

	दीर्घ    msgid;
	व्योम    *user_data;

	पूर्णांक           data_size;
	अचिन्हित अक्षर data[IPMI_MAX_MSG_LENGTH];

	पूर्णांक           rsp_size;
	अचिन्हित अक्षर rsp[IPMI_MAX_MSG_LENGTH];

	/*
	 * Will be called when the प्रणाली is करोne with the message
	 * (presumably to मुक्त it).
	 */
	व्योम (*करोne)(काष्ठा ipmi_smi_msg *msg);
पूर्ण;

काष्ठा ipmi_smi_handlers अणु
	काष्ठा module *owner;

	/*
	 * The low-level पूर्णांकerface cannot start sending messages to
	 * the upper layer until this function is called.  This may
	 * not be शून्य, the lower layer must take the पूर्णांकerface from
	 * this call.
	 */
	पूर्णांक (*start_processing)(व्योम            *send_info,
				काष्ठा ipmi_smi *new_पूर्णांकf);

	/*
	 * When called, the low-level पूर्णांकerface should disable all
	 * processing, it should be complete shut करोwn when it वापसs.
	 */
	व्योम (*shutकरोwn)(व्योम *send_info);

	/*
	 * Get the detailed निजी info of the low level पूर्णांकerface and store
	 * it पूर्णांकo the काष्ठाure of ipmi_smi_data. For example: the
	 * ACPI device handle will be वापसed क्रम the pnp_acpi IPMI device.
	 */
	पूर्णांक (*get_smi_info)(व्योम *send_info, काष्ठा ipmi_smi_info *data);

	/*
	 * Called to enqueue an SMI message to be sent.  This
	 * operation is not allowed to fail.  If an error occurs, it
	 * should report back the error in a received message.  It may
	 * करो this in the current call context, since no ग_लिखो locks
	 * are held when this is run.  Message are delivered one at
	 * a समय by the message handler, a new message will not be
	 * delivered until the previous message is वापसed.
	 */
	व्योम (*sender)(व्योम                *send_info,
		       काष्ठा ipmi_smi_msg *msg);

	/*
	 * Called by the upper layer to request that we try to get
	 * events from the BMC we are attached to.
	 */
	व्योम (*request_events)(व्योम *send_info);

	/*
	 * Called by the upper layer when some user requires that the
	 * पूर्णांकerface watch क्रम received messages and watchकरोg
	 * preसमयouts (basically करो a "Get Flags", or not.  Used by
	 * the SMI to know अगर it should watch क्रम these.  This may be
	 * शून्य अगर the SMI करोes not implement it.  watch_mask is from
	 * IPMI_WATCH_MASK_xxx above.  The पूर्णांकerface should run slower
	 * समयouts क्रम just watchकरोg checking or faster समयouts when
	 * रुकोing क्रम the message queue.
	 */
	व्योम (*set_need_watch)(व्योम *send_info, अचिन्हित पूर्णांक watch_mask);

	/*
	 * Called when flushing all pending messages.
	 */
	व्योम (*flush_messages)(व्योम *send_info);

	/*
	 * Called when the पूर्णांकerface should go पूर्णांकo "run to
	 * completion" mode.  If this call sets the value to true, the
	 * पूर्णांकerface should make sure that all messages are flushed
	 * out and that none are pending, and any new requests are run
	 * to completion immediately.
	 */
	व्योम (*set_run_to_completion)(व्योम *send_info, bool run_to_completion);

	/*
	 * Called to poll क्रम work to करो.  This is so upper layers can
	 * poll क्रम operations during things like crash dumps.
	 */
	व्योम (*poll)(व्योम *send_info);

	/*
	 * Enable/disable firmware मुख्यtenance mode.  Note that this
	 * is *not* the modes defined, this is simply an on/off
	 * setting.  The message handler करोes the mode handling.  Note
	 * that this is called from पूर्णांकerrupt context, so it cannot
	 * block.
	 */
	व्योम (*set_मुख्यtenance_mode)(व्योम *send_info, bool enable);
पूर्ण;

काष्ठा ipmi_device_id अणु
	अचिन्हित अक्षर device_id;
	अचिन्हित अक्षर device_revision;
	अचिन्हित अक्षर firmware_revision_1;
	अचिन्हित अक्षर firmware_revision_2;
	अचिन्हित अक्षर ipmi_version;
	अचिन्हित अक्षर additional_device_support;
	अचिन्हित पूर्णांक  manufacturer_id;
	अचिन्हित पूर्णांक  product_id;
	अचिन्हित अक्षर aux_firmware_revision[4];
	अचिन्हित पूर्णांक  aux_firmware_revision_set : 1;
पूर्ण;

#घोषणा ipmi_version_major(v) ((v)->ipmi_version & 0xf)
#घोषणा ipmi_version_minor(v) ((v)->ipmi_version >> 4)

/*
 * Take a poपूर्णांकer to an IPMI response and extract device id inक्रमmation from
 * it. @netfn is in the IPMI_NETFN_ क्रमmat, so may need to be shअगरted from
 * a SI response.
 */
अटल अंतरभूत पूर्णांक ipmi_demangle_device_id(uपूर्णांक8_t netfn, uपूर्णांक8_t cmd,
					  स्थिर अचिन्हित अक्षर *data,
					  अचिन्हित पूर्णांक data_len,
					  काष्ठा ipmi_device_id *id)
अणु
	अगर (data_len < 7)
		वापस -EINVAL;
	अगर (netfn != IPMI_NETFN_APP_RESPONSE || cmd != IPMI_GET_DEVICE_ID_CMD)
		/* Strange, didn't get the response we expected. */
		वापस -EINVAL;
	अगर (data[0] != 0)
		/* That's odd, it shouldn't be able to fail. */
		वापस -EINVAL;

	data++;
	data_len--;

	id->device_id = data[0];
	id->device_revision = data[1];
	id->firmware_revision_1 = data[2];
	id->firmware_revision_2 = data[3];
	id->ipmi_version = data[4];
	id->additional_device_support = data[5];
	अगर (data_len >= 11) अणु
		id->manufacturer_id = (data[6] | (data[7] << 8) |
				       (data[8] << 16));
		id->product_id = data[9] | (data[10] << 8);
	पूर्ण अन्यथा अणु
		id->manufacturer_id = 0;
		id->product_id = 0;
	पूर्ण
	अगर (data_len >= 15) अणु
		स_नकल(id->aux_firmware_revision, data+11, 4);
		id->aux_firmware_revision_set = 1;
	पूर्ण अन्यथा
		id->aux_firmware_revision_set = 0;

	वापस 0;
पूर्ण

/*
 * Add a low-level पूर्णांकerface to the IPMI driver.  Note that अगर the
 * पूर्णांकerface करोesn't know its slave address, it should pass in zero.
 * The low-level पूर्णांकerface should not deliver any messages to the
 * upper layer until the start_processing() function in the handlers
 * is called, and the lower layer must get the पूर्णांकerface from that
 * call.
 */
पूर्णांक ipmi_add_smi(काष्ठा module            *owner,
		 स्थिर काष्ठा ipmi_smi_handlers *handlers,
		 व्योम                     *send_info,
		 काष्ठा device            *dev,
		 अचिन्हित अक्षर            slave_addr);

#घोषणा ipmi_रेजिस्टर_smi(handlers, send_info, dev, slave_addr) \
	ipmi_add_smi(THIS_MODULE, handlers, send_info, dev, slave_addr)

/*
 * Remove a low-level पूर्णांकerface from the IPMI driver.  This will
 * वापस an error अगर the पूर्णांकerface is still in use by a user.
 */
व्योम ipmi_unरेजिस्टर_smi(काष्ठा ipmi_smi *पूर्णांकf);

/*
 * The lower layer reports received messages through this पूर्णांकerface.
 * The data_size should be zero अगर this is an asynchronous message.  If
 * the lower layer माला_लो an error sending a message, it should क्रमmat
 * an error response in the message response.
 */
व्योम ipmi_smi_msg_received(काष्ठा ipmi_smi     *पूर्णांकf,
			   काष्ठा ipmi_smi_msg *msg);

/* The lower layer received a watchकरोg pre-समयout on पूर्णांकerface. */
व्योम ipmi_smi_watchकरोg_preसमयout(काष्ठा ipmi_smi *पूर्णांकf);

काष्ठा ipmi_smi_msg *ipmi_alloc_smi_msg(व्योम);
अटल अंतरभूत व्योम ipmi_मुक्त_smi_msg(काष्ठा ipmi_smi_msg *msg)
अणु
	msg->करोne(msg);
पूर्ण

#पूर्ण_अगर /* __LINUX_IPMI_SMI_H */
