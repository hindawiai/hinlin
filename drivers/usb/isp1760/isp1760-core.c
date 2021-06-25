<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the NXP ISP1760 chip
 *
 * Copyright 2014 Laurent Pinअक्षरt
 * Copyright 2007 Sebastian Siewior
 *
 * Contacts:
 *	Sebastian Siewior <bigeasy@linutronix.de>
 *	Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश "isp1760-core.h"
#समावेश "isp1760-hcd.h"
#समावेश "isp1760-regs.h"
#समावेश "isp1760-udc.h"

अटल व्योम isp1760_init_core(काष्ठा isp1760_device *isp)
अणु
	u32 otgctrl;
	u32 hwmode;

	/* Low-level chip reset */
	अगर (isp->rst_gpio) अणु
		gpiod_set_value_cansleep(isp->rst_gpio, 1);
		msleep(50);
		gpiod_set_value_cansleep(isp->rst_gpio, 0);
	पूर्ण

	/*
	 * Reset the host controller, including the CPU पूर्णांकerface
	 * configuration.
	 */
	isp1760_ग_लिखो32(isp->regs, HC_RESET_REG, SW_RESET_RESET_ALL);
	msleep(100);

	/* Setup HW Mode Control: This assumes a level active-low पूर्णांकerrupt */
	hwmode = HW_DATA_BUS_32BIT;

	अगर (isp->devflags & ISP1760_FLAG_BUS_WIDTH_16)
		hwmode &= ~HW_DATA_BUS_32BIT;
	अगर (isp->devflags & ISP1760_FLAG_ANALOG_OC)
		hwmode |= HW_ANA_DIGI_OC;
	अगर (isp->devflags & ISP1760_FLAG_DACK_POL_HIGH)
		hwmode |= HW_DACK_POL_HIGH;
	अगर (isp->devflags & ISP1760_FLAG_DREQ_POL_HIGH)
		hwmode |= HW_DREQ_POL_HIGH;
	अगर (isp->devflags & ISP1760_FLAG_INTR_POL_HIGH)
		hwmode |= HW_INTR_HIGH_ACT;
	अगर (isp->devflags & ISP1760_FLAG_INTR_EDGE_TRIG)
		hwmode |= HW_INTR_EDGE_TRIG;

	/*
	 * The ISP1761 has a dedicated DC IRQ line but supports sharing the HC
	 * IRQ line क्रम both the host and device controllers. Hardcode IRQ
	 * sharing क्रम now and disable the DC पूर्णांकerrupts globally to aव्योम
	 * spurious पूर्णांकerrupts during HCD registration.
	 */
	अगर (isp->devflags & ISP1760_FLAG_ISP1761) अणु
		isp1760_ग_लिखो32(isp->regs, DC_MODE, 0);
		hwmode |= HW_COMN_IRQ;
	पूर्ण

	/*
	 * We have to set this first in हाल we're in 16-bit mode.
	 * Write it twice to ensure correct upper bits अगर चयनing
	 * to 16-bit mode.
	 */
	isp1760_ग_लिखो32(isp->regs, HC_HW_MODE_CTRL, hwmode);
	isp1760_ग_लिखो32(isp->regs, HC_HW_MODE_CTRL, hwmode);

	/*
	 * PORT 1 Control रेजिस्टर of the ISP1760 is the OTG control रेजिस्टर
	 * on ISP1761.
	 *
	 * TODO: Really support OTG. For now we configure port 1 in device mode
	 * when OTG is requested.
	 */
	अगर ((isp->devflags & ISP1760_FLAG_ISP1761) &&
	    (isp->devflags & ISP1760_FLAG_OTG_EN))
		otgctrl = ((HW_DM_PULLDOWN | HW_DP_PULLDOWN) << 16)
			| HW_OTG_DISABLE;
	अन्यथा
		otgctrl = (HW_SW_SEL_HC_DC << 16)
			| (HW_VBUS_DRV | HW_SEL_CP_EXT);

	isp1760_ग_लिखो32(isp->regs, HC_PORT1_CTRL, otgctrl);

	dev_info(isp->dev, "bus width: %u, oc: %s\n",
		 isp->devflags & ISP1760_FLAG_BUS_WIDTH_16 ? 16 : 32,
		 isp->devflags & ISP1760_FLAG_ANALOG_OC ? "analog" : "digital");
पूर्ण

व्योम isp1760_set_pullup(काष्ठा isp1760_device *isp, bool enable)
अणु
	isp1760_ग_लिखो32(isp->regs, HW_OTG_CTRL_SET,
			enable ? HW_DP_PULLUP : HW_DP_PULLUP << 16);
पूर्ण

पूर्णांक isp1760_रेजिस्टर(काष्ठा resource *mem, पूर्णांक irq, अचिन्हित दीर्घ irqflags,
		     काष्ठा device *dev, अचिन्हित पूर्णांक devflags)
अणु
	काष्ठा isp1760_device *isp;
	bool udc_disabled = !(devflags & ISP1760_FLAG_ISP1761);
	पूर्णांक ret;

	/*
	 * If neither the HCD not the UDC is enabled वापस an error, as no
	 * device would be रेजिस्टरed.
	 */
	अगर ((!IS_ENABLED(CONFIG_USB_ISP1760_HCD) || usb_disabled()) &&
	    (!IS_ENABLED(CONFIG_USB_ISP1761_UDC) || udc_disabled))
		वापस -ENODEV;

	isp = devm_kzalloc(dev, माप(*isp), GFP_KERNEL);
	अगर (!isp)
		वापस -ENOMEM;

	isp->dev = dev;
	isp->devflags = devflags;

	isp->rst_gpio = devm_gpiod_get_optional(dev, शून्य, GPIOD_OUT_HIGH);
	अगर (IS_ERR(isp->rst_gpio))
		वापस PTR_ERR(isp->rst_gpio);

	isp->regs = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(isp->regs))
		वापस PTR_ERR(isp->regs);

	isp1760_init_core(isp);

	अगर (IS_ENABLED(CONFIG_USB_ISP1760_HCD) && !usb_disabled()) अणु
		ret = isp1760_hcd_रेजिस्टर(&isp->hcd, isp->regs, mem, irq,
					   irqflags | IRQF_SHARED, dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_USB_ISP1761_UDC) && !udc_disabled) अणु
		ret = isp1760_udc_रेजिस्टर(isp, irq, irqflags);
		अगर (ret < 0) अणु
			isp1760_hcd_unरेजिस्टर(&isp->hcd);
			वापस ret;
		पूर्ण
	पूर्ण

	dev_set_drvdata(dev, isp);

	वापस 0;
पूर्ण

व्योम isp1760_unरेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा isp1760_device *isp = dev_get_drvdata(dev);

	isp1760_udc_unरेजिस्टर(isp);
	isp1760_hcd_unरेजिस्टर(&isp->hcd);
पूर्ण

MODULE_DESCRIPTION("Driver for the ISP1760 USB-controller from NXP");
MODULE_AUTHOR("Sebastian Siewior <bigeasy@linuxtronix.de>");
MODULE_LICENSE("GPL v2");
