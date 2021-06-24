<शैली गुरु>
/*
 * Copyright (C) 2012 Avionic Design GmbH
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित __LINUX_HDMI_H_
#घोषणा __LINUX_HDMI_H_

#समावेश <linux/types.h>
#समावेश <linux/device.h>

क्रमागत hdmi_packet_type अणु
	HDMI_PACKET_TYPE_शून्य = 0x00,
	HDMI_PACKET_TYPE_AUDIO_CLOCK_REGEN = 0x01,
	HDMI_PACKET_TYPE_AUDIO_SAMPLE = 0x02,
	HDMI_PACKET_TYPE_GENERAL_CONTROL = 0x03,
	HDMI_PACKET_TYPE_ACP = 0x04,
	HDMI_PACKET_TYPE_ISRC1 = 0x05,
	HDMI_PACKET_TYPE_ISRC2 = 0x06,
	HDMI_PACKET_TYPE_ONE_BIT_AUDIO_SAMPLE = 0x07,
	HDMI_PACKET_TYPE_DST_AUDIO = 0x08,
	HDMI_PACKET_TYPE_HBR_AUDIO_STREAM = 0x09,
	HDMI_PACKET_TYPE_GAMUT_METADATA = 0x0a,
	/* + क्रमागत hdmi_infoframe_type */
पूर्ण;

क्रमागत hdmi_infoframe_type अणु
	HDMI_INFOFRAME_TYPE_VENDOR = 0x81,
	HDMI_INFOFRAME_TYPE_AVI = 0x82,
	HDMI_INFOFRAME_TYPE_SPD = 0x83,
	HDMI_INFOFRAME_TYPE_AUDIO = 0x84,
	HDMI_INFOFRAME_TYPE_DRM = 0x87,
पूर्ण;

#घोषणा HDMI_IEEE_OUI 0x000c03
#घोषणा HDMI_FORUM_IEEE_OUI 0xc45dd8
#घोषणा HDMI_INFOFRAME_HEADER_SIZE  4
#घोषणा HDMI_AVI_INFOFRAME_SIZE    13
#घोषणा HDMI_SPD_INFOFRAME_SIZE    25
#घोषणा HDMI_AUDIO_INFOFRAME_SIZE  10
#घोषणा HDMI_DRM_INFOFRAME_SIZE    26
#घोषणा HDMI_VENDOR_INFOFRAME_SIZE  4

#घोषणा HDMI_INFOFRAME_SIZE(type)	\
	(HDMI_INFOFRAME_HEADER_SIZE + HDMI_ ## type ## _INFOFRAME_SIZE)

काष्ठा hdmi_any_infoframe अणु
	क्रमागत hdmi_infoframe_type type;
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर length;
पूर्ण;

क्रमागत hdmi_colorspace अणु
	HDMI_COLORSPACE_RGB,
	HDMI_COLORSPACE_YUV422,
	HDMI_COLORSPACE_YUV444,
	HDMI_COLORSPACE_YUV420,
	HDMI_COLORSPACE_RESERVED4,
	HDMI_COLORSPACE_RESERVED5,
	HDMI_COLORSPACE_RESERVED6,
	HDMI_COLORSPACE_IDO_DEFINED,
पूर्ण;

क्रमागत hdmi_scan_mode अणु
	HDMI_SCAN_MODE_NONE,
	HDMI_SCAN_MODE_OVERSCAN,
	HDMI_SCAN_MODE_UNDERSCAN,
	HDMI_SCAN_MODE_RESERVED,
पूर्ण;

क्रमागत hdmi_colorimetry अणु
	HDMI_COLORIMETRY_NONE,
	HDMI_COLORIMETRY_ITU_601,
	HDMI_COLORIMETRY_ITU_709,
	HDMI_COLORIMETRY_EXTENDED,
पूर्ण;

क्रमागत hdmi_picture_aspect अणु
	HDMI_PICTURE_ASPECT_NONE,
	HDMI_PICTURE_ASPECT_4_3,
	HDMI_PICTURE_ASPECT_16_9,
	HDMI_PICTURE_ASPECT_64_27,
	HDMI_PICTURE_ASPECT_256_135,
	HDMI_PICTURE_ASPECT_RESERVED,
पूर्ण;

क्रमागत hdmi_active_aspect अणु
	HDMI_ACTIVE_ASPECT_16_9_TOP = 2,
	HDMI_ACTIVE_ASPECT_14_9_TOP = 3,
	HDMI_ACTIVE_ASPECT_16_9_CENTER = 4,
	HDMI_ACTIVE_ASPECT_PICTURE = 8,
	HDMI_ACTIVE_ASPECT_4_3 = 9,
	HDMI_ACTIVE_ASPECT_16_9 = 10,
	HDMI_ACTIVE_ASPECT_14_9 = 11,
	HDMI_ACTIVE_ASPECT_4_3_SP_14_9 = 13,
	HDMI_ACTIVE_ASPECT_16_9_SP_14_9 = 14,
	HDMI_ACTIVE_ASPECT_16_9_SP_4_3 = 15,
पूर्ण;

क्रमागत hdmi_extended_colorimetry अणु
	HDMI_EXTENDED_COLORIMETRY_XV_YCC_601,
	HDMI_EXTENDED_COLORIMETRY_XV_YCC_709,
	HDMI_EXTENDED_COLORIMETRY_S_YCC_601,
	HDMI_EXTENDED_COLORIMETRY_OPYCC_601,
	HDMI_EXTENDED_COLORIMETRY_OPRGB,

	/* The following EC values are only defined in CEA-861-F. */
	HDMI_EXTENDED_COLORIMETRY_BT2020_CONST_LUM,
	HDMI_EXTENDED_COLORIMETRY_BT2020,
	HDMI_EXTENDED_COLORIMETRY_RESERVED,
पूर्ण;

क्रमागत hdmi_quantization_range अणु
	HDMI_QUANTIZATION_RANGE_DEFAULT,
	HDMI_QUANTIZATION_RANGE_LIMITED,
	HDMI_QUANTIZATION_RANGE_FULL,
	HDMI_QUANTIZATION_RANGE_RESERVED,
पूर्ण;

/* non-unअगरorm picture scaling */
क्रमागत hdmi_nups अणु
	HDMI_NUPS_UNKNOWN,
	HDMI_NUPS_HORIZONTAL,
	HDMI_NUPS_VERTICAL,
	HDMI_NUPS_BOTH,
पूर्ण;

क्रमागत hdmi_ycc_quantization_range अणु
	HDMI_YCC_QUANTIZATION_RANGE_LIMITED,
	HDMI_YCC_QUANTIZATION_RANGE_FULL,
पूर्ण;

क्रमागत hdmi_content_type अणु
	HDMI_CONTENT_TYPE_GRAPHICS,
	HDMI_CONTENT_TYPE_PHOTO,
	HDMI_CONTENT_TYPE_CINEMA,
	HDMI_CONTENT_TYPE_GAME,
पूर्ण;

क्रमागत hdmi_metadata_type अणु
	HDMI_STATIC_METADATA_TYPE1 = 0,
पूर्ण;

क्रमागत hdmi_eotf अणु
	HDMI_EOTF_TRADITIONAL_GAMMA_SDR,
	HDMI_EOTF_TRADITIONAL_GAMMA_HDR,
	HDMI_EOTF_SMPTE_ST2084,
	HDMI_EOTF_BT_2100_HLG,
पूर्ण;

काष्ठा hdmi_avi_infoframe अणु
	क्रमागत hdmi_infoframe_type type;
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर length;
	क्रमागत hdmi_colorspace colorspace;
	क्रमागत hdmi_scan_mode scan_mode;
	क्रमागत hdmi_colorimetry colorimetry;
	क्रमागत hdmi_picture_aspect picture_aspect;
	क्रमागत hdmi_active_aspect active_aspect;
	bool itc;
	क्रमागत hdmi_extended_colorimetry extended_colorimetry;
	क्रमागत hdmi_quantization_range quantization_range;
	क्रमागत hdmi_nups nups;
	अचिन्हित अक्षर video_code;
	क्रमागत hdmi_ycc_quantization_range ycc_quantization_range;
	क्रमागत hdmi_content_type content_type;
	अचिन्हित अक्षर pixel_repeat;
	अचिन्हित लघु top_bar;
	अचिन्हित लघु bottom_bar;
	अचिन्हित लघु left_bar;
	अचिन्हित लघु right_bar;
पूर्ण;

/* DRM Infoframe as per CTA 861.G spec */
काष्ठा hdmi_drm_infoframe अणु
	क्रमागत hdmi_infoframe_type type;
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर length;
	क्रमागत hdmi_eotf eotf;
	क्रमागत hdmi_metadata_type metadata_type;
	काष्ठा अणु
		u16 x, y;
	पूर्ण display_primaries[3];
	काष्ठा अणु
		u16 x, y;
	पूर्ण white_poपूर्णांक;
	u16 max_display_mastering_luminance;
	u16 min_display_mastering_luminance;
	u16 max_cll;
	u16 max_fall;
पूर्ण;

व्योम hdmi_avi_infoframe_init(काष्ठा hdmi_avi_infoframe *frame);
sमाप_प्रकार hdmi_avi_infoframe_pack(काष्ठा hdmi_avi_infoframe *frame, व्योम *buffer,
				माप_प्रकार size);
sमाप_प्रकार hdmi_avi_infoframe_pack_only(स्थिर काष्ठा hdmi_avi_infoframe *frame,
				     व्योम *buffer, माप_प्रकार size);
पूर्णांक hdmi_avi_infoframe_check(काष्ठा hdmi_avi_infoframe *frame);
पूर्णांक hdmi_drm_infoframe_init(काष्ठा hdmi_drm_infoframe *frame);
sमाप_प्रकार hdmi_drm_infoframe_pack(काष्ठा hdmi_drm_infoframe *frame, व्योम *buffer,
				माप_प्रकार size);
sमाप_प्रकार hdmi_drm_infoframe_pack_only(स्थिर काष्ठा hdmi_drm_infoframe *frame,
				     व्योम *buffer, माप_प्रकार size);
पूर्णांक hdmi_drm_infoframe_check(काष्ठा hdmi_drm_infoframe *frame);
पूर्णांक hdmi_drm_infoframe_unpack_only(काष्ठा hdmi_drm_infoframe *frame,
				   स्थिर व्योम *buffer, माप_प्रकार size);

क्रमागत hdmi_spd_sdi अणु
	HDMI_SPD_SDI_UNKNOWN,
	HDMI_SPD_SDI_DSTB,
	HDMI_SPD_SDI_DVDP,
	HDMI_SPD_SDI_DVHS,
	HDMI_SPD_SDI_HDDVR,
	HDMI_SPD_SDI_DVC,
	HDMI_SPD_SDI_DSC,
	HDMI_SPD_SDI_VCD,
	HDMI_SPD_SDI_GAME,
	HDMI_SPD_SDI_PC,
	HDMI_SPD_SDI_BD,
	HDMI_SPD_SDI_SACD,
	HDMI_SPD_SDI_HDDVD,
	HDMI_SPD_SDI_PMP,
पूर्ण;

काष्ठा hdmi_spd_infoframe अणु
	क्रमागत hdmi_infoframe_type type;
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर length;
	अक्षर venकरोr[8];
	अक्षर product[16];
	क्रमागत hdmi_spd_sdi sdi;
पूर्ण;

पूर्णांक hdmi_spd_infoframe_init(काष्ठा hdmi_spd_infoframe *frame,
			    स्थिर अक्षर *venकरोr, स्थिर अक्षर *product);
sमाप_प्रकार hdmi_spd_infoframe_pack(काष्ठा hdmi_spd_infoframe *frame, व्योम *buffer,
				माप_प्रकार size);
sमाप_प्रकार hdmi_spd_infoframe_pack_only(स्थिर काष्ठा hdmi_spd_infoframe *frame,
				     व्योम *buffer, माप_प्रकार size);
पूर्णांक hdmi_spd_infoframe_check(काष्ठा hdmi_spd_infoframe *frame);

क्रमागत hdmi_audio_coding_type अणु
	HDMI_AUDIO_CODING_TYPE_STREAM,
	HDMI_AUDIO_CODING_TYPE_PCM,
	HDMI_AUDIO_CODING_TYPE_AC3,
	HDMI_AUDIO_CODING_TYPE_MPEG1,
	HDMI_AUDIO_CODING_TYPE_MP3,
	HDMI_AUDIO_CODING_TYPE_MPEG2,
	HDMI_AUDIO_CODING_TYPE_AAC_LC,
	HDMI_AUDIO_CODING_TYPE_DTS,
	HDMI_AUDIO_CODING_TYPE_ATRAC,
	HDMI_AUDIO_CODING_TYPE_DSD,
	HDMI_AUDIO_CODING_TYPE_EAC3,
	HDMI_AUDIO_CODING_TYPE_DTS_HD,
	HDMI_AUDIO_CODING_TYPE_MLP,
	HDMI_AUDIO_CODING_TYPE_DST,
	HDMI_AUDIO_CODING_TYPE_WMA_PRO,
	HDMI_AUDIO_CODING_TYPE_CXT,
पूर्ण;

क्रमागत hdmi_audio_sample_size अणु
	HDMI_AUDIO_SAMPLE_SIZE_STREAM,
	HDMI_AUDIO_SAMPLE_SIZE_16,
	HDMI_AUDIO_SAMPLE_SIZE_20,
	HDMI_AUDIO_SAMPLE_SIZE_24,
पूर्ण;

क्रमागत hdmi_audio_sample_frequency अणु
	HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM,
	HDMI_AUDIO_SAMPLE_FREQUENCY_32000,
	HDMI_AUDIO_SAMPLE_FREQUENCY_44100,
	HDMI_AUDIO_SAMPLE_FREQUENCY_48000,
	HDMI_AUDIO_SAMPLE_FREQUENCY_88200,
	HDMI_AUDIO_SAMPLE_FREQUENCY_96000,
	HDMI_AUDIO_SAMPLE_FREQUENCY_176400,
	HDMI_AUDIO_SAMPLE_FREQUENCY_192000,
पूर्ण;

क्रमागत hdmi_audio_coding_type_ext अणु
	/* Refer to Audio Coding Type (CT) field in Data Byte 1 */
	HDMI_AUDIO_CODING_TYPE_EXT_CT,

	/*
	 * The next three CXT values are defined in CEA-861-E only.
	 * They करो not exist in older versions, and in CEA-861-F they are
	 * defined as 'Not in use'.
	 */
	HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC,
	HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC_V2,
	HDMI_AUDIO_CODING_TYPE_EXT_MPEG_SURROUND,

	/* The following CXT values are only defined in CEA-861-F. */
	HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC,
	HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_V2,
	HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC,
	HDMI_AUDIO_CODING_TYPE_EXT_DRA,
	HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_SURROUND,
	HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC_SURROUND = 10,
पूर्ण;

काष्ठा hdmi_audio_infoframe अणु
	क्रमागत hdmi_infoframe_type type;
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर length;
	अचिन्हित अक्षर channels;
	क्रमागत hdmi_audio_coding_type coding_type;
	क्रमागत hdmi_audio_sample_size sample_size;
	क्रमागत hdmi_audio_sample_frequency sample_frequency;
	क्रमागत hdmi_audio_coding_type_ext coding_type_ext;
	अचिन्हित अक्षर channel_allocation;
	अचिन्हित अक्षर level_shअगरt_value;
	bool करोwnmix_inhibit;

पूर्ण;

पूर्णांक hdmi_audio_infoframe_init(काष्ठा hdmi_audio_infoframe *frame);
sमाप_प्रकार hdmi_audio_infoframe_pack(काष्ठा hdmi_audio_infoframe *frame,
				  व्योम *buffer, माप_प्रकार size);
sमाप_प्रकार hdmi_audio_infoframe_pack_only(स्थिर काष्ठा hdmi_audio_infoframe *frame,
				       व्योम *buffer, माप_प्रकार size);
पूर्णांक hdmi_audio_infoframe_check(काष्ठा hdmi_audio_infoframe *frame);

क्रमागत hdmi_3d_काष्ठाure अणु
	HDMI_3D_STRUCTURE_INVALID = -1,
	HDMI_3D_STRUCTURE_FRAME_PACKING = 0,
	HDMI_3D_STRUCTURE_FIELD_ALTERNATIVE,
	HDMI_3D_STRUCTURE_LINE_ALTERNATIVE,
	HDMI_3D_STRUCTURE_SIDE_BY_SIDE_FULL,
	HDMI_3D_STRUCTURE_L_DEPTH,
	HDMI_3D_STRUCTURE_L_DEPTH_GFX_GFX_DEPTH,
	HDMI_3D_STRUCTURE_TOP_AND_BOTTOM,
	HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF = 8,
पूर्ण;


काष्ठा hdmi_venकरोr_infoframe अणु
	क्रमागत hdmi_infoframe_type type;
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर length;
	अचिन्हित पूर्णांक oui;
	u8 vic;
	क्रमागत hdmi_3d_काष्ठाure s3d_काष्ठा;
	अचिन्हित पूर्णांक s3d_ext_data;
पूर्ण;

/* HDR Metadata as per 861.G spec */
काष्ठा hdr_अटल_metadata अणु
	__u8 eotf;
	__u8 metadata_type;
	__u16 max_cll;
	__u16 max_fall;
	__u16 min_cll;
पूर्ण;

/**
 * काष्ठा hdr_sink_metadata - HDR sink metadata
 *
 * Metadata Inक्रमmation पढ़ो from Sink's EDID
 */
काष्ठा hdr_sink_metadata अणु
	/**
	 * @metadata_type: Static_Metadata_Descriptor_ID.
	 */
	__u32 metadata_type;
	/**
	 * @hdmi_type1: HDR Metadata Infoframe.
	 */
	जोड़ अणु
		काष्ठा hdr_अटल_metadata hdmi_type1;
	पूर्ण;
पूर्ण;

पूर्णांक hdmi_venकरोr_infoframe_init(काष्ठा hdmi_venकरोr_infoframe *frame);
sमाप_प्रकार hdmi_venकरोr_infoframe_pack(काष्ठा hdmi_venकरोr_infoframe *frame,
				   व्योम *buffer, माप_प्रकार size);
sमाप_प्रकार hdmi_venकरोr_infoframe_pack_only(स्थिर काष्ठा hdmi_venकरोr_infoframe *frame,
					व्योम *buffer, माप_प्रकार size);
पूर्णांक hdmi_venकरोr_infoframe_check(काष्ठा hdmi_venकरोr_infoframe *frame);

जोड़ hdmi_venकरोr_any_infoframe अणु
	काष्ठा अणु
		क्रमागत hdmi_infoframe_type type;
		अचिन्हित अक्षर version;
		अचिन्हित अक्षर length;
		अचिन्हित पूर्णांक oui;
	पूर्ण any;
	काष्ठा hdmi_venकरोr_infoframe hdmi;
पूर्ण;

/**
 * जोड़ hdmi_infoframe - overall जोड़ of all असलtract infoframe representations
 * @any: generic infoframe
 * @avi: avi infoframe
 * @spd: spd infoframe
 * @venकरोr: जोड़ of all venकरोr infoframes
 * @audio: audio infoframe
 * @drm: Dynamic Range and Mastering infoframe
 *
 * This is used by the generic pack function. This works since all infoframes
 * have the same header which also indicates which type of infoframe should be
 * packed.
 */
जोड़ hdmi_infoframe अणु
	काष्ठा hdmi_any_infoframe any;
	काष्ठा hdmi_avi_infoframe avi;
	काष्ठा hdmi_spd_infoframe spd;
	जोड़ hdmi_venकरोr_any_infoframe venकरोr;
	काष्ठा hdmi_audio_infoframe audio;
	काष्ठा hdmi_drm_infoframe drm;
पूर्ण;

sमाप_प्रकार hdmi_infoframe_pack(जोड़ hdmi_infoframe *frame, व्योम *buffer,
			    माप_प्रकार size);
sमाप_प्रकार hdmi_infoframe_pack_only(स्थिर जोड़ hdmi_infoframe *frame,
				 व्योम *buffer, माप_प्रकार size);
पूर्णांक hdmi_infoframe_check(जोड़ hdmi_infoframe *frame);
पूर्णांक hdmi_infoframe_unpack(जोड़ hdmi_infoframe *frame,
			  स्थिर व्योम *buffer, माप_प्रकार size);
व्योम hdmi_infoframe_log(स्थिर अक्षर *level, काष्ठा device *dev,
			स्थिर जोड़ hdmi_infoframe *frame);

#पूर्ण_अगर /* _DRM_HDMI_H */
