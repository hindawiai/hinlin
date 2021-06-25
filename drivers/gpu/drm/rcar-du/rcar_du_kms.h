<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar_du_kms.h  --  R-Car Display Unit Mode Setting
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_DU_KMS_H__
#घोषणा __RCAR_DU_KMS_H__

#समावेश <linux/types.h>

काष्ठा drm_file;
काष्ठा drm_device;
काष्ठा drm_mode_create_dumb;
काष्ठा rcar_du_device;

काष्ठा rcar_du_क्रमmat_info अणु
	u32 fourcc;
	u32 v4l2;
	अचिन्हित पूर्णांक bpp;
	अचिन्हित पूर्णांक planes;
	अचिन्हित पूर्णांक hsub;
	अचिन्हित पूर्णांक pnmr;
	अचिन्हित पूर्णांक edf;
पूर्ण;

स्थिर काष्ठा rcar_du_क्रमmat_info *rcar_du_क्रमmat_info(u32 fourcc);

पूर्णांक rcar_du_modeset_init(काष्ठा rcar_du_device *rcdu);

पूर्णांक rcar_du_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			काष्ठा drm_mode_create_dumb *args);

#पूर्ण_अगर /* __RCAR_DU_KMS_H__ */
