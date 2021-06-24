<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "core.h"

#घोषणा SYS_FLAGSSET		0x030
#घोषणा SYS_FLAGSCLR		0x034

व्योम vexpress_flags_set(u32 data)
अणु
	अटल व्योम __iomem *base;

	अगर (!base) अणु
		काष्ठा device_node *node = of_find_compatible_node(शून्य, शून्य,
				"arm,vexpress-sysreg");

		base = of_iomap(node, 0);
	पूर्ण

	अगर (WARN_ON(!base))
		वापस;

	ग_लिखोl(~0, base + SYS_FLAGSCLR);
	ग_लिखोl(data, base + SYS_FLAGSSET);
पूर्ण

अटल स्थिर अक्षर * स्थिर v2m_dt_match[] __initस्थिर = अणु
	"arm,vexpress",
	शून्य,
पूर्ण;

DT_MACHINE_START(VEXPRESS_DT, "ARM-Versatile Express")
	.dt_compat	= v2m_dt_match,
	.l2c_aux_val	= 0x00400000,
	.l2c_aux_mask	= 0xfe0fffff,
	.smp		= smp_ops(vexpress_smp_dt_ops),
	.smp_init	= smp_init_ops(vexpress_smp_init_ops),
MACHINE_END
