<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cooling device driver that activates the processor throttling by
 * programming the TCC Offset रेजिस्टर.
 * Copyright (c) 2021, Intel Corporation.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/thermal.h>
#समावेश <यंत्र/cpu_device_id.h>

#घोषणा TCC_SHIFT 24
#घोषणा TCC_MASK	(0x3fULL<<24)
#घोषणा TCC_PROGRAMMABLE	BIT(30)

अटल काष्ठा thermal_cooling_device *tcc_cdev;

अटल पूर्णांक tcc_get_max_state(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ
			     *state)
अणु
	*state = TCC_MASK >> TCC_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक tcc_offset_update(पूर्णांक tcc)
अणु
	u64 val;
	पूर्णांक err;

	err = rdmsrl_safe(MSR_IA32_TEMPERATURE_TARGET, &val);
	अगर (err)
		वापस err;

	val &= ~TCC_MASK;
	val |= tcc << TCC_SHIFT;

	err = wrmsrl_safe(MSR_IA32_TEMPERATURE_TARGET, val);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक tcc_get_cur_state(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ
			     *state)
अणु
	u64 val;
	पूर्णांक err;

	err = rdmsrl_safe(MSR_IA32_TEMPERATURE_TARGET, &val);
	अगर (err)
		वापस err;

	*state = (val & TCC_MASK) >> TCC_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक tcc_set_cur_state(काष्ठा thermal_cooling_device *cdev, अचिन्हित दीर्घ
			     state)
अणु
	वापस tcc_offset_update(state);
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops tcc_cooling_ops = अणु
	.get_max_state = tcc_get_max_state,
	.get_cur_state = tcc_get_cur_state,
	.set_cur_state = tcc_set_cur_state,
पूर्ण;

अटल स्थिर काष्ठा x86_cpu_id tcc_ids[] __initस्थिर = अणु
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(SKYLAKE_L, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(KABYLAKE_L, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(ICELAKE_L, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(TIGERLAKE_L, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(COMETLAKE, शून्य),
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(x86cpu, tcc_ids);

अटल पूर्णांक __init tcc_cooling_init(व्योम)
अणु
	पूर्णांक ret;
	u64 val;
	स्थिर काष्ठा x86_cpu_id *id;

	पूर्णांक err;

	id = x86_match_cpu(tcc_ids);
	अगर (!id)
		वापस -ENODEV;

	err = rdmsrl_safe(MSR_PLATFORM_INFO, &val);
	अगर (err)
		वापस err;

	अगर (!(val & TCC_PROGRAMMABLE))
		वापस -ENODEV;

	pr_info("Programmable TCC Offset detected\n");

	tcc_cdev =
	    thermal_cooling_device_रेजिस्टर("TCC Offset", शून्य,
					    &tcc_cooling_ops);
	अगर (IS_ERR(tcc_cdev)) अणु
		ret = PTR_ERR(tcc_cdev);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

module_init(tcc_cooling_init)

अटल व्योम __निकास tcc_cooling_निकास(व्योम)
अणु
	thermal_cooling_device_unरेजिस्टर(tcc_cdev);
पूर्ण

module_निकास(tcc_cooling_निकास)

MODULE_DESCRIPTION("TCC offset cooling device Driver");
MODULE_AUTHOR("Zhang Rui <rui.zhang@intel.com>");
MODULE_LICENSE("GPL v2");
