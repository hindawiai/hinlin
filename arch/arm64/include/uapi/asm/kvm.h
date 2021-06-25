<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Derived from arch/arm/include/uapi/यंत्र/kvm.h:
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#अगर_अघोषित __ARM_KVM_H__
#घोषणा __ARM_KVM_H__

#घोषणा KVM_SPSR_EL1	0
#घोषणा KVM_SPSR_SVC	KVM_SPSR_EL1
#घोषणा KVM_SPSR_ABT	1
#घोषणा KVM_SPSR_UND	2
#घोषणा KVM_SPSR_IRQ	3
#घोषणा KVM_SPSR_FIQ	4
#घोषणा KVM_NR_SPSR	5

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/psci.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sve_context.h>

#घोषणा __KVM_HAVE_GUEST_DEBUG
#घोषणा __KVM_HAVE_IRQ_LINE
#घोषणा __KVM_HAVE_READONLY_MEM
#घोषणा __KVM_HAVE_VCPU_EVENTS

#घोषणा KVM_COALESCED_MMIO_PAGE_OFFSET 1

#घोषणा KVM_REG_SIZE(id)						\
	(1U << (((id) & KVM_REG_SIZE_MASK) >> KVM_REG_SIZE_SHIFT))

काष्ठा kvm_regs अणु
	काष्ठा user_pt_regs regs;	/* sp = sp_el0 */

	__u64	sp_el1;
	__u64	elr_el1;

	__u64	spsr[KVM_NR_SPSR];

	काष्ठा user_fpsimd_state fp_regs;
पूर्ण;

/*
 * Supported CPU Tarमाला_लो - Adding a new target type is not recommended,
 * unless there are some special रेजिस्टरs not supported by the
 * genericv8 syreg table.
 */
#घोषणा KVM_ARM_TARGET_AEM_V8		0
#घोषणा KVM_ARM_TARGET_FOUNDATION_V8	1
#घोषणा KVM_ARM_TARGET_CORTEX_A57	2
#घोषणा KVM_ARM_TARGET_XGENE_POTENZA	3
#घोषणा KVM_ARM_TARGET_CORTEX_A53	4
/* Generic ARM v8 target */
#घोषणा KVM_ARM_TARGET_GENERIC_V8	5

#घोषणा KVM_ARM_NUM_TARGETS		6

/* KVM_ARM_SET_DEVICE_ADDR ioctl id encoding */
#घोषणा KVM_ARM_DEVICE_TYPE_SHIFT	0
#घोषणा KVM_ARM_DEVICE_TYPE_MASK	(0xffff << KVM_ARM_DEVICE_TYPE_SHIFT)
#घोषणा KVM_ARM_DEVICE_ID_SHIFT		16
#घोषणा KVM_ARM_DEVICE_ID_MASK		(0xffff << KVM_ARM_DEVICE_ID_SHIFT)

/* Supported device IDs */
#घोषणा KVM_ARM_DEVICE_VGIC_V2		0

/* Supported VGIC address types  */
#घोषणा KVM_VGIC_V2_ADDR_TYPE_DIST	0
#घोषणा KVM_VGIC_V2_ADDR_TYPE_CPU	1

#घोषणा KVM_VGIC_V2_DIST_SIZE		0x1000
#घोषणा KVM_VGIC_V2_CPU_SIZE		0x2000

/* Supported VGICv3 address types  */
#घोषणा KVM_VGIC_V3_ADDR_TYPE_DIST	2
#घोषणा KVM_VGIC_V3_ADDR_TYPE_REDIST	3
#घोषणा KVM_VGIC_ITS_ADDR_TYPE		4
#घोषणा KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION	5

#घोषणा KVM_VGIC_V3_DIST_SIZE		SZ_64K
#घोषणा KVM_VGIC_V3_REDIST_SIZE		(2 * SZ_64K)
#घोषणा KVM_VGIC_V3_ITS_SIZE		(2 * SZ_64K)

#घोषणा KVM_ARM_VCPU_POWER_OFF		0 /* CPU is started in OFF state */
#घोषणा KVM_ARM_VCPU_EL1_32BIT		1 /* CPU running a 32bit VM */
#घोषणा KVM_ARM_VCPU_PSCI_0_2		2 /* CPU uses PSCI v0.2 */
#घोषणा KVM_ARM_VCPU_PMU_V3		3 /* Support guest PMUv3 */
#घोषणा KVM_ARM_VCPU_SVE		4 /* enable SVE क्रम this CPU */
#घोषणा KVM_ARM_VCPU_PTRAUTH_ADDRESS	5 /* VCPU uses address authentication */
#घोषणा KVM_ARM_VCPU_PTRAUTH_GENERIC	6 /* VCPU uses generic authentication */

काष्ठा kvm_vcpu_init अणु
	__u32 target;
	__u32 features[7];
पूर्ण;

काष्ठा kvm_sregs अणु
पूर्ण;

काष्ठा kvm_fpu अणु
पूर्ण;

/*
 * See v8 ARM ARM D7.3: Debug Registers
 *
 * The architectural limit is 16 debug रेजिस्टरs of each type although
 * in practice there are usually less (see ID_AA64DFR0_EL1).
 *
 * Although the control रेजिस्टरs are architecturally defined as 32
 * bits wide we use a 64 bit काष्ठाure here to keep parity with
 * KVM_GET/SET_ONE_REG behaviour which treats all प्रणाली रेजिस्टरs as
 * 64 bit values. It also allows क्रम the possibility of the
 * architecture expanding the control रेजिस्टरs without having to
 * change the userspace ABI.
 */
#घोषणा KVM_ARM_MAX_DBG_REGS 16
काष्ठा kvm_guest_debug_arch अणु
	__u64 dbg_bcr[KVM_ARM_MAX_DBG_REGS];
	__u64 dbg_bvr[KVM_ARM_MAX_DBG_REGS];
	__u64 dbg_wcr[KVM_ARM_MAX_DBG_REGS];
	__u64 dbg_wvr[KVM_ARM_MAX_DBG_REGS];
पूर्ण;

काष्ठा kvm_debug_निकास_arch अणु
	__u32 hsr;
	__u64 far;	/* used क्रम watchpoपूर्णांकs */
पूर्ण;

/*
 * Architecture specअगरic defines क्रम kvm_guest_debug->control
 */

#घोषणा KVM_GUESTDBG_USE_SW_BP		(1 << 16)
#घोषणा KVM_GUESTDBG_USE_HW		(1 << 17)

काष्ठा kvm_sync_regs अणु
	/* Used with KVM_CAP_ARM_USER_IRQ */
	__u64 device_irq_level;
पूर्ण;

/*
 * PMU filter काष्ठाure. Describe a range of events with a particular
 * action. To be used with KVM_ARM_VCPU_PMU_V3_FILTER.
 */
काष्ठा kvm_pmu_event_filter अणु
	__u16	base_event;
	__u16	nevents;

#घोषणा KVM_PMU_EVENT_ALLOW	0
#घोषणा KVM_PMU_EVENT_DENY	1

	__u8	action;
	__u8	pad[3];
पूर्ण;

/* क्रम KVM_GET/SET_VCPU_EVENTS */
काष्ठा kvm_vcpu_events अणु
	काष्ठा अणु
		__u8 serror_pending;
		__u8 serror_has_esr;
		__u8 ext_dabt_pending;
		/* Align it to 8 bytes */
		__u8 pad[5];
		__u64 serror_esr;
	पूर्ण exception;
	__u32 reserved[12];
पूर्ण;

/* If you need to पूर्णांकerpret the index values, here is the key: */
#घोषणा KVM_REG_ARM_COPROC_MASK		0x000000000FFF0000
#घोषणा KVM_REG_ARM_COPROC_SHIFT	16

/* Normal रेजिस्टरs are mapped as coprocessor 16. */
#घोषणा KVM_REG_ARM_CORE		(0x0010 << KVM_REG_ARM_COPROC_SHIFT)
#घोषणा KVM_REG_ARM_CORE_REG(name)	(दुरत्व(काष्ठा kvm_regs, name) / माप(__u32))

/* Some रेजिस्टरs need more space to represent values. */
#घोषणा KVM_REG_ARM_DEMUX		(0x0011 << KVM_REG_ARM_COPROC_SHIFT)
#घोषणा KVM_REG_ARM_DEMUX_ID_MASK	0x000000000000FF00
#घोषणा KVM_REG_ARM_DEMUX_ID_SHIFT	8
#घोषणा KVM_REG_ARM_DEMUX_ID_CCSIDR	(0x00 << KVM_REG_ARM_DEMUX_ID_SHIFT)
#घोषणा KVM_REG_ARM_DEMUX_VAL_MASK	0x00000000000000FF
#घोषणा KVM_REG_ARM_DEMUX_VAL_SHIFT	0

/* AArch64 प्रणाली रेजिस्टरs */
#घोषणा KVM_REG_ARM64_SYSREG		(0x0013 << KVM_REG_ARM_COPROC_SHIFT)
#घोषणा KVM_REG_ARM64_SYSREG_OP0_MASK	0x000000000000c000
#घोषणा KVM_REG_ARM64_SYSREG_OP0_SHIFT	14
#घोषणा KVM_REG_ARM64_SYSREG_OP1_MASK	0x0000000000003800
#घोषणा KVM_REG_ARM64_SYSREG_OP1_SHIFT	11
#घोषणा KVM_REG_ARM64_SYSREG_CRN_MASK	0x0000000000000780
#घोषणा KVM_REG_ARM64_SYSREG_CRN_SHIFT	7
#घोषणा KVM_REG_ARM64_SYSREG_CRM_MASK	0x0000000000000078
#घोषणा KVM_REG_ARM64_SYSREG_CRM_SHIFT	3
#घोषणा KVM_REG_ARM64_SYSREG_OP2_MASK	0x0000000000000007
#घोषणा KVM_REG_ARM64_SYSREG_OP2_SHIFT	0

#घोषणा ARM64_SYS_REG_SHIFT_MASK(x,n) \
	(((x) << KVM_REG_ARM64_SYSREG_ ## n ## _SHIFT) & \
	KVM_REG_ARM64_SYSREG_ ## n ## _MASK)

#घोषणा __ARM64_SYS_REG(op0,op1,crn,crm,op2) \
	(KVM_REG_ARM64 | KVM_REG_ARM64_SYSREG | \
	ARM64_SYS_REG_SHIFT_MASK(op0, OP0) | \
	ARM64_SYS_REG_SHIFT_MASK(op1, OP1) | \
	ARM64_SYS_REG_SHIFT_MASK(crn, CRN) | \
	ARM64_SYS_REG_SHIFT_MASK(crm, CRM) | \
	ARM64_SYS_REG_SHIFT_MASK(op2, OP2))

#घोषणा ARM64_SYS_REG(...) (__ARM64_SYS_REG(__VA_ARGS__) | KVM_REG_SIZE_U64)

/* Physical Timer EL0 Registers */
#घोषणा KVM_REG_ARM_PTIMER_CTL		ARM64_SYS_REG(3, 3, 14, 2, 1)
#घोषणा KVM_REG_ARM_PTIMER_CVAL		ARM64_SYS_REG(3, 3, 14, 2, 2)
#घोषणा KVM_REG_ARM_PTIMER_CNT		ARM64_SYS_REG(3, 3, 14, 0, 1)

/*
 * EL0 Virtual Timer Registers
 *
 * WARNING:
 *      KVM_REG_ARM_TIMER_CVAL and KVM_REG_ARM_TIMER_CNT are not defined
 *      with the appropriate रेजिस्टर encodings.  Their values have been
 *      accidentally swapped.  As this is set API, the definitions here
 *      must be used, rather than ones derived from the encodings.
 */
#घोषणा KVM_REG_ARM_TIMER_CTL		ARM64_SYS_REG(3, 3, 14, 3, 1)
#घोषणा KVM_REG_ARM_TIMER_CVAL		ARM64_SYS_REG(3, 3, 14, 0, 2)
#घोषणा KVM_REG_ARM_TIMER_CNT		ARM64_SYS_REG(3, 3, 14, 3, 2)

/* KVM-as-firmware specअगरic pseuकरो-रेजिस्टरs */
#घोषणा KVM_REG_ARM_FW			(0x0014 << KVM_REG_ARM_COPROC_SHIFT)
#घोषणा KVM_REG_ARM_FW_REG(r)		(KVM_REG_ARM64 | KVM_REG_SIZE_U64 | \
					 KVM_REG_ARM_FW | ((r) & 0xffff))
#घोषणा KVM_REG_ARM_PSCI_VERSION	KVM_REG_ARM_FW_REG(0)
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1	KVM_REG_ARM_FW_REG(1)
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_AVAIL		0
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_AVAIL		1
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_REQUIRED	2

/*
 * Only two states can be presented by the host kernel:
 * - NOT_REQUIRED: the guest करोesn't need to करो anything
 * - NOT_AVAIL: the guest isn't mitigated (it can still use SSBS अगर available)
 *
 * All the other values are deprecated. The host still accepts all
 * values (they are ABI), but will narrow them to the above two.
 */
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2	KVM_REG_ARM_FW_REG(2)
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_AVAIL		0
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_UNKNOWN		1
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_AVAIL		2
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_REQUIRED	3
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_ENABLED     	(1U << 4)

/* SVE रेजिस्टरs */
#घोषणा KVM_REG_ARM64_SVE		(0x15 << KVM_REG_ARM_COPROC_SHIFT)

/* Z- and P-regs occupy blocks at the following offsets within this range: */
#घोषणा KVM_REG_ARM64_SVE_ZREG_BASE	0
#घोषणा KVM_REG_ARM64_SVE_PREG_BASE	0x400
#घोषणा KVM_REG_ARM64_SVE_FFR_BASE	0x600

#घोषणा KVM_ARM64_SVE_NUM_ZREGS		__SVE_NUM_ZREGS
#घोषणा KVM_ARM64_SVE_NUM_PREGS		__SVE_NUM_PREGS

#घोषणा KVM_ARM64_SVE_MAX_SLICES	32

#घोषणा KVM_REG_ARM64_SVE_ZREG(n, i)					\
	(KVM_REG_ARM64 | KVM_REG_ARM64_SVE | KVM_REG_ARM64_SVE_ZREG_BASE | \
	 KVM_REG_SIZE_U2048 |						\
	 (((n) & (KVM_ARM64_SVE_NUM_ZREGS - 1)) << 5) |			\
	 ((i) & (KVM_ARM64_SVE_MAX_SLICES - 1)))

#घोषणा KVM_REG_ARM64_SVE_PREG(n, i)					\
	(KVM_REG_ARM64 | KVM_REG_ARM64_SVE | KVM_REG_ARM64_SVE_PREG_BASE | \
	 KVM_REG_SIZE_U256 |						\
	 (((n) & (KVM_ARM64_SVE_NUM_PREGS - 1)) << 5) |			\
	 ((i) & (KVM_ARM64_SVE_MAX_SLICES - 1)))

#घोषणा KVM_REG_ARM64_SVE_FFR(i)					\
	(KVM_REG_ARM64 | KVM_REG_ARM64_SVE | KVM_REG_ARM64_SVE_FFR_BASE | \
	 KVM_REG_SIZE_U256 |						\
	 ((i) & (KVM_ARM64_SVE_MAX_SLICES - 1)))

/*
 * Register values क्रम KVM_REG_ARM64_SVE_ZREG(), KVM_REG_ARM64_SVE_PREG() and
 * KVM_REG_ARM64_SVE_FFR() are represented in memory in an endianness-
 * invariant layout which dअगरfers from the layout used क्रम the FPSIMD
 * V-रेजिस्टरs on big-endian प्रणालीs: see sigcontext.h क्रम more explanation.
 */

#घोषणा KVM_ARM64_SVE_VQ_MIN __SVE_VQ_MIN
#घोषणा KVM_ARM64_SVE_VQ_MAX __SVE_VQ_MAX

/* Vector lengths pseuकरो-रेजिस्टर: */
#घोषणा KVM_REG_ARM64_SVE_VLS		(KVM_REG_ARM64 | KVM_REG_ARM64_SVE | \
					 KVM_REG_SIZE_U512 | 0xffff)
#घोषणा KVM_ARM64_SVE_VLS_WORDS	\
	((KVM_ARM64_SVE_VQ_MAX - KVM_ARM64_SVE_VQ_MIN) / 64 + 1)

/* Device Control API: ARM VGIC */
#घोषणा KVM_DEV_ARM_VGIC_GRP_ADDR	0
#घोषणा KVM_DEV_ARM_VGIC_GRP_DIST_REGS	1
#घोषणा KVM_DEV_ARM_VGIC_GRP_CPU_REGS	2
#घोषणा   KVM_DEV_ARM_VGIC_CPUID_SHIFT	32
#घोषणा   KVM_DEV_ARM_VGIC_CPUID_MASK	(0xffULL << KVM_DEV_ARM_VGIC_CPUID_SHIFT)
#घोषणा   KVM_DEV_ARM_VGIC_V3_MPIDR_SHIFT 32
#घोषणा   KVM_DEV_ARM_VGIC_V3_MPIDR_MASK \
			(0xffffffffULL << KVM_DEV_ARM_VGIC_V3_MPIDR_SHIFT)
#घोषणा   KVM_DEV_ARM_VGIC_OFFSET_SHIFT	0
#घोषणा   KVM_DEV_ARM_VGIC_OFFSET_MASK	(0xffffffffULL << KVM_DEV_ARM_VGIC_OFFSET_SHIFT)
#घोषणा   KVM_DEV_ARM_VGIC_SYSREG_INSTR_MASK (0xffff)
#घोषणा KVM_DEV_ARM_VGIC_GRP_NR_IRQS	3
#घोषणा KVM_DEV_ARM_VGIC_GRP_CTRL	4
#घोषणा KVM_DEV_ARM_VGIC_GRP_REDIST_REGS 5
#घोषणा KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS 6
#घोषणा KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO  7
#घोषणा KVM_DEV_ARM_VGIC_GRP_ITS_REGS 8
#घोषणा KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT	10
#घोषणा KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_MASK \
			(0x3fffffULL << KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT)
#घोषणा KVM_DEV_ARM_VGIC_LINE_LEVEL_INTID_MASK	0x3ff
#घोषणा VGIC_LEVEL_INFO_LINE_LEVEL	0

#घोषणा   KVM_DEV_ARM_VGIC_CTRL_INIT		0
#घोषणा   KVM_DEV_ARM_ITS_SAVE_TABLES           1
#घोषणा   KVM_DEV_ARM_ITS_RESTORE_TABLES        2
#घोषणा   KVM_DEV_ARM_VGIC_SAVE_PENDING_TABLES	3
#घोषणा   KVM_DEV_ARM_ITS_CTRL_RESET		4

/* Device Control API on vcpu fd */
#घोषणा KVM_ARM_VCPU_PMU_V3_CTRL	0
#घोषणा   KVM_ARM_VCPU_PMU_V3_IRQ	0
#घोषणा   KVM_ARM_VCPU_PMU_V3_INIT	1
#घोषणा   KVM_ARM_VCPU_PMU_V3_FILTER	2
#घोषणा KVM_ARM_VCPU_TIMER_CTRL		1
#घोषणा   KVM_ARM_VCPU_TIMER_IRQ_VTIMER		0
#घोषणा   KVM_ARM_VCPU_TIMER_IRQ_PTIMER		1
#घोषणा KVM_ARM_VCPU_PVTIME_CTRL	2
#घोषणा   KVM_ARM_VCPU_PVTIME_IPA	0

/* KVM_IRQ_LINE irq field index values */
#घोषणा KVM_ARM_IRQ_VCPU2_SHIFT		28
#घोषणा KVM_ARM_IRQ_VCPU2_MASK		0xf
#घोषणा KVM_ARM_IRQ_TYPE_SHIFT		24
#घोषणा KVM_ARM_IRQ_TYPE_MASK		0xf
#घोषणा KVM_ARM_IRQ_VCPU_SHIFT		16
#घोषणा KVM_ARM_IRQ_VCPU_MASK		0xff
#घोषणा KVM_ARM_IRQ_NUM_SHIFT		0
#घोषणा KVM_ARM_IRQ_NUM_MASK		0xffff

/* irq_type field */
#घोषणा KVM_ARM_IRQ_TYPE_CPU		0
#घोषणा KVM_ARM_IRQ_TYPE_SPI		1
#घोषणा KVM_ARM_IRQ_TYPE_PPI		2

/* out-of-kernel GIC cpu पूर्णांकerrupt injection irq_number field */
#घोषणा KVM_ARM_IRQ_CPU_IRQ		0
#घोषणा KVM_ARM_IRQ_CPU_FIQ		1

/*
 * This used to hold the highest supported SPI, but it is now obsolete
 * and only here to provide source code level compatibility with older
 * userland. The highest SPI number can be set via KVM_DEV_ARM_VGIC_GRP_NR_IRQS.
 */
#अगर_अघोषित __KERNEL__
#घोषणा KVM_ARM_IRQ_GIC_MAX		127
#पूर्ण_अगर

/* One single KVM irqchip, ie. the VGIC */
#घोषणा KVM_NR_IRQCHIPS          1

/* PSCI पूर्णांकerface */
#घोषणा KVM_PSCI_FN_BASE		0x95c1ba5e
#घोषणा KVM_PSCI_FN(n)			(KVM_PSCI_FN_BASE + (n))

#घोषणा KVM_PSCI_FN_CPU_SUSPEND		KVM_PSCI_FN(0)
#घोषणा KVM_PSCI_FN_CPU_OFF		KVM_PSCI_FN(1)
#घोषणा KVM_PSCI_FN_CPU_ON		KVM_PSCI_FN(2)
#घोषणा KVM_PSCI_FN_MIGRATE		KVM_PSCI_FN(3)

#घोषणा KVM_PSCI_RET_SUCCESS		PSCI_RET_SUCCESS
#घोषणा KVM_PSCI_RET_NI			PSCI_RET_NOT_SUPPORTED
#घोषणा KVM_PSCI_RET_INVAL		PSCI_RET_INVALID_PARAMS
#घोषणा KVM_PSCI_RET_DENIED		PSCI_RET_DENIED

#पूर्ण_अगर

#पूर्ण_अगर /* __ARM_KVM_H__ */
