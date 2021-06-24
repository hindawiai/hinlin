<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 2011-2018 Magewell Electronics Co., Ltd. (Nanjing)
 * All rights reserved.
 * Author: Yong Deng <yong.deng@magewell.com>
 */

#अगर_अघोषित __SUN6I_VIDEO_H__
#घोषणा __SUN6I_VIDEO_H__

#समावेश <media/v4l2-dev.h>
#समावेश <media/videobuf2-core.h>

काष्ठा sun6i_csi;

काष्ठा sun6i_video अणु
	काष्ठा video_device		vdev;
	काष्ठा media_pad		pad;
	काष्ठा sun6i_csi		*csi;

	काष्ठा mutex			lock;

	काष्ठा vb2_queue		vb2_vidq;
	spinlock_t			dma_queue_lock;
	काष्ठा list_head		dma_queue;

	अचिन्हित पूर्णांक			sequence;
	काष्ठा v4l2_क्रमmat		fmt;
	u32				mbus_code;
पूर्ण;

पूर्णांक sun6i_video_init(काष्ठा sun6i_video *video, काष्ठा sun6i_csi *csi,
		     स्थिर अक्षर *name);
व्योम sun6i_video_cleanup(काष्ठा sun6i_video *video);

व्योम sun6i_video_frame_करोne(काष्ठा sun6i_video *video);

#पूर्ण_अगर /* __SUN6I_VIDEO_H__ */
