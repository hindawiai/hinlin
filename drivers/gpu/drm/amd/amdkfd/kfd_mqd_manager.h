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

#अगर_अघोषित KFD_MQD_MANAGER_H_
#घोषणा KFD_MQD_MANAGER_H_

#समावेश "kfd_priv.h"

#घोषणा KFD_MAX_NUM_SE 8

/**
 * काष्ठा mqd_manager
 *
 * @init_mqd: Allocates the mqd buffer on local gpu memory and initialize it.
 *
 * @load_mqd: Loads the mqd to a concrete hqd slot. Used only क्रम no cp
 * scheduling mode.
 *
 * @update_mqd: Handles a update call क्रम the MQD
 *
 * @destroy_mqd: Destroys the HQD slot and by that preempt the relevant queue.
 * Used only क्रम no cp scheduling.
 *
 * @मुक्त_mqd: Releases the mqd buffer from local gpu memory.
 *
 * @is_occupied: Checks अगर the relevant HQD slot is occupied.
 *
 * @get_wave_state: Retrieves context save state and optionally copies the
 * control stack, अगर kept in the MQD, to the given userspace address.
 *
 * @mqd_mutex: Mqd manager mutex.
 *
 * @dev: The kfd device काष्ठाure coupled with this module.
 *
 * MQD stands क्रम Memory Queue Descriptor which represents the current queue
 * state in the memory and initiate the HQD (Hardware Queue Descriptor) state.
 * This काष्ठाure is actually a base class क्रम the dअगरferent types of MQDs
 * काष्ठाures क्रम the variant ASICs that should be supported in the future.
 * This base class is also contains all the MQD specअगरic operations.
 * Another important thing to mention is that each queue has a MQD that keeps
 * his state (or context) after each preemption or reassignment.
 * Basically there are a instances of the mqd manager class per MQD type per
 * ASIC. Currently the kfd driver supports only Kaveri so there are instances
 * per KFD_MQD_TYPE क्रम each device.
 *
 */
बाह्य पूर्णांक pipe_priority_map[];
काष्ठा mqd_manager अणु
	काष्ठा kfd_mem_obj*	(*allocate_mqd)(काष्ठा kfd_dev *kfd,
		काष्ठा queue_properties *q);

	व्योम	(*init_mqd)(काष्ठा mqd_manager *mm, व्योम **mqd,
			काष्ठा kfd_mem_obj *mqd_mem_obj, uपूर्णांक64_t *gart_addr,
			काष्ठा queue_properties *q);

	पूर्णांक	(*load_mqd)(काष्ठा mqd_manager *mm, व्योम *mqd,
				uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
				काष्ठा queue_properties *p,
				काष्ठा mm_काष्ठा *mms);

	व्योम	(*update_mqd)(काष्ठा mqd_manager *mm, व्योम *mqd,
				काष्ठा queue_properties *q);

	पूर्णांक	(*destroy_mqd)(काष्ठा mqd_manager *mm, व्योम *mqd,
				क्रमागत kfd_preempt_type type,
				अचिन्हित पूर्णांक समयout, uपूर्णांक32_t pipe_id,
				uपूर्णांक32_t queue_id);

	व्योम	(*मुक्त_mqd)(काष्ठा mqd_manager *mm, व्योम *mqd,
				काष्ठा kfd_mem_obj *mqd_mem_obj);

	bool	(*is_occupied)(काष्ठा mqd_manager *mm, व्योम *mqd,
				uपूर्णांक64_t queue_address,	uपूर्णांक32_t pipe_id,
				uपूर्णांक32_t queue_id);

	पूर्णांक	(*get_wave_state)(काष्ठा mqd_manager *mm, व्योम *mqd,
				  व्योम __user *ctl_stack,
				  u32 *ctl_stack_used_size,
				  u32 *save_area_used_size);

#अगर defined(CONFIG_DEBUG_FS)
	पूर्णांक	(*debugfs_show_mqd)(काष्ठा seq_file *m, व्योम *data);
#पूर्ण_अगर
	uपूर्णांक32_t (*पढ़ो_करोorbell_id)(व्योम *mqd);

	काष्ठा mutex	mqd_mutex;
	काष्ठा kfd_dev	*dev;
	uपूर्णांक32_t mqd_size;
पूर्ण;

काष्ठा kfd_mem_obj *allocate_hiq_mqd(काष्ठा kfd_dev *dev,
				काष्ठा queue_properties *q);

काष्ठा kfd_mem_obj *allocate_sdma_mqd(काष्ठा kfd_dev *dev,
					काष्ठा queue_properties *q);
व्योम मुक्त_mqd_hiq_sdma(काष्ठा mqd_manager *mm, व्योम *mqd,
				काष्ठा kfd_mem_obj *mqd_mem_obj);

व्योम mqd_symmetrically_map_cu_mask(काष्ठा mqd_manager *mm,
		स्थिर uपूर्णांक32_t *cu_mask, uपूर्णांक32_t cu_mask_count,
		uपूर्णांक32_t *se_mask);

#पूर्ण_अगर /* KFD_MQD_MANAGER_H_ */
