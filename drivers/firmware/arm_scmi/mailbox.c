<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface (SCMI) Message Mailbox Transport
 * driver.
 *
 * Copyright (C) 2019 ARM Ltd.
 */

#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश "common.h"

/**
 * काष्ठा scmi_mailbox - Structure representing a SCMI mailbox transport
 *
 * @cl: Mailbox Client
 * @chan: Transmit/Receive mailbox channel
 * @cinfo: SCMI channel info
 * @shmem: Transmit/Receive shared memory area
 */
काष्ठा scmi_mailbox अणु
	काष्ठा mbox_client cl;
	काष्ठा mbox_chan *chan;
	काष्ठा scmi_chan_info *cinfo;
	काष्ठा scmi_shared_mem __iomem *shmem;
पूर्ण;

#घोषणा client_to_scmi_mailbox(c) container_of(c, काष्ठा scmi_mailbox, cl)

अटल व्योम tx_prepare(काष्ठा mbox_client *cl, व्योम *m)
अणु
	काष्ठा scmi_mailbox *smbox = client_to_scmi_mailbox(cl);

	shmem_tx_prepare(smbox->shmem, m);
पूर्ण

अटल व्योम rx_callback(काष्ठा mbox_client *cl, व्योम *m)
अणु
	काष्ठा scmi_mailbox *smbox = client_to_scmi_mailbox(cl);

	scmi_rx_callback(smbox->cinfo, shmem_पढ़ो_header(smbox->shmem));
पूर्ण

अटल bool mailbox_chan_available(काष्ठा device *dev, पूर्णांक idx)
अणु
	वापस !of_parse_phandle_with_args(dev->of_node, "mboxes",
					   "#mbox-cells", idx, शून्य);
पूर्ण

अटल पूर्णांक mailbox_chan_setup(काष्ठा scmi_chan_info *cinfo, काष्ठा device *dev,
			      bool tx)
अणु
	स्थिर अक्षर *desc = tx ? "Tx" : "Rx";
	काष्ठा device *cdev = cinfo->dev;
	काष्ठा scmi_mailbox *smbox;
	काष्ठा device_node *shmem;
	पूर्णांक ret, idx = tx ? 0 : 1;
	काष्ठा mbox_client *cl;
	resource_माप_प्रकार size;
	काष्ठा resource res;

	smbox = devm_kzalloc(dev, माप(*smbox), GFP_KERNEL);
	अगर (!smbox)
		वापस -ENOMEM;

	shmem = of_parse_phandle(cdev->of_node, "shmem", idx);
	ret = of_address_to_resource(shmem, 0, &res);
	of_node_put(shmem);
	अगर (ret) अणु
		dev_err(cdev, "failed to get SCMI %s shared memory\n", desc);
		वापस ret;
	पूर्ण

	size = resource_size(&res);
	smbox->shmem = devm_ioremap(dev, res.start, size);
	अगर (!smbox->shmem) अणु
		dev_err(dev, "failed to ioremap SCMI %s shared memory\n", desc);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	cl = &smbox->cl;
	cl->dev = cdev;
	cl->tx_prepare = tx ? tx_prepare : शून्य;
	cl->rx_callback = rx_callback;
	cl->tx_block = false;
	cl->knows_txकरोne = tx;

	smbox->chan = mbox_request_channel(cl, tx ? 0 : 1);
	अगर (IS_ERR(smbox->chan)) अणु
		ret = PTR_ERR(smbox->chan);
		अगर (ret != -EPROBE_DEFER)
			dev_err(cdev, "failed to request SCMI %s mailbox\n",
				tx ? "Tx" : "Rx");
		वापस ret;
	पूर्ण

	cinfo->transport_info = smbox;
	smbox->cinfo = cinfo;

	वापस 0;
पूर्ण

अटल पूर्णांक mailbox_chan_मुक्त(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा scmi_chan_info *cinfo = p;
	काष्ठा scmi_mailbox *smbox = cinfo->transport_info;

	अगर (smbox && !IS_ERR(smbox->chan)) अणु
		mbox_मुक्त_channel(smbox->chan);
		cinfo->transport_info = शून्य;
		smbox->chan = शून्य;
		smbox->cinfo = शून्य;
	पूर्ण

	scmi_मुक्त_channel(cinfo, data, id);

	वापस 0;
पूर्ण

अटल पूर्णांक mailbox_send_message(काष्ठा scmi_chan_info *cinfo,
				काष्ठा scmi_xfer *xfer)
अणु
	काष्ठा scmi_mailbox *smbox = cinfo->transport_info;
	पूर्णांक ret;

	ret = mbox_send_message(smbox->chan, xfer);

	/* mbox_send_message वापसs non-negative value on success, so reset */
	अगर (ret > 0)
		ret = 0;

	वापस ret;
पूर्ण

अटल व्योम mailbox_mark_txकरोne(काष्ठा scmi_chan_info *cinfo, पूर्णांक ret)
अणु
	काष्ठा scmi_mailbox *smbox = cinfo->transport_info;

	/*
	 * NOTE: we might prefer not to need the mailbox ticker to manage the
	 * transfer queueing since the protocol layer queues things by itself.
	 * Unक्रमtunately, we have to kick the mailbox framework after we have
	 * received our message.
	 */
	mbox_client_txकरोne(smbox->chan, ret);
पूर्ण

अटल व्योम mailbox_fetch_response(काष्ठा scmi_chan_info *cinfo,
				   काष्ठा scmi_xfer *xfer)
अणु
	काष्ठा scmi_mailbox *smbox = cinfo->transport_info;

	shmem_fetch_response(smbox->shmem, xfer);
पूर्ण

अटल व्योम mailbox_fetch_notअगरication(काष्ठा scmi_chan_info *cinfo,
				       माप_प्रकार max_len, काष्ठा scmi_xfer *xfer)
अणु
	काष्ठा scmi_mailbox *smbox = cinfo->transport_info;

	shmem_fetch_notअगरication(smbox->shmem, max_len, xfer);
पूर्ण

अटल व्योम mailbox_clear_channel(काष्ठा scmi_chan_info *cinfo)
अणु
	काष्ठा scmi_mailbox *smbox = cinfo->transport_info;

	shmem_clear_channel(smbox->shmem);
पूर्ण

अटल bool
mailbox_poll_करोne(काष्ठा scmi_chan_info *cinfo, काष्ठा scmi_xfer *xfer)
अणु
	काष्ठा scmi_mailbox *smbox = cinfo->transport_info;

	वापस shmem_poll_करोne(smbox->shmem, xfer);
पूर्ण

अटल स्थिर काष्ठा scmi_transport_ops scmi_mailbox_ops = अणु
	.chan_available = mailbox_chan_available,
	.chan_setup = mailbox_chan_setup,
	.chan_मुक्त = mailbox_chan_मुक्त,
	.send_message = mailbox_send_message,
	.mark_txकरोne = mailbox_mark_txकरोne,
	.fetch_response = mailbox_fetch_response,
	.fetch_notअगरication = mailbox_fetch_notअगरication,
	.clear_channel = mailbox_clear_channel,
	.poll_करोne = mailbox_poll_करोne,
पूर्ण;

स्थिर काष्ठा scmi_desc scmi_mailbox_desc = अणु
	.ops = &scmi_mailbox_ops,
	.max_rx_समयout_ms = 30, /* We may increase this अगर required */
	.max_msg = 20, /* Limited by MBOX_TX_QUEUE_LEN */
	.max_msg_size = 128,
पूर्ण;
