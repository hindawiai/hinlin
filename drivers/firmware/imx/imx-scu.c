<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2018 NXP
 *  Author: Dong Aisheng <aisheng.करोng@nxp.com>
 *
 * Implementation of the SCU IPC functions using MUs (client side).
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/firmware/imx/ipc.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mailbox_client.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा SCU_MU_CHAN_NUM		8
#घोषणा MAX_RX_TIMEOUT		(msecs_to_jअगरfies(30))

काष्ठा imx_sc_chan अणु
	काष्ठा imx_sc_ipc *sc_ipc;

	काष्ठा mbox_client cl;
	काष्ठा mbox_chan *ch;
	पूर्णांक idx;
	काष्ठा completion tx_करोne;
पूर्ण;

काष्ठा imx_sc_ipc अणु
	/* SCU uses 4 Tx and 4 Rx channels */
	काष्ठा imx_sc_chan chans[SCU_MU_CHAN_NUM];
	काष्ठा device *dev;
	काष्ठा mutex lock;
	काष्ठा completion करोne;
	bool fast_ipc;

	/* temporarily store the SCU msg */
	u32 *msg;
	u8 rx_size;
	u8 count;
पूर्ण;

/*
 * This type is used to indicate error response क्रम most functions.
 */
क्रमागत imx_sc_error_codes अणु
	IMX_SC_ERR_NONE = 0,	/* Success */
	IMX_SC_ERR_VERSION = 1,	/* Incompatible API version */
	IMX_SC_ERR_CONFIG = 2,	/* Configuration error */
	IMX_SC_ERR_PARM = 3,	/* Bad parameter */
	IMX_SC_ERR_NOACCESS = 4,	/* Permission error (no access) */
	IMX_SC_ERR_LOCKED = 5,	/* Permission error (locked) */
	IMX_SC_ERR_UNAVAILABLE = 6,	/* Unavailable (out of resources) */
	IMX_SC_ERR_NOTFOUND = 7,	/* Not found */
	IMX_SC_ERR_NOPOWER = 8,	/* No घातer */
	IMX_SC_ERR_IPC = 9,		/* Generic IPC error */
	IMX_SC_ERR_BUSY = 10,	/* Resource is currently busy/active */
	IMX_SC_ERR_FAIL = 11,	/* General I/O failure */
	IMX_SC_ERR_LAST
पूर्ण;

अटल पूर्णांक imx_sc_linux_errmap[IMX_SC_ERR_LAST] = अणु
	0,	 /* IMX_SC_ERR_NONE */
	-EINVAL, /* IMX_SC_ERR_VERSION */
	-EINVAL, /* IMX_SC_ERR_CONFIG */
	-EINVAL, /* IMX_SC_ERR_PARM */
	-EACCES, /* IMX_SC_ERR_NOACCESS */
	-EACCES, /* IMX_SC_ERR_LOCKED */
	-दुस्फल, /* IMX_SC_ERR_UNAVAILABLE */
	-EEXIST, /* IMX_SC_ERR_NOTFOUND */
	-EPERM,	 /* IMX_SC_ERR_NOPOWER */
	-EPIPE,	 /* IMX_SC_ERR_IPC */
	-EBUSY,	 /* IMX_SC_ERR_BUSY */
	-EIO,	 /* IMX_SC_ERR_FAIL */
पूर्ण;

अटल काष्ठा imx_sc_ipc *imx_sc_ipc_handle;

अटल अंतरभूत पूर्णांक imx_sc_to_linux_त्रुटि_सं(पूर्णांक त्रुटि_सं)
अणु
	अगर (त्रुटि_सं >= IMX_SC_ERR_NONE && त्रुटि_सं < IMX_SC_ERR_LAST)
		वापस imx_sc_linux_errmap[त्रुटि_सं];
	वापस -EIO;
पूर्ण

/*
 * Get the शेष handle used by SCU
 */
पूर्णांक imx_scu_get_handle(काष्ठा imx_sc_ipc **ipc)
अणु
	अगर (!imx_sc_ipc_handle)
		वापस -EPROBE_DEFER;

	*ipc = imx_sc_ipc_handle;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(imx_scu_get_handle);

/* Callback called when the word of a message is ack-ed, eg पढ़ो by SCU */
अटल व्योम imx_scu_tx_करोne(काष्ठा mbox_client *cl, व्योम *mssg, पूर्णांक r)
अणु
	काष्ठा imx_sc_chan *sc_chan = container_of(cl, काष्ठा imx_sc_chan, cl);

	complete(&sc_chan->tx_करोne);
पूर्ण

अटल व्योम imx_scu_rx_callback(काष्ठा mbox_client *c, व्योम *msg)
अणु
	काष्ठा imx_sc_chan *sc_chan = container_of(c, काष्ठा imx_sc_chan, cl);
	काष्ठा imx_sc_ipc *sc_ipc = sc_chan->sc_ipc;
	काष्ठा imx_sc_rpc_msg *hdr;
	u32 *data = msg;
	पूर्णांक i;

	अगर (!sc_ipc->msg) अणु
		dev_warn(sc_ipc->dev, "unexpected rx idx %d 0x%08x, ignore!\n",
				sc_chan->idx, *data);
		वापस;
	पूर्ण

	अगर (sc_ipc->fast_ipc) अणु
		hdr = msg;
		sc_ipc->rx_size = hdr->size;
		sc_ipc->msg[0] = *data++;

		क्रम (i = 1; i < sc_ipc->rx_size; i++)
			sc_ipc->msg[i] = *data++;

		complete(&sc_ipc->करोne);

		वापस;
	पूर्ण

	अगर (sc_chan->idx == 0) अणु
		hdr = msg;
		sc_ipc->rx_size = hdr->size;
		dev_dbg(sc_ipc->dev, "msg rx size %u\n", sc_ipc->rx_size);
		अगर (sc_ipc->rx_size > 4)
			dev_warn(sc_ipc->dev, "RPC does not support receiving over 4 words: %u\n",
				 sc_ipc->rx_size);
	पूर्ण

	sc_ipc->msg[sc_chan->idx] = *data;
	sc_ipc->count++;

	dev_dbg(sc_ipc->dev, "mu %u msg %u 0x%x\n", sc_chan->idx,
		sc_ipc->count, *data);

	अगर ((sc_ipc->rx_size != 0) && (sc_ipc->count == sc_ipc->rx_size))
		complete(&sc_ipc->करोne);
पूर्ण

अटल पूर्णांक imx_scu_ipc_ग_लिखो(काष्ठा imx_sc_ipc *sc_ipc, व्योम *msg)
अणु
	काष्ठा imx_sc_rpc_msg hdr = *(काष्ठा imx_sc_rpc_msg *)msg;
	काष्ठा imx_sc_chan *sc_chan;
	u32 *data = msg;
	पूर्णांक ret;
	पूर्णांक size;
	पूर्णांक i;

	/* Check size */
	अगर (hdr.size > IMX_SC_RPC_MAX_MSG)
		वापस -EINVAL;

	dev_dbg(sc_ipc->dev, "RPC SVC %u FUNC %u SIZE %u\n", hdr.svc,
		hdr.func, hdr.size);

	size = sc_ipc->fast_ipc ? 1 : hdr.size;
	क्रम (i = 0; i < size; i++) अणु
		sc_chan = &sc_ipc->chans[i % 4];

		/*
		 * SCU requires that all messages words are written
		 * sequentially but linux MU driver implements multiple
		 * independent channels क्रम each रेजिस्टर so ordering between
		 * dअगरferent channels must be ensured by SCU API पूर्णांकerface.
		 *
		 * Wait क्रम tx_करोne beक्रमe every send to ensure that no
		 * queueing happens at the mailbox channel level.
		 */
		अगर (!sc_ipc->fast_ipc) अणु
			रुको_क्रम_completion(&sc_chan->tx_करोne);
			reinit_completion(&sc_chan->tx_करोne);
		पूर्ण

		ret = mbox_send_message(sc_chan->ch, &data[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * RPC command/response
 */
पूर्णांक imx_scu_call_rpc(काष्ठा imx_sc_ipc *sc_ipc, व्योम *msg, bool have_resp)
अणु
	uपूर्णांक8_t saved_svc, saved_func;
	काष्ठा imx_sc_rpc_msg *hdr;
	पूर्णांक ret;

	अगर (WARN_ON(!sc_ipc || !msg))
		वापस -EINVAL;

	mutex_lock(&sc_ipc->lock);
	reinit_completion(&sc_ipc->करोne);

	अगर (have_resp) अणु
		sc_ipc->msg = msg;
		saved_svc = ((काष्ठा imx_sc_rpc_msg *)msg)->svc;
		saved_func = ((काष्ठा imx_sc_rpc_msg *)msg)->func;
	पूर्ण
	sc_ipc->count = 0;
	ret = imx_scu_ipc_ग_लिखो(sc_ipc, msg);
	अगर (ret < 0) अणु
		dev_err(sc_ipc->dev, "RPC send msg failed: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (have_resp) अणु
		अगर (!रुको_क्रम_completion_समयout(&sc_ipc->करोne,
						 MAX_RX_TIMEOUT)) अणु
			dev_err(sc_ipc->dev, "RPC send msg timeout\n");
			mutex_unlock(&sc_ipc->lock);
			वापस -ETIMEDOUT;
		पूर्ण

		/* response status is stored in hdr->func field */
		hdr = msg;
		ret = hdr->func;
		/*
		 * Some special SCU firmware APIs करो NOT have वापस value
		 * in hdr->func, but they करो have response data, those special
		 * APIs are defined as व्योम function in SCU firmware, so they
		 * should be treated as वापस success always.
		 */
		अगर ((saved_svc == IMX_SC_RPC_SVC_MISC) &&
			(saved_func == IMX_SC_MISC_FUNC_UNIQUE_ID ||
			 saved_func == IMX_SC_MISC_FUNC_GET_BUTTON_STATUS))
			ret = 0;
	पूर्ण

out:
	sc_ipc->msg = शून्य;
	mutex_unlock(&sc_ipc->lock);

	dev_dbg(sc_ipc->dev, "RPC SVC done\n");

	वापस imx_sc_to_linux_त्रुटि_सं(ret);
पूर्ण
EXPORT_SYMBOL(imx_scu_call_rpc);

अटल पूर्णांक imx_scu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा imx_sc_ipc *sc_ipc;
	काष्ठा imx_sc_chan *sc_chan;
	काष्ठा mbox_client *cl;
	अक्षर *chan_name;
	काष्ठा of_phandle_args args;
	पूर्णांक num_channel;
	पूर्णांक ret;
	पूर्णांक i;

	sc_ipc = devm_kzalloc(dev, माप(*sc_ipc), GFP_KERNEL);
	अगर (!sc_ipc)
		वापस -ENOMEM;

	ret = of_parse_phandle_with_args(pdev->dev.of_node, "mboxes",
					 "#mbox-cells", 0, &args);
	अगर (ret)
		वापस ret;

	sc_ipc->fast_ipc = of_device_is_compatible(args.np, "fsl,imx8-mu-scu");

	num_channel = sc_ipc->fast_ipc ? 2 : SCU_MU_CHAN_NUM;
	क्रम (i = 0; i < num_channel; i++) अणु
		अगर (i < num_channel / 2)
			chan_name = kaप्र_लिखो(GFP_KERNEL, "tx%d", i);
		अन्यथा
			chan_name = kaप्र_लिखो(GFP_KERNEL, "rx%d",
					      i - num_channel / 2);

		अगर (!chan_name)
			वापस -ENOMEM;

		sc_chan = &sc_ipc->chans[i];
		cl = &sc_chan->cl;
		cl->dev = dev;
		cl->tx_block = false;
		cl->knows_txकरोne = true;
		cl->rx_callback = imx_scu_rx_callback;

		अगर (!sc_ipc->fast_ipc) अणु
			/* Initial tx_करोne completion as "done" */
			cl->tx_करोne = imx_scu_tx_करोne;
			init_completion(&sc_chan->tx_करोne);
			complete(&sc_chan->tx_करोne);
		पूर्ण

		sc_chan->sc_ipc = sc_ipc;
		sc_chan->idx = i % (num_channel / 2);
		sc_chan->ch = mbox_request_channel_byname(cl, chan_name);
		अगर (IS_ERR(sc_chan->ch)) अणु
			ret = PTR_ERR(sc_chan->ch);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to request mbox chan %s ret %d\n",
					chan_name, ret);
			kमुक्त(chan_name);
			वापस ret;
		पूर्ण

		dev_dbg(dev, "request mbox chan %s\n", chan_name);
		/* chan_name is not used anymore by framework */
		kमुक्त(chan_name);
	पूर्ण

	sc_ipc->dev = dev;
	mutex_init(&sc_ipc->lock);
	init_completion(&sc_ipc->करोne);

	imx_sc_ipc_handle = sc_ipc;

	ret = imx_scu_soc_init(dev);
	अगर (ret)
		dev_warn(dev, "failed to initialize SoC info: %d\n", ret);

	ret = imx_scu_enable_general_irq_channel(dev);
	अगर (ret)
		dev_warn(dev,
			"failed to enable general irq channel: %d\n", ret);

	dev_info(dev, "NXP i.MX SCU Initialized\n");

	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_scu_match[] = अणु
	अणु .compatible = "fsl,imx-scu", पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_scu_driver = अणु
	.driver = अणु
		.name = "imx-scu",
		.of_match_table = imx_scu_match,
	पूर्ण,
	.probe = imx_scu_probe,
पूर्ण;
builtin_platक्रमm_driver(imx_scu_driver);

MODULE_AUTHOR("Dong Aisheng <aisheng.dong@nxp.com>");
MODULE_DESCRIPTION("IMX SCU firmware protocol driver");
MODULE_LICENSE("GPL v2");
