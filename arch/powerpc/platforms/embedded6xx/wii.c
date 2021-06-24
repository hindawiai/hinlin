<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/platक्रमms/embedded6xx/wii.c
 *
 * Nपूर्णांकenकरो Wii board-specअगरic support
 * Copyright (C) 2008-2009 The GameCube Linux Team
 * Copyright (C) 2008,2009 Albert Herranz
 */
#घोषणा DRV_MODULE_NAME "wii"
#घोषणा pr_fmt(fmt) DRV_MODULE_NAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/memblock.h>
#समावेश <mm/mmu_decl.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/udbg.h>

#समावेश "flipper-pic.h"
#समावेश "hlwd-pic.h"
#समावेश "usbgecko_udbg.h"

/* control block */
#घोषणा HW_CTRL_COMPATIBLE	"nintendo,hollywood-control"

#घोषणा HW_CTRL_RESETS		0x94
#घोषणा HW_CTRL_RESETS_SYS	(1<<0)

/* gpio */
#घोषणा HW_GPIO_COMPATIBLE	"nintendo,hollywood-gpio"

#घोषणा HW_GPIO_BASE(idx)	(idx * 0x20)
#घोषणा HW_GPIO_OUT(idx)	(HW_GPIO_BASE(idx) + 0)
#घोषणा HW_GPIO_सूची(idx)	(HW_GPIO_BASE(idx) + 4)
#घोषणा HW_GPIO_OWNER		(HW_GPIO_BASE(1) + 0x1c)

#घोषणा HW_GPIO_SHUTDOWN	(1<<1)
#घोषणा HW_GPIO_SLOT_LED	(1<<5)
#घोषणा HW_GPIO_SENSOR_BAR	(1<<8)


अटल व्योम __iomem *hw_ctrl;
अटल व्योम __iomem *hw_gpio;

अटल पूर्णांक __init page_aligned(अचिन्हित दीर्घ x)
अणु
	वापस !(x & (PAGE_SIZE-1));
पूर्ण

व्योम __init wii_memory_fixups(व्योम)
अणु
	काष्ठा memblock_region *p = memblock.memory.regions;

	BUG_ON(memblock.memory.cnt != 2);
	BUG_ON(!page_aligned(p[0].base) || !page_aligned(p[1].base));
पूर्ण

अटल व्योम __noवापस wii_spin(व्योम)
अणु
	local_irq_disable();
	क्रम (;;)
		cpu_relax();
पूर्ण

अटल व्योम __iomem *wii_ioremap_hw_regs(अक्षर *name, अक्षर *compatible)
अणु
	व्योम __iomem *hw_regs = शून्य;
	काष्ठा device_node *np;
	काष्ठा resource res;
	पूर्णांक error = -ENODEV;

	np = of_find_compatible_node(शून्य, शून्य, compatible);
	अगर (!np) अणु
		pr_err("no compatible node found for %s\n", compatible);
		जाओ out;
	पूर्ण
	error = of_address_to_resource(np, 0, &res);
	अगर (error) अणु
		pr_err("no valid reg found for %pOFn\n", np);
		जाओ out_put;
	पूर्ण

	hw_regs = ioremap(res.start, resource_size(&res));
	अगर (hw_regs) अणु
		pr_info("%s at 0x%08x mapped to 0x%p\n", name,
			res.start, hw_regs);
	पूर्ण

out_put:
	of_node_put(np);
out:
	वापस hw_regs;
पूर्ण

अटल व्योम __init wii_setup_arch(व्योम)
अणु
	hw_ctrl = wii_ioremap_hw_regs("hw_ctrl", HW_CTRL_COMPATIBLE);
	hw_gpio = wii_ioremap_hw_regs("hw_gpio", HW_GPIO_COMPATIBLE);
	अगर (hw_gpio) अणु
		/* turn off the front blue led and IR light */
		clrbits32(hw_gpio + HW_GPIO_OUT(0),
			  HW_GPIO_SLOT_LED | HW_GPIO_SENSOR_BAR);
	पूर्ण
पूर्ण

अटल व्योम __noवापस wii_restart(अक्षर *cmd)
अणु
	local_irq_disable();

	अगर (hw_ctrl) अणु
		/* clear the प्रणाली reset pin to cause a reset */
		clrbits32(hw_ctrl + HW_CTRL_RESETS, HW_CTRL_RESETS_SYS);
	पूर्ण
	wii_spin();
पूर्ण

अटल व्योम wii_घातer_off(व्योम)
अणु
	local_irq_disable();

	अगर (hw_gpio) अणु
		/*
		 * set the owner of the shutकरोwn pin to ARM, because it is
		 * accessed through the रेजिस्टरs क्रम the ARM, below
		 */
		clrbits32(hw_gpio + HW_GPIO_OWNER, HW_GPIO_SHUTDOWN);

		/* make sure that the घातeroff GPIO is configured as output */
		setbits32(hw_gpio + HW_GPIO_सूची(1), HW_GPIO_SHUTDOWN);

		/* drive the घातeroff GPIO high */
		setbits32(hw_gpio + HW_GPIO_OUT(1), HW_GPIO_SHUTDOWN);
	पूर्ण
	wii_spin();
पूर्ण

अटल व्योम __noवापस wii_halt(व्योम)
अणु
	अगर (ppc_md.restart)
		ppc_md.restart(शून्य);
	wii_spin();
पूर्ण

अटल व्योम __init wii_pic_probe(व्योम)
अणु
	flipper_pic_probe();
	hlwd_pic_probe();
पूर्ण

अटल पूर्णांक __init wii_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("nintendo,wii"))
		वापस 0;

	pm_घातer_off = wii_घातer_off;

	ug_udbg_init();

	वापस 1;
पूर्ण

अटल व्योम wii_shutकरोwn(व्योम)
अणु
	hlwd_quiesce();
	flipper_quiesce();
पूर्ण

अटल स्थिर काष्ठा of_device_id wii_of_bus[] = अणु
	अणु .compatible = "nintendo,hollywood", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __init wii_device_probe(व्योम)
अणु
	अगर (!machine_is(wii))
		वापस 0;

	of_platक्रमm_populate(शून्य, wii_of_bus, शून्य, शून्य);
	वापस 0;
पूर्ण
device_initcall(wii_device_probe);

define_machine(wii) अणु
	.name			= "wii",
	.probe			= wii_probe,
	.setup_arch		= wii_setup_arch,
	.restart		= wii_restart,
	.halt			= wii_halt,
	.init_IRQ		= wii_pic_probe,
	.get_irq		= flipper_pic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
	.machine_shutकरोwn	= wii_shutकरोwn,
पूर्ण;
