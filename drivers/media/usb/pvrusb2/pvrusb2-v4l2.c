<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश "pvrusb2-context.h"
#समावेश "pvrusb2-hdw.h"
#समावेश "pvrusb2.h"
#समावेश "pvrusb2-debug.h"
#समावेश "pvrusb2-v4l2.h"
#समावेश "pvrusb2-ioread.h"
#समावेश <linux/videodev2.h>
#समावेश <linux/module.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>

काष्ठा pvr2_v4l2_dev;
काष्ठा pvr2_v4l2_fh;
काष्ठा pvr2_v4l2;

काष्ठा pvr2_v4l2_dev अणु
	काष्ठा video_device devbase; /* MUST be first! */
	काष्ठा pvr2_v4l2 *v4lp;
	काष्ठा pvr2_context_stream *stream;
	/* Inक्रमmation about this device: */
	क्रमागत pvr2_config config; /* Expected stream क्रमmat */
	पूर्णांक v4l_type; /* V4L defined type क्रम this device node */
	क्रमागत pvr2_v4l_type minor_type; /* pvr2-understood minor device type */
पूर्ण;

काष्ठा pvr2_v4l2_fh अणु
	काष्ठा v4l2_fh fh;
	काष्ठा pvr2_channel channel;
	काष्ठा pvr2_v4l2_dev *pdi;
	काष्ठा pvr2_ioपढ़ो *rhp;
	काष्ठा file *file;
	रुको_queue_head_t रुको_data;
	पूर्णांक fw_mode_flag;
	/* Map contiguous ordinal value to input id */
	अचिन्हित अक्षर *input_map;
	अचिन्हित पूर्णांक input_cnt;
पूर्ण;

काष्ठा pvr2_v4l2 अणु
	काष्ठा pvr2_channel channel;

	/* streams - Note that these must be separately, inभागidually,
	 * allocated poपूर्णांकers.  This is because the v4l core is going to
	 * manage their deletion - separately, inभागidually...  */
	काष्ठा pvr2_v4l2_dev *dev_video;
	काष्ठा pvr2_v4l2_dev *dev_radio;
पूर्ण;

अटल पूर्णांक video_nr[PVR_NUM] = अणु[0 ... PVR_NUM-1] = -1पूर्ण;
module_param_array(video_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(video_nr, "Offset for device's video dev minor");
अटल पूर्णांक radio_nr[PVR_NUM] = अणु[0 ... PVR_NUM-1] = -1पूर्ण;
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(radio_nr, "Offset for device's radio dev minor");
अटल पूर्णांक vbi_nr[PVR_NUM] = अणु[0 ... PVR_NUM-1] = -1पूर्ण;
module_param_array(vbi_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(vbi_nr, "Offset for device's vbi dev minor");

#घोषणा PVR_FORMAT_PIX  0
#घोषणा PVR_FORMAT_VBI  1

अटल काष्ठा v4l2_क्रमmat pvr_क्रमmat [] = अणु
	[PVR_FORMAT_PIX] = अणु
		.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE,
		.fmt    = अणु
			.pix        = अणु
				.width          = 720,
				.height         = 576,
				.pixelक्रमmat    = V4L2_PIX_FMT_MPEG,
				.field          = V4L2_FIELD_INTERLACED,
				/* FIXME : Don't know what to put here... */
				.sizeimage      = 32 * 1024,
			पूर्ण
		पूर्ण
	पूर्ण,
	[PVR_FORMAT_VBI] = अणु
		.type   = V4L2_BUF_TYPE_VBI_CAPTURE,
		.fmt    = अणु
			.vbi        = अणु
				.sampling_rate = 27000000,
				.offset = 248,
				.samples_per_line = 1443,
				.sample_क्रमmat = V4L2_PIX_FMT_GREY,
				.start = अणु 0, 0 पूर्ण,
				.count = अणु 0, 0 पूर्ण,
				.flags = 0,
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण;



/*
 * This is part of Video 4 Linux API. These procedures handle ioctl() calls.
 */
अटल पूर्णांक pvr2_querycap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;

	strscpy(cap->driver, "pvrusb2", माप(cap->driver));
	strscpy(cap->bus_info, pvr2_hdw_get_bus_info(hdw),
		माप(cap->bus_info));
	strscpy(cap->card, pvr2_hdw_get_desc(hdw), माप(cap->card));
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TUNER |
			    V4L2_CAP_AUDIO | V4L2_CAP_RADIO |
			    V4L2_CAP_READWRITE | V4L2_CAP_DEVICE_CAPS;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक val = 0;
	पूर्णांक ret;

	ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_STDCUR), &val);
	*std = val;
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id std)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक ret;

	ret = pvr2_ctrl_set_value(
		pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_STDCUR), std);
	pvr2_hdw_commit_ctl(hdw);
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक val = 0;
	पूर्णांक ret;

	ret = pvr2_ctrl_get_value(
		pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_STDDETECT), &val);
	*std = val;
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_क्रमागत_input(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_input *vi)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	काष्ठा pvr2_ctrl *cptr;
	काष्ठा v4l2_input पंचांगp;
	अचिन्हित पूर्णांक cnt;
	पूर्णांक val;

	cptr = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_INPUT);

	स_रखो(&पंचांगp, 0, माप(पंचांगp));
	पंचांगp.index = vi->index;
	अगर (vi->index >= fh->input_cnt)
		वापस -EINVAL;
	val = fh->input_map[vi->index];
	चयन (val) अणु
	हाल PVR2_CVAL_INPUT_TV:
	हाल PVR2_CVAL_INPUT_DTV:
	हाल PVR2_CVAL_INPUT_RADIO:
		पंचांगp.type = V4L2_INPUT_TYPE_TUNER;
		अवरोध;
	हाल PVR2_CVAL_INPUT_SVIDEO:
	हाल PVR2_CVAL_INPUT_COMPOSITE:
		पंचांगp.type = V4L2_INPUT_TYPE_CAMERA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cnt = 0;
	pvr2_ctrl_get_valname(cptr, val,
			पंचांगp.name, माप(पंचांगp.name) - 1, &cnt);
	पंचांगp.name[cnt] = 0;

	/* Don't bother with audioset, since this driver currently
	   always चयनes the audio whenever the video is
	   चयनed. */

	/* Handling std is a tougher problem.  It करोesn't make
	   sense in हालs where a device might be multi-standard.
	   We could just copy out the current value क्रम the
	   standard, but it can change over समय.  For now just
	   leave it zero. */
	*vi = पंचांगp;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	अचिन्हित पूर्णांक idx;
	काष्ठा pvr2_ctrl *cptr;
	पूर्णांक val;
	पूर्णांक ret;

	cptr = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_INPUT);
	val = 0;
	ret = pvr2_ctrl_get_value(cptr, &val);
	*i = 0;
	क्रम (idx = 0; idx < fh->input_cnt; idx++) अणु
		अगर (fh->input_map[idx] == val) अणु
			*i = idx;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक inp)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक ret;

	अगर (inp >= fh->input_cnt)
		वापस -EINVAL;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_INPUT),
			fh->input_map[inp]);
	pvr2_hdw_commit_ctl(hdw);
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_क्रमागतaudio(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_audio *vin)
अणु
	/* pkt: FIXME: We are वापसing one "fake" input here
	   which could very well be called "whatever_we_like".
	   This is क्रम apps that want to see an audio input
	   just to feel comक्रमtable, as well as to test अगर
	   it can करो stereo or sth. There is actually no guarantee
	   that the actual audio input cannot change behind the app's
	   back, but most applications should not mind that either.

	   Hopefully, mplayer people will work with us on this (this
	   whole mess is to support mplayer pvr://), or Hans will come
	   up with a more standard way to say "we have inमाला_दो but we
	   करोn 't want you to change them independent of video" which
	   will sort this mess.
	 */

	अगर (vin->index > 0)
		वापस -EINVAL;
	strscpy(vin->name, "PVRUSB2 Audio", माप(vin->name));
	vin->capability = V4L2_AUDCAP_STEREO;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_g_audio(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_audio *vin)
अणु
	/* pkt: FIXME: see above comment (VIDIOC_ENUMAUDIO) */
	vin->index = 0;
	strscpy(vin->name, "PVRUSB2 Audio", माप(vin->name));
	vin->capability = V4L2_AUDCAP_STEREO;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_s_audio(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_audio *vout)
अणु
	अगर (vout->index)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;

	अगर (vt->index != 0)
		वापस -EINVAL; /* Only answer क्रम the 1st tuner */

	pvr2_hdw_execute_tuner_poll(hdw);
	वापस pvr2_hdw_get_tuner_status(hdw, vt);
पूर्ण

अटल पूर्णांक pvr2_s_tuner(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक ret;

	अगर (vt->index != 0)
		वापस -EINVAL;

	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_AUDIOMODE),
			vt->audmode);
	pvr2_hdw_commit_ctl(hdw);
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_s_frequency(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	अचिन्हित दीर्घ fv;
	काष्ठा v4l2_tuner vt;
	पूर्णांक cur_input;
	काष्ठा pvr2_ctrl *ctrlp;
	पूर्णांक ret;

	ret = pvr2_hdw_get_tuner_status(hdw, &vt);
	अगर (ret != 0)
		वापस ret;
	ctrlp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_INPUT);
	ret = pvr2_ctrl_get_value(ctrlp, &cur_input);
	अगर (ret != 0)
		वापस ret;
	अगर (vf->type == V4L2_TUNER_RADIO) अणु
		अगर (cur_input != PVR2_CVAL_INPUT_RADIO)
			pvr2_ctrl_set_value(ctrlp, PVR2_CVAL_INPUT_RADIO);
	पूर्ण अन्यथा अणु
		अगर (cur_input == PVR2_CVAL_INPUT_RADIO)
			pvr2_ctrl_set_value(ctrlp, PVR2_CVAL_INPUT_TV);
	पूर्ण
	fv = vf->frequency;
	अगर (vt.capability & V4L2_TUNER_CAP_LOW)
		fv = (fv * 125) / 2;
	अन्यथा
		fv = fv * 62500;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_FREQUENCY),fv);
	pvr2_hdw_commit_ctl(hdw);
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_g_frequency(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक val = 0;
	पूर्णांक cur_input;
	काष्ठा v4l2_tuner vt;
	पूर्णांक ret;

	ret = pvr2_hdw_get_tuner_status(hdw, &vt);
	अगर (ret != 0)
		वापस ret;
	ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_FREQUENCY),
			&val);
	अगर (ret != 0)
		वापस ret;
	pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_INPUT),
			&cur_input);
	अगर (cur_input == PVR2_CVAL_INPUT_RADIO)
		vf->type = V4L2_TUNER_RADIO;
	अन्यथा
		vf->type = V4L2_TUNER_ANALOG_TV;
	अगर (vt.capability & V4L2_TUNER_CAP_LOW)
		val = (val * 2) / 125;
	अन्यथा
		val /= 62500;
	vf->frequency = val;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_fmtdesc *fd)
अणु
	/* Only one क्रमmat is supported: MPEG. */
	अगर (fd->index)
		वापस -EINVAL;

	fd->pixelक्रमmat = V4L2_PIX_FMT_MPEG;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *vf)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक val;

	स_नकल(vf, &pvr_क्रमmat[PVR_FORMAT_PIX], माप(काष्ठा v4l2_क्रमmat));
	val = 0;
	pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_HRES),
			&val);
	vf->fmt.pix.width = val;
	val = 0;
	pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_VRES),
			&val);
	vf->fmt.pix.height = val;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *vf)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक lmin, lmax, ldef;
	काष्ठा pvr2_ctrl *hcp, *vcp;
	पूर्णांक h = vf->fmt.pix.height;
	पूर्णांक w = vf->fmt.pix.width;

	hcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_HRES);
	vcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_VRES);

	lmin = pvr2_ctrl_get_min(hcp);
	lmax = pvr2_ctrl_get_max(hcp);
	pvr2_ctrl_get_def(hcp, &ldef);
	अगर (w == -1)
		w = ldef;
	अन्यथा अगर (w < lmin)
		w = lmin;
	अन्यथा अगर (w > lmax)
		w = lmax;
	lmin = pvr2_ctrl_get_min(vcp);
	lmax = pvr2_ctrl_get_max(vcp);
	pvr2_ctrl_get_def(vcp, &ldef);
	अगर (h == -1)
		h = ldef;
	अन्यथा अगर (h < lmin)
		h = lmin;
	अन्यथा अगर (h > lmax)
		h = lmax;

	स_नकल(vf, &pvr_क्रमmat[PVR_FORMAT_PIX],
			माप(काष्ठा v4l2_क्रमmat));
	vf->fmt.pix.width = w;
	vf->fmt.pix.height = h;
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *vf)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	काष्ठा pvr2_ctrl *hcp, *vcp;
	पूर्णांक ret = pvr2_try_fmt_vid_cap(file, fh, vf);

	अगर (ret)
		वापस ret;
	hcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_HRES);
	vcp = pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_VRES);
	pvr2_ctrl_set_value(hcp, vf->fmt.pix.width);
	pvr2_ctrl_set_value(vcp, vf->fmt.pix.height);
	pvr2_hdw_commit_ctl(hdw);
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_streamon(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	काष्ठा pvr2_v4l2_dev *pdi = fh->pdi;
	पूर्णांक ret;

	अगर (!fh->pdi->stream) अणु
		/* No stream defined क्रम this node.  This means
		   that we're not currently allowed to stream from
		   this node. */
		वापस -EPERM;
	पूर्ण
	ret = pvr2_hdw_set_stream_type(hdw, pdi->config);
	अगर (ret < 0)
		वापस ret;
	वापस pvr2_hdw_set_streaming(hdw, !0);
पूर्ण

अटल पूर्णांक pvr2_streamoff(काष्ठा file *file, व्योम *priv, क्रमागत v4l2_buf_type i)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;

	अगर (!fh->pdi->stream) अणु
		/* No stream defined क्रम this node.  This means
		   that we're not currently allowed to stream from
		   this node. */
		वापस -EPERM;
	पूर्ण
	वापस pvr2_hdw_set_streaming(hdw, 0);
पूर्ण

अटल पूर्णांक pvr2_queryctrl(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_queryctrl *vc)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	काष्ठा pvr2_ctrl *cptr;
	पूर्णांक val;

	अगर (vc->id & V4L2_CTRL_FLAG_NEXT_CTRL) अणु
		cptr = pvr2_hdw_get_ctrl_nextv4l(
				hdw, (vc->id & ~V4L2_CTRL_FLAG_NEXT_CTRL));
		अगर (cptr)
			vc->id = pvr2_ctrl_get_v4lid(cptr);
	पूर्ण अन्यथा अणु
		cptr = pvr2_hdw_get_ctrl_v4l(hdw, vc->id);
	पूर्ण
	अगर (!cptr) अणु
		pvr2_trace(PVR2_TRACE_V4LIOCTL,
				"QUERYCTRL id=0x%x not implemented here",
				vc->id);
		वापस -EINVAL;
	पूर्ण

	pvr2_trace(PVR2_TRACE_V4LIOCTL,
			"QUERYCTRL id=0x%x mapping name=%s (%s)",
			vc->id, pvr2_ctrl_get_name(cptr),
			pvr2_ctrl_get_desc(cptr));
	strscpy(vc->name, pvr2_ctrl_get_desc(cptr), माप(vc->name));
	vc->flags = pvr2_ctrl_get_v4lflags(cptr);
	pvr2_ctrl_get_def(cptr, &val);
	vc->शेष_value = val;
	चयन (pvr2_ctrl_get_type(cptr)) अणु
	हाल pvr2_ctl_क्रमागत:
		vc->type = V4L2_CTRL_TYPE_MENU;
		vc->minimum = 0;
		vc->maximum = pvr2_ctrl_get_cnt(cptr) - 1;
		vc->step = 1;
		अवरोध;
	हाल pvr2_ctl_bool:
		vc->type = V4L2_CTRL_TYPE_BOOLEAN;
		vc->minimum = 0;
		vc->maximum = 1;
		vc->step = 1;
		अवरोध;
	हाल pvr2_ctl_पूर्णांक:
		vc->type = V4L2_CTRL_TYPE_INTEGER;
		vc->minimum = pvr2_ctrl_get_min(cptr);
		vc->maximum = pvr2_ctrl_get_max(cptr);
		vc->step = 1;
		अवरोध;
	शेष:
		pvr2_trace(PVR2_TRACE_V4LIOCTL,
				"QUERYCTRL id=0x%x name=%s not mappable",
				vc->id, pvr2_ctrl_get_name(cptr));
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_querymenu(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_querymenu *vm)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	अचिन्हित पूर्णांक cnt = 0;
	पूर्णांक ret;

	ret = pvr2_ctrl_get_valname(pvr2_hdw_get_ctrl_v4l(hdw, vm->id),
			vm->index,
			vm->name, माप(vm->name) - 1,
			&cnt);
	vm->name[cnt] = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_g_ctrl(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_control *vc)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक val = 0;
	पूर्णांक ret;

	ret = pvr2_ctrl_get_value(pvr2_hdw_get_ctrl_v4l(hdw, vc->id),
			&val);
	vc->value = val;
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_s_ctrl(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_control *vc)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक ret;

	ret = pvr2_ctrl_set_value(pvr2_hdw_get_ctrl_v4l(hdw, vc->id),
			vc->value);
	pvr2_hdw_commit_ctl(hdw);
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_g_ext_ctrls(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_ext_controls *ctls)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	काष्ठा v4l2_ext_control *ctrl;
	काष्ठा pvr2_ctrl *cptr;
	अचिन्हित पूर्णांक idx;
	पूर्णांक val;
	पूर्णांक ret;

	ret = 0;
	क्रम (idx = 0; idx < ctls->count; idx++) अणु
		ctrl = ctls->controls + idx;
		cptr = pvr2_hdw_get_ctrl_v4l(hdw, ctrl->id);
		अगर (cptr) अणु
			अगर (ctls->which == V4L2_CTRL_WHICH_DEF_VAL)
				pvr2_ctrl_get_def(cptr, &val);
			अन्यथा
				ret = pvr2_ctrl_get_value(cptr, &val);
		पूर्ण अन्यथा
			ret = -EINVAL;

		अगर (ret) अणु
			ctls->error_idx = idx;
			वापस ret;
		पूर्ण
		/* Ensure that अगर पढ़ो as a 64 bit value, the user
		   will still get a hopefully sane value */
		ctrl->value64 = 0;
		ctrl->value = val;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_s_ext_ctrls(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_ext_controls *ctls)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	काष्ठा v4l2_ext_control *ctrl;
	अचिन्हित पूर्णांक idx;
	पूर्णांक ret;

	/* Default value cannot be changed */
	अगर (ctls->which == V4L2_CTRL_WHICH_DEF_VAL)
		वापस -EINVAL;

	ret = 0;
	क्रम (idx = 0; idx < ctls->count; idx++) अणु
		ctrl = ctls->controls + idx;
		ret = pvr2_ctrl_set_value(
				pvr2_hdw_get_ctrl_v4l(hdw, ctrl->id),
				ctrl->value);
		अगर (ret) अणु
			ctls->error_idx = idx;
			जाओ commit;
		पूर्ण
	पूर्ण
commit:
	pvr2_hdw_commit_ctl(hdw);
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_try_ext_ctrls(काष्ठा file *file, व्योम *priv,
		काष्ठा v4l2_ext_controls *ctls)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	काष्ठा v4l2_ext_control *ctrl;
	काष्ठा pvr2_ctrl *pctl;
	अचिन्हित पूर्णांक idx;

	/* For the moment just validate that the requested control
	   actually exists. */
	क्रम (idx = 0; idx < ctls->count; idx++) अणु
		ctrl = ctls->controls + idx;
		pctl = pvr2_hdw_get_ctrl_v4l(hdw, ctrl->id);
		अगर (!pctl) अणु
			ctls->error_idx = idx;
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_g_pixelaspect(काष्ठा file *file, व्योम *priv,
			      पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	काष्ठा v4l2_cropcap cap = अणु .type = type पूर्ण;
	पूर्णांक ret;

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	ret = pvr2_hdw_get_cropcap(hdw, &cap);
	अगर (!ret)
		*f = cap.pixelaspect;
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_g_selection(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_selection *sel)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	काष्ठा v4l2_cropcap cap;
	पूर्णांक val = 0;
	पूर्णांक ret;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	cap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		ret = pvr2_ctrl_get_value(
			  pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPL), &val);
		अगर (ret != 0)
			वापस -EINVAL;
		sel->r.left = val;
		ret = pvr2_ctrl_get_value(
			  pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPT), &val);
		अगर (ret != 0)
			वापस -EINVAL;
		sel->r.top = val;
		ret = pvr2_ctrl_get_value(
			  pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPW), &val);
		अगर (ret != 0)
			वापस -EINVAL;
		sel->r.width = val;
		ret = pvr2_ctrl_get_value(
			  pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPH), &val);
		अगर (ret != 0)
			वापस -EINVAL;
		sel->r.height = val;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		ret = pvr2_hdw_get_cropcap(hdw, &cap);
		sel->r = cap.defrect;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		ret = pvr2_hdw_get_cropcap(hdw, &cap);
		sel->r = cap.bounds;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_s_selection(काष्ठा file *file, व्योम *priv,
			    काष्ठा v4l2_selection *sel)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	पूर्णांक ret;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
	    sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPL),
			sel->r.left);
	अगर (ret != 0)
		जाओ commit;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPT),
			sel->r.top);
	अगर (ret != 0)
		जाओ commit;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPW),
			sel->r.width);
	अगर (ret != 0)
		जाओ commit;
	ret = pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPH),
			sel->r.height);
commit:
	pvr2_hdw_commit_ctl(hdw);
	वापस ret;
पूर्ण

अटल पूर्णांक pvr2_log_status(काष्ठा file *file, व्योम *priv)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;

	pvr2_hdw_trigger_module_log(hdw);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops pvr2_ioctl_ops = अणु
	.vidioc_querycap		    = pvr2_querycap,
	.vidioc_s_audio			    = pvr2_s_audio,
	.vidioc_g_audio			    = pvr2_g_audio,
	.vidioc_क्रमागतaudio		    = pvr2_क्रमागतaudio,
	.vidioc_क्रमागत_input		    = pvr2_क्रमागत_input,
	.vidioc_g_pixelaspect		    = pvr2_g_pixelaspect,
	.vidioc_s_selection		    = pvr2_s_selection,
	.vidioc_g_selection		    = pvr2_g_selection,
	.vidioc_g_input			    = pvr2_g_input,
	.vidioc_s_input			    = pvr2_s_input,
	.vidioc_g_frequency		    = pvr2_g_frequency,
	.vidioc_s_frequency		    = pvr2_s_frequency,
	.vidioc_s_tuner			    = pvr2_s_tuner,
	.vidioc_g_tuner			    = pvr2_g_tuner,
	.vidioc_g_std			    = pvr2_g_std,
	.vidioc_s_std			    = pvr2_s_std,
	.vidioc_querystd		    = pvr2_querystd,
	.vidioc_log_status		    = pvr2_log_status,
	.vidioc_क्रमागत_fmt_vid_cap	    = pvr2_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		    = pvr2_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		    = pvr2_s_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		    = pvr2_try_fmt_vid_cap,
	.vidioc_streamon		    = pvr2_streamon,
	.vidioc_streamoff		    = pvr2_streamoff,
	.vidioc_queryctrl		    = pvr2_queryctrl,
	.vidioc_querymenu		    = pvr2_querymenu,
	.vidioc_g_ctrl			    = pvr2_g_ctrl,
	.vidioc_s_ctrl			    = pvr2_s_ctrl,
	.vidioc_g_ext_ctrls		    = pvr2_g_ext_ctrls,
	.vidioc_s_ext_ctrls		    = pvr2_s_ext_ctrls,
	.vidioc_try_ext_ctrls		    = pvr2_try_ext_ctrls,
पूर्ण;

अटल व्योम pvr2_v4l2_dev_destroy(काष्ठा pvr2_v4l2_dev *dip)
अणु
	काष्ठा pvr2_hdw *hdw = dip->v4lp->channel.mc_head->hdw;
	क्रमागत pvr2_config cfg = dip->config;
	अक्षर msg[80];
	अचिन्हित पूर्णांक mcnt;

	/* Conकाष्ठा the unregistration message *beक्रमe* we actually
	   perक्रमm the unregistration step.  By करोing it this way we करोn't
	   have to worry about potentially touching deleted resources. */
	mcnt = scnम_लिखो(msg, माप(msg) - 1,
			 "pvrusb2: unregistered device %s [%s]",
			 video_device_node_name(&dip->devbase),
			 pvr2_config_get_name(cfg));
	msg[mcnt] = 0;

	pvr2_hdw_v4l_store_minor_number(hdw,dip->minor_type,-1);

	/* Paranoia */
	dip->v4lp = शून्य;
	dip->stream = शून्य;

	/* Actual deallocation happens later when all पूर्णांकernal references
	   are gone. */
	video_unरेजिस्टर_device(&dip->devbase);

	pr_info("%s\n", msg);

पूर्ण


अटल व्योम pvr2_v4l2_dev_disassociate_parent(काष्ठा pvr2_v4l2_dev *dip)
अणु
	अगर (!dip) वापस;
	अगर (!dip->devbase.v4l2_dev->dev) वापस;
	dip->devbase.v4l2_dev->dev = शून्य;
	device_move(&dip->devbase.dev, शून्य, DPM_ORDER_NONE);
पूर्ण


अटल व्योम pvr2_v4l2_destroy_no_lock(काष्ठा pvr2_v4l2 *vp)
अणु
	अगर (vp->dev_video) अणु
		pvr2_v4l2_dev_destroy(vp->dev_video);
		vp->dev_video = शून्य;
	पूर्ण
	अगर (vp->dev_radio) अणु
		pvr2_v4l2_dev_destroy(vp->dev_radio);
		vp->dev_radio = शून्य;
	पूर्ण

	pvr2_trace(PVR2_TRACE_STRUCT,"Destroying pvr2_v4l2 id=%p",vp);
	pvr2_channel_करोne(&vp->channel);
	kमुक्त(vp);
पूर्ण


अटल व्योम pvr2_video_device_release(काष्ठा video_device *vdev)
अणु
	काष्ठा pvr2_v4l2_dev *dev;
	dev = container_of(vdev,काष्ठा pvr2_v4l2_dev,devbase);
	kमुक्त(dev);
पूर्ण


अटल व्योम pvr2_v4l2_पूर्णांकernal_check(काष्ठा pvr2_channel *chp)
अणु
	काष्ठा pvr2_v4l2 *vp;
	vp = container_of(chp,काष्ठा pvr2_v4l2,channel);
	अगर (!vp->channel.mc_head->disconnect_flag) वापस;
	pvr2_v4l2_dev_disassociate_parent(vp->dev_video);
	pvr2_v4l2_dev_disassociate_parent(vp->dev_radio);
	अगर (!list_empty(&vp->dev_video->devbase.fh_list) ||
	    (vp->dev_radio &&
	     !list_empty(&vp->dev_radio->devbase.fh_list))) अणु
		pvr2_trace(PVR2_TRACE_STRUCT,
			   "pvr2_v4l2 internal_check exit-empty id=%p", vp);
		वापस;
	पूर्ण
	pvr2_v4l2_destroy_no_lock(vp);
पूर्ण


अटल पूर्णांक pvr2_v4l2_release(काष्ठा file *file)
अणु
	काष्ठा pvr2_v4l2_fh *fhp = file->निजी_data;
	काष्ठा pvr2_v4l2 *vp = fhp->pdi->v4lp;
	काष्ठा pvr2_hdw *hdw = fhp->channel.mc_head->hdw;

	pvr2_trace(PVR2_TRACE_OPEN_CLOSE,"pvr2_v4l2_release");

	अगर (fhp->rhp) अणु
		काष्ठा pvr2_stream *sp;
		pvr2_hdw_set_streaming(hdw,0);
		sp = pvr2_ioपढ़ो_get_stream(fhp->rhp);
		अगर (sp) pvr2_stream_set_callback(sp,शून्य,शून्य);
		pvr2_ioपढ़ो_destroy(fhp->rhp);
		fhp->rhp = शून्य;
	पूर्ण

	v4l2_fh_del(&fhp->fh);
	v4l2_fh_निकास(&fhp->fh);
	file->निजी_data = शून्य;

	pvr2_channel_करोne(&fhp->channel);
	pvr2_trace(PVR2_TRACE_STRUCT,
		   "Destroying pvr_v4l2_fh id=%p",fhp);
	अगर (fhp->input_map) अणु
		kमुक्त(fhp->input_map);
		fhp->input_map = शून्य;
	पूर्ण
	kमुक्त(fhp);
	अगर (vp->channel.mc_head->disconnect_flag &&
	    list_empty(&vp->dev_video->devbase.fh_list) &&
	    (!vp->dev_radio ||
	     list_empty(&vp->dev_radio->devbase.fh_list))) अणु
		pvr2_v4l2_destroy_no_lock(vp);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक pvr2_v4l2_खोलो(काष्ठा file *file)
अणु
	काष्ठा pvr2_v4l2_dev *dip; /* Our own context poपूर्णांकer */
	काष्ठा pvr2_v4l2_fh *fhp;
	काष्ठा pvr2_v4l2 *vp;
	काष्ठा pvr2_hdw *hdw;
	अचिन्हित पूर्णांक input_mask = 0;
	अचिन्हित पूर्णांक input_cnt,idx;
	पूर्णांक ret = 0;

	dip = container_of(video_devdata(file),काष्ठा pvr2_v4l2_dev,devbase);

	vp = dip->v4lp;
	hdw = vp->channel.hdw;

	pvr2_trace(PVR2_TRACE_OPEN_CLOSE,"pvr2_v4l2_open");

	अगर (!pvr2_hdw_dev_ok(hdw)) अणु
		pvr2_trace(PVR2_TRACE_OPEN_CLOSE,
			   "pvr2_v4l2_open: hardware not ready");
		वापस -EIO;
	पूर्ण

	fhp = kzalloc(माप(*fhp),GFP_KERNEL);
	अगर (!fhp) अणु
		वापस -ENOMEM;
	पूर्ण

	v4l2_fh_init(&fhp->fh, &dip->devbase);
	init_रुकोqueue_head(&fhp->रुको_data);
	fhp->pdi = dip;

	pvr2_trace(PVR2_TRACE_STRUCT,"Creating pvr_v4l2_fh id=%p",fhp);
	pvr2_channel_init(&fhp->channel,vp->channel.mc_head);

	अगर (dip->v4l_type == VFL_TYPE_RADIO) अणु
		/* Opening device as a radio, legal input selection subset
		   is just the radio. */
		input_mask = (1 << PVR2_CVAL_INPUT_RADIO);
	पूर्ण अन्यथा अणु
		/* Opening the मुख्य V4L device, legal input selection
		   subset includes all analog inमाला_दो. */
		input_mask = ((1 << PVR2_CVAL_INPUT_RADIO) |
			      (1 << PVR2_CVAL_INPUT_TV) |
			      (1 << PVR2_CVAL_INPUT_COMPOSITE) |
			      (1 << PVR2_CVAL_INPUT_SVIDEO));
	पूर्ण
	ret = pvr2_channel_limit_inमाला_दो(&fhp->channel,input_mask);
	अगर (ret) अणु
		pvr2_channel_करोne(&fhp->channel);
		pvr2_trace(PVR2_TRACE_STRUCT,
			   "Destroying pvr_v4l2_fh id=%p (input mask error)",
			   fhp);
		v4l2_fh_निकास(&fhp->fh);
		kमुक्त(fhp);
		वापस ret;
	पूर्ण

	input_mask &= pvr2_hdw_get_input_available(hdw);
	input_cnt = 0;
	क्रम (idx = 0; idx < (माप(input_mask) << 3); idx++) अणु
		अगर (input_mask & (1UL << idx)) input_cnt++;
	पूर्ण
	fhp->input_cnt = input_cnt;
	fhp->input_map = kzalloc(input_cnt,GFP_KERNEL);
	अगर (!fhp->input_map) अणु
		pvr2_channel_करोne(&fhp->channel);
		pvr2_trace(PVR2_TRACE_STRUCT,
			   "Destroying pvr_v4l2_fh id=%p (input map failure)",
			   fhp);
		v4l2_fh_निकास(&fhp->fh);
		kमुक्त(fhp);
		वापस -ENOMEM;
	पूर्ण
	input_cnt = 0;
	क्रम (idx = 0; idx < (माप(input_mask) << 3); idx++) अणु
		अगर (!(input_mask & (1UL << idx))) जारी;
		fhp->input_map[input_cnt++] = idx;
	पूर्ण

	fhp->file = file;
	file->निजी_data = fhp;

	fhp->fw_mode_flag = pvr2_hdw_cpufw_get_enabled(hdw);
	v4l2_fh_add(&fhp->fh);

	वापस 0;
पूर्ण


अटल व्योम pvr2_v4l2_notअगरy(काष्ठा pvr2_v4l2_fh *fhp)
अणु
	wake_up(&fhp->रुको_data);
पूर्ण

अटल पूर्णांक pvr2_v4l2_iosetup(काष्ठा pvr2_v4l2_fh *fh)
अणु
	पूर्णांक ret;
	काष्ठा pvr2_stream *sp;
	काष्ठा pvr2_hdw *hdw;
	अगर (fh->rhp) वापस 0;

	अगर (!fh->pdi->stream) अणु
		/* No stream defined क्रम this node.  This means that we're
		   not currently allowed to stream from this node. */
		वापस -EPERM;
	पूर्ण

	/* First पढ़ो() attempt.  Try to claim the stream and start
	   it... */
	अगर ((ret = pvr2_channel_claim_stream(&fh->channel,
					     fh->pdi->stream)) != 0) अणु
		/* Someone अन्यथा must alपढ़ोy have it */
		वापस ret;
	पूर्ण

	fh->rhp = pvr2_channel_create_mpeg_stream(fh->pdi->stream);
	अगर (!fh->rhp) अणु
		pvr2_channel_claim_stream(&fh->channel,शून्य);
		वापस -ENOMEM;
	पूर्ण

	hdw = fh->channel.mc_head->hdw;
	sp = fh->pdi->stream->stream;
	pvr2_stream_set_callback(sp,(pvr2_stream_callback)pvr2_v4l2_notअगरy,fh);
	pvr2_hdw_set_stream_type(hdw,fh->pdi->config);
	अगर ((ret = pvr2_hdw_set_streaming(hdw,!0)) < 0) वापस ret;
	वापस pvr2_ioपढ़ो_set_enabled(fh->rhp,!0);
पूर्ण


अटल sमाप_प्रकार pvr2_v4l2_पढ़ो(काष्ठा file *file,
			      अक्षर __user *buff, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	पूर्णांक ret;

	अगर (fh->fw_mode_flag) अणु
		काष्ठा pvr2_hdw *hdw = fh->channel.mc_head->hdw;
		अक्षर *tbuf;
		पूर्णांक c1,c2;
		पूर्णांक tcnt = 0;
		अचिन्हित पूर्णांक offs = *ppos;

		tbuf = kदो_स्मृति(PAGE_SIZE,GFP_KERNEL);
		अगर (!tbuf) वापस -ENOMEM;

		जबतक (count) अणु
			c1 = count;
			अगर (c1 > PAGE_SIZE) c1 = PAGE_SIZE;
			c2 = pvr2_hdw_cpufw_get(hdw,offs,tbuf,c1);
			अगर (c2 < 0) अणु
				tcnt = c2;
				अवरोध;
			पूर्ण
			अगर (!c2) अवरोध;
			अगर (copy_to_user(buff,tbuf,c2)) अणु
				tcnt = -EFAULT;
				अवरोध;
			पूर्ण
			offs += c2;
			tcnt += c2;
			buff += c2;
			count -= c2;
			*ppos += c2;
		पूर्ण
		kमुक्त(tbuf);
		वापस tcnt;
	पूर्ण

	अगर (!fh->rhp) अणु
		ret = pvr2_v4l2_iosetup(fh);
		अगर (ret) अणु
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (;;) अणु
		ret = pvr2_ioपढ़ो_पढ़ो(fh->rhp,buff,count);
		अगर (ret >= 0) अवरोध;
		अगर (ret != -EAGAIN) अवरोध;
		अगर (file->f_flags & O_NONBLOCK) अवरोध;
		/* Doing blocking I/O.  Wait here. */
		ret = रुको_event_पूर्णांकerruptible(
			fh->रुको_data,
			pvr2_ioपढ़ो_avail(fh->rhp) >= 0);
		अगर (ret < 0) अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


अटल __poll_t pvr2_v4l2_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t mask = 0;
	काष्ठा pvr2_v4l2_fh *fh = file->निजी_data;
	पूर्णांक ret;

	अगर (fh->fw_mode_flag) अणु
		mask |= EPOLLIN | EPOLLRDNORM;
		वापस mask;
	पूर्ण

	अगर (!fh->rhp) अणु
		ret = pvr2_v4l2_iosetup(fh);
		अगर (ret) वापस EPOLLERR;
	पूर्ण

	poll_रुको(file,&fh->रुको_data,रुको);

	अगर (pvr2_ioपढ़ो_avail(fh->rhp) >= 0) अणु
		mask |= EPOLLIN | EPOLLRDNORM;
	पूर्ण

	वापस mask;
पूर्ण


अटल स्थिर काष्ठा v4l2_file_operations vdev_fops = अणु
	.owner      = THIS_MODULE,
	.खोलो       = pvr2_v4l2_खोलो,
	.release    = pvr2_v4l2_release,
	.पढ़ो       = pvr2_v4l2_पढ़ो,
	.unlocked_ioctl = video_ioctl2,
	.poll       = pvr2_v4l2_poll,
पूर्ण;


अटल स्थिर काष्ठा video_device vdev_ढाँचा = अणु
	.fops       = &vdev_fops,
पूर्ण;


अटल व्योम pvr2_v4l2_dev_init(काष्ठा pvr2_v4l2_dev *dip,
			       काष्ठा pvr2_v4l2 *vp,
			       पूर्णांक v4l_type)
अणु
	पूर्णांक mindevnum;
	पूर्णांक unit_number;
	काष्ठा pvr2_hdw *hdw;
	पूर्णांक *nr_ptr = शून्य;
	u32 caps = V4L2_CAP_TUNER | V4L2_CAP_READWRITE;

	dip->v4lp = vp;

	hdw = vp->channel.mc_head->hdw;
	dip->v4l_type = v4l_type;
	चयन (v4l_type) अणु
	हाल VFL_TYPE_VIDEO:
		dip->stream = &vp->channel.mc_head->video_stream;
		dip->config = pvr2_config_mpeg;
		dip->minor_type = pvr2_v4l_type_video;
		nr_ptr = video_nr;
		caps |= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_AUDIO;
		अगर (!dip->stream) अणु
			pr_err(KBUILD_MODNAME
				": Failed to set up pvrusb2 v4l video dev due to missing stream instance\n");
			वापस;
		पूर्ण
		अवरोध;
	हाल VFL_TYPE_VBI:
		dip->config = pvr2_config_vbi;
		dip->minor_type = pvr2_v4l_type_vbi;
		nr_ptr = vbi_nr;
		caps |= V4L2_CAP_VBI_CAPTURE;
		अवरोध;
	हाल VFL_TYPE_RADIO:
		dip->stream = &vp->channel.mc_head->video_stream;
		dip->config = pvr2_config_mpeg;
		dip->minor_type = pvr2_v4l_type_radio;
		nr_ptr = radio_nr;
		caps |= V4L2_CAP_RADIO;
		अवरोध;
	शेष:
		/* Bail out (this should be impossible) */
		pr_err(KBUILD_MODNAME ": Failed to set up pvrusb2 v4l dev due to unrecognized config\n");
		वापस;
	पूर्ण

	dip->devbase = vdev_ढाँचा;
	dip->devbase.release = pvr2_video_device_release;
	dip->devbase.ioctl_ops = &pvr2_ioctl_ops;
	dip->devbase.device_caps = caps;
	अणु
		पूर्णांक val;
		pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw,
						PVR2_CID_STDAVAIL), &val);
		dip->devbase.tvnorms = (v4l2_std_id)val;
	पूर्ण

	mindevnum = -1;
	unit_number = pvr2_hdw_get_unit_number(hdw);
	अगर (nr_ptr && (unit_number >= 0) && (unit_number < PVR_NUM)) अणु
		mindevnum = nr_ptr[unit_number];
	पूर्ण
	pvr2_hdw_set_v4l2_dev(hdw, &dip->devbase);
	अगर ((video_रेजिस्टर_device(&dip->devbase,
				   dip->v4l_type, mindevnum) < 0) &&
	    (video_रेजिस्टर_device(&dip->devbase,
				   dip->v4l_type, -1) < 0)) अणु
		pr_err(KBUILD_MODNAME
			": Failed to register pvrusb2 v4l device\n");
	पूर्ण

	pr_info("pvrusb2: registered device %s [%s]\n",
	       video_device_node_name(&dip->devbase),
	       pvr2_config_get_name(dip->config));

	pvr2_hdw_v4l_store_minor_number(hdw,
					dip->minor_type,dip->devbase.minor);
पूर्ण


काष्ठा pvr2_v4l2 *pvr2_v4l2_create(काष्ठा pvr2_context *mnp)
अणु
	काष्ठा pvr2_v4l2 *vp;

	vp = kzalloc(माप(*vp),GFP_KERNEL);
	अगर (!vp) वापस vp;
	pvr2_channel_init(&vp->channel,mnp);
	pvr2_trace(PVR2_TRACE_STRUCT,"Creating pvr2_v4l2 id=%p",vp);

	vp->channel.check_func = pvr2_v4l2_पूर्णांकernal_check;

	/* रेजिस्टर streams */
	vp->dev_video = kzalloc(माप(*vp->dev_video),GFP_KERNEL);
	अगर (!vp->dev_video) जाओ fail;
	pvr2_v4l2_dev_init(vp->dev_video,vp,VFL_TYPE_VIDEO);
	अगर (pvr2_hdw_get_input_available(vp->channel.mc_head->hdw) &
	    (1 << PVR2_CVAL_INPUT_RADIO)) अणु
		vp->dev_radio = kzalloc(माप(*vp->dev_radio),GFP_KERNEL);
		अगर (!vp->dev_radio) जाओ fail;
		pvr2_v4l2_dev_init(vp->dev_radio,vp,VFL_TYPE_RADIO);
	पूर्ण

	वापस vp;
 fail:
	pvr2_trace(PVR2_TRACE_STRUCT,"Failure creating pvr2_v4l2 id=%p",vp);
	pvr2_v4l2_destroy_no_lock(vp);
	वापस शून्य;
पूर्ण
