<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-dapm.c  --  ALSA SoC Dynamic Audio Power Management
//
// Copyright 2005 Wolfson Microelectronics PLC.
// Author: Liam Girdwood <lrg@slimlogic.co.uk>
//
//  Features:
//    o Changes घातer status of पूर्णांकernal codec blocks depending on the
//      dynamic configuration of codec पूर्णांकernal audio paths and active
//      DACs/ADCs.
//    o Platक्रमm घातer करोमुख्य - can support बाह्यal components i.e. amps and
//      mic/headphone insertion events.
//    o Automatic Mic Bias support
//    o Jack insertion घातer event initiation - e.g. hp insertion will enable
//      sinks, dacs, etc
//    o Delayed घातer करोwn of audio subप्रणाली to reduce pops between a quick
//      device reखोलो.

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/async.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#समावेश <trace/events/asoc.h>

#घोषणा DAPM_UPDATE_STAT(widget, val) widget->dapm->card->dapm_stats.val++;

#घोषणा SND_SOC_DAPM_सूची_REVERSE(x) ((x == SND_SOC_DAPM_सूची_IN) ? \
	SND_SOC_DAPM_सूची_OUT : SND_SOC_DAPM_सूची_IN)

#घोषणा snd_soc_dapm_क्रम_each_direction(dir) \
	क्रम ((dir) = SND_SOC_DAPM_सूची_IN; (dir) <= SND_SOC_DAPM_सूची_OUT; \
		(dir)++)

अटल पूर्णांक snd_soc_dapm_add_path(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा snd_soc_dapm_widget *wsource, काष्ठा snd_soc_dapm_widget *wsink,
	स्थिर अक्षर *control,
	पूर्णांक (*connected)(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink));

काष्ठा snd_soc_dapm_widget *
snd_soc_dapm_new_control(काष्ठा snd_soc_dapm_context *dapm,
			 स्थिर काष्ठा snd_soc_dapm_widget *widget);

काष्ठा snd_soc_dapm_widget *
snd_soc_dapm_new_control_unlocked(काष्ठा snd_soc_dapm_context *dapm,
			 स्थिर काष्ठा snd_soc_dapm_widget *widget);

/* dapm घातer sequences - make this per codec in the future */
अटल पूर्णांक dapm_up_seq[] = अणु
	[snd_soc_dapm_pre] = 1,
	[snd_soc_dapm_regulator_supply] = 2,
	[snd_soc_dapm_pinctrl] = 2,
	[snd_soc_dapm_घड़ी_supply] = 2,
	[snd_soc_dapm_supply] = 3,
	[snd_soc_dapm_micbias] = 4,
	[snd_soc_dapm_vmid] = 4,
	[snd_soc_dapm_dai_link] = 3,
	[snd_soc_dapm_dai_in] = 5,
	[snd_soc_dapm_dai_out] = 5,
	[snd_soc_dapm_aअगर_in] = 5,
	[snd_soc_dapm_aअगर_out] = 5,
	[snd_soc_dapm_mic] = 6,
	[snd_soc_dapm_siggen] = 6,
	[snd_soc_dapm_input] = 6,
	[snd_soc_dapm_output] = 6,
	[snd_soc_dapm_mux] = 7,
	[snd_soc_dapm_demux] = 7,
	[snd_soc_dapm_dac] = 8,
	[snd_soc_dapm_चयन] = 9,
	[snd_soc_dapm_mixer] = 9,
	[snd_soc_dapm_mixer_named_ctl] = 9,
	[snd_soc_dapm_pga] = 10,
	[snd_soc_dapm_buffer] = 10,
	[snd_soc_dapm_scheduler] = 10,
	[snd_soc_dapm_effect] = 10,
	[snd_soc_dapm_src] = 10,
	[snd_soc_dapm_asrc] = 10,
	[snd_soc_dapm_encoder] = 10,
	[snd_soc_dapm_decoder] = 10,
	[snd_soc_dapm_adc] = 11,
	[snd_soc_dapm_out_drv] = 12,
	[snd_soc_dapm_hp] = 12,
	[snd_soc_dapm_spk] = 12,
	[snd_soc_dapm_line] = 12,
	[snd_soc_dapm_sink] = 12,
	[snd_soc_dapm_kcontrol] = 13,
	[snd_soc_dapm_post] = 14,
पूर्ण;

अटल पूर्णांक dapm_करोwn_seq[] = अणु
	[snd_soc_dapm_pre] = 1,
	[snd_soc_dapm_kcontrol] = 2,
	[snd_soc_dapm_adc] = 3,
	[snd_soc_dapm_hp] = 4,
	[snd_soc_dapm_spk] = 4,
	[snd_soc_dapm_line] = 4,
	[snd_soc_dapm_out_drv] = 4,
	[snd_soc_dapm_sink] = 4,
	[snd_soc_dapm_pga] = 5,
	[snd_soc_dapm_buffer] = 5,
	[snd_soc_dapm_scheduler] = 5,
	[snd_soc_dapm_effect] = 5,
	[snd_soc_dapm_src] = 5,
	[snd_soc_dapm_asrc] = 5,
	[snd_soc_dapm_encoder] = 5,
	[snd_soc_dapm_decoder] = 5,
	[snd_soc_dapm_चयन] = 6,
	[snd_soc_dapm_mixer_named_ctl] = 6,
	[snd_soc_dapm_mixer] = 6,
	[snd_soc_dapm_dac] = 7,
	[snd_soc_dapm_mic] = 8,
	[snd_soc_dapm_siggen] = 8,
	[snd_soc_dapm_input] = 8,
	[snd_soc_dapm_output] = 8,
	[snd_soc_dapm_micbias] = 9,
	[snd_soc_dapm_vmid] = 9,
	[snd_soc_dapm_mux] = 10,
	[snd_soc_dapm_demux] = 10,
	[snd_soc_dapm_aअगर_in] = 11,
	[snd_soc_dapm_aअगर_out] = 11,
	[snd_soc_dapm_dai_in] = 11,
	[snd_soc_dapm_dai_out] = 11,
	[snd_soc_dapm_dai_link] = 12,
	[snd_soc_dapm_supply] = 13,
	[snd_soc_dapm_घड़ी_supply] = 14,
	[snd_soc_dapm_pinctrl] = 14,
	[snd_soc_dapm_regulator_supply] = 14,
	[snd_soc_dapm_post] = 15,
पूर्ण;

अटल व्योम dapm_निश्चित_locked(काष्ठा snd_soc_dapm_context *dapm)
अणु
	अगर (dapm->card && dapm->card->instantiated)
		lockdep_निश्चित_held(&dapm->card->dapm_mutex);
पूर्ण

अटल व्योम pop_रुको(u32 pop_समय)
अणु
	अगर (pop_समय)
		schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(pop_समय));
पूर्ण

__म_लिखो(3, 4)
अटल व्योम pop_dbg(काष्ठा device *dev, u32 pop_समय, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर *buf;

	अगर (!pop_समय)
		वापस;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस;

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, PAGE_SIZE, fmt, args);
	dev_info(dev, "%s", buf);
	बहु_पूर्ण(args);

	kमुक्त(buf);
पूर्ण

अटल bool dapm_dirty_widget(काष्ठा snd_soc_dapm_widget *w)
अणु
	वापस !list_empty(&w->dirty);
पूर्ण

अटल व्योम dapm_mark_dirty(काष्ठा snd_soc_dapm_widget *w, स्थिर अक्षर *reason)
अणु
	dapm_निश्चित_locked(w->dapm);

	अगर (!dapm_dirty_widget(w)) अणु
		dev_vdbg(w->dapm->dev, "Marking %s dirty due to %s\n",
			 w->name, reason);
		list_add_tail(&w->dirty, &w->dapm->card->dapm_dirty);
	पूर्ण
पूर्ण

/*
 * Common implementation क्रम dapm_widget_invalidate_input_paths() and
 * dapm_widget_invalidate_output_paths(). The function is अंतरभूतd since the
 * combined size of the two specialized functions is only marginally larger then
 * the size of the generic function and at the same समय the fast path of the
 * specialized functions is signअगरicantly smaller than the generic function.
 */
अटल __always_अंतरभूत व्योम dapm_widget_invalidate_paths(
	काष्ठा snd_soc_dapm_widget *w, क्रमागत snd_soc_dapm_direction dir)
अणु
	क्रमागत snd_soc_dapm_direction rdir = SND_SOC_DAPM_सूची_REVERSE(dir);
	काष्ठा snd_soc_dapm_widget *node;
	काष्ठा snd_soc_dapm_path *p;
	LIST_HEAD(list);

	dapm_निश्चित_locked(w->dapm);

	अगर (w->endpoपूर्णांकs[dir] == -1)
		वापस;

	list_add_tail(&w->work_list, &list);
	w->endpoपूर्णांकs[dir] = -1;

	list_क्रम_each_entry(w, &list, work_list) अणु
		snd_soc_dapm_widget_क्रम_each_path(w, dir, p) अणु
			अगर (p->is_supply || p->weak || !p->connect)
				जारी;
			node = p->node[rdir];
			अगर (node->endpoपूर्णांकs[dir] != -1) अणु
				node->endpoपूर्णांकs[dir] = -1;
				list_add_tail(&node->work_list, &list);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * dapm_widget_invalidate_input_paths() - Invalidate the cached number of
 *  input paths
 * @w: The widget क्रम which to invalidate the cached number of input paths
 *
 * Resets the cached number of inमाला_दो क्रम the specअगरied widget and all widमाला_लो
 * that can be reached via outcoming paths from the widget.
 *
 * This function must be called अगर the number of output paths क्रम a widget might
 * have changed. E.g. अगर the source state of a widget changes or a path is added
 * or activated with the widget as the sink.
 */
अटल व्योम dapm_widget_invalidate_input_paths(काष्ठा snd_soc_dapm_widget *w)
अणु
	dapm_widget_invalidate_paths(w, SND_SOC_DAPM_सूची_IN);
पूर्ण

/*
 * dapm_widget_invalidate_output_paths() - Invalidate the cached number of
 *  output paths
 * @w: The widget क्रम which to invalidate the cached number of output paths
 *
 * Resets the cached number of outमाला_दो क्रम the specअगरied widget and all widमाला_लो
 * that can be reached via incoming paths from the widget.
 *
 * This function must be called अगर the number of output paths क्रम a widget might
 * have changed. E.g. अगर the sink state of a widget changes or a path is added
 * or activated with the widget as the source.
 */
अटल व्योम dapm_widget_invalidate_output_paths(काष्ठा snd_soc_dapm_widget *w)
अणु
	dapm_widget_invalidate_paths(w, SND_SOC_DAPM_सूची_OUT);
पूर्ण

/*
 * dapm_path_invalidate() - Invalidates the cached number of inमाला_दो and outमाला_दो
 *  क्रम the widमाला_लो connected to a path
 * @p: The path to invalidate
 *
 * Resets the cached number of inमाला_दो क्रम the sink of the path and the cached
 * number of outमाला_दो क्रम the source of the path.
 *
 * This function must be called when a path is added, हटाओd or the connected
 * state changes.
 */
अटल व्योम dapm_path_invalidate(काष्ठा snd_soc_dapm_path *p)
अणु
	/*
	 * Weak paths or supply paths करो not influence the number of input or
	 * output paths of their neighbors.
	 */
	अगर (p->weak || p->is_supply)
		वापस;

	/*
	 * The number of connected endpoपूर्णांकs is the sum of the number of
	 * connected endpoपूर्णांकs of all neighbors. If a node with 0 connected
	 * endpoपूर्णांकs is either connected or disconnected that sum won't change,
	 * so there is no need to re-check the path.
	 */
	अगर (p->source->endpoपूर्णांकs[SND_SOC_DAPM_सूची_IN] != 0)
		dapm_widget_invalidate_input_paths(p->sink);
	अगर (p->sink->endpoपूर्णांकs[SND_SOC_DAPM_सूची_OUT] != 0)
		dapm_widget_invalidate_output_paths(p->source);
पूर्ण

व्योम dapm_mark_endpoपूर्णांकs_dirty(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dapm_widget *w;

	mutex_lock(&card->dapm_mutex);

	क्रम_each_card_widमाला_लो(card, w) अणु
		अगर (w->is_ep) अणु
			dapm_mark_dirty(w, "Rechecking endpoints");
			अगर (w->is_ep & SND_SOC_DAPM_EP_SINK)
				dapm_widget_invalidate_output_paths(w);
			अगर (w->is_ep & SND_SOC_DAPM_EP_SOURCE)
				dapm_widget_invalidate_input_paths(w);
		पूर्ण
	पूर्ण

	mutex_unlock(&card->dapm_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(dapm_mark_endpoपूर्णांकs_dirty);

/* create a new dapm widget */
अटल अंतरभूत काष्ठा snd_soc_dapm_widget *dapm_cnew_widget(
	स्थिर काष्ठा snd_soc_dapm_widget *_widget)
अणु
	काष्ठा snd_soc_dapm_widget *w;

	w = kmemdup(_widget, माप(*_widget), GFP_KERNEL);
	अगर (!w)
		वापस शून्य;

	/*
	 * w->name is duplicated in caller, but w->sname isn't.
	 * Duplicate it here अगर defined
	 */
	अगर (_widget->sname) अणु
		w->sname = kstrdup_स्थिर(_widget->sname, GFP_KERNEL);
		अगर (!w->sname) अणु
			kमुक्त(w);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस w;
पूर्ण

काष्ठा dapm_kcontrol_data अणु
	अचिन्हित पूर्णांक value;
	काष्ठा snd_soc_dapm_widget *widget;
	काष्ठा list_head paths;
	काष्ठा snd_soc_dapm_widget_list *wlist;
पूर्ण;

अटल पूर्णांक dapm_kcontrol_data_alloc(काष्ठा snd_soc_dapm_widget *widget,
	काष्ठा snd_kcontrol *kcontrol, स्थिर अक्षर *ctrl_name)
अणु
	काष्ठा dapm_kcontrol_data *data;
	काष्ठा soc_mixer_control *mc;
	काष्ठा soc_क्रमागत *e;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&data->paths);

	चयन (widget->id) अणु
	हाल snd_soc_dapm_चयन:
	हाल snd_soc_dapm_mixer:
	हाल snd_soc_dapm_mixer_named_ctl:
		mc = (काष्ठा soc_mixer_control *)kcontrol->निजी_value;

		अगर (mc->स्वतःdisable && snd_soc_volsw_is_stereo(mc))
			dev_warn(widget->dapm->dev,
				 "ASoC: Unsupported stereo autodisable control '%s'\n",
				 ctrl_name);

		अगर (mc->स्वतःdisable) अणु
			काष्ठा snd_soc_dapm_widget ढाँचा;

			name = kaप्र_लिखो(GFP_KERNEL, "%s %s", ctrl_name,
					 "Autodisable");
			अगर (!name) अणु
				ret = -ENOMEM;
				जाओ err_data;
			पूर्ण

			स_रखो(&ढाँचा, 0, माप(ढाँचा));
			ढाँचा.reg = mc->reg;
			ढाँचा.mask = (1 << fls(mc->max)) - 1;
			ढाँचा.shअगरt = mc->shअगरt;
			अगर (mc->invert)
				ढाँचा.off_val = mc->max;
			अन्यथा
				ढाँचा.off_val = 0;
			ढाँचा.on_val = ढाँचा.off_val;
			ढाँचा.id = snd_soc_dapm_kcontrol;
			ढाँचा.name = name;

			data->value = ढाँचा.on_val;

			data->widget =
				snd_soc_dapm_new_control_unlocked(widget->dapm,
				&ढाँचा);
			kमुक्त(name);
			अगर (IS_ERR(data->widget)) अणु
				ret = PTR_ERR(data->widget);
				जाओ err_data;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल snd_soc_dapm_demux:
	हाल snd_soc_dapm_mux:
		e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;

		अगर (e->स्वतःdisable) अणु
			काष्ठा snd_soc_dapm_widget ढाँचा;

			name = kaप्र_लिखो(GFP_KERNEL, "%s %s", ctrl_name,
					 "Autodisable");
			अगर (!name) अणु
				ret = -ENOMEM;
				जाओ err_data;
			पूर्ण

			स_रखो(&ढाँचा, 0, माप(ढाँचा));
			ढाँचा.reg = e->reg;
			ढाँचा.mask = e->mask;
			ढाँचा.shअगरt = e->shअगरt_l;
			ढाँचा.off_val = snd_soc_क्रमागत_item_to_val(e, 0);
			ढाँचा.on_val = ढाँचा.off_val;
			ढाँचा.id = snd_soc_dapm_kcontrol;
			ढाँचा.name = name;

			data->value = ढाँचा.on_val;

			data->widget = snd_soc_dapm_new_control_unlocked(
						widget->dapm, &ढाँचा);
			kमुक्त(name);
			अगर (IS_ERR(data->widget)) अणु
				ret = PTR_ERR(data->widget);
				जाओ err_data;
			पूर्ण

			snd_soc_dapm_add_path(widget->dapm, data->widget,
					      widget, शून्य, शून्य);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kcontrol->निजी_data = data;

	वापस 0;

err_data:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल व्योम dapm_kcontrol_मुक्त(काष्ठा snd_kcontrol *kctl)
अणु
	काष्ठा dapm_kcontrol_data *data = snd_kcontrol_chip(kctl);

	list_del(&data->paths);
	kमुक्त(data->wlist);
	kमुक्त(data);
पूर्ण

अटल काष्ठा snd_soc_dapm_widget_list *dapm_kcontrol_get_wlist(
	स्थिर काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);

	वापस data->wlist;
पूर्ण

अटल पूर्णांक dapm_kcontrol_add_widget(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_soc_dapm_widget *widget)
अणु
	काष्ठा dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_widget_list *new_wlist;
	अचिन्हित पूर्णांक n;

	अगर (data->wlist)
		n = data->wlist->num_widमाला_लो + 1;
	अन्यथा
		n = 1;

	new_wlist = kपुनः_स्मृति(data->wlist,
			     काष्ठा_size(new_wlist, widमाला_लो, n),
			     GFP_KERNEL);
	अगर (!new_wlist)
		वापस -ENOMEM;

	new_wlist->widमाला_लो[n - 1] = widget;
	new_wlist->num_widमाला_लो = n;

	data->wlist = new_wlist;

	वापस 0;
पूर्ण

अटल व्योम dapm_kcontrol_add_path(स्थिर काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_soc_dapm_path *path)
अणु
	काष्ठा dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);

	list_add_tail(&path->list_kcontrol, &data->paths);
पूर्ण

अटल bool dapm_kcontrol_is_घातered(स्थिर काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);

	अगर (!data->widget)
		वापस true;

	वापस data->widget->घातer;
पूर्ण

अटल काष्ठा list_head *dapm_kcontrol_get_path_list(
	स्थिर काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);

	वापस &data->paths;
पूर्ण

#घोषणा dapm_kcontrol_क्रम_each_path(path, kcontrol) \
	list_क्रम_each_entry(path, dapm_kcontrol_get_path_list(kcontrol), \
		list_kcontrol)

अचिन्हित पूर्णांक dapm_kcontrol_get_value(स्थिर काष्ठा snd_kcontrol *kcontrol)
अणु
	काष्ठा dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);

	वापस data->value;
पूर्ण
EXPORT_SYMBOL_GPL(dapm_kcontrol_get_value);

अटल bool dapm_kcontrol_set_value(स्थिर काष्ठा snd_kcontrol *kcontrol,
	अचिन्हित पूर्णांक value)
अणु
	काष्ठा dapm_kcontrol_data *data = snd_kcontrol_chip(kcontrol);

	अगर (data->value == value)
		वापस false;

	अगर (data->widget) अणु
		चयन (dapm_kcontrol_get_wlist(kcontrol)->widमाला_लो[0]->id) अणु
		हाल snd_soc_dapm_चयन:
		हाल snd_soc_dapm_mixer:
		हाल snd_soc_dapm_mixer_named_ctl:
			data->widget->on_val = value & data->widget->mask;
			अवरोध;
		हाल snd_soc_dapm_demux:
		हाल snd_soc_dapm_mux:
			data->widget->on_val = value >> data->widget->shअगरt;
			अवरोध;
		शेष:
			data->widget->on_val = value;
			अवरोध;
		पूर्ण
	पूर्ण

	data->value = value;

	वापस true;
पूर्ण

/**
 * snd_soc_dapm_kcontrol_widget() - Returns the widget associated to a
 *   kcontrol
 * @kcontrol: The kcontrol
 */
काष्ठा snd_soc_dapm_widget *snd_soc_dapm_kcontrol_widget(
				काष्ठा snd_kcontrol *kcontrol)
अणु
	वापस dapm_kcontrol_get_wlist(kcontrol)->widमाला_लो[0];
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_kcontrol_widget);

/**
 * snd_soc_dapm_kcontrol_dapm() - Returns the dapm context associated to a
 *  kcontrol
 * @kcontrol: The kcontrol
 *
 * Note: This function must only be used on kcontrols that are known to have
 * been रेजिस्टरed क्रम a CODEC. Otherwise the behaviour is undefined.
 */
काष्ठा snd_soc_dapm_context *snd_soc_dapm_kcontrol_dapm(
	काष्ठा snd_kcontrol *kcontrol)
अणु
	वापस dapm_kcontrol_get_wlist(kcontrol)->widमाला_लो[0]->dapm;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_kcontrol_dapm);

अटल व्योम dapm_reset(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dapm_widget *w;

	lockdep_निश्चित_held(&card->dapm_mutex);

	स_रखो(&card->dapm_stats, 0, माप(card->dapm_stats));

	क्रम_each_card_widमाला_लो(card, w) अणु
		w->new_घातer = w->घातer;
		w->घातer_checked = false;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *soc_dapm_prefix(काष्ठा snd_soc_dapm_context *dapm)
अणु
	अगर (!dapm->component)
		वापस शून्य;
	वापस dapm->component->name_prefix;
पूर्ण

अटल अचिन्हित पूर्णांक soc_dapm_पढ़ो(काष्ठा snd_soc_dapm_context *dapm, पूर्णांक reg)
अणु
	अगर (!dapm->component)
		वापस -EIO;
	वापस  snd_soc_component_पढ़ो(dapm->component, reg);
पूर्ण

अटल पूर्णांक soc_dapm_update_bits(काष्ठा snd_soc_dapm_context *dapm,
	पूर्णांक reg, अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक value)
अणु
	अगर (!dapm->component)
		वापस -EIO;
	वापस snd_soc_component_update_bits(dapm->component, reg,
					     mask, value);
पूर्ण

अटल पूर्णांक soc_dapm_test_bits(काष्ठा snd_soc_dapm_context *dapm,
	पूर्णांक reg, अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक value)
अणु
	अगर (!dapm->component)
		वापस -EIO;
	वापस snd_soc_component_test_bits(dapm->component, reg, mask, value);
पूर्ण

अटल व्योम soc_dapm_async_complete(काष्ठा snd_soc_dapm_context *dapm)
अणु
	अगर (dapm->component)
		snd_soc_component_async_complete(dapm->component);
पूर्ण

अटल काष्ठा snd_soc_dapm_widget *
dapm_wcache_lookup(काष्ठा snd_soc_dapm_wcache *wcache, स्थिर अक्षर *name)
अणु
	काष्ठा snd_soc_dapm_widget *w = wcache->widget;
	काष्ठा list_head *wlist;
	स्थिर पूर्णांक depth = 2;
	पूर्णांक i = 0;

	अगर (w) अणु
		wlist = &w->dapm->card->widमाला_लो;

		list_क्रम_each_entry_from(w, wlist, list) अणु
			अगर (!म_भेद(name, w->name))
				वापस w;

			अगर (++i == depth)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम dapm_wcache_update(काष्ठा snd_soc_dapm_wcache *wcache,
				      काष्ठा snd_soc_dapm_widget *w)
अणु
	wcache->widget = w;
पूर्ण

/**
 * snd_soc_dapm_क्रमce_bias_level() - Sets the DAPM bias level
 * @dapm: The DAPM context क्रम which to set the level
 * @level: The level to set
 *
 * Forces the DAPM bias level to a specअगरic state. It will call the bias level
 * callback of DAPM context with the specअगरied level. This will even happen अगर
 * the context is alपढ़ोy at the same level. Furthermore it will not go through
 * the normal bias level sequencing, meaning any पूर्णांकermediate states between the
 * current and the target state will not be entered.
 *
 * Note that the change in bias level is only temporary and the next समय
 * snd_soc_dapm_sync() is called the state will be set to the level as
 * determined by the DAPM core. The function is मुख्यly पूर्णांकended to be used to
 * used during probe or resume from suspend to घातer up the device so
 * initialization can be करोne, beक्रमe the DAPM core takes over.
 */
पूर्णांक snd_soc_dapm_क्रमce_bias_level(काष्ठा snd_soc_dapm_context *dapm,
	क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक ret = 0;

	अगर (dapm->component)
		ret = snd_soc_component_set_bias_level(dapm->component, level);

	अगर (ret == 0)
		dapm->bias_level = level;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_क्रमce_bias_level);

/**
 * snd_soc_dapm_set_bias_level - set the bias level क्रम the प्रणाली
 * @dapm: DAPM context
 * @level: level to configure
 *
 * Configure the bias (घातer) levels क्रम the SoC audio device.
 *
 * Returns 0 क्रम success अन्यथा error.
 */
अटल पूर्णांक snd_soc_dapm_set_bias_level(काष्ठा snd_soc_dapm_context *dapm,
				       क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_card *card = dapm->card;
	पूर्णांक ret = 0;

	trace_snd_soc_bias_level_start(card, level);

	ret = snd_soc_card_set_bias_level(card, dapm, level);
	अगर (ret != 0)
		जाओ out;

	अगर (!card || dapm != &card->dapm)
		ret = snd_soc_dapm_क्रमce_bias_level(dapm, level);

	अगर (ret != 0)
		जाओ out;

	ret = snd_soc_card_set_bias_level_post(card, dapm, level);
out:
	trace_snd_soc_bias_level_करोne(card, level);

	वापस ret;
पूर्ण

/* connect mux widget to its पूर्णांकerconnecting audio paths */
अटल पूर्णांक dapm_connect_mux(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा snd_soc_dapm_path *path, स्थिर अक्षर *control_name,
	काष्ठा snd_soc_dapm_widget *w)
अणु
	स्थिर काष्ठा snd_kcontrol_new *kcontrol = &w->kcontrol_news[0];
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val, item;
	पूर्णांक i;

	अगर (e->reg != SND_SOC_NOPM) अणु
		val = soc_dapm_पढ़ो(dapm, e->reg);
		val = (val >> e->shअगरt_l) & e->mask;
		item = snd_soc_क्रमागत_val_to_item(e, val);
	पूर्ण अन्यथा अणु
		/* since a भव mux has no backing रेजिस्टरs to
		 * decide which path to connect, it will try to match
		 * with the first क्रमागतeration.  This is to ensure
		 * that the शेष mux choice (the first) will be
		 * correctly घातered up during initialization.
		 */
		item = 0;
	पूर्ण

	i = match_string(e->texts, e->items, control_name);
	अगर (i < 0)
		वापस -ENODEV;

	path->name = e->texts[i];
	path->connect = (i == item);
	वापस 0;

पूर्ण

/* set up initial codec paths */
अटल व्योम dapm_set_mixer_path_status(काष्ठा snd_soc_dapm_path *p, पूर्णांक i,
				       पूर्णांक nth_path)
अणु
	काष्ठा soc_mixer_control *mc = (काष्ठा soc_mixer_control *)
		p->sink->kcontrol_news[i].निजी_value;
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक max = mc->max;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	अचिन्हित पूर्णांक invert = mc->invert;
	अचिन्हित पूर्णांक val;

	अगर (reg != SND_SOC_NOPM) अणु
		val = soc_dapm_पढ़ो(p->sink->dapm, reg);
		/*
		 * The nth_path argument allows this function to know
		 * which path of a kcontrol it is setting the initial
		 * status क्रम. Ideally this would support any number
		 * of paths and channels. But since kcontrols only come
		 * in mono and stereo variants, we are limited to 2
		 * channels.
		 *
		 * The following code assumes क्रम stereo controls the
		 * first path is the left channel, and all reमुख्यing
		 * paths are the right channel.
		 */
		अगर (snd_soc_volsw_is_stereo(mc) && nth_path > 0) अणु
			अगर (reg != mc->rreg)
				val = soc_dapm_पढ़ो(p->sink->dapm, mc->rreg);
			val = (val >> mc->rshअगरt) & mask;
		पूर्ण अन्यथा अणु
			val = (val >> shअगरt) & mask;
		पूर्ण
		अगर (invert)
			val = max - val;
		p->connect = !!val;
	पूर्ण अन्यथा अणु
		/* since a भव mixer has no backing रेजिस्टरs to
		 * decide which path to connect, it will try to match
		 * with initial state.  This is to ensure
		 * that the शेष mixer choice will be
		 * correctly घातered up during initialization.
		 */
		p->connect = invert;
	पूर्ण
पूर्ण

/* connect mixer widget to its पूर्णांकerconnecting audio paths */
अटल पूर्णांक dapm_connect_mixer(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा snd_soc_dapm_path *path, स्थिर अक्षर *control_name)
अणु
	पूर्णांक i, nth_path = 0;

	/* search क्रम mixer kcontrol */
	क्रम (i = 0; i < path->sink->num_kcontrols; i++) अणु
		अगर (!म_भेद(control_name, path->sink->kcontrol_news[i].name)) अणु
			path->name = path->sink->kcontrol_news[i].name;
			dapm_set_mixer_path_status(path, i, nth_path++);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक dapm_is_shared_kcontrol(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा snd_soc_dapm_widget *kcontrolw,
	स्थिर काष्ठा snd_kcontrol_new *kcontrol_new,
	काष्ठा snd_kcontrol **kcontrol)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	पूर्णांक i;

	*kcontrol = शून्य;

	क्रम_each_card_widमाला_लो(dapm->card, w) अणु
		अगर (w == kcontrolw || w->dapm != kcontrolw->dapm)
			जारी;
		क्रम (i = 0; i < w->num_kcontrols; i++) अणु
			अगर (&w->kcontrol_news[i] == kcontrol_new) अणु
				अगर (w->kcontrols)
					*kcontrol = w->kcontrols[i];
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Determine अगर a kcontrol is shared. If it is, look it up. If it isn't,
 * create it. Either way, add the widget पूर्णांकo the control's widget list
 */
अटल पूर्णांक dapm_create_or_share_kcontrol(काष्ठा snd_soc_dapm_widget *w,
	पूर्णांक kci)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_card *card = dapm->card->snd_card;
	स्थिर अक्षर *prefix;
	माप_प्रकार prefix_len;
	पूर्णांक shared;
	काष्ठा snd_kcontrol *kcontrol;
	bool wname_in_दीर्घ_name, kcname_in_दीर्घ_name;
	अक्षर *दीर्घ_name = शून्य;
	स्थिर अक्षर *name;
	पूर्णांक ret = 0;

	prefix = soc_dapm_prefix(dapm);
	अगर (prefix)
		prefix_len = म_माप(prefix) + 1;
	अन्यथा
		prefix_len = 0;

	shared = dapm_is_shared_kcontrol(dapm, w, &w->kcontrol_news[kci],
					 &kcontrol);

	अगर (!kcontrol) अणु
		अगर (shared) अणु
			wname_in_दीर्घ_name = false;
			kcname_in_दीर्घ_name = true;
		पूर्ण अन्यथा अणु
			चयन (w->id) अणु
			हाल snd_soc_dapm_चयन:
			हाल snd_soc_dapm_mixer:
			हाल snd_soc_dapm_pga:
			हाल snd_soc_dapm_effect:
			हाल snd_soc_dapm_out_drv:
				wname_in_दीर्घ_name = true;
				kcname_in_दीर्घ_name = true;
				अवरोध;
			हाल snd_soc_dapm_mixer_named_ctl:
				wname_in_दीर्घ_name = false;
				kcname_in_दीर्घ_name = true;
				अवरोध;
			हाल snd_soc_dapm_demux:
			हाल snd_soc_dapm_mux:
				wname_in_दीर्घ_name = true;
				kcname_in_दीर्घ_name = false;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (wname_in_दीर्घ_name && kcname_in_दीर्घ_name) अणु
			/*
			 * The control will get a prefix from the control
			 * creation process but we're also using the same
			 * prefix क्रम widमाला_लो so cut the prefix off the
			 * front of the widget name.
			 */
			दीर्घ_name = kaप्र_लिखो(GFP_KERNEL, "%s %s",
				 w->name + prefix_len,
				 w->kcontrol_news[kci].name);
			अगर (दीर्घ_name == शून्य)
				वापस -ENOMEM;

			name = दीर्घ_name;
		पूर्ण अन्यथा अगर (wname_in_दीर्घ_name) अणु
			दीर्घ_name = शून्य;
			name = w->name + prefix_len;
		पूर्ण अन्यथा अणु
			दीर्घ_name = शून्य;
			name = w->kcontrol_news[kci].name;
		पूर्ण

		kcontrol = snd_soc_cnew(&w->kcontrol_news[kci], शून्य, name,
					prefix);
		अगर (!kcontrol) अणु
			ret = -ENOMEM;
			जाओ निकास_मुक्त;
		पूर्ण

		kcontrol->निजी_मुक्त = dapm_kcontrol_मुक्त;

		ret = dapm_kcontrol_data_alloc(w, kcontrol, name);
		अगर (ret) अणु
			snd_ctl_मुक्त_one(kcontrol);
			जाओ निकास_मुक्त;
		पूर्ण

		ret = snd_ctl_add(card, kcontrol);
		अगर (ret < 0) अणु
			dev_err(dapm->dev,
				"ASoC: failed to add widget %s dapm kcontrol %s: %d\n",
				w->name, name, ret);
			जाओ निकास_मुक्त;
		पूर्ण
	पूर्ण

	ret = dapm_kcontrol_add_widget(kcontrol, w);
	अगर (ret == 0)
		w->kcontrols[kci] = kcontrol;

निकास_मुक्त:
	kमुक्त(दीर्घ_name);

	वापस ret;
पूर्ण

/* create new dapm mixer control */
अटल पूर्णांक dapm_new_mixer(काष्ठा snd_soc_dapm_widget *w)
अणु
	पूर्णांक i, ret;
	काष्ठा snd_soc_dapm_path *path;
	काष्ठा dapm_kcontrol_data *data;

	/* add kcontrol */
	क्रम (i = 0; i < w->num_kcontrols; i++) अणु
		/* match name */
		snd_soc_dapm_widget_क्रम_each_source_path(w, path) अणु
			/* mixer/mux paths name must match control name */
			अगर (path->name != (अक्षर *)w->kcontrol_news[i].name)
				जारी;

			अगर (!w->kcontrols[i]) अणु
				ret = dapm_create_or_share_kcontrol(w, i);
				अगर (ret < 0)
					वापस ret;
			पूर्ण

			dapm_kcontrol_add_path(w->kcontrols[i], path);

			data = snd_kcontrol_chip(w->kcontrols[i]);
			अगर (data->widget)
				snd_soc_dapm_add_path(data->widget->dapm,
						      data->widget,
						      path->source,
						      शून्य, शून्य);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* create new dapm mux control */
अटल पूर्णांक dapm_new_mux(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	क्रमागत snd_soc_dapm_direction dir;
	काष्ठा snd_soc_dapm_path *path;
	स्थिर अक्षर *type;
	पूर्णांक ret;

	चयन (w->id) अणु
	हाल snd_soc_dapm_mux:
		dir = SND_SOC_DAPM_सूची_OUT;
		type = "mux";
		अवरोध;
	हाल snd_soc_dapm_demux:
		dir = SND_SOC_DAPM_सूची_IN;
		type = "demux";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (w->num_kcontrols != 1) अणु
		dev_err(dapm->dev,
			"ASoC: %s %s has incorrect number of controls\n", type,
			w->name);
		वापस -EINVAL;
	पूर्ण

	अगर (list_empty(&w->edges[dir])) अणु
		dev_err(dapm->dev, "ASoC: %s %s has no paths\n", type, w->name);
		वापस -EINVAL;
	पूर्ण

	ret = dapm_create_or_share_kcontrol(w, 0);
	अगर (ret < 0)
		वापस ret;

	snd_soc_dapm_widget_क्रम_each_path(w, dir, path) अणु
		अगर (path->name)
			dapm_kcontrol_add_path(w->kcontrols[0], path);
	पूर्ण

	वापस 0;
पूर्ण

/* create new dapm volume control */
अटल पूर्णांक dapm_new_pga(काष्ठा snd_soc_dapm_widget *w)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < w->num_kcontrols; i++) अणु
		ret = dapm_create_or_share_kcontrol(w, i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* create new dapm dai link control */
अटल पूर्णांक dapm_new_dai_link(काष्ठा snd_soc_dapm_widget *w)
अणु
	पूर्णांक i, ret;
	काष्ठा snd_kcontrol *kcontrol;
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_card *card = dapm->card->snd_card;
	काष्ठा snd_soc_pcm_runसमय *rtd = w->priv;

	/* create control क्रम links with > 1 config */
	अगर (rtd->dai_link->num_params <= 1)
		वापस 0;

	/* add kcontrol */
	क्रम (i = 0; i < w->num_kcontrols; i++) अणु
		kcontrol = snd_soc_cnew(&w->kcontrol_news[i], w,
					w->name, शून्य);
		ret = snd_ctl_add(card, kcontrol);
		अगर (ret < 0) अणु
			dev_err(dapm->dev,
				"ASoC: failed to add widget %s dapm kcontrol %s: %d\n",
				w->name, w->kcontrol_news[i].name, ret);
			वापस ret;
		पूर्ण
		kcontrol->निजी_data = w;
		w->kcontrols[i] = kcontrol;
	पूर्ण

	वापस 0;
पूर्ण

/* We implement घातer करोwn on suspend by checking the घातer state of
 * the ALSA card - when we are suspending the ALSA state क्रम the card
 * is set to D3.
 */
अटल पूर्णांक snd_soc_dapm_suspend_check(काष्ठा snd_soc_dapm_widget *widget)
अणु
	पूर्णांक level = snd_घातer_get_state(widget->dapm->card->snd_card);

	चयन (level) अणु
	हाल SNDRV_CTL_POWER_D3hot:
	हाल SNDRV_CTL_POWER_D3cold:
		अगर (widget->ignore_suspend)
			dev_dbg(widget->dapm->dev, "ASoC: %s ignoring suspend\n",
				widget->name);
		वापस widget->ignore_suspend;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल व्योम dapm_widget_list_मुक्त(काष्ठा snd_soc_dapm_widget_list **list)
अणु
	kमुक्त(*list);
पूर्ण

अटल पूर्णांक dapm_widget_list_create(काष्ठा snd_soc_dapm_widget_list **list,
	काष्ठा list_head *widमाला_लो)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा list_head *it;
	अचिन्हित पूर्णांक size = 0;
	अचिन्हित पूर्णांक i = 0;

	list_क्रम_each(it, widमाला_लो)
		size++;

	*list = kzalloc(काष्ठा_size(*list, widमाला_लो, size), GFP_KERNEL);
	अगर (*list == शून्य)
		वापस -ENOMEM;

	list_क्रम_each_entry(w, widमाला_लो, work_list)
		(*list)->widमाला_लो[i++] = w;

	(*list)->num_widमाला_लो = i;

	वापस 0;
पूर्ण

/*
 * Recursively reset the cached number of inमाला_दो or outमाला_दो क्रम the specअगरied
 * widget and all widमाला_लो that can be reached via incoming or outcoming paths
 * from the widget.
 */
अटल व्योम invalidate_paths_ep(काष्ठा snd_soc_dapm_widget *widget,
	क्रमागत snd_soc_dapm_direction dir)
अणु
	क्रमागत snd_soc_dapm_direction rdir = SND_SOC_DAPM_सूची_REVERSE(dir);
	काष्ठा snd_soc_dapm_path *path;

	widget->endpoपूर्णांकs[dir] = -1;

	snd_soc_dapm_widget_क्रम_each_path(widget, rdir, path) अणु
		अगर (path->weak || path->is_supply)
			जारी;

		अगर (path->walking)
			वापस;

		अगर (path->connect) अणु
			path->walking = 1;
			invalidate_paths_ep(path->node[dir], dir);
			path->walking = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Common implementation क्रम is_connected_output_ep() and
 * is_connected_input_ep(). The function is अंतरभूतd since the combined size of
 * the two specialized functions is only marginally larger then the size of the
 * generic function and at the same समय the fast path of the specialized
 * functions is signअगरicantly smaller than the generic function.
 */
अटल __always_अंतरभूत पूर्णांक is_connected_ep(काष्ठा snd_soc_dapm_widget *widget,
	काष्ठा list_head *list, क्रमागत snd_soc_dapm_direction dir,
	पूर्णांक (*fn)(काष्ठा snd_soc_dapm_widget *, काष्ठा list_head *,
		  bool (*custom_stop_condition)(काष्ठा snd_soc_dapm_widget *,
						क्रमागत snd_soc_dapm_direction)),
	bool (*custom_stop_condition)(काष्ठा snd_soc_dapm_widget *,
				      क्रमागत snd_soc_dapm_direction))
अणु
	क्रमागत snd_soc_dapm_direction rdir = SND_SOC_DAPM_सूची_REVERSE(dir);
	काष्ठा snd_soc_dapm_path *path;
	पूर्णांक con = 0;

	अगर (widget->endpoपूर्णांकs[dir] >= 0)
		वापस widget->endpoपूर्णांकs[dir];

	DAPM_UPDATE_STAT(widget, path_checks);

	/* करो we need to add this widget to the list ? */
	अगर (list)
		list_add_tail(&widget->work_list, list);

	अगर (custom_stop_condition && custom_stop_condition(widget, dir)) अणु
		list = शून्य;
		custom_stop_condition = शून्य;
	पूर्ण

	अगर ((widget->is_ep & SND_SOC_DAPM_सूची_TO_EP(dir)) && widget->connected) अणु
		widget->endpoपूर्णांकs[dir] = snd_soc_dapm_suspend_check(widget);
		वापस widget->endpoपूर्णांकs[dir];
	पूर्ण

	snd_soc_dapm_widget_क्रम_each_path(widget, rdir, path) अणु
		DAPM_UPDATE_STAT(widget, neighbour_checks);

		अगर (path->weak || path->is_supply)
			जारी;

		अगर (path->walking)
			वापस 1;

		trace_snd_soc_dapm_path(widget, dir, path);

		अगर (path->connect) अणु
			path->walking = 1;
			con += fn(path->node[dir], list, custom_stop_condition);
			path->walking = 0;
		पूर्ण
	पूर्ण

	widget->endpoपूर्णांकs[dir] = con;

	वापस con;
पूर्ण

/*
 * Recursively check क्रम a completed path to an active or physically connected
 * output widget. Returns number of complete paths.
 *
 * Optionally, can be supplied with a function acting as a stopping condition.
 * This function takes the dapm widget currently being examined and the walk
 * direction as an arguments, it should वापस true अगर widमाला_लो from that poपूर्णांक
 * in the graph onwards should not be added to the widget list.
 */
अटल पूर्णांक is_connected_output_ep(काष्ठा snd_soc_dapm_widget *widget,
	काष्ठा list_head *list,
	bool (*custom_stop_condition)(काष्ठा snd_soc_dapm_widget *i,
				      क्रमागत snd_soc_dapm_direction))
अणु
	वापस is_connected_ep(widget, list, SND_SOC_DAPM_सूची_OUT,
			is_connected_output_ep, custom_stop_condition);
पूर्ण

/*
 * Recursively check क्रम a completed path to an active or physically connected
 * input widget. Returns number of complete paths.
 *
 * Optionally, can be supplied with a function acting as a stopping condition.
 * This function takes the dapm widget currently being examined and the walk
 * direction as an arguments, it should वापस true अगर the walk should be
 * stopped and false otherwise.
 */
अटल पूर्णांक is_connected_input_ep(काष्ठा snd_soc_dapm_widget *widget,
	काष्ठा list_head *list,
	bool (*custom_stop_condition)(काष्ठा snd_soc_dapm_widget *i,
				      क्रमागत snd_soc_dapm_direction))
अणु
	वापस is_connected_ep(widget, list, SND_SOC_DAPM_सूची_IN,
			is_connected_input_ep, custom_stop_condition);
पूर्ण

/**
 * snd_soc_dapm_dai_get_connected_widमाला_लो - query audio path and it's widमाला_लो.
 * @dai: the soc DAI.
 * @stream: stream direction.
 * @list: list of active widमाला_लो क्रम this stream.
 * @custom_stop_condition: (optional) a function meant to stop the widget graph
 *                         walk based on custom logic.
 *
 * Queries DAPM graph as to whether a valid audio stream path exists क्रम
 * the initial stream specअगरied by name. This takes पूर्णांकo account
 * current mixer and mux kcontrol settings. Creates list of valid widमाला_लो.
 *
 * Optionally, can be supplied with a function acting as a stopping condition.
 * This function takes the dapm widget currently being examined and the walk
 * direction as an arguments, it should वापस true अगर the walk should be
 * stopped and false otherwise.
 *
 * Returns the number of valid paths or negative error.
 */
पूर्णांक snd_soc_dapm_dai_get_connected_widमाला_लो(काष्ठा snd_soc_dai *dai, पूर्णांक stream,
	काष्ठा snd_soc_dapm_widget_list **list,
	bool (*custom_stop_condition)(काष्ठा snd_soc_dapm_widget *,
				      क्रमागत snd_soc_dapm_direction))
अणु
	काष्ठा snd_soc_card *card = dai->component->card;
	काष्ठा snd_soc_dapm_widget *w;
	LIST_HEAD(widमाला_लो);
	पूर्णांक paths;
	पूर्णांक ret;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		w = dai->playback_widget;
		invalidate_paths_ep(w, SND_SOC_DAPM_सूची_OUT);
		paths = is_connected_output_ep(w, &widमाला_लो,
				custom_stop_condition);
	पूर्ण अन्यथा अणु
		w = dai->capture_widget;
		invalidate_paths_ep(w, SND_SOC_DAPM_सूची_IN);
		paths = is_connected_input_ep(w, &widमाला_लो,
				custom_stop_condition);
	पूर्ण

	/* Drop starting poपूर्णांक */
	list_del(widमाला_लो.next);

	ret = dapm_widget_list_create(list, &widमाला_लो);
	अगर (ret)
		paths = ret;

	trace_snd_soc_dapm_connected(paths, stream);
	mutex_unlock(&card->dapm_mutex);

	वापस paths;
पूर्ण

व्योम snd_soc_dapm_dai_मुक्त_widमाला_लो(काष्ठा snd_soc_dapm_widget_list **list)
अणु
	dapm_widget_list_मुक्त(list);
पूर्ण

/*
 * Handler क्रम regulator supply widget.
 */
पूर्णांक dapm_regulator_event(काष्ठा snd_soc_dapm_widget *w,
		   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	पूर्णांक ret;

	soc_dapm_async_complete(w->dapm);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		अगर (w->on_val & SND_SOC_DAPM_REGULATOR_BYPASS) अणु
			ret = regulator_allow_bypass(w->regulator, false);
			अगर (ret != 0)
				dev_warn(w->dapm->dev,
					 "ASoC: Failed to unbypass %s: %d\n",
					 w->name, ret);
		पूर्ण

		वापस regulator_enable(w->regulator);
	पूर्ण अन्यथा अणु
		अगर (w->on_val & SND_SOC_DAPM_REGULATOR_BYPASS) अणु
			ret = regulator_allow_bypass(w->regulator, true);
			अगर (ret != 0)
				dev_warn(w->dapm->dev,
					 "ASoC: Failed to bypass %s: %d\n",
					 w->name, ret);
		पूर्ण

		वापस regulator_disable_deferred(w->regulator, w->shअगरt);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dapm_regulator_event);

/*
 * Handler क्रम pinctrl widget.
 */
पूर्णांक dapm_pinctrl_event(काष्ठा snd_soc_dapm_widget *w,
		       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_pinctrl_priv *priv = w->priv;
	काष्ठा pinctrl *p = w->pinctrl;
	काष्ठा pinctrl_state *s;

	अगर (!p || !priv)
		वापस -EIO;

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		s = pinctrl_lookup_state(p, priv->active_state);
	अन्यथा
		s = pinctrl_lookup_state(p, priv->sleep_state);

	अगर (IS_ERR(s))
		वापस PTR_ERR(s);

	वापस pinctrl_select_state(p, s);
पूर्ण
EXPORT_SYMBOL_GPL(dapm_pinctrl_event);

/*
 * Handler क्रम घड़ी supply widget.
 */
पूर्णांक dapm_घड़ी_event(काष्ठा snd_soc_dapm_widget *w,
		   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (!w->clk)
		वापस -EIO;

	soc_dapm_async_complete(w->dapm);

	अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		वापस clk_prepare_enable(w->clk);
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(w->clk);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dapm_घड़ी_event);

अटल पूर्णांक dapm_widget_घातer_check(काष्ठा snd_soc_dapm_widget *w)
अणु
	अगर (w->घातer_checked)
		वापस w->new_घातer;

	अगर (w->क्रमce)
		w->new_घातer = 1;
	अन्यथा
		w->new_घातer = w->घातer_check(w);

	w->घातer_checked = true;

	वापस w->new_घातer;
पूर्ण

/* Generic check to see अगर a widget should be घातered. */
अटल पूर्णांक dapm_generic_check_घातer(काष्ठा snd_soc_dapm_widget *w)
अणु
	पूर्णांक in, out;

	DAPM_UPDATE_STAT(w, घातer_checks);

	in = is_connected_input_ep(w, शून्य, शून्य);
	out = is_connected_output_ep(w, शून्य, शून्य);
	वापस out != 0 && in != 0;
पूर्ण

/* Check to see अगर a घातer supply is needed */
अटल पूर्णांक dapm_supply_check_घातer(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_path *path;

	DAPM_UPDATE_STAT(w, घातer_checks);

	/* Check अगर one of our outमाला_दो is connected */
	snd_soc_dapm_widget_क्रम_each_sink_path(w, path) अणु
		DAPM_UPDATE_STAT(w, neighbour_checks);

		अगर (path->weak)
			जारी;

		अगर (path->connected &&
		    !path->connected(path->source, path->sink))
			जारी;

		अगर (dapm_widget_घातer_check(path->sink))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dapm_always_on_check_घातer(काष्ठा snd_soc_dapm_widget *w)
अणु
	वापस w->connected;
पूर्ण

अटल पूर्णांक dapm_seq_compare(काष्ठा snd_soc_dapm_widget *a,
			    काष्ठा snd_soc_dapm_widget *b,
			    bool घातer_up)
अणु
	पूर्णांक *sort;

	BUILD_BUG_ON(ARRAY_SIZE(dapm_up_seq) != SND_SOC_DAPM_TYPE_COUNT);
	BUILD_BUG_ON(ARRAY_SIZE(dapm_करोwn_seq) != SND_SOC_DAPM_TYPE_COUNT);

	अगर (घातer_up)
		sort = dapm_up_seq;
	अन्यथा
		sort = dapm_करोwn_seq;

	WARN_ONCE(sort[a->id] == 0, "offset a->id %d not initialized\n", a->id);
	WARN_ONCE(sort[b->id] == 0, "offset b->id %d not initialized\n", b->id);

	अगर (sort[a->id] != sort[b->id])
		वापस sort[a->id] - sort[b->id];
	अगर (a->subseq != b->subseq) अणु
		अगर (घातer_up)
			वापस a->subseq - b->subseq;
		अन्यथा
			वापस b->subseq - a->subseq;
	पूर्ण
	अगर (a->reg != b->reg)
		वापस a->reg - b->reg;
	अगर (a->dapm != b->dapm)
		वापस (अचिन्हित दीर्घ)a->dapm - (अचिन्हित दीर्घ)b->dapm;

	वापस 0;
पूर्ण

/* Insert a widget in order पूर्णांकo a DAPM घातer sequence. */
अटल व्योम dapm_seq_insert(काष्ठा snd_soc_dapm_widget *new_widget,
			    काष्ठा list_head *list,
			    bool घातer_up)
अणु
	काष्ठा snd_soc_dapm_widget *w;

	list_क्रम_each_entry(w, list, घातer_list)
		अगर (dapm_seq_compare(new_widget, w, घातer_up) < 0) अणु
			list_add_tail(&new_widget->घातer_list, &w->घातer_list);
			वापस;
		पूर्ण

	list_add_tail(&new_widget->घातer_list, list);
पूर्ण

अटल व्योम dapm_seq_check_event(काष्ठा snd_soc_card *card,
				 काष्ठा snd_soc_dapm_widget *w, पूर्णांक event)
अणु
	स्थिर अक्षर *ev_name;
	पूर्णांक घातer, ret;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ev_name = "PRE_PMU";
		घातer = 1;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		ev_name = "POST_PMU";
		घातer = 1;
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		ev_name = "PRE_PMD";
		घातer = 0;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		ev_name = "POST_PMD";
		घातer = 0;
		अवरोध;
	हाल SND_SOC_DAPM_WILL_PMU:
		ev_name = "WILL_PMU";
		घातer = 1;
		अवरोध;
	हाल SND_SOC_DAPM_WILL_PMD:
		ev_name = "WILL_PMD";
		घातer = 0;
		अवरोध;
	शेष:
		WARN(1, "Unknown event %d\n", event);
		वापस;
	पूर्ण

	अगर (w->new_घातer != घातer)
		वापस;

	अगर (w->event && (w->event_flags & event)) अणु
		pop_dbg(w->dapm->dev, card->pop_समय, "pop test : %s %s\n",
			w->name, ev_name);
		soc_dapm_async_complete(w->dapm);
		trace_snd_soc_dapm_widget_event_start(w, event);
		ret = w->event(w, शून्य, event);
		trace_snd_soc_dapm_widget_event_करोne(w, event);
		अगर (ret < 0)
			dev_err(w->dapm->dev, "ASoC: %s: %s event failed: %d\n",
			       ev_name, w->name, ret);
	पूर्ण
पूर्ण

/* Apply the coalesced changes from a DAPM sequence */
अटल व्योम dapm_seq_run_coalesced(काष्ठा snd_soc_card *card,
				   काष्ठा list_head *pending)
अणु
	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा snd_soc_dapm_widget *w;
	पूर्णांक reg;
	अचिन्हित पूर्णांक value = 0;
	अचिन्हित पूर्णांक mask = 0;

	w = list_first_entry(pending, काष्ठा snd_soc_dapm_widget, घातer_list);
	reg = w->reg;
	dapm = w->dapm;

	list_क्रम_each_entry(w, pending, घातer_list) अणु
		WARN_ON(reg != w->reg || dapm != w->dapm);
		w->घातer = w->new_घातer;

		mask |= w->mask << w->shअगरt;
		अगर (w->घातer)
			value |= w->on_val << w->shअगरt;
		अन्यथा
			value |= w->off_val << w->shअगरt;

		pop_dbg(dapm->dev, card->pop_समय,
			"pop test : Queue %s: reg=0x%x, 0x%x/0x%x\n",
			w->name, reg, value, mask);

		/* Check क्रम events */
		dapm_seq_check_event(card, w, SND_SOC_DAPM_PRE_PMU);
		dapm_seq_check_event(card, w, SND_SOC_DAPM_PRE_PMD);
	पूर्ण

	अगर (reg >= 0) अणु
		/* Any widget will करो, they should all be updating the
		 * same रेजिस्टर.
		 */

		pop_dbg(dapm->dev, card->pop_समय,
			"pop test : Applying 0x%x/0x%x to %x in %dms\n",
			value, mask, reg, card->pop_समय);
		pop_रुको(card->pop_समय);
		soc_dapm_update_bits(dapm, reg, mask, value);
	पूर्ण

	list_क्रम_each_entry(w, pending, घातer_list) अणु
		dapm_seq_check_event(card, w, SND_SOC_DAPM_POST_PMU);
		dapm_seq_check_event(card, w, SND_SOC_DAPM_POST_PMD);
	पूर्ण
पूर्ण

/* Apply a DAPM घातer sequence.
 *
 * We walk over a pre-sorted list of widमाला_लो to apply घातer to.  In
 * order to minimise the number of ग_लिखोs to the device required
 * multiple widमाला_लो will be updated in a single ग_लिखो where possible.
 * Currently anything that requires more than a single ग_लिखो is not
 * handled.
 */
अटल व्योम dapm_seq_run(काष्ठा snd_soc_card *card,
	काष्ठा list_head *list, पूर्णांक event, bool घातer_up)
अणु
	काष्ठा snd_soc_dapm_widget *w, *n;
	काष्ठा snd_soc_dapm_context *d;
	LIST_HEAD(pending);
	पूर्णांक cur_sort = -1;
	पूर्णांक cur_subseq = -1;
	पूर्णांक cur_reg = SND_SOC_NOPM;
	काष्ठा snd_soc_dapm_context *cur_dapm = शून्य;
	पूर्णांक ret, i;
	पूर्णांक *sort;

	अगर (घातer_up)
		sort = dapm_up_seq;
	अन्यथा
		sort = dapm_करोwn_seq;

	list_क्रम_each_entry_safe(w, n, list, घातer_list) अणु
		ret = 0;

		/* Do we need to apply any queued changes? */
		अगर (sort[w->id] != cur_sort || w->reg != cur_reg ||
		    w->dapm != cur_dapm || w->subseq != cur_subseq) अणु
			अगर (!list_empty(&pending))
				dapm_seq_run_coalesced(card, &pending);

			अगर (cur_dapm && cur_dapm->component) अणु
				क्रम (i = 0; i < ARRAY_SIZE(dapm_up_seq); i++)
					अगर (sort[i] == cur_sort)
						snd_soc_component_seq_notअगरier(
							cur_dapm->component,
							i, cur_subseq);
			पूर्ण

			अगर (cur_dapm && w->dapm != cur_dapm)
				soc_dapm_async_complete(cur_dapm);

			INIT_LIST_HEAD(&pending);
			cur_sort = -1;
			cur_subseq = पूर्णांक_न्यून;
			cur_reg = SND_SOC_NOPM;
			cur_dapm = शून्य;
		पूर्ण

		चयन (w->id) अणु
		हाल snd_soc_dapm_pre:
			अगर (!w->event)
				list_क्रम_each_entry_safe_जारी(w, n, list,
								  घातer_list);

			अगर (event == SND_SOC_DAPM_STREAM_START)
				ret = w->event(w,
					       शून्य, SND_SOC_DAPM_PRE_PMU);
			अन्यथा अगर (event == SND_SOC_DAPM_STREAM_STOP)
				ret = w->event(w,
					       शून्य, SND_SOC_DAPM_PRE_PMD);
			अवरोध;

		हाल snd_soc_dapm_post:
			अगर (!w->event)
				list_क्रम_each_entry_safe_जारी(w, n, list,
								  घातer_list);

			अगर (event == SND_SOC_DAPM_STREAM_START)
				ret = w->event(w,
					       शून्य, SND_SOC_DAPM_POST_PMU);
			अन्यथा अगर (event == SND_SOC_DAPM_STREAM_STOP)
				ret = w->event(w,
					       शून्य, SND_SOC_DAPM_POST_PMD);
			अवरोध;

		शेष:
			/* Queue it up क्रम application */
			cur_sort = sort[w->id];
			cur_subseq = w->subseq;
			cur_reg = w->reg;
			cur_dapm = w->dapm;
			list_move(&w->घातer_list, &pending);
			अवरोध;
		पूर्ण

		अगर (ret < 0)
			dev_err(w->dapm->dev,
				"ASoC: Failed to apply widget power: %d\n", ret);
	पूर्ण

	अगर (!list_empty(&pending))
		dapm_seq_run_coalesced(card, &pending);

	अगर (cur_dapm && cur_dapm->component) अणु
		क्रम (i = 0; i < ARRAY_SIZE(dapm_up_seq); i++)
			अगर (sort[i] == cur_sort)
				snd_soc_component_seq_notअगरier(
					cur_dapm->component,
					i, cur_subseq);
	पूर्ण

	क्रम_each_card_dapms(card, d)
		soc_dapm_async_complete(d);
पूर्ण

अटल व्योम dapm_widget_update(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dapm_update *update = card->update;
	काष्ठा snd_soc_dapm_widget_list *wlist;
	काष्ठा snd_soc_dapm_widget *w = शून्य;
	अचिन्हित पूर्णांक wi;
	पूर्णांक ret;

	अगर (!update || !dapm_kcontrol_is_घातered(update->kcontrol))
		वापस;

	wlist = dapm_kcontrol_get_wlist(update->kcontrol);

	क्रम_each_dapm_widमाला_लो(wlist, wi, w) अणु
		अगर (w->event && (w->event_flags & SND_SOC_DAPM_PRE_REG)) अणु
			ret = w->event(w, update->kcontrol, SND_SOC_DAPM_PRE_REG);
			अगर (ret != 0)
				dev_err(w->dapm->dev, "ASoC: %s DAPM pre-event failed: %d\n",
					   w->name, ret);
		पूर्ण
	पूर्ण

	अगर (!w)
		वापस;

	ret = soc_dapm_update_bits(w->dapm, update->reg, update->mask,
		update->val);
	अगर (ret < 0)
		dev_err(w->dapm->dev, "ASoC: %s DAPM update failed: %d\n",
			w->name, ret);

	अगर (update->has_second_set) अणु
		ret = soc_dapm_update_bits(w->dapm, update->reg2,
					   update->mask2, update->val2);
		अगर (ret < 0)
			dev_err(w->dapm->dev,
				"ASoC: %s DAPM update failed: %d\n",
				w->name, ret);
	पूर्ण

	क्रम_each_dapm_widमाला_लो(wlist, wi, w) अणु
		अगर (w->event && (w->event_flags & SND_SOC_DAPM_POST_REG)) अणु
			ret = w->event(w, update->kcontrol, SND_SOC_DAPM_POST_REG);
			अगर (ret != 0)
				dev_err(w->dapm->dev, "ASoC: %s DAPM post-event failed: %d\n",
					   w->name, ret);
		पूर्ण
	पूर्ण
पूर्ण

/* Async callback run prior to DAPM sequences - brings to _PREPARE अगर
 * they're changing state.
 */
अटल व्योम dapm_pre_sequence_async(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा snd_soc_dapm_context *d = data;
	पूर्णांक ret;

	/* If we're off and we're not supposed to go पूर्णांकo STANDBY */
	अगर (d->bias_level == SND_SOC_BIAS_OFF &&
	    d->target_bias_level != SND_SOC_BIAS_OFF) अणु
		अगर (d->dev && cookie)
			pm_runसमय_get_sync(d->dev);

		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_STANDBY);
		अगर (ret != 0)
			dev_err(d->dev,
				"ASoC: Failed to turn on bias: %d\n", ret);
	पूर्ण

	/* Prepare क्रम a transition to ON or away from ON */
	अगर ((d->target_bias_level == SND_SOC_BIAS_ON &&
	     d->bias_level != SND_SOC_BIAS_ON) ||
	    (d->target_bias_level != SND_SOC_BIAS_ON &&
	     d->bias_level == SND_SOC_BIAS_ON)) अणु
		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_PREPARE);
		अगर (ret != 0)
			dev_err(d->dev,
				"ASoC: Failed to prepare bias: %d\n", ret);
	पूर्ण
पूर्ण

/* Async callback run prior to DAPM sequences - brings to their final
 * state.
 */
अटल व्योम dapm_post_sequence_async(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा snd_soc_dapm_context *d = data;
	पूर्णांक ret;

	/* If we just घातered the last thing off drop to standby bias */
	अगर (d->bias_level == SND_SOC_BIAS_PREPARE &&
	    (d->target_bias_level == SND_SOC_BIAS_STANDBY ||
	     d->target_bias_level == SND_SOC_BIAS_OFF)) अणु
		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_STANDBY);
		अगर (ret != 0)
			dev_err(d->dev, "ASoC: Failed to apply standby bias: %d\n",
				ret);
	पूर्ण

	/* If we're in standby and can support bias off then करो that */
	अगर (d->bias_level == SND_SOC_BIAS_STANDBY &&
	    d->target_bias_level == SND_SOC_BIAS_OFF) अणु
		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_OFF);
		अगर (ret != 0)
			dev_err(d->dev, "ASoC: Failed to turn off bias: %d\n",
				ret);

		अगर (d->dev && cookie)
			pm_runसमय_put(d->dev);
	पूर्ण

	/* If we just घातered up then move to active bias */
	अगर (d->bias_level == SND_SOC_BIAS_PREPARE &&
	    d->target_bias_level == SND_SOC_BIAS_ON) अणु
		ret = snd_soc_dapm_set_bias_level(d, SND_SOC_BIAS_ON);
		अगर (ret != 0)
			dev_err(d->dev, "ASoC: Failed to apply active bias: %d\n",
				ret);
	पूर्ण
पूर्ण

अटल व्योम dapm_widget_set_peer_घातer(काष्ठा snd_soc_dapm_widget *peer,
				       bool घातer, bool connect)
अणु
	/* If a connection is being made or broken then that update
	 * will have marked the peer dirty, otherwise the widमाला_लो are
	 * not connected and this update has no impact. */
	अगर (!connect)
		वापस;

	/* If the peer is alपढ़ोy in the state we're moving to then we
	 * won't have an impact on it. */
	अगर (घातer != peer->घातer)
		dapm_mark_dirty(peer, "peer state change");
पूर्ण

अटल व्योम dapm_widget_set_घातer(काष्ठा snd_soc_dapm_widget *w, bool घातer,
				  काष्ठा list_head *up_list,
				  काष्ठा list_head *करोwn_list)
अणु
	काष्ठा snd_soc_dapm_path *path;

	अगर (w->घातer == घातer)
		वापस;

	trace_snd_soc_dapm_widget_घातer(w, घातer);

	/* If we changed our घातer state perhaps our neigbours changed
	 * also.
	 */
	snd_soc_dapm_widget_क्रम_each_source_path(w, path)
		dapm_widget_set_peer_घातer(path->source, घातer, path->connect);

	/* Supplies can't affect their outमाला_दो, only their inमाला_दो */
	अगर (!w->is_supply) अणु
		snd_soc_dapm_widget_क्रम_each_sink_path(w, path)
			dapm_widget_set_peer_घातer(path->sink, घातer,
						   path->connect);
	पूर्ण

	अगर (घातer)
		dapm_seq_insert(w, up_list, true);
	अन्यथा
		dapm_seq_insert(w, करोwn_list, false);
पूर्ण

अटल व्योम dapm_घातer_one_widget(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा list_head *up_list,
				  काष्ठा list_head *करोwn_list)
अणु
	पूर्णांक घातer;

	चयन (w->id) अणु
	हाल snd_soc_dapm_pre:
		dapm_seq_insert(w, करोwn_list, false);
		अवरोध;
	हाल snd_soc_dapm_post:
		dapm_seq_insert(w, up_list, true);
		अवरोध;

	शेष:
		घातer = dapm_widget_घातer_check(w);

		dapm_widget_set_घातer(w, घातer, up_list, करोwn_list);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool dapm_idle_bias_off(काष्ठा snd_soc_dapm_context *dapm)
अणु
	अगर (dapm->idle_bias_off)
		वापस true;

	चयन (snd_घातer_get_state(dapm->card->snd_card)) अणु
	हाल SNDRV_CTL_POWER_D3hot:
	हाल SNDRV_CTL_POWER_D3cold:
		वापस dapm->suspend_bias_off;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Scan each dapm widget क्रम complete audio path.
 * A complete path is a route that has valid endpoपूर्णांकs i.e.:-
 *
 *  o DAC to output pin.
 *  o Input pin to ADC.
 *  o Input pin to Output pin (bypass, sidetone)
 *  o DAC to ADC (loopback).
 */
अटल पूर्णांक dapm_घातer_widमाला_लो(काष्ठा snd_soc_card *card, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा snd_soc_dapm_context *d;
	LIST_HEAD(up_list);
	LIST_HEAD(करोwn_list);
	ASYNC_DOMAIN_EXCLUSIVE(async_करोमुख्य);
	क्रमागत snd_soc_bias_level bias;
	पूर्णांक ret;

	lockdep_निश्चित_held(&card->dapm_mutex);

	trace_snd_soc_dapm_start(card);

	क्रम_each_card_dapms(card, d) अणु
		अगर (dapm_idle_bias_off(d))
			d->target_bias_level = SND_SOC_BIAS_OFF;
		अन्यथा
			d->target_bias_level = SND_SOC_BIAS_STANDBY;
	पूर्ण

	dapm_reset(card);

	/* Check which widमाला_लो we need to घातer and store them in
	 * lists indicating अगर they should be घातered up or करोwn.  We
	 * only check widमाला_लो that have been flagged as dirty but note
	 * that new widमाला_लो may be added to the dirty list जबतक we
	 * iterate.
	 */
	list_क्रम_each_entry(w, &card->dapm_dirty, dirty) अणु
		dapm_घातer_one_widget(w, &up_list, &करोwn_list);
	पूर्ण

	क्रम_each_card_widमाला_लो(card, w) अणु
		चयन (w->id) अणु
		हाल snd_soc_dapm_pre:
		हाल snd_soc_dapm_post:
			/* These widमाला_लो always need to be घातered */
			अवरोध;
		शेष:
			list_del_init(&w->dirty);
			अवरोध;
		पूर्ण

		अगर (w->new_घातer) अणु
			d = w->dapm;

			/* Supplies and micbiases only bring the
			 * context up to STANDBY as unless something
			 * अन्यथा is active and passing audio they
			 * generally करोn't require full घातer.  Signal
			 * generators are भव pins and have no
			 * घातer impact themselves.
			 */
			चयन (w->id) अणु
			हाल snd_soc_dapm_siggen:
			हाल snd_soc_dapm_vmid:
				अवरोध;
			हाल snd_soc_dapm_supply:
			हाल snd_soc_dapm_regulator_supply:
			हाल snd_soc_dapm_pinctrl:
			हाल snd_soc_dapm_घड़ी_supply:
			हाल snd_soc_dapm_micbias:
				अगर (d->target_bias_level < SND_SOC_BIAS_STANDBY)
					d->target_bias_level = SND_SOC_BIAS_STANDBY;
				अवरोध;
			शेष:
				d->target_bias_level = SND_SOC_BIAS_ON;
				अवरोध;
			पूर्ण
		पूर्ण

	पूर्ण

	/* Force all contexts in the card to the same bias state अगर
	 * they're not ground referenced.
	 */
	bias = SND_SOC_BIAS_OFF;
	क्रम_each_card_dapms(card, d)
		अगर (d->target_bias_level > bias)
			bias = d->target_bias_level;
	क्रम_each_card_dapms(card, d)
		अगर (!dapm_idle_bias_off(d))
			d->target_bias_level = bias;

	trace_snd_soc_dapm_walk_करोne(card);

	/* Run card bias changes at first */
	dapm_pre_sequence_async(&card->dapm, 0);
	/* Run other bias changes in parallel */
	क्रम_each_card_dapms(card, d) अणु
		अगर (d != &card->dapm && d->bias_level != d->target_bias_level)
			async_schedule_करोमुख्य(dapm_pre_sequence_async, d,
						&async_करोमुख्य);
	पूर्ण
	async_synchronize_full_करोमुख्य(&async_करोमुख्य);

	list_क्रम_each_entry(w, &करोwn_list, घातer_list) अणु
		dapm_seq_check_event(card, w, SND_SOC_DAPM_WILL_PMD);
	पूर्ण

	list_क्रम_each_entry(w, &up_list, घातer_list) अणु
		dapm_seq_check_event(card, w, SND_SOC_DAPM_WILL_PMU);
	पूर्ण

	/* Power करोwn widमाला_लो first; try to aव्योम amplअगरying pops. */
	dapm_seq_run(card, &करोwn_list, event, false);

	dapm_widget_update(card);

	/* Now घातer up. */
	dapm_seq_run(card, &up_list, event, true);

	/* Run all the bias changes in parallel */
	क्रम_each_card_dapms(card, d) अणु
		अगर (d != &card->dapm && d->bias_level != d->target_bias_level)
			async_schedule_करोमुख्य(dapm_post_sequence_async, d,
						&async_करोमुख्य);
	पूर्ण
	async_synchronize_full_करोमुख्य(&async_करोमुख्य);
	/* Run card bias changes at last */
	dapm_post_sequence_async(&card->dapm, 0);

	/* करो we need to notअगरy any clients that DAPM event is complete */
	क्रम_each_card_dapms(card, d) अणु
		अगर (!d->component)
			जारी;

		ret = snd_soc_component_stream_event(d->component, event);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	pop_dbg(card->dev, card->pop_समय,
		"DAPM sequencing finished, waiting %dms\n", card->pop_समय);
	pop_रुको(card->pop_समय);

	trace_snd_soc_dapm_करोne(card);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल sमाप_प्रकार dapm_widget_घातer_पढ़ो_file(काष्ठा file *file,
					   अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_soc_dapm_widget *w = file->निजी_data;
	काष्ठा snd_soc_card *card = w->dapm->card;
	क्रमागत snd_soc_dapm_direction dir, rdir;
	अक्षर *buf;
	पूर्णांक in, out;
	sमाप_प्रकार ret;
	काष्ठा snd_soc_dapm_path *p = शून्य;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&card->dapm_mutex);

	/* Supply widमाला_लो are not handled by is_connected_अणुinput,outputपूर्ण_ep() */
	अगर (w->is_supply) अणु
		in = 0;
		out = 0;
	पूर्ण अन्यथा अणु
		in = is_connected_input_ep(w, शून्य, शून्य);
		out = is_connected_output_ep(w, शून्य, शून्य);
	पूर्ण

	ret = scnम_लिखो(buf, PAGE_SIZE, "%s: %s%s  in %d out %d",
		       w->name, w->घातer ? "On" : "Off",
		       w->क्रमce ? " (forced)" : "", in, out);

	अगर (w->reg >= 0)
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
				" - R%d(0x%x) mask 0x%x",
				w->reg, w->reg, w->mask << w->shअगरt);

	ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, "\n");

	अगर (w->sname)
		ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret, " stream %s %s\n",
				w->sname,
				w->active ? "active" : "inactive");

	snd_soc_dapm_क्रम_each_direction(dir) अणु
		rdir = SND_SOC_DAPM_सूची_REVERSE(dir);
		snd_soc_dapm_widget_क्रम_each_path(w, dir, p) अणु
			अगर (p->connected && !p->connected(p->source, p->sink))
				जारी;

			अगर (!p->connect)
				जारी;

			ret += scnम_लिखो(buf + ret, PAGE_SIZE - ret,
					" %s  \"%s\" \"%s\"\n",
					(rdir == SND_SOC_DAPM_सूची_IN) ? "in" : "out",
					p->name ? p->name : "static",
					p->node[rdir]->name);
		पूर्ण
	पूर्ण

	mutex_unlock(&card->dapm_mutex);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, ret);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations dapm_widget_घातer_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = dapm_widget_घातer_पढ़ो_file,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार dapm_bias_पढ़ो_file(काष्ठा file *file, अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा snd_soc_dapm_context *dapm = file->निजी_data;
	अक्षर *level;

	चयन (dapm->bias_level) अणु
	हाल SND_SOC_BIAS_ON:
		level = "On\n";
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		level = "Prepare\n";
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		level = "Standby\n";
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		level = "Off\n";
		अवरोध;
	शेष:
		WARN(1, "Unknown bias_level %d\n", dapm->bias_level);
		level = "Unknown\n";
		अवरोध;
	पूर्ण

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, level,
				       म_माप(level));
पूर्ण

अटल स्थिर काष्ठा file_operations dapm_bias_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = dapm_bias_पढ़ो_file,
	.llseek = शेष_llseek,
पूर्ण;

व्योम snd_soc_dapm_debugfs_init(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा dentry *parent)
अणु
	अगर (!parent || IS_ERR(parent))
		वापस;

	dapm->debugfs_dapm = debugfs_create_dir("dapm", parent);

	debugfs_create_file("bias_level", 0444, dapm->debugfs_dapm, dapm,
			    &dapm_bias_fops);
पूर्ण

अटल व्योम dapm_debugfs_add_widget(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;

	अगर (!dapm->debugfs_dapm || !w->name)
		वापस;

	debugfs_create_file(w->name, 0444, dapm->debugfs_dapm, w,
			    &dapm_widget_घातer_fops);
पूर्ण

अटल व्योम dapm_debugfs_cleanup(काष्ठा snd_soc_dapm_context *dapm)
अणु
	debugfs_हटाओ_recursive(dapm->debugfs_dapm);
	dapm->debugfs_dapm = शून्य;
पूर्ण

#अन्यथा
व्योम snd_soc_dapm_debugfs_init(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा dentry *parent)
अणु
पूर्ण

अटल अंतरभूत व्योम dapm_debugfs_add_widget(काष्ठा snd_soc_dapm_widget *w)
अणु
पूर्ण

अटल अंतरभूत व्योम dapm_debugfs_cleanup(काष्ठा snd_soc_dapm_context *dapm)
अणु
पूर्ण

#पूर्ण_अगर

/*
 * soc_dapm_connect_path() - Connects or disconnects a path
 * @path: The path to update
 * @connect: The new connect state of the path. True अगर the path is connected,
 *  false अगर it is disconnected.
 * @reason: The reason why the path changed (क्रम debugging only)
 */
अटल व्योम soc_dapm_connect_path(काष्ठा snd_soc_dapm_path *path,
	bool connect, स्थिर अक्षर *reason)
अणु
	अगर (path->connect == connect)
		वापस;

	path->connect = connect;
	dapm_mark_dirty(path->source, reason);
	dapm_mark_dirty(path->sink, reason);
	dapm_path_invalidate(path);
पूर्ण

/* test and update the घातer status of a mux widget */
अटल पूर्णांक soc_dapm_mux_update_घातer(काष्ठा snd_soc_card *card,
				 काष्ठा snd_kcontrol *kcontrol, पूर्णांक mux, काष्ठा soc_क्रमागत *e)
अणु
	काष्ठा snd_soc_dapm_path *path;
	पूर्णांक found = 0;
	bool connect;

	lockdep_निश्चित_held(&card->dapm_mutex);

	/* find dapm widget path assoc with kcontrol */
	dapm_kcontrol_क्रम_each_path(path, kcontrol) अणु
		found = 1;
		/* we now need to match the string in the क्रमागत to the path */
		अगर (e && !(म_भेद(path->name, e->texts[mux])))
			connect = true;
		अन्यथा
			connect = false;

		soc_dapm_connect_path(path, connect, "mux update");
	पूर्ण

	अगर (found)
		dapm_घातer_widमाला_लो(card, SND_SOC_DAPM_STREAM_NOP);

	वापस found;
पूर्ण

पूर्णांक snd_soc_dapm_mux_update_घातer(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक mux, काष्ठा soc_क्रमागत *e,
	काष्ठा snd_soc_dapm_update *update)
अणु
	काष्ठा snd_soc_card *card = dapm->card;
	पूर्णांक ret;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	card->update = update;
	ret = soc_dapm_mux_update_घातer(card, kcontrol, mux, e);
	card->update = शून्य;
	mutex_unlock(&card->dapm_mutex);
	अगर (ret > 0)
		snd_soc_dpcm_runसमय_update(card);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_mux_update_घातer);

/* test and update the घातer status of a mixer or चयन widget */
अटल पूर्णांक soc_dapm_mixer_update_घातer(काष्ठा snd_soc_card *card,
				       काष्ठा snd_kcontrol *kcontrol,
				       पूर्णांक connect, पूर्णांक rconnect)
अणु
	काष्ठा snd_soc_dapm_path *path;
	पूर्णांक found = 0;

	lockdep_निश्चित_held(&card->dapm_mutex);

	/* find dapm widget path assoc with kcontrol */
	dapm_kcontrol_क्रम_each_path(path, kcontrol) अणु
		/*
		 * Ideally this function should support any number of
		 * paths and channels. But since kcontrols only come
		 * in mono and stereo variants, we are limited to 2
		 * channels.
		 *
		 * The following code assumes क्रम stereo controls the
		 * first path (when 'found == 0') is the left channel,
		 * and all reमुख्यing paths (when 'found == 1') are the
		 * right channel.
		 *
		 * A stereo control is signअगरied by a valid 'rconnect'
		 * value, either 0 क्रम unconnected, or >= 0 क्रम connected.
		 * This is chosen instead of using snd_soc_volsw_is_stereo,
		 * so that the behavior of snd_soc_dapm_mixer_update_घातer
		 * करोesn't change even when the kcontrol passed in is
		 * stereo.
		 *
		 * It passes 'connect' as the path connect status क्रम
		 * the left channel, and 'rconnect' क्रम the right
		 * channel.
		 */
		अगर (found && rconnect >= 0)
			soc_dapm_connect_path(path, rconnect, "mixer update");
		अन्यथा
			soc_dapm_connect_path(path, connect, "mixer update");
		found = 1;
	पूर्ण

	अगर (found)
		dapm_घातer_widमाला_लो(card, SND_SOC_DAPM_STREAM_NOP);

	वापस found;
पूर्ण

पूर्णांक snd_soc_dapm_mixer_update_घातer(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक connect,
	काष्ठा snd_soc_dapm_update *update)
अणु
	काष्ठा snd_soc_card *card = dapm->card;
	पूर्णांक ret;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	card->update = update;
	ret = soc_dapm_mixer_update_घातer(card, kcontrol, connect, -1);
	card->update = शून्य;
	mutex_unlock(&card->dapm_mutex);
	अगर (ret > 0)
		snd_soc_dpcm_runसमय_update(card);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_mixer_update_घातer);

अटल sमाप_प्रकार dapm_widget_show_component(काष्ठा snd_soc_component *cmpnt,
	अक्षर *buf)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	काष्ठा snd_soc_dapm_widget *w;
	पूर्णांक count = 0;
	अक्षर *state = "not set";

	/* card won't be set क्रम the dummy component, as a spot fix
	 * we're checking क्रम that हाल specअगरically here but in future
	 * we will ensure that the dummy component looks like others.
	 */
	अगर (!cmpnt->card)
		वापस 0;

	क्रम_each_card_widमाला_लो(cmpnt->card, w) अणु
		अगर (w->dapm != dapm)
			जारी;

		/* only display widमाला_लो that burn घातer */
		चयन (w->id) अणु
		हाल snd_soc_dapm_hp:
		हाल snd_soc_dapm_mic:
		हाल snd_soc_dapm_spk:
		हाल snd_soc_dapm_line:
		हाल snd_soc_dapm_micbias:
		हाल snd_soc_dapm_dac:
		हाल snd_soc_dapm_adc:
		हाल snd_soc_dapm_pga:
		हाल snd_soc_dapm_effect:
		हाल snd_soc_dapm_out_drv:
		हाल snd_soc_dapm_mixer:
		हाल snd_soc_dapm_mixer_named_ctl:
		हाल snd_soc_dapm_supply:
		हाल snd_soc_dapm_regulator_supply:
		हाल snd_soc_dapm_pinctrl:
		हाल snd_soc_dapm_घड़ी_supply:
			अगर (w->name)
				count += प्र_लिखो(buf + count, "%s: %s\n",
					w->name, w->घातer ? "On":"Off");
		अवरोध;
		शेष:
		अवरोध;
		पूर्ण
	पूर्ण

	चयन (snd_soc_dapm_get_bias_level(dapm)) अणु
	हाल SND_SOC_BIAS_ON:
		state = "On";
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		state = "Prepare";
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		state = "Standby";
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		state = "Off";
		अवरोध;
	पूर्ण
	count += प्र_लिखो(buf + count, "PM State: %s\n", state);

	वापस count;
पूर्ण

/* show dapm widget status in sys fs */
अटल sमाप_प्रकार dapm_widget_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = dev_get_drvdata(dev);
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक i, count = 0;

	mutex_lock(&rtd->card->dapm_mutex);

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		काष्ठा snd_soc_component *cmpnt = codec_dai->component;

		count += dapm_widget_show_component(cmpnt, buf + count);
	पूर्ण

	mutex_unlock(&rtd->card->dapm_mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(dapm_widget);

काष्ठा attribute *soc_dapm_dev_attrs[] = अणु
	&dev_attr_dapm_widget.attr,
	शून्य
पूर्ण;

अटल व्योम dapm_मुक्त_path(काष्ठा snd_soc_dapm_path *path)
अणु
	list_del(&path->list_node[SND_SOC_DAPM_सूची_IN]);
	list_del(&path->list_node[SND_SOC_DAPM_सूची_OUT]);
	list_del(&path->list_kcontrol);
	list_del(&path->list);
	kमुक्त(path);
पूर्ण

व्योम snd_soc_dapm_मुक्त_widget(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_path *p, *next_p;
	क्रमागत snd_soc_dapm_direction dir;

	list_del(&w->list);
	list_del(&w->dirty);
	/*
	 * हटाओ source and sink paths associated to this widget.
	 * While removing the path, हटाओ reference to it from both
	 * source and sink widमाला_लो so that path is हटाओd only once.
	 */
	snd_soc_dapm_क्रम_each_direction(dir) अणु
		snd_soc_dapm_widget_क्रम_each_path_safe(w, dir, p, next_p)
			dapm_मुक्त_path(p);
	पूर्ण

	kमुक्त(w->kcontrols);
	kमुक्त_स्थिर(w->name);
	kमुक्त_स्थिर(w->sname);
	kमुक्त(w);
पूर्ण

व्योम snd_soc_dapm_reset_cache(काष्ठा snd_soc_dapm_context *dapm)
अणु
	dapm->path_sink_cache.widget = शून्य;
	dapm->path_source_cache.widget = शून्य;
पूर्ण

/* मुक्त all dapm widमाला_लो and resources */
अटल व्योम dapm_मुक्त_widमाला_लो(काष्ठा snd_soc_dapm_context *dapm)
अणु
	काष्ठा snd_soc_dapm_widget *w, *next_w;

	क्रम_each_card_widमाला_लो_safe(dapm->card, w, next_w) अणु
		अगर (w->dapm != dapm)
			जारी;
		snd_soc_dapm_मुक्त_widget(w);
	पूर्ण
	snd_soc_dapm_reset_cache(dapm);
पूर्ण

अटल काष्ठा snd_soc_dapm_widget *dapm_find_widget(
			काष्ठा snd_soc_dapm_context *dapm, स्थिर अक्षर *pin,
			bool search_other_contexts)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा snd_soc_dapm_widget *fallback = शून्य;
	अक्षर prefixed_pin[80];
	स्थिर अक्षर *pin_name;
	स्थिर अक्षर *prefix = soc_dapm_prefix(dapm);

	अगर (prefix) अणु
		snम_लिखो(prefixed_pin, माप(prefixed_pin), "%s %s",
			 prefix, pin);
		pin_name = prefixed_pin;
	पूर्ण अन्यथा अणु
		pin_name = pin;
	पूर्ण

	क्रम_each_card_widमाला_लो(dapm->card, w) अणु
		अगर (!म_भेद(w->name, pin_name)) अणु
			अगर (w->dapm == dapm)
				वापस w;
			अन्यथा
				fallback = w;
		पूर्ण
	पूर्ण

	अगर (search_other_contexts)
		वापस fallback;

	वापस शून्य;
पूर्ण

अटल पूर्णांक snd_soc_dapm_set_pin(काष्ठा snd_soc_dapm_context *dapm,
				स्थिर अक्षर *pin, पूर्णांक status)
अणु
	काष्ठा snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, true);

	dapm_निश्चित_locked(dapm);

	अगर (!w) अणु
		dev_err(dapm->dev, "ASoC: DAPM unknown pin %s\n", pin);
		वापस -EINVAL;
	पूर्ण

	अगर (w->connected != status) अणु
		dapm_mark_dirty(w, "pin configuration");
		dapm_widget_invalidate_input_paths(w);
		dapm_widget_invalidate_output_paths(w);
	पूर्ण

	w->connected = status;
	अगर (status == 0)
		w->क्रमce = 0;

	वापस 0;
पूर्ण

/**
 * snd_soc_dapm_sync_unlocked - scan and घातer dapm paths
 * @dapm: DAPM context
 *
 * Walks all dapm audio paths and घातers widमाला_लो according to their
 * stream or path usage.
 *
 * Requires बाह्यal locking.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_dapm_sync_unlocked(काष्ठा snd_soc_dapm_context *dapm)
अणु
	/*
	 * Suppress early reports (eg, jacks syncing their state) to aव्योम
	 * silly DAPM runs during card startup.
	 */
	अगर (!dapm->card || !dapm->card->instantiated)
		वापस 0;

	वापस dapm_घातer_widमाला_लो(dapm->card, SND_SOC_DAPM_STREAM_NOP);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_sync_unlocked);

/**
 * snd_soc_dapm_sync - scan and घातer dapm paths
 * @dapm: DAPM context
 *
 * Walks all dapm audio paths and घातers widमाला_लो according to their
 * stream or path usage.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_dapm_sync(काष्ठा snd_soc_dapm_context *dapm)
अणु
	पूर्णांक ret;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	ret = snd_soc_dapm_sync_unlocked(dapm);
	mutex_unlock(&dapm->card->dapm_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_sync);

अटल पूर्णांक dapm_update_dai_chan(काष्ठा snd_soc_dapm_path *p,
				काष्ठा snd_soc_dapm_widget *w,
				पूर्णांक channels)
अणु
	चयन (w->id) अणु
	हाल snd_soc_dapm_aअगर_out:
	हाल snd_soc_dapm_aअगर_in:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	dev_dbg(w->dapm->dev, "%s DAI route %s -> %s\n",
		w->channel < channels ? "Connecting" : "Disconnecting",
		p->source->name, p->sink->name);

	अगर (w->channel < channels)
		soc_dapm_connect_path(p, true, "dai update");
	अन्यथा
		soc_dapm_connect_path(p, false, "dai update");

	वापस 0;
पूर्ण

अटल पूर्णांक dapm_update_dai_unlocked(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक dir = substream->stream;
	पूर्णांक channels = params_channels(params);
	काष्ठा snd_soc_dapm_path *p;
	काष्ठा snd_soc_dapm_widget *w;
	पूर्णांक ret;

	w = snd_soc_dai_get_widget(dai, dir);

	अगर (!w)
		वापस 0;

	dev_dbg(dai->dev, "Update DAI routes for %s %s\n", dai->name,
		dir == SNDRV_PCM_STREAM_PLAYBACK ? "playback" : "capture");

	snd_soc_dapm_widget_क्रम_each_sink_path(w, p) अणु
		ret = dapm_update_dai_chan(p, p->sink, channels);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	snd_soc_dapm_widget_क्रम_each_source_path(w, p) अणु
		ret = dapm_update_dai_chan(p, p->source, channels);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_soc_dapm_update_dai(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret;

	mutex_lock_nested(&rtd->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	ret = dapm_update_dai_unlocked(substream, params, dai);
	mutex_unlock(&rtd->card->dapm_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_update_dai);

/*
 * dapm_update_widget_flags() - Re-compute widget sink and source flags
 * @w: The widget क्रम which to update the flags
 *
 * Some widमाला_लो have a dynamic category which depends on which neighbors they
 * are connected to. This function update the category क्रम these widमाला_लो.
 *
 * This function must be called whenever a path is added or हटाओd to a widget.
 */
अटल व्योम dapm_update_widget_flags(काष्ठा snd_soc_dapm_widget *w)
अणु
	क्रमागत snd_soc_dapm_direction dir;
	काष्ठा snd_soc_dapm_path *p;
	अचिन्हित पूर्णांक ep;

	चयन (w->id) अणु
	हाल snd_soc_dapm_input:
		/* On a fully routed card an input is never a source */
		अगर (w->dapm->card->fully_routed)
			वापस;
		ep = SND_SOC_DAPM_EP_SOURCE;
		snd_soc_dapm_widget_क्रम_each_source_path(w, p) अणु
			अगर (p->source->id == snd_soc_dapm_micbias ||
				p->source->id == snd_soc_dapm_mic ||
				p->source->id == snd_soc_dapm_line ||
				p->source->id == snd_soc_dapm_output) अणु
					ep = 0;
					अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल snd_soc_dapm_output:
		/* On a fully routed card a output is never a sink */
		अगर (w->dapm->card->fully_routed)
			वापस;
		ep = SND_SOC_DAPM_EP_SINK;
		snd_soc_dapm_widget_क्रम_each_sink_path(w, p) अणु
			अगर (p->sink->id == snd_soc_dapm_spk ||
				p->sink->id == snd_soc_dapm_hp ||
				p->sink->id == snd_soc_dapm_line ||
				p->sink->id == snd_soc_dapm_input) अणु
					ep = 0;
					अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल snd_soc_dapm_line:
		ep = 0;
		snd_soc_dapm_क्रम_each_direction(dir) अणु
			अगर (!list_empty(&w->edges[dir]))
				ep |= SND_SOC_DAPM_सूची_TO_EP(dir);
		पूर्ण
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	w->is_ep = ep;
पूर्ण

अटल पूर्णांक snd_soc_dapm_check_dynamic_path(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा snd_soc_dapm_widget *source, काष्ठा snd_soc_dapm_widget *sink,
	स्थिर अक्षर *control)
अणु
	bool dynamic_source = false;
	bool dynamic_sink = false;

	अगर (!control)
		वापस 0;

	चयन (source->id) अणु
	हाल snd_soc_dapm_demux:
		dynamic_source = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (sink->id) अणु
	हाल snd_soc_dapm_mux:
	हाल snd_soc_dapm_चयन:
	हाल snd_soc_dapm_mixer:
	हाल snd_soc_dapm_mixer_named_ctl:
		dynamic_sink = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (dynamic_source && dynamic_sink) अणु
		dev_err(dapm->dev,
			"Direct connection between demux and mixer/mux not supported for path %s -> [%s] -> %s\n",
			source->name, control, sink->name);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!dynamic_source && !dynamic_sink) अणु
		dev_err(dapm->dev,
			"Control not supported for path %s -> [%s] -> %s\n",
			source->name, control, sink->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_soc_dapm_add_path(काष्ठा snd_soc_dapm_context *dapm,
	काष्ठा snd_soc_dapm_widget *wsource, काष्ठा snd_soc_dapm_widget *wsink,
	स्थिर अक्षर *control,
	पूर्णांक (*connected)(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink))
अणु
	काष्ठा snd_soc_dapm_widget *widमाला_लो[2];
	क्रमागत snd_soc_dapm_direction dir;
	काष्ठा snd_soc_dapm_path *path;
	पूर्णांक ret;

	अगर (wsink->is_supply && !wsource->is_supply) अणु
		dev_err(dapm->dev,
			"Connecting non-supply widget to supply widget is not supported (%s -> %s)\n",
			wsource->name, wsink->name);
		वापस -EINVAL;
	पूर्ण

	अगर (connected && !wsource->is_supply) अणु
		dev_err(dapm->dev,
			"connected() callback only supported for supply widgets (%s -> %s)\n",
			wsource->name, wsink->name);
		वापस -EINVAL;
	पूर्ण

	अगर (wsource->is_supply && control) अणु
		dev_err(dapm->dev,
			"Conditional paths are not supported for supply widgets (%s -> [%s] -> %s)\n",
			wsource->name, control, wsink->name);
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_dapm_check_dynamic_path(dapm, wsource, wsink, control);
	अगर (ret)
		वापस ret;

	path = kzalloc(माप(काष्ठा snd_soc_dapm_path), GFP_KERNEL);
	अगर (!path)
		वापस -ENOMEM;

	path->node[SND_SOC_DAPM_सूची_IN] = wsource;
	path->node[SND_SOC_DAPM_सूची_OUT] = wsink;
	widमाला_लो[SND_SOC_DAPM_सूची_IN] = wsource;
	widमाला_लो[SND_SOC_DAPM_सूची_OUT] = wsink;

	path->connected = connected;
	INIT_LIST_HEAD(&path->list);
	INIT_LIST_HEAD(&path->list_kcontrol);

	अगर (wsource->is_supply || wsink->is_supply)
		path->is_supply = 1;

	/* connect अटल paths */
	अगर (control == शून्य) अणु
		path->connect = 1;
	पूर्ण अन्यथा अणु
		चयन (wsource->id) अणु
		हाल snd_soc_dapm_demux:
			ret = dapm_connect_mux(dapm, path, control, wsource);
			अगर (ret)
				जाओ err;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		चयन (wsink->id) अणु
		हाल snd_soc_dapm_mux:
			ret = dapm_connect_mux(dapm, path, control, wsink);
			अगर (ret != 0)
				जाओ err;
			अवरोध;
		हाल snd_soc_dapm_चयन:
		हाल snd_soc_dapm_mixer:
		हाल snd_soc_dapm_mixer_named_ctl:
			ret = dapm_connect_mixer(dapm, path, control);
			अगर (ret != 0)
				जाओ err;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	list_add(&path->list, &dapm->card->paths);
	snd_soc_dapm_क्रम_each_direction(dir)
		list_add(&path->list_node[dir], &widमाला_लो[dir]->edges[dir]);

	snd_soc_dapm_क्रम_each_direction(dir) अणु
		dapm_update_widget_flags(widमाला_लो[dir]);
		dapm_mark_dirty(widमाला_लो[dir], "Route added");
	पूर्ण

	अगर (dapm->card->instantiated && path->connect)
		dapm_path_invalidate(path);

	वापस 0;
err:
	kमुक्त(path);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_soc_dapm_add_route(काष्ठा snd_soc_dapm_context *dapm,
				  स्थिर काष्ठा snd_soc_dapm_route *route)
अणु
	काष्ठा snd_soc_dapm_widget *wsource = शून्य, *wsink = शून्य, *w;
	काष्ठा snd_soc_dapm_widget *wtsource = शून्य, *wtsink = शून्य;
	स्थिर अक्षर *sink;
	स्थिर अक्षर *source;
	अक्षर prefixed_sink[80];
	अक्षर prefixed_source[80];
	स्थिर अक्षर *prefix;
	अचिन्हित पूर्णांक sink_ref = 0;
	अचिन्हित पूर्णांक source_ref = 0;
	पूर्णांक ret;

	prefix = soc_dapm_prefix(dapm);
	अगर (prefix) अणु
		snम_लिखो(prefixed_sink, माप(prefixed_sink), "%s %s",
			 prefix, route->sink);
		sink = prefixed_sink;
		snम_लिखो(prefixed_source, माप(prefixed_source), "%s %s",
			 prefix, route->source);
		source = prefixed_source;
	पूर्ण अन्यथा अणु
		sink = route->sink;
		source = route->source;
	पूर्ण

	wsource = dapm_wcache_lookup(&dapm->path_source_cache, source);
	wsink = dapm_wcache_lookup(&dapm->path_sink_cache, sink);

	अगर (wsink && wsource)
		जाओ skip_search;

	/*
	 * find src and dest widमाला_लो over all widमाला_लो but favor a widget from
	 * current DAPM context
	 */
	क्रम_each_card_widमाला_लो(dapm->card, w) अणु
		अगर (!wsink && !(म_भेद(w->name, sink))) अणु
			wtsink = w;
			अगर (w->dapm == dapm) अणु
				wsink = w;
				अगर (wsource)
					अवरोध;
			पूर्ण
			sink_ref++;
			अगर (sink_ref > 1)
				dev_warn(dapm->dev,
					"ASoC: sink widget %s overwritten\n",
					w->name);
			जारी;
		पूर्ण
		अगर (!wsource && !(म_भेद(w->name, source))) अणु
			wtsource = w;
			अगर (w->dapm == dapm) अणु
				wsource = w;
				अगर (wsink)
					अवरोध;
			पूर्ण
			source_ref++;
			अगर (source_ref > 1)
				dev_warn(dapm->dev,
					"ASoC: source widget %s overwritten\n",
					w->name);
		पूर्ण
	पूर्ण
	/* use widget from another DAPM context अगर not found from this */
	अगर (!wsink)
		wsink = wtsink;
	अगर (!wsource)
		wsource = wtsource;

	अगर (wsource == शून्य) अणु
		dev_err(dapm->dev, "ASoC: no source widget found for %s\n",
			route->source);
		वापस -ENODEV;
	पूर्ण
	अगर (wsink == शून्य) अणु
		dev_err(dapm->dev, "ASoC: no sink widget found for %s\n",
			route->sink);
		वापस -ENODEV;
	पूर्ण

skip_search:
	dapm_wcache_update(&dapm->path_sink_cache, wsink);
	dapm_wcache_update(&dapm->path_source_cache, wsource);

	ret = snd_soc_dapm_add_path(dapm, wsource, wsink, route->control,
		route->connected);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_warn(dapm->dev, "ASoC: no dapm match for %s --> %s --> %s\n",
		 source, route->control, sink);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_soc_dapm_del_route(काष्ठा snd_soc_dapm_context *dapm,
				  स्थिर काष्ठा snd_soc_dapm_route *route)
अणु
	काष्ठा snd_soc_dapm_widget *wsource, *wsink;
	काष्ठा snd_soc_dapm_path *path, *p;
	स्थिर अक्षर *sink;
	स्थिर अक्षर *source;
	अक्षर prefixed_sink[80];
	अक्षर prefixed_source[80];
	स्थिर अक्षर *prefix;

	अगर (route->control) अणु
		dev_err(dapm->dev,
			"ASoC: Removal of routes with controls not supported\n");
		वापस -EINVAL;
	पूर्ण

	prefix = soc_dapm_prefix(dapm);
	अगर (prefix) अणु
		snम_लिखो(prefixed_sink, माप(prefixed_sink), "%s %s",
			 prefix, route->sink);
		sink = prefixed_sink;
		snम_लिखो(prefixed_source, माप(prefixed_source), "%s %s",
			 prefix, route->source);
		source = prefixed_source;
	पूर्ण अन्यथा अणु
		sink = route->sink;
		source = route->source;
	पूर्ण

	path = शून्य;
	list_क्रम_each_entry(p, &dapm->card->paths, list) अणु
		अगर (म_भेद(p->source->name, source) != 0)
			जारी;
		अगर (म_भेद(p->sink->name, sink) != 0)
			जारी;
		path = p;
		अवरोध;
	पूर्ण

	अगर (path) अणु
		wsource = path->source;
		wsink = path->sink;

		dapm_mark_dirty(wsource, "Route removed");
		dapm_mark_dirty(wsink, "Route removed");
		अगर (path->connect)
			dapm_path_invalidate(path);

		dapm_मुक्त_path(path);

		/* Update any path related flags */
		dapm_update_widget_flags(wsource);
		dapm_update_widget_flags(wsink);
	पूर्ण अन्यथा अणु
		dev_warn(dapm->dev, "ASoC: Route %s->%s does not exist\n",
			 source, sink);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * snd_soc_dapm_add_routes - Add routes between DAPM widमाला_लो
 * @dapm: DAPM context
 * @route: audio routes
 * @num: number of routes
 *
 * Connects 2 dapm widमाला_लो together via a named audio path. The sink is
 * the widget receiving the audio संकेत, whilst the source is the sender
 * of the audio संकेत.
 *
 * Returns 0 क्रम success अन्यथा error. On error all resources can be मुक्तd
 * with a call to snd_soc_card_मुक्त().
 */
पूर्णांक snd_soc_dapm_add_routes(काष्ठा snd_soc_dapm_context *dapm,
			    स्थिर काष्ठा snd_soc_dapm_route *route, पूर्णांक num)
अणु
	पूर्णांक i, r, ret = 0;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	क्रम (i = 0; i < num; i++) अणु
		r = snd_soc_dapm_add_route(dapm, route);
		अगर (r < 0) अणु
			dev_err(dapm->dev, "ASoC: Failed to add route %s -> %s -> %s\n",
				route->source,
				route->control ? route->control : "direct",
				route->sink);
			ret = r;
		पूर्ण
		route++;
	पूर्ण
	mutex_unlock(&dapm->card->dapm_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_add_routes);

/**
 * snd_soc_dapm_del_routes - Remove routes between DAPM widमाला_लो
 * @dapm: DAPM context
 * @route: audio routes
 * @num: number of routes
 *
 * Removes routes from the DAPM context.
 */
पूर्णांक snd_soc_dapm_del_routes(काष्ठा snd_soc_dapm_context *dapm,
			    स्थिर काष्ठा snd_soc_dapm_route *route, पूर्णांक num)
अणु
	पूर्णांक i;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	क्रम (i = 0; i < num; i++) अणु
		snd_soc_dapm_del_route(dapm, route);
		route++;
	पूर्ण
	mutex_unlock(&dapm->card->dapm_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_del_routes);

अटल पूर्णांक snd_soc_dapm_weak_route(काष्ठा snd_soc_dapm_context *dapm,
				   स्थिर काष्ठा snd_soc_dapm_route *route)
अणु
	काष्ठा snd_soc_dapm_widget *source = dapm_find_widget(dapm,
							      route->source,
							      true);
	काष्ठा snd_soc_dapm_widget *sink = dapm_find_widget(dapm,
							    route->sink,
							    true);
	काष्ठा snd_soc_dapm_path *path;
	पूर्णांक count = 0;

	अगर (!source) अणु
		dev_err(dapm->dev, "ASoC: Unable to find source %s for weak route\n",
			route->source);
		वापस -ENODEV;
	पूर्ण

	अगर (!sink) अणु
		dev_err(dapm->dev, "ASoC: Unable to find sink %s for weak route\n",
			route->sink);
		वापस -ENODEV;
	पूर्ण

	अगर (route->control || route->connected)
		dev_warn(dapm->dev, "ASoC: Ignoring control for weak route %s->%s\n",
			 route->source, route->sink);

	snd_soc_dapm_widget_क्रम_each_sink_path(source, path) अणु
		अगर (path->sink == sink) अणु
			path->weak = 1;
			count++;
		पूर्ण
	पूर्ण

	अगर (count == 0)
		dev_err(dapm->dev, "ASoC: No path found for weak route %s->%s\n",
			route->source, route->sink);
	अगर (count > 1)
		dev_warn(dapm->dev, "ASoC: %d paths found for weak route %s->%s\n",
			 count, route->source, route->sink);

	वापस 0;
पूर्ण

/**
 * snd_soc_dapm_weak_routes - Mark routes between DAPM widमाला_लो as weak
 * @dapm: DAPM context
 * @route: audio routes
 * @num: number of routes
 *
 * Mark existing routes matching those specअगरied in the passed array
 * as being weak, meaning that they are ignored क्रम the purpose of
 * घातer decisions.  The मुख्य पूर्णांकended use हाल is क्रम sidetone paths
 * which couple audio between other independent paths अगर they are both
 * active in order to make the combination work better at the user
 * level but which aren't पूर्णांकended to be "used".
 *
 * Note that CODEC drivers should not use this as sidetone type paths
 * can frequently also be used as bypass paths.
 */
पूर्णांक snd_soc_dapm_weak_routes(काष्ठा snd_soc_dapm_context *dapm,
			     स्थिर काष्ठा snd_soc_dapm_route *route, पूर्णांक num)
अणु
	पूर्णांक i, err;
	पूर्णांक ret = 0;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_INIT);
	क्रम (i = 0; i < num; i++) अणु
		err = snd_soc_dapm_weak_route(dapm, route);
		अगर (err)
			ret = err;
		route++;
	पूर्ण
	mutex_unlock(&dapm->card->dapm_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_weak_routes);

/**
 * snd_soc_dapm_new_widमाला_लो - add new dapm widमाला_लो
 * @card: card to be checked क्रम new dapm widमाला_लो
 *
 * Checks the codec क्रम any new dapm widमाला_लो and creates them अगर found.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_dapm_new_widमाला_लो(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	अचिन्हित पूर्णांक val;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_INIT);

	क्रम_each_card_widमाला_लो(card, w)
	अणु
		अगर (w->new)
			जारी;

		अगर (w->num_kcontrols) अणु
			w->kcontrols = kसुस्मृति(w->num_kcontrols,
						माप(काष्ठा snd_kcontrol *),
						GFP_KERNEL);
			अगर (!w->kcontrols) अणु
				mutex_unlock(&card->dapm_mutex);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		चयन(w->id) अणु
		हाल snd_soc_dapm_चयन:
		हाल snd_soc_dapm_mixer:
		हाल snd_soc_dapm_mixer_named_ctl:
			dapm_new_mixer(w);
			अवरोध;
		हाल snd_soc_dapm_mux:
		हाल snd_soc_dapm_demux:
			dapm_new_mux(w);
			अवरोध;
		हाल snd_soc_dapm_pga:
		हाल snd_soc_dapm_effect:
		हाल snd_soc_dapm_out_drv:
			dapm_new_pga(w);
			अवरोध;
		हाल snd_soc_dapm_dai_link:
			dapm_new_dai_link(w);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* Read the initial घातer state from the device */
		अगर (w->reg >= 0) अणु
			val = soc_dapm_पढ़ो(w->dapm, w->reg);
			val = val >> w->shअगरt;
			val &= w->mask;
			अगर (val == w->on_val)
				w->घातer = 1;
		पूर्ण

		w->new = 1;

		dapm_mark_dirty(w, "new widget");
		dapm_debugfs_add_widget(w);
	पूर्ण

	dapm_घातer_widमाला_लो(card, SND_SOC_DAPM_STREAM_NOP);
	mutex_unlock(&card->dapm_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_new_widमाला_लो);

/**
 * snd_soc_dapm_get_volsw - dapm mixer get callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to get the value of a dapm mixer control.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_dapm_get_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	पूर्णांक max = mc->max;
	अचिन्हित पूर्णांक width = fls(max);
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	अचिन्हित पूर्णांक invert = mc->invert;
	अचिन्हित पूर्णांक reg_val, val, rval = 0;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	अगर (dapm_kcontrol_is_घातered(kcontrol) && reg != SND_SOC_NOPM) अणु
		reg_val = soc_dapm_पढ़ो(dapm, reg);
		val = (reg_val >> shअगरt) & mask;

		अगर (reg != mc->rreg)
			reg_val = soc_dapm_पढ़ो(dapm, mc->rreg);

		अगर (snd_soc_volsw_is_stereo(mc))
			rval = (reg_val >> mc->rshअगरt) & mask;
	पूर्ण अन्यथा अणु
		reg_val = dapm_kcontrol_get_value(kcontrol);
		val = reg_val & mask;

		अगर (snd_soc_volsw_is_stereo(mc))
			rval = (reg_val >> width) & mask;
	पूर्ण
	mutex_unlock(&card->dapm_mutex);

	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = max - val;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = val;

	अगर (snd_soc_volsw_is_stereo(mc)) अणु
		अगर (invert)
			ucontrol->value.पूर्णांकeger.value[1] = max - rval;
		अन्यथा
			ucontrol->value.पूर्णांकeger.value[1] = rval;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_get_volsw);

/**
 * snd_soc_dapm_put_volsw - dapm mixer set callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to set the value of a dapm mixer control.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_dapm_put_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	पूर्णांक max = mc->max;
	अचिन्हित पूर्णांक width = fls(max);
	अचिन्हित पूर्णांक mask = (1 << width) - 1;
	अचिन्हित पूर्णांक invert = mc->invert;
	अचिन्हित पूर्णांक val, rval = 0;
	पूर्णांक connect, rconnect = -1, change, reg_change = 0;
	काष्ठा snd_soc_dapm_update update = अणुपूर्ण;
	पूर्णांक ret = 0;

	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	connect = !!val;

	अगर (invert)
		val = max - val;

	अगर (snd_soc_volsw_is_stereo(mc)) अणु
		rval = (ucontrol->value.पूर्णांकeger.value[1] & mask);
		rconnect = !!rval;
		अगर (invert)
			rval = max - rval;
	पूर्ण

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);

	/* This assumes field width < (bits in अचिन्हित पूर्णांक / 2) */
	अगर (width > माप(अचिन्हित पूर्णांक) * 8 / 2)
		dev_warn(dapm->dev,
			 "ASoC: control %s field width limit exceeded\n",
			 kcontrol->id.name);
	change = dapm_kcontrol_set_value(kcontrol, val | (rval << width));

	अगर (reg != SND_SOC_NOPM) अणु
		val = val << shअगरt;
		rval = rval << mc->rshअगरt;

		reg_change = soc_dapm_test_bits(dapm, reg, mask << shअगरt, val);

		अगर (snd_soc_volsw_is_stereo(mc))
			reg_change |= soc_dapm_test_bits(dapm, mc->rreg,
							 mask << mc->rshअगरt,
							 rval);
	पूर्ण

	अगर (change || reg_change) अणु
		अगर (reg_change) अणु
			अगर (snd_soc_volsw_is_stereo(mc)) अणु
				update.has_second_set = true;
				update.reg2 = mc->rreg;
				update.mask2 = mask << mc->rshअगरt;
				update.val2 = rval;
			पूर्ण
			update.kcontrol = kcontrol;
			update.reg = reg;
			update.mask = mask << shअगरt;
			update.val = val;
			card->update = &update;
		पूर्ण
		change |= reg_change;

		ret = soc_dapm_mixer_update_घातer(card, kcontrol, connect,
						  rconnect);

		card->update = शून्य;
	पूर्ण

	mutex_unlock(&card->dapm_mutex);

	अगर (ret > 0)
		snd_soc_dpcm_runसमय_update(card);

	वापस change;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_put_volsw);

/**
 * snd_soc_dapm_get_क्रमागत_द्विगुन - dapm क्रमागतerated द्विगुन mixer get callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to get the value of a dapm क्रमागतerated द्विगुन mixer control.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_dapm_get_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg_val, val;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	अगर (e->reg != SND_SOC_NOPM && dapm_kcontrol_is_घातered(kcontrol)) अणु
		reg_val = soc_dapm_पढ़ो(dapm, e->reg);
	पूर्ण अन्यथा अणु
		reg_val = dapm_kcontrol_get_value(kcontrol);
	पूर्ण
	mutex_unlock(&card->dapm_mutex);

	val = (reg_val >> e->shअगरt_l) & e->mask;
	ucontrol->value.क्रमागतerated.item[0] = snd_soc_क्रमागत_val_to_item(e, val);
	अगर (e->shअगरt_l != e->shअगरt_r) अणु
		val = (reg_val >> e->shअगरt_r) & e->mask;
		val = snd_soc_क्रमागत_val_to_item(e, val);
		ucontrol->value.क्रमागतerated.item[1] = val;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_get_क्रमागत_द्विगुन);

/**
 * snd_soc_dapm_put_क्रमागत_द्विगुन - dapm क्रमागतerated द्विगुन mixer set callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to set the value of a dapm क्रमागतerated द्विगुन mixer control.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_dapm_put_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	अचिन्हित पूर्णांक val, change, reg_change = 0;
	अचिन्हित पूर्णांक mask;
	काष्ठा snd_soc_dapm_update update = अणुपूर्ण;
	पूर्णांक ret = 0;

	अगर (item[0] >= e->items)
		वापस -EINVAL;

	val = snd_soc_क्रमागत_item_to_val(e, item[0]) << e->shअगरt_l;
	mask = e->mask << e->shअगरt_l;
	अगर (e->shअगरt_l != e->shअगरt_r) अणु
		अगर (item[1] > e->items)
			वापस -EINVAL;
		val |= snd_soc_क्रमागत_item_to_val(e, item[1]) << e->shअगरt_r;
		mask |= e->mask << e->shअगरt_r;
	पूर्ण

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);

	change = dapm_kcontrol_set_value(kcontrol, val);

	अगर (e->reg != SND_SOC_NOPM)
		reg_change = soc_dapm_test_bits(dapm, e->reg, mask, val);

	अगर (change || reg_change) अणु
		अगर (reg_change) अणु
			update.kcontrol = kcontrol;
			update.reg = e->reg;
			update.mask = mask;
			update.val = val;
			card->update = &update;
		पूर्ण
		change |= reg_change;

		ret = soc_dapm_mux_update_घातer(card, kcontrol, item[0], e);

		card->update = शून्य;
	पूर्ण

	mutex_unlock(&card->dapm_mutex);

	अगर (ret > 0)
		snd_soc_dpcm_runसमय_update(card);

	वापस change;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_put_क्रमागत_द्विगुन);

/**
 * snd_soc_dapm_info_pin_चयन - Info क्रम a pin चयन
 *
 * @kcontrol: mixer control
 * @uinfo: control element inक्रमmation
 *
 * Callback to provide inक्रमmation about a pin चयन control.
 */
पूर्णांक snd_soc_dapm_info_pin_चयन(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_info_pin_चयन);

/**
 * snd_soc_dapm_get_pin_चयन - Get inक्रमmation क्रम a pin चयन
 *
 * @kcontrol: mixer control
 * @ucontrol: Value
 */
पूर्णांक snd_soc_dapm_get_pin_चयन(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	स्थिर अक्षर *pin = (स्थिर अक्षर *)kcontrol->निजी_value;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);

	ucontrol->value.पूर्णांकeger.value[0] =
		snd_soc_dapm_get_pin_status(&card->dapm, pin);

	mutex_unlock(&card->dapm_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_get_pin_चयन);

/**
 * snd_soc_dapm_put_pin_चयन - Set inक्रमmation क्रम a pin चयन
 *
 * @kcontrol: mixer control
 * @ucontrol: Value
 */
पूर्णांक snd_soc_dapm_put_pin_चयन(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	स्थिर अक्षर *pin = (स्थिर अक्षर *)kcontrol->निजी_value;

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		snd_soc_dapm_enable_pin(&card->dapm, pin);
	अन्यथा
		snd_soc_dapm_disable_pin(&card->dapm, pin);

	snd_soc_dapm_sync(&card->dapm);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_put_pin_चयन);

काष्ठा snd_soc_dapm_widget *
snd_soc_dapm_new_control_unlocked(काष्ठा snd_soc_dapm_context *dapm,
			 स्थिर काष्ठा snd_soc_dapm_widget *widget)
अणु
	क्रमागत snd_soc_dapm_direction dir;
	काष्ठा snd_soc_dapm_widget *w;
	स्थिर अक्षर *prefix;
	पूर्णांक ret;

	अगर ((w = dapm_cnew_widget(widget)) == शून्य)
		वापस ERR_PTR(-ENOMEM);

	चयन (w->id) अणु
	हाल snd_soc_dapm_regulator_supply:
		w->regulator = devm_regulator_get(dapm->dev, w->name);
		अगर (IS_ERR(w->regulator)) अणु
			ret = PTR_ERR(w->regulator);
			जाओ request_failed;
		पूर्ण

		अगर (w->on_val & SND_SOC_DAPM_REGULATOR_BYPASS) अणु
			ret = regulator_allow_bypass(w->regulator, true);
			अगर (ret != 0)
				dev_warn(dapm->dev,
					 "ASoC: Failed to bypass %s: %d\n",
					 w->name, ret);
		पूर्ण
		अवरोध;
	हाल snd_soc_dapm_pinctrl:
		w->pinctrl = devm_pinctrl_get(dapm->dev);
		अगर (IS_ERR(w->pinctrl)) अणु
			ret = PTR_ERR(w->pinctrl);
			जाओ request_failed;
		पूर्ण

		/* set to sleep_state when initializing */
		dapm_pinctrl_event(w, शून्य, SND_SOC_DAPM_POST_PMD);
		अवरोध;
	हाल snd_soc_dapm_घड़ी_supply:
		w->clk = devm_clk_get(dapm->dev, w->name);
		अगर (IS_ERR(w->clk)) अणु
			ret = PTR_ERR(w->clk);
			जाओ request_failed;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	prefix = soc_dapm_prefix(dapm);
	अगर (prefix)
		w->name = kaप्र_लिखो(GFP_KERNEL, "%s %s", prefix, widget->name);
	अन्यथा
		w->name = kstrdup_स्थिर(widget->name, GFP_KERNEL);
	अगर (w->name == शून्य) अणु
		kमुक्त_स्थिर(w->sname);
		kमुक्त(w);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	चयन (w->id) अणु
	हाल snd_soc_dapm_mic:
		w->is_ep = SND_SOC_DAPM_EP_SOURCE;
		w->घातer_check = dapm_generic_check_घातer;
		अवरोध;
	हाल snd_soc_dapm_input:
		अगर (!dapm->card->fully_routed)
			w->is_ep = SND_SOC_DAPM_EP_SOURCE;
		w->घातer_check = dapm_generic_check_घातer;
		अवरोध;
	हाल snd_soc_dapm_spk:
	हाल snd_soc_dapm_hp:
		w->is_ep = SND_SOC_DAPM_EP_SINK;
		w->घातer_check = dapm_generic_check_घातer;
		अवरोध;
	हाल snd_soc_dapm_output:
		अगर (!dapm->card->fully_routed)
			w->is_ep = SND_SOC_DAPM_EP_SINK;
		w->घातer_check = dapm_generic_check_घातer;
		अवरोध;
	हाल snd_soc_dapm_vmid:
	हाल snd_soc_dapm_siggen:
		w->is_ep = SND_SOC_DAPM_EP_SOURCE;
		w->घातer_check = dapm_always_on_check_घातer;
		अवरोध;
	हाल snd_soc_dapm_sink:
		w->is_ep = SND_SOC_DAPM_EP_SINK;
		w->घातer_check = dapm_always_on_check_घातer;
		अवरोध;

	हाल snd_soc_dapm_mux:
	हाल snd_soc_dapm_demux:
	हाल snd_soc_dapm_चयन:
	हाल snd_soc_dapm_mixer:
	हाल snd_soc_dapm_mixer_named_ctl:
	हाल snd_soc_dapm_adc:
	हाल snd_soc_dapm_aअगर_out:
	हाल snd_soc_dapm_dac:
	हाल snd_soc_dapm_aअगर_in:
	हाल snd_soc_dapm_pga:
	हाल snd_soc_dapm_buffer:
	हाल snd_soc_dapm_scheduler:
	हाल snd_soc_dapm_effect:
	हाल snd_soc_dapm_src:
	हाल snd_soc_dapm_asrc:
	हाल snd_soc_dapm_encoder:
	हाल snd_soc_dapm_decoder:
	हाल snd_soc_dapm_out_drv:
	हाल snd_soc_dapm_micbias:
	हाल snd_soc_dapm_line:
	हाल snd_soc_dapm_dai_link:
	हाल snd_soc_dapm_dai_out:
	हाल snd_soc_dapm_dai_in:
		w->घातer_check = dapm_generic_check_घातer;
		अवरोध;
	हाल snd_soc_dapm_supply:
	हाल snd_soc_dapm_regulator_supply:
	हाल snd_soc_dapm_pinctrl:
	हाल snd_soc_dapm_घड़ी_supply:
	हाल snd_soc_dapm_kcontrol:
		w->is_supply = 1;
		w->घातer_check = dapm_supply_check_घातer;
		अवरोध;
	शेष:
		w->घातer_check = dapm_always_on_check_घातer;
		अवरोध;
	पूर्ण

	w->dapm = dapm;
	INIT_LIST_HEAD(&w->list);
	INIT_LIST_HEAD(&w->dirty);
	/* see क्रम_each_card_widमाला_लो */
	list_add_tail(&w->list, &dapm->card->widमाला_लो);

	snd_soc_dapm_क्रम_each_direction(dir) अणु
		INIT_LIST_HEAD(&w->edges[dir]);
		w->endpoपूर्णांकs[dir] = -1;
	पूर्ण

	/* machine layer sets up unconnected pins and insertions */
	w->connected = 1;
	वापस w;

request_failed:
	अगर (ret != -EPROBE_DEFER)
		dev_err(dapm->dev, "ASoC: Failed to request %s: %d\n",
			w->name, ret);

	kमुक्त_स्थिर(w->sname);
	kमुक्त(w);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * snd_soc_dapm_new_control - create new dapm control
 * @dapm: DAPM context
 * @widget: widget ढाँचा
 *
 * Creates new DAPM control based upon a ढाँचा.
 *
 * Returns a widget poपूर्णांकer on success or an error poपूर्णांकer on failure
 */
काष्ठा snd_soc_dapm_widget *
snd_soc_dapm_new_control(काष्ठा snd_soc_dapm_context *dapm,
			 स्थिर काष्ठा snd_soc_dapm_widget *widget)
अणु
	काष्ठा snd_soc_dapm_widget *w;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	w = snd_soc_dapm_new_control_unlocked(dapm, widget);
	mutex_unlock(&dapm->card->dapm_mutex);

	वापस w;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_new_control);

/**
 * snd_soc_dapm_new_controls - create new dapm controls
 * @dapm: DAPM context
 * @widget: widget array
 * @num: number of widमाला_लो
 *
 * Creates new DAPM controls based upon the ढाँचाs.
 *
 * Returns 0 क्रम success अन्यथा error.
 */
पूर्णांक snd_soc_dapm_new_controls(काष्ठा snd_soc_dapm_context *dapm,
	स्थिर काष्ठा snd_soc_dapm_widget *widget,
	पूर्णांक num)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	पूर्णांक i;
	पूर्णांक ret = 0;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_INIT);
	क्रम (i = 0; i < num; i++) अणु
		w = snd_soc_dapm_new_control_unlocked(dapm, widget);
		अगर (IS_ERR(w)) अणु
			ret = PTR_ERR(w);
			अवरोध;
		पूर्ण
		widget++;
	पूर्ण
	mutex_unlock(&dapm->card->dapm_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_new_controls);

अटल पूर्णांक
snd_soc_dai_link_event_pre_pmu(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_dapm_path *path;
	काष्ठा snd_soc_dai *source, *sink;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_hw_params *params = शून्य;
	स्थिर काष्ठा snd_soc_pcm_stream *config = शून्य;
	काष्ठा snd_pcm_runसमय *runसमय = शून्य;
	अचिन्हित पूर्णांक fmt;
	पूर्णांक ret = 0;

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	runसमय = kzalloc(माप(*runसमय), GFP_KERNEL);
	अगर (!runसमय) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	substream->runसमय = runसमय;

	substream->stream = SNDRV_PCM_STREAM_CAPTURE;
	snd_soc_dapm_widget_क्रम_each_source_path(w, path) अणु
		source = path->source->priv;

		ret = snd_soc_dai_startup(source, substream);
		अगर (ret < 0)
			जाओ out;

		snd_soc_dai_activate(source, substream->stream);
	पूर्ण

	substream->stream = SNDRV_PCM_STREAM_PLAYBACK;
	snd_soc_dapm_widget_क्रम_each_sink_path(w, path) अणु
		sink = path->sink->priv;

		ret = snd_soc_dai_startup(sink, substream);
		अगर (ret < 0)
			जाओ out;

		snd_soc_dai_activate(sink, substream->stream);
	पूर्ण

	substream->hw_खोलोed = 1;

	/*
	 * Note: getting the config after .startup() gives a chance to
	 * either party on the link to alter the configuration अगर
	 * necessary
	 */
	config = rtd->dai_link->params + rtd->params_select;
	अगर (WARN_ON(!config)) अणु
		dev_err(w->dapm->dev, "ASoC: link config missing\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Be a little careful as we करोn't want to overflow the mask array */
	अगर (config->क्रमmats) अणु
		fmt = ffs(config->क्रमmats) - 1;
	पूर्ण अन्यथा अणु
		dev_warn(w->dapm->dev, "ASoC: Invalid format %llx specified\n",
			 config->क्रमmats);

		ret = -EINVAL;
		जाओ out;
	पूर्ण

	snd_mask_set(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT), fmt);
	hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE)->min =
		config->rate_min;
	hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE)->max =
		config->rate_max;
	hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS)->min
		= config->channels_min;
	hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS)->max
		= config->channels_max;

	substream->stream = SNDRV_PCM_STREAM_CAPTURE;
	snd_soc_dapm_widget_क्रम_each_source_path(w, path) अणु
		source = path->source->priv;

		ret = snd_soc_dai_hw_params(source, substream, params);
		अगर (ret < 0)
			जाओ out;

		dapm_update_dai_unlocked(substream, params, source);
	पूर्ण

	substream->stream = SNDRV_PCM_STREAM_PLAYBACK;
	snd_soc_dapm_widget_क्रम_each_sink_path(w, path) अणु
		sink = path->sink->priv;

		ret = snd_soc_dai_hw_params(sink, substream, params);
		अगर (ret < 0)
			जाओ out;

		dapm_update_dai_unlocked(substream, params, sink);
	पूर्ण

	runसमय->क्रमmat = params_क्रमmat(params);
	runसमय->subक्रमmat = params_subक्रमmat(params);
	runसमय->channels = params_channels(params);
	runसमय->rate = params_rate(params);

out:
	kमुक्त(params);
	वापस ret;
पूर्ण

अटल पूर्णांक snd_soc_dai_link_event(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_path *path;
	काष्ठा snd_soc_dai *source, *sink;
	काष्ठा snd_pcm_substream *substream = w->priv;
	पूर्णांक ret = 0, saved_stream = substream->stream;

	अगर (WARN_ON(list_empty(&w->edges[SND_SOC_DAPM_सूची_OUT]) ||
		    list_empty(&w->edges[SND_SOC_DAPM_सूची_IN])))
		वापस -EINVAL;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = snd_soc_dai_link_event_pre_pmu(w, substream);
		अगर (ret < 0)
			जाओ out;

		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_dapm_widget_क्रम_each_sink_path(w, path) अणु
			sink = path->sink->priv;

			snd_soc_dai_digital_mute(sink, 0, SNDRV_PCM_STREAM_PLAYBACK);
			ret = 0;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_dapm_widget_क्रम_each_sink_path(w, path) अणु
			sink = path->sink->priv;

			snd_soc_dai_digital_mute(sink, 1, SNDRV_PCM_STREAM_PLAYBACK);
			ret = 0;
		पूर्ण

		substream->stream = SNDRV_PCM_STREAM_CAPTURE;
		snd_soc_dapm_widget_क्रम_each_source_path(w, path) अणु
			source = path->source->priv;
			snd_soc_dai_hw_मुक्त(source, substream, 0);
		पूर्ण

		substream->stream = SNDRV_PCM_STREAM_PLAYBACK;
		snd_soc_dapm_widget_क्रम_each_sink_path(w, path) अणु
			sink = path->sink->priv;
			snd_soc_dai_hw_मुक्त(sink, substream, 0);
		पूर्ण

		substream->stream = SNDRV_PCM_STREAM_CAPTURE;
		snd_soc_dapm_widget_क्रम_each_source_path(w, path) अणु
			source = path->source->priv;
			snd_soc_dai_deactivate(source, substream->stream);
			snd_soc_dai_shutकरोwn(source, substream, 0);
		पूर्ण

		substream->stream = SNDRV_PCM_STREAM_PLAYBACK;
		snd_soc_dapm_widget_क्रम_each_sink_path(w, path) अणु
			sink = path->sink->priv;
			snd_soc_dai_deactivate(sink, substream->stream);
			snd_soc_dai_shutकरोwn(sink, substream, 0);
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		kमुक्त(substream->runसमय);
		अवरोध;

	शेष:
		WARN(1, "Unknown event %d\n", event);
		ret = -EINVAL;
	पूर्ण

out:
	/* Restore the substream direction */
	substream->stream = saved_stream;
	वापस ret;
पूर्ण

अटल पूर्णांक snd_soc_dapm_dai_link_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *w = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_pcm_runसमय *rtd = w->priv;

	ucontrol->value.क्रमागतerated.item[0] = rtd->params_select;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_soc_dapm_dai_link_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_widget *w = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_pcm_runसमय *rtd = w->priv;

	/* Can't change the config when widget is alपढ़ोy घातered */
	अगर (w->घातer)
		वापस -EBUSY;

	अगर (ucontrol->value.क्रमागतerated.item[0] == rtd->params_select)
		वापस 0;

	अगर (ucontrol->value.क्रमागतerated.item[0] >= rtd->dai_link->num_params)
		वापस -EINVAL;

	rtd->params_select = ucontrol->value.क्रमागतerated.item[0];

	वापस 0;
पूर्ण

अटल व्योम
snd_soc_dapm_मुक्त_kcontrol(काष्ठा snd_soc_card *card,
			अचिन्हित दीर्घ *निजी_value,
			पूर्णांक num_params,
			स्थिर अक्षर **w_param_text)
अणु
	पूर्णांक count;

	devm_kमुक्त(card->dev, (व्योम *)*निजी_value);

	अगर (!w_param_text)
		वापस;

	क्रम (count = 0 ; count < num_params; count++)
		devm_kमुक्त(card->dev, (व्योम *)w_param_text[count]);
	devm_kमुक्त(card->dev, w_param_text);
पूर्ण

अटल काष्ठा snd_kcontrol_new *
snd_soc_dapm_alloc_kcontrol(काष्ठा snd_soc_card *card,
			अक्षर *link_name,
			स्थिर काष्ठा snd_soc_pcm_stream *params,
			पूर्णांक num_params, स्थिर अक्षर **w_param_text,
			अचिन्हित दीर्घ *निजी_value)
अणु
	काष्ठा soc_क्रमागत w_param_क्रमागत[] = अणु
		SOC_ENUM_SINGLE(0, 0, 0, शून्य),
	पूर्ण;
	काष्ठा snd_kcontrol_new kcontrol_dai_link[] = अणु
		SOC_ENUM_EXT(शून्य, w_param_क्रमागत[0],
			     snd_soc_dapm_dai_link_get,
			     snd_soc_dapm_dai_link_put),
	पूर्ण;
	काष्ठा snd_kcontrol_new *kcontrol_news;
	स्थिर काष्ठा snd_soc_pcm_stream *config = params;
	पूर्णांक count;

	क्रम (count = 0 ; count < num_params; count++) अणु
		अगर (!config->stream_name) अणु
			dev_warn(card->dapm.dev,
				"ASoC: anonymous config %d for dai link %s\n",
				count, link_name);
			w_param_text[count] =
				devm_kaप्र_लिखो(card->dev, GFP_KERNEL,
					       "Anonymous Configuration %d",
					       count);
		पूर्ण अन्यथा अणु
			w_param_text[count] = devm_kmemdup(card->dev,
						config->stream_name,
						म_माप(config->stream_name) + 1,
						GFP_KERNEL);
		पूर्ण
		अगर (!w_param_text[count])
			जाओ outमुक्त_w_param;
		config++;
	पूर्ण

	w_param_क्रमागत[0].items = num_params;
	w_param_क्रमागत[0].texts = w_param_text;

	*निजी_value =
		(अचिन्हित दीर्घ) devm_kmemdup(card->dev,
			(व्योम *)(kcontrol_dai_link[0].निजी_value),
			माप(काष्ठा soc_क्रमागत), GFP_KERNEL);
	अगर (!*निजी_value) अणु
		dev_err(card->dev, "ASoC: Failed to create control for %s widget\n",
			link_name);
		जाओ outमुक्त_w_param;
	पूर्ण
	kcontrol_dai_link[0].निजी_value = *निजी_value;
	/* duplicate kcontrol_dai_link on heap so that memory persists */
	kcontrol_news = devm_kmemdup(card->dev, &kcontrol_dai_link[0],
					माप(काष्ठा snd_kcontrol_new),
					GFP_KERNEL);
	अगर (!kcontrol_news) अणु
		dev_err(card->dev, "ASoC: Failed to create control for %s widget\n",
			link_name);
		जाओ outमुक्त_w_param;
	पूर्ण
	वापस kcontrol_news;

outमुक्त_w_param:
	snd_soc_dapm_मुक्त_kcontrol(card, निजी_value, num_params, w_param_text);
	वापस शून्य;
पूर्ण

अटल काष्ठा snd_soc_dapm_widget *
snd_soc_dapm_new_dai(काष्ठा snd_soc_card *card,
		     काष्ठा snd_pcm_substream *substream,
		     अक्षर *id)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dapm_widget ढाँचा;
	काष्ठा snd_soc_dapm_widget *w;
	स्थिर अक्षर **w_param_text;
	अचिन्हित दीर्घ निजी_value = 0;
	अक्षर *link_name;
	पूर्णांक ret;

	link_name = devm_kaप्र_लिखो(card->dev, GFP_KERNEL, "%s-%s",
				   rtd->dai_link->name, id);
	अगर (!link_name)
		वापस ERR_PTR(-ENOMEM);

	स_रखो(&ढाँचा, 0, माप(ढाँचा));
	ढाँचा.reg = SND_SOC_NOPM;
	ढाँचा.id = snd_soc_dapm_dai_link;
	ढाँचा.name = link_name;
	ढाँचा.event = snd_soc_dai_link_event;
	ढाँचा.event_flags = SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD;
	ढाँचा.kcontrol_news = शून्य;

	/* allocate memory क्रम control, only in हाल of multiple configs */
	अगर (rtd->dai_link->num_params > 1) अणु
		w_param_text = devm_kसुस्मृति(card->dev,
					    rtd->dai_link->num_params,
					    माप(अक्षर *), GFP_KERNEL);
		अगर (!w_param_text) अणु
			ret = -ENOMEM;
			जाओ param_fail;
		पूर्ण

		ढाँचा.num_kcontrols = 1;
		ढाँचा.kcontrol_news =
					snd_soc_dapm_alloc_kcontrol(card,
						link_name,
						rtd->dai_link->params,
						rtd->dai_link->num_params,
						w_param_text, &निजी_value);
		अगर (!ढाँचा.kcontrol_news) अणु
			ret = -ENOMEM;
			जाओ param_fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		w_param_text = शून्य;
	पूर्ण
	dev_dbg(card->dev, "ASoC: adding %s widget\n", link_name);

	w = snd_soc_dapm_new_control_unlocked(&card->dapm, &ढाँचा);
	अगर (IS_ERR(w)) अणु
		ret = PTR_ERR(w);
		dev_err(rtd->dev, "ASoC: Failed to create %s widget: %d\n",
			link_name, ret);
		जाओ outमुक्त_kcontrol_news;
	पूर्ण

	w->priv = substream;

	वापस w;

outमुक्त_kcontrol_news:
	devm_kमुक्त(card->dev, (व्योम *)ढाँचा.kcontrol_news);
	snd_soc_dapm_मुक्त_kcontrol(card, &निजी_value,
				   rtd->dai_link->num_params, w_param_text);
param_fail:
	devm_kमुक्त(card->dev, link_name);
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक snd_soc_dapm_new_dai_widमाला_लो(काष्ठा snd_soc_dapm_context *dapm,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_dapm_widget ढाँचा;
	काष्ठा snd_soc_dapm_widget *w;

	WARN_ON(dapm->dev != dai->dev);

	स_रखो(&ढाँचा, 0, माप(ढाँचा));
	ढाँचा.reg = SND_SOC_NOPM;

	अगर (dai->driver->playback.stream_name) अणु
		ढाँचा.id = snd_soc_dapm_dai_in;
		ढाँचा.name = dai->driver->playback.stream_name;
		ढाँचा.sname = dai->driver->playback.stream_name;

		dev_dbg(dai->dev, "ASoC: adding %s widget\n",
			ढाँचा.name);

		w = snd_soc_dapm_new_control_unlocked(dapm, &ढाँचा);
		अगर (IS_ERR(w))
			वापस PTR_ERR(w);

		w->priv = dai;
		dai->playback_widget = w;
	पूर्ण

	अगर (dai->driver->capture.stream_name) अणु
		ढाँचा.id = snd_soc_dapm_dai_out;
		ढाँचा.name = dai->driver->capture.stream_name;
		ढाँचा.sname = dai->driver->capture.stream_name;

		dev_dbg(dai->dev, "ASoC: adding %s widget\n",
			ढाँचा.name);

		w = snd_soc_dapm_new_control_unlocked(dapm, &ढाँचा);
		अगर (IS_ERR(w))
			वापस PTR_ERR(w);

		w->priv = dai;
		dai->capture_widget = w;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_soc_dapm_link_dai_widमाला_लो(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dapm_widget *dai_w, *w;
	काष्ठा snd_soc_dapm_widget *src, *sink;
	काष्ठा snd_soc_dai *dai;

	/* For each DAI widget... */
	क्रम_each_card_widमाला_लो(card, dai_w) अणु
		चयन (dai_w->id) अणु
		हाल snd_soc_dapm_dai_in:
		हाल snd_soc_dapm_dai_out:
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		/* let users know there is no DAI to link */
		अगर (!dai_w->priv) अणु
			dev_dbg(card->dev, "dai widget %s has no DAI\n",
				dai_w->name);
			जारी;
		पूर्ण

		dai = dai_w->priv;

		/* ...find all widमाला_लो with the same stream and link them */
		क्रम_each_card_widमाला_लो(card, w) अणु
			अगर (w->dapm != dai_w->dapm)
				जारी;

			चयन (w->id) अणु
			हाल snd_soc_dapm_dai_in:
			हाल snd_soc_dapm_dai_out:
				जारी;
			शेष:
				अवरोध;
			पूर्ण

			अगर (!w->sname || !म_माला(w->sname, dai_w->sname))
				जारी;

			अगर (dai_w->id == snd_soc_dapm_dai_in) अणु
				src = dai_w;
				sink = w;
			पूर्ण अन्यथा अणु
				src = w;
				sink = dai_w;
			पूर्ण
			dev_dbg(dai->dev, "%s -> %s\n", src->name, sink->name);
			snd_soc_dapm_add_path(w->dapm, src, sink, शून्य, शून्य);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dapm_connect_dai_routes(काष्ठा snd_soc_dapm_context *dapm,
				    काष्ठा snd_soc_dai *src_dai,
				    काष्ठा snd_soc_dapm_widget *src,
				    काष्ठा snd_soc_dapm_widget *dai,
				    काष्ठा snd_soc_dai *sink_dai,
				    काष्ठा snd_soc_dapm_widget *sink)
अणु
	dev_dbg(dapm->dev, "connected DAI link %s:%s -> %s:%s\n",
		src_dai->component->name, src->name,
		sink_dai->component->name, sink->name);

	अगर (dai) अणु
		snd_soc_dapm_add_path(dapm, src, dai, शून्य, शून्य);
		src = dai;
	पूर्ण

	snd_soc_dapm_add_path(dapm, src, sink, शून्य, शून्य);
पूर्ण

अटल व्योम dapm_connect_dai_pair(काष्ठा snd_soc_card *card,
				  काष्ठा snd_soc_pcm_runसमय *rtd,
				  काष्ठा snd_soc_dai *codec_dai,
				  काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_dai_link *dai_link = rtd->dai_link;
	काष्ठा snd_soc_dapm_widget *dai, *codec, *playback_cpu, *capture_cpu;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_str *streams = rtd->pcm->streams;

	अगर (dai_link->params) अणु
		playback_cpu = cpu_dai->capture_widget;
		capture_cpu = cpu_dai->playback_widget;
	पूर्ण अन्यथा अणु
		playback_cpu = cpu_dai->playback_widget;
		capture_cpu = cpu_dai->capture_widget;
	पूर्ण

	/* connect BE DAI playback अगर widमाला_लो are valid */
	codec = codec_dai->playback_widget;

	अगर (playback_cpu && codec) अणु
		अगर (dai_link->params && !rtd->playback_widget) अणु
			substream = streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
			dai = snd_soc_dapm_new_dai(card, substream, "playback");
			अगर (IS_ERR(dai))
				जाओ capture;
			rtd->playback_widget = dai;
		पूर्ण

		dapm_connect_dai_routes(&card->dapm, cpu_dai, playback_cpu,
					rtd->playback_widget,
					codec_dai, codec);
	पूर्ण

capture:
	/* connect BE DAI capture अगर widमाला_लो are valid */
	codec = codec_dai->capture_widget;

	अगर (codec && capture_cpu) अणु
		अगर (dai_link->params && !rtd->capture_widget) अणु
			substream = streams[SNDRV_PCM_STREAM_CAPTURE].substream;
			dai = snd_soc_dapm_new_dai(card, substream, "capture");
			अगर (IS_ERR(dai))
				वापस;
			rtd->capture_widget = dai;
		पूर्ण

		dapm_connect_dai_routes(&card->dapm, codec_dai, codec,
					rtd->capture_widget,
					cpu_dai, capture_cpu);
	पूर्ण
पूर्ण

अटल व्योम soc_dapm_dai_stream_event(काष्ठा snd_soc_dai *dai, पूर्णांक stream,
	पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	अचिन्हित पूर्णांक ep;

	w = snd_soc_dai_get_widget(dai, stream);

	अगर (w) अणु
		dapm_mark_dirty(w, "stream event");

		अगर (w->id == snd_soc_dapm_dai_in) अणु
			ep = SND_SOC_DAPM_EP_SOURCE;
			dapm_widget_invalidate_input_paths(w);
		पूर्ण अन्यथा अणु
			ep = SND_SOC_DAPM_EP_SINK;
			dapm_widget_invalidate_output_paths(w);
		पूर्ण

		चयन (event) अणु
		हाल SND_SOC_DAPM_STREAM_START:
			w->active = 1;
			w->is_ep = ep;
			अवरोध;
		हाल SND_SOC_DAPM_STREAM_STOP:
			w->active = 0;
			w->is_ep = 0;
			अवरोध;
		हाल SND_SOC_DAPM_STREAM_SUSPEND:
		हाल SND_SOC_DAPM_STREAM_RESUME:
		हाल SND_SOC_DAPM_STREAM_PAUSE_PUSH:
		हाल SND_SOC_DAPM_STREAM_PAUSE_RELEASE:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम snd_soc_dapm_connect_dai_link_widमाला_लो(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक i;

	/* क्रम each BE DAI link... */
	क्रम_each_card_rtds(card, rtd)  अणु
		/*
		 * dynamic FE links have no fixed DAI mapping.
		 * CODEC<->CODEC links have no direct connection.
		 */
		अगर (rtd->dai_link->dynamic)
			जारी;

		अगर (rtd->num_cpus == 1) अणु
			क्रम_each_rtd_codec_dais(rtd, i, codec_dai)
				dapm_connect_dai_pair(card, rtd, codec_dai,
						      asoc_rtd_to_cpu(rtd, 0));
		पूर्ण अन्यथा अगर (rtd->num_codecs == rtd->num_cpus) अणु
			क्रम_each_rtd_codec_dais(rtd, i, codec_dai)
				dapm_connect_dai_pair(card, rtd, codec_dai,
						      asoc_rtd_to_cpu(rtd, i));
		पूर्ण अन्यथा अणु
			dev_err(card->dev,
				"N cpus to M codecs link is not supported yet\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम soc_dapm_stream_event(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक stream,
	पूर्णांक event)
अणु
	काष्ठा snd_soc_dai *dai;
	पूर्णांक i;

	क्रम_each_rtd_dais(rtd, i, dai)
		soc_dapm_dai_stream_event(dai, stream, event);

	dapm_घातer_widमाला_लो(rtd->card, event);
पूर्ण

/**
 * snd_soc_dapm_stream_event - send a stream event to the dapm core
 * @rtd: PCM runसमय data
 * @stream: stream name
 * @event: stream event
 *
 * Sends a stream event to the dapm core. The core then makes any
 * necessary widget घातer changes.
 *
 * Returns 0 क्रम success अन्यथा error.
 */
व्योम snd_soc_dapm_stream_event(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक stream,
			      पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = rtd->card;

	mutex_lock_nested(&card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);
	soc_dapm_stream_event(rtd, stream, event);
	mutex_unlock(&card->dapm_mutex);
पूर्ण

व्योम snd_soc_dapm_stream_stop(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक stream)
अणु
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (snd_soc_runसमय_ignore_pmकरोwn_समय(rtd)) अणु
			/* घातered करोwn playback stream now */
			snd_soc_dapm_stream_event(rtd,
						  SNDRV_PCM_STREAM_PLAYBACK,
						  SND_SOC_DAPM_STREAM_STOP);
		पूर्ण अन्यथा अणु
			/* start delayed pop wq here क्रम playback streams */
			rtd->pop_रुको = 1;
			queue_delayed_work(प्रणाली_घातer_efficient_wq,
					   &rtd->delayed_work,
					   msecs_to_jअगरfies(rtd->pmकरोwn_समय));
		पूर्ण
	पूर्ण अन्यथा अणु
		/* capture streams can be घातered करोwn now */
		snd_soc_dapm_stream_event(rtd, SNDRV_PCM_STREAM_CAPTURE,
					  SND_SOC_DAPM_STREAM_STOP);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_stream_stop);

/**
 * snd_soc_dapm_enable_pin_unlocked - enable pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Enables input/output pin and its parents or children widमाला_लो अगरf there is
 * a valid audio route and active audio stream.
 *
 * Requires बाह्यal locking.
 *
 * NOTE: snd_soc_dapm_sync() needs to be called after this क्रम DAPM to
 * करो any widget घातer चयनing.
 */
पूर्णांक snd_soc_dapm_enable_pin_unlocked(काष्ठा snd_soc_dapm_context *dapm,
				   स्थिर अक्षर *pin)
अणु
	वापस snd_soc_dapm_set_pin(dapm, pin, 1);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_enable_pin_unlocked);

/**
 * snd_soc_dapm_enable_pin - enable pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Enables input/output pin and its parents or children widमाला_लो अगरf there is
 * a valid audio route and active audio stream.
 *
 * NOTE: snd_soc_dapm_sync() needs to be called after this क्रम DAPM to
 * करो any widget घातer चयनing.
 */
पूर्णांक snd_soc_dapm_enable_pin(काष्ठा snd_soc_dapm_context *dapm, स्थिर अक्षर *pin)
अणु
	पूर्णांक ret;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);

	ret = snd_soc_dapm_set_pin(dapm, pin, 1);

	mutex_unlock(&dapm->card->dapm_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_enable_pin);

/**
 * snd_soc_dapm_क्रमce_enable_pin_unlocked - क्रमce a pin to be enabled
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Enables input/output pin regardless of any other state.  This is
 * पूर्णांकended क्रम use with microphone bias supplies used in microphone
 * jack detection.
 *
 * Requires बाह्यal locking.
 *
 * NOTE: snd_soc_dapm_sync() needs to be called after this क्रम DAPM to
 * करो any widget घातer चयनing.
 */
पूर्णांक snd_soc_dapm_क्रमce_enable_pin_unlocked(काष्ठा snd_soc_dapm_context *dapm,
					 स्थिर अक्षर *pin)
अणु
	काष्ठा snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, true);

	अगर (!w) अणु
		dev_err(dapm->dev, "ASoC: unknown pin %s\n", pin);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(w->dapm->dev, "ASoC: force enable pin %s\n", pin);
	अगर (!w->connected) अणु
		/*
		 * w->क्रमce करोes not affect the number of input or output paths,
		 * so we only have to recheck अगर w->connected is changed
		 */
		dapm_widget_invalidate_input_paths(w);
		dapm_widget_invalidate_output_paths(w);
		w->connected = 1;
	पूर्ण
	w->क्रमce = 1;
	dapm_mark_dirty(w, "force enable");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_क्रमce_enable_pin_unlocked);

/**
 * snd_soc_dapm_क्रमce_enable_pin - क्रमce a pin to be enabled
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Enables input/output pin regardless of any other state.  This is
 * पूर्णांकended क्रम use with microphone bias supplies used in microphone
 * jack detection.
 *
 * NOTE: snd_soc_dapm_sync() needs to be called after this क्रम DAPM to
 * करो any widget घातer चयनing.
 */
पूर्णांक snd_soc_dapm_क्रमce_enable_pin(काष्ठा snd_soc_dapm_context *dapm,
				  स्थिर अक्षर *pin)
अणु
	पूर्णांक ret;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);

	ret = snd_soc_dapm_क्रमce_enable_pin_unlocked(dapm, pin);

	mutex_unlock(&dapm->card->dapm_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_क्रमce_enable_pin);

/**
 * snd_soc_dapm_disable_pin_unlocked - disable pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Disables input/output pin and its parents or children widमाला_लो.
 *
 * Requires बाह्यal locking.
 *
 * NOTE: snd_soc_dapm_sync() needs to be called after this क्रम DAPM to
 * करो any widget घातer चयनing.
 */
पूर्णांक snd_soc_dapm_disable_pin_unlocked(काष्ठा snd_soc_dapm_context *dapm,
				    स्थिर अक्षर *pin)
अणु
	वापस snd_soc_dapm_set_pin(dapm, pin, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_disable_pin_unlocked);

/**
 * snd_soc_dapm_disable_pin - disable pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Disables input/output pin and its parents or children widमाला_लो.
 *
 * NOTE: snd_soc_dapm_sync() needs to be called after this क्रम DAPM to
 * करो any widget घातer चयनing.
 */
पूर्णांक snd_soc_dapm_disable_pin(काष्ठा snd_soc_dapm_context *dapm,
			     स्थिर अक्षर *pin)
अणु
	पूर्णांक ret;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);

	ret = snd_soc_dapm_set_pin(dapm, pin, 0);

	mutex_unlock(&dapm->card->dapm_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_disable_pin);

/**
 * snd_soc_dapm_nc_pin_unlocked - permanently disable pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Marks the specअगरied pin as being not connected, disabling it aदीर्घ
 * any parent or child widमाला_लो.  At present this is identical to
 * snd_soc_dapm_disable_pin() but in future it will be extended to करो
 * additional things such as disabling controls which only affect
 * paths through the pin.
 *
 * Requires बाह्यal locking.
 *
 * NOTE: snd_soc_dapm_sync() needs to be called after this क्रम DAPM to
 * करो any widget घातer चयनing.
 */
पूर्णांक snd_soc_dapm_nc_pin_unlocked(काष्ठा snd_soc_dapm_context *dapm,
			       स्थिर अक्षर *pin)
अणु
	वापस snd_soc_dapm_set_pin(dapm, pin, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_nc_pin_unlocked);

/**
 * snd_soc_dapm_nc_pin - permanently disable pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Marks the specअगरied pin as being not connected, disabling it aदीर्घ
 * any parent or child widमाला_लो.  At present this is identical to
 * snd_soc_dapm_disable_pin() but in future it will be extended to करो
 * additional things such as disabling controls which only affect
 * paths through the pin.
 *
 * NOTE: snd_soc_dapm_sync() needs to be called after this क्रम DAPM to
 * करो any widget घातer चयनing.
 */
पूर्णांक snd_soc_dapm_nc_pin(काष्ठा snd_soc_dapm_context *dapm, स्थिर अक्षर *pin)
अणु
	पूर्णांक ret;

	mutex_lock_nested(&dapm->card->dapm_mutex, SND_SOC_DAPM_CLASS_RUNTIME);

	ret = snd_soc_dapm_set_pin(dapm, pin, 0);

	mutex_unlock(&dapm->card->dapm_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_nc_pin);

/**
 * snd_soc_dapm_get_pin_status - get audio pin status
 * @dapm: DAPM context
 * @pin: audio संकेत pin endpoपूर्णांक (or start poपूर्णांक)
 *
 * Get audio pin status - connected or disconnected.
 *
 * Returns 1 क्रम connected otherwise 0.
 */
पूर्णांक snd_soc_dapm_get_pin_status(काष्ठा snd_soc_dapm_context *dapm,
				स्थिर अक्षर *pin)
अणु
	काष्ठा snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, true);

	अगर (w)
		वापस w->connected;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_get_pin_status);

/**
 * snd_soc_dapm_ignore_suspend - ignore suspend status क्रम DAPM endpoपूर्णांक
 * @dapm: DAPM context
 * @pin: audio संकेत pin endpoपूर्णांक (or start poपूर्णांक)
 *
 * Mark the given endpoपूर्णांक or pin as ignoring suspend.  When the
 * प्रणाली is disabled a path between two endpoपूर्णांकs flagged as ignoring
 * suspend will not be disabled.  The path must alपढ़ोy be enabled via
 * normal means at suspend समय, it will not be turned on अगर it was not
 * alपढ़ोy enabled.
 */
पूर्णांक snd_soc_dapm_ignore_suspend(काष्ठा snd_soc_dapm_context *dapm,
				स्थिर अक्षर *pin)
अणु
	काष्ठा snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, false);

	अगर (!w) अणु
		dev_err(dapm->dev, "ASoC: unknown pin %s\n", pin);
		वापस -EINVAL;
	पूर्ण

	w->ignore_suspend = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_ignore_suspend);

/**
 * snd_soc_dapm_मुक्त - मुक्त dapm resources
 * @dapm: DAPM context
 *
 * Free all dapm widमाला_लो and resources.
 */
व्योम snd_soc_dapm_मुक्त(काष्ठा snd_soc_dapm_context *dapm)
अणु
	dapm_debugfs_cleanup(dapm);
	dapm_मुक्त_widमाला_लो(dapm);
	list_del(&dapm->list);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_मुक्त);

व्योम snd_soc_dapm_init(काष्ठा snd_soc_dapm_context *dapm,
		       काष्ठा snd_soc_card *card,
		       काष्ठा snd_soc_component *component)
अणु
	dapm->card		= card;
	dapm->component		= component;
	dapm->bias_level	= SND_SOC_BIAS_OFF;

	अगर (component) अणु
		dapm->dev		= component->dev;
		dapm->idle_bias_off	= !component->driver->idle_bias_on;
		dapm->suspend_bias_off	= component->driver->suspend_bias_off;
	पूर्ण अन्यथा अणु
		dapm->dev		= card->dev;
	पूर्ण

	INIT_LIST_HEAD(&dapm->list);
	/* see क्रम_each_card_dapms */
	list_add(&dapm->list, &card->dapm_list);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_dapm_init);

अटल व्योम soc_dapm_shutकरोwn_dapm(काष्ठा snd_soc_dapm_context *dapm)
अणु
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dapm_widget *w;
	LIST_HEAD(करोwn_list);
	पूर्णांक घातerकरोwn = 0;

	mutex_lock(&card->dapm_mutex);

	क्रम_each_card_widमाला_लो(dapm->card, w) अणु
		अगर (w->dapm != dapm)
			जारी;
		अगर (w->घातer) अणु
			dapm_seq_insert(w, &करोwn_list, false);
			w->new_घातer = 0;
			घातerकरोwn = 1;
		पूर्ण
	पूर्ण

	/* If there were no widमाला_लो to घातer करोwn we're alपढ़ोy in
	 * standby.
	 */
	अगर (घातerकरोwn) अणु
		अगर (dapm->bias_level == SND_SOC_BIAS_ON)
			snd_soc_dapm_set_bias_level(dapm,
						    SND_SOC_BIAS_PREPARE);
		dapm_seq_run(card, &करोwn_list, 0, false);
		अगर (dapm->bias_level == SND_SOC_BIAS_PREPARE)
			snd_soc_dapm_set_bias_level(dapm,
						    SND_SOC_BIAS_STANDBY);
	पूर्ण

	mutex_unlock(&card->dapm_mutex);
पूर्ण

/*
 * snd_soc_dapm_shutकरोwn - callback क्रम प्रणाली shutकरोwn
 */
व्योम snd_soc_dapm_shutकरोwn(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dapm_context *dapm;

	क्रम_each_card_dapms(card, dapm) अणु
		अगर (dapm != &card->dapm) अणु
			soc_dapm_shutकरोwn_dapm(dapm);
			अगर (dapm->bias_level == SND_SOC_BIAS_STANDBY)
				snd_soc_dapm_set_bias_level(dapm,
							    SND_SOC_BIAS_OFF);
		पूर्ण
	पूर्ण

	soc_dapm_shutकरोwn_dapm(&card->dapm);
	अगर (card->dapm.bias_level == SND_SOC_BIAS_STANDBY)
		snd_soc_dapm_set_bias_level(&card->dapm,
					    SND_SOC_BIAS_OFF);
पूर्ण

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood, lrg@slimlogic.co.uk");
MODULE_DESCRIPTION("Dynamic Audio Power Management core for ALSA SoC");
MODULE_LICENSE("GPL");
