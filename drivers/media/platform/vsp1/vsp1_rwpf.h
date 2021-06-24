<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_rwpf.h  --  R-Car VSP1 Read and Write Pixel Formatters
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_RWPF_H__
#घोषणा __VSP1_RWPF_H__

#समावेश <linux/spinlock.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1.h"
#समावेश "vsp1_entity.h"

#घोषणा RWPF_PAD_SINK				0
#घोषणा RWPF_PAD_SOURCE				1

काष्ठा v4l2_ctrl;
काष्ठा vsp1_dl_manager;
काष्ठा vsp1_rwpf;
काष्ठा vsp1_video;

काष्ठा vsp1_rwpf_memory अणु
	dma_addr_t addr[3];
पूर्ण;

काष्ठा vsp1_rwpf अणु
	काष्ठा vsp1_entity entity;
	काष्ठा v4l2_ctrl_handler ctrls;

	काष्ठा vsp1_video *video;

	अचिन्हित पूर्णांक max_width;
	अचिन्हित पूर्णांक max_height;

	काष्ठा v4l2_pix_क्रमmat_mplane क्रमmat;
	स्थिर काष्ठा vsp1_क्रमmat_info *fmtinfo;
	अचिन्हित पूर्णांक brx_input;

	अचिन्हित पूर्णांक alpha;

	u32 mult_alpha;
	u32 outfmt;

	काष्ठा अणु
		spinlock_t lock;
		काष्ठा अणु
			काष्ठा v4l2_ctrl *vflip;
			काष्ठा v4l2_ctrl *hflip;
			काष्ठा v4l2_ctrl *rotate;
		पूर्ण ctrls;
		अचिन्हित पूर्णांक pending;
		अचिन्हित पूर्णांक active;
		bool rotate;
	पूर्ण flip;

	काष्ठा vsp1_rwpf_memory mem;
	bool ग_लिखोback;

	काष्ठा vsp1_dl_manager *dlm;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_rwpf *to_rwpf(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_rwpf, entity.subdev);
पूर्ण

अटल अंतरभूत काष्ठा vsp1_rwpf *entity_to_rwpf(काष्ठा vsp1_entity *entity)
अणु
	वापस container_of(entity, काष्ठा vsp1_rwpf, entity);
पूर्ण

काष्ठा vsp1_rwpf *vsp1_rpf_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index);
काष्ठा vsp1_rwpf *vsp1_wpf_create(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index);

पूर्णांक vsp1_rwpf_init_ctrls(काष्ठा vsp1_rwpf *rwpf, अचिन्हित पूर्णांक ncontrols);

बाह्य स्थिर काष्ठा v4l2_subdev_pad_ops vsp1_rwpf_pad_ops;

काष्ठा v4l2_rect *vsp1_rwpf_get_crop(काष्ठा vsp1_rwpf *rwpf,
				     काष्ठा v4l2_subdev_pad_config *config);

#पूर्ण_अगर /* __VSP1_RWPF_H__ */
