<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kexec.c - kexec_load प्रणाली call
 * Copyright (C) 2002-2004 Eric Biederman  <ebiederm@xmission.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/mm.h>
#समावेश <linux/file.h>
#समावेश <linux/security.h>
#समावेश <linux/kexec.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>

#समावेश "kexec_internal.h"

अटल पूर्णांक copy_user_segment_list(काष्ठा kimage *image,
				  अचिन्हित दीर्घ nr_segments,
				  काष्ठा kexec_segment __user *segments)
अणु
	पूर्णांक ret;
	माप_प्रकार segment_bytes;

	/* Read in the segments */
	image->nr_segments = nr_segments;
	segment_bytes = nr_segments * माप(*segments);
	ret = copy_from_user(image->segment, segments, segment_bytes);
	अगर (ret)
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल पूर्णांक kimage_alloc_init(काष्ठा kimage **rimage, अचिन्हित दीर्घ entry,
			     अचिन्हित दीर्घ nr_segments,
			     काष्ठा kexec_segment __user *segments,
			     अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;
	काष्ठा kimage *image;
	bool kexec_on_panic = flags & KEXEC_ON_CRASH;

	अगर (kexec_on_panic) अणु
		/* Verअगरy we have a valid entry poपूर्णांक */
		अगर ((entry < phys_to_boot_phys(crashk_res.start)) ||
		    (entry > phys_to_boot_phys(crashk_res.end)))
			वापस -EADDRNOTAVAIL;
	पूर्ण

	/* Allocate and initialize a controlling काष्ठाure */
	image = करो_kimage_alloc_init();
	अगर (!image)
		वापस -ENOMEM;

	image->start = entry;

	ret = copy_user_segment_list(image, nr_segments, segments);
	अगर (ret)
		जाओ out_मुक्त_image;

	अगर (kexec_on_panic) अणु
		/* Enable special crash kernel control page alloc policy. */
		image->control_page = crashk_res.start;
		image->type = KEXEC_TYPE_CRASH;
	पूर्ण

	ret = sanity_check_segment_list(image);
	अगर (ret)
		जाओ out_मुक्त_image;

	/*
	 * Find a location क्रम the control code buffer, and add it
	 * the vector of segments so that it's pages will also be
	 * counted as destination pages.
	 */
	ret = -ENOMEM;
	image->control_code_page = kimage_alloc_control_pages(image,
					   get_order(KEXEC_CONTROL_PAGE_SIZE));
	अगर (!image->control_code_page) अणु
		pr_err("Could not allocate control_code_buffer\n");
		जाओ out_मुक्त_image;
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
out_मुक्त_image:
	kमुक्त(image);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_kexec_load(अचिन्हित दीर्घ entry, अचिन्हित दीर्घ nr_segments,
		काष्ठा kexec_segment __user *segments, अचिन्हित दीर्घ flags)
अणु
	काष्ठा kimage **dest_image, *image;
	अचिन्हित दीर्घ i;
	पूर्णांक ret;

	अगर (flags & KEXEC_ON_CRASH) अणु
		dest_image = &kexec_crash_image;
		अगर (kexec_crash_image)
			arch_kexec_unprotect_crashkres();
	पूर्ण अन्यथा अणु
		dest_image = &kexec_image;
	पूर्ण

	अगर (nr_segments == 0) अणु
		/* Uninstall image */
		kimage_मुक्त(xchg(dest_image, शून्य));
		वापस 0;
	पूर्ण
	अगर (flags & KEXEC_ON_CRASH) अणु
		/*
		 * Loading another kernel to चयन to अगर this one
		 * crashes.  Free any current crash dump kernel beक्रमe
		 * we corrupt it.
		 */
		kimage_मुक्त(xchg(&kexec_crash_image, शून्य));
	पूर्ण

	ret = kimage_alloc_init(&image, entry, nr_segments, segments, flags);
	अगर (ret)
		वापस ret;

	अगर (flags & KEXEC_PRESERVE_CONTEXT)
		image->preserve_context = 1;

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

	क्रम (i = 0; i < nr_segments; i++) अणु
		ret = kimage_load_segment(image, &image->segment[i]);
		अगर (ret)
			जाओ out;
	पूर्ण

	kimage_terminate(image);

	ret = machine_kexec_post_load(image);
	अगर (ret)
		जाओ out;

	/* Install the new kernel and uninstall the old */
	image = xchg(dest_image, image);

out:
	अगर ((flags & KEXEC_ON_CRASH) && kexec_crash_image)
		arch_kexec_protect_crashkres();

	kimage_मुक्त(image);
	वापस ret;
पूर्ण

/*
 * Exec Kernel प्रणाली call: क्रम obvious reasons only root may call it.
 *
 * This call अवरोधs up पूर्णांकo three pieces.
 * - A generic part which loads the new kernel from the current
 *   address space, and very carefully places the data in the
 *   allocated pages.
 *
 * - A generic part that पूर्णांकeracts with the kernel and tells all of
 *   the devices to shut करोwn.  Preventing on-going dmas, and placing
 *   the devices in a consistent state so a later kernel can
 *   reinitialize them.
 *
 * - A machine specअगरic part that includes the syscall number
 *   and then copies the image to it's final destination.  And
 *   jumps पूर्णांकo the image at entry.
 *
 * kexec करोes not sync, or unmount fileप्रणालीs so अगर you need
 * that to happen you need to करो that yourself.
 */

अटल अंतरभूत पूर्णांक kexec_load_check(अचिन्हित दीर्घ nr_segments,
				   अचिन्हित दीर्घ flags)
अणु
	पूर्णांक result;

	/* We only trust the superuser with rebooting the प्रणाली. */
	अगर (!capable(CAP_SYS_BOOT) || kexec_load_disabled)
		वापस -EPERM;

	/* Permit LSMs and IMA to fail the kexec */
	result = security_kernel_load_data(LOADING_KEXEC_IMAGE, false);
	अगर (result < 0)
		वापस result;

	/*
	 * kexec can be used to circumvent module loading restrictions, so
	 * prevent loading in that हाल
	 */
	result = security_locked_करोwn(LOCKDOWN_KEXEC);
	अगर (result)
		वापस result;

	/*
	 * Verअगरy we have a legal set of flags
	 * This leaves us room क्रम future extensions.
	 */
	अगर ((flags & KEXEC_FLAGS) != (flags & ~KEXEC_ARCH_MASK))
		वापस -EINVAL;

	/* Put an artअगरicial cap on the number
	 * of segments passed to kexec_load.
	 */
	अगर (nr_segments > KEXEC_SEGMENT_MAX)
		वापस -EINVAL;

	वापस 0;
पूर्ण

SYSCALL_DEFINE4(kexec_load, अचिन्हित दीर्घ, entry, अचिन्हित दीर्घ, nr_segments,
		काष्ठा kexec_segment __user *, segments, अचिन्हित दीर्घ, flags)
अणु
	पूर्णांक result;

	result = kexec_load_check(nr_segments, flags);
	अगर (result)
		वापस result;

	/* Verअगरy we are on the appropriate architecture */
	अगर (((flags & KEXEC_ARCH_MASK) != KEXEC_ARCH) &&
		((flags & KEXEC_ARCH_MASK) != KEXEC_ARCH_DEFAULT))
		वापस -EINVAL;

	/* Because we ग_लिखो directly to the reserved memory
	 * region when loading crash kernels we need a mutex here to
	 * prevent multiple crash  kernels from attempting to load
	 * simultaneously, and to prevent a crash kernel from loading
	 * over the top of a in use crash kernel.
	 *
	 * KISS: always take the mutex.
	 */
	अगर (!mutex_trylock(&kexec_mutex))
		वापस -EBUSY;

	result = करो_kexec_load(entry, nr_segments, segments, flags);

	mutex_unlock(&kexec_mutex);

	वापस result;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE4(kexec_load, compat_uदीर्घ_t, entry,
		       compat_uदीर्घ_t, nr_segments,
		       काष्ठा compat_kexec_segment __user *, segments,
		       compat_uदीर्घ_t, flags)
अणु
	काष्ठा compat_kexec_segment in;
	काष्ठा kexec_segment out, __user *ksegments;
	अचिन्हित दीर्घ i, result;

	result = kexec_load_check(nr_segments, flags);
	अगर (result)
		वापस result;

	/* Don't allow clients that don't understand the native
	 * architecture to करो anything.
	 */
	अगर ((flags & KEXEC_ARCH_MASK) == KEXEC_ARCH_DEFAULT)
		वापस -EINVAL;

	ksegments = compat_alloc_user_space(nr_segments * माप(out));
	क्रम (i = 0; i < nr_segments; i++) अणु
		result = copy_from_user(&in, &segments[i], माप(in));
		अगर (result)
			वापस -EFAULT;

		out.buf   = compat_ptr(in.buf);
		out.bufsz = in.bufsz;
		out.mem   = in.mem;
		out.memsz = in.memsz;

		result = copy_to_user(&ksegments[i], &out, माप(out));
		अगर (result)
			वापस -EFAULT;
	पूर्ण

	/* Because we ग_लिखो directly to the reserved memory
	 * region when loading crash kernels we need a mutex here to
	 * prevent multiple crash  kernels from attempting to load
	 * simultaneously, and to prevent a crash kernel from loading
	 * over the top of a in use crash kernel.
	 *
	 * KISS: always take the mutex.
	 */
	अगर (!mutex_trylock(&kexec_mutex))
		वापस -EBUSY;

	result = करो_kexec_load(entry, nr_segments, ksegments, flags);

	mutex_unlock(&kexec_mutex);

	वापस result;
पूर्ण
#पूर्ण_अगर
