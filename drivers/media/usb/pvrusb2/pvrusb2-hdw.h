<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_HDW_H
#घोषणा __PVRUSB2_HDW_H

#समावेश <linux/usb.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-dev.h>
#समावेश "pvrusb2-io.h"
#समावेश "pvrusb2-ctrl.h"


/* Private पूर्णांकernal control ids, look these up with
   pvr2_hdw_get_ctrl_by_id() - these are NOT visible in V4L */
#घोषणा PVR2_CID_STDCUR 2
#घोषणा PVR2_CID_STDAVAIL 3
#घोषणा PVR2_CID_INPUT 4
#घोषणा PVR2_CID_AUDIOMODE 5
#घोषणा PVR2_CID_FREQUENCY 6
#घोषणा PVR2_CID_HRES 7
#घोषणा PVR2_CID_VRES 8
#घोषणा PVR2_CID_CROPL 9
#घोषणा PVR2_CID_CROPT 10
#घोषणा PVR2_CID_CROPW 11
#घोषणा PVR2_CID_CROPH 12
#घोषणा PVR2_CID_CROPCAPPAN 13
#घोषणा PVR2_CID_CROPCAPPAD 14
#घोषणा PVR2_CID_CROPCAPBL 15
#घोषणा PVR2_CID_CROPCAPBT 16
#घोषणा PVR2_CID_CROPCAPBW 17
#घोषणा PVR2_CID_CROPCAPBH 18
#घोषणा PVR2_CID_STDDETECT 19

/* Legal values क्रम the INPUT state variable */
#घोषणा PVR2_CVAL_INPUT_TV 0
#घोषणा PVR2_CVAL_INPUT_DTV 1
#घोषणा PVR2_CVAL_INPUT_COMPOSITE 2
#घोषणा PVR2_CVAL_INPUT_SVIDEO 3
#घोषणा PVR2_CVAL_INPUT_RADIO 4
#घोषणा PVR2_CVAL_INPUT_MAX PVR2_CVAL_INPUT_RADIO

क्रमागत pvr2_config अणु
	pvr2_config_empty,    /* No configuration */
	pvr2_config_mpeg,     /* Encoded / compressed video */
	pvr2_config_vbi,      /* Standard vbi info */
	pvr2_config_pcm,      /* Audio raw pcm stream */
	pvr2_config_rawvideo, /* Video raw frames */
पूर्ण;

क्रमागत pvr2_v4l_type अणु
	pvr2_v4l_type_video,
	pvr2_v4l_type_vbi,
	pvr2_v4l_type_radio,
पूर्ण;

/* Major states that we can be in:
 *
 *  DEAD - Device is in an unusable state and cannot be recovered.  This
 *  can happen अगर we completely lose the ability to communicate with it
 *  (but it might still on the bus).  In this state there's nothing we can
 *  करो; it must be replugged in order to recover.
 *
 *  COLD - Device is in an unusable state, needs microcontroller firmware.
 *
 *  WARM - We can communicate with the device and the proper
 *  microcontroller firmware is running, but other device initialization is
 *  still needed (e.g. encoder firmware).
 *
 *  ERROR - A problem prevents capture operation (e.g. encoder firmware
 *  missing).
 *
 *  READY - Device is operational, but not streaming.
 *
 *  RUN - Device is streaming.
 *
 */
#घोषणा PVR2_STATE_NONE 0
#घोषणा PVR2_STATE_DEAD 1
#घोषणा PVR2_STATE_COLD 2
#घोषणा PVR2_STATE_WARM 3
#घोषणा PVR2_STATE_ERROR 4
#घोषणा PVR2_STATE_READY 5
#घोषणा PVR2_STATE_RUN 6

/* Translate configuration क्रमागत to a string label */
स्थिर अक्षर *pvr2_config_get_name(क्रमागत pvr2_config);

काष्ठा pvr2_hdw;

/* Create and वापस a काष्ठाure क्रम पूर्णांकeracting with the underlying
   hardware */
काष्ठा pvr2_hdw *pvr2_hdw_create(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				 स्थिर काष्ठा usb_device_id *devid);

/* Perक्रमm second stage initialization, passing in a notअगरication callback
   क्रम when the master state changes. */
पूर्णांक pvr2_hdw_initialize(काष्ठा pvr2_hdw *,
			व्योम (*callback_func)(व्योम *),
			व्योम *callback_data);

/* Destroy hardware पूर्णांकeraction काष्ठाure */
व्योम pvr2_hdw_destroy(काष्ठा pvr2_hdw *);

/* Return true अगर in the पढ़ोy (normal) state */
पूर्णांक pvr2_hdw_dev_ok(काष्ठा pvr2_hdw *);

/* Return small पूर्णांकeger number [1..N] क्रम logical instance number of this
   device.  This is useful क्रम indexing array-valued module parameters. */
पूर्णांक pvr2_hdw_get_unit_number(काष्ठा pvr2_hdw *);

/* Get poपूर्णांकer to underlying USB device */
काष्ठा usb_device *pvr2_hdw_get_dev(काष्ठा pvr2_hdw *);

/* Retrieve serial number of device */
अचिन्हित दीर्घ pvr2_hdw_get_sn(काष्ठा pvr2_hdw *);

/* Retrieve bus location info of device */
स्थिर अक्षर *pvr2_hdw_get_bus_info(काष्ठा pvr2_hdw *);

/* Retrieve per-instance string identअगरier क्रम this specअगरic device */
स्थिर अक्षर *pvr2_hdw_get_device_identअगरier(काष्ठा pvr2_hdw *);

/* Called when hardware has been unplugged */
व्योम pvr2_hdw_disconnect(काष्ठा pvr2_hdw *);

/* Sets v4l2_dev of a video_device काष्ठा */
व्योम pvr2_hdw_set_v4l2_dev(काष्ठा pvr2_hdw *, काष्ठा video_device *);

/* Get the number of defined controls */
अचिन्हित पूर्णांक pvr2_hdw_get_ctrl_count(काष्ठा pvr2_hdw *);

/* Retrieve a control handle given its index (0..count-1) */
काष्ठा pvr2_ctrl *pvr2_hdw_get_ctrl_by_index(काष्ठा pvr2_hdw *,अचिन्हित पूर्णांक);

/* Retrieve a control handle given its पूर्णांकernal ID (अगर any) */
काष्ठा pvr2_ctrl *pvr2_hdw_get_ctrl_by_id(काष्ठा pvr2_hdw *,अचिन्हित पूर्णांक);

/* Retrieve a control handle given its V4L ID (अगर any) */
काष्ठा pvr2_ctrl *pvr2_hdw_get_ctrl_v4l(काष्ठा pvr2_hdw *,अचिन्हित पूर्णांक ctl_id);

/* Retrieve a control handle given its immediate predecessor V4L ID (अगर any) */
काष्ठा pvr2_ctrl *pvr2_hdw_get_ctrl_nextv4l(काष्ठा pvr2_hdw *,
					    अचिन्हित पूर्णांक ctl_id);

/* Commit all control changes made up to this poपूर्णांक */
पूर्णांक pvr2_hdw_commit_ctl(काष्ठा pvr2_hdw *);

/* Return a bit mask of valid input selections क्रम this device.  Mask bits
 * will be according to PVR_CVAL_INPUT_xxxx definitions. */
अचिन्हित पूर्णांक pvr2_hdw_get_input_available(काष्ठा pvr2_hdw *);

/* Return a bit mask of allowed input selections क्रम this device.  Mask bits
 * will be according to PVR_CVAL_INPUT_xxxx definitions. */
अचिन्हित पूर्णांक pvr2_hdw_get_input_allowed(काष्ठा pvr2_hdw *);

/* Change the set of allowed input selections क्रम this device.  Both
   change_mask and change_valu are mask bits according to
   PVR_CVAL_INPUT_xxxx definitions.  The change_mask parameter indicate
   which settings are being changed and the change_val parameter indicates
   whether corresponding settings are being set or cleared. */
पूर्णांक pvr2_hdw_set_input_allowed(काष्ठा pvr2_hdw *,
			       अचिन्हित पूर्णांक change_mask,
			       अचिन्हित पूर्णांक change_val);

/* Return name क्रम this driver instance */
स्थिर अक्षर *pvr2_hdw_get_driver_name(काष्ठा pvr2_hdw *);

/* Mark tuner status stale so that it will be re-fetched */
व्योम pvr2_hdw_execute_tuner_poll(काष्ठा pvr2_hdw *);

/* Return inक्रमmation about the tuner */
पूर्णांक pvr2_hdw_get_tuner_status(काष्ठा pvr2_hdw *,काष्ठा v4l2_tuner *);

/* Return inक्रमmation about cropping capabilities */
पूर्णांक pvr2_hdw_get_cropcap(काष्ठा pvr2_hdw *, काष्ठा v4l2_cropcap *);

/* Query device and see अगर it thinks it is on a high-speed USB link */
पूर्णांक pvr2_hdw_is_hsm(काष्ठा pvr2_hdw *);

/* Return a string token representative of the hardware type */
स्थिर अक्षर *pvr2_hdw_get_type(काष्ठा pvr2_hdw *);

/* Return a single line description of the hardware type */
स्थिर अक्षर *pvr2_hdw_get_desc(काष्ठा pvr2_hdw *);

/* Turn streaming on/off */
पूर्णांक pvr2_hdw_set_streaming(काष्ठा pvr2_hdw *,पूर्णांक);

/* Find out अगर streaming is on */
पूर्णांक pvr2_hdw_get_streaming(काष्ठा pvr2_hdw *);

/* Retrieve driver overall state */
पूर्णांक pvr2_hdw_get_state(काष्ठा pvr2_hdw *);

/* Configure the type of stream to generate */
पूर्णांक pvr2_hdw_set_stream_type(काष्ठा pvr2_hdw *, क्रमागत pvr2_config);

/* Get handle to video output stream */
काष्ठा pvr2_stream *pvr2_hdw_get_video_stream(काष्ठा pvr2_hdw *);

/* Enable / disable retrieval of CPU firmware or prom contents.  This must
   be enabled beक्रमe pvr2_hdw_cpufw_get() will function.  Note that करोing
   this may prevent the device from running (and leaving this mode may
   imply a device reset). */
व्योम pvr2_hdw_cpufw_set_enabled(काष्ठा pvr2_hdw *,
				पूर्णांक mode, /* 0=8KB FX2, 1=16KB FX2, 2=PROM */
				पूर्णांक enable_flag);

/* Return true अगर we're in a mode क्रम retrieval CPU firmware */
पूर्णांक pvr2_hdw_cpufw_get_enabled(काष्ठा pvr2_hdw *);

/* Retrieve a piece of the CPU's firmware at the given offset.  Return
   value is the number of bytes retrieved or zero अगर we're past the end or
   an error otherwise (e.g. अगर firmware retrieval is not enabled). */
पूर्णांक pvr2_hdw_cpufw_get(काष्ठा pvr2_hdw *,अचिन्हित पूर्णांक offs,
		       अक्षर *buf,अचिन्हित पूर्णांक cnt);

/* Retrieve a previously stored v4l minor device number */
पूर्णांक pvr2_hdw_v4l_get_minor_number(काष्ठा pvr2_hdw *,क्रमागत pvr2_v4l_type index);

/* Store a v4l minor device number */
व्योम pvr2_hdw_v4l_store_minor_number(काष्ठा pvr2_hdw *,
				     क्रमागत pvr2_v4l_type index,पूर्णांक);

/* The following entry poपूर्णांकs are all lower level things you normally करोn't
   want to worry about. */

/* Issue a command and get a response from the device.  LOTS of higher
   level stuff is built on this. */
पूर्णांक pvr2_send_request(काष्ठा pvr2_hdw *,
		      व्योम *ग_लिखो_ptr,अचिन्हित पूर्णांक ग_लिखो_len,
		      व्योम *पढ़ो_ptr,अचिन्हित पूर्णांक पढ़ो_len);

/* Slightly higher level device communication functions. */
पूर्णांक pvr2_ग_लिखो_रेजिस्टर(काष्ठा pvr2_hdw *, u16, u32);

/* Call अगर क्रम any reason we can't talk to the hardware anymore - this will
   cause the driver to stop flailing on the device. */
व्योम pvr2_hdw_render_useless(काष्ठा pvr2_hdw *);

/* Set / clear 8051's reset bit */
व्योम pvr2_hdw_cpureset_निश्चित(काष्ठा pvr2_hdw *,पूर्णांक);

/* Execute a USB-commanded device reset */
व्योम pvr2_hdw_device_reset(काष्ठा pvr2_hdw *);

/* Reset worker's error trapping circuit अवरोधer */
पूर्णांक pvr2_hdw_untrip(काष्ठा pvr2_hdw *);

/* Execute hard reset command (after this poपूर्णांक it's likely that the
   encoder will have to be reconfigured).  This also clears the "useless"
   state. */
पूर्णांक pvr2_hdw_cmd_deep_reset(काष्ठा pvr2_hdw *);

/* Execute simple reset command */
पूर्णांक pvr2_hdw_cmd_घातerup(काष्ठा pvr2_hdw *);

/* Order decoder to reset */
पूर्णांक pvr2_hdw_cmd_decoder_reset(काष्ठा pvr2_hdw *);

/* Direct manipulation of GPIO bits */
पूर्णांक pvr2_hdw_gpio_get_dir(काष्ठा pvr2_hdw *hdw,u32 *);
पूर्णांक pvr2_hdw_gpio_get_out(काष्ठा pvr2_hdw *hdw,u32 *);
पूर्णांक pvr2_hdw_gpio_get_in(काष्ठा pvr2_hdw *hdw,u32 *);
पूर्णांक pvr2_hdw_gpio_chg_dir(काष्ठा pvr2_hdw *hdw,u32 msk,u32 val);
पूर्णांक pvr2_hdw_gpio_chg_out(काष्ठा pvr2_hdw *hdw,u32 msk,u32 val);

/* This data काष्ठाure is specअगरically क्रम the next function... */
काष्ठा pvr2_hdw_debug_info अणु
	पूर्णांक big_lock_held;
	पूर्णांक ctl_lock_held;
	पूर्णांक flag_disconnected;
	पूर्णांक flag_init_ok;
	पूर्णांक flag_ok;
	पूर्णांक fw1_state;
	पूर्णांक flag_decoder_missed;
	पूर्णांक flag_tripped;
	पूर्णांक state_encoder_ok;
	पूर्णांक state_encoder_run;
	पूर्णांक state_decoder_run;
	पूर्णांक state_decoder_पढ़ोy;
	पूर्णांक state_usbstream_run;
	पूर्णांक state_decoder_quiescent;
	पूर्णांक state_pipeline_config;
	पूर्णांक state_pipeline_req;
	पूर्णांक state_pipeline_छोड़ो;
	पूर्णांक state_pipeline_idle;
	पूर्णांक cmd_debug_state;
	पूर्णांक cmd_debug_ग_लिखो_len;
	पूर्णांक cmd_debug_पढ़ो_len;
	पूर्णांक cmd_debug_ग_लिखो_pend;
	पूर्णांक cmd_debug_पढ़ो_pend;
	पूर्णांक cmd_debug_समयout;
	पूर्णांक cmd_debug_rstatus;
	पूर्णांक cmd_debug_wstatus;
	अचिन्हित अक्षर cmd_code;
पूर्ण;

/* Non-पूर्णांकrusively retrieve पूर्णांकernal state info - this is useful क्रम
   diagnosing lockups.  Note that this operation is completed without any
   kind of locking and so it is not atomic and may yield inconsistent
   results.  This is *purely* a debugging aid. */
व्योम pvr2_hdw_get_debug_info_unlocked(स्थिर काष्ठा pvr2_hdw *hdw,
				      काष्ठा pvr2_hdw_debug_info *);

/* Intrusively retrieve पूर्णांकernal state info - this is useful क्रम
   diagnosing overall driver state.  This operation synchronizes against
   the overall driver mutex - so अगर there are locking problems this will
   likely hang!  This is *purely* a debugging aid. */
व्योम pvr2_hdw_get_debug_info_locked(काष्ठा pvr2_hdw *hdw,
				    काष्ठा pvr2_hdw_debug_info *);

/* Report out several lines of text that describes driver पूर्णांकernal state.
   Results are written पूर्णांकo the passed-in buffer. */
अचिन्हित पूर्णांक pvr2_hdw_state_report(काष्ठा pvr2_hdw *hdw,
				   अक्षर *buf_ptr,अचिन्हित पूर्णांक buf_size);

/* Cause modules to log their state once */
व्योम pvr2_hdw_trigger_module_log(काष्ठा pvr2_hdw *hdw);

/* Cause encoder firmware to be uploaded पूर्णांकo the device.  This is normally
   करोne स्वतःnomously, but the पूर्णांकerface is exported here because it is also
   a debugging aid. */
पूर्णांक pvr2_upload_firmware2(काष्ठा pvr2_hdw *hdw);

#पूर्ण_अगर /* __PVRUSB2_HDW_H */
