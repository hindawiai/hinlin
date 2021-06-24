<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_DRM_FRONT_H_
#घोषणा __XEN_DRM_FRONT_H_

#समावेश <linux/scatterlist.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "xen_drm_front_cfg.h"

काष्ठा drm_device;
काष्ठा drm_framebuffer;
काष्ठा drm_gem_object;
काष्ठा drm_pending_vblank_event;

/**
 * DOC: Driver modes of operation in terms of display buffers used
 *
 * Depending on the requirements क्रम the para-भवized environment, namely
 * requirements dictated by the accompanying DRM/(v)GPU drivers running in both
 * host and guest environments, display buffers can be allocated by either
 * frontend driver or backend.
 */

/**
 * DOC: Buffers allocated by the frontend driver
 *
 * In this mode of operation driver allocates buffers from प्रणाली memory.
 *
 * Note! If used with accompanying DRM/(v)GPU drivers this mode of operation
 * may require IOMMU support on the platक्रमm, so accompanying DRM/vGPU
 * hardware can still reach display buffer memory जबतक importing PRIME
 * buffers from the frontend driver.
 */

/**
 * DOC: Buffers allocated by the backend
 *
 * This mode of operation is run-समय configured via guest करोमुख्य configuration
 * through XenStore entries.
 *
 * For प्रणालीs which करो not provide IOMMU support, but having specअगरic
 * requirements क्रम display buffers it is possible to allocate such buffers
 * at backend side and share those with the frontend.
 * For example, अगर host करोमुख्य is 1:1 mapped and has DRM/GPU hardware expecting
 * physically contiguous memory, this allows implementing zero-copying
 * use-हालs.
 *
 * Note, जबतक using this scenario the following should be considered:
 *
 * #. If guest करोमुख्य dies then pages/grants received from the backend
 *    cannot be claimed back
 *
 * #. Misbehaving guest may send too many requests to the
 *    backend exhausting its grant references and memory
 *    (consider this from security POV)
 */

/**
 * DOC: Driver limitations
 *
 * #. Only primary plane without additional properties is supported.
 *
 * #. Only one video mode per connector supported which is configured
 *    via XenStore.
 *
 * #. All CRTCs operate at fixed frequency of 60Hz.
 */

/* समयout in ms to रुको क्रम backend to respond */
#घोषणा XEN_DRM_FRONT_WAIT_BACK_MS	3000

#अगर_अघोषित GRANT_INVALID_REF
/*
 * Note on usage of grant reference 0 as invalid grant reference:
 * grant reference 0 is valid, but never exposed to a PV driver,
 * because of the fact it is alपढ़ोy in use/reserved by the PV console.
 */
#घोषणा GRANT_INVALID_REF	0
#पूर्ण_अगर

काष्ठा xen_drm_front_info अणु
	काष्ठा xenbus_device *xb_dev;
	काष्ठा xen_drm_front_drm_info *drm_info;

	/* to protect data between backend IO code and पूर्णांकerrupt handler */
	spinlock_t io_lock;

	पूर्णांक num_evt_pairs;
	काष्ठा xen_drm_front_evtchnl_pair *evt_pairs;
	काष्ठा xen_drm_front_cfg cfg;

	/* display buffers */
	काष्ठा list_head dbuf_list;
पूर्ण;

काष्ठा xen_drm_front_drm_pipeline अणु
	काष्ठा xen_drm_front_drm_info *drm_info;

	पूर्णांक index;

	काष्ठा drm_simple_display_pipe pipe;

	काष्ठा drm_connector conn;
	/* These are only क्रम connector mode checking */
	पूर्णांक width, height;

	काष्ठा drm_pending_vblank_event *pending_event;

	काष्ठा delayed_work pflip_to_worker;

	bool conn_connected;
पूर्ण;

काष्ठा xen_drm_front_drm_info अणु
	काष्ठा xen_drm_front_info *front_info;
	काष्ठा drm_device *drm_dev;

	काष्ठा xen_drm_front_drm_pipeline pipeline[XEN_DRM_FRONT_MAX_CRTCS];
पूर्ण;

अटल अंतरभूत u64 xen_drm_front_fb_to_cookie(काष्ठा drm_framebuffer *fb)
अणु
	वापस (uपूर्णांकptr_t)fb;
पूर्ण

अटल अंतरभूत u64 xen_drm_front_dbuf_to_cookie(काष्ठा drm_gem_object *gem_obj)
अणु
	वापस (uपूर्णांकptr_t)gem_obj;
पूर्ण

पूर्णांक xen_drm_front_mode_set(काष्ठा xen_drm_front_drm_pipeline *pipeline,
			   u32 x, u32 y, u32 width, u32 height,
			   u32 bpp, u64 fb_cookie);

पूर्णांक xen_drm_front_dbuf_create(काष्ठा xen_drm_front_info *front_info,
			      u64 dbuf_cookie, u32 width, u32 height,
			      u32 bpp, u64 size, u32 offset, काष्ठा page **pages);

पूर्णांक xen_drm_front_fb_attach(काष्ठा xen_drm_front_info *front_info,
			    u64 dbuf_cookie, u64 fb_cookie, u32 width,
			    u32 height, u32 pixel_क्रमmat);

पूर्णांक xen_drm_front_fb_detach(काष्ठा xen_drm_front_info *front_info,
			    u64 fb_cookie);

पूर्णांक xen_drm_front_page_flip(काष्ठा xen_drm_front_info *front_info,
			    पूर्णांक conn_idx, u64 fb_cookie);

व्योम xen_drm_front_on_frame_करोne(काष्ठा xen_drm_front_info *front_info,
				 पूर्णांक conn_idx, u64 fb_cookie);

व्योम xen_drm_front_gem_object_मुक्त(काष्ठा drm_gem_object *obj);

#पूर्ण_अगर /* __XEN_DRM_FRONT_H_ */
