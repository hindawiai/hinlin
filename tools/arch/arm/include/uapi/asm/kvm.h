<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301, USA.
 */

#अगर_अघोषित __ARM_KVM_H__
#घोषणा __ARM_KVM_H__

#समावेश <linux/types.h>
#समावेश <linux/psci.h>
#समावेश <यंत्र/ptrace.h>

#घोषणा __KVM_HAVE_GUEST_DEBUG
#घोषणा __KVM_HAVE_IRQ_LINE
#घोषणा __KVM_HAVE_READONLY_MEM
#घोषणा __KVM_HAVE_VCPU_EVENTS

#घोषणा KVM_COALESCED_MMIO_PAGE_OFFSET 1

#घोषणा KVM_REG_SIZE(id)						\
	(1U << (((id) & KVM_REG_SIZE_MASK) >> KVM_REG_SIZE_SHIFT))

/* Valid क्रम svc_regs, abt_regs, und_regs, irq_regs in काष्ठा kvm_regs */
#घोषणा KVM_ARM_SVC_sp		svc_regs[0]
#घोषणा KVM_ARM_SVC_lr		svc_regs[1]
#घोषणा KVM_ARM_SVC_spsr	svc_regs[2]
#घोषणा KVM_ARM_ABT_sp		abt_regs[0]
#घोषणा KVM_ARM_ABT_lr		abt_regs[1]
#घोषणा KVM_ARM_ABT_spsr	abt_regs[2]
#घोषणा KVM_ARM_UND_sp		und_regs[0]
#घोषणा KVM_ARM_UND_lr		und_regs[1]
#घोषणा KVM_ARM_UND_spsr	und_regs[2]
#घोषणा KVM_ARM_IRQ_sp		irq_regs[0]
#घोषणा KVM_ARM_IRQ_lr		irq_regs[1]
#घोषणा KVM_ARM_IRQ_spsr	irq_regs[2]

/* Valid only क्रम fiq_regs in काष्ठा kvm_regs */
#घोषणा KVM_ARM_FIQ_r8		fiq_regs[0]
#घोषणा KVM_ARM_FIQ_r9		fiq_regs[1]
#घोषणा KVM_ARM_FIQ_r10		fiq_regs[2]
#घोषणा KVM_ARM_FIQ_fp		fiq_regs[3]
#घोषणा KVM_ARM_FIQ_ip		fiq_regs[4]
#घोषणा KVM_ARM_FIQ_sp		fiq_regs[5]
#घोषणा KVM_ARM_FIQ_lr		fiq_regs[6]
#घोषणा KVM_ARM_FIQ_spsr	fiq_regs[7]

काष्ठा kvm_regs अणु
	काष्ठा pt_regs usr_regs;	/* R0_usr - R14_usr, PC, CPSR */
	अचिन्हित दीर्घ svc_regs[3];	/* SP_svc, LR_svc, SPSR_svc */
	अचिन्हित दीर्घ abt_regs[3];	/* SP_abt, LR_abt, SPSR_abt */
	अचिन्हित दीर्घ und_regs[3];	/* SP_und, LR_und, SPSR_und */
	अचिन्हित दीर्घ irq_regs[3];	/* SP_irq, LR_irq, SPSR_irq */
	अचिन्हित दीर्घ fiq_regs[8];	/* R8_fiq - R14_fiq, SPSR_fiq */
पूर्ण;

/* Supported Processor Types */
#घोषणा KVM_ARM_TARGET_CORTEX_A15	0
#घोषणा KVM_ARM_TARGET_CORTEX_A7	1
#घोषणा KVM_ARM_NUM_TARGETS		2

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
#घोषणा KVM_ARM_VCPU_PSCI_0_2		1 /* CPU uses PSCI v0.2 */

काष्ठा kvm_vcpu_init अणु
	__u32 target;
	__u32 features[7];
पूर्ण;

काष्ठा kvm_sregs अणु
पूर्ण;

काष्ठा kvm_fpu अणु
पूर्ण;

काष्ठा kvm_guest_debug_arch अणु
पूर्ण;

काष्ठा kvm_debug_निकास_arch अणु
पूर्ण;

काष्ठा kvm_sync_regs अणु
	/* Used with KVM_CAP_ARM_USER_IRQ */
	__u64 device_irq_level;
पूर्ण;

काष्ठा kvm_arch_memory_slot अणु
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
#घोषणा KVM_REG_ARM_32_OPC2_MASK	0x0000000000000007
#घोषणा KVM_REG_ARM_32_OPC2_SHIFT	0
#घोषणा KVM_REG_ARM_OPC1_MASK		0x0000000000000078
#घोषणा KVM_REG_ARM_OPC1_SHIFT		3
#घोषणा KVM_REG_ARM_CRM_MASK		0x0000000000000780
#घोषणा KVM_REG_ARM_CRM_SHIFT		7
#घोषणा KVM_REG_ARM_32_CRN_MASK		0x0000000000007800
#घोषणा KVM_REG_ARM_32_CRN_SHIFT	11
/*
 * For KVM currently all guest रेजिस्टरs are nonsecure, but we reserve a bit
 * in the encoding to distinguish secure from nonsecure क्रम AArch32 प्रणाली
 * रेजिस्टरs that are banked by security. This is 1 क्रम the secure banked
 * रेजिस्टर, and 0 क्रम the nonsecure banked रेजिस्टर or अगर the रेजिस्टर is
 * not banked by security.
 */
#घोषणा KVM_REG_ARM_SECURE_MASK	0x0000000010000000
#घोषणा KVM_REG_ARM_SECURE_SHIFT	28

#घोषणा ARM_CP15_REG_SHIFT_MASK(x,n) \
	(((x) << KVM_REG_ARM_ ## n ## _SHIFT) & KVM_REG_ARM_ ## n ## _MASK)

#घोषणा __ARM_CP15_REG(op1,crn,crm,op2) \
	(KVM_REG_ARM | (15 << KVM_REG_ARM_COPROC_SHIFT) | \
	ARM_CP15_REG_SHIFT_MASK(op1, OPC1) | \
	ARM_CP15_REG_SHIFT_MASK(crn, 32_CRN) | \
	ARM_CP15_REG_SHIFT_MASK(crm, CRM) | \
	ARM_CP15_REG_SHIFT_MASK(op2, 32_OPC2))

#घोषणा ARM_CP15_REG32(...) (__ARM_CP15_REG(__VA_ARGS__) | KVM_REG_SIZE_U32)

#घोषणा __ARM_CP15_REG64(op1,crm) \
	(__ARM_CP15_REG(op1, 0, crm, 0) | KVM_REG_SIZE_U64)
#घोषणा ARM_CP15_REG64(...) __ARM_CP15_REG64(__VA_ARGS__)

/* PL1 Physical Timer Registers */
#घोषणा KVM_REG_ARM_PTIMER_CTL		ARM_CP15_REG32(0, 14, 2, 1)
#घोषणा KVM_REG_ARM_PTIMER_CNT		ARM_CP15_REG64(0, 14)
#घोषणा KVM_REG_ARM_PTIMER_CVAL		ARM_CP15_REG64(2, 14)

/* Virtual Timer Registers */
#घोषणा KVM_REG_ARM_TIMER_CTL		ARM_CP15_REG32(0, 14, 3, 1)
#घोषणा KVM_REG_ARM_TIMER_CNT		ARM_CP15_REG64(1, 14)
#घोषणा KVM_REG_ARM_TIMER_CVAL		ARM_CP15_REG64(3, 14)

/* Normal रेजिस्टरs are mapped as coprocessor 16. */
#घोषणा KVM_REG_ARM_CORE		(0x0010 << KVM_REG_ARM_COPROC_SHIFT)
#घोषणा KVM_REG_ARM_CORE_REG(name)	(दुरत्व(काष्ठा kvm_regs, name) / 4)

/* Some रेजिस्टरs need more space to represent values. */
#घोषणा KVM_REG_ARM_DEMUX		(0x0011 << KVM_REG_ARM_COPROC_SHIFT)
#घोषणा KVM_REG_ARM_DEMUX_ID_MASK	0x000000000000FF00
#घोषणा KVM_REG_ARM_DEMUX_ID_SHIFT	8
#घोषणा KVM_REG_ARM_DEMUX_ID_CCSIDR	(0x00 << KVM_REG_ARM_DEMUX_ID_SHIFT)
#घोषणा KVM_REG_ARM_DEMUX_VAL_MASK	0x00000000000000FF
#घोषणा KVM_REG_ARM_DEMUX_VAL_SHIFT	0

/* VFP रेजिस्टरs: we could overload CP10 like ARM करोes, but that's ugly. */
#घोषणा KVM_REG_ARM_VFP			(0x0012 << KVM_REG_ARM_COPROC_SHIFT)
#घोषणा KVM_REG_ARM_VFP_MASK		0x000000000000FFFF
#घोषणा KVM_REG_ARM_VFP_BASE_REG	0x0
#घोषणा KVM_REG_ARM_VFP_FPSID		0x1000
#घोषणा KVM_REG_ARM_VFP_FPSCR		0x1001
#घोषणा KVM_REG_ARM_VFP_MVFR1		0x1006
#घोषणा KVM_REG_ARM_VFP_MVFR0		0x1007
#घोषणा KVM_REG_ARM_VFP_FPEXC		0x1008
#घोषणा KVM_REG_ARM_VFP_FPINST		0x1009
#घोषणा KVM_REG_ARM_VFP_FPINST2		0x100A

/* KVM-as-firmware specअगरic pseuकरो-रेजिस्टरs */
#घोषणा KVM_REG_ARM_FW			(0x0014 << KVM_REG_ARM_COPROC_SHIFT)
#घोषणा KVM_REG_ARM_FW_REG(r)		(KVM_REG_ARM | KVM_REG_SIZE_U64 | \
					 KVM_REG_ARM_FW | ((r) & 0xffff))
#घोषणा KVM_REG_ARM_PSCI_VERSION	KVM_REG_ARM_FW_REG(0)
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1	KVM_REG_ARM_FW_REG(1)
	/* Higher values mean better protection. */
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_AVAIL		0
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_AVAIL		1
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_REQUIRED	2
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2	KVM_REG_ARM_FW_REG(2)
	/* Higher values mean better protection. */
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_AVAIL		0
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_UNKNOWN		1
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_AVAIL		2
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_REQUIRED	3
#घोषणा KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_ENABLED	(1U << 4)

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
#घोषणा KVM_DEV_ARM_VGIC_GRP_CTRL       4
#घोषणा KVM_DEV_ARM_VGIC_GRP_REDIST_REGS 5
#घोषणा KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS 6
#घोषणा KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO  7
#घोषणा KVM_DEV_ARM_VGIC_GRP_ITS_REGS	8
#घोषणा KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT	10
#घोषणा KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_MASK \
			(0x3fffffULL << KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT)
#घोषणा KVM_DEV_ARM_VGIC_LINE_LEVEL_INTID_MASK 0x3ff
#घोषणा VGIC_LEVEL_INFO_LINE_LEVEL	0

/* Device Control API on vcpu fd */
#घोषणा KVM_ARM_VCPU_PMU_V3_CTRL	0
#घोषणा   KVM_ARM_VCPU_PMU_V3_IRQ	0
#घोषणा   KVM_ARM_VCPU_PMU_V3_INIT	1
#घोषणा KVM_ARM_VCPU_TIMER_CTRL		1
#घोषणा   KVM_ARM_VCPU_TIMER_IRQ_VTIMER		0
#घोषणा   KVM_ARM_VCPU_TIMER_IRQ_PTIMER		1

#घोषणा   KVM_DEV_ARM_VGIC_CTRL_INIT		0
#घोषणा   KVM_DEV_ARM_ITS_SAVE_TABLES		1
#घोषणा   KVM_DEV_ARM_ITS_RESTORE_TABLES	2
#घोषणा   KVM_DEV_ARM_VGIC_SAVE_PENDING_TABLES	3
#घोषणा   KVM_DEV_ARM_ITS_CTRL_RESET		4

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

#पूर्ण_अगर /* __ARM_KVM_H__ */
