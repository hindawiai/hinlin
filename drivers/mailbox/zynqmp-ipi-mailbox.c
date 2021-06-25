<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Inter Processor Interrupt(IPI) Mailbox Driver
 *
 * Copyright (C) 2018 Xilinx, Inc.
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/mailbox/zynqmp-ipi-message.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

/* IPI agent ID any */
#घोषणा IPI_ID_ANY 0xFFUL

/* indicate अगर ZynqMP IPI mailbox driver uses SMC calls or HVC calls */
#घोषणा USE_SMC 0
#घोषणा USE_HVC 1

/* Default IPI SMC function IDs */
#घोषणा SMC_IPI_MAILBOX_OPEN		0x82001000U
#घोषणा SMC_IPI_MAILBOX_RELEASE		0x82001001U
#घोषणा SMC_IPI_MAILBOX_STATUS_ENQUIRY	0x82001002U
#घोषणा SMC_IPI_MAILBOX_NOTIFY		0x82001003U
#घोषणा SMC_IPI_MAILBOX_ACK		0x82001004U
#घोषणा SMC_IPI_MAILBOX_ENABLE_IRQ	0x82001005U
#घोषणा SMC_IPI_MAILBOX_DISABLE_IRQ	0x82001006U

/* IPI SMC Macros */
#घोषणा IPI_SMC_ENQUIRY_सूचीQ_MASK	0x00000001UL /* Flag to indicate अगर
						      * notअगरication पूर्णांकerrupt
						      * to be disabled.
						      */
#घोषणा IPI_SMC_ACK_EIRQ_MASK		0x00000001UL /* Flag to indicate अगर
						      * notअगरication पूर्णांकerrupt
						      * to be enabled.
						      */

/* IPI mailbox status */
#घोषणा IPI_MB_STATUS_IDLE		0
#घोषणा IPI_MB_STATUS_SEND_PENDING	1
#घोषणा IPI_MB_STATUS_RECV_PENDING	2

#घोषणा IPI_MB_CHNL_TX	0 /* IPI mailbox TX channel */
#घोषणा IPI_MB_CHNL_RX	1 /* IPI mailbox RX channel */

/**
 * काष्ठा zynqmp_ipi_mchan - Description of a Xilinx ZynqMP IPI mailbox channel
 * @is_खोलोed: indicate अगर the IPI channel is खोलोed
 * @req_buf: local to remote request buffer start address
 * @resp_buf: local to remote response buffer start address
 * @req_buf_size: request buffer size
 * @resp_buf_size: response buffer size
 * @rx_buf: receive buffer to pass received message to client
 * @chan_type: channel type
 */
काष्ठा zynqmp_ipi_mchan अणु
	पूर्णांक is_खोलोed;
	व्योम __iomem *req_buf;
	व्योम __iomem *resp_buf;
	व्योम *rx_buf;
	माप_प्रकार req_buf_size;
	माप_प्रकार resp_buf_size;
	अचिन्हित पूर्णांक chan_type;
पूर्ण;

/**
 * काष्ठा zynqmp_ipi_mbox - Description of a ZynqMP IPI mailbox
 *                          platक्रमm data.
 * @pdata:		  poपूर्णांकer to the IPI निजी data
 * @dev:                  device poपूर्णांकer corresponding to the Xilinx ZynqMP
 *                        IPI mailbox
 * @remote_id:            remote IPI agent ID
 * @mbox:                 mailbox Controller
 * @mchans:               array क्रम channels, tx channel and rx channel.
 * @irq:                  IPI agent पूर्णांकerrupt ID
 */
काष्ठा zynqmp_ipi_mbox अणु
	काष्ठा zynqmp_ipi_pdata *pdata;
	काष्ठा device dev;
	u32 remote_id;
	काष्ठा mbox_controller mbox;
	काष्ठा zynqmp_ipi_mchan mchans[2];
पूर्ण;

/**
 * काष्ठा zynqmp_ipi_pdata - Description of z ZynqMP IPI agent platक्रमm data.
 *
 * @dev:                  device poपूर्णांकer corresponding to the Xilinx ZynqMP
 *                        IPI agent
 * @irq:                  IPI agent पूर्णांकerrupt ID
 * @method:               IPI SMC or HVC is going to be used
 * @local_id:             local IPI agent ID
 * @num_mboxes:           number of mailboxes of this IPI agent
 * @ipi_mboxes:           IPI mailboxes of this IPI agent
 */
काष्ठा zynqmp_ipi_pdata अणु
	काष्ठा device *dev;
	पूर्णांक irq;
	अचिन्हित पूर्णांक method;
	u32 local_id;
	पूर्णांक num_mboxes;
	काष्ठा zynqmp_ipi_mbox *ipi_mboxes;
पूर्ण;

अटल काष्ठा device_driver zynqmp_ipi_mbox_driver = अणु
	.owner = THIS_MODULE,
	.name = "zynqmp-ipi-mbox",
पूर्ण;

अटल व्योम zynqmp_ipi_fw_call(काष्ठा zynqmp_ipi_mbox *ipi_mbox,
			       अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a3,
			       काष्ठा arm_smccc_res *res)
अणु
	काष्ठा zynqmp_ipi_pdata *pdata = ipi_mbox->pdata;
	अचिन्हित दीर्घ a1, a2;

	a1 = pdata->local_id;
	a2 = ipi_mbox->remote_id;
	अगर (pdata->method == USE_SMC)
		arm_smccc_smc(a0, a1, a2, a3, 0, 0, 0, 0, res);
	अन्यथा
		arm_smccc_hvc(a0, a1, a2, a3, 0, 0, 0, 0, res);
पूर्ण

/**
 * zynqmp_ipi_पूर्णांकerrupt - Interrupt handler क्रम IPI notअगरication
 *
 * @irq:  Interrupt number
 * @data: ZynqMP IPI mailbox platक्रमm data.
 *
 * Return: -EINVAL अगर there is no instance
 * IRQ_NONE अगर the पूर्णांकerrupt is not ours.
 * IRQ_HANDLED अगर the rx पूर्णांकerrupt was successfully handled.
 */
अटल irqवापस_t zynqmp_ipi_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा zynqmp_ipi_pdata *pdata = data;
	काष्ठा mbox_chan *chan;
	काष्ठा zynqmp_ipi_mbox *ipi_mbox;
	काष्ठा zynqmp_ipi_mchan *mchan;
	काष्ठा zynqmp_ipi_message *msg;
	u64 arg0, arg3;
	काष्ठा arm_smccc_res res;
	पूर्णांक ret, i;

	(व्योम)irq;
	arg0 = SMC_IPI_MAILBOX_STATUS_ENQUIRY;
	arg3 = IPI_SMC_ENQUIRY_सूचीQ_MASK;
	क्रम (i = 0; i < pdata->num_mboxes; i++) अणु
		ipi_mbox = &pdata->ipi_mboxes[i];
		mchan = &ipi_mbox->mchans[IPI_MB_CHNL_RX];
		chan = &ipi_mbox->mbox.chans[IPI_MB_CHNL_RX];
		zynqmp_ipi_fw_call(ipi_mbox, arg0, arg3, &res);
		ret = (पूर्णांक)(res.a0 & 0xFFFFFFFF);
		अगर (ret > 0 && ret & IPI_MB_STATUS_RECV_PENDING) अणु
			अगर (mchan->is_खोलोed) अणु
				msg = mchan->rx_buf;
				msg->len = mchan->req_buf_size;
				स_नकल_fromio(msg->data, mchan->req_buf,
					      msg->len);
				mbox_chan_received_data(chan, (व्योम *)msg);
				वापस IRQ_HANDLED;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

/**
 * zynqmp_ipi_peek_data - Peek to see अगर there are any rx messages.
 *
 * @chan: Channel Poपूर्णांकer
 *
 * Return: 'true' if there is pending rx data, 'false' अगर there is none.
 */
अटल bool zynqmp_ipi_peek_data(काष्ठा mbox_chan *chan)
अणु
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा zynqmp_ipi_mbox *ipi_mbox = dev_get_drvdata(dev);
	काष्ठा zynqmp_ipi_mchan *mchan = chan->con_priv;
	पूर्णांक ret;
	u64 arg0;
	काष्ठा arm_smccc_res res;

	अगर (WARN_ON(!ipi_mbox)) अणु
		dev_err(dev, "no platform drv data??\n");
		वापस false;
	पूर्ण

	arg0 = SMC_IPI_MAILBOX_STATUS_ENQUIRY;
	zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
	ret = (पूर्णांक)(res.a0 & 0xFFFFFFFF);

	अगर (mchan->chan_type == IPI_MB_CHNL_TX) अणु
		/* TX channel, check अगर the message has been acked
		 * by the remote, अगर yes, response is available.
		 */
		अगर (ret < 0 || ret & IPI_MB_STATUS_SEND_PENDING)
			वापस false;
		अन्यथा
			वापस true;
	पूर्ण अन्यथा अगर (ret > 0 && ret & IPI_MB_STATUS_RECV_PENDING) अणु
		/* RX channel, check अगर there is message arrived. */
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * zynqmp_ipi_last_tx_करोne - See अगर the last tx message is sent
 *
 * @chan: Channel poपूर्णांकer
 *
 * Return: 'true' is no pending tx data, 'false' अगर there are any.
 */
अटल bool zynqmp_ipi_last_tx_करोne(काष्ठा mbox_chan *chan)
अणु
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा zynqmp_ipi_mbox *ipi_mbox = dev_get_drvdata(dev);
	काष्ठा zynqmp_ipi_mchan *mchan = chan->con_priv;
	पूर्णांक ret;
	u64 arg0;
	काष्ठा arm_smccc_res res;

	अगर (WARN_ON(!ipi_mbox)) अणु
		dev_err(dev, "no platform drv data??\n");
		वापस false;
	पूर्ण

	अगर (mchan->chan_type == IPI_MB_CHNL_TX) अणु
		/* We only need to check अगर the message been taken
		 * by the remote in the TX channel
		 */
		arg0 = SMC_IPI_MAILBOX_STATUS_ENQUIRY;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
		/* Check the SMC call status, a0 of the result */
		ret = (पूर्णांक)(res.a0 & 0xFFFFFFFF);
		अगर (ret < 0 || ret & IPI_MB_STATUS_SEND_PENDING)
			वापस false;
		वापस true;
	पूर्ण
	/* Always true क्रम the response message in RX channel */
	वापस true;
पूर्ण

/**
 * zynqmp_ipi_send_data - Send data
 *
 * @chan: Channel Poपूर्णांकer
 * @data: Message Poपूर्णांकer
 *
 * Return: 0 अगर all goes good, अन्यथा appropriate error messages.
 */
अटल पूर्णांक zynqmp_ipi_send_data(काष्ठा mbox_chan *chan, व्योम *data)
अणु
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा zynqmp_ipi_mbox *ipi_mbox = dev_get_drvdata(dev);
	काष्ठा zynqmp_ipi_mchan *mchan = chan->con_priv;
	काष्ठा zynqmp_ipi_message *msg = data;
	u64 arg0;
	काष्ठा arm_smccc_res res;

	अगर (WARN_ON(!ipi_mbox)) अणु
		dev_err(dev, "no platform drv data??\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mchan->chan_type == IPI_MB_CHNL_TX) अणु
		/* Send request message */
		अगर (msg && msg->len > mchan->req_buf_size) अणु
			dev_err(dev, "channel %d message length %u > max %lu\n",
				mchan->chan_type, (अचिन्हित पूर्णांक)msg->len,
				mchan->req_buf_size);
			वापस -EINVAL;
		पूर्ण
		अगर (msg && msg->len)
			स_नकल_toio(mchan->req_buf, msg->data, msg->len);
		/* Kick IPI mailbox to send message */
		arg0 = SMC_IPI_MAILBOX_NOTIFY;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
	पूर्ण अन्यथा अणु
		/* Send response message */
		अगर (msg && msg->len > mchan->resp_buf_size) अणु
			dev_err(dev, "channel %d message length %u > max %lu\n",
				mchan->chan_type, (अचिन्हित पूर्णांक)msg->len,
				mchan->resp_buf_size);
			वापस -EINVAL;
		पूर्ण
		अगर (msg && msg->len)
			स_नकल_toio(mchan->resp_buf, msg->data, msg->len);
		arg0 = SMC_IPI_MAILBOX_ACK;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, IPI_SMC_ACK_EIRQ_MASK,
				   &res);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * zynqmp_ipi_startup - Startup the IPI channel
 *
 * @chan: Channel poपूर्णांकer
 *
 * Return: 0 अगर all goes good, अन्यथा वापस corresponding error message
 */
अटल पूर्णांक zynqmp_ipi_startup(काष्ठा mbox_chan *chan)
अणु
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा zynqmp_ipi_mbox *ipi_mbox = dev_get_drvdata(dev);
	काष्ठा zynqmp_ipi_mchan *mchan = chan->con_priv;
	u64 arg0;
	काष्ठा arm_smccc_res res;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक nchan_type;

	अगर (mchan->is_खोलोed)
		वापस 0;

	/* If no channel has been खोलोed, खोलो the IPI mailbox */
	nchan_type = (mchan->chan_type + 1) % 2;
	अगर (!ipi_mbox->mchans[nchan_type].is_खोलोed) अणु
		arg0 = SMC_IPI_MAILBOX_OPEN;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
		/* Check the SMC call status, a0 of the result */
		ret = (पूर्णांक)(res.a0 & 0xFFFFFFFF);
		अगर (ret < 0) अणु
			dev_err(dev, "SMC to open the IPI channel failed.\n");
			वापस ret;
		पूर्ण
		ret = 0;
	पूर्ण

	/* If it is RX channel, enable the IPI notअगरication पूर्णांकerrupt */
	अगर (mchan->chan_type == IPI_MB_CHNL_RX) अणु
		arg0 = SMC_IPI_MAILBOX_ENABLE_IRQ;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
	पूर्ण
	mchan->is_खोलोed = 1;

	वापस ret;
पूर्ण

/**
 * zynqmp_ipi_shutकरोwn - Shutकरोwn the IPI channel
 *
 * @chan: Channel poपूर्णांकer
 */
अटल व्योम zynqmp_ipi_shutकरोwn(काष्ठा mbox_chan *chan)
अणु
	काष्ठा device *dev = chan->mbox->dev;
	काष्ठा zynqmp_ipi_mbox *ipi_mbox = dev_get_drvdata(dev);
	काष्ठा zynqmp_ipi_mchan *mchan = chan->con_priv;
	u64 arg0;
	काष्ठा arm_smccc_res res;
	अचिन्हित पूर्णांक chan_type;

	अगर (!mchan->is_खोलोed)
		वापस;

	/* If it is RX channel, disable notअगरication पूर्णांकerrupt */
	chan_type = mchan->chan_type;
	अगर (chan_type == IPI_MB_CHNL_RX) अणु
		arg0 = SMC_IPI_MAILBOX_DISABLE_IRQ;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
	पूर्ण
	/* Release IPI mailbox अगर no other channel is खोलोed */
	chan_type = (chan_type + 1) % 2;
	अगर (!ipi_mbox->mchans[chan_type].is_खोलोed) अणु
		arg0 = SMC_IPI_MAILBOX_RELEASE;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
	पूर्ण

	mchan->is_खोलोed = 0;
पूर्ण

/* ZynqMP IPI mailbox operations */
अटल स्थिर काष्ठा mbox_chan_ops zynqmp_ipi_chan_ops = अणु
	.startup = zynqmp_ipi_startup,
	.shutकरोwn = zynqmp_ipi_shutकरोwn,
	.peek_data = zynqmp_ipi_peek_data,
	.last_tx_करोne = zynqmp_ipi_last_tx_करोne,
	.send_data = zynqmp_ipi_send_data,
पूर्ण;

/**
 * zynqmp_ipi_of_xlate - Translate of phandle to IPI mailbox channel
 *
 * @mbox: mailbox controller poपूर्णांकer
 * @p:    phandle poपूर्णांकer
 *
 * Return: Mailbox channel, अन्यथा वापस error poपूर्णांकer.
 */
अटल काष्ठा mbox_chan *zynqmp_ipi_of_xlate(काष्ठा mbox_controller *mbox,
					     स्थिर काष्ठा of_phandle_args *p)
अणु
	काष्ठा mbox_chan *chan;
	काष्ठा device *dev = mbox->dev;
	अचिन्हित पूर्णांक chan_type;

	/* Only supports TX and RX channels */
	chan_type = p->args[0];
	अगर (chan_type != IPI_MB_CHNL_TX && chan_type != IPI_MB_CHNL_RX) अणु
		dev_err(dev, "req chnl failure: invalid chnl type %u.\n",
			chan_type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	chan = &mbox->chans[chan_type];
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा of_device_id zynqmp_ipi_of_match[] = अणु
	अणु .compatible = "xlnx,zynqmp-ipi-mailbox" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, zynqmp_ipi_of_match);

/**
 * zynqmp_ipi_mbox_get_buf_res - Get buffer resource from the IPI dev node
 *
 * @node: IPI mbox device child node
 * @name: name of the IPI buffer
 * @res: poपूर्णांकer to where the resource inक्रमmation will be stored.
 *
 * Return: 0 क्रम success, negative value क्रम failure
 */
अटल पूर्णांक zynqmp_ipi_mbox_get_buf_res(काष्ठा device_node *node,
				       स्थिर अक्षर *name,
				       काष्ठा resource *res)
अणु
	पूर्णांक ret, index;

	index = of_property_match_string(node, "reg-names", name);
	अगर (index >= 0) अणु
		ret = of_address_to_resource(node, index, res);
		अगर (ret < 0)
			वापस -EINVAL;
		वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

/**
 * zynqmp_ipi_mbox_dev_release() - release the existence of a ipi mbox dev
 *
 * @dev: the ipi mailbox device
 *
 * This is to aव्योम the no device release() function kernel warning.
 *
 */
अटल व्योम zynqmp_ipi_mbox_dev_release(काष्ठा device *dev)
अणु
	(व्योम)dev;
पूर्ण

/**
 * zynqmp_ipi_mbox_probe - probe IPI mailbox resource from device node
 *
 * @ipi_mbox: poपूर्णांकer to IPI mailbox निजी data काष्ठाure
 * @node: IPI mailbox device node
 *
 * Return: 0 क्रम success, negative value क्रम failure
 */
अटल पूर्णांक zynqmp_ipi_mbox_probe(काष्ठा zynqmp_ipi_mbox *ipi_mbox,
				 काष्ठा device_node *node)
अणु
	काष्ठा zynqmp_ipi_mchan *mchan;
	काष्ठा mbox_chan *chans;
	काष्ठा mbox_controller *mbox;
	काष्ठा resource res;
	काष्ठा device *dev, *mdev;
	स्थिर अक्षर *name;
	पूर्णांक ret;

	dev = ipi_mbox->pdata->dev;
	/* Initialize dev क्रम IPI mailbox */
	ipi_mbox->dev.parent = dev;
	ipi_mbox->dev.release = शून्य;
	ipi_mbox->dev.of_node = node;
	dev_set_name(&ipi_mbox->dev, "%s", of_node_full_name(node));
	dev_set_drvdata(&ipi_mbox->dev, ipi_mbox);
	ipi_mbox->dev.release = zynqmp_ipi_mbox_dev_release;
	ipi_mbox->dev.driver = &zynqmp_ipi_mbox_driver;
	ret = device_रेजिस्टर(&ipi_mbox->dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register ipi mbox dev.\n");
		वापस ret;
	पूर्ण
	mdev = &ipi_mbox->dev;

	mchan = &ipi_mbox->mchans[IPI_MB_CHNL_TX];
	name = "local_request_region";
	ret = zynqmp_ipi_mbox_get_buf_res(node, name, &res);
	अगर (!ret) अणु
		mchan->req_buf_size = resource_size(&res);
		mchan->req_buf = devm_ioremap(mdev, res.start,
					      mchan->req_buf_size);
		अगर (!mchan->req_buf) अणु
			dev_err(mdev, "Unable to map IPI buffer I/O memory\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (ret != -ENODEV) अणु
		dev_err(mdev, "Unmatched resource %s, %d.\n", name, ret);
		वापस ret;
	पूर्ण

	name = "remote_response_region";
	ret = zynqmp_ipi_mbox_get_buf_res(node, name, &res);
	अगर (!ret) अणु
		mchan->resp_buf_size = resource_size(&res);
		mchan->resp_buf = devm_ioremap(mdev, res.start,
					       mchan->resp_buf_size);
		अगर (!mchan->resp_buf) अणु
			dev_err(mdev, "Unable to map IPI buffer I/O memory\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (ret != -ENODEV) अणु
		dev_err(mdev, "Unmatched resource %s.\n", name);
		वापस ret;
	पूर्ण
	mchan->rx_buf = devm_kzalloc(mdev,
				     mchan->resp_buf_size +
				     माप(काष्ठा zynqmp_ipi_message),
				     GFP_KERNEL);
	अगर (!mchan->rx_buf)
		वापस -ENOMEM;

	mchan = &ipi_mbox->mchans[IPI_MB_CHNL_RX];
	name = "remote_request_region";
	ret = zynqmp_ipi_mbox_get_buf_res(node, name, &res);
	अगर (!ret) अणु
		mchan->req_buf_size = resource_size(&res);
		mchan->req_buf = devm_ioremap(mdev, res.start,
					      mchan->req_buf_size);
		अगर (!mchan->req_buf) अणु
			dev_err(mdev, "Unable to map IPI buffer I/O memory\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (ret != -ENODEV) अणु
		dev_err(mdev, "Unmatched resource %s.\n", name);
		वापस ret;
	पूर्ण

	name = "local_response_region";
	ret = zynqmp_ipi_mbox_get_buf_res(node, name, &res);
	अगर (!ret) अणु
		mchan->resp_buf_size = resource_size(&res);
		mchan->resp_buf = devm_ioremap(mdev, res.start,
					       mchan->resp_buf_size);
		अगर (!mchan->resp_buf) अणु
			dev_err(mdev, "Unable to map IPI buffer I/O memory\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (ret != -ENODEV) अणु
		dev_err(mdev, "Unmatched resource %s.\n", name);
		वापस ret;
	पूर्ण
	mchan->rx_buf = devm_kzalloc(mdev,
				     mchan->resp_buf_size +
				     माप(काष्ठा zynqmp_ipi_message),
				     GFP_KERNEL);
	अगर (!mchan->rx_buf)
		वापस -ENOMEM;

	/* Get the IPI remote agent ID */
	ret = of_property_पढ़ो_u32(node, "xlnx,ipi-id", &ipi_mbox->remote_id);
	अगर (ret < 0) अणु
		dev_err(dev, "No IPI remote ID is specified.\n");
		वापस ret;
	पूर्ण

	mbox = &ipi_mbox->mbox;
	mbox->dev = mdev;
	mbox->ops = &zynqmp_ipi_chan_ops;
	mbox->num_chans = 2;
	mbox->txकरोne_irq = false;
	mbox->txकरोne_poll = true;
	mbox->txpoll_period = 5;
	mbox->of_xlate = zynqmp_ipi_of_xlate;
	chans = devm_kzalloc(mdev, 2 * माप(*chans), GFP_KERNEL);
	अगर (!chans)
		वापस -ENOMEM;
	mbox->chans = chans;
	chans[IPI_MB_CHNL_TX].con_priv = &ipi_mbox->mchans[IPI_MB_CHNL_TX];
	chans[IPI_MB_CHNL_RX].con_priv = &ipi_mbox->mchans[IPI_MB_CHNL_RX];
	ipi_mbox->mchans[IPI_MB_CHNL_TX].chan_type = IPI_MB_CHNL_TX;
	ipi_mbox->mchans[IPI_MB_CHNL_RX].chan_type = IPI_MB_CHNL_RX;
	ret = devm_mbox_controller_रेजिस्टर(mdev, mbox);
	अगर (ret)
		dev_err(mdev,
			"Failed to register mbox_controller(%d)\n", ret);
	अन्यथा
		dev_info(mdev,
			 "Registered ZynqMP IPI mbox with TX/RX channels.\n");
	वापस ret;
पूर्ण

/**
 * zynqmp_ipi_मुक्त_mboxes - Free IPI mailboxes devices
 *
 * @pdata: IPI निजी data
 */
अटल व्योम zynqmp_ipi_मुक्त_mboxes(काष्ठा zynqmp_ipi_pdata *pdata)
अणु
	काष्ठा zynqmp_ipi_mbox *ipi_mbox;
	पूर्णांक i;

	i = pdata->num_mboxes;
	क्रम (; i >= 0; i--) अणु
		ipi_mbox = &pdata->ipi_mboxes[i];
		अगर (ipi_mbox->dev.parent) अणु
			mbox_controller_unरेजिस्टर(&ipi_mbox->mbox);
			device_unरेजिस्टर(&ipi_mbox->dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक zynqmp_ipi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *nc, *np = pdev->dev.of_node;
	काष्ठा zynqmp_ipi_pdata *pdata;
	काष्ठा zynqmp_ipi_mbox *mbox;
	पूर्णांक num_mboxes, ret = -EINVAL;

	num_mboxes = of_get_child_count(np);
	pdata = devm_kzalloc(dev, माप(*pdata) + (num_mboxes * माप(*mbox)),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;
	pdata->dev = dev;

	/* Get the IPI local agents ID */
	ret = of_property_पढ़ो_u32(np, "xlnx,ipi-id", &pdata->local_id);
	अगर (ret < 0) अणु
		dev_err(dev, "No IPI local ID is specified.\n");
		वापस ret;
	पूर्ण

	pdata->num_mboxes = num_mboxes;
	pdata->ipi_mboxes = (काष्ठा zynqmp_ipi_mbox *)
			    ((अक्षर *)pdata + माप(*pdata));

	mbox = pdata->ipi_mboxes;
	क्रम_each_available_child_of_node(np, nc) अणु
		mbox->pdata = pdata;
		ret = zynqmp_ipi_mbox_probe(mbox, nc);
		अगर (ret) अणु
			dev_err(dev, "failed to probe subdev.\n");
			ret = -EINVAL;
			जाओ मुक्त_mbox_dev;
		पूर्ण
		mbox++;
	पूर्ण

	/* IPI IRQ */
	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ मुक्त_mbox_dev;

	pdata->irq = ret;
	ret = devm_request_irq(dev, pdata->irq, zynqmp_ipi_पूर्णांकerrupt,
			       IRQF_SHARED, dev_name(dev), pdata);
	अगर (ret) अणु
		dev_err(dev, "IRQ %d is not requested successfully.\n",
			pdata->irq);
		जाओ मुक्त_mbox_dev;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pdata);
	वापस ret;

मुक्त_mbox_dev:
	zynqmp_ipi_मुक्त_mboxes(pdata);
	वापस ret;
पूर्ण

अटल पूर्णांक zynqmp_ipi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा zynqmp_ipi_pdata *pdata;

	pdata = platक्रमm_get_drvdata(pdev);
	zynqmp_ipi_मुक्त_mboxes(pdata);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver zynqmp_ipi_driver = अणु
	.probe = zynqmp_ipi_probe,
	.हटाओ = zynqmp_ipi_हटाओ,
	.driver = अणु
		   .name = "zynqmp-ipi",
		   .of_match_table = of_match_ptr(zynqmp_ipi_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init zynqmp_ipi_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&zynqmp_ipi_driver);
पूर्ण
subsys_initcall(zynqmp_ipi_init);

अटल व्योम __निकास zynqmp_ipi_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&zynqmp_ipi_driver);
पूर्ण
module_निकास(zynqmp_ipi_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Xilinx ZynqMP IPI Mailbox driver");
MODULE_AUTHOR("Xilinx Inc.");
