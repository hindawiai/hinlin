<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Surface Book (gen. 2 and later) detachment प्रणाली (DTX) driver.
 *
 * Provides a user-space पूर्णांकerface to properly handle clipboard/tablet
 * (containing screen and processor) detachment from the base of the device
 * (containing the keyboard and optionally a discrete GPU). Allows to
 * acknowledge (to speed things up), पात (e.g. in हाल the dGPU is still in
 * use), or request detachment via user-space.
 *
 * Copyright (C) 2019-2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/input.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/kref.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/poll.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/surface_aggregator/controller.h>
#समावेश <linux/surface_aggregator/device.h>
#समावेश <linux/surface_aggregator/dtx.h>


/* -- SSAM पूर्णांकerface. ------------------------------------------------------- */

क्रमागत sam_event_cid_bas अणु
	SAM_EVENT_CID_DTX_CONNECTION			= 0x0c,
	SAM_EVENT_CID_DTX_REQUEST			= 0x0e,
	SAM_EVENT_CID_DTX_CANCEL			= 0x0f,
	SAM_EVENT_CID_DTX_LATCH_STATUS			= 0x11,
पूर्ण;

क्रमागत ssam_bas_base_state अणु
	SSAM_BAS_BASE_STATE_DETACH_SUCCESS		= 0x00,
	SSAM_BAS_BASE_STATE_ATTACHED			= 0x01,
	SSAM_BAS_BASE_STATE_NOT_FEASIBLE		= 0x02,
पूर्ण;

क्रमागत ssam_bas_latch_status अणु
	SSAM_BAS_LATCH_STATUS_CLOSED			= 0x00,
	SSAM_BAS_LATCH_STATUS_OPENED			= 0x01,
	SSAM_BAS_LATCH_STATUS_FAILED_TO_OPEN		= 0x02,
	SSAM_BAS_LATCH_STATUS_FAILED_TO_REMAIN_OPEN	= 0x03,
	SSAM_BAS_LATCH_STATUS_FAILED_TO_CLOSE		= 0x04,
पूर्ण;

क्रमागत ssam_bas_cancel_reason अणु
	SSAM_BAS_CANCEL_REASON_NOT_FEASIBLE		= 0x00,  /* Low battery. */
	SSAM_BAS_CANCEL_REASON_TIMEOUT			= 0x02,
	SSAM_BAS_CANCEL_REASON_FAILED_TO_OPEN		= 0x03,
	SSAM_BAS_CANCEL_REASON_FAILED_TO_REMAIN_OPEN	= 0x04,
	SSAM_BAS_CANCEL_REASON_FAILED_TO_CLOSE		= 0x05,
पूर्ण;

काष्ठा ssam_bas_base_info अणु
	u8 state;
	u8 base_id;
पूर्ण __packed;

अटल_निश्चित(माप(काष्ठा ssam_bas_base_info) == 2);

SSAM_DEFINE_SYNC_REQUEST_N(ssam_bas_latch_lock, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x06,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_N(ssam_bas_latch_unlock, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x07,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_N(ssam_bas_latch_request, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x08,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_N(ssam_bas_latch_confirm, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x09,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_N(ssam_bas_latch_heartbeat, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x0a,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_N(ssam_bas_latch_cancel, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x0b,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_R(ssam_bas_get_base, काष्ठा ssam_bas_base_info, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x0c,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_R(ssam_bas_get_device_mode, u8, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x0d,
	.instance_id     = 0x00,
पूर्ण);

SSAM_DEFINE_SYNC_REQUEST_R(ssam_bas_get_latch_status, u8, अणु
	.target_category = SSAM_SSH_TC_BAS,
	.target_id       = 0x01,
	.command_id      = 0x11,
	.instance_id     = 0x00,
पूर्ण);


/* -- Main काष्ठाures. ------------------------------------------------------ */

क्रमागत sdtx_device_state अणु
	SDTX_DEVICE_SHUTDOWN_BIT    = BIT(0),
	SDTX_DEVICE_सूचीTY_BASE_BIT  = BIT(1),
	SDTX_DEVICE_सूचीTY_MODE_BIT  = BIT(2),
	SDTX_DEVICE_सूचीTY_LATCH_BIT = BIT(3),
पूर्ण;

काष्ठा sdtx_device अणु
	काष्ठा kref kref;
	काष्ठा rw_semaphore lock;         /* Guards device and controller reference. */

	काष्ठा device *dev;
	काष्ठा ssam_controller *ctrl;
	अचिन्हित दीर्घ flags;

	काष्ठा miscdevice mdev;
	रुको_queue_head_t रुकोq;
	काष्ठा mutex ग_लिखो_lock;          /* Guards order of events/notअगरications. */
	काष्ठा rw_semaphore client_lock;  /* Guards client list.                   */
	काष्ठा list_head client_list;

	काष्ठा delayed_work state_work;
	काष्ठा अणु
		काष्ठा ssam_bas_base_info base;
		u8 device_mode;
		u8 latch_status;
	पूर्ण state;

	काष्ठा delayed_work mode_work;
	काष्ठा input_dev *mode_चयन;

	काष्ठा ssam_event_notअगरier notअगर;
पूर्ण;

क्रमागत sdtx_client_state अणु
	SDTX_CLIENT_EVENTS_ENABLED_BIT = BIT(0),
पूर्ण;

काष्ठा sdtx_client अणु
	काष्ठा sdtx_device *ddev;
	काष्ठा list_head node;
	अचिन्हित दीर्घ flags;

	काष्ठा fasync_काष्ठा *fasync;

	काष्ठा mutex पढ़ो_lock;           /* Guards FIFO buffer पढ़ो access. */
	DECLARE_KFIFO(buffer, u8, 512);
पूर्ण;

अटल व्योम __sdtx_device_release(काष्ठा kref *kref)
अणु
	काष्ठा sdtx_device *ddev = container_of(kref, काष्ठा sdtx_device, kref);

	mutex_destroy(&ddev->ग_लिखो_lock);
	kमुक्त(ddev);
पूर्ण

अटल काष्ठा sdtx_device *sdtx_device_get(काष्ठा sdtx_device *ddev)
अणु
	अगर (ddev)
		kref_get(&ddev->kref);

	वापस ddev;
पूर्ण

अटल व्योम sdtx_device_put(काष्ठा sdtx_device *ddev)
अणु
	अगर (ddev)
		kref_put(&ddev->kref, __sdtx_device_release);
पूर्ण


/* -- Firmware value translations. ------------------------------------------ */

अटल u16 sdtx_translate_base_state(काष्ठा sdtx_device *ddev, u8 state)
अणु
	चयन (state) अणु
	हाल SSAM_BAS_BASE_STATE_ATTACHED:
		वापस SDTX_BASE_ATTACHED;

	हाल SSAM_BAS_BASE_STATE_DETACH_SUCCESS:
		वापस SDTX_BASE_DETACHED;

	हाल SSAM_BAS_BASE_STATE_NOT_FEASIBLE:
		वापस SDTX_DETACH_NOT_FEASIBLE;

	शेष:
		dev_err(ddev->dev, "unknown base state: %#04x\n", state);
		वापस SDTX_UNKNOWN(state);
	पूर्ण
पूर्ण

अटल u16 sdtx_translate_latch_status(काष्ठा sdtx_device *ddev, u8 status)
अणु
	चयन (status) अणु
	हाल SSAM_BAS_LATCH_STATUS_CLOSED:
		वापस SDTX_LATCH_CLOSED;

	हाल SSAM_BAS_LATCH_STATUS_OPENED:
		वापस SDTX_LATCH_OPENED;

	हाल SSAM_BAS_LATCH_STATUS_FAILED_TO_OPEN:
		वापस SDTX_ERR_FAILED_TO_OPEN;

	हाल SSAM_BAS_LATCH_STATUS_FAILED_TO_REMAIN_OPEN:
		वापस SDTX_ERR_FAILED_TO_REMAIN_OPEN;

	हाल SSAM_BAS_LATCH_STATUS_FAILED_TO_CLOSE:
		वापस SDTX_ERR_FAILED_TO_CLOSE;

	शेष:
		dev_err(ddev->dev, "unknown latch status: %#04x\n", status);
		वापस SDTX_UNKNOWN(status);
	पूर्ण
पूर्ण

अटल u16 sdtx_translate_cancel_reason(काष्ठा sdtx_device *ddev, u8 reason)
अणु
	चयन (reason) अणु
	हाल SSAM_BAS_CANCEL_REASON_NOT_FEASIBLE:
		वापस SDTX_DETACH_NOT_FEASIBLE;

	हाल SSAM_BAS_CANCEL_REASON_TIMEOUT:
		वापस SDTX_DETACH_TIMEDOUT;

	हाल SSAM_BAS_CANCEL_REASON_FAILED_TO_OPEN:
		वापस SDTX_ERR_FAILED_TO_OPEN;

	हाल SSAM_BAS_CANCEL_REASON_FAILED_TO_REMAIN_OPEN:
		वापस SDTX_ERR_FAILED_TO_REMAIN_OPEN;

	हाल SSAM_BAS_CANCEL_REASON_FAILED_TO_CLOSE:
		वापस SDTX_ERR_FAILED_TO_CLOSE;

	शेष:
		dev_err(ddev->dev, "unknown cancel reason: %#04x\n", reason);
		वापस SDTX_UNKNOWN(reason);
	पूर्ण
पूर्ण


/* -- IOCTLs. --------------------------------------------------------------- */

अटल पूर्णांक sdtx_ioctl_get_base_info(काष्ठा sdtx_device *ddev,
				    काष्ठा sdtx_base_info __user *buf)
अणु
	काष्ठा ssam_bas_base_info raw;
	काष्ठा sdtx_base_info info;
	पूर्णांक status;

	lockdep_निश्चित_held_पढ़ो(&ddev->lock);

	status = ssam_retry(ssam_bas_get_base, ddev->ctrl, &raw);
	अगर (status < 0)
		वापस status;

	info.state = sdtx_translate_base_state(ddev, raw.state);
	info.base_id = SDTX_BASE_TYPE_SSH(raw.base_id);

	अगर (copy_to_user(buf, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक sdtx_ioctl_get_device_mode(काष्ठा sdtx_device *ddev, u16 __user *buf)
अणु
	u8 mode;
	पूर्णांक status;

	lockdep_निश्चित_held_पढ़ो(&ddev->lock);

	status = ssam_retry(ssam_bas_get_device_mode, ddev->ctrl, &mode);
	अगर (status < 0)
		वापस status;

	वापस put_user(mode, buf);
पूर्ण

अटल पूर्णांक sdtx_ioctl_get_latch_status(काष्ठा sdtx_device *ddev, u16 __user *buf)
अणु
	u8 latch;
	पूर्णांक status;

	lockdep_निश्चित_held_पढ़ो(&ddev->lock);

	status = ssam_retry(ssam_bas_get_latch_status, ddev->ctrl, &latch);
	अगर (status < 0)
		वापस status;

	वापस put_user(sdtx_translate_latch_status(ddev, latch), buf);
पूर्ण

अटल दीर्घ __surface_dtx_ioctl(काष्ठा sdtx_client *client, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sdtx_device *ddev = client->ddev;

	lockdep_निश्चित_held_पढ़ो(&ddev->lock);

	चयन (cmd) अणु
	हाल SDTX_IOCTL_EVENTS_ENABLE:
		set_bit(SDTX_CLIENT_EVENTS_ENABLED_BIT, &client->flags);
		वापस 0;

	हाल SDTX_IOCTL_EVENTS_DISABLE:
		clear_bit(SDTX_CLIENT_EVENTS_ENABLED_BIT, &client->flags);
		वापस 0;

	हाल SDTX_IOCTL_LATCH_LOCK:
		वापस ssam_retry(ssam_bas_latch_lock, ddev->ctrl);

	हाल SDTX_IOCTL_LATCH_UNLOCK:
		वापस ssam_retry(ssam_bas_latch_unlock, ddev->ctrl);

	हाल SDTX_IOCTL_LATCH_REQUEST:
		वापस ssam_retry(ssam_bas_latch_request, ddev->ctrl);

	हाल SDTX_IOCTL_LATCH_CONFIRM:
		वापस ssam_retry(ssam_bas_latch_confirm, ddev->ctrl);

	हाल SDTX_IOCTL_LATCH_HEARTBEAT:
		वापस ssam_retry(ssam_bas_latch_heartbeat, ddev->ctrl);

	हाल SDTX_IOCTL_LATCH_CANCEL:
		वापस ssam_retry(ssam_bas_latch_cancel, ddev->ctrl);

	हाल SDTX_IOCTL_GET_BASE_INFO:
		वापस sdtx_ioctl_get_base_info(ddev, (काष्ठा sdtx_base_info __user *)arg);

	हाल SDTX_IOCTL_GET_DEVICE_MODE:
		वापस sdtx_ioctl_get_device_mode(ddev, (u16 __user *)arg);

	हाल SDTX_IOCTL_GET_LATCH_STATUS:
		वापस sdtx_ioctl_get_latch_status(ddev, (u16 __user *)arg);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल दीर्घ surface_dtx_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sdtx_client *client = file->निजी_data;
	दीर्घ status;

	अगर (करोwn_पढ़ो_समाप्तable(&client->ddev->lock))
		वापस -ERESTARTSYS;

	अगर (test_bit(SDTX_DEVICE_SHUTDOWN_BIT, &client->ddev->flags)) अणु
		up_पढ़ो(&client->ddev->lock);
		वापस -ENODEV;
	पूर्ण

	status = __surface_dtx_ioctl(client, cmd, arg);

	up_पढ़ो(&client->ddev->lock);
	वापस status;
पूर्ण


/* -- File operations. ------------------------------------------------------ */

अटल पूर्णांक surface_dtx_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sdtx_device *ddev = container_of(file->निजी_data, काष्ठा sdtx_device, mdev);
	काष्ठा sdtx_client *client;

	/* Initialize client. */
	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (!client)
		वापस -ENOMEM;

	client->ddev = sdtx_device_get(ddev);

	INIT_LIST_HEAD(&client->node);

	mutex_init(&client->पढ़ो_lock);
	INIT_KFIFO(client->buffer);

	file->निजी_data = client;

	/* Attach client. */
	करोwn_ग_लिखो(&ddev->client_lock);

	/*
	 * Do not add a new client अगर the device has been shut करोwn. Note that
	 * it's enough to hold the client_lock here as, during shutकरोwn, we
	 * only acquire that lock and हटाओ clients after marking the device
	 * as shut करोwn.
	 */
	अगर (test_bit(SDTX_DEVICE_SHUTDOWN_BIT, &ddev->flags)) अणु
		up_ग_लिखो(&ddev->client_lock);
		mutex_destroy(&client->पढ़ो_lock);
		sdtx_device_put(client->ddev);
		kमुक्त(client);
		वापस -ENODEV;
	पूर्ण

	list_add_tail(&client->node, &ddev->client_list);
	up_ग_लिखो(&ddev->client_lock);

	stream_खोलो(inode, file);
	वापस 0;
पूर्ण

अटल पूर्णांक surface_dtx_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sdtx_client *client = file->निजी_data;

	/* Detach client. */
	करोwn_ग_लिखो(&client->ddev->client_lock);
	list_del(&client->node);
	up_ग_लिखो(&client->ddev->client_lock);

	/* Free client. */
	sdtx_device_put(client->ddev);
	mutex_destroy(&client->पढ़ो_lock);
	kमुक्त(client);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार surface_dtx_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *offs)
अणु
	काष्ठा sdtx_client *client = file->निजी_data;
	काष्ठा sdtx_device *ddev = client->ddev;
	अचिन्हित पूर्णांक copied;
	पूर्णांक status = 0;

	अगर (करोwn_पढ़ो_समाप्तable(&ddev->lock))
		वापस -ERESTARTSYS;

	/* Make sure we're not shut करोwn. */
	अगर (test_bit(SDTX_DEVICE_SHUTDOWN_BIT, &ddev->flags)) अणु
		up_पढ़ो(&ddev->lock);
		वापस -ENODEV;
	पूर्ण

	करो अणु
		/* Check availability, रुको अगर necessary. */
		अगर (kfअगरo_is_empty(&client->buffer)) अणु
			up_पढ़ो(&ddev->lock);

			अगर (file->f_flags & O_NONBLOCK)
				वापस -EAGAIN;

			status = रुको_event_पूर्णांकerruptible(ddev->रुकोq,
							  !kfअगरo_is_empty(&client->buffer) ||
							  test_bit(SDTX_DEVICE_SHUTDOWN_BIT,
								   &ddev->flags));
			अगर (status < 0)
				वापस status;

			अगर (करोwn_पढ़ो_समाप्तable(&ddev->lock))
				वापस -ERESTARTSYS;

			/* Need to check that we're not shut करोwn again. */
			अगर (test_bit(SDTX_DEVICE_SHUTDOWN_BIT, &ddev->flags)) अणु
				up_पढ़ो(&ddev->lock);
				वापस -ENODEV;
			पूर्ण
		पूर्ण

		/* Try to पढ़ो from FIFO. */
		अगर (mutex_lock_पूर्णांकerruptible(&client->पढ़ो_lock)) अणु
			up_पढ़ो(&ddev->lock);
			वापस -ERESTARTSYS;
		पूर्ण

		status = kfअगरo_to_user(&client->buffer, buf, count, &copied);
		mutex_unlock(&client->पढ़ो_lock);

		अगर (status < 0) अणु
			up_पढ़ो(&ddev->lock);
			वापस status;
		पूर्ण

		/* We might not have gotten anything, check this here. */
		अगर (copied == 0 && (file->f_flags & O_NONBLOCK)) अणु
			up_पढ़ो(&ddev->lock);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण जबतक (copied == 0);

	up_पढ़ो(&ddev->lock);
	वापस copied;
पूर्ण

अटल __poll_t surface_dtx_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *pt)
अणु
	काष्ठा sdtx_client *client = file->निजी_data;
	__poll_t events = 0;

	अगर (test_bit(SDTX_DEVICE_SHUTDOWN_BIT, &client->ddev->flags))
		वापस EPOLLHUP | EPOLLERR;

	poll_रुको(file, &client->ddev->रुकोq, pt);

	अगर (!kfअगरo_is_empty(&client->buffer))
		events |= EPOLLIN | EPOLLRDNORM;

	वापस events;
पूर्ण

अटल पूर्णांक surface_dtx_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा sdtx_client *client = file->निजी_data;

	वापस fasync_helper(fd, file, on, &client->fasync);
पूर्ण

अटल स्थिर काष्ठा file_operations surface_dtx_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = surface_dtx_खोलो,
	.release        = surface_dtx_release,
	.पढ़ो           = surface_dtx_पढ़ो,
	.poll           = surface_dtx_poll,
	.fasync         = surface_dtx_fasync,
	.unlocked_ioctl = surface_dtx_ioctl,
	.compat_ioctl   = surface_dtx_ioctl,
	.llseek         = no_llseek,
पूर्ण;


/* -- Event handling/क्रमwarding. -------------------------------------------- */

/*
 * The device operation mode is not immediately updated on the EC when the
 * base has been connected, i.e. querying the device mode inside the
 * connection event callback yields an outdated value. Thus, we can only
 * determine the new tablet-mode चयन and device mode values after some
 * समय.
 *
 * These delays have been chosen by experimenting. We first delay on connect
 * events, then check and validate the device mode against the base state and
 * अगर invalid delay again by the "recheck" delay.
 */
#घोषणा SDTX_DEVICE_MODE_DELAY_CONNECT	msecs_to_jअगरfies(100)
#घोषणा SDTX_DEVICE_MODE_DELAY_RECHECK	msecs_to_jअगरfies(100)

काष्ठा sdtx_status_event अणु
	काष्ठा sdtx_event e;
	__u16 v;
पूर्ण __packed;

काष्ठा sdtx_base_info_event अणु
	काष्ठा sdtx_event e;
	काष्ठा sdtx_base_info v;
पूर्ण __packed;

जोड़ sdtx_generic_event अणु
	काष्ठा sdtx_event common;
	काष्ठा sdtx_status_event status;
	काष्ठा sdtx_base_info_event base;
पूर्ण;

अटल व्योम sdtx_update_device_mode(काष्ठा sdtx_device *ddev, अचिन्हित दीर्घ delay);

/* Must be executed with ddev->ग_लिखो_lock held. */
अटल व्योम sdtx_push_event(काष्ठा sdtx_device *ddev, काष्ठा sdtx_event *evt)
अणु
	स्थिर माप_प्रकार len = माप(काष्ठा sdtx_event) + evt->length;
	काष्ठा sdtx_client *client;

	lockdep_निश्चित_held(&ddev->ग_लिखो_lock);

	करोwn_पढ़ो(&ddev->client_lock);
	list_क्रम_each_entry(client, &ddev->client_list, node) अणु
		अगर (!test_bit(SDTX_CLIENT_EVENTS_ENABLED_BIT, &client->flags))
			जारी;

		अगर (likely(kfअगरo_avail(&client->buffer) >= len))
			kfअगरo_in(&client->buffer, (स्थिर u8 *)evt, len);
		अन्यथा
			dev_warn(ddev->dev, "event buffer overrun\n");

		समाप्त_fasync(&client->fasync, SIGIO, POLL_IN);
	पूर्ण
	up_पढ़ो(&ddev->client_lock);

	wake_up_पूर्णांकerruptible(&ddev->रुकोq);
पूर्ण

अटल u32 sdtx_notअगरier(काष्ठा ssam_event_notअगरier *nf, स्थिर काष्ठा ssam_event *in)
अणु
	काष्ठा sdtx_device *ddev = container_of(nf, काष्ठा sdtx_device, notअगर);
	जोड़ sdtx_generic_event event;
	माप_प्रकार len;

	/* Validate event payload length. */
	चयन (in->command_id) अणु
	हाल SAM_EVENT_CID_DTX_CONNECTION:
		len = 2 * माप(u8);
		अवरोध;

	हाल SAM_EVENT_CID_DTX_REQUEST:
		len = 0;
		अवरोध;

	हाल SAM_EVENT_CID_DTX_CANCEL:
		len = माप(u8);
		अवरोध;

	हाल SAM_EVENT_CID_DTX_LATCH_STATUS:
		len = माप(u8);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	अगर (in->length != len) अणु
		dev_err(ddev->dev,
			"unexpected payload size for event %#04x: got %u, expected %zu\n",
			in->command_id, in->length, len);
		वापस 0;
	पूर्ण

	mutex_lock(&ddev->ग_लिखो_lock);

	/* Translate event. */
	चयन (in->command_id) अणु
	हाल SAM_EVENT_CID_DTX_CONNECTION:
		clear_bit(SDTX_DEVICE_सूचीTY_BASE_BIT, &ddev->flags);

		/* If state has not changed: करो not send new event. */
		अगर (ddev->state.base.state == in->data[0] &&
		    ddev->state.base.base_id == in->data[1])
			जाओ out;

		ddev->state.base.state = in->data[0];
		ddev->state.base.base_id = in->data[1];

		event.base.e.length = माप(काष्ठा sdtx_base_info);
		event.base.e.code = SDTX_EVENT_BASE_CONNECTION;
		event.base.v.state = sdtx_translate_base_state(ddev, in->data[0]);
		event.base.v.base_id = SDTX_BASE_TYPE_SSH(in->data[1]);
		अवरोध;

	हाल SAM_EVENT_CID_DTX_REQUEST:
		event.common.code = SDTX_EVENT_REQUEST;
		event.common.length = 0;
		अवरोध;

	हाल SAM_EVENT_CID_DTX_CANCEL:
		event.status.e.length = माप(u16);
		event.status.e.code = SDTX_EVENT_CANCEL;
		event.status.v = sdtx_translate_cancel_reason(ddev, in->data[0]);
		अवरोध;

	हाल SAM_EVENT_CID_DTX_LATCH_STATUS:
		clear_bit(SDTX_DEVICE_सूचीTY_LATCH_BIT, &ddev->flags);

		/* If state has not changed: करो not send new event. */
		अगर (ddev->state.latch_status == in->data[0])
			जाओ out;

		ddev->state.latch_status = in->data[0];

		event.status.e.length = माप(u16);
		event.status.e.code = SDTX_EVENT_LATCH_STATUS;
		event.status.v = sdtx_translate_latch_status(ddev, in->data[0]);
		अवरोध;
	पूर्ण

	sdtx_push_event(ddev, &event.common);

	/* Update device mode on base connection change. */
	अगर (in->command_id == SAM_EVENT_CID_DTX_CONNECTION) अणु
		अचिन्हित दीर्घ delay;

		delay = in->data[0] ? SDTX_DEVICE_MODE_DELAY_CONNECT : 0;
		sdtx_update_device_mode(ddev, delay);
	पूर्ण

out:
	mutex_unlock(&ddev->ग_लिखो_lock);
	वापस SSAM_NOTIF_HANDLED;
पूर्ण


/* -- State update functions. ----------------------------------------------- */

अटल bool sdtx_device_mode_invalid(u8 mode, u8 base_state)
अणु
	वापस ((base_state == SSAM_BAS_BASE_STATE_ATTACHED) &&
		(mode == SDTX_DEVICE_MODE_TABLET)) ||
	       ((base_state == SSAM_BAS_BASE_STATE_DETACH_SUCCESS) &&
		(mode != SDTX_DEVICE_MODE_TABLET));
पूर्ण

अटल व्योम sdtx_device_mode_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sdtx_device *ddev = container_of(work, काष्ठा sdtx_device, mode_work.work);
	काष्ठा sdtx_status_event event;
	काष्ठा ssam_bas_base_info base;
	पूर्णांक status, tablet;
	u8 mode;

	/* Get operation mode. */
	status = ssam_retry(ssam_bas_get_device_mode, ddev->ctrl, &mode);
	अगर (status) अणु
		dev_err(ddev->dev, "failed to get device mode: %d\n", status);
		वापस;
	पूर्ण

	/* Get base info. */
	status = ssam_retry(ssam_bas_get_base, ddev->ctrl, &base);
	अगर (status) अणु
		dev_err(ddev->dev, "failed to get base info: %d\n", status);
		वापस;
	पूर्ण

	/*
	 * In some हालs (specअगरically when attaching the base), the device
	 * mode isn't updated right away. Thus we check अगर the device mode
	 * makes sense क्रम the given base state and try again later अगर it
	 * करोesn't.
	 */
	अगर (sdtx_device_mode_invalid(mode, base.state)) अणु
		dev_dbg(ddev->dev, "device mode is invalid, trying again\n");
		sdtx_update_device_mode(ddev, SDTX_DEVICE_MODE_DELAY_RECHECK);
		वापस;
	पूर्ण

	mutex_lock(&ddev->ग_लिखो_lock);
	clear_bit(SDTX_DEVICE_सूचीTY_MODE_BIT, &ddev->flags);

	/* Aव्योम sending duplicate device-mode events. */
	अगर (ddev->state.device_mode == mode) अणु
		mutex_unlock(&ddev->ग_लिखो_lock);
		वापस;
	पूर्ण

	ddev->state.device_mode = mode;

	event.e.length = माप(u16);
	event.e.code = SDTX_EVENT_DEVICE_MODE;
	event.v = mode;

	sdtx_push_event(ddev, &event.e);

	/* Send SW_TABLET_MODE event. */
	tablet = mode != SDTX_DEVICE_MODE_LAPTOP;
	input_report_चयन(ddev->mode_चयन, SW_TABLET_MODE, tablet);
	input_sync(ddev->mode_चयन);

	mutex_unlock(&ddev->ग_लिखो_lock);
पूर्ण

अटल व्योम sdtx_update_device_mode(काष्ठा sdtx_device *ddev, अचिन्हित दीर्घ delay)
अणु
	schedule_delayed_work(&ddev->mode_work, delay);
पूर्ण

/* Must be executed with ddev->ग_लिखो_lock held. */
अटल व्योम __sdtx_device_state_update_base(काष्ठा sdtx_device *ddev,
					    काष्ठा ssam_bas_base_info info)
अणु
	काष्ठा sdtx_base_info_event event;

	lockdep_निश्चित_held(&ddev->ग_लिखो_lock);

	/* Prevent duplicate events. */
	अगर (ddev->state.base.state == info.state &&
	    ddev->state.base.base_id == info.base_id)
		वापस;

	ddev->state.base = info;

	event.e.length = माप(काष्ठा sdtx_base_info);
	event.e.code = SDTX_EVENT_BASE_CONNECTION;
	event.v.state = sdtx_translate_base_state(ddev, info.state);
	event.v.base_id = SDTX_BASE_TYPE_SSH(info.base_id);

	sdtx_push_event(ddev, &event.e);
पूर्ण

/* Must be executed with ddev->ग_लिखो_lock held. */
अटल व्योम __sdtx_device_state_update_mode(काष्ठा sdtx_device *ddev, u8 mode)
अणु
	काष्ठा sdtx_status_event event;
	पूर्णांक tablet;

	/*
	 * Note: This function must be called after updating the base state
	 * via __sdtx_device_state_update_base(), as we rely on the updated
	 * base state value in the validity check below.
	 */

	lockdep_निश्चित_held(&ddev->ग_लिखो_lock);

	अगर (sdtx_device_mode_invalid(mode, ddev->state.base.state)) अणु
		dev_dbg(ddev->dev, "device mode is invalid, trying again\n");
		sdtx_update_device_mode(ddev, SDTX_DEVICE_MODE_DELAY_RECHECK);
		वापस;
	पूर्ण

	/* Prevent duplicate events. */
	अगर (ddev->state.device_mode == mode)
		वापस;

	ddev->state.device_mode = mode;

	/* Send event. */
	event.e.length = माप(u16);
	event.e.code = SDTX_EVENT_DEVICE_MODE;
	event.v = mode;

	sdtx_push_event(ddev, &event.e);

	/* Send SW_TABLET_MODE event. */
	tablet = mode != SDTX_DEVICE_MODE_LAPTOP;
	input_report_चयन(ddev->mode_चयन, SW_TABLET_MODE, tablet);
	input_sync(ddev->mode_चयन);
पूर्ण

/* Must be executed with ddev->ग_लिखो_lock held. */
अटल व्योम __sdtx_device_state_update_latch(काष्ठा sdtx_device *ddev, u8 status)
अणु
	काष्ठा sdtx_status_event event;

	lockdep_निश्चित_held(&ddev->ग_लिखो_lock);

	/* Prevent duplicate events. */
	अगर (ddev->state.latch_status == status)
		वापस;

	ddev->state.latch_status = status;

	event.e.length = माप(काष्ठा sdtx_base_info);
	event.e.code = SDTX_EVENT_BASE_CONNECTION;
	event.v = sdtx_translate_latch_status(ddev, status);

	sdtx_push_event(ddev, &event.e);
पूर्ण

अटल व्योम sdtx_device_state_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sdtx_device *ddev = container_of(work, काष्ठा sdtx_device, state_work.work);
	काष्ठा ssam_bas_base_info base;
	u8 mode, latch;
	पूर्णांक status;

	/* Mark everything as dirty. */
	set_bit(SDTX_DEVICE_सूचीTY_BASE_BIT, &ddev->flags);
	set_bit(SDTX_DEVICE_सूचीTY_MODE_BIT, &ddev->flags);
	set_bit(SDTX_DEVICE_सूचीTY_LATCH_BIT, &ddev->flags);

	/*
	 * Ensure that the state माला_लो marked as dirty beक्रमe continuing to
	 * query it. Necessary to ensure that clear_bit() calls in
	 * sdtx_notअगरier() and sdtx_device_mode_workfn() actually clear these
	 * bits अगर an event is received जबतक updating the state here.
	 */
	smp_mb__after_atomic();

	status = ssam_retry(ssam_bas_get_base, ddev->ctrl, &base);
	अगर (status) अणु
		dev_err(ddev->dev, "failed to get base state: %d\n", status);
		वापस;
	पूर्ण

	status = ssam_retry(ssam_bas_get_device_mode, ddev->ctrl, &mode);
	अगर (status) अणु
		dev_err(ddev->dev, "failed to get device mode: %d\n", status);
		वापस;
	पूर्ण

	status = ssam_retry(ssam_bas_get_latch_status, ddev->ctrl, &latch);
	अगर (status) अणु
		dev_err(ddev->dev, "failed to get latch status: %d\n", status);
		वापस;
	पूर्ण

	mutex_lock(&ddev->ग_लिखो_lock);

	/*
	 * If the respective dirty-bit has been cleared, an event has been
	 * received, updating this state. The queried state may thus be out of
	 * date. At this poपूर्णांक, we can safely assume that the state provided
	 * by the event is either up to date, or we're about to receive
	 * another event updating it.
	 */

	अगर (test_and_clear_bit(SDTX_DEVICE_सूचीTY_BASE_BIT, &ddev->flags))
		__sdtx_device_state_update_base(ddev, base);

	अगर (test_and_clear_bit(SDTX_DEVICE_सूचीTY_MODE_BIT, &ddev->flags))
		__sdtx_device_state_update_mode(ddev, mode);

	अगर (test_and_clear_bit(SDTX_DEVICE_सूचीTY_LATCH_BIT, &ddev->flags))
		__sdtx_device_state_update_latch(ddev, latch);

	mutex_unlock(&ddev->ग_लिखो_lock);
पूर्ण

अटल व्योम sdtx_update_device_state(काष्ठा sdtx_device *ddev, अचिन्हित दीर्घ delay)
अणु
	schedule_delayed_work(&ddev->state_work, delay);
पूर्ण


/* -- Common device initialization. ----------------------------------------- */

अटल पूर्णांक sdtx_device_init(काष्ठा sdtx_device *ddev, काष्ठा device *dev,
			    काष्ठा ssam_controller *ctrl)
अणु
	पूर्णांक status, tablet_mode;

	/* Basic initialization. */
	kref_init(&ddev->kref);
	init_rwsem(&ddev->lock);
	ddev->dev = dev;
	ddev->ctrl = ctrl;

	ddev->mdev.minor = MISC_DYNAMIC_MINOR;
	ddev->mdev.name = "surface_dtx";
	ddev->mdev.nodename = "surface/dtx";
	ddev->mdev.fops = &surface_dtx_fops;

	ddev->notअगर.base.priority = 1;
	ddev->notअगर.base.fn = sdtx_notअगरier;
	ddev->notअगर.event.reg = SSAM_EVENT_REGISTRY_SAM;
	ddev->notअगर.event.id.target_category = SSAM_SSH_TC_BAS;
	ddev->notअगर.event.id.instance = 0;
	ddev->notअगर.event.mask = SSAM_EVENT_MASK_NONE;
	ddev->notअगर.event.flags = SSAM_EVENT_SEQUENCED;

	init_रुकोqueue_head(&ddev->रुकोq);
	mutex_init(&ddev->ग_लिखो_lock);
	init_rwsem(&ddev->client_lock);
	INIT_LIST_HEAD(&ddev->client_list);

	INIT_DELAYED_WORK(&ddev->mode_work, sdtx_device_mode_workfn);
	INIT_DELAYED_WORK(&ddev->state_work, sdtx_device_state_workfn);

	/*
	 * Get current device state. We want to guarantee that events are only
	 * sent when state actually changes. Thus we cannot use special
	 * "uninitialized" values, as that would cause problems when manually
	 * querying the state in surface_dtx_pm_complete(). I.e. we would not
	 * be able to detect state changes there अगर no change event has been
	 * received between driver initialization and first device suspension.
	 *
	 * Note that we also need to करो this beक्रमe रेजिस्टरing the event
	 * notअगरier, as that may access the state values.
	 */
	status = ssam_retry(ssam_bas_get_base, ddev->ctrl, &ddev->state.base);
	अगर (status)
		वापस status;

	status = ssam_retry(ssam_bas_get_device_mode, ddev->ctrl, &ddev->state.device_mode);
	अगर (status)
		वापस status;

	status = ssam_retry(ssam_bas_get_latch_status, ddev->ctrl, &ddev->state.latch_status);
	अगर (status)
		वापस status;

	/* Set up tablet mode चयन. */
	ddev->mode_चयन = input_allocate_device();
	अगर (!ddev->mode_चयन)
		वापस -ENOMEM;

	ddev->mode_चयन->name = "Microsoft Surface DTX Device Mode Switch";
	ddev->mode_चयन->phys = "ssam/01:11:01:00:00/input0";
	ddev->mode_चयन->id.bustype = BUS_HOST;
	ddev->mode_चयन->dev.parent = ddev->dev;

	tablet_mode = (ddev->state.device_mode != SDTX_DEVICE_MODE_LAPTOP);
	input_set_capability(ddev->mode_चयन, EV_SW, SW_TABLET_MODE);
	input_report_चयन(ddev->mode_चयन, SW_TABLET_MODE, tablet_mode);

	status = input_रेजिस्टर_device(ddev->mode_चयन);
	अगर (status) अणु
		input_मुक्त_device(ddev->mode_चयन);
		वापस status;
	पूर्ण

	/* Set up event notअगरier. */
	status = ssam_notअगरier_रेजिस्टर(ddev->ctrl, &ddev->notअगर);
	अगर (status)
		जाओ err_notअगर;

	/* Register miscdevice. */
	status = misc_रेजिस्टर(&ddev->mdev);
	अगर (status)
		जाओ err_mdev;

	/*
	 * Update device state in हाल it has changed between getting the
	 * initial mode and रेजिस्टरing the event notअगरier.
	 */
	sdtx_update_device_state(ddev, 0);
	वापस 0;

err_notअगर:
	ssam_notअगरier_unरेजिस्टर(ddev->ctrl, &ddev->notअगर);
	cancel_delayed_work_sync(&ddev->mode_work);
err_mdev:
	input_unरेजिस्टर_device(ddev->mode_चयन);
	वापस status;
पूर्ण

अटल काष्ठा sdtx_device *sdtx_device_create(काष्ठा device *dev, काष्ठा ssam_controller *ctrl)
अणु
	काष्ठा sdtx_device *ddev;
	पूर्णांक status;

	ddev = kzalloc(माप(*ddev), GFP_KERNEL);
	अगर (!ddev)
		वापस ERR_PTR(-ENOMEM);

	status = sdtx_device_init(ddev, dev, ctrl);
	अगर (status) अणु
		sdtx_device_put(ddev);
		वापस ERR_PTR(status);
	पूर्ण

	वापस ddev;
पूर्ण

अटल व्योम sdtx_device_destroy(काष्ठा sdtx_device *ddev)
अणु
	काष्ठा sdtx_client *client;

	/*
	 * Mark device as shut-करोwn. Prevent new clients from being added and
	 * new operations from being executed.
	 */
	set_bit(SDTX_DEVICE_SHUTDOWN_BIT, &ddev->flags);

	/* Disable notअगरiers, prevent new events from arriving. */
	ssam_notअगरier_unरेजिस्टर(ddev->ctrl, &ddev->notअगर);

	/* Stop mode_work, prevent access to mode_चयन. */
	cancel_delayed_work_sync(&ddev->mode_work);

	/* Stop state_work. */
	cancel_delayed_work_sync(&ddev->state_work);

	/* With mode_work canceled, we can unरेजिस्टर the mode_चयन. */
	input_unरेजिस्टर_device(ddev->mode_चयन);

	/* Wake up async clients. */
	करोwn_ग_लिखो(&ddev->client_lock);
	list_क्रम_each_entry(client, &ddev->client_list, node) अणु
		समाप्त_fasync(&client->fasync, SIGIO, POLL_HUP);
	पूर्ण
	up_ग_लिखो(&ddev->client_lock);

	/* Wake up blocking clients. */
	wake_up_पूर्णांकerruptible(&ddev->रुकोq);

	/*
	 * Wait क्रम clients to finish their current operation. After this, the
	 * controller and device references are guaranteed to be no दीर्घer in
	 * use.
	 */
	करोwn_ग_लिखो(&ddev->lock);
	ddev->dev = शून्य;
	ddev->ctrl = शून्य;
	up_ग_लिखो(&ddev->lock);

	/* Finally हटाओ the misc-device. */
	misc_deरेजिस्टर(&ddev->mdev);

	/*
	 * We're now guaranteed that sdtx_device_open() won't be called any
	 * more, so we can now drop out reference.
	 */
	sdtx_device_put(ddev);
पूर्ण


/* -- PM ops. --------------------------------------------------------------- */

#अगर_घोषित CONFIG_PM_SLEEP

अटल व्योम surface_dtx_pm_complete(काष्ठा device *dev)
अणु
	काष्ठा sdtx_device *ddev = dev_get_drvdata(dev);

	/*
	 * Normally, the EC will store events जबतक suspended (i.e. in
	 * display-off state) and release them when resumed (i.e. transitioned
	 * to display-on state). During hibernation, however, the EC will be
	 * shut करोwn and करोes not store events. Furthermore, events might be
	 * dropped during proदीर्घed suspension (it is currently unknown how
	 * big this event buffer is and how it behaves on overruns).
	 *
	 * To prevent any problems, we update the device state here. We करो
	 * this delayed to ensure that any events sent by the EC directly
	 * after resuming will be handled first. The delay below has been
	 * chosen (experimentally), so that there should be ample समय क्रम
	 * these events to be handled, beक्रमe we check and, अगर necessary,
	 * update the state.
	 */
	sdtx_update_device_state(ddev, msecs_to_jअगरfies(1000));
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops surface_dtx_pm_ops = अणु
	.complete = surface_dtx_pm_complete,
पूर्ण;

#अन्यथा /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops surface_dtx_pm_ops = अणुपूर्ण;

#पूर्ण_अगर /* CONFIG_PM_SLEEP */


/* -- Platक्रमm driver. ------------------------------------------------------ */

अटल पूर्णांक surface_dtx_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ssam_controller *ctrl;
	काष्ठा sdtx_device *ddev;

	/* Link to EC. */
	ctrl = ssam_client_bind(&pdev->dev);
	अगर (IS_ERR(ctrl))
		वापस PTR_ERR(ctrl) == -ENODEV ? -EPROBE_DEFER : PTR_ERR(ctrl);

	ddev = sdtx_device_create(&pdev->dev, ctrl);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	platक्रमm_set_drvdata(pdev, ddev);
	वापस 0;
पूर्ण

अटल पूर्णांक surface_dtx_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	sdtx_device_destroy(platक्रमm_get_drvdata(pdev));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id surface_dtx_acpi_match[] = अणु
	अणु "MSHW0133", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, surface_dtx_acpi_match);

अटल काष्ठा platक्रमm_driver surface_dtx_platक्रमm_driver = अणु
	.probe = surface_dtx_platक्रमm_probe,
	.हटाओ = surface_dtx_platक्रमm_हटाओ,
	.driver = अणु
		.name = "surface_dtx_pltf",
		.acpi_match_table = surface_dtx_acpi_match,
		.pm = &surface_dtx_pm_ops,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;


/* -- SSAM device driver. --------------------------------------------------- */

#अगर_घोषित CONFIG_SURFACE_AGGREGATOR_BUS

अटल पूर्णांक surface_dtx_ssam_probe(काष्ठा ssam_device *sdev)
अणु
	काष्ठा sdtx_device *ddev;

	ddev = sdtx_device_create(&sdev->dev, sdev->ctrl);
	अगर (IS_ERR(ddev))
		वापस PTR_ERR(ddev);

	ssam_device_set_drvdata(sdev, ddev);
	वापस 0;
पूर्ण

अटल व्योम surface_dtx_ssam_हटाओ(काष्ठा ssam_device *sdev)
अणु
	sdtx_device_destroy(ssam_device_get_drvdata(sdev));
पूर्ण

अटल स्थिर काष्ठा ssam_device_id surface_dtx_ssam_match[] = अणु
	अणु SSAM_SDEV(BAS, 0x01, 0x00, 0x00) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ssam, surface_dtx_ssam_match);

अटल काष्ठा ssam_device_driver surface_dtx_ssam_driver = अणु
	.probe = surface_dtx_ssam_probe,
	.हटाओ = surface_dtx_ssam_हटाओ,
	.match_table = surface_dtx_ssam_match,
	.driver = अणु
		.name = "surface_dtx",
		.pm = &surface_dtx_pm_ops,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ssam_dtx_driver_रेजिस्टर(व्योम)
अणु
	वापस ssam_device_driver_रेजिस्टर(&surface_dtx_ssam_driver);
पूर्ण

अटल व्योम ssam_dtx_driver_unरेजिस्टर(व्योम)
अणु
	ssam_device_driver_unरेजिस्टर(&surface_dtx_ssam_driver);
पूर्ण

#अन्यथा /* CONFIG_SURFACE_AGGREGATOR_BUS */

अटल पूर्णांक ssam_dtx_driver_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम ssam_dtx_driver_unरेजिस्टर(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_SURFACE_AGGREGATOR_BUS */


/* -- Module setup. --------------------------------------------------------- */

अटल पूर्णांक __init surface_dtx_init(व्योम)
अणु
	पूर्णांक status;

	status = ssam_dtx_driver_रेजिस्टर();
	अगर (status)
		वापस status;

	status = platक्रमm_driver_रेजिस्टर(&surface_dtx_platक्रमm_driver);
	अगर (status)
		ssam_dtx_driver_unरेजिस्टर();

	वापस status;
पूर्ण
module_init(surface_dtx_init);

अटल व्योम __निकास surface_dtx_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&surface_dtx_platक्रमm_driver);
	ssam_dtx_driver_unरेजिस्टर();
पूर्ण
module_निकास(surface_dtx_निकास);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Detachment-system driver for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
