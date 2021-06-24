<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _DRM_AGPSUPPORT_H_
#घोषणा _DRM_AGPSUPPORT_H_

#समावेश <linux/agp_backend.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <uapi/drm/drm.h>

काष्ठा drm_device;
काष्ठा drm_file;

काष्ठा drm_agp_head अणु
	काष्ठा agp_kern_info agp_info;
	काष्ठा list_head memory;
	अचिन्हित दीर्घ mode;
	काष्ठा agp_bridge_data *bridge;
	पूर्णांक enabled;
	पूर्णांक acquired;
	अचिन्हित दीर्घ base;
	पूर्णांक agp_mtrr;
	पूर्णांक cant_use_aperture;
	अचिन्हित दीर्घ page_mask;
पूर्ण;

#अगर IS_ENABLED(CONFIG_AGP)

काष्ठा drm_agp_head *drm_agp_init(काष्ठा drm_device *dev);
व्योम drm_legacy_agp_clear(काष्ठा drm_device *dev);
पूर्णांक drm_agp_acquire(काष्ठा drm_device *dev);
पूर्णांक drm_agp_acquire_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv);
पूर्णांक drm_agp_release(काष्ठा drm_device *dev);
पूर्णांक drm_agp_release_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv);
पूर्णांक drm_agp_enable(काष्ठा drm_device *dev, काष्ठा drm_agp_mode mode);
पूर्णांक drm_agp_enable_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
पूर्णांक drm_agp_info(काष्ठा drm_device *dev, काष्ठा drm_agp_info *info);
पूर्णांक drm_agp_info_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv);
पूर्णांक drm_agp_alloc(काष्ठा drm_device *dev, काष्ठा drm_agp_buffer *request);
पूर्णांक drm_agp_alloc_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
पूर्णांक drm_agp_मुक्त(काष्ठा drm_device *dev, काष्ठा drm_agp_buffer *request);
पूर्णांक drm_agp_मुक्त_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv);
पूर्णांक drm_agp_unbind(काष्ठा drm_device *dev, काष्ठा drm_agp_binding *request);
पूर्णांक drm_agp_unbind_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
पूर्णांक drm_agp_bind(काष्ठा drm_device *dev, काष्ठा drm_agp_binding *request);
पूर्णांक drm_agp_bind_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv);

#अन्यथा /* CONFIG_AGP */

अटल अंतरभूत काष्ठा drm_agp_head *drm_agp_init(काष्ठा drm_device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम drm_legacy_agp_clear(काष्ठा drm_device *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक drm_agp_acquire(काष्ठा drm_device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक drm_agp_release(काष्ठा drm_device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक drm_agp_enable(काष्ठा drm_device *dev,
				 काष्ठा drm_agp_mode mode)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक drm_agp_info(काष्ठा drm_device *dev,
			       काष्ठा drm_agp_info *info)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक drm_agp_alloc(काष्ठा drm_device *dev,
				काष्ठा drm_agp_buffer *request)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक drm_agp_मुक्त(काष्ठा drm_device *dev,
			       काष्ठा drm_agp_buffer *request)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक drm_agp_unbind(काष्ठा drm_device *dev,
				 काष्ठा drm_agp_binding *request)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक drm_agp_bind(काष्ठा drm_device *dev,
			       काष्ठा drm_agp_binding *request)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर /* CONFIG_AGP */

#पूर्ण_अगर /* _DRM_AGPSUPPORT_H_ */
