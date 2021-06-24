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

#अगर_अघोषित __IA_CSS_TAGGER_COMMON_H__
#घोषणा __IA_CSS_TAGGER_COMMON_H__

#समावेश <प्रणाली_local.h>
#समावेश <type_support.h>

/**
 * @brief The tagger's circular buffer.
 *
 * Should be one less than NUM_CONTINUOUS_FRAMES in sh_css_पूर्णांकernal.h
 */
#घोषणा MAX_CB_ELEMS_FOR_TAGGER 14

/**
 * @brief Data काष्ठाure क्रम the tagger buffer element.
 */
प्रकार काष्ठा अणु
	u32 frame;	/* the frame value stored in the element */
	u32 param;	/* the param value stored in the element */
	u8 mark;	/* the mark on the element */
	u8 lock;	/* the lock on the element */
	u8 exp_id; /* exp_id of frame, क्रम debugging only */
पूर्ण ia_css_tagger_buf_sp_elem_t;

#पूर्ण_अगर /* __IA_CSS_TAGGER_COMMON_H__ */
