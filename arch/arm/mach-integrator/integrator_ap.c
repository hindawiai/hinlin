<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/arch/arm/mach-पूर्णांकegrator/पूर्णांकegrator_ap.c
 *
 *  Copyright (C) 2000-2003 Deep Blue Solutions Ltd
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/termios.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "hardware.h"
#समावेश "cm.h"
#समावेश "common.h"

/* Regmap to the AP प्रणाली controller */
अटल काष्ठा regmap *ap_syscon_map;

/*
 * All IO addresses are mapped onto VA 0xFFFx.xxxx, where x.xxxx
 * is the (PA >> 12).
 *
 * Setup a VA क्रम the Integrator पूर्णांकerrupt controller (क्रम header #0,
 * just क्रम now).
 */
#घोषणा VA_IC_BASE	__io_address(INTEGRATOR_IC_BASE)

/*
 * Logical      Physical
 * f1400000	14000000	Interrupt controller
 * f1600000	16000000	UART 0
 */

अटल काष्ठा map_desc ap_io_desc[] __initdata __maybe_unused = अणु
	अणु
		.भव	= IO_ADDRESS(INTEGRATOR_IC_BASE),
		.pfn		= __phys_to_pfn(INTEGRATOR_IC_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE
	पूर्ण, अणु
		.भव	= IO_ADDRESS(INTEGRATOR_UART0_BASE),
		.pfn		= __phys_to_pfn(INTEGRATOR_UART0_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init ap_map_io(व्योम)
अणु
	iotable_init(ap_io_desc, ARRAY_SIZE(ap_io_desc));
पूर्ण

#अगर_घोषित CONFIG_PM
अटल अचिन्हित दीर्घ ic_irq_enable;

अटल पूर्णांक irq_suspend(व्योम)
अणु
	ic_irq_enable = पढ़ोl(VA_IC_BASE + IRQ_ENABLE);
	वापस 0;
पूर्ण

अटल व्योम irq_resume(व्योम)
अणु
	/* disable all irq sources */
	cm_clear_irqs();
	ग_लिखोl(-1, VA_IC_BASE + IRQ_ENABLE_CLEAR);
	ग_लिखोl(-1, VA_IC_BASE + FIQ_ENABLE_CLEAR);

	ग_लिखोl(ic_irq_enable, VA_IC_BASE + IRQ_ENABLE_SET);
पूर्ण
#अन्यथा
#घोषणा irq_suspend शून्य
#घोषणा irq_resume शून्य
#पूर्ण_अगर

अटल काष्ठा syscore_ops irq_syscore_ops = अणु
	.suspend	= irq_suspend,
	.resume		= irq_resume,
पूर्ण;

अटल पूर्णांक __init irq_syscore_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&irq_syscore_ops);

	वापस 0;
पूर्ण

device_initcall(irq_syscore_init);

/*
 * For the PL010 found in the Integrator/AP some of the UART control is
 * implemented in the प्रणाली controller and accessed using a callback
 * from the driver.
 */
अटल व्योम पूर्णांकegrator_uart_set_mctrl(काष्ठा amba_device *dev,
				व्योम __iomem *base, अचिन्हित पूर्णांक mctrl)
अणु
	अचिन्हित पूर्णांक ctrls = 0, ctrlc = 0, rts_mask, dtr_mask;
	u32 phybase = dev->res.start;
	पूर्णांक ret;

	अगर (phybase == INTEGRATOR_UART0_BASE) अणु
		/* UART0 */
		rts_mask = 1 << 4;
		dtr_mask = 1 << 5;
	पूर्ण अन्यथा अणु
		/* UART1 */
		rts_mask = 1 << 6;
		dtr_mask = 1 << 7;
	पूर्ण

	अगर (mctrl & TIOCM_RTS)
		ctrlc |= rts_mask;
	अन्यथा
		ctrls |= rts_mask;

	अगर (mctrl & TIOCM_DTR)
		ctrlc |= dtr_mask;
	अन्यथा
		ctrls |= dtr_mask;

	ret = regmap_ग_लिखो(ap_syscon_map,
			   INTEGRATOR_SC_CTRLS_OFFSET,
			   ctrls);
	अगर (ret)
		pr_err("MODEM: unable to write PL010 UART CTRLS\n");

	ret = regmap_ग_लिखो(ap_syscon_map,
			   INTEGRATOR_SC_CTRLC_OFFSET,
			   ctrlc);
	अगर (ret)
		pr_err("MODEM: unable to write PL010 UART CRTLC\n");
पूर्ण

काष्ठा amba_pl010_data ap_uart_data = अणु
	.set_mctrl = पूर्णांकegrator_uart_set_mctrl,
पूर्ण;

व्योम __init ap_init_early(व्योम)
अणु
पूर्ण

अटल व्योम __init ap_init_irq_of(व्योम)
अणु
	cm_init();
	irqchip_init();
पूर्ण

/* For the Device Tree, add in the UART callbacks as AUXDATA */
अटल काष्ठा of_dev_auxdata ap_auxdata_lookup[] __initdata = अणु
	OF_DEV_AUXDATA("arm,primecell", INTEGRATOR_UART0_BASE,
		"uart0", &ap_uart_data),
	OF_DEV_AUXDATA("arm,primecell", INTEGRATOR_UART1_BASE,
		"uart1", &ap_uart_data),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ap_syscon_match[] = अणु
	अणु .compatible = "arm,integrator-ap-syscon"पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम __init ap_init_of(व्योम)
अणु
	काष्ठा device_node *syscon;

	of_platक्रमm_शेष_populate(शून्य, ap_auxdata_lookup, शून्य);

	syscon = of_find_matching_node(शून्य, ap_syscon_match);
	अगर (!syscon)
		वापस;
	ap_syscon_map = syscon_node_to_regmap(syscon);
	अगर (IS_ERR(ap_syscon_map)) अणु
		pr_crit("could not find Integrator/AP system controller\n");
		वापस;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * ap_dt_board_compat[] = अणु
	"arm,integrator-ap",
	शून्य,
पूर्ण;

DT_MACHINE_START(INTEGRATOR_AP_DT, "ARM Integrator/AP (Device Tree)")
	.reserve	= पूर्णांकegrator_reserve,
	.map_io		= ap_map_io,
	.init_early	= ap_init_early,
	.init_irq	= ap_init_irq_of,
	.init_machine	= ap_init_of,
	.dt_compat      = ap_dt_board_compat,
MACHINE_END
