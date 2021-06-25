<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SN Platक्रमm GRU Driver
 *
 *            DRIVER TABLE MANAGER + GRU CONTEXT LOAD/UNLOAD
 *
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/err.h>
#समावेश <linux/prefetch.h>
#समावेश <यंत्र/uv/uv_hub.h>
#समावेश "gru.h"
#समावेश "grutables.h"
#समावेश "gruhandles.h"

अचिन्हित दीर्घ gru_options __पढ़ो_mostly;

अटल काष्ठा device_driver gru_driver = अणु
	.name = "gru"
पूर्ण;

अटल काष्ठा device gru_device = अणु
	.init_name = "",
	.driver = &gru_driver,
पूर्ण;

काष्ठा device *grudev = &gru_device;

/*
 * Select a gru fault map to be used by the current cpu. Note that
 * multiple cpus may be using the same map.
 *	ZZZ should be अंतरभूत but did not work on emulator
 */
पूर्णांक gru_cpu_fault_map_id(व्योम)
अणु
#अगर_घोषित CONFIG_IA64
	वापस uv_blade_processor_id() % GRU_NUM_TFM;
#अन्यथा
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक id, core;

	core = uv_cpu_core_number(cpu);
	id = core + UV_MAX_INT_CORES * uv_cpu_socket_number(cpu);
	वापस id;
#पूर्ण_अगर
पूर्ण

/*--------- ASID Management -------------------------------------------
 *
 *  Initially, assign asids sequentially from MIN_ASID .. MAX_ASID.
 *  Once MAX is reached, flush the TLB & start over. However,
 *  some asids may still be in use. There won't be many (percentage wise) still
 *  in use. Search active contexts & determine the value of the first
 *  asid in use ("x"s below). Set "limit" to this value.
 *  This defines a block of assignable asids.
 *
 *  When "limit" is reached, search क्रमward from limit+1 and determine the
 *  next block of assignable asids.
 *
 *  Repeat until MAX_ASID is reached, then start over again.
 *
 *  Each समय MAX_ASID is reached, increment the asid generation. Since
 *  the search क्रम in-use asids only checks contexts with GRUs currently
 *  asचिन्हित, asids in some contexts will be missed. Prior to loading
 *  a context, the asid generation of the GTS asid is rechecked. If it
 *  करोesn't match the current generation, a new asid will be asचिन्हित.
 *
 *   	0---------------x------------x---------------------x----|
 *	  ^-next	^-limit	   				^-MAX_ASID
 *
 * All asid manipulation & context loading/unloading is रक्षित by the
 * gs_lock.
 */

/* Hit the asid limit. Start over */
अटल पूर्णांक gru_wrap_asid(काष्ठा gru_state *gru)
अणु
	gru_dbg(grudev, "gid %d\n", gru->gs_gid);
	STAT(asid_wrap);
	gru->gs_asid_gen++;
	वापस MIN_ASID;
पूर्ण

/* Find the next chunk of unused asids */
अटल पूर्णांक gru_reset_asid_limit(काष्ठा gru_state *gru, पूर्णांक asid)
अणु
	पूर्णांक i, gid, inuse_asid, limit;

	gru_dbg(grudev, "gid %d, asid 0x%x\n", gru->gs_gid, asid);
	STAT(asid_next);
	limit = MAX_ASID;
	अगर (asid >= limit)
		asid = gru_wrap_asid(gru);
	gru_flush_all_tlb(gru);
	gid = gru->gs_gid;
again:
	क्रम (i = 0; i < GRU_NUM_CCH; i++) अणु
		अगर (!gru->gs_gts[i] || is_kernel_context(gru->gs_gts[i]))
			जारी;
		inuse_asid = gru->gs_gts[i]->ts_gms->ms_asids[gid].mt_asid;
		gru_dbg(grudev, "gid %d, gts %p, gms %p, inuse 0x%x, cxt %d\n",
			gru->gs_gid, gru->gs_gts[i], gru->gs_gts[i]->ts_gms,
			inuse_asid, i);
		अगर (inuse_asid == asid) अणु
			asid += ASID_INC;
			अगर (asid >= limit) अणु
				/*
				 * empty range: reset the range limit and
				 * start over
				 */
				limit = MAX_ASID;
				अगर (asid >= MAX_ASID)
					asid = gru_wrap_asid(gru);
				जाओ again;
			पूर्ण
		पूर्ण

		अगर ((inuse_asid > asid) && (inuse_asid < limit))
			limit = inuse_asid;
	पूर्ण
	gru->gs_asid_limit = limit;
	gru->gs_asid = asid;
	gru_dbg(grudev, "gid %d, new asid 0x%x, new_limit 0x%x\n", gru->gs_gid,
					asid, limit);
	वापस asid;
पूर्ण

/* Assign a new ASID to a thपढ़ो context.  */
अटल पूर्णांक gru_assign_asid(काष्ठा gru_state *gru)
अणु
	पूर्णांक asid;

	gru->gs_asid += ASID_INC;
	asid = gru->gs_asid;
	अगर (asid >= gru->gs_asid_limit)
		asid = gru_reset_asid_limit(gru, asid);

	gru_dbg(grudev, "gid %d, asid 0x%x\n", gru->gs_gid, asid);
	वापस asid;
पूर्ण

/*
 * Clear n bits in a word. Return a word indicating the bits that were cleared.
 * Optionally, build an array of अक्षरs that contain the bit numbers allocated.
 */
अटल अचिन्हित दीर्घ reserve_resources(अचिन्हित दीर्घ *p, पूर्णांक n, पूर्णांक mmax,
				       अक्षर *idx)
अणु
	अचिन्हित दीर्घ bits = 0;
	पूर्णांक i;

	जबतक (n--) अणु
		i = find_first_bit(p, mmax);
		अगर (i == mmax)
			BUG();
		__clear_bit(i, p);
		__set_bit(i, &bits);
		अगर (idx)
			*idx++ = i;
	पूर्ण
	वापस bits;
पूर्ण

अचिन्हित दीर्घ gru_reserve_cb_resources(काष्ठा gru_state *gru, पूर्णांक cbr_au_count,
				       अक्षर *cbmap)
अणु
	वापस reserve_resources(&gru->gs_cbr_map, cbr_au_count, GRU_CBR_AU,
				 cbmap);
पूर्ण

अचिन्हित दीर्घ gru_reserve_ds_resources(काष्ठा gru_state *gru, पूर्णांक dsr_au_count,
				       अक्षर *dsmap)
अणु
	वापस reserve_resources(&gru->gs_dsr_map, dsr_au_count, GRU_DSR_AU,
				 dsmap);
पूर्ण

अटल व्योम reserve_gru_resources(काष्ठा gru_state *gru,
				  काष्ठा gru_thपढ़ो_state *gts)
अणु
	gru->gs_active_contexts++;
	gts->ts_cbr_map =
	    gru_reserve_cb_resources(gru, gts->ts_cbr_au_count,
				     gts->ts_cbr_idx);
	gts->ts_dsr_map =
	    gru_reserve_ds_resources(gru, gts->ts_dsr_au_count, शून्य);
पूर्ण

अटल व्योम मुक्त_gru_resources(काष्ठा gru_state *gru,
			       काष्ठा gru_thपढ़ो_state *gts)
अणु
	gru->gs_active_contexts--;
	gru->gs_cbr_map |= gts->ts_cbr_map;
	gru->gs_dsr_map |= gts->ts_dsr_map;
पूर्ण

/*
 * Check अगर a GRU has sufficient मुक्त resources to satisfy an allocation
 * request. Note: GRU locks may or may not be held when this is called. If
 * not held, recheck after acquiring the appropriate locks.
 *
 * Returns 1 अगर sufficient resources, 0 अगर not
 */
अटल पूर्णांक check_gru_resources(काष्ठा gru_state *gru, पूर्णांक cbr_au_count,
			       पूर्णांक dsr_au_count, पूर्णांक max_active_contexts)
अणु
	वापस hweight64(gru->gs_cbr_map) >= cbr_au_count
		&& hweight64(gru->gs_dsr_map) >= dsr_au_count
		&& gru->gs_active_contexts < max_active_contexts;
पूर्ण

/*
 * TLB manangment requires tracking all GRU chiplets that have loaded a GSEG
 * context.
 */
अटल पूर्णांक gru_load_mm_tracker(काष्ठा gru_state *gru,
					काष्ठा gru_thपढ़ो_state *gts)
अणु
	काष्ठा gru_mm_काष्ठा *gms = gts->ts_gms;
	काष्ठा gru_mm_tracker *asids = &gms->ms_asids[gru->gs_gid];
	अचिन्हित लघु ctxbiपंचांगap = (1 << gts->ts_ctxnum);
	पूर्णांक asid;

	spin_lock(&gms->ms_asid_lock);
	asid = asids->mt_asid;

	spin_lock(&gru->gs_asid_lock);
	अगर (asid == 0 || (asids->mt_ctxbiपंचांगap == 0 && asids->mt_asid_gen !=
			  gru->gs_asid_gen)) अणु
		asid = gru_assign_asid(gru);
		asids->mt_asid = asid;
		asids->mt_asid_gen = gru->gs_asid_gen;
		STAT(asid_new);
	पूर्ण अन्यथा अणु
		STAT(asid_reuse);
	पूर्ण
	spin_unlock(&gru->gs_asid_lock);

	BUG_ON(asids->mt_ctxbiपंचांगap & ctxbiपंचांगap);
	asids->mt_ctxbiपंचांगap |= ctxbiपंचांगap;
	अगर (!test_bit(gru->gs_gid, gms->ms_asidmap))
		__set_bit(gru->gs_gid, gms->ms_asidmap);
	spin_unlock(&gms->ms_asid_lock);

	gru_dbg(grudev,
		"gid %d, gts %p, gms %p, ctxnum %d, asid 0x%x, asidmap 0x%lx\n",
		gru->gs_gid, gts, gms, gts->ts_ctxnum, asid,
		gms->ms_asidmap[0]);
	वापस asid;
पूर्ण

अटल व्योम gru_unload_mm_tracker(काष्ठा gru_state *gru,
					काष्ठा gru_thपढ़ो_state *gts)
अणु
	काष्ठा gru_mm_काष्ठा *gms = gts->ts_gms;
	काष्ठा gru_mm_tracker *asids;
	अचिन्हित लघु ctxbiपंचांगap;

	asids = &gms->ms_asids[gru->gs_gid];
	ctxbiपंचांगap = (1 << gts->ts_ctxnum);
	spin_lock(&gms->ms_asid_lock);
	spin_lock(&gru->gs_asid_lock);
	BUG_ON((asids->mt_ctxbiपंचांगap & ctxbiपंचांगap) != ctxbiपंचांगap);
	asids->mt_ctxbiपंचांगap ^= ctxbiपंचांगap;
	gru_dbg(grudev, "gid %d, gts %p, gms %p, ctxnum %d, asidmap 0x%lx\n",
		gru->gs_gid, gts, gms, gts->ts_ctxnum, gms->ms_asidmap[0]);
	spin_unlock(&gru->gs_asid_lock);
	spin_unlock(&gms->ms_asid_lock);
पूर्ण

/*
 * Decrement the reference count on a GTS काष्ठाure. Free the काष्ठाure
 * अगर the reference count goes to zero.
 */
व्योम gts_drop(काष्ठा gru_thपढ़ो_state *gts)
अणु
	अगर (gts && atomic_dec_वापस(&gts->ts_refcnt) == 0) अणु
		अगर (gts->ts_gms)
			gru_drop_mmu_notअगरier(gts->ts_gms);
		kमुक्त(gts);
		STAT(gts_मुक्त);
	पूर्ण
पूर्ण

/*
 * Locate the GTS काष्ठाure क्रम the current thपढ़ो.
 */
अटल काष्ठा gru_thपढ़ो_state *gru_find_current_gts_nolock(काष्ठा gru_vma_data
			    *vdata, पूर्णांक tsid)
अणु
	काष्ठा gru_thपढ़ो_state *gts;

	list_क्रम_each_entry(gts, &vdata->vd_head, ts_next)
	    अगर (gts->ts_tsid == tsid)
		वापस gts;
	वापस शून्य;
पूर्ण

/*
 * Allocate a thपढ़ो state काष्ठाure.
 */
काष्ठा gru_thपढ़ो_state *gru_alloc_gts(काष्ठा vm_area_काष्ठा *vma,
		पूर्णांक cbr_au_count, पूर्णांक dsr_au_count,
		अचिन्हित अक्षर tlb_preload_count, पूर्णांक options, पूर्णांक tsid)
अणु
	काष्ठा gru_thपढ़ो_state *gts;
	काष्ठा gru_mm_काष्ठा *gms;
	पूर्णांक bytes;

	bytes = DSR_BYTES(dsr_au_count) + CBR_BYTES(cbr_au_count);
	bytes += माप(काष्ठा gru_thपढ़ो_state);
	gts = kदो_स्मृति(bytes, GFP_KERNEL);
	अगर (!gts)
		वापस ERR_PTR(-ENOMEM);

	STAT(gts_alloc);
	स_रखो(gts, 0, माप(काष्ठा gru_thपढ़ो_state)); /* zero out header */
	atomic_set(&gts->ts_refcnt, 1);
	mutex_init(&gts->ts_ctxlock);
	gts->ts_cbr_au_count = cbr_au_count;
	gts->ts_dsr_au_count = dsr_au_count;
	gts->ts_tlb_preload_count = tlb_preload_count;
	gts->ts_user_options = options;
	gts->ts_user_blade_id = -1;
	gts->ts_user_chiplet_id = -1;
	gts->ts_tsid = tsid;
	gts->ts_ctxnum = शून्यCTX;
	gts->ts_tlb_पूर्णांक_select = -1;
	gts->ts_cch_req_slice = -1;
	gts->ts_sizeavail = GRU_SIZEAVAIL(PAGE_SHIFT);
	अगर (vma) अणु
		gts->ts_mm = current->mm;
		gts->ts_vma = vma;
		gms = gru_रेजिस्टर_mmu_notअगरier();
		अगर (IS_ERR(gms))
			जाओ err;
		gts->ts_gms = gms;
	पूर्ण

	gru_dbg(grudev, "alloc gts %p\n", gts);
	वापस gts;

err:
	gts_drop(gts);
	वापस ERR_CAST(gms);
पूर्ण

/*
 * Allocate a vma निजी data काष्ठाure.
 */
काष्ठा gru_vma_data *gru_alloc_vma_data(काष्ठा vm_area_काष्ठा *vma, पूर्णांक tsid)
अणु
	काष्ठा gru_vma_data *vdata = शून्य;

	vdata = kदो_स्मृति(माप(*vdata), GFP_KERNEL);
	अगर (!vdata)
		वापस शून्य;

	STAT(vdata_alloc);
	INIT_LIST_HEAD(&vdata->vd_head);
	spin_lock_init(&vdata->vd_lock);
	gru_dbg(grudev, "alloc vdata %p\n", vdata);
	वापस vdata;
पूर्ण

/*
 * Find the thपढ़ो state काष्ठाure क्रम the current thपढ़ो.
 */
काष्ठा gru_thपढ़ो_state *gru_find_thपढ़ो_state(काष्ठा vm_area_काष्ठा *vma,
					पूर्णांक tsid)
अणु
	काष्ठा gru_vma_data *vdata = vma->vm_निजी_data;
	काष्ठा gru_thपढ़ो_state *gts;

	spin_lock(&vdata->vd_lock);
	gts = gru_find_current_gts_nolock(vdata, tsid);
	spin_unlock(&vdata->vd_lock);
	gru_dbg(grudev, "vma %p, gts %p\n", vma, gts);
	वापस gts;
पूर्ण

/*
 * Allocate a new thपढ़ो state क्रम a GSEG. Note that races may allow
 * another thपढ़ो to race to create a gts.
 */
काष्ठा gru_thपढ़ो_state *gru_alloc_thपढ़ो_state(काष्ठा vm_area_काष्ठा *vma,
					पूर्णांक tsid)
अणु
	काष्ठा gru_vma_data *vdata = vma->vm_निजी_data;
	काष्ठा gru_thपढ़ो_state *gts, *ngts;

	gts = gru_alloc_gts(vma, vdata->vd_cbr_au_count,
			    vdata->vd_dsr_au_count,
			    vdata->vd_tlb_preload_count,
			    vdata->vd_user_options, tsid);
	अगर (IS_ERR(gts))
		वापस gts;

	spin_lock(&vdata->vd_lock);
	ngts = gru_find_current_gts_nolock(vdata, tsid);
	अगर (ngts) अणु
		gts_drop(gts);
		gts = ngts;
		STAT(gts_द्विगुन_allocate);
	पूर्ण अन्यथा अणु
		list_add(&gts->ts_next, &vdata->vd_head);
	पूर्ण
	spin_unlock(&vdata->vd_lock);
	gru_dbg(grudev, "vma %p, gts %p\n", vma, gts);
	वापस gts;
पूर्ण

/*
 * Free the GRU context asचिन्हित to the thपढ़ो state.
 */
अटल व्योम gru_मुक्त_gru_context(काष्ठा gru_thपढ़ो_state *gts)
अणु
	काष्ठा gru_state *gru;

	gru = gts->ts_gru;
	gru_dbg(grudev, "gts %p, gid %d\n", gts, gru->gs_gid);

	spin_lock(&gru->gs_lock);
	gru->gs_gts[gts->ts_ctxnum] = शून्य;
	मुक्त_gru_resources(gru, gts);
	BUG_ON(test_bit(gts->ts_ctxnum, &gru->gs_context_map) == 0);
	__clear_bit(gts->ts_ctxnum, &gru->gs_context_map);
	gts->ts_ctxnum = शून्यCTX;
	gts->ts_gru = शून्य;
	gts->ts_blade = -1;
	spin_unlock(&gru->gs_lock);

	gts_drop(gts);
	STAT(मुक्त_context);
पूर्ण

/*
 * Prefetching cachelines help hardware perक्रमmance.
 * (Strictly a perक्रमmance enhancement. Not functionally required).
 */
अटल व्योम prefetch_data(व्योम *p, पूर्णांक num, पूर्णांक stride)
अणु
	जबतक (num-- > 0) अणु
		prefetchw(p);
		p += stride;
	पूर्ण
पूर्ण

अटल अंतरभूत दीर्घ gru_copy_handle(व्योम *d, व्योम *s)
अणु
	स_नकल(d, s, GRU_HANDLE_BYTES);
	वापस GRU_HANDLE_BYTES;
पूर्ण

अटल व्योम gru_prefetch_context(व्योम *gseg, व्योम *cb, व्योम *cbe,
				अचिन्हित दीर्घ cbrmap, अचिन्हित दीर्घ length)
अणु
	पूर्णांक i, scr;

	prefetch_data(gseg + GRU_DS_BASE, length / GRU_CACHE_LINE_BYTES,
		      GRU_CACHE_LINE_BYTES);

	क्रम_each_cbr_in_allocation_map(i, &cbrmap, scr) अणु
		prefetch_data(cb, 1, GRU_CACHE_LINE_BYTES);
		prefetch_data(cbe + i * GRU_HANDLE_STRIDE, 1,
			      GRU_CACHE_LINE_BYTES);
		cb += GRU_HANDLE_STRIDE;
	पूर्ण
पूर्ण

अटल व्योम gru_load_context_data(व्योम *save, व्योम *grubase, पूर्णांक ctxnum,
				  अचिन्हित दीर्घ cbrmap, अचिन्हित दीर्घ dsrmap,
				  पूर्णांक data_valid)
अणु
	व्योम *gseg, *cb, *cbe;
	अचिन्हित दीर्घ length;
	पूर्णांक i, scr;

	gseg = grubase + ctxnum * GRU_GSEG_STRIDE;
	cb = gseg + GRU_CB_BASE;
	cbe = grubase + GRU_CBE_BASE;
	length = hweight64(dsrmap) * GRU_DSR_AU_BYTES;
	gru_prefetch_context(gseg, cb, cbe, cbrmap, length);

	क्रम_each_cbr_in_allocation_map(i, &cbrmap, scr) अणु
		अगर (data_valid) अणु
			save += gru_copy_handle(cb, save);
			save += gru_copy_handle(cbe + i * GRU_HANDLE_STRIDE,
						save);
		पूर्ण अन्यथा अणु
			स_रखो(cb, 0, GRU_CACHE_LINE_BYTES);
			स_रखो(cbe + i * GRU_HANDLE_STRIDE, 0,
						GRU_CACHE_LINE_BYTES);
		पूर्ण
		/* Flush CBE to hide race in context restart */
		mb();
		gru_flush_cache(cbe + i * GRU_HANDLE_STRIDE);
		cb += GRU_HANDLE_STRIDE;
	पूर्ण

	अगर (data_valid)
		स_नकल(gseg + GRU_DS_BASE, save, length);
	अन्यथा
		स_रखो(gseg + GRU_DS_BASE, 0, length);
पूर्ण

अटल व्योम gru_unload_context_data(व्योम *save, व्योम *grubase, पूर्णांक ctxnum,
				    अचिन्हित दीर्घ cbrmap, अचिन्हित दीर्घ dsrmap)
अणु
	व्योम *gseg, *cb, *cbe;
	अचिन्हित दीर्घ length;
	पूर्णांक i, scr;

	gseg = grubase + ctxnum * GRU_GSEG_STRIDE;
	cb = gseg + GRU_CB_BASE;
	cbe = grubase + GRU_CBE_BASE;
	length = hweight64(dsrmap) * GRU_DSR_AU_BYTES;

	/* CBEs may not be coherent. Flush them from cache */
	क्रम_each_cbr_in_allocation_map(i, &cbrmap, scr)
		gru_flush_cache(cbe + i * GRU_HANDLE_STRIDE);
	mb();		/* Let the CL flush complete */

	gru_prefetch_context(gseg, cb, cbe, cbrmap, length);

	क्रम_each_cbr_in_allocation_map(i, &cbrmap, scr) अणु
		save += gru_copy_handle(save, cb);
		save += gru_copy_handle(save, cbe + i * GRU_HANDLE_STRIDE);
		cb += GRU_HANDLE_STRIDE;
	पूर्ण
	स_नकल(save, gseg + GRU_DS_BASE, length);
पूर्ण

व्योम gru_unload_context(काष्ठा gru_thपढ़ो_state *gts, पूर्णांक savestate)
अणु
	काष्ठा gru_state *gru = gts->ts_gru;
	काष्ठा gru_context_configuration_handle *cch;
	पूर्णांक ctxnum = gts->ts_ctxnum;

	अगर (!is_kernel_context(gts))
		zap_vma_ptes(gts->ts_vma, UGRUADDR(gts), GRU_GSEG_PAGESIZE);
	cch = get_cch(gru->gs_gru_base_vaddr, ctxnum);

	gru_dbg(grudev, "gts %p, cbrmap 0x%lx, dsrmap 0x%lx\n",
		gts, gts->ts_cbr_map, gts->ts_dsr_map);
	lock_cch_handle(cch);
	अगर (cch_पूर्णांकerrupt_sync(cch))
		BUG();

	अगर (!is_kernel_context(gts))
		gru_unload_mm_tracker(gru, gts);
	अगर (savestate) अणु
		gru_unload_context_data(gts->ts_gdata, gru->gs_gru_base_vaddr,
					ctxnum, gts->ts_cbr_map,
					gts->ts_dsr_map);
		gts->ts_data_valid = 1;
	पूर्ण

	अगर (cch_deallocate(cch))
		BUG();
	unlock_cch_handle(cch);

	gru_मुक्त_gru_context(gts);
पूर्ण

/*
 * Load a GRU context by copying it from the thपढ़ो data काष्ठाure in memory
 * to the GRU.
 */
व्योम gru_load_context(काष्ठा gru_thपढ़ो_state *gts)
अणु
	काष्ठा gru_state *gru = gts->ts_gru;
	काष्ठा gru_context_configuration_handle *cch;
	पूर्णांक i, err, asid, ctxnum = gts->ts_ctxnum;

	cch = get_cch(gru->gs_gru_base_vaddr, ctxnum);
	lock_cch_handle(cch);
	cch->tfm_fault_bit_enable =
	    (gts->ts_user_options == GRU_OPT_MISS_FMM_POLL
	     || gts->ts_user_options == GRU_OPT_MISS_FMM_INTR);
	cch->tlb_पूर्णांक_enable = (gts->ts_user_options == GRU_OPT_MISS_FMM_INTR);
	अगर (cch->tlb_पूर्णांक_enable) अणु
		gts->ts_tlb_पूर्णांक_select = gru_cpu_fault_map_id();
		cch->tlb_पूर्णांक_select = gts->ts_tlb_पूर्णांक_select;
	पूर्ण
	अगर (gts->ts_cch_req_slice >= 0) अणु
		cch->req_slice_set_enable = 1;
		cch->req_slice = gts->ts_cch_req_slice;
	पूर्ण अन्यथा अणु
		cch->req_slice_set_enable =0;
	पूर्ण
	cch->tfm_करोne_bit_enable = 0;
	cch->dsr_allocation_map = gts->ts_dsr_map;
	cch->cbr_allocation_map = gts->ts_cbr_map;

	अगर (is_kernel_context(gts)) अणु
		cch->unmap_enable = 1;
		cch->tfm_करोne_bit_enable = 1;
		cch->cb_पूर्णांक_enable = 1;
		cch->tlb_पूर्णांक_select = 0;	/* For now, पूर्णांकs go to cpu 0 */
	पूर्ण अन्यथा अणु
		cch->unmap_enable = 0;
		cch->tfm_करोne_bit_enable = 0;
		cch->cb_पूर्णांक_enable = 0;
		asid = gru_load_mm_tracker(gru, gts);
		क्रम (i = 0; i < 8; i++) अणु
			cch->asid[i] = asid + i;
			cch->sizeavail[i] = gts->ts_sizeavail;
		पूर्ण
	पूर्ण

	err = cch_allocate(cch);
	अगर (err) अणु
		gru_dbg(grudev,
			"err %d: cch %p, gts %p, cbr 0x%lx, dsr 0x%lx\n",
			err, cch, gts, gts->ts_cbr_map, gts->ts_dsr_map);
		BUG();
	पूर्ण

	gru_load_context_data(gts->ts_gdata, gru->gs_gru_base_vaddr, ctxnum,
			gts->ts_cbr_map, gts->ts_dsr_map, gts->ts_data_valid);

	अगर (cch_start(cch))
		BUG();
	unlock_cch_handle(cch);

	gru_dbg(grudev, "gid %d, gts %p, cbrmap 0x%lx, dsrmap 0x%lx, tie %d, tis %d\n",
		gts->ts_gru->gs_gid, gts, gts->ts_cbr_map, gts->ts_dsr_map,
		(gts->ts_user_options == GRU_OPT_MISS_FMM_INTR), gts->ts_tlb_पूर्णांक_select);
पूर्ण

/*
 * Update fields in an active CCH:
 * 	- retarget पूर्णांकerrupts on local blade
 * 	- update sizeavail mask
 */
पूर्णांक gru_update_cch(काष्ठा gru_thपढ़ो_state *gts)
अणु
	काष्ठा gru_context_configuration_handle *cch;
	काष्ठा gru_state *gru = gts->ts_gru;
	पूर्णांक i, ctxnum = gts->ts_ctxnum, ret = 0;

	cch = get_cch(gru->gs_gru_base_vaddr, ctxnum);

	lock_cch_handle(cch);
	अगर (cch->state == CCHSTATE_ACTIVE) अणु
		अगर (gru->gs_gts[gts->ts_ctxnum] != gts)
			जाओ निकास;
		अगर (cch_पूर्णांकerrupt(cch))
			BUG();
		क्रम (i = 0; i < 8; i++)
			cch->sizeavail[i] = gts->ts_sizeavail;
		gts->ts_tlb_पूर्णांक_select = gru_cpu_fault_map_id();
		cch->tlb_पूर्णांक_select = gru_cpu_fault_map_id();
		cch->tfm_fault_bit_enable =
		  (gts->ts_user_options == GRU_OPT_MISS_FMM_POLL
		    || gts->ts_user_options == GRU_OPT_MISS_FMM_INTR);
		अगर (cch_start(cch))
			BUG();
		ret = 1;
	पूर्ण
निकास:
	unlock_cch_handle(cch);
	वापस ret;
पूर्ण

/*
 * Update CCH tlb पूर्णांकerrupt select. Required when all the following is true:
 * 	- task's GRU context is loaded पूर्णांकo a GRU
 * 	- task is using पूर्णांकerrupt notअगरication क्रम TLB faults
 * 	- task has migrated to a dअगरferent cpu on the same blade where
 * 	  it was previously running.
 */
अटल पूर्णांक gru_retarget_पूर्णांकr(काष्ठा gru_thपढ़ो_state *gts)
अणु
	अगर (gts->ts_tlb_पूर्णांक_select < 0
	    || gts->ts_tlb_पूर्णांक_select == gru_cpu_fault_map_id())
		वापस 0;

	gru_dbg(grudev, "retarget from %d to %d\n", gts->ts_tlb_पूर्णांक_select,
		gru_cpu_fault_map_id());
	वापस gru_update_cch(gts);
पूर्ण

/*
 * Check अगर a GRU context is allowed to use a specअगरic chiplet. By शेष
 * a context is asचिन्हित to any blade-local chiplet. However, users can
 * override this.
 * 	Returns 1 अगर assignment allowed, 0 otherwise
 */
अटल पूर्णांक gru_check_chiplet_assignment(काष्ठा gru_state *gru,
					काष्ठा gru_thपढ़ो_state *gts)
अणु
	पूर्णांक blade_id;
	पूर्णांक chiplet_id;

	blade_id = gts->ts_user_blade_id;
	अगर (blade_id < 0)
		blade_id = uv_numa_blade_id();

	chiplet_id = gts->ts_user_chiplet_id;
	वापस gru->gs_blade_id == blade_id &&
		(chiplet_id < 0 || chiplet_id == gru->gs_chiplet_id);
पूर्ण

/*
 * Unload the gru context अगर it is not asचिन्हित to the correct blade or
 * chiplet. Misassignment can occur अगर the process migrates to a dअगरferent
 * blade or अगर the user changes the selected blade/chiplet.
 */
व्योम gru_check_context_placement(काष्ठा gru_thपढ़ो_state *gts)
अणु
	काष्ठा gru_state *gru;

	/*
	 * If the current task is the context owner, verअगरy that the
	 * context is correctly placed. This test is skipped क्रम non-owner
	 * references. Pthपढ़ो apps use non-owner references to the CBRs.
	 */
	gru = gts->ts_gru;
	अगर (!gru || gts->ts_tgid_owner != current->tgid)
		वापस;

	अगर (!gru_check_chiplet_assignment(gru, gts)) अणु
		STAT(check_context_unload);
		gru_unload_context(gts, 1);
	पूर्ण अन्यथा अगर (gru_retarget_पूर्णांकr(gts)) अणु
		STAT(check_context_retarget_पूर्णांकr);
	पूर्ण
पूर्ण


/*
 * Insufficient GRU resources available on the local blade. Steal a context from
 * a process. This is a hack until a _real_ resource scheduler is written....
 */
#घोषणा next_ctxnum(n)	((n) <  GRU_NUM_CCH - 2 ? (n) + 1 : 0)
#घोषणा next_gru(b, g)	(((g) < &(b)->bs_grus[GRU_CHIPLETS_PER_BLADE - 1]) ?  \
				 ((g)+1) : &(b)->bs_grus[0])

अटल पूर्णांक is_gts_stealable(काष्ठा gru_thपढ़ो_state *gts,
		काष्ठा gru_blade_state *bs)
अणु
	अगर (is_kernel_context(gts))
		वापस करोwn_ग_लिखो_trylock(&bs->bs_kgts_sema);
	अन्यथा
		वापस mutex_trylock(&gts->ts_ctxlock);
पूर्ण

अटल व्योम gts_stolen(काष्ठा gru_thपढ़ो_state *gts,
		काष्ठा gru_blade_state *bs)
अणु
	अगर (is_kernel_context(gts)) अणु
		up_ग_लिखो(&bs->bs_kgts_sema);
		STAT(steal_kernel_context);
	पूर्ण अन्यथा अणु
		mutex_unlock(&gts->ts_ctxlock);
		STAT(steal_user_context);
	पूर्ण
पूर्ण

व्योम gru_steal_context(काष्ठा gru_thपढ़ो_state *gts)
अणु
	काष्ठा gru_blade_state *blade;
	काष्ठा gru_state *gru, *gru0;
	काष्ठा gru_thपढ़ो_state *ngts = शून्य;
	पूर्णांक ctxnum, ctxnum0, flag = 0, cbr, dsr;
	पूर्णांक blade_id;

	blade_id = gts->ts_user_blade_id;
	अगर (blade_id < 0)
		blade_id = uv_numa_blade_id();
	cbr = gts->ts_cbr_au_count;
	dsr = gts->ts_dsr_au_count;

	blade = gru_base[blade_id];
	spin_lock(&blade->bs_lock);

	ctxnum = next_ctxnum(blade->bs_lru_ctxnum);
	gru = blade->bs_lru_gru;
	अगर (ctxnum == 0)
		gru = next_gru(blade, gru);
	blade->bs_lru_gru = gru;
	blade->bs_lru_ctxnum = ctxnum;
	ctxnum0 = ctxnum;
	gru0 = gru;
	जबतक (1) अणु
		अगर (gru_check_chiplet_assignment(gru, gts)) अणु
			अगर (check_gru_resources(gru, cbr, dsr, GRU_NUM_CCH))
				अवरोध;
			spin_lock(&gru->gs_lock);
			क्रम (; ctxnum < GRU_NUM_CCH; ctxnum++) अणु
				अगर (flag && gru == gru0 && ctxnum == ctxnum0)
					अवरोध;
				ngts = gru->gs_gts[ctxnum];
				/*
			 	* We are grabbing locks out of order, so trylock is
			 	* needed. GTSs are usually not locked, so the odds of
			 	* success are high. If trylock fails, try to steal a
			 	* dअगरferent GSEG.
			 	*/
				अगर (ngts && is_gts_stealable(ngts, blade))
					अवरोध;
				ngts = शून्य;
			पूर्ण
			spin_unlock(&gru->gs_lock);
			अगर (ngts || (flag && gru == gru0 && ctxnum == ctxnum0))
				अवरोध;
		पूर्ण
		अगर (flag && gru == gru0)
			अवरोध;
		flag = 1;
		ctxnum = 0;
		gru = next_gru(blade, gru);
	पूर्ण
	spin_unlock(&blade->bs_lock);

	अगर (ngts) अणु
		gts->ustats.context_stolen++;
		ngts->ts_steal_jअगरfies = jअगरfies;
		gru_unload_context(ngts, is_kernel_context(ngts) ? 0 : 1);
		gts_stolen(ngts, blade);
	पूर्ण अन्यथा अणु
		STAT(steal_context_failed);
	पूर्ण
	gru_dbg(grudev,
		"stole gid %d, ctxnum %d from gts %p. Need cb %d, ds %d;"
		" avail cb %ld, ds %ld\n",
		gru->gs_gid, ctxnum, ngts, cbr, dsr, hweight64(gru->gs_cbr_map),
		hweight64(gru->gs_dsr_map));
पूर्ण

/*
 * Assign a gru context.
 */
अटल पूर्णांक gru_assign_context_number(काष्ठा gru_state *gru)
अणु
	पूर्णांक ctxnum;

	ctxnum = find_first_zero_bit(&gru->gs_context_map, GRU_NUM_CCH);
	__set_bit(ctxnum, &gru->gs_context_map);
	वापस ctxnum;
पूर्ण

/*
 * Scan the GRUs on the local blade & assign a GRU context.
 */
काष्ठा gru_state *gru_assign_gru_context(काष्ठा gru_thपढ़ो_state *gts)
अणु
	काष्ठा gru_state *gru, *grux;
	पूर्णांक i, max_active_contexts;
	पूर्णांक blade_id = gts->ts_user_blade_id;

	अगर (blade_id < 0)
		blade_id = uv_numa_blade_id();
again:
	gru = शून्य;
	max_active_contexts = GRU_NUM_CCH;
	क्रम_each_gru_on_blade(grux, blade_id, i) अणु
		अगर (!gru_check_chiplet_assignment(grux, gts))
			जारी;
		अगर (check_gru_resources(grux, gts->ts_cbr_au_count,
					gts->ts_dsr_au_count,
					max_active_contexts)) अणु
			gru = grux;
			max_active_contexts = grux->gs_active_contexts;
			अगर (max_active_contexts == 0)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (gru) अणु
		spin_lock(&gru->gs_lock);
		अगर (!check_gru_resources(gru, gts->ts_cbr_au_count,
					 gts->ts_dsr_au_count, GRU_NUM_CCH)) अणु
			spin_unlock(&gru->gs_lock);
			जाओ again;
		पूर्ण
		reserve_gru_resources(gru, gts);
		gts->ts_gru = gru;
		gts->ts_blade = gru->gs_blade_id;
		gts->ts_ctxnum = gru_assign_context_number(gru);
		atomic_inc(&gts->ts_refcnt);
		gru->gs_gts[gts->ts_ctxnum] = gts;
		spin_unlock(&gru->gs_lock);

		STAT(assign_context);
		gru_dbg(grudev,
			"gseg %p, gts %p, gid %d, ctx %d, cbr %d, dsr %d\n",
			gseg_भव_address(gts->ts_gru, gts->ts_ctxnum), gts,
			gts->ts_gru->gs_gid, gts->ts_ctxnum,
			gts->ts_cbr_au_count, gts->ts_dsr_au_count);
	पूर्ण अन्यथा अणु
		gru_dbg(grudev, "failed to allocate a GTS %s\n", "");
		STAT(assign_context_failed);
	पूर्ण

	वापस gru;
पूर्ण

/*
 * gru_nopage
 *
 * Map the user's GRU segment
 *
 * 	Note: gru segments alway mmaped on GRU_GSEG_PAGESIZE boundaries.
 */
vm_fault_t gru_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा gru_thपढ़ो_state *gts;
	अचिन्हित दीर्घ paddr, vaddr;
	अचिन्हित दीर्घ expires;

	vaddr = vmf->address;
	gru_dbg(grudev, "vma %p, vaddr 0x%lx (0x%lx)\n",
		vma, vaddr, GSEG_BASE(vaddr));
	STAT(nopfn);

	/* The following check ensures vaddr is a valid address in the VMA */
	gts = gru_find_thपढ़ो_state(vma, TSID(vaddr, vma));
	अगर (!gts)
		वापस VM_FAULT_SIGBUS;

again:
	mutex_lock(&gts->ts_ctxlock);
	preempt_disable();

	gru_check_context_placement(gts);

	अगर (!gts->ts_gru) अणु
		STAT(load_user_context);
		अगर (!gru_assign_gru_context(gts)) अणु
			preempt_enable();
			mutex_unlock(&gts->ts_ctxlock);
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_समयout(GRU_ASSIGN_DELAY);  /* true hack ZZZ */
			expires = gts->ts_steal_jअगरfies + GRU_STEAL_DELAY;
			अगर (समय_beक्रमe(expires, jअगरfies))
				gru_steal_context(gts);
			जाओ again;
		पूर्ण
		gru_load_context(gts);
		paddr = gseg_physical_address(gts->ts_gru, gts->ts_ctxnum);
		remap_pfn_range(vma, vaddr & ~(GRU_GSEG_PAGESIZE - 1),
				paddr >> PAGE_SHIFT, GRU_GSEG_PAGESIZE,
				vma->vm_page_prot);
	पूर्ण

	preempt_enable();
	mutex_unlock(&gts->ts_ctxlock);

	वापस VM_FAULT_NOPAGE;
पूर्ण

