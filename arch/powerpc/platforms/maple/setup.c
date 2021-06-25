<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Maple (970 eval board) setup code
 *
 *  (c) Copyright 2004 Benjamin Herrenschmidt (benh@kernel.crashing.org),
 *                     IBM Corp. 
 */

#अघोषित DEBUG

#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/tty.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/major.h>
#समावेश <linux/initrd.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/console.h>
#समावेश <linux/pci.h>
#समावेश <linux/adb.h>
#समावेश <linux/cuda.h>
#समावेश <linux/pmu.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/serial.h>
#समावेश <linux/smp.h>
#समावेश <linux/bitops.h>
#समावेश <linux/of_device.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/nvram.h>

#समावेश "maple.h"

#अगर_घोषित DEBUG
#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

अटल अचिन्हित दीर्घ maple_find_nvram_base(व्योम)
अणु
	काष्ठा device_node *rtcs;
	अचिन्हित दीर्घ result = 0;

	/* find NVRAM device */
	rtcs = of_find_compatible_node(शून्य, "nvram", "AMD8111");
	अगर (rtcs) अणु
		काष्ठा resource r;
		अगर (of_address_to_resource(rtcs, 0, &r)) अणु
			prपूर्णांकk(KERN_EMERG "Maple: Unable to translate NVRAM"
			       " address\n");
			जाओ bail;
		पूर्ण
		अगर (!(r.flags & IORESOURCE_IO)) अणु
			prपूर्णांकk(KERN_EMERG "Maple: NVRAM address isn't PIO!\n");
			जाओ bail;
		पूर्ण
		result = r.start;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_EMERG "Maple: Unable to find NVRAM\n");
 bail:
	of_node_put(rtcs);
	वापस result;
पूर्ण

अटल व्योम __noवापस maple_restart(अक्षर *cmd)
अणु
	अचिन्हित पूर्णांक maple_nvram_base;
	स्थिर अचिन्हित पूर्णांक *maple_nvram_offset, *maple_nvram_command;
	काष्ठा device_node *sp;

	maple_nvram_base = maple_find_nvram_base();
	अगर (maple_nvram_base == 0)
		जाओ fail;

	/* find service processor device */
	sp = of_find_node_by_name(शून्य, "service-processor");
	अगर (!sp) अणु
		prपूर्णांकk(KERN_EMERG "Maple: Unable to find Service Processor\n");
		जाओ fail;
	पूर्ण
	maple_nvram_offset = of_get_property(sp, "restart-addr", शून्य);
	maple_nvram_command = of_get_property(sp, "restart-value", शून्य);
	of_node_put(sp);

	/* send command */
	outb_p(*maple_nvram_command, maple_nvram_base + *maple_nvram_offset);
	क्रम (;;) ;
 fail:
	prपूर्णांकk(KERN_EMERG "Maple: Manual Restart Required\n");
	क्रम (;;) ;
पूर्ण

अटल व्योम __noवापस maple_घातer_off(व्योम)
अणु
	अचिन्हित पूर्णांक maple_nvram_base;
	स्थिर अचिन्हित पूर्णांक *maple_nvram_offset, *maple_nvram_command;
	काष्ठा device_node *sp;

	maple_nvram_base = maple_find_nvram_base();
	अगर (maple_nvram_base == 0)
		जाओ fail;

	/* find service processor device */
	sp = of_find_node_by_name(शून्य, "service-processor");
	अगर (!sp) अणु
		prपूर्णांकk(KERN_EMERG "Maple: Unable to find Service Processor\n");
		जाओ fail;
	पूर्ण
	maple_nvram_offset = of_get_property(sp, "power-off-addr", शून्य);
	maple_nvram_command = of_get_property(sp, "power-off-value", शून्य);
	of_node_put(sp);

	/* send command */
	outb_p(*maple_nvram_command, maple_nvram_base + *maple_nvram_offset);
	क्रम (;;) ;
 fail:
	prपूर्णांकk(KERN_EMERG "Maple: Manual Power-Down Required\n");
	क्रम (;;) ;
पूर्ण

अटल व्योम __noवापस maple_halt(व्योम)
अणु
	maple_घातer_off();
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल काष्ठा smp_ops_t maple_smp_ops = अणु
	.probe		= smp_mpic_probe,
	.message_pass	= smp_mpic_message_pass,
	.kick_cpu	= smp_generic_kick_cpu,
	.setup_cpu	= smp_mpic_setup_cpu,
	.give_समयbase	= smp_generic_give_समयbase,
	.take_समयbase	= smp_generic_take_समयbase,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम __init maple_use_rtas_reboot_and_halt_अगर_present(व्योम)
अणु
	अगर (rtas_service_present("system-reboot") &&
	    rtas_service_present("power-off")) अणु
		ppc_md.restart = rtas_restart;
		pm_घातer_off = rtas_घातer_off;
		ppc_md.halt = rtas_halt;
	पूर्ण
पूर्ण

अटल व्योम __init maple_setup_arch(व्योम)
अणु
	/* init to some ~sane value until calibrate_delay() runs */
	loops_per_jअगरfy = 50000000;

	/* Setup SMP callback */
#अगर_घोषित CONFIG_SMP
	smp_ops = &maple_smp_ops;
#पूर्ण_अगर
	maple_use_rtas_reboot_and_halt_अगर_present();

	prपूर्णांकk(KERN_DEBUG "Using native/NAP idle loop\n");

	mmio_nvram_init();
पूर्ण

/*
 * This is almost identical to pSeries and CHRP. We need to make that
 * code generic at one poपूर्णांक, with appropriate bits in the device-tree to
 * identअगरy the presence of an HT APIC
 */
अटल व्योम __init maple_init_IRQ(व्योम)
अणु
	काष्ठा device_node *root, *np, *mpic_node = शून्य;
	स्थिर अचिन्हित पूर्णांक *opprop;
	अचिन्हित दीर्घ खोलोpic_addr = 0;
	पूर्णांक naddr, n, i, opplen, has_isus = 0;
	काष्ठा mpic *mpic;
	अचिन्हित पूर्णांक flags = 0;

	/* Locate MPIC in the device-tree. Note that there is a bug
	 * in Maple device-tree where the type of the controller is
	 * खोलो-pic and not पूर्णांकerrupt-controller
	 */

	क्रम_each_node_by_type(np, "interrupt-controller")
		अगर (of_device_is_compatible(np, "open-pic")) अणु
			mpic_node = np;
			अवरोध;
		पूर्ण
	अगर (mpic_node == शून्य)
		क्रम_each_node_by_type(np, "open-pic") अणु
			mpic_node = np;
			अवरोध;
		पूर्ण
	अगर (mpic_node == शून्य) अणु
		prपूर्णांकk(KERN_ERR
		       "Failed to locate the MPIC interrupt controller\n");
		वापस;
	पूर्ण

	/* Find address list in /platक्रमm-खोलो-pic */
	root = of_find_node_by_path("/");
	naddr = of_n_addr_cells(root);
	opprop = of_get_property(root, "platform-open-pic", &opplen);
	अगर (opprop) अणु
		खोलोpic_addr = of_पढ़ो_number(opprop, naddr);
		has_isus = (opplen > naddr);
		prपूर्णांकk(KERN_DEBUG "OpenPIC addr: %lx, has ISUs: %d\n",
		       खोलोpic_addr, has_isus);
	पूर्ण

	BUG_ON(खोलोpic_addr == 0);

	/* Check क्रम a big endian MPIC */
	अगर (of_get_property(np, "big-endian", शून्य) != शून्य)
		flags |= MPIC_BIG_ENDIAN;

	/* XXX Maple specअगरic bits */
	flags |= MPIC_U3_HT_IRQS;
	/* All U3/U4 are big-endian, older SLOF firmware करोesn't encode this */
	flags |= MPIC_BIG_ENDIAN;

	/* Setup the खोलोpic driver. More device-tree junks, we hard code no
	 * ISUs क्रम now. I'll have to revisit some stuffs with the folks करोing
	 * the firmware क्रम those
	 */
	mpic = mpic_alloc(mpic_node, खोलोpic_addr, flags,
			  /*has_isus ? 16 :*/ 0, 0, " MPIC     ");
	BUG_ON(mpic == शून्य);

	/* Add ISUs */
	opplen /= माप(u32);
	क्रम (n = 0, i = naddr; i < opplen; i += naddr, n++) अणु
		अचिन्हित दीर्घ isuaddr = of_पढ़ो_number(opprop + i, naddr);
		mpic_assign_isu(mpic, n, isuaddr);
	पूर्ण

	/* All ISUs are setup, complete initialization */
	mpic_init(mpic);
	ppc_md.get_irq = mpic_get_irq;
	of_node_put(mpic_node);
	of_node_put(root);
पूर्ण

अटल व्योम __init maple_progress(अक्षर *s, अचिन्हित लघु hex)
अणु
	prपूर्णांकk("*** %04x : %s\n", hex, s ? s : "");
पूर्ण


/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init maple_probe(व्योम)
अणु
	अगर (!of_machine_is_compatible("Momentum,Maple") &&
	    !of_machine_is_compatible("Momentum,Apache"))
		वापस 0;

	pm_घातer_off = maple_घातer_off;

	iommu_init_early_dart(&maple_pci_controller_ops);

	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_EDAC
/*
 * Register a platक्रमm device क्रम CPC925 memory controller on
 * all boards with U3H (CPC925) bridge.
 */
अटल पूर्णांक __init maple_cpc925_edac_setup(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np = शून्य;
	काष्ठा resource r;
	पूर्णांक ret;
	अस्थिर व्योम __iomem *mem;
	u32 rev;

	np = of_find_node_by_type(शून्य, "memory-controller");
	अगर (!np) अणु
		prपूर्णांकk(KERN_ERR "%s: Unable to find memory-controller node\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	ret = of_address_to_resource(np, 0, &r);
	of_node_put(np);

	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Unable to get memory-controller reg\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	mem = ioremap(r.start, resource_size(&r));
	अगर (!mem) अणु
		prपूर्णांकk(KERN_ERR "%s: Unable to map memory-controller memory\n",
				__func__);
		वापस -ENOMEM;
	पूर्ण

	rev = __raw_पढ़ोl(mem);
	iounmap(mem);

	अगर (rev < 0x34 || rev > 0x3f) अणु /* U3H */
		prपूर्णांकk(KERN_ERR "%s: Non-CPC925(U3H) bridge revision: %02x\n",
			__func__, rev);
		वापस 0;
	पूर्ण

	pdev = platक्रमm_device_रेजिस्टर_simple("cpc925_edac", 0, &r, 1);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	prपूर्णांकk(KERN_INFO "%s: CPC925 platform device created\n", __func__);

	वापस 0;
पूर्ण
machine_device_initcall(maple, maple_cpc925_edac_setup);
#पूर्ण_अगर

define_machine(maple) अणु
	.name			= "Maple",
	.probe			= maple_probe,
	.setup_arch		= maple_setup_arch,
	.discover_phbs		= maple_pci_init,
	.init_IRQ		= maple_init_IRQ,
	.pci_irq_fixup		= maple_pci_irq_fixup,
	.pci_get_legacy_ide_irq	= maple_pci_get_legacy_ide_irq,
	.restart		= maple_restart,
	.halt			= maple_halt,
	.get_boot_समय		= maple_get_boot_समय,
	.set_rtc_समय		= maple_set_rtc_समय,
	.get_rtc_समय		= maple_get_rtc_समय,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= maple_progress,
	.घातer_save		= घातer4_idle,
पूर्ण;
