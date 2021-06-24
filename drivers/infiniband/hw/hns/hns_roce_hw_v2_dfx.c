<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause)
// Copyright (c) 2019 Hisilicon Limited.

#समावेश "hnae3.h"
#समावेश "hns_roce_device.h"
#समावेश "hns_roce_cmd.h"
#समावेश "hns_roce_hw_v2.h"

पूर्णांक hns_roce_v2_query_cqc_info(काष्ठा hns_roce_dev *hr_dev, u32 cqn,
			       पूर्णांक *buffer)
अणु
	काष्ठा hns_roce_v2_cq_context *cq_context;
	काष्ठा hns_roce_cmd_mailbox *mailbox;
	पूर्णांक ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	cq_context = mailbox->buf;
	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, cqn, 0,
				HNS_ROCE_CMD_QUERY_CQC,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	अगर (ret) अणु
		dev_err(hr_dev->dev, "QUERY cqc cmd process error\n");
		जाओ err_mailbox;
	पूर्ण

	स_नकल(buffer, cq_context, माप(*cq_context));

err_mailbox:
	hns_roce_मुक्त_cmd_mailbox(hr_dev, mailbox);

	वापस ret;
पूर्ण
