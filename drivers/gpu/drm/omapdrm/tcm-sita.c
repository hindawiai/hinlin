<शैली गुरु>
/*
 * SImple Tiler Allocator (SiTA): 2D and 1D allocation(reservation) algorithm
 *
 * Authors: Ravi Ramachandra <r.ramachandra@ti.com>,
 *          Lajos Molnar <molnar@ti.com>
 *          Andy Gross <andy.gross@ti.com>
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This package is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/slab.h>
#समावेश "tcm.h"

अटल अचिन्हित दीर्घ mask[8];
/*
 * pos		position in biपंचांगap
 * w		width in slots
 * h		height in slots
 * map		ptr to biपंचांगap
 * stride		slots in a row
 */
अटल व्योम मुक्त_slots(अचिन्हित दीर्घ pos, u16 w, u16 h,
		अचिन्हित दीर्घ *map, u16 stride)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < h; i++, pos += stride)
		biपंचांगap_clear(map, pos, w);
पूर्ण

/*
 * w		width in slots
 * pos		ptr to position
 * map		ptr to biपंचांगap
 * num_bits	number of bits in biपंचांगap
 */
अटल पूर्णांक r2l_b2t_1d(u16 w, अचिन्हित दीर्घ *pos, अचिन्हित दीर्घ *map,
		माप_प्रकार num_bits)
अणु
	अचिन्हित दीर्घ search_count = 0;
	अचिन्हित दीर्घ bit;
	bool area_found = false;

	*pos = num_bits - w;

	जबतक (search_count < num_bits) अणु
		bit = find_next_bit(map, num_bits, *pos);

		अगर (bit - *pos >= w) अणु
			/* found a दीर्घ enough मुक्त area */
			biपंचांगap_set(map, *pos, w);
			area_found = true;
			अवरोध;
		पूर्ण

		search_count = num_bits - bit + w;
		*pos = bit - w;
	पूर्ण

	वापस (area_found) ? 0 : -ENOMEM;
पूर्ण

/*
 * w = width in slots
 * h = height in slots
 * a = align in slots	(mask, 2^n-1, 0 is unaligned)
 * offset = offset in bytes from 4KiB
 * pos = position in biपंचांगap क्रम buffer
 * map = biपंचांगap ptr
 * num_bits = size of biपंचांगap
 * stride = bits in one row of container
 */
अटल पूर्णांक l2r_t2b(u16 w, u16 h, u16 a, s16 offset,
		अचिन्हित दीर्घ *pos, अचिन्हित दीर्घ slot_bytes,
		अचिन्हित दीर्घ *map, माप_प्रकार num_bits, माप_प्रकार slot_stride)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ index;
	bool area_मुक्त = false;
	अचिन्हित दीर्घ slots_per_band = PAGE_SIZE / slot_bytes;
	अचिन्हित दीर्घ bit_offset = (offset > 0) ? offset / slot_bytes : 0;
	अचिन्हित दीर्घ curr_bit = bit_offset;

	/* reset alignment to 1 अगर we are matching a specअगरic offset */
	/* adjust alignment - 1 to get to the क्रमmat expected in biपंचांगaps */
	a = (offset > 0) ? 0 : a - 1;

	/* FIXME Return error अगर slots_per_band > stride */

	जबतक (curr_bit < num_bits) अणु
		*pos = biपंचांगap_find_next_zero_area(map, num_bits, curr_bit, w,
				a);

		/* skip क्रमward अगर we are not at right offset */
		अगर (bit_offset > 0 && (*pos % slots_per_band != bit_offset)) अणु
			curr_bit = ALIGN(*pos, slots_per_band) + bit_offset;
			जारी;
		पूर्ण

		/* skip क्रमward to next row अगर we overlap end of row */
		अगर ((*pos % slot_stride) + w > slot_stride) अणु
			curr_bit = ALIGN(*pos, slot_stride) + bit_offset;
			जारी;
		पूर्ण

		/* TODO: Handle overlapping 4K boundaries */

		/* अवरोध out of look अगर we will go past end of container */
		अगर ((*pos + slot_stride * h) > num_bits)
			अवरोध;

		/* generate mask that represents out matching pattern */
		biपंचांगap_clear(mask, 0, slot_stride);
		biपंचांगap_set(mask, (*pos % BITS_PER_LONG), w);

		/* assume the area is मुक्त until we find an overlap */
		area_मुक्त = true;

		/* check subsequent rows to see अगर complete area is मुक्त */
		क्रम (i = 1; i < h; i++) अणु
			index = *pos / BITS_PER_LONG + i * 8;
			अगर (biपंचांगap_पूर्णांकersects(&map[index], mask,
				(*pos % BITS_PER_LONG) + w)) अणु
				area_मुक्त = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (area_मुक्त)
			अवरोध;

		/* go क्रमward past this match */
		अगर (bit_offset > 0)
			curr_bit = ALIGN(*pos, slots_per_band) + bit_offset;
		अन्यथा
			curr_bit = *pos + a + 1;
	पूर्ण

	अगर (area_मुक्त) अणु
		/* set area as in-use. iterate over rows */
		क्रम (i = 0, index = *pos; i < h; i++, index += slot_stride)
			biपंचांगap_set(map, index, w);
	पूर्ण

	वापस (area_मुक्त) ? 0 : -ENOMEM;
पूर्ण

अटल s32 sita_reserve_1d(काष्ठा tcm *tcm, u32 num_slots,
			   काष्ठा tcm_area *area)
अणु
	अचिन्हित दीर्घ pos;
	पूर्णांक ret;

	spin_lock(&(tcm->lock));
	ret = r2l_b2t_1d(num_slots, &pos, tcm->biपंचांगap, tcm->map_size);
	अगर (!ret) अणु
		area->p0.x = pos % tcm->width;
		area->p0.y = pos / tcm->width;
		area->p1.x = (pos + num_slots - 1) % tcm->width;
		area->p1.y = (pos + num_slots - 1) / tcm->width;
	पूर्ण
	spin_unlock(&(tcm->lock));

	वापस ret;
पूर्ण

अटल s32 sita_reserve_2d(काष्ठा tcm *tcm, u16 h, u16 w, u16 align,
				s16 offset, u16 slot_bytes,
				काष्ठा tcm_area *area)
अणु
	अचिन्हित दीर्घ pos;
	पूर्णांक ret;

	spin_lock(&(tcm->lock));
	ret = l2r_t2b(w, h, align, offset, &pos, slot_bytes, tcm->biपंचांगap,
			tcm->map_size, tcm->width);

	अगर (!ret) अणु
		area->p0.x = pos % tcm->width;
		area->p0.y = pos / tcm->width;
		area->p1.x = area->p0.x + w - 1;
		area->p1.y = area->p0.y + h - 1;
	पूर्ण
	spin_unlock(&(tcm->lock));

	वापस ret;
पूर्ण

अटल व्योम sita_deinit(काष्ठा tcm *tcm)
अणु
	kमुक्त(tcm);
पूर्ण

अटल s32 sita_मुक्त(काष्ठा tcm *tcm, काष्ठा tcm_area *area)
अणु
	अचिन्हित दीर्घ pos;
	u16 w, h;

	pos = area->p0.x + area->p0.y * tcm->width;
	अगर (area->is2d) अणु
		w = area->p1.x - area->p0.x + 1;
		h = area->p1.y - area->p0.y + 1;
	पूर्ण अन्यथा अणु
		w = area->p1.x + area->p1.y * tcm->width - pos + 1;
		h = 1;
	पूर्ण

	spin_lock(&(tcm->lock));
	मुक्त_slots(pos, w, h, tcm->biपंचांगap, tcm->width);
	spin_unlock(&(tcm->lock));
	वापस 0;
पूर्ण

काष्ठा tcm *sita_init(u16 width, u16 height)
अणु
	काष्ठा tcm *tcm;
	माप_प्रकार map_size = BITS_TO_LONGS(width*height) * माप(अचिन्हित दीर्घ);

	अगर (width == 0 || height == 0)
		वापस शून्य;

	tcm = kzalloc(माप(*tcm) + map_size, GFP_KERNEL);
	अगर (!tcm)
		जाओ error;

	/* Updating the poपूर्णांकers to SiTA implementation APIs */
	tcm->height = height;
	tcm->width = width;
	tcm->reserve_2d = sita_reserve_2d;
	tcm->reserve_1d = sita_reserve_1d;
	tcm->मुक्त = sita_मुक्त;
	tcm->deinit = sita_deinit;

	spin_lock_init(&tcm->lock);
	tcm->biपंचांगap = (अचिन्हित दीर्घ *)(tcm + 1);
	biपंचांगap_clear(tcm->biपंचांगap, 0, width*height);

	tcm->map_size = width*height;

	वापस tcm;

error:
	वापस शून्य;
पूर्ण
