<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Defines an spu hypervisor असलtraction layer.
 *
 *  Copyright 2006 Sony Corp.
 */

#अगर !defined(_SPU_PRIV1_H)
#घोषणा _SPU_PRIV1_H
#अगर defined(__KERNEL__)

#समावेश <linux/types.h>

काष्ठा spu;
काष्ठा spu_context;

/* access to priv1 रेजिस्टरs */

काष्ठा spu_priv1_ops अणु
	व्योम (*पूर्णांक_mask_and) (काष्ठा spu *spu, पूर्णांक class, u64 mask);
	व्योम (*पूर्णांक_mask_or) (काष्ठा spu *spu, पूर्णांक class, u64 mask);
	व्योम (*पूर्णांक_mask_set) (काष्ठा spu *spu, पूर्णांक class, u64 mask);
	u64 (*पूर्णांक_mask_get) (काष्ठा spu *spu, पूर्णांक class);
	व्योम (*पूर्णांक_stat_clear) (काष्ठा spu *spu, पूर्णांक class, u64 stat);
	u64 (*पूर्णांक_stat_get) (काष्ठा spu *spu, पूर्णांक class);
	व्योम (*cpu_affinity_set) (काष्ठा spu *spu, पूर्णांक cpu);
	u64 (*mfc_dar_get) (काष्ठा spu *spu);
	u64 (*mfc_dsisr_get) (काष्ठा spu *spu);
	व्योम (*mfc_dsisr_set) (काष्ठा spu *spu, u64 dsisr);
	व्योम (*mfc_sdr_setup) (काष्ठा spu *spu);
	व्योम (*mfc_sr1_set) (काष्ठा spu *spu, u64 sr1);
	u64 (*mfc_sr1_get) (काष्ठा spu *spu);
	व्योम (*mfc_tclass_id_set) (काष्ठा spu *spu, u64 tclass_id);
	u64 (*mfc_tclass_id_get) (काष्ठा spu *spu);
	व्योम (*tlb_invalidate) (काष्ठा spu *spu);
	व्योम (*resource_allocation_groupID_set) (काष्ठा spu *spu, u64 id);
	u64 (*resource_allocation_groupID_get) (काष्ठा spu *spu);
	व्योम (*resource_allocation_enable_set) (काष्ठा spu *spu, u64 enable);
	u64 (*resource_allocation_enable_get) (काष्ठा spu *spu);
पूर्ण;

बाह्य स्थिर काष्ठा spu_priv1_ops* spu_priv1_ops;

अटल अंतरभूत व्योम
spu_पूर्णांक_mask_and (काष्ठा spu *spu, पूर्णांक class, u64 mask)
अणु
	spu_priv1_ops->पूर्णांक_mask_and(spu, class, mask);
पूर्ण

अटल अंतरभूत व्योम
spu_पूर्णांक_mask_or (काष्ठा spu *spu, पूर्णांक class, u64 mask)
अणु
	spu_priv1_ops->पूर्णांक_mask_or(spu, class, mask);
पूर्ण

अटल अंतरभूत व्योम
spu_पूर्णांक_mask_set (काष्ठा spu *spu, पूर्णांक class, u64 mask)
अणु
	spu_priv1_ops->पूर्णांक_mask_set(spu, class, mask);
पूर्ण

अटल अंतरभूत u64
spu_पूर्णांक_mask_get (काष्ठा spu *spu, पूर्णांक class)
अणु
	वापस spu_priv1_ops->पूर्णांक_mask_get(spu, class);
पूर्ण

अटल अंतरभूत व्योम
spu_पूर्णांक_stat_clear (काष्ठा spu *spu, पूर्णांक class, u64 stat)
अणु
	spu_priv1_ops->पूर्णांक_stat_clear(spu, class, stat);
पूर्ण

अटल अंतरभूत u64
spu_पूर्णांक_stat_get (काष्ठा spu *spu, पूर्णांक class)
अणु
	वापस spu_priv1_ops->पूर्णांक_stat_get (spu, class);
पूर्ण

अटल अंतरभूत व्योम
spu_cpu_affinity_set (काष्ठा spu *spu, पूर्णांक cpu)
अणु
	spu_priv1_ops->cpu_affinity_set(spu, cpu);
पूर्ण

अटल अंतरभूत u64
spu_mfc_dar_get (काष्ठा spu *spu)
अणु
	वापस spu_priv1_ops->mfc_dar_get(spu);
पूर्ण

अटल अंतरभूत u64
spu_mfc_dsisr_get (काष्ठा spu *spu)
अणु
	वापस spu_priv1_ops->mfc_dsisr_get(spu);
पूर्ण

अटल अंतरभूत व्योम
spu_mfc_dsisr_set (काष्ठा spu *spu, u64 dsisr)
अणु
	spu_priv1_ops->mfc_dsisr_set(spu, dsisr);
पूर्ण

अटल अंतरभूत व्योम
spu_mfc_sdr_setup (काष्ठा spu *spu)
अणु
	spu_priv1_ops->mfc_sdr_setup(spu);
पूर्ण

अटल अंतरभूत व्योम
spu_mfc_sr1_set (काष्ठा spu *spu, u64 sr1)
अणु
	spu_priv1_ops->mfc_sr1_set(spu, sr1);
पूर्ण

अटल अंतरभूत u64
spu_mfc_sr1_get (काष्ठा spu *spu)
अणु
	वापस spu_priv1_ops->mfc_sr1_get(spu);
पूर्ण

अटल अंतरभूत व्योम
spu_mfc_tclass_id_set (काष्ठा spu *spu, u64 tclass_id)
अणु
	spu_priv1_ops->mfc_tclass_id_set(spu, tclass_id);
पूर्ण

अटल अंतरभूत u64
spu_mfc_tclass_id_get (काष्ठा spu *spu)
अणु
	वापस spu_priv1_ops->mfc_tclass_id_get(spu);
पूर्ण

अटल अंतरभूत व्योम
spu_tlb_invalidate (काष्ठा spu *spu)
अणु
	spu_priv1_ops->tlb_invalidate(spu);
पूर्ण

अटल अंतरभूत व्योम
spu_resource_allocation_groupID_set (काष्ठा spu *spu, u64 id)
अणु
	spu_priv1_ops->resource_allocation_groupID_set(spu, id);
पूर्ण

अटल अंतरभूत u64
spu_resource_allocation_groupID_get (काष्ठा spu *spu)
अणु
	वापस spu_priv1_ops->resource_allocation_groupID_get(spu);
पूर्ण

अटल अंतरभूत व्योम
spu_resource_allocation_enable_set (काष्ठा spu *spu, u64 enable)
अणु
	spu_priv1_ops->resource_allocation_enable_set(spu, enable);
पूर्ण

अटल अंतरभूत u64
spu_resource_allocation_enable_get (काष्ठा spu *spu)
अणु
	वापस spu_priv1_ops->resource_allocation_enable_get(spu);
पूर्ण

/* spu management असलtraction */

काष्ठा spu_management_ops अणु
	पूर्णांक (*क्रमागतerate_spus)(पूर्णांक (*fn)(व्योम *data));
	पूर्णांक (*create_spu)(काष्ठा spu *spu, व्योम *data);
	पूर्णांक (*destroy_spu)(काष्ठा spu *spu);
	व्योम (*enable_spu)(काष्ठा spu_context *ctx);
	व्योम (*disable_spu)(काष्ठा spu_context *ctx);
	पूर्णांक (*init_affinity)(व्योम);
पूर्ण;

बाह्य स्थिर काष्ठा spu_management_ops* spu_management_ops;

अटल अंतरभूत पूर्णांक
spu_क्रमागतerate_spus (पूर्णांक (*fn)(व्योम *data))
अणु
	वापस spu_management_ops->क्रमागतerate_spus(fn);
पूर्ण

अटल अंतरभूत पूर्णांक
spu_create_spu (काष्ठा spu *spu, व्योम *data)
अणु
	वापस spu_management_ops->create_spu(spu, data);
पूर्ण

अटल अंतरभूत पूर्णांक
spu_destroy_spu (काष्ठा spu *spu)
अणु
	वापस spu_management_ops->destroy_spu(spu);
पूर्ण

अटल अंतरभूत पूर्णांक
spu_init_affinity (व्योम)
अणु
	वापस spu_management_ops->init_affinity();
पूर्ण

अटल अंतरभूत व्योम
spu_enable_spu (काष्ठा spu_context *ctx)
अणु
	spu_management_ops->enable_spu(ctx);
पूर्ण

अटल अंतरभूत व्योम
spu_disable_spu (काष्ठा spu_context *ctx)
अणु
	spu_management_ops->disable_spu(ctx);
पूर्ण

/*
 * The declarations following are put here क्रम convenience
 * and only पूर्णांकended to be used by the platक्रमm setup code.
 */

बाह्य स्थिर काष्ठा spu_priv1_ops spu_priv1_mmio_ops;
बाह्य स्थिर काष्ठा spu_priv1_ops spu_priv1_beat_ops;

बाह्य स्थिर काष्ठा spu_management_ops spu_management_of_ops;

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
