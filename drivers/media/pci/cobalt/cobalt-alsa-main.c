<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ALSA पूर्णांकerface to cobalt PCM capture streams
 *
 *  Copyright 2014-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>

#समावेश <media/v4l2-device.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>

#समावेश "cobalt-driver.h"
#समावेश "cobalt-alsa.h"
#समावेश "cobalt-alsa-pcm.h"

अटल व्योम snd_cobalt_card_मुक्त(काष्ठा snd_cobalt_card *cobsc)
अणु
	अगर (cobsc == शून्य)
		वापस;

	cobsc->s->alsa = शून्य;

	kमुक्त(cobsc);
पूर्ण

अटल व्योम snd_cobalt_card_निजी_मुक्त(काष्ठा snd_card *sc)
अणु
	अगर (sc == शून्य)
		वापस;
	snd_cobalt_card_मुक्त(sc->निजी_data);
	sc->निजी_data = शून्य;
	sc->निजी_मुक्त = शून्य;
पूर्ण

अटल पूर्णांक snd_cobalt_card_create(काष्ठा cobalt_stream *s,
				       काष्ठा snd_card *sc,
				       काष्ठा snd_cobalt_card **cobsc)
अणु
	*cobsc = kzalloc(माप(काष्ठा snd_cobalt_card), GFP_KERNEL);
	अगर (*cobsc == शून्य)
		वापस -ENOMEM;

	(*cobsc)->s = s;
	(*cobsc)->sc = sc;

	sc->निजी_data = *cobsc;
	sc->निजी_मुक्त = snd_cobalt_card_निजी_मुक्त;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cobalt_card_set_names(काष्ठा snd_cobalt_card *cobsc)
अणु
	काष्ठा cobalt_stream *s = cobsc->s;
	काष्ठा cobalt *cobalt = s->cobalt;
	काष्ठा snd_card *sc = cobsc->sc;

	/* sc->driver is used by alsa-lib's configurator: simple, unique */
	strscpy(sc->driver, "cobalt", माप(sc->driver));

	/* sc->लघुname is a symlink in /proc/asound: COBALT-M -> cardN */
	snम_लिखो(sc->लघुname,  माप(sc->लघुname), "cobalt-%d-%d",
		 cobalt->instance, s->video_channel);

	/* sc->दीर्घname is पढ़ो from /proc/asound/cards */
	snम_लिखो(sc->दीर्घname, माप(sc->दीर्घname),
		 "Cobalt %d HDMI %d",
		 cobalt->instance, s->video_channel);

	वापस 0;
पूर्ण

पूर्णांक cobalt_alsa_init(काष्ठा cobalt_stream *s)
अणु
	काष्ठा cobalt *cobalt = s->cobalt;
	काष्ठा snd_card *sc = शून्य;
	काष्ठा snd_cobalt_card *cobsc;
	पूर्णांक ret;

	/* Numbrs steps from "Writing an ALSA Driver" by Takashi Iwai */

	/* (1) Check and increment the device index */
	/* This is a no-op क्रम us.  We'll use the cobalt->instance */

	/* (2) Create a card instance */
	ret = snd_card_new(&cobalt->pci_dev->dev, SNDRV_DEFAULT_IDX1,
			   SNDRV_DEFAULT_STR1, THIS_MODULE, 0, &sc);
	अगर (ret) अणु
		cobalt_err("snd_card_new() failed with err %d\n", ret);
		जाओ err_निकास;
	पूर्ण

	/* (3) Create a मुख्य component */
	ret = snd_cobalt_card_create(s, sc, &cobsc);
	अगर (ret) अणु
		cobalt_err("snd_cobalt_card_create() failed with err %d\n",
			   ret);
		जाओ err_निकास_मुक्त;
	पूर्ण

	/* (4) Set the driver ID and name strings */
	snd_cobalt_card_set_names(cobsc);

	ret = snd_cobalt_pcm_create(cobsc);
	अगर (ret) अणु
		cobalt_err("snd_cobalt_pcm_create() failed with err %d\n",
			   ret);
		जाओ err_निकास_मुक्त;
	पूर्ण
	/* FIXME - proc files */

	/* (7) Set the driver data and वापस 0 */
	/* We करो this out of normal order क्रम PCI drivers to aव्योम races */
	s->alsa = cobsc;

	/* (6) Register the card instance */
	ret = snd_card_रेजिस्टर(sc);
	अगर (ret) अणु
		s->alsa = शून्य;
		cobalt_err("snd_card_register() failed with err %d\n", ret);
		जाओ err_निकास_मुक्त;
	पूर्ण

	वापस 0;

err_निकास_मुक्त:
	अगर (sc != शून्य)
		snd_card_मुक्त(sc);
	kमुक्त(cobsc);
err_निकास:
	वापस ret;
पूर्ण

व्योम cobalt_alsa_निकास(काष्ठा cobalt_stream *s)
अणु
	काष्ठा snd_cobalt_card *cobsc = s->alsa;

	अगर (cobsc)
		snd_card_मुक्त(cobsc->sc);
	s->alsa = शून्य;
पूर्ण
