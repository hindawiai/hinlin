<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  NEC VR4100 series SIU platक्रमm device.
 *
 *  Copyright (C) 2007-2008  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/vr41xx/siu.h>

अटल अचिन्हित पूर्णांक siu_type1_ports[SIU_PORTS_MAX] __initdata = अणु
	PORT_VR41XX_SIU,
	PORT_UNKNOWN,
पूर्ण;

अटल काष्ठा resource siu_type1_resource[] __initdata = अणु
	अणु
		.start	= 0x0c000000,
		.end	= 0x0c00000a,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= SIU_IRQ,
		.end	= SIU_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक siu_type2_ports[SIU_PORTS_MAX] __initdata = अणु
	PORT_VR41XX_SIU,
	PORT_VR41XX_DSIU,
पूर्ण;

अटल काष्ठा resource siu_type2_resource[] __initdata = अणु
	अणु
		.start	= 0x0f000800,
		.end	= 0x0f00080a,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= 0x0f000820,
		.end	= 0x0f000829,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= SIU_IRQ,
		.end	= SIU_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.start	= DSIU_IRQ,
		.end	= DSIU_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vr41xx_siu_add(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक num;
	पूर्णांक retval;

	pdev = platक्रमm_device_alloc("SIU", -1);
	अगर (!pdev)
		वापस -ENOMEM;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
	हाल CPU_VR4121:
		pdev->dev.platक्रमm_data = siu_type1_ports;
		res = siu_type1_resource;
		num = ARRAY_SIZE(siu_type1_resource);
		अवरोध;
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4133:
		pdev->dev.platक्रमm_data = siu_type2_ports;
		res = siu_type2_resource;
		num = ARRAY_SIZE(siu_type2_resource);
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
device_initcall(vr41xx_siu_add);

व्योम __init vr41xx_siu_setup(व्योम)
अणु
	काष्ठा uart_port port;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक *type;
	पूर्णांक i;

	चयन (current_cpu_type()) अणु
	हाल CPU_VR4111:
	हाल CPU_VR4121:
		type = siu_type1_ports;
		res = siu_type1_resource;
		अवरोध;
	हाल CPU_VR4122:
	हाल CPU_VR4131:
	हाल CPU_VR4133:
		type = siu_type2_ports;
		res = siu_type2_resource;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	क्रम (i = 0; i < SIU_PORTS_MAX; i++) अणु
		port.line = i;
		port.type = type[i];
		अगर (port.type == PORT_UNKNOWN)
			अवरोध;
		port.mapbase = res[i].start;
		port.membase = (अचिन्हित अक्षर __iomem *)KSEG1ADDR(res[i].start);
		vr41xx_siu_early_setup(&port);
	पूर्ण
पूर्ण
