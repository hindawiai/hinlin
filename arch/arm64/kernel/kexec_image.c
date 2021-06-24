<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Kexec image loader

 * Copyright (C) 2018 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 */

#घोषणा pr_fmt(fmt)	"kexec_file(Image): " fmt

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>
#समावेश <linux/pe.h>
#समावेश <linux/माला.स>
#समावेश <linux/verअगरication.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/image.h>
#समावेश <यंत्र/memory.h>

अटल पूर्णांक image_probe(स्थिर अक्षर *kernel_buf, अचिन्हित दीर्घ kernel_len)
अणु
	स्थिर काष्ठा arm64_image_header *h =
		(स्थिर काष्ठा arm64_image_header *)(kernel_buf);

	अगर (!h || (kernel_len < माप(*h)))
		वापस -EINVAL;

	अगर (स_भेद(&h->magic, ARM64_IMAGE_MAGIC, माप(h->magic)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम *image_load(काष्ठा kimage *image,
				अक्षर *kernel, अचिन्हित दीर्घ kernel_len,
				अक्षर *initrd, अचिन्हित दीर्घ initrd_len,
				अक्षर *cmdline, अचिन्हित दीर्घ cmdline_len)
अणु
	काष्ठा arm64_image_header *h;
	u64 flags, value;
	bool be_image, be_kernel;
	काष्ठा kexec_buf kbuf;
	अचिन्हित दीर्घ text_offset, kernel_segment_number;
	काष्ठा kexec_segment *kernel_segment;
	पूर्णांक ret;

	/*
	 * We require a kernel with an unambiguous Image header. Per
	 * Documentation/arm64/booting.rst, this is the हाल when image_size
	 * is non-zero (practically speaking, since v3.17).
	 */
	h = (काष्ठा arm64_image_header *)kernel;
	अगर (!h->image_size)
		वापस ERR_PTR(-EINVAL);

	/* Check cpu features */
	flags = le64_to_cpu(h->flags);
	be_image = arm64_image_flag_field(flags, ARM64_IMAGE_FLAG_BE);
	be_kernel = IS_ENABLED(CONFIG_CPU_BIG_ENDIAN);
	अगर ((be_image != be_kernel) && !प्रणाली_supports_mixed_endian())
		वापस ERR_PTR(-EINVAL);

	value = arm64_image_flag_field(flags, ARM64_IMAGE_FLAG_PAGE_SIZE);
	अगर (((value == ARM64_IMAGE_FLAG_PAGE_SIZE_4K) &&
			!प्रणाली_supports_4kb_granule()) ||
	    ((value == ARM64_IMAGE_FLAG_PAGE_SIZE_64K) &&
			!प्रणाली_supports_64kb_granule()) ||
	    ((value == ARM64_IMAGE_FLAG_PAGE_SIZE_16K) &&
			!प्रणाली_supports_16kb_granule()))
		वापस ERR_PTR(-EINVAL);

	/* Load the kernel */
	kbuf.image = image;
	kbuf.buf_min = 0;
	kbuf.buf_max = अच_दीर्घ_उच्च;
	kbuf.top_करोwn = false;

	kbuf.buffer = kernel;
	kbuf.bufsz = kernel_len;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf.memsz = le64_to_cpu(h->image_size);
	text_offset = le64_to_cpu(h->text_offset);
	kbuf.buf_align = MIN_KIMG_ALIGN;

	/* Adjust kernel segment with TEXT_OFFSET */
	kbuf.memsz += text_offset;

	kernel_segment_number = image->nr_segments;

	/*
	 * The location of the kernel segment may make it impossible to satisfy
	 * the other segment requirements, so we try repeatedly to find a
	 * location that will work.
	 */
	जबतक ((ret = kexec_add_buffer(&kbuf)) == 0) अणु
		/* Try to load additional data */
		kernel_segment = &image->segment[kernel_segment_number];
		ret = load_other_segments(image, kernel_segment->mem,
					  kernel_segment->memsz, initrd,
					  initrd_len, cmdline);
		अगर (!ret)
			अवरोध;

		/*
		 * We couldn't find space क्रम the other segments; erase the
		 * kernel segment and try the next available hole.
		 */
		image->nr_segments -= 1;
		kbuf.buf_min = kernel_segment->mem + kernel_segment->memsz;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	पूर्ण

	अगर (ret) अणु
		pr_err("Could not find any suitable kernel location!");
		वापस ERR_PTR(ret);
	पूर्ण

	kernel_segment = &image->segment[kernel_segment_number];
	kernel_segment->mem += text_offset;
	kernel_segment->memsz -= text_offset;
	image->start = kernel_segment->mem;

	pr_debug("Loaded kernel at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
				kernel_segment->mem, kbuf.bufsz,
				kernel_segment->memsz);

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_KEXEC_IMAGE_VERIFY_SIG
अटल पूर्णांक image_verअगरy_sig(स्थिर अक्षर *kernel, अचिन्हित दीर्घ kernel_len)
अणु
	वापस verअगरy_pefile_signature(kernel, kernel_len, शून्य,
				       VERIFYING_KEXEC_PE_SIGNATURE);
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा kexec_file_ops kexec_image_ops = अणु
	.probe = image_probe,
	.load = image_load,
#अगर_घोषित CONFIG_KEXEC_IMAGE_VERIFY_SIG
	.verअगरy_sig = image_verअगरy_sig,
#पूर्ण_अगर
पूर्ण;
