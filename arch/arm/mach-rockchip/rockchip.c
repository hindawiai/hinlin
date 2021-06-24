<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device Tree support क्रम Rockchip SoCs
 *
 * Copyright (c) 2013 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश "core.h"
#समावेश "pm.h"

#घोषणा RK3288_TIMER6_7_PHYS 0xff810000

अटल व्योम __init rockchip_समयr_init(व्योम)
अणु
	अगर (of_machine_is_compatible("rockchip,rk3288")) अणु
		व्योम __iomem *reg_base;

		/*
		 * Most/all uboot versions क्रम rk3288 करोn't enable समयr7
		 * which is needed क्रम the architected समयr to work.
		 * So make sure it is running during early boot.
		 */
		reg_base = ioremap(RK3288_TIMER6_7_PHYS, SZ_16K);
		अगर (reg_base) अणु
			ग_लिखोl(0, reg_base + 0x30);
			ग_लिखोl(0xffffffff, reg_base + 0x20);
			ग_लिखोl(0xffffffff, reg_base + 0x24);
			ग_लिखोl(1, reg_base + 0x30);
			dsb();
			iounmap(reg_base);
		पूर्ण अन्यथा अणु
			pr_err("rockchip: could not map timer7 registers\n");
		पूर्ण
	पूर्ण

	of_clk_init(शून्य);
	समयr_probe();
पूर्ण

अटल व्योम __init rockchip_dt_init(व्योम)
अणु
	rockchip_suspend_init();
पूर्ण

अटल स्थिर अक्षर * स्थिर rockchip_board_dt_compat[] = अणु
	"rockchip,rk2928",
	"rockchip,rk3066a",
	"rockchip,rk3066b",
	"rockchip,rk3188",
	"rockchip,rk3228",
	"rockchip,rk3288",
	"rockchip,rv1108",
	शून्य,
पूर्ण;

DT_MACHINE_START(ROCKCHIP_DT, "Rockchip (Device Tree)")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.init_समय	= rockchip_समयr_init,
	.dt_compat	= rockchip_board_dt_compat,
	.init_machine	= rockchip_dt_init,
MACHINE_END
