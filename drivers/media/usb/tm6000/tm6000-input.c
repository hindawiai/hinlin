<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  पंचांग6000-input.c - driver क्रम TM5600/TM6000/TM6010 USB video capture devices
 *
 *  Copyright (C) 2010 Stefan Ringel <stefan.ringel@arcor.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश <linux/input.h>
#समावेश <linux/usb.h>

#समावेश <media/rc-core.h>

#समावेश "tm6000.h"
#समावेश "tm6000-regs.h"

अटल अचिन्हित पूर्णांक ir_debug;
module_param(ir_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(ir_debug, "debug message level");

अटल अचिन्हित पूर्णांक enable_ir = 1;
module_param(enable_ir, पूर्णांक, 0644);
MODULE_PARM_DESC(enable_ir, "enable ir (default is enable)");

अटल अचिन्हित पूर्णांक ir_घड़ी_mhz = 12;
module_param(ir_घड़ी_mhz, पूर्णांक, 0644);
MODULE_PARM_DESC(ir_घड़ी_mhz, "ir clock, in MHz");

#घोषणा URB_SUBMIT_DELAY	100	/* ms - Delay to submit an URB request on retrial and init */
#घोषणा URB_INT_LED_DELAY	100	/* ms - Delay to turn led on again on पूर्णांक mode */

#अघोषित dprपूर्णांकk

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु\
	अगर (ir_debug >= level) \
		prपूर्णांकk(KERN_DEBUG "%s/ir: " fmt, ir->name , ## arg); \
	पूर्ण जबतक (0)

काष्ठा पंचांग6000_ir_poll_result अणु
	u16 rc_data;
पूर्ण;

काष्ठा पंचांग6000_IR अणु
	काष्ठा पंचांग6000_core	*dev;
	काष्ठा rc_dev		*rc;
	अक्षर			name[32];
	अक्षर			phys[32];

	/* poll expernal decoder */
	पूर्णांक			polling;
	काष्ठा delayed_work	work;
	u8			रुको:1;
	u8			pwled:2;
	u8			submit_urb:1;
	काष्ठा urb		*पूर्णांक_urb;

	/* IR device properties */
	u64			rc_proto;
पूर्ण;

व्योम पंचांग6000_ir_रुको(काष्ठा पंचांग6000_core *dev, u8 state)
अणु
	काष्ठा पंचांग6000_IR *ir = dev->ir;

	अगर (!dev->ir)
		वापस;

	dprपूर्णांकk(2, "%s: %i\n",__func__, ir->रुको);

	अगर (state)
		ir->रुको = 1;
	अन्यथा
		ir->रुको = 0;
पूर्ण

अटल पूर्णांक पंचांग6000_ir_config(काष्ठा पंचांग6000_IR *ir)
अणु
	काष्ठा पंचांग6000_core *dev = ir->dev;
	u32 pulse = 0, leader = 0;

	dprपूर्णांकk(2, "%s\n",__func__);

	/*
	 * The IR decoder supports RC-5 or NEC, with a configurable timing.
	 * The timing configuration there is not that accurate, as it uses
	 * approximate values. The NEC spec mentions a 562.5 unit period,
	 * and RC-5 uses a 888.8 period.
	 * Currently, driver assumes a घड़ी provided by a 12 MHz XTAL, but
	 * a modprobe parameter can adjust it.
	 * Adjusपंचांगents are required क्रम other timings.
	 * It seems that the 900ms timing क्रम NEC is used to detect a RC-5
	 * IR, in order to discard such decoding
	 */

	चयन (ir->rc_proto) अणु
	हाल RC_PROTO_BIT_NEC:
		leader = 900;	/* ms */
		pulse  = 700;	/* ms - the actual value would be 562 */
		अवरोध;
	शेष:
	हाल RC_PROTO_BIT_RC5:
		leader = 900;	/* ms - from the NEC decoding */
		pulse  = 1780;	/* ms - The actual value would be 1776 */
		अवरोध;
	पूर्ण

	pulse = ir_घड़ी_mhz * pulse;
	leader = ir_घड़ी_mhz * leader;
	अगर (ir->rc_proto == RC_PROTO_BIT_NEC)
		leader = leader | 0x8000;

	dprपूर्णांकk(2, "%s: %s, %d MHz, leader = 0x%04x, pulse = 0x%06x \n",
		__func__,
		(ir->rc_proto == RC_PROTO_BIT_NEC) ? "NEC" : "RC-5",
		ir_घड़ी_mhz, leader, pulse);

	/* Remote WAKEUP = enable, normal mode, from IR decoder output */
	पंचांग6000_set_reg(dev, TM6010_REQ07_RE5_REMOTE_WAKEUP, 0xfe);

	/* Enable IR reception on non-busrt mode */
	पंचांग6000_set_reg(dev, TM6010_REQ07_RD8_IR, 0x2f);

	/* IR_WKUP_SEL = Low byte in decoded IR data */
	पंचांग6000_set_reg(dev, TM6010_REQ07_RDA_IR_WAKEUP_SEL, 0xff);
	/* IR_WKU_ADD code */
	पंचांग6000_set_reg(dev, TM6010_REQ07_RDB_IR_WAKEUP_ADD, 0xff);

	पंचांग6000_set_reg(dev, TM6010_REQ07_RDC_IR_LEADER1, leader >> 8);
	पंचांग6000_set_reg(dev, TM6010_REQ07_RDD_IR_LEADER0, leader);

	पंचांग6000_set_reg(dev, TM6010_REQ07_RDE_IR_PULSE_CNT1, pulse >> 8);
	पंचांग6000_set_reg(dev, TM6010_REQ07_RDF_IR_PULSE_CNT0, pulse);

	अगर (!ir->polling)
		पंचांग6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT, 2, 0);
	अन्यथा
		पंचांग6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT, 2, 1);
	msleep(10);

	/* Shows that IR is working via the LED */
	पंचांग6000_flash_led(dev, 0);
	msleep(100);
	पंचांग6000_flash_led(dev, 1);
	ir->pwled = 1;

	वापस 0;
पूर्ण

अटल व्योम पंचांग6000_ir_keyकरोwn(काष्ठा पंचांग6000_IR *ir,
			      स्थिर अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	u8 device, command;
	u32 scancode;
	क्रमागत rc_proto protocol;

	अगर (len < 1)
		वापस;

	command = buf[0];
	device = (len > 1 ? buf[1] : 0x0);
	चयन (ir->rc_proto) अणु
	हाल RC_PROTO_BIT_RC5:
		protocol = RC_PROTO_RC5;
		scancode = RC_SCANCODE_RC5(device, command);
		अवरोध;
	हाल RC_PROTO_BIT_NEC:
		protocol = RC_PROTO_NEC;
		scancode = RC_SCANCODE_NEC(device, command);
		अवरोध;
	शेष:
		protocol = RC_PROTO_OTHER;
		scancode = RC_SCANCODE_OTHER(device << 8 | command);
		अवरोध;
	पूर्ण

	dprपूर्णांकk(1, "%s, protocol: 0x%04x, scancode: 0x%08x\n",
		__func__, protocol, scancode);
	rc_keyकरोwn(ir->rc, protocol, scancode, 0);
पूर्ण

अटल व्योम पंचांग6000_ir_urb_received(काष्ठा urb *urb)
अणु
	काष्ठा पंचांग6000_core *dev = urb->context;
	काष्ठा पंचांग6000_IR *ir = dev->ir;
	अक्षर *buf;

	dprपूर्णांकk(2, "%s\n",__func__);
	अगर (urb->status < 0 || urb->actual_length <= 0) अणु
		prपूर्णांकk(KERN_INFO "tm6000: IR URB failure: status: %i, length %i\n",
		       urb->status, urb->actual_length);
		ir->submit_urb = 1;
		schedule_delayed_work(&ir->work, msecs_to_jअगरfies(URB_SUBMIT_DELAY));
		वापस;
	पूर्ण
	buf = urb->transfer_buffer;

	अगर (ir_debug)
		prपूर्णांक_hex_dump(KERN_DEBUG, "tm6000: IR data: ",
			       DUMP_PREFIX_OFFSET,16, 1,
			       buf, urb->actual_length, false);

	पंचांग6000_ir_keyकरोwn(ir, urb->transfer_buffer, urb->actual_length);

	usb_submit_urb(urb, GFP_ATOMIC);
	/*
	 * Flash the led. We can't करो it here, as it is running on IRQ context.
	 * So, use the scheduler to करो it, in a few ms.
	 */
	ir->pwled = 2;
	schedule_delayed_work(&ir->work, msecs_to_jअगरfies(10));
पूर्ण

अटल व्योम पंचांग6000_ir_handle_key(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पंचांग6000_IR *ir = container_of(work, काष्ठा पंचांग6000_IR, work.work);
	काष्ठा पंचांग6000_core *dev = ir->dev;
	पूर्णांक rc;
	u8 buf[2];

	अगर (ir->रुको)
		वापस;

	dprपूर्णांकk(3, "%s\n",__func__);

	rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_IN |
		USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		REQ_02_GET_IR_CODE, 0, 0, buf, 2);
	अगर (rc < 0)
		वापस;

	/* Check अगर something was पढ़ो */
	अगर ((buf[0] & 0xff) == 0xff) अणु
		अगर (!ir->pwled) अणु
			पंचांग6000_flash_led(dev, 1);
			ir->pwled = 1;
		पूर्ण
		वापस;
	पूर्ण

	पंचांग6000_ir_keyकरोwn(ir, buf, rc);
	पंचांग6000_flash_led(dev, 0);
	ir->pwled = 0;

	/* Re-schedule polling */
	schedule_delayed_work(&ir->work, msecs_to_jअगरfies(ir->polling));
पूर्ण

अटल व्योम पंचांग6000_ir_पूर्णांक_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पंचांग6000_IR *ir = container_of(work, काष्ठा पंचांग6000_IR, work.work);
	काष्ठा पंचांग6000_core *dev = ir->dev;
	पूर्णांक rc;

	dprपूर्णांकk(3, "%s, submit_urb = %d, pwled = %d\n",__func__, ir->submit_urb,
		ir->pwled);

	अगर (ir->submit_urb) अणु
		dprपूर्णांकk(3, "Resubmit urb\n");
		पंचांग6000_set_reg(dev, REQ_04_EN_DISABLE_MCU_INT, 2, 0);

		rc = usb_submit_urb(ir->पूर्णांक_urb, GFP_ATOMIC);
		अगर (rc < 0) अणु
			prपूर्णांकk(KERN_ERR "tm6000: Can't submit an IR interrupt. Error %i\n",
			       rc);
			/* Retry in 100 ms */
			schedule_delayed_work(&ir->work, msecs_to_jअगरfies(URB_SUBMIT_DELAY));
			वापस;
		पूर्ण
		ir->submit_urb = 0;
	पूर्ण

	/* Led is enabled only अगर USB submit करोesn't fail */
	अगर (ir->pwled == 2) अणु
		पंचांग6000_flash_led(dev, 0);
		ir->pwled = 0;
		schedule_delayed_work(&ir->work, msecs_to_jअगरfies(URB_INT_LED_DELAY));
	पूर्ण अन्यथा अगर (!ir->pwled) अणु
		पंचांग6000_flash_led(dev, 1);
		ir->pwled = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक पंचांग6000_ir_start(काष्ठा rc_dev *rc)
अणु
	काष्ठा पंचांग6000_IR *ir = rc->priv;

	dprपूर्णांकk(2, "%s\n",__func__);

	schedule_delayed_work(&ir->work, 0);

	वापस 0;
पूर्ण

अटल व्योम पंचांग6000_ir_stop(काष्ठा rc_dev *rc)
अणु
	काष्ठा पंचांग6000_IR *ir = rc->priv;

	dprपूर्णांकk(2, "%s\n",__func__);

	cancel_delayed_work_sync(&ir->work);
पूर्ण

अटल पूर्णांक पंचांग6000_ir_change_protocol(काष्ठा rc_dev *rc, u64 *rc_proto)
अणु
	काष्ठा पंचांग6000_IR *ir = rc->priv;

	अगर (!ir)
		वापस 0;

	dprपूर्णांकk(2, "%s\n",__func__);

	ir->rc_proto = *rc_proto;

	पंचांग6000_ir_config(ir);
	/* TODO */
	वापस 0;
पूर्ण

अटल पूर्णांक __पंचांग6000_ir_पूर्णांक_start(काष्ठा rc_dev *rc)
अणु
	काष्ठा पंचांग6000_IR *ir = rc->priv;
	काष्ठा पंचांग6000_core *dev;
	पूर्णांक pipe, size;
	पूर्णांक err = -ENOMEM;

	अगर (!ir)
		वापस -ENODEV;
	dev = ir->dev;

	dprपूर्णांकk(2, "%s\n",__func__);

	ir->पूर्णांक_urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!ir->पूर्णांक_urb)
		वापस -ENOMEM;

	pipe = usb_rcvपूर्णांकpipe(dev->udev,
		dev->पूर्णांक_in.endp->desc.bEndpoपूर्णांकAddress
		& USB_ENDPOINT_NUMBER_MASK);

	size = usb_maxpacket(dev->udev, pipe, usb_pipeout(pipe));
	dprपूर्णांकk(1, "IR max size: %d\n", size);

	ir->पूर्णांक_urb->transfer_buffer = kzalloc(size, GFP_ATOMIC);
	अगर (!ir->पूर्णांक_urb->transfer_buffer) अणु
		usb_मुक्त_urb(ir->पूर्णांक_urb);
		वापस err;
	पूर्ण
	dprपूर्णांकk(1, "int interval: %d\n", dev->पूर्णांक_in.endp->desc.bInterval);

	usb_fill_पूर्णांक_urb(ir->पूर्णांक_urb, dev->udev, pipe,
		ir->पूर्णांक_urb->transfer_buffer, size,
		पंचांग6000_ir_urb_received, dev,
		dev->पूर्णांक_in.endp->desc.bInterval);

	ir->submit_urb = 1;
	schedule_delayed_work(&ir->work, msecs_to_jअगरfies(URB_SUBMIT_DELAY));

	वापस 0;
पूर्ण

अटल व्योम __पंचांग6000_ir_पूर्णांक_stop(काष्ठा rc_dev *rc)
अणु
	काष्ठा पंचांग6000_IR *ir = rc->priv;

	अगर (!ir || !ir->पूर्णांक_urb)
		वापस;

	dprपूर्णांकk(2, "%s\n",__func__);

	usb_समाप्त_urb(ir->पूर्णांक_urb);
	kमुक्त(ir->पूर्णांक_urb->transfer_buffer);
	usb_मुक्त_urb(ir->पूर्णांक_urb);
	ir->पूर्णांक_urb = शून्य;
पूर्ण

पूर्णांक पंचांग6000_ir_पूर्णांक_start(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_IR *ir = dev->ir;

	अगर (!ir)
		वापस 0;

	वापस __पंचांग6000_ir_पूर्णांक_start(ir->rc);
पूर्ण

व्योम पंचांग6000_ir_पूर्णांक_stop(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_IR *ir = dev->ir;

	अगर (!ir || !ir->rc)
		वापस;

	__पंचांग6000_ir_पूर्णांक_stop(ir->rc);
पूर्ण

पूर्णांक पंचांग6000_ir_init(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_IR *ir;
	काष्ठा rc_dev *rc;
	पूर्णांक err = -ENOMEM;
	u64 rc_proto;

	अगर (!enable_ir)
		वापस -ENODEV;

	अगर (!dev->caps.has_remote)
		वापस 0;

	अगर (!dev->ir_codes)
		वापस 0;

	ir = kzalloc(माप(*ir), GFP_ATOMIC);
	rc = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!ir || !rc)
		जाओ out;

	dprपूर्णांकk(2, "%s\n", __func__);

	/* record handles to ourself */
	ir->dev = dev;
	dev->ir = ir;
	ir->rc = rc;

	/* input setup */
	rc->allowed_protocols = RC_PROTO_BIT_RC5 | RC_PROTO_BIT_NEC;
	/* Needed, in order to support NEC remotes with 24 or 32 bits */
	rc->scancode_mask = 0xffff;
	rc->priv = ir;
	rc->change_protocol = पंचांग6000_ir_change_protocol;
	अगर (dev->पूर्णांक_in.endp) अणु
		rc->खोलो    = __पंचांग6000_ir_पूर्णांक_start;
		rc->बंद   = __पंचांग6000_ir_पूर्णांक_stop;
		INIT_DELAYED_WORK(&ir->work, पंचांग6000_ir_पूर्णांक_work);
	पूर्ण अन्यथा अणु
		rc->खोलो  = पंचांग6000_ir_start;
		rc->बंद = पंचांग6000_ir_stop;
		ir->polling = 50;
		INIT_DELAYED_WORK(&ir->work, पंचांग6000_ir_handle_key);
	पूर्ण

	snम_लिखो(ir->name, माप(ir->name), "tm5600/60x0 IR (%s)",
						dev->name);

	usb_make_path(dev->udev, ir->phys, माप(ir->phys));
	strlcat(ir->phys, "/input0", माप(ir->phys));

	rc_proto = RC_PROTO_BIT_UNKNOWN;
	पंचांग6000_ir_change_protocol(rc, &rc_proto);

	rc->device_name = ir->name;
	rc->input_phys = ir->phys;
	rc->input_id.bustype = BUS_USB;
	rc->input_id.version = 1;
	rc->input_id.venकरोr = le16_to_cpu(dev->udev->descriptor.idVenकरोr);
	rc->input_id.product = le16_to_cpu(dev->udev->descriptor.idProduct);
	rc->map_name = dev->ir_codes;
	rc->driver_name = "tm6000";
	rc->dev.parent = &dev->udev->dev;

	/* ir रेजिस्टर */
	err = rc_रेजिस्टर_device(rc);
	अगर (err)
		जाओ out;

	वापस 0;

out:
	dev->ir = शून्य;
	rc_मुक्त_device(rc);
	kमुक्त(ir);
	वापस err;
पूर्ण

पूर्णांक पंचांग6000_ir_fini(काष्ठा पंचांग6000_core *dev)
अणु
	काष्ठा पंचांग6000_IR *ir = dev->ir;

	/* skip detach on non attached board */

	अगर (!ir)
		वापस 0;

	dprपूर्णांकk(2, "%s\n",__func__);

	अगर (!ir->polling)
		__पंचांग6000_ir_पूर्णांक_stop(ir->rc);

	पंचांग6000_ir_stop(ir->rc);

	/* Turn off the led */
	पंचांग6000_flash_led(dev, 0);
	ir->pwled = 0;

	rc_unरेजिस्टर_device(ir->rc);

	kमुक्त(ir);
	dev->ir = शून्य;

	वापस 0;
पूर्ण
