<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright 2018 Marty E. Plummer <hanetzer@starपंचांगail.com> */
/* Copyright 2019 Linaro, Ltd, Rob Herring <robh@kernel.org> */

#अगर_अघोषित __PANFROST_DEVICE_H__
#घोषणा __PANFROST_DEVICE_H__

#समावेश <linux/atomic.h>
#समावेश <linux/io-pgtable.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spinlock.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mm.h>
#समावेश <drm/gpu_scheduler.h>

#समावेश "panfrost_devfreq.h"

काष्ठा panfrost_device;
काष्ठा panfrost_mmu;
काष्ठा panfrost_job_slot;
काष्ठा panfrost_job;
काष्ठा panfrost_perfcnt;

#घोषणा NUM_JOB_SLOTS 3
#घोषणा MAX_PM_DOMAINS 3

काष्ठा panfrost_features अणु
	u16 id;
	u16 revision;

	u64 shader_present;
	u64 tiler_present;
	u64 l2_present;
	u64 stack_present;
	u32 as_present;
	u32 js_present;

	u32 l2_features;
	u32 core_features;
	u32 tiler_features;
	u32 mem_features;
	u32 mmu_features;
	u32 thपढ़ो_features;
	u32 max_thपढ़ोs;
	u32 thपढ़ो_max_workgroup_sz;
	u32 thपढ़ो_max_barrier_sz;
	u32 coherency_features;
	u32 texture_features[4];
	u32 js_features[16];

	u32 nr_core_groups;
	u32 thपढ़ो_tls_alloc;

	अचिन्हित दीर्घ hw_features[64 / BITS_PER_LONG];
	अचिन्हित दीर्घ hw_issues[64 / BITS_PER_LONG];
पूर्ण;

/*
 * Features that cannot be स्वतःmatically detected and need matching using the
 * compatible string, typically SoC-specअगरic.
 */
काष्ठा panfrost_compatible अणु
	/* Supplies count and names. */
	पूर्णांक num_supplies;
	स्थिर अक्षर * स्थिर *supply_names;
	/*
	 * Number of घातer करोमुख्यs required, note that values 0 and 1 are
	 * handled identically, as only values > 1 need special handling.
	 */
	पूर्णांक num_pm_करोमुख्यs;
	/* Only required अगर num_pm_करोमुख्यs > 1. */
	स्थिर अक्षर * स्थिर *pm_करोमुख्य_names;

	/* Venकरोr implementation quirks callback */
	व्योम (*venकरोr_quirk)(काष्ठा panfrost_device *pfdev);
पूर्ण;

काष्ठा panfrost_device अणु
	काष्ठा device *dev;
	काष्ठा drm_device *ddev;
	काष्ठा platक्रमm_device *pdev;

	व्योम __iomem *iomem;
	काष्ठा clk *घड़ी;
	काष्ठा clk *bus_घड़ी;
	काष्ठा regulator_bulk_data *regulators;
	काष्ठा reset_control *rstc;
	/* pm_करोमुख्यs क्रम devices with more than one. */
	काष्ठा device *pm_करोमुख्य_devs[MAX_PM_DOMAINS];
	काष्ठा device_link *pm_करोमुख्य_links[MAX_PM_DOMAINS];
	bool coherent;

	काष्ठा panfrost_features features;
	स्थिर काष्ठा panfrost_compatible *comp;

	spinlock_t as_lock;
	अचिन्हित दीर्घ as_in_use_mask;
	अचिन्हित दीर्घ as_alloc_mask;
	काष्ठा list_head as_lru_list;

	काष्ठा panfrost_job_slot *js;

	काष्ठा panfrost_job *jobs[NUM_JOB_SLOTS];
	काष्ठा list_head scheduled_jobs;

	काष्ठा panfrost_perfcnt *perfcnt;

	काष्ठा mutex sched_lock;

	काष्ठा अणु
		काष्ठा work_काष्ठा work;
		atomic_t pending;
	पूर्ण reset;

	काष्ठा mutex shrinker_lock;
	काष्ठा list_head shrinker_list;
	काष्ठा shrinker shrinker;

	काष्ठा panfrost_devfreq pfdevfreq;
पूर्ण;

काष्ठा panfrost_mmu अणु
	काष्ठा io_pgtable_cfg pgtbl_cfg;
	काष्ठा io_pgtable_ops *pgtbl_ops;
	पूर्णांक as;
	atomic_t as_count;
	काष्ठा list_head list;
पूर्ण;

काष्ठा panfrost_file_priv अणु
	काष्ठा panfrost_device *pfdev;

	काष्ठा drm_sched_entity sched_entity[NUM_JOB_SLOTS];

	काष्ठा panfrost_mmu mmu;
	काष्ठा drm_mm mm;
	spinlock_t mm_lock;
पूर्ण;

अटल अंतरभूत काष्ठा panfrost_device *to_panfrost_device(काष्ठा drm_device *ddev)
अणु
	वापस ddev->dev_निजी;
पूर्ण

अटल अंतरभूत पूर्णांक panfrost_model_cmp(काष्ठा panfrost_device *pfdev, s32 id)
अणु
	s32 match_id = pfdev->features.id;

	अगर (match_id & 0xf000)
		match_id &= 0xf00f;
	वापस match_id - id;
पूर्ण

अटल अंतरभूत bool panfrost_model_is_bअगरrost(काष्ठा panfrost_device *pfdev)
अणु
	वापस panfrost_model_cmp(pfdev, 0x1000) >= 0;
पूर्ण

अटल अंतरभूत bool panfrost_model_eq(काष्ठा panfrost_device *pfdev, s32 id)
अणु
	वापस !panfrost_model_cmp(pfdev, id);
पूर्ण

पूर्णांक panfrost_unstable_ioctl_check(व्योम);

पूर्णांक panfrost_device_init(काष्ठा panfrost_device *pfdev);
व्योम panfrost_device_fini(काष्ठा panfrost_device *pfdev);
व्योम panfrost_device_reset(काष्ठा panfrost_device *pfdev);

पूर्णांक panfrost_device_resume(काष्ठा device *dev);
पूर्णांक panfrost_device_suspend(काष्ठा device *dev);

स्थिर अक्षर *panfrost_exception_name(काष्ठा panfrost_device *pfdev, u32 exception_code);

#पूर्ण_अगर
