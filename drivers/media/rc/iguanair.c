<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IguanaWorks USB IR Transceiver support
 *
 * Copyright (C) 2012 Sean Young <sean@mess.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <media/rc-core.h>

#घोषणा BUF_SIZE 152

काष्ठा iguanair अणु
	काष्ठा rc_dev *rc;

	काष्ठा device *dev;
	काष्ठा usb_device *udev;

	uपूर्णांक16_t version;
	uपूर्णांक8_t bufsize;
	uपूर्णांक8_t cycle_overhead;

	/* receiver support */
	bool receiver_on;
	dma_addr_t dma_in, dma_out;
	uपूर्णांक8_t *buf_in;
	काष्ठा urb *urb_in, *urb_out;
	काष्ठा completion completion;

	/* transmit support */
	bool tx_overflow;
	uपूर्णांक32_t carrier;
	काष्ठा send_packet *packet;

	अक्षर name[64];
	अक्षर phys[64];
पूर्ण;

#घोषणा CMD_NOP			0x00
#घोषणा CMD_GET_VERSION		0x01
#घोषणा CMD_GET_बफ_मानE		0x11
#घोषणा CMD_GET_FEATURES	0x10
#घोषणा CMD_SEND		0x15
#घोषणा CMD_EXECUTE		0x1f
#घोषणा CMD_RX_OVERFLOW		0x31
#घोषणा CMD_TX_OVERFLOW		0x32
#घोषणा CMD_RECEIVER_ON		0x12
#घोषणा CMD_RECEIVER_OFF	0x14

#घोषणा सूची_IN			0xdc
#घोषणा सूची_OUT			0xcd

#घोषणा MAX_IN_PACKET		8u
#घोषणा MAX_OUT_PACKET		(माप(काष्ठा send_packet) + BUF_SIZE)
#घोषणा TIMEOUT			1000
#घोषणा RX_RESOLUTION		21

काष्ठा packet अणु
	uपूर्णांक16_t start;
	uपूर्णांक8_t direction;
	uपूर्णांक8_t cmd;
पूर्ण;

काष्ठा send_packet अणु
	काष्ठा packet header;
	uपूर्णांक8_t length;
	uपूर्णांक8_t channels;
	uपूर्णांक8_t busy7;
	uपूर्णांक8_t busy4;
	uपूर्णांक8_t payload[];
पूर्ण;

अटल व्योम process_ir_data(काष्ठा iguanair *ir, अचिन्हित len)
अणु
	अगर (len >= 4 && ir->buf_in[0] == 0 && ir->buf_in[1] == 0) अणु
		चयन (ir->buf_in[3]) अणु
		हाल CMD_GET_VERSION:
			अगर (len == 6) अणु
				ir->version = (ir->buf_in[5] << 8) |
							ir->buf_in[4];
				complete(&ir->completion);
			पूर्ण
			अवरोध;
		हाल CMD_GET_बफ_मानE:
			अगर (len >= 5) अणु
				ir->bufsize = ir->buf_in[4];
				complete(&ir->completion);
			पूर्ण
			अवरोध;
		हाल CMD_GET_FEATURES:
			अगर (len > 5) अणु
				ir->cycle_overhead = ir->buf_in[5];
				complete(&ir->completion);
			पूर्ण
			अवरोध;
		हाल CMD_TX_OVERFLOW:
			ir->tx_overflow = true;
			fallthrough;
		हाल CMD_RECEIVER_OFF:
		हाल CMD_RECEIVER_ON:
		हाल CMD_SEND:
			complete(&ir->completion);
			अवरोध;
		हाल CMD_RX_OVERFLOW:
			dev_warn(ir->dev, "receive overflow\n");
			ir_raw_event_reset(ir->rc);
			अवरोध;
		शेष:
			dev_warn(ir->dev, "control code %02x received\n",
							ir->buf_in[3]);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (len >= 7) अणु
		काष्ठा ir_raw_event rawir = अणुपूर्ण;
		अचिन्हित i;
		bool event = false;

		क्रम (i = 0; i < 7; i++) अणु
			अगर (ir->buf_in[i] == 0x80) अणु
				rawir.pulse = false;
				rawir.duration = 21845;
			पूर्ण अन्यथा अणु
				rawir.pulse = (ir->buf_in[i] & 0x80) == 0;
				rawir.duration = ((ir->buf_in[i] & 0x7f) + 1) *
								 RX_RESOLUTION;
			पूर्ण

			अगर (ir_raw_event_store_with_filter(ir->rc, &rawir))
				event = true;
		पूर्ण

		अगर (event)
			ir_raw_event_handle(ir->rc);
	पूर्ण
पूर्ण

अटल व्योम iguanair_rx(काष्ठा urb *urb)
अणु
	काष्ठा iguanair *ir;
	पूर्णांक rc;

	अगर (!urb)
		वापस;

	ir = urb->context;
	अगर (!ir) अणु
		usb_unlink_urb(urb);
		वापस;
	पूर्ण

	चयन (urb->status) अणु
	हाल 0:
		process_ir_data(ir, urb->actual_length);
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		usb_unlink_urb(urb);
		वापस;
	हाल -EPIPE:
	शेष:
		dev_dbg(ir->dev, "Error: urb status = %d\n", urb->status);
		अवरोध;
	पूर्ण

	rc = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (rc && rc != -ENODEV)
		dev_warn(ir->dev, "failed to resubmit urb: %d\n", rc);
पूर्ण

अटल व्योम iguanair_irq_out(काष्ठा urb *urb)
अणु
	काष्ठा iguanair *ir = urb->context;

	अगर (urb->status)
		dev_dbg(ir->dev, "Error: out urb status = %d\n", urb->status);

	/* अगर we sent an nop packet, करो not expect a response */
	अगर (urb->status == 0 && ir->packet->header.cmd == CMD_NOP)
		complete(&ir->completion);
पूर्ण

अटल पूर्णांक iguanair_send(काष्ठा iguanair *ir, अचिन्हित size)
अणु
	पूर्णांक rc;

	reinit_completion(&ir->completion);

	ir->urb_out->transfer_buffer_length = size;
	rc = usb_submit_urb(ir->urb_out, GFP_KERNEL);
	अगर (rc)
		वापस rc;

	अगर (रुको_क्रम_completion_समयout(&ir->completion, TIMEOUT) == 0)
		वापस -ETIMEDOUT;

	वापस rc;
पूर्ण

अटल पूर्णांक iguanair_get_features(काष्ठा iguanair *ir)
अणु
	पूर्णांक rc;

	/*
	 * On cold boot, the iguanair initializes on the first packet
	 * received but करोes not process that packet. Send an empty
	 * packet.
	 */
	ir->packet->header.start = 0;
	ir->packet->header.direction = सूची_OUT;
	ir->packet->header.cmd = CMD_NOP;
	iguanair_send(ir, माप(ir->packet->header));

	ir->packet->header.cmd = CMD_GET_VERSION;
	rc = iguanair_send(ir, माप(ir->packet->header));
	अगर (rc) अणु
		dev_info(ir->dev, "failed to get version\n");
		जाओ out;
	पूर्ण

	अगर (ir->version < 0x205) अणु
		dev_err(ir->dev, "firmware 0x%04x is too old\n", ir->version);
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	ir->bufsize = 150;
	ir->cycle_overhead = 65;

	ir->packet->header.cmd = CMD_GET_बफ_मानE;

	rc = iguanair_send(ir, माप(ir->packet->header));
	अगर (rc) अणु
		dev_info(ir->dev, "failed to get buffer size\n");
		जाओ out;
	पूर्ण

	अगर (ir->bufsize > BUF_SIZE) अणु
		dev_info(ir->dev, "buffer size %u larger than expected\n",
								ir->bufsize);
		ir->bufsize = BUF_SIZE;
	पूर्ण

	ir->packet->header.cmd = CMD_GET_FEATURES;

	rc = iguanair_send(ir, माप(ir->packet->header));
	अगर (rc)
		dev_info(ir->dev, "failed to get features\n");
out:
	वापस rc;
पूर्ण

अटल पूर्णांक iguanair_receiver(काष्ठा iguanair *ir, bool enable)
अणु
	ir->packet->header.start = 0;
	ir->packet->header.direction = सूची_OUT;
	ir->packet->header.cmd = enable ? CMD_RECEIVER_ON : CMD_RECEIVER_OFF;

	अगर (enable)
		ir_raw_event_reset(ir->rc);

	वापस iguanair_send(ir, माप(ir->packet->header));
पूर्ण

/*
 * The iguanair creates the carrier by busy spinning after each half period.
 * This is counted in CPU cycles, with the CPU running at 24MHz. It is
 * broken करोwn पूर्णांकo 7-cycles and 4-cyles delays, with a preference क्रम
 * 4-cycle delays, minus the overhead of the loop itself (cycle_overhead).
 */
अटल पूर्णांक iguanair_set_tx_carrier(काष्ठा rc_dev *dev, uपूर्णांक32_t carrier)
अणु
	काष्ठा iguanair *ir = dev->priv;

	अगर (carrier < 25000 || carrier > 150000)
		वापस -EINVAL;

	अगर (carrier != ir->carrier) अणु
		uपूर्णांक32_t cycles, fours, sevens;

		ir->carrier = carrier;

		cycles = DIV_ROUND_CLOSEST(24000000, carrier * 2) -
							ir->cycle_overhead;

		/*
		 * Calculate minimum number of 7 cycles needed so
		 * we are left with a multiple of 4; so we want to have
		 * (sevens * 7) & 3 == cycles & 3
		 */
		sevens = (4 - cycles) & 3;
		fours = (cycles - sevens * 7) / 4;

		/*
		 * The firmware पूर्णांकerprets these values as a relative offset
		 * क्रम a branch. Immediately following the branches, there
		 * 4 inकाष्ठाions of 7 cycles (2 bytes each) and 110
		 * inकाष्ठाions of 4 cycles (1 byte each). A relative branch
		 * of 0 will execute all of them, branch further क्रम less
		 * cycle burning.
		 */
		ir->packet->busy7 = (4 - sevens) * 2;
		ir->packet->busy4 = 110 - fours;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iguanair_set_tx_mask(काष्ठा rc_dev *dev, uपूर्णांक32_t mask)
अणु
	काष्ठा iguanair *ir = dev->priv;

	अगर (mask > 15)
		वापस 4;

	ir->packet->channels = mask << 4;

	वापस 0;
पूर्ण

अटल पूर्णांक iguanair_tx(काष्ठा rc_dev *dev, अचिन्हित *txbuf, अचिन्हित count)
अणु
	काष्ठा iguanair *ir = dev->priv;
	अचिन्हित पूर्णांक i, size, p, periods;
	पूर्णांक rc;

	/* convert from us to carrier periods */
	क्रम (i = size = 0; i < count; i++) अणु
		periods = DIV_ROUND_CLOSEST(txbuf[i] * ir->carrier, 1000000);
		जबतक (periods) अणु
			p = min(periods, 127u);
			अगर (size >= ir->bufsize) अणु
				rc = -EINVAL;
				जाओ out;
			पूर्ण
			ir->packet->payload[size++] = p | ((i & 1) ? 0x80 : 0);
			periods -= p;
		पूर्ण
	पूर्ण

	ir->packet->header.start = 0;
	ir->packet->header.direction = सूची_OUT;
	ir->packet->header.cmd = CMD_SEND;
	ir->packet->length = size;

	ir->tx_overflow = false;

	rc = iguanair_send(ir, माप(*ir->packet) + size);

	अगर (rc == 0 && ir->tx_overflow)
		rc = -EOVERFLOW;

out:
	वापस rc ? rc : count;
पूर्ण

अटल पूर्णांक iguanair_खोलो(काष्ठा rc_dev *rdev)
अणु
	काष्ठा iguanair *ir = rdev->priv;
	पूर्णांक rc;

	rc = iguanair_receiver(ir, true);
	अगर (rc == 0)
		ir->receiver_on = true;

	वापस rc;
पूर्ण

अटल व्योम iguanair_बंद(काष्ठा rc_dev *rdev)
अणु
	काष्ठा iguanair *ir = rdev->priv;
	पूर्णांक rc;

	rc = iguanair_receiver(ir, false);
	ir->receiver_on = false;
	अगर (rc && rc != -ENODEV)
		dev_warn(ir->dev, "failed to disable receiver: %d\n", rc);
पूर्ण

अटल पूर्णांक iguanair_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा iguanair *ir;
	काष्ठा rc_dev *rc;
	पूर्णांक ret, pipein, pipeout;
	काष्ठा usb_host_पूर्णांकerface *idesc;

	idesc = पूर्णांकf->cur_altsetting;
	अगर (idesc->desc.bNumEndpoपूर्णांकs < 2)
		वापस -ENODEV;

	ir = kzalloc(माप(*ir), GFP_KERNEL);
	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!ir || !rc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ir->buf_in = usb_alloc_coherent(udev, MAX_IN_PACKET, GFP_KERNEL,
								&ir->dma_in);
	ir->packet = usb_alloc_coherent(udev, MAX_OUT_PACKET, GFP_KERNEL,
								&ir->dma_out);
	ir->urb_in = usb_alloc_urb(0, GFP_KERNEL);
	ir->urb_out = usb_alloc_urb(0, GFP_KERNEL);

	अगर (!ir->buf_in || !ir->packet || !ir->urb_in || !ir->urb_out ||
	    !usb_endpoपूर्णांक_is_पूर्णांक_in(&idesc->endpoपूर्णांक[0].desc) ||
	    !usb_endpoपूर्णांक_is_पूर्णांक_out(&idesc->endpoपूर्णांक[1].desc)) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ir->rc = rc;
	ir->dev = &पूर्णांकf->dev;
	ir->udev = udev;

	init_completion(&ir->completion);
	pipeout = usb_sndपूर्णांकpipe(udev,
				idesc->endpoपूर्णांक[1].desc.bEndpoपूर्णांकAddress);
	usb_fill_पूर्णांक_urb(ir->urb_out, udev, pipeout, ir->packet, MAX_OUT_PACKET,
						iguanair_irq_out, ir, 1);
	ir->urb_out->transfer_dma = ir->dma_out;
	ir->urb_out->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	pipein = usb_rcvपूर्णांकpipe(udev, idesc->endpoपूर्णांक[0].desc.bEndpoपूर्णांकAddress);
	usb_fill_पूर्णांक_urb(ir->urb_in, udev, pipein, ir->buf_in, MAX_IN_PACKET,
							 iguanair_rx, ir, 1);
	ir->urb_in->transfer_dma = ir->dma_in;
	ir->urb_in->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	ret = usb_submit_urb(ir->urb_in, GFP_KERNEL);
	अगर (ret) अणु
		dev_warn(&पूर्णांकf->dev, "failed to submit urb: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = iguanair_get_features(ir);
	अगर (ret)
		जाओ out2;

	snम_लिखो(ir->name, माप(ir->name),
		"IguanaWorks USB IR Transceiver version 0x%04x", ir->version);

	usb_make_path(ir->udev, ir->phys, माप(ir->phys));

	rc->device_name = ir->name;
	rc->input_phys = ir->phys;
	usb_to_input_id(ir->udev, &rc->input_id);
	rc->dev.parent = &पूर्णांकf->dev;
	rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rc->priv = ir;
	rc->खोलो = iguanair_खोलो;
	rc->बंद = iguanair_बंद;
	rc->s_tx_mask = iguanair_set_tx_mask;
	rc->s_tx_carrier = iguanair_set_tx_carrier;
	rc->tx_ir = iguanair_tx;
	rc->driver_name = KBUILD_MODNAME;
	rc->map_name = RC_MAP_RC6_MCE;
	rc->min_समयout = 1;
	rc->समयout = IR_DEFAULT_TIMEOUT;
	rc->max_समयout = 10 * IR_DEFAULT_TIMEOUT;
	rc->rx_resolution = RX_RESOLUTION;

	iguanair_set_tx_carrier(rc, 38000);
	iguanair_set_tx_mask(rc, 0);

	ret = rc_रेजिस्टर_device(rc);
	अगर (ret < 0) अणु
		dev_err(&पूर्णांकf->dev, "failed to register rc device %d", ret);
		जाओ out2;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, ir);

	वापस 0;
out2:
	usb_समाप्त_urb(ir->urb_in);
	usb_समाप्त_urb(ir->urb_out);
out:
	अगर (ir) अणु
		usb_मुक्त_urb(ir->urb_in);
		usb_मुक्त_urb(ir->urb_out);
		usb_मुक्त_coherent(udev, MAX_IN_PACKET, ir->buf_in, ir->dma_in);
		usb_मुक्त_coherent(udev, MAX_OUT_PACKET, ir->packet,
								ir->dma_out);
	पूर्ण
	rc_मुक्त_device(rc);
	kमुक्त(ir);
	वापस ret;
पूर्ण

अटल व्योम iguanair_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा iguanair *ir = usb_get_पूर्णांकfdata(पूर्णांकf);

	rc_unरेजिस्टर_device(ir->rc);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_समाप्त_urb(ir->urb_in);
	usb_समाप्त_urb(ir->urb_out);
	usb_मुक्त_urb(ir->urb_in);
	usb_मुक्त_urb(ir->urb_out);
	usb_मुक्त_coherent(ir->udev, MAX_IN_PACKET, ir->buf_in, ir->dma_in);
	usb_मुक्त_coherent(ir->udev, MAX_OUT_PACKET, ir->packet, ir->dma_out);
	kमुक्त(ir);
पूर्ण

अटल पूर्णांक iguanair_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा iguanair *ir = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक rc = 0;

	अगर (ir->receiver_on) अणु
		rc = iguanair_receiver(ir, false);
		अगर (rc)
			dev_warn(ir->dev, "failed to disable receiver for suspend\n");
	पूर्ण

	usb_समाप्त_urb(ir->urb_in);
	usb_समाप्त_urb(ir->urb_out);

	वापस rc;
पूर्ण

अटल पूर्णांक iguanair_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा iguanair *ir = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक rc;

	rc = usb_submit_urb(ir->urb_in, GFP_KERNEL);
	अगर (rc)
		dev_warn(&पूर्णांकf->dev, "failed to submit urb: %d\n", rc);

	अगर (ir->receiver_on) अणु
		rc = iguanair_receiver(ir, true);
		अगर (rc)
			dev_warn(ir->dev, "failed to enable receiver after resume\n");
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा usb_device_id iguanair_table[] = अणु
	अणु USB_DEVICE(0x1781, 0x0938) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा usb_driver iguanair_driver = अणु
	.name =	KBUILD_MODNAME,
	.probe = iguanair_probe,
	.disconnect = iguanair_disconnect,
	.suspend = iguanair_suspend,
	.resume = iguanair_resume,
	.reset_resume = iguanair_resume,
	.id_table = iguanair_table,
	.soft_unbind = 1	/* we want to disable receiver on unbind */
पूर्ण;

module_usb_driver(iguanair_driver);

MODULE_DESCRIPTION("IguanaWorks USB IR Transceiver");
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(usb, iguanair_table);

