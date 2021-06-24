<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Intel IO-APIC support क्रम multi-Pentium hosts.
 *
 *	Copyright (C) 1997, 1998, 1999, 2000, 2009 Ingo Molnar, Hajnalka Szabo
 *
 *	Many thanks to Stig Venaas क्रम trying out countless experimental
 *	patches and reporting/debugging problems patiently!
 *
 *	(c) 1999, Multiple IO-APIC support, developed by
 *	Ken-ichi Yaku <yaku@css1.kbnes.nec.co.jp> and
 *      Hidemi Kishimoto <kisimoto@css1.kbnes.nec.co.jp>,
 *	further tested and cleaned up by Zach Brown <zab@redhat.com>
 *	and Ingo Molnar <mingo@redhat.com>
 *
 *	Fixes
 *	Maciej W. Rozycki	:	Bits क्रम genuine 82489DX APICs;
 *					thanks to Eric Gilmore
 *					and Rolf G. Tews
 *					क्रम testing these extensively
 *	Paul Diefenbaugh	:	Added full ACPI support
 *
 * Historical inक्रमmation which is worth to be preserved:
 *
 * - SiS APIC rmw bug:
 *
 *	We used to have a workaround क्रम a bug in SiS chips which
 *	required to reग_लिखो the index रेजिस्टर क्रम a पढ़ो-modअगरy-ग_लिखो
 *	operation as the chip lost the index inक्रमmation which was
 *	setup क्रम the पढ़ो alपढ़ोy. We cache the data now, so that
 *	workaround has been हटाओd.
 */

#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/compiler.h>
#समावेश <linux/acpi.h>
#समावेश <linux/export.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/jअगरfies.h>	/* समय_after() */
#समावेश <linux/slab.h>
#समावेश <linux/memblock.h>
#समावेश <linux/msi.h>

#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/apic.h>

#घोषणा	क्रम_each_ioapic(idx)		\
	क्रम ((idx) = 0; (idx) < nr_ioapics; (idx)++)
#घोषणा	क्रम_each_ioapic_reverse(idx)	\
	क्रम ((idx) = nr_ioapics - 1; (idx) >= 0; (idx)--)
#घोषणा	क्रम_each_pin(idx, pin)		\
	क्रम ((pin) = 0; (pin) < ioapics[(idx)].nr_रेजिस्टरs; (pin)++)
#घोषणा	क्रम_each_ioapic_pin(idx, pin)	\
	क्रम_each_ioapic((idx))		\
		क्रम_each_pin((idx), (pin))
#घोषणा क्रम_each_irq_pin(entry, head) \
	list_क्रम_each_entry(entry, &head, list)

अटल DEFINE_RAW_SPINLOCK(ioapic_lock);
अटल DEFINE_MUTEX(ioapic_mutex);
अटल अचिन्हित पूर्णांक ioapic_dynirq_base;
अटल पूर्णांक ioapic_initialized;

काष्ठा irq_pin_list अणु
	काष्ठा list_head list;
	पूर्णांक apic, pin;
पूर्ण;

काष्ठा mp_chip_data अणु
	काष्ठा list_head		irq_2_pin;
	काष्ठा IO_APIC_route_entry	entry;
	bool				is_level;
	bool				active_low;
	bool				isa_irq;
	u32 count;
पूर्ण;

काष्ठा mp_ioapic_gsi अणु
	u32 gsi_base;
	u32 gsi_end;
पूर्ण;

अटल काष्ठा ioapic अणु
	/*
	 * # of IRQ routing रेजिस्टरs
	 */
	पूर्णांक nr_रेजिस्टरs;
	/*
	 * Saved state during suspend/resume, or जबतक enabling पूर्णांकr-remap.
	 */
	काष्ठा IO_APIC_route_entry *saved_रेजिस्टरs;
	/* I/O APIC config */
	काष्ठा mpc_ioapic mp_config;
	/* IO APIC gsi routing info */
	काष्ठा mp_ioapic_gsi  gsi_config;
	काष्ठा ioapic_करोमुख्य_cfg irqकरोमुख्य_cfg;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	काष्ठा resource *iomem_res;
पूर्ण ioapics[MAX_IO_APICS];

#घोषणा mpc_ioapic_ver(ioapic_idx)	ioapics[ioapic_idx].mp_config.apicver

पूर्णांक mpc_ioapic_id(पूर्णांक ioapic_idx)
अणु
	वापस ioapics[ioapic_idx].mp_config.apicid;
पूर्ण

अचिन्हित पूर्णांक mpc_ioapic_addr(पूर्णांक ioapic_idx)
अणु
	वापस ioapics[ioapic_idx].mp_config.apicaddr;
पूर्ण

अटल अंतरभूत काष्ठा mp_ioapic_gsi *mp_ioapic_gsi_routing(पूर्णांक ioapic_idx)
अणु
	वापस &ioapics[ioapic_idx].gsi_config;
पूर्ण

अटल अंतरभूत पूर्णांक mp_ioapic_pin_count(पूर्णांक ioapic)
अणु
	काष्ठा mp_ioapic_gsi *gsi_cfg = mp_ioapic_gsi_routing(ioapic);

	वापस gsi_cfg->gsi_end - gsi_cfg->gsi_base + 1;
पूर्ण

अटल अंतरभूत u32 mp_pin_to_gsi(पूर्णांक ioapic, पूर्णांक pin)
अणु
	वापस mp_ioapic_gsi_routing(ioapic)->gsi_base + pin;
पूर्ण

अटल अंतरभूत bool mp_is_legacy_irq(पूर्णांक irq)
अणु
	वापस irq >= 0 && irq < nr_legacy_irqs();
पूर्ण

अटल अंतरभूत काष्ठा irq_करोमुख्य *mp_ioapic_irqकरोमुख्य(पूर्णांक ioapic)
अणु
	वापस ioapics[ioapic].irqकरोमुख्य;
पूर्ण

पूर्णांक nr_ioapics;

/* The one past the highest gsi number used */
u32 gsi_top;

/* MP IRQ source entries */
काष्ठा mpc_पूर्णांकsrc mp_irqs[MAX_IRQ_SOURCES];

/* # of MP IRQ source entries */
पूर्णांक mp_irq_entries;

#अगर_घोषित CONFIG_EISA
पूर्णांक mp_bus_id_to_type[MAX_MP_BUSSES];
#पूर्ण_अगर

DECLARE_BITMAP(mp_bus_not_pci, MAX_MP_BUSSES);

पूर्णांक skip_ioapic_setup;

/**
 * disable_ioapic_support() - disables ioapic support at runसमय
 */
व्योम disable_ioapic_support(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	noioapicquirk = 1;
	noioapicreroute = -1;
#पूर्ण_अगर
	skip_ioapic_setup = 1;
पूर्ण

अटल पूर्णांक __init parse_noapic(अक्षर *str)
अणु
	/* disable IO-APIC */
	disable_ioapic_support();
	वापस 0;
पूर्ण
early_param("noapic", parse_noapic);

/* Will be called in mpparse/ACPI codes क्रम saving IRQ info */
व्योम mp_save_irq(काष्ठा mpc_पूर्णांकsrc *m)
अणु
	पूर्णांक i;

	apic_prपूर्णांकk(APIC_VERBOSE, "Int: type %d, pol %d, trig %d, bus %02x,"
		" IRQ %02x, APIC ID %x, APIC INT %02x\n",
		m->irqtype, m->irqflag & 3, (m->irqflag >> 2) & 3, m->srcbus,
		m->srcbusirq, m->dstapic, m->dstirq);

	क्रम (i = 0; i < mp_irq_entries; i++) अणु
		अगर (!स_भेद(&mp_irqs[i], m, माप(*m)))
			वापस;
	पूर्ण

	स_नकल(&mp_irqs[mp_irq_entries], m, माप(*m));
	अगर (++mp_irq_entries == MAX_IRQ_SOURCES)
		panic("Max # of irq sources exceeded!!\n");
पूर्ण

अटल व्योम alloc_ioapic_saved_रेजिस्टरs(पूर्णांक idx)
अणु
	माप_प्रकार size;

	अगर (ioapics[idx].saved_रेजिस्टरs)
		वापस;

	size = माप(काष्ठा IO_APIC_route_entry) * ioapics[idx].nr_रेजिस्टरs;
	ioapics[idx].saved_रेजिस्टरs = kzalloc(size, GFP_KERNEL);
	अगर (!ioapics[idx].saved_रेजिस्टरs)
		pr_err("IOAPIC %d: suspend/resume impossible!\n", idx);
पूर्ण

अटल व्योम मुक्त_ioapic_saved_रेजिस्टरs(पूर्णांक idx)
अणु
	kमुक्त(ioapics[idx].saved_रेजिस्टरs);
	ioapics[idx].saved_रेजिस्टरs = शून्य;
पूर्ण

पूर्णांक __init arch_early_ioapic_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!nr_legacy_irqs())
		io_apic_irqs = ~0UL;

	क्रम_each_ioapic(i)
		alloc_ioapic_saved_रेजिस्टरs(i);

	वापस 0;
पूर्ण

काष्ठा io_apic अणु
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक unused[3];
	अचिन्हित पूर्णांक data;
	अचिन्हित पूर्णांक unused2[11];
	अचिन्हित पूर्णांक eoi;
पूर्ण;

अटल __attribute_स्थिर__ काष्ठा io_apic __iomem *io_apic_base(पूर्णांक idx)
अणु
	वापस (व्योम __iomem *) __fix_to_virt(FIX_IO_APIC_BASE_0 + idx)
		+ (mpc_ioapic_addr(idx) & ~PAGE_MASK);
पूर्ण

अटल अंतरभूत व्योम io_apic_eoi(अचिन्हित पूर्णांक apic, अचिन्हित पूर्णांक vector)
अणु
	काष्ठा io_apic __iomem *io_apic = io_apic_base(apic);
	ग_लिखोl(vector, &io_apic->eoi);
पूर्ण

अचिन्हित पूर्णांक native_io_apic_पढ़ो(अचिन्हित पूर्णांक apic, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा io_apic __iomem *io_apic = io_apic_base(apic);
	ग_लिखोl(reg, &io_apic->index);
	वापस पढ़ोl(&io_apic->data);
पूर्ण

अटल व्योम io_apic_ग_लिखो(अचिन्हित पूर्णांक apic, अचिन्हित पूर्णांक reg,
			  अचिन्हित पूर्णांक value)
अणु
	काष्ठा io_apic __iomem *io_apic = io_apic_base(apic);

	ग_लिखोl(reg, &io_apic->index);
	ग_लिखोl(value, &io_apic->data);
पूर्ण

अटल काष्ठा IO_APIC_route_entry __ioapic_पढ़ो_entry(पूर्णांक apic, पूर्णांक pin)
अणु
	काष्ठा IO_APIC_route_entry entry;

	entry.w1 = io_apic_पढ़ो(apic, 0x10 + 2 * pin);
	entry.w2 = io_apic_पढ़ो(apic, 0x11 + 2 * pin);

	वापस entry;
पूर्ण

अटल काष्ठा IO_APIC_route_entry ioapic_पढ़ो_entry(पूर्णांक apic, पूर्णांक pin)
अणु
	काष्ठा IO_APIC_route_entry entry;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	entry = __ioapic_पढ़ो_entry(apic, pin);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);

	वापस entry;
पूर्ण

/*
 * When we ग_लिखो a new IO APIC routing entry, we need to ग_लिखो the high
 * word first! If the mask bit in the low word is clear, we will enable
 * the पूर्णांकerrupt, and we need to make sure the entry is fully populated
 * beक्रमe that happens.
 */
अटल व्योम __ioapic_ग_लिखो_entry(पूर्णांक apic, पूर्णांक pin, काष्ठा IO_APIC_route_entry e)
अणु
	io_apic_ग_लिखो(apic, 0x11 + 2*pin, e.w2);
	io_apic_ग_लिखो(apic, 0x10 + 2*pin, e.w1);
पूर्ण

अटल व्योम ioapic_ग_लिखो_entry(पूर्णांक apic, पूर्णांक pin, काष्ठा IO_APIC_route_entry e)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	__ioapic_ग_लिखो_entry(apic, pin, e);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
पूर्ण

/*
 * When we mask an IO APIC routing entry, we need to ग_लिखो the low
 * word first, in order to set the mask bit beक्रमe we change the
 * high bits!
 */
अटल व्योम ioapic_mask_entry(पूर्णांक apic, पूर्णांक pin)
अणु
	काष्ठा IO_APIC_route_entry e = अणु .masked = true पूर्ण;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	io_apic_ग_लिखो(apic, 0x10 + 2*pin, e.w1);
	io_apic_ग_लिखो(apic, 0x11 + 2*pin, e.w2);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
पूर्ण

/*
 * The common हाल is 1:1 IRQ<->pin mappings. Someबार there are
 * shared ISA-space IRQs, so we have to support them. We are super
 * fast in the common हाल, and fast क्रम shared ISA-space IRQs.
 */
अटल पूर्णांक __add_pin_to_irq_node(काष्ठा mp_chip_data *data,
				 पूर्णांक node, पूर्णांक apic, पूर्णांक pin)
अणु
	काष्ठा irq_pin_list *entry;

	/* करोn't allow duplicates */
	क्रम_each_irq_pin(entry, data->irq_2_pin)
		अगर (entry->apic == apic && entry->pin == pin)
			वापस 0;

	entry = kzalloc_node(माप(काष्ठा irq_pin_list), GFP_ATOMIC, node);
	अगर (!entry) अणु
		pr_err("can not alloc irq_pin_list (%d,%d,%d)\n",
		       node, apic, pin);
		वापस -ENOMEM;
	पूर्ण
	entry->apic = apic;
	entry->pin = pin;
	list_add_tail(&entry->list, &data->irq_2_pin);

	वापस 0;
पूर्ण

अटल व्योम __हटाओ_pin_from_irq(काष्ठा mp_chip_data *data, पूर्णांक apic, पूर्णांक pin)
अणु
	काष्ठा irq_pin_list *पंचांगp, *entry;

	list_क्रम_each_entry_safe(entry, पंचांगp, &data->irq_2_pin, list)
		अगर (entry->apic == apic && entry->pin == pin) अणु
			list_del(&entry->list);
			kमुक्त(entry);
			वापस;
		पूर्ण
पूर्ण

अटल व्योम add_pin_to_irq_node(काष्ठा mp_chip_data *data,
				पूर्णांक node, पूर्णांक apic, पूर्णांक pin)
अणु
	अगर (__add_pin_to_irq_node(data, node, apic, pin))
		panic("IO-APIC: failed to add irq-pin. Can not proceed\n");
पूर्ण

/*
 * Reroute an IRQ to a dअगरferent pin.
 */
अटल व्योम __init replace_pin_at_irq_node(काष्ठा mp_chip_data *data, पूर्णांक node,
					   पूर्णांक oldapic, पूर्णांक oldpin,
					   पूर्णांक newapic, पूर्णांक newpin)
अणु
	काष्ठा irq_pin_list *entry;

	क्रम_each_irq_pin(entry, data->irq_2_pin) अणु
		अगर (entry->apic == oldapic && entry->pin == oldpin) अणु
			entry->apic = newapic;
			entry->pin = newpin;
			/* every one is dअगरferent, right? */
			वापस;
		पूर्ण
	पूर्ण

	/* old apic/pin didn't exist, so just add new ones */
	add_pin_to_irq_node(data, node, newapic, newpin);
पूर्ण

अटल व्योम io_apic_modअगरy_irq(काष्ठा mp_chip_data *data, bool masked,
			       व्योम (*final)(काष्ठा irq_pin_list *entry))
अणु
	काष्ठा irq_pin_list *entry;

	data->entry.masked = masked;

	क्रम_each_irq_pin(entry, data->irq_2_pin) अणु
		io_apic_ग_लिखो(entry->apic, 0x10 + 2 * entry->pin, data->entry.w1);
		अगर (final)
			final(entry);
	पूर्ण
पूर्ण

अटल व्योम io_apic_sync(काष्ठा irq_pin_list *entry)
अणु
	/*
	 * Synchronize the IO-APIC and the CPU by करोing
	 * a dummy पढ़ो from the IO-APIC
	 */
	काष्ठा io_apic __iomem *io_apic;

	io_apic = io_apic_base(entry->apic);
	पढ़ोl(&io_apic->data);
पूर्ण

अटल व्योम mask_ioapic_irq(काष्ठा irq_data *irq_data)
अणु
	काष्ठा mp_chip_data *data = irq_data->chip_data;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	io_apic_modअगरy_irq(data, true, &io_apic_sync);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
पूर्ण

अटल व्योम __unmask_ioapic(काष्ठा mp_chip_data *data)
अणु
	io_apic_modअगरy_irq(data, false, शून्य);
पूर्ण

अटल व्योम unmask_ioapic_irq(काष्ठा irq_data *irq_data)
अणु
	काष्ठा mp_chip_data *data = irq_data->chip_data;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	__unmask_ioapic(data);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
पूर्ण

/*
 * IO-APIC versions below 0x20 करोn't support EOI रेजिस्टर.
 * For the record, here is the inक्रमmation about various versions:
 *     0Xh     82489DX
 *     1Xh     I/OAPIC or I/O(x)APIC which are not PCI 2.2 Compliant
 *     2Xh     I/O(x)APIC which is PCI 2.2 Compliant
 *     30h-FFh Reserved
 *
 * Some of the Intel ICH Specs (ICH2 to ICH5) करोcuments the io-apic
 * version as 0x2. This is an error with करोcumentation and these ICH chips
 * use io-apic's of version 0x20.
 *
 * For IO-APIC's with EOI रेजिस्टर, we use that to करो an explicit EOI.
 * Otherwise, we simulate the EOI message manually by changing the trigger
 * mode to edge and then back to level, with RTE being masked during this.
 */
अटल व्योम __eoi_ioapic_pin(पूर्णांक apic, पूर्णांक pin, पूर्णांक vector)
अणु
	अगर (mpc_ioapic_ver(apic) >= 0x20) अणु
		io_apic_eoi(apic, vector);
	पूर्ण अन्यथा अणु
		काष्ठा IO_APIC_route_entry entry, entry1;

		entry = entry1 = __ioapic_पढ़ो_entry(apic, pin);

		/*
		 * Mask the entry and change the trigger mode to edge.
		 */
		entry1.masked = true;
		entry1.is_level = false;

		__ioapic_ग_लिखो_entry(apic, pin, entry1);

		/*
		 * Restore the previous level triggered entry.
		 */
		__ioapic_ग_लिखो_entry(apic, pin, entry);
	पूर्ण
पूर्ण

अटल व्योम eoi_ioapic_pin(पूर्णांक vector, काष्ठा mp_chip_data *data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा irq_pin_list *entry;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	क्रम_each_irq_pin(entry, data->irq_2_pin)
		__eoi_ioapic_pin(entry->apic, entry->pin, vector);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
पूर्ण

अटल व्योम clear_IO_APIC_pin(अचिन्हित पूर्णांक apic, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा IO_APIC_route_entry entry;

	/* Check delivery_mode to be sure we're not clearing an SMI pin */
	entry = ioapic_पढ़ो_entry(apic, pin);
	अगर (entry.delivery_mode == APIC_DELIVERY_MODE_SMI)
		वापस;

	/*
	 * Make sure the entry is masked and re-पढ़ो the contents to check
	 * अगर it is a level triggered pin and अगर the remote-IRR is set.
	 */
	अगर (!entry.masked) अणु
		entry.masked = true;
		ioapic_ग_लिखो_entry(apic, pin, entry);
		entry = ioapic_पढ़ो_entry(apic, pin);
	पूर्ण

	अगर (entry.irr) अणु
		अचिन्हित दीर्घ flags;

		/*
		 * Make sure the trigger mode is set to level. Explicit EOI
		 * करोesn't clear the remote-IRR अगर the trigger mode is not
		 * set to level.
		 */
		अगर (!entry.is_level) अणु
			entry.is_level = true;
			ioapic_ग_लिखो_entry(apic, pin, entry);
		पूर्ण
		raw_spin_lock_irqsave(&ioapic_lock, flags);
		__eoi_ioapic_pin(apic, pin, entry.vector);
		raw_spin_unlock_irqrestore(&ioapic_lock, flags);
	पूर्ण

	/*
	 * Clear the rest of the bits in the IO-APIC RTE except क्रम the mask
	 * bit.
	 */
	ioapic_mask_entry(apic, pin);
	entry = ioapic_पढ़ो_entry(apic, pin);
	अगर (entry.irr)
		pr_err("Unable to reset IRR for apic: %d, pin :%d\n",
		       mpc_ioapic_id(apic), pin);
पूर्ण

व्योम clear_IO_APIC (व्योम)
अणु
	पूर्णांक apic, pin;

	क्रम_each_ioapic_pin(apic, pin)
		clear_IO_APIC_pin(apic, pin);
पूर्ण

#अगर_घोषित CONFIG_X86_32
/*
 * support क्रम broken MP BIOSs, enables hand-redirection of PIRQ0-7 to
 * specअगरic CPU-side IRQs.
 */

#घोषणा MAX_PIRQS 8
अटल पूर्णांक pirq_entries[MAX_PIRQS] = अणु
	[0 ... MAX_PIRQS - 1] = -1
पूर्ण;

अटल पूर्णांक __init ioapic_pirq_setup(अक्षर *str)
अणु
	पूर्णांक i, max;
	पूर्णांक पूर्णांकs[MAX_PIRQS+1];

	get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	apic_prपूर्णांकk(APIC_VERBOSE, KERN_INFO
			"PIRQ redirection, working around broken MP-BIOS.\n");
	max = MAX_PIRQS;
	अगर (पूर्णांकs[0] < MAX_PIRQS)
		max = पूर्णांकs[0];

	क्रम (i = 0; i < max; i++) अणु
		apic_prपूर्णांकk(APIC_VERBOSE, KERN_DEBUG
				"... PIRQ%d -> IRQ %d\n", i, पूर्णांकs[i+1]);
		/*
		 * PIRQs are mapped upside करोwn, usually.
		 */
		pirq_entries[MAX_PIRQS-i-1] = पूर्णांकs[i+1];
	पूर्ण
	वापस 1;
पूर्ण

__setup("pirq=", ioapic_pirq_setup);
#पूर्ण_अगर /* CONFIG_X86_32 */

/*
 * Saves all the IO-APIC RTE's
 */
पूर्णांक save_ioapic_entries(व्योम)
अणु
	पूर्णांक apic, pin;
	पूर्णांक err = 0;

	क्रम_each_ioapic(apic) अणु
		अगर (!ioapics[apic].saved_रेजिस्टरs) अणु
			err = -ENOMEM;
			जारी;
		पूर्ण

		क्रम_each_pin(apic, pin)
			ioapics[apic].saved_रेजिस्टरs[pin] =
				ioapic_पढ़ो_entry(apic, pin);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Mask all IO APIC entries.
 */
व्योम mask_ioapic_entries(व्योम)
अणु
	पूर्णांक apic, pin;

	क्रम_each_ioapic(apic) अणु
		अगर (!ioapics[apic].saved_रेजिस्टरs)
			जारी;

		क्रम_each_pin(apic, pin) अणु
			काष्ठा IO_APIC_route_entry entry;

			entry = ioapics[apic].saved_रेजिस्टरs[pin];
			अगर (!entry.masked) अणु
				entry.masked = true;
				ioapic_ग_लिखो_entry(apic, pin, entry);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Restore IO APIC entries which was saved in the ioapic काष्ठाure.
 */
पूर्णांक restore_ioapic_entries(व्योम)
अणु
	पूर्णांक apic, pin;

	क्रम_each_ioapic(apic) अणु
		अगर (!ioapics[apic].saved_रेजिस्टरs)
			जारी;

		क्रम_each_pin(apic, pin)
			ioapic_ग_लिखो_entry(apic, pin,
					   ioapics[apic].saved_रेजिस्टरs[pin]);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Find the IRQ entry number of a certain pin.
 */
अटल पूर्णांक find_irq_entry(पूर्णांक ioapic_idx, पूर्णांक pin, पूर्णांक type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mp_irq_entries; i++)
		अगर (mp_irqs[i].irqtype == type &&
		    (mp_irqs[i].dstapic == mpc_ioapic_id(ioapic_idx) ||
		     mp_irqs[i].dstapic == MP_APIC_ALL) &&
		    mp_irqs[i].dstirq == pin)
			वापस i;

	वापस -1;
पूर्ण

/*
 * Find the pin to which IRQ[irq] (ISA) is connected
 */
अटल पूर्णांक __init find_isa_irq_pin(पूर्णांक irq, पूर्णांक type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mp_irq_entries; i++) अणु
		पूर्णांक lbus = mp_irqs[i].srcbus;

		अगर (test_bit(lbus, mp_bus_not_pci) &&
		    (mp_irqs[i].irqtype == type) &&
		    (mp_irqs[i].srcbusirq == irq))

			वापस mp_irqs[i].dstirq;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक __init find_isa_irq_apic(पूर्णांक irq, पूर्णांक type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mp_irq_entries; i++) अणु
		पूर्णांक lbus = mp_irqs[i].srcbus;

		अगर (test_bit(lbus, mp_bus_not_pci) &&
		    (mp_irqs[i].irqtype == type) &&
		    (mp_irqs[i].srcbusirq == irq))
			अवरोध;
	पूर्ण

	अगर (i < mp_irq_entries) अणु
		पूर्णांक ioapic_idx;

		क्रम_each_ioapic(ioapic_idx)
			अगर (mpc_ioapic_id(ioapic_idx) == mp_irqs[i].dstapic)
				वापस ioapic_idx;
	पूर्ण

	वापस -1;
पूर्ण

अटल bool irq_active_low(पूर्णांक idx)
अणु
	पूर्णांक bus = mp_irqs[idx].srcbus;

	/*
	 * Determine IRQ line polarity (high active or low active):
	 */
	चयन (mp_irqs[idx].irqflag & MP_IRQPOL_MASK) अणु
	हाल MP_IRQPOL_DEFAULT:
		/*
		 * Conक्रमms to spec, ie. bus-type dependent polarity.  PCI
		 * शेषs to low active. [E]ISA शेषs to high active.
		 */
		वापस !test_bit(bus, mp_bus_not_pci);
	हाल MP_IRQPOL_ACTIVE_HIGH:
		वापस false;
	हाल MP_IRQPOL_RESERVED:
		pr_warn("IOAPIC: Invalid polarity: 2, defaulting to low\n");
		fallthrough;
	हाल MP_IRQPOL_ACTIVE_LOW:
	शेष: /* Poपूर्णांकless शेष required due to करो gcc stupidity */
		वापस true;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_EISA
/*
 * EISA Edge/Level control रेजिस्टर, ELCR
 */
अटल bool EISA_ELCR(अचिन्हित पूर्णांक irq)
अणु
	अगर (irq < nr_legacy_irqs()) अणु
		अचिन्हित पूर्णांक port = 0x4d0 + (irq >> 3);
		वापस (inb(port) >> (irq & 7)) & 1;
	पूर्ण
	apic_prपूर्णांकk(APIC_VERBOSE, KERN_INFO
			"Broken MPtable reports ISA irq %d\n", irq);
	वापस false;
पूर्ण

/*
 * EISA पूर्णांकerrupts are always active high and can be edge or level
 * triggered depending on the ELCR value.  If an पूर्णांकerrupt is listed as
 * EISA conक्रमming in the MP table, that means its trigger type must be
 * पढ़ो in from the ELCR.
 */
अटल bool eisa_irq_is_level(पूर्णांक idx, पूर्णांक bus, bool level)
अणु
	चयन (mp_bus_id_to_type[bus]) अणु
	हाल MP_BUS_PCI:
	हाल MP_BUS_ISA:
		वापस level;
	हाल MP_BUS_EISA:
		वापस EISA_ELCR(mp_irqs[idx].srcbusirq);
	पूर्ण
	pr_warn("IOAPIC: Invalid srcbus: %d defaulting to level\n", bus);
	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक eisa_irq_is_level(पूर्णांक idx, पूर्णांक bus, bool level)
अणु
	वापस level;
पूर्ण
#पूर्ण_अगर

अटल bool irq_is_level(पूर्णांक idx)
अणु
	पूर्णांक bus = mp_irqs[idx].srcbus;
	bool level;

	/*
	 * Determine IRQ trigger mode (edge or level sensitive):
	 */
	चयन (mp_irqs[idx].irqflag & MP_IRQTRIG_MASK) अणु
	हाल MP_IRQTRIG_DEFAULT:
		/*
		 * Conक्रमms to spec, ie. bus-type dependent trigger
		 * mode. PCI शेषs to level, ISA to edge.
		 */
		level = !test_bit(bus, mp_bus_not_pci);
		/* Take EISA पूर्णांकo account */
		वापस eisa_irq_is_level(idx, bus, level);
	हाल MP_IRQTRIG_EDGE:
		वापस false;
	हाल MP_IRQTRIG_RESERVED:
		pr_warn("IOAPIC: Invalid trigger mode 2 defaulting to level\n");
		fallthrough;
	हाल MP_IRQTRIG_LEVEL:
	शेष: /* Poपूर्णांकless शेष required due to करो gcc stupidity */
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक __acpi_get_override_irq(u32 gsi, bool *trigger, bool *polarity)
अणु
	पूर्णांक ioapic, pin, idx;

	अगर (skip_ioapic_setup)
		वापस -1;

	ioapic = mp_find_ioapic(gsi);
	अगर (ioapic < 0)
		वापस -1;

	pin = mp_find_ioapic_pin(ioapic, gsi);
	अगर (pin < 0)
		वापस -1;

	idx = find_irq_entry(ioapic, pin, mp_INT);
	अगर (idx < 0)
		वापस -1;

	*trigger = irq_is_level(idx);
	*polarity = irq_active_low(idx);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
पूर्णांक acpi_get_override_irq(u32 gsi, पूर्णांक *is_level, पूर्णांक *active_low)
अणु
	*is_level = *active_low = 0;
	वापस __acpi_get_override_irq(gsi, (bool *)is_level,
				       (bool *)active_low);
पूर्ण
#पूर्ण_अगर

व्योम ioapic_set_alloc_attr(काष्ठा irq_alloc_info *info, पूर्णांक node,
			   पूर्णांक trigger, पूर्णांक polarity)
अणु
	init_irq_alloc_info(info, शून्य);
	info->type = X86_IRQ_ALLOC_TYPE_IOAPIC;
	info->ioapic.node = node;
	info->ioapic.is_level = trigger;
	info->ioapic.active_low = polarity;
	info->ioapic.valid = 1;
पूर्ण

अटल व्योम ioapic_copy_alloc_attr(काष्ठा irq_alloc_info *dst,
				   काष्ठा irq_alloc_info *src,
				   u32 gsi, पूर्णांक ioapic_idx, पूर्णांक pin)
अणु
	bool level, pol_low;

	copy_irq_alloc_info(dst, src);
	dst->type = X86_IRQ_ALLOC_TYPE_IOAPIC;
	dst->devid = mpc_ioapic_id(ioapic_idx);
	dst->ioapic.pin = pin;
	dst->ioapic.valid = 1;
	अगर (src && src->ioapic.valid) अणु
		dst->ioapic.node = src->ioapic.node;
		dst->ioapic.is_level = src->ioapic.is_level;
		dst->ioapic.active_low = src->ioapic.active_low;
	पूर्ण अन्यथा अणु
		dst->ioapic.node = NUMA_NO_NODE;
		अगर (__acpi_get_override_irq(gsi, &level, &pol_low) >= 0) अणु
			dst->ioapic.is_level = level;
			dst->ioapic.active_low = pol_low;
		पूर्ण अन्यथा अणु
			/*
			 * PCI पूर्णांकerrupts are always active low level
			 * triggered.
			 */
			dst->ioapic.is_level = true;
			dst->ioapic.active_low = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ioapic_alloc_attr_node(काष्ठा irq_alloc_info *info)
अणु
	वापस (info && info->ioapic.valid) ? info->ioapic.node : NUMA_NO_NODE;
पूर्ण

अटल व्योम mp_रेजिस्टर_handler(अचिन्हित पूर्णांक irq, bool level)
अणु
	irq_flow_handler_t hdl;
	bool fasteoi;

	अगर (level) अणु
		irq_set_status_flags(irq, IRQ_LEVEL);
		fasteoi = true;
	पूर्ण अन्यथा अणु
		irq_clear_status_flags(irq, IRQ_LEVEL);
		fasteoi = false;
	पूर्ण

	hdl = fasteoi ? handle_fasteoi_irq : handle_edge_irq;
	__irq_set_handler(irq, hdl, 0, fasteoi ? "fasteoi" : "edge");
पूर्ण

अटल bool mp_check_pin_attr(पूर्णांक irq, काष्ठा irq_alloc_info *info)
अणु
	काष्ठा mp_chip_data *data = irq_get_chip_data(irq);

	/*
	 * setup_IO_APIC_irqs() programs all legacy IRQs with शेष trigger
	 * and polarity attributes. So allow the first user to reprogram the
	 * pin with real trigger and polarity attributes.
	 */
	अगर (irq < nr_legacy_irqs() && data->count == 1) अणु
		अगर (info->ioapic.is_level != data->is_level)
			mp_रेजिस्टर_handler(irq, info->ioapic.is_level);
		data->entry.is_level = data->is_level = info->ioapic.is_level;
		data->entry.active_low = data->active_low = info->ioapic.active_low;
	पूर्ण

	वापस data->is_level == info->ioapic.is_level &&
	       data->active_low == info->ioapic.active_low;
पूर्ण

अटल पूर्णांक alloc_irq_from_करोमुख्य(काष्ठा irq_करोमुख्य *करोमुख्य, पूर्णांक ioapic, u32 gsi,
				 काष्ठा irq_alloc_info *info)
अणु
	bool legacy = false;
	पूर्णांक irq = -1;
	पूर्णांक type = ioapics[ioapic].irqकरोमुख्य_cfg.type;

	चयन (type) अणु
	हाल IOAPIC_DOMAIN_LEGACY:
		/*
		 * Dynamically allocate IRQ number क्रम non-ISA IRQs in the first
		 * 16 GSIs on some weird platक्रमms.
		 */
		अगर (!ioapic_initialized || gsi >= nr_legacy_irqs())
			irq = gsi;
		legacy = mp_is_legacy_irq(irq);
		अवरोध;
	हाल IOAPIC_DOMAIN_STRICT:
		irq = gsi;
		अवरोध;
	हाल IOAPIC_DOMAIN_DYNAMIC:
		अवरोध;
	शेष:
		WARN(1, "ioapic: unknown irqdomain type %d\n", type);
		वापस -1;
	पूर्ण

	वापस __irq_करोमुख्य_alloc_irqs(करोमुख्य, irq, 1,
				       ioapic_alloc_attr_node(info),
				       info, legacy, शून्य);
पूर्ण

/*
 * Need special handling क्रम ISA IRQs because there may be multiple IOAPIC pins
 * sharing the same ISA IRQ number and irqकरोमुख्य only supports 1:1 mapping
 * between IOAPIC pin and IRQ number. A typical IOAPIC has 24 pins, pin 0-15 are
 * used क्रम legacy IRQs and pin 16-23 are used क्रम PCI IRQs (PIRQ A-H).
 * When ACPI is disabled, only legacy IRQ numbers (IRQ0-15) are available, and
 * some BIOSes may use MP Interrupt Source records to override IRQ numbers क्रम
 * PIRQs instead of reprogramming the पूर्णांकerrupt routing logic. Thus there may be
 * multiple pins sharing the same legacy IRQ number when ACPI is disabled.
 */
अटल पूर्णांक alloc_isa_irq_from_करोमुख्य(काष्ठा irq_करोमुख्य *करोमुख्य,
				     पूर्णांक irq, पूर्णांक ioapic, पूर्णांक pin,
				     काष्ठा irq_alloc_info *info)
अणु
	काष्ठा mp_chip_data *data;
	काष्ठा irq_data *irq_data = irq_get_irq_data(irq);
	पूर्णांक node = ioapic_alloc_attr_node(info);

	/*
	 * Legacy ISA IRQ has alपढ़ोy been allocated, just add pin to
	 * the pin list associated with this IRQ and program the IOAPIC
	 * entry. The IOAPIC entry
	 */
	अगर (irq_data && irq_data->parent_data) अणु
		अगर (!mp_check_pin_attr(irq, info))
			वापस -EBUSY;
		अगर (__add_pin_to_irq_node(irq_data->chip_data, node, ioapic,
					  info->ioapic.pin))
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		info->flags |= X86_IRQ_ALLOC_LEGACY;
		irq = __irq_करोमुख्य_alloc_irqs(करोमुख्य, irq, 1, node, info, true,
					      शून्य);
		अगर (irq >= 0) अणु
			irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, irq);
			data = irq_data->chip_data;
			data->isa_irq = true;
		पूर्ण
	पूर्ण

	वापस irq;
पूर्ण

अटल पूर्णांक mp_map_pin_to_irq(u32 gsi, पूर्णांक idx, पूर्णांक ioapic, पूर्णांक pin,
			     अचिन्हित पूर्णांक flags, काष्ठा irq_alloc_info *info)
अणु
	पूर्णांक irq;
	bool legacy = false;
	काष्ठा irq_alloc_info पंचांगp;
	काष्ठा mp_chip_data *data;
	काष्ठा irq_करोमुख्य *करोमुख्य = mp_ioapic_irqकरोमुख्य(ioapic);

	अगर (!करोमुख्य)
		वापस -ENOSYS;

	अगर (idx >= 0 && test_bit(mp_irqs[idx].srcbus, mp_bus_not_pci)) अणु
		irq = mp_irqs[idx].srcbusirq;
		legacy = mp_is_legacy_irq(irq);
		/*
		 * IRQ2 is unusable क्रम historical reasons on प्रणालीs which
		 * have a legacy PIC. See the comment vs. IRQ2 further करोwn.
		 *
		 * If this माला_लो हटाओd at some poपूर्णांक then the related code
		 * in lapic_assign_प्रणाली_vectors() needs to be adjusted as
		 * well.
		 */
		अगर (legacy && irq == PIC_CASCADE_IR)
			वापस -EINVAL;
	पूर्ण

	mutex_lock(&ioapic_mutex);
	अगर (!(flags & IOAPIC_MAP_ALLOC)) अणु
		अगर (!legacy) अणु
			irq = irq_find_mapping(करोमुख्य, pin);
			अगर (irq == 0)
				irq = -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		ioapic_copy_alloc_attr(&पंचांगp, info, gsi, ioapic, pin);
		अगर (legacy)
			irq = alloc_isa_irq_from_करोमुख्य(करोमुख्य, irq,
							ioapic, pin, &पंचांगp);
		अन्यथा अगर ((irq = irq_find_mapping(करोमुख्य, pin)) == 0)
			irq = alloc_irq_from_करोमुख्य(करोमुख्य, ioapic, gsi, &पंचांगp);
		अन्यथा अगर (!mp_check_pin_attr(irq, &पंचांगp))
			irq = -EBUSY;
		अगर (irq >= 0) अणु
			data = irq_get_chip_data(irq);
			data->count++;
		पूर्ण
	पूर्ण
	mutex_unlock(&ioapic_mutex);

	वापस irq;
पूर्ण

अटल पूर्णांक pin_2_irq(पूर्णांक idx, पूर्णांक ioapic, पूर्णांक pin, अचिन्हित पूर्णांक flags)
अणु
	u32 gsi = mp_pin_to_gsi(ioapic, pin);

	/*
	 * Debugging check, we are in big trouble अगर this message pops up!
	 */
	अगर (mp_irqs[idx].dstirq != pin)
		pr_err("broken BIOS or MPTABLE parser, ayiee!!\n");

#अगर_घोषित CONFIG_X86_32
	/*
	 * PCI IRQ command line redirection. Yes, limits are hardcoded.
	 */
	अगर ((pin >= 16) && (pin <= 23)) अणु
		अगर (pirq_entries[pin-16] != -1) अणु
			अगर (!pirq_entries[pin-16]) अणु
				apic_prपूर्णांकk(APIC_VERBOSE, KERN_DEBUG
						"disabling PIRQ%d\n", pin-16);
			पूर्ण अन्यथा अणु
				पूर्णांक irq = pirq_entries[pin-16];
				apic_prपूर्णांकk(APIC_VERBOSE, KERN_DEBUG
						"using PIRQ%d -> IRQ %d\n",
						pin-16, irq);
				वापस irq;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस  mp_map_pin_to_irq(gsi, idx, ioapic, pin, flags, शून्य);
पूर्ण

पूर्णांक mp_map_gsi_to_irq(u32 gsi, अचिन्हित पूर्णांक flags, काष्ठा irq_alloc_info *info)
अणु
	पूर्णांक ioapic, pin, idx;

	ioapic = mp_find_ioapic(gsi);
	अगर (ioapic < 0)
		वापस -ENODEV;

	pin = mp_find_ioapic_pin(ioapic, gsi);
	idx = find_irq_entry(ioapic, pin, mp_INT);
	अगर ((flags & IOAPIC_MAP_CHECK) && idx < 0)
		वापस -ENODEV;

	वापस mp_map_pin_to_irq(gsi, idx, ioapic, pin, flags, info);
पूर्ण

व्योम mp_unmap_irq(पूर्णांक irq)
अणु
	काष्ठा irq_data *irq_data = irq_get_irq_data(irq);
	काष्ठा mp_chip_data *data;

	अगर (!irq_data || !irq_data->करोमुख्य)
		वापस;

	data = irq_data->chip_data;
	अगर (!data || data->isa_irq)
		वापस;

	mutex_lock(&ioapic_mutex);
	अगर (--data->count == 0)
		irq_करोमुख्य_मुक्त_irqs(irq, 1);
	mutex_unlock(&ioapic_mutex);
पूर्ण

/*
 * Find a specअगरic PCI IRQ entry.
 * Not an __init, possibly needed by modules
 */
पूर्णांक IO_APIC_get_PCI_irq_vector(पूर्णांक bus, पूर्णांक slot, पूर्णांक pin)
अणु
	पूर्णांक irq, i, best_ioapic = -1, best_idx = -1;

	apic_prपूर्णांकk(APIC_DEBUG,
		    "querying PCI -> IRQ mapping bus:%d, slot:%d, pin:%d.\n",
		    bus, slot, pin);
	अगर (test_bit(bus, mp_bus_not_pci)) अणु
		apic_prपूर्णांकk(APIC_VERBOSE,
			    "PCI BIOS passed nonexistent PCI bus %d!\n", bus);
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < mp_irq_entries; i++) अणु
		पूर्णांक lbus = mp_irqs[i].srcbus;
		पूर्णांक ioapic_idx, found = 0;

		अगर (bus != lbus || mp_irqs[i].irqtype != mp_INT ||
		    slot != ((mp_irqs[i].srcbusirq >> 2) & 0x1f))
			जारी;

		क्रम_each_ioapic(ioapic_idx)
			अगर (mpc_ioapic_id(ioapic_idx) == mp_irqs[i].dstapic ||
			    mp_irqs[i].dstapic == MP_APIC_ALL) अणु
				found = 1;
				अवरोध;
			पूर्ण
		अगर (!found)
			जारी;

		/* Skip ISA IRQs */
		irq = pin_2_irq(i, ioapic_idx, mp_irqs[i].dstirq, 0);
		अगर (irq > 0 && !IO_APIC_IRQ(irq))
			जारी;

		अगर (pin == (mp_irqs[i].srcbusirq & 3)) अणु
			best_idx = i;
			best_ioapic = ioapic_idx;
			जाओ out;
		पूर्ण

		/*
		 * Use the first all-but-pin matching entry as a
		 * best-guess fuzzy result क्रम broken mptables.
		 */
		अगर (best_idx < 0) अणु
			best_idx = i;
			best_ioapic = ioapic_idx;
		पूर्ण
	पूर्ण
	अगर (best_idx < 0)
		वापस -1;

out:
	वापस pin_2_irq(best_idx, best_ioapic, mp_irqs[best_idx].dstirq,
			 IOAPIC_MAP_ALLOC);
पूर्ण
EXPORT_SYMBOL(IO_APIC_get_PCI_irq_vector);

अटल काष्ठा irq_chip ioapic_chip, ioapic_ir_chip;

अटल व्योम __init setup_IO_APIC_irqs(व्योम)
अणु
	अचिन्हित पूर्णांक ioapic, pin;
	पूर्णांक idx;

	apic_prपूर्णांकk(APIC_VERBOSE, KERN_DEBUG "init IO_APIC IRQs\n");

	क्रम_each_ioapic_pin(ioapic, pin) अणु
		idx = find_irq_entry(ioapic, pin, mp_INT);
		अगर (idx < 0)
			apic_prपूर्णांकk(APIC_VERBOSE,
				    KERN_DEBUG " apic %d pin %d not connected\n",
				    mpc_ioapic_id(ioapic), pin);
		अन्यथा
			pin_2_irq(idx, ioapic, pin,
				  ioapic ? 0 : IOAPIC_MAP_ALLOC);
	पूर्ण
पूर्ण

व्योम ioapic_zap_locks(व्योम)
अणु
	raw_spin_lock_init(&ioapic_lock);
पूर्ण

अटल व्योम io_apic_prपूर्णांक_entries(अचिन्हित पूर्णांक apic, अचिन्हित पूर्णांक nr_entries)
अणु
	काष्ठा IO_APIC_route_entry entry;
	अक्षर buf[256];
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "IOAPIC %d:\n", apic);
	क्रम (i = 0; i <= nr_entries; i++) अणु
		entry = ioapic_पढ़ो_entry(apic, i);
		snम_लिखो(buf, माप(buf),
			 " pin%02x, %s, %s, %s, V(%02X), IRR(%1d), S(%1d)",
			 i,
			 entry.masked ? "disabled" : "enabled ",
			 entry.is_level ? "level" : "edge ",
			 entry.active_low ? "low " : "high",
			 entry.vector, entry.irr, entry.delivery_status);
		अगर (entry.ir_क्रमmat) अणु
			prपूर्णांकk(KERN_DEBUG "%s, remapped, I(%04X),  Z(%X)\n",
			       buf,
			       (entry.ir_index_15 << 15) | entry.ir_index_0_14,
				entry.ir_zero);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG "%s, %s, D(%02X%02X), M(%1d)\n", buf,
			       entry.dest_mode_logical ? "logical " : "physical",
			       entry.virt_destid_8_14, entry.destid_0_7,
			       entry.delivery_mode);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init prपूर्णांक_IO_APIC(पूर्णांक ioapic_idx)
अणु
	जोड़ IO_APIC_reg_00 reg_00;
	जोड़ IO_APIC_reg_01 reg_01;
	जोड़ IO_APIC_reg_02 reg_02;
	जोड़ IO_APIC_reg_03 reg_03;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	reg_00.raw = io_apic_पढ़ो(ioapic_idx, 0);
	reg_01.raw = io_apic_पढ़ो(ioapic_idx, 1);
	अगर (reg_01.bits.version >= 0x10)
		reg_02.raw = io_apic_पढ़ो(ioapic_idx, 2);
	अगर (reg_01.bits.version >= 0x20)
		reg_03.raw = io_apic_पढ़ो(ioapic_idx, 3);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);

	prपूर्णांकk(KERN_DEBUG "IO APIC #%d......\n", mpc_ioapic_id(ioapic_idx));
	prपूर्णांकk(KERN_DEBUG ".... register #00: %08X\n", reg_00.raw);
	prपूर्णांकk(KERN_DEBUG ".......    : physical APIC id: %02X\n", reg_00.bits.ID);
	prपूर्णांकk(KERN_DEBUG ".......    : Delivery Type: %X\n", reg_00.bits.delivery_type);
	prपूर्णांकk(KERN_DEBUG ".......    : LTS          : %X\n", reg_00.bits.LTS);

	prपूर्णांकk(KERN_DEBUG ".... register #01: %08X\n", *(पूर्णांक *)&reg_01);
	prपूर्णांकk(KERN_DEBUG ".......     : max redirection entries: %02X\n",
		reg_01.bits.entries);

	prपूर्णांकk(KERN_DEBUG ".......     : PRQ implemented: %X\n", reg_01.bits.PRQ);
	prपूर्णांकk(KERN_DEBUG ".......     : IO APIC version: %02X\n",
		reg_01.bits.version);

	/*
	 * Some Intel chipsets with IO APIC VERSION of 0x1? करोn't have reg_02,
	 * but the value of reg_02 is पढ़ो as the previous पढ़ो रेजिस्टर
	 * value, so ignore it अगर reg_02 == reg_01.
	 */
	अगर (reg_01.bits.version >= 0x10 && reg_02.raw != reg_01.raw) अणु
		prपूर्णांकk(KERN_DEBUG ".... register #02: %08X\n", reg_02.raw);
		prपूर्णांकk(KERN_DEBUG ".......     : arbitration: %02X\n", reg_02.bits.arbitration);
	पूर्ण

	/*
	 * Some Intel chipsets with IO APIC VERSION of 0x2? करोn't have reg_02
	 * or reg_03, but the value of reg_0[23] is पढ़ो as the previous पढ़ो
	 * रेजिस्टर value, so ignore it अगर reg_03 == reg_0[12].
	 */
	अगर (reg_01.bits.version >= 0x20 && reg_03.raw != reg_02.raw &&
	    reg_03.raw != reg_01.raw) अणु
		prपूर्णांकk(KERN_DEBUG ".... register #03: %08X\n", reg_03.raw);
		prपूर्णांकk(KERN_DEBUG ".......     : Boot DT    : %X\n", reg_03.bits.boot_DT);
	पूर्ण

	prपूर्णांकk(KERN_DEBUG ".... IRQ redirection table:\n");
	io_apic_prपूर्णांक_entries(ioapic_idx, reg_01.bits.entries);
पूर्ण

व्योम __init prपूर्णांक_IO_APICs(व्योम)
अणु
	पूर्णांक ioapic_idx;
	अचिन्हित पूर्णांक irq;

	prपूर्णांकk(KERN_DEBUG "number of MP IRQ sources: %d.\n", mp_irq_entries);
	क्रम_each_ioapic(ioapic_idx)
		prपूर्णांकk(KERN_DEBUG "number of IO-APIC #%d registers: %d.\n",
		       mpc_ioapic_id(ioapic_idx),
		       ioapics[ioapic_idx].nr_रेजिस्टरs);

	/*
	 * We are a bit conservative about what we expect.  We have to
	 * know about every hardware change ASAP.
	 */
	prपूर्णांकk(KERN_INFO "testing the IO APIC.......................\n");

	क्रम_each_ioapic(ioapic_idx)
		prपूर्णांक_IO_APIC(ioapic_idx);

	prपूर्णांकk(KERN_DEBUG "IRQ to pin mappings:\n");
	क्रम_each_active_irq(irq) अणु
		काष्ठा irq_pin_list *entry;
		काष्ठा irq_chip *chip;
		काष्ठा mp_chip_data *data;

		chip = irq_get_chip(irq);
		अगर (chip != &ioapic_chip && chip != &ioapic_ir_chip)
			जारी;
		data = irq_get_chip_data(irq);
		अगर (!data)
			जारी;
		अगर (list_empty(&data->irq_2_pin))
			जारी;

		prपूर्णांकk(KERN_DEBUG "IRQ%d ", irq);
		क्रम_each_irq_pin(entry, data->irq_2_pin)
			pr_cont("-> %d:%d", entry->apic, entry->pin);
		pr_cont("\n");
	पूर्ण

	prपूर्णांकk(KERN_INFO ".................................... done.\n");
पूर्ण

/* Where अगर anywhere is the i8259 connect in बाह्यal पूर्णांक mode */
अटल काष्ठा अणु पूर्णांक pin, apic; पूर्ण ioapic_i8259 = अणु -1, -1 पूर्ण;

व्योम __init enable_IO_APIC(व्योम)
अणु
	पूर्णांक i8259_apic, i8259_pin;
	पूर्णांक apic, pin;

	अगर (skip_ioapic_setup)
		nr_ioapics = 0;

	अगर (!nr_legacy_irqs() || !nr_ioapics)
		वापस;

	क्रम_each_ioapic_pin(apic, pin) अणु
		/* See अगर any of the pins is in ExtINT mode */
		काष्ठा IO_APIC_route_entry entry = ioapic_पढ़ो_entry(apic, pin);

		/* If the पूर्णांकerrupt line is enabled and in ExtInt mode
		 * I have found the pin where the i8259 is connected.
		 */
		अगर (!entry.masked &&
		    entry.delivery_mode == APIC_DELIVERY_MODE_EXTINT) अणु
			ioapic_i8259.apic = apic;
			ioapic_i8259.pin  = pin;
			जाओ found_i8259;
		पूर्ण
	पूर्ण
 found_i8259:
	/* Look to see what अगर the MP table has reported the ExtINT */
	/* If we could not find the appropriate pin by looking at the ioapic
	 * the i8259 probably is not connected the ioapic but give the
	 * mptable a chance anyway.
	 */
	i8259_pin  = find_isa_irq_pin(0, mp_ExtINT);
	i8259_apic = find_isa_irq_apic(0, mp_ExtINT);
	/* Trust the MP table अगर nothing is setup in the hardware */
	अगर ((ioapic_i8259.pin == -1) && (i8259_pin >= 0)) अणु
		prपूर्णांकk(KERN_WARNING "ExtINT not setup in hardware but reported by MP table\n");
		ioapic_i8259.pin  = i8259_pin;
		ioapic_i8259.apic = i8259_apic;
	पूर्ण
	/* Complain अगर the MP table and the hardware disagree */
	अगर (((ioapic_i8259.apic != i8259_apic) || (ioapic_i8259.pin != i8259_pin)) &&
		(i8259_pin >= 0) && (ioapic_i8259.pin >= 0))
	अणु
		prपूर्णांकk(KERN_WARNING "ExtINT in hardware and MP table differ\n");
	पूर्ण

	/*
	 * Do not trust the IO-APIC being empty at bootup
	 */
	clear_IO_APIC();
पूर्ण

व्योम native_restore_boot_irq_mode(व्योम)
अणु
	/*
	 * If the i8259 is routed through an IOAPIC
	 * Put that IOAPIC in भव wire mode
	 * so legacy पूर्णांकerrupts can be delivered.
	 */
	अगर (ioapic_i8259.pin != -1) अणु
		काष्ठा IO_APIC_route_entry entry;
		u32 apic_id = पढ़ो_apic_id();

		स_रखो(&entry, 0, माप(entry));
		entry.masked		= false;
		entry.is_level		= false;
		entry.active_low	= false;
		entry.dest_mode_logical	= false;
		entry.delivery_mode	= APIC_DELIVERY_MODE_EXTINT;
		entry.destid_0_7	= apic_id & 0xFF;
		entry.virt_destid_8_14	= apic_id >> 8;

		/*
		 * Add it to the IO-APIC irq-routing table:
		 */
		ioapic_ग_लिखो_entry(ioapic_i8259.apic, ioapic_i8259.pin, entry);
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_APIC) || apic_from_smp_config())
		disconnect_bsp_APIC(ioapic_i8259.pin != -1);
पूर्ण

व्योम restore_boot_irq_mode(व्योम)
अणु
	अगर (!nr_legacy_irqs())
		वापस;

	x86_apic_ops.restore();
पूर्ण

#अगर_घोषित CONFIG_X86_32
/*
 * function to set the IO-APIC physical IDs based on the
 * values stored in the MPC table.
 *
 * by Matt Domsch <Matt_Domsch@dell.com>  Tue Dec 21 12:25:05 CST 1999
 */
व्योम __init setup_ioapic_ids_from_mpc_nocheck(व्योम)
अणु
	जोड़ IO_APIC_reg_00 reg_00;
	physid_mask_t phys_id_present_map;
	पूर्णांक ioapic_idx;
	पूर्णांक i;
	अचिन्हित अक्षर old_id;
	अचिन्हित दीर्घ flags;

	/*
	 * This is broken; anything with a real cpu count has to
	 * circumvent this idiocy regardless.
	 */
	apic->ioapic_phys_id_map(&phys_cpu_present_map, &phys_id_present_map);

	/*
	 * Set the IOAPIC ID to the value stored in the MPC table.
	 */
	क्रम_each_ioapic(ioapic_idx) अणु
		/* Read the रेजिस्टर 0 value */
		raw_spin_lock_irqsave(&ioapic_lock, flags);
		reg_00.raw = io_apic_पढ़ो(ioapic_idx, 0);
		raw_spin_unlock_irqrestore(&ioapic_lock, flags);

		old_id = mpc_ioapic_id(ioapic_idx);

		अगर (mpc_ioapic_id(ioapic_idx) >= get_physical_broadcast()) अणु
			prपूर्णांकk(KERN_ERR "BIOS bug, IO-APIC#%d ID is %d in the MPC table!...\n",
				ioapic_idx, mpc_ioapic_id(ioapic_idx));
			prपूर्णांकk(KERN_ERR "... fixing up to %d. (tell your hw vendor)\n",
				reg_00.bits.ID);
			ioapics[ioapic_idx].mp_config.apicid = reg_00.bits.ID;
		पूर्ण

		/*
		 * Sanity check, is the ID really मुक्त? Every APIC in a
		 * प्रणाली must have a unique ID or we get lots of nice
		 * 'stuck on smp_invalidate_needed IPI wait' messages.
		 */
		अगर (apic->check_apicid_used(&phys_id_present_map,
					    mpc_ioapic_id(ioapic_idx))) अणु
			prपूर्णांकk(KERN_ERR "BIOS bug, IO-APIC#%d ID %d is already used!...\n",
				ioapic_idx, mpc_ioapic_id(ioapic_idx));
			क्रम (i = 0; i < get_physical_broadcast(); i++)
				अगर (!physid_isset(i, phys_id_present_map))
					अवरोध;
			अगर (i >= get_physical_broadcast())
				panic("Max APIC ID exceeded!\n");
			prपूर्णांकk(KERN_ERR "... fixing up to %d. (tell your hw vendor)\n",
				i);
			physid_set(i, phys_id_present_map);
			ioapics[ioapic_idx].mp_config.apicid = i;
		पूर्ण अन्यथा अणु
			physid_mask_t पंचांगp;
			apic->apicid_to_cpu_present(mpc_ioapic_id(ioapic_idx),
						    &पंचांगp);
			apic_prपूर्णांकk(APIC_VERBOSE, "Setting %d in the "
					"phys_id_present_map\n",
					mpc_ioapic_id(ioapic_idx));
			physids_or(phys_id_present_map, phys_id_present_map, पंचांगp);
		पूर्ण

		/*
		 * We need to adjust the IRQ routing table
		 * अगर the ID changed.
		 */
		अगर (old_id != mpc_ioapic_id(ioapic_idx))
			क्रम (i = 0; i < mp_irq_entries; i++)
				अगर (mp_irqs[i].dstapic == old_id)
					mp_irqs[i].dstapic
						= mpc_ioapic_id(ioapic_idx);

		/*
		 * Update the ID रेजिस्टर according to the right value
		 * from the MPC table अगर they are dअगरferent.
		 */
		अगर (mpc_ioapic_id(ioapic_idx) == reg_00.bits.ID)
			जारी;

		apic_prपूर्णांकk(APIC_VERBOSE, KERN_INFO
			"...changing IO-APIC physical APIC ID to %d ...",
			mpc_ioapic_id(ioapic_idx));

		reg_00.bits.ID = mpc_ioapic_id(ioapic_idx);
		raw_spin_lock_irqsave(&ioapic_lock, flags);
		io_apic_ग_लिखो(ioapic_idx, 0, reg_00.raw);
		raw_spin_unlock_irqrestore(&ioapic_lock, flags);

		/*
		 * Sanity check
		 */
		raw_spin_lock_irqsave(&ioapic_lock, flags);
		reg_00.raw = io_apic_पढ़ो(ioapic_idx, 0);
		raw_spin_unlock_irqrestore(&ioapic_lock, flags);
		अगर (reg_00.bits.ID != mpc_ioapic_id(ioapic_idx))
			pr_cont("could not set ID!\n");
		अन्यथा
			apic_prपूर्णांकk(APIC_VERBOSE, " ok.\n");
	पूर्ण
पूर्ण

व्योम __init setup_ioapic_ids_from_mpc(व्योम)
अणु

	अगर (acpi_ioapic)
		वापस;
	/*
	 * Don't check I/O APIC IDs क्रम xAPIC प्रणालीs.  They have
	 * no meaning without the serial APIC bus.
	 */
	अगर (!(boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL)
		|| APIC_XAPIC(boot_cpu_apic_version))
		वापस;
	setup_ioapic_ids_from_mpc_nocheck();
पूर्ण
#पूर्ण_अगर

पूर्णांक no_समयr_check __initdata;

अटल पूर्णांक __init noसमयrcheck(अक्षर *s)
अणु
	no_समयr_check = 1;
	वापस 1;
पूर्ण
__setup("no_timer_check", noसमयrcheck);

अटल व्योम __init delay_with_tsc(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ start, now;
	अचिन्हित दीर्घ end = jअगरfies + 4;

	start = rdtsc();

	/*
	 * We करोn't know the TSC frequency yet, but रुकोing क्रम
	 * 40000000000/HZ TSC cycles is safe:
	 * 4 GHz == 10 jअगरfies
	 * 1 GHz == 40 jअगरfies
	 */
	करो अणु
		rep_nop();
		now = rdtsc();
	पूर्ण जबतक ((now - start) < 40000000000ULL / HZ &&
		समय_beक्रमe_eq(jअगरfies, end));
पूर्ण

अटल व्योम __init delay_without_tsc(व्योम)
अणु
	अचिन्हित दीर्घ end = jअगरfies + 4;
	पूर्णांक band = 1;

	/*
	 * We करोn't know any frequency yet, but रुकोing क्रम
	 * 40940000000/HZ cycles is safe:
	 * 4 GHz == 10 jअगरfies
	 * 1 GHz == 40 jअगरfies
	 * 1 << 1 + 1 << 2 +...+ 1 << 11 = 4094
	 */
	करो अणु
		__delay(((1U << band++) * 10000000UL) / HZ);
	पूर्ण जबतक (band < 12 && समय_beक्रमe_eq(jअगरfies, end));
पूर्ण

/*
 * There is a nasty bug in some older SMP boards, their mptable lies
 * about the समयr IRQ. We करो the following to work around the situation:
 *
 *	- समयr IRQ शेषs to IO-APIC IRQ
 *	- अगर this function detects that समयr IRQs are defunct, then we fall
 *	  back to ISA समयr IRQs
 */
अटल पूर्णांक __init समयr_irq_works(व्योम)
अणु
	अचिन्हित दीर्घ t1 = jअगरfies;

	अगर (no_समयr_check)
		वापस 1;

	local_irq_enable();
	अगर (boot_cpu_has(X86_FEATURE_TSC))
		delay_with_tsc();
	अन्यथा
		delay_without_tsc();

	/*
	 * Expect a few ticks at least, to be sure some possible
	 * glue logic करोes not lock up after one or two first
	 * ticks in a non-ExtINT mode.  Also the local APIC
	 * might have cached one ExtINT पूर्णांकerrupt.  Finally, at
	 * least one tick may be lost due to delays.
	 */

	local_irq_disable();

	/* Did jअगरfies advance? */
	वापस समय_after(jअगरfies, t1 + 4);
पूर्ण

/*
 * In the SMP+IOAPIC हाल it might happen that there are an unspecअगरied
 * number of pending IRQ events unhandled. These हालs are very rare,
 * so we 'resend' these IRQs via IPIs, to the same CPU. It's much
 * better to करो it this way as thus we करो not have to be aware of
 * 'pending' पूर्णांकerrupts in the IRQ path, except at this poपूर्णांक.
 */
/*
 * Edge triggered needs to resend any पूर्णांकerrupt
 * that was delayed but this is now handled in the device
 * independent code.
 */

/*
 * Starting up a edge-triggered IO-APIC पूर्णांकerrupt is
 * nasty - we need to make sure that we get the edge.
 * If it is alपढ़ोy निश्चितed क्रम some reason, we need
 * वापस 1 to indicate that is was pending.
 *
 * This is not complete - we should be able to fake
 * an edge even अगर it isn't on the 8259A...
 */
अटल अचिन्हित पूर्णांक startup_ioapic_irq(काष्ठा irq_data *data)
अणु
	पूर्णांक was_pending = 0, irq = data->irq;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	अगर (irq < nr_legacy_irqs()) अणु
		legacy_pic->mask(irq);
		अगर (legacy_pic->irq_pending(irq))
			was_pending = 1;
	पूर्ण
	__unmask_ioapic(data->chip_data);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);

	वापस was_pending;
पूर्ण

atomic_t irq_mis_count;

#अगर_घोषित CONFIG_GENERIC_PENDING_IRQ
अटल bool io_apic_level_ack_pending(काष्ठा mp_chip_data *data)
अणु
	काष्ठा irq_pin_list *entry;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	क्रम_each_irq_pin(entry, data->irq_2_pin) अणु
		काष्ठा IO_APIC_route_entry e;
		पूर्णांक pin;

		pin = entry->pin;
		e.w1 = io_apic_पढ़ो(entry->apic, 0x10 + pin*2);
		/* Is the remote IRR bit set? */
		अगर (e.irr) अणु
			raw_spin_unlock_irqrestore(&ioapic_lock, flags);
			वापस true;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);

	वापस false;
पूर्ण

अटल अंतरभूत bool ioapic_prepare_move(काष्ठा irq_data *data)
अणु
	/* If we are moving the IRQ we need to mask it */
	अगर (unlikely(irqd_is_setaffinity_pending(data))) अणु
		अगर (!irqd_irq_masked(data))
			mask_ioapic_irq(data);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम ioapic_finish_move(काष्ठा irq_data *data, bool moveit)
अणु
	अगर (unlikely(moveit)) अणु
		/* Only migrate the irq अगर the ack has been received.
		 *
		 * On rare occasions the broadcast level triggered ack माला_लो
		 * delayed going to ioapics, and अगर we reprogram the
		 * vector जबतक Remote IRR is still set the irq will never
		 * fire again.
		 *
		 * To prevent this scenario we पढ़ो the Remote IRR bit
		 * of the ioapic.  This has two effects.
		 * - On any sane प्रणाली the पढ़ो of the ioapic will
		 *   flush ग_लिखोs (and acks) going to the ioapic from
		 *   this cpu.
		 * - We get to see अगर the ACK has actually been delivered.
		 *
		 * Based on failed experiments of reprogramming the
		 * ioapic entry from outside of irq context starting
		 * with masking the ioapic entry and then polling until
		 * Remote IRR was clear beक्रमe reprogramming the
		 * ioapic I करोn't trust the Remote IRR bit to be
		 * completely accurate.
		 *
		 * However there appears to be no other way to plug
		 * this race, so अगर the Remote IRR bit is not
		 * accurate and is causing problems then it is a hardware bug
		 * and you can go talk to the chipset venकरोr about it.
		 */
		अगर (!io_apic_level_ack_pending(data->chip_data))
			irq_move_masked_irq(data);
		/* If the IRQ is masked in the core, leave it: */
		अगर (!irqd_irq_masked(data))
			unmask_ioapic_irq(data);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत bool ioapic_prepare_move(काष्ठा irq_data *data)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम ioapic_finish_move(काष्ठा irq_data *data, bool moveit)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम ioapic_ack_level(काष्ठा irq_data *irq_data)
अणु
	काष्ठा irq_cfg *cfg = irqd_cfg(irq_data);
	अचिन्हित दीर्घ v;
	bool moveit;
	पूर्णांक i;

	irq_complete_move(cfg);
	moveit = ioapic_prepare_move(irq_data);

	/*
	 * It appears there is an erratum which affects at least version 0x11
	 * of I/O APIC (that's the 82093AA and cores पूर्णांकegrated पूर्णांकo various
	 * chipsets).  Under certain conditions a level-triggered पूर्णांकerrupt is
	 * erroneously delivered as edge-triggered one but the respective IRR
	 * bit माला_लो set nevertheless.  As a result the I/O unit expects an EOI
	 * message but it will never arrive and further पूर्णांकerrupts are blocked
	 * from the source.  The exact reason is so far unknown, but the
	 * phenomenon was observed when two consecutive पूर्णांकerrupt requests
	 * from a given source get delivered to the same CPU and the source is
	 * temporarily disabled in between.
	 *
	 * A workaround is to simulate an EOI message manually.  We achieve it
	 * by setting the trigger mode to edge and then to level when the edge
	 * trigger mode माला_लो detected in the TMR of a local APIC क्रम a
	 * level-triggered पूर्णांकerrupt.  We mask the source क्रम the समय of the
	 * operation to prevent an edge-triggered पूर्णांकerrupt escaping meanजबतक.
	 * The idea is from Manfred Spraul.  --macro
	 *
	 * Also in the हाल when cpu goes offline, fixup_irqs() will क्रमward
	 * any unhandled पूर्णांकerrupt on the offlined cpu to the new cpu
	 * destination that is handling the corresponding पूर्णांकerrupt. This
	 * पूर्णांकerrupt क्रमwarding is करोne via IPI's. Hence, in this हाल also
	 * level-triggered io-apic पूर्णांकerrupt will be seen as an edge
	 * पूर्णांकerrupt in the IRR. And we can't rely on the cpu's EOI
	 * to be broadcasted to the IO-APIC's which will clear the remoteIRR
	 * corresponding to the level-triggered पूर्णांकerrupt. Hence on IO-APIC's
	 * supporting EOI रेजिस्टर, we करो an explicit EOI to clear the
	 * remote IRR and on IO-APIC's which don't have an EOI रेजिस्टर,
	 * we use the above logic (mask+edge followed by unmask+level) from
	 * Manfred Spraul to clear the remote IRR.
	 */
	i = cfg->vector;
	v = apic_पढ़ो(APIC_TMR + ((i & ~0x1f) >> 1));

	/*
	 * We must acknowledge the irq beक्रमe we move it or the acknowledge will
	 * not propagate properly.
	 */
	ack_APIC_irq();

	/*
	 * Tail end of clearing remote IRR bit (either by delivering the EOI
	 * message via io-apic EOI रेजिस्टर ग_लिखो or simulating it using
	 * mask+edge followed by unmask+level logic) manually when the
	 * level triggered पूर्णांकerrupt is seen as the edge triggered पूर्णांकerrupt
	 * at the cpu.
	 */
	अगर (!(v & (1 << (i & 0x1f)))) अणु
		atomic_inc(&irq_mis_count);
		eoi_ioapic_pin(cfg->vector, irq_data->chip_data);
	पूर्ण

	ioapic_finish_move(irq_data, moveit);
पूर्ण

अटल व्योम ioapic_ir_ack_level(काष्ठा irq_data *irq_data)
अणु
	काष्ठा mp_chip_data *data = irq_data->chip_data;

	/*
	 * Intr-remapping uses pin number as the भव vector
	 * in the RTE. Actual vector is programmed in
	 * पूर्णांकr-remapping table entry. Hence क्रम the io-apic
	 * EOI we use the pin number.
	 */
	apic_ack_irq(irq_data);
	eoi_ioapic_pin(data->entry.vector, data);
पूर्ण

/*
 * The I/OAPIC is just a device क्रम generating MSI messages from legacy
 * पूर्णांकerrupt pins. Various fields of the RTE translate पूर्णांकo bits of the
 * resulting MSI which had a historical meaning.
 *
 * With पूर्णांकerrupt remapping, many of those bits have dअगरferent meanings
 * in the underlying MSI, but the way that the I/OAPIC transक्रमms them
 * from its RTE to the MSI message is the same. This function allows
 * the parent IRQ करोमुख्य to compose the MSI message, then takes the
 * relevant bits to put them in the appropriate places in the RTE in
 * order to generate that message when the IRQ happens.
 *
 * The setup here relies on a preconfigured route entry (is_level,
 * active_low, masked) because the parent करोमुख्य is merely composing the
 * generic message routing inक्रमmation which is used क्रम the MSI.
 */
अटल व्योम ioapic_setup_msg_from_msi(काष्ठा irq_data *irq_data,
				      काष्ठा IO_APIC_route_entry *entry)
अणु
	काष्ठा msi_msg msg;

	/* Let the parent करोमुख्य compose the MSI message */
	irq_chip_compose_msi_msg(irq_data, &msg);

	/*
	 * - Real vector
	 * - DMAR/IR: 8bit subhandle (ioapic.pin)
	 * - AMD/IR:  8bit IRTE index
	 */
	entry->vector			= msg.arch_data.vector;
	/* Delivery mode (क्रम DMAR/IR all 0) */
	entry->delivery_mode		= msg.arch_data.delivery_mode;
	/* Destination mode or DMAR/IR index bit 15 */
	entry->dest_mode_logical	= msg.arch_addr_lo.dest_mode_logical;
	/* DMAR/IR: 1, 0 क्रम all other modes */
	entry->ir_क्रमmat		= msg.arch_addr_lo.dmar_क्रमmat;
	/*
	 * - DMAR/IR: index bit 0-14.
	 *
	 * - Virt: If the host supports x2apic without a भवized IR
	 *	   unit then bit 0-6 of dmar_index_0_14 are providing bit
	 *	   8-14 of the destination id.
	 *
	 * All other modes have bit 0-6 of dmar_index_0_14 cleared and the
	 * topmost 8 bits are destination id bit 0-7 (entry::destid_0_7).
	 */
	entry->ir_index_0_14		= msg.arch_addr_lo.dmar_index_0_14;
पूर्ण

अटल व्योम ioapic_configure_entry(काष्ठा irq_data *irqd)
अणु
	काष्ठा mp_chip_data *mpd = irqd->chip_data;
	काष्ठा irq_pin_list *entry;

	ioapic_setup_msg_from_msi(irqd, &mpd->entry);

	क्रम_each_irq_pin(entry, mpd->irq_2_pin)
		__ioapic_ग_लिखो_entry(entry->apic, entry->pin, mpd->entry);
पूर्ण

अटल पूर्णांक ioapic_set_affinity(काष्ठा irq_data *irq_data,
			       स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	काष्ठा irq_data *parent = irq_data->parent_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = parent->chip->irq_set_affinity(parent, mask, क्रमce);
	raw_spin_lock_irqsave(&ioapic_lock, flags);
	अगर (ret >= 0 && ret != IRQ_SET_MASK_OK_DONE)
		ioapic_configure_entry(irq_data);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);

	वापस ret;
पूर्ण

/*
 * Interrupt shutकरोwn masks the ioapic pin, but the पूर्णांकerrupt might alपढ़ोy
 * be in flight, but not yet serviced by the target CPU. That means
 * __synchronize_hardirq() would वापस and claim that everything is calmed
 * करोwn. So मुक्त_irq() would proceed and deactivate the पूर्णांकerrupt and मुक्त
 * resources.
 *
 * Once the target CPU comes around to service it it will find a cleared
 * vector and complain. While the spurious पूर्णांकerrupt is harmless, the full
 * release of resources might prevent the पूर्णांकerrupt from being acknowledged
 * which keeps the hardware in a weird state.
 *
 * Verअगरy that the corresponding Remote-IRR bits are clear.
 */
अटल पूर्णांक ioapic_irq_get_chip_state(काष्ठा irq_data *irqd,
				   क्रमागत irqchip_irq_state which,
				   bool *state)
अणु
	काष्ठा mp_chip_data *mcd = irqd->chip_data;
	काष्ठा IO_APIC_route_entry rentry;
	काष्ठा irq_pin_list *p;

	अगर (which != IRQCHIP_STATE_ACTIVE)
		वापस -EINVAL;

	*state = false;
	raw_spin_lock(&ioapic_lock);
	क्रम_each_irq_pin(p, mcd->irq_2_pin) अणु
		rentry = __ioapic_पढ़ो_entry(p->apic, p->pin);
		/*
		 * The remote IRR is only valid in level trigger mode. It's
		 * meaning is undefined क्रम edge triggered पूर्णांकerrupts and
		 * irrelevant because the IO-APIC treats them as fire and
		 * क्रमget.
		 */
		अगर (rentry.irr && rentry.is_level) अणु
			*state = true;
			अवरोध;
		पूर्ण
	पूर्ण
	raw_spin_unlock(&ioapic_lock);
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip ioapic_chip __पढ़ो_mostly = अणु
	.name			= "IO-APIC",
	.irq_startup		= startup_ioapic_irq,
	.irq_mask		= mask_ioapic_irq,
	.irq_unmask		= unmask_ioapic_irq,
	.irq_ack		= irq_chip_ack_parent,
	.irq_eoi		= ioapic_ack_level,
	.irq_set_affinity	= ioapic_set_affinity,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_get_irqchip_state	= ioapic_irq_get_chip_state,
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल काष्ठा irq_chip ioapic_ir_chip __पढ़ो_mostly = अणु
	.name			= "IR-IO-APIC",
	.irq_startup		= startup_ioapic_irq,
	.irq_mask		= mask_ioapic_irq,
	.irq_unmask		= unmask_ioapic_irq,
	.irq_ack		= irq_chip_ack_parent,
	.irq_eoi		= ioapic_ir_ack_level,
	.irq_set_affinity	= ioapic_set_affinity,
	.irq_retrigger		= irq_chip_retrigger_hierarchy,
	.irq_get_irqchip_state	= ioapic_irq_get_chip_state,
	.flags			= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल अंतरभूत व्योम init_IO_APIC_traps(व्योम)
अणु
	काष्ठा irq_cfg *cfg;
	अचिन्हित पूर्णांक irq;

	क्रम_each_active_irq(irq) अणु
		cfg = irq_cfg(irq);
		अगर (IO_APIC_IRQ(irq) && cfg && !cfg->vector) अणु
			/*
			 * Hmm.. We करोn't have an entry क्रम this,
			 * so शेष to an old-fashioned 8259
			 * पूर्णांकerrupt अगर we can..
			 */
			अगर (irq < nr_legacy_irqs())
				legacy_pic->make_irq(irq);
			अन्यथा
				/* Strange. Oh, well.. */
				irq_set_chip(irq, &no_irq_chip);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * The local APIC irq-chip implementation:
 */

अटल व्योम mask_lapic_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ v;

	v = apic_पढ़ो(APIC_LVT0);
	apic_ग_लिखो(APIC_LVT0, v | APIC_LVT_MASKED);
पूर्ण

अटल व्योम unmask_lapic_irq(काष्ठा irq_data *data)
अणु
	अचिन्हित दीर्घ v;

	v = apic_पढ़ो(APIC_LVT0);
	apic_ग_लिखो(APIC_LVT0, v & ~APIC_LVT_MASKED);
पूर्ण

अटल व्योम ack_lapic_irq(काष्ठा irq_data *data)
अणु
	ack_APIC_irq();
पूर्ण

अटल काष्ठा irq_chip lapic_chip __पढ़ो_mostly = अणु
	.name		= "local-APIC",
	.irq_mask	= mask_lapic_irq,
	.irq_unmask	= unmask_lapic_irq,
	.irq_ack	= ack_lapic_irq,
पूर्ण;

अटल व्योम lapic_रेजिस्टर_पूर्णांकr(पूर्णांक irq)
अणु
	irq_clear_status_flags(irq, IRQ_LEVEL);
	irq_set_chip_and_handler_name(irq, &lapic_chip, handle_edge_irq,
				      "edge");
पूर्ण

/*
 * This looks a bit hackish but it's about the only one way of sending
 * a few INTA cycles to 8259As and any associated glue logic.  ICR करोes
 * not support the ExtINT mode, unक्रमtunately.  We need to send these
 * cycles as some i82489DX-based boards have glue logic that keeps the
 * 8259A पूर्णांकerrupt line निश्चितed until INTA.  --macro
 */
अटल अंतरभूत व्योम __init unlock_ExtINT_logic(व्योम)
अणु
	पूर्णांक apic, pin, i;
	काष्ठा IO_APIC_route_entry entry0, entry1;
	अचिन्हित अक्षर save_control, save_freq_select;
	u32 apic_id;

	pin  = find_isa_irq_pin(8, mp_INT);
	अगर (pin == -1) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण
	apic = find_isa_irq_apic(8, mp_INT);
	अगर (apic == -1) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	entry0 = ioapic_पढ़ो_entry(apic, pin);
	clear_IO_APIC_pin(apic, pin);

	apic_id = hard_smp_processor_id();
	स_रखो(&entry1, 0, माप(entry1));

	entry1.dest_mode_logical	= true;
	entry1.masked			= false;
	entry1.destid_0_7		= apic_id & 0xFF;
	entry1.virt_destid_8_14		= apic_id >> 8;
	entry1.delivery_mode		= APIC_DELIVERY_MODE_EXTINT;
	entry1.active_low		= entry0.active_low;
	entry1.is_level			= false;
	entry1.vector = 0;

	ioapic_ग_लिखो_entry(apic, pin, entry1);

	save_control = CMOS_READ(RTC_CONTROL);
	save_freq_select = CMOS_READ(RTC_FREQ_SELECT);
	CMOS_WRITE((save_freq_select & ~RTC_RATE_SELECT) | 0x6,
		   RTC_FREQ_SELECT);
	CMOS_WRITE(save_control | RTC_PIE, RTC_CONTROL);

	i = 100;
	जबतक (i-- > 0) अणु
		mdelay(10);
		अगर ((CMOS_READ(RTC_INTR_FLAGS) & RTC_PF) == RTC_PF)
			i -= 10;
	पूर्ण

	CMOS_WRITE(save_control, RTC_CONTROL);
	CMOS_WRITE(save_freq_select, RTC_FREQ_SELECT);
	clear_IO_APIC_pin(apic, pin);

	ioapic_ग_लिखो_entry(apic, pin, entry0);
पूर्ण

अटल पूर्णांक disable_समयr_pin_1 __initdata;
/* Actually the next is obsolete, but keep it क्रम paranoid reasons -AK */
अटल पूर्णांक __init disable_समयr_pin_setup(अक्षर *arg)
अणु
	disable_समयr_pin_1 = 1;
	वापस 0;
पूर्ण
early_param("disable_timer_pin_1", disable_समयr_pin_setup);

अटल पूर्णांक mp_alloc_समयr_irq(पूर्णांक ioapic, पूर्णांक pin)
अणु
	पूर्णांक irq = -1;
	काष्ठा irq_करोमुख्य *करोमुख्य = mp_ioapic_irqकरोमुख्य(ioapic);

	अगर (करोमुख्य) अणु
		काष्ठा irq_alloc_info info;

		ioapic_set_alloc_attr(&info, NUMA_NO_NODE, 0, 0);
		info.devid = mpc_ioapic_id(ioapic);
		info.ioapic.pin = pin;
		mutex_lock(&ioapic_mutex);
		irq = alloc_isa_irq_from_करोमुख्य(करोमुख्य, 0, ioapic, pin, &info);
		mutex_unlock(&ioapic_mutex);
	पूर्ण

	वापस irq;
पूर्ण

/*
 * This code may look a bit paranoid, but it's supposed to cooperate with
 * a wide range of boards and BIOS bugs.  Fortunately only the समयr IRQ
 * is so screwy.  Thanks to Brian Perkins क्रम testing/hacking this beast
 * fanatically on his truly buggy board.
 *
 * FIXME: really need to revamp this क्रम all platक्रमms.
 */
अटल अंतरभूत व्योम __init check_समयr(व्योम)
अणु
	काष्ठा irq_data *irq_data = irq_get_irq_data(0);
	काष्ठा mp_chip_data *data = irq_data->chip_data;
	काष्ठा irq_cfg *cfg = irqd_cfg(irq_data);
	पूर्णांक node = cpu_to_node(0);
	पूर्णांक apic1, pin1, apic2, pin2;
	पूर्णांक no_pin1 = 0;

	अगर (!global_घड़ी_event)
		वापस;

	local_irq_disable();

	/*
	 * get/set the समयr IRQ vector:
	 */
	legacy_pic->mask(0);

	/*
	 * As IRQ0 is to be enabled in the 8259A, the भव
	 * wire has to be disabled in the local APIC.  Also
	 * समयr पूर्णांकerrupts need to be acknowledged manually in
	 * the 8259A क्रम the i82489DX when using the NMI
	 * watchकरोg as that APIC treats NMIs as level-triggered.
	 * The AEOI mode will finish them in the 8259A
	 * स्वतःmatically.
	 */
	apic_ग_लिखो(APIC_LVT0, APIC_LVT_MASKED | APIC_DM_EXTINT);
	legacy_pic->init(1);

	pin1  = find_isa_irq_pin(0, mp_INT);
	apic1 = find_isa_irq_apic(0, mp_INT);
	pin2  = ioapic_i8259.pin;
	apic2 = ioapic_i8259.apic;

	apic_prपूर्णांकk(APIC_QUIET, KERN_INFO "..TIMER: vector=0x%02X "
		    "apic1=%d pin1=%d apic2=%d pin2=%d\n",
		    cfg->vector, apic1, pin1, apic2, pin2);

	/*
	 * Some BIOS ग_लिखोrs are clueless and report the ExtINTA
	 * I/O APIC input from the cascaded 8259A as the समयr
	 * पूर्णांकerrupt input.  So just in हाल, अगर only one pin
	 * was found above, try it both directly and through the
	 * 8259A.
	 */
	अगर (pin1 == -1) अणु
		panic_अगर_irq_remap("BIOS bug: timer not connected to IO-APIC");
		pin1 = pin2;
		apic1 = apic2;
		no_pin1 = 1;
	पूर्ण अन्यथा अगर (pin2 == -1) अणु
		pin2 = pin1;
		apic2 = apic1;
	पूर्ण

	अगर (pin1 != -1) अणु
		/* Ok, करोes IRQ0 through the IOAPIC work? */
		अगर (no_pin1) अणु
			mp_alloc_समयr_irq(apic1, pin1);
		पूर्ण अन्यथा अणु
			/*
			 * क्रम edge trigger, it's alपढ़ोy unmasked,
			 * so only need to unmask अगर it is level-trigger
			 * करो we really have level trigger समयr?
			 */
			पूर्णांक idx = find_irq_entry(apic1, pin1, mp_INT);

			अगर (idx != -1 && irq_is_level(idx))
				unmask_ioapic_irq(irq_get_irq_data(0));
		पूर्ण
		irq_करोमुख्य_deactivate_irq(irq_data);
		irq_करोमुख्य_activate_irq(irq_data, false);
		अगर (समयr_irq_works()) अणु
			अगर (disable_समयr_pin_1 > 0)
				clear_IO_APIC_pin(0, pin1);
			जाओ out;
		पूर्ण
		panic_अगर_irq_remap("timer doesn't work through Interrupt-remapped IO-APIC");
		clear_IO_APIC_pin(apic1, pin1);
		अगर (!no_pin1)
			apic_prपूर्णांकk(APIC_QUIET, KERN_ERR "..MP-BIOS bug: "
				    "8254 timer not connected to IO-APIC\n");

		apic_prपूर्णांकk(APIC_QUIET, KERN_INFO "...trying to set up timer "
			    "(IRQ0) through the 8259A ...\n");
		apic_prपूर्णांकk(APIC_QUIET, KERN_INFO
			    "..... (found apic %d pin %d) ...\n", apic2, pin2);
		/*
		 * legacy devices should be connected to IO APIC #0
		 */
		replace_pin_at_irq_node(data, node, apic1, pin1, apic2, pin2);
		irq_करोमुख्य_deactivate_irq(irq_data);
		irq_करोमुख्य_activate_irq(irq_data, false);
		legacy_pic->unmask(0);
		अगर (समयr_irq_works()) अणु
			apic_prपूर्णांकk(APIC_QUIET, KERN_INFO "....... works.\n");
			जाओ out;
		पूर्ण
		/*
		 * Cleanup, just in हाल ...
		 */
		legacy_pic->mask(0);
		clear_IO_APIC_pin(apic2, pin2);
		apic_prपूर्णांकk(APIC_QUIET, KERN_INFO "....... failed.\n");
	पूर्ण

	apic_prपूर्णांकk(APIC_QUIET, KERN_INFO
		    "...trying to set up timer as Virtual Wire IRQ...\n");

	lapic_रेजिस्टर_पूर्णांकr(0);
	apic_ग_लिखो(APIC_LVT0, APIC_DM_FIXED | cfg->vector);	/* Fixed mode */
	legacy_pic->unmask(0);

	अगर (समयr_irq_works()) अणु
		apic_prपूर्णांकk(APIC_QUIET, KERN_INFO "..... works.\n");
		जाओ out;
	पूर्ण
	legacy_pic->mask(0);
	apic_ग_लिखो(APIC_LVT0, APIC_LVT_MASKED | APIC_DM_FIXED | cfg->vector);
	apic_prपूर्णांकk(APIC_QUIET, KERN_INFO "..... failed.\n");

	apic_prपूर्णांकk(APIC_QUIET, KERN_INFO
		    "...trying to set up timer as ExtINT IRQ...\n");

	legacy_pic->init(0);
	legacy_pic->make_irq(0);
	apic_ग_लिखो(APIC_LVT0, APIC_DM_EXTINT);
	legacy_pic->unmask(0);

	unlock_ExtINT_logic();

	अगर (समयr_irq_works()) अणु
		apic_prपूर्णांकk(APIC_QUIET, KERN_INFO "..... works.\n");
		जाओ out;
	पूर्ण
	apic_prपूर्णांकk(APIC_QUIET, KERN_INFO "..... failed :(.\n");
	अगर (apic_is_x2apic_enabled())
		apic_prपूर्णांकk(APIC_QUIET, KERN_INFO
			    "Perhaps problem with the pre-enabled x2apic mode\n"
			    "Try booting with x2apic and interrupt-remapping disabled in the bios.\n");
	panic("IO-APIC + timer doesn't work!  Boot with apic=debug and send a "
		"report.  Then try booting with the 'noapic' option.\n");
out:
	local_irq_enable();
पूर्ण

/*
 * Traditionally ISA IRQ2 is the cascade IRQ, and is not available
 * to devices.  However there may be an I/O APIC pin available क्रम
 * this पूर्णांकerrupt regardless.  The pin may be left unconnected, but
 * typically it will be reused as an ExtINT cascade पूर्णांकerrupt क्रम
 * the master 8259A.  In the MPS हाल such a pin will normally be
 * reported as an ExtINT पूर्णांकerrupt in the MP table.  With ACPI
 * there is no provision क्रम ExtINT पूर्णांकerrupts, and in the असलence
 * of an override it would be treated as an ordinary ISA I/O APIC
 * पूर्णांकerrupt, that is edge-triggered and unmasked by शेष.  We
 * used to करो this, but it caused problems on some प्रणालीs because
 * of the NMI watchकरोg and someबार IRQ0 of the 8254 समयr using
 * the same ExtINT cascade पूर्णांकerrupt to drive the local APIC of the
 * bootstrap processor.  Thereक्रमe we refrain from routing IRQ2 to
 * the I/O APIC in all हालs now.  No actual device should request
 * it anyway.  --macro
 */
#घोषणा PIC_IRQS	(1UL << PIC_CASCADE_IR)

अटल पूर्णांक mp_irqकरोमुख्य_create(पूर्णांक ioapic)
अणु
	काष्ठा irq_करोमुख्य *parent;
	पूर्णांक hwirqs = mp_ioapic_pin_count(ioapic);
	काष्ठा ioapic *ip = &ioapics[ioapic];
	काष्ठा ioapic_करोमुख्य_cfg *cfg = &ip->irqकरोमुख्य_cfg;
	काष्ठा mp_ioapic_gsi *gsi_cfg = mp_ioapic_gsi_routing(ioapic);
	काष्ठा fwnode_handle *fn;
	काष्ठा irq_fwspec fwspec;

	अगर (cfg->type == IOAPIC_DOMAIN_INVALID)
		वापस 0;

	/* Handle device tree क्रमागतerated APICs proper */
	अगर (cfg->dev) अणु
		fn = of_node_to_fwnode(cfg->dev);
	पूर्ण अन्यथा अणु
		fn = irq_करोमुख्य_alloc_named_id_fwnode("IO-APIC", mpc_ioapic_id(ioapic));
		अगर (!fn)
			वापस -ENOMEM;
	पूर्ण

	fwspec.fwnode = fn;
	fwspec.param_count = 1;
	fwspec.param[0] = mpc_ioapic_id(ioapic);

	parent = irq_find_matching_fwspec(&fwspec, DOMAIN_BUS_ANY);
	अगर (!parent) अणु
		अगर (!cfg->dev)
			irq_करोमुख्य_मुक्त_fwnode(fn);
		वापस -ENODEV;
	पूर्ण

	ip->irqकरोमुख्य = irq_करोमुख्य_create_linear(fn, hwirqs, cfg->ops,
						 (व्योम *)(दीर्घ)ioapic);

	अगर (!ip->irqकरोमुख्य) अणु
		/* Release fw handle अगर it was allocated above */
		अगर (!cfg->dev)
			irq_करोमुख्य_मुक्त_fwnode(fn);
		वापस -ENOMEM;
	पूर्ण

	ip->irqकरोमुख्य->parent = parent;

	अगर (cfg->type == IOAPIC_DOMAIN_LEGACY ||
	    cfg->type == IOAPIC_DOMAIN_STRICT)
		ioapic_dynirq_base = max(ioapic_dynirq_base,
					 gsi_cfg->gsi_end + 1);

	वापस 0;
पूर्ण

अटल व्योम ioapic_destroy_irqकरोमुख्य(पूर्णांक idx)
अणु
	काष्ठा ioapic_करोमुख्य_cfg *cfg = &ioapics[idx].irqकरोमुख्य_cfg;
	काष्ठा fwnode_handle *fn = ioapics[idx].irqकरोमुख्य->fwnode;

	अगर (ioapics[idx].irqकरोमुख्य) अणु
		irq_करोमुख्य_हटाओ(ioapics[idx].irqकरोमुख्य);
		अगर (!cfg->dev)
			irq_करोमुख्य_मुक्त_fwnode(fn);
		ioapics[idx].irqकरोमुख्य = शून्य;
	पूर्ण
पूर्ण

व्योम __init setup_IO_APIC(व्योम)
अणु
	पूर्णांक ioapic;

	अगर (skip_ioapic_setup || !nr_ioapics)
		वापस;

	io_apic_irqs = nr_legacy_irqs() ? ~PIC_IRQS : ~0UL;

	apic_prपूर्णांकk(APIC_VERBOSE, "ENABLING IO-APIC IRQs\n");
	क्रम_each_ioapic(ioapic)
		BUG_ON(mp_irqकरोमुख्य_create(ioapic));

	/*
         * Set up IO-APIC IRQ routing.
         */
	x86_init.mpparse.setup_ioapic_ids();

	sync_Arb_IDs();
	setup_IO_APIC_irqs();
	init_IO_APIC_traps();
	अगर (nr_legacy_irqs())
		check_समयr();

	ioapic_initialized = 1;
पूर्ण

अटल व्योम resume_ioapic_id(पूर्णांक ioapic_idx)
अणु
	अचिन्हित दीर्घ flags;
	जोड़ IO_APIC_reg_00 reg_00;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	reg_00.raw = io_apic_पढ़ो(ioapic_idx, 0);
	अगर (reg_00.bits.ID != mpc_ioapic_id(ioapic_idx)) अणु
		reg_00.bits.ID = mpc_ioapic_id(ioapic_idx);
		io_apic_ग_लिखो(ioapic_idx, 0, reg_00.raw);
	पूर्ण
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
पूर्ण

अटल व्योम ioapic_resume(व्योम)
अणु
	पूर्णांक ioapic_idx;

	क्रम_each_ioapic_reverse(ioapic_idx)
		resume_ioapic_id(ioapic_idx);

	restore_ioapic_entries();
पूर्ण

अटल काष्ठा syscore_ops ioapic_syscore_ops = अणु
	.suspend = save_ioapic_entries,
	.resume = ioapic_resume,
पूर्ण;

अटल पूर्णांक __init ioapic_init_ops(व्योम)
अणु
	रेजिस्टर_syscore_ops(&ioapic_syscore_ops);

	वापस 0;
पूर्ण

device_initcall(ioapic_init_ops);

अटल पूर्णांक io_apic_get_redir_entries(पूर्णांक ioapic)
अणु
	जोड़ IO_APIC_reg_01	reg_01;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	reg_01.raw = io_apic_पढ़ो(ioapic, 1);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);

	/* The रेजिस्टर वापसs the maximum index redir index
	 * supported, which is one less than the total number of redir
	 * entries.
	 */
	वापस reg_01.bits.entries + 1;
पूर्ण

अचिन्हित पूर्णांक arch_dynirq_lower_bound(अचिन्हित पूर्णांक from)
अणु
	/*
	 * dmar_alloc_hwirq() may be called beक्रमe setup_IO_APIC(), so use
	 * gsi_top अगर ioapic_dynirq_base hasn't been initialized yet.
	 */
	अगर (!ioapic_initialized)
		वापस gsi_top;
	/*
	 * For DT enabled machines ioapic_dynirq_base is irrelevant and not
	 * updated. So simply वापस @from अगर ioapic_dynirq_base == 0.
	 */
	वापस ioapic_dynirq_base ? : from;
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल पूर्णांक io_apic_get_unique_id(पूर्णांक ioapic, पूर्णांक apic_id)
अणु
	जोड़ IO_APIC_reg_00 reg_00;
	अटल physid_mask_t apic_id_map = PHYSID_MASK_NONE;
	physid_mask_t पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक i = 0;

	/*
	 * The P4 platक्रमm supports up to 256 APIC IDs on two separate APIC
	 * buses (one क्रम LAPICs, one क्रम IOAPICs), where predecessors only
	 * supports up to 16 on one shared APIC bus.
	 *
	 * TBD: Expand LAPIC/IOAPIC support on P4-class प्रणालीs to take full
	 *      advantage of new APIC bus architecture.
	 */

	अगर (physids_empty(apic_id_map))
		apic->ioapic_phys_id_map(&phys_cpu_present_map, &apic_id_map);

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	reg_00.raw = io_apic_पढ़ो(ioapic, 0);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);

	अगर (apic_id >= get_physical_broadcast()) अणु
		prपूर्णांकk(KERN_WARNING "IOAPIC[%d]: Invalid apic_id %d, trying "
			"%d\n", ioapic, apic_id, reg_00.bits.ID);
		apic_id = reg_00.bits.ID;
	पूर्ण

	/*
	 * Every APIC in a प्रणाली must have a unique ID or we get lots of nice
	 * 'stuck on smp_invalidate_needed IPI wait' messages.
	 */
	अगर (apic->check_apicid_used(&apic_id_map, apic_id)) अणु

		क्रम (i = 0; i < get_physical_broadcast(); i++) अणु
			अगर (!apic->check_apicid_used(&apic_id_map, i))
				अवरोध;
		पूर्ण

		अगर (i == get_physical_broadcast())
			panic("Max apic_id exceeded!\n");

		prपूर्णांकk(KERN_WARNING "IOAPIC[%d]: apic_id %d already used, "
			"trying %d\n", ioapic, apic_id, i);

		apic_id = i;
	पूर्ण

	apic->apicid_to_cpu_present(apic_id, &पंचांगp);
	physids_or(apic_id_map, apic_id_map, पंचांगp);

	अगर (reg_00.bits.ID != apic_id) अणु
		reg_00.bits.ID = apic_id;

		raw_spin_lock_irqsave(&ioapic_lock, flags);
		io_apic_ग_लिखो(ioapic, 0, reg_00.raw);
		reg_00.raw = io_apic_पढ़ो(ioapic, 0);
		raw_spin_unlock_irqrestore(&ioapic_lock, flags);

		/* Sanity check */
		अगर (reg_00.bits.ID != apic_id) अणु
			pr_err("IOAPIC[%d]: Unable to change apic_id!\n",
			       ioapic);
			वापस -1;
		पूर्ण
	पूर्ण

	apic_prपूर्णांकk(APIC_VERBOSE, KERN_INFO
			"IOAPIC[%d]: Assigned apic_id %d\n", ioapic, apic_id);

	वापस apic_id;
पूर्ण

अटल u8 io_apic_unique_id(पूर्णांक idx, u8 id)
अणु
	अगर ((boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL) &&
	    !APIC_XAPIC(boot_cpu_apic_version))
		वापस io_apic_get_unique_id(idx, id);
	अन्यथा
		वापस id;
पूर्ण
#अन्यथा
अटल u8 io_apic_unique_id(पूर्णांक idx, u8 id)
अणु
	जोड़ IO_APIC_reg_00 reg_00;
	DECLARE_BITMAP(used, 256);
	अचिन्हित दीर्घ flags;
	u8 new_id;
	पूर्णांक i;

	biपंचांगap_zero(used, 256);
	क्रम_each_ioapic(i)
		__set_bit(mpc_ioapic_id(i), used);

	/* Hand out the requested id अगर available */
	अगर (!test_bit(id, used))
		वापस id;

	/*
	 * Read the current id from the ioapic and keep it अगर
	 * available.
	 */
	raw_spin_lock_irqsave(&ioapic_lock, flags);
	reg_00.raw = io_apic_पढ़ो(idx, 0);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
	new_id = reg_00.bits.ID;
	अगर (!test_bit(new_id, used)) अणु
		apic_prपूर्णांकk(APIC_VERBOSE, KERN_INFO
			"IOAPIC[%d]: Using reg apic_id %d instead of %d\n",
			 idx, new_id, id);
		वापस new_id;
	पूर्ण

	/*
	 * Get the next मुक्त id and ग_लिखो it to the ioapic.
	 */
	new_id = find_first_zero_bit(used, 256);
	reg_00.bits.ID = new_id;
	raw_spin_lock_irqsave(&ioapic_lock, flags);
	io_apic_ग_लिखो(idx, 0, reg_00.raw);
	reg_00.raw = io_apic_पढ़ो(idx, 0);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
	/* Sanity check */
	BUG_ON(reg_00.bits.ID != new_id);

	वापस new_id;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक io_apic_get_version(पूर्णांक ioapic)
अणु
	जोड़ IO_APIC_reg_01	reg_01;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	reg_01.raw = io_apic_पढ़ो(ioapic, 1);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);

	वापस reg_01.bits.version;
पूर्ण

/*
 * This function updates target affinity of IOAPIC पूर्णांकerrupts to include
 * the CPUs which came online during SMP bringup.
 */
#घोषणा IOAPIC_RESOURCE_NAME_SIZE 11

अटल काष्ठा resource *ioapic_resources;

अटल काष्ठा resource * __init ioapic_setup_resources(व्योम)
अणु
	अचिन्हित दीर्घ n;
	काष्ठा resource *res;
	अक्षर *mem;
	पूर्णांक i;

	अगर (nr_ioapics == 0)
		वापस शून्य;

	n = IOAPIC_RESOURCE_NAME_SIZE + माप(काष्ठा resource);
	n *= nr_ioapics;

	mem = memblock_alloc(n, SMP_CACHE_BYTES);
	अगर (!mem)
		panic("%s: Failed to allocate %lu bytes\n", __func__, n);
	res = (व्योम *)mem;

	mem += माप(काष्ठा resource) * nr_ioapics;

	क्रम_each_ioapic(i) अणु
		res[i].name = mem;
		res[i].flags = IORESOURCE_MEM | IORESOURCE_BUSY;
		snम_लिखो(mem, IOAPIC_RESOURCE_NAME_SIZE, "IOAPIC %u", i);
		mem += IOAPIC_RESOURCE_NAME_SIZE;
		ioapics[i].iomem_res = &res[i];
	पूर्ण

	ioapic_resources = res;

	वापस res;
पूर्ण

व्योम __init io_apic_init_mappings(व्योम)
अणु
	अचिन्हित दीर्घ ioapic_phys, idx = FIX_IO_APIC_BASE_0;
	काष्ठा resource *ioapic_res;
	पूर्णांक i;

	ioapic_res = ioapic_setup_resources();
	क्रम_each_ioapic(i) अणु
		अगर (smp_found_config) अणु
			ioapic_phys = mpc_ioapic_addr(i);
#अगर_घोषित CONFIG_X86_32
			अगर (!ioapic_phys) अणु
				prपूर्णांकk(KERN_ERR
				       "WARNING: bogus zero IO-APIC "
				       "address found in MPTABLE, "
				       "disabling IO/APIC support!\n");
				smp_found_config = 0;
				skip_ioapic_setup = 1;
				जाओ fake_ioapic_page;
			पूर्ण
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_X86_32
fake_ioapic_page:
#पूर्ण_अगर
			ioapic_phys = (अचिन्हित दीर्घ)memblock_alloc(PAGE_SIZE,
								    PAGE_SIZE);
			अगर (!ioapic_phys)
				panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
				      __func__, PAGE_SIZE, PAGE_SIZE);
			ioapic_phys = __pa(ioapic_phys);
		पूर्ण
		set_fixmap_nocache(idx, ioapic_phys);
		apic_prपूर्णांकk(APIC_VERBOSE, "mapped IOAPIC to %08lx (%08lx)\n",
			__fix_to_virt(idx) + (ioapic_phys & ~PAGE_MASK),
			ioapic_phys);
		idx++;

		ioapic_res->start = ioapic_phys;
		ioapic_res->end = ioapic_phys + IO_APIC_SLOT_SIZE - 1;
		ioapic_res++;
	पूर्ण
पूर्ण

व्योम __init ioapic_insert_resources(व्योम)
अणु
	पूर्णांक i;
	काष्ठा resource *r = ioapic_resources;

	अगर (!r) अणु
		अगर (nr_ioapics > 0)
			prपूर्णांकk(KERN_ERR
				"IO APIC resources couldn't be allocated.\n");
		वापस;
	पूर्ण

	क्रम_each_ioapic(i) अणु
		insert_resource(&iomem_resource, r);
		r++;
	पूर्ण
पूर्ण

पूर्णांक mp_find_ioapic(u32 gsi)
अणु
	पूर्णांक i;

	अगर (nr_ioapics == 0)
		वापस -1;

	/* Find the IOAPIC that manages this GSI. */
	क्रम_each_ioapic(i) अणु
		काष्ठा mp_ioapic_gsi *gsi_cfg = mp_ioapic_gsi_routing(i);
		अगर (gsi >= gsi_cfg->gsi_base && gsi <= gsi_cfg->gsi_end)
			वापस i;
	पूर्ण

	prपूर्णांकk(KERN_ERR "ERROR: Unable to locate IOAPIC for GSI %d\n", gsi);
	वापस -1;
पूर्ण

पूर्णांक mp_find_ioapic_pin(पूर्णांक ioapic, u32 gsi)
अणु
	काष्ठा mp_ioapic_gsi *gsi_cfg;

	अगर (WARN_ON(ioapic < 0))
		वापस -1;

	gsi_cfg = mp_ioapic_gsi_routing(ioapic);
	अगर (WARN_ON(gsi > gsi_cfg->gsi_end))
		वापस -1;

	वापस gsi - gsi_cfg->gsi_base;
पूर्ण

अटल पूर्णांक bad_ioapic_रेजिस्टर(पूर्णांक idx)
अणु
	जोड़ IO_APIC_reg_00 reg_00;
	जोड़ IO_APIC_reg_01 reg_01;
	जोड़ IO_APIC_reg_02 reg_02;

	reg_00.raw = io_apic_पढ़ो(idx, 0);
	reg_01.raw = io_apic_पढ़ो(idx, 1);
	reg_02.raw = io_apic_पढ़ो(idx, 2);

	अगर (reg_00.raw == -1 && reg_01.raw == -1 && reg_02.raw == -1) अणु
		pr_warn("I/O APIC 0x%x registers return all ones, skipping!\n",
			mpc_ioapic_addr(idx));
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक find_मुक्त_ioapic_entry(व्योम)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < MAX_IO_APICS; idx++)
		अगर (ioapics[idx].nr_रेजिस्टरs == 0)
			वापस idx;

	वापस MAX_IO_APICS;
पूर्ण

/**
 * mp_रेजिस्टर_ioapic - Register an IOAPIC device
 * @id:		hardware IOAPIC ID
 * @address:	physical address of IOAPIC रेजिस्टर area
 * @gsi_base:	base of GSI associated with the IOAPIC
 * @cfg:	configuration inक्रमmation क्रम the IOAPIC
 */
पूर्णांक mp_रेजिस्टर_ioapic(पूर्णांक id, u32 address, u32 gsi_base,
		       काष्ठा ioapic_करोमुख्य_cfg *cfg)
अणु
	bool hotplug = !!ioapic_initialized;
	काष्ठा mp_ioapic_gsi *gsi_cfg;
	पूर्णांक idx, ioapic, entries;
	u32 gsi_end;

	अगर (!address) अणु
		pr_warn("Bogus (zero) I/O APIC address found, skipping!\n");
		वापस -EINVAL;
	पूर्ण
	क्रम_each_ioapic(ioapic)
		अगर (ioapics[ioapic].mp_config.apicaddr == address) अणु
			pr_warn("address 0x%x conflicts with IOAPIC%d\n",
				address, ioapic);
			वापस -EEXIST;
		पूर्ण

	idx = find_मुक्त_ioapic_entry();
	अगर (idx >= MAX_IO_APICS) अणु
		pr_warn("Max # of I/O APICs (%d) exceeded (found %d), skipping\n",
			MAX_IO_APICS, idx);
		वापस -ENOSPC;
	पूर्ण

	ioapics[idx].mp_config.type = MP_IOAPIC;
	ioapics[idx].mp_config.flags = MPC_APIC_USABLE;
	ioapics[idx].mp_config.apicaddr = address;

	set_fixmap_nocache(FIX_IO_APIC_BASE_0 + idx, address);
	अगर (bad_ioapic_रेजिस्टर(idx)) अणु
		clear_fixmap(FIX_IO_APIC_BASE_0 + idx);
		वापस -ENODEV;
	पूर्ण

	ioapics[idx].mp_config.apicid = io_apic_unique_id(idx, id);
	ioapics[idx].mp_config.apicver = io_apic_get_version(idx);

	/*
	 * Build basic GSI lookup table to facilitate gsi->io_apic lookups
	 * and to prevent reprogramming of IOAPIC pins (PCI GSIs).
	 */
	entries = io_apic_get_redir_entries(idx);
	gsi_end = gsi_base + entries - 1;
	क्रम_each_ioapic(ioapic) अणु
		gsi_cfg = mp_ioapic_gsi_routing(ioapic);
		अगर ((gsi_base >= gsi_cfg->gsi_base &&
		     gsi_base <= gsi_cfg->gsi_end) ||
		    (gsi_end >= gsi_cfg->gsi_base &&
		     gsi_end <= gsi_cfg->gsi_end)) अणु
			pr_warn("GSI range [%u-%u] for new IOAPIC conflicts with GSI[%u-%u]\n",
				gsi_base, gsi_end,
				gsi_cfg->gsi_base, gsi_cfg->gsi_end);
			clear_fixmap(FIX_IO_APIC_BASE_0 + idx);
			वापस -ENOSPC;
		पूर्ण
	पूर्ण
	gsi_cfg = mp_ioapic_gsi_routing(idx);
	gsi_cfg->gsi_base = gsi_base;
	gsi_cfg->gsi_end = gsi_end;

	ioapics[idx].irqकरोमुख्य = शून्य;
	ioapics[idx].irqकरोमुख्य_cfg = *cfg;

	/*
	 * If mp_रेजिस्टर_ioapic() is called during early boot stage when
	 * walking ACPI/DT tables, it's too early to create irqकरोमुख्य,
	 * we are still using booपंचांगem allocator. So delay it to setup_IO_APIC().
	 */
	अगर (hotplug) अणु
		अगर (mp_irqकरोमुख्य_create(idx)) अणु
			clear_fixmap(FIX_IO_APIC_BASE_0 + idx);
			वापस -ENOMEM;
		पूर्ण
		alloc_ioapic_saved_रेजिस्टरs(idx);
	पूर्ण

	अगर (gsi_cfg->gsi_end >= gsi_top)
		gsi_top = gsi_cfg->gsi_end + 1;
	अगर (nr_ioapics <= idx)
		nr_ioapics = idx + 1;

	/* Set nr_रेजिस्टरs to mark entry present */
	ioapics[idx].nr_रेजिस्टरs = entries;

	pr_info("IOAPIC[%d]: apic_id %d, version %d, address 0x%x, GSI %d-%d\n",
		idx, mpc_ioapic_id(idx),
		mpc_ioapic_ver(idx), mpc_ioapic_addr(idx),
		gsi_cfg->gsi_base, gsi_cfg->gsi_end);

	वापस 0;
पूर्ण

पूर्णांक mp_unरेजिस्टर_ioapic(u32 gsi_base)
अणु
	पूर्णांक ioapic, pin;
	पूर्णांक found = 0;

	क्रम_each_ioapic(ioapic)
		अगर (ioapics[ioapic].gsi_config.gsi_base == gsi_base) अणु
			found = 1;
			अवरोध;
		पूर्ण
	अगर (!found) अणु
		pr_warn("can't find IOAPIC for GSI %d\n", gsi_base);
		वापस -ENODEV;
	पूर्ण

	क्रम_each_pin(ioapic, pin) अणु
		u32 gsi = mp_pin_to_gsi(ioapic, pin);
		पूर्णांक irq = mp_map_gsi_to_irq(gsi, 0, शून्य);
		काष्ठा mp_chip_data *data;

		अगर (irq >= 0) अणु
			data = irq_get_chip_data(irq);
			अगर (data && data->count) अणु
				pr_warn("pin%d on IOAPIC%d is still in use.\n",
					pin, ioapic);
				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Mark entry not present */
	ioapics[ioapic].nr_रेजिस्टरs  = 0;
	ioapic_destroy_irqकरोमुख्य(ioapic);
	मुक्त_ioapic_saved_रेजिस्टरs(ioapic);
	अगर (ioapics[ioapic].iomem_res)
		release_resource(ioapics[ioapic].iomem_res);
	clear_fixmap(FIX_IO_APIC_BASE_0 + ioapic);
	स_रखो(&ioapics[ioapic], 0, माप(ioapics[ioapic]));

	वापस 0;
पूर्ण

पूर्णांक mp_ioapic_रेजिस्टरed(u32 gsi_base)
अणु
	पूर्णांक ioapic;

	क्रम_each_ioapic(ioapic)
		अगर (ioapics[ioapic].gsi_config.gsi_base == gsi_base)
			वापस 1;

	वापस 0;
पूर्ण

अटल व्योम mp_irqकरोमुख्य_get_attr(u32 gsi, काष्ठा mp_chip_data *data,
				  काष्ठा irq_alloc_info *info)
अणु
	अगर (info && info->ioapic.valid) अणु
		data->is_level = info->ioapic.is_level;
		data->active_low = info->ioapic.active_low;
	पूर्ण अन्यथा अगर (__acpi_get_override_irq(gsi, &data->is_level,
					   &data->active_low) < 0) अणु
		/* PCI पूर्णांकerrupts are always active low level triggered. */
		data->is_level = true;
		data->active_low = true;
	पूर्ण
पूर्ण

/*
 * Configure the I/O-APIC specअगरic fields in the routing entry.
 *
 * This is important to setup the I/O-APIC specअगरic bits (is_level,
 * active_low, masked) because the underlying parent करोमुख्य will only
 * provide the routing inक्रमmation and is oblivious of the I/O-APIC
 * specअगरic bits.
 *
 * The entry is just preconfigured at this poपूर्णांक and not written पूर्णांकo the
 * RTE. This happens later during activation which will fill in the actual
 * routing inक्रमmation.
 */
अटल व्योम mp_preconfigure_entry(काष्ठा mp_chip_data *data)
अणु
	काष्ठा IO_APIC_route_entry *entry = &data->entry;

	स_रखो(entry, 0, माप(*entry));
	entry->is_level		 = data->is_level;
	entry->active_low	 = data->active_low;
	/*
	 * Mask level triggered irqs. Edge triggered irqs are masked
	 * by the irq core code in हाल they fire.
	 */
	entry->masked		= data->is_level;
पूर्ण

पूर्णांक mp_irqकरोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
		       अचिन्हित पूर्णांक nr_irqs, व्योम *arg)
अणु
	काष्ठा irq_alloc_info *info = arg;
	काष्ठा mp_chip_data *data;
	काष्ठा irq_data *irq_data;
	पूर्णांक ret, ioapic, pin;
	अचिन्हित दीर्घ flags;

	अगर (!info || nr_irqs > 1)
		वापस -EINVAL;
	irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	अगर (!irq_data)
		वापस -EINVAL;

	ioapic = mp_irqकरोमुख्य_ioapic_idx(करोमुख्य);
	pin = info->ioapic.pin;
	अगर (irq_find_mapping(करोमुख्य, (irq_hw_number_t)pin) > 0)
		वापस -EEXIST;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = irq_करोमुख्य_alloc_irqs_parent(करोमुख्य, virq, nr_irqs, info);
	अगर (ret < 0) अणु
		kमुक्त(data);
		वापस ret;
	पूर्ण

	INIT_LIST_HEAD(&data->irq_2_pin);
	irq_data->hwirq = info->ioapic.pin;
	irq_data->chip = (करोमुख्य->parent == x86_vector_करोमुख्य) ?
			  &ioapic_chip : &ioapic_ir_chip;
	irq_data->chip_data = data;
	mp_irqकरोमुख्य_get_attr(mp_pin_to_gsi(ioapic, pin), data, info);

	add_pin_to_irq_node(data, ioapic_alloc_attr_node(info), ioapic, pin);

	mp_preconfigure_entry(data);
	mp_रेजिस्टर_handler(virq, data->is_level);

	local_irq_save(flags);
	अगर (virq < nr_legacy_irqs())
		legacy_pic->mask(virq);
	local_irq_restore(flags);

	apic_prपूर्णांकk(APIC_VERBOSE, KERN_DEBUG
		    "IOAPIC[%d]: Preconfigured routing entry (%d-%d -> IRQ %d Level:%i ActiveLow:%i)\n",
		    ioapic, mpc_ioapic_id(ioapic), pin, virq,
		    data->is_level, data->active_low);
	वापस 0;
पूर्ण

व्योम mp_irqकरोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
		       अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *irq_data;
	काष्ठा mp_chip_data *data;

	BUG_ON(nr_irqs != 1);
	irq_data = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	अगर (irq_data && irq_data->chip_data) अणु
		data = irq_data->chip_data;
		__हटाओ_pin_from_irq(data, mp_irqकरोमुख्य_ioapic_idx(करोमुख्य),
				      (पूर्णांक)irq_data->hwirq);
		WARN_ON(!list_empty(&data->irq_2_pin));
		kमुक्त(irq_data->chip_data);
	पूर्ण
	irq_करोमुख्य_मुक्त_irqs_top(करोमुख्य, virq, nr_irqs);
पूर्ण

पूर्णांक mp_irqकरोमुख्य_activate(काष्ठा irq_करोमुख्य *करोमुख्य,
			  काष्ठा irq_data *irq_data, bool reserve)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ioapic_lock, flags);
	ioapic_configure_entry(irq_data);
	raw_spin_unlock_irqrestore(&ioapic_lock, flags);
	वापस 0;
पूर्ण

व्योम mp_irqकरोमुख्य_deactivate(काष्ठा irq_करोमुख्य *करोमुख्य,
			     काष्ठा irq_data *irq_data)
अणु
	/* It won't be called क्रम IRQ with multiple IOAPIC pins associated */
	ioapic_mask_entry(mp_irqकरोमुख्य_ioapic_idx(करोमुख्य),
			  (पूर्णांक)irq_data->hwirq);
पूर्ण

पूर्णांक mp_irqकरोमुख्य_ioapic_idx(काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	वापस (पूर्णांक)(दीर्घ)करोमुख्य->host_data;
पूर्ण

स्थिर काष्ठा irq_करोमुख्य_ops mp_ioapic_irqकरोमुख्य_ops = अणु
	.alloc		= mp_irqकरोमुख्य_alloc,
	.मुक्त		= mp_irqकरोमुख्य_मुक्त,
	.activate	= mp_irqकरोमुख्य_activate,
	.deactivate	= mp_irqकरोमुख्य_deactivate,
पूर्ण;
