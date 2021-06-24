<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * Infrared Toy and IR Droid RC core driver
 *
 * Copyright (C) 2020 Sean Young <sean@mess.org>

 * This driver is based on the lirc driver which can be found here:
 * https://sourceक्रमge.net/p/lirc/git/ci/master/tree/plugins/irtoy.c
 * Copyright (C) 2011 Peter Kooiman <pkooiman@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/completion.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/input.h>

#समावेश <media/rc-core.h>

अटल स्थिर u8 COMMAND_VERSION[] = अणु 'v' पूर्ण;
// End transmit and repeat reset command so we निकास sump mode
अटल स्थिर u8 COMMAND_RESET[] = अणु 0xff, 0xff, 0, 0, 0, 0, 0 पूर्ण;
अटल स्थिर u8 COMMAND_SMODE_ENTER[] = अणु 's' पूर्ण;
अटल स्थिर u8 COMMAND_TXSTART[] = अणु 0x26, 0x24, 0x25, 0x03 पूर्ण;

#घोषणा REPLY_XMITCOUNT 't'
#घोषणा REPLY_XMITSUCCESS 'C'
#घोषणा REPLY_VERSION 'V'
#घोषणा REPLY_SAMPLEMODEPROTO 'S'

#घोषणा TIMEOUT 500

#घोषणा LEN_XMITRES 3
#घोषणा LEN_VERSION 4
#घोषणा LEN_SAMPLEMODEPROTO 3

#घोषणा MIN_FW_VERSION 20
#घोषणा UNIT_US 21
#घोषणा MAX_TIMEOUT_US (UNIT_US * U16_MAX)

#घोषणा MAX_PACKET 64

क्रमागत state अणु
	STATE_IRDATA,
	STATE_RESET,
	STATE_COMMAND,
	STATE_TX,
पूर्ण;

काष्ठा irtoy अणु
	काष्ठा device *dev;
	काष्ठा usb_device *usbdev;

	काष्ठा rc_dev *rc;
	काष्ठा urb *urb_in, *urb_out;

	u8 *in;
	u8 *out;
	काष्ठा completion command_करोne;

	bool pulse;
	क्रमागत state state;

	व्योम *tx_buf;
	uपूर्णांक tx_len;

	uपूर्णांक emitted;
	uपूर्णांक hw_version;
	uपूर्णांक sw_version;
	uपूर्णांक proto_version;

	अक्षर phys[64];
पूर्ण;

अटल व्योम irtoy_response(काष्ठा irtoy *irtoy, u32 len)
अणु
	चयन (irtoy->state) अणु
	हाल STATE_COMMAND:
		अगर (len == LEN_VERSION && irtoy->in[0] == REPLY_VERSION) अणु
			uपूर्णांक version;

			irtoy->in[LEN_VERSION] = 0;

			अगर (kstrtouपूर्णांक(irtoy->in + 1, 10, &version)) अणु
				dev_err(irtoy->dev, "invalid version %*phN. Please make sure you are using firmware v20 or higher",
					LEN_VERSION, irtoy->in);
				अवरोध;
			पूर्ण

			dev_dbg(irtoy->dev, "version %s\n", irtoy->in);

			irtoy->hw_version = version / 100;
			irtoy->sw_version = version % 100;

			irtoy->state = STATE_IRDATA;
			complete(&irtoy->command_करोne);
		पूर्ण अन्यथा अगर (len == LEN_SAMPLEMODEPROTO &&
			   irtoy->in[0] == REPLY_SAMPLEMODEPROTO) अणु
			uपूर्णांक version;

			irtoy->in[LEN_SAMPLEMODEPROTO] = 0;

			अगर (kstrtouपूर्णांक(irtoy->in + 1, 10, &version)) अणु
				dev_err(irtoy->dev, "invalid sample mode response %*phN",
					LEN_SAMPLEMODEPROTO, irtoy->in);
				वापस;
			पूर्ण

			dev_dbg(irtoy->dev, "protocol %s\n", irtoy->in);

			irtoy->proto_version = version;

			irtoy->state = STATE_IRDATA;
			complete(&irtoy->command_करोne);
		पूर्ण अन्यथा अणु
			dev_err(irtoy->dev, "unexpected response to command: %*phN\n",
				len, irtoy->in);
		पूर्ण
		अवरोध;
	हाल STATE_IRDATA: अणु
		काष्ठा ir_raw_event rawir = अणु .pulse = irtoy->pulse पूर्ण;
		__be16 *in = (__be16 *)irtoy->in;
		पूर्णांक i;

		क्रम (i = 0; i < len / माप(__be16); i++) अणु
			u16 v = be16_to_cpu(in[i]);

			अगर (v == 0xffff) अणु
				rawir.pulse = false;
			पूर्ण अन्यथा अणु
				rawir.duration = v * UNIT_US;
				ir_raw_event_store_with_समयout(irtoy->rc,
								&rawir);
			पूर्ण

			rawir.pulse = !rawir.pulse;
		पूर्ण

		irtoy->pulse = rawir.pulse;

		ir_raw_event_handle(irtoy->rc);
		अवरोध;
	पूर्ण
	हाल STATE_TX:
		अगर (irtoy->tx_len == 0) अणु
			अगर (len == LEN_XMITRES &&
			    irtoy->in[0] == REPLY_XMITCOUNT) अणु
				u16 emitted = get_unaligned_be16(irtoy->in + 1);

				dev_dbg(irtoy->dev, "emitted:%u\n", emitted);

				irtoy->emitted = emitted;
			पूर्ण अन्यथा अगर (len == 1 &&
				   irtoy->in[0] == REPLY_XMITSUCCESS) अणु
				irtoy->state = STATE_IRDATA;
				complete(&irtoy->command_करोne);
			पूर्ण
		पूर्ण अन्यथा अणु
			// send next part of tx buffer
			uपूर्णांक space = irtoy->in[0];
			uपूर्णांक buf_len;
			पूर्णांक err;

			अगर (len != 1 || space > MAX_PACKET || space == 0) अणु
				dev_err(irtoy->dev, "packet length expected: %*phN\n",
					len, irtoy->in);
				irtoy->state = STATE_IRDATA;
				complete(&irtoy->command_करोne);
				अवरोध;
			पूर्ण

			buf_len = min(space, irtoy->tx_len);

			dev_dbg(irtoy->dev, "remaining:%u sending:%u\n",
				irtoy->tx_len, buf_len);

			स_नकल(irtoy->out, irtoy->tx_buf, buf_len);
			irtoy->urb_out->transfer_buffer_length = buf_len;
			err = usb_submit_urb(irtoy->urb_out, GFP_ATOMIC);
			अगर (err != 0) अणु
				dev_err(irtoy->dev, "fail to submit tx buf urb: %d\n",
					err);
				irtoy->state = STATE_IRDATA;
				complete(&irtoy->command_करोne);
				अवरोध;
			पूर्ण

			irtoy->tx_buf += buf_len;
			irtoy->tx_len -= buf_len;
		पूर्ण
		अवरोध;
	हाल STATE_RESET:
		dev_err(irtoy->dev, "unexpected response to reset: %*phN\n",
			len, irtoy->in);
	पूर्ण
पूर्ण

अटल व्योम irtoy_out_callback(काष्ठा urb *urb)
अणु
	काष्ठा irtoy *irtoy = urb->context;

	अगर (urb->status == 0) अणु
		अगर (irtoy->state == STATE_RESET)
			complete(&irtoy->command_करोne);
	पूर्ण अन्यथा अणु
		dev_warn(irtoy->dev, "out urb status: %d\n", urb->status);
	पूर्ण
पूर्ण

अटल व्योम irtoy_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा irtoy *irtoy = urb->context;
	पूर्णांक ret;

	अगर (urb->status == 0)
		irtoy_response(irtoy, urb->actual_length);
	अन्यथा
		dev_dbg(irtoy->dev, "in urb status: %d\n", urb->status);

	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret && ret != -ENODEV)
		dev_warn(irtoy->dev, "failed to resubmit urb: %d\n", ret);
पूर्ण

अटल पूर्णांक irtoy_command(काष्ठा irtoy *irtoy, स्थिर u8 *cmd, पूर्णांक cmd_len,
			 क्रमागत state state)
अणु
	पूर्णांक err;

	init_completion(&irtoy->command_करोne);

	irtoy->state = state;

	स_नकल(irtoy->out, cmd, cmd_len);
	irtoy->urb_out->transfer_buffer_length = cmd_len;

	err = usb_submit_urb(irtoy->urb_out, GFP_KERNEL);
	अगर (err != 0)
		वापस err;

	अगर (!रुको_क्रम_completion_समयout(&irtoy->command_करोne,
					 msecs_to_jअगरfies(TIMEOUT))) अणु
		usb_समाप्त_urb(irtoy->urb_out);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक irtoy_setup(काष्ठा irtoy *irtoy)
अणु
	पूर्णांक err;

	err = irtoy_command(irtoy, COMMAND_RESET, माप(COMMAND_RESET),
			    STATE_RESET);
	अगर (err != 0) अणु
		dev_err(irtoy->dev, "could not write reset command: %d\n",
			err);
		वापस err;
	पूर्ण

	usleep_range(50, 50);

	// get version
	err = irtoy_command(irtoy, COMMAND_VERSION, माप(COMMAND_VERSION),
			    STATE_COMMAND);
	अगर (err) अणु
		dev_err(irtoy->dev, "could not write version command: %d\n",
			err);
		वापस err;
	पूर्ण

	// enter sample mode
	err = irtoy_command(irtoy, COMMAND_SMODE_ENTER,
			    माप(COMMAND_SMODE_ENTER), STATE_COMMAND);
	अगर (err)
		dev_err(irtoy->dev, "could not write sample command: %d\n",
			err);

	वापस err;
पूर्ण

/*
 * When sending IR, it is imperative that we send the IR data as quickly
 * as possible to the device, so it करोes not run out of IR data and
 * पूर्णांकroduce gaps. Allocate the buffer here, and then feed the data from
 * the urb callback handler.
 */
अटल पूर्णांक irtoy_tx(काष्ठा rc_dev *rc, uपूर्णांक *txbuf, uपूर्णांक count)
अणु
	काष्ठा irtoy *irtoy = rc->priv;
	अचिन्हित पूर्णांक i, size;
	__be16 *buf;
	पूर्णांक err;

	size = माप(u16) * (count + 1);
	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; i++) अणु
		u16 v = DIV_ROUND_CLOSEST(txbuf[i], UNIT_US);

		अगर (!v)
			v = 1;
		buf[i] = cpu_to_be16(v);
	पूर्ण

	buf[count] = cpu_to_be16(0xffff);

	irtoy->tx_buf = buf;
	irtoy->tx_len = size;
	irtoy->emitted = 0;

	err = irtoy_command(irtoy, COMMAND_TXSTART, माप(COMMAND_TXSTART),
			    STATE_TX);
	kमुक्त(buf);

	अगर (err) अणु
		dev_err(irtoy->dev, "failed to send tx start command: %d\n",
			err);
		// not sure what state the device is in, reset it
		irtoy_setup(irtoy);
		वापस err;
	पूर्ण

	अगर (size != irtoy->emitted) अणु
		dev_err(irtoy->dev, "expected %u emitted, got %u\n", size,
			irtoy->emitted);
		// not sure what state the device is in, reset it
		irtoy_setup(irtoy);
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक irtoy_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_host_पूर्णांकerface *idesc = पूर्णांकf->cur_altsetting;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_in = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep_out = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep = शून्य;
	काष्ठा irtoy *irtoy;
	काष्ठा rc_dev *rc;
	काष्ठा urb *urb;
	पूर्णांक i, pipe, err = -ENOMEM;

	क्रम (i = 0; i < idesc->desc.bNumEndpoपूर्णांकs; i++) अणु
		ep = &idesc->endpoपूर्णांक[i].desc;

		अगर (!ep_in && usb_endpoपूर्णांक_is_bulk_in(ep) &&
		    usb_endpoपूर्णांक_maxp(ep) == MAX_PACKET)
			ep_in = ep;

		अगर (!ep_out && usb_endpoपूर्णांक_is_bulk_out(ep) &&
		    usb_endpoपूर्णांक_maxp(ep) == MAX_PACKET)
			ep_out = ep;
	पूर्ण

	अगर (!ep_in || !ep_out) अणु
		dev_err(&पूर्णांकf->dev, "required endpoints not found\n");
		वापस -ENODEV;
	पूर्ण

	irtoy = kzalloc(माप(*irtoy), GFP_KERNEL);
	अगर (!irtoy)
		वापस -ENOMEM;

	irtoy->in = kदो_स्मृति(MAX_PACKET,  GFP_KERNEL);
	अगर (!irtoy->in)
		जाओ मुक्त_irtoy;

	irtoy->out = kदो_स्मृति(MAX_PACKET,  GFP_KERNEL);
	अगर (!irtoy->out)
		जाओ मुक्त_irtoy;

	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rc)
		जाओ मुक्त_irtoy;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		जाओ मुक्त_rcdev;

	pipe = usb_rcvbulkpipe(usbdev, ep_in->bEndpoपूर्णांकAddress);
	usb_fill_bulk_urb(urb, usbdev, pipe, irtoy->in, MAX_PACKET,
			  irtoy_in_callback, irtoy);
	irtoy->urb_in = urb;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb)
		जाओ मुक्त_rcdev;

	pipe = usb_sndbulkpipe(usbdev, ep_out->bEndpoपूर्णांकAddress);
	usb_fill_bulk_urb(urb, usbdev, pipe, irtoy->out, MAX_PACKET,
			  irtoy_out_callback, irtoy);

	irtoy->dev = &पूर्णांकf->dev;
	irtoy->usbdev = usbdev;
	irtoy->rc = rc;
	irtoy->urb_out = urb;
	irtoy->pulse = true;

	err = usb_submit_urb(irtoy->urb_in, GFP_KERNEL);
	अगर (err != 0) अणु
		dev_err(irtoy->dev, "fail to submit in urb: %d\n", err);
		वापस err;
	पूर्ण

	err = irtoy_setup(irtoy);
	अगर (err)
		जाओ मुक्त_rcdev;

	dev_info(irtoy->dev, "version: hardware %u, firmware %u, protocol %u",
		 irtoy->hw_version, irtoy->sw_version, irtoy->proto_version);

	अगर (irtoy->sw_version < MIN_FW_VERSION) अणु
		dev_err(irtoy->dev, "need firmware V%02u or higher",
			MIN_FW_VERSION);
		err = -ENODEV;
		जाओ मुक्त_rcdev;
	पूर्ण

	usb_make_path(usbdev, irtoy->phys, माप(irtoy->phys));

	rc->device_name = "Infrared Toy";
	rc->driver_name = KBUILD_MODNAME;
	rc->input_phys = irtoy->phys;
	usb_to_input_id(usbdev, &rc->input_id);
	rc->dev.parent = &पूर्णांकf->dev;
	rc->priv = irtoy;
	rc->tx_ir = irtoy_tx;
	rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rc->map_name = RC_MAP_RC6_MCE;
	rc->rx_resolution = UNIT_US;
	rc->समयout = IR_DEFAULT_TIMEOUT;

	/*
	 * end of transmission is detected by असलence of a usb packet
	 * with more pulse/spaces. However, each usb packet sent can
	 * contain 32 pulse/spaces, which can be quite lengthy, so there
	 * can be a delay between usb packets. For example with nec there is a
	 * 17ms gap between packets.
	 *
	 * So, make समयout a largish minimum which works with most protocols.
	 */
	rc->min_समयout = MS_TO_US(40);
	rc->max_समयout = MAX_TIMEOUT_US;

	err = rc_रेजिस्टर_device(rc);
	अगर (err)
		जाओ मुक्त_rcdev;

	usb_set_पूर्णांकfdata(पूर्णांकf, irtoy);

	वापस 0;

मुक्त_rcdev:
	usb_समाप्त_urb(irtoy->urb_out);
	usb_मुक्त_urb(irtoy->urb_out);
	usb_समाप्त_urb(irtoy->urb_in);
	usb_मुक्त_urb(irtoy->urb_in);
	rc_मुक्त_device(rc);
मुक्त_irtoy:
	kमुक्त(irtoy->in);
	kमुक्त(irtoy->out);
	kमुक्त(irtoy);
	वापस err;
पूर्ण

अटल व्योम irtoy_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा irtoy *ir = usb_get_पूर्णांकfdata(पूर्णांकf);

	rc_unरेजिस्टर_device(ir->rc);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_समाप्त_urb(ir->urb_out);
	usb_मुक्त_urb(ir->urb_out);
	usb_समाप्त_urb(ir->urb_in);
	usb_मुक्त_urb(ir->urb_in);
	kमुक्त(ir->in);
	kमुक्त(ir->out);
	kमुक्त(ir);
पूर्ण

अटल स्थिर काष्ठा usb_device_id irtoy_table[] = अणु
	अणु USB_DEVICE_INTERFACE_CLASS(0x04d8, 0xfd08, USB_CLASS_CDC_DATA) पूर्ण,
	अणु USB_DEVICE_INTERFACE_CLASS(0x04d8, 0xf58b, USB_CLASS_CDC_DATA) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा usb_driver irtoy_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = irtoy_probe,
	.disconnect = irtoy_disconnect,
	.id_table = irtoy_table,
पूर्ण;

module_usb_driver(irtoy_driver);

MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_DESCRIPTION("Infrared Toy and IR Droid driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(usb, irtoy_table);
