<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Loopback driver क्रम rc-core,
 *
 * Copyright (c) 2010 David Hथअrdeman <david@hardeman.nu>
 *
 * This driver receives TX data and passes it back as RX data,
 * which is useful क्रम (scripted) debugging of rc-core without
 * having to use actual hardware.
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <media/rc-core.h>

#घोषणा DRIVER_NAME	"rc-loopback"
#घोषणा dprपूर्णांकk(x...)	अगर (debug) prपूर्णांकk(KERN_INFO DRIVER_NAME ": " x)
#घोषणा RXMASK_REGULAR	0x1
#घोषणा RXMASK_LEARNING	0x2

अटल bool debug;

काष्ठा loopback_dev अणु
	काष्ठा rc_dev *dev;
	u32 txmask;
	u32 txcarrier;
	u32 txduty;
	bool idle;
	bool learning;
	bool carrierreport;
	u32 rxcarriermin;
	u32 rxcarriermax;
पूर्ण;

अटल काष्ठा loopback_dev loopdev;

अटल पूर्णांक loop_set_tx_mask(काष्ठा rc_dev *dev, u32 mask)
अणु
	काष्ठा loopback_dev *lodev = dev->priv;

	अगर ((mask & (RXMASK_REGULAR | RXMASK_LEARNING)) != mask) अणु
		dprपूर्णांकk("invalid tx mask: %u\n", mask);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk("setting tx mask: %u\n", mask);
	lodev->txmask = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक loop_set_tx_carrier(काष्ठा rc_dev *dev, u32 carrier)
अणु
	काष्ठा loopback_dev *lodev = dev->priv;

	dprपूर्णांकk("setting tx carrier: %u\n", carrier);
	lodev->txcarrier = carrier;
	वापस 0;
पूर्ण

अटल पूर्णांक loop_set_tx_duty_cycle(काष्ठा rc_dev *dev, u32 duty_cycle)
अणु
	काष्ठा loopback_dev *lodev = dev->priv;

	अगर (duty_cycle < 1 || duty_cycle > 99) अणु
		dprपूर्णांकk("invalid duty cycle: %u\n", duty_cycle);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk("setting duty cycle: %u\n", duty_cycle);
	lodev->txduty = duty_cycle;
	वापस 0;
पूर्ण

अटल पूर्णांक loop_set_rx_carrier_range(काष्ठा rc_dev *dev, u32 min, u32 max)
अणु
	काष्ठा loopback_dev *lodev = dev->priv;

	अगर (min < 1 || min > max) अणु
		dprपूर्णांकk("invalid rx carrier range %u to %u\n", min, max);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk("setting rx carrier range %u to %u\n", min, max);
	lodev->rxcarriermin = min;
	lodev->rxcarriermax = max;
	वापस 0;
पूर्ण

अटल पूर्णांक loop_tx_ir(काष्ठा rc_dev *dev, अचिन्हित *txbuf, अचिन्हित count)
अणु
	काष्ठा loopback_dev *lodev = dev->priv;
	u32 rxmask;
	अचिन्हित i;
	काष्ठा ir_raw_event rawir = अणुपूर्ण;

	अगर (lodev->txcarrier < lodev->rxcarriermin ||
	    lodev->txcarrier > lodev->rxcarriermax) अणु
		dprपूर्णांकk("ignoring tx, carrier out of range\n");
		जाओ out;
	पूर्ण

	अगर (lodev->learning)
		rxmask = RXMASK_LEARNING;
	अन्यथा
		rxmask = RXMASK_REGULAR;

	अगर (!(rxmask & lodev->txmask)) अणु
		dprपूर्णांकk("ignoring tx, rx mask mismatch\n");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		rawir.pulse = i % 2 ? false : true;
		rawir.duration = txbuf[i];
		अगर (rawir.duration)
			ir_raw_event_store_with_filter(dev, &rawir);
	पूर्ण

	/* Fake a silence दीर्घ enough to cause us to go idle */
	rawir.pulse = false;
	rawir.duration = dev->समयout;
	ir_raw_event_store_with_filter(dev, &rawir);

	ir_raw_event_handle(dev);

out:
	वापस count;
पूर्ण

अटल व्योम loop_set_idle(काष्ठा rc_dev *dev, bool enable)
अणु
	काष्ठा loopback_dev *lodev = dev->priv;

	अगर (lodev->idle != enable) अणु
		dprपूर्णांकk("%sing idle mode\n", enable ? "enter" : "exit");
		lodev->idle = enable;
	पूर्ण
पूर्ण

अटल पूर्णांक loop_set_learning_mode(काष्ठा rc_dev *dev, पूर्णांक enable)
अणु
	काष्ठा loopback_dev *lodev = dev->priv;

	अगर (lodev->learning != enable) अणु
		dprपूर्णांकk("%sing learning mode\n", enable ? "enter" : "exit");
		lodev->learning = !!enable;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक loop_set_carrier_report(काष्ठा rc_dev *dev, पूर्णांक enable)
अणु
	काष्ठा loopback_dev *lodev = dev->priv;

	अगर (lodev->carrierreport != enable) अणु
		dprपूर्णांकk("%sabling carrier reports\n", enable ? "en" : "dis");
		lodev->carrierreport = !!enable;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक loop_set_wakeup_filter(काष्ठा rc_dev *dev,
				  काष्ठा rc_scancode_filter *sc)
अणु
	अटल स्थिर अचिन्हित पूर्णांक max = 512;
	काष्ठा ir_raw_event *raw;
	पूर्णांक ret;
	पूर्णांक i;

	/* fine to disable filter */
	अगर (!sc->mask)
		वापस 0;

	/* encode the specअगरied filter and loop it back */
	raw = kदो_स्मृति_array(max, माप(*raw), GFP_KERNEL);
	अगर (!raw)
		वापस -ENOMEM;

	ret = ir_raw_encode_scancode(dev->wakeup_protocol, sc->data, raw, max);
	/* still loop back the partial raw IR even अगर it's incomplete */
	अगर (ret == -ENOBUFS)
		ret = max;
	अगर (ret >= 0) अणु
		/* करो the loopback */
		क्रम (i = 0; i < ret; ++i)
			ir_raw_event_store(dev, &raw[i]);
		ir_raw_event_handle(dev);

		ret = 0;
	पूर्ण

	kमुक्त(raw);

	वापस ret;
पूर्ण

अटल पूर्णांक __init loop_init(व्योम)
अणु
	काष्ठा rc_dev *rc;
	पूर्णांक ret;

	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rc) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": rc_dev allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	rc->device_name		= "rc-core loopback device";
	rc->input_phys		= "rc-core/virtual";
	rc->input_id.bustype	= BUS_VIRTUAL;
	rc->input_id.version	= 1;
	rc->driver_name		= DRIVER_NAME;
	rc->map_name		= RC_MAP_EMPTY;
	rc->priv		= &loopdev;
	rc->allowed_protocols	= RC_PROTO_BIT_ALL_IR_DECODER;
	rc->allowed_wakeup_protocols = RC_PROTO_BIT_ALL_IR_ENCODER;
	rc->encode_wakeup	= true;
	rc->समयout		= MS_TO_US(100); /* 100 ms */
	rc->min_समयout		= 1;
	rc->max_समयout		= अच_पूर्णांक_उच्च;
	rc->rx_resolution	= 1;
	rc->tx_resolution	= 1;
	rc->s_tx_mask		= loop_set_tx_mask;
	rc->s_tx_carrier	= loop_set_tx_carrier;
	rc->s_tx_duty_cycle	= loop_set_tx_duty_cycle;
	rc->s_rx_carrier_range	= loop_set_rx_carrier_range;
	rc->tx_ir		= loop_tx_ir;
	rc->s_idle		= loop_set_idle;
	rc->s_learning_mode	= loop_set_learning_mode;
	rc->s_carrier_report	= loop_set_carrier_report;
	rc->s_wakeup_filter	= loop_set_wakeup_filter;

	loopdev.txmask		= RXMASK_REGULAR;
	loopdev.txcarrier	= 36000;
	loopdev.txduty		= 50;
	loopdev.rxcarriermin	= 1;
	loopdev.rxcarriermax	= ~0;
	loopdev.idle		= true;
	loopdev.learning	= false;
	loopdev.carrierreport	= false;

	ret = rc_रेजिस्टर_device(rc);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR DRIVER_NAME ": rc_dev registration failed\n");
		rc_मुक्त_device(rc);
		वापस ret;
	पूर्ण

	loopdev.dev = rc;
	वापस 0;
पूर्ण

अटल व्योम __निकास loop_निकास(व्योम)
अणु
	rc_unरेजिस्टर_device(loopdev.dev);
पूर्ण

module_init(loop_init);
module_निकास(loop_निकास);

module_param(debug, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Enable debug messages");

MODULE_DESCRIPTION("Loopback device for rc-core debugging");
MODULE_AUTHOR("David Hथअrdeman <david@hardeman.nu>");
MODULE_LICENSE("GPL");
