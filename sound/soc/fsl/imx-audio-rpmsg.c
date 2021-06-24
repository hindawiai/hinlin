<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017-2020 NXP

#समावेश <linux/module.h>
#समावेश <linux/rpmsg.h>
#समावेश "imx-pcm-rpmsg.h"

/*
 * काष्ठा imx_audio_rpmsg: निजी data
 *
 * @rpmsg_pdev: poपूर्णांकer of platक्रमm device
 */
काष्ठा imx_audio_rpmsg अणु
	काष्ठा platक्रमm_device *rpmsg_pdev;
पूर्ण;

अटल पूर्णांक imx_audio_rpmsg_cb(काष्ठा rpmsg_device *rpdev, व्योम *data, पूर्णांक len,
			      व्योम *priv, u32 src)
अणु
	काष्ठा imx_audio_rpmsg *rpmsg = dev_get_drvdata(&rpdev->dev);
	काष्ठा rpmsg_r_msg *r_msg = (काष्ठा rpmsg_r_msg *)data;
	काष्ठा rpmsg_info *info;
	काष्ठा rpmsg_msg *msg;
	अचिन्हित दीर्घ flags;

	अगर (!rpmsg->rpmsg_pdev)
		वापस 0;

	info = platक्रमm_get_drvdata(rpmsg->rpmsg_pdev);

	dev_dbg(&rpdev->dev, "get from%d: cmd:%d. %d\n",
		src, r_msg->header.cmd, r_msg->param.resp);

	चयन (r_msg->header.type) अणु
	हाल MSG_TYPE_C:
		/* TYPE C is notअगरication from M core */
		चयन (r_msg->header.cmd) अणु
		हाल TX_PERIOD_DONE:
			spin_lock_irqsave(&info->lock[TX], flags);
			msg = &info->msg[TX_PERIOD_DONE + MSG_TYPE_A_NUM];
			msg->r_msg.param.buffer_tail =
						r_msg->param.buffer_tail;
			msg->r_msg.param.buffer_tail %= info->num_period[TX];
			spin_unlock_irqrestore(&info->lock[TX], flags);
			info->callback[TX](info->callback_param[TX]);
			अवरोध;
		हाल RX_PERIOD_DONE:
			spin_lock_irqsave(&info->lock[RX], flags);
			msg = &info->msg[RX_PERIOD_DONE + MSG_TYPE_A_NUM];
			msg->r_msg.param.buffer_tail =
						r_msg->param.buffer_tail;
			msg->r_msg.param.buffer_tail %= info->num_period[1];
			spin_unlock_irqrestore(&info->lock[RX], flags);
			info->callback[RX](info->callback_param[RX]);
			अवरोध;
		शेष:
			dev_warn(&rpdev->dev, "unknown msg command\n");
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MSG_TYPE_B:
		/* TYPE B is response msg */
		स_नकल(&info->r_msg, r_msg, माप(काष्ठा rpmsg_r_msg));
		complete(&info->cmd_complete);
		अवरोध;
	शेष:
		dev_warn(&rpdev->dev, "unknown msg type\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx_audio_rpmsg_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा imx_audio_rpmsg *data;
	पूर्णांक ret = 0;

	dev_info(&rpdev->dev, "new channel: 0x%x -> 0x%x!\n",
		 rpdev->src, rpdev->dst);

	data = devm_kzalloc(&rpdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	dev_set_drvdata(&rpdev->dev, data);

	/* Register platक्रमm driver क्रम rpmsg routine */
	data->rpmsg_pdev = platक्रमm_device_रेजिस्टर_data(&rpdev->dev,
							 IMX_PCM_DRV_NAME,
							 PLATFORM_DEVID_NONE,
							 शून्य, 0);
	अगर (IS_ERR(data->rpmsg_pdev)) अणु
		dev_err(&rpdev->dev, "failed to register rpmsg platform.\n");
		ret = PTR_ERR(data->rpmsg_pdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम imx_audio_rpmsg_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा imx_audio_rpmsg *data = dev_get_drvdata(&rpdev->dev);

	अगर (data->rpmsg_pdev)
		platक्रमm_device_unरेजिस्टर(data->rpmsg_pdev);

	dev_info(&rpdev->dev, "audio rpmsg driver is removed\n");
पूर्ण

अटल काष्ठा rpmsg_device_id imx_audio_rpmsg_id_table[] = अणु
	अणु .name	= "rpmsg-audio-channel" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा rpmsg_driver imx_audio_rpmsg_driver = अणु
	.drv.name	= "imx_audio_rpmsg",
	.drv.owner	= THIS_MODULE,
	.id_table	= imx_audio_rpmsg_id_table,
	.probe		= imx_audio_rpmsg_probe,
	.callback	= imx_audio_rpmsg_cb,
	.हटाओ		= imx_audio_rpmsg_हटाओ,
पूर्ण;

अटल पूर्णांक __init imx_audio_rpmsg_init(व्योम)
अणु
	वापस रेजिस्टर_rpmsg_driver(&imx_audio_rpmsg_driver);
पूर्ण

अटल व्योम __निकास imx_audio_rpmsg_निकास(व्योम)
अणु
	unरेजिस्टर_rpmsg_driver(&imx_audio_rpmsg_driver);
पूर्ण
module_init(imx_audio_rpmsg_init);
module_निकास(imx_audio_rpmsg_निकास);

MODULE_DESCRIPTION("Freescale SoC Audio RPMSG interface");
MODULE_AUTHOR("Shengjiu Wang <shengjiu.wang@nxp.com>");
MODULE_ALIAS("platform:imx_audio_rpmsg");
MODULE_LICENSE("GPL v2");
