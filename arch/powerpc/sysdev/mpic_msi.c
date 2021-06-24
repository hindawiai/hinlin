<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2006-2007, Michael Ellerman, IBM Corporation.
 */

#समावेश <linux/irq.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/msi.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/msi_biपंचांगap.h>

#समावेश <sysdev/mpic.h>

व्योम mpic_msi_reserve_hwirq(काष्ठा mpic *mpic, irq_hw_number_t hwirq)
अणु
	/* The mpic calls this even when there is no allocator setup */
	अगर (!mpic->msi_biपंचांगap.biपंचांगap)
		वापस;

	msi_biपंचांगap_reserve_hwirq(&mpic->msi_biपंचांगap, hwirq);
पूर्ण

#अगर_घोषित CONFIG_MPIC_U3_HT_IRQS
अटल पूर्णांक mpic_msi_reserve_u3_hwirqs(काष्ठा mpic *mpic)
अणु
	irq_hw_number_t hwirq;
	स्थिर काष्ठा irq_करोमुख्य_ops *ops = mpic->irqhost->ops;
	काष्ठा device_node *np;
	पूर्णांक flags, index, i;
	काष्ठा of_phandle_args oirq;

	pr_debug("mpic: found U3, guessing msi allocator setup\n");

	/* Reserve source numbers we know are reserved in the HW.
	 *
	 * This is a bit of a mix of U3 and U4 reserves but that's going
	 * to work fine, we have plenty enugh numbers left so let's just
	 * mark anything we करोn't like reserved.
	 */
	क्रम (i = 0;   i < 8;   i++)
		msi_biपंचांगap_reserve_hwirq(&mpic->msi_biपंचांगap, i);

	क्रम (i = 42;  i < 46;  i++)
		msi_biपंचांगap_reserve_hwirq(&mpic->msi_biपंचांगap, i);

	क्रम (i = 100; i < 105; i++)
		msi_biपंचांगap_reserve_hwirq(&mpic->msi_biपंचांगap, i);

	क्रम (i = 124; i < mpic->num_sources; i++)
		msi_biपंचांगap_reserve_hwirq(&mpic->msi_biपंचांगap, i);


	np = शून्य;
	जबतक ((np = of_find_all_nodes(np))) अणु
		pr_debug("mpic: mapping hwirqs for %pOF\n", np);

		index = 0;
		जबतक (of_irq_parse_one(np, index++, &oirq) == 0) अणु
			ops->xlate(mpic->irqhost, शून्य, oirq.args,
						oirq.args_count, &hwirq, &flags);
			msi_biपंचांगap_reserve_hwirq(&mpic->msi_biपंचांगap, hwirq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक mpic_msi_reserve_u3_hwirqs(काष्ठा mpic *mpic)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

पूर्णांक mpic_msi_init_allocator(काष्ठा mpic *mpic)
अणु
	पूर्णांक rc;

	rc = msi_biपंचांगap_alloc(&mpic->msi_biपंचांगap, mpic->num_sources,
			      irq_करोमुख्य_get_of_node(mpic->irqhost));
	अगर (rc)
		वापस rc;

	rc = msi_biपंचांगap_reserve_dt_hwirqs(&mpic->msi_biपंचांगap);
	अगर (rc > 0) अणु
		अगर (mpic->flags & MPIC_U3_HT_IRQS)
			rc = mpic_msi_reserve_u3_hwirqs(mpic);

		अगर (rc) अणु
			msi_biपंचांगap_मुक्त(&mpic->msi_biपंचांगap);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
