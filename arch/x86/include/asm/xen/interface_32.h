<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * arch-x86_32.h
 *
 * Guest OS पूर्णांकerface to x86 32-bit Xen.
 *
 * Copyright (c) 2004, K A Fraser
 */

#अगर_अघोषित _ASM_X86_XEN_INTERFACE_32_H
#घोषणा _ASM_X86_XEN_INTERFACE_32_H


/*
 * These flat segments are in the Xen-निजी section of every GDT. Since these
 * are also present in the initial GDT, many OSes will be able to aव्योम
 * installing their own GDT.
 */
#घोषणा FLAT_RING1_CS 0xe019    /* GDT index 259 */
#घोषणा FLAT_RING1_DS 0xe021    /* GDT index 260 */
#घोषणा FLAT_RING1_SS 0xe021    /* GDT index 260 */
#घोषणा FLAT_RING3_CS 0xe02b    /* GDT index 261 */
#घोषणा FLAT_RING3_DS 0xe033    /* GDT index 262 */
#घोषणा FLAT_RING3_SS 0xe033    /* GDT index 262 */

#घोषणा FLAT_KERNEL_CS FLAT_RING1_CS
#घोषणा FLAT_KERNEL_DS FLAT_RING1_DS
#घोषणा FLAT_KERNEL_SS FLAT_RING1_SS
#घोषणा FLAT_USER_CS    FLAT_RING3_CS
#घोषणा FLAT_USER_DS    FLAT_RING3_DS
#घोषणा FLAT_USER_SS    FLAT_RING3_SS

/* And the trap vector is... */
#घोषणा TRAP_INSTR "int $0x82"

#घोषणा __MACH2PHYS_VIRT_START 0xF5800000
#घोषणा __MACH2PHYS_VIRT_END   0xF6800000

#घोषणा __MACH2PHYS_SHIFT      2

/*
 * Virtual addresses beyond this are not modअगरiable by guest OSes. The
 * machine->physical mapping table starts at this address, पढ़ो-only.
 */
#घोषणा __HYPERVISOR_VIRT_START 0xF5800000

#अगर_अघोषित __ASSEMBLY__

काष्ठा cpu_user_regs अणु
    uपूर्णांक32_t ebx;
    uपूर्णांक32_t ecx;
    uपूर्णांक32_t edx;
    uपूर्णांक32_t esi;
    uपूर्णांक32_t edi;
    uपूर्णांक32_t ebp;
    uपूर्णांक32_t eax;
    uपूर्णांक16_t error_code;    /* निजी */
    uपूर्णांक16_t entry_vector;  /* निजी */
    uपूर्णांक32_t eip;
    uपूर्णांक16_t cs;
    uपूर्णांक8_t  saved_upcall_mask;
    uपूर्णांक8_t  _pad0;
    uपूर्णांक32_t eflags;        /* eflags.IF == !saved_upcall_mask */
    uपूर्णांक32_t esp;
    uपूर्णांक16_t ss, _pad1;
    uपूर्णांक16_t es, _pad2;
    uपूर्णांक16_t ds, _pad3;
    uपूर्णांक16_t fs, _pad4;
    uपूर्णांक16_t gs, _pad5;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(cpu_user_regs);

प्रकार uपूर्णांक64_t tsc_बारtamp_t; /* RDTSC बारtamp */

काष्ठा arch_vcpu_info अणु
    अचिन्हित दीर्घ cr2;
    अचिन्हित दीर्घ pad[5]; /* माप(काष्ठा vcpu_info) == 64 */
पूर्ण;

काष्ठा xen_callback अणु
	अचिन्हित दीर्घ cs;
	अचिन्हित दीर्घ eip;
पूर्ण;
प्रकार काष्ठा xen_callback xen_callback_t;

#घोषणा XEN_CALLBACK(__cs, __eip)				\
	((काष्ठा xen_callback)अणु .cs = (__cs), .eip = (अचिन्हित दीर्घ)(__eip) पूर्ण)
#पूर्ण_अगर /* !__ASSEMBLY__ */


/*
 * Page-directory addresses above 4GB करो not fit पूर्णांकo architectural %cr3.
 * When accessing %cr3, or equivalent field in vcpu_guest_context, guests
 * must use the following accessor macros to pack/unpack valid MFNs.
 *
 * Note that Xen is using the fact that the pagetable base is always
 * page-aligned, and putting the 12 MSB of the address पूर्णांकo the 12 LSB
 * of cr3.
 */
#घोषणा xen_pfn_to_cr3(pfn) (((अचिन्हित)(pfn) << 12) | ((अचिन्हित)(pfn) >> 20))
#घोषणा xen_cr3_to_pfn(cr3) (((अचिन्हित)(cr3) >> 12) | ((अचिन्हित)(cr3) << 20))

#पूर्ण_अगर /* _ASM_X86_XEN_INTERFACE_32_H */
