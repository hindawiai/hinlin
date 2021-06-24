<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>
#समावेश "pvrusb2.h"
#समावेश "pvrusb2-std.h"
#समावेश "pvrusb2-util.h"
#समावेश "pvrusb2-hdw.h"
#समावेश "pvrusb2-i2c-core.h"
#समावेश "pvrusb2-eeprom.h"
#समावेश "pvrusb2-hdw-internal.h"
#समावेश "pvrusb2-encoder.h"
#समावेश "pvrusb2-debug.h"
#समावेश "pvrusb2-fx2-cmd.h"
#समावेश "pvrusb2-wm8775.h"
#समावेश "pvrusb2-video-v4l.h"
#समावेश "pvrusb2-cx2584x-v4l.h"
#समावेश "pvrusb2-cs53l32a.h"
#समावेश "pvrusb2-audio.h"

#घोषणा TV_MIN_FREQ     55250000L
#घोषणा TV_MAX_FREQ    850000000L

/* This defines a minimum पूर्णांकerval that the decoder must reमुख्य quiet
   beक्रमe we are allowed to start it running. */
#घोषणा TIME_MSEC_DECODER_WAIT 50

/* This defines a minimum पूर्णांकerval that the decoder must be allowed to run
   beक्रमe we can safely begin using its streaming output. */
#घोषणा TIME_MSEC_DECODER_STABILIZATION_WAIT 300

/* This defines a minimum पूर्णांकerval that the encoder must reमुख्य quiet
   beक्रमe we are allowed to configure it. */
#घोषणा TIME_MSEC_ENCODER_WAIT 50

/* This defines the minimum पूर्णांकerval that the encoder must successfully run
   beक्रमe we consider that the encoder has run at least once since its
   firmware has been loaded.  This measurement is in important क्रम हालs
   where we can't करो something until we know that the encoder has been run
   at least once. */
#घोषणा TIME_MSEC_ENCODER_OK 250

अटल काष्ठा pvr2_hdw *unit_poपूर्णांकers[PVR_NUM] = अणु[ 0 ... PVR_NUM-1 ] = शून्यपूर्ण;
अटल DEFINE_MUTEX(pvr2_unit_mtx);

अटल पूर्णांक ctlchg;
अटल पूर्णांक procreload;
अटल पूर्णांक tuner[PVR_NUM] = अणु [0 ... PVR_NUM-1] = -1 पूर्ण;
अटल पूर्णांक tolerance[PVR_NUM] = अणु [0 ... PVR_NUM-1] = 0 पूर्ण;
अटल पूर्णांक video_std[PVR_NUM] = अणु [0 ... PVR_NUM-1] = 0 पूर्ण;
अटल पूर्णांक init_छोड़ो_msec;

module_param(ctlchg, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ctlchg, "0=optimize ctl change 1=always accept new ctl value");
module_param(init_छोड़ो_msec, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(init_छोड़ो_msec, "hardware initialization settling delay");
module_param(procreload, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(procreload,
		 "Attempt init failure recovery with firmware reload");
module_param_array(tuner,    पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(tuner,"specify installed tuner type");
module_param_array(video_std,    पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(video_std,"specify initial video standard");
module_param_array(tolerance,    पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(tolerance,"specify stream error tolerance");

/* US Broadcast channel 3 (61.25 MHz), to help with testing */
अटल पूर्णांक शेष_tv_freq    = 61250000L;
/* 104.3 MHz, a usable FM station क्रम my area */
अटल पूर्णांक शेष_radio_freq = 104300000L;

module_param_named(tv_freq, शेष_tv_freq, पूर्णांक, 0444);
MODULE_PARM_DESC(tv_freq, "specify initial television frequency");
module_param_named(radio_freq, शेष_radio_freq, पूर्णांक, 0444);
MODULE_PARM_DESC(radio_freq, "specify initial radio frequency");

#घोषणा PVR2_CTL_WRITE_ENDPOINT  0x01
#घोषणा PVR2_CTL_READ_ENDPOINT   0x81

#घोषणा PVR2_GPIO_IN 0x9008
#घोषणा PVR2_GPIO_OUT 0x900c
#घोषणा PVR2_GPIO_सूची 0x9020

#घोषणा trace_firmware(...) pvr2_trace(PVR2_TRACE_FIRMWARE,__VA_ARGS__)

#घोषणा PVR2_FIRMWARE_ENDPOINT   0x02

/* size of a firmware chunk */
#घोषणा FIRMWARE_CHUNK_SIZE 0x2000

प्रकार व्योम (*pvr2_subdev_update_func)(काष्ठा pvr2_hdw *,
					काष्ठा v4l2_subdev *);

अटल स्थिर pvr2_subdev_update_func pvr2_module_update_functions[] = अणु
	[PVR2_CLIENT_ID_WM8775] = pvr2_wm8775_subdev_update,
	[PVR2_CLIENT_ID_SAA7115] = pvr2_saa7115_subdev_update,
	[PVR2_CLIENT_ID_MSP3400] = pvr2_msp3400_subdev_update,
	[PVR2_CLIENT_ID_CX25840] = pvr2_cx25840_subdev_update,
	[PVR2_CLIENT_ID_CS53L32A] = pvr2_cs53l32a_subdev_update,
पूर्ण;

अटल स्थिर अक्षर *module_names[] = अणु
	[PVR2_CLIENT_ID_MSP3400] = "msp3400",
	[PVR2_CLIENT_ID_CX25840] = "cx25840",
	[PVR2_CLIENT_ID_SAA7115] = "saa7115",
	[PVR2_CLIENT_ID_TUNER] = "tuner",
	[PVR2_CLIENT_ID_DEMOD] = "tuner",
	[PVR2_CLIENT_ID_CS53L32A] = "cs53l32a",
	[PVR2_CLIENT_ID_WM8775] = "wm8775",
पूर्ण;


अटल स्थिर अचिन्हित अक्षर *module_i2c_addresses[] = अणु
	[PVR2_CLIENT_ID_TUNER] = "\x60\x61\x62\x63",
	[PVR2_CLIENT_ID_DEMOD] = "\x43",
	[PVR2_CLIENT_ID_MSP3400] = "\x40",
	[PVR2_CLIENT_ID_SAA7115] = "\x21",
	[PVR2_CLIENT_ID_WM8775] = "\x1b",
	[PVR2_CLIENT_ID_CX25840] = "\x44",
	[PVR2_CLIENT_ID_CS53L32A] = "\x11",
पूर्ण;


अटल स्थिर अक्षर *ir_scheme_names[] = अणु
	[PVR2_IR_SCHEME_NONE] = "none",
	[PVR2_IR_SCHEME_29XXX] = "29xxx",
	[PVR2_IR_SCHEME_24XXX] = "24xxx (29xxx emulation)",
	[PVR2_IR_SCHEME_24XXX_MCE] = "24xxx (MCE device)",
	[PVR2_IR_SCHEME_ZILOG] = "Zilog",
पूर्ण;


/* Define the list of additional controls we'll dynamically स्थिरruct based
   on query of the cx2341x module. */
काष्ठा pvr2_mpeg_ids अणु
	स्थिर अक्षर *strid;
	पूर्णांक id;
पूर्ण;
अटल स्थिर काष्ठा pvr2_mpeg_ids mpeg_ids[] = अणु
	अणु
		.strid = "audio_layer",
		.id = V4L2_CID_MPEG_AUDIO_ENCODING,
	पूर्ण,अणु
		.strid = "audio_bitrate",
		.id = V4L2_CID_MPEG_AUDIO_L2_BITRATE,
	पूर्ण,अणु
		/* Alपढ़ोy using audio_mode अन्यथाwhere :-( */
		.strid = "mpeg_audio_mode",
		.id = V4L2_CID_MPEG_AUDIO_MODE,
	पूर्ण,अणु
		.strid = "mpeg_audio_mode_extension",
		.id = V4L2_CID_MPEG_AUDIO_MODE_EXTENSION,
	पूर्ण,अणु
		.strid = "audio_emphasis",
		.id = V4L2_CID_MPEG_AUDIO_EMPHASIS,
	पूर्ण,अणु
		.strid = "audio_crc",
		.id = V4L2_CID_MPEG_AUDIO_CRC,
	पूर्ण,अणु
		.strid = "video_aspect",
		.id = V4L2_CID_MPEG_VIDEO_ASPECT,
	पूर्ण,अणु
		.strid = "video_b_frames",
		.id = V4L2_CID_MPEG_VIDEO_B_FRAMES,
	पूर्ण,अणु
		.strid = "video_gop_size",
		.id = V4L2_CID_MPEG_VIDEO_GOP_SIZE,
	पूर्ण,अणु
		.strid = "video_gop_closure",
		.id = V4L2_CID_MPEG_VIDEO_GOP_CLOSURE,
	पूर्ण,अणु
		.strid = "video_bitrate_mode",
		.id = V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
	पूर्ण,अणु
		.strid = "video_bitrate",
		.id = V4L2_CID_MPEG_VIDEO_BITRATE,
	पूर्ण,अणु
		.strid = "video_bitrate_peak",
		.id = V4L2_CID_MPEG_VIDEO_BITRATE_PEAK,
	पूर्ण,अणु
		.strid = "video_temporal_decimation",
		.id = V4L2_CID_MPEG_VIDEO_TEMPORAL_DECIMATION,
	पूर्ण,अणु
		.strid = "stream_type",
		.id = V4L2_CID_MPEG_STREAM_TYPE,
	पूर्ण,अणु
		.strid = "video_spatial_filter_mode",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER_MODE,
	पूर्ण,अणु
		.strid = "video_spatial_filter",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_SPATIAL_FILTER,
	पूर्ण,अणु
		.strid = "video_luma_spatial_filter_type",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_SPATIAL_FILTER_TYPE,
	पूर्ण,अणु
		.strid = "video_chroma_spatial_filter_type",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_SPATIAL_FILTER_TYPE,
	पूर्ण,अणु
		.strid = "video_temporal_filter_mode",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER_MODE,
	पूर्ण,अणु
		.strid = "video_temporal_filter",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_TEMPORAL_FILTER,
	पूर्ण,अणु
		.strid = "video_median_filter_type",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FILTER_TYPE,
	पूर्ण,अणु
		.strid = "video_luma_median_filter_top",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_TOP,
	पूर्ण,अणु
		.strid = "video_luma_median_filter_bottom",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_LUMA_MEDIAN_FILTER_BOTTOM,
	पूर्ण,अणु
		.strid = "video_chroma_median_filter_top",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_TOP,
	पूर्ण,अणु
		.strid = "video_chroma_median_filter_bottom",
		.id = V4L2_CID_MPEG_CX2341X_VIDEO_CHROMA_MEDIAN_FILTER_BOTTOM,
	पूर्ण
पूर्ण;
#घोषणा MPEGDEF_COUNT ARRAY_SIZE(mpeg_ids)


अटल स्थिर अक्षर *control_values_srate[] = अणु
	[V4L2_MPEG_AUDIO_SAMPLING_FREQ_44100]   = "44.1 kHz",
	[V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000]   = "48 kHz",
	[V4L2_MPEG_AUDIO_SAMPLING_FREQ_32000]   = "32 kHz",
पूर्ण;



अटल स्थिर अक्षर *control_values_input[] = अणु
	[PVR2_CVAL_INPUT_TV]        = "television",  /*xawtv needs this name*/
	[PVR2_CVAL_INPUT_DTV]       = "dtv",
	[PVR2_CVAL_INPUT_RADIO]     = "radio",
	[PVR2_CVAL_INPUT_SVIDEO]    = "s-video",
	[PVR2_CVAL_INPUT_COMPOSITE] = "composite",
पूर्ण;


अटल स्थिर अक्षर *control_values_audiomode[] = अणु
	[V4L2_TUNER_MODE_MONO]   = "Mono",
	[V4L2_TUNER_MODE_STEREO] = "Stereo",
	[V4L2_TUNER_MODE_LANG1]  = "Lang1",
	[V4L2_TUNER_MODE_LANG2]  = "Lang2",
	[V4L2_TUNER_MODE_LANG1_LANG2] = "Lang1+Lang2",
पूर्ण;


अटल स्थिर अक्षर *control_values_hsm[] = अणु
	[PVR2_CVAL_HSM_FAIL] = "Fail",
	[PVR2_CVAL_HSM_HIGH] = "High",
	[PVR2_CVAL_HSM_FULL] = "Full",
पूर्ण;


अटल स्थिर अक्षर *pvr2_state_names[] = अणु
	[PVR2_STATE_NONE] =    "none",
	[PVR2_STATE_DEAD] =    "dead",
	[PVR2_STATE_COLD] =    "cold",
	[PVR2_STATE_WARM] =    "warm",
	[PVR2_STATE_ERROR] =   "error",
	[PVR2_STATE_READY] =   "ready",
	[PVR2_STATE_RUN] =     "run",
पूर्ण;


काष्ठा pvr2_fx2cmd_descdef अणु
	अचिन्हित अक्षर id;
	अचिन्हित अक्षर *desc;
पूर्ण;

अटल स्थिर काष्ठा pvr2_fx2cmd_descdef pvr2_fx2cmd_desc[] = अणु
	अणुFX2CMD_MEM_WRITE_DWORD, "write encoder dword"पूर्ण,
	अणुFX2CMD_MEM_READ_DWORD, "read encoder dword"पूर्ण,
	अणुFX2CMD_HCW_ZILOG_RESET, "zilog IR reset control"पूर्ण,
	अणुFX2CMD_MEM_READ_64BYTES, "read encoder 64bytes"पूर्ण,
	अणुFX2CMD_REG_WRITE, "write encoder register"पूर्ण,
	अणुFX2CMD_REG_READ, "read encoder register"पूर्ण,
	अणुFX2CMD_MEMSEL, "encoder memsel"पूर्ण,
	अणुFX2CMD_I2C_WRITE, "i2c write"पूर्ण,
	अणुFX2CMD_I2C_READ, "i2c read"पूर्ण,
	अणुFX2CMD_GET_USB_SPEED, "get USB speed"पूर्ण,
	अणुFX2CMD_STREAMING_ON, "stream on"पूर्ण,
	अणुFX2CMD_STREAMING_OFF, "stream off"पूर्ण,
	अणुFX2CMD_FWPOST1, "fwpost1"पूर्ण,
	अणुFX2CMD_POWER_OFF, "power off"पूर्ण,
	अणुFX2CMD_POWER_ON, "power on"पूर्ण,
	अणुFX2CMD_DEEP_RESET, "deep reset"पूर्ण,
	अणुFX2CMD_GET_EEPROM_ADDR, "get rom addr"पूर्ण,
	अणुFX2CMD_GET_IR_CODE, "get IR code"पूर्ण,
	अणुFX2CMD_HCW_DEMOD_RESETIN, "hcw demod resetin"पूर्ण,
	अणुFX2CMD_HCW_DTV_STREAMING_ON, "hcw dtv stream on"पूर्ण,
	अणुFX2CMD_HCW_DTV_STREAMING_OFF, "hcw dtv stream off"पूर्ण,
	अणुFX2CMD_ONAIR_DTV_STREAMING_ON, "onair dtv stream on"पूर्ण,
	अणुFX2CMD_ONAIR_DTV_STREAMING_OFF, "onair dtv stream off"पूर्ण,
	अणुFX2CMD_ONAIR_DTV_POWER_ON, "onair dtv power on"पूर्ण,
	अणुFX2CMD_ONAIR_DTV_POWER_OFF, "onair dtv power off"पूर्ण,
	अणुFX2CMD_HCW_DEMOD_RESET_PIN, "hcw demod reset pin"पूर्ण,
	अणुFX2CMD_HCW_MAKO_SLEEP_PIN, "hcw mako sleep pin"पूर्ण,
पूर्ण;


अटल पूर्णांक pvr2_hdw_set_input(काष्ठा pvr2_hdw *hdw,पूर्णांक v);
अटल व्योम pvr2_hdw_state_sched(काष्ठा pvr2_hdw *);
अटल पूर्णांक pvr2_hdw_state_eval(काष्ठा pvr2_hdw *);
अटल व्योम pvr2_hdw_set_cur_freq(काष्ठा pvr2_hdw *,अचिन्हित दीर्घ);
अटल व्योम pvr2_hdw_worker_poll(काष्ठा work_काष्ठा *work);
अटल पूर्णांक pvr2_hdw_रुको(काष्ठा pvr2_hdw *,पूर्णांक state);
अटल पूर्णांक pvr2_hdw_untrip_unlocked(काष्ठा pvr2_hdw *);
अटल व्योम pvr2_hdw_state_log_state(काष्ठा pvr2_hdw *);
अटल पूर्णांक pvr2_hdw_cmd_usbstream(काष्ठा pvr2_hdw *hdw,पूर्णांक runFl);
अटल पूर्णांक pvr2_hdw_commit_setup(काष्ठा pvr2_hdw *hdw);
अटल पूर्णांक pvr2_hdw_get_eeprom_addr(काष्ठा pvr2_hdw *hdw);
अटल व्योम pvr2_hdw_quiescent_समयout(काष्ठा समयr_list *);
अटल व्योम pvr2_hdw_decoder_stabilization_समयout(काष्ठा समयr_list *);
अटल व्योम pvr2_hdw_encoder_रुको_समयout(काष्ठा समयr_list *);
अटल व्योम pvr2_hdw_encoder_run_समयout(काष्ठा समयr_list *);
अटल पूर्णांक pvr2_issue_simple_cmd(काष्ठा pvr2_hdw *,u32);
अटल पूर्णांक pvr2_send_request_ex(काष्ठा pvr2_hdw *hdw,
				अचिन्हित पूर्णांक समयout,पूर्णांक probe_fl,
				व्योम *ग_लिखो_data,अचिन्हित पूर्णांक ग_लिखो_len,
				व्योम *पढ़ो_data,अचिन्हित पूर्णांक पढ़ो_len);
अटल पूर्णांक pvr2_hdw_check_cropcap(काष्ठा pvr2_hdw *hdw);
अटल v4l2_std_id pvr2_hdw_get_detected_std(काष्ठा pvr2_hdw *hdw);

अटल व्योम trace_stbit(स्थिर अक्षर *name,पूर्णांक val)
अणु
	pvr2_trace(PVR2_TRACE_STBITS,
		   "State bit %s <-- %s",
		   name,(val ? "true" : "false"));
पूर्ण

अटल पूर्णांक ctrl_channelfreq_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	अगर ((hdw->freqProgSlot > 0) && (hdw->freqProgSlot <= FREQTABLE_SIZE)) अणु
		*vp = hdw->freqTable[hdw->freqProgSlot-1];
	पूर्ण अन्यथा अणु
		*vp = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_channelfreq_set(काष्ठा pvr2_ctrl *cptr,पूर्णांक m,पूर्णांक v)
अणु
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	अचिन्हित पूर्णांक slotId = hdw->freqProgSlot;
	अगर ((slotId > 0) && (slotId <= FREQTABLE_SIZE)) अणु
		hdw->freqTable[slotId-1] = v;
		/* Handle side effects correctly - अगर we're tuned to this
		   slot, then क्रमgot the slot id relation since the stored
		   frequency has been changed. */
		अगर (hdw->freqSelector) अणु
			अगर (hdw->freqSlotRadio == slotId) अणु
				hdw->freqSlotRadio = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (hdw->freqSlotTelevision == slotId) अणु
				hdw->freqSlotTelevision = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_channelprog_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	*vp = cptr->hdw->freqProgSlot;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_channelprog_set(काष्ठा pvr2_ctrl *cptr,पूर्णांक m,पूर्णांक v)
अणु
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	अगर ((v >= 0) && (v <= FREQTABLE_SIZE)) अणु
		hdw->freqProgSlot = v;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_channel_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	*vp = hdw->freqSelector ? hdw->freqSlotRadio : hdw->freqSlotTelevision;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_channel_set(काष्ठा pvr2_ctrl *cptr,पूर्णांक m,पूर्णांक slotId)
अणु
	अचिन्हित freq = 0;
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	अगर ((slotId < 0) || (slotId > FREQTABLE_SIZE)) वापस 0;
	अगर (slotId > 0) अणु
		freq = hdw->freqTable[slotId-1];
		अगर (!freq) वापस 0;
		pvr2_hdw_set_cur_freq(hdw,freq);
	पूर्ण
	अगर (hdw->freqSelector) अणु
		hdw->freqSlotRadio = slotId;
	पूर्ण अन्यथा अणु
		hdw->freqSlotTelevision = slotId;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_freq_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	*vp = pvr2_hdw_get_cur_freq(cptr->hdw);
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_freq_is_dirty(काष्ठा pvr2_ctrl *cptr)
अणु
	वापस cptr->hdw->freqDirty != 0;
पूर्ण

अटल व्योम ctrl_freq_clear_dirty(काष्ठा pvr2_ctrl *cptr)
अणु
	cptr->hdw->freqDirty = 0;
पूर्ण

अटल पूर्णांक ctrl_freq_set(काष्ठा pvr2_ctrl *cptr,पूर्णांक m,पूर्णांक v)
अणु
	pvr2_hdw_set_cur_freq(cptr->hdw,v);
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_cropl_min_get(काष्ठा pvr2_ctrl *cptr, पूर्णांक *left)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*left = cap->bounds.left;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_cropl_max_get(काष्ठा pvr2_ctrl *cptr, पूर्णांक *left)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*left = cap->bounds.left;
	अगर (cap->bounds.width > cptr->hdw->cropw_val) अणु
		*left += cap->bounds.width - cptr->hdw->cropw_val;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_cropt_min_get(काष्ठा pvr2_ctrl *cptr, पूर्णांक *top)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*top = cap->bounds.top;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_cropt_max_get(काष्ठा pvr2_ctrl *cptr, पूर्णांक *top)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*top = cap->bounds.top;
	अगर (cap->bounds.height > cptr->hdw->croph_val) अणु
		*top += cap->bounds.height - cptr->hdw->croph_val;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_cropw_max_get(काष्ठा pvr2_ctrl *cptr, पूर्णांक *width)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat, bleftend, cleft;

	stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	bleftend = cap->bounds.left+cap->bounds.width;
	cleft = cptr->hdw->cropl_val;

	*width = cleft < bleftend ? bleftend-cleft : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_croph_max_get(काष्ठा pvr2_ctrl *cptr, पूर्णांक *height)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat, btखोलोd, ctop;

	stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	btखोलोd = cap->bounds.top+cap->bounds.height;
	ctop = cptr->hdw->cropt_val;

	*height = ctop < btखोलोd ? btखोलोd-ctop : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcapbl(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->bounds.left;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcapbt(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->bounds.top;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcapbw(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->bounds.width;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcapbh(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->bounds.height;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcapdl(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->defrect.left;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcapdt(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->defrect.top;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcapdw(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->defrect.width;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcapdh(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->defrect.height;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcappan(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->pixelaspect.numerator;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_cropcappad(काष्ठा pvr2_ctrl *cptr, पूर्णांक *val)
अणु
	काष्ठा v4l2_cropcap *cap = &cptr->hdw->cropcap_info;
	पूर्णांक stat = pvr2_hdw_check_cropcap(cptr->hdw);
	अगर (stat != 0) अणु
		वापस stat;
	पूर्ण
	*val = cap->pixelaspect.denominator;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_vres_max_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	/* Actual maximum depends on the video standard in effect. */
	अगर (cptr->hdw->std_mask_cur & V4L2_STD_525_60) अणु
		*vp = 480;
	पूर्ण अन्यथा अणु
		*vp = 576;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_vres_min_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	/* Actual minimum depends on device digitizer type. */
	अगर (cptr->hdw->hdw_desc->flag_has_cx25840) अणु
		*vp = 75;
	पूर्ण अन्यथा अणु
		*vp = 17;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_get_input(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	*vp = cptr->hdw->input_val;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_check_input(काष्ठा pvr2_ctrl *cptr,पूर्णांक v)
अणु
	अगर (v < 0 || v > PVR2_CVAL_INPUT_MAX)
		वापस 0;
	वापस ((1UL << v) & cptr->hdw->input_allowed_mask) != 0;
पूर्ण

अटल पूर्णांक ctrl_set_input(काष्ठा pvr2_ctrl *cptr,पूर्णांक m,पूर्णांक v)
अणु
	वापस pvr2_hdw_set_input(cptr->hdw,v);
पूर्ण

अटल पूर्णांक ctrl_isdirty_input(काष्ठा pvr2_ctrl *cptr)
अणु
	वापस cptr->hdw->input_dirty != 0;
पूर्ण

अटल व्योम ctrl_cleardirty_input(काष्ठा pvr2_ctrl *cptr)
अणु
	cptr->hdw->input_dirty = 0;
पूर्ण


अटल पूर्णांक ctrl_freq_max_get(काष्ठा pvr2_ctrl *cptr, पूर्णांक *vp)
अणु
	अचिन्हित दीर्घ fv;
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	अगर (hdw->tuner_संकेत_stale) अणु
		pvr2_hdw_status_poll(hdw);
	पूर्ण
	fv = hdw->tuner_संकेत_info.rangehigh;
	अगर (!fv) अणु
		/* Safety fallback */
		*vp = TV_MAX_FREQ;
		वापस 0;
	पूर्ण
	अगर (hdw->tuner_संकेत_info.capability & V4L2_TUNER_CAP_LOW) अणु
		fv = (fv * 125) / 2;
	पूर्ण अन्यथा अणु
		fv = fv * 62500;
	पूर्ण
	*vp = fv;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_freq_min_get(काष्ठा pvr2_ctrl *cptr, पूर्णांक *vp)
अणु
	अचिन्हित दीर्घ fv;
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	अगर (hdw->tuner_संकेत_stale) अणु
		pvr2_hdw_status_poll(hdw);
	पूर्ण
	fv = hdw->tuner_संकेत_info.rangelow;
	अगर (!fv) अणु
		/* Safety fallback */
		*vp = TV_MIN_FREQ;
		वापस 0;
	पूर्ण
	अगर (hdw->tuner_संकेत_info.capability & V4L2_TUNER_CAP_LOW) अणु
		fv = (fv * 125) / 2;
	पूर्ण अन्यथा अणु
		fv = fv * 62500;
	पूर्ण
	*vp = fv;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_cx2341x_is_dirty(काष्ठा pvr2_ctrl *cptr)
अणु
	वापस cptr->hdw->enc_stale != 0;
पूर्ण

अटल व्योम ctrl_cx2341x_clear_dirty(काष्ठा pvr2_ctrl *cptr)
अणु
	cptr->hdw->enc_stale = 0;
	cptr->hdw->enc_unsafe_stale = 0;
पूर्ण

अटल पूर्णांक ctrl_cx2341x_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	पूर्णांक ret;
	काष्ठा v4l2_ext_controls cs;
	काष्ठा v4l2_ext_control c1;
	स_रखो(&cs,0,माप(cs));
	स_रखो(&c1,0,माप(c1));
	cs.controls = &c1;
	cs.count = 1;
	c1.id = cptr->info->v4l_id;
	ret = cx2341x_ext_ctrls(&cptr->hdw->enc_ctl_state, 0, &cs,
				VIDIOC_G_EXT_CTRLS);
	अगर (ret) वापस ret;
	*vp = c1.value;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_cx2341x_set(काष्ठा pvr2_ctrl *cptr,पूर्णांक m,पूर्णांक v)
अणु
	पूर्णांक ret;
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	काष्ठा v4l2_ext_controls cs;
	काष्ठा v4l2_ext_control c1;
	स_रखो(&cs,0,माप(cs));
	स_रखो(&c1,0,माप(c1));
	cs.controls = &c1;
	cs.count = 1;
	c1.id = cptr->info->v4l_id;
	c1.value = v;
	ret = cx2341x_ext_ctrls(&hdw->enc_ctl_state,
				hdw->state_encoder_run, &cs,
				VIDIOC_S_EXT_CTRLS);
	अगर (ret == -EBUSY) अणु
		/* Oops.  cx2341x is telling us it's not safe to change
		   this control जबतक we're capturing.  Make a note of this
		   fact so that the pipeline will be stopped the next समय
		   controls are committed.  Then go on ahead and store this
		   change anyway. */
		ret = cx2341x_ext_ctrls(&hdw->enc_ctl_state,
					0, &cs,
					VIDIOC_S_EXT_CTRLS);
		अगर (!ret) hdw->enc_unsafe_stale = !0;
	पूर्ण
	अगर (ret) वापस ret;
	hdw->enc_stale = !0;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ctrl_cx2341x_getv4lflags(काष्ठा pvr2_ctrl *cptr)
अणु
	काष्ठा v4l2_queryctrl qctrl = अणुपूर्ण;
	काष्ठा pvr2_ctl_info *info;
	qctrl.id = cptr->info->v4l_id;
	cx2341x_ctrl_query(&cptr->hdw->enc_ctl_state,&qctrl);
	/* Strip out the स्थिर so we can adjust a function poपूर्णांकer.  It's
	   OK to करो this here because we know this is a dynamically created
	   control, so the underlying storage क्रम the info poपूर्णांकer is (a)
	   निजी to us, and (b) not in पढ़ो-only storage.  Either we करो
	   this or we signअगरicantly complicate the underlying control
	   implementation. */
	info = (काष्ठा pvr2_ctl_info *)(cptr->info);
	अगर (qctrl.flags & V4L2_CTRL_FLAG_READ_ONLY) अणु
		अगर (info->set_value) अणु
			info->set_value = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(info->set_value)) अणु
			info->set_value = ctrl_cx2341x_set;
		पूर्ण
	पूर्ण
	वापस qctrl.flags;
पूर्ण

अटल पूर्णांक ctrl_streamingenabled_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	*vp = cptr->hdw->state_pipeline_req;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_masterstate_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	*vp = cptr->hdw->master_state;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_hsm_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	पूर्णांक result = pvr2_hdw_is_hsm(cptr->hdw);
	*vp = PVR2_CVAL_HSM_FULL;
	अगर (result < 0) *vp = PVR2_CVAL_HSM_FAIL;
	अगर (result) *vp = PVR2_CVAL_HSM_HIGH;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_stddetect_get(काष्ठा pvr2_ctrl *cptr, पूर्णांक *vp)
अणु
	*vp = pvr2_hdw_get_detected_std(cptr->hdw);
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_stdavail_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	*vp = cptr->hdw->std_mask_avail;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_stdavail_set(काष्ठा pvr2_ctrl *cptr,पूर्णांक m,पूर्णांक v)
अणु
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	v4l2_std_id ns;
	ns = hdw->std_mask_avail;
	ns = (ns & ~m) | (v & m);
	अगर (ns == hdw->std_mask_avail) वापस 0;
	hdw->std_mask_avail = ns;
	hdw->std_info_cur.def.type_biपंचांगask.valid_bits = hdw->std_mask_avail;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_std_val_to_sym(काष्ठा pvr2_ctrl *cptr,पूर्णांक msk,पूर्णांक val,
			       अक्षर *bufPtr,अचिन्हित पूर्णांक bufSize,
			       अचिन्हित पूर्णांक *len)
अणु
	*len = pvr2_std_id_to_str(bufPtr,bufSize,msk & val);
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_std_sym_to_val(काष्ठा pvr2_ctrl *cptr,
			       स्थिर अक्षर *bufPtr,अचिन्हित पूर्णांक bufSize,
			       पूर्णांक *mskp,पूर्णांक *valp)
अणु
	v4l2_std_id id;
	अगर (!pvr2_std_str_to_id(&id, bufPtr, bufSize))
		वापस -EINVAL;
	अगर (mskp) *mskp = id;
	अगर (valp) *valp = id;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_stdcur_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	*vp = cptr->hdw->std_mask_cur;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_stdcur_set(काष्ठा pvr2_ctrl *cptr,पूर्णांक m,पूर्णांक v)
अणु
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	v4l2_std_id ns;
	ns = hdw->std_mask_cur;
	ns = (ns & ~m) | (v & m);
	अगर (ns == hdw->std_mask_cur) वापस 0;
	hdw->std_mask_cur = ns;
	hdw->std_dirty = !0;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_stdcur_is_dirty(काष्ठा pvr2_ctrl *cptr)
अणु
	वापस cptr->hdw->std_dirty != 0;
पूर्ण

अटल व्योम ctrl_stdcur_clear_dirty(काष्ठा pvr2_ctrl *cptr)
अणु
	cptr->hdw->std_dirty = 0;
पूर्ण

अटल पूर्णांक ctrl_संकेत_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	pvr2_hdw_status_poll(hdw);
	*vp = hdw->tuner_संकेत_info.संकेत;
	वापस 0;
पूर्ण

अटल पूर्णांक ctrl_audio_modes_present_get(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp)
अणु
	पूर्णांक val = 0;
	अचिन्हित पूर्णांक subchan;
	काष्ठा pvr2_hdw *hdw = cptr->hdw;
	pvr2_hdw_status_poll(hdw);
	subchan = hdw->tuner_संकेत_info.rxsubchans;
	अगर (subchan & V4L2_TUNER_SUB_MONO) अणु
		val |= (1 << V4L2_TUNER_MODE_MONO);
	पूर्ण
	अगर (subchan & V4L2_TUNER_SUB_STEREO) अणु
		val |= (1 << V4L2_TUNER_MODE_STEREO);
	पूर्ण
	अगर (subchan & V4L2_TUNER_SUB_LANG1) अणु
		val |= (1 << V4L2_TUNER_MODE_LANG1);
	पूर्ण
	अगर (subchan & V4L2_TUNER_SUB_LANG2) अणु
		val |= (1 << V4L2_TUNER_MODE_LANG2);
	पूर्ण
	*vp = val;
	वापस 0;
पूर्ण


#घोषणा DEFINT(vmin,vmax) \
	.type = pvr2_ctl_पूर्णांक, \
	.def.type_पूर्णांक.min_value = vmin, \
	.def.type_पूर्णांक.max_value = vmax

#घोषणा DEFENUM(tab) \
	.type = pvr2_ctl_क्रमागत, \
	.def.type_क्रमागत.count = ARRAY_SIZE(tab), \
	.def.type_क्रमागत.value_names = tab

#घोषणा DEFBOOL \
	.type = pvr2_ctl_bool

#घोषणा DEFMASK(msk,tab) \
	.type = pvr2_ctl_biपंचांगask, \
	.def.type_biपंचांगask.valid_bits = msk, \
	.def.type_biपंचांगask.bit_names = tab

#घोषणा DEFREF(vname) \
	.set_value = ctrl_set_##vname, \
	.get_value = ctrl_get_##vname, \
	.is_dirty = ctrl_isdirty_##vname, \
	.clear_dirty = ctrl_cleardirty_##vname


#घोषणा VCREATE_FUNCS(vname) \
अटल पूर्णांक ctrl_get_##vname(काष्ठा pvr2_ctrl *cptr,पूर्णांक *vp) \
अणु*vp = cptr->hdw->vname##_val; वापस 0;पूर्ण \
अटल पूर्णांक ctrl_set_##vname(काष्ठा pvr2_ctrl *cptr,पूर्णांक m,पूर्णांक v) \
अणुcptr->hdw->vname##_val = v; cptr->hdw->vname##_dirty = !0; वापस 0;पूर्ण \
अटल पूर्णांक ctrl_isdirty_##vname(काष्ठा pvr2_ctrl *cptr) \
अणुवापस cptr->hdw->vname##_dirty != 0;पूर्ण \
अटल व्योम ctrl_cleardirty_##vname(काष्ठा pvr2_ctrl *cptr) \
अणुcptr->hdw->vname##_dirty = 0;पूर्ण

VCREATE_FUNCS(brightness)
VCREATE_FUNCS(contrast)
VCREATE_FUNCS(saturation)
VCREATE_FUNCS(hue)
VCREATE_FUNCS(volume)
VCREATE_FUNCS(balance)
VCREATE_FUNCS(bass)
VCREATE_FUNCS(treble)
VCREATE_FUNCS(mute)
VCREATE_FUNCS(cropl)
VCREATE_FUNCS(cropt)
VCREATE_FUNCS(cropw)
VCREATE_FUNCS(croph)
VCREATE_FUNCS(audiomode)
VCREATE_FUNCS(res_hor)
VCREATE_FUNCS(res_ver)
VCREATE_FUNCS(srate)

/* Table definition of all controls which can be manipulated */
अटल स्थिर काष्ठा pvr2_ctl_info control_defs[] = अणु
	अणु
		.v4l_id = V4L2_CID_BRIGHTNESS,
		.desc = "Brightness",
		.name = "brightness",
		.शेष_value = 128,
		DEFREF(brightness),
		DEFINT(0,255),
	पूर्ण,अणु
		.v4l_id = V4L2_CID_CONTRAST,
		.desc = "Contrast",
		.name = "contrast",
		.शेष_value = 68,
		DEFREF(contrast),
		DEFINT(0,127),
	पूर्ण,अणु
		.v4l_id = V4L2_CID_SATURATION,
		.desc = "Saturation",
		.name = "saturation",
		.शेष_value = 64,
		DEFREF(saturation),
		DEFINT(0,127),
	पूर्ण,अणु
		.v4l_id = V4L2_CID_HUE,
		.desc = "Hue",
		.name = "hue",
		.शेष_value = 0,
		DEFREF(hue),
		DEFINT(-128,127),
	पूर्ण,अणु
		.v4l_id = V4L2_CID_AUDIO_VOLUME,
		.desc = "Volume",
		.name = "volume",
		.शेष_value = 62000,
		DEFREF(volume),
		DEFINT(0,65535),
	पूर्ण,अणु
		.v4l_id = V4L2_CID_AUDIO_BALANCE,
		.desc = "Balance",
		.name = "balance",
		.शेष_value = 0,
		DEFREF(balance),
		DEFINT(-32768,32767),
	पूर्ण,अणु
		.v4l_id = V4L2_CID_AUDIO_BASS,
		.desc = "Bass",
		.name = "bass",
		.शेष_value = 0,
		DEFREF(bass),
		DEFINT(-32768,32767),
	पूर्ण,अणु
		.v4l_id = V4L2_CID_AUDIO_TREBLE,
		.desc = "Treble",
		.name = "treble",
		.शेष_value = 0,
		DEFREF(treble),
		DEFINT(-32768,32767),
	पूर्ण,अणु
		.v4l_id = V4L2_CID_AUDIO_MUTE,
		.desc = "Mute",
		.name = "mute",
		.शेष_value = 0,
		DEFREF(mute),
		DEFBOOL,
	पूर्ण, अणु
		.desc = "Capture crop left margin",
		.name = "crop_left",
		.पूर्णांकernal_id = PVR2_CID_CROPL,
		.शेष_value = 0,
		DEFREF(cropl),
		DEFINT(-129, 340),
		.get_min_value = ctrl_cropl_min_get,
		.get_max_value = ctrl_cropl_max_get,
		.get_def_value = ctrl_get_cropcapdl,
	पूर्ण, अणु
		.desc = "Capture crop top margin",
		.name = "crop_top",
		.पूर्णांकernal_id = PVR2_CID_CROPT,
		.शेष_value = 0,
		DEFREF(cropt),
		DEFINT(-35, 544),
		.get_min_value = ctrl_cropt_min_get,
		.get_max_value = ctrl_cropt_max_get,
		.get_def_value = ctrl_get_cropcapdt,
	पूर्ण, अणु
		.desc = "Capture crop width",
		.name = "crop_width",
		.पूर्णांकernal_id = PVR2_CID_CROPW,
		.शेष_value = 720,
		DEFREF(cropw),
		DEFINT(0, 864),
		.get_max_value = ctrl_cropw_max_get,
		.get_def_value = ctrl_get_cropcapdw,
	पूर्ण, अणु
		.desc = "Capture crop height",
		.name = "crop_height",
		.पूर्णांकernal_id = PVR2_CID_CROPH,
		.शेष_value = 480,
		DEFREF(croph),
		DEFINT(0, 576),
		.get_max_value = ctrl_croph_max_get,
		.get_def_value = ctrl_get_cropcapdh,
	पूर्ण, अणु
		.desc = "Capture capability pixel aspect numerator",
		.name = "cropcap_pixel_numerator",
		.पूर्णांकernal_id = PVR2_CID_CROPCAPPAN,
		.get_value = ctrl_get_cropcappan,
	पूर्ण, अणु
		.desc = "Capture capability pixel aspect denominator",
		.name = "cropcap_pixel_denominator",
		.पूर्णांकernal_id = PVR2_CID_CROPCAPPAD,
		.get_value = ctrl_get_cropcappad,
	पूर्ण, अणु
		.desc = "Capture capability bounds top",
		.name = "cropcap_bounds_top",
		.पूर्णांकernal_id = PVR2_CID_CROPCAPBT,
		.get_value = ctrl_get_cropcapbt,
	पूर्ण, अणु
		.desc = "Capture capability bounds left",
		.name = "cropcap_bounds_left",
		.पूर्णांकernal_id = PVR2_CID_CROPCAPBL,
		.get_value = ctrl_get_cropcapbl,
	पूर्ण, अणु
		.desc = "Capture capability bounds width",
		.name = "cropcap_bounds_width",
		.पूर्णांकernal_id = PVR2_CID_CROPCAPBW,
		.get_value = ctrl_get_cropcapbw,
	पूर्ण, अणु
		.desc = "Capture capability bounds height",
		.name = "cropcap_bounds_height",
		.पूर्णांकernal_id = PVR2_CID_CROPCAPBH,
		.get_value = ctrl_get_cropcapbh,
	पूर्ण,अणु
		.desc = "Video Source",
		.name = "input",
		.पूर्णांकernal_id = PVR2_CID_INPUT,
		.शेष_value = PVR2_CVAL_INPUT_TV,
		.check_value = ctrl_check_input,
		DEFREF(input),
		DEFENUM(control_values_input),
	पूर्ण,अणु
		.desc = "Audio Mode",
		.name = "audio_mode",
		.पूर्णांकernal_id = PVR2_CID_AUDIOMODE,
		.शेष_value = V4L2_TUNER_MODE_STEREO,
		DEFREF(audiomode),
		DEFENUM(control_values_audiomode),
	पूर्ण,अणु
		.desc = "Horizontal capture resolution",
		.name = "resolution_hor",
		.पूर्णांकernal_id = PVR2_CID_HRES,
		.शेष_value = 720,
		DEFREF(res_hor),
		DEFINT(19,720),
	पूर्ण,अणु
		.desc = "Vertical capture resolution",
		.name = "resolution_ver",
		.पूर्णांकernal_id = PVR2_CID_VRES,
		.शेष_value = 480,
		DEFREF(res_ver),
		DEFINT(17,576),
		/* Hook in check क्रम video standard and adjust maximum
		   depending on the standard. */
		.get_max_value = ctrl_vres_max_get,
		.get_min_value = ctrl_vres_min_get,
	पूर्ण,अणु
		.v4l_id = V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ,
		.शेष_value = V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000,
		.desc = "Audio Sampling Frequency",
		.name = "srate",
		DEFREF(srate),
		DEFENUM(control_values_srate),
	पूर्ण,अणु
		.desc = "Tuner Frequency (Hz)",
		.name = "frequency",
		.पूर्णांकernal_id = PVR2_CID_FREQUENCY,
		.शेष_value = 0,
		.set_value = ctrl_freq_set,
		.get_value = ctrl_freq_get,
		.is_dirty = ctrl_freq_is_dirty,
		.clear_dirty = ctrl_freq_clear_dirty,
		DEFINT(0,0),
		/* Hook in check क्रम input value (tv/radio) and adjust
		   max/min values accordingly */
		.get_max_value = ctrl_freq_max_get,
		.get_min_value = ctrl_freq_min_get,
	पूर्ण,अणु
		.desc = "Channel",
		.name = "channel",
		.set_value = ctrl_channel_set,
		.get_value = ctrl_channel_get,
		DEFINT(0,FREQTABLE_SIZE),
	पूर्ण,अणु
		.desc = "Channel Program Frequency",
		.name = "freq_table_value",
		.set_value = ctrl_channelfreq_set,
		.get_value = ctrl_channelfreq_get,
		DEFINT(0,0),
		/* Hook in check क्रम input value (tv/radio) and adjust
		   max/min values accordingly */
		.get_max_value = ctrl_freq_max_get,
		.get_min_value = ctrl_freq_min_get,
	पूर्ण,अणु
		.desc = "Channel Program ID",
		.name = "freq_table_channel",
		.set_value = ctrl_channelprog_set,
		.get_value = ctrl_channelprog_get,
		DEFINT(0,FREQTABLE_SIZE),
	पूर्ण,अणु
		.desc = "Streaming Enabled",
		.name = "streaming_enabled",
		.get_value = ctrl_streamingenabled_get,
		DEFBOOL,
	पूर्ण,अणु
		.desc = "USB Speed",
		.name = "usb_speed",
		.get_value = ctrl_hsm_get,
		DEFENUM(control_values_hsm),
	पूर्ण,अणु
		.desc = "Master State",
		.name = "master_state",
		.get_value = ctrl_masterstate_get,
		DEFENUM(pvr2_state_names),
	पूर्ण,अणु
		.desc = "Signal Present",
		.name = "signal_present",
		.get_value = ctrl_संकेत_get,
		DEFINT(0,65535),
	पूर्ण,अणु
		.desc = "Audio Modes Present",
		.name = "audio_modes_present",
		.get_value = ctrl_audio_modes_present_get,
		/* For this type we "borrow" the V4L2_TUNER_MODE क्रमागत from
		   v4l.  Nothing outside of this module cares about this,
		   but I reuse it in order to also reuse the
		   control_values_audiomode string table. */
		DEFMASK(((1 << V4L2_TUNER_MODE_MONO)|
			 (1 << V4L2_TUNER_MODE_STEREO)|
			 (1 << V4L2_TUNER_MODE_LANG1)|
			 (1 << V4L2_TUNER_MODE_LANG2)),
			control_values_audiomode),
	पूर्ण,अणु
		.desc = "Video Standards Available Mask",
		.name = "video_standard_mask_available",
		.पूर्णांकernal_id = PVR2_CID_STDAVAIL,
		.skip_init = !0,
		.get_value = ctrl_stdavail_get,
		.set_value = ctrl_stdavail_set,
		.val_to_sym = ctrl_std_val_to_sym,
		.sym_to_val = ctrl_std_sym_to_val,
		.type = pvr2_ctl_biपंचांगask,
	पूर्ण,अणु
		.desc = "Video Standards In Use Mask",
		.name = "video_standard_mask_active",
		.पूर्णांकernal_id = PVR2_CID_STDCUR,
		.skip_init = !0,
		.get_value = ctrl_stdcur_get,
		.set_value = ctrl_stdcur_set,
		.is_dirty = ctrl_stdcur_is_dirty,
		.clear_dirty = ctrl_stdcur_clear_dirty,
		.val_to_sym = ctrl_std_val_to_sym,
		.sym_to_val = ctrl_std_sym_to_val,
		.type = pvr2_ctl_biपंचांगask,
	पूर्ण,अणु
		.desc = "Video Standards Detected Mask",
		.name = "video_standard_mask_detected",
		.पूर्णांकernal_id = PVR2_CID_STDDETECT,
		.skip_init = !0,
		.get_value = ctrl_stddetect_get,
		.val_to_sym = ctrl_std_val_to_sym,
		.sym_to_val = ctrl_std_sym_to_val,
		.type = pvr2_ctl_biपंचांगask,
	पूर्ण
पूर्ण;

#घोषणा CTRLDEF_COUNT ARRAY_SIZE(control_defs)


स्थिर अक्षर *pvr2_config_get_name(क्रमागत pvr2_config cfg)
अणु
	चयन (cfg) अणु
	हाल pvr2_config_empty: वापस "empty";
	हाल pvr2_config_mpeg: वापस "mpeg";
	हाल pvr2_config_vbi: वापस "vbi";
	हाल pvr2_config_pcm: वापस "pcm";
	हाल pvr2_config_rawvideo: वापस "raw video";
	पूर्ण
	वापस "<unknown>";
पूर्ण


काष्ठा usb_device *pvr2_hdw_get_dev(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->usb_dev;
पूर्ण


अचिन्हित दीर्घ pvr2_hdw_get_sn(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->serial_number;
पूर्ण


स्थिर अक्षर *pvr2_hdw_get_bus_info(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->bus_info;
पूर्ण


स्थिर अक्षर *pvr2_hdw_get_device_identअगरier(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->identअगरier;
पूर्ण


अचिन्हित दीर्घ pvr2_hdw_get_cur_freq(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->freqSelector ? hdw->freqValTelevision : hdw->freqValRadio;
पूर्ण

/* Set the currently tuned frequency and account क्रम all possible
   driver-core side effects of this action. */
अटल व्योम pvr2_hdw_set_cur_freq(काष्ठा pvr2_hdw *hdw,अचिन्हित दीर्घ val)
अणु
	अगर (hdw->input_val == PVR2_CVAL_INPUT_RADIO) अणु
		अगर (hdw->freqSelector) अणु
			/* Swing over to radio frequency selection */
			hdw->freqSelector = 0;
			hdw->freqDirty = !0;
		पूर्ण
		अगर (hdw->freqValRadio != val) अणु
			hdw->freqValRadio = val;
			hdw->freqSlotRadio = 0;
			hdw->freqDirty = !0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(hdw->freqSelector)) अणु
			/* Swing over to television frequency selection */
			hdw->freqSelector = 1;
			hdw->freqDirty = !0;
		पूर्ण
		अगर (hdw->freqValTelevision != val) अणु
			hdw->freqValTelevision = val;
			hdw->freqSlotTelevision = 0;
			hdw->freqDirty = !0;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक pvr2_hdw_get_unit_number(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->unit_number;
पूर्ण


/* Attempt to locate one of the given set of files.  Messages are logged
   appropriate to what has been found.  The वापस value will be 0 or
   greater on success (it will be the index of the file name found) and
   fw_entry will be filled in.  Otherwise a negative error is वापसed on
   failure.  If the वापस value is -ENOENT then no viable firmware file
   could be located. */
अटल पूर्णांक pvr2_locate_firmware(काष्ठा pvr2_hdw *hdw,
				स्थिर काष्ठा firmware **fw_entry,
				स्थिर अक्षर *fwtypename,
				अचिन्हित पूर्णांक fwcount,
				स्थिर अक्षर *fwnames[])
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक ret = -EINVAL;
	क्रम (idx = 0; idx < fwcount; idx++) अणु
		ret = request_firmware(fw_entry,
				       fwnames[idx],
				       &hdw->usb_dev->dev);
		अगर (!ret) अणु
			trace_firmware("Located %s firmware: %s; uploading...",
				       fwtypename,
				       fwnames[idx]);
			वापस idx;
		पूर्ण
		अगर (ret == -ENOENT) जारी;
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "request_firmware fatal error with code=%d",ret);
		वापस ret;
	पूर्ण
	pvr2_trace(PVR2_TRACE_ERROR_LEGS,
		   "***WARNING*** Device %s firmware seems to be missing.",
		   fwtypename);
	pvr2_trace(PVR2_TRACE_ERROR_LEGS,
		   "Did you install the pvrusb2 firmware files in their proper location?");
	अगर (fwcount == 1) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "request_firmware unable to locate %s file %s",
			   fwtypename,fwnames[0]);
	पूर्ण अन्यथा अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "request_firmware unable to locate one of the following %s files:",
			   fwtypename);
		क्रम (idx = 0; idx < fwcount; idx++) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "request_firmware: Failed to find %s",
				   fwnames[idx]);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण


/*
 * pvr2_upload_firmware1().
 *
 * Send the 8051 firmware to the device.  After the upload, arrange क्रम
 * device to re-क्रमागतerate.
 *
 * NOTE : the poपूर्णांकer to the firmware data given by request_firmware()
 * is not suitable क्रम an usb transaction.
 *
 */
अटल पूर्णांक pvr2_upload_firmware1(काष्ठा pvr2_hdw *hdw)
अणु
	स्थिर काष्ठा firmware *fw_entry = शून्य;
	व्योम  *fw_ptr;
	अचिन्हित पूर्णांक pipe;
	अचिन्हित पूर्णांक fwsize;
	पूर्णांक ret;
	u16 address;

	अगर (!hdw->hdw_desc->fx2_firmware.cnt) अणु
		hdw->fw1_state = FW1_STATE_OK;
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Connected device type defines no firmware to upload; ignoring firmware");
		वापस -ENOTTY;
	पूर्ण

	hdw->fw1_state = FW1_STATE_FAILED; // शेष result

	trace_firmware("pvr2_upload_firmware1");

	ret = pvr2_locate_firmware(hdw,&fw_entry,"fx2 controller",
				   hdw->hdw_desc->fx2_firmware.cnt,
				   hdw->hdw_desc->fx2_firmware.lst);
	अगर (ret < 0) अणु
		अगर (ret == -ENOENT) hdw->fw1_state = FW1_STATE_MISSING;
		वापस ret;
	पूर्ण

	usb_clear_halt(hdw->usb_dev, usb_sndbulkpipe(hdw->usb_dev, 0 & 0x7f));

	pipe = usb_sndctrlpipe(hdw->usb_dev, 0);
	fwsize = fw_entry->size;

	अगर ((fwsize != 0x2000) &&
	    (!(hdw->hdw_desc->flag_fx2_16kb && (fwsize == 0x4000)))) अणु
		अगर (hdw->hdw_desc->flag_fx2_16kb) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "Wrong fx2 firmware size (expected 8192 or 16384, got %u)",
				   fwsize);
		पूर्ण अन्यथा अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "Wrong fx2 firmware size (expected 8192, got %u)",
				   fwsize);
		पूर्ण
		release_firmware(fw_entry);
		वापस -ENOMEM;
	पूर्ण

	fw_ptr = kदो_स्मृति(0x800, GFP_KERNEL);
	अगर (fw_ptr == शून्य)अणु
		release_firmware(fw_entry);
		वापस -ENOMEM;
	पूर्ण

	/* We have to hold the CPU during firmware upload. */
	pvr2_hdw_cpureset_निश्चित(hdw,1);

	/* upload the firmware to address 0000-1fff in 2048 (=0x800) bytes
	   chunk. */

	ret = 0;
	क्रम (address = 0; address < fwsize; address += 0x800) अणु
		स_नकल(fw_ptr, fw_entry->data + address, 0x800);
		ret += usb_control_msg(hdw->usb_dev, pipe, 0xa0, 0x40, address,
				       0, fw_ptr, 0x800, HZ);
	पूर्ण

	trace_firmware("Upload done, releasing device's CPU");

	/* Now release the CPU.  It will disconnect and reconnect later. */
	pvr2_hdw_cpureset_निश्चित(hdw,0);

	kमुक्त(fw_ptr);
	release_firmware(fw_entry);

	trace_firmware("Upload done (%d bytes sent)",ret);

	/* We should have written fwsize bytes */
	अगर (ret == fwsize) अणु
		hdw->fw1_state = FW1_STATE_RELOAD;
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण


/*
 * pvr2_upload_firmware2()
 *
 * This uploads encoder firmware on endpoपूर्णांक 2.
 *
 */

पूर्णांक pvr2_upload_firmware2(काष्ठा pvr2_hdw *hdw)
अणु
	स्थिर काष्ठा firmware *fw_entry = शून्य;
	व्योम  *fw_ptr;
	अचिन्हित पूर्णांक pipe, fw_len, fw_करोne, bcnt, icnt;
	पूर्णांक actual_length;
	पूर्णांक ret = 0;
	पूर्णांक fwidx;
	अटल स्थिर अक्षर *fw_files[] = अणु
		CX2341X_FIRM_ENC_खाताNAME,
	पूर्ण;

	अगर (hdw->hdw_desc->flag_skip_cx23416_firmware) अणु
		वापस 0;
	पूर्ण

	trace_firmware("pvr2_upload_firmware2");

	ret = pvr2_locate_firmware(hdw,&fw_entry,"encoder",
				   ARRAY_SIZE(fw_files), fw_files);
	अगर (ret < 0) वापस ret;
	fwidx = ret;
	ret = 0;
	/* Since we're about to completely reinitialize the encoder,
	   invalidate our cached copy of its configuration state.  Next
	   समय we configure the encoder, then we'll fully configure it. */
	hdw->enc_cur_valid = 0;

	/* Encoder is about to be reset so note that as far as we're
	   concerned now, the encoder has never been run. */
	del_समयr_sync(&hdw->encoder_run_समयr);
	अगर (hdw->state_encoder_runok) अणु
		hdw->state_encoder_runok = 0;
		trace_stbit("state_encoder_runok",hdw->state_encoder_runok);
	पूर्ण

	/* First prepare firmware loading */
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0x0048, 0xffffffff); /*पूर्णांकerrupt mask*/
	ret |= pvr2_hdw_gpio_chg_dir(hdw,0xffffffff,0x00000088); /*gpio dir*/
	ret |= pvr2_hdw_gpio_chg_out(hdw,0xffffffff,0x00000008); /*gpio output state*/
	ret |= pvr2_hdw_cmd_deep_reset(hdw);
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0xa064, 0x00000000); /*APU command*/
	ret |= pvr2_hdw_gpio_chg_dir(hdw,0xffffffff,0x00000408); /*gpio dir*/
	ret |= pvr2_hdw_gpio_chg_out(hdw,0xffffffff,0x00000008); /*gpio output state*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0x9058, 0xffffffed); /*VPU ctrl*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0x9054, 0xfffffffd); /*reset hw blocks*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0x07f8, 0x80000800); /*encoder SDRAM refresh*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0x07fc, 0x0000001a); /*encoder SDRAM pre-अक्षरge*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0x0700, 0x00000000); /*I2C घड़ी*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0xaa00, 0x00000000); /*unknown*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0xaa04, 0x00057810); /*unknown*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0xaa10, 0x00148500); /*unknown*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0xaa18, 0x00840000); /*unknown*/
	ret |= pvr2_issue_simple_cmd(hdw,FX2CMD_FWPOST1);
	ret |= pvr2_issue_simple_cmd(hdw,FX2CMD_MEMSEL | (1 << 8) | (0 << 16));

	अगर (ret) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "firmware2 upload prep failed, ret=%d",ret);
		release_firmware(fw_entry);
		जाओ करोne;
	पूर्ण

	/* Now send firmware */

	fw_len = fw_entry->size;

	अगर (fw_len % माप(u32)) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "size of %s firmware must be a multiple of %zu bytes",
			   fw_files[fwidx],माप(u32));
		release_firmware(fw_entry);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	fw_ptr = kदो_स्मृति(FIRMWARE_CHUNK_SIZE, GFP_KERNEL);
	अगर (fw_ptr == शून्य)अणु
		release_firmware(fw_entry);
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "failed to allocate memory for firmware2 upload");
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	pipe = usb_sndbulkpipe(hdw->usb_dev, PVR2_FIRMWARE_ENDPOINT);

	fw_करोne = 0;
	क्रम (fw_करोne = 0; fw_करोne < fw_len;) अणु
		bcnt = fw_len - fw_करोne;
		अगर (bcnt > FIRMWARE_CHUNK_SIZE) bcnt = FIRMWARE_CHUNK_SIZE;
		स_नकल(fw_ptr, fw_entry->data + fw_करोne, bcnt);
		/* Usbsnoop log shows that we must swap bytes... */
		/* Some background info: The data being swapped here is a
		   firmware image destined क्रम the mpeg encoder chip that
		   lives at the other end of a USB endpoपूर्णांक.  The encoder
		   chip always talks in 32 bit chunks and its storage is
		   organized पूर्णांकo 32 bit words.  However from the file
		   प्रणाली to the encoder chip everything is purely a byte
		   stream.  The firmware file's contents are always 32 bit
		   swapped from what the encoder expects.  Thus the need
		   always exists to swap the bytes regardless of the endian
		   type of the host processor and thereक्रमe swab32() makes
		   the most sense. */
		क्रम (icnt = 0; icnt < bcnt/4 ; icnt++)
			((u32 *)fw_ptr)[icnt] = swab32(((u32 *)fw_ptr)[icnt]);

		ret |= usb_bulk_msg(hdw->usb_dev, pipe, fw_ptr,bcnt,
				    &actual_length, HZ);
		ret |= (actual_length != bcnt);
		अगर (ret) अवरोध;
		fw_करोne += bcnt;
	पूर्ण

	trace_firmware("upload of %s : %i / %i ",
		       fw_files[fwidx],fw_करोne,fw_len);

	kमुक्त(fw_ptr);
	release_firmware(fw_entry);

	अगर (ret) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "firmware2 upload transfer failure");
		जाओ करोne;
	पूर्ण

	/* Finish upload */

	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0x9054, 0xffffffff); /*reset hw blocks*/
	ret |= pvr2_ग_लिखो_रेजिस्टर(hdw, 0x9058, 0xffffffe8); /*VPU ctrl*/
	ret |= pvr2_issue_simple_cmd(hdw,FX2CMD_MEMSEL | (1 << 8) | (0 << 16));

	अगर (ret) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "firmware2 upload post-proc failure");
	पूर्ण

 करोne:
	अगर (hdw->hdw_desc->संकेत_routing_scheme ==
	    PVR2_ROUTING_SCHEME_GOTVIEW) अणु
		/* Ensure that GPIO 11 is set to output क्रम GOTVIEW
		   hardware. */
		pvr2_hdw_gpio_chg_dir(hdw,(1 << 11),~0);
	पूर्ण
	वापस ret;
पूर्ण


अटल स्थिर अक्षर *pvr2_get_state_name(अचिन्हित पूर्णांक st)
अणु
	अगर (st < ARRAY_SIZE(pvr2_state_names)) अणु
		वापस pvr2_state_names[st];
	पूर्ण
	वापस "???";
पूर्ण

अटल पूर्णांक pvr2_decoder_enable(काष्ठा pvr2_hdw *hdw,पूर्णांक enablefl)
अणु
	/* Even though we really only care about the video decoder chip at
	   this poपूर्णांक, we'll broadcast stream on/off to all sub-devices
	   anyway, just in हाल somebody अन्यथा wants to hear the
	   command... */
	pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 stream=%s",
		   (enablefl ? "on" : "off"));
	v4l2_device_call_all(&hdw->v4l2_dev, 0, video, s_stream, enablefl);
	v4l2_device_call_all(&hdw->v4l2_dev, 0, audio, s_stream, enablefl);
	अगर (hdw->decoder_client_id) अणु
		/* We get here अगर the encoder has been noticed.  Otherwise
		   we'll issue a warning to the user (which should
		   normally never happen). */
		वापस 0;
	पूर्ण
	अगर (!hdw->flag_decoder_missed) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "***WARNING*** No decoder present");
		hdw->flag_decoder_missed = !0;
		trace_stbit("flag_decoder_missed",
			    hdw->flag_decoder_missed);
	पूर्ण
	वापस -EIO;
पूर्ण


पूर्णांक pvr2_hdw_get_state(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->master_state;
पूर्ण


अटल पूर्णांक pvr2_hdw_untrip_unlocked(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (!hdw->flag_tripped) वापस 0;
	hdw->flag_tripped = 0;
	pvr2_trace(PVR2_TRACE_ERROR_LEGS,
		   "Clearing driver error status");
	वापस !0;
पूर्ण


पूर्णांक pvr2_hdw_untrip(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक fl;
	LOCK_TAKE(hdw->big_lock); करो अणु
		fl = pvr2_hdw_untrip_unlocked(hdw);
	पूर्ण जबतक (0); LOCK_GIVE(hdw->big_lock);
	अगर (fl) pvr2_hdw_state_sched(hdw);
	वापस 0;
पूर्ण




पूर्णांक pvr2_hdw_get_streaming(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->state_pipeline_req != 0;
पूर्ण


पूर्णांक pvr2_hdw_set_streaming(काष्ठा pvr2_hdw *hdw,पूर्णांक enable_flag)
अणु
	पूर्णांक ret,st;
	LOCK_TAKE(hdw->big_lock); करो अणु
		pvr2_hdw_untrip_unlocked(hdw);
		अगर ((!enable_flag) != !(hdw->state_pipeline_req)) अणु
			hdw->state_pipeline_req = enable_flag != 0;
			pvr2_trace(PVR2_TRACE_START_STOP,
				   "/*--TRACE_STREAM--*/ %s",
				   enable_flag ? "enable" : "disable");
		पूर्ण
		pvr2_hdw_state_sched(hdw);
	पूर्ण जबतक (0); LOCK_GIVE(hdw->big_lock);
	अगर ((ret = pvr2_hdw_रुको(hdw,0)) < 0) वापस ret;
	अगर (enable_flag) अणु
		जबतक ((st = hdw->master_state) != PVR2_STATE_RUN) अणु
			अगर (st != PVR2_STATE_READY) वापस -EIO;
			अगर ((ret = pvr2_hdw_रुको(hdw,st)) < 0) वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक pvr2_hdw_set_stream_type(काष्ठा pvr2_hdw *hdw,क्रमागत pvr2_config config)
अणु
	पूर्णांक fl;
	LOCK_TAKE(hdw->big_lock);
	अगर ((fl = (hdw->desired_stream_type != config)) != 0) अणु
		hdw->desired_stream_type = config;
		hdw->state_pipeline_config = 0;
		trace_stbit("state_pipeline_config",
			    hdw->state_pipeline_config);
		pvr2_hdw_state_sched(hdw);
	पूर्ण
	LOCK_GIVE(hdw->big_lock);
	अगर (fl) वापस 0;
	वापस pvr2_hdw_रुको(hdw,0);
पूर्ण


अटल पूर्णांक get_शेष_tuner_type(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक unit_number = hdw->unit_number;
	पूर्णांक tp = -1;
	अगर ((unit_number >= 0) && (unit_number < PVR_NUM)) अणु
		tp = tuner[unit_number];
	पूर्ण
	अगर (tp < 0) वापस -EINVAL;
	hdw->tuner_type = tp;
	hdw->tuner_updated = !0;
	वापस 0;
पूर्ण


अटल v4l2_std_id get_शेष_standard(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक unit_number = hdw->unit_number;
	पूर्णांक tp = 0;
	अगर ((unit_number >= 0) && (unit_number < PVR_NUM)) अणु
		tp = video_std[unit_number];
		अगर (tp) वापस tp;
	पूर्ण
	वापस 0;
पूर्ण


अटल अचिन्हित पूर्णांक get_शेष_error_tolerance(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक unit_number = hdw->unit_number;
	पूर्णांक tp = 0;
	अगर ((unit_number >= 0) && (unit_number < PVR_NUM)) अणु
		tp = tolerance[unit_number];
	पूर्ण
	वापस tp;
पूर्ण


अटल पूर्णांक pvr2_hdw_check_firmware(काष्ठा pvr2_hdw *hdw)
अणु
	/* Try a harmless request to fetch the eeprom's address over
	   endpoपूर्णांक 1.  See what happens.  Only the full FX2 image can
	   respond to this.  If this probe fails then likely the FX2
	   firmware needs be loaded. */
	पूर्णांक result;
	LOCK_TAKE(hdw->ctl_lock); करो अणु
		hdw->cmd_buffer[0] = FX2CMD_GET_EEPROM_ADDR;
		result = pvr2_send_request_ex(hdw,HZ*1,!0,
					   hdw->cmd_buffer,1,
					   hdw->cmd_buffer,1);
		अगर (result < 0) अवरोध;
	पूर्ण जबतक(0); LOCK_GIVE(hdw->ctl_lock);
	अगर (result) अणु
		pvr2_trace(PVR2_TRACE_INIT,
			   "Probe of device endpoint 1 result status %d",
			   result);
	पूर्ण अन्यथा अणु
		pvr2_trace(PVR2_TRACE_INIT,
			   "Probe of device endpoint 1 succeeded");
	पूर्ण
	वापस result == 0;
पूर्ण

काष्ठा pvr2_std_hack अणु
	v4l2_std_id pat;  /* Pattern to match */
	v4l2_std_id msk;  /* Which bits we care about */
	v4l2_std_id std;  /* What additional standards or शेष to set */
पूर्ण;

/* This data काष्ठाure labels specअगरic combinations of standards from
   tveeprom that we'll try to recognize.  If we recognize one, then assume
   a specअगरied शेष standard to use.  This is here because tveeprom only
   tells us about available standards not the पूर्णांकended शेष standard (अगर
   any) क्रम the device in question.  We guess the शेष based on what has
   been reported as available.  Note that this is only क्रम guessing a
   शेष - which can always be overridden explicitly - and अगर the user
   has otherwise named a शेष then that शेष will always be used in
   place of this table. */
अटल स्थिर काष्ठा pvr2_std_hack std_eeprom_maps[] = अणु
	अणु	/* PAL(B/G) */
		.pat = V4L2_STD_B|V4L2_STD_GH,
		.std = V4L2_STD_PAL_B|V4L2_STD_PAL_B1|V4L2_STD_PAL_G,
	पूर्ण,
	अणु	/* NTSC(M) */
		.pat = V4L2_STD_MN,
		.std = V4L2_STD_NTSC_M,
	पूर्ण,
	अणु	/* PAL(I) */
		.pat = V4L2_STD_PAL_I,
		.std = V4L2_STD_PAL_I,
	पूर्ण,
	अणु	/* SECAM(L/L') */
		.pat = V4L2_STD_SECAM_L|V4L2_STD_SECAM_LC,
		.std = V4L2_STD_SECAM_L|V4L2_STD_SECAM_LC,
	पूर्ण,
	अणु	/* PAL(D/D1/K) */
		.pat = V4L2_STD_DK,
		.std = V4L2_STD_PAL_D|V4L2_STD_PAL_D1|V4L2_STD_PAL_K,
	पूर्ण,
पूर्ण;

अटल व्योम pvr2_hdw_setup_std(काष्ठा pvr2_hdw *hdw)
अणु
	अक्षर buf[40];
	अचिन्हित पूर्णांक bcnt;
	v4l2_std_id std1,std2,std3;

	std1 = get_शेष_standard(hdw);
	std3 = std1 ? 0 : hdw->hdw_desc->शेष_std_mask;

	bcnt = pvr2_std_id_to_str(buf,माप(buf),hdw->std_mask_eeprom);
	pvr2_trace(PVR2_TRACE_STD,
		   "Supported video standard(s) reported available in hardware: %.*s",
		   bcnt,buf);

	hdw->std_mask_avail = hdw->std_mask_eeprom;

	std2 = (std1|std3) & ~hdw->std_mask_avail;
	अगर (std2) अणु
		bcnt = pvr2_std_id_to_str(buf,माप(buf),std2);
		pvr2_trace(PVR2_TRACE_STD,
			   "Expanding supported video standards to include: %.*s",
			   bcnt,buf);
		hdw->std_mask_avail |= std2;
	पूर्ण

	hdw->std_info_cur.def.type_biपंचांगask.valid_bits = hdw->std_mask_avail;

	अगर (std1) अणु
		bcnt = pvr2_std_id_to_str(buf,माप(buf),std1);
		pvr2_trace(PVR2_TRACE_STD,
			   "Initial video standard forced to %.*s",
			   bcnt,buf);
		hdw->std_mask_cur = std1;
		hdw->std_dirty = !0;
		वापस;
	पूर्ण
	अगर (std3) अणु
		bcnt = pvr2_std_id_to_str(buf,माप(buf),std3);
		pvr2_trace(PVR2_TRACE_STD,
			   "Initial video standard (determined by device type): %.*s",
			   bcnt, buf);
		hdw->std_mask_cur = std3;
		hdw->std_dirty = !0;
		वापस;
	पूर्ण

	अणु
		अचिन्हित पूर्णांक idx;
		क्रम (idx = 0; idx < ARRAY_SIZE(std_eeprom_maps); idx++) अणु
			अगर (std_eeprom_maps[idx].msk ?
			    ((std_eeprom_maps[idx].pat ^
			     hdw->std_mask_eeprom) &
			     std_eeprom_maps[idx].msk) :
			    (std_eeprom_maps[idx].pat !=
			     hdw->std_mask_eeprom)) जारी;
			bcnt = pvr2_std_id_to_str(buf,माप(buf),
						  std_eeprom_maps[idx].std);
			pvr2_trace(PVR2_TRACE_STD,
				   "Initial video standard guessed as %.*s",
				   bcnt,buf);
			hdw->std_mask_cur = std_eeprom_maps[idx].std;
			hdw->std_dirty = !0;
			वापस;
		पूर्ण
	पूर्ण

पूर्ण


अटल अचिन्हित पूर्णांक pvr2_copy_i2c_addr_list(
	अचिन्हित लघु *dst, स्थिर अचिन्हित अक्षर *src,
	अचिन्हित पूर्णांक dst_max)
अणु
	अचिन्हित पूर्णांक cnt = 0;
	अगर (!src) वापस 0;
	जबतक (src[cnt] && (cnt + 1) < dst_max) अणु
		dst[cnt] = src[cnt];
		cnt++;
	पूर्ण
	dst[cnt] = I2C_CLIENT_END;
	वापस cnt;
पूर्ण


अटल व्योम pvr2_hdw_cx25840_vbi_hack(काष्ठा pvr2_hdw *hdw)
अणु
	/*
	  Mike Isely <isely@pobox.com> 19-Nov-2006 - This bit of nuttiness
	  क्रम cx25840 causes that module to correctly set up its video
	  scaling.  This is really a problem in the cx25840 module itself,
	  but we work around it here.  The problem has not been seen in
	  ivtv because there VBI is supported and set up.  We करोn't करो VBI
	  here (at least not yet) and thus we never attempted to even set
	  it up.
	*/
	काष्ठा v4l2_क्रमmat fmt;
	अगर (hdw->decoder_client_id != PVR2_CLIENT_ID_CX25840) अणु
		/* We're not using a cx25840 so don't enable the hack */
		वापस;
	पूर्ण

	pvr2_trace(PVR2_TRACE_INIT,
		   "Module ID %u: Executing cx25840 VBI hack",
		   hdw->decoder_client_id);
	स_रखो(&fmt, 0, माप(fmt));
	fmt.type = V4L2_BUF_TYPE_SLICED_VBI_CAPTURE;
	fmt.fmt.sliced.service_lines[0][21] = V4L2_SLICED_CAPTION_525;
	fmt.fmt.sliced.service_lines[1][21] = V4L2_SLICED_CAPTION_525;
	v4l2_device_call_all(&hdw->v4l2_dev, hdw->decoder_client_id,
			     vbi, s_sliced_fmt, &fmt.fmt.sliced);
पूर्ण


अटल पूर्णांक pvr2_hdw_load_subdev(काष्ठा pvr2_hdw *hdw,
				स्थिर काष्ठा pvr2_device_client_desc *cd)
अणु
	स्थिर अक्षर *fname;
	अचिन्हित अक्षर mid;
	काष्ठा v4l2_subdev *sd;
	अचिन्हित पूर्णांक i2ccnt;
	स्थिर अचिन्हित अक्षर *p;
	/* Arbitrary count - max # i2c addresses we will probe */
	अचिन्हित लघु i2caddr[25];

	mid = cd->module_id;
	fname = (mid < ARRAY_SIZE(module_names)) ? module_names[mid] : शून्य;
	अगर (!fname) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Module ID %u for device %s has no name?  The driver might have a configuration problem.",
			   mid,
			   hdw->hdw_desc->description);
		वापस -EINVAL;
	पूर्ण
	pvr2_trace(PVR2_TRACE_INIT,
		   "Module ID %u (%s) for device %s being loaded...",
		   mid, fname,
		   hdw->hdw_desc->description);

	i2ccnt = pvr2_copy_i2c_addr_list(i2caddr, cd->i2c_address_list,
					 ARRAY_SIZE(i2caddr));
	अगर (!i2ccnt && ((p = (mid < ARRAY_SIZE(module_i2c_addresses)) ?
			 module_i2c_addresses[mid] : शून्य) != शून्य)) अणु
		/* Second chance: Try शेष i2c address list */
		i2ccnt = pvr2_copy_i2c_addr_list(i2caddr, p,
						 ARRAY_SIZE(i2caddr));
		अगर (i2ccnt) अणु
			pvr2_trace(PVR2_TRACE_INIT,
				   "Module ID %u: Using default i2c address list",
				   mid);
		पूर्ण
	पूर्ण

	अगर (!i2ccnt) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Module ID %u (%s) for device %s: No i2c addresses.	The driver might have a configuration problem.",
			   mid, fname, hdw->hdw_desc->description);
		वापस -EINVAL;
	पूर्ण

	अगर (i2ccnt == 1) अणु
		pvr2_trace(PVR2_TRACE_INIT,
			   "Module ID %u: Setting up with specified i2c address 0x%x",
			   mid, i2caddr[0]);
		sd = v4l2_i2c_new_subdev(&hdw->v4l2_dev, &hdw->i2c_adap,
					 fname, i2caddr[0], शून्य);
	पूर्ण अन्यथा अणु
		pvr2_trace(PVR2_TRACE_INIT,
			   "Module ID %u: Setting up with address probe list",
			   mid);
		sd = v4l2_i2c_new_subdev(&hdw->v4l2_dev, &hdw->i2c_adap,
					 fname, 0, i2caddr);
	पूर्ण

	अगर (!sd) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Module ID %u (%s) for device %s failed to load.  Possible missing sub-device kernel module or initialization failure within module.",
			   mid, fname, hdw->hdw_desc->description);
		वापस -EIO;
	पूर्ण

	/* Tag this sub-device instance with the module ID we know about.
	   In other places we'll use that tag to determine अगर the instance
	   requires special handling. */
	sd->grp_id = mid;

	pvr2_trace(PVR2_TRACE_INFO, "Attached sub-driver %s", fname);


	/* client-specअगरic setup... */
	चयन (mid) अणु
	हाल PVR2_CLIENT_ID_CX25840:
	हाल PVR2_CLIENT_ID_SAA7115:
		hdw->decoder_client_id = mid;
		अवरोध;
	शेष: अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम pvr2_hdw_load_modules(काष्ठा pvr2_hdw *hdw)
अणु
	अचिन्हित पूर्णांक idx;
	स्थिर काष्ठा pvr2_string_table *cm;
	स्थिर काष्ठा pvr2_device_client_table *ct;
	पूर्णांक okFl = !0;

	cm = &hdw->hdw_desc->client_modules;
	क्रम (idx = 0; idx < cm->cnt; idx++) अणु
		request_module(cm->lst[idx]);
	पूर्ण

	ct = &hdw->hdw_desc->client_table;
	क्रम (idx = 0; idx < ct->cnt; idx++) अणु
		अगर (pvr2_hdw_load_subdev(hdw, &ct->lst[idx]) < 0) okFl = 0;
	पूर्ण
	अगर (!okFl) अणु
		hdw->flag_modulefail = !0;
		pvr2_hdw_render_useless(hdw);
	पूर्ण
पूर्ण


अटल व्योम pvr2_hdw_setup_low(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक idx;
	काष्ठा pvr2_ctrl *cptr;
	पूर्णांक reloadFl = 0;
	अगर (hdw->hdw_desc->fx2_firmware.cnt) अणु
		अगर (!reloadFl) अणु
			reloadFl =
				(hdw->usb_पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs
				 == 0);
			अगर (reloadFl) अणु
				pvr2_trace(PVR2_TRACE_INIT,
					   "USB endpoint config looks strange; possibly firmware needs to be loaded");
			पूर्ण
		पूर्ण
		अगर (!reloadFl) अणु
			reloadFl = !pvr2_hdw_check_firmware(hdw);
			अगर (reloadFl) अणु
				pvr2_trace(PVR2_TRACE_INIT,
					   "Check for FX2 firmware failed; possibly firmware needs to be loaded");
			पूर्ण
		पूर्ण
		अगर (reloadFl) अणु
			अगर (pvr2_upload_firmware1(hdw) != 0) अणु
				pvr2_trace(PVR2_TRACE_ERROR_LEGS,
					   "Failure uploading firmware1");
			पूर्ण
			वापस;
		पूर्ण
	पूर्ण
	hdw->fw1_state = FW1_STATE_OK;

	अगर (!pvr2_hdw_dev_ok(hdw)) वापस;

	hdw->क्रमce_dirty = !0;

	अगर (!hdw->hdw_desc->flag_no_घातerup) अणु
		pvr2_hdw_cmd_घातerup(hdw);
		अगर (!pvr2_hdw_dev_ok(hdw)) वापस;
	पूर्ण

	/* Take the IR chip out of reset, अगर appropriate */
	अगर (hdw->ir_scheme_active == PVR2_IR_SCHEME_ZILOG) अणु
		pvr2_issue_simple_cmd(hdw,
				      FX2CMD_HCW_ZILOG_RESET |
				      (1 << 8) |
				      ((0) << 16));
	पूर्ण

	/* This step MUST happen after the earlier घातerup step */
	pvr2_i2c_core_init(hdw);
	अगर (!pvr2_hdw_dev_ok(hdw)) वापस;

	/* Reset demod only on Hauppauge 160xxx platक्रमm */
	अगर (le16_to_cpu(hdw->usb_dev->descriptor.idVenकरोr) == 0x2040 &&
	    (le16_to_cpu(hdw->usb_dev->descriptor.idProduct) == 0x7502 ||
	     le16_to_cpu(hdw->usb_dev->descriptor.idProduct) == 0x7510)) अणु
		pr_info("%s(): resetting 160xxx demod\n", __func__);
		/* TODO: not sure this is proper place to reset once only */
		pvr2_issue_simple_cmd(hdw,
				      FX2CMD_HCW_DEMOD_RESET_PIN |
				      (1 << 8) |
				      ((0) << 16));
		usleep_range(10000, 10500);
		pvr2_issue_simple_cmd(hdw,
				      FX2CMD_HCW_DEMOD_RESET_PIN |
				      (1 << 8) |
				      ((1) << 16));
		usleep_range(10000, 10500);
	पूर्ण

	pvr2_hdw_load_modules(hdw);
	अगर (!pvr2_hdw_dev_ok(hdw)) वापस;

	v4l2_device_call_all(&hdw->v4l2_dev, 0, core, load_fw);

	क्रम (idx = 0; idx < CTRLDEF_COUNT; idx++) अणु
		cptr = hdw->controls + idx;
		अगर (cptr->info->skip_init) जारी;
		अगर (!cptr->info->set_value) जारी;
		cptr->info->set_value(cptr,~0,cptr->info->शेष_value);
	पूर्ण

	pvr2_hdw_cx25840_vbi_hack(hdw);

	/* Set up special शेष values क्रम the television and radio
	   frequencies here.  It's not really important what these शेषs
	   are, but I set them to something usable in the Chicago area just
	   to make driver testing a little easier. */

	hdw->freqValTelevision = शेष_tv_freq;
	hdw->freqValRadio = शेष_radio_freq;

	// Do not use pvr2_reset_ctl_endpoपूर्णांकs() here.  It is not
	// thपढ़ो-safe against the normal pvr2_send_request() mechanism.
	// (We should make it thपढ़ो safe).

	अगर (hdw->hdw_desc->flag_has_hauppauge_rom) अणु
		ret = pvr2_hdw_get_eeprom_addr(hdw);
		अगर (!pvr2_hdw_dev_ok(hdw)) वापस;
		अगर (ret < 0) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "Unable to determine location of eeprom, skipping");
		पूर्ण अन्यथा अणु
			hdw->eeprom_addr = ret;
			pvr2_eeprom_analyze(hdw);
			अगर (!pvr2_hdw_dev_ok(hdw)) वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		hdw->tuner_type = hdw->hdw_desc->शेष_tuner_type;
		hdw->tuner_updated = !0;
		hdw->std_mask_eeprom = V4L2_STD_ALL;
	पूर्ण

	अगर (hdw->serial_number) अणु
		idx = scnम_लिखो(hdw->identअगरier, माप(hdw->identअगरier) - 1,
				"sn-%lu", hdw->serial_number);
	पूर्ण अन्यथा अगर (hdw->unit_number >= 0) अणु
		idx = scnम_लिखो(hdw->identअगरier, माप(hdw->identअगरier) - 1,
				"unit-%c",
				hdw->unit_number + 'a');
	पूर्ण अन्यथा अणु
		idx = scnम_लिखो(hdw->identअगरier, माप(hdw->identअगरier) - 1,
				"unit-??");
	पूर्ण
	hdw->identअगरier[idx] = 0;

	pvr2_hdw_setup_std(hdw);

	अगर (!get_शेष_tuner_type(hdw)) अणु
		pvr2_trace(PVR2_TRACE_INIT,
			   "pvr2_hdw_setup: Tuner type overridden to %d",
			   hdw->tuner_type);
	पूर्ण


	अगर (!pvr2_hdw_dev_ok(hdw)) वापस;

	अगर (hdw->hdw_desc->संकेत_routing_scheme ==
	    PVR2_ROUTING_SCHEME_GOTVIEW) अणु
		/* Ensure that GPIO 11 is set to output क्रम GOTVIEW
		   hardware. */
		pvr2_hdw_gpio_chg_dir(hdw,(1 << 11),~0);
	पूर्ण

	pvr2_hdw_commit_setup(hdw);

	hdw->vid_stream = pvr2_stream_create();
	अगर (!pvr2_hdw_dev_ok(hdw)) वापस;
	pvr2_trace(PVR2_TRACE_INIT,
		   "pvr2_hdw_setup: video stream is %p",hdw->vid_stream);
	अगर (hdw->vid_stream) अणु
		idx = get_शेष_error_tolerance(hdw);
		अगर (idx) अणु
			pvr2_trace(PVR2_TRACE_INIT,
				   "pvr2_hdw_setup: video stream %p setting tolerance %u",
				   hdw->vid_stream,idx);
		पूर्ण
		pvr2_stream_setup(hdw->vid_stream,hdw->usb_dev,
				  PVR2_VID_ENDPOINT,idx);
	पूर्ण

	अगर (!pvr2_hdw_dev_ok(hdw)) वापस;

	hdw->flag_init_ok = !0;

	pvr2_hdw_state_sched(hdw);
पूर्ण


/* Set up the काष्ठाure and attempt to put the device पूर्णांकo a usable state.
   This can be a समय-consuming operation, which is why it is not करोne
   पूर्णांकernally as part of the create() step. */
अटल व्योम pvr2_hdw_setup(काष्ठा pvr2_hdw *hdw)
अणु
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_setup(hdw=%p) begin",hdw);
	करो अणु
		pvr2_hdw_setup_low(hdw);
		pvr2_trace(PVR2_TRACE_INIT,
			   "pvr2_hdw_setup(hdw=%p) done, ok=%d init_ok=%d",
			   hdw,pvr2_hdw_dev_ok(hdw),hdw->flag_init_ok);
		अगर (pvr2_hdw_dev_ok(hdw)) अणु
			अगर (hdw->flag_init_ok) अणु
				pvr2_trace(
					PVR2_TRACE_INFO,
					"Device initialization completed successfully.");
				अवरोध;
			पूर्ण
			अगर (hdw->fw1_state == FW1_STATE_RELOAD) अणु
				pvr2_trace(
					PVR2_TRACE_INFO,
					"Device microcontroller firmware (re)loaded; it should now reset and reconnect.");
				अवरोध;
			पूर्ण
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Device initialization was not successful.");
			अगर (hdw->fw1_state == FW1_STATE_MISSING) अणु
				pvr2_trace(
					PVR2_TRACE_ERROR_LEGS,
					"Giving up since device microcontroller firmware appears to be missing.");
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (hdw->flag_modulefail) अणु
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"***WARNING*** pvrusb2 driver initialization failed due to the failure of one or more sub-device kernel modules.");
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"You need to resolve the failing condition before this driver can function.  There should be some earlier messages giving more information about the problem.");
			अवरोध;
		पूर्ण
		अगर (procreload) अणु
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Attempting pvrusb2 recovery by reloading primary firmware.");
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"If this works, device should disconnect and reconnect in a sane state.");
			hdw->fw1_state = FW1_STATE_UNKNOWN;
			pvr2_upload_firmware1(hdw);
		पूर्ण अन्यथा अणु
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"***WARNING*** pvrusb2 device hardware appears to be jammed and I can't clear it.");
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"You might need to power cycle the pvrusb2 device in order to recover.");
		पूर्ण
	पूर्ण जबतक (0);
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_setup(hdw=%p) end",hdw);
पूर्ण


/* Perक्रमm second stage initialization.  Set callback poपूर्णांकer first so that
   we can aव्योम a possible initialization race (अगर the kernel thपढ़ो runs
   beक्रमe the callback has been set). */
पूर्णांक pvr2_hdw_initialize(काष्ठा pvr2_hdw *hdw,
			व्योम (*callback_func)(व्योम *),
			व्योम *callback_data)
अणु
	LOCK_TAKE(hdw->big_lock); करो अणु
		अगर (hdw->flag_disconnected) अणु
			/* Handle a race here: If we're alपढ़ोy
			   disconnected by this poपूर्णांक, then give up.  If we
			   get past this then we'll reमुख्य connected क्रम
			   the duration of initialization since the entire
			   initialization sequence is now रक्षित by the
			   big_lock. */
			अवरोध;
		पूर्ण
		hdw->state_data = callback_data;
		hdw->state_func = callback_func;
		pvr2_hdw_setup(hdw);
	पूर्ण जबतक (0); LOCK_GIVE(hdw->big_lock);
	वापस hdw->flag_init_ok;
पूर्ण


/* Create, set up, and वापस a काष्ठाure क्रम पूर्णांकeracting with the
   underlying hardware.  */
काष्ठा pvr2_hdw *pvr2_hdw_create(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				 स्थिर काष्ठा usb_device_id *devid)
अणु
	अचिन्हित पूर्णांक idx,cnt1,cnt2,m;
	काष्ठा pvr2_hdw *hdw = शून्य;
	पूर्णांक valid_std_mask;
	काष्ठा pvr2_ctrl *cptr;
	काष्ठा usb_device *usb_dev;
	स्थिर काष्ठा pvr2_device_desc *hdw_desc;
	__u8 अगरnum;
	काष्ठा v4l2_queryctrl qctrl;
	काष्ठा pvr2_ctl_info *ciptr;

	usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	hdw_desc = (स्थिर काष्ठा pvr2_device_desc *)(devid->driver_info);

	अगर (hdw_desc == शून्य) अणु
		pvr2_trace(PVR2_TRACE_INIT, "pvr2_hdw_create: No device description pointer, unable to continue.");
		pvr2_trace(PVR2_TRACE_INIT,
			   "If you have a new device type, please contact Mike Isely <isely@pobox.com> to get it included in the driver");
		जाओ fail;
	पूर्ण

	hdw = kzalloc(माप(*hdw),GFP_KERNEL);
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_create: hdw=%p, type \"%s\"",
		   hdw,hdw_desc->description);
	pvr2_trace(PVR2_TRACE_INFO, "Hardware description: %s",
		hdw_desc->description);
	अगर (hdw_desc->flag_is_experimental) अणु
		pvr2_trace(PVR2_TRACE_INFO, "**********");
		pvr2_trace(PVR2_TRACE_INFO,
			   "***WARNING*** Support for this device (%s) is experimental.",
							      hdw_desc->description);
		pvr2_trace(PVR2_TRACE_INFO,
			   "Important functionality might not be entirely working.");
		pvr2_trace(PVR2_TRACE_INFO,
			   "Please consider contacting the driver author to help with further stabilization of the driver.");
		pvr2_trace(PVR2_TRACE_INFO, "**********");
	पूर्ण
	अगर (!hdw) जाओ fail;

	समयr_setup(&hdw->quiescent_समयr, pvr2_hdw_quiescent_समयout, 0);

	समयr_setup(&hdw->decoder_stabilization_समयr,
		    pvr2_hdw_decoder_stabilization_समयout, 0);

	समयr_setup(&hdw->encoder_रुको_समयr, pvr2_hdw_encoder_रुको_समयout,
		    0);

	समयr_setup(&hdw->encoder_run_समयr, pvr2_hdw_encoder_run_समयout, 0);

	hdw->master_state = PVR2_STATE_DEAD;

	init_रुकोqueue_head(&hdw->state_रुको_data);

	hdw->tuner_संकेत_stale = !0;
	cx2341x_fill_शेषs(&hdw->enc_ctl_state);

	/* Calculate which inमाला_दो are OK */
	m = 0;
	अगर (hdw_desc->flag_has_analogtuner) m |= 1 << PVR2_CVAL_INPUT_TV;
	अगर (hdw_desc->digital_control_scheme != PVR2_DIGITAL_SCHEME_NONE) अणु
		m |= 1 << PVR2_CVAL_INPUT_DTV;
	पूर्ण
	अगर (hdw_desc->flag_has_svideo) m |= 1 << PVR2_CVAL_INPUT_SVIDEO;
	अगर (hdw_desc->flag_has_composite) m |= 1 << PVR2_CVAL_INPUT_COMPOSITE;
	अगर (hdw_desc->flag_has_fmradio) m |= 1 << PVR2_CVAL_INPUT_RADIO;
	hdw->input_avail_mask = m;
	hdw->input_allowed_mask = hdw->input_avail_mask;

	/* If not a hybrid device, pathway_state never changes.  So
	   initialize it here to what it should क्रमever be. */
	अगर (!(hdw->input_avail_mask & (1 << PVR2_CVAL_INPUT_DTV))) अणु
		hdw->pathway_state = PVR2_PATHWAY_ANALOG;
	पूर्ण अन्यथा अगर (!(hdw->input_avail_mask & (1 << PVR2_CVAL_INPUT_TV))) अणु
		hdw->pathway_state = PVR2_PATHWAY_DIGITAL;
	पूर्ण

	hdw->control_cnt = CTRLDEF_COUNT;
	hdw->control_cnt += MPEGDEF_COUNT;
	hdw->controls = kसुस्मृति(hdw->control_cnt, माप(काष्ठा pvr2_ctrl),
				GFP_KERNEL);
	अगर (!hdw->controls) जाओ fail;
	hdw->hdw_desc = hdw_desc;
	hdw->ir_scheme_active = hdw->hdw_desc->ir_scheme;
	क्रम (idx = 0; idx < hdw->control_cnt; idx++) अणु
		cptr = hdw->controls + idx;
		cptr->hdw = hdw;
	पूर्ण
	क्रम (idx = 0; idx < 32; idx++) अणु
		hdw->std_mask_ptrs[idx] = hdw->std_mask_names[idx];
	पूर्ण
	क्रम (idx = 0; idx < CTRLDEF_COUNT; idx++) अणु
		cptr = hdw->controls + idx;
		cptr->info = control_defs+idx;
	पूर्ण

	/* Ensure that शेष input choice is a valid one. */
	m = hdw->input_avail_mask;
	अगर (m) क्रम (idx = 0; idx < (माप(m) << 3); idx++) अणु
		अगर (!((1UL << idx) & m)) जारी;
		hdw->input_val = idx;
		अवरोध;
	पूर्ण

	/* Define and configure additional controls from cx2341x module. */
	hdw->mpeg_ctrl_info = kसुस्मृति(MPEGDEF_COUNT,
				      माप(*(hdw->mpeg_ctrl_info)),
				      GFP_KERNEL);
	अगर (!hdw->mpeg_ctrl_info) जाओ fail;
	क्रम (idx = 0; idx < MPEGDEF_COUNT; idx++) अणु
		cptr = hdw->controls + idx + CTRLDEF_COUNT;
		ciptr = &(hdw->mpeg_ctrl_info[idx].info);
		ciptr->desc = hdw->mpeg_ctrl_info[idx].desc;
		ciptr->name = mpeg_ids[idx].strid;
		ciptr->v4l_id = mpeg_ids[idx].id;
		ciptr->skip_init = !0;
		ciptr->get_value = ctrl_cx2341x_get;
		ciptr->get_v4lflags = ctrl_cx2341x_getv4lflags;
		ciptr->is_dirty = ctrl_cx2341x_is_dirty;
		अगर (!idx) ciptr->clear_dirty = ctrl_cx2341x_clear_dirty;
		qctrl.id = ciptr->v4l_id;
		cx2341x_ctrl_query(&hdw->enc_ctl_state,&qctrl);
		अगर (!(qctrl.flags & V4L2_CTRL_FLAG_READ_ONLY)) अणु
			ciptr->set_value = ctrl_cx2341x_set;
		पूर्ण
		strscpy(hdw->mpeg_ctrl_info[idx].desc, qctrl.name,
			माप(hdw->mpeg_ctrl_info[idx].desc));
		ciptr->शेष_value = qctrl.शेष_value;
		चयन (qctrl.type) अणु
		शेष:
		हाल V4L2_CTRL_TYPE_INTEGER:
			ciptr->type = pvr2_ctl_पूर्णांक;
			ciptr->def.type_पूर्णांक.min_value = qctrl.minimum;
			ciptr->def.type_पूर्णांक.max_value = qctrl.maximum;
			अवरोध;
		हाल V4L2_CTRL_TYPE_BOOLEAN:
			ciptr->type = pvr2_ctl_bool;
			अवरोध;
		हाल V4L2_CTRL_TYPE_MENU:
			ciptr->type = pvr2_ctl_क्रमागत;
			ciptr->def.type_क्रमागत.value_names =
				cx2341x_ctrl_get_menu(&hdw->enc_ctl_state,
								ciptr->v4l_id);
			क्रम (cnt1 = 0;
			     ciptr->def.type_क्रमागत.value_names[cnt1] != शून्य;
			     cnt1++) अणु पूर्ण
			ciptr->def.type_क्रमागत.count = cnt1;
			अवरोध;
		पूर्ण
		cptr->info = ciptr;
	पूर्ण

	// Initialize control data regarding video standard masks
	valid_std_mask = pvr2_std_get_usable();
	क्रम (idx = 0; idx < 32; idx++) अणु
		अगर (!(valid_std_mask & (1UL << idx))) जारी;
		cnt1 = pvr2_std_id_to_str(
			hdw->std_mask_names[idx],
			माप(hdw->std_mask_names[idx])-1,
			1UL << idx);
		hdw->std_mask_names[idx][cnt1] = 0;
	पूर्ण
	cptr = pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_STDAVAIL);
	अगर (cptr) अणु
		स_नकल(&hdw->std_info_avail,cptr->info,
		       माप(hdw->std_info_avail));
		cptr->info = &hdw->std_info_avail;
		hdw->std_info_avail.def.type_biपंचांगask.bit_names =
			hdw->std_mask_ptrs;
		hdw->std_info_avail.def.type_biपंचांगask.valid_bits =
			valid_std_mask;
	पूर्ण
	cptr = pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_STDCUR);
	अगर (cptr) अणु
		स_नकल(&hdw->std_info_cur,cptr->info,
		       माप(hdw->std_info_cur));
		cptr->info = &hdw->std_info_cur;
		hdw->std_info_cur.def.type_biपंचांगask.bit_names =
			hdw->std_mask_ptrs;
		hdw->std_info_cur.def.type_biपंचांगask.valid_bits =
			valid_std_mask;
	पूर्ण
	cptr = pvr2_hdw_get_ctrl_by_id(hdw,PVR2_CID_STDDETECT);
	अगर (cptr) अणु
		स_नकल(&hdw->std_info_detect,cptr->info,
		       माप(hdw->std_info_detect));
		cptr->info = &hdw->std_info_detect;
		hdw->std_info_detect.def.type_biपंचांगask.bit_names =
			hdw->std_mask_ptrs;
		hdw->std_info_detect.def.type_biपंचांगask.valid_bits =
			valid_std_mask;
	पूर्ण

	hdw->cropcap_stale = !0;
	hdw->eeprom_addr = -1;
	hdw->unit_number = -1;
	hdw->v4l_minor_number_video = -1;
	hdw->v4l_minor_number_vbi = -1;
	hdw->v4l_minor_number_radio = -1;
	hdw->ctl_ग_लिखो_buffer = kदो_स्मृति(PVR2_CTL_BUFFSIZE,GFP_KERNEL);
	अगर (!hdw->ctl_ग_लिखो_buffer) जाओ fail;
	hdw->ctl_पढ़ो_buffer = kदो_स्मृति(PVR2_CTL_BUFFSIZE,GFP_KERNEL);
	अगर (!hdw->ctl_पढ़ो_buffer) जाओ fail;
	hdw->ctl_ग_लिखो_urb = usb_alloc_urb(0,GFP_KERNEL);
	अगर (!hdw->ctl_ग_लिखो_urb) जाओ fail;
	hdw->ctl_पढ़ो_urb = usb_alloc_urb(0,GFP_KERNEL);
	अगर (!hdw->ctl_पढ़ो_urb) जाओ fail;

	अगर (v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &hdw->v4l2_dev) != 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Error registering with v4l core, giving up");
		जाओ fail;
	पूर्ण
	mutex_lock(&pvr2_unit_mtx);
	करो अणु
		क्रम (idx = 0; idx < PVR_NUM; idx++) अणु
			अगर (unit_poपूर्णांकers[idx]) जारी;
			hdw->unit_number = idx;
			unit_poपूर्णांकers[idx] = hdw;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (0);
	mutex_unlock(&pvr2_unit_mtx);

	cnt1 = 0;
	cnt2 = scnम_लिखो(hdw->name+cnt1,माप(hdw->name)-cnt1,"pvrusb2");
	cnt1 += cnt2;
	अगर (hdw->unit_number >= 0) अणु
		cnt2 = scnम_लिखो(hdw->name+cnt1,माप(hdw->name)-cnt1,"_%c",
				 ('a' + hdw->unit_number));
		cnt1 += cnt2;
	पूर्ण
	अगर (cnt1 >= माप(hdw->name)) cnt1 = माप(hdw->name)-1;
	hdw->name[cnt1] = 0;

	INIT_WORK(&hdw->workpoll,pvr2_hdw_worker_poll);

	pvr2_trace(PVR2_TRACE_INIT,"Driver unit number is %d, name is %s",
		   hdw->unit_number,hdw->name);

	hdw->tuner_type = -1;
	hdw->flag_ok = !0;

	hdw->usb_पूर्णांकf = पूर्णांकf;
	hdw->usb_dev = usb_dev;

	usb_make_path(hdw->usb_dev, hdw->bus_info, माप(hdw->bus_info));

	अगरnum = hdw->usb_पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	usb_set_पूर्णांकerface(hdw->usb_dev,अगरnum,0);

	mutex_init(&hdw->ctl_lock_mutex);
	mutex_init(&hdw->big_lock_mutex);

	वापस hdw;
 fail:
	अगर (hdw) अणु
		del_समयr_sync(&hdw->quiescent_समयr);
		del_समयr_sync(&hdw->decoder_stabilization_समयr);
		del_समयr_sync(&hdw->encoder_run_समयr);
		del_समयr_sync(&hdw->encoder_रुको_समयr);
		flush_work(&hdw->workpoll);
		usb_मुक्त_urb(hdw->ctl_पढ़ो_urb);
		usb_मुक्त_urb(hdw->ctl_ग_लिखो_urb);
		kमुक्त(hdw->ctl_पढ़ो_buffer);
		kमुक्त(hdw->ctl_ग_लिखो_buffer);
		kमुक्त(hdw->controls);
		kमुक्त(hdw->mpeg_ctrl_info);
		kमुक्त(hdw);
	पूर्ण
	वापस शून्य;
पूर्ण


/* Remove _all_ associations between this driver and the underlying USB
   layer. */
अटल व्योम pvr2_hdw_हटाओ_usb_stuff(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->flag_disconnected) वापस;
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_remove_usb_stuff: hdw=%p",hdw);
	अगर (hdw->ctl_पढ़ो_urb) अणु
		usb_समाप्त_urb(hdw->ctl_पढ़ो_urb);
		usb_मुक्त_urb(hdw->ctl_पढ़ो_urb);
		hdw->ctl_पढ़ो_urb = शून्य;
	पूर्ण
	अगर (hdw->ctl_ग_लिखो_urb) अणु
		usb_समाप्त_urb(hdw->ctl_ग_लिखो_urb);
		usb_मुक्त_urb(hdw->ctl_ग_लिखो_urb);
		hdw->ctl_ग_लिखो_urb = शून्य;
	पूर्ण
	अगर (hdw->ctl_पढ़ो_buffer) अणु
		kमुक्त(hdw->ctl_पढ़ो_buffer);
		hdw->ctl_पढ़ो_buffer = शून्य;
	पूर्ण
	अगर (hdw->ctl_ग_लिखो_buffer) अणु
		kमुक्त(hdw->ctl_ग_लिखो_buffer);
		hdw->ctl_ग_लिखो_buffer = शून्य;
	पूर्ण
	hdw->flag_disconnected = !0;
	/* If we करोn't करो this, then there will be a dangling काष्ठा device
	   reference to our disappearing device persisting inside the V4L
	   core... */
	v4l2_device_disconnect(&hdw->v4l2_dev);
	hdw->usb_dev = शून्य;
	hdw->usb_पूर्णांकf = शून्य;
	pvr2_hdw_render_useless(hdw);
पूर्ण

व्योम pvr2_hdw_set_v4l2_dev(काष्ठा pvr2_hdw *hdw, काष्ठा video_device *vdev)
अणु
	vdev->v4l2_dev = &hdw->v4l2_dev;
पूर्ण

/* Destroy hardware पूर्णांकeraction काष्ठाure */
व्योम pvr2_hdw_destroy(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (!hdw) वापस;
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_destroy: hdw=%p",hdw);
	flush_work(&hdw->workpoll);
	del_समयr_sync(&hdw->quiescent_समयr);
	del_समयr_sync(&hdw->decoder_stabilization_समयr);
	del_समयr_sync(&hdw->encoder_run_समयr);
	del_समयr_sync(&hdw->encoder_रुको_समयr);
	अगर (hdw->fw_buffer) अणु
		kमुक्त(hdw->fw_buffer);
		hdw->fw_buffer = शून्य;
	पूर्ण
	अगर (hdw->vid_stream) अणु
		pvr2_stream_destroy(hdw->vid_stream);
		hdw->vid_stream = शून्य;
	पूर्ण
	pvr2_i2c_core_करोne(hdw);
	v4l2_device_unरेजिस्टर(&hdw->v4l2_dev);
	pvr2_hdw_हटाओ_usb_stuff(hdw);
	mutex_lock(&pvr2_unit_mtx);
	करो अणु
		अगर ((hdw->unit_number >= 0) &&
		    (hdw->unit_number < PVR_NUM) &&
		    (unit_poपूर्णांकers[hdw->unit_number] == hdw)) अणु
			unit_poपूर्णांकers[hdw->unit_number] = शून्य;
		पूर्ण
	पूर्ण जबतक (0);
	mutex_unlock(&pvr2_unit_mtx);
	kमुक्त(hdw->controls);
	kमुक्त(hdw->mpeg_ctrl_info);
	kमुक्त(hdw);
पूर्ण


पूर्णांक pvr2_hdw_dev_ok(काष्ठा pvr2_hdw *hdw)
अणु
	वापस (hdw && hdw->flag_ok);
पूर्ण


/* Called when hardware has been unplugged */
व्योम pvr2_hdw_disconnect(काष्ठा pvr2_hdw *hdw)
अणु
	pvr2_trace(PVR2_TRACE_INIT,"pvr2_hdw_disconnect(hdw=%p)",hdw);
	LOCK_TAKE(hdw->big_lock);
	LOCK_TAKE(hdw->ctl_lock);
	pvr2_hdw_हटाओ_usb_stuff(hdw);
	LOCK_GIVE(hdw->ctl_lock);
	LOCK_GIVE(hdw->big_lock);
पूर्ण


/* Get the number of defined controls */
अचिन्हित पूर्णांक pvr2_hdw_get_ctrl_count(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->control_cnt;
पूर्ण


/* Retrieve a control handle given its index (0..count-1) */
काष्ठा pvr2_ctrl *pvr2_hdw_get_ctrl_by_index(काष्ठा pvr2_hdw *hdw,
					     अचिन्हित पूर्णांक idx)
अणु
	अगर (idx >= hdw->control_cnt) वापस शून्य;
	वापस hdw->controls + idx;
पूर्ण


/* Retrieve a control handle given its index (0..count-1) */
काष्ठा pvr2_ctrl *pvr2_hdw_get_ctrl_by_id(काष्ठा pvr2_hdw *hdw,
					  अचिन्हित पूर्णांक ctl_id)
अणु
	काष्ठा pvr2_ctrl *cptr;
	अचिन्हित पूर्णांक idx;
	पूर्णांक i;

	/* This could be made a lot more efficient, but क्रम now... */
	क्रम (idx = 0; idx < hdw->control_cnt; idx++) अणु
		cptr = hdw->controls + idx;
		i = cptr->info->पूर्णांकernal_id;
		अगर (i && (i == ctl_id)) वापस cptr;
	पूर्ण
	वापस शून्य;
पूर्ण


/* Given a V4L ID, retrieve the control काष्ठाure associated with it. */
काष्ठा pvr2_ctrl *pvr2_hdw_get_ctrl_v4l(काष्ठा pvr2_hdw *hdw,अचिन्हित पूर्णांक ctl_id)
अणु
	काष्ठा pvr2_ctrl *cptr;
	अचिन्हित पूर्णांक idx;
	पूर्णांक i;

	/* This could be made a lot more efficient, but क्रम now... */
	क्रम (idx = 0; idx < hdw->control_cnt; idx++) अणु
		cptr = hdw->controls + idx;
		i = cptr->info->v4l_id;
		अगर (i && (i == ctl_id)) वापस cptr;
	पूर्ण
	वापस शून्य;
पूर्ण


/* Given a V4L ID क्रम its immediate predecessor, retrieve the control
   काष्ठाure associated with it. */
काष्ठा pvr2_ctrl *pvr2_hdw_get_ctrl_nextv4l(काष्ठा pvr2_hdw *hdw,
					    अचिन्हित पूर्णांक ctl_id)
अणु
	काष्ठा pvr2_ctrl *cptr,*cp2;
	अचिन्हित पूर्णांक idx;
	पूर्णांक i;

	/* This could be made a lot more efficient, but क्रम now... */
	cp2 = शून्य;
	क्रम (idx = 0; idx < hdw->control_cnt; idx++) अणु
		cptr = hdw->controls + idx;
		i = cptr->info->v4l_id;
		अगर (!i) जारी;
		अगर (i <= ctl_id) जारी;
		अगर (cp2 && (cp2->info->v4l_id < i)) जारी;
		cp2 = cptr;
	पूर्ण
	वापस cp2;
	वापस शून्य;
पूर्ण


अटल स्थिर अक्षर *get_ctrl_typename(क्रमागत pvr2_ctl_type tp)
अणु
	चयन (tp) अणु
	हाल pvr2_ctl_पूर्णांक: वापस "integer";
	हाल pvr2_ctl_क्रमागत: वापस "enum";
	हाल pvr2_ctl_bool: वापस "boolean";
	हाल pvr2_ctl_biपंचांगask: वापस "bitmask";
	पूर्ण
	वापस "";
पूर्ण


अटल व्योम pvr2_subdev_set_control(काष्ठा pvr2_hdw *hdw, पूर्णांक id,
				    स्थिर अक्षर *name, पूर्णांक val)
अणु
	काष्ठा v4l2_control ctrl;
	काष्ठा v4l2_subdev *sd;

	pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 %s=%d", name, val);
	स_रखो(&ctrl, 0, माप(ctrl));
	ctrl.id = id;
	ctrl.value = val;

	v4l2_device_क्रम_each_subdev(sd, &hdw->v4l2_dev)
		v4l2_s_ctrl(शून्य, sd->ctrl_handler, &ctrl);
पूर्ण

#घोषणा PVR2_SUBDEV_SET_CONTROL(hdw, id, lab) \
	अगर ((hdw)->lab##_dirty || (hdw)->क्रमce_dirty) अणु		\
		pvr2_subdev_set_control(hdw, id, #lab, (hdw)->lab##_val); \
	पूर्ण

अटल v4l2_std_id pvr2_hdw_get_detected_std(काष्ठा pvr2_hdw *hdw)
अणु
	v4l2_std_id std;
	std = (v4l2_std_id)hdw->std_mask_avail;
	v4l2_device_call_all(&hdw->v4l2_dev, 0,
			     video, querystd, &std);
	वापस std;
पूर्ण

/* Execute whatever commands are required to update the state of all the
   sub-devices so that they match our current control values. */
अटल व्योम pvr2_subdev_update(काष्ठा pvr2_hdw *hdw)
अणु
	काष्ठा v4l2_subdev *sd;
	अचिन्हित पूर्णांक id;
	pvr2_subdev_update_func fp;

	pvr2_trace(PVR2_TRACE_CHIPS, "subdev update...");

	अगर (hdw->tuner_updated || hdw->क्रमce_dirty) अणु
		काष्ठा tuner_setup setup;
		pvr2_trace(PVR2_TRACE_CHIPS, "subdev tuner set_type(%d)",
			   hdw->tuner_type);
		अगर (((पूर्णांक)(hdw->tuner_type)) >= 0) अणु
			स_रखो(&setup, 0, माप(setup));
			setup.addr = ADDR_UNSET;
			setup.type = hdw->tuner_type;
			setup.mode_mask = T_RADIO | T_ANALOG_TV;
			v4l2_device_call_all(&hdw->v4l2_dev, 0,
					     tuner, s_type_addr, &setup);
		पूर्ण
	पूर्ण

	अगर (hdw->input_dirty || hdw->std_dirty || hdw->क्रमce_dirty) अणु
		pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 set_standard");
		अगर (hdw->input_val == PVR2_CVAL_INPUT_RADIO) अणु
			v4l2_device_call_all(&hdw->v4l2_dev, 0,
					     tuner, s_radio);
		पूर्ण अन्यथा अणु
			v4l2_std_id vs;
			vs = hdw->std_mask_cur;
			v4l2_device_call_all(&hdw->v4l2_dev, 0,
					     video, s_std, vs);
			pvr2_hdw_cx25840_vbi_hack(hdw);
		पूर्ण
		hdw->tuner_संकेत_stale = !0;
		hdw->cropcap_stale = !0;
	पूर्ण

	PVR2_SUBDEV_SET_CONTROL(hdw, V4L2_CID_BRIGHTNESS, brightness);
	PVR2_SUBDEV_SET_CONTROL(hdw, V4L2_CID_CONTRAST, contrast);
	PVR2_SUBDEV_SET_CONTROL(hdw, V4L2_CID_SATURATION, saturation);
	PVR2_SUBDEV_SET_CONTROL(hdw, V4L2_CID_HUE, hue);
	PVR2_SUBDEV_SET_CONTROL(hdw, V4L2_CID_AUDIO_MUTE, mute);
	PVR2_SUBDEV_SET_CONTROL(hdw, V4L2_CID_AUDIO_VOLUME, volume);
	PVR2_SUBDEV_SET_CONTROL(hdw, V4L2_CID_AUDIO_BALANCE, balance);
	PVR2_SUBDEV_SET_CONTROL(hdw, V4L2_CID_AUDIO_BASS, bass);
	PVR2_SUBDEV_SET_CONTROL(hdw, V4L2_CID_AUDIO_TREBLE, treble);

	अगर (hdw->input_dirty || hdw->audiomode_dirty || hdw->क्रमce_dirty) अणु
		काष्ठा v4l2_tuner vt;
		स_रखो(&vt, 0, माप(vt));
		vt.type = (hdw->input_val == PVR2_CVAL_INPUT_RADIO) ?
			V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
		vt.audmode = hdw->audiomode_val;
		v4l2_device_call_all(&hdw->v4l2_dev, 0, tuner, s_tuner, &vt);
	पूर्ण

	अगर (hdw->freqDirty || hdw->क्रमce_dirty) अणु
		अचिन्हित दीर्घ fv;
		काष्ठा v4l2_frequency freq;
		fv = pvr2_hdw_get_cur_freq(hdw);
		pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 set_freq(%lu)", fv);
		अगर (hdw->tuner_संकेत_stale) pvr2_hdw_status_poll(hdw);
		स_रखो(&freq, 0, माप(freq));
		अगर (hdw->tuner_संकेत_info.capability & V4L2_TUNER_CAP_LOW) अणु
			/* ((fv * 1000) / 62500) */
			freq.frequency = (fv * 2) / 125;
		पूर्ण अन्यथा अणु
			freq.frequency = fv / 62500;
		पूर्ण
		/* tuner-core currently करोesn't seem to care about this, but
		   let's set it anyway क्रम completeness. */
		अगर (hdw->input_val == PVR2_CVAL_INPUT_RADIO) अणु
			freq.type = V4L2_TUNER_RADIO;
		पूर्ण अन्यथा अणु
			freq.type = V4L2_TUNER_ANALOG_TV;
		पूर्ण
		freq.tuner = 0;
		v4l2_device_call_all(&hdw->v4l2_dev, 0, tuner,
				     s_frequency, &freq);
	पूर्ण

	अगर (hdw->res_hor_dirty || hdw->res_ver_dirty || hdw->क्रमce_dirty) अणु
		काष्ठा v4l2_subdev_क्रमmat क्रमmat = अणु
			.which = V4L2_SUBDEV_FORMAT_ACTIVE,
		पूर्ण;

		क्रमmat.क्रमmat.width = hdw->res_hor_val;
		क्रमmat.क्रमmat.height = hdw->res_ver_val;
		क्रमmat.क्रमmat.code = MEDIA_BUS_FMT_FIXED;
		pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 set_size(%dx%d)",
			   क्रमmat.क्रमmat.width, क्रमmat.क्रमmat.height);
		v4l2_device_call_all(&hdw->v4l2_dev, 0, pad, set_fmt,
				     शून्य, &क्रमmat);
	पूर्ण

	अगर (hdw->srate_dirty || hdw->क्रमce_dirty) अणु
		u32 val;
		pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 set_audio %d",
			   hdw->srate_val);
		चयन (hdw->srate_val) अणु
		शेष:
		हाल V4L2_MPEG_AUDIO_SAMPLING_FREQ_48000:
			val = 48000;
			अवरोध;
		हाल V4L2_MPEG_AUDIO_SAMPLING_FREQ_44100:
			val = 44100;
			अवरोध;
		हाल V4L2_MPEG_AUDIO_SAMPLING_FREQ_32000:
			val = 32000;
			अवरोध;
		पूर्ण
		v4l2_device_call_all(&hdw->v4l2_dev, 0,
				     audio, s_घड़ी_freq, val);
	पूर्ण

	/* Unable to set crop parameters; there is apparently no equivalent
	   क्रम VIDIOC_S_CROP */

	v4l2_device_क्रम_each_subdev(sd, &hdw->v4l2_dev) अणु
		id = sd->grp_id;
		अगर (id >= ARRAY_SIZE(pvr2_module_update_functions)) जारी;
		fp = pvr2_module_update_functions[id];
		अगर (!fp) जारी;
		(*fp)(hdw, sd);
	पूर्ण

	अगर (hdw->tuner_संकेत_stale || hdw->cropcap_stale) अणु
		pvr2_hdw_status_poll(hdw);
	पूर्ण
पूर्ण


/* Figure out अगर we need to commit control changes.  If so, mark पूर्णांकernal
   state flags to indicate this fact and वापस true.  Otherwise करो nothing
   अन्यथा and वापस false. */
अटल पूर्णांक pvr2_hdw_commit_setup(काष्ठा pvr2_hdw *hdw)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा pvr2_ctrl *cptr;
	पूर्णांक value;
	पूर्णांक commit_flag = hdw->क्रमce_dirty;
	अक्षर buf[100];
	अचिन्हित पूर्णांक bcnt,ccnt;

	क्रम (idx = 0; idx < hdw->control_cnt; idx++) अणु
		cptr = hdw->controls + idx;
		अगर (!cptr->info->is_dirty) जारी;
		अगर (!cptr->info->is_dirty(cptr)) जारी;
		commit_flag = !0;

		अगर (!(pvrusb2_debug & PVR2_TRACE_CTL)) जारी;
		bcnt = scnम_लिखो(buf,माप(buf),"\"%s\" <-- ",
				 cptr->info->name);
		value = 0;
		cptr->info->get_value(cptr,&value);
		pvr2_ctrl_value_to_sym_पूर्णांकernal(cptr,~0,value,
						buf+bcnt,
						माप(buf)-bcnt,&ccnt);
		bcnt += ccnt;
		bcnt += scnम_लिखो(buf+bcnt,माप(buf)-bcnt," <%s>",
				  get_ctrl_typename(cptr->info->type));
		pvr2_trace(PVR2_TRACE_CTL,
			   "/*--TRACE_COMMIT--*/ %.*s",
			   bcnt,buf);
	पूर्ण

	अगर (!commit_flag) अणु
		/* Nothing has changed */
		वापस 0;
	पूर्ण

	hdw->state_pipeline_config = 0;
	trace_stbit("state_pipeline_config",hdw->state_pipeline_config);
	pvr2_hdw_state_sched(hdw);

	वापस !0;
पूर्ण


/* Perक्रमm all operations needed to commit all control changes.  This must
   be perक्रमmed in synchronization with the pipeline state and is thus
   expected to be called as part of the driver's worker thपढ़ो.  Return
   true अगर commit successful, otherwise वापस false to indicate that
   commit isn't possible at this समय. */
अटल पूर्णांक pvr2_hdw_commit_execute(काष्ठा pvr2_hdw *hdw)
अणु
	अचिन्हित पूर्णांक idx;
	काष्ठा pvr2_ctrl *cptr;
	पूर्णांक disruptive_change;

	अगर (hdw->input_dirty && hdw->state_pathway_ok &&
	    (((hdw->input_val == PVR2_CVAL_INPUT_DTV) ?
	      PVR2_PATHWAY_DIGITAL : PVR2_PATHWAY_ANALOG) !=
	     hdw->pathway_state)) अणु
		/* Change of mode being asked क्रम... */
		hdw->state_pathway_ok = 0;
		trace_stbit("state_pathway_ok", hdw->state_pathway_ok);
	पूर्ण
	अगर (!hdw->state_pathway_ok) अणु
		/* Can't commit anything until pathway is ok. */
		वापस 0;
	पूर्ण

	/* Handle some required side effects when the video standard is
	   changed.... */
	अगर (hdw->std_dirty) अणु
		पूर्णांक nvres;
		पूर्णांक gop_size;
		अगर (hdw->std_mask_cur & V4L2_STD_525_60) अणु
			nvres = 480;
			gop_size = 15;
		पूर्ण अन्यथा अणु
			nvres = 576;
			gop_size = 12;
		पूर्ण
		/* Reग_लिखो the vertical resolution to be appropriate to the
		   video standard that has been selected. */
		अगर (nvres != hdw->res_ver_val) अणु
			hdw->res_ver_val = nvres;
			hdw->res_ver_dirty = !0;
		पूर्ण
		/* Reग_लिखो the GOP size to be appropriate to the video
		   standard that has been selected. */
		अगर (gop_size != hdw->enc_ctl_state.video_gop_size) अणु
			काष्ठा v4l2_ext_controls cs;
			काष्ठा v4l2_ext_control c1;
			स_रखो(&cs, 0, माप(cs));
			स_रखो(&c1, 0, माप(c1));
			cs.controls = &c1;
			cs.count = 1;
			c1.id = V4L2_CID_MPEG_VIDEO_GOP_SIZE;
			c1.value = gop_size;
			cx2341x_ext_ctrls(&hdw->enc_ctl_state, 0, &cs,
					  VIDIOC_S_EXT_CTRLS);
		पूर्ण
	पूर्ण

	/* The broadcast decoder can only scale करोwn, so अगर
	 * res_*_dirty && crop winकरोw < output क्रमmat ==> enlarge crop.
	 *
	 * The mpeg encoder receives fields of res_hor_val करोts and
	 * res_ver_val halflines.  Limits: hor<=720, ver<=576.
	 */
	अगर (hdw->res_hor_dirty && hdw->cropw_val < hdw->res_hor_val) अणु
		hdw->cropw_val = hdw->res_hor_val;
		hdw->cropw_dirty = !0;
	पूर्ण अन्यथा अगर (hdw->cropw_dirty) अणु
		hdw->res_hor_dirty = !0;           /* must rescale */
		hdw->res_hor_val = min(720, hdw->cropw_val);
	पूर्ण
	अगर (hdw->res_ver_dirty && hdw->croph_val < hdw->res_ver_val) अणु
		hdw->croph_val = hdw->res_ver_val;
		hdw->croph_dirty = !0;
	पूर्ण अन्यथा अगर (hdw->croph_dirty) अणु
		पूर्णांक nvres = hdw->std_mask_cur & V4L2_STD_525_60 ? 480 : 576;
		hdw->res_ver_dirty = !0;
		hdw->res_ver_val = min(nvres, hdw->croph_val);
	पूर्ण

	/* If any of the below has changed, then we can't करो the update
	   जबतक the pipeline is running.  Pipeline must be छोड़ोd first
	   and decoder -> encoder connection be made quiescent beक्रमe we
	   can proceed. */
	disruptive_change =
		(hdw->std_dirty ||
		 hdw->enc_unsafe_stale ||
		 hdw->srate_dirty ||
		 hdw->res_ver_dirty ||
		 hdw->res_hor_dirty ||
		 hdw->cropw_dirty ||
		 hdw->croph_dirty ||
		 hdw->input_dirty ||
		 (hdw->active_stream_type != hdw->desired_stream_type));
	अगर (disruptive_change && !hdw->state_pipeline_idle) अणु
		/* Pipeline is not idle; we can't proceed.  Arrange to
		   cause pipeline to stop so that we can try this again
		   later.... */
		hdw->state_pipeline_छोड़ो = !0;
		वापस 0;
	पूर्ण

	अगर (hdw->srate_dirty) अणु
		/* Write new sample rate पूर्णांकo control काष्ठाure since
		 * the master copy is stale.  We must track srate
		 * separate from the mpeg control काष्ठाure because
		 * other logic also uses this value. */
		काष्ठा v4l2_ext_controls cs;
		काष्ठा v4l2_ext_control c1;
		स_रखो(&cs,0,माप(cs));
		स_रखो(&c1,0,माप(c1));
		cs.controls = &c1;
		cs.count = 1;
		c1.id = V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ;
		c1.value = hdw->srate_val;
		cx2341x_ext_ctrls(&hdw->enc_ctl_state, 0, &cs,VIDIOC_S_EXT_CTRLS);
	पूर्ण

	अगर (hdw->active_stream_type != hdw->desired_stream_type) अणु
		/* Handle any side effects of stream config here */
		hdw->active_stream_type = hdw->desired_stream_type;
	पूर्ण

	अगर (hdw->hdw_desc->संकेत_routing_scheme ==
	    PVR2_ROUTING_SCHEME_GOTVIEW) अणु
		u32 b;
		/* Handle GOTVIEW audio चयनing */
		pvr2_hdw_gpio_get_out(hdw,&b);
		अगर (hdw->input_val == PVR2_CVAL_INPUT_RADIO) अणु
			/* Set GPIO 11 */
			pvr2_hdw_gpio_chg_out(hdw,(1 << 11),~0);
		पूर्ण अन्यथा अणु
			/* Clear GPIO 11 */
			pvr2_hdw_gpio_chg_out(hdw,(1 << 11),0);
		पूर्ण
	पूर्ण

	/* Check and update state क्रम all sub-devices. */
	pvr2_subdev_update(hdw);

	hdw->tuner_updated = 0;
	hdw->क्रमce_dirty = 0;
	क्रम (idx = 0; idx < hdw->control_cnt; idx++) अणु
		cptr = hdw->controls + idx;
		अगर (!cptr->info->clear_dirty) जारी;
		cptr->info->clear_dirty(cptr);
	पूर्ण

	अगर ((hdw->pathway_state == PVR2_PATHWAY_ANALOG) &&
	    hdw->state_encoder_run) अणु
		/* If encoder isn't running or it can't be touched, then
		   this will get worked out later when we start the
		   encoder. */
		अगर (pvr2_encoder_adjust(hdw) < 0) वापस !0;
	पूर्ण

	hdw->state_pipeline_config = !0;
	/* Hardware state may have changed in a way to cause the cropping
	   capabilities to have changed.  So mark it stale, which will
	   cause a later re-fetch. */
	trace_stbit("state_pipeline_config",hdw->state_pipeline_config);
	वापस !0;
पूर्ण


पूर्णांक pvr2_hdw_commit_ctl(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक fl;
	LOCK_TAKE(hdw->big_lock);
	fl = pvr2_hdw_commit_setup(hdw);
	LOCK_GIVE(hdw->big_lock);
	अगर (!fl) वापस 0;
	वापस pvr2_hdw_रुको(hdw,0);
पूर्ण


अटल व्योम pvr2_hdw_worker_poll(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक fl = 0;
	काष्ठा pvr2_hdw *hdw = container_of(work,काष्ठा pvr2_hdw,workpoll);
	LOCK_TAKE(hdw->big_lock); करो अणु
		fl = pvr2_hdw_state_eval(hdw);
	पूर्ण जबतक (0); LOCK_GIVE(hdw->big_lock);
	अगर (fl && hdw->state_func) अणु
		hdw->state_func(hdw->state_data);
	पूर्ण
पूर्ण


अटल पूर्णांक pvr2_hdw_रुको(काष्ठा pvr2_hdw *hdw,पूर्णांक state)
अणु
	वापस रुको_event_पूर्णांकerruptible(
		hdw->state_रुको_data,
		(hdw->state_stale == 0) &&
		(!state || (hdw->master_state != state)));
पूर्ण


/* Return name क्रम this driver instance */
स्थिर अक्षर *pvr2_hdw_get_driver_name(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->name;
पूर्ण


स्थिर अक्षर *pvr2_hdw_get_desc(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->hdw_desc->description;
पूर्ण


स्थिर अक्षर *pvr2_hdw_get_type(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->hdw_desc->लघुname;
पूर्ण


पूर्णांक pvr2_hdw_is_hsm(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक result;
	LOCK_TAKE(hdw->ctl_lock); करो अणु
		hdw->cmd_buffer[0] = FX2CMD_GET_USB_SPEED;
		result = pvr2_send_request(hdw,
					   hdw->cmd_buffer,1,
					   hdw->cmd_buffer,1);
		अगर (result < 0) अवरोध;
		result = (hdw->cmd_buffer[0] != 0);
	पूर्ण जबतक(0); LOCK_GIVE(hdw->ctl_lock);
	वापस result;
पूर्ण


/* Execute poll of tuner status */
व्योम pvr2_hdw_execute_tuner_poll(काष्ठा pvr2_hdw *hdw)
अणु
	LOCK_TAKE(hdw->big_lock); करो अणु
		pvr2_hdw_status_poll(hdw);
	पूर्ण जबतक (0); LOCK_GIVE(hdw->big_lock);
पूर्ण


अटल पूर्णांक pvr2_hdw_check_cropcap(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (!hdw->cropcap_stale) अणु
		वापस 0;
	पूर्ण
	pvr2_hdw_status_poll(hdw);
	अगर (hdw->cropcap_stale) अणु
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण


/* Return inक्रमmation about cropping capabilities */
पूर्णांक pvr2_hdw_get_cropcap(काष्ठा pvr2_hdw *hdw, काष्ठा v4l2_cropcap *pp)
अणु
	पूर्णांक stat = 0;
	LOCK_TAKE(hdw->big_lock);
	stat = pvr2_hdw_check_cropcap(hdw);
	अगर (!stat) अणु
		स_नकल(pp, &hdw->cropcap_info, माप(hdw->cropcap_info));
	पूर्ण
	LOCK_GIVE(hdw->big_lock);
	वापस stat;
पूर्ण


/* Return inक्रमmation about the tuner */
पूर्णांक pvr2_hdw_get_tuner_status(काष्ठा pvr2_hdw *hdw,काष्ठा v4l2_tuner *vtp)
अणु
	LOCK_TAKE(hdw->big_lock); करो अणु
		अगर (hdw->tuner_संकेत_stale) अणु
			pvr2_hdw_status_poll(hdw);
		पूर्ण
		स_नकल(vtp,&hdw->tuner_संकेत_info,माप(काष्ठा v4l2_tuner));
	पूर्ण जबतक (0); LOCK_GIVE(hdw->big_lock);
	वापस 0;
पूर्ण


/* Get handle to video output stream */
काष्ठा pvr2_stream *pvr2_hdw_get_video_stream(काष्ठा pvr2_hdw *hp)
अणु
	वापस hp->vid_stream;
पूर्ण


व्योम pvr2_hdw_trigger_module_log(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक nr = pvr2_hdw_get_unit_number(hdw);
	LOCK_TAKE(hdw->big_lock);
	करो अणु
		pr_info("pvrusb2: =================  START STATUS CARD #%d  =================\n", nr);
		v4l2_device_call_all(&hdw->v4l2_dev, 0, core, log_status);
		pvr2_trace(PVR2_TRACE_INFO,"cx2341x config:");
		cx2341x_log_status(&hdw->enc_ctl_state, "pvrusb2");
		pvr2_hdw_state_log_state(hdw);
		pr_info("pvrusb2: ==================  END STATUS CARD #%d  ==================\n", nr);
	पूर्ण जबतक (0);
	LOCK_GIVE(hdw->big_lock);
पूर्ण


/* Grab EEPROM contents, needed क्रम direct method. */
#घोषणा EEPROM_SIZE 8192
#घोषणा trace_eeprom(...) pvr2_trace(PVR2_TRACE_EEPROM,__VA_ARGS__)
अटल u8 *pvr2_full_eeprom_fetch(काष्ठा pvr2_hdw *hdw)
अणु
	काष्ठा i2c_msg msg[2];
	u8 *eeprom;
	u8 iadd[2];
	u8 addr;
	u16 eepromSize;
	अचिन्हित पूर्णांक offs;
	पूर्णांक ret;
	पूर्णांक mode16 = 0;
	अचिन्हित pcnt,tcnt;
	eeprom = kzalloc(EEPROM_SIZE, GFP_KERNEL);
	अगर (!eeprom) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Failed to allocate memory required to read eeprom");
		वापस शून्य;
	पूर्ण

	trace_eeprom("Value for eeprom addr from controller was 0x%x",
		     hdw->eeprom_addr);
	addr = hdw->eeprom_addr;
	/* Seems that अगर the high bit is set, then the *real* eeprom
	   address is shअगरted right now bit position (noticed this in
	   newer PVR USB2 hardware) */
	अगर (addr & 0x80) addr >>= 1;

	/* FX2 करोcumentation states that a 16bit-addressed eeprom is
	   expected अगर the I2C address is an odd number (yeah, this is
	   strange but it's what they करो) */
	mode16 = (addr & 1);
	eepromSize = (mode16 ? EEPROM_SIZE : 256);
	trace_eeprom("Examining %d byte eeprom at location 0x%x using %d bit addressing",
		     eepromSize, addr,
		     mode16 ? 16 : 8);

	msg[0].addr = addr;
	msg[0].flags = 0;
	msg[0].len = mode16 ? 2 : 1;
	msg[0].buf = iadd;
	msg[1].addr = addr;
	msg[1].flags = I2C_M_RD;

	/* We have to करो the actual eeprom data fetch ourselves, because
	   (1) we're only fetching part of the eeprom, and (2) अगर we were
	   getting the whole thing our I2C driver can't grab it in one
	   pass - which is what tveeprom is otherwise going to attempt */
	क्रम (tcnt = 0; tcnt < EEPROM_SIZE; tcnt += pcnt) अणु
		pcnt = 16;
		अगर (pcnt + tcnt > EEPROM_SIZE) pcnt = EEPROM_SIZE-tcnt;
		offs = tcnt + (eepromSize - EEPROM_SIZE);
		अगर (mode16) अणु
			iadd[0] = offs >> 8;
			iadd[1] = offs;
		पूर्ण अन्यथा अणु
			iadd[0] = offs;
		पूर्ण
		msg[1].len = pcnt;
		msg[1].buf = eeprom+tcnt;
		अगर ((ret = i2c_transfer(&hdw->i2c_adap,
					msg,ARRAY_SIZE(msg))) != 2) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "eeprom fetch set offs err=%d",ret);
			kमुक्त(eeprom);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस eeprom;
पूर्ण


व्योम pvr2_hdw_cpufw_set_enabled(काष्ठा pvr2_hdw *hdw,
				पूर्णांक mode,
				पूर्णांक enable_flag)
अणु
	पूर्णांक ret;
	u16 address;
	अचिन्हित पूर्णांक pipe;
	LOCK_TAKE(hdw->big_lock); करो अणु
		अगर ((hdw->fw_buffer == शून्य) == !enable_flag) अवरोध;

		अगर (!enable_flag) अणु
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Cleaning up after CPU firmware fetch");
			kमुक्त(hdw->fw_buffer);
			hdw->fw_buffer = शून्य;
			hdw->fw_size = 0;
			अगर (hdw->fw_cpu_flag) अणु
				/* Now release the CPU.  It will disconnect
				   and reconnect later. */
				pvr2_hdw_cpureset_निश्चित(hdw,0);
			पूर्ण
			अवरोध;
		पूर्ण

		hdw->fw_cpu_flag = (mode != 2);
		अगर (hdw->fw_cpu_flag) अणु
			hdw->fw_size = (mode == 1) ? 0x4000 : 0x2000;
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Preparing to suck out CPU firmware (size=%u)",
				   hdw->fw_size);
			hdw->fw_buffer = kzalloc(hdw->fw_size,GFP_KERNEL);
			अगर (!hdw->fw_buffer) अणु
				hdw->fw_size = 0;
				अवरोध;
			पूर्ण

			/* We have to hold the CPU during firmware upload. */
			pvr2_hdw_cpureset_निश्चित(hdw,1);

			/* करोwnload the firmware from address 0000-1fff in 2048
			   (=0x800) bytes chunk. */

			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Grabbing CPU firmware");
			pipe = usb_rcvctrlpipe(hdw->usb_dev, 0);
			क्रम(address = 0; address < hdw->fw_size;
			    address += 0x800) अणु
				ret = usb_control_msg(hdw->usb_dev,pipe,
						      0xa0,0xc0,
						      address,0,
						      hdw->fw_buffer+address,
						      0x800,HZ);
				अगर (ret < 0) अवरोध;
			पूर्ण

			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Done grabbing CPU firmware");
		पूर्ण अन्यथा अणु
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Sucking down EEPROM contents");
			hdw->fw_buffer = pvr2_full_eeprom_fetch(hdw);
			अगर (!hdw->fw_buffer) अणु
				pvr2_trace(PVR2_TRACE_FIRMWARE,
					   "EEPROM content suck failed.");
				अवरोध;
			पूर्ण
			hdw->fw_size = EEPROM_SIZE;
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Done sucking down EEPROM contents");
		पूर्ण

	पूर्ण जबतक (0); LOCK_GIVE(hdw->big_lock);
पूर्ण


/* Return true अगर we're in a mode क्रम retrieval CPU firmware */
पूर्णांक pvr2_hdw_cpufw_get_enabled(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->fw_buffer != शून्य;
पूर्ण


पूर्णांक pvr2_hdw_cpufw_get(काष्ठा pvr2_hdw *hdw,अचिन्हित पूर्णांक offs,
		       अक्षर *buf,अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक ret = -EINVAL;
	LOCK_TAKE(hdw->big_lock); करो अणु
		अगर (!buf) अवरोध;
		अगर (!cnt) अवरोध;

		अगर (!hdw->fw_buffer) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण

		अगर (offs >= hdw->fw_size) अणु
			pvr2_trace(PVR2_TRACE_FIRMWARE,
				   "Read firmware data offs=%d EOF",
				   offs);
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (offs + cnt > hdw->fw_size) cnt = hdw->fw_size - offs;

		स_नकल(buf,hdw->fw_buffer+offs,cnt);

		pvr2_trace(PVR2_TRACE_FIRMWARE,
			   "Read firmware data offs=%d cnt=%d",
			   offs,cnt);
		ret = cnt;
	पूर्ण जबतक (0); LOCK_GIVE(hdw->big_lock);

	वापस ret;
पूर्ण


पूर्णांक pvr2_hdw_v4l_get_minor_number(काष्ठा pvr2_hdw *hdw,
				  क्रमागत pvr2_v4l_type index)
अणु
	चयन (index) अणु
	हाल pvr2_v4l_type_video: वापस hdw->v4l_minor_number_video;
	हाल pvr2_v4l_type_vbi: वापस hdw->v4l_minor_number_vbi;
	हाल pvr2_v4l_type_radio: वापस hdw->v4l_minor_number_radio;
	शेष: वापस -1;
	पूर्ण
पूर्ण


/* Store a v4l minor device number */
व्योम pvr2_hdw_v4l_store_minor_number(काष्ठा pvr2_hdw *hdw,
				     क्रमागत pvr2_v4l_type index,पूर्णांक v)
अणु
	चयन (index) अणु
	हाल pvr2_v4l_type_video: hdw->v4l_minor_number_video = v;अवरोध;
	हाल pvr2_v4l_type_vbi: hdw->v4l_minor_number_vbi = v;अवरोध;
	हाल pvr2_v4l_type_radio: hdw->v4l_minor_number_radio = v;अवरोध;
	शेष: अवरोध;
	पूर्ण
पूर्ण


अटल व्योम pvr2_ctl_ग_लिखो_complete(काष्ठा urb *urb)
अणु
	काष्ठा pvr2_hdw *hdw = urb->context;
	hdw->ctl_ग_लिखो_pend_flag = 0;
	अगर (hdw->ctl_पढ़ो_pend_flag) वापस;
	complete(&hdw->ctl_करोne);
पूर्ण


अटल व्योम pvr2_ctl_पढ़ो_complete(काष्ठा urb *urb)
अणु
	काष्ठा pvr2_hdw *hdw = urb->context;
	hdw->ctl_पढ़ो_pend_flag = 0;
	अगर (hdw->ctl_ग_लिखो_pend_flag) वापस;
	complete(&hdw->ctl_करोne);
पूर्ण

काष्ठा hdw_समयr अणु
	काष्ठा समयr_list समयr;
	काष्ठा pvr2_hdw *hdw;
पूर्ण;

अटल व्योम pvr2_ctl_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा hdw_समयr *समयr = from_समयr(समयr, t, समयr);
	काष्ठा pvr2_hdw *hdw = समयr->hdw;

	अगर (hdw->ctl_ग_लिखो_pend_flag || hdw->ctl_पढ़ो_pend_flag) अणु
		hdw->ctl_समयout_flag = !0;
		अगर (hdw->ctl_ग_लिखो_pend_flag)
			usb_unlink_urb(hdw->ctl_ग_लिखो_urb);
		अगर (hdw->ctl_पढ़ो_pend_flag)
			usb_unlink_urb(hdw->ctl_पढ़ो_urb);
	पूर्ण
पूर्ण


/* Issue a command and get a response from the device.  This extended
   version includes a probe flag (which अगर set means that device errors
   should not be logged or treated as fatal) and a समयout in jअगरfies.
   This can be used to non-lethally probe the health of endpoपूर्णांक 1. */
अटल पूर्णांक pvr2_send_request_ex(काष्ठा pvr2_hdw *hdw,
				अचिन्हित पूर्णांक समयout,पूर्णांक probe_fl,
				व्योम *ग_लिखो_data,अचिन्हित पूर्णांक ग_लिखो_len,
				व्योम *पढ़ो_data,अचिन्हित पूर्णांक पढ़ो_len)
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक status = 0;
	काष्ठा hdw_समयr समयr = अणु
		.hdw = hdw,
	पूर्ण;

	अगर (!hdw->ctl_lock_held) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Attempted to execute control transfer without lock!!");
		वापस -EDEADLK;
	पूर्ण
	अगर (!hdw->flag_ok && !probe_fl) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Attempted to execute control transfer when device not ok");
		वापस -EIO;
	पूर्ण
	अगर (!(hdw->ctl_पढ़ो_urb && hdw->ctl_ग_लिखो_urb)) अणु
		अगर (!probe_fl) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "Attempted to execute control transfer when USB is disconnected");
		पूर्ण
		वापस -ENOTTY;
	पूर्ण

	/* Ensure that we have sane parameters */
	अगर (!ग_लिखो_data) ग_लिखो_len = 0;
	अगर (!पढ़ो_data) पढ़ो_len = 0;
	अगर (ग_लिखो_len > PVR2_CTL_BUFFSIZE) अणु
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"Attempted to execute %d byte control-write transfer (limit=%d)",
			ग_लिखो_len,PVR2_CTL_BUFFSIZE);
		वापस -EINVAL;
	पूर्ण
	अगर (पढ़ो_len > PVR2_CTL_BUFFSIZE) अणु
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"Attempted to execute %d byte control-read transfer (limit=%d)",
			ग_लिखो_len,PVR2_CTL_BUFFSIZE);
		वापस -EINVAL;
	पूर्ण
	अगर ((!ग_लिखो_len) && (!पढ़ो_len)) अणु
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"Attempted to execute null control transfer?");
		वापस -EINVAL;
	पूर्ण


	hdw->cmd_debug_state = 1;
	अगर (ग_लिखो_len && ग_लिखो_data)
		hdw->cmd_debug_code = ((अचिन्हित अक्षर *)ग_लिखो_data)[0];
	अन्यथा
		hdw->cmd_debug_code = 0;
	hdw->cmd_debug_ग_लिखो_len = ग_लिखो_len;
	hdw->cmd_debug_पढ़ो_len = पढ़ो_len;

	/* Initialize common stuff */
	init_completion(&hdw->ctl_करोne);
	hdw->ctl_समयout_flag = 0;
	hdw->ctl_ग_लिखो_pend_flag = 0;
	hdw->ctl_पढ़ो_pend_flag = 0;
	समयr_setup_on_stack(&समयr.समयr, pvr2_ctl_समयout, 0);
	समयr.समयr.expires = jअगरfies + समयout;

	अगर (ग_लिखो_len && ग_लिखो_data) अणु
		hdw->cmd_debug_state = 2;
		/* Transfer ग_लिखो data to पूर्णांकernal buffer */
		क्रम (idx = 0; idx < ग_लिखो_len; idx++) अणु
			hdw->ctl_ग_लिखो_buffer[idx] =
				((अचिन्हित अक्षर *)ग_लिखो_data)[idx];
		पूर्ण
		/* Initiate a ग_लिखो request */
		usb_fill_bulk_urb(hdw->ctl_ग_लिखो_urb,
				  hdw->usb_dev,
				  usb_sndbulkpipe(hdw->usb_dev,
						  PVR2_CTL_WRITE_ENDPOINT),
				  hdw->ctl_ग_लिखो_buffer,
				  ग_लिखो_len,
				  pvr2_ctl_ग_लिखो_complete,
				  hdw);
		hdw->ctl_ग_लिखो_urb->actual_length = 0;
		hdw->ctl_ग_लिखो_pend_flag = !0;
		अगर (usb_urb_ep_type_check(hdw->ctl_ग_लिखो_urb)) अणु
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Invalid write control endpoint");
			वापस -EINVAL;
		पूर्ण
		status = usb_submit_urb(hdw->ctl_ग_लिखो_urb,GFP_KERNEL);
		अगर (status < 0) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "Failed to submit write-control URB status=%d",
status);
			hdw->ctl_ग_लिखो_pend_flag = 0;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (पढ़ो_len) अणु
		hdw->cmd_debug_state = 3;
		स_रखो(hdw->ctl_पढ़ो_buffer,0x43,पढ़ो_len);
		/* Initiate a पढ़ो request */
		usb_fill_bulk_urb(hdw->ctl_पढ़ो_urb,
				  hdw->usb_dev,
				  usb_rcvbulkpipe(hdw->usb_dev,
						  PVR2_CTL_READ_ENDPOINT),
				  hdw->ctl_पढ़ो_buffer,
				  पढ़ो_len,
				  pvr2_ctl_पढ़ो_complete,
				  hdw);
		hdw->ctl_पढ़ो_urb->actual_length = 0;
		hdw->ctl_पढ़ो_pend_flag = !0;
		अगर (usb_urb_ep_type_check(hdw->ctl_पढ़ो_urb)) अणु
			pvr2_trace(
				PVR2_TRACE_ERROR_LEGS,
				"Invalid read control endpoint");
			वापस -EINVAL;
		पूर्ण
		status = usb_submit_urb(hdw->ctl_पढ़ो_urb,GFP_KERNEL);
		अगर (status < 0) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "Failed to submit read-control URB status=%d",
status);
			hdw->ctl_पढ़ो_pend_flag = 0;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* Start समयr */
	add_समयr(&समयr.समयr);

	/* Now रुको क्रम all I/O to complete */
	hdw->cmd_debug_state = 4;
	जबतक (hdw->ctl_ग_लिखो_pend_flag || hdw->ctl_पढ़ो_pend_flag) अणु
		रुको_क्रम_completion(&hdw->ctl_करोne);
	पूर्ण
	hdw->cmd_debug_state = 5;

	/* Stop समयr */
	del_समयr_sync(&समयr.समयr);

	hdw->cmd_debug_state = 6;
	status = 0;

	अगर (hdw->ctl_समयout_flag) अणु
		status = -ETIMEDOUT;
		अगर (!probe_fl) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "Timed out control-write");
		पूर्ण
		जाओ करोne;
	पूर्ण

	अगर (ग_लिखो_len) अणु
		/* Validate results of ग_लिखो request */
		अगर ((hdw->ctl_ग_लिखो_urb->status != 0) &&
		    (hdw->ctl_ग_लिखो_urb->status != -ENOENT) &&
		    (hdw->ctl_ग_लिखो_urb->status != -ESHUTDOWN) &&
		    (hdw->ctl_ग_लिखो_urb->status != -ECONNRESET)) अणु
			/* USB subप्रणाली is reporting some kind of failure
			   on the ग_लिखो */
			status = hdw->ctl_ग_लिखो_urb->status;
			अगर (!probe_fl) अणु
				pvr2_trace(PVR2_TRACE_ERROR_LEGS,
					   "control-write URB failure, status=%d",
					   status);
			पूर्ण
			जाओ करोne;
		पूर्ण
		अगर (hdw->ctl_ग_लिखो_urb->actual_length < ग_लिखो_len) अणु
			/* Failed to ग_लिखो enough data */
			status = -EIO;
			अगर (!probe_fl) अणु
				pvr2_trace(PVR2_TRACE_ERROR_LEGS,
					   "control-write URB short, expected=%d got=%d",
					   ग_लिखो_len,
					   hdw->ctl_ग_लिखो_urb->actual_length);
			पूर्ण
			जाओ करोne;
		पूर्ण
	पूर्ण
	अगर (पढ़ो_len && पढ़ो_data) अणु
		/* Validate results of पढ़ो request */
		अगर ((hdw->ctl_पढ़ो_urb->status != 0) &&
		    (hdw->ctl_पढ़ो_urb->status != -ENOENT) &&
		    (hdw->ctl_पढ़ो_urb->status != -ESHUTDOWN) &&
		    (hdw->ctl_पढ़ो_urb->status != -ECONNRESET)) अणु
			/* USB subप्रणाली is reporting some kind of failure
			   on the पढ़ो */
			status = hdw->ctl_पढ़ो_urb->status;
			अगर (!probe_fl) अणु
				pvr2_trace(PVR2_TRACE_ERROR_LEGS,
					   "control-read URB failure, status=%d",
					   status);
			पूर्ण
			जाओ करोne;
		पूर्ण
		अगर (hdw->ctl_पढ़ो_urb->actual_length < पढ़ो_len) अणु
			/* Failed to पढ़ो enough data */
			status = -EIO;
			अगर (!probe_fl) अणु
				pvr2_trace(PVR2_TRACE_ERROR_LEGS,
					   "control-read URB short, expected=%d got=%d",
					   पढ़ो_len,
					   hdw->ctl_पढ़ो_urb->actual_length);
			पूर्ण
			जाओ करोne;
		पूर्ण
		/* Transfer retrieved data out from पूर्णांकernal buffer */
		क्रम (idx = 0; idx < पढ़ो_len; idx++) अणु
			((अचिन्हित अक्षर *)पढ़ो_data)[idx] =
				hdw->ctl_पढ़ो_buffer[idx];
		पूर्ण
	पूर्ण

 करोne:

	hdw->cmd_debug_state = 0;
	अगर ((status < 0) && (!probe_fl)) अणु
		pvr2_hdw_render_useless(hdw);
	पूर्ण
	destroy_समयr_on_stack(&समयr.समयr);

	वापस status;
पूर्ण


पूर्णांक pvr2_send_request(काष्ठा pvr2_hdw *hdw,
		      व्योम *ग_लिखो_data,अचिन्हित पूर्णांक ग_लिखो_len,
		      व्योम *पढ़ो_data,अचिन्हित पूर्णांक पढ़ो_len)
अणु
	वापस pvr2_send_request_ex(hdw,HZ*4,0,
				    ग_लिखो_data,ग_लिखो_len,
				    पढ़ो_data,पढ़ो_len);
पूर्ण


अटल पूर्णांक pvr2_issue_simple_cmd(काष्ठा pvr2_hdw *hdw,u32 cmdcode)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक cnt = 1;
	अचिन्हित पूर्णांक args = 0;
	LOCK_TAKE(hdw->ctl_lock);
	hdw->cmd_buffer[0] = cmdcode & 0xffu;
	args = (cmdcode >> 8) & 0xffu;
	args = (args > 2) ? 2 : args;
	अगर (args) अणु
		cnt += args;
		hdw->cmd_buffer[1] = (cmdcode >> 16) & 0xffu;
		अगर (args > 1) अणु
			hdw->cmd_buffer[2] = (cmdcode >> 24) & 0xffu;
		पूर्ण
	पूर्ण
	अगर (pvrusb2_debug & PVR2_TRACE_INIT) अणु
		अचिन्हित पूर्णांक idx;
		अचिन्हित पूर्णांक ccnt,bcnt;
		अक्षर tbuf[50];
		cmdcode &= 0xffu;
		bcnt = 0;
		ccnt = scnम_लिखो(tbuf+bcnt,
				 माप(tbuf)-bcnt,
				 "Sending FX2 command 0x%x",cmdcode);
		bcnt += ccnt;
		क्रम (idx = 0; idx < ARRAY_SIZE(pvr2_fx2cmd_desc); idx++) अणु
			अगर (pvr2_fx2cmd_desc[idx].id == cmdcode) अणु
				ccnt = scnम_लिखो(tbuf+bcnt,
						 माप(tbuf)-bcnt,
						 " \"%s\"",
						 pvr2_fx2cmd_desc[idx].desc);
				bcnt += ccnt;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (args) अणु
			ccnt = scnम_लिखो(tbuf+bcnt,
					 माप(tbuf)-bcnt,
					 " (%u",hdw->cmd_buffer[1]);
			bcnt += ccnt;
			अगर (args > 1) अणु
				ccnt = scnम_लिखो(tbuf+bcnt,
						 माप(tbuf)-bcnt,
						 ",%u",hdw->cmd_buffer[2]);
				bcnt += ccnt;
			पूर्ण
			ccnt = scnम_लिखो(tbuf+bcnt,
					 माप(tbuf)-bcnt,
					 ")");
			bcnt += ccnt;
		पूर्ण
		pvr2_trace(PVR2_TRACE_INIT,"%.*s",bcnt,tbuf);
	पूर्ण
	ret = pvr2_send_request(hdw,hdw->cmd_buffer,cnt,शून्य,0);
	LOCK_GIVE(hdw->ctl_lock);
	वापस ret;
पूर्ण


पूर्णांक pvr2_ग_लिखो_रेजिस्टर(काष्ठा pvr2_hdw *hdw, u16 reg, u32 data)
अणु
	पूर्णांक ret;

	LOCK_TAKE(hdw->ctl_lock);

	hdw->cmd_buffer[0] = FX2CMD_REG_WRITE;  /* ग_लिखो रेजिस्टर prefix */
	PVR2_DECOMPOSE_LE(hdw->cmd_buffer,1,data);
	hdw->cmd_buffer[5] = 0;
	hdw->cmd_buffer[6] = (reg >> 8) & 0xff;
	hdw->cmd_buffer[7] = reg & 0xff;


	ret = pvr2_send_request(hdw, hdw->cmd_buffer, 8, hdw->cmd_buffer, 0);

	LOCK_GIVE(hdw->ctl_lock);

	वापस ret;
पूर्ण


अटल पूर्णांक pvr2_पढ़ो_रेजिस्टर(काष्ठा pvr2_hdw *hdw, u16 reg, u32 *data)
अणु
	पूर्णांक ret = 0;

	LOCK_TAKE(hdw->ctl_lock);

	hdw->cmd_buffer[0] = FX2CMD_REG_READ;  /* पढ़ो रेजिस्टर prefix */
	hdw->cmd_buffer[1] = 0;
	hdw->cmd_buffer[2] = 0;
	hdw->cmd_buffer[3] = 0;
	hdw->cmd_buffer[4] = 0;
	hdw->cmd_buffer[5] = 0;
	hdw->cmd_buffer[6] = (reg >> 8) & 0xff;
	hdw->cmd_buffer[7] = reg & 0xff;

	ret |= pvr2_send_request(hdw, hdw->cmd_buffer, 8, hdw->cmd_buffer, 4);
	*data = PVR2_COMPOSE_LE(hdw->cmd_buffer,0);

	LOCK_GIVE(hdw->ctl_lock);

	वापस ret;
पूर्ण


व्योम pvr2_hdw_render_useless(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (!hdw->flag_ok) वापस;
	pvr2_trace(PVR2_TRACE_ERROR_LEGS,
		   "Device being rendered inoperable");
	अगर (hdw->vid_stream) अणु
		pvr2_stream_setup(hdw->vid_stream,शून्य,0,0);
	पूर्ण
	hdw->flag_ok = 0;
	trace_stbit("flag_ok",hdw->flag_ok);
	pvr2_hdw_state_sched(hdw);
पूर्ण


व्योम pvr2_hdw_device_reset(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक ret;
	pvr2_trace(PVR2_TRACE_INIT,"Performing a device reset...");
	ret = usb_lock_device_क्रम_reset(hdw->usb_dev,शून्य);
	अगर (ret == 0) अणु
		ret = usb_reset_device(hdw->usb_dev);
		usb_unlock_device(hdw->usb_dev);
	पूर्ण अन्यथा अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Failed to lock USB device ret=%d",ret);
	पूर्ण
	अगर (init_छोड़ो_msec) अणु
		pvr2_trace(PVR2_TRACE_INFO,
			   "Waiting %u msec for hardware to settle",
			   init_छोड़ो_msec);
		msleep(init_छोड़ो_msec);
	पूर्ण

पूर्ण


व्योम pvr2_hdw_cpureset_निश्चित(काष्ठा pvr2_hdw *hdw,पूर्णांक val)
अणु
	अक्षर *da;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक ret;

	अगर (!hdw->usb_dev) वापस;

	da = kदो_स्मृति(16, GFP_KERNEL);

	अगर (da == शून्य) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Unable to allocate memory to control CPU reset");
		वापस;
	पूर्ण

	pvr2_trace(PVR2_TRACE_INIT,"cpureset_assert(%d)",val);

	da[0] = val ? 0x01 : 0x00;

	/* Write the CPUCS रेजिस्टर on the 8051.  The lsb of the रेजिस्टर
	   is the reset bit; a 1 निश्चितs reset जबतक a 0 clears it. */
	pipe = usb_sndctrlpipe(hdw->usb_dev, 0);
	ret = usb_control_msg(hdw->usb_dev,pipe,0xa0,0x40,0xe600,0,da,1,HZ);
	अगर (ret < 0) अणु
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "cpureset_assert(%d) error=%d",val,ret);
		pvr2_hdw_render_useless(hdw);
	पूर्ण

	kमुक्त(da);
पूर्ण


पूर्णांक pvr2_hdw_cmd_deep_reset(काष्ठा pvr2_hdw *hdw)
अणु
	वापस pvr2_issue_simple_cmd(hdw,FX2CMD_DEEP_RESET);
पूर्ण


पूर्णांक pvr2_hdw_cmd_घातerup(काष्ठा pvr2_hdw *hdw)
अणु
	वापस pvr2_issue_simple_cmd(hdw,FX2CMD_POWER_ON);
पूर्ण



पूर्णांक pvr2_hdw_cmd_decoder_reset(काष्ठा pvr2_hdw *hdw)
अणु
	pvr2_trace(PVR2_TRACE_INIT,
		   "Requesting decoder reset");
	अगर (hdw->decoder_client_id) अणु
		v4l2_device_call_all(&hdw->v4l2_dev, hdw->decoder_client_id,
				     core, reset, 0);
		pvr2_hdw_cx25840_vbi_hack(hdw);
		वापस 0;
	पूर्ण
	pvr2_trace(PVR2_TRACE_INIT,
		   "Unable to reset decoder: nothing attached");
	वापस -ENOTTY;
पूर्ण


अटल पूर्णांक pvr2_hdw_cmd_hcw_demod_reset(काष्ठा pvr2_hdw *hdw, पूर्णांक onoff)
अणु
	hdw->flag_ok = !0;

	/* Use this क्रम Hauppauge 160xxx only */
	अगर (le16_to_cpu(hdw->usb_dev->descriptor.idVenकरोr) == 0x2040 &&
	    (le16_to_cpu(hdw->usb_dev->descriptor.idProduct) == 0x7502 ||
	     le16_to_cpu(hdw->usb_dev->descriptor.idProduct) == 0x7510)) अणु
		pr_debug("%s(): resetting demod on Hauppauge 160xxx platform skipped\n",
			 __func__);
		/* Can't reset 160xxx or it will trash Demod tristate */
		वापस pvr2_issue_simple_cmd(hdw,
					     FX2CMD_HCW_MAKO_SLEEP_PIN |
					     (1 << 8) |
					     ((onoff ? 1 : 0) << 16));
	पूर्ण

	वापस pvr2_issue_simple_cmd(hdw,
				     FX2CMD_HCW_DEMOD_RESETIN |
				     (1 << 8) |
				     ((onoff ? 1 : 0) << 16));
पूर्ण


अटल पूर्णांक pvr2_hdw_cmd_onair_fe_घातer_ctrl(काष्ठा pvr2_hdw *hdw, पूर्णांक onoff)
अणु
	hdw->flag_ok = !0;
	वापस pvr2_issue_simple_cmd(hdw,(onoff ?
					  FX2CMD_ONAIR_DTV_POWER_ON :
					  FX2CMD_ONAIR_DTV_POWER_OFF));
पूर्ण


अटल पूर्णांक pvr2_hdw_cmd_onair_digital_path_ctrl(काष्ठा pvr2_hdw *hdw,
						पूर्णांक onoff)
अणु
	वापस pvr2_issue_simple_cmd(hdw,(onoff ?
					  FX2CMD_ONAIR_DTV_STREAMING_ON :
					  FX2CMD_ONAIR_DTV_STREAMING_OFF));
पूर्ण


अटल व्योम pvr2_hdw_cmd_modeचयन(काष्ठा pvr2_hdw *hdw,पूर्णांक digitalFl)
अणु
	पूर्णांक cmode;
	/* Compare digital/analog desired setting with current setting.  If
	   they करोn't match, fix it... */
	cmode = (digitalFl ? PVR2_PATHWAY_DIGITAL : PVR2_PATHWAY_ANALOG);
	अगर (cmode == hdw->pathway_state) अणु
		/* They match; nothing to करो */
		वापस;
	पूर्ण

	चयन (hdw->hdw_desc->digital_control_scheme) अणु
	हाल PVR2_DIGITAL_SCHEME_HAUPPAUGE:
		pvr2_hdw_cmd_hcw_demod_reset(hdw,digitalFl);
		अगर (cmode == PVR2_PATHWAY_ANALOG) अणु
			/* If moving to analog mode, also क्रमce the decoder
			   to reset.  If no decoder is attached, then it's
			   ok to ignore this because अगर/when the decoder
			   attaches, it will reset itself at that समय. */
			pvr2_hdw_cmd_decoder_reset(hdw);
		पूर्ण
		अवरोध;
	हाल PVR2_DIGITAL_SCHEME_ONAIR:
		/* Supposedly we should always have the घातer on whether in
		   digital or analog mode.  But क्रम now करो what appears to
		   work... */
		pvr2_hdw_cmd_onair_fe_घातer_ctrl(hdw,digitalFl);
		अवरोध;
	शेष: अवरोध;
	पूर्ण

	pvr2_hdw_untrip_unlocked(hdw);
	hdw->pathway_state = cmode;
पूर्ण


अटल व्योम pvr2_led_ctrl_hauppauge(काष्ठा pvr2_hdw *hdw, पूर्णांक onoff)
अणु
	/* change some GPIO data
	 *
	 * note: bit d7 of dir appears to control the LED,
	 * so we shut it off here.
	 *
	 */
	अगर (onoff) अणु
		pvr2_hdw_gpio_chg_dir(hdw, 0xffffffff, 0x00000481);
	पूर्ण अन्यथा अणु
		pvr2_hdw_gpio_chg_dir(hdw, 0xffffffff, 0x00000401);
	पूर्ण
	pvr2_hdw_gpio_chg_out(hdw, 0xffffffff, 0x00000000);
पूर्ण


प्रकार व्योम (*led_method_func)(काष्ठा pvr2_hdw *,पूर्णांक);

अटल led_method_func led_methods[] = अणु
	[PVR2_LED_SCHEME_HAUPPAUGE] = pvr2_led_ctrl_hauppauge,
पूर्ण;


/* Toggle LED */
अटल व्योम pvr2_led_ctrl(काष्ठा pvr2_hdw *hdw,पूर्णांक onoff)
अणु
	अचिन्हित पूर्णांक scheme_id;
	led_method_func fp;

	अगर ((!onoff) == (!hdw->led_on)) वापस;

	hdw->led_on = onoff != 0;

	scheme_id = hdw->hdw_desc->led_scheme;
	अगर (scheme_id < ARRAY_SIZE(led_methods)) अणु
		fp = led_methods[scheme_id];
	पूर्ण अन्यथा अणु
		fp = शून्य;
	पूर्ण

	अगर (fp) (*fp)(hdw,onoff);
पूर्ण


/* Stop / start video stream transport */
अटल पूर्णांक pvr2_hdw_cmd_usbstream(काष्ठा pvr2_hdw *hdw,पूर्णांक runFl)
अणु
	पूर्णांक ret;

	/* If we're in analog mode, then just issue the usual analog
	   command. */
	अगर (hdw->pathway_state == PVR2_PATHWAY_ANALOG) अणु
		वापस pvr2_issue_simple_cmd(hdw,
					     (runFl ?
					      FX2CMD_STREAMING_ON :
					      FX2CMD_STREAMING_OFF));
		/*Note: Not reached */
	पूर्ण

	अगर (hdw->pathway_state != PVR2_PATHWAY_DIGITAL) अणु
		/* Whoops, we करोn't know what mode we're in... */
		वापस -EINVAL;
	पूर्ण

	/* To get here we have to be in digital mode.  The mechanism here
	   is unक्रमtunately dअगरferent क्रम dअगरferent venकरोrs.  So we चयन
	   on the device's digital scheme attribute in order to figure out
	   what to करो. */
	चयन (hdw->hdw_desc->digital_control_scheme) अणु
	हाल PVR2_DIGITAL_SCHEME_HAUPPAUGE:
		वापस pvr2_issue_simple_cmd(hdw,
					     (runFl ?
					      FX2CMD_HCW_DTV_STREAMING_ON :
					      FX2CMD_HCW_DTV_STREAMING_OFF));
	हाल PVR2_DIGITAL_SCHEME_ONAIR:
		ret = pvr2_issue_simple_cmd(hdw,
					    (runFl ?
					     FX2CMD_STREAMING_ON :
					     FX2CMD_STREAMING_OFF));
		अगर (ret) वापस ret;
		वापस pvr2_hdw_cmd_onair_digital_path_ctrl(hdw,runFl);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण


/* Evaluate whether or not state_pathway_ok can change */
अटल पूर्णांक state_eval_pathway_ok(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->state_pathway_ok) अणु
		/* Nothing to करो अगर pathway is alपढ़ोy ok */
		वापस 0;
	पूर्ण
	अगर (!hdw->state_pipeline_idle) अणु
		/* Not allowed to change anything अगर pipeline is not idle */
		वापस 0;
	पूर्ण
	pvr2_hdw_cmd_modeचयन(hdw,hdw->input_val == PVR2_CVAL_INPUT_DTV);
	hdw->state_pathway_ok = !0;
	trace_stbit("state_pathway_ok",hdw->state_pathway_ok);
	वापस !0;
पूर्ण


/* Evaluate whether or not state_encoder_ok can change */
अटल पूर्णांक state_eval_encoder_ok(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->state_encoder_ok) वापस 0;
	अगर (hdw->flag_tripped) वापस 0;
	अगर (hdw->state_encoder_run) वापस 0;
	अगर (hdw->state_encoder_config) वापस 0;
	अगर (hdw->state_decoder_run) वापस 0;
	अगर (hdw->state_usbstream_run) वापस 0;
	अगर (hdw->pathway_state == PVR2_PATHWAY_DIGITAL) अणु
		अगर (!hdw->hdw_desc->flag_digital_requires_cx23416) वापस 0;
	पूर्ण अन्यथा अगर (hdw->pathway_state != PVR2_PATHWAY_ANALOG) अणु
		वापस 0;
	पूर्ण

	अगर (pvr2_upload_firmware2(hdw) < 0) अणु
		hdw->flag_tripped = !0;
		trace_stbit("flag_tripped",hdw->flag_tripped);
		वापस !0;
	पूर्ण
	hdw->state_encoder_ok = !0;
	trace_stbit("state_encoder_ok",hdw->state_encoder_ok);
	वापस !0;
पूर्ण


/* Evaluate whether or not state_encoder_config can change */
अटल पूर्णांक state_eval_encoder_config(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->state_encoder_config) अणु
		अगर (hdw->state_encoder_ok) अणु
			अगर (hdw->state_pipeline_req &&
			    !hdw->state_pipeline_छोड़ो) वापस 0;
		पूर्ण
		hdw->state_encoder_config = 0;
		hdw->state_encoder_रुकोok = 0;
		trace_stbit("state_encoder_waitok",hdw->state_encoder_रुकोok);
		/* paranoia - solve race अगर समयr just completed */
		del_समयr_sync(&hdw->encoder_रुको_समयr);
	पूर्ण अन्यथा अणु
		अगर (!hdw->state_pathway_ok ||
		    (hdw->pathway_state != PVR2_PATHWAY_ANALOG) ||
		    !hdw->state_encoder_ok ||
		    !hdw->state_pipeline_idle ||
		    hdw->state_pipeline_छोड़ो ||
		    !hdw->state_pipeline_req ||
		    !hdw->state_pipeline_config) अणु
			/* We must reset the enक्रमced रुको पूर्णांकerval अगर
			   anything has happened that might have disturbed
			   the encoder.  This should be a rare हाल. */
			अगर (समयr_pending(&hdw->encoder_रुको_समयr)) अणु
				del_समयr_sync(&hdw->encoder_रुको_समयr);
			पूर्ण
			अगर (hdw->state_encoder_रुकोok) अणु
				/* Must clear the state - thereक्रमe we did
				   something to a state bit and must also
				   वापस true. */
				hdw->state_encoder_रुकोok = 0;
				trace_stbit("state_encoder_waitok",
					    hdw->state_encoder_रुकोok);
				वापस !0;
			पूर्ण
			वापस 0;
		पूर्ण
		अगर (!hdw->state_encoder_रुकोok) अणु
			अगर (!समयr_pending(&hdw->encoder_रुको_समयr)) अणु
				/* रुकोok flag wasn't set and timer isn't
				   running.  Check flag once more to aव्योम
				   a race then start the समयr.  This is
				   the poपूर्णांक when we measure out a minimal
				   quiet पूर्णांकerval beक्रमe करोing something to
				   the encoder. */
				अगर (!hdw->state_encoder_रुकोok) अणु
					hdw->encoder_रुको_समयr.expires =
						jअगरfies + msecs_to_jअगरfies(
						TIME_MSEC_ENCODER_WAIT);
					add_समयr(&hdw->encoder_रुको_समयr);
				पूर्ण
			पूर्ण
			/* We can't जारी until we know we have been
			   quiet क्रम the पूर्णांकerval measured by this
			   समयr. */
			वापस 0;
		पूर्ण
		pvr2_encoder_configure(hdw);
		अगर (hdw->state_encoder_ok) hdw->state_encoder_config = !0;
	पूर्ण
	trace_stbit("state_encoder_config",hdw->state_encoder_config);
	वापस !0;
पूर्ण


/* Return true अगर the encoder should not be running. */
अटल पूर्णांक state_check_disable_encoder_run(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (!hdw->state_encoder_ok) अणु
		/* Encoder isn't healthy at the moment, so stop it. */
		वापस !0;
	पूर्ण
	अगर (!hdw->state_pathway_ok) अणु
		/* Mode is not understood at the moment (i.e. it wants to
		   change), so encoder must be stopped. */
		वापस !0;
	पूर्ण

	चयन (hdw->pathway_state) अणु
	हाल PVR2_PATHWAY_ANALOG:
		अगर (!hdw->state_decoder_run) अणु
			/* We're in analog mode and the decoder is not
			   running; thus the encoder should be stopped as
			   well. */
			वापस !0;
		पूर्ण
		अवरोध;
	हाल PVR2_PATHWAY_DIGITAL:
		अगर (hdw->state_encoder_runok) अणु
			/* This is a funny हाल.  We're in digital mode so
			   really the encoder should be stopped.  However
			   अगर it really is running, only समाप्त it after
			   runok has been set.  This gives a chance क्रम the
			   onair quirk to function (encoder must run
			   briefly first, at least once, beक्रमe onair
			   digital streaming can work). */
			वापस !0;
		पूर्ण
		अवरोध;
	शेष:
		/* Unknown mode; so encoder should be stopped. */
		वापस !0;
	पूर्ण

	/* If we get here, we haven't found a reason to stop the
	   encoder. */
	वापस 0;
पूर्ण


/* Return true अगर the encoder should be running. */
अटल पूर्णांक state_check_enable_encoder_run(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (!hdw->state_encoder_ok) अणु
		/* Don't run the encoder if it isn't healthy... */
		वापस 0;
	पूर्ण
	अगर (!hdw->state_pathway_ok) अणु
		/* Don't run the encoder if we don't (yet) know what mode
		   we need to be in... */
		वापस 0;
	पूर्ण

	चयन (hdw->pathway_state) अणु
	हाल PVR2_PATHWAY_ANALOG:
		अगर (hdw->state_decoder_run && hdw->state_decoder_पढ़ोy) अणु
			/* In analog mode, अगर the decoder is running, then
			   run the encoder. */
			वापस !0;
		पूर्ण
		अवरोध;
	हाल PVR2_PATHWAY_DIGITAL:
		अगर ((hdw->hdw_desc->digital_control_scheme ==
		     PVR2_DIGITAL_SCHEME_ONAIR) &&
		    !hdw->state_encoder_runok) अणु
			/* This is a quirk.  OnAir hardware won't stream
			   digital until the encoder has been run at least
			   once, क्रम a minimal period of समय (empiricially
			   measured to be 1/4 second).  So अगर we're on
			   OnAir hardware and the encoder has never been
			   run at all, then start the encoder.  Normal
			   state machine logic in the driver will
			   स्वतःmatically handle the reमुख्यing bits. */
			वापस !0;
		पूर्ण
		अवरोध;
	शेष:
		/* For completeness (unknown mode; encoder won't run ever) */
		अवरोध;
	पूर्ण
	/* If we get here, then we haven't found any reason to run the
	   encoder, so करोn't run it. */
	वापस 0;
पूर्ण


/* Evaluate whether or not state_encoder_run can change */
अटल पूर्णांक state_eval_encoder_run(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->state_encoder_run) अणु
		अगर (!state_check_disable_encoder_run(hdw)) वापस 0;
		अगर (hdw->state_encoder_ok) अणु
			del_समयr_sync(&hdw->encoder_run_समयr);
			अगर (pvr2_encoder_stop(hdw) < 0) वापस !0;
		पूर्ण
		hdw->state_encoder_run = 0;
	पूर्ण अन्यथा अणु
		अगर (!state_check_enable_encoder_run(hdw)) वापस 0;
		अगर (pvr2_encoder_start(hdw) < 0) वापस !0;
		hdw->state_encoder_run = !0;
		अगर (!hdw->state_encoder_runok) अणु
			hdw->encoder_run_समयr.expires = jअगरfies +
				 msecs_to_jअगरfies(TIME_MSEC_ENCODER_OK);
			add_समयr(&hdw->encoder_run_समयr);
		पूर्ण
	पूर्ण
	trace_stbit("state_encoder_run",hdw->state_encoder_run);
	वापस !0;
पूर्ण


/* Timeout function क्रम quiescent समयr. */
अटल व्योम pvr2_hdw_quiescent_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा pvr2_hdw *hdw = from_समयr(hdw, t, quiescent_समयr);
	hdw->state_decoder_quiescent = !0;
	trace_stbit("state_decoder_quiescent",hdw->state_decoder_quiescent);
	hdw->state_stale = !0;
	schedule_work(&hdw->workpoll);
पूर्ण


/* Timeout function क्रम decoder stabilization समयr. */
अटल व्योम pvr2_hdw_decoder_stabilization_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा pvr2_hdw *hdw = from_समयr(hdw, t, decoder_stabilization_समयr);
	hdw->state_decoder_पढ़ोy = !0;
	trace_stbit("state_decoder_ready", hdw->state_decoder_पढ़ोy);
	hdw->state_stale = !0;
	schedule_work(&hdw->workpoll);
पूर्ण


/* Timeout function क्रम encoder रुको समयr. */
अटल व्योम pvr2_hdw_encoder_रुको_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा pvr2_hdw *hdw = from_समयr(hdw, t, encoder_रुको_समयr);
	hdw->state_encoder_रुकोok = !0;
	trace_stbit("state_encoder_waitok",hdw->state_encoder_रुकोok);
	hdw->state_stale = !0;
	schedule_work(&hdw->workpoll);
पूर्ण


/* Timeout function क्रम encoder run समयr. */
अटल व्योम pvr2_hdw_encoder_run_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा pvr2_hdw *hdw = from_समयr(hdw, t, encoder_run_समयr);
	अगर (!hdw->state_encoder_runok) अणु
		hdw->state_encoder_runok = !0;
		trace_stbit("state_encoder_runok",hdw->state_encoder_runok);
		hdw->state_stale = !0;
		schedule_work(&hdw->workpoll);
	पूर्ण
पूर्ण


/* Evaluate whether or not state_decoder_run can change */
अटल पूर्णांक state_eval_decoder_run(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->state_decoder_run) अणु
		अगर (hdw->state_encoder_ok) अणु
			अगर (hdw->state_pipeline_req &&
			    !hdw->state_pipeline_छोड़ो &&
			    hdw->state_pathway_ok) वापस 0;
		पूर्ण
		अगर (!hdw->flag_decoder_missed) अणु
			pvr2_decoder_enable(hdw,0);
		पूर्ण
		hdw->state_decoder_quiescent = 0;
		hdw->state_decoder_run = 0;
		/* paranoia - solve race अगर समयr(s) just completed */
		del_समयr_sync(&hdw->quiescent_समयr);
		/* Kill the stabilization समयr, in हाल we're समाप्तing the
		   encoder beक्रमe the previous stabilization पूर्णांकerval has
		   been properly समयd. */
		del_समयr_sync(&hdw->decoder_stabilization_समयr);
		hdw->state_decoder_पढ़ोy = 0;
	पूर्ण अन्यथा अणु
		अगर (!hdw->state_decoder_quiescent) अणु
			अगर (!समयr_pending(&hdw->quiescent_समयr)) अणु
				/* We करोn't करो something about the
				   quiescent समयr until right here because
				   we also want to catch हालs where the
				   decoder was alपढ़ोy not running (like
				   after initialization) as opposed to
				   knowing that we had just stopped it.
				   The second flag check is here to cover a
				   race - the समयr could have run and set
				   this flag just after the previous check
				   but beक्रमe we did the pending check. */
				अगर (!hdw->state_decoder_quiescent) अणु
					hdw->quiescent_समयr.expires =
						jअगरfies + msecs_to_jअगरfies(
						TIME_MSEC_DECODER_WAIT);
					add_समयr(&hdw->quiescent_समयr);
				पूर्ण
			पूर्ण
			/* Don't allow decoder to start again until it has
			   been quiesced first.  This little detail should
			   hopefully further stabilize the encoder. */
			वापस 0;
		पूर्ण
		अगर (!hdw->state_pathway_ok ||
		    (hdw->pathway_state != PVR2_PATHWAY_ANALOG) ||
		    !hdw->state_pipeline_req ||
		    hdw->state_pipeline_छोड़ो ||
		    !hdw->state_pipeline_config ||
		    !hdw->state_encoder_config ||
		    !hdw->state_encoder_ok) वापस 0;
		del_समयr_sync(&hdw->quiescent_समयr);
		अगर (hdw->flag_decoder_missed) वापस 0;
		अगर (pvr2_decoder_enable(hdw,!0) < 0) वापस 0;
		hdw->state_decoder_quiescent = 0;
		hdw->state_decoder_पढ़ोy = 0;
		hdw->state_decoder_run = !0;
		अगर (hdw->decoder_client_id == PVR2_CLIENT_ID_SAA7115) अणु
			hdw->decoder_stabilization_समयr.expires =
				jअगरfies + msecs_to_jअगरfies(
				TIME_MSEC_DECODER_STABILIZATION_WAIT);
			add_समयr(&hdw->decoder_stabilization_समयr);
		पूर्ण अन्यथा अणु
			hdw->state_decoder_पढ़ोy = !0;
		पूर्ण
	पूर्ण
	trace_stbit("state_decoder_quiescent",hdw->state_decoder_quiescent);
	trace_stbit("state_decoder_run",hdw->state_decoder_run);
	trace_stbit("state_decoder_ready", hdw->state_decoder_पढ़ोy);
	वापस !0;
पूर्ण


/* Evaluate whether or not state_usbstream_run can change */
अटल पूर्णांक state_eval_usbstream_run(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->state_usbstream_run) अणु
		पूर्णांक fl = !0;
		अगर (hdw->pathway_state == PVR2_PATHWAY_ANALOG) अणु
			fl = (hdw->state_encoder_ok &&
			      hdw->state_encoder_run);
		पूर्ण अन्यथा अगर ((hdw->pathway_state == PVR2_PATHWAY_DIGITAL) &&
			   (hdw->hdw_desc->flag_digital_requires_cx23416)) अणु
			fl = hdw->state_encoder_ok;
		पूर्ण
		अगर (fl &&
		    hdw->state_pipeline_req &&
		    !hdw->state_pipeline_छोड़ो &&
		    hdw->state_pathway_ok) अणु
			वापस 0;
		पूर्ण
		pvr2_hdw_cmd_usbstream(hdw,0);
		hdw->state_usbstream_run = 0;
	पूर्ण अन्यथा अणु
		अगर (!hdw->state_pipeline_req ||
		    hdw->state_pipeline_छोड़ो ||
		    !hdw->state_pathway_ok) वापस 0;
		अगर (hdw->pathway_state == PVR2_PATHWAY_ANALOG) अणु
			अगर (!hdw->state_encoder_ok ||
			    !hdw->state_encoder_run) वापस 0;
		पूर्ण अन्यथा अगर ((hdw->pathway_state == PVR2_PATHWAY_DIGITAL) &&
			   (hdw->hdw_desc->flag_digital_requires_cx23416)) अणु
			अगर (!hdw->state_encoder_ok) वापस 0;
			अगर (hdw->state_encoder_run) वापस 0;
			अगर (hdw->hdw_desc->digital_control_scheme ==
			    PVR2_DIGITAL_SCHEME_ONAIR) अणु
				/* OnAir digital receivers won't stream
				   unless the analog encoder has run first.
				   Why?  I have no idea.  But करोn't even
				   try until we know the analog side is
				   known to have run. */
				अगर (!hdw->state_encoder_runok) वापस 0;
			पूर्ण
		पूर्ण
		अगर (pvr2_hdw_cmd_usbstream(hdw,!0) < 0) वापस 0;
		hdw->state_usbstream_run = !0;
	पूर्ण
	trace_stbit("state_usbstream_run",hdw->state_usbstream_run);
	वापस !0;
पूर्ण


/* Attempt to configure pipeline, अगर needed */
अटल पूर्णांक state_eval_pipeline_config(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->state_pipeline_config ||
	    hdw->state_pipeline_छोड़ो) वापस 0;
	pvr2_hdw_commit_execute(hdw);
	वापस !0;
पूर्ण


/* Update pipeline idle and pipeline छोड़ो tracking states based on other
   inमाला_दो.  This must be called whenever the other relevant inमाला_दो have
   changed. */
अटल पूर्णांक state_update_pipeline_state(काष्ठा pvr2_hdw *hdw)
अणु
	अचिन्हित पूर्णांक st;
	पूर्णांक updatedFl = 0;
	/* Update pipeline state */
	st = !(hdw->state_encoder_run ||
	       hdw->state_decoder_run ||
	       hdw->state_usbstream_run ||
	       (!hdw->state_decoder_quiescent));
	अगर (!st != !hdw->state_pipeline_idle) अणु
		hdw->state_pipeline_idle = st;
		updatedFl = !0;
	पूर्ण
	अगर (hdw->state_pipeline_idle && hdw->state_pipeline_छोड़ो) अणु
		hdw->state_pipeline_छोड़ो = 0;
		updatedFl = !0;
	पूर्ण
	वापस updatedFl;
पूर्ण


प्रकार पूर्णांक (*state_eval_func)(काष्ठा pvr2_hdw *);

/* Set of functions to be run to evaluate various states in the driver. */
अटल स्थिर state_eval_func eval_funcs[] = अणु
	state_eval_pathway_ok,
	state_eval_pipeline_config,
	state_eval_encoder_ok,
	state_eval_encoder_config,
	state_eval_decoder_run,
	state_eval_encoder_run,
	state_eval_usbstream_run,
पूर्ण;


/* Process various states and वापस true अगर we did anything पूर्णांकeresting. */
अटल पूर्णांक pvr2_hdw_state_update(काष्ठा pvr2_hdw *hdw)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक state_updated = 0;
	पूर्णांक check_flag;

	अगर (!hdw->state_stale) वापस 0;
	अगर ((hdw->fw1_state != FW1_STATE_OK) ||
	    !hdw->flag_ok) अणु
		hdw->state_stale = 0;
		वापस !0;
	पूर्ण
	/* This loop is the heart of the entire driver.  It keeps trying to
	   evaluate various bits of driver state until nothing changes क्रम
	   one full iteration.  Each "bit of state" tracks some global
	   aspect of the driver, e.g. whether decoder should run, अगर
	   pipeline is configured, usb streaming is on, etc.  We separately
	   evaluate each of those questions based on other driver state to
	   arrive at the correct running configuration. */
	करो अणु
		check_flag = 0;
		state_update_pipeline_state(hdw);
		/* Iterate over each bit of state */
		क्रम (i = 0; (i<ARRAY_SIZE(eval_funcs)) && hdw->flag_ok; i++) अणु
			अगर ((*eval_funcs[i])(hdw)) अणु
				check_flag = !0;
				state_updated = !0;
				state_update_pipeline_state(hdw);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (check_flag && hdw->flag_ok);
	hdw->state_stale = 0;
	trace_stbit("state_stale",hdw->state_stale);
	वापस state_updated;
पूर्ण


अटल अचिन्हित पूर्णांक prपूर्णांक_input_mask(अचिन्हित पूर्णांक msk,
				     अक्षर *buf,अचिन्हित पूर्णांक acnt)
अणु
	अचिन्हित पूर्णांक idx,ccnt;
	अचिन्हित पूर्णांक tcnt = 0;
	क्रम (idx = 0; idx < ARRAY_SIZE(control_values_input); idx++) अणु
		अगर (!((1UL << idx) & msk)) जारी;
		ccnt = scnम_लिखो(buf+tcnt,
				 acnt-tcnt,
				 "%s%s",
				 (tcnt ? ", " : ""),
				 control_values_input[idx]);
		tcnt += ccnt;
	पूर्ण
	वापस tcnt;
पूर्ण


अटल स्थिर अक्षर *pvr2_pathway_state_name(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल PVR2_PATHWAY_ANALOG: वापस "analog";
	हाल PVR2_PATHWAY_DIGITAL: वापस "digital";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण


अटल अचिन्हित पूर्णांक pvr2_hdw_report_unlocked(काष्ठा pvr2_hdw *hdw,पूर्णांक which,
					     अक्षर *buf,अचिन्हित पूर्णांक acnt)
अणु
	चयन (which) अणु
	हाल 0:
		वापस scnम_लिखो(
			buf,acnt,
			"driver:%s%s%s%s%s <mode=%s>",
			(hdw->flag_ok ? " <ok>" : " <fail>"),
			(hdw->flag_init_ok ? " <init>" : " <uninitialized>"),
			(hdw->flag_disconnected ? " <disconnected>" :
			 " <connected>"),
			(hdw->flag_tripped ? " <tripped>" : ""),
			(hdw->flag_decoder_missed ? " <no decoder>" : ""),
			pvr2_pathway_state_name(hdw->pathway_state));

	हाल 1:
		वापस scnम_लिखो(
			buf,acnt,
			"pipeline:%s%s%s%s",
			(hdw->state_pipeline_idle ? " <idle>" : ""),
			(hdw->state_pipeline_config ?
			 " <configok>" : " <stale>"),
			(hdw->state_pipeline_req ? " <req>" : ""),
			(hdw->state_pipeline_छोड़ो ? " <pause>" : ""));
	हाल 2:
		वापस scnम_लिखो(
			buf,acnt,
			"worker:%s%s%s%s%s%s%s",
			(hdw->state_decoder_run ?
			 (hdw->state_decoder_पढ़ोy ?
			  "<decode:run>" : " <decode:start>") :
			 (hdw->state_decoder_quiescent ?
			  "" : " <decode:stop>")),
			(hdw->state_decoder_quiescent ?
			 " <decode:quiescent>" : ""),
			(hdw->state_encoder_ok ?
			 "" : " <encode:init>"),
			(hdw->state_encoder_run ?
			 (hdw->state_encoder_runok ?
			  " <encode:run>" :
			  " <encode:firstrun>") :
			 (hdw->state_encoder_runok ?
			  " <encode:stop>" :
			  " <encode:virgin>")),
			(hdw->state_encoder_config ?
			 " <encode:configok>" :
			 (hdw->state_encoder_रुकोok ?
			  "" : " <encode:waitok>")),
			(hdw->state_usbstream_run ?
			 " <usb:run>" : " <usb:stop>"),
			(hdw->state_pathway_ok ?
			 " <pathway:ok>" : ""));
	हाल 3:
		वापस scnम_लिखो(
			buf,acnt,
			"state: %s",
			pvr2_get_state_name(hdw->master_state));
	हाल 4: अणु
		अचिन्हित पूर्णांक tcnt = 0;
		अचिन्हित पूर्णांक ccnt;

		ccnt = scnम_लिखो(buf,
				 acnt,
				 "Hardware supported inputs: ");
		tcnt += ccnt;
		tcnt += prपूर्णांक_input_mask(hdw->input_avail_mask,
					 buf+tcnt,
					 acnt-tcnt);
		अगर (hdw->input_avail_mask != hdw->input_allowed_mask) अणु
			ccnt = scnम_लिखो(buf+tcnt,
					 acnt-tcnt,
					 "; allowed inputs: ");
			tcnt += ccnt;
			tcnt += prपूर्णांक_input_mask(hdw->input_allowed_mask,
						 buf+tcnt,
						 acnt-tcnt);
		पूर्ण
		वापस tcnt;
	पूर्ण
	हाल 5: अणु
		काष्ठा pvr2_stream_stats stats;
		अगर (!hdw->vid_stream) अवरोध;
		pvr2_stream_get_stats(hdw->vid_stream,
				      &stats,
				      0);
		वापस scnम_लिखो(
			buf,acnt,
			"Bytes streamed=%u URBs: queued=%u idle=%u ready=%u processed=%u failed=%u",
			stats.bytes_processed,
			stats.buffers_in_queue,
			stats.buffers_in_idle,
			stats.buffers_in_पढ़ोy,
			stats.buffers_processed,
			stats.buffers_failed);
	पूर्ण
	हाल 6: अणु
		अचिन्हित पूर्णांक id = hdw->ir_scheme_active;
		वापस scnम_लिखो(buf, acnt, "ir scheme: id=%d %s", id,
				 (id >= ARRAY_SIZE(ir_scheme_names) ?
				  "?" : ir_scheme_names[id]));
	पूर्ण
	शेष: अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


/* Generate report containing info about attached sub-devices and attached
   i2c clients, including an indication of which attached i2c clients are
   actually sub-devices. */
अटल अचिन्हित पूर्णांक pvr2_hdw_report_clients(काष्ठा pvr2_hdw *hdw,
					    अक्षर *buf, अचिन्हित पूर्णांक acnt)
अणु
	काष्ठा v4l2_subdev *sd;
	अचिन्हित पूर्णांक tcnt = 0;
	अचिन्हित पूर्णांक ccnt;
	काष्ठा i2c_client *client;
	स्थिर अक्षर *p;
	अचिन्हित पूर्णांक id;

	ccnt = scnम_लिखो(buf, acnt, "Associated v4l2-subdev drivers and I2C clients:\n");
	tcnt += ccnt;
	v4l2_device_क्रम_each_subdev(sd, &hdw->v4l2_dev) अणु
		id = sd->grp_id;
		p = शून्य;
		अगर (id < ARRAY_SIZE(module_names)) p = module_names[id];
		अगर (p) अणु
			ccnt = scnम_लिखो(buf + tcnt, acnt - tcnt, "  %s:", p);
			tcnt += ccnt;
		पूर्ण अन्यथा अणु
			ccnt = scnम_लिखो(buf + tcnt, acnt - tcnt,
					 "  (unknown id=%u):", id);
			tcnt += ccnt;
		पूर्ण
		client = v4l2_get_subdevdata(sd);
		अगर (client) अणु
			ccnt = scnम_लिखो(buf + tcnt, acnt - tcnt,
					 " %s @ %02x\n", client->name,
					 client->addr);
			tcnt += ccnt;
		पूर्ण अन्यथा अणु
			ccnt = scnम_लिखो(buf + tcnt, acnt - tcnt,
					 " no i2c client\n");
			tcnt += ccnt;
		पूर्ण
	पूर्ण
	वापस tcnt;
पूर्ण


अचिन्हित पूर्णांक pvr2_hdw_state_report(काष्ठा pvr2_hdw *hdw,
				   अक्षर *buf,अचिन्हित पूर्णांक acnt)
अणु
	अचिन्हित पूर्णांक bcnt,ccnt,idx;
	bcnt = 0;
	LOCK_TAKE(hdw->big_lock);
	क्रम (idx = 0; ; idx++) अणु
		ccnt = pvr2_hdw_report_unlocked(hdw,idx,buf,acnt);
		अगर (!ccnt) अवरोध;
		bcnt += ccnt; acnt -= ccnt; buf += ccnt;
		अगर (!acnt) अवरोध;
		buf[0] = '\n'; ccnt = 1;
		bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	पूर्ण
	ccnt = pvr2_hdw_report_clients(hdw, buf, acnt);
	bcnt += ccnt; acnt -= ccnt; buf += ccnt;
	LOCK_GIVE(hdw->big_lock);
	वापस bcnt;
पूर्ण


अटल व्योम pvr2_hdw_state_log_state(काष्ठा pvr2_hdw *hdw)
अणु
	अक्षर buf[256];
	अचिन्हित पूर्णांक idx, ccnt;
	अचिन्हित पूर्णांक lcnt, ucnt;

	क्रम (idx = 0; ; idx++) अणु
		ccnt = pvr2_hdw_report_unlocked(hdw,idx,buf,माप(buf));
		अगर (!ccnt) अवरोध;
		pr_info("%s %.*s\n", hdw->name, ccnt, buf);
	पूर्ण
	ccnt = pvr2_hdw_report_clients(hdw, buf, माप(buf));
	अगर (ccnt >= माप(buf))
		ccnt = माप(buf);

	ucnt = 0;
	जबतक (ucnt < ccnt) अणु
		lcnt = 0;
		जबतक ((lcnt + ucnt < ccnt) && (buf[lcnt + ucnt] != '\n')) अणु
			lcnt++;
		पूर्ण
		pr_info("%s %.*s\n", hdw->name, lcnt, buf + ucnt);
		ucnt += lcnt + 1;
	पूर्ण
पूर्ण


/* Evaluate and update the driver's current state, taking various actions
   as appropriate क्रम the update. */
अटल पूर्णांक pvr2_hdw_state_eval(काष्ठा pvr2_hdw *hdw)
अणु
	अचिन्हित पूर्णांक st;
	पूर्णांक state_updated = 0;
	पूर्णांक callback_flag = 0;
	पूर्णांक analog_mode;

	pvr2_trace(PVR2_TRACE_STBITS,
		   "Drive state check START");
	अगर (pvrusb2_debug & PVR2_TRACE_STBITS) अणु
		pvr2_hdw_state_log_state(hdw);
	पूर्ण

	/* Process all state and get back over disposition */
	state_updated = pvr2_hdw_state_update(hdw);

	analog_mode = (hdw->pathway_state != PVR2_PATHWAY_DIGITAL);

	/* Update master state based upon all other states. */
	अगर (!hdw->flag_ok) अणु
		st = PVR2_STATE_DEAD;
	पूर्ण अन्यथा अगर (hdw->fw1_state != FW1_STATE_OK) अणु
		st = PVR2_STATE_COLD;
	पूर्ण अन्यथा अगर ((analog_mode ||
		    hdw->hdw_desc->flag_digital_requires_cx23416) &&
		   !hdw->state_encoder_ok) अणु
		st = PVR2_STATE_WARM;
	पूर्ण अन्यथा अगर (hdw->flag_tripped ||
		   (analog_mode && hdw->flag_decoder_missed)) अणु
		st = PVR2_STATE_ERROR;
	पूर्ण अन्यथा अगर (hdw->state_usbstream_run &&
		   (!analog_mode ||
		    (hdw->state_encoder_run && hdw->state_decoder_run))) अणु
		st = PVR2_STATE_RUN;
	पूर्ण अन्यथा अणु
		st = PVR2_STATE_READY;
	पूर्ण
	अगर (hdw->master_state != st) अणु
		pvr2_trace(PVR2_TRACE_STATE,
			   "Device state change from %s to %s",
			   pvr2_get_state_name(hdw->master_state),
			   pvr2_get_state_name(st));
		pvr2_led_ctrl(hdw,st == PVR2_STATE_RUN);
		hdw->master_state = st;
		state_updated = !0;
		callback_flag = !0;
	पूर्ण
	अगर (state_updated) अणु
		/* Trigger anyone रुकोing on any state changes here. */
		wake_up(&hdw->state_रुको_data);
	पूर्ण

	अगर (pvrusb2_debug & PVR2_TRACE_STBITS) अणु
		pvr2_hdw_state_log_state(hdw);
	पूर्ण
	pvr2_trace(PVR2_TRACE_STBITS,
		   "Drive state check DONE callback=%d",callback_flag);

	वापस callback_flag;
पूर्ण


/* Cause kernel thपढ़ो to check / update driver state */
अटल व्योम pvr2_hdw_state_sched(काष्ठा pvr2_hdw *hdw)
अणु
	अगर (hdw->state_stale) वापस;
	hdw->state_stale = !0;
	trace_stbit("state_stale",hdw->state_stale);
	schedule_work(&hdw->workpoll);
पूर्ण


पूर्णांक pvr2_hdw_gpio_get_dir(काष्ठा pvr2_hdw *hdw,u32 *dp)
अणु
	वापस pvr2_पढ़ो_रेजिस्टर(hdw,PVR2_GPIO_सूची,dp);
पूर्ण


पूर्णांक pvr2_hdw_gpio_get_out(काष्ठा pvr2_hdw *hdw,u32 *dp)
अणु
	वापस pvr2_पढ़ो_रेजिस्टर(hdw,PVR2_GPIO_OUT,dp);
पूर्ण


पूर्णांक pvr2_hdw_gpio_get_in(काष्ठा pvr2_hdw *hdw,u32 *dp)
अणु
	वापस pvr2_पढ़ो_रेजिस्टर(hdw,PVR2_GPIO_IN,dp);
पूर्ण


पूर्णांक pvr2_hdw_gpio_chg_dir(काष्ठा pvr2_hdw *hdw,u32 msk,u32 val)
अणु
	u32 cval,nval;
	पूर्णांक ret;
	अगर (~msk) अणु
		ret = pvr2_पढ़ो_रेजिस्टर(hdw,PVR2_GPIO_सूची,&cval);
		अगर (ret) वापस ret;
		nval = (cval & ~msk) | (val & msk);
		pvr2_trace(PVR2_TRACE_GPIO,
			   "GPIO direction changing 0x%x:0x%x from 0x%x to 0x%x",
			   msk,val,cval,nval);
	पूर्ण अन्यथा अणु
		nval = val;
		pvr2_trace(PVR2_TRACE_GPIO,
			   "GPIO direction changing to 0x%x",nval);
	पूर्ण
	वापस pvr2_ग_लिखो_रेजिस्टर(hdw,PVR2_GPIO_सूची,nval);
पूर्ण


पूर्णांक pvr2_hdw_gpio_chg_out(काष्ठा pvr2_hdw *hdw,u32 msk,u32 val)
अणु
	u32 cval,nval;
	पूर्णांक ret;
	अगर (~msk) अणु
		ret = pvr2_पढ़ो_रेजिस्टर(hdw,PVR2_GPIO_OUT,&cval);
		अगर (ret) वापस ret;
		nval = (cval & ~msk) | (val & msk);
		pvr2_trace(PVR2_TRACE_GPIO,
			   "GPIO output changing 0x%x:0x%x from 0x%x to 0x%x",
			   msk,val,cval,nval);
	पूर्ण अन्यथा अणु
		nval = val;
		pvr2_trace(PVR2_TRACE_GPIO,
			   "GPIO output changing to 0x%x",nval);
	पूर्ण
	वापस pvr2_ग_लिखो_रेजिस्टर(hdw,PVR2_GPIO_OUT,nval);
पूर्ण


व्योम pvr2_hdw_status_poll(काष्ठा pvr2_hdw *hdw)
अणु
	काष्ठा v4l2_tuner *vtp = &hdw->tuner_संकेत_info;
	स_रखो(vtp, 0, माप(*vtp));
	vtp->type = (hdw->input_val == PVR2_CVAL_INPUT_RADIO) ?
		V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
	hdw->tuner_संकेत_stale = 0;
	/* Note: There apparently is no replacement क्रम VIDIOC_CROPCAP
	   using v4l2-subdev - thereक्रमe we can't support that AT ALL right
	   now.  (Of course, no sub-drivers seem to implement it either.
	   But now it's a a chicken and egg problem...) */
	v4l2_device_call_all(&hdw->v4l2_dev, 0, tuner, g_tuner, vtp);
	pvr2_trace(PVR2_TRACE_CHIPS, "subdev status poll type=%u strength=%u audio=0x%x cap=0x%x low=%u hi=%u",
		   vtp->type,
		   vtp->संकेत, vtp->rxsubchans, vtp->capability,
		   vtp->rangelow, vtp->rangehigh);

	/* We have to करो this to aव्योम getting पूर्णांकo स्थिरant polling अगर
	   there's nobody to answer a poll of cropcap info. */
	hdw->cropcap_stale = 0;
पूर्ण


अचिन्हित पूर्णांक pvr2_hdw_get_input_available(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->input_avail_mask;
पूर्ण


अचिन्हित पूर्णांक pvr2_hdw_get_input_allowed(काष्ठा pvr2_hdw *hdw)
अणु
	वापस hdw->input_allowed_mask;
पूर्ण


अटल पूर्णांक pvr2_hdw_set_input(काष्ठा pvr2_hdw *hdw,पूर्णांक v)
अणु
	अगर (hdw->input_val != v) अणु
		hdw->input_val = v;
		hdw->input_dirty = !0;
	पूर्ण

	/* Handle side effects - अगर we चयन to a mode that needs the RF
	   tuner, then select the right frequency choice as well and mark
	   it dirty. */
	अगर (hdw->input_val == PVR2_CVAL_INPUT_RADIO) अणु
		hdw->freqSelector = 0;
		hdw->freqDirty = !0;
	पूर्ण अन्यथा अगर ((hdw->input_val == PVR2_CVAL_INPUT_TV) ||
		   (hdw->input_val == PVR2_CVAL_INPUT_DTV)) अणु
		hdw->freqSelector = 1;
		hdw->freqDirty = !0;
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक pvr2_hdw_set_input_allowed(काष्ठा pvr2_hdw *hdw,
			       अचिन्हित पूर्णांक change_mask,
			       अचिन्हित पूर्णांक change_val)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक nv,m,idx;
	LOCK_TAKE(hdw->big_lock);
	करो अणु
		nv = hdw->input_allowed_mask & ~change_mask;
		nv |= (change_val & change_mask);
		nv &= hdw->input_avail_mask;
		अगर (!nv) अणु
			/* No legal modes left; वापस error instead. */
			ret = -EPERM;
			अवरोध;
		पूर्ण
		hdw->input_allowed_mask = nv;
		अगर ((1UL << hdw->input_val) & hdw->input_allowed_mask) अणु
			/* Current mode is still in the allowed mask, so
			   we're करोne. */
			अवरोध;
		पूर्ण
		/* Select and चयन to a mode that is still in the allowed
		   mask */
		अगर (!hdw->input_allowed_mask) अणु
			/* Nothing legal; give up */
			अवरोध;
		पूर्ण
		m = hdw->input_allowed_mask;
		क्रम (idx = 0; idx < (माप(m) << 3); idx++) अणु
			अगर (!((1UL << idx) & m)) जारी;
			pvr2_hdw_set_input(hdw,idx);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (0);
	LOCK_GIVE(hdw->big_lock);
	वापस ret;
पूर्ण


/* Find I2C address of eeprom */
अटल पूर्णांक pvr2_hdw_get_eeprom_addr(काष्ठा pvr2_hdw *hdw)
अणु
	पूर्णांक result;
	LOCK_TAKE(hdw->ctl_lock); करो अणु
		hdw->cmd_buffer[0] = FX2CMD_GET_EEPROM_ADDR;
		result = pvr2_send_request(hdw,
					   hdw->cmd_buffer,1,
					   hdw->cmd_buffer,1);
		अगर (result < 0) अवरोध;
		result = hdw->cmd_buffer[0];
	पूर्ण जबतक(0); LOCK_GIVE(hdw->ctl_lock);
	वापस result;
पूर्ण
