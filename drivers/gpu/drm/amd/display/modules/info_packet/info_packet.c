<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
 *
 * Authors: AMD
 *
 */

#समावेश "mod_info_packet.h"
#समावेश "core_types.h"
#समावेश "dc_types.h"
#समावेश "mod_shared.h"
#समावेश "mod_freesync.h"
#समावेश "dc.h"

क्रमागत vsc_packet_revision अणु
	vsc_packet_undefined = 0,
	//01h = VSC SDP supports only 3D stereo.
	vsc_packet_rev1 = 1,
	//02h = 3D stereo + PSR.
	vsc_packet_rev2 = 2,
	//03h = 3D stereo + PSR2.
	vsc_packet_rev3 = 3,
	//04h = 3D stereo + PSR/PSR2 + Y-coordinate.
	vsc_packet_rev4 = 4,
	//05h = 3D stereo + PSR/PSR2 + Y-coordinate + Pixel Encoding/Colorimetry Format
	vsc_packet_rev5 = 5,
पूर्ण;

#घोषणा HDMI_INFOFRAME_TYPE_VENDOR 0x81
#घोषणा HF_VSIF_VERSION 1

// VTEM Byte Offset
#घोषणा VTEM_PB0		0
#घोषणा VTEM_PB1		1
#घोषणा VTEM_PB2		2
#घोषणा VTEM_PB3		3
#घोषणा VTEM_PB4		4
#घोषणा VTEM_PB5		5
#घोषणा VTEM_PB6		6

#घोषणा VTEM_MD0		7
#घोषणा VTEM_MD1		8
#घोषणा VTEM_MD2		9
#घोषणा VTEM_MD3		10


// VTEM Byte Masks
//PB0
#घोषणा MASK_VTEM_PB0__RESERVED0  0x01
#घोषणा MASK_VTEM_PB0__SYNC       0x02
#घोषणा MASK_VTEM_PB0__VFR        0x04
#घोषणा MASK_VTEM_PB0__AFR        0x08
#घोषणा MASK_VTEM_PB0__DS_TYPE    0x30
	//0: Periodic pseuकरो-अटल EM Data Set
	//1: Periodic dynamic EM Data Set
	//2: Unique EM Data Set
	//3: Reserved
#घोषणा MASK_VTEM_PB0__END        0x40
#घोषणा MASK_VTEM_PB0__NEW        0x80

//PB1
#घोषणा MASK_VTEM_PB1__RESERVED1 0xFF

//PB2
#घोषणा MASK_VTEM_PB2__ORGANIZATION_ID 0xFF
	//0: This is a Venकरोr Specअगरic EM Data Set
	//1: This EM Data Set is defined by This Specअगरication (HDMI 2.1 r102.clean)
	//2: This EM Data Set is defined by CTA-861-G
	//3: This EM Data Set is defined by VESA
//PB3
#घोषणा MASK_VTEM_PB3__DATA_SET_TAG_MSB    0xFF
//PB4
#घोषणा MASK_VTEM_PB4__DATA_SET_TAG_LSB    0xFF
//PB5
#घोषणा MASK_VTEM_PB5__DATA_SET_LENGTH_MSB 0xFF
//PB6
#घोषणा MASK_VTEM_PB6__DATA_SET_LENGTH_LSB 0xFF



//PB7-27 (20 bytes):
//PB7 = MD0
#घोषणा MASK_VTEM_MD0__VRR_EN         0x01
#घोषणा MASK_VTEM_MD0__M_CONST        0x02
#घोषणा MASK_VTEM_MD0__RESERVED2      0x0C
#घोषणा MASK_VTEM_MD0__FVA_FACTOR_M1  0xF0

//MD1
#घोषणा MASK_VTEM_MD1__BASE_VFRONT    0xFF

//MD2
#घोषणा MASK_VTEM_MD2__BASE_REFRESH_RATE_98  0x03
#घोषणा MASK_VTEM_MD2__RB                    0x04
#घोषणा MASK_VTEM_MD2__RESERVED3             0xF8

//MD3
#घोषणा MASK_VTEM_MD3__BASE_REFRESH_RATE_07  0xFF

क्रमागत ColorimetryRGBDP अणु
	ColorimetryRGB_DP_sRGB               = 0,
	ColorimetryRGB_DP_AकरोbeRGB           = 3,
	ColorimetryRGB_DP_P3                 = 4,
	ColorimetryRGB_DP_CustomColorProfile = 5,
	ColorimetryRGB_DP_ITU_R_BT2020RGB    = 6,
पूर्ण;
क्रमागत ColorimetryYCCDP अणु
	ColorimetryYCC_DP_ITU601        = 0,
	ColorimetryYCC_DP_ITU709        = 1,
	ColorimetryYCC_DP_AकरोbeYCC      = 5,
	ColorimetryYCC_DP_ITU2020YCC    = 6,
	ColorimetryYCC_DP_ITU2020YCbCr  = 7,
पूर्ण;

व्योम mod_build_vsc_infopacket(स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा dc_info_packet *info_packet)
अणु
	अचिन्हित पूर्णांक vsc_packet_revision = vsc_packet_undefined;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक pixelEncoding = 0;
	अचिन्हित पूर्णांक colorimetryFormat = 0;
	bool stereo3dSupport = false;

	अगर (stream->timing.timing_3d_क्रमmat != TIMING_3D_FORMAT_NONE && stream->view_क्रमmat != VIEW_3D_FORMAT_NONE) अणु
		vsc_packet_revision = vsc_packet_rev1;
		stereo3dSupport = true;
	पूर्ण

	/*VSC packet set to 2 when DP revision >= 1.2*/
	अगर (stream->link->psr_settings.psr_version != DC_PSR_VERSION_UNSUPPORTED)
		vsc_packet_revision = vsc_packet_rev2;

	/* Update to revision 5 क्रम extended colorimetry support */
	अगर (stream->use_vsc_sdp_क्रम_colorimetry)
		vsc_packet_revision = vsc_packet_rev5;

	/* VSC packet not needed based on the features
	 * supported by this DP display
	 */
	अगर (vsc_packet_revision == vsc_packet_undefined)
		वापस;

	अगर (vsc_packet_revision == vsc_packet_rev2) अणु
		/* Secondary-data Packet ID = 0*/
		info_packet->hb0 = 0x00;
		/* 07h - Packet Type Value indicating Video
		 * Stream Configuration packet
		 */
		info_packet->hb1 = 0x07;
		/* 02h = VSC SDP supporting 3D stereo and PSR
		 * (applies to eDP v1.3 or higher).
		 */
		info_packet->hb2 = 0x02;
		/* 08h = VSC packet supporting 3D stereo + PSR
		 * (HB2 = 02h).
		 */
		info_packet->hb3 = 0x08;

		क्रम (i = 0; i < 28; i++)
			info_packet->sb[i] = 0;

		info_packet->valid = true;
	पूर्ण

	अगर (vsc_packet_revision == vsc_packet_rev1) अणु

		info_packet->hb0 = 0x00;	// Secondary-data Packet ID = 0
		info_packet->hb1 = 0x07;	// 07h = Packet Type Value indicating Video Stream Configuration packet
		info_packet->hb2 = 0x01;	// 01h = Revision number. VSC SDP supporting 3D stereo only
		info_packet->hb3 = 0x01;	// 01h = VSC SDP supporting 3D stereo only (HB2 = 01h).

		info_packet->valid = true;
	पूर्ण

	अगर (stereo3dSupport) अणु
		/* ==============================================================================================================|
		 * A. STEREO 3D
		 * ==============================================================================================================|
		 * VSC Payload (1 byte) From DP1.2 spec
		 *
		 * Bits 3:0 (Stereo Interface Method Code)  |  Bits 7:4 (Stereo Interface Method Specअगरic Parameter)
		 * -----------------------------------------------------------------------------------------------------
		 * 0 = Non Stereo Video                     |  Must be set to 0x0
		 * -----------------------------------------------------------------------------------------------------
		 * 1 = Frame/Field Sequential               |  0x0: L + R view indication based on MISC1 bit 2:1
		 *                                          |  0x1: Right when Stereo Signal = 1
		 *                                          |  0x2: Left when Stereo Signal = 1
		 *                                          |  (others reserved)
		 * -----------------------------------------------------------------------------------------------------
		 * 2 = Stacked Frame                        |  0x0: Left view is on top and right view on bottom
		 *                                          |  (others reserved)
		 * -----------------------------------------------------------------------------------------------------
		 * 3 = Pixel Interleaved                    |  0x0: horiz पूर्णांकerleaved, right view pixels on even lines
		 *                                          |  0x1: horiz पूर्णांकerleaved, right view pixels on odd lines
		 *                                          |  0x2: checker board, start with left view pixel
		 *                                          |  0x3: vertical पूर्णांकerleaved, start with left view pixels
		 *                                          |  0x4: vertical पूर्णांकerleaved, start with right view pixels
		 *                                          |  (others reserved)
		 * -----------------------------------------------------------------------------------------------------
		 * 4 = Side-by-side                         |  0x0: left half represents left eye view
		 *                                          |  0x1: left half represents right eye view
		 */
		चयन (stream->timing.timing_3d_क्रमmat) अणु
		हाल TIMING_3D_FORMAT_HW_FRAME_PACKING:
		हाल TIMING_3D_FORMAT_SW_FRAME_PACKING:
		हाल TIMING_3D_FORMAT_TOP_AND_BOTTOM:
		हाल TIMING_3D_FORMAT_TB_SW_PACKED:
			info_packet->sb[0] = 0x02; // Stacked Frame, Left view is on top and right view on bottom.
			अवरोध;
		हाल TIMING_3D_FORMAT_DP_HDMI_INBAND_FA:
		हाल TIMING_3D_FORMAT_INBAND_FA:
			info_packet->sb[0] = 0x01; // Frame/Field Sequential, L + R view indication based on MISC1 bit 2:1
			अवरोध;
		हाल TIMING_3D_FORMAT_SIDE_BY_SIDE:
		हाल TIMING_3D_FORMAT_SBS_SW_PACKED:
			info_packet->sb[0] = 0x04; // Side-by-side
			अवरोध;
		शेष:
			info_packet->sb[0] = 0x00; // No Stereo Video, Shall be cleared to 0x0.
			अवरोध;
		पूर्ण

	पूर्ण

	/* 05h = VSC SDP supporting 3D stereo, PSR2, and Pixel Encoding/Colorimetry Format indication.
	 *   Added in DP1.3, a DP Source device is allowed to indicate the pixel encoding/colorimetry
	 *   क्रमmat to the DP Sink device with VSC SDP only when the DP Sink device supports it
	 *   (i.e., VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED bit in the DPRX_FEATURE_ENUMERATION_LIST
	 *   रेजिस्टर (DPCD Address 02210h, bit 3) is set to 1).
	 *   (Requires VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED bit set to 1 in DPCD 02210h. This
	 *   DPCD रेजिस्टर is exposed in the new Extended Receiver Capability field क्रम DPCD Rev. 1.4
	 *   (and higher). When MISC1. bit 6. is Set to 1, a Source device uses a VSC SDP to indicate
	 *   the Pixel Encoding/Colorimetry Format and that a Sink device must ignore MISC1, bit 7, and
	 *   MISC0, bits 7:1 (MISC1, bit 7. and MISC0, bits 7:1 become "don't care").)
	 */
	अगर (vsc_packet_revision == vsc_packet_rev5) अणु
		/* Secondary-data Packet ID = 0 */
		info_packet->hb0 = 0x00;
		/* 07h - Packet Type Value indicating Video Stream Configuration packet */
		info_packet->hb1 = 0x07;
		/* 05h = VSC SDP supporting 3D stereo, PSR2, and Pixel Encoding/Colorimetry Format indication. */
		info_packet->hb2 = 0x05;
		/* 13h = VSC SDP supporting 3D stereo, + PSR2, + Pixel Encoding/Colorimetry Format indication (HB2 = 05h). */
		info_packet->hb3 = 0x13;

		info_packet->valid = true;

		/* Set VSC SDP fields क्रम pixel encoding and colorimetry क्रमmat from DP 1.3 specs
		 * Data Bytes DB 18~16
		 * Bits 3:0 (Colorimetry Format)        |  Bits 7:4 (Pixel Encoding)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 = sRGB                           |  0 = RGB
		 * 0x1 = RGB Wide Gamut Fixed Poपूर्णांक
		 * 0x2 = RGB Wide Gamut Floating Poपूर्णांक
		 * 0x3 = AकरोbeRGB
		 * 0x4 = DCI-P3
		 * 0x5 = CustomColorProfile
		 * (others reserved)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 = ITU-R BT.601                   |  1 = YCbCr444
		 * 0x1 = ITU-R BT.709
		 * 0x2 = xvYCC601
		 * 0x3 = xvYCC709
		 * 0x4 = sYCC601
		 * 0x5 = AकरोbeYCC601
		 * 0x6 = ITU-R BT.2020 Y'cC'bcC'rc
		 * 0x7 = ITU-R BT.2020 Y'C'bC'r
		 * (others reserved)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 = ITU-R BT.601                   |  2 = YCbCr422
		 * 0x1 = ITU-R BT.709
		 * 0x2 = xvYCC601
		 * 0x3 = xvYCC709
		 * 0x4 = sYCC601
		 * 0x5 = AकरोbeYCC601
		 * 0x6 = ITU-R BT.2020 Y'cC'bcC'rc
		 * 0x7 = ITU-R BT.2020 Y'C'bC'r
		 * (others reserved)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 = ITU-R BT.601                   |  3 = YCbCr420
		 * 0x1 = ITU-R BT.709
		 * 0x2 = xvYCC601
		 * 0x3 = xvYCC709
		 * 0x4 = sYCC601
		 * 0x5 = AकरोbeYCC601
		 * 0x6 = ITU-R BT.2020 Y'cC'bcC'rc
		 * 0x7 = ITU-R BT.2020 Y'C'bC'r
		 * (others reserved)
		 * ----------------------------------------------------------------------------------------------------
		 * 0x0 =DICOM Part14 Grayscale          |  4 = Yonly
		 * Display Function
		 * (others reserved)
		 */

		/* Set Pixel Encoding */
		चयन (stream->timing.pixel_encoding) अणु
		हाल PIXEL_ENCODING_RGB:
			pixelEncoding = 0x0;  /* RGB = 0h */
			अवरोध;
		हाल PIXEL_ENCODING_YCBCR444:
			pixelEncoding = 0x1;  /* YCbCr444 = 1h */
			अवरोध;
		हाल PIXEL_ENCODING_YCBCR422:
			pixelEncoding = 0x2;  /* YCbCr422 = 2h */
			अवरोध;
		हाल PIXEL_ENCODING_YCBCR420:
			pixelEncoding = 0x3;  /* YCbCr420 = 3h */
			अवरोध;
		शेष:
			pixelEncoding = 0x0;  /* शेष RGB = 0h */
			अवरोध;
		पूर्ण

		/* Set Colorimetry क्रमmat based on pixel encoding */
		चयन (stream->timing.pixel_encoding) अणु
		हाल PIXEL_ENCODING_RGB:
			अगर ((stream->output_color_space == COLOR_SPACE_SRGB) ||
					(stream->output_color_space == COLOR_SPACE_SRGB_LIMITED))
				colorimetryFormat = ColorimetryRGB_DP_sRGB;
			अन्यथा अगर (stream->output_color_space == COLOR_SPACE_ADOBERGB)
				colorimetryFormat = ColorimetryRGB_DP_AकरोbeRGB;
			अन्यथा अगर ((stream->output_color_space == COLOR_SPACE_2020_RGB_FULLRANGE) ||
					(stream->output_color_space == COLOR_SPACE_2020_RGB_LIMITEDRANGE))
				colorimetryFormat = ColorimetryRGB_DP_ITU_R_BT2020RGB;
			अवरोध;

		हाल PIXEL_ENCODING_YCBCR444:
		हाल PIXEL_ENCODING_YCBCR422:
		हाल PIXEL_ENCODING_YCBCR420:
			/* Note: xvYCC probably not supported correctly here on DP since colorspace translation
			 * loses distinction between BT601 vs xvYCC601 in translation
			 */
			अगर (stream->output_color_space == COLOR_SPACE_YCBCR601)
				colorimetryFormat = ColorimetryYCC_DP_ITU601;
			अन्यथा अगर (stream->output_color_space == COLOR_SPACE_YCBCR709)
				colorimetryFormat = ColorimetryYCC_DP_ITU709;
			अन्यथा अगर (stream->output_color_space == COLOR_SPACE_ADOBERGB)
				colorimetryFormat = ColorimetryYCC_DP_AकरोbeYCC;
			अन्यथा अगर (stream->output_color_space == COLOR_SPACE_2020_YCBCR)
				colorimetryFormat = ColorimetryYCC_DP_ITU2020YCbCr;
			अवरोध;

		शेष:
			colorimetryFormat = ColorimetryRGB_DP_sRGB;
			अवरोध;
		पूर्ण

		info_packet->sb[16] = (pixelEncoding << 4) | colorimetryFormat;

		/* Set color depth */
		चयन (stream->timing.display_color_depth) अणु
		हाल COLOR_DEPTH_666:
			/* NOTE: This is actually not valid क्रम YCbCr pixel encoding to have 6 bpc
			 *       as of DP1.4 spec, but value of 0 probably reserved here क्रम potential future use.
			 */
			info_packet->sb[17] = 0;
			अवरोध;
		हाल COLOR_DEPTH_888:
			info_packet->sb[17] = 1;
			अवरोध;
		हाल COLOR_DEPTH_101010:
			info_packet->sb[17] = 2;
			अवरोध;
		हाल COLOR_DEPTH_121212:
			info_packet->sb[17] = 3;
			अवरोध;
		/*हाल COLOR_DEPTH_141414: -- NO SUCH FORMAT IN DP SPEC */
		हाल COLOR_DEPTH_161616:
			info_packet->sb[17] = 4;
			अवरोध;
		शेष:
			info_packet->sb[17] = 0;
			अवरोध;
		पूर्ण

		/* all YCbCr are always limited range */
		अगर ((stream->output_color_space == COLOR_SPACE_SRGB_LIMITED) ||
				(stream->output_color_space == COLOR_SPACE_2020_RGB_LIMITEDRANGE) ||
				(pixelEncoding != 0x0)) अणु
			info_packet->sb[17] |= 0x80; /* DB17 bit 7 set to 1 क्रम CEA timing. */
		पूर्ण

		/* Content Type (Bits 2:0)
		 *  0 = Not defined.
		 *  1 = Graphics.
		 *  2 = Photo.
		 *  3 = Video.
		 *  4 = Game.
		 */
		info_packet->sb[18] = 0;
	पूर्ण
पूर्ण

/**
 *  mod_build_hf_vsअगर_infopacket - Prepare HDMI Venकरोr Specअगरic info frame.
 *                                 Follows HDMI Spec to build up Venकरोr Specअगरic info frame
 *
 *  @stream:      contains data we may need to स्थिरruct VSIF (i.e. timing_3d_क्रमmat, etc.)
 *  @info_packet: output काष्ठाure where to store VSIF
 */
व्योम mod_build_hf_vsअगर_infopacket(स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा dc_info_packet *info_packet)
अणु
		अचिन्हित पूर्णांक length = 5;
		bool hdmi_vic_mode = false;
		uपूर्णांक8_t checksum = 0;
		uपूर्णांक32_t i = 0;
		क्रमागत dc_timing_3d_क्रमmat क्रमmat;

		info_packet->valid = false;
		क्रमmat = stream->timing.timing_3d_क्रमmat;
		अगर (stream->view_क्रमmat == VIEW_3D_FORMAT_NONE)
			क्रमmat = TIMING_3D_FORMAT_NONE;

		अगर (stream->timing.hdmi_vic != 0
				&& stream->timing.h_total >= 3840
				&& stream->timing.v_total >= 2160
				&& क्रमmat == TIMING_3D_FORMAT_NONE)
			hdmi_vic_mode = true;

		अगर ((क्रमmat == TIMING_3D_FORMAT_NONE) && !hdmi_vic_mode)
			वापस;

		info_packet->sb[1] = 0x03;
		info_packet->sb[2] = 0x0C;
		info_packet->sb[3] = 0x00;

		अगर (क्रमmat != TIMING_3D_FORMAT_NONE)
			info_packet->sb[4] = (2 << 5);

		अन्यथा अगर (hdmi_vic_mode)
			info_packet->sb[4] = (1 << 5);

		चयन (क्रमmat) अणु
		हाल TIMING_3D_FORMAT_HW_FRAME_PACKING:
		हाल TIMING_3D_FORMAT_SW_FRAME_PACKING:
			info_packet->sb[5] = (0x0 << 4);
			अवरोध;

		हाल TIMING_3D_FORMAT_SIDE_BY_SIDE:
		हाल TIMING_3D_FORMAT_SBS_SW_PACKED:
			info_packet->sb[5] = (0x8 << 4);
			length = 6;
			अवरोध;

		हाल TIMING_3D_FORMAT_TOP_AND_BOTTOM:
		हाल TIMING_3D_FORMAT_TB_SW_PACKED:
			info_packet->sb[5] = (0x6 << 4);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		अगर (hdmi_vic_mode)
			info_packet->sb[5] = stream->timing.hdmi_vic;

		info_packet->hb0 = HDMI_INFOFRAME_TYPE_VENDOR;
		info_packet->hb1 = 0x01;
		info_packet->hb2 = (uपूर्णांक8_t) (length);

		checksum += info_packet->hb0;
		checksum += info_packet->hb1;
		checksum += info_packet->hb2;

		क्रम (i = 1; i <= length; i++)
			checksum += info_packet->sb[i];

		info_packet->sb[0] = (uपूर्णांक8_t) (0x100 - checksum);

		info_packet->valid = true;
पूर्ण

