<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtual PTP 1588 घड़ी क्रम use with KVM guests
 *
 * Copyright (C) 2017 Red Hat Inc.
 */
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/ptp_kvm.h>
#समावेश <uapi/linux/kvm_para.h>
#समावेश <यंत्र/kvm_para.h>
#समावेश <uapi/यंत्र/kvm_para.h>

#समावेश <linux/ptp_घड़ी_kernel.h>

काष्ठा kvm_ptp_घड़ी अणु
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info caps;
पूर्ण;

अटल DEFINE_SPINLOCK(kvm_ptp_lock);

अटल पूर्णांक ptp_kvm_get_समय_fn(kसमय_प्रकार *device_समय,
			       काष्ठा प्रणाली_counterval_t *प्रणाली_counter,
			       व्योम *ctx)
अणु
	दीर्घ ret;
	u64 cycle;
	काष्ठा बारpec64 tspec;
	काष्ठा घड़ीsource *cs;

	spin_lock(&kvm_ptp_lock);

	preempt_disable_notrace();
	ret = kvm_arch_ptp_get_crosststamp(&cycle, &tspec, &cs);
	अगर (ret) अणु
		spin_unlock(&kvm_ptp_lock);
		preempt_enable_notrace();
		वापस ret;
	पूर्ण

	preempt_enable_notrace();

	प्रणाली_counter->cycles = cycle;
	प्रणाली_counter->cs = cs;

	*device_समय = बारpec64_to_kसमय(tspec);

	spin_unlock(&kvm_ptp_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_kvm_अ_लोrosststamp(काष्ठा ptp_घड़ी_info *ptp,
				  काष्ठा प्रणाली_device_crosststamp *xtstamp)
अणु
	वापस get_device_प्रणाली_crosststamp(ptp_kvm_get_समय_fn, शून्य,
					     शून्य, xtstamp);
पूर्ण

/*
 * PTP घड़ी operations
 */

अटल पूर्णांक ptp_kvm_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ptp_kvm_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ptp_kvm_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			   स्थिर काष्ठा बारpec64 *ts)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ptp_kvm_समय_लो(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts)
अणु
	दीर्घ ret;
	काष्ठा बारpec64 tspec;

	spin_lock(&kvm_ptp_lock);

	ret = kvm_arch_ptp_get_घड़ी(&tspec);
	अगर (ret) अणु
		spin_unlock(&kvm_ptp_lock);
		वापस ret;
	पूर्ण

	spin_unlock(&kvm_ptp_lock);

	स_नकल(ts, &tspec, माप(काष्ठा बारpec64));

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_kvm_enable(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info ptp_kvm_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "KVM virtual PTP",
	.max_adj	= 0,
	.n_ext_ts	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfreq	= ptp_kvm_adjfreq,
	.adjसमय	= ptp_kvm_adjसमय,
	.समय_लो64	= ptp_kvm_समय_लो,
	.समय_रखो64	= ptp_kvm_समय_रखो,
	.enable		= ptp_kvm_enable,
	.अ_लोrosststamp = ptp_kvm_अ_लोrosststamp,
पूर्ण;

/* module operations */

अटल काष्ठा kvm_ptp_घड़ी kvm_ptp_घड़ी;

अटल व्योम __निकास ptp_kvm_निकास(व्योम)
अणु
	ptp_घड़ी_unरेजिस्टर(kvm_ptp_घड़ी.ptp_घड़ी);
पूर्ण

अटल पूर्णांक __init ptp_kvm_init(व्योम)
अणु
	दीर्घ ret;

	ret = kvm_arch_ptp_init();
	अगर (ret) अणु
		अगर (ret != -EOPNOTSUPP)
			pr_err("fail to initialize ptp_kvm");
		वापस ret;
	पूर्ण

	kvm_ptp_घड़ी.caps = ptp_kvm_caps;

	kvm_ptp_घड़ी.ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&kvm_ptp_घड़ी.caps, शून्य);

	वापस PTR_ERR_OR_ZERO(kvm_ptp_घड़ी.ptp_घड़ी);
पूर्ण

module_init(ptp_kvm_init);
module_निकास(ptp_kvm_निकास);

MODULE_AUTHOR("Marcelo Tosatti <mtosatti@redhat.com>");
MODULE_DESCRIPTION("PTP clock using KVMCLOCK");
MODULE_LICENSE("GPL");
