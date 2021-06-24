<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus audio driver
 * Copyright 2015-2016 Google Inc.
 * Copyright 2015-2016 Linaro Ltd.
 */

#समावेश <linux/greybus.h>
#समावेश "audio_codec.h"

#घोषणा GBAUDIO_INVALID_ID	0xFF

/* mixer control */
काष्ठा gb_mixer_control अणु
	पूर्णांक min, max;
	अचिन्हित पूर्णांक reg, rreg, shअगरt, rshअगरt, invert;
पूर्ण;

काष्ठा gbaudio_ctl_pvt अणु
	अचिन्हित पूर्णांक ctl_id;
	अचिन्हित पूर्णांक data_cport;
	अचिन्हित पूर्णांक access;
	अचिन्हित पूर्णांक vcount;
	काष्ठा gb_audio_ctl_elem_info *info;
पूर्ण;

अटल काष्ठा gbaudio_module_info *find_gb_module(
					काष्ठा gbaudio_codec_info *codec,
					अक्षर स्थिर *name)
अणु
	पूर्णांक dev_id;
	अक्षर begin[NAME_SIZE];
	काष्ठा gbaudio_module_info *module;

	अगर (!name)
		वापस शून्य;

	अगर (माला_पूछो(name, "%s %d", begin, &dev_id) != 2)
		वापस शून्य;

	dev_dbg(codec->dev, "%s:Find module#%d\n", __func__, dev_id);

	mutex_lock(&codec->lock);
	list_क्रम_each_entry(module, &codec->module_list, list) अणु
		अगर (module->dev_id == dev_id) अणु
			mutex_unlock(&codec->lock);
			वापस module;
		पूर्ण
	पूर्ण
	mutex_unlock(&codec->lock);
	dev_warn(codec->dev, "%s: module#%d missing in codec list\n", name,
		 dev_id);
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *gbaudio_map_controlid(काष्ठा gbaudio_module_info *module,
					 __u8 control_id, __u8 index)
अणु
	काष्ठा gbaudio_control *control;

	अगर (control_id == GBAUDIO_INVALID_ID)
		वापस शून्य;

	list_क्रम_each_entry(control, &module->ctl_list, list) अणु
		अगर (control->id == control_id) अणु
			अगर (index == GBAUDIO_INVALID_ID)
				वापस control->name;
			अगर (index >= control->items)
				वापस शून्य;
			वापस control->texts[index];
		पूर्ण
	पूर्ण
	list_क्रम_each_entry(control, &module->widget_ctl_list, list) अणु
		अगर (control->id == control_id) अणु
			अगर (index == GBAUDIO_INVALID_ID)
				वापस control->name;
			अगर (index >= control->items)
				वापस शून्य;
			वापस control->texts[index];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक gbaudio_map_controlname(काष्ठा gbaudio_module_info *module,
				   स्थिर अक्षर *name)
अणु
	काष्ठा gbaudio_control *control;

	list_क्रम_each_entry(control, &module->ctl_list, list) अणु
		अगर (!म_भेदन(control->name, name, NAME_SIZE))
			वापस control->id;
	पूर्ण

	dev_warn(module->dev, "%s: missing in modules controls list\n", name);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gbaudio_map_wcontrolname(काष्ठा gbaudio_module_info *module,
				    स्थिर अक्षर *name)
अणु
	काष्ठा gbaudio_control *control;

	list_क्रम_each_entry(control, &module->widget_ctl_list, list) अणु
		अगर (!म_भेदन(control->wname, name, NAME_SIZE))
			वापस control->id;
	पूर्ण
	dev_warn(module->dev, "%s: missing in modules controls list\n", name);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gbaudio_map_widgetname(काष्ठा gbaudio_module_info *module,
				  स्थिर अक्षर *name)
अणु
	काष्ठा gbaudio_widget *widget;

	list_क्रम_each_entry(widget, &module->widget_list, list) अणु
		अगर (!म_भेदन(widget->name, name, NAME_SIZE))
			वापस widget->id;
	पूर्ण
	dev_warn(module->dev, "%s: missing in modules widgets list\n", name);

	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *gbaudio_map_widgetid(काष्ठा gbaudio_module_info *module,
					__u8 widget_id)
अणु
	काष्ठा gbaudio_widget *widget;

	list_क्रम_each_entry(widget, &module->widget_list, list) अणु
		अगर (widget->id == widget_id)
			वापस widget->name;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर **gb_generate_क्रमागत_strings(काष्ठा gbaudio_module_info *gb,
					     काष्ठा gb_audio_क्रमागतerated *gbक्रमागत)
अणु
	स्थिर अक्षर **strings;
	पूर्णांक i;
	अचिन्हित पूर्णांक items;
	__u8 *data;

	items = le32_to_cpu(gbक्रमागत->items);
	strings = devm_kसुस्मृति(gb->dev, items, माप(अक्षर *), GFP_KERNEL);
	data = gbक्रमागत->names;

	क्रम (i = 0; i < items; i++) अणु
		strings[i] = (स्थिर अक्षर *)data;
		जबतक (*data != '\0')
			data++;
		data++;
	पूर्ण

	वापस strings;
पूर्ण

अटल पूर्णांक gbcodec_mixer_ctl_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक max;
	स्थिर अक्षर *name;
	काष्ठा gbaudio_ctl_pvt *data;
	काष्ठा gb_audio_ctl_elem_info *info;
	काष्ठा gbaudio_module_info *module;
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा gbaudio_codec_info *gbcodec = snd_soc_component_get_drvdata(comp);

	dev_dbg(comp->dev, "Entered %s:%s\n", __func__, kcontrol->id.name);
	data = (काष्ठा gbaudio_ctl_pvt *)kcontrol->निजी_value;
	info = (काष्ठा gb_audio_ctl_elem_info *)data->info;

	अगर (!info) अणु
		dev_err(comp->dev, "NULL info for %s\n", uinfo->id.name);
		वापस -EINVAL;
	पूर्ण

	/* update uinfo */
	uinfo->access = data->access;
	uinfo->count = data->vcount;
	uinfo->type = (__क्रमce snd_ctl_elem_type_t)info->type;

	चयन (info->type) अणु
	हाल GB_AUDIO_CTL_ELEM_TYPE_BOOLEAN:
	हाल GB_AUDIO_CTL_ELEM_TYPE_INTEGER:
		uinfo->value.पूर्णांकeger.min = le32_to_cpu(info->value.पूर्णांकeger.min);
		uinfo->value.पूर्णांकeger.max = le32_to_cpu(info->value.पूर्णांकeger.max);
		अवरोध;
	हाल GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED:
		max = le32_to_cpu(info->value.क्रमागतerated.items);
		uinfo->value.क्रमागतerated.items = max;
		अगर (uinfo->value.क्रमागतerated.item > max - 1)
			uinfo->value.क्रमागतerated.item = max - 1;
		module = find_gb_module(gbcodec, kcontrol->id.name);
		अगर (!module)
			वापस -EINVAL;
		name = gbaudio_map_controlid(module, data->ctl_id,
					     uinfo->value.क्रमागतerated.item);
		strscpy(uinfo->value.क्रमागतerated.name, name, माप(uinfo->value.क्रमागतerated.name));
		अवरोध;
	शेष:
		dev_err(comp->dev, "Invalid type: %d for %s:kcontrol\n",
			info->type, kcontrol->id.name);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gbcodec_mixer_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret;
	काष्ठा gb_audio_ctl_elem_info *info;
	काष्ठा gbaudio_ctl_pvt *data;
	काष्ठा gb_audio_ctl_elem_value gbvalue;
	काष्ठा gbaudio_module_info *module;
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा gbaudio_codec_info *gb = snd_soc_component_get_drvdata(comp);
	काष्ठा gb_bundle *bundle;

	dev_dbg(comp->dev, "Entered %s:%s\n", __func__, kcontrol->id.name);
	module = find_gb_module(gb, kcontrol->id.name);
	अगर (!module)
		वापस -EINVAL;

	data = (काष्ठा gbaudio_ctl_pvt *)kcontrol->निजी_value;
	info = (काष्ठा gb_audio_ctl_elem_info *)data->info;
	bundle = to_gb_bundle(module->dev);

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	ret = gb_audio_gb_get_control(module->mgmt_connection, data->ctl_id,
				      GB_AUDIO_INVALID_INDEX, &gbvalue);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	अगर (ret) अणु
		dev_err_ratelimited(comp->dev, "%d:Error in %s for %s\n", ret,
				    __func__, kcontrol->id.name);
		वापस ret;
	पूर्ण

	/* update ucontrol */
	चयन (info->type) अणु
	हाल GB_AUDIO_CTL_ELEM_TYPE_BOOLEAN:
	हाल GB_AUDIO_CTL_ELEM_TYPE_INTEGER:
		ucontrol->value.पूर्णांकeger.value[0] =
			le32_to_cpu(gbvalue.value.पूर्णांकeger_value[0]);
		अगर (data->vcount == 2)
			ucontrol->value.पूर्णांकeger.value[1] =
				le32_to_cpu(gbvalue.value.पूर्णांकeger_value[1]);
		अवरोध;
	हाल GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED:
		ucontrol->value.क्रमागतerated.item[0] =
			le32_to_cpu(gbvalue.value.क्रमागतerated_item[0]);
		अगर (data->vcount == 2)
			ucontrol->value.क्रमागतerated.item[1] =
				le32_to_cpu(gbvalue.value.क्रमागतerated_item[1]);
		अवरोध;
	शेष:
		dev_err(comp->dev, "Invalid type: %d for %s:kcontrol\n",
			info->type, kcontrol->id.name);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gbcodec_mixer_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret = 0;
	काष्ठा gb_audio_ctl_elem_info *info;
	काष्ठा gbaudio_ctl_pvt *data;
	काष्ठा gb_audio_ctl_elem_value gbvalue;
	काष्ठा gbaudio_module_info *module;
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा gbaudio_codec_info *gb = snd_soc_component_get_drvdata(comp);
	काष्ठा gb_bundle *bundle;

	dev_dbg(comp->dev, "Entered %s:%s\n", __func__, kcontrol->id.name);
	module = find_gb_module(gb, kcontrol->id.name);
	अगर (!module)
		वापस -EINVAL;

	data = (काष्ठा gbaudio_ctl_pvt *)kcontrol->निजी_value;
	info = (काष्ठा gb_audio_ctl_elem_info *)data->info;
	bundle = to_gb_bundle(module->dev);

	/* update ucontrol */
	चयन (info->type) अणु
	हाल GB_AUDIO_CTL_ELEM_TYPE_BOOLEAN:
	हाल GB_AUDIO_CTL_ELEM_TYPE_INTEGER:
		gbvalue.value.पूर्णांकeger_value[0] =
			cpu_to_le32(ucontrol->value.पूर्णांकeger.value[0]);
		अगर (data->vcount == 2)
			gbvalue.value.पूर्णांकeger_value[1] =
				cpu_to_le32(ucontrol->value.पूर्णांकeger.value[1]);
		अवरोध;
	हाल GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED:
		gbvalue.value.क्रमागतerated_item[0] =
			cpu_to_le32(ucontrol->value.क्रमागतerated.item[0]);
		अगर (data->vcount == 2)
			gbvalue.value.क्रमागतerated_item[1] =
				cpu_to_le32(ucontrol->value.क्रमागतerated.item[1]);
		अवरोध;
	शेष:
		dev_err(comp->dev, "Invalid type: %d for %s:kcontrol\n",
			info->type, kcontrol->id.name);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	ret = gb_audio_gb_set_control(module->mgmt_connection, data->ctl_id,
				      GB_AUDIO_INVALID_INDEX, &gbvalue);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	अगर (ret) अणु
		dev_err_ratelimited(comp->dev, "%d:Error in %s for %s\n", ret,
				    __func__, kcontrol->id.name);
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा SOC_MIXER_GB(xname, kcount, data) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.count = kcount, .info = gbcodec_mixer_ctl_info, \
	.get = gbcodec_mixer_ctl_get, .put = gbcodec_mixer_ctl_put, \
	.निजी_value = (अचिन्हित दीर्घ)data पूर्ण

/*
 * although below callback functions seems redundant to above functions.
 * same are kept to allow provision क्रम dअगरferent handling in हाल
 * of DAPM related sequencing, etc.
 */
अटल पूर्णांक gbcodec_mixer_dapm_ctl_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक platक्रमm_max, platक्रमm_min;
	काष्ठा gbaudio_ctl_pvt *data;
	काष्ठा gb_audio_ctl_elem_info *info;

	data = (काष्ठा gbaudio_ctl_pvt *)kcontrol->निजी_value;
	info = (काष्ठा gb_audio_ctl_elem_info *)data->info;

	/* update uinfo */
	platक्रमm_max = le32_to_cpu(info->value.पूर्णांकeger.max);
	platक्रमm_min = le32_to_cpu(info->value.पूर्णांकeger.min);

	अगर (platक्रमm_max == 1 &&
	    !strnstr(kcontrol->id.name, " Volume", माप(kcontrol->id.name)))
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	अन्यथा
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;

	uinfo->count = data->vcount;
	uinfo->value.पूर्णांकeger.min = platक्रमm_min;
	uinfo->value.पूर्णांकeger.max = platक्रमm_max;

	वापस 0;
पूर्ण

अटल पूर्णांक gbcodec_mixer_dapm_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret;
	काष्ठा gbaudio_ctl_pvt *data;
	काष्ठा gb_audio_ctl_elem_value gbvalue;
	काष्ठा gbaudio_module_info *module;
	काष्ठा snd_soc_dapm_widget_list *wlist = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_widget *widget = wlist->widमाला_लो[0];
	काष्ठा device *codec_dev = widget->dapm->dev;
	काष्ठा gbaudio_codec_info *gb = dev_get_drvdata(codec_dev);
	काष्ठा gb_bundle *bundle;

	dev_dbg(codec_dev, "Entered %s:%s\n", __func__, kcontrol->id.name);
	module = find_gb_module(gb, kcontrol->id.name);
	अगर (!module)
		वापस -EINVAL;

	data = (काष्ठा gbaudio_ctl_pvt *)kcontrol->निजी_value;
	bundle = to_gb_bundle(module->dev);

	अगर (data->vcount == 2)
		dev_warn(widget->dapm->dev,
			 "GB: Control '%s' is stereo, which is not supported\n",
			 kcontrol->id.name);

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	ret = gb_audio_gb_get_control(module->mgmt_connection, data->ctl_id,
				      GB_AUDIO_INVALID_INDEX, &gbvalue);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	अगर (ret) अणु
		dev_err_ratelimited(codec_dev, "%d:Error in %s for %s\n", ret,
				    __func__, kcontrol->id.name);
		वापस ret;
	पूर्ण
	/* update ucontrol */
	ucontrol->value.पूर्णांकeger.value[0] =
		le32_to_cpu(gbvalue.value.पूर्णांकeger_value[0]);

	वापस ret;
पूर्ण

अटल पूर्णांक gbcodec_mixer_dapm_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret, wi, max, connect;
	अचिन्हित पूर्णांक mask, val;
	काष्ठा gb_audio_ctl_elem_info *info;
	काष्ठा gbaudio_ctl_pvt *data;
	काष्ठा gb_audio_ctl_elem_value gbvalue;
	काष्ठा gbaudio_module_info *module;
	काष्ठा snd_soc_dapm_widget_list *wlist = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_widget *widget = wlist->widमाला_लो[0];
	काष्ठा device *codec_dev = widget->dapm->dev;
	काष्ठा gbaudio_codec_info *gb = dev_get_drvdata(codec_dev);
	काष्ठा gb_bundle *bundle;

	dev_dbg(codec_dev, "Entered %s:%s\n", __func__, kcontrol->id.name);
	module = find_gb_module(gb, kcontrol->id.name);
	अगर (!module)
		वापस -EINVAL;

	data = (काष्ठा gbaudio_ctl_pvt *)kcontrol->निजी_value;
	info = (काष्ठा gb_audio_ctl_elem_info *)data->info;
	bundle = to_gb_bundle(module->dev);

	अगर (data->vcount == 2)
		dev_warn(widget->dapm->dev,
			 "GB: Control '%s' is stereo, which is not supported\n",
			 kcontrol->id.name);

	max = le32_to_cpu(info->value.पूर्णांकeger.max);
	mask = (1 << fls(max)) - 1;
	val = ucontrol->value.पूर्णांकeger.value[0] & mask;
	connect = !!val;

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	ret = gb_audio_gb_get_control(module->mgmt_connection, data->ctl_id,
				      GB_AUDIO_INVALID_INDEX, &gbvalue);
	अगर (ret)
		जाओ निकास;

	/* update ucontrol */
	अगर (le32_to_cpu(gbvalue.value.पूर्णांकeger_value[0]) != val) अणु
		क्रम (wi = 0; wi < wlist->num_widमाला_लो; wi++) अणु
			widget = wlist->widमाला_लो[wi];
			snd_soc_dapm_mixer_update_घातer(widget->dapm, kcontrol,
							connect, शून्य);
		पूर्ण
		gbvalue.value.पूर्णांकeger_value[0] =
			cpu_to_le32(ucontrol->value.पूर्णांकeger.value[0]);

		ret = gb_audio_gb_set_control(module->mgmt_connection,
					      data->ctl_id,
					      GB_AUDIO_INVALID_INDEX, &gbvalue);
	पूर्ण

निकास:
	gb_pm_runसमय_put_स्वतःsuspend(bundle);
	अगर (ret)
		dev_err_ratelimited(codec_dev, "%d:Error in %s for %s\n", ret,
				    __func__, kcontrol->id.name);
	वापस ret;
पूर्ण

#घोषणा SOC_DAPM_MIXER_GB(xname, kcount, data) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.count = kcount, .info = gbcodec_mixer_dapm_ctl_info, \
	.get = gbcodec_mixer_dapm_ctl_get, .put = gbcodec_mixer_dapm_ctl_put, \
	.निजी_value = (अचिन्हित दीर्घ)dataपूर्ण

अटल पूर्णांक gbcodec_event_spk(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	/* Ensure GB speaker is connected */

	वापस 0;
पूर्ण

अटल पूर्णांक gbcodec_event_hp(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	/* Ensure GB module supports jack slot */

	वापस 0;
पूर्ण

अटल पूर्णांक gbcodec_event_पूर्णांक_mic(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	/* Ensure GB module supports jack slot */

	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_validate_kcontrol_count(काष्ठा gb_audio_widget *w)
अणु
	पूर्णांक ret = 0;

	चयन (w->type) अणु
	हाल snd_soc_dapm_spk:
	हाल snd_soc_dapm_hp:
	हाल snd_soc_dapm_mic:
	हाल snd_soc_dapm_output:
	हाल snd_soc_dapm_input:
		अगर (w->ncontrols)
			ret = -EINVAL;
		अवरोध;
	हाल snd_soc_dapm_चयन:
	हाल snd_soc_dapm_mux:
		अगर (w->ncontrols != 1)
			ret = -EINVAL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gbcodec_क्रमागत_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret, ctl_id;
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा gbaudio_codec_info *gb = snd_soc_component_get_drvdata(comp);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा gb_audio_ctl_elem_value gbvalue;
	काष्ठा gbaudio_module_info *module;
	काष्ठा gb_bundle *bundle;

	module = find_gb_module(gb, kcontrol->id.name);
	अगर (!module)
		वापस -EINVAL;

	ctl_id = gbaudio_map_controlname(module, kcontrol->id.name);
	अगर (ctl_id < 0)
		वापस -EINVAL;

	bundle = to_gb_bundle(module->dev);

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	ret = gb_audio_gb_get_control(module->mgmt_connection, ctl_id,
				      GB_AUDIO_INVALID_INDEX, &gbvalue);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	अगर (ret) अणु
		dev_err_ratelimited(comp->dev, "%d:Error in %s for %s\n", ret,
				    __func__, kcontrol->id.name);
		वापस ret;
	पूर्ण

	ucontrol->value.क्रमागतerated.item[0] =
		le32_to_cpu(gbvalue.value.क्रमागतerated_item[0]);
	अगर (e->shअगरt_l != e->shअगरt_r)
		ucontrol->value.क्रमागतerated.item[1] =
			le32_to_cpu(gbvalue.value.क्रमागतerated_item[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक gbcodec_क्रमागत_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret, ctl_id;
	काष्ठा snd_soc_component *comp = snd_soc_kcontrol_component(kcontrol);
	काष्ठा gbaudio_codec_info *gb = snd_soc_component_get_drvdata(comp);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा gb_audio_ctl_elem_value gbvalue;
	काष्ठा gbaudio_module_info *module;
	काष्ठा gb_bundle *bundle;

	module = find_gb_module(gb, kcontrol->id.name);
	अगर (!module)
		वापस -EINVAL;

	ctl_id = gbaudio_map_controlname(module, kcontrol->id.name);
	अगर (ctl_id < 0)
		वापस -EINVAL;

	अगर (ucontrol->value.क्रमागतerated.item[0] > e->items - 1)
		वापस -EINVAL;
	gbvalue.value.क्रमागतerated_item[0] =
		cpu_to_le32(ucontrol->value.क्रमागतerated.item[0]);

	अगर (e->shअगरt_l != e->shअगरt_r) अणु
		अगर (ucontrol->value.क्रमागतerated.item[1] > e->items - 1)
			वापस -EINVAL;
		gbvalue.value.क्रमागतerated_item[1] =
			cpu_to_le32(ucontrol->value.क्रमागतerated.item[1]);
	पूर्ण

	bundle = to_gb_bundle(module->dev);

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	ret = gb_audio_gb_set_control(module->mgmt_connection, ctl_id,
				      GB_AUDIO_INVALID_INDEX, &gbvalue);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	अगर (ret) अणु
		dev_err_ratelimited(comp->dev, "%d:Error in %s for %s\n",
				    ret, __func__, kcontrol->id.name);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक gbaudio_tplg_create_क्रमागत_kctl(काष्ठा gbaudio_module_info *gb,
					 काष्ठा snd_kcontrol_new *kctl,
					 काष्ठा gb_audio_control *ctl)
अणु
	काष्ठा soc_क्रमागत *gbe;
	काष्ठा gb_audio_क्रमागतerated *gb_क्रमागत;
	पूर्णांक i;

	gbe = devm_kzalloc(gb->dev, माप(*gbe), GFP_KERNEL);
	अगर (!gbe)
		वापस -ENOMEM;

	gb_क्रमागत = &ctl->info.value.क्रमागतerated;

	/* since count=1, and reg is dummy */
	gbe->items = le32_to_cpu(gb_क्रमागत->items);
	gbe->texts = gb_generate_क्रमागत_strings(gb, gb_क्रमागत);

	/* debug क्रमागत info */
	dev_dbg(gb->dev, "Max:%d, name_length:%d\n", gbe->items,
		le16_to_cpu(gb_क्रमागत->names_length));
	क्रम (i = 0; i < gbe->items; i++)
		dev_dbg(gb->dev, "src[%d]: %s\n", i, gbe->texts[i]);

	*kctl = (काष्ठा snd_kcontrol_new)
		SOC_ENUM_EXT(ctl->name, *gbe, gbcodec_क्रमागत_ctl_get,
			     gbcodec_क्रमागत_ctl_put);
	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_tplg_create_kcontrol(काष्ठा gbaudio_module_info *gb,
					काष्ठा snd_kcontrol_new *kctl,
					काष्ठा gb_audio_control *ctl)
अणु
	पूर्णांक ret = 0;
	काष्ठा gbaudio_ctl_pvt *ctldata;

	चयन (ctl->अगरace) अणु
	हाल SNDRV_CTL_ELEM_IFACE_MIXER:
		चयन (ctl->info.type) अणु
		हाल GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED:
			ret = gbaudio_tplg_create_क्रमागत_kctl(gb, kctl, ctl);
			अवरोध;
		शेष:
			ctldata = devm_kzalloc(gb->dev,
					       माप(काष्ठा gbaudio_ctl_pvt),
					       GFP_KERNEL);
			अगर (!ctldata)
				वापस -ENOMEM;
			ctldata->ctl_id = ctl->id;
			ctldata->data_cport = le16_to_cpu(ctl->data_cport);
			ctldata->access = le32_to_cpu(ctl->access);
			ctldata->vcount = ctl->count_values;
			ctldata->info = &ctl->info;
			*kctl = (काष्ठा snd_kcontrol_new)
				SOC_MIXER_GB(ctl->name, ctl->count, ctldata);
			ctldata = शून्य;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(gb->dev, "%s:%d control created\n", ctl->name, ctl->id);
	वापस ret;
पूर्ण

अटल पूर्णांक gbcodec_क्रमागत_dapm_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret, ctl_id;
	काष्ठा snd_soc_dapm_widget_list *wlist = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_widget *widget = wlist->widमाला_लो[0];
	काष्ठा gbaudio_module_info *module;
	काष्ठा gb_audio_ctl_elem_value gbvalue;
	काष्ठा device *codec_dev = widget->dapm->dev;
	काष्ठा gbaudio_codec_info *gb = dev_get_drvdata(codec_dev);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा gb_bundle *bundle;

	module = find_gb_module(gb, kcontrol->id.name);
	अगर (!module)
		वापस -EINVAL;

	ctl_id = gbaudio_map_wcontrolname(module, kcontrol->id.name);
	अगर (ctl_id < 0)
		वापस -EINVAL;

	bundle = to_gb_bundle(module->dev);

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	ret = gb_audio_gb_get_control(module->mgmt_connection, ctl_id,
				      GB_AUDIO_INVALID_INDEX, &gbvalue);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	अगर (ret) अणु
		dev_err_ratelimited(codec_dev, "%d:Error in %s for %s\n", ret,
				    __func__, kcontrol->id.name);
		वापस ret;
	पूर्ण

	ucontrol->value.क्रमागतerated.item[0] = le32_to_cpu(gbvalue.value.क्रमागतerated_item[0]);
	अगर (e->shअगरt_l != e->shअगरt_r)
		ucontrol->value.क्रमागतerated.item[1] =
			le32_to_cpu(gbvalue.value.क्रमागतerated_item[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक gbcodec_क्रमागत_dapm_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक ret, wi, ctl_id;
	अचिन्हित पूर्णांक val, mux, change;
	अचिन्हित पूर्णांक mask;
	काष्ठा snd_soc_dapm_widget_list *wlist = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_widget *widget = wlist->widमाला_लो[0];
	काष्ठा gb_audio_ctl_elem_value gbvalue;
	काष्ठा gbaudio_module_info *module;
	काष्ठा device *codec_dev = widget->dapm->dev;
	काष्ठा gbaudio_codec_info *gb = dev_get_drvdata(codec_dev);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	काष्ठा gb_bundle *bundle;

	अगर (ucontrol->value.क्रमागतerated.item[0] > e->items - 1)
		वापस -EINVAL;

	module = find_gb_module(gb, kcontrol->id.name);
	अगर (!module)
		वापस -EINVAL;

	ctl_id = gbaudio_map_wcontrolname(module, kcontrol->id.name);
	अगर (ctl_id < 0)
		वापस -EINVAL;

	change = 0;
	bundle = to_gb_bundle(module->dev);

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	ret = gb_audio_gb_get_control(module->mgmt_connection, ctl_id,
				      GB_AUDIO_INVALID_INDEX, &gbvalue);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	अगर (ret) अणु
		dev_err_ratelimited(codec_dev, "%d:Error in %s for %s\n", ret,
				    __func__, kcontrol->id.name);
		वापस ret;
	पूर्ण

	mux = ucontrol->value.क्रमागतerated.item[0];
	val = mux << e->shअगरt_l;
	mask = e->mask << e->shअगरt_l;

	अगर (le32_to_cpu(gbvalue.value.क्रमागतerated_item[0]) !=
	    ucontrol->value.क्रमागतerated.item[0]) अणु
		change = 1;
		gbvalue.value.क्रमागतerated_item[0] =
			cpu_to_le32(ucontrol->value.क्रमागतerated.item[0]);
	पूर्ण

	अगर (e->shअगरt_l != e->shअगरt_r) अणु
		अगर (ucontrol->value.क्रमागतerated.item[1] > e->items - 1)
			वापस -EINVAL;
		val |= ucontrol->value.क्रमागतerated.item[1] << e->shअगरt_r;
		mask |= e->mask << e->shअगरt_r;
		अगर (le32_to_cpu(gbvalue.value.क्रमागतerated_item[1]) !=
		    ucontrol->value.क्रमागतerated.item[1]) अणु
			change = 1;
			gbvalue.value.क्रमागतerated_item[1] =
				cpu_to_le32(ucontrol->value.क्रमागतerated.item[1]);
		पूर्ण
	पूर्ण

	अगर (change) अणु
		ret = gb_pm_runसमय_get_sync(bundle);
		अगर (ret)
			वापस ret;

		ret = gb_audio_gb_set_control(module->mgmt_connection, ctl_id,
					      GB_AUDIO_INVALID_INDEX, &gbvalue);

		gb_pm_runसमय_put_स्वतःsuspend(bundle);

		अगर (ret) अणु
			dev_err_ratelimited(codec_dev,
					    "%d:Error in %s for %s\n", ret,
					    __func__, kcontrol->id.name);
		पूर्ण
		क्रम (wi = 0; wi < wlist->num_widमाला_लो; wi++) अणु
			widget = wlist->widमाला_लो[wi];
			snd_soc_dapm_mux_update_घातer(widget->dapm, kcontrol,
						      val, e, शून्य);
		पूर्ण
	पूर्ण

	वापस change;
पूर्ण

अटल पूर्णांक gbaudio_tplg_create_क्रमागत_ctl(काष्ठा gbaudio_module_info *gb,
					काष्ठा snd_kcontrol_new *kctl,
					काष्ठा gb_audio_control *ctl)
अणु
	काष्ठा soc_क्रमागत *gbe;
	काष्ठा gb_audio_क्रमागतerated *gb_क्रमागत;
	पूर्णांक i;

	gbe = devm_kzalloc(gb->dev, माप(*gbe), GFP_KERNEL);
	अगर (!gbe)
		वापस -ENOMEM;

	gb_क्रमागत = &ctl->info.value.क्रमागतerated;

	/* since count=1, and reg is dummy */
	gbe->items = le32_to_cpu(gb_क्रमागत->items);
	gbe->texts = gb_generate_क्रमागत_strings(gb, gb_क्रमागत);

	/* debug क्रमागत info */
	dev_dbg(gb->dev, "Max:%d, name_length:%d\n", gbe->items,
		le16_to_cpu(gb_क्रमागत->names_length));
	क्रम (i = 0; i < gbe->items; i++)
		dev_dbg(gb->dev, "src[%d]: %s\n", i, gbe->texts[i]);

	*kctl = (काष्ठा snd_kcontrol_new)
		SOC_DAPM_ENUM_EXT(ctl->name, *gbe, gbcodec_क्रमागत_dapm_ctl_get,
				  gbcodec_क्रमागत_dapm_ctl_put);
	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_tplg_create_mixer_ctl(काष्ठा gbaudio_module_info *gb,
					 काष्ठा snd_kcontrol_new *kctl,
					 काष्ठा gb_audio_control *ctl)
अणु
	काष्ठा gbaudio_ctl_pvt *ctldata;

	ctldata = devm_kzalloc(gb->dev, माप(काष्ठा gbaudio_ctl_pvt),
			       GFP_KERNEL);
	अगर (!ctldata)
		वापस -ENOMEM;
	ctldata->ctl_id = ctl->id;
	ctldata->data_cport = le16_to_cpu(ctl->data_cport);
	ctldata->access = le32_to_cpu(ctl->access);
	ctldata->vcount = ctl->count_values;
	ctldata->info = &ctl->info;
	*kctl = (काष्ठा snd_kcontrol_new)
		SOC_DAPM_MIXER_GB(ctl->name, ctl->count, ctldata);

	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_tplg_create_wcontrol(काष्ठा gbaudio_module_info *gb,
					काष्ठा snd_kcontrol_new *kctl,
					काष्ठा gb_audio_control *ctl)
अणु
	पूर्णांक ret;

	चयन (ctl->अगरace) अणु
	हाल SNDRV_CTL_ELEM_IFACE_MIXER:
		चयन (ctl->info.type) अणु
		हाल GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED:
			ret = gbaudio_tplg_create_क्रमागत_ctl(gb, kctl, ctl);
			अवरोध;
		शेष:
			ret = gbaudio_tplg_create_mixer_ctl(gb, kctl, ctl);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(gb->dev, "%s:%d DAPM control created, ret:%d\n", ctl->name,
		ctl->id, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक gbaudio_widget_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	पूर्णांक wid;
	पूर्णांक ret;
	काष्ठा device *codec_dev = w->dapm->dev;
	काष्ठा gbaudio_codec_info *gbcodec = dev_get_drvdata(codec_dev);
	काष्ठा gbaudio_module_info *module;
	काष्ठा gb_bundle *bundle;

	dev_dbg(codec_dev, "%s %s %d\n", __func__, w->name, event);

	/* Find relevant module */
	module = find_gb_module(gbcodec, w->name);
	अगर (!module)
		वापस -EINVAL;

	/* map name to widget id */
	wid = gbaudio_map_widgetname(module, w->name);
	अगर (wid < 0) अणु
		dev_err(codec_dev, "Invalid widget name:%s\n", w->name);
		वापस -EINVAL;
	पूर्ण

	bundle = to_gb_bundle(module->dev);

	ret = gb_pm_runसमय_get_sync(bundle);
	अगर (ret)
		वापस ret;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = gb_audio_gb_enable_widget(module->mgmt_connection, wid);
		अगर (!ret)
			ret = gbaudio_module_update(gbcodec, w, module, 1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		ret = gb_audio_gb_disable_widget(module->mgmt_connection, wid);
		अगर (!ret)
			ret = gbaudio_module_update(gbcodec, w, module, 0);
		अवरोध;
	पूर्ण
	अगर (ret)
		dev_err_ratelimited(codec_dev,
				    "%d: widget, event:%d failed:%d\n", wid,
				    event, ret);

	gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस ret;
पूर्ण

अटल पूर्णांक gbaudio_tplg_create_widget(काष्ठा gbaudio_module_info *module,
				      काष्ठा snd_soc_dapm_widget *dw,
				      काष्ठा gb_audio_widget *w, पूर्णांक *w_size)
अणु
	पूर्णांक i, ret, csize;
	काष्ठा snd_kcontrol_new *widget_kctls;
	काष्ठा gb_audio_control *curr;
	काष्ठा gbaudio_control *control, *_control;
	माप_प्रकार size;
	अक्षर temp_name[NAME_SIZE];

	ret = gbaudio_validate_kcontrol_count(w);
	अगर (ret) अणु
		dev_err(module->dev, "Invalid kcontrol count=%d for %s\n",
			w->ncontrols, w->name);
		वापस ret;
	पूर्ण

	/* allocate memory क्रम kcontrol */
	अगर (w->ncontrols) अणु
		size = माप(काष्ठा snd_kcontrol_new) * w->ncontrols;
		widget_kctls = devm_kzalloc(module->dev, size, GFP_KERNEL);
		अगर (!widget_kctls)
			वापस -ENOMEM;
	पूर्ण

	*w_size = माप(काष्ठा gb_audio_widget);

	/* create relevant kcontrols */
	curr = w->ctl;
	क्रम (i = 0; i < w->ncontrols; i++) अणु
		ret = gbaudio_tplg_create_wcontrol(module, &widget_kctls[i],
						   curr);
		अगर (ret) अणु
			dev_err(module->dev,
				"%s:%d type widget_ctl not supported\n",
				curr->name, curr->अगरace);
			जाओ error;
		पूर्ण
		control = devm_kzalloc(module->dev,
				       माप(काष्ठा gbaudio_control),
				       GFP_KERNEL);
		अगर (!control) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		control->id = curr->id;
		control->name = curr->name;
		control->wname = w->name;

		अगर (curr->info.type == GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED) अणु
			काष्ठा gb_audio_क्रमागतerated *gbक्रमागत =
				&curr->info.value.क्रमागतerated;

			csize = दुरत्व(काष्ठा gb_audio_control, info);
			csize += दुरत्व(काष्ठा gb_audio_ctl_elem_info, value);
			csize += दुरत्व(काष्ठा gb_audio_क्रमागतerated, names);
			csize += le16_to_cpu(gbक्रमागत->names_length);
			control->texts = (स्थिर अक्षर * स्थिर *)
				gb_generate_क्रमागत_strings(module, gbक्रमागत);
			control->items = le32_to_cpu(gbक्रमागत->items);
		पूर्ण अन्यथा अणु
			csize = माप(काष्ठा gb_audio_control);
		पूर्ण

		*w_size += csize;
		curr = (व्योम *)curr + csize;
		list_add(&control->list, &module->widget_ctl_list);
		dev_dbg(module->dev, "%s: control of type %d created\n",
			widget_kctls[i].name, widget_kctls[i].अगरace);
	पूर्ण

	/* Prefix dev_id to widget control_name */
	strscpy(temp_name, w->name, माप(temp_name));
	snम_लिखो(w->name, माप(w->name), "GB %d %s", module->dev_id, temp_name);

	चयन (w->type) अणु
	हाल snd_soc_dapm_spk:
		*dw = (काष्ठा snd_soc_dapm_widget)
			SND_SOC_DAPM_SPK(w->name, gbcodec_event_spk);
		module->op_devices |= GBAUDIO_DEVICE_OUT_SPEAKER;
		अवरोध;
	हाल snd_soc_dapm_hp:
		*dw = (काष्ठा snd_soc_dapm_widget)
			SND_SOC_DAPM_HP(w->name, gbcodec_event_hp);
		module->op_devices |= (GBAUDIO_DEVICE_OUT_WIRED_HEADSET
					| GBAUDIO_DEVICE_OUT_WIRED_HEADPHONE);
		module->ip_devices |= GBAUDIO_DEVICE_IN_WIRED_HEADSET;
		अवरोध;
	हाल snd_soc_dapm_mic:
		*dw = (काष्ठा snd_soc_dapm_widget)
			SND_SOC_DAPM_MIC(w->name, gbcodec_event_पूर्णांक_mic);
		module->ip_devices |= GBAUDIO_DEVICE_IN_BUILTIN_MIC;
		अवरोध;
	हाल snd_soc_dapm_output:
		*dw = (काष्ठा snd_soc_dapm_widget)SND_SOC_DAPM_OUTPUT(w->name);
		अवरोध;
	हाल snd_soc_dapm_input:
		*dw = (काष्ठा snd_soc_dapm_widget)SND_SOC_DAPM_INPUT(w->name);
		अवरोध;
	हाल snd_soc_dapm_चयन:
		*dw = (काष्ठा snd_soc_dapm_widget)
			SND_SOC_DAPM_SWITCH_E(w->name, SND_SOC_NOPM, 0, 0,
					      widget_kctls,
					      gbaudio_widget_event,
					      SND_SOC_DAPM_PRE_PMU |
					      SND_SOC_DAPM_POST_PMD);
		अवरोध;
	हाल snd_soc_dapm_pga:
		*dw = (काष्ठा snd_soc_dapm_widget)
			SND_SOC_DAPM_PGA_E(w->name, SND_SOC_NOPM, 0, 0, शून्य, 0,
					   gbaudio_widget_event,
					   SND_SOC_DAPM_PRE_PMU |
					   SND_SOC_DAPM_POST_PMD);
		अवरोध;
	हाल snd_soc_dapm_mixer:
		*dw = (काष्ठा snd_soc_dapm_widget)
			SND_SOC_DAPM_MIXER_E(w->name, SND_SOC_NOPM, 0, 0, शून्य,
					     0, gbaudio_widget_event,
					     SND_SOC_DAPM_PRE_PMU |
					     SND_SOC_DAPM_POST_PMD);
		अवरोध;
	हाल snd_soc_dapm_mux:
		*dw = (काष्ठा snd_soc_dapm_widget)
			SND_SOC_DAPM_MUX_E(w->name, SND_SOC_NOPM, 0, 0,
					   widget_kctls, gbaudio_widget_event,
					   SND_SOC_DAPM_PRE_PMU |
					   SND_SOC_DAPM_POST_PMD);
		अवरोध;
	हाल snd_soc_dapm_aअगर_in:
		*dw = (काष्ठा snd_soc_dapm_widget)
			SND_SOC_DAPM_AIF_IN_E(w->name, w->sname, 0,
					      SND_SOC_NOPM,
					      0, 0, gbaudio_widget_event,
					      SND_SOC_DAPM_PRE_PMU |
					      SND_SOC_DAPM_POST_PMD);
		अवरोध;
	हाल snd_soc_dapm_aअगर_out:
		*dw = (काष्ठा snd_soc_dapm_widget)
			SND_SOC_DAPM_AIF_OUT_E(w->name, w->sname, 0,
					       SND_SOC_NOPM,
					       0, 0, gbaudio_widget_event,
					       SND_SOC_DAPM_PRE_PMU |
					       SND_SOC_DAPM_POST_PMD);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	dev_dbg(module->dev, "%s: widget of type %d created\n", dw->name,
		dw->id);
	वापस 0;
error:
	list_क्रम_each_entry_safe(control, _control, &module->widget_ctl_list,
				 list) अणु
		list_del(&control->list);
		devm_kमुक्त(module->dev, control);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gbaudio_tplg_process_kcontrols(काष्ठा gbaudio_module_info *module,
					  काष्ठा gb_audio_control *controls)
अणु
	पूर्णांक i, csize, ret;
	काष्ठा snd_kcontrol_new *dapm_kctls;
	काष्ठा gb_audio_control *curr;
	काष्ठा gbaudio_control *control, *_control;
	माप_प्रकार size;
	अक्षर temp_name[NAME_SIZE];

	size = माप(काष्ठा snd_kcontrol_new) * module->num_controls;
	dapm_kctls = devm_kzalloc(module->dev, size, GFP_KERNEL);
	अगर (!dapm_kctls)
		वापस -ENOMEM;

	curr = controls;
	क्रम (i = 0; i < module->num_controls; i++) अणु
		ret = gbaudio_tplg_create_kcontrol(module, &dapm_kctls[i],
						   curr);
		अगर (ret) अणु
			dev_err(module->dev, "%s:%d type not supported\n",
				curr->name, curr->अगरace);
			जाओ error;
		पूर्ण
		control = devm_kzalloc(module->dev, माप(काष्ठा
							   gbaudio_control),
				      GFP_KERNEL);
		अगर (!control) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		control->id = curr->id;
		/* Prefix dev_id to widget_name */
		strscpy(temp_name, curr->name, माप(temp_name));
		snम_लिखो(curr->name, माप(curr->name), "GB %d %s", module->dev_id,
			 temp_name);
		control->name = curr->name;
		अगर (curr->info.type == GB_AUDIO_CTL_ELEM_TYPE_ENUMERATED) अणु
			काष्ठा gb_audio_क्रमागतerated *gbक्रमागत =
				&curr->info.value.क्रमागतerated;

			csize = दुरत्व(काष्ठा gb_audio_control, info);
			csize += दुरत्व(काष्ठा gb_audio_ctl_elem_info, value);
			csize += दुरत्व(काष्ठा gb_audio_क्रमागतerated, names);
			csize += le16_to_cpu(gbक्रमागत->names_length);
			control->texts = (स्थिर अक्षर * स्थिर *)
				gb_generate_क्रमागत_strings(module, gbक्रमागत);
			control->items = le32_to_cpu(gbक्रमागत->items);
		पूर्ण अन्यथा अणु
			csize = माप(काष्ठा gb_audio_control);
		पूर्ण

		list_add(&control->list, &module->ctl_list);
		dev_dbg(module->dev, "%d:%s created of type %d\n", curr->id,
			curr->name, curr->info.type);
		curr = (व्योम *)curr + csize;
	पूर्ण
	module->controls = dapm_kctls;

	वापस 0;
error:
	list_क्रम_each_entry_safe(control, _control, &module->ctl_list,
				 list) अणु
		list_del(&control->list);
		devm_kमुक्त(module->dev, control);
	पूर्ण
	devm_kमुक्त(module->dev, dapm_kctls);
	वापस ret;
पूर्ण

अटल पूर्णांक gbaudio_tplg_process_widमाला_लो(काष्ठा gbaudio_module_info *module,
					काष्ठा gb_audio_widget *widमाला_लो)
अणु
	पूर्णांक i, ret, w_size;
	काष्ठा snd_soc_dapm_widget *dapm_widमाला_लो;
	काष्ठा gb_audio_widget *curr;
	काष्ठा gbaudio_widget *widget, *_widget;
	माप_प्रकार size;

	size = माप(काष्ठा snd_soc_dapm_widget) * module->num_dapm_widमाला_लो;
	dapm_widमाला_लो = devm_kzalloc(module->dev, size, GFP_KERNEL);
	अगर (!dapm_widमाला_लो)
		वापस -ENOMEM;

	curr = widमाला_लो;
	क्रम (i = 0; i < module->num_dapm_widमाला_लो; i++) अणु
		ret = gbaudio_tplg_create_widget(module, &dapm_widमाला_लो[i],
						 curr, &w_size);
		अगर (ret) अणु
			dev_err(module->dev, "%s:%d type not supported\n",
				curr->name, curr->type);
			जाओ error;
		पूर्ण
		widget = devm_kzalloc(module->dev, माप(काष्ठा
							   gbaudio_widget),
				      GFP_KERNEL);
		अगर (!widget) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
		widget->id = curr->id;
		widget->name = curr->name;
		list_add(&widget->list, &module->widget_list);
		curr = (व्योम *)curr + w_size;
	पूर्ण
	module->dapm_widमाला_लो = dapm_widमाला_लो;

	वापस 0;

error:
	list_क्रम_each_entry_safe(widget, _widget, &module->widget_list,
				 list) अणु
		list_del(&widget->list);
		devm_kमुक्त(module->dev, widget);
	पूर्ण
	devm_kमुक्त(module->dev, dapm_widमाला_लो);
	वापस ret;
पूर्ण

अटल पूर्णांक gbaudio_tplg_process_routes(काष्ठा gbaudio_module_info *module,
				       काष्ठा gb_audio_route *routes)
अणु
	पूर्णांक i, ret;
	काष्ठा snd_soc_dapm_route *dapm_routes;
	काष्ठा gb_audio_route *curr;
	माप_प्रकार size;

	size = माप(काष्ठा snd_soc_dapm_route) * module->num_dapm_routes;
	dapm_routes = devm_kzalloc(module->dev, size, GFP_KERNEL);
	अगर (!dapm_routes)
		वापस -ENOMEM;

	module->dapm_routes = dapm_routes;
	curr = routes;

	क्रम (i = 0; i < module->num_dapm_routes; i++) अणु
		dapm_routes->sink =
			gbaudio_map_widgetid(module, curr->destination_id);
		अगर (!dapm_routes->sink) अणु
			dev_err(module->dev, "%d:%d:%d:%d - Invalid sink\n",
				curr->source_id, curr->destination_id,
				curr->control_id, curr->index);
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		dapm_routes->source =
			gbaudio_map_widgetid(module, curr->source_id);
		अगर (!dapm_routes->source) अणु
			dev_err(module->dev, "%d:%d:%d:%d - Invalid source\n",
				curr->source_id, curr->destination_id,
				curr->control_id, curr->index);
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		dapm_routes->control =
			gbaudio_map_controlid(module,
					      curr->control_id,
					      curr->index);
		अगर ((curr->control_id !=  GBAUDIO_INVALID_ID) &&
		    !dapm_routes->control) अणु
			dev_err(module->dev, "%d:%d:%d:%d - Invalid control\n",
				curr->source_id, curr->destination_id,
				curr->control_id, curr->index);
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		dev_dbg(module->dev, "Route {%s, %s, %s}\n", dapm_routes->sink,
			(dapm_routes->control) ? dapm_routes->control : "NULL",
			dapm_routes->source);
		dapm_routes++;
		curr++;
	पूर्ण

	वापस 0;

error:
	devm_kमुक्त(module->dev, module->dapm_routes);
	वापस ret;
पूर्ण

अटल पूर्णांक gbaudio_tplg_process_header(काष्ठा gbaudio_module_info *module,
				       काष्ठा gb_audio_topology *tplg_data)
अणु
	/* fetch no. of kcontrols, widमाला_लो & routes */
	module->num_controls = tplg_data->num_controls;
	module->num_dapm_widमाला_लो = tplg_data->num_widमाला_लो;
	module->num_dapm_routes = tplg_data->num_routes;

	/* update block offset */
	module->dai_offset = (अचिन्हित दीर्घ)&tplg_data->data;
	module->control_offset = module->dai_offset +
					le32_to_cpu(tplg_data->size_dais);
	module->widget_offset = module->control_offset +
					le32_to_cpu(tplg_data->size_controls);
	module->route_offset = module->widget_offset +
					le32_to_cpu(tplg_data->size_widमाला_लो);

	dev_dbg(module->dev, "DAI offset is 0x%lx\n", module->dai_offset);
	dev_dbg(module->dev, "control offset is %lx\n",
		module->control_offset);
	dev_dbg(module->dev, "widget offset is %lx\n", module->widget_offset);
	dev_dbg(module->dev, "route offset is %lx\n", module->route_offset);

	वापस 0;
पूर्ण

पूर्णांक gbaudio_tplg_parse_data(काष्ठा gbaudio_module_info *module,
			    काष्ठा gb_audio_topology *tplg_data)
अणु
	पूर्णांक ret;
	काष्ठा gb_audio_control *controls;
	काष्ठा gb_audio_widget *widमाला_लो;
	काष्ठा gb_audio_route *routes;
	अचिन्हित पूर्णांक jack_type;

	अगर (!tplg_data)
		वापस -EINVAL;

	ret = gbaudio_tplg_process_header(module, tplg_data);
	अगर (ret) अणु
		dev_err(module->dev, "%d: Error in parsing topology header\n",
			ret);
		वापस ret;
	पूर्ण

	/* process control */
	controls = (काष्ठा gb_audio_control *)module->control_offset;
	ret = gbaudio_tplg_process_kcontrols(module, controls);
	अगर (ret) अणु
		dev_err(module->dev,
			"%d: Error in parsing controls data\n", ret);
		वापस ret;
	पूर्ण
	dev_dbg(module->dev, "Control parsing finished\n");

	/* process widमाला_लो */
	widमाला_लो = (काष्ठा gb_audio_widget *)module->widget_offset;
	ret = gbaudio_tplg_process_widमाला_लो(module, widमाला_लो);
	अगर (ret) अणु
		dev_err(module->dev,
			"%d: Error in parsing widgets data\n", ret);
		वापस ret;
	पूर्ण
	dev_dbg(module->dev, "Widget parsing finished\n");

	/* process route */
	routes = (काष्ठा gb_audio_route *)module->route_offset;
	ret = gbaudio_tplg_process_routes(module, routes);
	अगर (ret) अणु
		dev_err(module->dev,
			"%d: Error in parsing routes data\n", ret);
		वापस ret;
	पूर्ण
	dev_dbg(module->dev, "Route parsing finished\n");

	/* parse jack capabilities */
	jack_type = le32_to_cpu(tplg_data->jack_type);
	अगर (jack_type) अणु
		module->jack_mask = jack_type & GBCODEC_JACK_MASK;
		module->button_mask = jack_type & GBCODEC_JACK_BUTTON_MASK;
	पूर्ण

	वापस ret;
पूर्ण

व्योम gbaudio_tplg_release(काष्ठा gbaudio_module_info *module)
अणु
	काष्ठा gbaudio_control *control, *_control;
	काष्ठा gbaudio_widget *widget, *_widget;

	अगर (!module->topology)
		वापस;

	/* release kcontrols */
	list_क्रम_each_entry_safe(control, _control, &module->ctl_list,
				 list) अणु
		list_del(&control->list);
		devm_kमुक्त(module->dev, control);
	पूर्ण
	अगर (module->controls)
		devm_kमुक्त(module->dev, module->controls);

	/* release widget controls */
	list_क्रम_each_entry_safe(control, _control, &module->widget_ctl_list,
				 list) अणु
		list_del(&control->list);
		devm_kमुक्त(module->dev, control);
	पूर्ण

	/* release widमाला_लो */
	list_क्रम_each_entry_safe(widget, _widget, &module->widget_list,
				 list) अणु
		list_del(&widget->list);
		devm_kमुक्त(module->dev, widget);
	पूर्ण
	अगर (module->dapm_widमाला_लो)
		devm_kमुक्त(module->dev, module->dapm_widमाला_लो);

	/* release routes */
	अगर (module->dapm_routes)
		devm_kमुक्त(module->dev, module->dapm_routes);
पूर्ण
