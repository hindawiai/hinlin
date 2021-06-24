<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2019 NXP
 *
 * Implementation of the SCU IRQ functions using MU.
 *
 */

#समावेश <dt-bindings/firmware/imx/rsrc.h>
#समावेश <linux/firmware/imx/ipc.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/suspend.h>

#घोषणा IMX_SC_IRQ_FUNC_ENABLE	1
#घोषणा IMX_SC_IRQ_FUNC_STATUS	2
#घोषणा IMX_SC_IRQ_NUM_GROUP	4

अटल u32 mu_resource_id;

काष्ठा imx_sc_msg_irq_get_status अणु
	काष्ठा imx_sc_rpc_msg hdr;
	जोड़ अणु
		काष्ठा अणु
			u16 resource;
			u8 group;
			u8 reserved;
		पूर्ण __packed req;
		काष्ठा अणु
			u32 status;
		पूर्ण resp;
	पूर्ण data;
पूर्ण;

काष्ठा imx_sc_msg_irq_enable अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 mask;
	u16 resource;
	u8 group;
	u8 enable;
पूर्ण __packed;

अटल काष्ठा imx_sc_ipc *imx_sc_irq_ipc_handle;
अटल काष्ठा work_काष्ठा imx_sc_irq_work;
अटल ATOMIC_NOTIFIER_HEAD(imx_scu_irq_notअगरier_chain);

पूर्णांक imx_scu_irq_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(
		&imx_scu_irq_notअगरier_chain, nb);
पूर्ण
EXPORT_SYMBOL(imx_scu_irq_रेजिस्टर_notअगरier);

पूर्णांक imx_scu_irq_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(
		&imx_scu_irq_notअगरier_chain, nb);
पूर्ण
EXPORT_SYMBOL(imx_scu_irq_unरेजिस्टर_notअगरier);

अटल पूर्णांक imx_scu_irq_notअगरier_call_chain(अचिन्हित दीर्घ status, u8 *group)
अणु
	वापस atomic_notअगरier_call_chain(&imx_scu_irq_notअगरier_chain,
		status, (व्योम *)group);
पूर्ण

अटल व्योम imx_scu_irq_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा imx_sc_msg_irq_get_status msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	u32 irq_status;
	पूर्णांक ret;
	u8 i;

	क्रम (i = 0; i < IMX_SC_IRQ_NUM_GROUP; i++) अणु
		hdr->ver = IMX_SC_RPC_VERSION;
		hdr->svc = IMX_SC_RPC_SVC_IRQ;
		hdr->func = IMX_SC_IRQ_FUNC_STATUS;
		hdr->size = 2;

		msg.data.req.resource = mu_resource_id;
		msg.data.req.group = i;

		ret = imx_scu_call_rpc(imx_sc_irq_ipc_handle, &msg, true);
		अगर (ret) अणु
			pr_err("get irq group %d status failed, ret %d\n",
			       i, ret);
			वापस;
		पूर्ण

		irq_status = msg.data.resp.status;
		अगर (!irq_status)
			जारी;

		pm_प्रणाली_wakeup();
		imx_scu_irq_notअगरier_call_chain(irq_status, &i);
	पूर्ण
पूर्ण

पूर्णांक imx_scu_irq_group_enable(u8 group, u32 mask, u8 enable)
अणु
	काष्ठा imx_sc_msg_irq_enable msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	पूर्णांक ret;

	अगर (!imx_sc_irq_ipc_handle)
		वापस -EPROBE_DEFER;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_IRQ;
	hdr->func = IMX_SC_IRQ_FUNC_ENABLE;
	hdr->size = 3;

	msg.resource = mu_resource_id;
	msg.group = group;
	msg.mask = mask;
	msg.enable = enable;

	ret = imx_scu_call_rpc(imx_sc_irq_ipc_handle, &msg, true);
	अगर (ret)
		pr_err("enable irq failed, group %d, mask %d, ret %d\n",
			group, mask, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(imx_scu_irq_group_enable);

अटल व्योम imx_scu_irq_callback(काष्ठा mbox_client *c, व्योम *msg)
अणु
	schedule_work(&imx_sc_irq_work);
पूर्ण

पूर्णांक imx_scu_enable_general_irq_channel(काष्ठा device *dev)
अणु
	काष्ठा of_phandle_args spec;
	काष्ठा mbox_client *cl;
	काष्ठा mbox_chan *ch;
	पूर्णांक ret = 0, i = 0;

	ret = imx_scu_get_handle(&imx_sc_irq_ipc_handle);
	अगर (ret)
		वापस ret;

	cl = devm_kzalloc(dev, माप(*cl), GFP_KERNEL);
	अगर (!cl)
		वापस -ENOMEM;

	cl->dev = dev;
	cl->rx_callback = imx_scu_irq_callback;

	/* SCU general IRQ uses general पूर्णांकerrupt channel 3 */
	ch = mbox_request_channel_byname(cl, "gip3");
	अगर (IS_ERR(ch)) अणु
		ret = PTR_ERR(ch);
		dev_err(dev, "failed to request mbox chan gip3, ret %d\n", ret);
		devm_kमुक्त(dev, cl);
		वापस ret;
	पूर्ण

	INIT_WORK(&imx_sc_irq_work, imx_scu_irq_work_handler);

	अगर (!of_parse_phandle_with_args(dev->of_node, "mboxes",
				       "#mbox-cells", 0, &spec))
		i = of_alias_get_id(spec.np, "mu");

	/* use mu1 as general mu irq channel अगर failed */
	अगर (i < 0)
		i = 1;

	mu_resource_id = IMX_SC_R_MU_0A + i;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(imx_scu_enable_general_irq_channel);
