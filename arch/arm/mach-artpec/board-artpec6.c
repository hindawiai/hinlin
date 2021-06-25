<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARTPEC-6 device support.
 */

#समावेश <linux/amba/bus.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/smp_scu.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/psci.h>
#समावेश <linux/arm-smccc.h>


#घोषणा ARTPEC6_DMACFG_REGNUM 0x10
#घोषणा ARTPEC6_DMACFG_UARTS_BURST 0xff

#घोषणा SECURE_OP_L2C_WRITEREG 0xb4000001

अटल व्योम __init artpec6_init_machine(व्योम)
अणु
	काष्ठा regmap *regmap;

	regmap = syscon_regmap_lookup_by_compatible("axis,artpec6-syscon");

	अगर (!IS_ERR(regmap)) अणु
		/* Use PL011 DMA Burst Request संकेत instead of DMA
		 *  Single Request
		 */
		regmap_ग_लिखो(regmap, ARTPEC6_DMACFG_REGNUM,
			     ARTPEC6_DMACFG_UARTS_BURST);
	पूर्ण;
पूर्ण

अटल व्योम artpec6_l2c310_ग_लिखो_sec(अचिन्हित दीर्घ val, अचिन्हित reg)
अणु
	काष्ठा arm_smccc_res res;

	arm_smccc_smc(SECURE_OP_L2C_WRITEREG, reg, val, 0,
		      0, 0, 0, 0, &res);

	WARN_ON(res.a0);
पूर्ण

अटल स्थिर अक्षर * स्थिर artpec6_dt_match[] = अणु
	"axis,artpec6",
	शून्य
पूर्ण;

DT_MACHINE_START(ARTPEC6, "Axis ARTPEC-6 Platform")
	.l2c_aux_val	= 0x0C000000,
	.l2c_aux_mask	= 0xF3FFFFFF,
	.l2c_ग_लिखो_sec  = artpec6_l2c310_ग_लिखो_sec,
	.init_machine	= artpec6_init_machine,
	.dt_compat	= artpec6_dt_match,
MACHINE_END
