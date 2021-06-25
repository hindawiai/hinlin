<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on the x86 implementation.
 *
 * Copyright (C) 2012 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm_emulate.h>

DEFINE_STATIC_KEY_FALSE(kvm_arm_pmu_available);

अटल पूर्णांक kvm_is_in_guest(व्योम)
अणु
        वापस kvm_get_running_vcpu() != शून्य;
पूर्ण

अटल पूर्णांक kvm_is_user_mode(व्योम)
अणु
	काष्ठा kvm_vcpu *vcpu;

	vcpu = kvm_get_running_vcpu();

	अगर (vcpu)
		वापस !vcpu_mode_priv(vcpu);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ kvm_get_guest_ip(व्योम)
अणु
	काष्ठा kvm_vcpu *vcpu;

	vcpu = kvm_get_running_vcpu();

	अगर (vcpu)
		वापस *vcpu_pc(vcpu);

	वापस 0;
पूर्ण

अटल काष्ठा perf_guest_info_callbacks kvm_guest_cbs = अणु
	.is_in_guest	= kvm_is_in_guest,
	.is_user_mode	= kvm_is_user_mode,
	.get_guest_ip	= kvm_get_guest_ip,
पूर्ण;

पूर्णांक kvm_perf_init(व्योम)
अणु
	अगर (kvm_pmu_probe_pmuver() != 0xf && !is_रक्षित_kvm_enabled())
		अटल_branch_enable(&kvm_arm_pmu_available);

	वापस perf_रेजिस्टर_guest_info_callbacks(&kvm_guest_cbs);
पूर्ण

पूर्णांक kvm_perf_tearकरोwn(व्योम)
अणु
	वापस perf_unरेजिस्टर_guest_info_callbacks(&kvm_guest_cbs);
पूर्ण
