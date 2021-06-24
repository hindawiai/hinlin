<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Header क्रम M-5MOLS 8M Pixel camera sensor with ISP
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * Author: HeungJun Kim <riverful.kim@samsung.com>
 *
 * Copyright (C) 2009 Samsung Electronics Co., Ltd.
 * Author: Dongsoo Nathaniel Kim <करोngsoo45.kim@samsung.com>
 */

#अगर_अघोषित M5MOLS_H
#घोषणा M5MOLS_H

#समावेश <linux/sizes.h>
#समावेश <media/v4l2-subdev.h>
#समावेश "m5mols_reg.h"


/* An amount of data transmitted in addition to the value
 * determined by CAPP_JPEG_SIZE_MAX रेजिस्टर.
 */
#घोषणा M5MOLS_JPEG_TAGS_SIZE		0x20000
#घोषणा M5MOLS_MAIN_JPEG_SIZE_MAX	(5 * SZ_1M)

बाह्य पूर्णांक m5mols_debug;

क्रमागत m5mols_restype अणु
	M5MOLS_RESTYPE_MONITOR,
	M5MOLS_RESTYPE_CAPTURE,
	M5MOLS_RESTYPE_MAX,
पूर्ण;

/**
 * काष्ठा m5mols_resolution - काष्ठाure क्रम the resolution
 * @type: resolution type according to the pixel code
 * @width: width of the resolution
 * @height: height of the resolution
 * @reg: resolution preset रेजिस्टर value
 */
काष्ठा m5mols_resolution अणु
	u8 reg;
	क्रमागत m5mols_restype type;
	u16 width;
	u16 height;
पूर्ण;

/**
 * काष्ठा m5mols_exअगर - काष्ठाure क्रम the EXIF inक्रमmation of M-5MOLS
 * @exposure_समय: exposure समय रेजिस्टर value
 * @shutter_speed: speed of the shutter रेजिस्टर value
 * @aperture: aperture रेजिस्टर value
 * @brightness: brightness रेजिस्टर value
 * @exposure_bias: it calls also EV bias
 * @iso_speed: ISO रेजिस्टर value
 * @flash: status रेजिस्टर value of the flash
 * @sdr: status रेजिस्टर value of the Subject Distance Range
 * @qval: not written exact meaning in करोcument
 */
काष्ठा m5mols_exअगर अणु
	u32 exposure_समय;
	u32 shutter_speed;
	u32 aperture;
	u32 brightness;
	u32 exposure_bias;
	u16 iso_speed;
	u16 flash;
	u16 sdr;
	u16 qval;
पूर्ण;

/**
 * काष्ठा m5mols_capture - Structure क्रम the capture capability
 * @exअगर: EXIF inक्रमmation
 * @buf_size: पूर्णांकernal JPEG frame buffer size, in bytes
 * @मुख्य: size in bytes of the मुख्य image
 * @thumb: size in bytes of the thumb image, अगर it was accompanied
 * @total: total size in bytes of the produced image
 */
काष्ठा m5mols_capture अणु
	काष्ठा m5mols_exअगर exअगर;
	अचिन्हित पूर्णांक buf_size;
	u32 मुख्य;
	u32 thumb;
	u32 total;
पूर्ण;

/**
 * काष्ठा m5mols_scenemode - काष्ठाure क्रम the scenemode capability
 * @metering: metering light रेजिस्टर value
 * @ev_bias: EV bias रेजिस्टर value
 * @wb_mode: mode which means the WhiteBalance is Auto or Manual
 * @wb_preset: whitebalance preset रेजिस्टर value in the Manual mode
 * @chroma_en: रेजिस्टर value whether the Chroma capability is enabled or not
 * @chroma_lvl: chroma's level रेजिस्टर value
 * @edge_en: रेजिस्टर value Whether the Edge capability is enabled or not
 * @edge_lvl: edge's level रेजिस्टर value
 * @af_range: Auto Focus's range
 * @fd_mode: Face Detection mode
 * @mcc: Multi-axis Color Conversion which means emotion color
 * @light: status of the Light
 * @flash: status of the Flash
 * @tone: Tone color which means Contrast
 * @iso: ISO रेजिस्टर value
 * @capt_mode: Mode of the Image Stabilization जबतक the camera capturing
 * @wdr: Wide Dynamic Range रेजिस्टर value
 *
 * The each value according to each scenemode is recommended in the करोcuments.
 */
काष्ठा m5mols_scenemode अणु
	u8 metering;
	u8 ev_bias;
	u8 wb_mode;
	u8 wb_preset;
	u8 chroma_en;
	u8 chroma_lvl;
	u8 edge_en;
	u8 edge_lvl;
	u8 af_range;
	u8 fd_mode;
	u8 mcc;
	u8 light;
	u8 flash;
	u8 tone;
	u8 iso;
	u8 capt_mode;
	u8 wdr;
पूर्ण;

#घोषणा VERSION_STRING_SIZE	22

/**
 * काष्ठा m5mols_version - firmware version inक्रमmation
 * @customer:	customer inक्रमmation
 * @project:	version of project inक्रमmation according to customer
 * @fw:		firmware revision
 * @hw:		hardware revision
 * @param:	version of the parameter
 * @awb:	Auto WhiteBalance algorithm version
 * @str:	inक्रमmation about manufacturer and packaging venकरोr
 * @af:		Auto Focus version
 *
 * The रेजिस्टर offset starts the customer version at 0x0, and it ends
 * the awb version at 0x09. The customer, project inक्रमmation occupies 1 bytes
 * each. And also the fw, hw, param, awb each requires 2 bytes. The str is
 * unique string associated with firmware's version. It includes inक्रमmation
 * about manufacturer and the venकरोr of the sensor's packaging. The least
 * signअगरicant 2 bytes of the string indicate packaging manufacturer.
 */
काष्ठा m5mols_version अणु
	u8	customer;
	u8	project;
	u16	fw;
	u16	hw;
	u16	param;
	u16	awb;
	u8	str[VERSION_STRING_SIZE];
	u8	af;
पूर्ण;

/**
 * काष्ठा m5mols_info - M-5MOLS driver data काष्ठाure
 * @pdata: platक्रमm data
 * @sd: v4l-subdev instance
 * @pad: media pad
 * @irq_रुकोq: रुकोqueue क्रम the capture
 * @irq_करोne: set to 1 in the पूर्णांकerrupt handler
 * @handle: control handler
 * @स्वतः_exposure: स्वतः/manual exposure control
 * @exposure_bias: exposure compensation control
 * @exposure: manual exposure control
 * @metering: exposure metering control
 * @स्वतः_iso: स्वतः/manual ISO sensitivity control
 * @iso: manual ISO sensitivity control
 * @स्वतः_wb: स्वतः white balance control
 * @lock_3a: 3A lock control
 * @colorfx: color effect control
 * @saturation: saturation control
 * @zoom: zoom control
 * @wdr: wide dynamic range control
 * @stabilization: image stabilization control
 * @jpeg_quality: JPEG compression quality control
 * @set_घातer: optional घातer callback to the board code
 * @lock: mutex protecting the काष्ठाure fields below
 * @ffmt: current fmt according to resolution type
 * @res_type: current resolution type
 * @ver: inक्रमmation of the version
 * @cap: the capture mode attributes
 * @isp_पढ़ोy: 1 when the ISP controller has completed booting
 * @घातer: current sensor's घातer status
 * @ctrl_sync: 1 when the control handler state is restored in H/W
 * @resolution:	रेजिस्टर value क्रम current resolution
 * @mode: रेजिस्टर value क्रम current operation mode
 */
काष्ठा m5mols_info अणु
	स्थिर काष्ठा m5mols_platक्रमm_data *pdata;
	काष्ठा v4l2_subdev sd;
	काष्ठा media_pad pad;

	रुको_queue_head_t irq_रुकोq;
	atomic_t irq_करोne;

	काष्ठा v4l2_ctrl_handler handle;
	काष्ठा अणु
		/* exposure/exposure bias/स्वतः exposure cluster */
		काष्ठा v4l2_ctrl *स्वतः_exposure;
		काष्ठा v4l2_ctrl *exposure_bias;
		काष्ठा v4l2_ctrl *exposure;
		काष्ठा v4l2_ctrl *metering;
	पूर्ण;
	काष्ठा अणु
		/* iso/स्वतः iso cluster */
		काष्ठा v4l2_ctrl *स्वतः_iso;
		काष्ठा v4l2_ctrl *iso;
	पूर्ण;
	काष्ठा v4l2_ctrl *स्वतः_wb;

	काष्ठा v4l2_ctrl *lock_3a;
	काष्ठा v4l2_ctrl *colorfx;
	काष्ठा v4l2_ctrl *saturation;
	काष्ठा v4l2_ctrl *zoom;
	काष्ठा v4l2_ctrl *wdr;
	काष्ठा v4l2_ctrl *stabilization;
	काष्ठा v4l2_ctrl *jpeg_quality;

	पूर्णांक (*set_घातer)(काष्ठा device *dev, पूर्णांक on);

	काष्ठा mutex lock;

	काष्ठा v4l2_mbus_framefmt ffmt[M5MOLS_RESTYPE_MAX];
	पूर्णांक res_type;

	काष्ठा m5mols_version ver;
	काष्ठा m5mols_capture cap;

	अचिन्हित पूर्णांक isp_पढ़ोy:1;
	अचिन्हित पूर्णांक घातer:1;
	अचिन्हित पूर्णांक ctrl_sync:1;

	u8 resolution;
	u8 mode;
पूर्ण;

#घोषणा is_available_af(__info)	(__info->ver.af)
#घोषणा is_code(__code, __type) (__code == m5mols_शेष_ffmt[__type].code)
#घोषणा is_manufacturer(__info, __manufacturer)	\
				(__info->ver.str[0] == __manufacturer[0] && \
				 __info->ver.str[1] == __manufacturer[1])
/*
 * I2C operation of the M-5MOLS
 *
 * The I2C पढ़ो operation of the M-5MOLS requires 2 messages. The first
 * message sends the inक्रमmation about the command, command category, and total
 * message size. The second message is used to retrieve the data specअगरied in
 * the first message
 *
 *   1st message                                2nd message
 *   +-------+---+----------+-----+-------+     +------+------+------+------+
 *   | size1 | R | category | cmd | size2 |     | d[0] | d[1] | d[2] | d[3] |
 *   +-------+---+----------+-----+-------+     +------+------+------+------+
 *   - size1: message data size(5 in this हाल)
 *   - size2: desired buffer size of the 2nd message
 *   - d[0..3]: according to size2
 *
 * The I2C ग_लिखो operation needs just one message. The message includes
 * category, command, total size, and desired data.
 *
 *   1st message
 *   +-------+---+----------+-----+------+------+------+------+
 *   | size1 | W | category | cmd | d[0] | d[1] | d[2] | d[3] |
 *   +-------+---+----------+-----+------+------+------+------+
 *   - d[0..3]: according to size1
 */
पूर्णांक m5mols_पढ़ो_u8(काष्ठा v4l2_subdev *sd, u32 reg_comb, u8 *val);
पूर्णांक m5mols_पढ़ो_u16(काष्ठा v4l2_subdev *sd, u32 reg_comb, u16 *val);
पूर्णांक m5mols_पढ़ो_u32(काष्ठा v4l2_subdev *sd, u32 reg_comb, u32 *val);
पूर्णांक m5mols_ग_लिखो(काष्ठा v4l2_subdev *sd, u32 reg_comb, u32 val);

पूर्णांक m5mols_busy_रुको(काष्ठा v4l2_subdev *sd, u32 reg, u32 value, u32 mask,
		     पूर्णांक समयout);

/* Mask value क्रम busy रुकोing until M-5MOLS I2C पूर्णांकerface is initialized */
#घोषणा M5MOLS_I2C_RDY_WAIT_FL		(1 << 16)
/* ISP state transition समयout, in ms */
#घोषणा M5MOLS_MODE_CHANGE_TIMEOUT	200
#घोषणा M5MOLS_BUSY_WAIT_DEF_TIMEOUT	250

/*
 * Mode operation of the M-5MOLS
 *
 * Changing the mode of the M-5MOLS is needed right executing order.
 * There are three modes(PARAMETER, MONITOR, CAPTURE) which can be changed
 * by user. There are various categories associated with each mode.
 *
 * +============================================================+
 * | mode	| category					|
 * +============================================================+
 * | FLASH	| FLASH(only after Stand-by or Power-on)	|
 * | SYSTEM	| SYSTEM(only after sensor arm-booting)		|
 * | PARAMETER	| PARAMETER					|
 * | MONITOR	| MONITOR(preview), Auto Focus, Face Detection	|
 * | CAPTURE	| Single CAPTURE, Preview(recording)		|
 * +============================================================+
 *
 * The available executing order between each modes are as follows:
 *   PARAMETER <---> MONITOR <---> CAPTURE
 */
पूर्णांक m5mols_set_mode(काष्ठा m5mols_info *info, u8 mode);

पूर्णांक m5mols_enable_पूर्णांकerrupt(काष्ठा v4l2_subdev *sd, u8 reg);
पूर्णांक m5mols_रुको_पूर्णांकerrupt(काष्ठा v4l2_subdev *sd, u8 condition, u32 समयout);
पूर्णांक m5mols_restore_controls(काष्ठा m5mols_info *info);
पूर्णांक m5mols_start_capture(काष्ठा m5mols_info *info);
पूर्णांक m5mols_करो_scenemode(काष्ठा m5mols_info *info, u8 mode);
पूर्णांक m5mols_lock_3a(काष्ठा m5mols_info *info, bool lock);
पूर्णांक m5mols_set_ctrl(काष्ठा v4l2_ctrl *ctrl);
पूर्णांक m5mols_init_controls(काष्ठा v4l2_subdev *sd);

/* The firmware function */
पूर्णांक m5mols_update_fw(काष्ठा v4l2_subdev *sd,
		     पूर्णांक (*set_घातer)(काष्ठा m5mols_info *, bool));

अटल अंतरभूत काष्ठा m5mols_info *to_m5mols(काष्ठा v4l2_subdev *subdev)
अणु
	वापस container_of(subdev, काष्ठा m5mols_info, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा m5mols_info *info = container_of(ctrl->handler,
						काष्ठा m5mols_info, handle);
	वापस &info->sd;
पूर्ण

अटल अंतरभूत व्योम m5mols_set_ctrl_mode(काष्ठा v4l2_ctrl *ctrl,
					अचिन्हित पूर्णांक mode)
अणु
	ctrl->priv = (व्योम *)(uपूर्णांकptr_t)mode;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक m5mols_get_ctrl_mode(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस (अचिन्हित पूर्णांक)(uपूर्णांकptr_t)ctrl->priv;
पूर्ण

#पूर्ण_अगर	/* M5MOLS_H */
