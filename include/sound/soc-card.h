<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * soc-card.h
 *
 * Copyright (C) 2019 Renesas Electronics Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#अगर_अघोषित __SOC_CARD_H
#घोषणा __SOC_CARD_H

क्रमागत snd_soc_card_subclass अणु
	SND_SOC_CARD_CLASS_INIT		= 0,
	SND_SOC_CARD_CLASS_RUNTIME	= 1,
पूर्ण;

काष्ठा snd_kcontrol *snd_soc_card_get_kcontrol(काष्ठा snd_soc_card *soc_card,
					       स्थिर अक्षर *name);
पूर्णांक snd_soc_card_jack_new(काष्ठा snd_soc_card *card, स्थिर अक्षर *id, पूर्णांक type,
			  काष्ठा snd_soc_jack *jack,
			  काष्ठा snd_soc_jack_pin *pins, अचिन्हित पूर्णांक num_pins);

पूर्णांक snd_soc_card_suspend_pre(काष्ठा snd_soc_card *card);
पूर्णांक snd_soc_card_suspend_post(काष्ठा snd_soc_card *card);
पूर्णांक snd_soc_card_resume_pre(काष्ठा snd_soc_card *card);
पूर्णांक snd_soc_card_resume_post(काष्ठा snd_soc_card *card);

पूर्णांक snd_soc_card_probe(काष्ठा snd_soc_card *card);
पूर्णांक snd_soc_card_late_probe(काष्ठा snd_soc_card *card);
पूर्णांक snd_soc_card_हटाओ(काष्ठा snd_soc_card *card);

पूर्णांक snd_soc_card_set_bias_level(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_dapm_context *dapm,
				क्रमागत snd_soc_bias_level level);
पूर्णांक snd_soc_card_set_bias_level_post(काष्ठा snd_soc_card *card,
				     काष्ठा snd_soc_dapm_context *dapm,
				     क्रमागत snd_soc_bias_level level);

पूर्णांक snd_soc_card_add_dai_link(काष्ठा snd_soc_card *card,
			      काष्ठा snd_soc_dai_link *dai_link);
व्योम snd_soc_card_हटाओ_dai_link(काष्ठा snd_soc_card *card,
				  काष्ठा snd_soc_dai_link *dai_link);

/* device driver data */
अटल अंतरभूत व्योम snd_soc_card_set_drvdata(काष्ठा snd_soc_card *card,
					    व्योम *data)
अणु
	card->drvdata = data;
पूर्ण

अटल अंतरभूत व्योम *snd_soc_card_get_drvdata(काष्ठा snd_soc_card *card)
अणु
	वापस card->drvdata;
पूर्ण

अटल अंतरभूत
काष्ठा snd_soc_dai *snd_soc_card_get_codec_dai(काष्ठा snd_soc_card *card,
					       स्थिर अक्षर *dai_name)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;

	क्रम_each_card_rtds(card, rtd) अणु
		अगर (!म_भेद(asoc_rtd_to_codec(rtd, 0)->name, dai_name))
			वापस asoc_rtd_to_codec(rtd, 0);
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* __SOC_CARD_H */
