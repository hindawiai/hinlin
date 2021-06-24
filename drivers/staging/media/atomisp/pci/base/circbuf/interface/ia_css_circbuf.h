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

#अगर_अघोषित _IA_CSS_CIRCBUF_H
#घोषणा _IA_CSS_CIRCBUF_H

#समावेश <sp.h>
#समावेश <type_support.h>
#समावेश <math_support.h>
#समावेश <निश्चित_support.h>
#समावेश <platक्रमm_support.h>
#समावेश "ia_css_circbuf_comm.h"
#समावेश "ia_css_circbuf_desc.h"

/****************************************************************
 *
 * Data काष्ठाures.
 *
 ****************************************************************/
/**
 * @brief Data काष्ठाure क्रम the circular buffer.
 */
प्रकार काष्ठा ia_css_circbuf_s ia_css_circbuf_t;
काष्ठा ia_css_circbuf_s अणु
	ia_css_circbuf_desc_t *desc;    /* Poपूर्णांकer to the descriptor of the circbuf */
	ia_css_circbuf_elem_t *elems;	/* an array of elements    */
पूर्ण;

/**
 * @brief Create the circular buffer.
 *
 * @param cb	The poपूर्णांकer to the circular buffer.
 * @param elems	An array of elements.
 * @param desc	The descriptor set to the size using ia_css_circbuf_desc_init().
 */
व्योम ia_css_circbuf_create(
    ia_css_circbuf_t *cb,
    ia_css_circbuf_elem_t *elems,
    ia_css_circbuf_desc_t *desc);

/**
 * @brief Destroy the circular buffer.
 *
 * @param cb The poपूर्णांकer to the circular buffer.
 */
व्योम ia_css_circbuf_destroy(
    ia_css_circbuf_t *cb);

/**
 * @brief Pop a value out of the circular buffer.
 * Get a value at the head of the circular buffer.
 * The user should call "ia_css_circbuf_is_empty()"
 * to aव्योम accessing to an empty buffer.
 *
 * @param cb	The poपूर्णांकer to the circular buffer.
 *
 * @वापस the pop-out value.
 */
uपूर्णांक32_t ia_css_circbuf_pop(
    ia_css_circbuf_t *cb);

/**
 * @brief Extract a value out of the circular buffer.
 * Get a value at an arbitrary poistion in the circular
 * buffer. The user should call "ia_css_circbuf_is_empty()"
 * to aव्योम accessing to an empty buffer.
 *
 * @param cb	 The poपूर्णांकer to the circular buffer.
 * @param offset The offset from "start" to the target position.
 *
 * @वापस the extracted value.
 */
uपूर्णांक32_t ia_css_circbuf_extract(
    ia_css_circbuf_t *cb,
    पूर्णांक offset);

/****************************************************************
 *
 * Inline functions.
 *
 ****************************************************************/
/**
 * @brief Set the "val" field in the element.
 *
 * @param elem The poपूर्णांकer to the element.
 * @param val  The value to be set.
 */
अटल अंतरभूत व्योम ia_css_circbuf_elem_set_val(
    ia_css_circbuf_elem_t *elem,
    uपूर्णांक32_t val)
अणु
	OP___निश्चित(elem);

	elem->val = val;
पूर्ण

/**
 * @brief Initialize the element.
 *
 * @param elem The poपूर्णांकer to the element.
 */
अटल अंतरभूत व्योम ia_css_circbuf_elem_init(
    ia_css_circbuf_elem_t *elem)
अणु
	OP___निश्चित(elem);
	ia_css_circbuf_elem_set_val(elem, 0);
पूर्ण

/**
 * @brief Copy an element.
 *
 * @param src  The element as the copy source.
 * @param dest The element as the copy destination.
 */
अटल अंतरभूत व्योम ia_css_circbuf_elem_cpy(
    ia_css_circbuf_elem_t *src,
    ia_css_circbuf_elem_t *dest)
अणु
	OP___निश्चित(src);
	OP___निश्चित(dest);

	ia_css_circbuf_elem_set_val(dest, src->val);
पूर्ण

/**
 * @brief Get position in the circular buffer.
 *
 * @param cb		The poपूर्णांकer to the circular buffer.
 * @param base		The base position.
 * @param offset	The offset.
 *
 * @वापस the position at offset.
 */
अटल अंतरभूत uपूर्णांक8_t ia_css_circbuf_get_pos_at_offset(
    ia_css_circbuf_t *cb,
    u32 base,
    पूर्णांक offset)
अणु
	u8 dest;

	OP___निश्चित(cb);
	OP___निश्चित(cb->desc);
	OP___निश्चित(cb->desc->size > 0);

	/* step 1: adjudst the offset  */
	जबतक (offset < 0) अणु
		offset += cb->desc->size;
	पूर्ण

	/* step 2: shअगरt and round by the upper limit */
	dest = OP_std_modadd(base, offset, cb->desc->size);

	वापस dest;
पूर्ण

/**
 * @brief Get the offset between two positions in the circular buffer.
 * Get the offset from the source position to the terminal position,
 * aदीर्घ the direction in which the new elements come in.
 *
 * @param cb		The poपूर्णांकer to the circular buffer.
 * @param src_pos	The source position.
 * @param dest_pos	The terminal position.
 *
 * @वापस the offset.
 */
अटल अंतरभूत पूर्णांक ia_css_circbuf_get_offset(
    ia_css_circbuf_t *cb,
    u32 src_pos,
    uपूर्णांक32_t dest_pos)
अणु
	पूर्णांक offset;

	OP___निश्चित(cb);
	OP___निश्चित(cb->desc);

	offset = (पूर्णांक)(dest_pos - src_pos);
	offset += (offset < 0) ? cb->desc->size : 0;

	वापस offset;
पूर्ण

/**
 * @brief Get the maximum number of elements.
 *
 * @param cb The poपूर्णांकer to the circular buffer.
 *
 * @वापस the maximum number of elements.
 *
 * TODO: Test this API.
 */
अटल अंतरभूत uपूर्णांक32_t ia_css_circbuf_get_size(
    ia_css_circbuf_t *cb)
अणु
	OP___निश्चित(cb);
	OP___निश्चित(cb->desc);

	वापस cb->desc->size;
पूर्ण

/**
 * @brief Get the number of available elements.
 *
 * @param cb The poपूर्णांकer to the circular buffer.
 *
 * @वापस the number of available elements.
 */
अटल अंतरभूत uपूर्णांक32_t ia_css_circbuf_get_num_elems(
    ia_css_circbuf_t *cb)
अणु
	पूर्णांक num;

	OP___निश्चित(cb);
	OP___निश्चित(cb->desc);

	num = ia_css_circbuf_get_offset(cb, cb->desc->start, cb->desc->end);

	वापस (uपूर्णांक32_t)num;
पूर्ण

/**
 * @brief Test अगर the circular buffer is empty.
 *
 * @param cb	The poपूर्णांकer to the circular buffer.
 *
 * @वापस
 *	- true when it is empty.
 *	- false when it is not empty.
 */
अटल अंतरभूत bool ia_css_circbuf_is_empty(
    ia_css_circbuf_t *cb)
अणु
	OP___निश्चित(cb);
	OP___निश्चित(cb->desc);

	वापस ia_css_circbuf_desc_is_empty(cb->desc);
पूर्ण

/**
 * @brief Test अगर the circular buffer is full.
 *
 * @param cb	The poपूर्णांकer to the circular buffer.
 *
 * @वापस
 *	- true when it is full.
 *	- false when it is not full.
 */
अटल अंतरभूत bool ia_css_circbuf_is_full(ia_css_circbuf_t *cb)
अणु
	OP___निश्चित(cb);
	OP___निश्चित(cb->desc);

	वापस ia_css_circbuf_desc_is_full(cb->desc);
पूर्ण

/**
 * @brief Write a new element पूर्णांकo the circular buffer.
 * Write a new element WITHOUT checking whether the
 * circular buffer is full or not. So it also overग_लिखोs
 * the oldest element when the buffer is full.
 *
 * @param cb	The poपूर्णांकer to the circular buffer.
 * @param elem	The new element.
 */
अटल अंतरभूत व्योम ia_css_circbuf_ग_लिखो(
    ia_css_circbuf_t *cb,
    ia_css_circbuf_elem_t elem)
अणु
	OP___निश्चित(cb);
	OP___निश्चित(cb->desc);

	/* Cannot जारी as the queue is full*/
	निश्चित(!ia_css_circbuf_is_full(cb));

	ia_css_circbuf_elem_cpy(&elem, &cb->elems[cb->desc->end]);

	cb->desc->end = ia_css_circbuf_get_pos_at_offset(cb, cb->desc->end, 1);
पूर्ण

/**
 * @brief Push a value in the circular buffer.
 * Put a new value at the tail of the circular buffer.
 * The user should call "ia_css_circbuf_is_full()"
 * to aव्योम accessing to a full buffer.
 *
 * @param cb	The poपूर्णांकer to the circular buffer.
 * @param val	The value to be pushed in.
 */
अटल अंतरभूत व्योम ia_css_circbuf_push(
    ia_css_circbuf_t *cb,
    uपूर्णांक32_t val)
अणु
	ia_css_circbuf_elem_t elem;

	OP___निश्चित(cb);

	/* set up an element */
	ia_css_circbuf_elem_init(&elem);
	ia_css_circbuf_elem_set_val(&elem, val);

	/* ग_लिखो the element पूर्णांकo the buffer */
	ia_css_circbuf_ग_लिखो(cb, elem);
पूर्ण

/**
 * @brief Get the number of मुक्त elements.
 *
 * @param cb The poपूर्णांकer to the circular buffer.
 *
 * @वापस: The number of मुक्त elements.
 */
अटल अंतरभूत uपूर्णांक32_t ia_css_circbuf_get_मुक्त_elems(
    ia_css_circbuf_t *cb)
अणु
	OP___निश्चित(cb);
	OP___निश्चित(cb->desc);

	वापस ia_css_circbuf_desc_get_मुक्त_elems(cb->desc);
पूर्ण

/**
 * @brief Peek an element in Circular Buffer.
 *
 * @param cb	 The poपूर्णांकer to the circular buffer.
 * @param offset Offset to the element.
 *
 * @वापस the elements value.
 */
uपूर्णांक32_t ia_css_circbuf_peek(
    ia_css_circbuf_t *cb,
    पूर्णांक offset);

/**
 * @brief Get an element in Circular Buffer.
 *
 * @param cb	 The poपूर्णांकer to the circular buffer.
 * @param offset Offset to the element.
 *
 * @वापस the elements value.
 */
uपूर्णांक32_t ia_css_circbuf_peek_from_start(
    ia_css_circbuf_t *cb,
    पूर्णांक offset);

/**
 * @brief Increase Size of a Circular Buffer.
 * Use 'CAUTION' beक्रमe using this function, This was added to
 * support / fix issue with increasing size क्रम tagger only
 *
 * @param cb The poपूर्णांकer to the circular buffer.
 * @param sz_delta delta increase क्रम new size
 * @param elems (optional) poपूर्णांकers to new additional elements
 *		cb element array size will not be increased dynamically,
 *		but new elements should be added at the end to existing
 *		cb element array which अगर of max_size >= new size
 *
 * @वापस	true on successfully increasing the size
 *			false on failure
 */
bool ia_css_circbuf_increase_size(
    ia_css_circbuf_t *cb,
    अचिन्हित पूर्णांक sz_delta,
    ia_css_circbuf_elem_t *elems);

#पूर्ण_अगर /*_IA_CSS_CIRCBUF_H */
