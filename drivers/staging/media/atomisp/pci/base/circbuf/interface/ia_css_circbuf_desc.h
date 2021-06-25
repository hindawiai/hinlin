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

#अगर_अघोषित _IA_CSS_CIRCBUF_DESC_H_
#घोषणा _IA_CSS_CIRCBUF_DESC_H_

#समावेश <type_support.h>
#समावेश <math_support.h>
#समावेश <platक्रमm_support.h>
#समावेश <sp.h>
#समावेश "ia_css_circbuf_comm.h"
/****************************************************************
 *
 * Inline functions.
 *
 ****************************************************************/
/**
 * @brief Test अगर the circular buffer is empty.
 *
 * @param cb_desc The poपूर्णांकer to the circular buffer descriptor.
 *
 * @वापस
 *	- true when it is empty.
 *	- false when it is not empty.
 */
अटल अंतरभूत bool ia_css_circbuf_desc_is_empty(
    ia_css_circbuf_desc_t *cb_desc)
अणु
	OP___निश्चित(cb_desc);
	वापस (cb_desc->end == cb_desc->start);
पूर्ण

/**
 * @brief Test अगर the circular buffer descriptor is full.
 *
 * @param cb_desc	The poपूर्णांकer to the circular buffer
 *			descriptor.
 *
 * @वापस
 *	- true when it is full.
 *	- false when it is not full.
 */
अटल अंतरभूत bool ia_css_circbuf_desc_is_full(
    ia_css_circbuf_desc_t *cb_desc)
अणु
	OP___निश्चित(cb_desc);
	वापस (OP_std_modadd(cb_desc->end, 1, cb_desc->size) == cb_desc->start);
पूर्ण

/**
 * @brief Initialize the circular buffer descriptor
 *
 * @param cb_desc	The poपूर्णांकer circular buffer descriptor
 * @param size		The size of the circular buffer
 */
अटल अंतरभूत व्योम ia_css_circbuf_desc_init(
    ia_css_circbuf_desc_t *cb_desc,
    पूर्णांक8_t size)
अणु
	OP___निश्चित(cb_desc);
	cb_desc->size = size;
पूर्ण

/**
 * @brief Get a position in the circular buffer descriptor.
 *
 * @param cb     The poपूर्णांकer to the circular buffer descriptor.
 * @param base   The base position.
 * @param offset The offset.
 *
 * @वापस the position in the circular buffer descriptor.
 */
अटल अंतरभूत uपूर्णांक8_t ia_css_circbuf_desc_get_pos_at_offset(
    ia_css_circbuf_desc_t *cb_desc,
    u32 base,
    पूर्णांक offset)
अणु
	u8 dest;

	OP___निश्चित(cb_desc);
	OP___निश्चित(cb_desc->size > 0);

	/* step 1: adjust the offset  */
	जबतक (offset < 0) अणु
		offset += cb_desc->size;
	पूर्ण

	/* step 2: shअगरt and round by the upper limit */
	dest = OP_std_modadd(base, offset, cb_desc->size);

	वापस dest;
पूर्ण

/**
 * @brief Get the offset between two positions in the circular buffer
 * descriptor.
 * Get the offset from the source position to the terminal position,
 * aदीर्घ the direction in which the new elements come in.
 *
 * @param cb_desc	The poपूर्णांकer to the circular buffer descriptor.
 * @param src_pos	The source position.
 * @param dest_pos	The terminal position.
 *
 * @वापस the offset.
 */
अटल अंतरभूत पूर्णांक ia_css_circbuf_desc_get_offset(
    ia_css_circbuf_desc_t *cb_desc,
    u32 src_pos,
    uपूर्णांक32_t dest_pos)
अणु
	पूर्णांक offset;

	OP___निश्चित(cb_desc);

	offset = (पूर्णांक)(dest_pos - src_pos);
	offset += (offset < 0) ? cb_desc->size : 0;

	वापस offset;
पूर्ण

/**
 * @brief Get the number of available elements.
 *
 * @param cb_desc The poपूर्णांकer to the circular buffer.
 *
 * @वापस The number of available elements.
 */
अटल अंतरभूत uपूर्णांक32_t ia_css_circbuf_desc_get_num_elems(
    ia_css_circbuf_desc_t *cb_desc)
अणु
	पूर्णांक num;

	OP___निश्चित(cb_desc);

	num = ia_css_circbuf_desc_get_offset(cb_desc,
					     cb_desc->start,
					     cb_desc->end);

	वापस (uपूर्णांक32_t)num;
पूर्ण

/**
 * @brief Get the number of मुक्त elements.
 *
 * @param cb_desc The poपूर्णांकer to the circular buffer descriptor.
 *
 * @वापस: The number of मुक्त elements.
 */
अटल अंतरभूत uपूर्णांक32_t ia_css_circbuf_desc_get_मुक्त_elems(
    ia_css_circbuf_desc_t *cb_desc)
अणु
	u32 num;

	OP___निश्चित(cb_desc);

	num = ia_css_circbuf_desc_get_offset(cb_desc,
					     cb_desc->start,
					     cb_desc->end);

	वापस (cb_desc->size - num);
पूर्ण
#पूर्ण_अगर /*_IA_CSS_CIRCBUF_DESC_H_ */
