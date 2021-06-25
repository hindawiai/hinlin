<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Apple Onboard Audio definitions
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#अगर_अघोषित __AOA_H
#घोषणा __AOA_H
#समावेश <यंत्र/prom.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/asound.h>
#समावेश <sound/control.h>
#समावेश "aoa-gpio.h"
#समावेश "soundbus/soundbus.h"

#घोषणा MAX_CODEC_NAME_LEN	32

काष्ठा aoa_codec अणु
	अक्षर	name[MAX_CODEC_NAME_LEN];

	काष्ठा module *owner;

	/* called when the fabric wants to init this codec.
	 * Do alsa card manipulations from here. */
	पूर्णांक (*init)(काष्ठा aoa_codec *codec);

	/* called when the fabric is करोne with the codec.
	 * The alsa card will be cleaned up so करोn't bother. */
	व्योम (*निकास)(काष्ठा aoa_codec *codec);

	/* May be शून्य, but can be used by the fabric.
	 * Refcounting is the codec driver's responsibility */
	काष्ठा device_node *node;

	/* asचिन्हित by fabric beक्रमe init() is called, poपूर्णांकs
	 * to the soundbus device. Cannot be शून्य. */
	काष्ठा soundbus_dev *soundbus_dev;

	/* asचिन्हित by the fabric beक्रमe init() is called, poपूर्णांकs
	 * to the fabric's gpio runसमय record क्रम the relevant
	 * device. */
	काष्ठा gpio_runसमय *gpio;

	/* asचिन्हित by the fabric beक्रमe init() is called, contains
	 * a codec specअगरic biपंचांगask of what outमाला_दो and inमाला_दो are
	 * actually connected */
	u32 connected;

	/* data the fabric can associate with this काष्ठाure */
	व्योम *fabric_data;

	/* निजी! */
	काष्ठा list_head list;
	काष्ठा aoa_fabric *fabric;
पूर्ण;

/* वापस 0 on success */
बाह्य पूर्णांक
aoa_codec_रेजिस्टर(काष्ठा aoa_codec *codec);
बाह्य व्योम
aoa_codec_unरेजिस्टर(काष्ठा aoa_codec *codec);

#घोषणा MAX_LAYOUT_NAME_LEN	32

काष्ठा aoa_fabric अणु
	अक्षर	name[MAX_LAYOUT_NAME_LEN];

	काष्ठा module *owner;

	/* once codecs रेजिस्टर, they are passed here after.
	 * They are of course not initialised, since the
	 * fabric is responsible क्रम initialising some fields
	 * in the codec काष्ठाure! */
	पूर्णांक (*found_codec)(काष्ठा aoa_codec *codec);
	/* called क्रम each codec when it is हटाओd,
	 * also in the हाल that aoa_fabric_unरेजिस्टर
	 * is called and all codecs are हटाओd
	 * from this fabric.
	 * Also called अगर found_codec वापसed 0 but
	 * the codec couldn't initialise. */
	व्योम (*हटाओ_codec)(काष्ठा aoa_codec *codec);
	/* If found_codec वापसed 0, and the codec
	 * could be initialised, this is called. */
	व्योम (*attached_codec)(काष्ठा aoa_codec *codec);
पूर्ण;

/* वापस 0 on success, -EEXIST अगर another fabric is
 * रेजिस्टरed, -EALREADY अगर the same fabric is रेजिस्टरed.
 * Passing शून्य can be used to test क्रम the presence
 * of another fabric, अगर -EALREADY is वापसed there is
 * no other fabric present.
 * In the हाल that the function वापसs -EALREADY
 * and the fabric passed is not शून्य, all codecs
 * that are not asचिन्हित yet are passed to the fabric
 * again क्रम reconsideration. */
बाह्य पूर्णांक
aoa_fabric_रेजिस्टर(काष्ठा aoa_fabric *fabric, काष्ठा device *dev);

/* it is vital to call this when the fabric निकासs!
 * When calling, the हटाओ_codec will be called
 * क्रम all codecs, unless it is शून्य. */
बाह्य व्योम
aoa_fabric_unरेजिस्टर(काष्ठा aoa_fabric *fabric);

/* अगर क्रम some reason you want to get rid of a codec
 * beक्रमe the fabric is हटाओd, use this.
 * Note that हटाओ_codec is called क्रम it! */
बाह्य व्योम
aoa_fabric_unlink_codec(काष्ठा aoa_codec *codec);

/* alsa help methods */
काष्ठा aoa_card अणु
	काष्ठा snd_card *alsa_card;
पूर्ण;
        
बाह्य पूर्णांक aoa_snd_device_new(क्रमागत snd_device_type type,
	व्योम *device_data, स्थिर काष्ठा snd_device_ops *ops);
बाह्य काष्ठा snd_card *aoa_get_card(व्योम);
बाह्य पूर्णांक aoa_snd_ctl_add(काष्ठा snd_kcontrol* control);

/* GPIO stuff */
बाह्य काष्ठा gpio_methods *pmf_gpio_methods;
बाह्य काष्ठा gpio_methods *ftr_gpio_methods;
/* बाह्य काष्ठा gpio_methods *map_gpio_methods; */

#पूर्ण_अगर /* __AOA_H */
