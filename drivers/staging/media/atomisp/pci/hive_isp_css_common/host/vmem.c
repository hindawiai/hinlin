<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2016, Intel Corporation.
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

#समावेश "isp.h"
#समावेश "vmem.h"
#समावेश "vmem_local.h"

#अगर !defined(HRT_MEMORY_ACCESS)
#समावेश "ia_css_device_access.h"
#पूर्ण_अगर
#समावेश "assert_support.h"

प्रकार अचिन्हित दीर्घ दीर्घ hive_uedge;
प्रकार hive_uedge *hive_wide;

/* Copied from SDK: sim_semantics.c */

/* subword bits move like this:         MSB[____xxxx____]LSB -> MSB[00000000xxxx]LSB */
#घोषणा SUBWORD(w, start, end)     (((w) & (((1ULL << ((end) - 1)) - 1) << 1 | 1)) >> (start))

/* inverse subword bits move like this: MSB[xxxx____xxxx]LSB -> MSB[xxxx0000xxxx]LSB */
#घोषणा INV_SUBWORD(w, start, end) ((w) & (~(((1ULL << ((end) - 1)) - 1) << 1 | 1) | ((1ULL << (start)) - 1)))

#घोषणा uedge_bits (8 * माप(hive_uedge))
#घोषणा move_lower_bits(target, target_bit, src, src_bit) move_subword(target, target_bit, src, 0, src_bit)
#घोषणा move_upper_bits(target, target_bit, src, src_bit) move_subword(target, target_bit, src, src_bit, uedge_bits)
#घोषणा move_word(target, target_bit, src) move_subword(target, target_bit, src, 0, uedge_bits)

अटल व्योम
move_subword(
    hive_uedge *target,
    अचिन्हित पूर्णांक target_bit,
    hive_uedge src,
    अचिन्हित पूर्णांक src_start,
    अचिन्हित पूर्णांक src_end)
अणु
	अचिन्हित पूर्णांक start_elem = target_bit / uedge_bits;
	अचिन्हित पूर्णांक start_bit  = target_bit % uedge_bits;
	अचिन्हित पूर्णांक subword_width = src_end - src_start;

	hive_uedge src_subword = SUBWORD(src, src_start, src_end);

	अगर (subword_width + start_bit > uedge_bits) अणु /* overlap */
		hive_uedge old_val1;
		hive_uedge old_val0 = INV_SUBWORD(target[start_elem], start_bit, uedge_bits);

		target[start_elem] = old_val0 | (src_subword << start_bit);
		old_val1 = INV_SUBWORD(target[start_elem + 1], 0,
				       subword_width + start_bit - uedge_bits);
		target[start_elem + 1] = old_val1 | (src_subword >> (uedge_bits - start_bit));
	पूर्ण अन्यथा अणु
		hive_uedge old_val = INV_SUBWORD(target[start_elem], start_bit,
						 start_bit + subword_width);

		target[start_elem] = old_val | (src_subword << start_bit);
	पूर्ण
पूर्ण

अटल व्योम
hive_sim_wide_unpack(
    hive_wide vector,
    hive_wide elem,
    hive_uपूर्णांक elem_bits,
    hive_uपूर्णांक index)
अणु
	/* poपूर्णांकers पूर्णांकo wide_type: */
	अचिन्हित पूर्णांक start_elem = (elem_bits * index) / uedge_bits;
	अचिन्हित पूर्णांक start_bit  = (elem_bits * index) % uedge_bits;
	अचिन्हित पूर्णांक end_elem   = (elem_bits * (index + 1) - 1) / uedge_bits;
	अचिन्हित पूर्णांक end_bit    = ((elem_bits * (index + 1) - 1) % uedge_bits) + 1;

	अगर (elem_bits == uedge_bits) अणु
		/* easy हाल क्रम speedup: */
		elem[0] = vector[index];
	पूर्ण अन्यथा अगर (start_elem == end_elem) अणु
		/* only one (<=64 bits) element needs to be (partly) copied: */
		move_subword(elem, 0, vector[start_elem], start_bit, end_bit);
	पूर्ण अन्यथा अणु
		/* general हाल: handles edge spanning हालs (includes >64bit elements) */
		अचिन्हित पूर्णांक bits_written = 0;
		अचिन्हित पूर्णांक i;

		move_upper_bits(elem, bits_written, vector[start_elem], start_bit);
		bits_written += (64 - start_bit);
		क्रम (i = start_elem + 1; i < end_elem; i++) अणु
			move_word(elem, bits_written, vector[i]);
			bits_written += uedge_bits;
		पूर्ण
		move_lower_bits(elem, bits_written, vector[end_elem], end_bit);
	पूर्ण
पूर्ण

अटल व्योम
hive_sim_wide_pack(
    hive_wide vector,
    hive_wide elem,
    hive_uपूर्णांक elem_bits,
    hive_uपूर्णांक index)
अणु
	/* poपूर्णांकers पूर्णांकo wide_type: */
	अचिन्हित पूर्णांक start_elem = (elem_bits * index) / uedge_bits;

	/* easy हाल क्रम speedup: */
	अगर (elem_bits == uedge_bits) अणु
		vector[start_elem] = elem[0];
	पूर्ण अन्यथा अगर (elem_bits > uedge_bits) अणु
		अचिन्हित पूर्णांक bits_to_ग_लिखो = elem_bits;
		अचिन्हित पूर्णांक start_bit = elem_bits * index;
		अचिन्हित पूर्णांक i = 0;

		क्रम (; bits_to_ग_लिखो > uedge_bits;
		     bits_to_ग_लिखो -= uedge_bits, i++, start_bit += uedge_bits) अणु
			move_word(vector, start_bit, elem[i]);
		पूर्ण
		move_lower_bits(vector, start_bit, elem[i], bits_to_ग_लिखो);
	पूर्ण अन्यथा अणु
		/* only one element needs to be (partly) copied: */
		move_lower_bits(vector, elem_bits * index, elem[0], elem_bits);
	पूर्ण
पूर्ण

अटल व्योम load_vector(
    स्थिर isp_ID_t		ID,
    t_vmem_elem		*to,
    स्थिर t_vmem_elem	*from)
अणु
	अचिन्हित पूर्णांक i;
	hive_uedge *data;
	अचिन्हित पूर्णांक size = माप(लघु) * ISP_NWAY;

	VMEM_ARRAY(v, 2 * ISP_NWAY); /* Need 2 vectors to work around vmem hss bug */
	निश्चित(ISP_BAMEM_BASE[ID] != (hrt_address) - 1);
#अगर !defined(HRT_MEMORY_ACCESS)
	ia_css_device_load(ISP_BAMEM_BASE[ID] + (अचिन्हित दीर्घ)from, &v[0][0], size);
#अन्यथा
	hrt_master_port_load(ISP_BAMEM_BASE[ID] + (अचिन्हित दीर्घ)from, &v[0][0], size);
#पूर्ण_अगर
	data = (hive_uedge *)v;
	क्रम (i = 0; i < ISP_NWAY; i++) अणु
		hive_uedge elem = 0;

		hive_sim_wide_unpack(data, &elem, ISP_VEC_ELEMBITS, i);
		to[i] = elem;
	पूर्ण
	udelay(1); /* Spend at least 1 cycles per vector */
पूर्ण

अटल व्योम store_vector(
    स्थिर isp_ID_t		ID,
    t_vmem_elem		*to,
    स्थिर t_vmem_elem	*from)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक size = माप(लघु) * ISP_NWAY;

	VMEM_ARRAY(v, 2 * ISP_NWAY); /* Need 2 vectors to work around vmem hss bug */
	//load_vector (&v[1][0], &to[ISP_NWAY]); /* Fetch the next vector, since it will be overwritten. */
	hive_uedge *data = (hive_uedge *)v;

	क्रम (i = 0; i < ISP_NWAY; i++) अणु
		hive_sim_wide_pack(data, (hive_wide)&from[i], ISP_VEC_ELEMBITS, i);
	पूर्ण
	निश्चित(ISP_BAMEM_BASE[ID] != (hrt_address) - 1);
#अगर !defined(HRT_MEMORY_ACCESS)
	ia_css_device_store(ISP_BAMEM_BASE[ID] + (अचिन्हित दीर्घ)to, &v, size);
#अन्यथा
	//hrt_mem_store (ISP, VMEM, (अचिन्हित)to, &v, siz); /* This will overग_लिखो the next vector as well */
	hrt_master_port_store(ISP_BAMEM_BASE[ID] + (अचिन्हित दीर्घ)to, &v, size);
#पूर्ण_अगर
	udelay(1); /* Spend at least 1 cycles per vector */
पूर्ण

व्योम isp_vmem_load(
    स्थिर isp_ID_t		ID,
    स्थिर t_vmem_elem	*from,
    t_vmem_elem		*to,
    अचिन्हित पूर्णांक elems) /* In t_vmem_elem */
अणु
	अचिन्हित पूर्णांक c;
	स्थिर t_vmem_elem *vp = from;

	निश्चित(ID < N_ISP_ID);
	निश्चित((अचिन्हित दीर्घ)from % ISP_VEC_ALIGN == 0);
	निश्चित(elems % ISP_NWAY == 0);
	क्रम (c = 0; c < elems; c += ISP_NWAY) अणु
		load_vector(ID, &to[c], vp);
		vp = (t_vmem_elem *)((अक्षर *)vp + ISP_VEC_ALIGN);
	पूर्ण
पूर्ण

व्योम isp_vmem_store(
    स्थिर isp_ID_t		ID,
    t_vmem_elem		*to,
    स्थिर t_vmem_elem	*from,
    अचिन्हित पूर्णांक elems) /* In t_vmem_elem */
अणु
	अचिन्हित पूर्णांक c;
	t_vmem_elem *vp = to;

	निश्चित(ID < N_ISP_ID);
	निश्चित((अचिन्हित दीर्घ)to % ISP_VEC_ALIGN == 0);
	निश्चित(elems % ISP_NWAY == 0);
	क्रम (c = 0; c < elems; c += ISP_NWAY) अणु
		store_vector(ID, vp, &from[c]);
		vp = (t_vmem_elem *)((अक्षर *)vp + ISP_VEC_ALIGN);
	पूर्ण
पूर्ण

व्योम isp_vmem_2d_load(
    स्थिर isp_ID_t		ID,
    स्थिर t_vmem_elem	*from,
    t_vmem_elem		*to,
    अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक stride_to,  /* In t_vmem_elem */

    अचिन्हित stride_from /* In t_vmem_elem */)
अणु
	अचिन्हित पूर्णांक h;

	निश्चित(ID < N_ISP_ID);
	निश्चित((अचिन्हित दीर्घ)from % ISP_VEC_ALIGN == 0);
	निश्चित(width % ISP_NWAY == 0);
	निश्चित(stride_from % ISP_NWAY == 0);
	क्रम (h = 0; h < height; h++) अणु
		अचिन्हित पूर्णांक c;
		स्थिर t_vmem_elem *vp = from;

		क्रम (c = 0; c < width; c += ISP_NWAY) अणु
			load_vector(ID, &to[stride_to * h + c], vp);
			vp = (t_vmem_elem *)((अक्षर *)vp + ISP_VEC_ALIGN);
		पूर्ण
		from = (स्थिर t_vmem_elem *)((स्थिर अक्षर *)from + stride_from / ISP_NWAY *
					     ISP_VEC_ALIGN);
	पूर्ण
पूर्ण

व्योम isp_vmem_2d_store(
    स्थिर isp_ID_t		ID,
    t_vmem_elem		*to,
    स्थिर t_vmem_elem	*from,
    अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक stride_to,  /* In t_vmem_elem */

    अचिन्हित stride_from /* In t_vmem_elem */)
अणु
	अचिन्हित पूर्णांक h;

	निश्चित(ID < N_ISP_ID);
	निश्चित((अचिन्हित दीर्घ)to % ISP_VEC_ALIGN == 0);
	निश्चित(width % ISP_NWAY == 0);
	निश्चित(stride_to % ISP_NWAY == 0);
	क्रम (h = 0; h < height; h++) अणु
		अचिन्हित पूर्णांक c;
		t_vmem_elem *vp = to;

		क्रम (c = 0; c < width; c += ISP_NWAY) अणु
			store_vector(ID, vp, &from[stride_from * h + c]);
			vp = (t_vmem_elem *)((अक्षर *)vp + ISP_VEC_ALIGN);
		पूर्ण
		to = (t_vmem_elem *)((अक्षर *)to + stride_to / ISP_NWAY * ISP_VEC_ALIGN);
	पूर्ण
पूर्ण
