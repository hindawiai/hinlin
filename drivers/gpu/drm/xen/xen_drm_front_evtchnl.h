<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_DRM_FRONT_EVTCHNL_H_
#घोषणा __XEN_DRM_FRONT_EVTCHNL_H_

#समावेश <linux/completion.h>
#समावेश <linux/types.h>

#समावेश <xen/पूर्णांकerface/io/ring.h>
#समावेश <xen/पूर्णांकerface/io/displअगर.h>

/*
 * All operations which are not connector oriented use this ctrl event channel,
 * e.g. fb_attach/destroy which beदीर्घ to a DRM device, not to a CRTC.
 */
#घोषणा GENERIC_OP_EVT_CHNL	0

क्रमागत xen_drm_front_evtchnl_state अणु
	EVTCHNL_STATE_DISCONNECTED,
	EVTCHNL_STATE_CONNECTED,
पूर्ण;

क्रमागत xen_drm_front_evtchnl_type अणु
	EVTCHNL_TYPE_REQ,
	EVTCHNL_TYPE_EVT,
पूर्ण;

काष्ठा xen_drm_front_drm_info;

काष्ठा xen_drm_front_evtchnl अणु
	काष्ठा xen_drm_front_info *front_info;
	पूर्णांक gref;
	पूर्णांक port;
	पूर्णांक irq;
	पूर्णांक index;
	क्रमागत xen_drm_front_evtchnl_state state;
	क्रमागत xen_drm_front_evtchnl_type type;
	/* either response id or incoming event id */
	u16 evt_id;
	/* next request id or next expected event id */
	u16 evt_next_id;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा xen_displअगर_front_ring ring;
			काष्ठा completion completion;
			/* latest response status */
			पूर्णांक resp_status;
			/* serializer क्रम backend IO: request/response */
			काष्ठा mutex req_io_lock;
		पूर्ण req;
		काष्ठा अणु
			काष्ठा xendispl_event_page *page;
		पूर्ण evt;
	पूर्ण u;
पूर्ण;

काष्ठा xen_drm_front_evtchnl_pair अणु
	काष्ठा xen_drm_front_evtchnl req;
	काष्ठा xen_drm_front_evtchnl evt;
पूर्ण;

पूर्णांक xen_drm_front_evtchnl_create_all(काष्ठा xen_drm_front_info *front_info);

पूर्णांक xen_drm_front_evtchnl_publish_all(काष्ठा xen_drm_front_info *front_info);

व्योम xen_drm_front_evtchnl_flush(काष्ठा xen_drm_front_evtchnl *evtchnl);

व्योम xen_drm_front_evtchnl_set_state(काष्ठा xen_drm_front_info *front_info,
				     क्रमागत xen_drm_front_evtchnl_state state);

व्योम xen_drm_front_evtchnl_मुक्त_all(काष्ठा xen_drm_front_info *front_info);

#पूर्ण_अगर /* __XEN_DRM_FRONT_EVTCHNL_H_ */
