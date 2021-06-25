<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित _IA_CSS_INPUTFIFO_H
#घोषणा _IA_CSS_INPUTFIFO_H

#समावेश <sp.h>
#समावेश <isp.h>

#समावेश "ia_css_stream_format.h"

/* SP access */
व्योम ia_css_inputfअगरo_send_input_frame(
    स्थिर अचिन्हित लघु	*data,
    अचिन्हित पूर्णांक	width,
    अचिन्हित पूर्णांक	height,
    अचिन्हित पूर्णांक	ch_id,
    क्रमागत atomisp_input_क्रमmat	input_क्रमmat,
    bool			two_ppc);

व्योम ia_css_inputfअगरo_start_frame(
    अचिन्हित पूर्णांक	ch_id,
    क्रमागत atomisp_input_क्रमmat	input_क्रमmat,
    bool			two_ppc);

व्योम ia_css_inputfअगरo_send_line(
    अचिन्हित पूर्णांक	ch_id,
    स्थिर अचिन्हित लघु	*data,
    अचिन्हित पूर्णांक	width,
    स्थिर अचिन्हित लघु	*data2,
    अचिन्हित पूर्णांक	width2);

व्योम ia_css_inputfअगरo_send_embedded_line(
    अचिन्हित पूर्णांक	ch_id,
    क्रमागत atomisp_input_क्रमmat	data_type,
    स्थिर अचिन्हित लघु	*data,
    अचिन्हित पूर्णांक	width);

व्योम ia_css_inputfअगरo_end_frame(
    अचिन्हित पूर्णांक	ch_id);

#पूर्ण_अगर /* _IA_CSS_INPUTFIFO_H */
