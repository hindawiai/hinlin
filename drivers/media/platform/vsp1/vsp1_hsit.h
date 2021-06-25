<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_hsit.h  --  R-Car VSP1 Hue Saturation value (Inverse) Transक्रमm
 *
 * Copyright (C) 2013 Renesas Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_HSIT_H__
#घोषणा __VSP1_HSIT_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_entity.h"

काष्ठा vsp1_device;

#घोषणा HSIT_PAD_SINK				0
#घोषणा HSIT_PAD_SOURCE				1

काष्ठा vsp1_hsit अणु
	काष्ठा vsp1_entity entity;
	bool inverse;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_hsit *to_hsit(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_hsit, entity.subdev);
पूर्ण

काष्ठा vsp1_hsit *vsp1_hsit_create(काष्ठा vsp1_device *vsp1, bool inverse);

#पूर्ण_अगर /* __VSP1_HSIT_H__ */
