<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Intel Multiprocessor Specअगरication 1.1 and 1.4
 *	compliant MP-table parsing routines.
 *
 *	(c) 1995 Alan Cox, Building #3 <alan@lxorguk.ukuu.org.uk>
 *	(c) 1998, 1999, 2000, 2009 Ingo Molnar <mingo@redhat.com>
 *      (c) 2008 Alexey Starikovskiy <astarikovskiy@suse.de>
 */

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/memblock.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/bitops.h>
#समावेश <linux/acpi.h>
#समावेश <linux/smp.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/irqकरोमुख्य.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/bios_ebda.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/smp.h>

#समावेश <यंत्र/apic.h>
/*
 * Checksum an MP configuration block.
 */

अटल पूर्णांक __init mpf_checksum(अचिन्हित अक्षर *mp, पूर्णांक len)
अणु
	पूर्णांक sum = 0;

	जबतक (len--)
		sum += *mp++;

	वापस sum & 0xFF;
पूर्ण

अटल व्योम __init MP_processor_info(काष्ठा mpc_cpu *m)
अणु
	पूर्णांक apicid;
	अक्षर *bootup_cpu = "";

	अगर (!(m->cpuflag & CPU_ENABLED)) अणु
		disabled_cpus++;
		वापस;
	पूर्ण

	apicid = m->apicid;

	अगर (m->cpuflag & CPU_BOOTPROCESSOR) अणु
		bootup_cpu = " (Bootup-CPU)";
		boot_cpu_physical_apicid = m->apicid;
	पूर्ण

	pr_info("Processor #%d%s\n", m->apicid, bootup_cpu);
	generic_processor_info(apicid, m->apicver);
पूर्ण

#अगर_घोषित CONFIG_X86_IO_APIC
अटल व्योम __init mpc_oem_bus_info(काष्ठा mpc_bus *m, अक्षर *str)
अणु
	स_नकल(str, m->bustype, 6);
	str[6] = 0;
	apic_prपूर्णांकk(APIC_VERBOSE, "Bus #%d is %s\n", m->busid, str);
पूर्ण

अटल व्योम __init MP_bus_info(काष्ठा mpc_bus *m)
अणु
	अक्षर str[7];

	mpc_oem_bus_info(m, str);

#अगर MAX_MP_BUSSES < 256
	अगर (m->busid >= MAX_MP_BUSSES) अणु
		pr_warn("MP table busid value (%d) for bustype %s is too large, max. supported is %d\n",
			m->busid, str, MAX_MP_BUSSES - 1);
		वापस;
	पूर्ण
#पूर्ण_अगर

	set_bit(m->busid, mp_bus_not_pci);
	अगर (म_भेदन(str, BUSTYPE_ISA, माप(BUSTYPE_ISA) - 1) == 0) अणु
#अगर_घोषित CONFIG_EISA
		mp_bus_id_to_type[m->busid] = MP_BUS_ISA;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (म_भेदन(str, BUSTYPE_PCI, माप(BUSTYPE_PCI) - 1) == 0) अणु
		clear_bit(m->busid, mp_bus_not_pci);
#अगर_घोषित CONFIG_EISA
		mp_bus_id_to_type[m->busid] = MP_BUS_PCI;
	पूर्ण अन्यथा अगर (म_भेदन(str, BUSTYPE_EISA, माप(BUSTYPE_EISA) - 1) == 0) अणु
		mp_bus_id_to_type[m->busid] = MP_BUS_EISA;
#पूर्ण_अगर
	पूर्ण अन्यथा
		pr_warn("Unknown bustype %s - ignoring\n", str);
पूर्ण

अटल व्योम __init MP_ioapic_info(काष्ठा mpc_ioapic *m)
अणु
	काष्ठा ioapic_करोमुख्य_cfg cfg = अणु
		.type = IOAPIC_DOMAIN_LEGACY,
		.ops = &mp_ioapic_irqकरोमुख्य_ops,
	पूर्ण;

	अगर (m->flags & MPC_APIC_USABLE)
		mp_रेजिस्टर_ioapic(m->apicid, m->apicaddr, gsi_top, &cfg);
पूर्ण

अटल व्योम __init prपूर्णांक_mp_irq_info(काष्ठा mpc_पूर्णांकsrc *mp_irq)
अणु
	apic_prपूर्णांकk(APIC_VERBOSE,
		"Int: type %d, pol %d, trig %d, bus %02x, IRQ %02x, APIC ID %x, APIC INT %02x\n",
		mp_irq->irqtype, mp_irq->irqflag & 3,
		(mp_irq->irqflag >> 2) & 3, mp_irq->srcbus,
		mp_irq->srcbusirq, mp_irq->dstapic, mp_irq->dstirq);
पूर्ण

#अन्यथा /* CONFIG_X86_IO_APIC */
अटल अंतरभूत व्योम __init MP_bus_info(काष्ठा mpc_bus *m) अणुपूर्ण
अटल अंतरभूत व्योम __init MP_ioapic_info(काष्ठा mpc_ioapic *m) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_X86_IO_APIC */

अटल व्योम __init MP_lपूर्णांकsrc_info(काष्ठा mpc_lपूर्णांकsrc *m)
अणु
	apic_prपूर्णांकk(APIC_VERBOSE,
		"Lint: type %d, pol %d, trig %d, bus %02x, IRQ %02x, APIC ID %x, APIC LINT %02x\n",
		m->irqtype, m->irqflag & 3, (m->irqflag >> 2) & 3, m->srcbusid,
		m->srcbusirq, m->destapic, m->destapiclपूर्णांक);
पूर्ण

/*
 * Read/parse the MPC
 */
अटल पूर्णांक __init smp_check_mpc(काष्ठा mpc_table *mpc, अक्षर *oem, अक्षर *str)
अणु

	अगर (स_भेद(mpc->signature, MPC_SIGNATURE, 4)) अणु
		pr_err("MPTABLE: bad signature [%c%c%c%c]!\n",
		       mpc->signature[0], mpc->signature[1],
		       mpc->signature[2], mpc->signature[3]);
		वापस 0;
	पूर्ण
	अगर (mpf_checksum((अचिन्हित अक्षर *)mpc, mpc->length)) अणु
		pr_err("MPTABLE: checksum error!\n");
		वापस 0;
	पूर्ण
	अगर (mpc->spec != 0x01 && mpc->spec != 0x04) अणु
		pr_err("MPTABLE: bad table version (%d)!!\n", mpc->spec);
		वापस 0;
	पूर्ण
	अगर (!mpc->lapic) अणु
		pr_err("MPTABLE: null local APIC address!\n");
		वापस 0;
	पूर्ण
	स_नकल(oem, mpc->oem, 8);
	oem[8] = 0;
	pr_info("MPTABLE: OEM ID: %s\n", oem);

	स_नकल(str, mpc->productid, 12);
	str[12] = 0;

	pr_info("MPTABLE: Product ID: %s\n", str);

	pr_info("MPTABLE: APIC at: 0x%X\n", mpc->lapic);

	वापस 1;
पूर्ण

अटल व्योम skip_entry(अचिन्हित अक्षर **ptr, पूर्णांक *count, पूर्णांक size)
अणु
	*ptr += size;
	*count += size;
पूर्ण

अटल व्योम __init smp_dump_mptable(काष्ठा mpc_table *mpc, अचिन्हित अक्षर *mpt)
अणु
	pr_err("Your mptable is wrong, contact your HW vendor!\n");
	pr_cont("type %x\n", *mpt);
	prपूर्णांक_hex_dump(KERN_ERR, "  ", DUMP_PREFIX_ADDRESS, 16,
			1, mpc, mpc->length, 1);
पूर्ण

अटल पूर्णांक __init smp_पढ़ो_mpc(काष्ठा mpc_table *mpc, अचिन्हित early)
अणु
	अक्षर str[16];
	अक्षर oem[10];

	पूर्णांक count = माप(*mpc);
	अचिन्हित अक्षर *mpt = ((अचिन्हित अक्षर *)mpc) + count;

	अगर (!smp_check_mpc(mpc, oem, str))
		वापस 0;

	/* Initialize the lapic mapping */
	अगर (!acpi_lapic)
		रेजिस्टर_lapic_address(mpc->lapic);

	अगर (early)
		वापस 1;

	/* Now process the configuration blocks. */
	जबतक (count < mpc->length) अणु
		चयन (*mpt) अणु
		हाल MP_PROCESSOR:
			/* ACPI may have alपढ़ोy provided this data */
			अगर (!acpi_lapic)
				MP_processor_info((काष्ठा mpc_cpu *)mpt);
			skip_entry(&mpt, &count, माप(काष्ठा mpc_cpu));
			अवरोध;
		हाल MP_BUS:
			MP_bus_info((काष्ठा mpc_bus *)mpt);
			skip_entry(&mpt, &count, माप(काष्ठा mpc_bus));
			अवरोध;
		हाल MP_IOAPIC:
			MP_ioapic_info((काष्ठा mpc_ioapic *)mpt);
			skip_entry(&mpt, &count, माप(काष्ठा mpc_ioapic));
			अवरोध;
		हाल MP_INTSRC:
			mp_save_irq((काष्ठा mpc_पूर्णांकsrc *)mpt);
			skip_entry(&mpt, &count, माप(काष्ठा mpc_पूर्णांकsrc));
			अवरोध;
		हाल MP_LINTSRC:
			MP_lपूर्णांकsrc_info((काष्ठा mpc_lपूर्णांकsrc *)mpt);
			skip_entry(&mpt, &count, माप(काष्ठा mpc_lपूर्णांकsrc));
			अवरोध;
		शेष:
			/* wrong mptable */
			smp_dump_mptable(mpc, mpt);
			count = mpc->length;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!num_processors)
		pr_err("MPTABLE: no processors registered!\n");
	वापस num_processors;
पूर्ण

#अगर_घोषित CONFIG_X86_IO_APIC

अटल पूर्णांक __init ELCR_trigger(अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक port;

	port = 0x4d0 + (irq >> 3);
	वापस (inb(port) >> (irq & 7)) & 1;
पूर्ण

अटल व्योम __init स्थिरruct_शेष_ioirq_mptable(पूर्णांक mpc_शेष_type)
अणु
	काष्ठा mpc_पूर्णांकsrc पूर्णांकsrc;
	पूर्णांक i;
	पूर्णांक ELCR_fallback = 0;

	पूर्णांकsrc.type = MP_INTSRC;
	पूर्णांकsrc.irqflag = MP_IRQTRIG_DEFAULT | MP_IRQPOL_DEFAULT;
	पूर्णांकsrc.srcbus = 0;
	पूर्णांकsrc.dstapic = mpc_ioapic_id(0);

	पूर्णांकsrc.irqtype = mp_INT;

	/*
	 *  If true, we have an ISA/PCI प्रणाली with no IRQ entries
	 *  in the MP table. To prevent the PCI पूर्णांकerrupts from being set up
	 *  incorrectly, we try to use the ELCR. The sanity check to see अगर
	 *  there is good ELCR data is very simple - IRQ0, 1, 2 and 13 can
	 *  never be level sensitive, so we simply see अगर the ELCR agrees.
	 *  If it करोes, we assume it's valid.
	 */
	अगर (mpc_शेष_type == 5) अणु
		pr_info("ISA/PCI bus type with no IRQ information... falling back to ELCR\n");

		अगर (ELCR_trigger(0) || ELCR_trigger(1) || ELCR_trigger(2) ||
		    ELCR_trigger(13))
			pr_err("ELCR contains invalid data... not using ELCR\n");
		अन्यथा अणु
			pr_info("Using ELCR to identify PCI interrupts\n");
			ELCR_fallback = 1;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 16; i++) अणु
		चयन (mpc_शेष_type) अणु
		हाल 2:
			अगर (i == 0 || i == 13)
				जारी;	/* IRQ0 & IRQ13 not connected */
			fallthrough;
		शेष:
			अगर (i == 2)
				जारी;	/* IRQ2 is never connected */
		पूर्ण

		अगर (ELCR_fallback) अणु
			/*
			 *  If the ELCR indicates a level-sensitive पूर्णांकerrupt, we
			 *  copy that inक्रमmation over to the MP table in the
			 *  irqflag field (level sensitive, active high polarity).
			 */
			अगर (ELCR_trigger(i)) अणु
				पूर्णांकsrc.irqflag = MP_IRQTRIG_LEVEL |
						 MP_IRQPOL_ACTIVE_HIGH;
			पूर्ण अन्यथा अणु
				पूर्णांकsrc.irqflag = MP_IRQTRIG_DEFAULT |
						 MP_IRQPOL_DEFAULT;
			पूर्ण
		पूर्ण

		पूर्णांकsrc.srcbusirq = i;
		पूर्णांकsrc.dstirq = i ? i : 2;	/* IRQ0 to INTIN2 */
		mp_save_irq(&पूर्णांकsrc);
	पूर्ण

	पूर्णांकsrc.irqtype = mp_ExtINT;
	पूर्णांकsrc.srcbusirq = 0;
	पूर्णांकsrc.dstirq = 0;	/* 8259A to INTIN0 */
	mp_save_irq(&पूर्णांकsrc);
पूर्ण


अटल व्योम __init स्थिरruct_ioapic_table(पूर्णांक mpc_शेष_type)
अणु
	काष्ठा mpc_ioapic ioapic;
	काष्ठा mpc_bus bus;

	bus.type = MP_BUS;
	bus.busid = 0;
	चयन (mpc_शेष_type) अणु
	शेष:
		pr_err("???\nUnknown standard configuration %d\n",
		       mpc_शेष_type);
		fallthrough;
	हाल 1:
	हाल 5:
		स_नकल(bus.bustype, "ISA   ", 6);
		अवरोध;
	हाल 2:
	हाल 6:
	हाल 3:
		स_नकल(bus.bustype, "EISA  ", 6);
		अवरोध;
	पूर्ण
	MP_bus_info(&bus);
	अगर (mpc_शेष_type > 4) अणु
		bus.busid = 1;
		स_नकल(bus.bustype, "PCI   ", 6);
		MP_bus_info(&bus);
	पूर्ण

	ioapic.type	= MP_IOAPIC;
	ioapic.apicid	= 2;
	ioapic.apicver	= mpc_शेष_type > 4 ? 0x10 : 0x01;
	ioapic.flags	= MPC_APIC_USABLE;
	ioapic.apicaddr	= IO_APIC_DEFAULT_PHYS_BASE;
	MP_ioapic_info(&ioapic);

	/*
	 * We set up most of the low 16 IO-APIC pins according to MPS rules.
	 */
	स्थिरruct_शेष_ioirq_mptable(mpc_शेष_type);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __init स्थिरruct_ioapic_table(पूर्णांक mpc_शेष_type) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम __init स्थिरruct_शेष_ISA_mptable(पूर्णांक mpc_शेष_type)
अणु
	काष्ठा mpc_cpu processor;
	काष्ठा mpc_lपूर्णांकsrc lपूर्णांकsrc;
	पूर्णांक lपूर्णांकtypes[2] = अणु mp_ExtINT, mp_NMI पूर्ण;
	पूर्णांक i;

	/*
	 * local APIC has शेष address
	 */
	mp_lapic_addr = APIC_DEFAULT_PHYS_BASE;

	/*
	 * 2 CPUs, numbered 0 & 1.
	 */
	processor.type = MP_PROCESSOR;
	/* Either an पूर्णांकegrated APIC or a discrete 82489DX. */
	processor.apicver = mpc_शेष_type > 4 ? 0x10 : 0x01;
	processor.cpuflag = CPU_ENABLED;
	processor.cpufeature = (boot_cpu_data.x86 << 8) |
	    (boot_cpu_data.x86_model << 4) | boot_cpu_data.x86_stepping;
	processor.featureflag = boot_cpu_data.x86_capability[CPUID_1_EDX];
	processor.reserved[0] = 0;
	processor.reserved[1] = 0;
	क्रम (i = 0; i < 2; i++) अणु
		processor.apicid = i;
		MP_processor_info(&processor);
	पूर्ण

	स्थिरruct_ioapic_table(mpc_शेष_type);

	lपूर्णांकsrc.type = MP_LINTSRC;
	lपूर्णांकsrc.irqflag = MP_IRQTRIG_DEFAULT | MP_IRQPOL_DEFAULT;
	lपूर्णांकsrc.srcbusid = 0;
	lपूर्णांकsrc.srcbusirq = 0;
	lपूर्णांकsrc.destapic = MP_APIC_ALL;
	क्रम (i = 0; i < 2; i++) अणु
		lपूर्णांकsrc.irqtype = lपूर्णांकtypes[i];
		lपूर्णांकsrc.destapiclपूर्णांक = i;
		MP_lपूर्णांकsrc_info(&lपूर्णांकsrc);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ mpf_base;
अटल bool mpf_found;

अटल अचिन्हित दीर्घ __init get_mpc_size(अचिन्हित दीर्घ physptr)
अणु
	काष्ठा mpc_table *mpc;
	अचिन्हित दीर्घ size;

	mpc = early_memremap(physptr, PAGE_SIZE);
	size = mpc->length;
	early_memunmap(mpc, PAGE_SIZE);
	apic_prपूर्णांकk(APIC_VERBOSE, "  mpc: %lx-%lx\n", physptr, physptr + size);

	वापस size;
पूर्ण

अटल पूर्णांक __init check_physptr(काष्ठा mpf_पूर्णांकel *mpf, अचिन्हित पूर्णांक early)
अणु
	काष्ठा mpc_table *mpc;
	अचिन्हित दीर्घ size;

	size = get_mpc_size(mpf->physptr);
	mpc = early_memremap(mpf->physptr, size);

	/*
	 * Read the physical hardware table.  Anything here will
	 * override the शेषs.
	 */
	अगर (!smp_पढ़ो_mpc(mpc, early)) अणु
#अगर_घोषित CONFIG_X86_LOCAL_APIC
		smp_found_config = 0;
#पूर्ण_अगर
		pr_err("BIOS bug, MP table errors detected!...\n");
		pr_cont("... disabling SMP support. (tell your hw vendor)\n");
		early_memunmap(mpc, size);
		वापस -1;
	पूर्ण
	early_memunmap(mpc, size);

	अगर (early)
		वापस -1;

#अगर_घोषित CONFIG_X86_IO_APIC
	/*
	 * If there are no explicit MP IRQ entries, then we are
	 * broken.  We set up most of the low 16 IO-APIC pins to
	 * ISA शेषs and hope it will work.
	 */
	अगर (!mp_irq_entries) अणु
		काष्ठा mpc_bus bus;

		pr_err("BIOS bug, no explicit IRQ entries, using default mptable. (tell your hw vendor)\n");

		bus.type = MP_BUS;
		bus.busid = 0;
		स_नकल(bus.bustype, "ISA   ", 6);
		MP_bus_info(&bus);

		स्थिरruct_शेष_ioirq_mptable(0);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * Scan the memory blocks क्रम an SMP configuration block.
 */
व्योम __init शेष_get_smp_config(अचिन्हित पूर्णांक early)
अणु
	काष्ठा mpf_पूर्णांकel *mpf;

	अगर (!smp_found_config)
		वापस;

	अगर (!mpf_found)
		वापस;

	अगर (acpi_lapic && early)
		वापस;

	/*
	 * MPS करोesn't support hyperthपढ़ोing, aka only have
	 * thपढ़ो 0 apic id in MPS table
	 */
	अगर (acpi_lapic && acpi_ioapic)
		वापस;

	mpf = early_memremap(mpf_base, माप(*mpf));
	अगर (!mpf) अणु
		pr_err("MPTABLE: error mapping MP table\n");
		वापस;
	पूर्ण

	pr_info("Intel MultiProcessor Specification v1.%d\n",
		mpf->specअगरication);
#अगर defined(CONFIG_X86_LOCAL_APIC) && defined(CONFIG_X86_32)
	अगर (mpf->feature2 & (1 << 7)) अणु
		pr_info("    IMCR and PIC compatibility mode.\n");
		pic_mode = 1;
	पूर्ण अन्यथा अणु
		pr_info("    Virtual Wire compatibility mode.\n");
		pic_mode = 0;
	पूर्ण
#पूर्ण_अगर
	/*
	 * Now see अगर we need to पढ़ो further.
	 */
	अगर (mpf->feature1) अणु
		अगर (early) अणु
			/*
			 * local APIC has शेष address
			 */
			mp_lapic_addr = APIC_DEFAULT_PHYS_BASE;
			जाओ out;
		पूर्ण

		pr_info("Default MP configuration #%d\n", mpf->feature1);
		स्थिरruct_शेष_ISA_mptable(mpf->feature1);

	पूर्ण अन्यथा अगर (mpf->physptr) अणु
		अगर (check_physptr(mpf, early))
			जाओ out;
	पूर्ण अन्यथा
		BUG();

	अगर (!early)
		pr_info("Processors: %d\n", num_processors);
	/*
	 * Only use the first configuration found.
	 */
out:
	early_memunmap(mpf, माप(*mpf));
पूर्ण

अटल व्योम __init smp_reserve_memory(काष्ठा mpf_पूर्णांकel *mpf)
अणु
	memblock_reserve(mpf->physptr, get_mpc_size(mpf->physptr));
पूर्ण

अटल पूर्णांक __init smp_scan_config(अचिन्हित दीर्घ base, अचिन्हित दीर्घ length)
अणु
	अचिन्हित पूर्णांक *bp;
	काष्ठा mpf_पूर्णांकel *mpf;
	पूर्णांक ret = 0;

	apic_prपूर्णांकk(APIC_VERBOSE, "Scan for SMP in [mem %#010lx-%#010lx]\n",
		    base, base + length - 1);
	BUILD_BUG_ON(माप(*mpf) != 16);

	जबतक (length > 0) अणु
		bp = early_memremap(base, length);
		mpf = (काष्ठा mpf_पूर्णांकel *)bp;
		अगर ((*bp == SMP_MAGIC_IDENT) &&
		    (mpf->length == 1) &&
		    !mpf_checksum((अचिन्हित अक्षर *)bp, 16) &&
		    ((mpf->specअगरication == 1)
		     || (mpf->specअगरication == 4))) अणु
#अगर_घोषित CONFIG_X86_LOCAL_APIC
			smp_found_config = 1;
#पूर्ण_अगर
			mpf_base = base;
			mpf_found = true;

			pr_info("found SMP MP-table at [mem %#010lx-%#010lx]\n",
				base, base + माप(*mpf) - 1);

			memblock_reserve(base, माप(*mpf));
			अगर (mpf->physptr)
				smp_reserve_memory(mpf);

			ret = 1;
		पूर्ण
		early_memunmap(bp, length);

		अगर (ret)
			अवरोध;

		base += 16;
		length -= 16;
	पूर्ण
	वापस ret;
पूर्ण

व्योम __init शेष_find_smp_config(व्योम)
अणु
	अचिन्हित पूर्णांक address;

	/*
	 * FIXME: Linux assumes you have 640K of base ram..
	 * this जारीs the error...
	 *
	 * 1) Scan the bottom 1K क्रम a signature
	 * 2) Scan the top 1K of base RAM
	 * 3) Scan the 64K of bios
	 */
	अगर (smp_scan_config(0x0, 0x400) ||
	    smp_scan_config(639 * 0x400, 0x400) ||
	    smp_scan_config(0xF0000, 0x10000))
		वापस;
	/*
	 * If it is an SMP machine we should know now, unless the
	 * configuration is in an EISA bus machine with an
	 * extended bios data area.
	 *
	 * there is a real-mode segmented poपूर्णांकer poपूर्णांकing to the
	 * 4K EBDA area at 0x40E, calculate and scan it here.
	 *
	 * NOTE! There are Linux loaders that will corrupt the EBDA
	 * area, and as such this kind of SMP config may be less
	 * trustworthy, simply because the SMP table may have been
	 * stomped on during early boot. These loaders are buggy and
	 * should be fixed.
	 *
	 * MP1.4 SPEC states to only scan first 1K of 4K EBDA.
	 */

	address = get_bios_ebda();
	अगर (address)
		smp_scan_config(address, 0x400);
पूर्ण

#अगर_घोषित CONFIG_X86_IO_APIC
अटल u8 __initdata irq_used[MAX_IRQ_SOURCES];

अटल पूर्णांक  __init get_MP_पूर्णांकsrc_index(काष्ठा mpc_पूर्णांकsrc *m)
अणु
	पूर्णांक i;

	अगर (m->irqtype != mp_INT)
		वापस 0;

	अगर (m->irqflag != (MP_IRQTRIG_LEVEL | MP_IRQPOL_ACTIVE_LOW))
		वापस 0;

	/* not legacy */

	क्रम (i = 0; i < mp_irq_entries; i++) अणु
		अगर (mp_irqs[i].irqtype != mp_INT)
			जारी;

		अगर (mp_irqs[i].irqflag != (MP_IRQTRIG_LEVEL |
					   MP_IRQPOL_ACTIVE_LOW))
			जारी;

		अगर (mp_irqs[i].srcbus != m->srcbus)
			जारी;
		अगर (mp_irqs[i].srcbusirq != m->srcbusirq)
			जारी;
		अगर (irq_used[i]) अणु
			/* alपढ़ोy claimed */
			वापस -2;
		पूर्ण
		irq_used[i] = 1;
		वापस i;
	पूर्ण

	/* not found */
	वापस -1;
पूर्ण

#घोषणा SPARE_SLOT_NUM 20

अटल काष्ठा mpc_पूर्णांकsrc __initdata *m_spare[SPARE_SLOT_NUM];

अटल व्योम __init check_irq_src(काष्ठा mpc_पूर्णांकsrc *m, पूर्णांक *nr_m_spare)
अणु
	पूर्णांक i;

	apic_prपूर्णांकk(APIC_VERBOSE, "OLD ");
	prपूर्णांक_mp_irq_info(m);

	i = get_MP_पूर्णांकsrc_index(m);
	अगर (i > 0) अणु
		स_नकल(m, &mp_irqs[i], माप(*m));
		apic_prपूर्णांकk(APIC_VERBOSE, "NEW ");
		prपूर्णांक_mp_irq_info(&mp_irqs[i]);
		वापस;
	पूर्ण
	अगर (!i) अणु
		/* legacy, करो nothing */
		वापस;
	पूर्ण
	अगर (*nr_m_spare < SPARE_SLOT_NUM) अणु
		/*
		 * not found (-1), or duplicated (-2) are invalid entries,
		 * we need to use the slot later
		 */
		m_spare[*nr_m_spare] = m;
		*nr_m_spare += 1;
	पूर्ण
पूर्ण

अटल पूर्णांक __init
check_slot(अचिन्हित दीर्घ mpc_new_phys, अचिन्हित दीर्घ mpc_new_length, पूर्णांक count)
अणु
	अगर (!mpc_new_phys || count <= mpc_new_length) अणु
		WARN(1, "update_mptable: No spare slots (length: %x)\n", count);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_X86_IO_APIC */
अटल
अंतरभूत व्योम __init check_irq_src(काष्ठा mpc_पूर्णांकsrc *m, पूर्णांक *nr_m_spare) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_X86_IO_APIC */

अटल पूर्णांक  __init replace_पूर्णांकsrc_all(काष्ठा mpc_table *mpc,
					अचिन्हित दीर्घ mpc_new_phys,
					अचिन्हित दीर्घ mpc_new_length)
अणु
#अगर_घोषित CONFIG_X86_IO_APIC
	पूर्णांक i;
#पूर्ण_अगर
	पूर्णांक count = माप(*mpc);
	पूर्णांक nr_m_spare = 0;
	अचिन्हित अक्षर *mpt = ((अचिन्हित अक्षर *)mpc) + count;

	pr_info("mpc_length %x\n", mpc->length);
	जबतक (count < mpc->length) अणु
		चयन (*mpt) अणु
		हाल MP_PROCESSOR:
			skip_entry(&mpt, &count, माप(काष्ठा mpc_cpu));
			अवरोध;
		हाल MP_BUS:
			skip_entry(&mpt, &count, माप(काष्ठा mpc_bus));
			अवरोध;
		हाल MP_IOAPIC:
			skip_entry(&mpt, &count, माप(काष्ठा mpc_ioapic));
			अवरोध;
		हाल MP_INTSRC:
			check_irq_src((काष्ठा mpc_पूर्णांकsrc *)mpt, &nr_m_spare);
			skip_entry(&mpt, &count, माप(काष्ठा mpc_पूर्णांकsrc));
			अवरोध;
		हाल MP_LINTSRC:
			skip_entry(&mpt, &count, माप(काष्ठा mpc_lपूर्णांकsrc));
			अवरोध;
		शेष:
			/* wrong mptable */
			smp_dump_mptable(mpc, mpt);
			जाओ out;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_X86_IO_APIC
	क्रम (i = 0; i < mp_irq_entries; i++) अणु
		अगर (irq_used[i])
			जारी;

		अगर (mp_irqs[i].irqtype != mp_INT)
			जारी;

		अगर (mp_irqs[i].irqflag != (MP_IRQTRIG_LEVEL |
					   MP_IRQPOL_ACTIVE_LOW))
			जारी;

		अगर (nr_m_spare > 0) अणु
			apic_prपूर्णांकk(APIC_VERBOSE, "*NEW* found\n");
			nr_m_spare--;
			स_नकल(m_spare[nr_m_spare], &mp_irqs[i], माप(mp_irqs[i]));
			m_spare[nr_m_spare] = शून्य;
		पूर्ण अन्यथा अणु
			काष्ठा mpc_पूर्णांकsrc *m = (काष्ठा mpc_पूर्णांकsrc *)mpt;
			count += माप(काष्ठा mpc_पूर्णांकsrc);
			अगर (check_slot(mpc_new_phys, mpc_new_length, count) < 0)
				जाओ out;
			स_नकल(m, &mp_irqs[i], माप(*m));
			mpc->length = count;
			mpt += माप(काष्ठा mpc_पूर्णांकsrc);
		पूर्ण
		prपूर्णांक_mp_irq_info(&mp_irqs[i]);
	पूर्ण
#पूर्ण_अगर
out:
	/* update checksum */
	mpc->checksum = 0;
	mpc->checksum -= mpf_checksum((अचिन्हित अक्षर *)mpc, mpc->length);

	वापस 0;
पूर्ण

पूर्णांक enable_update_mptable;

अटल पूर्णांक __init update_mptable_setup(अक्षर *str)
अणु
	enable_update_mptable = 1;
#अगर_घोषित CONFIG_PCI
	pci_routeirq = 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण
early_param("update_mptable", update_mptable_setup);

अटल अचिन्हित दीर्घ __initdata mpc_new_phys;
अटल अचिन्हित दीर्घ mpc_new_length __initdata = 4096;

/* alloc_mptable or alloc_mptable=4k */
अटल पूर्णांक __initdata alloc_mptable;
अटल पूर्णांक __init parse_alloc_mptable_opt(अक्षर *p)
अणु
	enable_update_mptable = 1;
#अगर_घोषित CONFIG_PCI
	pci_routeirq = 1;
#पूर्ण_अगर
	alloc_mptable = 1;
	अगर (!p)
		वापस 0;
	mpc_new_length = memparse(p, &p);
	वापस 0;
पूर्ण
early_param("alloc_mptable", parse_alloc_mptable_opt);

व्योम __init e820__memblock_alloc_reserved_mpc_new(व्योम)
अणु
	अगर (enable_update_mptable && alloc_mptable)
		mpc_new_phys = e820__memblock_alloc_reserved(mpc_new_length, 4);
पूर्ण

अटल पूर्णांक __init update_mp_table(व्योम)
अणु
	अक्षर str[16];
	अक्षर oem[10];
	काष्ठा mpf_पूर्णांकel *mpf;
	काष्ठा mpc_table *mpc, *mpc_new;
	अचिन्हित दीर्घ size;

	अगर (!enable_update_mptable)
		वापस 0;

	अगर (!mpf_found)
		वापस 0;

	mpf = early_memremap(mpf_base, माप(*mpf));
	अगर (!mpf) अणु
		pr_err("MPTABLE: mpf early_memremap() failed\n");
		वापस 0;
	पूर्ण

	/*
	 * Now see अगर we need to go further.
	 */
	अगर (mpf->feature1)
		जाओ करो_unmap_mpf;

	अगर (!mpf->physptr)
		जाओ करो_unmap_mpf;

	size = get_mpc_size(mpf->physptr);
	mpc = early_memremap(mpf->physptr, size);
	अगर (!mpc) अणु
		pr_err("MPTABLE: mpc early_memremap() failed\n");
		जाओ करो_unmap_mpf;
	पूर्ण

	अगर (!smp_check_mpc(mpc, oem, str))
		जाओ करो_unmap_mpc;

	pr_info("mpf: %llx\n", (u64)mpf_base);
	pr_info("physptr: %x\n", mpf->physptr);

	अगर (mpc_new_phys && mpc->length > mpc_new_length) अणु
		mpc_new_phys = 0;
		pr_info("mpc_new_length is %ld, please use alloc_mptable=8k\n",
			mpc_new_length);
	पूर्ण

	अगर (!mpc_new_phys) अणु
		अचिन्हित अक्षर old, new;
		/* check अगर we can change the position */
		mpc->checksum = 0;
		old = mpf_checksum((अचिन्हित अक्षर *)mpc, mpc->length);
		mpc->checksum = 0xff;
		new = mpf_checksum((अचिन्हित अक्षर *)mpc, mpc->length);
		अगर (old == new) अणु
			pr_info("mpc is readonly, please try alloc_mptable instead\n");
			जाओ करो_unmap_mpc;
		पूर्ण
		pr_info("use in-position replacing\n");
	पूर्ण अन्यथा अणु
		mpc_new = early_memremap(mpc_new_phys, mpc_new_length);
		अगर (!mpc_new) अणु
			pr_err("MPTABLE: new mpc early_memremap() failed\n");
			जाओ करो_unmap_mpc;
		पूर्ण
		mpf->physptr = mpc_new_phys;
		स_नकल(mpc_new, mpc, mpc->length);
		early_memunmap(mpc, size);
		mpc = mpc_new;
		size = mpc_new_length;
		/* check अगर we can modअगरy that */
		अगर (mpc_new_phys - mpf->physptr) अणु
			काष्ठा mpf_पूर्णांकel *mpf_new;
			/* steal 16 bytes from [0, 1k) */
			mpf_new = early_memremap(0x400 - 16, माप(*mpf_new));
			अगर (!mpf_new) अणु
				pr_err("MPTABLE: new mpf early_memremap() failed\n");
				जाओ करो_unmap_mpc;
			पूर्ण
			pr_info("mpf new: %x\n", 0x400 - 16);
			स_नकल(mpf_new, mpf, 16);
			early_memunmap(mpf, माप(*mpf));
			mpf = mpf_new;
			mpf->physptr = mpc_new_phys;
		पूर्ण
		mpf->checksum = 0;
		mpf->checksum -= mpf_checksum((अचिन्हित अक्षर *)mpf, 16);
		pr_info("physptr new: %x\n", mpf->physptr);
	पूर्ण

	/*
	 * only replace the one with mp_INT and
	 *	 MP_IRQ_TRIGGER_LEVEL|MP_IRQ_POLARITY_LOW,
	 * alपढ़ोy in mp_irqs , stored by ... and mp_config_acpi_gsi,
	 * may need pci=routeirq क्रम all coverage
	 */
	replace_पूर्णांकsrc_all(mpc, mpc_new_phys, mpc_new_length);

करो_unmap_mpc:
	early_memunmap(mpc, size);

करो_unmap_mpf:
	early_memunmap(mpf, माप(*mpf));

	वापस 0;
पूर्ण

late_initcall(update_mp_table);
