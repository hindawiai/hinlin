<शैली गुरु>
/*
 * Copyright तऊ 2007-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#अगर_अघोषित __DRM_EDID_H__
#घोषणा __DRM_EDID_H__

#समावेश <linux/types.h>
#समावेश <linux/hdmi.h>
#समावेश <drm/drm_mode.h>

काष्ठा drm_device;
काष्ठा i2c_adapter;

#घोषणा EDID_LENGTH 128
#घोषणा DDC_ADDR 0x50
#घोषणा DDC_ADDR2 0x52 /* E-DDC 1.2 - where DisplayID can hide */

#घोषणा CEA_EXT	    0x02
#घोषणा VTB_EXT	    0x10
#घोषणा DI_EXT	    0x40
#घोषणा LS_EXT	    0x50
#घोषणा MI_EXT	    0x60
#घोषणा DISPLAYID_EXT 0x70

काष्ठा est_timings अणु
	u8 t1;
	u8 t2;
	u8 mfg_rsvd;
पूर्ण __attribute__((packed));

/* 00=16:10, 01=4:3, 10=5:4, 11=16:9 */
#घोषणा EDID_TIMING_ASPECT_SHIFT 6
#घोषणा EDID_TIMING_ASPECT_MASK  (0x3 << EDID_TIMING_ASPECT_SHIFT)

/* need to add 60 */
#घोषणा EDID_TIMING_VFREQ_SHIFT  0
#घोषणा EDID_TIMING_VFREQ_MASK   (0x3f << EDID_TIMING_VFREQ_SHIFT)

काष्ठा std_timing अणु
	u8 hsize; /* need to multiply by 8 then add 248 */
	u8 vfreq_aspect;
पूर्ण __attribute__((packed));

#घोषणा DRM_EDID_PT_HSYNC_POSITIVE (1 << 1)
#घोषणा DRM_EDID_PT_VSYNC_POSITIVE (1 << 2)
#घोषणा DRM_EDID_PT_SEPARATE_SYNC  (3 << 3)
#घोषणा DRM_EDID_PT_STEREO         (1 << 5)
#घोषणा DRM_EDID_PT_INTERLACED     (1 << 7)

/* If detailed data is pixel timing */
काष्ठा detailed_pixel_timing अणु
	u8 hactive_lo;
	u8 hblank_lo;
	u8 hactive_hblank_hi;
	u8 vactive_lo;
	u8 vblank_lo;
	u8 vactive_vblank_hi;
	u8 hsync_offset_lo;
	u8 hsync_pulse_width_lo;
	u8 vsync_offset_pulse_width_lo;
	u8 hsync_vsync_offset_pulse_width_hi;
	u8 width_mm_lo;
	u8 height_mm_lo;
	u8 width_height_mm_hi;
	u8 hborder;
	u8 vborder;
	u8 misc;
पूर्ण __attribute__((packed));

/* If it's not pixel timing, it'll be one of the below */
काष्ठा detailed_data_string अणु
	u8 str[13];
पूर्ण __attribute__((packed));

#घोषणा DRM_EDID_DEFAULT_GTF_SUPPORT_FLAG   0x00
#घोषणा DRM_EDID_RANGE_LIMITS_ONLY_FLAG     0x01
#घोषणा DRM_EDID_SECONDARY_GTF_SUPPORT_FLAG 0x02
#घोषणा DRM_EDID_CVT_SUPPORT_FLAG           0x04

काष्ठा detailed_data_monitor_range अणु
	u8 min_vfreq;
	u8 max_vfreq;
	u8 min_hfreq_khz;
	u8 max_hfreq_khz;
	u8 pixel_घड़ी_mhz; /* need to multiply by 10 */
	u8 flags;
	जोड़ अणु
		काष्ठा अणु
			u8 reserved;
			u8 hfreq_start_khz; /* need to multiply by 2 */
			u8 c; /* need to भागide by 2 */
			__le16 m;
			u8 k;
			u8 j; /* need to भागide by 2 */
		पूर्ण __attribute__((packed)) gtf2;
		काष्ठा अणु
			u8 version;
			u8 data1; /* high 6 bits: extra घड़ी resolution */
			u8 data2; /* plus low 2 of above: max hactive */
			u8 supported_aspects;
			u8 flags; /* preferred aspect and blanking support */
			u8 supported_scalings;
			u8 preferred_refresh;
		पूर्ण __attribute__((packed)) cvt;
	पूर्ण क्रमmula;
पूर्ण __attribute__((packed));

काष्ठा detailed_data_wpindex अणु
	u8 white_yx_lo; /* Lower 2 bits each */
	u8 white_x_hi;
	u8 white_y_hi;
	u8 gamma; /* need to भागide by 100 then add 1 */
पूर्ण __attribute__((packed));

काष्ठा detailed_data_color_poपूर्णांक अणु
	u8 windex1;
	u8 wpindex1[3];
	u8 windex2;
	u8 wpindex2[3];
पूर्ण __attribute__((packed));

काष्ठा cvt_timing अणु
	u8 code[3];
पूर्ण __attribute__((packed));

काष्ठा detailed_non_pixel अणु
	u8 pad1;
	u8 type; /* ff=serial, fe=string, fd=monitor range, fc=monitor name
		    fb=color poपूर्णांक data, fa=standard timing data,
		    f9=undefined, f8=mfg. reserved */
	u8 pad2;
	जोड़ अणु
		काष्ठा detailed_data_string str;
		काष्ठा detailed_data_monitor_range range;
		काष्ठा detailed_data_wpindex color;
		काष्ठा std_timing timings[6];
		काष्ठा cvt_timing cvt[4];
	पूर्ण data;
पूर्ण __attribute__((packed));

#घोषणा EDID_DETAIL_EST_TIMINGS 0xf7
#घोषणा EDID_DETAIL_CVT_3BYTE 0xf8
#घोषणा EDID_DETAIL_COLOR_MGMT_DATA 0xf9
#घोषणा EDID_DETAIL_STD_MODES 0xfa
#घोषणा EDID_DETAIL_MONITOR_CPDATA 0xfb
#घोषणा EDID_DETAIL_MONITOR_NAME 0xfc
#घोषणा EDID_DETAIL_MONITOR_RANGE 0xfd
#घोषणा EDID_DETAIL_MONITOR_STRING 0xfe
#घोषणा EDID_DETAIL_MONITOR_SERIAL 0xff

काष्ठा detailed_timing अणु
	__le16 pixel_घड़ी; /* need to multiply by 10 KHz */
	जोड़ अणु
		काष्ठा detailed_pixel_timing pixel_data;
		काष्ठा detailed_non_pixel other_data;
	पूर्ण data;
पूर्ण __attribute__((packed));

#घोषणा DRM_EDID_INPUT_SERRATION_VSYNC (1 << 0)
#घोषणा DRM_EDID_INPUT_SYNC_ON_GREEN   (1 << 1)
#घोषणा DRM_EDID_INPUT_COMPOSITE_SYNC  (1 << 2)
#घोषणा DRM_EDID_INPUT_SEPARATE_SYNCS  (1 << 3)
#घोषणा DRM_EDID_INPUT_BLANK_TO_BLACK  (1 << 4)
#घोषणा DRM_EDID_INPUT_VIDEO_LEVEL     (3 << 5)
#घोषणा DRM_EDID_INPUT_DIGITAL         (1 << 7)
#घोषणा DRM_EDID_DIGITAL_DEPTH_MASK    (7 << 4) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_DEPTH_UNDEF   (0 << 4) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_DEPTH_6       (1 << 4) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_DEPTH_8       (2 << 4) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_DEPTH_10      (3 << 4) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_DEPTH_12      (4 << 4) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_DEPTH_14      (5 << 4) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_DEPTH_16      (6 << 4) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_DEPTH_RSVD    (7 << 4) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_TYPE_MASK     (7 << 0) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_TYPE_UNDEF    (0 << 0) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_TYPE_DVI      (1 << 0) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_TYPE_HDMI_A   (2 << 0) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_TYPE_HDMI_B   (3 << 0) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_TYPE_MDDI     (4 << 0) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_TYPE_DP       (5 << 0) /* 1.4 */
#घोषणा DRM_EDID_DIGITAL_DFP_1_X       (1 << 0) /* 1.3 */

#घोषणा DRM_EDID_FEATURE_DEFAULT_GTF      (1 << 0)
#घोषणा DRM_EDID_FEATURE_PREFERRED_TIMING (1 << 1)
#घोषणा DRM_EDID_FEATURE_STANDARD_COLOR   (1 << 2)
/* If analog */
#घोषणा DRM_EDID_FEATURE_DISPLAY_TYPE     (3 << 3) /* 00=mono, 01=rgb, 10=non-rgb, 11=unknown */
/* If digital */
#घोषणा DRM_EDID_FEATURE_COLOR_MASK	  (3 << 3)
#घोषणा DRM_EDID_FEATURE_RGB		  (0 << 3)
#घोषणा DRM_EDID_FEATURE_RGB_YCRCB444	  (1 << 3)
#घोषणा DRM_EDID_FEATURE_RGB_YCRCB422	  (2 << 3)
#घोषणा DRM_EDID_FEATURE_RGB_YCRCB	  (3 << 3) /* both 4:4:4 and 4:2:2 */

#घोषणा DRM_EDID_FEATURE_PM_ACTIVE_OFF    (1 << 5)
#घोषणा DRM_EDID_FEATURE_PM_SUSPEND       (1 << 6)
#घोषणा DRM_EDID_FEATURE_PM_STANDBY       (1 << 7)

#घोषणा DRM_EDID_HDMI_DC_48               (1 << 6)
#घोषणा DRM_EDID_HDMI_DC_36               (1 << 5)
#घोषणा DRM_EDID_HDMI_DC_30               (1 << 4)
#घोषणा DRM_EDID_HDMI_DC_Y444             (1 << 3)

/* YCBCR 420 deep color modes */
#घोषणा DRM_EDID_YCBCR420_DC_48		  (1 << 2)
#घोषणा DRM_EDID_YCBCR420_DC_36		  (1 << 1)
#घोषणा DRM_EDID_YCBCR420_DC_30		  (1 << 0)
#घोषणा DRM_EDID_YCBCR420_DC_MASK (DRM_EDID_YCBCR420_DC_48 | \
				    DRM_EDID_YCBCR420_DC_36 | \
				    DRM_EDID_YCBCR420_DC_30)

/* HDMI 2.1 additional fields */
#घोषणा DRM_EDID_MAX_FRL_RATE_MASK		0xf0
#घोषणा DRM_EDID_FAPA_START_LOCATION		(1 << 0)
#घोषणा DRM_EDID_ALLM				(1 << 1)
#घोषणा DRM_EDID_FVA				(1 << 2)

/* Deep Color specअगरic */
#घोषणा DRM_EDID_DC_30BIT_420			(1 << 0)
#घोषणा DRM_EDID_DC_36BIT_420			(1 << 1)
#घोषणा DRM_EDID_DC_48BIT_420			(1 << 2)

/* VRR specअगरic */
#घोषणा DRM_EDID_CNMVRR				(1 << 3)
#घोषणा DRM_EDID_CINEMA_VRR			(1 << 4)
#घोषणा DRM_EDID_MDELTA				(1 << 5)
#घोषणा DRM_EDID_VRR_MAX_UPPER_MASK		0xc0
#घोषणा DRM_EDID_VRR_MAX_LOWER_MASK		0xff
#घोषणा DRM_EDID_VRR_MIN_MASK			0x3f

/* DSC specअगरic */
#घोषणा DRM_EDID_DSC_10BPC			(1 << 0)
#घोषणा DRM_EDID_DSC_12BPC			(1 << 1)
#घोषणा DRM_EDID_DSC_16BPC			(1 << 2)
#घोषणा DRM_EDID_DSC_ALL_BPP			(1 << 3)
#घोषणा DRM_EDID_DSC_NATIVE_420			(1 << 6)
#घोषणा DRM_EDID_DSC_1P2			(1 << 7)
#घोषणा DRM_EDID_DSC_MAX_FRL_RATE_MASK		0xf0
#घोषणा DRM_EDID_DSC_MAX_SLICES			0xf
#घोषणा DRM_EDID_DSC_TOTAL_CHUNK_KBYTES		0x3f

/* ELD Header Block */
#घोषणा DRM_ELD_HEADER_BLOCK_SIZE	4

#घोषणा DRM_ELD_VER			0
# define DRM_ELD_VER_SHIFT		3
# define DRM_ELD_VER_MASK		(0x1f << 3)
# define DRM_ELD_VER_CEA861D		(2 << 3) /* supports 861D or below */
# define DRM_ELD_VER_CANNED		(0x1f << 3)

#घोषणा DRM_ELD_BASELINE_ELD_LEN	2	/* in dwords! */

/* ELD Baseline Block क्रम ELD_Ver == 2 */
#घोषणा DRM_ELD_CEA_EDID_VER_MNL	4
# define DRM_ELD_CEA_EDID_VER_SHIFT	5
# define DRM_ELD_CEA_EDID_VER_MASK	(7 << 5)
# define DRM_ELD_CEA_EDID_VER_NONE	(0 << 5)
# define DRM_ELD_CEA_EDID_VER_CEA861	(1 << 5)
# define DRM_ELD_CEA_EDID_VER_CEA861A	(2 << 5)
# define DRM_ELD_CEA_EDID_VER_CEA861BCD	(3 << 5)
# define DRM_ELD_MNL_SHIFT		0
# define DRM_ELD_MNL_MASK		(0x1f << 0)

#घोषणा DRM_ELD_SAD_COUNT_CONN_TYPE	5
# define DRM_ELD_SAD_COUNT_SHIFT	4
# define DRM_ELD_SAD_COUNT_MASK		(0xf << 4)
# define DRM_ELD_CONN_TYPE_SHIFT	2
# define DRM_ELD_CONN_TYPE_MASK		(3 << 2)
# define DRM_ELD_CONN_TYPE_HDMI		(0 << 2)
# define DRM_ELD_CONN_TYPE_DP		(1 << 2)
# define DRM_ELD_SUPPORTS_AI		(1 << 1)
# define DRM_ELD_SUPPORTS_HDCP		(1 << 0)

#घोषणा DRM_ELD_AUD_SYNCH_DELAY		6	/* in units of 2 ms */
# define DRM_ELD_AUD_SYNCH_DELAY_MAX	0xfa	/* 500 ms */

#घोषणा DRM_ELD_SPEAKER			7
# define DRM_ELD_SPEAKER_MASK		0x7f
# define DRM_ELD_SPEAKER_RLRC		(1 << 6)
# define DRM_ELD_SPEAKER_FLRC		(1 << 5)
# define DRM_ELD_SPEAKER_RC		(1 << 4)
# define DRM_ELD_SPEAKER_RLR		(1 << 3)
# define DRM_ELD_SPEAKER_FC		(1 << 2)
# define DRM_ELD_SPEAKER_LFE		(1 << 1)
# define DRM_ELD_SPEAKER_FLR		(1 << 0)

#घोषणा DRM_ELD_PORT_ID			8	/* offsets 8..15 inclusive */
# define DRM_ELD_PORT_ID_LEN		8

#घोषणा DRM_ELD_MANUFACTURER_NAME0	16
#घोषणा DRM_ELD_MANUFACTURER_NAME1	17

#घोषणा DRM_ELD_PRODUCT_CODE0		18
#घोषणा DRM_ELD_PRODUCT_CODE1		19

#घोषणा DRM_ELD_MONITOR_NAME_STRING	20	/* offsets 20..(20+mnl-1) inclusive */

#घोषणा DRM_ELD_CEA_SAD(mnl, sad)	(20 + (mnl) + 3 * (sad))

काष्ठा edid अणु
	u8 header[8];
	/* Venकरोr & product info */
	u8 mfg_id[2];
	u8 prod_code[2];
	u32 serial; /* FIXME: byte order */
	u8 mfg_week;
	u8 mfg_year;
	/* EDID version */
	u8 version;
	u8 revision;
	/* Display info: */
	u8 input;
	u8 width_cm;
	u8 height_cm;
	u8 gamma;
	u8 features;
	/* Color अक्षरacteristics */
	u8 red_green_lo;
	u8 black_white_lo;
	u8 red_x;
	u8 red_y;
	u8 green_x;
	u8 green_y;
	u8 blue_x;
	u8 blue_y;
	u8 white_x;
	u8 white_y;
	/* Est. timings and mfg rsvd timings*/
	काष्ठा est_timings established_timings;
	/* Standard timings 1-8*/
	काष्ठा std_timing standard_timings[8];
	/* Detailing timings 1-4 */
	काष्ठा detailed_timing detailed_timings[4];
	/* Number of 128 byte ext. blocks */
	u8 extensions;
	/* Checksum */
	u8 checksum;
पूर्ण __attribute__((packed));

#घोषणा EDID_PRODUCT_ID(e) ((e)->prod_code[0] | ((e)->prod_code[1] << 8))

/* Short Audio Descriptor */
काष्ठा cea_sad अणु
	u8 क्रमmat;
	u8 channels; /* max number of channels - 1 */
	u8 freq;
	u8 byte2; /* meaning depends on क्रमmat */
पूर्ण;

काष्ठा drm_encoder;
काष्ठा drm_connector;
काष्ठा drm_connector_state;
काष्ठा drm_display_mode;

पूर्णांक drm_edid_to_sad(काष्ठा edid *edid, काष्ठा cea_sad **sads);
पूर्णांक drm_edid_to_speaker_allocation(काष्ठा edid *edid, u8 **sadb);
पूर्णांक drm_av_sync_delay(काष्ठा drm_connector *connector,
		      स्थिर काष्ठा drm_display_mode *mode);

#अगर_घोषित CONFIG_DRM_LOAD_EDID_FIRMWARE
काष्ठा edid *drm_load_edid_firmware(काष्ठा drm_connector *connector);
पूर्णांक __drm_set_edid_firmware_path(स्थिर अक्षर *path);
पूर्णांक __drm_get_edid_firmware_path(अक्षर *buf, माप_प्रकार bufsize);
#अन्यथा
अटल अंतरभूत काष्ठा edid *
drm_load_edid_firmware(काष्ठा drm_connector *connector)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
#पूर्ण_अगर

bool drm_edid_are_equal(स्थिर काष्ठा edid *edid1, स्थिर काष्ठा edid *edid2);

पूर्णांक
drm_hdmi_avi_infoframe_from_display_mode(काष्ठा hdmi_avi_infoframe *frame,
					 स्थिर काष्ठा drm_connector *connector,
					 स्थिर काष्ठा drm_display_mode *mode);
पूर्णांक
drm_hdmi_venकरोr_infoframe_from_display_mode(काष्ठा hdmi_venकरोr_infoframe *frame,
					    स्थिर काष्ठा drm_connector *connector,
					    स्थिर काष्ठा drm_display_mode *mode);

व्योम
drm_hdmi_avi_infoframe_colorspace(काष्ठा hdmi_avi_infoframe *frame,
				  स्थिर काष्ठा drm_connector_state *conn_state);

व्योम
drm_hdmi_avi_infoframe_bars(काष्ठा hdmi_avi_infoframe *frame,
			    स्थिर काष्ठा drm_connector_state *conn_state);

व्योम
drm_hdmi_avi_infoframe_quant_range(काष्ठा hdmi_avi_infoframe *frame,
				   स्थिर काष्ठा drm_connector *connector,
				   स्थिर काष्ठा drm_display_mode *mode,
				   क्रमागत hdmi_quantization_range rgb_quant_range);

पूर्णांक
drm_hdmi_infoframe_set_hdr_metadata(काष्ठा hdmi_drm_infoframe *frame,
				    स्थिर काष्ठा drm_connector_state *conn_state);

/**
 * drm_eld_mnl - Get ELD monitor name length in bytes.
 * @eld: poपूर्णांकer to an eld memory काष्ठाure with mnl set
 */
अटल अंतरभूत पूर्णांक drm_eld_mnl(स्थिर uपूर्णांक8_t *eld)
अणु
	वापस (eld[DRM_ELD_CEA_EDID_VER_MNL] & DRM_ELD_MNL_MASK) >> DRM_ELD_MNL_SHIFT;
पूर्ण

/**
 * drm_eld_sad - Get ELD SAD काष्ठाures.
 * @eld: poपूर्णांकer to an eld memory काष्ठाure with sad_count set
 */
अटल अंतरभूत स्थिर uपूर्णांक8_t *drm_eld_sad(स्थिर uपूर्णांक8_t *eld)
अणु
	अचिन्हित पूर्णांक ver, mnl;

	ver = (eld[DRM_ELD_VER] & DRM_ELD_VER_MASK) >> DRM_ELD_VER_SHIFT;
	अगर (ver != 2 && ver != 31)
		वापस शून्य;

	mnl = drm_eld_mnl(eld);
	अगर (mnl > 16)
		वापस शून्य;

	वापस eld + DRM_ELD_CEA_SAD(mnl, 0);
पूर्ण

/**
 * drm_eld_sad_count - Get ELD SAD count.
 * @eld: poपूर्णांकer to an eld memory काष्ठाure with sad_count set
 */
अटल अंतरभूत पूर्णांक drm_eld_sad_count(स्थिर uपूर्णांक8_t *eld)
अणु
	वापस (eld[DRM_ELD_SAD_COUNT_CONN_TYPE] & DRM_ELD_SAD_COUNT_MASK) >>
		DRM_ELD_SAD_COUNT_SHIFT;
पूर्ण

/**
 * drm_eld_calc_baseline_block_size - Calculate baseline block size in bytes
 * @eld: poपूर्णांकer to an eld memory काष्ठाure with mnl and sad_count set
 *
 * This is a helper क्रम determining the payload size of the baseline block, in
 * bytes, क्रम e.g. setting the Baseline_ELD_Len field in the ELD header block.
 */
अटल अंतरभूत पूर्णांक drm_eld_calc_baseline_block_size(स्थिर uपूर्णांक8_t *eld)
अणु
	वापस DRM_ELD_MONITOR_NAME_STRING - DRM_ELD_HEADER_BLOCK_SIZE +
		drm_eld_mnl(eld) + drm_eld_sad_count(eld) * 3;
पूर्ण

/**
 * drm_eld_size - Get ELD size in bytes
 * @eld: poपूर्णांकer to a complete eld memory काष्ठाure
 *
 * The वापसed value करोes not include the venकरोr block. It's venकरोr specअगरic,
 * and comprises of the reमुख्यing bytes in the ELD memory buffer after
 * drm_eld_size() bytes of header and baseline block.
 *
 * The वापसed value is guaranteed to be a multiple of 4.
 */
अटल अंतरभूत पूर्णांक drm_eld_size(स्थिर uपूर्णांक8_t *eld)
अणु
	वापस DRM_ELD_HEADER_BLOCK_SIZE + eld[DRM_ELD_BASELINE_ELD_LEN] * 4;
पूर्ण

/**
 * drm_eld_get_spk_alloc - Get speaker allocation
 * @eld: poपूर्णांकer to an ELD memory काष्ठाure
 *
 * The वापसed value is the speakers mask. User has to use %DRM_ELD_SPEAKER
 * field definitions to identअगरy speakers.
 */
अटल अंतरभूत u8 drm_eld_get_spk_alloc(स्थिर uपूर्णांक8_t *eld)
अणु
	वापस eld[DRM_ELD_SPEAKER] & DRM_ELD_SPEAKER_MASK;
पूर्ण

/**
 * drm_eld_get_conn_type - Get device type hdmi/dp connected
 * @eld: poपूर्णांकer to an ELD memory काष्ठाure
 *
 * The caller need to use %DRM_ELD_CONN_TYPE_HDMI or %DRM_ELD_CONN_TYPE_DP to
 * identअगरy the display type connected.
 */
अटल अंतरभूत u8 drm_eld_get_conn_type(स्थिर uपूर्णांक8_t *eld)
अणु
	वापस eld[DRM_ELD_SAD_COUNT_CONN_TYPE] & DRM_ELD_CONN_TYPE_MASK;
पूर्ण

bool drm_probe_ddc(काष्ठा i2c_adapter *adapter);
काष्ठा edid *drm_करो_get_edid(काष्ठा drm_connector *connector,
	पूर्णांक (*get_edid_block)(व्योम *data, u8 *buf, अचिन्हित पूर्णांक block,
			      माप_प्रकार len),
	व्योम *data);
काष्ठा edid *drm_get_edid(काष्ठा drm_connector *connector,
			  काष्ठा i2c_adapter *adapter);
काष्ठा edid *drm_get_edid_चयनeroo(काष्ठा drm_connector *connector,
				     काष्ठा i2c_adapter *adapter);
काष्ठा edid *drm_edid_duplicate(स्थिर काष्ठा edid *edid);
पूर्णांक drm_add_edid_modes(काष्ठा drm_connector *connector, काष्ठा edid *edid);
पूर्णांक drm_add_override_edid_modes(काष्ठा drm_connector *connector);

u8 drm_match_cea_mode(स्थिर काष्ठा drm_display_mode *to_match);
bool drm_detect_hdmi_monitor(काष्ठा edid *edid);
bool drm_detect_monitor_audio(काष्ठा edid *edid);
क्रमागत hdmi_quantization_range
drm_शेष_rgb_quant_range(स्थिर काष्ठा drm_display_mode *mode);
पूर्णांक drm_add_modes_noedid(काष्ठा drm_connector *connector,
			 पूर्णांक hdisplay, पूर्णांक vdisplay);
व्योम drm_set_preferred_mode(काष्ठा drm_connector *connector,
			    पूर्णांक hpref, पूर्णांक vpref);

पूर्णांक drm_edid_header_is_valid(स्थिर u8 *raw_edid);
bool drm_edid_block_valid(u8 *raw_edid, पूर्णांक block, bool prपूर्णांक_bad_edid,
			  bool *edid_corrupt);
bool drm_edid_is_valid(काष्ठा edid *edid);
व्योम drm_edid_get_monitor_name(काष्ठा edid *edid, अक्षर *name,
			       पूर्णांक buflen);
काष्ठा drm_display_mode *drm_mode_find_dmt(काष्ठा drm_device *dev,
					   पूर्णांक hsize, पूर्णांक vsize, पूर्णांक fresh,
					   bool rb);
काष्ठा drm_display_mode *
drm_display_mode_from_cea_vic(काष्ठा drm_device *dev,
			      u8 video_code);
स्थिर u8 *drm_find_edid_extension(स्थिर काष्ठा edid *edid,
				  पूर्णांक ext_id, पूर्णांक *ext_index);


#पूर्ण_अगर /* __DRM_EDID_H__ */
