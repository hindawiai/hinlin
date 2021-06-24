<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// Copyright 2020 NXP
//
// Author: Daniel Baluta <daniel.baluta@nxp.com>
//
// Hardware पूर्णांकerface क्रम audio DSP on i.MX8M

#समावेश <linux/firmware.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <linux/module.h>
#समावेश <sound/sof.h>
#समावेश <sound/sof/xtensa.h>
#समावेश <linux/firmware/imx/dsp.h>

#समावेश "../ops.h"
#समावेश "imx-common.h"

#घोषणा MBOX_OFFSET	0x800000
#घोषणा MBOX_SIZE	0x1000

काष्ठा imx8m_priv अणु
	काष्ठा device *dev;
	काष्ठा snd_sof_dev *sdev;

	/* DSP IPC handler */
	काष्ठा imx_dsp_ipc *dsp_ipc;
	काष्ठा platक्रमm_device *ipc_dev;
पूर्ण;

अटल व्योम imx8m_get_reply(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_ipc_msg *msg = sdev->msg;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक ret = 0;

	अगर (!msg) अणु
		dev_warn(sdev->dev, "unexpected ipc interrupt\n");
		वापस;
	पूर्ण

	/* get reply */
	sof_mailbox_पढ़ो(sdev, sdev->host_box.offset, &reply, माप(reply));

	अगर (reply.error < 0) अणु
		स_नकल(msg->reply_data, &reply, माप(reply));
		ret = reply.error;
	पूर्ण अन्यथा अणु
		/* reply has correct size? */
		अगर (reply.hdr.size != msg->reply_size) अणु
			dev_err(sdev->dev, "error: reply expected %zu got %u bytes\n",
				msg->reply_size, reply.hdr.size);
			ret = -EINVAL;
		पूर्ण

		/* पढ़ो the message */
		अगर (msg->reply_size > 0)
			sof_mailbox_पढ़ो(sdev, sdev->host_box.offset,
					 msg->reply_data, msg->reply_size);
	पूर्ण

	msg->reply_error = ret;
पूर्ण

अटल पूर्णांक imx8m_get_mailbox_offset(काष्ठा snd_sof_dev *sdev)
अणु
	वापस MBOX_OFFSET;
पूर्ण

अटल पूर्णांक imx8m_get_winकरोw_offset(काष्ठा snd_sof_dev *sdev, u32 id)
अणु
	वापस MBOX_OFFSET;
पूर्ण

अटल व्योम imx8m_dsp_handle_reply(काष्ठा imx_dsp_ipc *ipc)
अणु
	काष्ठा imx8m_priv *priv = imx_dsp_get_data(ipc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->sdev->ipc_lock, flags);
	imx8m_get_reply(priv->sdev);
	snd_sof_ipc_reply(priv->sdev, 0);
	spin_unlock_irqrestore(&priv->sdev->ipc_lock, flags);
पूर्ण

अटल व्योम imx8m_dsp_handle_request(काष्ठा imx_dsp_ipc *ipc)
अणु
	काष्ठा imx8m_priv *priv = imx_dsp_get_data(ipc);
	u32 p; /* Panic code */

	/* Read the message from the debug box. */
	sof_mailbox_पढ़ो(priv->sdev, priv->sdev->debug_box.offset + 4, &p, माप(p));

	/* Check to see अगर the message is a panic code (0x0dead***) */
	अगर ((p & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC)
		snd_sof_dsp_panic(priv->sdev, p);
	अन्यथा
		snd_sof_ipc_msgs_rx(priv->sdev);
पूर्ण

अटल काष्ठा imx_dsp_ops imx8m_dsp_ops = अणु
	.handle_reply		= imx8m_dsp_handle_reply,
	.handle_request		= imx8m_dsp_handle_request,
पूर्ण;

अटल पूर्णांक imx8m_send_msg(काष्ठा snd_sof_dev *sdev, काष्ठा snd_sof_ipc_msg *msg)
अणु
	काष्ठा imx8m_priv *priv = sdev->pdata->hw_pdata;

	sof_mailbox_ग_लिखो(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	imx_dsp_ring_करोorbell(priv->dsp_ipc, 0);

	वापस 0;
पूर्ण

/*
 * DSP control.
 */
अटल पूर्णांक imx8m_run(काष्ठा snd_sof_dev *sdev)
अणु
	/* TODO: start DSP using Audio MIX bits */
	वापस 0;
पूर्ण

अटल पूर्णांक imx8m_probe(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा platक्रमm_device *pdev =
		container_of(sdev->dev, काष्ठा platक्रमm_device, dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *res_node;
	काष्ठा resource *mmio;
	काष्ठा imx8m_priv *priv;
	काष्ठा resource res;
	u32 base, size;
	पूर्णांक ret = 0;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	sdev->pdata->hw_pdata = priv;
	priv->dev = sdev->dev;
	priv->sdev = sdev;

	priv->ipc_dev = platक्रमm_device_रेजिस्टर_data(sdev->dev, "imx-dsp",
						      PLATFORM_DEVID_NONE,
						      pdev, माप(*pdev));
	अगर (IS_ERR(priv->ipc_dev))
		वापस PTR_ERR(priv->ipc_dev);

	priv->dsp_ipc = dev_get_drvdata(&priv->ipc_dev->dev);
	अगर (!priv->dsp_ipc) अणु
		/* DSP IPC driver not probed yet, try later */
		ret = -EPROBE_DEFER;
		dev_err(sdev->dev, "Failed to get drvdata\n");
		जाओ निकास_pdev_unरेजिस्टर;
	पूर्ण

	imx_dsp_set_data(priv->dsp_ipc, priv);
	priv->dsp_ipc->ops = &imx8m_dsp_ops;

	/* DSP base */
	mmio = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (mmio) अणु
		base = mmio->start;
		size = resource_size(mmio);
	पूर्ण अन्यथा अणु
		dev_err(sdev->dev, "error: failed to get DSP base at idx 0\n");
		ret = -EINVAL;
		जाओ निकास_pdev_unरेजिस्टर;
	पूर्ण

	sdev->bar[SOF_FW_BLK_TYPE_IRAM] = devm_ioremap(sdev->dev, base, size);
	अगर (!sdev->bar[SOF_FW_BLK_TYPE_IRAM]) अणु
		dev_err(sdev->dev, "failed to ioremap base 0x%x size 0x%x\n",
			base, size);
		ret = -ENODEV;
		जाओ निकास_pdev_unरेजिस्टर;
	पूर्ण
	sdev->mmio_bar = SOF_FW_BLK_TYPE_IRAM;

	res_node = of_parse_phandle(np, "memory-region", 0);
	अगर (!res_node) अणु
		dev_err(&pdev->dev, "failed to get memory region node\n");
		ret = -ENODEV;
		जाओ निकास_pdev_unरेजिस्टर;
	पूर्ण

	ret = of_address_to_resource(res_node, 0, &res);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get reserved region address\n");
		जाओ निकास_pdev_unरेजिस्टर;
	पूर्ण

	sdev->bar[SOF_FW_BLK_TYPE_SRAM] = devm_ioremap_wc(sdev->dev, res.start,
							  resource_size(&res));
	अगर (!sdev->bar[SOF_FW_BLK_TYPE_SRAM]) अणु
		dev_err(sdev->dev, "failed to ioremap mem 0x%x size 0x%x\n",
			base, size);
		ret = -ENOMEM;
		जाओ निकास_pdev_unरेजिस्टर;
	पूर्ण
	sdev->mailbox_bar = SOF_FW_BLK_TYPE_SRAM;

	/* set शेष mailbox offset क्रम FW पढ़ोy message */
	sdev->dsp_box.offset = MBOX_OFFSET;

	वापस 0;

निकास_pdev_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(priv->ipc_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक imx8m_हटाओ(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा imx8m_priv *priv = sdev->pdata->hw_pdata;

	platक्रमm_device_unरेजिस्टर(priv->ipc_dev);

	वापस 0;
पूर्ण

/* on i.MX8 there is 1 to 1 match between type and BAR idx */
अटल पूर्णांक imx8m_get_bar_index(काष्ठा snd_sof_dev *sdev, u32 type)
अणु
	वापस type;
पूर्ण

अटल व्योम imx8m_ipc_msg_data(काष्ठा snd_sof_dev *sdev,
			       काष्ठा snd_pcm_substream *substream,
			       व्योम *p, माप_प्रकार sz)
अणु
	sof_mailbox_पढ़ो(sdev, sdev->dsp_box.offset, p, sz);
पूर्ण

अटल पूर्णांक imx8m_ipc_pcm_params(काष्ठा snd_sof_dev *sdev,
				काष्ठा snd_pcm_substream *substream,
				स्थिर काष्ठा sof_ipc_pcm_params_reply *reply)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver imx8m_dai[] = अणु
अणु
	.name = "sai3",
	.playback = अणु
		.channels_min = 1,
		.channels_max = 32,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 32,
	पूर्ण,
पूर्ण,
पूर्ण;

/* i.MX8 ops */
काष्ठा snd_sof_dsp_ops sof_imx8m_ops = अणु
	/* probe and हटाओ */
	.probe		= imx8m_probe,
	.हटाओ		= imx8m_हटाओ,
	/* DSP core boot */
	.run		= imx8m_run,

	/* Block IO */
	.block_पढ़ो	= sof_block_पढ़ो,
	.block_ग_लिखो	= sof_block_ग_लिखो,

	/* Module IO */
	.पढ़ो64	= sof_io_पढ़ो64,

	/* ipc */
	.send_msg	= imx8m_send_msg,
	.fw_पढ़ोy	= sof_fw_पढ़ोy,
	.get_mailbox_offset	= imx8m_get_mailbox_offset,
	.get_winकरोw_offset	= imx8m_get_winकरोw_offset,

	.ipc_msg_data	= imx8m_ipc_msg_data,
	.ipc_pcm_params	= imx8m_ipc_pcm_params,

	/* module loading */
	.load_module	= snd_sof_parse_module_स_नकल,
	.get_bar_index	= imx8m_get_bar_index,
	/* firmware loading */
	.load_firmware	= snd_sof_load_firmware_स_नकल,

	/* Debug inक्रमmation */
	.dbg_dump = imx8_dump,

	/* Firmware ops */
	.arch_ops = &sof_xtensa_arch_ops,

	/* DAI drivers */
	.drv = imx8m_dai,
	.num_drv = ARRAY_SIZE(imx8m_dai),

	.hw_info = SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_NO_PERIOD_WAKEUP,
पूर्ण;
EXPORT_SYMBOL(sof_imx8m_ops);

MODULE_IMPORT_NS(SND_SOC_SOF_XTENSA);
MODULE_LICENSE("Dual BSD/GPL");
