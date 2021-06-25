<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_sru.h  --  R-Car VSP1 Super Resolution Unit
 *
 * Copyright (C) 2013 Renesas Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_SRU_H__
#घोषणा __VSP1_SRU_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_entity.h"

काष्ठा vsp1_device;

#घोषणा SRU_PAD_SINK				0
#घोषणा SRU_PAD_SOURCE				1

काष्ठा vsp1_sru अणु
	काष्ठा vsp1_entity entity;

	काष्ठा v4l2_ctrl_handler ctrls;

	अचिन्हित पूर्णांक पूर्णांकensity;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_sru *to_sru(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_sru, entity.subdev);
पूर्ण

काष्ठा vsp1_sru *vsp1_sru_create(काष्ठा vsp1_device *vsp1);

#पूर्ण_अगर /* __VSP1_SRU_H__ */
