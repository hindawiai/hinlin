<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2018 Sean Young <sean@mess.org>

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <media/rc-core.h>

/* Each bit is 250us */
#घोषणा BIT_DURATION 250

काष्ठा imon अणु
	काष्ठा device *dev;
	काष्ठा urb *ir_urb;
	काष्ठा rc_dev *rcdev;
	__be64 ir_buf;
	अक्षर phys[64];
पूर्ण;

/*
 * The first 5 bytes of data represent IR pulse or space. Each bit, starting
 * from highest bit in the first byte, represents 250तगs of data. It is 1
 * क्रम space and 0 क्रम pulse.
 *
 * The station sends 10 packets, and the 7th byte will be number 1 to 10, so
 * when we receive 10 we assume all the data has arrived.
 */
अटल व्योम imon_ir_data(काष्ठा imon *imon)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	u64 data = be64_to_cpu(imon->ir_buf);
	u8 packet_no = data & 0xff;
	पूर्णांक offset = 40;
	पूर्णांक bit;

	अगर (packet_no == 0xff)
		वापस;

	dev_dbg(imon->dev, "data: %*ph", 8, &imon->ir_buf);

	/*
	 * Only the first 5 bytes contain IR data. Right shअगरt so we move
	 * the IR bits to the lower 40 bits.
	 */
	data >>= 24;

	करो अणु
		/*
		 * Find highest set bit which is less or equal to offset
		 *
		 * offset is the bit above (base 0) where we start looking.
		 *
		 * data & (BIT_ULL(offset) - 1) masks off any unwanted bits,
		 * so we have just bits less than offset.
		 *
		 * fls will tell us the highest bit set plus 1 (or 0 अगर no
		 * bits are set).
		 */
		rawir.pulse = !rawir.pulse;
		bit = fls64(data & (BIT_ULL(offset) - 1));
		अगर (bit < offset) अणु
			dev_dbg(imon->dev, "%s: %d bits",
				rawir.pulse ? "pulse" : "space", offset - bit);
			rawir.duration = (offset - bit) * BIT_DURATION;
			ir_raw_event_store_with_filter(imon->rcdev, &rawir);

			offset = bit;
		पूर्ण

		data = ~data;
	पूर्ण जबतक (offset > 0);

	अगर (packet_no == 0x0a && !imon->rcdev->idle) अणु
		ir_raw_event_set_idle(imon->rcdev, true);
		ir_raw_event_handle(imon->rcdev);
	पूर्ण
पूर्ण

अटल व्योम imon_ir_rx(काष्ठा urb *urb)
अणु
	काष्ठा imon *imon = urb->context;
	पूर्णांक ret;

	चयन (urb->status) अणु
	हाल 0:
		imon_ir_data(imon);
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		usb_unlink_urb(urb);
		वापस;
	हाल -EPIPE:
	शेष:
		dev_dbg(imon->dev, "error: urb status = %d", urb->status);
		अवरोध;
	पूर्ण

	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret && ret != -ENODEV)
		dev_warn(imon->dev, "failed to resubmit urb: %d", ret);
पूर्ण

अटल पूर्णांक imon_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		      स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *ir_ep = शून्य;
	काष्ठा usb_host_पूर्णांकerface *idesc;
	काष्ठा usb_device *udev;
	काष्ठा rc_dev *rcdev;
	काष्ठा imon *imon;
	पूर्णांक i, ret;

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	idesc = पूर्णांकf->cur_altsetting;

	क्रम (i = 0; i < idesc->desc.bNumEndpoपूर्णांकs; i++) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor *ep = &idesc->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_is_पूर्णांक_in(ep)) अणु
			ir_ep = ep;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ir_ep) अणु
		dev_err(&पूर्णांकf->dev, "IR endpoint missing");
		वापस -ENODEV;
	पूर्ण

	imon = devm_kदो_स्मृति(&पूर्णांकf->dev, माप(*imon), GFP_KERNEL);
	अगर (!imon)
		वापस -ENOMEM;

	imon->ir_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!imon->ir_urb)
		वापस -ENOMEM;

	imon->dev = &पूर्णांकf->dev;
	usb_fill_पूर्णांक_urb(imon->ir_urb, udev,
			 usb_rcvपूर्णांकpipe(udev, ir_ep->bEndpoपूर्णांकAddress),
			 &imon->ir_buf, माप(imon->ir_buf),
			 imon_ir_rx, imon, ir_ep->bInterval);

	rcdev = devm_rc_allocate_device(&पूर्णांकf->dev, RC_DRIVER_IR_RAW);
	अगर (!rcdev) अणु
		ret = -ENOMEM;
		जाओ मुक्त_urb;
	पूर्ण

	usb_make_path(udev, imon->phys, माप(imon->phys));

	rcdev->device_name = "iMON Station";
	rcdev->driver_name = KBUILD_MODNAME;
	rcdev->input_phys = imon->phys;
	usb_to_input_id(udev, &rcdev->input_id);
	rcdev->dev.parent = &पूर्णांकf->dev;
	rcdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rcdev->map_name = RC_MAP_IMON_RSC;
	rcdev->rx_resolution = BIT_DURATION;
	rcdev->priv = imon;

	ret = devm_rc_रेजिस्टर_device(&पूर्णांकf->dev, rcdev);
	अगर (ret)
		जाओ मुक्त_urb;

	imon->rcdev = rcdev;

	ret = usb_submit_urb(imon->ir_urb, GFP_KERNEL);
	अगर (ret)
		जाओ मुक्त_urb;

	usb_set_पूर्णांकfdata(पूर्णांकf, imon);

	वापस 0;

मुक्त_urb:
	usb_मुक्त_urb(imon->ir_urb);
	वापस ret;
पूर्ण

अटल व्योम imon_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा imon *imon = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_समाप्त_urb(imon->ir_urb);
	usb_मुक्त_urb(imon->ir_urb);
पूर्ण

अटल स्थिर काष्ठा usb_device_id imon_table[] = अणु
	/* SoundGraph iMON (IR only) -- sg_imon.inf */
	अणु USB_DEVICE(0x04e8, 0xff30) पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा usb_driver imon_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = imon_probe,
	.disconnect = imon_disconnect,
	.id_table = imon_table
पूर्ण;

module_usb_driver(imon_driver);

MODULE_DESCRIPTION("Early raw iMON IR devices");
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(usb, imon_table);
