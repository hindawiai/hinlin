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

#समावेश "hmm.h"

#समावेश "type_support.h"
#समावेश "queue_access.h"
#समावेश "ia_css_circbuf.h"
#समावेश "sp.h"
#समावेश "assert_support.h"

पूर्णांक ia_css_queue_load(
    काष्ठा ia_css_queue *rdesc,
    ia_css_circbuf_desc_t *cb_desc,
    uपूर्णांक32_t ignore_desc_flags)
अणु
	अगर (!rdesc || !cb_desc)
		वापस -EINVAL;

	अगर (rdesc->location == IA_CSS_QUEUE_LOC_SP) अणु
		निश्चित(ignore_desc_flags <= QUEUE_IGNORE_DESC_FLAGS_MAX);

		अगर (0 == (ignore_desc_flags & QUEUE_IGNORE_SIZE_FLAG)) अणु
			cb_desc->size = sp_dmem_load_uपूर्णांक8(rdesc->proc_id,
							   rdesc->desc.remote.cb_desc_addr
							   + दुरत्व(ia_css_circbuf_desc_t, size));

			अगर (cb_desc->size == 0) अणु
				/* Adding back the workaround which was हटाओd
				   जबतक refactoring queues. When पढ़ोing size
				   through sp_dmem_load_*, someबार we get back
				   the value as zero. This causes भागision by 0
				   exception as the size is used in a modular
				   भागision operation. */
				वापस -गलत_तर्क;
			पूर्ण
		पूर्ण

		अगर (0 == (ignore_desc_flags & QUEUE_IGNORE_START_FLAG))
			cb_desc->start = sp_dmem_load_uपूर्णांक8(rdesc->proc_id,
							    rdesc->desc.remote.cb_desc_addr
							    + दुरत्व(ia_css_circbuf_desc_t, start));

		अगर (0 == (ignore_desc_flags & QUEUE_IGNORE_END_FLAG))
			cb_desc->end = sp_dmem_load_uपूर्णांक8(rdesc->proc_id,
							  rdesc->desc.remote.cb_desc_addr
							  + दुरत्व(ia_css_circbuf_desc_t, end));

		अगर (0 == (ignore_desc_flags & QUEUE_IGNORE_STEP_FLAG))
			cb_desc->step = sp_dmem_load_uपूर्णांक8(rdesc->proc_id,
							   rdesc->desc.remote.cb_desc_addr
							   + दुरत्व(ia_css_circbuf_desc_t, step));

	पूर्ण अन्यथा अगर (rdesc->location == IA_CSS_QUEUE_LOC_HOST) अणु
		/* करोing DMA transfer of entire काष्ठाure */
		hmm_load(rdesc->desc.remote.cb_desc_addr,
			  (व्योम *)cb_desc,
			  माप(ia_css_circbuf_desc_t));
	पूर्ण अन्यथा अगर (rdesc->location == IA_CSS_QUEUE_LOC_ISP) अणु
		/* Not supported yet */
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ia_css_queue_store(
    काष्ठा ia_css_queue *rdesc,
    ia_css_circbuf_desc_t *cb_desc,
    uपूर्णांक32_t ignore_desc_flags)
अणु
	अगर (!rdesc || !cb_desc)
		वापस -EINVAL;

	अगर (rdesc->location == IA_CSS_QUEUE_LOC_SP) अणु
		निश्चित(ignore_desc_flags <= QUEUE_IGNORE_DESC_FLAGS_MAX);

		अगर (0 == (ignore_desc_flags & QUEUE_IGNORE_SIZE_FLAG))
			sp_dmem_store_uपूर्णांक8(rdesc->proc_id,
					    rdesc->desc.remote.cb_desc_addr
					    + दुरत्व(ia_css_circbuf_desc_t, size),
					    cb_desc->size);

		अगर (0 == (ignore_desc_flags & QUEUE_IGNORE_START_FLAG))
			sp_dmem_store_uपूर्णांक8(rdesc->proc_id,
					    rdesc->desc.remote.cb_desc_addr
					    + दुरत्व(ia_css_circbuf_desc_t, start),
					    cb_desc->start);

		अगर (0 == (ignore_desc_flags & QUEUE_IGNORE_END_FLAG))
			sp_dmem_store_uपूर्णांक8(rdesc->proc_id,
					    rdesc->desc.remote.cb_desc_addr
					    + दुरत्व(ia_css_circbuf_desc_t, end),
					    cb_desc->end);

		अगर (0 == (ignore_desc_flags & QUEUE_IGNORE_STEP_FLAG))
			sp_dmem_store_uपूर्णांक8(rdesc->proc_id,
					    rdesc->desc.remote.cb_desc_addr
					    + दुरत्व(ia_css_circbuf_desc_t, step),
					    cb_desc->step);
	पूर्ण अन्यथा अगर (rdesc->location == IA_CSS_QUEUE_LOC_HOST) अणु
		/* करोing DMA transfer of entire काष्ठाure */
		hmm_store(rdesc->desc.remote.cb_desc_addr,
			   (व्योम *)cb_desc,
			   माप(ia_css_circbuf_desc_t));
	पूर्ण अन्यथा अगर (rdesc->location == IA_CSS_QUEUE_LOC_ISP) अणु
		/* Not supported yet */
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ia_css_queue_item_load(
    काष्ठा ia_css_queue *rdesc,
    u8 position,
    ia_css_circbuf_elem_t *item)
अणु
	अगर (!rdesc || !item)
		वापस -EINVAL;

	अगर (rdesc->location == IA_CSS_QUEUE_LOC_SP) अणु
		sp_dmem_load(rdesc->proc_id,
			     rdesc->desc.remote.cb_elems_addr
			     + position * माप(ia_css_circbuf_elem_t),
			     item,
			     माप(ia_css_circbuf_elem_t));
	पूर्ण अन्यथा अगर (rdesc->location == IA_CSS_QUEUE_LOC_HOST) अणु
		hmm_load(rdesc->desc.remote.cb_elems_addr
			  + position * माप(ia_css_circbuf_elem_t),
			  (व्योम *)item,
			  माप(ia_css_circbuf_elem_t));
	पूर्ण अन्यथा अगर (rdesc->location == IA_CSS_QUEUE_LOC_ISP) अणु
		/* Not supported yet */
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ia_css_queue_item_store(
    काष्ठा ia_css_queue *rdesc,
    u8 position,
    ia_css_circbuf_elem_t *item)
अणु
	अगर (!rdesc || !item)
		वापस -EINVAL;

	अगर (rdesc->location == IA_CSS_QUEUE_LOC_SP) अणु
		sp_dmem_store(rdesc->proc_id,
			      rdesc->desc.remote.cb_elems_addr
			      + position * माप(ia_css_circbuf_elem_t),
			      item,
			      माप(ia_css_circbuf_elem_t));
	पूर्ण अन्यथा अगर (rdesc->location == IA_CSS_QUEUE_LOC_HOST) अणु
		hmm_store(rdesc->desc.remote.cb_elems_addr
			   + position * माप(ia_css_circbuf_elem_t),
			   (व्योम *)item,
			   माप(ia_css_circbuf_elem_t));
	पूर्ण अन्यथा अगर (rdesc->location == IA_CSS_QUEUE_LOC_ISP) अणु
		/* Not supported yet */
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण
