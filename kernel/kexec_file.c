<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kexec: kexec_file_load प्रणाली call
 *
 * Copyright (C) 2014 Red Hat Inc.
 * Authors:
 *      Vivek Goyal <vgoyal@redhat.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/mm.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/kexec.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/fs.h>
#समावेश <linux/ima.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha2.h>
#समावेश <linux/elf.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "kexec_internal.h"

अटल पूर्णांक kexec_calculate_store_digests(काष्ठा kimage *image);

/*
 * Currently this is the only शेष function that is exported as some
 * architectures need it to करो additional handlings.
 * In the future, other शेष functions may be exported too अगर required.
 */
पूर्णांक kexec_image_probe_शेष(काष्ठा kimage *image, व्योम *buf,
			      अचिन्हित दीर्घ buf_len)
अणु
	स्थिर काष्ठा kexec_file_ops * स्थिर *fops;
	पूर्णांक ret = -ENOEXEC;

	क्रम (fops = &kexec_file_loaders[0]; *fops && (*fops)->probe; ++fops) अणु
		ret = (*fops)->probe(buf, buf_len);
		अगर (!ret) अणु
			image->fops = *fops;
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* Architectures can provide this probe function */
पूर्णांक __weak arch_kexec_kernel_image_probe(काष्ठा kimage *image, व्योम *buf,
					 अचिन्हित दीर्घ buf_len)
अणु
	वापस kexec_image_probe_शेष(image, buf, buf_len);
पूर्ण

अटल व्योम *kexec_image_load_शेष(काष्ठा kimage *image)
अणु
	अगर (!image->fops || !image->fops->load)
		वापस ERR_PTR(-ENOEXEC);

	वापस image->fops->load(image, image->kernel_buf,
				 image->kernel_buf_len, image->initrd_buf,
				 image->initrd_buf_len, image->cmdline_buf,
				 image->cmdline_buf_len);
पूर्ण

व्योम * __weak arch_kexec_kernel_image_load(काष्ठा kimage *image)
अणु
	वापस kexec_image_load_शेष(image);
पूर्ण

पूर्णांक kexec_image_post_load_cleanup_शेष(काष्ठा kimage *image)
अणु
	अगर (!image->fops || !image->fops->cleanup)
		वापस 0;

	वापस image->fops->cleanup(image->image_loader_data);
पूर्ण

पूर्णांक __weak arch_kimage_file_post_load_cleanup(काष्ठा kimage *image)
अणु
	वापस kexec_image_post_load_cleanup_शेष(image);
पूर्ण

#अगर_घोषित CONFIG_KEXEC_SIG
अटल पूर्णांक kexec_image_verअगरy_sig_शेष(काष्ठा kimage *image, व्योम *buf,
					  अचिन्हित दीर्घ buf_len)
अणु
	अगर (!image->fops || !image->fops->verअगरy_sig) अणु
		pr_debug("kernel loader does not support signature verification.\n");
		वापस -EKEYREJECTED;
	पूर्ण

	वापस image->fops->verअगरy_sig(buf, buf_len);
पूर्ण

पूर्णांक __weak arch_kexec_kernel_verअगरy_sig(काष्ठा kimage *image, व्योम *buf,
					अचिन्हित दीर्घ buf_len)
अणु
	वापस kexec_image_verअगरy_sig_शेष(image, buf, buf_len);
पूर्ण
#पूर्ण_अगर

/*
 * arch_kexec_apply_relocations_add - apply relocations of type RELA
 * @pi:		Purgatory to be relocated.
 * @section:	Section relocations applying to.
 * @rअन्यथाc:	Section containing RELAs.
 * @symtab:	Corresponding symtab.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक __weak
arch_kexec_apply_relocations_add(काष्ठा purgatory_info *pi, Elf_Shdr *section,
				 स्थिर Elf_Shdr *rअन्यथाc, स्थिर Elf_Shdr *symtab)
अणु
	pr_err("RELA relocation unsupported.\n");
	वापस -ENOEXEC;
पूर्ण

/*
 * arch_kexec_apply_relocations - apply relocations of type REL
 * @pi:		Purgatory to be relocated.
 * @section:	Section relocations applying to.
 * @rअन्यथाc:	Section containing RELs.
 * @symtab:	Corresponding symtab.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक __weak
arch_kexec_apply_relocations(काष्ठा purgatory_info *pi, Elf_Shdr *section,
			     स्थिर Elf_Shdr *rअन्यथाc, स्थिर Elf_Shdr *symtab)
अणु
	pr_err("REL relocation unsupported.\n");
	वापस -ENOEXEC;
पूर्ण

/*
 * Free up memory used by kernel, initrd, and command line. This is temporary
 * memory allocation which is not needed any more after these buffers have
 * been loaded पूर्णांकo separate segments and have been copied अन्यथाwhere.
 */
व्योम kimage_file_post_load_cleanup(काष्ठा kimage *image)
अणु
	काष्ठा purgatory_info *pi = &image->purgatory_info;

	vमुक्त(image->kernel_buf);
	image->kernel_buf = शून्य;

	vमुक्त(image->initrd_buf);
	image->initrd_buf = शून्य;

	kमुक्त(image->cmdline_buf);
	image->cmdline_buf = शून्य;

	vमुक्त(pi->purgatory_buf);
	pi->purgatory_buf = शून्य;

	vमुक्त(pi->sechdrs);
	pi->sechdrs = शून्य;

#अगर_घोषित CONFIG_IMA_KEXEC
	vमुक्त(image->ima_buffer);
	image->ima_buffer = शून्य;
#पूर्ण_अगर /* CONFIG_IMA_KEXEC */

	/* See अगर architecture has anything to cleanup post load */
	arch_kimage_file_post_load_cleanup(image);

	/*
	 * Above call should have called पूर्णांकo bootloader to मुक्त up
	 * any data stored in kimage->image_loader_data. It should
	 * be ok now to मुक्त it up.
	 */
	kमुक्त(image->image_loader_data);
	image->image_loader_data = शून्य;
पूर्ण

#अगर_घोषित CONFIG_KEXEC_SIG
अटल पूर्णांक
kimage_validate_signature(काष्ठा kimage *image)
अणु
	पूर्णांक ret;

	ret = arch_kexec_kernel_verअगरy_sig(image, image->kernel_buf,
					   image->kernel_buf_len);
	अगर (ret) अणु

		अगर (IS_ENABLED(CONFIG_KEXEC_SIG_FORCE)) अणु
			pr_notice("Enforced kernel signature verification failed (%d).\n", ret);
			वापस ret;
		पूर्ण

		/*
		 * If IMA is guaranteed to appउठाओ a signature on the kexec
		 * image, permit it even अगर the kernel is otherwise locked
		 * करोwn.
		 */
		अगर (!ima_appउठाओ_signature(READING_KEXEC_IMAGE) &&
		    security_locked_करोwn(LOCKDOWN_KEXEC))
			वापस -EPERM;

		pr_debug("kernel signature verification failed (%d).\n", ret);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * In file mode list of segments is prepared by kernel. Copy relevant
 * data from user space, करो error checking, prepare segment list
 */
अटल पूर्णांक
kimage_file_prepare_segments(काष्ठा kimage *image, पूर्णांक kernel_fd, पूर्णांक initrd_fd,
			     स्थिर अक्षर __user *cmdline_ptr,
			     अचिन्हित दीर्घ cmdline_len, अचिन्हित flags)
अणु
	पूर्णांक ret;
	व्योम *ldata;

	ret = kernel_पढ़ो_file_from_fd(kernel_fd, 0, &image->kernel_buf,
				       पूर्णांक_उच्च, शून्य, READING_KEXEC_IMAGE);
	अगर (ret < 0)
		वापस ret;
	image->kernel_buf_len = ret;

	/* Call arch image probe handlers */
	ret = arch_kexec_kernel_image_probe(image, image->kernel_buf,
					    image->kernel_buf_len);
	अगर (ret)
		जाओ out;

#अगर_घोषित CONFIG_KEXEC_SIG
	ret = kimage_validate_signature(image);

	अगर (ret)
		जाओ out;
#पूर्ण_अगर
	/* It is possible that there no initramfs is being loaded */
	अगर (!(flags & KEXEC_खाता_NO_INITRAMFS)) अणु
		ret = kernel_पढ़ो_file_from_fd(initrd_fd, 0, &image->initrd_buf,
					       पूर्णांक_उच्च, शून्य,
					       READING_KEXEC_INITRAMFS);
		अगर (ret < 0)
			जाओ out;
		image->initrd_buf_len = ret;
		ret = 0;
	पूर्ण

	अगर (cmdline_len) अणु
		image->cmdline_buf = memdup_user(cmdline_ptr, cmdline_len);
		अगर (IS_ERR(image->cmdline_buf)) अणु
			ret = PTR_ERR(image->cmdline_buf);
			image->cmdline_buf = शून्य;
			जाओ out;
		पूर्ण

		image->cmdline_buf_len = cmdline_len;

		/* command line should be a string with last byte null */
		अगर (image->cmdline_buf[cmdline_len - 1] != '\0') अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		ima_kexec_cmdline(kernel_fd, image->cmdline_buf,
				  image->cmdline_buf_len - 1);
	पूर्ण

	/* IMA needs to pass the measurement list to the next kernel. */
	ima_add_kexec_buffer(image);

	/* Call arch image load handlers */
	ldata = arch_kexec_kernel_image_load(image);

	अगर (IS_ERR(ldata)) अणु
		ret = PTR_ERR(ldata);
		जाओ out;
	पूर्ण

	image->image_loader_data = ldata;
out:
	/* In हाल of error, मुक्त up all allocated memory in this function */
	अगर (ret)
		kimage_file_post_load_cleanup(image);
	वापस ret;
पूर्ण

अटल पूर्णांक
kimage_file_alloc_init(काष्ठा kimage **rimage, पूर्णांक kernel_fd,
		       पूर्णांक initrd_fd, स्थिर अक्षर __user *cmdline_ptr,
		       अचिन्हित दीर्घ cmdline_len, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;
	काष्ठा kimage *image;
	bool kexec_on_panic = flags & KEXEC_खाता_ON_CRASH;

	image = करो_kimage_alloc_init();
	अगर (!image)
		वापस -ENOMEM;

	image->file_mode = 1;

	अगर (kexec_on_panic) अणु
		/* Enable special crash kernel control page alloc policy. */
		image->control_page = crashk_res.start;
		image->type = KEXEC_TYPE_CRASH;
	पूर्ण

	ret = kimage_file_prepare_segments(image, kernel_fd, initrd_fd,
					   cmdline_ptr, cmdline_len, flags);
	अगर (ret)
		जाओ out_मुक्त_image;

	ret = sanity_check_segment_list(image);
	अगर (ret)
		जाओ out_मुक्त_post_load_bufs;

	ret = -ENOMEM;
	image->control_code_page = kimage_alloc_control_pages(image,
					   get_order(KEXEC_CONTROL_PAGE_SIZE));
	अगर (!image->control_code_page) अणु
		pr_err("Could not allocate control_code_buffer\n");
		जाओ out_मुक्त_post_load_bufs;
	पूर्ण

	अगर (!kexec_on_panic) अणु
		image->swap_page = kimage_alloc_control_pages(image, 0);
		अगर (!image->swap_page) अणु
			pr_err("Could not allocate swap buffer\n");
			जाओ out_मुक्त_control_pages;
		पूर्ण
	पूर्ण

	*rimage = image;
	वापस 0;
out_मुक्त_control_pages:
	kimage_मुक्त_page_list(&image->control_pages);
out_मुक्त_post_load_bufs:
	kimage_file_post_load_cleanup(image);
out_मुक्त_image:
	kमुक्त(image);
	वापस ret;
पूर्ण

SYSCALL_DEFINE5(kexec_file_load, पूर्णांक, kernel_fd, पूर्णांक, initrd_fd,
		अचिन्हित दीर्घ, cmdline_len, स्थिर अक्षर __user *, cmdline_ptr,
		अचिन्हित दीर्घ, flags)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा kimage **dest_image, *image;

	/* We only trust the superuser with rebooting the प्रणाली. */
	अगर (!capable(CAP_SYS_BOOT) || kexec_load_disabled)
		वापस -EPERM;

	/* Make sure we have a legal set of flags */
	अगर (flags != (flags & KEXEC_खाता_FLAGS))
		वापस -EINVAL;

	image = शून्य;

	अगर (!mutex_trylock(&kexec_mutex))
		वापस -EBUSY;

	dest_image = &kexec_image;
	अगर (flags & KEXEC_खाता_ON_CRASH) अणु
		dest_image = &kexec_crash_image;
		अगर (kexec_crash_image)
			arch_kexec_unprotect_crashkres();
	पूर्ण

	अगर (flags & KEXEC_खाता_UNLOAD)
		जाओ exchange;

	/*
	 * In हाल of crash, new kernel माला_लो loaded in reserved region. It is
	 * same memory where old crash kernel might be loaded. Free any
	 * current crash dump kernel beक्रमe we corrupt it.
	 */
	अगर (flags & KEXEC_खाता_ON_CRASH)
		kimage_मुक्त(xchg(&kexec_crash_image, शून्य));

	ret = kimage_file_alloc_init(&image, kernel_fd, initrd_fd, cmdline_ptr,
				     cmdline_len, flags);
	अगर (ret)
		जाओ out;

	ret = machine_kexec_prepare(image);
	अगर (ret)
		जाओ out;

	/*
	 * Some architecture(like S390) may touch the crash memory beक्रमe
	 * machine_kexec_prepare(), we must copy vmcoreinfo data after it.
	 */
	ret = kimage_crash_copy_vmcoreinfo(image);
	अगर (ret)
		जाओ out;

	ret = kexec_calculate_store_digests(image);
	अगर (ret)
		जाओ out;

	क्रम (i = 0; i < image->nr_segments; i++) अणु
		काष्ठा kexec_segment *ksegment;

		ksegment = &image->segment[i];
		pr_debug("Loading segment %d: buf=0x%p bufsz=0x%zx mem=0x%lx memsz=0x%zx\n",
			 i, ksegment->buf, ksegment->bufsz, ksegment->mem,
			 ksegment->memsz);

		ret = kimage_load_segment(image, &image->segment[i]);
		अगर (ret)
			जाओ out;
	पूर्ण

	kimage_terminate(image);

	ret = machine_kexec_post_load(image);
	अगर (ret)
		जाओ out;

	/*
	 * Free up any temporary buffers allocated which are not needed
	 * after image has been loaded
	 */
	kimage_file_post_load_cleanup(image);
exchange:
	image = xchg(dest_image, image);
out:
	अगर ((flags & KEXEC_खाता_ON_CRASH) && kexec_crash_image)
		arch_kexec_protect_crashkres();

	mutex_unlock(&kexec_mutex);
	kimage_मुक्त(image);
	वापस ret;
पूर्ण

अटल पूर्णांक locate_mem_hole_top_करोwn(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				    काष्ठा kexec_buf *kbuf)
अणु
	काष्ठा kimage *image = kbuf->image;
	अचिन्हित दीर्घ temp_start, temp_end;

	temp_end = min(end, kbuf->buf_max);
	temp_start = temp_end - kbuf->memsz;

	करो अणु
		/* align करोwn start */
		temp_start = temp_start & (~(kbuf->buf_align - 1));

		अगर (temp_start < start || temp_start < kbuf->buf_min)
			वापस 0;

		temp_end = temp_start + kbuf->memsz - 1;

		/*
		 * Make sure this करोes not conflict with any of existing
		 * segments
		 */
		अगर (kimage_is_destination_range(image, temp_start, temp_end)) अणु
			temp_start = temp_start - PAGE_SIZE;
			जारी;
		पूर्ण

		/* We found a suitable memory range */
		अवरोध;
	पूर्ण जबतक (1);

	/* If we are here, we found a suitable memory range */
	kbuf->mem = temp_start;

	/* Success, stop navigating through reमुख्यing System RAM ranges */
	वापस 1;
पूर्ण

अटल पूर्णांक locate_mem_hole_bottom_up(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				     काष्ठा kexec_buf *kbuf)
अणु
	काष्ठा kimage *image = kbuf->image;
	अचिन्हित दीर्घ temp_start, temp_end;

	temp_start = max(start, kbuf->buf_min);

	करो अणु
		temp_start = ALIGN(temp_start, kbuf->buf_align);
		temp_end = temp_start + kbuf->memsz - 1;

		अगर (temp_end > end || temp_end > kbuf->buf_max)
			वापस 0;
		/*
		 * Make sure this करोes not conflict with any of existing
		 * segments
		 */
		अगर (kimage_is_destination_range(image, temp_start, temp_end)) अणु
			temp_start = temp_start + PAGE_SIZE;
			जारी;
		पूर्ण

		/* We found a suitable memory range */
		अवरोध;
	पूर्ण जबतक (1);

	/* If we are here, we found a suitable memory range */
	kbuf->mem = temp_start;

	/* Success, stop navigating through reमुख्यing System RAM ranges */
	वापस 1;
पूर्ण

अटल पूर्णांक locate_mem_hole_callback(काष्ठा resource *res, व्योम *arg)
अणु
	काष्ठा kexec_buf *kbuf = (काष्ठा kexec_buf *)arg;
	u64 start = res->start, end = res->end;
	अचिन्हित दीर्घ sz = end - start + 1;

	/* Returning 0 will take to next memory range */

	/* Don't use memory that will be detected and handled by a driver. */
	अगर (res->flags & IORESOURCE_SYSRAM_DRIVER_MANAGED)
		वापस 0;

	अगर (sz < kbuf->memsz)
		वापस 0;

	अगर (end < kbuf->buf_min || start > kbuf->buf_max)
		वापस 0;

	/*
	 * Allocate memory top करोwn with-in ram range. Otherwise bottom up
	 * allocation.
	 */
	अगर (kbuf->top_करोwn)
		वापस locate_mem_hole_top_करोwn(start, end, kbuf);
	वापस locate_mem_hole_bottom_up(start, end, kbuf);
पूर्ण

#अगर_घोषित CONFIG_ARCH_KEEP_MEMBLOCK
अटल पूर्णांक kexec_walk_memblock(काष्ठा kexec_buf *kbuf,
			       पूर्णांक (*func)(काष्ठा resource *, व्योम *))
अणु
	पूर्णांक ret = 0;
	u64 i;
	phys_addr_t mstart, mend;
	काष्ठा resource res = अणु पूर्ण;

	अगर (kbuf->image->type == KEXEC_TYPE_CRASH)
		वापस func(&crashk_res, kbuf);

	अगर (kbuf->top_करोwn) अणु
		क्रम_each_मुक्त_mem_range_reverse(i, NUMA_NO_NODE, MEMBLOCK_NONE,
						&mstart, &mend, शून्य) अणु
			/*
			 * In memblock, end poपूर्णांकs to the first byte after the
			 * range जबतक in kexec, end poपूर्णांकs to the last byte
			 * in the range.
			 */
			res.start = mstart;
			res.end = mend - 1;
			ret = func(&res, kbuf);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_मुक्त_mem_range(i, NUMA_NO_NODE, MEMBLOCK_NONE,
					&mstart, &mend, शून्य) अणु
			/*
			 * In memblock, end poपूर्णांकs to the first byte after the
			 * range जबतक in kexec, end poपूर्णांकs to the last byte
			 * in the range.
			 */
			res.start = mstart;
			res.end = mend - 1;
			ret = func(&res, kbuf);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक kexec_walk_memblock(काष्ठा kexec_buf *kbuf,
			       पूर्णांक (*func)(काष्ठा resource *, व्योम *))
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * kexec_walk_resources - call func(data) on मुक्त memory regions
 * @kbuf:	Context info क्रम the search. Also passed to @func.
 * @func:	Function to call क्रम each memory region.
 *
 * Return: The memory walk will stop when func वापसs a non-zero value
 * and that value will be वापसed. If all मुक्त regions are visited without
 * func वापसing non-zero, then zero will be वापसed.
 */
अटल पूर्णांक kexec_walk_resources(काष्ठा kexec_buf *kbuf,
				पूर्णांक (*func)(काष्ठा resource *, व्योम *))
अणु
	अगर (kbuf->image->type == KEXEC_TYPE_CRASH)
		वापस walk_iomem_res_desc(crashk_res.desc,
					   IORESOURCE_SYSTEM_RAM | IORESOURCE_BUSY,
					   crashk_res.start, crashk_res.end,
					   kbuf, func);
	अन्यथा
		वापस walk_प्रणाली_ram_res(0, अच_दीर्घ_उच्च, kbuf, func);
पूर्ण

/**
 * kexec_locate_mem_hole - find मुक्त memory क्रम the purgatory or the next kernel
 * @kbuf:	Parameters क्रम the memory search.
 *
 * On success, kbuf->mem will have the start address of the memory region found.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक kexec_locate_mem_hole(काष्ठा kexec_buf *kbuf)
अणु
	पूर्णांक ret;

	/* Arch knows where to place */
	अगर (kbuf->mem != KEXEC_BUF_MEM_UNKNOWN)
		वापस 0;

	अगर (!IS_ENABLED(CONFIG_ARCH_KEEP_MEMBLOCK))
		ret = kexec_walk_resources(kbuf, locate_mem_hole_callback);
	अन्यथा
		ret = kexec_walk_memblock(kbuf, locate_mem_hole_callback);

	वापस ret == 1 ? 0 : -EADDRNOTAVAIL;
पूर्ण

/**
 * arch_kexec_locate_mem_hole - Find मुक्त memory to place the segments.
 * @kbuf:                       Parameters क्रम the memory search.
 *
 * On success, kbuf->mem will have the start address of the memory region found.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक __weak arch_kexec_locate_mem_hole(काष्ठा kexec_buf *kbuf)
अणु
	वापस kexec_locate_mem_hole(kbuf);
पूर्ण

/**
 * kexec_add_buffer - place a buffer in a kexec segment
 * @kbuf:	Buffer contents and memory parameters.
 *
 * This function assumes that kexec_mutex is held.
 * On successful वापस, @kbuf->mem will have the physical address of
 * the buffer in memory.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक kexec_add_buffer(काष्ठा kexec_buf *kbuf)
अणु
	काष्ठा kexec_segment *ksegment;
	पूर्णांक ret;

	/* Currently adding segment this way is allowed only in file mode */
	अगर (!kbuf->image->file_mode)
		वापस -EINVAL;

	अगर (kbuf->image->nr_segments >= KEXEC_SEGMENT_MAX)
		वापस -EINVAL;

	/*
	 * Make sure we are not trying to add buffer after allocating
	 * control pages. All segments need to be placed first beक्रमe
	 * any control pages are allocated. As control page allocation
	 * logic goes through list of segments to make sure there are
	 * no destination overlaps.
	 */
	अगर (!list_empty(&kbuf->image->control_pages)) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	/* Ensure minimum alignment needed क्रम segments. */
	kbuf->memsz = ALIGN(kbuf->memsz, PAGE_SIZE);
	kbuf->buf_align = max(kbuf->buf_align, PAGE_SIZE);

	/* Walk the RAM ranges and allocate a suitable range क्रम the buffer */
	ret = arch_kexec_locate_mem_hole(kbuf);
	अगर (ret)
		वापस ret;

	/* Found a suitable memory range */
	ksegment = &kbuf->image->segment[kbuf->image->nr_segments];
	ksegment->kbuf = kbuf->buffer;
	ksegment->bufsz = kbuf->bufsz;
	ksegment->mem = kbuf->mem;
	ksegment->memsz = kbuf->memsz;
	kbuf->image->nr_segments++;
	वापस 0;
पूर्ण

/* Calculate and store the digest of segments */
अटल पूर्णांक kexec_calculate_store_digests(काष्ठा kimage *image)
अणु
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *desc;
	पूर्णांक ret = 0, i, j, zero_buf_sz, sha_region_sz;
	माप_प्रकार desc_size, nullsz;
	अक्षर *digest;
	व्योम *zero_buf;
	काष्ठा kexec_sha_region *sha_regions;
	काष्ठा purgatory_info *pi = &image->purgatory_info;

	अगर (!IS_ENABLED(CONFIG_ARCH_HAS_KEXEC_PURGATORY))
		वापस 0;

	zero_buf = __va(page_to_pfn(ZERO_PAGE(0)) << PAGE_SHIFT);
	zero_buf_sz = PAGE_SIZE;

	tfm = crypto_alloc_shash("sha256", 0, 0);
	अगर (IS_ERR(tfm)) अणु
		ret = PTR_ERR(tfm);
		जाओ out;
	पूर्ण

	desc_size = crypto_shash_descsize(tfm) + माप(*desc);
	desc = kzalloc(desc_size, GFP_KERNEL);
	अगर (!desc) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_tfm;
	पूर्ण

	sha_region_sz = KEXEC_SEGMENT_MAX * माप(काष्ठा kexec_sha_region);
	sha_regions = vzalloc(sha_region_sz);
	अगर (!sha_regions) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_desc;
	पूर्ण

	desc->tfm   = tfm;

	ret = crypto_shash_init(desc);
	अगर (ret < 0)
		जाओ out_मुक्त_sha_regions;

	digest = kzalloc(SHA256_DIGEST_SIZE, GFP_KERNEL);
	अगर (!digest) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_sha_regions;
	पूर्ण

	क्रम (j = i = 0; i < image->nr_segments; i++) अणु
		काष्ठा kexec_segment *ksegment;

		ksegment = &image->segment[i];
		/*
		 * Skip purgatory as it will be modअगरied once we put digest
		 * info in purgatory.
		 */
		अगर (ksegment->kbuf == pi->purgatory_buf)
			जारी;

		ret = crypto_shash_update(desc, ksegment->kbuf,
					  ksegment->bufsz);
		अगर (ret)
			अवरोध;

		/*
		 * Assume rest of the buffer is filled with zero and
		 * update digest accordingly.
		 */
		nullsz = ksegment->memsz - ksegment->bufsz;
		जबतक (nullsz) अणु
			अचिन्हित दीर्घ bytes = nullsz;

			अगर (bytes > zero_buf_sz)
				bytes = zero_buf_sz;
			ret = crypto_shash_update(desc, zero_buf, bytes);
			अगर (ret)
				अवरोध;
			nullsz -= bytes;
		पूर्ण

		अगर (ret)
			अवरोध;

		sha_regions[j].start = ksegment->mem;
		sha_regions[j].len = ksegment->memsz;
		j++;
	पूर्ण

	अगर (!ret) अणु
		ret = crypto_shash_final(desc, digest);
		अगर (ret)
			जाओ out_मुक्त_digest;
		ret = kexec_purgatory_get_set_symbol(image, "purgatory_sha_regions",
						     sha_regions, sha_region_sz, 0);
		अगर (ret)
			जाओ out_मुक्त_digest;

		ret = kexec_purgatory_get_set_symbol(image, "purgatory_sha256_digest",
						     digest, SHA256_DIGEST_SIZE, 0);
		अगर (ret)
			जाओ out_मुक्त_digest;
	पूर्ण

out_मुक्त_digest:
	kमुक्त(digest);
out_मुक्त_sha_regions:
	vमुक्त(sha_regions);
out_मुक्त_desc:
	kमुक्त(desc);
out_मुक्त_tfm:
	kमुक्त(tfm);
out:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_KEXEC_PURGATORY
/*
 * kexec_purgatory_setup_kbuf - prepare buffer to load purgatory.
 * @pi:		Purgatory to be loaded.
 * @kbuf:	Buffer to setup.
 *
 * Allocates the memory needed क्रम the buffer. Caller is responsible to मुक्त
 * the memory after use.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक kexec_purgatory_setup_kbuf(काष्ठा purgatory_info *pi,
				      काष्ठा kexec_buf *kbuf)
अणु
	स्थिर Elf_Shdr *sechdrs;
	अचिन्हित दीर्घ bss_align;
	अचिन्हित दीर्घ bss_sz;
	अचिन्हित दीर्घ align;
	पूर्णांक i, ret;

	sechdrs = (व्योम *)pi->ehdr + pi->ehdr->e_shoff;
	kbuf->buf_align = bss_align = 1;
	kbuf->bufsz = bss_sz = 0;

	क्रम (i = 0; i < pi->ehdr->e_shnum; i++) अणु
		अगर (!(sechdrs[i].sh_flags & SHF_ALLOC))
			जारी;

		align = sechdrs[i].sh_addralign;
		अगर (sechdrs[i].sh_type != SHT_NOBITS) अणु
			अगर (kbuf->buf_align < align)
				kbuf->buf_align = align;
			kbuf->bufsz = ALIGN(kbuf->bufsz, align);
			kbuf->bufsz += sechdrs[i].sh_size;
		पूर्ण अन्यथा अणु
			अगर (bss_align < align)
				bss_align = align;
			bss_sz = ALIGN(bss_sz, align);
			bss_sz += sechdrs[i].sh_size;
		पूर्ण
	पूर्ण
	kbuf->bufsz = ALIGN(kbuf->bufsz, bss_align);
	kbuf->memsz = kbuf->bufsz + bss_sz;
	अगर (kbuf->buf_align < bss_align)
		kbuf->buf_align = bss_align;

	kbuf->buffer = vzalloc(kbuf->bufsz);
	अगर (!kbuf->buffer)
		वापस -ENOMEM;
	pi->purgatory_buf = kbuf->buffer;

	ret = kexec_add_buffer(kbuf);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	vमुक्त(pi->purgatory_buf);
	pi->purgatory_buf = शून्य;
	वापस ret;
पूर्ण

/*
 * kexec_purgatory_setup_sechdrs - prepares the pi->sechdrs buffer.
 * @pi:		Purgatory to be loaded.
 * @kbuf:	Buffer prepared to store purgatory.
 *
 * Allocates the memory needed क्रम the buffer. Caller is responsible to मुक्त
 * the memory after use.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
अटल पूर्णांक kexec_purgatory_setup_sechdrs(काष्ठा purgatory_info *pi,
					 काष्ठा kexec_buf *kbuf)
अणु
	अचिन्हित दीर्घ bss_addr;
	अचिन्हित दीर्घ offset;
	Elf_Shdr *sechdrs;
	पूर्णांक i;

	/*
	 * The section headers in kexec_purgatory are पढ़ो-only. In order to
	 * have them modअगरiable make a temporary copy.
	 */
	sechdrs = vzalloc(array_size(माप(Elf_Shdr), pi->ehdr->e_shnum));
	अगर (!sechdrs)
		वापस -ENOMEM;
	स_नकल(sechdrs, (व्योम *)pi->ehdr + pi->ehdr->e_shoff,
	       pi->ehdr->e_shnum * माप(Elf_Shdr));
	pi->sechdrs = sechdrs;

	offset = 0;
	bss_addr = kbuf->mem + kbuf->bufsz;
	kbuf->image->start = pi->ehdr->e_entry;

	क्रम (i = 0; i < pi->ehdr->e_shnum; i++) अणु
		अचिन्हित दीर्घ align;
		व्योम *src, *dst;

		अगर (!(sechdrs[i].sh_flags & SHF_ALLOC))
			जारी;

		align = sechdrs[i].sh_addralign;
		अगर (sechdrs[i].sh_type == SHT_NOBITS) अणु
			bss_addr = ALIGN(bss_addr, align);
			sechdrs[i].sh_addr = bss_addr;
			bss_addr += sechdrs[i].sh_size;
			जारी;
		पूर्ण

		offset = ALIGN(offset, align);
		अगर (sechdrs[i].sh_flags & SHF_EXECINSTR &&
		    pi->ehdr->e_entry >= sechdrs[i].sh_addr &&
		    pi->ehdr->e_entry < (sechdrs[i].sh_addr
					 + sechdrs[i].sh_size)) अणु
			kbuf->image->start -= sechdrs[i].sh_addr;
			kbuf->image->start += kbuf->mem + offset;
		पूर्ण

		src = (व्योम *)pi->ehdr + sechdrs[i].sh_offset;
		dst = pi->purgatory_buf + offset;
		स_नकल(dst, src, sechdrs[i].sh_size);

		sechdrs[i].sh_addr = kbuf->mem + offset;
		sechdrs[i].sh_offset = offset;
		offset += sechdrs[i].sh_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kexec_apply_relocations(काष्ठा kimage *image)
अणु
	पूर्णांक i, ret;
	काष्ठा purgatory_info *pi = &image->purgatory_info;
	स्थिर Elf_Shdr *sechdrs;

	sechdrs = (व्योम *)pi->ehdr + pi->ehdr->e_shoff;

	क्रम (i = 0; i < pi->ehdr->e_shnum; i++) अणु
		स्थिर Elf_Shdr *rअन्यथाc;
		स्थिर Elf_Shdr *symtab;
		Elf_Shdr *section;

		rअन्यथाc = sechdrs + i;

		अगर (rअन्यथाc->sh_type != SHT_RELA &&
		    rअन्यथाc->sh_type != SHT_REL)
			जारी;

		/*
		 * For section of type SHT_RELA/SHT_REL,
		 * ->sh_link contains section header index of associated
		 * symbol table. And ->sh_info contains section header
		 * index of section to which relocations apply.
		 */
		अगर (rअन्यथाc->sh_info >= pi->ehdr->e_shnum ||
		    rअन्यथाc->sh_link >= pi->ehdr->e_shnum)
			वापस -ENOEXEC;

		section = pi->sechdrs + rअन्यथाc->sh_info;
		symtab = sechdrs + rअन्यथाc->sh_link;

		अगर (!(section->sh_flags & SHF_ALLOC))
			जारी;

		/*
		 * symtab->sh_link contain section header index of associated
		 * string table.
		 */
		अगर (symtab->sh_link >= pi->ehdr->e_shnum)
			/* Invalid section number? */
			जारी;

		/*
		 * Respective architecture needs to provide support क्रम applying
		 * relocations of type SHT_RELA/SHT_REL.
		 */
		अगर (rअन्यथाc->sh_type == SHT_RELA)
			ret = arch_kexec_apply_relocations_add(pi, section,
							       rअन्यथाc, symtab);
		अन्यथा अगर (rअन्यथाc->sh_type == SHT_REL)
			ret = arch_kexec_apply_relocations(pi, section,
							   rअन्यथाc, symtab);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * kexec_load_purgatory - Load and relocate the purgatory object.
 * @image:	Image to add the purgatory to.
 * @kbuf:	Memory parameters to use.
 *
 * Allocates the memory needed क्रम image->purgatory_info.sechdrs and
 * image->purgatory_info.purgatory_buf/kbuf->buffer. Caller is responsible
 * to मुक्त the memory after use.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक kexec_load_purgatory(काष्ठा kimage *image, काष्ठा kexec_buf *kbuf)
अणु
	काष्ठा purgatory_info *pi = &image->purgatory_info;
	पूर्णांक ret;

	अगर (kexec_purgatory_size <= 0)
		वापस -EINVAL;

	pi->ehdr = (स्थिर Elf_Ehdr *)kexec_purgatory;

	ret = kexec_purgatory_setup_kbuf(pi, kbuf);
	अगर (ret)
		वापस ret;

	ret = kexec_purgatory_setup_sechdrs(pi, kbuf);
	अगर (ret)
		जाओ out_मुक्त_kbuf;

	ret = kexec_apply_relocations(image);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	vमुक्त(pi->sechdrs);
	pi->sechdrs = शून्य;
out_मुक्त_kbuf:
	vमुक्त(pi->purgatory_buf);
	pi->purgatory_buf = शून्य;
	वापस ret;
पूर्ण

/*
 * kexec_purgatory_find_symbol - find a symbol in the purgatory
 * @pi:		Purgatory to search in.
 * @name:	Name of the symbol.
 *
 * Return: poपूर्णांकer to symbol in पढ़ो-only symtab on success, शून्य on error.
 */
अटल स्थिर Elf_Sym *kexec_purgatory_find_symbol(काष्ठा purgatory_info *pi,
						  स्थिर अक्षर *name)
अणु
	स्थिर Elf_Shdr *sechdrs;
	स्थिर Elf_Ehdr *ehdr;
	स्थिर Elf_Sym *syms;
	स्थिर अक्षर *strtab;
	पूर्णांक i, k;

	अगर (!pi->ehdr)
		वापस शून्य;

	ehdr = pi->ehdr;
	sechdrs = (व्योम *)ehdr + ehdr->e_shoff;

	क्रम (i = 0; i < ehdr->e_shnum; i++) अणु
		अगर (sechdrs[i].sh_type != SHT_SYMTAB)
			जारी;

		अगर (sechdrs[i].sh_link >= ehdr->e_shnum)
			/* Invalid strtab section number */
			जारी;
		strtab = (व्योम *)ehdr + sechdrs[sechdrs[i].sh_link].sh_offset;
		syms = (व्योम *)ehdr + sechdrs[i].sh_offset;

		/* Go through symbols क्रम a match */
		क्रम (k = 0; k < sechdrs[i].sh_size/माप(Elf_Sym); k++) अणु
			अगर (ELF_ST_BIND(syms[k].st_info) != STB_GLOBAL)
				जारी;

			अगर (म_भेद(strtab + syms[k].st_name, name) != 0)
				जारी;

			अगर (syms[k].st_shndx == SHN_UNDEF ||
			    syms[k].st_shndx >= ehdr->e_shnum) अणु
				pr_debug("Symbol: %s has bad section index %d.\n",
						name, syms[k].st_shndx);
				वापस शून्य;
			पूर्ण

			/* Found the symbol we are looking क्रम */
			वापस &syms[k];
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम *kexec_purgatory_get_symbol_addr(काष्ठा kimage *image, स्थिर अक्षर *name)
अणु
	काष्ठा purgatory_info *pi = &image->purgatory_info;
	स्थिर Elf_Sym *sym;
	Elf_Shdr *sechdr;

	sym = kexec_purgatory_find_symbol(pi, name);
	अगर (!sym)
		वापस ERR_PTR(-EINVAL);

	sechdr = &pi->sechdrs[sym->st_shndx];

	/*
	 * Returns the address where symbol will finally be loaded after
	 * kexec_load_segment()
	 */
	वापस (व्योम *)(sechdr->sh_addr + sym->st_value);
पूर्ण

/*
 * Get or set value of a symbol. If "get_value" is true, symbol value is
 * वापसed in buf otherwise symbol value is set based on value in buf.
 */
पूर्णांक kexec_purgatory_get_set_symbol(काष्ठा kimage *image, स्थिर अक्षर *name,
				   व्योम *buf, अचिन्हित पूर्णांक size, bool get_value)
अणु
	काष्ठा purgatory_info *pi = &image->purgatory_info;
	स्थिर Elf_Sym *sym;
	Elf_Shdr *sec;
	अक्षर *sym_buf;

	sym = kexec_purgatory_find_symbol(pi, name);
	अगर (!sym)
		वापस -EINVAL;

	अगर (sym->st_size != size) अणु
		pr_err("symbol %s size mismatch: expected %lu actual %u\n",
		       name, (अचिन्हित दीर्घ)sym->st_size, size);
		वापस -EINVAL;
	पूर्ण

	sec = pi->sechdrs + sym->st_shndx;

	अगर (sec->sh_type == SHT_NOBITS) अणु
		pr_err("symbol %s is in a bss section. Cannot %s\n", name,
		       get_value ? "get" : "set");
		वापस -EINVAL;
	पूर्ण

	sym_buf = (अक्षर *)pi->purgatory_buf + sec->sh_offset + sym->st_value;

	अगर (get_value)
		स_नकल((व्योम *)buf, sym_buf, size);
	अन्यथा
		स_नकल((व्योम *)sym_buf, buf, size);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_KEXEC_PURGATORY */

पूर्णांक crash_exclude_mem_range(काष्ठा crash_mem *mem,
			    अचिन्हित दीर्घ दीर्घ mstart, अचिन्हित दीर्घ दीर्घ mend)
अणु
	पूर्णांक i, j;
	अचिन्हित दीर्घ दीर्घ start, end, p_start, p_end;
	काष्ठा crash_mem_range temp_range = अणु0, 0पूर्ण;

	क्रम (i = 0; i < mem->nr_ranges; i++) अणु
		start = mem->ranges[i].start;
		end = mem->ranges[i].end;
		p_start = mstart;
		p_end = mend;

		अगर (mstart > end || mend < start)
			जारी;

		/* Truncate any area outside of range */
		अगर (mstart < start)
			p_start = start;
		अगर (mend > end)
			p_end = end;

		/* Found completely overlapping range */
		अगर (p_start == start && p_end == end) अणु
			mem->ranges[i].start = 0;
			mem->ranges[i].end = 0;
			अगर (i < mem->nr_ranges - 1) अणु
				/* Shअगरt rest of the ranges to left */
				क्रम (j = i; j < mem->nr_ranges - 1; j++) अणु
					mem->ranges[j].start =
						mem->ranges[j+1].start;
					mem->ranges[j].end =
							mem->ranges[j+1].end;
				पूर्ण

				/*
				 * Continue to check अगर there are another overlapping ranges
				 * from the current position because of shअगरting the above
				 * mem ranges.
				 */
				i--;
				mem->nr_ranges--;
				जारी;
			पूर्ण
			mem->nr_ranges--;
			वापस 0;
		पूर्ण

		अगर (p_start > start && p_end < end) अणु
			/* Split original range */
			mem->ranges[i].end = p_start - 1;
			temp_range.start = p_end + 1;
			temp_range.end = end;
		पूर्ण अन्यथा अगर (p_start != start)
			mem->ranges[i].end = p_start - 1;
		अन्यथा
			mem->ranges[i].start = p_end + 1;
		अवरोध;
	पूर्ण

	/* If a split happened, add the split to array */
	अगर (!temp_range.end)
		वापस 0;

	/* Split happened */
	अगर (i == mem->max_nr_ranges - 1)
		वापस -ENOMEM;

	/* Location where new range should go */
	j = i + 1;
	अगर (j < mem->nr_ranges) अणु
		/* Move over all ranges one slot towards the end */
		क्रम (i = mem->nr_ranges - 1; i >= j; i--)
			mem->ranges[i + 1] = mem->ranges[i];
	पूर्ण

	mem->ranges[j].start = temp_range.start;
	mem->ranges[j].end = temp_range.end;
	mem->nr_ranges++;
	वापस 0;
पूर्ण

पूर्णांक crash_prepare_elf64_headers(काष्ठा crash_mem *mem, पूर्णांक kernel_map,
			  व्योम **addr, अचिन्हित दीर्घ *sz)
अणु
	Elf64_Ehdr *ehdr;
	Elf64_Phdr *phdr;
	अचिन्हित दीर्घ nr_cpus = num_possible_cpus(), nr_phdr, elf_sz;
	अचिन्हित अक्षर *buf;
	अचिन्हित पूर्णांक cpu, i;
	अचिन्हित दीर्घ दीर्घ notes_addr;
	अचिन्हित दीर्घ mstart, mend;

	/* extra phdr क्रम vmcoreinfo ELF note */
	nr_phdr = nr_cpus + 1;
	nr_phdr += mem->nr_ranges;

	/*
	 * kexec-tools creates an extra PT_LOAD phdr क्रम kernel text mapping
	 * area (क्रम example, ffffffff80000000 - ffffffffa0000000 on x86_64).
	 * I think this is required by tools like gdb. So same physical
	 * memory will be mapped in two ELF headers. One will contain kernel
	 * text भव addresses and other will have __va(physical) addresses.
	 */

	nr_phdr++;
	elf_sz = माप(Elf64_Ehdr) + nr_phdr * माप(Elf64_Phdr);
	elf_sz = ALIGN(elf_sz, ELF_CORE_HEADER_ALIGN);

	buf = vzalloc(elf_sz);
	अगर (!buf)
		वापस -ENOMEM;

	ehdr = (Elf64_Ehdr *)buf;
	phdr = (Elf64_Phdr *)(ehdr + 1);
	स_नकल(ehdr->e_ident, ELFMAG, SELFMAG);
	ehdr->e_ident[EI_CLASS] = ELFCLASS64;
	ehdr->e_ident[EI_DATA] = ELFDATA2LSB;
	ehdr->e_ident[EI_VERSION] = EV_CURRENT;
	ehdr->e_ident[EI_OSABI] = ELF_OSABI;
	स_रखो(ehdr->e_ident + EI_PAD, 0, EI_NIDENT - EI_PAD);
	ehdr->e_type = ET_CORE;
	ehdr->e_machine = ELF_ARCH;
	ehdr->e_version = EV_CURRENT;
	ehdr->e_phoff = माप(Elf64_Ehdr);
	ehdr->e_ehsize = माप(Elf64_Ehdr);
	ehdr->e_phentsize = माप(Elf64_Phdr);

	/* Prepare one phdr of type PT_NOTE क्रम each present CPU */
	क्रम_each_present_cpu(cpu) अणु
		phdr->p_type = PT_NOTE;
		notes_addr = per_cpu_ptr_to_phys(per_cpu_ptr(crash_notes, cpu));
		phdr->p_offset = phdr->p_paddr = notes_addr;
		phdr->p_filesz = phdr->p_memsz = माप(note_buf_t);
		(ehdr->e_phnum)++;
		phdr++;
	पूर्ण

	/* Prepare one PT_NOTE header क्रम vmcoreinfo */
	phdr->p_type = PT_NOTE;
	phdr->p_offset = phdr->p_paddr = paddr_vmcoreinfo_note();
	phdr->p_filesz = phdr->p_memsz = VMCOREINFO_NOTE_SIZE;
	(ehdr->e_phnum)++;
	phdr++;

	/* Prepare PT_LOAD type program header क्रम kernel text region */
	अगर (kernel_map) अणु
		phdr->p_type = PT_LOAD;
		phdr->p_flags = PF_R|PF_W|PF_X;
		phdr->p_vaddr = (अचिन्हित दीर्घ) _text;
		phdr->p_filesz = phdr->p_memsz = _end - _text;
		phdr->p_offset = phdr->p_paddr = __pa_symbol(_text);
		ehdr->e_phnum++;
		phdr++;
	पूर्ण

	/* Go through all the ranges in mem->ranges[] and prepare phdr */
	क्रम (i = 0; i < mem->nr_ranges; i++) अणु
		mstart = mem->ranges[i].start;
		mend = mem->ranges[i].end;

		phdr->p_type = PT_LOAD;
		phdr->p_flags = PF_R|PF_W|PF_X;
		phdr->p_offset  = mstart;

		phdr->p_paddr = mstart;
		phdr->p_vaddr = (अचिन्हित दीर्घ) __va(mstart);
		phdr->p_filesz = phdr->p_memsz = mend - mstart + 1;
		phdr->p_align = 0;
		ehdr->e_phnum++;
		pr_debug("Crash PT_LOAD ELF header. phdr=%p vaddr=0x%llx, paddr=0x%llx, sz=0x%llx e_phnum=%d p_offset=0x%llx\n",
			phdr, phdr->p_vaddr, phdr->p_paddr, phdr->p_filesz,
			ehdr->e_phnum, phdr->p_offset);
		phdr++;
	पूर्ण

	*addr = buf;
	*sz = elf_sz;
	वापस 0;
पूर्ण
