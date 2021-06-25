<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PowerNV OPAL IPMI driver
 *
 * Copyright 2014 IBM Corp.
 */

#घोषणा pr_fmt(fmt)        "ipmi-powernv: " fmt

#समावेश <linux/ipmi_smi.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/opal.h>


काष्ठा ipmi_smi_घातernv अणु
	u64			पूर्णांकerface_id;
	काष्ठा ipmi_smi		*पूर्णांकf;
	अचिन्हित पूर्णांक		irq;

	/**
	 * We assume that there can only be one outstanding request, so
	 * keep the pending message in cur_msg. We protect this from concurrent
	 * updates through send & recv calls, (and consequently opal_msg, which
	 * is in-use when cur_msg is set) with msg_lock
	 */
	spinlock_t		msg_lock;
	काष्ठा ipmi_smi_msg	*cur_msg;
	काष्ठा opal_ipmi_msg	*opal_msg;
पूर्ण;

अटल पूर्णांक ipmi_घातernv_start_processing(व्योम *send_info, काष्ठा ipmi_smi *पूर्णांकf)
अणु
	काष्ठा ipmi_smi_घातernv *smi = send_info;

	smi->पूर्णांकf = पूर्णांकf;
	वापस 0;
पूर्ण

अटल व्योम send_error_reply(काष्ठा ipmi_smi_घातernv *smi,
		काष्ठा ipmi_smi_msg *msg, u8 completion_code)
अणु
	msg->rsp[0] = msg->data[0] | 0x4;
	msg->rsp[1] = msg->data[1];
	msg->rsp[2] = completion_code;
	msg->rsp_size = 3;
	ipmi_smi_msg_received(smi->पूर्णांकf, msg);
पूर्ण

अटल व्योम ipmi_घातernv_send(व्योम *send_info, काष्ठा ipmi_smi_msg *msg)
अणु
	काष्ठा ipmi_smi_घातernv *smi = send_info;
	काष्ठा opal_ipmi_msg *opal_msg;
	अचिन्हित दीर्घ flags;
	पूर्णांक comp, rc;
	माप_प्रकार size;

	/* ensure data_len will fit in the opal_ipmi_msg buffer... */
	अगर (msg->data_size > IPMI_MAX_MSG_LENGTH) अणु
		comp = IPMI_REQ_LEN_EXCEEDED_ERR;
		जाओ err;
	पूर्ण

	/* ... and that we at least have netfn and cmd bytes */
	अगर (msg->data_size < 2) अणु
		comp = IPMI_REQ_LEN_INVALID_ERR;
		जाओ err;
	पूर्ण

	spin_lock_irqsave(&smi->msg_lock, flags);

	अगर (smi->cur_msg) अणु
		comp = IPMI_NODE_BUSY_ERR;
		जाओ err_unlock;
	पूर्ण

	/* क्रमmat our data क्रम the OPAL API */
	opal_msg = smi->opal_msg;
	opal_msg->version = OPAL_IPMI_MSG_FORMAT_VERSION_1;
	opal_msg->netfn = msg->data[0];
	opal_msg->cmd = msg->data[1];
	अगर (msg->data_size > 2)
		स_नकल(opal_msg->data, msg->data + 2, msg->data_size - 2);

	/* data_size alपढ़ोy includes the netfn and cmd bytes */
	size = माप(*opal_msg) + msg->data_size - 2;

	pr_devel("%s: opal_ipmi_send(0x%llx, %p, %ld)\n", __func__,
			smi->पूर्णांकerface_id, opal_msg, size);
	rc = opal_ipmi_send(smi->पूर्णांकerface_id, opal_msg, size);
	pr_devel("%s:  -> %d\n", __func__, rc);

	अगर (!rc) अणु
		smi->cur_msg = msg;
		spin_unlock_irqrestore(&smi->msg_lock, flags);
		वापस;
	पूर्ण

	comp = IPMI_ERR_UNSPECIFIED;
err_unlock:
	spin_unlock_irqrestore(&smi->msg_lock, flags);
err:
	send_error_reply(smi, msg, comp);
पूर्ण

अटल पूर्णांक ipmi_घातernv_recv(काष्ठा ipmi_smi_घातernv *smi)
अणु
	काष्ठा opal_ipmi_msg *opal_msg;
	काष्ठा ipmi_smi_msg *msg;
	अचिन्हित दीर्घ flags;
	uपूर्णांक64_t size;
	पूर्णांक rc;

	pr_devel("%s: opal_ipmi_recv(%llx, msg, sz)\n", __func__,
			smi->पूर्णांकerface_id);

	spin_lock_irqsave(&smi->msg_lock, flags);

	अगर (!smi->cur_msg) अणु
		spin_unlock_irqrestore(&smi->msg_lock, flags);
		pr_warn("no current message?\n");
		वापस 0;
	पूर्ण

	msg = smi->cur_msg;
	opal_msg = smi->opal_msg;

	size = cpu_to_be64(माप(*opal_msg) + IPMI_MAX_MSG_LENGTH);

	rc = opal_ipmi_recv(smi->पूर्णांकerface_id,
			opal_msg,
			&size);
	size = be64_to_cpu(size);
	pr_devel("%s:   -> %d (size %lld)\n", __func__,
			rc, rc == 0 ? size : 0);
	अगर (rc) अणु
		/* If came via the poll, and response was not yet पढ़ोy */
		अगर (rc == OPAL_EMPTY) अणु
			spin_unlock_irqrestore(&smi->msg_lock, flags);
			वापस 0;
		पूर्ण

		smi->cur_msg = शून्य;
		spin_unlock_irqrestore(&smi->msg_lock, flags);
		send_error_reply(smi, msg, IPMI_ERR_UNSPECIFIED);
		वापस 0;
	पूर्ण

	अगर (size < माप(*opal_msg)) अणु
		spin_unlock_irqrestore(&smi->msg_lock, flags);
		pr_warn("unexpected IPMI message size %lld\n", size);
		वापस 0;
	पूर्ण

	अगर (opal_msg->version != OPAL_IPMI_MSG_FORMAT_VERSION_1) अणु
		spin_unlock_irqrestore(&smi->msg_lock, flags);
		pr_warn("unexpected IPMI message format (version %d)\n",
				opal_msg->version);
		वापस 0;
	पूर्ण

	msg->rsp[0] = opal_msg->netfn;
	msg->rsp[1] = opal_msg->cmd;
	अगर (size > माप(*opal_msg))
		स_नकल(&msg->rsp[2], opal_msg->data, size - माप(*opal_msg));
	msg->rsp_size = 2 + size - माप(*opal_msg);

	smi->cur_msg = शून्य;
	spin_unlock_irqrestore(&smi->msg_lock, flags);
	ipmi_smi_msg_received(smi->पूर्णांकf, msg);
	वापस 0;
पूर्ण

अटल व्योम ipmi_घातernv_request_events(व्योम *send_info)
अणु
पूर्ण

अटल व्योम ipmi_घातernv_set_run_to_completion(व्योम *send_info,
		bool run_to_completion)
अणु
पूर्ण

अटल व्योम ipmi_घातernv_poll(व्योम *send_info)
अणु
	काष्ठा ipmi_smi_घातernv *smi = send_info;

	ipmi_घातernv_recv(smi);
पूर्ण

अटल स्थिर काष्ठा ipmi_smi_handlers ipmi_घातernv_smi_handlers = अणु
	.owner			= THIS_MODULE,
	.start_processing	= ipmi_घातernv_start_processing,
	.sender			= ipmi_घातernv_send,
	.request_events		= ipmi_घातernv_request_events,
	.set_run_to_completion	= ipmi_घातernv_set_run_to_completion,
	.poll			= ipmi_घातernv_poll,
पूर्ण;

अटल irqवापस_t ipmi_opal_event(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ipmi_smi_घातernv *smi = data;

	ipmi_घातernv_recv(smi);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ipmi_घातernv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipmi_smi_घातernv *ipmi;
	काष्ठा device *dev;
	u32 prop;
	पूर्णांक rc;

	अगर (!pdev || !pdev->dev.of_node)
		वापस -ENODEV;

	dev = &pdev->dev;

	ipmi = devm_kzalloc(dev, माप(*ipmi), GFP_KERNEL);
	अगर (!ipmi)
		वापस -ENOMEM;

	spin_lock_init(&ipmi->msg_lock);

	rc = of_property_पढ़ो_u32(dev->of_node, "ibm,ipmi-interface-id",
			&prop);
	अगर (rc) अणु
		dev_warn(dev, "No interface ID property\n");
		जाओ err_मुक्त;
	पूर्ण
	ipmi->पूर्णांकerface_id = prop;

	rc = of_property_पढ़ो_u32(dev->of_node, "interrupts", &prop);
	अगर (rc) अणु
		dev_warn(dev, "No interrupts property\n");
		जाओ err_मुक्त;
	पूर्ण

	ipmi->irq = irq_of_parse_and_map(dev->of_node, 0);
	अगर (!ipmi->irq) अणु
		dev_info(dev, "Unable to map irq from device tree\n");
		ipmi->irq = opal_event_request(prop);
	पूर्ण

	rc = request_irq(ipmi->irq, ipmi_opal_event, IRQ_TYPE_LEVEL_HIGH,
			 "opal-ipmi", ipmi);
	अगर (rc) अणु
		dev_warn(dev, "Unable to request irq\n");
		जाओ err_dispose;
	पूर्ण

	ipmi->opal_msg = devm_kदो_स्मृति(dev,
			माप(*ipmi->opal_msg) + IPMI_MAX_MSG_LENGTH,
			GFP_KERNEL);
	अगर (!ipmi->opal_msg) अणु
		rc = -ENOMEM;
		जाओ err_unरेजिस्टर;
	पूर्ण

	rc = ipmi_रेजिस्टर_smi(&ipmi_घातernv_smi_handlers, ipmi, dev, 0);
	अगर (rc) अणु
		dev_warn(dev, "IPMI SMI registration failed (%d)\n", rc);
		जाओ err_मुक्त_msg;
	पूर्ण

	dev_set_drvdata(dev, ipmi);
	वापस 0;

err_मुक्त_msg:
	devm_kमुक्त(dev, ipmi->opal_msg);
err_unरेजिस्टर:
	मुक्त_irq(ipmi->irq, ipmi);
err_dispose:
	irq_dispose_mapping(ipmi->irq);
err_मुक्त:
	devm_kमुक्त(dev, ipmi);
	वापस rc;
पूर्ण

अटल पूर्णांक ipmi_घातernv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipmi_smi_घातernv *smi = dev_get_drvdata(&pdev->dev);

	ipmi_unरेजिस्टर_smi(smi->पूर्णांकf);
	मुक्त_irq(smi->irq, smi);
	irq_dispose_mapping(smi->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ipmi_घातernv_match[] = अणु
	अणु .compatible = "ibm,opal-ipmi" पूर्ण,
	अणु पूर्ण,
पूर्ण;


अटल काष्ठा platक्रमm_driver घातernv_ipmi_driver = अणु
	.driver = अणु
		.name		= "ipmi-powernv",
		.of_match_table	= ipmi_घातernv_match,
	पूर्ण,
	.probe	= ipmi_घातernv_probe,
	.हटाओ	= ipmi_घातernv_हटाओ,
पूर्ण;


module_platक्रमm_driver(घातernv_ipmi_driver);

MODULE_DEVICE_TABLE(of, ipmi_घातernv_match);
MODULE_DESCRIPTION("powernv IPMI driver");
MODULE_AUTHOR("Jeremy Kerr <jk@ozlabs.org>");
MODULE_LICENSE("GPL");
