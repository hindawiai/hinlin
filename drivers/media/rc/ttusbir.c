<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TechnoTrend USB IR Receiver
 *
 * Copyright (C) 2012 Sean Young <sean@mess.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश <media/rc-core.h>

#घोषणा DRIVER_NAME	"ttusbir"
#घोषणा DRIVER_DESC	"TechnoTrend USB IR Receiver"
/*
 * The Winकरोws driver uses 8 URBS, the original lirc drivers has a
 * configurable amount (2 शेष, 4 max). This device generates about 125
 * messages per second (!), whether IR is idle or not.
 */
#घोषणा NUM_URBS	4
#घोषणा US_PER_BYTE	62
#घोषणा US_PER_BIT	(US_PER_BYTE / 8)

काष्ठा ttusbir अणु
	काष्ठा rc_dev *rc;
	काष्ठा device *dev;
	काष्ठा usb_device *udev;

	काष्ठा urb *urb[NUM_URBS];

	काष्ठा led_classdev led;
	काष्ठा urb *bulk_urb;
	uपूर्णांक8_t bulk_buffer[5];
	पूर्णांक bulk_out_endp, iso_in_endp;
	bool led_on, is_led_on;
	atomic_t led_complete;

	अक्षर phys[64];
पूर्ण;

अटल क्रमागत led_brightness ttusbir_brightness_get(काष्ठा led_classdev *led_dev)
अणु
	काष्ठा ttusbir *tt = container_of(led_dev, काष्ठा ttusbir, led);

	वापस tt->led_on ? LED_FULL : LED_OFF;
पूर्ण

अटल व्योम ttusbir_set_led(काष्ठा ttusbir *tt)
अणु
	पूर्णांक ret;

	smp_mb();

	अगर (tt->led_on != tt->is_led_on && tt->udev &&
				atomic_add_unless(&tt->led_complete, 1, 1)) अणु
		tt->bulk_buffer[4] = tt->is_led_on = tt->led_on;
		ret = usb_submit_urb(tt->bulk_urb, GFP_ATOMIC);
		अगर (ret) अणु
			dev_warn(tt->dev, "failed to submit bulk urb: %d\n",
									ret);
			atomic_dec(&tt->led_complete);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ttusbir_brightness_set(काष्ठा led_classdev *led_dev, क्रमागत
						led_brightness brightness)
अणु
	काष्ठा ttusbir *tt = container_of(led_dev, काष्ठा ttusbir, led);

	tt->led_on = brightness != LED_OFF;

	ttusbir_set_led(tt);
पूर्ण

/*
 * The urb cannot be reused until the urb completes
 */
अटल व्योम ttusbir_bulk_complete(काष्ठा urb *urb)
अणु
	काष्ठा ttusbir *tt = urb->context;

	atomic_dec(&tt->led_complete);

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		usb_unlink_urb(urb);
		वापस;
	हाल -EPIPE:
	शेष:
		dev_dbg(tt->dev, "Error: urb status = %d\n", urb->status);
		अवरोध;
	पूर्ण

	ttusbir_set_led(tt);
पूर्ण

/*
 * The data is one bit per sample, a set bit signअगरying silence and samples
 * being MSB first. Bit 0 can contain garbage so take it to be whatever
 * bit 1 is, so we करोn't have unexpected edges.
 */
अटल व्योम ttusbir_process_ir_data(काष्ठा ttusbir *tt, uपूर्णांक8_t *buf)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	अचिन्हित i, v, b;
	bool event = false;

	क्रम (i = 0; i < 128; i++) अणु
		v = buf[i] & 0xfe;
		चयन (v) अणु
		हाल 0xfe:
			rawir.pulse = false;
			rawir.duration = US_PER_BYTE;
			अगर (ir_raw_event_store_with_filter(tt->rc, &rawir))
				event = true;
			अवरोध;
		हाल 0:
			rawir.pulse = true;
			rawir.duration = US_PER_BYTE;
			अगर (ir_raw_event_store_with_filter(tt->rc, &rawir))
				event = true;
			अवरोध;
		शेष:
			/* one edge per byte */
			अगर (v & 2) अणु
				b = ffz(v | 1);
				rawir.pulse = true;
			पूर्ण अन्यथा अणु
				b = ffs(v) - 1;
				rawir.pulse = false;
			पूर्ण

			rawir.duration = US_PER_BIT * (8 - b);
			अगर (ir_raw_event_store_with_filter(tt->rc, &rawir))
				event = true;

			rawir.pulse = !rawir.pulse;
			rawir.duration = US_PER_BIT * b;
			अगर (ir_raw_event_store_with_filter(tt->rc, &rawir))
				event = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* करोn't wakeup when there's nothing to करो */
	अगर (event)
		ir_raw_event_handle(tt->rc);
पूर्ण

अटल व्योम ttusbir_urb_complete(काष्ठा urb *urb)
अणु
	काष्ठा ttusbir *tt = urb->context;
	पूर्णांक rc;

	चयन (urb->status) अणु
	हाल 0:
		ttusbir_process_ir_data(tt, urb->transfer_buffer);
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		usb_unlink_urb(urb);
		वापस;
	हाल -EPIPE:
	शेष:
		dev_dbg(tt->dev, "Error: urb status = %d\n", urb->status);
		अवरोध;
	पूर्ण

	rc = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (rc && rc != -ENODEV)
		dev_warn(tt->dev, "failed to resubmit urb: %d\n", rc);
पूर्ण

अटल पूर्णांक ttusbir_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा ttusbir *tt;
	काष्ठा usb_पूर्णांकerface_descriptor *idesc;
	काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	काष्ठा rc_dev *rc;
	पूर्णांक i, j, ret;
	पूर्णांक altsetting = -1;

	tt = kzalloc(माप(*tt), GFP_KERNEL);
	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!tt || !rc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* find the correct alt setting */
	क्रम (i = 0; i < पूर्णांकf->num_altsetting && altsetting == -1; i++) अणु
		पूर्णांक max_packet, bulk_out_endp = -1, iso_in_endp = -1;

		idesc = &पूर्णांकf->altsetting[i].desc;

		क्रम (j = 0; j < idesc->bNumEndpoपूर्णांकs; j++) अणु
			desc = &पूर्णांकf->altsetting[i].endpoपूर्णांक[j].desc;
			max_packet = le16_to_cpu(desc->wMaxPacketSize);
			अगर (usb_endpoपूर्णांक_dir_in(desc) &&
					usb_endpoपूर्णांक_xfer_isoc(desc) &&
					max_packet == 0x10)
				iso_in_endp = j;
			अन्यथा अगर (usb_endpoपूर्णांक_dir_out(desc) &&
					usb_endpoपूर्णांक_xfer_bulk(desc) &&
					max_packet == 0x20)
				bulk_out_endp = j;

			अगर (bulk_out_endp != -1 && iso_in_endp != -1) अणु
				tt->bulk_out_endp = bulk_out_endp;
				tt->iso_in_endp = iso_in_endp;
				altsetting = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (altsetting == -1) अणु
		dev_err(&पूर्णांकf->dev, "cannot find expected altsetting\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	tt->dev = &पूर्णांकf->dev;
	tt->udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	tt->rc = rc;

	ret = usb_set_पूर्णांकerface(tt->udev, 0, altsetting);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < NUM_URBS; i++) अणु
		काष्ठा urb *urb = usb_alloc_urb(8, GFP_KERNEL);
		व्योम *buffer;

		अगर (!urb) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		urb->dev = tt->udev;
		urb->context = tt;
		urb->pipe = usb_rcvisocpipe(tt->udev, tt->iso_in_endp);
		urb->पूर्णांकerval = 1;
		buffer = usb_alloc_coherent(tt->udev, 128, GFP_KERNEL,
						&urb->transfer_dma);
		अगर (!buffer) अणु
			usb_मुक्त_urb(urb);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP | URB_ISO_ASAP;
		urb->transfer_buffer = buffer;
		urb->complete = ttusbir_urb_complete;
		urb->number_of_packets = 8;
		urb->transfer_buffer_length = 128;

		क्रम (j = 0; j < 8; j++) अणु
			urb->iso_frame_desc[j].offset = j * 16;
			urb->iso_frame_desc[j].length = 16;
		पूर्ण

		tt->urb[i] = urb;
	पूर्ण

	tt->bulk_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!tt->bulk_urb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	tt->bulk_buffer[0] = 0xaa;
	tt->bulk_buffer[1] = 0x01;
	tt->bulk_buffer[2] = 0x05;
	tt->bulk_buffer[3] = 0x01;

	usb_fill_bulk_urb(tt->bulk_urb, tt->udev, usb_sndbulkpipe(tt->udev,
		tt->bulk_out_endp), tt->bulk_buffer, माप(tt->bulk_buffer),
						ttusbir_bulk_complete, tt);

	tt->led.name = "ttusbir:green:power";
	tt->led.शेष_trigger = "rc-feedback";
	tt->led.brightness_set = ttusbir_brightness_set;
	tt->led.brightness_get = ttusbir_brightness_get;
	tt->is_led_on = tt->led_on = true;
	atomic_set(&tt->led_complete, 0);
	ret = led_classdev_रेजिस्टर(&पूर्णांकf->dev, &tt->led);
	अगर (ret)
		जाओ out;

	usb_make_path(tt->udev, tt->phys, माप(tt->phys));

	rc->device_name = DRIVER_DESC;
	rc->input_phys = tt->phys;
	usb_to_input_id(tt->udev, &rc->input_id);
	rc->dev.parent = &पूर्णांकf->dev;
	rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rc->priv = tt;
	rc->driver_name = DRIVER_NAME;
	rc->map_name = RC_MAP_TT_1500;
	rc->min_समयout = 1;
	rc->समयout = IR_DEFAULT_TIMEOUT;
	rc->max_समयout = 10 * IR_DEFAULT_TIMEOUT;

	/*
	 * The precision is US_PER_BIT, but since every 8th bit can be
	 * overwritten with garbage the accuracy is at best 2 * US_PER_BIT.
	 */
	rc->rx_resolution = 2 * US_PER_BIT;

	ret = rc_रेजिस्टर_device(rc);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to register rc device %d\n", ret);
		जाओ out2;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, tt);

	क्रम (i = 0; i < NUM_URBS; i++) अणु
		ret = usb_submit_urb(tt->urb[i], GFP_KERNEL);
		अगर (ret) अणु
			dev_err(tt->dev, "failed to submit urb %d\n", ret);
			जाओ out3;
		पूर्ण
	पूर्ण

	वापस 0;
out3:
	rc_unरेजिस्टर_device(rc);
	rc = शून्य;
out2:
	led_classdev_unरेजिस्टर(&tt->led);
out:
	अगर (tt) अणु
		क्रम (i = 0; i < NUM_URBS && tt->urb[i]; i++) अणु
			काष्ठा urb *urb = tt->urb[i];

			usb_समाप्त_urb(urb);
			usb_मुक्त_coherent(tt->udev, 128, urb->transfer_buffer,
							urb->transfer_dma);
			usb_मुक्त_urb(urb);
		पूर्ण
		usb_समाप्त_urb(tt->bulk_urb);
		usb_मुक्त_urb(tt->bulk_urb);
		kमुक्त(tt);
	पूर्ण
	rc_मुक्त_device(rc);

	वापस ret;
पूर्ण

अटल व्योम ttusbir_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ttusbir *tt = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device *udev = tt->udev;
	पूर्णांक i;

	tt->udev = शून्य;

	rc_unरेजिस्टर_device(tt->rc);
	led_classdev_unरेजिस्टर(&tt->led);
	क्रम (i = 0; i < NUM_URBS; i++) अणु
		usb_समाप्त_urb(tt->urb[i]);
		usb_मुक्त_coherent(udev, 128, tt->urb[i]->transfer_buffer,
						tt->urb[i]->transfer_dma);
		usb_मुक्त_urb(tt->urb[i]);
	पूर्ण
	usb_समाप्त_urb(tt->bulk_urb);
	usb_मुक्त_urb(tt->bulk_urb);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	kमुक्त(tt);
पूर्ण

अटल पूर्णांक ttusbir_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा ttusbir *tt = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक i;

	क्रम (i = 0; i < NUM_URBS; i++)
		usb_समाप्त_urb(tt->urb[i]);

	led_classdev_suspend(&tt->led);
	usb_समाप्त_urb(tt->bulk_urb);

	वापस 0;
पूर्ण

अटल पूर्णांक ttusbir_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ttusbir *tt = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक i, rc;

	tt->is_led_on = true;
	led_classdev_resume(&tt->led);

	क्रम (i = 0; i < NUM_URBS; i++) अणु
		rc = usb_submit_urb(tt->urb[i], GFP_KERNEL);
		अगर (rc) अणु
			dev_warn(tt->dev, "failed to submit urb: %d\n", rc);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा usb_device_id ttusbir_table[] = अणु
	अणु USB_DEVICE(0x0b48, 0x2003) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा usb_driver ttusbir_driver = अणु
	.name = DRIVER_NAME,
	.id_table = ttusbir_table,
	.probe = ttusbir_probe,
	.suspend = ttusbir_suspend,
	.resume = ttusbir_resume,
	.reset_resume = ttusbir_resume,
	.disconnect = ttusbir_disconnect,
पूर्ण;

module_usb_driver(ttusbir_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(usb, ttusbir_table);

