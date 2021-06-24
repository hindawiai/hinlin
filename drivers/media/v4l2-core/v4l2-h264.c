<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * V4L2 H264 helpers.
 *
 * Copyright (C) 2019 Collabora, Ltd.
 *
 * Author: Boris Brezillon <boris.brezillon@collabora.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/sort.h>

#समावेश <media/v4l2-h264.h>

/**
 * v4l2_h264_init_reflist_builder() - Initialize a P/B0/B1 reference list
 *				      builder
 *
 * @b: the builder context to initialize
 * @dec_params: decode parameters control
 * @sps: SPS control
 * @dpb: DPB to use when creating the reference list
 */
व्योम
v4l2_h264_init_reflist_builder(काष्ठा v4l2_h264_reflist_builder *b,
		स्थिर काष्ठा v4l2_ctrl_h264_decode_params *dec_params,
		स्थिर काष्ठा v4l2_ctrl_h264_sps *sps,
		स्थिर काष्ठा v4l2_h264_dpb_entry dpb[V4L2_H264_NUM_DPB_ENTRIES])
अणु
	पूर्णांक cur_frame_num, max_frame_num;
	अचिन्हित पूर्णांक i;

	max_frame_num = 1 << (sps->log2_max_frame_num_minus4 + 4);
	cur_frame_num = dec_params->frame_num;

	स_रखो(b, 0, माप(*b));
	अगर (!(dec_params->flags & V4L2_H264_DECODE_PARAM_FLAG_FIELD_PIC))
		b->cur_pic_order_count = min(dec_params->bottom_field_order_cnt,
					     dec_params->top_field_order_cnt);
	अन्यथा अगर (dec_params->flags & V4L2_H264_DECODE_PARAM_FLAG_BOTTOM_FIELD)
		b->cur_pic_order_count = dec_params->bottom_field_order_cnt;
	अन्यथा
		b->cur_pic_order_count = dec_params->top_field_order_cnt;

	क्रम (i = 0; i < V4L2_H264_NUM_DPB_ENTRIES; i++) अणु
		u32 pic_order_count;

		अगर (!(dpb[i].flags & V4L2_H264_DPB_ENTRY_FLAG_ACTIVE))
			जारी;

		b->refs[i].pic_num = dpb[i].pic_num;
		अगर (dpb[i].flags & V4L2_H264_DPB_ENTRY_FLAG_LONG_TERM)
			b->refs[i].दीर्घterm = true;

		/*
		 * Handle frame_num wraparound as described in section
		 * '8.2.4.1 Decoding process for picture numbers' of the spec.
		 * TODO: This logic will have to be adjusted when we start
		 * supporting पूर्णांकerlaced content.
		 */
		अगर (dpb[i].frame_num > cur_frame_num)
			b->refs[i].frame_num = (पूर्णांक)dpb[i].frame_num -
					       max_frame_num;
		अन्यथा
			b->refs[i].frame_num = dpb[i].frame_num;

		अगर (dpb[i].fields == V4L2_H264_FRAME_REF)
			pic_order_count = min(dpb[i].top_field_order_cnt,
					      dpb[i].bottom_field_order_cnt);
		अन्यथा अगर (dpb[i].fields & V4L2_H264_BOTTOM_FIELD_REF)
			pic_order_count = dpb[i].bottom_field_order_cnt;
		अन्यथा
			pic_order_count = dpb[i].top_field_order_cnt;

		b->refs[i].pic_order_count = pic_order_count;
		b->unordered_reflist[b->num_valid] = i;
		b->num_valid++;
	पूर्ण

	क्रम (i = b->num_valid; i < ARRAY_SIZE(b->unordered_reflist); i++)
		b->unordered_reflist[i] = i;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_h264_init_reflist_builder);

अटल पूर्णांक v4l2_h264_p_ref_list_cmp(स्थिर व्योम *ptra, स्थिर व्योम *ptrb,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा v4l2_h264_reflist_builder *builder = data;
	u8 idxa, idxb;

	idxa = *((u8 *)ptra);
	idxb = *((u8 *)ptrb);

	अगर (WARN_ON(idxa >= V4L2_H264_NUM_DPB_ENTRIES ||
		    idxb >= V4L2_H264_NUM_DPB_ENTRIES))
		वापस 1;

	अगर (builder->refs[idxa].दीर्घterm != builder->refs[idxb].दीर्घterm) अणु
		/* Short term pics first. */
		अगर (!builder->refs[idxa].दीर्घterm)
			वापस -1;
		अन्यथा
			वापस 1;
	पूर्ण

	/*
	 * Short term pics in descending pic num order, दीर्घ term ones in
	 * ascending order.
	 */
	अगर (!builder->refs[idxa].दीर्घterm)
		वापस builder->refs[idxb].frame_num <
		       builder->refs[idxa].frame_num ?
		       -1 : 1;

	वापस builder->refs[idxa].pic_num < builder->refs[idxb].pic_num ?
	       -1 : 1;
पूर्ण

अटल पूर्णांक v4l2_h264_b0_ref_list_cmp(स्थिर व्योम *ptra, स्थिर व्योम *ptrb,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा v4l2_h264_reflist_builder *builder = data;
	s32 poca, pocb;
	u8 idxa, idxb;

	idxa = *((u8 *)ptra);
	idxb = *((u8 *)ptrb);

	अगर (WARN_ON(idxa >= V4L2_H264_NUM_DPB_ENTRIES ||
		    idxb >= V4L2_H264_NUM_DPB_ENTRIES))
		वापस 1;

	अगर (builder->refs[idxa].दीर्घterm != builder->refs[idxb].दीर्घterm) अणु
		/* Short term pics first. */
		अगर (!builder->refs[idxa].दीर्घterm)
			वापस -1;
		अन्यथा
			वापस 1;
	पूर्ण

	/* Long term pics in ascending pic num order. */
	अगर (builder->refs[idxa].दीर्घterm)
		वापस builder->refs[idxa].pic_num <
		       builder->refs[idxb].pic_num ?
		       -1 : 1;

	poca = builder->refs[idxa].pic_order_count;
	pocb = builder->refs[idxb].pic_order_count;

	/*
	 * Short term pics with POC < cur POC first in POC descending order
	 * followed by लघु term pics with POC > cur POC in POC ascending
	 * order.
	 */
	अगर ((poca < builder->cur_pic_order_count) !=
	     (pocb < builder->cur_pic_order_count))
		वापस poca < pocb ? -1 : 1;
	अन्यथा अगर (poca < builder->cur_pic_order_count)
		वापस pocb < poca ? -1 : 1;

	वापस poca < pocb ? -1 : 1;
पूर्ण

अटल पूर्णांक v4l2_h264_b1_ref_list_cmp(स्थिर व्योम *ptra, स्थिर व्योम *ptrb,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा v4l2_h264_reflist_builder *builder = data;
	s32 poca, pocb;
	u8 idxa, idxb;

	idxa = *((u8 *)ptra);
	idxb = *((u8 *)ptrb);

	अगर (WARN_ON(idxa >= V4L2_H264_NUM_DPB_ENTRIES ||
		    idxb >= V4L2_H264_NUM_DPB_ENTRIES))
		वापस 1;

	अगर (builder->refs[idxa].दीर्घterm != builder->refs[idxb].दीर्घterm) अणु
		/* Short term pics first. */
		अगर (!builder->refs[idxa].दीर्घterm)
			वापस -1;
		अन्यथा
			वापस 1;
	पूर्ण

	/* Long term pics in ascending pic num order. */
	अगर (builder->refs[idxa].दीर्घterm)
		वापस builder->refs[idxa].pic_num <
		       builder->refs[idxb].pic_num ?
		       -1 : 1;

	poca = builder->refs[idxa].pic_order_count;
	pocb = builder->refs[idxb].pic_order_count;

	/*
	 * Short term pics with POC > cur POC first in POC ascending order
	 * followed by लघु term pics with POC < cur POC in POC descending
	 * order.
	 */
	अगर ((poca < builder->cur_pic_order_count) !=
	    (pocb < builder->cur_pic_order_count))
		वापस pocb < poca ? -1 : 1;
	अन्यथा अगर (poca < builder->cur_pic_order_count)
		वापस pocb < poca ? -1 : 1;

	वापस poca < pocb ? -1 : 1;
पूर्ण

/**
 * v4l2_h264_build_p_ref_list() - Build the P reference list
 *
 * @builder: reference list builder context
 * @reflist: 16-bytes array used to store the P reference list. Each entry
 *	     is an index in the DPB
 *
 * This functions builds the P reference lists. This procedure is describe in
 * section '8.2.4 Decoding process for reference picture lists construction'
 * of the H264 spec. This function can be used by H264 decoder drivers that
 * need to pass a P reference list to the hardware.
 */
व्योम
v4l2_h264_build_p_ref_list(स्थिर काष्ठा v4l2_h264_reflist_builder *builder,
			   u8 *reflist)
अणु
	स_नकल(reflist, builder->unordered_reflist,
	       माप(builder->unordered_reflist[0]) * builder->num_valid);
	sort_r(reflist, builder->num_valid, माप(*reflist),
	       v4l2_h264_p_ref_list_cmp, शून्य, builder);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_h264_build_p_ref_list);

/**
 * v4l2_h264_build_b_ref_lists() - Build the B0/B1 reference lists
 *
 * @builder: reference list builder context
 * @b0_reflist: 16-bytes array used to store the B0 reference list. Each entry
 *		is an index in the DPB
 * @b1_reflist: 16-bytes array used to store the B1 reference list. Each entry
 *		is an index in the DPB
 *
 * This functions builds the B0/B1 reference lists. This procedure is described
 * in section '8.2.4 Decoding process for reference picture lists construction'
 * of the H264 spec. This function can be used by H264 decoder drivers that
 * need to pass B0/B1 reference lists to the hardware.
 */
व्योम
v4l2_h264_build_b_ref_lists(स्थिर काष्ठा v4l2_h264_reflist_builder *builder,
			    u8 *b0_reflist, u8 *b1_reflist)
अणु
	स_नकल(b0_reflist, builder->unordered_reflist,
	       माप(builder->unordered_reflist[0]) * builder->num_valid);
	sort_r(b0_reflist, builder->num_valid, माप(*b0_reflist),
	       v4l2_h264_b0_ref_list_cmp, शून्य, builder);

	स_नकल(b1_reflist, builder->unordered_reflist,
	       माप(builder->unordered_reflist[0]) * builder->num_valid);
	sort_r(b1_reflist, builder->num_valid, माप(*b1_reflist),
	       v4l2_h264_b1_ref_list_cmp, शून्य, builder);

	अगर (builder->num_valid > 1 &&
	    !स_भेद(b1_reflist, b0_reflist, builder->num_valid))
		swap(b1_reflist[0], b1_reflist[1]);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_h264_build_b_ref_lists);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("V4L2 H264 Helpers");
MODULE_AUTHOR("Boris Brezillon <boris.brezillon@collabora.com>");
