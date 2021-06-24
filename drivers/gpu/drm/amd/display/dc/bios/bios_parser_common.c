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

#समावेश "bios_parser_common.h"
#समावेश "include/grph_object_ctrl_defs.h"

अटल क्रमागत object_type object_type_from_bios_object_id(uपूर्णांक32_t bios_object_id)
अणु
	uपूर्णांक32_t bios_object_type = (bios_object_id & OBJECT_TYPE_MASK)
				>> OBJECT_TYPE_SHIFT;
	क्रमागत object_type object_type;

	चयन (bios_object_type) अणु
	हाल GRAPH_OBJECT_TYPE_GPU:
		object_type = OBJECT_TYPE_GPU;
		अवरोध;
	हाल GRAPH_OBJECT_TYPE_ENCODER:
		object_type = OBJECT_TYPE_ENCODER;
		अवरोध;
	हाल GRAPH_OBJECT_TYPE_CONNECTOR:
		object_type = OBJECT_TYPE_CONNECTOR;
		अवरोध;
	हाल GRAPH_OBJECT_TYPE_ROUTER:
		object_type = OBJECT_TYPE_ROUTER;
		अवरोध;
	हाल GRAPH_OBJECT_TYPE_GENERIC:
		object_type = OBJECT_TYPE_GENERIC;
		अवरोध;
	शेष:
		object_type = OBJECT_TYPE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस object_type;
पूर्ण

अटल क्रमागत object_क्रमागत_id क्रमागत_id_from_bios_object_id(uपूर्णांक32_t bios_object_id)
अणु
	uपूर्णांक32_t bios_क्रमागत_id =
			(bios_object_id & ENUM_ID_MASK) >> ENUM_ID_SHIFT;
	क्रमागत object_क्रमागत_id id;

	चयन (bios_क्रमागत_id) अणु
	हाल GRAPH_OBJECT_ENUM_ID1:
		id = ENUM_ID_1;
		अवरोध;
	हाल GRAPH_OBJECT_ENUM_ID2:
		id = ENUM_ID_2;
		अवरोध;
	हाल GRAPH_OBJECT_ENUM_ID3:
		id = ENUM_ID_3;
		अवरोध;
	हाल GRAPH_OBJECT_ENUM_ID4:
		id = ENUM_ID_4;
		अवरोध;
	हाल GRAPH_OBJECT_ENUM_ID5:
		id = ENUM_ID_5;
		अवरोध;
	हाल GRAPH_OBJECT_ENUM_ID6:
		id = ENUM_ID_6;
		अवरोध;
	हाल GRAPH_OBJECT_ENUM_ID7:
		id = ENUM_ID_7;
		अवरोध;
	शेष:
		id = ENUM_ID_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस id;
पूर्ण

अटल uपूर्णांक32_t gpu_id_from_bios_object_id(uपूर्णांक32_t bios_object_id)
अणु
	वापस (bios_object_id & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
पूर्ण

अटल क्रमागत encoder_id encoder_id_from_bios_object_id(uपूर्णांक32_t bios_object_id)
अणु
	uपूर्णांक32_t bios_encoder_id = gpu_id_from_bios_object_id(bios_object_id);
	क्रमागत encoder_id id;

	चयन (bios_encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
		id = ENCODER_ID_INTERNAL_LVDS;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
		id = ENCODER_ID_INTERNAL_TMDS1;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS2:
		id = ENCODER_ID_INTERNAL_TMDS2;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC1:
		id = ENCODER_ID_INTERNAL_DAC1;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
		id = ENCODER_ID_INTERNAL_DAC2;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		id = ENCODER_ID_INTERNAL_LVTM1;
		अवरोध;
	हाल ENCODER_OBJECT_ID_HDMI_INTERNAL:
		id = ENCODER_ID_INTERNAL_HDMI;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
		id = ENCODER_ID_INTERNAL_KLDSCP_TMDS1;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
		id = ENCODER_ID_INTERNAL_KLDSCP_DAC1;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		id = ENCODER_ID_INTERNAL_KLDSCP_DAC2;
		अवरोध;
	हाल ENCODER_OBJECT_ID_MVPU_FPGA:
		id = ENCODER_ID_EXTERNAL_MVPU_FPGA;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
		id = ENCODER_ID_INTERNAL_DDI;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		id = ENCODER_ID_INTERNAL_UNIPHY;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		id = ENCODER_ID_INTERNAL_KLDSCP_LVTMA;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		id = ENCODER_ID_INTERNAL_UNIPHY1;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		id = ENCODER_ID_INTERNAL_UNIPHY2;
		अवरोध;
	हाल ENCODER_OBJECT_ID_ALMOND: /* ENCODER_OBJECT_ID_NUTMEG */
		id = ENCODER_ID_EXTERNAL_NUTMEG;
		अवरोध;
	हाल ENCODER_OBJECT_ID_TRAVIS:
		id = ENCODER_ID_EXTERNAL_TRAVIS;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		id = ENCODER_ID_INTERNAL_UNIPHY3;
		अवरोध;
	शेष:
		id = ENCODER_ID_UNKNOWN;
		ASSERT(0);
		अवरोध;
	पूर्ण

	वापस id;
पूर्ण

अटल क्रमागत connector_id connector_id_from_bios_object_id(
	uपूर्णांक32_t bios_object_id)
अणु
	uपूर्णांक32_t bios_connector_id = gpu_id_from_bios_object_id(bios_object_id);

	क्रमागत connector_id id;

	चयन (bios_connector_id) अणु
	हाल CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I:
		id = CONNECTOR_ID_SINGLE_LINK_DVII;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I:
		id = CONNECTOR_ID_DUAL_LINK_DVII;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D:
		id = CONNECTOR_ID_SINGLE_LINK_DVID;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D:
		id = CONNECTOR_ID_DUAL_LINK_DVID;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_VGA:
		id = CONNECTOR_ID_VGA;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_HDMI_TYPE_A:
		id = CONNECTOR_ID_HDMI_TYPE_A;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_LVDS:
		id = CONNECTOR_ID_LVDS;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_PCIE_CONNECTOR:
		id = CONNECTOR_ID_PCIE;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_HARDCODE_DVI:
		id = CONNECTOR_ID_HARDCODE_DVI;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_DISPLAYPORT:
		id = CONNECTOR_ID_DISPLAY_PORT;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_eDP:
		id = CONNECTOR_ID_EDP;
		अवरोध;
	हाल CONNECTOR_OBJECT_ID_MXM:
		id = CONNECTOR_ID_MXM;
		अवरोध;
	शेष:
		id = CONNECTOR_ID_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस id;
पूर्ण

अटल क्रमागत generic_id generic_id_from_bios_object_id(uपूर्णांक32_t bios_object_id)
अणु
	uपूर्णांक32_t bios_generic_id = gpu_id_from_bios_object_id(bios_object_id);

	क्रमागत generic_id id;

	चयन (bios_generic_id) अणु
	हाल GENERIC_OBJECT_ID_MXM_OPM:
		id = GENERIC_ID_MXM_OPM;
		अवरोध;
	हाल GENERIC_OBJECT_ID_GLSYNC:
		id = GENERIC_ID_GLSYNC;
		अवरोध;
	हाल GENERIC_OBJECT_ID_STEREO_PIN:
		id = GENERIC_ID_STEREO;
		अवरोध;
	शेष:
		id = GENERIC_ID_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस id;
पूर्ण

अटल uपूर्णांक32_t id_from_bios_object_id(क्रमागत object_type type,
	uपूर्णांक32_t bios_object_id)
अणु
	चयन (type) अणु
	हाल OBJECT_TYPE_GPU:
		वापस gpu_id_from_bios_object_id(bios_object_id);
	हाल OBJECT_TYPE_ENCODER:
		वापस (uपूर्णांक32_t)encoder_id_from_bios_object_id(bios_object_id);
	हाल OBJECT_TYPE_CONNECTOR:
		वापस (uपूर्णांक32_t)connector_id_from_bios_object_id(
				bios_object_id);
	हाल OBJECT_TYPE_GENERIC:
		वापस generic_id_from_bios_object_id(bios_object_id);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

काष्ठा graphics_object_id object_id_from_bios_object_id(uपूर्णांक32_t bios_object_id)
अणु
	क्रमागत object_type type;
	क्रमागत object_क्रमागत_id क्रमागत_id;
	काष्ठा graphics_object_id go_id = अणु 0 पूर्ण;

	type = object_type_from_bios_object_id(bios_object_id);

	अगर (OBJECT_TYPE_UNKNOWN == type)
		वापस go_id;

	क्रमागत_id = क्रमागत_id_from_bios_object_id(bios_object_id);

	अगर (ENUM_ID_UNKNOWN == क्रमागत_id)
		वापस go_id;

	go_id = dal_graphics_object_id_init(
			id_from_bios_object_id(type, bios_object_id), क्रमागत_id, type);

	वापस go_id;
पूर्ण


