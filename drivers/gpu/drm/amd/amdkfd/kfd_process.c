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
 */

#समावेश <linux/mutex.h>
#समावेश <linux/log2.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/slab.h>
#समावेश <linux/amd-iommu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/compat.h>
#समावेश <linux/mman.h>
#समावेश <linux/file.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu.h"

काष्ठा mm_काष्ठा;

#समावेश "kfd_priv.h"
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_dbgmgr.h"
#समावेश "kfd_iommu.h"

/*
 * List of काष्ठा kfd_process (field kfd_process).
 * Unique/indexed by mm_काष्ठा*
 */
DEFINE_HASHTABLE(kfd_processes_table, KFD_PROCESS_TABLE_SIZE);
अटल DEFINE_MUTEX(kfd_processes_mutex);

DEFINE_SRCU(kfd_processes_srcu);

/* For process termination handling */
अटल काष्ठा workqueue_काष्ठा *kfd_process_wq;

/* Ordered, single-thपढ़ोed workqueue क्रम restoring evicted
 * processes. Restoring multiple processes concurrently under memory
 * pressure can lead to processes blocking each other from validating
 * their BOs and result in a live-lock situation where processes
 * reमुख्य evicted indefinitely.
 */
अटल काष्ठा workqueue_काष्ठा *kfd_restore_wq;

अटल काष्ठा kfd_process *find_process(स्थिर काष्ठा task_काष्ठा *thपढ़ो);
अटल व्योम kfd_process_ref_release(काष्ठा kref *ref);
अटल काष्ठा kfd_process *create_process(स्थिर काष्ठा task_काष्ठा *thपढ़ो);
अटल पूर्णांक kfd_process_init_cwsr_apu(काष्ठा kfd_process *p, काष्ठा file *filep);

अटल व्योम evict_process_worker(काष्ठा work_काष्ठा *work);
अटल व्योम restore_process_worker(काष्ठा work_काष्ठा *work);

काष्ठा kfd_procfs_tree अणु
	काष्ठा kobject *kobj;
पूर्ण;

अटल काष्ठा kfd_procfs_tree procfs;

/*
 * Structure क्रम SDMA activity tracking
 */
काष्ठा kfd_sdma_activity_handler_workarea अणु
	काष्ठा work_काष्ठा sdma_activity_work;
	काष्ठा kfd_process_device *pdd;
	uपूर्णांक64_t sdma_activity_counter;
पूर्ण;

काष्ठा temp_sdma_queue_list अणु
	uपूर्णांक64_t __user *rptr;
	uपूर्णांक64_t sdma_val;
	अचिन्हित पूर्णांक queue_id;
	काष्ठा list_head list;
पूर्ण;

अटल व्योम kfd_sdma_activity_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kfd_sdma_activity_handler_workarea *workarea;
	काष्ठा kfd_process_device *pdd;
	uपूर्णांक64_t val;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा queue *q;
	काष्ठा qcm_process_device *qpd;
	काष्ठा device_queue_manager *dqm;
	पूर्णांक ret = 0;
	काष्ठा temp_sdma_queue_list sdma_q_list;
	काष्ठा temp_sdma_queue_list *sdma_q, *next;

	workarea = container_of(work, काष्ठा kfd_sdma_activity_handler_workarea,
				sdma_activity_work);
	अगर (!workarea)
		वापस;

	pdd = workarea->pdd;
	अगर (!pdd)
		वापस;
	dqm = pdd->dev->dqm;
	qpd = &pdd->qpd;
	अगर (!dqm || !qpd)
		वापस;
	/*
	 * Total SDMA activity is current SDMA activity + past SDMA activity
	 * Past SDMA count is stored in pdd.
	 * To get the current activity counters क्रम all active SDMA queues,
	 * we loop over all SDMA queues and get their counts from user-space.
	 *
	 * We cannot call get_user() with dqm_lock held as it can cause
	 * a circular lock dependency situation. To पढ़ो the SDMA stats,
	 * we need to करो the following:
	 *
	 * 1. Create a temporary list of SDMA queue nodes from the qpd->queues_list,
	 *    with dqm_lock/dqm_unlock().
	 * 2. Call get_user() क्रम each node in temporary list without dqm_lock.
	 *    Save the SDMA count क्रम each node and also add the count to the total
	 *    SDMA count counter.
	 *    Its possible, during this step, a few SDMA queue nodes got deleted
	 *    from the qpd->queues_list.
	 * 3. Do a second pass over qpd->queues_list to check अगर any nodes got deleted.
	 *    If any node got deleted, its SDMA count would be captured in the sdma
	 *    past activity counter. So subtract the SDMA counter stored in step 2
	 *    क्रम this node from the total SDMA count.
	 */
	INIT_LIST_HEAD(&sdma_q_list.list);

	/*
	 * Create the temp list of all SDMA queues
	 */
	dqm_lock(dqm);

	list_क्रम_each_entry(q, &qpd->queues_list, list) अणु
		अगर ((q->properties.type != KFD_QUEUE_TYPE_SDMA) &&
		    (q->properties.type != KFD_QUEUE_TYPE_SDMA_XGMI))
			जारी;

		sdma_q = kzalloc(माप(काष्ठा temp_sdma_queue_list), GFP_KERNEL);
		अगर (!sdma_q) अणु
			dqm_unlock(dqm);
			जाओ cleanup;
		पूर्ण

		INIT_LIST_HEAD(&sdma_q->list);
		sdma_q->rptr = (uपूर्णांक64_t __user *)q->properties.पढ़ो_ptr;
		sdma_q->queue_id = q->properties.queue_id;
		list_add_tail(&sdma_q->list, &sdma_q_list.list);
	पूर्ण

	/*
	 * If the temp list is empty, then no SDMA queues nodes were found in
	 * qpd->queues_list. Return the past activity count as the total sdma
	 * count
	 */
	अगर (list_empty(&sdma_q_list.list)) अणु
		workarea->sdma_activity_counter = pdd->sdma_past_activity_counter;
		dqm_unlock(dqm);
		वापस;
	पूर्ण

	dqm_unlock(dqm);

	/*
	 * Get the usage count क्रम each SDMA queue in temp_list.
	 */
	mm = get_task_mm(pdd->process->lead_thपढ़ो);
	अगर (!mm)
		जाओ cleanup;

	kthपढ़ो_use_mm(mm);

	list_क्रम_each_entry(sdma_q, &sdma_q_list.list, list) अणु
		val = 0;
		ret = पढ़ो_sdma_queue_counter(sdma_q->rptr, &val);
		अगर (ret) अणु
			pr_debug("Failed to read SDMA queue active counter for queue id: %d",
				 sdma_q->queue_id);
		पूर्ण अन्यथा अणु
			sdma_q->sdma_val = val;
			workarea->sdma_activity_counter += val;
		पूर्ण
	पूर्ण

	kthपढ़ो_unuse_mm(mm);
	mmput(mm);

	/*
	 * Do a second iteration over qpd_queues_list to check अगर any SDMA
	 * nodes got deleted जबतक fetching SDMA counter.
	 */
	dqm_lock(dqm);

	workarea->sdma_activity_counter += pdd->sdma_past_activity_counter;

	list_क्रम_each_entry(q, &qpd->queues_list, list) अणु
		अगर (list_empty(&sdma_q_list.list))
			अवरोध;

		अगर ((q->properties.type != KFD_QUEUE_TYPE_SDMA) &&
		    (q->properties.type != KFD_QUEUE_TYPE_SDMA_XGMI))
			जारी;

		list_क्रम_each_entry_safe(sdma_q, next, &sdma_q_list.list, list) अणु
			अगर (((uपूर्णांक64_t __user *)q->properties.पढ़ो_ptr == sdma_q->rptr) &&
			     (sdma_q->queue_id == q->properties.queue_id)) अणु
				list_del(&sdma_q->list);
				kमुक्त(sdma_q);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	dqm_unlock(dqm);

	/*
	 * If temp list is not empty, it implies some queues got deleted
	 * from qpd->queues_list during SDMA usage पढ़ो. Subtract the SDMA
	 * count क्रम each node from the total SDMA count.
	 */
	list_क्रम_each_entry_safe(sdma_q, next, &sdma_q_list.list, list) अणु
		workarea->sdma_activity_counter -= sdma_q->sdma_val;
		list_del(&sdma_q->list);
		kमुक्त(sdma_q);
	पूर्ण

	वापस;

cleanup:
	list_क्रम_each_entry_safe(sdma_q, next, &sdma_q_list.list, list) अणु
		list_del(&sdma_q->list);
		kमुक्त(sdma_q);
	पूर्ण
पूर्ण

/**
 * @kfd_get_cu_occupancy() - Collect number of waves in-flight on this device
 * by current process. Translates acquired wave count पूर्णांकo number of compute units
 * that are occupied.
 *
 * @atr: Handle of attribute that allows reporting of wave count. The attribute
 * handle encapsulates GPU device it is associated with, thereby allowing collection
 * of waves in flight, etc
 *
 * @buffer: Handle of user provided buffer updated with wave count
 *
 * Return: Number of bytes written to user buffer or an error value
 */
अटल पूर्णांक kfd_get_cu_occupancy(काष्ठा attribute *attr, अक्षर *buffer)
अणु
	पूर्णांक cu_cnt;
	पूर्णांक wave_cnt;
	पूर्णांक max_waves_per_cu;
	काष्ठा kfd_dev *dev = शून्य;
	काष्ठा kfd_process *proc = शून्य;
	काष्ठा kfd_process_device *pdd = शून्य;

	pdd = container_of(attr, काष्ठा kfd_process_device, attr_cu_occupancy);
	dev = pdd->dev;
	अगर (dev->kfd2kgd->get_cu_occupancy == शून्य)
		वापस -EINVAL;

	cu_cnt = 0;
	proc = pdd->process;
	अगर (pdd->qpd.queue_count == 0) अणु
		pr_debug("Gpu-Id: %d has no active queues for process %d\n",
			 dev->id, proc->pasid);
		वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", cu_cnt);
	पूर्ण

	/* Collect wave count from device अगर it supports */
	wave_cnt = 0;
	max_waves_per_cu = 0;
	dev->kfd2kgd->get_cu_occupancy(dev->kgd, proc->pasid, &wave_cnt,
			&max_waves_per_cu);

	/* Translate wave count to number of compute units */
	cu_cnt = (wave_cnt + (max_waves_per_cu - 1)) / max_waves_per_cu;
	वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", cu_cnt);
पूर्ण

अटल sमाप_प्रकार kfd_procfs_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       अक्षर *buffer)
अणु
	अगर (म_भेद(attr->name, "pasid") == 0) अणु
		काष्ठा kfd_process *p = container_of(attr, काष्ठा kfd_process,
						     attr_pasid);

		वापस snम_लिखो(buffer, PAGE_SIZE, "%d\n", p->pasid);
	पूर्ण अन्यथा अगर (म_भेदन(attr->name, "vram_", 5) == 0) अणु
		काष्ठा kfd_process_device *pdd = container_of(attr, काष्ठा kfd_process_device,
							      attr_vram);
		वापस snम_लिखो(buffer, PAGE_SIZE, "%llu\n", READ_ONCE(pdd->vram_usage));
	पूर्ण अन्यथा अगर (म_भेदन(attr->name, "sdma_", 5) == 0) अणु
		काष्ठा kfd_process_device *pdd = container_of(attr, काष्ठा kfd_process_device,
							      attr_sdma);
		काष्ठा kfd_sdma_activity_handler_workarea sdma_activity_work_handler;

		INIT_WORK(&sdma_activity_work_handler.sdma_activity_work,
					kfd_sdma_activity_worker);

		sdma_activity_work_handler.pdd = pdd;
		sdma_activity_work_handler.sdma_activity_counter = 0;

		schedule_work(&sdma_activity_work_handler.sdma_activity_work);

		flush_work(&sdma_activity_work_handler.sdma_activity_work);

		वापस snम_लिखो(buffer, PAGE_SIZE, "%llu\n",
				(sdma_activity_work_handler.sdma_activity_counter)/
				 SDMA_ACTIVITY_DIVISOR);
	पूर्ण अन्यथा अणु
		pr_err("Invalid attribute");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kfd_procfs_kobj_release(काष्ठा kobject *kobj)
अणु
	kमुक्त(kobj);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops kfd_procfs_ops = अणु
	.show = kfd_procfs_show,
पूर्ण;

अटल काष्ठा kobj_type procfs_type = अणु
	.release = kfd_procfs_kobj_release,
	.sysfs_ops = &kfd_procfs_ops,
पूर्ण;

व्योम kfd_procfs_init(व्योम)
अणु
	पूर्णांक ret = 0;

	procfs.kobj = kfd_alloc_काष्ठा(procfs.kobj);
	अगर (!procfs.kobj)
		वापस;

	ret = kobject_init_and_add(procfs.kobj, &procfs_type,
				   &kfd_device->kobj, "proc");
	अगर (ret) अणु
		pr_warn("Could not create procfs proc folder");
		/* If we fail to create the procfs, clean up */
		kfd_procfs_shutकरोwn();
	पूर्ण
पूर्ण

व्योम kfd_procfs_shutकरोwn(व्योम)
अणु
	अगर (procfs.kobj) अणु
		kobject_del(procfs.kobj);
		kobject_put(procfs.kobj);
		procfs.kobj = शून्य;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार kfd_procfs_queue_show(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, अक्षर *buffer)
अणु
	काष्ठा queue *q = container_of(kobj, काष्ठा queue, kobj);

	अगर (!म_भेद(attr->name, "size"))
		वापस snम_लिखो(buffer, PAGE_SIZE, "%llu",
				q->properties.queue_size);
	अन्यथा अगर (!म_भेद(attr->name, "type"))
		वापस snम_लिखो(buffer, PAGE_SIZE, "%d", q->properties.type);
	अन्यथा अगर (!म_भेद(attr->name, "gpuid"))
		वापस snम_लिखो(buffer, PAGE_SIZE, "%u", q->device->id);
	अन्यथा
		pr_err("Invalid attribute");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार kfd_procfs_stats_show(काष्ठा kobject *kobj,
				     काष्ठा attribute *attr, अक्षर *buffer)
अणु
	अगर (म_भेद(attr->name, "evicted_ms") == 0) अणु
		काष्ठा kfd_process_device *pdd = container_of(attr,
				काष्ठा kfd_process_device,
				attr_evict);
		uपूर्णांक64_t evict_jअगरfies;

		evict_jअगरfies = atomic64_पढ़ो(&pdd->evict_duration_counter);

		वापस snम_लिखो(buffer,
				PAGE_SIZE,
				"%llu\n",
				jअगरfies64_to_msecs(evict_jअगरfies));

	/* Sysfs handle that माला_लो CU occupancy is per device */
	पूर्ण अन्यथा अगर (म_भेद(attr->name, "cu_occupancy") == 0) अणु
		वापस kfd_get_cu_occupancy(attr, buffer);
	पूर्ण अन्यथा अणु
		pr_err("Invalid attribute");
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा attribute attr_queue_size = अणु
	.name = "size",
	.mode = KFD_SYSFS_खाता_MODE
पूर्ण;

अटल काष्ठा attribute attr_queue_type = अणु
	.name = "type",
	.mode = KFD_SYSFS_खाता_MODE
पूर्ण;

अटल काष्ठा attribute attr_queue_gpuid = अणु
	.name = "gpuid",
	.mode = KFD_SYSFS_खाता_MODE
पूर्ण;

अटल काष्ठा attribute *procfs_queue_attrs[] = अणु
	&attr_queue_size,
	&attr_queue_type,
	&attr_queue_gpuid,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops procfs_queue_ops = अणु
	.show = kfd_procfs_queue_show,
पूर्ण;

अटल काष्ठा kobj_type procfs_queue_type = अणु
	.sysfs_ops = &procfs_queue_ops,
	.शेष_attrs = procfs_queue_attrs,
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops procfs_stats_ops = अणु
	.show = kfd_procfs_stats_show,
पूर्ण;

अटल काष्ठा attribute *procfs_stats_attrs[] = अणु
	शून्य
पूर्ण;

अटल काष्ठा kobj_type procfs_stats_type = अणु
	.sysfs_ops = &procfs_stats_ops,
	.शेष_attrs = procfs_stats_attrs,
पूर्ण;

पूर्णांक kfd_procfs_add_queue(काष्ठा queue *q)
अणु
	काष्ठा kfd_process *proc;
	पूर्णांक ret;

	अगर (!q || !q->process)
		वापस -EINVAL;
	proc = q->process;

	/* Create proc/<pid>/queues/<queue id> folder */
	अगर (!proc->kobj_queues)
		वापस -EFAULT;
	ret = kobject_init_and_add(&q->kobj, &procfs_queue_type,
			proc->kobj_queues, "%u", q->properties.queue_id);
	अगर (ret < 0) अणु
		pr_warn("Creating proc/<pid>/queues/%u failed",
			q->properties.queue_id);
		kobject_put(&q->kobj);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kfd_sysfs_create_file(काष्ठा kfd_process *p, काष्ठा attribute *attr,
				 अक्षर *name)
अणु
	पूर्णांक ret = 0;

	अगर (!p || !attr || !name)
		वापस -EINVAL;

	attr->name = name;
	attr->mode = KFD_SYSFS_खाता_MODE;
	sysfs_attr_init(attr);

	ret = sysfs_create_file(p->kobj, attr);

	वापस ret;
पूर्ण

अटल पूर्णांक kfd_procfs_add_sysfs_stats(काष्ठा kfd_process *p)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	अक्षर stats_dir_filename[MAX_SYSFS_खाताNAME_LEN];

	अगर (!p)
		वापस -EINVAL;

	अगर (!p->kobj)
		वापस -EFAULT;

	/*
	 * Create sysfs files क्रम each GPU:
	 * - proc/<pid>/stats_<gpuid>/
	 * - proc/<pid>/stats_<gpuid>/evicted_ms
	 * - proc/<pid>/stats_<gpuid>/cu_occupancy
	 */
	क्रम (i = 0; i < p->n_pdds; i++) अणु
		काष्ठा kfd_process_device *pdd = p->pdds[i];
		काष्ठा kobject *kobj_stats;

		snम_लिखो(stats_dir_filename, MAX_SYSFS_खाताNAME_LEN,
				"stats_%u", pdd->dev->id);
		kobj_stats = kfd_alloc_काष्ठा(kobj_stats);
		अगर (!kobj_stats)
			वापस -ENOMEM;

		ret = kobject_init_and_add(kobj_stats,
						&procfs_stats_type,
						p->kobj,
						stats_dir_filename);

		अगर (ret) अणु
			pr_warn("Creating KFD proc/stats_%s folder failed",
					stats_dir_filename);
			kobject_put(kobj_stats);
			जाओ err;
		पूर्ण

		pdd->kobj_stats = kobj_stats;
		pdd->attr_evict.name = "evicted_ms";
		pdd->attr_evict.mode = KFD_SYSFS_खाता_MODE;
		sysfs_attr_init(&pdd->attr_evict);
		ret = sysfs_create_file(kobj_stats, &pdd->attr_evict);
		अगर (ret)
			pr_warn("Creating eviction stats for gpuid %d failed",
					(पूर्णांक)pdd->dev->id);

		/* Add sysfs file to report compute unit occupancy */
		अगर (pdd->dev->kfd2kgd->get_cu_occupancy != शून्य) अणु
			pdd->attr_cu_occupancy.name = "cu_occupancy";
			pdd->attr_cu_occupancy.mode = KFD_SYSFS_खाता_MODE;
			sysfs_attr_init(&pdd->attr_cu_occupancy);
			ret = sysfs_create_file(kobj_stats,
						&pdd->attr_cu_occupancy);
			अगर (ret)
				pr_warn("Creating %s failed for gpuid: %d",
					pdd->attr_cu_occupancy.name,
					(पूर्णांक)pdd->dev->id);
		पूर्ण
	पूर्ण
err:
	वापस ret;
पूर्ण


अटल पूर्णांक kfd_procfs_add_sysfs_files(काष्ठा kfd_process *p)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (!p)
		वापस -EINVAL;

	अगर (!p->kobj)
		वापस -EFAULT;

	/*
	 * Create sysfs files क्रम each GPU:
	 * - proc/<pid>/vram_<gpuid>
	 * - proc/<pid>/sdma_<gpuid>
	 */
	क्रम (i = 0; i < p->n_pdds; i++) अणु
		काष्ठा kfd_process_device *pdd = p->pdds[i];

		snम_लिखो(pdd->vram_filename, MAX_SYSFS_खाताNAME_LEN, "vram_%u",
			 pdd->dev->id);
		ret = kfd_sysfs_create_file(p, &pdd->attr_vram, pdd->vram_filename);
		अगर (ret)
			pr_warn("Creating vram usage for gpu id %d failed",
				(पूर्णांक)pdd->dev->id);

		snम_लिखो(pdd->sdma_filename, MAX_SYSFS_खाताNAME_LEN, "sdma_%u",
			 pdd->dev->id);
		ret = kfd_sysfs_create_file(p, &pdd->attr_sdma, pdd->sdma_filename);
		अगर (ret)
			pr_warn("Creating sdma usage for gpu id %d failed",
				(पूर्णांक)pdd->dev->id);
	पूर्ण

	वापस ret;
पूर्ण

व्योम kfd_procfs_del_queue(काष्ठा queue *q)
अणु
	अगर (!q)
		वापस;

	kobject_del(&q->kobj);
	kobject_put(&q->kobj);
पूर्ण

पूर्णांक kfd_process_create_wq(व्योम)
अणु
	अगर (!kfd_process_wq)
		kfd_process_wq = alloc_workqueue("kfd_process_wq", 0, 0);
	अगर (!kfd_restore_wq)
		kfd_restore_wq = alloc_ordered_workqueue("kfd_restore_wq", 0);

	अगर (!kfd_process_wq || !kfd_restore_wq) अणु
		kfd_process_destroy_wq();
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम kfd_process_destroy_wq(व्योम)
अणु
	अगर (kfd_process_wq) अणु
		destroy_workqueue(kfd_process_wq);
		kfd_process_wq = शून्य;
	पूर्ण
	अगर (kfd_restore_wq) अणु
		destroy_workqueue(kfd_restore_wq);
		kfd_restore_wq = शून्य;
	पूर्ण
पूर्ण

अटल व्योम kfd_process_मुक्त_gpuvm(काष्ठा kgd_mem *mem,
			काष्ठा kfd_process_device *pdd)
अणु
	काष्ठा kfd_dev *dev = pdd->dev;

	amdgpu_amdkfd_gpuvm_unmap_memory_from_gpu(dev->kgd, mem, pdd->vm);
	amdgpu_amdkfd_gpuvm_मुक्त_memory_of_gpu(dev->kgd, mem, शून्य);
पूर्ण

/* kfd_process_alloc_gpuvm - Allocate GPU VM क्रम the KFD process
 *	This function should be only called right after the process
 *	is created and when kfd_processes_mutex is still being held
 *	to aव्योम concurrency. Because of that exclusiveness, we करो
 *	not need to take p->mutex.
 */
अटल पूर्णांक kfd_process_alloc_gpuvm(काष्ठा kfd_process_device *pdd,
				   uपूर्णांक64_t gpu_va, uपूर्णांक32_t size,
				   uपूर्णांक32_t flags, व्योम **kptr)
अणु
	काष्ठा kfd_dev *kdev = pdd->dev;
	काष्ठा kgd_mem *mem = शून्य;
	पूर्णांक handle;
	पूर्णांक err;

	err = amdgpu_amdkfd_gpuvm_alloc_memory_of_gpu(kdev->kgd, gpu_va, size,
						 pdd->vm, &mem, शून्य, flags);
	अगर (err)
		जाओ err_alloc_mem;

	err = amdgpu_amdkfd_gpuvm_map_memory_to_gpu(kdev->kgd, mem, pdd->vm);
	अगर (err)
		जाओ err_map_mem;

	err = amdgpu_amdkfd_gpuvm_sync_memory(kdev->kgd, mem, true);
	अगर (err) अणु
		pr_debug("Sync memory failed, wait interrupted by user signal\n");
		जाओ sync_memory_failed;
	पूर्ण

	/* Create an obj handle so kfd_process_device_हटाओ_obj_handle
	 * will take care of the bo removal when the process finishes.
	 * We करो not need to take p->mutex, because the process is just
	 * created and the ioctls have not had the chance to run.
	 */
	handle = kfd_process_device_create_obj_handle(pdd, mem);

	अगर (handle < 0) अणु
		err = handle;
		जाओ मुक्त_gpuvm;
	पूर्ण

	अगर (kptr) अणु
		err = amdgpu_amdkfd_gpuvm_map_gtt_bo_to_kernel(kdev->kgd,
				(काष्ठा kgd_mem *)mem, kptr, शून्य);
		अगर (err) अणु
			pr_debug("Map GTT BO to kernel failed\n");
			जाओ मुक्त_obj_handle;
		पूर्ण
	पूर्ण

	वापस err;

मुक्त_obj_handle:
	kfd_process_device_हटाओ_obj_handle(pdd, handle);
मुक्त_gpuvm:
sync_memory_failed:
	kfd_process_मुक्त_gpuvm(mem, pdd);
	वापस err;

err_map_mem:
	amdgpu_amdkfd_gpuvm_मुक्त_memory_of_gpu(kdev->kgd, mem, शून्य);
err_alloc_mem:
	*kptr = शून्य;
	वापस err;
पूर्ण

/* kfd_process_device_reserve_ib_mem - Reserve memory inside the
 *	process क्रम IB usage The memory reserved is क्रम KFD to submit
 *	IB to AMDGPU from kernel.  If the memory is reserved
 *	successfully, ib_kaddr will have the CPU/kernel
 *	address. Check ib_kaddr beक्रमe accessing the memory.
 */
अटल पूर्णांक kfd_process_device_reserve_ib_mem(काष्ठा kfd_process_device *pdd)
अणु
	काष्ठा qcm_process_device *qpd = &pdd->qpd;
	uपूर्णांक32_t flags = KFD_IOC_ALLOC_MEM_FLAGS_GTT |
			KFD_IOC_ALLOC_MEM_FLAGS_NO_SUBSTITUTE |
			KFD_IOC_ALLOC_MEM_FLAGS_WRITABLE |
			KFD_IOC_ALLOC_MEM_FLAGS_EXECUTABLE;
	व्योम *kaddr;
	पूर्णांक ret;

	अगर (qpd->ib_kaddr || !qpd->ib_base)
		वापस 0;

	/* ib_base is only set क्रम dGPU */
	ret = kfd_process_alloc_gpuvm(pdd, qpd->ib_base, PAGE_SIZE, flags,
				      &kaddr);
	अगर (ret)
		वापस ret;

	qpd->ib_kaddr = kaddr;

	वापस 0;
पूर्ण

काष्ठा kfd_process *kfd_create_process(काष्ठा file *filep)
अणु
	काष्ठा kfd_process *process;
	काष्ठा task_काष्ठा *thपढ़ो = current;
	पूर्णांक ret;

	अगर (!thपढ़ो->mm)
		वापस ERR_PTR(-EINVAL);

	/* Only the pthपढ़ोs thपढ़ोing model is supported. */
	अगर (thपढ़ो->group_leader->mm != thपढ़ो->mm)
		वापस ERR_PTR(-EINVAL);

	/*
	 * take kfd processes mutex beक्रमe starting of process creation
	 * so there won't be a हाल where two thपढ़ोs of the same process
	 * create two kfd_process काष्ठाures
	 */
	mutex_lock(&kfd_processes_mutex);

	/* A prior खोलो of /dev/kfd could have alपढ़ोy created the process. */
	process = find_process(thपढ़ो);
	अगर (process) अणु
		pr_debug("Process already found\n");
	पूर्ण अन्यथा अणु
		process = create_process(thपढ़ो);
		अगर (IS_ERR(process))
			जाओ out;

		ret = kfd_process_init_cwsr_apu(process, filep);
		अगर (ret)
			जाओ out_destroy;

		अगर (!procfs.kobj)
			जाओ out;

		process->kobj = kfd_alloc_काष्ठा(process->kobj);
		अगर (!process->kobj) अणु
			pr_warn("Creating procfs kobject failed");
			जाओ out;
		पूर्ण
		ret = kobject_init_and_add(process->kobj, &procfs_type,
					   procfs.kobj, "%d",
					   (पूर्णांक)process->lead_thपढ़ो->pid);
		अगर (ret) अणु
			pr_warn("Creating procfs pid directory failed");
			kobject_put(process->kobj);
			जाओ out;
		पूर्ण

		process->attr_pasid.name = "pasid";
		process->attr_pasid.mode = KFD_SYSFS_खाता_MODE;
		sysfs_attr_init(&process->attr_pasid);
		ret = sysfs_create_file(process->kobj, &process->attr_pasid);
		अगर (ret)
			pr_warn("Creating pasid for pid %d failed",
					(पूर्णांक)process->lead_thपढ़ो->pid);

		process->kobj_queues = kobject_create_and_add("queues",
							process->kobj);
		अगर (!process->kobj_queues)
			pr_warn("Creating KFD proc/queues folder failed");

		ret = kfd_procfs_add_sysfs_stats(process);
		अगर (ret)
			pr_warn("Creating sysfs stats dir for pid %d failed",
				(पूर्णांक)process->lead_thपढ़ो->pid);

		ret = kfd_procfs_add_sysfs_files(process);
		अगर (ret)
			pr_warn("Creating sysfs usage file for pid %d failed",
				(पूर्णांक)process->lead_thपढ़ो->pid);
	पूर्ण
out:
	अगर (!IS_ERR(process))
		kref_get(&process->ref);
	mutex_unlock(&kfd_processes_mutex);

	वापस process;

out_destroy:
	hash_del_rcu(&process->kfd_processes);
	mutex_unlock(&kfd_processes_mutex);
	synchronize_srcu(&kfd_processes_srcu);
	/* kfd_process_मुक्त_notअगरier will trigger the cleanup */
	mmu_notअगरier_put(&process->mmu_notअगरier);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा kfd_process *kfd_get_process(स्थिर काष्ठा task_काष्ठा *thपढ़ो)
अणु
	काष्ठा kfd_process *process;

	अगर (!thपढ़ो->mm)
		वापस ERR_PTR(-EINVAL);

	/* Only the pthपढ़ोs thपढ़ोing model is supported. */
	अगर (thपढ़ो->group_leader->mm != thपढ़ो->mm)
		वापस ERR_PTR(-EINVAL);

	process = find_process(thपढ़ो);
	अगर (!process)
		वापस ERR_PTR(-EINVAL);

	वापस process;
पूर्ण

अटल काष्ठा kfd_process *find_process_by_mm(स्थिर काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा kfd_process *process;

	hash_क्रम_each_possible_rcu(kfd_processes_table, process,
					kfd_processes, (uपूर्णांकptr_t)mm)
		अगर (process->mm == mm)
			वापस process;

	वापस शून्य;
पूर्ण

अटल काष्ठा kfd_process *find_process(स्थिर काष्ठा task_काष्ठा *thपढ़ो)
अणु
	काष्ठा kfd_process *p;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&kfd_processes_srcu);
	p = find_process_by_mm(thपढ़ो->mm);
	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);

	वापस p;
पूर्ण

व्योम kfd_unref_process(काष्ठा kfd_process *p)
अणु
	kref_put(&p->ref, kfd_process_ref_release);
पूर्ण


अटल व्योम kfd_process_device_मुक्त_bos(काष्ठा kfd_process_device *pdd)
अणु
	काष्ठा kfd_process *p = pdd->process;
	व्योम *mem;
	पूर्णांक id;
	पूर्णांक i;

	/*
	 * Remove all handles from idr and release appropriate
	 * local memory object
	 */
	idr_क्रम_each_entry(&pdd->alloc_idr, mem, id) अणु

		क्रम (i = 0; i < p->n_pdds; i++) अणु
			काष्ठा kfd_process_device *peer_pdd = p->pdds[i];

			अगर (!peer_pdd->vm)
				जारी;
			amdgpu_amdkfd_gpuvm_unmap_memory_from_gpu(
				peer_pdd->dev->kgd, mem, peer_pdd->vm);
		पूर्ण

		amdgpu_amdkfd_gpuvm_मुक्त_memory_of_gpu(pdd->dev->kgd, mem, शून्य);
		kfd_process_device_हटाओ_obj_handle(pdd, id);
	पूर्ण
पूर्ण

अटल व्योम kfd_process_मुक्त_outstanding_kfd_bos(काष्ठा kfd_process *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < p->n_pdds; i++)
		kfd_process_device_मुक्त_bos(p->pdds[i]);
पूर्ण

अटल व्योम kfd_process_destroy_pdds(काष्ठा kfd_process *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < p->n_pdds; i++) अणु
		काष्ठा kfd_process_device *pdd = p->pdds[i];

		pr_debug("Releasing pdd (topology id %d) for process (pasid 0x%x)\n",
				pdd->dev->id, p->pasid);

		अगर (pdd->drm_file) अणु
			amdgpu_amdkfd_gpuvm_release_process_vm(
					pdd->dev->kgd, pdd->vm);
			fput(pdd->drm_file);
		पूर्ण

		अगर (pdd->qpd.cwsr_kaddr && !pdd->qpd.cwsr_base)
			मुक्त_pages((अचिन्हित दीर्घ)pdd->qpd.cwsr_kaddr,
				get_order(KFD_CWSR_TBA_TMA_SIZE));

		kमुक्त(pdd->qpd.करोorbell_biपंचांगap);
		idr_destroy(&pdd->alloc_idr);

		kfd_मुक्त_process_करोorbells(pdd->dev, pdd->करोorbell_index);

		/*
		 * beक्रमe destroying pdd, make sure to report availability
		 * क्रम स्वतः suspend
		 */
		अगर (pdd->runसमय_inuse) अणु
			pm_runसमय_mark_last_busy(pdd->dev->ddev->dev);
			pm_runसमय_put_स्वतःsuspend(pdd->dev->ddev->dev);
			pdd->runसमय_inuse = false;
		पूर्ण

		kमुक्त(pdd);
		p->pdds[i] = शून्य;
	पूर्ण
	p->n_pdds = 0;
पूर्ण

/* No process locking is needed in this function, because the process
 * is not findable any more. We must assume that no other thपढ़ो is
 * using it any more, otherwise we couldn't safely मुक्त the process
 * काष्ठाure in the end.
 */
अटल व्योम kfd_process_wq_release(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kfd_process *p = container_of(work, काष्ठा kfd_process,
					     release_work);
	पूर्णांक i;

	/* Remove the procfs files */
	अगर (p->kobj) अणु
		sysfs_हटाओ_file(p->kobj, &p->attr_pasid);
		kobject_del(p->kobj_queues);
		kobject_put(p->kobj_queues);
		p->kobj_queues = शून्य;

		क्रम (i = 0; i < p->n_pdds; i++) अणु
			काष्ठा kfd_process_device *pdd = p->pdds[i];

			sysfs_हटाओ_file(p->kobj, &pdd->attr_vram);
			sysfs_हटाओ_file(p->kobj, &pdd->attr_sdma);
			sysfs_हटाओ_file(p->kobj, &pdd->attr_evict);
			अगर (pdd->dev->kfd2kgd->get_cu_occupancy != शून्य)
				sysfs_हटाओ_file(p->kobj, &pdd->attr_cu_occupancy);
			kobject_del(pdd->kobj_stats);
			kobject_put(pdd->kobj_stats);
			pdd->kobj_stats = शून्य;
		पूर्ण

		kobject_del(p->kobj);
		kobject_put(p->kobj);
		p->kobj = शून्य;
	पूर्ण

	kfd_iommu_unbind_process(p);

	kfd_process_मुक्त_outstanding_kfd_bos(p);

	kfd_process_destroy_pdds(p);
	dma_fence_put(p->ef);

	kfd_event_मुक्त_process(p);

	kfd_pasid_मुक्त(p->pasid);
	mutex_destroy(&p->mutex);

	put_task_काष्ठा(p->lead_thपढ़ो);

	kमुक्त(p);
पूर्ण

अटल व्योम kfd_process_ref_release(काष्ठा kref *ref)
अणु
	काष्ठा kfd_process *p = container_of(ref, काष्ठा kfd_process, ref);

	INIT_WORK(&p->release_work, kfd_process_wq_release);
	queue_work(kfd_process_wq, &p->release_work);
पूर्ण

अटल काष्ठा mmu_notअगरier *kfd_process_alloc_notअगरier(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक idx = srcu_पढ़ो_lock(&kfd_processes_srcu);
	काष्ठा kfd_process *p = find_process_by_mm(mm);

	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);

	वापस p ? &p->mmu_notअगरier : ERR_PTR(-ESRCH);
पूर्ण

अटल व्योम kfd_process_मुक्त_notअगरier(काष्ठा mmu_notअगरier *mn)
अणु
	kfd_unref_process(container_of(mn, काष्ठा kfd_process, mmu_notअगरier));
पूर्ण

अटल व्योम kfd_process_notअगरier_release(काष्ठा mmu_notअगरier *mn,
					काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा kfd_process *p;
	पूर्णांक i;

	/*
	 * The kfd_process काष्ठाure can not be मुक्त because the
	 * mmu_notअगरier srcu is पढ़ो locked
	 */
	p = container_of(mn, काष्ठा kfd_process, mmu_notअगरier);
	अगर (WARN_ON(p->mm != mm))
		वापस;

	mutex_lock(&kfd_processes_mutex);
	hash_del_rcu(&p->kfd_processes);
	mutex_unlock(&kfd_processes_mutex);
	synchronize_srcu(&kfd_processes_srcu);

	cancel_delayed_work_sync(&p->eviction_work);
	cancel_delayed_work_sync(&p->restore_work);

	mutex_lock(&p->mutex);

	/* Iterate over all process device data काष्ठाures and अगर the
	 * pdd is in debug mode, we should first क्रमce unregistration,
	 * then we will be able to destroy the queues
	 */
	क्रम (i = 0; i < p->n_pdds; i++) अणु
		काष्ठा kfd_dev *dev = p->pdds[i]->dev;

		mutex_lock(kfd_get_dbgmgr_mutex());
		अगर (dev && dev->dbgmgr && dev->dbgmgr->pasid == p->pasid) अणु
			अगर (!kfd_dbgmgr_unरेजिस्टर(dev->dbgmgr, p)) अणु
				kfd_dbgmgr_destroy(dev->dbgmgr);
				dev->dbgmgr = शून्य;
			पूर्ण
		पूर्ण
		mutex_unlock(kfd_get_dbgmgr_mutex());
	पूर्ण

	kfd_process_dequeue_from_all_devices(p);
	pqm_uninit(&p->pqm);

	/* Indicate to other users that MM is no दीर्घer valid */
	p->mm = शून्य;
	/* Signal the eviction fence after user mode queues are
	 * destroyed. This allows any BOs to be मुक्तd without
	 * triggering poपूर्णांकless evictions or रुकोing क्रम fences.
	 */
	dma_fence_संकेत(p->ef);

	mutex_unlock(&p->mutex);

	mmu_notअगरier_put(&p->mmu_notअगरier);
पूर्ण

अटल स्थिर काष्ठा mmu_notअगरier_ops kfd_process_mmu_notअगरier_ops = अणु
	.release = kfd_process_notअगरier_release,
	.alloc_notअगरier = kfd_process_alloc_notअगरier,
	.मुक्त_notअगरier = kfd_process_मुक्त_notअगरier,
पूर्ण;

अटल पूर्णांक kfd_process_init_cwsr_apu(काष्ठा kfd_process *p, काष्ठा file *filep)
अणु
	अचिन्हित दीर्घ  offset;
	पूर्णांक i;

	क्रम (i = 0; i < p->n_pdds; i++) अणु
		काष्ठा kfd_dev *dev = p->pdds[i]->dev;
		काष्ठा qcm_process_device *qpd = &p->pdds[i]->qpd;

		अगर (!dev->cwsr_enabled || qpd->cwsr_kaddr || qpd->cwsr_base)
			जारी;

		offset = KFD_MMAP_TYPE_RESERVED_MEM | KFD_MMAP_GPU_ID(dev->id);
		qpd->tba_addr = (पूर्णांक64_t)vm_mmap(filep, 0,
			KFD_CWSR_TBA_TMA_SIZE, PROT_READ | PROT_EXEC,
			MAP_SHARED, offset);

		अगर (IS_ERR_VALUE(qpd->tba_addr)) अणु
			पूर्णांक err = qpd->tba_addr;

			pr_err("Failure to set tba address. error %d.\n", err);
			qpd->tba_addr = 0;
			qpd->cwsr_kaddr = शून्य;
			वापस err;
		पूर्ण

		स_नकल(qpd->cwsr_kaddr, dev->cwsr_isa, dev->cwsr_isa_size);

		qpd->पंचांगa_addr = qpd->tba_addr + KFD_CWSR_TMA_OFFSET;
		pr_debug("set tba :0x%llx, tma:0x%llx, cwsr_kaddr:%p for pqm.\n",
			qpd->tba_addr, qpd->पंचांगa_addr, qpd->cwsr_kaddr);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kfd_process_device_init_cwsr_dgpu(काष्ठा kfd_process_device *pdd)
अणु
	काष्ठा kfd_dev *dev = pdd->dev;
	काष्ठा qcm_process_device *qpd = &pdd->qpd;
	uपूर्णांक32_t flags = KFD_IOC_ALLOC_MEM_FLAGS_GTT
			| KFD_IOC_ALLOC_MEM_FLAGS_NO_SUBSTITUTE
			| KFD_IOC_ALLOC_MEM_FLAGS_EXECUTABLE;
	व्योम *kaddr;
	पूर्णांक ret;

	अगर (!dev->cwsr_enabled || qpd->cwsr_kaddr || !qpd->cwsr_base)
		वापस 0;

	/* cwsr_base is only set क्रम dGPU */
	ret = kfd_process_alloc_gpuvm(pdd, qpd->cwsr_base,
				      KFD_CWSR_TBA_TMA_SIZE, flags, &kaddr);
	अगर (ret)
		वापस ret;

	qpd->cwsr_kaddr = kaddr;
	qpd->tba_addr = qpd->cwsr_base;

	स_नकल(qpd->cwsr_kaddr, dev->cwsr_isa, dev->cwsr_isa_size);

	qpd->पंचांगa_addr = qpd->tba_addr + KFD_CWSR_TMA_OFFSET;
	pr_debug("set tba :0x%llx, tma:0x%llx, cwsr_kaddr:%p for pqm.\n",
		 qpd->tba_addr, qpd->पंचांगa_addr, qpd->cwsr_kaddr);

	वापस 0;
पूर्ण

व्योम kfd_process_set_trap_handler(काष्ठा qcm_process_device *qpd,
				  uपूर्णांक64_t tba_addr,
				  uपूर्णांक64_t पंचांगa_addr)
अणु
	अगर (qpd->cwsr_kaddr) अणु
		/* KFD trap handler is bound, record as second-level TBA/TMA
		 * in first-level TMA. First-level trap will jump to second.
		 */
		uपूर्णांक64_t *पंचांगa =
			(uपूर्णांक64_t *)(qpd->cwsr_kaddr + KFD_CWSR_TMA_OFFSET);
		पंचांगa[0] = tba_addr;
		पंचांगa[1] = पंचांगa_addr;
	पूर्ण अन्यथा अणु
		/* No trap handler bound, bind as first-level TBA/TMA. */
		qpd->tba_addr = tba_addr;
		qpd->पंचांगa_addr = पंचांगa_addr;
	पूर्ण
पूर्ण

/*
 * On वापस the kfd_process is fully operational and will be मुक्तd when the
 * mm is released
 */
अटल काष्ठा kfd_process *create_process(स्थिर काष्ठा task_काष्ठा *thपढ़ो)
अणु
	काष्ठा kfd_process *process;
	काष्ठा mmu_notअगरier *mn;
	पूर्णांक err = -ENOMEM;

	process = kzalloc(माप(*process), GFP_KERNEL);
	अगर (!process)
		जाओ err_alloc_process;

	kref_init(&process->ref);
	mutex_init(&process->mutex);
	process->mm = thपढ़ो->mm;
	process->lead_thपढ़ो = thपढ़ो->group_leader;
	process->n_pdds = 0;
	INIT_DELAYED_WORK(&process->eviction_work, evict_process_worker);
	INIT_DELAYED_WORK(&process->restore_work, restore_process_worker);
	process->last_restore_बारtamp = get_jअगरfies_64();
	kfd_event_init_process(process);
	process->is_32bit_user_mode = in_compat_syscall();

	process->pasid = kfd_pasid_alloc();
	अगर (process->pasid == 0)
		जाओ err_alloc_pasid;

	err = pqm_init(&process->pqm, process);
	अगर (err != 0)
		जाओ err_process_pqm_init;

	/* init process apertures*/
	err = kfd_init_apertures(process);
	अगर (err != 0)
		जाओ err_init_apertures;

	/* alloc_notअगरier needs to find the process in the hash table */
	hash_add_rcu(kfd_processes_table, &process->kfd_processes,
			(uपूर्णांकptr_t)process->mm);

	/* MMU notअगरier registration must be the last call that can fail
	 * because after this poपूर्णांक we cannot unwind the process creation.
	 * After this poपूर्णांक, mmu_notअगरier_put will trigger the cleanup by
	 * dropping the last process reference in the मुक्त_notअगरier.
	 */
	mn = mmu_notअगरier_get(&kfd_process_mmu_notअगरier_ops, process->mm);
	अगर (IS_ERR(mn)) अणु
		err = PTR_ERR(mn);
		जाओ err_रेजिस्टर_notअगरier;
	पूर्ण
	BUG_ON(mn != &process->mmu_notअगरier);

	get_task_काष्ठा(process->lead_thपढ़ो);

	वापस process;

err_रेजिस्टर_notअगरier:
	hash_del_rcu(&process->kfd_processes);
	kfd_process_मुक्त_outstanding_kfd_bos(process);
	kfd_process_destroy_pdds(process);
err_init_apertures:
	pqm_uninit(&process->pqm);
err_process_pqm_init:
	kfd_pasid_मुक्त(process->pasid);
err_alloc_pasid:
	mutex_destroy(&process->mutex);
	kमुक्त(process);
err_alloc_process:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक init_करोorbell_biपंचांगap(काष्ठा qcm_process_device *qpd,
			काष्ठा kfd_dev *dev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक range_start = dev->shared_resources.non_cp_करोorbells_start;
	पूर्णांक range_end = dev->shared_resources.non_cp_करोorbells_end;

	अगर (!KFD_IS_SOC15(dev->device_info->asic_family))
		वापस 0;

	qpd->करोorbell_biपंचांगap =
		kzalloc(DIV_ROUND_UP(KFD_MAX_NUM_OF_QUEUES_PER_PROCESS,
				     BITS_PER_BYTE), GFP_KERNEL);
	अगर (!qpd->करोorbell_biपंचांगap)
		वापस -ENOMEM;

	/* Mask out करोorbells reserved क्रम SDMA, IH, and VCN on SOC15. */
	pr_debug("reserved doorbell 0x%03x - 0x%03x\n", range_start, range_end);
	pr_debug("reserved doorbell 0x%03x - 0x%03x\n",
			range_start + KFD_QUEUE_DOORBELL_MIRROR_OFFSET,
			range_end + KFD_QUEUE_DOORBELL_MIRROR_OFFSET);

	क्रम (i = 0; i < KFD_MAX_NUM_OF_QUEUES_PER_PROCESS / 2; i++) अणु
		अगर (i >= range_start && i <= range_end) अणु
			set_bit(i, qpd->करोorbell_biपंचांगap);
			set_bit(i + KFD_QUEUE_DOORBELL_MIRROR_OFFSET,
				qpd->करोorbell_biपंचांगap);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा kfd_process_device *kfd_get_process_device_data(काष्ठा kfd_dev *dev,
							काष्ठा kfd_process *p)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < p->n_pdds; i++)
		अगर (p->pdds[i]->dev == dev)
			वापस p->pdds[i];

	वापस शून्य;
पूर्ण

काष्ठा kfd_process_device *kfd_create_process_device_data(काष्ठा kfd_dev *dev,
							काष्ठा kfd_process *p)
अणु
	काष्ठा kfd_process_device *pdd = शून्य;

	अगर (WARN_ON_ONCE(p->n_pdds >= MAX_GPU_INSTANCE))
		वापस शून्य;
	pdd = kzalloc(माप(*pdd), GFP_KERNEL);
	अगर (!pdd)
		वापस शून्य;

	अगर (kfd_alloc_process_करोorbells(dev, &pdd->करोorbell_index) < 0) अणु
		pr_err("Failed to alloc doorbell for pdd\n");
		जाओ err_मुक्त_pdd;
	पूर्ण

	अगर (init_करोorbell_biपंचांगap(&pdd->qpd, dev)) अणु
		pr_err("Failed to init doorbell for process\n");
		जाओ err_मुक्त_pdd;
	पूर्ण

	pdd->dev = dev;
	INIT_LIST_HEAD(&pdd->qpd.queues_list);
	INIT_LIST_HEAD(&pdd->qpd.priv_queue_list);
	pdd->qpd.dqm = dev->dqm;
	pdd->qpd.pqm = &p->pqm;
	pdd->qpd.evicted = 0;
	pdd->qpd.mapped_gws_queue = false;
	pdd->process = p;
	pdd->bound = PDD_UNBOUND;
	pdd->alपढ़ोy_dequeued = false;
	pdd->runसमय_inuse = false;
	pdd->vram_usage = 0;
	pdd->sdma_past_activity_counter = 0;
	atomic64_set(&pdd->evict_duration_counter, 0);
	p->pdds[p->n_pdds++] = pdd;

	/* Init idr used क्रम memory handle translation */
	idr_init(&pdd->alloc_idr);

	वापस pdd;

err_मुक्त_pdd:
	kमुक्त(pdd);
	वापस शून्य;
पूर्ण

/**
 * kfd_process_device_init_vm - Initialize a VM क्रम a process-device
 *
 * @pdd: The process-device
 * @drm_file: Optional poपूर्णांकer to a DRM file descriptor
 *
 * If @drm_file is specअगरied, it will be used to acquire the VM from
 * that file descriptor. If successful, the @pdd takes ownership of
 * the file descriptor.
 *
 * If @drm_file is शून्य, a new VM is created.
 *
 * Returns 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक kfd_process_device_init_vm(काष्ठा kfd_process_device *pdd,
			       काष्ठा file *drm_file)
अणु
	काष्ठा kfd_process *p;
	काष्ठा kfd_dev *dev;
	पूर्णांक ret;

	अगर (!drm_file)
		वापस -EINVAL;

	अगर (pdd->vm)
		वापस -EBUSY;

	p = pdd->process;
	dev = pdd->dev;

	ret = amdgpu_amdkfd_gpuvm_acquire_process_vm(
		dev->kgd, drm_file, p->pasid,
		&pdd->vm, &p->kgd_process_info, &p->ef);
	अगर (ret) अणु
		pr_err("Failed to create process VM object\n");
		वापस ret;
	पूर्ण

	amdgpu_vm_set_task_info(pdd->vm);

	ret = kfd_process_device_reserve_ib_mem(pdd);
	अगर (ret)
		जाओ err_reserve_ib_mem;
	ret = kfd_process_device_init_cwsr_dgpu(pdd);
	अगर (ret)
		जाओ err_init_cwsr;

	pdd->drm_file = drm_file;

	वापस 0;

err_init_cwsr:
err_reserve_ib_mem:
	kfd_process_device_मुक्त_bos(pdd);
	pdd->vm = शून्य;

	वापस ret;
पूर्ण

/*
 * Direct the IOMMU to bind the process (specअगरically the pasid->mm)
 * to the device.
 * Unbinding occurs when the process dies or the device is हटाओd.
 *
 * Assumes that the process lock is held.
 */
काष्ठा kfd_process_device *kfd_bind_process_to_device(काष्ठा kfd_dev *dev,
							काष्ठा kfd_process *p)
अणु
	काष्ठा kfd_process_device *pdd;
	पूर्णांक err;

	pdd = kfd_get_process_device_data(dev, p);
	अगर (!pdd) अणु
		pr_err("Process device data doesn't exist\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (!pdd->vm)
		वापस ERR_PTR(-ENODEV);

	/*
	 * संकेत runसमय-pm प्रणाली to स्वतः resume and prevent
	 * further runसमय suspend once device pdd is created until
	 * pdd is destroyed.
	 */
	अगर (!pdd->runसमय_inuse) अणु
		err = pm_runसमय_get_sync(dev->ddev->dev);
		अगर (err < 0) अणु
			pm_runसमय_put_स्वतःsuspend(dev->ddev->dev);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	err = kfd_iommu_bind_process_to_device(pdd);
	अगर (err)
		जाओ out;

	/*
	 * make sure that runसमय_usage counter is incremented just once
	 * per pdd
	 */
	pdd->runसमय_inuse = true;

	वापस pdd;

out:
	/* balance runpm reference count and निकास with error */
	अगर (!pdd->runसमय_inuse) अणु
		pm_runसमय_mark_last_busy(dev->ddev->dev);
		pm_runसमय_put_स्वतःsuspend(dev->ddev->dev);
	पूर्ण

	वापस ERR_PTR(err);
पूर्ण

/* Create specअगरic handle mapped to mem from process local memory idr
 * Assumes that the process lock is held.
 */
पूर्णांक kfd_process_device_create_obj_handle(काष्ठा kfd_process_device *pdd,
					व्योम *mem)
अणु
	वापस idr_alloc(&pdd->alloc_idr, mem, 0, 0, GFP_KERNEL);
पूर्ण

/* Translate specअगरic handle from process local memory idr
 * Assumes that the process lock is held.
 */
व्योम *kfd_process_device_translate_handle(काष्ठा kfd_process_device *pdd,
					पूर्णांक handle)
अणु
	अगर (handle < 0)
		वापस शून्य;

	वापस idr_find(&pdd->alloc_idr, handle);
पूर्ण

/* Remove specअगरic handle from process local memory idr
 * Assumes that the process lock is held.
 */
व्योम kfd_process_device_हटाओ_obj_handle(काष्ठा kfd_process_device *pdd,
					पूर्णांक handle)
अणु
	अगर (handle >= 0)
		idr_हटाओ(&pdd->alloc_idr, handle);
पूर्ण

/* This increments the process->ref counter. */
काष्ठा kfd_process *kfd_lookup_process_by_pasid(u32 pasid)
अणु
	काष्ठा kfd_process *p, *ret_p = शून्य;
	अचिन्हित पूर्णांक temp;

	पूर्णांक idx = srcu_पढ़ो_lock(&kfd_processes_srcu);

	hash_क्रम_each_rcu(kfd_processes_table, temp, p, kfd_processes) अणु
		अगर (p->pasid == pasid) अणु
			kref_get(&p->ref);
			ret_p = p;
			अवरोध;
		पूर्ण
	पूर्ण

	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);

	वापस ret_p;
पूर्ण

/* This increments the process->ref counter. */
काष्ठा kfd_process *kfd_lookup_process_by_mm(स्थिर काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा kfd_process *p;

	पूर्णांक idx = srcu_पढ़ो_lock(&kfd_processes_srcu);

	p = find_process_by_mm(mm);
	अगर (p)
		kref_get(&p->ref);

	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);

	वापस p;
पूर्ण

/* kfd_process_evict_queues - Evict all user queues of a process
 *
 * Eviction is reference-counted per process-device. This means multiple
 * evictions from dअगरferent sources can be nested safely.
 */
पूर्णांक kfd_process_evict_queues(काष्ठा kfd_process *p)
अणु
	पूर्णांक r = 0;
	पूर्णांक i;
	अचिन्हित पूर्णांक n_evicted = 0;

	क्रम (i = 0; i < p->n_pdds; i++) अणु
		काष्ठा kfd_process_device *pdd = p->pdds[i];

		r = pdd->dev->dqm->ops.evict_process_queues(pdd->dev->dqm,
							    &pdd->qpd);
		अगर (r) अणु
			pr_err("Failed to evict process queues\n");
			जाओ fail;
		पूर्ण
		n_evicted++;
	पूर्ण

	वापस r;

fail:
	/* To keep state consistent, roll back partial eviction by
	 * restoring queues
	 */
	क्रम (i = 0; i < p->n_pdds; i++) अणु
		काष्ठा kfd_process_device *pdd = p->pdds[i];

		अगर (n_evicted == 0)
			अवरोध;
		अगर (pdd->dev->dqm->ops.restore_process_queues(pdd->dev->dqm,
							      &pdd->qpd))
			pr_err("Failed to restore queues\n");

		n_evicted--;
	पूर्ण

	वापस r;
पूर्ण

/* kfd_process_restore_queues - Restore all user queues of a process */
पूर्णांक kfd_process_restore_queues(काष्ठा kfd_process *p)
अणु
	पूर्णांक r, ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < p->n_pdds; i++) अणु
		काष्ठा kfd_process_device *pdd = p->pdds[i];

		r = pdd->dev->dqm->ops.restore_process_queues(pdd->dev->dqm,
							      &pdd->qpd);
		अगर (r) अणु
			pr_err("Failed to restore process queues\n");
			अगर (!ret)
				ret = r;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम evict_process_worker(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा kfd_process *p;
	काष्ठा delayed_work *dwork;

	dwork = to_delayed_work(work);

	/* Process termination destroys this worker thपढ़ो. So during the
	 * lअगरeसमय of this thपढ़ो, kfd_process p will be valid
	 */
	p = container_of(dwork, काष्ठा kfd_process, eviction_work);
	WARN_ONCE(p->last_eviction_seqno != p->ef->seqno,
		  "Eviction fence mismatch\n");

	/* Narrow winकरोw of overlap between restore and evict work
	 * item is possible. Once amdgpu_amdkfd_gpuvm_restore_process_bos
	 * unreserves KFD BOs, it is possible to evicted again. But
	 * restore has few more steps of finish. So lets रुको क्रम any
	 * previous restore work to complete
	 */
	flush_delayed_work(&p->restore_work);

	pr_debug("Started evicting pasid 0x%x\n", p->pasid);
	ret = kfd_process_evict_queues(p);
	अगर (!ret) अणु
		dma_fence_संकेत(p->ef);
		dma_fence_put(p->ef);
		p->ef = शून्य;
		queue_delayed_work(kfd_restore_wq, &p->restore_work,
				msecs_to_jअगरfies(PROCESS_RESTORE_TIME_MS));

		pr_debug("Finished evicting pasid 0x%x\n", p->pasid);
	पूर्ण अन्यथा
		pr_err("Failed to evict queues of pasid 0x%x\n", p->pasid);
पूर्ण

अटल व्योम restore_process_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा kfd_process *p;
	पूर्णांक ret = 0;

	dwork = to_delayed_work(work);

	/* Process termination destroys this worker thपढ़ो. So during the
	 * lअगरeसमय of this thपढ़ो, kfd_process p will be valid
	 */
	p = container_of(dwork, काष्ठा kfd_process, restore_work);
	pr_debug("Started restoring pasid 0x%x\n", p->pasid);

	/* Setting last_restore_बारtamp beक्रमe successful restoration.
	 * Otherwise this would have to be set by KGD (restore_process_bos)
	 * beक्रमe KFD BOs are unreserved. If not, the process can be evicted
	 * again beक्रमe the बारtamp is set.
	 * If restore fails, the बारtamp will be set again in the next
	 * attempt. This would mean that the minimum GPU quanta would be
	 * PROCESS_ACTIVE_TIME_MS - (समय to execute the following two
	 * functions)
	 */

	p->last_restore_बारtamp = get_jअगरfies_64();
	ret = amdgpu_amdkfd_gpuvm_restore_process_bos(p->kgd_process_info,
						     &p->ef);
	अगर (ret) अणु
		pr_debug("Failed to restore BOs of pasid 0x%x, retry after %d ms\n",
			 p->pasid, PROCESS_BACK_OFF_TIME_MS);
		ret = queue_delayed_work(kfd_restore_wq, &p->restore_work,
				msecs_to_jअगरfies(PROCESS_BACK_OFF_TIME_MS));
		WARN(!ret, "reschedule restore work failed\n");
		वापस;
	पूर्ण

	ret = kfd_process_restore_queues(p);
	अगर (!ret)
		pr_debug("Finished restoring pasid 0x%x\n", p->pasid);
	अन्यथा
		pr_err("Failed to restore queues of pasid 0x%x\n", p->pasid);
पूर्ण

व्योम kfd_suspend_all_processes(व्योम)
अणु
	काष्ठा kfd_process *p;
	अचिन्हित पूर्णांक temp;
	पूर्णांक idx = srcu_पढ़ो_lock(&kfd_processes_srcu);

	WARN(debug_evictions, "Evicting all processes");
	hash_क्रम_each_rcu(kfd_processes_table, temp, p, kfd_processes) अणु
		cancel_delayed_work_sync(&p->eviction_work);
		cancel_delayed_work_sync(&p->restore_work);

		अगर (kfd_process_evict_queues(p))
			pr_err("Failed to suspend process 0x%x\n", p->pasid);
		dma_fence_संकेत(p->ef);
		dma_fence_put(p->ef);
		p->ef = शून्य;
	पूर्ण
	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);
पूर्ण

पूर्णांक kfd_resume_all_processes(व्योम)
अणु
	काष्ठा kfd_process *p;
	अचिन्हित पूर्णांक temp;
	पूर्णांक ret = 0, idx = srcu_पढ़ो_lock(&kfd_processes_srcu);

	hash_क्रम_each_rcu(kfd_processes_table, temp, p, kfd_processes) अणु
		अगर (!queue_delayed_work(kfd_restore_wq, &p->restore_work, 0)) अणु
			pr_err("Restore process %d failed during resume\n",
			       p->pasid);
			ret = -EFAULT;
		पूर्ण
	पूर्ण
	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);
	वापस ret;
पूर्ण

पूर्णांक kfd_reserved_mem_mmap(काष्ठा kfd_dev *dev, काष्ठा kfd_process *process,
			  काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा kfd_process_device *pdd;
	काष्ठा qcm_process_device *qpd;

	अगर ((vma->vm_end - vma->vm_start) != KFD_CWSR_TBA_TMA_SIZE) अणु
		pr_err("Incorrect CWSR mapping size.\n");
		वापस -EINVAL;
	पूर्ण

	pdd = kfd_get_process_device_data(dev, process);
	अगर (!pdd)
		वापस -EINVAL;
	qpd = &pdd->qpd;

	qpd->cwsr_kaddr = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					get_order(KFD_CWSR_TBA_TMA_SIZE));
	अगर (!qpd->cwsr_kaddr) अणु
		pr_err("Error allocating per process CWSR buffer.\n");
		वापस -ENOMEM;
	पूर्ण

	vma->vm_flags |= VM_IO | VM_DONTCOPY | VM_DONTEXPAND
		| VM_NORESERVE | VM_DONTDUMP | VM_PFNMAP;
	/* Mapping pages to user process */
	वापस remap_pfn_range(vma, vma->vm_start,
			       PFN_DOWN(__pa(qpd->cwsr_kaddr)),
			       KFD_CWSR_TBA_TMA_SIZE, vma->vm_page_prot);
पूर्ण

व्योम kfd_flush_tlb(काष्ठा kfd_process_device *pdd)
अणु
	काष्ठा kfd_dev *dev = pdd->dev;

	अगर (dev->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS) अणु
		/* Nothing to flush until a VMID is asचिन्हित, which
		 * only happens when the first queue is created.
		 */
		अगर (pdd->qpd.vmid)
			amdgpu_amdkfd_flush_gpu_tlb_vmid(dev->kgd,
							pdd->qpd.vmid);
	पूर्ण अन्यथा अणु
		amdgpu_amdkfd_flush_gpu_tlb_pasid(dev->kgd,
						pdd->process->pasid);
	पूर्ण
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

पूर्णांक kfd_debugfs_mqds_by_process(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा kfd_process *p;
	अचिन्हित पूर्णांक temp;
	पूर्णांक r = 0;

	पूर्णांक idx = srcu_पढ़ो_lock(&kfd_processes_srcu);

	hash_क्रम_each_rcu(kfd_processes_table, temp, p, kfd_processes) अणु
		seq_म_लिखो(m, "Process %d PASID 0x%x:\n",
			   p->lead_thपढ़ो->tgid, p->pasid);

		mutex_lock(&p->mutex);
		r = pqm_debugfs_mqds(m, &p->pqm);
		mutex_unlock(&p->mutex);

		अगर (r)
			अवरोध;
	पूर्ण

	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);

	वापस r;
पूर्ण

#पूर्ण_अगर

