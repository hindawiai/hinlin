<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  V4L2 sub-device support header.
 *
 *  Copyright (C) 2008  Hans Verkuil <hverkuil@xs4all.nl>
 */

#अगर_अघोषित _V4L2_SUBDEV_H
#घोषणा _V4L2_SUBDEV_H

#समावेश <linux/types.h>
#समावेश <linux/v4l2-subdev.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-mediabus.h>

/* generic v4l2_device notअगरy callback notअगरication values */
#घोषणा V4L2_SUBDEV_IR_RX_NOTIFY		_IOW('v', 0, u32)
#घोषणा V4L2_SUBDEV_IR_RX_FIFO_SERVICE_REQ	0x00000001
#घोषणा V4L2_SUBDEV_IR_RX_END_OF_RX_DETECTED	0x00000002
#घोषणा V4L2_SUBDEV_IR_RX_HW_FIFO_OVERRUN	0x00000004
#घोषणा V4L2_SUBDEV_IR_RX_SW_FIFO_OVERRUN	0x00000008

#घोषणा V4L2_SUBDEV_IR_TX_NOTIFY		_IOW('v', 1, u32)
#घोषणा V4L2_SUBDEV_IR_TX_FIFO_SERVICE_REQ	0x00000001

#घोषणा	V4L2_DEVICE_NOTIFY_EVENT		_IOW('v', 2, काष्ठा v4l2_event)

काष्ठा v4l2_device;
काष्ठा v4l2_ctrl_handler;
काष्ठा v4l2_event;
काष्ठा v4l2_event_subscription;
काष्ठा v4l2_fh;
काष्ठा v4l2_subdev;
काष्ठा v4l2_subdev_fh;
काष्ठा tuner_setup;
काष्ठा v4l2_mbus_frame_desc;

/**
 * काष्ठा v4l2_decode_vbi_line - used to decode_vbi_line
 *
 * @is_second_field: Set to 0 क्रम the first (odd) field;
 *	set to 1 क्रम the second (even) field.
 * @p: Poपूर्णांकer to the sliced VBI data from the decoder. On निकास, poपूर्णांकs to
 *	the start of the payload.
 * @line: Line number of the sliced VBI data (1-23)
 * @type: VBI service type (V4L2_SLICED_*). 0 अगर no service found
 */
काष्ठा v4l2_decode_vbi_line अणु
	u32 is_second_field;
	u8 *p;
	u32 line;
	u32 type;
पूर्ण;

/*
 * Sub-devices are devices that are connected somehow to the मुख्य bridge
 * device. These devices are usually audio/video muxers/encoders/decoders or
 * sensors and webcam controllers.
 *
 * Usually these devices are controlled through an i2c bus, but other buses
 * may also be used.
 *
 * The v4l2_subdev काष्ठा provides a way of accessing these devices in a
 * generic manner. Most operations that these sub-devices support fall in
 * a few categories: core ops, audio ops, video ops and tuner ops.
 *
 * More categories can be added अगर needed, although this should reमुख्य a
 * limited set (no more than approx. 8 categories).
 *
 * Each category has its own set of ops that subdev drivers can implement.
 *
 * A subdev driver can leave the poपूर्णांकer to the category ops शून्य अगर
 * it करोes not implement them (e.g. an audio subdev will generally not
 * implement the video category ops). The exception is the core category:
 * this must always be present.
 *
 * These ops are all used पूर्णांकernally so it is no problem to change, हटाओ
 * or add ops or move ops from one to another category. Currently these
 * ops are based on the original ioctls, but since ops are not limited to
 * one argument there is room क्रम improvement here once all i2c subdev
 * drivers are converted to use these ops.
 */

/*
 * Core ops: it is highly recommended to implement at least these ops:
 *
 * log_status
 * g_रेजिस्टर
 * s_रेजिस्टर
 *
 * This provides basic debugging support.
 *
 * The ioctl ops is meant क्रम generic ioctl-like commands. Depending on
 * the use-हाल it might be better to use subdev-specअगरic ops (currently
 * not yet implemented) since ops provide proper type-checking.
 */

/**
 * क्रमागत v4l2_subdev_io_pin_bits - Subdevice बाह्यal IO pin configuration
 *	bits
 *
 * @V4L2_SUBDEV_IO_PIN_DISABLE: disables a pin config. ENABLE assumed.
 * @V4L2_SUBDEV_IO_PIN_OUTPUT: set it अगर pin is an output.
 * @V4L2_SUBDEV_IO_PIN_INPUT: set it अगर pin is an input.
 * @V4L2_SUBDEV_IO_PIN_SET_VALUE: to set the output value via
 *				  &काष्ठा v4l2_subdev_io_pin_config->value.
 * @V4L2_SUBDEV_IO_PIN_ACTIVE_LOW: pin active is bit 0.
 *				   Otherwise, ACTIVE HIGH is assumed.
 */
क्रमागत v4l2_subdev_io_pin_bits अणु
	V4L2_SUBDEV_IO_PIN_DISABLE	= 0,
	V4L2_SUBDEV_IO_PIN_OUTPUT	= 1,
	V4L2_SUBDEV_IO_PIN_INPUT	= 2,
	V4L2_SUBDEV_IO_PIN_SET_VALUE	= 3,
	V4L2_SUBDEV_IO_PIN_ACTIVE_LOW	= 4,
पूर्ण;

/**
 * काष्ठा v4l2_subdev_io_pin_config - Subdevice बाह्यal IO pin configuration
 *
 * @flags: biपंचांगask with flags क्रम this pin's config, whose bits are defined by
 *	   &क्रमागत v4l2_subdev_io_pin_bits.
 * @pin: Chip बाह्यal IO pin to configure
 * @function: Internal संकेत pad/function to route to IO pin
 * @value: Initial value क्रम pin - e.g. GPIO output value
 * @strength: Pin drive strength
 */
काष्ठा v4l2_subdev_io_pin_config अणु
	u32 flags;
	u8 pin;
	u8 function;
	u8 value;
	u8 strength;
पूर्ण;

/**
 * काष्ठा v4l2_subdev_core_ops - Define core ops callbacks क्रम subdevs
 *
 * @log_status: callback क्रम VIDIOC_LOG_STATUS() ioctl handler code.
 *
 * @s_io_pin_config: configure one or more chip I/O pins क्रम chips that
 *	multiplex dअगरferent पूर्णांकernal संकेत pads out to IO pins.  This function
 *	takes a poपूर्णांकer to an array of 'n' pin configuration entries, one क्रम
 *	each pin being configured.  This function could be called at बार
 *	other than just subdevice initialization.
 *
 * @init: initialize the sensor रेजिस्टरs to some sort of reasonable शेष
 *	values. Do not use क्रम new drivers and should be हटाओd in existing
 *	drivers.
 *
 * @load_fw: load firmware.
 *
 * @reset: generic reset command. The argument selects which subप्रणालीs to
 *	reset. Passing 0 will always reset the whole chip. Do not use क्रम new
 *	drivers without discussing this first on the linux-media mailinglist.
 *	There should be no reason normally to reset a device.
 *
 * @s_gpio: set GPIO pins. Very simple right now, might need to be extended with
 *	a direction argument अगर needed.
 *
 * @ioctl: called at the end of ioctl() syscall handler at the V4L2 core.
 *	   used to provide support क्रम निजी ioctls used on the driver.
 *
 * @compat_ioctl32: called when a 32 bits application uses a 64 bits Kernel,
 *		    in order to fix data passed from/to userspace.
 *
 * @g_रेजिस्टर: callback क्रम VIDIOC_DBG_G_REGISTER() ioctl handler code.
 *
 * @s_रेजिस्टर: callback क्रम VIDIOC_DBG_S_REGISTER() ioctl handler code.
 *
 * @s_घातer: माला_दो subdevice in घातer saving mode (on == 0) or normal operation
 *	mode (on == 1).
 *
 * @पूर्णांकerrupt_service_routine: Called by the bridge chip's पूर्णांकerrupt service
 *	handler, when an पूर्णांकerrupt status has be उठाओd due to this subdev,
 *	so that this subdev can handle the details.  It may schedule work to be
 *	perक्रमmed later.  It must not sleep. **Called from an IRQ context**.
 *
 * @subscribe_event: used by the drivers to request the control framework that
 *		     क्रम it to be warned when the value of a control changes.
 *
 * @unsubscribe_event: हटाओ event subscription from the control framework.
 */
काष्ठा v4l2_subdev_core_ops अणु
	पूर्णांक (*log_status)(काष्ठा v4l2_subdev *sd);
	पूर्णांक (*s_io_pin_config)(काष्ठा v4l2_subdev *sd, माप_प्रकार n,
				      काष्ठा v4l2_subdev_io_pin_config *pincfg);
	पूर्णांक (*init)(काष्ठा v4l2_subdev *sd, u32 val);
	पूर्णांक (*load_fw)(काष्ठा v4l2_subdev *sd);
	पूर्णांक (*reset)(काष्ठा v4l2_subdev *sd, u32 val);
	पूर्णांक (*s_gpio)(काष्ठा v4l2_subdev *sd, u32 val);
	दीर्घ (*ioctl)(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg);
#अगर_घोषित CONFIG_COMPAT
	दीर्घ (*compat_ioctl32)(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg);
#पूर्ण_अगर
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	पूर्णांक (*g_रेजिस्टर)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_dbg_रेजिस्टर *reg);
	पूर्णांक (*s_रेजिस्टर)(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg);
#पूर्ण_अगर
	पूर्णांक (*s_घातer)(काष्ठा v4l2_subdev *sd, पूर्णांक on);
	पूर्णांक (*पूर्णांकerrupt_service_routine)(काष्ठा v4l2_subdev *sd,
						u32 status, bool *handled);
	पूर्णांक (*subscribe_event)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
			       काष्ठा v4l2_event_subscription *sub);
	पूर्णांक (*unsubscribe_event)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
				 काष्ठा v4l2_event_subscription *sub);
पूर्ण;

/**
 * काष्ठा v4l2_subdev_tuner_ops - Callbacks used when v4l device was खोलोed
 *	in radio mode.
 *
 * @standby: माला_दो the tuner in standby mode. It will be woken up
 *	     स्वतःmatically the next समय it is used.
 *
 * @s_radio: callback that चयनes the tuner to radio mode.
 *	     drivers should explicitly call it when a tuner ops should
 *	     operate on radio mode, beक्रमe being able to handle it.
 *	     Used on devices that have both AM/FM radio receiver and TV.
 *
 * @s_frequency: callback क्रम VIDIOC_S_FREQUENCY() ioctl handler code.
 *
 * @g_frequency: callback क्रम VIDIOC_G_FREQUENCY() ioctl handler code.
 *		 freq->type must be filled in. Normally करोne by video_ioctl2()
 *		 or the bridge driver.
 *
 * @क्रमागत_freq_bands: callback क्रम VIDIOC_ENUM_FREQ_BANDS() ioctl handler code.
 *
 * @g_tuner: callback क्रम VIDIOC_G_TUNER() ioctl handler code.
 *
 * @s_tuner: callback क्रम VIDIOC_S_TUNER() ioctl handler code. @vt->type must be
 *	     filled in. Normally करोne by video_ioctl2 or the
 *	     bridge driver.
 *
 * @g_modulator: callback क्रम VIDIOC_G_MODULATOR() ioctl handler code.
 *
 * @s_modulator: callback क्रम VIDIOC_S_MODULATOR() ioctl handler code.
 *
 * @s_type_addr: sets tuner type and its I2C addr.
 *
 * @s_config: sets tda9887 specअगरic stuff, like port1, port2 and qss
 *
 * .. note::
 *
 *	On devices that have both AM/FM and TV, it is up to the driver
 *	to explicitly call s_radio when the tuner should be चयनed to
 *	radio mode, beक्रमe handling other &काष्ठा v4l2_subdev_tuner_ops
 *	that would require it. An example of such usage is::
 *
 *	  अटल व्योम s_frequency(व्योम *priv, स्थिर काष्ठा v4l2_frequency *f)
 *	  अणु
 *		...
 *		अगर (f.type == V4L2_TUNER_RADIO)
 *			v4l2_device_call_all(v4l2_dev, 0, tuner, s_radio);
 *		...
 *		v4l2_device_call_all(v4l2_dev, 0, tuner, s_frequency);
 *	  पूर्ण
 */
काष्ठा v4l2_subdev_tuner_ops अणु
	पूर्णांक (*standby)(काष्ठा v4l2_subdev *sd);
	पूर्णांक (*s_radio)(काष्ठा v4l2_subdev *sd);
	पूर्णांक (*s_frequency)(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_frequency *freq);
	पूर्णांक (*g_frequency)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_frequency *freq);
	पूर्णांक (*क्रमागत_freq_bands)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_frequency_band *band);
	पूर्णांक (*g_tuner)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt);
	पूर्णांक (*s_tuner)(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt);
	पूर्णांक (*g_modulator)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_modulator *vm);
	पूर्णांक (*s_modulator)(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_modulator *vm);
	पूर्णांक (*s_type_addr)(काष्ठा v4l2_subdev *sd, काष्ठा tuner_setup *type);
	पूर्णांक (*s_config)(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_priv_tun_config *config);
पूर्ण;

/**
 * काष्ठा v4l2_subdev_audio_ops - Callbacks used क्रम audio-related settings
 *
 * @s_घड़ी_freq: set the frequency (in Hz) of the audio घड़ी output.
 *	Used to slave an audio processor to the video decoder, ensuring that
 *	audio and video reमुख्य synchronized. Usual values क्रम the frequency
 *	are 48000, 44100 or 32000 Hz. If the frequency is not supported, then
 *	-EINVAL is वापसed.
 *
 * @s_i2s_घड़ी_freq: sets I2S speed in bps. This is used to provide a standard
 *	way to select I2S घड़ी used by driving digital audio streams at some
 *	board designs. Usual values क्रम the frequency are 1024000 and 2048000.
 *	If the frequency is not supported, then %-EINVAL is वापसed.
 *
 * @s_routing: used to define the input and/or output pins of an audio chip,
 *	and any additional configuration data.
 *	Never attempt to use user-level input IDs (e.g. Composite, S-Video,
 *	Tuner) at this level. An i2c device shouldn't know about whether an
 *	input pin is connected to a Composite connector, become on another
 *	board or platक्रमm it might be connected to something अन्यथा entirely.
 *	The calling driver is responsible क्रम mapping a user-level input to
 *	the right pins on the i2c device.
 *
 * @s_stream: used to notअगरy the audio code that stream will start or has
 *	stopped.
 */
काष्ठा v4l2_subdev_audio_ops अणु
	पूर्णांक (*s_घड़ी_freq)(काष्ठा v4l2_subdev *sd, u32 freq);
	पूर्णांक (*s_i2s_घड़ी_freq)(काष्ठा v4l2_subdev *sd, u32 freq);
	पूर्णांक (*s_routing)(काष्ठा v4l2_subdev *sd, u32 input, u32 output, u32 config);
	पूर्णांक (*s_stream)(काष्ठा v4l2_subdev *sd, पूर्णांक enable);
पूर्ण;

/**
 * क्रमागत v4l2_mbus_frame_desc_flags - media bus frame description flags
 *
 * @V4L2_MBUS_FRAME_DESC_FL_LEN_MAX:
 *	Indicates that &काष्ठा v4l2_mbus_frame_desc_entry->length field
 *	specअगरies maximum data length.
 * @V4L2_MBUS_FRAME_DESC_FL_BLOB:
 *	Indicates that the क्रमmat करोes not have line offsets, i.e.
 *	the receiver should use 1D DMA.
 */
क्रमागत v4l2_mbus_frame_desc_flags अणु
	V4L2_MBUS_FRAME_DESC_FL_LEN_MAX	= BIT(0),
	V4L2_MBUS_FRAME_DESC_FL_BLOB	= BIT(1),
पूर्ण;

/**
 * काष्ठा v4l2_mbus_frame_desc_entry - media bus frame description काष्ठाure
 *
 * @flags:	biपंचांगask flags, as defined by &क्रमागत v4l2_mbus_frame_desc_flags.
 * @pixelcode:	media bus pixel code, valid अगर @flags
 *		%FRAME_DESC_FL_BLOB is not set.
 * @length:	number of octets per frame, valid अगर @flags
 *		%V4L2_MBUS_FRAME_DESC_FL_LEN_MAX is set.
 */
काष्ठा v4l2_mbus_frame_desc_entry अणु
	क्रमागत v4l2_mbus_frame_desc_flags flags;
	u32 pixelcode;
	u32 length;
पूर्ण;

#घोषणा V4L2_FRAME_DESC_ENTRY_MAX	4

/**
 * काष्ठा v4l2_mbus_frame_desc - media bus data frame description
 * @entry: frame descriptors array
 * @num_entries: number of entries in @entry array
 */
काष्ठा v4l2_mbus_frame_desc अणु
	काष्ठा v4l2_mbus_frame_desc_entry entry[V4L2_FRAME_DESC_ENTRY_MAX];
	अचिन्हित लघु num_entries;
पूर्ण;

/**
 * काष्ठा v4l2_subdev_video_ops - Callbacks used when v4l device was खोलोed
 *				  in video mode.
 *
 * @s_routing: see s_routing in audio_ops, except this version is क्रम video
 *	devices.
 *
 * @s_crystal_freq: sets the frequency of the crystal used to generate the
 *	घड़ीs in Hz. An extra flags field allows device specअगरic configuration
 *	regarding घड़ी frequency भागiders, etc. If not used, then set flags
 *	to 0. If the frequency is not supported, then -EINVAL is वापसed.
 *
 * @g_std: callback क्रम VIDIOC_G_STD() ioctl handler code.
 *
 * @s_std: callback क्रम VIDIOC_S_STD() ioctl handler code.
 *
 * @s_std_output: set v4l2_std_id क्रम video OUTPUT devices. This is ignored by
 *	video input devices.
 *
 * @g_std_output: get current standard क्रम video OUTPUT devices. This is ignored
 *	by video input devices.
 *
 * @querystd: callback क्रम VIDIOC_QUERYSTD() ioctl handler code.
 *
 * @g_tvnorms: get &v4l2_std_id with all standards supported by the video
 *	CAPTURE device. This is ignored by video output devices.
 *
 * @g_tvnorms_output: get v4l2_std_id with all standards supported by the video
 *	OUTPUT device. This is ignored by video capture devices.
 *
 * @g_input_status: get input status. Same as the status field in the
 *	&काष्ठा v4l2_input
 *
 * @s_stream: used to notअगरy the driver that a video stream will start or has
 *	stopped.
 *
 * @g_pixelaspect: callback to वापस the pixelaspect ratio.
 *
 * @g_frame_पूर्णांकerval: callback क्रम VIDIOC_SUBDEV_G_FRAME_INTERVAL()
 *		      ioctl handler code.
 *
 * @s_frame_पूर्णांकerval: callback क्रम VIDIOC_SUBDEV_S_FRAME_INTERVAL()
 *		      ioctl handler code.
 *
 * @s_dv_timings: Set custom dv timings in the sub device. This is used
 *	when sub device is capable of setting detailed timing inक्रमmation
 *	in the hardware to generate/detect the video संकेत.
 *
 * @g_dv_timings: Get custom dv timings in the sub device.
 *
 * @query_dv_timings: callback क्रम VIDIOC_QUERY_DV_TIMINGS() ioctl handler code.
 *
 * @s_rx_buffer: set a host allocated memory buffer क्रम the subdev. The subdev
 *	can adjust @size to a lower value and must not ग_लिखो more data to the
 *	buffer starting at @data than the original value of @size.
 */
काष्ठा v4l2_subdev_video_ops अणु
	पूर्णांक (*s_routing)(काष्ठा v4l2_subdev *sd, u32 input, u32 output, u32 config);
	पूर्णांक (*s_crystal_freq)(काष्ठा v4l2_subdev *sd, u32 freq, u32 flags);
	पूर्णांक (*g_std)(काष्ठा v4l2_subdev *sd, v4l2_std_id *norm);
	पूर्णांक (*s_std)(काष्ठा v4l2_subdev *sd, v4l2_std_id norm);
	पूर्णांक (*s_std_output)(काष्ठा v4l2_subdev *sd, v4l2_std_id std);
	पूर्णांक (*g_std_output)(काष्ठा v4l2_subdev *sd, v4l2_std_id *std);
	पूर्णांक (*querystd)(काष्ठा v4l2_subdev *sd, v4l2_std_id *std);
	पूर्णांक (*g_tvnorms)(काष्ठा v4l2_subdev *sd, v4l2_std_id *std);
	पूर्णांक (*g_tvnorms_output)(काष्ठा v4l2_subdev *sd, v4l2_std_id *std);
	पूर्णांक (*g_input_status)(काष्ठा v4l2_subdev *sd, u32 *status);
	पूर्णांक (*s_stream)(काष्ठा v4l2_subdev *sd, पूर्णांक enable);
	पूर्णांक (*g_pixelaspect)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fract *aspect);
	पूर्णांक (*g_frame_पूर्णांकerval)(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval);
	पूर्णांक (*s_frame_पूर्णांकerval)(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_frame_पूर्णांकerval *पूर्णांकerval);
	पूर्णांक (*s_dv_timings)(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_dv_timings *timings);
	पूर्णांक (*g_dv_timings)(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_dv_timings *timings);
	पूर्णांक (*query_dv_timings)(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_dv_timings *timings);
	पूर्णांक (*s_rx_buffer)(काष्ठा v4l2_subdev *sd, व्योम *buf,
			   अचिन्हित पूर्णांक *size);
पूर्ण;

/**
 * काष्ठा v4l2_subdev_vbi_ops - Callbacks used when v4l device was खोलोed
 *				  in video mode via the vbi device node.
 *
 *  @decode_vbi_line: video decoders that support sliced VBI need to implement
 *	this ioctl. Field p of the &काष्ठा v4l2_decode_vbi_line is set to the
 *	start of the VBI data that was generated by the decoder. The driver
 *	then parses the sliced VBI data and sets the other fields in the
 *	काष्ठा accordingly. The poपूर्णांकer p is updated to poपूर्णांक to the start of
 *	the payload which can be copied verbatim पूर्णांकo the data field of the
 *	&काष्ठा v4l2_sliced_vbi_data. If no valid VBI data was found, then the
 *	type field is set to 0 on वापस.
 *
 * @s_vbi_data: used to generate VBI संकेतs on a video संकेत.
 *	&काष्ठा v4l2_sliced_vbi_data is filled with the data packets that
 *	should be output. Note that अगर you set the line field to 0, then that
 *	VBI संकेत is disabled. If no valid VBI data was found, then the type
 *	field is set to 0 on वापस.
 *
 * @g_vbi_data: used to obtain the sliced VBI packet from a पढ़ोback रेजिस्टर.
 *	Not all video decoders support this. If no data is available because
 *	the पढ़ोback रेजिस्टर contains invalid or erroneous data %-EIO is
 *	वापसed. Note that you must fill in the 'id' member and the 'field'
 *	member (to determine whether CC data from the first or second field
 *	should be obtained).
 *
 * @g_sliced_vbi_cap: callback क्रम VIDIOC_G_SLICED_VBI_CAP() ioctl handler
 *		      code.
 *
 * @s_raw_fmt: setup the video encoder/decoder क्रम raw VBI.
 *
 * @g_sliced_fmt: retrieve the current sliced VBI settings.
 *
 * @s_sliced_fmt: setup the sliced VBI settings.
 */
काष्ठा v4l2_subdev_vbi_ops अणु
	पूर्णांक (*decode_vbi_line)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_decode_vbi_line *vbi_line);
	पूर्णांक (*s_vbi_data)(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_sliced_vbi_data *vbi_data);
	पूर्णांक (*g_vbi_data)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_data *vbi_data);
	पूर्णांक (*g_sliced_vbi_cap)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_cap *cap);
	पूर्णांक (*s_raw_fmt)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_vbi_क्रमmat *fmt);
	पूर्णांक (*g_sliced_fmt)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *fmt);
	पूर्णांक (*s_sliced_fmt)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *fmt);
पूर्ण;

/**
 * काष्ठा v4l2_subdev_sensor_ops - v4l2-subdev sensor operations
 * @g_skip_top_lines: number of lines at the top of the image to be skipped.
 *		      This is needed क्रम some sensors, which always corrupt
 *		      several top lines of the output image, or which send their
 *		      metadata in them.
 * @g_skip_frames: number of frames to skip at stream start. This is needed क्रम
 *		   buggy sensors that generate faulty frames when they are
 *		   turned on.
 */
काष्ठा v4l2_subdev_sensor_ops अणु
	पूर्णांक (*g_skip_top_lines)(काष्ठा v4l2_subdev *sd, u32 *lines);
	पूर्णांक (*g_skip_frames)(काष्ठा v4l2_subdev *sd, u32 *frames);
पूर्ण;

/**
 * क्रमागत v4l2_subdev_ir_mode- describes the type of IR supported
 *
 * @V4L2_SUBDEV_IR_MODE_PULSE_WIDTH: IR uses काष्ठा ir_raw_event records
 */
क्रमागत v4l2_subdev_ir_mode अणु
	V4L2_SUBDEV_IR_MODE_PULSE_WIDTH,
पूर्ण;

/**
 * काष्ठा v4l2_subdev_ir_parameters - Parameters क्रम IR TX or TX
 *
 * @bytes_per_data_element: bytes per data element of data in पढ़ो or
 *	ग_लिखो call.
 * @mode: IR mode as defined by &क्रमागत v4l2_subdev_ir_mode.
 * @enable: device is active अगर true
 * @पूर्णांकerrupt_enable: IR पूर्णांकerrupts are enabled अगर true
 * @shutकरोwn: अगर true: set hardware to low/no घातer, false: normal mode
 *
 * @modulation: अगर true, it uses carrier, अगर false: baseband
 * @max_pulse_width:  maximum pulse width in ns, valid only क्रम baseband संकेत
 * @carrier_freq: carrier frequency in Hz, valid only क्रम modulated संकेत
 * @duty_cycle: duty cycle percentage, valid only क्रम modulated संकेत
 * @invert_level: invert संकेत level
 *
 * @invert_carrier_sense: Send 0/space as a carrier burst. used only in TX.
 *
 * @noise_filter_min_width: min समय of a valid pulse, in ns. Used only क्रम RX.
 * @carrier_range_lower: Lower carrier range, in Hz, valid only क्रम modulated
 *	संकेत. Used only क्रम RX.
 * @carrier_range_upper: Upper carrier range, in Hz, valid only क्रम modulated
 *	संकेत. Used only क्रम RX.
 * @resolution: The receive resolution, in ns . Used only क्रम RX.
 */
काष्ठा v4l2_subdev_ir_parameters अणु
	अचिन्हित पूर्णांक bytes_per_data_element;
	क्रमागत v4l2_subdev_ir_mode mode;

	bool enable;
	bool पूर्णांकerrupt_enable;
	bool shutकरोwn;

	bool modulation;
	u32 max_pulse_width;
	अचिन्हित पूर्णांक carrier_freq;
	अचिन्हित पूर्णांक duty_cycle;
	bool invert_level;

	/* Tx only */
	bool invert_carrier_sense;

	/* Rx only */
	u32 noise_filter_min_width;
	अचिन्हित पूर्णांक carrier_range_lower;
	अचिन्हित पूर्णांक carrier_range_upper;
	u32 resolution;
पूर्ण;

/**
 * काष्ठा v4l2_subdev_ir_ops - operations क्रम IR subdevices
 *
 * @rx_पढ़ो: Reads received codes or pulse width data.
 *	The semantics are similar to a non-blocking पढ़ो() call.
 * @rx_g_parameters: Get the current operating parameters and state of
 *	the IR receiver.
 * @rx_s_parameters: Set the current operating parameters and state of
 *	the IR receiver.  It is recommended to call
 *	[rt]x_g_parameters first to fill out the current state, and only change
 *	the fields that need to be changed.  Upon वापस, the actual device
 *	operating parameters and state will be वापसed.  Note that hardware
 *	limitations may prevent the actual settings from matching the requested
 *	settings - e.g. an actual carrier setting of 35,904 Hz when 36,000 Hz
 *	was requested.  An exception is when the shutकरोwn parameter is true.
 *	The last used operational parameters will be वापसed, but the actual
 *	state of the hardware be dअगरferent to minimize घातer consumption and
 *	processing when shutकरोwn is true.
 *
 * @tx_ग_लिखो: Writes codes or pulse width data क्रम transmission.
 *	The semantics are similar to a non-blocking ग_लिखो() call.
 * @tx_g_parameters: Get the current operating parameters and state of
 *	the IR transmitter.
 * @tx_s_parameters: Set the current operating parameters and state of
 *	the IR transmitter.  It is recommended to call
 *	[rt]x_g_parameters first to fill out the current state, and only change
 *	the fields that need to be changed.  Upon वापस, the actual device
 *	operating parameters and state will be वापसed.  Note that hardware
 *	limitations may prevent the actual settings from matching the requested
 *	settings - e.g. an actual carrier setting of 35,904 Hz when 36,000 Hz
 *	was requested.  An exception is when the shutकरोwn parameter is true.
 *	The last used operational parameters will be वापसed, but the actual
 *	state of the hardware be dअगरferent to minimize घातer consumption and
 *	processing when shutकरोwn is true.
 */
काष्ठा v4l2_subdev_ir_ops अणु
	/* Receiver */
	पूर्णांक (*rx_पढ़ो)(काष्ठा v4l2_subdev *sd, u8 *buf, माप_प्रकार count,
				sमाप_प्रकार *num);

	पूर्णांक (*rx_g_parameters)(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_ir_parameters *params);
	पूर्णांक (*rx_s_parameters)(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_ir_parameters *params);

	/* Transmitter */
	पूर्णांक (*tx_ग_लिखो)(काष्ठा v4l2_subdev *sd, u8 *buf, माप_प्रकार count,
				sमाप_प्रकार *num);

	पूर्णांक (*tx_g_parameters)(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_ir_parameters *params);
	पूर्णांक (*tx_s_parameters)(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_ir_parameters *params);
पूर्ण;

/**
 * काष्ठा v4l2_subdev_pad_config - Used क्रम storing subdev pad inक्रमmation.
 *
 * @try_fmt: &काष्ठा v4l2_mbus_framefmt
 * @try_crop: &काष्ठा v4l2_rect to be used क्रम crop
 * @try_compose: &काष्ठा v4l2_rect to be used क्रम compose
 *
 * This काष्ठाure only needs to be passed to the pad op अगर the 'which' field
 * of the मुख्य argument is set to %V4L2_SUBDEV_FORMAT_TRY. For
 * %V4L2_SUBDEV_FORMAT_ACTIVE it is safe to pass %शून्य.
 */
काष्ठा v4l2_subdev_pad_config अणु
	काष्ठा v4l2_mbus_framefmt try_fmt;
	काष्ठा v4l2_rect try_crop;
	काष्ठा v4l2_rect try_compose;
पूर्ण;

/**
 * काष्ठा v4l2_subdev_pad_ops - v4l2-subdev pad level operations
 *
 * @init_cfg: initialize the pad config to शेष values
 * @क्रमागत_mbus_code: callback क्रम VIDIOC_SUBDEV_ENUM_MBUS_CODE() ioctl handler
 *		    code.
 * @क्रमागत_frame_size: callback क्रम VIDIOC_SUBDEV_ENUM_FRAME_SIZE() ioctl handler
 *		     code.
 *
 * @क्रमागत_frame_पूर्णांकerval: callback क्रम VIDIOC_SUBDEV_ENUM_FRAME_INTERVAL() ioctl
 *			 handler code.
 *
 * @get_fmt: callback क्रम VIDIOC_SUBDEV_G_FMT() ioctl handler code.
 *
 * @set_fmt: callback क्रम VIDIOC_SUBDEV_S_FMT() ioctl handler code.
 *
 * @get_selection: callback क्रम VIDIOC_SUBDEV_G_SELECTION() ioctl handler code.
 *
 * @set_selection: callback क्रम VIDIOC_SUBDEV_S_SELECTION() ioctl handler code.
 *
 * @get_edid: callback क्रम VIDIOC_SUBDEV_G_EDID() ioctl handler code.
 *
 * @set_edid: callback क्रम VIDIOC_SUBDEV_S_EDID() ioctl handler code.
 *
 * @dv_timings_cap: callback क्रम VIDIOC_SUBDEV_DV_TIMINGS_CAP() ioctl handler
 *		    code.
 *
 * @क्रमागत_dv_timings: callback क्रम VIDIOC_SUBDEV_ENUM_DV_TIMINGS() ioctl handler
 *		     code.
 *
 * @link_validate: used by the media controller code to check अगर the links
 *		   that beदीर्घs to a pipeline can be used क्रम stream.
 *
 * @get_frame_desc: get the current low level media bus frame parameters.
 *
 * @set_frame_desc: set the low level media bus frame parameters, @fd array
 *                  may be adjusted by the subdev driver to device capabilities.
 *
 * @get_mbus_config: get the media bus configuration of a remote sub-device.
 *		     The media bus configuration is usually retrieved from the
 *		     firmware पूर्णांकerface at sub-device probe समय, immediately
 *		     applied to the hardware and eventually adjusted by the
 *		     driver. Remote sub-devices (usually video receivers) shall
 *		     use this operation to query the transmitting end bus
 *		     configuration in order to adjust their own one accordingly.
 *		     Callers should make sure they get the most up-to-date as
 *		     possible configuration from the remote end, likely calling
 *		     this operation as बंद as possible to stream on समय. The
 *		     operation shall fail अगर the pad index it has been called on
 *		     is not valid or in हाल of unrecoverable failures.
 *
 * @set_mbus_config: set the media bus configuration of a remote sub-device.
 *		     This operations is पूर्णांकended to allow, in combination with
 *		     the get_mbus_config operation, the negotiation of media bus
 *		     configuration parameters between media sub-devices. The
 *		     operation shall not fail अगर the requested configuration is
 *		     not supported, but the driver shall update the content of
 *		     the %config argument to reflect what has been actually
 *		     applied to the hardware. The operation shall fail अगर the
 *		     pad index it has been called on is not valid or in हाल of
 *		     unrecoverable failures.
 */
काष्ठा v4l2_subdev_pad_ops अणु
	पूर्णांक (*init_cfg)(काष्ठा v4l2_subdev *sd,
			काष्ठा v4l2_subdev_pad_config *cfg);
	पूर्णांक (*क्रमागत_mbus_code)(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_subdev_pad_config *cfg,
			      काष्ठा v4l2_subdev_mbus_code_क्रमागत *code);
	पूर्णांक (*क्रमागत_frame_size)(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_frame_size_क्रमागत *fse);
	पूर्णांक (*क्रमागत_frame_पूर्णांकerval)(काष्ठा v4l2_subdev *sd,
				   काष्ठा v4l2_subdev_pad_config *cfg,
				   काष्ठा v4l2_subdev_frame_पूर्णांकerval_क्रमागत *fie);
	पूर्णांक (*get_fmt)(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *क्रमmat);
	पूर्णांक (*set_fmt)(काष्ठा v4l2_subdev *sd,
		       काष्ठा v4l2_subdev_pad_config *cfg,
		       काष्ठा v4l2_subdev_क्रमmat *क्रमmat);
	पूर्णांक (*get_selection)(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel);
	पूर्णांक (*set_selection)(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg,
			     काष्ठा v4l2_subdev_selection *sel);
	पूर्णांक (*get_edid)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid);
	पूर्णांक (*set_edid)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid);
	पूर्णांक (*dv_timings_cap)(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dv_timings_cap *cap);
	पूर्णांक (*क्रमागत_dv_timings)(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_क्रमागत_dv_timings *timings);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	पूर्णांक (*link_validate)(काष्ठा v4l2_subdev *sd, काष्ठा media_link *link,
			     काष्ठा v4l2_subdev_क्रमmat *source_fmt,
			     काष्ठा v4l2_subdev_क्रमmat *sink_fmt);
#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER */
	पूर्णांक (*get_frame_desc)(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
			      काष्ठा v4l2_mbus_frame_desc *fd);
	पूर्णांक (*set_frame_desc)(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
			      काष्ठा v4l2_mbus_frame_desc *fd);
	पूर्णांक (*get_mbus_config)(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
			       काष्ठा v4l2_mbus_config *config);
	पूर्णांक (*set_mbus_config)(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक pad,
			       काष्ठा v4l2_mbus_config *config);
पूर्ण;

/**
 * काष्ठा v4l2_subdev_ops - Subdev operations
 *
 * @core: poपूर्णांकer to &काष्ठा v4l2_subdev_core_ops. Can be %शून्य
 * @tuner: poपूर्णांकer to &काष्ठा v4l2_subdev_tuner_ops. Can be %शून्य
 * @audio: poपूर्णांकer to &काष्ठा v4l2_subdev_audio_ops. Can be %शून्य
 * @video: poपूर्णांकer to &काष्ठा v4l2_subdev_video_ops. Can be %शून्य
 * @vbi: poपूर्णांकer to &काष्ठा v4l2_subdev_vbi_ops. Can be %शून्य
 * @ir: poपूर्णांकer to &काष्ठा v4l2_subdev_ir_ops. Can be %शून्य
 * @sensor: poपूर्णांकer to &काष्ठा v4l2_subdev_sensor_ops. Can be %शून्य
 * @pad: poपूर्णांकer to &काष्ठा v4l2_subdev_pad_ops. Can be %शून्य
 */
काष्ठा v4l2_subdev_ops अणु
	स्थिर काष्ठा v4l2_subdev_core_ops	*core;
	स्थिर काष्ठा v4l2_subdev_tuner_ops	*tuner;
	स्थिर काष्ठा v4l2_subdev_audio_ops	*audio;
	स्थिर काष्ठा v4l2_subdev_video_ops	*video;
	स्थिर काष्ठा v4l2_subdev_vbi_ops	*vbi;
	स्थिर काष्ठा v4l2_subdev_ir_ops		*ir;
	स्थिर काष्ठा v4l2_subdev_sensor_ops	*sensor;
	स्थिर काष्ठा v4l2_subdev_pad_ops	*pad;
पूर्ण;

/**
 * काष्ठा v4l2_subdev_पूर्णांकernal_ops - V4L2 subdev पूर्णांकernal ops
 *
 * @रेजिस्टरed: called when this subdev is रेजिस्टरed. When called the v4l2_dev
 *	field is set to the correct v4l2_device.
 *
 * @unरेजिस्टरed: called when this subdev is unरेजिस्टरed. When called the
 *	v4l2_dev field is still set to the correct v4l2_device.
 *
 * @खोलो: called when the subdev device node is खोलोed by an application.
 *
 * @बंद: called when the subdev device node is बंदd. Please note that
 *	it is possible क्रम @बंद to be called after @unरेजिस्टरed!
 *
 * @release: called when the last user of the subdev device is gone. This
 *	happens after the @unरेजिस्टरed callback and when the last खोलो
 *	filehandle to the v4l-subdevX device node was बंदd. If no device
 *	node was created क्रम this sub-device, then the @release callback
 *	is called right after the @unरेजिस्टरed callback.
 *	The @release callback is typically used to मुक्त the memory containing
 *	the v4l2_subdev काष्ठाure. It is almost certainly required क्रम any
 *	sub-device that sets the V4L2_SUBDEV_FL_HAS_DEVNODE flag.
 *
 * .. note::
 *	Never call this from drivers, only the v4l2 framework can call
 *	these ops.
 */
काष्ठा v4l2_subdev_पूर्णांकernal_ops अणु
	पूर्णांक (*रेजिस्टरed)(काष्ठा v4l2_subdev *sd);
	व्योम (*unरेजिस्टरed)(काष्ठा v4l2_subdev *sd);
	पूर्णांक (*खोलो)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh);
	पूर्णांक (*बंद)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_subdev_fh *fh);
	व्योम (*release)(काष्ठा v4l2_subdev *sd);
पूर्ण;

#घोषणा V4L2_SUBDEV_NAME_SIZE 32

/* Set this flag अगर this subdev is a i2c device. */
#घोषणा V4L2_SUBDEV_FL_IS_I2C			(1U << 0)
/* Set this flag अगर this subdev is a spi device. */
#घोषणा V4L2_SUBDEV_FL_IS_SPI			(1U << 1)
/* Set this flag अगर this subdev needs a device node. */
#घोषणा V4L2_SUBDEV_FL_HAS_DEVNODE		(1U << 2)
/*
 * Set this flag अगर this subdev generates events.
 * Note controls can send events, thus drivers exposing controls
 * should set this flag.
 */
#घोषणा V4L2_SUBDEV_FL_HAS_EVENTS		(1U << 3)

काष्ठा regulator_bulk_data;

/**
 * काष्ठा v4l2_subdev_platक्रमm_data - regulators config काष्ठा
 *
 * @regulators: Optional regulators used to घातer on/off the subdevice
 * @num_regulators: Number of regululators
 * @host_priv: Per-subdevice data, specअगरic क्रम a certain video host device
 */
काष्ठा v4l2_subdev_platक्रमm_data अणु
	काष्ठा regulator_bulk_data *regulators;
	पूर्णांक num_regulators;

	व्योम *host_priv;
पूर्ण;

/**
 * काष्ठा v4l2_subdev - describes a V4L2 sub-device
 *
 * @entity: poपूर्णांकer to &काष्ठा media_entity
 * @list: List of sub-devices
 * @owner: The owner is the same as the driver's &काष्ठा device owner.
 * @owner_v4l2_dev: true अगर the &sd->owner matches the owner of @v4l2_dev->dev
 *	owner. Initialized by v4l2_device_रेजिस्टर_subdev().
 * @flags: subdev flags. Can be:
 *   %V4L2_SUBDEV_FL_IS_I2C - Set this flag अगर this subdev is a i2c device;
 *   %V4L2_SUBDEV_FL_IS_SPI - Set this flag अगर this subdev is a spi device;
 *   %V4L2_SUBDEV_FL_HAS_DEVNODE - Set this flag अगर this subdev needs a
 *   device node;
 *   %V4L2_SUBDEV_FL_HAS_EVENTS -  Set this flag अगर this subdev generates
 *   events.
 *
 * @v4l2_dev: poपूर्णांकer to काष्ठा &v4l2_device
 * @ops: poपूर्णांकer to काष्ठा &v4l2_subdev_ops
 * @पूर्णांकernal_ops: poपूर्णांकer to काष्ठा &v4l2_subdev_पूर्णांकernal_ops.
 *	Never call these पूर्णांकernal ops from within a driver!
 * @ctrl_handler: The control handler of this subdev. May be शून्य.
 * @name: Name of the sub-device. Please notice that the name must be unique.
 * @grp_id: can be used to group similar subdevs. Value is driver-specअगरic
 * @dev_priv: poपूर्णांकer to निजी data
 * @host_priv: poपूर्णांकer to निजी data used by the device where the subdev
 *	is attached.
 * @devnode: subdev device node
 * @dev: poपूर्णांकer to the physical device, अगर any
 * @fwnode: The fwnode_handle of the subdev, usually the same as
 *	    either dev->of_node->fwnode or dev->fwnode (whichever is non-शून्य).
 * @async_list: Links this subdev to a global subdev_list or @notअगरier->करोne
 *	list.
 * @asd: Poपूर्णांकer to respective &काष्ठा v4l2_async_subdev.
 * @notअगरier: Poपूर्णांकer to the managing notअगरier.
 * @subdev_notअगरier: A sub-device notअगरier implicitly रेजिस्टरed क्रम the sub-
 *		     device using v4l2_device_रेजिस्टर_sensor_subdev().
 * @pdata: common part of subdevice platक्रमm data
 *
 * Each instance of a subdev driver should create this काष्ठा, either
 * stand-alone or embedded in a larger काष्ठा.
 *
 * This काष्ठाure should be initialized by v4l2_subdev_init() or one of
 * its variants: v4l2_spi_subdev_init(), v4l2_i2c_subdev_init().
 */
काष्ठा v4l2_subdev अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा media_entity entity;
#पूर्ण_अगर
	काष्ठा list_head list;
	काष्ठा module *owner;
	bool owner_v4l2_dev;
	u32 flags;
	काष्ठा v4l2_device *v4l2_dev;
	स्थिर काष्ठा v4l2_subdev_ops *ops;
	स्थिर काष्ठा v4l2_subdev_पूर्णांकernal_ops *पूर्णांकernal_ops;
	काष्ठा v4l2_ctrl_handler *ctrl_handler;
	अक्षर name[V4L2_SUBDEV_NAME_SIZE];
	u32 grp_id;
	व्योम *dev_priv;
	व्योम *host_priv;
	काष्ठा video_device *devnode;
	काष्ठा device *dev;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा list_head async_list;
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा v4l2_async_notअगरier *notअगरier;
	काष्ठा v4l2_async_notअगरier *subdev_notअगरier;
	काष्ठा v4l2_subdev_platक्रमm_data *pdata;
पूर्ण;


/**
 * media_entity_to_v4l2_subdev - Returns a &काष्ठा v4l2_subdev from
 *    the &काष्ठा media_entity embedded in it.
 *
 * @ent: poपूर्णांकer to &काष्ठा media_entity.
 */
#घोषणा media_entity_to_v4l2_subdev(ent)				\
(अणु									\
	typeof(ent) __me_sd_ent = (ent);				\
									\
	__me_sd_ent ?							\
		container_of(__me_sd_ent, काष्ठा v4l2_subdev, entity) :	\
		शून्य;							\
पूर्ण)

/**
 * vdev_to_v4l2_subdev - Returns a &काष्ठा v4l2_subdev from
 *	the &काष्ठा video_device embedded on it.
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 */
#घोषणा vdev_to_v4l2_subdev(vdev) \
	((काष्ठा v4l2_subdev *)video_get_drvdata(vdev))

/**
 * काष्ठा v4l2_subdev_fh - Used क्रम storing subdev inक्रमmation per file handle
 *
 * @vfh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @pad: poपूर्णांकer to &काष्ठा v4l2_subdev_pad_config
 * @owner: module poपूर्णांकer to the owner of this file handle
 */
काष्ठा v4l2_subdev_fh अणु
	काष्ठा v4l2_fh vfh;
	काष्ठा module *owner;
#अगर defined(CONFIG_VIDEO_V4L2_SUBDEV_API)
	काष्ठा v4l2_subdev_pad_config *pad;
#पूर्ण_अगर
पूर्ण;

/**
 * to_v4l2_subdev_fh - Returns a &काष्ठा v4l2_subdev_fh from
 *	the &काष्ठा v4l2_fh embedded on it.
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 */
#घोषणा to_v4l2_subdev_fh(fh)	\
	container_of(fh, काष्ठा v4l2_subdev_fh, vfh)

#अगर defined(CONFIG_VIDEO_V4L2_SUBDEV_API)

/**
 * v4l2_subdev_get_try_क्रमmat - ancillary routine to call
 *	&काष्ठा v4l2_subdev_pad_config->try_fmt
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @cfg: poपूर्णांकer to &काष्ठा v4l2_subdev_pad_config array.
 * @pad: index of the pad in the @cfg array.
 */
अटल अंतरभूत काष्ठा v4l2_mbus_framefmt *
v4l2_subdev_get_try_क्रमmat(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   अचिन्हित पूर्णांक pad)
अणु
	अगर (WARN_ON(pad >= sd->entity.num_pads))
		pad = 0;
	वापस &cfg[pad].try_fmt;
पूर्ण

/**
 * v4l2_subdev_get_try_crop - ancillary routine to call
 *	&काष्ठा v4l2_subdev_pad_config->try_crop
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @cfg: poपूर्णांकer to &काष्ठा v4l2_subdev_pad_config array.
 * @pad: index of the pad in the @cfg array.
 */
अटल अंतरभूत काष्ठा v4l2_rect *
v4l2_subdev_get_try_crop(काष्ठा v4l2_subdev *sd,
			 काष्ठा v4l2_subdev_pad_config *cfg,
			 अचिन्हित पूर्णांक pad)
अणु
	अगर (WARN_ON(pad >= sd->entity.num_pads))
		pad = 0;
	वापस &cfg[pad].try_crop;
पूर्ण

/**
 * v4l2_subdev_get_try_compose - ancillary routine to call
 *	&काष्ठा v4l2_subdev_pad_config->try_compose
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @cfg: poपूर्णांकer to &काष्ठा v4l2_subdev_pad_config array.
 * @pad: index of the pad in the @cfg array.
 */
अटल अंतरभूत काष्ठा v4l2_rect *
v4l2_subdev_get_try_compose(काष्ठा v4l2_subdev *sd,
			    काष्ठा v4l2_subdev_pad_config *cfg,
			    अचिन्हित पूर्णांक pad)
अणु
	अगर (WARN_ON(pad >= sd->entity.num_pads))
		pad = 0;
	वापस &cfg[pad].try_compose;
पूर्ण

#पूर्ण_अगर

बाह्य स्थिर काष्ठा v4l2_file_operations v4l2_subdev_fops;

/**
 * v4l2_set_subdevdata - Sets V4L2 dev निजी device data
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @p: poपूर्णांकer to the निजी device data to be stored.
 */
अटल अंतरभूत व्योम v4l2_set_subdevdata(काष्ठा v4l2_subdev *sd, व्योम *p)
अणु
	sd->dev_priv = p;
पूर्ण

/**
 * v4l2_get_subdevdata - Gets V4L2 dev निजी device data
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 *
 * Returns the poपूर्णांकer to the निजी device data to be stored.
 */
अटल अंतरभूत व्योम *v4l2_get_subdevdata(स्थिर काष्ठा v4l2_subdev *sd)
अणु
	वापस sd->dev_priv;
पूर्ण

/**
 * v4l2_set_subdev_hostdata - Sets V4L2 dev निजी host data
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @p: poपूर्णांकer to the निजी data to be stored.
 */
अटल अंतरभूत व्योम v4l2_set_subdev_hostdata(काष्ठा v4l2_subdev *sd, व्योम *p)
अणु
	sd->host_priv = p;
पूर्ण

/**
 * v4l2_get_subdev_hostdata - Gets V4L2 dev निजी data
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 *
 * Returns the poपूर्णांकer to the निजी host data to be stored.
 */
अटल अंतरभूत व्योम *v4l2_get_subdev_hostdata(स्थिर काष्ठा v4l2_subdev *sd)
अणु
	वापस sd->host_priv;
पूर्ण

#अगर_घोषित CONFIG_MEDIA_CONTROLLER

/**
 * v4l2_subdev_get_fwnode_pad_1_to_1 - Get pad number from a subdev fwnode
 *                                     endpoपूर्णांक, assuming 1:1 port:pad
 *
 * @entity: Poपूर्णांकer to the subdev entity
 * @endpoपूर्णांक: Poपूर्णांकer to a parsed fwnode endpoपूर्णांक
 *
 * This function can be used as the .get_fwnode_pad operation क्रम
 * subdevices that map port numbers and pad indexes 1:1. If the endpoपूर्णांक
 * is owned by the subdevice, the function वापसs the endpoपूर्णांक port
 * number.
 *
 * Returns the endpoपूर्णांक port number on success or a negative error code.
 */
पूर्णांक v4l2_subdev_get_fwnode_pad_1_to_1(काष्ठा media_entity *entity,
				      काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक);

/**
 * v4l2_subdev_link_validate_शेष - validates a media link
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @link: poपूर्णांकer to &काष्ठा media_link
 * @source_fmt: poपूर्णांकer to &काष्ठा v4l2_subdev_क्रमmat
 * @sink_fmt: poपूर्णांकer to &काष्ठा v4l2_subdev_क्रमmat
 *
 * This function ensures that width, height and the media bus pixel
 * code are equal on both source and sink of the link.
 */
पूर्णांक v4l2_subdev_link_validate_शेष(काष्ठा v4l2_subdev *sd,
				      काष्ठा media_link *link,
				      काष्ठा v4l2_subdev_क्रमmat *source_fmt,
				      काष्ठा v4l2_subdev_क्रमmat *sink_fmt);

/**
 * v4l2_subdev_link_validate - validates a media link
 *
 * @link: poपूर्णांकer to &काष्ठा media_link
 *
 * This function calls the subdev's link_validate ops to validate
 * अगर a media link is valid क्रम streaming. It also पूर्णांकernally
 * calls v4l2_subdev_link_validate_शेष() to ensure that
 * width, height and the media bus pixel code are equal on both
 * source and sink of the link.
 */
पूर्णांक v4l2_subdev_link_validate(काष्ठा media_link *link);

/**
 * v4l2_subdev_alloc_pad_config - Allocates memory क्रम pad config
 *
 * @sd: poपूर्णांकer to काष्ठा v4l2_subdev
 */
काष्ठा
v4l2_subdev_pad_config *v4l2_subdev_alloc_pad_config(काष्ठा v4l2_subdev *sd);

/**
 * v4l2_subdev_मुक्त_pad_config - Frees memory allocated by
 *	v4l2_subdev_alloc_pad_config().
 *
 * @cfg: poपूर्णांकer to &काष्ठा v4l2_subdev_pad_config
 */
व्योम v4l2_subdev_मुक्त_pad_config(काष्ठा v4l2_subdev_pad_config *cfg);
#पूर्ण_अगर /* CONFIG_MEDIA_CONTROLLER */

/**
 * v4l2_subdev_init - initializes the sub-device काष्ठा
 *
 * @sd: poपूर्णांकer to the &काष्ठा v4l2_subdev to be initialized
 * @ops: poपूर्णांकer to &काष्ठा v4l2_subdev_ops.
 */
व्योम v4l2_subdev_init(काष्ठा v4l2_subdev *sd,
		      स्थिर काष्ठा v4l2_subdev_ops *ops);

बाह्य स्थिर काष्ठा v4l2_subdev_ops v4l2_subdev_call_wrappers;

/**
 * v4l2_subdev_call - call an operation of a v4l2_subdev.
 *
 * @sd: poपूर्णांकer to the &काष्ठा v4l2_subdev
 * @o: name of the element at &काष्ठा v4l2_subdev_ops that contains @f.
 *     Each element there groups a set of callbacks functions.
 * @f: callback function to be called.
 *     The callback functions are defined in groups, according to
 *     each element at &काष्ठा v4l2_subdev_ops.
 * @args: arguments क्रम @f.
 *
 * Example: err = v4l2_subdev_call(sd, video, s_std, norm);
 */
#घोषणा v4l2_subdev_call(sd, o, f, args...)				\
	(अणु								\
		काष्ठा v4l2_subdev *__sd = (sd);			\
		पूर्णांक __result;						\
		अगर (!__sd)						\
			__result = -ENODEV;				\
		अन्यथा अगर (!(__sd->ops->o && __sd->ops->o->f))		\
			__result = -ENOIOCTLCMD;			\
		अन्यथा अगर (v4l2_subdev_call_wrappers.o &&			\
			 v4l2_subdev_call_wrappers.o->f)		\
			__result = v4l2_subdev_call_wrappers.o->f(	\
							__sd, ##args);	\
		अन्यथा							\
			__result = __sd->ops->o->f(__sd, ##args);	\
		__result;						\
	पूर्ण)

/**
 * v4l2_subdev_has_op - Checks अगर a subdev defines a certain operation.
 *
 * @sd: poपूर्णांकer to the &काष्ठा v4l2_subdev
 * @o: The group of callback functions in &काष्ठा v4l2_subdev_ops
 * which @f is a part of.
 * @f: callback function to be checked क्रम its existence.
 */
#घोषणा v4l2_subdev_has_op(sd, o, f) \
	((sd)->ops->o && (sd)->ops->o->f)

/**
 * v4l2_subdev_notअगरy_event() - Delivers event notअगरication क्रम subdevice
 * @sd: The subdev क्रम which to deliver the event
 * @ev: The event to deliver
 *
 * Will deliver the specअगरied event to all userspace event listeners which are
 * subscribed to the v42l subdev event queue as well as to the bridge driver
 * using the notअगरy callback. The notअगरication type क्रम the notअगरy callback
 * will be %V4L2_DEVICE_NOTIFY_EVENT.
 */
व्योम v4l2_subdev_notअगरy_event(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_event *ev);

#पूर्ण_अगर
