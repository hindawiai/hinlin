<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  ALSA पूर्णांकerface to cx18 PCM capture streams
 *
 *  Copyright (C) 2009  Andy Walls <awalls@md.metrocast.net>
 */

काष्ठा snd_card;

काष्ठा snd_cx18_card अणु
	काष्ठा v4l2_device *v4l2_dev;
	काष्ठा snd_card *sc;
	अचिन्हित पूर्णांक capture_transfer_करोne;
	अचिन्हित पूर्णांक hwptr_करोne_capture;
	काष्ठा snd_pcm_substream *capture_pcm_substream;
	spinlock_t slock;
पूर्ण;

बाह्य पूर्णांक cx18_alsa_debug;

/*
 * File operations that manipulate the encoder or video or audio subdevices
 * need to be serialized.  Use the same lock we use क्रम v4l2 file ops.
 */
अटल अंतरभूत व्योम snd_cx18_lock(काष्ठा snd_cx18_card *cxsc)
अणु
	काष्ठा cx18 *cx = to_cx18(cxsc->v4l2_dev);
	mutex_lock(&cx->serialize_lock);
पूर्ण

अटल अंतरभूत व्योम snd_cx18_unlock(काष्ठा snd_cx18_card *cxsc)
अणु
	काष्ठा cx18 *cx = to_cx18(cxsc->v4l2_dev);
	mutex_unlock(&cx->serialize_lock);
पूर्ण

#घोषणा CX18_ALSA_DBGFLG_WARN  (1 << 0)
#घोषणा CX18_ALSA_DBGFLG_INFO  (1 << 1)

#घोषणा CX18_ALSA_DEBUG(x, type, fmt, args...) \
	करो अणु \
		अगर ((x) & cx18_alsa_debug) \
			prपूर्णांकk(KERN_INFO "%s-alsa: " type ": " fmt, \
				v4l2_dev->name , ## args); \
	पूर्ण जबतक (0)

#घोषणा CX18_ALSA_DEBUG_WARN(fmt, args...) \
	CX18_ALSA_DEBUG(CX18_ALSA_DBGFLG_WARN, "warning", fmt , ## args)

#घोषणा CX18_ALSA_DEBUG_INFO(fmt, args...) \
	CX18_ALSA_DEBUG(CX18_ALSA_DBGFLG_INFO, "info", fmt , ## args)

#घोषणा CX18_ALSA_ERR(fmt, args...) \
	prपूर्णांकk(KERN_ERR "%s-alsa: " fmt, v4l2_dev->name , ## args)

#घोषणा CX18_ALSA_WARN(fmt, args...) \
	prपूर्णांकk(KERN_WARNING "%s-alsa: " fmt, v4l2_dev->name , ## args)

#घोषणा CX18_ALSA_INFO(fmt, args...) \
	prपूर्णांकk(KERN_INFO "%s-alsa: " fmt, v4l2_dev->name , ## args)
