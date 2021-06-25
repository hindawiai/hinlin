<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kexec_file क्रम arm64
 *
 * Copyright (C) 2018 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 *
 * Most code is derived from arm64 port of kexec-tools
 */

#घोषणा pr_fmt(fmt) "kexec_file: " fmt

#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>

स्थिर काष्ठा kexec_file_ops * स्थिर kexec_file_loaders[] = अणु
	&kexec_image_ops,
	शून्य
पूर्ण;

पूर्णांक arch_kimage_file_post_load_cleanup(काष्ठा kimage *image)
अणु
	kvमुक्त(image->arch.dtb);
	image->arch.dtb = शून्य;

	vमुक्त(image->elf_headers);
	image->elf_headers = शून्य;
	image->elf_headers_sz = 0;

	वापस kexec_image_post_load_cleanup_शेष(image);
पूर्ण

अटल पूर्णांक prepare_elf_headers(व्योम **addr, अचिन्हित दीर्घ *sz)
अणु
	काष्ठा crash_mem *cmem;
	अचिन्हित पूर्णांक nr_ranges;
	पूर्णांक ret;
	u64 i;
	phys_addr_t start, end;

	nr_ranges = 1; /* क्रम exclusion of crashkernel region */
	क्रम_each_mem_range(i, &start, &end)
		nr_ranges++;

	cmem = kदो_स्मृति(काष्ठा_size(cmem, ranges, nr_ranges), GFP_KERNEL);
	अगर (!cmem)
		वापस -ENOMEM;

	cmem->max_nr_ranges = nr_ranges;
	cmem->nr_ranges = 0;
	क्रम_each_mem_range(i, &start, &end) अणु
		cmem->ranges[cmem->nr_ranges].start = start;
		cmem->ranges[cmem->nr_ranges].end = end - 1;
		cmem->nr_ranges++;
	पूर्ण

	/* Exclude crashkernel region */
	ret = crash_exclude_mem_range(cmem, crashk_res.start, crashk_res.end);

	अगर (!ret)
		ret =  crash_prepare_elf64_headers(cmem, true, addr, sz);

	kमुक्त(cmem);
	वापस ret;
पूर्ण

/*
 * Tries to add the initrd and DTB to the image. If it is not possible to find
 * valid locations, this function will unकरो changes to the image and वापस non
 * zero.
 */
पूर्णांक load_other_segments(काष्ठा kimage *image,
			अचिन्हित दीर्घ kernel_load_addr,
			अचिन्हित दीर्घ kernel_size,
			अक्षर *initrd, अचिन्हित दीर्घ initrd_len,
			अक्षर *cmdline)
अणु
	काष्ठा kexec_buf kbuf;
	व्योम *headers, *dtb = शून्य;
	अचिन्हित दीर्घ headers_sz, initrd_load_addr = 0, dtb_len,
		      orig_segments = image->nr_segments;
	पूर्णांक ret = 0;

	kbuf.image = image;
	/* not allocate anything below the kernel */
	kbuf.buf_min = kernel_load_addr + kernel_size;

	/* load elf core header */
	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		ret = prepare_elf_headers(&headers, &headers_sz);
		अगर (ret) अणु
			pr_err("Preparing elf core header failed\n");
			जाओ out_err;
		पूर्ण

		kbuf.buffer = headers;
		kbuf.bufsz = headers_sz;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		kbuf.memsz = headers_sz;
		kbuf.buf_align = SZ_64K; /* largest supported page size */
		kbuf.buf_max = अच_दीर्घ_उच्च;
		kbuf.top_करोwn = true;

		ret = kexec_add_buffer(&kbuf);
		अगर (ret) अणु
			vमुक्त(headers);
			जाओ out_err;
		पूर्ण
		image->elf_headers = headers;
		image->elf_load_addr = kbuf.mem;
		image->elf_headers_sz = headers_sz;

		pr_debug("Loaded elf core header at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
			 image->elf_load_addr, kbuf.bufsz, kbuf.memsz);
	पूर्ण

	/* load initrd */
	अगर (initrd) अणु
		kbuf.buffer = initrd;
		kbuf.bufsz = initrd_len;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		kbuf.memsz = initrd_len;
		kbuf.buf_align = 0;
		/* within 1GB-aligned winकरोw of up to 32GB in size */
		kbuf.buf_max = round_करोwn(kernel_load_addr, SZ_1G)
						+ (अचिन्हित दीर्घ)SZ_1G * 32;
		kbuf.top_करोwn = false;

		ret = kexec_add_buffer(&kbuf);
		अगर (ret)
			जाओ out_err;
		initrd_load_addr = kbuf.mem;

		pr_debug("Loaded initrd at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
				initrd_load_addr, kbuf.bufsz, kbuf.memsz);
	पूर्ण

	/* load dtb */
	dtb = of_kexec_alloc_and_setup_fdt(image, initrd_load_addr,
					   initrd_len, cmdline, 0);
	अगर (!dtb) अणु
		pr_err("Preparing for new dtb failed\n");
		जाओ out_err;
	पूर्ण

	/* trim it */
	fdt_pack(dtb);
	dtb_len = fdt_totalsize(dtb);
	kbuf.buffer = dtb;
	kbuf.bufsz = dtb_len;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf.memsz = dtb_len;
	/* not across 2MB boundary */
	kbuf.buf_align = SZ_2M;
	kbuf.buf_max = अच_दीर्घ_उच्च;
	kbuf.top_करोwn = true;

	ret = kexec_add_buffer(&kbuf);
	अगर (ret)
		जाओ out_err;
	image->arch.dtb = dtb;
	image->arch.dtb_mem = kbuf.mem;

	pr_debug("Loaded dtb at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
			kbuf.mem, kbuf.bufsz, kbuf.memsz);

	वापस 0;

out_err:
	image->nr_segments = orig_segments;
	kvमुक्त(dtb);
	वापस ret;
पूर्ण
