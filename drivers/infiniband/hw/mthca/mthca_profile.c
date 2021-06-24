<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
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
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश "mthca_profile.h"

क्रमागत अणु
	MTHCA_RES_QP,
	MTHCA_RES_EEC,
	MTHCA_RES_SRQ,
	MTHCA_RES_CQ,
	MTHCA_RES_EQP,
	MTHCA_RES_EEEC,
	MTHCA_RES_EQ,
	MTHCA_RES_RDB,
	MTHCA_RES_MCG,
	MTHCA_RES_MPT,
	MTHCA_RES_MTT,
	MTHCA_RES_UAR,
	MTHCA_RES_UDAV,
	MTHCA_RES_UARC,
	MTHCA_RES_NUM
पूर्ण;

क्रमागत अणु
	MTHCA_NUM_EQS = 32,
	MTHCA_NUM_PDS = 1 << 15
पूर्ण;

s64 mthca_make_profile(काष्ठा mthca_dev *dev,
		       काष्ठा mthca_profile *request,
		       काष्ठा mthca_dev_lim *dev_lim,
		       काष्ठा mthca_init_hca_param *init_hca)
अणु
	काष्ठा mthca_resource अणु
		u64 size;
		u64 start;
		पूर्णांक type;
		पूर्णांक num;
		पूर्णांक log_num;
	पूर्ण;

	u64 mem_base, mem_avail;
	s64 total_size = 0;
	काष्ठा mthca_resource *profile;
	पूर्णांक i, j;

	profile = kसुस्मृति(MTHCA_RES_NUM, माप(*profile), GFP_KERNEL);
	अगर (!profile)
		वापस -ENOMEM;

	profile[MTHCA_RES_QP].size   = dev_lim->qpc_entry_sz;
	profile[MTHCA_RES_EEC].size  = dev_lim->eec_entry_sz;
	profile[MTHCA_RES_SRQ].size  = dev_lim->srq_entry_sz;
	profile[MTHCA_RES_CQ].size   = dev_lim->cqc_entry_sz;
	profile[MTHCA_RES_EQP].size  = dev_lim->eqpc_entry_sz;
	profile[MTHCA_RES_EEEC].size = dev_lim->eeec_entry_sz;
	profile[MTHCA_RES_EQ].size   = dev_lim->eqc_entry_sz;
	profile[MTHCA_RES_RDB].size  = MTHCA_RDB_ENTRY_SIZE;
	profile[MTHCA_RES_MCG].size  = MTHCA_MGM_ENTRY_SIZE;
	profile[MTHCA_RES_MPT].size  = dev_lim->mpt_entry_sz;
	profile[MTHCA_RES_MTT].size  = dev->limits.mtt_seg_size;
	profile[MTHCA_RES_UAR].size  = dev_lim->uar_scratch_entry_sz;
	profile[MTHCA_RES_UDAV].size = MTHCA_AV_SIZE;
	profile[MTHCA_RES_UARC].size = request->uarc_size;

	profile[MTHCA_RES_QP].num    = request->num_qp;
	profile[MTHCA_RES_SRQ].num   = request->num_srq;
	profile[MTHCA_RES_EQP].num   = request->num_qp;
	profile[MTHCA_RES_RDB].num   = request->num_qp * request->rdb_per_qp;
	profile[MTHCA_RES_CQ].num    = request->num_cq;
	profile[MTHCA_RES_EQ].num    = MTHCA_NUM_EQS;
	profile[MTHCA_RES_MCG].num   = request->num_mcg;
	profile[MTHCA_RES_MPT].num   = request->num_mpt;
	profile[MTHCA_RES_MTT].num   = request->num_mtt;
	profile[MTHCA_RES_UAR].num   = request->num_uar;
	profile[MTHCA_RES_UARC].num  = request->num_uar;
	profile[MTHCA_RES_UDAV].num  = request->num_udav;

	क्रम (i = 0; i < MTHCA_RES_NUM; ++i) अणु
		profile[i].type     = i;
		profile[i].log_num  = max(ffs(profile[i].num) - 1, 0);
		profile[i].size    *= profile[i].num;
		अगर (mthca_is_memमुक्त(dev))
			profile[i].size = max(profile[i].size, (u64) PAGE_SIZE);
	पूर्ण

	अगर (mthca_is_memमुक्त(dev)) अणु
		mem_base  = 0;
		mem_avail = dev_lim->hca.arbel.max_icm_sz;
	पूर्ण अन्यथा अणु
		mem_base  = dev->ddr_start;
		mem_avail = dev->fw.tavor.fw_start - dev->ddr_start;
	पूर्ण

	/*
	 * Sort the resources in decreasing order of size.  Since they
	 * all have sizes that are घातers of 2, we'll be able to keep
	 * resources aligned to their size and pack them without gaps
	 * using the sorted order.
	 */
	क्रम (i = MTHCA_RES_NUM; i > 0; --i)
		क्रम (j = 1; j < i; ++j) अणु
			अगर (profile[j].size > profile[j - 1].size)
				swap(profile[j], profile[j - 1]);
		पूर्ण

	क्रम (i = 0; i < MTHCA_RES_NUM; ++i) अणु
		अगर (profile[i].size) अणु
			profile[i].start = mem_base + total_size;
			total_size      += profile[i].size;
		पूर्ण
		अगर (total_size > mem_avail) अणु
			mthca_err(dev, "Profile requires 0x%llx bytes; "
				  "won't fit in 0x%llx bytes of context memory.\n",
				  (अचिन्हित दीर्घ दीर्घ) total_size,
				  (अचिन्हित दीर्घ दीर्घ) mem_avail);
			kमुक्त(profile);
			वापस -ENOMEM;
		पूर्ण

		अगर (profile[i].size)
			mthca_dbg(dev, "profile[%2d]--%2d/%2d @ 0x%16llx "
				  "(size 0x%8llx)\n",
				  i, profile[i].type, profile[i].log_num,
				  (अचिन्हित दीर्घ दीर्घ) profile[i].start,
				  (अचिन्हित दीर्घ दीर्घ) profile[i].size);
	पूर्ण

	अगर (mthca_is_memमुक्त(dev))
		mthca_dbg(dev, "HCA context memory: reserving %d KB\n",
			  (पूर्णांक) (total_size >> 10));
	अन्यथा
		mthca_dbg(dev, "HCA memory: allocated %d KB/%d KB (%d KB free)\n",
			  (पूर्णांक) (total_size >> 10), (पूर्णांक) (mem_avail >> 10),
			  (पूर्णांक) ((mem_avail - total_size) >> 10));

	क्रम (i = 0; i < MTHCA_RES_NUM; ++i) अणु
		चयन (profile[i].type) अणु
		हाल MTHCA_RES_QP:
			dev->limits.num_qps   = profile[i].num;
			init_hca->qpc_base    = profile[i].start;
			init_hca->log_num_qps = profile[i].log_num;
			अवरोध;
		हाल MTHCA_RES_EEC:
			dev->limits.num_eecs   = profile[i].num;
			init_hca->eec_base     = profile[i].start;
			init_hca->log_num_eecs = profile[i].log_num;
			अवरोध;
		हाल MTHCA_RES_SRQ:
			dev->limits.num_srqs   = profile[i].num;
			init_hca->srqc_base    = profile[i].start;
			init_hca->log_num_srqs = profile[i].log_num;
			अवरोध;
		हाल MTHCA_RES_CQ:
			dev->limits.num_cqs   = profile[i].num;
			init_hca->cqc_base    = profile[i].start;
			init_hca->log_num_cqs = profile[i].log_num;
			अवरोध;
		हाल MTHCA_RES_EQP:
			init_hca->eqpc_base = profile[i].start;
			अवरोध;
		हाल MTHCA_RES_EEEC:
			init_hca->eeec_base = profile[i].start;
			अवरोध;
		हाल MTHCA_RES_EQ:
			dev->limits.num_eqs   = profile[i].num;
			init_hca->eqc_base    = profile[i].start;
			init_hca->log_num_eqs = profile[i].log_num;
			अवरोध;
		हाल MTHCA_RES_RDB:
			क्रम (dev->qp_table.rdb_shअगरt = 0;
			     request->num_qp << dev->qp_table.rdb_shअगरt < profile[i].num;
			     ++dev->qp_table.rdb_shअगरt)
				; /* nothing */
			dev->qp_table.rdb_base    = (u32) profile[i].start;
			init_hca->rdb_base        = profile[i].start;
			अवरोध;
		हाल MTHCA_RES_MCG:
			dev->limits.num_mgms      = profile[i].num >> 1;
			dev->limits.num_amgms     = profile[i].num >> 1;
			init_hca->mc_base         = profile[i].start;
			init_hca->log_mc_entry_sz = ffs(MTHCA_MGM_ENTRY_SIZE) - 1;
			init_hca->log_mc_table_sz = profile[i].log_num;
			init_hca->mc_hash_sz      = 1 << (profile[i].log_num - 1);
			अवरोध;
		हाल MTHCA_RES_MPT:
			dev->limits.num_mpts   = profile[i].num;
			dev->mr_table.mpt_base = profile[i].start;
			init_hca->mpt_base     = profile[i].start;
			init_hca->log_mpt_sz   = profile[i].log_num;
			अवरोध;
		हाल MTHCA_RES_MTT:
			dev->limits.num_mtt_segs = profile[i].num;
			dev->mr_table.mtt_base   = profile[i].start;
			init_hca->mtt_base       = profile[i].start;
			init_hca->mtt_seg_sz     = ffs(dev->limits.mtt_seg_size) - 7;
			अवरोध;
		हाल MTHCA_RES_UAR:
			dev->limits.num_uars       = profile[i].num;
			init_hca->uar_scratch_base = profile[i].start;
			अवरोध;
		हाल MTHCA_RES_UDAV:
			dev->av_table.ddr_av_base = profile[i].start;
			dev->av_table.num_ddr_avs = profile[i].num;
			अवरोध;
		हाल MTHCA_RES_UARC:
			dev->uar_table.uarc_size = request->uarc_size;
			dev->uar_table.uarc_base = profile[i].start;
			init_hca->uarc_base   	 = profile[i].start;
			init_hca->log_uarc_sz 	 = ffs(request->uarc_size) - 13;
			init_hca->log_uar_sz  	 = ffs(request->num_uar) - 1;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * PDs करोn't take any HCA memory, but we assign them as part
	 * of the HCA profile anyway.
	 */
	dev->limits.num_pds = MTHCA_NUM_PDS;

	अगर (dev->mthca_flags & MTHCA_FLAG_SINAI_OPT &&
	    init_hca->log_mpt_sz > 23) अणु
		mthca_warn(dev, "MPT table too large (requested size 2^%d >= 2^24)\न",
			   init_hca->log_mpt_sz);
		mthca_warn(dev, "Disabling memory key throughput optimization.\n");
		dev->mthca_flags &= ~MTHCA_FLAG_SINAI_OPT;
	पूर्ण

	/*
	 * For Tavor, FMRs use ioremapped PCI memory. For 32 bit
	 * प्रणालीs it may use too much vदो_स्मृति space to map all MTT
	 * memory, so we reserve some MTTs क्रम FMR access, taking them
	 * out of the MR pool. They करोn't use additional memory, but
	 * we assign them as part of the HCA profile anyway.
	 */
	अगर (mthca_is_memमुक्त(dev) || BITS_PER_LONG == 64)
		dev->limits.fmr_reserved_mtts = 0;
	अन्यथा
		dev->limits.fmr_reserved_mtts = request->fmr_reserved_mtts;

	kमुक्त(profile);
	वापस total_size;
पूर्ण
