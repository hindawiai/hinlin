<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 or MIT */
#अगर_अघोषित _ASM_X86_VMWARE_H
#घोषणा _ASM_X86_VMWARE_H

#समावेश <यंत्र/cpufeatures.h>
#समावेश <यंत्र/alternative.h>
#समावेश <linux/stringअगरy.h>

/*
 * The hypercall definitions dअगरfer in the low word of the %edx argument
 * in the following way: the old port base पूर्णांकerface uses the port
 * number to distinguish between high- and low bandwidth versions.
 *
 * The new vmcall पूर्णांकerface instead uses a set of flags to select
 * bandwidth mode and transfer direction. The flags should be loaded
 * पूर्णांकo %dx by any user and are स्वतःmatically replaced by the port
 * number अगर the VMWARE_HYPERVISOR_PORT method is used.
 *
 * In लघु, new driver code should strictly use the new definition of
 * %dx content.
 */

/* Old port-based version */
#घोषणा VMWARE_HYPERVISOR_PORT    0x5658
#घोषणा VMWARE_HYPERVISOR_PORT_HB 0x5659

/* Current vmcall / vmmcall version */
#घोषणा VMWARE_HYPERVISOR_HB   BIT(0)
#घोषणा VMWARE_HYPERVISOR_OUT  BIT(1)

/* The low bandwidth call. The low word of edx is presumed clear. */
#घोषणा VMWARE_HYPERCALL						\
	ALTERNATIVE_2("movw $" __stringअगरy(VMWARE_HYPERVISOR_PORT) ", %%dx; " \
		      "inl (%%dx), %%eax",				\
		      "vmcall", X86_FEATURE_VMCALL,			\
		      "vmmcall", X86_FEATURE_VMW_VMMCALL)

/*
 * The high bandwidth out call. The low word of edx is presumed to have the
 * HB and OUT bits set.
 */
#घोषणा VMWARE_HYPERCALL_HB_OUT						\
	ALTERNATIVE_2("movw $" __stringअगरy(VMWARE_HYPERVISOR_PORT_HB) ", %%dx; " \
		      "rep outsb",					\
		      "vmcall", X86_FEATURE_VMCALL,			\
		      "vmmcall", X86_FEATURE_VMW_VMMCALL)

/*
 * The high bandwidth in call. The low word of edx is presumed to have the
 * HB bit set.
 */
#घोषणा VMWARE_HYPERCALL_HB_IN						\
	ALTERNATIVE_2("movw $" __stringअगरy(VMWARE_HYPERVISOR_PORT_HB) ", %%dx; " \
		      "rep insb",					\
		      "vmcall", X86_FEATURE_VMCALL,			\
		      "vmmcall", X86_FEATURE_VMW_VMMCALL)
#पूर्ण_अगर
