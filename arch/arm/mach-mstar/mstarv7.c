<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device Tree support क्रम MStar/Sigmastar Armv7 SoCs
 *
 * Copyright (c) 2020 thingy.jp
 * Author: Daniel Palmer <daniel@thingy.jp>
 */

#समावेश <linux/init.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पन.स>

/*
 * In the u-boot code the area these रेजिस्टरs are in is
 * called "L3 bridge" and there are रेजिस्टर descriptions
 * क्रम something in the same area called "AXI".
 *
 * It's not exactly known what this is but the venकरोr code
 * क्रम both u-boot and linux share calls to "flush the miu pipe".
 * This seems to be to क्रमce pending CPU ग_लिखोs to memory so that
 * the state is right beक्रमe DMA capable devices try to पढ़ो
 * descriptors and data the CPU has prepared. Without करोing this
 * ethernet करोesn't work reliably क्रम example.
 */

#घोषणा MSTARV7_L3BRIDGE_FLUSH		0x14
#घोषणा MSTARV7_L3BRIDGE_STATUS		0x40
#घोषणा MSTARV7_L3BRIDGE_FLUSH_TRIGGER	BIT(0)
#घोषणा MSTARV7_L3BRIDGE_STATUS_DONE	BIT(12)

#अगर_घोषित CONFIG_SMP
#घोषणा MSTARV7_CPU1_BOOT_ADDR_HIGH	0x4c
#घोषणा MSTARV7_CPU1_BOOT_ADDR_LOW	0x50
#घोषणा MSTARV7_CPU1_UNLOCK		0x58
#घोषणा MSTARV7_CPU1_UNLOCK_MAGIC	0xbabe
#पूर्ण_अगर

अटल व्योम __iomem *l3bridge;

अटल स्थिर अक्षर * स्थिर mstarv7_board_dt_compat[] __initस्थिर = अणु
	"mstar,infinity",
	"mstar,infinity2m",
	"mstar,infinity3",
	"mstar,mercury5",
	शून्य,
पूर्ण;

/*
 * This may need locking to deal with situations where an पूर्णांकerrupt
 * happens जबतक we are in here and mb() माला_लो called by the पूर्णांकerrupt handler.
 *
 * The venकरोr code did have a spin lock but it करोesn't seem to be needed and
 * removing it hasn't caused any side effects so far.
 *
 * [ग_लिखोl|पढ़ोl]_relaxed have to be used here because otherwise
 * we'd end up right back in here.
 */
अटल व्योम mstarv7_mb(व्योम)
अणु
	/* toggle the flush miu pipe fire bit */
	ग_लिखोl_relaxed(0, l3bridge + MSTARV7_L3BRIDGE_FLUSH);
	ग_लिखोl_relaxed(MSTARV7_L3BRIDGE_FLUSH_TRIGGER, l3bridge
			+ MSTARV7_L3BRIDGE_FLUSH);
	जबतक (!(पढ़ोl_relaxed(l3bridge + MSTARV7_L3BRIDGE_STATUS)
			& MSTARV7_L3BRIDGE_STATUS_DONE)) अणु
		/* रुको क्रम flush to complete */
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक mstarv7_boot_secondary(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle)
अणु
	काष्ठा device_node *np;
	u32 bootaddr = (u32) __pa_symbol(secondary_startup_arm);
	व्योम __iomem *smpctrl;

	/*
	 * right now we करोn't know how to boot anything except
	 * cpu 1.
	 */
	अगर (cpu != 1)
		वापस -EINVAL;

	np = of_find_compatible_node(शून्य, शून्य, "mstar,smpctrl");
	smpctrl = of_iomap(np, 0);

	अगर (!smpctrl)
		वापस -ENODEV;

	/* set the boot address क्रम the second cpu */
	ग_लिखोw(bootaddr & 0xffff, smpctrl + MSTARV7_CPU1_BOOT_ADDR_LOW);
	ग_लिखोw((bootaddr >> 16) & 0xffff, smpctrl + MSTARV7_CPU1_BOOT_ADDR_HIGH);

	/* unlock the second cpu */
	ग_लिखोw(MSTARV7_CPU1_UNLOCK_MAGIC, smpctrl + MSTARV7_CPU1_UNLOCK);

	/* and away we go...*/
	arch_send_wakeup_ipi_mask(cpumask_of(cpu));

	iounmap(smpctrl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा smp_operations __initdata mstarv7_smp_ops = अणु
	.smp_boot_secondary = mstarv7_boot_secondary,
पूर्ण;
#पूर्ण_अगर

अटल व्योम __init mstarv7_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "mstar,l3bridge");
	l3bridge = of_iomap(np, 0);
	अगर (l3bridge)
		soc_mb = mstarv7_mb;
	अन्यथा
		pr_warn("Failed to install memory barrier, DMA will be broken!\n");
पूर्ण

DT_MACHINE_START(MSTARV7_DT, "MStar/Sigmastar Armv7 (Device Tree)")
	.dt_compat	= mstarv7_board_dt_compat,
	.init_machine	= mstarv7_init,
	.smp		= smp_ops(mstarv7_smp_ops),
MACHINE_END
