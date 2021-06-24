<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

#अगर_अघोषित __LINUX_GUD_INTERNAL_H
#घोषणा __LINUX_GUD_INTERNAL_H

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/drm/drm_fourcc.h>

#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_simple_kms_helper.h>

काष्ठा gud_device अणु
	काष्ठा drm_device drm;
	काष्ठा drm_simple_display_pipe pipe;
	काष्ठा device *dmadev;
	काष्ठा work_काष्ठा work;
	u32 flags;
	स्थिर काष्ठा drm_क्रमmat_info *xrgb8888_emulation_क्रमmat;

	u16 *properties;
	अचिन्हित पूर्णांक num_properties;

	अचिन्हित पूर्णांक bulk_pipe;
	व्योम *bulk_buf;
	माप_प्रकार bulk_len;

	u8 compression;
	व्योम *lz4_comp_mem;
	व्योम *compress_buf;

	u64 stats_length;
	u64 stats_actual_length;
	अचिन्हित पूर्णांक stats_num_errors;

	काष्ठा mutex ctrl_lock; /* Serialize get/set and status transfers */

	काष्ठा mutex damage_lock; /* Protects the following members: */
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_rect damage;
	bool prev_flush_failed;
पूर्ण;

अटल अंतरभूत काष्ठा gud_device *to_gud_device(काष्ठा drm_device *drm)
अणु
	वापस container_of(drm, काष्ठा gud_device, drm);
पूर्ण

अटल अंतरभूत काष्ठा usb_device *gud_to_usb_device(काष्ठा gud_device *gdrm)
अणु
	वापस पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(gdrm->drm.dev));
पूर्ण

पूर्णांक gud_usb_get(काष्ठा gud_device *gdrm, u8 request, u16 index, व्योम *buf, माप_प्रकार len);
पूर्णांक gud_usb_set(काष्ठा gud_device *gdrm, u8 request, u16 index, व्योम *buf, माप_प्रकार len);
पूर्णांक gud_usb_get_u8(काष्ठा gud_device *gdrm, u8 request, u16 index, u8 *val);
पूर्णांक gud_usb_set_u8(काष्ठा gud_device *gdrm, u8 request, u8 val);

व्योम gud_clear_damage(काष्ठा gud_device *gdrm);
व्योम gud_flush_work(काष्ठा work_काष्ठा *work);
पूर्णांक gud_pipe_check(काष्ठा drm_simple_display_pipe *pipe,
		   काष्ठा drm_plane_state *new_plane_state,
		   काष्ठा drm_crtc_state *new_crtc_state);
व्योम gud_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
		     काष्ठा drm_plane_state *old_state);
पूर्णांक gud_connector_fill_properties(काष्ठा drm_connector_state *connector_state,
				  काष्ठा gud_property_req *properties);
पूर्णांक gud_get_connectors(काष्ठा gud_device *gdrm);

/* Driver पूर्णांकernal fourcc transfer क्रमmats */
#घोषणा GUD_DRM_FORMAT_R1		0x00000122
#घोषणा GUD_DRM_FORMAT_XRGB1111		0x03121722

अटल अंतरभूत u8 gud_from_fourcc(u32 fourcc)
अणु
	चयन (fourcc) अणु
	हाल GUD_DRM_FORMAT_R1:
		वापस GUD_PIXEL_FORMAT_R1;
	हाल GUD_DRM_FORMAT_XRGB1111:
		वापस GUD_PIXEL_FORMAT_XRGB1111;
	हाल DRM_FORMAT_RGB565:
		वापस GUD_PIXEL_FORMAT_RGB565;
	हाल DRM_FORMAT_XRGB8888:
		वापस GUD_PIXEL_FORMAT_XRGB8888;
	हाल DRM_FORMAT_ARGB8888:
		वापस GUD_PIXEL_FORMAT_ARGB8888;
	पूर्ण;

	वापस 0;
पूर्ण

अटल अंतरभूत u32 gud_to_fourcc(u8 क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल GUD_PIXEL_FORMAT_R1:
		वापस GUD_DRM_FORMAT_R1;
	हाल GUD_PIXEL_FORMAT_XRGB1111:
		वापस GUD_DRM_FORMAT_XRGB1111;
	हाल GUD_PIXEL_FORMAT_RGB565:
		वापस DRM_FORMAT_RGB565;
	हाल GUD_PIXEL_FORMAT_XRGB8888:
		वापस DRM_FORMAT_XRGB8888;
	हाल GUD_PIXEL_FORMAT_ARGB8888:
		वापस DRM_FORMAT_ARGB8888;
	पूर्ण;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम gud_from_display_mode(काष्ठा gud_display_mode_req *dst,
					 स्थिर काष्ठा drm_display_mode *src)
अणु
	u32 flags = src->flags & GUD_DISPLAY_MODE_FLAG_USER_MASK;

	अगर (src->type & DRM_MODE_TYPE_PREFERRED)
		flags |= GUD_DISPLAY_MODE_FLAG_PREFERRED;

	dst->घड़ी = cpu_to_le32(src->घड़ी);
	dst->hdisplay = cpu_to_le16(src->hdisplay);
	dst->hsync_start = cpu_to_le16(src->hsync_start);
	dst->hsync_end = cpu_to_le16(src->hsync_end);
	dst->htotal = cpu_to_le16(src->htotal);
	dst->vdisplay = cpu_to_le16(src->vdisplay);
	dst->vsync_start = cpu_to_le16(src->vsync_start);
	dst->vsync_end = cpu_to_le16(src->vsync_end);
	dst->vtotal = cpu_to_le16(src->vtotal);
	dst->flags = cpu_to_le32(flags);
पूर्ण

अटल अंतरभूत व्योम gud_to_display_mode(काष्ठा drm_display_mode *dst,
				       स्थिर काष्ठा gud_display_mode_req *src)
अणु
	u32 flags = le32_to_cpu(src->flags);

	स_रखो(dst, 0, माप(*dst));
	dst->घड़ी = le32_to_cpu(src->घड़ी);
	dst->hdisplay = le16_to_cpu(src->hdisplay);
	dst->hsync_start = le16_to_cpu(src->hsync_start);
	dst->hsync_end = le16_to_cpu(src->hsync_end);
	dst->htotal = le16_to_cpu(src->htotal);
	dst->vdisplay = le16_to_cpu(src->vdisplay);
	dst->vsync_start = le16_to_cpu(src->vsync_start);
	dst->vsync_end = le16_to_cpu(src->vsync_end);
	dst->vtotal = le16_to_cpu(src->vtotal);
	dst->flags = flags & GUD_DISPLAY_MODE_FLAG_USER_MASK;
	dst->type = DRM_MODE_TYPE_DRIVER;
	अगर (flags & GUD_DISPLAY_MODE_FLAG_PREFERRED)
		dst->type |= DRM_MODE_TYPE_PREFERRED;
	drm_mode_set_name(dst);
पूर्ण

#पूर्ण_अगर
