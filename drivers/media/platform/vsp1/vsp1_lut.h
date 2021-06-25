<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_lut.h  --  R-Car VSP1 Look-Up Table
 *
 * Copyright (C) 2013 Renesas Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_LUT_H__
#घोषणा __VSP1_LUT_H__

#समावेश <linux/spinlock.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_entity.h"

काष्ठा vsp1_device;

#घोषणा LUT_PAD_SINK				0
#घोषणा LUT_PAD_SOURCE				1

काष्ठा vsp1_lut अणु
	काष्ठा vsp1_entity entity;

	काष्ठा v4l2_ctrl_handler ctrls;

	spinlock_t lock;
	काष्ठा vsp1_dl_body *lut;
	काष्ठा vsp1_dl_body_pool *pool;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_lut *to_lut(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_lut, entity.subdev);
पूर्ण

काष्ठा vsp1_lut *vsp1_lut_create(काष्ठा vsp1_device *vsp1);

#पूर्ण_अगर /* __VSP1_LUT_H__ */
