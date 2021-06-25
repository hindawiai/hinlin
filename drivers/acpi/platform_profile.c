<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/* Platक्रमm profile sysfs पूर्णांकerface */

#समावेश <linux/acpi.h>
#समावेश <linux/bits.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_profile.h>
#समावेश <linux/sysfs.h>

अटल काष्ठा platक्रमm_profile_handler *cur_profile;
अटल DEFINE_MUTEX(profile_lock);

अटल स्थिर अक्षर * स्थिर profile_names[] = अणु
	[PLATFORM_PROखाता_LOW_POWER] = "low-power",
	[PLATFORM_PROखाता_COOL] = "cool",
	[PLATFORM_PROखाता_QUIET] = "quiet",
	[PLATFORM_PROखाता_BALANCED] = "balanced",
	[PLATFORM_PROखाता_BALANCED_PERFORMANCE] = "balanced-performance",
	[PLATFORM_PROखाता_PERFORMANCE] = "performance",
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(profile_names) == PLATFORM_PROखाता_LAST);

अटल sमाप_प्रकार platक्रमm_profile_choices_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	पूर्णांक len = 0;
	पूर्णांक err, i;

	err = mutex_lock_पूर्णांकerruptible(&profile_lock);
	अगर (err)
		वापस err;

	अगर (!cur_profile) अणु
		mutex_unlock(&profile_lock);
		वापस -ENODEV;
	पूर्ण

	क्रम_each_set_bit(i, cur_profile->choices, PLATFORM_PROखाता_LAST) अणु
		अगर (len == 0)
			len += sysfs_emit_at(buf, len, "%s", profile_names[i]);
		अन्यथा
			len += sysfs_emit_at(buf, len, " %s", profile_names[i]);
	पूर्ण
	len += sysfs_emit_at(buf, len, "\n");
	mutex_unlock(&profile_lock);
	वापस len;
पूर्ण

अटल sमाप_प्रकार platक्रमm_profile_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	क्रमागत platक्रमm_profile_option profile = PLATFORM_PROखाता_BALANCED;
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&profile_lock);
	अगर (err)
		वापस err;

	अगर (!cur_profile) अणु
		mutex_unlock(&profile_lock);
		वापस -ENODEV;
	पूर्ण

	err = cur_profile->profile_get(cur_profile, &profile);
	mutex_unlock(&profile_lock);
	अगर (err)
		वापस err;

	/* Check that profile is valid index */
	अगर (WARN_ON((profile < 0) || (profile >= ARRAY_SIZE(profile_names))))
		वापस -EIO;

	वापस sysfs_emit(buf, "%s\n", profile_names[profile]);
पूर्ण

अटल sमाप_प्रकार platक्रमm_profile_store(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err, i;

	err = mutex_lock_पूर्णांकerruptible(&profile_lock);
	अगर (err)
		वापस err;

	अगर (!cur_profile) अणु
		mutex_unlock(&profile_lock);
		वापस -ENODEV;
	पूर्ण

	/* Scan क्रम a matching profile */
	i = sysfs_match_string(profile_names, buf);
	अगर (i < 0) अणु
		mutex_unlock(&profile_lock);
		वापस -EINVAL;
	पूर्ण

	/* Check that platक्रमm supports this profile choice */
	अगर (!test_bit(i, cur_profile->choices)) अणु
		mutex_unlock(&profile_lock);
		वापस -EOPNOTSUPP;
	पूर्ण

	err = cur_profile->profile_set(cur_profile, i);
	mutex_unlock(&profile_lock);
	अगर (err)
		वापस err;
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(platक्रमm_profile_choices);
अटल DEVICE_ATTR_RW(platक्रमm_profile);

अटल काष्ठा attribute *platक्रमm_profile_attrs[] = अणु
	&dev_attr_platक्रमm_profile_choices.attr,
	&dev_attr_platक्रमm_profile.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group platक्रमm_profile_group = अणु
	.attrs = platक्रमm_profile_attrs
पूर्ण;

व्योम platक्रमm_profile_notअगरy(व्योम)
अणु
	अगर (!cur_profile)
		वापस;
	sysfs_notअगरy(acpi_kobj, शून्य, "platform_profile");
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_profile_notअगरy);

पूर्णांक platक्रमm_profile_रेजिस्टर(काष्ठा platक्रमm_profile_handler *pprof)
अणु
	पूर्णांक err;

	mutex_lock(&profile_lock);
	/* We can only have one active profile */
	अगर (cur_profile) अणु
		mutex_unlock(&profile_lock);
		वापस -EEXIST;
	पूर्ण

	/* Sanity check the profile handler field are set */
	अगर (!pprof || biपंचांगap_empty(pprof->choices, PLATFORM_PROखाता_LAST) ||
		!pprof->profile_set || !pprof->profile_get) अणु
		mutex_unlock(&profile_lock);
		वापस -EINVAL;
	पूर्ण

	err = sysfs_create_group(acpi_kobj, &platक्रमm_profile_group);
	अगर (err) अणु
		mutex_unlock(&profile_lock);
		वापस err;
	पूर्ण

	cur_profile = pprof;
	mutex_unlock(&profile_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_profile_रेजिस्टर);

पूर्णांक platक्रमm_profile_हटाओ(व्योम)
अणु
	sysfs_हटाओ_group(acpi_kobj, &platक्रमm_profile_group);

	mutex_lock(&profile_lock);
	cur_profile = शून्य;
	mutex_unlock(&profile_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(platक्रमm_profile_हटाओ);

MODULE_AUTHOR("Mark Pearson <markpearson@lenovo.com>");
MODULE_LICENSE("GPL");
