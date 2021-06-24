<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_hgt.h  --  R-Car VSP1 Histogram Generator 2D
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 *
 * Contact: Niklas Sथघderlund (niklas.soderlund@ragnatech.se)
 */
#अगर_अघोषित __VSP1_HGT_H__
#घोषणा __VSP1_HGT_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_histo.h"

काष्ठा vsp1_device;

#घोषणा HGT_NUM_HUE_AREAS			6

काष्ठा vsp1_hgt अणु
	काष्ठा vsp1_histogram histo;

	काष्ठा v4l2_ctrl_handler ctrls;

	u8 hue_areas[HGT_NUM_HUE_AREAS * 2];
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_hgt *to_hgt(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_hgt, histo.entity.subdev);
पूर्ण

काष्ठा vsp1_hgt *vsp1_hgt_create(काष्ठा vsp1_device *vsp1);
व्योम vsp1_hgt_frame_end(काष्ठा vsp1_entity *hgt);

#पूर्ण_अगर /* __VSP1_HGT_H__ */
