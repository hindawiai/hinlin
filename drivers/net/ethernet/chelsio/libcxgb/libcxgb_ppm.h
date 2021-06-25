<शैली गुरु>
/*
 * libcxgb_ppm.h: Chelsio common library क्रम T3/T4/T5 iSCSI ddp operation
 *
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Written by: Karen Xie (kxie@chelsio.com)
 */

#अगर_अघोषित	__LIBCXGB_PPM_H__
#घोषणा	__LIBCXGB_PPM_H__

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/biपंचांगap.h>

काष्ठा cxgbi_pagepod_hdr अणु
	u32 vld_tid;
	u32 pgsz_tag_clr;
	u32 max_offset;
	u32 page_offset;
	u64 rsvd;
पूर्ण;

#घोषणा PPOD_PAGES_MAX			4
काष्ठा cxgbi_pagepod अणु
	काष्ठा cxgbi_pagepod_hdr hdr;
	__be64 addr[PPOD_PAGES_MAX + 1];
पूर्ण;

/* ddp tag क्रमmat
 * क्रम a 32-bit tag:
 * bit #
 * 31 .....   .....  0
 *     X   Y...Y Z...Z, where
 *     ^   ^^^^^ ^^^^
 *     |   |      |____ when ddp bit = 0: color bits
 *     |   |
 *     |   |____ when ddp bit = 0: idx पूर्णांकo the ddp memory region
 *     |
 *     |____ ddp bit: 0 - ddp tag, 1 - non-ddp tag
 *
 *  [page selector:2] [sw/मुक्त bits] [0] [idx] [color:6]
 */

#घोषणा DDP_PGIDX_MAX		4
#घोषणा DDP_PGSZ_BASE_SHIFT	12	/* base page 4K */

काष्ठा cxgbi_task_tag_info अणु
	अचिन्हित अक्षर flags;
#घोषणा CXGBI_PPOD_INFO_FLAG_VALID	0x1
#घोषणा CXGBI_PPOD_INFO_FLAG_MAPPED	0x2
	अचिन्हित अक्षर cid;
	अचिन्हित लघु pg_shअगरt;
	अचिन्हित पूर्णांक npods;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक tag;
	काष्ठा cxgbi_pagepod_hdr hdr;
	पूर्णांक nents;
	पूर्णांक nr_pages;
	काष्ठा scatterlist *sgl;
पूर्ण;

काष्ठा cxgbi_tag_क्रमmat अणु
	अचिन्हित अक्षर pgsz_order[DDP_PGIDX_MAX];
	अचिन्हित अक्षर pgsz_idx_dflt;
	अचिन्हित अक्षर मुक्त_bits:4;
	अचिन्हित अक्षर color_bits:4;
	अचिन्हित अक्षर idx_bits;
	अचिन्हित अक्षर rsvd_bits;
	अचिन्हित पूर्णांक  no_ddp_mask;
	अचिन्हित पूर्णांक  idx_mask;
	अचिन्हित पूर्णांक  color_mask;
	अचिन्हित पूर्णांक  idx_clr_mask;
	अचिन्हित पूर्णांक  rsvd_mask;
पूर्ण;

काष्ठा cxgbi_ppod_data अणु
	अचिन्हित अक्षर pg_idx:2;
	अचिन्हित अक्षर color:6;
	अचिन्हित अक्षर chan_id;
	अचिन्हित लघु npods;
	अचिन्हित दीर्घ caller_data;
पूर्ण;

/* per cpu ppm pool */
काष्ठा cxgbi_ppm_pool अणु
	अचिन्हित पूर्णांक base;		/* base index */
	अचिन्हित पूर्णांक next;		/* next possible मुक्त index */
	spinlock_t lock;		/* ppm pool lock */
	अचिन्हित दीर्घ bmap[];
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा cxgbi_ppm अणु
	काष्ठा kref refcnt;
	काष्ठा net_device *ndev;	/* net_device, 1st port */
	काष्ठा pci_dev *pdev;
	व्योम *lldev;
	व्योम **ppm_pp;
	काष्ठा cxgbi_tag_क्रमmat tक्रमmat;
	अचिन्हित पूर्णांक ppmax;
	अचिन्हित पूर्णांक llimit;
	अचिन्हित पूर्णांक base_idx;

	अचिन्हित पूर्णांक pool_rsvd;
	अचिन्हित पूर्णांक pool_index_max;
	काष्ठा cxgbi_ppm_pool __percpu *pool;
	/* map lock */
	spinlock_t map_lock;		/* ppm map lock */
	अचिन्हित पूर्णांक bmap_index_max;
	अचिन्हित पूर्णांक next;
	अचिन्हित पूर्णांक max_index_in_edram;
	अचिन्हित दीर्घ *ppod_bmap;
	काष्ठा cxgbi_ppod_data ppod_data[];
पूर्ण;

#घोषणा DDP_THRESHOLD		512

#घोषणा PPOD_PAGES_SHIFT	2       /*  4 pages per pod */

#घोषणा IPPOD_SIZE               माप(काष्ठा cxgbi_pagepod)  /*  64 */
#घोषणा PPOD_SIZE_SHIFT         6

/* page pods are allocated in groups of this size (must be घातer of 2) */
#घोषणा PPOD_CLUSTER_SIZE	16U

#घोषणा ULPMEM_DSGL_MAX_NPPODS	16	/*  1024/PPOD_SIZE */
#घोषणा ULPMEM_IDATA_MAX_NPPODS	3	/* (PPOD_SIZE * 3 + ulptx hdr) < 256B */
#घोषणा PCIE_MEMWIN_MAX_NPPODS	16	/*  1024/PPOD_SIZE */

#घोषणा PPOD_COLOR_SHIFT	0
#घोषणा PPOD_COLOR(x)		((x) << PPOD_COLOR_SHIFT)

#घोषणा PPOD_IDX_SHIFT          6
#घोषणा PPOD_IDX_MAX_SIZE       24

#घोषणा PPOD_TID_SHIFT		0
#घोषणा PPOD_TID(x)		((x) << PPOD_TID_SHIFT)

#घोषणा PPOD_TAG_SHIFT		6
#घोषणा PPOD_TAG(x)		((x) << PPOD_TAG_SHIFT)

#घोषणा PPOD_VALID_SHIFT	24
#घोषणा PPOD_VALID(x)		((x) << PPOD_VALID_SHIFT)
#घोषणा PPOD_VALID_FLAG		PPOD_VALID(1U)

#घोषणा PPOD_PI_EXTRACT_CTL_SHIFT	31
#घोषणा PPOD_PI_EXTRACT_CTL(x)		((x) << PPOD_PI_EXTRACT_CTL_SHIFT)
#घोषणा PPOD_PI_EXTRACT_CTL_FLAG	V_PPOD_PI_EXTRACT_CTL(1U)

#घोषणा PPOD_PI_TYPE_SHIFT		29
#घोषणा PPOD_PI_TYPE_MASK		0x3
#घोषणा PPOD_PI_TYPE(x)			((x) << PPOD_PI_TYPE_SHIFT)

#घोषणा PPOD_PI_CHECK_CTL_SHIFT		27
#घोषणा PPOD_PI_CHECK_CTL_MASK		0x3
#घोषणा PPOD_PI_CHECK_CTL(x)		((x) << PPOD_PI_CHECK_CTL_SHIFT)

#घोषणा PPOD_PI_REPORT_CTL_SHIFT	25
#घोषणा PPOD_PI_REPORT_CTL_MASK		0x3
#घोषणा PPOD_PI_REPORT_CTL(x)		((x) << PPOD_PI_REPORT_CTL_SHIFT)

अटल अंतरभूत पूर्णांक cxgbi_ppm_is_ddp_tag(काष्ठा cxgbi_ppm *ppm, u32 tag)
अणु
	वापस !(tag & ppm->tक्रमmat.no_ddp_mask);
पूर्ण

अटल अंतरभूत पूर्णांक cxgbi_ppm_sw_tag_is_usable(काष्ठा cxgbi_ppm *ppm,
					     u32 tag)
अणु
	/* the sw tag must be using <= 31 bits */
	वापस !(tag & 0x80000000U);
पूर्ण

अटल अंतरभूत पूर्णांक cxgbi_ppm_make_non_ddp_tag(काष्ठा cxgbi_ppm *ppm,
					     u32 sw_tag,
					     u32 *final_tag)
अणु
	काष्ठा cxgbi_tag_क्रमmat *tक्रमmat = &ppm->tक्रमmat;

	अगर (!cxgbi_ppm_sw_tag_is_usable(ppm, sw_tag)) अणु
		pr_info("sw_tag 0x%x NOT usable.\n", sw_tag);
		वापस -EINVAL;
	पूर्ण

	अगर (!sw_tag) अणु
		*final_tag = tक्रमmat->no_ddp_mask;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक shअगरt = tक्रमmat->idx_bits + tक्रमmat->color_bits;
		u32 lower = sw_tag & tक्रमmat->idx_clr_mask;
		u32 upper = (sw_tag >> shअगरt) << (shअगरt + 1);

		*final_tag = upper | tक्रमmat->no_ddp_mask | lower;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u32 cxgbi_ppm_decode_non_ddp_tag(काष्ठा cxgbi_ppm *ppm,
					       u32 tag)
अणु
	काष्ठा cxgbi_tag_क्रमmat *tक्रमmat = &ppm->tक्रमmat;
	अचिन्हित पूर्णांक shअगरt = tक्रमmat->idx_bits + tक्रमmat->color_bits;
	u32 lower = tag & tक्रमmat->idx_clr_mask;
	u32 upper = (tag >> tक्रमmat->rsvd_bits) << shअगरt;

	वापस upper | lower;
पूर्ण

अटल अंतरभूत u32 cxgbi_ppm_ddp_tag_get_idx(काष्ठा cxgbi_ppm *ppm,
					    u32 ddp_tag)
अणु
	u32 hw_idx = (ddp_tag >> PPOD_IDX_SHIFT) &
			ppm->tक्रमmat.idx_mask;

	वापस hw_idx - ppm->base_idx;
पूर्ण

अटल अंतरभूत u32 cxgbi_ppm_make_ddp_tag(अचिन्हित पूर्णांक hw_idx,
					 अचिन्हित अक्षर color)
अणु
	वापस (hw_idx << PPOD_IDX_SHIFT) | ((u32)color);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
cxgbi_ppm_get_tag_caller_data(काष्ठा cxgbi_ppm *ppm,
			      u32 ddp_tag)
अणु
	u32 idx = cxgbi_ppm_ddp_tag_get_idx(ppm, ddp_tag);

	वापस ppm->ppod_data[idx].caller_data;
पूर्ण

/* sw bits are the मुक्त bits */
अटल अंतरभूत पूर्णांक cxgbi_ppm_ddp_tag_update_sw_bits(काष्ठा cxgbi_ppm *ppm,
						   u32 val, u32 orig_tag,
						   u32 *final_tag)
अणु
	काष्ठा cxgbi_tag_क्रमmat *tक्रमmat = &ppm->tक्रमmat;
	u32 v = val >> tक्रमmat->मुक्त_bits;

	अगर (v) अणु
		pr_info("sw_bits 0x%x too large, avail bits %u.\n",
			val, tक्रमmat->मुक्त_bits);
		वापस -EINVAL;
	पूर्ण
	अगर (!cxgbi_ppm_is_ddp_tag(ppm, orig_tag))
		वापस -EINVAL;

	*final_tag = (val << tक्रमmat->rsvd_bits) |
		     (orig_tag & ppm->tक्रमmat.rsvd_mask);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cxgbi_ppm_ppod_clear(काष्ठा cxgbi_pagepod *ppod)
अणु
	ppod->hdr.vld_tid = 0U;
पूर्ण

अटल अंतरभूत व्योम cxgbi_tagmask_check(अचिन्हित पूर्णांक tagmask,
				       काष्ठा cxgbi_tag_क्रमmat *tक्रमmat)
अणु
	अचिन्हित पूर्णांक bits = fls(tagmask);

	/* reserve top most 2 bits क्रम page selector */
	tक्रमmat->मुक्त_bits = 32 - 2 - bits;
	tक्रमmat->rsvd_bits = bits;
	tक्रमmat->color_bits = PPOD_IDX_SHIFT;
	tक्रमmat->idx_bits = bits - 1 - PPOD_IDX_SHIFT;
	tक्रमmat->no_ddp_mask = 1 << (bits - 1);
	tक्रमmat->idx_mask = (1 << tक्रमmat->idx_bits) - 1;
	tक्रमmat->color_mask = (1 << PPOD_IDX_SHIFT) - 1;
	tक्रमmat->idx_clr_mask = (1 << (bits - 1)) - 1;
	tक्रमmat->rsvd_mask = (1 << bits) - 1;

	pr_info("ippm: tagmask 0x%x, rsvd %u=%u+%u+1, mask 0x%x,0x%x, "
		"pg %u,%u,%u,%u.\n",
		tagmask, tक्रमmat->rsvd_bits, tक्रमmat->idx_bits,
		tक्रमmat->color_bits, tक्रमmat->no_ddp_mask, tक्रमmat->rsvd_mask,
		tक्रमmat->pgsz_order[0], tक्रमmat->pgsz_order[1],
		tक्रमmat->pgsz_order[2], tक्रमmat->pgsz_order[3]);
पूर्ण

पूर्णांक cxgbi_ppm_find_page_index(काष्ठा cxgbi_ppm *ppm, अचिन्हित दीर्घ pgsz);
व्योम cxgbi_ppm_make_ppod_hdr(काष्ठा cxgbi_ppm *ppm, u32 tag,
			     अचिन्हित पूर्णांक tid, अचिन्हित पूर्णांक offset,
			     अचिन्हित पूर्णांक length,
			     काष्ठा cxgbi_pagepod_hdr *hdr);
व्योम cxgbi_ppm_ppod_release(काष्ठा cxgbi_ppm *, u32 idx);
पूर्णांक cxgbi_ppm_ppods_reserve(काष्ठा cxgbi_ppm *, अचिन्हित लघु nr_pages,
			    u32 per_tag_pg_idx, u32 *ppod_idx, u32 *ddp_tag,
			    अचिन्हित दीर्घ caller_data);
पूर्णांक cxgbi_ppm_init(व्योम **ppm_pp, काष्ठा net_device *, काष्ठा pci_dev *,
		   व्योम *lldev, काष्ठा cxgbi_tag_क्रमmat *,
		   अचिन्हित पूर्णांक iscsi_size, अचिन्हित पूर्णांक llimit,
		   अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक reserve_factor,
		   अचिन्हित पूर्णांक edram_start, अचिन्हित पूर्णांक edram_size);
पूर्णांक cxgbi_ppm_release(काष्ठा cxgbi_ppm *ppm);
व्योम cxgbi_tagmask_check(अचिन्हित पूर्णांक tagmask, काष्ठा cxgbi_tag_क्रमmat *);
अचिन्हित पूर्णांक cxgbi_tagmask_set(अचिन्हित पूर्णांक ppmax);

#पूर्ण_अगर	/*__LIBCXGB_PPM_H__*/
