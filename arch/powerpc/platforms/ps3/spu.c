<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 Platक्रमm spu routines.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>

#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3.h>

#समावेश "../cell/spufs/spufs.h"
#समावेश "platform.h"

/* spu_management_ops */

/**
 * क्रमागत spe_type - Type of spe to create.
 * @spe_type_logical: Standard logical spe.
 *
 * For use with lv1_स्थिरruct_logical_spe().  The current HV करोes not support
 * any types other than those listed.
 */

क्रमागत spe_type अणु
	SPE_TYPE_LOGICAL = 0,
पूर्ण;

/**
 * काष्ठा spe_shaकरोw - logical spe shaकरोw रेजिस्टर area.
 *
 * Read-only shaकरोw of spe रेजिस्टरs.
 */

काष्ठा spe_shaकरोw अणु
	u8 padding_0140[0x0140];
	u64 पूर्णांक_status_class0_RW;       /* 0x0140 */
	u64 पूर्णांक_status_class1_RW;       /* 0x0148 */
	u64 पूर्णांक_status_class2_RW;       /* 0x0150 */
	u8 padding_0158[0x0610-0x0158];
	u64 mfc_dsisr_RW;               /* 0x0610 */
	u8 padding_0618[0x0620-0x0618];
	u64 mfc_dar_RW;                 /* 0x0620 */
	u8 padding_0628[0x0800-0x0628];
	u64 mfc_dsipr_R;                /* 0x0800 */
	u8 padding_0808[0x0810-0x0808];
	u64 mfc_lscrr_R;                /* 0x0810 */
	u8 padding_0818[0x0c00-0x0818];
	u64 mfc_cer_R;                  /* 0x0c00 */
	u8 padding_0c08[0x0f00-0x0c08];
	u64 spe_execution_status;       /* 0x0f00 */
	u8 padding_0f08[0x1000-0x0f08];
पूर्ण;

/**
 * क्रमागत spe_ex_state - Logical spe execution state.
 * @spe_ex_state_unexecutable: Uninitialized.
 * @spe_ex_state_executable: Enabled, not पढ़ोy.
 * @spe_ex_state_executed: Ready क्रम use.
 *
 * The execution state (status) of the logical spe as reported in
 * काष्ठा spe_shaकरोw:spe_execution_status.
 */

क्रमागत spe_ex_state अणु
	SPE_EX_STATE_UNEXECUTABLE = 0,
	SPE_EX_STATE_EXECUTABLE = 2,
	SPE_EX_STATE_EXECUTED = 3,
पूर्ण;

/**
 * काष्ठा priv1_cache - Cached values of priv1 रेजिस्टरs.
 * @masks[]: Array of cached spe पूर्णांकerrupt masks, indexed by class.
 * @sr1: Cached mfc_sr1 रेजिस्टर.
 * @tclass_id: Cached mfc_tclass_id रेजिस्टर.
 */

काष्ठा priv1_cache अणु
	u64 masks[3];
	u64 sr1;
	u64 tclass_id;
पूर्ण;

/**
 * काष्ठा spu_pdata - Platक्रमm state variables.
 * @spe_id: HV spe id वापसed by lv1_स्थिरruct_logical_spe().
 * @resource_id: HV spe resource id वापसed by
 * 	ps3_repository_पढ़ो_spe_resource_id().
 * @priv2_addr: lpar address of spe priv2 area वापसed by
 * 	lv1_स्थिरruct_logical_spe().
 * @shaकरोw_addr: lpar address of spe रेजिस्टर shaकरोw area वापसed by
 * 	lv1_स्थिरruct_logical_spe().
 * @shaकरोw: Virtual (ioremap) address of spe रेजिस्टर shaकरोw area.
 * @cache: Cached values of priv1 रेजिस्टरs.
 */

काष्ठा spu_pdata अणु
	u64 spe_id;
	u64 resource_id;
	u64 priv2_addr;
	u64 shaकरोw_addr;
	काष्ठा spe_shaकरोw __iomem *shaकरोw;
	काष्ठा priv1_cache cache;
पूर्ण;

अटल काष्ठा spu_pdata *spu_pdata(काष्ठा spu *spu)
अणु
	वापस spu->pdata;
पूर्ण

#घोषणा dump_areas(_a, _b, _c, _d, _e) \
	_dump_areas(_a, _b, _c, _d, _e, __func__, __LINE__)
अटल व्योम _dump_areas(अचिन्हित पूर्णांक spe_id, अचिन्हित दीर्घ priv2,
	अचिन्हित दीर्घ problem, अचिन्हित दीर्घ ls, अचिन्हित दीर्घ shaकरोw,
	स्थिर अक्षर* func, पूर्णांक line)
अणु
	pr_debug("%s:%d: spe_id:  %xh (%u)\n", func, line, spe_id, spe_id);
	pr_debug("%s:%d: priv2:   %lxh\n", func, line, priv2);
	pr_debug("%s:%d: problem: %lxh\n", func, line, problem);
	pr_debug("%s:%d: ls:      %lxh\n", func, line, ls);
	pr_debug("%s:%d: shadow:  %lxh\n", func, line, shaकरोw);
पूर्ण

u64 ps3_get_spe_id(व्योम *arg)
अणु
	वापस spu_pdata(arg)->spe_id;
पूर्ण
EXPORT_SYMBOL_GPL(ps3_get_spe_id);

अटल अचिन्हित दीर्घ get_vas_id(व्योम)
अणु
	u64 id;

	lv1_get_logical_ppe_id(&id);
	lv1_get_भव_address_space_id_of_ppe(&id);

	वापस id;
पूर्ण

अटल पूर्णांक __init स्थिरruct_spu(काष्ठा spu *spu)
अणु
	पूर्णांक result;
	u64 unused;
	u64 problem_phys;
	u64 local_store_phys;

	result = lv1_स्थिरruct_logical_spe(PAGE_SHIFT, PAGE_SHIFT, PAGE_SHIFT,
		PAGE_SHIFT, PAGE_SHIFT, get_vas_id(), SPE_TYPE_LOGICAL,
		&spu_pdata(spu)->priv2_addr, &problem_phys,
		&local_store_phys, &unused,
		&spu_pdata(spu)->shaकरोw_addr,
		&spu_pdata(spu)->spe_id);
	spu->problem_phys = problem_phys;
	spu->local_store_phys = local_store_phys;

	अगर (result) अणु
		pr_debug("%s:%d: lv1_construct_logical_spe failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		वापस result;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम spu_unmap(काष्ठा spu *spu)
अणु
	iounmap(spu->priv2);
	iounmap(spu->problem);
	iounmap((__क्रमce u8 __iomem *)spu->local_store);
	iounmap(spu_pdata(spu)->shaकरोw);
पूर्ण

/**
 * setup_areas - Map the spu regions पूर्णांकo the address space.
 *
 * The current HV requires the spu shaकरोw regs to be mapped with the
 * PTE page protection bits set as पढ़ो-only.
 */

अटल पूर्णांक __init setup_areas(काष्ठा spu *spu)
अणु
	काष्ठा table अणुअक्षर* name; अचिन्हित दीर्घ addr; अचिन्हित दीर्घ size;पूर्ण;
	अचिन्हित दीर्घ shaकरोw_flags = pgprot_val(pgprot_noncached_wc(PAGE_KERNEL_RO));

	spu_pdata(spu)->shaकरोw = ioremap_prot(spu_pdata(spu)->shaकरोw_addr,
					      माप(काष्ठा spe_shaकरोw), shaकरोw_flags);
	अगर (!spu_pdata(spu)->shaकरोw) अणु
		pr_debug("%s:%d: ioremap shadow failed\n", __func__, __LINE__);
		जाओ fail_ioremap;
	पूर्ण

	spu->local_store = (__क्रमce व्योम *)ioremap_wc(spu->local_store_phys, LS_SIZE);

	अगर (!spu->local_store) अणु
		pr_debug("%s:%d: ioremap local_store failed\n",
			__func__, __LINE__);
		जाओ fail_ioremap;
	पूर्ण

	spu->problem = ioremap(spu->problem_phys,
		माप(काष्ठा spu_problem));

	अगर (!spu->problem) अणु
		pr_debug("%s:%d: ioremap problem failed\n", __func__, __LINE__);
		जाओ fail_ioremap;
	पूर्ण

	spu->priv2 = ioremap(spu_pdata(spu)->priv2_addr,
		माप(काष्ठा spu_priv2));

	अगर (!spu->priv2) अणु
		pr_debug("%s:%d: ioremap priv2 failed\n", __func__, __LINE__);
		जाओ fail_ioremap;
	पूर्ण

	dump_areas(spu_pdata(spu)->spe_id, spu_pdata(spu)->priv2_addr,
		spu->problem_phys, spu->local_store_phys,
		spu_pdata(spu)->shaकरोw_addr);
	dump_areas(spu_pdata(spu)->spe_id, (अचिन्हित दीर्घ)spu->priv2,
		(अचिन्हित दीर्घ)spu->problem, (अचिन्हित दीर्घ)spu->local_store,
		(अचिन्हित दीर्घ)spu_pdata(spu)->shaकरोw);

	वापस 0;

fail_ioremap:
	spu_unmap(spu);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __init setup_पूर्णांकerrupts(काष्ठा spu *spu)
अणु
	पूर्णांक result;

	result = ps3_spe_irq_setup(PS3_BINDING_CPU_ANY, spu_pdata(spu)->spe_id,
		0, &spu->irqs[0]);

	अगर (result)
		जाओ fail_alloc_0;

	result = ps3_spe_irq_setup(PS3_BINDING_CPU_ANY, spu_pdata(spu)->spe_id,
		1, &spu->irqs[1]);

	अगर (result)
		जाओ fail_alloc_1;

	result = ps3_spe_irq_setup(PS3_BINDING_CPU_ANY, spu_pdata(spu)->spe_id,
		2, &spu->irqs[2]);

	अगर (result)
		जाओ fail_alloc_2;

	वापस result;

fail_alloc_2:
	ps3_spe_irq_destroy(spu->irqs[1]);
fail_alloc_1:
	ps3_spe_irq_destroy(spu->irqs[0]);
fail_alloc_0:
	spu->irqs[0] = spu->irqs[1] = spu->irqs[2] = 0;
	वापस result;
पूर्ण

अटल पूर्णांक __init enable_spu(काष्ठा spu *spu)
अणु
	पूर्णांक result;

	result = lv1_enable_logical_spe(spu_pdata(spu)->spe_id,
		spu_pdata(spu)->resource_id);

	अगर (result) अणु
		pr_debug("%s:%d: lv1_enable_logical_spe failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		जाओ fail_enable;
	पूर्ण

	result = setup_areas(spu);

	अगर (result)
		जाओ fail_areas;

	result = setup_पूर्णांकerrupts(spu);

	अगर (result)
		जाओ fail_पूर्णांकerrupts;

	वापस 0;

fail_पूर्णांकerrupts:
	spu_unmap(spu);
fail_areas:
	lv1_disable_logical_spe(spu_pdata(spu)->spe_id, 0);
fail_enable:
	वापस result;
पूर्ण

अटल पूर्णांक ps3_destroy_spu(काष्ठा spu *spu)
अणु
	पूर्णांक result;

	pr_debug("%s:%d spu_%d\n", __func__, __LINE__, spu->number);

	result = lv1_disable_logical_spe(spu_pdata(spu)->spe_id, 0);
	BUG_ON(result);

	ps3_spe_irq_destroy(spu->irqs[2]);
	ps3_spe_irq_destroy(spu->irqs[1]);
	ps3_spe_irq_destroy(spu->irqs[0]);

	spu->irqs[0] = spu->irqs[1] = spu->irqs[2] = 0;

	spu_unmap(spu);

	result = lv1_deकाष्ठा_logical_spe(spu_pdata(spu)->spe_id);
	BUG_ON(result);

	kमुक्त(spu->pdata);
	spu->pdata = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक __init ps3_create_spu(काष्ठा spu *spu, व्योम *data)
अणु
	पूर्णांक result;

	pr_debug("%s:%d spu_%d\n", __func__, __LINE__, spu->number);

	spu->pdata = kzalloc(माप(काष्ठा spu_pdata),
		GFP_KERNEL);

	अगर (!spu->pdata) अणु
		result = -ENOMEM;
		जाओ fail_दो_स्मृति;
	पूर्ण

	spu_pdata(spu)->resource_id = (अचिन्हित दीर्घ)data;

	/* Init cached reg values to HV शेषs. */

	spu_pdata(spu)->cache.sr1 = 0x33;

	result = स्थिरruct_spu(spu);

	अगर (result)
		जाओ fail_स्थिरruct;

	/* For now, just go ahead and enable it. */

	result = enable_spu(spu);

	अगर (result)
		जाओ fail_enable;

	/* Make sure the spu is in SPE_EX_STATE_EXECUTED. */

	/* need something better here!!! */
	जबतक (in_be64(&spu_pdata(spu)->shaकरोw->spe_execution_status)
		!= SPE_EX_STATE_EXECUTED)
		(व्योम)0;

	वापस result;

fail_enable:
fail_स्थिरruct:
	ps3_destroy_spu(spu);
fail_दो_स्मृति:
	वापस result;
पूर्ण

अटल पूर्णांक __init ps3_क्रमागतerate_spus(पूर्णांक (*fn)(व्योम *data))
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक num_resource_id;
	अचिन्हित पूर्णांक i;

	result = ps3_repository_पढ़ो_num_spu_resource_id(&num_resource_id);

	pr_debug("%s:%d: num_resource_id %u\n", __func__, __LINE__,
		num_resource_id);

	/*
	 * For now, just create logical spus equal to the number
	 * of physical spus reserved क्रम the partition.
	 */

	क्रम (i = 0; i < num_resource_id; i++) अणु
		क्रमागत ps3_spu_resource_type resource_type;
		अचिन्हित पूर्णांक resource_id;

		result = ps3_repository_पढ़ो_spu_resource_id(i,
			&resource_type, &resource_id);

		अगर (result)
			अवरोध;

		अगर (resource_type == PS3_SPU_RESOURCE_TYPE_EXCLUSIVE) अणु
			result = fn((व्योम*)(अचिन्हित दीर्घ)resource_id);

			अगर (result)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (result) अणु
		prपूर्णांकk(KERN_WARNING "%s:%d: Error initializing spus\n",
			__func__, __LINE__);
		वापस result;
	पूर्ण

	वापस num_resource_id;
पूर्ण

अटल पूर्णांक ps3_init_affinity(व्योम)
अणु
	वापस 0;
पूर्ण

/**
 * ps3_enable_spu - Enable SPU run control.
 *
 * An outstanding enhancement क्रम the PS3 would be to add a guard to check
 * क्रम incorrect access to the spu problem state when the spu context is
 * disabled.  This check could be implemented with a flag added to the spu
 * context that would inhibit mapping problem state pages, and a routine
 * to unmap spu problem state pages.  When the spu is enabled with
 * ps3_enable_spu() the flag would be set allowing pages to be mapped,
 * and when the spu is disabled with ps3_disable_spu() the flag would be
 * cleared and the mapped problem state pages would be unmapped.
 */

अटल व्योम ps3_enable_spu(काष्ठा spu_context *ctx)
अणु
पूर्ण

अटल व्योम ps3_disable_spu(काष्ठा spu_context *ctx)
अणु
	ctx->ops->runcntl_stop(ctx);
पूर्ण

अटल स्थिर काष्ठा spu_management_ops spu_management_ps3_ops = अणु
	.क्रमागतerate_spus = ps3_क्रमागतerate_spus,
	.create_spu = ps3_create_spu,
	.destroy_spu = ps3_destroy_spu,
	.enable_spu = ps3_enable_spu,
	.disable_spu = ps3_disable_spu,
	.init_affinity = ps3_init_affinity,
पूर्ण;

/* spu_priv1_ops */

अटल व्योम पूर्णांक_mask_and(काष्ठा spu *spu, पूर्णांक class, u64 mask)
अणु
	u64 old_mask;

	/* are these serialized by caller??? */
	old_mask = spu_पूर्णांक_mask_get(spu, class);
	spu_पूर्णांक_mask_set(spu, class, old_mask & mask);
पूर्ण

अटल व्योम पूर्णांक_mask_or(काष्ठा spu *spu, पूर्णांक class, u64 mask)
अणु
	u64 old_mask;

	old_mask = spu_पूर्णांक_mask_get(spu, class);
	spu_पूर्णांक_mask_set(spu, class, old_mask | mask);
पूर्ण

अटल व्योम पूर्णांक_mask_set(काष्ठा spu *spu, पूर्णांक class, u64 mask)
अणु
	spu_pdata(spu)->cache.masks[class] = mask;
	lv1_set_spe_पूर्णांकerrupt_mask(spu_pdata(spu)->spe_id, class,
		spu_pdata(spu)->cache.masks[class]);
पूर्ण

अटल u64 पूर्णांक_mask_get(काष्ठा spu *spu, पूर्णांक class)
अणु
	वापस spu_pdata(spu)->cache.masks[class];
पूर्ण

अटल व्योम पूर्णांक_stat_clear(काष्ठा spu *spu, पूर्णांक class, u64 stat)
अणु
	/* Note that MFC_DSISR will be cleared when class1[MF] is set. */

	lv1_clear_spe_पूर्णांकerrupt_status(spu_pdata(spu)->spe_id, class,
		stat, 0);
पूर्ण

अटल u64 पूर्णांक_stat_get(काष्ठा spu *spu, पूर्णांक class)
अणु
	u64 stat;

	lv1_get_spe_पूर्णांकerrupt_status(spu_pdata(spu)->spe_id, class, &stat);
	वापस stat;
पूर्ण

अटल व्योम cpu_affinity_set(काष्ठा spu *spu, पूर्णांक cpu)
अणु
	/* No support. */
पूर्ण

अटल u64 mfc_dar_get(काष्ठा spu *spu)
अणु
	वापस in_be64(&spu_pdata(spu)->shaकरोw->mfc_dar_RW);
पूर्ण

अटल व्योम mfc_dsisr_set(काष्ठा spu *spu, u64 dsisr)
अणु
	/* Nothing to करो, cleared in पूर्णांक_stat_clear(). */
पूर्ण

अटल u64 mfc_dsisr_get(काष्ठा spu *spu)
अणु
	वापस in_be64(&spu_pdata(spu)->shaकरोw->mfc_dsisr_RW);
पूर्ण

अटल व्योम mfc_sdr_setup(काष्ठा spu *spu)
अणु
	/* Nothing to करो. */
पूर्ण

अटल व्योम mfc_sr1_set(काष्ठा spu *spu, u64 sr1)
अणु
	/* Check bits allowed by HV. */

	अटल स्थिर u64 allowed = ~(MFC_STATE1_LOCAL_STORAGE_DECODE_MASK
		| MFC_STATE1_PROBLEM_STATE_MASK);

	BUG_ON((sr1 & allowed) != (spu_pdata(spu)->cache.sr1 & allowed));

	spu_pdata(spu)->cache.sr1 = sr1;
	lv1_set_spe_privilege_state_area_1_रेजिस्टर(
		spu_pdata(spu)->spe_id,
		दुरत्व(काष्ठा spu_priv1, mfc_sr1_RW),
		spu_pdata(spu)->cache.sr1);
पूर्ण

अटल u64 mfc_sr1_get(काष्ठा spu *spu)
अणु
	वापस spu_pdata(spu)->cache.sr1;
पूर्ण

अटल व्योम mfc_tclass_id_set(काष्ठा spu *spu, u64 tclass_id)
अणु
	spu_pdata(spu)->cache.tclass_id = tclass_id;
	lv1_set_spe_privilege_state_area_1_रेजिस्टर(
		spu_pdata(spu)->spe_id,
		दुरत्व(काष्ठा spu_priv1, mfc_tclass_id_RW),
		spu_pdata(spu)->cache.tclass_id);
पूर्ण

अटल u64 mfc_tclass_id_get(काष्ठा spu *spu)
अणु
	वापस spu_pdata(spu)->cache.tclass_id;
पूर्ण

अटल व्योम tlb_invalidate(काष्ठा spu *spu)
अणु
	/* Nothing to करो. */
पूर्ण

अटल व्योम resource_allocation_groupID_set(काष्ठा spu *spu, u64 id)
अणु
	/* No support. */
पूर्ण

अटल u64 resource_allocation_groupID_get(काष्ठा spu *spu)
अणु
	वापस 0; /* No support. */
पूर्ण

अटल व्योम resource_allocation_enable_set(काष्ठा spu *spu, u64 enable)
अणु
	/* No support. */
पूर्ण

अटल u64 resource_allocation_enable_get(काष्ठा spu *spu)
अणु
	वापस 0; /* No support. */
पूर्ण

अटल स्थिर काष्ठा spu_priv1_ops spu_priv1_ps3_ops = अणु
	.पूर्णांक_mask_and = पूर्णांक_mask_and,
	.पूर्णांक_mask_or = पूर्णांक_mask_or,
	.पूर्णांक_mask_set = पूर्णांक_mask_set,
	.पूर्णांक_mask_get = पूर्णांक_mask_get,
	.पूर्णांक_stat_clear = पूर्णांक_stat_clear,
	.पूर्णांक_stat_get = पूर्णांक_stat_get,
	.cpu_affinity_set = cpu_affinity_set,
	.mfc_dar_get = mfc_dar_get,
	.mfc_dsisr_set = mfc_dsisr_set,
	.mfc_dsisr_get = mfc_dsisr_get,
	.mfc_sdr_setup = mfc_sdr_setup,
	.mfc_sr1_set = mfc_sr1_set,
	.mfc_sr1_get = mfc_sr1_get,
	.mfc_tclass_id_set = mfc_tclass_id_set,
	.mfc_tclass_id_get = mfc_tclass_id_get,
	.tlb_invalidate = tlb_invalidate,
	.resource_allocation_groupID_set = resource_allocation_groupID_set,
	.resource_allocation_groupID_get = resource_allocation_groupID_get,
	.resource_allocation_enable_set = resource_allocation_enable_set,
	.resource_allocation_enable_get = resource_allocation_enable_get,
पूर्ण;

व्योम ps3_spu_set_platक्रमm(व्योम)
अणु
	spu_priv1_ops = &spu_priv1_ps3_ops;
	spu_management_ops = &spu_management_ps3_ops;
पूर्ण
