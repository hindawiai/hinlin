<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _LINUX_RANDOMIZE_KSTACK_H
#घोषणा _LINUX_RANDOMIZE_KSTACK_H

#समावेश <linux/kernel.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/percpu-defs.h>

DECLARE_STATIC_KEY_MAYBE(CONFIG_RANDOMIZE_KSTACK_OFFSET_DEFAULT,
			 अक्रमomize_kstack_offset);
DECLARE_PER_CPU(u32, kstack_offset);

/*
 * Do not use this anywhere अन्यथा in the kernel. This is used here because
 * it provides an arch-agnostic way to grow the stack with correct
 * alignment. Also, since this use is being explicitly masked to a max of
 * 10 bits, stack-clash style attacks are unlikely. For more details see
 * "VLAs" in Documentation/process/deprecated.rst
 */
व्योम *__builtin_alloca(माप_प्रकार size);
/*
 * Use, at most, 10 bits of entropy. We explicitly cap this to keep the
 * "VLA" from being unbounded (see above). 10 bits leaves enough room क्रम
 * per-arch offset masks to reduce entropy (by removing higher bits, since
 * high entropy may overly स्थिरrain usable stack space), and क्रम
 * compiler/arch-specअगरic stack alignment to हटाओ the lower bits.
 */
#घोषणा KSTACK_OFFSET_MAX(x)	((x) & 0x3FF)

/*
 * These macros must be used during syscall entry when पूर्णांकerrupts and
 * preempt are disabled, and after user रेजिस्टरs have been stored to
 * the stack.
 */
#घोषणा add_अक्रमom_kstack_offset() करो अणु					\
	अगर (अटल_branch_maybe(CONFIG_RANDOMIZE_KSTACK_OFFSET_DEFAULT,	\
				&अक्रमomize_kstack_offset)) अणु		\
		u32 offset = raw_cpu_पढ़ो(kstack_offset);		\
		u8 *ptr = __builtin_alloca(KSTACK_OFFSET_MAX(offset));	\
		/* Keep allocation even after "ptr" loses scope. */	\
		यंत्र अस्थिर("" :: "r"(ptr) : "memory");		\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा choose_अक्रमom_kstack_offset(अक्रम) करो अणु				\
	अगर (अटल_branch_maybe(CONFIG_RANDOMIZE_KSTACK_OFFSET_DEFAULT,	\
				&अक्रमomize_kstack_offset)) अणु		\
		u32 offset = raw_cpu_पढ़ो(kstack_offset);		\
		offset ^= (अक्रम);					\
		raw_cpu_ग_लिखो(kstack_offset, offset);			\
	पूर्ण								\
पूर्ण जबतक (0)

#पूर्ण_अगर
