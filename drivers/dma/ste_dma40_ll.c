<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2007-2010
 * Author: Per Forlin <per.क्रमlin@stericsson.com> क्रम ST-Ericsson
 * Author: Jonas Aaberg <jonas.aberg@stericsson.com> क्रम ST-Ericsson
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_data/dma-ste-dma40.h>

#समावेश "ste_dma40_ll.h"

अटल u8 d40_width_to_bits(क्रमागत dma_slave_buswidth width)
अणु
	अगर (width == DMA_SLAVE_BUSWIDTH_1_BYTE)
		वापस STEDMA40_ESIZE_8_BIT;
	अन्यथा अगर (width == DMA_SLAVE_BUSWIDTH_2_BYTES)
		वापस STEDMA40_ESIZE_16_BIT;
	अन्यथा अगर (width == DMA_SLAVE_BUSWIDTH_8_BYTES)
		वापस STEDMA40_ESIZE_64_BIT;
	अन्यथा
		वापस STEDMA40_ESIZE_32_BIT;
पूर्ण

/* Sets up proper LCSP1 and LCSP3 रेजिस्टर क्रम a logical channel */
व्योम d40_log_cfg(काष्ठा stedma40_chan_cfg *cfg,
		 u32 *lcsp1, u32 *lcsp3)
अणु
	u32 l3 = 0; /* dst */
	u32 l1 = 0; /* src */

	/* src is mem? -> increase address pos */
	अगर (cfg->dir ==  DMA_MEM_TO_DEV ||
	    cfg->dir ==  DMA_MEM_TO_MEM)
		l1 |= BIT(D40_MEM_LCSP1_SCFG_INCR_POS);

	/* dst is mem? -> increase address pos */
	अगर (cfg->dir ==  DMA_DEV_TO_MEM ||
	    cfg->dir ==  DMA_MEM_TO_MEM)
		l3 |= BIT(D40_MEM_LCSP3_DCFG_INCR_POS);

	/* src is hw? -> master port 1 */
	अगर (cfg->dir ==  DMA_DEV_TO_MEM ||
	    cfg->dir ==  DMA_DEV_TO_DEV)
		l1 |= BIT(D40_MEM_LCSP1_SCFG_MST_POS);

	/* dst is hw? -> master port 1 */
	अगर (cfg->dir ==  DMA_MEM_TO_DEV ||
	    cfg->dir ==  DMA_DEV_TO_DEV)
		l3 |= BIT(D40_MEM_LCSP3_DCFG_MST_POS);

	l3 |= BIT(D40_MEM_LCSP3_DCFG_EIM_POS);
	l3 |= cfg->dst_info.psize << D40_MEM_LCSP3_DCFG_PSIZE_POS;
	l3 |= d40_width_to_bits(cfg->dst_info.data_width)
		<< D40_MEM_LCSP3_DCFG_ESIZE_POS;

	l1 |= BIT(D40_MEM_LCSP1_SCFG_EIM_POS);
	l1 |= cfg->src_info.psize << D40_MEM_LCSP1_SCFG_PSIZE_POS;
	l1 |= d40_width_to_bits(cfg->src_info.data_width)
		<< D40_MEM_LCSP1_SCFG_ESIZE_POS;

	*lcsp1 = l1;
	*lcsp3 = l3;

पूर्ण

व्योम d40_phy_cfg(काष्ठा stedma40_chan_cfg *cfg, u32 *src_cfg, u32 *dst_cfg)
अणु
	u32 src = 0;
	u32 dst = 0;

	अगर ((cfg->dir == DMA_DEV_TO_MEM) ||
	    (cfg->dir == DMA_DEV_TO_DEV)) अणु
		/* Set master port to 1 */
		src |= BIT(D40_SREG_CFG_MST_POS);
		src |= D40_TYPE_TO_EVENT(cfg->dev_type);

		अगर (cfg->src_info.flow_ctrl == STEDMA40_NO_FLOW_CTRL)
			src |= BIT(D40_SREG_CFG_PHY_TM_POS);
		अन्यथा
			src |= 3 << D40_SREG_CFG_PHY_TM_POS;
	पूर्ण
	अगर ((cfg->dir == DMA_MEM_TO_DEV) ||
	    (cfg->dir == DMA_DEV_TO_DEV)) अणु
		/* Set master port to 1 */
		dst |= BIT(D40_SREG_CFG_MST_POS);
		dst |= D40_TYPE_TO_EVENT(cfg->dev_type);

		अगर (cfg->dst_info.flow_ctrl == STEDMA40_NO_FLOW_CTRL)
			dst |= BIT(D40_SREG_CFG_PHY_TM_POS);
		अन्यथा
			dst |= 3 << D40_SREG_CFG_PHY_TM_POS;
	पूर्ण
	/* Interrupt on end of transfer क्रम destination */
	dst |= BIT(D40_SREG_CFG_TIM_POS);

	/* Generate पूर्णांकerrupt on error */
	src |= BIT(D40_SREG_CFG_EIM_POS);
	dst |= BIT(D40_SREG_CFG_EIM_POS);

	/* PSIZE */
	अगर (cfg->src_info.psize != STEDMA40_PSIZE_PHY_1) अणु
		src |= BIT(D40_SREG_CFG_PHY_PEN_POS);
		src |= cfg->src_info.psize << D40_SREG_CFG_PSIZE_POS;
	पूर्ण
	अगर (cfg->dst_info.psize != STEDMA40_PSIZE_PHY_1) अणु
		dst |= BIT(D40_SREG_CFG_PHY_PEN_POS);
		dst |= cfg->dst_info.psize << D40_SREG_CFG_PSIZE_POS;
	पूर्ण

	/* Element size */
	src |= d40_width_to_bits(cfg->src_info.data_width)
		<< D40_SREG_CFG_ESIZE_POS;
	dst |= d40_width_to_bits(cfg->dst_info.data_width)
		<< D40_SREG_CFG_ESIZE_POS;

	/* Set the priority bit to high क्रम the physical channel */
	अगर (cfg->high_priority) अणु
		src |= BIT(D40_SREG_CFG_PRI_POS);
		dst |= BIT(D40_SREG_CFG_PRI_POS);
	पूर्ण

	अगर (cfg->src_info.big_endian)
		src |= BIT(D40_SREG_CFG_LBE_POS);
	अगर (cfg->dst_info.big_endian)
		dst |= BIT(D40_SREG_CFG_LBE_POS);

	*src_cfg = src;
	*dst_cfg = dst;
पूर्ण

अटल पूर्णांक d40_phy_fill_lli(काष्ठा d40_phy_lli *lli,
			    dma_addr_t data,
			    u32 data_size,
			    dma_addr_t next_lli,
			    u32 reg_cfg,
			    काष्ठा stedma40_half_channel_info *info,
			    अचिन्हित पूर्णांक flags)
अणु
	bool addr_inc = flags & LLI_ADDR_INC;
	bool term_पूर्णांक = flags & LLI_TERM_INT;
	अचिन्हित पूर्णांक data_width = info->data_width;
	पूर्णांक psize = info->psize;
	पूर्णांक num_elems;

	अगर (psize == STEDMA40_PSIZE_PHY_1)
		num_elems = 1;
	अन्यथा
		num_elems = 2 << psize;

	/* Must be aligned */
	अगर (!IS_ALIGNED(data, data_width))
		वापस -EINVAL;

	/* Transfer size can't be smaller than (num_elms * elem_size) */
	अगर (data_size < num_elems * data_width)
		वापस -EINVAL;

	/* The number of elements. IE now many chunks */
	lli->reg_elt = (data_size / data_width) << D40_SREG_ELEM_PHY_ECNT_POS;

	/*
	 * Distance to next element sized entry.
	 * Usually the size of the element unless you want gaps.
	 */
	अगर (addr_inc)
		lli->reg_elt |= data_width << D40_SREG_ELEM_PHY_EIDX_POS;

	/* Where the data is */
	lli->reg_ptr = data;
	lli->reg_cfg = reg_cfg;

	/* If this scatter list entry is the last one, no next link */
	अगर (next_lli == 0)
		lli->reg_lnk = BIT(D40_SREG_LNK_PHY_TCP_POS);
	अन्यथा
		lli->reg_lnk = next_lli;

	/* Set/clear पूर्णांकerrupt generation on this link item.*/
	अगर (term_पूर्णांक)
		lli->reg_cfg |= BIT(D40_SREG_CFG_TIM_POS);
	अन्यथा
		lli->reg_cfg &= ~BIT(D40_SREG_CFG_TIM_POS);

	/*
	 * Post link - D40_SREG_LNK_PHY_PRE_POS = 0
	 * Relink happens after transfer completion.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक d40_seg_size(पूर्णांक size, पूर्णांक data_width1, पूर्णांक data_width2)
अणु
	u32 max_w = max(data_width1, data_width2);
	u32 min_w = min(data_width1, data_width2);
	u32 seg_max = ALIGN(STEDMA40_MAX_SEG_SIZE * min_w, max_w);

	अगर (seg_max > STEDMA40_MAX_SEG_SIZE)
		seg_max -= max_w;

	अगर (size <= seg_max)
		वापस size;

	अगर (size <= 2 * seg_max)
		वापस ALIGN(size / 2, max_w);

	वापस seg_max;
पूर्ण

अटल काष्ठा d40_phy_lli *
d40_phy_buf_to_lli(काष्ठा d40_phy_lli *lli, dma_addr_t addr, u32 size,
		   dma_addr_t lli_phys, dma_addr_t first_phys, u32 reg_cfg,
		   काष्ठा stedma40_half_channel_info *info,
		   काष्ठा stedma40_half_channel_info *otherinfo,
		   अचिन्हित दीर्घ flags)
अणु
	bool lastlink = flags & LLI_LAST_LINK;
	bool addr_inc = flags & LLI_ADDR_INC;
	bool term_पूर्णांक = flags & LLI_TERM_INT;
	bool cyclic = flags & LLI_CYCLIC;
	पूर्णांक err;
	dma_addr_t next = lli_phys;
	पूर्णांक size_rest = size;
	पूर्णांक size_seg = 0;

	/*
	 * This piece may be split up based on d40_seg_size(); we only want the
	 * term पूर्णांक on the last part.
	 */
	अगर (term_पूर्णांक)
		flags &= ~LLI_TERM_INT;

	करो अणु
		size_seg = d40_seg_size(size_rest, info->data_width,
					otherinfo->data_width);
		size_rest -= size_seg;

		अगर (size_rest == 0 && term_पूर्णांक)
			flags |= LLI_TERM_INT;

		अगर (size_rest == 0 && lastlink)
			next = cyclic ? first_phys : 0;
		अन्यथा
			next = ALIGN(next + माप(काष्ठा d40_phy_lli),
				     D40_LLI_ALIGN);

		err = d40_phy_fill_lli(lli, addr, size_seg, next,
				       reg_cfg, info, flags);

		अगर (err)
			जाओ err;

		lli++;
		अगर (addr_inc)
			addr += size_seg;
	पूर्ण जबतक (size_rest);

	वापस lli;

err:
	वापस शून्य;
पूर्ण

पूर्णांक d40_phy_sg_to_lli(काष्ठा scatterlist *sg,
		      पूर्णांक sg_len,
		      dma_addr_t target,
		      काष्ठा d40_phy_lli *lli_sg,
		      dma_addr_t lli_phys,
		      u32 reg_cfg,
		      काष्ठा stedma40_half_channel_info *info,
		      काष्ठा stedma40_half_channel_info *otherinfo,
		      अचिन्हित दीर्घ flags)
अणु
	पूर्णांक total_size = 0;
	पूर्णांक i;
	काष्ठा scatterlist *current_sg = sg;
	काष्ठा d40_phy_lli *lli = lli_sg;
	dma_addr_t l_phys = lli_phys;

	अगर (!target)
		flags |= LLI_ADDR_INC;

	क्रम_each_sg(sg, current_sg, sg_len, i) अणु
		dma_addr_t sg_addr = sg_dma_address(current_sg);
		अचिन्हित पूर्णांक len = sg_dma_len(current_sg);
		dma_addr_t dst = target ?: sg_addr;

		total_size += sg_dma_len(current_sg);

		अगर (i == sg_len - 1)
			flags |= LLI_TERM_INT | LLI_LAST_LINK;

		l_phys = ALIGN(lli_phys + (lli - lli_sg) *
			       माप(काष्ठा d40_phy_lli), D40_LLI_ALIGN);

		lli = d40_phy_buf_to_lli(lli, dst, len, l_phys, lli_phys,
					 reg_cfg, info, otherinfo, flags);

		अगर (lli == शून्य)
			वापस -EINVAL;
	पूर्ण

	वापस total_size;
पूर्ण


/* DMA logical lli operations */

अटल व्योम d40_log_lli_link(काष्ठा d40_log_lli *lli_dst,
			     काष्ठा d40_log_lli *lli_src,
			     पूर्णांक next, अचिन्हित पूर्णांक flags)
अणु
	bool पूर्णांकerrupt = flags & LLI_TERM_INT;
	u32 slos = 0;
	u32 dlos = 0;

	अगर (next != -EINVAL) अणु
		slos = next * 2;
		dlos = next * 2 + 1;
	पूर्ण

	अगर (पूर्णांकerrupt) अणु
		lli_dst->lcsp13 |= D40_MEM_LCSP1_SCFG_TIM_MASK;
		lli_dst->lcsp13 |= D40_MEM_LCSP3_DTCP_MASK;
	पूर्ण

	lli_src->lcsp13 = (lli_src->lcsp13 & ~D40_MEM_LCSP1_SLOS_MASK) |
		(slos << D40_MEM_LCSP1_SLOS_POS);

	lli_dst->lcsp13 = (lli_dst->lcsp13 & ~D40_MEM_LCSP1_SLOS_MASK) |
		(dlos << D40_MEM_LCSP1_SLOS_POS);
पूर्ण

व्योम d40_log_lli_lcpa_ग_लिखो(काष्ठा d40_log_lli_full *lcpa,
			   काष्ठा d40_log_lli *lli_dst,
			   काष्ठा d40_log_lli *lli_src,
			   पूर्णांक next, अचिन्हित पूर्णांक flags)
अणु
	d40_log_lli_link(lli_dst, lli_src, next, flags);

	ग_लिखोl_relaxed(lli_src->lcsp02, &lcpa[0].lcsp0);
	ग_लिखोl_relaxed(lli_src->lcsp13, &lcpa[0].lcsp1);
	ग_लिखोl_relaxed(lli_dst->lcsp02, &lcpa[0].lcsp2);
	ग_लिखोl_relaxed(lli_dst->lcsp13, &lcpa[0].lcsp3);
पूर्ण

व्योम d40_log_lli_lcla_ग_लिखो(काष्ठा d40_log_lli *lcla,
			   काष्ठा d40_log_lli *lli_dst,
			   काष्ठा d40_log_lli *lli_src,
			   पूर्णांक next, अचिन्हित पूर्णांक flags)
अणु
	d40_log_lli_link(lli_dst, lli_src, next, flags);

	ग_लिखोl_relaxed(lli_src->lcsp02, &lcla[0].lcsp02);
	ग_लिखोl_relaxed(lli_src->lcsp13, &lcla[0].lcsp13);
	ग_लिखोl_relaxed(lli_dst->lcsp02, &lcla[1].lcsp02);
	ग_लिखोl_relaxed(lli_dst->lcsp13, &lcla[1].lcsp13);
पूर्ण

अटल व्योम d40_log_fill_lli(काष्ठा d40_log_lli *lli,
			     dma_addr_t data, u32 data_size,
			     u32 reg_cfg,
			     u32 data_width,
			     अचिन्हित पूर्णांक flags)
अणु
	bool addr_inc = flags & LLI_ADDR_INC;

	lli->lcsp13 = reg_cfg;

	/* The number of elements to transfer */
	lli->lcsp02 = ((data_size / data_width) <<
		       D40_MEM_LCSP0_ECNT_POS) & D40_MEM_LCSP0_ECNT_MASK;

	BUG_ON((data_size / data_width) > STEDMA40_MAX_SEG_SIZE);

	/* 16 LSBs address of the current element */
	lli->lcsp02 |= data & D40_MEM_LCSP0_SPTR_MASK;
	/* 16 MSBs address of the current element */
	lli->lcsp13 |= data & D40_MEM_LCSP1_SPTR_MASK;

	अगर (addr_inc)
		lli->lcsp13 |= D40_MEM_LCSP1_SCFG_INCR_MASK;

पूर्ण

अटल काष्ठा d40_log_lli *d40_log_buf_to_lli(काष्ठा d40_log_lli *lli_sg,
				       dma_addr_t addr,
				       पूर्णांक size,
				       u32 lcsp13, /* src or dst*/
				       u32 data_width1,
				       u32 data_width2,
				       अचिन्हित पूर्णांक flags)
अणु
	bool addr_inc = flags & LLI_ADDR_INC;
	काष्ठा d40_log_lli *lli = lli_sg;
	पूर्णांक size_rest = size;
	पूर्णांक size_seg = 0;

	करो अणु
		size_seg = d40_seg_size(size_rest, data_width1, data_width2);
		size_rest -= size_seg;

		d40_log_fill_lli(lli,
				 addr,
				 size_seg,
				 lcsp13, data_width1,
				 flags);
		अगर (addr_inc)
			addr += size_seg;
		lli++;
	पूर्ण जबतक (size_rest);

	वापस lli;
पूर्ण

पूर्णांक d40_log_sg_to_lli(काष्ठा scatterlist *sg,
		      पूर्णांक sg_len,
		      dma_addr_t dev_addr,
		      काष्ठा d40_log_lli *lli_sg,
		      u32 lcsp13, /* src or dst*/
		      u32 data_width1, u32 data_width2)
अणु
	पूर्णांक total_size = 0;
	काष्ठा scatterlist *current_sg = sg;
	पूर्णांक i;
	काष्ठा d40_log_lli *lli = lli_sg;
	अचिन्हित दीर्घ flags = 0;

	अगर (!dev_addr)
		flags |= LLI_ADDR_INC;

	क्रम_each_sg(sg, current_sg, sg_len, i) अणु
		dma_addr_t sg_addr = sg_dma_address(current_sg);
		अचिन्हित पूर्णांक len = sg_dma_len(current_sg);
		dma_addr_t addr = dev_addr ?: sg_addr;

		total_size += sg_dma_len(current_sg);

		lli = d40_log_buf_to_lli(lli, addr, len,
					 lcsp13,
					 data_width1,
					 data_width2,
					 flags);
	पूर्ण

	वापस total_size;
पूर्ण
