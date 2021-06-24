<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PPC64 code to handle Linux booting another kernel.
 *
 * Copyright (C) 2004-2005, IBM Corp.
 *
 * Created by: Milton D Miller II
 */


#समावेश <linux/kexec.h>
#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/init_task.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/cpu.h>
#समावेश <linux/hardirq.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/sections.h>	/* _end */
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/ultravisor.h>

पूर्णांक शेष_machine_kexec_prepare(काष्ठा kimage *image)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ begin, end;	/* limits of segment */
	अचिन्हित दीर्घ low, high;	/* limits of blocked memory range */
	काष्ठा device_node *node;
	स्थिर अचिन्हित दीर्घ *basep;
	स्थिर अचिन्हित पूर्णांक *sizep;

	/*
	 * Since we use the kernel fault handlers and paging code to
	 * handle the भव mode, we must make sure no destination
	 * overlaps kernel अटल data or bss.
	 */
	क्रम (i = 0; i < image->nr_segments; i++)
		अगर (image->segment[i].mem < __pa(_end))
			वापस -ETXTBSY;

	/* We also should not overग_लिखो the tce tables */
	क्रम_each_node_by_type(node, "pci") अणु
		basep = of_get_property(node, "linux,tce-base", शून्य);
		sizep = of_get_property(node, "linux,tce-size", शून्य);
		अगर (basep == शून्य || sizep == शून्य)
			जारी;

		low = *basep;
		high = low + (*sizep);

		क्रम (i = 0; i < image->nr_segments; i++) अणु
			begin = image->segment[i].mem;
			end = begin + image->segment[i].memsz;

			अगर ((begin < high) && (end > low))
				वापस -ETXTBSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम copy_segments(अचिन्हित दीर्घ ind)
अणु
	अचिन्हित दीर्घ entry;
	अचिन्हित दीर्घ *ptr;
	व्योम *dest;
	व्योम *addr;

	/*
	 * We rely on kexec_load to create a lists that properly
	 * initializes these poपूर्णांकers beक्रमe they are used.
	 * We will still crash अगर the list is wrong, but at least
	 * the compiler will be quiet.
	 */
	ptr = शून्य;
	dest = शून्य;

	क्रम (entry = ind; !(entry & IND_DONE); entry = *ptr++) अणु
		addr = __va(entry & PAGE_MASK);

		चयन (entry & IND_FLAGS) अणु
		हाल IND_DESTINATION:
			dest = addr;
			अवरोध;
		हाल IND_INसूचीECTION:
			ptr = addr;
			अवरोध;
		हाल IND_SOURCE:
			copy_page(dest, addr);
			dest += PAGE_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

व्योम kexec_copy_flush(काष्ठा kimage *image)
अणु
	दीर्घ i, nr_segments = image->nr_segments;
	काष्ठा  kexec_segment ranges[KEXEC_SEGMENT_MAX];

	/* save the ranges on the stack to efficiently flush the icache */
	स_नकल(ranges, image->segment, माप(ranges));

	/*
	 * After this call we may not use anything allocated in dynamic
	 * memory, including *image.
	 *
	 * Only globals and the stack are allowed.
	 */
	copy_segments(image->head);

	/*
	 * we need to clear the icache क्रम all dest pages someसमय,
	 * including ones that were in place on the original copy
	 */
	क्रम (i = 0; i < nr_segments; i++)
		flush_icache_range((अचिन्हित दीर्घ)__va(ranges[i].mem),
			(अचिन्हित दीर्घ)__va(ranges[i].mem + ranges[i].memsz));
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल पूर्णांक kexec_all_irq_disabled = 0;

अटल व्योम kexec_smp_करोwn(व्योम *arg)
अणु
	local_irq_disable();
	hard_irq_disable();

	mb(); /* make sure our irqs are disabled beक्रमe we say they are */
	get_paca()->kexec_state = KEXEC_STATE_IRQS_OFF;
	जबतक(kexec_all_irq_disabled == 0)
		cpu_relax();
	mb(); /* make sure all irqs are disabled beक्रमe this */
	hw_अवरोधpoपूर्णांक_disable();
	/*
	 * Now every CPU has IRQs off, we can clear out any pending
	 * IPIs and be sure that no more will come in after this.
	 */
	अगर (ppc_md.kexec_cpu_करोwn)
		ppc_md.kexec_cpu_करोwn(0, 1);

	reset_sprs();

	kexec_smp_रुको();
	/* NOTREACHED */
पूर्ण

अटल व्योम kexec_prepare_cpus_रुको(पूर्णांक रुको_state)
अणु
	पूर्णांक my_cpu, i, notअगरied=-1;

	hw_अवरोधpoपूर्णांक_disable();
	my_cpu = get_cpu();
	/* Make sure each CPU has at least made it to the state we need.
	 *
	 * FIXME: There is a (slim) chance of a problem अगर not all of the CPUs
	 * are correctly onlined.  If somehow we start a CPU on boot with RTAS
	 * start-cpu, but somehow that CPU करोesn't ग_लिखो callin_cpu_map[] in
	 * समय, the boot CPU will समयout.  If it करोes eventually execute
	 * stuff, the secondary will start up (paca_ptrs[]->cpu_start was
	 * written) and get पूर्णांकo a peculiar state.
	 * If the platक्रमm supports smp_ops->take_समयbase(), the secondary CPU
	 * will probably be spinning in there.  If not (i.e. pseries), the
	 * secondary will जारी on and try to online itself/idle/etc. If it
	 * survives that, we need to find these
	 * possible-but-not-online-but-should-be CPUs and chaperone them पूर्णांकo
	 * kexec_smp_रुको().
	 */
	क्रम_each_online_cpu(i) अणु
		अगर (i == my_cpu)
			जारी;

		जबतक (paca_ptrs[i]->kexec_state < रुको_state) अणु
			barrier();
			अगर (i != notअगरied) अणु
				prपूर्णांकk(KERN_INFO "kexec: waiting for cpu %d "
				       "(physical %d) to enter %i state\n",
				       i, paca_ptrs[i]->hw_cpu_id, रुको_state);
				notअगरied = i;
			पूर्ण
		पूर्ण
	पूर्ण
	mb();
पूर्ण

/*
 * We need to make sure each present CPU is online.  The next kernel will scan
 * the device tree and assume primary thपढ़ोs are online and query secondary
 * thपढ़ोs via RTAS to online them अगर required.  If we करोn't online primary
 * thपढ़ोs, they will be stuck.  However, we also online secondary thपढ़ोs as we
 * may be using 'cede offline'.  In this case RTAS doesn't see the secondary
 * thपढ़ोs as offline -- and again, these CPUs will be stuck.
 *
 * So, we online all CPUs that should be running, including secondary thपढ़ोs.
 */
अटल व्योम wake_offline_cpus(व्योम)
अणु
	पूर्णांक cpu = 0;

	क्रम_each_present_cpu(cpu) अणु
		अगर (!cpu_online(cpu)) अणु
			prपूर्णांकk(KERN_INFO "kexec: Waking offline cpu %d.\n",
			       cpu);
			WARN_ON(add_cpu(cpu));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम kexec_prepare_cpus(व्योम)
अणु
	wake_offline_cpus();
	smp_call_function(kexec_smp_करोwn, शून्य, /* रुको */0);
	local_irq_disable();
	hard_irq_disable();

	mb(); /* make sure IRQs are disabled beक्रमe we say they are */
	get_paca()->kexec_state = KEXEC_STATE_IRQS_OFF;

	kexec_prepare_cpus_रुको(KEXEC_STATE_IRQS_OFF);
	/* we are sure every CPU has IRQs off at this poपूर्णांक */
	kexec_all_irq_disabled = 1;

	/*
	 * Beक्रमe removing MMU mappings make sure all CPUs have entered real
	 * mode:
	 */
	kexec_prepare_cpus_रुको(KEXEC_STATE_REAL_MODE);

	/* after we tell the others to go करोwn */
	अगर (ppc_md.kexec_cpu_करोwn)
		ppc_md.kexec_cpu_करोwn(0, 0);

	put_cpu();
पूर्ण

#अन्यथा /* ! SMP */

अटल व्योम kexec_prepare_cpus(व्योम)
अणु
	/*
	 * move the secondarys to us so that we can copy
	 * the new kernel 0-0x100 safely
	 *
	 * करो this अगर kexec in setup.c ?
	 *
	 * We need to release the cpus अगर we are ever going from an
	 * UP to an SMP kernel.
	 */
	smp_release_cpus();
	अगर (ppc_md.kexec_cpu_करोwn)
		ppc_md.kexec_cpu_करोwn(0, 0);
	local_irq_disable();
	hard_irq_disable();
पूर्ण

#पूर्ण_अगर /* SMP */

/*
 * kexec thपढ़ो काष्ठाure and stack.
 *
 * We need to make sure that this is 16384-byte aligned due to the
 * way process stacks are handled.  It also must be अटलally allocated
 * or allocated as part of the kimage, because everything अन्यथा may be
 * overwritten when we copy the kexec image.  We piggyback on the
 * "init_task" linker section here to अटलally allocate a stack.
 *
 * We could use a smaller stack अगर we करोn't care about anything using
 * current, but that audit has not been perक्रमmed.
 */
अटल जोड़ thपढ़ो_जोड़ kexec_stack __init_task_data =
	अणु पूर्ण;

/*
 * For similar reasons to the stack above, the kexecing CPU needs to be on a
 * अटल PACA; we चयन to kexec_paca.
 */
काष्ठा paca_काष्ठा kexec_paca;

/* Our assembly helper, in misc_64.S */
बाह्य व्योम kexec_sequence(व्योम *newstack, अचिन्हित दीर्घ start,
			   व्योम *image, व्योम *control,
			   व्योम (*clear_all)(व्योम),
			   bool copy_with_mmu_off) __noवापस;

/* too late to fail here */
व्योम शेष_machine_kexec(काष्ठा kimage *image)
अणु
	bool copy_with_mmu_off;

	/* prepare control code अगर any */

	/*
        * If the kexec boot is the normal one, need to shutकरोwn other cpus
        * पूर्णांकo our रुको loop and quiesce पूर्णांकerrupts.
        * Otherwise, in the हाल of crashed mode (crashing_cpu >= 0),
        * stopping other CPUs and collecting their pt_regs is करोne beक्रमe
        * using debugger IPI.
        */

	अगर (!kdump_in_progress())
		kexec_prepare_cpus();

	prपूर्णांकk("kexec: Starting switchover sequence.\n");

	/* चयन to a अटलly allocated stack.  Based on irq stack code.
	 * We setup preempt_count to aव्योम using VMX in स_नकल.
	 * XXX: the task काष्ठा will likely be invalid once we करो the copy!
	 */
	current_thपढ़ो_info()->flags = 0;
	current_thपढ़ो_info()->preempt_count = HARसूचीQ_OFFSET;

	/* We need a अटल PACA, too; copy this CPU's PACA over and चयन to
	 * it. Also poison per_cpu_offset and शून्य lppaca to catch anyone using
	 * non-अटल data.
	 */
	स_नकल(&kexec_paca, get_paca(), माप(काष्ठा paca_काष्ठा));
	kexec_paca.data_offset = 0xedeaddeadeeeeeeeUL;
#अगर_घोषित CONFIG_PPC_PSERIES
	kexec_paca.lppaca_ptr = शून्य;
#पूर्ण_अगर

	अगर (is_secure_guest() && !(image->preserve_context ||
				   image->type == KEXEC_TYPE_CRASH)) अणु
		uv_unshare_all_pages();
		prपूर्णांकk("kexec: Unshared all shared pages.\n");
	पूर्ण

	paca_ptrs[kexec_paca.paca_index] = &kexec_paca;

	setup_paca(&kexec_paca);

	/*
	 * The lppaca should be unरेजिस्टरed at this poपूर्णांक so the HV won't
	 * touch it. In the हाल of a crash, none of the lppacas are
	 * unरेजिस्टरed so there is not much we can करो about it here.
	 */

	/*
	 * On Book3S, the copy must happen with the MMU off अगर we are either
	 * using Radix page tables or we are not in an LPAR since we can
	 * overग_लिखो the page tables जबतक copying.
	 *
	 * In an LPAR, we keep the MMU on otherwise we can't access beyond
	 * the RMA. On BookE there is no real MMU off mode, so we have to
	 * keep it enabled as well (but then we have bolted TLB entries).
	 */
#अगर_घोषित CONFIG_PPC_BOOK3E
	copy_with_mmu_off = false;
#अन्यथा
	copy_with_mmu_off = radix_enabled() ||
		!(firmware_has_feature(FW_FEATURE_LPAR) ||
		  firmware_has_feature(FW_FEATURE_PS3_LV1));
#पूर्ण_अगर

	/* Some things are best करोne in assembly.  Finding globals with
	 * a toc is easier in C, so pass in what we can.
	 */
	kexec_sequence(&kexec_stack, image->start, image,
		       page_address(image->control_code_page),
		       mmu_cleanup_all, copy_with_mmu_off);
	/* NOTREACHED */
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
/* Values we need to export to the second kernel via the device tree. */
अटल अचिन्हित दीर्घ htab_base;
अटल अचिन्हित दीर्घ htab_size;

अटल काष्ठा property htab_base_prop = अणु
	.name = "linux,htab-base",
	.length = माप(अचिन्हित दीर्घ),
	.value = &htab_base,
पूर्ण;

अटल काष्ठा property htab_size_prop = अणु
	.name = "linux,htab-size",
	.length = माप(अचिन्हित दीर्घ),
	.value = &htab_size,
पूर्ण;

अटल पूर्णांक __init export_htab_values(व्योम)
अणु
	काष्ठा device_node *node;

	/* On machines with no htab htab_address is शून्य */
	अगर (!htab_address)
		वापस -ENODEV;

	node = of_find_node_by_path("/chosen");
	अगर (!node)
		वापस -ENODEV;

	/* हटाओ any stale propertys so ours can be found */
	of_हटाओ_property(node, of_find_property(node, htab_base_prop.name, शून्य));
	of_हटाओ_property(node, of_find_property(node, htab_size_prop.name, शून्य));

	htab_base = cpu_to_be64(__pa(htab_address));
	of_add_property(node, &htab_base_prop);
	htab_size = cpu_to_be64(htab_size_bytes);
	of_add_property(node, &htab_size_prop);

	of_node_put(node);
	वापस 0;
पूर्ण
late_initcall(export_htab_values);
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */
