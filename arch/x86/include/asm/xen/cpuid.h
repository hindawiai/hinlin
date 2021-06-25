<शैली गुरु>
/******************************************************************************
 * arch-x86/cpuid.h
 *
 * CPUID पूर्णांकerface to Xen.
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
 * Copyright (c) 2007 Citrix Systems, Inc.
 *
 * Authors:
 *    Keir Fraser <keir@xen.org>
 */

#अगर_अघोषित __XEN_PUBLIC_ARCH_X86_CPUID_H__
#घोषणा __XEN_PUBLIC_ARCH_X86_CPUID_H__

/*
 * For compatibility with other hypervisor पूर्णांकerfaces, the Xen cpuid leaves
 * can be found at the first otherwise unused 0x100 aligned boundary starting
 * from 0x40000000.
 *
 * e.g If viridian extensions are enabled क्रम an HVM करोमुख्य, the Xen cpuid
 * leaves will start at 0x40000100
 */

#घोषणा XEN_CPUID_FIRST_LEAF 0x40000000
#घोषणा XEN_CPUID_LEAF(i)    (XEN_CPUID_FIRST_LEAF + (i))

/*
 * Leaf 1 (0x40000x00)
 * EAX: Largest Xen-inक्रमmation leaf. All leaves up to an including @EAX
 *      are supported by the Xen host.
 * EBX-EDX: "XenVMMXenVMM" signature, allowing positive identअगरication
 *      of a Xen host.
 */
#घोषणा XEN_CPUID_SIGNATURE_EBX 0x566e6558 /* "XenV" */
#घोषणा XEN_CPUID_SIGNATURE_ECX 0x65584d4d /* "MMXe" */
#घोषणा XEN_CPUID_SIGNATURE_EDX 0x4d4d566e /* "nVMM" */

/*
 * Leaf 2 (0x40000x01)
 * EAX[31:16]: Xen major version.
 * EAX[15: 0]: Xen minor version.
 * EBX-EDX: Reserved (currently all zeroes).
 */

/*
 * Leaf 3 (0x40000x02)
 * EAX: Number of hypercall transfer pages. This रेजिस्टर is always guaranteed
 *      to specअगरy one hypercall page.
 * EBX: Base address of Xen-specअगरic MSRs.
 * ECX: Features 1. Unused bits are set to zero.
 * EDX: Features 2. Unused bits are set to zero.
 */

/* Does the host support MMU_PT_UPDATE_PRESERVE_AD क्रम this guest? */
#घोषणा _XEN_CPUID_FEAT1_MMU_PT_UPDATE_PRESERVE_AD 0
#घोषणा XEN_CPUID_FEAT1_MMU_PT_UPDATE_PRESERVE_AD  (1u<<0)

/*
 * Leaf 4 (0x40000x03)
 * Sub-leaf 0: EAX: bit 0: emulated tsc
 *                  bit 1: host tsc is known to be reliable
 *                  bit 2: RDTSCP inकाष्ठाion available
 *             EBX: tsc_mode: 0=शेष (emulate अगर necessary), 1=emulate,
 *                            2=no emulation, 3=no emulation + TSC_AUX support
 *             ECX: guest tsc frequency in kHz
 *             EDX: guest tsc incarnation (migration count)
 * Sub-leaf 1: EAX: tsc offset low part
 *             EBX: tsc offset high part
 *             ECX: multiplicator क्रम tsc->ns conversion
 *             EDX: shअगरt amount क्रम tsc->ns conversion
 * Sub-leaf 2: EAX: host tsc frequency in kHz
 */

/*
 * Leaf 5 (0x40000x04)
 * HVM-specअगरic features
 * Sub-leaf 0: EAX: Features
 * Sub-leaf 0: EBX: vcpu id (अगरf EAX has XEN_HVM_CPUID_VCPU_ID_PRESENT flag)
 */
#घोषणा XEN_HVM_CPUID_APIC_ACCESS_VIRT (1u << 0) /* Virtualized APIC रेजिस्टरs */
#घोषणा XEN_HVM_CPUID_X2APIC_VIRT      (1u << 1) /* Virtualized x2APIC accesses */
/* Memory mapped from other करोमुख्यs has valid IOMMU entries */
#घोषणा XEN_HVM_CPUID_IOMMU_MAPPINGS   (1u << 2)
#घोषणा XEN_HVM_CPUID_VCPU_ID_PRESENT  (1u << 3) /* vcpu id is present in EBX */

/*
 * Leaf 6 (0x40000x05)
 * PV-specअगरic parameters
 * Sub-leaf 0: EAX: max available sub-leaf
 * Sub-leaf 0: EBX: bits 0-7: max machine address width
 */

/* Max. address width in bits taking memory hotplug पूर्णांकo account. */
#घोषणा XEN_CPUID_MACHINE_ADDRESS_WIDTH_MASK (0xffu << 0)

#घोषणा XEN_CPUID_MAX_NUM_LEAVES 5

#पूर्ण_अगर /* __XEN_PUBLIC_ARCH_X86_CPUID_H__ */
