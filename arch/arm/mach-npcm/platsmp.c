<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Nuvoton Technology corporation.
// Copyright 2018 Google, Inc.

#घोषणा pr_fmt(fmt) "nuvoton,npcm7xx-smp: " fmt

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/smp_scu.h>

#घोषणा NPCM7XX_SCRPAD_REG 0x13c

बाह्य व्योम npcm7xx_secondary_startup(व्योम);

अटल पूर्णांक npcm7xx_smp_boot_secondary(अचिन्हित पूर्णांक cpu,
				      काष्ठा task_काष्ठा *idle)
अणु
	काष्ठा device_node *gcr_np;
	व्योम __iomem *gcr_base;
	पूर्णांक ret = 0;

	gcr_np = of_find_compatible_node(शून्य, शून्य, "nuvoton,npcm750-gcr");
	अगर (!gcr_np) अणु
		pr_err("no gcr device node\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	gcr_base = of_iomap(gcr_np, 0);
	अगर (!gcr_base) अणु
		pr_err("could not iomap gcr");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* give boot ROM kernel start address. */
	ioग_लिखो32(__pa_symbol(npcm7xx_secondary_startup), gcr_base +
		  NPCM7XX_SCRPAD_REG);
	/* make sure the previous ग_लिखो is seen by all observers. */
	dsb_sev();

	iounmap(gcr_base);
out:
	वापस ret;
पूर्ण

अटल व्योम __init npcm7xx_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	काष्ठा device_node *scu_np;
	व्योम __iomem *scu_base;

	scu_np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-scu");
	अगर (!scu_np) अणु
		pr_err("no scu device node\n");
		वापस;
	पूर्ण
	scu_base = of_iomap(scu_np, 0);
	अगर (!scu_base) अणु
		pr_err("could not iomap scu");
		वापस;
	पूर्ण

	scu_enable(scu_base);

	iounmap(scu_base);
पूर्ण

अटल काष्ठा smp_operations npcm7xx_smp_ops __initdata = अणु
	.smp_prepare_cpus = npcm7xx_smp_prepare_cpus,
	.smp_boot_secondary = npcm7xx_smp_boot_secondary,
पूर्ण;

CPU_METHOD_OF_DECLARE(npcm7xx_smp, "nuvoton,npcm750-smp", &npcm7xx_smp_ops);
