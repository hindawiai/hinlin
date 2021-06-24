<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2019-2020, Mellanox Technologies Ltd. All rights reserved.
 */

#समावेश <uapi/rdma/rdma_netlink.h>
#समावेश <linux/mlx5/rsc_dump.h>
#समावेश <rdma/ib_umem_odp.h>
#समावेश <rdma/restrack.h>
#समावेश "mlx5_ib.h"
#समावेश "restrack.h"

#घोषणा MAX_DUMP_SIZE 1024

अटल पूर्णांक dump_rsc(काष्ठा mlx5_core_dev *dev, क्रमागत mlx5_sgmt_type type,
		    पूर्णांक index, व्योम *data, पूर्णांक *data_len)
अणु
	काष्ठा mlx5_core_dev *mdev = dev;
	काष्ठा mlx5_rsc_dump_cmd *cmd;
	काष्ठा mlx5_rsc_key key = अणुपूर्ण;
	काष्ठा page *page;
	पूर्णांक offset = 0;
	पूर्णांक err = 0;
	पूर्णांक cmd_err;
	पूर्णांक size;

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	key.size = PAGE_SIZE;
	key.rsc = type;
	key.index1 = index;
	key.num_of_obj1 = 1;

	cmd = mlx5_rsc_dump_cmd_create(mdev, &key);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ मुक्त_page;
	पूर्ण

	करो अणु
		cmd_err = mlx5_rsc_dump_next(mdev, cmd, page, &size);
		अगर (cmd_err < 0 || size + offset > MAX_DUMP_SIZE) अणु
			err = cmd_err;
			जाओ destroy_cmd;
		पूर्ण
		स_नकल(data + offset, page_address(page), size);
		offset += size;
	पूर्ण जबतक (cmd_err > 0);
	*data_len = offset;

destroy_cmd:
	mlx5_rsc_dump_cmd_destroy(cmd);
मुक्त_page:
	__मुक्त_page(page);
	वापस err;
पूर्ण

अटल पूर्णांक fill_res_raw(काष्ठा sk_buff *msg, काष्ठा mlx5_ib_dev *dev,
			क्रमागत mlx5_sgmt_type type, u32 key)
अणु
	पूर्णांक len = 0;
	व्योम *data;
	पूर्णांक err;

	data = kzalloc(MAX_DUMP_SIZE, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	err = dump_rsc(dev->mdev, type, key, data, &len);
	अगर (err)
		जाओ out;

	err = nla_put(msg, RDMA_NLDEV_ATTR_RES_RAW, len, data);
out:
	kमुक्त(data);
	वापस err;
पूर्ण

अटल पूर्णांक fill_stat_mr_entry(काष्ठा sk_buff *msg, काष्ठा ib_mr *ibmr)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	काष्ठा nlattr *table_attr;

	अगर (!(mr->access_flags & IB_ACCESS_ON_DEMAND))
		वापस 0;

	table_attr = nla_nest_start(msg,
				    RDMA_NLDEV_ATTR_STAT_HWCOUNTERS);

	अगर (!table_attr)
		जाओ err;

	अगर (rdma_nl_stat_hwcounter_entry(msg, "page_faults",
					 atomic64_पढ़ो(&mr->odp_stats.faults)))
		जाओ err_table;
	अगर (rdma_nl_stat_hwcounter_entry(
		    msg, "page_invalidations",
		    atomic64_पढ़ो(&mr->odp_stats.invalidations)))
		जाओ err_table;
	अगर (rdma_nl_stat_hwcounter_entry(msg, "page_prefetch",
					 atomic64_पढ़ो(&mr->odp_stats.prefetch)))
		जाओ err_table;

	nla_nest_end(msg, table_attr);
	वापस 0;

err_table:
	nla_nest_cancel(msg, table_attr);
err:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_res_mr_entry_raw(काष्ठा sk_buff *msg, काष्ठा ib_mr *ibmr)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);

	वापस fill_res_raw(msg, mr_to_mdev(mr), MLX5_SGMT_TYPE_PRM_QUERY_MKEY,
			    mlx5_mkey_to_idx(mr->mmkey.key));
पूर्ण

अटल पूर्णांक fill_res_mr_entry(काष्ठा sk_buff *msg, काष्ठा ib_mr *ibmr)
अणु
	काष्ठा mlx5_ib_mr *mr = to_mmr(ibmr);
	काष्ठा nlattr *table_attr;

	अगर (!(mr->access_flags & IB_ACCESS_ON_DEMAND))
		वापस 0;

	table_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_DRIVER);
	अगर (!table_attr)
		जाओ err;

	अगर (mr->is_odp_implicit) अणु
		अगर (rdma_nl_put_driver_string(msg, "odp", "implicit"))
			जाओ err;
	पूर्ण अन्यथा अणु
		अगर (rdma_nl_put_driver_string(msg, "odp", "explicit"))
			जाओ err;
	पूर्ण

	nla_nest_end(msg, table_attr);
	वापस 0;

err:
	nla_nest_cancel(msg, table_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_res_cq_entry_raw(काष्ठा sk_buff *msg, काष्ठा ib_cq *ibcq)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibcq->device);
	काष्ठा mlx5_ib_cq *cq = to_mcq(ibcq);

	वापस fill_res_raw(msg, dev, MLX5_SGMT_TYPE_PRM_QUERY_CQ, cq->mcq.cqn);
पूर्ण

अटल पूर्णांक fill_res_qp_entry_raw(काष्ठा sk_buff *msg, काष्ठा ib_qp *ibqp)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(ibqp->device);

	वापस fill_res_raw(msg, dev, MLX5_SGMT_TYPE_PRM_QUERY_QP,
			    ibqp->qp_num);
पूर्ण

अटल स्थिर काष्ठा ib_device_ops restrack_ops = अणु
	.fill_res_cq_entry_raw = fill_res_cq_entry_raw,
	.fill_res_mr_entry = fill_res_mr_entry,
	.fill_res_mr_entry_raw = fill_res_mr_entry_raw,
	.fill_res_qp_entry_raw = fill_res_qp_entry_raw,
	.fill_stat_mr_entry = fill_stat_mr_entry,
पूर्ण;

पूर्णांक mlx5_ib_restrack_init(काष्ठा mlx5_ib_dev *dev)
अणु
	ib_set_device_ops(&dev->ib_dev, &restrack_ops);
	वापस 0;
पूर्ण
