<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SN Platक्रमm GRU Driver
 *
 * 		MMUOPS callbacks  + TLB flushing
 *
 * This file handles emu notअगरier callbacks from the core kernel. The callbacks
 * are used to update the TLB in the GRU as a result of changes in the
 * state of a process address space. This file also handles TLB invalidates
 * from the GRU driver.
 *
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयx.h>
#समावेश <linux/srcu.h>
#समावेश <यंत्र/processor.h>
#समावेश "gru.h"
#समावेश "grutables.h"
#समावेश <यंत्र/uv/uv_hub.h>

#घोषणा gru_अक्रमom()	get_cycles()

/* ---------------------------------- TLB Invalidation functions --------
 * get_tgh_handle
 *
 * Find a TGH to use क्रम issuing a TLB invalidate. For GRUs that are on the
 * local blade, use a fixed TGH that is a function of the blade-local cpu
 * number. Normally, this TGH is निजी to the cpu & no contention occurs क्रम
 * the TGH. For offblade GRUs, select a अक्रमom TGH in the range above the
 * निजी TGHs. A spinlock is required to access this TGH & the lock must be
 * released when the invalidate is completes. This sucks, but it is the best we
 * can करो.
 *
 * Note that the spinlock is IN the TGH handle so locking करोes not involve
 * additional cache lines.
 *
 */
अटल अंतरभूत पूर्णांक get_off_blade_tgh(काष्ठा gru_state *gru)
अणु
	पूर्णांक n;

	n = GRU_NUM_TGH - gru->gs_tgh_first_remote;
	n = gru_अक्रमom() % n;
	n += gru->gs_tgh_first_remote;
	वापस n;
पूर्ण

अटल अंतरभूत पूर्णांक get_on_blade_tgh(काष्ठा gru_state *gru)
अणु
	वापस uv_blade_processor_id() >> gru->gs_tgh_local_shअगरt;
पूर्ण

अटल काष्ठा gru_tlb_global_handle *get_lock_tgh_handle(काष्ठा gru_state
							 *gru)
अणु
	काष्ठा gru_tlb_global_handle *tgh;
	पूर्णांक n;

	preempt_disable();
	अगर (uv_numa_blade_id() == gru->gs_blade_id)
		n = get_on_blade_tgh(gru);
	अन्यथा
		n = get_off_blade_tgh(gru);
	tgh = get_tgh_by_index(gru, n);
	lock_tgh_handle(tgh);

	वापस tgh;
पूर्ण

अटल व्योम get_unlock_tgh_handle(काष्ठा gru_tlb_global_handle *tgh)
अणु
	unlock_tgh_handle(tgh);
	preempt_enable();
पूर्ण

/*
 * gru_flush_tlb_range
 *
 * General purpose TLB invalidation function. This function scans every GRU in
 * the ENTIRE प्रणाली (partition) looking क्रम GRUs where the specअगरied MM has
 * been accessed by the GRU. For each GRU found, the TLB must be invalidated OR
 * the ASID invalidated. Invalidating an ASID causes a new ASID to be asचिन्हित
 * on the next fault. This effectively flushes the ENTIRE TLB क्रम the MM at the
 * cost of (possibly) a large number of future TLBmisses.
 *
 * The current algorithm is optimized based on the following (somewhat true)
 * assumptions:
 * 	- GRU contexts are not loaded पूर्णांकo a GRU unless a reference is made to
 * 	  the data segment or control block (this is true, not an assumption).
 * 	  If a DS/CB is referenced, the user will also issue inकाष्ठाions that
 * 	  cause TLBmisses. It is not necessary to optimize क्रम the हाल where
 * 	  contexts are loaded but no inकाष्ठाions cause TLB misses. (I know
 * 	  this will happen but I'm not optimizing क्रम it).
 * 	- GRU inकाष्ठाions to invalidate TLB entries are SLOOOOWWW - normally
 * 	  a few usec but in unusual हालs, it could be दीर्घer. Aव्योम अगर
 * 	  possible.
 * 	- पूर्णांकrablade process migration between cpus is not frequent but is
 * 	  common.
 * 	- a GRU context is not typically migrated to a dअगरferent GRU on the
 * 	  blade because of पूर्णांकrablade migration
 *	- पूर्णांकerblade migration is rare. Processes migrate their GRU context to
 *	  the new blade.
 *	- अगर पूर्णांकerblade migration occurs, migration back to the original blade
 *	  is very very rare (ie., no optimization क्रम this हाल)
 *	- most GRU inकाष्ठाion operate on a subset of the user REGIONS. Code
 *	  & shared library regions are not likely tarमाला_लो of GRU inकाष्ठाions.
 *
 * To help improve the efficiency of TLB invalidation, the GMS data
 * काष्ठाure is मुख्यtained क्रम EACH address space (MM काष्ठा). The GMS is
 * also the काष्ठाure that contains the poपूर्णांकer to the mmu callout
 * functions. This काष्ठाure is linked to the mm_काष्ठा क्रम the address space
 * using the mmu "register" function. The mmu पूर्णांकerfaces are used to
 * provide the callbacks क्रम TLB invalidation. The GMS contains:
 *
 * 	- asid[maxgrus] array. ASIDs are asचिन्हित to a GRU when a context is
 * 	  loaded पूर्णांकo the GRU.
 * 	- asidmap[maxgrus]. biपंचांगap to make it easier to find non-zero asids in
 * 	  the above array
 *	- ctxbiपंचांगap[maxgrus]. Indicates the contexts that are currently active
 *	  in the GRU क्रम the address space. This biपंचांगap must be passed to the
 *	  GRU to करो an invalidate.
 *
 * The current algorithm क्रम invalidating TLBs is:
 * 	- scan the asidmap क्रम GRUs where the context has been loaded, ie,
 * 	  asid is non-zero.
 * 	- क्रम each gru found:
 * 		- अगर the ctxपंचांगap is non-zero, there are active contexts in the
 * 		  GRU. TLB invalidate inकाष्ठाions must be issued to the GRU.
 *		- अगर the ctxपंचांगap is zero, no context is active. Set the ASID to
 *		  zero to क्रमce a full TLB invalidation. This is fast but will
 *		  cause a lot of TLB misses अगर the context is reloaded onto the
 *		  GRU
 *
 */

व्योम gru_flush_tlb_range(काष्ठा gru_mm_काष्ठा *gms, अचिन्हित दीर्घ start,
			 अचिन्हित दीर्घ len)
अणु
	काष्ठा gru_state *gru;
	काष्ठा gru_mm_tracker *asids;
	काष्ठा gru_tlb_global_handle *tgh;
	अचिन्हित दीर्घ num;
	पूर्णांक grupagesize, pagesize, pageshअगरt, gid, asid;

	/* ZZZ TODO - handle huge pages */
	pageshअगरt = PAGE_SHIFT;
	pagesize = (1UL << pageshअगरt);
	grupagesize = GRU_PAGESIZE(pageshअगरt);
	num = min(((len + pagesize - 1) >> pageshअगरt), GRUMAXINVAL);

	STAT(flush_tlb);
	gru_dbg(grudev, "gms %p, start 0x%lx, len 0x%lx, asidmap 0x%lx\n", gms,
		start, len, gms->ms_asidmap[0]);

	spin_lock(&gms->ms_asid_lock);
	क्रम_each_gru_in_biपंचांगap(gid, gms->ms_asidmap) अणु
		STAT(flush_tlb_gru);
		gru = GID_TO_GRU(gid);
		asids = gms->ms_asids + gid;
		asid = asids->mt_asid;
		अगर (asids->mt_ctxbiपंचांगap && asid) अणु
			STAT(flush_tlb_gru_tgh);
			asid = GRUASID(asid, start);
			gru_dbg(grudev,
	"  FLUSH gruid %d, asid 0x%x, vaddr 0x%lx, vamask 0x%x, num %ld, cbmap 0x%x\n",
			      gid, asid, start, grupagesize, num, asids->mt_ctxbiपंचांगap);
			tgh = get_lock_tgh_handle(gru);
			tgh_invalidate(tgh, start, ~0, asid, grupagesize, 0,
				       num - 1, asids->mt_ctxbiपंचांगap);
			get_unlock_tgh_handle(tgh);
		पूर्ण अन्यथा अणु
			STAT(flush_tlb_gru_zero_asid);
			asids->mt_asid = 0;
			__clear_bit(gru->gs_gid, gms->ms_asidmap);
			gru_dbg(grudev,
	"  CLEARASID gruid %d, asid 0x%x, cbtmap 0x%x, asidmap 0x%lx\n",
				gid, asid, asids->mt_ctxbiपंचांगap,
				gms->ms_asidmap[0]);
		पूर्ण
	पूर्ण
	spin_unlock(&gms->ms_asid_lock);
पूर्ण

/*
 * Flush the entire TLB on a chiplet.
 */
व्योम gru_flush_all_tlb(काष्ठा gru_state *gru)
अणु
	काष्ठा gru_tlb_global_handle *tgh;

	gru_dbg(grudev, "gid %d\n", gru->gs_gid);
	tgh = get_lock_tgh_handle(gru);
	tgh_invalidate(tgh, 0, ~0, 0, 1, 1, GRUMAXINVAL - 1, 0xffff);
	get_unlock_tgh_handle(tgh);
पूर्ण

/*
 * MMUOPS notअगरier callout functions
 */
अटल पूर्णांक gru_invalidate_range_start(काष्ठा mmu_notअगरier *mn,
			स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	काष्ठा gru_mm_काष्ठा *gms = container_of(mn, काष्ठा gru_mm_काष्ठा,
						 ms_notअगरier);

	STAT(mmu_invalidate_range);
	atomic_inc(&gms->ms_range_active);
	gru_dbg(grudev, "gms %p, start 0x%lx, end 0x%lx, act %d\n", gms,
		range->start, range->end, atomic_पढ़ो(&gms->ms_range_active));
	gru_flush_tlb_range(gms, range->start, range->end - range->start);

	वापस 0;
पूर्ण

अटल व्योम gru_invalidate_range_end(काष्ठा mmu_notअगरier *mn,
			स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	काष्ठा gru_mm_काष्ठा *gms = container_of(mn, काष्ठा gru_mm_काष्ठा,
						 ms_notअगरier);

	/* ..._and_test() provides needed barrier */
	(व्योम)atomic_dec_and_test(&gms->ms_range_active);

	wake_up_all(&gms->ms_रुको_queue);
	gru_dbg(grudev, "gms %p, start 0x%lx, end 0x%lx\n",
		gms, range->start, range->end);
पूर्ण

अटल काष्ठा mmu_notअगरier *gru_alloc_notअगरier(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा gru_mm_काष्ठा *gms;

	gms = kzalloc(माप(*gms), GFP_KERNEL);
	अगर (!gms)
		वापस ERR_PTR(-ENOMEM);
	STAT(gms_alloc);
	spin_lock_init(&gms->ms_asid_lock);
	init_रुकोqueue_head(&gms->ms_रुको_queue);

	वापस &gms->ms_notअगरier;
पूर्ण

अटल व्योम gru_मुक्त_notअगरier(काष्ठा mmu_notअगरier *mn)
अणु
	kमुक्त(container_of(mn, काष्ठा gru_mm_काष्ठा, ms_notअगरier));
	STAT(gms_मुक्त);
पूर्ण

अटल स्थिर काष्ठा mmu_notअगरier_ops gru_mmuops = अणु
	.invalidate_range_start	= gru_invalidate_range_start,
	.invalidate_range_end	= gru_invalidate_range_end,
	.alloc_notअगरier		= gru_alloc_notअगरier,
	.मुक्त_notअगरier		= gru_मुक्त_notअगरier,
पूर्ण;

काष्ठा gru_mm_काष्ठा *gru_रेजिस्टर_mmu_notअगरier(व्योम)
अणु
	काष्ठा mmu_notअगरier *mn;

	mn = mmu_notअगरier_get_locked(&gru_mmuops, current->mm);
	अगर (IS_ERR(mn))
		वापस ERR_CAST(mn);

	वापस container_of(mn, काष्ठा gru_mm_काष्ठा, ms_notअगरier);
पूर्ण

व्योम gru_drop_mmu_notअगरier(काष्ठा gru_mm_काष्ठा *gms)
अणु
	mmu_notअगरier_put(&gms->ms_notअगरier);
पूर्ण

/*
 * Setup TGH parameters. There are:
 * 	- 24 TGH handles per GRU chiplet
 * 	- a portion (MAX_LOCAL_TGH) of the handles are reserved क्रम
 * 	  use by blade-local cpus
 * 	- the rest are used by off-blade cpus. This usage is
 * 	  less frequent than blade-local usage.
 *
 * For now, use 16 handles क्रम local flushes, 8 क्रम remote flushes. If the blade
 * has less tan or equal to 16 cpus, each cpu has a unique handle that it can
 * use.
 */
#घोषणा MAX_LOCAL_TGH	16

व्योम gru_tgh_flush_init(काष्ठा gru_state *gru)
अणु
	पूर्णांक cpus, shअगरt = 0, n;

	cpus = uv_blade_nr_possible_cpus(gru->gs_blade_id);

	/* n = cpus rounded up to next घातer of 2 */
	अगर (cpus) अणु
		n = 1 << fls(cpus - 1);

		/*
		 * shअगरt count क्रम converting local cpu# to TGH index
		 *      0 अगर cpus <= MAX_LOCAL_TGH,
		 *      1 अगर cpus <= 2*MAX_LOCAL_TGH,
		 *      etc
		 */
		shअगरt = max(0, fls(n - 1) - fls(MAX_LOCAL_TGH - 1));
	पूर्ण
	gru->gs_tgh_local_shअगरt = shअगरt;

	/* first starting TGH index to use क्रम remote purges */
	gru->gs_tgh_first_remote = (cpus + (1 << shअगरt) - 1) >> shअगरt;

पूर्ण
