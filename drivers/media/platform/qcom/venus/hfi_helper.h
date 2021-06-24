<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#अगर_अघोषित __VENUS_HFI_HELPER_H__
#घोषणा __VENUS_HFI_HELPER_H__

#घोषणा HFI_DOMAIN_BASE_COMMON				0

#घोषणा HFI_DOMAIN_BASE_VDEC				0x1000000
#घोषणा HFI_DOMAIN_BASE_VENC				0x2000000
#घोषणा HFI_DOMAIN_BASE_VPE				0x3000000

#घोषणा HFI_VIDEO_ARCH_OX				0x1

#घोषणा HFI_ARCH_COMMON_OFFSET				0
#घोषणा HFI_ARCH_OX_OFFSET				0x200000

#घोषणा HFI_OX_BASE					0x1000000

#घोषणा HFI_CMD_START_OFFSET				0x10000
#घोषणा HFI_MSG_START_OFFSET				0x20000

#घोषणा HFI_ERR_NONE					0x0
#घोषणा HFI_ERR_SYS_FATAL				0x1
#घोषणा HFI_ERR_SYS_INVALID_PARAMETER			0x2
#घोषणा HFI_ERR_SYS_VERSION_MISMATCH			0x3
#घोषणा HFI_ERR_SYS_INSUFFICIENT_RESOURCES		0x4
#घोषणा HFI_ERR_SYS_MAX_SESSIONS_REACHED		0x5
#घोषणा HFI_ERR_SYS_UNSUPPORTED_CODEC			0x6
#घोषणा HFI_ERR_SYS_SESSION_IN_USE			0x7
#घोषणा HFI_ERR_SYS_SESSION_ID_OUT_OF_RANGE		0x8
#घोषणा HFI_ERR_SYS_UNSUPPORTED_DOMAIN			0x9

#घोषणा HFI_ERR_SESSION_FATAL				0x1001
#घोषणा HFI_ERR_SESSION_INVALID_PARAMETER		0x1002
#घोषणा HFI_ERR_SESSION_BAD_POINTER			0x1003
#घोषणा HFI_ERR_SESSION_INVALID_SESSION_ID		0x1004
#घोषणा HFI_ERR_SESSION_INVALID_STREAM_ID		0x1005
#घोषणा HFI_ERR_SESSION_INCORRECT_STATE_OPERATION	0x1006
#घोषणा HFI_ERR_SESSION_UNSUPPORTED_PROPERTY		0x1007
#घोषणा HFI_ERR_SESSION_UNSUPPORTED_SETTING		0x1008
#घोषणा HFI_ERR_SESSION_INSUFFICIENT_RESOURCES		0x1009
#घोषणा HFI_ERR_SESSION_STREAM_CORRUPT_OUTPUT_STALLED	0x100a
#घोषणा HFI_ERR_SESSION_STREAM_CORRUPT			0x100b
#घोषणा HFI_ERR_SESSION_ENC_OVERFLOW			0x100c
#घोषणा HFI_ERR_SESSION_UNSUPPORTED_STREAM		0x100d
#घोषणा HFI_ERR_SESSION_CMDSIZE				0x100e
#घोषणा HFI_ERR_SESSION_UNSUPPORT_CMD			0x100f
#घोषणा HFI_ERR_SESSION_UNSUPPORT_BUFFERTYPE		0x1010
#घोषणा HFI_ERR_SESSION_BUFFERCOUNT_TOOSMALL		0x1011
#घोषणा HFI_ERR_SESSION_INVALID_SCALE_FACTOR		0x1012
#घोषणा HFI_ERR_SESSION_UPSCALE_NOT_SUPPORTED		0x1013

#घोषणा HFI_EVENT_SYS_ERROR				0x1
#घोषणा HFI_EVENT_SESSION_ERROR				0x2

#घोषणा HFI_EVENT_DATA_SEQUENCE_CHANGED_SUFFICIENT_BUF_RESOURCES   0x1000001
#घोषणा HFI_EVENT_DATA_SEQUENCE_CHANGED_INSUFFICIENT_BUF_RESOURCES 0x1000002
#घोषणा HFI_EVENT_SESSION_SEQUENCE_CHANGED			   0x1000003
#घोषणा HFI_EVENT_SESSION_PROPERTY_CHANGED			   0x1000004
#घोषणा HFI_EVENT_SESSION_LTRUSE_FAILED				   0x1000005
#घोषणा HFI_EVENT_RELEASE_BUFFER_REFERENCE			   0x1000006

#घोषणा HFI_BUFFERFLAG_EOS				0x00000001
#घोषणा HFI_BUFFERFLAG_STARTTIME			0x00000002
#घोषणा HFI_BUFFERFLAG_DECODEONLY			0x00000004
#घोषणा HFI_BUFFERFLAG_DATACORRUPT			0x00000008
#घोषणा HFI_BUFFERFLAG_ENDOFFRAME			0x00000010
#घोषणा HFI_BUFFERFLAG_SYNCFRAME			0x00000020
#घोषणा HFI_BUFFERFLAG_EXTRADATA			0x00000040
#घोषणा HFI_BUFFERFLAG_CODECCONFIG			0x00000080
#घोषणा HFI_BUFFERFLAG_TIMESTAMPINVALID			0x00000100
#घोषणा HFI_BUFFERFLAG_READONLY				0x00000200
#घोषणा HFI_BUFFERFLAG_ENDOFSUBFRAME			0x00000400
#घोषणा HFI_BUFFERFLAG_EOSEQ				0x00200000
#घोषणा HFI_BUFFERFLAG_MBAFF				0x08000000
#घोषणा HFI_BUFFERFLAG_VPE_YUV_601_709_CSC_CLAMP	0x10000000
#घोषणा HFI_BUFFERFLAG_DROP_FRAME			0x20000000
#घोषणा HFI_BUFFERFLAG_TEI				0x40000000
#घोषणा HFI_BUFFERFLAG_DISCONTINUITY			0x80000000

#घोषणा HFI_ERR_SESSION_EMPTY_BUFFER_DONE_OUTPUT_PENDING	0x1001001
#घोषणा HFI_ERR_SESSION_SAME_STATE_OPERATION			0x1001002
#घोषणा HFI_ERR_SESSION_SYNC_FRAME_NOT_DETECTED			0x1001003
#घोषणा HFI_ERR_SESSION_START_CODE_NOT_FOUND			0x1001004

#घोषणा HFI_FLUSH_INPUT					0x1000001
#घोषणा HFI_FLUSH_OUTPUT				0x1000002
#घोषणा HFI_FLUSH_OUTPUT2				0x1000003
#घोषणा HFI_FLUSH_ALL					0x1000004

#घोषणा HFI_EXTRADATA_NONE				0x00000000
#घोषणा HFI_EXTRADATA_MB_QUANTIZATION			0x00000001
#घोषणा HFI_EXTRADATA_INTERLACE_VIDEO			0x00000002
#घोषणा HFI_EXTRADATA_VC1_FRAMEDISP			0x00000003
#घोषणा HFI_EXTRADATA_VC1_SEQDISP			0x00000004
#घोषणा HFI_EXTRADATA_TIMESTAMP				0x00000005
#घोषणा HFI_EXTRADATA_S3D_FRAME_PACKING			0x00000006
#घोषणा HFI_EXTRADATA_FRAME_RATE			0x00000007
#घोषणा HFI_EXTRADATA_PANSCAN_WINDOW			0x00000008
#घोषणा HFI_EXTRADATA_RECOVERY_POINT_SEI		0x00000009
#घोषणा HFI_EXTRADATA_MPEG2_SEQDISP			0x0000000d
#घोषणा HFI_EXTRADATA_STREAM_USERDATA			0x0000000e
#घोषणा HFI_EXTRADATA_FRAME_QP				0x0000000f
#घोषणा HFI_EXTRADATA_FRAME_BITS_INFO			0x00000010
#घोषणा HFI_EXTRADATA_MULTISLICE_INFO			0x7f100000
#घोषणा HFI_EXTRADATA_NUM_CONCEALED_MB			0x7f100001
#घोषणा HFI_EXTRADATA_INDEX				0x7f100002
#घोषणा HFI_EXTRADATA_METADATA_LTR			0x7f100004
#घोषणा HFI_EXTRADATA_METADATA_FILLER			0x7fe00002

#घोषणा HFI_INDEX_EXTRADATA_INPUT_CROP			0x0700000e
#घोषणा HFI_INDEX_EXTRADATA_OUTPUT_CROP			0x0700000f
#घोषणा HFI_INDEX_EXTRADATA_DIGITAL_ZOOM		0x07000010
#घोषणा HFI_INDEX_EXTRADATA_ASPECT_RATIO		0x7f100003

#घोषणा HFI_INTERLACE_FRAME_PROGRESSIVE			0x01
#घोषणा HFI_INTERLACE_INTERLEAVE_FRAME_TOPFIELDFIRST	0x02
#घोषणा HFI_INTERLACE_INTERLEAVE_FRAME_BOTTOMFIELDFIRST	0x04
#घोषणा HFI_INTERLACE_FRAME_TOPFIELDFIRST		0x08
#घोषणा HFI_INTERLACE_FRAME_BOTTOMFIELDFIRST		0x10

/*
 * HFI_PROPERTY_PARAM_OX_START
 * HFI_DOMAIN_BASE_COMMON + HFI_ARCH_OX_OFFSET + 0x1000
 */
#घोषणा HFI_PROPERTY_PARAM_BUFFER_COUNT_ACTUAL				0x201001
#घोषणा HFI_PROPERTY_PARAM_UNCOMPRESSED_PLANE_ACTUAL_CONSTRAINTS_INFO	0x201002
#घोषणा HFI_PROPERTY_PARAM_INTERLACE_FORMAT_SUPPORTED			0x201003
#घोषणा HFI_PROPERTY_PARAM_CHROMA_SITE					0x201004
#घोषणा HFI_PROPERTY_PARAM_EXTRA_DATA_HEADER_CONFIG			0x201005
#घोषणा HFI_PROPERTY_PARAM_INDEX_EXTRADATA				0x201006
#घोषणा HFI_PROPERTY_PARAM_DIVX_FORMAT					0x201007
#घोषणा HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE				0x201008
#घोषणा HFI_PROPERTY_PARAM_S3D_FRAME_PACKING_EXTRADATA			0x201009
#घोषणा HFI_PROPERTY_PARAM_ERR_DETECTION_CODE_EXTRADATA			0x20100a
#घोषणा HFI_PROPERTY_PARAM_BUFFER_ALLOC_MODE_SUPPORTED			0x20100b
#घोषणा HFI_PROPERTY_PARAM_BUFFER_SIZE_ACTUAL				0x20100c
#घोषणा HFI_PROPERTY_PARAM_BUFFER_DISPLAY_HOLD_COUNT_ACTUAL		0x20100d

/*
 * HFI_PROPERTY_CONFIG_OX_START
 * HFI_DOMAIN_BASE_COMMON + HFI_ARCH_OX_OFFSET + 0x2000
 */
#घोषणा HFI_PROPERTY_CONFIG_BUFFER_REQUIREMENTS		0x202001
#घोषणा HFI_PROPERTY_CONFIG_REALTIME			0x202002
#घोषणा HFI_PROPERTY_CONFIG_PRIORITY			0x202003
#घोषणा HFI_PROPERTY_CONFIG_BATCH_INFO			0x202004

/*
 * HFI_PROPERTY_PARAM_VDEC_OX_START	\
 * HFI_DOMAIN_BASE_VDEC + HFI_ARCH_OX_OFFSET + 0x3000
 */
#घोषणा HFI_PROPERTY_PARAM_VDEC_CONTINUE_DATA_TRANSFER		0x1203001
#घोषणा HFI_PROPERTY_PARAM_VDEC_DISPLAY_PICTURE_BUFFER_COUNT	0x1203002
#घोषणा HFI_PROPERTY_PARAM_VDEC_MULTI_VIEW_SELECT		0x1203003
#घोषणा HFI_PROPERTY_PARAM_VDEC_PICTURE_TYPE_DECODE		0x1203004
#घोषणा HFI_PROPERTY_PARAM_VDEC_OUTPUT_ORDER			0x1203005
#घोषणा HFI_PROPERTY_PARAM_VDEC_MB_QUANTIZATION			0x1203006
#घोषणा HFI_PROPERTY_PARAM_VDEC_NUM_CONCEALED_MB		0x1203007
#घोषणा HFI_PROPERTY_PARAM_VDEC_H264_ENTROPY_SWITCHING		0x1203008
#घोषणा HFI_PROPERTY_PARAM_VDEC_OUTPUT2_KEEP_ASPECT_RATIO	0x1203009
#घोषणा HFI_PROPERTY_PARAM_VDEC_FRAME_RATE_EXTRADATA		0x120300a
#घोषणा HFI_PROPERTY_PARAM_VDEC_PANSCAN_WNDW_EXTRADATA		0x120300b
#घोषणा HFI_PROPERTY_PARAM_VDEC_RECOVERY_POINT_SEI_EXTRADATA	0x120300c
#घोषणा HFI_PROPERTY_PARAM_VDEC_THUMBNAIL_MODE			0x120300d
#घोषणा HFI_PROPERTY_PARAM_VDEC_FRAME_ASSEMBLY			0x120300e
#घोषणा HFI_PROPERTY_PARAM_VDEC_VC1_FRAMEDISP_EXTRADATA		0x1203011
#घोषणा HFI_PROPERTY_PARAM_VDEC_VC1_SEQDISP_EXTRADATA		0x1203012
#घोषणा HFI_PROPERTY_PARAM_VDEC_TIMESTAMP_EXTRADATA		0x1203013
#घोषणा HFI_PROPERTY_PARAM_VDEC_INTERLACE_VIDEO_EXTRADATA	0x1203014
#घोषणा HFI_PROPERTY_PARAM_VDEC_AVC_SESSION_SELECT		0x1203015
#घोषणा HFI_PROPERTY_PARAM_VDEC_MPEG2_SEQDISP_EXTRADATA		0x1203016
#घोषणा HFI_PROPERTY_PARAM_VDEC_STREAM_USERDATA_EXTRADATA	0x1203017
#घोषणा HFI_PROPERTY_PARAM_VDEC_FRAME_QP_EXTRADATA		0x1203018
#घोषणा HFI_PROPERTY_PARAM_VDEC_FRAME_BITS_INFO_EXTRADATA	0x1203019
#घोषणा HFI_PROPERTY_PARAM_VDEC_SCS_THRESHOLD			0x120301a

/*
 * HFI_PROPERTY_CONFIG_VDEC_OX_START
 * HFI_DOMAIN_BASE_VDEC + HFI_ARCH_OX_OFFSET + 0x0000
 */
#घोषणा HFI_PROPERTY_CONFIG_VDEC_POST_LOOP_DEBLOCKER		0x1200001
#घोषणा HFI_PROPERTY_CONFIG_VDEC_MB_ERROR_MAP_REPORTING		0x1200002
#घोषणा HFI_PROPERTY_CONFIG_VDEC_MB_ERROR_MAP			0x1200003

#घोषणा HFI_PROPERTY_CONFIG_VDEC_ENTROPY			0x1204004

/*
 * HFI_PROPERTY_PARAM_VENC_OX_START
 * HFI_DOMAIN_BASE_VENC + HFI_ARCH_OX_OFFSET + 0x5000
 */
#घोषणा  HFI_PROPERTY_PARAM_VENC_MULTI_SLICE_INFO		0x2205001
#घोषणा  HFI_PROPERTY_PARAM_VENC_H264_IDR_S3D_FRAME_PACKING_NAL	0x2205002
#घोषणा  HFI_PROPERTY_PARAM_VENC_LTR_INFO			0x2205003
#घोषणा  HFI_PROPERTY_PARAM_VENC_MBI_DUMPING			0x2205005

/*
 * HFI_PROPERTY_CONFIG_VENC_OX_START
 * HFI_DOMAIN_BASE_VENC + HFI_ARCH_OX_OFFSET + 0x6000
 */
#घोषणा HFI_PROPERTY_CONFIG_VENC_FRAME_QP			0x2206001

/*
 * HFI_PROPERTY_PARAM_VPE_OX_START
 * HFI_DOMAIN_BASE_VPE + HFI_ARCH_OX_OFFSET + 0x7000
 */
#घोषणा HFI_PROPERTY_PARAM_VPE_COLOR_SPACE_CONVERSION		0x3207001

#घोषणा HFI_PROPERTY_CONFIG_VPE_OX_START	\
	(HFI_DOMAIN_BASE_VPE + HFI_ARCH_OX_OFFSET + 0x8000)

#घोषणा HFI_CHROMA_SITE_0			0x1000001
#घोषणा HFI_CHROMA_SITE_1			0x1000002
#घोषणा HFI_CHROMA_SITE_2			0x1000003
#घोषणा HFI_CHROMA_SITE_3			0x1000004
#घोषणा HFI_CHROMA_SITE_4			0x1000005
#घोषणा HFI_CHROMA_SITE_5			0x1000006

#घोषणा HFI_PRIORITY_LOW			10
#घोषणा HFI_PRIOIRTY_MEDIUM			20
#घोषणा HFI_PRIORITY_HIGH			30

#घोषणा HFI_OUTPUT_ORDER_DISPLAY		0x1000001
#घोषणा HFI_OUTPUT_ORDER_DECODE			0x1000002

#घोषणा HFI_RATE_CONTROL_OFF			0x1000001
#घोषणा HFI_RATE_CONTROL_VBR_VFR		0x1000002
#घोषणा HFI_RATE_CONTROL_VBR_CFR		0x1000003
#घोषणा HFI_RATE_CONTROL_CBR_VFR		0x1000004
#घोषणा HFI_RATE_CONTROL_CBR_CFR		0x1000005
#घोषणा HFI_RATE_CONTROL_CQ			0x1000008

#घोषणा HFI_VIDEO_CODEC_H264			0x00000002
#घोषणा HFI_VIDEO_CODEC_H263			0x00000004
#घोषणा HFI_VIDEO_CODEC_MPEG1			0x00000008
#घोषणा HFI_VIDEO_CODEC_MPEG2			0x00000010
#घोषणा HFI_VIDEO_CODEC_MPEG4			0x00000020
#घोषणा HFI_VIDEO_CODEC_DIVX_311		0x00000040
#घोषणा HFI_VIDEO_CODEC_DIVX			0x00000080
#घोषणा HFI_VIDEO_CODEC_VC1			0x00000100
#घोषणा HFI_VIDEO_CODEC_SPARK			0x00000200
#घोषणा HFI_VIDEO_CODEC_VP8			0x00001000
#घोषणा HFI_VIDEO_CODEC_HEVC			0x00002000
#घोषणा HFI_VIDEO_CODEC_VP9			0x00004000
#घोषणा HFI_VIDEO_CODEC_HEVC_HYBRID		0x80000000

#घोषणा HFI_H264_PROखाता_BASELINE		0x00000001
#घोषणा HFI_H264_PROखाता_MAIN			0x00000002
#घोषणा HFI_H264_PROखाता_HIGH			0x00000004
#घोषणा HFI_H264_PROखाता_STEREO_HIGH		0x00000008
#घोषणा HFI_H264_PROखाता_MULTIVIEW_HIGH		0x00000010
#घोषणा HFI_H264_PROखाता_CONSTRAINED_BASE	0x00000020
#घोषणा HFI_H264_PROखाता_CONSTRAINED_HIGH	0x00000040

#घोषणा HFI_H264_LEVEL_1			0x00000001
#घोषणा HFI_H264_LEVEL_1b			0x00000002
#घोषणा HFI_H264_LEVEL_11			0x00000004
#घोषणा HFI_H264_LEVEL_12			0x00000008
#घोषणा HFI_H264_LEVEL_13			0x00000010
#घोषणा HFI_H264_LEVEL_2			0x00000020
#घोषणा HFI_H264_LEVEL_21			0x00000040
#घोषणा HFI_H264_LEVEL_22			0x00000080
#घोषणा HFI_H264_LEVEL_3			0x00000100
#घोषणा HFI_H264_LEVEL_31			0x00000200
#घोषणा HFI_H264_LEVEL_32			0x00000400
#घोषणा HFI_H264_LEVEL_4			0x00000800
#घोषणा HFI_H264_LEVEL_41			0x00001000
#घोषणा HFI_H264_LEVEL_42			0x00002000
#घोषणा HFI_H264_LEVEL_5			0x00004000
#घोषणा HFI_H264_LEVEL_51			0x00008000
#घोषणा HFI_H264_LEVEL_52			0x00010000

#घोषणा HFI_H263_PROखाता_BASELINE		0x00000001

#घोषणा HFI_H263_LEVEL_10			0x00000001
#घोषणा HFI_H263_LEVEL_20			0x00000002
#घोषणा HFI_H263_LEVEL_30			0x00000004
#घोषणा HFI_H263_LEVEL_40			0x00000008
#घोषणा HFI_H263_LEVEL_45			0x00000010
#घोषणा HFI_H263_LEVEL_50			0x00000020
#घोषणा HFI_H263_LEVEL_60			0x00000040
#घोषणा HFI_H263_LEVEL_70			0x00000080

#घोषणा HFI_MPEG2_PROखाता_SIMPLE		0x00000001
#घोषणा HFI_MPEG2_PROखाता_MAIN			0x00000002
#घोषणा HFI_MPEG2_PROखाता_422			0x00000004
#घोषणा HFI_MPEG2_PROखाता_SNR			0x00000008
#घोषणा HFI_MPEG2_PROखाता_SPATIAL		0x00000010
#घोषणा HFI_MPEG2_PROखाता_HIGH			0x00000020

#घोषणा HFI_MPEG2_LEVEL_LL			0x00000001
#घोषणा HFI_MPEG2_LEVEL_ML			0x00000002
#घोषणा HFI_MPEG2_LEVEL_H14			0x00000004
#घोषणा HFI_MPEG2_LEVEL_HL			0x00000008

#घोषणा HFI_MPEG4_PROखाता_SIMPLE		0x00000001
#घोषणा HFI_MPEG4_PROखाता_ADVANCEDSIMPLE	0x00000002

#घोषणा HFI_MPEG4_LEVEL_0			0x00000001
#घोषणा HFI_MPEG4_LEVEL_0b			0x00000002
#घोषणा HFI_MPEG4_LEVEL_1			0x00000004
#घोषणा HFI_MPEG4_LEVEL_2			0x00000008
#घोषणा HFI_MPEG4_LEVEL_3			0x00000010
#घोषणा HFI_MPEG4_LEVEL_4			0x00000020
#घोषणा HFI_MPEG4_LEVEL_4a			0x00000040
#घोषणा HFI_MPEG4_LEVEL_5			0x00000080
#घोषणा HFI_MPEG4_LEVEL_6			0x00000100
#घोषणा HFI_MPEG4_LEVEL_7			0x00000200
#घोषणा HFI_MPEG4_LEVEL_8			0x00000400
#घोषणा HFI_MPEG4_LEVEL_9			0x00000800
#घोषणा HFI_MPEG4_LEVEL_3b			0x00001000

#घोषणा HFI_VC1_PROखाता_SIMPLE			0x00000001
#घोषणा HFI_VC1_PROखाता_MAIN			0x00000002
#घोषणा HFI_VC1_PROखाता_ADVANCED		0x00000004

#घोषणा HFI_VC1_LEVEL_LOW			0x00000001
#घोषणा HFI_VC1_LEVEL_MEDIUM			0x00000002
#घोषणा HFI_VC1_LEVEL_HIGH			0x00000004
#घोषणा HFI_VC1_LEVEL_0				0x00000008
#घोषणा HFI_VC1_LEVEL_1				0x00000010
#घोषणा HFI_VC1_LEVEL_2				0x00000020
#घोषणा HFI_VC1_LEVEL_3				0x00000040
#घोषणा HFI_VC1_LEVEL_4				0x00000080

#घोषणा HFI_VPX_PROखाता_SIMPLE			0x00000001
#घोषणा HFI_VPX_PROखाता_ADVANCED		0x00000002
#घोषणा HFI_VPX_PROखाता_VERSION_0		0x00000004
#घोषणा HFI_VPX_PROखाता_VERSION_1		0x00000008
#घोषणा HFI_VPX_PROखाता_VERSION_2		0x00000010
#घोषणा HFI_VPX_PROखाता_VERSION_3		0x00000020

#घोषणा HFI_DIVX_FORMAT_4			0x1
#घोषणा HFI_DIVX_FORMAT_5			0x2
#घोषणा HFI_DIVX_FORMAT_6			0x3

#घोषणा HFI_DIVX_PROखाता_QMOBILE		0x00000001
#घोषणा HFI_DIVX_PROखाता_MOBILE			0x00000002
#घोषणा HFI_DIVX_PROखाता_MT			0x00000004
#घोषणा HFI_DIVX_PROखाता_HT			0x00000008
#घोषणा HFI_DIVX_PROखाता_HD			0x00000010

#घोषणा HFI_HEVC_PROखाता_MAIN			0x00000001
#घोषणा HFI_HEVC_PROखाता_MAIN10			0x00000002
#घोषणा HFI_HEVC_PROखाता_MAIN_STILL_PIC		0x00000004

#घोषणा HFI_HEVC_LEVEL_1			0x00000001
#घोषणा HFI_HEVC_LEVEL_2			0x00000002
#घोषणा HFI_HEVC_LEVEL_21			0x00000004
#घोषणा HFI_HEVC_LEVEL_3			0x00000008
#घोषणा HFI_HEVC_LEVEL_31			0x00000010
#घोषणा HFI_HEVC_LEVEL_4			0x00000020
#घोषणा HFI_HEVC_LEVEL_41			0x00000040
#घोषणा HFI_HEVC_LEVEL_5			0x00000080
#घोषणा HFI_HEVC_LEVEL_51			0x00000100
#घोषणा HFI_HEVC_LEVEL_52			0x00000200
#घोषणा HFI_HEVC_LEVEL_6			0x00000400
#घोषणा HFI_HEVC_LEVEL_61			0x00000800
#घोषणा HFI_HEVC_LEVEL_62			0x00001000

#घोषणा HFI_HEVC_TIER_MAIN			0x1
#घोषणा HFI_HEVC_TIER_HIGH0			0x2

#घोषणा HFI_VPX_PROखाता_MAIN			0x00000001

#घोषणा HFI_VPX_LEVEL_VERSION_0			0x00000001
#घोषणा HFI_VPX_LEVEL_VERSION_1			0x00000002
#घोषणा HFI_VPX_LEVEL_VERSION_2			0x00000004
#घोषणा HFI_VPX_LEVEL_VERSION_3			0x00000008

/* VP9 Profile 0, 8-bit */
#घोषणा HFI_VP9_PROखाता_P0			0x00000001
/* VP9 Profile 2, 10-bit */
#घोषणा HFI_VP9_PROखाता_P2_10B			0x00000004

#घोषणा HFI_VP9_LEVEL_1				0x00000001
#घोषणा HFI_VP9_LEVEL_11			0x00000002
#घोषणा HFI_VP9_LEVEL_2				0x00000004
#घोषणा HFI_VP9_LEVEL_21			0x00000008
#घोषणा HFI_VP9_LEVEL_3				0x00000010
#घोषणा HFI_VP9_LEVEL_31			0x00000020
#घोषणा HFI_VP9_LEVEL_4				0x00000040
#घोषणा HFI_VP9_LEVEL_41			0x00000080
#घोषणा HFI_VP9_LEVEL_5				0x00000100
#घोषणा HFI_VP9_LEVEL_51			0x00000200
#घोषणा HFI_VP9_LEVEL_6				0x00000400
#घोषणा HFI_VP9_LEVEL_61			0x00000800

#घोषणा HFI_BUFFER_INPUT			0x1
#घोषणा HFI_BUFFER_OUTPUT			0x2
#घोषणा HFI_BUFFER_OUTPUT2			0x3
#घोषणा HFI_BUFFER_INTERNAL_PERSIST		0x4
#घोषणा HFI_BUFFER_INTERNAL_PERSIST_1		0x5
#घोषणा HFI_BUFFER_INTERNAL_SCRATCH(ver)	\
	(((ver) == HFI_VERSION_4XX ||		\
	(ver) == HFI_VERSION_6XX) ? 0x6 : 0x1000001)
#घोषणा HFI_BUFFER_INTERNAL_SCRATCH_1(ver)	\
	(((ver) == HFI_VERSION_4XX ||		\
	(ver) == HFI_VERSION_6XX) ? 0x7 : 0x1000005)
#घोषणा HFI_BUFFER_INTERNAL_SCRATCH_2(ver)	\
	(((ver) == HFI_VERSION_4XX ||		\
	(ver) == HFI_VERSION_6XX) ? 0x8 : 0x1000006)
#घोषणा HFI_BUFFER_EXTRADATA_INPUT(ver)		\
	(((ver) == HFI_VERSION_4XX) ? 0xc : 0x1000002)
#घोषणा HFI_BUFFER_EXTRADATA_OUTPUT(ver)	\
	(((ver) == HFI_VERSION_4XX) ? 0xa : 0x1000003)
#घोषणा HFI_BUFFER_EXTRADATA_OUTPUT2(ver)	\
	(((ver) == HFI_VERSION_4XX) ? 0xb : 0x1000004)
#घोषणा HFI_BUFFER_TYPE_MAX			11

#घोषणा HFI_BUFFER_MODE_STATIC			0x1000001
#घोषणा HFI_BUFFER_MODE_RING			0x1000002
#घोषणा HFI_BUFFER_MODE_DYNAMIC			0x1000003

#घोषणा HFI_VENC_PERFMODE_MAX_QUALITY		0x1
#घोषणा HFI_VENC_PERFMODE_POWER_SAVE		0x2

/*
 * HFI_PROPERTY_SYS_COMMON_START
 * HFI_DOMAIN_BASE_COMMON + HFI_ARCH_COMMON_OFFSET + 0x0000
 */
#घोषणा HFI_PROPERTY_SYS_DEBUG_CONFIG				0x1
#घोषणा HFI_PROPERTY_SYS_RESOURCE_OCMEM_REQUIREMENT_INFO	0x2
#घोषणा HFI_PROPERTY_SYS_CONFIG_VCODEC_CLKFREQ			0x3
#घोषणा HFI_PROPERTY_SYS_IDLE_INDICATOR				0x4
#घोषणा HFI_PROPERTY_SYS_CODEC_POWER_PLANE_CTRL			0x5
#घोषणा HFI_PROPERTY_SYS_IMAGE_VERSION				0x6
#घोषणा HFI_PROPERTY_SYS_CONFIG_COVERAGE			0x7

/*
 * HFI_PROPERTY_PARAM_COMMON_START
 * HFI_DOMAIN_BASE_COMMON + HFI_ARCH_COMMON_OFFSET + 0x1000
 */
#घोषणा HFI_PROPERTY_PARAM_FRAME_SIZE				0x1001
#घोषणा HFI_PROPERTY_PARAM_UNCOMPRESSED_PLANE_ACTUAL_INFO	0x1002
#घोषणा HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SELECT		0x1003
#घोषणा HFI_PROPERTY_PARAM_UNCOMPRESSED_FORMAT_SUPPORTED	0x1004
#घोषणा HFI_PROPERTY_PARAM_PROखाता_LEVEL_CURRENT		0x1005
#घोषणा HFI_PROPERTY_PARAM_PROखाता_LEVEL_SUPPORTED		0x1006
#घोषणा HFI_PROPERTY_PARAM_CAPABILITY_SUPPORTED			0x1007
#घोषणा HFI_PROPERTY_PARAM_PROPERTIES_SUPPORTED			0x1008
#घोषणा HFI_PROPERTY_PARAM_CODEC_SUPPORTED			0x1009
#घोषणा HFI_PROPERTY_PARAM_NAL_STREAM_FORMAT_SUPPORTED		0x100a
#घोषणा HFI_PROPERTY_PARAM_NAL_STREAM_FORMAT_SELECT		0x100b
#घोषणा HFI_PROPERTY_PARAM_MULTI_VIEW_FORMAT			0x100c
#घोषणा HFI_PROPERTY_PARAM_MAX_SEQUENCE_HEADER_SIZE		0x100d
#घोषणा HFI_PROPERTY_PARAM_CODEC_MASK_SUPPORTED			0x100e
#घोषणा HFI_PROPERTY_PARAM_MVC_BUFFER_LAYOUT			0x100f
#घोषणा HFI_PROPERTY_PARAM_MAX_SESSIONS_SUPPORTED		0x1010
#घोषणा HFI_PROPERTY_PARAM_WORK_MODE				0x1015

/*
 * HFI_PROPERTY_CONFIG_COMMON_START
 * HFI_DOMAIN_BASE_COMMON + HFI_ARCH_COMMON_OFFSET + 0x2000
 */
#घोषणा HFI_PROPERTY_CONFIG_FRAME_RATE				0x2001
#घोषणा HFI_PROPERTY_CONFIG_VIDEOCORES_USAGE			0x2002

/*
 * HFI_PROPERTY_PARAM_VDEC_COMMON_START
 * HFI_DOMAIN_BASE_VDEC + HFI_ARCH_COMMON_OFFSET + 0x3000
 */
#घोषणा HFI_PROPERTY_PARAM_VDEC_MULTI_STREAM			0x1003001
#घोषणा HFI_PROPERTY_PARAM_VDEC_CONCEAL_COLOR			0x1003002
#घोषणा HFI_PROPERTY_PARAM_VDEC_NONCP_OUTPUT2			0x1003003
#घोषणा HFI_PROPERTY_PARAM_VDEC_PIXEL_BITDEPTH			0x1003007
#घोषणा HFI_PROPERTY_PARAM_VDEC_PIC_STRUCT			0x1003009
#घोषणा HFI_PROPERTY_PARAM_VDEC_COLOUR_SPACE			0x100300a

/*
 * HFI_PROPERTY_CONFIG_VDEC_COMMON_START
 * HFI_DOMAIN_BASE_VDEC + HFI_ARCH_COMMON_OFFSET + 0x4000
 */

/*
 * HFI_PROPERTY_PARAM_VENC_COMMON_START
 * HFI_DOMAIN_BASE_VENC + HFI_ARCH_COMMON_OFFSET + 0x5000
 */
#घोषणा HFI_PROPERTY_PARAM_VENC_SLICE_DELIVERY_MODE		0x2005001
#घोषणा HFI_PROPERTY_PARAM_VENC_H264_ENTROPY_CONTROL		0x2005002
#घोषणा HFI_PROPERTY_PARAM_VENC_H264_DEBLOCK_CONTROL		0x2005003
#घोषणा HFI_PROPERTY_PARAM_VENC_RATE_CONTROL			0x2005004
#घोषणा HFI_PROPERTY_PARAM_VENC_H264_PICORDER_CNT_TYPE		0x2005005
#घोषणा HFI_PROPERTY_PARAM_VENC_SESSION_QP			0x2005006
#घोषणा HFI_PROPERTY_PARAM_VENC_MPEG4_AC_PREDICTION		0x2005007
#घोषणा HFI_PROPERTY_PARAM_VENC_SESSION_QP_RANGE		0x2005008
#घोषणा HFI_PROPERTY_PARAM_VENC_MPEG4_TIME_RESOLUTION		0x2005009
#घोषणा HFI_PROPERTY_PARAM_VENC_MPEG4_SHORT_HEADER		0x200500a
#घोषणा HFI_PROPERTY_PARAM_VENC_MPEG4_HEADER_EXTENSION		0x200500b
#घोषणा HFI_PROPERTY_PARAM_VENC_OPEN_GOP			0x200500c
#घोषणा HFI_PROPERTY_PARAM_VENC_INTRA_REFRESH			0x200500d
#घोषणा HFI_PROPERTY_PARAM_VENC_MULTI_SLICE_CONTROL		0x200500e
#घोषणा HFI_PROPERTY_PARAM_VENC_VBV_HRD_BUF_SIZE		0x200500f
#घोषणा HFI_PROPERTY_PARAM_VENC_QUALITY_VS_SPEED		0x2005010
#घोषणा HFI_PROPERTY_PARAM_VENC_ADVANCED			0x2005012
#घोषणा HFI_PROPERTY_PARAM_VENC_H264_SPS_ID			0x2005014
#घोषणा HFI_PROPERTY_PARAM_VENC_H264_PPS_ID			0x2005015
#घोषणा HFI_PROPERTY_PARAM_VENC_H264_GENERATE_AUDNAL		0x2005016
#घोषणा HFI_PROPERTY_PARAM_VENC_ASPECT_RATIO			0x2005017
#घोषणा HFI_PROPERTY_PARAM_VENC_NUMREF				0x2005018
#घोषणा HFI_PROPERTY_PARAM_VENC_MULTIREF_P			0x2005019
#घोषणा HFI_PROPERTY_PARAM_VENC_H264_NAL_SVC_EXT		0x200501b
#घोषणा HFI_PROPERTY_PARAM_VENC_LTRMODE				0x200501c
#घोषणा HFI_PROPERTY_PARAM_VENC_VIDEO_FULL_RANGE		0x200501d
#घोषणा HFI_PROPERTY_PARAM_VENC_H264_VUI_TIMING_INFO		0x200501e
#घोषणा HFI_PROPERTY_PARAM_VENC_VC1_PERF_CFG			0x200501f
#घोषणा HFI_PROPERTY_PARAM_VENC_MAX_NUM_B_FRAMES		0x2005020
#घोषणा HFI_PROPERTY_PARAM_VENC_H264_VUI_BITSTREAM_RESTRC	0x2005021
#घोषणा HFI_PROPERTY_PARAM_VENC_PRESERVE_TEXT_QUALITY		0x2005023
#घोषणा HFI_PROPERTY_PARAM_VENC_HIER_P_MAX_NUM_ENH_LAYER	0x2005026
#घोषणा HFI_PROPERTY_PARAM_VENC_DISABLE_RC_TIMESTAMP		0x2005027
#घोषणा HFI_PROPERTY_PARAM_VENC_INITIAL_QP			0x2005028
#घोषणा HFI_PROPERTY_PARAM_VENC_VPX_ERROR_RESILIENCE_MODE	0x2005029
#घोषणा HFI_PROPERTY_PARAM_VENC_HIER_B_MAX_NUM_ENH_LAYER	0x200502c
#घोषणा HFI_PROPERTY_PARAM_VENC_HIER_P_HYBRID_MODE		0x200502f
#घोषणा HFI_PROPERTY_PARAM_VENC_HDR10_PQ_SEI			0x2005036

/*
 * HFI_PROPERTY_CONFIG_VENC_COMMON_START
 * HFI_DOMAIN_BASE_VENC + HFI_ARCH_COMMON_OFFSET + 0x6000
 */
#घोषणा HFI_PROPERTY_CONFIG_VENC_TARGET_BITRATE			0x2006001
#घोषणा HFI_PROPERTY_CONFIG_VENC_IDR_PERIOD			0x2006002
#घोषणा HFI_PROPERTY_CONFIG_VENC_INTRA_PERIOD			0x2006003
#घोषणा HFI_PROPERTY_CONFIG_VENC_REQUEST_SYNC_FRAME		0x2006004
#घोषणा HFI_PROPERTY_CONFIG_VENC_SLICE_SIZE			0x2006005
#घोषणा HFI_PROPERTY_CONFIG_VENC_MAX_BITRATE			0x2006007
#घोषणा HFI_PROPERTY_CONFIG_VENC_SYNC_FRAME_SEQUENCE_HEADER	0x2006008
#घोषणा HFI_PROPERTY_CONFIG_VENC_MARKLTRFRAME			0x2006009
#घोषणा HFI_PROPERTY_CONFIG_VENC_USELTRFRAME			0x200600a
#घोषणा HFI_PROPERTY_CONFIG_VENC_HIER_P_ENH_LAYER		0x200600b
#घोषणा HFI_PROPERTY_CONFIG_VENC_LTRPERIOD			0x200600c
#घोषणा HFI_PROPERTY_CONFIG_VENC_PERF_MODE			0x200600e
#घोषणा HFI_PROPERTY_CONFIG_HEIC_FRAME_QUALITY			0x2006014

/*
 * HFI_PROPERTY_PARAM_VPE_COMMON_START
 * HFI_DOMAIN_BASE_VPE + HFI_ARCH_COMMON_OFFSET + 0x7000
 */

/*
 * HFI_PROPERTY_CONFIG_VPE_COMMON_START
 * HFI_DOMAIN_BASE_VPE + HFI_ARCH_COMMON_OFFSET + 0x8000
 */
#घोषणा HFI_PROPERTY_CONFIG_VPE_DEINTERLACE			0x3008001
#घोषणा HFI_PROPERTY_CONFIG_VPE_OPERATIONS			0x3008002

क्रमागत hfi_version अणु
	HFI_VERSION_1XX,
	HFI_VERSION_3XX,
	HFI_VERSION_4XX,
	HFI_VERSION_6XX,
पूर्ण;

काष्ठा hfi_buffer_info अणु
	u32 buffer_addr;
	u32 extradata_addr;
पूर्ण;

काष्ठा hfi_bitrate अणु
	u32 bitrate;
	u32 layer_id;
पूर्ण;

#घोषणा HFI_CAPABILITY_FRAME_WIDTH			0x01
#घोषणा HFI_CAPABILITY_FRAME_HEIGHT			0x02
#घोषणा HFI_CAPABILITY_MBS_PER_FRAME			0x03
#घोषणा HFI_CAPABILITY_MBS_PER_SECOND			0x04
#घोषणा HFI_CAPABILITY_FRAMERATE			0x05
#घोषणा HFI_CAPABILITY_SCALE_X				0x06
#घोषणा HFI_CAPABILITY_SCALE_Y				0x07
#घोषणा HFI_CAPABILITY_BITRATE				0x08
#घोषणा HFI_CAPABILITY_BFRAME				0x09
#घोषणा HFI_CAPABILITY_PEAKBITRATE			0x0a
#घोषणा HFI_CAPABILITY_HIER_P_NUM_ENH_LAYERS		0x10
#घोषणा HFI_CAPABILITY_ENC_LTR_COUNT			0x11
#घोषणा HFI_CAPABILITY_CP_OUTPUT2_THRESH		0x12
#घोषणा HFI_CAPABILITY_HIER_B_NUM_ENH_LAYERS		0x13
#घोषणा HFI_CAPABILITY_LCU_SIZE				0x14
#घोषणा HFI_CAPABILITY_HIER_P_HYBRID_NUM_ENH_LAYERS	0x15
#घोषणा HFI_CAPABILITY_MBS_PER_SECOND_POWERSAVE		0x16
#घोषणा HFI_CAPABILITY_I_FRAME_QP			0x20
#घोषणा HFI_CAPABILITY_P_FRAME_QP			0x21
#घोषणा HFI_CAPABILITY_B_FRAME_QP			0x22
#घोषणा HFI_CAPABILITY_RATE_CONTROL_MODES		0x23
#घोषणा HFI_CAPABILITY_BLUR_WIDTH			0x24
#घोषणा HFI_CAPABILITY_BLUR_HEIGHT			0x25
#घोषणा HFI_CAPABILITY_SLICE_BYTE			0x27
#घोषणा HFI_CAPABILITY_SLICE_MB				0x28
#घोषणा HFI_CAPABILITY_MAX_VIDEOCORES			0x2b
#घोषणा HFI_CAPABILITY_MAX_WORKMODES			0x2c
#घोषणा HFI_CAPABILITY_ROTATION				0x2f
#घोषणा HFI_CAPABILITY_COLOR_SPACE_CONVERSION		0x30

काष्ठा hfi_capability अणु
	u32 capability_type;
	u32 min;
	u32 max;
	u32 step_size;
पूर्ण;

काष्ठा hfi_capabilities अणु
	u32 num_capabilities;
	काष्ठा hfi_capability data[];
पूर्ण;

#घोषणा HFI_DEBUG_MSG_LOW	0x01
#घोषणा HFI_DEBUG_MSG_MEDIUM	0x02
#घोषणा HFI_DEBUG_MSG_HIGH	0x04
#घोषणा HFI_DEBUG_MSG_ERROR	0x08
#घोषणा HFI_DEBUG_MSG_FATAL	0x10
#घोषणा HFI_DEBUG_MSG_PERF	0x20

#घोषणा HFI_DEBUG_MODE_QUEUE	0x01
#घोषणा HFI_DEBUG_MODE_QDSS	0x02

काष्ठा hfi_debug_config अणु
	u32 config;
	u32 mode;
पूर्ण;

काष्ठा hfi_enable अणु
	u32 enable;
पूर्ण;

#घोषणा HFI_H264_DB_MODE_DISABLE		0x1
#घोषणा HFI_H264_DB_MODE_SKIP_SLICE_BOUNDARY	0x2
#घोषणा HFI_H264_DB_MODE_ALL_BOUNDARY		0x3

काष्ठा hfi_h264_db_control अणु
	u32 mode;
	s32 slice_alpha_offset;
	s32 slice_beta_offset;
पूर्ण;

#घोषणा HFI_H264_ENTROPY_CAVLC			0x1
#घोषणा HFI_H264_ENTROPY_CABAC			0x2

#घोषणा HFI_H264_CABAC_MODEL_0			0x1
#घोषणा HFI_H264_CABAC_MODEL_1			0x2
#घोषणा HFI_H264_CABAC_MODEL_2			0x3

काष्ठा hfi_h264_entropy_control अणु
	u32 entropy_mode;
	u32 cabac_model;
पूर्ण;

काष्ठा hfi_framerate अणु
	u32 buffer_type;
	u32 framerate;
पूर्ण;

#घोषणा HFI_INTRA_REFRESH_NONE			0x1
#घोषणा HFI_INTRA_REFRESH_CYCLIC		0x2
#घोषणा HFI_INTRA_REFRESH_ADAPTIVE		0x3
#घोषणा HFI_INTRA_REFRESH_CYCLIC_ADAPTIVE	0x4
#घोषणा HFI_INTRA_REFRESH_RANDOM		0x5

काष्ठा hfi_पूर्णांकra_refresh अणु
	u32 mode;
	u32 air_mbs;
	u32 air_ref;
	u32 cir_mbs;
पूर्ण;

काष्ठा hfi_पूर्णांकra_refresh_3x अणु
	u32 mode;
	u32 mbs;
पूर्ण;

काष्ठा hfi_idr_period अणु
	u32 idr_period;
पूर्ण;

काष्ठा hfi_operations_type अणु
	u32 rotation;
	u32 flip;
पूर्ण;

काष्ठा hfi_max_num_b_frames अणु
	u32 max_num_b_frames;
पूर्ण;

काष्ठा hfi_vc1e_perf_cfg_type अणु
	u32 search_range_x_subsampled[3];
	u32 search_range_y_subsampled[3];
पूर्ण;

/*
 * 0 - 7bit -> Luma (def: 16)
 * 8 - 15bit -> Chroma (def: 128)
 * क्रमmat is valid up to v4
 */
काष्ठा hfi_conceal_color अणु
	u32 conceal_color;
पूर्ण;

काष्ठा hfi_conceal_color_v4 अणु
	u32 conceal_color_8bit;
	u32 conceal_color_10bit;
पूर्ण;

काष्ठा hfi_पूर्णांकra_period अणु
	u32 pframes;
	u32 bframes;
पूर्ण;

काष्ठा hfi_mpeg4_header_extension अणु
	u32 header_extension;
पूर्ण;

काष्ठा hfi_mpeg4_समय_resolution अणु
	u32 समय_increment_resolution;
पूर्ण;

काष्ठा hfi_multi_stream अणु
	u32 buffer_type;
	u32 enable;
	u32 width;
	u32 height;
पूर्ण;

काष्ठा hfi_multi_stream_3x अणु
	u32 buffer_type;
	u32 enable;
पूर्ण;

काष्ठा hfi_multi_view_क्रमmat अणु
	u32 views;
	u32 view_order[1];
पूर्ण;

#घोषणा HFI_MULTI_SLICE_OFF			0x1
#घोषणा HFI_MULTI_SLICE_BY_MB_COUNT		0x2
#घोषणा HFI_MULTI_SLICE_BY_BYTE_COUNT		0x3
#घोषणा HFI_MULTI_SLICE_GOB			0x4

काष्ठा hfi_multi_slice_control अणु
	u32 multi_slice;
	u32 slice_size;
पूर्ण;

#घोषणा HFI_NAL_FORMAT_STARTCODES		0x01
#घोषणा HFI_NAL_FORMAT_ONE_NAL_PER_BUFFER	0x02
#घोषणा HFI_NAL_FORMAT_ONE_BYTE_LENGTH		0x04
#घोषणा HFI_NAL_FORMAT_TWO_BYTE_LENGTH		0x08
#घोषणा HFI_NAL_FORMAT_FOUR_BYTE_LENGTH		0x10

काष्ठा hfi_nal_stream_क्रमmat अणु
	u32 क्रमmat;
पूर्ण;

काष्ठा hfi_nal_stream_क्रमmat_select अणु
	u32 क्रमmat;
पूर्ण;

#घोषणा HFI_PICTURE_TYPE_I			0x01
#घोषणा HFI_PICTURE_TYPE_P			0x02
#घोषणा HFI_PICTURE_TYPE_B			0x04
#घोषणा HFI_PICTURE_TYPE_IDR			0x08

काष्ठा hfi_profile_level अणु
	u32 profile;
	u32 level;
पूर्ण;

#घोषणा HFI_MAX_PROखाता_COUNT			16

काष्ठा hfi_profile_level_supported अणु
	u32 profile_count;
	काष्ठा hfi_profile_level profile_level[];
पूर्ण;

काष्ठा hfi_quality_vs_speed अणु
	u32 quality_vs_speed;
पूर्ण;

काष्ठा hfi_heic_frame_quality अणु
	u32 frame_quality;
	u32 reserved[3];
पूर्ण;

काष्ठा hfi_quantization अणु
	u32 qp_i;
	u32 qp_p;
	u32 qp_b;
	u32 layer_id;
पूर्ण;

काष्ठा hfi_initial_quantization अणु
	u32 qp_i;
	u32 qp_p;
	u32 qp_b;
	u32 init_qp_enable;
पूर्ण;

काष्ठा hfi_quantization_range अणु
	u32 min_qp;
	u32 max_qp;
	u32 layer_id;
पूर्ण;

#घोषणा HFI_LTR_MODE_DISABLE	0x0
#घोषणा HFI_LTR_MODE_MANUAL	0x1
#घोषणा HFI_LTR_MODE_PERIODIC	0x2

काष्ठा hfi_ltr_mode अणु
	u32 ltr_mode;
	u32 ltr_count;
	u32 trust_mode;
पूर्ण;

काष्ठा hfi_ltr_use अणु
	u32 ref_ltr;
	u32 use_स्थिरrnt;
	u32 frames;
पूर्ण;

काष्ठा hfi_ltr_mark अणु
	u32 mark_frame;
पूर्ण;

काष्ठा hfi_mastering_display_colour_sei_payload अणु
	u32 display_primaries_x[3];
	u32 display_primaries_y[3];
	u32 white_poपूर्णांक_x;
	u32 white_poपूर्णांक_y;
	u32 max_display_mastering_luminance;
	u32 min_display_mastering_luminance;
पूर्ण;

काष्ठा hfi_content_light_level_sei_payload अणु
	u32 max_content_light;
	u32 max_pic_average_light;
पूर्ण;

काष्ठा hfi_hdr10_pq_sei अणु
	काष्ठा hfi_mastering_display_colour_sei_payload mastering;
	काष्ठा hfi_content_light_level_sei_payload cll;
पूर्ण;

काष्ठा hfi_framesize अणु
	u32 buffer_type;
	u32 width;
	u32 height;
पूर्ण;

#घोषणा VIDC_CORE_ID_DEFAULT	0
#घोषणा VIDC_CORE_ID_1		1
#घोषणा VIDC_CORE_ID_2		2
#घोषणा VIDC_CORE_ID_3		3

काष्ठा hfi_videocores_usage_type अणु
	u32 video_core_enable_mask;
पूर्ण;

#घोषणा VIDC_WORK_MODE_1	1
#घोषणा VIDC_WORK_MODE_2	2

काष्ठा hfi_video_work_mode अणु
	u32 video_work_mode;
पूर्ण;

काष्ठा hfi_h264_vui_timing_info अणु
	u32 enable;
	u32 fixed_framerate;
	u32 समय_scale;
पूर्ण;

#घोषणा VIDC_BITDEPTH_8		0x00000
#घोषणा VIDC_BITDEPTH_10	0x20002

काष्ठा hfi_bit_depth अणु
	u32 buffer_type;
	u32 bit_depth;
पूर्ण;

काष्ठा hfi_picture_type अणु
	u32 is_sync_frame;
	u32 picture_type;
पूर्ण;

काष्ठा hfi_pic_काष्ठा अणु
	u32 progressive_only;
पूर्ण;

काष्ठा hfi_colour_space अणु
	u32 colour_space;
पूर्ण;

काष्ठा hfi_extradata_input_crop अणु
	u32 size;
	u32 version;
	u32 port_index;
	u32 left;
	u32 top;
	u32 width;
	u32 height;
पूर्ण;

#घोषणा HFI_COLOR_FORMAT_MONOCHROME		0x01
#घोषणा HFI_COLOR_FORMAT_NV12			0x02
#घोषणा HFI_COLOR_FORMAT_NV21			0x03
#घोषणा HFI_COLOR_FORMAT_NV12_4x4TILE		0x04
#घोषणा HFI_COLOR_FORMAT_NV21_4x4TILE		0x05
#घोषणा HFI_COLOR_FORMAT_YUYV			0x06
#घोषणा HFI_COLOR_FORMAT_YVYU			0x07
#घोषणा HFI_COLOR_FORMAT_UYVY			0x08
#घोषणा HFI_COLOR_FORMAT_VYUY			0x09
#घोषणा HFI_COLOR_FORMAT_RGB565			0x0a
#घोषणा HFI_COLOR_FORMAT_BGR565			0x0b
#घोषणा HFI_COLOR_FORMAT_RGB888			0x0c
#घोषणा HFI_COLOR_FORMAT_BGR888			0x0d
#घोषणा HFI_COLOR_FORMAT_YUV444			0x0e
#घोषणा HFI_COLOR_FORMAT_RGBA8888		0x10

#घोषणा HFI_COLOR_FORMAT_UBWC_BASE		0x8000
#घोषणा HFI_COLOR_FORMAT_10_BIT_BASE		0x4000

#घोषणा HFI_COLOR_FORMAT_YUV420_TP10		0x4002
#घोषणा HFI_COLOR_FORMAT_P010			0x4003
#घोषणा HFI_COLOR_FORMAT_NV12_UBWC		0x8002
#घोषणा HFI_COLOR_FORMAT_YUV420_TP10_UBWC	0xc002
#घोषणा HFI_COLOR_FORMAT_P010_UBWC		0xc003
#घोषणा HFI_COLOR_FORMAT_RGBA8888_UBWC		0x8010

काष्ठा hfi_uncompressed_क्रमmat_select अणु
	u32 buffer_type;
	u32 क्रमmat;
पूर्ण;

काष्ठा hfi_uncompressed_plane_स्थिरraपूर्णांकs अणु
	u32 stride_multiples;
	u32 max_stride;
	u32 min_plane_buffer_height_multiple;
	u32 buffer_alignment;
पूर्ण;

काष्ठा hfi_uncompressed_plane_info अणु
	u32 क्रमmat;
	u32 num_planes;
	काष्ठा hfi_uncompressed_plane_स्थिरraपूर्णांकs plane_स्थिरraपूर्णांकs[1];
पूर्ण;

काष्ठा hfi_uncompressed_क्रमmat_supported अणु
	u32 buffer_type;
	u32 क्रमmat_entries;
	काष्ठा hfi_uncompressed_plane_info plane_info[1];
पूर्ण;

काष्ठा hfi_uncompressed_plane_actual अणु
	पूर्णांक actual_stride;
	u32 actual_plane_buffer_height;
पूर्ण;

काष्ठा hfi_uncompressed_plane_actual_info अणु
	u32 buffer_type;
	u32 num_planes;
	काष्ठा hfi_uncompressed_plane_actual plane_क्रमmat[2];
पूर्ण;

काष्ठा hfi_uncompressed_plane_actual_स्थिरraपूर्णांकs_info अणु
	u32 buffer_type;
	u32 num_planes;
	काष्ठा hfi_uncompressed_plane_स्थिरraपूर्णांकs plane_क्रमmat[2];
पूर्ण;

काष्ठा hfi_codec_supported अणु
	u32 dec_codecs;
	u32 enc_codecs;
पूर्ण;

काष्ठा hfi_properties_supported अणु
	u32 num_properties;
	u32 properties[1];
पूर्ण;

काष्ठा hfi_max_sessions_supported अणु
	u32 max_sessions;
पूर्ण;

#घोषणा HFI_MAX_MATRIX_COEFFS	9
#घोषणा HFI_MAX_BIAS_COEFFS	3
#घोषणा HFI_MAX_LIMIT_COEFFS	6

काष्ठा hfi_vpe_color_space_conversion अणु
	u32 csc_matrix[HFI_MAX_MATRIX_COEFFS];
	u32 csc_bias[HFI_MAX_BIAS_COEFFS];
	u32 csc_limit[HFI_MAX_LIMIT_COEFFS];
पूर्ण;

#घोषणा HFI_ROTATE_NONE		0x1
#घोषणा HFI_ROTATE_90		0x2
#घोषणा HFI_ROTATE_180		0x3
#घोषणा HFI_ROTATE_270		0x4

#घोषणा HFI_FLIP_NONE		0x1
#घोषणा HFI_FLIP_HORIZONTAL	0x2
#घोषणा HFI_FLIP_VERTICAL	0x3

काष्ठा hfi_operations अणु
	u32 rotate;
	u32 flip;
पूर्ण;

#घोषणा HFI_RESOURCE_OCMEM	0x1

काष्ठा hfi_resource_ocmem अणु
	u32 size;
	u32 mem;
पूर्ण;

काष्ठा hfi_resource_ocmem_requirement अणु
	u32 session_करोमुख्य;
	u32 width;
	u32 height;
	u32 size;
पूर्ण;

काष्ठा hfi_resource_ocmem_requirement_info अणु
	u32 num_entries;
	काष्ठा hfi_resource_ocmem_requirement requirements[1];
पूर्ण;

काष्ठा hfi_property_sys_image_version_info_type अणु
	u32 string_size;
	u8  str_image_version[1];
पूर्ण;

काष्ठा hfi_codec_mask_supported अणु
	u32 codecs;
	u32 video_करोमुख्यs;
पूर्ण;

काष्ठा hfi_seq_header_info अणु
	u32 max_hader_len;
पूर्ण;

काष्ठा hfi_aspect_ratio अणु
	u32 aspect_width;
	u32 aspect_height;
पूर्ण;

#घोषणा HFI_MVC_BUFFER_LAYOUT_TOP_BOTTOM	0
#घोषणा HFI_MVC_BUFFER_LAYOUT_SIDEBYSIDE	1
#घोषणा HFI_MVC_BUFFER_LAYOUT_SEQ		2

काष्ठा hfi_mvc_buffer_layout_descp_type अणु
	u32 layout_type;
	u32 bright_view_first;
	u32 ngap;
पूर्ण;

काष्ठा hfi_scs_threshold अणु
	u32 threshold_value;
पूर्ण;

#घोषणा HFI_TEST_SSR_SW_ERR_FATAL	0x1
#घोषणा HFI_TEST_SSR_SW_DIV_BY_ZERO	0x2
#घोषणा HFI_TEST_SSR_HW_WDOG_IRQ	0x3

काष्ठा hfi_buffer_alloc_mode अणु
	u32 type;
	u32 mode;
पूर्ण;

काष्ठा hfi_index_extradata_config अणु
	u32 enable;
	u32 index_extra_data_id;
पूर्ण;

काष्ठा hfi_extradata_header अणु
	u32 size;
	u32 version;
	u32 port_index;
	u32 type;
	u32 data_size;
	u8 data[1];
पूर्ण;

काष्ठा hfi_batch_info अणु
	u32 input_batch_count;
	u32 output_batch_count;
पूर्ण;

काष्ठा hfi_buffer_count_actual अणु
	u32 type;
	u32 count_actual;
पूर्ण;

काष्ठा hfi_buffer_count_actual_4xx अणु
	u32 type;
	u32 count_actual;
	u32 count_min_host;
पूर्ण;

काष्ठा hfi_buffer_size_actual अणु
	u32 type;
	u32 size;
पूर्ण;

काष्ठा hfi_buffer_display_hold_count_actual अणु
	u32 type;
	u32 hold_count;
पूर्ण;

/* HFI 4XX reorder the fields, use these macros */
#घोषणा HFI_BUFREQ_HOLD_COUNT(bufreq, ver)	\
	((ver) == HFI_VERSION_4XX ? 0 : (bufreq)->hold_count)
#घोषणा HFI_BUFREQ_COUNT_MIN(bufreq, ver)	\
	((ver) == HFI_VERSION_4XX ? (bufreq)->hold_count : (bufreq)->count_min)
#घोषणा HFI_BUFREQ_COUNT_MIN_HOST(bufreq, ver)	\
	((ver) == HFI_VERSION_4XX ? (bufreq)->count_min : 0)

काष्ठा hfi_buffer_requirements अणु
	u32 type;
	u32 size;
	u32 region_size;
	u32 hold_count;
	u32 count_min;
	u32 count_actual;
	u32 contiguous;
	u32 alignment;
पूर्ण;

काष्ठा hfi_data_payload अणु
	u32 size;
	u8 data[1];
पूर्ण;

काष्ठा hfi_enable_picture अणु
	u32 picture_type;
पूर्ण;

काष्ठा hfi_display_picture_buffer_count अणु
	पूर्णांक enable;
	u32 count;
पूर्ण;

काष्ठा hfi_extra_data_header_config अणु
	u32 type;
	u32 buffer_type;
	u32 version;
	u32 port_index;
	u32 client_extra_data_id;
पूर्ण;

काष्ठा hfi_पूर्णांकerlace_क्रमmat_supported अणु
	u32 buffer_type;
	u32 क्रमmat;
पूर्ण;

काष्ठा hfi_buffer_alloc_mode_supported अणु
	u32 buffer_type;
	u32 num_entries;
	u32 data[1];
पूर्ण;

काष्ठा hfi_mb_error_map अणु
	u32 error_map_size;
	u8 error_map[1];
पूर्ण;

काष्ठा hfi_metadata_pass_through अणु
	पूर्णांक enable;
	u32 size;
पूर्ण;

काष्ठा hfi_multi_view_select अणु
	u32 view_index;
पूर्ण;

काष्ठा hfi_hybrid_hierp अणु
	u32 layers;
पूर्ण;

काष्ठा hfi_pkt_hdr अणु
	u32 size;
	u32 pkt_type;
पूर्ण;

काष्ठा hfi_session_hdr_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 session_id;
पूर्ण;

काष्ठा hfi_session_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
पूर्ण;

#पूर्ण_अगर
