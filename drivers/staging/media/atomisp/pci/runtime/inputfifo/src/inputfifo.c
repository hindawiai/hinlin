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

#समावेश "platform_support.h"

#समावेश "ia_css_inputfifo.h"

#समावेश "device_access.h"

#घोषणा __INLINE_SP__
#समावेश "sp.h"
#घोषणा __INLINE_ISP__
#समावेश "isp.h"
#घोषणा __INLINE_IRQ__
#समावेश "irq.h"
#घोषणा __INLINE_FIFO_MONITOR__
#समावेश "fifo_monitor.h"

#घोषणा __INLINE_EVENT__
#समावेश "event_fifo.h"
#घोषणा __INLINE_SP__

#समावेश "input_system.h"	/* MIPI_PREDICTOR_NONE,... */

#समावेश "assert_support.h"

/* System independent */
#समावेश "sh_css_internal.h"
#समावेश "ia_css_isys.h"

#घोषणा HBLANK_CYCLES (187)
#घोषणा MARKER_CYCLES (6)

#समावेश <hive_isp_css_streaming_to_mipi_types_hrt.h>

/* The data type is used to send special हालs:
 * yuv420: odd lines (1, 3 etc) are twice as wide as even
 *         lines (0, 2, 4 etc).
 * rgb: क्रम two pixels per घड़ी, the R and B values are sent
 *      to output_0 जबतक only G is sent to output_1. This means
 *      that output_1 only माला_लो half the number of values of output_0.
 *      WARNING: This type should also be used क्रम Legacy YUV420.
 * regular: used क्रम all other data types (RAW, YUV422, etc)
 */
क्रमागत inputfअगरo_mipi_data_type अणु
	inputfअगरo_mipi_data_type_regular,
	inputfअगरo_mipi_data_type_yuv420,
	inputfअगरo_mipi_data_type_yuv420_legacy,
	inputfअगरo_mipi_data_type_rgb,
पूर्ण;

अटल अचिन्हित पूर्णांक inputfअगरo_curr_ch_id, inputfअगरo_curr_fmt_type;
काष्ठा inputfअगरo_instance अणु
	अचिन्हित पूर्णांक				ch_id;
	क्रमागत atomisp_input_क्रमmat	input_क्रमmat;
	bool						two_ppc;
	bool						streaming;
	अचिन्हित पूर्णांक				hblank_cycles;
	अचिन्हित पूर्णांक				marker_cycles;
	अचिन्हित पूर्णांक				fmt_type;
	क्रमागत inputfअगरo_mipi_data_type	type;
पूर्ण;

/*
 * Maपूर्णांकain a basic streaming to Mipi administration with ch_id as index
 * ch_id maps on the "Mipi virtual channel ID" and can have value 0..3
 */
#घोषणा INPUTFIFO_NR_OF_S2M_CHANNELS	(4)
अटल काष्ठा inputfअगरo_instance
	inputfअगरo_inst_admin[INPUTFIFO_NR_OF_S2M_CHANNELS];

/* Streaming to MIPI */
अटल अचिन्हित पूर्णांक inputfअगरo_wrap_marker(
    /* अटल अंतरभूत अचिन्हित inputfअगरo_wrap_marker( */
    अचिन्हित पूर्णांक marker)
अणु
	वापस marker |
	       (inputfअगरo_curr_ch_id << HIVE_STR_TO_MIPI_CH_ID_LSB) |
	       (inputfअगरo_curr_fmt_type << _HIVE_STR_TO_MIPI_FMT_TYPE_LSB);
पूर्ण

अटल अंतरभूत व्योम
_sh_css_fअगरo_snd(अचिन्हित पूर्णांक token)
अणु
	जबतक (!can_event_send_token(STR2MIPI_EVENT_ID))
		udelay(1);
	event_send_token(STR2MIPI_EVENT_ID, token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_data_a(
    /* अटल अंतरभूत व्योम inputfअगरo_send_data_a( */
    अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक token = (1 << HIVE_STR_TO_MIPI_VALID_A_BIT) |
			     (data << HIVE_STR_TO_MIPI_DATA_A_LSB);
	_sh_css_fअगरo_snd(token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_data_b(
    /* अटल अंतरभूत व्योम inputfअगरo_send_data_b( */
    अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक token = (1 << HIVE_STR_TO_MIPI_VALID_B_BIT) |
			     (data << _HIVE_STR_TO_MIPI_DATA_B_LSB);
	_sh_css_fअगरo_snd(token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_data(
    /* अटल अंतरभूत व्योम inputfअगरo_send_data( */
    अचिन्हित पूर्णांक a,
    अचिन्हित पूर्णांक b)
अणु
	अचिन्हित पूर्णांक token = ((1 << HIVE_STR_TO_MIPI_VALID_A_BIT) |
			      (1 << HIVE_STR_TO_MIPI_VALID_B_BIT) |
			      (a << HIVE_STR_TO_MIPI_DATA_A_LSB) |
			      (b << _HIVE_STR_TO_MIPI_DATA_B_LSB));
	_sh_css_fअगरo_snd(token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_sol(व्योम)
/* अटल अंतरभूत व्योम inputfअगरo_send_sol(व्योम) */
अणु
	hrt_data	token = inputfअगरo_wrap_marker(
				1 << HIVE_STR_TO_MIPI_SOL_BIT);

	_sh_css_fअगरo_snd(token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_eol(व्योम)
/* अटल अंतरभूत व्योम inputfअगरo_send_eol(व्योम) */
अणु
	hrt_data	token = inputfअगरo_wrap_marker(
				1 << HIVE_STR_TO_MIPI_EOL_BIT);
	_sh_css_fअगरo_snd(token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_sof(व्योम)
/* अटल अंतरभूत व्योम inputfअगरo_send_sof(व्योम) */
अणु
	hrt_data	token = inputfअगरo_wrap_marker(
				1 << HIVE_STR_TO_MIPI_SOF_BIT);

	_sh_css_fअगरo_snd(token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_eof(व्योम)
/* अटल अंतरभूत व्योम inputfअगरo_send_eof(व्योम) */
अणु
	hrt_data	token = inputfअगरo_wrap_marker(
				1 << HIVE_STR_TO_MIPI_खातापूर्ण_BIT);
	_sh_css_fअगरo_snd(token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_ch_id_and_fmt_type(
    /* अटल अंतरभूत
    व्योम inputfअगरo_send_ch_id_and_fmt_type( */
    अचिन्हित पूर्णांक ch_id,
    अचिन्हित पूर्णांक fmt_type)
अणु
	hrt_data	token;

	inputfअगरo_curr_ch_id = ch_id & _HIVE_ISP_CH_ID_MASK;
	inputfअगरo_curr_fmt_type = fmt_type & _HIVE_ISP_FMT_TYPE_MASK;
	/* we send an zero marker, this will wrap the ch_id and
	 * fmt_type स्वतःmatically.
	 */
	token = inputfअगरo_wrap_marker(0);
	_sh_css_fअगरo_snd(token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_empty_token(व्योम)
/* अटल अंतरभूत व्योम inputfअगरo_send_empty_token(व्योम) */
अणु
	hrt_data	token = inputfअगरo_wrap_marker(0);

	_sh_css_fअगरo_snd(token);
	वापस;
पूर्ण

अटल व्योम inputfअगरo_start_frame(
    /* अटल अंतरभूत व्योम inputfअगरo_start_frame( */
    अचिन्हित पूर्णांक ch_id,
    अचिन्हित पूर्णांक fmt_type)
अणु
	inputfअगरo_send_ch_id_and_fmt_type(ch_id, fmt_type);
	inputfअगरo_send_sof();
	वापस;
पूर्ण

अटल व्योम inputfअगरo_end_frame(
    अचिन्हित पूर्णांक marker_cycles)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < marker_cycles; i++)
		inputfअगरo_send_empty_token();
	inputfअगरo_send_eof();
	वापस;
पूर्ण

अटल व्योम inputfअगरo_send_line2(
    स्थिर अचिन्हित लघु *data,
    अचिन्हित पूर्णांक width,
    स्थिर अचिन्हित लघु *data2,
    अचिन्हित पूर्णांक width2,
    अचिन्हित पूर्णांक hblank_cycles,
    अचिन्हित पूर्णांक marker_cycles,
    अचिन्हित पूर्णांक two_ppc,
    क्रमागत inputfअगरo_mipi_data_type type)
अणु
	अचिन्हित पूर्णांक i, is_rgb = 0, is_legacy = 0;

	निश्चित(data);
	निश्चित((data2) || (width2 == 0));
	अगर (type == inputfअगरo_mipi_data_type_rgb)
		is_rgb = 1;

	अगर (type == inputfअगरo_mipi_data_type_yuv420_legacy)
		is_legacy = 1;

	क्रम (i = 0; i < hblank_cycles; i++)
		inputfअगरo_send_empty_token();
	inputfअगरo_send_sol();
	क्रम (i = 0; i < marker_cycles; i++)
		inputfअगरo_send_empty_token();
	क्रम (i = 0; i < width; i++, data++) अणु
		/* क्रम RGB in two_ppc, we only actually send 2 pixels per
		 * घड़ी in the even pixels (0, 2 etc). In the other cycles,
		 * we only send 1 pixel, to data[0].
		 */
		अचिन्हित पूर्णांक send_two_pixels = two_ppc;

		अगर ((is_rgb || is_legacy) && (i % 3 == 2))
			send_two_pixels = 0;
		अगर (send_two_pixels) अणु
			अगर (i + 1 == width) अणु
				/* क्रम jpg (binary) copy, this can occur
				 * अगर the file contains an odd number of bytes.
				 */
				inputfअगरo_send_data(
				    data[0], 0);
			पूर्ण अन्यथा अणु
				inputfअगरo_send_data(
				    data[0], data[1]);
			पूर्ण
			/* Additional increment because we send 2 pixels */
			data++;
			i++;
		पूर्ण अन्यथा अगर (two_ppc && is_legacy) अणु
			inputfअगरo_send_data_b(data[0]);
		पूर्ण अन्यथा अणु
			inputfअगरo_send_data_a(data[0]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < width2; i++, data2++) अणु
		/* क्रम RGB in two_ppc, we only actually send 2 pixels per
		 * घड़ी in the even pixels (0, 2 etc). In the other cycles,
		 * we only send 1 pixel, to data2[0].
		 */
		अचिन्हित पूर्णांक send_two_pixels = two_ppc;

		अगर ((is_rgb || is_legacy) && (i % 3 == 2))
			send_two_pixels = 0;
		अगर (send_two_pixels) अणु
			अगर (i + 1 == width2) अणु
				/* क्रम jpg (binary) copy, this can occur
				 * अगर the file contains an odd number of bytes.
				 */
				inputfअगरo_send_data(
				    data2[0], 0);
			पूर्ण अन्यथा अणु
				inputfअगरo_send_data(
				    data2[0], data2[1]);
			पूर्ण
			/* Additional increment because we send 2 pixels */
			data2++;
			i++;
		पूर्ण अन्यथा अगर (two_ppc && is_legacy) अणु
			inputfअगरo_send_data_b(data2[0]);
		पूर्ण अन्यथा अणु
			inputfअगरo_send_data_a(data2[0]);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < hblank_cycles; i++)
		inputfअगरo_send_empty_token();
	inputfअगरo_send_eol();
	वापस;
पूर्ण

अटल व्योम
inputfअगरo_send_line(स्थिर अचिन्हित लघु *data,
		    अचिन्हित पूर्णांक width,
		    अचिन्हित पूर्णांक hblank_cycles,
		    अचिन्हित पूर्णांक marker_cycles,
		    अचिन्हित पूर्णांक two_ppc,
		    क्रमागत inputfअगरo_mipi_data_type type)
अणु
	निश्चित(data);
	inputfअगरo_send_line2(data, width, शून्य, 0,
			     hblank_cycles,
			     marker_cycles,
			     two_ppc,
			     type);
पूर्ण

/* Send a frame of data पूर्णांकo the input network via the GP FIFO.
 *  Parameters:
 *   - data: array of 16 bit values that contains all data क्रम the frame.
 *   - width: width of a line in number of subpixels, क्रम yuv420 it is the
 *            number of Y components per line.
 *   - height: height of the frame in number of lines.
 *   - ch_id: channel ID.
 *   - fmt_type: क्रमmat type.
 *   - hblank_cycles: length of horizontal blanking in cycles.
 *   - marker_cycles: number of empty cycles after start-of-line and beक्रमe
 *                    end-of-frame.
 *   - two_ppc: boolean, describes whether to send one or two pixels per घड़ी
 *              cycle. In this mode, we sent pixels N and N+1 in the same cycle,
 *              to IF_PRIM_A and IF_PRIM_B respectively. The caller must make
 *              sure the input data has been क्रमmatted correctly क्रम this.
 *              For example, क्रम RGB क्रमmats this means that unused values
 *              must be inserted.
 *   - yuv420: boolean, describes whether (non-legacy) yuv420 data is used. In
 *             this mode, the odd lines (1,3,5 etc) are half as दीर्घ as the
 *             even lines (2,4,6 etc).
 *             Note that the first line is odd (1) and the second line is even
 *             (2).
 *
 * This function करोes not करो any reordering of pixels, the caller must make
 * sure the data is in the righ क्रमmat. Please refer to the CSS receiver
 * करोcumentation क्रम details on the data क्रमmats.
 */

अटल व्योम inputfअगरo_send_frame(
    स्थिर अचिन्हित लघु *data,
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक ch_id,
    अचिन्हित पूर्णांक fmt_type,
    अचिन्हित पूर्णांक hblank_cycles,
    अचिन्हित पूर्णांक marker_cycles,
    अचिन्हित पूर्णांक two_ppc,
    क्रमागत inputfअगरo_mipi_data_type type)
अणु
	अचिन्हित पूर्णांक i;

	निश्चित(data);
	inputfअगरo_start_frame(ch_id, fmt_type);

	क्रम (i = 0; i < height; i++) अणु
		अगर ((type == inputfअगरo_mipi_data_type_yuv420) &&
		    (i & 1) == 1) अणु
			inputfअगरo_send_line(data, 2 * width,
					    hblank_cycles,
					    marker_cycles,
					    two_ppc, type);
			data += 2 * width;
		पूर्ण अन्यथा अणु
			inputfअगरo_send_line(data, width,
					    hblank_cycles,
					    marker_cycles,
					    two_ppc, type);
			data += width;
		पूर्ण
	पूर्ण
	inputfअगरo_end_frame(marker_cycles);
	वापस;
पूर्ण

अटल क्रमागत inputfअगरo_mipi_data_type inputfअगरo_determine_type(
    क्रमागत atomisp_input_क्रमmat input_क्रमmat)
अणु
	क्रमागत inputfअगरo_mipi_data_type type;

	type = inputfअगरo_mipi_data_type_regular;
	अगर (input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY) अणु
		type =
		    inputfअगरo_mipi_data_type_yuv420_legacy;
	पूर्ण अन्यथा अगर (input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_8  ||
		   input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_10 ||
		   input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_16) अणु
		type =
		    inputfअगरo_mipi_data_type_yuv420;
	पूर्ण अन्यथा अगर (input_क्रमmat >= ATOMISP_INPUT_FORMAT_RGB_444 &&
		   input_क्रमmat <= ATOMISP_INPUT_FORMAT_RGB_888) अणु
		type =
		    inputfअगरo_mipi_data_type_rgb;
	पूर्ण
	वापस type;
पूर्ण

अटल काष्ठा inputfअगरo_instance *inputfअगरo_get_inst(
    अचिन्हित पूर्णांक ch_id)
अणु
	वापस &inputfअगरo_inst_admin[ch_id];
पूर्ण

व्योम ia_css_inputfअगरo_send_input_frame(
    स्थिर अचिन्हित लघु *data,
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक ch_id,
    क्रमागत atomisp_input_क्रमmat input_क्रमmat,
    bool two_ppc)
अणु
	अचिन्हित पूर्णांक fmt_type, hblank_cycles, marker_cycles;
	क्रमागत inputfअगरo_mipi_data_type type;

	निश्चित(data);
	hblank_cycles = HBLANK_CYCLES;
	marker_cycles = MARKER_CYCLES;
	ia_css_isys_convert_stream_क्रमmat_to_mipi_क्रमmat(input_क्रमmat,
		MIPI_PREDICTOR_NONE,
		&fmt_type);

	type = inputfअगरo_determine_type(input_क्रमmat);

	inputfअगरo_send_frame(data, width, height,
			     ch_id, fmt_type, hblank_cycles, marker_cycles,
			     two_ppc, type);
पूर्ण

व्योम ia_css_inputfअगरo_start_frame(
    अचिन्हित पूर्णांक ch_id,
    क्रमागत atomisp_input_क्रमmat input_क्रमmat,
    bool two_ppc)
अणु
	काष्ठा inputfअगरo_instance *s2mi;

	s2mi = inputfअगरo_get_inst(ch_id);

	s2mi->ch_id = ch_id;
	ia_css_isys_convert_stream_क्रमmat_to_mipi_क्रमmat(input_क्रमmat,
		MIPI_PREDICTOR_NONE,
		&s2mi->fmt_type);
	s2mi->two_ppc = two_ppc;
	s2mi->type = inputfअगरo_determine_type(input_क्रमmat);
	s2mi->hblank_cycles = HBLANK_CYCLES;
	s2mi->marker_cycles = MARKER_CYCLES;
	s2mi->streaming = true;

	inputfअगरo_start_frame(ch_id, s2mi->fmt_type);
	वापस;
पूर्ण

व्योम ia_css_inputfअगरo_send_line(
    अचिन्हित पूर्णांक ch_id,
    स्थिर अचिन्हित लघु *data,
    अचिन्हित पूर्णांक width,
    स्थिर अचिन्हित लघु *data2,
    अचिन्हित पूर्णांक width2)
अणु
	काष्ठा inputfअगरo_instance *s2mi;

	निश्चित(data);
	निश्चित((data2) || (width2 == 0));
	s2mi = inputfअगरo_get_inst(ch_id);

	/* Set global variables that indicate channel_id and क्रमmat_type */
	inputfअगरo_curr_ch_id = (s2mi->ch_id) & _HIVE_ISP_CH_ID_MASK;
	inputfअगरo_curr_fmt_type = (s2mi->fmt_type) & _HIVE_ISP_FMT_TYPE_MASK;

	inputfअगरo_send_line2(data, width, data2, width2,
			     s2mi->hblank_cycles,
			     s2mi->marker_cycles,
			     s2mi->two_ppc,
			     s2mi->type);
पूर्ण

व्योम ia_css_inputfअगरo_send_embedded_line(
    अचिन्हित पूर्णांक	ch_id,
    क्रमागत atomisp_input_क्रमmat	data_type,
    स्थिर अचिन्हित लघु	*data,
    अचिन्हित पूर्णांक	width)
अणु
	काष्ठा inputfअगरo_instance *s2mi;
	अचिन्हित पूर्णांक fmt_type;

	निश्चित(data);
	s2mi = inputfअगरo_get_inst(ch_id);
	ia_css_isys_convert_stream_क्रमmat_to_mipi_क्रमmat(data_type,
		MIPI_PREDICTOR_NONE, &fmt_type);

	/* Set क्रमmat_type क्रम metadata line. */
	inputfअगरo_curr_fmt_type = fmt_type & _HIVE_ISP_FMT_TYPE_MASK;

	inputfअगरo_send_line(data, width, s2mi->hblank_cycles, s2mi->marker_cycles,
			    s2mi->two_ppc, inputfअगरo_mipi_data_type_regular);
पूर्ण

व्योम ia_css_inputfअगरo_end_frame(
    अचिन्हित पूर्णांक	ch_id)
अणु
	काष्ठा inputfअगरo_instance *s2mi;

	s2mi = inputfअगरo_get_inst(ch_id);

	/* Set global variables that indicate channel_id and क्रमmat_type */
	inputfअगरo_curr_ch_id = (s2mi->ch_id) & _HIVE_ISP_CH_ID_MASK;
	inputfअगरo_curr_fmt_type = (s2mi->fmt_type) & _HIVE_ISP_FMT_TYPE_MASK;

	/* Call existing HRT function */
	inputfअगरo_end_frame(s2mi->marker_cycles);

	s2mi->streaming = false;
	वापस;
पूर्ण
