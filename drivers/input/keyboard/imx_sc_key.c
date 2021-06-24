<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#घोषणा DEBOUNCE_TIME				30
#घोषणा REPEAT_INTERVAL				60

#घोषणा SC_IRQ_BUTTON				1
#घोषणा SC_IRQ_GROUP_WAKE			3

#घोषणा IMX_SC_MISC_FUNC_GET_BUTTON_STATUS	18

काष्ठा imx_key_drv_data अणु
	u32 keycode;
	bool keystate;  /* true: pressed, false: released */
	काष्ठा delayed_work check_work;
	काष्ठा input_dev *input;
	काष्ठा imx_sc_ipc *key_ipc_handle;
	काष्ठा notअगरier_block key_notअगरier;
पूर्ण;

काष्ठा imx_sc_msg_key अणु
	काष्ठा imx_sc_rpc_msg hdr;
	u32 state;
पूर्ण;

अटल पूर्णांक imx_sc_key_notअगरy(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ event, व्योम *group)
अणु
	काष्ठा imx_key_drv_data *priv =
				 container_of(nb,
					      काष्ठा imx_key_drv_data,
					      key_notअगरier);

	अगर ((event & SC_IRQ_BUTTON) && (*(u8 *)group == SC_IRQ_GROUP_WAKE)) अणु
		schedule_delayed_work(&priv->check_work,
				      msecs_to_jअगरfies(DEBOUNCE_TIME));
		pm_wakeup_event(priv->input->dev.parent, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx_sc_check_क्रम_events(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा imx_key_drv_data *priv =
				 container_of(work,
					      काष्ठा imx_key_drv_data,
					      check_work.work);
	काष्ठा input_dev *input = priv->input;
	काष्ठा imx_sc_msg_key msg;
	काष्ठा imx_sc_rpc_msg *hdr = &msg.hdr;
	bool state;
	पूर्णांक error;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_MISC;
	hdr->func = IMX_SC_MISC_FUNC_GET_BUTTON_STATUS;
	hdr->size = 1;

	error = imx_scu_call_rpc(priv->key_ipc_handle, &msg, true);
	अगर (error) अणु
		dev_err(&input->dev, "read imx sc key failed, error %d\n", error);
		वापस;
	पूर्ण

	/*
	 * The response data from SCU firmware is 4 bytes,
	 * but ONLY the first byte is the key state, other
	 * 3 bytes could be some dirty data, so we should
	 * ONLY take the first byte as key state.
	 */
	state = (bool)(msg.state & 0xff);

	अगर (state ^ priv->keystate) अणु
		priv->keystate = state;
		input_event(input, EV_KEY, priv->keycode, state);
		input_sync(input);
		अगर (!priv->keystate)
			pm_relax(priv->input->dev.parent);
	पूर्ण

	अगर (state)
		schedule_delayed_work(&priv->check_work,
				      msecs_to_jअगरfies(REPEAT_INTERVAL));
पूर्ण

अटल व्योम imx_sc_key_action(व्योम *data)
अणु
	काष्ठा imx_key_drv_data *priv = data;

	imx_scu_irq_group_enable(SC_IRQ_GROUP_WAKE, SC_IRQ_BUTTON, false);
	imx_scu_irq_unरेजिस्टर_notअगरier(&priv->key_notअगरier);
	cancel_delayed_work_sync(&priv->check_work);
पूर्ण

अटल पूर्णांक imx_sc_key_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_key_drv_data *priv;
	काष्ठा input_dev *input;
	पूर्णांक error;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	error = imx_scu_get_handle(&priv->key_ipc_handle);
	अगर (error)
		वापस error;

	अगर (device_property_पढ़ो_u32(&pdev->dev, "linux,keycodes",
				     &priv->keycode)) अणु
		dev_err(&pdev->dev, "missing linux,keycodes property\n");
		वापस -EINVAL;
	पूर्ण

	INIT_DELAYED_WORK(&priv->check_work, imx_sc_check_क्रम_events);

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input) अणु
		dev_err(&pdev->dev, "failed to allocate the input device\n");
		वापस -ENOMEM;
	पूर्ण

	input->name = pdev->name;
	input->phys = "imx-sc-key/input0";
	input->id.bustype = BUS_HOST;

	input_set_capability(input, EV_KEY, priv->keycode);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	priv->input = input;
	platक्रमm_set_drvdata(pdev, priv);

	error = imx_scu_irq_group_enable(SC_IRQ_GROUP_WAKE, SC_IRQ_BUTTON,
					 true);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to enable scu group irq\n");
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&pdev->dev, imx_sc_key_action, &priv);
	अगर (error)
		वापस error;

	priv->key_notअगरier.notअगरier_call = imx_sc_key_notअगरy;
	error = imx_scu_irq_रेजिस्टर_notअगरier(&priv->key_notअगरier);
	अगर (error)
		dev_err(&pdev->dev, "failed to register scu notifier\n");

	वापस error;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx_sc_key_ids[] = अणु
	अणु .compatible = "fsl,imx-sc-key" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_sc_key_ids);

अटल काष्ठा platक्रमm_driver imx_sc_key_driver = अणु
	.driver = अणु
		.name = "imx-sc-key",
		.of_match_table = imx_sc_key_ids,
	पूर्ण,
	.probe = imx_sc_key_probe,
पूर्ण;
module_platक्रमm_driver(imx_sc_key_driver);

MODULE_AUTHOR("Anson Huang <Anson.Huang@nxp.com>");
MODULE_DESCRIPTION("i.MX System Controller Key Driver");
MODULE_LICENSE("GPL v2");
