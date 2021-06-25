<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/pci.h>

#समावेश "ath5k.h"
#समावेश "reg.h"

#घोषणा SIMPLE_SHOW_STORE(name, get, set)				\
अटल sमाप_प्रकार ath5k_attr_show_##name(काष्ठा device *dev,		\
			काष्ठा device_attribute *attr,			\
			अक्षर *buf)					\
अणु									\
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(dev);			\
	काष्ठा ath5k_hw *ah = hw->priv;				\
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", get);			\
पूर्ण									\
									\
अटल sमाप_प्रकार ath5k_attr_store_##name(काष्ठा device *dev,		\
			काष्ठा device_attribute *attr,			\
			स्थिर अक्षर *buf, माप_प्रकार count)			\
अणु									\
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(dev);			\
	काष्ठा ath5k_hw *ah = hw->priv;				\
	पूर्णांक val, ret;							\
									\
	ret = kstrtoपूर्णांक(buf, 10, &val);					\
	अगर (ret < 0)							\
		वापस ret;						\
	set(ah, val);						\
	वापस count;							\
पूर्ण									\
अटल DEVICE_ATTR(name, 0644,						\
		   ath5k_attr_show_##name, ath5k_attr_store_##name)

#घोषणा SIMPLE_SHOW(name, get)						\
अटल sमाप_प्रकार ath5k_attr_show_##name(काष्ठा device *dev,		\
			काष्ठा device_attribute *attr,			\
			अक्षर *buf)					\
अणु									\
	काष्ठा ieee80211_hw *hw = dev_get_drvdata(dev);			\
	काष्ठा ath5k_hw *ah = hw->priv;				\
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", get);			\
पूर्ण									\
अटल DEVICE_ATTR(name, 0444, ath5k_attr_show_##name, शून्य)

/*** ANI ***/

SIMPLE_SHOW_STORE(ani_mode, ah->ani_state.ani_mode, ath5k_ani_init);
SIMPLE_SHOW_STORE(noise_immunity_level, ah->ani_state.noise_imm_level,
			ath5k_ani_set_noise_immunity_level);
SIMPLE_SHOW_STORE(spur_level, ah->ani_state.spur_level,
			ath5k_ani_set_spur_immunity_level);
SIMPLE_SHOW_STORE(firstep_level, ah->ani_state.firstep_level,
			ath5k_ani_set_firstep_level);
SIMPLE_SHOW_STORE(ofdm_weak_संकेत_detection, ah->ani_state.ofdm_weak_sig,
			ath5k_ani_set_ofdm_weak_संकेत_detection);
SIMPLE_SHOW_STORE(cck_weak_संकेत_detection, ah->ani_state.cck_weak_sig,
			ath5k_ani_set_cck_weak_संकेत_detection);
SIMPLE_SHOW(spur_level_max, ah->ani_state.max_spur_level);

अटल sमाप_प्रकार ath5k_attr_show_noise_immunity_level_max(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ATH5K_ANI_MAX_NOISE_IMM_LVL);
पूर्ण
अटल DEVICE_ATTR(noise_immunity_level_max, 0444,
		   ath5k_attr_show_noise_immunity_level_max, शून्य);

अटल sमाप_प्रकार ath5k_attr_show_firstep_level_max(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ATH5K_ANI_MAX_FIRSTEP_LVL);
पूर्ण
अटल DEVICE_ATTR(firstep_level_max, 0444,
		   ath5k_attr_show_firstep_level_max, शून्य);

अटल काष्ठा attribute *ath5k_sysfs_entries_ani[] = अणु
	&dev_attr_ani_mode.attr,
	&dev_attr_noise_immunity_level.attr,
	&dev_attr_spur_level.attr,
	&dev_attr_firstep_level.attr,
	&dev_attr_ofdm_weak_संकेत_detection.attr,
	&dev_attr_cck_weak_संकेत_detection.attr,
	&dev_attr_noise_immunity_level_max.attr,
	&dev_attr_spur_level_max.attr,
	&dev_attr_firstep_level_max.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group ath5k_attribute_group_ani = अणु
	.name = "ani",
	.attrs = ath5k_sysfs_entries_ani,
पूर्ण;


/*** रेजिस्टर / unरेजिस्टर ***/

पूर्णांक
ath5k_sysfs_रेजिस्टर(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा device *dev = ah->dev;
	पूर्णांक err;

	err = sysfs_create_group(&dev->kobj, &ath5k_attribute_group_ani);
	अगर (err) अणु
		ATH5K_ERR(ah, "failed to create sysfs group\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
ath5k_sysfs_unरेजिस्टर(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा device *dev = ah->dev;

	sysfs_हटाओ_group(&dev->kobj, &ath5k_attribute_group_ani);
पूर्ण
