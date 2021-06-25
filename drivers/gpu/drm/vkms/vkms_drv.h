<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

#अगर_अघोषित _VKMS_DRV_H_
#घोषणा _VKMS_DRV_H_

#समावेश <linux/hrसमयr.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_ग_लिखोback.h>

#घोषणा XRES_MIN    20
#घोषणा YRES_MIN    20

#घोषणा XRES_DEF  1024
#घोषणा YRES_DEF   768

#घोषणा XRES_MAX  8192
#घोषणा YRES_MAX  8192

काष्ठा vkms_composer अणु
	काष्ठा drm_framebuffer fb;
	काष्ठा drm_rect src, dst;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक pitch;
	अचिन्हित पूर्णांक cpp;
पूर्ण;

/**
 * vkms_plane_state - Driver specअगरic plane state
 * @base: base plane state
 * @composer: data required क्रम composing computation
 */
काष्ठा vkms_plane_state अणु
	काष्ठा drm_plane_state base;
	काष्ठा vkms_composer *composer;
पूर्ण;

/**
 * vkms_crtc_state - Driver specअगरic CRTC state
 * @base: base CRTC state
 * @composer_work: work काष्ठा to compose and add CRC entries
 * @n_frame_start: start frame number क्रम computed CRC
 * @n_frame_end: end frame number क्रम computed CRC
 */
काष्ठा vkms_crtc_state अणु
	काष्ठा drm_crtc_state base;
	काष्ठा work_काष्ठा composer_work;

	पूर्णांक num_active_planes;
	/* stack of active planes क्रम crc computation, should be in z order */
	काष्ठा vkms_plane_state **active_planes;
	व्योम *active_ग_लिखोback;

	/* below four are रक्षित by vkms_output.composer_lock */
	bool crc_pending;
	bool wb_pending;
	u64 frame_start;
	u64 frame_end;
पूर्ण;

काष्ठा vkms_output अणु
	काष्ठा drm_crtc crtc;
	काष्ठा drm_encoder encoder;
	काष्ठा drm_connector connector;
	काष्ठा drm_ग_लिखोback_connector wb_connector;
	काष्ठा hrसमयr vblank_hrसमयr;
	kसमय_प्रकार period_ns;
	काष्ठा drm_pending_vblank_event *event;
	/* ordered wq क्रम composer_work */
	काष्ठा workqueue_काष्ठा *composer_workq;
	/* protects concurrent access to composer */
	spinlock_t lock;

	/* रक्षित by @lock */
	bool composer_enabled;
	काष्ठा vkms_crtc_state *composer_state;

	spinlock_t composer_lock;
पूर्ण;

काष्ठा vkms_device;

काष्ठा vkms_config अणु
	bool ग_लिखोback;
	bool cursor;
	/* only set when instantiated */
	काष्ठा vkms_device *dev;
पूर्ण;

काष्ठा vkms_device अणु
	काष्ठा drm_device drm;
	काष्ठा platक्रमm_device *platक्रमm;
	काष्ठा vkms_output output;
	स्थिर काष्ठा vkms_config *config;
पूर्ण;

#घोषणा drm_crtc_to_vkms_output(target) \
	container_of(target, काष्ठा vkms_output, crtc)

#घोषणा drm_device_to_vkms_device(target) \
	container_of(target, काष्ठा vkms_device, drm)

#घोषणा to_vkms_crtc_state(target)\
	container_of(target, काष्ठा vkms_crtc_state, base)

#घोषणा to_vkms_plane_state(target)\
	container_of(target, काष्ठा vkms_plane_state, base)

/* CRTC */
पूर्णांक vkms_crtc_init(काष्ठा drm_device *dev, काष्ठा drm_crtc *crtc,
		   काष्ठा drm_plane *primary, काष्ठा drm_plane *cursor);

पूर्णांक vkms_output_init(काष्ठा vkms_device *vkmsdev, पूर्णांक index);

काष्ठा drm_plane *vkms_plane_init(काष्ठा vkms_device *vkmsdev,
				  क्रमागत drm_plane_type type, पूर्णांक index);

/* CRC Support */
स्थिर अक्षर *स्थिर *vkms_get_crc_sources(काष्ठा drm_crtc *crtc,
					माप_प्रकार *count);
पूर्णांक vkms_set_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *src_name);
पूर्णांक vkms_verअगरy_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *source_name,
			   माप_प्रकार *values_cnt);

/* Composer Support */
व्योम vkms_composer_worker(काष्ठा work_काष्ठा *work);
व्योम vkms_set_composer(काष्ठा vkms_output *out, bool enabled);

/* Writeback */
पूर्णांक vkms_enable_ग_लिखोback_connector(काष्ठा vkms_device *vkmsdev);

#पूर्ण_अगर /* _VKMS_DRV_H_ */
