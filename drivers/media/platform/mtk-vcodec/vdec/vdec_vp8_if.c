<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Jungchang Tsao <jungchang.tsao@mediatek.com>
 *	   PC Chen <pc.chen@mediatek.com>
 */

#समावेश <linux/slab.h>
#समावेश "../vdec_drv_if.h"
#समावेश "../mtk_vcodec_util.h"
#समावेश "../mtk_vcodec_dec.h"
#समावेश "../mtk_vcodec_intr.h"
#समावेश "../vdec_vpu_if.h"
#समावेश "../vdec_drv_base.h"

/* Decoding picture buffer size (3 reference frames plus current frame) */
#घोषणा VP8_DPB_SIZE			4

/* HW working buffer size (bytes) */
#घोषणा VP8_WORKING_BUF_SZ		(45 * 4096)

/* HW control रेजिस्टर address */
#घोषणा VP8_SEGID_DRAM_ADDR		0x3c
#घोषणा VP8_HW_VLD_ADDR			0x93C
#घोषणा VP8_HW_VLD_VALUE		0x940
#घोषणा VP8_BSASET			0x100
#घोषणा VP8_BSDSET			0x104
#घोषणा VP8_RW_CKEN_SET			0x0
#घोषणा VP8_RW_DCM_CON			0x18
#घोषणा VP8_WO_VLD_SRST			0x108
#घोषणा VP8_RW_MISC_SYS_SEL		0x84
#घोषणा VP8_RW_MISC_SPEC_CON		0xC8
#घोषणा VP8_WO_VLD_SRST			0x108
#घोषणा VP8_RW_VP8_CTRL			0xA4
#घोषणा VP8_RW_MISC_DCM_CON		0xEC
#घोषणा VP8_RW_MISC_SRST		0xF4
#घोषणा VP8_RW_MISC_FUNC_CON		0xCC

#घोषणा VP8_MAX_FRM_BUF_NUM		5
#घोषणा VP8_MAX_FRM_BUF_NODE_NUM	(VP8_MAX_FRM_BUF_NUM * 2)

/* required buffer size (bytes) to store decode inक्रमmation */
#घोषणा VP8_HW_SEGMENT_DATA_SZ		272
#घोषणा VP8_HW_SEGMENT_UINT		4

#घोषणा VP8_DEC_TABLE_PROC_LOOP		96
#घोषणा VP8_DEC_TABLE_UNIT		3
#घोषणा VP8_DEC_TABLE_SZ		300
#घोषणा VP8_DEC_TABLE_OFFSET		2
#घोषणा VP8_DEC_TABLE_RW_UNIT		4

/**
 * काष्ठा vdec_vp8_dec_info - decode misc inक्रमmation
 * @working_buf_dma   : working buffer dma address
 * @prev_y_dma        : previous decoded frame buffer Y plane address
 * @cur_y_fb_dma      : current plane Y frame buffer dma address
 * @cur_c_fb_dma      : current plane C frame buffer dma address
 * @bs_dma	      : bitstream dma address
 * @bs_sz	      : bitstream size
 * @resolution_changed: resolution change flag 1 - changed,  0 - not change
 * @show_frame	      : display this frame or not
 * @रुको_key_frame    : रुको key frame coming
 */
काष्ठा vdec_vp8_dec_info अणु
	uपूर्णांक64_t working_buf_dma;
	uपूर्णांक64_t prev_y_dma;
	uपूर्णांक64_t cur_y_fb_dma;
	uपूर्णांक64_t cur_c_fb_dma;
	uपूर्णांक64_t bs_dma;
	uपूर्णांक32_t bs_sz;
	uपूर्णांक32_t resolution_changed;
	uपूर्णांक32_t show_frame;
	uपूर्णांक32_t रुको_key_frame;
पूर्ण;

/**
 * काष्ठा vdec_vp8_vsi - VPU shared inक्रमmation
 * @dec			: decoding inक्रमmation
 * @pic			: picture inक्रमmation
 * @dec_table		: decoder coefficient table
 * @segment_buf		: segmentation buffer
 * @load_data		: flag to indicate reload decode data
 */
काष्ठा vdec_vp8_vsi अणु
	काष्ठा vdec_vp8_dec_info dec;
	काष्ठा vdec_pic_info pic;
	uपूर्णांक32_t dec_table[VP8_DEC_TABLE_SZ];
	uपूर्णांक32_t segment_buf[VP8_HW_SEGMENT_DATA_SZ][VP8_HW_SEGMENT_UINT];
	uपूर्णांक32_t load_data;
पूर्ण;

/**
 * काष्ठा vdec_vp8_hw_reg_base - HW रेजिस्टर base
 * @sys		: base address क्रम sys
 * @misc	: base address क्रम misc
 * @ld		: base address क्रम ld
 * @top		: base address क्रम top
 * @cm		: base address क्रम cm
 * @hwd		: base address क्रम hwd
 * @hwb		: base address क्रम hwb
 */
काष्ठा vdec_vp8_hw_reg_base अणु
	व्योम __iomem *sys;
	व्योम __iomem *misc;
	व्योम __iomem *ld;
	व्योम __iomem *top;
	व्योम __iomem *cm;
	व्योम __iomem *hwd;
	व्योम __iomem *hwb;
पूर्ण;

/**
 * काष्ठा vdec_vp8_vpu_inst - VPU instance क्रम VP8 decode
 * @wq_hd	: Wait queue to रुको VPU message ack
 * @संकेतed	: 1 - Host has received ack message from VPU, 0 - not receive
 * @failure	: VPU execution result status 0 - success, others - fail
 * @inst_addr	: VPU decoder instance address
 */
काष्ठा vdec_vp8_vpu_inst अणु
	रुको_queue_head_t wq_hd;
	पूर्णांक संकेतed;
	पूर्णांक failure;
	uपूर्णांक32_t inst_addr;
पूर्ण;

/* frame buffer (fb) list
 * [available_fb_node_list]  - decode fb are initialized to 0 and populated in
 * [fb_use_list]  - fb is set after decode and is moved to this list
 * [fb_मुक्त_list] - fb is not needed क्रम reference will be moved from
 *		     [fb_use_list] to [fb_मुक्त_list] and
 *		     once user हटाओ fb from [fb_मुक्त_list],
 *		     it is circulated back to [available_fb_node_list]
 * [fb_disp_list] - fb is set after decode and is moved to this list
 *                   once user हटाओ fb from [fb_disp_list] it is
 *                   circulated back to [available_fb_node_list]
 */

/**
 * काष्ठा vdec_vp8_inst - VP8 decoder instance
 * @cur_fb		   : current frame buffer
 * @dec_fb		   : decode frame buffer node
 * @available_fb_node_list : list to store available frame buffer node
 * @fb_use_list		   : list to store frame buffer in use
 * @fb_मुक्त_list	   : list to store मुक्त frame buffer
 * @fb_disp_list	   : list to store display पढ़ोy frame buffer
 * @working_buf		   : HW decoder working buffer
 * @reg_base		   : HW रेजिस्टर base address
 * @frm_cnt		   : decode frame count
 * @ctx			   : V4L2 context
 * @vpu			   : VPU instance क्रम decoder
 * @vsi			   : VPU share inक्रमmation
 */
काष्ठा vdec_vp8_inst अणु
	काष्ठा vdec_fb *cur_fb;
	काष्ठा vdec_fb_node dec_fb[VP8_MAX_FRM_BUF_NODE_NUM];
	काष्ठा list_head available_fb_node_list;
	काष्ठा list_head fb_use_list;
	काष्ठा list_head fb_मुक्त_list;
	काष्ठा list_head fb_disp_list;
	काष्ठा mtk_vcodec_mem working_buf;
	काष्ठा vdec_vp8_hw_reg_base reg_base;
	अचिन्हित पूर्णांक frm_cnt;
	काष्ठा mtk_vcodec_ctx *ctx;
	काष्ठा vdec_vpu_inst vpu;
	काष्ठा vdec_vp8_vsi *vsi;
पूर्ण;

अटल व्योम get_hw_reg_base(काष्ठा vdec_vp8_inst *inst)
अणु
	inst->reg_base.top = mtk_vcodec_get_reg_addr(inst->ctx, VDEC_TOP);
	inst->reg_base.cm = mtk_vcodec_get_reg_addr(inst->ctx, VDEC_CM);
	inst->reg_base.hwd = mtk_vcodec_get_reg_addr(inst->ctx, VDEC_HWD);
	inst->reg_base.sys = mtk_vcodec_get_reg_addr(inst->ctx, VDEC_SYS);
	inst->reg_base.misc = mtk_vcodec_get_reg_addr(inst->ctx, VDEC_MISC);
	inst->reg_base.ld = mtk_vcodec_get_reg_addr(inst->ctx, VDEC_LD);
	inst->reg_base.hwb = mtk_vcodec_get_reg_addr(inst->ctx, VDEC_HWB);
पूर्ण

अटल व्योम ग_लिखो_hw_segmentation_data(काष्ठा vdec_vp8_inst *inst)
अणु
	पूर्णांक i, j;
	u32 seg_id_addr;
	u32 val;
	व्योम __iomem *cm = inst->reg_base.cm;
	काष्ठा vdec_vp8_vsi *vsi = inst->vsi;

	seg_id_addr = पढ़ोl(inst->reg_base.top + VP8_SEGID_DRAM_ADDR) >> 4;

	क्रम (i = 0; i < ARRAY_SIZE(vsi->segment_buf); i++) अणु
		क्रम (j = ARRAY_SIZE(vsi->segment_buf[i]) - 1; j >= 0; j--) अणु
			val = (1 << 16) + ((seg_id_addr + i) << 2) + j;
			ग_लिखोl(val, cm + VP8_HW_VLD_ADDR);

			val = vsi->segment_buf[i][j];
			ग_लिखोl(val, cm + VP8_HW_VLD_VALUE);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_hw_segmentation_data(काष्ठा vdec_vp8_inst *inst)
अणु
	पूर्णांक i, j;
	u32 seg_id_addr;
	u32 val;
	व्योम __iomem *cm = inst->reg_base.cm;
	काष्ठा vdec_vp8_vsi *vsi = inst->vsi;

	seg_id_addr = पढ़ोl(inst->reg_base.top + VP8_SEGID_DRAM_ADDR) >> 4;

	क्रम (i = 0; i < ARRAY_SIZE(vsi->segment_buf); i++) अणु
		क्रम (j = ARRAY_SIZE(vsi->segment_buf[i]) - 1; j >= 0; j--) अणु
			val = ((seg_id_addr + i) << 2) + j;
			ग_लिखोl(val, cm + VP8_HW_VLD_ADDR);

			val = पढ़ोl(cm + VP8_HW_VLD_VALUE);
			vsi->segment_buf[i][j] = val;
		पूर्ण
	पूर्ण
पूर्ण

/* reset HW and enable HW पढ़ो/ग_लिखो data function */
अटल व्योम enable_hw_rw_function(काष्ठा vdec_vp8_inst *inst)
अणु
	u32 val = 0;
	व्योम __iomem *sys = inst->reg_base.sys;
	व्योम __iomem *misc = inst->reg_base.misc;
	व्योम __iomem *ld = inst->reg_base.ld;
	व्योम __iomem *hwb = inst->reg_base.hwb;
	व्योम __iomem *hwd = inst->reg_base.hwd;

	ग_लिखोl(0x1, sys + VP8_RW_CKEN_SET);
	ग_लिखोl(0x101, ld + VP8_WO_VLD_SRST);
	ग_लिखोl(0x101, hwb + VP8_WO_VLD_SRST);

	ग_लिखोl(1, sys);
	val = पढ़ोl(misc + VP8_RW_MISC_SRST);
	ग_लिखोl((val & 0xFFFFFFFE), misc + VP8_RW_MISC_SRST);

	ग_लिखोl(0x1, misc + VP8_RW_MISC_SYS_SEL);
	ग_लिखोl(0x17F, misc + VP8_RW_MISC_SPEC_CON);
	ग_लिखोl(0x71201100, misc + VP8_RW_MISC_FUNC_CON);
	ग_लिखोl(0x0, ld + VP8_WO_VLD_SRST);
	ग_लिखोl(0x0, hwb + VP8_WO_VLD_SRST);
	ग_लिखोl(0x1, sys + VP8_RW_DCM_CON);
	ग_लिखोl(0x1, misc + VP8_RW_MISC_DCM_CON);
	ग_लिखोl(0x1, hwd + VP8_RW_VP8_CTRL);
पूर्ण

अटल व्योम store_dec_table(काष्ठा vdec_vp8_inst *inst)
अणु
	पूर्णांक i, j;
	u32 addr = 0, val = 0;
	व्योम __iomem *hwd = inst->reg_base.hwd;
	u32 *p = &inst->vsi->dec_table[VP8_DEC_TABLE_OFFSET];

	क्रम (i = 0; i < VP8_DEC_TABLE_PROC_LOOP; i++) अणु
		ग_लिखोl(addr, hwd + VP8_BSASET);
		क्रम (j = 0; j < VP8_DEC_TABLE_UNIT ; j++) अणु
			val = *p++;
			ग_लिखोl(val, hwd + VP8_BSDSET);
		पूर्ण
		addr += VP8_DEC_TABLE_RW_UNIT;
	पूर्ण
पूर्ण

अटल व्योम load_dec_table(काष्ठा vdec_vp8_inst *inst)
अणु
	पूर्णांक i;
	u32 addr = 0;
	u32 *p = &inst->vsi->dec_table[VP8_DEC_TABLE_OFFSET];
	व्योम __iomem *hwd = inst->reg_base.hwd;

	क्रम (i = 0; i < VP8_DEC_TABLE_PROC_LOOP; i++) अणु
		ग_लिखोl(addr, hwd + VP8_BSASET);
		/* पढ़ो total 11 bytes */
		*p++ = पढ़ोl(hwd + VP8_BSDSET);
		*p++ = पढ़ोl(hwd + VP8_BSDSET);
		*p++ = पढ़ोl(hwd + VP8_BSDSET) & 0xFFFFFF;
		addr += VP8_DEC_TABLE_RW_UNIT;
	पूर्ण
पूर्ण

अटल व्योम get_pic_info(काष्ठा vdec_vp8_inst *inst, काष्ठा vdec_pic_info *pic)
अणु
	*pic = inst->vsi->pic;

	mtk_vcodec_debug(inst, "pic(%d, %d), buf(%d, %d)",
			 pic->pic_w, pic->pic_h, pic->buf_w, pic->buf_h);
	mtk_vcodec_debug(inst, "fb size: Y(%d), C(%d)",
			 pic->fb_sz[0], pic->fb_sz[1]);
पूर्ण

अटल व्योम vp8_dec_finish(काष्ठा vdec_vp8_inst *inst)
अणु
	काष्ठा vdec_fb_node *node;
	uपूर्णांक64_t prev_y_dma = inst->vsi->dec.prev_y_dma;

	mtk_vcodec_debug(inst, "prev fb base dma=%llx", prev_y_dma);

	/* put last decode ok frame to fb_मुक्त_list */
	अगर (prev_y_dma != 0) अणु
		list_क्रम_each_entry(node, &inst->fb_use_list, list) अणु
			काष्ठा vdec_fb *fb = (काष्ठा vdec_fb *)node->fb;

			अगर (prev_y_dma == (uपूर्णांक64_t)fb->base_y.dma_addr) अणु
				list_move_tail(&node->list,
					       &inst->fb_मुक्त_list);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* available_fb_node_list -> fb_use_list */
	node = list_first_entry(&inst->available_fb_node_list,
				काष्ठा vdec_fb_node, list);
	node->fb = inst->cur_fb;
	list_move_tail(&node->list, &inst->fb_use_list);

	/* available_fb_node_list -> fb_disp_list */
	अगर (inst->vsi->dec.show_frame) अणु
		node = list_first_entry(&inst->available_fb_node_list,
					काष्ठा vdec_fb_node, list);
		node->fb = inst->cur_fb;
		list_move_tail(&node->list, &inst->fb_disp_list);
	पूर्ण
पूर्ण

अटल व्योम move_fb_list_use_to_मुक्त(काष्ठा vdec_vp8_inst *inst)
अणु
	काष्ठा vdec_fb_node *node, *पंचांगp;

	list_क्रम_each_entry_safe(node, पंचांगp, &inst->fb_use_list, list)
		list_move_tail(&node->list, &inst->fb_मुक्त_list);
पूर्ण

अटल व्योम init_list(काष्ठा vdec_vp8_inst *inst)
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

अटल व्योम add_fb_to_मुक्त_list(काष्ठा vdec_vp8_inst *inst, व्योम *fb)
अणु
	काष्ठा vdec_fb_node *node;

	अगर (fb) अणु
		node = list_first_entry(&inst->available_fb_node_list,
					काष्ठा vdec_fb_node, list);
		node->fb = fb;
		list_move_tail(&node->list, &inst->fb_मुक्त_list);
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_working_buf(काष्ठा vdec_vp8_inst *inst)
अणु
	पूर्णांक err;
	काष्ठा mtk_vcodec_mem *mem = &inst->working_buf;

	mem->size = VP8_WORKING_BUF_SZ;
	err = mtk_vcodec_mem_alloc(inst->ctx, mem);
	अगर (err) अणु
		mtk_vcodec_err(inst, "Cannot allocate working buffer");
		वापस err;
	पूर्ण

	inst->vsi->dec.working_buf_dma = (uपूर्णांक64_t)mem->dma_addr;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_working_buf(काष्ठा vdec_vp8_inst *inst)
अणु
	काष्ठा mtk_vcodec_mem *mem = &inst->working_buf;

	अगर (mem->va)
		mtk_vcodec_mem_मुक्त(inst->ctx, mem);

	inst->vsi->dec.working_buf_dma = 0;
पूर्ण

अटल पूर्णांक vdec_vp8_init(काष्ठा mtk_vcodec_ctx *ctx)
अणु
	काष्ठा vdec_vp8_inst *inst;
	पूर्णांक err;

	inst = kzalloc(माप(*inst), GFP_KERNEL);
	अगर (!inst)
		वापस  -ENOMEM;

	inst->ctx = ctx;

	inst->vpu.id = IPI_VDEC_VP8;
	inst->vpu.ctx = ctx;

	err = vpu_dec_init(&inst->vpu);
	अगर (err) अणु
		mtk_vcodec_err(inst, "vdec_vp8 init err=%d", err);
		जाओ error_मुक्त_inst;
	पूर्ण

	inst->vsi = (काष्ठा vdec_vp8_vsi *)inst->vpu.vsi;
	init_list(inst);
	err = alloc_working_buf(inst);
	अगर (err)
		जाओ error_deinit;

	get_hw_reg_base(inst);
	mtk_vcodec_debug(inst, "VP8 Instance >> %p", inst);

	ctx->drv_handle = inst;
	वापस 0;

error_deinit:
	vpu_dec_deinit(&inst->vpu);
error_मुक्त_inst:
	kमुक्त(inst);
	वापस err;
पूर्ण

अटल पूर्णांक vdec_vp8_decode(व्योम *h_vdec, काष्ठा mtk_vcodec_mem *bs,
			   काष्ठा vdec_fb *fb, bool *res_chg)
अणु
	काष्ठा vdec_vp8_inst *inst = (काष्ठा vdec_vp8_inst *)h_vdec;
	काष्ठा vdec_vp8_dec_info *dec = &inst->vsi->dec;
	काष्ठा vdec_vpu_inst *vpu = &inst->vpu;
	अचिन्हित अक्षर *bs_va;
	अचिन्हित पूर्णांक data;
	पूर्णांक err = 0;
	uपूर्णांक64_t y_fb_dma;
	uपूर्णांक64_t c_fb_dma;

	/* bs शून्य means flush decoder */
	अगर (bs == शून्य) अणु
		move_fb_list_use_to_मुक्त(inst);
		वापस vpu_dec_reset(vpu);
	पूर्ण

	y_fb_dma = fb ? (u64)fb->base_y.dma_addr : 0;
	c_fb_dma = fb ? (u64)fb->base_c.dma_addr : 0;

	mtk_vcodec_debug(inst, "+ [%d] FB y_dma=%llx c_dma=%llx fb=%p",
			 inst->frm_cnt, y_fb_dma, c_fb_dma, fb);

	inst->cur_fb = fb;
	dec->bs_dma = (अचिन्हित दीर्घ)bs->dma_addr;
	dec->bs_sz = bs->size;
	dec->cur_y_fb_dma = y_fb_dma;
	dec->cur_c_fb_dma = c_fb_dma;

	mtk_vcodec_debug(inst, "\n + FRAME[%d] +\n", inst->frm_cnt);

	ग_लिखो_hw_segmentation_data(inst);
	enable_hw_rw_function(inst);
	store_dec_table(inst);

	bs_va = (अचिन्हित अक्षर *)bs->va;

	/* retrieve width/hight and scale info from header */
	data = (*(bs_va + 9) << 24) | (*(bs_va + 8) << 16) |
	       (*(bs_va + 7) << 8) | *(bs_va + 6);
	err = vpu_dec_start(vpu, &data, 1);
	अगर (err) अणु
		add_fb_to_मुक्त_list(inst, fb);
		अगर (dec->रुको_key_frame) अणु
			mtk_vcodec_debug(inst, "wait key frame !");
			वापस 0;
		पूर्ण

		जाओ error;
	पूर्ण

	अगर (dec->resolution_changed) अणु
		mtk_vcodec_debug(inst, "- resolution_changed -");
		*res_chg = true;
		add_fb_to_मुक्त_list(inst, fb);
		वापस 0;
	पूर्ण

	/* रुको decoder करोne पूर्णांकerrupt */
	mtk_vcodec_रुको_क्रम_करोne_ctx(inst->ctx, MTK_INST_IRQ_RECEIVED,
				     WAIT_INTR_TIMEOUT_MS);

	अगर (inst->vsi->load_data)
		load_dec_table(inst);

	vp8_dec_finish(inst);
	पढ़ो_hw_segmentation_data(inst);

	err = vpu_dec_end(vpu);
	अगर (err)
		जाओ error;

	mtk_vcodec_debug(inst, "\n - FRAME[%d] - show=%d\n", inst->frm_cnt,
			 dec->show_frame);
	inst->frm_cnt++;
	*res_chg = false;
	वापस 0;

error:
	mtk_vcodec_err(inst, "\n - FRAME[%d] - err=%d\n", inst->frm_cnt, err);
	वापस err;
पूर्ण

अटल व्योम get_disp_fb(काष्ठा vdec_vp8_inst *inst, काष्ठा vdec_fb **out_fb)
अणु
	काष्ठा vdec_fb_node *node;
	काष्ठा vdec_fb *fb;

	node = list_first_entry_or_null(&inst->fb_disp_list,
					काष्ठा vdec_fb_node, list);
	अगर (node) अणु
		list_move_tail(&node->list, &inst->available_fb_node_list);
		fb = (काष्ठा vdec_fb *)node->fb;
		fb->status |= FB_ST_DISPLAY;
		mtk_vcodec_debug(inst, "[FB] get disp fb %p st=%d",
				 node->fb, fb->status);
	पूर्ण अन्यथा अणु
		fb = शून्य;
		mtk_vcodec_debug(inst, "[FB] there is no disp fb");
	पूर्ण

	*out_fb = fb;
पूर्ण

अटल व्योम get_मुक्त_fb(काष्ठा vdec_vp8_inst *inst, काष्ठा vdec_fb **out_fb)
अणु
	काष्ठा vdec_fb_node *node;
	काष्ठा vdec_fb *fb;

	node = list_first_entry_or_null(&inst->fb_मुक्त_list,
					काष्ठा vdec_fb_node, list);
	अगर (node) अणु
		list_move_tail(&node->list, &inst->available_fb_node_list);
		fb = (काष्ठा vdec_fb *)node->fb;
		fb->status |= FB_ST_FREE;
		mtk_vcodec_debug(inst, "[FB] get free fb %p st=%d",
				 node->fb, fb->status);
	पूर्ण अन्यथा अणु
		fb = शून्य;
		mtk_vcodec_debug(inst, "[FB] there is no free fb");
	पूर्ण

	*out_fb = fb;
पूर्ण

अटल व्योम get_crop_info(काष्ठा vdec_vp8_inst *inst, काष्ठा v4l2_rect *cr)
अणु
	cr->left = 0;
	cr->top = 0;
	cr->width = inst->vsi->pic.pic_w;
	cr->height = inst->vsi->pic.pic_h;
	mtk_vcodec_debug(inst, "get crop info l=%d, t=%d, w=%d, h=%d",
			 cr->left, cr->top, cr->width, cr->height);
पूर्ण

अटल पूर्णांक vdec_vp8_get_param(व्योम *h_vdec, क्रमागत vdec_get_param_type type,
			      व्योम *out)
अणु
	काष्ठा vdec_vp8_inst *inst = (काष्ठा vdec_vp8_inst *)h_vdec;

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

	हाल GET_PARAM_CROP_INFO:
		get_crop_info(inst, out);
		अवरोध;

	हाल GET_PARAM_DPB_SIZE:
		*((अचिन्हित पूर्णांक *)out) = VP8_DPB_SIZE;
		अवरोध;

	शेष:
		mtk_vcodec_err(inst, "invalid get parameter type=%d", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vdec_vp8_deinit(व्योम *h_vdec)
अणु
	काष्ठा vdec_vp8_inst *inst = (काष्ठा vdec_vp8_inst *)h_vdec;

	mtk_vcodec_debug_enter(inst);

	vpu_dec_deinit(&inst->vpu);
	मुक्त_working_buf(inst);
	kमुक्त(inst);
पूर्ण

स्थिर काष्ठा vdec_common_अगर vdec_vp8_अगर = अणु
	.init		= vdec_vp8_init,
	.decode		= vdec_vp8_decode,
	.get_param	= vdec_vp8_get_param,
	.deinit		= vdec_vp8_deinit,
पूर्ण;
