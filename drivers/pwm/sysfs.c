<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A simple sysfs पूर्णांकerface क्रम the generic PWM framework
 *
 * Copyright (C) 2013 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * Based on previous work by Lars Poeschel <poeschel@lemonage.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/pwm.h>

काष्ठा pwm_export अणु
	काष्ठा device child;
	काष्ठा pwm_device *pwm;
	काष्ठा mutex lock;
	काष्ठा pwm_state suspend;
पूर्ण;

अटल काष्ठा pwm_export *child_to_pwm_export(काष्ठा device *child)
अणु
	वापस container_of(child, काष्ठा pwm_export, child);
पूर्ण

अटल काष्ठा pwm_device *child_to_pwm_device(काष्ठा device *child)
अणु
	काष्ठा pwm_export *export = child_to_pwm_export(child);

	वापस export->pwm;
पूर्ण

अटल sमाप_प्रकार period_show(काष्ठा device *child,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	स्थिर काष्ठा pwm_device *pwm = child_to_pwm_device(child);
	काष्ठा pwm_state state;

	pwm_get_state(pwm, &state);

	वापस प्र_लिखो(buf, "%llu\n", state.period);
पूर्ण

अटल sमाप_प्रकार period_store(काष्ठा device *child,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा pwm_export *export = child_to_pwm_export(child);
	काष्ठा pwm_device *pwm = export->pwm;
	काष्ठा pwm_state state;
	u64 val;
	पूर्णांक ret;

	ret = kstrtou64(buf, 0, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&export->lock);
	pwm_get_state(pwm, &state);
	state.period = val;
	ret = pwm_apply_state(pwm, &state);
	mutex_unlock(&export->lock);

	वापस ret ? : size;
पूर्ण

अटल sमाप_प्रकार duty_cycle_show(काष्ठा device *child,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	स्थिर काष्ठा pwm_device *pwm = child_to_pwm_device(child);
	काष्ठा pwm_state state;

	pwm_get_state(pwm, &state);

	वापस प्र_लिखो(buf, "%llu\n", state.duty_cycle);
पूर्ण

अटल sमाप_प्रकार duty_cycle_store(काष्ठा device *child,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा pwm_export *export = child_to_pwm_export(child);
	काष्ठा pwm_device *pwm = export->pwm;
	काष्ठा pwm_state state;
	u64 val;
	पूर्णांक ret;

	ret = kstrtou64(buf, 0, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&export->lock);
	pwm_get_state(pwm, &state);
	state.duty_cycle = val;
	ret = pwm_apply_state(pwm, &state);
	mutex_unlock(&export->lock);

	वापस ret ? : size;
पूर्ण

अटल sमाप_प्रकार enable_show(काष्ठा device *child,
			   काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	स्थिर काष्ठा pwm_device *pwm = child_to_pwm_device(child);
	काष्ठा pwm_state state;

	pwm_get_state(pwm, &state);

	वापस प्र_लिखो(buf, "%d\n", state.enabled);
पूर्ण

अटल sमाप_प्रकार enable_store(काष्ठा device *child,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा pwm_export *export = child_to_pwm_export(child);
	काष्ठा pwm_device *pwm = export->pwm;
	काष्ठा pwm_state state;
	पूर्णांक val, ret;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&export->lock);

	pwm_get_state(pwm, &state);

	चयन (val) अणु
	हाल 0:
		state.enabled = false;
		अवरोध;
	हाल 1:
		state.enabled = true;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	ret = pwm_apply_state(pwm, &state);

unlock:
	mutex_unlock(&export->lock);
	वापस ret ? : size;
पूर्ण

अटल sमाप_प्रकार polarity_show(काष्ठा device *child,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	स्थिर काष्ठा pwm_device *pwm = child_to_pwm_device(child);
	स्थिर अक्षर *polarity = "unknown";
	काष्ठा pwm_state state;

	pwm_get_state(pwm, &state);

	चयन (state.polarity) अणु
	हाल PWM_POLARITY_NORMAL:
		polarity = "normal";
		अवरोध;

	हाल PWM_POLARITY_INVERSED:
		polarity = "inversed";
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", polarity);
पूर्ण

अटल sमाप_प्रकार polarity_store(काष्ठा device *child,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा pwm_export *export = child_to_pwm_export(child);
	काष्ठा pwm_device *pwm = export->pwm;
	क्रमागत pwm_polarity polarity;
	काष्ठा pwm_state state;
	पूर्णांक ret;

	अगर (sysfs_streq(buf, "normal"))
		polarity = PWM_POLARITY_NORMAL;
	अन्यथा अगर (sysfs_streq(buf, "inversed"))
		polarity = PWM_POLARITY_INVERSED;
	अन्यथा
		वापस -EINVAL;

	mutex_lock(&export->lock);
	pwm_get_state(pwm, &state);
	state.polarity = polarity;
	ret = pwm_apply_state(pwm, &state);
	mutex_unlock(&export->lock);

	वापस ret ? : size;
पूर्ण

अटल sमाप_प्रकार capture_show(काष्ठा device *child,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा pwm_device *pwm = child_to_pwm_device(child);
	काष्ठा pwm_capture result;
	पूर्णांक ret;

	ret = pwm_capture(pwm, &result, jअगरfies_to_msecs(HZ));
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%u %u\n", result.period, result.duty_cycle);
पूर्ण

अटल DEVICE_ATTR_RW(period);
अटल DEVICE_ATTR_RW(duty_cycle);
अटल DEVICE_ATTR_RW(enable);
अटल DEVICE_ATTR_RW(polarity);
अटल DEVICE_ATTR_RO(capture);

अटल काष्ठा attribute *pwm_attrs[] = अणु
	&dev_attr_period.attr,
	&dev_attr_duty_cycle.attr,
	&dev_attr_enable.attr,
	&dev_attr_polarity.attr,
	&dev_attr_capture.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(pwm);

अटल व्योम pwm_export_release(काष्ठा device *child)
अणु
	काष्ठा pwm_export *export = child_to_pwm_export(child);

	kमुक्त(export);
पूर्ण

अटल पूर्णांक pwm_export_child(काष्ठा device *parent, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_export *export;
	अक्षर *pwm_prop[2];
	पूर्णांक ret;

	अगर (test_and_set_bit(PWMF_EXPORTED, &pwm->flags))
		वापस -EBUSY;

	export = kzalloc(माप(*export), GFP_KERNEL);
	अगर (!export) अणु
		clear_bit(PWMF_EXPORTED, &pwm->flags);
		वापस -ENOMEM;
	पूर्ण

	export->pwm = pwm;
	mutex_init(&export->lock);

	export->child.release = pwm_export_release;
	export->child.parent = parent;
	export->child.devt = MKDEV(0, 0);
	export->child.groups = pwm_groups;
	dev_set_name(&export->child, "pwm%u", pwm->hwpwm);

	ret = device_रेजिस्टर(&export->child);
	अगर (ret) अणु
		clear_bit(PWMF_EXPORTED, &pwm->flags);
		put_device(&export->child);
		export = शून्य;
		वापस ret;
	पूर्ण
	pwm_prop[0] = kaप्र_लिखो(GFP_KERNEL, "EXPORT=pwm%u", pwm->hwpwm);
	pwm_prop[1] = शून्य;
	kobject_uevent_env(&parent->kobj, KOBJ_CHANGE, pwm_prop);
	kमुक्त(pwm_prop[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_unexport_match(काष्ठा device *child, व्योम *data)
अणु
	वापस child_to_pwm_device(child) == data;
पूर्ण

अटल पूर्णांक pwm_unexport_child(काष्ठा device *parent, काष्ठा pwm_device *pwm)
अणु
	काष्ठा device *child;
	अक्षर *pwm_prop[2];

	अगर (!test_and_clear_bit(PWMF_EXPORTED, &pwm->flags))
		वापस -ENODEV;

	child = device_find_child(parent, pwm, pwm_unexport_match);
	अगर (!child)
		वापस -ENODEV;

	pwm_prop[0] = kaप्र_लिखो(GFP_KERNEL, "UNEXPORT=pwm%u", pwm->hwpwm);
	pwm_prop[1] = शून्य;
	kobject_uevent_env(&parent->kobj, KOBJ_CHANGE, pwm_prop);
	kमुक्त(pwm_prop[0]);

	/* क्रम device_find_child() */
	put_device(child);
	device_unरेजिस्टर(child);
	pwm_put(pwm);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार export_store(काष्ठा device *parent,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा pwm_chip *chip = dev_get_drvdata(parent);
	काष्ठा pwm_device *pwm;
	अचिन्हित पूर्णांक hwpwm;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &hwpwm);
	अगर (ret < 0)
		वापस ret;

	अगर (hwpwm >= chip->npwm)
		वापस -ENODEV;

	pwm = pwm_request_from_chip(chip, hwpwm, "sysfs");
	अगर (IS_ERR(pwm))
		वापस PTR_ERR(pwm);

	ret = pwm_export_child(parent, pwm);
	अगर (ret < 0)
		pwm_put(pwm);

	वापस ret ? : len;
पूर्ण
अटल DEVICE_ATTR_WO(export);

अटल sमाप_प्रकार unexport_store(काष्ठा device *parent,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा pwm_chip *chip = dev_get_drvdata(parent);
	अचिन्हित पूर्णांक hwpwm;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &hwpwm);
	अगर (ret < 0)
		वापस ret;

	अगर (hwpwm >= chip->npwm)
		वापस -ENODEV;

	ret = pwm_unexport_child(parent, &chip->pwms[hwpwm]);

	वापस ret ? : len;
पूर्ण
अटल DEVICE_ATTR_WO(unexport);

अटल sमाप_प्रकार npwm_show(काष्ठा device *parent, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	स्थिर काष्ठा pwm_chip *chip = dev_get_drvdata(parent);

	वापस प्र_लिखो(buf, "%u\n", chip->npwm);
पूर्ण
अटल DEVICE_ATTR_RO(npwm);

अटल काष्ठा attribute *pwm_chip_attrs[] = अणु
	&dev_attr_export.attr,
	&dev_attr_unexport.attr,
	&dev_attr_npwm.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(pwm_chip);

/* takes export->lock on success */
अटल काष्ठा pwm_export *pwm_class_get_state(काष्ठा device *parent,
					      काष्ठा pwm_device *pwm,
					      काष्ठा pwm_state *state)
अणु
	काष्ठा device *child;
	काष्ठा pwm_export *export;

	अगर (!test_bit(PWMF_EXPORTED, &pwm->flags))
		वापस शून्य;

	child = device_find_child(parent, pwm, pwm_unexport_match);
	अगर (!child)
		वापस शून्य;

	export = child_to_pwm_export(child);
	put_device(child);	/* क्रम device_find_child() */

	mutex_lock(&export->lock);
	pwm_get_state(pwm, state);

	वापस export;
पूर्ण

अटल पूर्णांक pwm_class_apply_state(काष्ठा pwm_export *export,
				 काष्ठा pwm_device *pwm,
				 काष्ठा pwm_state *state)
अणु
	पूर्णांक ret = pwm_apply_state(pwm, state);

	/* release lock taken in pwm_class_get_state */
	mutex_unlock(&export->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pwm_class_resume_npwm(काष्ठा device *parent, अचिन्हित पूर्णांक npwm)
अणु
	काष्ठा pwm_chip *chip = dev_get_drvdata(parent);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < npwm; i++) अणु
		काष्ठा pwm_device *pwm = &chip->pwms[i];
		काष्ठा pwm_state state;
		काष्ठा pwm_export *export;

		export = pwm_class_get_state(parent, pwm, &state);
		अगर (!export)
			जारी;

		state.enabled = export->suspend.enabled;
		ret = pwm_class_apply_state(export, pwm, &state);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused pwm_class_suspend(काष्ठा device *parent)
अणु
	काष्ठा pwm_chip *chip = dev_get_drvdata(parent);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < chip->npwm; i++) अणु
		काष्ठा pwm_device *pwm = &chip->pwms[i];
		काष्ठा pwm_state state;
		काष्ठा pwm_export *export;

		export = pwm_class_get_state(parent, pwm, &state);
		अगर (!export)
			जारी;

		export->suspend = state;
		state.enabled = false;
		ret = pwm_class_apply_state(export, pwm, &state);
		अगर (ret < 0) अणु
			/*
			 * roll back the PWM devices that were disabled by
			 * this suspend function.
			 */
			pwm_class_resume_npwm(parent, i);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused pwm_class_resume(काष्ठा device *parent)
अणु
	काष्ठा pwm_chip *chip = dev_get_drvdata(parent);

	वापस pwm_class_resume_npwm(parent, chip->npwm);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pwm_class_pm_ops, pwm_class_suspend, pwm_class_resume);

अटल काष्ठा class pwm_class = अणु
	.name = "pwm",
	.owner = THIS_MODULE,
	.dev_groups = pwm_chip_groups,
	.pm = &pwm_class_pm_ops,
पूर्ण;

अटल पूर्णांक pwmchip_sysfs_match(काष्ठा device *parent, स्थिर व्योम *data)
अणु
	वापस dev_get_drvdata(parent) == data;
पूर्ण

व्योम pwmchip_sysfs_export(काष्ठा pwm_chip *chip)
अणु
	काष्ठा device *parent;

	/*
	 * If device_create() fails the pwm_chip is still usable by
	 * the kernel it's just not exported.
	 */
	parent = device_create(&pwm_class, chip->dev, MKDEV(0, 0), chip,
			       "pwmchip%d", chip->base);
	अगर (IS_ERR(parent)) अणु
		dev_warn(chip->dev,
			 "device_create failed for pwm_chip sysfs export\n");
	पूर्ण
पूर्ण

व्योम pwmchip_sysfs_unexport(काष्ठा pwm_chip *chip)
अणु
	काष्ठा device *parent;
	अचिन्हित पूर्णांक i;

	parent = class_find_device(&pwm_class, शून्य, chip,
				   pwmchip_sysfs_match);
	अगर (!parent)
		वापस;

	क्रम (i = 0; i < chip->npwm; i++) अणु
		काष्ठा pwm_device *pwm = &chip->pwms[i];

		अगर (test_bit(PWMF_EXPORTED, &pwm->flags))
			pwm_unexport_child(parent, pwm);
	पूर्ण

	put_device(parent);
	device_unरेजिस्टर(parent);
पूर्ण

अटल पूर्णांक __init pwm_sysfs_init(व्योम)
अणु
	वापस class_रेजिस्टर(&pwm_class);
पूर्ण
subsys_initcall(pwm_sysfs_init);
