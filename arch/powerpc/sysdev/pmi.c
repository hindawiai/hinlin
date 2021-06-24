<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pmi driver
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * PMI (Platक्रमm Management Interrupt) is a way to communicate
 * with the BMC (Baseboard Management Controller) via पूर्णांकerrupts.
 * Unlike IPMI it is bidirectional and has a low latency.
 *
 * Author: Christian Krafft <krafft@de.ibm.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/pmi.h>
#समावेश <यंत्र/prom.h>

काष्ठा pmi_data अणु
	काष्ठा list_head	handler;
	spinlock_t		handler_spinlock;
	spinlock_t		pmi_spinlock;
	काष्ठा mutex		msg_mutex;
	pmi_message_t		msg;
	काष्ठा completion	*completion;
	काष्ठा platक्रमm_device	*dev;
	पूर्णांक			irq;
	u8 __iomem		*pmi_reg;
	काष्ठा work_काष्ठा	work;
पूर्ण;

अटल काष्ठा pmi_data *data;

अटल irqवापस_t pmi_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u8 type;
	पूर्णांक rc;

	spin_lock(&data->pmi_spinlock);

	type = ioपढ़ो8(data->pmi_reg + PMI_READ_TYPE);
	pr_debug("pmi: got message of type %d\n", type);

	अगर (type & PMI_ACK && !data->completion) अणु
		prपूर्णांकk(KERN_WARNING "pmi: got unexpected ACK message.\n");
		rc = -EIO;
		जाओ unlock;
	पूर्ण

	अगर (data->completion && !(type & PMI_ACK)) अणु
		prपूर्णांकk(KERN_WARNING "pmi: expected ACK, but got %d\n", type);
		rc = -EIO;
		जाओ unlock;
	पूर्ण

	data->msg.type = type;
	data->msg.data0 = ioपढ़ो8(data->pmi_reg + PMI_READ_DATA0);
	data->msg.data1 = ioपढ़ो8(data->pmi_reg + PMI_READ_DATA1);
	data->msg.data2 = ioपढ़ो8(data->pmi_reg + PMI_READ_DATA2);
	rc = 0;
unlock:
	spin_unlock(&data->pmi_spinlock);

	अगर (rc == -EIO) अणु
		rc = IRQ_HANDLED;
		जाओ out;
	पूर्ण

	अगर (data->msg.type & PMI_ACK) अणु
		complete(data->completion);
		rc = IRQ_HANDLED;
		जाओ out;
	पूर्ण

	schedule_work(&data->work);

	rc = IRQ_HANDLED;
out:
	वापस rc;
पूर्ण


अटल स्थिर काष्ठा of_device_id pmi_match[] = अणु
	अणु .type = "ibm,pmi", .name = "ibm,pmi" पूर्ण,
	अणु .type = "ibm,pmi" पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, pmi_match);

अटल व्योम pmi_notअगरy_handlers(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pmi_handler *handler;

	spin_lock(&data->handler_spinlock);
	list_क्रम_each_entry(handler, &data->handler, node) अणु
		pr_debug("pmi: notifying handler %p\n", handler);
		अगर (handler->type == data->msg.type)
			handler->handle_pmi_message(data->msg);
	पूर्ण
	spin_unlock(&data->handler_spinlock);
पूर्ण

अटल पूर्णांक pmi_of_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा device_node *np = dev->dev.of_node;
	पूर्णांक rc;

	अगर (data) अणु
		prपूर्णांकk(KERN_ERR "pmi: driver has already been initialized.\n");
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	data = kzalloc(माप(काष्ठा pmi_data), GFP_KERNEL);
	अगर (!data) अणु
		prपूर्णांकk(KERN_ERR "pmi: could not allocate memory.\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	data->pmi_reg = of_iomap(np, 0);
	अगर (!data->pmi_reg) अणु
		prपूर्णांकk(KERN_ERR "pmi: invalid register address.\n");
		rc = -EFAULT;
		जाओ error_cleanup_data;
	पूर्ण

	INIT_LIST_HEAD(&data->handler);

	mutex_init(&data->msg_mutex);
	spin_lock_init(&data->pmi_spinlock);
	spin_lock_init(&data->handler_spinlock);

	INIT_WORK(&data->work, pmi_notअगरy_handlers);

	data->dev = dev;

	data->irq = irq_of_parse_and_map(np, 0);
	अगर (!data->irq) अणु
		prपूर्णांकk(KERN_ERR "pmi: invalid interrupt.\n");
		rc = -EFAULT;
		जाओ error_cleanup_iomap;
	पूर्ण

	rc = request_irq(data->irq, pmi_irq_handler, 0, "pmi", शून्य);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "pmi: can't request IRQ %d: returned %d\n",
				data->irq, rc);
		जाओ error_cleanup_iomap;
	पूर्ण

	prपूर्णांकk(KERN_INFO "pmi: found pmi device at addr %p.\n", data->pmi_reg);

	जाओ out;

error_cleanup_iomap:
	iounmap(data->pmi_reg);

error_cleanup_data:
	kमुक्त(data);

out:
	वापस rc;
पूर्ण

अटल पूर्णांक pmi_of_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pmi_handler *handler, *पंचांगp;

	मुक्त_irq(data->irq, शून्य);
	iounmap(data->pmi_reg);

	spin_lock(&data->handler_spinlock);

	list_क्रम_each_entry_safe(handler, पंचांगp, &data->handler, node)
		list_del(&handler->node);

	spin_unlock(&data->handler_spinlock);

	kमुक्त(data);
	data = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pmi_of_platक्रमm_driver = अणु
	.probe		= pmi_of_probe,
	.हटाओ		= pmi_of_हटाओ,
	.driver = अणु
		.name = "pmi",
		.of_match_table = pmi_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pmi_of_platक्रमm_driver);

पूर्णांक pmi_send_message(pmi_message_t msg)
अणु
	अचिन्हित दीर्घ flags;
	DECLARE_COMPLETION_ONSTACK(completion);

	अगर (!data)
		वापस -ENODEV;

	mutex_lock(&data->msg_mutex);

	data->msg = msg;
	pr_debug("pmi_send_message: msg is %08x\n", *(u32*)&msg);

	data->completion = &completion;

	spin_lock_irqsave(&data->pmi_spinlock, flags);
	ioग_लिखो8(msg.data0, data->pmi_reg + PMI_WRITE_DATA0);
	ioग_लिखो8(msg.data1, data->pmi_reg + PMI_WRITE_DATA1);
	ioग_लिखो8(msg.data2, data->pmi_reg + PMI_WRITE_DATA2);
	ioग_लिखो8(msg.type, data->pmi_reg + PMI_WRITE_TYPE);
	spin_unlock_irqrestore(&data->pmi_spinlock, flags);

	pr_debug("pmi_send_message: wait for completion\n");

	रुको_क्रम_completion_पूर्णांकerruptible_समयout(data->completion,
						  PMI_TIMEOUT);

	data->completion = शून्य;

	mutex_unlock(&data->msg_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pmi_send_message);

पूर्णांक pmi_रेजिस्टर_handler(काष्ठा pmi_handler *handler)
अणु
	अगर (!data)
		वापस -ENODEV;

	spin_lock(&data->handler_spinlock);
	list_add_tail(&handler->node, &data->handler);
	spin_unlock(&data->handler_spinlock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pmi_रेजिस्टर_handler);

व्योम pmi_unरेजिस्टर_handler(काष्ठा pmi_handler *handler)
अणु
	अगर (!data)
		वापस;

	pr_debug("pmi: unregistering handler %p\n", handler);

	spin_lock(&data->handler_spinlock);
	list_del(&handler->node);
	spin_unlock(&data->handler_spinlock);
पूर्ण
EXPORT_SYMBOL_GPL(pmi_unरेजिस्टर_handler);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Krafft <krafft@de.ibm.com>");
MODULE_DESCRIPTION("IBM Platform Management Interrupt driver");
