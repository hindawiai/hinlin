<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/percpu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/mips-cps.h>

व्योम __iomem *mips_cpc_base;

अटल DEFINE_PER_CPU_ALIGNED(spinlock_t, cpc_core_lock);

अटल DEFINE_PER_CPU_ALIGNED(अचिन्हित दीर्घ, cpc_core_lock_flags);

phys_addr_t __weak mips_cpc_शेष_phys_base(व्योम)
अणु
	काष्ठा device_node *cpc_node;
	काष्ठा resource res;
	पूर्णांक err;

	cpc_node = of_find_compatible_node(of_root, शून्य, "mti,mips-cpc");
	अगर (cpc_node) अणु
		err = of_address_to_resource(cpc_node, 0, &res);
		अगर (!err)
			वापस res.start;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mips_cpc_phys_base - retrieve the physical base address of the CPC
 *
 * This function वापसs the physical base address of the Cluster Power
 * Controller memory mapped रेजिस्टरs, or 0 अगर no Cluster Power Controller
 * is present.
 */
अटल phys_addr_t mips_cpc_phys_base(व्योम)
अणु
	अचिन्हित दीर्घ cpc_base;

	अगर (!mips_cm_present())
		वापस 0;

	अगर (!(पढ़ो_gcr_cpc_status() & CM_GCR_CPC_STATUS_EX))
		वापस 0;

	/* If the CPC is alपढ़ोy enabled, leave it so */
	cpc_base = पढ़ो_gcr_cpc_base();
	अगर (cpc_base & CM_GCR_CPC_BASE_CPCEN)
		वापस cpc_base & CM_GCR_CPC_BASE_CPCBASE;

	/* Otherwise, use the शेष address */
	cpc_base = mips_cpc_शेष_phys_base();
	अगर (!cpc_base)
		वापस cpc_base;

	/* Enable the CPC, mapped at the शेष address */
	ग_लिखो_gcr_cpc_base(cpc_base | CM_GCR_CPC_BASE_CPCEN);
	वापस cpc_base;
पूर्ण

पूर्णांक mips_cpc_probe(व्योम)
अणु
	phys_addr_t addr;
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		spin_lock_init(&per_cpu(cpc_core_lock, cpu));

	addr = mips_cpc_phys_base();
	अगर (!addr)
		वापस -ENODEV;

	mips_cpc_base = ioremap(addr, 0x8000);
	अगर (!mips_cpc_base)
		वापस -ENXIO;

	वापस 0;
पूर्ण

व्योम mips_cpc_lock_other(अचिन्हित पूर्णांक core)
अणु
	अचिन्हित पूर्णांक curr_core;

	अगर (mips_cm_revision() >= CM_REV_CM3)
		/* Systems with CM >= 3 lock the CPC via mips_cm_lock_other */
		वापस;

	preempt_disable();
	curr_core = cpu_core(&current_cpu_data);
	spin_lock_irqsave(&per_cpu(cpc_core_lock, curr_core),
			  per_cpu(cpc_core_lock_flags, curr_core));
	ग_लिखो_cpc_cl_other(core << __ffs(CPC_Cx_OTHER_CORENUM));

	/*
	 * Ensure the core-other region reflects the appropriate core &
	 * VP beक्रमe any accesses to it occur.
	 */
	mb();
पूर्ण

व्योम mips_cpc_unlock_other(व्योम)
अणु
	अचिन्हित पूर्णांक curr_core;

	अगर (mips_cm_revision() >= CM_REV_CM3)
		/* Systems with CM >= 3 lock the CPC via mips_cm_lock_other */
		वापस;

	curr_core = cpu_core(&current_cpu_data);
	spin_unlock_irqrestore(&per_cpu(cpc_core_lock, curr_core),
			       per_cpu(cpc_core_lock_flags, curr_core));
	preempt_enable();
पूर्ण
