<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_video.h  --  R-Car VSP1 Video Node
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_VIDEO_H__
#घोषणा __VSP1_VIDEO_H__

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>

#समावेश <media/videobuf2-v4l2.h>

#समावेश "vsp1_rwpf.h"

काष्ठा vsp1_vb2_buffer अणु
	काष्ठा vb2_v4l2_buffer buf;
	काष्ठा list_head queue;
	काष्ठा vsp1_rwpf_memory mem;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_vb2_buffer *
to_vsp1_vb2_buffer(काष्ठा vb2_v4l2_buffer *vbuf)
अणु
	वापस container_of(vbuf, काष्ठा vsp1_vb2_buffer, buf);
पूर्ण

काष्ठा vsp1_video अणु
	काष्ठा list_head list;
	काष्ठा vsp1_device *vsp1;
	काष्ठा vsp1_rwpf *rwpf;

	काष्ठा video_device video;
	क्रमागत v4l2_buf_type type;
	काष्ठा media_pad pad;

	काष्ठा mutex lock;

	अचिन्हित पूर्णांक pipe_index;

	काष्ठा vb2_queue queue;
	spinlock_t irqlock;
	काष्ठा list_head irqqueue;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_video *to_vsp1_video(काष्ठा video_device *vdev)
अणु
	वापस container_of(vdev, काष्ठा vsp1_video, video);
पूर्ण

व्योम vsp1_video_suspend(काष्ठा vsp1_device *vsp1);
व्योम vsp1_video_resume(काष्ठा vsp1_device *vsp1);

काष्ठा vsp1_video *vsp1_video_create(काष्ठा vsp1_device *vsp1,
				     काष्ठा vsp1_rwpf *rwpf);
व्योम vsp1_video_cleanup(काष्ठा vsp1_video *video);

#पूर्ण_अगर /* __VSP1_VIDEO_H__ */
