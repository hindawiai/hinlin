<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#घोषणा __INLINE_INPUT_SYSTEM__
#समावेश "input_system.h"
#समावेश "assert_support.h"
#समावेश "ia_css_isys.h"
#समावेश "ia_css_irq.h"
#समावेश "sh_css_internal.h"

#अगर !defined(ISP2401)
व्योम ia_css_isys_rx_enable_all_पूर्णांकerrupts(क्रमागत mipi_port_id port)
अणु
	hrt_data bits = receiver_port_reg_load(RX0_ID,
					       port,
					       _HRT_CSS_RECEIVER_IRQ_ENABLE_REG_IDX);

	bits |= (1U << _HRT_CSS_RECEIVER_IRQ_OVERRUN_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_INIT_TIMEOUT_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_ENTRY_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_EXIT_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_SOT_HS_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_SOT_SYNC_HS_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_CONTROL_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_DOUBLE_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_CORRECTED_BIT) |
		/*(1U << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_NO_CORRECTION_BIT) | */
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_CRC_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_ID_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_SYNC_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_DATA_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_DATA_TIMEOUT_BIT) |
		(1U << _HRT_CSS_RECEIVER_IRQ_ERR_ESCAPE_BIT);
	/*(1U << _HRT_CSS_RECEIVER_IRQ_ERR_LINE_SYNC_BIT); */

	receiver_port_reg_store(RX0_ID,
				port,
				_HRT_CSS_RECEIVER_IRQ_ENABLE_REG_IDX, bits);

	/*
	 * The CSI is nested पूर्णांकo the Iunit IRQ's
	 */
	ia_css_irq_enable(IA_CSS_IRQ_INFO_CSS_RECEIVER_ERROR, true);

	वापस;
पूर्ण

/* This function converts between the क्रमागत used on the CSS API and the
 * पूर्णांकernal DLI क्रमागत type.
 * We करो not use an array क्रम this since we cannot use named array
 * initializers in Winकरोws. Without that there is no easy way to guarantee
 * that the array values would be in the correct order.
 * */
क्रमागत mipi_port_id ia_css_isys_port_to_mipi_port(क्रमागत mipi_port_id api_port)
अणु
	/* In this module the validity of the inptu variable should
	 * have been checked alपढ़ोy, so we करो not check क्रम erroneous
	 * values. */
	क्रमागत mipi_port_id port = MIPI_PORT0_ID;

	अगर (api_port == MIPI_PORT1_ID)
		port = MIPI_PORT1_ID;
	अन्यथा अगर (api_port == MIPI_PORT2_ID)
		port = MIPI_PORT2_ID;

	वापस port;
पूर्ण

अचिन्हित पूर्णांक ia_css_isys_rx_get_पूर्णांकerrupt_reg(क्रमागत mipi_port_id port)
अणु
	वापस receiver_port_reg_load(RX0_ID,
				      port,
				      _HRT_CSS_RECEIVER_IRQ_STATUS_REG_IDX);
पूर्ण

व्योम ia_css_rx_get_irq_info(अचिन्हित पूर्णांक *irq_infos)
अणु
	ia_css_rx_port_get_irq_info(MIPI_PORT1_ID, irq_infos);
पूर्ण

व्योम ia_css_rx_port_get_irq_info(क्रमागत mipi_port_id api_port,
				 अचिन्हित पूर्णांक *irq_infos)
अणु
	क्रमागत mipi_port_id port = ia_css_isys_port_to_mipi_port(api_port);

	ia_css_isys_rx_get_irq_info(port, irq_infos);
पूर्ण

व्योम ia_css_isys_rx_get_irq_info(क्रमागत mipi_port_id port,
				 अचिन्हित पूर्णांक *irq_infos)
अणु
	अचिन्हित पूर्णांक bits;

	निश्चित(irq_infos);
	bits = ia_css_isys_rx_get_पूर्णांकerrupt_reg(port);
	*irq_infos = ia_css_isys_rx_translate_irq_infos(bits);
पूर्ण

/* Translate रेजिस्टर bits to CSS API क्रमागत mask */
अचिन्हित पूर्णांक ia_css_isys_rx_translate_irq_infos(अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक infos = 0;

	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_OVERRUN_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_BUFFER_OVERRUN;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_INIT_TIMEOUT_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_INIT_TIMEOUT;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_ENTRY_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ENTER_SLEEP_MODE;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_EXIT_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_EXIT_SLEEP_MODE;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_CORRECTED_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ECC_CORRECTED;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_SOT_HS_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_SOT;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_SOT_SYNC_HS_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_SOT_SYNC;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_CONTROL_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_CONTROL;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_DOUBLE_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_ECC_DOUBLE;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_CRC_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_CRC;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_ID_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ID;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_SYNC_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_FRAME_SYNC;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_DATA_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_FRAME_DATA;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_DATA_TIMEOUT_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_DATA_TIMEOUT;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_ESCAPE_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ESC;
	अगर (bits & (1U << _HRT_CSS_RECEIVER_IRQ_ERR_LINE_SYNC_BIT))
		infos |= IA_CSS_RX_IRQ_INFO_ERR_LINE_SYNC;

	वापस infos;
पूर्ण

व्योम ia_css_rx_clear_irq_info(अचिन्हित पूर्णांक irq_infos)
अणु
	ia_css_rx_port_clear_irq_info(MIPI_PORT1_ID, irq_infos);
पूर्ण

व्योम ia_css_rx_port_clear_irq_info(क्रमागत mipi_port_id api_port,
				   अचिन्हित पूर्णांक irq_infos)
अणु
	क्रमागत mipi_port_id port = ia_css_isys_port_to_mipi_port(api_port);

	ia_css_isys_rx_clear_irq_info(port, irq_infos);
पूर्ण

व्योम ia_css_isys_rx_clear_irq_info(क्रमागत mipi_port_id port,
				   अचिन्हित पूर्णांक irq_infos)
अणु
	hrt_data bits = receiver_port_reg_load(RX0_ID,
					       port,
					       _HRT_CSS_RECEIVER_IRQ_ENABLE_REG_IDX);

	/* MW: Why करो we remap the receiver biपंचांगap */
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_BUFFER_OVERRUN)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_OVERRUN_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_INIT_TIMEOUT)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_INIT_TIMEOUT_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ENTER_SLEEP_MODE)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_ENTRY_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_EXIT_SLEEP_MODE)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_SLEEP_MODE_EXIT_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ECC_CORRECTED)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_CORRECTED_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_SOT)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_SOT_HS_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_SOT_SYNC)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_SOT_SYNC_HS_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_CONTROL)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_CONTROL_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_ECC_DOUBLE)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_ECC_DOUBLE_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_CRC)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_CRC_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ID)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_ID_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_FRAME_SYNC)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_SYNC_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_FRAME_DATA)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_FRAME_DATA_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_DATA_TIMEOUT)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_DATA_TIMEOUT_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_UNKNOWN_ESC)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_ESCAPE_BIT;
	अगर (irq_infos & IA_CSS_RX_IRQ_INFO_ERR_LINE_SYNC)
		bits |= 1U << _HRT_CSS_RECEIVER_IRQ_ERR_LINE_SYNC_BIT;

	receiver_port_reg_store(RX0_ID,
				port,
				_HRT_CSS_RECEIVER_IRQ_ENABLE_REG_IDX, bits);

	वापस;
पूर्ण
#पूर्ण_अगर /* #अगर !defined(ISP2401) */

पूर्णांक ia_css_isys_convert_stream_क्रमmat_to_mipi_क्रमmat(
    क्रमागत atomisp_input_क्रमmat input_क्रमmat,
    mipi_predictor_t compression,
    अचिन्हित पूर्णांक *fmt_type)
अणु
	निश्चित(fmt_type);
	/*
	 * Custom (user defined) modes. Used क्रम compressed
	 * MIPI transfers
	 *
	 * Checkpatch thinks the indent beक्रमe "if" is suspect
	 * I think the only suspect part is the missing "else"
	 * because of the वापस.
	 */
	अगर (compression != MIPI_PREDICTOR_NONE) अणु
		चयन (input_क्रमmat) अणु
		हाल ATOMISP_INPUT_FORMAT_RAW_6:
			*fmt_type = 6;
			अवरोध;
		हाल ATOMISP_INPUT_FORMAT_RAW_7:
			*fmt_type = 7;
			अवरोध;
		हाल ATOMISP_INPUT_FORMAT_RAW_8:
			*fmt_type = 8;
			अवरोध;
		हाल ATOMISP_INPUT_FORMAT_RAW_10:
			*fmt_type = 10;
			अवरोध;
		हाल ATOMISP_INPUT_FORMAT_RAW_12:
			*fmt_type = 12;
			अवरोध;
		हाल ATOMISP_INPUT_FORMAT_RAW_14:
			*fmt_type = 14;
			अवरोध;
		हाल ATOMISP_INPUT_FORMAT_RAW_16:
			*fmt_type = 16;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण
	/*
	 * This mapping comes from the Arasan CSS function spec
	 * (CSS_func_spec1.08_ahb_sep29_08.pdf).
	 *
	 * MW: For some reason the mapping is not 1-to-1
	 */
	चयन (input_क्रमmat) अणु
	हाल ATOMISP_INPUT_FORMAT_RGB_888:
		*fmt_type = MIPI_FORMAT_RGB888;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_555:
		*fmt_type = MIPI_FORMAT_RGB555;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_444:
		*fmt_type = MIPI_FORMAT_RGB444;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_565:
		*fmt_type = MIPI_FORMAT_RGB565;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_666:
		*fmt_type = MIPI_FORMAT_RGB666;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_8:
		*fmt_type = MIPI_FORMAT_RAW8;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_10:
		*fmt_type = MIPI_FORMAT_RAW10;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_6:
		*fmt_type = MIPI_FORMAT_RAW6;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_7:
		*fmt_type = MIPI_FORMAT_RAW7;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_12:
		*fmt_type = MIPI_FORMAT_RAW12;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_14:
		*fmt_type = MIPI_FORMAT_RAW14;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:
		*fmt_type = MIPI_FORMAT_YUV420_8;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_10:
		*fmt_type = MIPI_FORMAT_YUV420_10;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:
		*fmt_type = MIPI_FORMAT_YUV422_8;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV422_10:
		*fmt_type = MIPI_FORMAT_YUV422_10;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY:
		*fmt_type = MIPI_FORMAT_YUV420_8_LEGACY;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_EMBEDDED:
		*fmt_type = MIPI_FORMAT_EMBEDDED;
		अवरोध;
#अगर_अघोषित ISP2401
	हाल ATOMISP_INPUT_FORMAT_RAW_16:
		/* This is not specअगरied by Arasan, so we use
		 * 17 क्रम now.
		 */
		*fmt_type = MIPI_FORMAT_RAW16;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_BINARY_8:
		*fmt_type = MIPI_FORMAT_BINARY_8;
		अवरोध;
#अन्यथा
	हाल ATOMISP_INPUT_FORMAT_USER_DEF1:
		*fmt_type = MIPI_FORMAT_CUSTOM0;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_USER_DEF2:
		*fmt_type = MIPI_FORMAT_CUSTOM1;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_USER_DEF3:
		*fmt_type = MIPI_FORMAT_CUSTOM2;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_USER_DEF4:
		*fmt_type = MIPI_FORMAT_CUSTOM3;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_USER_DEF5:
		*fmt_type = MIPI_FORMAT_CUSTOM4;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_USER_DEF6:
		*fmt_type = MIPI_FORMAT_CUSTOM5;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_USER_DEF7:
		*fmt_type = MIPI_FORMAT_CUSTOM6;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_USER_DEF8:
		*fmt_type = MIPI_FORMAT_CUSTOM7;
		अवरोध;
#पूर्ण_अगर

	हाल ATOMISP_INPUT_FORMAT_YUV420_16:
	हाल ATOMISP_INPUT_FORMAT_YUV422_16:
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#अगर defined(ISP2401)
अटल mipi_predictor_t sh_css_csi2_compression_type_2_mipi_predictor(
    क्रमागत ia_css_csi2_compression_type type)
अणु
	mipi_predictor_t predictor = MIPI_PREDICTOR_NONE;

	चयन (type) अणु
	हाल IA_CSS_CSI2_COMPRESSION_TYPE_1:
		predictor = MIPI_PREDICTOR_TYPE1 - 1;
		अवरोध;
	हाल IA_CSS_CSI2_COMPRESSION_TYPE_2:
		predictor = MIPI_PREDICTOR_TYPE2 - 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस predictor;
पूर्ण

पूर्णांक ia_css_isys_convert_compressed_क्रमmat(
    काष्ठा ia_css_csi2_compression *comp,
    काष्ठा isp2401_input_प्रणाली_cfg_s *cfg)
अणु
	पूर्णांक err = 0;

	निश्चित(comp);
	निश्चित(cfg);

	अगर (comp->type != IA_CSS_CSI2_COMPRESSION_TYPE_NONE) अणु
		/* compression रेजिस्टर bit slicing
		4 bit क्रम each user defined data type
			3 bit indicate compression scheme
				000 No compression
				001 10-6-10
				010 10-7-10
				011 10-8-10
				100 12-6-12
				101 12-6-12
				100 12-7-12
				110 12-8-12
			1 bit indicate predictor
		*/
		अगर (comp->uncompressed_bits_per_pixel == UNCOMPRESSED_BITS_PER_PIXEL_10) अणु
			चयन (comp->compressed_bits_per_pixel) अणु
			हाल COMPRESSED_BITS_PER_PIXEL_6:
				cfg->csi_port_attr.comp_scheme = MIPI_COMPRESSOR_10_6_10;
				अवरोध;
			हाल COMPRESSED_BITS_PER_PIXEL_7:
				cfg->csi_port_attr.comp_scheme = MIPI_COMPRESSOR_10_7_10;
				अवरोध;
			हाल COMPRESSED_BITS_PER_PIXEL_8:
				cfg->csi_port_attr.comp_scheme = MIPI_COMPRESSOR_10_8_10;
				अवरोध;
			शेष:
				err = -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (comp->uncompressed_bits_per_pixel ==
			   UNCOMPRESSED_BITS_PER_PIXEL_12) अणु
			चयन (comp->compressed_bits_per_pixel) अणु
			हाल COMPRESSED_BITS_PER_PIXEL_6:
				cfg->csi_port_attr.comp_scheme = MIPI_COMPRESSOR_12_6_12;
				अवरोध;
			हाल COMPRESSED_BITS_PER_PIXEL_7:
				cfg->csi_port_attr.comp_scheme = MIPI_COMPRESSOR_12_7_12;
				अवरोध;
			हाल COMPRESSED_BITS_PER_PIXEL_8:
				cfg->csi_port_attr.comp_scheme = MIPI_COMPRESSOR_12_8_12;
				अवरोध;
			शेष:
				err = -EINVAL;
			पूर्ण
		पूर्ण अन्यथा
			err = -EINVAL;
		cfg->csi_port_attr.comp_predictor =
		    sh_css_csi2_compression_type_2_mipi_predictor(comp->type);
		cfg->csi_port_attr.comp_enable = true;
	पूर्ण अन्यथा /* No compression */
		cfg->csi_port_attr.comp_enable = false;
	वापस err;
पूर्ण

अचिन्हित पूर्णांक ia_css_csi2_calculate_input_प्रणाली_alignment(
    क्रमागत atomisp_input_क्रमmat fmt_type)
अणु
	अचिन्हित पूर्णांक memory_alignment_in_bytes = HIVE_ISP_DDR_WORD_BYTES;

	चयन (fmt_type) अणु
	हाल ATOMISP_INPUT_FORMAT_RAW_6:
	हाल ATOMISP_INPUT_FORMAT_RAW_7:
	हाल ATOMISP_INPUT_FORMAT_RAW_8:
	हाल ATOMISP_INPUT_FORMAT_RAW_10:
	हाल ATOMISP_INPUT_FORMAT_RAW_12:
	हाल ATOMISP_INPUT_FORMAT_RAW_14:
		memory_alignment_in_bytes = 2 * ISP_VEC_NELEMS;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF1:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF2:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF3:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF4:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF5:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF6:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF7:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF8:
		/* Planar YUV क्रमmats need to have all planes aligned, this means
		 * द्विगुन the alignment क्रम the Y plane अगर the horizontal decimation is 2. */
		memory_alignment_in_bytes = 2 * HIVE_ISP_DDR_WORD_BYTES;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_EMBEDDED:
	शेष:
		memory_alignment_in_bytes = HIVE_ISP_DDR_WORD_BYTES;
		अवरोध;
	पूर्ण
	वापस memory_alignment_in_bytes;
पूर्ण

#पूर्ण_अगर

#अगर !defined(ISP2401)
व्योम ia_css_isys_rx_configure(स्थिर rx_cfg_t *config,
			      स्थिर क्रमागत ia_css_input_mode input_mode)
अणु
	bool port_enabled[N_MIPI_PORT_ID];
	bool any_port_enabled = false;
	क्रमागत mipi_port_id port;

	अगर ((!config)
	    || (config->mode >= N_RX_MODE)
	    || (config->port >= N_MIPI_PORT_ID)) अणु
		निश्चित(0);
		वापस;
	पूर्ण
	क्रम (port = (क्रमागत mipi_port_id)0; port < N_MIPI_PORT_ID; port++) अणु
		अगर (is_receiver_port_enabled(RX0_ID, port))
			any_port_enabled = true;
	पूर्ण
	/* AM: Check whether this is a problem with multiple
	 * streams. MS: This is the हाल. */

	port = config->port;
	receiver_port_enable(RX0_ID, port, false);

	port = config->port;

	/* AM: Check whether this is a problem with multiple streams. */
	अगर (MIPI_PORT_LANES[config->mode][port] != MIPI_0LANE_CFG) अणु
		receiver_port_reg_store(RX0_ID, port,
					_HRT_CSS_RECEIVER_FUNC_PROG_REG_IDX,
					config->समयout);
		receiver_port_reg_store(RX0_ID, port,
					_HRT_CSS_RECEIVER_2400_INIT_COUNT_REG_IDX,
					config->initcount);
		receiver_port_reg_store(RX0_ID, port,
					_HRT_CSS_RECEIVER_2400_SYNC_COUNT_REG_IDX,
					config->synccount);
		receiver_port_reg_store(RX0_ID, port,
					_HRT_CSS_RECEIVER_2400_RX_COUNT_REG_IDX,
					config->rxcount);

		port_enabled[port] = true;

		अगर (input_mode != IA_CSS_INPUT_MODE_BUFFERED_SENSOR) अणु
			/* MW: A bit of a hack, straight wiring of the capture
			 * units,assuming they are linearly क्रमागतerated. */
			input_प्रणाली_sub_प्रणाली_reg_store(INPUT_SYSTEM0_ID,
							  GPREGS_UNIT0_ID,
							  HIVE_ISYS_GPREG_MULTICAST_A_IDX
							  + (अचिन्हित पूर्णांक)port,
							  INPUT_SYSTEM_CSI_BACKEND);
			/* MW: Like the पूर्णांकegration test example we overwite,
			 * the GPREG_MUX रेजिस्टर */
			input_प्रणाली_sub_प्रणाली_reg_store(INPUT_SYSTEM0_ID,
							  GPREGS_UNIT0_ID,
							  HIVE_ISYS_GPREG_MUX_IDX,
							  (input_प्रणाली_multiplex_t)port);
		पूर्ण अन्यथा अणु
			/*
			 * AM: A bit of a hack, wiring the input प्रणाली.
			 */
			input_प्रणाली_sub_प्रणाली_reg_store(INPUT_SYSTEM0_ID,
							  GPREGS_UNIT0_ID,
							  HIVE_ISYS_GPREG_MULTICAST_A_IDX
							  + (अचिन्हित पूर्णांक)port,
							  INPUT_SYSTEM_INPUT_BUFFER);
			input_प्रणाली_sub_प्रणाली_reg_store(INPUT_SYSTEM0_ID,
							  GPREGS_UNIT0_ID,
							  HIVE_ISYS_GPREG_MUX_IDX,
							  INPUT_SYSTEM_ACQUISITION_UNIT);
		पूर्ण
	पूर्ण
	/*
	 * The 2ppc is shared क्रम all ports, so we cannot
	 * disable->configure->enable inभागidual ports
	 */
	/* AM: Check whether this is a problem with multiple streams. */
	/* MS: 2ppc should be a property per binary and should be
	 * enabled/disabled per binary.
	 * Currently it is implemented as a प्रणाली wide setting due
	 * to efक्रमt and risks. */
	अगर (!any_port_enabled) अणु
		receiver_reg_store(RX0_ID,
				   _HRT_CSS_RECEIVER_TWO_PIXEL_EN_REG_IDX,
				   config->is_two_ppc);
		receiver_reg_store(RX0_ID, _HRT_CSS_RECEIVER_BE_TWO_PPC_REG_IDX,
				   config->is_two_ppc);
	पूर्ण
	receiver_port_enable(RX0_ID, port, true);
	/* TODO: JB: need to add the beneath used define to mizuchi */
	/* sh_css_sw_hive_isp_css_2400_प्रणाली_20121224_0125\css
	 *                      \hrt\input_प्रणाली_defs.h
	 * #घोषणा INPUT_SYSTEM_CSI_RECEIVER_SELECT_BACKENG 0X207
	 */
	/* TODO: need better name क्रम define
	 * input_प्रणाली_reg_store(INPUT_SYSTEM0_ID,
	 *                INPUT_SYSTEM_CSI_RECEIVER_SELECT_BACKENG, 1);
	 */
	input_प्रणाली_reg_store(INPUT_SYSTEM0_ID, 0x207, 1);

	वापस;
पूर्ण

व्योम ia_css_isys_rx_disable(व्योम)
अणु
	क्रमागत mipi_port_id port;

	क्रम (port = (क्रमागत mipi_port_id)0; port < N_MIPI_PORT_ID; port++) अणु
		receiver_port_reg_store(RX0_ID, port,
					_HRT_CSS_RECEIVER_DEVICE_READY_REG_IDX,
					false);
	पूर्ण
	वापस;
पूर्ण
#पूर्ण_अगर /* अगर !defined(ISP2401) */
