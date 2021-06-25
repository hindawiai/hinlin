<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Streamzap Remote Control driver
 *
 * Copyright (c) 2005 Christoph Bartelmus <lirc@bartelmus.de>
 * Copyright (c) 2010 Jarod Wilson <jarod@wilsonet.com>
 *
 * This driver was based on the work of Greg Wickham and Adrian
 * Dewhurst. It was substantially rewritten to support correct संकेत
 * gaps and now मुख्यtains a delay buffer, which is used to present
 * consistent timing behaviour to user space applications. Without the
 * delay buffer an ugly hack would be required in lircd, which can
 * cause sluggish संकेत decoding in certain situations.
 *
 * Ported to in-kernel ir-core पूर्णांकerface by Jarod Wilson
 *
 * This driver is based on the USB skeleton driver packaged with the
 * kernel; copyright (C) 2001-2003 Greg Kroah-Harपंचांगan (greg@kroah.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <media/rc-core.h>

#घोषणा DRIVER_VERSION	"1.61"
#घोषणा DRIVER_NAME	"streamzap"
#घोषणा DRIVER_DESC	"Streamzap Remote Control driver"

#घोषणा USB_STREAMZAP_VENDOR_ID		0x0e9c
#घोषणा USB_STREAMZAP_PRODUCT_ID	0x0000

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id streamzap_table[] = अणु
	/* Streamzap Remote Control */
	अणु USB_DEVICE(USB_STREAMZAP_VENDOR_ID, USB_STREAMZAP_PRODUCT_ID) पूर्ण,
	/* Terminating entry */
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, streamzap_table);

#घोषणा SZ_PULSE_MASK 0xf0
#घोषणा SZ_SPACE_MASK 0x0f
#घोषणा SZ_TIMEOUT    0xff
#घोषणा SZ_RESOLUTION 256

/* number of samples buffered */
#घोषणा SZ_BUF_LEN 128

क्रमागत StreamzapDecoderState अणु
	PulseSpace,
	FullPulse,
	FullSpace,
	IgnorePulse
पूर्ण;

/* काष्ठाure to hold our device specअगरic stuff */
काष्ठा streamzap_ir अणु
	/* ir-core */
	काष्ठा rc_dev *rdev;

	/* core device info */
	काष्ठा device *dev;

	/* usb */
	काष्ठा usb_device	*usbdev;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा urb		*urb_in;

	/* buffer & dma */
	अचिन्हित अक्षर		*buf_in;
	dma_addr_t		dma_in;
	अचिन्हित पूर्णांक		buf_in_len;

	/* track what state we're in */
	क्रमागत StreamzapDecoderState decoder_state;
	/* tracks whether we are currently receiving some संकेत */
	bool			idle;
	/* sum of संकेत lengths received since संकेत start */
	अचिन्हित दीर्घ		sum;
	/* start समय of संकेत; necessary क्रम gap tracking */
	kसमय_प्रकार			संकेत_last;
	kसमय_प्रकार			संकेत_start;
	bool			समयout_enabled;

	अक्षर			name[128];
	अक्षर			phys[64];
पूर्ण;


/* local function prototypes */
अटल पूर्णांक streamzap_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			   स्थिर काष्ठा usb_device_id *id);
अटल व्योम streamzap_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
अटल व्योम streamzap_callback(काष्ठा urb *urb);
अटल पूर्णांक streamzap_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message);
अटल पूर्णांक streamzap_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver streamzap_driver = अणु
	.name =		DRIVER_NAME,
	.probe =	streamzap_probe,
	.disconnect =	streamzap_disconnect,
	.suspend =	streamzap_suspend,
	.resume =	streamzap_resume,
	.id_table =	streamzap_table,
पूर्ण;

अटल व्योम sz_push(काष्ठा streamzap_ir *sz, काष्ठा ir_raw_event rawir)
अणु
	dev_dbg(sz->dev, "Storing %s with duration %u us\n",
		(rawir.pulse ? "pulse" : "space"), rawir.duration);
	ir_raw_event_store_with_filter(sz->rdev, &rawir);
पूर्ण

अटल व्योम sz_push_full_pulse(काष्ठा streamzap_ir *sz,
			       अचिन्हित अक्षर value)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;

	अगर (sz->idle) अणु
		पूर्णांक delta;

		sz->संकेत_last = sz->संकेत_start;
		sz->संकेत_start = kसमय_get_real();

		delta = kसमय_us_delta(sz->संकेत_start, sz->संकेत_last);
		rawir.pulse = false;
		अगर (delta > (15 * USEC_PER_SEC)) अणु
			/* really दीर्घ समय */
			rawir.duration = IR_MAX_DURATION;
		पूर्ण अन्यथा अणु
			rawir.duration = delta;
			rawir.duration -= sz->sum;
			rawir.duration = (rawir.duration > IR_MAX_DURATION) ?
					 IR_MAX_DURATION : rawir.duration;
		पूर्ण
		sz_push(sz, rawir);

		sz->idle = false;
		sz->sum = 0;
	पूर्ण

	rawir.pulse = true;
	rawir.duration = ((पूर्णांक) value) * SZ_RESOLUTION;
	rawir.duration += SZ_RESOLUTION / 2;
	sz->sum += rawir.duration;
	rawir.duration = (rawir.duration > IR_MAX_DURATION) ?
			 IR_MAX_DURATION : rawir.duration;
	sz_push(sz, rawir);
पूर्ण

अटल व्योम sz_push_half_pulse(काष्ठा streamzap_ir *sz,
			       अचिन्हित अक्षर value)
अणु
	sz_push_full_pulse(sz, (value & SZ_PULSE_MASK) >> 4);
पूर्ण

अटल व्योम sz_push_full_space(काष्ठा streamzap_ir *sz,
			       अचिन्हित अक्षर value)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;

	rawir.pulse = false;
	rawir.duration = ((पूर्णांक) value) * SZ_RESOLUTION;
	rawir.duration += SZ_RESOLUTION / 2;
	sz->sum += rawir.duration;
	sz_push(sz, rawir);
पूर्ण

अटल व्योम sz_push_half_space(काष्ठा streamzap_ir *sz,
			       अचिन्हित दीर्घ value)
अणु
	sz_push_full_space(sz, value & SZ_SPACE_MASK);
पूर्ण

/*
 * streamzap_callback - usb IRQ handler callback
 *
 * This procedure is invoked on reception of data from
 * the usb remote.
 */
अटल व्योम streamzap_callback(काष्ठा urb *urb)
अणु
	काष्ठा streamzap_ir *sz;
	अचिन्हित पूर्णांक i;
	पूर्णांक len;

	अगर (!urb)
		वापस;

	sz = urb->context;
	len = urb->actual_length;

	चयन (urb->status) अणु
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/*
		 * this urb is terminated, clean up.
		 * sz might alपढ़ोy be invalid at this poपूर्णांक
		 */
		dev_err(sz->dev, "urb terminated, status: %d\n", urb->status);
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(sz->dev, "%s: received urb, len %d\n", __func__, len);
	क्रम (i = 0; i < len; i++) अणु
		dev_dbg(sz->dev, "sz->buf_in[%d]: %x\n",
			i, (अचिन्हित अक्षर)sz->buf_in[i]);
		चयन (sz->decoder_state) अणु
		हाल PulseSpace:
			अगर ((sz->buf_in[i] & SZ_PULSE_MASK) ==
				SZ_PULSE_MASK) अणु
				sz->decoder_state = FullPulse;
				जारी;
			पूर्ण अन्यथा अगर ((sz->buf_in[i] & SZ_SPACE_MASK)
					== SZ_SPACE_MASK) अणु
				sz_push_half_pulse(sz, sz->buf_in[i]);
				sz->decoder_state = FullSpace;
				जारी;
			पूर्ण अन्यथा अणु
				sz_push_half_pulse(sz, sz->buf_in[i]);
				sz_push_half_space(sz, sz->buf_in[i]);
			पूर्ण
			अवरोध;
		हाल FullPulse:
			sz_push_full_pulse(sz, sz->buf_in[i]);
			sz->decoder_state = IgnorePulse;
			अवरोध;
		हाल FullSpace:
			अगर (sz->buf_in[i] == SZ_TIMEOUT) अणु
				काष्ठा ir_raw_event rawir = अणु
					.pulse = false,
					.duration = sz->rdev->समयout
				पूर्ण;
				sz->idle = true;
				अगर (sz->समयout_enabled)
					sz_push(sz, rawir);
				ir_raw_event_handle(sz->rdev);
				ir_raw_event_reset(sz->rdev);
			पूर्ण अन्यथा अणु
				sz_push_full_space(sz, sz->buf_in[i]);
			पूर्ण
			sz->decoder_state = PulseSpace;
			अवरोध;
		हाल IgnorePulse:
			अगर ((sz->buf_in[i] & SZ_SPACE_MASK) ==
				SZ_SPACE_MASK) अणु
				sz->decoder_state = FullSpace;
				जारी;
			पूर्ण
			sz_push_half_space(sz, sz->buf_in[i]);
			sz->decoder_state = PulseSpace;
			अवरोध;
		पूर्ण
	पूर्ण

	ir_raw_event_handle(sz->rdev);
	usb_submit_urb(urb, GFP_ATOMIC);

	वापस;
पूर्ण

अटल काष्ठा rc_dev *streamzap_init_rc_dev(काष्ठा streamzap_ir *sz)
अणु
	काष्ठा rc_dev *rdev;
	काष्ठा device *dev = sz->dev;
	पूर्णांक ret;

	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rdev) अणु
		dev_err(dev, "remote dev allocation failed\n");
		जाओ out;
	पूर्ण

	snम_लिखो(sz->name, माप(sz->name), "Streamzap PC Remote Infrared Receiver (%04x:%04x)",
		 le16_to_cpu(sz->usbdev->descriptor.idVenकरोr),
		 le16_to_cpu(sz->usbdev->descriptor.idProduct));
	usb_make_path(sz->usbdev, sz->phys, माप(sz->phys));
	strlcat(sz->phys, "/input0", माप(sz->phys));

	rdev->device_name = sz->name;
	rdev->input_phys = sz->phys;
	usb_to_input_id(sz->usbdev, &rdev->input_id);
	rdev->dev.parent = dev;
	rdev->priv = sz;
	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->driver_name = DRIVER_NAME;
	rdev->map_name = RC_MAP_STREAMZAP;

	ret = rc_रेजिस्टर_device(rdev);
	अगर (ret < 0) अणु
		dev_err(dev, "remote input device register failed\n");
		जाओ out;
	पूर्ण

	वापस rdev;

out:
	rc_मुक्त_device(rdev);
	वापस शून्य;
पूर्ण

/*
 *	streamzap_probe
 *
 *	Called by usb-core to associated with a candidate device
 *	On any failure the वापस value is the ERROR
 *	On success वापस 0
 */
अटल पूर्णांक streamzap_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *अगरace_host;
	काष्ठा streamzap_ir *sz = शून्य;
	अक्षर buf[63], name[128] = "";
	पूर्णांक retval = -ENOMEM;
	पूर्णांक pipe, maxp;

	/* Allocate space क्रम device driver specअगरic data */
	sz = kzalloc(माप(काष्ठा streamzap_ir), GFP_KERNEL);
	अगर (!sz)
		वापस -ENOMEM;

	sz->usbdev = usbdev;
	sz->पूर्णांकerface = पूर्णांकf;

	/* Check to ensure endpoपूर्णांक inक्रमmation matches requirements */
	अगरace_host = पूर्णांकf->cur_altsetting;

	अगर (अगरace_host->desc.bNumEndpoपूर्णांकs != 1) अणु
		dev_err(&पूर्णांकf->dev, "%s: Unexpected desc.bNumEndpoints (%d)\n",
			__func__, अगरace_host->desc.bNumEndpoपूर्णांकs);
		retval = -ENODEV;
		जाओ मुक्त_sz;
	पूर्ण

	sz->endpoपूर्णांक = &(अगरace_host->endpoपूर्णांक[0].desc);
	अगर (!usb_endpoपूर्णांक_dir_in(sz->endpoपूर्णांक)) अणु
		dev_err(&पूर्णांकf->dev, "%s: endpoint doesn't match input device 02%02x\n",
			__func__, sz->endpoपूर्णांक->bEndpoपूर्णांकAddress);
		retval = -ENODEV;
		जाओ मुक्त_sz;
	पूर्ण

	अगर (!usb_endpoपूर्णांक_xfer_पूर्णांक(sz->endpoपूर्णांक)) अणु
		dev_err(&पूर्णांकf->dev, "%s: endpoint attributes don't match xfer 02%02x\n",
			__func__, sz->endpoपूर्णांक->bmAttributes);
		retval = -ENODEV;
		जाओ मुक्त_sz;
	पूर्ण

	pipe = usb_rcvपूर्णांकpipe(usbdev, sz->endpoपूर्णांक->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(usbdev, pipe, usb_pipeout(pipe));

	अगर (maxp == 0) अणु
		dev_err(&पूर्णांकf->dev, "%s: endpoint Max Packet Size is 0!?!\n",
			__func__);
		retval = -ENODEV;
		जाओ मुक्त_sz;
	पूर्ण

	/* Allocate the USB buffer and IRQ URB */
	sz->buf_in = usb_alloc_coherent(usbdev, maxp, GFP_ATOMIC, &sz->dma_in);
	अगर (!sz->buf_in)
		जाओ मुक्त_sz;

	sz->urb_in = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!sz->urb_in)
		जाओ मुक्त_buf_in;

	sz->dev = &पूर्णांकf->dev;
	sz->buf_in_len = maxp;

	अगर (usbdev->descriptor.iManufacturer
	    && usb_string(usbdev, usbdev->descriptor.iManufacturer,
			  buf, माप(buf)) > 0)
		strscpy(name, buf, माप(name));

	अगर (usbdev->descriptor.iProduct
	    && usb_string(usbdev, usbdev->descriptor.iProduct,
			  buf, माप(buf)) > 0)
		snम_लिखो(name + म_माप(name), माप(name) - म_माप(name),
			 " %s", buf);

	sz->rdev = streamzap_init_rc_dev(sz);
	अगर (!sz->rdev)
		जाओ rc_dev_fail;

	sz->idle = true;
	sz->decoder_state = PulseSpace;
	/* FIXME: करोn't yet have a way to set this */
	sz->समयout_enabled = true;
	sz->rdev->समयout = SZ_TIMEOUT * SZ_RESOLUTION;
	#अगर 0
	/* not yet supported, depends on patches from maxim */
	/* see also: LIRC_GET_REC_RESOLUTION and LIRC_SET_REC_TIMEOUT */
	sz->min_समयout = SZ_TIMEOUT * SZ_RESOLUTION;
	sz->max_समयout = SZ_TIMEOUT * SZ_RESOLUTION;
	#पूर्ण_अगर

	sz->संकेत_start = kसमय_get_real();

	/* Complete final initialisations */
	usb_fill_पूर्णांक_urb(sz->urb_in, usbdev, pipe, sz->buf_in,
			 maxp, (usb_complete_t)streamzap_callback,
			 sz, sz->endpoपूर्णांक->bInterval);
	sz->urb_in->transfer_dma = sz->dma_in;
	sz->urb_in->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	usb_set_पूर्णांकfdata(पूर्णांकf, sz);

	अगर (usb_submit_urb(sz->urb_in, GFP_ATOMIC))
		dev_err(sz->dev, "urb submit failed\n");

	dev_info(sz->dev, "Registered %s on usb%d:%d\n", name,
		 usbdev->bus->busnum, usbdev->devnum);

	वापस 0;

rc_dev_fail:
	usb_मुक्त_urb(sz->urb_in);
मुक्त_buf_in:
	usb_मुक्त_coherent(usbdev, maxp, sz->buf_in, sz->dma_in);
मुक्त_sz:
	kमुक्त(sz);

	वापस retval;
पूर्ण

/*
 * streamzap_disconnect
 *
 * Called by the usb core when the device is हटाओd from the प्रणाली.
 *
 * This routine guarantees that the driver will not submit any more urbs
 * by clearing dev->usbdev.  It is also supposed to terminate any currently
 * active urbs.  Unक्रमtunately, usb_bulk_msg(), used in streamzap_पढ़ो(),
 * करोes not provide any way to करो this.
 */
अटल व्योम streamzap_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा streamzap_ir *sz = usb_get_पूर्णांकfdata(पूर्णांकerface);
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	अगर (!sz)
		वापस;

	sz->usbdev = शून्य;
	rc_unरेजिस्टर_device(sz->rdev);
	usb_समाप्त_urb(sz->urb_in);
	usb_मुक्त_urb(sz->urb_in);
	usb_मुक्त_coherent(usbdev, sz->buf_in_len, sz->buf_in, sz->dma_in);

	kमुक्त(sz);
पूर्ण

अटल पूर्णांक streamzap_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा streamzap_ir *sz = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_समाप्त_urb(sz->urb_in);

	वापस 0;
पूर्ण

अटल पूर्णांक streamzap_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा streamzap_ir *sz = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (usb_submit_urb(sz->urb_in, GFP_ATOMIC)) अणु
		dev_err(sz->dev, "Error submitting urb\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

module_usb_driver(streamzap_driver);

MODULE_AUTHOR("Jarod Wilson <jarod@wilsonet.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
