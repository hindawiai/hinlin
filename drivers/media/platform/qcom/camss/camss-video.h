<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * camss-video.h
 *
 * Qualcomm MSM Camera Subप्रणाली - V4L2 device node
 *
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#अगर_अघोषित QC_MSM_CAMSS_VIDEO_H
#घोषणा QC_MSM_CAMSS_VIDEO_H

#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/videobuf2-v4l2.h>

काष्ठा camss_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	dma_addr_t addr[3];
	काष्ठा list_head queue;
पूर्ण;

काष्ठा camss_video;

काष्ठा camss_video_ops अणु
	पूर्णांक (*queue_buffer)(काष्ठा camss_video *vid, काष्ठा camss_buffer *buf);
	पूर्णांक (*flush_buffers)(काष्ठा camss_video *vid,
			     क्रमागत vb2_buffer_state state);
पूर्ण;

काष्ठा camss_क्रमmat_info;

काष्ठा camss_video अणु
	काष्ठा camss *camss;
	काष्ठा vb2_queue vb2_q;
	काष्ठा video_device vdev;
	काष्ठा media_pad pad;
	काष्ठा v4l2_क्रमmat active_fmt;
	क्रमागत v4l2_buf_type type;
	काष्ठा media_pipeline pipe;
	स्थिर काष्ठा camss_video_ops *ops;
	काष्ठा mutex lock;
	काष्ठा mutex q_lock;
	अचिन्हित पूर्णांक bpl_alignment;
	अचिन्हित पूर्णांक line_based;
	स्थिर काष्ठा camss_क्रमmat_info *क्रमmats;
	अचिन्हित पूर्णांक nक्रमmats;
पूर्ण;

पूर्णांक msm_video_रेजिस्टर(काष्ठा camss_video *video, काष्ठा v4l2_device *v4l2_dev,
		       स्थिर अक्षर *name, पूर्णांक is_pix);

व्योम msm_video_unरेजिस्टर(काष्ठा camss_video *video);

#पूर्ण_अगर /* QC_MSM_CAMSS_VIDEO_H */
