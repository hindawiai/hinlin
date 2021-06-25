<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (c) 2009, Citrix Systems, Inc.
 *  Copyright (c) 2010, Microsoft Corporation.
 *  Copyright (c) 2011, Novell Inc.
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/completion.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/hiddev.h>
#समावेश <linux/hyperv.h>


काष्ठा hv_input_dev_info अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित लघु venकरोr;
	अचिन्हित लघु product;
	अचिन्हित लघु version;
	अचिन्हित लघु reserved[11];
पूर्ण;

/* The maximum size of a synthetic input message. */
#घोषणा SYNTHHID_MAX_INPUT_REPORT_SIZE 16

/*
 * Current version
 *
 * History:
 * Beta, RC < 2008/1/22        1,0
 * RC > 2008/1/22              2,0
 */
#घोषणा SYNTHHID_INPUT_VERSION_MAJOR	2
#घोषणा SYNTHHID_INPUT_VERSION_MINOR	0
#घोषणा SYNTHHID_INPUT_VERSION		(SYNTHHID_INPUT_VERSION_MINOR | \
					 (SYNTHHID_INPUT_VERSION_MAJOR << 16))


#आशय pack(push, 1)
/*
 * Message types in the synthetic input protocol
 */
क्रमागत synthhid_msg_type अणु
	SYNTH_HID_PROTOCOL_REQUEST,
	SYNTH_HID_PROTOCOL_RESPONSE,
	SYNTH_HID_INITIAL_DEVICE_INFO,
	SYNTH_HID_INITIAL_DEVICE_INFO_ACK,
	SYNTH_HID_INPUT_REPORT,
	SYNTH_HID_MAX
पूर्ण;

/*
 * Basic message काष्ठाures.
 */
काष्ठा synthhid_msg_hdr अणु
	क्रमागत synthhid_msg_type type;
	u32 size;
पूर्ण;

काष्ठा synthhid_msg अणु
	काष्ठा synthhid_msg_hdr header;
	अक्षर data[1]; /* Enबंदd message */
पूर्ण;

जोड़ synthhid_version अणु
	काष्ठा अणु
		u16 minor_version;
		u16 major_version;
	पूर्ण;
	u32 version;
पूर्ण;

/*
 * Protocol messages
 */
काष्ठा synthhid_protocol_request अणु
	काष्ठा synthhid_msg_hdr header;
	जोड़ synthhid_version version_requested;
पूर्ण;

काष्ठा synthhid_protocol_response अणु
	काष्ठा synthhid_msg_hdr header;
	जोड़ synthhid_version version_requested;
	अचिन्हित अक्षर approved;
पूर्ण;

काष्ठा synthhid_device_info अणु
	काष्ठा synthhid_msg_hdr header;
	काष्ठा hv_input_dev_info hid_dev_info;
	काष्ठा hid_descriptor hid_descriptor;
पूर्ण;

काष्ठा synthhid_device_info_ack अणु
	काष्ठा synthhid_msg_hdr header;
	अचिन्हित अक्षर reserved;
पूर्ण;

काष्ठा synthhid_input_report अणु
	काष्ठा synthhid_msg_hdr header;
	अक्षर buffer[1];
पूर्ण;

#आशय pack(pop)

#घोषणा INPUTVSC_SEND_RING_BUFFER_SIZE	VMBUS_RING_SIZE(36 * 1024)
#घोषणा INPUTVSC_RECV_RING_BUFFER_SIZE	VMBUS_RING_SIZE(36 * 1024)


क्रमागत pipe_prot_msg_type अणु
	PIPE_MESSAGE_INVALID,
	PIPE_MESSAGE_DATA,
	PIPE_MESSAGE_MAXIMUM
पूर्ण;


काष्ठा pipe_prt_msg अणु
	क्रमागत pipe_prot_msg_type type;
	u32 size;
	अक्षर data[1];
पूर्ण;

काष्ठा  mousevsc_prt_msg अणु
	क्रमागत pipe_prot_msg_type type;
	u32 size;
	जोड़ अणु
		काष्ठा synthhid_protocol_request request;
		काष्ठा synthhid_protocol_response response;
		काष्ठा synthhid_device_info_ack ack;
	पूर्ण;
पूर्ण;

/*
 * Represents an mousevsc device
 */
काष्ठा mousevsc_dev अणु
	काष्ठा hv_device	*device;
	bool			init_complete;
	bool			connected;
	काष्ठा mousevsc_prt_msg	protocol_req;
	काष्ठा mousevsc_prt_msg	protocol_resp;
	/* Synchronize the request/response अगर needed */
	काष्ठा completion	रुको_event;
	पूर्णांक			dev_info_status;

	काष्ठा hid_descriptor	*hid_desc;
	अचिन्हित अक्षर		*report_desc;
	u32			report_desc_size;
	काष्ठा hv_input_dev_info hid_dev_info;
	काष्ठा hid_device       *hid_device;
	u8			input_buf[HID_MAX_BUFFER_SIZE];
पूर्ण;


अटल काष्ठा mousevsc_dev *mousevsc_alloc_device(काष्ठा hv_device *device)
अणु
	काष्ठा mousevsc_dev *input_dev;

	input_dev = kzalloc(माप(काष्ठा mousevsc_dev), GFP_KERNEL);

	अगर (!input_dev)
		वापस शून्य;

	input_dev->device = device;
	hv_set_drvdata(device, input_dev);
	init_completion(&input_dev->रुको_event);
	input_dev->init_complete = false;

	वापस input_dev;
पूर्ण

अटल व्योम mousevsc_मुक्त_device(काष्ठा mousevsc_dev *device)
अणु
	kमुक्त(device->hid_desc);
	kमुक्त(device->report_desc);
	hv_set_drvdata(device->device, शून्य);
	kमुक्त(device);
पूर्ण

अटल व्योम mousevsc_on_receive_device_info(काष्ठा mousevsc_dev *input_device,
				काष्ठा synthhid_device_info *device_info)
अणु
	पूर्णांक ret = 0;
	काष्ठा hid_descriptor *desc;
	काष्ठा mousevsc_prt_msg ack;

	input_device->dev_info_status = -ENOMEM;

	input_device->hid_dev_info = device_info->hid_dev_info;
	desc = &device_info->hid_descriptor;
	अगर (desc->bLength == 0)
		जाओ cleanup;

	/* The poपूर्णांकer is not शून्य when we resume from hibernation */
	kमुक्त(input_device->hid_desc);
	input_device->hid_desc = kmemdup(desc, desc->bLength, GFP_ATOMIC);

	अगर (!input_device->hid_desc)
		जाओ cleanup;

	input_device->report_desc_size = desc->desc[0].wDescriptorLength;
	अगर (input_device->report_desc_size == 0) अणु
		input_device->dev_info_status = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/* The poपूर्णांकer is not शून्य when we resume from hibernation */
	kमुक्त(input_device->report_desc);
	input_device->report_desc = kzalloc(input_device->report_desc_size,
					  GFP_ATOMIC);

	अगर (!input_device->report_desc) अणु
		input_device->dev_info_status = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	स_नकल(input_device->report_desc,
	       ((अचिन्हित अक्षर *)desc) + desc->bLength,
	       desc->desc[0].wDescriptorLength);

	/* Send the ack */
	स_रखो(&ack, 0, माप(काष्ठा mousevsc_prt_msg));

	ack.type = PIPE_MESSAGE_DATA;
	ack.size = माप(काष्ठा synthhid_device_info_ack);

	ack.ack.header.type = SYNTH_HID_INITIAL_DEVICE_INFO_ACK;
	ack.ack.header.size = 1;
	ack.ack.reserved = 0;

	ret = vmbus_sendpacket(input_device->device->channel,
			&ack,
			माप(काष्ठा pipe_prt_msg) - माप(अचिन्हित अक्षर) +
			माप(काष्ठा synthhid_device_info_ack),
			(अचिन्हित दीर्घ)&ack,
			VM_PKT_DATA_INBAND,
			VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);

	अगर (!ret)
		input_device->dev_info_status = 0;

cleanup:
	complete(&input_device->रुको_event);

	वापस;
पूर्ण

अटल व्योम mousevsc_on_receive(काष्ठा hv_device *device,
				काष्ठा vmpacket_descriptor *packet)
अणु
	काष्ठा pipe_prt_msg *pipe_msg;
	काष्ठा synthhid_msg *hid_msg;
	काष्ठा mousevsc_dev *input_dev = hv_get_drvdata(device);
	काष्ठा synthhid_input_report *input_report;
	माप_प्रकार len;

	pipe_msg = (काष्ठा pipe_prt_msg *)((अचिन्हित दीर्घ)packet +
						(packet->offset8 << 3));

	अगर (pipe_msg->type != PIPE_MESSAGE_DATA)
		वापस;

	hid_msg = (काष्ठा synthhid_msg *)pipe_msg->data;

	चयन (hid_msg->header.type) अणु
	हाल SYNTH_HID_PROTOCOL_RESPONSE:
		/*
		 * While it will be impossible क्रम us to protect against
		 * malicious/buggy hypervisor/host, add a check here to
		 * ensure we करोn't corrupt memory.
		 */
		अगर ((pipe_msg->size + माप(काष्ठा pipe_prt_msg)
			- माप(अचिन्हित अक्षर))
			> माप(काष्ठा mousevsc_prt_msg)) अणु
			WARN_ON(1);
			अवरोध;
		पूर्ण

		स_नकल(&input_dev->protocol_resp, pipe_msg,
		       pipe_msg->size + माप(काष्ठा pipe_prt_msg) -
		       माप(अचिन्हित अक्षर));
		complete(&input_dev->रुको_event);
		अवरोध;

	हाल SYNTH_HID_INITIAL_DEVICE_INFO:
		WARN_ON(pipe_msg->size < माप(काष्ठा hv_input_dev_info));

		/*
		 * Parse out the device info पूर्णांकo device attr,
		 * hid desc and report desc
		 */
		mousevsc_on_receive_device_info(input_dev,
			(काष्ठा synthhid_device_info *)pipe_msg->data);
		अवरोध;
	हाल SYNTH_HID_INPUT_REPORT:
		input_report =
			(काष्ठा synthhid_input_report *)pipe_msg->data;
		अगर (!input_dev->init_complete)
			अवरोध;

		len = min(input_report->header.size,
			  (u32)माप(input_dev->input_buf));
		स_नकल(input_dev->input_buf, input_report->buffer, len);
		hid_input_report(input_dev->hid_device, HID_INPUT_REPORT,
				 input_dev->input_buf, len, 1);

		pm_wakeup_hard_event(&input_dev->device->device);

		अवरोध;
	शेष:
		pr_err("unsupported hid msg type - type %d len %d\n",
		       hid_msg->header.type, hid_msg->header.size);
		अवरोध;
	पूर्ण

पूर्ण

अटल व्योम mousevsc_on_channel_callback(व्योम *context)
अणु
	काष्ठा hv_device *device = context;
	काष्ठा vmpacket_descriptor *desc;

	क्रमeach_vmbus_pkt(desc, device->channel) अणु
		चयन (desc->type) अणु
		हाल VM_PKT_COMP:
			अवरोध;

		हाल VM_PKT_DATA_INBAND:
			mousevsc_on_receive(device, desc);
			अवरोध;

		शेष:
			pr_err("Unhandled packet type %d, tid %llx len %d\n",
			       desc->type, desc->trans_id, desc->len8 * 8);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mousevsc_connect_to_vsp(काष्ठा hv_device *device)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ t;
	काष्ठा mousevsc_dev *input_dev = hv_get_drvdata(device);
	काष्ठा mousevsc_prt_msg *request;
	काष्ठा mousevsc_prt_msg *response;

	reinit_completion(&input_dev->रुको_event);

	request = &input_dev->protocol_req;
	स_रखो(request, 0, माप(काष्ठा mousevsc_prt_msg));

	request->type = PIPE_MESSAGE_DATA;
	request->size = माप(काष्ठा synthhid_protocol_request);
	request->request.header.type = SYNTH_HID_PROTOCOL_REQUEST;
	request->request.header.size = माप(अचिन्हित पूर्णांक);
	request->request.version_requested.version = SYNTHHID_INPUT_VERSION;

	ret = vmbus_sendpacket(device->channel, request,
				माप(काष्ठा pipe_prt_msg) -
				माप(अचिन्हित अक्षर) +
				माप(काष्ठा synthhid_protocol_request),
				(अचिन्हित दीर्घ)request,
				VM_PKT_DATA_INBAND,
				VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret)
		जाओ cleanup;

	t = रुको_क्रम_completion_समयout(&input_dev->रुको_event, 5*HZ);
	अगर (!t) अणु
		ret = -ETIMEDOUT;
		जाओ cleanup;
	पूर्ण

	response = &input_dev->protocol_resp;

	अगर (!response->response.approved) अणु
		pr_err("synthhid protocol request failed (version %d)\n",
		       SYNTHHID_INPUT_VERSION);
		ret = -ENODEV;
		जाओ cleanup;
	पूर्ण

	t = रुको_क्रम_completion_समयout(&input_dev->रुको_event, 5*HZ);
	अगर (!t) अणु
		ret = -ETIMEDOUT;
		जाओ cleanup;
	पूर्ण

	/*
	 * We should have gotten the device attr, hid desc and report
	 * desc at this poपूर्णांक
	 */
	ret = input_dev->dev_info_status;

cleanup:
	वापस ret;
पूर्ण

अटल पूर्णांक mousevsc_hid_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा hv_device *dev = hid_get_drvdata(hid);
	काष्ठा mousevsc_dev *input_dev = hv_get_drvdata(dev);

	वापस hid_parse_report(hid, input_dev->report_desc,
				input_dev->report_desc_size);
पूर्ण

अटल पूर्णांक mousevsc_hid_खोलो(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mousevsc_hid_start(काष्ठा hid_device *hid)
अणु
	वापस 0;
पूर्ण

अटल व्योम mousevsc_hid_बंद(काष्ठा hid_device *hid)
अणु
पूर्ण

अटल व्योम mousevsc_hid_stop(काष्ठा hid_device *hid)
अणु
पूर्ण

अटल पूर्णांक mousevsc_hid_raw_request(काष्ठा hid_device *hid,
				    अचिन्हित अक्षर report_num,
				    __u8 *buf, माप_प्रकार len,
				    अचिन्हित अक्षर rtype,
				    पूर्णांक reqtype)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा hid_ll_driver mousevsc_ll_driver = अणु
	.parse = mousevsc_hid_parse,
	.खोलो = mousevsc_hid_खोलो,
	.बंद = mousevsc_hid_बंद,
	.start = mousevsc_hid_start,
	.stop = mousevsc_hid_stop,
	.raw_request = mousevsc_hid_raw_request,
पूर्ण;

अटल काष्ठा hid_driver mousevsc_hid_driver;

अटल पूर्णांक mousevsc_probe(काष्ठा hv_device *device,
			स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	पूर्णांक ret;
	काष्ठा mousevsc_dev *input_dev;
	काष्ठा hid_device *hid_dev;

	input_dev = mousevsc_alloc_device(device);

	अगर (!input_dev)
		वापस -ENOMEM;

	ret = vmbus_खोलो(device->channel,
		INPUTVSC_SEND_RING_BUFFER_SIZE,
		INPUTVSC_RECV_RING_BUFFER_SIZE,
		शून्य,
		0,
		mousevsc_on_channel_callback,
		device
		);

	अगर (ret)
		जाओ probe_err0;

	ret = mousevsc_connect_to_vsp(device);

	अगर (ret)
		जाओ probe_err1;

	/* workaround SA-167 */
	अगर (input_dev->report_desc[14] == 0x25)
		input_dev->report_desc[14] = 0x29;

	hid_dev = hid_allocate_device();
	अगर (IS_ERR(hid_dev)) अणु
		ret = PTR_ERR(hid_dev);
		जाओ probe_err1;
	पूर्ण

	hid_dev->ll_driver = &mousevsc_ll_driver;
	hid_dev->driver = &mousevsc_hid_driver;
	hid_dev->bus = BUS_VIRTUAL;
	hid_dev->venकरोr = input_dev->hid_dev_info.venकरोr;
	hid_dev->product = input_dev->hid_dev_info.product;
	hid_dev->version = input_dev->hid_dev_info.version;
	input_dev->hid_device = hid_dev;

	प्र_लिखो(hid_dev->name, "%s", "Microsoft Vmbus HID-compliant Mouse");

	hid_set_drvdata(hid_dev, device);

	ret = hid_add_device(hid_dev);
	अगर (ret)
		जाओ probe_err1;


	ret = hid_parse(hid_dev);
	अगर (ret) अणु
		hid_err(hid_dev, "parse failed\n");
		जाओ probe_err2;
	पूर्ण

	ret = hid_hw_start(hid_dev, HID_CONNECT_HIDINPUT | HID_CONNECT_HIDDEV);

	अगर (ret) अणु
		hid_err(hid_dev, "hw start failed\n");
		जाओ probe_err2;
	पूर्ण

	device_init_wakeup(&device->device, true);

	input_dev->connected = true;
	input_dev->init_complete = true;

	वापस ret;

probe_err2:
	hid_destroy_device(hid_dev);

probe_err1:
	vmbus_बंद(device->channel);

probe_err0:
	mousevsc_मुक्त_device(input_dev);

	वापस ret;
पूर्ण


अटल पूर्णांक mousevsc_हटाओ(काष्ठा hv_device *dev)
अणु
	काष्ठा mousevsc_dev *input_dev = hv_get_drvdata(dev);

	device_init_wakeup(&dev->device, false);
	vmbus_बंद(dev->channel);
	hid_hw_stop(input_dev->hid_device);
	hid_destroy_device(input_dev->hid_device);
	mousevsc_मुक्त_device(input_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mousevsc_suspend(काष्ठा hv_device *dev)
अणु
	vmbus_बंद(dev->channel);

	वापस 0;
पूर्ण

अटल पूर्णांक mousevsc_resume(काष्ठा hv_device *dev)
अणु
	पूर्णांक ret;

	ret = vmbus_खोलो(dev->channel,
			 INPUTVSC_SEND_RING_BUFFER_SIZE,
			 INPUTVSC_RECV_RING_BUFFER_SIZE,
			 शून्य, 0,
			 mousevsc_on_channel_callback,
			 dev);
	अगर (ret)
		वापस ret;

	ret = mousevsc_connect_to_vsp(dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hv_vmbus_device_id id_table[] = अणु
	/* Mouse guid */
	अणु HV_MOUSE_GUID, पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(vmbus, id_table);

अटल काष्ठा  hv_driver mousevsc_drv = अणु
	.name = KBUILD_MODNAME,
	.id_table = id_table,
	.probe = mousevsc_probe,
	.हटाओ = mousevsc_हटाओ,
	.suspend = mousevsc_suspend,
	.resume = mousevsc_resume,
	.driver = अणु
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mousevsc_init(व्योम)
अणु
	वापस vmbus_driver_रेजिस्टर(&mousevsc_drv);
पूर्ण

अटल व्योम __निकास mousevsc_निकास(व्योम)
अणु
	vmbus_driver_unरेजिस्टर(&mousevsc_drv);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Microsoft Hyper-V Synthetic HID Driver");

module_init(mousevsc_init);
module_निकास(mousevsc_निकास);
