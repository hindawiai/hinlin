<शैली गुरु>
/*
 * Copyright (c) 2012 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 /***********************************************************/
/*This file support the handling of the Alias GUID feature. */
/***********************************************************/
#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/ib_sa.h>
#समावेश <rdma/ib_pack.h>
#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <linux/delay.h>
#समावेश "mlx4_ib.h"

/*
The driver keeps the current state of all guids, as they are in the HW.
Whenever we receive an smp mad GUIDInfo record, the data will be cached.
*/

काष्ठा mlx4_alias_guid_work_context अणु
	u8 port;
	काष्ठा mlx4_ib_dev     *dev ;
	काष्ठा ib_sa_query     *sa_query;
	काष्ठा completion	करोne;
	पूर्णांक			query_id;
	काष्ठा list_head	list;
	पूर्णांक			block_num;
	ib_sa_comp_mask		guid_indexes;
	u8			method;
पूर्ण;

काष्ठा mlx4_next_alias_guid_work अणु
	u8 port;
	u8 block_num;
	u8 method;
	काष्ठा mlx4_sriov_alias_guid_info_rec_det rec_det;
पूर्ण;

अटल पूर्णांक get_low_record_समय_index(काष्ठा mlx4_ib_dev *dev, u8 port,
				     पूर्णांक *resched_delay_sec);

व्योम mlx4_ib_update_cache_on_guid_change(काष्ठा mlx4_ib_dev *dev, पूर्णांक block_num,
					 u32 port_num, u8 *p_data)
अणु
	पूर्णांक i;
	u64 guid_indexes;
	पूर्णांक slave_id;
	u32 port_index = port_num - 1;

	अगर (!mlx4_is_master(dev->dev))
		वापस;

	guid_indexes = be64_to_cpu((__क्रमce __be64) dev->sriov.alias_guid.
				   ports_guid[port_num - 1].
				   all_rec_per_port[block_num].guid_indexes);
	pr_debug("port: %u, guid_indexes: 0x%llx\n", port_num, guid_indexes);

	क्रम (i = 0; i < NUM_ALIAS_GUID_IN_REC; i++) अणु
		/* The location of the specअगरic index starts from bit number 4
		 * until bit num 11 */
		अगर (test_bit(i + 4, (अचिन्हित दीर्घ *)&guid_indexes)) अणु
			slave_id = (block_num * NUM_ALIAS_GUID_IN_REC) + i ;
			अगर (slave_id >= dev->dev->num_slaves) अणु
				pr_debug("The last slave: %d\n", slave_id);
				वापस;
			पूर्ण

			/* cache the guid: */
			स_नकल(&dev->sriov.demux[port_index].guid_cache[slave_id],
			       &p_data[i * GUID_REC_SIZE],
			       GUID_REC_SIZE);
		पूर्ण अन्यथा
			pr_debug("Guid number: %d in block: %d"
				 " was not updated\n", i, block_num);
	पूर्ण
पूर्ण

अटल __be64 get_cached_alias_guid(काष्ठा mlx4_ib_dev *dev, पूर्णांक port, पूर्णांक index)
अणु
	अगर (index >= NUM_ALIAS_GUID_PER_PORT) अणु
		pr_err("%s: ERROR: asked for index:%d\n", __func__, index);
		वापस (__क्रमce __be64) -1;
	पूर्ण
	वापस *(__be64 *)&dev->sriov.demux[port - 1].guid_cache[index];
पूर्ण


ib_sa_comp_mask mlx4_ib_get_aguid_comp_mask_from_ix(पूर्णांक index)
अणु
	वापस IB_SA_COMP_MASK(4 + index);
पूर्ण

व्योम mlx4_ib_slave_alias_guid_event(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave,
				    पूर्णांक port,  पूर्णांक slave_init)
अणु
	__be64 curr_guid, required_guid;
	पूर्णांक record_num = slave / 8;
	पूर्णांक index = slave % 8;
	पूर्णांक port_index = port - 1;
	अचिन्हित दीर्घ flags;
	पूर्णांक करो_work = 0;

	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags);
	अगर (dev->sriov.alias_guid.ports_guid[port_index].state_flags &
	    GUID_STATE_NEED_PORT_INIT)
		जाओ unlock;
	अगर (!slave_init) अणु
		curr_guid = *(__be64 *)&dev->sriov.
			alias_guid.ports_guid[port_index].
			all_rec_per_port[record_num].
			all_recs[GUID_REC_SIZE * index];
		अगर (curr_guid == cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL) ||
		    !curr_guid)
			जाओ unlock;
		required_guid = cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL);
	पूर्ण अन्यथा अणु
		required_guid = mlx4_get_admin_guid(dev->dev, slave, port);
		अगर (required_guid == cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL))
			जाओ unlock;
	पूर्ण
	*(__be64 *)&dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].
		all_recs[GUID_REC_SIZE * index] = required_guid;
	dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].guid_indexes
		|= mlx4_ib_get_aguid_comp_mask_from_ix(index);
	dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].status
		= MLX4_GUID_INFO_STATUS_IDLE;
	/* set to run immediately */
	dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].समय_प्रकारo_run = 0;
	dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[record_num].
		guids_retry_schedule[index] = 0;
	करो_work = 1;
unlock:
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags);

	अगर (करो_work)
		mlx4_ib_init_alias_guid_work(dev, port_index);
पूर्ण

/*
 * Whenever new GUID is set/unset (guid table change) create event and
 * notअगरy the relevant slave (master also should be notअगरied).
 * If the GUID value is not as we have in the cache the slave will not be
 * updated; in this हाल it रुकोs क्रम the smp_snoop or the port management
 * event to call the function and to update the slave.
 * block_number - the index of the block (16 blocks available)
 * port_number - 1 or 2
 */
व्योम mlx4_ib_notअगरy_slaves_on_guid_change(काष्ठा mlx4_ib_dev *dev,
					  पूर्णांक block_num, u32 port_num,
					  u8 *p_data)
अणु
	पूर्णांक i;
	u64 guid_indexes;
	पूर्णांक slave_id, slave_port;
	क्रमागत slave_port_state new_state;
	क्रमागत slave_port_state prev_state;
	__be64 पंचांगp_cur_ag, क्रमm_cache_ag;
	क्रमागत slave_port_gen_event gen_event;
	काष्ठा mlx4_sriov_alias_guid_info_rec_det *rec;
	अचिन्हित दीर्घ flags;
	__be64 required_value;

	अगर (!mlx4_is_master(dev->dev))
		वापस;

	rec = &dev->sriov.alias_guid.ports_guid[port_num - 1].
			all_rec_per_port[block_num];
	guid_indexes = be64_to_cpu((__क्रमce __be64) dev->sriov.alias_guid.
				   ports_guid[port_num - 1].
				   all_rec_per_port[block_num].guid_indexes);
	pr_debug("port: %u, guid_indexes: 0x%llx\n", port_num, guid_indexes);

	/*calculate the slaves and notअगरy them*/
	क्रम (i = 0; i < NUM_ALIAS_GUID_IN_REC; i++) अणु
		/* the location of the specअगरic index runs from bits 4..11 */
		अगर (!(test_bit(i + 4, (अचिन्हित दीर्घ *)&guid_indexes)))
			जारी;

		slave_id = (block_num * NUM_ALIAS_GUID_IN_REC) + i ;
		अगर (slave_id >= dev->dev->persist->num_vfs + 1)
			वापस;

		slave_port = mlx4_phys_to_slave_port(dev->dev, slave_id, port_num);
		अगर (slave_port < 0) /* this port isn't available क्रम the VF */
			जारी;

		पंचांगp_cur_ag = *(__be64 *)&p_data[i * GUID_REC_SIZE];
		क्रमm_cache_ag = get_cached_alias_guid(dev, port_num,
					(NUM_ALIAS_GUID_IN_REC * block_num) + i);
		/*
		 * Check अगर guid is not the same as in the cache,
		 * If it is dअगरferent, रुको क्रम the snoop_smp or the port mgmt
		 * change event to update the slave on its port state change
		 */
		अगर (पंचांगp_cur_ag != क्रमm_cache_ag)
			जारी;

		spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags);
		required_value = *(__be64 *)&rec->all_recs[i * GUID_REC_SIZE];

		अगर (required_value == cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL))
			required_value = 0;

		अगर (पंचांगp_cur_ag == required_value) अणु
			rec->guid_indexes = rec->guid_indexes &
			       ~mlx4_ib_get_aguid_comp_mask_from_ix(i);
		पूर्ण अन्यथा अणु
			/* may notअगरy port करोwn अगर value is 0 */
			अगर (पंचांगp_cur_ag != MLX4_NOT_SET_GUID) अणु
				spin_unlock_irqrestore(&dev->sriov.
					alias_guid.ag_work_lock, flags);
				जारी;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock,
				       flags);
		mlx4_gen_guid_change_eqe(dev->dev, slave_id, port_num);
		/*2 हालs: Valid GUID, and Invalid Guid*/

		अगर (पंचांगp_cur_ag != MLX4_NOT_SET_GUID) अणु /*valid GUID*/
			prev_state = mlx4_get_slave_port_state(dev->dev, slave_id, port_num);
			new_state = set_and_calc_slave_port_state(dev->dev, slave_id, port_num,
								  MLX4_PORT_STATE_IB_PORT_STATE_EVENT_GID_VALID,
								  &gen_event);
			pr_debug("slave: %d, port: %u prev_port_state: %d,"
				 " new_port_state: %d, gen_event: %d\n",
				 slave_id, port_num, prev_state, new_state, gen_event);
			अगर (gen_event == SLAVE_PORT_GEN_EVENT_UP) अणु
				pr_debug("sending PORT_UP event to slave: %d, port: %u\n",
					 slave_id, port_num);
				mlx4_gen_port_state_change_eqe(dev->dev, slave_id,
							       port_num, MLX4_PORT_CHANGE_SUBTYPE_ACTIVE);
			पूर्ण
		पूर्ण अन्यथा अणु /* request to invalidate GUID */
			set_and_calc_slave_port_state(dev->dev, slave_id, port_num,
						      MLX4_PORT_STATE_IB_EVENT_GID_INVALID,
						      &gen_event);
			अगर (gen_event == SLAVE_PORT_GEN_EVENT_DOWN) अणु
				pr_debug("sending PORT DOWN event to slave: %d, port: %u\n",
					 slave_id, port_num);
				mlx4_gen_port_state_change_eqe(dev->dev,
							       slave_id,
							       port_num,
							       MLX4_PORT_CHANGE_SUBTYPE_DOWN);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम aliasguid_query_handler(पूर्णांक status,
				    काष्ठा ib_sa_guidinfo_rec *guid_rec,
				    व्योम *context)
अणु
	काष्ठा mlx4_ib_dev *dev;
	काष्ठा mlx4_alias_guid_work_context *cb_ctx = context;
	u8 port_index ;
	पूर्णांक i;
	काष्ठा mlx4_sriov_alias_guid_info_rec_det *rec;
	अचिन्हित दीर्घ flags, flags1;
	ib_sa_comp_mask declined_guid_indexes = 0;
	ib_sa_comp_mask applied_guid_indexes = 0;
	अचिन्हित पूर्णांक resched_delay_sec = 0;

	अगर (!context)
		वापस;

	dev = cb_ctx->dev;
	port_index = cb_ctx->port - 1;
	rec = &dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[cb_ctx->block_num];

	अगर (status) अणु
		pr_debug("(port: %d) failed: status = %d\n",
			 cb_ctx->port, status);
		rec->समय_प्रकारo_run = kसमय_get_bootसमय_ns() + 1 * NSEC_PER_SEC;
		जाओ out;
	पूर्ण

	अगर (guid_rec->block_num != cb_ctx->block_num) अणु
		pr_err("block num mismatch: %d != %d\n",
		       cb_ctx->block_num, guid_rec->block_num);
		जाओ out;
	पूर्ण

	pr_debug("lid/port: %d/%d, block_num: %d\n",
		 be16_to_cpu(guid_rec->lid), cb_ctx->port,
		 guid_rec->block_num);

	rec = &dev->sriov.alias_guid.ports_guid[port_index].
		all_rec_per_port[guid_rec->block_num];

	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags);
	क्रम (i = 0 ; i < NUM_ALIAS_GUID_IN_REC; i++) अणु
		__be64 sm_response, required_val;

		अगर (!(cb_ctx->guid_indexes &
			mlx4_ib_get_aguid_comp_mask_from_ix(i)))
			जारी;
		sm_response = *(__be64 *)&guid_rec->guid_info_list
				[i * GUID_REC_SIZE];
		required_val = *(__be64 *)&rec->all_recs[i * GUID_REC_SIZE];
		अगर (cb_ctx->method == MLX4_GUID_INFO_RECORD_DELETE) अणु
			अगर (required_val ==
			    cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL))
				जाओ next_entry;

			/* A new value was set till we got the response */
			pr_debug("need to set new value %llx, record num %d, block_num:%d\n",
				 be64_to_cpu(required_val),
				 i, guid_rec->block_num);
			जाओ entry_declined;
		पूर्ण

		/* check अगर the SM didn't assign one of the records.
		 * अगर it didn't, re-ask क्रम.
		 */
		अगर (sm_response == MLX4_NOT_SET_GUID) अणु
			अगर (rec->guids_retry_schedule[i] == 0)
				mlx4_ib_warn(&dev->ib_dev,
					     "%s:Record num %d in  block_num: %d was declined by SM\n",
					     __func__, i,
					     guid_rec->block_num);
			जाओ entry_declined;
		पूर्ण अन्यथा अणु
		       /* properly asचिन्हित record. */
		       /* We save the GUID we just got from the SM in the
			* admin_guid in order to be persistent, and in the
			* request from the sm the process will ask क्रम the same GUID */
			अगर (required_val &&
			    sm_response != required_val) अणु
				/* Warn only on first retry */
				अगर (rec->guids_retry_schedule[i] == 0)
					mlx4_ib_warn(&dev->ib_dev, "%s: Failed to set"
						     " admin guid after SysAdmin "
						     "configuration. "
						     "Record num %d in block_num:%d "
						     "was declined by SM, "
						     "new val(0x%llx) was kept, SM returned (0x%llx)\n",
						      __func__, i,
						     guid_rec->block_num,
						     be64_to_cpu(required_val),
						     be64_to_cpu(sm_response));
				जाओ entry_declined;
			पूर्ण अन्यथा अणु
				*(__be64 *)&rec->all_recs[i * GUID_REC_SIZE] =
					sm_response;
				अगर (required_val == 0)
					mlx4_set_admin_guid(dev->dev,
							    sm_response,
							    (guid_rec->block_num
							    * NUM_ALIAS_GUID_IN_REC) + i,
							    cb_ctx->port);
				जाओ next_entry;
			पूर्ण
		पूर्ण
entry_declined:
		declined_guid_indexes |= mlx4_ib_get_aguid_comp_mask_from_ix(i);
		rec->guids_retry_schedule[i] =
			(rec->guids_retry_schedule[i] == 0) ?  1 :
			min((अचिन्हित पूर्णांक)60,
			    rec->guids_retry_schedule[i] * 2);
		/* using the minimum value among all entries in that record */
		resched_delay_sec = (resched_delay_sec == 0) ?
				rec->guids_retry_schedule[i] :
				min(resched_delay_sec,
				    rec->guids_retry_schedule[i]);
		जारी;

next_entry:
		rec->guids_retry_schedule[i] = 0;
	पूर्ण

	applied_guid_indexes =  cb_ctx->guid_indexes & ~declined_guid_indexes;
	अगर (declined_guid_indexes ||
	    rec->guid_indexes & ~(applied_guid_indexes)) अणु
		pr_debug("record=%d wasn't fully set, guid_indexes=0x%llx applied_indexes=0x%llx, declined_indexes=0x%llx\n",
			 guid_rec->block_num,
			 be64_to_cpu((__क्रमce __be64)rec->guid_indexes),
			 be64_to_cpu((__क्रमce __be64)applied_guid_indexes),
			 be64_to_cpu((__क्रमce __be64)declined_guid_indexes));
		rec->समय_प्रकारo_run = kसमय_get_bootसमय_ns() +
			resched_delay_sec * NSEC_PER_SEC;
	पूर्ण अन्यथा अणु
		rec->status = MLX4_GUID_INFO_STATUS_SET;
	पूर्ण
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags);
	/*
	The func is call here to बंद the हालs when the
	sm करोesn't send smp, so in the sa response the driver
	notअगरies the slave.
	*/
	mlx4_ib_notअगरy_slaves_on_guid_change(dev, guid_rec->block_num,
					     cb_ctx->port,
					     guid_rec->guid_info_list);
out:
	spin_lock_irqsave(&dev->sriov.going_करोwn_lock, flags);
	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags1);
	अगर (!dev->sriov.is_going_करोwn) अणु
		get_low_record_समय_index(dev, port_index, &resched_delay_sec);
		queue_delayed_work(dev->sriov.alias_guid.ports_guid[port_index].wq,
				   &dev->sriov.alias_guid.ports_guid[port_index].
				   alias_guid_work,
				   msecs_to_jअगरfies(resched_delay_sec * 1000));
	पूर्ण
	अगर (cb_ctx->sa_query) अणु
		list_del(&cb_ctx->list);
		kमुक्त(cb_ctx);
	पूर्ण अन्यथा
		complete(&cb_ctx->करोne);
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags1);
	spin_unlock_irqrestore(&dev->sriov.going_करोwn_lock, flags);
पूर्ण

अटल व्योम invalidate_guid_record(काष्ठा mlx4_ib_dev *dev, u8 port, पूर्णांक index)
अणु
	पूर्णांक i;
	u64 cur_admin_val;
	ib_sa_comp_mask comp_mask = 0;

	dev->sriov.alias_guid.ports_guid[port - 1].all_rec_per_port[index].status
		= MLX4_GUID_INFO_STATUS_SET;

	/* calculate the comp_mask क्रम that record.*/
	क्रम (i = 0; i < NUM_ALIAS_GUID_IN_REC; i++) अणु
		cur_admin_val =
			*(u64 *)&dev->sriov.alias_guid.ports_guid[port - 1].
			all_rec_per_port[index].all_recs[GUID_REC_SIZE * i];
		/*
		check the admin value: अगर it's क्रम delete (~00LL) or
		it is the first guid of the first record (hw guid) or
		the records is not in ownership of the sysadmin and the sm करोesn't
		need to assign GUIDs, then करोn't put it up क्रम assignment.
		*/
		अगर (MLX4_GUID_FOR_DELETE_VAL == cur_admin_val ||
		    (!index && !i))
			जारी;
		comp_mask |= mlx4_ib_get_aguid_comp_mask_from_ix(i);
	पूर्ण
	dev->sriov.alias_guid.ports_guid[port - 1].
		all_rec_per_port[index].guid_indexes |= comp_mask;
	अगर (dev->sriov.alias_guid.ports_guid[port - 1].
	    all_rec_per_port[index].guid_indexes)
		dev->sriov.alias_guid.ports_guid[port - 1].
		all_rec_per_port[index].status = MLX4_GUID_INFO_STATUS_IDLE;

पूर्ण

अटल पूर्णांक set_guid_rec(काष्ठा ib_device *ibdev,
			काष्ठा mlx4_next_alias_guid_work *rec)
अणु
	पूर्णांक err;
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	काष्ठा ib_sa_guidinfo_rec guid_info_rec;
	ib_sa_comp_mask comp_mask;
	काष्ठा ib_port_attr attr;
	काष्ठा mlx4_alias_guid_work_context *callback_context;
	अचिन्हित दीर्घ resched_delay, flags, flags1;
	u8 port = rec->port + 1;
	पूर्णांक index = rec->block_num;
	काष्ठा mlx4_sriov_alias_guid_info_rec_det *rec_det = &rec->rec_det;
	काष्ठा list_head *head =
		&dev->sriov.alias_guid.ports_guid[port - 1].cb_list;

	स_रखो(&attr, 0, माप(attr));
	err = __mlx4_ib_query_port(ibdev, port, &attr, 1);
	अगर (err) अणु
		pr_debug("mlx4_ib_query_port failed (err: %d), port: %d\n",
			 err, port);
		वापस err;
	पूर्ण
	/*check the port was configured by the sm, otherwise no need to send */
	अगर (attr.state != IB_PORT_ACTIVE) अणु
		pr_debug("port %d not active...rescheduling\n", port);
		resched_delay = 5 * HZ;
		err = -EAGAIN;
		जाओ new_schedule;
	पूर्ण

	callback_context = kदो_स्मृति(माप *callback_context, GFP_KERNEL);
	अगर (!callback_context) अणु
		err = -ENOMEM;
		resched_delay = HZ * 5;
		जाओ new_schedule;
	पूर्ण
	callback_context->port = port;
	callback_context->dev = dev;
	callback_context->block_num = index;
	callback_context->guid_indexes = rec_det->guid_indexes;
	callback_context->method = rec->method;

	स_रखो(&guid_info_rec, 0, माप (काष्ठा ib_sa_guidinfo_rec));

	guid_info_rec.lid = ib_lid_be16(attr.lid);
	guid_info_rec.block_num = index;

	स_नकल(guid_info_rec.guid_info_list, rec_det->all_recs,
	       GUID_REC_SIZE * NUM_ALIAS_GUID_IN_REC);
	comp_mask = IB_SA_GUIDINFO_REC_LID | IB_SA_GUIDINFO_REC_BLOCK_NUM |
		rec_det->guid_indexes;

	init_completion(&callback_context->करोne);
	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags1);
	list_add_tail(&callback_context->list, head);
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags1);

	callback_context->query_id =
		ib_sa_guid_info_rec_query(dev->sriov.alias_guid.sa_client,
					  ibdev, port, &guid_info_rec,
					  comp_mask, rec->method, 1000,
					  GFP_KERNEL, aliasguid_query_handler,
					  callback_context,
					  &callback_context->sa_query);
	अगर (callback_context->query_id < 0) अणु
		pr_debug("ib_sa_guid_info_rec_query failed, query_id: "
			 "%d. will reschedule to the next 1 sec.\n",
			 callback_context->query_id);
		spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags1);
		list_del(&callback_context->list);
		kमुक्त(callback_context);
		spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags1);
		resched_delay = 1 * HZ;
		err = -EAGAIN;
		जाओ new_schedule;
	पूर्ण
	err = 0;
	जाओ out;

new_schedule:
	spin_lock_irqsave(&dev->sriov.going_करोwn_lock, flags);
	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags1);
	invalidate_guid_record(dev, port, index);
	अगर (!dev->sriov.is_going_करोwn) अणु
		queue_delayed_work(dev->sriov.alias_guid.ports_guid[port - 1].wq,
				   &dev->sriov.alias_guid.ports_guid[port - 1].alias_guid_work,
				   resched_delay);
	पूर्ण
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags1);
	spin_unlock_irqrestore(&dev->sriov.going_करोwn_lock, flags);

out:
	वापस err;
पूर्ण

अटल व्योम mlx4_ib_guid_port_init(काष्ठा mlx4_ib_dev *dev, पूर्णांक port)
अणु
	पूर्णांक j, k, entry;
	__be64 guid;

	/*Check अगर the SM करोesn't need to assign the GUIDs*/
	क्रम (j = 0; j < NUM_ALIAS_GUID_REC_IN_PORT; j++) अणु
		क्रम (k = 0; k < NUM_ALIAS_GUID_IN_REC; k++) अणु
			entry = j * NUM_ALIAS_GUID_IN_REC + k;
			/* no request क्रम the 0 entry (hw guid) */
			अगर (!entry || entry > dev->dev->persist->num_vfs ||
			    !mlx4_is_slave_active(dev->dev, entry))
				जारी;
			guid = mlx4_get_admin_guid(dev->dev, entry, port);
			*(__be64 *)&dev->sriov.alias_guid.ports_guid[port - 1].
				all_rec_per_port[j].all_recs
				[GUID_REC_SIZE * k] = guid;
			pr_debug("guid was set, entry=%d, val=0x%llx, port=%d\n",
				 entry,
				 be64_to_cpu(guid),
				 port);
		पूर्ण
	पूर्ण
पूर्ण
व्योम mlx4_ib_invalidate_all_guid_record(काष्ठा mlx4_ib_dev *dev, पूर्णांक port)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags, flags1;

	pr_debug("port %d\n", port);

	spin_lock_irqsave(&dev->sriov.going_करोwn_lock, flags);
	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags1);

	अगर (dev->sriov.alias_guid.ports_guid[port - 1].state_flags &
		GUID_STATE_NEED_PORT_INIT) अणु
		mlx4_ib_guid_port_init(dev, port);
		dev->sriov.alias_guid.ports_guid[port - 1].state_flags &=
			(~GUID_STATE_NEED_PORT_INIT);
	पूर्ण
	क्रम (i = 0; i < NUM_ALIAS_GUID_REC_IN_PORT; i++)
		invalidate_guid_record(dev, port, i);

	अगर (mlx4_is_master(dev->dev) && !dev->sriov.is_going_करोwn) अणु
		/*
		make sure no work रुकोs in the queue, अगर the work is alपढ़ोy
		queued(not on the समयr) the cancel will fail. That is not a problem
		because we just want the work started.
		*/
		cancel_delayed_work(&dev->sriov.alias_guid.
				      ports_guid[port - 1].alias_guid_work);
		queue_delayed_work(dev->sriov.alias_guid.ports_guid[port - 1].wq,
				   &dev->sriov.alias_guid.ports_guid[port - 1].alias_guid_work,
				   0);
	पूर्ण
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags1);
	spin_unlock_irqrestore(&dev->sriov.going_करोwn_lock, flags);
पूर्ण

अटल व्योम set_required_record(काष्ठा mlx4_ib_dev *dev, u8 port,
				काष्ठा mlx4_next_alias_guid_work *next_rec,
				पूर्णांक record_index)
अणु
	पूर्णांक i;
	पूर्णांक lowset_समय_entry = -1;
	पूर्णांक lowest_समय = 0;
	ib_sa_comp_mask delete_guid_indexes = 0;
	ib_sa_comp_mask set_guid_indexes = 0;
	काष्ठा mlx4_sriov_alias_guid_info_rec_det *rec =
			&dev->sriov.alias_guid.ports_guid[port].
			all_rec_per_port[record_index];

	क्रम (i = 0; i < NUM_ALIAS_GUID_IN_REC; i++) अणु
		अगर (!(rec->guid_indexes &
			mlx4_ib_get_aguid_comp_mask_from_ix(i)))
			जारी;

		अगर (*(__be64 *)&rec->all_recs[i * GUID_REC_SIZE] ==
				cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL))
			delete_guid_indexes |=
				mlx4_ib_get_aguid_comp_mask_from_ix(i);
		अन्यथा
			set_guid_indexes |=
				mlx4_ib_get_aguid_comp_mask_from_ix(i);

		अगर (lowset_समय_entry == -1 || rec->guids_retry_schedule[i] <=
			lowest_समय) अणु
			lowset_समय_entry = i;
			lowest_समय = rec->guids_retry_schedule[i];
		पूर्ण
	पूर्ण

	स_नकल(&next_rec->rec_det, rec, माप(*rec));
	next_rec->port = port;
	next_rec->block_num = record_index;

	अगर (*(__be64 *)&rec->all_recs[lowset_समय_entry * GUID_REC_SIZE] ==
				cpu_to_be64(MLX4_GUID_FOR_DELETE_VAL)) अणु
		next_rec->rec_det.guid_indexes = delete_guid_indexes;
		next_rec->method = MLX4_GUID_INFO_RECORD_DELETE;
	पूर्ण अन्यथा अणु
		next_rec->rec_det.guid_indexes = set_guid_indexes;
		next_rec->method = MLX4_GUID_INFO_RECORD_SET;
	पूर्ण
पूर्ण

/* वापस index of record that should be updated based on lowest
 * rescheduled समय
 */
अटल पूर्णांक get_low_record_समय_index(काष्ठा mlx4_ib_dev *dev, u8 port,
				     पूर्णांक *resched_delay_sec)
अणु
	पूर्णांक record_index = -1;
	u64 low_record_समय = 0;
	काष्ठा mlx4_sriov_alias_guid_info_rec_det rec;
	पूर्णांक j;

	क्रम (j = 0; j < NUM_ALIAS_GUID_REC_IN_PORT; j++) अणु
		rec = dev->sriov.alias_guid.ports_guid[port].
			all_rec_per_port[j];
		अगर (rec.status == MLX4_GUID_INFO_STATUS_IDLE &&
		    rec.guid_indexes) अणु
			अगर (record_index == -1 ||
			    rec.समय_प्रकारo_run < low_record_समय) अणु
				record_index = j;
				low_record_समय = rec.समय_प्रकारo_run;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (resched_delay_sec) अणु
		u64 curr_समय = kसमय_get_bootसमय_ns();

		*resched_delay_sec = (low_record_समय < curr_समय) ? 0 :
			भाग_u64((low_record_समय - curr_समय), NSEC_PER_SEC);
	पूर्ण

	वापस record_index;
पूर्ण

/* The function वापसs the next record that was
 * not configured (or failed to be configured) */
अटल पूर्णांक get_next_record_to_update(काष्ठा mlx4_ib_dev *dev, u8 port,
				     काष्ठा mlx4_next_alias_guid_work *rec)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक record_index;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags);
	record_index = get_low_record_समय_index(dev, port, शून्य);

	अगर (record_index < 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	set_required_record(dev, port, rec, record_index);
out:
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम alias_guid_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delay = to_delayed_work(work);
	पूर्णांक ret = 0;
	काष्ठा mlx4_next_alias_guid_work *rec;
	काष्ठा mlx4_sriov_alias_guid_port_rec_det *sriov_alias_port =
		container_of(delay, काष्ठा mlx4_sriov_alias_guid_port_rec_det,
			     alias_guid_work);
	काष्ठा mlx4_sriov_alias_guid *sriov_alias_guid = sriov_alias_port->parent;
	काष्ठा mlx4_ib_sriov *ib_sriov = container_of(sriov_alias_guid,
						काष्ठा mlx4_ib_sriov,
						alias_guid);
	काष्ठा mlx4_ib_dev *dev = container_of(ib_sriov, काष्ठा mlx4_ib_dev, sriov);

	rec = kzalloc(माप *rec, GFP_KERNEL);
	अगर (!rec)
		वापस;

	pr_debug("starting [port: %d]...\n", sriov_alias_port->port + 1);
	ret = get_next_record_to_update(dev, sriov_alias_port->port, rec);
	अगर (ret) अणु
		pr_debug("No more records to update.\n");
		जाओ out;
	पूर्ण

	set_guid_rec(&dev->ib_dev, rec);
out:
	kमुक्त(rec);
पूर्ण


व्योम mlx4_ib_init_alias_guid_work(काष्ठा mlx4_ib_dev *dev, पूर्णांक port)
अणु
	अचिन्हित दीर्घ flags, flags1;

	अगर (!mlx4_is_master(dev->dev))
		वापस;
	spin_lock_irqsave(&dev->sriov.going_करोwn_lock, flags);
	spin_lock_irqsave(&dev->sriov.alias_guid.ag_work_lock, flags1);
	अगर (!dev->sriov.is_going_करोwn) अणु
		/* If there is pending one should cancel then run, otherwise
		  * won't run till previous one is ended as same work
		  * काष्ठा is used.
		  */
		cancel_delayed_work(&dev->sriov.alias_guid.ports_guid[port].
				    alias_guid_work);
		queue_delayed_work(dev->sriov.alias_guid.ports_guid[port].wq,
			   &dev->sriov.alias_guid.ports_guid[port].alias_guid_work, 0);
	पूर्ण
	spin_unlock_irqrestore(&dev->sriov.alias_guid.ag_work_lock, flags1);
	spin_unlock_irqrestore(&dev->sriov.going_करोwn_lock, flags);
पूर्ण

व्योम mlx4_ib_destroy_alias_guid_service(काष्ठा mlx4_ib_dev *dev)
अणु
	पूर्णांक i;
	काष्ठा mlx4_ib_sriov *sriov = &dev->sriov;
	काष्ठा mlx4_alias_guid_work_context *cb_ctx;
	काष्ठा mlx4_sriov_alias_guid_port_rec_det *det;
	काष्ठा ib_sa_query *sa_query;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0 ; i < dev->num_ports; i++) अणु
		det = &sriov->alias_guid.ports_guid[i];
		cancel_delayed_work_sync(&det->alias_guid_work);
		spin_lock_irqsave(&sriov->alias_guid.ag_work_lock, flags);
		जबतक (!list_empty(&det->cb_list)) अणु
			cb_ctx = list_entry(det->cb_list.next,
					    काष्ठा mlx4_alias_guid_work_context,
					    list);
			sa_query = cb_ctx->sa_query;
			cb_ctx->sa_query = शून्य;
			list_del(&cb_ctx->list);
			spin_unlock_irqrestore(&sriov->alias_guid.ag_work_lock, flags);
			ib_sa_cancel_query(cb_ctx->query_id, sa_query);
			रुको_क्रम_completion(&cb_ctx->करोne);
			kमुक्त(cb_ctx);
			spin_lock_irqsave(&sriov->alias_guid.ag_work_lock, flags);
		पूर्ण
		spin_unlock_irqrestore(&sriov->alias_guid.ag_work_lock, flags);
	पूर्ण
	क्रम (i = 0 ; i < dev->num_ports; i++) अणु
		flush_workqueue(dev->sriov.alias_guid.ports_guid[i].wq);
		destroy_workqueue(dev->sriov.alias_guid.ports_guid[i].wq);
	पूर्ण
	ib_sa_unरेजिस्टर_client(dev->sriov.alias_guid.sa_client);
	kमुक्त(dev->sriov.alias_guid.sa_client);
पूर्ण

पूर्णांक mlx4_ib_init_alias_guid_service(काष्ठा mlx4_ib_dev *dev)
अणु
	अक्षर alias_wq_name[15];
	पूर्णांक ret = 0;
	पूर्णांक i, j;
	जोड़ ib_gid gid;

	अगर (!mlx4_is_master(dev->dev))
		वापस 0;
	dev->sriov.alias_guid.sa_client =
		kzalloc(माप *dev->sriov.alias_guid.sa_client, GFP_KERNEL);
	अगर (!dev->sriov.alias_guid.sa_client)
		वापस -ENOMEM;

	ib_sa_रेजिस्टर_client(dev->sriov.alias_guid.sa_client);

	spin_lock_init(&dev->sriov.alias_guid.ag_work_lock);

	क्रम (i = 1; i <= dev->num_ports; ++i) अणु
		अगर (dev->ib_dev.ops.query_gid(&dev->ib_dev, i, 0, &gid)) अणु
			ret = -EFAULT;
			जाओ err_unरेजिस्टर;
		पूर्ण
	पूर्ण

	क्रम (i = 0 ; i < dev->num_ports; i++) अणु
		स_रखो(&dev->sriov.alias_guid.ports_guid[i], 0,
		       माप (काष्ठा mlx4_sriov_alias_guid_port_rec_det));
		dev->sriov.alias_guid.ports_guid[i].state_flags |=
				GUID_STATE_NEED_PORT_INIT;
		क्रम (j = 0; j < NUM_ALIAS_GUID_REC_IN_PORT; j++) अणु
			/* mark each val as it was deleted */
			स_रखो(dev->sriov.alias_guid.ports_guid[i].
				all_rec_per_port[j].all_recs, 0xFF,
				माप(dev->sriov.alias_guid.ports_guid[i].
				all_rec_per_port[j].all_recs));
		पूर्ण
		INIT_LIST_HEAD(&dev->sriov.alias_guid.ports_guid[i].cb_list);
		/*prepare the records, set them to be allocated by sm*/
		अगर (mlx4_ib_sm_guid_assign)
			क्रम (j = 1; j < NUM_ALIAS_GUID_PER_PORT; j++)
				mlx4_set_admin_guid(dev->dev, 0, j, i + 1);
		क्रम (j = 0 ; j < NUM_ALIAS_GUID_REC_IN_PORT; j++)
			invalidate_guid_record(dev, i + 1, j);

		dev->sriov.alias_guid.ports_guid[i].parent = &dev->sriov.alias_guid;
		dev->sriov.alias_guid.ports_guid[i].port  = i;

		snम_लिखो(alias_wq_name, माप alias_wq_name, "alias_guid%d", i);
		dev->sriov.alias_guid.ports_guid[i].wq =
			alloc_ordered_workqueue(alias_wq_name, WQ_MEM_RECLAIM);
		अगर (!dev->sriov.alias_guid.ports_guid[i].wq) अणु
			ret = -ENOMEM;
			जाओ err_thपढ़ो;
		पूर्ण
		INIT_DELAYED_WORK(&dev->sriov.alias_guid.ports_guid[i].alias_guid_work,
			  alias_guid_work);
	पूर्ण
	वापस 0;

err_thपढ़ो:
	क्रम (--i; i >= 0; i--) अणु
		destroy_workqueue(dev->sriov.alias_guid.ports_guid[i].wq);
		dev->sriov.alias_guid.ports_guid[i].wq = शून्य;
	पूर्ण

err_unरेजिस्टर:
	ib_sa_unरेजिस्टर_client(dev->sriov.alias_guid.sa_client);
	kमुक्त(dev->sriov.alias_guid.sa_client);
	dev->sriov.alias_guid.sa_client = शून्य;
	pr_err("init_alias_guid_service: Failed. (ret:%d)\n", ret);
	वापस ret;
पूर्ण
