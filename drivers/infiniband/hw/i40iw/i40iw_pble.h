<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
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
*******************************************************************************/

#अगर_अघोषित I40IW_PBLE_H
#घोषणा I40IW_PBLE_H

#घोषणा POOL_SHIFT      6
#घोषणा PBLE_PER_PAGE   512
#घोषणा I40IW_HMC_PAGED_BP_SHIFT 12
#घोषणा PBLE_512_SHIFT  9

क्रमागत i40iw_pble_level अणु
	I40IW_LEVEL_0 = 0,
	I40IW_LEVEL_1 = 1,
	I40IW_LEVEL_2 = 2
पूर्ण;

क्रमागत i40iw_alloc_type अणु
	I40IW_NO_ALLOC = 0,
	I40IW_DMA_COHERENT = 1,
	I40IW_VMALLOC = 2
पूर्ण;

काष्ठा i40iw_pble_info अणु
	अचिन्हित दीर्घ addr;
	u32 idx;
	u32 cnt;
पूर्ण;

काष्ठा i40iw_pble_level2 अणु
	काष्ठा i40iw_pble_info root;
	काष्ठा i40iw_pble_info *leaf;
	u32 leaf_cnt;
पूर्ण;

काष्ठा i40iw_pble_alloc अणु
	u32 total_cnt;
	क्रमागत i40iw_pble_level level;
	जोड़ अणु
		काष्ठा i40iw_pble_info level1;
		काष्ठा i40iw_pble_level2 level2;
	पूर्ण;
पूर्ण;

काष्ठा sd_pd_idx अणु
	u32 sd_idx;
	u32 pd_idx;
	u32 rel_pd_idx;
पूर्ण;

काष्ठा i40iw_add_page_info अणु
	काष्ठा i40iw_chunk *chunk;
	काष्ठा i40iw_hmc_sd_entry *sd_entry;
	काष्ठा i40iw_hmc_info *hmc_info;
	काष्ठा sd_pd_idx idx;
	u32 pages;
पूर्ण;

काष्ठा i40iw_chunk अणु
	काष्ठा list_head list;
	u32 size;
	व्योम *vaddr;
	u64 fpm_addr;
	u32 pg_cnt;
	dma_addr_t *dmaaddrs;
	क्रमागत i40iw_alloc_type type;
पूर्ण;

काष्ठा i40iw_pble_pool अणु
	काष्ठा gen_pool *pool;
	काष्ठा list_head clist;
	u32 total_pble_alloc;
	u32 मुक्त_pble_cnt;
	u32 pool_shअगरt;
पूर्ण;

काष्ठा i40iw_hmc_pble_rsrc अणु
	u32 unallocated_pble;
	u64 fpm_base_addr;
	u64 next_fpm_addr;
	काष्ठा i40iw_pble_pool pinfo;

	u32 stats_direct_sds;
	u32 stats_paged_sds;
	u64 stats_alloc_ok;
	u64 stats_alloc_fail;
	u64 stats_alloc_मुक्तd;
	u64 stats_lvl1;
	u64 stats_lvl2;
पूर्ण;

व्योम i40iw_destroy_pble_pool(काष्ठा i40iw_sc_dev *dev, काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc);
क्रमागत i40iw_status_code i40iw_hmc_init_pble(काष्ठा i40iw_sc_dev *dev,
					   काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc);
व्योम i40iw_मुक्त_pble(काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc, काष्ठा i40iw_pble_alloc *palloc);
क्रमागत i40iw_status_code i40iw_get_pble(काष्ठा i40iw_sc_dev *dev,
				      काष्ठा i40iw_hmc_pble_rsrc *pble_rsrc,
				      काष्ठा i40iw_pble_alloc *palloc,
				      u32 pble_cnt);
#पूर्ण_अगर
