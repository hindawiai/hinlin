<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// Copyright 2019 NXP
//
// Author: Daniel Baluta <daniel.baluta@nxp.com>
//
// Hardware पूर्णांकerface क्रम audio DSP on i.MX8

#समावेश <linux/firmware.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm_करोमुख्य.h>

#समावेश <linux/module.h>
#समावेश <sound/sof.h>
#समावेश <sound/sof/xtensa.h>
#समावेश <linux/firmware/imx/ipc.h>
#समावेश <linux/firmware/imx/dsp.h>

#समावेश <linux/firmware/imx/svc/misc.h>
#समावेश <dt-bindings/firmware/imx/rsrc.h>
#समावेश "../ops.h"
#समावेश "imx-common.h"

/* DSP memories */
#घोषणा IRAM_OFFSET		0x10000
#घोषणा IRAM_SIZE		(2 * 1024)
#घोषणा DRAM0_OFFSET		0x0
#घोषणा DRAM0_SIZE		(32 * 1024)
#घोषणा DRAM1_OFFSET		0x8000
#घोषणा DRAM1_SIZE		(32 * 1024)
#घोषणा SYSRAM_OFFSET		0x18000
#घोषणा SYSRAM_SIZE		(256 * 1024)
#घोषणा SYSROM_OFFSET		0x58000
#घोषणा SYSROM_SIZE		(192 * 1024)

#घोषणा RESET_VECTOR_VADDR	0x596f8000

#घोषणा MBOX_OFFSET	0x800000
#घोषणा MBOX_SIZE	0x1000

काष्ठा imx8_priv अणु
	काष्ठा device *dev;
	काष्ठा snd_sof_dev *sdev;

	/* DSP IPC handler */
	काष्ठा imx_dsp_ipc *dsp_ipc;
	काष्ठा platक्रमm_device *ipc_dev;

	/* System Controller IPC handler */
	काष्ठा imx_sc_ipc *sc_ipc;

	/* Power करोमुख्य handling */
	पूर्णांक num_करोमुख्यs;
	काष्ठा device **pd_dev;
	काष्ठा device_link **link;

पूर्ण;

अटल व्योम imx8_get_reply(काष्ठा snd_sof_dev *sdev)
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

अटल पूर्णांक imx8_get_mailbox_offset(काष्ठा snd_sof_dev *sdev)
अणु
	वापस MBOX_OFFSET;
पूर्ण

अटल पूर्णांक imx8_get_winकरोw_offset(काष्ठा snd_sof_dev *sdev, u32 id)
अणु
	वापस MBOX_OFFSET;
पूर्ण

अटल व्योम imx8_dsp_handle_reply(काष्ठा imx_dsp_ipc *ipc)
अणु
	काष्ठा imx8_priv *priv = imx_dsp_get_data(ipc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->sdev->ipc_lock, flags);
	imx8_get_reply(priv->sdev);
	snd_sof_ipc_reply(priv->sdev, 0);
	spin_unlock_irqrestore(&priv->sdev->ipc_lock, flags);
पूर्ण

अटल व्योम imx8_dsp_handle_request(काष्ठा imx_dsp_ipc *ipc)
अणु
	काष्ठा imx8_priv *priv = imx_dsp_get_data(ipc);
	u32 p; /* panic code */

	/* Read the message from the debug box. */
	sof_mailbox_पढ़ो(priv->sdev, priv->sdev->debug_box.offset + 4, &p, माप(p));

	/* Check to see अगर the message is a panic code (0x0dead***) */
	अगर ((p & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC)
		snd_sof_dsp_panic(priv->sdev, p);
	अन्यथा
		snd_sof_ipc_msgs_rx(priv->sdev);
पूर्ण

अटल काष्ठा imx_dsp_ops dsp_ops = अणु
	.handle_reply		= imx8_dsp_handle_reply,
	.handle_request		= imx8_dsp_handle_request,
पूर्ण;

अटल पूर्णांक imx8_send_msg(काष्ठा snd_sof_dev *sdev, काष्ठा snd_sof_ipc_msg *msg)
अणु
	काष्ठा imx8_priv *priv = sdev->pdata->hw_pdata;

	sof_mailbox_ग_लिखो(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	imx_dsp_ring_करोorbell(priv->dsp_ipc, 0);

	वापस 0;
पूर्ण

/*
 * DSP control.
 */
अटल पूर्णांक imx8x_run(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा imx8_priv *dsp_priv = sdev->pdata->hw_pdata;
	पूर्णांक ret;

	ret = imx_sc_misc_set_control(dsp_priv->sc_ipc, IMX_SC_R_DSP,
				      IMX_SC_C_OFS_SEL, 1);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "Error system address offset source select\n");
		वापस ret;
	पूर्ण

	ret = imx_sc_misc_set_control(dsp_priv->sc_ipc, IMX_SC_R_DSP,
				      IMX_SC_C_OFS_AUDIO, 0x80);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "Error system address offset of AUDIO\n");
		वापस ret;
	पूर्ण

	ret = imx_sc_misc_set_control(dsp_priv->sc_ipc, IMX_SC_R_DSP,
				      IMX_SC_C_OFS_PERIPH, 0x5A);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "Error system address offset of PERIPH %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = imx_sc_misc_set_control(dsp_priv->sc_ipc, IMX_SC_R_DSP,
				      IMX_SC_C_OFS_IRQ, 0x51);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "Error system address offset of IRQ\n");
		वापस ret;
	पूर्ण

	imx_sc_pm_cpu_start(dsp_priv->sc_ipc, IMX_SC_R_DSP, true,
			    RESET_VECTOR_VADDR);

	वापस 0;
पूर्ण

अटल पूर्णांक imx8_run(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा imx8_priv *dsp_priv = sdev->pdata->hw_pdata;
	पूर्णांक ret;

	ret = imx_sc_misc_set_control(dsp_priv->sc_ipc, IMX_SC_R_DSP,
				      IMX_SC_C_OFS_SEL, 0);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "Error system address offset source select\n");
		वापस ret;
	पूर्ण

	imx_sc_pm_cpu_start(dsp_priv->sc_ipc, IMX_SC_R_DSP, true,
			    RESET_VECTOR_VADDR);

	वापस 0;
पूर्ण

अटल पूर्णांक imx8_probe(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा platक्रमm_device *pdev =
		container_of(sdev->dev, काष्ठा platक्रमm_device, dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *res_node;
	काष्ठा resource *mmio;
	काष्ठा imx8_priv *priv;
	काष्ठा resource res;
	u32 base, size;
	पूर्णांक ret = 0;
	पूर्णांक i;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	sdev->pdata->hw_pdata = priv;
	priv->dev = sdev->dev;
	priv->sdev = sdev;

	/* घातer up device associated घातer करोमुख्यs */
	priv->num_करोमुख्यs = of_count_phandle_with_args(np, "power-domains",
						       "#power-domain-cells");
	अगर (priv->num_करोमुख्यs < 0) अणु
		dev_err(sdev->dev, "no power-domains property in %pOF\n", np);
		वापस priv->num_करोमुख्यs;
	पूर्ण

	priv->pd_dev = devm_kदो_स्मृति_array(&pdev->dev, priv->num_करोमुख्यs,
					  माप(*priv->pd_dev), GFP_KERNEL);
	अगर (!priv->pd_dev)
		वापस -ENOMEM;

	priv->link = devm_kदो_स्मृति_array(&pdev->dev, priv->num_करोमुख्यs,
					माप(*priv->link), GFP_KERNEL);
	अगर (!priv->link)
		वापस -ENOMEM;

	क्रम (i = 0; i < priv->num_करोमुख्यs; i++) अणु
		priv->pd_dev[i] = dev_pm_करोमुख्य_attach_by_id(&pdev->dev, i);
		अगर (IS_ERR(priv->pd_dev[i])) अणु
			ret = PTR_ERR(priv->pd_dev[i]);
			जाओ निकास_unroll_pm;
		पूर्ण
		priv->link[i] = device_link_add(&pdev->dev, priv->pd_dev[i],
						DL_FLAG_STATELESS |
						DL_FLAG_PM_RUNTIME |
						DL_FLAG_RPM_ACTIVE);
		अगर (!priv->link[i]) अणु
			ret = -ENOMEM;
			dev_pm_करोमुख्य_detach(priv->pd_dev[i], false);
			जाओ निकास_unroll_pm;
		पूर्ण
	पूर्ण

	ret = imx_scu_get_handle(&priv->sc_ipc);
	अगर (ret) अणु
		dev_err(sdev->dev, "Cannot obtain SCU handle (err = %d)\n",
			ret);
		जाओ निकास_unroll_pm;
	पूर्ण

	priv->ipc_dev = platक्रमm_device_रेजिस्टर_data(sdev->dev, "imx-dsp",
						      PLATFORM_DEVID_NONE,
						      pdev, माप(*pdev));
	अगर (IS_ERR(priv->ipc_dev)) अणु
		ret = PTR_ERR(priv->ipc_dev);
		जाओ निकास_unroll_pm;
	पूर्ण

	priv->dsp_ipc = dev_get_drvdata(&priv->ipc_dev->dev);
	अगर (!priv->dsp_ipc) अणु
		/* DSP IPC driver not probed yet, try later */
		ret = -EPROBE_DEFER;
		dev_err(sdev->dev, "Failed to get drvdata\n");
		जाओ निकास_pdev_unरेजिस्टर;
	पूर्ण

	imx_dsp_set_data(priv->dsp_ipc, priv);
	priv->dsp_ipc->ops = &dsp_ops;

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
निकास_unroll_pm:
	जबतक (--i >= 0) अणु
		device_link_del(priv->link[i]);
		dev_pm_करोमुख्य_detach(priv->pd_dev[i], false);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक imx8_हटाओ(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा imx8_priv *priv = sdev->pdata->hw_pdata;
	पूर्णांक i;

	platक्रमm_device_unरेजिस्टर(priv->ipc_dev);

	क्रम (i = 0; i < priv->num_करोमुख्यs; i++) अणु
		device_link_del(priv->link[i]);
		dev_pm_करोमुख्य_detach(priv->pd_dev[i], false);
	पूर्ण

	वापस 0;
पूर्ण

/* on i.MX8 there is 1 to 1 match between type and BAR idx */
अटल पूर्णांक imx8_get_bar_index(काष्ठा snd_sof_dev *sdev, u32 type)
अणु
	वापस type;
पूर्ण

अटल व्योम imx8_ipc_msg_data(काष्ठा snd_sof_dev *sdev,
			      काष्ठा snd_pcm_substream *substream,
			      व्योम *p, माप_प्रकार sz)
अणु
	sof_mailbox_पढ़ो(sdev, sdev->dsp_box.offset, p, sz);
पूर्ण

अटल पूर्णांक imx8_ipc_pcm_params(काष्ठा snd_sof_dev *sdev,
			       काष्ठा snd_pcm_substream *substream,
			       स्थिर काष्ठा sof_ipc_pcm_params_reply *reply)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver imx8_dai[] = अणु
अणु
	.name = "esai0",
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "sai1",
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
काष्ठा snd_sof_dsp_ops sof_imx8_ops = अणु
	/* probe and हटाओ */
	.probe		= imx8_probe,
	.हटाओ		= imx8_हटाओ,
	/* DSP core boot */
	.run		= imx8_run,

	/* Block IO */
	.block_पढ़ो	= sof_block_पढ़ो,
	.block_ग_लिखो	= sof_block_ग_लिखो,

	/* Module IO */
	.पढ़ो64	= sof_io_पढ़ो64,

	/* ipc */
	.send_msg	= imx8_send_msg,
	.fw_पढ़ोy	= sof_fw_पढ़ोy,
	.get_mailbox_offset	= imx8_get_mailbox_offset,
	.get_winकरोw_offset	= imx8_get_winकरोw_offset,

	.ipc_msg_data	= imx8_ipc_msg_data,
	.ipc_pcm_params	= imx8_ipc_pcm_params,

	/* module loading */
	.load_module	= snd_sof_parse_module_स_नकल,
	.get_bar_index	= imx8_get_bar_index,
	/* firmware loading */
	.load_firmware	= snd_sof_load_firmware_स_नकल,

	/* Debug inक्रमmation */
	.dbg_dump = imx8_dump,

	/* Firmware ops */
	.arch_ops = &sof_xtensa_arch_ops,

	/* DAI drivers */
	.drv = imx8_dai,
	.num_drv = ARRAY_SIZE(imx8_dai),

	/* ALSA HW info flags */
	.hw_info =	SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_PAUSE |
			SNDRV_PCM_INFO_NO_PERIOD_WAKEUP,
पूर्ण;
EXPORT_SYMBOL(sof_imx8_ops);

/* i.MX8X ops */
काष्ठा snd_sof_dsp_ops sof_imx8x_ops = अणु
	/* probe and हटाओ */
	.probe		= imx8_probe,
	.हटाओ		= imx8_हटाओ,
	/* DSP core boot */
	.run		= imx8x_run,

	/* Block IO */
	.block_पढ़ो	= sof_block_पढ़ो,
	.block_ग_लिखो	= sof_block_ग_लिखो,

	/* Module IO */
	.पढ़ो64	= sof_io_पढ़ो64,

	/* ipc */
	.send_msg	= imx8_send_msg,
	.fw_पढ़ोy	= sof_fw_पढ़ोy,
	.get_mailbox_offset	= imx8_get_mailbox_offset,
	.get_winकरोw_offset	= imx8_get_winकरोw_offset,

	.ipc_msg_data	= imx8_ipc_msg_data,
	.ipc_pcm_params	= imx8_ipc_pcm_params,

	/* module loading */
	.load_module	= snd_sof_parse_module_स_नकल,
	.get_bar_index	= imx8_get_bar_index,
	/* firmware loading */
	.load_firmware	= snd_sof_load_firmware_स_नकल,

	/* Debug inक्रमmation */
	.dbg_dump = imx8_dump,

	/* Firmware ops */
	.arch_ops = &sof_xtensa_arch_ops,

	/* DAI drivers */
	.drv = imx8_dai,
	.num_drv = ARRAY_SIZE(imx8_dai),

	/* ALSA HW info flags */
	.hw_info =	SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_PAUSE |
			SNDRV_PCM_INFO_NO_PERIOD_WAKEUP
पूर्ण;
EXPORT_SYMBOL(sof_imx8x_ops);

MODULE_IMPORT_NS(SND_SOC_SOF_XTENSA);
MODULE_LICENSE("Dual BSD/GPL");
