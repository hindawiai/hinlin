<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Audio Sound SoC helper APIs
 */

#समावेश <linux/debugfs.h>
#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश "audio_helper.h"

#घोषणा gbaudio_dapm_क्रम_each_direction(dir) \
	क्रम ((dir) = SND_SOC_DAPM_सूची_IN; (dir) <= SND_SOC_DAPM_सूची_OUT; \
		(dir)++)

अटल व्योम gbaudio_dapm_link_dai_widget(काष्ठा snd_soc_dapm_widget *dai_w,
					 काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dapm_widget *w;
	काष्ठा snd_soc_dapm_widget *src, *sink;
	काष्ठा snd_soc_dai *dai = dai_w->priv;

	/* ...find all widमाला_लो with the same stream and link them */
	list_क्रम_each_entry(w, &card->widमाला_लो, list) अणु
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

		/*
		 * check अगर widget is alपढ़ोy linked,
		 * अगर (w->linked)
		 *	वापस;
		 */

		अगर (dai_w->id == snd_soc_dapm_dai_in) अणु
			src = dai_w;
			sink = w;
		पूर्ण अन्यथा अणु
			src = w;
			sink = dai_w;
		पूर्ण
		dev_dbg(dai->dev, "%s -> %s\n", src->name, sink->name);
		/* Add the DAPM path and set widget's linked status
		 * snd_soc_dapm_add_path(w->dapm, src, sink, शून्य, शून्य);
		 * w->linked = 1;
		 */
	पूर्ण
पूर्ण

पूर्णांक gbaudio_dapm_link_component_dai_widमाला_लो(काष्ठा snd_soc_card *card,
					    काष्ठा snd_soc_dapm_context *dapm)
अणु
	काष्ठा snd_soc_dapm_widget *dai_w;

	/* For each DAI widget... */
	list_क्रम_each_entry(dai_w, &card->widमाला_लो, list) अणु
		अगर (dai_w->dapm != dapm)
			जारी;
		चयन (dai_w->id) अणु
		हाल snd_soc_dapm_dai_in:
		हाल snd_soc_dapm_dai_out:
			अवरोध;
		शेष:
			जारी;
		पूर्ण
		gbaudio_dapm_link_dai_widget(dai_w, card);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gbaudio_dapm_मुक्त_path(काष्ठा snd_soc_dapm_path *path)
अणु
	list_del(&path->list_node[SND_SOC_DAPM_सूची_IN]);
	list_del(&path->list_node[SND_SOC_DAPM_सूची_OUT]);
	list_del(&path->list_kcontrol);
	list_del(&path->list);
	kमुक्त(path);
पूर्ण

अटल व्योम gbaudio_dapm_मुक्त_widget(काष्ठा snd_soc_dapm_widget *w)
अणु
	काष्ठा snd_soc_dapm_path *p, *next_p;
	क्रमागत snd_soc_dapm_direction dir;

	list_del(&w->list);
	/*
	 * हटाओ source and sink paths associated to this widget.
	 * While removing the path, हटाओ reference to it from both
	 * source and sink widमाला_लो so that path is हटाओd only once.
	 */
	gbaudio_dapm_क्रम_each_direction(dir) अणु
		snd_soc_dapm_widget_क्रम_each_path_safe(w, dir, p, next_p)
			gbaudio_dapm_मुक्त_path(p);
	पूर्ण

	kमुक्त(w->kcontrols);
	kमुक्त_स्थिर(w->name);
	kमुक्त_स्थिर(w->sname);
	kमुक्त(w);
पूर्ण

पूर्णांक gbaudio_dapm_मुक्त_controls(काष्ठा snd_soc_dapm_context *dapm,
			       स्थिर काष्ठा snd_soc_dapm_widget *widget,
			       पूर्णांक num)
अणु
	पूर्णांक i;
	काष्ठा snd_soc_dapm_widget *w, *next_w;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *parent = dapm->debugfs_dapm;
	काष्ठा dentry *debugfs_w = शून्य;
#पूर्ण_अगर

	mutex_lock(&dapm->card->dapm_mutex);
	क्रम (i = 0; i < num; i++) अणु
		/* below logic can be optimized to identअगरy widget poपूर्णांकer */
		list_क्रम_each_entry_safe(w, next_w, &dapm->card->widमाला_लो,
					 list) अणु
			अगर (w->dapm != dapm)
				जारी;
			अगर (!म_भेद(w->name, widget->name))
				अवरोध;
			w = शून्य;
		पूर्ण
		अगर (!w) अणु
			dev_err(dapm->dev, "%s: widget not found\n",
				widget->name);
			widget++;
			जारी;
		पूर्ण
		widget++;
#अगर_घोषित CONFIG_DEBUG_FS
		अगर (!parent)
			debugfs_w = debugfs_lookup(w->name, parent);
		debugfs_हटाओ(debugfs_w);
		debugfs_w = शून्य;
#पूर्ण_अगर
		gbaudio_dapm_मुक्त_widget(w);
	पूर्ण
	mutex_unlock(&dapm->card->dapm_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक gbaudio_हटाओ_controls(काष्ठा snd_card *card, काष्ठा device *dev,
				   स्थिर काष्ठा snd_kcontrol_new *controls,
				   पूर्णांक num_controls, स्थिर अक्षर *prefix)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < num_controls; i++) अणु
		स्थिर काष्ठा snd_kcontrol_new *control = &controls[i];
		काष्ठा snd_ctl_elem_id id;
		काष्ठा snd_kcontrol *kctl;

		अगर (prefix)
			snम_लिखो(id.name, माप(id.name), "%s %s", prefix,
				 control->name);
		अन्यथा
			strscpy(id.name, control->name, माप(id.name));
		id.numid = 0;
		id.अगरace = control->अगरace;
		id.device = control->device;
		id.subdevice = control->subdevice;
		id.index = control->index;
		kctl = snd_ctl_find_id(card, &id);
		अगर (!kctl) अणु
			dev_err(dev, "Failed to find %s\n", control->name);
			जारी;
		पूर्ण
		err = snd_ctl_हटाओ(card, kctl);
		अगर (err < 0) अणु
			dev_err(dev, "%d: Failed to remove %s\n", err,
				control->name);
			जारी;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक gbaudio_हटाओ_component_controls(काष्ठा snd_soc_component *component,
				      स्थिर काष्ठा snd_kcontrol_new *controls,
				      अचिन्हित पूर्णांक num_controls)
अणु
	काष्ठा snd_card *card = component->card->snd_card;

	वापस gbaudio_हटाओ_controls(card, component->dev, controls,
				       num_controls, component->name_prefix);
पूर्ण
