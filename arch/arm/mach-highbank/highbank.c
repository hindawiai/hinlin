<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2010-2011 Calxeda, Inc.
 */
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/pl320-ipc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reboot.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/psci.h>

#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "core.h"
#समावेश "sysregs.h"

व्योम __iomem *sregs_base;
व्योम __iomem *scu_base_addr;

अटल व्योम __init highbank_scu_map_io(व्योम)
अणु
	अचिन्हित दीर्घ base;

	/* Get SCU base */
	यंत्र("mrc p15, 4, %0, c15, c0, 0" : "=r" (base));

	scu_base_addr = ioremap(base, SZ_4K);
पूर्ण


अटल व्योम highbank_l2c310_ग_लिखो_sec(अचिन्हित दीर्घ val, अचिन्हित reg)
अणु
	अगर (reg == L2X0_CTRL)
		highbank_smc1(0x102, val);
	अन्यथा
		WARN_ONCE(1, "Highbank L2C310: ignoring write to reg 0x%x\n",
			  reg);
पूर्ण

अटल व्योम __init highbank_init_irq(व्योम)
अणु
	irqchip_init();

	अगर (of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9"))
		highbank_scu_map_io();
पूर्ण

अटल व्योम highbank_घातer_off(व्योम)
अणु
	highbank_set_pwr_shutकरोwn();

	जबतक (1)
		cpu_करो_idle();
पूर्ण

अटल पूर्णांक highbank_platक्रमm_notअगरier(काष्ठा notअगरier_block *nb,
				  अचिन्हित दीर्घ event, व्योम *__dev)
अणु
	काष्ठा resource *res;
	पूर्णांक reg = -1;
	u32 val;
	काष्ठा device *dev = __dev;

	अगर (event != BUS_NOTIFY_ADD_DEVICE)
		वापस NOTIFY_DONE;

	अगर (of_device_is_compatible(dev->of_node, "calxeda,hb-ahci"))
		reg = 0xc;
	अन्यथा अगर (of_device_is_compatible(dev->of_node, "calxeda,hb-sdhci"))
		reg = 0x18;
	अन्यथा अगर (of_device_is_compatible(dev->of_node, "arm,pl330"))
		reg = 0x20;
	अन्यथा अगर (of_device_is_compatible(dev->of_node, "calxeda,hb-xgmac")) अणु
		res = platक्रमm_get_resource(to_platक्रमm_device(dev),
					    IORESOURCE_MEM, 0);
		अगर (res) अणु
			अगर (res->start == 0xfff50000)
				reg = 0;
			अन्यथा अगर (res->start == 0xfff51000)
				reg = 4;
		पूर्ण
	पूर्ण

	अगर (reg < 0)
		वापस NOTIFY_DONE;

	अगर (of_property_पढ़ो_bool(dev->of_node, "dma-coherent")) अणु
		val = पढ़ोl(sregs_base + reg);
		ग_लिखोl(val | 0xff01, sregs_base + reg);
		set_dma_ops(dev, &arm_coherent_dma_ops);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block highbank_amba_nb = अणु
	.notअगरier_call = highbank_platक्रमm_notअगरier,
पूर्ण;

अटल काष्ठा notअगरier_block highbank_platक्रमm_nb = अणु
	.notअगरier_call = highbank_platक्रमm_notअगरier,
पूर्ण;

अटल काष्ठा platक्रमm_device highbank_cpuidle_device = अणु
	.name = "cpuidle-calxeda",
पूर्ण;

अटल पूर्णांक hb_keys_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *data)
अणु
	u32 key = *(u32 *)data;

	अगर (event != 0x1000)
		वापस 0;

	अगर (key == KEY_POWER)
		orderly_घातeroff(false);
	अन्यथा अगर (key == 0xffff)
		ctrl_alt_del();

	वापस 0;
पूर्ण
अटल काष्ठा notअगरier_block hb_keys_nb = अणु
	.notअगरier_call = hb_keys_notअगरier,
पूर्ण;

अटल व्योम __init highbank_init(व्योम)
अणु
	काष्ठा device_node *np;

	/* Map प्रणाली रेजिस्टरs */
	np = of_find_compatible_node(शून्य, शून्य, "calxeda,hb-sregs");
	sregs_base = of_iomap(np, 0);
	WARN_ON(!sregs_base);

	pm_घातer_off = highbank_घातer_off;
	highbank_pm_init();

	bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type, &highbank_platक्रमm_nb);
	bus_रेजिस्टर_notअगरier(&amba_bustype, &highbank_amba_nb);

	pl320_ipc_रेजिस्टर_notअगरier(&hb_keys_nb);

	अगर (psci_ops.cpu_suspend)
		platक्रमm_device_रेजिस्टर(&highbank_cpuidle_device);
पूर्ण

अटल स्थिर अक्षर *स्थिर highbank_match[] __initस्थिर = अणु
	"calxeda,highbank",
	"calxeda,ecx-2000",
	शून्य,
पूर्ण;

DT_MACHINE_START(HIGHBANK, "Highbank")
#अगर defined(CONFIG_ZONE_DMA) && defined(CONFIG_ARM_LPAE)
	.dma_zone_size	= (4ULL * SZ_1G),
#पूर्ण_अगर
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.l2c_ग_लिखो_sec	= highbank_l2c310_ग_लिखो_sec,
	.init_irq	= highbank_init_irq,
	.init_machine	= highbank_init,
	.dt_compat	= highbank_match,
	.restart	= highbank_restart,
MACHINE_END
