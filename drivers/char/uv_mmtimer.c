<शैली गुरु>
/*
 * Timer device implementation क्रम SGI UV platक्रमm.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2009 Silicon Graphics, Inc.  All rights reserved.
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/mmसमयr.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <linux/math64.h>

#समावेश <यंत्र/genapic.h>
#समावेश <यंत्र/uv/uv_hub.h>
#समावेश <यंत्र/uv/मूलप्रण.स>
#समावेश <यंत्र/uv/uv.h>

MODULE_AUTHOR("Dimitri Sivanich <sivanich@sgi.com>");
MODULE_DESCRIPTION("SGI UV Memory Mapped RTC Timer");
MODULE_LICENSE("GPL");

/* name of the device, usually in /dev */
#घोषणा UV_MMTIMER_NAME "mmtimer"
#घोषणा UV_MMTIMER_DESC "SGI UV Memory Mapped RTC Timer"
#घोषणा UV_MMTIMER_VERSION "1.0"

अटल दीर्घ uv_mmसमयr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg);
अटल पूर्णांक uv_mmसमयr_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);

/*
 * Period in femtoseconds (10^-15 s)
 */
अटल अचिन्हित दीर्घ uv_mmसमयr_femtoperiod;

अटल स्थिर काष्ठा file_operations uv_mmसमयr_fops = अणु
	.owner = THIS_MODULE,
	.mmap =	uv_mmसमयr_mmap,
	.unlocked_ioctl = uv_mmसमयr_ioctl,
	.llseek = noop_llseek,
पूर्ण;

/**
 * uv_mmसमयr_ioctl - ioctl पूर्णांकerface क्रम /dev/uv_mmसमयr
 * @file: file काष्ठाure क्रम the device
 * @cmd: command to execute
 * @arg: optional argument to command
 *
 * Executes the command specअगरied by @cmd.  Returns 0 क्रम success, < 0 क्रम
 * failure.
 *
 * Valid commands:
 *
 * %MMTIMER_GETOFFSET - Should वापस the offset (relative to the start
 * of the page where the रेजिस्टरs are mapped) क्रम the counter in question.
 *
 * %MMTIMER_GETRES - Returns the resolution of the घड़ी in femto (10^-15)
 * seconds
 *
 * %MMTIMER_GETFREQ - Copies the frequency of the घड़ी in Hz to the address
 * specअगरied by @arg
 *
 * %MMTIMER_GETBITS - Returns the number of bits in the घड़ी's counter
 *
 * %MMTIMER_MMAPAVAIL - Returns 1 अगर रेजिस्टरs can be mmap'd पूर्णांकo userspace
 *
 * %MMTIMER_GETCOUNTER - Gets the current value in the counter and places it
 * in the address specअगरied by @arg.
 */
अटल दीर्घ uv_mmसमयr_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
						अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल MMTIMER_GETOFFSET:	/* offset of the counter */
		/*
		 * Starting with HUB rev 2.0, the UV RTC रेजिस्टर is
		 * replicated across all cachelines of it's own page.
		 * This allows faster simultaneous पढ़ोs from a given socket.
		 *
		 * The offset वापसed is in 64 bit units.
		 */
		अगर (uv_get_min_hub_revision_id() == 1)
			ret = 0;
		अन्यथा
			ret = ((uv_blade_processor_id() * L1_CACHE_BYTES) %
					PAGE_SIZE) / 8;
		अवरोध;

	हाल MMTIMER_GETRES: /* resolution of the घड़ी in 10^-15 s */
		अगर (copy_to_user((अचिन्हित दीर्घ __user *)arg,
				&uv_mmसमयr_femtoperiod, माप(अचिन्हित दीर्घ)))
			ret = -EFAULT;
		अवरोध;

	हाल MMTIMER_GETFREQ: /* frequency in Hz */
		अगर (copy_to_user((अचिन्हित दीर्घ __user *)arg,
				&sn_rtc_cycles_per_second,
				माप(अचिन्हित दीर्घ)))
			ret = -EFAULT;
		अवरोध;

	हाल MMTIMER_GETBITS: /* number of bits in the घड़ी */
		ret = hweight64(UVH_RTC_REAL_TIME_CLOCK_MASK);
		अवरोध;

	हाल MMTIMER_MMAPAVAIL:
		ret = 1;
		अवरोध;

	हाल MMTIMER_GETCOUNTER:
		अगर (copy_to_user((अचिन्हित दीर्घ __user *)arg,
				(अचिन्हित दीर्घ *)uv_local_mmr_address(UVH_RTC),
				माप(अचिन्हित दीर्घ)))
			ret = -EFAULT;
		अवरोध;
	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * uv_mmसमयr_mmap - maps the घड़ी's रेजिस्टरs पूर्णांकo userspace
 * @file: file काष्ठाure क्रम the device
 * @vma: VMA to map the रेजिस्टरs पूर्णांकo
 *
 * Calls remap_pfn_range() to map the घड़ी's रेजिस्टरs पूर्णांकo
 * the calling process' address space.
 */
अटल पूर्णांक uv_mmसमयr_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ uv_mmसमयr_addr;

	अगर (vma->vm_end - vma->vm_start != PAGE_SIZE)
		वापस -EINVAL;

	अगर (vma->vm_flags & VM_WRITE)
		वापस -EPERM;

	अगर (PAGE_SIZE > (1 << 16))
		वापस -ENOSYS;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	uv_mmसमयr_addr = UV_LOCAL_MMR_BASE | UVH_RTC;
	uv_mmसमयr_addr &= ~(PAGE_SIZE - 1);
	uv_mmसमयr_addr &= 0xfffffffffffffffUL;

	अगर (remap_pfn_range(vma, vma->vm_start, uv_mmसमयr_addr >> PAGE_SHIFT,
					PAGE_SIZE, vma->vm_page_prot)) अणु
		prपूर्णांकk(KERN_ERR "remap_pfn_range failed in uv_mmtimer_mmap\n");
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा miscdevice uv_mmसमयr_miscdev = अणु
	MISC_DYNAMIC_MINOR,
	UV_MMTIMER_NAME,
	&uv_mmसमयr_fops
पूर्ण;


/**
 * uv_mmसमयr_init - device initialization routine
 *
 * Does initial setup क्रम the uv_mmसमयr device.
 */
अटल पूर्णांक __init uv_mmसमयr_init(व्योम)
अणु
	अगर (!is_uv_प्रणाली()) अणु
		prपूर्णांकk(KERN_ERR "%s: Hardware unsupported\n", UV_MMTIMER_NAME);
		वापस -1;
	पूर्ण

	/*
	 * Sanity check the cycles/sec variable
	 */
	अगर (sn_rtc_cycles_per_second < 100000) अणु
		prपूर्णांकk(KERN_ERR "%s: unable to determine clock frequency\n",
		       UV_MMTIMER_NAME);
		वापस -1;
	पूर्ण

	uv_mmसमयr_femtoperiod = ((अचिन्हित दीर्घ)1E15 +
				sn_rtc_cycles_per_second / 2) /
				sn_rtc_cycles_per_second;

	अगर (misc_रेजिस्टर(&uv_mmसमयr_miscdev)) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to register device\n",
		       UV_MMTIMER_NAME);
		वापस -1;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: v%s, %ld MHz\n", UV_MMTIMER_DESC,
		UV_MMTIMER_VERSION,
		sn_rtc_cycles_per_second/(अचिन्हित दीर्घ)1E6);

	वापस 0;
पूर्ण

module_init(uv_mmसमयr_init);
