<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Initialization protocol क्रम ISHTP driver
 *
 * Copyright (c) 2003-2016, Intel Corporation.
 */

#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश "ishtp-dev.h"
#समावेश "hbm.h"
#समावेश "client.h"

/**
 * ishtp_dev_state_str() -Convert to string क्रमmat
 * @state: state to convert
 *
 * Convert state to string क्रम prपूर्णांकs
 *
 * Return: अक्षरacter poपूर्णांकer to converted string
 */
स्थिर अक्षर *ishtp_dev_state_str(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल ISHTP_DEV_INITIALIZING:
		वापस	"INITIALIZING";
	हाल ISHTP_DEV_INIT_CLIENTS:
		वापस	"INIT_CLIENTS";
	हाल ISHTP_DEV_ENABLED:
		वापस	"ENABLED";
	हाल ISHTP_DEV_RESETTING:
		वापस	"RESETTING";
	हाल ISHTP_DEV_DISABLED:
		वापस	"DISABLED";
	हाल ISHTP_DEV_POWER_DOWN:
		वापस	"POWER_DOWN";
	हाल ISHTP_DEV_POWER_UP:
		वापस	"POWER_UP";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

/**
 * ishtp_device_init() - ishtp device init
 * @dev: ISHTP device instance
 *
 * After ISHTP device is alloacted, this function is used to initialize
 * each field which includes spin lock, work काष्ठा and lists
 */
व्योम ishtp_device_init(काष्ठा ishtp_device *dev)
अणु
	dev->dev_state = ISHTP_DEV_INITIALIZING;
	INIT_LIST_HEAD(&dev->cl_list);
	INIT_LIST_HEAD(&dev->device_list);
	dev->rd_msg_fअगरo_head = 0;
	dev->rd_msg_fअगरo_tail = 0;
	spin_lock_init(&dev->rd_msg_spinlock);

	init_रुकोqueue_head(&dev->रुको_hbm_recvd_msg);
	spin_lock_init(&dev->पढ़ो_list_spinlock);
	spin_lock_init(&dev->device_lock);
	spin_lock_init(&dev->device_list_lock);
	spin_lock_init(&dev->cl_list_lock);
	spin_lock_init(&dev->fw_clients_lock);
	INIT_WORK(&dev->bh_hbm_work, bh_hbm_work_fn);

	biपंचांगap_zero(dev->host_clients_map, ISHTP_CLIENTS_MAX);
	dev->खोलो_handle_count = 0;

	/*
	 * Reserving client ID 0 क्रम ISHTP Bus Message communications
	 */
	biपंचांगap_set(dev->host_clients_map, 0, 1);

	INIT_LIST_HEAD(&dev->पढ़ो_list.list);

पूर्ण
EXPORT_SYMBOL(ishtp_device_init);

/**
 * ishtp_start() - Start ISH processing
 * @dev: ISHTP device instance
 *
 * Start ISHTP processing by sending query subscriber message
 *
 * Return: 0 on success अन्यथा -ENODEV
 */
पूर्णांक ishtp_start(काष्ठा ishtp_device *dev)
अणु
	अगर (ishtp_hbm_start_रुको(dev)) अणु
		dev_err(dev->devc, "HBM haven't started");
		जाओ err;
	पूर्ण

	/* suspend & resume notअगरication - send QUERY_SUBSCRIBERS msg */
	ishtp_query_subscribers(dev);

	वापस 0;
err:
	dev_err(dev->devc, "link layer initialization failed.\n");
	dev->dev_state = ISHTP_DEV_DISABLED;
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(ishtp_start);
