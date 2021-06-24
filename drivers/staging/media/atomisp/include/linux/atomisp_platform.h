<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
#अगर_अघोषित ATOMISP_PLATFORM_H_
#घोषणा ATOMISP_PLATFORM_H_

#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/processor.h>

#समावेश <linux/i2c.h>
#समावेश <media/v4l2-subdev.h>
#समावेश "atomisp.h"

#घोषणा MAX_SENSORS_PER_PORT 4
#घोषणा MAX_STREAMS_PER_CHANNEL 2

#घोषणा CAMERA_MODULE_ID_LEN 64

क्रमागत atomisp_bayer_order अणु
	atomisp_bayer_order_grbg,
	atomisp_bayer_order_rggb,
	atomisp_bayer_order_bggr,
	atomisp_bayer_order_gbrg
पूर्ण;

क्रमागत atomisp_input_stream_id अणु
	ATOMISP_INPUT_STREAM_GENERAL = 0,
	ATOMISP_INPUT_STREAM_CAPTURE = 0,
	ATOMISP_INPUT_STREAM_POSTVIEW,
	ATOMISP_INPUT_STREAM_PREVIEW,
	ATOMISP_INPUT_STREAM_VIDEO,
	ATOMISP_INPUT_STREAM_NUM
पूर्ण;

क्रमागत atomisp_input_क्रमmat अणु
	ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY,/* 8 bits per subpixel (legacy) */
	ATOMISP_INPUT_FORMAT_YUV420_8, /* 8 bits per subpixel */
	ATOMISP_INPUT_FORMAT_YUV420_10,/* 10 bits per subpixel */
	ATOMISP_INPUT_FORMAT_YUV420_16,/* 16 bits per subpixel */
	ATOMISP_INPUT_FORMAT_YUV422_8, /* UYVY..UVYV, 8 bits per subpixel */
	ATOMISP_INPUT_FORMAT_YUV422_10,/* UYVY..UVYV, 10 bits per subpixel */
	ATOMISP_INPUT_FORMAT_YUV422_16,/* UYVY..UVYV, 16 bits per subpixel */
	ATOMISP_INPUT_FORMAT_RGB_444,  /* BGR..BGR, 4 bits per subpixel */
	ATOMISP_INPUT_FORMAT_RGB_555,  /* BGR..BGR, 5 bits per subpixel */
	ATOMISP_INPUT_FORMAT_RGB_565,  /* BGR..BGR, 5 bits B and R, 6 bits G */
	ATOMISP_INPUT_FORMAT_RGB_666,  /* BGR..BGR, 6 bits per subpixel */
	ATOMISP_INPUT_FORMAT_RGB_888,  /* BGR..BGR, 8 bits per subpixel */
	ATOMISP_INPUT_FORMAT_RAW_6,    /* RAW data, 6 bits per pixel */
	ATOMISP_INPUT_FORMAT_RAW_7,    /* RAW data, 7 bits per pixel */
	ATOMISP_INPUT_FORMAT_RAW_8,    /* RAW data, 8 bits per pixel */
	ATOMISP_INPUT_FORMAT_RAW_10,   /* RAW data, 10 bits per pixel */
	ATOMISP_INPUT_FORMAT_RAW_12,   /* RAW data, 12 bits per pixel */
	ATOMISP_INPUT_FORMAT_RAW_14,   /* RAW data, 14 bits per pixel */
	ATOMISP_INPUT_FORMAT_RAW_16,   /* RAW data, 16 bits per pixel */
	ATOMISP_INPUT_FORMAT_BINARY_8, /* Binary byte stream. */

	/* CSI2-MIPI specअगरic क्रमmat: Generic लघु packet data. It is used to
	 * keep the timing inक्रमmation क्रम the खोलोing/closing of shutters,
	 * triggering of flashes and etc.
	 */
	ATOMISP_INPUT_FORMAT_GENERIC_SHORT1,  /* Generic Short Packet Code 1 */
	ATOMISP_INPUT_FORMAT_GENERIC_SHORT2,  /* Generic Short Packet Code 2 */
	ATOMISP_INPUT_FORMAT_GENERIC_SHORT3,  /* Generic Short Packet Code 3 */
	ATOMISP_INPUT_FORMAT_GENERIC_SHORT4,  /* Generic Short Packet Code 4 */
	ATOMISP_INPUT_FORMAT_GENERIC_SHORT5,  /* Generic Short Packet Code 5 */
	ATOMISP_INPUT_FORMAT_GENERIC_SHORT6,  /* Generic Short Packet Code 6 */
	ATOMISP_INPUT_FORMAT_GENERIC_SHORT7,  /* Generic Short Packet Code 7 */
	ATOMISP_INPUT_FORMAT_GENERIC_SHORT8,  /* Generic Short Packet Code 8 */

	/* CSI2-MIPI specअगरic क्रमmat: YUV data.
	 */
	ATOMISP_INPUT_FORMAT_YUV420_8_SHIFT,  /* YUV420 8-bit (Chroma Shअगरted
						 Pixel Sampling) */
	ATOMISP_INPUT_FORMAT_YUV420_10_SHIFT, /* YUV420 8-bit (Chroma Shअगरted
						 Pixel Sampling) */

	/* CSI2-MIPI specअगरic क्रमmat: Generic दीर्घ packet data
	 */
	ATOMISP_INPUT_FORMAT_EMBEDDED, /* Embedded 8-bit non Image Data */

	/* CSI2-MIPI specअगरic क्रमmat: User defined byte-based data. For example,
	 * the data transmitter (e.g. the SoC sensor) can keep the JPEG data as
	 * the User Defined Data Type 4 and the MPEG data as the
	 * User Defined Data Type 7.
	 */
	ATOMISP_INPUT_FORMAT_USER_DEF1,  /* User defined 8-bit data type 1 */
	ATOMISP_INPUT_FORMAT_USER_DEF2,  /* User defined 8-bit data type 2 */
	ATOMISP_INPUT_FORMAT_USER_DEF3,  /* User defined 8-bit data type 3 */
	ATOMISP_INPUT_FORMAT_USER_DEF4,  /* User defined 8-bit data type 4 */
	ATOMISP_INPUT_FORMAT_USER_DEF5,  /* User defined 8-bit data type 5 */
	ATOMISP_INPUT_FORMAT_USER_DEF6,  /* User defined 8-bit data type 6 */
	ATOMISP_INPUT_FORMAT_USER_DEF7,  /* User defined 8-bit data type 7 */
	ATOMISP_INPUT_FORMAT_USER_DEF8,  /* User defined 8-bit data type 8 */
पूर्ण;

#घोषणा N_ATOMISP_INPUT_FORMAT (ATOMISP_INPUT_FORMAT_USER_DEF8 + 1)

क्रमागत पूर्णांकel_v4l2_subdev_type अणु
	RAW_CAMERA = 1,
	SOC_CAMERA = 2,
	CAMERA_MOTOR = 3,
	LED_FLASH = 4,
	XENON_FLASH = 5,
	खाता_INPUT = 6,
	TEST_PATTERN = 7,
पूर्ण;

काष्ठा पूर्णांकel_v4l2_subdev_id अणु
	अक्षर name[17];
	क्रमागत पूर्णांकel_v4l2_subdev_type type;
	क्रमागत atomisp_camera_port    port;
पूर्ण;

काष्ठा पूर्णांकel_v4l2_subdev_i2c_board_info अणु
	काष्ठा i2c_board_info board_info;
	पूर्णांक i2c_adapter_id;
पूर्ण;

काष्ठा पूर्णांकel_v4l2_subdev_table अणु
	काष्ठा पूर्णांकel_v4l2_subdev_i2c_board_info v4l2_subdev;
	क्रमागत पूर्णांकel_v4l2_subdev_type type;
	क्रमागत atomisp_camera_port port;
	काष्ठा v4l2_subdev *subdev;
पूर्ण;

काष्ठा atomisp_platक्रमm_data अणु
	काष्ठा पूर्णांकel_v4l2_subdev_table *subdevs;
पूर्ण;

/* Describe the capacities of one single sensor. */
काष्ठा atomisp_sensor_caps अणु
	/* The number of streams this sensor can output. */
	पूर्णांक stream_num;
	bool is_slave;
पूर्ण;

/* Describe the capacities of sensors connected to one camera port. */
काष्ठा atomisp_camera_caps अणु
	/* The number of sensors connected to this camera port. */
	पूर्णांक sensor_num;
	/* The capacities of each sensor. */
	काष्ठा atomisp_sensor_caps sensor[MAX_SENSORS_PER_PORT];
	/* Define whether stream control is required क्रम multiple streams. */
	bool multi_stream_ctrl;
पूर्ण;

/*
 *  Sensor of बाह्यal ISP can send multiple steams with dअगरferent mipi data
 * type in the same भव channel. This inक्रमmation needs to come from the
 * sensor or बाह्यal ISP
 */
काष्ठा atomisp_isys_config_info अणु
	u8 input_क्रमmat;
	u16 width;
	u16 height;
पूर्ण;

काष्ठा atomisp_input_stream_info अणु
	क्रमागत atomisp_input_stream_id stream;
	u8 enable;
	/* Sensor driver fills ch_id with the id
	   of the भव channel. */
	u8 ch_id;
	/* Tells how many streams in this भव channel. If 0 ignore rest
	 * and the input क्रमmat will be from mipi_info */
	u8 isys_configs;
	/*
	 * अगर more isys_configs is more than 0, sensor needs to configure the
	 * input क्रमmat dअगरferently. width and height can be 0. If width and
	 * height is not zero, then the corresponsing data needs to be set
	 */
	काष्ठा atomisp_isys_config_info isys_info[MAX_STREAMS_PER_CHANNEL];
पूर्ण;

काष्ठा camera_vcm_control;
काष्ठा camera_vcm_ops अणु
	पूर्णांक (*घातer_up)(काष्ठा v4l2_subdev *sd, काष्ठा camera_vcm_control *vcm);
	पूर्णांक (*घातer_करोwn)(काष्ठा v4l2_subdev *sd,
			  काष्ठा camera_vcm_control *vcm);
	पूर्णांक (*queryctrl)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_queryctrl *qc,
			 काष्ठा camera_vcm_control *vcm);
	पूर्णांक (*g_ctrl)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_control *ctrl,
		      काष्ठा camera_vcm_control *vcm);
	पूर्णांक (*s_ctrl)(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_control *ctrl,
		      काष्ठा camera_vcm_control *vcm);
पूर्ण;

काष्ठा camera_vcm_control अणु
	अक्षर camera_module[CAMERA_MODULE_ID_LEN];
	काष्ठा camera_vcm_ops *ops;
	काष्ठा list_head list;
पूर्ण;

काष्ठा camera_sensor_platक्रमm_data अणु
	पूर्णांक (*flisclk_ctrl)(काष्ठा v4l2_subdev *subdev, पूर्णांक flag);
	पूर्णांक (*csi_cfg)(काष्ठा v4l2_subdev *subdev, पूर्णांक flag);

	/*
	 * New G-Min घातer and GPIO पूर्णांकerface to control inभागidual
	 * lines as implemented on all known camera modules.
	 */
	पूर्णांक (*gpio0_ctrl)(काष्ठा v4l2_subdev *subdev, पूर्णांक on);
	पूर्णांक (*gpio1_ctrl)(काष्ठा v4l2_subdev *subdev, पूर्णांक on);
	पूर्णांक (*v1p8_ctrl)(काष्ठा v4l2_subdev *subdev, पूर्णांक on);
	पूर्णांक (*v2p8_ctrl)(काष्ठा v4l2_subdev *subdev, पूर्णांक on);
	पूर्णांक (*v1p2_ctrl)(काष्ठा v4l2_subdev *subdev, पूर्णांक on);
	काष्ठा camera_vcm_control *(*get_vcm_ctrl)(काष्ठा v4l2_subdev *subdev,
		अक्षर *module_id);
पूर्ण;

काष्ठा camera_mipi_info अणु
	क्रमागत atomisp_camera_port        port;
	अचिन्हित पूर्णांक                    num_lanes;
	क्रमागत atomisp_input_क्रमmat       input_क्रमmat;
	क्रमागत atomisp_bayer_order        raw_bayer_order;
	काष्ठा atomisp_sensor_mode_data data;
	क्रमागत atomisp_input_क्रमmat       metadata_क्रमmat;
	u32                             metadata_width;
	u32                             metadata_height;
	स्थिर u32                       *metadata_effective_width;
पूर्ण;

स्थिर काष्ठा atomisp_platक्रमm_data *atomisp_get_platक्रमm_data(व्योम);
स्थिर काष्ठा atomisp_camera_caps *atomisp_get_शेष_camera_caps(व्योम);

/* API from old platक्रमm_camera.h, new CPUID implementation */
#घोषणा __IS_SOC(x) (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL && \
		     boot_cpu_data.x86 == 6 &&                       \
		     boot_cpu_data.x86_model == (x))
#घोषणा __IS_SOCS(x,y) (boot_cpu_data.x86_venकरोr == X86_VENDOR_INTEL && \
		        boot_cpu_data.x86 == 6 &&                       \
		        (boot_cpu_data.x86_model == (x) || \
		         boot_cpu_data.x86_model == (y)))

#घोषणा IS_MFLD	__IS_SOC(INTEL_FAM6_ATOM_SALTWELL_MID)
#घोषणा IS_BYT	__IS_SOC(INTEL_FAM6_ATOM_SILVERMONT)
#घोषणा IS_CHT	__IS_SOC(INTEL_FAM6_ATOM_AIRMONT)
#घोषणा IS_MRFD	__IS_SOC(INTEL_FAM6_ATOM_SILVERMONT_MID)
#घोषणा IS_MOFD	__IS_SOC(INTEL_FAM6_ATOM_AIRMONT_MID)

/* Both CHT and MOFD come with ISP2401 */
#घोषणा IS_ISP2401 __IS_SOCS(INTEL_FAM6_ATOM_AIRMONT, \
			     INTEL_FAM6_ATOM_AIRMONT_MID)

#पूर्ण_अगर /* ATOMISP_PLATFORM_H_ */
