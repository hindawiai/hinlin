<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2013
 * Author: Hugues Fruchet <hugues.fruchet@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित DELTA_MJPEG_H
#घोषणा DELTA_MJPEG_H

#समावेश "delta.h"

काष्ठा mjpeg_component अणु
	अचिन्हित पूर्णांक id;/* 1=Y, 2=Cb, 3=Cr, 4=L, 5=Q */
	अचिन्हित पूर्णांक h_sampling_factor;
	अचिन्हित पूर्णांक v_sampling_factor;
	अचिन्हित पूर्णांक quant_table_index;
पूर्ण;

#घोषणा MJPEG_MAX_COMPONENTS 5

काष्ठा mjpeg_header अणु
	अचिन्हित पूर्णांक length;
	अचिन्हित पूर्णांक sample_precision;
	अचिन्हित पूर्णांक frame_width;
	अचिन्हित पूर्णांक frame_height;
	अचिन्हित पूर्णांक nb_of_components;
	काष्ठा mjpeg_component components[MJPEG_MAX_COMPONENTS];
पूर्ण;

पूर्णांक delta_mjpeg_पढ़ो_header(काष्ठा delta_ctx *pctx,
			    अचिन्हित अक्षर *data, अचिन्हित पूर्णांक size,
			    काष्ठा mjpeg_header *header,
			    अचिन्हित पूर्णांक *data_offset);

#पूर्ण_अगर /* DELTA_MJPEG_H */
