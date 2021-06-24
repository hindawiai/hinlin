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

#समावेश "ia_css_mipi.h"
#समावेश "sh_css_mipi.h"
#समावेश <type_support.h>
#समावेश "system_global.h"
#समावेश "ia_css_err.h"
#समावेश "ia_css_pipe.h"
#समावेश "ia_css_stream_format.h"
#समावेश "sh_css_stream_format.h"
#समावेश "ia_css_stream_public.h"
#समावेश "ia_css_frame_public.h"
#समावेश "ia_css_input_port.h"
#समावेश "ia_css_debug.h"
#समावेश "sh_css_struct.h"
#समावेश "sh_css_defs.h"
#समावेश "sh_css_sp.h" /* sh_css_update_host2sp_mipi_frame sh_css_update_host2sp_num_mipi_frames ... */
#समावेश "sw_event_global.h" /* IA_CSS_PSYS_SW_EVENT_MIPI_BUFFERS_READY */

अटल u32
ref_count_mipi_allocation[N_CSI_PORTS]; /* Initialized in mipi_init */

/*
 * Check अगर a source port or TPG/PRBS ID is valid
 */
अटल bool ia_css_mipi_is_source_port_valid(काष्ठा ia_css_pipe *pipe,
	अचिन्हित पूर्णांक *pport)
अणु
	bool ret = true;
	अचिन्हित पूर्णांक port = 0;
	अचिन्हित पूर्णांक max_ports = 0;

	चयन (pipe->stream->config.mode) अणु
	हाल IA_CSS_INPUT_MODE_BUFFERED_SENSOR:
		port = (अचिन्हित पूर्णांक)pipe->stream->config.source.port.port;
		max_ports = N_CSI_PORTS;
		अवरोध;
	हाल IA_CSS_INPUT_MODE_TPG:
		port = (अचिन्हित पूर्णांक)pipe->stream->config.source.tpg.id;
		max_ports = N_CSS_TPG_IDS;
		अवरोध;
	हाल IA_CSS_INPUT_MODE_PRBS:
		port = (अचिन्हित पूर्णांक)pipe->stream->config.source.prbs.id;
		max_ports = N_CSS_PRBS_IDS;
		अवरोध;
	शेष:
		निश्चित(false);
		ret = false;
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		निश्चित(port < max_ports);

		अगर (port >= max_ports)
			ret = false;
	पूर्ण

	*pport = port;

	वापस ret;
पूर्ण

/* Assumptions:
 *	- A line is multiple of 4 bytes = 1 word.
 *	- Each frame has SOF and खातापूर्ण (each 1 word).
 *	- Each line has क्रमmat header and optionally SOL and EOL (each 1 word).
 *	- Odd and even lines of YUV420 क्रमmat are dअगरferent in bites per pixel size.
 *	- Custom size of embedded data.
 *  -- Interleaved frames are not taken पूर्णांकo account.
 *  -- Lines are multiples of 8B, and not necessary of (custom 3B, or 7B
 *  etc.).
 * Result is given in DDR mem words, 32B or 256 bits
 */
पूर्णांक
ia_css_mipi_frame_calculate_size(स्थिर अचिन्हित पूर्णांक width,
				 स्थिर अचिन्हित पूर्णांक height,
				 स्थिर क्रमागत atomisp_input_क्रमmat क्रमmat,
				 स्थिर bool hasSOLandEOL,
				 स्थिर अचिन्हित पूर्णांक embedded_data_size_words,
				 अचिन्हित पूर्णांक *size_mem_words) अणु
	पूर्णांक err = 0;

	अचिन्हित पूर्णांक bits_per_pixel = 0;
	अचिन्हित पूर्णांक even_line_bytes = 0;
	अचिन्हित पूर्णांक odd_line_bytes = 0;
	अचिन्हित पूर्णांक words_per_odd_line = 0;
	अचिन्हित पूर्णांक words_क्रम_first_line = 0;
	अचिन्हित पूर्णांक words_per_even_line = 0;
	अचिन्हित पूर्णांक mem_words_per_even_line = 0;
	अचिन्हित पूर्णांक mem_words_per_odd_line = 0;
	अचिन्हित पूर्णांक mem_words_क्रम_first_line = 0;
	अचिन्हित पूर्णांक mem_words_क्रम_खातापूर्ण = 0;
	अचिन्हित पूर्णांक mem_words = 0;
	अचिन्हित पूर्णांक width_padded = width;

#अगर defined(ISP2401)
	/* The changes will be reverted as soon as RAW
	 * Buffers are deployed by the 2401 Input System
	 * in the non-continuous use scenario.
	 */
	width_padded += (2 * ISP_VEC_NELEMS);
#पूर्ण_अगर

	IA_CSS_ENTER("padded_width=%d, height=%d, format=%d, hasSOLandEOL=%d, embedded_data_size_words=%d\n",
		     width_padded, height, क्रमmat, hasSOLandEOL, embedded_data_size_words);

	चयन (क्रमmat)
	अणु
	हाल ATOMISP_INPUT_FORMAT_RAW_6:		/* 4p, 3B, 24bits */
		bits_per_pixel = 6;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_7:		/* 8p, 7B, 56bits */
		bits_per_pixel = 7;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_8:		/* 1p, 1B, 8bits */
	हाल ATOMISP_INPUT_FORMAT_BINARY_8:		/*  8bits, TODO: check. */
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:		/* odd 2p, 2B, 16bits, even 2p, 4B, 32bits */
		bits_per_pixel = 8;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_10:		/* odd 4p, 5B, 40bits, even 4p, 10B, 80bits */
	हाल ATOMISP_INPUT_FORMAT_RAW_10:		/* 4p, 5B, 40bits */
#अगर !defined(HAS_NO_PACKED_RAW_PIXELS)
		/* The changes will be reverted as soon as RAW
		 * Buffers are deployed by the 2401 Input System
		 * in the non-continuous use scenario.
		 */
		bits_per_pixel = 10;
#अन्यथा
		bits_per_pixel = 16;
#पूर्ण_अगर
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY:	/* 2p, 3B, 24bits */
	हाल ATOMISP_INPUT_FORMAT_RAW_12:		/* 2p, 3B, 24bits */
		bits_per_pixel = 12;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_14:		/* 4p, 7B, 56bits */
		bits_per_pixel = 14;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_444:		/* 1p, 2B, 16bits */
	हाल ATOMISP_INPUT_FORMAT_RGB_555:		/* 1p, 2B, 16bits */
	हाल ATOMISP_INPUT_FORMAT_RGB_565:		/* 1p, 2B, 16bits */
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:		/* 2p, 4B, 32bits */
		bits_per_pixel = 16;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_666:		/* 4p, 9B, 72bits */
		bits_per_pixel = 18;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV422_10:		/* 2p, 5B, 40bits */
		bits_per_pixel = 20;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_888:		/* 1p, 3B, 24bits */
		bits_per_pixel = 24;
		अवरोध;

	हाल ATOMISP_INPUT_FORMAT_YUV420_16:		/* Not supported */
	हाल ATOMISP_INPUT_FORMAT_YUV422_16:		/* Not supported */
	हाल ATOMISP_INPUT_FORMAT_RAW_16:		/* TODO: not specअगरied in MIPI SPEC, check */
	शेष:
		वापस -EINVAL;
	पूर्ण

	odd_line_bytes = (width_padded * bits_per_pixel + 7) >> 3; /* उच्चमान ( bits per line / 8) */

	/* Even lines क्रम YUV420 क्रमmats are द्विगुन in bits_per_pixel. */
	अगर (क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_8
	    || क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_10
	    || क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_16)
	अणु
		even_line_bytes = (width_padded * 2 * bits_per_pixel + 7) >>
			3; /* उच्चमान ( bits per line / 8) */
	पूर्ण अन्यथा
	अणु
		even_line_bytes = odd_line_bytes;
	पूर्ण

	/*  a frame represented in memory:  ()- optional; data - payload words.
	*  addr		0	1	2	3	4	5	6	7:
	*  first	SOF	(SOL)	PACK_H	data	data	data	data	data
	*		data	data	data	data	data	data	data	data
	*		...
	*		data	data	0	0	0	0	0	0
	*  second	(EOL)	(SOL)	PACK_H	data	data	data	data	data
	*		data	data	data	data	data	data	data	data
	*		...
	*		data	data	0	0	0	0	0	0
	*  ...
	*  last		(EOL)	खातापूर्ण	0	0	0	0	0	0
	*
	*  Embedded lines are regular lines stored beक्रमe the first and after
	*  payload lines.
	*/

	words_per_odd_line = (odd_line_bytes + 3) >> 2;
	/* उच्चमान(odd_line_bytes/4); word = 4 bytes */
	words_per_even_line  = (even_line_bytes  + 3) >> 2;
	words_क्रम_first_line = words_per_odd_line + 2 + (hasSOLandEOL ? 1 : 0);
	/* + SOF +packet header + optionally (SOL), but (EOL) is not in the first line */
	words_per_odd_line	+= (1 + (hasSOLandEOL ? 2 : 0));
	/* each non-first line has क्रमmat header, and optionally (SOL) and (EOL). */
	words_per_even_line += (1 + (hasSOLandEOL ? 2 : 0));

	mem_words_per_odd_line	 = (words_per_odd_line + 7) >> 3;
	/* उच्चमान(words_per_odd_line/8); mem_word = 32 bytes, 8 words */
	mem_words_क्रम_first_line = (words_क्रम_first_line + 7) >> 3;
	mem_words_per_even_line  = (words_per_even_line + 7) >> 3;
	mem_words_क्रम_खातापूर्ण        = 1; /* last line consisit of the optional (EOL) and खातापूर्ण */

	mem_words = ((embedded_data_size_words + 7) >> 3) +
	mem_words_क्रम_first_line +
	(((height + 1) >> 1) - 1) * mem_words_per_odd_line +
	/* उच्चमान (height/2) - 1 (first line is calculated separatelly) */
	(height      >> 1) * mem_words_per_even_line + /* न्यूनमान(height/2) */
	mem_words_क्रम_खातापूर्ण;

	*size_mem_words = mem_words; /* उच्चमान(words/8); mem word is 32B = 8words. */
	/* Check अगर the above is still needed. */

	IA_CSS_LEAVE_ERR(err);
	वापस err;
पूर्ण

#अगर !defined(ISP2401)
पूर्णांक
ia_css_mipi_frame_enable_check_on_size(स्थिर क्रमागत mipi_port_id port,
				       स्थिर अचिन्हित पूर्णांक	size_mem_words) अणु
	u32 idx;

	पूर्णांक err = -EBUSY;

	OP___निश्चित(port < N_CSI_PORTS);
	OP___निश्चित(size_mem_words != 0);

	क्रम (idx = 0; idx < IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTRIES_PER_PORT &&
	     my_css.mipi_sizes_क्रम_check[port][idx] != 0;
	     idx++)   /* करो nothing */
	अणु
	पूर्ण
	अगर (idx < IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTRIES_PER_PORT)
	अणु
		my_css.mipi_sizes_क्रम_check[port][idx] = size_mem_words;
		err = 0;
	पूर्ण

	वापस err;
पूर्ण
#पूर्ण_अगर

व्योम
mipi_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < N_CSI_PORTS; i++)
		ref_count_mipi_allocation[i] = 0;
पूर्ण

पूर्णांक
calculate_mipi_buff_size(
    काष्ठा ia_css_stream_config *stream_cfg,
    अचिन्हित पूर्णांक *size_mem_words) अणु
#अगर !defined(ISP2401)
	पूर्णांक err = -EINVAL;
	(व्योम)stream_cfg;
	(व्योम)size_mem_words;
#अन्यथा
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	क्रमागत atomisp_input_क्रमmat क्रमmat;
	bool pack_raw_pixels;

	अचिन्हित पूर्णांक width_padded;
	अचिन्हित पूर्णांक bits_per_pixel = 0;

	अचिन्हित पूर्णांक even_line_bytes = 0;
	अचिन्हित पूर्णांक odd_line_bytes = 0;

	अचिन्हित पूर्णांक words_per_odd_line = 0;
	अचिन्हित पूर्णांक words_per_even_line = 0;

	अचिन्हित पूर्णांक mem_words_per_even_line = 0;
	अचिन्हित पूर्णांक mem_words_per_odd_line = 0;

	अचिन्हित पूर्णांक mem_words_per_buff_line = 0;
	अचिन्हित पूर्णांक mem_words_per_buff = 0;
	पूर्णांक err = 0;

	/**
	 * zhengjie.lu@पूर्णांकel.com
	 *
	 * NOTE
	 * - In the काष्ठा "ia_css_stream_config", there
	 *   are two members: "input_config" and "isys_config".
	 *   Both of them provide the same inक्रमmation, e.g.
	 *   input_res and क्रमmat.
	 *
	 *   Question here is that: which one shall be used?
	 */
	width = stream_cfg->input_config.input_res.width;
	height = stream_cfg->input_config.input_res.height;
	क्रमmat = stream_cfg->input_config.क्रमmat;
	pack_raw_pixels = stream_cfg->pack_raw_pixels;
	/* end of NOTE */

	/**
	 * zhengjie.lu@पूर्णांकel.com
	 *
	 * NOTE
	 * - The following code is derived from the
	 *   existing code "ia_css_mipi_frame_calculate_size()".
	 *
	 *   Question here is: why adding "2 * ISP_VEC_NELEMS"
	 *   to "width_padded", but not making "width_padded"
	 *   aligned with "2 * ISP_VEC_NELEMS"?
	 */
	/* The changes will be reverted as soon as RAW
	 * Buffers are deployed by the 2401 Input System
	 * in the non-continuous use scenario.
	 */
	width_padded = width + (2 * ISP_VEC_NELEMS);
	/* end of NOTE */

	IA_CSS_ENTER("padded_width=%d, height=%d, format=%d\n",
		     width_padded, height, क्रमmat);

	bits_per_pixel = sh_css_stream_क्रमmat_2_bits_per_subpixel(क्रमmat);
	bits_per_pixel =
	(क्रमmat == ATOMISP_INPUT_FORMAT_RAW_10 && pack_raw_pixels) ? bits_per_pixel : 16;
	अगर (bits_per_pixel == 0)
		वापस -EINVAL;

	odd_line_bytes = (width_padded * bits_per_pixel + 7) >> 3; /* उच्चमान ( bits per line / 8) */

	/* Even lines क्रम YUV420 क्रमmats are द्विगुन in bits_per_pixel. */
	अगर (क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_8
	    || क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_10)
	अणु
		even_line_bytes = (width_padded * 2 * bits_per_pixel + 7) >>
			3; /* उच्चमान ( bits per line / 8) */
	पूर्ण अन्यथा
	अणु
		even_line_bytes = odd_line_bytes;
	पूर्ण

	words_per_odd_line	 = (odd_line_bytes   + 3) >> 2;
	/* उच्चमान(odd_line_bytes/4); word = 4 bytes */
	words_per_even_line  = (even_line_bytes  + 3) >> 2;

	mem_words_per_odd_line	 = (words_per_odd_line + 7) >> 3;
	/* उच्चमान(words_per_odd_line/8); mem_word = 32 bytes, 8 words */
	mem_words_per_even_line  = (words_per_even_line + 7) >> 3;

	mem_words_per_buff_line =
	(mem_words_per_odd_line > mem_words_per_even_line) ? mem_words_per_odd_line : mem_words_per_even_line;
	mem_words_per_buff = mem_words_per_buff_line * height;

	*size_mem_words = mem_words_per_buff;

	IA_CSS_LEAVE_ERR(err);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल bool buffers_needed(काष्ठा ia_css_pipe *pipe)
अणु
	अगर (!IS_ISP2401) अणु
		अगर (pipe->stream->config.mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR)
			वापस false;
		अन्यथा
			वापस true;
	पूर्ण

	अगर (pipe->stream->config.mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR ||
	    pipe->stream->config.mode == IA_CSS_INPUT_MODE_TPG ||
	    pipe->stream->config.mode == IA_CSS_INPUT_MODE_PRBS)
		वापस false;

	वापस true;
पूर्ण

पूर्णांक
allocate_mipi_frames(काष्ठा ia_css_pipe *pipe,
		     काष्ठा ia_css_stream_info *info) अणु
	पूर्णांक err = -EINVAL;
	अचिन्हित पूर्णांक port;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "allocate_mipi_frames(%p) enter:\n", pipe);

	निश्चित(pipe);
	निश्चित(pipe->stream);
	अगर ((!pipe) || (!pipe->stream))
	अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "allocate_mipi_frames(%p) exit: pipe or stream is null.\n",
				    pipe);
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित ISP2401
	अगर (pipe->stream->config.online)
	अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "allocate_mipi_frames(%p) exit: no buffers needed for 2401 pipe mode.\n",
				    pipe);
		वापस 0;
	पूर्ण

#पूर्ण_अगर

	अगर (!buffers_needed(pipe)) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "allocate_mipi_frames(%p) exit: no buffers needed for pipe mode.\n",
				    pipe);
		वापस 0; /* AM TODO: Check  */
	पूर्ण

	अगर (!IS_ISP2401)
		port = (अचिन्हित पूर्णांक)pipe->stream->config.source.port.port;
	अन्यथा
		err = ia_css_mipi_is_source_port_valid(pipe, &port);

	निश्चित(port < N_CSI_PORTS);

	अगर (port >= N_CSI_PORTS || err) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "allocate_mipi_frames(%p) exit: error: port is not correct (port=%d).\n",
				    pipe, port);
		वापस -EINVAL;
	पूर्ण

#अगर_घोषित ISP2401
	err = calculate_mipi_buff_size(
	    &pipe->stream->config,
	    &my_css.mipi_frame_size[port]);
#पूर्ण_अगर

#अगर !defined(ISP2401)
	अगर (ref_count_mipi_allocation[port] != 0)
	अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "allocate_mipi_frames(%p) exit: already allocated for this port (port=%d).\n",
				    pipe, port);
		वापस 0;
	पूर्ण
#अन्यथा
	/* 2401 प्रणाली allows multiple streams to use same physical port. This is not
	 * true क्रम 2400 प्रणाली. Currently 2401 uses MIPI buffers as a temporary solution.
	 * TODO AM: Once that is changed (हटाओd) this code should be हटाओd as well.
	 * In that हाल only 2400 related code should reमुख्य.
	 */
	अगर (ref_count_mipi_allocation[port] != 0)
	अणु
		ref_count_mipi_allocation[port]++;
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "allocate_mipi_frames(%p) leave: nothing to do, already allocated for this port (port=%d).\n",
				    pipe, port);
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	ref_count_mipi_allocation[port]++;

	/* AM TODO: mipi frames number should come from stream काष्ठा. */
	my_css.num_mipi_frames[port] = NUM_MIPI_FRAMES_PER_STREAM;

	/* Incremental allocation (per stream), not क्रम all streams at once. */
	अणु /* limit the scope of i,j */
		अचिन्हित पूर्णांक i, j;

		क्रम (i = 0; i < my_css.num_mipi_frames[port]; i++)
		अणु
			/* मुक्त previous frame */
			अगर (my_css.mipi_frames[port][i]) अणु
				ia_css_frame_मुक्त(my_css.mipi_frames[port][i]);
				my_css.mipi_frames[port][i] = शून्य;
			पूर्ण
			/* check अगर new frame is needed */
			अगर (i < my_css.num_mipi_frames[port]) अणु
				/* allocate new frame */
				err = ia_css_frame_allocate_with_buffer_size(
					  &my_css.mipi_frames[port][i],
					  my_css.mipi_frame_size[port] * HIVE_ISP_DDR_WORD_BYTES,
					  false);
				अगर (err) अणु
					क्रम (j = 0; j < i; j++) अणु
						अगर (my_css.mipi_frames[port][j]) अणु
							ia_css_frame_मुक्त(my_css.mipi_frames[port][j]);
							my_css.mipi_frames[port][j] = शून्य;
						पूर्ण
					पूर्ण
					ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
							    "allocate_mipi_frames(%p, %d) exit: error: allocation failed.\n",
							    pipe, port);
					वापस err;
				पूर्ण
			पूर्ण
			अगर (info->metadata_info.size > 0) अणु
				/* मुक्त previous metadata buffer */
				अगर (my_css.mipi_metadata[port][i]) अणु
					ia_css_metadata_मुक्त(my_css.mipi_metadata[port][i]);
					my_css.mipi_metadata[port][i] = शून्य;
				पूर्ण
				/* check अगर need to allocate a new metadata buffer */
				अगर (i < my_css.num_mipi_frames[port]) अणु
					/* allocate new metadata buffer */
					my_css.mipi_metadata[port][i] = ia_css_metadata_allocate(&info->metadata_info);
					अगर (!my_css.mipi_metadata[port][i]) अणु
						ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
								    "allocate_mipi_metadata(%p, %d) failed.\n",
								    pipe, port);
						वापस err;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "allocate_mipi_frames(%p) exit:\n", pipe);

	वापस err;
पूर्ण

पूर्णांक
मुक्त_mipi_frames(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = -EINVAL;
	अचिन्हित पूर्णांक port;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "free_mipi_frames(%p) enter:\n", pipe);

	/* निश्चित(pipe != शून्य); TEMP: TODO: Should be निश्चित only. */
	अगर (pipe)
	अणु
		निश्चित(pipe->stream);
		अगर ((!pipe) || (!pipe->stream)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
					    "free_mipi_frames(%p) exit: error: pipe or stream is null.\n",
					    pipe);
			वापस -EINVAL;
		पूर्ण

		अगर (!buffers_needed(pipe)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
					    "free_mipi_frames(%p) exit: error: wrong mode.\n",
					    pipe);
			वापस err;
		पूर्ण

		अगर (!IS_ISP2401)
			port = (अचिन्हित पूर्णांक)pipe->stream->config.source.port.port;
		अन्यथा
			err = ia_css_mipi_is_source_port_valid(pipe, &port);

		निश्चित(port < N_CSI_PORTS);

		अगर (port >= N_CSI_PORTS || err) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
					    "free_mipi_frames(%p, %d) exit: error: pipe port is not correct.\n",
					    pipe, port);
			वापस err;
		पूर्ण

		अगर (ref_count_mipi_allocation[port] > 0) अणु
#अगर !defined(ISP2401)
			निश्चित(ref_count_mipi_allocation[port] == 1);
			अगर (ref_count_mipi_allocation[port] != 1) अणु
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
						    "free_mipi_frames(%p) exit: error: wrong ref_count (ref_count=%d).\n",
						    pipe, ref_count_mipi_allocation[port]);
				वापस err;
			पूर्ण
#पूर्ण_अगर

			ref_count_mipi_allocation[port]--;

			अगर (ref_count_mipi_allocation[port] == 0) अणु
				/* no streams are using this buffer, so मुक्त it */
				अचिन्हित पूर्णांक i;

				क्रम (i = 0; i < my_css.num_mipi_frames[port]; i++) अणु
					अगर (my_css.mipi_frames[port][i]) अणु
						ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
								    "free_mipi_frames(port=%d, num=%d).\n", port, i);
						ia_css_frame_मुक्त(my_css.mipi_frames[port][i]);
						my_css.mipi_frames[port][i] = शून्य;
					पूर्ण
					अगर (my_css.mipi_metadata[port][i]) अणु
						ia_css_metadata_मुक्त(my_css.mipi_metadata[port][i]);
						my_css.mipi_metadata[port][i] = शून्य;
					पूर्ण
				पूर्ण

				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
						    "free_mipi_frames(%p) exit (deallocated).\n", pipe);
			पूर्ण
#अगर defined(ISP2401)
			अन्यथा अणु
				/* 2401 प्रणाली allows multiple streams to use same physical port. This is not
				 * true क्रम 2400 प्रणाली. Currently 2401 uses MIPI buffers as a temporary solution.
				 * TODO AM: Once that is changed (हटाओd) this code should be हटाओd as well.
				 * In that हाल only 2400 related code should reमुख्य.
				 */
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
						    "free_mipi_frames(%p) leave: nothing to do, other streams still use this port (port=%d).\n",
						    pipe, port);
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा   /* pipe ==शून्य */
	अणु
		/* AM TEMP: मुक्त-ing all mipi buffers just like a legacy code. */
		क्रम (port = CSI_PORT0_ID; port < N_CSI_PORTS; port++) अणु
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < my_css.num_mipi_frames[port]; i++) अणु
				अगर (my_css.mipi_frames[port][i]) अणु
					ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
							    "free_mipi_frames(port=%d, num=%d).\n", port, i);
					ia_css_frame_मुक्त(my_css.mipi_frames[port][i]);
					my_css.mipi_frames[port][i] = शून्य;
				पूर्ण
				अगर (my_css.mipi_metadata[port][i]) अणु
					ia_css_metadata_मुक्त(my_css.mipi_metadata[port][i]);
					my_css.mipi_metadata[port][i] = शून्य;
				पूर्ण
			पूर्ण
			ref_count_mipi_allocation[port] = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
send_mipi_frames(काष्ठा ia_css_pipe *pipe) अणु
	पूर्णांक err = -EINVAL;
	अचिन्हित पूर्णांक i;
#अगर_अघोषित ISP2401
	अचिन्हित पूर्णांक port;
#अन्यथा
	अचिन्हित पूर्णांक port = 0;
#पूर्ण_अगर

	IA_CSS_ENTER_PRIVATE("pipe=%p", pipe);

	निश्चित(pipe);
	निश्चित(pipe->stream);
	अगर (!pipe || !pipe->stream)
	अणु
		IA_CSS_ERROR("pipe or stream is null");
		वापस -EINVAL;
	पूर्ण

	/* multi stream video needs mipi buffers */
	/* nothing to be करोne in other हालs. */
	अगर (!buffers_needed(pipe)) अणु
		IA_CSS_LOG("nothing to be done for this mode");
		वापस 0;
		/* TODO: AM: maybe this should be वापसing an error. */
	पूर्ण

	अगर (!IS_ISP2401)
		port = (अचिन्हित पूर्णांक)pipe->stream->config.source.port.port;
	अन्यथा
		err = ia_css_mipi_is_source_port_valid(pipe, &port);

	निश्चित(port < N_CSI_PORTS);

	अगर (port >= N_CSI_PORTS || err) अणु
		IA_CSS_ERROR("send_mipi_frames(%p) exit: invalid port specified (port=%d).\n",
			     pipe, port);
		वापस err;
	पूर्ण

	/* Hand-over the SP-पूर्णांकernal mipi buffers */
	क्रम (i = 0; i < my_css.num_mipi_frames[port]; i++)
	अणु
		/* Need to include the ofset क्रम port. */
		sh_css_update_host2sp_mipi_frame(port * NUM_MIPI_FRAMES_PER_STREAM + i,
						 my_css.mipi_frames[port][i]);
		sh_css_update_host2sp_mipi_metadata(port * NUM_MIPI_FRAMES_PER_STREAM + i,
						    my_css.mipi_metadata[port][i]);
	पूर्ण
	sh_css_update_host2sp_num_mipi_frames(my_css.num_mipi_frames[port]);

	/**********************************
	 * Send an event to inक्रमm the SP
	 * that all MIPI frames are passed.
	 **********************************/
	अगर (!sh_css_sp_is_running())
	अणु
		/* SP is not running. The queues are not valid */
		IA_CSS_ERROR("sp is not running");
		वापस err;
	पूर्ण

	ia_css_bufq_enqueue_psys_event(
	    IA_CSS_PSYS_SW_EVENT_MIPI_BUFFERS_READY,
	    (uपूर्णांक8_t)port,
	    (uपूर्णांक8_t)my_css.num_mipi_frames[port],
	    0 /* not used */);
	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण
