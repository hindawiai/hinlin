<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung S5P/EXYNOS4 SoC Camera Subप्रणाली driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <media/drv-पूर्णांकf/exynos-fimc.h>
#समावेश "common.h"

/* Called with the media graph mutex held or entity->stream_count > 0. */
काष्ठा v4l2_subdev *fimc_find_remote_sensor(काष्ठा media_entity *entity)
अणु
	काष्ठा media_pad *pad = &entity->pads[0];
	काष्ठा v4l2_subdev *sd;

	जबतक (pad->flags & MEDIA_PAD_FL_SINK) अणु
		/* source pad */
		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			अवरोध;

		sd = media_entity_to_v4l2_subdev(pad->entity);

		अगर (sd->grp_id == GRP_ID_FIMC_IS_SENSOR ||
		    sd->grp_id == GRP_ID_SENSOR)
			वापस sd;
		/* sink pad */
		pad = &sd->entity.pads[0];
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(fimc_find_remote_sensor);

व्योम __fimc_vidioc_querycap(काष्ठा device *dev, काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, dev->driver->name, माप(cap->driver));
	strscpy(cap->card, dev->driver->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
				"platform:%s", dev_name(dev));
पूर्ण
EXPORT_SYMBOL(__fimc_vidioc_querycap);

MODULE_LICENSE("GPL");
