<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ALSA पूर्णांकerface to cx18 PCM capture streams
 *
 *  Copyright (C) 2009  Andy Walls <awalls@md.metrocast.net>
 *  Copyright (C) 2009  Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 *
 *  Portions of this work were sponsored by ONELAN Limited.
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

#समावेश "cx18-driver.h"
#समावेश "cx18-version.h"
#समावेश "cx18-alsa.h"
#समावेश "cx18-alsa-pcm.h"

पूर्णांक cx18_alsa_debug;

#घोषणा CX18_DEBUG_ALSA_INFO(fmt, arg...) \
	करो अणु \
		अगर (cx18_alsa_debug & 2) \
			prपूर्णांकk(KERN_INFO "%s: " fmt, "cx18-alsa", ## arg); \
	पूर्ण जबतक (0);

module_param_named(debug, cx18_alsa_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		 "Debug level (bitmask). Default: 0\n"
		 "\t\t\t  1/0x0001: warning\n"
		 "\t\t\t  2/0x0002: info\n");

MODULE_AUTHOR("Andy Walls");
MODULE_DESCRIPTION("CX23418 ALSA Interface");
MODULE_LICENSE("GPL");

MODULE_VERSION(CX18_VERSION);

अटल अंतरभूत
काष्ठा snd_cx18_card *to_snd_cx18_card(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस to_cx18(v4l2_dev)->alsa;
पूर्ण

अटल अंतरभूत
काष्ठा snd_cx18_card *p_to_snd_cx18_card(काष्ठा v4l2_device **v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा snd_cx18_card, v4l2_dev);
पूर्ण

अटल व्योम snd_cx18_card_मुक्त(काष्ठा snd_cx18_card *cxsc)
अणु
	अगर (cxsc == शून्य)
		वापस;

	अगर (cxsc->v4l2_dev != शून्य)
		to_cx18(cxsc->v4l2_dev)->alsa = शून्य;

	/* FIXME - take any other stopping actions needed */

	kमुक्त(cxsc);
पूर्ण

अटल व्योम snd_cx18_card_निजी_मुक्त(काष्ठा snd_card *sc)
अणु
	अगर (sc == शून्य)
		वापस;
	snd_cx18_card_मुक्त(sc->निजी_data);
	sc->निजी_data = शून्य;
	sc->निजी_मुक्त = शून्य;
पूर्ण

अटल पूर्णांक snd_cx18_card_create(काष्ठा v4l2_device *v4l2_dev,
				       काष्ठा snd_card *sc,
				       काष्ठा snd_cx18_card **cxsc)
अणु
	*cxsc = kzalloc(माप(काष्ठा snd_cx18_card), GFP_KERNEL);
	अगर (*cxsc == शून्य)
		वापस -ENOMEM;

	(*cxsc)->v4l2_dev = v4l2_dev;
	(*cxsc)->sc = sc;

	sc->निजी_data = *cxsc;
	sc->निजी_मुक्त = snd_cx18_card_निजी_मुक्त;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cx18_card_set_names(काष्ठा snd_cx18_card *cxsc)
अणु
	काष्ठा cx18 *cx = to_cx18(cxsc->v4l2_dev);
	काष्ठा snd_card *sc = cxsc->sc;

	/* sc->driver is used by alsa-lib's configurator: simple, unique */
	strscpy(sc->driver, "CX23418", माप(sc->driver));

	/* sc->लघुname is a symlink in /proc/asound: CX18-M -> cardN */
	snम_लिखो(sc->लघुname,  माप(sc->लघुname), "CX18-%d",
		 cx->instance);

	/* sc->दीर्घname is पढ़ो from /proc/asound/cards */
	snम_लिखो(sc->दीर्घname, माप(sc->दीर्घname),
		 "CX23418 #%d %s TV/FM Radio/Line-In Capture",
		 cx->instance, cx->card_name);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cx18_init(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा cx18 *cx = to_cx18(v4l2_dev);
	काष्ठा snd_card *sc = शून्य;
	काष्ठा snd_cx18_card *cxsc;
	पूर्णांक ret;

	/* Numbrs steps from "Writing an ALSA Driver" by Takashi Iwai */

	/* (1) Check and increment the device index */
	/* This is a no-op क्रम us.  We'll use the cx->instance */

	/* (2) Create a card instance */
	ret = snd_card_new(&cx->pci_dev->dev,
			   SNDRV_DEFAULT_IDX1, /* use first available id */
			   SNDRV_DEFAULT_STR1, /* xid from end of लघुname*/
			   THIS_MODULE, 0, &sc);
	अगर (ret) अणु
		CX18_ALSA_ERR("%s: snd_card_new() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास;
	पूर्ण

	/* (3) Create a मुख्य component */
	ret = snd_cx18_card_create(v4l2_dev, sc, &cxsc);
	अगर (ret) अणु
		CX18_ALSA_ERR("%s: snd_cx18_card_create() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास_मुक्त;
	पूर्ण

	/* (4) Set the driver ID and name strings */
	snd_cx18_card_set_names(cxsc);


	ret = snd_cx18_pcm_create(cxsc);
	अगर (ret) अणु
		CX18_ALSA_ERR("%s: snd_cx18_pcm_create() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास_मुक्त;
	पूर्ण
	/* FIXME - proc files */

	/* (7) Set the driver data and वापस 0 */
	/* We करो this out of normal order क्रम PCI drivers to aव्योम races */
	cx->alsa = cxsc;

	/* (6) Register the card instance */
	ret = snd_card_रेजिस्टर(sc);
	अगर (ret) अणु
		cx->alsa = शून्य;
		CX18_ALSA_ERR("%s: snd_card_register() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास_मुक्त;
	पूर्ण

	वापस 0;

err_निकास_मुक्त:
	अगर (sc != शून्य)
		snd_card_मुक्त(sc);
	kमुक्त(cxsc);
err_निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक cx18_alsa_load(काष्ठा cx18 *cx)
अणु
	काष्ठा v4l2_device *v4l2_dev = &cx->v4l2_dev;
	काष्ठा cx18_stream *s;

	अगर (v4l2_dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR "cx18-alsa: %s: struct v4l2_device * is NULL\n",
		       __func__);
		वापस 0;
	पूर्ण

	cx = to_cx18(v4l2_dev);
	अगर (cx == शून्य) अणु
		prपूर्णांकk(KERN_ERR "cx18-alsa cx is NULL\n");
		वापस 0;
	पूर्ण

	s = &cx->streams[CX18_ENC_STREAM_TYPE_PCM];
	अगर (s->video_dev.v4l2_dev == शून्य) अणु
		CX18_DEBUG_ALSA_INFO("%s: PCM stream for card is disabled - skipping\n",
				     __func__);
		वापस 0;
	पूर्ण

	अगर (cx->alsa != शून्य) अणु
		CX18_ALSA_ERR("%s: struct snd_cx18_card * already exists\n",
			      __func__);
		वापस 0;
	पूर्ण

	अगर (snd_cx18_init(v4l2_dev)) अणु
		CX18_ALSA_ERR("%s: failed to create struct snd_cx18_card\n",
			      __func__);
	पूर्ण अन्यथा अणु
		CX18_DEBUG_ALSA_INFO("%s: created cx18 ALSA interface instance\n",
				     __func__);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init cx18_alsa_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "cx18-alsa: module loading...\n");
	cx18_ext_init = &cx18_alsa_load;
	वापस 0;
पूर्ण

अटल व्योम __निकास snd_cx18_निकास(काष्ठा snd_cx18_card *cxsc)
अणु
	काष्ठा cx18 *cx = to_cx18(cxsc->v4l2_dev);

	/* FIXME - poपूर्णांकer checks & shutकरोwn cxsc */

	snd_card_मुक्त(cxsc->sc);
	cx->alsa = शून्य;
पूर्ण

अटल पूर्णांक __निकास cx18_alsa_निकास_callback(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	काष्ठा snd_cx18_card *cxsc;

	अगर (v4l2_dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR "cx18-alsa: %s: struct v4l2_device * is NULL\n",
		       __func__);
		वापस 0;
	पूर्ण

	cxsc = to_snd_cx18_card(v4l2_dev);
	अगर (cxsc == शून्य) अणु
		CX18_ALSA_WARN("%s: struct snd_cx18_card * is NULL\n",
			       __func__);
		वापस 0;
	पूर्ण

	snd_cx18_निकास(cxsc);
	वापस 0;
पूर्ण

अटल व्योम __निकास cx18_alsa_निकास(व्योम)
अणु
	काष्ठा device_driver *drv;
	पूर्णांक ret;

	prपूर्णांकk(KERN_INFO "cx18-alsa: module unloading...\n");

	drv = driver_find("cx18", &pci_bus_type);
	ret = driver_क्रम_each_device(drv, शून्य, शून्य, cx18_alsa_निकास_callback);
	(व्योम)ret;	/* suppress compiler warning */

	cx18_ext_init = शून्य;
	prपूर्णांकk(KERN_INFO "cx18-alsa: module unload complete\n");
पूर्ण

module_init(cx18_alsa_init);
module_निकास(cx18_alsa_निकास);
