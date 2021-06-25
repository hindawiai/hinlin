<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/kexec.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/sections.h>

बाह्य व्योम relocate_new_kernel(अचिन्हित दीर्घ head,
				अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ phys);

बाह्य स्थिर अचिन्हित पूर्णांक relocate_new_kernel_size;
बाह्य अचिन्हित पूर्णांक kexec_initrd_start_offset;
बाह्य अचिन्हित पूर्णांक kexec_initrd_end_offset;
बाह्य अचिन्हित पूर्णांक kexec_cmdline_offset;
बाह्य अचिन्हित पूर्णांक kexec_मुक्त_mem_offset;

अटल व्योम kexec_show_segment_info(स्थिर काष्ठा kimage *kimage,
				    अचिन्हित दीर्घ n)
अणु
	pr_debug("    segment[%lu]: %016lx - %016lx, 0x%lx bytes, %lu pages\n",
			n,
			kimage->segment[n].mem,
			kimage->segment[n].mem + kimage->segment[n].memsz,
			(अचिन्हित दीर्घ)kimage->segment[n].memsz,
			(अचिन्हित दीर्घ)kimage->segment[n].memsz /  PAGE_SIZE);
पूर्ण

अटल व्योम kexec_image_info(स्थिर काष्ठा kimage *kimage)
अणु
	अचिन्हित दीर्घ i;

	pr_debug("kexec kimage info:\n");
	pr_debug("  type:        %d\n", kimage->type);
	pr_debug("  start:       %lx\n", kimage->start);
	pr_debug("  head:        %lx\n", kimage->head);
	pr_debug("  nr_segments: %lu\n", kimage->nr_segments);

	क्रम (i = 0; i < kimage->nr_segments; i++)
		kexec_show_segment_info(kimage, i);

#अगर_घोषित CONFIG_KEXEC_खाता
	अगर (kimage->file_mode) अणु
		pr_debug("cmdline: %.*s\n", (पूर्णांक)kimage->cmdline_buf_len,
			 kimage->cmdline_buf);
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम machine_kexec_cleanup(काष्ठा kimage *kimage)
अणु
पूर्ण

व्योम machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
पूर्ण

व्योम machine_shutकरोwn(व्योम)
अणु
	smp_send_stop();
	जबतक (num_online_cpus() > 1) अणु
		cpu_relax();
		mdelay(1);
	पूर्ण
पूर्ण

व्योम machine_kexec(काष्ठा kimage *image)
अणु
#अगर_घोषित CONFIG_64BIT
	Elf64_Fdesc desc;
#पूर्ण_अगर
	व्योम (*reloc)(अचिन्हित दीर्घ head,
		      अचिन्हित दीर्घ start,
		      अचिन्हित दीर्घ phys);

	अचिन्हित दीर्घ phys = page_to_phys(image->control_code_page);
	व्योम *virt = (व्योम *)__fix_to_virt(FIX_TEXT_KEXEC);
	काष्ठा kimage_arch *arch = &image->arch;

	set_fixmap(FIX_TEXT_KEXEC, phys);

	flush_cache_all();

#अगर_घोषित CONFIG_64BIT
	reloc = (व्योम *)&desc;
	desc.addr = (दीर्घ दीर्घ)virt;
#अन्यथा
	reloc = (व्योम *)virt;
#पूर्ण_अगर

	स_नकल(virt, dereference_function_descriptor(relocate_new_kernel),
		relocate_new_kernel_size);

	*(अचिन्हित दीर्घ *)(virt + kexec_cmdline_offset) = arch->cmdline;
	*(अचिन्हित दीर्घ *)(virt + kexec_initrd_start_offset) = arch->initrd_start;
	*(अचिन्हित दीर्घ *)(virt + kexec_initrd_end_offset) = arch->initrd_end;
	*(अचिन्हित दीर्घ *)(virt + kexec_मुक्त_mem_offset) = PAGE0->mem_मुक्त;

	flush_cache_all();
	flush_tlb_all();
	local_irq_disable();

	reloc(image->head & PAGE_MASK, image->start, phys);
पूर्ण

पूर्णांक machine_kexec_prepare(काष्ठा kimage *image)
अणु
	kexec_image_info(image);
	वापस 0;
पूर्ण
