<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <hyp/debug-sr.h>

#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm_hyp.h>

व्योम __debug_चयन_to_guest(काष्ठा kvm_vcpu *vcpu)
अणु
	__debug_चयन_to_guest_common(vcpu);
पूर्ण

व्योम __debug_चयन_to_host(काष्ठा kvm_vcpu *vcpu)
अणु
	__debug_चयन_to_host_common(vcpu);
पूर्ण

u32 __kvm_get_mdcr_el2(व्योम)
अणु
	वापस पढ़ो_sysreg(mdcr_el2);
पूर्ण
