<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 pagetable management routines.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006, 2007 Sony Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3fb.h>

#घोषणा PS3_VERBOSE_RESULT
#समावेश "platform.h"

/**
 * क्रमागत lpar_vas_id - id of LPAR भव address space.
 * @lpar_vas_id_current: Current selected भव address space
 *
 * Identअगरy the target LPAR address space.
 */

क्रमागत ps3_lpar_vas_id अणु
	PS3_LPAR_VAS_ID_CURRENT = 0,
पूर्ण;


अटल DEFINE_SPINLOCK(ps3_htab_lock);

अटल दीर्घ ps3_hpte_insert(अचिन्हित दीर्घ hpte_group, अचिन्हित दीर्घ vpn,
	अचिन्हित दीर्घ pa, अचिन्हित दीर्घ rflags, अचिन्हित दीर्घ vflags,
	पूर्णांक psize, पूर्णांक apsize, पूर्णांक ssize)
अणु
	पूर्णांक result;
	u64 hpte_v, hpte_r;
	u64 inserted_index;
	u64 evicted_v, evicted_r;
	u64 hpte_v_array[4], hpte_rs;
	अचिन्हित दीर्घ flags;
	दीर्घ ret = -1;

	/*
	 * lv1_insert_htab_entry() will search क्रम victim
	 * entry in both primary and secondary pte group
	 */
	vflags &= ~HPTE_V_SECONDARY;

	hpte_v = hpte_encode_v(vpn, psize, apsize, ssize) | vflags | HPTE_V_VALID;
	hpte_r = hpte_encode_r(ps3_mm_phys_to_lpar(pa), psize, apsize) | rflags;

	spin_lock_irqsave(&ps3_htab_lock, flags);

	/* talk hvc to replace entries BOLTED == 0 */
	result = lv1_insert_htab_entry(PS3_LPAR_VAS_ID_CURRENT, hpte_group,
				       hpte_v, hpte_r,
				       HPTE_V_BOLTED, 0,
				       &inserted_index,
				       &evicted_v, &evicted_r);

	अगर (result) अणु
		/* all entries bolted !*/
		pr_info("%s:result=%s vpn=%lx pa=%lx ix=%lx v=%llx r=%llx\n",
			__func__, ps3_result(result), vpn, pa, hpte_group,
			hpte_v, hpte_r);
		BUG();
	पूर्ण

	/*
	 * see अगर the entry is inserted पूर्णांकo secondary pteg
	 */
	result = lv1_पढ़ो_htab_entries(PS3_LPAR_VAS_ID_CURRENT,
				       inserted_index & ~0x3UL,
				       &hpte_v_array[0], &hpte_v_array[1],
				       &hpte_v_array[2], &hpte_v_array[3],
				       &hpte_rs);
	BUG_ON(result);

	अगर (hpte_v_array[inserted_index % 4] & HPTE_V_SECONDARY)
		ret = (inserted_index & 7) | (1 << 3);
	अन्यथा
		ret = inserted_index & 7;

	spin_unlock_irqrestore(&ps3_htab_lock, flags);

	वापस ret;
पूर्ण

अटल दीर्घ ps3_hpte_हटाओ(अचिन्हित दीर्घ hpte_group)
अणु
	panic("ps3_hpte_remove() not implemented");
	वापस 0;
पूर्ण

अटल दीर्घ ps3_hpte_updatepp(अचिन्हित दीर्घ slot, अचिन्हित दीर्घ newpp,
			      अचिन्हित दीर्घ vpn, पूर्णांक psize, पूर्णांक apsize,
			      पूर्णांक ssize, अचिन्हित दीर्घ inv_flags)
अणु
	पूर्णांक result;
	u64 hpte_v, want_v, hpte_rs;
	u64 hpte_v_array[4];
	अचिन्हित दीर्घ flags;
	दीर्घ ret;

	want_v = hpte_encode_avpn(vpn, psize, ssize);

	spin_lock_irqsave(&ps3_htab_lock, flags);

	result = lv1_पढ़ो_htab_entries(PS3_LPAR_VAS_ID_CURRENT, slot & ~0x3UL,
				       &hpte_v_array[0], &hpte_v_array[1],
				       &hpte_v_array[2], &hpte_v_array[3],
				       &hpte_rs);

	अगर (result) अणु
		pr_info("%s: result=%s read vpn=%lx slot=%lx psize=%d\n",
			__func__, ps3_result(result), vpn, slot, psize);
		BUG();
	पूर्ण

	hpte_v = hpte_v_array[slot % 4];

	/*
	 * As lv1_पढ़ो_htab_entries() करोes not give us the RPN, we can
	 * not synthesize the new hpte_r value here, and thereक्रमe can
	 * not update the hpte with lv1_insert_htab_entry(), so we
	 * instead invalidate it and ask the caller to update it via
	 * ps3_hpte_insert() by वापसing a -1 value.
	 */
	अगर (!HPTE_V_COMPARE(hpte_v, want_v) || !(hpte_v & HPTE_V_VALID)) अणु
		/* not found */
		ret = -1;
	पूर्ण अन्यथा अणु
		/* entry found, just invalidate it */
		result = lv1_ग_लिखो_htab_entry(PS3_LPAR_VAS_ID_CURRENT,
					      slot, 0, 0);
		ret = -1;
	पूर्ण

	spin_unlock_irqrestore(&ps3_htab_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम ps3_hpte_updateboltedpp(अचिन्हित दीर्घ newpp, अचिन्हित दीर्घ ea,
	पूर्णांक psize, पूर्णांक ssize)
अणु
	panic("ps3_hpte_updateboltedpp() not implemented");
पूर्ण

अटल व्योम ps3_hpte_invalidate(अचिन्हित दीर्घ slot, अचिन्हित दीर्घ vpn,
				पूर्णांक psize, पूर्णांक apsize, पूर्णांक ssize, पूर्णांक local)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	spin_lock_irqsave(&ps3_htab_lock, flags);

	result = lv1_ग_लिखो_htab_entry(PS3_LPAR_VAS_ID_CURRENT, slot, 0, 0);

	अगर (result) अणु
		pr_info("%s: result=%s vpn=%lx slot=%lx psize=%d\n",
			__func__, ps3_result(result), vpn, slot, psize);
		BUG();
	पूर्ण

	spin_unlock_irqrestore(&ps3_htab_lock, flags);
पूर्ण

अटल व्योम ps3_hpte_clear(व्योम)
अणु
	अचिन्हित दीर्घ hpte_count = (1UL << ppc64_pft_size) >> 4;
	u64 i;

	क्रम (i = 0; i < hpte_count; i++)
		lv1_ग_लिखो_htab_entry(PS3_LPAR_VAS_ID_CURRENT, i, 0, 0);

	ps3_mm_shutकरोwn();
	ps3_mm_vas_destroy();
पूर्ण

व्योम __init ps3_hpte_init(अचिन्हित दीर्घ htab_size)
अणु
	mmu_hash_ops.hpte_invalidate = ps3_hpte_invalidate;
	mmu_hash_ops.hpte_updatepp = ps3_hpte_updatepp;
	mmu_hash_ops.hpte_updateboltedpp = ps3_hpte_updateboltedpp;
	mmu_hash_ops.hpte_insert = ps3_hpte_insert;
	mmu_hash_ops.hpte_हटाओ = ps3_hpte_हटाओ;
	mmu_hash_ops.hpte_clear_all = ps3_hpte_clear;

	ppc64_pft_size = __ilog2(htab_size);
पूर्ण

