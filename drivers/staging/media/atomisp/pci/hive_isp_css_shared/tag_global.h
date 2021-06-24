<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __TAG_GLOBAL_H_INCLUDED__
#घोषणा __TAG_GLOBAL_H_INCLUDED__

/* offsets क्रम encoding/decoding the tag पूर्णांकo an uपूर्णांक32_t */

#घोषणा TAG_CAP	1
#घोषणा TAG_EXP	2

#घोषणा TAG_NUM_CAPTURES_SIGN_SHIFT	 6
#घोषणा TAG_OFFSET_SIGN_SHIFT		 7
#घोषणा TAG_NUM_CAPTURES_SHIFT		 8
#घोषणा TAG_OFFSET_SHIFT		16
#घोषणा TAG_SKIP_SHIFT			24

#घोषणा TAG_EXP_ID_SHIFT		 8

/* Data काष्ठाure containing the tagging inक्रमmation which is used in
 * continuous mode to specअगरy which frames should be captured.
 * num_captures		The number of RAW frames to be processed to
 *                      YUV. Setting this to -1 will make continuous
 *                      capture run until it is stopped.
 * skip			Skip N frames in between captures. This can be
 *                      used to select a slower capture frame rate than
 *                      the sensor output frame rate.
 * offset		Start the RAW-to-YUV processing at RAW buffer
 *                      with this offset. This allows the user to
 *                      process RAW frames that were captured in the
 *                      past or future.
 * exp_id		Exposure id of the RAW frame to tag.
 *
 * NOTE: Either exp_id = 0 or all other fields are 0
 *	 (so yeah, this could be a जोड़)
 */

काष्ठा sh_css_tag_descr अणु
	पूर्णांक num_captures;
	अचिन्हित पूर्णांक skip;
	पूर्णांक offset;
	अचिन्हित पूर्णांक exp_id;
पूर्ण;

#पूर्ण_अगर /* __TAG_GLOBAL_H_INCLUDED__ */
