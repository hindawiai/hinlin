<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IRQ offload/bypass manager
 *
 * Copyright (C) 2015 Red Hat, Inc.
 * Copyright (c) 2015 Linaro Ltd.
 *
 * Various भवization hardware acceleration techniques allow bypassing or
 * offloading पूर्णांकerrupts received from devices around the host kernel.  Posted
 * Interrupts on Intel VT-d प्रणालीs can allow पूर्णांकerrupts to be received
 * directly by a भव machine.  ARM IRQ Forwarding allows क्रमwarded physical
 * पूर्णांकerrupts to be directly deactivated by the guest.  This manager allows
 * पूर्णांकerrupt producers and consumers to find each other to enable this sort of
 * bypass.
 */

#समावेश <linux/irqbypass.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("IRQ bypass manager utility module");

अटल LIST_HEAD(producers);
अटल LIST_HEAD(consumers);
अटल DEFINE_MUTEX(lock);

/* @lock must be held when calling connect */
अटल पूर्णांक __connect(काष्ठा irq_bypass_producer *prod,
		     काष्ठा irq_bypass_consumer *cons)
अणु
	पूर्णांक ret = 0;

	अगर (prod->stop)
		prod->stop(prod);
	अगर (cons->stop)
		cons->stop(cons);

	अगर (prod->add_consumer)
		ret = prod->add_consumer(prod, cons);

	अगर (!ret) अणु
		ret = cons->add_producer(cons, prod);
		अगर (ret && prod->del_consumer)
			prod->del_consumer(prod, cons);
	पूर्ण

	अगर (cons->start)
		cons->start(cons);
	अगर (prod->start)
		prod->start(prod);

	वापस ret;
पूर्ण

/* @lock must be held when calling disconnect */
अटल व्योम __disconnect(काष्ठा irq_bypass_producer *prod,
			 काष्ठा irq_bypass_consumer *cons)
अणु
	अगर (prod->stop)
		prod->stop(prod);
	अगर (cons->stop)
		cons->stop(cons);

	cons->del_producer(cons, prod);

	अगर (prod->del_consumer)
		prod->del_consumer(prod, cons);

	अगर (cons->start)
		cons->start(cons);
	अगर (prod->start)
		prod->start(prod);
पूर्ण

/**
 * irq_bypass_रेजिस्टर_producer - रेजिस्टर IRQ bypass producer
 * @producer: poपूर्णांकer to producer काष्ठाure
 *
 * Add the provided IRQ producer to the list of producers and connect
 * with any matching token found on the IRQ consumers list.
 */
पूर्णांक irq_bypass_रेजिस्टर_producer(काष्ठा irq_bypass_producer *producer)
अणु
	काष्ठा irq_bypass_producer *पंचांगp;
	काष्ठा irq_bypass_consumer *consumer;
	पूर्णांक ret;

	अगर (!producer->token)
		वापस -EINVAL;

	might_sleep();

	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	mutex_lock(&lock);

	list_क्रम_each_entry(पंचांगp, &producers, node) अणु
		अगर (पंचांगp->token == producer->token) अणु
			ret = -EBUSY;
			जाओ out_err;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(consumer, &consumers, node) अणु
		अगर (consumer->token == producer->token) अणु
			ret = __connect(producer, consumer);
			अगर (ret)
				जाओ out_err;
			अवरोध;
		पूर्ण
	पूर्ण

	list_add(&producer->node, &producers);

	mutex_unlock(&lock);

	वापस 0;
out_err:
	mutex_unlock(&lock);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(irq_bypass_रेजिस्टर_producer);

/**
 * irq_bypass_unरेजिस्टर_producer - unरेजिस्टर IRQ bypass producer
 * @producer: poपूर्णांकer to producer काष्ठाure
 *
 * Remove a previously रेजिस्टरed IRQ producer from the list of producers
 * and disconnect it from any connected IRQ consumer.
 */
व्योम irq_bypass_unरेजिस्टर_producer(काष्ठा irq_bypass_producer *producer)
अणु
	काष्ठा irq_bypass_producer *पंचांगp;
	काष्ठा irq_bypass_consumer *consumer;

	अगर (!producer->token)
		वापस;

	might_sleep();

	अगर (!try_module_get(THIS_MODULE))
		वापस; /* nothing in the list anyway */

	mutex_lock(&lock);

	list_क्रम_each_entry(पंचांगp, &producers, node) अणु
		अगर (पंचांगp->token != producer->token)
			जारी;

		list_क्रम_each_entry(consumer, &consumers, node) अणु
			अगर (consumer->token == producer->token) अणु
				__disconnect(producer, consumer);
				अवरोध;
			पूर्ण
		पूर्ण

		list_del(&producer->node);
		module_put(THIS_MODULE);
		अवरोध;
	पूर्ण

	mutex_unlock(&lock);

	module_put(THIS_MODULE);
पूर्ण
EXPORT_SYMBOL_GPL(irq_bypass_unरेजिस्टर_producer);

/**
 * irq_bypass_रेजिस्टर_consumer - रेजिस्टर IRQ bypass consumer
 * @consumer: poपूर्णांकer to consumer काष्ठाure
 *
 * Add the provided IRQ consumer to the list of consumers and connect
 * with any matching token found on the IRQ producer list.
 */
पूर्णांक irq_bypass_रेजिस्टर_consumer(काष्ठा irq_bypass_consumer *consumer)
अणु
	काष्ठा irq_bypass_consumer *पंचांगp;
	काष्ठा irq_bypass_producer *producer;
	पूर्णांक ret;

	अगर (!consumer->token ||
	    !consumer->add_producer || !consumer->del_producer)
		वापस -EINVAL;

	might_sleep();

	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	mutex_lock(&lock);

	list_क्रम_each_entry(पंचांगp, &consumers, node) अणु
		अगर (पंचांगp->token == consumer->token || पंचांगp == consumer) अणु
			ret = -EBUSY;
			जाओ out_err;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(producer, &producers, node) अणु
		अगर (producer->token == consumer->token) अणु
			ret = __connect(producer, consumer);
			अगर (ret)
				जाओ out_err;
			अवरोध;
		पूर्ण
	पूर्ण

	list_add(&consumer->node, &consumers);

	mutex_unlock(&lock);

	वापस 0;
out_err:
	mutex_unlock(&lock);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(irq_bypass_रेजिस्टर_consumer);

/**
 * irq_bypass_unरेजिस्टर_consumer - unरेजिस्टर IRQ bypass consumer
 * @consumer: poपूर्णांकer to consumer काष्ठाure
 *
 * Remove a previously रेजिस्टरed IRQ consumer from the list of consumers
 * and disconnect it from any connected IRQ producer.
 */
व्योम irq_bypass_unरेजिस्टर_consumer(काष्ठा irq_bypass_consumer *consumer)
अणु
	काष्ठा irq_bypass_consumer *पंचांगp;
	काष्ठा irq_bypass_producer *producer;

	अगर (!consumer->token)
		वापस;

	might_sleep();

	अगर (!try_module_get(THIS_MODULE))
		वापस; /* nothing in the list anyway */

	mutex_lock(&lock);

	list_क्रम_each_entry(पंचांगp, &consumers, node) अणु
		अगर (पंचांगp != consumer)
			जारी;

		list_क्रम_each_entry(producer, &producers, node) अणु
			अगर (producer->token == consumer->token) अणु
				__disconnect(producer, consumer);
				अवरोध;
			पूर्ण
		पूर्ण

		list_del(&consumer->node);
		module_put(THIS_MODULE);
		अवरोध;
	पूर्ण

	mutex_unlock(&lock);

	module_put(THIS_MODULE);
पूर्ण
EXPORT_SYMBOL_GPL(irq_bypass_unरेजिस्टर_consumer);
