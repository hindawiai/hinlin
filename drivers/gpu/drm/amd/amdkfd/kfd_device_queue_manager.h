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

#अगर_अघोषित KFD_DEVICE_QUEUE_MANAGER_H_
#घोषणा KFD_DEVICE_QUEUE_MANAGER_H_

#समावेश <linux/rwsem.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched/mm.h>
#समावेश "kfd_priv.h"
#समावेश "kfd_mqd_manager.h"


#घोषणा VMID_NUM 16

काष्ठा device_process_node अणु
	काष्ठा qcm_process_device *qpd;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा device_queue_manager_ops
 *
 * @create_queue: Queue creation routine.
 *
 * @destroy_queue: Queue deकाष्ठाion routine.
 *
 * @update_queue: Queue update routine.
 *
 * @exeute_queues: Dispatches the queues list to the H/W.
 *
 * @रेजिस्टर_process: This routine associates a specअगरic process with device.
 *
 * @unरेजिस्टर_process: destroys the associations between process to device.
 *
 * @initialize: Initializes the pipelines and memory module क्रम that device.
 *
 * @start: Initializes the resources/modules the the device needs क्रम queues
 * execution. This function is called on device initialization and after the
 * प्रणाली woke up after suspension.
 *
 * @stop: This routine stops execution of all the active queue running on the
 * H/W and basically this function called on प्रणाली suspend.
 *
 * @uninitialize: Destroys all the device queue manager resources allocated in
 * initialize routine.
 *
 * @create_kernel_queue: Creates kernel queue. Used क्रम debug queue.
 *
 * @destroy_kernel_queue: Destroys kernel queue. Used क्रम debug queue.
 *
 * @set_cache_memory_policy: Sets memory policy (cached/ non cached) क्रम the
 * memory apertures.
 *
 * @process_termination: Clears all process queues beदीर्घs to that device.
 *
 * @evict_process_queues: Evict all active queues of a process
 *
 * @restore_process_queues: Restore all evicted queues queues of a process
 *
 * @get_wave_state: Retrieves context save state and optionally copies the
 * control stack, अगर kept in the MQD, to the given userspace address.
 */

काष्ठा device_queue_manager_ops अणु
	पूर्णांक	(*create_queue)(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q,
				काष्ठा qcm_process_device *qpd);

	पूर्णांक	(*destroy_queue)(काष्ठा device_queue_manager *dqm,
				काष्ठा qcm_process_device *qpd,
				काष्ठा queue *q);

	पूर्णांक	(*update_queue)(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q);

	पूर्णांक	(*रेजिस्टर_process)(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd);

	पूर्णांक	(*unरेजिस्टर_process)(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd);

	पूर्णांक	(*initialize)(काष्ठा device_queue_manager *dqm);
	पूर्णांक	(*start)(काष्ठा device_queue_manager *dqm);
	पूर्णांक	(*stop)(काष्ठा device_queue_manager *dqm);
	व्योम	(*pre_reset)(काष्ठा device_queue_manager *dqm);
	व्योम	(*uninitialize)(काष्ठा device_queue_manager *dqm);
	पूर्णांक	(*create_kernel_queue)(काष्ठा device_queue_manager *dqm,
					काष्ठा kernel_queue *kq,
					काष्ठा qcm_process_device *qpd);

	व्योम	(*destroy_kernel_queue)(काष्ठा device_queue_manager *dqm,
					काष्ठा kernel_queue *kq,
					काष्ठा qcm_process_device *qpd);

	bool	(*set_cache_memory_policy)(काष्ठा device_queue_manager *dqm,
					   काष्ठा qcm_process_device *qpd,
					   क्रमागत cache_policy शेष_policy,
					   क्रमागत cache_policy alternate_policy,
					   व्योम __user *alternate_aperture_base,
					   uपूर्णांक64_t alternate_aperture_size);

	पूर्णांक (*process_termination)(काष्ठा device_queue_manager *dqm,
			काष्ठा qcm_process_device *qpd);

	पूर्णांक (*evict_process_queues)(काष्ठा device_queue_manager *dqm,
				    काष्ठा qcm_process_device *qpd);
	पूर्णांक (*restore_process_queues)(काष्ठा device_queue_manager *dqm,
				      काष्ठा qcm_process_device *qpd);

	पूर्णांक	(*get_wave_state)(काष्ठा device_queue_manager *dqm,
				  काष्ठा queue *q,
				  व्योम __user *ctl_stack,
				  u32 *ctl_stack_used_size,
				  u32 *save_area_used_size);
पूर्ण;

काष्ठा device_queue_manager_asic_ops अणु
	पूर्णांक	(*update_qpd)(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd);
	bool	(*set_cache_memory_policy)(काष्ठा device_queue_manager *dqm,
					   काष्ठा qcm_process_device *qpd,
					   क्रमागत cache_policy शेष_policy,
					   क्रमागत cache_policy alternate_policy,
					   व्योम __user *alternate_aperture_base,
					   uपूर्णांक64_t alternate_aperture_size);
	व्योम	(*init_sdma_vm)(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q,
				काष्ठा qcm_process_device *qpd);
	काष्ठा mqd_manager *	(*mqd_manager_init)(क्रमागत KFD_MQD_TYPE type,
				 काष्ठा kfd_dev *dev);
पूर्ण;

/**
 * काष्ठा device_queue_manager
 *
 * This काष्ठा is a base class क्रम the kfd queues scheduler in the
 * device level. The device base class should expose the basic operations
 * क्रम queue creation and queue deकाष्ठाion. This base class hides the
 * scheduling mode of the driver and the specअगरic implementation of the
 * concrete device. This class is the only class in the queues scheduler
 * that configures the H/W.
 *
 */

काष्ठा device_queue_manager अणु
	काष्ठा device_queue_manager_ops ops;
	काष्ठा device_queue_manager_asic_ops asic_ops;

	काष्ठा mqd_manager	*mqd_mgrs[KFD_MQD_TYPE_MAX];
	काष्ठा packet_manager	packets;
	काष्ठा kfd_dev		*dev;
	काष्ठा mutex		lock_hidden; /* use dqm_lock/unlock(dqm) */
	काष्ठा list_head	queues;
	अचिन्हित पूर्णांक		saved_flags;
	अचिन्हित पूर्णांक		processes_count;
	अचिन्हित पूर्णांक		active_queue_count;
	अचिन्हित पूर्णांक		active_cp_queue_count;
	अचिन्हित पूर्णांक		gws_queue_count;
	अचिन्हित पूर्णांक		total_queue_count;
	अचिन्हित पूर्णांक		next_pipe_to_allocate;
	अचिन्हित पूर्णांक		*allocated_queues;
	uपूर्णांक64_t		sdma_biपंचांगap;
	uपूर्णांक64_t		xgmi_sdma_biपंचांगap;
	/* the pasid mapping क्रम each kfd vmid */
	uपूर्णांक16_t		vmid_pasid[VMID_NUM];
	uपूर्णांक64_t		pipelines_addr;
	uपूर्णांक64_t		fence_gpu_addr;
	uपूर्णांक64_t		*fence_addr;
	काष्ठा kfd_mem_obj	*fence_mem;
	bool			active_runlist;
	पूर्णांक			sched_policy;

	/* hw exception  */
	bool			is_hws_hang;
	bool			is_resetting;
	काष्ठा work_काष्ठा	hw_exception_work;
	काष्ठा kfd_mem_obj	hiq_sdma_mqd;
	bool			sched_running;
पूर्ण;

व्योम device_queue_manager_init_cik(
		काष्ठा device_queue_manager_asic_ops *asic_ops);
व्योम device_queue_manager_init_cik_hawaii(
		काष्ठा device_queue_manager_asic_ops *asic_ops);
व्योम device_queue_manager_init_vi(
		काष्ठा device_queue_manager_asic_ops *asic_ops);
व्योम device_queue_manager_init_vi_tonga(
		काष्ठा device_queue_manager_asic_ops *asic_ops);
व्योम device_queue_manager_init_v9(
		काष्ठा device_queue_manager_asic_ops *asic_ops);
व्योम device_queue_manager_init_v10_navi10(
		काष्ठा device_queue_manager_asic_ops *asic_ops);
व्योम program_sh_mem_settings(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd);
अचिन्हित पूर्णांक get_cp_queues_num(काष्ठा device_queue_manager *dqm);
अचिन्हित पूर्णांक get_queues_per_pipe(काष्ठा device_queue_manager *dqm);
अचिन्हित पूर्णांक get_pipes_per_mec(काष्ठा device_queue_manager *dqm);
अचिन्हित पूर्णांक get_num_sdma_queues(काष्ठा device_queue_manager *dqm);
अचिन्हित पूर्णांक get_num_xgmi_sdma_queues(काष्ठा device_queue_manager *dqm);

अटल अंतरभूत अचिन्हित पूर्णांक get_sh_mem_bases_32(काष्ठा kfd_process_device *pdd)
अणु
	वापस (pdd->lds_base >> 16) & 0xFF;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
get_sh_mem_bases_nybble_64(काष्ठा kfd_process_device *pdd)
अणु
	वापस (pdd->lds_base >> 60) & 0x0E;
पूर्ण

/* The DQM lock can be taken in MMU notअगरiers. Make sure no reclaim-FS
 * happens जबतक holding this lock anywhere to prevent deadlocks when
 * an MMU notअगरier runs in reclaim-FS context.
 */
अटल अंतरभूत व्योम dqm_lock(काष्ठा device_queue_manager *dqm)
अणु
	mutex_lock(&dqm->lock_hidden);
	dqm->saved_flags = meदो_स्मृति_noreclaim_save();
पूर्ण
अटल अंतरभूत व्योम dqm_unlock(काष्ठा device_queue_manager *dqm)
अणु
	meदो_स्मृति_noreclaim_restore(dqm->saved_flags);
	mutex_unlock(&dqm->lock_hidden);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_sdma_queue_counter(uपूर्णांक64_t __user *q_rptr, uपूर्णांक64_t *val)
अणु
        /*
         * SDMA activity counter is stored at queue's RPTR + 0x8 location.
         */
	वापस get_user(*val, q_rptr + 1);
पूर्ण
#पूर्ण_अगर /* KFD_DEVICE_QUEUE_MANAGER_H_ */
