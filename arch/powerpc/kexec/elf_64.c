<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Load ELF vmlinux file क्रम the kexec_file_load syscall.
 *
 * Copyright (C) 2004  Adam Litke (agl@us.ibm.com)
 * Copyright (C) 2004  IBM Corp.
 * Copyright (C) 2005  R Sharada (sharada@in.ibm.com)
 * Copyright (C) 2006  Mohan Kumar M (mohan@in.ibm.com)
 * Copyright (C) 2016  IBM Corporation
 *
 * Based on kexec-tools' kexec-elf-exec.c and kexec-elf-ppc64.c.
 * Heavily modअगरied क्रम the kernel by
 * Thiago Jung Bauermann <bauerman@linux.vnet.ibm.com>.
 */

#घोषणा pr_fmt(fmt)	"kexec_elf: " fmt

#समावेश <linux/elf.h>
#समावेश <linux/kexec.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

अटल व्योम *elf64_load(काष्ठा kimage *image, अक्षर *kernel_buf,
			अचिन्हित दीर्घ kernel_len, अक्षर *initrd,
			अचिन्हित दीर्घ initrd_len, अक्षर *cmdline,
			अचिन्हित दीर्घ cmdline_len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ kernel_load_addr;
	अचिन्हित दीर्घ initrd_load_addr = 0, fdt_load_addr;
	व्योम *fdt;
	स्थिर व्योम *slave_code;
	काष्ठा elfhdr ehdr;
	अक्षर *modअगरied_cmdline = शून्य;
	काष्ठा kexec_elf_info elf_info;
	काष्ठा kexec_buf kbuf = अणु .image = image, .buf_min = 0,
				  .buf_max = ppc64_rma_size पूर्ण;
	काष्ठा kexec_buf pbuf = अणु .image = image, .buf_min = 0,
				  .buf_max = ppc64_rma_size, .top_करोwn = true,
				  .mem = KEXEC_BUF_MEM_UNKNOWN पूर्ण;

	ret = kexec_build_elf_info(kernel_buf, kernel_len, &ehdr, &elf_info);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		/* min & max buffer values क्रम kdump हाल */
		kbuf.buf_min = pbuf.buf_min = crashk_res.start;
		kbuf.buf_max = pbuf.buf_max =
				((crashk_res.end < ppc64_rma_size) ?
				 crashk_res.end : (ppc64_rma_size - 1));
	पूर्ण

	ret = kexec_elf_load(image, &ehdr, &elf_info, &kbuf, &kernel_load_addr);
	अगर (ret)
		जाओ out;

	pr_debug("Loaded the kernel at 0x%lx\n", kernel_load_addr);

	ret = kexec_load_purgatory(image, &pbuf);
	अगर (ret) अणु
		pr_err("Loading purgatory failed.\n");
		जाओ out;
	पूर्ण

	pr_debug("Loaded purgatory at 0x%lx\n", pbuf.mem);

	/* Load additional segments needed क्रम panic kernel */
	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		ret = load_crashdump_segments_ppc64(image, &kbuf);
		अगर (ret) अणु
			pr_err("Failed to load kdump kernel segments\n");
			जाओ out;
		पूर्ण

		/* Setup cmdline क्रम kdump kernel हाल */
		modअगरied_cmdline = setup_kdump_cmdline(image, cmdline,
						       cmdline_len);
		अगर (!modअगरied_cmdline) अणु
			pr_err("Setting up cmdline for kdump kernel failed\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		cmdline = modअगरied_cmdline;
	पूर्ण

	अगर (initrd != शून्य) अणु
		kbuf.buffer = initrd;
		kbuf.bufsz = kbuf.memsz = initrd_len;
		kbuf.buf_align = PAGE_SIZE;
		kbuf.top_करोwn = false;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		ret = kexec_add_buffer(&kbuf);
		अगर (ret)
			जाओ out;
		initrd_load_addr = kbuf.mem;

		pr_debug("Loaded initrd at 0x%lx\n", initrd_load_addr);
	पूर्ण

	fdt = of_kexec_alloc_and_setup_fdt(image, initrd_load_addr,
					   initrd_len, cmdline,
					   kexec_extra_fdt_size_ppc64(image));
	अगर (!fdt) अणु
		pr_err("Error setting up the new device tree.\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = setup_new_fdt_ppc64(image, fdt, initrd_load_addr,
				  initrd_len, cmdline);
	अगर (ret)
		जाओ out_मुक्त_fdt;

	fdt_pack(fdt);

	kbuf.buffer = fdt;
	kbuf.bufsz = kbuf.memsz = fdt_totalsize(fdt);
	kbuf.buf_align = PAGE_SIZE;
	kbuf.top_करोwn = true;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	ret = kexec_add_buffer(&kbuf);
	अगर (ret)
		जाओ out_मुक्त_fdt;

	/* FDT will be मुक्तd in arch_kimage_file_post_load_cleanup */
	image->arch.fdt = fdt;

	fdt_load_addr = kbuf.mem;

	pr_debug("Loaded device tree at 0x%lx\n", fdt_load_addr);

	slave_code = elf_info.buffer + elf_info.proghdrs[0].p_offset;
	ret = setup_purgatory_ppc64(image, slave_code, fdt, kernel_load_addr,
				    fdt_load_addr);
	अगर (ret)
		pr_err("Error setting up the purgatory.\n");

	जाओ out;

out_मुक्त_fdt:
	kvमुक्त(fdt);
out:
	kमुक्त(modअगरied_cmdline);
	kexec_मुक्त_elf_info(&elf_info);

	वापस ret ? ERR_PTR(ret) : शून्य;
पूर्ण

स्थिर काष्ठा kexec_file_ops kexec_elf64_ops = अणु
	.probe = kexec_elf_probe,
	.load = elf64_load,
पूर्ण;
