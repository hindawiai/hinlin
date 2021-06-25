<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_uds.h  --  R-Car VSP1 Up and Down Scaler
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_UDS_H__
#घोषणा __VSP1_UDS_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_entity.h"

काष्ठा vsp1_device;

#घोषणा UDS_PAD_SINK				0
#घोषणा UDS_PAD_SOURCE				1

काष्ठा vsp1_uds अणु
	काष्ठा vsp1_entity entity;
	bool scale_alpha;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_uds *to_uds(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_uds, entity.subdev);
पूर्ण

काष्ठा vsp1_uds *vsp1_uds_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index);

व्योम vsp1_uds_set_alpha(काष्ठा vsp1_entity *uds, काष्ठा vsp1_dl_body *dlb,
			अचिन्हित पूर्णांक alpha);

#पूर्ण_अगर /* __VSP1_UDS_H__ */
