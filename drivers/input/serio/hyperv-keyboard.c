<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (c) 2013, Microsoft Corporation.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/completion.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>

/*
 * Current version 1.0
 *
 */
#घोषणा SYNTH_KBD_VERSION_MAJOR 1
#घोषणा SYNTH_KBD_VERSION_MINOR	0
#घोषणा SYNTH_KBD_VERSION		(SYNTH_KBD_VERSION_MINOR | \
					 (SYNTH_KBD_VERSION_MAJOR << 16))


/*
 * Message types in the synthetic input protocol
 */
क्रमागत synth_kbd_msg_type अणु
	SYNTH_KBD_PROTOCOL_REQUEST = 1,
	SYNTH_KBD_PROTOCOL_RESPONSE = 2,
	SYNTH_KBD_EVENT = 3,
	SYNTH_KBD_LED_INDICATORS = 4,
पूर्ण;

/*
 * Basic message काष्ठाures.
 */
काष्ठा synth_kbd_msg_hdr अणु
	__le32 type;
पूर्ण;

काष्ठा synth_kbd_msg अणु
	काष्ठा synth_kbd_msg_hdr header;
	अक्षर data[]; /* Enबंदd message */
पूर्ण;

जोड़ synth_kbd_version अणु
	__le32 version;
पूर्ण;

/*
 * Protocol messages
 */
काष्ठा synth_kbd_protocol_request अणु
	काष्ठा synth_kbd_msg_hdr header;
	जोड़ synth_kbd_version version_requested;
पूर्ण;

#घोषणा PROTOCOL_ACCEPTED	BIT(0)
काष्ठा synth_kbd_protocol_response अणु
	काष्ठा synth_kbd_msg_hdr header;
	__le32 proto_status;
पूर्ण;

#घोषणा IS_UNICODE	BIT(0)
#घोषणा IS_BREAK	BIT(1)
#घोषणा IS_E0		BIT(2)
#घोषणा IS_E1		BIT(3)
काष्ठा synth_kbd_keystroke अणु
	काष्ठा synth_kbd_msg_hdr header;
	__le16 make_code;
	__le16 reserved0;
	__le32 info; /* Additional inक्रमmation */
पूर्ण;


#घोषणा HK_MAXIMUM_MESSAGE_SIZE 256

#घोषणा KBD_VSC_SEND_RING_BUFFER_SIZE	VMBUS_RING_SIZE(36 * 1024)
#घोषणा KBD_VSC_RECV_RING_BUFFER_SIZE	VMBUS_RING_SIZE(36 * 1024)

#घोषणा XTKBD_EMUL0     0xe0
#घोषणा XTKBD_EMUL1     0xe1
#घोषणा XTKBD_RELEASE   0x80


/*
 * Represents a keyboard device
 */
काष्ठा hv_kbd_dev अणु
	काष्ठा hv_device *hv_dev;
	काष्ठा serio *hv_serio;
	काष्ठा synth_kbd_protocol_request protocol_req;
	काष्ठा synth_kbd_protocol_response protocol_resp;
	/* Synchronize the request/response अगर needed */
	काष्ठा completion रुको_event;
	spinlock_t lock; /* protects 'started' field */
	bool started;
पूर्ण;

अटल व्योम hv_kbd_on_receive(काष्ठा hv_device *hv_dev,
			      काष्ठा synth_kbd_msg *msg, u32 msg_length)
अणु
	काष्ठा hv_kbd_dev *kbd_dev = hv_get_drvdata(hv_dev);
	काष्ठा synth_kbd_keystroke *ks_msg;
	अचिन्हित दीर्घ flags;
	u32 msg_type = __le32_to_cpu(msg->header.type);
	u32 info;
	u16 scan_code;

	चयन (msg_type) अणु
	हाल SYNTH_KBD_PROTOCOL_RESPONSE:
		/*
		 * Validate the inक्रमmation provided by the host.
		 * If the host is giving us a bogus packet,
		 * drop the packet (hoping the problem
		 * goes away).
		 */
		अगर (msg_length < माप(काष्ठा synth_kbd_protocol_response)) अणु
			dev_err(&hv_dev->device,
				"Illegal protocol response packet (len: %d)\n",
				msg_length);
			अवरोध;
		पूर्ण

		स_नकल(&kbd_dev->protocol_resp, msg,
			माप(काष्ठा synth_kbd_protocol_response));
		complete(&kbd_dev->रुको_event);
		अवरोध;

	हाल SYNTH_KBD_EVENT:
		/*
		 * Validate the inक्रमmation provided by the host.
		 * If the host is giving us a bogus packet,
		 * drop the packet (hoping the problem
		 * goes away).
		 */
		अगर (msg_length < माप(काष्ठा  synth_kbd_keystroke)) अणु
			dev_err(&hv_dev->device,
				"Illegal keyboard event packet (len: %d)\n",
				msg_length);
			अवरोध;
		पूर्ण

		ks_msg = (काष्ठा synth_kbd_keystroke *)msg;
		info = __le32_to_cpu(ks_msg->info);

		/*
		 * Inject the inक्रमmation through the serio पूर्णांकerrupt.
		 */
		spin_lock_irqsave(&kbd_dev->lock, flags);
		अगर (kbd_dev->started) अणु
			अगर (info & IS_E0)
				serio_पूर्णांकerrupt(kbd_dev->hv_serio,
						XTKBD_EMUL0, 0);
			अगर (info & IS_E1)
				serio_पूर्णांकerrupt(kbd_dev->hv_serio,
						XTKBD_EMUL1, 0);
			scan_code = __le16_to_cpu(ks_msg->make_code);
			अगर (info & IS_BREAK)
				scan_code |= XTKBD_RELEASE;

			serio_पूर्णांकerrupt(kbd_dev->hv_serio, scan_code, 0);
		पूर्ण
		spin_unlock_irqrestore(&kbd_dev->lock, flags);

		/*
		 * Only trigger a wakeup on key करोwn, otherwise
		 * "echo freeze > /sys/power/state" can't really enter the
		 * state because the Enter-UP can trigger a wakeup at once.
		 */
		अगर (!(info & IS_BREAK))
			pm_wakeup_hard_event(&hv_dev->device);

		अवरोध;

	शेष:
		dev_err(&hv_dev->device,
			"unhandled message type %d\n", msg_type);
	पूर्ण
पूर्ण

अटल व्योम hv_kbd_handle_received_packet(काष्ठा hv_device *hv_dev,
					  काष्ठा vmpacket_descriptor *desc,
					  u32 bytes_recvd,
					  u64 req_id)
अणु
	काष्ठा synth_kbd_msg *msg;
	u32 msg_sz;

	चयन (desc->type) अणु
	हाल VM_PKT_COMP:
		अवरोध;

	हाल VM_PKT_DATA_INBAND:
		/*
		 * We have a packet that has "inband" data. The API used
		 * क्रम retrieving the packet guarantees that the complete
		 * packet is पढ़ो. So, minimally, we should be able to
		 * parse the payload header safely (assuming that the host
		 * can be trusted.  Trusting the host seems to be a
		 * reasonable assumption because in a भवized
		 * environment there is not whole lot you can करो अगर you
		 * करोn't trust the host.
		 *
		 * Nonetheless, let us validate अगर the host can be trusted
		 * (in a trivial way).  The पूर्णांकeresting aspect of this
		 * validation is how करो you recover अगर we discover that the
		 * host is not to be trusted? Simply dropping the packet, I
		 * करोn't think is an appropriate recovery.  In the पूर्णांकerest
		 * of failing fast, it may be better to crash the guest.
		 * For now, I will just drop the packet!
		 */

		msg_sz = bytes_recvd - (desc->offset8 << 3);
		अगर (msg_sz <= माप(काष्ठा synth_kbd_msg_hdr)) अणु
			/*
			 * Drop the packet and hope
			 * the problem magically goes away.
			 */
			dev_err(&hv_dev->device,
				"Illegal packet (type: %d, tid: %llx, size: %d)\n",
				desc->type, req_id, msg_sz);
			अवरोध;
		पूर्ण

		msg = (व्योम *)desc + (desc->offset8 << 3);
		hv_kbd_on_receive(hv_dev, msg, msg_sz);
		अवरोध;

	शेष:
		dev_err(&hv_dev->device,
			"unhandled packet type %d, tid %llx len %d\n",
			desc->type, req_id, bytes_recvd);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम hv_kbd_on_channel_callback(व्योम *context)
अणु
	काष्ठा vmpacket_descriptor *desc;
	काष्ठा hv_device *hv_dev = context;
	u32 bytes_recvd;
	u64 req_id;

	क्रमeach_vmbus_pkt(desc, hv_dev->channel) अणु
		bytes_recvd = desc->len8 * 8;
		req_id = desc->trans_id;

		hv_kbd_handle_received_packet(hv_dev, desc, bytes_recvd,
					      req_id);
	पूर्ण
पूर्ण

अटल पूर्णांक hv_kbd_connect_to_vsp(काष्ठा hv_device *hv_dev)
अणु
	काष्ठा hv_kbd_dev *kbd_dev = hv_get_drvdata(hv_dev);
	काष्ठा synth_kbd_protocol_request *request;
	काष्ठा synth_kbd_protocol_response *response;
	u32 proto_status;
	पूर्णांक error;

	reinit_completion(&kbd_dev->रुको_event);

	request = &kbd_dev->protocol_req;
	स_रखो(request, 0, माप(काष्ठा synth_kbd_protocol_request));
	request->header.type = __cpu_to_le32(SYNTH_KBD_PROTOCOL_REQUEST);
	request->version_requested.version = __cpu_to_le32(SYNTH_KBD_VERSION);

	error = vmbus_sendpacket(hv_dev->channel, request,
				 माप(काष्ठा synth_kbd_protocol_request),
				 (अचिन्हित दीर्घ)request,
				 VM_PKT_DATA_INBAND,
				 VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (error)
		वापस error;

	अगर (!रुको_क्रम_completion_समयout(&kbd_dev->रुको_event, 10 * HZ))
		वापस -ETIMEDOUT;

	response = &kbd_dev->protocol_resp;
	proto_status = __le32_to_cpu(response->proto_status);
	अगर (!(proto_status & PROTOCOL_ACCEPTED)) अणु
		dev_err(&hv_dev->device,
			"synth_kbd protocol request failed (version %d)\n",
		        SYNTH_KBD_VERSION);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hv_kbd_start(काष्ठा serio *serio)
अणु
	काष्ठा hv_kbd_dev *kbd_dev = serio->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kbd_dev->lock, flags);
	kbd_dev->started = true;
	spin_unlock_irqrestore(&kbd_dev->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम hv_kbd_stop(काष्ठा serio *serio)
अणु
	काष्ठा hv_kbd_dev *kbd_dev = serio->port_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kbd_dev->lock, flags);
	kbd_dev->started = false;
	spin_unlock_irqrestore(&kbd_dev->lock, flags);
पूर्ण

अटल पूर्णांक hv_kbd_probe(काष्ठा hv_device *hv_dev,
			स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	काष्ठा hv_kbd_dev *kbd_dev;
	काष्ठा serio *hv_serio;
	पूर्णांक error;

	kbd_dev = kzalloc(माप(काष्ठा hv_kbd_dev), GFP_KERNEL);
	hv_serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!kbd_dev || !hv_serio) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	kbd_dev->hv_dev = hv_dev;
	kbd_dev->hv_serio = hv_serio;
	spin_lock_init(&kbd_dev->lock);
	init_completion(&kbd_dev->रुको_event);
	hv_set_drvdata(hv_dev, kbd_dev);

	hv_serio->dev.parent  = &hv_dev->device;
	hv_serio->id.type = SERIO_8042_XL;
	hv_serio->port_data = kbd_dev;
	strlcpy(hv_serio->name, dev_name(&hv_dev->device),
		माप(hv_serio->name));
	strlcpy(hv_serio->phys, dev_name(&hv_dev->device),
		माप(hv_serio->phys));

	hv_serio->start = hv_kbd_start;
	hv_serio->stop = hv_kbd_stop;

	error = vmbus_खोलो(hv_dev->channel,
			   KBD_VSC_SEND_RING_BUFFER_SIZE,
			   KBD_VSC_RECV_RING_BUFFER_SIZE,
			   शून्य, 0,
			   hv_kbd_on_channel_callback,
			   hv_dev);
	अगर (error)
		जाओ err_मुक्त_mem;

	error = hv_kbd_connect_to_vsp(hv_dev);
	अगर (error)
		जाओ err_बंद_vmbus;

	serio_रेजिस्टर_port(kbd_dev->hv_serio);

	device_init_wakeup(&hv_dev->device, true);

	वापस 0;

err_बंद_vmbus:
	vmbus_बंद(hv_dev->channel);
err_मुक्त_mem:
	kमुक्त(hv_serio);
	kमुक्त(kbd_dev);
	वापस error;
पूर्ण

अटल पूर्णांक hv_kbd_हटाओ(काष्ठा hv_device *hv_dev)
अणु
	काष्ठा hv_kbd_dev *kbd_dev = hv_get_drvdata(hv_dev);

	serio_unरेजिस्टर_port(kbd_dev->hv_serio);
	vmbus_बंद(hv_dev->channel);
	kमुक्त(kbd_dev);

	hv_set_drvdata(hv_dev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक hv_kbd_suspend(काष्ठा hv_device *hv_dev)
अणु
	vmbus_बंद(hv_dev->channel);

	वापस 0;
पूर्ण

अटल पूर्णांक hv_kbd_resume(काष्ठा hv_device *hv_dev)
अणु
	पूर्णांक ret;

	ret = vmbus_खोलो(hv_dev->channel,
			 KBD_VSC_SEND_RING_BUFFER_SIZE,
			 KBD_VSC_RECV_RING_BUFFER_SIZE,
			 शून्य, 0,
			 hv_kbd_on_channel_callback,
			 hv_dev);
	अगर (ret == 0)
		ret = hv_kbd_connect_to_vsp(hv_dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hv_vmbus_device_id id_table[] = अणु
	/* Keyboard guid */
	अणु HV_KBD_GUID, पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(vmbus, id_table);

अटल काष्ठा  hv_driver hv_kbd_drv = अणु
	.name = KBUILD_MODNAME,
	.id_table = id_table,
	.probe = hv_kbd_probe,
	.हटाओ = hv_kbd_हटाओ,
	.suspend = hv_kbd_suspend,
	.resume = hv_kbd_resume,
	.driver = अणु
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init hv_kbd_init(व्योम)
अणु
	वापस vmbus_driver_रेजिस्टर(&hv_kbd_drv);
पूर्ण

अटल व्योम __निकास hv_kbd_निकास(व्योम)
अणु
	vmbus_driver_unरेजिस्टर(&hv_kbd_drv);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Microsoft Hyper-V Synthetic Keyboard Driver");

module_init(hv_kbd_init);
module_निकास(hv_kbd_निकास);
