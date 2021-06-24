<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_XEN_INTERFACE_64_H
#घोषणा _ASM_X86_XEN_INTERFACE_64_H

/*
 * 64-bit segment selectors
 * These flat segments are in the Xen-निजी section of every GDT. Since these
 * are also present in the initial GDT, many OSes will be able to aव्योम
 * installing their own GDT.
 */

#घोषणा FLAT_RING3_CS32 0xe023  /* GDT index 260 */
#घोषणा FLAT_RING3_CS64 0xe033  /* GDT index 261 */
#घोषणा FLAT_RING3_DS32 0xe02b  /* GDT index 262 */
#घोषणा FLAT_RING3_DS64 0x0000  /* शून्य selector */
#घोषणा FLAT_RING3_SS32 0xe02b  /* GDT index 262 */
#घोषणा FLAT_RING3_SS64 0xe02b  /* GDT index 262 */

#घोषणा FLAT_KERNEL_DS64 FLAT_RING3_DS64
#घोषणा FLAT_KERNEL_DS32 FLAT_RING3_DS32
#घोषणा FLAT_KERNEL_DS   FLAT_KERNEL_DS64
#घोषणा FLAT_KERNEL_CS64 FLAT_RING3_CS64
#घोषणा FLAT_KERNEL_CS32 FLAT_RING3_CS32
#घोषणा FLAT_KERNEL_CS   FLAT_KERNEL_CS64
#घोषणा FLAT_KERNEL_SS64 FLAT_RING3_SS64
#घोषणा FLAT_KERNEL_SS32 FLAT_RING3_SS32
#घोषणा FLAT_KERNEL_SS   FLAT_KERNEL_SS64

#घोषणा FLAT_USER_DS64 FLAT_RING3_DS64
#घोषणा FLAT_USER_DS32 FLAT_RING3_DS32
#घोषणा FLAT_USER_DS   FLAT_USER_DS64
#घोषणा FLAT_USER_CS64 FLAT_RING3_CS64
#घोषणा FLAT_USER_CS32 FLAT_RING3_CS32
#घोषणा FLAT_USER_CS   FLAT_USER_CS64
#घोषणा FLAT_USER_SS64 FLAT_RING3_SS64
#घोषणा FLAT_USER_SS32 FLAT_RING3_SS32
#घोषणा FLAT_USER_SS   FLAT_USER_SS64

#घोषणा __HYPERVISOR_VIRT_START 0xFFFF800000000000
#घोषणा __HYPERVISOR_VIRT_END   0xFFFF880000000000
#घोषणा __MACH2PHYS_VIRT_START  0xFFFF800000000000
#घोषणा __MACH2PHYS_VIRT_END    0xFFFF804000000000
#घोषणा __MACH2PHYS_SHIFT       3

/*
 * पूर्णांक HYPERVISOR_set_segment_base(अचिन्हित पूर्णांक which, अचिन्हित दीर्घ base)
 *  @which == SEGBASE_*  ;  @base == 64-bit base address
 * Returns 0 on success.
 */
#घोषणा SEGBASE_FS          0
#घोषणा SEGBASE_GS_USER     1
#घोषणा SEGBASE_GS_KERNEL   2
#घोषणा SEGBASE_GS_USER_SEL 3 /* Set user %gs specअगरied in base[15:0] */

/*
 * पूर्णांक HYPERVISOR_iret(व्योम)
 * All arguments are on the kernel stack, in the following क्रमmat.
 * Never वापसs अगर successful. Current kernel context is lost.
 * The saved CS is mapped as follows:
 *   RING0 -> RING3 kernel mode.
 *   RING1 -> RING3 kernel mode.
 *   RING2 -> RING3 kernel mode.
 *   RING3 -> RING3 user mode.
 * However RING0 indicates that the guest kernel should वापस to iteself
 * directly with
 *      orb   $3,1*8(%rsp)
 *      iretq
 * If flags contains VGCF_in_syscall:
 *   Restore RAX, RIP, RFLAGS, RSP.
 *   Discard R11, RCX, CS, SS.
 * Otherwise:
 *   Restore RAX, R11, RCX, CS:RIP, RFLAGS, SS:RSP.
 * All other रेजिस्टरs are saved on hypercall entry and restored to user.
 */
/* Guest निकासed in SYSCALL context? Return to guest with SYSRET? */
#घोषणा _VGCF_in_syscall 8
#घोषणा VGCF_in_syscall  (1<<_VGCF_in_syscall)
#घोषणा VGCF_IN_SYSCALL  VGCF_in_syscall

#अगर_अघोषित __ASSEMBLY__

काष्ठा iret_context अणु
    /* Top of stack (%rsp at poपूर्णांक of hypercall). */
    uपूर्णांक64_t rax, r11, rcx, flags, rip, cs, rflags, rsp, ss;
    /* Bottom of iret stack frame. */
पूर्ण;

#अगर defined(__GNUC__) && !defined(__STRICT_ANSI__)
/* Anonymous जोड़ includes both 32- and 64-bit names (e.g., eax/rax). */
#घोषणा __DECL_REG(name) जोड़ अणु \
    uपूर्णांक64_t r ## name, e ## name; \
    uपूर्णांक32_t _e ## name; \
पूर्ण
#अन्यथा
/* Non-gcc sources must always use the proper 64-bit name (e.g., rax). */
#घोषणा __DECL_REG(name) uपूर्णांक64_t r ## name
#पूर्ण_अगर

काष्ठा cpu_user_regs अणु
    uपूर्णांक64_t r15;
    uपूर्णांक64_t r14;
    uपूर्णांक64_t r13;
    uपूर्णांक64_t r12;
    __DECL_REG(bp);
    __DECL_REG(bx);
    uपूर्णांक64_t r11;
    uपूर्णांक64_t r10;
    uपूर्णांक64_t r9;
    uपूर्णांक64_t r8;
    __DECL_REG(ax);
    __DECL_REG(cx);
    __DECL_REG(dx);
    __DECL_REG(si);
    __DECL_REG(di);
    uपूर्णांक32_t error_code;    /* निजी */
    uपूर्णांक32_t entry_vector;  /* निजी */
    __DECL_REG(ip);
    uपूर्णांक16_t cs, _pad0[1];
    uपूर्णांक8_t  saved_upcall_mask;
    uपूर्णांक8_t  _pad1[3];
    __DECL_REG(flags);      /* rflags.IF == !saved_upcall_mask */
    __DECL_REG(sp);
    uपूर्णांक16_t ss, _pad2[3];
    uपूर्णांक16_t es, _pad3[3];
    uपूर्णांक16_t ds, _pad4[3];
    uपूर्णांक16_t fs, _pad5[3]; /* Non-zero => takes precedence over fs_base.     */
    uपूर्णांक16_t gs, _pad6[3]; /* Non-zero => takes precedence over gs_base_usr. */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(cpu_user_regs);

#अघोषित __DECL_REG

#घोषणा xen_pfn_to_cr3(pfn) ((अचिन्हित दीर्घ)(pfn) << 12)
#घोषणा xen_cr3_to_pfn(cr3) ((अचिन्हित दीर्घ)(cr3) >> 12)

काष्ठा arch_vcpu_info अणु
    अचिन्हित दीर्घ cr2;
    अचिन्हित दीर्घ pad; /* माप(vcpu_info_t) == 64 */
पूर्ण;

प्रकार अचिन्हित दीर्घ xen_callback_t;

#घोषणा XEN_CALLBACK(__cs, __rip)				\
	((अचिन्हित दीर्घ)(__rip))

#पूर्ण_अगर /* !__ASSEMBLY__ */


#पूर्ण_अगर /* _ASM_X86_XEN_INTERFACE_64_H */
