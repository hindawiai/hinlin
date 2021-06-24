<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * V4L2 sub-device
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contact: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	    Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/ioctl.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/export.h>
#समावेश <linux/version.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>

#अगर defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
अटल पूर्णांक subdev_fh_init(काष्ठा v4l2_subdev_fh *fh, काष्ठा v4l2_subdev *sd)
अणु
	अगर (sd->entity.num_pads) अणु
		fh->pad = v4l2_subdev_alloc_pad_config(sd);
		अगर (fh->pad == शून्य)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम subdev_fh_मुक्त(काष्ठा v4l2_subdev_fh *fh)
अणु
	v4l2_subdev_मुक्त_pad_config(fh->pad);
	fh->pad = शून्य;
पूर्ण

अटल पूर्णांक subdev_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा v4l2_subdev *sd = vdev_to_v4l2_subdev(vdev);
	काष्ठा v4l2_subdev_fh *subdev_fh;
	पूर्णांक ret;

	subdev_fh = kzalloc(माप(*subdev_fh), GFP_KERNEL);
	अगर (subdev_fh == शून्य)
		वापस -ENOMEM;

	ret = subdev_fh_init(subdev_fh, sd);
	अगर (ret) अणु
		kमुक्त(subdev_fh);
		वापस ret;
	पूर्ण

	v4l2_fh_init(&subdev_fh->vfh, vdev);
	v4l2_fh_add(&subdev_fh->vfh);
	file->निजी_data = &subdev_fh->vfh;
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	अगर (sd->v4l2_dev->mdev && sd->entity.graph_obj.mdev->dev) अणु
		काष्ठा module *owner;

		owner = sd->entity.graph_obj.mdev->dev->driver->owner;
		अगर (!try_module_get(owner)) अणु
			ret = -EBUSY;
			जाओ err;
		पूर्ण
		subdev_fh->owner = owner;
	पूर्ण
#पूर्ण_अगर

	अगर (sd->पूर्णांकernal_ops && sd->पूर्णांकernal_ops->खोलो) अणु
		ret = sd->पूर्णांकernal_ops->खोलो(sd, subdev_fh);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	module_put(subdev_fh->owner);
	v4l2_fh_del(&subdev_fh->vfh);
	v4l2_fh_निकास(&subdev_fh->vfh);
	subdev_fh_मुक्त(subdev_fh);
	kमुक्त(subdev_fh);

	वापस ret;
पूर्ण

अटल पूर्णांक subdev_बंद(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा v4l2_subdev *sd = vdev_to_v4l2_subdev(vdev);
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा v4l2_subdev_fh *subdev_fh = to_v4l2_subdev_fh(vfh);

	अगर (sd->पूर्णांकernal_ops && sd->पूर्णांकernal_ops->बंद)
		sd->पूर्णांकernal_ops->बंद(sd, subdev_fh);
	module_put(subdev_fh->owner);
	v4l2_fh_del(vfh);
	v4l2_fh_निकास(vfh);
	subdev_fh_मुक्त(subdev_fh);
	kमुक्त(subdev_fh);
	file->निजी_data = शून्य;

	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_VIDEO_V4L2_SUBDEV_API */
अटल पूर्णांक subdev_खोलो(काष्ठा file *file)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक subdev_बंद(काष्ठा file *file)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_VIDEO_V4L2_SUBDEV_API */

अटल अंतरभूत पूर्णांक check_which(u32 which)
अणु
	अगर (which != V4L2_SUBDEV_FORMAT_TRY &&
	    which != V4L2_SUBDEV_FORMAT_ACTIVE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक check_pad(काष्ठा v4l2_subdev *sd, u32 pad)
अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	अगर (sd->entity.num_pads) अणु
		अगर (pad >= sd->entity.num_pads)
			वापस -EINVAL;
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	/* allow pad 0 on subdevices not रेजिस्टरed as media entities */
	अगर (pad > 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक check_cfg(u32 which, काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY && !cfg)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक check_क्रमmat(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	अगर (!क्रमmat)
		वापस -EINVAL;

	वापस check_which(क्रमmat->which) ? : check_pad(sd, क्रमmat->pad) ? :
	       check_cfg(क्रमmat->which, cfg);
पूर्ण

अटल पूर्णांक call_get_fmt(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	वापस check_क्रमmat(sd, cfg, क्रमmat) ? :
	       sd->ops->pad->get_fmt(sd, cfg, क्रमmat);
पूर्ण

अटल पूर्णांक call_set_fmt(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	वापस check_क्रमmat(sd, cfg, क्रमmat) ? :
	       sd->ops->pad->set_fmt(sd, cfg, क्रमmat);
पूर्ण

अटल पूर्णांक call_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	अगर (!code)
		वापस -EINVAL;

	वापस check_which(code->which) ? : check_pad(sd, code->pad) ? :
	       check_cfg(code->which, cfg) ? :
	       sd->ops->pad->क्रमागत_mbus_code(sd, cfg, code);
पूर्ण

अटल पूर्णांक call_क्रमागत_frame_size(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_frame_size_क्रमागत *fse)
अणु
	अगर (!fse)
		वापस -EINVAL;

	वापस check_which(fse->which) ? : check_pad(sd, fse->pad) ? :
	       check_cfg(fse->which, cfg) ? :
	       sd->ops->pad->क्रमागत_frame_size(sd, cfg, fse);
पूर्ण

अटल अंतरभूत पूर्णांक check_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				       काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	अगर (!fi)
		वापस -EINVAL;

	वापस check_pad(sd, fi->pad);
पूर्ण

अटल पूर्णांक call_g_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	वापस check_frame_पूर्णांकerval(sd, fi) ? :
	       sd->ops->video->g_frame_पूर्णांकerval(sd, fi);
पूर्ण

अटल पूर्णांक call_s_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi)
अणु
	वापस check_frame_पूर्णांकerval(sd, fi) ? :
	       sd->ops->video->s_frame_पूर्णांकerval(sd, fi);
पूर्ण

अटल पूर्णांक call_क्रमागत_frame_पूर्णांकerval(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_subdev_pad_config *cfg,
				    काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie)
अणु
	अगर (!fie)
		वापस -EINVAL;

	वापस check_which(fie->which) ? : check_pad(sd, fie->pad) ? :
	       check_cfg(fie->which, cfg) ? :
	       sd->ops->pad->क्रमागत_frame_पूर्णांकerval(sd, cfg, fie);
पूर्ण

अटल अंतरभूत पूर्णांक check_selection(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_selection *sel)
अणु
	अगर (!sel)
		वापस -EINVAL;

	वापस check_which(sel->which) ? : check_pad(sd, sel->pad) ? :
	       check_cfg(sel->which, cfg);
पूर्ण

अटल पूर्णांक call_get_selection(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_selection *sel)
अणु
	वापस check_selection(sd, cfg, sel) ? :
	       sd->ops->pad->get_selection(sd, cfg, sel);
पूर्ण

अटल पूर्णांक call_set_selection(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_selection *sel)
अणु
	वापस check_selection(sd, cfg, sel) ? :
	       sd->ops->pad->set_selection(sd, cfg, sel);
पूर्ण

अटल अंतरभूत पूर्णांक check_edid(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_edid *edid)
अणु
	अगर (!edid)
		वापस -EINVAL;

	अगर (edid->blocks && edid->edid == शून्य)
		वापस -EINVAL;

	वापस check_pad(sd, edid->pad);
पूर्ण

अटल पूर्णांक call_get_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_edid *edid)
अणु
	वापस check_edid(sd, edid) ? : sd->ops->pad->get_edid(sd, edid);
पूर्ण

अटल पूर्णांक call_set_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_edid *edid)
अणु
	वापस check_edid(sd, edid) ? : sd->ops->pad->set_edid(sd, edid);
पूर्ण

अटल पूर्णांक call_dv_timings_cap(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_dv_timings_cap *cap)
अणु
	अगर (!cap)
		वापस -EINVAL;

	वापस check_pad(sd, cap->pad) ? :
	       sd->ops->pad->dv_timings_cap(sd, cap);
पूर्ण

अटल पूर्णांक call_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_क्रमागत_dv_timings *dvt)
अणु
	अगर (!dvt)
		वापस -EINVAL;

	वापस check_pad(sd, dvt->pad) ? :
	       sd->ops->pad->क्रमागत_dv_timings(sd, dvt);
पूर्ण

अटल पूर्णांक call_get_mbus_config(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
				काष्ठा v4l2_mbus_config *config)
अणु
	वापस check_pad(sd, pad) ? :
	       sd->ops->pad->get_mbus_config(sd, pad, config);
पूर्ण

अटल पूर्णांक call_set_mbus_config(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
				काष्ठा v4l2_mbus_config *config)
अणु
	वापस check_pad(sd, pad) ? :
	       sd->ops->pad->get_mbus_config(sd, pad, config);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops v4l2_subdev_call_pad_wrappers = अणु
	.get_fmt		= call_get_fmt,
	.set_fmt		= call_set_fmt,
	.क्रमागत_mbus_code		= call_क्रमागत_mbus_code,
	.क्रमागत_frame_size	= call_क्रमागत_frame_size,
	.क्रमागत_frame_पूर्णांकerval	= call_क्रमागत_frame_पूर्णांकerval,
	.get_selection		= call_get_selection,
	.set_selection		= call_set_selection,
	.get_edid		= call_get_edid,
	.set_edid		= call_set_edid,
	.dv_timings_cap		= call_dv_timings_cap,
	.क्रमागत_dv_timings	= call_क्रमागत_dv_timings,
	.get_mbus_config	= call_get_mbus_config,
	.set_mbus_config	= call_set_mbus_config,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops v4l2_subdev_call_video_wrappers = अणु
	.g_frame_पूर्णांकerval	= call_g_frame_पूर्णांकerval,
	.s_frame_पूर्णांकerval	= call_s_frame_पूर्णांकerval,
पूर्ण;

स्थिर काष्ठा v4l2_subdev_ops v4l2_subdev_call_wrappers = अणु
	.pad	= &v4l2_subdev_call_pad_wrappers,
	.video	= &v4l2_subdev_call_video_wrappers,
पूर्ण;
EXPORT_SYMBOL(v4l2_subdev_call_wrappers);

#अगर defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
अटल दीर्घ subdev_करो_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा v4l2_subdev *sd = vdev_to_v4l2_subdev(vdev);
	काष्ठा v4l2_fh *vfh = file->निजी_data;
	काष्ठा v4l2_subdev_fh *subdev_fh = to_v4l2_subdev_fh(vfh);
	bool ro_subdev = test_bit(V4L2_FL_SUBDEV_RO_DEVNODE, &vdev->flags);
	पूर्णांक rval;

	चयन (cmd) अणु
	हाल VIDIOC_SUBDEV_QUERYCAP: अणु
		काष्ठा v4l2_subdev_capability *cap = arg;

		स_रखो(cap->reserved, 0, माप(cap->reserved));
		cap->version = LINUX_VERSION_CODE;
		cap->capabilities = ro_subdev ? V4L2_SUBDEV_CAP_RO_SUBDEV : 0;

		वापस 0;
	पूर्ण

	हाल VIDIOC_QUERYCTRL:
		/*
		 * TODO: this really should be folded पूर्णांकo v4l2_queryctrl (this
		 * currently वापसs -EINVAL क्रम शून्य control handlers).
		 * However, v4l2_queryctrl() is still called directly by
		 * drivers as well and until that has been addressed I believe
		 * it is safer to करो the check here. The same is true क्रम the
		 * other control ioctls below.
		 */
		अगर (!vfh->ctrl_handler)
			वापस -ENOTTY;
		वापस v4l2_queryctrl(vfh->ctrl_handler, arg);

	हाल VIDIOC_QUERY_EXT_CTRL:
		अगर (!vfh->ctrl_handler)
			वापस -ENOTTY;
		वापस v4l2_query_ext_ctrl(vfh->ctrl_handler, arg);

	हाल VIDIOC_QUERYMENU:
		अगर (!vfh->ctrl_handler)
			वापस -ENOTTY;
		वापस v4l2_querymenu(vfh->ctrl_handler, arg);

	हाल VIDIOC_G_CTRL:
		अगर (!vfh->ctrl_handler)
			वापस -ENOTTY;
		वापस v4l2_g_ctrl(vfh->ctrl_handler, arg);

	हाल VIDIOC_S_CTRL:
		अगर (!vfh->ctrl_handler)
			वापस -ENOTTY;
		वापस v4l2_s_ctrl(vfh, vfh->ctrl_handler, arg);

	हाल VIDIOC_G_EXT_CTRLS:
		अगर (!vfh->ctrl_handler)
			वापस -ENOTTY;
		वापस v4l2_g_ext_ctrls(vfh->ctrl_handler,
					vdev, sd->v4l2_dev->mdev, arg);

	हाल VIDIOC_S_EXT_CTRLS:
		अगर (!vfh->ctrl_handler)
			वापस -ENOTTY;
		वापस v4l2_s_ext_ctrls(vfh, vfh->ctrl_handler,
					vdev, sd->v4l2_dev->mdev, arg);

	हाल VIDIOC_TRY_EXT_CTRLS:
		अगर (!vfh->ctrl_handler)
			वापस -ENOTTY;
		वापस v4l2_try_ext_ctrls(vfh->ctrl_handler,
					  vdev, sd->v4l2_dev->mdev, arg);

	हाल VIDIOC_DQEVENT:
		अगर (!(sd->flags & V4L2_SUBDEV_FL_HAS_EVENTS))
			वापस -ENOIOCTLCMD;

		वापस v4l2_event_dequeue(vfh, arg, file->f_flags & O_NONBLOCK);

	हाल VIDIOC_DQEVENT_TIME32: अणु
		काष्ठा v4l2_event_समय32 *ev32 = arg;
		काष्ठा v4l2_event ev = अणु पूर्ण;

		अगर (!(sd->flags & V4L2_SUBDEV_FL_HAS_EVENTS))
			वापस -ENOIOCTLCMD;

		rval = v4l2_event_dequeue(vfh, &ev, file->f_flags & O_NONBLOCK);

		*ev32 = (काष्ठा v4l2_event_समय32) अणु
			.type		= ev.type,
			.pending	= ev.pending,
			.sequence	= ev.sequence,
			.बारtamp.tv_sec  = ev.बारtamp.tv_sec,
			.बारtamp.tv_nsec = ev.बारtamp.tv_nsec,
			.id		= ev.id,
		पूर्ण;

		स_नकल(&ev32->u, &ev.u, माप(ev.u));
		स_नकल(&ev32->reserved, &ev.reserved, माप(ev.reserved));

		वापस rval;
	पूर्ण

	हाल VIDIOC_SUBSCRIBE_EVENT:
		वापस v4l2_subdev_call(sd, core, subscribe_event, vfh, arg);

	हाल VIDIOC_UNSUBSCRIBE_EVENT:
		वापस v4l2_subdev_call(sd, core, unsubscribe_event, vfh, arg);

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	हाल VIDIOC_DBG_G_REGISTER:
	अणु
		काष्ठा v4l2_dbg_रेजिस्टर *p = arg;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		वापस v4l2_subdev_call(sd, core, g_रेजिस्टर, p);
	पूर्ण
	हाल VIDIOC_DBG_S_REGISTER:
	अणु
		काष्ठा v4l2_dbg_रेजिस्टर *p = arg;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		वापस v4l2_subdev_call(sd, core, s_रेजिस्टर, p);
	पूर्ण
	हाल VIDIOC_DBG_G_CHIP_INFO:
	अणु
		काष्ठा v4l2_dbg_chip_info *p = arg;

		अगर (p->match.type != V4L2_CHIP_MATCH_SUBDEV || p->match.addr)
			वापस -EINVAL;
		अगर (sd->ops->core && sd->ops->core->s_रेजिस्टर)
			p->flags |= V4L2_CHIP_FL_WRITABLE;
		अगर (sd->ops->core && sd->ops->core->g_रेजिस्टर)
			p->flags |= V4L2_CHIP_FL_READABLE;
		strscpy(p->name, sd->name, माप(p->name));
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	हाल VIDIOC_LOG_STATUS: अणु
		पूर्णांक ret;

		pr_info("%s: =================  START STATUS  =================\n",
			sd->name);
		ret = v4l2_subdev_call(sd, core, log_status);
		pr_info("%s: ==================  END STATUS  ==================\n",
			sd->name);
		वापस ret;
	पूर्ण

	हाल VIDIOC_SUBDEV_G_FMT: अणु
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat = arg;

		स_रखो(क्रमmat->reserved, 0, माप(क्रमmat->reserved));
		स_रखो(क्रमmat->क्रमmat.reserved, 0, माप(क्रमmat->क्रमmat.reserved));
		वापस v4l2_subdev_call(sd, pad, get_fmt, subdev_fh->pad, क्रमmat);
	पूर्ण

	हाल VIDIOC_SUBDEV_S_FMT: अणु
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat = arg;

		अगर (क्रमmat->which != V4L2_SUBDEV_FORMAT_TRY && ro_subdev)
			वापस -EPERM;

		स_रखो(क्रमmat->reserved, 0, माप(क्रमmat->reserved));
		स_रखो(क्रमmat->क्रमmat.reserved, 0, माप(क्रमmat->क्रमmat.reserved));
		वापस v4l2_subdev_call(sd, pad, set_fmt, subdev_fh->pad, क्रमmat);
	पूर्ण

	हाल VIDIOC_SUBDEV_G_CROP: अणु
		काष्ठा v4l2_subdev_crop *crop = arg;
		काष्ठा v4l2_subdev_selection sel;

		स_रखो(crop->reserved, 0, माप(crop->reserved));
		स_रखो(&sel, 0, माप(sel));
		sel.which = crop->which;
		sel.pad = crop->pad;
		sel.target = V4L2_SEL_TGT_CROP;

		rval = v4l2_subdev_call(
			sd, pad, get_selection, subdev_fh->pad, &sel);

		crop->rect = sel.r;

		वापस rval;
	पूर्ण

	हाल VIDIOC_SUBDEV_S_CROP: अणु
		काष्ठा v4l2_subdev_crop *crop = arg;
		काष्ठा v4l2_subdev_selection sel;

		अगर (crop->which != V4L2_SUBDEV_FORMAT_TRY && ro_subdev)
			वापस -EPERM;

		स_रखो(crop->reserved, 0, माप(crop->reserved));
		स_रखो(&sel, 0, माप(sel));
		sel.which = crop->which;
		sel.pad = crop->pad;
		sel.target = V4L2_SEL_TGT_CROP;
		sel.r = crop->rect;

		rval = v4l2_subdev_call(
			sd, pad, set_selection, subdev_fh->pad, &sel);

		crop->rect = sel.r;

		वापस rval;
	पूर्ण

	हाल VIDIOC_SUBDEV_ENUM_MBUS_CODE: अणु
		काष्ठा v4l2_subdev_mbus_code_क्रमागत *code = arg;

		स_रखो(code->reserved, 0, माप(code->reserved));
		वापस v4l2_subdev_call(sd, pad, क्रमागत_mbus_code, subdev_fh->pad,
					code);
	पूर्ण

	हाल VIDIOC_SUBDEV_ENUM_FRAME_SIZE: अणु
		काष्ठा v4l2_subdev_frame_size_क्रमागत *fse = arg;

		स_रखो(fse->reserved, 0, माप(fse->reserved));
		वापस v4l2_subdev_call(sd, pad, क्रमागत_frame_size, subdev_fh->pad,
					fse);
	पूर्ण

	हाल VIDIOC_SUBDEV_G_FRAME_INTERVAL: अणु
		काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi = arg;

		स_रखो(fi->reserved, 0, माप(fi->reserved));
		वापस v4l2_subdev_call(sd, video, g_frame_पूर्णांकerval, arg);
	पूर्ण

	हाल VIDIOC_SUBDEV_S_FRAME_INTERVAL: अणु
		काष्ठा v4l2_subdev_frame_पूर्णांकerval *fi = arg;

		अगर (ro_subdev)
			वापस -EPERM;

		स_रखो(fi->reserved, 0, माप(fi->reserved));
		वापस v4l2_subdev_call(sd, video, s_frame_पूर्णांकerval, arg);
	पूर्ण

	हाल VIDIOC_SUBDEV_ENUM_FRAME_INTERVAL: अणु
		काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie = arg;

		स_रखो(fie->reserved, 0, माप(fie->reserved));
		वापस v4l2_subdev_call(sd, pad, क्रमागत_frame_पूर्णांकerval, subdev_fh->pad,
					fie);
	पूर्ण

	हाल VIDIOC_SUBDEV_G_SELECTION: अणु
		काष्ठा v4l2_subdev_selection *sel = arg;

		स_रखो(sel->reserved, 0, माप(sel->reserved));
		वापस v4l2_subdev_call(
			sd, pad, get_selection, subdev_fh->pad, sel);
	पूर्ण

	हाल VIDIOC_SUBDEV_S_SELECTION: अणु
		काष्ठा v4l2_subdev_selection *sel = arg;

		अगर (sel->which != V4L2_SUBDEV_FORMAT_TRY && ro_subdev)
			वापस -EPERM;

		स_रखो(sel->reserved, 0, माप(sel->reserved));
		वापस v4l2_subdev_call(
			sd, pad, set_selection, subdev_fh->pad, sel);
	पूर्ण

	हाल VIDIOC_G_EDID: अणु
		काष्ठा v4l2_subdev_edid *edid = arg;

		वापस v4l2_subdev_call(sd, pad, get_edid, edid);
	पूर्ण

	हाल VIDIOC_S_EDID: अणु
		काष्ठा v4l2_subdev_edid *edid = arg;

		वापस v4l2_subdev_call(sd, pad, set_edid, edid);
	पूर्ण

	हाल VIDIOC_SUBDEV_DV_TIMINGS_CAP: अणु
		काष्ठा v4l2_dv_timings_cap *cap = arg;

		वापस v4l2_subdev_call(sd, pad, dv_timings_cap, cap);
	पूर्ण

	हाल VIDIOC_SUBDEV_ENUM_DV_TIMINGS: अणु
		काष्ठा v4l2_क्रमागत_dv_timings *dvt = arg;

		वापस v4l2_subdev_call(sd, pad, क्रमागत_dv_timings, dvt);
	पूर्ण

	हाल VIDIOC_SUBDEV_QUERY_DV_TIMINGS:
		वापस v4l2_subdev_call(sd, video, query_dv_timings, arg);

	हाल VIDIOC_SUBDEV_G_DV_TIMINGS:
		वापस v4l2_subdev_call(sd, video, g_dv_timings, arg);

	हाल VIDIOC_SUBDEV_S_DV_TIMINGS:
		अगर (ro_subdev)
			वापस -EPERM;

		वापस v4l2_subdev_call(sd, video, s_dv_timings, arg);

	हाल VIDIOC_SUBDEV_G_STD:
		वापस v4l2_subdev_call(sd, video, g_std, arg);

	हाल VIDIOC_SUBDEV_S_STD: अणु
		v4l2_std_id *std = arg;

		अगर (ro_subdev)
			वापस -EPERM;

		वापस v4l2_subdev_call(sd, video, s_std, *std);
	पूर्ण

	हाल VIDIOC_SUBDEV_ENUMSTD: अणु
		काष्ठा v4l2_standard *p = arg;
		v4l2_std_id id;

		अगर (v4l2_subdev_call(sd, video, g_tvnorms, &id))
			वापस -EINVAL;

		वापस v4l_video_std_क्रमागतstd(p, id);
	पूर्ण

	हाल VIDIOC_SUBDEV_QUERYSTD:
		वापस v4l2_subdev_call(sd, video, querystd, arg);

	शेष:
		वापस v4l2_subdev_call(sd, core, ioctl, cmd, arg);
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ subdev_करो_ioctl_lock(काष्ठा file *file, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा mutex *lock = vdev->lock;
	दीर्घ ret = -ENODEV;

	अगर (lock && mutex_lock_पूर्णांकerruptible(lock))
		वापस -ERESTARTSYS;
	अगर (video_is_रेजिस्टरed(vdev))
		ret = subdev_करो_ioctl(file, cmd, arg);
	अगर (lock)
		mutex_unlock(lock);
	वापस ret;
पूर्ण

अटल दीर्घ subdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
	अचिन्हित दीर्घ arg)
अणु
	वापस video_usercopy(file, cmd, arg, subdev_करो_ioctl_lock);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ subdev_compat_ioctl32(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
	अचिन्हित दीर्घ arg)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा v4l2_subdev *sd = vdev_to_v4l2_subdev(vdev);

	वापस v4l2_subdev_call(sd, core, compat_ioctl32, cmd, arg);
पूर्ण
#पूर्ण_अगर

#अन्यथा /* CONFIG_VIDEO_V4L2_SUBDEV_API */
अटल दीर्घ subdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	वापस -ENODEV;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ subdev_compat_ioctl32(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ arg)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_VIDEO_V4L2_SUBDEV_API */

अटल __poll_t subdev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा v4l2_subdev *sd = vdev_to_v4l2_subdev(vdev);
	काष्ठा v4l2_fh *fh = file->निजी_data;

	अगर (!(sd->flags & V4L2_SUBDEV_FL_HAS_EVENTS))
		वापस EPOLLERR;

	poll_रुको(file, &fh->रुको, रुको);

	अगर (v4l2_event_pending(fh))
		वापस EPOLLPRI;

	वापस 0;
पूर्ण

स्थिर काष्ठा v4l2_file_operations v4l2_subdev_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = subdev_खोलो,
	.unlocked_ioctl = subdev_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl32 = subdev_compat_ioctl32,
#पूर्ण_अगर
	.release = subdev_बंद,
	.poll = subdev_poll,
पूर्ण;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER

पूर्णांक v4l2_subdev_get_fwnode_pad_1_to_1(काष्ठा media_entity *entity,
				      काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा v4l2_subdev *sd;

	अगर (!is_media_entity_v4l2_subdev(entity))
		वापस -EINVAL;

	sd = media_entity_to_v4l2_subdev(entity);

	fwnode = fwnode_graph_get_port_parent(endpoपूर्णांक->local_fwnode);
	fwnode_handle_put(fwnode);

	अगर (dev_fwnode(sd->dev) == fwnode)
		वापस endpoपूर्णांक->port;

	वापस -ENXIO;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_subdev_get_fwnode_pad_1_to_1);

पूर्णांक v4l2_subdev_link_validate_शेष(काष्ठा v4l2_subdev *sd,
				      काष्ठा media_link *link,
				      काष्ठा v4l2_subdev_क्रमmat *source_fmt,
				      काष्ठा v4l2_subdev_क्रमmat *sink_fmt)
अणु
	bool pass = true;

	/* The width, height and code must match. */
	अगर (source_fmt->क्रमmat.width != sink_fmt->क्रमmat.width) अणु
		dev_dbg(sd->entity.graph_obj.mdev->dev,
			"%s: width does not match (source %u, sink %u)\n",
			__func__,
			source_fmt->क्रमmat.width, sink_fmt->क्रमmat.width);
		pass = false;
	पूर्ण

	अगर (source_fmt->क्रमmat.height != sink_fmt->क्रमmat.height) अणु
		dev_dbg(sd->entity.graph_obj.mdev->dev,
			"%s: height does not match (source %u, sink %u)\n",
			__func__,
			source_fmt->क्रमmat.height, sink_fmt->क्रमmat.height);
		pass = false;
	पूर्ण

	अगर (source_fmt->क्रमmat.code != sink_fmt->क्रमmat.code) अणु
		dev_dbg(sd->entity.graph_obj.mdev->dev,
			"%s: media bus code does not match (source 0x%8.8x, sink 0x%8.8x)\n",
			__func__,
			source_fmt->क्रमmat.code, sink_fmt->क्रमmat.code);
		pass = false;
	पूर्ण

	/* The field order must match, or the sink field order must be NONE
	 * to support पूर्णांकerlaced hardware connected to bridges that support
	 * progressive क्रमmats only.
	 */
	अगर (source_fmt->क्रमmat.field != sink_fmt->क्रमmat.field &&
	    sink_fmt->क्रमmat.field != V4L2_FIELD_NONE) अणु
		dev_dbg(sd->entity.graph_obj.mdev->dev,
			"%s: field does not match (source %u, sink %u)\n",
			__func__,
			source_fmt->क्रमmat.field, sink_fmt->क्रमmat.field);
		pass = false;
	पूर्ण

	अगर (pass)
		वापस 0;

	dev_dbg(sd->entity.graph_obj.mdev->dev,
		"%s: link was \"%s\":%u -> \"%s\":%u\n", __func__,
		link->source->entity->name, link->source->index,
		link->sink->entity->name, link->sink->index);

	वापस -EPIPE;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_subdev_link_validate_शेष);

अटल पूर्णांक
v4l2_subdev_link_validate_get_क्रमmat(काष्ठा media_pad *pad,
				     काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	अगर (is_media_entity_v4l2_subdev(pad->entity)) अणु
		काष्ठा v4l2_subdev *sd =
			media_entity_to_v4l2_subdev(pad->entity);

		fmt->which = V4L2_SUBDEV_FORMAT_ACTIVE;
		fmt->pad = pad->index;
		वापस v4l2_subdev_call(sd, pad, get_fmt, शून्य, fmt);
	पूर्ण

	WARN(pad->entity->function != MEDIA_ENT_F_IO_V4L,
	     "Driver bug! Wrong media entity type 0x%08x, entity %s\n",
	     pad->entity->function, pad->entity->name);

	वापस -EINVAL;
पूर्ण

पूर्णांक v4l2_subdev_link_validate(काष्ठा media_link *link)
अणु
	काष्ठा v4l2_subdev *sink;
	काष्ठा v4l2_subdev_क्रमmat sink_fmt, source_fmt;
	पूर्णांक rval;

	rval = v4l2_subdev_link_validate_get_क्रमmat(
		link->source, &source_fmt);
	अगर (rval < 0)
		वापस 0;

	rval = v4l2_subdev_link_validate_get_क्रमmat(
		link->sink, &sink_fmt);
	अगर (rval < 0)
		वापस 0;

	sink = media_entity_to_v4l2_subdev(link->sink->entity);

	rval = v4l2_subdev_call(sink, pad, link_validate, link,
				&source_fmt, &sink_fmt);
	अगर (rval != -ENOIOCTLCMD)
		वापस rval;

	वापस v4l2_subdev_link_validate_शेष(
		sink, link, &source_fmt, &sink_fmt);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_subdev_link_validate);

काष्ठा v4l2_subdev_pad_config *
v4l2_subdev_alloc_pad_config(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा v4l2_subdev_pad_config *cfg;
	पूर्णांक ret;

	अगर (!sd->entity.num_pads)
		वापस शून्य;

	cfg = kvदो_स्मृति_array(sd->entity.num_pads, माप(*cfg),
			     GFP_KERNEL | __GFP_ZERO);
	अगर (!cfg)
		वापस शून्य;

	ret = v4l2_subdev_call(sd, pad, init_cfg, cfg);
	अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
		kvमुक्त(cfg);
		वापस शून्य;
	पूर्ण

	वापस cfg;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_subdev_alloc_pad_config);

व्योम v4l2_subdev_मुक्त_pad_config(काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	kvमुक्त(cfg);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_subdev_मुक्त_pad_config);
#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER */

व्योम v4l2_subdev_init(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_subdev_ops *ops)
अणु
	INIT_LIST_HEAD(&sd->list);
	BUG_ON(!ops);
	sd->ops = ops;
	sd->v4l2_dev = शून्य;
	sd->flags = 0;
	sd->name[0] = '\0';
	sd->grp_id = 0;
	sd->dev_priv = शून्य;
	sd->host_priv = शून्य;
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	sd->entity.name = sd->name;
	sd->entity.obj_type = MEDIA_ENTITY_TYPE_V4L2_SUBDEV;
	sd->entity.function = MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN;
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(v4l2_subdev_init);

व्योम v4l2_subdev_notअगरy_event(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_event *ev)
अणु
	v4l2_event_queue(sd->devnode, ev);
	v4l2_subdev_notअगरy(sd, V4L2_DEVICE_NOTIFY_EVENT, (व्योम *)ev);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_subdev_notअगरy_event);
