<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// soc-card.c
//
// Copyright (C) 2019 Renesas Electronics Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
//
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#घोषणा soc_card_ret(dai, ret) _soc_card_ret(dai, __func__, ret)
अटल अंतरभूत पूर्णांक _soc_card_ret(काष्ठा snd_soc_card *card,
				स्थिर अक्षर *func, पूर्णांक ret)
अणु
	चयन (ret) अणु
	हाल -EPROBE_DEFER:
	हाल -ENOTSUPP:
	हाल 0:
		अवरोध;
	शेष:
		dev_err(card->dev,
			"ASoC: error at %s on %s: %d\n",
			func, card->name, ret);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा snd_kcontrol *snd_soc_card_get_kcontrol(काष्ठा snd_soc_card *soc_card,
					       स्थिर अक्षर *name)
अणु
	काष्ठा snd_card *card = soc_card->snd_card;
	काष्ठा snd_kcontrol *kctl;

	अगर (unlikely(!name))
		वापस शून्य;

	list_क्रम_each_entry(kctl, &card->controls, list)
		अगर (!म_भेदन(kctl->id.name, name, माप(kctl->id.name)))
			वापस kctl;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_card_get_kcontrol);

/**
 * snd_soc_card_jack_new - Create a new jack
 * @card:  ASoC card
 * @id:    an identअगरying string क्रम this jack
 * @type:  a biपंचांगask of क्रमागत snd_jack_type values that can be detected by
 *         this jack
 * @jack:  काष्ठाure to use क्रम the jack
 * @pins:  Array of jack pins to be added to the jack or शून्य
 * @num_pins: Number of elements in the @pins array
 *
 * Creates a new jack object.
 *
 * Returns zero अगर successful, or a negative error code on failure.
 * On success jack will be initialised.
 */
पूर्णांक snd_soc_card_jack_new(काष्ठा snd_soc_card *card, स्थिर अक्षर *id, पूर्णांक type,
			  काष्ठा snd_soc_jack *jack,
			  काष्ठा snd_soc_jack_pin *pins, अचिन्हित पूर्णांक num_pins)
अणु
	पूर्णांक ret;

	mutex_init(&jack->mutex);
	jack->card = card;
	INIT_LIST_HEAD(&jack->pins);
	INIT_LIST_HEAD(&jack->jack_zones);
	BLOCKING_INIT_NOTIFIER_HEAD(&jack->notअगरier);

	ret = snd_jack_new(card->snd_card, id, type, &jack->jack, false, false);
	अगर (ret)
		जाओ end;

	अगर (num_pins)
		ret = snd_soc_jack_add_pins(jack, num_pins, pins);
end:
	वापस soc_card_ret(card, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_card_jack_new);

पूर्णांक snd_soc_card_suspend_pre(काष्ठा snd_soc_card *card)
अणु
	पूर्णांक ret = 0;

	अगर (card->suspend_pre)
		ret = card->suspend_pre(card);

	वापस soc_card_ret(card, ret);
पूर्ण

पूर्णांक snd_soc_card_suspend_post(काष्ठा snd_soc_card *card)
अणु
	पूर्णांक ret = 0;

	अगर (card->suspend_post)
		ret = card->suspend_post(card);

	वापस soc_card_ret(card, ret);
पूर्ण

पूर्णांक snd_soc_card_resume_pre(काष्ठा snd_soc_card *card)
अणु
	पूर्णांक ret = 0;

	अगर (card->resume_pre)
		ret = card->resume_pre(card);

	वापस soc_card_ret(card, ret);
पूर्ण

पूर्णांक snd_soc_card_resume_post(काष्ठा snd_soc_card *card)
अणु
	पूर्णांक ret = 0;

	अगर (card->resume_post)
		ret = card->resume_post(card);

	वापस soc_card_ret(card, ret);
पूर्ण

पूर्णांक snd_soc_card_probe(काष्ठा snd_soc_card *card)
अणु
	अगर (card->probe) अणु
		पूर्णांक ret = card->probe(card);

		अगर (ret < 0)
			वापस soc_card_ret(card, ret);

		/*
		 * It has "card->probe" and "card->late_probe" callbacks.
		 * So, set "probed" flag here, because it needs to care
		 * about "late_probe".
		 *
		 * see
		 *	snd_soc_bind_card()
		 *	snd_soc_card_late_probe()
		 */
		card->probed = 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_soc_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	अगर (card->late_probe) अणु
		पूर्णांक ret = card->late_probe(card);

		अगर (ret < 0)
			वापस soc_card_ret(card, ret);
	पूर्ण

	/*
	 * It has "card->probe" and "card->late_probe" callbacks,
	 * and "late_probe" callback is called after "probe".
	 * This means, we can set "card->probed" flag afer "late_probe"
	 * क्रम all हालs.
	 *
	 * see
	 *	snd_soc_bind_card()
	 *	snd_soc_card_probe()
	 */
	card->probed = 1;

	वापस 0;
पूर्ण

पूर्णांक snd_soc_card_हटाओ(काष्ठा snd_soc_card *card)
अणु
	पूर्णांक ret = 0;

	अगर (card->probed &&
	    card->हटाओ)
		ret = card->हटाओ(card);

	card->probed = 0;

	वापस soc_card_ret(card, ret);
पूर्ण

पूर्णांक snd_soc_card_set_bias_level(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_dapm_context *dapm,
				क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक ret = 0;

	अगर (card && card->set_bias_level)
		ret = card->set_bias_level(card, dapm, level);

	वापस soc_card_ret(card, ret);
पूर्ण

पूर्णांक snd_soc_card_set_bias_level_post(काष्ठा snd_soc_card *card,
				     काष्ठा snd_soc_dapm_context *dapm,
				     क्रमागत snd_soc_bias_level level)
अणु
	पूर्णांक ret = 0;

	अगर (card && card->set_bias_level_post)
		ret = card->set_bias_level_post(card, dapm, level);

	वापस soc_card_ret(card, ret);
पूर्ण

पूर्णांक snd_soc_card_add_dai_link(काष्ठा snd_soc_card *card,
			      काष्ठा snd_soc_dai_link *dai_link)
अणु
	पूर्णांक ret = 0;

	अगर (card->add_dai_link)
		ret = card->add_dai_link(card, dai_link);

	वापस soc_card_ret(card, ret);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_card_add_dai_link);

व्योम snd_soc_card_हटाओ_dai_link(काष्ठा snd_soc_card *card,
				  काष्ठा snd_soc_dai_link *dai_link)
अणु
	अगर (card->हटाओ_dai_link)
		card->हटाओ_dai_link(card, dai_link);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_card_हटाओ_dai_link);
