<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/****************************************************************

Siano Mobile Silicon, Inc.
MDTV receiver kernel modules.
Copyright (C) 2005-2009, Uri Shkolnik, Anम_से_दy Greenblat


****************************************************************/

#समावेश "smscoreapi.h"

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <media/media-device.h>

#समावेश "sms-cards.h"
#समावेश "smsendian.h"

#घोषणा USB1_BUFFER_SIZE		0x1000
#घोषणा USB2_BUFFER_SIZE		0x2000

#घोषणा MAX_BUFFERS		50
#घोषणा MAX_URBS		10

काष्ठा smsusb_device_t;

क्रमागत smsusb_state अणु
	SMSUSB_DISCONNECTED,
	SMSUSB_SUSPENDED,
	SMSUSB_ACTIVE
पूर्ण;

काष्ठा smsusb_urb_t अणु
	काष्ठा list_head entry;
	काष्ठा smscore_buffer_t *cb;
	काष्ठा smsusb_device_t *dev;

	काष्ठा urb urb;

	/* For the bottom half */
	काष्ठा work_काष्ठा wq;
पूर्ण;

काष्ठा smsusb_device_t अणु
	काष्ठा usb_device *udev;
	काष्ठा smscore_device_t *coredev;

	काष्ठा smsusb_urb_t	surbs[MAX_URBS];

	पूर्णांक		response_alignment;
	पूर्णांक		buffer_size;

	अचिन्हित अक्षर in_ep;
	अचिन्हित अक्षर out_ep;
	क्रमागत smsusb_state state;
पूर्ण;

अटल पूर्णांक smsusb_submit_urb(काष्ठा smsusb_device_t *dev,
			     काष्ठा smsusb_urb_t *surb);

/*
 * Completing URB's callback handler - bottom half (process context)
 * submits the URB prepared on smsusb_onresponse()
 */
अटल व्योम करो_submit_urb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smsusb_urb_t *surb = container_of(work, काष्ठा smsusb_urb_t, wq);
	काष्ठा smsusb_device_t *dev = surb->dev;

	smsusb_submit_urb(dev, surb);
पूर्ण

/*
 * Completing URB's callback handler - top half (पूर्णांकerrupt context)
 * adds completing sms urb to the global surbs list and activtes the worker
 * thपढ़ो the surb
 * IMPORTANT - blocking functions must not be called from here !!!

 * @param urb poपूर्णांकer to a completing urb object
 */
अटल व्योम smsusb_onresponse(काष्ठा urb *urb)
अणु
	काष्ठा smsusb_urb_t *surb = (काष्ठा smsusb_urb_t *) urb->context;
	काष्ठा smsusb_device_t *dev = surb->dev;

	अगर (urb->status == -ESHUTDOWN) अणु
		pr_err("error, urb status %d (-ESHUTDOWN), %d bytes\n",
			urb->status, urb->actual_length);
		वापस;
	पूर्ण

	अगर ((urb->actual_length > 0) && (urb->status == 0)) अणु
		काष्ठा sms_msg_hdr *phdr = (काष्ठा sms_msg_hdr *)surb->cb->p;

		smsendian_handle_message_header(phdr);
		अगर (urb->actual_length >= phdr->msg_length) अणु
			surb->cb->size = phdr->msg_length;

			अगर (dev->response_alignment &&
			    (phdr->msg_flags & MSG_HDR_FLAG_SPLIT_MSG)) अणु

				surb->cb->offset =
					dev->response_alignment +
					((phdr->msg_flags >> 8) & 3);

				/* sanity check */
				अगर (((पूर्णांक) phdr->msg_length +
				     surb->cb->offset) > urb->actual_length) अणु
					pr_err("invalid response msglen %d offset %d size %d\n",
						phdr->msg_length,
						surb->cb->offset,
						urb->actual_length);
					जाओ निकास_and_resubmit;
				पूर्ण

				/* move buffer poपूर्णांकer and
				 * copy header to its new location */
				स_नकल((अक्षर *) phdr + surb->cb->offset,
				       phdr, माप(काष्ठा sms_msg_hdr));
			पूर्ण अन्यथा
				surb->cb->offset = 0;

			pr_debug("received %s(%d) size: %d\n",
				  smscore_translate_msg(phdr->msg_type),
				  phdr->msg_type, phdr->msg_length);

			smsendian_handle_rx_message((काष्ठा sms_msg_data *) phdr);

			smscore_onresponse(dev->coredev, surb->cb);
			surb->cb = शून्य;
		पूर्ण अन्यथा अणु
			pr_err("invalid response msglen %d actual %d\n",
				phdr->msg_length, urb->actual_length);
		पूर्ण
	पूर्ण अन्यथा
		pr_err("error, urb status %d, %d bytes\n",
			urb->status, urb->actual_length);


निकास_and_resubmit:
	INIT_WORK(&surb->wq, करो_submit_urb);
	schedule_work(&surb->wq);
पूर्ण

अटल पूर्णांक smsusb_submit_urb(काष्ठा smsusb_device_t *dev,
			     काष्ठा smsusb_urb_t *surb)
अणु
	अगर (!surb->cb) अणु
		/* This function can sleep */
		surb->cb = smscore_getbuffer(dev->coredev);
		अगर (!surb->cb) अणु
			pr_err("smscore_getbuffer(...) returned NULL\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	usb_fill_bulk_urb(
		&surb->urb,
		dev->udev,
		usb_rcvbulkpipe(dev->udev, dev->in_ep),
		surb->cb->p,
		dev->buffer_size,
		smsusb_onresponse,
		surb
	);
	surb->urb.transfer_flags |= URB_FREE_BUFFER;

	वापस usb_submit_urb(&surb->urb, GFP_ATOMIC);
पूर्ण

अटल व्योम smsusb_stop_streaming(काष्ठा smsusb_device_t *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_URBS; i++) अणु
		usb_समाप्त_urb(&dev->surbs[i].urb);

		अगर (dev->surbs[i].cb) अणु
			smscore_putbuffer(dev->coredev, dev->surbs[i].cb);
			dev->surbs[i].cb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक smsusb_start_streaming(काष्ठा smsusb_device_t *dev)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < MAX_URBS; i++) अणु
		rc = smsusb_submit_urb(dev, &dev->surbs[i]);
		अगर (rc < 0) अणु
			pr_err("smsusb_submit_urb(...) failed\n");
			smsusb_stop_streaming(dev);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक smsusb_sendrequest(व्योम *context, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा smsusb_device_t *dev = (काष्ठा smsusb_device_t *) context;
	काष्ठा sms_msg_hdr *phdr;
	पूर्णांक dummy, ret;

	अगर (dev->state != SMSUSB_ACTIVE) अणु
		pr_debug("Device not active yet\n");
		वापस -ENOENT;
	पूर्ण

	phdr = kmemdup(buffer, size, GFP_KERNEL);
	अगर (!phdr)
		वापस -ENOMEM;

	pr_debug("sending %s(%d) size: %d\n",
		  smscore_translate_msg(phdr->msg_type), phdr->msg_type,
		  phdr->msg_length);

	smsendian_handle_tx_message((काष्ठा sms_msg_data *) phdr);
	smsendian_handle_message_header((काष्ठा sms_msg_hdr *)phdr);
	ret = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 2),
			    phdr, size, &dummy, 1000);

	kमुक्त(phdr);
	वापस ret;
पूर्ण

अटल अक्षर *smsusb1_fw_lkup[] = अणु
	"dvbt_stellar_usb.inp",
	"dvbh_stellar_usb.inp",
	"tdmb_stellar_usb.inp",
	"none",
	"dvbt_bda_stellar_usb.inp",
पूर्ण;

अटल अंतरभूत अक्षर *sms_get_fw_name(पूर्णांक mode, पूर्णांक board_id)
अणु
	अक्षर **fw = sms_get_board(board_id)->fw;
	वापस (fw && fw[mode]) ? fw[mode] : smsusb1_fw_lkup[mode];
पूर्ण

अटल पूर्णांक smsusb1_load_firmware(काष्ठा usb_device *udev, पूर्णांक id, पूर्णांक board_id)
अणु
	स्थिर काष्ठा firmware *fw;
	u8 *fw_buffer;
	पूर्णांक rc, dummy;
	अक्षर *fw_filename;

	अगर (id < 0)
		id = sms_get_board(board_id)->शेष_mode;

	अगर (id < DEVICE_MODE_DVBT || id > DEVICE_MODE_DVBT_BDA) अणु
		pr_err("invalid firmware id specified %d\n", id);
		वापस -EINVAL;
	पूर्ण

	fw_filename = sms_get_fw_name(id, board_id);

	rc = request_firmware(&fw, fw_filename, &udev->dev);
	अगर (rc < 0) अणु
		pr_warn("failed to open '%s' mode %d, trying again with default firmware\n",
			fw_filename, id);

		fw_filename = smsusb1_fw_lkup[id];
		rc = request_firmware(&fw, fw_filename, &udev->dev);
		अगर (rc < 0) अणु
			pr_warn("failed to open '%s' mode %d\n",
				 fw_filename, id);

			वापस rc;
		पूर्ण
	पूर्ण

	fw_buffer = kदो_स्मृति(fw->size, GFP_KERNEL);
	अगर (fw_buffer) अणु
		स_नकल(fw_buffer, fw->data, fw->size);

		rc = usb_bulk_msg(udev, usb_sndbulkpipe(udev, 2),
				  fw_buffer, fw->size, &dummy, 1000);

		pr_debug("sent %zu(%d) bytes, rc %d\n", fw->size, dummy, rc);

		kमुक्त(fw_buffer);
	पूर्ण अन्यथा अणु
		pr_err("failed to allocate firmware buffer\n");
		rc = -ENOMEM;
	पूर्ण
	pr_debug("read FW %s, size=%zu\n", fw_filename, fw->size);

	release_firmware(fw);

	वापस rc;
पूर्ण

अटल व्योम smsusb1_detecपंचांगode(व्योम *context, पूर्णांक *mode)
अणु
	अक्षर *product_string =
		((काष्ठा smsusb_device_t *) context)->udev->product;

	*mode = DEVICE_MODE_NONE;

	अगर (!product_string) अणु
		product_string = "none";
		pr_err("product string not found\n");
	पूर्ण अन्यथा अगर (म_माला(product_string, "DVBH"))
		*mode = 1;
	अन्यथा अगर (म_माला(product_string, "BDA"))
		*mode = 4;
	अन्यथा अगर (म_माला(product_string, "DVBT"))
		*mode = 0;
	अन्यथा अगर (म_माला(product_string, "TDMB"))
		*mode = 2;

	pr_debug("%d \"%s\"\n", *mode, product_string);
पूर्ण

अटल पूर्णांक smsusb1_seपंचांगode(व्योम *context, पूर्णांक mode)
अणु
	काष्ठा sms_msg_hdr msg = अणु MSG_SW_RELOAD_REQ, 0, HIF_TASK,
			     माप(काष्ठा sms_msg_hdr), 0 पूर्ण;

	अगर (mode < DEVICE_MODE_DVBT || mode > DEVICE_MODE_DVBT_BDA) अणु
		pr_err("invalid firmware id specified %d\n", mode);
		वापस -EINVAL;
	पूर्ण

	वापस smsusb_sendrequest(context, &msg, माप(msg));
पूर्ण

अटल व्योम smsusb_term_device(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा smsusb_device_t *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (dev) अणु
		dev->state = SMSUSB_DISCONNECTED;

		smsusb_stop_streaming(dev);

		/* unरेजिस्टर from smscore */
		अगर (dev->coredev)
			smscore_unरेजिस्टर_device(dev->coredev);

		pr_debug("device 0x%p destroyed\n", dev);
		kमुक्त(dev);
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

अटल व्योम *siano_media_device_रेजिस्टर(काष्ठा smsusb_device_t *dev,
					पूर्णांक board_id)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	काष्ठा media_device *mdev;
	काष्ठा usb_device *udev = dev->udev;
	काष्ठा sms_board *board = sms_get_board(board_id);
	पूर्णांक ret;

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev)
		वापस शून्य;

	media_device_usb_init(mdev, udev, board->name);

	ret = media_device_रेजिस्टर(mdev);
	अगर (ret) अणु
		media_device_cleanup(mdev);
		kमुक्त(mdev);
		वापस शून्य;
	पूर्ण

	pr_info("media controller created\n");

	वापस mdev;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक smsusb_init_device(काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक board_id)
अणु
	काष्ठा smsdevice_params_t params;
	काष्ठा smsusb_device_t *dev;
	व्योम *mdev;
	पूर्णांक i, rc;
	पूर्णांक align = 0;

	/* create device object */
	dev = kzalloc(माप(काष्ठा smsusb_device_t), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	स_रखो(&params, 0, माप(params));
	usb_set_पूर्णांकfdata(पूर्णांकf, dev);
	dev->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	dev->state = SMSUSB_DISCONNECTED;

	क्रम (i = 0; i < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; i++) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor *desc =
				&पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc;

		अगर (desc->bEndpoपूर्णांकAddress & USB_सूची_IN) अणु
			dev->in_ep = desc->bEndpoपूर्णांकAddress;
			align = usb_endpoपूर्णांक_maxp(desc) - माप(काष्ठा sms_msg_hdr);
		पूर्ण अन्यथा अणु
			dev->out_ep = desc->bEndpoपूर्णांकAddress;
		पूर्ण
	पूर्ण

	pr_debug("in_ep = %02x, out_ep = %02x\n", dev->in_ep, dev->out_ep);
	अगर (!dev->in_ep || !dev->out_ep || align < 0) अणु  /* Missing endpoपूर्णांकs? */
		smsusb_term_device(पूर्णांकf);
		वापस -ENODEV;
	पूर्ण

	params.device_type = sms_get_board(board_id)->type;

	चयन (params.device_type) अणु
	हाल SMS_STELLAR:
		dev->buffer_size = USB1_BUFFER_SIZE;

		params.seपंचांगode_handler = smsusb1_seपंचांगode;
		params.detecपंचांगode_handler = smsusb1_detecपंचांगode;
		अवरोध;
	हाल SMS_UNKNOWN_TYPE:
		pr_err("Unspecified sms device type!\n");
		fallthrough;
	शेष:
		dev->buffer_size = USB2_BUFFER_SIZE;
		dev->response_alignment = align;

		params.flags |= SMS_DEVICE_FAMILY2;
		अवरोध;
	पूर्ण

	params.device = &dev->udev->dev;
	params.usb_device = dev->udev;
	params.buffer_size = dev->buffer_size;
	params.num_buffers = MAX_BUFFERS;
	params.sendrequest_handler = smsusb_sendrequest;
	params.context = dev;
	usb_make_path(dev->udev, params.devpath, माप(params.devpath));

	mdev = siano_media_device_रेजिस्टर(dev, board_id);

	/* रेजिस्टर in smscore */
	rc = smscore_रेजिस्टर_device(&params, &dev->coredev, 0, mdev);
	अगर (rc < 0) अणु
		pr_err("smscore_register_device(...) failed, rc %d\n", rc);
		smsusb_term_device(पूर्णांकf);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
		media_device_unरेजिस्टर(mdev);
#पूर्ण_अगर
		kमुक्त(mdev);
		वापस rc;
	पूर्ण

	smscore_set_board_id(dev->coredev, board_id);

	dev->coredev->is_usb_device = true;

	/* initialize urbs */
	क्रम (i = 0; i < MAX_URBS; i++) अणु
		dev->surbs[i].dev = dev;
		usb_init_urb(&dev->surbs[i].urb);
	पूर्ण

	pr_debug("smsusb_start_streaming(...).\n");
	rc = smsusb_start_streaming(dev);
	अगर (rc < 0) अणु
		pr_err("smsusb_start_streaming(...) failed\n");
		smsusb_term_device(पूर्णांकf);
		वापस rc;
	पूर्ण

	dev->state = SMSUSB_ACTIVE;

	rc = smscore_start_device(dev->coredev);
	अगर (rc < 0) अणु
		pr_err("smscore_start_device(...) failed\n");
		smsusb_term_device(पूर्णांकf);
		वापस rc;
	पूर्ण

	pr_debug("device 0x%p created\n", dev);

	वापस rc;
पूर्ण

अटल पूर्णांक smsusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	अक्षर devpath[32];
	पूर्णांक i, rc;

	pr_info("board id=%lu, interface number %d\n",
		 id->driver_info,
		 पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);

	अगर (sms_get_board(id->driver_info)->पूर्णांकf_num !=
	    पूर्णांकf->cur_altsetting->desc.bInterfaceNumber) अणु
		pr_debug("interface %d won't be used. Expecting interface %d to popup\n",
			पूर्णांकf->cur_altsetting->desc.bInterfaceNumber,
			sms_get_board(id->driver_info)->पूर्णांकf_num);
		वापस -ENODEV;
	पूर्ण

	अगर (पूर्णांकf->num_altsetting > 1) अणु
		rc = usb_set_पूर्णांकerface(udev,
				       पूर्णांकf->cur_altsetting->desc.bInterfaceNumber,
				       0);
		अगर (rc < 0) अणु
			pr_err("usb_set_interface failed, rc %d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	pr_debug("smsusb_probe %d\n",
	       पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);
	क्रम (i = 0; i < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; i++) अणु
		pr_debug("endpoint %d %02x %02x %d\n", i,
		       पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress,
		       पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc.bmAttributes,
		       पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc.wMaxPacketSize);
		अगर (पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress &
		    USB_सूची_IN)
			rc = usb_clear_halt(udev, usb_rcvbulkpipe(udev,
				पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress));
		अन्यथा
			rc = usb_clear_halt(udev, usb_sndbulkpipe(udev,
				पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress));
	पूर्ण
	अगर ((udev->actconfig->desc.bNumInterfaces == 2) &&
	    (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber == 0)) अणु
		pr_debug("rom interface 0 is not used\n");
		वापस -ENODEV;
	पूर्ण

	अगर (id->driver_info == SMS1XXX_BOARD_SIANO_STELLAR_ROM) अणु
		/* Detected a Siano Stellar uninitialized */

		snम_लिखो(devpath, माप(devpath), "usb\\%d-%s",
			 udev->bus->busnum, udev->devpath);
		pr_info("stellar device in cold state was found at %s.\n",
			devpath);
		rc = smsusb1_load_firmware(
				udev, smscore_registry_geपंचांगode(devpath),
				id->driver_info);

		/* This device will reset and gain another USB ID */
		अगर (!rc)
			pr_info("stellar device now in warm state\n");
		अन्यथा
			pr_err("Failed to put stellar in warm state. Error: %d\n",
			       rc);

		वापस rc;
	पूर्ण अन्यथा अणु
		rc = smsusb_init_device(पूर्णांकf, id->driver_info);
	पूर्ण

	pr_info("Device initialized with return code %d\n", rc);
	sms_board_load_modules(id->driver_info);
	वापस rc;
पूर्ण

अटल व्योम smsusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	smsusb_term_device(पूर्णांकf);
पूर्ण

अटल पूर्णांक smsusb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t msg)
अणु
	काष्ठा smsusb_device_t *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	prपूर्णांकk(KERN_INFO "%s  Entering status %d.\n", __func__, msg.event);
	dev->state = SMSUSB_SUSPENDED;
	/*smscore_set_घातer_mode(dev, SMS_POWER_MODE_SUSPENDED);*/
	smsusb_stop_streaming(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक smsusb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	पूर्णांक rc, i;
	काष्ठा smsusb_device_t *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	prपूर्णांकk(KERN_INFO "%s  Entering.\n", __func__);
	usb_clear_halt(udev, usb_rcvbulkpipe(udev, dev->in_ep));
	usb_clear_halt(udev, usb_sndbulkpipe(udev, dev->out_ep));

	क्रम (i = 0; i < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; i++)
		prपूर्णांकk(KERN_INFO "endpoint %d %02x %02x %d\n", i,
		       पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc.bEndpoपूर्णांकAddress,
		       पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc.bmAttributes,
		       पूर्णांकf->cur_altsetting->endpoपूर्णांक[i].desc.wMaxPacketSize);

	अगर (पूर्णांकf->num_altsetting > 0) अणु
		rc = usb_set_पूर्णांकerface(udev,
				       पूर्णांकf->cur_altsetting->desc.
				       bInterfaceNumber, 0);
		अगर (rc < 0) अणु
			prपूर्णांकk(KERN_INFO "%s usb_set_interface failed, rc %d\n",
			       __func__, rc);
			वापस rc;
		पूर्ण
	पूर्ण

	smsusb_start_streaming(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_device_id smsusb_id_table[] = अणु
	/* This device is only present beक्रमe firmware load */
	अणु USB_DEVICE(0x187f, 0x0010),
		.driver_info = SMS1XXX_BOARD_SIANO_STELLAR_ROM पूर्ण,
	/* This device pops up after firmware load */
	अणु USB_DEVICE(0x187f, 0x0100),
		.driver_info = SMS1XXX_BOARD_SIANO_STELLAR पूर्ण,

	अणु USB_DEVICE(0x187f, 0x0200),
		.driver_info = SMS1XXX_BOARD_SIANO_NOVA_A पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0201),
		.driver_info = SMS1XXX_BOARD_SIANO_NOVA_B पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0300),
		.driver_info = SMS1XXX_BOARD_SIANO_VEGA पूर्ण,
	अणु USB_DEVICE(0x2040, 0x1700),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_CATAMOUNT पूर्ण,
	अणु USB_DEVICE(0x2040, 0x1800),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_OKEMO_A पूर्ण,
	अणु USB_DEVICE(0x2040, 0x1801),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_OKEMO_B पूर्ण,
	अणु USB_DEVICE(0x2040, 0x2000),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD पूर्ण,
	अणु USB_DEVICE(0x2040, 0x2009),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2 पूर्ण,
	अणु USB_DEVICE(0x2040, 0x200a),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD पूर्ण,
	अणु USB_DEVICE(0x2040, 0x2010),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD पूर्ण,
	अणु USB_DEVICE(0x2040, 0x2011),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD पूर्ण,
	अणु USB_DEVICE(0x2040, 0x2019),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD पूर्ण,
	अणु USB_DEVICE(0x2040, 0x5500),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0x5510),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0x5520),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0x5530),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0x5580),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0x5590),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0202),
		.driver_info = SMS1XXX_BOARD_SIANO_NICE पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0301),
		.driver_info = SMS1XXX_BOARD_SIANO_VENICE पूर्ण,
	अणु USB_DEVICE(0x2040, 0xb900),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0xb910),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0xb980),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0xb990),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0xc000),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0xc010),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0xc080),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0xc090),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0xc0a0),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x2040, 0xf5a0),
		.driver_info = SMS1XXX_BOARD_HAUPPAUGE_WINDHAM पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0202),
		.driver_info = SMS1XXX_BOARD_SIANO_NICE पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0301),
		.driver_info = SMS1XXX_BOARD_SIANO_VENICE पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0302),
		.driver_info = SMS1XXX_BOARD_SIANO_VENICE पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0310),
		.driver_info = SMS1XXX_BOARD_SIANO_MING पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0500),
		.driver_info = SMS1XXX_BOARD_SIANO_PELE पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0600),
		.driver_info = SMS1XXX_BOARD_SIANO_RIO पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0700),
		.driver_info = SMS1XXX_BOARD_SIANO_DENVER_2160 पूर्ण,
	अणु USB_DEVICE(0x187f, 0x0800),
		.driver_info = SMS1XXX_BOARD_SIANO_DENVER_1530 पूर्ण,
	अणु USB_DEVICE(0x19D2, 0x0086),
		.driver_info = SMS1XXX_BOARD_ZTE_DVB_DATA_CARD पूर्ण,
	अणु USB_DEVICE(0x19D2, 0x0078),
		.driver_info = SMS1XXX_BOARD_ONDA_MDTV_DATA_CARD पूर्ण,
	अणु USB_DEVICE(0x3275, 0x0080),
		.driver_info = SMS1XXX_BOARD_SIANO_RIO पूर्ण,
	अणु USB_DEVICE(0x2013, 0x0257),
		.driver_info = SMS1XXX_BOARD_PCTV_77E पूर्ण,
	अणु पूर्ण /* Terminating entry */
	पूर्ण;

MODULE_DEVICE_TABLE(usb, smsusb_id_table);

अटल काष्ठा usb_driver smsusb_driver = अणु
	.name			= "smsusb",
	.probe			= smsusb_probe,
	.disconnect		= smsusb_disconnect,
	.id_table		= smsusb_id_table,

	.suspend		= smsusb_suspend,
	.resume			= smsusb_resume,
पूर्ण;

module_usb_driver(smsusb_driver);

MODULE_DESCRIPTION("Driver for the Siano SMS1xxx USB dongle");
MODULE_AUTHOR("Siano Mobile Silicon, INC. (uris@siano-ms.com)");
MODULE_LICENSE("GPL");
