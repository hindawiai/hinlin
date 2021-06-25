<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Message SMC/HVC
 * Transport driver
 *
 * Copyright 2020 NXP
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>

#समावेश "common.h"

/**
 * काष्ठा scmi_smc - Structure representing a SCMI smc transport
 *
 * @cinfo: SCMI channel info
 * @shmem: Transmit/Receive shared memory area
 * @shmem_lock: Lock to protect access to Tx/Rx shared memory area
 * @func_id: smc/hvc call function id
 * @irq: Optional; employed when platक्रमms indicates msg completion by पूर्णांकr.
 * @tx_complete: Optional, employed only when irq is valid.
 */

काष्ठा scmi_smc अणु
	काष्ठा scmi_chan_info *cinfo;
	काष्ठा scmi_shared_mem __iomem *shmem;
	काष्ठा mutex shmem_lock;
	u32 func_id;
	पूर्णांक irq;
	काष्ठा completion tx_complete;
पूर्ण;

अटल irqवापस_t smc_msg_करोne_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा scmi_smc *scmi_info = data;

	complete(&scmi_info->tx_complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool smc_chan_available(काष्ठा device *dev, पूर्णांक idx)
अणु
	काष्ठा device_node *np = of_parse_phandle(dev->of_node, "shmem", 0);
	अगर (!np)
		वापस false;

	of_node_put(np);
	वापस true;
पूर्ण

अटल पूर्णांक smc_chan_setup(काष्ठा scmi_chan_info *cinfo, काष्ठा device *dev,
			  bool tx)
अणु
	काष्ठा device *cdev = cinfo->dev;
	काष्ठा scmi_smc *scmi_info;
	resource_माप_प्रकार size;
	काष्ठा resource res;
	काष्ठा device_node *np;
	u32 func_id;
	पूर्णांक ret, irq;

	अगर (!tx)
		वापस -ENODEV;

	scmi_info = devm_kzalloc(dev, माप(*scmi_info), GFP_KERNEL);
	अगर (!scmi_info)
		वापस -ENOMEM;

	np = of_parse_phandle(cdev->of_node, "shmem", 0);
	ret = of_address_to_resource(np, 0, &res);
	of_node_put(np);
	अगर (ret) अणु
		dev_err(cdev, "failed to get SCMI Tx shared memory\n");
		वापस ret;
	पूर्ण

	size = resource_size(&res);
	scmi_info->shmem = devm_ioremap(dev, res.start, size);
	अगर (!scmi_info->shmem) अणु
		dev_err(dev, "failed to ioremap SCMI Tx shared memory\n");
		वापस -EADDRNOTAVAIL;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "arm,smc-id", &func_id);
	अगर (ret < 0)
		वापस ret;

	/*
	 * If there is an पूर्णांकerrupt named "a2p", then the service and
	 * completion of a message is संकेतed by an पूर्णांकerrupt rather than by
	 * the वापस of the SMC call.
	 */
	irq = of_irq_get_byname(cdev->of_node, "a2p");
	अगर (irq > 0) अणु
		ret = devm_request_irq(dev, irq, smc_msg_करोne_isr,
				       IRQF_NO_SUSPEND,
				       dev_name(dev), scmi_info);
		अगर (ret) अणु
			dev_err(dev, "failed to setup SCMI smc irq\n");
			वापस ret;
		पूर्ण
		init_completion(&scmi_info->tx_complete);
		scmi_info->irq = irq;
	पूर्ण

	scmi_info->func_id = func_id;
	scmi_info->cinfo = cinfo;
	mutex_init(&scmi_info->shmem_lock);
	cinfo->transport_info = scmi_info;

	वापस 0;
पूर्ण

अटल पूर्णांक smc_chan_मुक्त(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा scmi_chan_info *cinfo = p;
	काष्ठा scmi_smc *scmi_info = cinfo->transport_info;

	cinfo->transport_info = शून्य;
	scmi_info->cinfo = शून्य;

	scmi_मुक्त_channel(cinfo, data, id);

	वापस 0;
पूर्ण

अटल पूर्णांक smc_send_message(काष्ठा scmi_chan_info *cinfo,
			    काष्ठा scmi_xfer *xfer)
अणु
	काष्ठा scmi_smc *scmi_info = cinfo->transport_info;
	काष्ठा arm_smccc_res res;

	mutex_lock(&scmi_info->shmem_lock);

	shmem_tx_prepare(scmi_info->shmem, xfer);

	अगर (scmi_info->irq)
		reinit_completion(&scmi_info->tx_complete);

	arm_smccc_1_1_invoke(scmi_info->func_id, 0, 0, 0, 0, 0, 0, 0, &res);

	अगर (scmi_info->irq)
		रुको_क्रम_completion(&scmi_info->tx_complete);

	scmi_rx_callback(scmi_info->cinfo, shmem_पढ़ो_header(scmi_info->shmem));

	mutex_unlock(&scmi_info->shmem_lock);

	/* Only SMCCC_RET_NOT_SUPPORTED is valid error code */
	अगर (res.a0)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण

अटल व्योम smc_fetch_response(काष्ठा scmi_chan_info *cinfo,
			       काष्ठा scmi_xfer *xfer)
अणु
	काष्ठा scmi_smc *scmi_info = cinfo->transport_info;

	shmem_fetch_response(scmi_info->shmem, xfer);
पूर्ण

अटल bool
smc_poll_करोne(काष्ठा scmi_chan_info *cinfo, काष्ठा scmi_xfer *xfer)
अणु
	काष्ठा scmi_smc *scmi_info = cinfo->transport_info;

	वापस shmem_poll_करोne(scmi_info->shmem, xfer);
पूर्ण

अटल स्थिर काष्ठा scmi_transport_ops scmi_smc_ops = अणु
	.chan_available = smc_chan_available,
	.chan_setup = smc_chan_setup,
	.chan_मुक्त = smc_chan_मुक्त,
	.send_message = smc_send_message,
	.fetch_response = smc_fetch_response,
	.poll_करोne = smc_poll_करोne,
पूर्ण;

स्थिर काष्ठा scmi_desc scmi_smc_desc = अणु
	.ops = &scmi_smc_ops,
	.max_rx_समयout_ms = 30,
	.max_msg = 20,
	.max_msg_size = 128,
पूर्ण;
