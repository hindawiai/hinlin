<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Support क्रम the पूर्णांकerrupt controllers found on Power Macपूर्णांकosh,
 *  currently Apple's "Grand Central" पूर्णांकerrupt controller in all
 *  it's incarnations. OpenPIC support used on newer machines is
 *  in a separate file
 *
 *  Copyright (C) 1997 Paul Mackerras (paulus@samba.org)
 *  Copyright (C) 2005 Benjamin Herrenschmidt (benh@kernel.crashing.org)
 *                     IBM, Corp.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/xmon.h>

#समावेश "pmac.h"

#अगर_घोषित CONFIG_PPC32
काष्ठा pmac_irq_hw अणु
        अचिन्हित पूर्णांक    event;
        अचिन्हित पूर्णांक    enable;
        अचिन्हित पूर्णांक    ack;
        अचिन्हित पूर्णांक    level;
पूर्ण;

/* Workaround flags क्रम 32bit घातermac machines */
अचिन्हित पूर्णांक of_irq_workarounds;
काष्ठा device_node *of_irq_dflt_pic;

/* Default addresses */
अटल अस्थिर काष्ठा pmac_irq_hw __iomem *pmac_irq_hw[4];

अटल पूर्णांक max_irqs;
अटल पूर्णांक max_real_irqs;

अटल DEFINE_RAW_SPINLOCK(pmac_pic_lock);

/* The max irq number this driver deals with is 128; see max_irqs */
अटल DECLARE_BITMAP(ppc_lost_पूर्णांकerrupts, 128);
अटल DECLARE_BITMAP(ppc_cached_irq_mask, 128);
अटल पूर्णांक pmac_irq_cascade = -1;
अटल काष्ठा irq_करोमुख्य *pmac_pic_host;

अटल व्योम __pmac_retrigger(अचिन्हित पूर्णांक irq_nr)
अणु
	अगर (irq_nr >= max_real_irqs && pmac_irq_cascade > 0) अणु
		__set_bit(irq_nr, ppc_lost_पूर्णांकerrupts);
		irq_nr = pmac_irq_cascade;
		mb();
	पूर्ण
	अगर (!__test_and_set_bit(irq_nr, ppc_lost_पूर्णांकerrupts)) अणु
		atomic_inc(&ppc_n_lost_पूर्णांकerrupts);
		set_dec(1);
	पूर्ण
पूर्ण

अटल व्योम pmac_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
        अचिन्हित दीर्घ bit = 1UL << (src & 0x1f);
        पूर्णांक i = src >> 5;
        अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pmac_pic_lock, flags);
        __clear_bit(src, ppc_cached_irq_mask);
        अगर (__test_and_clear_bit(src, ppc_lost_पूर्णांकerrupts))
                atomic_dec(&ppc_n_lost_पूर्णांकerrupts);
        out_le32(&pmac_irq_hw[i]->enable, ppc_cached_irq_mask[i]);
        out_le32(&pmac_irq_hw[i]->ack, bit);
        करो अणु
                /* make sure ack माला_लो to controller beक्रमe we enable
                   पूर्णांकerrupts */
                mb();
        पूर्ण जबतक((in_le32(&pmac_irq_hw[i]->enable) & bit)
                != (ppc_cached_irq_mask[i] & bit));
	raw_spin_unlock_irqrestore(&pmac_pic_lock, flags);
पूर्ण

अटल व्योम pmac_ack_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
        अचिन्हित दीर्घ bit = 1UL << (src & 0x1f);
        पूर्णांक i = src >> 5;
        अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pmac_pic_lock, flags);
	अगर (__test_and_clear_bit(src, ppc_lost_पूर्णांकerrupts))
                atomic_dec(&ppc_n_lost_पूर्णांकerrupts);
        out_le32(&pmac_irq_hw[i]->ack, bit);
        (व्योम)in_le32(&pmac_irq_hw[i]->ack);
	raw_spin_unlock_irqrestore(&pmac_pic_lock, flags);
पूर्ण

अटल व्योम __pmac_set_irq_mask(अचिन्हित पूर्णांक irq_nr, पूर्णांक nokicklost)
अणु
        अचिन्हित दीर्घ bit = 1UL << (irq_nr & 0x1f);
        पूर्णांक i = irq_nr >> 5;

        अगर ((अचिन्हित)irq_nr >= max_irqs)
                वापस;

        /* enable unmasked पूर्णांकerrupts */
        out_le32(&pmac_irq_hw[i]->enable, ppc_cached_irq_mask[i]);

        करो अणु
                /* make sure mask माला_लो to controller beक्रमe we
                   वापस to user */
                mb();
        पूर्ण जबतक((in_le32(&pmac_irq_hw[i]->enable) & bit)
                != (ppc_cached_irq_mask[i] & bit));

        /*
         * Unक्रमtunately, setting the bit in the enable रेजिस्टर
         * when the device पूर्णांकerrupt is alपढ़ोy on *करोesn't* set
         * the bit in the flag रेजिस्टर or request another पूर्णांकerrupt.
         */
        अगर (bit & ppc_cached_irq_mask[i] & in_le32(&pmac_irq_hw[i]->level))
		__pmac_retrigger(irq_nr);
पूर्ण

/* When an irq माला_लो requested क्रम the first client, अगर it's an
 * edge पूर्णांकerrupt, we clear any previous one on the controller
 */
अटल अचिन्हित पूर्णांक pmac_startup_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);
        अचिन्हित दीर्घ bit = 1UL << (src & 0x1f);
        पूर्णांक i = src >> 5;

	raw_spin_lock_irqsave(&pmac_pic_lock, flags);
	अगर (!irqd_is_level_type(d))
		out_le32(&pmac_irq_hw[i]->ack, bit);
        __set_bit(src, ppc_cached_irq_mask);
        __pmac_set_irq_mask(src, 0);
	raw_spin_unlock_irqrestore(&pmac_pic_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम pmac_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

	raw_spin_lock_irqsave(&pmac_pic_lock, flags);
        __clear_bit(src, ppc_cached_irq_mask);
        __pmac_set_irq_mask(src, 1);
	raw_spin_unlock_irqrestore(&pmac_pic_lock, flags);
पूर्ण

अटल व्योम pmac_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

	raw_spin_lock_irqsave(&pmac_pic_lock, flags);
	__set_bit(src, ppc_cached_irq_mask);
        __pmac_set_irq_mask(src, 0);
	raw_spin_unlock_irqrestore(&pmac_pic_lock, flags);
पूर्ण

अटल पूर्णांक pmac_retrigger(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pmac_pic_lock, flags);
	__pmac_retrigger(irqd_to_hwirq(d));
	raw_spin_unlock_irqrestore(&pmac_pic_lock, flags);
	वापस 1;
पूर्ण

अटल काष्ठा irq_chip pmac_pic = अणु
	.name		= "PMAC-PIC",
	.irq_startup	= pmac_startup_irq,
	.irq_mask	= pmac_mask_irq,
	.irq_ack	= pmac_ack_irq,
	.irq_mask_ack	= pmac_mask_and_ack_irq,
	.irq_unmask	= pmac_unmask_irq,
	.irq_retrigger	= pmac_retrigger,
पूर्ण;

अटल irqवापस_t gatwick_action(पूर्णांक cpl, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक irq, bits;
	पूर्णांक rc = IRQ_NONE;

	raw_spin_lock_irqsave(&pmac_pic_lock, flags);
	क्रम (irq = max_irqs; (irq -= 32) >= max_real_irqs; ) अणु
		पूर्णांक i = irq >> 5;
		bits = in_le32(&pmac_irq_hw[i]->event) | ppc_lost_पूर्णांकerrupts[i];
		bits |= in_le32(&pmac_irq_hw[i]->level);
		bits &= ppc_cached_irq_mask[i];
		अगर (bits == 0)
			जारी;
		irq += __ilog2(bits);
		raw_spin_unlock_irqrestore(&pmac_pic_lock, flags);
		generic_handle_irq(irq);
		raw_spin_lock_irqsave(&pmac_pic_lock, flags);
		rc = IRQ_HANDLED;
	पूर्ण
	raw_spin_unlock_irqrestore(&pmac_pic_lock, flags);
	वापस rc;
पूर्ण

अटल अचिन्हित पूर्णांक pmac_pic_get_irq(व्योम)
अणु
	पूर्णांक irq;
	अचिन्हित दीर्घ bits = 0;
	अचिन्हित दीर्घ flags;

#अगर_घोषित CONFIG_PPC_PMAC32_PSURGE
	/* IPI's are a hack on the घातersurge -- Cort */
	अगर (smp_processor_id() != 0) अणु
		वापस  psurge_secondary_virq;
        पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC32_PSURGE */
	raw_spin_lock_irqsave(&pmac_pic_lock, flags);
	क्रम (irq = max_real_irqs; (irq -= 32) >= 0; ) अणु
		पूर्णांक i = irq >> 5;
		bits = in_le32(&pmac_irq_hw[i]->event) | ppc_lost_पूर्णांकerrupts[i];
		bits |= in_le32(&pmac_irq_hw[i]->level);
		bits &= ppc_cached_irq_mask[i];
		अगर (bits == 0)
			जारी;
		irq += __ilog2(bits);
		अवरोध;
	पूर्ण
	raw_spin_unlock_irqrestore(&pmac_pic_lock, flags);
	अगर (unlikely(irq < 0))
		वापस 0;
	वापस irq_linear_revmap(pmac_pic_host, irq);
पूर्ण

अटल पूर्णांक pmac_pic_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
			       क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	/* We match all, we करोn't always have a node anyway */
	वापस 1;
पूर्ण

अटल पूर्णांक pmac_pic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			     irq_hw_number_t hw)
अणु
	अगर (hw >= max_irqs)
		वापस -EINVAL;

	/* Mark level पूर्णांकerrupts, set delayed disable क्रम edge ones and set
	 * handlers
	 */
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &pmac_pic, handle_level_irq);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pmac_pic_host_ops = अणु
	.match = pmac_pic_host_match,
	.map = pmac_pic_host_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल व्योम __init pmac_pic_probe_oldstyle(व्योम)
अणु
        पूर्णांक i;
        काष्ठा device_node *master = शून्य;
	काष्ठा device_node *slave = शून्य;
	u8 __iomem *addr;
	काष्ठा resource r;

	/* Set our get_irq function */
	ppc_md.get_irq = pmac_pic_get_irq;

	/*
	 * Find the पूर्णांकerrupt controller type & node
	 */

	अगर ((master = of_find_node_by_name(शून्य, "gc")) != शून्य) अणु
		max_irqs = max_real_irqs = 32;
	पूर्ण अन्यथा अगर ((master = of_find_node_by_name(शून्य, "ohare")) != शून्य) अणु
		max_irqs = max_real_irqs = 32;
		/* We might have a second cascaded ohare */
		slave = of_find_node_by_name(शून्य, "pci106b,7");
		अगर (slave)
			max_irqs = 64;
	पूर्ण अन्यथा अगर ((master = of_find_node_by_name(शून्य, "mac-io")) != शून्य) अणु
		max_irqs = max_real_irqs = 64;

		/* We might have a second cascaded heathrow */

		/* Compensate क्रम of_node_put() in of_find_node_by_name() */
		of_node_get(master);
		slave = of_find_node_by_name(master, "mac-io");

		/* Check ordering of master & slave */
		अगर (of_device_is_compatible(master, "gatwick")) अणु
			काष्ठा device_node *पंचांगp;
			BUG_ON(slave == शून्य);
			पंचांगp = master;
			master = slave;
			slave = पंचांगp;
		पूर्ण

		/* We found a slave */
		अगर (slave)
			max_irqs = 128;
	पूर्ण
	BUG_ON(master == शून्य);

	/*
	 * Allocate an irq host
	 */
	pmac_pic_host = irq_करोमुख्य_add_linear(master, max_irqs,
					      &pmac_pic_host_ops, शून्य);
	BUG_ON(pmac_pic_host == शून्य);
	irq_set_शेष_host(pmac_pic_host);

	/* Get addresses of first controller अगर we have a node क्रम it */
	BUG_ON(of_address_to_resource(master, 0, &r));

	/* Map पूर्णांकerrupts of primary controller */
	addr = (u8 __iomem *) ioremap(r.start, 0x40);
	i = 0;
	pmac_irq_hw[i++] = (अस्थिर काष्ठा pmac_irq_hw __iomem *)
		(addr + 0x20);
	अगर (max_real_irqs > 32)
		pmac_irq_hw[i++] = (अस्थिर काष्ठा pmac_irq_hw __iomem *)
			(addr + 0x10);
	of_node_put(master);

	prपूर्णांकk(KERN_INFO "irq: Found primary Apple PIC %pOF for %d irqs\n",
	       master, max_real_irqs);

	/* Map पूर्णांकerrupts of cascaded controller */
	अगर (slave && !of_address_to_resource(slave, 0, &r)) अणु
		addr = (u8 __iomem *)ioremap(r.start, 0x40);
		pmac_irq_hw[i++] = (अस्थिर काष्ठा pmac_irq_hw __iomem *)
			(addr + 0x20);
		अगर (max_irqs > 64)
			pmac_irq_hw[i++] =
				(अस्थिर काष्ठा pmac_irq_hw __iomem *)
				(addr + 0x10);
		pmac_irq_cascade = irq_of_parse_and_map(slave, 0);

		prपूर्णांकk(KERN_INFO "irq: Found slave Apple PIC %pOF for %d irqs"
		       " cascade: %d\n", slave,
		       max_irqs - max_real_irqs, pmac_irq_cascade);
	पूर्ण
	of_node_put(slave);

	/* Disable all पूर्णांकerrupts in all controllers */
	क्रम (i = 0; i * 32 < max_irqs; ++i)
		out_le32(&pmac_irq_hw[i]->enable, 0);

	/* Hookup cascade irq */
	अगर (slave && pmac_irq_cascade) अणु
		अगर (request_irq(pmac_irq_cascade, gatwick_action,
				IRQF_NO_THREAD, "cascade", शून्य))
			pr_err("Failed to register cascade interrupt\n");
	पूर्ण

	prपूर्णांकk(KERN_INFO "irq: System has %d possible interrupts\n", max_irqs);
#अगर_घोषित CONFIG_XMON
	i = irq_create_mapping(शून्य, 20);
	अगर (request_irq(i, xmon_irq, IRQF_NO_THREAD, "NMI - XMON", शून्य))
		pr_err("Failed to register NMI-XMON interrupt\n");
#पूर्ण_अगर
पूर्ण

पूर्णांक of_irq_parse_oldworld(काष्ठा device_node *device, पूर्णांक index,
			काष्ठा of_phandle_args *out_irq)
अणु
	स्थिर u32 *पूर्णांकs = शून्य;
	पूर्णांक पूर्णांकlen;

	/*
	 * Old machines just have a list of पूर्णांकerrupt numbers
	 * and no पूर्णांकerrupt-controller nodes. We also have करोdgy
	 * हालs where the APPL,पूर्णांकerrupts property is completely
	 * missing behind pci-pci bridges and we have to get it
	 * from the parent (the bridge itself, as apple just wired
	 * everything together on these)
	 */
	जबतक (device) अणु
		पूर्णांकs = of_get_property(device, "AAPL,interrupts", &पूर्णांकlen);
		अगर (पूर्णांकs != शून्य)
			अवरोध;
		device = device->parent;
		अगर (!of_node_is_type(device, "pci"))
			अवरोध;
	पूर्ण
	अगर (पूर्णांकs == शून्य)
		वापस -EINVAL;
	पूर्णांकlen /= माप(u32);

	अगर (index >= पूर्णांकlen)
		वापस -EINVAL;

	out_irq->np = शून्य;
	out_irq->args[0] = पूर्णांकs[index];
	out_irq->args_count = 1;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */

अटल व्योम __init pmac_pic_setup_mpic_nmi(काष्ठा mpic *mpic)
अणु
#अगर defined(CONFIG_XMON) && defined(CONFIG_PPC32)
	काष्ठा device_node* pचयन;
	पूर्णांक nmi_irq;

	pचयन = of_find_node_by_name(शून्य, "programmer-switch");
	अगर (pचयन) अणु
		nmi_irq = irq_of_parse_and_map(pचयन, 0);
		अगर (nmi_irq) अणु
			mpic_irq_set_priority(nmi_irq, 9);
			अगर (request_irq(nmi_irq, xmon_irq, IRQF_NO_THREAD,
					"NMI - XMON", शून्य))
				pr_err("Failed to register NMI-XMON interrupt\n");
		पूर्ण
		of_node_put(pचयन);
	पूर्ण
#पूर्ण_अगर	/* defined(CONFIG_XMON) && defined(CONFIG_PPC32) */
पूर्ण

अटल काष्ठा mpic * __init pmac_setup_one_mpic(काष्ठा device_node *np,
						पूर्णांक master)
अणु
	स्थिर अक्षर *name = master ? " MPIC 1   " : " MPIC 2   ";
	काष्ठा mpic *mpic;
	अचिन्हित पूर्णांक flags = master ? 0 : MPIC_SECONDARY;

	pmac_call_feature(PMAC_FTR_ENABLE_MPIC, np, 0, 0);

	अगर (of_get_property(np, "big-endian", शून्य))
		flags |= MPIC_BIG_ENDIAN;

	/* Primary Big Endian means HT पूर्णांकerrupts. This is quite करोdgy
	 * but works until I find a better way
	 */
	अगर (master && (flags & MPIC_BIG_ENDIAN))
		flags |= MPIC_U3_HT_IRQS;

	mpic = mpic_alloc(np, 0, flags, 0, 0, name);
	अगर (mpic == शून्य)
		वापस शून्य;

	mpic_init(mpic);

	वापस mpic;
 पूर्ण

अटल पूर्णांक __init pmac_pic_probe_mpic(व्योम)
अणु
	काष्ठा mpic *mpic1, *mpic2;
	काष्ठा device_node *np, *master = शून्य, *slave = शून्य;

	/* We can have up to 2 MPICs cascaded */
	क्रम_each_node_by_type(np, "open-pic") अणु
		अगर (master == शून्य &&
		    of_get_property(np, "interrupts", शून्य) == शून्य)
			master = of_node_get(np);
		अन्यथा अगर (slave == शून्य)
			slave = of_node_get(np);
		अगर (master && slave) अणु
			of_node_put(np);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check क्रम bogus setups */
	अगर (master == शून्य && slave != शून्य) अणु
		master = slave;
		slave = शून्य;
	पूर्ण

	/* Not found, शेष to good old pmac pic */
	अगर (master == शून्य)
		वापस -ENODEV;

	/* Set master handler */
	ppc_md.get_irq = mpic_get_irq;

	/* Setup master */
	mpic1 = pmac_setup_one_mpic(master, 1);
	BUG_ON(mpic1 == शून्य);

	/* Install NMI अगर any */
	pmac_pic_setup_mpic_nmi(mpic1);

	of_node_put(master);

	/* Set up a cascaded controller, अगर present */
	अगर (slave) अणु
		mpic2 = pmac_setup_one_mpic(slave, 0);
		अगर (mpic2 == शून्य)
			prपूर्णांकk(KERN_ERR "Failed to setup slave MPIC\n");
		of_node_put(slave);
	पूर्ण

	वापस 0;
पूर्ण


व्योम __init pmac_pic_init(व्योम)
अणु
	/* We configure the OF parsing based on our oldworld vs. newworld
	 * platक्रमm type and whether we were booted by BootX.
	 */
#अगर_घोषित CONFIG_PPC32
	अगर (!pmac_newworld)
		of_irq_workarounds |= OF_IMAP_OLDWORLD_MAC;
	अगर (of_get_property(of_chosen, "linux,bootx", शून्य) != शून्य)
		of_irq_workarounds |= OF_IMAP_NO_PHANDLE;

	/* If we करोn't have phandles on a newworld, then try to locate a
	 * शेष पूर्णांकerrupt controller (happens when booting with BootX).
	 * We करो a first match here, hopefully, that only ever happens on
	 * machines with one controller.
	 */
	अगर (pmac_newworld && (of_irq_workarounds & OF_IMAP_NO_PHANDLE)) अणु
		काष्ठा device_node *np;

		क्रम_each_node_with_property(np, "interrupt-controller") अणु
			/* Skip /chosen/पूर्णांकerrupt-controller */
			अगर (of_node_name_eq(np, "chosen"))
				जारी;
			/* It seems like at least one person wants
			 * to use BootX on a machine with an AppleKiwi
			 * controller which happens to pretend to be an
			 * पूर्णांकerrupt controller too. */
			अगर (of_node_name_eq(np, "AppleKiwi"))
				जारी;
			/* I think we found one ! */
			of_irq_dflt_pic = np;
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */

	/* We first try to detect Apple's new Core99 chipset, since mac-io
	 * is quite dअगरferent on those machines and contains an IBM MPIC2.
	 */
	अगर (pmac_pic_probe_mpic() == 0)
		वापस;

#अगर_घोषित CONFIG_PPC32
	pmac_pic_probe_oldstyle();
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_PM) && defined(CONFIG_PPC32)
/*
 * These procedures are used in implementing sleep on the घातerbooks.
 * sleep_save_पूर्णांकrs() saves the states of all पूर्णांकerrupt enables
 * and disables all पूर्णांकerrupts except क्रम the nominated one.
 * sleep_restore_पूर्णांकrs() restores the states of all पूर्णांकerrupt enables.
 */
अचिन्हित दीर्घ sleep_save_mask[2];

/* This used to be passed by the PMU driver but that link got
 * broken with the new driver model. We use this tweak क्रम now...
 * We really want to करो things dअगरferently though...
 */
अटल पूर्णांक pmacpic_find_viaपूर्णांक(व्योम)
अणु
	पूर्णांक viaपूर्णांक = -1;

#अगर_घोषित CONFIG_ADB_PMU
	काष्ठा device_node *np;

	अगर (pmu_get_model() != PMU_OHARE_BASED)
		जाओ not_found;
	np = of_find_node_by_name(शून्य, "via-pmu");
	अगर (np == शून्य)
		जाओ not_found;
	viaपूर्णांक = irq_of_parse_and_map(np, 0);
	of_node_put(np);

not_found:
#पूर्ण_अगर /* CONFIG_ADB_PMU */
	वापस viaपूर्णांक;
पूर्ण

अटल पूर्णांक pmacpic_suspend(व्योम)
अणु
	पूर्णांक viaपूर्णांक = pmacpic_find_viaपूर्णांक();

	sleep_save_mask[0] = ppc_cached_irq_mask[0];
	sleep_save_mask[1] = ppc_cached_irq_mask[1];
	ppc_cached_irq_mask[0] = 0;
	ppc_cached_irq_mask[1] = 0;
	अगर (viaपूर्णांक > 0)
		set_bit(viaपूर्णांक, ppc_cached_irq_mask);
	out_le32(&pmac_irq_hw[0]->enable, ppc_cached_irq_mask[0]);
	अगर (max_real_irqs > 32)
		out_le32(&pmac_irq_hw[1]->enable, ppc_cached_irq_mask[1]);
	(व्योम)in_le32(&pmac_irq_hw[0]->event);
	/* make sure mask माला_लो to controller beक्रमe we वापस to caller */
	mb();
        (व्योम)in_le32(&pmac_irq_hw[0]->enable);

        वापस 0;
पूर्ण

अटल व्योम pmacpic_resume(व्योम)
अणु
	पूर्णांक i;

	out_le32(&pmac_irq_hw[0]->enable, 0);
	अगर (max_real_irqs > 32)
		out_le32(&pmac_irq_hw[1]->enable, 0);
	mb();
	क्रम (i = 0; i < max_real_irqs; ++i)
		अगर (test_bit(i, sleep_save_mask))
			pmac_unmask_irq(irq_get_irq_data(i));
पूर्ण

अटल काष्ठा syscore_ops pmacpic_syscore_ops = अणु
	.suspend	= pmacpic_suspend,
	.resume		= pmacpic_resume,
पूर्ण;

अटल पूर्णांक __init init_pmacpic_syscore(व्योम)
अणु
	अगर (pmac_irq_hw[0])
		रेजिस्टर_syscore_ops(&pmacpic_syscore_ops);
	वापस 0;
पूर्ण

machine_subsys_initcall(घातermac, init_pmacpic_syscore);

#पूर्ण_अगर /* CONFIG_PM && CONFIG_PPC32 */
