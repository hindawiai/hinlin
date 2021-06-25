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
#समावेश "atomisp_internal.h"
#समावेश "atomisp_tpg.h"

अटल पूर्णांक tpg_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tpg_get_fmt(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	/*to fake*/
	वापस 0;
पूर्ण

अटल पूर्णांक tpg_set_fmt(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;

	अगर (क्रमmat->pad)
		वापस -EINVAL;
	/* only raw8 grbg is supported by TPG */
	fmt->code = MEDIA_BUS_FMT_SGRBG8_1X8;
	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cfg->try_fmt = *fmt;
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tpg_log_status(काष्ठा v4l2_subdev *sd)
अणु
	/*to fake*/
	वापस 0;
पूर्ण

अटल पूर्णांक tpg_s_घातer(काष्ठा v4l2_subdev *sd, पूर्णांक on)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tpg_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	/*to fake*/
	वापस 0;
पूर्ण

अटल पूर्णांक tpg_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	/*to fake*/
	वापस 0;
पूर्ण

अटल पूर्णांक tpg_क्रमागत_frame_ival(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	/*to fake*/
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops tpg_video_ops = अणु
	.s_stream = tpg_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops tpg_core_ops = अणु
	.log_status = tpg_log_status,
	.s_घातer = tpg_s_घातer,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops tpg_pad_ops = अणु
	.क्रमागत_mbus_code = tpg_क्रमागत_mbus_code,
	.क्रमागत_frame_size = tpg_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval = tpg_क्रमागत_frame_ival,
	.get_fmt = tpg_get_fmt,
	.set_fmt = tpg_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops tpg_ops = अणु
	.core = &tpg_core_ops,
	.video = &tpg_video_ops,
	.pad = &tpg_pad_ops,
पूर्ण;

व्योम atomisp_tpg_unरेजिस्टर_entities(काष्ठा atomisp_tpg_device *tpg)
अणु
	media_entity_cleanup(&tpg->sd.entity);
	v4l2_device_unरेजिस्टर_subdev(&tpg->sd);
पूर्ण

पूर्णांक atomisp_tpg_रेजिस्टर_entities(काष्ठा atomisp_tpg_device *tpg,
				  काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;
	/* Register the subdev and video nodes. */
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &tpg->sd);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	atomisp_tpg_unरेजिस्टर_entities(tpg);
	वापस ret;
पूर्ण

व्योम atomisp_tpg_cleanup(काष्ठा atomisp_device *isp)
अणु
पूर्ण

पूर्णांक atomisp_tpg_init(काष्ठा atomisp_device *isp)
अणु
	काष्ठा atomisp_tpg_device *tpg = &isp->tpg;
	काष्ठा v4l2_subdev *sd = &tpg->sd;
	काष्ठा media_pad *pads = tpg->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	tpg->isp = isp;
	v4l2_subdev_init(sd, &tpg_ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	strscpy(sd->name, "tpg_subdev", माप(sd->name));
	v4l2_set_subdevdata(sd, tpg);

	pads[0].flags = MEDIA_PAD_FL_SINK;
	me->function = MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN;

	ret = media_entity_pads_init(me, 1, pads);
	अगर (ret < 0)
		जाओ fail;
	वापस 0;
fail:
	atomisp_tpg_cleanup(isp);
	वापस ret;
पूर्ण
