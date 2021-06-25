<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012-2019, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>

#समावेश <linux/mei.h>

#समावेश "mei_dev.h"
#समावेश "hbm.h"
#समावेश "client.h"

स्थिर अक्षर *mei_dev_state_str(पूर्णांक state)
अणु
#घोषणा MEI_DEV_STATE(state) हाल MEI_DEV_##state: वापस #state
	चयन (state) अणु
	MEI_DEV_STATE(INITIALIZING);
	MEI_DEV_STATE(INIT_CLIENTS);
	MEI_DEV_STATE(ENABLED);
	MEI_DEV_STATE(RESETTING);
	MEI_DEV_STATE(DISABLED);
	MEI_DEV_STATE(POWER_DOWN);
	MEI_DEV_STATE(POWER_UP);
	शेष:
		वापस "unknown";
	पूर्ण
#अघोषित MEI_DEV_STATE
पूर्ण

स्थिर अक्षर *mei_pg_state_str(क्रमागत mei_pg_state state)
अणु
#घोषणा MEI_PG_STATE(state) हाल MEI_PG_##state: वापस #state
	चयन (state) अणु
	MEI_PG_STATE(OFF);
	MEI_PG_STATE(ON);
	शेष:
		वापस "unknown";
	पूर्ण
#अघोषित MEI_PG_STATE
पूर्ण

/**
 * mei_fw_status2str - convert fw status रेजिस्टरs to prपूर्णांकable string
 *
 * @fw_status:  firmware status
 * @buf: string buffer at minimal size MEI_FW_STATUS_STR_SZ
 * @len: buffer len must be >= MEI_FW_STATUS_STR_SZ
 *
 * Return: number of bytes written or -EINVAL अगर buffer is to small
 */
sमाप_प्रकार mei_fw_status2str(काष्ठा mei_fw_status *fw_status,
			  अक्षर *buf, माप_प्रकार len)
अणु
	sमाप_प्रकार cnt = 0;
	पूर्णांक i;

	buf[0] = '\0';

	अगर (len < MEI_FW_STATUS_STR_SZ)
		वापस -EINVAL;

	क्रम (i = 0; i < fw_status->count; i++)
		cnt += scnम_लिखो(buf + cnt, len - cnt, "%08X ",
				fw_status->status[i]);

	/* drop last space */
	buf[cnt] = '\0';
	वापस cnt;
पूर्ण
EXPORT_SYMBOL_GPL(mei_fw_status2str);

/**
 * mei_cancel_work - Cancel mei background jobs
 *
 * @dev: the device काष्ठाure
 */
व्योम mei_cancel_work(काष्ठा mei_device *dev)
अणु
	cancel_work_sync(&dev->reset_work);
	cancel_work_sync(&dev->bus_rescan_work);

	cancel_delayed_work_sync(&dev->समयr_work);
पूर्ण
EXPORT_SYMBOL_GPL(mei_cancel_work);

/**
 * mei_reset - resets host and fw.
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success or < 0 अगर the reset hasn't succeeded
 */
पूर्णांक mei_reset(काष्ठा mei_device *dev)
अणु
	क्रमागत mei_dev_state state = dev->dev_state;
	bool पूर्णांकerrupts_enabled;
	पूर्णांक ret;

	अगर (state != MEI_DEV_INITIALIZING &&
	    state != MEI_DEV_DISABLED &&
	    state != MEI_DEV_POWER_DOWN &&
	    state != MEI_DEV_POWER_UP) अणु
		अक्षर fw_sts_str[MEI_FW_STATUS_STR_SZ];

		mei_fw_status_str(dev, fw_sts_str, MEI_FW_STATUS_STR_SZ);
		dev_warn(dev->dev, "unexpected reset: dev_state = %s fw status = %s\n",
			 mei_dev_state_str(state), fw_sts_str);
	पूर्ण

	mei_clear_पूर्णांकerrupts(dev);

	/* we're alपढ़ोy in reset, cancel the init समयr
	 * अगर the reset was called due the hbm protocol error
	 * we need to call it beक्रमe hw start
	 * so the hbm watchकरोg won't kick in
	 */
	mei_hbm_idle(dev);

	/* enter reset flow */
	पूर्णांकerrupts_enabled = state != MEI_DEV_POWER_DOWN;
	mei_set_devstate(dev, MEI_DEV_RESETTING);

	dev->reset_count++;
	अगर (dev->reset_count > MEI_MAX_CONSEC_RESET) अणु
		dev_err(dev->dev, "reset: reached maximal consecutive resets: disabling the device\n");
		mei_set_devstate(dev, MEI_DEV_DISABLED);
		वापस -ENODEV;
	पूर्ण

	ret = mei_hw_reset(dev, पूर्णांकerrupts_enabled);
	/* fall through and हटाओ the sw state even अगर hw reset has failed */

	/* no need to clean up software state in हाल of घातer up */
	अगर (state != MEI_DEV_INITIALIZING && state != MEI_DEV_POWER_UP)
		mei_cl_all_disconnect(dev);

	mei_hbm_reset(dev);

	स_रखो(dev->rd_msg_hdr, 0, माप(dev->rd_msg_hdr));

	अगर (ret) अणु
		dev_err(dev->dev, "hw_reset failed ret = %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (state == MEI_DEV_POWER_DOWN) अणु
		dev_dbg(dev->dev, "powering down: end of reset\n");
		mei_set_devstate(dev, MEI_DEV_DISABLED);
		वापस 0;
	पूर्ण

	ret = mei_hw_start(dev);
	अगर (ret) अणु
		dev_err(dev->dev, "hw_start failed ret = %d\n", ret);
		वापस ret;
	पूर्ण

	dev_dbg(dev->dev, "link is established start sending messages.\n");

	mei_set_devstate(dev, MEI_DEV_INIT_CLIENTS);
	ret = mei_hbm_start_req(dev);
	अगर (ret) अणु
		dev_err(dev->dev, "hbm_start failed ret = %d\n", ret);
		mei_set_devstate(dev, MEI_DEV_RESETTING);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mei_reset);

/**
 * mei_start - initializes host and fw to start work.
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success, <0 on failure.
 */
पूर्णांक mei_start(काष्ठा mei_device *dev)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->device_lock);

	/* acknowledge पूर्णांकerrupt and stop पूर्णांकerrupts */
	mei_clear_पूर्णांकerrupts(dev);

	ret = mei_hw_config(dev);
	अगर (ret)
		जाओ err;

	dev_dbg(dev->dev, "reset in start the mei device.\n");

	dev->reset_count = 0;
	करो अणु
		mei_set_devstate(dev, MEI_DEV_INITIALIZING);
		ret = mei_reset(dev);

		अगर (ret == -ENODEV || dev->dev_state == MEI_DEV_DISABLED) अणु
			dev_err(dev->dev, "reset failed ret = %d", ret);
			जाओ err;
		पूर्ण
	पूर्ण जबतक (ret);

	अगर (mei_hbm_start_रुको(dev)) अणु
		dev_err(dev->dev, "HBM haven't started");
		जाओ err;
	पूर्ण

	अगर (!mei_host_is_पढ़ोy(dev)) अणु
		dev_err(dev->dev, "host is not ready.\n");
		जाओ err;
	पूर्ण

	अगर (!mei_hw_is_पढ़ोy(dev)) अणु
		dev_err(dev->dev, "ME is not ready.\n");
		जाओ err;
	पूर्ण

	अगर (!mei_hbm_version_is_supported(dev)) अणु
		dev_dbg(dev->dev, "MEI start failed.\n");
		जाओ err;
	पूर्ण

	dev_dbg(dev->dev, "link layer has been established.\n");

	mutex_unlock(&dev->device_lock);
	वापस 0;
err:
	dev_err(dev->dev, "link layer initialization failed.\n");
	mei_set_devstate(dev, MEI_DEV_DISABLED);
	mutex_unlock(&dev->device_lock);
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(mei_start);

/**
 * mei_restart - restart device after suspend
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success or -ENODEV अगर the restart hasn't succeeded
 */
पूर्णांक mei_restart(काष्ठा mei_device *dev)
अणु
	पूर्णांक err;

	mutex_lock(&dev->device_lock);

	mei_set_devstate(dev, MEI_DEV_POWER_UP);
	dev->reset_count = 0;

	err = mei_reset(dev);

	mutex_unlock(&dev->device_lock);

	अगर (err == -ENODEV || dev->dev_state == MEI_DEV_DISABLED) अणु
		dev_err(dev->dev, "device disabled = %d\n", err);
		वापस -ENODEV;
	पूर्ण

	/* try to start again */
	अगर (err)
		schedule_work(&dev->reset_work);


	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mei_restart);

अटल व्योम mei_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mei_device *dev =
		container_of(work, काष्ठा mei_device,  reset_work);
	पूर्णांक ret;

	mei_clear_पूर्णांकerrupts(dev);
	mei_synchronize_irq(dev);

	mutex_lock(&dev->device_lock);

	ret = mei_reset(dev);

	mutex_unlock(&dev->device_lock);

	अगर (dev->dev_state == MEI_DEV_DISABLED) अणु
		dev_err(dev->dev, "device disabled = %d\n", ret);
		वापस;
	पूर्ण

	/* retry reset in हाल of failure */
	अगर (ret)
		schedule_work(&dev->reset_work);
पूर्ण

व्योम mei_stop(काष्ठा mei_device *dev)
अणु
	dev_dbg(dev->dev, "stopping the device.\n");

	mutex_lock(&dev->device_lock);
	mei_set_devstate(dev, MEI_DEV_POWERING_DOWN);
	mutex_unlock(&dev->device_lock);
	mei_cl_bus_हटाओ_devices(dev);
	mutex_lock(&dev->device_lock);
	mei_set_devstate(dev, MEI_DEV_POWER_DOWN);
	mutex_unlock(&dev->device_lock);

	mei_cancel_work(dev);

	mei_clear_पूर्णांकerrupts(dev);
	mei_synchronize_irq(dev);

	mutex_lock(&dev->device_lock);

	mei_reset(dev);
	/* move device to disabled state unconditionally */
	mei_set_devstate(dev, MEI_DEV_DISABLED);

	mutex_unlock(&dev->device_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mei_stop);

/**
 * mei_ग_लिखो_is_idle - check अगर the ग_लिखो queues are idle
 *
 * @dev: the device काष्ठाure
 *
 * Return: true of there is no pending ग_लिखो
 */
bool mei_ग_लिखो_is_idle(काष्ठा mei_device *dev)
अणु
	bool idle = (dev->dev_state == MEI_DEV_ENABLED &&
		list_empty(&dev->ctrl_wr_list) &&
		list_empty(&dev->ग_लिखो_list)   &&
		list_empty(&dev->ग_लिखो_रुकोing_list));

	dev_dbg(dev->dev, "write pg: is idle[%d] state=%s ctrl=%01d write=%01d wwait=%01d\n",
		idle,
		mei_dev_state_str(dev->dev_state),
		list_empty(&dev->ctrl_wr_list),
		list_empty(&dev->ग_लिखो_list),
		list_empty(&dev->ग_लिखो_रुकोing_list));

	वापस idle;
पूर्ण
EXPORT_SYMBOL_GPL(mei_ग_लिखो_is_idle);

/**
 * mei_device_init  -- initialize mei_device काष्ठाure
 *
 * @dev: the mei device
 * @device: the device काष्ठाure
 * @hw_ops: hw operations
 */
व्योम mei_device_init(काष्ठा mei_device *dev,
		     काष्ठा device *device,
		     स्थिर काष्ठा mei_hw_ops *hw_ops)
अणु
	/* setup our list array */
	INIT_LIST_HEAD(&dev->file_list);
	INIT_LIST_HEAD(&dev->device_list);
	INIT_LIST_HEAD(&dev->me_clients);
	mutex_init(&dev->device_lock);
	init_rwsem(&dev->me_clients_rwsem);
	mutex_init(&dev->cl_bus_lock);
	init_रुकोqueue_head(&dev->रुको_hw_पढ़ोy);
	init_रुकोqueue_head(&dev->रुको_pg);
	init_रुकोqueue_head(&dev->रुको_hbm_start);
	dev->dev_state = MEI_DEV_INITIALIZING;
	dev->reset_count = 0;

	INIT_LIST_HEAD(&dev->ग_लिखो_list);
	INIT_LIST_HEAD(&dev->ग_लिखो_रुकोing_list);
	INIT_LIST_HEAD(&dev->ctrl_wr_list);
	INIT_LIST_HEAD(&dev->ctrl_rd_list);
	dev->tx_queue_limit = MEI_TX_QUEUE_LIMIT_DEFAULT;

	INIT_DELAYED_WORK(&dev->समयr_work, mei_समयr);
	INIT_WORK(&dev->reset_work, mei_reset_work);
	INIT_WORK(&dev->bus_rescan_work, mei_cl_bus_rescan_work);

	biपंचांगap_zero(dev->host_clients_map, MEI_CLIENTS_MAX);
	dev->खोलो_handle_count = 0;

	/*
	 * Reserving the first client ID
	 * 0: Reserved क्रम MEI Bus Message communications
	 */
	biपंचांगap_set(dev->host_clients_map, 0, 1);

	dev->pg_event = MEI_PG_EVENT_IDLE;
	dev->ops      = hw_ops;
	dev->dev      = device;
पूर्ण
EXPORT_SYMBOL_GPL(mei_device_init);

