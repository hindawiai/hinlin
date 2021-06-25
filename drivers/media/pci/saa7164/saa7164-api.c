<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>

#समावेश "saa7164.h"

पूर्णांक saa7164_api_get_load_info(काष्ठा saa7164_dev *dev, काष्ठा पंचांगFwInfoStruct *i)
अणु
	पूर्णांक ret;

	अगर (!(saa_debug & DBGLVL_CPU))
		वापस 0;

	dprपूर्णांकk(DBGLVL_API, "%s()\n", __func__);

	i->deviceinst = 0;
	i->devicespec = 0;
	i->mode = 0;
	i->status = 0;

	ret = saa7164_cmd_send(dev, 0, GET_CUR,
		GET_FW_STATUS_CONTROL, माप(काष्ठा पंचांगFwInfoStruct), i);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	prपूर्णांकk(KERN_INFO "saa7164[%d]-CPU: %d percent", dev->nr, i->CPULoad);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_collect_debug(काष्ठा saa7164_dev *dev)
अणु
	काष्ठा पंचांगComResDebugGetData d;
	u8 more = 255;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s()\n", __func__);

	जबतक (more--) अणु

		स_रखो(&d, 0, माप(d));

		ret = saa7164_cmd_send(dev, 0, GET_CUR,
			GET_DEBUG_DATA_CONTROL, माप(d), &d);
		अगर (ret != SAA_OK)
			prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n",
				__func__, ret);

		अगर (d.dwResult != SAA_OK)
			अवरोध;

		prपूर्णांकk(KERN_INFO "saa7164[%d]-FWMSG: %s", dev->nr,
			d.ucDebugData);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक saa7164_api_set_debug(काष्ठा saa7164_dev *dev, u8 level)
अणु
	काष्ठा पंचांगComResDebugSetLevel lvl;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s(level=%d)\n", __func__, level);

	/* Retrieve current state */
	ret = saa7164_cmd_send(dev, 0, GET_CUR,
		SET_DEBUG_LEVEL_CONTROL, माप(lvl), &lvl);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	dprपूर्णांकk(DBGLVL_API, "%s() Was %d\n", __func__, lvl.dwDebugLevel);

	lvl.dwDebugLevel = level;

	/* set new state */
	ret = saa7164_cmd_send(dev, 0, SET_CUR,
		SET_DEBUG_LEVEL_CONTROL, माप(lvl), &lvl);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_set_vbi_क्रमmat(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा पंचांगComResProbeCommit fmt, rsp;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s(nr=%d, unitid=0x%x)\n", __func__,
		port->nr, port->hwcfg.unitid);

	fmt.bmHपूर्णांक = 0;
	fmt.bFormatIndex = 1;
	fmt.bFrameIndex = 1;

	/* Probe, see अगर it can support this क्रमmat */
	ret = saa7164_cmd_send(port->dev, port->hwcfg.unitid,
		SET_CUR, SAA_PROBE_CONTROL, माप(fmt), &fmt);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() set error, ret = 0x%x\n", __func__, ret);

	/* See of the क्रमmat change was successful */
	ret = saa7164_cmd_send(port->dev, port->hwcfg.unitid,
		GET_CUR, SAA_PROBE_CONTROL, माप(rsp), &rsp);
	अगर (ret != SAA_OK) अणु
		prपूर्णांकk(KERN_ERR "%s() get error, ret = 0x%x\n", __func__, ret);
	पूर्ण अन्यथा अणु
		/* Compare requested vs received, should be same */
		अगर (स_भेद(&fmt, &rsp, माप(rsp)) == 0) अणु
			dprपूर्णांकk(DBGLVL_API, "SET/PROBE Verified\n");

			/* Ask the device to select the negotiated क्रमmat */
			ret = saa7164_cmd_send(port->dev, port->hwcfg.unitid,
				SET_CUR, SAA_COMMIT_CONTROL, माप(fmt), &fmt);
			अगर (ret != SAA_OK)
				prपूर्णांकk(KERN_ERR "%s() commit error, ret = 0x%x\n",
					__func__, ret);

			ret = saa7164_cmd_send(port->dev, port->hwcfg.unitid,
				GET_CUR, SAA_COMMIT_CONTROL, माप(rsp), &rsp);
			अगर (ret != SAA_OK)
				prपूर्णांकk(KERN_ERR "%s() GET commit error, ret = 0x%x\n",
					__func__, ret);

			अगर (स_भेद(&fmt, &rsp, माप(rsp)) != 0) अणु
				prपूर्णांकk(KERN_ERR "%s() memcmp error, ret = 0x%x\n",
					__func__, ret);
			पूर्ण अन्यथा
				dprपूर्णांकk(DBGLVL_API, "SET/COMMIT Verified\n");

			dprपूर्णांकk(DBGLVL_API, "rsp.bmHint = 0x%x\n", rsp.bmHपूर्णांक);
			dprपूर्णांकk(DBGLVL_API, "rsp.bFormatIndex = 0x%x\n",
				rsp.bFormatIndex);
			dprपूर्णांकk(DBGLVL_API, "rsp.bFrameIndex = 0x%x\n",
				rsp.bFrameIndex);
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_ERR "%s() compare failed\n", __func__);
	पूर्ण

	अगर (ret == SAA_OK)
		dprपूर्णांकk(DBGLVL_API, "%s(nr=%d) Success\n", __func__, port->nr);

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_api_set_gop_size(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा पंचांगComResEncVideoGopStructure gs;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_ENC, "%s()\n", __func__);

	gs.ucRefFrameDist = port->encoder_params.refdist;
	gs.ucGOPSize = port->encoder_params.gop_size;
	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_VIDEO_GOP_STRUCTURE_CONTROL,
		माप(gs), &gs);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_set_encoder(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा पंचांगComResEncVideoBitRate vb;
	काष्ठा पंचांगComResEncAudioBitRate ab;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_ENC, "%s() unitid=0x%x\n", __func__,
		port->hwcfg.sourceid);

	अगर (port->encoder_params.stream_type == V4L2_MPEG_STREAM_TYPE_MPEG2_PS)
		port->encoder_profile = EU_PROखाता_PS_DVD;
	अन्यथा
		port->encoder_profile = EU_PROखाता_TS_HQ;

	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_PROखाता_CONTROL, माप(u8), &port->encoder_profile);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	/* Resolution */
	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_PROखाता_CONTROL, माप(u8), &port->encoder_profile);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	/* Establish video bitrates */
	अगर (port->encoder_params.bitrate_mode ==
		V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)
		vb.ucVideoBitRateMode = EU_VIDEO_BIT_RATE_MODE_CONSTANT;
	अन्यथा
		vb.ucVideoBitRateMode = EU_VIDEO_BIT_RATE_MODE_VARIABLE_PEAK;
	vb.dwVideoBitRate = port->encoder_params.bitrate;
	vb.dwVideoBitRatePeak = port->encoder_params.bitrate_peak;
	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_VIDEO_BIT_RATE_CONTROL,
		माप(काष्ठा पंचांगComResEncVideoBitRate),
		&vb);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	/* Establish audio bitrates */
	ab.ucAudioBitRateMode = 0;
	ab.dwAudioBitRate = 384000;
	ab.dwAudioBitRatePeak = ab.dwAudioBitRate;
	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_AUDIO_BIT_RATE_CONTROL,
		माप(काष्ठा पंचांगComResEncAudioBitRate),
		&ab);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__,
			ret);

	saa7164_api_set_aspect_ratio(port);
	saa7164_api_set_gop_size(port);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_get_encoder(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा पंचांगComResEncVideoBitRate v;
	काष्ठा पंचांगComResEncAudioBitRate a;
	काष्ठा पंचांगComResEncVideoInputAspectRatio ar;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_ENC, "%s() unitid=0x%x\n", __func__,
		port->hwcfg.sourceid);

	port->encoder_profile = 0;
	port->video_क्रमmat = 0;
	port->video_resolution = 0;
	port->audio_क्रमmat = 0;

	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, GET_CUR,
		EU_PROखाता_CONTROL, माप(u8), &port->encoder_profile);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, GET_CUR,
		EU_VIDEO_RESOLUTION_CONTROL, माप(u8),
		&port->video_resolution);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, GET_CUR,
		EU_VIDEO_FORMAT_CONTROL, माप(u8), &port->video_क्रमmat);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, GET_CUR,
		EU_VIDEO_BIT_RATE_CONTROL, माप(v), &v);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, GET_CUR,
		EU_AUDIO_FORMAT_CONTROL, माप(u8), &port->audio_क्रमmat);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, GET_CUR,
		EU_AUDIO_BIT_RATE_CONTROL, माप(a), &a);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	/* Aspect Ratio */
	ar.width = 0;
	ar.height = 0;
	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, GET_CUR,
		EU_VIDEO_INPUT_ASPECT_CONTROL,
		माप(काष्ठा पंचांगComResEncVideoInputAspectRatio), &ar);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	dprपूर्णांकk(DBGLVL_ENC, "encoder_profile = %d\n", port->encoder_profile);
	dprपूर्णांकk(DBGLVL_ENC, "video_format    = %d\n", port->video_क्रमmat);
	dprपूर्णांकk(DBGLVL_ENC, "audio_format    = %d\n", port->audio_क्रमmat);
	dprपूर्णांकk(DBGLVL_ENC, "video_resolution= %d\n", port->video_resolution);
	dprपूर्णांकk(DBGLVL_ENC, "v.ucVideoBitRateMode = %d\n",
		v.ucVideoBitRateMode);
	dprपूर्णांकk(DBGLVL_ENC, "v.dwVideoBitRate     = %d\n",
		v.dwVideoBitRate);
	dprपूर्णांकk(DBGLVL_ENC, "v.dwVideoBitRatePeak = %d\n",
		v.dwVideoBitRatePeak);
	dprपूर्णांकk(DBGLVL_ENC, "a.ucVideoBitRateMode = %d\n",
		a.ucAudioBitRateMode);
	dprपूर्णांकk(DBGLVL_ENC, "a.dwVideoBitRate     = %d\n",
		a.dwAudioBitRate);
	dprपूर्णांकk(DBGLVL_ENC, "a.dwVideoBitRatePeak = %d\n",
		a.dwAudioBitRatePeak);
	dprपूर्णांकk(DBGLVL_ENC, "aspect.width / height = %d:%d\n",
		ar.width, ar.height);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_set_aspect_ratio(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा पंचांगComResEncVideoInputAspectRatio ar;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_ENC, "%s(%d)\n", __func__,
		port->encoder_params.ctl_aspect);

	चयन (port->encoder_params.ctl_aspect) अणु
	हाल V4L2_MPEG_VIDEO_ASPECT_1x1:
		ar.width = 1;
		ar.height = 1;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_ASPECT_4x3:
		ar.width = 4;
		ar.height = 3;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_ASPECT_16x9:
		ar.width = 16;
		ar.height = 9;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_ASPECT_221x100:
		ar.width = 221;
		ar.height = 100;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	dprपूर्णांकk(DBGLVL_ENC, "%s(%d) now %d:%d\n", __func__,
		port->encoder_params.ctl_aspect,
		ar.width, ar.height);

	/* Aspect Ratio */
	ret = saa7164_cmd_send(port->dev, port->hwcfg.sourceid, SET_CUR,
		EU_VIDEO_INPUT_ASPECT_CONTROL,
		माप(काष्ठा पंचांगComResEncVideoInputAspectRatio), &ar);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_set_usercontrol(काष्ठा saa7164_port *port, u8 ctl)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;
	u16 val;

	अगर (ctl == PU_BRIGHTNESS_CONTROL)
		val = port->ctl_brightness;
	अन्यथा
	अगर (ctl == PU_CONTRAST_CONTROL)
		val = port->ctl_contrast;
	अन्यथा
	अगर (ctl == PU_HUE_CONTROL)
		val = port->ctl_hue;
	अन्यथा
	अगर (ctl == PU_SATURATION_CONTROL)
		val = port->ctl_saturation;
	अन्यथा
	अगर (ctl == PU_SHARPNESS_CONTROL)
		val = port->ctl_sharpness;
	अन्यथा
		वापस -EINVAL;

	dprपूर्णांकk(DBGLVL_ENC, "%s() unitid=0x%x ctl=%d, val=%d\n",
		__func__, port->encunit.vsourceid, ctl, val);

	ret = saa7164_cmd_send(port->dev, port->encunit.vsourceid, SET_CUR,
		ctl, माप(u16), &val);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_get_usercontrol(काष्ठा saa7164_port *port, u8 ctl)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;
	u16 val;

	ret = saa7164_cmd_send(port->dev, port->encunit.vsourceid, GET_CUR,
		ctl, माप(u16), &val);
	अगर (ret != SAA_OK) अणु
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);
		वापस ret;
	पूर्ण

	dprपूर्णांकk(DBGLVL_ENC, "%s() ctl=%d, val=%d\n",
		__func__, ctl, val);

	अगर (ctl == PU_BRIGHTNESS_CONTROL)
		port->ctl_brightness = val;
	अन्यथा
	अगर (ctl == PU_CONTRAST_CONTROL)
		port->ctl_contrast = val;
	अन्यथा
	अगर (ctl == PU_HUE_CONTROL)
		port->ctl_hue = val;
	अन्यथा
	अगर (ctl == PU_SATURATION_CONTROL)
		port->ctl_saturation = val;
	अन्यथा
	अगर (ctl == PU_SHARPNESS_CONTROL)
		port->ctl_sharpness = val;

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_set_videomux(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	u8 inमाला_दो[] = अणु 1, 2, 2, 2, 5, 5, 5 पूर्ण;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_ENC, "%s() v_mux=%d a_mux=%d\n",
		__func__, port->mux_input, inमाला_दो[port->mux_input - 1]);

	/* Audio Mute */
	ret = saa7164_api_audio_mute(port, 1);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	/* Video Mux */
	ret = saa7164_cmd_send(port->dev, port->vidproc.sourceid, SET_CUR,
		SU_INPUT_SELECT_CONTROL, माप(u8), &port->mux_input);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	/* Audio Mux */
	ret = saa7164_cmd_send(port->dev, port->audfeat.sourceid, SET_CUR,
		SU_INPUT_SELECT_CONTROL, माप(u8),
		&inमाला_दो[port->mux_input - 1]);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	/* Audio UnMute */
	ret = saa7164_api_audio_mute(port, 0);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_audio_mute(काष्ठा saa7164_port *port, पूर्णांक mute)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	u8 v = mute;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s(%d)\n", __func__, mute);

	ret = saa7164_cmd_send(port->dev, port->audfeat.unitid, SET_CUR,
		MUTE_CONTROL, माप(u8), &v);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	वापस ret;
पूर्ण

/* 0 = silence, 0xff = full */
पूर्णांक saa7164_api_set_audio_volume(काष्ठा saa7164_port *port, s8 level)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	s16 v, min, max;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s(%d)\n", __func__, level);

	/* Obtain the min/max ranges */
	ret = saa7164_cmd_send(port->dev, port->audfeat.unitid, GET_MIN,
		VOLUME_CONTROL, माप(u16), &min);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	ret = saa7164_cmd_send(port->dev, port->audfeat.unitid, GET_MAX,
		VOLUME_CONTROL, माप(u16), &max);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	ret = saa7164_cmd_send(port->dev, port->audfeat.unitid, GET_CUR,
		(0x01 << 8) | VOLUME_CONTROL, माप(u16), &v);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	dprपूर्णांकk(DBGLVL_API, "%s(%d) min=%d max=%d cur=%d\n", __func__,
		level, min, max, v);

	v = level;
	अगर (v < min)
		v = min;
	अगर (v > max)
		v = max;

	/* Left */
	ret = saa7164_cmd_send(port->dev, port->audfeat.unitid, SET_CUR,
		(0x01 << 8) | VOLUME_CONTROL, माप(s16), &v);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	/* Right */
	ret = saa7164_cmd_send(port->dev, port->audfeat.unitid, SET_CUR,
		(0x02 << 8) | VOLUME_CONTROL, माप(s16), &v);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	ret = saa7164_cmd_send(port->dev, port->audfeat.unitid, GET_CUR,
		(0x01 << 8) | VOLUME_CONTROL, माप(u16), &v);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	dprपूर्णांकk(DBGLVL_API, "%s(%d) min=%d max=%d cur=%d\n", __func__,
		level, min, max, v);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_set_audio_std(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा पंचांगComResAudioDefaults lvl;
	काष्ठा पंचांगComResTunerStandard tvaudio;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s()\n", __func__);

	/* Establish शेष levels */
	lvl.ucDecoderLevel = TMHW_LEV_ADJ_DECLEV_DEFAULT;
	lvl.ucDecoderFM_Level = TMHW_LEV_ADJ_DECLEV_DEFAULT;
	lvl.ucMonoLevel = TMHW_LEV_ADJ_MONOLEV_DEFAULT;
	lvl.ucNICAM_Level = TMHW_LEV_ADJ_NICLEV_DEFAULT;
	lvl.ucSAP_Level = TMHW_LEV_ADJ_SAPLEV_DEFAULT;
	lvl.ucADC_Level = TMHW_LEV_ADJ_ADCLEV_DEFAULT;
	ret = saa7164_cmd_send(port->dev, port->audfeat.unitid, SET_CUR,
		AUDIO_DEFAULT_CONTROL, माप(काष्ठा पंचांगComResAudioDefaults),
		&lvl);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	/* Manually select the appropriate TV audio standard */
	अगर (port->encodernorm.id & V4L2_STD_NTSC) अणु
		tvaudio.std = TU_STANDARD_NTSC_M;
		tvaudio.country = 1;
	पूर्ण अन्यथा अणु
		tvaudio.std = TU_STANDARD_PAL_I;
		tvaudio.country = 44;
	पूर्ण

	ret = saa7164_cmd_send(port->dev, port->tunerunit.unitid, SET_CUR,
		TU_STANDARD_CONTROL, माप(tvaudio), &tvaudio);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() TU_STANDARD_CONTROL error, ret = 0x%x\n",
			__func__, ret);
	वापस ret;
पूर्ण

पूर्णांक saa7164_api_set_audio_detection(काष्ठा saa7164_port *port, पूर्णांक स्वतःdetect)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा पंचांगComResTunerStandardAuto p;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s(%d)\n", __func__, स्वतःdetect);

	/* Disable TV Audio स्वतःdetect अगर not alपढ़ोy set (buggy) */
	अगर (स्वतःdetect)
		p.mode = TU_STANDARD_AUTO;
	अन्यथा
		p.mode = TU_STANDARD_MANUAL;
	ret = saa7164_cmd_send(port->dev, port->tunerunit.unitid, SET_CUR,
		TU_STANDARD_AUTO_CONTROL, माप(p), &p);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR
			"%s() TU_STANDARD_AUTO_CONTROL error, ret = 0x%x\n",
			__func__, ret);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_get_videomux(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	पूर्णांक ret;

	ret = saa7164_cmd_send(port->dev, port->vidproc.sourceid, GET_CUR,
		SU_INPUT_SELECT_CONTROL, माप(u8), &port->mux_input);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	dprपूर्णांकk(DBGLVL_ENC, "%s() v_mux=%d\n",
		__func__, port->mux_input);

	वापस ret;
पूर्ण

अटल पूर्णांक saa7164_api_set_dअगर(काष्ठा saa7164_port *port, u8 reg, u8 val)
अणु
	काष्ठा saa7164_dev *dev = port->dev;

	u16 len = 0;
	u8 buf[256];
	पूर्णांक ret;
	u8 mas;

	dprपूर्णांकk(DBGLVL_API, "%s(nr=%d type=%d val=%x)\n", __func__,
		port->nr, port->type, val);

	अगर (port->nr == 0)
		mas = 0xd0;
	अन्यथा
		mas = 0xe0;

	स_रखो(buf, 0, माप(buf));

	buf[0x00] = 0x04;
	buf[0x01] = 0x00;
	buf[0x02] = 0x00;
	buf[0x03] = 0x00;

	buf[0x04] = 0x04;
	buf[0x05] = 0x00;
	buf[0x06] = 0x00;
	buf[0x07] = 0x00;

	buf[0x08] = reg;
	buf[0x09] = 0x26;
	buf[0x0a] = mas;
	buf[0x0b] = 0xb0;

	buf[0x0c] = val;
	buf[0x0d] = 0x00;
	buf[0x0e] = 0x00;
	buf[0x0f] = 0x00;

	ret = saa7164_cmd_send(dev, port->अगरunit.unitid, GET_LEN,
		EXU_REGISTER_ACCESS_CONTROL, माप(len), &len);
	अगर (ret != SAA_OK) अणु
		prपूर्णांकk(KERN_ERR "%s() error, ret(1) = 0x%x\n", __func__, ret);
		वापस -EIO;
	पूर्ण

	ret = saa7164_cmd_send(dev, port->अगरunit.unitid, SET_CUR,
		EXU_REGISTER_ACCESS_CONTROL, len, &buf);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret(2) = 0x%x\n", __func__, ret);
#अगर 0
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1, buf, 16,
		       false);
#पूर्ण_अगर
	वापस ret == SAA_OK ? 0 : -EIO;
पूर्ण

/* Disable the IF block AGC controls */
पूर्णांक saa7164_api_configure_dअगर(काष्ठा saa7164_port *port, u32 std)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	u8 agc_disable;

	dprपूर्णांकk(DBGLVL_API, "%s(nr=%d, 0x%x)\n", __func__, port->nr, std);

	अगर (std & V4L2_STD_NTSC) अणु
		dprपूर्णांकk(DBGLVL_API, " NTSC\n");
		saa7164_api_set_dअगर(port, 0x00, 0x01); /* Video Standard */
		agc_disable = 0;
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL_I) अणु
		dprपूर्णांकk(DBGLVL_API, " PAL-I\n");
		saa7164_api_set_dअगर(port, 0x00, 0x08); /* Video Standard */
		agc_disable = 0;
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL_M) अणु
		dprपूर्णांकk(DBGLVL_API, " PAL-M\n");
		saa7164_api_set_dअगर(port, 0x00, 0x01); /* Video Standard */
		agc_disable = 0;
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL_N) अणु
		dprपूर्णांकk(DBGLVL_API, " PAL-N\n");
		saa7164_api_set_dअगर(port, 0x00, 0x01); /* Video Standard */
		agc_disable = 0;
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL_Nc) अणु
		dprपूर्णांकk(DBGLVL_API, " PAL-Nc\n");
		saa7164_api_set_dअगर(port, 0x00, 0x01); /* Video Standard */
		agc_disable = 0;
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL_B) अणु
		dprपूर्णांकk(DBGLVL_API, " PAL-B\n");
		saa7164_api_set_dअगर(port, 0x00, 0x02); /* Video Standard */
		agc_disable = 0;
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL_DK) अणु
		dprपूर्णांकk(DBGLVL_API, " PAL-DK\n");
		saa7164_api_set_dअगर(port, 0x00, 0x10); /* Video Standard */
		agc_disable = 0;
	पूर्ण अन्यथा अगर (std & V4L2_STD_SECAM_L) अणु
		dprपूर्णांकk(DBGLVL_API, " SECAM-L\n");
		saa7164_api_set_dअगर(port, 0x00, 0x20); /* Video Standard */
		agc_disable = 0;
	पूर्ण अन्यथा अणु
		/* Unknown standard, assume DTV */
		dprपूर्णांकk(DBGLVL_API, " Unknown (assuming DTV)\n");
		/* Undefinded Video Standard */
		saa7164_api_set_dअगर(port, 0x00, 0x80);
		agc_disable = 1;
	पूर्ण

	saa7164_api_set_dअगर(port, 0x48, 0xa0); /* AGC Functions 1 */
	saa7164_api_set_dअगर(port, 0xc0, agc_disable); /* AGC Output Disable */
	saa7164_api_set_dअगर(port, 0x7c, 0x04); /* CVBS EQ */
	saa7164_api_set_dअगर(port, 0x04, 0x01); /* Active */
	msleep(100);
	saa7164_api_set_dअगर(port, 0x04, 0x00); /* Active (again) */
	msleep(100);

	वापस 0;
पूर्ण

/* Ensure the dअगर is in the correct state क्रम the operating mode
 * (analog / dtv). We only configure the dअगरf through the analog encoder
 * so when we're in digital mode we need to find the appropriate encoder
 * and use it to configure the DIF.
 */
पूर्णांक saa7164_api_initialize_dअगर(काष्ठा saa7164_port *port)
अणु
	काष्ठा saa7164_dev *dev = port->dev;
	काष्ठा saa7164_port *p = शून्य;
	पूर्णांक ret = -EINVAL;
	u32 std = 0;

	dprपूर्णांकk(DBGLVL_API, "%s(nr=%d type=%d)\n", __func__,
		port->nr, port->type);

	अगर (port->type == SAA7164_MPEG_ENCODER) अणु
		/* Pick any analog standard to init the dअगरf.
		 * we'll come back during encoder_init'
		 * and set the correct standard अगर required.
		 */
		std = V4L2_STD_NTSC;
	पूर्ण अन्यथा
	अगर (port->type == SAA7164_MPEG_DVB) अणु
		अगर (port->nr == SAA7164_PORT_TS1)
			p = &dev->ports[SAA7164_PORT_ENC1];
		अन्यथा
			p = &dev->ports[SAA7164_PORT_ENC2];
	पूर्ण अन्यथा
	अगर (port->type == SAA7164_MPEG_VBI) अणु
		std = V4L2_STD_NTSC;
		अगर (port->nr == SAA7164_PORT_VBI1)
			p = &dev->ports[SAA7164_PORT_ENC1];
		अन्यथा
			p = &dev->ports[SAA7164_PORT_ENC2];
	पूर्ण अन्यथा
		BUG();

	अगर (p)
		ret = saa7164_api_configure_dअगर(p, std);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_transition_port(काष्ठा saa7164_port *port, u8 mode)
अणु
	काष्ठा saa7164_dev *dev = port->dev;

	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s(nr=%d unitid=0x%x,%d)\n",
		__func__, port->nr, port->hwcfg.unitid, mode);

	ret = saa7164_cmd_send(port->dev, port->hwcfg.unitid, SET_CUR,
		SAA_STATE_CONTROL, माप(mode), &mode);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s(portnr %d unitid 0x%x) error, ret = 0x%x\n",
			__func__, port->nr, port->hwcfg.unitid, ret);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_get_fw_version(काष्ठा saa7164_dev *dev, u32 *version)
अणु
	पूर्णांक ret;

	ret = saa7164_cmd_send(dev, 0, GET_CUR,
		GET_FW_VERSION_CONTROL, माप(u32), version);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_पढ़ो_eeprom(काष्ठा saa7164_dev *dev, u8 *buf, पूर्णांक buflen)
अणु
	u8 reg[] = अणु 0x0f, 0x00 पूर्ण;

	अगर (buflen < 128)
		वापस -ENOMEM;

	/* Assumption: Hauppauge eeprom is at 0xa0 on on bus 0 */
	/* TODO: Pull the details from the boards काष्ठा */
	वापस saa7164_api_i2c_पढ़ो(&dev->i2c_bus[0], 0xa0 >> 1, माप(reg),
		&reg[0], 128, buf);
पूर्ण

अटल पूर्णांक saa7164_api_configure_port_vbi(काष्ठा saa7164_dev *dev,
					  काष्ठा saa7164_port *port)
अणु
	काष्ठा पंचांगComResVBIFormatDescrHeader *fmt = &port->vbi_fmt_ntsc;

	dprपूर्णांकk(DBGLVL_API, "    bFormatIndex  = 0x%x\n", fmt->bFormatIndex);
	dprपूर्णांकk(DBGLVL_API, "    VideoStandard = 0x%x\n", fmt->VideoStandard);
	dprपूर्णांकk(DBGLVL_API, "    StartLine     = %d\n", fmt->StartLine);
	dprपूर्णांकk(DBGLVL_API, "    EndLine       = %d\n", fmt->EndLine);
	dprपूर्णांकk(DBGLVL_API, "    FieldRate     = %d\n", fmt->FieldRate);
	dprपूर्णांकk(DBGLVL_API, "    bNumLines     = %d\n", fmt->bNumLines);

	/* Cache the hardware configuration in the port */

	port->bufcounter = port->hwcfg.BARLocation;
	port->pitch = port->hwcfg.BARLocation + (2 * माप(u32));
	port->bufsize = port->hwcfg.BARLocation + (3 * माप(u32));
	port->bufoffset = port->hwcfg.BARLocation + (4 * माप(u32));
	port->bufptr32l = port->hwcfg.BARLocation +
		(4 * माप(u32)) +
		(माप(u32) * port->hwcfg.buffercount) + माप(u32);
	port->bufptr32h = port->hwcfg.BARLocation +
		(4 * माप(u32)) +
		(माप(u32) * port->hwcfg.buffercount);
	port->bufptr64 = port->hwcfg.BARLocation +
		(4 * माप(u32)) +
		(माप(u32) * port->hwcfg.buffercount);
	dprपूर्णांकk(DBGLVL_API, "   = port->hwcfg.BARLocation = 0x%x\n",
		port->hwcfg.BARLocation);

	dprपूर्णांकk(DBGLVL_API, "   = VS_FORMAT_VBI (becomes dev->en[%d])\n",
		port->nr);

	वापस 0;
पूर्ण

अटल पूर्णांक
saa7164_api_configure_port_mpeg2ts(काष्ठा saa7164_dev *dev,
				   काष्ठा saa7164_port *port,
				   काष्ठा पंचांगComResTSFormatDescrHeader *tsfmt)
अणु
	dprपूर्णांकk(DBGLVL_API, "    bFormatIndex = 0x%x\n", tsfmt->bFormatIndex);
	dprपूर्णांकk(DBGLVL_API, "    bDataOffset  = 0x%x\n", tsfmt->bDataOffset);
	dprपूर्णांकk(DBGLVL_API, "    bPacketLength= 0x%x\n", tsfmt->bPacketLength);
	dprपूर्णांकk(DBGLVL_API, "    bStrideLength= 0x%x\n", tsfmt->bStrideLength);
	dprपूर्णांकk(DBGLVL_API, "    bguid        = (....)\n");

	/* Cache the hardware configuration in the port */

	port->bufcounter = port->hwcfg.BARLocation;
	port->pitch = port->hwcfg.BARLocation + (2 * माप(u32));
	port->bufsize = port->hwcfg.BARLocation + (3 * माप(u32));
	port->bufoffset = port->hwcfg.BARLocation + (4 * माप(u32));
	port->bufptr32l = port->hwcfg.BARLocation +
		(4 * माप(u32)) +
		(माप(u32) * port->hwcfg.buffercount) + माप(u32);
	port->bufptr32h = port->hwcfg.BARLocation +
		(4 * माप(u32)) +
		(माप(u32) * port->hwcfg.buffercount);
	port->bufptr64 = port->hwcfg.BARLocation +
		(4 * माप(u32)) +
		(माप(u32) * port->hwcfg.buffercount);
	dprपूर्णांकk(DBGLVL_API, "   = port->hwcfg.BARLocation = 0x%x\n",
		port->hwcfg.BARLocation);

	dprपूर्णांकk(DBGLVL_API, "   = VS_FORMAT_MPEGTS (becomes dev->ts[%d])\n",
		port->nr);

	वापस 0;
पूर्ण

अटल पूर्णांक
saa7164_api_configure_port_mpeg2ps(काष्ठा saa7164_dev *dev,
				   काष्ठा saa7164_port *port,
				   काष्ठा पंचांगComResPSFormatDescrHeader *fmt)
अणु
	dprपूर्णांकk(DBGLVL_API, "    bFormatIndex = 0x%x\n", fmt->bFormatIndex);
	dprपूर्णांकk(DBGLVL_API, "    wPacketLength= 0x%x\n", fmt->wPacketLength);
	dprपूर्णांकk(DBGLVL_API, "    wPackLength=   0x%x\n", fmt->wPackLength);
	dprपूर्णांकk(DBGLVL_API, "    bPackDataType= 0x%x\n", fmt->bPackDataType);

	/* Cache the hardware configuration in the port */
	/* TODO: CHECK THIS in the port config */
	port->bufcounter = port->hwcfg.BARLocation;
	port->pitch = port->hwcfg.BARLocation + (2 * माप(u32));
	port->bufsize = port->hwcfg.BARLocation + (3 * माप(u32));
	port->bufoffset = port->hwcfg.BARLocation + (4 * माप(u32));
	port->bufptr32l = port->hwcfg.BARLocation +
		(4 * माप(u32)) +
		(माप(u32) * port->hwcfg.buffercount) + माप(u32);
	port->bufptr32h = port->hwcfg.BARLocation +
		(4 * माप(u32)) +
		(माप(u32) * port->hwcfg.buffercount);
	port->bufptr64 = port->hwcfg.BARLocation +
		(4 * माप(u32)) +
		(माप(u32) * port->hwcfg.buffercount);
	dprपूर्णांकk(DBGLVL_API, "   = port->hwcfg.BARLocation = 0x%x\n",
		port->hwcfg.BARLocation);

	dprपूर्णांकk(DBGLVL_API, "   = VS_FORMAT_MPEGPS (becomes dev->enc[%d])\n",
		port->nr);

	वापस 0;
पूर्ण

अटल पूर्णांक saa7164_api_dump_subdevs(काष्ठा saa7164_dev *dev, u8 *buf, पूर्णांक len)
अणु
	काष्ठा saa7164_port *tsport = शून्य;
	काष्ठा saa7164_port *encport = शून्य;
	काष्ठा saa7164_port *vbiport = शून्य;
	u32 idx, next_offset;
	पूर्णांक i;
	काष्ठा पंचांगComResDescrHeader *hdr, *t;
	काष्ठा पंचांगComResExtDevDescrHeader *exthdr;
	काष्ठा पंचांगComResPathDescrHeader *pathhdr;
	काष्ठा पंचांगComResAntTermDescrHeader *anttermhdr;
	काष्ठा पंचांगComResTunerDescrHeader *tunerunithdr;
	काष्ठा पंचांगComResDMATermDescrHeader *vcoutputtermhdr;
	काष्ठा पंचांगComResTSFormatDescrHeader *tsfmt;
	काष्ठा पंचांगComResPSFormatDescrHeader *psfmt;
	काष्ठा पंचांगComResSelDescrHeader *psel;
	काष्ठा पंचांगComResProcDescrHeader *pdh;
	काष्ठा पंचांगComResAFeatureDescrHeader *afd;
	काष्ठा पंचांगComResEncoderDescrHeader *edh;
	काष्ठा पंचांगComResVBIFormatDescrHeader *vbअगरmt;
	u32 currpath = 0;

	dprपूर्णांकk(DBGLVL_API,
		"%s(?,?,%d) sizeof(struct tmComResDescrHeader) = %d bytes\n",
		__func__, len, (u32)माप(काष्ठा पंचांगComResDescrHeader));

	क्रम (idx = 0; idx < (len - माप(काष्ठा पंचांगComResDescrHeader));) अणु

		hdr = (काष्ठा पंचांगComResDescrHeader *)(buf + idx);

		अगर (hdr->type != CS_INTERFACE)
			वापस SAA_ERR_NOT_SUPPORTED;

		dprपूर्णांकk(DBGLVL_API, "@ 0x%x =\n", idx);
		चयन (hdr->subtype) अणु
		हाल GENERAL_REQUEST:
			dprपूर्णांकk(DBGLVL_API, " GENERAL_REQUEST\n");
			अवरोध;
		हाल VC_TUNER_PATH:
			dprपूर्णांकk(DBGLVL_API, " VC_TUNER_PATH\n");
			pathhdr = (काष्ठा पंचांगComResPathDescrHeader *)(buf + idx);
			dprपूर्णांकk(DBGLVL_API, "  pathid = 0x%x\n",
				pathhdr->pathid);
			currpath = pathhdr->pathid;
			अवरोध;
		हाल VC_INPUT_TERMINAL:
			dprपूर्णांकk(DBGLVL_API, " VC_INPUT_TERMINAL\n");
			anttermhdr =
				(काष्ठा पंचांगComResAntTermDescrHeader *)(buf + idx);
			dprपूर्णांकk(DBGLVL_API, "  terminalid   = 0x%x\n",
				anttermhdr->terminalid);
			dprपूर्णांकk(DBGLVL_API, "  terminaltype = 0x%x\n",
				anttermhdr->terminaltype);
			चयन (anttermhdr->terminaltype) अणु
			हाल ITT_ANTENNA:
				dprपूर्णांकk(DBGLVL_API, "   = ITT_ANTENNA\n");
				अवरोध;
			हाल LINE_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API, "   = LINE_CONNECTOR\n");
				अवरोध;
			हाल SPDIF_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API, "   = SPDIF_CONNECTOR\n");
				अवरोध;
			हाल COMPOSITE_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API,
					"   = COMPOSITE_CONNECTOR\n");
				अवरोध;
			हाल SVIDEO_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API, "   = SVIDEO_CONNECTOR\n");
				अवरोध;
			हाल COMPONENT_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API,
					"   = COMPONENT_CONNECTOR\n");
				अवरोध;
			हाल STANDARD_DMA:
				dprपूर्णांकk(DBGLVL_API, "   = STANDARD_DMA\n");
				अवरोध;
			शेष:
				dprपूर्णांकk(DBGLVL_API, "   = undefined (0x%x)\n",
					anttermhdr->terminaltype);
			पूर्ण
			dprपूर्णांकk(DBGLVL_API, "  assocterminal= 0x%x\n",
				anttermhdr->assocterminal);
			dprपूर्णांकk(DBGLVL_API, "  iterminal    = 0x%x\n",
				anttermhdr->iterminal);
			dprपूर्णांकk(DBGLVL_API, "  controlsize  = 0x%x\n",
				anttermhdr->controlsize);
			अवरोध;
		हाल VC_OUTPUT_TERMINAL:
			dprपूर्णांकk(DBGLVL_API, " VC_OUTPUT_TERMINAL\n");
			vcoutputtermhdr =
				(काष्ठा पंचांगComResDMATermDescrHeader *)(buf + idx);
			dprपूर्णांकk(DBGLVL_API, "  unitid = 0x%x\n",
				vcoutputtermhdr->unitid);
			dprपूर्णांकk(DBGLVL_API, "  terminaltype = 0x%x\n",
				vcoutputtermhdr->terminaltype);
			चयन (vcoutputtermhdr->terminaltype) अणु
			हाल ITT_ANTENNA:
				dprपूर्णांकk(DBGLVL_API, "   = ITT_ANTENNA\n");
				अवरोध;
			हाल LINE_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API, "   = LINE_CONNECTOR\n");
				अवरोध;
			हाल SPDIF_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API, "   = SPDIF_CONNECTOR\n");
				अवरोध;
			हाल COMPOSITE_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API,
					"   = COMPOSITE_CONNECTOR\n");
				अवरोध;
			हाल SVIDEO_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API, "   = SVIDEO_CONNECTOR\n");
				अवरोध;
			हाल COMPONENT_CONNECTOR:
				dprपूर्णांकk(DBGLVL_API,
					"   = COMPONENT_CONNECTOR\n");
				अवरोध;
			हाल STANDARD_DMA:
				dprपूर्णांकk(DBGLVL_API, "   = STANDARD_DMA\n");
				अवरोध;
			शेष:
				dprपूर्णांकk(DBGLVL_API, "   = undefined (0x%x)\n",
					vcoutputtermhdr->terminaltype);
			पूर्ण
			dprपूर्णांकk(DBGLVL_API, "  assocterminal= 0x%x\n",
				vcoutputtermhdr->assocterminal);
			dprपूर्णांकk(DBGLVL_API, "  sourceid     = 0x%x\n",
				vcoutputtermhdr->sourceid);
			dprपूर्णांकk(DBGLVL_API, "  iterminal    = 0x%x\n",
				vcoutputtermhdr->iterminal);
			dprपूर्णांकk(DBGLVL_API, "  BARLocation  = 0x%x\n",
				vcoutputtermhdr->BARLocation);
			dprपूर्णांकk(DBGLVL_API, "  flags        = 0x%x\n",
				vcoutputtermhdr->flags);
			dprपूर्णांकk(DBGLVL_API, "  interruptid  = 0x%x\n",
				vcoutputtermhdr->पूर्णांकerruptid);
			dprपूर्णांकk(DBGLVL_API, "  buffercount  = 0x%x\n",
				vcoutputtermhdr->buffercount);
			dprपूर्णांकk(DBGLVL_API, "  metadatasize = 0x%x\n",
				vcoutputtermhdr->metadatasize);
			dprपूर्णांकk(DBGLVL_API, "  controlsize  = 0x%x\n",
				vcoutputtermhdr->controlsize);
			dprपूर्णांकk(DBGLVL_API, "  numformats   = 0x%x\n",
				vcoutputtermhdr->numक्रमmats);

			t = (काष्ठा पंचांगComResDescrHeader *)
				((काष्ठा पंचांगComResDMATermDescrHeader *)(buf + idx));
			next_offset = idx + (vcoutputtermhdr->len);
			क्रम (i = 0; i < vcoutputtermhdr->numक्रमmats; i++) अणु
				t = (काष्ठा पंचांगComResDescrHeader *)
					(buf + next_offset);
				चयन (t->subtype) अणु
				हाल VS_FORMAT_MPEG2TS:
					tsfmt =
					(काष्ठा पंचांगComResTSFormatDescrHeader *)t;
					अगर (currpath == 1)
						tsport = &dev->ports[SAA7164_PORT_TS1];
					अन्यथा
						tsport = &dev->ports[SAA7164_PORT_TS2];
					स_नकल(&tsport->hwcfg, vcoutputtermhdr,
						माप(*vcoutputtermhdr));
					saa7164_api_configure_port_mpeg2ts(dev,
						tsport, tsfmt);
					अवरोध;
				हाल VS_FORMAT_MPEG2PS:
					psfmt =
					(काष्ठा पंचांगComResPSFormatDescrHeader *)t;
					अगर (currpath == 1)
						encport = &dev->ports[SAA7164_PORT_ENC1];
					अन्यथा
						encport = &dev->ports[SAA7164_PORT_ENC2];
					स_नकल(&encport->hwcfg, vcoutputtermhdr,
						माप(*vcoutputtermhdr));
					saa7164_api_configure_port_mpeg2ps(dev,
						encport, psfmt);
					अवरोध;
				हाल VS_FORMAT_VBI:
					vbअगरmt =
					(काष्ठा पंचांगComResVBIFormatDescrHeader *)t;
					अगर (currpath == 1)
						vbiport = &dev->ports[SAA7164_PORT_VBI1];
					अन्यथा
						vbiport = &dev->ports[SAA7164_PORT_VBI2];
					स_नकल(&vbiport->hwcfg, vcoutputtermhdr,
						माप(*vcoutputtermhdr));
					स_नकल(&vbiport->vbi_fmt_ntsc, vbअगरmt,
						माप(*vbअगरmt));
					saa7164_api_configure_port_vbi(dev,
						vbiport);
					अवरोध;
				हाल VS_FORMAT_RDS:
					dprपूर्णांकk(DBGLVL_API,
						"   = VS_FORMAT_RDS\n");
					अवरोध;
				हाल VS_FORMAT_UNCOMPRESSED:
					dprपूर्णांकk(DBGLVL_API,
					"   = VS_FORMAT_UNCOMPRESSED\n");
					अवरोध;
				हाल VS_FORMAT_TYPE:
					dprपूर्णांकk(DBGLVL_API,
						"   = VS_FORMAT_TYPE\n");
					अवरोध;
				शेष:
					dprपूर्णांकk(DBGLVL_API,
						"   = undefined (0x%x)\n",
						t->subtype);
				पूर्ण
				next_offset += t->len;
			पूर्ण

			अवरोध;
		हाल TUNER_UNIT:
			dprपूर्णांकk(DBGLVL_API, " TUNER_UNIT\n");
			tunerunithdr =
				(काष्ठा पंचांगComResTunerDescrHeader *)(buf + idx);
			dprपूर्णांकk(DBGLVL_API, "  unitid = 0x%x\n",
				tunerunithdr->unitid);
			dprपूर्णांकk(DBGLVL_API, "  sourceid = 0x%x\n",
				tunerunithdr->sourceid);
			dprपूर्णांकk(DBGLVL_API, "  iunit = 0x%x\n",
				tunerunithdr->iunit);
			dprपूर्णांकk(DBGLVL_API, "  tuningstandards = 0x%x\n",
				tunerunithdr->tuningstandards);
			dprपूर्णांकk(DBGLVL_API, "  controlsize = 0x%x\n",
				tunerunithdr->controlsize);
			dprपूर्णांकk(DBGLVL_API, "  controls = 0x%x\n",
				tunerunithdr->controls);

			अगर (tunerunithdr->unitid == tunerunithdr->iunit) अणु
				अगर (currpath == 1)
					encport = &dev->ports[SAA7164_PORT_ENC1];
				अन्यथा
					encport = &dev->ports[SAA7164_PORT_ENC2];
				स_नकल(&encport->tunerunit, tunerunithdr,
					माप(काष्ठा पंचांगComResTunerDescrHeader));
				dprपूर्णांकk(DBGLVL_API,
					"  (becomes dev->enc[%d] tuner)\n",
					encport->nr);
			पूर्ण
			अवरोध;
		हाल VC_SELECTOR_UNIT:
			psel = (काष्ठा पंचांगComResSelDescrHeader *)(buf + idx);
			dprपूर्णांकk(DBGLVL_API, " VC_SELECTOR_UNIT\n");
			dprपूर्णांकk(DBGLVL_API, "  unitid = 0x%x\n",
				psel->unitid);
			dprपूर्णांकk(DBGLVL_API, "  nrinpins = 0x%x\n",
				psel->nrinpins);
			dprपूर्णांकk(DBGLVL_API, "  sourceid = 0x%x\n",
				psel->sourceid);
			अवरोध;
		हाल VC_PROCESSING_UNIT:
			pdh = (काष्ठा पंचांगComResProcDescrHeader *)(buf + idx);
			dprपूर्णांकk(DBGLVL_API, " VC_PROCESSING_UNIT\n");
			dprपूर्णांकk(DBGLVL_API, "  unitid = 0x%x\n",
				pdh->unitid);
			dprपूर्णांकk(DBGLVL_API, "  sourceid = 0x%x\n",
				pdh->sourceid);
			dprपूर्णांकk(DBGLVL_API, "  controlsize = 0x%x\n",
				pdh->controlsize);
			अगर (pdh->controlsize == 0x04) अणु
				अगर (currpath == 1)
					encport = &dev->ports[SAA7164_PORT_ENC1];
				अन्यथा
					encport = &dev->ports[SAA7164_PORT_ENC2];
				स_नकल(&encport->vidproc, pdh,
					माप(काष्ठा पंचांगComResProcDescrHeader));
				dprपूर्णांकk(DBGLVL_API, "  (becomes dev->enc[%d])\n",
					encport->nr);
			पूर्ण
			अवरोध;
		हाल FEATURE_UNIT:
			afd = (काष्ठा पंचांगComResAFeatureDescrHeader *)(buf + idx);
			dprपूर्णांकk(DBGLVL_API, " FEATURE_UNIT\n");
			dprपूर्णांकk(DBGLVL_API, "  unitid = 0x%x\n",
				afd->unitid);
			dprपूर्णांकk(DBGLVL_API, "  sourceid = 0x%x\n",
				afd->sourceid);
			dprपूर्णांकk(DBGLVL_API, "  controlsize = 0x%x\n",
				afd->controlsize);
			अगर (currpath == 1)
				encport = &dev->ports[SAA7164_PORT_ENC1];
			अन्यथा
				encport = &dev->ports[SAA7164_PORT_ENC2];
			स_नकल(&encport->audfeat, afd,
				माप(काष्ठा पंचांगComResAFeatureDescrHeader));
			dprपूर्णांकk(DBGLVL_API, "  (becomes dev->enc[%d])\n",
				encport->nr);
			अवरोध;
		हाल ENCODER_UNIT:
			edh = (काष्ठा पंचांगComResEncoderDescrHeader *)(buf + idx);
			dprपूर्णांकk(DBGLVL_API, " ENCODER_UNIT\n");
			dprपूर्णांकk(DBGLVL_API, "  subtype = 0x%x\n", edh->subtype);
			dprपूर्णांकk(DBGLVL_API, "  unitid = 0x%x\n", edh->unitid);
			dprपूर्णांकk(DBGLVL_API, "  vsourceid = 0x%x\n",
			edh->vsourceid);
			dprपूर्णांकk(DBGLVL_API, "  asourceid = 0x%x\n",
				edh->asourceid);
			dprपूर्णांकk(DBGLVL_API, "  iunit = 0x%x\n", edh->iunit);
			अगर (edh->iunit == edh->unitid) अणु
				अगर (currpath == 1)
					encport = &dev->ports[SAA7164_PORT_ENC1];
				अन्यथा
					encport = &dev->ports[SAA7164_PORT_ENC2];
				स_नकल(&encport->encunit, edh,
					माप(काष्ठा पंचांगComResEncoderDescrHeader));
				dprपूर्णांकk(DBGLVL_API,
					"  (becomes dev->enc[%d])\n",
					encport->nr);
			पूर्ण
			अवरोध;
		हाल EXTENSION_UNIT:
			dprपूर्णांकk(DBGLVL_API, " EXTENSION_UNIT\n");
			exthdr = (काष्ठा पंचांगComResExtDevDescrHeader *)(buf + idx);
			dprपूर्णांकk(DBGLVL_API, "  unitid = 0x%x\n",
				exthdr->unitid);
			dprपूर्णांकk(DBGLVL_API, "  deviceid = 0x%x\n",
				exthdr->deviceid);
			dprपूर्णांकk(DBGLVL_API, "  devicetype = 0x%x\n",
				exthdr->devicetype);
			अगर (exthdr->devicetype & 0x1)
				dprपूर्णांकk(DBGLVL_API, "   = Decoder Device\n");
			अगर (exthdr->devicetype & 0x2)
				dprपूर्णांकk(DBGLVL_API, "   = GPIO Source\n");
			अगर (exthdr->devicetype & 0x4)
				dprपूर्णांकk(DBGLVL_API, "   = Video Decoder\n");
			अगर (exthdr->devicetype & 0x8)
				dprपूर्णांकk(DBGLVL_API, "   = Audio Decoder\n");
			अगर (exthdr->devicetype & 0x20)
				dprपूर्णांकk(DBGLVL_API, "   = Crossbar\n");
			अगर (exthdr->devicetype & 0x40)
				dprपूर्णांकk(DBGLVL_API, "   = Tuner\n");
			अगर (exthdr->devicetype & 0x80)
				dprपूर्णांकk(DBGLVL_API, "   = IF PLL\n");
			अगर (exthdr->devicetype & 0x100)
				dprपूर्णांकk(DBGLVL_API, "   = Demodulator\n");
			अगर (exthdr->devicetype & 0x200)
				dprपूर्णांकk(DBGLVL_API, "   = RDS Decoder\n");
			अगर (exthdr->devicetype & 0x400)
				dprपूर्णांकk(DBGLVL_API, "   = Encoder\n");
			अगर (exthdr->devicetype & 0x800)
				dprपूर्णांकk(DBGLVL_API, "   = IR Decoder\n");
			अगर (exthdr->devicetype & 0x1000)
				dprपूर्णांकk(DBGLVL_API, "   = EEPROM\n");
			अगर (exthdr->devicetype & 0x2000)
				dprपूर्णांकk(DBGLVL_API,
					"   = VBI Decoder\n");
			अगर (exthdr->devicetype & 0x10000)
				dprपूर्णांकk(DBGLVL_API,
					"   = Streaming Device\n");
			अगर (exthdr->devicetype & 0x20000)
				dprपूर्णांकk(DBGLVL_API,
					"   = DRM Device\n");
			अगर (exthdr->devicetype & 0x40000000)
				dprपूर्णांकk(DBGLVL_API,
					"   = Generic Device\n");
			अगर (exthdr->devicetype & 0x80000000)
				dprपूर्णांकk(DBGLVL_API,
					"   = Config Space Device\n");
			dprपूर्णांकk(DBGLVL_API, "  numgpiopins = 0x%x\n",
				exthdr->numgpiopins);
			dprपूर्णांकk(DBGLVL_API, "  numgpiogroups = 0x%x\n",
				exthdr->numgpiogroups);
			dprपूर्णांकk(DBGLVL_API, "  controlsize = 0x%x\n",
				exthdr->controlsize);
			अगर (exthdr->devicetype & 0x80) अणु
				अगर (currpath == 1)
					encport = &dev->ports[SAA7164_PORT_ENC1];
				अन्यथा
					encport = &dev->ports[SAA7164_PORT_ENC2];
				स_नकल(&encport->अगरunit, exthdr,
					माप(काष्ठा पंचांगComResExtDevDescrHeader));
				dprपूर्णांकk(DBGLVL_API,
					"  (becomes dev->enc[%d])\n",
					encport->nr);
			पूर्ण
			अवरोध;
		हाल PVC_INFRARED_UNIT:
			dprपूर्णांकk(DBGLVL_API, " PVC_INFRARED_UNIT\n");
			अवरोध;
		हाल DRM_UNIT:
			dprपूर्णांकk(DBGLVL_API, " DRM_UNIT\n");
			अवरोध;
		शेष:
			dprपूर्णांकk(DBGLVL_API, "default %d\n", hdr->subtype);
		पूर्ण

		dprपूर्णांकk(DBGLVL_API, " 1.%x\n", hdr->len);
		dprपूर्णांकk(DBGLVL_API, " 2.%x\n", hdr->type);
		dprपूर्णांकk(DBGLVL_API, " 3.%x\n", hdr->subtype);
		dprपूर्णांकk(DBGLVL_API, " 4.%x\n", hdr->unitid);

		idx += hdr->len;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक saa7164_api_क्रमागत_subdevs(काष्ठा saa7164_dev *dev)
अणु
	पूर्णांक ret;
	u32 buflen = 0;
	u8 *buf;

	dprपूर्णांकk(DBGLVL_API, "%s()\n", __func__);

	/* Get the total descriptor length */
	ret = saa7164_cmd_send(dev, 0, GET_LEN,
		GET_DESCRIPTORS_CONTROL, माप(buflen), &buflen);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);

	dprपूर्णांकk(DBGLVL_API, "%s() total descriptor size = %d bytes.\n",
		__func__, buflen);

	/* Allocate enough storage क्रम all of the descs */
	buf = kzalloc(buflen, GFP_KERNEL);
	अगर (!buf)
		वापस SAA_ERR_NO_RESOURCES;

	/* Retrieve them */
	ret = saa7164_cmd_send(dev, 0, GET_CUR,
		GET_DESCRIPTORS_CONTROL, buflen, buf);
	अगर (ret != SAA_OK) अणु
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n", __func__, ret);
		जाओ out;
	पूर्ण

	अगर (saa_debug & DBGLVL_API)
		prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1, buf,
			       buflen & ~15, false);

	saa7164_api_dump_subdevs(dev, buf, buflen);

out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

पूर्णांक saa7164_api_i2c_पढ़ो(काष्ठा saa7164_i2c *bus, u8 addr, u32 reglen, u8 *reg,
	u32 datalen, u8 *data)
अणु
	काष्ठा saa7164_dev *dev = bus->dev;
	u16 len = 0;
	पूर्णांक unitid;
	u8 buf[256];
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s() addr=%x reglen=%d datalen=%d\n",
		__func__, addr, reglen, datalen);

	अगर (reglen > 4)
		वापस -EIO;

	/* Prepare the send buffer */
	/* Bytes 00-03 source रेजिस्टर length
	 *       04-07 source bytes to पढ़ो
	 *       08... रेजिस्टर address
	 */
	स_रखो(buf, 0, माप(buf));
	स_नकल((buf + 2 * माप(u32) + 0), reg, reglen);
	*((u32 *)(buf + 0 * माप(u32))) = reglen;
	*((u32 *)(buf + 1 * माप(u32))) = datalen;

	unitid = saa7164_i2caddr_to_unitid(bus, addr);
	अगर (unitid < 0) अणु
		prपूर्णांकk(KERN_ERR
			"%s() error, cannot translate regaddr 0x%x to unitid\n",
			__func__, addr);
		वापस -EIO;
	पूर्ण

	ret = saa7164_cmd_send(bus->dev, unitid, GET_LEN,
		EXU_REGISTER_ACCESS_CONTROL, माप(len), &len);
	अगर (ret != SAA_OK) अणु
		prपूर्णांकk(KERN_ERR "%s() error, ret(1) = 0x%x\n", __func__, ret);
		वापस -EIO;
	पूर्ण

	dprपूर्णांकk(DBGLVL_API, "%s() len = %d bytes\n", __func__, len);

	अगर (saa_debug & DBGLVL_I2C)
		prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1, buf,
			       32, false);

	ret = saa7164_cmd_send(bus->dev, unitid, GET_CUR,
		EXU_REGISTER_ACCESS_CONTROL, len, &buf);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret(2) = 0x%x\n", __func__, ret);
	अन्यथा अणु
		अगर (saa_debug & DBGLVL_I2C)
			prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1,
				       buf, माप(buf), false);
		स_नकल(data, (buf + 2 * माप(u32) + reglen), datalen);
	पूर्ण

	वापस ret == SAA_OK ? 0 : -EIO;
पूर्ण

/* For a given 8 bit i2c address device, ग_लिखो the buffer */
पूर्णांक saa7164_api_i2c_ग_लिखो(काष्ठा saa7164_i2c *bus, u8 addr, u32 datalen,
	u8 *data)
अणु
	काष्ठा saa7164_dev *dev = bus->dev;
	u16 len = 0;
	पूर्णांक unitid;
	पूर्णांक reglen;
	u8 buf[256];
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_API, "%s() addr=0x%2x len=0x%x\n",
		__func__, addr, datalen);

	अगर ((datalen == 0) || (datalen > 232))
		वापस -EIO;

	स_रखो(buf, 0, माप(buf));

	unitid = saa7164_i2caddr_to_unitid(bus, addr);
	अगर (unitid < 0) अणु
		prपूर्णांकk(KERN_ERR
			"%s() error, cannot translate regaddr 0x%x to unitid\n",
			__func__, addr);
		वापस -EIO;
	पूर्ण

	reglen = saa7164_i2caddr_to_reglen(bus, addr);
	अगर (reglen < 0) अणु
		prपूर्णांकk(KERN_ERR
			"%s() error, cannot translate regaddr to reglen\n",
			__func__);
		वापस -EIO;
	पूर्ण

	ret = saa7164_cmd_send(bus->dev, unitid, GET_LEN,
		EXU_REGISTER_ACCESS_CONTROL, माप(len), &len);
	अगर (ret != SAA_OK) अणु
		prपूर्णांकk(KERN_ERR "%s() error, ret(1) = 0x%x\n", __func__, ret);
		वापस -EIO;
	पूर्ण

	dprपूर्णांकk(DBGLVL_API, "%s() len = %d bytes unitid=0x%x\n", __func__,
		len, unitid);

	/* Prepare the send buffer */
	/* Bytes 00-03 dest रेजिस्टर length
	 *       04-07 dest bytes to ग_लिखो
	 *       08... रेजिस्टर address
	 */
	*((u32 *)(buf + 0 * माप(u32))) = reglen;
	*((u32 *)(buf + 1 * माप(u32))) = datalen - reglen;
	स_नकल((buf + 2 * माप(u32)), data, datalen);

	अगर (saa_debug & DBGLVL_I2C)
		prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1,
			       buf, माप(buf), false);

	ret = saa7164_cmd_send(bus->dev, unitid, SET_CUR,
		EXU_REGISTER_ACCESS_CONTROL, len, &buf);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret(2) = 0x%x\n", __func__, ret);

	वापस ret == SAA_OK ? 0 : -EIO;
पूर्ण

अटल पूर्णांक saa7164_api_modअगरy_gpio(काष्ठा saa7164_dev *dev, u8 unitid,
	u8 pin, u8 state)
अणु
	पूर्णांक ret;
	काष्ठा पंचांगComResGPIO t;

	dprपूर्णांकk(DBGLVL_API, "%s(0x%x, %d, %d)\n",
		__func__, unitid, pin, state);

	अगर ((pin > 7) || (state > 2))
		वापस SAA_ERR_BAD_PARAMETER;

	t.pin = pin;
	t.state = state;

	ret = saa7164_cmd_send(dev, unitid, SET_CUR,
		EXU_GPIO_CONTROL, माप(t), &t);
	अगर (ret != SAA_OK)
		prपूर्णांकk(KERN_ERR "%s() error, ret = 0x%x\n",
			__func__, ret);

	वापस ret;
पूर्ण

पूर्णांक saa7164_api_set_gpiobit(काष्ठा saa7164_dev *dev, u8 unitid,
	u8 pin)
अणु
	वापस saa7164_api_modअगरy_gpio(dev, unitid, pin, 1);
पूर्ण

पूर्णांक saa7164_api_clear_gpiobit(काष्ठा saa7164_dev *dev, u8 unitid,
	u8 pin)
अणु
	वापस saa7164_api_modअगरy_gpio(dev, unitid, pin, 0);
पूर्ण

