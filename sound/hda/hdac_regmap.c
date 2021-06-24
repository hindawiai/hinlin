<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regmap support क्रम HD-audio verbs
 *
 * A भव रेजिस्टर is translated to one or more hda verbs क्रम ग_लिखो,
 * vice versa क्रम पढ़ो.
 *
 * A few limitations:
 * - Provided क्रम not all verbs but only subset standard non-अस्थिर verbs.
 * - For पढ़ोing, only AC_VERB_GET_* variants can be used.
 * - For writing, mapped to the *corresponding* AC_VERB_SET_* variants,
 *   so can't handle asymmetric verbs क्रम पढ़ो and ग_लिखो
 */

#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/export.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/core.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_regmap.h>
#समावेश "local.h"

अटल पूर्णांक codec_pm_lock(काष्ठा hdac_device *codec)
अणु
	वापस snd_hdac_keep_घातer_up(codec);
पूर्ण

अटल व्योम codec_pm_unlock(काष्ठा hdac_device *codec, पूर्णांक lock)
अणु
	अगर (lock == 1)
		snd_hdac_घातer_करोwn_pm(codec);
पूर्ण

#घोषणा get_verb(reg)	(((reg) >> 8) & 0xfff)

अटल bool hda_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा hdac_device *codec = dev_to_hdac_dev(dev);
	अचिन्हित पूर्णांक verb = get_verb(reg);

	चयन (verb) अणु
	हाल AC_VERB_GET_PROC_COEF:
		वापस !codec->cache_coef;
	हाल AC_VERB_GET_COEF_INDEX:
	हाल AC_VERB_GET_PROC_STATE:
	हाल AC_VERB_GET_POWER_STATE:
	हाल AC_VERB_GET_PIN_SENSE:
	हाल AC_VERB_GET_HDMI_DIP_SIZE:
	हाल AC_VERB_GET_HDMI_ELDD:
	हाल AC_VERB_GET_HDMI_DIP_INDEX:
	हाल AC_VERB_GET_HDMI_DIP_DATA:
	हाल AC_VERB_GET_HDMI_DIP_XMIT:
	हाल AC_VERB_GET_HDMI_CP_CTRL:
	हाल AC_VERB_GET_HDMI_CHAN_SLOT:
	हाल AC_VERB_GET_DEVICE_SEL:
	हाल AC_VERB_GET_DEVICE_LIST:	/* पढ़ो-only अस्थिर */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool hda_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा hdac_device *codec = dev_to_hdac_dev(dev);
	अचिन्हित पूर्णांक verb = get_verb(reg);
	स्थिर अचिन्हित पूर्णांक *v;
	पूर्णांक i;

	snd_array_क्रम_each(&codec->venकरोr_verbs, i, v) अणु
		अगर (verb == *v)
			वापस true;
	पूर्ण

	अगर (codec->caps_overwriting)
		वापस true;

	चयन (verb & 0xf00) अणु
	हाल AC_VERB_GET_STREAM_FORMAT:
	हाल AC_VERB_GET_AMP_GAIN_MUTE:
		वापस true;
	हाल AC_VERB_GET_PROC_COEF:
		वापस codec->cache_coef;
	हाल 0xf00:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	चयन (verb) अणु
	हाल AC_VERB_GET_CONNECT_SEL:
	हाल AC_VERB_GET_SDI_SELECT:
	हाल AC_VERB_GET_PIN_WIDGET_CONTROL:
	हाल AC_VERB_GET_UNSOLICITED_RESPONSE: /* only as SET_UNSOLICITED_ENABLE */
	हाल AC_VERB_GET_BEEP_CONTROL:
	हाल AC_VERB_GET_EAPD_BTLENABLE:
	हाल AC_VERB_GET_DIGI_CONVERT_1:
	हाल AC_VERB_GET_DIGI_CONVERT_2: /* only क्रम beep control */
	हाल AC_VERB_GET_VOLUME_KNOB_CONTROL:
	हाल AC_VERB_GET_GPIO_MASK:
	हाल AC_VERB_GET_GPIO_सूचीECTION:
	हाल AC_VERB_GET_GPIO_DATA: /* not क्रम अस्थिर पढ़ो */
	हाल AC_VERB_GET_GPIO_WAKE_MASK:
	हाल AC_VERB_GET_GPIO_UNSOLICITED_RSP_MASK:
	हाल AC_VERB_GET_GPIO_STICKY_MASK:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool hda_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा hdac_device *codec = dev_to_hdac_dev(dev);
	अचिन्हित पूर्णांक verb = get_verb(reg);

	अगर (codec->caps_overwriting)
		वापस true;

	चयन (verb) अणु
	हाल AC_VERB_PARAMETERS:
	हाल AC_VERB_GET_CONNECT_LIST:
	हाल AC_VERB_GET_SUBSYSTEM_ID:
		वापस true;
	/* below are basically writable, but disabled क्रम reducing unnecessary
	 * ग_लिखोs at sync
	 */
	हाल AC_VERB_GET_CONFIG_DEFAULT: /* usually just पढ़ो */
	हाल AC_VERB_GET_CONV: /* managed in PCM code */
	हाल AC_VERB_GET_CVT_CHAN_COUNT: /* managed in HDMI CA code */
		वापस true;
	पूर्ण

	वापस hda_ग_लिखोable_reg(dev, reg);
पूर्ण

/*
 * Stereo amp pseuकरो रेजिस्टर:
 * क्रम making easier to handle the stereo volume control, we provide a
 * fake रेजिस्टर to deal both left and right channels by a single
 * (pseuकरो) रेजिस्टर access.  A verb consisting of SET_AMP_GAIN with
 * *both* SET_LEFT and SET_RIGHT bits takes a 16bit value, the lower 8bit
 * क्रम the left and the upper 8bit क्रम the right channel.
 */
अटल bool is_stereo_amp_verb(अचिन्हित पूर्णांक reg)
अणु
	अगर (((reg >> 8) & 0x700) != AC_VERB_SET_AMP_GAIN_MUTE)
		वापस false;
	वापस (reg & (AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT)) ==
		(AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT);
पूर्ण

/* पढ़ो a pseuकरो stereo amp रेजिस्टर (16bit left+right) */
अटल पूर्णांक hda_reg_पढ़ो_stereo_amp(काष्ठा hdac_device *codec,
				   अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक left, right;
	पूर्णांक err;

	reg &= ~(AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT);
	err = snd_hdac_exec_verb(codec, reg | AC_AMP_GET_LEFT, 0, &left);
	अगर (err < 0)
		वापस err;
	err = snd_hdac_exec_verb(codec, reg | AC_AMP_GET_RIGHT, 0, &right);
	अगर (err < 0)
		वापस err;
	*val = left | (right << 8);
	वापस 0;
पूर्ण

/* ग_लिखो a pseuकरो stereo amp रेजिस्टर (16bit left+right) */
अटल पूर्णांक hda_reg_ग_लिखो_stereo_amp(काष्ठा hdac_device *codec,
				    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक verb, left, right;

	verb = AC_VERB_SET_AMP_GAIN_MUTE << 8;
	अगर (reg & AC_AMP_GET_OUTPUT)
		verb |= AC_AMP_SET_OUTPUT;
	अन्यथा
		verb |= AC_AMP_SET_INPUT | ((reg & 0xf) << 8);
	reg = (reg & ~0xfffff) | verb;

	left = val & 0xff;
	right = (val >> 8) & 0xff;
	अगर (left == right) अणु
		reg |= AC_AMP_SET_LEFT | AC_AMP_SET_RIGHT;
		वापस snd_hdac_exec_verb(codec, reg | left, 0, शून्य);
	पूर्ण

	err = snd_hdac_exec_verb(codec, reg | AC_AMP_SET_LEFT | left, 0, शून्य);
	अगर (err < 0)
		वापस err;
	err = snd_hdac_exec_verb(codec, reg | AC_AMP_SET_RIGHT | right, 0, शून्य);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

/* पढ़ो a pseuकरो coef रेजिस्टर (16bit) */
अटल पूर्णांक hda_reg_पढ़ो_coef(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक verb;
	पूर्णांक err;

	अगर (!codec->cache_coef)
		वापस -EINVAL;
	/* LSB 8bit = coef index */
	verb = (reg & ~0xfff00) | (AC_VERB_SET_COEF_INDEX << 8);
	err = snd_hdac_exec_verb(codec, verb, 0, शून्य);
	अगर (err < 0)
		वापस err;
	verb = (reg & ~0xfffff) | (AC_VERB_GET_COEF_INDEX << 8);
	वापस snd_hdac_exec_verb(codec, verb, 0, val);
पूर्ण

/* ग_लिखो a pseuकरो coef रेजिस्टर (16bit) */
अटल पूर्णांक hda_reg_ग_लिखो_coef(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक verb;
	पूर्णांक err;

	अगर (!codec->cache_coef)
		वापस -EINVAL;
	/* LSB 8bit = coef index */
	verb = (reg & ~0xfff00) | (AC_VERB_SET_COEF_INDEX << 8);
	err = snd_hdac_exec_verb(codec, verb, 0, शून्य);
	अगर (err < 0)
		वापस err;
	verb = (reg & ~0xfffff) | (AC_VERB_GET_COEF_INDEX << 8) |
		(val & 0xffff);
	वापस snd_hdac_exec_verb(codec, verb, 0, शून्य);
पूर्ण

अटल पूर्णांक hda_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा hdac_device *codec = context;
	पूर्णांक verb = get_verb(reg);
	पूर्णांक err;
	पूर्णांक pm_lock = 0;

	अगर (verb != AC_VERB_GET_POWER_STATE) अणु
		pm_lock = codec_pm_lock(codec);
		अगर (pm_lock < 0)
			वापस -EAGAIN;
	पूर्ण
	reg |= (codec->addr << 28);
	अगर (is_stereo_amp_verb(reg)) अणु
		err = hda_reg_पढ़ो_stereo_amp(codec, reg, val);
		जाओ out;
	पूर्ण
	अगर (verb == AC_VERB_GET_PROC_COEF) अणु
		err = hda_reg_पढ़ो_coef(codec, reg, val);
		जाओ out;
	पूर्ण
	अगर ((verb & 0x700) == AC_VERB_SET_AMP_GAIN_MUTE)
		reg &= ~AC_AMP_FAKE_MUTE;

	err = snd_hdac_exec_verb(codec, reg, 0, val);
	अगर (err < 0)
		जाओ out;
	/* special handling क्रम asymmetric पढ़ोs */
	अगर (verb == AC_VERB_GET_POWER_STATE) अणु
		अगर (*val & AC_PWRST_ERROR)
			*val = -1;
		अन्यथा /* take only the actual state */
			*val = (*val >> 4) & 0x0f;
	पूर्ण
 out:
	codec_pm_unlock(codec, pm_lock);
	वापस err;
पूर्ण

अटल पूर्णांक hda_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा hdac_device *codec = context;
	अचिन्हित पूर्णांक verb;
	पूर्णांक i, bytes, err;
	पूर्णांक pm_lock = 0;

	अगर (codec->caps_overwriting)
		वापस 0;

	reg &= ~0x00080000U; /* drop GET bit */
	reg |= (codec->addr << 28);
	verb = get_verb(reg);

	अगर (verb != AC_VERB_SET_POWER_STATE) अणु
		pm_lock = codec_pm_lock(codec);
		अगर (pm_lock < 0)
			वापस codec->lazy_cache ? 0 : -EAGAIN;
	पूर्ण

	अगर (is_stereo_amp_verb(reg)) अणु
		err = hda_reg_ग_लिखो_stereo_amp(codec, reg, val);
		जाओ out;
	पूर्ण

	अगर (verb == AC_VERB_SET_PROC_COEF) अणु
		err = hda_reg_ग_लिखो_coef(codec, reg, val);
		जाओ out;
	पूर्ण

	चयन (verb & 0xf00) अणु
	हाल AC_VERB_SET_AMP_GAIN_MUTE:
		अगर ((reg & AC_AMP_FAKE_MUTE) && (val & AC_AMP_MUTE))
			val = 0;
		verb = AC_VERB_SET_AMP_GAIN_MUTE;
		अगर (reg & AC_AMP_GET_LEFT)
			verb |= AC_AMP_SET_LEFT >> 8;
		अन्यथा
			verb |= AC_AMP_SET_RIGHT >> 8;
		अगर (reg & AC_AMP_GET_OUTPUT) अणु
			verb |= AC_AMP_SET_OUTPUT >> 8;
		पूर्ण अन्यथा अणु
			verb |= AC_AMP_SET_INPUT >> 8;
			verb |= reg & 0xf;
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (verb) अणु
	हाल AC_VERB_SET_DIGI_CONVERT_1:
		bytes = 2;
		अवरोध;
	हाल AC_VERB_SET_CONFIG_DEFAULT_BYTES_0:
		bytes = 4;
		अवरोध;
	शेष:
		bytes = 1;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < bytes; i++) अणु
		reg &= ~0xfffff;
		reg |= (verb + i) << 8 | ((val >> (8 * i)) & 0xff);
		err = snd_hdac_exec_verb(codec, reg, 0, शून्य);
		अगर (err < 0)
			जाओ out;
	पूर्ण

 out:
	codec_pm_unlock(codec, pm_lock);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा regmap_config hda_regmap_cfg = अणु
	.name = "hdaudio",
	.reg_bits = 32,
	.val_bits = 32,
	.max_रेजिस्टर = 0xfffffff,
	.ग_लिखोable_reg = hda_ग_लिखोable_reg,
	.पढ़ोable_reg = hda_पढ़ोable_reg,
	.अस्थिर_reg = hda_अस्थिर_reg,
	.cache_type = REGCACHE_RBTREE,
	.reg_पढ़ो = hda_reg_पढ़ो,
	.reg_ग_लिखो = hda_reg_ग_लिखो,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.disable_locking = true,
पूर्ण;

/**
 * snd_hdac_regmap_init - Initialize regmap क्रम HDA रेजिस्टर accesses
 * @codec: the codec object
 *
 * Returns zero क्रम success or a negative error code.
 */
पूर्णांक snd_hdac_regmap_init(काष्ठा hdac_device *codec)
अणु
	काष्ठा regmap *regmap;

	regmap = regmap_init(&codec->dev, शून्य, codec, &hda_regmap_cfg);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);
	codec->regmap = regmap;
	snd_array_init(&codec->venकरोr_verbs, माप(अचिन्हित पूर्णांक), 8);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_regmap_init);

/**
 * snd_hdac_regmap_निकास - Release the regmap from HDA codec
 * @codec: the codec object
 */
व्योम snd_hdac_regmap_निकास(काष्ठा hdac_device *codec)
अणु
	अगर (codec->regmap) अणु
		regmap_निकास(codec->regmap);
		codec->regmap = शून्य;
		snd_array_मुक्त(&codec->venकरोr_verbs);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_regmap_निकास);

/**
 * snd_hdac_regmap_add_venकरोr_verb - add a venकरोr-specअगरic verb to regmap
 * @codec: the codec object
 * @verb: verb to allow accessing via regmap
 *
 * Returns zero क्रम success or a negative error code.
 */
पूर्णांक snd_hdac_regmap_add_venकरोr_verb(काष्ठा hdac_device *codec,
				    अचिन्हित पूर्णांक verb)
अणु
	अचिन्हित पूर्णांक *p = snd_array_new(&codec->venकरोr_verbs);

	अगर (!p)
		वापस -ENOMEM;
	*p = verb | 0x800; /* set GET bit */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_regmap_add_venकरोr_verb);

/*
 * helper functions
 */

/* ग_लिखो a pseuकरो-रेजिस्टर value (w/o घातer sequence) */
अटल पूर्णांक reg_raw_ग_लिखो(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			 अचिन्हित पूर्णांक val)
अणु
	पूर्णांक err;

	mutex_lock(&codec->regmap_lock);
	अगर (!codec->regmap)
		err = hda_reg_ग_लिखो(codec, reg, val);
	अन्यथा
		err = regmap_ग_लिखो(codec->regmap, reg, val);
	mutex_unlock(&codec->regmap_lock);
	वापस err;
पूर्ण

/* a helper macro to call @func_call; retry with घातer-up अगर failed */
#घोषणा CALL_RAW_FUNC(codec, func_call)				\
	(अणु							\
		पूर्णांक _err = func_call;				\
		अगर (_err == -EAGAIN) अणु				\
			_err = snd_hdac_घातer_up_pm(codec);	\
			अगर (_err >= 0)				\
				_err = func_call;		\
			snd_hdac_घातer_करोwn_pm(codec);		\
		पूर्ण						\
		_err;पूर्ण)

/**
 * snd_hdac_regmap_ग_लिखो_raw - ग_लिखो a pseuकरो रेजिस्टर with घातer mgmt
 * @codec: the codec object
 * @reg: pseuकरो रेजिस्टर
 * @val: value to ग_लिखो
 *
 * Returns zero अगर successful or a negative error code.
 */
पूर्णांक snd_hdac_regmap_ग_लिखो_raw(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक val)
अणु
	वापस CALL_RAW_FUNC(codec, reg_raw_ग_लिखो(codec, reg, val));
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_regmap_ग_लिखो_raw);

अटल पूर्णांक reg_raw_पढ़ो(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			अचिन्हित पूर्णांक *val, bool uncached)
अणु
	पूर्णांक err;

	mutex_lock(&codec->regmap_lock);
	अगर (uncached || !codec->regmap)
		err = hda_reg_पढ़ो(codec, reg, val);
	अन्यथा
		err = regmap_पढ़ो(codec->regmap, reg, val);
	mutex_unlock(&codec->regmap_lock);
	वापस err;
पूर्ण

अटल पूर्णांक __snd_hdac_regmap_पढ़ो_raw(काष्ठा hdac_device *codec,
				      अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val,
				      bool uncached)
अणु
	वापस CALL_RAW_FUNC(codec, reg_raw_पढ़ो(codec, reg, val, uncached));
पूर्ण

/**
 * snd_hdac_regmap_पढ़ो_raw - पढ़ो a pseuकरो रेजिस्टर with घातer mgmt
 * @codec: the codec object
 * @reg: pseuकरो रेजिस्टर
 * @val: poपूर्णांकer to store the पढ़ो value
 *
 * Returns zero अगर successful or a negative error code.
 */
पूर्णांक snd_hdac_regmap_पढ़ो_raw(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक *val)
अणु
	वापस __snd_hdac_regmap_पढ़ो_raw(codec, reg, val, false);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_regmap_पढ़ो_raw);

/* Works like snd_hdac_regmap_पढ़ो_raw(), but this करोesn't पढ़ो from the
 * cache but always via hda verbs.
 */
पूर्णांक snd_hdac_regmap_पढ़ो_raw_uncached(काष्ठा hdac_device *codec,
				      अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	वापस __snd_hdac_regmap_पढ़ो_raw(codec, reg, val, true);
पूर्ण

अटल पूर्णांक reg_raw_update(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक orig;
	bool change;
	पूर्णांक err;

	mutex_lock(&codec->regmap_lock);
	अगर (codec->regmap) अणु
		err = regmap_update_bits_check(codec->regmap, reg, mask, val,
					       &change);
		अगर (!err)
			err = change ? 1 : 0;
	पूर्ण अन्यथा अणु
		err = hda_reg_पढ़ो(codec, reg, &orig);
		अगर (!err) अणु
			val &= mask;
			val |= orig & ~mask;
			अगर (val != orig) अणु
				err = hda_reg_ग_लिखो(codec, reg, val);
				अगर (!err)
					err = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&codec->regmap_lock);
	वापस err;
पूर्ण

/**
 * snd_hdac_regmap_update_raw - update a pseuकरो रेजिस्टर with घातer mgmt
 * @codec: the codec object
 * @reg: pseuकरो रेजिस्टर
 * @mask: bit mask to update
 * @val: value to update
 *
 * Returns zero अगर successful or a negative error code.
 */
पूर्णांक snd_hdac_regmap_update_raw(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	वापस CALL_RAW_FUNC(codec, reg_raw_update(codec, reg, mask, val));
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_regmap_update_raw);

अटल पूर्णांक reg_raw_update_once(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक orig;
	पूर्णांक err;

	अगर (!codec->regmap)
		वापस reg_raw_update(codec, reg, mask, val);

	mutex_lock(&codec->regmap_lock);
	regcache_cache_only(codec->regmap, true);
	err = regmap_पढ़ो(codec->regmap, reg, &orig);
	regcache_cache_only(codec->regmap, false);
	अगर (err < 0)
		err = regmap_update_bits(codec->regmap, reg, mask, val);
	mutex_unlock(&codec->regmap_lock);
	वापस err;
पूर्ण

/**
 * snd_hdac_regmap_update_raw_once - initialize the रेजिस्टर value only once
 * @codec: the codec object
 * @reg: pseuकरो रेजिस्टर
 * @mask: bit mask to update
 * @val: value to update
 *
 * Perक्रमms the update of the रेजिस्टर bits only once when the रेजिस्टर
 * hasn't been initialized yet.  Used in HD-audio legacy driver.
 * Returns zero अगर successful or a negative error code
 */
पूर्णांक snd_hdac_regmap_update_raw_once(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	वापस CALL_RAW_FUNC(codec, reg_raw_update_once(codec, reg, mask, val));
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_regmap_update_raw_once);

/**
 * snd_hdac_regmap_sync - sync out the cached values क्रम PM resume
 * @codec: the codec object
 */
व्योम snd_hdac_regmap_sync(काष्ठा hdac_device *codec)
अणु
	अगर (codec->regmap) अणु
		mutex_lock(&codec->regmap_lock);
		regcache_sync(codec->regmap);
		mutex_unlock(&codec->regmap_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_regmap_sync);
