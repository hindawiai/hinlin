<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  ALSA पूर्णांकerface to ivtv PCM capture streams
 *
 *  Copyright (C) 2009,2012  Andy Walls <awalls@md.metrocast.net>
 *  Copyright (C) 2009  Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 */

काष्ठा snd_card;

काष्ठा snd_ivtv_card अणु
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा snd_card *sc;
	अचिन्हित पूर्णांक capture_transfer_करोne;
	अचिन्हित पूर्णांक hwptr_करोne_capture;
	काष्ठा snd_pcm_substream *capture_pcm_substream;
	spinlock_t slock;
पूर्ण;

बाह्य पूर्णांक ivtv_alsa_debug;

/*
 * File operations that manipulate the encoder or video or audio subdevices
 * need to be serialized.  Use the same lock we use क्रम v4l2 file ops.
 */
अटल अंतरभूत व्योम snd_ivtv_lock(काष्ठा snd_ivtv_card *itvsc)
अणु
	काष्ठा ivtv *itv = to_ivtv(itvsc->v4l2_dev);
	mutex_lock(&itv->serialize_lock);
पूर्ण

अटल अंतरभूत व्योम snd_ivtv_unlock(काष्ठा snd_ivtv_card *itvsc)
अणु
	काष्ठा ivtv *itv = to_ivtv(itvsc->v4l2_dev);
	mutex_unlock(&itv->serialize_lock);
पूर्ण

#घोषणा IVTV_ALSA_DBGFLG_WARN  (1 << 0)
#घोषणा IVTV_ALSA_DBGFLG_INFO  (1 << 1)

#घोषणा IVTV_ALSA_DEBUG(x, type, fmt, args...) \
	करो अणु \
		अगर ((x) & ivtv_alsa_debug) \
			pr_info("%s-alsa: " type ": " fmt, \
				v4l2_dev->name , ## args); \
	पूर्ण जबतक (0)

#घोषणा IVTV_ALSA_DEBUG_WARN(fmt, args...) \
	IVTV_ALSA_DEBUG(IVTV_ALSA_DBGFLG_WARN, "warning", fmt , ## args)

#घोषणा IVTV_ALSA_DEBUG_INFO(fmt, args...) \
	IVTV_ALSA_DEBUG(IVTV_ALSA_DBGFLG_INFO, "info", fmt , ## args)

#घोषणा IVTV_ALSA_ERR(fmt, args...) \
	pr_err("%s-alsa: " fmt, v4l2_dev->name , ## args)

#घोषणा IVTV_ALSA_WARN(fmt, args...) \
	pr_warn("%s-alsa: " fmt, v4l2_dev->name , ## args)

#घोषणा IVTV_ALSA_INFO(fmt, args...) \
	pr_info("%s-alsa: " fmt, v4l2_dev->name , ## args)
