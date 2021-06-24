<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश "amdgpu.h"
#समावेश "amdgpu_gfx.h"
#समावेश "amdgpu_rlc.h"
#समावेश "amdgpu_ras.h"

/* delay 0.1 second to enable gfx off feature */
#घोषणा GFX_OFF_DELAY_ENABLE         msecs_to_jअगरfies(100)

/*
 * GPU GFX IP block helpers function.
 */

पूर्णांक amdgpu_gfx_mec_queue_to_bit(काष्ठा amdgpu_device *adev, पूर्णांक mec,
				पूर्णांक pipe, पूर्णांक queue)
अणु
	पूर्णांक bit = 0;

	bit += mec * adev->gfx.mec.num_pipe_per_mec
		* adev->gfx.mec.num_queue_per_pipe;
	bit += pipe * adev->gfx.mec.num_queue_per_pipe;
	bit += queue;

	वापस bit;
पूर्ण

व्योम amdgpu_queue_mask_bit_to_mec_queue(काष्ठा amdgpu_device *adev, पूर्णांक bit,
				 पूर्णांक *mec, पूर्णांक *pipe, पूर्णांक *queue)
अणु
	*queue = bit % adev->gfx.mec.num_queue_per_pipe;
	*pipe = (bit / adev->gfx.mec.num_queue_per_pipe)
		% adev->gfx.mec.num_pipe_per_mec;
	*mec = (bit / adev->gfx.mec.num_queue_per_pipe)
	       / adev->gfx.mec.num_pipe_per_mec;

पूर्ण

bool amdgpu_gfx_is_mec_queue_enabled(काष्ठा amdgpu_device *adev,
				     पूर्णांक mec, पूर्णांक pipe, पूर्णांक queue)
अणु
	वापस test_bit(amdgpu_gfx_mec_queue_to_bit(adev, mec, pipe, queue),
			adev->gfx.mec.queue_biपंचांगap);
पूर्ण

पूर्णांक amdgpu_gfx_me_queue_to_bit(काष्ठा amdgpu_device *adev,
			       पूर्णांक me, पूर्णांक pipe, पूर्णांक queue)
अणु
	पूर्णांक bit = 0;

	bit += me * adev->gfx.me.num_pipe_per_me
		* adev->gfx.me.num_queue_per_pipe;
	bit += pipe * adev->gfx.me.num_queue_per_pipe;
	bit += queue;

	वापस bit;
पूर्ण

व्योम amdgpu_gfx_bit_to_me_queue(काष्ठा amdgpu_device *adev, पूर्णांक bit,
				पूर्णांक *me, पूर्णांक *pipe, पूर्णांक *queue)
अणु
	*queue = bit % adev->gfx.me.num_queue_per_pipe;
	*pipe = (bit / adev->gfx.me.num_queue_per_pipe)
		% adev->gfx.me.num_pipe_per_me;
	*me = (bit / adev->gfx.me.num_queue_per_pipe)
		/ adev->gfx.me.num_pipe_per_me;
पूर्ण

bool amdgpu_gfx_is_me_queue_enabled(काष्ठा amdgpu_device *adev,
				    पूर्णांक me, पूर्णांक pipe, पूर्णांक queue)
अणु
	वापस test_bit(amdgpu_gfx_me_queue_to_bit(adev, me, pipe, queue),
			adev->gfx.me.queue_biपंचांगap);
पूर्ण

/**
 * amdgpu_gfx_scratch_get - Allocate a scratch रेजिस्टर
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @reg: scratch रेजिस्टर mmio offset
 *
 * Allocate a CP scratch रेजिस्टर क्रम use by the driver (all asics).
 * Returns 0 on success or -EINVAL on failure.
 */
पूर्णांक amdgpu_gfx_scratch_get(काष्ठा amdgpu_device *adev, uपूर्णांक32_t *reg)
अणु
	पूर्णांक i;

	i = ffs(adev->gfx.scratch.मुक्त_mask);
	अगर (i != 0 && i <= adev->gfx.scratch.num_reg) अणु
		i--;
		adev->gfx.scratch.मुक्त_mask &= ~(1u << i);
		*reg = adev->gfx.scratch.reg_base + i;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * amdgpu_gfx_scratch_मुक्त - Free a scratch रेजिस्टर
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @reg: scratch रेजिस्टर mmio offset
 *
 * Free a CP scratch रेजिस्टर allocated क्रम use by the driver (all asics)
 */
व्योम amdgpu_gfx_scratch_मुक्त(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg)
अणु
	adev->gfx.scratch.मुक्त_mask |= 1u << (reg - adev->gfx.scratch.reg_base);
पूर्ण

/**
 * amdgpu_gfx_parse_disable_cu - Parse the disable_cu module parameter
 *
 * @mask: array in which the per-shader array disable masks will be stored
 * @max_se: number of SEs
 * @max_sh: number of SHs
 *
 * The biपंचांगask of CUs to be disabled in the shader array determined by se and
 * sh is stored in mask[se * max_sh + sh].
 */
व्योम amdgpu_gfx_parse_disable_cu(अचिन्हित *mask, अचिन्हित max_se, अचिन्हित max_sh)
अणु
	अचिन्हित se, sh, cu;
	स्थिर अक्षर *p;

	स_रखो(mask, 0, माप(*mask) * max_se * max_sh);

	अगर (!amdgpu_disable_cu || !*amdgpu_disable_cu)
		वापस;

	p = amdgpu_disable_cu;
	क्रम (;;) अणु
		अक्षर *next;
		पूर्णांक ret = माला_पूछो(p, "%u.%u.%u", &se, &sh, &cu);
		अगर (ret < 3) अणु
			DRM_ERROR("amdgpu: could not parse disable_cu\n");
			वापस;
		पूर्ण

		अगर (se < max_se && sh < max_sh && cu < 16) अणु
			DRM_INFO("amdgpu: disabling CU %u.%u.%u\n", se, sh, cu);
			mask[se * max_sh + sh] |= 1u << cu;
		पूर्ण अन्यथा अणु
			DRM_ERROR("amdgpu: disable_cu %u.%u.%u is out of range\n",
				  se, sh, cu);
		पूर्ण

		next = म_अक्षर(p, ',');
		अगर (!next)
			अवरोध;
		p = next + 1;
	पूर्ण
पूर्ण

अटल bool amdgpu_gfx_is_multipipe_capable(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_compute_multipipe != -1) अणु
		DRM_INFO("amdgpu: forcing compute pipe policy %d\n",
			 amdgpu_compute_multipipe);
		वापस amdgpu_compute_multipipe == 1;
	पूर्ण

	/* FIXME: spपढ़ोing the queues across pipes causes perf regressions
	 * on POLARIS11 compute workloads */
	अगर (adev->asic_type == CHIP_POLARIS11)
		वापस false;

	वापस adev->gfx.mec.num_mec > 1;
पूर्ण

bool amdgpu_gfx_is_high_priority_compute_queue(काष्ठा amdgpu_device *adev,
					       काष्ठा amdgpu_ring *ring)
अणु
	/* Policy: use 1st queue as high priority compute queue अगर we
	 * have more than one compute queue.
	 */
	अगर (adev->gfx.num_compute_rings > 1 &&
	    ring == &adev->gfx.compute_ring[0])
		वापस true;

	वापस false;
पूर्ण

व्योम amdgpu_gfx_compute_queue_acquire(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, queue, pipe;
	bool multipipe_policy = amdgpu_gfx_is_multipipe_capable(adev);
	पूर्णांक max_queues_per_mec = min(adev->gfx.mec.num_pipe_per_mec *
				     adev->gfx.mec.num_queue_per_pipe,
				     adev->gfx.num_compute_rings);

	अगर (multipipe_policy) अणु
		/* policy: make queues evenly cross all pipes on MEC1 only */
		क्रम (i = 0; i < max_queues_per_mec; i++) अणु
			pipe = i % adev->gfx.mec.num_pipe_per_mec;
			queue = (i / adev->gfx.mec.num_pipe_per_mec) %
				adev->gfx.mec.num_queue_per_pipe;

			set_bit(pipe * adev->gfx.mec.num_queue_per_pipe + queue,
					adev->gfx.mec.queue_biपंचांगap);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* policy: amdgpu owns all queues in the given pipe */
		क्रम (i = 0; i < max_queues_per_mec; ++i)
			set_bit(i, adev->gfx.mec.queue_biपंचांगap);
	पूर्ण

	dev_dbg(adev->dev, "mec queue bitmap weight=%d\n", biपंचांगap_weight(adev->gfx.mec.queue_biपंचांगap, AMDGPU_MAX_COMPUTE_QUEUES));
पूर्ण

व्योम amdgpu_gfx_graphics_queue_acquire(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, queue, me;

	क्रम (i = 0; i < AMDGPU_MAX_GFX_QUEUES; ++i) अणु
		queue = i % adev->gfx.me.num_queue_per_pipe;
		me = (i / adev->gfx.me.num_queue_per_pipe)
		      / adev->gfx.me.num_pipe_per_me;

		अगर (me >= adev->gfx.me.num_me)
			अवरोध;
		/* policy: amdgpu owns the first queue per pipe at this stage
		 * will extend to mulitple queues per pipe later */
		अगर (me == 0 && queue < 1)
			set_bit(i, adev->gfx.me.queue_biपंचांगap);
	पूर्ण

	/* update the number of active graphics rings */
	adev->gfx.num_gfx_rings =
		biपंचांगap_weight(adev->gfx.me.queue_biपंचांगap, AMDGPU_MAX_GFX_QUEUES);
पूर्ण

अटल पूर्णांक amdgpu_gfx_kiq_acquire(काष्ठा amdgpu_device *adev,
				  काष्ठा amdgpu_ring *ring)
अणु
	पूर्णांक queue_bit;
	पूर्णांक mec, pipe, queue;

	queue_bit = adev->gfx.mec.num_mec
		    * adev->gfx.mec.num_pipe_per_mec
		    * adev->gfx.mec.num_queue_per_pipe;

	जबतक (queue_bit-- >= 0) अणु
		अगर (test_bit(queue_bit, adev->gfx.mec.queue_biपंचांगap))
			जारी;

		amdgpu_queue_mask_bit_to_mec_queue(adev, queue_bit, &mec, &pipe, &queue);

		/*
		 * 1. Using pipes 2/3 from MEC 2 seems cause problems.
		 * 2. It must use queue id 0, because CGPG_IDLE/SAVE/LOAD/RUN
		 * only can be issued on queue 0.
		 */
		अगर ((mec == 1 && pipe > 1) || queue != 0)
			जारी;

		ring->me = mec + 1;
		ring->pipe = pipe;
		ring->queue = queue;

		वापस 0;
	पूर्ण

	dev_err(adev->dev, "Failed to find a queue for KIQ\n");
	वापस -EINVAL;
पूर्ण

पूर्णांक amdgpu_gfx_kiq_init_ring(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ring *ring,
			     काष्ठा amdgpu_irq_src *irq)
अणु
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;
	पूर्णांक r = 0;

	spin_lock_init(&kiq->ring_lock);

	ring->adev = शून्य;
	ring->ring_obj = शून्य;
	ring->use_करोorbell = true;
	ring->करोorbell_index = adev->करोorbell_index.kiq;

	r = amdgpu_gfx_kiq_acquire(adev, ring);
	अगर (r)
		वापस r;

	ring->eop_gpu_addr = kiq->eop_gpu_addr;
	ring->no_scheduler = true;
	प्र_लिखो(ring->name, "kiq_%d.%d.%d", ring->me, ring->pipe, ring->queue);
	r = amdgpu_ring_init(adev, ring, 1024, irq, AMDGPU_CP_KIQ_IRQ_DRIVER0,
			     AMDGPU_RING_PRIO_DEFAULT, शून्य);
	अगर (r)
		dev_warn(adev->dev, "(%d) failed to init kiq ring\n", r);

	वापस r;
पूर्ण

व्योम amdgpu_gfx_kiq_मुक्त_ring(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_fini(ring);
पूर्ण

व्योम amdgpu_gfx_kiq_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;

	amdgpu_bo_मुक्त_kernel(&kiq->eop_obj, &kiq->eop_gpu_addr, शून्य);
पूर्ण

पूर्णांक amdgpu_gfx_kiq_init(काष्ठा amdgpu_device *adev,
			अचिन्हित hpd_size)
अणु
	पूर्णांक r;
	u32 *hpd;
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;

	r = amdgpu_bo_create_kernel(adev, hpd_size, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_GTT, &kiq->eop_obj,
				    &kiq->eop_gpu_addr, (व्योम **)&hpd);
	अगर (r) अणु
		dev_warn(adev->dev, "failed to create KIQ bo (%d).\n", r);
		वापस r;
	पूर्ण

	स_रखो(hpd, 0, hpd_size);

	r = amdgpu_bo_reserve(kiq->eop_obj, true);
	अगर (unlikely(r != 0))
		dev_warn(adev->dev, "(%d) reserve kiq eop bo failed\n", r);
	amdgpu_bo_kunmap(kiq->eop_obj);
	amdgpu_bo_unreserve(kiq->eop_obj);

	वापस 0;
पूर्ण

/* create MQD क्रम each compute/gfx queue */
पूर्णांक amdgpu_gfx_mqd_sw_init(काष्ठा amdgpu_device *adev,
			   अचिन्हित mqd_size)
अणु
	काष्ठा amdgpu_ring *ring = शून्य;
	पूर्णांक r, i;

	/* create MQD क्रम KIQ */
	ring = &adev->gfx.kiq.ring;
	अगर (!ring->mqd_obj) अणु
		/* originaly the KIQ MQD is put in GTT करोमुख्य, but क्रम SRIOV VRAM करोमुख्य is a must
		 * otherwise hypervisor trigger SAVE_VF fail after driver unloaded which mean MQD
		 * deallocated and gart_unbind, to strict भागerage we decide to use VRAM करोमुख्य क्रम
		 * KIQ MQD no matter SRIOV or Bare-metal
		 */
		r = amdgpu_bo_create_kernel(adev, mqd_size, PAGE_SIZE,
					    AMDGPU_GEM_DOMAIN_VRAM, &ring->mqd_obj,
					    &ring->mqd_gpu_addr, &ring->mqd_ptr);
		अगर (r) अणु
			dev_warn(adev->dev, "failed to create ring mqd ob (%d)", r);
			वापस r;
		पूर्ण

		/* prepare MQD backup */
		adev->gfx.mec.mqd_backup[AMDGPU_MAX_COMPUTE_RINGS] = kदो_स्मृति(mqd_size, GFP_KERNEL);
		अगर (!adev->gfx.mec.mqd_backup[AMDGPU_MAX_COMPUTE_RINGS])
				dev_warn(adev->dev, "no memory to create MQD backup for ring %s\n", ring->name);
	पूर्ण

	अगर (adev->asic_type >= CHIP_NAVI10 && amdgpu_async_gfx_ring) अणु
		/* create MQD क्रम each KGQ */
		क्रम (i = 0; i < adev->gfx.num_gfx_rings; i++) अणु
			ring = &adev->gfx.gfx_ring[i];
			अगर (!ring->mqd_obj) अणु
				r = amdgpu_bo_create_kernel(adev, mqd_size, PAGE_SIZE,
							    AMDGPU_GEM_DOMAIN_GTT, &ring->mqd_obj,
							    &ring->mqd_gpu_addr, &ring->mqd_ptr);
				अगर (r) अणु
					dev_warn(adev->dev, "failed to create ring mqd bo (%d)", r);
					वापस r;
				पूर्ण

				/* prepare MQD backup */
				adev->gfx.me.mqd_backup[i] = kदो_स्मृति(mqd_size, GFP_KERNEL);
				अगर (!adev->gfx.me.mqd_backup[i])
					dev_warn(adev->dev, "no memory to create MQD backup for ring %s\n", ring->name);
			पूर्ण
		पूर्ण
	पूर्ण

	/* create MQD क्रम each KCQ */
	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
		ring = &adev->gfx.compute_ring[i];
		अगर (!ring->mqd_obj) अणु
			r = amdgpu_bo_create_kernel(adev, mqd_size, PAGE_SIZE,
						    AMDGPU_GEM_DOMAIN_GTT, &ring->mqd_obj,
						    &ring->mqd_gpu_addr, &ring->mqd_ptr);
			अगर (r) अणु
				dev_warn(adev->dev, "failed to create ring mqd bo (%d)", r);
				वापस r;
			पूर्ण

			/* prepare MQD backup */
			adev->gfx.mec.mqd_backup[i] = kदो_स्मृति(mqd_size, GFP_KERNEL);
			अगर (!adev->gfx.mec.mqd_backup[i])
				dev_warn(adev->dev, "no memory to create MQD backup for ring %s\n", ring->name);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम amdgpu_gfx_mqd_sw_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = शून्य;
	पूर्णांक i;

	अगर (adev->asic_type >= CHIP_NAVI10 && amdgpu_async_gfx_ring) अणु
		क्रम (i = 0; i < adev->gfx.num_gfx_rings; i++) अणु
			ring = &adev->gfx.gfx_ring[i];
			kमुक्त(adev->gfx.me.mqd_backup[i]);
			amdgpu_bo_मुक्त_kernel(&ring->mqd_obj,
					      &ring->mqd_gpu_addr,
					      &ring->mqd_ptr);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++) अणु
		ring = &adev->gfx.compute_ring[i];
		kमुक्त(adev->gfx.mec.mqd_backup[i]);
		amdgpu_bo_मुक्त_kernel(&ring->mqd_obj,
				      &ring->mqd_gpu_addr,
				      &ring->mqd_ptr);
	पूर्ण

	ring = &adev->gfx.kiq.ring;
	kमुक्त(adev->gfx.mec.mqd_backup[AMDGPU_MAX_COMPUTE_RINGS]);
	amdgpu_bo_मुक्त_kernel(&ring->mqd_obj,
			      &ring->mqd_gpu_addr,
			      &ring->mqd_ptr);
पूर्ण

पूर्णांक amdgpu_gfx_disable_kcq(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;
	काष्ठा amdgpu_ring *kiq_ring = &kiq->ring;
	पूर्णांक i, r;

	अगर (!kiq->pmf || !kiq->pmf->kiq_unmap_queues)
		वापस -EINVAL;

	spin_lock(&adev->gfx.kiq.ring_lock);
	अगर (amdgpu_ring_alloc(kiq_ring, kiq->pmf->unmap_queues_size *
					adev->gfx.num_compute_rings)) अणु
		spin_unlock(&adev->gfx.kiq.ring_lock);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++)
		kiq->pmf->kiq_unmap_queues(kiq_ring, &adev->gfx.compute_ring[i],
					   RESET_QUEUES, 0, 0);
	r = amdgpu_ring_test_helper(kiq_ring);
	spin_unlock(&adev->gfx.kiq.ring_lock);

	वापस r;
पूर्ण

पूर्णांक amdgpu_queue_mask_bit_to_set_resource_bit(काष्ठा amdgpu_device *adev,
					पूर्णांक queue_bit)
अणु
	पूर्णांक mec, pipe, queue;
	पूर्णांक set_resource_bit = 0;

	amdgpu_queue_mask_bit_to_mec_queue(adev, queue_bit, &mec, &pipe, &queue);

	set_resource_bit = mec * 4 * 8 + pipe * 8 + queue;

	वापस set_resource_bit;
पूर्ण

पूर्णांक amdgpu_gfx_enable_kcq(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;
	काष्ठा amdgpu_ring *kiq_ring = &adev->gfx.kiq.ring;
	uपूर्णांक64_t queue_mask = 0;
	पूर्णांक r, i;

	अगर (!kiq->pmf || !kiq->pmf->kiq_map_queues || !kiq->pmf->kiq_set_resources)
		वापस -EINVAL;

	क्रम (i = 0; i < AMDGPU_MAX_COMPUTE_QUEUES; ++i) अणु
		अगर (!test_bit(i, adev->gfx.mec.queue_biपंचांगap))
			जारी;

		/* This situation may be hit in the future अगर a new HW
		 * generation exposes more than 64 queues. If so, the
		 * definition of queue_mask needs updating */
		अगर (WARN_ON(i > (माप(queue_mask)*8))) अणु
			DRM_ERROR("Invalid KCQ enabled: %d\n", i);
			अवरोध;
		पूर्ण

		queue_mask |= (1ull << amdgpu_queue_mask_bit_to_set_resource_bit(adev, i));
	पूर्ण

	DRM_INFO("kiq ring mec %d pipe %d q %d\n", kiq_ring->me, kiq_ring->pipe,
							kiq_ring->queue);
	spin_lock(&adev->gfx.kiq.ring_lock);
	r = amdgpu_ring_alloc(kiq_ring, kiq->pmf->map_queues_size *
					adev->gfx.num_compute_rings +
					kiq->pmf->set_resources_size);
	अगर (r) अणु
		DRM_ERROR("Failed to lock KIQ (%d).\n", r);
		spin_unlock(&adev->gfx.kiq.ring_lock);
		वापस r;
	पूर्ण

	kiq->pmf->kiq_set_resources(kiq_ring, queue_mask);
	क्रम (i = 0; i < adev->gfx.num_compute_rings; i++)
		kiq->pmf->kiq_map_queues(kiq_ring, &adev->gfx.compute_ring[i]);

	r = amdgpu_ring_test_helper(kiq_ring);
	spin_unlock(&adev->gfx.kiq.ring_lock);
	अगर (r)
		DRM_ERROR("KCQ enable failed\n");

	वापस r;
पूर्ण

/* amdgpu_gfx_off_ctrl - Handle gfx off feature enable/disable
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @bool enable true: enable gfx off feature, false: disable gfx off feature
 *
 * 1. gfx off feature will be enabled by gfx ip after gfx cg gp enabled.
 * 2. other client can send request to disable gfx off feature, the request should be honored.
 * 3. other client can cancel their request of disable gfx off feature
 * 4. other client should not send request to enable gfx off feature beक्रमe disable gfx off feature.
 */

व्योम amdgpu_gfx_off_ctrl(काष्ठा amdgpu_device *adev, bool enable)
अणु
	अगर (!(adev->pm.pp_feature & PP_GFXOFF_MASK))
		वापस;

	mutex_lock(&adev->gfx.gfx_off_mutex);

	अगर (!enable)
		adev->gfx.gfx_off_req_count++;
	अन्यथा अगर (adev->gfx.gfx_off_req_count > 0)
		adev->gfx.gfx_off_req_count--;

	अगर (enable && !adev->gfx.gfx_off_state && !adev->gfx.gfx_off_req_count) अणु
		schedule_delayed_work(&adev->gfx.gfx_off_delay_work, GFX_OFF_DELAY_ENABLE);
	पूर्ण अन्यथा अगर (!enable && adev->gfx.gfx_off_state) अणु
		अगर (!amdgpu_dpm_set_घातergating_by_smu(adev, AMD_IP_BLOCK_TYPE_GFX, false)) अणु
			adev->gfx.gfx_off_state = false;

			अगर (adev->gfx.funcs->init_spm_golden) अणु
				dev_dbg(adev->dev, "GFXOFF is disabled, re-init SPM golden settings\n");
				amdgpu_gfx_init_spm_golden(adev);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&adev->gfx.gfx_off_mutex);
पूर्ण

पूर्णांक amdgpu_get_gfx_off_status(काष्ठा amdgpu_device *adev, uपूर्णांक32_t *value)
अणु

	पूर्णांक r = 0;

	mutex_lock(&adev->gfx.gfx_off_mutex);

	r = smu_get_status_gfxoff(adev, value);

	mutex_unlock(&adev->gfx.gfx_off_mutex);

	वापस r;
पूर्ण

पूर्णांक amdgpu_gfx_ras_late_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	काष्ठा ras_fs_अगर fs_info = अणु
		.sysfs_name = "gfx_err_count",
	पूर्ण;
	काष्ठा ras_ih_अगर ih_info = अणु
		.cb = amdgpu_gfx_process_ras_data_cb,
	पूर्ण;
	काष्ठा ras_query_अगर info = अणु 0 पूर्ण;

	अगर (!adev->gfx.ras_अगर) अणु
		adev->gfx.ras_अगर = kदो_स्मृति(माप(काष्ठा ras_common_अगर), GFP_KERNEL);
		अगर (!adev->gfx.ras_अगर)
			वापस -ENOMEM;
		adev->gfx.ras_अगर->block = AMDGPU_RAS_BLOCK__GFX;
		adev->gfx.ras_अगर->type = AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE;
		adev->gfx.ras_अगर->sub_block_index = 0;
		म_नकल(adev->gfx.ras_अगर->name, "gfx");
	पूर्ण
	fs_info.head = ih_info.head = *adev->gfx.ras_अगर;
	r = amdgpu_ras_late_init(adev, adev->gfx.ras_अगर,
				 &fs_info, &ih_info);
	अगर (r)
		जाओ मुक्त;

	अगर (amdgpu_ras_is_supported(adev, adev->gfx.ras_अगर->block)) अणु
		अगर (adev->gmc.xgmi.connected_to_cpu) अणु
			info.head = *adev->gfx.ras_अगर;
			amdgpu_ras_query_error_status(adev, &info);
		पूर्ण अन्यथा अणु
			amdgpu_ras_reset_error_status(adev, AMDGPU_RAS_BLOCK__GFX);
		पूर्ण

		r = amdgpu_irq_get(adev, &adev->gfx.cp_ecc_error_irq, 0);
		अगर (r)
			जाओ late_fini;
	पूर्ण अन्यथा अणु
		/* मुक्त gfx ras_अगर अगर ras is not supported */
		r = 0;
		जाओ मुक्त;
	पूर्ण

	वापस 0;
late_fini:
	amdgpu_ras_late_fini(adev, adev->gfx.ras_अगर, &ih_info);
मुक्त:
	kमुक्त(adev->gfx.ras_अगर);
	adev->gfx.ras_अगर = शून्य;
	वापस r;
पूर्ण

व्योम amdgpu_gfx_ras_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__GFX) &&
			adev->gfx.ras_अगर) अणु
		काष्ठा ras_common_अगर *ras_अगर = adev->gfx.ras_अगर;
		काष्ठा ras_ih_अगर ih_info = अणु
			.head = *ras_अगर,
			.cb = amdgpu_gfx_process_ras_data_cb,
		पूर्ण;

		amdgpu_ras_late_fini(adev, ras_अगर, &ih_info);
		kमुक्त(ras_अगर);
	पूर्ण
पूर्ण

पूर्णांक amdgpu_gfx_process_ras_data_cb(काष्ठा amdgpu_device *adev,
		व्योम *err_data,
		काष्ठा amdgpu_iv_entry *entry)
अणु
	/* TODO ue will trigger an पूर्णांकerrupt.
	 *
	 * When ै Full RASै  is enabled, the per-IP पूर्णांकerrupt sources should
	 * be disabled and the driver should only look क्रम the aggregated
	 * पूर्णांकerrupt via sync flood
	 */
	अगर (!amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__GFX)) अणु
		kgd2kfd_set_sram_ecc_flag(adev->kfd.dev);
		अगर (adev->gfx.ras_funcs &&
		    adev->gfx.ras_funcs->query_ras_error_count)
			adev->gfx.ras_funcs->query_ras_error_count(adev, err_data);
		amdgpu_ras_reset_gpu(adev);
	पूर्ण
	वापस AMDGPU_RAS_SUCCESS;
पूर्ण

पूर्णांक amdgpu_gfx_cp_ecc_error_irq(काष्ठा amdgpu_device *adev,
				  काष्ठा amdgpu_irq_src *source,
				  काष्ठा amdgpu_iv_entry *entry)
अणु
	काष्ठा ras_common_अगर *ras_अगर = adev->gfx.ras_अगर;
	काष्ठा ras_dispatch_अगर ih_data = अणु
		.entry = entry,
	पूर्ण;

	अगर (!ras_अगर)
		वापस 0;

	ih_data.head = *ras_अगर;

	DRM_ERROR("CP ECC ERROR IRQ\n");
	amdgpu_ras_पूर्णांकerrupt_dispatch(adev, &ih_data);
	वापस 0;
पूर्ण

uपूर्णांक32_t amdgpu_kiq_rreg(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg)
अणु
	चिन्हित दीर्घ r, cnt = 0;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t seq, reg_val_offs = 0, value = 0;
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;
	काष्ठा amdgpu_ring *ring = &kiq->ring;

	अगर (amdgpu_device_skip_hw_access(adev))
		वापस 0;

	BUG_ON(!ring->funcs->emit_rreg);

	spin_lock_irqsave(&kiq->ring_lock, flags);
	अगर (amdgpu_device_wb_get(adev, &reg_val_offs)) अणु
		pr_err("critical bug! too many kiq readers\n");
		जाओ failed_unlock;
	पूर्ण
	amdgpu_ring_alloc(ring, 32);
	amdgpu_ring_emit_rreg(ring, reg, reg_val_offs);
	r = amdgpu_fence_emit_polling(ring, &seq, MAX_KIQ_REG_WAIT);
	अगर (r)
		जाओ failed_unकरो;

	amdgpu_ring_commit(ring);
	spin_unlock_irqrestore(&kiq->ring_lock, flags);

	r = amdgpu_fence_रुको_polling(ring, seq, MAX_KIQ_REG_WAIT);

	/* करोn't रुको anymore क्रम gpu reset हाल because this way may
	 * block gpu_recover() routine क्रमever, e.g. this virt_kiq_rreg
	 * is triggered in TTM and tपंचांग_bo_lock_delayed_workqueue() will
	 * never वापस अगर we keep रुकोing in virt_kiq_rreg, which cause
	 * gpu_recover() hang there.
	 *
	 * also करोn't रुको anymore क्रम IRQ context
	 * */
	अगर (r < 1 && (amdgpu_in_reset(adev) || in_पूर्णांकerrupt()))
		जाओ failed_kiq_पढ़ो;

	might_sleep();
	जबतक (r < 1 && cnt++ < MAX_KIQ_REG_TRY) अणु
		msleep(MAX_KIQ_REG_BAILOUT_INTERVAL);
		r = amdgpu_fence_रुको_polling(ring, seq, MAX_KIQ_REG_WAIT);
	पूर्ण

	अगर (cnt > MAX_KIQ_REG_TRY)
		जाओ failed_kiq_पढ़ो;

	mb();
	value = adev->wb.wb[reg_val_offs];
	amdgpu_device_wb_मुक्त(adev, reg_val_offs);
	वापस value;

failed_unकरो:
	amdgpu_ring_unकरो(ring);
failed_unlock:
	spin_unlock_irqrestore(&kiq->ring_lock, flags);
failed_kiq_पढ़ो:
	अगर (reg_val_offs)
		amdgpu_device_wb_मुक्त(adev, reg_val_offs);
	dev_err(adev->dev, "failed to read reg:%x\n", reg);
	वापस ~0;
पूर्ण

व्योम amdgpu_kiq_wreg(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg, uपूर्णांक32_t v)
अणु
	चिन्हित दीर्घ r, cnt = 0;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t seq;
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;
	काष्ठा amdgpu_ring *ring = &kiq->ring;

	BUG_ON(!ring->funcs->emit_wreg);

	अगर (amdgpu_device_skip_hw_access(adev))
		वापस;

	spin_lock_irqsave(&kiq->ring_lock, flags);
	amdgpu_ring_alloc(ring, 32);
	amdgpu_ring_emit_wreg(ring, reg, v);
	r = amdgpu_fence_emit_polling(ring, &seq, MAX_KIQ_REG_WAIT);
	अगर (r)
		जाओ failed_unकरो;

	amdgpu_ring_commit(ring);
	spin_unlock_irqrestore(&kiq->ring_lock, flags);

	r = amdgpu_fence_रुको_polling(ring, seq, MAX_KIQ_REG_WAIT);

	/* करोn't रुको anymore क्रम gpu reset हाल because this way may
	 * block gpu_recover() routine क्रमever, e.g. this virt_kiq_rreg
	 * is triggered in TTM and tपंचांग_bo_lock_delayed_workqueue() will
	 * never वापस अगर we keep रुकोing in virt_kiq_rreg, which cause
	 * gpu_recover() hang there.
	 *
	 * also करोn't रुको anymore क्रम IRQ context
	 * */
	अगर (r < 1 && (amdgpu_in_reset(adev) || in_पूर्णांकerrupt()))
		जाओ failed_kiq_ग_लिखो;

	might_sleep();
	जबतक (r < 1 && cnt++ < MAX_KIQ_REG_TRY) अणु

		msleep(MAX_KIQ_REG_BAILOUT_INTERVAL);
		r = amdgpu_fence_रुको_polling(ring, seq, MAX_KIQ_REG_WAIT);
	पूर्ण

	अगर (cnt > MAX_KIQ_REG_TRY)
		जाओ failed_kiq_ग_लिखो;

	वापस;

failed_unकरो:
	amdgpu_ring_unकरो(ring);
	spin_unlock_irqrestore(&kiq->ring_lock, flags);
failed_kiq_ग_लिखो:
	dev_err(adev->dev, "failed to write reg:%x\n", reg);
पूर्ण

पूर्णांक amdgpu_gfx_get_num_kcq(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_num_kcq == -1) अणु
		वापस 8;
	पूर्ण अन्यथा अगर (amdgpu_num_kcq > 8 || amdgpu_num_kcq < 0) अणु
		dev_warn(adev->dev, "set kernel compute queue number to 8 due to invalid parameter provided by user\n");
		वापस 8;
	पूर्ण
	वापस amdgpu_num_kcq;
पूर्ण

/* amdgpu_gfx_state_change_set - Handle gfx घातer state change set
 * @adev: amdgpu_device poपूर्णांकer
 * @state: gfx घातer state(1 -sGpuChangeState_D0Entry and 2 -sGpuChangeState_D3Entry)
 *
 */

व्योम amdgpu_gfx_state_change_set(काष्ठा amdgpu_device *adev, क्रमागत gfx_change_state state)
अणु
	mutex_lock(&adev->pm.mutex);
	अगर (adev->घातerplay.pp_funcs &&
	    adev->घातerplay.pp_funcs->gfx_state_change_set)
		((adev)->घातerplay.pp_funcs->gfx_state_change_set(
			(adev)->घातerplay.pp_handle, state));
	mutex_unlock(&adev->pm.mutex);
पूर्ण
