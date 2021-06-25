<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2013-2020, Mellanox Technologies inc. All rights reserved.
 */

#समावेश "mlx5_ib.h"
#समावेश <linux/mlx5/eचयन.h>
#समावेश "counters.h"
#समावेश "ib_rep.h"
#समावेश "qp.h"

काष्ठा mlx5_ib_counter अणु
	स्थिर अक्षर *name;
	माप_प्रकार offset;
पूर्ण;

#घोषणा INIT_Q_COUNTER(_name)		\
	अणु .name = #_name, .offset = MLX5_BYTE_OFF(query_q_counter_out, _name)पूर्ण

अटल स्थिर काष्ठा mlx5_ib_counter basic_q_cnts[] = अणु
	INIT_Q_COUNTER(rx_ग_लिखो_requests),
	INIT_Q_COUNTER(rx_पढ़ो_requests),
	INIT_Q_COUNTER(rx_atomic_requests),
	INIT_Q_COUNTER(out_of_buffer),
पूर्ण;

अटल स्थिर काष्ठा mlx5_ib_counter out_of_seq_q_cnts[] = अणु
	INIT_Q_COUNTER(out_of_sequence),
पूर्ण;

अटल स्थिर काष्ठा mlx5_ib_counter retrans_q_cnts[] = अणु
	INIT_Q_COUNTER(duplicate_request),
	INIT_Q_COUNTER(rnr_nak_retry_err),
	INIT_Q_COUNTER(packet_seq_err),
	INIT_Q_COUNTER(implied_nak_seq_err),
	INIT_Q_COUNTER(local_ack_समयout_err),
पूर्ण;

#घोषणा INIT_CONG_COUNTER(_name)		\
	अणु .name = #_name, .offset =	\
		MLX5_BYTE_OFF(query_cong_statistics_out, _name ## _high)पूर्ण

अटल स्थिर काष्ठा mlx5_ib_counter cong_cnts[] = अणु
	INIT_CONG_COUNTER(rp_cnp_ignored),
	INIT_CONG_COUNTER(rp_cnp_handled),
	INIT_CONG_COUNTER(np_ecn_marked_roce_packets),
	INIT_CONG_COUNTER(np_cnp_sent),
पूर्ण;

अटल स्थिर काष्ठा mlx5_ib_counter extended_err_cnts[] = अणु
	INIT_Q_COUNTER(resp_local_length_error),
	INIT_Q_COUNTER(resp_cqe_error),
	INIT_Q_COUNTER(req_cqe_error),
	INIT_Q_COUNTER(req_remote_invalid_request),
	INIT_Q_COUNTER(req_remote_access_errors),
	INIT_Q_COUNTER(resp_remote_access_errors),
	INIT_Q_COUNTER(resp_cqe_flush_error),
	INIT_Q_COUNTER(req_cqe_flush_error),
पूर्ण;

अटल स्थिर काष्ठा mlx5_ib_counter roce_accl_cnts[] = अणु
	INIT_Q_COUNTER(roce_adp_retrans),
	INIT_Q_COUNTER(roce_adp_retrans_to),
	INIT_Q_COUNTER(roce_slow_restart),
	INIT_Q_COUNTER(roce_slow_restart_cnps),
	INIT_Q_COUNTER(roce_slow_restart_trans),
पूर्ण;

#घोषणा INIT_EXT_PPCNT_COUNTER(_name)		\
	अणु .name = #_name, .offset =	\
	MLX5_BYTE_OFF(ppcnt_reg, \
		      counter_set.eth_extended_cntrs_grp_data_layout._name##_high)पूर्ण

अटल स्थिर काष्ठा mlx5_ib_counter ext_ppcnt_cnts[] = अणु
	INIT_EXT_PPCNT_COUNTER(rx_icrc_encapsulated),
पूर्ण;

अटल पूर्णांक mlx5_ib_पढ़ो_counters(काष्ठा ib_counters *counters,
				 काष्ठा ib_counters_पढ़ो_attr *पढ़ो_attr,
				 काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_mcounters *mcounters = to_mcounters(counters);
	काष्ठा mlx5_पढ़ो_counters_attr mपढ़ो_attr = अणुपूर्ण;
	काष्ठा mlx5_ib_flow_counters_desc *desc;
	पूर्णांक ret, i;

	mutex_lock(&mcounters->mcntrs_mutex);
	अगर (mcounters->cntrs_max_index > पढ़ो_attr->ncounters) अणु
		ret = -EINVAL;
		जाओ err_bound;
	पूर्ण

	mपढ़ो_attr.out = kसुस्मृति(mcounters->counters_num, माप(u64),
				 GFP_KERNEL);
	अगर (!mपढ़ो_attr.out) अणु
		ret = -ENOMEM;
		जाओ err_bound;
	पूर्ण

	mपढ़ो_attr.hw_cntrs_hndl = mcounters->hw_cntrs_hndl;
	mपढ़ो_attr.flags = पढ़ो_attr->flags;
	ret = mcounters->पढ़ो_counters(counters->device, &mपढ़ो_attr);
	अगर (ret)
		जाओ err_पढ़ो;

	/* करो the pass over the counters data array to assign according to the
	 * descriptions and indexing pairs
	 */
	desc = mcounters->counters_data;
	क्रम (i = 0; i < mcounters->ncounters; i++)
		पढ़ो_attr->counters_buff[desc[i].index] += mपढ़ो_attr.out[desc[i].description];

err_पढ़ो:
	kमुक्त(mपढ़ो_attr.out);
err_bound:
	mutex_unlock(&mcounters->mcntrs_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_ib_destroy_counters(काष्ठा ib_counters *counters)
अणु
	काष्ठा mlx5_ib_mcounters *mcounters = to_mcounters(counters);

	mlx5_ib_counters_clear_description(counters);
	अगर (mcounters->hw_cntrs_hndl)
		mlx5_fc_destroy(to_mdev(counters->device)->mdev,
				mcounters->hw_cntrs_hndl);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_create_counters(काष्ठा ib_counters *counters,
				   काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_mcounters *mcounters = to_mcounters(counters);

	mutex_init(&mcounters->mcntrs_mutex);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा mlx5_ib_counters *get_counters(काष्ठा mlx5_ib_dev *dev,
						   u32 port_num)
अणु
	वापस is_mdev_चयनdev_mode(dev->mdev) ? &dev->port[0].cnts :
						   &dev->port[port_num].cnts;
पूर्ण

/**
 * mlx5_ib_get_counters_id - Returns counters id to use क्रम device+port
 * @dev:	Poपूर्णांकer to mlx5 IB device
 * @port_num:	Zero based port number
 *
 * mlx5_ib_get_counters_id() Returns counters set id to use क्रम given
 * device port combination in चयनdev and non चयनdev mode of the
 * parent device.
 */
u16 mlx5_ib_get_counters_id(काष्ठा mlx5_ib_dev *dev, u32 port_num)
अणु
	स्थिर काष्ठा mlx5_ib_counters *cnts = get_counters(dev, port_num);

	वापस cnts->set_id;
पूर्ण

अटल काष्ठा rdma_hw_stats *mlx5_ib_alloc_hw_stats(काष्ठा ib_device *ibdev,
						    u32 port_num)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	स्थिर काष्ठा mlx5_ib_counters *cnts;
	bool is_चयनdev = is_mdev_चयनdev_mode(dev->mdev);

	अगर ((is_चयनdev && port_num) || (!is_चयनdev && !port_num))
		वापस शून्य;

	cnts = get_counters(dev, port_num - 1);

	वापस rdma_alloc_hw_stats_काष्ठा(cnts->names,
					  cnts->num_q_counters +
					  cnts->num_cong_counters +
					  cnts->num_ext_ppcnt_counters,
					  RDMA_HW_STATS_DEFAULT_LIFESPAN);
पूर्ण

अटल पूर्णांक mlx5_ib_query_q_counters(काष्ठा mlx5_core_dev *mdev,
				    स्थिर काष्ठा mlx5_ib_counters *cnts,
				    काष्ठा rdma_hw_stats *stats,
				    u16 set_id)
अणु
	u32 out[MLX5_ST_SZ_DW(query_q_counter_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_q_counter_in)] = अणुपूर्ण;
	__be32 val;
	पूर्णांक ret, i;

	MLX5_SET(query_q_counter_in, in, opcode, MLX5_CMD_OP_QUERY_Q_COUNTER);
	MLX5_SET(query_q_counter_in, in, counter_set_id, set_id);
	ret = mlx5_cmd_exec_inout(mdev, query_q_counter, in, out);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < cnts->num_q_counters; i++) अणु
		val = *(__be32 *)((व्योम *)out + cnts->offsets[i]);
		stats->value[i] = (u64)be32_to_cpu(val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_query_ext_ppcnt_counters(काष्ठा mlx5_ib_dev *dev,
					    स्थिर काष्ठा mlx5_ib_counters *cnts,
					    काष्ठा rdma_hw_stats *stats)
अणु
	पूर्णांक offset = cnts->num_q_counters + cnts->num_cong_counters;
	u32 in[MLX5_ST_SZ_DW(ppcnt_reg)] = अणुपूर्ण;
	पूर्णांक sz = MLX5_ST_SZ_BYTES(ppcnt_reg);
	पूर्णांक ret, i;
	व्योम *out;

	out = kvzalloc(sz, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(ppcnt_reg, in, local_port, 1);
	MLX5_SET(ppcnt_reg, in, grp, MLX5_ETHERNET_EXTENDED_COUNTERS_GROUP);
	ret = mlx5_core_access_reg(dev->mdev, in, sz, out, sz, MLX5_REG_PPCNT,
				   0, 0);
	अगर (ret)
		जाओ मुक्त;

	क्रम (i = 0; i < cnts->num_ext_ppcnt_counters; i++)
		stats->value[i + offset] =
			be64_to_cpup((__be64 *)(out +
				    cnts->offsets[i + offset]));
मुक्त:
	kvमुक्त(out);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_ib_get_hw_stats(काष्ठा ib_device *ibdev,
				काष्ठा rdma_hw_stats *stats,
				u32 port_num, पूर्णांक index)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);
	स्थिर काष्ठा mlx5_ib_counters *cnts = get_counters(dev, port_num - 1);
	काष्ठा mlx5_core_dev *mdev;
	पूर्णांक ret, num_counters;
	u32 mdev_port_num;

	अगर (!stats)
		वापस -EINVAL;

	num_counters = cnts->num_q_counters +
		       cnts->num_cong_counters +
		       cnts->num_ext_ppcnt_counters;

	/* q_counters are per IB device, query the master mdev */
	ret = mlx5_ib_query_q_counters(dev->mdev, cnts, stats, cnts->set_id);
	अगर (ret)
		वापस ret;

	अगर (MLX5_CAP_PCAM_FEATURE(dev->mdev, rx_icrc_encapsulated_counter)) अणु
		ret =  mlx5_ib_query_ext_ppcnt_counters(dev, cnts, stats);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev->mdev, cc_query_allowed)) अणु
		mdev = mlx5_ib_get_native_port_mdev(dev, port_num,
						    &mdev_port_num);
		अगर (!mdev) अणु
			/* If port is not affiliated yet, its in करोwn state
			 * which करोesn't have any counters yet, so it would be
			 * zero. So no need to पढ़ो from the HCA.
			 */
			जाओ करोne;
		पूर्ण
		ret = mlx5_lag_query_cong_counters(dev->mdev,
						   stats->value +
						   cnts->num_q_counters,
						   cnts->num_cong_counters,
						   cnts->offsets +
						   cnts->num_q_counters);

		mlx5_ib_put_native_port_mdev(dev, port_num);
		अगर (ret)
			वापस ret;
	पूर्ण

करोne:
	वापस num_counters;
पूर्ण

अटल काष्ठा rdma_hw_stats *
mlx5_ib_counter_alloc_stats(काष्ठा rdma_counter *counter)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(counter->device);
	स्थिर काष्ठा mlx5_ib_counters *cnts =
		get_counters(dev, counter->port - 1);

	वापस rdma_alloc_hw_stats_काष्ठा(cnts->names,
					  cnts->num_q_counters +
					  cnts->num_cong_counters +
					  cnts->num_ext_ppcnt_counters,
					  RDMA_HW_STATS_DEFAULT_LIFESPAN);
पूर्ण

अटल पूर्णांक mlx5_ib_counter_update_stats(काष्ठा rdma_counter *counter)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(counter->device);
	स्थिर काष्ठा mlx5_ib_counters *cnts =
		get_counters(dev, counter->port - 1);

	वापस mlx5_ib_query_q_counters(dev->mdev, cnts,
					counter->stats, counter->id);
पूर्ण

अटल पूर्णांक mlx5_ib_counter_dealloc(काष्ठा rdma_counter *counter)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(counter->device);
	u32 in[MLX5_ST_SZ_DW(dealloc_q_counter_in)] = अणुपूर्ण;

	अगर (!counter->id)
		वापस 0;

	MLX5_SET(dealloc_q_counter_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_Q_COUNTER);
	MLX5_SET(dealloc_q_counter_in, in, counter_set_id, counter->id);
	वापस mlx5_cmd_exec_in(dev->mdev, dealloc_q_counter, in);
पूर्ण

अटल पूर्णांक mlx5_ib_counter_bind_qp(काष्ठा rdma_counter *counter,
				   काष्ठा ib_qp *qp)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	पूर्णांक err;

	अगर (!counter->id) अणु
		u32 out[MLX5_ST_SZ_DW(alloc_q_counter_out)] = अणुपूर्ण;
		u32 in[MLX5_ST_SZ_DW(alloc_q_counter_in)] = अणुपूर्ण;

		MLX5_SET(alloc_q_counter_in, in, opcode,
			 MLX5_CMD_OP_ALLOC_Q_COUNTER);
		MLX5_SET(alloc_q_counter_in, in, uid, MLX5_SHARED_RESOURCE_UID);
		err = mlx5_cmd_exec_inout(dev->mdev, alloc_q_counter, in, out);
		अगर (err)
			वापस err;
		counter->id =
			MLX5_GET(alloc_q_counter_out, out, counter_set_id);
	पूर्ण

	err = mlx5_ib_qp_set_counter(qp, counter);
	अगर (err)
		जाओ fail_set_counter;

	वापस 0;

fail_set_counter:
	mlx5_ib_counter_dealloc(counter);
	counter->id = 0;

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_ib_counter_unbind_qp(काष्ठा ib_qp *qp)
अणु
	वापस mlx5_ib_qp_set_counter(qp, शून्य);
पूर्ण


अटल व्योम mlx5_ib_fill_counters(काष्ठा mlx5_ib_dev *dev,
				  स्थिर अक्षर **names,
				  माप_प्रकार *offsets)
अणु
	पूर्णांक i;
	पूर्णांक j = 0;

	क्रम (i = 0; i < ARRAY_SIZE(basic_q_cnts); i++, j++) अणु
		names[j] = basic_q_cnts[i].name;
		offsets[j] = basic_q_cnts[i].offset;
	पूर्ण

	अगर (MLX5_CAP_GEN(dev->mdev, out_of_seq_cnt)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(out_of_seq_q_cnts); i++, j++) अणु
			names[j] = out_of_seq_q_cnts[i].name;
			offsets[j] = out_of_seq_q_cnts[i].offset;
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_GEN(dev->mdev, retransmission_q_counters)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(retrans_q_cnts); i++, j++) अणु
			names[j] = retrans_q_cnts[i].name;
			offsets[j] = retrans_q_cnts[i].offset;
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_GEN(dev->mdev, enhanced_error_q_counters)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(extended_err_cnts); i++, j++) अणु
			names[j] = extended_err_cnts[i].name;
			offsets[j] = extended_err_cnts[i].offset;
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_GEN(dev->mdev, roce_accl)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(roce_accl_cnts); i++, j++) अणु
			names[j] = roce_accl_cnts[i].name;
			offsets[j] = roce_accl_cnts[i].offset;
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_GEN(dev->mdev, cc_query_allowed)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(cong_cnts); i++, j++) अणु
			names[j] = cong_cnts[i].name;
			offsets[j] = cong_cnts[i].offset;
		पूर्ण
	पूर्ण

	अगर (MLX5_CAP_PCAM_FEATURE(dev->mdev, rx_icrc_encapsulated_counter)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ext_ppcnt_cnts); i++, j++) अणु
			names[j] = ext_ppcnt_cnts[i].name;
			offsets[j] = ext_ppcnt_cnts[i].offset;
		पूर्ण
	पूर्ण
पूर्ण


अटल पूर्णांक __mlx5_ib_alloc_counters(काष्ठा mlx5_ib_dev *dev,
				    काष्ठा mlx5_ib_counters *cnts)
अणु
	u32 num_counters;

	num_counters = ARRAY_SIZE(basic_q_cnts);

	अगर (MLX5_CAP_GEN(dev->mdev, out_of_seq_cnt))
		num_counters += ARRAY_SIZE(out_of_seq_q_cnts);

	अगर (MLX5_CAP_GEN(dev->mdev, retransmission_q_counters))
		num_counters += ARRAY_SIZE(retrans_q_cnts);

	अगर (MLX5_CAP_GEN(dev->mdev, enhanced_error_q_counters))
		num_counters += ARRAY_SIZE(extended_err_cnts);

	अगर (MLX5_CAP_GEN(dev->mdev, roce_accl))
		num_counters += ARRAY_SIZE(roce_accl_cnts);

	cnts->num_q_counters = num_counters;

	अगर (MLX5_CAP_GEN(dev->mdev, cc_query_allowed)) अणु
		cnts->num_cong_counters = ARRAY_SIZE(cong_cnts);
		num_counters += ARRAY_SIZE(cong_cnts);
	पूर्ण
	अगर (MLX5_CAP_PCAM_FEATURE(dev->mdev, rx_icrc_encapsulated_counter)) अणु
		cnts->num_ext_ppcnt_counters = ARRAY_SIZE(ext_ppcnt_cnts);
		num_counters += ARRAY_SIZE(ext_ppcnt_cnts);
	पूर्ण
	cnts->names = kसुस्मृति(num_counters, माप(*cnts->names), GFP_KERNEL);
	अगर (!cnts->names)
		वापस -ENOMEM;

	cnts->offsets = kसुस्मृति(num_counters,
				माप(*cnts->offsets), GFP_KERNEL);
	अगर (!cnts->offsets)
		जाओ err_names;

	वापस 0;

err_names:
	kमुक्त(cnts->names);
	cnts->names = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल व्योम mlx5_ib_dealloc_counters(काष्ठा mlx5_ib_dev *dev)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_q_counter_in)] = अणुपूर्ण;
	पूर्णांक num_cnt_ports;
	पूर्णांक i;

	num_cnt_ports = is_mdev_चयनdev_mode(dev->mdev) ? 1 : dev->num_ports;

	MLX5_SET(dealloc_q_counter_in, in, opcode,
		 MLX5_CMD_OP_DEALLOC_Q_COUNTER);

	क्रम (i = 0; i < num_cnt_ports; i++) अणु
		अगर (dev->port[i].cnts.set_id) अणु
			MLX5_SET(dealloc_q_counter_in, in, counter_set_id,
				 dev->port[i].cnts.set_id);
			mlx5_cmd_exec_in(dev->mdev, dealloc_q_counter, in);
		पूर्ण
		kमुक्त(dev->port[i].cnts.names);
		kमुक्त(dev->port[i].cnts.offsets);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_ib_alloc_counters(काष्ठा mlx5_ib_dev *dev)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_q_counter_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_q_counter_in)] = अणुपूर्ण;
	पूर्णांक num_cnt_ports;
	पूर्णांक err = 0;
	पूर्णांक i;
	bool is_shared;

	MLX5_SET(alloc_q_counter_in, in, opcode, MLX5_CMD_OP_ALLOC_Q_COUNTER);
	is_shared = MLX5_CAP_GEN(dev->mdev, log_max_uctx) != 0;
	num_cnt_ports = is_mdev_चयनdev_mode(dev->mdev) ? 1 : dev->num_ports;

	क्रम (i = 0; i < num_cnt_ports; i++) अणु
		err = __mlx5_ib_alloc_counters(dev, &dev->port[i].cnts);
		अगर (err)
			जाओ err_alloc;

		mlx5_ib_fill_counters(dev, dev->port[i].cnts.names,
				      dev->port[i].cnts.offsets);

		MLX5_SET(alloc_q_counter_in, in, uid,
			 is_shared ? MLX5_SHARED_RESOURCE_UID : 0);

		err = mlx5_cmd_exec_inout(dev->mdev, alloc_q_counter, in, out);
		अगर (err) अणु
			mlx5_ib_warn(dev,
				     "couldn't allocate queue counter for port %d, err %d\n",
				     i + 1, err);
			जाओ err_alloc;
		पूर्ण

		dev->port[i].cnts.set_id =
			MLX5_GET(alloc_q_counter_out, out, counter_set_id);
	पूर्ण
	वापस 0;

err_alloc:
	mlx5_ib_dealloc_counters(dev);
	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_flow_counters(काष्ठा ib_device *ibdev,
			      काष्ठा mlx5_पढ़ो_counters_attr *पढ़ो_attr)
अणु
	काष्ठा mlx5_fc *fc = पढ़ो_attr->hw_cntrs_hndl;
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibdev);

	वापस mlx5_fc_query(dev->mdev, fc,
			     &पढ़ो_attr->out[IB_COUNTER_PACKETS],
			     &पढ़ो_attr->out[IB_COUNTER_BYTES]);
पूर्ण

/* flow counters currently expose two counters packets and bytes */
#घोषणा FLOW_COUNTERS_NUM 2
अटल पूर्णांक counters_set_description(
	काष्ठा ib_counters *counters, क्रमागत mlx5_ib_counters_type counters_type,
	काष्ठा mlx5_ib_flow_counters_desc *desc_data, u32 ncounters)
अणु
	काष्ठा mlx5_ib_mcounters *mcounters = to_mcounters(counters);
	u32 cntrs_max_index = 0;
	पूर्णांक i;

	अगर (counters_type != MLX5_IB_COUNTERS_FLOW)
		वापस -EINVAL;

	/* init the fields क्रम the object */
	mcounters->type = counters_type;
	mcounters->पढ़ो_counters = पढ़ो_flow_counters;
	mcounters->counters_num = FLOW_COUNTERS_NUM;
	mcounters->ncounters = ncounters;
	/* each counter entry have both description and index pair */
	क्रम (i = 0; i < ncounters; i++) अणु
		अगर (desc_data[i].description > IB_COUNTER_BYTES)
			वापस -EINVAL;

		अगर (cntrs_max_index <= desc_data[i].index)
			cntrs_max_index = desc_data[i].index + 1;
	पूर्ण

	mutex_lock(&mcounters->mcntrs_mutex);
	mcounters->counters_data = desc_data;
	mcounters->cntrs_max_index = cntrs_max_index;
	mutex_unlock(&mcounters->mcntrs_mutex);

	वापस 0;
पूर्ण

#घोषणा MAX_COUNTERS_NUM (अच_लघु_उच्च / (माप(u32) * 2))
पूर्णांक mlx5_ib_flow_counters_set_data(काष्ठा ib_counters *ibcounters,
				   काष्ठा mlx5_ib_create_flow *ucmd)
अणु
	काष्ठा mlx5_ib_mcounters *mcounters = to_mcounters(ibcounters);
	काष्ठा mlx5_ib_flow_counters_data *cntrs_data = शून्य;
	काष्ठा mlx5_ib_flow_counters_desc *desc_data = शून्य;
	bool hw_hndl = false;
	पूर्णांक ret = 0;

	अगर (ucmd && ucmd->ncounters_data != 0) अणु
		cntrs_data = ucmd->data;
		अगर (cntrs_data->ncounters > MAX_COUNTERS_NUM)
			वापस -EINVAL;

		desc_data = kसुस्मृति(cntrs_data->ncounters,
				    माप(*desc_data),
				    GFP_KERNEL);
		अगर (!desc_data)
			वापस  -ENOMEM;

		अगर (copy_from_user(desc_data,
				   u64_to_user_ptr(cntrs_data->counters_data),
				   माप(*desc_data) * cntrs_data->ncounters)) अणु
			ret = -EFAULT;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	अगर (!mcounters->hw_cntrs_hndl) अणु
		mcounters->hw_cntrs_hndl = mlx5_fc_create(
			to_mdev(ibcounters->device)->mdev, false);
		अगर (IS_ERR(mcounters->hw_cntrs_hndl)) अणु
			ret = PTR_ERR(mcounters->hw_cntrs_hndl);
			जाओ मुक्त;
		पूर्ण
		hw_hndl = true;
	पूर्ण

	अगर (desc_data) अणु
		/* counters alपढ़ोy bound to at least one flow */
		अगर (mcounters->cntrs_max_index) अणु
			ret = -EINVAL;
			जाओ मुक्त_hndl;
		पूर्ण

		ret = counters_set_description(ibcounters,
					       MLX5_IB_COUNTERS_FLOW,
					       desc_data,
					       cntrs_data->ncounters);
		अगर (ret)
			जाओ मुक्त_hndl;

	पूर्ण अन्यथा अगर (!mcounters->cntrs_max_index) अणु
		/* counters not bound yet, must have udata passed */
		ret = -EINVAL;
		जाओ मुक्त_hndl;
	पूर्ण

	वापस 0;

मुक्त_hndl:
	अगर (hw_hndl) अणु
		mlx5_fc_destroy(to_mdev(ibcounters->device)->mdev,
				mcounters->hw_cntrs_hndl);
		mcounters->hw_cntrs_hndl = शून्य;
	पूर्ण
मुक्त:
	kमुक्त(desc_data);
	वापस ret;
पूर्ण

व्योम mlx5_ib_counters_clear_description(काष्ठा ib_counters *counters)
अणु
	काष्ठा mlx5_ib_mcounters *mcounters;

	अगर (!counters || atomic_पढ़ो(&counters->usecnt) != 1)
		वापस;

	mcounters = to_mcounters(counters);

	mutex_lock(&mcounters->mcntrs_mutex);
	kमुक्त(mcounters->counters_data);
	mcounters->counters_data = शून्य;
	mcounters->cntrs_max_index = 0;
	mutex_unlock(&mcounters->mcntrs_mutex);
पूर्ण

अटल स्थिर काष्ठा ib_device_ops hw_stats_ops = अणु
	.alloc_hw_stats = mlx5_ib_alloc_hw_stats,
	.get_hw_stats = mlx5_ib_get_hw_stats,
	.counter_bind_qp = mlx5_ib_counter_bind_qp,
	.counter_unbind_qp = mlx5_ib_counter_unbind_qp,
	.counter_dealloc = mlx5_ib_counter_dealloc,
	.counter_alloc_stats = mlx5_ib_counter_alloc_stats,
	.counter_update_stats = mlx5_ib_counter_update_stats,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops counters_ops = अणु
	.create_counters = mlx5_ib_create_counters,
	.destroy_counters = mlx5_ib_destroy_counters,
	.पढ़ो_counters = mlx5_ib_पढ़ो_counters,

	INIT_RDMA_OBJ_SIZE(ib_counters, mlx5_ib_mcounters, ibcntrs),
पूर्ण;

पूर्णांक mlx5_ib_counters_init(काष्ठा mlx5_ib_dev *dev)
अणु
	ib_set_device_ops(&dev->ib_dev, &counters_ops);

	अगर (!MLX5_CAP_GEN(dev->mdev, max_qp_cnt))
		वापस 0;

	ib_set_device_ops(&dev->ib_dev, &hw_stats_ops);
	वापस mlx5_ib_alloc_counters(dev);
पूर्ण

व्योम mlx5_ib_counters_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	अगर (!MLX5_CAP_GEN(dev->mdev, max_qp_cnt))
		वापस;

	mlx5_ib_dealloc_counters(dev);
पूर्ण
