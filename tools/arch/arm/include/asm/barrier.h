<शैली गुरु>
#अगर_अघोषित _TOOLS_LINUX_ASM_ARM_BARRIER_H
#घोषणा _TOOLS_LINUX_ASM_ARM_BARRIER_H

/*
 * Use the __kuser_memory_barrier helper in the CPU helper page. See
 * arch/arm/kernel/entry-armv.S in the kernel source क्रम details.
 */
#घोषणा mb()		((व्योम(*)(व्योम))0xffff0fa0)()
#घोषणा wmb()		((व्योम(*)(व्योम))0xffff0fa0)()
#घोषणा rmb()		((व्योम(*)(व्योम))0xffff0fa0)()

#पूर्ण_अगर /* _TOOLS_LINUX_ASM_ARM_BARRIER_H */
