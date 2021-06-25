<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Virtual PTP 1588 घड़ी क्रम use with KVM guests
 *  Copyright (C) 2019 ARM Ltd.
 *  All Rights Reserved
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/ptp_kvm.h>

#समावेश <यंत्र/arch_समयr.h>
#समावेश <यंत्र/hypervisor.h>

पूर्णांक kvm_arch_ptp_init(व्योम)
अणु
	पूर्णांक ret;

	ret = kvm_arm_hyp_service_available(ARM_SMCCC_KVM_FUNC_PTP);
	अगर (ret <= 0)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_ptp_get_घड़ी(काष्ठा बारpec64 *ts)
अणु
	वापस kvm_arch_ptp_get_crosststamp(शून्य, ts, शून्य);
पूर्ण
