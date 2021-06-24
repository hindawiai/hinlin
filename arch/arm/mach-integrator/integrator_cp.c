<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-पूर्णांकegrator/पूर्णांकegrator_cp.c
 *
 *  Copyright (C) 2003 Deep Blue Solutions Ltd
 */
#समावेश <linux/kernel.h>
#समावेश <linux/amba/mmci.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "hardware.h"
#समावेश "cm.h"
#समावेश "common.h"

/* Base address to the core module header */
अटल काष्ठा regmap *cm_map;
/* Base address to the CP controller */
अटल व्योम __iomem *पूर्णांकcp_con_base;

#घोषणा CM_COUNTER_OFFSET 0x28

/*
 * Logical      Physical
 * f1400000	14000000	Interrupt controller
 * f1600000	16000000	UART 0
 * fca00000	ca000000	SIC
 */

अटल काष्ठा map_desc पूर्णांकcp_io_desc[] __initdata __maybe_unused = अणु
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
	पूर्ण, अणु
		.भव	= IO_ADDRESS(INTEGRATOR_CP_SIC_BASE),
		.pfn		= __phys_to_pfn(INTEGRATOR_CP_SIC_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल व्योम __init पूर्णांकcp_map_io(व्योम)
अणु
	iotable_init(पूर्णांकcp_io_desc, ARRAY_SIZE(पूर्णांकcp_io_desc));
पूर्ण

/*
 * It seems that the card insertion पूर्णांकerrupt reमुख्यs active after
 * we've acknowledged it.  We thereक्रमe ignore the पूर्णांकerrupt, and
 * rely on पढ़ोing it from the SIC.  This also means that we must
 * clear the latched पूर्णांकerrupt.
 */
अटल अचिन्हित पूर्णांक mmc_status(काष्ठा device *dev)
अणु
	अचिन्हित पूर्णांक status = पढ़ोl(__io_address(0xca000000 + 4));
	ग_लिखोl(8, पूर्णांकcp_con_base + 8);

	वापस status & 8;
पूर्ण

अटल काष्ठा mmci_platक्रमm_data mmc_data = अणु
	.ocr_mask	= MMC_VDD_32_33|MMC_VDD_33_34,
	.status		= mmc_status,
पूर्ण;

अटल u64 notrace पूर्णांकcp_पढ़ो_sched_घड़ी(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	/* MMIO so discard वापस code */
	regmap_पढ़ो(cm_map, CM_COUNTER_OFFSET, &val);
	वापस val;
पूर्ण

अटल व्योम __init पूर्णांकcp_init_early(व्योम)
अणु
	cm_map = syscon_regmap_lookup_by_compatible("arm,core-module-integrator");
	अगर (IS_ERR(cm_map))
		वापस;
	sched_घड़ी_रेजिस्टर(पूर्णांकcp_पढ़ो_sched_घड़ी, 32, 24000000);
पूर्ण

अटल व्योम __init पूर्णांकcp_init_irq_of(व्योम)
अणु
	cm_init();
	irqchip_init();
पूर्ण

/*
 * For the Device Tree, add in the UART, MMC and CLCD specअगरics as AUXDATA
 * and enक्रमce the bus names since these are used क्रम घड़ी lookups.
 */
अटल काष्ठा of_dev_auxdata पूर्णांकcp_auxdata_lookup[] __initdata = अणु
	OF_DEV_AUXDATA("arm,primecell", INTEGRATOR_CP_MMC_BASE,
		"mmci", &mmc_data),
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id पूर्णांकcp_syscon_match[] = अणु
	अणु .compatible = "arm,integrator-cp-syscon"पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम __init पूर्णांकcp_init_of(व्योम)
अणु
	काष्ठा device_node *cpcon;

	cpcon = of_find_matching_node(शून्य, पूर्णांकcp_syscon_match);
	अगर (!cpcon)
		वापस;

	पूर्णांकcp_con_base = of_iomap(cpcon, 0);
	अगर (!पूर्णांकcp_con_base)
		वापस;

	of_platक्रमm_शेष_populate(शून्य, पूर्णांकcp_auxdata_lookup, शून्य);
पूर्ण

अटल स्थिर अक्षर * पूर्णांकcp_dt_board_compat[] = अणु
	"arm,integrator-cp",
	शून्य,
पूर्ण;

DT_MACHINE_START(INTEGRATOR_CP_DT, "ARM Integrator/CP (Device Tree)")
	.reserve	= पूर्णांकegrator_reserve,
	.map_io		= पूर्णांकcp_map_io,
	.init_early	= पूर्णांकcp_init_early,
	.init_irq	= पूर्णांकcp_init_irq_of,
	.init_machine	= पूर्णांकcp_init_of,
	.dt_compat      = पूर्णांकcp_dt_board_compat,
MACHINE_END
