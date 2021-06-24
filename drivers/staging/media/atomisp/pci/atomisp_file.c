<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mediabus.h>

#समावेश <media/videobuf-vदो_स्मृति.h>
#समावेश <linux/delay.h>

#समावेश "ia_css.h"

#समावेश "atomisp_cmd.h"
#समावेश "atomisp_common.h"
#समावेश "atomisp_file.h"
#समावेश "atomisp_internal.h"
#समावेश "atomisp_ioctl.h"

अटल व्योम file_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा atomisp_file_device *file_dev =
	    container_of(work, काष्ठा atomisp_file_device, work);
	काष्ठा atomisp_device *isp = file_dev->isp;
	/* only support file injection on subdev0 */
	काष्ठा atomisp_sub_device *asd = &isp->asd[0];
	काष्ठा atomisp_video_pipe *out_pipe = &asd->video_in;
	अचिन्हित लघु *buf = videobuf_to_vदो_स्मृति(out_pipe->outq.bufs[0]);
	काष्ठा v4l2_mbus_framefmt isp_sink_fmt;

	अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
		वापस;

	dev_dbg(isp->dev, ">%s: ready to start streaming\n", __func__);
	isp_sink_fmt = *atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
						V4L2_SUBDEV_FORMAT_ACTIVE,
						ATOMISP_SUBDEV_PAD_SINK);

	जबतक (!ia_css_isp_has_started())
		usleep_range(1000, 1500);

	ia_css_stream_send_input_frame(asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].stream,
				       buf, isp_sink_fmt.width,
				       isp_sink_fmt.height);
	dev_dbg(isp->dev, "<%s: streaming done\n", __func__);
पूर्ण

अटल पूर्णांक file_input_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा atomisp_file_device *file_dev = v4l2_get_subdevdata(sd);
	काष्ठा atomisp_device *isp = file_dev->isp;
	/* only support file injection on subdev0 */
	काष्ठा atomisp_sub_device *asd = &isp->asd[0];

	dev_dbg(isp->dev, "%s: enable %d\n", __func__, enable);
	अगर (enable) अणु
		अगर (asd->streaming != ATOMISP_DEVICE_STREAMING_ENABLED)
			वापस 0;

		queue_work(file_dev->work_queue, &file_dev->work);
		वापस 0;
	पूर्ण
	cancel_work_sync(&file_dev->work);
	वापस 0;
पूर्ण

अटल पूर्णांक file_input_get_fmt(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा atomisp_file_device *file_dev = v4l2_get_subdevdata(sd);
	काष्ठा atomisp_device *isp = file_dev->isp;
	/* only support file injection on subdev0 */
	काष्ठा atomisp_sub_device *asd = &isp->asd[0];
	काष्ठा v4l2_mbus_framefmt *isp_sink_fmt;

	अगर (क्रमmat->pad)
		वापस -EINVAL;
	isp_sink_fmt = atomisp_subdev_get_ffmt(&asd->subdev, शून्य,
					       V4L2_SUBDEV_FORMAT_ACTIVE,
					       ATOMISP_SUBDEV_PAD_SINK);

	fmt->width = isp_sink_fmt->width;
	fmt->height = isp_sink_fmt->height;
	fmt->code = isp_sink_fmt->code;

	वापस 0;
पूर्ण

अटल पूर्णांक file_input_set_fmt(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;

	अगर (क्रमmat->pad)
		वापस -EINVAL;
	file_input_get_fmt(sd, cfg, क्रमmat);
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		cfg->try_fmt = *fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक file_input_log_status(काष्ठा v4l2_subdev *sd)
अणु
	/*to fake*/
	वापस 0;
पूर्ण

अटल पूर्णांक file_input_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	/* to fake */
	वापस 0;
पूर्ण

अटल पूर्णांक file_input_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_subdev_pad_config *cfg,
				     काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	/*to fake*/
	वापस 0;
पूर्ण

अटल पूर्णांक file_input_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	/*to fake*/
	वापस 0;
पूर्ण

अटल पूर्णांक file_input_क्रमागत_frame_ival(काष्ठा v4l2_subdev *sd,
				      काष्ठा v4l2_subdev_pad_config *cfg,
				      काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत
				      *fie)
अणु
	/*to fake*/
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops file_input_video_ops = अणु
	.s_stream = file_input_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops file_input_core_ops = अणु
	.log_status = file_input_log_status,
	.s_घातer = file_input_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops file_input_pad_ops = अणु
	.क्रमागत_mbus_code = file_input_क्रमागत_mbus_code,
	.क्रमागत_frame_size = file_input_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval = file_input_क्रमागत_frame_ival,
	.get_fmt = file_input_get_fmt,
	.set_fmt = file_input_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops file_input_ops = अणु
	.core = &file_input_core_ops,
	.video = &file_input_video_ops,
	.pad = &file_input_pad_ops,
पूर्ण;

व्योम
atomisp_file_input_unरेजिस्टर_entities(काष्ठा atomisp_file_device *file_dev)
अणु
	media_entity_cleanup(&file_dev->sd.entity);
	v4l2_device_unरेजिस्टर_subdev(&file_dev->sd);
पूर्ण

पूर्णांक atomisp_file_input_रेजिस्टर_entities(काष्ठा atomisp_file_device *file_dev,
	काष्ठा v4l2_device *vdev)
अणु
	/* Register the subdev and video nodes. */
	वापस  v4l2_device_रेजिस्टर_subdev(vdev, &file_dev->sd);
पूर्ण

व्योम atomisp_file_input_cleanup(काष्ठा atomisp_device *isp)
अणु
	काष्ठा atomisp_file_device *file_dev = &isp->file_dev;

	अगर (file_dev->work_queue) अणु
		destroy_workqueue(file_dev->work_queue);
		file_dev->work_queue = शून्य;
	पूर्ण
पूर्ण

पूर्णांक atomisp_file_input_init(काष्ठा atomisp_device *isp)
अणु
	काष्ठा atomisp_file_device *file_dev = &isp->file_dev;
	काष्ठा v4l2_subdev *sd = &file_dev->sd;
	काष्ठा media_pad *pads = file_dev->pads;
	काष्ठा media_entity *me = &sd->entity;

	file_dev->isp = isp;
	file_dev->work_queue = alloc_workqueue(isp->v4l2_dev.name, 0, 1);
	अगर (!file_dev->work_queue) अणु
		dev_err(isp->dev, "Failed to initialize file inject workq\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_WORK(&file_dev->work, file_work);

	v4l2_subdev_init(sd, &file_input_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	strscpy(sd->name, "file_input_subdev", माप(sd->name));
	v4l2_set_subdevdata(sd, file_dev);

	pads[0].flags = MEDIA_PAD_FL_SINK;
	me->function = MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN;

	वापस media_entity_pads_init(me, 1, pads);
पूर्ण
