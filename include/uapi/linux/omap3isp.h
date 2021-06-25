<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * omap3isp.h
 *
 * TI OMAP3 ISP - User-space API
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA
 * 02110-1301 USA
 */

#अगर_अघोषित OMAP3_ISP_USER_H
#घोषणा OMAP3_ISP_USER_H

#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

/*
 * Private IOCTLs
 *
 * VIDIOC_OMAP3ISP_CCDC_CFG: Set CCDC configuration
 * VIDIOC_OMAP3ISP_PRV_CFG: Set preview engine configuration
 * VIDIOC_OMAP3ISP_AEWB_CFG: Set AEWB module configuration
 * VIDIOC_OMAP3ISP_HIST_CFG: Set histogram module configuration
 * VIDIOC_OMAP3ISP_AF_CFG: Set स्वतः-focus module configuration
 * VIDIOC_OMAP3ISP_STAT_REQ: Read statistics (AEWB/AF/histogram) data
 * VIDIOC_OMAP3ISP_STAT_EN: Enable/disable a statistics module
 */

#घोषणा VIDIOC_OMAP3ISP_CCDC_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 1, काष्ठा omap3isp_ccdc_update_config)
#घोषणा VIDIOC_OMAP3ISP_PRV_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 2, काष्ठा omap3isp_prev_update_config)
#घोषणा VIDIOC_OMAP3ISP_AEWB_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 3, काष्ठा omap3isp_h3a_aewb_config)
#घोषणा VIDIOC_OMAP3ISP_HIST_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 4, काष्ठा omap3isp_hist_config)
#घोषणा VIDIOC_OMAP3ISP_AF_CFG \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 5, काष्ठा omap3isp_h3a_af_config)
#घोषणा VIDIOC_OMAP3ISP_STAT_REQ \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 6, काष्ठा omap3isp_stat_data)
#घोषणा VIDIOC_OMAP3ISP_STAT_REQ_TIME32 \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 6, काष्ठा omap3isp_stat_data_समय32)
#घोषणा VIDIOC_OMAP3ISP_STAT_EN \
	_IOWR('V', BASE_VIDIOC_PRIVATE + 7, अचिन्हित दीर्घ)

/*
 * Events
 *
 * V4L2_EVENT_OMAP3ISP_AEWB: AEWB statistics data पढ़ोy
 * V4L2_EVENT_OMAP3ISP_AF: AF statistics data पढ़ोy
 * V4L2_EVENT_OMAP3ISP_HIST: Histogram statistics data पढ़ोy
 */

#घोषणा V4L2_EVENT_OMAP3ISP_CLASS	(V4L2_EVENT_PRIVATE_START | 0x100)
#घोषणा V4L2_EVENT_OMAP3ISP_AEWB	(V4L2_EVENT_OMAP3ISP_CLASS | 0x1)
#घोषणा V4L2_EVENT_OMAP3ISP_AF		(V4L2_EVENT_OMAP3ISP_CLASS | 0x2)
#घोषणा V4L2_EVENT_OMAP3ISP_HIST	(V4L2_EVENT_OMAP3ISP_CLASS | 0x3)

काष्ठा omap3isp_stat_event_status अणु
	__u32 frame_number;
	__u16 config_counter;
	__u8 buf_err;
पूर्ण;

/* AE/AWB related काष्ठाures and flags*/

/* H3A Range Constants */
#घोषणा OMAP3ISP_AEWB_MAX_SATURATION_LIM	1023
#घोषणा OMAP3ISP_AEWB_MIN_WIN_H			2
#घोषणा OMAP3ISP_AEWB_MAX_WIN_H			256
#घोषणा OMAP3ISP_AEWB_MIN_WIN_W			6
#घोषणा OMAP3ISP_AEWB_MAX_WIN_W			256
#घोषणा OMAP3ISP_AEWB_MIN_WINVC			1
#घोषणा OMAP3ISP_AEWB_MIN_WINHC			1
#घोषणा OMAP3ISP_AEWB_MAX_WINVC			128
#घोषणा OMAP3ISP_AEWB_MAX_WINHC			36
#घोषणा OMAP3ISP_AEWB_MAX_WINSTART		4095
#घोषणा OMAP3ISP_AEWB_MIN_SUB_INC		2
#घोषणा OMAP3ISP_AEWB_MAX_SUB_INC		32
#घोषणा OMAP3ISP_AEWB_MAX_BUF_SIZE		83600

#घोषणा OMAP3ISP_AF_IIRSH_MIN			0
#घोषणा OMAP3ISP_AF_IIRSH_MAX			4095
#घोषणा OMAP3ISP_AF_PAXEL_HORIZONTAL_COUNT_MIN	1
#घोषणा OMAP3ISP_AF_PAXEL_HORIZONTAL_COUNT_MAX	36
#घोषणा OMAP3ISP_AF_PAXEL_VERTICAL_COUNT_MIN	1
#घोषणा OMAP3ISP_AF_PAXEL_VERTICAL_COUNT_MAX	128
#घोषणा OMAP3ISP_AF_PAXEL_INCREMENT_MIN		2
#घोषणा OMAP3ISP_AF_PAXEL_INCREMENT_MAX		32
#घोषणा OMAP3ISP_AF_PAXEL_HEIGHT_MIN		2
#घोषणा OMAP3ISP_AF_PAXEL_HEIGHT_MAX		256
#घोषणा OMAP3ISP_AF_PAXEL_WIDTH_MIN		16
#घोषणा OMAP3ISP_AF_PAXEL_WIDTH_MAX		256
#घोषणा OMAP3ISP_AF_PAXEL_HZSTART_MIN		1
#घोषणा OMAP3ISP_AF_PAXEL_HZSTART_MAX		4095
#घोषणा OMAP3ISP_AF_PAXEL_VTSTART_MIN		0
#घोषणा OMAP3ISP_AF_PAXEL_VTSTART_MAX		4095
#घोषणा OMAP3ISP_AF_THRESHOLD_MAX		255
#घोषणा OMAP3ISP_AF_COEF_MAX			4095
#घोषणा OMAP3ISP_AF_PAXEL_SIZE			48
#घोषणा OMAP3ISP_AF_MAX_BUF_SIZE		221184

/**
 * काष्ठा omap3isp_h3a_aewb_config - AE AWB configuration reset values
 * saturation_limit: Saturation limit.
 * @win_height: Winकरोw Height. Range 2 - 256, even values only.
 * @win_width: Winकरोw Width. Range 6 - 256, even values only.
 * @ver_win_count: Vertical Winकरोw Count. Range 1 - 128.
 * @hor_win_count: Horizontal Winकरोw Count. Range 1 - 36.
 * @ver_win_start: Vertical Winकरोw Start. Range 0 - 4095.
 * @hor_win_start: Horizontal Winकरोw Start. Range 0 - 4095.
 * @blk_ver_win_start: Black Vertical Winकरोws Start. Range 0 - 4095.
 * @blk_win_height: Black Winकरोw Height. Range 2 - 256, even values only.
 * @subsample_ver_inc: Subsample Vertical poपूर्णांकs increment Range 2 - 32, even
 *                     values only.
 * @subsample_hor_inc: Subsample Horizontal poपूर्णांकs increment Range 2 - 32, even
 *                     values only.
 * @alaw_enable: AEW ALAW EN flag.
 */
काष्ठा omap3isp_h3a_aewb_config अणु
	/*
	 * Common fields.
	 * They should be the first ones and must be in the same order as in
	 * ispstat_generic_config काष्ठा.
	 */
	__u32 buf_size;
	__u16 config_counter;

	/* Private fields */
	__u16 saturation_limit;
	__u16 win_height;
	__u16 win_width;
	__u16 ver_win_count;
	__u16 hor_win_count;
	__u16 ver_win_start;
	__u16 hor_win_start;
	__u16 blk_ver_win_start;
	__u16 blk_win_height;
	__u16 subsample_ver_inc;
	__u16 subsample_hor_inc;
	__u8 alaw_enable;
पूर्ण;

/**
 * काष्ठा omap3isp_stat_data - Statistic data sent to or received from user
 * @ts: Timestamp of वापसed framestats.
 * @buf: Poपूर्णांकer to pass to user.
 * @frame_number: Frame number of requested stats.
 * @cur_frame: Current frame number being processed.
 * @config_counter: Number of the configuration associated with the data.
 */
काष्ठा omap3isp_stat_data अणु
#अगर_घोषित __KERNEL__
	काष्ठा अणु
		__s64	tv_sec;
		__s64	tv_usec;
	पूर्ण ts;
#अन्यथा
	काष्ठा समयval ts;
#पूर्ण_अगर
	व्योम __user *buf;
	__u32 buf_size;
	__u16 frame_number;
	__u16 cur_frame;
	__u16 config_counter;
पूर्ण;

#अगर_घोषित __KERNEL__
काष्ठा omap3isp_stat_data_समय32 अणु
	काष्ठा अणु
		__s32	tv_sec;
		__s32	tv_usec;
	पूर्ण ts;
	__u32 buf;
	__u32 buf_size;
	__u16 frame_number;
	__u16 cur_frame;
	__u16 config_counter;
पूर्ण;
#पूर्ण_अगर

/* Histogram related काष्ठाs */

/* Flags क्रम number of bins */
#घोषणा OMAP3ISP_HIST_BINS_32		0
#घोषणा OMAP3ISP_HIST_BINS_64		1
#घोषणा OMAP3ISP_HIST_BINS_128		2
#घोषणा OMAP3ISP_HIST_BINS_256		3

/* Number of bins * 4 colors * 4-bytes word */
#घोषणा OMAP3ISP_HIST_MEM_SIZE_BINS(n)	((1 << ((n)+5))*4*4)

#घोषणा OMAP3ISP_HIST_MEM_SIZE		1024
#घोषणा OMAP3ISP_HIST_MIN_REGIONS	1
#घोषणा OMAP3ISP_HIST_MAX_REGIONS	4
#घोषणा OMAP3ISP_HIST_MAX_WB_GAIN	255
#घोषणा OMAP3ISP_HIST_MIN_WB_GAIN	0
#घोषणा OMAP3ISP_HIST_MAX_BIT_WIDTH	14
#घोषणा OMAP3ISP_HIST_MIN_BIT_WIDTH	8
#घोषणा OMAP3ISP_HIST_MAX_WG		4
#घोषणा OMAP3ISP_HIST_MAX_BUF_SIZE	4096

/* Source */
#घोषणा OMAP3ISP_HIST_SOURCE_CCDC	0
#घोषणा OMAP3ISP_HIST_SOURCE_MEM	1

/* CFA pattern */
#घोषणा OMAP3ISP_HIST_CFA_BAYER		0
#घोषणा OMAP3ISP_HIST_CFA_FOVEONX3	1

काष्ठा omap3isp_hist_region अणु
	__u16 h_start;
	__u16 h_end;
	__u16 v_start;
	__u16 v_end;
पूर्ण;

काष्ठा omap3isp_hist_config अणु
	/*
	 * Common fields.
	 * They should be the first ones and must be in the same order as in
	 * ispstat_generic_config काष्ठा.
	 */
	__u32 buf_size;
	__u16 config_counter;

	__u8 num_acc_frames;	/* Num of image frames to be processed and
				   accumulated क्रम each histogram frame */
	__u16 hist_bins;	/* number of bins: 32, 64, 128, or 256 */
	__u8 cfa;		/* BAYER or FOVEON X3 */
	__u8 wg[OMAP3ISP_HIST_MAX_WG];	/* White Balance Gain */
	__u8 num_regions;	/* number of regions to be configured */
	काष्ठा omap3isp_hist_region region[OMAP3ISP_HIST_MAX_REGIONS];
पूर्ण;

/* Auto Focus related काष्ठाs */

#घोषणा OMAP3ISP_AF_NUM_COEF		11

क्रमागत omap3isp_h3a_af_fvmode अणु
	OMAP3ISP_AF_MODE_SUMMED = 0,
	OMAP3ISP_AF_MODE_PEAK = 1
पूर्ण;

/* Red, Green, and blue pixel location in the AF winकरोws */
क्रमागत omap3isp_h3a_af_rgbpos अणु
	OMAP3ISP_AF_GR_GB_BAYER = 0,	/* GR and GB as Bayer pattern */
	OMAP3ISP_AF_RG_GB_BAYER = 1,	/* RG and GB as Bayer pattern */
	OMAP3ISP_AF_GR_BG_BAYER = 2,	/* GR and BG as Bayer pattern */
	OMAP3ISP_AF_RG_BG_BAYER = 3,	/* RG and BG as Bayer pattern */
	OMAP3ISP_AF_GG_RB_CUSTOM = 4,	/* GG and RB as custom pattern */
	OMAP3ISP_AF_RB_GG_CUSTOM = 5	/* RB and GG as custom pattern */
पूर्ण;

/* Contains the inक्रमmation regarding the Horizontal Median Filter */
काष्ठा omap3isp_h3a_af_hmf अणु
	__u8 enable;	/* Status of Horizontal Median Filter */
	__u8 threshold;	/* Threshold Value क्रम Horizontal Median Filter */
पूर्ण;

/* Contains the inक्रमmation regarding the IIR Filters */
काष्ठा omap3isp_h3a_af_iir अणु
	__u16 h_start;			/* IIR horizontal start */
	__u16 coeff_set0[OMAP3ISP_AF_NUM_COEF];	/* Filter coefficient, set 0 */
	__u16 coeff_set1[OMAP3ISP_AF_NUM_COEF];	/* Filter coefficient, set 1 */
पूर्ण;

/* Contains the inक्रमmation regarding the Paxels Structure in AF Engine */
काष्ठा omap3isp_h3a_af_paxel अणु
	__u16 h_start;	/* Horizontal Start Position */
	__u16 v_start;	/* Vertical Start Position */
	__u8 width;	/* Width of the Paxel */
	__u8 height;	/* Height of the Paxel */
	__u8 h_cnt;	/* Horizontal Count */
	__u8 v_cnt;	/* vertical Count */
	__u8 line_inc;	/* Line Increment */
पूर्ण;

/* Contains the parameters required क्रम hardware set up of AF Engine */
काष्ठा omap3isp_h3a_af_config अणु
	/*
	 * Common fields.
	 * They should be the first ones and must be in the same order as in
	 * ispstat_generic_config काष्ठा.
	 */
	__u32 buf_size;
	__u16 config_counter;

	काष्ठा omap3isp_h3a_af_hmf hmf;		/* HMF configurations */
	काष्ठा omap3isp_h3a_af_iir iir;		/* IIR filter configurations */
	काष्ठा omap3isp_h3a_af_paxel paxel;	/* Paxel parameters */
	क्रमागत omap3isp_h3a_af_rgbpos rgb_pos;	/* RGB Positions */
	क्रमागत omap3isp_h3a_af_fvmode fvmode;	/* Accumulator mode */
	__u8 alaw_enable;			/* AF ALAW status */
पूर्ण;

/* ISP CCDC काष्ठाs */

/* Abstraction layer CCDC configurations */
#घोषणा OMAP3ISP_CCDC_ALAW		(1 << 0)
#घोषणा OMAP3ISP_CCDC_LPF		(1 << 1)
#घोषणा OMAP3ISP_CCDC_BLCLAMP		(1 << 2)
#घोषणा OMAP3ISP_CCDC_BCOMP		(1 << 3)
#घोषणा OMAP3ISP_CCDC_FPC		(1 << 4)
#घोषणा OMAP3ISP_CCDC_CULL		(1 << 5)
#घोषणा OMAP3ISP_CCDC_CONFIG_LSC	(1 << 7)
#घोषणा OMAP3ISP_CCDC_TBL_LSC		(1 << 8)

#घोषणा OMAP3ISP_RGB_MAX		3

/* Enumeration स्थिरants क्रम Alaw input width */
क्रमागत omap3isp_alaw_ipwidth अणु
	OMAP3ISP_ALAW_BIT12_3 = 0x3,
	OMAP3ISP_ALAW_BIT11_2 = 0x4,
	OMAP3ISP_ALAW_BIT10_1 = 0x5,
	OMAP3ISP_ALAW_BIT9_0 = 0x6
पूर्ण;

/**
 * काष्ठा omap3isp_ccdc_lsc_config - LSC configuration
 * @offset: Table Offset of the gain table.
 * @gain_mode_n: Vertical dimension of a paxel in LSC configuration.
 * @gain_mode_m: Horizontal dimension of a paxel in LSC configuration.
 * @gain_क्रमmat: Gain table क्रमmat.
 * @fmtsph: Start pixel horizontal from start of the HS sync pulse.
 * @fmtlnh: Number of pixels in horizontal direction to use क्रम the data
 *          reक्रमmatter.
 * @fmtslv: Start line from start of VS sync pulse क्रम the data reक्रमmatter.
 * @fmtlnv: Number of lines in vertical direction क्रम the data reक्रमmatter.
 * @initial_x: X position, in pixels, of the first active pixel in reference
 *             to the first active paxel. Must be an even number.
 * @initial_y: Y position, in pixels, of the first active pixel in reference
 *             to the first active paxel. Must be an even number.
 * @size: Size of LSC gain table. Filled when loaded from userspace.
 */
काष्ठा omap3isp_ccdc_lsc_config अणु
	__u16 offset;
	__u8 gain_mode_n;
	__u8 gain_mode_m;
	__u8 gain_क्रमmat;
	__u16 fmtsph;
	__u16 fmtlnh;
	__u16 fmtslv;
	__u16 fmtlnv;
	__u8 initial_x;
	__u8 initial_y;
	__u32 size;
पूर्ण;

/**
 * काष्ठा omap3isp_ccdc_bclamp - Optical & Digital black clamp subtract
 * @obgain: Optical black average gain.
 * @obstpixel: Start Pixel w.r.t. HS pulse in Optical black sample.
 * @oblines: Optical Black Sample lines.
 * @oblen: Optical Black Sample Length.
 * @dcsubval: Digital Black Clamp subtract value.
 */
काष्ठा omap3isp_ccdc_bclamp अणु
	__u8 obgain;
	__u8 obstpixel;
	__u8 oblines;
	__u8 oblen;
	__u16 dcsubval;
पूर्ण;

/**
 * काष्ठा omap3isp_ccdc_fpc - Faulty Pixels Correction
 * @fpnum: Number of faulty pixels to be corrected in the frame.
 * @fpcaddr: Memory address of the FPC Table
 */
काष्ठा omap3isp_ccdc_fpc अणु
	__u16 fpnum;
	__u32 fpcaddr;
पूर्ण;

/**
 * काष्ठा omap3isp_ccdc_blcomp - Black Level Compensation parameters
 * @b_mg: B/Mg pixels. 2's complement. -128 to +127.
 * @gb_g: Gb/G pixels. 2's complement. -128 to +127.
 * @gr_cy: Gr/Cy pixels. 2's complement. -128 to +127.
 * @r_ye: R/Ye pixels. 2's complement. -128 to +127.
 */
काष्ठा omap3isp_ccdc_blcomp अणु
	__u8 b_mg;
	__u8 gb_g;
	__u8 gr_cy;
	__u8 r_ye;
पूर्ण;

/**
 * omap3isp_ccdc_culling - Culling parameters
 * @v_pattern: Vertical culling pattern.
 * @h_odd: Horizontal Culling pattern क्रम odd lines.
 * @h_even: Horizontal Culling pattern क्रम even lines.
 */
काष्ठा omap3isp_ccdc_culling अणु
	__u8 v_pattern;
	__u16 h_odd;
	__u16 h_even;
पूर्ण;

/**
 * omap3isp_ccdc_update_config - CCDC configuration
 * @update: Specअगरies which CCDC रेजिस्टरs should be updated.
 * @flag: Specअगरies which CCDC functions should be enabled.
 * @alawip: Enable/Disable A-Law compression.
 * @bclamp: Black clamp control रेजिस्टर.
 * @blcomp: Black level compensation value क्रम RGrGbB Pixels. 2's complement.
 * @fpc: Number of faulty pixels corrected in the frame, address of FPC table.
 * @cull: Cull control रेजिस्टर.
 * @lsc: Poपूर्णांकer to LSC gain table.
 */
काष्ठा omap3isp_ccdc_update_config अणु
	__u16 update;
	__u16 flag;
	क्रमागत omap3isp_alaw_ipwidth alawip;
	काष्ठा omap3isp_ccdc_bclamp __user *bclamp;
	काष्ठा omap3isp_ccdc_blcomp __user *blcomp;
	काष्ठा omap3isp_ccdc_fpc __user *fpc;
	काष्ठा omap3isp_ccdc_lsc_config __user *lsc_cfg;
	काष्ठा omap3isp_ccdc_culling __user *cull;
	__u8 __user *lsc;
पूर्ण;

/* Preview configurations */
#घोषणा OMAP3ISP_PREV_LUMAENH		(1 << 0)
#घोषणा OMAP3ISP_PREV_INVALAW		(1 << 1)
#घोषणा OMAP3ISP_PREV_HRZ_MED		(1 << 2)
#घोषणा OMAP3ISP_PREV_CFA		(1 << 3)
#घोषणा OMAP3ISP_PREV_CHROMA_SUPP	(1 << 4)
#घोषणा OMAP3ISP_PREV_WB		(1 << 5)
#घोषणा OMAP3ISP_PREV_BLKADJ		(1 << 6)
#घोषणा OMAP3ISP_PREV_RGB2RGB		(1 << 7)
#घोषणा OMAP3ISP_PREV_COLOR_CONV	(1 << 8)
#घोषणा OMAP3ISP_PREV_YC_LIMIT		(1 << 9)
#घोषणा OMAP3ISP_PREV_DEFECT_COR	(1 << 10)
/* Bit 11 was OMAP3ISP_PREV_GAMMABYPASS, now merged with OMAP3ISP_PREV_GAMMA */
#घोषणा OMAP3ISP_PREV_DRK_FRM_CAPTURE	(1 << 12)
#घोषणा OMAP3ISP_PREV_DRK_FRM_SUBTRACT	(1 << 13)
#घोषणा OMAP3ISP_PREV_LENS_SHADING	(1 << 14)
#घोषणा OMAP3ISP_PREV_NF		(1 << 15)
#घोषणा OMAP3ISP_PREV_GAMMA		(1 << 16)

#घोषणा OMAP3ISP_PREV_NF_TBL_SIZE	64
#घोषणा OMAP3ISP_PREV_CFA_TBL_SIZE	576
#घोषणा OMAP3ISP_PREV_CFA_BLK_SIZE	(OMAP3ISP_PREV_CFA_TBL_SIZE / 4)
#घोषणा OMAP3ISP_PREV_GAMMA_TBL_SIZE	1024
#घोषणा OMAP3ISP_PREV_YENH_TBL_SIZE	128

#घोषणा OMAP3ISP_PREV_DETECT_CORRECT_CHANNELS	4

/**
 * काष्ठा omap3isp_prev_hmed - Horizontal Median Filter
 * @odddist: Distance between consecutive pixels of same color in the odd line.
 * @evendist: Distance between consecutive pixels of same color in the even
 *            line.
 * @thres: Horizontal median filter threshold.
 */
काष्ठा omap3isp_prev_hmed अणु
	__u8 odddist;
	__u8 evendist;
	__u8 thres;
पूर्ण;

/*
 * Enumeration क्रम CFA Formats supported by preview
 */
क्रमागत omap3isp_cfa_fmt अणु
	OMAP3ISP_CFAFMT_BAYER,
	OMAP3ISP_CFAFMT_SONYVGA,
	OMAP3ISP_CFAFMT_RGBFOVEON,
	OMAP3ISP_CFAFMT_DNSPL,
	OMAP3ISP_CFAFMT_HONEYCOMB,
	OMAP3ISP_CFAFMT_RRGGBBFOVEON
पूर्ण;

/**
 * काष्ठा omap3isp_prev_cfa - CFA Interpolation
 * @क्रमmat: CFA Format Enum value supported by preview.
 * @gradthrs_vert: CFA Gradient Threshold - Vertical.
 * @gradthrs_horz: CFA Gradient Threshold - Horizontal.
 * @table: Poपूर्णांकer to the CFA table.
 */
काष्ठा omap3isp_prev_cfa अणु
	क्रमागत omap3isp_cfa_fmt क्रमmat;
	__u8 gradthrs_vert;
	__u8 gradthrs_horz;
	__u32 table[4][OMAP3ISP_PREV_CFA_BLK_SIZE];
पूर्ण;

/**
 * काष्ठा omap3isp_prev_csup - Chrominance Suppression
 * @gain: Gain.
 * @thres: Threshold.
 * @hypf_en: Flag to enable/disable the High Pass Filter.
 */
काष्ठा omap3isp_prev_csup अणु
	__u8 gain;
	__u8 thres;
	__u8 hypf_en;
पूर्ण;

/**
 * काष्ठा omap3isp_prev_wbal - White Balance
 * @dgain: Digital gain (U10Q8).
 * @coef3: White balance gain - COEF 3 (U8Q5).
 * @coef2: White balance gain - COEF 2 (U8Q5).
 * @coef1: White balance gain - COEF 1 (U8Q5).
 * @coef0: White balance gain - COEF 0 (U8Q5).
 */
काष्ठा omap3isp_prev_wbal अणु
	__u16 dgain;
	__u8 coef3;
	__u8 coef2;
	__u8 coef1;
	__u8 coef0;
पूर्ण;

/**
 * काष्ठा omap3isp_prev_blkadj - Black Level Adjusपंचांगent
 * @red: Black level offset adjusपंचांगent क्रम Red in 2's complement क्रमmat
 * @green: Black level offset adjusपंचांगent क्रम Green in 2's complement क्रमmat
 * @blue: Black level offset adjusपंचांगent क्रम Blue in 2's complement क्रमmat
 */
काष्ठा omap3isp_prev_blkadj अणु
	/*Black level offset adjusपंचांगent क्रम Red in 2's complement क्रमmat */
	__u8 red;
	/*Black level offset adjusपंचांगent क्रम Green in 2's complement क्रमmat */
	__u8 green;
	/* Black level offset adjusपंचांगent क्रम Blue in 2's complement क्रमmat */
	__u8 blue;
पूर्ण;

/**
 * काष्ठा omap3isp_prev_rgbtorgb - RGB to RGB Blending
 * @matrix: Blending values(S12Q8 क्रमmat)
 *              [RR] [GR] [BR]
 *              [RG] [GG] [BG]
 *              [RB] [GB] [BB]
 * @offset: Blending offset value क्रम R,G,B in 2's complement पूर्णांकeger क्रमmat.
 */
काष्ठा omap3isp_prev_rgbtorgb अणु
	__u16 matrix[OMAP3ISP_RGB_MAX][OMAP3ISP_RGB_MAX];
	__u16 offset[OMAP3ISP_RGB_MAX];
पूर्ण;

/**
 * काष्ठा omap3isp_prev_csc - Color Space Conversion from RGB-YCbYCr
 * @matrix: Color space conversion coefficients(S10Q8)
 *              [CSCRY]  [CSCGY]  [CSCBY]
 *              [CSCRCB] [CSCGCB] [CSCBCB]
 *              [CSCRCR] [CSCGCR] [CSCBCR]
 * @offset: CSC offset values क्रम Y offset, CB offset and CR offset respectively
 */
काष्ठा omap3isp_prev_csc अणु
	__u16 matrix[OMAP3ISP_RGB_MAX][OMAP3ISP_RGB_MAX];
	__s16 offset[OMAP3ISP_RGB_MAX];
पूर्ण;

/**
 * काष्ठा omap3isp_prev_yclimit - Y, C Value Limit
 * @minC: Minimum C value
 * @maxC: Maximum C value
 * @minY: Minimum Y value
 * @maxY: Maximum Y value
 */
काष्ठा omap3isp_prev_yclimit अणु
	__u8 minC;
	__u8 maxC;
	__u8 minY;
	__u8 maxY;
पूर्ण;

/**
 * काष्ठा omap3isp_prev_dcor - Defect correction
 * @couplet_mode_en: Flag to enable or disable the couplet dc Correction in NF
 * @detect_correct: Thresholds क्रम correction bit 0:10 detect 16:25 correct
 */
काष्ठा omap3isp_prev_dcor अणु
	__u8 couplet_mode_en;
	__u32 detect_correct[OMAP3ISP_PREV_DETECT_CORRECT_CHANNELS];
पूर्ण;

/**
 * काष्ठा omap3isp_prev_nf - Noise Filter
 * @spपढ़ो: Spपढ़ो value to be used in Noise Filter
 * @table: Poपूर्णांकer to the Noise Filter table
 */
काष्ठा omap3isp_prev_nf अणु
	__u8 spपढ़ो;
	__u32 table[OMAP3ISP_PREV_NF_TBL_SIZE];
पूर्ण;

/**
 * काष्ठा omap3isp_prev_gtables - Gamma correction tables
 * @red: Array क्रम red gamma table.
 * @green: Array क्रम green gamma table.
 * @blue: Array क्रम blue gamma table.
 */
काष्ठा omap3isp_prev_gtables अणु
	__u32 red[OMAP3ISP_PREV_GAMMA_TBL_SIZE];
	__u32 green[OMAP3ISP_PREV_GAMMA_TBL_SIZE];
	__u32 blue[OMAP3ISP_PREV_GAMMA_TBL_SIZE];
पूर्ण;

/**
 * काष्ठा omap3isp_prev_luma - Luma enhancement
 * @table: Array क्रम luma enhancement table.
 */
काष्ठा omap3isp_prev_luma अणु
	__u32 table[OMAP3ISP_PREV_YENH_TBL_SIZE];
पूर्ण;

/**
 * काष्ठा omap3isp_prev_update_config - Preview engine configuration (user)
 * @update: Specअगरies which ISP Preview रेजिस्टरs should be updated.
 * @flag: Specअगरies which ISP Preview functions should be enabled.
 * @shading_shअगरt: 3bit value of shअगरt used in shading compensation.
 * @luma: Poपूर्णांकer to luma enhancement काष्ठाure.
 * @hmed: Poपूर्णांकer to काष्ठाure containing the odd and even distance.
 *        between the pixels in the image aदीर्घ with the filter threshold.
 * @cfa: Poपूर्णांकer to काष्ठाure containing the CFA पूर्णांकerpolation table, CFA.
 *       क्रमmat in the image, vertical and horizontal gradient threshold.
 * @csup: Poपूर्णांकer to Structure क्रम Chrominance Suppression coefficients.
 * @wbal: Poपूर्णांकer to काष्ठाure क्रम White Balance.
 * @blkadj: Poपूर्णांकer to काष्ठाure क्रम Black Adjusपंचांगent.
 * @rgb2rgb: Poपूर्णांकer to काष्ठाure क्रम RGB to RGB Blending.
 * @csc: Poपूर्णांकer to काष्ठाure क्रम Color Space Conversion from RGB-YCbYCr.
 * @yclimit: Poपूर्णांकer to काष्ठाure क्रम Y, C Value Limit.
 * @dcor: Poपूर्णांकer to काष्ठाure क्रम defect correction.
 * @nf: Poपूर्णांकer to काष्ठाure क्रम Noise Filter
 * @gamma: Poपूर्णांकer to gamma काष्ठाure.
 */
काष्ठा omap3isp_prev_update_config अणु
	__u32 update;
	__u32 flag;
	__u32 shading_shअगरt;
	काष्ठा omap3isp_prev_luma __user *luma;
	काष्ठा omap3isp_prev_hmed __user *hmed;
	काष्ठा omap3isp_prev_cfa __user *cfa;
	काष्ठा omap3isp_prev_csup __user *csup;
	काष्ठा omap3isp_prev_wbal __user *wbal;
	काष्ठा omap3isp_prev_blkadj __user *blkadj;
	काष्ठा omap3isp_prev_rgbtorgb __user *rgb2rgb;
	काष्ठा omap3isp_prev_csc __user *csc;
	काष्ठा omap3isp_prev_yclimit __user *yclimit;
	काष्ठा omap3isp_prev_dcor __user *dcor;
	काष्ठा omap3isp_prev_nf __user *nf;
	काष्ठा omap3isp_prev_gtables __user *gamma;
पूर्ण;

#पूर्ण_अगर	/* OMAP3_ISP_USER_H */
