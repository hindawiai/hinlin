<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  NEC VR4100 series RTC platक्रमm device.
 *
 *  Copyright (C) 2007	Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/vr41xx/irq.h>

अटल काष्ठा resource rtc_type1_resource[] __initdata = अणु
	अणु
		.start	= 0x0b0000c0,
		.end	= 0x0b0000df,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x0b0001c0,
		.end	= 0x0b0001df,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= ELAPSEDTIME_IRQ,
		.end	= ELAPSEDTIME_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= RTCLONG1_IRQ,
		.end	= RTCLONG1_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource rtc_type2_resource[] __initdata = अणु
	अणु
		.start	= 0x0f000100,
		.end	= 0x0f00011f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x0f000120,
		.end	= 0x0f00013f,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= ELAPSEDTIME_IRQ,
		.end	= ELAPSEDTIME_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= RTCLONG1_IRQ,
		.end	= RTCLONG1_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vr41xx_rtc_add(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक num;
	पूर्णांक retval;

	pdev = platक्रमm_device_alloc("RTC", -1);
	अगर (!pdev)
		वापस -ENOMEM;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
	हाल CPU_VR4121:
		res = rtc_type1_resource;
		num = ARRAY_SIZE(rtc_type1_resource);
		अवरोध;
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4133:
		res = rtc_type2_resource;
		num = ARRAY_SIZE(rtc_type2_resource);
		अवरोध;
	शेष:
		retval = -ENODEV;
		जाओ err_मुक्त_device;
	पूर्ण

	retval = platक्रमm_device_add_resources(pdev, res, num);
	अगर (retval)
		जाओ err_मुक्त_device;

	retval = platक्रमm_device_add(pdev);
	अगर (retval)
		जाओ err_मुक्त_device;

	वापस 0;

err_मुक्त_device:
	platक्रमm_device_put(pdev);

	वापस retval;
पूर्ण
device_initcall(vr41xx_rtc_add);
