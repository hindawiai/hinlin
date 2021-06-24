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

#समावेश "ia_css_circbuf.h"

#समावेश <निश्चित_support.h>

/**********************************************************************
 *
 * Forward declarations.
 *
 **********************************************************************/
/*
 * @brief Read the oldest element from the circular buffer.
 * Read the oldest element WITHOUT checking whehter the
 * circular buffer is empty or not. The oldest element is
 * also हटाओd out from the circular buffer.
 *
 * @param cb The poपूर्णांकer to the circular buffer.
 *
 * @वापस the oldest element.
 */
अटल अंतरभूत ia_css_circbuf_elem_t
ia_css_circbuf_पढ़ो(ia_css_circbuf_t *cb);

/*
 * @brief Shअगरt a chunk of elements in the circular buffer.
 * A chunk of elements (i.e. the ones from the "start" position
 * to the "chunk_src" position) are shअगरted in the circular buffer,
 * aदीर्घ the direction of new elements coming.
 *
 * @param cb	     The poपूर्णांकer to the circular buffer.
 * @param chunk_src  The position at which the first element in the chunk is.
 * @param chunk_dest The position to which the first element in the chunk would be shअगरt.
 */
अटल अंतरभूत व्योम ia_css_circbuf_shअगरt_chunk(ia_css_circbuf_t *cb,
	u32 chunk_src,
	uपूर्णांक32_t chunk_dest);

/*
 * @brief Get the "val" field in the element.
 *
 * @param elem The poपूर्णांकer to the element.
 *
 * @वापस the "val" field.
 */
अटल अंतरभूत uपूर्णांक32_t
ia_css_circbuf_elem_get_val(ia_css_circbuf_elem_t *elem);

/**********************************************************************
 *
 * Non-अंतरभूत functions.
 *
 **********************************************************************/
/*
 * @brief Create the circular buffer.
 * Refer to "ia_css_circbuf.h" क्रम details.
 */
व्योम
ia_css_circbuf_create(ia_css_circbuf_t *cb,
		      ia_css_circbuf_elem_t *elems,
		      ia_css_circbuf_desc_t *desc)
अणु
	u32 i;

	OP___निश्चित(desc);

	cb->desc = desc;
	/* Initialize to शेषs */
	cb->desc->start = 0;
	cb->desc->end = 0;
	cb->desc->step = 0;

	क्रम (i = 0; i < cb->desc->size; i++)
		ia_css_circbuf_elem_init(&elems[i]);

	cb->elems = elems;
पूर्ण

/*
 * @brief Destroy the circular buffer.
 * Refer to "ia_css_circbuf.h" क्रम details.
 */
व्योम ia_css_circbuf_destroy(ia_css_circbuf_t *cb)
अणु
	cb->desc = शून्य;

	cb->elems = शून्य;
पूर्ण

/*
 * @brief Pop a value out of the circular buffer.
 * Refer to "ia_css_circbuf.h" क्रम details.
 */
uपूर्णांक32_t ia_css_circbuf_pop(ia_css_circbuf_t *cb)
अणु
	u32 ret;
	ia_css_circbuf_elem_t elem;

	निश्चित(!ia_css_circbuf_is_empty(cb));

	/* पढ़ो an element from the buffer */
	elem = ia_css_circbuf_पढ़ो(cb);
	ret = ia_css_circbuf_elem_get_val(&elem);
	वापस ret;
पूर्ण

/*
 * @brief Extract a value out of the circular buffer.
 * Refer to "ia_css_circbuf.h" क्रम details.
 */
uपूर्णांक32_t ia_css_circbuf_extract(ia_css_circbuf_t *cb, पूर्णांक offset)
अणु
	पूर्णांक max_offset;
	u32 val;
	u32 pos;
	u32 src_pos;
	u32 dest_pos;

	/* get the maximum offest */
	max_offset = ia_css_circbuf_get_offset(cb, cb->desc->start, cb->desc->end);
	max_offset--;

	/*
	 * Step 1: When the target element is at the "start" position.
	 */
	अगर (offset == 0) अणु
		val = ia_css_circbuf_pop(cb);
		वापस val;
	पूर्ण

	/*
	 * Step 2: When the target element is out of the range.
	 */
	अगर (offset > max_offset) अणु
		val = 0;
		वापस val;
	पूर्ण

	/*
	 * Step 3: When the target element is between the "start" and
	 * "end" position.
	 */
	/* get the position of the target element */
	pos = ia_css_circbuf_get_pos_at_offset(cb, cb->desc->start, offset);

	/* get the value from the target element */
	val = ia_css_circbuf_elem_get_val(&cb->elems[pos]);

	/* shअगरt the elements */
	src_pos = ia_css_circbuf_get_pos_at_offset(cb, pos, -1);
	dest_pos = pos;
	ia_css_circbuf_shअगरt_chunk(cb, src_pos, dest_pos);

	वापस val;
पूर्ण

/*
 * @brief Peek an element from the circular buffer.
 * Refer to "ia_css_circbuf.h" क्रम details.
 */
uपूर्णांक32_t ia_css_circbuf_peek(ia_css_circbuf_t *cb, पूर्णांक offset)
अणु
	पूर्णांक pos;

	pos = ia_css_circbuf_get_pos_at_offset(cb, cb->desc->end, offset);

	/* get the value at the position */
	वापस cb->elems[pos].val;
पूर्ण

/*
 * @brief Get the value of an element from the circular buffer.
 * Refer to "ia_css_circbuf.h" क्रम details.
 */
uपूर्णांक32_t ia_css_circbuf_peek_from_start(ia_css_circbuf_t *cb, पूर्णांक offset)
अणु
	पूर्णांक pos;

	pos = ia_css_circbuf_get_pos_at_offset(cb, cb->desc->start, offset);

	/* get the value at the position */
	वापस cb->elems[pos].val;
पूर्ण

/* @brief increase size of a circular buffer.
 * Use 'CAUTION' beक्रमe using this function. This was added to
 * support / fix issue with increasing size क्रम tagger only
 * Please refer to "ia_css_circbuf.h" क्रम details.
 */
bool ia_css_circbuf_increase_size(
    ia_css_circbuf_t *cb,
    अचिन्हित पूर्णांक sz_delta,
    ia_css_circbuf_elem_t *elems)
अणु
	u8 curr_size;
	u8 curr_end;
	अचिन्हित पूर्णांक i = 0;

	अगर (!cb || sz_delta == 0)
		वापस false;

	curr_size = cb->desc->size;
	curr_end = cb->desc->end;
	/* We assume cb was pre defined as global to allow
	 * increase in size */
	/* FM: are we sure this cannot cause size to become too big? */
	अगर (((uपूर्णांक8_t)(cb->desc->size + (uपूर्णांक8_t)sz_delta) > cb->desc->size) &&
	    ((uपूर्णांक8_t)sz_delta == sz_delta))
		cb->desc->size += (uपूर्णांक8_t)sz_delta;
	अन्यथा
		वापस false; /* overflow in size */

	/* If elems are passed update them अन्यथा we assume its been taken
	 * care beक्रमe calling this function */
	अगर (elems) अणु
		/* cb element array size will not be increased dynamically,
		 * but poपूर्णांकers to new elements can be added at the end
		 * of existing pre defined cb element array of
		 * size >= new size अगर not alपढ़ोy added */
		क्रम (i = curr_size; i <  cb->desc->size; i++)
			cb->elems[i] = elems[i - curr_size];
	पूर्ण
	/* Fix Start / End */
	अगर (curr_end < cb->desc->start) अणु
		अगर (curr_end == 0) अणु
			/* Easily fix End */
			cb->desc->end = curr_size;
		पूर्ण अन्यथा अणु
			/* Move elements and fix Start*/
			ia_css_circbuf_shअगरt_chunk(cb,
						   curr_size - 1,
						   curr_size + sz_delta - 1);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/****************************************************************
 *
 * Inline functions.
 *
 ****************************************************************/
/*
 * @brief Get the "val" field in the element.
 * Refer to "Forward declarations" क्रम details.
 */
अटल अंतरभूत uपूर्णांक32_t
ia_css_circbuf_elem_get_val(ia_css_circbuf_elem_t *elem)
अणु
	वापस elem->val;
पूर्ण

/*
 * @brief Read the oldest element from the circular buffer.
 * Refer to "Forward declarations" क्रम details.
 */
अटल अंतरभूत ia_css_circbuf_elem_t
ia_css_circbuf_पढ़ो(ia_css_circbuf_t *cb)
अणु
	ia_css_circbuf_elem_t elem;

	/* get the element from the target position */
	elem = cb->elems[cb->desc->start];

	/* clear the target position */
	ia_css_circbuf_elem_init(&cb->elems[cb->desc->start]);

	/* adjust the "start" position */
	cb->desc->start = ia_css_circbuf_get_pos_at_offset(cb, cb->desc->start, 1);
	वापस elem;
पूर्ण

/*
 * @brief Shअगरt a chunk of elements in the circular buffer.
 * Refer to "Forward declarations" क्रम details.
 */
अटल अंतरभूत व्योम
ia_css_circbuf_shअगरt_chunk(ia_css_circbuf_t *cb,
			   u32 chunk_src, uपूर्णांक32_t chunk_dest)
अणु
	पूर्णांक chunk_offset;
	पूर्णांक chunk_sz;
	पूर्णांक i;

	/* get the chunk offset and size */
	chunk_offset = ia_css_circbuf_get_offset(cb,
		       chunk_src, chunk_dest);
	chunk_sz = ia_css_circbuf_get_offset(cb, cb->desc->start, chunk_src) + 1;

	/* shअगरt each element to its terminal position */
	क्रम (i = 0; i < chunk_sz; i++) अणु
		/* copy the element from the source to the destination */
		ia_css_circbuf_elem_cpy(&cb->elems[chunk_src],
					&cb->elems[chunk_dest]);

		/* clear the source position */
		ia_css_circbuf_elem_init(&cb->elems[chunk_src]);

		/* adjust the source/terminal positions */
		chunk_src = ia_css_circbuf_get_pos_at_offset(cb, chunk_src, -1);
		chunk_dest = ia_css_circbuf_get_pos_at_offset(cb, chunk_dest, -1);
	पूर्ण

	/* adjust the index "start" */
	cb->desc->start = ia_css_circbuf_get_pos_at_offset(cb, cb->desc->start,
			  chunk_offset);
पूर्ण
