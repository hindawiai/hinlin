<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Sony MemoryStick support
 *
 *  Copyright (C) 2007 Alex Dubov <oakad@yahoo.com>
 *
 * Special thanks to Carlos Corbacho क्रम providing various MemoryStick cards
 * that made this driver possible.
 */

#समावेश <linux/memstick.h>
#समावेश <linux/idr.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा DRIVER_NAME "memstick"

अटल अचिन्हित पूर्णांक cmd_retries = 3;
module_param(cmd_retries, uपूर्णांक, 0644);

अटल काष्ठा workqueue_काष्ठा *workqueue;
अटल DEFINE_IDR(memstick_host_idr);
अटल DEFINE_SPINLOCK(memstick_host_lock);

अटल पूर्णांक memstick_dev_match(काष्ठा memstick_dev *card,
			      काष्ठा memstick_device_id *id)
अणु
	अगर (id->match_flags & MEMSTICK_MATCH_ALL) अणु
		अगर ((id->type == card->id.type)
		    && (id->category == card->id.category)
		    && (id->class == card->id.class))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक memstick_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा memstick_dev *card = container_of(dev, काष्ठा memstick_dev,
						 dev);
	काष्ठा memstick_driver *ms_drv = container_of(drv,
						      काष्ठा memstick_driver,
						      driver);
	काष्ठा memstick_device_id *ids = ms_drv->id_table;

	अगर (ids) अणु
		जबतक (ids->match_flags) अणु
			अगर (memstick_dev_match(card, ids))
				वापस 1;
			++ids;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक memstick_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा memstick_dev *card = container_of(dev, काष्ठा memstick_dev,
						  dev);

	अगर (add_uevent_var(env, "MEMSTICK_TYPE=%02X", card->id.type))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "MEMSTICK_CATEGORY=%02X", card->id.category))
		वापस -ENOMEM;

	अगर (add_uevent_var(env, "MEMSTICK_CLASS=%02X", card->id.class))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक memstick_device_probe(काष्ठा device *dev)
अणु
	काष्ठा memstick_dev *card = container_of(dev, काष्ठा memstick_dev,
						 dev);
	काष्ठा memstick_driver *drv = container_of(dev->driver,
						   काष्ठा memstick_driver,
						   driver);
	पूर्णांक rc = -ENODEV;

	अगर (dev->driver && drv->probe) अणु
		rc = drv->probe(card);
		अगर (!rc)
			get_device(dev);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक memstick_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा memstick_dev *card = container_of(dev, काष्ठा memstick_dev,
						  dev);
	काष्ठा memstick_driver *drv = container_of(dev->driver,
						   काष्ठा memstick_driver,
						   driver);

	अगर (dev->driver && drv->हटाओ) अणु
		drv->हटाओ(card);
		card->dev.driver = शून्य;
	पूर्ण

	put_device(dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक memstick_device_suspend(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा memstick_dev *card = container_of(dev, काष्ठा memstick_dev,
						  dev);
	काष्ठा memstick_driver *drv = container_of(dev->driver,
						   काष्ठा memstick_driver,
						   driver);

	अगर (dev->driver && drv->suspend)
		वापस drv->suspend(card, state);
	वापस 0;
पूर्ण

अटल पूर्णांक memstick_device_resume(काष्ठा device *dev)
अणु
	काष्ठा memstick_dev *card = container_of(dev, काष्ठा memstick_dev,
						  dev);
	काष्ठा memstick_driver *drv = container_of(dev->driver,
						   काष्ठा memstick_driver,
						   driver);

	अगर (dev->driver && drv->resume)
		वापस drv->resume(card);
	वापस 0;
पूर्ण

#अन्यथा

#घोषणा memstick_device_suspend शून्य
#घोषणा memstick_device_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

#घोषणा MEMSTICK_ATTR(name, क्रमmat)                                           \
अटल sमाप_प्रकार name##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, \
			    अक्षर *buf)                                        \
अणु                                                                             \
	काष्ठा memstick_dev *card = container_of(dev, काष्ठा memstick_dev,    \
						 dev);                        \
	वापस प्र_लिखो(buf, क्रमmat, card->id.name);                           \
पूर्ण                                                                             \
अटल DEVICE_ATTR_RO(name);

MEMSTICK_ATTR(type, "%02X");
MEMSTICK_ATTR(category, "%02X");
MEMSTICK_ATTR(class, "%02X");

अटल काष्ठा attribute *memstick_dev_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_category.attr,
	&dev_attr_class.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(memstick_dev);

अटल काष्ठा bus_type memstick_bus_type = अणु
	.name           = "memstick",
	.dev_groups	= memstick_dev_groups,
	.match          = memstick_bus_match,
	.uevent         = memstick_uevent,
	.probe          = memstick_device_probe,
	.हटाओ         = memstick_device_हटाओ,
	.suspend        = memstick_device_suspend,
	.resume         = memstick_device_resume
पूर्ण;

अटल व्योम memstick_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा memstick_host *host = container_of(dev, काष्ठा memstick_host,
						  dev);
	kमुक्त(host);
पूर्ण

अटल काष्ठा class memstick_host_class = अणु
	.name        = "memstick_host",
	.dev_release = memstick_मुक्त
पूर्ण;

अटल व्योम memstick_मुक्त_card(काष्ठा device *dev)
अणु
	काष्ठा memstick_dev *card = container_of(dev, काष्ठा memstick_dev,
						 dev);
	kमुक्त(card);
पूर्ण

अटल पूर्णांक memstick_dummy_check(काष्ठा memstick_dev *card)
अणु
	वापस 0;
पूर्ण

/**
 * memstick_detect_change - schedule media detection on memstick host
 * @host - host to use
 */
व्योम memstick_detect_change(काष्ठा memstick_host *host)
अणु
	queue_work(workqueue, &host->media_checker);
पूर्ण
EXPORT_SYMBOL(memstick_detect_change);

/**
 * memstick_next_req - called by host driver to obtain next request to process
 * @host - host to use
 * @mrq - poपूर्णांकer to stick the request to
 *
 * Host calls this function from idle state (*mrq == शून्य) or after finishing
 * previous request (*mrq should poपूर्णांक to it). If previous request was
 * unsuccessful, it is retried क्रम predetermined number of बार. Return value
 * of 0 means that new request was asचिन्हित to the host.
 */
पूर्णांक memstick_next_req(काष्ठा memstick_host *host, काष्ठा memstick_request **mrq)
अणु
	पूर्णांक rc = -ENXIO;

	अगर ((*mrq) && (*mrq)->error && host->retries) अणु
		(*mrq)->error = rc;
		host->retries--;
		वापस 0;
	पूर्ण

	अगर (host->card && host->card->next_request)
		rc = host->card->next_request(host->card, mrq);

	अगर (!rc)
		host->retries = cmd_retries > 1 ? cmd_retries - 1 : 1;
	अन्यथा
		*mrq = शून्य;

	वापस rc;
पूर्ण
EXPORT_SYMBOL(memstick_next_req);

/**
 * memstick_new_req - notअगरy the host that some requests are pending
 * @host - host to use
 */
व्योम memstick_new_req(काष्ठा memstick_host *host)
अणु
	अगर (host->card) अणु
		host->retries = cmd_retries;
		reinit_completion(&host->card->mrq_complete);
		host->request(host);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(memstick_new_req);

/**
 * memstick_init_req_sg - set request fields needed क्रम bulk data transfer
 * @mrq - request to use
 * @tpc - memstick Transport Protocol Command
 * @sg - TPC argument
 */
व्योम memstick_init_req_sg(काष्ठा memstick_request *mrq, अचिन्हित अक्षर tpc,
			  स्थिर काष्ठा scatterlist *sg)
अणु
	mrq->tpc = tpc;
	अगर (tpc & 8)
		mrq->data_dir = WRITE;
	अन्यथा
		mrq->data_dir = READ;

	mrq->sg = *sg;
	mrq->दीर्घ_data = 1;

	अगर (tpc == MS_TPC_SET_CMD || tpc == MS_TPC_EX_SET_CMD)
		mrq->need_card_पूर्णांक = 1;
	अन्यथा
		mrq->need_card_पूर्णांक = 0;
पूर्ण
EXPORT_SYMBOL(memstick_init_req_sg);

/**
 * memstick_init_req - set request fields needed क्रम लघु data transfer
 * @mrq - request to use
 * @tpc - memstick Transport Protocol Command
 * @buf - TPC argument buffer
 * @length - TPC argument size
 *
 * The पूर्णांकended use of this function (transfer of data items several bytes
 * in size) allows us to just copy the value between request काष्ठाure and
 * user supplied buffer.
 */
व्योम memstick_init_req(काष्ठा memstick_request *mrq, अचिन्हित अक्षर tpc,
		       स्थिर व्योम *buf, माप_प्रकार length)
अणु
	mrq->tpc = tpc;
	अगर (tpc & 8)
		mrq->data_dir = WRITE;
	अन्यथा
		mrq->data_dir = READ;

	mrq->data_len = length > माप(mrq->data) ? माप(mrq->data) : length;
	अगर (mrq->data_dir == WRITE)
		स_नकल(mrq->data, buf, mrq->data_len);

	mrq->दीर्घ_data = 0;

	अगर (tpc == MS_TPC_SET_CMD || tpc == MS_TPC_EX_SET_CMD)
		mrq->need_card_पूर्णांक = 1;
	अन्यथा
		mrq->need_card_पूर्णांक = 0;
पूर्ण
EXPORT_SYMBOL(memstick_init_req);

/*
 * Functions prefixed with "h_" are protocol callbacks. They can be called from
 * पूर्णांकerrupt context. Return value of 0 means that request processing is still
 * ongoing, जबतक special error value of -EAGAIN means that current request is
 * finished (and request processor should come back some समय later).
 */

अटल पूर्णांक h_memstick_पढ़ो_dev_id(काष्ठा memstick_dev *card,
				  काष्ठा memstick_request **mrq)
अणु
	काष्ठा ms_id_रेजिस्टर id_reg;

	अगर (!(*mrq)) अणु
		memstick_init_req(&card->current_mrq, MS_TPC_READ_REG, &id_reg,
				  माप(काष्ठा ms_id_रेजिस्टर));
		*mrq = &card->current_mrq;
		वापस 0;
	पूर्ण
	अगर (!(*mrq)->error) अणु
		स_नकल(&id_reg, (*mrq)->data, माप(id_reg));
		card->id.match_flags = MEMSTICK_MATCH_ALL;
		card->id.type = id_reg.type;
		card->id.category = id_reg.category;
		card->id.class = id_reg.class;
		dev_dbg(&card->dev, "if_mode = %02x\n", id_reg.अगर_mode);
	पूर्ण
	complete(&card->mrq_complete);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक h_memstick_set_rw_addr(काष्ठा memstick_dev *card,
				  काष्ठा memstick_request **mrq)
अणु
	अगर (!(*mrq)) अणु
		memstick_init_req(&card->current_mrq, MS_TPC_SET_RW_REG_ADRS,
				  (अक्षर *)&card->reg_addr,
				  माप(card->reg_addr));
		*mrq = &card->current_mrq;
		वापस 0;
	पूर्ण अन्यथा अणु
		complete(&card->mrq_complete);
		वापस -EAGAIN;
	पूर्ण
पूर्ण

/**
 * memstick_set_rw_addr - issue SET_RW_REG_ADDR request and रुको क्रम it to
 *                        complete
 * @card - media device to use
 */
पूर्णांक memstick_set_rw_addr(काष्ठा memstick_dev *card)
अणु
	card->next_request = h_memstick_set_rw_addr;
	memstick_new_req(card->host);
	रुको_क्रम_completion(&card->mrq_complete);

	वापस card->current_mrq.error;
पूर्ण
EXPORT_SYMBOL(memstick_set_rw_addr);

अटल काष्ठा memstick_dev *memstick_alloc_card(काष्ठा memstick_host *host)
अणु
	काष्ठा memstick_dev *card = kzalloc(माप(काष्ठा memstick_dev),
					    GFP_KERNEL);
	काष्ठा memstick_dev *old_card = host->card;
	काष्ठा ms_id_रेजिस्टर id_reg;

	अगर (card) अणु
		card->host = host;
		dev_set_name(&card->dev, "%s", dev_name(&host->dev));
		card->dev.parent = &host->dev;
		card->dev.bus = &memstick_bus_type;
		card->dev.release = memstick_मुक्त_card;
		card->check = memstick_dummy_check;

		card->reg_addr.r_offset = दुरत्व(काष्ठा ms_रेजिस्टर, id);
		card->reg_addr.r_length = माप(id_reg);
		card->reg_addr.w_offset = दुरत्व(काष्ठा ms_रेजिस्टर, id);
		card->reg_addr.w_length = माप(id_reg);

		init_completion(&card->mrq_complete);

		host->card = card;
		अगर (memstick_set_rw_addr(card))
			जाओ err_out;

		card->next_request = h_memstick_पढ़ो_dev_id;
		memstick_new_req(host);
		रुको_क्रम_completion(&card->mrq_complete);

		अगर (card->current_mrq.error)
			जाओ err_out;
	पूर्ण
	host->card = old_card;
	वापस card;
err_out:
	host->card = old_card;
	kमुक्त(card);
	वापस शून्य;
पूर्ण

अटल पूर्णांक memstick_घातer_on(काष्ठा memstick_host *host)
अणु
	पूर्णांक rc = host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_ON);

	अगर (!rc)
		rc = host->set_param(host, MEMSTICK_INTERFACE, MEMSTICK_SERIAL);

	वापस rc;
पूर्ण

अटल व्योम memstick_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा memstick_host *host = container_of(work, काष्ठा memstick_host,
						  media_checker);
	काष्ठा memstick_dev *card;

	dev_dbg(&host->dev, "memstick_check started\n");
	pm_runसमय_get_noresume(host->dev.parent);
	mutex_lock(&host->lock);
	अगर (!host->card) अणु
		अगर (memstick_घातer_on(host))
			जाओ out_घातer_off;
	पूर्ण अन्यथा अगर (host->card->stop)
		host->card->stop(host->card);

	अगर (host->removing)
		जाओ out_घातer_off;

	card = memstick_alloc_card(host);

	अगर (!card) अणु
		अगर (host->card) अणु
			device_unरेजिस्टर(&host->card->dev);
			host->card = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&host->dev, "new card %02x, %02x, %02x\n",
			card->id.type, card->id.category, card->id.class);
		अगर (host->card) अणु
			अगर (memstick_set_rw_addr(host->card)
			    || !memstick_dev_match(host->card, &card->id)
			    || !(host->card->check(host->card))) अणु
				device_unरेजिस्टर(&host->card->dev);
				host->card = शून्य;
			पूर्ण अन्यथा अगर (host->card->start)
				host->card->start(host->card);
		पूर्ण

		अगर (!host->card) अणु
			host->card = card;
			अगर (device_रेजिस्टर(&card->dev)) अणु
				put_device(&card->dev);
				host->card = शून्य;
			पूर्ण
		पूर्ण अन्यथा
			kमुक्त(card);
	पूर्ण

out_घातer_off:
	अगर (!host->card)
		host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_OFF);

	mutex_unlock(&host->lock);
	pm_runसमय_put(host->dev.parent);
	dev_dbg(&host->dev, "memstick_check finished\n");
पूर्ण

/**
 * memstick_alloc_host - allocate a memstick_host काष्ठाure
 * @extra: size of the user निजी data to allocate
 * @dev: parent device of the host
 */
काष्ठा memstick_host *memstick_alloc_host(अचिन्हित पूर्णांक extra,
					  काष्ठा device *dev)
अणु
	काष्ठा memstick_host *host;

	host = kzalloc(माप(काष्ठा memstick_host) + extra, GFP_KERNEL);
	अगर (host) अणु
		mutex_init(&host->lock);
		INIT_WORK(&host->media_checker, memstick_check);
		host->dev.class = &memstick_host_class;
		host->dev.parent = dev;
		device_initialize(&host->dev);
	पूर्ण
	वापस host;
पूर्ण
EXPORT_SYMBOL(memstick_alloc_host);

/**
 * memstick_add_host - start request processing on memstick host
 * @host - host to use
 */
पूर्णांक memstick_add_host(काष्ठा memstick_host *host)
अणु
	पूर्णांक rc;

	idr_preload(GFP_KERNEL);
	spin_lock(&memstick_host_lock);

	rc = idr_alloc(&memstick_host_idr, host, 0, 0, GFP_NOWAIT);
	अगर (rc >= 0)
		host->id = rc;

	spin_unlock(&memstick_host_lock);
	idr_preload_end();
	अगर (rc < 0)
		वापस rc;

	dev_set_name(&host->dev, "memstick%u", host->id);

	rc = device_add(&host->dev);
	अगर (rc) अणु
		spin_lock(&memstick_host_lock);
		idr_हटाओ(&memstick_host_idr, host->id);
		spin_unlock(&memstick_host_lock);
		वापस rc;
	पूर्ण

	host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_OFF);
	memstick_detect_change(host);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(memstick_add_host);

/**
 * memstick_हटाओ_host - stop request processing on memstick host
 * @host - host to use
 */
व्योम memstick_हटाओ_host(काष्ठा memstick_host *host)
अणु
	host->removing = 1;
	flush_workqueue(workqueue);
	mutex_lock(&host->lock);
	अगर (host->card)
		device_unरेजिस्टर(&host->card->dev);
	host->card = शून्य;
	host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_OFF);
	mutex_unlock(&host->lock);

	spin_lock(&memstick_host_lock);
	idr_हटाओ(&memstick_host_idr, host->id);
	spin_unlock(&memstick_host_lock);
	device_del(&host->dev);
पूर्ण
EXPORT_SYMBOL(memstick_हटाओ_host);

/**
 * memstick_मुक्त_host - मुक्त memstick host
 * @host - host to use
 */
व्योम memstick_मुक्त_host(काष्ठा memstick_host *host)
अणु
	mutex_destroy(&host->lock);
	put_device(&host->dev);
पूर्ण
EXPORT_SYMBOL(memstick_मुक्त_host);

/**
 * memstick_suspend_host - notअगरy bus driver of host suspension
 * @host - host to use
 */
व्योम memstick_suspend_host(काष्ठा memstick_host *host)
अणु
	mutex_lock(&host->lock);
	host->set_param(host, MEMSTICK_POWER, MEMSTICK_POWER_OFF);
	mutex_unlock(&host->lock);
पूर्ण
EXPORT_SYMBOL(memstick_suspend_host);

/**
 * memstick_resume_host - notअगरy bus driver of host resumption
 * @host - host to use
 */
व्योम memstick_resume_host(काष्ठा memstick_host *host)
अणु
	पूर्णांक rc = 0;

	mutex_lock(&host->lock);
	अगर (host->card)
		rc = memstick_घातer_on(host);
	mutex_unlock(&host->lock);

	अगर (!rc)
		memstick_detect_change(host);
पूर्ण
EXPORT_SYMBOL(memstick_resume_host);

पूर्णांक memstick_रेजिस्टर_driver(काष्ठा memstick_driver *drv)
अणु
	drv->driver.bus = &memstick_bus_type;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(memstick_रेजिस्टर_driver);

व्योम memstick_unरेजिस्टर_driver(काष्ठा memstick_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(memstick_unरेजिस्टर_driver);


अटल पूर्णांक __init memstick_init(व्योम)
अणु
	पूर्णांक rc;

	workqueue = create_मुक्तzable_workqueue("kmemstick");
	अगर (!workqueue)
		वापस -ENOMEM;

	rc = bus_रेजिस्टर(&memstick_bus_type);
	अगर (rc)
		जाओ error_destroy_workqueue;

	rc = class_रेजिस्टर(&memstick_host_class);
	अगर (rc)
		जाओ error_bus_unरेजिस्टर;

	वापस 0;

error_bus_unरेजिस्टर:
	bus_unरेजिस्टर(&memstick_bus_type);
error_destroy_workqueue:
	destroy_workqueue(workqueue);

	वापस rc;
पूर्ण

अटल व्योम __निकास memstick_निकास(व्योम)
अणु
	class_unरेजिस्टर(&memstick_host_class);
	bus_unरेजिस्टर(&memstick_bus_type);
	destroy_workqueue(workqueue);
	idr_destroy(&memstick_host_idr);
पूर्ण

module_init(memstick_init);
module_निकास(memstick_निकास);

MODULE_AUTHOR("Alex Dubov");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Sony MemoryStick core driver");
