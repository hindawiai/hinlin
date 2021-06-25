<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Red Hat, Inc
 */

#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/libps2.h>
#समावेश <linux/i2c.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश "psmouse.h"

काष्ठा psmouse_smbus_dev अणु
	काष्ठा i2c_board_info board;
	काष्ठा psmouse *psmouse;
	काष्ठा i2c_client *client;
	काष्ठा list_head node;
	bool dead;
	bool need_deactivate;
पूर्ण;

अटल LIST_HEAD(psmouse_smbus_list);
अटल DEFINE_MUTEX(psmouse_smbus_mutex);

अटल व्योम psmouse_smbus_check_adapter(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा psmouse_smbus_dev *smbdev;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_HOST_NOTIFY))
		वापस;

	mutex_lock(&psmouse_smbus_mutex);

	list_क्रम_each_entry(smbdev, &psmouse_smbus_list, node) अणु
		अगर (smbdev->dead)
			जारी;

		अगर (smbdev->client)
			जारी;

		/*
		 * Here would be a good place to check अगर device is actually
		 * present, but it seems that SMBus will not respond unless we
		 * fully reset PS/2 connection.  So cross our fingers, and try
		 * to चयन over, hopefully our प्रणाली will not have too many
		 * "host notify" I2C adapters.
		 */
		psmouse_dbg(smbdev->psmouse,
			    "SMBus candidate adapter appeared, triggering rescan\n");
		serio_rescan(smbdev->psmouse->ps2dev.serio);
	पूर्ण

	mutex_unlock(&psmouse_smbus_mutex);
पूर्ण

अटल व्योम psmouse_smbus_detach_i2c_client(काष्ठा i2c_client *client)
अणु
	काष्ठा psmouse_smbus_dev *smbdev, *पंचांगp;

	mutex_lock(&psmouse_smbus_mutex);

	list_क्रम_each_entry_safe(smbdev, पंचांगp, &psmouse_smbus_list, node) अणु
		अगर (smbdev->client != client)
			जारी;

		kमुक्त(client->dev.platक्रमm_data);
		client->dev.platक्रमm_data = शून्य;

		अगर (!smbdev->dead) अणु
			psmouse_dbg(smbdev->psmouse,
				    "Marking SMBus companion %s as gone\n",
				    dev_name(&smbdev->client->dev));
			smbdev->dead = true;
			serio_rescan(smbdev->psmouse->ps2dev.serio);
		पूर्ण अन्यथा अणु
			list_del(&smbdev->node);
			kमुक्त(smbdev);
		पूर्ण
	पूर्ण

	mutex_unlock(&psmouse_smbus_mutex);
पूर्ण

अटल पूर्णांक psmouse_smbus_notअगरier_call(काष्ठा notअगरier_block *nb,
				       अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		अगर (dev->type == &i2c_adapter_type)
			psmouse_smbus_check_adapter(to_i2c_adapter(dev));
		अवरोध;

	हाल BUS_NOTIFY_REMOVED_DEVICE:
		अगर (dev->type == &i2c_client_type)
			psmouse_smbus_detach_i2c_client(to_i2c_client(dev));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block psmouse_smbus_notअगरier = अणु
	.notअगरier_call = psmouse_smbus_notअगरier_call,
पूर्ण;

अटल psmouse_ret_t psmouse_smbus_process_byte(काष्ठा psmouse *psmouse)
अणु
	वापस PSMOUSE_FULL_PACKET;
पूर्ण

अटल पूर्णांक psmouse_smbus_reconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा psmouse_smbus_dev *smbdev = psmouse->निजी;

	अगर (smbdev->need_deactivate)
		psmouse_deactivate(psmouse);

	वापस 0;
पूर्ण

काष्ठा psmouse_smbus_removal_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा i2c_client *client;
पूर्ण;

अटल व्योम psmouse_smbus_हटाओ_i2c_device(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा psmouse_smbus_removal_work *rwork =
		container_of(work, काष्ठा psmouse_smbus_removal_work, work);

	dev_dbg(&rwork->client->dev, "destroying SMBus companion device\n");
	i2c_unरेजिस्टर_device(rwork->client);

	kमुक्त(rwork);
पूर्ण

/*
 * This schedules removal of SMBus companion device. We have to करो
 * it in a separate tपढ़ो to aव्योम deadlocking on psmouse_mutex in
 * हाल the device has a trackstick (which is also driven by psmouse).
 *
 * Note that this may be racing with i2c adapter removal, but we
 * can't करो anything about that: i2c स्वतःmatically destroys clients
 * attached to an adapter that is being हटाओd. This has to be
 * fixed in i2c core.
 */
अटल व्योम psmouse_smbus_schedule_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा psmouse_smbus_removal_work *rwork;

	rwork = kzalloc(माप(*rwork), GFP_KERNEL);
	अगर (rwork) अणु
		INIT_WORK(&rwork->work, psmouse_smbus_हटाओ_i2c_device);
		rwork->client = client;

		schedule_work(&rwork->work);
	पूर्ण
पूर्ण

अटल व्योम psmouse_smbus_disconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा psmouse_smbus_dev *smbdev = psmouse->निजी;

	mutex_lock(&psmouse_smbus_mutex);

	अगर (smbdev->dead) अणु
		list_del(&smbdev->node);
		kमुक्त(smbdev);
	पूर्ण अन्यथा अणु
		smbdev->dead = true;
		psmouse_dbg(smbdev->psmouse,
			    "posting removal request for SMBus companion %s\n",
			    dev_name(&smbdev->client->dev));
		psmouse_smbus_schedule_हटाओ(smbdev->client);
	पूर्ण

	mutex_unlock(&psmouse_smbus_mutex);

	psmouse->निजी = शून्य;
पूर्ण

अटल पूर्णांक psmouse_smbus_create_companion(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा psmouse_smbus_dev *smbdev = data;
	अचिन्हित लघु addr_list[] = अणु smbdev->board.addr, I2C_CLIENT_END पूर्ण;
	काष्ठा i2c_adapter *adapter;
	काष्ठा i2c_client *client;

	adapter = i2c_verअगरy_adapter(dev);
	अगर (!adapter)
		वापस 0;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_HOST_NOTIFY))
		वापस 0;

	client = i2c_new_scanned_device(adapter, &smbdev->board,
					addr_list, शून्य);
	अगर (IS_ERR(client))
		वापस 0;

	/* We have our(?) device, stop iterating i2c bus. */
	smbdev->client = client;
	वापस 1;
पूर्ण

व्योम psmouse_smbus_cleanup(काष्ठा psmouse *psmouse)
अणु
	काष्ठा psmouse_smbus_dev *smbdev, *पंचांगp;

	mutex_lock(&psmouse_smbus_mutex);

	list_क्रम_each_entry_safe(smbdev, पंचांगp, &psmouse_smbus_list, node) अणु
		अगर (psmouse == smbdev->psmouse) अणु
			list_del(&smbdev->node);
			kमुक्त(smbdev);
		पूर्ण
	पूर्ण

	mutex_unlock(&psmouse_smbus_mutex);
पूर्ण

पूर्णांक psmouse_smbus_init(काष्ठा psmouse *psmouse,
		       स्थिर काष्ठा i2c_board_info *board,
		       स्थिर व्योम *pdata, माप_प्रकार pdata_size,
		       bool need_deactivate,
		       bool leave_bपढ़ोcrumbs)
अणु
	काष्ठा psmouse_smbus_dev *smbdev;
	पूर्णांक error;

	smbdev = kzalloc(माप(*smbdev), GFP_KERNEL);
	अगर (!smbdev)
		वापस -ENOMEM;

	smbdev->psmouse = psmouse;
	smbdev->board = *board;
	smbdev->need_deactivate = need_deactivate;

	अगर (pdata) अणु
		smbdev->board.platक्रमm_data = kmemdup(pdata, pdata_size,
						      GFP_KERNEL);
		अगर (!smbdev->board.platक्रमm_data) अणु
			kमुक्त(smbdev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (need_deactivate)
		psmouse_deactivate(psmouse);

	psmouse->निजी = smbdev;
	psmouse->protocol_handler = psmouse_smbus_process_byte;
	psmouse->reconnect = psmouse_smbus_reconnect;
	psmouse->fast_reconnect = psmouse_smbus_reconnect;
	psmouse->disconnect = psmouse_smbus_disconnect;
	psmouse->resync_समय = 0;

	mutex_lock(&psmouse_smbus_mutex);
	list_add_tail(&smbdev->node, &psmouse_smbus_list);
	mutex_unlock(&psmouse_smbus_mutex);

	/* Bind to alपढ़ोy existing adapters right away */
	error = i2c_क्रम_each_dev(smbdev, psmouse_smbus_create_companion);

	अगर (smbdev->client) अणु
		/* We have our companion device */
		वापस 0;
	पूर्ण

	/*
	 * If we did not create i2c device we will not need platक्रमm
	 * data even अगर we are leaving bपढ़ोcrumbs.
	 */
	kमुक्त(smbdev->board.platक्रमm_data);
	smbdev->board.platक्रमm_data = शून्य;

	अगर (error < 0 || !leave_bपढ़ोcrumbs) अणु
		mutex_lock(&psmouse_smbus_mutex);
		list_del(&smbdev->node);
		mutex_unlock(&psmouse_smbus_mutex);

		kमुक्त(smbdev);
	पूर्ण

	वापस error < 0 ? error : -EAGAIN;
पूर्ण

पूर्णांक __init psmouse_smbus_module_init(व्योम)
अणु
	पूर्णांक error;

	error = bus_रेजिस्टर_notअगरier(&i2c_bus_type, &psmouse_smbus_notअगरier);
	अगर (error) अणु
		pr_err("failed to register i2c bus notifier: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

व्योम psmouse_smbus_module_निकास(व्योम)
अणु
	bus_unरेजिस्टर_notअगरier(&i2c_bus_type, &psmouse_smbus_notअगरier);
	flush_scheduled_work();
पूर्ण
