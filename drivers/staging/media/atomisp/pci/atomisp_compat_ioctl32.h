<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
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
#अगर_अघोषित __ATOMISP_COMPAT_IOCTL32_H__
#घोषणा __ATOMISP_COMPAT_IOCTL32_H__

#समावेश <linux/compat.h>
#समावेश <linux/videodev2.h>

#समावेश "atomisp_compat.h"

काष्ठा atomisp_histogram32 अणु
	अचिन्हित पूर्णांक num_elements;
	compat_uptr_t data;
पूर्ण;

काष्ठा atomisp_dvs2_stat_types32 अणु
	compat_uptr_t odd_real; /** real part of the odd statistics*/
	compat_uptr_t odd_imag; /** imaginary part of the odd statistics*/
	compat_uptr_t even_real;/** real part of the even statistics*/
	compat_uptr_t even_imag;/** imaginary part of the even statistics*/
पूर्ण;

काष्ठा atomisp_dvs2_coef_types32 अणु
	compat_uptr_t odd_real; /** real part of the odd coefficients*/
	compat_uptr_t odd_imag; /** imaginary part of the odd coefficients*/
	compat_uptr_t even_real;/** real part of the even coefficients*/
	compat_uptr_t even_imag;/** imaginary part of the even coefficients*/
पूर्ण;

काष्ठा atomisp_dvs2_statistics32 अणु
	काष्ठा atomisp_dvs_grid_info grid_info;
	काष्ठा atomisp_dvs2_stat_types32 hor_prod;
	काष्ठा atomisp_dvs2_stat_types32 ver_prod;
पूर्ण;

काष्ठा atomisp_dis_statistics32 अणु
	काष्ठा atomisp_dvs2_statistics32 dvs2_stat;
	u32 exp_id;
पूर्ण;

काष्ठा atomisp_dis_coefficients32 अणु
	काष्ठा atomisp_dvs_grid_info grid_info;
	काष्ठा atomisp_dvs2_coef_types32 hor_coefs;
	काष्ठा atomisp_dvs2_coef_types32 ver_coefs;
पूर्ण;

काष्ठा atomisp_3a_statistics32 अणु
	काष्ठा atomisp_grid_info  grid_info;
	compat_uptr_t data;
	compat_uptr_t rgby_data;
	u32 exp_id;
	u32 isp_config_id;
पूर्ण;

काष्ठा atomisp_metadata_with_type32 अणु
	/* to specअगरy which type of metadata to get */
	क्रमागत atomisp_metadata_type type;
	compat_uptr_t data;
	u32 width;
	u32 height;
	u32 stride; /* in bytes */
	u32 exp_id; /* exposure ID */
	compat_uptr_t effective_width;
पूर्ण;

काष्ठा atomisp_metadata32 अणु
	compat_uptr_t data;
	u32 width;
	u32 height;
	u32 stride;
	u32 exp_id;
	compat_uptr_t effective_width;
पूर्ण;

काष्ठा atomisp_morph_table32 अणु
	अचिन्हित पूर्णांक enabled;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक width;	/* number of valid elements per line */
	compat_uptr_t coordinates_x[ATOMISP_MORPH_TABLE_NUM_PLANES];
	compat_uptr_t coordinates_y[ATOMISP_MORPH_TABLE_NUM_PLANES];
पूर्ण;

काष्ठा v4l2_framebuffer32 अणु
	__u32			capability;
	__u32			flags;
	compat_uptr_t		base;
	काष्ठा v4l2_pix_क्रमmat	fmt;
पूर्ण;

काष्ठा atomisp_overlay32 अणु
	/* the frame containing the overlay data The overlay frame width should
	 * be the multiples of 2*ISP_VEC_NELEMS. The overlay frame height
	 * should be the multiples of 2.
	 */
	compat_uptr_t frame;
	/* Y value of overlay background */
	अचिन्हित अक्षर bg_y;
	/* U value of overlay background */
	अक्षर bg_u;
	/* V value of overlay background */
	अक्षर bg_v;
	/* the blending percent of input data क्रम Y subpixels */
	अचिन्हित अक्षर blend_input_perc_y;
	/* the blending percent of input data क्रम U subpixels */
	अचिन्हित अक्षर blend_input_perc_u;
	/* the blending percent of input data क्रम V subpixels */
	अचिन्हित अक्षर blend_input_perc_v;
	/* the blending percent of overlay data क्रम Y subpixels */
	अचिन्हित अक्षर blend_overlay_perc_y;
	/* the blending percent of overlay data क्रम U subpixels */
	अचिन्हित अक्षर blend_overlay_perc_u;
	/* the blending percent of overlay data क्रम V subpixels */
	अचिन्हित अक्षर blend_overlay_perc_v;
	/* the overlay start x pixel position on output frame It should be the
	   multiples of 2*ISP_VEC_NELEMS. */
	अचिन्हित पूर्णांक overlay_start_x;
	/* the overlay start y pixel position on output frame It should be the
	   multiples of 2. */
	अचिन्हित पूर्णांक overlay_start_y;
पूर्ण;

काष्ठा atomisp_calibration_group32 अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक type;
	compat_uptr_t calb_grp_values;
पूर्ण;

काष्ठा atomisp_acc_fw_load32 अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक fw_handle;
	compat_uptr_t data;
पूर्ण;

काष्ठा atomisp_acc_fw_arg32 अणु
	अचिन्हित पूर्णांक fw_handle;
	अचिन्हित पूर्णांक index;
	compat_uptr_t value;
	compat_माप_प्रकार size;
पूर्ण;

काष्ठा v4l2_निजी_पूर्णांक_data32 अणु
	__u32 size;
	compat_uptr_t data;
	__u32 reserved[2];
पूर्ण;

काष्ठा atomisp_shading_table32 अणु
	__u32 enable;
	__u32 sensor_width;
	__u32 sensor_height;
	__u32 width;
	__u32 height;
	__u32 fraction_bits;

	compat_uptr_t data[ATOMISP_NUM_SC_COLORS];
पूर्ण;

काष्ठा atomisp_acc_map32 अणु
	__u32 flags;			/* Flags, see list below */
	__u32 length;			/* Length of data in bytes */
	compat_uptr_t user_ptr;		/* Poपूर्णांकer पूर्णांकo user space */
	compat_uदीर्घ_t css_ptr;		/* Poपूर्णांकer पूर्णांकo CSS address space */
	__u32 reserved[4];		/* Set to zero */
पूर्ण;

काष्ठा atomisp_acc_s_mapped_arg32 अणु
	अचिन्हित पूर्णांक fw_handle;
	__u32 memory;			/* one of क्रमागत atomisp_acc_memory */
	compat_माप_प्रकार length;
	compat_uदीर्घ_t css_ptr;
पूर्ण;

काष्ठा atomisp_parameters32 अणु
	compat_uptr_t wb_config;  /* White Balance config */
	compat_uptr_t cc_config;  /* Color Correction config */
	compat_uptr_t tnr_config; /* Temporal Noise Reduction */
	compat_uptr_t ecd_config; /* Eigen Color Demosaicing */
	compat_uptr_t ynr_config; /* Y(Luma) Noise Reduction */
	compat_uptr_t fc_config;  /* Fringe Control */
	compat_uptr_t क्रमmats_config;  /* Formats Control */
	compat_uptr_t cnr_config; /* Chroma Noise Reduction */
	compat_uptr_t macc_config;  /* MACC */
	compat_uptr_t ctc_config; /* Chroma Tone Control */
	compat_uptr_t aa_config;  /* Anti-Aliasing */
	compat_uptr_t baa_config;  /* Anti-Aliasing */
	compat_uptr_t ce_config;
	compat_uptr_t dvs_6axis_config;
	compat_uptr_t ob_config;  /* Objective Black config */
	compat_uptr_t dp_config;  /* Dead Pixel config */
	compat_uptr_t nr_config;  /* Noise Reduction config */
	compat_uptr_t ee_config;  /* Edge Enhancement config */
	compat_uptr_t de_config;  /* Demosaic config */
	compat_uptr_t gc_config;  /* Gamma Correction config */
	compat_uptr_t anr_config; /* Advanced Noise Reduction */
	compat_uptr_t a3a_config; /* 3A Statistics config */
	compat_uptr_t xnr_config; /* eXtra Noise Reduction */
	compat_uptr_t dz_config;  /* Digital Zoom */
	compat_uptr_t yuv2rgb_cc_config; /* Color
							Correction config */
	compat_uptr_t rgb2yuv_cc_config; /* Color
							Correction config */
	compat_uptr_t macc_table;
	compat_uptr_t gamma_table;
	compat_uptr_t ctc_table;
	compat_uptr_t xnr_table;
	compat_uptr_t r_gamma_table;
	compat_uptr_t g_gamma_table;
	compat_uptr_t b_gamma_table;
	compat_uptr_t motion_vector; /* For 2-axis DVS */
	compat_uptr_t shading_table;
	compat_uptr_t morph_table;
	compat_uptr_t dvs_coefs; /* DVS 1.0 coefficients */
	compat_uptr_t dvs2_coefs; /* DVS 2.0 coefficients */
	compat_uptr_t capture_config;
	compat_uptr_t anr_thres;

	compat_uptr_t	lin_2500_config;       /* Skylake: Linearization config */
	compat_uptr_t	obgrid_2500_config;    /* Skylake: OBGRID config */
	compat_uptr_t	bnr_2500_config;       /* Skylake: bayer denoise config */
	compat_uptr_t	shd_2500_config;       /* Skylake: shading config */
	compat_uptr_t	dm_2500_config;        /* Skylake: demosaic config */
	compat_uptr_t	rgbpp_2500_config;     /* Skylake: RGBPP config */
	compat_uptr_t	dvs_stat_2500_config;  /* Skylake: DVS STAT config */
	compat_uptr_t	lace_stat_2500_config; /* Skylake: LACE STAT config */
	compat_uptr_t	yuvp1_2500_config;     /* Skylake: yuvp1 config */
	compat_uptr_t	yuvp2_2500_config;     /* Skylake: yuvp2 config */
	compat_uptr_t	tnr_2500_config;       /* Skylake: TNR config */
	compat_uptr_t	dpc_2500_config;       /* Skylake: DPC config */
	compat_uptr_t	awb_2500_config;       /* Skylake: स्वतः white balance config */
	compat_uptr_t
	awb_fr_2500_config;    /* Skylake: स्वतः white balance filter response config */
	compat_uptr_t	anr_2500_config;       /* Skylake: ANR config */
	compat_uptr_t	af_2500_config;        /* Skylake: स्वतः focus config */
	compat_uptr_t	ae_2500_config;        /* Skylake: स्वतः exposure config */
	compat_uptr_t	bds_2500_config;       /* Skylake: bayer करोwnscaler config */
	compat_uptr_t
	dvs_2500_config;       /* Skylake: digital video stabilization config */
	compat_uptr_t	res_mgr_2500_config;

	/*
	 * Output frame poपूर्णांकer the config is to be applied to (optional),
	 * set to शून्य to make this config is applied as global.
	 */
	compat_uptr_t	output_frame;
	/*
	 * Unique ID to track which config was actually applied to a particular
	 * frame, driver will send this id back with output frame together.
	 */
	u32	isp_config_id;
	u32	per_frame_setting;
पूर्ण;

काष्ठा atomisp_acc_fw_load_to_pipe32 अणु
	__u32 flags;			/* Flags, see below क्रम valid values */
	अचिन्हित पूर्णांक fw_handle;		/* Handle, filled by kernel. */
	__u32 size;			/* Firmware binary size */
	compat_uptr_t data;		/* Poपूर्णांकer to firmware */
	__u32 type;			/* Binary type */
	__u32 reserved[3];		/* Set to zero */
पूर्ण;

काष्ठा atomisp_dvs_6axis_config32 अणु
	u32 exp_id;
	u32 width_y;
	u32 height_y;
	u32 width_uv;
	u32 height_uv;
	compat_uptr_t xcoords_y;
	compat_uptr_t ycoords_y;
	compat_uptr_t xcoords_uv;
	compat_uptr_t ycoords_uv;
पूर्ण;

काष्ठा atomisp_sensor_ae_bracketing_lut32 अणु
	compat_uptr_t lut;
	अचिन्हित पूर्णांक lut_size;
पूर्ण;

#घोषणा ATOMISP_IOC_G_HISTOGRAM32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 3, काष्ठा atomisp_histogram32)
#घोषणा ATOMISP_IOC_S_HISTOGRAM32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 3, काष्ठा atomisp_histogram32)

#घोषणा ATOMISP_IOC_G_DIS_STAT32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 6, काष्ठा atomisp_dis_statistics32)
#घोषणा ATOMISP_IOC_S_DIS_COEFS32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 6, काष्ठा atomisp_dis_coefficients32)

#घोषणा ATOMISP_IOC_S_DIS_VECTOR32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 6, काष्ठा atomisp_dvs_6axis_config32)

#घोषणा ATOMISP_IOC_G_3A_STAT32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 7, काष्ठा atomisp_3a_statistics32)

#घोषणा ATOMISP_IOC_G_ISP_GDC_TAB32 \
	_IOR('v', BASE_VIDIOC_PRIVATE + 10, काष्ठा atomisp_morph_table32)
#घोषणा ATOMISP_IOC_S_ISP_GDC_TAB32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 10, काष्ठा atomisp_morph_table32)

#घोषणा ATOMISP_IOC_S_ISP_FPN_TABLE32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 17, काष्ठा v4l2_framebuffer32)

#घोषणा ATOMISP_IOC_G_ISP_OVERLAY32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 18, काष्ठा atomisp_overlay32)
#घोषणा ATOMISP_IOC_S_ISP_OVERLAY32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 18, काष्ठा atomisp_overlay32)

#घोषणा ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 22, काष्ठा atomisp_calibration_group32)

#घोषणा ATOMISP_IOC_ACC_LOAD32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 24, काष्ठा atomisp_acc_fw_load32)

#घोषणा ATOMISP_IOC_ACC_S_ARG32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 24, काष्ठा atomisp_acc_fw_arg32)

#घोषणा ATOMISP_IOC_ACC_DESTAB32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 25, काष्ठा atomisp_acc_fw_arg32)

#घोषणा ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 26, काष्ठा v4l2_निजी_पूर्णांक_data32)

#घोषणा ATOMISP_IOC_S_ISP_SHD_TAB32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 27, काष्ठा atomisp_shading_table32)

#घोषणा ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 29, काष्ठा v4l2_निजी_पूर्णांक_data32)

#घोषणा ATOMISP_IOC_ACC_MAP32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 30, काष्ठा atomisp_acc_map32)

#घोषणा ATOMISP_IOC_ACC_UNMAP32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 30, काष्ठा atomisp_acc_map32)

#घोषणा ATOMISP_IOC_ACC_S_MAPPED_ARG32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 30, काष्ठा atomisp_acc_s_mapped_arg32)

#घोषणा ATOMISP_IOC_ACC_LOAD_TO_PIPE32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 31, काष्ठा atomisp_acc_fw_load_to_pipe32)

#घोषणा ATOMISP_IOC_S_PARAMETERS32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 32, काष्ठा atomisp_parameters32)

#घोषणा ATOMISP_IOC_G_METADATA32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 34, काष्ठा atomisp_metadata32)

#घोषणा ATOMISP_IOC_G_METADATA_BY_TYPE32 \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 34, काष्ठा atomisp_metadata_with_type32)

#घोषणा ATOMISP_IOC_S_SENSOR_AE_BRACKETING_LUT32 \
	_IOW('v', BASE_VIDIOC_PRIVATE + 43, काष्ठा atomisp_sensor_ae_bracketing_lut32)

#पूर्ण_अगर /* __ATOMISP_COMPAT_IOCTL32_H__ */
