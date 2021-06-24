<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_clu.h  --  R-Car VSP1 Cubic Look-Up Table
 *
 * Copyright (C) 2015 Renesas Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_CLU_H__
#घोषणा __VSP1_CLU_H__

#समावेश <linux/spinlock.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_entity.h"

काष्ठा vsp1_device;
काष्ठा vsp1_dl_body;

#घोषणा CLU_PAD_SINK				0
#घोषणा CLU_PAD_SOURCE				1

काष्ठा vsp1_clu अणु
	काष्ठा vsp1_entity entity;

	काष्ठा v4l2_ctrl_handler ctrls;

	bool yuv_mode;
	spinlock_t lock;
	अचिन्हित पूर्णांक mode;
	काष्ठा vsp1_dl_body *clu;
	काष्ठा vsp1_dl_body_pool *pool;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_clu *to_clu(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_clu, entity.subdev);
पूर्ण

काष्ठा vsp1_clu *vsp1_clu_create(काष्ठा vsp1_device *vsp1);

#पूर्ण_अगर /* __VSP1_CLU_H__ */
