<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_lअगर.h  --  R-Car VSP1 LCD Controller Interface
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_LIF_H__
#घोषणा __VSP1_LIF_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_entity.h"

काष्ठा vsp1_device;

#घोषणा LIF_PAD_SINK				0
#घोषणा LIF_PAD_SOURCE				1

काष्ठा vsp1_lअगर अणु
	काष्ठा vsp1_entity entity;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_lअगर *to_lअगर(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_lअगर, entity.subdev);
पूर्ण

काष्ठा vsp1_lअगर *vsp1_lअगर_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index);

#पूर्ण_अगर /* __VSP1_LIF_H__ */
