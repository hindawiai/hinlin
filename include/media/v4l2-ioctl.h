<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 *	V 4 L 2   D R I V E R   H E L P E R   A P I
 *
 * Moved from videodev2.h
 *
 *	Some commonly needed functions क्रम drivers (v4l2-common.o module)
 */
#अगर_अघोषित _V4L2_IOCTL_H
#घोषणा _V4L2_IOCTL_H

#समावेश <linux/poll.h>
#समावेश <linux/fs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/compiler.h> /* need __user */
#समावेश <linux/videodev2.h>

काष्ठा v4l2_fh;

/**
 * काष्ठा v4l2_ioctl_ops - describe operations क्रम each V4L2 ioctl
 *
 * @vidioc_querycap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_QUERYCAP <vidioc_querycap>` ioctl
 * @vidioc_क्रमागत_fmt_vid_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FMT <vidioc_क्रमागत_fmt>` ioctl logic
 *	क्रम video capture in single and multi plane mode
 * @vidioc_क्रमागत_fmt_vid_overlay: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FMT <vidioc_क्रमागत_fmt>` ioctl logic
 *	क्रम video overlay
 * @vidioc_क्रमागत_fmt_vid_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FMT <vidioc_क्रमागत_fmt>` ioctl logic
 *	क्रम video output in single and multi plane mode
 * @vidioc_क्रमागत_fmt_sdr_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FMT <vidioc_क्रमागत_fmt>` ioctl logic
 *	क्रम Software Defined Radio capture
 * @vidioc_क्रमागत_fmt_sdr_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FMT <vidioc_क्रमागत_fmt>` ioctl logic
 *	क्रम Software Defined Radio output
 * @vidioc_क्रमागत_fmt_meta_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FMT <vidioc_क्रमागत_fmt>` ioctl logic
 *	क्रम metadata capture
 * @vidioc_क्रमागत_fmt_meta_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FMT <vidioc_क्रमागत_fmt>` ioctl logic
 *	क्रम metadata output
 * @vidioc_g_fmt_vid_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम video capture
 *	in single plane mode
 * @vidioc_g_fmt_vid_overlay: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम video overlay
 * @vidioc_g_fmt_vid_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम video out
 *	in single plane mode
 * @vidioc_g_fmt_vid_out_overlay: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम video overlay output
 * @vidioc_g_fmt_vbi_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम raw VBI capture
 * @vidioc_g_fmt_vbi_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम raw VBI output
 * @vidioc_g_fmt_sliced_vbi_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम sliced VBI capture
 * @vidioc_g_fmt_sliced_vbi_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम sliced VBI output
 * @vidioc_g_fmt_vid_cap_mplane: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम video capture
 *	in multiple plane mode
 * @vidioc_g_fmt_vid_out_mplane: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम video out
 *	in multiplane plane mode
 * @vidioc_g_fmt_sdr_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम Software Defined
 *	Radio capture
 * @vidioc_g_fmt_sdr_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम Software Defined
 *	Radio output
 * @vidioc_g_fmt_meta_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम metadata capture
 * @vidioc_g_fmt_meta_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FMT <vidioc_g_fmt>` ioctl logic क्रम metadata output
 * @vidioc_s_fmt_vid_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम video capture
 *	in single plane mode
 * @vidioc_s_fmt_vid_overlay: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम video overlay
 * @vidioc_s_fmt_vid_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम video out
 *	in single plane mode
 * @vidioc_s_fmt_vid_out_overlay: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम video overlay output
 * @vidioc_s_fmt_vbi_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम raw VBI capture
 * @vidioc_s_fmt_vbi_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम raw VBI output
 * @vidioc_s_fmt_sliced_vbi_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम sliced VBI capture
 * @vidioc_s_fmt_sliced_vbi_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम sliced VBI output
 * @vidioc_s_fmt_vid_cap_mplane: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम video capture
 *	in multiple plane mode
 * @vidioc_s_fmt_vid_out_mplane: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम video out
 *	in multiplane plane mode
 * @vidioc_s_fmt_sdr_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम Software Defined
 *	Radio capture
 * @vidioc_s_fmt_sdr_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम Software Defined
 *	Radio output
 * @vidioc_s_fmt_meta_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम metadata capture
 * @vidioc_s_fmt_meta_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FMT <vidioc_g_fmt>` ioctl logic क्रम metadata output
 * @vidioc_try_fmt_vid_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम video capture
 *	in single plane mode
 * @vidioc_try_fmt_vid_overlay: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम video overlay
 * @vidioc_try_fmt_vid_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम video out
 *	in single plane mode
 * @vidioc_try_fmt_vid_out_overlay: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम video overlay
 *	output
 * @vidioc_try_fmt_vbi_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम raw VBI capture
 * @vidioc_try_fmt_vbi_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम raw VBI output
 * @vidioc_try_fmt_sliced_vbi_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम sliced VBI
 *	capture
 * @vidioc_try_fmt_sliced_vbi_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम sliced VBI output
 * @vidioc_try_fmt_vid_cap_mplane: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम video capture
 *	in multiple plane mode
 * @vidioc_try_fmt_vid_out_mplane: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम video out
 *	in multiplane plane mode
 * @vidioc_try_fmt_sdr_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम Software Defined
 *	Radio capture
 * @vidioc_try_fmt_sdr_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम Software Defined
 *	Radio output
 * @vidioc_try_fmt_meta_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम metadata capture
 * @vidioc_try_fmt_meta_out: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_FMT <vidioc_g_fmt>` ioctl logic क्रम metadata output
 * @vidioc_reqbufs: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_REQBUFS <vidioc_reqbufs>` ioctl
 * @vidioc_querybuf: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_QUERYBUF <vidioc_querybuf>` ioctl
 * @vidioc_qbuf: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_QBUF <vidioc_qbuf>` ioctl
 * @vidioc_expbuf: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_EXPBUF <vidioc_expbuf>` ioctl
 * @vidioc_dqbuf: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_DQBUF <vidioc_qbuf>` ioctl
 * @vidioc_create_bufs: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_CREATE_BUFS <vidioc_create_bufs>` ioctl
 * @vidioc_prepare_buf: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_PREPARE_BUF <vidioc_prepare_buf>` ioctl
 * @vidioc_overlay: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_OVERLAY <vidioc_overlay>` ioctl
 * @vidioc_g_fbuf: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FBUF <vidioc_g_fbuf>` ioctl
 * @vidioc_s_fbuf: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FBUF <vidioc_g_fbuf>` ioctl
 * @vidioc_streamon: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_STREAMON <vidioc_streamon>` ioctl
 * @vidioc_streamoff: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_STREAMOFF <vidioc_streamon>` ioctl
 * @vidioc_g_std: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_STD <vidioc_g_std>` ioctl
 * @vidioc_s_std: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_STD <vidioc_g_std>` ioctl
 * @vidioc_querystd: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_QUERYSTD <vidioc_querystd>` ioctl
 * @vidioc_क्रमागत_input: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_INPUT <vidioc_g_input>` ioctl
 * @vidioc_g_input: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_INPUT <vidioc_g_input>` ioctl
 * @vidioc_s_input: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_INPUT <vidioc_g_input>` ioctl
 * @vidioc_क्रमागत_output: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_OUTPUT <vidioc_g_output>` ioctl
 * @vidioc_g_output: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_OUTPUT <vidioc_g_output>` ioctl
 * @vidioc_s_output: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_OUTPUT <vidioc_g_output>` ioctl
 * @vidioc_queryctrl: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_QUERYCTRL <vidioc_queryctrl>` ioctl
 * @vidioc_query_ext_ctrl: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_QUERY_EXT_CTRL <vidioc_queryctrl>` ioctl
 * @vidioc_g_ctrl: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_CTRL <vidioc_g_ctrl>` ioctl
 * @vidioc_s_ctrl: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_CTRL <vidioc_g_ctrl>` ioctl
 * @vidioc_g_ext_ctrls: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_EXT_CTRLS <vidioc_g_ext_ctrls>` ioctl
 * @vidioc_s_ext_ctrls: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_EXT_CTRLS <vidioc_g_ext_ctrls>` ioctl
 * @vidioc_try_ext_ctrls: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_EXT_CTRLS <vidioc_g_ext_ctrls>` ioctl
 * @vidioc_querymenu: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_QUERYMENU <vidioc_queryctrl>` ioctl
 * @vidioc_क्रमागतaudio: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUMAUDIO <vidioc_क्रमागतaudio>` ioctl
 * @vidioc_g_audio: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_AUDIO <vidioc_g_audio>` ioctl
 * @vidioc_s_audio: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_AUDIO <vidioc_g_audio>` ioctl
 * @vidioc_क्रमागतauकरोut: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUMAUDOUT <vidioc_क्रमागतauकरोut>` ioctl
 * @vidioc_g_auकरोut: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_AUDOUT <vidioc_g_auकरोut>` ioctl
 * @vidioc_s_auकरोut: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_AUDOUT <vidioc_g_auकरोut>` ioctl
 * @vidioc_g_modulator: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_MODULATOR <vidioc_g_modulator>` ioctl
 * @vidioc_s_modulator: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_MODULATOR <vidioc_g_modulator>` ioctl
 * @vidioc_g_pixelaspect: poपूर्णांकer to the function that implements
 *	the pixelaspect part of the :ref:`VIDIOC_CROPCAP <vidioc_cropcap>` ioctl
 * @vidioc_g_selection: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_SELECTION <vidioc_g_selection>` ioctl
 * @vidioc_s_selection: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_SELECTION <vidioc_g_selection>` ioctl
 * @vidioc_g_jpegcomp: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_JPEGCOMP <vidioc_g_jpegcomp>` ioctl
 * @vidioc_s_jpegcomp: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_JPEGCOMP <vidioc_g_jpegcomp>` ioctl
 * @vidioc_g_enc_index: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_ENC_INDEX <vidioc_g_enc_index>` ioctl
 * @vidioc_encoder_cmd: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENCODER_CMD <vidioc_encoder_cmd>` ioctl
 * @vidioc_try_encoder_cmd: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_ENCODER_CMD <vidioc_encoder_cmd>` ioctl
 * @vidioc_decoder_cmd: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_DECODER_CMD <vidioc_decoder_cmd>` ioctl
 * @vidioc_try_decoder_cmd: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_TRY_DECODER_CMD <vidioc_decoder_cmd>` ioctl
 * @vidioc_g_parm: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_PARM <vidioc_g_parm>` ioctl
 * @vidioc_s_parm: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_PARM <vidioc_g_parm>` ioctl
 * @vidioc_g_tuner: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_TUNER <vidioc_g_tuner>` ioctl
 * @vidioc_s_tuner: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_TUNER <vidioc_g_tuner>` ioctl
 * @vidioc_g_frequency: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_FREQUENCY <vidioc_g_frequency>` ioctl
 * @vidioc_s_frequency: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_FREQUENCY <vidioc_g_frequency>` ioctl
 * @vidioc_क्रमागत_freq_bands: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FREQ_BANDS <vidioc_क्रमागत_freq_bands>` ioctl
 * @vidioc_g_sliced_vbi_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_SLICED_VBI_CAP <vidioc_g_sliced_vbi_cap>` ioctl
 * @vidioc_log_status: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_LOG_STATUS <vidioc_log_status>` ioctl
 * @vidioc_s_hw_freq_seek: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_HW_FREQ_SEEK <vidioc_s_hw_freq_seek>` ioctl
 * @vidioc_g_रेजिस्टर: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_DBG_G_REGISTER <vidioc_dbg_g_रेजिस्टर>` ioctl
 * @vidioc_s_रेजिस्टर: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_DBG_S_REGISTER <vidioc_dbg_g_रेजिस्टर>` ioctl
 * @vidioc_g_chip_info: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_DBG_G_CHIP_INFO <vidioc_dbg_g_chip_info>` ioctl
 * @vidioc_क्रमागत_framesizes: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FRAMESIZES <vidioc_क्रमागत_framesizes>` ioctl
 * @vidioc_क्रमागत_frameपूर्णांकervals: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_FRAMEINTERVALS <vidioc_क्रमागत_frameपूर्णांकervals>` ioctl
 * @vidioc_s_dv_timings: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_DV_TIMINGS <vidioc_g_dv_timings>` ioctl
 * @vidioc_g_dv_timings: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_DV_TIMINGS <vidioc_g_dv_timings>` ioctl
 * @vidioc_query_dv_timings: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_QUERY_DV_TIMINGS <vidioc_query_dv_timings>` ioctl
 * @vidioc_क्रमागत_dv_timings: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_ENUM_DV_TIMINGS <vidioc_क्रमागत_dv_timings>` ioctl
 * @vidioc_dv_timings_cap: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_DV_TIMINGS_CAP <vidioc_dv_timings_cap>` ioctl
 * @vidioc_g_edid: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_G_EDID <vidioc_g_edid>` ioctl
 * @vidioc_s_edid: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_S_EDID <vidioc_g_edid>` ioctl
 * @vidioc_subscribe_event: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_SUBSCRIBE_EVENT <vidioc_subscribe_event>` ioctl
 * @vidioc_unsubscribe_event: poपूर्णांकer to the function that implements
 *	:ref:`VIDIOC_UNSUBSCRIBE_EVENT <vidioc_unsubscribe_event>` ioctl
 * @vidioc_शेष: poपूर्णांकed used to allow other ioctls
 */
काष्ठा v4l2_ioctl_ops अणु
	/* ioctl callbacks */

	/* VIDIOC_QUERYCAP handler */
	पूर्णांक (*vidioc_querycap)(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_capability *cap);

	/* VIDIOC_ENUM_FMT handlers */
	पूर्णांक (*vidioc_क्रमागत_fmt_vid_cap)(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_fmtdesc *f);
	पूर्णांक (*vidioc_क्रमागत_fmt_vid_overlay)(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_fmtdesc *f);
	पूर्णांक (*vidioc_क्रमागत_fmt_vid_out)(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_fmtdesc *f);
	पूर्णांक (*vidioc_क्रमागत_fmt_sdr_cap)(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_fmtdesc *f);
	पूर्णांक (*vidioc_क्रमागत_fmt_sdr_out)(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_fmtdesc *f);
	पूर्णांक (*vidioc_क्रमागत_fmt_meta_cap)(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_fmtdesc *f);
	पूर्णांक (*vidioc_क्रमागत_fmt_meta_out)(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_fmtdesc *f);

	/* VIDIOC_G_FMT handlers */
	पूर्णांक (*vidioc_g_fmt_vid_cap)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_vid_overlay)(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_vid_out)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_vid_out_overlay)(काष्ठा file *file, व्योम *fh,
					    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_vbi_cap)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_vbi_out)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_sliced_vbi_cap)(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_sliced_vbi_out)(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_vid_cap_mplane)(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_vid_out_mplane)(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_sdr_cap)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_sdr_out)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_meta_cap)(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_g_fmt_meta_out)(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_क्रमmat *f);

	/* VIDIOC_S_FMT handlers */
	पूर्णांक (*vidioc_s_fmt_vid_cap)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_vid_overlay)(काष्ठा file *file, व्योम *fh,
					काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_vid_out)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_vid_out_overlay)(काष्ठा file *file, व्योम *fh,
					    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_vbi_cap)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_vbi_out)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_sliced_vbi_cap)(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_sliced_vbi_out)(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_vid_cap_mplane)(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_vid_out_mplane)(काष्ठा file *file, व्योम *fh,
					   काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_sdr_cap)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_sdr_out)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_meta_cap)(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_s_fmt_meta_out)(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_क्रमmat *f);

	/* VIDIOC_TRY_FMT handlers */
	पूर्णांक (*vidioc_try_fmt_vid_cap)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_vid_overlay)(काष्ठा file *file, व्योम *fh,
					  काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_vid_out)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_vid_out_overlay)(काष्ठा file *file, व्योम *fh,
					     काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_vbi_cap)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_vbi_out)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_sliced_vbi_cap)(काष्ठा file *file, व्योम *fh,
					     काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_sliced_vbi_out)(काष्ठा file *file, व्योम *fh,
					     काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_vid_cap_mplane)(काष्ठा file *file, व्योम *fh,
					     काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_vid_out_mplane)(काष्ठा file *file, व्योम *fh,
					     काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_sdr_cap)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_sdr_out)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_meta_cap)(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_क्रमmat *f);
	पूर्णांक (*vidioc_try_fmt_meta_out)(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_क्रमmat *f);

	/* Buffer handlers */
	पूर्णांक (*vidioc_reqbufs)(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_requestbuffers *b);
	पूर्णांक (*vidioc_querybuf)(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_buffer *b);
	पूर्णांक (*vidioc_qbuf)(काष्ठा file *file, व्योम *fh,
			   काष्ठा v4l2_buffer *b);
	पूर्णांक (*vidioc_expbuf)(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_exportbuffer *e);
	पूर्णांक (*vidioc_dqbuf)(काष्ठा file *file, व्योम *fh,
			    काष्ठा v4l2_buffer *b);

	पूर्णांक (*vidioc_create_bufs)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_create_buffers *b);
	पूर्णांक (*vidioc_prepare_buf)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_buffer *b);

	पूर्णांक (*vidioc_overlay)(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक i);
	पूर्णांक (*vidioc_g_fbuf)(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_framebuffer *a);
	पूर्णांक (*vidioc_s_fbuf)(काष्ठा file *file, व्योम *fh,
			     स्थिर काष्ठा v4l2_framebuffer *a);

		/* Stream on/off */
	पूर्णांक (*vidioc_streamon)(काष्ठा file *file, व्योम *fh,
			       क्रमागत v4l2_buf_type i);
	पूर्णांक (*vidioc_streamoff)(काष्ठा file *file, व्योम *fh,
				क्रमागत v4l2_buf_type i);

		/*
		 * Standard handling
		 *
		 * Note: ENUMSTD is handled by videodev.c
		 */
	पूर्णांक (*vidioc_g_std)(काष्ठा file *file, व्योम *fh, v4l2_std_id *norm);
	पूर्णांक (*vidioc_s_std)(काष्ठा file *file, व्योम *fh, v4l2_std_id norm);
	पूर्णांक (*vidioc_querystd)(काष्ठा file *file, व्योम *fh, v4l2_std_id *a);

		/* Input handling */
	पूर्णांक (*vidioc_क्रमागत_input)(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_input *inp);
	पूर्णांक (*vidioc_g_input)(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i);
	पूर्णांक (*vidioc_s_input)(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक i);

		/* Output handling */
	पूर्णांक (*vidioc_क्रमागत_output)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_output *a);
	पूर्णांक (*vidioc_g_output)(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i);
	पूर्णांक (*vidioc_s_output)(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक i);

		/* Control handling */
	पूर्णांक (*vidioc_queryctrl)(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_queryctrl *a);
	पूर्णांक (*vidioc_query_ext_ctrl)(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_query_ext_ctrl *a);
	पूर्णांक (*vidioc_g_ctrl)(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_control *a);
	पूर्णांक (*vidioc_s_ctrl)(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_control *a);
	पूर्णांक (*vidioc_g_ext_ctrls)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_ext_controls *a);
	पूर्णांक (*vidioc_s_ext_ctrls)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_ext_controls *a);
	पूर्णांक (*vidioc_try_ext_ctrls)(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_ext_controls *a);
	पूर्णांक (*vidioc_querymenu)(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_querymenu *a);

	/* Audio ioctls */
	पूर्णांक (*vidioc_क्रमागतaudio)(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_audio *a);
	पूर्णांक (*vidioc_g_audio)(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_audio *a);
	पूर्णांक (*vidioc_s_audio)(काष्ठा file *file, व्योम *fh,
			      स्थिर काष्ठा v4l2_audio *a);

	/* Audio out ioctls */
	पूर्णांक (*vidioc_क्रमागतauकरोut)(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_audioout *a);
	पूर्णांक (*vidioc_g_auकरोut)(काष्ठा file *file, व्योम *fh,
			       काष्ठा v4l2_audioout *a);
	पूर्णांक (*vidioc_s_auकरोut)(काष्ठा file *file, व्योम *fh,
			       स्थिर काष्ठा v4l2_audioout *a);
	पूर्णांक (*vidioc_g_modulator)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_modulator *a);
	पूर्णांक (*vidioc_s_modulator)(काष्ठा file *file, व्योम *fh,
				  स्थिर काष्ठा v4l2_modulator *a);
	/* Crop ioctls */
	पूर्णांक (*vidioc_g_pixelaspect)(काष्ठा file *file, व्योम *fh,
				    पूर्णांक buf_type, काष्ठा v4l2_fract *aspect);
	पूर्णांक (*vidioc_g_selection)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_selection *s);
	पूर्णांक (*vidioc_s_selection)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_selection *s);
	/* Compression ioctls */
	पूर्णांक (*vidioc_g_jpegcomp)(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_jpegcompression *a);
	पूर्णांक (*vidioc_s_jpegcomp)(काष्ठा file *file, व्योम *fh,
				 स्थिर काष्ठा v4l2_jpegcompression *a);
	पूर्णांक (*vidioc_g_enc_index)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_enc_idx *a);
	पूर्णांक (*vidioc_encoder_cmd)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_encoder_cmd *a);
	पूर्णांक (*vidioc_try_encoder_cmd)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_encoder_cmd *a);
	पूर्णांक (*vidioc_decoder_cmd)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_decoder_cmd *a);
	पूर्णांक (*vidioc_try_decoder_cmd)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_decoder_cmd *a);

	/* Stream type-dependent parameter ioctls */
	पूर्णांक (*vidioc_g_parm)(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_streamparm *a);
	पूर्णांक (*vidioc_s_parm)(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_streamparm *a);

	/* Tuner ioctls */
	पूर्णांक (*vidioc_g_tuner)(काष्ठा file *file, व्योम *fh,
			      काष्ठा v4l2_tuner *a);
	पूर्णांक (*vidioc_s_tuner)(काष्ठा file *file, व्योम *fh,
			      स्थिर काष्ठा v4l2_tuner *a);
	पूर्णांक (*vidioc_g_frequency)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_frequency *a);
	पूर्णांक (*vidioc_s_frequency)(काष्ठा file *file, व्योम *fh,
				  स्थिर काष्ठा v4l2_frequency *a);
	पूर्णांक (*vidioc_क्रमागत_freq_bands)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_frequency_band *band);

	/* Sliced VBI cap */
	पूर्णांक (*vidioc_g_sliced_vbi_cap)(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_sliced_vbi_cap *a);

	/* Log status ioctl */
	पूर्णांक (*vidioc_log_status)(काष्ठा file *file, व्योम *fh);

	पूर्णांक (*vidioc_s_hw_freq_seek)(काष्ठा file *file, व्योम *fh,
				     स्थिर काष्ठा v4l2_hw_freq_seek *a);

	/* Debugging ioctls */
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	पूर्णांक (*vidioc_g_रेजिस्टर)(काष्ठा file *file, व्योम *fh,
				 काष्ठा v4l2_dbg_रेजिस्टर *reg);
	पूर्णांक (*vidioc_s_रेजिस्टर)(काष्ठा file *file, व्योम *fh,
				 स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg);

	पूर्णांक (*vidioc_g_chip_info)(काष्ठा file *file, व्योम *fh,
				  काष्ठा v4l2_dbg_chip_info *chip);
#पूर्ण_अगर

	पूर्णांक (*vidioc_क्रमागत_framesizes)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_frmsizeक्रमागत *fsize);

	पूर्णांक (*vidioc_क्रमागत_frameपूर्णांकervals)(काष्ठा file *file, व्योम *fh,
					  काष्ठा v4l2_frmivalक्रमागत *fival);

	/* DV Timings IOCTLs */
	पूर्णांक (*vidioc_s_dv_timings)(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_dv_timings *timings);
	पूर्णांक (*vidioc_g_dv_timings)(काष्ठा file *file, व्योम *fh,
				   काष्ठा v4l2_dv_timings *timings);
	पूर्णांक (*vidioc_query_dv_timings)(काष्ठा file *file, व्योम *fh,
				       काष्ठा v4l2_dv_timings *timings);
	पूर्णांक (*vidioc_क्रमागत_dv_timings)(काष्ठा file *file, व्योम *fh,
				      काष्ठा v4l2_क्रमागत_dv_timings *timings);
	पूर्णांक (*vidioc_dv_timings_cap)(काष्ठा file *file, व्योम *fh,
				     काष्ठा v4l2_dv_timings_cap *cap);
	पूर्णांक (*vidioc_g_edid)(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_edid *edid);
	पूर्णांक (*vidioc_s_edid)(काष्ठा file *file, व्योम *fh,
			     काष्ठा v4l2_edid *edid);

	पूर्णांक (*vidioc_subscribe_event)(काष्ठा v4l2_fh *fh,
				      स्थिर काष्ठा v4l2_event_subscription *sub);
	पूर्णांक (*vidioc_unsubscribe_event)(काष्ठा v4l2_fh *fh,
					स्थिर काष्ठा v4l2_event_subscription *sub);

	/* For other निजी ioctls */
	दीर्घ (*vidioc_शेष)(काष्ठा file *file, व्योम *fh,
			       bool valid_prio, अचिन्हित पूर्णांक cmd, व्योम *arg);
पूर्ण;


/* v4l debugging and diagnostics */

/* Device debug flags to be used with the video device debug attribute */

/* Just log the ioctl name + error code */
#घोषणा V4L2_DEV_DEBUG_IOCTL		0x01
/* Log the ioctl name arguments + error code */
#घोषणा V4L2_DEV_DEBUG_IOCTL_ARG	0x02
/* Log the file operations खोलो, release, mmap and get_unmapped_area */
#घोषणा V4L2_DEV_DEBUG_FOP		0x04
/* Log the पढ़ो and ग_लिखो file operations and the VIDIOC_(D)QBUF ioctls */
#घोषणा V4L2_DEV_DEBUG_STREAMING	0x08
/* Log poll() */
#घोषणा V4L2_DEV_DEBUG_POLL		0x10
/* Log controls */
#घोषणा V4L2_DEV_DEBUG_CTRL		0x20

/*  Video standard functions  */

/**
 * v4l2_norm_to_name - Ancillary routine to analog TV standard name from its ID.
 *
 * @id:	analog TV standard ID.
 *
 * Return: वापसs a string with the name of the analog TV standard.
 * If the standard is not found or अगर @id poपूर्णांकs to multiple standard,
 * it वापसs "Unknown".
 */
स्थिर अक्षर *v4l2_norm_to_name(v4l2_std_id id);

/**
 * v4l2_video_std_frame_period - Ancillary routine that fills a
 *	काष्ठा &v4l2_fract poपूर्णांकer with the शेष framerate fraction.
 *
 * @id: analog TV standard ID.
 * @frameperiod: काष्ठा &v4l2_fract poपूर्णांकer to be filled
 *
 */
व्योम v4l2_video_std_frame_period(पूर्णांक id, काष्ठा v4l2_fract *frameperiod);

/**
 * v4l2_video_std_स्थिरruct - Ancillary routine that fills in the fields of
 *	a &v4l2_standard काष्ठाure according to the @id parameter.
 *
 * @vs: काष्ठा &v4l2_standard poपूर्णांकer to be filled
 * @id: analog TV standard ID.
 * @name: name of the standard to be used
 *
 * .. note::
 *
 *    This ancillary routine is obsolete. Shouldn't be used on newer drivers.
 */
पूर्णांक v4l2_video_std_स्थिरruct(काष्ठा v4l2_standard *vs,
				    पूर्णांक id, स्थिर अक्षर *name);

/**
 * v4l_video_std_क्रमागतstd - Ancillary routine that fills in the fields of
 *	a &v4l2_standard काष्ठाure according to the @id and @vs->index
 *	parameters.
 *
 * @vs: काष्ठा &v4l2_standard poपूर्णांकer to be filled.
 * @id: analog TV standard ID.
 *
 */
पूर्णांक v4l_video_std_क्रमागतstd(काष्ठा v4l2_standard *vs, v4l2_std_id id);

/**
 * v4l_prपूर्णांकk_ioctl - Ancillary routine that prपूर्णांकs the ioctl in a
 *	human-पढ़ोable क्रमmat.
 *
 * @prefix: prefix to be added at the ioctl prपूर्णांकs.
 * @cmd: ioctl name
 *
 * .. note::
 *
 *    If prefix != %शून्य, then it will issue a
 *    ``prपूर्णांकk(KERN_DEBUG "%s: ", prefix)`` first.
 */
व्योम v4l_prपूर्णांकk_ioctl(स्थिर अक्षर *prefix, अचिन्हित पूर्णांक cmd);

काष्ठा video_device;

/* names क्रम fancy debug output */
बाह्य स्थिर अक्षर *v4l2_field_names[];
बाह्य स्थिर अक्षर *v4l2_type_names[];

#अगर_घोषित CONFIG_COMPAT
/**
 * v4l2_compat_ioctl32 -32 Bits compatibility layer क्रम 64 bits processors
 *
 * @file: Poपूर्णांकer to काष्ठा &file.
 * @cmd: Ioctl name.
 * @arg: Ioctl argument.
 */
दीर्घ पूर्णांक v4l2_compat_ioctl32(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg);
#पूर्ण_अगर

अचिन्हित पूर्णांक v4l2_compat_translate_cmd(अचिन्हित पूर्णांक cmd);
पूर्णांक v4l2_compat_get_user(व्योम __user *arg, व्योम *parg, अचिन्हित पूर्णांक cmd);
पूर्णांक v4l2_compat_put_user(व्योम __user *arg, व्योम *parg, अचिन्हित पूर्णांक cmd);
पूर्णांक v4l2_compat_get_array_args(काष्ठा file *file, व्योम *mbuf,
			       व्योम __user *user_ptr, माप_प्रकार array_size,
			       अचिन्हित पूर्णांक cmd, व्योम *arg);
पूर्णांक v4l2_compat_put_array_args(काष्ठा file *file, व्योम __user *user_ptr,
			       व्योम *mbuf, माप_प्रकार array_size,
			       अचिन्हित पूर्णांक cmd, व्योम *arg);

/**
 * प्रकार v4l2_kioctl - Typedef used to pass an ioctl handler.
 *
 * @file: Poपूर्णांकer to काष्ठा &file.
 * @cmd: Ioctl name.
 * @arg: Ioctl argument.
 */
प्रकार दीर्घ (*v4l2_kioctl)(काष्ठा file *file, अचिन्हित पूर्णांक cmd, व्योम *arg);

/**
 * video_usercopy - copies data from/to userspace memory when an ioctl is
 *	issued.
 *
 * @file: Poपूर्णांकer to काष्ठा &file.
 * @cmd: Ioctl name.
 * @arg: Ioctl argument.
 * @func: function that will handle the ioctl
 *
 * .. note::
 *
 *    This routine should be used only inside the V4L2 core.
 */
दीर्घ पूर्णांक video_usercopy(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ पूर्णांक arg, v4l2_kioctl func);

/**
 * video_ioctl2 - Handles a V4L2 ioctl.
 *
 * @file: Poपूर्णांकer to काष्ठा &file.
 * @cmd: Ioctl name.
 * @arg: Ioctl argument.
 *
 * Method used to hancle an ioctl. Should be used to fill the
 * &v4l2_ioctl_ops.unlocked_ioctl on all V4L2 drivers.
 */
दीर्घ पूर्णांक video_ioctl2(काष्ठा file *file,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ पूर्णांक arg);

/*
 * The user space पूर्णांकerpretation of the 'v4l2_event' dअगरfers
 * based on the 'time_t' definition on 32-bit architectures, so
 * the kernel has to handle both.
 * This is the old version क्रम 32-bit architectures.
 */
काष्ठा v4l2_event_समय32 अणु
	__u32				type;
	जोड़ अणु
		काष्ठा v4l2_event_vsync		vsync;
		काष्ठा v4l2_event_ctrl		ctrl;
		काष्ठा v4l2_event_frame_sync	frame_sync;
		काष्ठा v4l2_event_src_change	src_change;
		काष्ठा v4l2_event_motion_det	motion_det;
		__u8				data[64];
	पूर्ण u;
	__u32				pending;
	__u32				sequence;
	काष्ठा old_बारpec32		बारtamp;
	__u32				id;
	__u32				reserved[8];
पूर्ण;

#घोषणा	VIDIOC_DQEVENT_TIME32	 _IOR('V', 89, काष्ठा v4l2_event_समय32)

काष्ठा v4l2_buffer_समय32 अणु
	__u32			index;
	__u32			type;
	__u32			bytesused;
	__u32			flags;
	__u32			field;
	काष्ठा old_समयval32	बारtamp;
	काष्ठा v4l2_समयcode	समयcode;
	__u32			sequence;

	/* memory location */
	__u32			memory;
	जोड़ अणु
		__u32           offset;
		अचिन्हित दीर्घ   userptr;
		काष्ठा v4l2_plane *planes;
		__s32		fd;
	पूर्ण m;
	__u32			length;
	__u32			reserved2;
	जोड़ अणु
		__s32		request_fd;
		__u32		reserved;
	पूर्ण;
पूर्ण;
#घोषणा VIDIOC_QUERYBUF_TIME32	_IOWR('V',  9, काष्ठा v4l2_buffer_समय32)
#घोषणा VIDIOC_QBUF_TIME32	_IOWR('V', 15, काष्ठा v4l2_buffer_समय32)
#घोषणा VIDIOC_DQBUF_TIME32	_IOWR('V', 17, काष्ठा v4l2_buffer_समय32)
#घोषणा VIDIOC_PREPARE_BUF_TIME32 _IOWR('V', 93, काष्ठा v4l2_buffer_समय32)

#पूर्ण_अगर /* _V4L2_IOCTL_H */
