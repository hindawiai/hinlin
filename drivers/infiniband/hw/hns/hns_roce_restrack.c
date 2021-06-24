<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause)
// Copyright (c) 2019 Hisilicon Limited.

#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/restrack.h>
#समावेश <uapi/rdma/rdma_netlink.h>
#समावेश "hnae3.h"
#समावेश "hns_roce_common.h"
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_hw_v2.h"

अटल पूर्णांक hns_roce_fill_cq(काष्ठा sk_buff *msg,
			    काष्ठा hns_roce_v2_cq_context *context)
अणु
	अगर (rdma_nl_put_driver_u32(msg, "state",
				   roce_get_field(context->byte_4_pg_ceqn,
						  V2_CQC_BYTE_4_ARM_ST_M,
						  V2_CQC_BYTE_4_ARM_ST_S)))
		जाओ err;

	अगर (rdma_nl_put_driver_u32(msg, "ceqn",
				   roce_get_field(context->byte_4_pg_ceqn,
						  V2_CQC_BYTE_4_CEQN_M,
						  V2_CQC_BYTE_4_CEQN_S)))
		जाओ err;

	अगर (rdma_nl_put_driver_u32(msg, "cqn",
				   roce_get_field(context->byte_8_cqn,
						  V2_CQC_BYTE_8_CQN_M,
						  V2_CQC_BYTE_8_CQN_S)))
		जाओ err;

	अगर (rdma_nl_put_driver_u32(msg, "hopnum",
				   roce_get_field(context->byte_16_hop_addr,
						  V2_CQC_BYTE_16_CQE_HOP_NUM_M,
						  V2_CQC_BYTE_16_CQE_HOP_NUM_S)))
		जाओ err;

	अगर (rdma_nl_put_driver_u32(
		    msg, "pi",
		    roce_get_field(context->byte_28_cq_pi,
				   V2_CQC_BYTE_28_CQ_PRODUCER_IDX_M,
				   V2_CQC_BYTE_28_CQ_PRODUCER_IDX_S)))
		जाओ err;

	अगर (rdma_nl_put_driver_u32(
		    msg, "ci",
		    roce_get_field(context->byte_32_cq_ci,
				   V2_CQC_BYTE_32_CQ_CONSUMER_IDX_M,
				   V2_CQC_BYTE_32_CQ_CONSUMER_IDX_S)))
		जाओ err;

	अगर (rdma_nl_put_driver_u32(
		    msg, "coalesce",
		    roce_get_field(context->byte_56_cqe_period_maxcnt,
				   V2_CQC_BYTE_56_CQ_MAX_CNT_M,
				   V2_CQC_BYTE_56_CQ_MAX_CNT_S)))
		जाओ err;

	अगर (rdma_nl_put_driver_u32(
		    msg, "period",
		    roce_get_field(context->byte_56_cqe_period_maxcnt,
				   V2_CQC_BYTE_56_CQ_PERIOD_M,
				   V2_CQC_BYTE_56_CQ_PERIOD_S)))
		जाओ err;

	अगर (rdma_nl_put_driver_u32(msg, "cnt",
				   roce_get_field(context->byte_52_cqe_cnt,
						  V2_CQC_BYTE_52_CQE_CNT_M,
						  V2_CQC_BYTE_52_CQE_CNT_S)))
		जाओ err;

	वापस 0;

err:
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक hns_roce_fill_res_cq_entry(काष्ठा sk_buff *msg,
			       काष्ठा ib_cq *ib_cq)
अणु
	काष्ठा hns_roce_dev *hr_dev = to_hr_dev(ib_cq->device);
	काष्ठा hns_roce_cq *hr_cq = to_hr_cq(ib_cq);
	काष्ठा hns_roce_v2_cq_context *context;
	काष्ठा nlattr *table_attr;
	पूर्णांक ret;

	अगर (!hr_dev->dfx->query_cqc_info)
		वापस -EINVAL;

	context = kzalloc(माप(काष्ठा hns_roce_v2_cq_context), GFP_KERNEL);
	अगर (!context)
		वापस -ENOMEM;

	ret = hr_dev->dfx->query_cqc_info(hr_dev, hr_cq->cqn, (पूर्णांक *)context);
	अगर (ret)
		जाओ err;

	table_attr = nla_nest_start(msg, RDMA_NLDEV_ATTR_DRIVER);
	अगर (!table_attr) अणु
		ret = -EMSGSIZE;
		जाओ err;
	पूर्ण

	अगर (hns_roce_fill_cq(msg, context)) अणु
		ret = -EMSGSIZE;
		जाओ err_cancel_table;
	पूर्ण

	nla_nest_end(msg, table_attr);
	kमुक्त(context);

	वापस 0;

err_cancel_table:
	nla_nest_cancel(msg, table_attr);
err:
	kमुक्त(context);
	वापस ret;
पूर्ण
