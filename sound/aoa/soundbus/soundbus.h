<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * soundbus generic definitions
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */
#अगर_अघोषित __SOUNDBUS_H
#घोषणा __SOUNDBUS_H

#समावेश <linux/of_device.h>
#समावेश <sound/pcm.h>
#समावेश <linux/list.h>


/* When चयनing from master to slave or the other way around,
 * you करोn't want to have the codec chip acting as घड़ी source
 * जबतक the bus still is.
 * More importantly, जबतक चयन from slave to master, you need
 * to turn off the chip's master function first, but then there's
 * no घड़ी क्रम a जबतक and other chips might reset, so we notअगरy
 * their drivers after having चयनed.
 * The स्थिरants here are codec-poपूर्णांक of view, so when we चयन
 * the soundbus to master we tell the codec we're going to चयन
 * and give it CLOCK_SWITCH_PREPARE_SLAVE!
 */
क्रमागत घड़ी_चयन अणु
	CLOCK_SWITCH_PREPARE_SLAVE,
	CLOCK_SWITCH_PREPARE_MASTER,
	CLOCK_SWITCH_SLAVE,
	CLOCK_SWITCH_MASTER,
	CLOCK_SWITCH_NOTIFY,
पूर्ण;

/* inक्रमmation on a transfer the codec can take */
काष्ठा transfer_info अणु
	u64 क्रमmats;		/* SNDRV_PCM_FMTBIT_* */
	अचिन्हित पूर्णांक rates;	/* SNDRV_PCM_RATE_* */
	/* flags */
	u32 transfer_in:1, /* input = 1, output = 0 */
	    must_be_घड़ी_source:1;
	/* क्रम codecs to distinguish among their TIs */
	पूर्णांक tag;
पूर्ण;

काष्ठा codec_info_item अणु
	काष्ठा codec_info *codec;
	व्योम *codec_data;
	काष्ठा soundbus_dev *sdev;
	/* पूर्णांकernal, to be used by the soundbus provider */
	काष्ठा list_head list;
पूर्ण;

/* क्रम prepare, where the codecs need to know
 * what we're going to drive the bus with */
काष्ठा bus_info अणु
	/* see below */
	पूर्णांक sysघड़ी_factor;
	पूर्णांक bus_factor;
पूर्ण;

/* inक्रमmation on the codec itself, plus function poपूर्णांकers */
काष्ठा codec_info अणु
	/* the module this lives in */
	काष्ठा module *owner;

	/* supported transfer possibilities, array terminated by
	 * क्रमmats or rates being 0. */
	काष्ठा transfer_info *transfers;

	/* Master घड़ी speed factor
	 * to be used (master घड़ी speed = sysघड़ी_factor * sampling freq)
	 * Unused अगर the soundbus provider has no such notion.
	 */
	पूर्णांक sysघड़ी_factor;

	/* Bus factor, bus घड़ी speed = bus_factor * sampling freq)
	 * Unused अगर the soundbus provider has no such notion.
	 */
	पूर्णांक bus_factor;

	/* operations */
	/* घड़ी चयनing, see above */
	पूर्णांक (*चयन_घड़ी)(काष्ठा codec_info_item *cii,
			    क्रमागत घड़ी_चयन घड़ी);

	/* called क्रम each transfer_info when the user
	 * खोलोs the pcm device to determine what the
	 * hardware can support at this poपूर्णांक in समय.
	 * That can depend on other user-चयनable controls.
	 * Return 1 अगर usable, 0 अगर not.
	 * out poपूर्णांकs to another instance of a transfer_info
	 * which is initialised to the values in *ti, and
	 * it's क्रमmat and rate values can be modअगरied by
	 * the callback अगर it is necessary to further restrict
	 * the क्रमmats that can be used at the moment, क्रम
	 * example when one codec has multiple logical codec
	 * info काष्ठाs क्रम multiple inमाला_दो.
	 */
	पूर्णांक (*usable)(काष्ठा codec_info_item *cii,
		      काष्ठा transfer_info *ti,
		      काष्ठा transfer_info *out);

	/* called when pcm stream is खोलोed, probably not implemented
	 * most of the समय since it isn't too useful */
	पूर्णांक (*खोलो)(काष्ठा codec_info_item *cii,
		    काष्ठा snd_pcm_substream *substream);

	/* called when the pcm stream is बंदd, at this poपूर्णांक
	 * the user choices can all be unlocked (see below) */
	पूर्णांक (*बंद)(काष्ठा codec_info_item *cii,
		     काष्ठा snd_pcm_substream *substream);

	/* अगर the codec must क्रमbid some user choices because
	 * they are not valid with the substream/transfer info,
	 * it must करो so here. Example: no digital output क्रम
	 * incompatible framerate, say 8KHz, on Onyx.
	 * If the selected stuff in the substream is NOT
	 * compatible, you have to reject this call! */
	पूर्णांक (*prepare)(काष्ठा codec_info_item *cii,
		       काष्ठा bus_info *bi,
		       काष्ठा snd_pcm_substream *substream);

	/* start() is called beक्रमe data is pushed to the codec.
	 * Note that start() must be atomic! */
	पूर्णांक (*start)(काष्ठा codec_info_item *cii,
		     काष्ठा snd_pcm_substream *substream);

	/* stop() is called after data is no दीर्घer pushed to the codec.
	 * Note that stop() must be atomic! */
	पूर्णांक (*stop)(काष्ठा codec_info_item *cii,
		    काष्ठा snd_pcm_substream *substream);

	पूर्णांक (*suspend)(काष्ठा codec_info_item *cii, pm_message_t state);
	पूर्णांक (*resume)(काष्ठा codec_info_item *cii);
पूर्ण;

/* inक्रमmation on a soundbus device */
काष्ठा soundbus_dev अणु
	/* the bus it beदीर्घs to */
	काष्ठा list_head onbuslist;

	/* the of device it represents */
	काष्ठा platक्रमm_device ofdev;

	/* what modules go by */
	अक्षर modalias[32];

	/* These fields must be beक्रमe attach_codec can be called.
	 * They should be set by the owner of the alsa card object
	 * that is needed, and whoever sets them must make sure
	 * that they are unique within that alsa card object. */
	अक्षर *pcmname;
	पूर्णांक pcmid;

	/* this is asचिन्हित by the soundbus provider in attach_codec */
	काष्ठा snd_pcm *pcm;

	/* operations */
	/* attach a codec to this soundbus, give the alsa
	 * card object the PCMs क्रम this soundbus should be in.
	 * The 'data' poपूर्णांकer must be unique, it is used as the
	 * key क्रम detach_codec(). */
	पूर्णांक (*attach_codec)(काष्ठा soundbus_dev *dev, काष्ठा snd_card *card,
			    काष्ठा codec_info *ci, व्योम *data);
	व्योम (*detach_codec)(काष्ठा soundbus_dev *dev, व्योम *data);
	/* TODO: suspend/resume */

	/* निजी क्रम the soundbus provider */
	काष्ठा list_head codec_list;
	u32 have_out:1, have_in:1;
पूर्ण;
#घोषणा to_soundbus_device(d) container_of(d, काष्ठा soundbus_dev, ofdev.dev)
#घोषणा of_to_soundbus_device(d) container_of(d, काष्ठा soundbus_dev, ofdev)

बाह्य पूर्णांक soundbus_add_one(काष्ठा soundbus_dev *dev);
बाह्य व्योम soundbus_हटाओ_one(काष्ठा soundbus_dev *dev);

बाह्य काष्ठा soundbus_dev *soundbus_dev_get(काष्ठा soundbus_dev *dev);
बाह्य व्योम soundbus_dev_put(काष्ठा soundbus_dev *dev);

काष्ठा soundbus_driver अणु
	अक्षर *name;
	काष्ठा module *owner;

	/* we करोn't implement any matching at all */

	पूर्णांक	(*probe)(काष्ठा soundbus_dev* dev);
	पूर्णांक	(*हटाओ)(काष्ठा soundbus_dev* dev);

	पूर्णांक	(*shutकरोwn)(काष्ठा soundbus_dev* dev);

	काष्ठा device_driver driver;
पूर्ण;
#घोषणा to_soundbus_driver(drv) container_of(drv,काष्ठा soundbus_driver, driver)

बाह्य पूर्णांक soundbus_रेजिस्टर_driver(काष्ठा soundbus_driver *drv);
बाह्य व्योम soundbus_unरेजिस्टर_driver(काष्ठा soundbus_driver *drv);

बाह्य काष्ठा attribute *soundbus_dev_attrs[];

#पूर्ण_अगर /* __SOUNDBUS_H */
