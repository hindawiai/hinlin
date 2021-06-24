<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2013 HiSilicon Limited.
 */

#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश "core.h"

/* Sysctrl रेजिस्टरs in Hi3620 SoC */
#घोषणा SCISOEN				0xc0
#घोषणा SCISODIS			0xc4
#घोषणा SCPERPWREN			0xd0
#घोषणा SCPERPWRDIS			0xd4
#घोषणा SCCPUCOREEN			0xf4
#घोषणा SCCPUCOREDIS			0xf8
#घोषणा SCPERCTRL0			0x200
#घोषणा SCCPURSTEN			0x410
#घोषणा SCCPURSTDIS			0x414

/*
 * bit definition in SCISOEN/SCPERPWREN/...
 *
 * CPU2_ISO_CTRL	(1 << 5)
 * CPU3_ISO_CTRL	(1 << 6)
 * ...
 */
#घोषणा CPU2_ISO_CTRL			(1 << 5)

/*
 * bit definition in SCPERCTRL0
 *
 * CPU0_WFI_MASK_CFG	(1 << 28)
 * CPU1_WFI_MASK_CFG	(1 << 29)
 * ...
 */
#घोषणा CPU0_WFI_MASK_CFG		(1 << 28)

/*
 * bit definition in SCCPURSTEN/...
 *
 * CPU0_SRST_REQ_EN	(1 << 0)
 * CPU1_SRST_REQ_EN	(1 << 1)
 * ...
 */
#घोषणा CPU0_HPM_SRST_REQ_EN		(1 << 22)
#घोषणा CPU0_DBG_SRST_REQ_EN		(1 << 12)
#घोषणा CPU0_NEON_SRST_REQ_EN		(1 << 4)
#घोषणा CPU0_SRST_REQ_EN		(1 << 0)

#घोषणा HIX5HD2_PERI_CRG20		0x50
#घोषणा CRG20_CPU1_RESET		(1 << 17)

#घोषणा HIX5HD2_PERI_PMC0		0x1000
#घोषणा PMC0_CPU1_WAIT_MTCOMS_ACK	(1 << 8)
#घोषणा PMC0_CPU1_PMC_ENABLE		(1 << 7)
#घोषणा PMC0_CPU1_POWERDOWN		(1 << 3)

#घोषणा HIP01_PERI9                    0x50
#घोषणा PERI9_CPU1_RESET               (1 << 1)

क्रमागत अणु
	HI3620_CTRL,
	ERROR_CTRL,
पूर्ण;

अटल व्योम __iomem *ctrl_base;
अटल पूर्णांक id;

अटल व्योम set_cpu_hi3620(पूर्णांक cpu, bool enable)
अणु
	u32 val = 0;

	अगर (enable) अणु
		/* MTCMOS set */
		अगर ((cpu == 2) || (cpu == 3))
			ग_लिखोl_relaxed(CPU2_ISO_CTRL << (cpu - 2),
				       ctrl_base + SCPERPWREN);
		udelay(100);

		/* Enable core */
		ग_लिखोl_relaxed(0x01 << cpu, ctrl_base + SCCPUCOREEN);

		/* unreset */
		val = CPU0_DBG_SRST_REQ_EN | CPU0_NEON_SRST_REQ_EN
			| CPU0_SRST_REQ_EN;
		ग_लिखोl_relaxed(val << cpu, ctrl_base + SCCPURSTDIS);
		/* reset */
		val |= CPU0_HPM_SRST_REQ_EN;
		ग_लिखोl_relaxed(val << cpu, ctrl_base + SCCPURSTEN);

		/* ISO disable */
		अगर ((cpu == 2) || (cpu == 3))
			ग_लिखोl_relaxed(CPU2_ISO_CTRL << (cpu - 2),
				       ctrl_base + SCISODIS);
		udelay(1);

		/* WFI Mask */
		val = पढ़ोl_relaxed(ctrl_base + SCPERCTRL0);
		val &= ~(CPU0_WFI_MASK_CFG << cpu);
		ग_लिखोl_relaxed(val, ctrl_base + SCPERCTRL0);

		/* Unreset */
		val = CPU0_DBG_SRST_REQ_EN | CPU0_NEON_SRST_REQ_EN
			| CPU0_SRST_REQ_EN | CPU0_HPM_SRST_REQ_EN;
		ग_लिखोl_relaxed(val << cpu, ctrl_base + SCCPURSTDIS);
	पूर्ण अन्यथा अणु
		/* wfi mask */
		val = पढ़ोl_relaxed(ctrl_base + SCPERCTRL0);
		val |= (CPU0_WFI_MASK_CFG << cpu);
		ग_लिखोl_relaxed(val, ctrl_base + SCPERCTRL0);

		/* disable core*/
		ग_लिखोl_relaxed(0x01 << cpu, ctrl_base + SCCPUCOREDIS);

		अगर ((cpu == 2) || (cpu == 3)) अणु
			/* iso enable */
			ग_लिखोl_relaxed(CPU2_ISO_CTRL << (cpu - 2),
				       ctrl_base + SCISOEN);
			udelay(1);
		पूर्ण

		/* reset */
		val = CPU0_DBG_SRST_REQ_EN | CPU0_NEON_SRST_REQ_EN
			| CPU0_SRST_REQ_EN | CPU0_HPM_SRST_REQ_EN;
		ग_लिखोl_relaxed(val << cpu, ctrl_base + SCCPURSTEN);

		अगर ((cpu == 2) || (cpu == 3)) अणु
			/* MTCMOS unset */
			ग_लिखोl_relaxed(CPU2_ISO_CTRL << (cpu - 2),
				       ctrl_base + SCPERPWRDIS);
			udelay(100);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hi3xxx_hotplug_init(व्योम)
अणु
	काष्ठा device_node *node;

	node = of_find_compatible_node(शून्य, शून्य, "hisilicon,sysctrl");
	अगर (!node) अणु
		id = ERROR_CTRL;
		वापस -ENOENT;
	पूर्ण

	ctrl_base = of_iomap(node, 0);
	of_node_put(node);
	अगर (!ctrl_base) अणु
		id = ERROR_CTRL;
		वापस -ENOMEM;
	पूर्ण

	id = HI3620_CTRL;
	वापस 0;
पूर्ण

व्योम hi3xxx_set_cpu(पूर्णांक cpu, bool enable)
अणु
	अगर (!ctrl_base) अणु
		अगर (hi3xxx_hotplug_init() < 0)
			वापस;
	पूर्ण

	अगर (id == HI3620_CTRL)
		set_cpu_hi3620(cpu, enable);
पूर्ण

अटल bool hix5hd2_hotplug_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "hisilicon,cpuctrl");
	अगर (!np)
		वापस false;

	ctrl_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!ctrl_base)
		वापस false;

	वापस true;
पूर्ण

व्योम hix5hd2_set_cpu(पूर्णांक cpu, bool enable)
अणु
	u32 val = 0;

	अगर (!ctrl_base)
		अगर (!hix5hd2_hotplug_init())
			BUG();

	अगर (enable) अणु
		/* घातer on cpu1 */
		val = पढ़ोl_relaxed(ctrl_base + HIX5HD2_PERI_PMC0);
		val &= ~(PMC0_CPU1_WAIT_MTCOMS_ACK | PMC0_CPU1_POWERDOWN);
		val |= PMC0_CPU1_PMC_ENABLE;
		ग_लिखोl_relaxed(val, ctrl_base + HIX5HD2_PERI_PMC0);
		/* unreset */
		val = पढ़ोl_relaxed(ctrl_base + HIX5HD2_PERI_CRG20);
		val &= ~CRG20_CPU1_RESET;
		ग_लिखोl_relaxed(val, ctrl_base + HIX5HD2_PERI_CRG20);
	पूर्ण अन्यथा अणु
		/* घातer करोwn cpu1 */
		val = पढ़ोl_relaxed(ctrl_base + HIX5HD2_PERI_PMC0);
		val |= PMC0_CPU1_PMC_ENABLE | PMC0_CPU1_POWERDOWN;
		val &= ~PMC0_CPU1_WAIT_MTCOMS_ACK;
		ग_लिखोl_relaxed(val, ctrl_base + HIX5HD2_PERI_PMC0);

		/* reset */
		val = पढ़ोl_relaxed(ctrl_base + HIX5HD2_PERI_CRG20);
		val |= CRG20_CPU1_RESET;
		ग_लिखोl_relaxed(val, ctrl_base + HIX5HD2_PERI_CRG20);
	पूर्ण
पूर्ण

व्योम hip01_set_cpu(पूर्णांक cpu, bool enable)
अणु
	अचिन्हित पूर्णांक temp;
	काष्ठा device_node *np;

	अगर (!ctrl_base) अणु
		np = of_find_compatible_node(शून्य, शून्य, "hisilicon,hip01-sysctrl");
		BUG_ON(!np);
		ctrl_base = of_iomap(np, 0);
		of_node_put(np);
		BUG_ON(!ctrl_base);
	पूर्ण

	अगर (enable) अणु
		/* reset on CPU1  */
		temp = पढ़ोl_relaxed(ctrl_base + HIP01_PERI9);
		temp |= PERI9_CPU1_RESET;
		ग_लिखोl_relaxed(temp, ctrl_base + HIP01_PERI9);

		udelay(50);

		/* unreset on CPU1 */
		temp = पढ़ोl_relaxed(ctrl_base + HIP01_PERI9);
		temp &= ~PERI9_CPU1_RESET;
		ग_लिखोl_relaxed(temp, ctrl_base + HIP01_PERI9);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_enter_lowघातer(व्योम)
अणु
	अचिन्हित पूर्णांक v;

	flush_cache_all();

	/*
	 * Turn off coherency and L1 D-cache
	 */
	यंत्र अस्थिर(
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, #0x40\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	"	mrc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, #0x04\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	  : "=&r" (v)
	  : "r" (0)
	  : "cc");
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम hi3xxx_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	cpu_enter_lowघातer();
	hi3xxx_set_cpu_jump(cpu, phys_to_virt(0));
	cpu_करो_idle();

	/* We should have never वापसed from idle */
	panic("cpu %d unexpectedly exit from shutdown\n", cpu);
पूर्ण

पूर्णांक hi3xxx_cpu_समाप्त(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(50);

	जबतक (hi3xxx_get_cpu_jump(cpu))
		अगर (समय_after(jअगरfies, समयout))
			वापस 0;
	hi3xxx_set_cpu(cpu, false);
	वापस 1;
पूर्ण

व्योम hix5hd2_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	flush_cache_all();
	hix5hd2_set_cpu(cpu, false);
पूर्ण
#पूर्ण_अगर
