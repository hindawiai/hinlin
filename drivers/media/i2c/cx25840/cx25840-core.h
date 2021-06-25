<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* cx25840 पूर्णांकernal API header
 *
 * Copyright (C) 2003-2004 Chris Kennedy
 */

#अगर_अघोषित _CX25840_CORE_H_
#घोषणा _CX25840_CORE_H_

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <linux/i2c.h>

काष्ठा cx25840_ir_state;

क्रमागत cx25840_model अणु
	CX23885_AV,
	CX23887_AV,
	CX23888_AV,
	CX2310X_AV,
	CX25840,
	CX25841,
	CX25842,
	CX25843,
	CX25836,
	CX25837,
पूर्ण;

क्रमागत cx25840_media_pads अणु
	CX25840_PAD_INPUT,
	CX25840_PAD_VID_OUT,

	CX25840_NUM_PADS
पूर्ण;

/**
 * काष्ठा cx25840_state - a device instance निजी data
 * @c:			i2c_client काष्ठा representing this device
 * @sd:		our V4L2 sub-device
 * @hdl:		our V4L2 control handler
 * @volume:		audio volume V4L2 control (non-cx2583x devices only)
 * @mute:		audio mute V4L2 control (non-cx2583x devices only)
 * @pvr150_workaround:	whether we enable workaround क्रम Hauppauge PVR150
 *			hardware bug (audio dropping out)
 * @generic_mode:	whether we disable ivtv-specअगरic hacks
 *			this mode माला_लो turned on when the bridge driver calls
 *			cx25840 subdevice init core op
 * @radio:		set अगर we are currently in the radio mode, otherwise
 *			the current mode is non-radio (that is, video)
 * @std:		currently set video standard
 * @vid_input:		currently set video input
 * @vid_config:	currently set video output configuration
 *			only used in the generic mode
 * @aud_input:		currently set audio input
 * @audclk_freq:	currently set audio sample rate
 * @audmode:		currently set audio mode (when in non-radio mode)
 * @vbi_line_offset:	vbi line number offset
 * @id:		exact device model
 * @rev:		raw device id पढ़ो from the chip
 * @is_initialized:	whether we have alपढ़ोy loaded firmware पूर्णांकo the chip
 *			and initialized it
 * @vbi_regs_offset:	offset of vbi regs
 * @fw_रुको:		रुको queue to wake an initialization function up when
 *			firmware loading (on a separate workqueue) finishes
 * @fw_work:		a work that actually loads the firmware on a separate
 *			workqueue
 * @ir_state:		a poपूर्णांकer to chip IR controller निजी data
 * @pads:		array of supported chip pads (currently only a stub)
 */
काष्ठा cx25840_state अणु
	काष्ठा i2c_client *c;
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा अणु
		/* volume cluster */
		काष्ठा v4l2_ctrl *volume;
		काष्ठा v4l2_ctrl *mute;
	पूर्ण;
	पूर्णांक pvr150_workaround;
	bool generic_mode;
	पूर्णांक radio;
	v4l2_std_id std;
	क्रमागत cx25840_video_input vid_input;
	u32 vid_config;
	क्रमागत cx25840_audio_input aud_input;
	u32 audclk_freq;
	पूर्णांक audmode;
	पूर्णांक vbi_line_offset;
	क्रमागत cx25840_model id;
	u32 rev;
	पूर्णांक is_initialized;
	अचिन्हित पूर्णांक vbi_regs_offset;
	रुको_queue_head_t fw_रुको;
	काष्ठा work_काष्ठा fw_work;
	काष्ठा cx25840_ir_state *ir_state;
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_pad	pads[CX25840_NUM_PADS];
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा cx25840_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा cx25840_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा cx25840_state, hdl)->sd;
पूर्ण

अटल अंतरभूत bool is_cx2583x(काष्ठा cx25840_state *state)
अणु
	वापस state->id == CX25836 ||
	       state->id == CX25837;
पूर्ण

अटल अंतरभूत bool is_cx2584x(काष्ठा cx25840_state *state)
अणु
	वापस state->id == CX25840 ||
	       state->id == CX25841 ||
	       state->id == CX25842 ||
	       state->id == CX25843;
पूर्ण

अटल अंतरभूत bool is_cx231xx(काष्ठा cx25840_state *state)
अणु
	वापस state->id == CX2310X_AV;
पूर्ण

अटल अंतरभूत bool is_cx2388x(काष्ठा cx25840_state *state)
अणु
	वापस state->id == CX23885_AV ||
	       state->id == CX23887_AV ||
	       state->id == CX23888_AV;
पूर्ण

अटल अंतरभूत bool is_cx23885(काष्ठा cx25840_state *state)
अणु
	वापस state->id == CX23885_AV;
पूर्ण

अटल अंतरभूत bool is_cx23887(काष्ठा cx25840_state *state)
अणु
	वापस state->id == CX23887_AV;
पूर्ण

अटल अंतरभूत bool is_cx23888(काष्ठा cx25840_state *state)
अणु
	वापस state->id == CX23888_AV;
पूर्ण

/* ----------------------------------------------------------------------- */
/* cx25850-core.c							   */
पूर्णांक cx25840_ग_लिखो(काष्ठा i2c_client *client, u16 addr, u8 value);
पूर्णांक cx25840_ग_लिखो4(काष्ठा i2c_client *client, u16 addr, u32 value);
u8 cx25840_पढ़ो(काष्ठा i2c_client *client, u16 addr);
u32 cx25840_पढ़ो4(काष्ठा i2c_client *client, u16 addr);
पूर्णांक cx25840_and_or(काष्ठा i2c_client *client, u16 addr, अचिन्हित पूर्णांक mask,
		   u8 value);
पूर्णांक cx25840_and_or4(काष्ठा i2c_client *client, u16 addr, u32 and_mask,
		    u32 or_value);
व्योम cx25840_std_setup(काष्ठा i2c_client *client);

/* ----------------------------------------------------------------------- */
/* cx25850-firmware.c                                                      */
पूर्णांक cx25840_loadfw(काष्ठा i2c_client *client);

/* ----------------------------------------------------------------------- */
/* cx25850-audio.c                                                         */
व्योम cx25840_audio_set_path(काष्ठा i2c_client *client);
पूर्णांक cx25840_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq);

बाह्य स्थिर काष्ठा v4l2_ctrl_ops cx25840_audio_ctrl_ops;

/* ----------------------------------------------------------------------- */
/* cx25850-vbi.c                                                           */
पूर्णांक cx25840_s_raw_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_vbi_क्रमmat *fmt);
पूर्णांक cx25840_s_sliced_fmt(काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_sliced_vbi_क्रमmat *fmt);
पूर्णांक cx25840_g_sliced_fmt(काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_sliced_vbi_क्रमmat *fmt);
पूर्णांक cx25840_decode_vbi_line(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_decode_vbi_line *vbi);

/* ----------------------------------------------------------------------- */
/* cx25850-ir.c                                                            */
बाह्य स्थिर काष्ठा v4l2_subdev_ir_ops cx25840_ir_ops;
पूर्णांक cx25840_ir_log_status(काष्ठा v4l2_subdev *sd);
पूर्णांक cx25840_ir_irq_handler(काष्ठा v4l2_subdev *sd, u32 status, bool *handled);
पूर्णांक cx25840_ir_probe(काष्ठा v4l2_subdev *sd);
पूर्णांक cx25840_ir_हटाओ(काष्ठा v4l2_subdev *sd);

#पूर्ण_अगर
