<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Architecture specअगरic (i386/x86_64) functions क्रम kexec based crash dumps.
 *
 * Created by: Hariprasad Nellitheertha (hari@in.ibm.com)
 *
 * Copyright (C) IBM Corporation, 2004. All rights reserved.
 * Copyright (C) Red Hat Inc., 2014. All rights reserved.
 * Authors:
 *      Vivek Goyal <vgoyal@redhat.com>
 *
 */

#घोषणा pr_fmt(fmt)	"kexec: " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/reboot.h>
#समावेश <linux/kexec.h>
#समावेश <linux/delay.h>
#समावेश <linux/elf.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/hardirq.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/e820/types.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/hpet.h>
#समावेश <linux/kdebug.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/virtext.h>
#समावेश <यंत्र/पूर्णांकel_pt.h>
#समावेश <यंत्र/crash.h>
#समावेश <यंत्र/cmdline.h>

/* Used जबतक preparing memory map entries क्रम second kernel */
काष्ठा crash_memmap_data अणु
	काष्ठा boot_params *params;
	/* Type of memory */
	अचिन्हित पूर्णांक type;
पूर्ण;

/*
 * This is used to VMCLEAR all VMCSs loaded on the
 * processor. And when loading kvm_पूर्णांकel module, the
 * callback function poपूर्णांकer will be asचिन्हित.
 *
 * रक्षित by rcu.
 */
crash_vmclear_fn __rcu *crash_vmclear_loaded_vmcss = शून्य;
EXPORT_SYMBOL_GPL(crash_vmclear_loaded_vmcss);

अटल अंतरभूत व्योम cpu_crash_vmclear_loaded_vmcss(व्योम)
अणु
	crash_vmclear_fn *करो_vmclear_operation = शून्य;

	rcu_पढ़ो_lock();
	करो_vmclear_operation = rcu_dereference(crash_vmclear_loaded_vmcss);
	अगर (करो_vmclear_operation)
		करो_vmclear_operation();
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * When the crashkernel option is specअगरied, only use the low
 * 1M क्रम the real mode trampoline.
 */
व्योम __init crash_reserve_low_1M(व्योम)
अणु
	अगर (cmdline_find_option(boot_command_line, "crashkernel", शून्य, 0) < 0)
		वापस;

	memblock_reserve(0, 1<<20);
	pr_info("Reserving the low 1M of memory for crashkernel\n");
पूर्ण

#अगर defined(CONFIG_SMP) && defined(CONFIG_X86_LOCAL_APIC)

अटल व्योम kdump_nmi_callback(पूर्णांक cpu, काष्ठा pt_regs *regs)
अणु
	crash_save_cpu(regs, cpu);

	/*
	 * VMCLEAR VMCSs loaded on all cpus अगर needed.
	 */
	cpu_crash_vmclear_loaded_vmcss();

	/* Disable VMX or SVM अगर needed.
	 *
	 * We need to disable भवization on all CPUs.
	 * Having VMX or SVM enabled on any CPU may अवरोध rebooting
	 * after the kdump kernel has finished its task.
	 */
	cpu_emergency_vmxoff();
	cpu_emergency_svm_disable();

	/*
	 * Disable Intel PT to stop its logging
	 */
	cpu_emergency_stop_pt();

	disable_local_APIC();
पूर्ण

व्योम kdump_nmi_shootकरोwn_cpus(व्योम)
अणु
	nmi_shootकरोwn_cpus(kdump_nmi_callback);

	disable_local_APIC();
पूर्ण

/* Override the weak function in kernel/panic.c */
व्योम crash_smp_send_stop(व्योम)
अणु
	अटल पूर्णांक cpus_stopped;

	अगर (cpus_stopped)
		वापस;

	अगर (smp_ops.crash_stop_other_cpus)
		smp_ops.crash_stop_other_cpus();
	अन्यथा
		smp_send_stop();

	cpus_stopped = 1;
पूर्ण

#अन्यथा
व्योम crash_smp_send_stop(व्योम)
अणु
	/* There are no cpus to shootकरोwn */
पूर्ण
#पूर्ण_अगर

व्योम native_machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	/* This function is only called after the प्रणाली
	 * has panicked or is otherwise in a critical state.
	 * The minimum amount of code to allow a kexec'd kernel
	 * to run successfully needs to happen here.
	 *
	 * In practice this means shooting करोwn the other cpus in
	 * an SMP प्रणाली.
	 */
	/* The kernel is broken so disable पूर्णांकerrupts */
	local_irq_disable();

	crash_smp_send_stop();

	/*
	 * VMCLEAR VMCSs loaded on this cpu अगर needed.
	 */
	cpu_crash_vmclear_loaded_vmcss();

	/* Booting kdump kernel with VMX or SVM enabled won't work,
	 * because (among other limitations) we can't disable paging
	 * with the virt flags.
	 */
	cpu_emergency_vmxoff();
	cpu_emergency_svm_disable();

	/*
	 * Disable Intel PT to stop its logging
	 */
	cpu_emergency_stop_pt();

#अगर_घोषित CONFIG_X86_IO_APIC
	/* Prevent crash_kexec() from deadlocking on ioapic_lock. */
	ioapic_zap_locks();
	clear_IO_APIC();
#पूर्ण_अगर
	lapic_shutकरोwn();
	restore_boot_irq_mode();
#अगर_घोषित CONFIG_HPET_TIMER
	hpet_disable();
#पूर्ण_अगर
	crash_save_cpu(regs, safe_smp_processor_id());
पूर्ण

#अगर_घोषित CONFIG_KEXEC_खाता

अटल पूर्णांक get_nr_ram_ranges_callback(काष्ठा resource *res, व्योम *arg)
अणु
	अचिन्हित पूर्णांक *nr_ranges = arg;

	(*nr_ranges)++;
	वापस 0;
पूर्ण

/* Gather all the required inक्रमmation to prepare elf headers क्रम ram regions */
अटल काष्ठा crash_mem *fill_up_crash_elf_data(व्योम)
अणु
	अचिन्हित पूर्णांक nr_ranges = 0;
	काष्ठा crash_mem *cmem;

	walk_प्रणाली_ram_res(0, -1, &nr_ranges, get_nr_ram_ranges_callback);
	अगर (!nr_ranges)
		वापस शून्य;

	/*
	 * Exclusion of crash region and/or crashk_low_res may cause
	 * another range split. So add extra two slots here.
	 */
	nr_ranges += 2;
	cmem = vzalloc(काष्ठा_size(cmem, ranges, nr_ranges));
	अगर (!cmem)
		वापस शून्य;

	cmem->max_nr_ranges = nr_ranges;
	cmem->nr_ranges = 0;

	वापस cmem;
पूर्ण

/*
 * Look क्रम any unwanted ranges between mstart, mend and हटाओ them. This
 * might lead to split and split ranges are put in cmem->ranges[] array
 */
अटल पूर्णांक elf_header_exclude_ranges(काष्ठा crash_mem *cmem)
अणु
	पूर्णांक ret = 0;

	/* Exclude the low 1M because it is always reserved */
	ret = crash_exclude_mem_range(cmem, 0, (1<<20)-1);
	अगर (ret)
		वापस ret;

	/* Exclude crashkernel region */
	ret = crash_exclude_mem_range(cmem, crashk_res.start, crashk_res.end);
	अगर (ret)
		वापस ret;

	अगर (crashk_low_res.end)
		ret = crash_exclude_mem_range(cmem, crashk_low_res.start,
					      crashk_low_res.end);

	वापस ret;
पूर्ण

अटल पूर्णांक prepare_elf64_ram_headers_callback(काष्ठा resource *res, व्योम *arg)
अणु
	काष्ठा crash_mem *cmem = arg;

	cmem->ranges[cmem->nr_ranges].start = res->start;
	cmem->ranges[cmem->nr_ranges].end = res->end;
	cmem->nr_ranges++;

	वापस 0;
पूर्ण

/* Prepare elf headers. Return addr and size */
अटल पूर्णांक prepare_elf_headers(काष्ठा kimage *image, व्योम **addr,
					अचिन्हित दीर्घ *sz)
अणु
	काष्ठा crash_mem *cmem;
	पूर्णांक ret;

	cmem = fill_up_crash_elf_data();
	अगर (!cmem)
		वापस -ENOMEM;

	ret = walk_प्रणाली_ram_res(0, -1, cmem, prepare_elf64_ram_headers_callback);
	अगर (ret)
		जाओ out;

	/* Exclude unwanted mem ranges */
	ret = elf_header_exclude_ranges(cmem);
	अगर (ret)
		जाओ out;

	/* By शेष prepare 64bit headers */
	ret =  crash_prepare_elf64_headers(cmem, IS_ENABLED(CONFIG_X86_64), addr, sz);

out:
	vमुक्त(cmem);
	वापस ret;
पूर्ण

अटल पूर्णांक add_e820_entry(काष्ठा boot_params *params, काष्ठा e820_entry *entry)
अणु
	अचिन्हित पूर्णांक nr_e820_entries;

	nr_e820_entries = params->e820_entries;
	अगर (nr_e820_entries >= E820_MAX_ENTRIES_ZEROPAGE)
		वापस 1;

	स_नकल(&params->e820_table[nr_e820_entries], entry, माप(काष्ठा e820_entry));
	params->e820_entries++;
	वापस 0;
पूर्ण

अटल पूर्णांक memmap_entry_callback(काष्ठा resource *res, व्योम *arg)
अणु
	काष्ठा crash_memmap_data *cmd = arg;
	काष्ठा boot_params *params = cmd->params;
	काष्ठा e820_entry ei;

	ei.addr = res->start;
	ei.size = resource_size(res);
	ei.type = cmd->type;
	add_e820_entry(params, &ei);

	वापस 0;
पूर्ण

अटल पूर्णांक memmap_exclude_ranges(काष्ठा kimage *image, काष्ठा crash_mem *cmem,
				 अचिन्हित दीर्घ दीर्घ mstart,
				 अचिन्हित दीर्घ दीर्घ mend)
अणु
	अचिन्हित दीर्घ start, end;

	cmem->ranges[0].start = mstart;
	cmem->ranges[0].end = mend;
	cmem->nr_ranges = 1;

	/* Exclude elf header region */
	start = image->elf_load_addr;
	end = start + image->elf_headers_sz - 1;
	वापस crash_exclude_mem_range(cmem, start, end);
पूर्ण

/* Prepare memory map क्रम crash dump kernel */
पूर्णांक crash_setup_memmap_entries(काष्ठा kimage *image, काष्ठा boot_params *params)
अणु
	पूर्णांक i, ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा e820_entry ei;
	काष्ठा crash_memmap_data cmd;
	काष्ठा crash_mem *cmem;

	cmem = vzalloc(काष्ठा_size(cmem, ranges, 1));
	अगर (!cmem)
		वापस -ENOMEM;

	स_रखो(&cmd, 0, माप(काष्ठा crash_memmap_data));
	cmd.params = params;

	/* Add the low 1M */
	cmd.type = E820_TYPE_RAM;
	flags = IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY;
	walk_iomem_res_desc(IORES_DESC_NONE, flags, 0, (1<<20)-1, &cmd,
			    memmap_entry_callback);

	/* Add ACPI tables */
	cmd.type = E820_TYPE_ACPI;
	flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	walk_iomem_res_desc(IORES_DESC_ACPI_TABLES, flags, 0, -1, &cmd,
			    memmap_entry_callback);

	/* Add ACPI Non-अस्थिर Storage */
	cmd.type = E820_TYPE_NVS;
	walk_iomem_res_desc(IORES_DESC_ACPI_NV_STORAGE, flags, 0, -1, &cmd,
			    memmap_entry_callback);

	/* Add e820 reserved ranges */
	cmd.type = E820_TYPE_RESERVED;
	flags = IORESOURCE_MEM;
	walk_iomem_res_desc(IORES_DESC_RESERVED, flags, 0, -1, &cmd,
			    memmap_entry_callback);

	/* Add crashk_low_res region */
	अगर (crashk_low_res.end) अणु
		ei.addr = crashk_low_res.start;
		ei.size = resource_size(&crashk_low_res);
		ei.type = E820_TYPE_RAM;
		add_e820_entry(params, &ei);
	पूर्ण

	/* Exclude some ranges from crashk_res and add rest to memmap */
	ret = memmap_exclude_ranges(image, cmem, crashk_res.start, crashk_res.end);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < cmem->nr_ranges; i++) अणु
		ei.size = cmem->ranges[i].end - cmem->ranges[i].start + 1;

		/* If entry is less than a page, skip it */
		अगर (ei.size < PAGE_SIZE)
			जारी;
		ei.addr = cmem->ranges[i].start;
		ei.type = E820_TYPE_RAM;
		add_e820_entry(params, &ei);
	पूर्ण

out:
	vमुक्त(cmem);
	वापस ret;
पूर्ण

पूर्णांक crash_load_segments(काष्ठा kimage *image)
अणु
	पूर्णांक ret;
	काष्ठा kexec_buf kbuf = अणु .image = image, .buf_min = 0,
				  .buf_max = अच_दीर्घ_उच्च, .top_करोwn = false पूर्ण;

	/* Prepare elf headers and add a segment */
	ret = prepare_elf_headers(image, &kbuf.buffer, &kbuf.bufsz);
	अगर (ret)
		वापस ret;

	image->elf_headers = kbuf.buffer;
	image->elf_headers_sz = kbuf.bufsz;

	kbuf.memsz = kbuf.bufsz;
	kbuf.buf_align = ELF_CORE_HEADER_ALIGN;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	ret = kexec_add_buffer(&kbuf);
	अगर (ret) अणु
		vमुक्त((व्योम *)image->elf_headers);
		वापस ret;
	पूर्ण
	image->elf_load_addr = kbuf.mem;
	pr_debug("Loaded ELF headers at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
		 image->elf_load_addr, kbuf.bufsz, kbuf.bufsz);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_खाता */
