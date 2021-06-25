<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Apple Onboard Audio Alsa helpers
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */
#समावेश <linux/module.h>
#समावेश "alsa.h"

अटल पूर्णांक index = -1;
module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "index for AOA sound card.");

अटल काष्ठा aoa_card *aoa_card;

पूर्णांक aoa_alsa_init(अक्षर *name, काष्ठा module *mod, काष्ठा device *dev)
अणु
	काष्ठा snd_card *alsa_card;
	पूर्णांक err;

	अगर (aoa_card)
		/* cannot be EEXIST due to usage in aoa_fabric_रेजिस्टर */
		वापस -EBUSY;

	err = snd_card_new(dev, index, name, mod, माप(काष्ठा aoa_card),
			   &alsa_card);
	अगर (err < 0)
		वापस err;
	aoa_card = alsa_card->निजी_data;
	aoa_card->alsa_card = alsa_card;
	strscpy(alsa_card->driver, "AppleOnbdAudio", माप(alsa_card->driver));
	strscpy(alsa_card->लघुname, name, माप(alsa_card->लघुname));
	strscpy(alsa_card->दीर्घname, name, माप(alsa_card->दीर्घname));
	strscpy(alsa_card->mixername, name, माप(alsa_card->mixername));
	err = snd_card_रेजिस्टर(aoa_card->alsa_card);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "snd-aoa: couldn't register alsa card\n");
		snd_card_मुक्त(aoa_card->alsa_card);
		aoa_card = शून्य;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा snd_card *aoa_get_card(व्योम)
अणु
	अगर (aoa_card)
		वापस aoa_card->alsa_card;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(aoa_get_card);

व्योम aoa_alsa_cleanup(व्योम)
अणु
	अगर (aoa_card) अणु
		snd_card_मुक्त(aoa_card->alsa_card);
		aoa_card = शून्य;
	पूर्ण
पूर्ण

पूर्णांक aoa_snd_device_new(क्रमागत snd_device_type type,
		       व्योम *device_data, स्थिर काष्ठा snd_device_ops *ops)
अणु
	काष्ठा snd_card *card = aoa_get_card();
	पूर्णांक err;

	अगर (!card) वापस -ENOMEM;

	err = snd_device_new(card, type, device_data, ops);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "snd-aoa: failed to create snd device (%d)\n", err);
		वापस err;
	पूर्ण
	err = snd_device_रेजिस्टर(card, device_data);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "snd-aoa: failed to register "
				"snd device (%d)\n", err);
		prपूर्णांकk(KERN_ERR "snd-aoa: have you forgotten the "
				"dev_register callback?\n");
		snd_device_मुक्त(card, device_data);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(aoa_snd_device_new);

पूर्णांक aoa_snd_ctl_add(काष्ठा snd_kcontrol* control)
अणु
	पूर्णांक err;

	अगर (!aoa_card) वापस -ENODEV;

	err = snd_ctl_add(aoa_card->alsa_card, control);
	अगर (err)
		prपूर्णांकk(KERN_ERR "snd-aoa: failed to add alsa control (%d)\n",
		       err);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(aoa_snd_ctl_add);
