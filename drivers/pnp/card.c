<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * card.c - contains functions क्रम managing groups of PnP devices
 *
 * Copyright 2002 Adam Belay <ambx1@neo.rr.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/pnp.h>
#समावेश <linux/dma-mapping.h>
#समावेश "base.h"

LIST_HEAD(pnp_cards);
अटल LIST_HEAD(pnp_card_drivers);

अटल स्थिर काष्ठा pnp_card_device_id *match_card(काष्ठा pnp_card_driver *drv,
						   काष्ठा pnp_card *card)
अणु
	स्थिर काष्ठा pnp_card_device_id *drv_id = drv->id_table;

	जबतक (*drv_id->id) अणु
		अगर (compare_pnp_id(card->id, drv_id->id)) अणु
			पूर्णांक i = 0;

			क्रम (;;) अणु
				पूर्णांक found;
				काष्ठा pnp_dev *dev;

				अगर (i == PNP_MAX_DEVICES ||
				    !*drv_id->devs[i].id)
					वापस drv_id;
				found = 0;
				card_क्रम_each_dev(card, dev) अणु
					अगर (compare_pnp_id(dev->id,
						   drv_id->devs[i].id)) अणु
						found = 1;
						अवरोध;
					पूर्ण
				पूर्ण
				अगर (!found)
					अवरोध;
				i++;
			पूर्ण
		पूर्ण
		drv_id++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम card_हटाओ(काष्ठा pnp_dev *dev)
अणु
	dev->card_link = शून्य;
पूर्ण

अटल व्योम card_हटाओ_first(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_card_driver *drv = to_pnp_card_driver(dev->driver);

	अगर (!dev->card || !drv)
		वापस;
	अगर (drv->हटाओ)
		drv->हटाओ(dev->card_link);
	drv->link.हटाओ = &card_हटाओ;
	kमुक्त(dev->card_link);
	card_हटाओ(dev);
पूर्ण

अटल पूर्णांक card_probe(काष्ठा pnp_card *card, काष्ठा pnp_card_driver *drv)
अणु
	स्थिर काष्ठा pnp_card_device_id *id;
	काष्ठा pnp_card_link *clink;
	काष्ठा pnp_dev *dev;

	अगर (!drv->probe)
		वापस 0;
	id = match_card(drv, card);
	अगर (!id)
		वापस 0;

	clink = pnp_alloc(माप(*clink));
	अगर (!clink)
		वापस 0;
	clink->card = card;
	clink->driver = drv;
	clink->pm_state = PMSG_ON;

	अगर (drv->probe(clink, id) >= 0)
		वापस 1;

	/* Recovery */
	card_क्रम_each_dev(card, dev) अणु
		अगर (dev->card_link == clink)
			pnp_release_card_device(dev);
	पूर्ण
	kमुक्त(clink);
	वापस 0;
पूर्ण

/**
 * pnp_add_card_id - adds an EISA id to the specअगरied card
 * @id: poपूर्णांकer to a pnp_id काष्ठाure
 * @card: poपूर्णांकer to the desired card
 */
अटल काष्ठा pnp_id *pnp_add_card_id(काष्ठा pnp_card *card, अक्षर *id)
अणु
	काष्ठा pnp_id *dev_id, *ptr;

	dev_id = kzalloc(माप(काष्ठा pnp_id), GFP_KERNEL);
	अगर (!dev_id)
		वापस शून्य;

	dev_id->id[0] = id[0];
	dev_id->id[1] = id[1];
	dev_id->id[2] = id[2];
	dev_id->id[3] = छोटे(id[3]);
	dev_id->id[4] = छोटे(id[4]);
	dev_id->id[5] = छोटे(id[5]);
	dev_id->id[6] = छोटे(id[6]);
	dev_id->id[7] = '\0';

	dev_id->next = शून्य;
	ptr = card->id;
	जबतक (ptr && ptr->next)
		ptr = ptr->next;
	अगर (ptr)
		ptr->next = dev_id;
	अन्यथा
		card->id = dev_id;

	वापस dev_id;
पूर्ण

अटल व्योम pnp_मुक्त_card_ids(काष्ठा pnp_card *card)
अणु
	काष्ठा pnp_id *id;
	काष्ठा pnp_id *next;

	id = card->id;
	जबतक (id) अणु
		next = id->next;
		kमुक्त(id);
		id = next;
	पूर्ण
पूर्ण

अटल व्योम pnp_release_card(काष्ठा device *dmdev)
अणु
	काष्ठा pnp_card *card = to_pnp_card(dmdev);

	pnp_मुक्त_card_ids(card);
	kमुक्त(card);
पूर्ण

काष्ठा pnp_card *pnp_alloc_card(काष्ठा pnp_protocol *protocol, पूर्णांक id, अक्षर *pnpid)
अणु
	काष्ठा pnp_card *card;
	काष्ठा pnp_id *dev_id;

	card = kzalloc(माप(काष्ठा pnp_card), GFP_KERNEL);
	अगर (!card)
		वापस शून्य;

	card->protocol = protocol;
	card->number = id;

	card->dev.parent = &card->protocol->dev;
	dev_set_name(&card->dev, "%02x:%02x", card->protocol->number, card->number);

	card->dev.coherent_dma_mask = DMA_BIT_MASK(24);
	card->dev.dma_mask = &card->dev.coherent_dma_mask;

	dev_id = pnp_add_card_id(card, pnpid);
	अगर (!dev_id) अणु
		kमुक्त(card);
		वापस शून्य;
	पूर्ण

	वापस card;
पूर्ण

अटल sमाप_प्रकार pnp_show_card_name(काष्ठा device *dmdev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अक्षर *str = buf;
	काष्ठा pnp_card *card = to_pnp_card(dmdev);

	str += प्र_लिखो(str, "%s\n", card->name);
	वापस (str - buf);
पूर्ण

अटल DEVICE_ATTR(name, S_IRUGO, pnp_show_card_name, शून्य);

अटल sमाप_प्रकार pnp_show_card_ids(काष्ठा device *dmdev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अक्षर *str = buf;
	काष्ठा pnp_card *card = to_pnp_card(dmdev);
	काष्ठा pnp_id *pos = card->id;

	जबतक (pos) अणु
		str += प्र_लिखो(str, "%s\n", pos->id);
		pos = pos->next;
	पूर्ण
	वापस (str - buf);
पूर्ण

अटल DEVICE_ATTR(card_id, S_IRUGO, pnp_show_card_ids, शून्य);

अटल पूर्णांक pnp_पूर्णांकerface_attach_card(काष्ठा pnp_card *card)
अणु
	पूर्णांक rc = device_create_file(&card->dev, &dev_attr_name);

	अगर (rc)
		वापस rc;

	rc = device_create_file(&card->dev, &dev_attr_card_id);
	अगर (rc)
		जाओ err_name;

	वापस 0;

err_name:
	device_हटाओ_file(&card->dev, &dev_attr_name);
	वापस rc;
पूर्ण

/**
 * pnp_add_card - adds a PnP card to the PnP Layer
 * @card: poपूर्णांकer to the card to add
 */
पूर्णांक pnp_add_card(काष्ठा pnp_card *card)
अणु
	पूर्णांक error;
	काष्ठा list_head *pos, *temp;

	card->dev.bus = शून्य;
	card->dev.release = &pnp_release_card;
	error = device_रेजिस्टर(&card->dev);
	अगर (error) अणु
		dev_err(&card->dev, "could not register (err=%d)\n", error);
		put_device(&card->dev);
		वापस error;
	पूर्ण

	pnp_पूर्णांकerface_attach_card(card);
	mutex_lock(&pnp_lock);
	list_add_tail(&card->global_list, &pnp_cards);
	list_add_tail(&card->protocol_list, &card->protocol->cards);
	mutex_unlock(&pnp_lock);

	/* we रुको until now to add devices in order to ensure the drivers
	 * will be able to use all of the related devices on the card
	 * without रुकोing an unreasonable length of समय */
	list_क्रम_each(pos, &card->devices) अणु
		काष्ठा pnp_dev *dev = card_to_pnp_dev(pos);
		__pnp_add_device(dev);
	पूर्ण

	/* match with card drivers */
	list_क्रम_each_safe(pos, temp, &pnp_card_drivers) अणु
		काष्ठा pnp_card_driver *drv =
		    list_entry(pos, काष्ठा pnp_card_driver,
			       global_list);
		card_probe(card, drv);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pnp_हटाओ_card - हटाओs a PnP card from the PnP Layer
 * @card: poपूर्णांकer to the card to हटाओ
 */
व्योम pnp_हटाओ_card(काष्ठा pnp_card *card)
अणु
	काष्ठा list_head *pos, *temp;

	device_unरेजिस्टर(&card->dev);
	mutex_lock(&pnp_lock);
	list_del(&card->global_list);
	list_del(&card->protocol_list);
	mutex_unlock(&pnp_lock);
	list_क्रम_each_safe(pos, temp, &card->devices) अणु
		काष्ठा pnp_dev *dev = card_to_pnp_dev(pos);
		pnp_हटाओ_card_device(dev);
	पूर्ण
पूर्ण

/**
 * pnp_add_card_device - adds a device to the specअगरied card
 * @card: poपूर्णांकer to the card to add to
 * @dev: poपूर्णांकer to the device to add
 */
पूर्णांक pnp_add_card_device(काष्ठा pnp_card *card, काष्ठा pnp_dev *dev)
अणु
	dev->dev.parent = &card->dev;
	dev->card_link = शून्य;
	dev_set_name(&dev->dev, "%02x:%02x.%02x",
		     dev->protocol->number, card->number, dev->number);
	mutex_lock(&pnp_lock);
	dev->card = card;
	list_add_tail(&dev->card_list, &card->devices);
	mutex_unlock(&pnp_lock);
	वापस 0;
पूर्ण

/**
 * pnp_हटाओ_card_device- हटाओs a device from the specअगरied card
 * @dev: poपूर्णांकer to the device to हटाओ
 */
व्योम pnp_हटाओ_card_device(काष्ठा pnp_dev *dev)
अणु
	mutex_lock(&pnp_lock);
	dev->card = शून्य;
	list_del(&dev->card_list);
	mutex_unlock(&pnp_lock);
	__pnp_हटाओ_device(dev);
पूर्ण

/**
 * pnp_request_card_device - Searches क्रम a PnP device under the specअगरied card
 * @clink: poपूर्णांकer to the card link, cannot be शून्य
 * @id: poपूर्णांकer to a PnP ID काष्ठाure that explains the rules क्रम finding the device
 * @from: Starting place to search from. If शून्य it will start from the beginning.
 */
काष्ठा pnp_dev *pnp_request_card_device(काष्ठा pnp_card_link *clink,
					स्थिर अक्षर *id, काष्ठा pnp_dev *from)
अणु
	काष्ठा list_head *pos;
	काष्ठा pnp_dev *dev;
	काष्ठा pnp_card_driver *drv;
	काष्ठा pnp_card *card;

	अगर (!clink || !id)
		वापस शून्य;

	card = clink->card;
	drv = clink->driver;
	अगर (!from) अणु
		pos = card->devices.next;
	पूर्ण अन्यथा अणु
		अगर (from->card != card)
			वापस शून्य;
		pos = from->card_list.next;
	पूर्ण
	जबतक (pos != &card->devices) अणु
		dev = card_to_pnp_dev(pos);
		अगर ((!dev->card_link) && compare_pnp_id(dev->id, id))
			जाओ found;
		pos = pos->next;
	पूर्ण

	वापस शून्य;

found:
	dev->card_link = clink;
	dev->dev.driver = &drv->link.driver;
	अगर (pnp_bus_type.probe(&dev->dev))
		जाओ err_out;
	अगर (device_bind_driver(&dev->dev))
		जाओ err_out;

	वापस dev;

err_out:
	dev->dev.driver = शून्य;
	dev->card_link = शून्य;
	वापस शून्य;
पूर्ण

/**
 * pnp_release_card_device - call this when the driver no दीर्घer needs the device
 * @dev: poपूर्णांकer to the PnP device काष्ठाure
 */
व्योम pnp_release_card_device(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_card_driver *drv = dev->card_link->driver;

	drv->link.हटाओ = &card_हटाओ;
	device_release_driver(&dev->dev);
	drv->link.हटाओ = &card_हटाओ_first;
पूर्ण

/*
 * suspend/resume callbacks
 */
अटल पूर्णांक card_suspend(काष्ठा pnp_dev *dev, pm_message_t state)
अणु
	काष्ठा pnp_card_link *link = dev->card_link;

	अगर (link->pm_state.event == state.event)
		वापस 0;
	link->pm_state = state;
	वापस link->driver->suspend(link, state);
पूर्ण

अटल पूर्णांक card_resume(काष्ठा pnp_dev *dev)
अणु
	काष्ठा pnp_card_link *link = dev->card_link;

	अगर (link->pm_state.event == PM_EVENT_ON)
		वापस 0;
	link->pm_state = PMSG_ON;
	link->driver->resume(link);
	वापस 0;
पूर्ण

/**
 * pnp_रेजिस्टर_card_driver - रेजिस्टरs a PnP card driver with the PnP Layer
 * @drv: poपूर्णांकer to the driver to रेजिस्टर
 */
पूर्णांक pnp_रेजिस्टर_card_driver(काष्ठा pnp_card_driver *drv)
अणु
	पूर्णांक error;
	काष्ठा list_head *pos, *temp;

	drv->link.name = drv->name;
	drv->link.id_table = शून्य;	/* this will disable स्वतः matching */
	drv->link.flags = drv->flags;
	drv->link.probe = शून्य;
	drv->link.हटाओ = &card_हटाओ_first;
	drv->link.suspend = drv->suspend ? card_suspend : शून्य;
	drv->link.resume = drv->resume ? card_resume : शून्य;

	error = pnp_रेजिस्टर_driver(&drv->link);
	अगर (error < 0)
		वापस error;

	mutex_lock(&pnp_lock);
	list_add_tail(&drv->global_list, &pnp_card_drivers);
	mutex_unlock(&pnp_lock);

	list_क्रम_each_safe(pos, temp, &pnp_cards) अणु
		काष्ठा pnp_card *card =
		    list_entry(pos, काष्ठा pnp_card, global_list);
		card_probe(card, drv);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pnp_unरेजिस्टर_card_driver - unरेजिस्टरs a PnP card driver from the PnP Layer
 * @drv: poपूर्णांकer to the driver to unरेजिस्टर
 */
व्योम pnp_unरेजिस्टर_card_driver(काष्ठा pnp_card_driver *drv)
अणु
	mutex_lock(&pnp_lock);
	list_del(&drv->global_list);
	mutex_unlock(&pnp_lock);
	pnp_unरेजिस्टर_driver(&drv->link);
पूर्ण

EXPORT_SYMBOL(pnp_request_card_device);
EXPORT_SYMBOL(pnp_release_card_device);
EXPORT_SYMBOL(pnp_रेजिस्टर_card_driver);
EXPORT_SYMBOL(pnp_unरेजिस्टर_card_driver);
