<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi_ipmi.c - ACPI IPMI opregion
 *
 *  Copyright (C) 2010, 2013 Intel Corporation
 *    Author: Zhao Yakui <yakui.zhao@पूर्णांकel.com>
 *            Lv Zheng <lv.zheng@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/ipmi.h>
#समावेश <linux/spinlock.h>

MODULE_AUTHOR("Zhao Yakui");
MODULE_DESCRIPTION("ACPI IPMI Opregion driver");
MODULE_LICENSE("GPL");

#घोषणा ACPI_IPMI_OK			0
#घोषणा ACPI_IPMI_TIMEOUT		0x10
#घोषणा ACPI_IPMI_UNKNOWN		0x07
/* the IPMI समयout is 5s */
#घोषणा IPMI_TIMEOUT			(5000)
#घोषणा ACPI_IPMI_MAX_MSG_LENGTH	64

काष्ठा acpi_ipmi_device अणु
	/* the device list attached to driver_data.ipmi_devices */
	काष्ठा list_head head;

	/* the IPMI request message list */
	काष्ठा list_head tx_msg_list;

	spinlock_t tx_msg_lock;
	acpi_handle handle;
	काष्ठा device *dev;
	काष्ठा ipmi_user *user_पूर्णांकerface;
	पूर्णांक ipmi_अगरnum; /* IPMI पूर्णांकerface number */
	दीर्घ curr_msgid;
	bool dead;
	काष्ठा kref kref;
पूर्ण;

काष्ठा ipmi_driver_data अणु
	काष्ठा list_head ipmi_devices;
	काष्ठा ipmi_smi_watcher bmc_events;
	स्थिर काष्ठा ipmi_user_hndl ipmi_hndlrs;
	काष्ठा mutex ipmi_lock;

	/*
	 * NOTE: IPMI System Interface Selection
	 * There is no प्रणाली पूर्णांकerface specअगरied by the IPMI operation
	 * region access.  We try to select one प्रणाली पूर्णांकerface with ACPI
	 * handle set.  IPMI messages passed from the ACPI codes are sent
	 * to this selected global IPMI प्रणाली पूर्णांकerface.
	 */
	काष्ठा acpi_ipmi_device *selected_smi;
पूर्ण;

काष्ठा acpi_ipmi_msg अणु
	काष्ठा list_head head;

	/*
	 * General speaking the addr type should be SI_ADDR_TYPE. And
	 * the addr channel should be BMC.
	 * In fact it can also be IPMB type. But we will have to
	 * parse it from the Netfn command buffer. It is so complex
	 * that it is skipped.
	 */
	काष्ठा ipmi_addr addr;
	दीर्घ tx_msgid;

	/* it is used to track whether the IPMI message is finished */
	काष्ठा completion tx_complete;

	काष्ठा kernel_ipmi_msg tx_message;
	पूर्णांक msg_करोne;

	/* tx/rx data . And copy it from/to ACPI object buffer */
	u8 data[ACPI_IPMI_MAX_MSG_LENGTH];
	u8 rx_len;

	काष्ठा acpi_ipmi_device *device;
	काष्ठा kref kref;
पूर्ण;

/* IPMI request/response buffer per ACPI 4.0, sec 5.5.2.4.3.2 */
काष्ठा acpi_ipmi_buffer अणु
	u8 status;
	u8 length;
	u8 data[ACPI_IPMI_MAX_MSG_LENGTH];
पूर्ण;

अटल व्योम ipmi_रेजिस्टर_bmc(पूर्णांक अगरace, काष्ठा device *dev);
अटल व्योम ipmi_bmc_gone(पूर्णांक अगरace);
अटल व्योम ipmi_msg_handler(काष्ठा ipmi_recv_msg *msg, व्योम *user_msg_data);

अटल काष्ठा ipmi_driver_data driver_data = अणु
	.ipmi_devices = LIST_HEAD_INIT(driver_data.ipmi_devices),
	.bmc_events = अणु
		.owner = THIS_MODULE,
		.new_smi = ipmi_रेजिस्टर_bmc,
		.smi_gone = ipmi_bmc_gone,
	पूर्ण,
	.ipmi_hndlrs = अणु
		.ipmi_recv_hndl = ipmi_msg_handler,
	पूर्ण,
	.ipmi_lock = __MUTEX_INITIALIZER(driver_data.ipmi_lock)
पूर्ण;

अटल काष्ठा acpi_ipmi_device *
ipmi_dev_alloc(पूर्णांक अगरace, काष्ठा device *dev, acpi_handle handle)
अणु
	काष्ठा acpi_ipmi_device *ipmi_device;
	पूर्णांक err;
	काष्ठा ipmi_user *user;

	ipmi_device = kzalloc(माप(*ipmi_device), GFP_KERNEL);
	अगर (!ipmi_device)
		वापस शून्य;

	kref_init(&ipmi_device->kref);
	INIT_LIST_HEAD(&ipmi_device->head);
	INIT_LIST_HEAD(&ipmi_device->tx_msg_list);
	spin_lock_init(&ipmi_device->tx_msg_lock);
	ipmi_device->handle = handle;
	ipmi_device->dev = get_device(dev);
	ipmi_device->ipmi_अगरnum = अगरace;

	err = ipmi_create_user(अगरace, &driver_data.ipmi_hndlrs,
			       ipmi_device, &user);
	अगर (err) अणु
		put_device(dev);
		kमुक्त(ipmi_device);
		वापस शून्य;
	पूर्ण
	ipmi_device->user_पूर्णांकerface = user;

	वापस ipmi_device;
पूर्ण

अटल व्योम ipmi_dev_release(काष्ठा acpi_ipmi_device *ipmi_device)
अणु
	ipmi_destroy_user(ipmi_device->user_पूर्णांकerface);
	put_device(ipmi_device->dev);
	kमुक्त(ipmi_device);
पूर्ण

अटल व्योम ipmi_dev_release_kref(काष्ठा kref *kref)
अणु
	काष्ठा acpi_ipmi_device *ipmi =
		container_of(kref, काष्ठा acpi_ipmi_device, kref);

	ipmi_dev_release(ipmi);
पूर्ण

अटल व्योम __ipmi_dev_समाप्त(काष्ठा acpi_ipmi_device *ipmi_device)
अणु
	list_del(&ipmi_device->head);
	अगर (driver_data.selected_smi == ipmi_device)
		driver_data.selected_smi = शून्य;

	/*
	 * Always setting dead flag after deleting from the list or
	 * list_क्रम_each_entry() codes must get changed.
	 */
	ipmi_device->dead = true;
पूर्ण

अटल काष्ठा acpi_ipmi_device *acpi_ipmi_dev_get(व्योम)
अणु
	काष्ठा acpi_ipmi_device *ipmi_device = शून्य;

	mutex_lock(&driver_data.ipmi_lock);
	अगर (driver_data.selected_smi) अणु
		ipmi_device = driver_data.selected_smi;
		kref_get(&ipmi_device->kref);
	पूर्ण
	mutex_unlock(&driver_data.ipmi_lock);

	वापस ipmi_device;
पूर्ण

अटल व्योम acpi_ipmi_dev_put(काष्ठा acpi_ipmi_device *ipmi_device)
अणु
	kref_put(&ipmi_device->kref, ipmi_dev_release_kref);
पूर्ण

अटल काष्ठा acpi_ipmi_msg *ipmi_msg_alloc(व्योम)
अणु
	काष्ठा acpi_ipmi_device *ipmi;
	काष्ठा acpi_ipmi_msg *ipmi_msg;

	ipmi = acpi_ipmi_dev_get();
	अगर (!ipmi)
		वापस शून्य;

	ipmi_msg = kzalloc(माप(काष्ठा acpi_ipmi_msg), GFP_KERNEL);
	अगर (!ipmi_msg) अणु
		acpi_ipmi_dev_put(ipmi);
		वापस शून्य;
	पूर्ण

	kref_init(&ipmi_msg->kref);
	init_completion(&ipmi_msg->tx_complete);
	INIT_LIST_HEAD(&ipmi_msg->head);
	ipmi_msg->device = ipmi;
	ipmi_msg->msg_करोne = ACPI_IPMI_UNKNOWN;

	वापस ipmi_msg;
पूर्ण

अटल व्योम ipmi_msg_release(काष्ठा acpi_ipmi_msg *tx_msg)
अणु
	acpi_ipmi_dev_put(tx_msg->device);
	kमुक्त(tx_msg);
पूर्ण

अटल व्योम ipmi_msg_release_kref(काष्ठा kref *kref)
अणु
	काष्ठा acpi_ipmi_msg *tx_msg =
		container_of(kref, काष्ठा acpi_ipmi_msg, kref);

	ipmi_msg_release(tx_msg);
पूर्ण

अटल काष्ठा acpi_ipmi_msg *acpi_ipmi_msg_get(काष्ठा acpi_ipmi_msg *tx_msg)
अणु
	kref_get(&tx_msg->kref);

	वापस tx_msg;
पूर्ण

अटल व्योम acpi_ipmi_msg_put(काष्ठा acpi_ipmi_msg *tx_msg)
अणु
	kref_put(&tx_msg->kref, ipmi_msg_release_kref);
पूर्ण

#घोषणा IPMI_OP_RGN_NETFN(offset)	((offset >> 8) & 0xff)
#घोषणा IPMI_OP_RGN_CMD(offset)		(offset & 0xff)
अटल पूर्णांक acpi_क्रमmat_ipmi_request(काष्ठा acpi_ipmi_msg *tx_msg,
				    acpi_physical_address address,
				    acpi_पूर्णांकeger *value)
अणु
	काष्ठा kernel_ipmi_msg *msg;
	काष्ठा acpi_ipmi_buffer *buffer;
	काष्ठा acpi_ipmi_device *device;
	अचिन्हित दीर्घ flags;

	msg = &tx_msg->tx_message;

	/*
	 * IPMI network function and command are encoded in the address
	 * within the IPMI OpRegion; see ACPI 4.0, sec 5.5.2.4.3.
	 */
	msg->netfn = IPMI_OP_RGN_NETFN(address);
	msg->cmd = IPMI_OP_RGN_CMD(address);
	msg->data = tx_msg->data;

	/*
	 * value is the parameter passed by the IPMI opregion space handler.
	 * It poपूर्णांकs to the IPMI request message buffer
	 */
	buffer = (काष्ठा acpi_ipmi_buffer *)value;

	/* copy the tx message data */
	अगर (buffer->length > ACPI_IPMI_MAX_MSG_LENGTH) अणु
		dev_WARN_ONCE(tx_msg->device->dev, true,
			      "Unexpected request (msg len %d).\n",
			      buffer->length);
		वापस -EINVAL;
	पूर्ण
	msg->data_len = buffer->length;
	स_नकल(tx_msg->data, buffer->data, msg->data_len);

	/*
	 * now the शेष type is SYSTEM_INTERFACE and channel type is BMC.
	 * If the netfn is APP_REQUEST and the cmd is SEND_MESSAGE,
	 * the addr type should be changed to IPMB. Then we will have to parse
	 * the IPMI request message buffer to get the IPMB address.
	 * If so, please fix me.
	 */
	tx_msg->addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	tx_msg->addr.channel = IPMI_BMC_CHANNEL;
	tx_msg->addr.data[0] = 0;

	/* Get the msgid */
	device = tx_msg->device;

	spin_lock_irqsave(&device->tx_msg_lock, flags);
	device->curr_msgid++;
	tx_msg->tx_msgid = device->curr_msgid;
	spin_unlock_irqrestore(&device->tx_msg_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम acpi_क्रमmat_ipmi_response(काष्ठा acpi_ipmi_msg *msg,
				      acpi_पूर्णांकeger *value)
अणु
	काष्ठा acpi_ipmi_buffer *buffer;

	/*
	 * value is also used as output parameter. It represents the response
	 * IPMI message वापसed by IPMI command.
	 */
	buffer = (काष्ठा acpi_ipmi_buffer *)value;

	/*
	 * If the flag of msg_करोne is not set, it means that the IPMI command is
	 * not executed correctly.
	 */
	buffer->status = msg->msg_करोne;
	अगर (msg->msg_करोne != ACPI_IPMI_OK)
		वापस;

	/*
	 * If the IPMI response message is obtained correctly, the status code
	 * will be ACPI_IPMI_OK
	 */
	buffer->length = msg->rx_len;
	स_नकल(buffer->data, msg->data, msg->rx_len);
पूर्ण

अटल व्योम ipmi_flush_tx_msg(काष्ठा acpi_ipmi_device *ipmi)
अणु
	काष्ठा acpi_ipmi_msg *tx_msg;
	अचिन्हित दीर्घ flags;

	/*
	 * NOTE: On-going ipmi_recv_msg
	 * ipmi_msg_handler() may still be invoked by ipmi_si after
	 * flushing.  But it is safe to करो a fast flushing on module_निकास()
	 * without रुकोing क्रम all ipmi_recv_msg(s) to complete from
	 * ipmi_msg_handler() as it is ensured by ipmi_si that all
	 * ipmi_recv_msg(s) are मुक्तd after invoking ipmi_destroy_user().
	 */
	spin_lock_irqsave(&ipmi->tx_msg_lock, flags);
	जबतक (!list_empty(&ipmi->tx_msg_list)) अणु
		tx_msg = list_first_entry(&ipmi->tx_msg_list,
					  काष्ठा acpi_ipmi_msg,
					  head);
		list_del(&tx_msg->head);
		spin_unlock_irqrestore(&ipmi->tx_msg_lock, flags);

		/* wake up the sleep thपढ़ो on the Tx msg */
		complete(&tx_msg->tx_complete);
		acpi_ipmi_msg_put(tx_msg);
		spin_lock_irqsave(&ipmi->tx_msg_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&ipmi->tx_msg_lock, flags);
पूर्ण

अटल व्योम ipmi_cancel_tx_msg(काष्ठा acpi_ipmi_device *ipmi,
			       काष्ठा acpi_ipmi_msg *msg)
अणु
	काष्ठा acpi_ipmi_msg *tx_msg, *temp;
	bool msg_found = false;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipmi->tx_msg_lock, flags);
	list_क्रम_each_entry_safe(tx_msg, temp, &ipmi->tx_msg_list, head) अणु
		अगर (msg == tx_msg) अणु
			msg_found = true;
			list_del(&tx_msg->head);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ipmi->tx_msg_lock, flags);

	अगर (msg_found)
		acpi_ipmi_msg_put(tx_msg);
पूर्ण

अटल व्योम ipmi_msg_handler(काष्ठा ipmi_recv_msg *msg, व्योम *user_msg_data)
अणु
	काष्ठा acpi_ipmi_device *ipmi_device = user_msg_data;
	bool msg_found = false;
	काष्ठा acpi_ipmi_msg *tx_msg, *temp;
	काष्ठा device *dev = ipmi_device->dev;
	अचिन्हित दीर्घ flags;

	अगर (msg->user != ipmi_device->user_पूर्णांकerface) अणु
		dev_warn(dev,
			 "Unexpected response is returned. returned user %p, expected user %p\n",
			 msg->user, ipmi_device->user_पूर्णांकerface);
		जाओ out_msg;
	पूर्ण

	spin_lock_irqsave(&ipmi_device->tx_msg_lock, flags);
	list_क्रम_each_entry_safe(tx_msg, temp, &ipmi_device->tx_msg_list, head) अणु
		अगर (msg->msgid == tx_msg->tx_msgid) अणु
			msg_found = true;
			list_del(&tx_msg->head);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ipmi_device->tx_msg_lock, flags);

	अगर (!msg_found) अणु
		dev_warn(dev,
			 "Unexpected response (msg id %ld) is returned.\n",
			 msg->msgid);
		जाओ out_msg;
	पूर्ण

	/* copy the response data to Rx_data buffer */
	अगर (msg->msg.data_len > ACPI_IPMI_MAX_MSG_LENGTH) अणु
		dev_WARN_ONCE(dev, true,
			      "Unexpected response (msg len %d).\n",
			      msg->msg.data_len);
		जाओ out_comp;
	पूर्ण

	/* response msg is an error msg */
	msg->recv_type = IPMI_RESPONSE_RECV_TYPE;
	अगर (msg->recv_type == IPMI_RESPONSE_RECV_TYPE &&
	    msg->msg.data_len == 1) अणु
		अगर (msg->msg.data[0] == IPMI_TIMEOUT_COMPLETION_CODE) अणु
			dev_dbg_once(dev, "Unexpected response (timeout).\n");
			tx_msg->msg_करोne = ACPI_IPMI_TIMEOUT;
		पूर्ण
		जाओ out_comp;
	पूर्ण

	tx_msg->rx_len = msg->msg.data_len;
	स_नकल(tx_msg->data, msg->msg.data, tx_msg->rx_len);
	tx_msg->msg_करोne = ACPI_IPMI_OK;

out_comp:
	complete(&tx_msg->tx_complete);
	acpi_ipmi_msg_put(tx_msg);
out_msg:
	ipmi_मुक्त_recv_msg(msg);
पूर्ण

अटल व्योम ipmi_रेजिस्टर_bmc(पूर्णांक अगरace, काष्ठा device *dev)
अणु
	काष्ठा acpi_ipmi_device *ipmi_device, *temp;
	पूर्णांक err;
	काष्ठा ipmi_smi_info smi_data;
	acpi_handle handle;

	err = ipmi_get_smi_info(अगरace, &smi_data);
	अगर (err)
		वापस;

	अगर (smi_data.addr_src != SI_ACPI)
		जाओ err_ref;
	handle = smi_data.addr_info.acpi_info.acpi_handle;
	अगर (!handle)
		जाओ err_ref;

	ipmi_device = ipmi_dev_alloc(अगरace, smi_data.dev, handle);
	अगर (!ipmi_device) अणु
		dev_warn(smi_data.dev, "Can't create IPMI user interface\n");
		जाओ err_ref;
	पूर्ण

	mutex_lock(&driver_data.ipmi_lock);
	list_क्रम_each_entry(temp, &driver_data.ipmi_devices, head) अणु
		/*
		 * अगर the corresponding ACPI handle is alपढ़ोy added
		 * to the device list, करोn't add it again.
		 */
		अगर (temp->handle == handle)
			जाओ err_lock;
	पूर्ण
	अगर (!driver_data.selected_smi)
		driver_data.selected_smi = ipmi_device;
	list_add_tail(&ipmi_device->head, &driver_data.ipmi_devices);
	mutex_unlock(&driver_data.ipmi_lock);

	put_device(smi_data.dev);
	वापस;

err_lock:
	mutex_unlock(&driver_data.ipmi_lock);
	ipmi_dev_release(ipmi_device);
err_ref:
	put_device(smi_data.dev);
पूर्ण

अटल व्योम ipmi_bmc_gone(पूर्णांक अगरace)
अणु
	काष्ठा acpi_ipmi_device *ipmi_device, *temp;
	bool dev_found = false;

	mutex_lock(&driver_data.ipmi_lock);
	list_क्रम_each_entry_safe(ipmi_device, temp,
				 &driver_data.ipmi_devices, head) अणु
		अगर (ipmi_device->ipmi_अगरnum != अगरace) अणु
			dev_found = true;
			__ipmi_dev_समाप्त(ipmi_device);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!driver_data.selected_smi)
		driver_data.selected_smi = list_first_entry_or_null(
					&driver_data.ipmi_devices,
					काष्ठा acpi_ipmi_device, head);
	mutex_unlock(&driver_data.ipmi_lock);

	अगर (dev_found) अणु
		ipmi_flush_tx_msg(ipmi_device);
		acpi_ipmi_dev_put(ipmi_device);
	पूर्ण
पूर्ण

/*
 * This is the IPMI opregion space handler.
 * @function: indicates the पढ़ो/ग_लिखो. In fact as the IPMI message is driven
 * by command, only ग_लिखो is meaningful.
 * @address: This contains the netfn/command of IPMI request message.
 * @bits   : not used.
 * @value  : it is an in/out parameter. It poपूर्णांकs to the IPMI message buffer.
 *	     Beक्रमe the IPMI message is sent, it represents the actual request
 *	     IPMI message. After the IPMI message is finished, it represents
 *	     the response IPMI message वापसed by IPMI command.
 * @handler_context: IPMI device context.
 */
अटल acpi_status
acpi_ipmi_space_handler(u32 function, acpi_physical_address address,
			u32 bits, acpi_पूर्णांकeger *value,
			व्योम *handler_context, व्योम *region_context)
अणु
	काष्ठा acpi_ipmi_msg *tx_msg;
	काष्ठा acpi_ipmi_device *ipmi_device;
	पूर्णांक err;
	acpi_status status;
	अचिन्हित दीर्घ flags;

	/*
	 * IPMI opregion message.
	 * IPMI message is firstly written to the BMC and प्रणाली software
	 * can get the respsonse. So it is unmeaningful क्रम the पढ़ो access
	 * of IPMI opregion.
	 */
	अगर ((function & ACPI_IO_MASK) == ACPI_READ)
		वापस AE_TYPE;

	tx_msg = ipmi_msg_alloc();
	अगर (!tx_msg)
		वापस AE_NOT_EXIST;
	ipmi_device = tx_msg->device;

	अगर (acpi_क्रमmat_ipmi_request(tx_msg, address, value) != 0) अणु
		ipmi_msg_release(tx_msg);
		वापस AE_TYPE;
	पूर्ण

	acpi_ipmi_msg_get(tx_msg);
	mutex_lock(&driver_data.ipmi_lock);
	/* Do not add a tx_msg that can not be flushed. */
	अगर (ipmi_device->dead) अणु
		mutex_unlock(&driver_data.ipmi_lock);
		ipmi_msg_release(tx_msg);
		वापस AE_NOT_EXIST;
	पूर्ण
	spin_lock_irqsave(&ipmi_device->tx_msg_lock, flags);
	list_add_tail(&tx_msg->head, &ipmi_device->tx_msg_list);
	spin_unlock_irqrestore(&ipmi_device->tx_msg_lock, flags);
	mutex_unlock(&driver_data.ipmi_lock);

	err = ipmi_request_समय_रखो(ipmi_device->user_पूर्णांकerface,
				   &tx_msg->addr,
				   tx_msg->tx_msgid,
				   &tx_msg->tx_message,
				   शून्य, 0, 0, IPMI_TIMEOUT);
	अगर (err) अणु
		status = AE_ERROR;
		जाओ out_msg;
	पूर्ण
	रुको_क्रम_completion(&tx_msg->tx_complete);

	acpi_क्रमmat_ipmi_response(tx_msg, value);
	status = AE_OK;

out_msg:
	ipmi_cancel_tx_msg(ipmi_device, tx_msg);
	acpi_ipmi_msg_put(tx_msg);
	वापस status;
पूर्ण

अटल पूर्णांक __init acpi_ipmi_init(व्योम)
अणु
	पूर्णांक result;
	acpi_status status;

	अगर (acpi_disabled)
		वापस 0;

	status = acpi_install_address_space_handler(ACPI_ROOT_OBJECT,
						    ACPI_ADR_SPACE_IPMI,
						    &acpi_ipmi_space_handler,
						    शून्य, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		pr_warn("Can't register IPMI opregion space handle\n");
		वापस -EINVAL;
	पूर्ण
	result = ipmi_smi_watcher_रेजिस्टर(&driver_data.bmc_events);
	अगर (result)
		pr_err("Can't register IPMI system interface watcher\n");

	वापस result;
पूर्ण

अटल व्योम __निकास acpi_ipmi_निकास(व्योम)
अणु
	काष्ठा acpi_ipmi_device *ipmi_device;

	अगर (acpi_disabled)
		वापस;

	ipmi_smi_watcher_unरेजिस्टर(&driver_data.bmc_events);

	/*
	 * When one smi_watcher is unरेजिस्टरed, it is only deleted
	 * from the smi_watcher list. But the smi_gone callback function
	 * is not called. So explicitly uninstall the ACPI IPMI oregion
	 * handler and मुक्त it.
	 */
	mutex_lock(&driver_data.ipmi_lock);
	जबतक (!list_empty(&driver_data.ipmi_devices)) अणु
		ipmi_device = list_first_entry(&driver_data.ipmi_devices,
					       काष्ठा acpi_ipmi_device,
					       head);
		__ipmi_dev_समाप्त(ipmi_device);
		mutex_unlock(&driver_data.ipmi_lock);

		ipmi_flush_tx_msg(ipmi_device);
		acpi_ipmi_dev_put(ipmi_device);

		mutex_lock(&driver_data.ipmi_lock);
	पूर्ण
	mutex_unlock(&driver_data.ipmi_lock);
	acpi_हटाओ_address_space_handler(ACPI_ROOT_OBJECT,
					  ACPI_ADR_SPACE_IPMI,
					  &acpi_ipmi_space_handler);
पूर्ण

module_init(acpi_ipmi_init);
module_निकास(acpi_ipmi_निकास);
