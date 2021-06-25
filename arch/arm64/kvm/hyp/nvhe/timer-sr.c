<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <घड़ीsource/arm_arch_समयr.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm_hyp.h>

व्योम __kvm_समयr_set_cntvoff(u64 cntvoff)
अणु
	ग_लिखो_sysreg(cntvoff, cntvoff_el2);
पूर्ण

/*
 * Should only be called on non-VHE प्रणालीs.
 * VHE प्रणालीs use EL2 समयrs and configure EL1 समयrs in kvm_समयr_init_vhe().
 */
व्योम __समयr_disable_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 val;

	/* Allow physical समयr/counter access क्रम the host */
	val = पढ़ो_sysreg(cnthctl_el2);
	val |= CNTHCTL_EL1PCTEN | CNTHCTL_EL1PCEN;
	ग_लिखो_sysreg(val, cnthctl_el2);
पूर्ण

/*
 * Should only be called on non-VHE प्रणालीs.
 * VHE प्रणालीs use EL2 समयrs and configure EL1 समयrs in kvm_समयr_init_vhe().
 */
व्योम __समयr_enable_traps(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 val;

	/*
	 * Disallow physical समयr access क्रम the guest
	 * Physical counter access is allowed
	 */
	val = पढ़ो_sysreg(cnthctl_el2);
	val &= ~CNTHCTL_EL1PCEN;
	val |= CNTHCTL_EL1PCTEN;
	ग_लिखो_sysreg(val, cnthctl_el2);
पूर्ण
