<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2006-2008, IBM Corporation.
 */

#अघोषित DEBUG

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/reboot.h>
#समावेश <linux/kexec.h>
#समावेश <linux/crash_dump.h>

#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/cell-regs.h>

#समावेश "ras.h"


अटल व्योम dump_fir(पूर्णांक cpu)
अणु
	काष्ठा cbe_pmd_regs __iomem *pregs = cbe_get_cpu_pmd_regs(cpu);
	काष्ठा cbe_iic_regs __iomem *iregs = cbe_get_cpu_iic_regs(cpu);

	अगर (pregs == शून्य)
		वापस;

	/* Toकरो: करो some nicer parsing of bits and based on them go करोwn
	 * to other sub-units FIRs and not only IIC
	 */
	prपूर्णांकk(KERN_ERR "Global Checkstop FIR    : 0x%016llx\n",
	       in_be64(&pregs->checkstop_fir));
	prपूर्णांकk(KERN_ERR "Global Recoverable FIR  : 0x%016llx\n",
	       in_be64(&pregs->checkstop_fir));
	prपूर्णांकk(KERN_ERR "Global MachineCheck FIR : 0x%016llx\n",
	       in_be64(&pregs->spec_att_mchk_fir));

	अगर (iregs == शून्य)
		वापस;
	prपूर्णांकk(KERN_ERR "IOC FIR                 : 0x%016llx\n",
	       in_be64(&iregs->ioc_fir));

पूर्ण

DEFINE_INTERRUPT_HANDLER(cbe_प्रणाली_error_exception)
अणु
	पूर्णांक cpu = smp_processor_id();

	prपूर्णांकk(KERN_ERR "System Error Interrupt on CPU %d !\n", cpu);
	dump_fir(cpu);
	dump_stack();
पूर्ण

DEFINE_INTERRUPT_HANDLER(cbe_मुख्यtenance_exception)
अणु
	पूर्णांक cpu = smp_processor_id();

	/*
	 * Nothing implemented क्रम the मुख्यtenance पूर्णांकerrupt at this poपूर्णांक
	 */

	prपूर्णांकk(KERN_ERR "Unhandled Maintenance interrupt on CPU %d !\n", cpu);
	dump_stack();
पूर्ण

DEFINE_INTERRUPT_HANDLER(cbe_thermal_exception)
अणु
	पूर्णांक cpu = smp_processor_id();

	/*
	 * Nothing implemented क्रम the thermal पूर्णांकerrupt at this poपूर्णांक
	 */

	prपूर्णांकk(KERN_ERR "Unhandled Thermal interrupt on CPU %d !\n", cpu);
	dump_stack();
पूर्ण

अटल पूर्णांक cbe_machine_check_handler(काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu = smp_processor_id();

	prपूर्णांकk(KERN_ERR "Machine Check Interrupt on CPU %d !\n", cpu);
	dump_fir(cpu);

	/* No recovery from this code now, lets जारी */
	वापस 0;
पूर्ण

काष्ठा ptcal_area अणु
	काष्ठा list_head list;
	पूर्णांक nid;
	पूर्णांक order;
	काष्ठा page *pages;
पूर्ण;

अटल LIST_HEAD(ptcal_list);

अटल पूर्णांक ptcal_start_tok, ptcal_stop_tok;

अटल पूर्णांक __init cbe_ptcal_enable_on_node(पूर्णांक nid, पूर्णांक order)
अणु
	काष्ठा ptcal_area *area;
	पूर्णांक ret = -ENOMEM;
	अचिन्हित दीर्घ addr;

	अगर (is_kdump_kernel())
		rtas_call(ptcal_stop_tok, 1, 1, शून्य, nid);

	area = kदो_स्मृति(माप(*area), GFP_KERNEL);
	अगर (!area)
		जाओ out_err;

	area->nid = nid;
	area->order = order;
	area->pages = __alloc_pages_node(area->nid,
						GFP_KERNEL|__GFP_THISNODE,
						area->order);

	अगर (!area->pages) अणु
		prपूर्णांकk(KERN_WARNING "%s: no page on node %d\n",
			__func__, area->nid);
		जाओ out_मुक्त_area;
	पूर्ण

	/*
	 * We move the ptcal area to the middle of the allocated
	 * page, in order to aव्योम prefetches in स_नकल and similar
	 * functions stepping on it.
	 */
	addr = __pa(page_address(area->pages)) + (PAGE_SIZE >> 1);
	prपूर्णांकk(KERN_DEBUG "%s: enabling PTCAL on node %d address=0x%016lx\n",
			__func__, area->nid, addr);

	ret = -EIO;
	अगर (rtas_call(ptcal_start_tok, 3, 1, शून्य, area->nid,
				(अचिन्हित पूर्णांक)(addr >> 32),
				(अचिन्हित पूर्णांक)(addr & 0xffffffff))) अणु
		prपूर्णांकk(KERN_ERR "%s: error enabling PTCAL on node %d!\n",
				__func__, nid);
		जाओ out_मुक्त_pages;
	पूर्ण

	list_add(&area->list, &ptcal_list);

	वापस 0;

out_मुक्त_pages:
	__मुक्त_pages(area->pages, area->order);
out_मुक्त_area:
	kमुक्त(area);
out_err:
	वापस ret;
पूर्ण

अटल पूर्णांक __init cbe_ptcal_enable(व्योम)
अणु
	स्थिर u32 *size;
	काष्ठा device_node *np;
	पूर्णांक order, found_mic = 0;

	np = of_find_node_by_path("/rtas");
	अगर (!np)
		वापस -ENODEV;

	size = of_get_property(np, "ibm,cbe-ptcal-size", शून्य);
	अगर (!size) अणु
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण

	pr_debug("%s: enabling PTCAL, size = 0x%x\n", __func__, *size);
	order = get_order(*size);
	of_node_put(np);

	/* support क्रम malta device trees, with be@/mic@ nodes */
	क्रम_each_node_by_type(np, "mic-tm") अणु
		cbe_ptcal_enable_on_node(of_node_to_nid(np), order);
		found_mic = 1;
	पूर्ण

	अगर (found_mic)
		वापस 0;

	/* support क्रम older device tree - use cpu nodes */
	क्रम_each_node_by_type(np, "cpu") अणु
		स्थिर u32 *nid = of_get_property(np, "node-id", शून्य);
		अगर (!nid) अणु
			prपूर्णांकk(KERN_ERR "%s: node %pOF is missing node-id?\n",
					__func__, np);
			जारी;
		पूर्ण
		cbe_ptcal_enable_on_node(*nid, order);
		found_mic = 1;
	पूर्ण

	वापस found_mic ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक cbe_ptcal_disable(व्योम)
अणु
	काष्ठा ptcal_area *area, *पंचांगp;
	पूर्णांक ret = 0;

	pr_debug("%s: disabling PTCAL\n", __func__);

	list_क्रम_each_entry_safe(area, पंचांगp, &ptcal_list, list) अणु
		/* disable ptcal on this node */
		अगर (rtas_call(ptcal_stop_tok, 1, 1, शून्य, area->nid)) अणु
			prपूर्णांकk(KERN_ERR "%s: error disabling PTCAL "
					"on node %d!\n", __func__,
					area->nid);
			ret = -EIO;
			जारी;
		पूर्ण

		/* ensure we can access the PTCAL area */
		स_रखो(page_address(area->pages), 0,
				1 << (area->order + PAGE_SHIFT));

		/* clean up */
		list_del(&area->list);
		__मुक्त_pages(area->pages, area->order);
		kमुक्त(area);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cbe_ptcal_notअगरy_reboot(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ code, व्योम *data)
अणु
	वापस cbe_ptcal_disable();
पूर्ण

अटल व्योम cbe_ptcal_crash_shutकरोwn(व्योम)
अणु
	cbe_ptcal_disable();
पूर्ण

अटल काष्ठा notअगरier_block cbe_ptcal_reboot_notअगरier = अणु
	.notअगरier_call = cbe_ptcal_notअगरy_reboot
पूर्ण;

#अगर_घोषित CONFIG_PPC_IBM_CELL_RESETBUTTON
अटल पूर्णांक sysreset_hack;

अटल पूर्णांक __init cbe_sysreset_init(व्योम)
अणु
	काष्ठा cbe_pmd_regs __iomem *regs;

	sysreset_hack = of_machine_is_compatible("IBM,CBPLUS-1.0");
	अगर (!sysreset_hack)
		वापस 0;

	regs = cbe_get_cpu_pmd_regs(0);
	अगर (!regs)
		वापस 0;

	/* Enable JTAG प्रणाली-reset hack */
	out_be32(&regs->fir_mode_reg,
		in_be32(&regs->fir_mode_reg) |
		CBE_PMD_FIR_MODE_M8);

	वापस 0;
पूर्ण
device_initcall(cbe_sysreset_init);

पूर्णांक cbe_sysreset_hack(व्योम)
अणु
	काष्ठा cbe_pmd_regs __iomem *regs;

	/*
	 * The BMC can inject user triggered प्रणाली reset exceptions,
	 * but cannot set the प्रणाली reset reason in srr1,
	 * so check an extra रेजिस्टर here.
	 */
	अगर (sysreset_hack && (smp_processor_id() == 0)) अणु
		regs = cbe_get_cpu_pmd_regs(0);
		अगर (!regs)
			वापस 0;
		अगर (in_be64(&regs->ras_esc_0) & 0x0000ffff) अणु
			out_be64(&regs->ras_esc_0, 0);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_IBM_CELL_RESETBUTTON */

अटल पूर्णांक __init cbe_ptcal_init(व्योम)
अणु
	पूर्णांक ret;
	ptcal_start_tok = rtas_token("ibm,cbe-start-ptcal");
	ptcal_stop_tok = rtas_token("ibm,cbe-stop-ptcal");

	अगर (ptcal_start_tok == RTAS_UNKNOWN_SERVICE
			|| ptcal_stop_tok == RTAS_UNKNOWN_SERVICE)
		वापस -ENODEV;

	ret = रेजिस्टर_reboot_notअगरier(&cbe_ptcal_reboot_notअगरier);
	अगर (ret)
		जाओ out1;

	ret = crash_shutकरोwn_रेजिस्टर(&cbe_ptcal_crash_shutकरोwn);
	अगर (ret)
		जाओ out2;

	वापस cbe_ptcal_enable();

out2:
	unरेजिस्टर_reboot_notअगरier(&cbe_ptcal_reboot_notअगरier);
out1:
	prपूर्णांकk(KERN_ERR "Can't disable PTCAL, so not enabling\n");
	वापस ret;
पूर्ण

arch_initcall(cbe_ptcal_init);

व्योम __init cbe_ras_init(व्योम)
अणु
	अचिन्हित दीर्घ hid0;

	/*
	 * Enable System Error & thermal पूर्णांकerrupts and wakeup conditions
	 */

	hid0 = mfspr(SPRN_HID0);
	hid0 |= HID0_CBE_THERM_INT_EN | HID0_CBE_THERM_WAKEUP |
		HID0_CBE_SYSERR_INT_EN | HID0_CBE_SYSERR_WAKEUP;
	mtspr(SPRN_HID0, hid0);
	mb();

	/*
	 * Install machine check handler. Leave setting of precise mode to
	 * what the firmware did क्रम now
	 */
	ppc_md.machine_check_exception = cbe_machine_check_handler;
	mb();

	/*
	 * For now, we assume that IOC_FIR is alपढ़ोy set to क्रमward some
	 * error conditions to the System Error handler. If that is not true
	 * then it will have to be fixed up here.
	 */
पूर्ण
