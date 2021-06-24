<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_GRPH_OBJECT_ID_H__
#घोषणा __DAL_GRPH_OBJECT_ID_H__

/* Types of graphics objects */
क्रमागत object_type अणु
	OBJECT_TYPE_UNKNOWN  = 0,

	/* Direct ATOM BIOS translation */
	OBJECT_TYPE_GPU,
	OBJECT_TYPE_ENCODER,
	OBJECT_TYPE_CONNECTOR,
	OBJECT_TYPE_ROUTER,
	OBJECT_TYPE_GENERIC,

	/* Driver specअगरic */
	OBJECT_TYPE_AUDIO,
	OBJECT_TYPE_CONTROLLER,
	OBJECT_TYPE_CLOCK_SOURCE,
	OBJECT_TYPE_ENGINE,

	OBJECT_TYPE_COUNT
पूर्ण;

/* Enumeration inside one type of graphics objects */
क्रमागत object_क्रमागत_id अणु
	ENUM_ID_UNKNOWN = 0,
	ENUM_ID_1,
	ENUM_ID_2,
	ENUM_ID_3,
	ENUM_ID_4,
	ENUM_ID_5,
	ENUM_ID_6,
	ENUM_ID_7,

	ENUM_ID_COUNT
पूर्ण;

/* Generic object ids */
क्रमागत generic_id अणु
	GENERIC_ID_UNKNOWN = 0,
	GENERIC_ID_MXM_OPM,
	GENERIC_ID_GLSYNC,
	GENERIC_ID_STEREO,

	GENERIC_ID_COUNT
पूर्ण;

/* Controller object ids */
क्रमागत controller_id अणु
	CONTROLLER_ID_UNDEFINED = 0,
	CONTROLLER_ID_D0,
	CONTROLLER_ID_D1,
	CONTROLLER_ID_D2,
	CONTROLLER_ID_D3,
	CONTROLLER_ID_D4,
	CONTROLLER_ID_D5,
	CONTROLLER_ID_UNDERLAY0,
	CONTROLLER_ID_MAX = CONTROLLER_ID_UNDERLAY0
पूर्ण;

#घोषणा IS_UNDERLAY_CONTROLLER(ctrlr_id) (ctrlr_id >= CONTROLLER_ID_UNDERLAY0)

/*
 * ClockSource object ids.
 * We मुख्यtain the order matching (more or less) ATOM BIOS
 * to improve optimized acquire
 */
क्रमागत घड़ी_source_id अणु
	CLOCK_SOURCE_ID_UNDEFINED = 0,
	CLOCK_SOURCE_ID_PLL0,
	CLOCK_SOURCE_ID_PLL1,
	CLOCK_SOURCE_ID_PLL2,
	CLOCK_SOURCE_ID_EXTERNAL, /* ID (Phy) ref. clk. क्रम DP */
	CLOCK_SOURCE_ID_DCPLL,
	CLOCK_SOURCE_ID_DFS,	/* DENTIST */
	CLOCK_SOURCE_ID_VCE,	/* VCE करोes not need a real PLL */
	/* Used to distinguish between programming pixel घड़ी and ID (Phy) घड़ी */
	CLOCK_SOURCE_ID_DP_DTO,

	CLOCK_SOURCE_COMBO_PHY_PLL0, /*combo PHY PLL defines (DC 11.2 and up)*/
	CLOCK_SOURCE_COMBO_PHY_PLL1,
	CLOCK_SOURCE_COMBO_PHY_PLL2,
	CLOCK_SOURCE_COMBO_PHY_PLL3,
	CLOCK_SOURCE_COMBO_PHY_PLL4,
	CLOCK_SOURCE_COMBO_PHY_PLL5,
	CLOCK_SOURCE_COMBO_DISPLAY_PLL0
पूर्ण;

/* Encoder object ids */
क्रमागत encoder_id अणु
	ENCODER_ID_UNKNOWN = 0,

	/* Radeon Class Display Hardware */
	ENCODER_ID_INTERNAL_LVDS,
	ENCODER_ID_INTERNAL_TMDS1,
	ENCODER_ID_INTERNAL_TMDS2,
	ENCODER_ID_INTERNAL_DAC1,
	ENCODER_ID_INTERNAL_DAC2,	/* TV/CV DAC */

	/* External Third Party Encoders */
	ENCODER_ID_INTERNAL_LVTM1,	/* not used क्रम Radeon */
	ENCODER_ID_INTERNAL_HDMI,

	/* Kaledisope (KLDSCP) Class Display Hardware */
	ENCODER_ID_INTERNAL_KLDSCP_TMDS1,
	ENCODER_ID_INTERNAL_KLDSCP_DAC1,
	ENCODER_ID_INTERNAL_KLDSCP_DAC2,	/* Shared with CV/TV and CRT */
	/* External TMDS (dual link) */
	ENCODER_ID_EXTERNAL_MVPU_FPGA,	/* MVPU FPGA chip */
	ENCODER_ID_INTERNAL_DDI,
	ENCODER_ID_INTERNAL_UNIPHY,
	ENCODER_ID_INTERNAL_KLDSCP_LVTMA,
	ENCODER_ID_INTERNAL_UNIPHY1,
	ENCODER_ID_INTERNAL_UNIPHY2,
	ENCODER_ID_EXTERNAL_NUTMEG,
	ENCODER_ID_EXTERNAL_TRAVIS,

	ENCODER_ID_INTERNAL_WIRELESS,	/* Internal wireless display encoder */
	ENCODER_ID_INTERNAL_UNIPHY3,
	ENCODER_ID_INTERNAL_VIRTUAL,
पूर्ण;

/* Connector object ids */
क्रमागत connector_id अणु
	CONNECTOR_ID_UNKNOWN = 0,
	CONNECTOR_ID_SINGLE_LINK_DVII = 1,
	CONNECTOR_ID_DUAL_LINK_DVII = 2,
	CONNECTOR_ID_SINGLE_LINK_DVID = 3,
	CONNECTOR_ID_DUAL_LINK_DVID = 4,
	CONNECTOR_ID_VGA = 5,
	CONNECTOR_ID_HDMI_TYPE_A = 12,
	CONNECTOR_ID_LVDS = 14,
	CONNECTOR_ID_PCIE = 16,
	CONNECTOR_ID_HARDCODE_DVI = 18,
	CONNECTOR_ID_DISPLAY_PORT = 19,
	CONNECTOR_ID_EDP = 20,
	CONNECTOR_ID_MXM = 21,
	CONNECTOR_ID_WIRELESS = 22,
	CONNECTOR_ID_MIRACAST = 23,

	CONNECTOR_ID_VIRTUAL = 100
पूर्ण;

/* Audio object ids */
क्रमागत audio_id अणु
	AUDIO_ID_UNKNOWN = 0,
	AUDIO_ID_INTERNAL_AZALIA
पूर्ण;

/* Engine object ids */
क्रमागत engine_id अणु
	ENGINE_ID_DIGA,
	ENGINE_ID_DIGB,
	ENGINE_ID_DIGC,
	ENGINE_ID_DIGD,
	ENGINE_ID_DIGE,
	ENGINE_ID_DIGF,
	ENGINE_ID_DIGG,
	ENGINE_ID_DACA,
	ENGINE_ID_DACB,
	ENGINE_ID_VCE,	/* wireless display pseuकरो-encoder */
	ENGINE_ID_VIRTUAL,

	ENGINE_ID_COUNT,
	ENGINE_ID_UNKNOWN = (-1L)
पूर्ण;

क्रमागत transmitter_color_depth अणु
	TRANSMITTER_COLOR_DEPTH_24 = 0,  /* 8  bits */
	TRANSMITTER_COLOR_DEPTH_30,      /* 10 bits */
	TRANSMITTER_COLOR_DEPTH_36,      /* 12 bits */
	TRANSMITTER_COLOR_DEPTH_48       /* 16 bits */
पूर्ण;

क्रमागत dp_alt_mode अणु
	DP_Alt_mode__Unknown = 0,
	DP_Alt_mode__Connect,
	DP_Alt_mode__NoConnect,
पूर्ण;
/*
 *****************************************************************************
 * graphics_object_id काष्ठा
 *
 * graphics_object_id is a very simple काष्ठा wrapping 32bit Graphics
 * Object identication
 *
 * This काष्ठा should stay very simple
 *  No dependencies at all (no includes)
 *  No debug messages or निश्चितs
 *  No #अगर_अघोषित and preprocessor directives
 *  No grow in space (no more data member)
 *****************************************************************************
 */

काष्ठा graphics_object_id अणु
	uपूर्णांक32_t  id:8;
	uपूर्णांक32_t  क्रमागत_id:4;
	uपूर्णांक32_t  type:4;
	uपूर्णांक32_t  reserved:16; /* क्रम padding. total size should be u32 */
पूर्ण;

/* some simple functions क्रम convenient graphics_object_id handle */

अटल अंतरभूत काष्ठा graphics_object_id dal_graphics_object_id_init(
	uपूर्णांक32_t id,
	क्रमागत object_क्रमागत_id क्रमागत_id,
	क्रमागत object_type type)
अणु
	काष्ठा graphics_object_id result = अणु
		id, क्रमागत_id, type, 0
	पूर्ण;

	वापस result;
पूर्ण

/* Based on पूर्णांकernal data members memory layout */
अटल अंतरभूत uपूर्णांक32_t dal_graphics_object_id_to_uपूर्णांक(
	काष्ठा graphics_object_id id)
अणु
	वापस id.id + (id.क्रमागत_id << 0x8) + (id.type << 0xc);
पूर्ण

अटल अंतरभूत क्रमागत controller_id dal_graphics_object_id_get_controller_id(
	काष्ठा graphics_object_id id)
अणु
	अगर (id.type == OBJECT_TYPE_CONTROLLER)
		वापस (क्रमागत controller_id) id.id;
	वापस CONTROLLER_ID_UNDEFINED;
पूर्ण

अटल अंतरभूत क्रमागत घड़ी_source_id dal_graphics_object_id_get_घड़ी_source_id(
	काष्ठा graphics_object_id id)
अणु
	अगर (id.type == OBJECT_TYPE_CLOCK_SOURCE)
		वापस (क्रमागत घड़ी_source_id) id.id;
	वापस CLOCK_SOURCE_ID_UNDEFINED;
पूर्ण

अटल अंतरभूत क्रमागत encoder_id dal_graphics_object_id_get_encoder_id(
	काष्ठा graphics_object_id id)
अणु
	अगर (id.type == OBJECT_TYPE_ENCODER)
		वापस (क्रमागत encoder_id) id.id;
	वापस ENCODER_ID_UNKNOWN;
पूर्ण

अटल अंतरभूत क्रमागत connector_id dal_graphics_object_id_get_connector_id(
	काष्ठा graphics_object_id id)
अणु
	अगर (id.type == OBJECT_TYPE_CONNECTOR)
		वापस (क्रमागत connector_id) id.id;
	वापस CONNECTOR_ID_UNKNOWN;
पूर्ण

अटल अंतरभूत क्रमागत audio_id dal_graphics_object_id_get_audio_id(
	काष्ठा graphics_object_id id)
अणु
	अगर (id.type == OBJECT_TYPE_AUDIO)
		वापस (क्रमागत audio_id) id.id;
	वापस AUDIO_ID_UNKNOWN;
पूर्ण

अटल अंतरभूत क्रमागत engine_id dal_graphics_object_id_get_engine_id(
	काष्ठा graphics_object_id id)
अणु
	अगर (id.type == OBJECT_TYPE_ENGINE)
		वापस (क्रमागत engine_id) id.id;
	वापस ENGINE_ID_UNKNOWN;
पूर्ण

अटल अंतरभूत bool dal_graphics_object_id_equal(
	काष्ठा graphics_object_id id_1,
	काष्ठा graphics_object_id id_2)
अणु
	अगर ((id_1.id == id_2.id) && (id_1.क्रमागत_id == id_2.क्रमागत_id) &&
		(id_1.type == id_2.type)) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
#पूर्ण_अगर
