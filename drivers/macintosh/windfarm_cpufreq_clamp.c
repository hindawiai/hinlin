<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>

#समावेश <यंत्र/prom.h>

#समावेश "windfarm.h"

#घोषणा VERSION "0.3"

अटल पूर्णांक clamped;
अटल काष्ठा wf_control *clamp_control;
अटल काष्ठा freq_qos_request qos_req;
अटल अचिन्हित पूर्णांक min_freq, max_freq;

अटल पूर्णांक clamp_set(काष्ठा wf_control *ct, s32 value)
अणु
	अचिन्हित पूर्णांक freq;

	अगर (value) अणु
		freq = min_freq;
		prपूर्णांकk(KERN_INFO "windfarm: Clamping CPU frequency to "
		       "minimum !\n");
	पूर्ण अन्यथा अणु
		freq = max_freq;
		prपूर्णांकk(KERN_INFO "windfarm: CPU frequency unclamped !\n");
	पूर्ण
	clamped = value;

	वापस freq_qos_update_request(&qos_req, freq);
पूर्ण

अटल पूर्णांक clamp_get(काष्ठा wf_control *ct, s32 *value)
अणु
	*value = clamped;
	वापस 0;
पूर्ण

अटल s32 clamp_min(काष्ठा wf_control *ct)
अणु
	वापस 0;
पूर्ण

अटल s32 clamp_max(काष्ठा wf_control *ct)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा wf_control_ops clamp_ops = अणु
	.set_value	= clamp_set,
	.get_value	= clamp_get,
	.get_min	= clamp_min,
	.get_max	= clamp_max,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init wf_cpufreq_clamp_init(व्योम)
अणु
	काष्ठा cpufreq_policy *policy;
	काष्ठा wf_control *clamp;
	काष्ठा device *dev;
	पूर्णांक ret;

	policy = cpufreq_cpu_get(0);
	अगर (!policy) अणु
		pr_warn("%s: cpufreq policy not found cpu0\n", __func__);
		वापस -EPROBE_DEFER;
	पूर्ण

	min_freq = policy->cpuinfo.min_freq;
	max_freq = policy->cpuinfo.max_freq;

	ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs, &qos_req, FREQ_QOS_MAX,
				   max_freq);

	cpufreq_cpu_put(policy);

	अगर (ret < 0) अणु
		pr_err("%s: Failed to add freq constraint (%d)\n", __func__,
		       ret);
		वापस ret;
	पूर्ण

	dev = get_cpu_device(0);
	अगर (unlikely(!dev)) अणु
		pr_warn("%s: No cpu device for cpu0\n", __func__);
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	clamp = kदो_स्मृति(माप(काष्ठा wf_control), GFP_KERNEL);
	अगर (clamp == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	clamp->ops = &clamp_ops;
	clamp->name = "cpufreq-clamp";
	ret = wf_रेजिस्टर_control(clamp);
	अगर (ret)
		जाओ मुक्त;

	clamp_control = clamp;
	वापस 0;

 मुक्त:
	kमुक्त(clamp);
 fail:
	freq_qos_हटाओ_request(&qos_req);
	वापस ret;
पूर्ण

अटल व्योम __निकास wf_cpufreq_clamp_निकास(व्योम)
अणु
	अगर (clamp_control) अणु
		wf_unरेजिस्टर_control(clamp_control);
		freq_qos_हटाओ_request(&qos_req);
	पूर्ण
पूर्ण


module_init(wf_cpufreq_clamp_init);
module_निकास(wf_cpufreq_clamp_निकास);

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("CPU frequency clamp for PowerMacs thermal control");
MODULE_LICENSE("GPL");

