<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2004-2005 Simtec Electronics
//   Ben Dooks <ben@simtec.co.uk>
//
// http://www.simtec.co.uk/products/EB2410ITX/
//
// Simtec BAST and Thorcom VR1000 USB port support functions

#घोषणा DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "gpio-samsung.h"
#समावेश <mach/irqs.h>
#समावेश <यंत्र/irq.h>

#समावेश <linux/platक्रमm_data/usb-ohci-s3c2410.h>
#समावेश "devs.h"

#समावेश "bast.h"
#समावेश "simtec.h"

/* control घातer and monitor over-current events on various Simtec
 * deचिन्हित boards.
*/

अटल अचिन्हित पूर्णांक घातer_state[2];

अटल व्योम
usb_simtec_घातercontrol(पूर्णांक port, पूर्णांक to)
अणु
	pr_debug("usb_simtec_powercontrol(%d,%d)\n", port, to);

	घातer_state[port] = to;

	अगर (घातer_state[0] && घातer_state[1])
		gpio_set_value(S3C2410_GPB(4), 0);
	अन्यथा
		gpio_set_value(S3C2410_GPB(4), 1);
पूर्ण

अटल irqवापस_t
usb_simtec_ocirq(पूर्णांक irq, व्योम *pw)
अणु
	काष्ठा s3c2410_hcd_info *info = pw;

	अगर (gpio_get_value(S3C2410_GPG(10)) == 0) अणु
		pr_debug("usb_simtec: over-current irq (oc detected)\n");
		s3c2410_usb_report_oc(info, 3);
	पूर्ण अन्यथा अणु
		pr_debug("usb_simtec: over-current irq (oc cleared)\n");
		s3c2410_usb_report_oc(info, 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम usb_simtec_enableoc(काष्ठा s3c2410_hcd_info *info, पूर्णांक on)
अणु
	पूर्णांक ret;

	अगर (on) अणु
		ret = request_irq(BAST_IRQ_USBOC, usb_simtec_ocirq,
				  IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				  "USB Over-current", info);
		अगर (ret != 0) अणु
			prपूर्णांकk(KERN_ERR "failed to request usb oc irq\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		मुक्त_irq(BAST_IRQ_USBOC, info);
	पूर्ण
पूर्ण

अटल काष्ठा s3c2410_hcd_info usb_simtec_info __initdata = अणु
	.port[0]	= अणु
		.flags	= S3C_HCDFLG_USED
	पूर्ण,
	.port[1]	= अणु
		.flags	= S3C_HCDFLG_USED
	पूर्ण,

	.घातer_control	= usb_simtec_घातercontrol,
	.enable_oc	= usb_simtec_enableoc,
पूर्ण;


पूर्णांक __init usb_simtec_init(व्योम)
अणु
	पूर्णांक ret;

	prपूर्णांकk("USB Power Control, Copyright 2004 Simtec Electronics\n");

	ret = gpio_request(S3C2410_GPB(4), "USB power control");
	अगर (ret < 0) अणु
		pr_err("%s: failed to get GPB4\n", __func__);
		वापस ret;
	पूर्ण

	ret = gpio_request(S3C2410_GPG(10), "USB overcurrent");
	अगर (ret < 0) अणु
		pr_err("%s: failed to get GPG10\n", __func__);
		gpio_मुक्त(S3C2410_GPB(4));
		वापस ret;
	पूर्ण

	/* turn घातer on */
	gpio_direction_output(S3C2410_GPB(4), 1);
	gpio_direction_input(S3C2410_GPG(10));

	s3c_ohci_set_platdata(&usb_simtec_info);
	वापस 0;
पूर्ण
