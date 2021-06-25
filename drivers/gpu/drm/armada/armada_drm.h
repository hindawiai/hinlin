<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Russell King
 */
#अगर_अघोषित ARMADA_DRM_H
#घोषणा ARMADA_DRM_H

#समावेश <linux/kfअगरo.h>
#समावेश <linux/पन.स>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mm.h>

काष्ठा armada_crtc;
काष्ठा armada_gem_object;
काष्ठा clk;
काष्ठा drm_display_mode;
काष्ठा drm_fb_helper;

अटल अंतरभूत व्योम
armada_updatel(uपूर्णांक32_t val, uपूर्णांक32_t mask, व्योम __iomem *ptr)
अणु
	uपूर्णांक32_t ov, v;

	ov = v = पढ़ोl_relaxed(ptr);
	v = (v & ~mask) | val;
	अगर (ov != v)
		ग_लिखोl_relaxed(v, ptr);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t armada_pitch(uपूर्णांक32_t width, uपूर्णांक32_t bpp)
अणु
	uपूर्णांक32_t pitch = bpp != 4 ? width * ((bpp + 7) / 8) : width / 2;

	/* 88AP510 spec recommends pitch be a multiple of 128 */
	वापस ALIGN(pitch, 128);
पूर्ण


काष्ठा armada_निजी;

काष्ठा armada_variant अणु
	bool has_spu_adv_reg;
	पूर्णांक (*init)(काष्ठा armada_crtc *, काष्ठा device *);
	पूर्णांक (*compute_घड़ी)(काष्ठा armada_crtc *,
			     स्थिर काष्ठा drm_display_mode *,
			     uपूर्णांक32_t *);
	व्योम (*disable)(काष्ठा armada_crtc *);
	व्योम (*enable)(काष्ठा armada_crtc *, स्थिर काष्ठा drm_display_mode *);
पूर्ण;

/* Variant ops */
बाह्य स्थिर काष्ठा armada_variant armada510_ops;

काष्ठा armada_निजी अणु
	काष्ठा drm_device	drm;
	काष्ठा drm_fb_helper	*fbdev;
	काष्ठा armada_crtc	*dcrtc[2];
	काष्ठा drm_mm		linear; /* रक्षित by linear_lock */
	काष्ठा mutex		linear_lock;
	काष्ठा drm_property	*colorkey_prop;
	काष्ठा drm_property	*colorkey_min_prop;
	काष्ठा drm_property	*colorkey_max_prop;
	काष्ठा drm_property	*colorkey_val_prop;
	काष्ठा drm_property	*colorkey_alpha_prop;
	काष्ठा drm_property	*colorkey_mode_prop;
	काष्ठा drm_property	*brightness_prop;
	काष्ठा drm_property	*contrast_prop;
	काष्ठा drm_property	*saturation_prop;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry		*de;
#पूर्ण_अगर
पूर्ण;

#घोषणा drm_to_armada_dev(dev) container_of(dev, काष्ठा armada_निजी, drm)

पूर्णांक armada_fbdev_init(काष्ठा drm_device *);
व्योम armada_fbdev_fini(काष्ठा drm_device *);

पूर्णांक armada_overlay_plane_create(काष्ठा drm_device *, अचिन्हित दीर्घ);

व्योम armada_drm_crtc_debugfs_init(काष्ठा armada_crtc *dcrtc);
पूर्णांक armada_drm_debugfs_init(काष्ठा drm_minor *);

#पूर्ण_अगर
