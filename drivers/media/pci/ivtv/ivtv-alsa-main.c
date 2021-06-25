<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ALSA पूर्णांकerface to ivtv PCM capture streams
 *
 *  Copyright (C) 2009,2012  Andy Walls <awalls@md.metrocast.net>
 *  Copyright (C) 2009  Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 *
 *  Portions of this work were sponsored by ONELAN Limited क्रम the cx18 driver
 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-version.h"
#समावेश "ivtv-alsa.h"
#समावेश "ivtv-alsa-pcm.h"

#समावेश <sound/core.h>
#समावेश <sound/initval.h>

पूर्णांक ivtv_alsa_debug;
अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;

#घोषणा IVTV_DEBUG_ALSA_INFO(__fmt, __arg...) \
	करो अणु \
		अगर (ivtv_alsa_debug & 2) \
			prपूर्णांकk(KERN_INFO pr_fmt("%s: alsa:" __fmt),	\
			       __func__, ##__arg);			\
	पूर्ण जबतक (0)

module_param_named(debug, ivtv_alsa_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		 "Debug level (bitmask). Default: 0\n"
		 "\t\t\t  1/0x0001: warning\n"
		 "\t\t\t  2/0x0002: info\n");

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index,
		 "Index value for IVTV ALSA capture interface(s).\n");

MODULE_AUTHOR("Andy Walls");
MODULE_DESCRIPTION("CX23415/CX23416 ALSA Interface");
MODULE_LICENSE("GPL");

MODULE_VERSION(IVTV_VERSION);

अटल अंतरभूत
काष्ठा snd_ivtv_card *to_snd_ivtv_card(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस to_ivtv(v4l2_dev)->alsa;
पूर्ण

अटल अंतरभूत
काष्ठा snd_ivtv_card *p_to_snd_ivtv_card(काष्ठा v4l2_device **v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा snd_ivtv_card, v4l2_dev);
पूर्ण

अटल व्योम snd_ivtv_card_मुक्त(काष्ठा snd_ivtv_card *itvsc)
अणु
	अगर (itvsc == शून्य)
		वापस;

	अगर (itvsc->v4l2_dev != शून्य)
		to_ivtv(itvsc->v4l2_dev)->alsa = शून्य;

	/* FIXME - take any other stopping actions needed */

	kमुक्त(itvsc);
पूर्ण

अटल व्योम snd_ivtv_card_निजी_मुक्त(काष्ठा snd_card *sc)
अणु
	अगर (sc == शून्य)
		वापस;
	snd_ivtv_card_मुक्त(sc->निजी_data);
	sc->निजी_data = शून्य;
	sc->निजी_मुक्त = शून्य;
पूर्ण

अटल पूर्णांक snd_ivtv_card_create(काष्ठा v4l2_device *v4l2_dev,
				       काष्ठा snd_card *sc,
				       काष्ठा snd_ivtv_card **itvsc)
अणु
	*itvsc = kzalloc(माप(काष्ठा snd_ivtv_card), GFP_KERNEL);
	अगर (*itvsc == शून्य)
		वापस -ENOMEM;

	(*itvsc)->v4l2_dev = v4l2_dev;
	(*itvsc)->sc = sc;

	sc->निजी_data = *itvsc;
	sc->निजी_मुक्त = snd_ivtv_card_निजी_मुक्त;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ivtv_card_set_names(काष्ठा snd_ivtv_card *itvsc)
अणु
	काष्ठा ivtv *itv = to_ivtv(itvsc->v4l2_dev);
	काष्ठा snd_card *sc = itvsc->sc;

	/* sc->driver is used by alsa-lib's configurator: simple, unique */
	strscpy(sc->driver, "CX2341[56]", माप(sc->driver));

	/* sc->लघुname is a symlink in /proc/asound: IVTV-M -> cardN */
	snम_लिखो(sc->लघुname,  माप(sc->लघुname), "IVTV-%d",
		 itv->instance);

	/* sc->दीर्घname is पढ़ो from /proc/asound/cards */
	snम_लिखो(sc->दीर्घname, माप(sc->दीर्घname),
		 "CX2341[56] #%d %s TV/FM Radio/Line-In Capture",
		 itv->instance, itv->card_name);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ivtv_init(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा ivtv *itv = to_ivtv(v4l2_dev);
	काष्ठा snd_card *sc = शून्य;
	काष्ठा snd_ivtv_card *itvsc;
	पूर्णांक ret, idx;

	/* Numbrs steps from "Writing an ALSA Driver" by Takashi Iwai */

	/* (1) Check and increment the device index */
	/* This is a no-op क्रम us.  We'll use the itv->instance */

	/* (2) Create a card instance */
	/* use first available id अगर not specअगरied otherwise*/
	idx = index[itv->instance] == -1 ? SNDRV_DEFAULT_IDX1 : index[itv->instance];
	ret = snd_card_new(&itv->pdev->dev,
			   idx,
			   SNDRV_DEFAULT_STR1, /* xid from end of लघुname*/
			   THIS_MODULE, 0, &sc);
	अगर (ret) अणु
		IVTV_ALSA_ERR("%s: snd_card_new() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास;
	पूर्ण

	/* (3) Create a मुख्य component */
	ret = snd_ivtv_card_create(v4l2_dev, sc, &itvsc);
	अगर (ret) अणु
		IVTV_ALSA_ERR("%s: snd_ivtv_card_create() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास_मुक्त;
	पूर्ण

	/* (4) Set the driver ID and name strings */
	snd_ivtv_card_set_names(itvsc);

	/* (5) Create other components: PCM, & proc files */
	ret = snd_ivtv_pcm_create(itvsc);
	अगर (ret) अणु
		IVTV_ALSA_ERR("%s: snd_ivtv_pcm_create() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास_मुक्त;
	पूर्ण
	/* FIXME - proc files */

	/* (7) Set the driver data and वापस 0 */
	/* We करो this out of normal order क्रम PCI drivers to aव्योम races */
	itv->alsa = itvsc;

	/* (6) Register the card instance */
	ret = snd_card_रेजिस्टर(sc);
	अगर (ret) अणु
		itv->alsa = शून्य;
		IVTV_ALSA_ERR("%s: snd_card_register() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास_मुक्त;
	पूर्ण

	IVTV_ALSA_INFO("%s: Instance %d registered as ALSA card %d\n",
			 __func__, itv->instance, sc->number);

	वापस 0;

err_निकास_मुक्त:
	अगर (sc != शून्य)
		snd_card_मुक्त(sc);
	kमुक्त(itvsc);
err_निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक ivtv_alsa_load(काष्ठा ivtv *itv)
अणु
	काष्ठा v4l2_device *v4l2_dev = &itv->v4l2_dev;
	काष्ठा ivtv_stream *s;

	अगर (v4l2_dev == शून्य) अणु
		pr_err("ivtv-alsa: %s: struct v4l2_device * is NULL\n",
		       __func__);
		वापस 0;
	पूर्ण

	itv = to_ivtv(v4l2_dev);
	अगर (itv == शून्य) अणु
		pr_err("ivtv-alsa itv is NULL\n");
		वापस 0;
	पूर्ण

	s = &itv->streams[IVTV_ENC_STREAM_TYPE_PCM];
	अगर (s->vdev.v4l2_dev == शून्य) अणु
		IVTV_DEBUG_ALSA_INFO("PCM stream for card is disabled - skipping\n");
		वापस 0;
	पूर्ण

	अगर (itv->alsa != शून्य) अणु
		IVTV_ALSA_ERR("%s: struct snd_ivtv_card * already exists\n",
			      __func__);
		वापस 0;
	पूर्ण

	अगर (snd_ivtv_init(v4l2_dev)) अणु
		IVTV_ALSA_ERR("%s: failed to create struct snd_ivtv_card\n",
			      __func__);
	पूर्ण अन्यथा अणु
		IVTV_DEBUG_ALSA_INFO("created ivtv ALSA interface instance\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init ivtv_alsa_init(व्योम)
अणु
	pr_info("ivtv-alsa: module loading...\n");
	ivtv_ext_init = &ivtv_alsa_load;
	वापस 0;
पूर्ण

अटल व्योम __निकास snd_ivtv_निकास(काष्ठा snd_ivtv_card *itvsc)
अणु
	काष्ठा ivtv *itv = to_ivtv(itvsc->v4l2_dev);

	/* FIXME - poपूर्णांकer checks & shutकरोwn itvsc */

	snd_card_मुक्त(itvsc->sc);
	itv->alsa = शून्य;
पूर्ण

अटल पूर्णांक __निकास ivtv_alsa_निकास_callback(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	काष्ठा snd_ivtv_card *itvsc;

	अगर (v4l2_dev == शून्य) अणु
		pr_err("ivtv-alsa: %s: struct v4l2_device * is NULL\n",
		       __func__);
		वापस 0;
	पूर्ण

	itvsc = to_snd_ivtv_card(v4l2_dev);
	अगर (itvsc == शून्य) अणु
		IVTV_ALSA_WARN("%s: struct snd_ivtv_card * is NULL\n",
			       __func__);
		वापस 0;
	पूर्ण

	snd_ivtv_निकास(itvsc);
	वापस 0;
पूर्ण

अटल व्योम __निकास ivtv_alsa_निकास(व्योम)
अणु
	काष्ठा device_driver *drv;
	पूर्णांक ret;

	pr_info("ivtv-alsa: module unloading...\n");

	drv = driver_find("ivtv", &pci_bus_type);
	ret = driver_क्रम_each_device(drv, शून्य, शून्य, ivtv_alsa_निकास_callback);
	(व्योम)ret;	/* suppress compiler warning */

	ivtv_ext_init = शून्य;
	pr_info("ivtv-alsa: module unload complete\n");
पूर्ण

module_init(ivtv_alsa_init);
module_निकास(ivtv_alsa_निकास);
