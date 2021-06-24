<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /*
    saa6752hs - i2c-driver क्रम the saa6752hs by Philips

    Copyright (C) 2004 Andrew de Quincey

    AC-3 support:

    Copyright (C) 2008 Hans Verkuil <hverkuil@xs4all.nl>

  */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/i2c.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/init.h>
#समावेश <linux/crc32.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-common.h>

#घोषणा MPEG_VIDEO_TARGET_BITRATE_MAX  27000
#घोषणा MPEG_VIDEO_MAX_BITRATE_MAX     27000
#घोषणा MPEG_TOTAL_TARGET_BITRATE_MAX  27000
#घोषणा MPEG_PID_MAX ((1 << 14) - 1)


MODULE_DESCRIPTION("device driver for saa6752hs MPEG2 encoder");
MODULE_AUTHOR("Andrew de Quincey");
MODULE_LICENSE("GPL");

क्रमागत saa6752hs_videoक्रमmat अणु
	SAA6752HS_VF_D1 = 0,    /* standard D1 video क्रमmat: 720x576 */
	SAA6752HS_VF_2_3_D1 = 1,/* 2/3D1 video क्रमmat: 480x576 */
	SAA6752HS_VF_1_2_D1 = 2,/* 1/2D1 video क्रमmat: 352x576 */
	SAA6752HS_VF_SIF = 3,   /* SIF video क्रमmat: 352x288 */
	SAA6752HS_VF_UNKNOWN,
पूर्ण;

काष्ठा saa6752hs_mpeg_params अणु
	/* transport streams */
	__u16				ts_pid_pmt;
	__u16				ts_pid_audio;
	__u16				ts_pid_video;
	__u16				ts_pid_pcr;

	/* audio */
	क्रमागत v4l2_mpeg_audio_encoding    au_encoding;
	क्रमागत v4l2_mpeg_audio_l2_bitrate  au_l2_bitrate;
	क्रमागत v4l2_mpeg_audio_ac3_bitrate au_ac3_bitrate;

	/* video */
	क्रमागत v4l2_mpeg_video_aspect	vi_aspect;
	क्रमागत v4l2_mpeg_video_bitrate_mode vi_bitrate_mode;
	__u32				vi_bitrate;
	__u32				vi_bitrate_peak;
पूर्ण;

अटल स्थिर काष्ठा v4l2_क्रमmat v4l2_क्रमmat_table[] =
अणु
	[SAA6752HS_VF_D1] =
		अणु .fmt = अणु .pix = अणु .width = 720, .height = 576 पूर्णपूर्णपूर्ण,
	[SAA6752HS_VF_2_3_D1] =
		अणु .fmt = अणु .pix = अणु .width = 480, .height = 576 पूर्णपूर्णपूर्ण,
	[SAA6752HS_VF_1_2_D1] =
		अणु .fmt = अणु .pix = अणु .width = 352, .height = 576 पूर्णपूर्णपूर्ण,
	[SAA6752HS_VF_SIF] =
		अणु .fmt = अणु .pix = अणु .width = 352, .height = 288 पूर्णपूर्णपूर्ण,
	[SAA6752HS_VF_UNKNOWN] =
		अणु .fmt = अणु .pix = अणु .width = 0, .height = 0पूर्णपूर्णपूर्ण,
पूर्ण;

काष्ठा saa6752hs_state अणु
	काष्ठा v4l2_subdev            sd;
	काष्ठा v4l2_ctrl_handler      hdl;
	काष्ठा अणु /* video bitrate mode control cluster */
		काष्ठा v4l2_ctrl *video_bitrate_mode;
		काष्ठा v4l2_ctrl *video_bitrate;
		काष्ठा v4l2_ctrl *video_bitrate_peak;
	पूर्ण;
	u32			      revision;
	पूर्णांक			      has_ac3;
	काष्ठा saa6752hs_mpeg_params  params;
	क्रमागत saa6752hs_videoक्रमmat    video_क्रमmat;
	v4l2_std_id                   standard;
पूर्ण;

क्रमागत saa6752hs_command अणु
	SAA6752HS_COMMAND_RESET = 0,
	SAA6752HS_COMMAND_STOP = 1,
	SAA6752HS_COMMAND_START = 2,
	SAA6752HS_COMMAND_PAUSE = 3,
	SAA6752HS_COMMAND_RECONFIGURE = 4,
	SAA6752HS_COMMAND_SLEEP = 5,
	SAA6752HS_COMMAND_RECONFIGURE_FORCE = 6,

	SAA6752HS_COMMAND_MAX
पूर्ण;

अटल अंतरभूत काष्ठा saa6752hs_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा saa6752hs_state, sd);
पूर्ण

/* ---------------------------------------------------------------------- */

अटल स्थिर u8 PAT[] = अणु
	0xc2, /* i2c रेजिस्टर */
	0x00, /* table number क्रम encoder */

	0x47, /* sync */
	0x40, 0x00, /* transport_error_indicator(0), payload_unit_start(1), transport_priority(0), pid(0) */
	0x10, /* transport_scrambling_control(00), adaptation_field_control(01), continuity_counter(0) */

	0x00, /* PSI poपूर्णांकer to start of table */

	0x00, /* tid(0) */
	0xb0, 0x0d, /* section_syntax_indicator(1), section_length(13) */

	0x00, 0x01, /* transport_stream_id(1) */

	0xc1, /* version_number(0), current_next_indicator(1) */

	0x00, 0x00, /* section_number(0), last_section_number(0) */

	0x00, 0x01, /* program_number(1) */

	0xe0, 0x00, /* PMT PID */

	0x00, 0x00, 0x00, 0x00 /* CRC32 */
पूर्ण;

अटल स्थिर u8 PMT[] = अणु
	0xc2, /* i2c रेजिस्टर */
	0x01, /* table number क्रम encoder */

	0x47, /* sync */
	0x40, 0x00, /* transport_error_indicator(0), payload_unit_start(1), transport_priority(0), pid */
	0x10, /* transport_scrambling_control(00), adaptation_field_control(01), continuity_counter(0) */

	0x00, /* PSI poपूर्णांकer to start of table */

	0x02, /* tid(2) */
	0xb0, 0x17, /* section_syntax_indicator(1), section_length(23) */

	0x00, 0x01, /* program_number(1) */

	0xc1, /* version_number(0), current_next_indicator(1) */

	0x00, 0x00, /* section_number(0), last_section_number(0) */

	0xe0, 0x00, /* PCR_PID */

	0xf0, 0x00, /* program_info_length(0) */

	0x02, 0xe0, 0x00, 0xf0, 0x00, /* video stream type(2), pid */
	0x04, 0xe0, 0x00, 0xf0, 0x00, /* audio stream type(4), pid */

	0x00, 0x00, 0x00, 0x00 /* CRC32 */
पूर्ण;

अटल स्थिर u8 PMT_AC3[] = अणु
	0xc2, /* i2c रेजिस्टर */
	0x01, /* table number क्रम encoder(1) */
	0x47, /* sync */

	0x40, /* transport_error_indicator(0), payload_unit_start(1), transport_priority(0) */
	0x10, /* PMT PID (0x0010) */
	0x10, /* transport_scrambling_control(00), adaptation_field_control(01), continuity_counter(0) */

	0x00, /* PSI poपूर्णांकer to start of table */

	0x02, /* TID (2) */
	0xb0, 0x1a, /* section_syntax_indicator(1), section_length(26) */

	0x00, 0x01, /* program_number(1) */

	0xc1, /* version_number(0), current_next_indicator(1) */

	0x00, 0x00, /* section_number(0), last_section_number(0) */

	0xe1, 0x04, /* PCR_PID (0x0104) */

	0xf0, 0x00, /* program_info_length(0) */

	0x02, 0xe1, 0x00, 0xf0, 0x00, /* video stream type(2), pid */
	0x06, 0xe1, 0x03, 0xf0, 0x03, /* audio stream type(6), pid */
	0x6a, /* AC3 */
	0x01, /* Descriptor_length(1) */
	0x00, /* component_type_flag(0), bsid_flag(0), मुख्यid_flag(0), asvc_flag(0), reserved flags(0) */

	0xED, 0xDE, 0x2D, 0xF3 /* CRC32 BE */
पूर्ण;

अटल स्थिर काष्ठा saa6752hs_mpeg_params param_शेषs =
अणु
	.ts_pid_pmt      = 16,
	.ts_pid_video    = 260,
	.ts_pid_audio    = 256,
	.ts_pid_pcr      = 259,

	.vi_aspect       = V4L2_MPEG_VIDEO_ASPECT_4x3,
	.vi_bitrate      = 4000,
	.vi_bitrate_peak = 6000,
	.vi_bitrate_mode = V4L2_MPEG_VIDEO_BITRATE_MODE_VBR,

	.au_encoding     = V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
	.au_l2_bitrate   = V4L2_MPEG_AUDIO_L2_BITRATE_256K,
	.au_ac3_bitrate  = V4L2_MPEG_AUDIO_AC3_BITRATE_256K,
पूर्ण;

/* ---------------------------------------------------------------------- */

अटल पूर्णांक saa6752hs_chip_command(काष्ठा i2c_client *client,
				  क्रमागत saa6752hs_command command)
अणु
	अचिन्हित अक्षर buf[3];
	अचिन्हित दीर्घ समयout;
	पूर्णांक status = 0;

	/* execute the command */
	चयन(command) अणु
	हाल SAA6752HS_COMMAND_RESET:
		buf[0] = 0x00;
		अवरोध;

	हाल SAA6752HS_COMMAND_STOP:
		buf[0] = 0x03;
		अवरोध;

	हाल SAA6752HS_COMMAND_START:
		buf[0] = 0x02;
		अवरोध;

	हाल SAA6752HS_COMMAND_PAUSE:
		buf[0] = 0x04;
		अवरोध;

	हाल SAA6752HS_COMMAND_RECONFIGURE:
		buf[0] = 0x05;
		अवरोध;

	हाल SAA6752HS_COMMAND_SLEEP:
		buf[0] = 0x06;
		अवरोध;

	हाल SAA6752HS_COMMAND_RECONFIGURE_FORCE:
		buf[0] = 0x07;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set it and रुको क्रम it to be so */
	i2c_master_send(client, buf, 1);
	समयout = jअगरfies + HZ * 3;
	क्रम (;;) अणु
		/* get the current status */
		buf[0] = 0x10;
		i2c_master_send(client, buf, 1);
		i2c_master_recv(client, buf, 1);

		अगर (!(buf[0] & 0x20))
			अवरोध;
		अगर (समय_after(jअगरfies,समयout)) अणु
			status = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		msleep(10);
	पूर्ण

	/* delay a bit to let encoder settle */
	msleep(50);

	वापस status;
पूर्ण


अटल अंतरभूत व्योम set_reg8(काष्ठा i2c_client *client, uपूर्णांक8_t reg, uपूर्णांक8_t val)
अणु
	u8 buf[2];

	buf[0] = reg;
	buf[1] = val;
	i2c_master_send(client, buf, 2);
पूर्ण

अटल अंतरभूत व्योम set_reg16(काष्ठा i2c_client *client, uपूर्णांक8_t reg, uपूर्णांक16_t val)
अणु
	u8 buf[3];

	buf[0] = reg;
	buf[1] = val >> 8;
	buf[2] = val & 0xff;
	i2c_master_send(client, buf, 3);
पूर्ण

अटल पूर्णांक saa6752hs_set_bitrate(काष्ठा i2c_client *client,
				 काष्ठा saa6752hs_state *h)
अणु
	काष्ठा saa6752hs_mpeg_params *params = &h->params;
	पूर्णांक tot_bitrate;
	पूर्णांक is_384k;

	/* set the bitrate mode */
	set_reg8(client, 0x71,
		params->vi_bitrate_mode != V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);

	/* set the video bitrate */
	अगर (params->vi_bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR) अणु
		/* set the target bitrate */
		set_reg16(client, 0x80, params->vi_bitrate);

		/* set the max bitrate */
		set_reg16(client, 0x81, params->vi_bitrate_peak);
		tot_bitrate = params->vi_bitrate_peak;
	पूर्ण अन्यथा अणु
		/* set the target bitrate (no max bitrate क्रम CBR) */
		set_reg16(client, 0x81, params->vi_bitrate);
		tot_bitrate = params->vi_bitrate;
	पूर्ण

	/* set the audio encoding */
	set_reg8(client, 0x93,
			params->au_encoding == V4L2_MPEG_AUDIO_ENCODING_AC3);

	/* set the audio bitrate */
	अगर (params->au_encoding == V4L2_MPEG_AUDIO_ENCODING_AC3)
		is_384k = V4L2_MPEG_AUDIO_AC3_BITRATE_384K == params->au_ac3_bitrate;
	अन्यथा
		is_384k = V4L2_MPEG_AUDIO_L2_BITRATE_384K == params->au_l2_bitrate;
	set_reg8(client, 0x94, is_384k);
	tot_bitrate += is_384k ? 384 : 256;

	/* Note: the total max bitrate is determined by adding the video and audio
	   bitrates together and also adding an extra 768kbit/s to stay on the
	   safe side. If more control should be required, then an extra MPEG control
	   should be added. */
	tot_bitrate += 768;
	अगर (tot_bitrate > MPEG_TOTAL_TARGET_BITRATE_MAX)
		tot_bitrate = MPEG_TOTAL_TARGET_BITRATE_MAX;

	/* set the total bitrate */
	set_reg16(client, 0xb1, tot_bitrate);
	वापस 0;
पूर्ण

अटल पूर्णांक saa6752hs_try_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा saa6752hs_state *h =
		container_of(ctrl->handler, काष्ठा saa6752hs_state, hdl);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		/* peak bitrate shall be >= normal bitrate */
		अगर (ctrl->val == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
		    h->video_bitrate_peak->val < h->video_bitrate->val)
			h->video_bitrate_peak->val = h->video_bitrate->val;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa6752hs_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा saa6752hs_state *h =
		container_of(ctrl->handler, काष्ठा saa6752hs_state, hdl);
	काष्ठा saa6752hs_mpeg_params *params = &h->params;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_MPEG_STREAM_TYPE:
		अवरोध;
	हाल V4L2_CID_MPEG_STREAM_PID_PMT:
		params->ts_pid_pmt = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_STREAM_PID_AUDIO:
		params->ts_pid_audio = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_STREAM_PID_VIDEO:
		params->ts_pid_video = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_STREAM_PID_PCR:
		params->ts_pid_pcr = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_ENCODING:
		params->au_encoding = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		params->au_l2_bitrate = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		params->au_ac3_bitrate = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_ENCODING:
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_ASPECT:
		params->vi_aspect = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		params->vi_bitrate_mode = ctrl->val;
		params->vi_bitrate = h->video_bitrate->val / 1000;
		params->vi_bitrate_peak = h->video_bitrate_peak->val / 1000;
		v4l2_ctrl_activate(h->video_bitrate_peak,
				ctrl->val == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa6752hs_init(काष्ठा v4l2_subdev *sd, u32 leading_null_bytes)
अणु
	अचिन्हित अक्षर buf[9], buf2[4];
	काष्ठा saa6752hs_state *h = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	अचिन्हित size;
	u32 crc;
	अचिन्हित अक्षर localPAT[256];
	अचिन्हित अक्षर localPMT[256];

	/* Set video क्रमmat - must be करोne first as it resets other settings */
	set_reg8(client, 0x41, h->video_क्रमmat);

	/* Set number of lines in input संकेत */
	set_reg8(client, 0x40, (h->standard & V4L2_STD_525_60) ? 1 : 0);

	/* set bitrate */
	saa6752hs_set_bitrate(client, h);

	/* Set GOP काष्ठाure अणु3, 13पूर्ण */
	set_reg16(client, 0x72, 0x030d);

	/* Set minimum Q-scale अणु4पूर्ण */
	set_reg8(client, 0x82, 0x04);

	/* Set maximum Q-scale अणु12पूर्ण */
	set_reg8(client, 0x83, 0x0c);

	/* Set Output Protocol */
	set_reg8(client, 0xd0, 0x81);

	/* Set video output stream क्रमmat अणुTSपूर्ण */
	set_reg8(client, 0xb0, 0x05);

	/* Set leading null byte क्रम TS */
	set_reg16(client, 0xf6, leading_null_bytes);

	/* compute PAT */
	स_नकल(localPAT, PAT, माप(PAT));
	localPAT[17] = 0xe0 | ((h->params.ts_pid_pmt >> 8) & 0x0f);
	localPAT[18] = h->params.ts_pid_pmt & 0xff;
	crc = crc32_be(~0, &localPAT[7], माप(PAT) - 7 - 4);
	localPAT[माप(PAT) - 4] = (crc >> 24) & 0xFF;
	localPAT[माप(PAT) - 3] = (crc >> 16) & 0xFF;
	localPAT[माप(PAT) - 2] = (crc >> 8) & 0xFF;
	localPAT[माप(PAT) - 1] = crc & 0xFF;

	/* compute PMT */
	अगर (h->params.au_encoding == V4L2_MPEG_AUDIO_ENCODING_AC3) अणु
		size = माप(PMT_AC3);
		स_नकल(localPMT, PMT_AC3, size);
	पूर्ण अन्यथा अणु
		size = माप(PMT);
		स_नकल(localPMT, PMT, size);
	पूर्ण
	localPMT[3] = 0x40 | ((h->params.ts_pid_pmt >> 8) & 0x0f);
	localPMT[4] = h->params.ts_pid_pmt & 0xff;
	localPMT[15] = 0xE0 | ((h->params.ts_pid_pcr >> 8) & 0x0F);
	localPMT[16] = h->params.ts_pid_pcr & 0xFF;
	localPMT[20] = 0xE0 | ((h->params.ts_pid_video >> 8) & 0x0F);
	localPMT[21] = h->params.ts_pid_video & 0xFF;
	localPMT[25] = 0xE0 | ((h->params.ts_pid_audio >> 8) & 0x0F);
	localPMT[26] = h->params.ts_pid_audio & 0xFF;
	crc = crc32_be(~0, &localPMT[7], size - 7 - 4);
	localPMT[size - 4] = (crc >> 24) & 0xFF;
	localPMT[size - 3] = (crc >> 16) & 0xFF;
	localPMT[size - 2] = (crc >> 8) & 0xFF;
	localPMT[size - 1] = crc & 0xFF;

	/* Set Audio PID */
	set_reg16(client, 0xc1, h->params.ts_pid_audio);

	/* Set Video PID */
	set_reg16(client, 0xc0, h->params.ts_pid_video);

	/* Set PCR PID */
	set_reg16(client, 0xc4, h->params.ts_pid_pcr);

	/* Send SI tables */
	i2c_master_send(client, localPAT, माप(PAT));
	i2c_master_send(client, localPMT, size);

	/* mute then unmute audio. This हटाओs buzzing artefacts */
	set_reg8(client, 0xa4, 1);
	set_reg8(client, 0xa4, 0);

	/* start it going */
	saa6752hs_chip_command(client, SAA6752HS_COMMAND_START);

	/* पढ़ोout current state */
	buf[0] = 0xE1;
	buf[1] = 0xA7;
	buf[2] = 0xFE;
	buf[3] = 0x82;
	buf[4] = 0xB0;
	i2c_master_send(client, buf, 5);
	i2c_master_recv(client, buf2, 4);

	/* change aspect ratio */
	buf[0] = 0xE0;
	buf[1] = 0xA7;
	buf[2] = 0xFE;
	buf[3] = 0x82;
	buf[4] = 0xB0;
	buf[5] = buf2[0];
	चयन (h->params.vi_aspect) अणु
	हाल V4L2_MPEG_VIDEO_ASPECT_16x9:
		buf[6] = buf2[1] | 0x40;
		अवरोध;
	हाल V4L2_MPEG_VIDEO_ASPECT_4x3:
	शेष:
		buf[6] = buf2[1] & 0xBF;
		अवरोध;
	पूर्ण
	buf[7] = buf2[2];
	buf[8] = buf2[3];
	i2c_master_send(client, buf, 9);

	वापस 0;
पूर्ण

अटल पूर्णांक saa6752hs_get_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *f = &क्रमmat->क्रमmat;
	काष्ठा saa6752hs_state *h = to_state(sd);

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	अगर (h->video_क्रमmat == SAA6752HS_VF_UNKNOWN)
		h->video_क्रमmat = SAA6752HS_VF_D1;
	f->width = v4l2_क्रमmat_table[h->video_क्रमmat].fmt.pix.width;
	f->height = v4l2_क्रमmat_table[h->video_क्रमmat].fmt.pix.height;
	f->code = MEDIA_BUS_FMT_FIXED;
	f->field = V4L2_FIELD_INTERLACED;
	f->colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

अटल पूर्णांक saa6752hs_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *f = &क्रमmat->क्रमmat;
	काष्ठा saa6752hs_state *h = to_state(sd);
	पूर्णांक dist_352, dist_480, dist_720;

	अगर (क्रमmat->pad)
		वापस -EINVAL;

	f->code = MEDIA_BUS_FMT_FIXED;

	dist_352 = असल(f->width - 352);
	dist_480 = असल(f->width - 480);
	dist_720 = असल(f->width - 720);
	अगर (dist_720 < dist_480) अणु
		f->width = 720;
		f->height = 576;
	पूर्ण अन्यथा अगर (dist_480 < dist_352) अणु
		f->width = 480;
		f->height = 576;
	पूर्ण अन्यथा अणु
		f->width = 352;
		अगर (असल(f->height - 576) < असल(f->height - 288))
			f->height = 576;
		अन्यथा
			f->height = 288;
	पूर्ण
	f->field = V4L2_FIELD_INTERLACED;
	f->colorspace = V4L2_COLORSPACE_SMPTE170M;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		cfg->try_fmt = *f;
		वापस 0;
	पूर्ण

	/*
	  FIXME: translate and round width/height पूर्णांकo EMPRESS
	  subsample type:

	  type   |   PAL   |  NTSC
	  ---------------------------
	  SIF    | 352x288 | 352x240
	  1/2 D1 | 352x576 | 352x480
	  2/3 D1 | 480x576 | 480x480
	  D1     | 720x576 | 720x480
	*/

	अगर (f->code != MEDIA_BUS_FMT_FIXED)
		वापस -EINVAL;

	अगर (f->width == 720)
		h->video_क्रमmat = SAA6752HS_VF_D1;
	अन्यथा अगर (f->width == 480)
		h->video_क्रमmat = SAA6752HS_VF_2_3_D1;
	अन्यथा अगर (f->height == 576)
		h->video_क्रमmat = SAA6752HS_VF_1_2_D1;
	अन्यथा
		h->video_क्रमmat = SAA6752HS_VF_SIF;
	वापस 0;
पूर्ण

अटल पूर्णांक saa6752hs_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id std)
अणु
	काष्ठा saa6752hs_state *h = to_state(sd);

	h->standard = std;
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops saa6752hs_ctrl_ops = अणु
	.try_ctrl = saa6752hs_try_ctrl,
	.s_ctrl = saa6752hs_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops saa6752hs_core_ops = अणु
	.init = saa6752hs_init,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops saa6752hs_video_ops = अणु
	.s_std = saa6752hs_s_std,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops saa6752hs_pad_ops = अणु
	.get_fmt = saa6752hs_get_fmt,
	.set_fmt = saa6752hs_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops saa6752hs_ops = अणु
	.core = &saa6752hs_core_ops,
	.video = &saa6752hs_video_ops,
	.pad = &saa6752hs_pad_ops,
पूर्ण;

अटल पूर्णांक saa6752hs_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा saa6752hs_state *h;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_ctrl_handler *hdl;
	u8 addr = 0x13;
	u8 data[12];

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	h = devm_kzalloc(&client->dev, माप(*h), GFP_KERNEL);
	अगर (h == शून्य)
		वापस -ENOMEM;
	sd = &h->sd;
	v4l2_i2c_subdev_init(sd, client, &saa6752hs_ops);

	i2c_master_send(client, &addr, 1);
	i2c_master_recv(client, data, माप(data));
	h->revision = (data[8] << 8) | data[9];
	h->has_ac3 = 0;
	अगर (h->revision == 0x0206) अणु
		h->has_ac3 = 1;
		v4l_info(client, "supports AC-3\n");
	पूर्ण
	h->params = param_शेषs;

	hdl = &h->hdl;
	v4l2_ctrl_handler_init(hdl, 14);
	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_AUDIO_ENCODING,
		h->has_ac3 ? V4L2_MPEG_AUDIO_ENCODING_AC3 :
			V4L2_MPEG_AUDIO_ENCODING_LAYER_2,
		0x0d, V4L2_MPEG_AUDIO_ENCODING_LAYER_2);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_AUDIO_L2_BITRATE,
		V4L2_MPEG_AUDIO_L2_BITRATE_384K,
		~((1 << V4L2_MPEG_AUDIO_L2_BITRATE_256K) |
		  (1 << V4L2_MPEG_AUDIO_L2_BITRATE_384K)),
		V4L2_MPEG_AUDIO_L2_BITRATE_256K);

	अगर (h->has_ac3)
		v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
			V4L2_CID_MPEG_AUDIO_AC3_BITRATE,
			V4L2_MPEG_AUDIO_AC3_BITRATE_384K,
			~((1 << V4L2_MPEG_AUDIO_AC3_BITRATE_256K) |
			  (1 << V4L2_MPEG_AUDIO_AC3_BITRATE_384K)),
			V4L2_MPEG_AUDIO_AC3_BITRATE_256K);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ,
		V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000,
		~(1 << V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000),
		V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_ENCODING,
		V4L2_MPEG_VIDEO_ENCODING_MPEG_2,
		~(1 << V4L2_MPEG_VIDEO_ENCODING_MPEG_2),
		V4L2_MPEG_VIDEO_ENCODING_MPEG_2);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_ASPECT,
		V4L2_MPEG_VIDEO_ASPECT_16x9, 0x01,
		V4L2_MPEG_VIDEO_ASPECT_4x3);

	h->video_bitrate_peak = v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_PEAK,
		1000000, 27000000, 1000, 8000000);

	v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_TYPE,
		V4L2_MPEG_STREAM_TYPE_MPEG2_TS,
		~(1 << V4L2_MPEG_STREAM_TYPE_MPEG2_TS),
		V4L2_MPEG_STREAM_TYPE_MPEG2_TS);

	h->video_bitrate_mode = v4l2_ctrl_new_std_menu(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
		V4L2_MPEG_VIDEO_BITRATE_MODE_CBR, 0,
		V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);
	h->video_bitrate = v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE, 1000000, 27000000, 1000, 6000000);
	v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_PID_PMT, 0, (1 << 14) - 1, 1, 16);
	v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_PID_AUDIO, 0, (1 << 14) - 1, 1, 260);
	v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_PID_VIDEO, 0, (1 << 14) - 1, 1, 256);
	v4l2_ctrl_new_std(hdl, &saa6752hs_ctrl_ops,
		V4L2_CID_MPEG_STREAM_PID_PCR, 0, (1 << 14) - 1, 1, 259);
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		पूर्णांक err = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		वापस err;
	पूर्ण
	v4l2_ctrl_cluster(3, &h->video_bitrate_mode);
	v4l2_ctrl_handler_setup(hdl);
	h->standard = 0; /* Assume 625 input lines */
	वापस 0;
पूर्ण

अटल पूर्णांक saa6752hs_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);

	v4l2_device_unरेजिस्टर_subdev(sd);
	v4l2_ctrl_handler_मुक्त(&to_state(sd)->hdl);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id saa6752hs_id[] = अणु
	अणु "saa6752hs", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, saa6752hs_id);

अटल काष्ठा i2c_driver saa6752hs_driver = अणु
	.driver = अणु
		.name	= "saa6752hs",
	पूर्ण,
	.probe		= saa6752hs_probe,
	.हटाओ		= saa6752hs_हटाओ,
	.id_table	= saa6752hs_id,
पूर्ण;

module_i2c_driver(saa6752hs_driver);
