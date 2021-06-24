<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_hgo.h  --  R-Car VSP1 Histogram Generator 1D
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_HGO_H__
#घोषणा __VSP1_HGO_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_histo.h"

काष्ठा vsp1_device;

काष्ठा vsp1_hgo अणु
	काष्ठा vsp1_histogram histo;

	काष्ठा अणु
		काष्ठा v4l2_ctrl_handler handler;
		काष्ठा v4l2_ctrl *max_rgb;
		काष्ठा v4l2_ctrl *num_bins;
	पूर्ण ctrls;

	bool max_rgb;
	अचिन्हित पूर्णांक num_bins;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_hgo *to_hgo(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_hgo, histo.entity.subdev);
पूर्ण

काष्ठा vsp1_hgo *vsp1_hgo_create(काष्ठा vsp1_device *vsp1);
व्योम vsp1_hgo_frame_end(काष्ठा vsp1_entity *hgo);

#पूर्ण_अगर /* __VSP1_HGO_H__ */
