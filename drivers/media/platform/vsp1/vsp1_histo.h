<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_histo.h  --  R-Car VSP1 Histogram API
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 * Copyright (C) 2016 Laurent Pinअक्षरt
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_HISTO_H__
#घोषणा __VSP1_HISTO_H__

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "vsp1_entity.h"

काष्ठा vsp1_device;

#घोषणा HISTO_PAD_SINK				0
#घोषणा HISTO_PAD_SOURCE			1

काष्ठा vsp1_histogram_buffer अणु
	काष्ठा vb2_v4l2_buffer buf;
	काष्ठा list_head queue;
	व्योम *addr;
पूर्ण;

काष्ठा vsp1_histogram अणु
	काष्ठा vsp1_entity entity;
	काष्ठा video_device video;
	काष्ठा media_pad pad;

	स्थिर u32 *क्रमmats;
	अचिन्हित पूर्णांक num_क्रमmats;
	माप_प्रकार data_size;
	u32 meta_क्रमmat;

	काष्ठा mutex lock;
	काष्ठा vb2_queue queue;

	spinlock_t irqlock;
	काष्ठा list_head irqqueue;

	रुको_queue_head_t रुको_queue;
	bool पढ़ोout;
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_histogram *vdev_to_histo(काष्ठा video_device *vdev)
अणु
	वापस container_of(vdev, काष्ठा vsp1_histogram, video);
पूर्ण

अटल अंतरभूत काष्ठा vsp1_histogram *subdev_to_histo(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा vsp1_histogram, entity.subdev);
पूर्ण

पूर्णांक vsp1_histogram_init(काष्ठा vsp1_device *vsp1, काष्ठा vsp1_histogram *histo,
			क्रमागत vsp1_entity_type type, स्थिर अक्षर *name,
			स्थिर काष्ठा vsp1_entity_operations *ops,
			स्थिर अचिन्हित पूर्णांक *क्रमmats, अचिन्हित पूर्णांक num_क्रमmats,
			माप_प्रकार data_size, u32 meta_क्रमmat);
व्योम vsp1_histogram_destroy(काष्ठा vsp1_entity *entity);

काष्ठा vsp1_histogram_buffer *
vsp1_histogram_buffer_get(काष्ठा vsp1_histogram *histo);
व्योम vsp1_histogram_buffer_complete(काष्ठा vsp1_histogram *histo,
				    काष्ठा vsp1_histogram_buffer *buf,
				    माप_प्रकार size);

#पूर्ण_अगर /* __VSP1_HISTO_H__ */
