<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Load ELF vmlinux file क्रम the kexec_file_load syscall.
 *
 * Copyright (c) 2019 Sven Schnelle <svens@stackframe.org>
 *
 */
#समावेश <linux/elf.h>
#समावेश <linux/kexec.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

अटल व्योम *elf_load(काष्ठा kimage *image, अक्षर *kernel_buf,
			अचिन्हित दीर्घ kernel_len, अक्षर *initrd,
			अचिन्हित दीर्घ initrd_len, अक्षर *cmdline,
			अचिन्हित दीर्घ cmdline_len)
अणु
	पूर्णांक ret, i;
	अचिन्हित दीर्घ kernel_load_addr;
	काष्ठा elfhdr ehdr;
	काष्ठा kexec_elf_info elf_info;
	काष्ठा kexec_buf kbuf = अणु .image = image, .buf_min = 0,
				  .buf_max = -1UL, पूर्ण;

	ret = kexec_build_elf_info(kernel_buf, kernel_len, &ehdr, &elf_info);
	अगर (ret)
		जाओ out;

	ret = kexec_elf_load(image, &ehdr, &elf_info, &kbuf, &kernel_load_addr);
	अगर (ret)
		जाओ out;

	image->start = __pa(elf_info.ehdr->e_entry);

	क्रम (i = 0; i < image->nr_segments; i++)
		image->segment[i].mem = __pa(image->segment[i].mem);

	pr_debug("Loaded the kernel at 0x%lx, entry at 0x%lx\n",
		 kernel_load_addr, image->start);

	अगर (initrd != शून्य) अणु
		kbuf.buffer = initrd;
		kbuf.bufsz = kbuf.memsz = initrd_len;
		kbuf.buf_align = PAGE_SIZE;
		kbuf.top_करोwn = false;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		ret = kexec_add_buffer(&kbuf);
		अगर (ret)
			जाओ out;

		pr_debug("Loaded initrd at 0x%lx\n", kbuf.mem);
		image->arch.initrd_start = kbuf.mem;
		image->arch.initrd_end = kbuf.mem + initrd_len;
	पूर्ण

	अगर (cmdline != शून्य) अणु
		kbuf.buffer = cmdline;
		kbuf.bufsz = kbuf.memsz = ALIGN(cmdline_len, 8);
		kbuf.buf_align = PAGE_SIZE;
		kbuf.top_करोwn = false;
		kbuf.buf_min = PAGE0->mem_मुक्त + PAGE_SIZE;
		kbuf.buf_max = kernel_load_addr;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		ret = kexec_add_buffer(&kbuf);
		अगर (ret)
			जाओ out;

		pr_debug("Loaded cmdline at 0x%lx\n", kbuf.mem);
		image->arch.cmdline = kbuf.mem;
	पूर्ण
out:
	वापस शून्य;
पूर्ण

स्थिर काष्ठा kexec_file_ops kexec_elf_ops = अणु
	.probe = kexec_elf_probe,
	.load = elf_load,
पूर्ण;

स्थिर काष्ठा kexec_file_ops * स्थिर kexec_file_loaders[] = अणु
	&kexec_elf_ops,
	शून्य
पूर्ण;
