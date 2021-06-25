<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Manager Driver क्रम Intel Stratix10 SoC
 *
 *  Copyright (C) 2018 Intel Corporation
 */
#समावेश <linux/completion.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/firmware/पूर्णांकel/stratix10-svc-client.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>

/*
 * FPGA programming requires a higher level of privilege (EL3), per the SoC
 * design.
 */
#घोषणा NUM_SVC_BUFS	4
#घोषणा SVC_BUF_SIZE	SZ_512K

/* Indicates buffer is in use अगर set */
#घोषणा SVC_BUF_LOCK	0

#घोषणा S10_BUFFER_TIMEOUT (msecs_to_jअगरfies(SVC_RECONFIG_BUFFER_TIMEOUT_MS))
#घोषणा S10_RECONFIG_TIMEOUT (msecs_to_jअगरfies(SVC_RECONFIG_REQUEST_TIMEOUT_MS))

/*
 * काष्ठा s10_svc_buf
 * buf:  भव address of buf provided by service layer
 * lock: locked अगर buffer is in use
 */
काष्ठा s10_svc_buf अणु
	अक्षर *buf;
	अचिन्हित दीर्घ lock;
पूर्ण;

काष्ठा s10_priv अणु
	काष्ठा stratix10_svc_chan *chan;
	काष्ठा stratix10_svc_client client;
	काष्ठा completion status_वापस_completion;
	काष्ठा s10_svc_buf svc_bufs[NUM_SVC_BUFS];
	अचिन्हित दीर्घ status;
पूर्ण;

अटल पूर्णांक s10_svc_send_msg(काष्ठा s10_priv *priv,
			    क्रमागत stratix10_svc_command_code command,
			    व्योम *payload, u32 payload_length)
अणु
	काष्ठा stratix10_svc_chan *chan = priv->chan;
	काष्ठा device *dev = priv->client.dev;
	काष्ठा stratix10_svc_client_msg msg;
	पूर्णांक ret;

	dev_dbg(dev, "%s cmd=%d payload=%p length=%d\n",
		__func__, command, payload, payload_length);

	msg.command = command;
	msg.payload = payload;
	msg.payload_length = payload_length;

	ret = stratix10_svc_send(chan, &msg);
	dev_dbg(dev, "stratix10_svc_send returned status %d\n", ret);

	वापस ret;
पूर्ण

/*
 * Free buffers allocated from the service layer's pool that are not in use.
 * Return true when all buffers are मुक्तd.
 */
अटल bool s10_मुक्त_buffers(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा s10_priv *priv = mgr->priv;
	uपूर्णांक num_मुक्त = 0;
	uपूर्णांक i;

	क्रम (i = 0; i < NUM_SVC_BUFS; i++) अणु
		अगर (!priv->svc_bufs[i].buf) अणु
			num_मुक्त++;
			जारी;
		पूर्ण

		अगर (!test_and_set_bit_lock(SVC_BUF_LOCK,
					   &priv->svc_bufs[i].lock)) अणु
			stratix10_svc_मुक्त_memory(priv->chan,
						  priv->svc_bufs[i].buf);
			priv->svc_bufs[i].buf = शून्य;
			num_मुक्त++;
		पूर्ण
	पूर्ण

	वापस num_मुक्त == NUM_SVC_BUFS;
पूर्ण

/*
 * Returns count of how many buffers are not in use.
 */
अटल uपूर्णांक s10_मुक्त_buffer_count(काष्ठा fpga_manager *mgr)
अणु
	काष्ठा s10_priv *priv = mgr->priv;
	uपूर्णांक num_मुक्त = 0;
	uपूर्णांक i;

	क्रम (i = 0; i < NUM_SVC_BUFS; i++)
		अगर (!priv->svc_bufs[i].buf)
			num_मुक्त++;

	वापस num_मुक्त;
पूर्ण

/*
 * s10_unlock_bufs
 * Given the वापसed buffer address, match that address to our buffer काष्ठा
 * and unlock that buffer.  This marks it as available to be refilled and sent
 * (or मुक्तd).
 * priv: निजी data
 * kaddr: kernel address of buffer that was वापसed from service layer
 */
अटल व्योम s10_unlock_bufs(काष्ठा s10_priv *priv, व्योम *kaddr)
अणु
	uपूर्णांक i;

	अगर (!kaddr)
		वापस;

	क्रम (i = 0; i < NUM_SVC_BUFS; i++)
		अगर (priv->svc_bufs[i].buf == kaddr) अणु
			clear_bit_unlock(SVC_BUF_LOCK,
					 &priv->svc_bufs[i].lock);
			वापस;
		पूर्ण

	WARN(1, "Unknown buffer returned from service layer %p\n", kaddr);
पूर्ण

/*
 * s10_receive_callback - callback क्रम service layer to use to provide client
 * (this driver) messages received through the mailbox.
 * client: service layer client काष्ठा
 * data: message from service layer
 */
अटल व्योम s10_receive_callback(काष्ठा stratix10_svc_client *client,
				 काष्ठा stratix10_svc_cb_data *data)
अणु
	काष्ठा s10_priv *priv = client->priv;
	u32 status;
	पूर्णांक i;

	WARN_ONCE(!data, "%s: stratix10_svc_rc_data = NULL", __func__);

	status = data->status;

	/*
	 * Here we set status bits as we receive them.  Elsewhere, we always use
	 * test_and_clear_bit() to check status in priv->status
	 */
	क्रम (i = 0; i <= SVC_STATUS_ERROR; i++)
		अगर (status & (1 << i))
			set_bit(i, &priv->status);

	अगर (status & BIT(SVC_STATUS_BUFFER_DONE)) अणु
		s10_unlock_bufs(priv, data->kaddr1);
		s10_unlock_bufs(priv, data->kaddr2);
		s10_unlock_bufs(priv, data->kaddr3);
	पूर्ण

	complete(&priv->status_वापस_completion);
पूर्ण

/*
 * s10_ops_ग_लिखो_init - prepare क्रम FPGA reconfiguration by requesting
 * partial reconfig and allocating buffers from the service layer.
 */
अटल पूर्णांक s10_ops_ग_लिखो_init(काष्ठा fpga_manager *mgr,
			      काष्ठा fpga_image_info *info,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा s10_priv *priv = mgr->priv;
	काष्ठा device *dev = priv->client.dev;
	काष्ठा stratix10_svc_command_config_type ctype;
	अक्षर *kbuf;
	uपूर्णांक i;
	पूर्णांक ret;

	ctype.flags = 0;
	अगर (info->flags & FPGA_MGR_PARTIAL_RECONFIG) अणु
		dev_dbg(dev, "Requesting partial reconfiguration.\n");
		ctype.flags |= BIT(COMMAND_RECONFIG_FLAG_PARTIAL);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "Requesting full reconfiguration.\n");
	पूर्ण

	reinit_completion(&priv->status_वापस_completion);
	ret = s10_svc_send_msg(priv, COMMAND_RECONFIG,
			       &ctype, माप(ctype));
	अगर (ret < 0)
		जाओ init_करोne;

	ret = रुको_क्रम_completion_समयout(
		&priv->status_वापस_completion, S10_RECONFIG_TIMEOUT);
	अगर (!ret) अणु
		dev_err(dev, "timeout waiting for RECONFIG_REQUEST\n");
		ret = -ETIMEDOUT;
		जाओ init_करोne;
	पूर्ण

	ret = 0;
	अगर (!test_and_clear_bit(SVC_STATUS_OK, &priv->status)) अणु
		ret = -ETIMEDOUT;
		जाओ init_करोne;
	पूर्ण

	/* Allocate buffers from the service layer's pool. */
	क्रम (i = 0; i < NUM_SVC_BUFS; i++) अणु
		kbuf = stratix10_svc_allocate_memory(priv->chan, SVC_BUF_SIZE);
		अगर (!kbuf) अणु
			s10_मुक्त_buffers(mgr);
			ret = -ENOMEM;
			जाओ init_करोne;
		पूर्ण

		priv->svc_bufs[i].buf = kbuf;
		priv->svc_bufs[i].lock = 0;
	पूर्ण

init_करोne:
	stratix10_svc_करोne(priv->chan);
	वापस ret;
पूर्ण

/*
 * s10_send_buf - send a buffer to the service layer queue
 * mgr: fpga manager काष्ठा
 * buf: fpga image buffer
 * count: size of buf in bytes
 * Returns # of bytes transferred or -ENOBUFS अगर the all the buffers are in use
 * or अगर the service queue is full. Never वापसs 0.
 */
अटल पूर्णांक s10_send_buf(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा s10_priv *priv = mgr->priv;
	काष्ठा device *dev = priv->client.dev;
	व्योम *svc_buf;
	माप_प्रकार xfer_sz;
	पूर्णांक ret;
	uपूर्णांक i;

	/* get/lock a buffer that that's not being used */
	क्रम (i = 0; i < NUM_SVC_BUFS; i++)
		अगर (!test_and_set_bit_lock(SVC_BUF_LOCK,
					   &priv->svc_bufs[i].lock))
			अवरोध;

	अगर (i == NUM_SVC_BUFS)
		वापस -ENOBUFS;

	xfer_sz = count < SVC_BUF_SIZE ? count : SVC_BUF_SIZE;

	svc_buf = priv->svc_bufs[i].buf;
	स_नकल(svc_buf, buf, xfer_sz);
	ret = s10_svc_send_msg(priv, COMMAND_RECONFIG_DATA_SUBMIT,
			       svc_buf, xfer_sz);
	अगर (ret < 0) अणु
		dev_err(dev,
			"Error while sending data to service layer (%d)", ret);
		clear_bit_unlock(SVC_BUF_LOCK, &priv->svc_bufs[i].lock);
		वापस ret;
	पूर्ण

	वापस xfer_sz;
पूर्ण

/*
 * Send a FPGA image to privileged layers to ग_लिखो to the FPGA.  When करोne
 * sending, मुक्त all service layer buffers we allocated in ग_लिखो_init.
 */
अटल पूर्णांक s10_ops_ग_लिखो(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf,
			 माप_प्रकार count)
अणु
	काष्ठा s10_priv *priv = mgr->priv;
	काष्ठा device *dev = priv->client.dev;
	दीर्घ रुको_status;
	पूर्णांक sent = 0;
	पूर्णांक ret = 0;

	/*
	 * Loop रुकोing क्रम buffers to be वापसed.  When a buffer is वापसed,
	 * reuse it to send more data or मुक्त अगर अगर all data has been sent.
	 */
	जबतक (count > 0 || s10_मुक्त_buffer_count(mgr) != NUM_SVC_BUFS) अणु
		reinit_completion(&priv->status_वापस_completion);

		अगर (count > 0) अणु
			sent = s10_send_buf(mgr, buf, count);
			अगर (sent < 0)
				जारी;

			count -= sent;
			buf += sent;
		पूर्ण अन्यथा अणु
			अगर (s10_मुक्त_buffers(mgr))
				वापस 0;

			ret = s10_svc_send_msg(
				priv, COMMAND_RECONFIG_DATA_CLAIM,
				शून्य, 0);
			अगर (ret < 0)
				अवरोध;
		पूर्ण

		/*
		 * If callback hasn't alपढ़ोy happened, रुको क्रम buffers to be
		 * वापसed from service layer
		 */
		रुको_status = 1; /* not समयd out */
		अगर (!priv->status)
			रुको_status = रुको_क्रम_completion_समयout(
				&priv->status_वापस_completion,
				S10_BUFFER_TIMEOUT);

		अगर (test_and_clear_bit(SVC_STATUS_BUFFER_DONE, &priv->status) ||
		    test_and_clear_bit(SVC_STATUS_BUFFER_SUBMITTED,
				       &priv->status)) अणु
			ret = 0;
			जारी;
		पूर्ण

		अगर (test_and_clear_bit(SVC_STATUS_ERROR, &priv->status)) अणु
			dev_err(dev, "ERROR - giving up - SVC_STATUS_ERROR\n");
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (!रुको_status) अणु
			dev_err(dev, "timeout waiting for svc layer buffers\n");
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!s10_मुक्त_buffers(mgr))
		dev_err(dev, "%s not all buffers were freed\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक s10_ops_ग_लिखो_complete(काष्ठा fpga_manager *mgr,
				  काष्ठा fpga_image_info *info)
अणु
	काष्ठा s10_priv *priv = mgr->priv;
	काष्ठा device *dev = priv->client.dev;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	समयout = usecs_to_jअगरfies(info->config_complete_समयout_us);

	करो अणु
		reinit_completion(&priv->status_वापस_completion);

		ret = s10_svc_send_msg(priv, COMMAND_RECONFIG_STATUS, शून्य, 0);
		अगर (ret < 0)
			अवरोध;

		ret = रुको_क्रम_completion_समयout(
			&priv->status_वापस_completion, समयout);
		अगर (!ret) अणु
			dev_err(dev,
				"timeout waiting for RECONFIG_COMPLETED\n");
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		/* Not error or समयout, so ret is # of jअगरfies until समयout */
		समयout = ret;
		ret = 0;

		अगर (test_and_clear_bit(SVC_STATUS_COMPLETED, &priv->status))
			अवरोध;

		अगर (test_and_clear_bit(SVC_STATUS_ERROR, &priv->status)) अणु
			dev_err(dev, "ERROR - giving up - SVC_STATUS_ERROR\n");
			ret = -EFAULT;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (1);

	stratix10_svc_करोne(priv->chan);

	वापस ret;
पूर्ण

अटल क्रमागत fpga_mgr_states s10_ops_state(काष्ठा fpga_manager *mgr)
अणु
	वापस FPGA_MGR_STATE_UNKNOWN;
पूर्ण

अटल स्थिर काष्ठा fpga_manager_ops s10_ops = अणु
	.state = s10_ops_state,
	.ग_लिखो_init = s10_ops_ग_लिखो_init,
	.ग_लिखो = s10_ops_ग_लिखो,
	.ग_लिखो_complete = s10_ops_ग_लिखो_complete,
पूर्ण;

अटल पूर्णांक s10_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा s10_priv *priv;
	काष्ठा fpga_manager *mgr;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->client.dev = dev;
	priv->client.receive_cb = s10_receive_callback;
	priv->client.priv = priv;

	priv->chan = stratix10_svc_request_channel_byname(&priv->client,
							  SVC_CLIENT_FPGA);
	अगर (IS_ERR(priv->chan)) अणु
		dev_err(dev, "couldn't get service channel (%s)\n",
			SVC_CLIENT_FPGA);
		वापस PTR_ERR(priv->chan);
	पूर्ण

	init_completion(&priv->status_वापस_completion);

	mgr = fpga_mgr_create(dev, "Stratix10 SOC FPGA Manager",
			      &s10_ops, priv);
	अगर (!mgr) अणु
		dev_err(dev, "unable to create FPGA manager\n");
		ret = -ENOMEM;
		जाओ probe_err;
	पूर्ण

	ret = fpga_mgr_रेजिस्टर(mgr);
	अगर (ret) अणु
		dev_err(dev, "unable to register FPGA manager\n");
		fpga_mgr_मुक्त(mgr);
		जाओ probe_err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mgr);
	वापस ret;

probe_err:
	stratix10_svc_मुक्त_channel(priv->chan);
	वापस ret;
पूर्ण

अटल पूर्णांक s10_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fpga_manager *mgr = platक्रमm_get_drvdata(pdev);
	काष्ठा s10_priv *priv = mgr->priv;

	fpga_mgr_unरेजिस्टर(mgr);
	stratix10_svc_मुक्त_channel(priv->chan);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id s10_of_match[] = अणु
	अणु.compatible = "intel,stratix10-soc-fpga-mgr"पूर्ण,
	अणु.compatible = "intel,agilex-soc-fpga-mgr"पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, s10_of_match);

अटल काष्ठा platक्रमm_driver s10_driver = अणु
	.probe = s10_probe,
	.हटाओ = s10_हटाओ,
	.driver = अणु
		.name	= "Stratix10 SoC FPGA manager",
		.of_match_table = of_match_ptr(s10_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init s10_init(व्योम)
अणु
	काष्ठा device_node *fw_np;
	काष्ठा device_node *np;
	पूर्णांक ret;

	fw_np = of_find_node_by_name(शून्य, "svc");
	अगर (!fw_np)
		वापस -ENODEV;

	of_node_get(fw_np);
	np = of_find_matching_node(fw_np, s10_of_match);
	अगर (!np) अणु
		of_node_put(fw_np);
		वापस -ENODEV;
	पूर्ण

	of_node_put(np);
	ret = of_platक्रमm_populate(fw_np, s10_of_match, शून्य, शून्य);
	of_node_put(fw_np);
	अगर (ret)
		वापस ret;

	वापस platक्रमm_driver_रेजिस्टर(&s10_driver);
पूर्ण

अटल व्योम __निकास s10_निकास(व्योम)
अणु
	वापस platक्रमm_driver_unरेजिस्टर(&s10_driver);
पूर्ण

module_init(s10_init);
module_निकास(s10_निकास);

MODULE_AUTHOR("Alan Tull <atull@kernel.org>");
MODULE_DESCRIPTION("Intel Stratix 10 SOC FPGA Manager");
MODULE_LICENSE("GPL v2");
