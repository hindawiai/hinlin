<शैली गुरु>
/*
 * Copyright तऊ 2008 Keith Packard
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#अगर_अघोषित _DRM_DP_HELPER_H_
#घोषणा _DRM_DP_HELPER_H_

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/types.h>
#समावेश <drm/drm_connector.h>

काष्ठा drm_device;

/*
 * Unless otherwise noted, all values are from the DP 1.1a spec.  Note that
 * DP and DPCD versions are independent.  Dअगरferences from 1.0 are not noted,
 * 1.0 devices basically करोn't exist in the wild.
 *
 * Abbreviations, in chronological order:
 *
 * eDP: Embedded DisplayPort version 1
 * DPI: DisplayPort Interoperability Guideline v1.1a
 * 1.2: DisplayPort 1.2
 * MST: Multistream Transport - part of DP 1.2a
 *
 * 1.2 क्रमmally includes both eDP and DPI definitions.
 */

/* MSA (Main Stream Attribute) MISC bits (as MISC1<<8|MISC0) */
#घोषणा DP_MSA_MISC_SYNC_CLOCK			(1 << 0)
#घोषणा DP_MSA_MISC_INTERLACE_VTOTAL_EVEN	(1 << 8)
#घोषणा DP_MSA_MISC_STEREO_NO_3D		(0 << 9)
#घोषणा DP_MSA_MISC_STEREO_PROG_RIGHT_EYE	(1 << 9)
#घोषणा DP_MSA_MISC_STEREO_PROG_LEFT_EYE	(3 << 9)
/* bits per component क्रम non-RAW */
#घोषणा DP_MSA_MISC_6_BPC			(0 << 5)
#घोषणा DP_MSA_MISC_8_BPC			(1 << 5)
#घोषणा DP_MSA_MISC_10_BPC			(2 << 5)
#घोषणा DP_MSA_MISC_12_BPC			(3 << 5)
#घोषणा DP_MSA_MISC_16_BPC			(4 << 5)
/* bits per component क्रम RAW */
#घोषणा DP_MSA_MISC_RAW_6_BPC			(1 << 5)
#घोषणा DP_MSA_MISC_RAW_7_BPC			(2 << 5)
#घोषणा DP_MSA_MISC_RAW_8_BPC			(3 << 5)
#घोषणा DP_MSA_MISC_RAW_10_BPC			(4 << 5)
#घोषणा DP_MSA_MISC_RAW_12_BPC			(5 << 5)
#घोषणा DP_MSA_MISC_RAW_14_BPC			(6 << 5)
#घोषणा DP_MSA_MISC_RAW_16_BPC			(7 << 5)
/* pixel encoding/colorimetry क्रमmat */
#घोषणा _DP_MSA_MISC_COLOR(misc1_7, misc0_21, misc0_3, misc0_4) \
	((misc1_7) << 15 | (misc0_4) << 4 | (misc0_3) << 3 | ((misc0_21) << 1))
#घोषणा DP_MSA_MISC_COLOR_RGB			_DP_MSA_MISC_COLOR(0, 0, 0, 0)
#घोषणा DP_MSA_MISC_COLOR_CEA_RGB		_DP_MSA_MISC_COLOR(0, 0, 1, 0)
#घोषणा DP_MSA_MISC_COLOR_RGB_WIDE_FIXED	_DP_MSA_MISC_COLOR(0, 3, 0, 0)
#घोषणा DP_MSA_MISC_COLOR_RGB_WIDE_FLOAT	_DP_MSA_MISC_COLOR(0, 3, 0, 1)
#घोषणा DP_MSA_MISC_COLOR_Y_ONLY		_DP_MSA_MISC_COLOR(1, 0, 0, 0)
#घोषणा DP_MSA_MISC_COLOR_RAW			_DP_MSA_MISC_COLOR(1, 1, 0, 0)
#घोषणा DP_MSA_MISC_COLOR_YCBCR_422_BT601	_DP_MSA_MISC_COLOR(0, 1, 1, 0)
#घोषणा DP_MSA_MISC_COLOR_YCBCR_422_BT709	_DP_MSA_MISC_COLOR(0, 1, 1, 1)
#घोषणा DP_MSA_MISC_COLOR_YCBCR_444_BT601	_DP_MSA_MISC_COLOR(0, 2, 1, 0)
#घोषणा DP_MSA_MISC_COLOR_YCBCR_444_BT709	_DP_MSA_MISC_COLOR(0, 2, 1, 1)
#घोषणा DP_MSA_MISC_COLOR_XVYCC_422_BT601	_DP_MSA_MISC_COLOR(0, 1, 0, 0)
#घोषणा DP_MSA_MISC_COLOR_XVYCC_422_BT709	_DP_MSA_MISC_COLOR(0, 1, 0, 1)
#घोषणा DP_MSA_MISC_COLOR_XVYCC_444_BT601	_DP_MSA_MISC_COLOR(0, 2, 0, 0)
#घोषणा DP_MSA_MISC_COLOR_XVYCC_444_BT709	_DP_MSA_MISC_COLOR(0, 2, 0, 1)
#घोषणा DP_MSA_MISC_COLOR_OPRGB			_DP_MSA_MISC_COLOR(0, 0, 1, 1)
#घोषणा DP_MSA_MISC_COLOR_DCI_P3		_DP_MSA_MISC_COLOR(0, 3, 1, 0)
#घोषणा DP_MSA_MISC_COLOR_COLOR_PROखाता		_DP_MSA_MISC_COLOR(0, 3, 1, 1)
#घोषणा DP_MSA_MISC_COLOR_VSC_SDP		(1 << 14)

#घोषणा DP_AUX_MAX_PAYLOAD_BYTES	16

#घोषणा DP_AUX_I2C_WRITE		0x0
#घोषणा DP_AUX_I2C_READ			0x1
#घोषणा DP_AUX_I2C_WRITE_STATUS_UPDATE	0x2
#घोषणा DP_AUX_I2C_MOT			0x4
#घोषणा DP_AUX_NATIVE_WRITE		0x8
#घोषणा DP_AUX_NATIVE_READ		0x9

#घोषणा DP_AUX_NATIVE_REPLY_ACK		(0x0 << 0)
#घोषणा DP_AUX_NATIVE_REPLY_NACK	(0x1 << 0)
#घोषणा DP_AUX_NATIVE_REPLY_DEFER	(0x2 << 0)
#घोषणा DP_AUX_NATIVE_REPLY_MASK	(0x3 << 0)

#घोषणा DP_AUX_I2C_REPLY_ACK		(0x0 << 2)
#घोषणा DP_AUX_I2C_REPLY_NACK		(0x1 << 2)
#घोषणा DP_AUX_I2C_REPLY_DEFER		(0x2 << 2)
#घोषणा DP_AUX_I2C_REPLY_MASK		(0x3 << 2)

/* DPCD Field Address Mapping */

/* Receiver Capability */
#घोषणा DP_DPCD_REV                         0x000
# define DP_DPCD_REV_10                     0x10
# define DP_DPCD_REV_11                     0x11
# define DP_DPCD_REV_12                     0x12
# define DP_DPCD_REV_13                     0x13
# define DP_DPCD_REV_14                     0x14

#घोषणा DP_MAX_LINK_RATE                    0x001

#घोषणा DP_MAX_LANE_COUNT                   0x002
# define DP_MAX_LANE_COUNT_MASK		    0x1f
# define DP_TPS3_SUPPORTED		    (1 << 6) /* 1.2 */
# define DP_ENHANCED_FRAME_CAP		    (1 << 7)

#घोषणा DP_MAX_DOWNSPREAD                   0x003
# define DP_MAX_DOWNSPREAD_0_5		    (1 << 0)
# define DP_STREAM_REGENERATION_STATUS_CAP  (1 << 1) /* 2.0 */
# define DP_NO_AUX_HANDSHAKE_LINK_TRAINING  (1 << 6)
# define DP_TPS4_SUPPORTED                  (1 << 7)

#घोषणा DP_NORP                             0x004

#घोषणा DP_DOWNSTREAMPORT_PRESENT           0x005
# define DP_DWN_STRM_PORT_PRESENT           (1 << 0)
# define DP_DWN_STRM_PORT_TYPE_MASK         0x06
# define DP_DWN_STRM_PORT_TYPE_DP           (0 << 1)
# define DP_DWN_STRM_PORT_TYPE_ANALOG       (1 << 1)
# define DP_DWN_STRM_PORT_TYPE_TMDS         (2 << 1)
# define DP_DWN_STRM_PORT_TYPE_OTHER        (3 << 1)
# define DP_FORMAT_CONVERSION               (1 << 3)
# define DP_DETAILED_CAP_INFO_AVAILABLE	    (1 << 4) /* DPI */

#घोषणा DP_MAIN_LINK_CHANNEL_CODING         0x006
# define DP_CAP_ANSI_8B10B		    (1 << 0)
# define DP_CAP_ANSI_128B132B               (1 << 1) /* 2.0 */

#घोषणा DP_DOWN_STREAM_PORT_COUNT	    0x007
# define DP_PORT_COUNT_MASK		    0x0f
# define DP_MSA_TIMING_PAR_IGNORED	    (1 << 6) /* eDP */
# define DP_OUI_SUPPORT			    (1 << 7)

#घोषणा DP_RECEIVE_PORT_0_CAP_0		    0x008
# define DP_LOCAL_EDID_PRESENT		    (1 << 1)
# define DP_ASSOCIATED_TO_PRECEDING_PORT    (1 << 2)

#घोषणा DP_RECEIVE_PORT_0_BUFFER_SIZE	    0x009

#घोषणा DP_RECEIVE_PORT_1_CAP_0		    0x00a
#घोषणा DP_RECEIVE_PORT_1_BUFFER_SIZE       0x00b

#घोषणा DP_I2C_SPEED_CAP		    0x00c    /* DPI */
# define DP_I2C_SPEED_1K		    0x01
# define DP_I2C_SPEED_5K		    0x02
# define DP_I2C_SPEED_10K		    0x04
# define DP_I2C_SPEED_100K		    0x08
# define DP_I2C_SPEED_400K		    0x10
# define DP_I2C_SPEED_1M		    0x20

#घोषणा DP_EDP_CONFIGURATION_CAP            0x00d   /* XXX 1.2? */
# define DP_ALTERNATE_SCRAMBLER_RESET_CAP   (1 << 0)
# define DP_FRAMING_CHANGE_CAP		    (1 << 1)
# define DP_DPCD_DISPLAY_CONTROL_CAPABLE     (1 << 3) /* edp v1.2 or higher */

#घोषणा DP_TRAINING_AUX_RD_INTERVAL             0x00e   /* XXX 1.2? */
# define DP_TRAINING_AUX_RD_MASK                0x7F    /* DP 1.3 */
# define DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT	(1 << 7) /* DP 1.3 */

#घोषणा DP_ADAPTER_CAP			    0x00f   /* 1.2 */
# define DP_FORCE_LOAD_SENSE_CAP	    (1 << 0)
# define DP_ALTERNATE_I2C_PATTERN_CAP	    (1 << 1)

#घोषणा DP_SUPPORTED_LINK_RATES		    0x010 /* eDP 1.4 */
# define DP_MAX_SUPPORTED_RATES		     8	    /* 16-bit little-endian */

/* Multiple stream transport */
#घोषणा DP_FAUX_CAP			    0x020   /* 1.2 */
# define DP_FAUX_CAP_1			    (1 << 0)

#घोषणा DP_SINK_VIDEO_FALLBACK_FORMATS      0x020   /* 2.0 */
# define DP_FALLBACK_1024x768_60HZ_24BPP    (1 << 0)
# define DP_FALLBACK_1280x720_60HZ_24BPP    (1 << 1)
# define DP_FALLBACK_1920x1080_60HZ_24BPP   (1 << 2)

#घोषणा DP_MSTM_CAP			    0x021   /* 1.2 */
# define DP_MST_CAP			    (1 << 0)
# define DP_SINGLE_STREAM_SIDEBAND_MSG      (1 << 1) /* 2.0 */

#घोषणा DP_NUMBER_OF_AUDIO_ENDPOINTS	    0x022   /* 1.2 */

/* AV_SYNC_DATA_BLOCK                                  1.2 */
#घोषणा DP_AV_GRANULARITY		    0x023
# define DP_AG_FACTOR_MASK		    (0xf << 0)
# define DP_AG_FACTOR_3MS		    (0 << 0)
# define DP_AG_FACTOR_2MS		    (1 << 0)
# define DP_AG_FACTOR_1MS		    (2 << 0)
# define DP_AG_FACTOR_500US		    (3 << 0)
# define DP_AG_FACTOR_200US		    (4 << 0)
# define DP_AG_FACTOR_100US		    (5 << 0)
# define DP_AG_FACTOR_10US		    (6 << 0)
# define DP_AG_FACTOR_1US		    (7 << 0)
# define DP_VG_FACTOR_MASK		    (0xf << 4)
# define DP_VG_FACTOR_3MS		    (0 << 4)
# define DP_VG_FACTOR_2MS		    (1 << 4)
# define DP_VG_FACTOR_1MS		    (2 << 4)
# define DP_VG_FACTOR_500US		    (3 << 4)
# define DP_VG_FACTOR_200US		    (4 << 4)
# define DP_VG_FACTOR_100US		    (5 << 4)

#घोषणा DP_AUD_DEC_LAT0			    0x024
#घोषणा DP_AUD_DEC_LAT1			    0x025

#घोषणा DP_AUD_PP_LAT0			    0x026
#घोषणा DP_AUD_PP_LAT1			    0x027

#घोषणा DP_VID_INTER_LAT		    0x028

#घोषणा DP_VID_PROG_LAT			    0x029

#घोषणा DP_REP_LAT			    0x02a

#घोषणा DP_AUD_DEL_INS0			    0x02b
#घोषणा DP_AUD_DEL_INS1			    0x02c
#घोषणा DP_AUD_DEL_INS2			    0x02d
/* End of AV_SYNC_DATA_BLOCK */

#घोषणा DP_RECEIVER_ALPM_CAP		    0x02e   /* eDP 1.4 */
# define DP_ALPM_CAP			    (1 << 0)

#घोषणा DP_SINK_DEVICE_AUX_FRAME_SYNC_CAP   0x02f   /* eDP 1.4 */
# define DP_AUX_FRAME_SYNC_CAP		    (1 << 0)

#घोषणा DP_GUID				    0x030   /* 1.2 */

#घोषणा DP_DSC_SUPPORT                      0x060   /* DP 1.4 */
# define DP_DSC_DECOMPRESSION_IS_SUPPORTED  (1 << 0)

#घोषणा DP_DSC_REV                          0x061
# define DP_DSC_MAJOR_MASK                  (0xf << 0)
# define DP_DSC_MINOR_MASK                  (0xf << 4)
# define DP_DSC_MAJOR_SHIFT                 0
# define DP_DSC_MINOR_SHIFT                 4

#घोषणा DP_DSC_RC_BUF_BLK_SIZE              0x062
# define DP_DSC_RC_BUF_BLK_SIZE_1           0x0
# define DP_DSC_RC_BUF_BLK_SIZE_4           0x1
# define DP_DSC_RC_BUF_BLK_SIZE_16          0x2
# define DP_DSC_RC_BUF_BLK_SIZE_64          0x3

#घोषणा DP_DSC_RC_BUF_SIZE                  0x063

#घोषणा DP_DSC_SLICE_CAP_1                  0x064
# define DP_DSC_1_PER_DP_DSC_SINK           (1 << 0)
# define DP_DSC_2_PER_DP_DSC_SINK           (1 << 1)
# define DP_DSC_4_PER_DP_DSC_SINK           (1 << 3)
# define DP_DSC_6_PER_DP_DSC_SINK           (1 << 4)
# define DP_DSC_8_PER_DP_DSC_SINK           (1 << 5)
# define DP_DSC_10_PER_DP_DSC_SINK          (1 << 6)
# define DP_DSC_12_PER_DP_DSC_SINK          (1 << 7)

#घोषणा DP_DSC_LINE_BUF_BIT_DEPTH           0x065
# define DP_DSC_LINE_BUF_BIT_DEPTH_MASK     (0xf << 0)
# define DP_DSC_LINE_BUF_BIT_DEPTH_9        0x0
# define DP_DSC_LINE_BUF_BIT_DEPTH_10       0x1
# define DP_DSC_LINE_BUF_BIT_DEPTH_11       0x2
# define DP_DSC_LINE_BUF_BIT_DEPTH_12       0x3
# define DP_DSC_LINE_BUF_BIT_DEPTH_13       0x4
# define DP_DSC_LINE_BUF_BIT_DEPTH_14       0x5
# define DP_DSC_LINE_BUF_BIT_DEPTH_15       0x6
# define DP_DSC_LINE_BUF_BIT_DEPTH_16       0x7
# define DP_DSC_LINE_BUF_BIT_DEPTH_8        0x8

#घोषणा DP_DSC_BLK_PREDICTION_SUPPORT       0x066
# define DP_DSC_BLK_PREDICTION_IS_SUPPORTED (1 << 0)

#घोषणा DP_DSC_MAX_BITS_PER_PIXEL_LOW       0x067   /* eDP 1.4 */

#घोषणा DP_DSC_MAX_BITS_PER_PIXEL_HI        0x068   /* eDP 1.4 */
# define DP_DSC_MAX_BITS_PER_PIXEL_HI_MASK  (0x3 << 0)
# define DP_DSC_MAX_BITS_PER_PIXEL_HI_SHIFT 8

#घोषणा DP_DSC_DEC_COLOR_FORMAT_CAP         0x069
# define DP_DSC_RGB                         (1 << 0)
# define DP_DSC_YCbCr444                    (1 << 1)
# define DP_DSC_YCbCr422_Simple             (1 << 2)
# define DP_DSC_YCbCr422_Native             (1 << 3)
# define DP_DSC_YCbCr420_Native             (1 << 4)

#घोषणा DP_DSC_DEC_COLOR_DEPTH_CAP          0x06A
# define DP_DSC_8_BPC                       (1 << 1)
# define DP_DSC_10_BPC                      (1 << 2)
# define DP_DSC_12_BPC                      (1 << 3)

#घोषणा DP_DSC_PEAK_THROUGHPUT              0x06B
# define DP_DSC_THROUGHPUT_MODE_0_MASK      (0xf << 0)
# define DP_DSC_THROUGHPUT_MODE_0_SHIFT     0
# define DP_DSC_THROUGHPUT_MODE_0_UNSUPPORTED 0
# define DP_DSC_THROUGHPUT_MODE_0_340       (1 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_400       (2 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_450       (3 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_500       (4 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_550       (5 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_600       (6 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_650       (7 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_700       (8 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_750       (9 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_800       (10 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_850       (11 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_900       (12 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_950       (13 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_1000      (14 << 0)
# define DP_DSC_THROUGHPUT_MODE_0_170       (15 << 0) /* 1.4a */
# define DP_DSC_THROUGHPUT_MODE_1_MASK      (0xf << 4)
# define DP_DSC_THROUGHPUT_MODE_1_SHIFT     4
# define DP_DSC_THROUGHPUT_MODE_1_UNSUPPORTED 0
# define DP_DSC_THROUGHPUT_MODE_1_340       (1 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_400       (2 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_450       (3 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_500       (4 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_550       (5 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_600       (6 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_650       (7 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_700       (8 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_750       (9 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_800       (10 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_850       (11 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_900       (12 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_950       (13 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_1000      (14 << 4)
# define DP_DSC_THROUGHPUT_MODE_1_170       (15 << 4)

#घोषणा DP_DSC_MAX_SLICE_WIDTH              0x06C
#घोषणा DP_DSC_MIN_SLICE_WIDTH_VALUE        2560
#घोषणा DP_DSC_SLICE_WIDTH_MULTIPLIER       320

#घोषणा DP_DSC_SLICE_CAP_2                  0x06D
# define DP_DSC_16_PER_DP_DSC_SINK          (1 << 0)
# define DP_DSC_20_PER_DP_DSC_SINK          (1 << 1)
# define DP_DSC_24_PER_DP_DSC_SINK          (1 << 2)

#घोषणा DP_DSC_BITS_PER_PIXEL_INC           0x06F
# define DP_DSC_BITS_PER_PIXEL_1_16         0x0
# define DP_DSC_BITS_PER_PIXEL_1_8          0x1
# define DP_DSC_BITS_PER_PIXEL_1_4          0x2
# define DP_DSC_BITS_PER_PIXEL_1_2          0x3
# define DP_DSC_BITS_PER_PIXEL_1            0x4

#घोषणा DP_PSR_SUPPORT                      0x070   /* XXX 1.2? */
# define DP_PSR_IS_SUPPORTED                1
# define DP_PSR2_IS_SUPPORTED		    2	    /* eDP 1.4 */
# define DP_PSR2_WITH_Y_COORD_IS_SUPPORTED  3	    /* eDP 1.4a */

#घोषणा DP_PSR_CAPS                         0x071   /* XXX 1.2? */
# define DP_PSR_NO_TRAIN_ON_EXIT            1
# define DP_PSR_SETUP_TIME_330              (0 << 1)
# define DP_PSR_SETUP_TIME_275              (1 << 1)
# define DP_PSR_SETUP_TIME_220              (2 << 1)
# define DP_PSR_SETUP_TIME_165              (3 << 1)
# define DP_PSR_SETUP_TIME_110              (4 << 1)
# define DP_PSR_SETUP_TIME_55               (5 << 1)
# define DP_PSR_SETUP_TIME_0                (6 << 1)
# define DP_PSR_SETUP_TIME_MASK             (7 << 1)
# define DP_PSR_SETUP_TIME_SHIFT            1
# define DP_PSR2_SU_Y_COORDINATE_REQUIRED   (1 << 4)  /* eDP 1.4a */
# define DP_PSR2_SU_GRANULARITY_REQUIRED    (1 << 5)  /* eDP 1.4b */

#घोषणा DP_PSR2_SU_X_GRANULARITY	    0x072 /* eDP 1.4b */
#घोषणा DP_PSR2_SU_Y_GRANULARITY	    0x074 /* eDP 1.4b */

/*
 * 0x80-0x8f describe करोwnstream port capabilities, but there are two layouts
 * based on whether DP_DETAILED_CAP_INFO_AVAILABLE was set.  If it was not,
 * each port's descriptor is one byte wide.  If it was set, each port's is
 * four bytes wide, starting with the one byte from the base info.  As of
 * DP पूर्णांकerop v1.1a only VGA defines additional detail.
 */

/* offset 0 */
#घोषणा DP_DOWNSTREAM_PORT_0		    0x80
# define DP_DS_PORT_TYPE_MASK		    (7 << 0)
# define DP_DS_PORT_TYPE_DP		    0
# define DP_DS_PORT_TYPE_VGA		    1
# define DP_DS_PORT_TYPE_DVI		    2
# define DP_DS_PORT_TYPE_HDMI		    3
# define DP_DS_PORT_TYPE_NON_EDID	    4
# define DP_DS_PORT_TYPE_DP_DUALMODE        5
# define DP_DS_PORT_TYPE_WIRELESS           6
# define DP_DS_PORT_HPD			    (1 << 3)
# define DP_DS_NON_EDID_MASK		    (0xf << 4)
# define DP_DS_NON_EDID_720x480i_60	    (1 << 4)
# define DP_DS_NON_EDID_720x480i_50	    (2 << 4)
# define DP_DS_NON_EDID_1920x1080i_60	    (3 << 4)
# define DP_DS_NON_EDID_1920x1080i_50	    (4 << 4)
# define DP_DS_NON_EDID_1280x720_60	    (5 << 4)
# define DP_DS_NON_EDID_1280x720_50	    (7 << 4)
/* offset 1 क्रम VGA is maximum megapixels per second / 8 */
/* offset 1 क्रम DVI/HDMI is maximum TMDS घड़ी in Mbps / 2.5 */
/* offset 2 क्रम VGA/DVI/HDMI */
# define DP_DS_MAX_BPC_MASK	            (3 << 0)
# define DP_DS_8BPC		            0
# define DP_DS_10BPC		            1
# define DP_DS_12BPC		            2
# define DP_DS_16BPC		            3
/* HDMI2.1 PCON FRL CONFIGURATION */
# define DP_PCON_MAX_FRL_BW                 (7 << 2)
# define DP_PCON_MAX_0GBPS                  (0 << 2)
# define DP_PCON_MAX_9GBPS                  (1 << 2)
# define DP_PCON_MAX_18GBPS                 (2 << 2)
# define DP_PCON_MAX_24GBPS                 (3 << 2)
# define DP_PCON_MAX_32GBPS                 (4 << 2)
# define DP_PCON_MAX_40GBPS                 (5 << 2)
# define DP_PCON_MAX_48GBPS                 (6 << 2)
# define DP_PCON_SOURCE_CTL_MODE            (1 << 5)

/* offset 3 क्रम DVI */
# define DP_DS_DVI_DUAL_LINK		    (1 << 1)
# define DP_DS_DVI_HIGH_COLOR_DEPTH	    (1 << 2)
/* offset 3 क्रम HDMI */
# define DP_DS_HDMI_FRAME_SEQ_TO_FRAME_PACK (1 << 0)
# define DP_DS_HDMI_YCBCR422_PASS_THROUGH   (1 << 1)
# define DP_DS_HDMI_YCBCR420_PASS_THROUGH   (1 << 2)
# define DP_DS_HDMI_YCBCR444_TO_422_CONV    (1 << 3)
# define DP_DS_HDMI_YCBCR444_TO_420_CONV    (1 << 4)

/*
 * VESA DP-to-HDMI PCON Specअगरication adds caps क्रम colorspace
 * conversion in DFP cap DPCD 83h. Sec6.1 Table-3.
 * Based on the available support the source can enable
 * color conversion by writing पूर्णांकo PROTOCOL_COVERTER_CONTROL_2
 * DPCD 3052h.
 */
# define DP_DS_HDMI_BT601_RGB_YCBCR_CONV    (1 << 5)
# define DP_DS_HDMI_BT709_RGB_YCBCR_CONV    (1 << 6)
# define DP_DS_HDMI_BT2020_RGB_YCBCR_CONV   (1 << 7)

#घोषणा DP_MAX_DOWNSTREAM_PORTS		    0x10

/* DP Forward error Correction Registers */
#घोषणा DP_FEC_CAPABILITY		    0x090    /* 1.4 */
# define DP_FEC_CAPABLE			    (1 << 0)
# define DP_FEC_UNCORR_BLK_ERROR_COUNT_CAP  (1 << 1)
# define DP_FEC_CORR_BLK_ERROR_COUNT_CAP    (1 << 2)
# define DP_FEC_BIT_ERROR_COUNT_CAP	    (1 << 3)

/* DP-HDMI2.1 PCON DSC ENCODER SUPPORT */
#घोषणा DP_PCON_DSC_ENCODER_CAP_SIZE        0xC	/* 0x9E - 0x92 */
#घोषणा DP_PCON_DSC_ENCODER                 0x092
# define DP_PCON_DSC_ENCODER_SUPPORTED      (1 << 0)
# define DP_PCON_DSC_PPS_ENC_OVERRIDE       (1 << 1)

/* DP-HDMI2.1 PCON DSC Version */
#घोषणा DP_PCON_DSC_VERSION                 0x093
# define DP_PCON_DSC_MAJOR_MASK		    (0xF << 0)
# define DP_PCON_DSC_MINOR_MASK		    (0xF << 4)
# define DP_PCON_DSC_MAJOR_SHIFT	    0
# define DP_PCON_DSC_MINOR_SHIFT	    4

/* DP-HDMI2.1 PCON DSC RC Buffer block size */
#घोषणा DP_PCON_DSC_RC_BUF_BLK_INFO	    0x094
# define DP_PCON_DSC_RC_BUF_BLK_SIZE	    (0x3 << 0)
# define DP_PCON_DSC_RC_BUF_BLK_1KB	    0
# define DP_PCON_DSC_RC_BUF_BLK_4KB	    1
# define DP_PCON_DSC_RC_BUF_BLK_16KB	    2
# define DP_PCON_DSC_RC_BUF_BLK_64KB	    3

/* DP-HDMI2.1 PCON DSC RC Buffer size */
#घोषणा DP_PCON_DSC_RC_BUF_SIZE		    0x095

/* DP-HDMI2.1 PCON DSC Slice capabilities-1 */
#घोषणा DP_PCON_DSC_SLICE_CAP_1		    0x096
# define DP_PCON_DSC_1_PER_DSC_ENC     (0x1 << 0)
# define DP_PCON_DSC_2_PER_DSC_ENC     (0x1 << 1)
# define DP_PCON_DSC_4_PER_DSC_ENC     (0x1 << 3)
# define DP_PCON_DSC_6_PER_DSC_ENC     (0x1 << 4)
# define DP_PCON_DSC_8_PER_DSC_ENC     (0x1 << 5)
# define DP_PCON_DSC_10_PER_DSC_ENC    (0x1 << 6)
# define DP_PCON_DSC_12_PER_DSC_ENC    (0x1 << 7)

#घोषणा DP_PCON_DSC_BUF_BIT_DEPTH	    0x097
# define DP_PCON_DSC_BIT_DEPTH_MASK	    (0xF << 0)
# define DP_PCON_DSC_DEPTH_9_BITS	    0
# define DP_PCON_DSC_DEPTH_10_BITS	    1
# define DP_PCON_DSC_DEPTH_11_BITS	    2
# define DP_PCON_DSC_DEPTH_12_BITS	    3
# define DP_PCON_DSC_DEPTH_13_BITS	    4
# define DP_PCON_DSC_DEPTH_14_BITS	    5
# define DP_PCON_DSC_DEPTH_15_BITS	    6
# define DP_PCON_DSC_DEPTH_16_BITS	    7
# define DP_PCON_DSC_DEPTH_8_BITS	    8

#घोषणा DP_PCON_DSC_BLOCK_PREDICTION	    0x098
# define DP_PCON_DSC_BLOCK_PRED_SUPPORT	    (0x1 << 0)

#घोषणा DP_PCON_DSC_ENC_COLOR_FMT_CAP	    0x099
# define DP_PCON_DSC_ENC_RGB		    (0x1 << 0)
# define DP_PCON_DSC_ENC_YUV444		    (0x1 << 1)
# define DP_PCON_DSC_ENC_YUV422_S	    (0x1 << 2)
# define DP_PCON_DSC_ENC_YUV422_N	    (0x1 << 3)
# define DP_PCON_DSC_ENC_YUV420_N	    (0x1 << 4)

#घोषणा DP_PCON_DSC_ENC_COLOR_DEPTH_CAP	    0x09A
# define DP_PCON_DSC_ENC_8BPC		    (0x1 << 1)
# define DP_PCON_DSC_ENC_10BPC		    (0x1 << 2)
# define DP_PCON_DSC_ENC_12BPC		    (0x1 << 3)

#घोषणा DP_PCON_DSC_MAX_SLICE_WIDTH	    0x09B

/* DP-HDMI2.1 PCON DSC Slice capabilities-2 */
#घोषणा DP_PCON_DSC_SLICE_CAP_2             0x09C
# define DP_PCON_DSC_16_PER_DSC_ENC	    (0x1 << 0)
# define DP_PCON_DSC_20_PER_DSC_ENC         (0x1 << 1)
# define DP_PCON_DSC_24_PER_DSC_ENC         (0x1 << 2)

/* DP-HDMI2.1 PCON HDMI TX Encoder Bits/pixel increment */
#घोषणा DP_PCON_DSC_BPP_INCR		    0x09E
# define DP_PCON_DSC_BPP_INCR_MASK	    (0x7 << 0)
# define DP_PCON_DSC_ONE_16TH_BPP	    0
# define DP_PCON_DSC_ONE_8TH_BPP	    1
# define DP_PCON_DSC_ONE_4TH_BPP	    2
# define DP_PCON_DSC_ONE_HALF_BPP	    3
# define DP_PCON_DSC_ONE_BPP		    4

/* DP Extended DSC Capabilities */
#घोषणा DP_DSC_BRANCH_OVERALL_THROUGHPUT_0  0x0a0   /* DP 1.4a SCR */
#घोषणा DP_DSC_BRANCH_OVERALL_THROUGHPUT_1  0x0a1
#घोषणा DP_DSC_BRANCH_MAX_LINE_WIDTH        0x0a2

/* Link Configuration */
#घोषणा	DP_LINK_BW_SET		            0x100
# define DP_LINK_RATE_TABLE		    0x00    /* eDP 1.4 */
# define DP_LINK_BW_1_62		    0x06
# define DP_LINK_BW_2_7			    0x0a
# define DP_LINK_BW_5_4			    0x14    /* 1.2 */
# define DP_LINK_BW_8_1			    0x1e    /* 1.4 */
# define DP_LINK_BW_10                      0x01    /* 2.0 128b/132b Link Layer */
# define DP_LINK_BW_13_5                    0x04    /* 2.0 128b/132b Link Layer */
# define DP_LINK_BW_20                      0x02    /* 2.0 128b/132b Link Layer */

#घोषणा DP_LANE_COUNT_SET	            0x101
# define DP_LANE_COUNT_MASK		    0x0f
# define DP_LANE_COUNT_ENHANCED_FRAME_EN    (1 << 7)

#घोषणा DP_TRAINING_PATTERN_SET	            0x102
# define DP_TRAINING_PATTERN_DISABLE	    0
# define DP_TRAINING_PATTERN_1		    1
# define DP_TRAINING_PATTERN_2		    2
# define DP_TRAINING_PATTERN_3		    3	    /* 1.2 */
# define DP_TRAINING_PATTERN_4              7       /* 1.4 */
# define DP_TRAINING_PATTERN_MASK	    0x3
# define DP_TRAINING_PATTERN_MASK_1_4	    0xf

/* DPCD 1.1 only. For DPCD >= 1.2 see per-lane DP_LINK_QUAL_LANEn_SET */
# define DP_LINK_QUAL_PATTERN_11_DISABLE    (0 << 2)
# define DP_LINK_QUAL_PATTERN_11_D10_2	    (1 << 2)
# define DP_LINK_QUAL_PATTERN_11_ERROR_RATE (2 << 2)
# define DP_LINK_QUAL_PATTERN_11_PRBS7	    (3 << 2)
# define DP_LINK_QUAL_PATTERN_11_MASK	    (3 << 2)

# define DP_RECOVERED_CLOCK_OUT_EN	    (1 << 4)
# define DP_LINK_SCRAMBLING_DISABLE	    (1 << 5)

# define DP_SYMBOL_ERROR_COUNT_BOTH	    (0 << 6)
# define DP_SYMBOL_ERROR_COUNT_DISPARITY    (1 << 6)
# define DP_SYMBOL_ERROR_COUNT_SYMBOL	    (2 << 6)
# define DP_SYMBOL_ERROR_COUNT_MASK	    (3 << 6)

#घोषणा DP_TRAINING_LANE0_SET		    0x103
#घोषणा DP_TRAINING_LANE1_SET		    0x104
#घोषणा DP_TRAINING_LANE2_SET		    0x105
#घोषणा DP_TRAINING_LANE3_SET		    0x106

# define DP_TRAIN_VOLTAGE_SWING_MASK	    0x3
# define DP_TRAIN_VOLTAGE_SWING_SHIFT	    0
# define DP_TRAIN_MAX_SWING_REACHED	    (1 << 2)
# define DP_TRAIN_VOLTAGE_SWING_LEVEL_0 (0 << 0)
# define DP_TRAIN_VOLTAGE_SWING_LEVEL_1 (1 << 0)
# define DP_TRAIN_VOLTAGE_SWING_LEVEL_2 (2 << 0)
# define DP_TRAIN_VOLTAGE_SWING_LEVEL_3 (3 << 0)

# define DP_TRAIN_PRE_EMPHASIS_MASK	    (3 << 3)
# define DP_TRAIN_PRE_EMPH_LEVEL_0		(0 << 3)
# define DP_TRAIN_PRE_EMPH_LEVEL_1		(1 << 3)
# define DP_TRAIN_PRE_EMPH_LEVEL_2		(2 << 3)
# define DP_TRAIN_PRE_EMPH_LEVEL_3		(3 << 3)

# define DP_TRAIN_PRE_EMPHASIS_SHIFT	    3
# define DP_TRAIN_MAX_PRE_EMPHASIS_REACHED  (1 << 5)

# define DP_TX_FFE_PRESET_VALUE_MASK        (0xf << 0) /* 2.0 128b/132b Link Layer */

#घोषणा DP_DOWNSPREAD_CTRL		    0x107
# define DP_SPREAD_AMP_0_5		    (1 << 4)
# define DP_MSA_TIMING_PAR_IGNORE_EN	    (1 << 7) /* eDP */

#घोषणा DP_MAIN_LINK_CHANNEL_CODING_SET	    0x108
# define DP_SET_ANSI_8B10B		    (1 << 0)
# define DP_SET_ANSI_128B132B               (1 << 1)

#घोषणा DP_I2C_SPEED_CONTROL_STATUS	    0x109   /* DPI */
/* biपंचांगask as क्रम DP_I2C_SPEED_CAP */

#घोषणा DP_EDP_CONFIGURATION_SET            0x10a   /* XXX 1.2? */
# define DP_ALTERNATE_SCRAMBLER_RESET_ENABLE (1 << 0)
# define DP_FRAMING_CHANGE_ENABLE	    (1 << 1)
# define DP_PANEL_SELF_TEST_ENABLE	    (1 << 7)

#घोषणा DP_LINK_QUAL_LANE0_SET		    0x10b   /* DPCD >= 1.2 */
#घोषणा DP_LINK_QUAL_LANE1_SET		    0x10c
#घोषणा DP_LINK_QUAL_LANE2_SET		    0x10d
#घोषणा DP_LINK_QUAL_LANE3_SET		    0x10e
# define DP_LINK_QUAL_PATTERN_DISABLE	    0
# define DP_LINK_QUAL_PATTERN_D10_2	    1
# define DP_LINK_QUAL_PATTERN_ERROR_RATE    2
# define DP_LINK_QUAL_PATTERN_PRBS7	    3
# define DP_LINK_QUAL_PATTERN_80BIT_CUSTOM  4
# define DP_LINK_QUAL_PATTERN_CP2520_PAT_1  5
# define DP_LINK_QUAL_PATTERN_CP2520_PAT_2  6
# define DP_LINK_QUAL_PATTERN_CP2520_PAT_3  7
/* DP 2.0 UHBR10, UHBR13.5, UHBR20 */
# define DP_LINK_QUAL_PATTERN_128B132B_TPS1 0x08
# define DP_LINK_QUAL_PATTERN_128B132B_TPS2 0x10
# define DP_LINK_QUAL_PATTERN_PRSBS9        0x18
# define DP_LINK_QUAL_PATTERN_PRSBS11       0x20
# define DP_LINK_QUAL_PATTERN_PRSBS15       0x28
# define DP_LINK_QUAL_PATTERN_PRSBS23       0x30
# define DP_LINK_QUAL_PATTERN_PRSBS31       0x38
# define DP_LINK_QUAL_PATTERN_CUSTOM        0x40
# define DP_LINK_QUAL_PATTERN_SQUARE        0x48

#घोषणा DP_TRAINING_LANE0_1_SET2	    0x10f
#घोषणा DP_TRAINING_LANE2_3_SET2	    0x110
# define DP_LANE02_POST_CURSOR2_SET_MASK    (3 << 0)
# define DP_LANE02_MAX_POST_CURSOR2_REACHED (1 << 2)
# define DP_LANE13_POST_CURSOR2_SET_MASK    (3 << 4)
# define DP_LANE13_MAX_POST_CURSOR2_REACHED (1 << 6)

#घोषणा DP_MSTM_CTRL			    0x111   /* 1.2 */
# define DP_MST_EN			    (1 << 0)
# define DP_UP_REQ_EN			    (1 << 1)
# define DP_UPSTREAM_IS_SRC		    (1 << 2)

#घोषणा DP_AUDIO_DELAY0			    0x112   /* 1.2 */
#घोषणा DP_AUDIO_DELAY1			    0x113
#घोषणा DP_AUDIO_DELAY2			    0x114

#घोषणा DP_LINK_RATE_SET		    0x115   /* eDP 1.4 */
# define DP_LINK_RATE_SET_SHIFT		    0
# define DP_LINK_RATE_SET_MASK		    (7 << 0)

#घोषणा DP_RECEIVER_ALPM_CONFIG		    0x116   /* eDP 1.4 */
# define DP_ALPM_ENABLE			    (1 << 0)
# define DP_ALPM_LOCK_ERROR_IRQ_HPD_ENABLE  (1 << 1)

#घोषणा DP_SINK_DEVICE_AUX_FRAME_SYNC_CONF  0x117   /* eDP 1.4 */
# define DP_AUX_FRAME_SYNC_ENABLE	    (1 << 0)
# define DP_IRQ_HPD_ENABLE		    (1 << 1)

#घोषणा DP_UPSTREAM_DEVICE_DP_PWR_NEED	    0x118   /* 1.2 */
# define DP_PWR_NOT_NEEDED		    (1 << 0)

#घोषणा DP_FEC_CONFIGURATION		    0x120    /* 1.4 */
# define DP_FEC_READY			    (1 << 0)
# define DP_FEC_ERR_COUNT_SEL_MASK	    (7 << 1)
# define DP_FEC_ERR_COUNT_DIS		    (0 << 1)
# define DP_FEC_UNCORR_BLK_ERROR_COUNT	    (1 << 1)
# define DP_FEC_CORR_BLK_ERROR_COUNT	    (2 << 1)
# define DP_FEC_BIT_ERROR_COUNT		    (3 << 1)
# define DP_FEC_LANE_SELECT_MASK	    (3 << 4)
# define DP_FEC_LANE_0_SELECT		    (0 << 4)
# define DP_FEC_LANE_1_SELECT		    (1 << 4)
# define DP_FEC_LANE_2_SELECT		    (2 << 4)
# define DP_FEC_LANE_3_SELECT		    (3 << 4)

#घोषणा DP_AUX_FRAME_SYNC_VALUE		    0x15c   /* eDP 1.4 */
# define DP_AUX_FRAME_SYNC_VALID	    (1 << 0)

#घोषणा DP_DSC_ENABLE                       0x160   /* DP 1.4 */
# define DP_DECOMPRESSION_EN                (1 << 0)

#घोषणा DP_PSR_EN_CFG			    0x170   /* XXX 1.2? */
# define DP_PSR_ENABLE			    (1 << 0)
# define DP_PSR_MAIN_LINK_ACTIVE	    (1 << 1)
# define DP_PSR_CRC_VERIFICATION	    (1 << 2)
# define DP_PSR_FRAME_CAPTURE		    (1 << 3)
# define DP_PSR_SELECTIVE_UPDATE	    (1 << 4)
# define DP_PSR_IRQ_HPD_WITH_CRC_ERRORS     (1 << 5)
# define DP_PSR_ENABLE_PSR2		    (1 << 6) /* eDP 1.4a */

#घोषणा DP_ADAPTER_CTRL			    0x1a0
# define DP_ADAPTER_CTRL_FORCE_LOAD_SENSE   (1 << 0)

#घोषणा DP_BRANCH_DEVICE_CTRL		    0x1a1
# define DP_BRANCH_DEVICE_IRQ_HPD	    (1 << 0)

#घोषणा DP_PAYLOAD_ALLOCATE_SET		    0x1c0
#घोषणा DP_PAYLOAD_ALLOCATE_START_TIME_SLOT 0x1c1
#घोषणा DP_PAYLOAD_ALLOCATE_TIME_SLOT_COUNT 0x1c2

/* Link/Sink Device Status */
#घोषणा DP_SINK_COUNT			    0x200
/* prior to 1.2 bit 7 was reserved mbz */
# define DP_GET_SINK_COUNT(x)		    ((((x) & 0x80) >> 1) | ((x) & 0x3f))
# define DP_SINK_CP_READY		    (1 << 6)

#घोषणा DP_DEVICE_SERVICE_IRQ_VECTOR	    0x201
# define DP_REMOTE_CONTROL_COMMAND_PENDING  (1 << 0)
# define DP_AUTOMATED_TEST_REQUEST	    (1 << 1)
# define DP_CP_IRQ			    (1 << 2)
# define DP_MCCS_IRQ			    (1 << 3)
# define DP_DOWN_REP_MSG_RDY		    (1 << 4) /* 1.2 MST */
# define DP_UP_REQ_MSG_RDY		    (1 << 5) /* 1.2 MST */
# define DP_SINK_SPECIFIC_IRQ		    (1 << 6)

#घोषणा DP_LANE0_1_STATUS		    0x202
#घोषणा DP_LANE2_3_STATUS		    0x203
# define DP_LANE_CR_DONE		    (1 << 0)
# define DP_LANE_CHANNEL_EQ_DONE	    (1 << 1)
# define DP_LANE_SYMBOL_LOCKED		    (1 << 2)

#घोषणा DP_CHANNEL_EQ_BITS (DP_LANE_CR_DONE |		\
			    DP_LANE_CHANNEL_EQ_DONE |	\
			    DP_LANE_SYMBOL_LOCKED)

#घोषणा DP_LANE_ALIGN_STATUS_UPDATED	    0x204

#घोषणा DP_INTERLANE_ALIGN_DONE		    (1 << 0)
#घोषणा DP_DOWNSTREAM_PORT_STATUS_CHANGED   (1 << 6)
#घोषणा DP_LINK_STATUS_UPDATED		    (1 << 7)

#घोषणा DP_SINK_STATUS			    0x205
# define DP_RECEIVE_PORT_0_STATUS	    (1 << 0)
# define DP_RECEIVE_PORT_1_STATUS	    (1 << 1)
# define DP_STREAM_REGENERATION_STATUS      (1 << 2) /* 2.0 */

#घोषणा DP_ADJUST_REQUEST_LANE0_1	    0x206
#घोषणा DP_ADJUST_REQUEST_LANE2_3	    0x207
# define DP_ADJUST_VOLTAGE_SWING_LANE0_MASK  0x03
# define DP_ADJUST_VOLTAGE_SWING_LANE0_SHIFT 0
# define DP_ADJUST_PRE_EMPHASIS_LANE0_MASK   0x0c
# define DP_ADJUST_PRE_EMPHASIS_LANE0_SHIFT  2
# define DP_ADJUST_VOLTAGE_SWING_LANE1_MASK  0x30
# define DP_ADJUST_VOLTAGE_SWING_LANE1_SHIFT 4
# define DP_ADJUST_PRE_EMPHASIS_LANE1_MASK   0xc0
# define DP_ADJUST_PRE_EMPHASIS_LANE1_SHIFT  6

/* DP 2.0 128b/132b Link Layer */
# define DP_ADJUST_TX_FFE_PRESET_LANE0_MASK  (0xf << 0)
# define DP_ADJUST_TX_FFE_PRESET_LANE0_SHIFT 0
# define DP_ADJUST_TX_FFE_PRESET_LANE1_MASK  (0xf << 4)
# define DP_ADJUST_TX_FFE_PRESET_LANE1_SHIFT 4

#घोषणा DP_ADJUST_REQUEST_POST_CURSOR2      0x20c
# define DP_ADJUST_POST_CURSOR2_LANE0_MASK  0x03
# define DP_ADJUST_POST_CURSOR2_LANE0_SHIFT 0
# define DP_ADJUST_POST_CURSOR2_LANE1_MASK  0x0c
# define DP_ADJUST_POST_CURSOR2_LANE1_SHIFT 2
# define DP_ADJUST_POST_CURSOR2_LANE2_MASK  0x30
# define DP_ADJUST_POST_CURSOR2_LANE2_SHIFT 4
# define DP_ADJUST_POST_CURSOR2_LANE3_MASK  0xc0
# define DP_ADJUST_POST_CURSOR2_LANE3_SHIFT 6

#घोषणा DP_TEST_REQUEST			    0x218
# define DP_TEST_LINK_TRAINING		    (1 << 0)
# define DP_TEST_LINK_VIDEO_PATTERN	    (1 << 1)
# define DP_TEST_LINK_EDID_READ		    (1 << 2)
# define DP_TEST_LINK_PHY_TEST_PATTERN	    (1 << 3) /* DPCD >= 1.1 */
# define DP_TEST_LINK_FAUX_PATTERN	    (1 << 4) /* DPCD >= 1.2 */
# define DP_TEST_LINK_AUDIO_PATTERN         (1 << 5) /* DPCD >= 1.2 */
# define DP_TEST_LINK_AUDIO_DISABLED_VIDEO  (1 << 6) /* DPCD >= 1.2 */

#घोषणा DP_TEST_LINK_RATE		    0x219
# define DP_LINK_RATE_162		    (0x6)
# define DP_LINK_RATE_27		    (0xa)

#घोषणा DP_TEST_LANE_COUNT		    0x220

#घोषणा DP_TEST_PATTERN			    0x221
# define DP_NO_TEST_PATTERN                 0x0
# define DP_COLOR_RAMP                      0x1
# define DP_BLACK_AND_WHITE_VERTICAL_LINES  0x2
# define DP_COLOR_SQUARE                    0x3

#घोषणा DP_TEST_H_TOTAL_HI                  0x222
#घोषणा DP_TEST_H_TOTAL_LO                  0x223

#घोषणा DP_TEST_V_TOTAL_HI                  0x224
#घोषणा DP_TEST_V_TOTAL_LO                  0x225

#घोषणा DP_TEST_H_START_HI                  0x226
#घोषणा DP_TEST_H_START_LO                  0x227

#घोषणा DP_TEST_V_START_HI                  0x228
#घोषणा DP_TEST_V_START_LO                  0x229

#घोषणा DP_TEST_HSYNC_HI                    0x22A
# define DP_TEST_HSYNC_POLARITY             (1 << 7)
# define DP_TEST_HSYNC_WIDTH_HI_MASK        (127 << 0)
#घोषणा DP_TEST_HSYNC_WIDTH_LO              0x22B

#घोषणा DP_TEST_VSYNC_HI                    0x22C
# define DP_TEST_VSYNC_POLARITY             (1 << 7)
# define DP_TEST_VSYNC_WIDTH_HI_MASK        (127 << 0)
#घोषणा DP_TEST_VSYNC_WIDTH_LO              0x22D

#घोषणा DP_TEST_H_WIDTH_HI                  0x22E
#घोषणा DP_TEST_H_WIDTH_LO                  0x22F

#घोषणा DP_TEST_V_HEIGHT_HI                 0x230
#घोषणा DP_TEST_V_HEIGHT_LO                 0x231

#घोषणा DP_TEST_MISC0                       0x232
# define DP_TEST_SYNC_CLOCK                 (1 << 0)
# define DP_TEST_COLOR_FORMAT_MASK          (3 << 1)
# define DP_TEST_COLOR_FORMAT_SHIFT         1
# define DP_COLOR_FORMAT_RGB                (0 << 1)
# define DP_COLOR_FORMAT_YCbCr422           (1 << 1)
# define DP_COLOR_FORMAT_YCbCr444           (2 << 1)
# define DP_TEST_DYNAMIC_RANGE_VESA         (0 << 3)
# define DP_TEST_DYNAMIC_RANGE_CEA          (1 << 3)
# define DP_TEST_YCBCR_COEFFICIENTS         (1 << 4)
# define DP_YCBCR_COEFFICIENTS_ITU601       (0 << 4)
# define DP_YCBCR_COEFFICIENTS_ITU709       (1 << 4)
# define DP_TEST_BIT_DEPTH_MASK             (7 << 5)
# define DP_TEST_BIT_DEPTH_SHIFT            5
# define DP_TEST_BIT_DEPTH_6                (0 << 5)
# define DP_TEST_BIT_DEPTH_8                (1 << 5)
# define DP_TEST_BIT_DEPTH_10               (2 << 5)
# define DP_TEST_BIT_DEPTH_12               (3 << 5)
# define DP_TEST_BIT_DEPTH_16               (4 << 5)

#घोषणा DP_TEST_MISC1                       0x233
# define DP_TEST_REFRESH_DENOMINATOR        (1 << 0)
# define DP_TEST_INTERLACED                 (1 << 1)

#घोषणा DP_TEST_REFRESH_RATE_NUMERATOR      0x234

#घोषणा DP_TEST_MISC0                       0x232

#घोषणा DP_TEST_CRC_R_CR		    0x240
#घोषणा DP_TEST_CRC_G_Y			    0x242
#घोषणा DP_TEST_CRC_B_CB		    0x244

#घोषणा DP_TEST_SINK_MISC		    0x246
# define DP_TEST_CRC_SUPPORTED		    (1 << 5)
# define DP_TEST_COUNT_MASK		    0xf

#घोषणा DP_PHY_TEST_PATTERN                 0x248
# define DP_PHY_TEST_PATTERN_SEL_MASK       0x7
# define DP_PHY_TEST_PATTERN_NONE           0x0
# define DP_PHY_TEST_PATTERN_D10_2          0x1
# define DP_PHY_TEST_PATTERN_ERROR_COUNT    0x2
# define DP_PHY_TEST_PATTERN_PRBS7          0x3
# define DP_PHY_TEST_PATTERN_80BIT_CUSTOM   0x4
# define DP_PHY_TEST_PATTERN_CP2520         0x5

#घोषणा DP_TEST_HBR2_SCRAMBLER_RESET        0x24A
#घोषणा DP_TEST_80BIT_CUSTOM_PATTERN_7_0    0x250
#घोषणा	DP_TEST_80BIT_CUSTOM_PATTERN_15_8   0x251
#घोषणा	DP_TEST_80BIT_CUSTOM_PATTERN_23_16  0x252
#घोषणा	DP_TEST_80BIT_CUSTOM_PATTERN_31_24  0x253
#घोषणा	DP_TEST_80BIT_CUSTOM_PATTERN_39_32  0x254
#घोषणा	DP_TEST_80BIT_CUSTOM_PATTERN_47_40  0x255
#घोषणा	DP_TEST_80BIT_CUSTOM_PATTERN_55_48  0x256
#घोषणा	DP_TEST_80BIT_CUSTOM_PATTERN_63_56  0x257
#घोषणा	DP_TEST_80BIT_CUSTOM_PATTERN_71_64  0x258
#घोषणा	DP_TEST_80BIT_CUSTOM_PATTERN_79_72  0x259

#घोषणा DP_TEST_RESPONSE		    0x260
# define DP_TEST_ACK			    (1 << 0)
# define DP_TEST_NAK			    (1 << 1)
# define DP_TEST_EDID_CHECKSUM_WRITE	    (1 << 2)

#घोषणा DP_TEST_EDID_CHECKSUM		    0x261

#घोषणा DP_TEST_SINK			    0x270
# define DP_TEST_SINK_START		    (1 << 0)
#घोषणा DP_TEST_AUDIO_MODE		    0x271
#घोषणा DP_TEST_AUDIO_PATTERN_TYPE	    0x272
#घोषणा DP_TEST_AUDIO_PERIOD_CH1	    0x273
#घोषणा DP_TEST_AUDIO_PERIOD_CH2	    0x274
#घोषणा DP_TEST_AUDIO_PERIOD_CH3	    0x275
#घोषणा DP_TEST_AUDIO_PERIOD_CH4	    0x276
#घोषणा DP_TEST_AUDIO_PERIOD_CH5	    0x277
#घोषणा DP_TEST_AUDIO_PERIOD_CH6	    0x278
#घोषणा DP_TEST_AUDIO_PERIOD_CH7	    0x279
#घोषणा DP_TEST_AUDIO_PERIOD_CH8	    0x27A

#घोषणा DP_FEC_STATUS			    0x280    /* 1.4 */
# define DP_FEC_DECODE_EN_DETECTED	    (1 << 0)
# define DP_FEC_DECODE_DIS_DETECTED	    (1 << 1)

#घोषणा DP_FEC_ERROR_COUNT_LSB		    0x0281    /* 1.4 */

#घोषणा DP_FEC_ERROR_COUNT_MSB		    0x0282    /* 1.4 */
# define DP_FEC_ERROR_COUNT_MASK	    0x7F
# define DP_FEC_ERR_COUNT_VALID		    (1 << 7)

#घोषणा DP_PAYLOAD_TABLE_UPDATE_STATUS      0x2c0   /* 1.2 MST */
# define DP_PAYLOAD_TABLE_UPDATED           (1 << 0)
# define DP_PAYLOAD_ACT_HANDLED             (1 << 1)

#घोषणा DP_VC_PAYLOAD_ID_SLOT_1             0x2c1   /* 1.2 MST */
/* up to ID_SLOT_63 at 0x2ff */

/* Source Device-specअगरic */
#घोषणा DP_SOURCE_OUI			    0x300

/* Sink Device-specअगरic */
#घोषणा DP_SINK_OUI			    0x400

/* Branch Device-specअगरic */
#घोषणा DP_BRANCH_OUI			    0x500
#घोषणा DP_BRANCH_ID                        0x503
#घोषणा DP_BRANCH_REVISION_START            0x509
#घोषणा DP_BRANCH_HW_REV                    0x509
#घोषणा DP_BRANCH_SW_REV                    0x50A

/* Link/Sink Device Power Control */
#घोषणा DP_SET_POWER                        0x600
# define DP_SET_POWER_D0                    0x1
# define DP_SET_POWER_D3                    0x2
# define DP_SET_POWER_MASK                  0x3
# define DP_SET_POWER_D3_AUX_ON             0x5

/* eDP-specअगरic */
#घोषणा DP_EDP_DPCD_REV			    0x700    /* eDP 1.2 */
# define DP_EDP_11			    0x00
# define DP_EDP_12			    0x01
# define DP_EDP_13			    0x02
# define DP_EDP_14			    0x03
# define DP_EDP_14a                         0x04    /* eDP 1.4a */
# define DP_EDP_14b                         0x05    /* eDP 1.4b */

#घोषणा DP_EDP_GENERAL_CAP_1		    0x701
# define DP_EDP_TCON_BACKLIGHT_ADJUSTMENT_CAP		(1 << 0)
# define DP_EDP_BACKLIGHT_PIN_ENABLE_CAP		(1 << 1)
# define DP_EDP_BACKLIGHT_AUX_ENABLE_CAP		(1 << 2)
# define DP_EDP_PANEL_SELF_TEST_PIN_ENABLE_CAP		(1 << 3)
# define DP_EDP_PANEL_SELF_TEST_AUX_ENABLE_CAP		(1 << 4)
# define DP_EDP_FRC_ENABLE_CAP				(1 << 5)
# define DP_EDP_COLOR_ENGINE_CAP			(1 << 6)
# define DP_EDP_SET_POWER_CAP				(1 << 7)

#घोषणा DP_EDP_BACKLIGHT_ADJUSTMENT_CAP     0x702
# define DP_EDP_BACKLIGHT_BRIGHTNESS_PWM_PIN_CAP	(1 << 0)
# define DP_EDP_BACKLIGHT_BRIGHTNESS_AUX_SET_CAP	(1 << 1)
# define DP_EDP_BACKLIGHT_BRIGHTNESS_BYTE_COUNT		(1 << 2)
# define DP_EDP_BACKLIGHT_AUX_PWM_PRODUCT_CAP		(1 << 3)
# define DP_EDP_BACKLIGHT_FREQ_PWM_PIN_PASSTHRU_CAP	(1 << 4)
# define DP_EDP_BACKLIGHT_FREQ_AUX_SET_CAP		(1 << 5)
# define DP_EDP_DYNAMIC_BACKLIGHT_CAP			(1 << 6)
# define DP_EDP_VBLANK_BACKLIGHT_UPDATE_CAP		(1 << 7)

#घोषणा DP_EDP_GENERAL_CAP_2		    0x703
# define DP_EDP_OVERDRIVE_ENGINE_ENABLED		(1 << 0)

#घोषणा DP_EDP_GENERAL_CAP_3		    0x704    /* eDP 1.4 */
# define DP_EDP_X_REGION_CAP_MASK			(0xf << 0)
# define DP_EDP_X_REGION_CAP_SHIFT			0
# define DP_EDP_Y_REGION_CAP_MASK			(0xf << 4)
# define DP_EDP_Y_REGION_CAP_SHIFT			4

#घोषणा DP_EDP_DISPLAY_CONTROL_REGISTER     0x720
# define DP_EDP_BACKLIGHT_ENABLE			(1 << 0)
# define DP_EDP_BLACK_VIDEO_ENABLE			(1 << 1)
# define DP_EDP_FRC_ENABLE				(1 << 2)
# define DP_EDP_COLOR_ENGINE_ENABLE			(1 << 3)
# define DP_EDP_VBLANK_BACKLIGHT_UPDATE_ENABLE		(1 << 7)

#घोषणा DP_EDP_BACKLIGHT_MODE_SET_REGISTER  0x721
# define DP_EDP_BACKLIGHT_CONTROL_MODE_MASK		(3 << 0)
# define DP_EDP_BACKLIGHT_CONTROL_MODE_PWM		(0 << 0)
# define DP_EDP_BACKLIGHT_CONTROL_MODE_PRESET		(1 << 0)
# define DP_EDP_BACKLIGHT_CONTROL_MODE_DPCD		(2 << 0)
# define DP_EDP_BACKLIGHT_CONTROL_MODE_PRODUCT		(3 << 0)
# define DP_EDP_BACKLIGHT_FREQ_PWM_PIN_PASSTHRU_ENABLE	(1 << 2)
# define DP_EDP_BACKLIGHT_FREQ_AUX_SET_ENABLE		(1 << 3)
# define DP_EDP_DYNAMIC_BACKLIGHT_ENABLE		(1 << 4)
# define DP_EDP_REGIONAL_BACKLIGHT_ENABLE		(1 << 5)
# define DP_EDP_UPDATE_REGION_BRIGHTNESS		(1 << 6) /* eDP 1.4 */

#घोषणा DP_EDP_BACKLIGHT_BRIGHTNESS_MSB     0x722
#घोषणा DP_EDP_BACKLIGHT_BRIGHTNESS_LSB     0x723

#घोषणा DP_EDP_PWMGEN_BIT_COUNT             0x724
#घोषणा DP_EDP_PWMGEN_BIT_COUNT_CAP_MIN     0x725
#घोषणा DP_EDP_PWMGEN_BIT_COUNT_CAP_MAX     0x726
# define DP_EDP_PWMGEN_BIT_COUNT_MASK       (0x1f << 0)

#घोषणा DP_EDP_BACKLIGHT_CONTROL_STATUS     0x727

#घोषणा DP_EDP_BACKLIGHT_FREQ_SET           0x728
# define DP_EDP_BACKLIGHT_FREQ_BASE_KHZ     27000

#घोषणा DP_EDP_BACKLIGHT_FREQ_CAP_MIN_MSB   0x72a
#घोषणा DP_EDP_BACKLIGHT_FREQ_CAP_MIN_MID   0x72b
#घोषणा DP_EDP_BACKLIGHT_FREQ_CAP_MIN_LSB   0x72c

#घोषणा DP_EDP_BACKLIGHT_FREQ_CAP_MAX_MSB   0x72d
#घोषणा DP_EDP_BACKLIGHT_FREQ_CAP_MAX_MID   0x72e
#घोषणा DP_EDP_BACKLIGHT_FREQ_CAP_MAX_LSB   0x72f

#घोषणा DP_EDP_DBC_MINIMUM_BRIGHTNESS_SET   0x732
#घोषणा DP_EDP_DBC_MAXIMUM_BRIGHTNESS_SET   0x733

#घोषणा DP_EDP_REGIONAL_BACKLIGHT_BASE      0x740    /* eDP 1.4 */
#घोषणा DP_EDP_REGIONAL_BACKLIGHT_0	    0x741    /* eDP 1.4 */

#घोषणा DP_EDP_MSO_LINK_CAPABILITIES        0x7a4    /* eDP 1.4 */
# define DP_EDP_MSO_NUMBER_OF_LINKS_MASK    (7 << 0)
# define DP_EDP_MSO_NUMBER_OF_LINKS_SHIFT   0
# define DP_EDP_MSO_INDEPENDENT_LINK_BIT    (1 << 3)

/* Sideband MSG Buffers */
#घोषणा DP_SIDEBAND_MSG_DOWN_REQ_BASE	    0x1000   /* 1.2 MST */
#घोषणा DP_SIDEBAND_MSG_UP_REP_BASE	    0x1200   /* 1.2 MST */
#घोषणा DP_SIDEBAND_MSG_DOWN_REP_BASE	    0x1400   /* 1.2 MST */
#घोषणा DP_SIDEBAND_MSG_UP_REQ_BASE	    0x1600   /* 1.2 MST */

/* DPRX Event Status Indicator */
#घोषणा DP_SINK_COUNT_ESI		    0x2002   /* 1.2 */
/* 0-5 sink count */
# define DP_SINK_COUNT_CP_READY             (1 << 6)

#घोषणा DP_DEVICE_SERVICE_IRQ_VECTOR_ESI0   0x2003   /* 1.2 */

#घोषणा DP_DEVICE_SERVICE_IRQ_VECTOR_ESI1   0x2004   /* 1.2 */
# define DP_RX_GTC_MSTR_REQ_STATUS_CHANGE    (1 << 0)
# define DP_LOCK_ACQUISITION_REQUEST         (1 << 1)
# define DP_CEC_IRQ                          (1 << 2)

#घोषणा DP_LINK_SERVICE_IRQ_VECTOR_ESI0     0x2005   /* 1.2 */
# define RX_CAP_CHANGED                      (1 << 0)
# define LINK_STATUS_CHANGED                 (1 << 1)
# define STREAM_STATUS_CHANGED               (1 << 2)
# define HDMI_LINK_STATUS_CHANGED            (1 << 3)
# define CONNECTED_OFF_ENTRY_REQUESTED       (1 << 4)

#घोषणा DP_PSR_ERROR_STATUS                 0x2006  /* XXX 1.2? */
# define DP_PSR_LINK_CRC_ERROR              (1 << 0)
# define DP_PSR_RFB_STORAGE_ERROR           (1 << 1)
# define DP_PSR_VSC_SDP_UNCORRECTABLE_ERROR (1 << 2) /* eDP 1.4 */

#घोषणा DP_PSR_ESI                          0x2007  /* XXX 1.2? */
# define DP_PSR_CAPS_CHANGE                 (1 << 0)

#घोषणा DP_PSR_STATUS                       0x2008  /* XXX 1.2? */
# define DP_PSR_SINK_INACTIVE               0
# define DP_PSR_SINK_ACTIVE_SRC_SYNCED      1
# define DP_PSR_SINK_ACTIVE_RFB             2
# define DP_PSR_SINK_ACTIVE_SINK_SYNCED     3
# define DP_PSR_SINK_ACTIVE_RESYNC          4
# define DP_PSR_SINK_INTERNAL_ERROR         7
# define DP_PSR_SINK_STATE_MASK             0x07

#घोषणा DP_SYNCHRONIZATION_LATENCY_IN_SINK		0x2009 /* edp 1.4 */
# define DP_MAX_RESYNC_FRAME_COUNT_MASK			(0xf << 0)
# define DP_MAX_RESYNC_FRAME_COUNT_SHIFT		0
# define DP_LAST_ACTUAL_SYNCHRONIZATION_LATENCY_MASK	(0xf << 4)
# define DP_LAST_ACTUAL_SYNCHRONIZATION_LATENCY_SHIFT	4

#घोषणा DP_LAST_RECEIVED_PSR_SDP	    0x200a /* eDP 1.2 */
# define DP_PSR_STATE_BIT		    (1 << 0) /* eDP 1.2 */
# define DP_UPDATE_RFB_BIT		    (1 << 1) /* eDP 1.2 */
# define DP_CRC_VALID_BIT		    (1 << 2) /* eDP 1.2 */
# define DP_SU_VALID			    (1 << 3) /* eDP 1.4 */
# define DP_FIRST_SCAN_LINE_SU_REGION	    (1 << 4) /* eDP 1.4 */
# define DP_LAST_SCAN_LINE_SU_REGION	    (1 << 5) /* eDP 1.4 */
# define DP_Y_COORDINATE_VALID		    (1 << 6) /* eDP 1.4a */

#घोषणा DP_RECEIVER_ALPM_STATUS		    0x200b  /* eDP 1.4 */
# define DP_ALPM_LOCK_TIMEOUT_ERROR	    (1 << 0)

#घोषणा DP_LANE0_1_STATUS_ESI                  0x200c /* status same as 0x202 */
#घोषणा DP_LANE2_3_STATUS_ESI                  0x200d /* status same as 0x203 */
#घोषणा DP_LANE_ALIGN_STATUS_UPDATED_ESI       0x200e /* status same as 0x204 */
#घोषणा DP_SINK_STATUS_ESI                     0x200f /* status same as 0x205 */

/* Extended Receiver Capability: See DP_DPCD_REV क्रम definitions */
#घोषणा DP_DP13_DPCD_REV                    0x2200

#घोषणा DP_DPRX_FEATURE_ENUMERATION_LIST    0x2210  /* DP 1.3 */
# define DP_GTC_CAP					(1 << 0)  /* DP 1.3 */
# define DP_SST_SPLIT_SDP_CAP				(1 << 1)  /* DP 1.4 */
# define DP_AV_SYNC_CAP					(1 << 2)  /* DP 1.3 */
# define DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORTED	(1 << 3)  /* DP 1.3 */
# define DP_VSC_EXT_VESA_SDP_SUPPORTED			(1 << 4)  /* DP 1.4 */
# define DP_VSC_EXT_VESA_SDP_CHAINING_SUPPORTED		(1 << 5)  /* DP 1.4 */
# define DP_VSC_EXT_CEA_SDP_SUPPORTED			(1 << 6)  /* DP 1.4 */
# define DP_VSC_EXT_CEA_SDP_CHAINING_SUPPORTED		(1 << 7)  /* DP 1.4 */

#घोषणा DP_128B132B_SUPPORTED_LINK_RATES       0x2215 /* 2.0 */
# define DP_UHBR10                             (1 << 0)
# define DP_UHBR20                             (1 << 1)
# define DP_UHBR13_5                           (1 << 2)

#घोषणा DP_128B132B_TRAINING_AUX_RD_INTERVAL   0x2216 /* 2.0 */
# define DP_128B132B_TRAINING_AUX_RD_INTERVAL_MASK 0x7f

/* Protocol Converter Extension */
/* HDMI CEC tunneling over AUX DP 1.3 section 5.3.3.3.1 DPCD 1.4+ */
#घोषणा DP_CEC_TUNNELING_CAPABILITY            0x3000
# define DP_CEC_TUNNELING_CAPABLE               (1 << 0)
# define DP_CEC_SNOOPING_CAPABLE                (1 << 1)
# define DP_CEC_MULTIPLE_LA_CAPABLE             (1 << 2)

#घोषणा DP_CEC_TUNNELING_CONTROL               0x3001
# define DP_CEC_TUNNELING_ENABLE                (1 << 0)
# define DP_CEC_SNOOPING_ENABLE                 (1 << 1)

#घोषणा DP_CEC_RX_MESSAGE_INFO                 0x3002
# define DP_CEC_RX_MESSAGE_LEN_MASK             (0xf << 0)
# define DP_CEC_RX_MESSAGE_LEN_SHIFT            0
# define DP_CEC_RX_MESSAGE_HPD_STATE            (1 << 4)
# define DP_CEC_RX_MESSAGE_HPD_LOST             (1 << 5)
# define DP_CEC_RX_MESSAGE_ACKED                (1 << 6)
# define DP_CEC_RX_MESSAGE_ENDED                (1 << 7)

#घोषणा DP_CEC_TX_MESSAGE_INFO                 0x3003
# define DP_CEC_TX_MESSAGE_LEN_MASK             (0xf << 0)
# define DP_CEC_TX_MESSAGE_LEN_SHIFT            0
# define DP_CEC_TX_RETRY_COUNT_MASK             (0x7 << 4)
# define DP_CEC_TX_RETRY_COUNT_SHIFT            4
# define DP_CEC_TX_MESSAGE_SEND                 (1 << 7)

#घोषणा DP_CEC_TUNNELING_IRQ_FLAGS             0x3004
# define DP_CEC_RX_MESSAGE_INFO_VALID           (1 << 0)
# define DP_CEC_RX_MESSAGE_OVERFLOW             (1 << 1)
# define DP_CEC_TX_MESSAGE_SENT                 (1 << 4)
# define DP_CEC_TX_LINE_ERROR                   (1 << 5)
# define DP_CEC_TX_ADDRESS_NACK_ERROR           (1 << 6)
# define DP_CEC_TX_DATA_NACK_ERROR              (1 << 7)

#घोषणा DP_CEC_LOGICAL_ADDRESS_MASK            0x300E /* 0x300F word */
# define DP_CEC_LOGICAL_ADDRESS_0               (1 << 0)
# define DP_CEC_LOGICAL_ADDRESS_1               (1 << 1)
# define DP_CEC_LOGICAL_ADDRESS_2               (1 << 2)
# define DP_CEC_LOGICAL_ADDRESS_3               (1 << 3)
# define DP_CEC_LOGICAL_ADDRESS_4               (1 << 4)
# define DP_CEC_LOGICAL_ADDRESS_5               (1 << 5)
# define DP_CEC_LOGICAL_ADDRESS_6               (1 << 6)
# define DP_CEC_LOGICAL_ADDRESS_7               (1 << 7)
#घोषणा DP_CEC_LOGICAL_ADDRESS_MASK_2          0x300F /* 0x300E word */
# define DP_CEC_LOGICAL_ADDRESS_8               (1 << 0)
# define DP_CEC_LOGICAL_ADDRESS_9               (1 << 1)
# define DP_CEC_LOGICAL_ADDRESS_10              (1 << 2)
# define DP_CEC_LOGICAL_ADDRESS_11              (1 << 3)
# define DP_CEC_LOGICAL_ADDRESS_12              (1 << 4)
# define DP_CEC_LOGICAL_ADDRESS_13              (1 << 5)
# define DP_CEC_LOGICAL_ADDRESS_14              (1 << 6)
# define DP_CEC_LOGICAL_ADDRESS_15              (1 << 7)

#घोषणा DP_CEC_RX_MESSAGE_BUFFER               0x3010
#घोषणा DP_CEC_TX_MESSAGE_BUFFER               0x3020
#घोषणा DP_CEC_MESSAGE_BUFFER_LENGTH             0x10

/* PCON CONFIGURE-1 FRL FOR HDMI SINK */
#घोषणा DP_PCON_HDMI_LINK_CONFIG_1             0x305A
# define DP_PCON_ENABLE_MAX_FRL_BW             (7 << 0)
# define DP_PCON_ENABLE_MAX_BW_0GBPS	       0
# define DP_PCON_ENABLE_MAX_BW_9GBPS	       1
# define DP_PCON_ENABLE_MAX_BW_18GBPS	       2
# define DP_PCON_ENABLE_MAX_BW_24GBPS	       3
# define DP_PCON_ENABLE_MAX_BW_32GBPS	       4
# define DP_PCON_ENABLE_MAX_BW_40GBPS	       5
# define DP_PCON_ENABLE_MAX_BW_48GBPS	       6
# define DP_PCON_ENABLE_SOURCE_CTL_MODE       (1 << 3)
# define DP_PCON_ENABLE_CONCURRENT_LINK       (1 << 4)
# define DP_PCON_ENABLE_SEQUENTIAL_LINK       (0 << 4)
# define DP_PCON_ENABLE_LINK_FRL_MODE         (1 << 5)
# define DP_PCON_ENABLE_HPD_READY	      (1 << 6)
# define DP_PCON_ENABLE_HDMI_LINK             (1 << 7)

/* PCON CONFIGURE-2 FRL FOR HDMI SINK */
#घोषणा DP_PCON_HDMI_LINK_CONFIG_2            0x305B
# define DP_PCON_MAX_LINK_BW_MASK             (0x3F << 0)
# define DP_PCON_FRL_BW_MASK_9GBPS            (1 << 0)
# define DP_PCON_FRL_BW_MASK_18GBPS           (1 << 1)
# define DP_PCON_FRL_BW_MASK_24GBPS           (1 << 2)
# define DP_PCON_FRL_BW_MASK_32GBPS           (1 << 3)
# define DP_PCON_FRL_BW_MASK_40GBPS           (1 << 4)
# define DP_PCON_FRL_BW_MASK_48GBPS           (1 << 5)
# define DP_PCON_FRL_LINK_TRAIN_EXTENDED      (1 << 6)
# define DP_PCON_FRL_LINK_TRAIN_NORMAL        (0 << 6)

/* PCON HDMI LINK STATUS */
#घोषणा DP_PCON_HDMI_TX_LINK_STATUS           0x303B
# define DP_PCON_HDMI_TX_LINK_ACTIVE          (1 << 0)
# define DP_PCON_FRL_READY		      (1 << 1)

/* PCON HDMI POST FRL STATUS */
#घोषणा DP_PCON_HDMI_POST_FRL_STATUS          0x3036
# define DP_PCON_HDMI_LINK_MODE               (1 << 0)
# define DP_PCON_HDMI_MODE_TMDS               0
# define DP_PCON_HDMI_MODE_FRL                1
# define DP_PCON_HDMI_FRL_TRAINED_BW          (0x3F << 1)
# define DP_PCON_FRL_TRAINED_BW_9GBPS	      (1 << 1)
# define DP_PCON_FRL_TRAINED_BW_18GBPS	      (1 << 2)
# define DP_PCON_FRL_TRAINED_BW_24GBPS	      (1 << 3)
# define DP_PCON_FRL_TRAINED_BW_32GBPS	      (1 << 4)
# define DP_PCON_FRL_TRAINED_BW_40GBPS	      (1 << 5)
# define DP_PCON_FRL_TRAINED_BW_48GBPS	      (1 << 6)

#घोषणा DP_PROTOCOL_CONVERTER_CONTROL_0		0x3050 /* DP 1.3 */
# define DP_HDMI_DVI_OUTPUT_CONFIG		(1 << 0) /* DP 1.3 */
#घोषणा DP_PROTOCOL_CONVERTER_CONTROL_1		0x3051 /* DP 1.3 */
# define DP_CONVERSION_TO_YCBCR420_ENABLE	(1 << 0) /* DP 1.3 */
# define DP_HDMI_EDID_PROCESSING_DISABLE	(1 << 1) /* DP 1.4 */
# define DP_HDMI_AUTONOMOUS_SCRAMBLING_DISABLE	(1 << 2) /* DP 1.4 */
# define DP_HDMI_FORCE_SCRAMBLING		(1 << 3) /* DP 1.4 */
#घोषणा DP_PROTOCOL_CONVERTER_CONTROL_2		0x3052 /* DP 1.3 */
# define DP_CONVERSION_TO_YCBCR422_ENABLE	(1 << 0) /* DP 1.3 */
# define DP_PCON_ENABLE_DSC_ENCODER	        (1 << 1)
# define DP_PCON_ENCODER_PPS_OVERRIDE_MASK	(0x3 << 2)
# define DP_PCON_ENC_PPS_OVERRIDE_DISABLED      0
# define DP_PCON_ENC_PPS_OVERRIDE_EN_PARAMS     1
# define DP_PCON_ENC_PPS_OVERRIDE_EN_BUFFER     2
# define DP_CONVERSION_RGB_YCBCR_MASK	       (7 << 4)
# define DP_CONVERSION_BT601_RGB_YCBCR_ENABLE  (1 << 4)
# define DP_CONVERSION_BT709_RGB_YCBCR_ENABLE  (1 << 5)
# define DP_CONVERSION_BT2020_RGB_YCBCR_ENABLE (1 << 6)

/* PCON Downstream HDMI ERROR Status per Lane */
#घोषणा DP_PCON_HDMI_ERROR_STATUS_LN0          0x3037
#घोषणा DP_PCON_HDMI_ERROR_STATUS_LN1          0x3038
#घोषणा DP_PCON_HDMI_ERROR_STATUS_LN2          0x3039
#घोषणा DP_PCON_HDMI_ERROR_STATUS_LN3          0x303A
# define DP_PCON_HDMI_ERROR_COUNT_MASK         (0x7 << 0)
# define DP_PCON_HDMI_ERROR_COUNT_THREE_PLUS   (1 << 0)
# define DP_PCON_HDMI_ERROR_COUNT_TEN_PLUS     (1 << 1)
# define DP_PCON_HDMI_ERROR_COUNT_HUNDRED_PLUS (1 << 2)

/* PCON HDMI CONFIG PPS Override Buffer
 * Valid Offsets to be added to Base : 0-127
 */
#घोषणा DP_PCON_HDMI_PPS_OVERRIDE_BASE        0x3100

/* PCON HDMI CONFIG PPS Override Parameter: Slice height
 * Offset-0 8LSBs of the Slice height.
 * Offset-1 8MSBs of the Slice height.
 */
#घोषणा DP_PCON_HDMI_PPS_OVRD_SLICE_HEIGHT    0x3180

/* PCON HDMI CONFIG PPS Override Parameter: Slice width
 * Offset-0 8LSBs of the Slice width.
 * Offset-1 8MSBs of the Slice width.
 */
#घोषणा DP_PCON_HDMI_PPS_OVRD_SLICE_WIDTH    0x3182

/* PCON HDMI CONFIG PPS Override Parameter: bits_per_pixel
 * Offset-0 8LSBs of the bits_per_pixel.
 * Offset-1 2MSBs of the bits_per_pixel.
 */
#घोषणा DP_PCON_HDMI_PPS_OVRD_BPP	     0x3184

/* HDCP 1.3 and HDCP 2.2 */
#घोषणा DP_AUX_HDCP_BKSV		0x68000
#घोषणा DP_AUX_HDCP_RI_PRIME		0x68005
#घोषणा DP_AUX_HDCP_AKSV		0x68007
#घोषणा DP_AUX_HDCP_AN			0x6800C
#घोषणा DP_AUX_HDCP_V_PRIME(h)		(0x68014 + h * 4)
#घोषणा DP_AUX_HDCP_BCAPS		0x68028
# define DP_BCAPS_REPEATER_PRESENT	BIT(1)
# define DP_BCAPS_HDCP_CAPABLE		BIT(0)
#घोषणा DP_AUX_HDCP_BSTATUS		0x68029
# define DP_BSTATUS_REAUTH_REQ		BIT(3)
# define DP_BSTATUS_LINK_FAILURE	BIT(2)
# define DP_BSTATUS_R0_PRIME_READY	BIT(1)
# define DP_BSTATUS_READY		BIT(0)
#घोषणा DP_AUX_HDCP_BINFO		0x6802A
#घोषणा DP_AUX_HDCP_KSV_FIFO		0x6802C
#घोषणा DP_AUX_HDCP_AINFO		0x6803B

/* DP HDCP2.2 parameter offsets in DPCD address space */
#घोषणा DP_HDCP_2_2_REG_RTX_OFFSET		0x69000
#घोषणा DP_HDCP_2_2_REG_TXCAPS_OFFSET		0x69008
#घोषणा DP_HDCP_2_2_REG_CERT_RX_OFFSET		0x6900B
#घोषणा DP_HDCP_2_2_REG_RRX_OFFSET		0x69215
#घोषणा DP_HDCP_2_2_REG_RX_CAPS_OFFSET		0x6921D
#घोषणा DP_HDCP_2_2_REG_EKPUB_KM_OFFSET		0x69220
#घोषणा DP_HDCP_2_2_REG_EKH_KM_WR_OFFSET	0x692A0
#घोषणा DP_HDCP_2_2_REG_M_OFFSET		0x692B0
#घोषणा DP_HDCP_2_2_REG_HPRIME_OFFSET		0x692C0
#घोषणा DP_HDCP_2_2_REG_EKH_KM_RD_OFFSET	0x692E0
#घोषणा DP_HDCP_2_2_REG_RN_OFFSET		0x692F0
#घोषणा DP_HDCP_2_2_REG_LPRIME_OFFSET		0x692F8
#घोषणा DP_HDCP_2_2_REG_EDKEY_KS_OFFSET		0x69318
#घोषणा	DP_HDCP_2_2_REG_RIV_OFFSET		0x69328
#घोषणा DP_HDCP_2_2_REG_RXINFO_OFFSET		0x69330
#घोषणा DP_HDCP_2_2_REG_SEQ_NUM_V_OFFSET	0x69332
#घोषणा DP_HDCP_2_2_REG_VPRIME_OFFSET		0x69335
#घोषणा DP_HDCP_2_2_REG_RECV_ID_LIST_OFFSET	0x69345
#घोषणा DP_HDCP_2_2_REG_V_OFFSET		0x693E0
#घोषणा DP_HDCP_2_2_REG_SEQ_NUM_M_OFFSET	0x693F0
#घोषणा DP_HDCP_2_2_REG_K_OFFSET		0x693F3
#घोषणा DP_HDCP_2_2_REG_STREAM_ID_TYPE_OFFSET	0x693F5
#घोषणा DP_HDCP_2_2_REG_MPRIME_OFFSET		0x69473
#घोषणा DP_HDCP_2_2_REG_RXSTATUS_OFFSET		0x69493
#घोषणा DP_HDCP_2_2_REG_STREAM_TYPE_OFFSET	0x69494
#घोषणा DP_HDCP_2_2_REG_DBG_OFFSET		0x69518

/* LTTPR: Link Training (LT)-tunable PHY Repeaters */
#घोषणा DP_LT_TUNABLE_PHY_REPEATER_FIELD_DATA_STRUCTURE_REV 0xf0000 /* 1.3 */
#घोषणा DP_MAX_LINK_RATE_PHY_REPEATER			    0xf0001 /* 1.4a */
#घोषणा DP_PHY_REPEATER_CNT				    0xf0002 /* 1.3 */
#घोषणा DP_PHY_REPEATER_MODE				    0xf0003 /* 1.3 */
#घोषणा DP_MAX_LANE_COUNT_PHY_REPEATER			    0xf0004 /* 1.4a */
#घोषणा DP_Repeater_FEC_CAPABILITY			    0xf0004 /* 1.4 */
#घोषणा DP_PHY_REPEATER_EXTENDED_WAIT_TIMEOUT		    0xf0005 /* 1.4a */

क्रमागत drm_dp_phy अणु
	DP_PHY_DPRX,

	DP_PHY_LTTPR1,
	DP_PHY_LTTPR2,
	DP_PHY_LTTPR3,
	DP_PHY_LTTPR4,
	DP_PHY_LTTPR5,
	DP_PHY_LTTPR6,
	DP_PHY_LTTPR7,
	DP_PHY_LTTPR8,

	DP_MAX_LTTPR_COUNT = DP_PHY_LTTPR8,
पूर्ण;

#घोषणा DP_PHY_LTTPR(i)					    (DP_PHY_LTTPR1 + (i))

#घोषणा __DP_LTTPR1_BASE				    0xf0010 /* 1.3 */
#घोषणा __DP_LTTPR2_BASE				    0xf0060 /* 1.3 */
#घोषणा DP_LTTPR_BASE(dp_phy) \
	(__DP_LTTPR1_BASE + (__DP_LTTPR2_BASE - __DP_LTTPR1_BASE) * \
		((dp_phy) - DP_PHY_LTTPR1))

#घोषणा DP_LTTPR_REG(dp_phy, lttpr1_reg) \
	(DP_LTTPR_BASE(dp_phy) - DP_LTTPR_BASE(DP_PHY_LTTPR1) + (lttpr1_reg))

#घोषणा DP_TRAINING_PATTERN_SET_PHY_REPEATER1		    0xf0010 /* 1.3 */
#घोषणा DP_TRAINING_PATTERN_SET_PHY_REPEATER(dp_phy) \
	DP_LTTPR_REG(dp_phy, DP_TRAINING_PATTERN_SET_PHY_REPEATER1)

#घोषणा DP_TRAINING_LANE0_SET_PHY_REPEATER1		    0xf0011 /* 1.3 */
#घोषणा DP_TRAINING_LANE0_SET_PHY_REPEATER(dp_phy) \
	DP_LTTPR_REG(dp_phy, DP_TRAINING_LANE0_SET_PHY_REPEATER1)

#घोषणा DP_TRAINING_LANE1_SET_PHY_REPEATER1		    0xf0012 /* 1.3 */
#घोषणा DP_TRAINING_LANE2_SET_PHY_REPEATER1		    0xf0013 /* 1.3 */
#घोषणा DP_TRAINING_LANE3_SET_PHY_REPEATER1		    0xf0014 /* 1.3 */
#घोषणा DP_TRAINING_AUX_RD_INTERVAL_PHY_REPEATER1	    0xf0020 /* 1.4a */
#घोषणा DP_TRAINING_AUX_RD_INTERVAL_PHY_REPEATER(dp_phy)	\
	DP_LTTPR_REG(dp_phy, DP_TRAINING_AUX_RD_INTERVAL_PHY_REPEATER1)

#घोषणा DP_TRANSMITTER_CAPABILITY_PHY_REPEATER1		    0xf0021 /* 1.4a */
# define DP_VOLTAGE_SWING_LEVEL_3_SUPPORTED		    BIT(0)
# define DP_PRE_EMPHASIS_LEVEL_3_SUPPORTED		    BIT(1)

#घोषणा DP_LANE0_1_STATUS_PHY_REPEATER1			    0xf0030 /* 1.3 */
#घोषणा DP_LANE0_1_STATUS_PHY_REPEATER(dp_phy) \
	DP_LTTPR_REG(dp_phy, DP_LANE0_1_STATUS_PHY_REPEATER1)

#घोषणा DP_LANE2_3_STATUS_PHY_REPEATER1			    0xf0031 /* 1.3 */

#घोषणा DP_LANE_ALIGN_STATUS_UPDATED_PHY_REPEATER1	    0xf0032 /* 1.3 */
#घोषणा DP_ADJUST_REQUEST_LANE0_1_PHY_REPEATER1		    0xf0033 /* 1.3 */
#घोषणा DP_ADJUST_REQUEST_LANE2_3_PHY_REPEATER1		    0xf0034 /* 1.3 */
#घोषणा DP_SYMBOL_ERROR_COUNT_LANE0_PHY_REPEATER1	    0xf0035 /* 1.3 */
#घोषणा DP_SYMBOL_ERROR_COUNT_LANE1_PHY_REPEATER1	    0xf0037 /* 1.3 */
#घोषणा DP_SYMBOL_ERROR_COUNT_LANE2_PHY_REPEATER1	    0xf0039 /* 1.3 */
#घोषणा DP_SYMBOL_ERROR_COUNT_LANE3_PHY_REPEATER1	    0xf003b /* 1.3 */
#घोषणा DP_FEC_STATUS_PHY_REPEATER1			    0xf0290 /* 1.4 */
#घोषणा DP_FEC_ERROR_COUNT_PHY_REPEATER1                    0xf0291 /* 1.4 */
#घोषणा DP_FEC_CAPABILITY_PHY_REPEATER1                     0xf0294 /* 1.4a */

/* Repeater modes */
#घोषणा DP_PHY_REPEATER_MODE_TRANSPARENT		    0x55    /* 1.3 */
#घोषणा DP_PHY_REPEATER_MODE_NON_TRANSPARENT		    0xaa    /* 1.3 */

/* DP HDCP message start offsets in DPCD address space */
#घोषणा DP_HDCP_2_2_AKE_INIT_OFFSET		DP_HDCP_2_2_REG_RTX_OFFSET
#घोषणा DP_HDCP_2_2_AKE_SEND_CERT_OFFSET	DP_HDCP_2_2_REG_CERT_RX_OFFSET
#घोषणा DP_HDCP_2_2_AKE_NO_STORED_KM_OFFSET	DP_HDCP_2_2_REG_EKPUB_KM_OFFSET
#घोषणा DP_HDCP_2_2_AKE_STORED_KM_OFFSET	DP_HDCP_2_2_REG_EKH_KM_WR_OFFSET
#घोषणा DP_HDCP_2_2_AKE_SEND_HPRIME_OFFSET	DP_HDCP_2_2_REG_HPRIME_OFFSET
#घोषणा DP_HDCP_2_2_AKE_SEND_PAIRING_INFO_OFFSET \
						DP_HDCP_2_2_REG_EKH_KM_RD_OFFSET
#घोषणा DP_HDCP_2_2_LC_INIT_OFFSET		DP_HDCP_2_2_REG_RN_OFFSET
#घोषणा DP_HDCP_2_2_LC_SEND_LPRIME_OFFSET	DP_HDCP_2_2_REG_LPRIME_OFFSET
#घोषणा DP_HDCP_2_2_SKE_SEND_EKS_OFFSET		DP_HDCP_2_2_REG_EDKEY_KS_OFFSET
#घोषणा DP_HDCP_2_2_REP_SEND_RECVID_LIST_OFFSET	DP_HDCP_2_2_REG_RXINFO_OFFSET
#घोषणा DP_HDCP_2_2_REP_SEND_ACK_OFFSET		DP_HDCP_2_2_REG_V_OFFSET
#घोषणा DP_HDCP_2_2_REP_STREAM_MANAGE_OFFSET	DP_HDCP_2_2_REG_SEQ_NUM_M_OFFSET
#घोषणा DP_HDCP_2_2_REP_STREAM_READY_OFFSET	DP_HDCP_2_2_REG_MPRIME_OFFSET

#घोषणा HDCP_2_2_DP_RXSTATUS_LEN		1
#घोषणा HDCP_2_2_DP_RXSTATUS_READY(x)		((x) & BIT(0))
#घोषणा HDCP_2_2_DP_RXSTATUS_H_PRIME(x)		((x) & BIT(1))
#घोषणा HDCP_2_2_DP_RXSTATUS_PAIRING(x)		((x) & BIT(2))
#घोषणा HDCP_2_2_DP_RXSTATUS_REAUTH_REQ(x)	((x) & BIT(3))
#घोषणा HDCP_2_2_DP_RXSTATUS_LINK_FAILED(x)	((x) & BIT(4))

/* DP 1.2 Sideband message defines */
/* peer device type - DP 1.2a Table 2-92 */
#घोषणा DP_PEER_DEVICE_NONE		0x0
#घोषणा DP_PEER_DEVICE_SOURCE_OR_SST	0x1
#घोषणा DP_PEER_DEVICE_MST_BRANCHING	0x2
#घोषणा DP_PEER_DEVICE_SST_SINK		0x3
#घोषणा DP_PEER_DEVICE_DP_LEGACY_CONV	0x4

/* DP 1.2 MST sideband request names DP 1.2a Table 2-80 */
#घोषणा DP_GET_MSG_TRANSACTION_VERSION	0x00 /* DP 1.3 */
#घोषणा DP_LINK_ADDRESS			0x01
#घोषणा DP_CONNECTION_STATUS_NOTIFY	0x02
#घोषणा DP_ENUM_PATH_RESOURCES		0x10
#घोषणा DP_ALLOCATE_PAYLOAD		0x11
#घोषणा DP_QUERY_PAYLOAD		0x12
#घोषणा DP_RESOURCE_STATUS_NOTIFY	0x13
#घोषणा DP_CLEAR_PAYLOAD_ID_TABLE	0x14
#घोषणा DP_REMOTE_DPCD_READ		0x20
#घोषणा DP_REMOTE_DPCD_WRITE		0x21
#घोषणा DP_REMOTE_I2C_READ		0x22
#घोषणा DP_REMOTE_I2C_WRITE		0x23
#घोषणा DP_POWER_UP_PHY			0x24
#घोषणा DP_POWER_DOWN_PHY		0x25
#घोषणा DP_SINK_EVENT_NOTIFY		0x30
#घोषणा DP_QUERY_STREAM_ENC_STATUS	0x38
#घोषणा  DP_QUERY_STREAM_ENC_STATUS_STATE_NO_EXIST	0
#घोषणा  DP_QUERY_STREAM_ENC_STATUS_STATE_INACTIVE	1
#घोषणा  DP_QUERY_STREAM_ENC_STATUS_STATE_ACTIVE	2

/* DP 1.2 MST sideband reply types */
#घोषणा DP_SIDEBAND_REPLY_ACK		0x00
#घोषणा DP_SIDEBAND_REPLY_NAK		0x01

/* DP 1.2 MST sideband nak reasons - table 2.84 */
#घोषणा DP_NAK_WRITE_FAILURE		0x01
#घोषणा DP_NAK_INVALID_READ		0x02
#घोषणा DP_NAK_CRC_FAILURE		0x03
#घोषणा DP_NAK_BAD_PARAM		0x04
#घोषणा DP_NAK_DEFER			0x05
#घोषणा DP_NAK_LINK_FAILURE		0x06
#घोषणा DP_NAK_NO_RESOURCES		0x07
#घोषणा DP_NAK_DPCD_FAIL		0x08
#घोषणा DP_NAK_I2C_NAK			0x09
#घोषणा DP_NAK_ALLOCATE_FAIL		0x0a

#घोषणा MODE_I2C_START	1
#घोषणा MODE_I2C_WRITE	2
#घोषणा MODE_I2C_READ	4
#घोषणा MODE_I2C_STOP	8

/* DP 1.2 MST PORTs - Section 2.5.1 v1.2a spec */
#घोषणा DP_MST_PHYSICAL_PORT_0 0
#घोषणा DP_MST_LOGICAL_PORT_0 8

#घोषणा DP_LINK_CONSTANT_N_VALUE 0x8000
#घोषणा DP_LINK_STATUS_SIZE	   6
bool drm_dp_channel_eq_ok(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
			  पूर्णांक lane_count);
bool drm_dp_घड़ी_recovery_ok(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
			      पूर्णांक lane_count);
u8 drm_dp_get_adjust_request_voltage(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
				     पूर्णांक lane);
u8 drm_dp_get_adjust_request_pre_emphasis(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
					  पूर्णांक lane);
u8 drm_dp_get_adjust_request_post_cursor(स्थिर u8 link_status[DP_LINK_STATUS_SIZE],
					 अचिन्हित पूर्णांक lane);

#घोषणा DP_BRANCH_OUI_HEADER_SIZE	0xc
#घोषणा DP_RECEIVER_CAP_SIZE		0xf
#घोषणा DP_DSC_RECEIVER_CAP_SIZE        0xf
#घोषणा EDP_PSR_RECEIVER_CAP_SIZE	2
#घोषणा EDP_DISPLAY_CTL_CAP_SIZE	3
#घोषणा DP_LTTPR_COMMON_CAP_SIZE	8
#घोषणा DP_LTTPR_PHY_CAP_SIZE		3

व्योम drm_dp_link_train_घड़ी_recovery_delay(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE]);
व्योम drm_dp_lttpr_link_train_घड़ी_recovery_delay(व्योम);
व्योम drm_dp_link_train_channel_eq_delay(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE]);
व्योम drm_dp_lttpr_link_train_channel_eq_delay(स्थिर u8 caps[DP_LTTPR_PHY_CAP_SIZE]);

u8 drm_dp_link_rate_to_bw_code(पूर्णांक link_rate);
पूर्णांक drm_dp_bw_code_to_link_rate(u8 link_bw);

#घोषणा DP_SDP_AUDIO_TIMESTAMP		0x01
#घोषणा DP_SDP_AUDIO_STREAM		0x02
#घोषणा DP_SDP_EXTENSION		0x04 /* DP 1.1 */
#घोषणा DP_SDP_AUDIO_COPYMANAGEMENT	0x05 /* DP 1.2 */
#घोषणा DP_SDP_ISRC			0x06 /* DP 1.2 */
#घोषणा DP_SDP_VSC			0x07 /* DP 1.2 */
#घोषणा DP_SDP_CAMERA_GENERIC(i)	(0x08 + (i)) /* 0-7, DP 1.3 */
#घोषणा DP_SDP_PPS			0x10 /* DP 1.4 */
#घोषणा DP_SDP_VSC_EXT_VESA		0x20 /* DP 1.4 */
#घोषणा DP_SDP_VSC_EXT_CEA		0x21 /* DP 1.4 */
/* 0x80+ CEA-861 infoframe types */

/**
 * काष्ठा dp_sdp_header - DP secondary data packet header
 * @HB0: Secondary Data Packet ID
 * @HB1: Secondary Data Packet Type
 * @HB2: Secondary Data Packet Specअगरic header, Byte 0
 * @HB3: Secondary Data packet Specअगरic header, Byte 1
 */
काष्ठा dp_sdp_header अणु
	u8 HB0;
	u8 HB1;
	u8 HB2;
	u8 HB3;
पूर्ण __packed;

#घोषणा EDP_SDP_HEADER_REVISION_MASK		0x1F
#घोषणा EDP_SDP_HEADER_VALID_PAYLOAD_BYTES	0x1F
#घोषणा DP_SDP_PPS_HEADER_PAYLOAD_BYTES_MINUS_1 0x7F

/**
 * काष्ठा dp_sdp - DP secondary data packet
 * @sdp_header: DP secondary data packet header
 * @db: DP secondaray data packet data blocks
 * VSC SDP Payload क्रम PSR
 * db[0]: Stereo Interface
 * db[1]: 0 - PSR State; 1 - Update RFB; 2 - CRC Valid
 * db[2]: CRC value bits 7:0 of the R or Cr component
 * db[3]: CRC value bits 15:8 of the R or Cr component
 * db[4]: CRC value bits 7:0 of the G or Y component
 * db[5]: CRC value bits 15:8 of the G or Y component
 * db[6]: CRC value bits 7:0 of the B or Cb component
 * db[7]: CRC value bits 15:8 of the B or Cb component
 * db[8] - db[31]: Reserved
 * VSC SDP Payload क्रम Pixel Encoding/Colorimetry Format
 * db[0] - db[15]: Reserved
 * db[16]: Pixel Encoding and Colorimetry Formats
 * db[17]: Dynamic Range and Component Bit Depth
 * db[18]: Content Type
 * db[19] - db[31]: Reserved
 */
काष्ठा dp_sdp अणु
	काष्ठा dp_sdp_header sdp_header;
	u8 db[32];
पूर्ण __packed;

#घोषणा EDP_VSC_PSR_STATE_ACTIVE	(1<<0)
#घोषणा EDP_VSC_PSR_UPDATE_RFB		(1<<1)
#घोषणा EDP_VSC_PSR_CRC_VALUES_VALID	(1<<2)

/**
 * क्रमागत dp_pixelक्रमmat - drm DP Pixel encoding क्रमmats
 *
 * This क्रमागत is used to indicate DP VSC SDP Pixel encoding क्रमmats.
 * It is based on DP 1.4 spec [Table 2-117: VSC SDP Payload क्रम DB16 through
 * DB18]
 *
 * @DP_PIXELFORMAT_RGB: RGB pixel encoding क्रमmat
 * @DP_PIXELFORMAT_YUV444: YCbCr 4:4:4 pixel encoding क्रमmat
 * @DP_PIXELFORMAT_YUV422: YCbCr 4:2:2 pixel encoding क्रमmat
 * @DP_PIXELFORMAT_YUV420: YCbCr 4:2:0 pixel encoding क्रमmat
 * @DP_PIXELFORMAT_Y_ONLY: Y Only pixel encoding क्रमmat
 * @DP_PIXELFORMAT_RAW: RAW pixel encoding क्रमmat
 * @DP_PIXELFORMAT_RESERVED: Reserved pixel encoding क्रमmat
 */
क्रमागत dp_pixelक्रमmat अणु
	DP_PIXELFORMAT_RGB = 0,
	DP_PIXELFORMAT_YUV444 = 0x1,
	DP_PIXELFORMAT_YUV422 = 0x2,
	DP_PIXELFORMAT_YUV420 = 0x3,
	DP_PIXELFORMAT_Y_ONLY = 0x4,
	DP_PIXELFORMAT_RAW = 0x5,
	DP_PIXELFORMAT_RESERVED = 0x6,
पूर्ण;

/**
 * क्रमागत dp_colorimetry - drm DP Colorimetry क्रमmats
 *
 * This क्रमागत is used to indicate DP VSC SDP Colorimetry क्रमmats.
 * It is based on DP 1.4 spec [Table 2-117: VSC SDP Payload क्रम DB16 through
 * DB18] and a name of क्रमागत member follows DRM_MODE_COLORIMETRY definition.
 *
 * @DP_COLORIMETRY_DEFAULT: sRGB (IEC 61966-2-1) or
 *                          ITU-R BT.601 colorimetry क्रमmat
 * @DP_COLORIMETRY_RGB_WIDE_FIXED: RGB wide gamut fixed poपूर्णांक colorimetry क्रमmat
 * @DP_COLORIMETRY_BT709_YCC: ITU-R BT.709 colorimetry क्रमmat
 * @DP_COLORIMETRY_RGB_WIDE_FLOAT: RGB wide gamut भग्नing poपूर्णांक
 *                                 (scRGB (IEC 61966-2-2)) colorimetry क्रमmat
 * @DP_COLORIMETRY_XVYCC_601: xvYCC601 colorimetry क्रमmat
 * @DP_COLORIMETRY_OPRGB: OpRGB colorimetry क्रमmat
 * @DP_COLORIMETRY_XVYCC_709: xvYCC709 colorimetry क्रमmat
 * @DP_COLORIMETRY_DCI_P3_RGB: DCI-P3 (SMPTE RP 431-2) colorimetry क्रमmat
 * @DP_COLORIMETRY_SYCC_601: sYCC601 colorimetry क्रमmat
 * @DP_COLORIMETRY_RGB_CUSTOM: RGB Custom Color Profile colorimetry क्रमmat
 * @DP_COLORIMETRY_OPYCC_601: opYCC601 colorimetry क्रमmat
 * @DP_COLORIMETRY_BT2020_RGB: ITU-R BT.2020 R' G' B' colorimetry क्रमmat
 * @DP_COLORIMETRY_BT2020_CYCC: ITU-R BT.2020 Y'c C'bc C'rc colorimetry क्रमmat
 * @DP_COLORIMETRY_BT2020_YCC: ITU-R BT.2020 Y' C'b C'r colorimetry क्रमmat
 */
क्रमागत dp_colorimetry अणु
	DP_COLORIMETRY_DEFAULT = 0,
	DP_COLORIMETRY_RGB_WIDE_FIXED = 0x1,
	DP_COLORIMETRY_BT709_YCC = 0x1,
	DP_COLORIMETRY_RGB_WIDE_FLOAT = 0x2,
	DP_COLORIMETRY_XVYCC_601 = 0x2,
	DP_COLORIMETRY_OPRGB = 0x3,
	DP_COLORIMETRY_XVYCC_709 = 0x3,
	DP_COLORIMETRY_DCI_P3_RGB = 0x4,
	DP_COLORIMETRY_SYCC_601 = 0x4,
	DP_COLORIMETRY_RGB_CUSTOM = 0x5,
	DP_COLORIMETRY_OPYCC_601 = 0x5,
	DP_COLORIMETRY_BT2020_RGB = 0x6,
	DP_COLORIMETRY_BT2020_CYCC = 0x6,
	DP_COLORIMETRY_BT2020_YCC = 0x7,
पूर्ण;

/**
 * क्रमागत dp_dynamic_range - drm DP Dynamic Range
 *
 * This क्रमागत is used to indicate DP VSC SDP Dynamic Range.
 * It is based on DP 1.4 spec [Table 2-117: VSC SDP Payload क्रम DB16 through
 * DB18]
 *
 * @DP_DYNAMIC_RANGE_VESA: VESA range
 * @DP_DYNAMIC_RANGE_CTA: CTA range
 */
क्रमागत dp_dynamic_range अणु
	DP_DYNAMIC_RANGE_VESA = 0,
	DP_DYNAMIC_RANGE_CTA = 1,
पूर्ण;

/**
 * क्रमागत dp_content_type - drm DP Content Type
 *
 * This क्रमागत is used to indicate DP VSC SDP Content Types.
 * It is based on DP 1.4 spec [Table 2-117: VSC SDP Payload क्रम DB16 through
 * DB18]
 * CTA-861-G defines content types and expected processing by a sink device
 *
 * @DP_CONTENT_TYPE_NOT_DEFINED: Not defined type
 * @DP_CONTENT_TYPE_GRAPHICS: Graphics type
 * @DP_CONTENT_TYPE_PHOTO: Photo type
 * @DP_CONTENT_TYPE_VIDEO: Video type
 * @DP_CONTENT_TYPE_GAME: Game type
 */
क्रमागत dp_content_type अणु
	DP_CONTENT_TYPE_NOT_DEFINED = 0x00,
	DP_CONTENT_TYPE_GRAPHICS = 0x01,
	DP_CONTENT_TYPE_PHOTO = 0x02,
	DP_CONTENT_TYPE_VIDEO = 0x03,
	DP_CONTENT_TYPE_GAME = 0x04,
पूर्ण;

/**
 * काष्ठा drm_dp_vsc_sdp - drm DP VSC SDP
 *
 * This काष्ठाure represents a DP VSC SDP of drm
 * It is based on DP 1.4 spec [Table 2-116: VSC SDP Header Bytes] and
 * [Table 2-117: VSC SDP Payload क्रम DB16 through DB18]
 *
 * @sdp_type: secondary-data packet type
 * @revision: revision number
 * @length: number of valid data bytes
 * @pixelक्रमmat: pixel encoding क्रमmat
 * @colorimetry: colorimetry क्रमmat
 * @bpc: bit per color
 * @dynamic_range: dynamic range inक्रमmation
 * @content_type: CTA-861-G defines content types and expected processing by a sink device
 */
काष्ठा drm_dp_vsc_sdp अणु
	अचिन्हित अक्षर sdp_type;
	अचिन्हित अक्षर revision;
	अचिन्हित अक्षर length;
	क्रमागत dp_pixelक्रमmat pixelक्रमmat;
	क्रमागत dp_colorimetry colorimetry;
	पूर्णांक bpc;
	क्रमागत dp_dynamic_range dynamic_range;
	क्रमागत dp_content_type content_type;
पूर्ण;

व्योम drm_dp_vsc_sdp_log(स्थिर अक्षर *level, काष्ठा device *dev,
			स्थिर काष्ठा drm_dp_vsc_sdp *vsc);

पूर्णांक drm_dp_psr_setup_समय(स्थिर u8 psr_cap[EDP_PSR_RECEIVER_CAP_SIZE]);

अटल अंतरभूत पूर्णांक
drm_dp_max_link_rate(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस drm_dp_bw_code_to_link_rate(dpcd[DP_MAX_LINK_RATE]);
पूर्ण

अटल अंतरभूत u8
drm_dp_max_lane_count(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस dpcd[DP_MAX_LANE_COUNT] & DP_MAX_LANE_COUNT_MASK;
पूर्ण

अटल अंतरभूत bool
drm_dp_enhanced_frame_cap(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस dpcd[DP_DPCD_REV] >= 0x11 &&
		(dpcd[DP_MAX_LANE_COUNT] & DP_ENHANCED_FRAME_CAP);
पूर्ण

अटल अंतरभूत bool
drm_dp_fast_training_cap(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस dpcd[DP_DPCD_REV] >= 0x11 &&
		(dpcd[DP_MAX_DOWNSPREAD] & DP_NO_AUX_HANDSHAKE_LINK_TRAINING);
पूर्ण

अटल अंतरभूत bool
drm_dp_tps3_supported(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस dpcd[DP_DPCD_REV] >= 0x12 &&
		dpcd[DP_MAX_LANE_COUNT] & DP_TPS3_SUPPORTED;
पूर्ण

अटल अंतरभूत bool
drm_dp_tps4_supported(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस dpcd[DP_DPCD_REV] >= 0x14 &&
		dpcd[DP_MAX_DOWNSPREAD] & DP_TPS4_SUPPORTED;
पूर्ण

अटल अंतरभूत u8
drm_dp_training_pattern_mask(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस (dpcd[DP_DPCD_REV] >= 0x14) ? DP_TRAINING_PATTERN_MASK_1_4 :
		DP_TRAINING_PATTERN_MASK;
पूर्ण

अटल अंतरभूत bool
drm_dp_is_branch(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DWN_STRM_PORT_PRESENT;
पूर्ण

/* DP/eDP DSC support */
u8 drm_dp_dsc_sink_max_slice_count(स्थिर u8 dsc_dpcd[DP_DSC_RECEIVER_CAP_SIZE],
				   bool is_edp);
u8 drm_dp_dsc_sink_line_buf_depth(स्थिर u8 dsc_dpcd[DP_DSC_RECEIVER_CAP_SIZE]);
पूर्णांक drm_dp_dsc_sink_supported_input_bpcs(स्थिर u8 dsc_dpc[DP_DSC_RECEIVER_CAP_SIZE],
					 u8 dsc_bpc[3]);

अटल अंतरभूत bool
drm_dp_sink_supports_dsc(स्थिर u8 dsc_dpcd[DP_DSC_RECEIVER_CAP_SIZE])
अणु
	वापस dsc_dpcd[DP_DSC_SUPPORT - DP_DSC_SUPPORT] &
		DP_DSC_DECOMPRESSION_IS_SUPPORTED;
पूर्ण

अटल अंतरभूत u16
drm_edp_dsc_sink_output_bpp(स्थिर u8 dsc_dpcd[DP_DSC_RECEIVER_CAP_SIZE])
अणु
	वापस dsc_dpcd[DP_DSC_MAX_BITS_PER_PIXEL_LOW - DP_DSC_SUPPORT] |
		(dsc_dpcd[DP_DSC_MAX_BITS_PER_PIXEL_HI - DP_DSC_SUPPORT] &
		 DP_DSC_MAX_BITS_PER_PIXEL_HI_MASK <<
		 DP_DSC_MAX_BITS_PER_PIXEL_HI_SHIFT);
पूर्ण

अटल अंतरभूत u32
drm_dp_dsc_sink_max_slice_width(स्थिर u8 dsc_dpcd[DP_DSC_RECEIVER_CAP_SIZE])
अणु
	/* Max Slicewidth = Number of Pixels * 320 */
	वापस dsc_dpcd[DP_DSC_MAX_SLICE_WIDTH - DP_DSC_SUPPORT] *
		DP_DSC_SLICE_WIDTH_MULTIPLIER;
पूर्ण

/* Forward Error Correction Support on DP 1.4 */
अटल अंतरभूत bool
drm_dp_sink_supports_fec(स्थिर u8 fec_capable)
अणु
	वापस fec_capable & DP_FEC_CAPABLE;
पूर्ण

अटल अंतरभूत bool
drm_dp_channel_coding_supported(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस dpcd[DP_MAIN_LINK_CHANNEL_CODING] & DP_CAP_ANSI_8B10B;
पूर्ण

अटल अंतरभूत bool
drm_dp_alternate_scrambler_reset_cap(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस dpcd[DP_EDP_CONFIGURATION_CAP] &
			DP_ALTERNATE_SCRAMBLER_RESET_CAP;
पूर्ण

/* Ignore MSA timing क्रम Adaptive Sync support on DP 1.4 */
अटल अंतरभूत bool
drm_dp_sink_can_करो_video_without_timing_msa(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE])
अणु
	वापस dpcd[DP_DOWN_STREAM_PORT_COUNT] &
		DP_MSA_TIMING_PAR_IGNORED;
पूर्ण

/*
 * DisplayPort AUX channel
 */

/**
 * काष्ठा drm_dp_aux_msg - DisplayPort AUX channel transaction
 * @address: address of the (first) रेजिस्टर to access
 * @request: contains the type of transaction (see DP_AUX_* macros)
 * @reply: upon completion, contains the reply type of the transaction
 * @buffer: poपूर्णांकer to a transmission or reception buffer
 * @size: size of @buffer
 */
काष्ठा drm_dp_aux_msg अणु
	अचिन्हित पूर्णांक address;
	u8 request;
	u8 reply;
	व्योम *buffer;
	माप_प्रकार size;
पूर्ण;

काष्ठा cec_adapter;
काष्ठा edid;
काष्ठा drm_connector;

/**
 * काष्ठा drm_dp_aux_cec - DisplayPort CEC-Tunneling-over-AUX
 * @lock: mutex protecting this काष्ठा
 * @adap: the CEC adapter क्रम CEC-Tunneling-over-AUX support.
 * @connector: the connector this CEC adapter is associated with
 * @unरेजिस्टर_work: unरेजिस्टर the CEC adapter
 */
काष्ठा drm_dp_aux_cec अणु
	काष्ठा mutex lock;
	काष्ठा cec_adapter *adap;
	काष्ठा drm_connector *connector;
	काष्ठा delayed_work unरेजिस्टर_work;
पूर्ण;

/**
 * काष्ठा drm_dp_aux - DisplayPort AUX channel
 * @name: user-visible name of this AUX channel and the I2C-over-AUX adapter
 * @ddc: I2C adapter that can be used क्रम I2C-over-AUX communication
 * @dev: poपूर्णांकer to काष्ठा device that is the parent क्रम this AUX channel
 * @crtc: backpoपूर्णांकer to the crtc that is currently using this AUX channel
 * @hw_mutex: पूर्णांकernal mutex used क्रम locking transfers
 * @crc_work: worker that captures CRCs क्रम each frame
 * @crc_count: counter of captured frame CRCs
 * @transfer: transfers a message representing a single AUX transaction
 *
 * The @dev field should be set to a poपूर्णांकer to the device that implements the
 * AUX channel.
 *
 * The @name field may be used to specअगरy the name of the I2C adapter. If set to
 * %शून्य, dev_name() of @dev will be used.
 *
 * Drivers provide a hardware-specअगरic implementation of how transactions are
 * executed via the @transfer() function. A poपूर्णांकer to a &drm_dp_aux_msg
 * काष्ठाure describing the transaction is passed पूर्णांकo this function. Upon
 * success, the implementation should वापस the number of payload bytes that
 * were transferred, or a negative error-code on failure. Helpers propagate
 * errors from the @transfer() function, with the exception of the %-EBUSY
 * error, which causes a transaction to be retried. On a लघु, helpers will
 * वापस %-EPROTO to make it simpler to check क्रम failure.
 *
 * An AUX channel can also be used to transport I2C messages to a sink. A
 * typical application of that is to access an EDID that's present in the sink
 * device. The @transfer() function can also be used to execute such
 * transactions. The drm_dp_aux_रेजिस्टर() function रेजिस्टरs an I2C adapter
 * that can be passed to drm_probe_ddc(). Upon removal, drivers should call
 * drm_dp_aux_unरेजिस्टर() to हटाओ the I2C adapter. The I2C adapter uses दीर्घ
 * transfers by शेष; अगर a partial response is received, the adapter will
 * drop करोwn to the size given by the partial response क्रम this transaction
 * only.
 *
 * Note that the aux helper code assumes that the @transfer() function only
 * modअगरies the reply field of the &drm_dp_aux_msg काष्ठाure. The retry logic
 * and i2c helpers assume this is the हाल.
 */
काष्ठा drm_dp_aux अणु
	स्थिर अक्षर *name;
	काष्ठा i2c_adapter ddc;
	काष्ठा device *dev;
	काष्ठा drm_crtc *crtc;
	काष्ठा mutex hw_mutex;
	काष्ठा work_काष्ठा crc_work;
	u8 crc_count;
	sमाप_प्रकार (*transfer)(काष्ठा drm_dp_aux *aux,
			    काष्ठा drm_dp_aux_msg *msg);
	/**
	 * @i2c_nack_count: Counts I2C NACKs, used क्रम DP validation.
	 */
	अचिन्हित i2c_nack_count;
	/**
	 * @i2c_defer_count: Counts I2C DEFERs, used क्रम DP validation.
	 */
	अचिन्हित i2c_defer_count;
	/**
	 * @cec: काष्ठा containing fields used क्रम CEC-Tunneling-over-AUX.
	 */
	काष्ठा drm_dp_aux_cec cec;
	/**
	 * @is_remote: Is this AUX CH actually using sideband messaging.
	 */
	bool is_remote;
पूर्ण;

sमाप_प्रकार drm_dp_dpcd_पढ़ो(काष्ठा drm_dp_aux *aux, अचिन्हित पूर्णांक offset,
			 व्योम *buffer, माप_प्रकार size);
sमाप_प्रकार drm_dp_dpcd_ग_लिखो(काष्ठा drm_dp_aux *aux, अचिन्हित पूर्णांक offset,
			  व्योम *buffer, माप_प्रकार size);

/**
 * drm_dp_dpcd_पढ़ोb() - पढ़ो a single byte from the DPCD
 * @aux: DisplayPort AUX channel
 * @offset: address of the रेजिस्टर to पढ़ो
 * @valuep: location where the value of the रेजिस्टर will be stored
 *
 * Returns the number of bytes transferred (1) on success, or a negative
 * error code on failure.
 */
अटल अंतरभूत sमाप_प्रकार drm_dp_dpcd_पढ़ोb(काष्ठा drm_dp_aux *aux,
					अचिन्हित पूर्णांक offset, u8 *valuep)
अणु
	वापस drm_dp_dpcd_पढ़ो(aux, offset, valuep, 1);
पूर्ण

/**
 * drm_dp_dpcd_ग_लिखोb() - ग_लिखो a single byte to the DPCD
 * @aux: DisplayPort AUX channel
 * @offset: address of the रेजिस्टर to ग_लिखो
 * @value: value to ग_लिखो to the रेजिस्टर
 *
 * Returns the number of bytes transferred (1) on success, or a negative
 * error code on failure.
 */
अटल अंतरभूत sमाप_प्रकार drm_dp_dpcd_ग_लिखोb(काष्ठा drm_dp_aux *aux,
					 अचिन्हित पूर्णांक offset, u8 value)
अणु
	वापस drm_dp_dpcd_ग_लिखो(aux, offset, &value, 1);
पूर्ण

पूर्णांक drm_dp_पढ़ो_dpcd_caps(काष्ठा drm_dp_aux *aux,
			  u8 dpcd[DP_RECEIVER_CAP_SIZE]);

पूर्णांक drm_dp_dpcd_पढ़ो_link_status(काष्ठा drm_dp_aux *aux,
				 u8 status[DP_LINK_STATUS_SIZE]);

पूर्णांक drm_dp_dpcd_पढ़ो_phy_link_status(काष्ठा drm_dp_aux *aux,
				     क्रमागत drm_dp_phy dp_phy,
				     u8 link_status[DP_LINK_STATUS_SIZE]);

bool drm_dp_send_real_edid_checksum(काष्ठा drm_dp_aux *aux,
				    u8 real_edid_checksum);

पूर्णांक drm_dp_पढ़ो_करोwnstream_info(काष्ठा drm_dp_aux *aux,
				स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				u8 करोwnstream_ports[DP_MAX_DOWNSTREAM_PORTS]);
bool drm_dp_करोwnstream_is_type(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			       स्थिर u8 port_cap[4], u8 type);
bool drm_dp_करोwnstream_is_पंचांगds(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			       स्थिर u8 port_cap[4],
			       स्थिर काष्ठा edid *edid);
पूर्णांक drm_dp_करोwnstream_max_करोtघड़ी(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				   स्थिर u8 port_cap[4]);
पूर्णांक drm_dp_करोwnstream_max_पंचांगds_घड़ी(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				     स्थिर u8 port_cap[4],
				     स्थिर काष्ठा edid *edid);
पूर्णांक drm_dp_करोwnstream_min_पंचांगds_घड़ी(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				     स्थिर u8 port_cap[4],
				     स्थिर काष्ठा edid *edid);
पूर्णांक drm_dp_करोwnstream_max_bpc(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			      स्थिर u8 port_cap[4],
			      स्थिर काष्ठा edid *edid);
bool drm_dp_करोwnstream_420_passthrough(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				       स्थिर u8 port_cap[4]);
bool drm_dp_करोwnstream_444_to_420_conversion(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
					     स्थिर u8 port_cap[4]);
काष्ठा drm_display_mode *drm_dp_करोwnstream_mode(काष्ठा drm_device *dev,
						स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
						स्थिर u8 port_cap[4]);
पूर्णांक drm_dp_करोwnstream_id(काष्ठा drm_dp_aux *aux, अक्षर id[6]);
व्योम drm_dp_करोwnstream_debug(काष्ठा seq_file *m,
			     स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			     स्थिर u8 port_cap[4],
			     स्थिर काष्ठा edid *edid,
			     काष्ठा drm_dp_aux *aux);
क्रमागत drm_mode_subconnector
drm_dp_subconnector_type(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			 स्थिर u8 port_cap[4]);
व्योम drm_dp_set_subconnector_property(काष्ठा drm_connector *connector,
				      क्रमागत drm_connector_status status,
				      स्थिर u8 *dpcd,
				      स्थिर u8 port_cap[4]);

काष्ठा drm_dp_desc;
bool drm_dp_पढ़ो_sink_count_cap(काष्ठा drm_connector *connector,
				स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
				स्थिर काष्ठा drm_dp_desc *desc);
पूर्णांक drm_dp_पढ़ो_sink_count(काष्ठा drm_dp_aux *aux);

पूर्णांक drm_dp_पढ़ो_lttpr_common_caps(काष्ठा drm_dp_aux *aux,
				  u8 caps[DP_LTTPR_COMMON_CAP_SIZE]);
पूर्णांक drm_dp_पढ़ो_lttpr_phy_caps(काष्ठा drm_dp_aux *aux,
			       क्रमागत drm_dp_phy dp_phy,
			       u8 caps[DP_LTTPR_PHY_CAP_SIZE]);
पूर्णांक drm_dp_lttpr_count(स्थिर u8 cap[DP_LTTPR_COMMON_CAP_SIZE]);
पूर्णांक drm_dp_lttpr_max_link_rate(स्थिर u8 caps[DP_LTTPR_COMMON_CAP_SIZE]);
पूर्णांक drm_dp_lttpr_max_lane_count(स्थिर u8 caps[DP_LTTPR_COMMON_CAP_SIZE]);
bool drm_dp_lttpr_voltage_swing_level_3_supported(स्थिर u8 caps[DP_LTTPR_PHY_CAP_SIZE]);
bool drm_dp_lttpr_pre_emphasis_level_3_supported(स्थिर u8 caps[DP_LTTPR_PHY_CAP_SIZE]);

व्योम drm_dp_remote_aux_init(काष्ठा drm_dp_aux *aux);
व्योम drm_dp_aux_init(काष्ठा drm_dp_aux *aux);
पूर्णांक drm_dp_aux_रेजिस्टर(काष्ठा drm_dp_aux *aux);
व्योम drm_dp_aux_unरेजिस्टर(काष्ठा drm_dp_aux *aux);

पूर्णांक drm_dp_start_crc(काष्ठा drm_dp_aux *aux, काष्ठा drm_crtc *crtc);
पूर्णांक drm_dp_stop_crc(काष्ठा drm_dp_aux *aux);

काष्ठा drm_dp_dpcd_ident अणु
	u8 oui[3];
	u8 device_id[6];
	u8 hw_rev;
	u8 sw_major_rev;
	u8 sw_minor_rev;
पूर्ण __packed;

/**
 * काष्ठा drm_dp_desc - DP branch/sink device descriptor
 * @ident: DP device identअगरication from DPCD 0x400 (sink) or 0x500 (branch).
 * @quirks: Quirks; use drm_dp_has_quirk() to query क्रम the quirks.
 */
काष्ठा drm_dp_desc अणु
	काष्ठा drm_dp_dpcd_ident ident;
	u32 quirks;
पूर्ण;

पूर्णांक drm_dp_पढ़ो_desc(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_desc *desc,
		     bool is_branch);

/**
 * क्रमागत drm_dp_quirk - Display Port sink/branch device specअगरic quirks
 *
 * Display Port sink and branch devices in the wild have a variety of bugs, try
 * to collect them here. The quirks are shared, but it's up to the drivers to
 * implement workarounds क्रम them.
 */
क्रमागत drm_dp_quirk अणु
	/**
	 * @DP_DPCD_QUIRK_CONSTANT_N:
	 *
	 * The device requires मुख्य link attributes Mvid and Nvid to be limited
	 * to 16 bits. So will give a स्थिरant value (0x8000) क्रम compatability.
	 */
	DP_DPCD_QUIRK_CONSTANT_N,
	/**
	 * @DP_DPCD_QUIRK_NO_PSR:
	 *
	 * The device करोes not support PSR even अगर reports that it supports or
	 * driver still need to implement proper handling क्रम such device.
	 */
	DP_DPCD_QUIRK_NO_PSR,
	/**
	 * @DP_DPCD_QUIRK_NO_SINK_COUNT:
	 *
	 * The device करोes not set SINK_COUNT to a non-zero value.
	 * The driver should ignore SINK_COUNT during detection. Note that
	 * drm_dp_पढ़ो_sink_count_cap() स्वतःmatically checks क्रम this quirk.
	 */
	DP_DPCD_QUIRK_NO_SINK_COUNT,
	/**
	 * @DP_DPCD_QUIRK_DSC_WITHOUT_VIRTUAL_DPCD:
	 *
	 * The device supports MST DSC despite not supporting Virtual DPCD.
	 * The DSC caps can be पढ़ो from the physical aux instead.
	 */
	DP_DPCD_QUIRK_DSC_WITHOUT_VIRTUAL_DPCD,
	/**
	 * @DP_DPCD_QUIRK_CAN_DO_MAX_LINK_RATE_3_24_GBPS:
	 *
	 * The device supports a link rate of 3.24 Gbps (multiplier 0xc) despite
	 * the DP_MAX_LINK_RATE रेजिस्टर reporting a lower max multiplier.
	 */
	DP_DPCD_QUIRK_CAN_DO_MAX_LINK_RATE_3_24_GBPS,
पूर्ण;

/**
 * drm_dp_has_quirk() - करोes the DP device have a specअगरic quirk
 * @desc: Device descriptor filled by drm_dp_पढ़ो_desc()
 * @quirk: Quirk to query क्रम
 *
 * Return true अगर DP device identअगरied by @desc has @quirk.
 */
अटल अंतरभूत bool
drm_dp_has_quirk(स्थिर काष्ठा drm_dp_desc *desc, क्रमागत drm_dp_quirk quirk)
अणु
	वापस desc->quirks & BIT(quirk);
पूर्ण

#अगर_घोषित CONFIG_DRM_DP_CEC
व्योम drm_dp_cec_irq(काष्ठा drm_dp_aux *aux);
व्योम drm_dp_cec_रेजिस्टर_connector(काष्ठा drm_dp_aux *aux,
				   काष्ठा drm_connector *connector);
व्योम drm_dp_cec_unरेजिस्टर_connector(काष्ठा drm_dp_aux *aux);
व्योम drm_dp_cec_set_edid(काष्ठा drm_dp_aux *aux, स्थिर काष्ठा edid *edid);
व्योम drm_dp_cec_unset_edid(काष्ठा drm_dp_aux *aux);
#अन्यथा
अटल अंतरभूत व्योम drm_dp_cec_irq(काष्ठा drm_dp_aux *aux)
अणु
पूर्ण

अटल अंतरभूत व्योम
drm_dp_cec_रेजिस्टर_connector(काष्ठा drm_dp_aux *aux,
			      काष्ठा drm_connector *connector)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_dp_cec_unरेजिस्टर_connector(काष्ठा drm_dp_aux *aux)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_dp_cec_set_edid(काष्ठा drm_dp_aux *aux,
				       स्थिर काष्ठा edid *edid)
अणु
पूर्ण

अटल अंतरभूत व्योम drm_dp_cec_unset_edid(काष्ठा drm_dp_aux *aux)
अणु
पूर्ण

#पूर्ण_अगर

/**
 * काष्ठा drm_dp_phy_test_params - DP Phy Compliance parameters
 * @link_rate: Requested Link rate from DPCD 0x219
 * @num_lanes: Number of lanes requested by sing through DPCD 0x220
 * @phy_pattern: DP Phy test pattern from DPCD 0x248
 * @hbr2_reset: DP HBR2_COMPLIANCE_SCRAMBLER_RESET from DCPD 0x24A and 0x24B
 * @custom80: DP Test_80BIT_CUSTOM_PATTERN from DPCDs 0x250 through 0x259
 * @enhanced_frame_cap: flag क्रम enhanced frame capability.
 */
काष्ठा drm_dp_phy_test_params अणु
	पूर्णांक link_rate;
	u8 num_lanes;
	u8 phy_pattern;
	u8 hbr2_reset[2];
	u8 custom80[10];
	bool enhanced_frame_cap;
पूर्ण;

पूर्णांक drm_dp_get_phy_test_pattern(काष्ठा drm_dp_aux *aux,
				काष्ठा drm_dp_phy_test_params *data);
पूर्णांक drm_dp_set_phy_test_pattern(काष्ठा drm_dp_aux *aux,
				काष्ठा drm_dp_phy_test_params *data, u8 dp_rev);
पूर्णांक drm_dp_get_pcon_max_frl_bw(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
			       स्थिर u8 port_cap[4]);
पूर्णांक drm_dp_pcon_frl_prepare(काष्ठा drm_dp_aux *aux, bool enable_frl_पढ़ोy_hpd);
bool drm_dp_pcon_is_frl_पढ़ोy(काष्ठा drm_dp_aux *aux);
पूर्णांक drm_dp_pcon_frl_configure_1(काष्ठा drm_dp_aux *aux, पूर्णांक max_frl_gbps,
				u8 frl_mode);
पूर्णांक drm_dp_pcon_frl_configure_2(काष्ठा drm_dp_aux *aux, पूर्णांक max_frl_mask,
				u8 frl_type);
पूर्णांक drm_dp_pcon_reset_frl_config(काष्ठा drm_dp_aux *aux);
पूर्णांक drm_dp_pcon_frl_enable(काष्ठा drm_dp_aux *aux);

bool drm_dp_pcon_hdmi_link_active(काष्ठा drm_dp_aux *aux);
पूर्णांक drm_dp_pcon_hdmi_link_mode(काष्ठा drm_dp_aux *aux, u8 *frl_trained_mask);
व्योम drm_dp_pcon_hdmi_frl_link_error_count(काष्ठा drm_dp_aux *aux,
					   काष्ठा drm_connector *connector);
bool drm_dp_pcon_enc_is_dsc_1_2(स्थिर u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODER_CAP_SIZE]);
पूर्णांक drm_dp_pcon_dsc_max_slices(स्थिर u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODER_CAP_SIZE]);
पूर्णांक drm_dp_pcon_dsc_max_slice_width(स्थिर u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODER_CAP_SIZE]);
पूर्णांक drm_dp_pcon_dsc_bpp_incr(स्थिर u8 pcon_dsc_dpcd[DP_PCON_DSC_ENCODER_CAP_SIZE]);
पूर्णांक drm_dp_pcon_pps_शेष(काष्ठा drm_dp_aux *aux);
पूर्णांक drm_dp_pcon_pps_override_buf(काष्ठा drm_dp_aux *aux, u8 pps_buf[128]);
पूर्णांक drm_dp_pcon_pps_override_param(काष्ठा drm_dp_aux *aux, u8 pps_param[6]);
bool drm_dp_करोwnstream_rgb_to_ycbcr_conversion(स्थिर u8 dpcd[DP_RECEIVER_CAP_SIZE],
					       स्थिर u8 port_cap[4], u8 color_spc);
पूर्णांक drm_dp_pcon_convert_rgb_to_ycbcr(काष्ठा drm_dp_aux *aux, u8 color_spc);

#पूर्ण_अगर /* _DRM_DP_HELPER_H_ */
