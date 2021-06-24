<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Linaro Ltd.
 * Copyright 2016 ZTE Corporation.
 */

#अगर_अघोषित __ZX_PLANE_H__
#घोषणा __ZX_PLANE_H__

काष्ठा zx_plane अणु
	काष्ठा drm_plane plane;
	काष्ठा device *dev;
	व्योम __iomem *layer;
	व्योम __iomem *csc;
	व्योम __iomem *hbsc;
	व्योम __iomem *rsz;
	स्थिर काष्ठा vou_layer_bits *bits;
पूर्ण;

#घोषणा to_zx_plane(plane) container_of(plane, काष्ठा zx_plane, plane)

पूर्णांक zx_plane_init(काष्ठा drm_device *drm, काष्ठा zx_plane *zplane,
		  क्रमागत drm_plane_type type);
व्योम zx_plane_set_update(काष्ठा drm_plane *plane);

#पूर्ण_अगर /* __ZX_PLANE_H__ */
