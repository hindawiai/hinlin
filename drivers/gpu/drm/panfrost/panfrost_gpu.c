<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2018 Marty E. Plummer <hanetzer@starपंचांगail.com> */
/* Copyright 2019 Linaro, Ltd., Rob Herring <robh@kernel.org> */
/* Copyright 2019 Collabora ltd. */
#समावेश <linux/bitfield.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "panfrost_device.h"
#समावेश "panfrost_features.h"
#समावेश "panfrost_issues.h"
#समावेश "panfrost_gpu.h"
#समावेश "panfrost_perfcnt.h"
#समावेश "panfrost_regs.h"

अटल irqवापस_t panfrost_gpu_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा panfrost_device *pfdev = data;
	u32 state = gpu_पढ़ो(pfdev, GPU_INT_STAT);
	u32 fault_status = gpu_पढ़ो(pfdev, GPU_FAULT_STATUS);

	अगर (!state)
		वापस IRQ_NONE;

	अगर (state & GPU_IRQ_MASK_ERROR) अणु
		u64 address = (u64) gpu_पढ़ो(pfdev, GPU_FAULT_ADDRESS_HI) << 32;
		address |= gpu_पढ़ो(pfdev, GPU_FAULT_ADDRESS_LO);

		dev_warn(pfdev->dev, "GPU Fault 0x%08x (%s) at 0x%016llx\n",
			 fault_status & 0xFF, panfrost_exception_name(pfdev, fault_status),
			 address);

		अगर (state & GPU_IRQ_MULTIPLE_FAULT)
			dev_warn(pfdev->dev, "There were multiple GPU faults - some have not been reported\n");

		gpu_ग_लिखो(pfdev, GPU_INT_MASK, 0);
	पूर्ण

	अगर (state & GPU_IRQ_PERFCNT_SAMPLE_COMPLETED)
		panfrost_perfcnt_sample_करोne(pfdev);

	अगर (state & GPU_IRQ_CLEAN_CACHES_COMPLETED)
		panfrost_perfcnt_clean_cache_करोne(pfdev);

	gpu_ग_लिखो(pfdev, GPU_INT_CLEAR, state);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक panfrost_gpu_soft_reset(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक ret;
	u32 val;

	gpu_ग_लिखो(pfdev, GPU_INT_MASK, 0);
	gpu_ग_लिखो(pfdev, GPU_INT_CLEAR, GPU_IRQ_RESET_COMPLETED);
	gpu_ग_लिखो(pfdev, GPU_CMD, GPU_CMD_SOFT_RESET);

	ret = पढ़ोl_relaxed_poll_समयout(pfdev->iomem + GPU_INT_RAWSTAT,
		val, val & GPU_IRQ_RESET_COMPLETED, 100, 10000);

	अगर (ret) अणु
		dev_err(pfdev->dev, "gpu soft reset timed out\n");
		वापस ret;
	पूर्ण

	gpu_ग_लिखो(pfdev, GPU_INT_CLEAR, GPU_IRQ_MASK_ALL);
	gpu_ग_लिखो(pfdev, GPU_INT_MASK, GPU_IRQ_MASK_ALL);

	वापस 0;
पूर्ण

व्योम panfrost_gpu_amlogic_quirk(काष्ठा panfrost_device *pfdev)
अणु
	/*
	 * The Amlogic पूर्णांकegrated Mali-T820, Mali-G31 & Mali-G52 needs
	 * these unकरोcumented bits in GPU_PWR_OVERRIDE1 to be set in order
	 * to operate correctly.
	 */
	gpu_ग_लिखो(pfdev, GPU_PWR_KEY, GPU_PWR_KEY_UNLOCK);
	gpu_ग_लिखो(pfdev, GPU_PWR_OVERRIDE1, 0xfff | (0x20 << 16));
पूर्ण

अटल व्योम panfrost_gpu_init_quirks(काष्ठा panfrost_device *pfdev)
अणु
	u32 quirks = 0;

	अगर (panfrost_has_hw_issue(pfdev, HW_ISSUE_8443) ||
	    panfrost_has_hw_issue(pfdev, HW_ISSUE_11035))
		quirks |= SC_LS_PAUSEBUFFER_DISABLE;

	अगर (panfrost_has_hw_issue(pfdev, HW_ISSUE_10327))
		quirks |= SC_SDC_DISABLE_OQ_DISCARD;

	अगर (panfrost_has_hw_issue(pfdev, HW_ISSUE_10797))
		quirks |= SC_ENABLE_TEXGRD_FLAGS;

	अगर (!panfrost_has_hw_issue(pfdev, GPUCORE_1619)) अणु
		अगर (panfrost_model_cmp(pfdev, 0x750) < 0) /* T60x, T62x, T72x */
			quirks |= SC_LS_ATTR_CHECK_DISABLE;
		अन्यथा अगर (panfrost_model_cmp(pfdev, 0x880) <= 0) /* T76x, T8xx */
			quirks |= SC_LS_ALLOW_ATTR_TYPES;
	पूर्ण

	अगर (panfrost_has_hw_feature(pfdev, HW_FEATURE_TLS_HASHING))
		quirks |= SC_TLS_HASH_ENABLE;

	अगर (quirks)
		gpu_ग_लिखो(pfdev, GPU_SHADER_CONFIG, quirks);


	quirks = gpu_पढ़ो(pfdev, GPU_TILER_CONFIG);

	/* Set tiler घड़ी gate override अगर required */
	अगर (panfrost_has_hw_issue(pfdev, HW_ISSUE_T76X_3953))
		quirks |= TC_CLOCK_GATE_OVERRIDE;

	gpu_ग_लिखो(pfdev, GPU_TILER_CONFIG, quirks);


	quirks = gpu_पढ़ो(pfdev, GPU_L2_MMU_CONFIG);

	/* Limit पढ़ो & ग_लिखो ID width क्रम AXI */
	अगर (panfrost_has_hw_feature(pfdev, HW_FEATURE_3BIT_EXT_RW_L2_MMU_CONFIG))
		quirks &= ~(L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_READS |
			    L2_MMU_CONFIG_3BIT_LIMIT_EXTERNAL_WRITES);
	अन्यथा
		quirks &= ~(L2_MMU_CONFIG_LIMIT_EXTERNAL_READS |
			    L2_MMU_CONFIG_LIMIT_EXTERNAL_WRITES);

	gpu_ग_लिखो(pfdev, GPU_L2_MMU_CONFIG, quirks);

	quirks = 0;
	अगर ((panfrost_model_eq(pfdev, 0x860) || panfrost_model_eq(pfdev, 0x880)) &&
	    pfdev->features.revision >= 0x2000)
		quirks |= JM_MAX_JOB_THROTTLE_LIMIT << JM_JOB_THROTTLE_LIMIT_SHIFT;
	अन्यथा अगर (panfrost_model_eq(pfdev, 0x6000) &&
		 pfdev->features.coherency_features == COHERENCY_ACE)
		quirks |= (COHERENCY_ACE_LITE | COHERENCY_ACE) <<
			   JM_FORCE_COHERENCY_FEATURES_SHIFT;

	अगर (quirks)
		gpu_ग_लिखो(pfdev, GPU_JM_CONFIG, quirks);

	/* Here goes platक्रमm specअगरic quirks */
	अगर (pfdev->comp->venकरोr_quirk)
		pfdev->comp->venकरोr_quirk(pfdev);
पूर्ण

#घोषणा MAX_HW_REVS 6

काष्ठा panfrost_model अणु
	स्थिर अक्षर *name;
	u32 id;
	u32 id_mask;
	u64 features;
	u64 issues;
	काष्ठा अणु
		u32 revision;
		u64 issues;
	पूर्ण revs[MAX_HW_REVS];
पूर्ण;

#घोषणा GPU_MODEL(_name, _id, ...) \
अणु\
	.name = __stringअगरy(_name),				\
	.id = _id,						\
	.features = hw_features_##_name,			\
	.issues = hw_issues_##_name,				\
	.revs = अणु __VA_ARGS__ पूर्ण,				\
पूर्ण

#घोषणा GPU_REV_EXT(name, _rev, _p, _s, stat) \
अणु\
	.revision = (_rev) << 12 | (_p) << 4 | (_s),		\
	.issues = hw_issues_##name##_r##_rev##p##_p##stat,	\
पूर्ण
#घोषणा GPU_REV(name, r, p) GPU_REV_EXT(name, r, p, 0, )

अटल स्थिर काष्ठा panfrost_model gpu_models[] = अणु
	/* T60x has an oddball version */
	GPU_MODEL(t600, 0x600,
		GPU_REV_EXT(t600, 0, 0, 1, _15dev0)),
	GPU_MODEL(t620, 0x620,
		GPU_REV(t620, 0, 1), GPU_REV(t620, 1, 0)),
	GPU_MODEL(t720, 0x720),
	GPU_MODEL(t760, 0x750,
		GPU_REV(t760, 0, 0), GPU_REV(t760, 0, 1),
		GPU_REV_EXT(t760, 0, 1, 0, _50rel0),
		GPU_REV(t760, 0, 2), GPU_REV(t760, 0, 3)),
	GPU_MODEL(t820, 0x820),
	GPU_MODEL(t830, 0x830),
	GPU_MODEL(t860, 0x860),
	GPU_MODEL(t880, 0x880),

	GPU_MODEL(g71, 0x6000,
		GPU_REV_EXT(g71, 0, 0, 1, _05dev0)),
	GPU_MODEL(g72, 0x6001),
	GPU_MODEL(g51, 0x7000),
	GPU_MODEL(g76, 0x7001),
	GPU_MODEL(g52, 0x7002),
	GPU_MODEL(g31, 0x7003,
		GPU_REV(g31, 1, 0)),
पूर्ण;

अटल व्योम panfrost_gpu_init_features(काष्ठा panfrost_device *pfdev)
अणु
	u32 gpu_id, num_js, major, minor, status, rev;
	स्थिर अक्षर *name = "unknown";
	u64 hw_feat = 0;
	u64 hw_issues = hw_issues_all;
	स्थिर काष्ठा panfrost_model *model;
	पूर्णांक i;

	pfdev->features.l2_features = gpu_पढ़ो(pfdev, GPU_L2_FEATURES);
	pfdev->features.core_features = gpu_पढ़ो(pfdev, GPU_CORE_FEATURES);
	pfdev->features.tiler_features = gpu_पढ़ो(pfdev, GPU_TILER_FEATURES);
	pfdev->features.mem_features = gpu_पढ़ो(pfdev, GPU_MEM_FEATURES);
	pfdev->features.mmu_features = gpu_पढ़ो(pfdev, GPU_MMU_FEATURES);
	pfdev->features.thपढ़ो_features = gpu_पढ़ो(pfdev, GPU_THREAD_FEATURES);
	pfdev->features.max_thपढ़ोs = gpu_पढ़ो(pfdev, GPU_THREAD_MAX_THREADS);
	pfdev->features.thपढ़ो_max_workgroup_sz = gpu_पढ़ो(pfdev, GPU_THREAD_MAX_WORKGROUP_SIZE);
	pfdev->features.thपढ़ो_max_barrier_sz = gpu_पढ़ो(pfdev, GPU_THREAD_MAX_BARRIER_SIZE);
	pfdev->features.coherency_features = gpu_पढ़ो(pfdev, GPU_COHERENCY_FEATURES);
	क्रम (i = 0; i < 4; i++)
		pfdev->features.texture_features[i] = gpu_पढ़ो(pfdev, GPU_TEXTURE_FEATURES(i));

	pfdev->features.as_present = gpu_पढ़ो(pfdev, GPU_AS_PRESENT);

	pfdev->features.js_present = gpu_पढ़ो(pfdev, GPU_JS_PRESENT);
	num_js = hweight32(pfdev->features.js_present);
	क्रम (i = 0; i < num_js; i++)
		pfdev->features.js_features[i] = gpu_पढ़ो(pfdev, GPU_JS_FEATURES(i));

	pfdev->features.shader_present = gpu_पढ़ो(pfdev, GPU_SHADER_PRESENT_LO);
	pfdev->features.shader_present |= (u64)gpu_पढ़ो(pfdev, GPU_SHADER_PRESENT_HI) << 32;

	pfdev->features.tiler_present = gpu_पढ़ो(pfdev, GPU_TILER_PRESENT_LO);
	pfdev->features.tiler_present |= (u64)gpu_पढ़ो(pfdev, GPU_TILER_PRESENT_HI) << 32;

	pfdev->features.l2_present = gpu_पढ़ो(pfdev, GPU_L2_PRESENT_LO);
	pfdev->features.l2_present |= (u64)gpu_पढ़ो(pfdev, GPU_L2_PRESENT_HI) << 32;
	pfdev->features.nr_core_groups = hweight64(pfdev->features.l2_present);

	pfdev->features.stack_present = gpu_पढ़ो(pfdev, GPU_STACK_PRESENT_LO);
	pfdev->features.stack_present |= (u64)gpu_पढ़ो(pfdev, GPU_STACK_PRESENT_HI) << 32;

	pfdev->features.thपढ़ो_tls_alloc = gpu_पढ़ो(pfdev, GPU_THREAD_TLS_ALLOC);

	gpu_id = gpu_पढ़ो(pfdev, GPU_ID);
	pfdev->features.revision = gpu_id & 0xffff;
	pfdev->features.id = gpu_id >> 16;

	/* The T60x has an oddball ID value. Fix it up to the standard Midgard
	 * क्रमmat so we (and userspace) करोn't have to special हाल it.
	 */
	अगर (pfdev->features.id == 0x6956)
		pfdev->features.id = 0x0600;

	major = (pfdev->features.revision >> 12) & 0xf;
	minor = (pfdev->features.revision >> 4) & 0xff;
	status = pfdev->features.revision & 0xf;
	rev = pfdev->features.revision;

	gpu_id = pfdev->features.id;

	क्रम (model = gpu_models; model->name; model++) अणु
		पूर्णांक best = -1;

		अगर (!panfrost_model_eq(pfdev, model->id))
			जारी;

		name = model->name;
		hw_feat = model->features;
		hw_issues |= model->issues;
		क्रम (i = 0; i < MAX_HW_REVS; i++) अणु
			अगर (model->revs[i].revision == rev) अणु
				best = i;
				अवरोध;
			पूर्ण अन्यथा अगर (model->revs[i].revision == (rev & ~0xf))
				best = i;
		पूर्ण

		अगर (best >= 0)
			hw_issues |= model->revs[best].issues;

		अवरोध;
	पूर्ण

	biपंचांगap_from_u64(pfdev->features.hw_features, hw_feat);
	biपंचांगap_from_u64(pfdev->features.hw_issues, hw_issues);

	dev_info(pfdev->dev, "mali-%s id 0x%x major 0x%x minor 0x%x status 0x%x",
		 name, gpu_id, major, minor, status);
	dev_info(pfdev->dev, "features: %64pb, issues: %64pb",
		 pfdev->features.hw_features,
		 pfdev->features.hw_issues);

	dev_info(pfdev->dev, "Features: L2:0x%08x Shader:0x%08x Tiler:0x%08x Mem:0x%0x MMU:0x%08x AS:0x%x JS:0x%x",
		 pfdev->features.l2_features,
		 pfdev->features.core_features,
		 pfdev->features.tiler_features,
		 pfdev->features.mem_features,
		 pfdev->features.mmu_features,
		 pfdev->features.as_present,
		 pfdev->features.js_present);

	dev_info(pfdev->dev, "shader_present=0x%0llx l2_present=0x%0llx",
		 pfdev->features.shader_present, pfdev->features.l2_present);
पूर्ण

व्योम panfrost_gpu_घातer_on(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक ret;
	u32 val;

	panfrost_gpu_init_quirks(pfdev);

	/* Just turn on everything क्रम now */
	gpu_ग_लिखो(pfdev, L2_PWRON_LO, pfdev->features.l2_present);
	ret = पढ़ोl_relaxed_poll_समयout(pfdev->iomem + L2_READY_LO,
		val, val == pfdev->features.l2_present, 100, 20000);
	अगर (ret)
		dev_err(pfdev->dev, "error powering up gpu L2");

	gpu_ग_लिखो(pfdev, SHADER_PWRON_LO, pfdev->features.shader_present);
	ret = पढ़ोl_relaxed_poll_समयout(pfdev->iomem + SHADER_READY_LO,
		val, val == pfdev->features.shader_present, 100, 20000);
	अगर (ret)
		dev_err(pfdev->dev, "error powering up gpu shader");

	gpu_ग_लिखो(pfdev, TILER_PWRON_LO, pfdev->features.tiler_present);
	ret = पढ़ोl_relaxed_poll_समयout(pfdev->iomem + TILER_READY_LO,
		val, val == pfdev->features.tiler_present, 100, 1000);
	अगर (ret)
		dev_err(pfdev->dev, "error powering up gpu tiler");
पूर्ण

व्योम panfrost_gpu_घातer_off(काष्ठा panfrost_device *pfdev)
अणु
	gpu_ग_लिखो(pfdev, TILER_PWROFF_LO, 0);
	gpu_ग_लिखो(pfdev, SHADER_PWROFF_LO, 0);
	gpu_ग_लिखो(pfdev, L2_PWROFF_LO, 0);
पूर्ण

पूर्णांक panfrost_gpu_init(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक err, irq;

	err = panfrost_gpu_soft_reset(pfdev);
	अगर (err)
		वापस err;

	panfrost_gpu_init_features(pfdev);

	dma_set_mask_and_coherent(pfdev->dev,
		DMA_BIT_MASK(FIELD_GET(0xff00, pfdev->features.mmu_features)));
	dma_set_max_seg_size(pfdev->dev, अच_पूर्णांक_उच्च);

	irq = platक्रमm_get_irq_byname(to_platक्रमm_device(pfdev->dev), "gpu");
	अगर (irq <= 0)
		वापस -ENODEV;

	err = devm_request_irq(pfdev->dev, irq, panfrost_gpu_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME "-gpu", pfdev);
	अगर (err) अणु
		dev_err(pfdev->dev, "failed to request gpu irq");
		वापस err;
	पूर्ण

	panfrost_gpu_घातer_on(pfdev);

	वापस 0;
पूर्ण

व्योम panfrost_gpu_fini(काष्ठा panfrost_device *pfdev)
अणु
	panfrost_gpu_घातer_off(pfdev);
पूर्ण

u32 panfrost_gpu_get_latest_flush_id(काष्ठा panfrost_device *pfdev)
अणु
	u32 flush_id;

	अगर (panfrost_has_hw_feature(pfdev, HW_FEATURE_FLUSH_REDUCTION)) अणु
		/* Flush reduction only makes sense when the GPU is kept घातered on between jobs */
		अगर (pm_runसमय_get_अगर_in_use(pfdev->dev)) अणु
			flush_id = gpu_पढ़ो(pfdev, GPU_LATEST_FLUSH_ID);
			pm_runसमय_put(pfdev->dev);
			वापस flush_id;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
