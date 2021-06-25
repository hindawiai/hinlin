<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_brx.h  --  R-Car VSP1 Blend ROP Unit (BRU and BRS)
 *
 * Copyright (C) 2013 Renesas Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_BRX_H__
#घोषणा __VSP1_BRX_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_entity.h"

काष्ठा vsp1_device;
काष्ठा vsp1_rwpf;

#घोषणा BRX_PAD_SINK(n)				(n)

काष्ठा vsp1_brx अणु
	काष्ठा vsp1_entity entity;
	अचिन्हित पूर्णांक base;

	काष्ठा v4l2_ctrl_handler ctrls;

	काष्ठा अणु
		काष्ठा vsp1_rwpf *rpf;
	पूर्ण inमाला_दो[VSP1_MAX_RPF];

	u32 bgcolor;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_brx *to_brx(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_brx, entity.subdev);
पूर्ण

काष्ठा vsp1_brx *vsp1_brx_create(काष्ठा vsp1_device *vsp1,
				 क्रमागत vsp1_entity_type type);

#पूर्ण_अगर /* __VSP1_BRX_H__ */
