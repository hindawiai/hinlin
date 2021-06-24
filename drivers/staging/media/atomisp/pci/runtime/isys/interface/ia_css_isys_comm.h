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

#अगर_अघोषित __IA_CSS_ISYS_COMM_H
#घोषणा __IA_CSS_ISYS_COMM_H

#समावेश <type_support.h>
#समावेश <input_प्रणाली.h>

#अगर_घोषित ISP2401
#समावेश <platक्रमm_support.h>		/* अंतरभूत */
#समावेश <input_प्रणाली_global.h>
#समावेश <ia_css_stream_खुला.h>	/* IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH */

#घोषणा SH_CSS_NODES_PER_THREAD		2
#घोषणा SH_CSS_MAX_ISYS_CHANNEL_NODES	(SH_CSS_MAX_SP_THREADS * SH_CSS_NODES_PER_THREAD)

/*
 * a) ia_css_isys_stream_h & ia_css_isys_stream_cfg_t come from host.
 *
 * b) Here it is better  to use actual काष्ठाures क्रम stream handle
 * instead of opaque handles. Otherwise, we need to have another
 * communication channel to पूर्णांकerpret that opaque handle(this handle is
 * मुख्यtained by host and needs to be populated to sp क्रम every stream खोलो)
 * */
प्रकार भव_input_प्रणाली_stream_t		*ia_css_isys_stream_h;
प्रकार भव_input_प्रणाली_stream_cfg_t	ia_css_isys_stream_cfg_t;

/*
 * error check क्रम ISYS APIs.
 * */
प्रकार bool ia_css_isys_error_t;

अटल अंतरभूत uपूर्णांक32_t ia_css_isys_generate_stream_id(
    u32	sp_thपढ़ो_id,
    uपूर्णांक32_t	stream_id)
अणु
	वापस sp_thपढ़ो_id * IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH + stream_id;
पूर्ण

#पूर्ण_अगर  /* ISP2401*/
#पूर्ण_अगर  /*_IA_CSS_ISYS_COMM_H */
