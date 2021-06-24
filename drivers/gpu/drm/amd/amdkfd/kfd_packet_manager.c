<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_kernel_queue.h"
#समावेश "kfd_priv.h"

अटल अंतरभूत व्योम inc_wptr(अचिन्हित पूर्णांक *wptr, अचिन्हित पूर्णांक increment_bytes,
				अचिन्हित पूर्णांक buffer_size_bytes)
अणु
	अचिन्हित पूर्णांक temp = *wptr + increment_bytes / माप(uपूर्णांक32_t);

	WARN((temp * माप(uपूर्णांक32_t)) > buffer_size_bytes,
	     "Runlist IB overflow");
	*wptr = temp;
पूर्ण

अटल व्योम pm_calc_rlib_size(काष्ठा packet_manager *pm,
				अचिन्हित पूर्णांक *rlib_size,
				bool *over_subscription)
अणु
	अचिन्हित पूर्णांक process_count, queue_count, compute_queue_count, gws_queue_count;
	अचिन्हित पूर्णांक map_queue_size;
	अचिन्हित पूर्णांक max_proc_per_quantum = 1;
	काष्ठा kfd_dev *dev = pm->dqm->dev;

	process_count = pm->dqm->processes_count;
	queue_count = pm->dqm->active_queue_count;
	compute_queue_count = pm->dqm->active_cp_queue_count;
	gws_queue_count = pm->dqm->gws_queue_count;

	/* check अगर there is over subscription
	 * Note: the arbitration between the number of VMIDs and
	 * hws_max_conc_proc has been करोne in
	 * kgd2kfd_device_init().
	 */
	*over_subscription = false;

	अगर (dev->max_proc_per_quantum > 1)
		max_proc_per_quantum = dev->max_proc_per_quantum;

	अगर ((process_count > max_proc_per_quantum) ||
	    compute_queue_count > get_cp_queues_num(pm->dqm) ||
	    gws_queue_count > 1) अणु
		*over_subscription = true;
		pr_debug("Over subscribed runlist\n");
	पूर्ण

	map_queue_size = pm->pmf->map_queues_size;
	/* calculate run list ib allocation size */
	*rlib_size = process_count * pm->pmf->map_process_size +
		     queue_count * map_queue_size;

	/*
	 * Increase the allocation size in हाल we need a chained run list
	 * when over subscription
	 */
	अगर (*over_subscription)
		*rlib_size += pm->pmf->runlist_size;

	pr_debug("runlist ib size %d\n", *rlib_size);
पूर्ण

अटल पूर्णांक pm_allocate_runlist_ib(काष्ठा packet_manager *pm,
				अचिन्हित पूर्णांक **rl_buffer,
				uपूर्णांक64_t *rl_gpu_buffer,
				अचिन्हित पूर्णांक *rl_buffer_size,
				bool *is_over_subscription)
अणु
	पूर्णांक retval;

	अगर (WARN_ON(pm->allocated))
		वापस -EINVAL;

	pm_calc_rlib_size(pm, rl_buffer_size, is_over_subscription);

	mutex_lock(&pm->lock);

	retval = kfd_gtt_sa_allocate(pm->dqm->dev, *rl_buffer_size,
					&pm->ib_buffer_obj);

	अगर (retval) अणु
		pr_err("Failed to allocate runlist IB\n");
		जाओ out;
	पूर्ण

	*(व्योम **)rl_buffer = pm->ib_buffer_obj->cpu_ptr;
	*rl_gpu_buffer = pm->ib_buffer_obj->gpu_addr;

	स_रखो(*rl_buffer, 0, *rl_buffer_size);
	pm->allocated = true;

out:
	mutex_unlock(&pm->lock);
	वापस retval;
पूर्ण

अटल पूर्णांक pm_create_runlist_ib(काष्ठा packet_manager *pm,
				काष्ठा list_head *queues,
				uपूर्णांक64_t *rl_gpu_addr,
				माप_प्रकार *rl_size_bytes)
अणु
	अचिन्हित पूर्णांक alloc_size_bytes;
	अचिन्हित पूर्णांक *rl_buffer, rl_wptr, i;
	पूर्णांक retval, proccesses_mapped;
	काष्ठा device_process_node *cur;
	काष्ठा qcm_process_device *qpd;
	काष्ठा queue *q;
	काष्ठा kernel_queue *kq;
	bool is_over_subscription;

	rl_wptr = retval = proccesses_mapped = 0;

	retval = pm_allocate_runlist_ib(pm, &rl_buffer, rl_gpu_addr,
				&alloc_size_bytes, &is_over_subscription);
	अगर (retval)
		वापस retval;

	*rl_size_bytes = alloc_size_bytes;
	pm->ib_size_bytes = alloc_size_bytes;

	pr_debug("Building runlist ib process count: %d queues count %d\n",
		pm->dqm->processes_count, pm->dqm->active_queue_count);

	/* build the run list ib packet */
	list_क्रम_each_entry(cur, queues, list) अणु
		qpd = cur->qpd;
		/* build map process packet */
		अगर (proccesses_mapped >= pm->dqm->processes_count) अणु
			pr_debug("Not enough space left in runlist IB\n");
			pm_release_ib(pm);
			वापस -ENOMEM;
		पूर्ण

		retval = pm->pmf->map_process(pm, &rl_buffer[rl_wptr], qpd);
		अगर (retval)
			वापस retval;

		proccesses_mapped++;
		inc_wptr(&rl_wptr, pm->pmf->map_process_size,
				alloc_size_bytes);

		list_क्रम_each_entry(kq, &qpd->priv_queue_list, list) अणु
			अगर (!kq->queue->properties.is_active)
				जारी;

			pr_debug("static_queue, mapping kernel q %d, is debug status %d\n",
				kq->queue->queue, qpd->is_debug);

			retval = pm->pmf->map_queues(pm,
						&rl_buffer[rl_wptr],
						kq->queue,
						qpd->is_debug);
			अगर (retval)
				वापस retval;

			inc_wptr(&rl_wptr,
				pm->pmf->map_queues_size,
				alloc_size_bytes);
		पूर्ण

		list_क्रम_each_entry(q, &qpd->queues_list, list) अणु
			अगर (!q->properties.is_active)
				जारी;

			pr_debug("static_queue, mapping user queue %d, is debug status %d\n",
				q->queue, qpd->is_debug);

			retval = pm->pmf->map_queues(pm,
						&rl_buffer[rl_wptr],
						q,
						qpd->is_debug);

			अगर (retval)
				वापस retval;

			inc_wptr(&rl_wptr,
				pm->pmf->map_queues_size,
				alloc_size_bytes);
		पूर्ण
	पूर्ण

	pr_debug("Finished map process and queues to runlist\n");

	अगर (is_over_subscription) अणु
		अगर (!pm->is_over_subscription)
			pr_warn("Runlist is getting oversubscribed. Expect reduced ROCm performance.\n");
		retval = pm->pmf->runlist(pm, &rl_buffer[rl_wptr],
					*rl_gpu_addr,
					alloc_size_bytes / माप(uपूर्णांक32_t),
					true);
	पूर्ण
	pm->is_over_subscription = is_over_subscription;

	क्रम (i = 0; i < alloc_size_bytes / माप(uपूर्णांक32_t); i++)
		pr_debug("0x%2X ", rl_buffer[i]);
	pr_debug("\n");

	वापस retval;
पूर्ण

पूर्णांक pm_init(काष्ठा packet_manager *pm, काष्ठा device_queue_manager *dqm)
अणु
	चयन (dqm->dev->device_info->asic_family) अणु
	हाल CHIP_KAVERI:
	हाल CHIP_HAWAII:
		/* PM4 packet काष्ठाures on CIK are the same as on VI */
	हाल CHIP_CARRIZO:
	हाल CHIP_TONGA:
	हाल CHIP_FIJI:
	हाल CHIP_POLARIS10:
	हाल CHIP_POLARIS11:
	हाल CHIP_POLARIS12:
	हाल CHIP_VEGAM:
		pm->pmf = &kfd_vi_pm_funcs;
		अवरोध;
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
	हाल CHIP_RAVEN:
	हाल CHIP_RENOIR:
	हाल CHIP_ARCTURUS:
	हाल CHIP_ALDEBARAN:
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI12:
	हाल CHIP_NAVI14:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
		pm->pmf = &kfd_v9_pm_funcs;
		अवरोध;
	शेष:
		WARN(1, "Unexpected ASIC family %u",
		     dqm->dev->device_info->asic_family);
		वापस -EINVAL;
	पूर्ण

	pm->dqm = dqm;
	mutex_init(&pm->lock);
	pm->priv_queue = kernel_queue_init(dqm->dev, KFD_QUEUE_TYPE_HIQ);
	अगर (!pm->priv_queue) अणु
		mutex_destroy(&pm->lock);
		वापस -ENOMEM;
	पूर्ण
	pm->allocated = false;

	वापस 0;
पूर्ण

व्योम pm_uninit(काष्ठा packet_manager *pm, bool hanging)
अणु
	mutex_destroy(&pm->lock);
	kernel_queue_uninit(pm->priv_queue, hanging);
पूर्ण

पूर्णांक pm_send_set_resources(काष्ठा packet_manager *pm,
				काष्ठा scheduling_resources *res)
अणु
	uपूर्णांक32_t *buffer, size;
	पूर्णांक retval = 0;

	size = pm->pmf->set_resources_size;
	mutex_lock(&pm->lock);
	kq_acquire_packet_buffer(pm->priv_queue,
					size / माप(uपूर्णांक32_t),
					(अचिन्हित पूर्णांक **)&buffer);
	अगर (!buffer) अणु
		pr_err("Failed to allocate buffer on kernel queue\n");
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	retval = pm->pmf->set_resources(pm, buffer, res);
	अगर (!retval)
		kq_submit_packet(pm->priv_queue);
	अन्यथा
		kq_rollback_packet(pm->priv_queue);

out:
	mutex_unlock(&pm->lock);

	वापस retval;
पूर्ण

पूर्णांक pm_send_runlist(काष्ठा packet_manager *pm, काष्ठा list_head *dqm_queues)
अणु
	uपूर्णांक64_t rl_gpu_ib_addr;
	uपूर्णांक32_t *rl_buffer;
	माप_प्रकार rl_ib_size, packet_size_dwords;
	पूर्णांक retval;

	retval = pm_create_runlist_ib(pm, dqm_queues, &rl_gpu_ib_addr,
					&rl_ib_size);
	अगर (retval)
		जाओ fail_create_runlist_ib;

	pr_debug("runlist IB address: 0x%llX\n", rl_gpu_ib_addr);

	packet_size_dwords = pm->pmf->runlist_size / माप(uपूर्णांक32_t);
	mutex_lock(&pm->lock);

	retval = kq_acquire_packet_buffer(pm->priv_queue,
					packet_size_dwords, &rl_buffer);
	अगर (retval)
		जाओ fail_acquire_packet_buffer;

	retval = pm->pmf->runlist(pm, rl_buffer, rl_gpu_ib_addr,
					rl_ib_size / माप(uपूर्णांक32_t), false);
	अगर (retval)
		जाओ fail_create_runlist;

	kq_submit_packet(pm->priv_queue);

	mutex_unlock(&pm->lock);

	वापस retval;

fail_create_runlist:
	kq_rollback_packet(pm->priv_queue);
fail_acquire_packet_buffer:
	mutex_unlock(&pm->lock);
fail_create_runlist_ib:
	pm_release_ib(pm);
	वापस retval;
पूर्ण

पूर्णांक pm_send_query_status(काष्ठा packet_manager *pm, uपूर्णांक64_t fence_address,
			uपूर्णांक64_t fence_value)
अणु
	uपूर्णांक32_t *buffer, size;
	पूर्णांक retval = 0;

	अगर (WARN_ON(!fence_address))
		वापस -EFAULT;

	size = pm->pmf->query_status_size;
	mutex_lock(&pm->lock);
	kq_acquire_packet_buffer(pm->priv_queue,
			size / माप(uपूर्णांक32_t), (अचिन्हित पूर्णांक **)&buffer);
	अगर (!buffer) अणु
		pr_err("Failed to allocate buffer on kernel queue\n");
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	retval = pm->pmf->query_status(pm, buffer, fence_address, fence_value);
	अगर (!retval)
		kq_submit_packet(pm->priv_queue);
	अन्यथा
		kq_rollback_packet(pm->priv_queue);

out:
	mutex_unlock(&pm->lock);
	वापस retval;
पूर्ण

पूर्णांक pm_send_unmap_queue(काष्ठा packet_manager *pm, क्रमागत kfd_queue_type type,
			क्रमागत kfd_unmap_queues_filter filter,
			uपूर्णांक32_t filter_param, bool reset,
			अचिन्हित पूर्णांक sdma_engine)
अणु
	uपूर्णांक32_t *buffer, size;
	पूर्णांक retval = 0;

	size = pm->pmf->unmap_queues_size;
	mutex_lock(&pm->lock);
	kq_acquire_packet_buffer(pm->priv_queue,
			size / माप(uपूर्णांक32_t), (अचिन्हित पूर्णांक **)&buffer);
	अगर (!buffer) अणु
		pr_err("Failed to allocate buffer on kernel queue\n");
		retval = -ENOMEM;
		जाओ out;
	पूर्ण

	retval = pm->pmf->unmap_queues(pm, buffer, type, filter, filter_param,
				       reset, sdma_engine);
	अगर (!retval)
		kq_submit_packet(pm->priv_queue);
	अन्यथा
		kq_rollback_packet(pm->priv_queue);

out:
	mutex_unlock(&pm->lock);
	वापस retval;
पूर्ण

व्योम pm_release_ib(काष्ठा packet_manager *pm)
अणु
	mutex_lock(&pm->lock);
	अगर (pm->allocated) अणु
		kfd_gtt_sa_मुक्त(pm->dqm->dev, pm->ib_buffer_obj);
		pm->allocated = false;
	पूर्ण
	mutex_unlock(&pm->lock);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

पूर्णांक pm_debugfs_runlist(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा packet_manager *pm = data;

	mutex_lock(&pm->lock);

	अगर (!pm->allocated) अणु
		seq_माला_दो(m, "  No active runlist\n");
		जाओ out;
	पूर्ण

	seq_hex_dump(m, "  ", DUMP_PREFIX_OFFSET, 32, 4,
		     pm->ib_buffer_obj->cpu_ptr, pm->ib_size_bytes, false);

out:
	mutex_unlock(&pm->lock);
	वापस 0;
पूर्ण

पूर्णांक pm_debugfs_hang_hws(काष्ठा packet_manager *pm)
अणु
	uपूर्णांक32_t *buffer, size;
	पूर्णांक r = 0;

	size = pm->pmf->query_status_size;
	mutex_lock(&pm->lock);
	kq_acquire_packet_buffer(pm->priv_queue,
			size / माप(uपूर्णांक32_t), (अचिन्हित पूर्णांक **)&buffer);
	अगर (!buffer) अणु
		pr_err("Failed to allocate buffer on kernel queue\n");
		r = -ENOMEM;
		जाओ out;
	पूर्ण
	स_रखो(buffer, 0x55, size);
	kq_submit_packet(pm->priv_queue);

	pr_info("Submitting %x %x %x %x %x %x %x to HIQ to hang the HWS.",
		buffer[0], buffer[1], buffer[2], buffer[3],
		buffer[4], buffer[5], buffer[6]);
out:
	mutex_unlock(&pm->lock);
	वापस r;
पूर्ण


#पूर्ण_अगर
