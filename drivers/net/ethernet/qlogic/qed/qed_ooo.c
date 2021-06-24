<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "qed.h"
#समावेश "qed_iscsi.h"
#समावेश "qed_ll2.h"
#समावेश "qed_ooo.h"
#समावेश "qed_cxt.h"

अटल काष्ठा qed_ooo_archipelago
*qed_ooo_seek_archipelago(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ooo_info
			  *p_ooo_info,
			  u32 cid)
अणु
	u32 idx = (cid & 0xffff) - p_ooo_info->cid_base;
	काष्ठा qed_ooo_archipelago *p_archipelago;

	अगर (idx >= p_ooo_info->max_num_archipelagos)
		वापस शून्य;

	p_archipelago = &p_ooo_info->p_archipelagos_mem[idx];

	अगर (list_empty(&p_archipelago->isles_list))
		वापस शून्य;

	वापस p_archipelago;
पूर्ण

अटल काष्ठा qed_ooo_isle *qed_ooo_seek_isle(काष्ठा qed_hwfn *p_hwfn,
					      काष्ठा qed_ooo_info *p_ooo_info,
					      u32 cid, u8 isle)
अणु
	काष्ठा qed_ooo_archipelago *p_archipelago = शून्य;
	काष्ठा qed_ooo_isle *p_isle = शून्य;
	u8 the_num_of_isle = 1;

	p_archipelago = qed_ooo_seek_archipelago(p_hwfn, p_ooo_info, cid);
	अगर (!p_archipelago) अणु
		DP_NOTICE(p_hwfn,
			  "Connection %d is not found in OOO list\n", cid);
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(p_isle, &p_archipelago->isles_list, list_entry) अणु
		अगर (the_num_of_isle == isle)
			वापस p_isle;
		the_num_of_isle++;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम qed_ooo_save_history_entry(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ooo_info *p_ooo_info,
				काष्ठा ooo_opaque *p_cqe)
अणु
	काष्ठा qed_ooo_history *p_history = &p_ooo_info->ooo_history;

	अगर (p_history->head_idx == p_history->num_of_cqes)
		p_history->head_idx = 0;
	p_history->p_cqes[p_history->head_idx] = *p_cqe;
	p_history->head_idx++;
पूर्ण

पूर्णांक qed_ooo_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	u16 max_num_archipelagos = 0, cid_base;
	काष्ठा qed_ooo_info *p_ooo_info;
	क्रमागत protocol_type proto;
	u16 max_num_isles = 0;
	u32 i;

	चयन (p_hwfn->hw_info.personality) अणु
	हाल QED_PCI_ISCSI:
		proto = PROTOCOLID_ISCSI;
		अवरोध;
	हाल QED_PCI_ETH_RDMA:
	हाल QED_PCI_ETH_IWARP:
		proto = PROTOCOLID_IWARP;
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn,
			  "Failed to allocate qed_ooo_info: unknown personality\n");
		वापस -EINVAL;
	पूर्ण

	max_num_archipelagos = (u16)qed_cxt_get_proto_cid_count(p_hwfn, proto,
								शून्य);
	max_num_isles = QED_MAX_NUM_ISLES + max_num_archipelagos;
	cid_base = (u16)qed_cxt_get_proto_cid_start(p_hwfn, proto);

	अगर (!max_num_archipelagos) अणु
		DP_NOTICE(p_hwfn,
			  "Failed to allocate qed_ooo_info: unknown amount of connections\n");
		वापस -EINVAL;
	पूर्ण

	p_ooo_info = kzalloc(माप(*p_ooo_info), GFP_KERNEL);
	अगर (!p_ooo_info)
		वापस -ENOMEM;

	p_ooo_info->cid_base = cid_base;
	p_ooo_info->max_num_archipelagos = max_num_archipelagos;

	INIT_LIST_HEAD(&p_ooo_info->मुक्त_buffers_list);
	INIT_LIST_HEAD(&p_ooo_info->पढ़ोy_buffers_list);
	INIT_LIST_HEAD(&p_ooo_info->मुक्त_isles_list);

	p_ooo_info->p_isles_mem = kसुस्मृति(max_num_isles,
					  माप(काष्ठा qed_ooo_isle),
					  GFP_KERNEL);
	अगर (!p_ooo_info->p_isles_mem)
		जाओ no_isles_mem;

	क्रम (i = 0; i < max_num_isles; i++) अणु
		INIT_LIST_HEAD(&p_ooo_info->p_isles_mem[i].buffers_list);
		list_add_tail(&p_ooo_info->p_isles_mem[i].list_entry,
			      &p_ooo_info->मुक्त_isles_list);
	पूर्ण

	p_ooo_info->p_archipelagos_mem =
				kसुस्मृति(max_num_archipelagos,
					माप(काष्ठा qed_ooo_archipelago),
					GFP_KERNEL);
	अगर (!p_ooo_info->p_archipelagos_mem)
		जाओ no_archipelagos_mem;

	क्रम (i = 0; i < max_num_archipelagos; i++)
		INIT_LIST_HEAD(&p_ooo_info->p_archipelagos_mem[i].isles_list);

	p_ooo_info->ooo_history.p_cqes =
				kसुस्मृति(QED_MAX_NUM_OOO_HISTORY_ENTRIES,
					माप(काष्ठा ooo_opaque),
					GFP_KERNEL);
	अगर (!p_ooo_info->ooo_history.p_cqes)
		जाओ no_history_mem;

	p_ooo_info->ooo_history.num_of_cqes = QED_MAX_NUM_OOO_HISTORY_ENTRIES;

	p_hwfn->p_ooo_info = p_ooo_info;
	वापस 0;

no_history_mem:
	kमुक्त(p_ooo_info->p_archipelagos_mem);
no_archipelagos_mem:
	kमुक्त(p_ooo_info->p_isles_mem);
no_isles_mem:
	kमुक्त(p_ooo_info);
	वापस -ENOMEM;
पूर्ण

व्योम qed_ooo_release_connection_isles(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ooo_info *p_ooo_info, u32 cid)
अणु
	काष्ठा qed_ooo_archipelago *p_archipelago;
	काष्ठा qed_ooo_buffer *p_buffer;
	काष्ठा qed_ooo_isle *p_isle;

	p_archipelago = qed_ooo_seek_archipelago(p_hwfn, p_ooo_info, cid);
	अगर (!p_archipelago)
		वापस;

	जबतक (!list_empty(&p_archipelago->isles_list)) अणु
		p_isle = list_first_entry(&p_archipelago->isles_list,
					  काष्ठा qed_ooo_isle, list_entry);

		list_del(&p_isle->list_entry);

		जबतक (!list_empty(&p_isle->buffers_list)) अणु
			p_buffer = list_first_entry(&p_isle->buffers_list,
						    काष्ठा qed_ooo_buffer,
						    list_entry);

			अगर (!p_buffer)
				अवरोध;

			list_move_tail(&p_buffer->list_entry,
				       &p_ooo_info->मुक्त_buffers_list);
		पूर्ण
		list_add_tail(&p_isle->list_entry,
			      &p_ooo_info->मुक्त_isles_list);
	पूर्ण
पूर्ण

व्योम qed_ooo_release_all_isles(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_ooo_info *p_ooo_info)
अणु
	काष्ठा qed_ooo_archipelago *p_archipelago;
	काष्ठा qed_ooo_buffer *p_buffer;
	काष्ठा qed_ooo_isle *p_isle;
	u32 i;

	क्रम (i = 0; i < p_ooo_info->max_num_archipelagos; i++) अणु
		p_archipelago = &(p_ooo_info->p_archipelagos_mem[i]);

		जबतक (!list_empty(&p_archipelago->isles_list)) अणु
			p_isle = list_first_entry(&p_archipelago->isles_list,
						  काष्ठा qed_ooo_isle,
						  list_entry);

			list_del(&p_isle->list_entry);

			जबतक (!list_empty(&p_isle->buffers_list)) अणु
				p_buffer =
				    list_first_entry(&p_isle->buffers_list,
						     काष्ठा qed_ooo_buffer,
						     list_entry);

				अगर (!p_buffer)
					अवरोध;

				list_move_tail(&p_buffer->list_entry,
					       &p_ooo_info->मुक्त_buffers_list);
			पूर्ण
			list_add_tail(&p_isle->list_entry,
				      &p_ooo_info->मुक्त_isles_list);
		पूर्ण
	पूर्ण
	अगर (!list_empty(&p_ooo_info->पढ़ोy_buffers_list))
		list_splice_tail_init(&p_ooo_info->पढ़ोy_buffers_list,
				      &p_ooo_info->मुक्त_buffers_list);
पूर्ण

व्योम qed_ooo_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	qed_ooo_release_all_isles(p_hwfn, p_hwfn->p_ooo_info);
	स_रखो(p_hwfn->p_ooo_info->ooo_history.p_cqes, 0,
	       p_hwfn->p_ooo_info->ooo_history.num_of_cqes *
	       माप(काष्ठा ooo_opaque));
	p_hwfn->p_ooo_info->ooo_history.head_idx = 0;
पूर्ण

व्योम qed_ooo_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ooo_info *p_ooo_info  = p_hwfn->p_ooo_info;
	काष्ठा qed_ooo_buffer *p_buffer;

	अगर (!p_ooo_info)
		वापस;

	qed_ooo_release_all_isles(p_hwfn, p_ooo_info);
	जबतक (!list_empty(&p_ooo_info->मुक्त_buffers_list)) अणु
		p_buffer = list_first_entry(&p_ooo_info->मुक्त_buffers_list,
					    काष्ठा qed_ooo_buffer, list_entry);

		अगर (!p_buffer)
			अवरोध;

		list_del(&p_buffer->list_entry);
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  p_buffer->rx_buffer_size,
				  p_buffer->rx_buffer_virt_addr,
				  p_buffer->rx_buffer_phys_addr);
		kमुक्त(p_buffer);
	पूर्ण

	kमुक्त(p_ooo_info->p_isles_mem);
	kमुक्त(p_ooo_info->p_archipelagos_mem);
	kमुक्त(p_ooo_info->ooo_history.p_cqes);
	kमुक्त(p_ooo_info);
	p_hwfn->p_ooo_info = शून्य;
पूर्ण

व्योम qed_ooo_put_मुक्त_buffer(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ooo_info *p_ooo_info,
			     काष्ठा qed_ooo_buffer *p_buffer)
अणु
	list_add_tail(&p_buffer->list_entry, &p_ooo_info->मुक्त_buffers_list);
पूर्ण

काष्ठा qed_ooo_buffer *qed_ooo_get_मुक्त_buffer(काष्ठा qed_hwfn *p_hwfn,
					       काष्ठा qed_ooo_info *p_ooo_info)
अणु
	काष्ठा qed_ooo_buffer *p_buffer = शून्य;

	अगर (!list_empty(&p_ooo_info->मुक्त_buffers_list)) अणु
		p_buffer = list_first_entry(&p_ooo_info->मुक्त_buffers_list,
					    काष्ठा qed_ooo_buffer, list_entry);

		list_del(&p_buffer->list_entry);
	पूर्ण

	वापस p_buffer;
पूर्ण

व्योम qed_ooo_put_पढ़ोy_buffer(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ooo_info *p_ooo_info,
			      काष्ठा qed_ooo_buffer *p_buffer, u8 on_tail)
अणु
	अगर (on_tail)
		list_add_tail(&p_buffer->list_entry,
			      &p_ooo_info->पढ़ोy_buffers_list);
	अन्यथा
		list_add(&p_buffer->list_entry,
			 &p_ooo_info->पढ़ोy_buffers_list);
पूर्ण

काष्ठा qed_ooo_buffer *qed_ooo_get_पढ़ोy_buffer(काष्ठा qed_hwfn *p_hwfn,
						काष्ठा qed_ooo_info *p_ooo_info)
अणु
	काष्ठा qed_ooo_buffer *p_buffer = शून्य;

	अगर (!list_empty(&p_ooo_info->पढ़ोy_buffers_list)) अणु
		p_buffer = list_first_entry(&p_ooo_info->पढ़ोy_buffers_list,
					    काष्ठा qed_ooo_buffer, list_entry);

		list_del(&p_buffer->list_entry);
	पूर्ण

	वापस p_buffer;
पूर्ण

व्योम qed_ooo_delete_isles(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ooo_info *p_ooo_info,
			  u32 cid, u8 drop_isle, u8 drop_size)
अणु
	काष्ठा qed_ooo_isle *p_isle = शून्य;
	u8 isle_idx;

	क्रम (isle_idx = 0; isle_idx < drop_size; isle_idx++) अणु
		p_isle = qed_ooo_seek_isle(p_hwfn, p_ooo_info, cid, drop_isle);
		अगर (!p_isle) अणु
			DP_NOTICE(p_hwfn,
				  "Isle %d is not found(cid %d)\n",
				  drop_isle, cid);
			वापस;
		पूर्ण
		अगर (list_empty(&p_isle->buffers_list))
			DP_NOTICE(p_hwfn,
				  "Isle %d is empty(cid %d)\n", drop_isle, cid);
		अन्यथा
			list_splice_tail_init(&p_isle->buffers_list,
					      &p_ooo_info->मुक्त_buffers_list);

		list_del(&p_isle->list_entry);
		p_ooo_info->cur_isles_number--;
		list_add(&p_isle->list_entry, &p_ooo_info->मुक्त_isles_list);
	पूर्ण
पूर्ण

व्योम qed_ooo_add_new_isle(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ooo_info *p_ooo_info,
			  u32 cid, u8 ooo_isle,
			  काष्ठा qed_ooo_buffer *p_buffer)
अणु
	काष्ठा qed_ooo_archipelago *p_archipelago = शून्य;
	काष्ठा qed_ooo_isle *p_prev_isle = शून्य;
	काष्ठा qed_ooo_isle *p_isle = शून्य;

	अगर (ooo_isle > 1) अणु
		p_prev_isle = qed_ooo_seek_isle(p_hwfn,
						p_ooo_info, cid, ooo_isle - 1);
		अगर (!p_prev_isle) अणु
			DP_NOTICE(p_hwfn,
				  "Isle %d is not found(cid %d)\n",
				  ooo_isle - 1, cid);
			वापस;
		पूर्ण
	पूर्ण
	p_archipelago = qed_ooo_seek_archipelago(p_hwfn, p_ooo_info, cid);
	अगर (!p_archipelago && (ooo_isle != 1)) अणु
		DP_NOTICE(p_hwfn,
			  "Connection %d is not found in OOO list\n", cid);
		वापस;
	पूर्ण

	अगर (!list_empty(&p_ooo_info->मुक्त_isles_list)) अणु
		p_isle = list_first_entry(&p_ooo_info->मुक्त_isles_list,
					  काष्ठा qed_ooo_isle, list_entry);

		list_del(&p_isle->list_entry);
		अगर (!list_empty(&p_isle->buffers_list)) अणु
			DP_NOTICE(p_hwfn, "Free isle is not empty\n");
			INIT_LIST_HEAD(&p_isle->buffers_list);
		पूर्ण
	पूर्ण अन्यथा अणु
		DP_NOTICE(p_hwfn, "No more free isles\n");
		वापस;
	पूर्ण

	अगर (!p_archipelago) अणु
		u32 idx = (cid & 0xffff) - p_ooo_info->cid_base;

		p_archipelago = &p_ooo_info->p_archipelagos_mem[idx];
	पूर्ण

	list_add(&p_buffer->list_entry, &p_isle->buffers_list);
	p_ooo_info->cur_isles_number++;
	p_ooo_info->gen_isles_number++;

	अगर (p_ooo_info->cur_isles_number > p_ooo_info->max_isles_number)
		p_ooo_info->max_isles_number = p_ooo_info->cur_isles_number;

	अगर (!p_prev_isle)
		list_add(&p_isle->list_entry, &p_archipelago->isles_list);
	अन्यथा
		list_add(&p_isle->list_entry, &p_prev_isle->list_entry);
पूर्ण

व्योम qed_ooo_add_new_buffer(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ooo_info *p_ooo_info,
			    u32 cid,
			    u8 ooo_isle,
			    काष्ठा qed_ooo_buffer *p_buffer, u8 buffer_side)
अणु
	काष्ठा qed_ooo_isle *p_isle = शून्य;

	p_isle = qed_ooo_seek_isle(p_hwfn, p_ooo_info, cid, ooo_isle);
	अगर (!p_isle) अणु
		DP_NOTICE(p_hwfn,
			  "Isle %d is not found(cid %d)\n", ooo_isle, cid);
		वापस;
	पूर्ण

	अगर (buffer_side == QED_OOO_LEFT_BUF)
		list_add(&p_buffer->list_entry, &p_isle->buffers_list);
	अन्यथा
		list_add_tail(&p_buffer->list_entry, &p_isle->buffers_list);
पूर्ण

व्योम qed_ooo_join_isles(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ooo_info *p_ooo_info, u32 cid, u8 left_isle)
अणु
	काष्ठा qed_ooo_isle *p_right_isle = शून्य;
	काष्ठा qed_ooo_isle *p_left_isle = शून्य;

	p_right_isle = qed_ooo_seek_isle(p_hwfn, p_ooo_info, cid,
					 left_isle + 1);
	अगर (!p_right_isle) अणु
		DP_NOTICE(p_hwfn,
			  "Right isle %d is not found(cid %d)\n",
			  left_isle + 1, cid);
		वापस;
	पूर्ण

	list_del(&p_right_isle->list_entry);
	p_ooo_info->cur_isles_number--;
	अगर (left_isle) अणु
		p_left_isle = qed_ooo_seek_isle(p_hwfn, p_ooo_info, cid,
						left_isle);
		अगर (!p_left_isle) अणु
			DP_NOTICE(p_hwfn,
				  "Left isle %d is not found(cid %d)\n",
				  left_isle, cid);
			वापस;
		पूर्ण
		list_splice_tail_init(&p_right_isle->buffers_list,
				      &p_left_isle->buffers_list);
	पूर्ण अन्यथा अणु
		list_splice_tail_init(&p_right_isle->buffers_list,
				      &p_ooo_info->पढ़ोy_buffers_list);
	पूर्ण
	list_add_tail(&p_right_isle->list_entry, &p_ooo_info->मुक्त_isles_list);
पूर्ण
