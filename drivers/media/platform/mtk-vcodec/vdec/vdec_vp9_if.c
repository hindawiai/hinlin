<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Daniel Hsiao <daniel.hsiao@mediatek.com>
 *	Kai-Sean Yang <kai-sean.yang@mediatek.com>
 *	Tअगरfany Lin <tअगरfany.lin@mediatek.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/delay.h>
#समावेश <linux/समय.स>

#समावेश "../mtk_vcodec_intr.h"
#समावेश "../vdec_drv_base.h"
#समावेश "../vdec_vpu_if.h"

#घोषणा VP9_SUPER_FRAME_BS_SZ 64
#घोषणा MAX_VP9_DPB_SIZE	9

#घोषणा REFS_PER_FRAME 3
#घोषणा MAX_NUM_REF_FRAMES 8
#घोषणा VP9_MAX_FRM_BUF_NUM 9
#घोषणा VP9_MAX_FRM_BUF_NODE_NUM (VP9_MAX_FRM_BUF_NUM * 2)
#घोषणा VP9_SEG_ID_SZ 0x12000

/**
 * काष्ठा vp9_dram_buf - contains buffer info क्रम vpu
 * @va : cpu address
 * @pa : iova address
 * @sz : buffer size
 * @padding : क्रम 64 bytes alignment
 */
काष्ठा vp9_dram_buf अणु
	अचिन्हित दीर्घ va;
	अचिन्हित दीर्घ pa;
	अचिन्हित पूर्णांक sz;
	अचिन्हित पूर्णांक padding;
पूर्ण;

/**
 * काष्ठा vp9_fb_info - contains frame buffer info
 * @fb : frmae buffer
 * @reserved : reserved field used by vpu
 */
काष्ठा vp9_fb_info अणु
	काष्ठा vdec_fb *fb;
	अचिन्हित पूर्णांक reserved[32];
पूर्ण;

/**
 * काष्ठा vp9_ref_cnt_buf - contains reference buffer inक्रमmation
 * @buf : referenced frame buffer
 * @ref_cnt : referenced frame buffer's reference count.
 *	When reference count=0, हटाओ it from reference list
 */
काष्ठा vp9_ref_cnt_buf अणु
	काष्ठा vp9_fb_info buf;
	अचिन्हित पूर्णांक ref_cnt;
पूर्ण;

/**
 * काष्ठा vp9_ref_buf - contains current frame's reference buffer inक्रमmation
 * @buf : reference buffer
 * @idx : reference buffer index to frm_bufs
 * @reserved : reserved field used by vpu
 */
काष्ठा vp9_ref_buf अणु
	काष्ठा vp9_fb_info *buf;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक reserved[6];
पूर्ण;

/**
 * काष्ठा vp9_sf_ref_fb - contains frame buffer info
 * @fb : super frame reference frame buffer
 * @used : this reference frame info entry is used
 * @padding : क्रम 64 bytes size align
 */
काष्ठा vp9_sf_ref_fb अणु
	काष्ठा vdec_fb fb;
	पूर्णांक used;
	पूर्णांक padding;
पूर्ण;

/*
 * काष्ठा vdec_vp9_vsi - shared buffer between host and VPU firmware
 *	AP-W/R : AP is ग_लिखोr/पढ़ोer on this item
 *	VPU-W/R: VPU is ग_लिखो/पढ़ोer on this item
 * @sf_bs_buf : super frame backup buffer (AP-W, VPU-R)
 * @sf_ref_fb : record supoer frame reference buffer inक्रमmation
 *	(AP-R/W, VPU-R/W)
 * @sf_next_ref_fb_idx : next available super frame (AP-W, VPU-R)
 * @sf_frm_cnt : super frame count, filled by vpu (AP-R, VPU-W)
 * @sf_frm_offset : super frame offset, filled by vpu (AP-R, VPU-W)
 * @sf_frm_sz : super frame size, filled by vpu (AP-R, VPU-W)
 * @sf_frm_idx : current super frame (AP-R, VPU-W)
 * @sf_init : inक्रमm super frame info alपढ़ोy parsed by vpu (AP-R, VPU-W)
 * @fb : capture buffer (AP-W, VPU-R)
 * @bs : bs buffer (AP-W, VPU-R)
 * @cur_fb : current show capture buffer (AP-R/W, VPU-R/W)
 * @pic_w : picture width (AP-R, VPU-W)
 * @pic_h : picture height (AP-R, VPU-W)
 * @buf_w : codec width (AP-R, VPU-W)
 * @buf_h : coded height (AP-R, VPU-W)
 * @buf_sz_y_bs : ufo compressed y plane size (AP-R, VPU-W)
 * @buf_sz_c_bs : ufo compressed cbcr plane size (AP-R, VPU-W)
 * @buf_len_sz_y : size used to store y plane ufo info (AP-R, VPU-W)
 * @buf_len_sz_c : size used to store cbcr plane ufo info (AP-R, VPU-W)

 * @profile : profile sparsed from vpu (AP-R, VPU-W)
 * @show_frame : [BIT(0)] display this frame or not (AP-R, VPU-W)
 *	[BIT(1)] reset segment data or not (AP-R, VPU-W)
 *	[BIT(2)] trig decoder hardware or not (AP-R, VPU-W)
 *	[BIT(3)] ask VPU to set bits(0~4) accordingly (AP-W, VPU-R)
 *	[BIT(4)] करो not reset segment data beक्रमe every frame (AP-R, VPU-W)
 * @show_existing_frame : inक्रमm this frame is show existing frame
 *	(AP-R, VPU-W)
 * @frm_to_show_idx : index to show frame (AP-R, VPU-W)

 * @refresh_frm_flags : indicate when frame need to refine reference count
 *	(AP-R, VPU-W)
 * @resolution_changed : resolution change in this frame (AP-R, VPU-W)

 * @frm_bufs : मुख्यtain reference buffer info (AP-R/W, VPU-R/W)
 * @ref_frm_map : मुख्यtain reference buffer map info (AP-R/W, VPU-R/W)
 * @new_fb_idx : index to frm_bufs array (AP-R, VPU-W)
 * @frm_num : decoded frame number, include sub-frame count (AP-R, VPU-W)
 * @mv_buf : motion vector working buffer (AP-W, VPU-R)
 * @frm_refs : मुख्यtain three reference buffer info (AP-R/W, VPU-R/W)
 * @seg_id_buf : segmentation map working buffer (AP-W, VPU-R)
 */
काष्ठा vdec_vp9_vsi अणु
	अचिन्हित अक्षर sf_bs_buf[VP9_SUPER_FRAME_BS_SZ];
	काष्ठा vp9_sf_ref_fb sf_ref_fb[VP9_MAX_FRM_BUF_NUM-1];
	पूर्णांक sf_next_ref_fb_idx;
	अचिन्हित पूर्णांक sf_frm_cnt;
	अचिन्हित पूर्णांक sf_frm_offset[VP9_MAX_FRM_BUF_NUM-1];
	अचिन्हित पूर्णांक sf_frm_sz[VP9_MAX_FRM_BUF_NUM-1];
	अचिन्हित पूर्णांक sf_frm_idx;
	अचिन्हित पूर्णांक sf_init;
	काष्ठा vdec_fb fb;
	काष्ठा mtk_vcodec_mem bs;
	काष्ठा vdec_fb cur_fb;
	अचिन्हित पूर्णांक pic_w;
	अचिन्हित पूर्णांक pic_h;
	अचिन्हित पूर्णांक buf_w;
	अचिन्हित पूर्णांक buf_h;
	अचिन्हित पूर्णांक buf_sz_y_bs;
	अचिन्हित पूर्णांक buf_sz_c_bs;
	अचिन्हित पूर्णांक buf_len_sz_y;
	अचिन्हित पूर्णांक buf_len_sz_c;
	अचिन्हित पूर्णांक profile;
	अचिन्हित पूर्णांक show_frame;
	अचिन्हित पूर्णांक show_existing_frame;
	अचिन्हित पूर्णांक frm_to_show_idx;
	अचिन्हित पूर्णांक refresh_frm_flags;
	अचिन्हित पूर्णांक resolution_changed;

	काष्ठा vp9_ref_cnt_buf frm_bufs[VP9_MAX_FRM_BUF_NUM];
	पूर्णांक ref_frm_map[MAX_NUM_REF_FRAMES];
	अचिन्हित पूर्णांक new_fb_idx;
	अचिन्हित पूर्णांक frm_num;
	काष्ठा vp9_dram_buf mv_buf;

	काष्ठा vp9_ref_buf frm_refs[REFS_PER_FRAME];
	काष्ठा vp9_dram_buf seg_id_buf;

पूर्ण;

/*
 * काष्ठा vdec_vp9_inst - vp9 decode instance
 * @mv_buf : working buffer क्रम mv
 * @seg_id_buf : working buffer क्रम segmentation map
 * @dec_fb : vdec_fb node to link fb to dअगरferent fb_xxx_list
 * @available_fb_node_list : current available vdec_fb node
 * @fb_use_list : current used or referenced vdec_fb
 * @fb_मुक्त_list : current available to मुक्त vdec_fb
 * @fb_disp_list : current available to display vdec_fb
 * @cur_fb : current frame buffer
 * @ctx : current decode context
 * @vpu : vpu instance inक्रमmation
 * @vsi : shared buffer between host and VPU firmware
 * @total_frm_cnt : total frame count, it करो not include sub-frames in super
 *	    frame
 * @mem : instance memory inक्रमmation
 */
काष्ठा vdec_vp9_inst अणु
	काष्ठा mtk_vcodec_mem mv_buf;
	काष्ठा mtk_vcodec_mem seg_id_buf;

	काष्ठा vdec_fb_node dec_fb[VP9_MAX_FRM_BUF_NODE_NUM];
	काष्ठा list_head available_fb_node_list;
	काष्ठा list_head fb_use_list;
	काष्ठा list_head fb_मुक्त_list;
	काष्ठा list_head fb_disp_list;
	काष्ठा vdec_fb *cur_fb;
	काष्ठा mtk_vcodec_ctx *ctx;
	काष्ठा vdec_vpu_inst vpu;
	काष्ठा vdec_vp9_vsi *vsi;
	अचिन्हित पूर्णांक total_frm_cnt;
	काष्ठा mtk_vcodec_mem mem;
पूर्ण;

अटल bool vp9_is_sf_ref_fb(काष्ठा vdec_vp9_inst *inst, काष्ठा vdec_fb *fb)
अणु
	पूर्णांक i;
	काष्ठा vdec_vp9_vsi *vsi = inst->vsi;

	क्रम (i = 0; i < ARRAY_SIZE(vsi->sf_ref_fb); i++) अणु
		अगर (fb == &vsi->sf_ref_fb[i].fb)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा vdec_fb *vp9_rm_from_fb_use_list(काष्ठा vdec_vp9_inst
					*inst, व्योम *addr)
अणु
	काष्ठा vdec_fb *fb = शून्य;
	काष्ठा vdec_fb_node *node;

	list_क्रम_each_entry(node, &inst->fb_use_list, list) अणु
		fb = (काष्ठा vdec_fb *)node->fb;
		अगर (fb->base_y.va == addr) अणु
			list_move_tail(&node->list,
				       &inst->available_fb_node_list);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस fb;
पूर्ण

अटल व्योम vp9_add_to_fb_मुक्त_list(काष्ठा vdec_vp9_inst *inst,
			     काष्ठा vdec_fb *fb)
अणु
	काष्ठा vdec_fb_node *node;

	अगर (fb) अणु
		node = list_first_entry_or_null(&inst->available_fb_node_list,
					काष्ठा vdec_fb_node, list);

		अगर (node) अणु
			node->fb = fb;
			list_move_tail(&node->list, &inst->fb_मुक्त_list);
		पूर्ण
	पूर्ण अन्यथा अणु
		mtk_vcodec_debug(inst, "No free fb node");
	पूर्ण
पूर्ण

अटल व्योम vp9_मुक्त_sf_ref_fb(काष्ठा vdec_fb *fb)
अणु
	काष्ठा vp9_sf_ref_fb *sf_ref_fb =
		container_of(fb, काष्ठा vp9_sf_ref_fb, fb);

	sf_ref_fb->used = 0;
पूर्ण

अटल व्योम vp9_ref_cnt_fb(काष्ठा vdec_vp9_inst *inst, पूर्णांक *idx,
			   पूर्णांक new_idx)
अणु
	काष्ठा vdec_vp9_vsi *vsi = inst->vsi;
	पूर्णांक ref_idx = *idx;

	अगर (ref_idx >= 0 && vsi->frm_bufs[ref_idx].ref_cnt > 0) अणु
		vsi->frm_bufs[ref_idx].ref_cnt--;

		अगर (vsi->frm_bufs[ref_idx].ref_cnt == 0) अणु
			अगर (!vp9_is_sf_ref_fb(inst,
					      vsi->frm_bufs[ref_idx].buf.fb)) अणु
				काष्ठा vdec_fb *fb;

				fb = vp9_rm_from_fb_use_list(inst,
				     vsi->frm_bufs[ref_idx].buf.fb->base_y.va);
				vp9_add_to_fb_मुक्त_list(inst, fb);
			पूर्ण अन्यथा
				vp9_मुक्त_sf_ref_fb(
					vsi->frm_bufs[ref_idx].buf.fb);
		पूर्ण
	पूर्ण

	*idx = new_idx;
	vsi->frm_bufs[new_idx].ref_cnt++;
पूर्ण

अटल व्योम vp9_मुक्त_all_sf_ref_fb(काष्ठा vdec_vp9_inst *inst)
अणु
	पूर्णांक i;
	काष्ठा vdec_vp9_vsi *vsi = inst->vsi;

	क्रम (i = 0; i < ARRAY_SIZE(vsi->sf_ref_fb); i++) अणु
		अगर (vsi->sf_ref_fb[i].fb.base_y.va) अणु
			mtk_vcodec_mem_मुक्त(inst->ctx,
				&vsi->sf_ref_fb[i].fb.base_y);
			mtk_vcodec_mem_मुक्त(inst->ctx,
				&vsi->sf_ref_fb[i].fb.base_c);
			vsi->sf_ref_fb[i].used = 0;
		पूर्ण
	पूर्ण
पूर्ण

/* For each sub-frame except the last one, the driver will dynamically
 * allocate reference buffer by calling vp9_get_sf_ref_fb()
 * The last sub-frame will use the original fb provided by the
 * vp9_dec_decode() पूर्णांकerface
 */
अटल पूर्णांक vp9_get_sf_ref_fb(काष्ठा vdec_vp9_inst *inst)
अणु
	पूर्णांक idx;
	काष्ठा mtk_vcodec_mem *mem_basy_y;
	काष्ठा mtk_vcodec_mem *mem_basy_c;
	काष्ठा vdec_vp9_vsi *vsi = inst->vsi;

	क्रम (idx = 0;
		idx < ARRAY_SIZE(vsi->sf_ref_fb);
		idx++) अणु
		अगर (vsi->sf_ref_fb[idx].fb.base_y.va &&
		    vsi->sf_ref_fb[idx].used == 0) अणु
			वापस idx;
		पूर्ण
	पूर्ण

	क्रम (idx = 0;
		idx < ARRAY_SIZE(vsi->sf_ref_fb);
		idx++) अणु
		अगर (vsi->sf_ref_fb[idx].fb.base_y.va == शून्य)
			अवरोध;
	पूर्ण

	अगर (idx == ARRAY_SIZE(vsi->sf_ref_fb)) अणु
		mtk_vcodec_err(inst, "List Full");
		वापस -1;
	पूर्ण

	mem_basy_y = &vsi->sf_ref_fb[idx].fb.base_y;
	mem_basy_y->size = vsi->buf_sz_y_bs +
		vsi->buf_len_sz_y;

	अगर (mtk_vcodec_mem_alloc(inst->ctx, mem_basy_y)) अणु
		mtk_vcodec_err(inst, "Cannot allocate sf_ref_buf y_buf");
		वापस -1;
	पूर्ण

	mem_basy_c = &vsi->sf_ref_fb[idx].fb.base_c;
	mem_basy_c->size = vsi->buf_sz_c_bs +
		vsi->buf_len_sz_c;

	अगर (mtk_vcodec_mem_alloc(inst->ctx, mem_basy_c)) अणु
		mtk_vcodec_err(inst, "Cannot allocate sf_ref_fb c_buf");
		वापस -1;
	पूर्ण
	vsi->sf_ref_fb[idx].used = 0;

	वापस idx;
पूर्ण

अटल bool vp9_alloc_work_buf(काष्ठा vdec_vp9_inst *inst)
अणु
	काष्ठा vdec_vp9_vsi *vsi = inst->vsi;
	पूर्णांक result;
	काष्ठा mtk_vcodec_mem *mem;

	अचिन्हित पूर्णांक max_pic_w;
	अचिन्हित पूर्णांक max_pic_h;


	अगर (!(inst->ctx->dev->dec_capability &
		VCODEC_CAPABILITY_4K_DISABLED)) अणु
		max_pic_w = VCODEC_DEC_4K_CODED_WIDTH;
		max_pic_h = VCODEC_DEC_4K_CODED_HEIGHT;
	पूर्ण अन्यथा अणु
		max_pic_w = MTK_VDEC_MAX_W;
		max_pic_h = MTK_VDEC_MAX_H;
	पूर्ण

	अगर ((vsi->pic_w > max_pic_w) ||
		(vsi->pic_h > max_pic_h)) अणु
		mtk_vcodec_err(inst, "Invalid w/h %d/%d",
				vsi->pic_w, vsi->pic_h);
		वापस false;
	पूर्ण

	mtk_vcodec_debug(inst, "BUF CHG(%d): w/h/sb_w/sb_h=%d/%d/%d/%d",
			vsi->resolution_changed,
			vsi->pic_w,
			vsi->pic_h,
			vsi->buf_w,
			vsi->buf_h);

	mem = &inst->mv_buf;
	अगर (mem->va)
		mtk_vcodec_mem_मुक्त(inst->ctx, mem);

	mem->size = ((vsi->buf_w / 64) *
		    (vsi->buf_h / 64) + 2) * 36 * 16;
	result = mtk_vcodec_mem_alloc(inst->ctx, mem);
	अगर (result) अणु
		mem->size = 0;
		mtk_vcodec_err(inst, "Cannot allocate mv_buf");
		वापस false;
	पूर्ण
	/* Set the va again */
	vsi->mv_buf.va = (अचिन्हित दीर्घ)mem->va;
	vsi->mv_buf.pa = (अचिन्हित दीर्घ)mem->dma_addr;
	vsi->mv_buf.sz = (अचिन्हित पूर्णांक)mem->size;


	mem = &inst->seg_id_buf;
	अगर (mem->va)
		mtk_vcodec_mem_मुक्त(inst->ctx, mem);

	mem->size = VP9_SEG_ID_SZ;
	result = mtk_vcodec_mem_alloc(inst->ctx, mem);
	अगर (result) अणु
		mem->size = 0;
		mtk_vcodec_err(inst, "Cannot allocate seg_id_buf");
		वापस false;
	पूर्ण
	/* Set the va again */
	vsi->seg_id_buf.va = (अचिन्हित दीर्घ)mem->va;
	vsi->seg_id_buf.pa = (अचिन्हित दीर्घ)mem->dma_addr;
	vsi->seg_id_buf.sz = (अचिन्हित पूर्णांक)mem->size;


	vp9_मुक्त_all_sf_ref_fb(inst);
	vsi->sf_next_ref_fb_idx = vp9_get_sf_ref_fb(inst);

	वापस true;
पूर्ण

अटल bool vp9_add_to_fb_disp_list(काष्ठा vdec_vp9_inst *inst,
			     काष्ठा vdec_fb *fb)
अणु
	काष्ठा vdec_fb_node *node;

	अगर (!fb) अणु
		mtk_vcodec_err(inst, "fb == NULL");
		वापस false;
	पूर्ण

	node = list_first_entry_or_null(&inst->available_fb_node_list,
					काष्ठा vdec_fb_node, list);
	अगर (node) अणु
		node->fb = fb;
		list_move_tail(&node->list, &inst->fb_disp_list);
	पूर्ण अन्यथा अणु
		mtk_vcodec_err(inst, "No available fb node");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* If any buffer updating is संकेतed it should be करोne here. */
अटल व्योम vp9_swap_frm_bufs(काष्ठा vdec_vp9_inst *inst)
अणु
	काष्ठा vdec_vp9_vsi *vsi = inst->vsi;
	काष्ठा vp9_fb_info *frm_to_show;
	पूर्णांक ref_index = 0, mask;

	क्रम (mask = vsi->refresh_frm_flags; mask; mask >>= 1) अणु
		अगर (mask & 1)
			vp9_ref_cnt_fb(inst, &vsi->ref_frm_map[ref_index],
				       vsi->new_fb_idx);
		++ref_index;
	पूर्ण

	frm_to_show = &vsi->frm_bufs[vsi->new_fb_idx].buf;
	vsi->frm_bufs[vsi->new_fb_idx].ref_cnt--;

	अगर (frm_to_show->fb != inst->cur_fb) अणु
		/* This frame is show exist frame and no decode output
		 * copy frame data from frm_to_show to current CAPTURE
		 * buffer
		 */
		अगर ((frm_to_show->fb != शून्य) &&
			(inst->cur_fb->base_y.size >=
			frm_to_show->fb->base_y.size) &&
			(inst->cur_fb->base_c.size >=
			frm_to_show->fb->base_c.size)) अणु
			स_नकल((व्योम *)inst->cur_fb->base_y.va,
				(व्योम *)frm_to_show->fb->base_y.va,
				frm_to_show->fb->base_y.size);
			स_नकल((व्योम *)inst->cur_fb->base_c.va,
				(व्योम *)frm_to_show->fb->base_c.va,
				frm_to_show->fb->base_c.size);
		पूर्ण अन्यथा अणु
			/* After resolution change हाल, current CAPTURE buffer
			 * may have less buffer size than frm_to_show buffer
			 * size
			 */
			अगर (frm_to_show->fb != शून्य)
				mtk_vcodec_err(inst,
					"inst->cur_fb->base_y.size=%zu, frm_to_show->fb.base_y.size=%zu",
					inst->cur_fb->base_y.size,
					frm_to_show->fb->base_y.size);
		पूर्ण
		अगर (!vp9_is_sf_ref_fb(inst, inst->cur_fb)) अणु
			अगर (vsi->show_frame & BIT(0))
				vp9_add_to_fb_disp_list(inst, inst->cur_fb);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!vp9_is_sf_ref_fb(inst, inst->cur_fb)) अणु
			अगर (vsi->show_frame & BIT(0))
				vp9_add_to_fb_disp_list(inst, frm_to_show->fb);
		पूर्ण
	पूर्ण

	/* when ref_cnt ==0, move this fb to fb_मुक्त_list. v4l2 driver will
	 * clean fb_मुक्त_list
	 */
	अगर (vsi->frm_bufs[vsi->new_fb_idx].ref_cnt == 0) अणु
		अगर (!vp9_is_sf_ref_fb(
			inst, vsi->frm_bufs[vsi->new_fb_idx].buf.fb)) अणु
			काष्ठा vdec_fb *fb;

			fb = vp9_rm_from_fb_use_list(inst,
			vsi->frm_bufs[vsi->new_fb_idx].buf.fb->base_y.va);

			vp9_add_to_fb_मुक्त_list(inst, fb);
		पूर्ण अन्यथा अणु
			vp9_मुक्त_sf_ref_fb(
				vsi->frm_bufs[vsi->new_fb_idx].buf.fb);
		पूर्ण
	पूर्ण

	/* अगर this super frame and it is not last sub-frame, get next fb क्रम
	 * sub-frame decode
	 */
	अगर (vsi->sf_frm_cnt > 0 && vsi->sf_frm_idx != vsi->sf_frm_cnt - 1)
		vsi->sf_next_ref_fb_idx = vp9_get_sf_ref_fb(inst);
पूर्ण

अटल bool vp9_रुको_dec_end(काष्ठा vdec_vp9_inst *inst)
अणु
	काष्ठा mtk_vcodec_ctx *ctx = inst->ctx;

	mtk_vcodec_रुको_क्रम_करोne_ctx(inst->ctx,
			MTK_INST_IRQ_RECEIVED,
			WAIT_INTR_TIMEOUT_MS);

	अगर (ctx->irq_status & MTK_VDEC_IRQ_STATUS_DEC_SUCCESS)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल काष्ठा vdec_vp9_inst *vp9_alloc_inst(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	पूर्णांक result;
	काष्ठा mtk_vcodec_mem mem;
	काष्ठा vdec_vp9_inst *inst;

	स_रखो(&mem, 0, माप(mem));
	mem.size = माप(काष्ठा vdec_vp9_inst);
	result = mtk_vcodec_mem_alloc(ctx, &mem);
	अगर (result)
		वापस शून्य;

	inst = mem.va;
	inst->mem = mem;

	वापस inst;
पूर्ण

अटल व्योम vp9_मुक्त_inst(काष्ठा vdec_vp9_inst *inst)
अणु
	काष्ठा mtk_vcodec_mem mem;

	mem = inst->mem;
	अगर (mem.va)
		mtk_vcodec_mem_मुक्त(inst->ctx, &mem);
पूर्ण

अटल bool vp9_decode_end_proc(काष्ठा vdec_vp9_inst *inst)
अणु
	काष्ठा vdec_vp9_vsi *vsi = inst->vsi;
	bool ret = false;

	अगर (!vsi->show_existing_frame) अणु
		ret = vp9_रुको_dec_end(inst);
		अगर (!ret) अणु
			mtk_vcodec_err(inst, "Decode failed, Decode Timeout @[%d]",
				vsi->frm_num);
			वापस false;
		पूर्ण

		अगर (vpu_dec_end(&inst->vpu)) अणु
			mtk_vcodec_err(inst, "vp9_dec_vpu_end failed");
			वापस false;
		पूर्ण
		mtk_vcodec_debug(inst, "Decode Ok @%d (%d/%d)", vsi->frm_num,
				vsi->pic_w, vsi->pic_h);
	पूर्ण अन्यथा अणु
		mtk_vcodec_debug(inst, "Decode Ok @%d (show_existing_frame)",
				vsi->frm_num);
	पूर्ण

	vp9_swap_frm_bufs(inst);
	vsi->frm_num++;
	वापस true;
पूर्ण

अटल bool vp9_is_last_sub_frm(काष्ठा vdec_vp9_inst *inst)
अणु
	काष्ठा vdec_vp9_vsi *vsi = inst->vsi;

	अगर (vsi->sf_frm_cnt <= 0 || vsi->sf_frm_idx == vsi->sf_frm_cnt)
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा vdec_fb *vp9_rm_from_fb_disp_list(काष्ठा vdec_vp9_inst *inst)
अणु
	काष्ठा vdec_fb_node *node;
	काष्ठा vdec_fb *fb = शून्य;

	node = list_first_entry_or_null(&inst->fb_disp_list,
					काष्ठा vdec_fb_node, list);
	अगर (node) अणु
		fb = (काष्ठा vdec_fb *)node->fb;
		fb->status |= FB_ST_DISPLAY;
		list_move_tail(&node->list, &inst->available_fb_node_list);
		mtk_vcodec_debug(inst, "[FB] get disp fb %p st=%d",
				 node->fb, fb->status);
	पूर्ण अन्यथा
		mtk_vcodec_debug(inst, "[FB] there is no disp fb");

	वापस fb;
पूर्ण

अटल bool vp9_add_to_fb_use_list(काष्ठा vdec_vp9_inst *inst,
			    काष्ठा vdec_fb *fb)
अणु
	काष्ठा vdec_fb_node *node;

	अगर (!fb) अणु
		mtk_vcodec_debug(inst, "fb == NULL");
		वापस false;
	पूर्ण

	node = list_first_entry_or_null(&inst->available_fb_node_list,
					काष्ठा vdec_fb_node, list);
	अगर (node) अणु
		node->fb = fb;
		list_move_tail(&node->list, &inst->fb_use_list);
	पूर्ण अन्यथा अणु
		mtk_vcodec_err(inst, "No free fb node");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम vp9_reset(काष्ठा vdec_vp9_inst *inst)
अणु
	काष्ठा vdec_fb_node *node, *पंचांगp;

	list_क्रम_each_entry_safe(node, पंचांगp, &inst->fb_use_list, list)
		list_move_tail(&node->list, &inst->fb_मुक्त_list);

	vp9_मुक्त_all_sf_ref_fb(inst);
	inst->vsi->sf_next_ref_fb_idx = vp9_get_sf_ref_fb(inst);

	अगर (vpu_dec_reset(&inst->vpu))
		mtk_vcodec_err(inst, "vp9_dec_vpu_reset failed");

	/* Set the va again, since vpu_dec_reset will clear mv_buf in vpu */
	inst->vsi->mv_buf.va = (अचिन्हित दीर्घ)inst->mv_buf.va;
	inst->vsi->mv_buf.pa = (अचिन्हित दीर्घ)inst->mv_buf.dma_addr;
	inst->vsi->mv_buf.sz = (अचिन्हित दीर्घ)inst->mv_buf.size;

	/* Set the va again, since vpu_dec_reset will clear seg_id_buf in vpu */
	inst->vsi->seg_id_buf.va = (अचिन्हित दीर्घ)inst->seg_id_buf.va;
	inst->vsi->seg_id_buf.pa = (अचिन्हित दीर्घ)inst->seg_id_buf.dma_addr;
	inst->vsi->seg_id_buf.sz = (अचिन्हित दीर्घ)inst->seg_id_buf.size;

पूर्ण

अटल व्योम init_all_fb_lists(काष्ठा vdec_vp9_inst *inst)
अणु
	पूर्णांक i;

	INIT_LIST_HEAD(&inst->available_fb_node_list);
	INIT_LIST_HEAD(&inst->fb_use_list);
	INIT_LIST_HEAD(&inst->fb_मुक्त_list);
	INIT_LIST_HEAD(&inst->fb_disp_list);

	क्रम (i = 0; i < ARRAY_SIZE(inst->dec_fb); i++) अणु
		INIT_LIST_HEAD(&inst->dec_fb[i].list);
		inst->dec_fb[i].fb = शून्य;
		list_add_tail(&inst->dec_fb[i].list,
			      &inst->available_fb_node_list);
	पूर्ण
पूर्ण

अटल व्योम get_pic_info(काष्ठा vdec_vp9_inst *inst, काष्ठा vdec_pic_info *pic)
अणु
	pic->fb_sz[0] = inst->vsi->buf_sz_y_bs + inst->vsi->buf_len_sz_y;
	pic->fb_sz[1] = inst->vsi->buf_sz_c_bs + inst->vsi->buf_len_sz_c;

	pic->pic_w = inst->vsi->pic_w;
	pic->pic_h = inst->vsi->pic_h;
	pic->buf_w = inst->vsi->buf_w;
	pic->buf_h = inst->vsi->buf_h;

	mtk_vcodec_debug(inst, "pic(%d, %d), buf(%d, %d)",
		 pic->pic_w, pic->pic_h, pic->buf_w, pic->buf_h);
	mtk_vcodec_debug(inst, "fb size: Y(%d), C(%d)",
		pic->fb_sz[0],
		pic->fb_sz[1]);
पूर्ण

अटल व्योम get_disp_fb(काष्ठा vdec_vp9_inst *inst, काष्ठा vdec_fb **out_fb)
अणु

	*out_fb = vp9_rm_from_fb_disp_list(inst);
	अगर (*out_fb)
		(*out_fb)->status |= FB_ST_DISPLAY;
पूर्ण

अटल व्योम get_मुक्त_fb(काष्ठा vdec_vp9_inst *inst, काष्ठा vdec_fb **out_fb)
अणु
	काष्ठा vdec_fb_node *node;
	काष्ठा vdec_fb *fb = शून्य;

	node = list_first_entry_or_null(&inst->fb_मुक्त_list,
					काष्ठा vdec_fb_node, list);
	अगर (node) अणु
		list_move_tail(&node->list, &inst->available_fb_node_list);
		fb = (काष्ठा vdec_fb *)node->fb;
		fb->status |= FB_ST_FREE;
		mtk_vcodec_debug(inst, "[FB] get free fb %p st=%d",
				 node->fb, fb->status);
	पूर्ण अन्यथा अणु
		mtk_vcodec_debug(inst, "[FB] there is no free fb");
	पूर्ण

	*out_fb = fb;
पूर्ण

अटल पूर्णांक validate_vsi_array_indexes(काष्ठा vdec_vp9_inst *inst,
		काष्ठा vdec_vp9_vsi *vsi) अणु
	अगर (vsi->sf_frm_idx >= VP9_MAX_FRM_BUF_NUM - 1) अणु
		mtk_vcodec_err(inst, "Invalid vsi->sf_frm_idx=%u.",
				vsi->sf_frm_idx);
		वापस -EIO;
	पूर्ण
	अगर (vsi->frm_to_show_idx >= VP9_MAX_FRM_BUF_NUM) अणु
		mtk_vcodec_err(inst, "Invalid vsi->frm_to_show_idx=%u.",
				vsi->frm_to_show_idx);
		वापस -EIO;
	पूर्ण
	अगर (vsi->new_fb_idx >= VP9_MAX_FRM_BUF_NUM) अणु
		mtk_vcodec_err(inst, "Invalid vsi->new_fb_idx=%u.",
				vsi->new_fb_idx);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vdec_vp9_deinit(व्योम *h_vdec)
अणु
	काष्ठा vdec_vp9_inst *inst = (काष्ठा vdec_vp9_inst *)h_vdec;
	काष्ठा mtk_vcodec_mem *mem;
	पूर्णांक ret = 0;

	ret = vpu_dec_deinit(&inst->vpu);
	अगर (ret)
		mtk_vcodec_err(inst, "vpu_dec_deinit failed");

	mem = &inst->mv_buf;
	अगर (mem->va)
		mtk_vcodec_mem_मुक्त(inst->ctx, mem);

	mem = &inst->seg_id_buf;
	अगर (mem->va)
		mtk_vcodec_mem_मुक्त(inst->ctx, mem);

	vp9_मुक्त_all_sf_ref_fb(inst);
	vp9_मुक्त_inst(inst);
पूर्ण

अटल पूर्णांक vdec_vp9_init(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा vdec_vp9_inst *inst;

	inst = vp9_alloc_inst(ctx);
	अगर (!inst)
		वापस -ENOMEM;

	inst->total_frm_cnt = 0;
	inst->ctx = ctx;

	inst->vpu.id = IPI_VDEC_VP9;
	inst->vpu.ctx = ctx;

	अगर (vpu_dec_init(&inst->vpu)) अणु
		mtk_vcodec_err(inst, "vp9_dec_vpu_init failed");
		जाओ err_deinit_inst;
	पूर्ण

	inst->vsi = (काष्ठा vdec_vp9_vsi *)inst->vpu.vsi;

	inst->vsi->show_frame |= BIT(3);

	init_all_fb_lists(inst);

	ctx->drv_handle = inst;
	वापस 0;

err_deinit_inst:
	vp9_मुक्त_inst(inst);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vdec_vp9_decode(व्योम *h_vdec, काष्ठा mtk_vcodec_mem *bs,
			   काष्ठा vdec_fb *fb, bool *res_chg)
अणु
	पूर्णांक ret = 0;
	काष्ठा vdec_vp9_inst *inst = (काष्ठा vdec_vp9_inst *)h_vdec;
	काष्ठा vdec_vp9_vsi *vsi = inst->vsi;
	u32 data[3];
	पूर्णांक i;

	*res_chg = false;

	अगर ((bs == शून्य) && (fb == शून्य)) अणु
		mtk_vcodec_debug(inst, "[EOS]");
		vp9_reset(inst);
		वापस ret;
	पूर्ण

	अगर (bs == शून्य) अणु
		mtk_vcodec_err(inst, "bs == NULL");
		वापस -EINVAL;
	पूर्ण

	mtk_vcodec_debug(inst, "Input BS Size = %zu", bs->size);

	जबतक (1) अणु
		काष्ठा vdec_fb *cur_fb = शून्य;

		data[0] = *((अचिन्हित पूर्णांक *)bs->va);
		data[1] = *((अचिन्हित पूर्णांक *)(bs->va + 4));
		data[2] = *((अचिन्हित पूर्णांक *)(bs->va + 8));

		vsi->bs = *bs;

		अगर (fb)
			vsi->fb = *fb;

		अगर (!vsi->sf_init) अणु
			अचिन्हित पूर्णांक sf_bs_sz;
			अचिन्हित पूर्णांक sf_bs_off;
			अचिन्हित अक्षर *sf_bs_src;
			अचिन्हित अक्षर *sf_bs_dst;

			sf_bs_sz = bs->size > VP9_SUPER_FRAME_BS_SZ ?
					VP9_SUPER_FRAME_BS_SZ : bs->size;
			sf_bs_off = VP9_SUPER_FRAME_BS_SZ - sf_bs_sz;
			sf_bs_src = bs->va + bs->size - sf_bs_sz;
			sf_bs_dst = vsi->sf_bs_buf + sf_bs_off;
			स_नकल(sf_bs_dst, sf_bs_src, sf_bs_sz);
		पूर्ण अन्यथा अणु
			अगर ((vsi->sf_frm_cnt > 0) &&
				(vsi->sf_frm_idx < vsi->sf_frm_cnt)) अणु
				अचिन्हित पूर्णांक idx = vsi->sf_frm_idx;

				स_नकल((व्योम *)bs->va,
					(व्योम *)(bs->va +
					vsi->sf_frm_offset[idx]),
					vsi->sf_frm_sz[idx]);
			पूर्ण
		पूर्ण

		अगर (!(vsi->show_frame & BIT(4)))
			स_रखो(inst->seg_id_buf.va, 0, inst->seg_id_buf.size);

		ret = vpu_dec_start(&inst->vpu, data, 3);
		अगर (ret) अणु
			mtk_vcodec_err(inst, "vpu_dec_start failed");
			जाओ DECODE_ERROR;
		पूर्ण

		अगर (vsi->show_frame & BIT(1)) अणु
			स_रखो(inst->seg_id_buf.va, 0, inst->seg_id_buf.size);

			अगर (vsi->show_frame & BIT(2)) अणु
				ret = vpu_dec_start(&inst->vpu, शून्य, 0);
				अगर (ret) अणु
					mtk_vcodec_err(inst, "vpu trig decoder failed");
					जाओ DECODE_ERROR;
				पूर्ण
			पूर्ण
		पूर्ण

		ret = validate_vsi_array_indexes(inst, vsi);
		अगर (ret) अणु
			mtk_vcodec_err(inst, "Invalid values from VPU.");
			जाओ DECODE_ERROR;
		पूर्ण

		अगर (vsi->resolution_changed) अणु
			अगर (!vp9_alloc_work_buf(inst)) अणु
				ret = -EIO;
				जाओ DECODE_ERROR;
			पूर्ण
		पूर्ण

		अगर (vsi->sf_frm_cnt > 0) अणु
			cur_fb = &vsi->sf_ref_fb[vsi->sf_next_ref_fb_idx].fb;

			अगर (vsi->sf_frm_idx < vsi->sf_frm_cnt)
				inst->cur_fb = cur_fb;
			अन्यथा
				inst->cur_fb = fb;
		पूर्ण अन्यथा अणु
			inst->cur_fb = fb;
		पूर्ण

		vsi->frm_bufs[vsi->new_fb_idx].buf.fb = inst->cur_fb;
		अगर (!vp9_is_sf_ref_fb(inst, inst->cur_fb))
			vp9_add_to_fb_use_list(inst, inst->cur_fb);

		mtk_vcodec_debug(inst, "[#pic %d]", vsi->frm_num);

		अगर (vsi->show_existing_frame)
			mtk_vcodec_debug(inst,
				"drv->new_fb_idx=%d, drv->frm_to_show_idx=%d",
				vsi->new_fb_idx, vsi->frm_to_show_idx);

		अगर (vsi->show_existing_frame && (vsi->frm_to_show_idx <
					VP9_MAX_FRM_BUF_NUM)) अणु
			mtk_vcodec_debug(inst,
				"Skip Decode drv->new_fb_idx=%d, drv->frm_to_show_idx=%d",
				vsi->new_fb_idx, vsi->frm_to_show_idx);

			vp9_ref_cnt_fb(inst, &vsi->new_fb_idx,
					vsi->frm_to_show_idx);
		पूर्ण

		/* VPU assign the buffer poपूर्णांकer in its address space,
		 * reassign here
		 */
		क्रम (i = 0; i < ARRAY_SIZE(vsi->frm_refs); i++) अणु
			अचिन्हित पूर्णांक idx = vsi->frm_refs[i].idx;

			vsi->frm_refs[i].buf = &vsi->frm_bufs[idx].buf;
		पूर्ण

		अगर (vsi->resolution_changed) अणु
			*res_chg = true;
			mtk_vcodec_debug(inst, "VDEC_ST_RESOLUTION_CHANGED");

			ret = 0;
			जाओ DECODE_ERROR;
		पूर्ण

		अगर (!vp9_decode_end_proc(inst)) अणु
			mtk_vcodec_err(inst, "vp9_decode_end_proc");
			ret = -EINVAL;
			जाओ DECODE_ERROR;
		पूर्ण

		अगर (vp9_is_last_sub_frm(inst))
			अवरोध;

	पूर्ण
	inst->total_frm_cnt++;

DECODE_ERROR:
	अगर (ret < 0)
		vp9_add_to_fb_मुक्त_list(inst, fb);

	वापस ret;
पूर्ण

अटल व्योम get_crop_info(काष्ठा vdec_vp9_inst *inst, काष्ठा v4l2_rect *cr)
अणु
	cr->left = 0;
	cr->top = 0;
	cr->width = inst->vsi->pic_w;
	cr->height = inst->vsi->pic_h;
	mtk_vcodec_debug(inst, "get crop info l=%d, t=%d, w=%d, h=%d\n",
			 cr->left, cr->top, cr->width, cr->height);
पूर्ण

अटल पूर्णांक vdec_vp9_get_param(व्योम *h_vdec, क्रमागत vdec_get_param_type type,
			      व्योम *out)
अणु
	काष्ठा vdec_vp9_inst *inst = (काष्ठा vdec_vp9_inst *)h_vdec;
	पूर्णांक ret = 0;

	चयन (type) अणु
	हाल GET_PARAM_DISP_FRAME_BUFFER:
		get_disp_fb(inst, out);
		अवरोध;
	हाल GET_PARAM_FREE_FRAME_BUFFER:
		get_मुक्त_fb(inst, out);
		अवरोध;
	हाल GET_PARAM_PIC_INFO:
		get_pic_info(inst, out);
		अवरोध;
	हाल GET_PARAM_DPB_SIZE:
		*((अचिन्हित पूर्णांक *)out) = MAX_VP9_DPB_SIZE;
		अवरोध;
	हाल GET_PARAM_CROP_INFO:
		get_crop_info(inst, out);
		अवरोध;
	शेष:
		mtk_vcodec_err(inst, "not supported param type %d", type);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

स्थिर काष्ठा vdec_common_अगर vdec_vp9_अगर = अणु
	.init		= vdec_vp9_init,
	.decode		= vdec_vp9_decode,
	.get_param	= vdec_vp9_get_param,
	.deinit		= vdec_vp9_deinit,
पूर्ण;
