<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 Freescale Semiconductor, Inc.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश "common.h"

#घोषणा SRC_SCR				0x000
#घोषणा SRC_GPR1			0x020
#घोषणा BP_SRC_SCR_WARM_RESET_ENABLE	0
#घोषणा BP_SRC_SCR_SW_GPU_RST		1
#घोषणा BP_SRC_SCR_SW_VPU_RST		2
#घोषणा BP_SRC_SCR_SW_IPU1_RST		3
#घोषणा BP_SRC_SCR_SW_OPEN_VG_RST	4
#घोषणा BP_SRC_SCR_SW_IPU2_RST		12
#घोषणा BP_SRC_SCR_CORE1_RST		14
#घोषणा BP_SRC_SCR_CORE1_ENABLE		22

अटल व्योम __iomem *src_base;
अटल DEFINE_SPINLOCK(scr_lock);

अटल स्थिर पूर्णांक sw_reset_bits[5] = अणु
	BP_SRC_SCR_SW_GPU_RST,
	BP_SRC_SCR_SW_VPU_RST,
	BP_SRC_SCR_SW_IPU1_RST,
	BP_SRC_SCR_SW_OPEN_VG_RST,
	BP_SRC_SCR_SW_IPU2_RST
पूर्ण;

अटल पूर्णांक imx_src_reset_module(काष्ठा reset_controller_dev *rcdev,
		अचिन्हित दीर्घ sw_reset_idx)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ flags;
	पूर्णांक bit;
	u32 val;

	अगर (sw_reset_idx >= ARRAY_SIZE(sw_reset_bits))
		वापस -EINVAL;

	bit = 1 << sw_reset_bits[sw_reset_idx];

	spin_lock_irqsave(&scr_lock, flags);
	val = पढ़ोl_relaxed(src_base + SRC_SCR);
	val |= bit;
	ग_लिखोl_relaxed(val, src_base + SRC_SCR);
	spin_unlock_irqrestore(&scr_lock, flags);

	समयout = jअगरfies + msecs_to_jअगरfies(1000);
	जबतक (पढ़ोl(src_base + SRC_SCR) & bit) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIME;
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops imx_src_ops = अणु
	.reset = imx_src_reset_module,
पूर्ण;

अटल काष्ठा reset_controller_dev imx_reset_controller = अणु
	.ops = &imx_src_ops,
	.nr_resets = ARRAY_SIZE(sw_reset_bits),
पूर्ण;

व्योम imx_enable_cpu(पूर्णांक cpu, bool enable)
अणु
	u32 mask, val;

	cpu = cpu_logical_map(cpu);
	mask = 1 << (BP_SRC_SCR_CORE1_ENABLE + cpu - 1);
	spin_lock(&scr_lock);
	val = पढ़ोl_relaxed(src_base + SRC_SCR);
	val = enable ? val | mask : val & ~mask;
	val |= 1 << (BP_SRC_SCR_CORE1_RST + cpu - 1);
	ग_लिखोl_relaxed(val, src_base + SRC_SCR);
	spin_unlock(&scr_lock);
पूर्ण

व्योम imx_set_cpu_jump(पूर्णांक cpu, व्योम *jump_addr)
अणु
	cpu = cpu_logical_map(cpu);
	ग_लिखोl_relaxed(__pa_symbol(jump_addr),
		       src_base + SRC_GPR1 + cpu * 8);
पूर्ण

u32 imx_get_cpu_arg(पूर्णांक cpu)
अणु
	cpu = cpu_logical_map(cpu);
	वापस पढ़ोl_relaxed(src_base + SRC_GPR1 + cpu * 8 + 4);
पूर्ण

व्योम imx_set_cpu_arg(पूर्णांक cpu, u32 arg)
अणु
	cpu = cpu_logical_map(cpu);
	ग_लिखोl_relaxed(arg, src_base + SRC_GPR1 + cpu * 8 + 4);
पूर्ण

व्योम __init imx_src_init(व्योम)
अणु
	काष्ठा device_node *np;
	u32 val;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx51-src");
	अगर (!np)
		वापस;
	src_base = of_iomap(np, 0);
	WARN_ON(!src_base);

	imx_reset_controller.of_node = np;
	अगर (IS_ENABLED(CONFIG_RESET_CONTROLLER))
		reset_controller_रेजिस्टर(&imx_reset_controller);

	/*
	 * क्रमce warm reset sources to generate cold reset
	 * क्रम a more reliable restart
	 */
	spin_lock(&scr_lock);
	val = पढ़ोl_relaxed(src_base + SRC_SCR);
	val &= ~(1 << BP_SRC_SCR_WARM_RESET_ENABLE);
	ग_लिखोl_relaxed(val, src_base + SRC_SCR);
	spin_unlock(&scr_lock);
पूर्ण
