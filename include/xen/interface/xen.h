<शैली गुरु>
/******************************************************************************
 * xen.h
 *
 * Guest OS पूर्णांकerface to Xen.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (c) 2004, K A Fraser
 */

#अगर_अघोषित __XEN_PUBLIC_XEN_H__
#घोषणा __XEN_PUBLIC_XEN_H__

#समावेश <यंत्र/xen/पूर्णांकerface.h>

/*
 * XEN "SYSTEM CALLS" (a.k.a. HYPERCALLS).
 */

/*
 * x86_32: EAX = vector; EBX, ECX, EDX, ESI, EDI = args 1, 2, 3, 4, 5.
 *         EAX = वापस value
 *         (argument रेजिस्टरs may be clobbered on वापस)
 * x86_64: RAX = vector; RDI, RSI, RDX, R10, R8, R9 = args 1, 2, 3, 4, 5, 6.
 *         RAX = वापस value
 *         (argument रेजिस्टरs not clobbered on वापस; RCX, R11 are)
 */
#घोषणा __HYPERVISOR_set_trap_table        0
#घोषणा __HYPERVISOR_mmu_update            1
#घोषणा __HYPERVISOR_set_gdt               2
#घोषणा __HYPERVISOR_stack_चयन          3
#घोषणा __HYPERVISOR_set_callbacks         4
#घोषणा __HYPERVISOR_fpu_taskचयन        5
#घोषणा __HYPERVISOR_sched_op_compat       6
#घोषणा __HYPERVISOR_platक्रमm_op           7
#घोषणा __HYPERVISOR_set_debugreg          8
#घोषणा __HYPERVISOR_get_debugreg          9
#घोषणा __HYPERVISOR_update_descriptor    10
#घोषणा __HYPERVISOR_memory_op            12
#घोषणा __HYPERVISOR_multicall            13
#घोषणा __HYPERVISOR_update_va_mapping    14
#घोषणा __HYPERVISOR_set_समयr_op         15
#घोषणा __HYPERVISOR_event_channel_op_compat 16
#घोषणा __HYPERVISOR_xen_version          17
#घोषणा __HYPERVISOR_console_io           18
#घोषणा __HYPERVISOR_physdev_op_compat    19
#घोषणा __HYPERVISOR_grant_table_op       20
#घोषणा __HYPERVISOR_vm_assist            21
#घोषणा __HYPERVISOR_update_va_mapping_otherकरोमुख्य 22
#घोषणा __HYPERVISOR_iret                 23 /* x86 only */
#घोषणा __HYPERVISOR_vcpu_op              24
#घोषणा __HYPERVISOR_set_segment_base     25 /* x86/64 only */
#घोषणा __HYPERVISOR_mmuext_op            26
#घोषणा __HYPERVISOR_xsm_op               27
#घोषणा __HYPERVISOR_nmi_op               28
#घोषणा __HYPERVISOR_sched_op             29
#घोषणा __HYPERVISOR_callback_op          30
#घोषणा __HYPERVISOR_xenoprof_op          31
#घोषणा __HYPERVISOR_event_channel_op     32
#घोषणा __HYPERVISOR_physdev_op           33
#घोषणा __HYPERVISOR_hvm_op               34
#घोषणा __HYPERVISOR_sysctl               35
#घोषणा __HYPERVISOR_करोmctl               36
#घोषणा __HYPERVISOR_kexec_op             37
#घोषणा __HYPERVISOR_पंचांगem_op              38
#घोषणा __HYPERVISOR_xc_reserved_op       39 /* reserved क्रम XenClient */
#घोषणा __HYPERVISOR_xenpmu_op            40
#घोषणा __HYPERVISOR_dm_op                41

/* Architecture-specअगरic hypercall definitions. */
#घोषणा __HYPERVISOR_arch_0               48
#घोषणा __HYPERVISOR_arch_1               49
#घोषणा __HYPERVISOR_arch_2               50
#घोषणा __HYPERVISOR_arch_3               51
#घोषणा __HYPERVISOR_arch_4               52
#घोषणा __HYPERVISOR_arch_5               53
#घोषणा __HYPERVISOR_arch_6               54
#घोषणा __HYPERVISOR_arch_7               55

/*
 * VIRTUAL INTERRUPTS
 *
 * Virtual पूर्णांकerrupts that a guest OS may receive from Xen.
 * In the side comments, 'V.' denotes a per-VCPU VIRQ while 'G.' denotes a
 * global VIRQ. The क्रमmer can be bound once per VCPU and cannot be re-bound.
 * The latter can be allocated only once per guest: they must initially be
 * allocated to VCPU0 but can subsequently be re-bound.
 */
#घोषणा VIRQ_TIMER      0  /* V. Timebase update, and/or requested समयout.  */
#घोषणा VIRQ_DEBUG      1  /* V. Request guest to dump debug info.           */
#घोषणा VIRQ_CONSOLE    2  /* G. (DOM0) Bytes received on emergency console. */
#घोषणा VIRQ_DOM_EXC    3  /* G. (DOM0) Exceptional event क्रम some करोमुख्य.   */
#घोषणा VIRQ_TBUF       4  /* G. (DOM0) Trace buffer has records available.  */
#घोषणा VIRQ_DEBUGGER   6  /* G. (DOM0) A करोमुख्य has छोड़ोd क्रम debugging.   */
#घोषणा VIRQ_XENOPROF   7  /* V. XenOprofile पूर्णांकerrupt: new sample available */
#घोषणा VIRQ_CON_RING   8  /* G. (DOM0) Bytes received on console            */
#घोषणा VIRQ_PCPU_STATE 9  /* G. (DOM0) PCPU state changed                   */
#घोषणा VIRQ_MEM_EVENT  10 /* G. (DOM0) A memory event has occured           */
#घोषणा VIRQ_XC_RESERVED 11 /* G. Reserved क्रम XenClient                     */
#घोषणा VIRQ_ENOMEM     12 /* G. (DOM0) Low on heap memory       */
#घोषणा VIRQ_XENPMU     13  /* PMC पूर्णांकerrupt                                 */

/* Architecture-specअगरic VIRQ definitions. */
#घोषणा VIRQ_ARCH_0    16
#घोषणा VIRQ_ARCH_1    17
#घोषणा VIRQ_ARCH_2    18
#घोषणा VIRQ_ARCH_3    19
#घोषणा VIRQ_ARCH_4    20
#घोषणा VIRQ_ARCH_5    21
#घोषणा VIRQ_ARCH_6    22
#घोषणा VIRQ_ARCH_7    23

#घोषणा NR_VIRQS       24

/*
 * क्रमागत neg_त्रुटि_संval HYPERVISOR_mmu_update(स्थिर काष्ठा mmu_update reqs[],
 *                                         अचिन्हित count, अचिन्हित *करोne_out,
 *                                         अचिन्हित क्रमeignकरोm)
 * @reqs is an array of mmu_update_t काष्ठाures ((ptr, val) pairs).
 * @count is the length of the above array.
 * @pकरोne is an output parameter indicating number of completed operations
 * @क्रमeignकरोm[15:0]: FD, the expected owner of data pages referenced in this
 *                    hypercall invocation. Can be DOMID_SELF.
 * @क्रमeignकरोm[31:16]: PFD, the expected owner of pagetable pages referenced
 *                     in this hypercall invocation. The value of this field
 *                     (x) encodes the PFD as follows:
 *                     x == 0 => PFD == DOMID_SELF
 *                     x != 0 => PFD == x - 1
 *
 * Sub-commands: ptr[1:0] specअगरies the appropriate MMU_* command.
 * -------------
 * ptr[1:0] == MMU_NORMAL_PT_UPDATE:
 * Updates an entry in a page table beदीर्घing to PFD. If updating an L1 table,
 * and the new table entry is valid/present, the mapped frame must beदीर्घ to
 * FD. If attempting to map an I/O page then the caller assumes the privilege
 * of the FD.
 * FD == DOMID_IO: Permit /only/ I/O mappings, at the priv level of the caller.
 * FD == DOMID_XEN: Map restricted areas of Xen's heap space.
 * ptr[:2]  -- Machine address of the page-table entry to modअगरy.
 * val      -- Value to ग_लिखो.
 *
 * There also certain implicit requirements when using this hypercall. The
 * pages that make up a pagetable must be mapped पढ़ो-only in the guest.
 * This prevents uncontrolled guest updates to the pagetable. Xen strictly
 * enक्रमces this, and will disallow any pagetable update which will end up
 * mapping pagetable page RW, and will disallow using any writable page as a
 * pagetable. In practice it means that when स्थिरructing a page table क्रम a
 * process, thपढ़ो, etc, we MUST be very dilligient in following these rules:
 *  1). Start with top-level page (PGD or in Xen language: L4). Fill out
 *      the entries.
 *  2). Keep on going, filling out the upper (PUD or L3), and middle (PMD
 *      or L2).
 *  3). Start filling out the PTE table (L1) with the PTE entries. Once
 *      करोne, make sure to set each of those entries to RO (so ग_लिखोable bit
 *      is unset). Once that has been completed, set the PMD (L2) क्रम this
 *      PTE table as RO.
 *  4). When completed with all of the PMD (L2) entries, and all of them have
 *      been set to RO, make sure to set RO the PUD (L3). Do the same
 *      operation on PGD (L4) pagetable entries that have a PUD (L3) entry.
 *  5). Now beक्रमe you can use those pages (so setting the cr3), you MUST also
 *      pin them so that the hypervisor can verअगरy the entries. This is करोne
 *      via the HYPERVISOR_mmuext_op(MMUEXT_PIN_L4_TABLE, guest physical frame
 *      number of the PGD (L4)). And this poपूर्णांक the HYPERVISOR_mmuext_op(
 *      MMUEXT_NEW_BASEPTR, guest physical frame number of the PGD (L4)) can be
 *      issued.
 * For 32-bit guests, the L4 is not used (as there is less pagetables), so
 * instead use L3.
 * At this poपूर्णांक the pagetables can be modअगरied using the MMU_NORMAL_PT_UPDATE
 * hypercall. Also अगर so desired the OS can also try to ग_लिखो to the PTE
 * and be trapped by the hypervisor (as the PTE entry is RO).
 *
 * To deallocate the pages, the operations are the reverse of the steps
 * mentioned above. The argument is MMUEXT_UNPIN_TABLE क्रम all levels and the
 * pagetable MUST not be in use (meaning that the cr3 is not set to it).
 *
 * ptr[1:0] == MMU_MACHPHYS_UPDATE:
 * Updates an entry in the machine->pseuकरो-physical mapping table.
 * ptr[:2]  -- Machine address within the frame whose mapping to modअगरy.
 *             The frame must beदीर्घ to the FD, अगर one is specअगरied.
 * val      -- Value to ग_लिखो पूर्णांकo the mapping entry.
 *
 * ptr[1:0] == MMU_PT_UPDATE_PRESERVE_AD:
 * As MMU_NORMAL_PT_UPDATE above, but A/D bits currently in the PTE are ORed
 * with those in @val.
 *
 * @val is usually the machine frame number aदीर्घ with some attributes.
 * The attributes by शेष follow the architecture defined bits. Meaning that
 * अगर this is a X86_64 machine and four page table layout is used, the layout
 * of val is:
 *  - 63 अगर set means No execute (NX)
 *  - 46-13 the machine frame number
 *  - 12 available क्रम guest
 *  - 11 available क्रम guest
 *  - 10 available क्रम guest
 *  - 9 available क्रम guest
 *  - 8 global
 *  - 7 PAT (PSE is disabled, must use hypercall to make 4MB or 2MB pages)
 *  - 6 dirty
 *  - 5 accessed
 *  - 4 page cached disabled
 *  - 3 page ग_लिखो through
 *  - 2 userspace accessible
 *  - 1 ग_लिखोable
 *  - 0 present
 *
 *  The one bits that करोes not fit with the शेष layout is the PAGE_PSE
 *  also called PAGE_PAT). The MMUEXT_[UN]MARK_SUPER arguments to the
 *  HYPERVISOR_mmuext_op serve as mechanism to set a pagetable to be 4MB
 *  (or 2MB) instead of using the PAGE_PSE bit.
 *
 *  The reason that the PAGE_PSE (bit 7) is not being utilized is due to Xen
 *  using it as the Page Attribute Table (PAT) bit - क्रम details on it please
 *  refer to Intel SDM 10.12. The PAT allows to set the caching attributes of
 *  pages instead of using MTRRs.
 *
 *  The PAT MSR is as follows (it is a 64-bit value, each entry is 8 bits):
 *                    PAT4                 PAT0
 *  +-----+-----+----+----+----+-----+----+----+
 *  | UC  | UC- | WC | WB | UC | UC- | WC | WB |  <= Linux
 *  +-----+-----+----+----+----+-----+----+----+
 *  | UC  | UC- | WT | WB | UC | UC- | WT | WB |  <= BIOS (शेष when machine boots)
 *  +-----+-----+----+----+----+-----+----+----+
 *  | rsv | rsv | WP | WC | UC | UC- | WT | WB |  <= Xen
 *  +-----+-----+----+----+----+-----+----+----+
 *
 *  The lookup of this index table translates to looking up
 *  Bit 7, Bit 4, and Bit 3 of val entry:
 *
 *  PAT/PSE (bit 7) ... PCD (bit 4) .. PWT (bit 3).
 *
 *  If all bits are off, then we are using PAT0. If bit 3 turned on,
 *  then we are using PAT1, अगर bit 3 and bit 4, then PAT2..
 *
 *  As you can see, the Linux PAT1 translates to PAT4 under Xen. Which means
 *  that अगर a guest that follows Linux's PAT setup and would like to set Write
 *  Combined on pages it MUST use PAT4 entry. Meaning that Bit 7 (PAGE_PAT) is
 *  set. For example, under Linux it only uses PAT0, PAT1, and PAT2 क्रम the
 *  caching as:
 *
 *   WB = none (so PAT0)
 *   WC = PWT (bit 3 on)
 *   UC = PWT | PCD (bit 3 and 4 are on).
 *
 * To make it work with Xen, it needs to translate the WC bit as so:
 *
 *  PWT (so bit 3 on) --> PAT (so bit 7 is on) and clear bit 3
 *
 * And to translate back it would:
 *
 * PAT (bit 7 on) --> PWT (bit 3 on) and clear bit 7.
 */
#घोषणा MMU_NORMAL_PT_UPDATE       0 /* checked '*ptr = val'. ptr is MA.      */
#घोषणा MMU_MACHPHYS_UPDATE        1 /* ptr = MA of frame to modअगरy entry क्रम */
#घोषणा MMU_PT_UPDATE_PRESERVE_AD  2 /* atomically: *ptr = val | (*ptr&(A|D)) */
#घोषणा MMU_PT_UPDATE_NO_TRANSLATE 3 /* checked '*ptr = val'. ptr is MA.      */

/*
 * MMU EXTENDED OPERATIONS
 *
 * क्रमागत neg_त्रुटि_संval HYPERVISOR_mmuext_op(mmuext_op_t uops[],
 *                                        अचिन्हित पूर्णांक count,
 *                                        अचिन्हित पूर्णांक *pकरोne,
 *                                        अचिन्हित पूर्णांक क्रमeignकरोm)
 */
/* HYPERVISOR_mmuext_op() accepts a list of mmuext_op काष्ठाures.
 * A क्रमeignकरोm (FD) can be specअगरied (or DOMID_SELF क्रम none).
 * Where the FD has some effect, it is described below.
 *
 * cmd: MMUEXT_(UN)PIN_*_TABLE
 * mfn: Machine frame number to be (un)pinned as a p.t. page.
 *      The frame must beदीर्घ to the FD, अगर one is specअगरied.
 *
 * cmd: MMUEXT_NEW_BASEPTR
 * mfn: Machine frame number of new page-table base to install in MMU.
 *
 * cmd: MMUEXT_NEW_USER_BASEPTR [x86/64 only]
 * mfn: Machine frame number of new page-table base to install in MMU
 *      when in user space.
 *
 * cmd: MMUEXT_TLB_FLUSH_LOCAL
 * No additional arguments. Flushes local TLB.
 *
 * cmd: MMUEXT_INVLPG_LOCAL
 * linear_addr: Linear address to be flushed from the local TLB.
 *
 * cmd: MMUEXT_TLB_FLUSH_MULTI
 * vcpumask: Poपूर्णांकer to biपंचांगap of VCPUs to be flushed.
 *
 * cmd: MMUEXT_INVLPG_MULTI
 * linear_addr: Linear address to be flushed.
 * vcpumask: Poपूर्णांकer to biपंचांगap of VCPUs to be flushed.
 *
 * cmd: MMUEXT_TLB_FLUSH_ALL
 * No additional arguments. Flushes all VCPUs' TLBs.
 *
 * cmd: MMUEXT_INVLPG_ALL
 * linear_addr: Linear address to be flushed from all VCPUs' TLBs.
 *
 * cmd: MMUEXT_FLUSH_CACHE
 * No additional arguments. Writes back and flushes cache contents.
 *
 * cmd: MMUEXT_FLUSH_CACHE_GLOBAL
 * No additional arguments. Writes back and flushes cache contents
 * on all CPUs in the प्रणाली.
 *
 * cmd: MMUEXT_SET_LDT
 * linear_addr: Linear address of LDT base (NB. must be page-aligned).
 * nr_ents: Number of entries in LDT.
 *
 * cmd: MMUEXT_CLEAR_PAGE
 * mfn: Machine frame number to be cleared.
 *
 * cmd: MMUEXT_COPY_PAGE
 * mfn: Machine frame number of the destination page.
 * src_mfn: Machine frame number of the source page.
 *
 * cmd: MMUEXT_[UN]MARK_SUPER
 * mfn: Machine frame number of head of superpage to be [un]marked.
 */
#घोषणा MMUEXT_PIN_L1_TABLE      0
#घोषणा MMUEXT_PIN_L2_TABLE      1
#घोषणा MMUEXT_PIN_L3_TABLE      2
#घोषणा MMUEXT_PIN_L4_TABLE      3
#घोषणा MMUEXT_UNPIN_TABLE       4
#घोषणा MMUEXT_NEW_BASEPTR       5
#घोषणा MMUEXT_TLB_FLUSH_LOCAL   6
#घोषणा MMUEXT_INVLPG_LOCAL      7
#घोषणा MMUEXT_TLB_FLUSH_MULTI   8
#घोषणा MMUEXT_INVLPG_MULTI      9
#घोषणा MMUEXT_TLB_FLUSH_ALL    10
#घोषणा MMUEXT_INVLPG_ALL       11
#घोषणा MMUEXT_FLUSH_CACHE      12
#घोषणा MMUEXT_SET_LDT          13
#घोषणा MMUEXT_NEW_USER_BASEPTR 15
#घोषणा MMUEXT_CLEAR_PAGE       16
#घोषणा MMUEXT_COPY_PAGE        17
#घोषणा MMUEXT_FLUSH_CACHE_GLOBAL 18
#घोषणा MMUEXT_MARK_SUPER       19
#घोषणा MMUEXT_UNMARK_SUPER     20

#अगर_अघोषित __ASSEMBLY__
काष्ठा mmuext_op अणु
	अचिन्हित पूर्णांक cmd;
	जोड़ अणु
		/* [UN]PIN_TABLE, NEW_BASEPTR, NEW_USER_BASEPTR
		 * CLEAR_PAGE, COPY_PAGE, [UN]MARK_SUPER */
		xen_pfn_t mfn;
		/* INVLPG_LOCAL, INVLPG_ALL, SET_LDT */
		अचिन्हित दीर्घ linear_addr;
	पूर्ण arg1;
	जोड़ अणु
		/* SET_LDT */
		अचिन्हित पूर्णांक nr_ents;
		/* TLB_FLUSH_MULTI, INVLPG_MULTI */
		व्योम *vcpumask;
		/* COPY_PAGE */
		xen_pfn_t src_mfn;
	पूर्ण arg2;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(mmuext_op);
#पूर्ण_अगर

/* These are passed as 'flags' to update_va_mapping. They can be ORed. */
/* When specअगरying UVMF_MULTI, also OR in a poपूर्णांकer to a CPU biपंचांगap.   */
/* UVMF_LOCAL is merely UVMF_MULTI with a शून्य biपंचांगap poपूर्णांकer.         */
#घोषणा UVMF_NONE               (0UL<<0) /* No flushing at all.   */
#घोषणा UVMF_TLB_FLUSH          (1UL<<0) /* Flush entire TLB(s).  */
#घोषणा UVMF_INVLPG             (2UL<<0) /* Flush only one entry. */
#घोषणा UVMF_FLUSHTYPE_MASK     (3UL<<0)
#घोषणा UVMF_MULTI              (0UL<<2) /* Flush subset of TLBs. */
#घोषणा UVMF_LOCAL              (0UL<<2) /* Flush local TLB.      */
#घोषणा UVMF_ALL                (1UL<<2) /* Flush all TLBs.       */

/*
 * Commands to HYPERVISOR_console_io().
 */
#घोषणा CONSOLEIO_ग_लिखो         0
#घोषणा CONSOLEIO_पढ़ो          1

/*
 * Commands to HYPERVISOR_vm_assist().
 */
#घोषणा VMASST_CMD_enable                0
#घोषणा VMASST_CMD_disable               1

/* x86/32 guests: simulate full 4GB segment limits. */
#घोषणा VMASST_TYPE_4gb_segments         0

/* x86/32 guests: trap (vector 15) whenever above vmassist is used. */
#घोषणा VMASST_TYPE_4gb_segments_notअगरy  1

/*
 * x86 guests: support ग_लिखोs to bottom-level PTEs.
 * NB1. Page-directory entries cannot be written.
 * NB2. Guest must जारी to हटाओ all writable mappings of PTEs.
 */
#घोषणा VMASST_TYPE_writable_pagetables  2

/* x86/PAE guests: support PDPTs above 4GB. */
#घोषणा VMASST_TYPE_pae_extended_cr3     3

/*
 * x86 guests: Sane behaviour क्रम भव iopl
 *  - भव iopl updated from करो_iret() hypercalls.
 *  - भव iopl reported in bounce frames.
 *  - guest kernels assumed to be level 0 क्रम the purpose of iopl checks.
 */
#घोषणा VMASST_TYPE_architectural_iopl   4

/*
 * All guests: activate update indicator in vcpu_runstate_info
 * Enable setting the XEN_RUNSTATE_UPDATE flag in guest memory mapped
 * vcpu_runstate_info during updates of the runstate inक्रमmation.
 */
#घोषणा VMASST_TYPE_runstate_update_flag 5

#घोषणा MAX_VMASST_TYPE 5

#अगर_अघोषित __ASSEMBLY__

प्रकार uपूर्णांक16_t करोmid_t;

/* Doमुख्य ids >= DOMID_FIRST_RESERVED cannot be used क्रम ordinary करोमुख्यs. */
#घोषणा DOMID_FIRST_RESERVED (0x7FF0U)

/* DOMID_SELF is used in certain contexts to refer to oneself. */
#घोषणा DOMID_SELF (0x7FF0U)

/*
 * DOMID_IO is used to restrict page-table updates to mapping I/O memory.
 * Although no Foreign Doमुख्य need be specअगरied to map I/O pages, DOMID_IO
 * is useful to ensure that no mappings to the OS's own heap are accidentally
 * installed. (e.g., in Linux this could cause havoc as reference counts
 * aren't adjusted on the I/O-mapping code path).
 * This only makes sense in MMUEXT_SET_FOREIGNDOM, but in that context can
 * be specअगरied by any calling करोमुख्य.
 */
#घोषणा DOMID_IO   (0x7FF1U)

/*
 * DOMID_XEN is used to allow privileged करोमुख्यs to map restricted parts of
 * Xen's heap space (e.g., the machine_to_phys table).
 * This only makes sense in MMUEXT_SET_FOREIGNDOM, and is only permitted अगर
 * the caller is privileged.
 */
#घोषणा DOMID_XEN  (0x7FF2U)

/* DOMID_COW is used as the owner of sharable pages */
#घोषणा DOMID_COW  (0x7FF3U)

/* DOMID_INVALID is used to identअगरy pages with unknown owner. */
#घोषणा DOMID_INVALID (0x7FF4U)

/* Idle करोमुख्य. */
#घोषणा DOMID_IDLE (0x7FFFU)

/*
 * Send an array of these to HYPERVISOR_mmu_update().
 * NB. The fields are natural poपूर्णांकer/address size क्रम this architecture.
 */
काष्ठा mmu_update अणु
    uपूर्णांक64_t ptr;       /* Machine address of PTE. */
    uपूर्णांक64_t val;       /* New contents of PTE.    */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(mmu_update);

/*
 * Send an array of these to HYPERVISOR_multicall().
 * NB. The fields are logically the natural रेजिस्टर size क्रम this
 * architecture. In हालs where xen_uदीर्घ_t is larger than this then
 * any unused bits in the upper portion must be zero.
 */
काष्ठा multicall_entry अणु
    xen_uदीर्घ_t op;
    xen_दीर्घ_t result;
    xen_uदीर्घ_t args[6];
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(multicall_entry);

काष्ठा vcpu_समय_info अणु
	/*
	 * Updates to the following values are preceded and followed
	 * by an increment of 'version'. The guest can thereक्रमe
	 * detect updates by looking क्रम changes to 'version'. If the
	 * least-signअगरicant bit of the version number is set then an
	 * update is in progress and the guest must रुको to पढ़ो a
	 * consistent set of values.  The correct way to पूर्णांकeract with
	 * the version number is similar to Linux's seqlock: see the
	 * implementations of पढ़ो_seqbegin/पढ़ो_seqretry.
	 */
	uपूर्णांक32_t version;
	uपूर्णांक32_t pad0;
	uपूर्णांक64_t tsc_बारtamp;   /* TSC at last update of समय vals.  */
	uपूर्णांक64_t प्रणाली_समय;     /* Time, in nanosecs, since boot.    */
	/*
	 * Current प्रणाली समय:
	 *   प्रणाली_समय + ((tsc - tsc_बारtamp) << tsc_shअगरt) * tsc_to_प्रणाली_mul
	 * CPU frequency (Hz):
	 *   ((10^9 << 32) / tsc_to_प्रणाली_mul) >> tsc_shअगरt
	 */
	uपूर्णांक32_t tsc_to_प्रणाली_mul;
	पूर्णांक8_t   tsc_shअगरt;
	पूर्णांक8_t   pad1[3];
पूर्ण; /* 32 bytes */

काष्ठा vcpu_info अणु
	/*
	 * 'evtchn_upcall_pending' is written non-zero by Xen to indicate
	 * a pending notअगरication क्रम a particular VCPU. It is then cleared
	 * by the guest OS /beक्रमe/ checking क्रम pending work, thus aव्योमing
	 * a set-and-check race. Note that the mask is only accessed by Xen
	 * on the CPU that is currently hosting the VCPU. This means that the
	 * pending and mask flags can be updated by the guest without special
	 * synchronisation (i.e., no need क्रम the x86 LOCK prefix).
	 * This may seem suboptimal because अगर the pending flag is set by
	 * a dअगरferent CPU then an IPI may be scheduled even when the mask
	 * is set. However, note:
	 *  1. The task of 'interrupt holdoff' is covered by the per-event-
	 *     channel mask bits. A 'noisy' event that is continually being
	 *     triggered can be masked at source at this very precise
	 *     granularity.
	 *  2. The मुख्य purpose of the per-VCPU mask is thereक्रमe to restrict
	 *     reentrant execution: whether क्रम concurrency control, or to
	 *     prevent unbounded stack usage. Whatever the purpose, we expect
	 *     that the mask will be निश्चितed only क्रम लघु periods at a समय,
	 *     and so the likelihood of a 'spurious' IPI is suitably small.
	 * The mask is पढ़ो beक्रमe making an event upcall to the guest: a
	 * non-zero mask thereक्रमe guarantees that the VCPU will not receive
	 * an upcall activation. The mask is cleared when the VCPU requests
	 * to block: this aव्योमs wakeup-रुकोing races.
	 */
	uपूर्णांक8_t evtchn_upcall_pending;
	uपूर्णांक8_t evtchn_upcall_mask;
	xen_uदीर्घ_t evtchn_pending_sel;
	काष्ठा arch_vcpu_info arch;
	काष्ठा pvघड़ी_vcpu_समय_info समय;
पूर्ण; /* 64 bytes (x86) */

/*
 * Xen/kernel shared data -- poपूर्णांकer provided in start_info.
 * NB. We expect that this काष्ठा is smaller than a page.
 */
काष्ठा shared_info अणु
	काष्ठा vcpu_info vcpu_info[MAX_VIRT_CPUS];

	/*
	 * A करोमुख्य can create "event channels" on which it can send and receive
	 * asynchronous event notअगरications. There are three classes of event that
	 * are delivered by this mechanism:
	 *  1. Bi-directional पूर्णांकer- and पूर्णांकra-करोमुख्य connections. Doमुख्यs must
	 *     arrange out-of-band to set up a connection (usually by allocating
	 *     an unbound 'listener' port and avertising that via a storage service
	 *     such as xenstore).
	 *  2. Physical पूर्णांकerrupts. A करोमुख्य with suitable hardware-access
	 *     privileges can bind an event-channel port to a physical पूर्णांकerrupt
	 *     source.
	 *  3. Virtual पूर्णांकerrupts ('events'). A करोमुख्य can bind an event-channel
	 *     port to a भव पूर्णांकerrupt source, such as the भव-समयr
	 *     device or the emergency console.
	 *
	 * Event channels are addressed by a "port index". Each channel is
	 * associated with two bits of inक्रमmation:
	 *  1. PENDING -- notअगरies the करोमुख्य that there is a pending notअगरication
	 *     to be processed. This bit is cleared by the guest.
	 *  2. MASK -- अगर this bit is clear then a 0->1 transition of PENDING
	 *     will cause an asynchronous upcall to be scheduled. This bit is only
	 *     updated by the guest. It is पढ़ो-only within Xen. If a channel
	 *     becomes pending जबतक the channel is masked then the 'edge' is lost
	 *     (i.e., when the channel is unmasked, the guest must manually handle
	 *     pending notअगरications as no upcall will be scheduled by Xen).
	 *
	 * To expedite scanning of pending notअगरications, any 0->1 pending
	 * transition on an unmasked channel causes a corresponding bit in a
	 * per-vcpu selector word to be set. Each bit in the selector covers a
	 * 'C long' in the PENDING bitfield array.
	 */
	xen_uदीर्घ_t evtchn_pending[माप(xen_uदीर्घ_t) * 8];
	xen_uदीर्घ_t evtchn_mask[माप(xen_uदीर्घ_t) * 8];

	/*
	 * Wallघड़ी समय: updated only by control software. Guests should base
	 * their समय_लोofday() syscall on this wallघड़ी-base value.
	 */
	काष्ठा pvघड़ी_wall_घड़ी wc;
#अगर_अघोषित CONFIG_X86_32
	uपूर्णांक32_t wc_sec_hi;
#पूर्ण_अगर
	काष्ठा arch_shared_info arch;

पूर्ण;

/*
 * Start-of-day memory layout
 *
 *  1. The करोमुख्य is started within contiguous भव-memory region.
 *  2. The contiguous region begins and ends on an aligned 4MB boundary.
 *  3. This the order of bootstrap elements in the initial भव region:
 *      a. relocated kernel image
 *      b. initial ram disk              [mod_start, mod_len]
 *         (may be omitted)
 *      c. list of allocated page frames [mfn_list, nr_pages]
 *         (unless relocated due to XEN_ELFNOTE_INIT_P2M)
 *      d. start_info_t काष्ठाure        [रेजिस्टर ESI (x86)]
 *         in हाल of करोm0 this page contains the console info, too
 *      e. unless करोm0: xenstore ring page
 *      f. unless करोm0: console ring page
 *      g. bootstrap page tables         [pt_base, CR3 (x86)]
 *      h. bootstrap stack               [रेजिस्टर ESP (x86)]
 *  4. Bootstrap elements are packed together, but each is 4kB-aligned.
 *  5. The list of page frames क्रमms a contiguous 'pseudo-physical' memory
 *     layout क्रम the करोमुख्य. In particular, the bootstrap भव-memory
 *     region is a 1:1 mapping to the first section of the pseuकरो-physical map.
 *  6. All bootstrap elements are mapped पढ़ो-writable क्रम the guest OS. The
 *     only exception is the bootstrap page table, which is mapped पढ़ो-only.
 *  7. There is guaranteed to be at least 512kB padding after the final
 *     bootstrap element. If necessary, the bootstrap भव region is
 *     extended by an extra 4MB to ensure this.
 */

#घोषणा MAX_GUEST_CMDLINE 1024
काष्ठा start_info अणु
	/* THE FOLLOWING ARE FILLED IN BOTH ON INITIAL BOOT AND ON RESUME.    */
	अक्षर magic[32];             /* "xen-<version>-<platform>".            */
	अचिन्हित दीर्घ nr_pages;     /* Total pages allocated to this करोमुख्य.  */
	अचिन्हित दीर्घ shared_info;  /* MACHINE address of shared info काष्ठा. */
	uपूर्णांक32_t flags;             /* SIF_xxx flags.                         */
	xen_pfn_t store_mfn;        /* MACHINE page number of shared page.    */
	uपूर्णांक32_t store_evtchn;      /* Event channel क्रम store communication. */
	जोड़ अणु
		काष्ठा अणु
			xen_pfn_t mfn;      /* MACHINE page number of console page.   */
			uपूर्णांक32_t  evtchn;   /* Event channel क्रम console page.        */
		पूर्ण करोmU;
		काष्ठा अणु
			uपूर्णांक32_t info_off;  /* Offset of console_info काष्ठा.         */
			uपूर्णांक32_t info_size; /* Size of console_info काष्ठा from start.*/
		पूर्ण करोm0;
	पूर्ण console;
	/* THE FOLLOWING ARE ONLY FILLED IN ON INITIAL BOOT (NOT RESUME).     */
	अचिन्हित दीर्घ pt_base;      /* VIRTUAL address of page directory.     */
	अचिन्हित दीर्घ nr_pt_frames; /* Number of bootstrap p.t. frames.       */
	अचिन्हित दीर्घ mfn_list;     /* VIRTUAL address of page-frame list.    */
	अचिन्हित दीर्घ mod_start;    /* VIRTUAL address of pre-loaded module.  */
	अचिन्हित दीर्घ mod_len;      /* Size (bytes) of pre-loaded module.     */
	पूर्णांक8_t cmd_line[MAX_GUEST_CMDLINE];
	/* The pfn range here covers both page table and p->m table frames.   */
	अचिन्हित दीर्घ first_p2m_pfn;/* 1st pfn क्रमming initial P->M table.    */
	अचिन्हित दीर्घ nr_p2m_frames;/* # of pfns क्रमming initial P->M table.  */
पूर्ण;

/* These flags are passed in the 'flags' field of start_info_t. */
#घोषणा SIF_PRIVILEGED      (1<<0)  /* Is the करोमुख्य privileged? */
#घोषणा SIF_INITDOMAIN      (1<<1)  /* Is this the initial control करोमुख्य? */
#घोषणा SIF_MULTIBOOT_MOD   (1<<2)  /* Is mod_start a multiboot module? */
#घोषणा SIF_MOD_START_PFN   (1<<3)  /* Is mod_start a PFN? */
#घोषणा SIF_VIRT_P2M_4TOOLS (1<<4)  /* Do Xen tools understand a virt. mapped */
				    /* P->M making the 3 level tree obsolete? */
#घोषणा SIF_PM_MASK       (0xFF<<8) /* reserve 1 byte क्रम xen-pm options */

/*
 * A multiboot module is a package containing modules very similar to a
 * multiboot module array. The only dअगरferences are:
 * - the array of module descriptors is by convention simply at the beginning
 *   of the multiboot module,
 * - addresses in the module descriptors are based on the beginning of the
 *   multiboot module,
 * - the number of modules is determined by a termination descriptor that has
 *   mod_start == 0.
 *
 * This permits to both build it अटलally and reference it in a configuration
 * file, and let the PV guest easily rebase the addresses to भव addresses
 * and at the same समय count the number of modules.
 */
काष्ठा xen_multiboot_mod_list अणु
	/* Address of first byte of the module */
	uपूर्णांक32_t mod_start;
	/* Address of last byte of the module (inclusive) */
	uपूर्णांक32_t mod_end;
	/* Address of zero-terminated command line */
	uपूर्णांक32_t cmdline;
	/* Unused, must be zero */
	uपूर्णांक32_t pad;
पूर्ण;
/*
 * The console काष्ठाure in start_info.console.करोm0
 *
 * This काष्ठाure includes a variety of inक्रमmation required to
 * have a working VGA/VESA console.
 */
काष्ठा करोm0_vga_console_info अणु
	uपूर्णांक8_t video_type;
#घोषणा XEN_VGATYPE_TEXT_MODE_3 0x03
#घोषणा XEN_VGATYPE_VESA_LFB    0x23
#घोषणा XEN_VGATYPE_EFI_LFB     0x70

	जोड़ अणु
		काष्ठा अणु
			/* Font height, in pixels. */
			uपूर्णांक16_t font_height;
			/* Cursor location (column, row). */
			uपूर्णांक16_t cursor_x, cursor_y;
			/* Number of rows and columns (dimensions in अक्षरacters). */
			uपूर्णांक16_t rows, columns;
		पूर्ण text_mode_3;

		काष्ठा अणु
			/* Width and height, in pixels. */
			uपूर्णांक16_t width, height;
			/* Bytes per scan line. */
			uपूर्णांक16_t bytes_per_line;
			/* Bits per pixel. */
			uपूर्णांक16_t bits_per_pixel;
			/* LFB physical address, and size (in units of 64kB). */
			uपूर्णांक32_t lfb_base;
			uपूर्णांक32_t lfb_size;
			/* RGB mask offsets and sizes, as defined by VBE 1.2+ */
			uपूर्णांक8_t  red_pos, red_size;
			uपूर्णांक8_t  green_pos, green_size;
			uपूर्णांक8_t  blue_pos, blue_size;
			uपूर्णांक8_t  rsvd_pos, rsvd_size;

			/* VESA capabilities (offset 0xa, VESA command 0x4f00). */
			uपूर्णांक32_t gbl_caps;
			/* Mode attributes (offset 0x0, VESA command 0x4f01). */
			uपूर्णांक16_t mode_attrs;
		पूर्ण vesa_lfb;
	पूर्ण u;
पूर्ण;

प्रकार uपूर्णांक64_t cpumap_t;

प्रकार uपूर्णांक8_t xen_करोमुख्य_handle_t[16];

/* Turn a plain number पूर्णांकo a C अचिन्हित दीर्घ स्थिरant. */
#घोषणा __mk_अचिन्हित_दीर्घ(x) x ## UL
#घोषणा mk_अचिन्हित_दीर्घ(x) __mk_अचिन्हित_दीर्घ(x)

#घोषणा TMEM_SPEC_VERSION 1

काष्ठा पंचांगem_op अणु
	uपूर्णांक32_t cmd;
	पूर्णांक32_t pool_id;
	जोड़ अणु
		काष्ठा अणु  /* क्रम cmd == TMEM_NEW_POOL */
			uपूर्णांक64_t uuid[2];
			uपूर्णांक32_t flags;
		पूर्ण new;
		काष्ठा अणु
			uपूर्णांक64_t oid[3];
			uपूर्णांक32_t index;
			uपूर्णांक32_t पंचांगem_offset;
			uपूर्णांक32_t pfn_offset;
			uपूर्णांक32_t len;
			GUEST_HANDLE(व्योम) gmfn; /* guest machine page frame */
		पूर्ण gen;
	पूर्ण u;
पूर्ण;

DEFINE_GUEST_HANDLE(u64);

#अन्यथा /* __ASSEMBLY__ */

/* In assembly code we cannot use C numeric स्थिरant suffixes. */
#घोषणा mk_अचिन्हित_दीर्घ(x) x

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __XEN_PUBLIC_XEN_H__ */
