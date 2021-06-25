<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PPC476 board specअगरic routines
 *
 * Copyright 2010 Torez Smith, IBM Corporation.
 *
 * Based on earlier code:
 *    Matt Porter <mporter@kernel.crashing.org>
 *    Copyright 2002-2005 MontaVista Software Inc.
 *
 *    Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *    Copyright (c) 2003-2005 Zultys Technologies
 *
 *    Rewritten and ported to the merged घातerpc tree:
 *    Copyright 2007 David Gibson <dwg@au1.ibm.com>, IBM Corporation.
 */

#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/rtc.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/uic.h>
#समावेश <यंत्र/ppc4xx.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/mmu.h>

अटल स्थिर काष्ठा of_device_id iss4xx_of_bus[] __initस्थिर = अणु
	अणु .compatible = "ibm,plb4", पूर्ण,
	अणु .compatible = "ibm,plb6", पूर्ण,
	अणु .compatible = "ibm,opb", पूर्ण,
	अणु .compatible = "ibm,ebc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक __init iss4xx_device_probe(व्योम)
अणु
	of_platक्रमm_bus_probe(शून्य, iss4xx_of_bus, शून्य);
	of_instantiate_rtc();

	वापस 0;
पूर्ण
machine_device_initcall(iss4xx, iss4xx_device_probe);

/* We can have either UICs or MPICs */
अटल व्योम __init iss4xx_init_irq(व्योम)
अणु
	काष्ठा device_node *np;

	/* Find top level पूर्णांकerrupt controller */
	क्रम_each_node_with_property(np, "interrupt-controller") अणु
		अगर (of_get_property(np, "interrupts", शून्य) == शून्य)
			अवरोध;
	पूर्ण
	अगर (np == शून्य)
		panic("Can't find top level interrupt controller");

	/* Check type and करो appropriate initialization */
	अगर (of_device_is_compatible(np, "ibm,uic")) अणु
		uic_init_tree();
		ppc_md.get_irq = uic_get_irq;
#अगर_घोषित CONFIG_MPIC
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "chrp,open-pic")) अणु
		/* The MPIC driver will get everything it needs from the
		 * device-tree, just pass 0 to all arguments
		 */
		काष्ठा mpic *mpic = mpic_alloc(np, 0, MPIC_NO_RESET, 0, 0, " MPIC     ");
		BUG_ON(mpic == शून्य);
		mpic_init(mpic);
		ppc_md.get_irq = mpic_get_irq;
#पूर्ण_अगर
	पूर्ण अन्यथा
		panic("Unrecognized top level interrupt controller");
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल व्योम smp_iss4xx_setup_cpu(पूर्णांक cpu)
अणु
	mpic_setup_this_cpu();
पूर्ण

अटल पूर्णांक smp_iss4xx_kick_cpu(पूर्णांक cpu)
अणु
	काष्ठा device_node *cpunode = of_get_cpu_node(cpu, शून्य);
	स्थिर u64 *spin_table_addr_prop;
	u32 *spin_table;
	बाह्य व्योम start_secondary_47x(व्योम);

	BUG_ON(cpunode == शून्य);

	/* Assume spin table. We could test क्रम the enable-method in
	 * the device-tree but currently there's little point as it's
	 * our only supported method
	 */
	spin_table_addr_prop = of_get_property(cpunode, "cpu-release-addr",
					       शून्य);
	अगर (spin_table_addr_prop == शून्य) अणु
		pr_err("CPU%d: Can't start, missing cpu-release-addr !\n", cpu);
		वापस -ENOENT;
	पूर्ण

	/* Assume it's mapped as part of the linear mapping. This is a bit
	 * fishy but will work fine क्रम now
	 */
	spin_table = (u32 *)__va(*spin_table_addr_prop);
	pr_debug("CPU%d: Spin table mapped at %p\n", cpu, spin_table);

	spin_table[3] = cpu;
	smp_wmb();
	spin_table[1] = __pa(start_secondary_47x);
	mb();

	वापस 0;
पूर्ण

अटल काष्ठा smp_ops_t iss_smp_ops = अणु
	.probe		= smp_mpic_probe,
	.message_pass	= smp_mpic_message_pass,
	.setup_cpu	= smp_iss4xx_setup_cpu,
	.kick_cpu	= smp_iss4xx_kick_cpu,
	.give_समयbase	= smp_generic_give_समयbase,
	.take_समयbase	= smp_generic_take_समयbase,
पूर्ण;

अटल व्योम __init iss4xx_smp_init(व्योम)
अणु
	अगर (mmu_has_feature(MMU_FTR_TYPE_47x))
		smp_ops = &iss_smp_ops;
पूर्ण

#अन्यथा /* CONFIG_SMP */
अटल व्योम __init iss4xx_smp_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम __init iss4xx_setup_arch(व्योम)
अणु
	iss4xx_smp_init();
पूर्ण

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init iss4xx_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("ibm,iss-4xx"))
		वापस 0;

	वापस 1;
पूर्ण

define_machine(iss4xx) अणु
	.name			= "ISS-4xx",
	.probe			= iss4xx_probe,
	.progress		= udbg_progress,
	.init_IRQ		= iss4xx_init_irq,
	.setup_arch		= iss4xx_setup_arch,
	.restart		= ppc4xx_reset_प्रणाली,
	.calibrate_decr		= generic_calibrate_decr,
पूर्ण;
