<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_X86_KVM_PARA_H
#घोषणा _UAPI_ASM_X86_KVM_PARA_H

#समावेश <linux/types.h>

/* This CPUID वापसs the signature 'KVMKVMKVM' in ebx, ecx, and edx.  It
 * should be used to determine that a VM is running under KVM.
 */
#घोषणा KVM_CPUID_SIGNATURE	0x40000000

/* This CPUID वापसs two feature biपंचांगaps in eax, edx. Beक्रमe enabling
 * a particular paraभवization, the appropriate feature bit should
 * be checked in eax. The perक्रमmance hपूर्णांक feature bit should be checked
 * in edx.
 */
#घोषणा KVM_CPUID_FEATURES	0x40000001
#घोषणा KVM_FEATURE_CLOCKSOURCE		0
#घोषणा KVM_FEATURE_NOP_IO_DELAY	1
#घोषणा KVM_FEATURE_MMU_OP		2
/* This indicates that the new set of kvmघड़ी msrs
 * are available. The use of 0x11 and 0x12 is deprecated
 */
#घोषणा KVM_FEATURE_CLOCKSOURCE2        3
#घोषणा KVM_FEATURE_ASYNC_PF		4
#घोषणा KVM_FEATURE_STEAL_TIME		5
#घोषणा KVM_FEATURE_PV_EOI		6
#घोषणा KVM_FEATURE_PV_UNHALT		7
#घोषणा KVM_FEATURE_PV_TLB_FLUSH	9
#घोषणा KVM_FEATURE_ASYNC_PF_VMEXIT	10
#घोषणा KVM_FEATURE_PV_SEND_IPI	11
#घोषणा KVM_FEATURE_POLL_CONTROL	12
#घोषणा KVM_FEATURE_PV_SCHED_YIELD	13
#घोषणा KVM_FEATURE_ASYNC_PF_INT	14
#घोषणा KVM_FEATURE_MSI_EXT_DEST_ID	15

#घोषणा KVM_HINTS_REALTIME      0

/* The last 8 bits are used to indicate how to पूर्णांकerpret the flags field
 * in pvघड़ी काष्ठाure. If no bits are set, all flags are ignored.
 */
#घोषणा KVM_FEATURE_CLOCKSOURCE_STABLE_BIT	24

#घोषणा MSR_KVM_WALL_CLOCK  0x11
#घोषणा MSR_KVM_SYSTEM_TIME 0x12

#घोषणा KVM_MSR_ENABLED 1
/* Custom MSRs falls in the range 0x4b564d00-0x4b564dff */
#घोषणा MSR_KVM_WALL_CLOCK_NEW  0x4b564d00
#घोषणा MSR_KVM_SYSTEM_TIME_NEW 0x4b564d01
#घोषणा MSR_KVM_ASYNC_PF_EN 0x4b564d02
#घोषणा MSR_KVM_STEAL_TIME  0x4b564d03
#घोषणा MSR_KVM_PV_EOI_EN      0x4b564d04
#घोषणा MSR_KVM_POLL_CONTROL	0x4b564d05
#घोषणा MSR_KVM_ASYNC_PF_INT	0x4b564d06
#घोषणा MSR_KVM_ASYNC_PF_ACK	0x4b564d07

काष्ठा kvm_steal_समय अणु
	__u64 steal;
	__u32 version;
	__u32 flags;
	__u8  preempted;
	__u8  u8_pad[3];
	__u32 pad[11];
पूर्ण;

#घोषणा KVM_VCPU_PREEMPTED          (1 << 0)
#घोषणा KVM_VCPU_FLUSH_TLB          (1 << 1)

#घोषणा KVM_CLOCK_PAIRING_WALLCLOCK 0
काष्ठा kvm_घड़ी_pairing अणु
	__s64 sec;
	__s64 nsec;
	__u64 tsc;
	__u32 flags;
	__u32 pad[9];
पूर्ण;

#घोषणा KVM_STEAL_ALIGNMENT_BITS 5
#घोषणा KVM_STEAL_VALID_BITS ((-1ULL << (KVM_STEAL_ALIGNMENT_BITS + 1)))
#घोषणा KVM_STEAL_RESERVED_MASK (((1 << KVM_STEAL_ALIGNMENT_BITS) - 1 ) << 1)

#घोषणा KVM_MAX_MMU_OP_BATCH           32

#घोषणा KVM_ASYNC_PF_ENABLED			(1 << 0)
#घोषणा KVM_ASYNC_PF_SEND_ALWAYS		(1 << 1)
#घोषणा KVM_ASYNC_PF_DELIVERY_AS_PF_VMEXIT	(1 << 2)
#घोषणा KVM_ASYNC_PF_DELIVERY_AS_INT		(1 << 3)

/* MSR_KVM_ASYNC_PF_INT */
#घोषणा KVM_ASYNC_PF_VEC_MASK			GENMASK(7, 0)


/* Operations क्रम KVM_HC_MMU_OP */
#घोषणा KVM_MMU_OP_WRITE_PTE            1
#घोषणा KVM_MMU_OP_FLUSH_TLB	        2
#घोषणा KVM_MMU_OP_RELEASE_PT	        3

/* Payload क्रम KVM_HC_MMU_OP */
काष्ठा kvm_mmu_op_header अणु
	__u32 op;
	__u32 pad;
पूर्ण;

काष्ठा kvm_mmu_op_ग_लिखो_pte अणु
	काष्ठा kvm_mmu_op_header header;
	__u64 pte_phys;
	__u64 pte_val;
पूर्ण;

काष्ठा kvm_mmu_op_flush_tlb अणु
	काष्ठा kvm_mmu_op_header header;
पूर्ण;

काष्ठा kvm_mmu_op_release_pt अणु
	काष्ठा kvm_mmu_op_header header;
	__u64 pt_phys;
पूर्ण;

#घोषणा KVM_PV_REASON_PAGE_NOT_PRESENT 1
#घोषणा KVM_PV_REASON_PAGE_READY 2

काष्ठा kvm_vcpu_pv_apf_data अणु
	/* Used क्रम 'page not present' events delivered via #PF */
	__u32 flags;

	/* Used क्रम 'page ready' events delivered via पूर्णांकerrupt notअगरication */
	__u32 token;

	__u8 pad[56];
	__u32 enabled;
पूर्ण;

#घोषणा KVM_PV_EOI_BIT 0
#घोषणा KVM_PV_EOI_MASK (0x1 << KVM_PV_EOI_BIT)
#घोषणा KVM_PV_EOI_ENABLED KVM_PV_EOI_MASK
#घोषणा KVM_PV_EOI_DISABLED 0x0

#पूर्ण_अगर /* _UAPI_ASM_X86_KVM_PARA_H */
