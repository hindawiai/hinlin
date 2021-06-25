<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
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

#समावेश <linux/माला.स> /* क्रम स_नकल() */

#समावेश "system_global.h"

#अगर_घोषित ISP2401

#समावेश "ia_css_isys.h"
#समावेश "ia_css_debug.h"
#समावेश "math_support.h"
#समावेश "virtual_isys.h"
#समावेश "isp.h"
#समावेश "sh_css_defs.h"

/*************************************************
 *
 * Forwarded Declaration
 *
 *************************************************/

अटल bool create_input_प्रणाली_channel(
    isp2401_input_प्रणाली_cfg_t	*cfg,
    bool			metadata,
    input_प्रणाली_channel_t	*channel);

अटल व्योम destroy_input_प्रणाली_channel(
    input_प्रणाली_channel_t	*channel);

अटल bool create_input_प्रणाली_input_port(
    isp2401_input_प्रणाली_cfg_t		*cfg,
    input_प्रणाली_input_port_t	*input_port);

अटल व्योम destroy_input_प्रणाली_input_port(
    input_प्रणाली_input_port_t	*input_port);

अटल bool calculate_input_प्रणाली_channel_cfg(
    input_प्रणाली_channel_t		*channel,
    input_प्रणाली_input_port_t	*input_port,
    isp2401_input_प्रणाली_cfg_t		*isys_cfg,
    input_प्रणाली_channel_cfg_t	*channel_cfg,
    bool metadata);

अटल bool calculate_input_प्रणाली_input_port_cfg(
    input_प्रणाली_channel_t		*channel,
    input_प्रणाली_input_port_t	*input_port,
    isp2401_input_प्रणाली_cfg_t		*isys_cfg,
    input_प्रणाली_input_port_cfg_t	*input_port_cfg);

अटल bool acquire_sid(
    stream2mmio_ID_t	stream2mmio,
    stream2mmio_sid_ID_t	*sid);

अटल व्योम release_sid(
    stream2mmio_ID_t	stream2mmio,
    stream2mmio_sid_ID_t	*sid);

अटल bool acquire_ib_buffer(
    s32 bits_per_pixel,
    s32 pixels_per_line,
    s32 lines_per_frame,
    s32 align_in_bytes,
    bool online,
    isp2401_ib_buffer_t *buf);

अटल व्योम release_ib_buffer(
    isp2401_ib_buffer_t *buf);

अटल bool acquire_dma_channel(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channel	*channel);

अटल व्योम release_dma_channel(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channel	*channel);

अटल bool acquire_be_lut_entry(
    csi_rx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_rx_backend_lut_entry_t	*entry);

अटल व्योम release_be_lut_entry(
    csi_rx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_rx_backend_lut_entry_t	*entry);

अटल bool calculate_tpg_cfg(
    input_प्रणाली_channel_t		*channel,
    input_प्रणाली_input_port_t	*input_port,
    isp2401_input_प्रणाली_cfg_t		*isys_cfg,
    pixelgen_tpg_cfg_t		*cfg);

अटल bool calculate_prbs_cfg(
    input_प्रणाली_channel_t		*channel,
    input_प्रणाली_input_port_t	*input_port,
    isp2401_input_प्रणाली_cfg_t		*isys_cfg,
    pixelgen_prbs_cfg_t		*cfg);

अटल bool calculate_fe_cfg(
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    csi_rx_frontend_cfg_t		*cfg);

अटल bool calculate_be_cfg(
    स्थिर input_प्रणाली_input_port_t	*input_port,
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    bool				metadata,
    csi_rx_backend_cfg_t		*cfg);

अटल bool calculate_stream2mmio_cfg(
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    bool				metadata,
    stream2mmio_cfg_t		*cfg);

अटल bool calculate_ibuf_ctrl_cfg(
    स्थिर input_प्रणाली_channel_t	*channel,
    स्थिर input_प्रणाली_input_port_t	*input_port,
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    ibuf_ctrl_cfg_t			*cfg);

अटल bool calculate_isys2401_dma_cfg(
    स्थिर input_प्रणाली_channel_t	*channel,
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    isys2401_dma_cfg_t		*cfg);

अटल bool calculate_isys2401_dma_port_cfg(
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    bool				raw_packed,
    bool				metadata,
    isys2401_dma_port_cfg_t		*cfg);

अटल csi_mipi_packet_type_t get_csi_mipi_packet_type(
    पूर्णांक32_t data_type);

अटल पूर्णांक32_t calculate_stride(
    s32 bits_per_pixel,
    s32 pixels_per_line,
    bool	raw_packed,
    पूर्णांक32_t	align_in_bytes);

/* end of Forwarded Declaration */

/**************************************************
 *
 * Public Methods
 *
 **************************************************/
ia_css_isys_error_t ia_css_isys_stream_create(
    ia_css_isys_descr_t	*isys_stream_descr,
    ia_css_isys_stream_h	isys_stream,
    uपूर्णांक32_t isys_stream_id)
अणु
	ia_css_isys_error_t rc;

	अगर (!isys_stream_descr || !isys_stream ||
	    isys_stream_id >= SH_CSS_MAX_ISYS_CHANNEL_NODES)
		वापस	false;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_isys_stream_create() enter:\n");

	/*Reset isys_stream to 0*/
	स_रखो(isys_stream, 0, माप(*isys_stream));
	isys_stream->enable_metadata = isys_stream_descr->metadata.enable;
	isys_stream->id = isys_stream_id;

	isys_stream->linked_isys_stream_id = isys_stream_descr->linked_isys_stream_id;
	rc = create_input_प्रणाली_input_port(isys_stream_descr,
					    &isys_stream->input_port);
	अगर (!rc)
		वापस false;

	rc = create_input_प्रणाली_channel(isys_stream_descr, false,
					 &isys_stream->channel);
	अगर (!rc) अणु
		destroy_input_प्रणाली_input_port(&isys_stream->input_port);
		वापस false;
	पूर्ण

#अगर_घोषित ISP2401
	/*
	 * Early polling is required क्रम बारtamp accuracy in certain cause.
	 * The ISYS HW polling is started on
	 * ia_css_isys_stream_capture_indication() instead of
	 * ia_css_pipeline_sp_रुको_क्रम_isys_stream_N() as isp processing of
	 * capture takes दीर्घer than getting an ISYS frame
	 */
	isys_stream->polling_mode = isys_stream_descr->polling_mode;

#पूर्ण_अगर
	/* create metadata channel */
	अगर (isys_stream_descr->metadata.enable) अणु
		rc = create_input_प्रणाली_channel(isys_stream_descr, true,
						 &isys_stream->md_channel);
		अगर (!rc) अणु
			destroy_input_प्रणाली_input_port(&isys_stream->input_port);
			destroy_input_प्रणाली_channel(&isys_stream->channel);
			वापस false;
		पूर्ण
	पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_isys_stream_create() leave:\n");

	वापस true;
पूर्ण

व्योम ia_css_isys_stream_destroy(
    ia_css_isys_stream_h	isys_stream)
अणु
	destroy_input_प्रणाली_input_port(&isys_stream->input_port);
	destroy_input_प्रणाली_channel(&isys_stream->channel);
	अगर (isys_stream->enable_metadata) अणु
		/* Destroy metadata channel only अगर its allocated*/
		destroy_input_प्रणाली_channel(&isys_stream->md_channel);
	पूर्ण
पूर्ण

ia_css_isys_error_t ia_css_isys_stream_calculate_cfg(
    ia_css_isys_stream_h		isys_stream,
    ia_css_isys_descr_t		*isys_stream_descr,
    ia_css_isys_stream_cfg_t	*isys_stream_cfg)
अणु
	ia_css_isys_error_t rc;

	अगर (!isys_stream_cfg		||
	    !isys_stream_descr	||
	    !isys_stream)
		वापस false;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_isys_stream_calculate_cfg() enter:\n");

	rc  = calculate_input_प्रणाली_channel_cfg(
		  &isys_stream->channel,
		  &isys_stream->input_port,
		  isys_stream_descr,
		  &isys_stream_cfg->channel_cfg,
		  false);
	अगर (!rc)
		वापस false;

	/* configure metadata channel */
	अगर (isys_stream_descr->metadata.enable) अणु
		isys_stream_cfg->enable_metadata = true;
		rc  = calculate_input_प्रणाली_channel_cfg(
			  &isys_stream->md_channel,
			  &isys_stream->input_port,
			  isys_stream_descr,
			  &isys_stream_cfg->md_channel_cfg,
			  true);
		अगर (!rc)
			वापस false;
	पूर्ण

	rc = calculate_input_प्रणाली_input_port_cfg(
		 &isys_stream->channel,
		 &isys_stream->input_port,
		 isys_stream_descr,
		 &isys_stream_cfg->input_port_cfg);
	अगर (!rc)
		वापस false;

	isys_stream->valid = 1;
	isys_stream_cfg->valid = 1;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_isys_stream_calculate_cfg() leave:\n");
	वापस rc;
पूर्ण

/* end of Public Methods */

/**************************************************
 *
 * Private Methods
 *
 **************************************************/
अटल bool create_input_प्रणाली_channel(
    isp2401_input_प्रणाली_cfg_t	*cfg,
    bool			metadata,
    input_प्रणाली_channel_t	*me)
अणु
	bool rc = true;

	me->dma_id = ISYS2401_DMA0_ID;

	चयन (cfg->input_port_id) अणु
	हाल INPUT_SYSTEM_CSI_PORT0_ID:
	हाल INPUT_SYSTEM_PIXELGEN_PORT0_ID:
		me->stream2mmio_id = STREAM2MMIO0_ID;
		me->ibuf_ctrl_id = IBUF_CTRL0_ID;
		अवरोध;

	हाल INPUT_SYSTEM_CSI_PORT1_ID:
	हाल INPUT_SYSTEM_PIXELGEN_PORT1_ID:
		me->stream2mmio_id = STREAM2MMIO1_ID;
		me->ibuf_ctrl_id = IBUF_CTRL1_ID;
		अवरोध;

	हाल INPUT_SYSTEM_CSI_PORT2_ID:
	हाल INPUT_SYSTEM_PIXELGEN_PORT2_ID:
		me->stream2mmio_id = STREAM2MMIO2_ID;
		me->ibuf_ctrl_id = IBUF_CTRL2_ID;
		अवरोध;
	शेष:
		rc = false;
		अवरोध;
	पूर्ण

	अगर (!rc)
		वापस false;

	अगर (!acquire_sid(me->stream2mmio_id, &me->stream2mmio_sid_id)) अणु
		वापस false;
	पूर्ण

	अगर (!acquire_ib_buffer(
		metadata ? cfg->metadata.bits_per_pixel :
		cfg->input_port_resolution.bits_per_pixel,
		metadata ? cfg->metadata.pixels_per_line :
		cfg->input_port_resolution.pixels_per_line,
		metadata ? cfg->metadata.lines_per_frame :
		cfg->input_port_resolution.lines_per_frame,
		metadata ? cfg->metadata.align_req_in_bytes :
		cfg->input_port_resolution.align_req_in_bytes,
		cfg->online,
		&me->ib_buffer)) अणु
		release_sid(me->stream2mmio_id, &me->stream2mmio_sid_id);
		वापस false;
	पूर्ण

	अगर (!acquire_dma_channel(me->dma_id, &me->dma_channel)) अणु
		release_sid(me->stream2mmio_id, &me->stream2mmio_sid_id);
		release_ib_buffer(&me->ib_buffer);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम destroy_input_प्रणाली_channel(
    input_प्रणाली_channel_t	*me)
अणु
	release_sid(me->stream2mmio_id,
		    &me->stream2mmio_sid_id);

	release_ib_buffer(&me->ib_buffer);

	release_dma_channel(me->dma_id, &me->dma_channel);
पूर्ण

अटल bool create_input_प्रणाली_input_port(
    isp2401_input_प्रणाली_cfg_t		*cfg,
    input_प्रणाली_input_port_t	*me)
अणु
	csi_mipi_packet_type_t packet_type;
	bool rc = true;

	चयन (cfg->input_port_id) अणु
	हाल INPUT_SYSTEM_CSI_PORT0_ID:
		me->csi_rx.frontend_id = CSI_RX_FRONTEND0_ID;
		me->csi_rx.backend_id = CSI_RX_BACKEND0_ID;

		packet_type = get_csi_mipi_packet_type(cfg->csi_port_attr.fmt_type);
		me->csi_rx.packet_type = packet_type;

		rc = acquire_be_lut_entry(
			 me->csi_rx.backend_id,
			 packet_type,
			 &me->csi_rx.backend_lut_entry);
		अवरोध;
	हाल INPUT_SYSTEM_PIXELGEN_PORT0_ID:
		me->pixelgen.pixelgen_id = PIXELGEN0_ID;
		अवरोध;
	हाल INPUT_SYSTEM_CSI_PORT1_ID:
		me->csi_rx.frontend_id = CSI_RX_FRONTEND1_ID;
		me->csi_rx.backend_id = CSI_RX_BACKEND1_ID;

		packet_type = get_csi_mipi_packet_type(cfg->csi_port_attr.fmt_type);
		me->csi_rx.packet_type = packet_type;

		rc = acquire_be_lut_entry(
			 me->csi_rx.backend_id,
			 packet_type,
			 &me->csi_rx.backend_lut_entry);
		अवरोध;
	हाल INPUT_SYSTEM_PIXELGEN_PORT1_ID:
		me->pixelgen.pixelgen_id = PIXELGEN1_ID;

		अवरोध;
	हाल INPUT_SYSTEM_CSI_PORT2_ID:
		me->csi_rx.frontend_id = CSI_RX_FRONTEND2_ID;
		me->csi_rx.backend_id = CSI_RX_BACKEND2_ID;

		packet_type = get_csi_mipi_packet_type(cfg->csi_port_attr.fmt_type);
		me->csi_rx.packet_type = packet_type;

		rc = acquire_be_lut_entry(
			 me->csi_rx.backend_id,
			 packet_type,
			 &me->csi_rx.backend_lut_entry);
		अवरोध;
	हाल INPUT_SYSTEM_PIXELGEN_PORT2_ID:
		me->pixelgen.pixelgen_id = PIXELGEN2_ID;
		अवरोध;
	शेष:
		rc = false;
		अवरोध;
	पूर्ण

	me->source_type = cfg->mode;

	/* क्रम metadata */
	me->metadata.packet_type = CSI_MIPI_PACKET_TYPE_UNDEFINED;
	अगर (rc && cfg->metadata.enable) अणु
		me->metadata.packet_type = get_csi_mipi_packet_type(
					       cfg->metadata.fmt_type);
		rc = acquire_be_lut_entry(
			 me->csi_rx.backend_id,
			 me->metadata.packet_type,
			 &me->metadata.backend_lut_entry);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम destroy_input_प्रणाली_input_port(
    input_प्रणाली_input_port_t	*me)
अणु
	अगर (me->source_type == INPUT_SYSTEM_SOURCE_TYPE_SENSOR) अणु
		release_be_lut_entry(
		    me->csi_rx.backend_id,
		    me->csi_rx.packet_type,
		    &me->csi_rx.backend_lut_entry);
	पूर्ण

	अगर (me->metadata.packet_type != CSI_MIPI_PACKET_TYPE_UNDEFINED) अणु
		/*Free the backend lut allocated क्रम metadata*/
		release_be_lut_entry(
		    me->csi_rx.backend_id,
		    me->metadata.packet_type,
		    &me->metadata.backend_lut_entry);
	पूर्ण
पूर्ण

अटल bool calculate_input_प्रणाली_channel_cfg(
    input_प्रणाली_channel_t		*channel,
    input_प्रणाली_input_port_t	*input_port,
    isp2401_input_प्रणाली_cfg_t		*isys_cfg,
    input_प्रणाली_channel_cfg_t	*channel_cfg,
    bool metadata)
अणु
	bool rc;

	rc = calculate_stream2mmio_cfg(isys_cfg, metadata,
				       &channel_cfg->stream2mmio_cfg);
	अगर (!rc)
		वापस false;

	rc = calculate_ibuf_ctrl_cfg(
		 channel,
		 input_port,
		 isys_cfg,
		 &channel_cfg->ibuf_ctrl_cfg);
	अगर (!rc)
		वापस false;
	अगर (metadata)
		channel_cfg->ibuf_ctrl_cfg.stores_per_frame =
		    isys_cfg->metadata.lines_per_frame;

	rc = calculate_isys2401_dma_cfg(
		 channel,
		 isys_cfg,
		 &channel_cfg->dma_cfg);
	अगर (!rc)
		वापस false;

	rc = calculate_isys2401_dma_port_cfg(
		 isys_cfg,
		 false,
		 metadata,
		 &channel_cfg->dma_src_port_cfg);
	अगर (!rc)
		वापस false;

	rc = calculate_isys2401_dma_port_cfg(
		 isys_cfg,
		 isys_cfg->raw_packed,
		 metadata,
		 &channel_cfg->dma_dest_port_cfg);
	अगर (!rc)
		वापस false;

	वापस true;
पूर्ण

अटल bool calculate_input_प्रणाली_input_port_cfg(
    input_प्रणाली_channel_t		*channel,
    input_प्रणाली_input_port_t	*input_port,
    isp2401_input_प्रणाली_cfg_t		*isys_cfg,
    input_प्रणाली_input_port_cfg_t	*input_port_cfg)
अणु
	bool rc;

	चयन (input_port->source_type) अणु
	हाल INPUT_SYSTEM_SOURCE_TYPE_SENSOR:
		rc  = calculate_fe_cfg(
			  isys_cfg,
			  &input_port_cfg->csi_rx_cfg.frontend_cfg);

		rc &= calculate_be_cfg(
			  input_port,
			  isys_cfg,
			  false,
			  &input_port_cfg->csi_rx_cfg.backend_cfg);

		अगर (rc && isys_cfg->metadata.enable)
			rc &= calculate_be_cfg(input_port, isys_cfg, true,
					       &input_port_cfg->csi_rx_cfg.md_backend_cfg);
		अवरोध;
	हाल INPUT_SYSTEM_SOURCE_TYPE_TPG:
		rc = calculate_tpg_cfg(
			 channel,
			 input_port,
			 isys_cfg,
			 &input_port_cfg->pixelgen_cfg.tpg_cfg);
		अवरोध;
	हाल INPUT_SYSTEM_SOURCE_TYPE_PRBS:
		rc = calculate_prbs_cfg(
			 channel,
			 input_port,
			 isys_cfg,
			 &input_port_cfg->pixelgen_cfg.prbs_cfg);
		अवरोध;
	शेष:
		rc = false;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल bool acquire_sid(
    stream2mmio_ID_t	stream2mmio,
    stream2mmio_sid_ID_t	*sid)
अणु
	वापस ia_css_isys_stream2mmio_sid_rmgr_acquire(stream2mmio, sid);
पूर्ण

अटल व्योम release_sid(
    stream2mmio_ID_t	stream2mmio,
    stream2mmio_sid_ID_t	*sid)
अणु
	ia_css_isys_stream2mmio_sid_rmgr_release(stream2mmio, sid);
पूर्ण

/* See also: ia_css_dma_configure_from_info() */
अटल पूर्णांक32_t calculate_stride(
    s32 bits_per_pixel,
    s32 pixels_per_line,
    bool	raw_packed,
    पूर्णांक32_t align_in_bytes)
अणु
	s32 bytes_per_line;
	s32 pixels_per_word;
	s32 words_per_line;
	s32 pixels_per_line_padded;

	pixels_per_line_padded = CEIL_MUL(pixels_per_line, align_in_bytes);

	अगर (!raw_packed)
		bits_per_pixel = CEIL_MUL(bits_per_pixel, 8);

	pixels_per_word = HIVE_ISP_DDR_WORD_BITS / bits_per_pixel;
	words_per_line  = उच्चमान_भाग(pixels_per_line_padded, pixels_per_word);
	bytes_per_line  = HIVE_ISP_DDR_WORD_BYTES * words_per_line;

	वापस bytes_per_line;
पूर्ण

अटल bool acquire_ib_buffer(
    s32 bits_per_pixel,
    s32 pixels_per_line,
    s32 lines_per_frame,
    s32 align_in_bytes,
    bool online,
    isp2401_ib_buffer_t *buf)
अणु
	buf->stride = calculate_stride(bits_per_pixel, pixels_per_line, false,
				       align_in_bytes);
	अगर (online)
		buf->lines = 4; /* use द्विगुन buffering क्रम online useहालs */
	अन्यथा
		buf->lines = 2;

	(व्योम)(lines_per_frame);
	वापस ia_css_isys_ibuf_rmgr_acquire(buf->stride * buf->lines,
					     &buf->start_addr);
पूर्ण

अटल व्योम release_ib_buffer(
    isp2401_ib_buffer_t *buf)
अणु
	ia_css_isys_ibuf_rmgr_release(&buf->start_addr);
पूर्ण

अटल bool acquire_dma_channel(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channel	*channel)
अणु
	वापस ia_css_isys_dma_channel_rmgr_acquire(dma_id, channel);
पूर्ण

अटल व्योम release_dma_channel(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channel	*channel)
अणु
	ia_css_isys_dma_channel_rmgr_release(dma_id, channel);
पूर्ण

अटल bool acquire_be_lut_entry(
    csi_rx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_rx_backend_lut_entry_t	*entry)
अणु
	वापस ia_css_isys_csi_rx_lut_rmgr_acquire(backend, packet_type, entry);
पूर्ण

अटल व्योम release_be_lut_entry(
    csi_rx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_rx_backend_lut_entry_t	*entry)
अणु
	ia_css_isys_csi_rx_lut_rmgr_release(backend, packet_type, entry);
पूर्ण

अटल bool calculate_tpg_cfg(
    input_प्रणाली_channel_t		*channel,
    input_प्रणाली_input_port_t	*input_port,
    isp2401_input_प्रणाली_cfg_t		*isys_cfg,
    pixelgen_tpg_cfg_t		*cfg)
अणु
	स_नकल(cfg, &isys_cfg->tpg_port_attr, माप(pixelgen_tpg_cfg_t));

	वापस true;
पूर्ण

अटल bool calculate_prbs_cfg(
    input_प्रणाली_channel_t		*channel,
    input_प्रणाली_input_port_t	*input_port,
    isp2401_input_प्रणाली_cfg_t		*isys_cfg,
    pixelgen_prbs_cfg_t		*cfg)
अणु
	स_नकल(cfg, &isys_cfg->prbs_port_attr, माप(pixelgen_prbs_cfg_t));

	वापस true;
पूर्ण

अटल bool calculate_fe_cfg(
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    csi_rx_frontend_cfg_t		*cfg)
अणु
	cfg->active_lanes = isys_cfg->csi_port_attr.active_lanes;
	वापस true;
पूर्ण

अटल bool calculate_be_cfg(
    स्थिर input_प्रणाली_input_port_t	*input_port,
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    bool				metadata,
    csi_rx_backend_cfg_t		*cfg)
अणु
	स_नकल(&cfg->lut_entry,
	      metadata ? &input_port->metadata.backend_lut_entry :
			 &input_port->csi_rx.backend_lut_entry,
	      माप(csi_rx_backend_lut_entry_t));

	cfg->csi_mipi_cfg.भव_channel = isys_cfg->csi_port_attr.ch_id;
	अगर (metadata) अणु
		cfg->csi_mipi_packet_type = get_csi_mipi_packet_type(
						isys_cfg->metadata.fmt_type);
		cfg->csi_mipi_cfg.comp_enable = false;
		cfg->csi_mipi_cfg.data_type = isys_cfg->metadata.fmt_type;
	पूर्ण अन्यथा अणु
		cfg->csi_mipi_packet_type = get_csi_mipi_packet_type(
						isys_cfg->csi_port_attr.fmt_type);
		cfg->csi_mipi_cfg.data_type = isys_cfg->csi_port_attr.fmt_type;
		cfg->csi_mipi_cfg.comp_enable = isys_cfg->csi_port_attr.comp_enable;
		cfg->csi_mipi_cfg.comp_scheme = isys_cfg->csi_port_attr.comp_scheme;
		cfg->csi_mipi_cfg.comp_predictor = isys_cfg->csi_port_attr.comp_predictor;
		cfg->csi_mipi_cfg.comp_bit_idx = cfg->csi_mipi_cfg.data_type -
						 MIPI_FORMAT_CUSTOM0;
	पूर्ण

	वापस true;
पूर्ण

अटल bool calculate_stream2mmio_cfg(
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    bool				metadata,
    stream2mmio_cfg_t		*cfg
)
अणु
	cfg->bits_per_pixel = metadata ? isys_cfg->metadata.bits_per_pixel :
			      isys_cfg->input_port_resolution.bits_per_pixel;

	cfg->enable_blocking =
	    ((isys_cfg->mode == INPUT_SYSTEM_SOURCE_TYPE_TPG) ||
	     (isys_cfg->mode == INPUT_SYSTEM_SOURCE_TYPE_PRBS));

	वापस true;
पूर्ण

अटल bool calculate_ibuf_ctrl_cfg(
    स्थिर input_प्रणाली_channel_t	*channel,
    स्थिर input_प्रणाली_input_port_t	*input_port,
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    ibuf_ctrl_cfg_t			*cfg)
अणु
	स्थिर s32 bits_per_byte = 8;
	s32 bits_per_pixel;
	s32 bytes_per_pixel;
	s32 left_padding;

	(व्योम)input_port;

	bits_per_pixel = isys_cfg->input_port_resolution.bits_per_pixel;
	bytes_per_pixel = उच्चमान_भाग(bits_per_pixel, bits_per_byte);

	left_padding = CEIL_MUL(isys_cfg->output_port_attr.left_padding, ISP_VEC_NELEMS)
		       * bytes_per_pixel;

	cfg->online	= isys_cfg->online;

	cfg->dma_cfg.channel	= channel->dma_channel;
	cfg->dma_cfg.cmd	= _DMA_V2_MOVE_A2B_NO_SYNC_CHK_COMMAND;

	cfg->dma_cfg.shअगरt_वापसed_items	= 0;
	cfg->dma_cfg.elems_per_word_in_ibuf	= 0;
	cfg->dma_cfg.elems_per_word_in_dest	= 0;

	cfg->ib_buffer.start_addr		= channel->ib_buffer.start_addr;
	cfg->ib_buffer.stride			= channel->ib_buffer.stride;
	cfg->ib_buffer.lines			= channel->ib_buffer.lines;

	/*
	#अगर_अघोषित ISP2401
	 * zhengjie.lu@पूर्णांकel.com:
	#पूर्ण_अगर
	 * "dest_buf_cfg" should be part of the input प्रणाली output
	 * port configuration.
	 *
	 * TODO: move "dest_buf_cfg" to the input प्रणाली output
	 * port configuration.
	 */

	/* input_buf addr only available in sched mode;
	   this buffer is allocated in isp, crun mode addr
	   can be passed by after ISP allocation */
	अगर (cfg->online) अणु
		cfg->dest_buf_cfg.start_addr	= ISP_INPUT_BUF_START_ADDR + left_padding;
		cfg->dest_buf_cfg.stride	= bytes_per_pixel
					      * isys_cfg->output_port_attr.max_isp_input_width;
		cfg->dest_buf_cfg.lines		= LINES_OF_ISP_INPUT_BUF;
	पूर्ण अन्यथा अगर (isys_cfg->raw_packed) अणु
		cfg->dest_buf_cfg.stride	= calculate_stride(bits_per_pixel,
					      isys_cfg->input_port_resolution.pixels_per_line,
					      isys_cfg->raw_packed,
					      isys_cfg->input_port_resolution.align_req_in_bytes);
	पूर्ण अन्यथा अणु
		cfg->dest_buf_cfg.stride	= channel->ib_buffer.stride;
	पूर्ण

	/*
	#अगर_अघोषित ISP2401
	 * zhengjie.lu@पूर्णांकel.com:
	#पूर्ण_अगर
	 * "items_per_store" is hard coded as "1", which is ONLY valid
	 * when the CSI-MIPI दीर्घ packet is transferred.
	 *
	 * TODO: After the 1st stage of MERR+,  make the proper solution to
	 * configure "items_per_store" so that it can also handle the CSI-MIPI
	 * लघु packet.
	 */
	cfg->items_per_store		= 1;

	cfg->stores_per_frame		= isys_cfg->input_port_resolution.lines_per_frame;

	cfg->stream2mmio_cfg.sync_cmd	= _STREAM2MMIO_CMD_TOKEN_SYNC_FRAME;

	/* TODO: Define conditions as when to use store words vs store packets */
	cfg->stream2mmio_cfg.store_cmd	= _STREAM2MMIO_CMD_TOKEN_STORE_PACKETS;

	वापस true;
पूर्ण

अटल bool calculate_isys2401_dma_cfg(
    स्थिर input_प्रणाली_channel_t	*channel,
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    isys2401_dma_cfg_t		*cfg)
अणु
	cfg->channel	= channel->dma_channel;

	/* only online/sensor mode जाओ vmem
	   offline/buffered_sensor, tpg and prbs will go to ddr */
	अगर (isys_cfg->online)
		cfg->connection = isys2401_dma_ibuf_to_vmem_connection;
	अन्यथा
		cfg->connection = isys2401_dma_ibuf_to_ddr_connection;

	cfg->extension	= isys2401_dma_zero_extension;
	cfg->height	= 1;

	वापस true;
पूर्ण

/* See also: ia_css_dma_configure_from_info() */
अटल bool calculate_isys2401_dma_port_cfg(
    स्थिर isp2401_input_प्रणाली_cfg_t	*isys_cfg,
    bool				raw_packed,
    bool				metadata,
    isys2401_dma_port_cfg_t		*cfg)
अणु
	s32 bits_per_pixel;
	s32 pixels_per_line;
	s32 align_req_in_bytes;

	/* TODO: Move metadata away from isys_cfg to application layer */
	अगर (metadata) अणु
		bits_per_pixel = isys_cfg->metadata.bits_per_pixel;
		pixels_per_line = isys_cfg->metadata.pixels_per_line;
		align_req_in_bytes = isys_cfg->metadata.align_req_in_bytes;
	पूर्ण अन्यथा अणु
		bits_per_pixel = isys_cfg->input_port_resolution.bits_per_pixel;
		pixels_per_line = isys_cfg->input_port_resolution.pixels_per_line;
		align_req_in_bytes = isys_cfg->input_port_resolution.align_req_in_bytes;
	पूर्ण

	cfg->stride	= calculate_stride(bits_per_pixel, pixels_per_line, raw_packed,
				       align_req_in_bytes);

	अगर (!raw_packed)
		bits_per_pixel = CEIL_MUL(bits_per_pixel, 8);

	cfg->elements	= HIVE_ISP_DDR_WORD_BITS / bits_per_pixel;
	cfg->cropping	= 0;
	cfg->width	= CEIL_DIV(cfg->stride, HIVE_ISP_DDR_WORD_BYTES);

	वापस true;
पूर्ण

अटल csi_mipi_packet_type_t get_csi_mipi_packet_type(
    पूर्णांक32_t data_type)
अणु
	csi_mipi_packet_type_t packet_type;

	packet_type = CSI_MIPI_PACKET_TYPE_RESERVED;

	अगर (data_type >= 0 && data_type <= MIPI_FORMAT_SHORT8)
		packet_type = CSI_MIPI_PACKET_TYPE_SHORT;

	अगर (data_type > MIPI_FORMAT_SHORT8 && data_type <= N_MIPI_FORMAT)
		packet_type = CSI_MIPI_PACKET_TYPE_LONG;

	वापस packet_type;
पूर्ण

/* end of Private Methods */
#पूर्ण_अगर
