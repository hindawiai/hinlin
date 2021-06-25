<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2019 NXP
 *  Author: Daniel Baluta <daniel.baluta@nxp.com>
 *
 * Implementation of the DSP IPC पूर्णांकerface (host side)
 */

#समावेश <linux/firmware/imx/dsp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/*
 * imx_dsp_ring_करोorbell - triggers an पूर्णांकerrupt on the other side (DSP)
 *
 * @dsp: DSP IPC handle
 * @chan_idx: index of the channel where to trigger the पूर्णांकerrupt
 *
 * Returns non-negative value क्रम success, negative value क्रम error
 */
पूर्णांक imx_dsp_ring_करोorbell(काष्ठा imx_dsp_ipc *ipc, अचिन्हित पूर्णांक idx)
अणु
	पूर्णांक ret;
	काष्ठा imx_dsp_chan *dsp_chan;

	अगर (idx >= DSP_MU_CHAN_NUM)
		वापस -EINVAL;

	dsp_chan = &ipc->chans[idx];
	ret = mbox_send_message(dsp_chan->ch, शून्य);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(imx_dsp_ring_करोorbell);

/*
 * imx_dsp_handle_rx - rx callback used by imx mailbox
 *
 * @c: mbox client
 * @msg: message received
 *
 * Users of DSP IPC will need to privde handle_reply and handle_request
 * callbacks.
 */
अटल व्योम imx_dsp_handle_rx(काष्ठा mbox_client *c, व्योम *msg)
अणु
	काष्ठा imx_dsp_chan *chan = container_of(c, काष्ठा imx_dsp_chan, cl);

	अगर (chan->idx == 0) अणु
		chan->ipc->ops->handle_reply(chan->ipc);
	पूर्ण अन्यथा अणु
		chan->ipc->ops->handle_request(chan->ipc);
		imx_dsp_ring_करोorbell(chan->ipc, 1);
	पूर्ण
पूर्ण

काष्ठा mbox_chan *imx_dsp_request_channel(काष्ठा imx_dsp_ipc *dsp_ipc, पूर्णांक idx)
अणु
	काष्ठा imx_dsp_chan *dsp_chan;

	अगर (idx >= DSP_MU_CHAN_NUM)
		वापस ERR_PTR(-EINVAL);

	dsp_chan = &dsp_ipc->chans[idx];
	dsp_chan->ch = mbox_request_channel_byname(&dsp_chan->cl, dsp_chan->name);
	वापस dsp_chan->ch;
पूर्ण
EXPORT_SYMBOL(imx_dsp_request_channel);

व्योम imx_dsp_मुक्त_channel(काष्ठा imx_dsp_ipc *dsp_ipc, पूर्णांक idx)
अणु
	काष्ठा imx_dsp_chan *dsp_chan;

	अगर (idx >= DSP_MU_CHAN_NUM)
		वापस;

	dsp_chan = &dsp_ipc->chans[idx];
	mbox_मुक्त_channel(dsp_chan->ch);
पूर्ण
EXPORT_SYMBOL(imx_dsp_मुक्त_channel);

अटल पूर्णांक imx_dsp_setup_channels(काष्ठा imx_dsp_ipc *dsp_ipc)
अणु
	काष्ठा device *dev = dsp_ipc->dev;
	काष्ठा imx_dsp_chan *dsp_chan;
	काष्ठा mbox_client *cl;
	अक्षर *chan_name;
	पूर्णांक ret;
	पूर्णांक i, j;

	क्रम (i = 0; i < DSP_MU_CHAN_NUM; i++) अणु
		अगर (i < 2)
			chan_name = kaप्र_लिखो(GFP_KERNEL, "txdb%d", i);
		अन्यथा
			chan_name = kaप्र_लिखो(GFP_KERNEL, "rxdb%d", i - 2);

		अगर (!chan_name)
			वापस -ENOMEM;

		dsp_chan = &dsp_ipc->chans[i];
		dsp_chan->name = chan_name;
		cl = &dsp_chan->cl;
		cl->dev = dev;
		cl->tx_block = false;
		cl->knows_txकरोne = true;
		cl->rx_callback = imx_dsp_handle_rx;

		dsp_chan->ipc = dsp_ipc;
		dsp_chan->idx = i % 2;
		dsp_chan->ch = mbox_request_channel_byname(cl, chan_name);
		अगर (IS_ERR(dsp_chan->ch)) अणु
			ret = PTR_ERR(dsp_chan->ch);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to request mbox chan %s ret %d\n",
					chan_name, ret);
			जाओ out;
		पूर्ण

		dev_dbg(dev, "request mbox chan %s\n", chan_name);
	पूर्ण

	वापस 0;
out:
	क्रम (j = 0; j < i; j++) अणु
		dsp_chan = &dsp_ipc->chans[j];
		mbox_मुक्त_channel(dsp_chan->ch);
		kमुक्त(dsp_chan->name);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imx_dsp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा imx_dsp_ipc *dsp_ipc;
	पूर्णांक ret;

	device_set_of_node_from_dev(&pdev->dev, pdev->dev.parent);

	dsp_ipc = devm_kzalloc(dev, माप(*dsp_ipc), GFP_KERNEL);
	अगर (!dsp_ipc)
		वापस -ENOMEM;

	dsp_ipc->dev = dev;
	dev_set_drvdata(dev, dsp_ipc);

	ret = imx_dsp_setup_channels(dsp_ipc);
	अगर (ret < 0)
		वापस ret;

	dev_info(dev, "NXP i.MX DSP IPC initialized\n");

	वापस 0;
पूर्ण

अटल पूर्णांक imx_dsp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_dsp_chan *dsp_chan;
	काष्ठा imx_dsp_ipc *dsp_ipc;
	पूर्णांक i;

	dsp_ipc = dev_get_drvdata(&pdev->dev);

	क्रम (i = 0; i < DSP_MU_CHAN_NUM; i++) अणु
		dsp_chan = &dsp_ipc->chans[i];
		mbox_मुक्त_channel(dsp_chan->ch);
		kमुक्त(dsp_chan->name);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver imx_dsp_driver = अणु
	.driver = अणु
		.name = "imx-dsp",
	पूर्ण,
	.probe = imx_dsp_probe,
	.हटाओ = imx_dsp_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(imx_dsp_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@nxp.com>");
MODULE_DESCRIPTION("IMX DSP IPC protocol driver");
MODULE_LICENSE("GPL v2");
