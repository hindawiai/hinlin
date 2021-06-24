<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Access kernel memory without faulting -- s390 specअगरic implementation.
 *
 * Copyright IBM Corp. 2009, 2015
 *
 *   Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>,
 *
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/cpu.h>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/stacktrace.h>

अटल notrace दीर्घ s390_kernel_ग_लिखो_odd(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ aligned, offset, count;
	अक्षर पंचांगp[8];

	aligned = (अचिन्हित दीर्घ) dst & ~7UL;
	offset = (अचिन्हित दीर्घ) dst & 7UL;
	size = min(8UL - offset, size);
	count = size - 1;
	यंत्र अस्थिर(
		"	bras	1,0f\n"
		"	mvc	0(1,%4),0(%5)\n"
		"0:	mvc	0(8,%3),0(%0)\n"
		"	ex	%1,0(1)\n"
		"	lg	%1,0(%3)\n"
		"	lra	%0,0(%0)\n"
		"	sturg	%1,%0\n"
		: "+&a" (aligned), "+&a" (count), "=m" (पंचांगp)
		: "a" (&पंचांगp), "a" (&पंचांगp[offset]), "a" (src)
		: "cc", "memory", "1");
	वापस size;
पूर्ण

/*
 * s390_kernel_ग_लिखो - ग_लिखो to kernel memory bypassing DAT
 * @dst: destination address
 * @src: source address
 * @size: number of bytes to copy
 *
 * This function ग_लिखोs to kernel memory bypassing DAT and possible page table
 * ग_लिखो protection. It ग_लिखोs to the destination using the sturg inकाष्ठाion.
 * Thereक्रमe we have a पढ़ो-modअगरy-ग_लिखो sequence: the function पढ़ोs eight
 * bytes from destination at an eight byte boundary, modअगरies the bytes
 * requested and ग_लिखोs the result back in a loop.
 */
अटल DEFINE_SPINLOCK(s390_kernel_ग_लिखो_lock);

notrace व्योम *s390_kernel_ग_लिखो(व्योम *dst, स्थिर व्योम *src, माप_प्रकार size)
अणु
	व्योम *पंचांगp = dst;
	अचिन्हित दीर्घ flags;
	दीर्घ copied;

	spin_lock_irqsave(&s390_kernel_ग_लिखो_lock, flags);
	अगर (!(flags & PSW_MASK_DAT)) अणु
		स_नकल(dst, src, size);
	पूर्ण अन्यथा अणु
		जबतक (size) अणु
			copied = s390_kernel_ग_लिखो_odd(पंचांगp, src, size);
			पंचांगp += copied;
			src += copied;
			size -= copied;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&s390_kernel_ग_लिखो_lock, flags);

	वापस dst;
पूर्ण

अटल पूर्णांक __no_sanitize_address __स_नकल_real(व्योम *dest, व्योम *src, माप_प्रकार count)
अणु
	रेजिस्टर अचिन्हित दीर्घ _dest यंत्र("2") = (अचिन्हित दीर्घ) dest;
	रेजिस्टर अचिन्हित दीर्घ _len1 यंत्र("3") = (अचिन्हित दीर्घ) count;
	रेजिस्टर अचिन्हित दीर्घ _src  यंत्र("4") = (अचिन्हित दीर्घ) src;
	रेजिस्टर अचिन्हित दीर्घ _len2 यंत्र("5") = (अचिन्हित दीर्घ) count;
	पूर्णांक rc = -EFAULT;

	यंत्र अस्थिर (
		"0:	mvcle	%1,%2,0x0\n"
		"1:	jo	0b\n"
		"	lhi	%0,0x0\n"
		"2:\n"
		EX_TABLE(1b,2b)
		: "+d" (rc), "+d" (_dest), "+d" (_src), "+d" (_len1),
		  "+d" (_len2), "=m" (*((दीर्घ *) dest))
		: "m" (*((दीर्घ *) src))
		: "cc", "memory");
	वापस rc;
पूर्ण

अटल अचिन्हित दीर्घ __no_sanitize_address _स_नकल_real(अचिन्हित दीर्घ dest,
							अचिन्हित दीर्घ src,
							अचिन्हित दीर्घ count)
अणु
	पूर्णांक irqs_disabled, rc;
	अचिन्हित दीर्घ flags;

	अगर (!count)
		वापस 0;
	flags = arch_local_irq_save();
	irqs_disabled = arch_irqs_disabled_flags(flags);
	अगर (!irqs_disabled)
		trace_hardirqs_off();
	__arch_local_irq_stnsm(0xf8); // disable DAT
	rc = __स_नकल_real((व्योम *) dest, (व्योम *) src, (माप_प्रकार) count);
	अगर (flags & PSW_MASK_DAT)
		__arch_local_irq_stosm(0x04); // enable DAT
	अगर (!irqs_disabled)
		trace_hardirqs_on();
	__arch_local_irq_ssm(flags);
	वापस rc;
पूर्ण

/*
 * Copy memory in real mode (kernel to kernel)
 */
पूर्णांक स_नकल_real(व्योम *dest, व्योम *src, माप_प्रकार count)
अणु
	पूर्णांक rc;

	अगर (S390_lowcore.nodat_stack != 0) अणु
		preempt_disable();
		rc = CALL_ON_STACK(_स_नकल_real, S390_lowcore.nodat_stack, 3,
				   dest, src, count);
		preempt_enable();
		वापस rc;
	पूर्ण
	/*
	 * This is a really early स_नकल_real call, the stacks are
	 * not set up yet. Just call _स_नकल_real on the early boot
	 * stack
	 */
	वापस _स_नकल_real((अचिन्हित दीर्घ) dest,(अचिन्हित दीर्घ) src,
			    (अचिन्हित दीर्घ) count);
पूर्ण

/*
 * Copy memory in असलolute mode (kernel to kernel)
 */
व्योम स_नकल_असलolute(व्योम *dest, व्योम *src, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ cr0, flags, prefix;

	flags = arch_local_irq_save();
	__ctl_store(cr0, 0, 0);
	__ctl_clear_bit(0, 28); /* disable lowcore protection */
	prefix = store_prefix();
	अगर (prefix) अणु
		local_mcck_disable();
		set_prefix(0);
		स_नकल(dest, src, count);
		set_prefix(prefix);
		local_mcck_enable();
	पूर्ण अन्यथा अणु
		स_नकल(dest, src, count);
	पूर्ण
	__ctl_load(cr0, 0, 0);
	arch_local_irq_restore(flags);
पूर्ण

/*
 * Copy memory from kernel (real) to user (भव)
 */
पूर्णांक copy_to_user_real(व्योम __user *dest, व्योम *src, अचिन्हित दीर्घ count)
अणु
	पूर्णांक offs = 0, size, rc;
	अक्षर *buf;

	buf = (अक्षर *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	rc = -EFAULT;
	जबतक (offs < count) अणु
		size = min(PAGE_SIZE, count - offs);
		अगर (स_नकल_real(buf, src + offs, size))
			जाओ out;
		अगर (copy_to_user(dest + offs, buf, size))
			जाओ out;
		offs += size;
	पूर्ण
	rc = 0;
out:
	मुक्त_page((अचिन्हित दीर्घ) buf);
	वापस rc;
पूर्ण

/*
 * Check अगर physical address is within prefix or zero page
 */
अटल पूर्णांक is_swapped(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ lc;
	पूर्णांक cpu;

	अगर (addr < माप(काष्ठा lowcore))
		वापस 1;
	क्रम_each_online_cpu(cpu) अणु
		lc = (अचिन्हित दीर्घ) lowcore_ptr[cpu];
		अगर (addr > lc + माप(काष्ठा lowcore) - 1 || addr < lc)
			जारी;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Convert a physical poपूर्णांकer क्रम /dev/mem access
 *
 * For swapped prefix pages a new buffer is वापसed that contains a copy of
 * the असलolute memory. The buffer size is maximum one page large.
 */
व्योम *xlate_dev_mem_ptr(phys_addr_t addr)
अणु
	व्योम *bounce = (व्योम *) addr;
	अचिन्हित दीर्घ size;

	get_online_cpus();
	preempt_disable();
	अगर (is_swapped(addr)) अणु
		size = PAGE_SIZE - (addr & ~PAGE_MASK);
		bounce = (व्योम *) __get_मुक्त_page(GFP_ATOMIC);
		अगर (bounce)
			स_नकल_असलolute(bounce, (व्योम *) addr, size);
	पूर्ण
	preempt_enable();
	put_online_cpus();
	वापस bounce;
पूर्ण

/*
 * Free converted buffer क्रम /dev/mem access (अगर necessary)
 */
व्योम unxlate_dev_mem_ptr(phys_addr_t addr, व्योम *buf)
अणु
	अगर ((व्योम *) addr != buf)
		मुक्त_page((अचिन्हित दीर्घ) buf);
पूर्ण
