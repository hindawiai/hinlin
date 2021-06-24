<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sysfs पूर्णांकerface क्रम HD-audio codec
 *
 * Copyright (c) 2014 Takashi Iwai <tiwai@suse.de>
 *
 * split from hda_hwdep.c
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/mutex.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/hda_codec.h>
#समावेश "hda_local.h"
#समावेश <sound/hda_hwdep.h>
#समावेश <sound/minors.h>

/* hपूर्णांक string pair */
काष्ठा hda_hपूर्णांक अणु
	स्थिर अक्षर *key;
	स्थिर अक्षर *val;	/* contained in the same alloc as key */
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल sमाप_प्रकार घातer_on_acct_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	snd_hda_update_घातer_acct(codec);
	वापस प्र_लिखो(buf, "%u\n", jअगरfies_to_msecs(codec->घातer_on_acct));
पूर्ण

अटल sमाप_प्रकार घातer_off_acct_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	snd_hda_update_घातer_acct(codec);
	वापस प्र_लिखो(buf, "%u\n", jअगरfies_to_msecs(codec->घातer_off_acct));
पूर्ण

अटल DEVICE_ATTR_RO(घातer_on_acct);
अटल DEVICE_ATTR_RO(घातer_off_acct);
#पूर्ण_अगर /* CONFIG_PM */

#घोषणा CODEC_INFO_SHOW(type, field)				\
अटल sमाप_प्रकार type##_show(काष्ठा device *dev,			\
			   काष्ठा device_attribute *attr,	\
			   अक्षर *buf)				\
अणु								\
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);		\
	वापस प्र_लिखो(buf, "0x%x\n", codec->field);		\
पूर्ण

#घोषणा CODEC_INFO_STR_SHOW(type, field)			\
अटल sमाप_प्रकार type##_show(काष्ठा device *dev,			\
			     काष्ठा device_attribute *attr,	\
					अक्षर *buf)		\
अणु								\
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);		\
	वापस प्र_लिखो(buf, "%s\n",				\
		       codec->field ? codec->field : "");	\
पूर्ण

CODEC_INFO_SHOW(venकरोr_id, core.venकरोr_id);
CODEC_INFO_SHOW(subप्रणाली_id, core.subप्रणाली_id);
CODEC_INFO_SHOW(revision_id, core.revision_id);
CODEC_INFO_SHOW(afg, core.afg);
CODEC_INFO_SHOW(mfg, core.mfg);
CODEC_INFO_STR_SHOW(venकरोr_name, core.venकरोr_name);
CODEC_INFO_STR_SHOW(chip_name, core.chip_name);
CODEC_INFO_STR_SHOW(modelname, modelname);

अटल sमाप_प्रकार pin_configs_show(काष्ठा hda_codec *codec,
				काष्ठा snd_array *list,
				अक्षर *buf)
अणु
	स्थिर काष्ठा hda_pincfg *pin;
	पूर्णांक i, len = 0;
	mutex_lock(&codec->user_mutex);
	snd_array_क्रम_each(list, i, pin) अणु
		len += प्र_लिखो(buf + len, "0x%02x 0x%08x\n",
			       pin->nid, pin->cfg);
	पूर्ण
	mutex_unlock(&codec->user_mutex);
	वापस len;
पूर्ण

अटल sमाप_प्रकार init_pin_configs_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	वापस pin_configs_show(codec, &codec->init_pins, buf);
पूर्ण

अटल sमाप_प्रकार driver_pin_configs_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	वापस pin_configs_show(codec, &codec->driver_pins, buf);
पूर्ण

#अगर_घोषित CONFIG_SND_HDA_RECONFIG

/*
 * sysfs पूर्णांकerface
 */

अटल पूर्णांक clear_codec(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;

	err = snd_hda_codec_reset(codec);
	अगर (err < 0) अणु
		codec_err(codec, "The codec is being used, can't free.\n");
		वापस err;
	पूर्ण
	snd_hda_sysfs_clear(codec);
	वापस 0;
पूर्ण

अटल पूर्णांक reconfig_codec(काष्ठा hda_codec *codec)
अणु
	पूर्णांक err;

	snd_hda_घातer_up(codec);
	codec_info(codec, "hda-codec: reconfiguring\n");
	err = snd_hda_codec_reset(codec);
	अगर (err < 0) अणु
		codec_err(codec,
			   "The codec is being used, can't reconfigure.\n");
		जाओ error;
	पूर्ण
	err = device_reprobe(hda_codec_dev(codec));
	अगर (err < 0)
		जाओ error;
	err = snd_card_रेजिस्टर(codec->card);
 error:
	snd_hda_घातer_करोwn(codec);
	वापस err;
पूर्ण

/*
 * allocate a string at most len अक्षरs, and हटाओ the trailing EOL
 */
अटल अक्षर *kstrndup_noeol(स्थिर अक्षर *src, माप_प्रकार len)
अणु
	अक्षर *s = kstrndup(src, len, GFP_KERNEL);
	अक्षर *p;
	अगर (!s)
		वापस शून्य;
	p = म_अक्षर(s, '\n');
	अगर (p)
		*p = 0;
	वापस s;
पूर्ण

#घोषणा CODEC_INFO_STORE(type, field)				\
अटल sमाप_प्रकार type##_store(काष्ठा device *dev,			\
			    काष्ठा device_attribute *attr,	\
			    स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु								\
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);		\
	अचिन्हित दीर्घ val;					\
	पूर्णांक err = kम_से_अदीर्घ(buf, 0, &val);			\
	अगर (err < 0)						\
		वापस err;					\
	codec->field = val;					\
	वापस count;						\
पूर्ण

#घोषणा CODEC_INFO_STR_STORE(type, field)			\
अटल sमाप_प्रकार type##_store(काष्ठा device *dev,			\
			    काष्ठा device_attribute *attr,	\
			    स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु								\
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);		\
	अक्षर *s = kstrndup_noeol(buf, 64);			\
	अगर (!s)							\
		वापस -ENOMEM;					\
	kमुक्त(codec->field);					\
	codec->field = s;					\
	वापस count;						\
पूर्ण

CODEC_INFO_STORE(venकरोr_id, core.venकरोr_id);
CODEC_INFO_STORE(subप्रणाली_id, core.subप्रणाली_id);
CODEC_INFO_STORE(revision_id, core.revision_id);
CODEC_INFO_STR_STORE(venकरोr_name, core.venकरोr_name);
CODEC_INFO_STR_STORE(chip_name, core.chip_name);
CODEC_INFO_STR_STORE(modelname, modelname);

#घोषणा CODEC_ACTION_STORE(type)				\
अटल sमाप_प्रकार type##_store(काष्ठा device *dev,			\
			    काष्ठा device_attribute *attr,	\
			    स्थिर अक्षर *buf, माप_प्रकार count)	\
अणु								\
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);		\
	पूर्णांक err = 0;						\
	अगर (*buf)						\
		err = type##_codec(codec);			\
	वापस err < 0 ? err : count;				\
पूर्ण

CODEC_ACTION_STORE(reconfig);
CODEC_ACTION_STORE(clear);

अटल sमाप_प्रकार init_verbs_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	स्थिर काष्ठा hda_verb *v;
	पूर्णांक i, len = 0;
	mutex_lock(&codec->user_mutex);
	snd_array_क्रम_each(&codec->init_verbs, i, v) अणु
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				"0x%02x 0x%03x 0x%04x\n",
				v->nid, v->verb, v->param);
	पूर्ण
	mutex_unlock(&codec->user_mutex);
	वापस len;
पूर्ण

अटल पूर्णांक parse_init_verbs(काष्ठा hda_codec *codec, स्थिर अक्षर *buf)
अणु
	काष्ठा hda_verb *v;
	पूर्णांक nid, verb, param;

	अगर (माला_पूछो(buf, "%i %i %i", &nid, &verb, &param) != 3)
		वापस -EINVAL;
	अगर (!nid || !verb)
		वापस -EINVAL;
	mutex_lock(&codec->user_mutex);
	v = snd_array_new(&codec->init_verbs);
	अगर (!v) अणु
		mutex_unlock(&codec->user_mutex);
		वापस -ENOMEM;
	पूर्ण
	v->nid = nid;
	v->verb = verb;
	v->param = param;
	mutex_unlock(&codec->user_mutex);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार init_verbs_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	पूर्णांक err = parse_init_verbs(codec, buf);
	अगर (err < 0)
		वापस err;
	वापस count;
पूर्ण

अटल sमाप_प्रकार hपूर्णांकs_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	स्थिर काष्ठा hda_hपूर्णांक *hपूर्णांक;
	पूर्णांक i, len = 0;
	mutex_lock(&codec->user_mutex);
	snd_array_क्रम_each(&codec->hपूर्णांकs, i, hपूर्णांक) अणु
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				"%s = %s\n", hपूर्णांक->key, hपूर्णांक->val);
	पूर्ण
	mutex_unlock(&codec->user_mutex);
	वापस len;
पूर्ण

अटल काष्ठा hda_hपूर्णांक *get_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key)
अणु
	काष्ठा hda_hपूर्णांक *hपूर्णांक;
	पूर्णांक i;

	snd_array_क्रम_each(&codec->hपूर्णांकs, i, hपूर्णांक) अणु
		अगर (!म_भेद(hपूर्णांक->key, key))
			वापस hपूर्णांक;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम हटाओ_trail_spaces(अक्षर *str)
अणु
	अक्षर *p;
	अगर (!*str)
		वापस;
	p = str + म_माप(str) - 1;
	क्रम (; है_खाली(*p); p--) अणु
		*p = 0;
		अगर (p == str)
			वापस;
	पूर्ण
पूर्ण

#घोषणा MAX_HINTS	1024

अटल पूर्णांक parse_hपूर्णांकs(काष्ठा hda_codec *codec, स्थिर अक्षर *buf)
अणु
	अक्षर *key, *val;
	काष्ठा hda_hपूर्णांक *hपूर्णांक;
	पूर्णांक err = 0;

	buf = skip_spaces(buf);
	अगर (!*buf || *buf == '#' || *buf == '\n')
		वापस 0;
	अगर (*buf == '=')
		वापस -EINVAL;
	key = kstrndup_noeol(buf, 1024);
	अगर (!key)
		वापस -ENOMEM;
	/* extract key and val */
	val = म_अक्षर(key, '=');
	अगर (!val) अणु
		kमुक्त(key);
		वापस -EINVAL;
	पूर्ण
	*val++ = 0;
	val = skip_spaces(val);
	हटाओ_trail_spaces(key);
	हटाओ_trail_spaces(val);
	mutex_lock(&codec->user_mutex);
	hपूर्णांक = get_hपूर्णांक(codec, key);
	अगर (hपूर्णांक) अणु
		/* replace */
		kमुक्त(hपूर्णांक->key);
		hपूर्णांक->key = key;
		hपूर्णांक->val = val;
		जाओ unlock;
	पूर्ण
	/* allocate a new hपूर्णांक entry */
	अगर (codec->hपूर्णांकs.used >= MAX_HINTS)
		hपूर्णांक = शून्य;
	अन्यथा
		hपूर्णांक = snd_array_new(&codec->hपूर्णांकs);
	अगर (hपूर्णांक) अणु
		hपूर्णांक->key = key;
		hपूर्णांक->val = val;
	पूर्ण अन्यथा अणु
		err = -ENOMEM;
	पूर्ण
 unlock:
	mutex_unlock(&codec->user_mutex);
	अगर (err)
		kमुक्त(key);
	वापस err;
पूर्ण

अटल sमाप_प्रकार hपूर्णांकs_store(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	पूर्णांक err = parse_hपूर्णांकs(codec, buf);
	अगर (err < 0)
		वापस err;
	वापस count;
पूर्ण

अटल sमाप_प्रकार user_pin_configs_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	वापस pin_configs_show(codec, &codec->user_pins, buf);
पूर्ण

#घोषणा MAX_PIN_CONFIGS		32

अटल पूर्णांक parse_user_pin_configs(काष्ठा hda_codec *codec, स्थिर अक्षर *buf)
अणु
	पूर्णांक nid, cfg, err;

	अगर (माला_पूछो(buf, "%i %i", &nid, &cfg) != 2)
		वापस -EINVAL;
	अगर (!nid)
		वापस -EINVAL;
	mutex_lock(&codec->user_mutex);
	err = snd_hda_add_pincfg(codec, &codec->user_pins, nid, cfg);
	mutex_unlock(&codec->user_mutex);
	वापस err;
पूर्ण

अटल sमाप_प्रकार user_pin_configs_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hda_codec *codec = dev_get_drvdata(dev);
	पूर्णांक err = parse_user_pin_configs(codec, buf);
	अगर (err < 0)
		वापस err;
	वापस count;
पूर्ण

/* sysfs attributes exposed only when CONFIG_SND_HDA_RECONFIG=y */
अटल DEVICE_ATTR_RW(init_verbs);
अटल DEVICE_ATTR_RW(hपूर्णांकs);
अटल DEVICE_ATTR_RW(user_pin_configs);
अटल DEVICE_ATTR_WO(reconfig);
अटल DEVICE_ATTR_WO(clear);

/**
 * snd_hda_get_hपूर्णांक - Look क्रम hपूर्णांक string
 * @codec: the HDA codec
 * @key: the hपूर्णांक key string
 *
 * Look क्रम a hपूर्णांक key/value pair matching with the given key string
 * and वापसs the value string.  If nothing found, वापसs शून्य.
 */
स्थिर अक्षर *snd_hda_get_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key)
अणु
	काष्ठा hda_hपूर्णांक *hपूर्णांक = get_hपूर्णांक(codec, key);
	वापस hपूर्णांक ? hपूर्णांक->val : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_hपूर्णांक);

/**
 * snd_hda_get_bool_hपूर्णांक - Get a boolean hपूर्णांक value
 * @codec: the HDA codec
 * @key: the hपूर्णांक key string
 *
 * Look क्रम a hपूर्णांक key/value pair matching with the given key string
 * and वापसs a boolean value parsed from the value.  If no matching
 * key is found, वापस a negative value.
 */
पूर्णांक snd_hda_get_bool_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key)
अणु
	स्थिर अक्षर *p;
	पूर्णांक ret;

	mutex_lock(&codec->user_mutex);
	p = snd_hda_get_hपूर्णांक(codec, key);
	अगर (!p || !*p)
		ret = -ENOENT;
	अन्यथा अणु
		चयन (बड़े(*p)) अणु
		हाल 'T': /* true */
		हाल 'Y': /* yes */
		हाल '1':
			ret = 1;
			अवरोध;
		शेष:
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&codec->user_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_bool_hपूर्णांक);

/**
 * snd_hda_get_पूर्णांक_hपूर्णांक - Get an पूर्णांकeger hपूर्णांक value
 * @codec: the HDA codec
 * @key: the hपूर्णांक key string
 * @valp: poपूर्णांकer to store a value
 *
 * Look क्रम a hपूर्णांक key/value pair matching with the given key string
 * and stores the पूर्णांकeger value to @valp.  If no matching key is found,
 * वापस a negative error code.  Otherwise it वापसs zero.
 */
पूर्णांक snd_hda_get_पूर्णांक_hपूर्णांक(काष्ठा hda_codec *codec, स्थिर अक्षर *key, पूर्णांक *valp)
अणु
	स्थिर अक्षर *p;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	mutex_lock(&codec->user_mutex);
	p = snd_hda_get_hपूर्णांक(codec, key);
	अगर (!p)
		ret = -ENOENT;
	अन्यथा अगर (kम_से_अदीर्घ(p, 0, &val))
		ret = -EINVAL;
	अन्यथा अणु
		*valp = val;
		ret = 0;
	पूर्ण
	mutex_unlock(&codec->user_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_get_पूर्णांक_hपूर्णांक);
#पूर्ण_अगर /* CONFIG_SND_HDA_RECONFIG */

/*
 * common sysfs attributes
 */
#अगर_घोषित CONFIG_SND_HDA_RECONFIG
#घोषणा RECONFIG_DEVICE_ATTR(name)	DEVICE_ATTR_RW(name)
#अन्यथा
#घोषणा RECONFIG_DEVICE_ATTR(name)	DEVICE_ATTR_RO(name)
#पूर्ण_अगर
अटल RECONFIG_DEVICE_ATTR(venकरोr_id);
अटल RECONFIG_DEVICE_ATTR(subप्रणाली_id);
अटल RECONFIG_DEVICE_ATTR(revision_id);
अटल DEVICE_ATTR_RO(afg);
अटल DEVICE_ATTR_RO(mfg);
अटल RECONFIG_DEVICE_ATTR(venकरोr_name);
अटल RECONFIG_DEVICE_ATTR(chip_name);
अटल RECONFIG_DEVICE_ATTR(modelname);
अटल DEVICE_ATTR_RO(init_pin_configs);
अटल DEVICE_ATTR_RO(driver_pin_configs);


#अगर_घोषित CONFIG_SND_HDA_PATCH_LOADER

/* parser mode */
क्रमागत अणु
	LINE_MODE_NONE,
	LINE_MODE_CODEC,
	LINE_MODE_MODEL,
	LINE_MODE_PINCFG,
	LINE_MODE_VERB,
	LINE_MODE_HINT,
	LINE_MODE_VENDOR_ID,
	LINE_MODE_SUBSYSTEM_ID,
	LINE_MODE_REVISION_ID,
	LINE_MODE_CHIP_NAME,
	NUM_LINE_MODES,
पूर्ण;

अटल अंतरभूत पूर्णांक strmatch(स्थिर अक्षर *a, स्थिर अक्षर *b)
अणु
	वापस strnहालcmp(a, b, म_माप(b)) == 0;
पूर्ण

/* parse the contents after the line "[codec]"
 * accept only the line with three numbers, and assign the current codec
 */
अटल व्योम parse_codec_mode(अक्षर *buf, काष्ठा hda_bus *bus,
			     काष्ठा hda_codec **codecp)
अणु
	पूर्णांक venकरोrid, subid, caddr;
	काष्ठा hda_codec *codec;

	*codecp = शून्य;
	अगर (माला_पूछो(buf, "%i %i %i", &venकरोrid, &subid, &caddr) == 3) अणु
		list_क्रम_each_codec(codec, bus) अणु
			अगर ((venकरोrid <= 0 || codec->core.venकरोr_id == venकरोrid) &&
			    (subid <= 0 || codec->core.subप्रणाली_id == subid) &&
			    codec->core.addr == caddr) अणु
				*codecp = codec;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* parse the contents after the other command tags, [pincfg], [verb],
 * [venकरोr_id], [subप्रणाली_id], [revision_id], [chip_name], [hपूर्णांक] and [model]
 * just pass to the sysfs helper (only when any codec was specअगरied)
 */
अटल व्योम parse_pincfg_mode(अक्षर *buf, काष्ठा hda_bus *bus,
			      काष्ठा hda_codec **codecp)
अणु
	parse_user_pin_configs(*codecp, buf);
पूर्ण

अटल व्योम parse_verb_mode(अक्षर *buf, काष्ठा hda_bus *bus,
			    काष्ठा hda_codec **codecp)
अणु
	parse_init_verbs(*codecp, buf);
पूर्ण

अटल व्योम parse_hपूर्णांक_mode(अक्षर *buf, काष्ठा hda_bus *bus,
			    काष्ठा hda_codec **codecp)
अणु
	parse_hपूर्णांकs(*codecp, buf);
पूर्ण

अटल व्योम parse_model_mode(अक्षर *buf, काष्ठा hda_bus *bus,
			     काष्ठा hda_codec **codecp)
अणु
	kमुक्त((*codecp)->modelname);
	(*codecp)->modelname = kstrdup(buf, GFP_KERNEL);
पूर्ण

अटल व्योम parse_chip_name_mode(अक्षर *buf, काष्ठा hda_bus *bus,
				 काष्ठा hda_codec **codecp)
अणु
	snd_hda_codec_set_name(*codecp, buf);
पूर्ण

#घोषणा DEFINE_PARSE_ID_MODE(name) \
अटल व्योम parse_##name##_mode(अक्षर *buf, काष्ठा hda_bus *bus, \
				 काष्ठा hda_codec **codecp) \
अणु \
	अचिन्हित दीर्घ val; \
	अगर (!kम_से_अदीर्घ(buf, 0, &val)) \
		(*codecp)->core.name = val; \
पूर्ण

DEFINE_PARSE_ID_MODE(venकरोr_id);
DEFINE_PARSE_ID_MODE(subप्रणाली_id);
DEFINE_PARSE_ID_MODE(revision_id);


काष्ठा hda_patch_item अणु
	स्थिर अक्षर *tag;
	स्थिर अक्षर *alias;
	व्योम (*parser)(अक्षर *buf, काष्ठा hda_bus *bus, काष्ठा hda_codec **retc);
पूर्ण;

अटल स्थिर काष्ठा hda_patch_item patch_items[NUM_LINE_MODES] = अणु
	[LINE_MODE_CODEC] = अणु
		.tag = "[codec]",
		.parser = parse_codec_mode,
	पूर्ण,
	[LINE_MODE_MODEL] = अणु
		.tag = "[model]",
		.parser = parse_model_mode,
	पूर्ण,
	[LINE_MODE_VERB] = अणु
		.tag = "[verb]",
		.alias = "[init_verbs]",
		.parser = parse_verb_mode,
	पूर्ण,
	[LINE_MODE_PINCFG] = अणु
		.tag = "[pincfg]",
		.alias = "[user_pin_configs]",
		.parser = parse_pincfg_mode,
	पूर्ण,
	[LINE_MODE_HINT] = अणु
		.tag = "[hint]",
		.alias = "[hints]",
		.parser = parse_hपूर्णांक_mode
	पूर्ण,
	[LINE_MODE_VENDOR_ID] = अणु
		.tag = "[vendor_id]",
		.parser = parse_venकरोr_id_mode,
	पूर्ण,
	[LINE_MODE_SUBSYSTEM_ID] = अणु
		.tag = "[subsystem_id]",
		.parser = parse_subप्रणाली_id_mode,
	पूर्ण,
	[LINE_MODE_REVISION_ID] = अणु
		.tag = "[revision_id]",
		.parser = parse_revision_id_mode,
	पूर्ण,
	[LINE_MODE_CHIP_NAME] = अणु
		.tag = "[chip_name]",
		.parser = parse_chip_name_mode,
	पूर्ण,
पूर्ण;

/* check the line starting with '[' -- change the parser mode accodingly */
अटल पूर्णांक parse_line_mode(अक्षर *buf, काष्ठा hda_bus *bus)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(patch_items); i++) अणु
		अगर (!patch_items[i].tag)
			जारी;
		अगर (strmatch(buf, patch_items[i].tag))
			वापस i;
		अगर (patch_items[i].alias && strmatch(buf, patch_items[i].alias))
			वापस i;
	पूर्ण
	वापस LINE_MODE_NONE;
पूर्ण

/* copy one line from the buffer in fw, and update the fields in fw
 * वापस zero अगर it reaches to the end of the buffer, or non-zero
 * अगर successfully copied a line
 *
 * the spaces at the beginning and the end of the line are stripped
 */
अटल पूर्णांक get_line_from_fw(अक्षर *buf, पूर्णांक size, माप_प्रकार *fw_size_p,
			    स्थिर व्योम **fw_data_p)
अणु
	पूर्णांक len;
	माप_प्रकार fw_size = *fw_size_p;
	स्थिर अक्षर *p = *fw_data_p;

	जबतक (है_खाली(*p) && fw_size) अणु
		p++;
		fw_size--;
	पूर्ण
	अगर (!fw_size)
		वापस 0;

	क्रम (len = 0; len < fw_size; len++) अणु
		अगर (!*p)
			अवरोध;
		अगर (*p == '\n') अणु
			p++;
			len++;
			अवरोध;
		पूर्ण
		अगर (len < size)
			*buf++ = *p++;
	पूर्ण
	*buf = 0;
	*fw_size_p = fw_size - len;
	*fw_data_p = p;
	हटाओ_trail_spaces(buf);
	वापस 1;
पूर्ण

/**
 * snd_hda_load_patch - load a "patch" firmware file and parse it
 * @bus: HD-audio bus
 * @fw_size: the firmware byte size
 * @fw_buf: the firmware data
 */
पूर्णांक snd_hda_load_patch(काष्ठा hda_bus *bus, माप_प्रकार fw_size, स्थिर व्योम *fw_buf)
अणु
	अक्षर buf[128];
	काष्ठा hda_codec *codec;
	पूर्णांक line_mode;

	line_mode = LINE_MODE_NONE;
	codec = शून्य;
	जबतक (get_line_from_fw(buf, माप(buf) - 1, &fw_size, &fw_buf)) अणु
		अगर (!*buf || *buf == '#' || *buf == '\n')
			जारी;
		अगर (*buf == '[')
			line_mode = parse_line_mode(buf, bus);
		अन्यथा अगर (patch_items[line_mode].parser &&
			 (codec || line_mode <= LINE_MODE_CODEC))
			patch_items[line_mode].parser(buf, bus, &codec);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hda_load_patch);
#पूर्ण_अगर /* CONFIG_SND_HDA_PATCH_LOADER */

/*
 * sysfs entries
 */
अटल काष्ठा attribute *hda_dev_attrs[] = अणु
	&dev_attr_venकरोr_id.attr,
	&dev_attr_subप्रणाली_id.attr,
	&dev_attr_revision_id.attr,
	&dev_attr_afg.attr,
	&dev_attr_mfg.attr,
	&dev_attr_venकरोr_name.attr,
	&dev_attr_chip_name.attr,
	&dev_attr_modelname.attr,
	&dev_attr_init_pin_configs.attr,
	&dev_attr_driver_pin_configs.attr,
#अगर_घोषित CONFIG_PM
	&dev_attr_घातer_on_acct.attr,
	&dev_attr_घातer_off_acct.attr,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SND_HDA_RECONFIG
	&dev_attr_init_verbs.attr,
	&dev_attr_hपूर्णांकs.attr,
	&dev_attr_user_pin_configs.attr,
	&dev_attr_reconfig.attr,
	&dev_attr_clear.attr,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hda_dev_attr_group = अणु
	.attrs	= hda_dev_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *snd_hda_dev_attr_groups[] = अणु
	&hda_dev_attr_group,
	शून्य
पूर्ण;

व्योम snd_hda_sysfs_init(काष्ठा hda_codec *codec)
अणु
	mutex_init(&codec->user_mutex);
#अगर_घोषित CONFIG_SND_HDA_RECONFIG
	snd_array_init(&codec->init_verbs, माप(काष्ठा hda_verb), 32);
	snd_array_init(&codec->hपूर्णांकs, माप(काष्ठा hda_hपूर्णांक), 32);
	snd_array_init(&codec->user_pins, माप(काष्ठा hda_pincfg), 16);
#पूर्ण_अगर
पूर्ण

व्योम snd_hda_sysfs_clear(काष्ठा hda_codec *codec)
अणु
#अगर_घोषित CONFIG_SND_HDA_RECONFIG
	काष्ठा hda_hपूर्णांक *hपूर्णांक;
	पूर्णांक i;

	/* clear init verbs */
	snd_array_मुक्त(&codec->init_verbs);
	/* clear hपूर्णांकs */
	snd_array_क्रम_each(&codec->hपूर्णांकs, i, hपूर्णांक) अणु
		kमुक्त(hपूर्णांक->key); /* we करोn't need to मुक्त hपूर्णांक->val */
	पूर्ण
	snd_array_मुक्त(&codec->hपूर्णांकs);
	snd_array_मुक्त(&codec->user_pins);
#पूर्ण_अगर
पूर्ण
