<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar_du_encoder.h  --  R-Car Display Unit Encoder
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_DU_ENCODER_H__
#घोषणा __RCAR_DU_ENCODER_H__

#समावेश <drm/drm_encoder.h>

काष्ठा rcar_du_device;

काष्ठा rcar_du_encoder अणु
	काष्ठा drm_encoder base;
	क्रमागत rcar_du_output output;
पूर्ण;

#घोषणा to_rcar_encoder(e) \
	container_of(e, काष्ठा rcar_du_encoder, base)

पूर्णांक rcar_du_encoder_init(काष्ठा rcar_du_device *rcdu,
			 क्रमागत rcar_du_output output,
			 काष्ठा device_node *enc_node);

#पूर्ण_अगर /* __RCAR_DU_ENCODER_H__ */
