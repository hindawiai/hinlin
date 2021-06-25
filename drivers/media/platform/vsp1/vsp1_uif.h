<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_uअगर.h  --  R-Car VSP1 User Logic Interface
 *
 * Copyright (C) 2017-2018 Laurent Pinअक्षरt
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_UIF_H__
#घोषणा __VSP1_UIF_H__

#समावेश "vsp1_entity.h"

काष्ठा vsp1_device;

#घोषणा UIF_PAD_SINK				0
#घोषणा UIF_PAD_SOURCE				1

काष्ठा vsp1_uअगर अणु
	काष्ठा vsp1_entity entity;
	bool m3w_quirk;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_uअगर *to_uअगर(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_uअगर, entity.subdev);
पूर्ण

काष्ठा vsp1_uअगर *vsp1_uअगर_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index);
u32 vsp1_uअगर_get_crc(काष्ठा vsp1_uअगर *uअगर);

#पूर्ण_अगर /* __VSP1_UIF_H__ */
