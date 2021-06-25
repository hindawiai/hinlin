<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus Audio Sound SoC helper APIs
 */

#अगर_अघोषित __LINUX_GBAUDIO_HELPER_H
#घोषणा __LINUX_GBAUDIO_HELPER_H

पूर्णांक gbaudio_dapm_link_component_dai_widमाला_लो(काष्ठा snd_soc_card *card,
					    काष्ठा snd_soc_dapm_context *dapm);
पूर्णांक gbaudio_dapm_मुक्त_controls(काष्ठा snd_soc_dapm_context *dapm,
			       स्थिर काष्ठा snd_soc_dapm_widget *widget,
			       पूर्णांक num);
पूर्णांक gbaudio_हटाओ_component_controls(काष्ठा snd_soc_component *component,
				      स्थिर काष्ठा snd_kcontrol_new *controls,
				      अचिन्हित पूर्णांक num_controls);
#पूर्ण_अगर
