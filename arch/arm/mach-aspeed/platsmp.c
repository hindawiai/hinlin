<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// Copyright (C) ASPEED Technology Inc.
// Copyright IBM Corp.

#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/smp.h>

#घोषणा BOOT_ADDR	0x00
#घोषणा BOOT_SIG	0x04

अटल काष्ठा device_node *secboot_node;

अटल पूर्णांक aspeed_g6_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	व्योम __iomem *base;

	base = of_iomap(secboot_node, 0);
	अगर (!base) अणु
		pr_err("could not map the secondary boot base!");
		वापस -ENODEV;
	पूर्ण

	ग_लिखोl_relaxed(0, base + BOOT_ADDR);
	ग_लिखोl_relaxed(__pa_symbol(secondary_startup_arm), base + BOOT_ADDR);
	ग_लिखोl_relaxed((0xABBAAB00 | (cpu & 0xff)), base + BOOT_SIG);

	dsb_sev();

	iounmap(base);

	वापस 0;
पूर्ण

अटल व्योम __init aspeed_g6_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	व्योम __iomem *base;

	secboot_node = of_find_compatible_node(शून्य, शून्य, "aspeed,ast2600-smpmem");
	अगर (!secboot_node) अणु
		pr_err("secboot device node found!!\n");
		वापस;
	पूर्ण

	base = of_iomap(secboot_node, 0);
	अगर (!base) अणु
		pr_err("could not map the secondary boot base!");
		वापस;
	पूर्ण
	__raw_ग_लिखोl(0xBADABABA, base + BOOT_SIG);

	iounmap(base);
पूर्ण

अटल स्थिर काष्ठा smp_operations aspeed_smp_ops __initस्थिर = अणु
	.smp_prepare_cpus	= aspeed_g6_smp_prepare_cpus,
	.smp_boot_secondary	= aspeed_g6_boot_secondary,
पूर्ण;

CPU_METHOD_OF_DECLARE(aspeed_smp, "aspeed,ast2600-smp", &aspeed_smp_ops);
