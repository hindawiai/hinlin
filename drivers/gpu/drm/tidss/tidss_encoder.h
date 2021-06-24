<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#अगर_अघोषित __TIDSS_ENCODER_H__
#घोषणा __TIDSS_ENCODER_H__

#समावेश <drm/drm_encoder.h>

काष्ठा tidss_device;

काष्ठा drm_encoder *tidss_encoder_create(काष्ठा tidss_device *tidss,
					 u32 encoder_type, u32 possible_crtcs);

#पूर्ण_अगर
