<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * spu hypervisor असलtraction क्रम direct hardware access.
 *
 *  (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *  Copyright 2006 Sony Corp.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/prom.h>

#समावेश "interrupt.h"
#समावेश "spu_priv1_mmio.h"

अटल व्योम पूर्णांक_mask_and(काष्ठा spu *spu, पूर्णांक class, u64 mask)
अणु
	u64 old_mask;

	old_mask = in_be64(&spu->priv1->पूर्णांक_mask_RW[class]);
	out_be64(&spu->priv1->पूर्णांक_mask_RW[class], old_mask & mask);
पूर्ण

अटल व्योम पूर्णांक_mask_or(काष्ठा spu *spu, पूर्णांक class, u64 mask)
अणु
	u64 old_mask;

	old_mask = in_be64(&spu->priv1->पूर्णांक_mask_RW[class]);
	out_be64(&spu->priv1->पूर्णांक_mask_RW[class], old_mask | mask);
पूर्ण

अटल व्योम पूर्णांक_mask_set(काष्ठा spu *spu, पूर्णांक class, u64 mask)
अणु
	out_be64(&spu->priv1->पूर्णांक_mask_RW[class], mask);
पूर्ण

अटल u64 पूर्णांक_mask_get(काष्ठा spu *spu, पूर्णांक class)
अणु
	वापस in_be64(&spu->priv1->पूर्णांक_mask_RW[class]);
पूर्ण

अटल व्योम पूर्णांक_stat_clear(काष्ठा spu *spu, पूर्णांक class, u64 stat)
अणु
	out_be64(&spu->priv1->पूर्णांक_stat_RW[class], stat);
पूर्ण

अटल u64 पूर्णांक_stat_get(काष्ठा spu *spu, पूर्णांक class)
अणु
	वापस in_be64(&spu->priv1->पूर्णांक_stat_RW[class]);
पूर्ण

अटल व्योम cpu_affinity_set(काष्ठा spu *spu, पूर्णांक cpu)
अणु
	u64 target;
	u64 route;

	अगर (nr_cpus_node(spu->node)) अणु
		स्थिर काष्ठा cpumask *spumask = cpumask_of_node(spu->node),
			*cpumask = cpumask_of_node(cpu_to_node(cpu));

		अगर (!cpumask_पूर्णांकersects(spumask, cpumask))
			वापस;
	पूर्ण

	target = iic_get_target_id(cpu);
	route = target << 48 | target << 32 | target << 16;
	out_be64(&spu->priv1->पूर्णांक_route_RW, route);
पूर्ण

अटल u64 mfc_dar_get(काष्ठा spu *spu)
अणु
	वापस in_be64(&spu->priv1->mfc_dar_RW);
पूर्ण

अटल u64 mfc_dsisr_get(काष्ठा spu *spu)
अणु
	वापस in_be64(&spu->priv1->mfc_dsisr_RW);
पूर्ण

अटल व्योम mfc_dsisr_set(काष्ठा spu *spu, u64 dsisr)
अणु
	out_be64(&spu->priv1->mfc_dsisr_RW, dsisr);
पूर्ण

अटल व्योम mfc_sdr_setup(काष्ठा spu *spu)
अणु
	out_be64(&spu->priv1->mfc_sdr_RW, mfspr(SPRN_SDR1));
पूर्ण

अटल व्योम mfc_sr1_set(काष्ठा spu *spu, u64 sr1)
अणु
	out_be64(&spu->priv1->mfc_sr1_RW, sr1);
पूर्ण

अटल u64 mfc_sr1_get(काष्ठा spu *spu)
अणु
	वापस in_be64(&spu->priv1->mfc_sr1_RW);
पूर्ण

अटल व्योम mfc_tclass_id_set(काष्ठा spu *spu, u64 tclass_id)
अणु
	out_be64(&spu->priv1->mfc_tclass_id_RW, tclass_id);
पूर्ण

अटल u64 mfc_tclass_id_get(काष्ठा spu *spu)
अणु
	वापस in_be64(&spu->priv1->mfc_tclass_id_RW);
पूर्ण

अटल व्योम tlb_invalidate(काष्ठा spu *spu)
अणु
	out_be64(&spu->priv1->tlb_invalidate_entry_W, 0ul);
पूर्ण

अटल व्योम resource_allocation_groupID_set(काष्ठा spu *spu, u64 id)
अणु
	out_be64(&spu->priv1->resource_allocation_groupID_RW, id);
पूर्ण

अटल u64 resource_allocation_groupID_get(काष्ठा spu *spu)
अणु
	वापस in_be64(&spu->priv1->resource_allocation_groupID_RW);
पूर्ण

अटल व्योम resource_allocation_enable_set(काष्ठा spu *spu, u64 enable)
अणु
	out_be64(&spu->priv1->resource_allocation_enable_RW, enable);
पूर्ण

अटल u64 resource_allocation_enable_get(काष्ठा spu *spu)
अणु
	वापस in_be64(&spu->priv1->resource_allocation_enable_RW);
पूर्ण

स्थिर काष्ठा spu_priv1_ops spu_priv1_mmio_ops =
अणु
	.पूर्णांक_mask_and = पूर्णांक_mask_and,
	.पूर्णांक_mask_or = पूर्णांक_mask_or,
	.पूर्णांक_mask_set = पूर्णांक_mask_set,
	.पूर्णांक_mask_get = पूर्णांक_mask_get,
	.पूर्णांक_stat_clear = पूर्णांक_stat_clear,
	.पूर्णांक_stat_get = पूर्णांक_stat_get,
	.cpu_affinity_set = cpu_affinity_set,
	.mfc_dar_get = mfc_dar_get,
	.mfc_dsisr_get = mfc_dsisr_get,
	.mfc_dsisr_set = mfc_dsisr_set,
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
