<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2014 Raspberry Pi (Trading) Ltd. All rights reserved.
 * Copyright (c) 2010-2012 Broadcom. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/bug.h>
#समावेश <linux/completion.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/compat.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <soc/bcm2835/raspberrypi-firmware.h>

#समावेश "vchiq_core.h"
#समावेश "vchiq_ioctl.h"
#समावेश "vchiq_arm.h"
#समावेश "vchiq_debugfs.h"

#घोषणा DEVICE_NAME "vchiq"

/* Override the शेष prefix, which would be vchiq_arm (from the filename) */
#अघोषित MODULE_PARAM_PREFIX
#घोषणा MODULE_PARAM_PREFIX DEVICE_NAME "."

/* Some per-instance स्थिरants */
#घोषणा MAX_COMPLETIONS 128
#घोषणा MAX_SERVICES 64
#घोषणा MAX_ELEMENTS 8
#घोषणा MSG_QUEUE_SIZE 128

#घोषणा KEEPALIVE_VER 1
#घोषणा KEEPALIVE_VER_MIN KEEPALIVE_VER

/* Run समय control of log level, based on KERN_XXX level. */
पूर्णांक vchiq_arm_log_level = VCHIQ_LOG_DEFAULT;
पूर्णांक vchiq_susp_log_level = VCHIQ_LOG_ERROR;

काष्ठा user_service अणु
	काष्ठा vchiq_service *service;
	व्योम __user *userdata;
	काष्ठा vchiq_instance *instance;
	अक्षर is_vchi;
	अक्षर dequeue_pending;
	अक्षर बंद_pending;
	पूर्णांक message_available_pos;
	पूर्णांक msg_insert;
	पूर्णांक msg_हटाओ;
	काष्ठा completion insert_event;
	काष्ठा completion हटाओ_event;
	काष्ठा completion बंद_event;
	काष्ठा vchiq_header *msg_queue[MSG_QUEUE_SIZE];
पूर्ण;

काष्ठा bulk_रुकोer_node अणु
	काष्ठा bulk_रुकोer bulk_रुकोer;
	पूर्णांक pid;
	काष्ठा list_head list;
पूर्ण;

काष्ठा vchiq_instance अणु
	काष्ठा vchiq_state *state;
	काष्ठा vchiq_completion_data_kernel completions[MAX_COMPLETIONS];
	पूर्णांक completion_insert;
	पूर्णांक completion_हटाओ;
	काष्ठा completion insert_event;
	काष्ठा completion हटाओ_event;
	काष्ठा mutex completion_mutex;

	पूर्णांक connected;
	पूर्णांक closing;
	पूर्णांक pid;
	पूर्णांक mark;
	पूर्णांक use_बंद_delivered;
	पूर्णांक trace;

	काष्ठा list_head bulk_रुकोer_list;
	काष्ठा mutex bulk_रुकोer_list_mutex;

	काष्ठा vchiq_debugfs_node debugfs_node;
पूर्ण;

काष्ठा dump_context अणु
	अक्षर __user *buf;
	माप_प्रकार actual;
	माप_प्रकार space;
	loff_t offset;
पूर्ण;

अटल काष्ठा cdev    vchiq_cdev;
अटल dev_t          vchiq_devid;
अटल काष्ठा vchiq_state g_state;
अटल काष्ठा class  *vchiq_class;
अटल DEFINE_SPINLOCK(msg_queue_spinlock);
अटल काष्ठा platक्रमm_device *bcm2835_camera;
अटल काष्ठा platक्रमm_device *bcm2835_audio;

अटल काष्ठा vchiq_drvdata bcm2835_drvdata = अणु
	.cache_line_size = 32,
पूर्ण;

अटल काष्ठा vchiq_drvdata bcm2836_drvdata = अणु
	.cache_line_size = 64,
पूर्ण;

अटल स्थिर अक्षर *स्थिर ioctl_names[] = अणु
	"CONNECT",
	"SHUTDOWN",
	"CREATE_SERVICE",
	"REMOVE_SERVICE",
	"QUEUE_MESSAGE",
	"QUEUE_BULK_TRANSMIT",
	"QUEUE_BULK_RECEIVE",
	"AWAIT_COMPLETION",
	"DEQUEUE_MESSAGE",
	"GET_CLIENT_ID",
	"GET_CONFIG",
	"CLOSE_SERVICE",
	"USE_SERVICE",
	"RELEASE_SERVICE",
	"SET_SERVICE_OPTION",
	"DUMP_PHYS_MEM",
	"LIB_VERSION",
	"CLOSE_DELIVERED"
पूर्ण;

vchiq_अटल_निश्चित(ARRAY_SIZE(ioctl_names) ==
		    (VCHIQ_IOC_MAX + 1));

अटल क्रमागत vchiq_status
vchiq_blocking_bulk_transfer(अचिन्हित पूर्णांक handle, व्योम *data,
	अचिन्हित पूर्णांक size, क्रमागत vchiq_bulk_dir dir);

#घोषणा VCHIQ_INIT_RETRIES 10
क्रमागत vchiq_status vchiq_initialise(काष्ठा vchiq_instance **instance_out)
अणु
	क्रमागत vchiq_status status = VCHIQ_ERROR;
	काष्ठा vchiq_state *state;
	काष्ठा vchiq_instance *instance = शून्य;
	पूर्णांक i;

	vchiq_log_trace(vchiq_core_log_level, "%s called", __func__);

	/*
	 * VideoCore may not be पढ़ोy due to boot up timing.
	 * It may never be पढ़ोy अगर kernel and firmware are mismatched,so करोn't
	 * block क्रमever.
	 */
	क्रम (i = 0; i < VCHIQ_INIT_RETRIES; i++) अणु
		state = vchiq_get_state();
		अगर (state)
			अवरोध;
		usleep_range(500, 600);
	पूर्ण
	अगर (i == VCHIQ_INIT_RETRIES) अणु
		vchiq_log_error(vchiq_core_log_level,
			"%s: videocore not initialized\n", __func__);
		जाओ failed;
	पूर्ण अन्यथा अगर (i > 0) अणु
		vchiq_log_warning(vchiq_core_log_level,
			"%s: videocore initialized after %d retries\n",
			__func__, i);
	पूर्ण

	instance = kzalloc(माप(*instance), GFP_KERNEL);
	अगर (!instance) अणु
		vchiq_log_error(vchiq_core_log_level,
			"%s: error allocating vchiq instance\n", __func__);
		जाओ failed;
	पूर्ण

	instance->connected = 0;
	instance->state = state;
	mutex_init(&instance->bulk_रुकोer_list_mutex);
	INIT_LIST_HEAD(&instance->bulk_रुकोer_list);

	*instance_out = instance;

	status = VCHIQ_SUCCESS;

failed:
	vchiq_log_trace(vchiq_core_log_level,
		"%s(%p): returning %d", __func__, instance, status);

	वापस status;
पूर्ण
EXPORT_SYMBOL(vchiq_initialise);

क्रमागत vchiq_status vchiq_shutकरोwn(काष्ठा vchiq_instance *instance)
अणु
	क्रमागत vchiq_status status;
	काष्ठा vchiq_state *state = instance->state;

	vchiq_log_trace(vchiq_core_log_level,
		"%s(%p) called", __func__, instance);

	अगर (mutex_lock_समाप्तable(&state->mutex))
		वापस VCHIQ_RETRY;

	/* Remove all services */
	status = vchiq_shutकरोwn_पूर्णांकernal(state, instance);

	mutex_unlock(&state->mutex);

	vchiq_log_trace(vchiq_core_log_level,
		"%s(%p): returning %d", __func__, instance, status);

	अगर (status == VCHIQ_SUCCESS) अणु
		काष्ठा bulk_रुकोer_node *रुकोer, *next;

		list_क्रम_each_entry_safe(रुकोer, next,
					 &instance->bulk_रुकोer_list, list) अणु
			list_del(&रुकोer->list);
			vchiq_log_info(vchiq_arm_log_level,
					"bulk_waiter - cleaned up %pK for pid %d",
					रुकोer, रुकोer->pid);
			kमुक्त(रुकोer);
		पूर्ण
		kमुक्त(instance);
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL(vchiq_shutकरोwn);

अटल पूर्णांक vchiq_is_connected(काष्ठा vchiq_instance *instance)
अणु
	वापस instance->connected;
पूर्ण

क्रमागत vchiq_status vchiq_connect(काष्ठा vchiq_instance *instance)
अणु
	क्रमागत vchiq_status status;
	काष्ठा vchiq_state *state = instance->state;

	vchiq_log_trace(vchiq_core_log_level,
		"%s(%p) called", __func__, instance);

	अगर (mutex_lock_समाप्तable(&state->mutex)) अणु
		vchiq_log_trace(vchiq_core_log_level,
			"%s: call to mutex_lock failed", __func__);
		status = VCHIQ_RETRY;
		जाओ failed;
	पूर्ण
	status = vchiq_connect_पूर्णांकernal(state, instance);

	अगर (status == VCHIQ_SUCCESS)
		instance->connected = 1;

	mutex_unlock(&state->mutex);

failed:
	vchiq_log_trace(vchiq_core_log_level,
		"%s(%p): returning %d", __func__, instance, status);

	वापस status;
पूर्ण
EXPORT_SYMBOL(vchiq_connect);

अटल क्रमागत vchiq_status vchiq_add_service(
	काष्ठा vchiq_instance             *instance,
	स्थिर काष्ठा vchiq_service_params_kernel *params,
	अचिन्हित पूर्णांक       *phandle)
अणु
	क्रमागत vchiq_status status;
	काष्ठा vchiq_state *state = instance->state;
	काष्ठा vchiq_service *service = शून्य;
	पूर्णांक srvstate;

	vchiq_log_trace(vchiq_core_log_level,
		"%s(%p) called", __func__, instance);

	*phandle = VCHIQ_SERVICE_HANDLE_INVALID;

	srvstate = vchiq_is_connected(instance)
		? VCHIQ_SRVSTATE_LISTENING
		: VCHIQ_SRVSTATE_HIDDEN;

	service = vchiq_add_service_पूर्णांकernal(
		state,
		params,
		srvstate,
		instance,
		शून्य);

	अगर (service) अणु
		*phandle = service->handle;
		status = VCHIQ_SUCCESS;
	पूर्ण अन्यथा
		status = VCHIQ_ERROR;

	vchiq_log_trace(vchiq_core_log_level,
		"%s(%p): returning %d", __func__, instance, status);

	वापस status;
पूर्ण

क्रमागत vchiq_status vchiq_खोलो_service(
	काष्ठा vchiq_instance             *instance,
	स्थिर काष्ठा vchiq_service_params_kernel *params,
	अचिन्हित पूर्णांक       *phandle)
अणु
	क्रमागत vchiq_status   status = VCHIQ_ERROR;
	काष्ठा vchiq_state   *state = instance->state;
	काष्ठा vchiq_service *service = शून्य;

	vchiq_log_trace(vchiq_core_log_level,
		"%s(%p) called", __func__, instance);

	*phandle = VCHIQ_SERVICE_HANDLE_INVALID;

	अगर (!vchiq_is_connected(instance))
		जाओ failed;

	service = vchiq_add_service_पूर्णांकernal(state,
		params,
		VCHIQ_SRVSTATE_OPENING,
		instance,
		शून्य);

	अगर (service) अणु
		*phandle = service->handle;
		status = vchiq_खोलो_service_पूर्णांकernal(service, current->pid);
		अगर (status != VCHIQ_SUCCESS) अणु
			vchiq_हटाओ_service(service->handle);
			*phandle = VCHIQ_SERVICE_HANDLE_INVALID;
		पूर्ण
	पूर्ण

failed:
	vchiq_log_trace(vchiq_core_log_level,
		"%s(%p): returning %d", __func__, instance, status);

	वापस status;
पूर्ण
EXPORT_SYMBOL(vchiq_खोलो_service);

क्रमागत vchiq_status
vchiq_bulk_transmit(अचिन्हित पूर्णांक handle, स्थिर व्योम *data,
	अचिन्हित पूर्णांक size, व्योम *userdata, क्रमागत vchiq_bulk_mode mode)
अणु
	क्रमागत vchiq_status status;

	जबतक (1) अणु
		चयन (mode) अणु
		हाल VCHIQ_BULK_MODE_NOCALLBACK:
		हाल VCHIQ_BULK_MODE_CALLBACK:
			status = vchiq_bulk_transfer(handle,
						     (व्योम *)data, शून्य,
						     size, userdata, mode,
						     VCHIQ_BULK_TRANSMIT);
			अवरोध;
		हाल VCHIQ_BULK_MODE_BLOCKING:
			status = vchiq_blocking_bulk_transfer(handle,
				(व्योम *)data, size, VCHIQ_BULK_TRANSMIT);
			अवरोध;
		शेष:
			वापस VCHIQ_ERROR;
		पूर्ण

		/*
		 * vchiq_*_bulk_transfer() may वापस VCHIQ_RETRY, so we need
		 * to implement a retry mechanism since this function is
		 * supposed to block until queued
		 */
		अगर (status != VCHIQ_RETRY)
			अवरोध;

		msleep(1);
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL(vchiq_bulk_transmit);

क्रमागत vchiq_status vchiq_bulk_receive(अचिन्हित पूर्णांक handle, व्योम *data,
				     अचिन्हित पूर्णांक size, व्योम *userdata,
				     क्रमागत vchiq_bulk_mode mode)
अणु
	क्रमागत vchiq_status status;

	जबतक (1) अणु
		चयन (mode) अणु
		हाल VCHIQ_BULK_MODE_NOCALLBACK:
		हाल VCHIQ_BULK_MODE_CALLBACK:
			status = vchiq_bulk_transfer(handle, data, शून्य,
						     size, userdata,
						     mode, VCHIQ_BULK_RECEIVE);
			अवरोध;
		हाल VCHIQ_BULK_MODE_BLOCKING:
			status = vchiq_blocking_bulk_transfer(handle,
				(व्योम *)data, size, VCHIQ_BULK_RECEIVE);
			अवरोध;
		शेष:
			वापस VCHIQ_ERROR;
		पूर्ण

		/*
		 * vchiq_*_bulk_transfer() may वापस VCHIQ_RETRY, so we need
		 * to implement a retry mechanism since this function is
		 * supposed to block until queued
		 */
		अगर (status != VCHIQ_RETRY)
			अवरोध;

		msleep(1);
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL(vchiq_bulk_receive);

अटल क्रमागत vchiq_status
vchiq_blocking_bulk_transfer(अचिन्हित पूर्णांक handle, व्योम *data,
	अचिन्हित पूर्णांक size, क्रमागत vchiq_bulk_dir dir)
अणु
	काष्ठा vchiq_instance *instance;
	काष्ठा vchiq_service *service;
	क्रमागत vchiq_status status;
	काष्ठा bulk_रुकोer_node *रुकोer = शून्य;
	bool found = false;

	service = find_service_by_handle(handle);
	अगर (!service)
		वापस VCHIQ_ERROR;

	instance = service->instance;

	unlock_service(service);

	mutex_lock(&instance->bulk_रुकोer_list_mutex);
	list_क्रम_each_entry(रुकोer, &instance->bulk_रुकोer_list, list) अणु
		अगर (रुकोer->pid == current->pid) अणु
			list_del(&रुकोer->list);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&instance->bulk_रुकोer_list_mutex);

	अगर (found) अणु
		काष्ठा vchiq_bulk *bulk = रुकोer->bulk_रुकोer.bulk;

		अगर (bulk) अणु
			/* This thपढ़ो has an outstanding bulk transfer. */
			/* FIXME: why compare a dma address to a poपूर्णांकer? */
			अगर ((bulk->data != (dma_addr_t)(uपूर्णांकptr_t)data) ||
				(bulk->size != size)) अणु
				/*
				 * This is not a retry of the previous one.
				 * Cancel the संकेत when the transfer completes.
				 */
				spin_lock(&bulk_रुकोer_spinlock);
				bulk->userdata = शून्य;
				spin_unlock(&bulk_रुकोer_spinlock);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		रुकोer = kzalloc(माप(काष्ठा bulk_रुकोer_node), GFP_KERNEL);
		अगर (!रुकोer) अणु
			vchiq_log_error(vchiq_core_log_level,
				"%s - out of memory", __func__);
			वापस VCHIQ_ERROR;
		पूर्ण
	पूर्ण

	status = vchiq_bulk_transfer(handle, data, शून्य, size,
				     &रुकोer->bulk_रुकोer,
				     VCHIQ_BULK_MODE_BLOCKING, dir);
	अगर ((status != VCHIQ_RETRY) || fatal_संकेत_pending(current) ||
		!रुकोer->bulk_रुकोer.bulk) अणु
		काष्ठा vchiq_bulk *bulk = रुकोer->bulk_रुकोer.bulk;

		अगर (bulk) अणु
			/* Cancel the संकेत when the transfer completes. */
			spin_lock(&bulk_रुकोer_spinlock);
			bulk->userdata = शून्य;
			spin_unlock(&bulk_रुकोer_spinlock);
		पूर्ण
		kमुक्त(रुकोer);
	पूर्ण अन्यथा अणु
		रुकोer->pid = current->pid;
		mutex_lock(&instance->bulk_रुकोer_list_mutex);
		list_add(&रुकोer->list, &instance->bulk_रुकोer_list);
		mutex_unlock(&instance->bulk_रुकोer_list_mutex);
		vchiq_log_info(vchiq_arm_log_level,
				"saved bulk_waiter %pK for pid %d",
				रुकोer, current->pid);
	पूर्ण

	वापस status;
पूर्ण
/****************************************************************************
 *
 *   add_completion
 *
 ***************************************************************************/

अटल क्रमागत vchiq_status
add_completion(काष्ठा vchiq_instance *instance, क्रमागत vchiq_reason reason,
	       काष्ठा vchiq_header *header, काष्ठा user_service *user_service,
	       व्योम *bulk_userdata)
अणु
	काष्ठा vchiq_completion_data_kernel *completion;
	पूर्णांक insert;

	DEBUG_INITIALISE(g_state.local)

	insert = instance->completion_insert;
	जबतक ((insert - instance->completion_हटाओ) >= MAX_COMPLETIONS) अणु
		/* Out of space - रुको क्रम the client */
		DEBUG_TRACE(SERVICE_CALLBACK_LINE);
		vchiq_log_trace(vchiq_arm_log_level,
			"%s - completion queue full", __func__);
		DEBUG_COUNT(COMPLETION_QUEUE_FULL_COUNT);
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(
					&instance->हटाओ_event)) अणु
			vchiq_log_info(vchiq_arm_log_level,
				"service_callback interrupted");
			वापस VCHIQ_RETRY;
		पूर्ण अन्यथा अगर (instance->closing) अणु
			vchiq_log_info(vchiq_arm_log_level,
				"service_callback closing");
			वापस VCHIQ_SUCCESS;
		पूर्ण
		DEBUG_TRACE(SERVICE_CALLBACK_LINE);
	पूर्ण

	completion = &instance->completions[insert & (MAX_COMPLETIONS - 1)];

	completion->header = header;
	completion->reason = reason;
	/* N.B. service_userdata is updated जबतक processing AWAIT_COMPLETION */
	completion->service_userdata = user_service->service;
	completion->bulk_userdata = bulk_userdata;

	अगर (reason == VCHIQ_SERVICE_CLOSED) अणु
		/*
		 * Take an extra reference, to be held until
		 * this CLOSED notअगरication is delivered.
		 */
		lock_service(user_service->service);
		अगर (instance->use_बंद_delivered)
			user_service->बंद_pending = 1;
	पूर्ण

	/*
	 * A ग_लिखो barrier is needed here to ensure that the entire completion
	 * record is written out beक्रमe the insert poपूर्णांक.
	 */
	wmb();

	अगर (reason == VCHIQ_MESSAGE_AVAILABLE)
		user_service->message_available_pos = insert;

	insert++;
	instance->completion_insert = insert;

	complete(&instance->insert_event);

	वापस VCHIQ_SUCCESS;
पूर्ण

/****************************************************************************
 *
 *   service_callback
 *
 ***************************************************************************/

अटल क्रमागत vchiq_status
service_callback(क्रमागत vchiq_reason reason, काष्ठा vchiq_header *header,
		 अचिन्हित पूर्णांक handle, व्योम *bulk_userdata)
अणु
	/*
	 * How करो we ensure the callback goes to the right client?
	 * The service_user data poपूर्णांकs to a user_service record
	 * containing the original callback and the user state काष्ठाure, which
	 * contains a circular buffer क्रम completion records.
	 */
	काष्ठा user_service *user_service;
	काष्ठा vchiq_service *service;
	काष्ठा vchiq_instance *instance;
	bool skip_completion = false;

	DEBUG_INITIALISE(g_state.local)

	DEBUG_TRACE(SERVICE_CALLBACK_LINE);

	service = handle_to_service(handle);
	BUG_ON(!service);
	user_service = (काष्ठा user_service *)service->base.userdata;
	instance = user_service->instance;

	अगर (!instance || instance->closing)
		वापस VCHIQ_SUCCESS;

	vchiq_log_trace(vchiq_arm_log_level,
		"%s - service %lx(%d,%p), reason %d, header %lx, instance %lx, bulk_userdata %lx",
		__func__, (अचिन्हित दीर्घ)user_service,
		service->localport, user_service->userdata,
		reason, (अचिन्हित दीर्घ)header,
		(अचिन्हित दीर्घ)instance, (अचिन्हित दीर्घ)bulk_userdata);

	अगर (header && user_service->is_vchi) अणु
		spin_lock(&msg_queue_spinlock);
		जबतक (user_service->msg_insert ==
			(user_service->msg_हटाओ + MSG_QUEUE_SIZE)) अणु
			spin_unlock(&msg_queue_spinlock);
			DEBUG_TRACE(SERVICE_CALLBACK_LINE);
			DEBUG_COUNT(MSG_QUEUE_FULL_COUNT);
			vchiq_log_trace(vchiq_arm_log_level,
				"service_callback - msg queue full");
			/*
			 * If there is no MESSAGE_AVAILABLE in the completion
			 * queue, add one
			 */
			अगर ((user_service->message_available_pos -
				instance->completion_हटाओ) < 0) अणु
				क्रमागत vchiq_status status;

				vchiq_log_info(vchiq_arm_log_level,
					"Inserting extra MESSAGE_AVAILABLE");
				DEBUG_TRACE(SERVICE_CALLBACK_LINE);
				status = add_completion(instance, reason,
					शून्य, user_service, bulk_userdata);
				अगर (status != VCHIQ_SUCCESS) अणु
					DEBUG_TRACE(SERVICE_CALLBACK_LINE);
					वापस status;
				पूर्ण
			पूर्ण

			DEBUG_TRACE(SERVICE_CALLBACK_LINE);
			अगर (रुको_क्रम_completion_पूर्णांकerruptible(
						&user_service->हटाओ_event)) अणु
				vchiq_log_info(vchiq_arm_log_level,
					"%s interrupted", __func__);
				DEBUG_TRACE(SERVICE_CALLBACK_LINE);
				वापस VCHIQ_RETRY;
			पूर्ण अन्यथा अगर (instance->closing) अणु
				vchiq_log_info(vchiq_arm_log_level,
					"%s closing", __func__);
				DEBUG_TRACE(SERVICE_CALLBACK_LINE);
				वापस VCHIQ_ERROR;
			पूर्ण
			DEBUG_TRACE(SERVICE_CALLBACK_LINE);
			spin_lock(&msg_queue_spinlock);
		पूर्ण

		user_service->msg_queue[user_service->msg_insert &
			(MSG_QUEUE_SIZE - 1)] = header;
		user_service->msg_insert++;

		/*
		 * If there is a thपढ़ो रुकोing in DEQUEUE_MESSAGE, or अगर
		 * there is a MESSAGE_AVAILABLE in the completion queue then
		 * bypass the completion queue.
		 */
		अगर (((user_service->message_available_pos -
			instance->completion_हटाओ) >= 0) ||
			user_service->dequeue_pending) अणु
			user_service->dequeue_pending = 0;
			skip_completion = true;
		पूर्ण

		spin_unlock(&msg_queue_spinlock);
		complete(&user_service->insert_event);

		header = शून्य;
	पूर्ण
	DEBUG_TRACE(SERVICE_CALLBACK_LINE);

	अगर (skip_completion)
		वापस VCHIQ_SUCCESS;

	वापस add_completion(instance, reason, header, user_service,
		bulk_userdata);
पूर्ण

/****************************************************************************
 *
 *   user_service_मुक्त
 *
 ***************************************************************************/
अटल व्योम
user_service_मुक्त(व्योम *userdata)
अणु
	kमुक्त(userdata);
पूर्ण

/****************************************************************************
 *
 *   बंद_delivered
 *
 ***************************************************************************/
अटल व्योम बंद_delivered(काष्ठा user_service *user_service)
अणु
	vchiq_log_info(vchiq_arm_log_level,
		"%s(handle=%x)",
		__func__, user_service->service->handle);

	अगर (user_service->बंद_pending) अणु
		/* Allow the underlying service to be culled */
		unlock_service(user_service->service);

		/* Wake the user-thपढ़ो blocked in बंद_ or हटाओ_service */
		complete(&user_service->बंद_event);

		user_service->बंद_pending = 0;
	पूर्ण
पूर्ण

काष्ठा vchiq_io_copy_callback_context अणु
	काष्ठा vchiq_element *element;
	माप_प्रकार element_offset;
	अचिन्हित दीर्घ elements_to_go;
पूर्ण;

अटल sमाप_प्रकार vchiq_ioc_copy_element_data(व्योम *context, व्योम *dest,
					   माप_प्रकार offset, माप_प्रकार maxsize)
अणु
	काष्ठा vchiq_io_copy_callback_context *cc = context;
	माप_प्रकार total_bytes_copied = 0;
	माप_प्रकार bytes_this_round;

	जबतक (total_bytes_copied < maxsize) अणु
		अगर (!cc->elements_to_go)
			वापस total_bytes_copied;

		अगर (!cc->element->size) अणु
			cc->elements_to_go--;
			cc->element++;
			cc->element_offset = 0;
			जारी;
		पूर्ण

		bytes_this_round = min(cc->element->size - cc->element_offset,
				       maxsize - total_bytes_copied);

		अगर (copy_from_user(dest + total_bytes_copied,
				  cc->element->data + cc->element_offset,
				  bytes_this_round))
			वापस -EFAULT;

		cc->element_offset += bytes_this_round;
		total_bytes_copied += bytes_this_round;

		अगर (cc->element_offset == cc->element->size) अणु
			cc->elements_to_go--;
			cc->element++;
			cc->element_offset = 0;
		पूर्ण
	पूर्ण

	वापस maxsize;
पूर्ण

/**************************************************************************
 *
 *   vchiq_ioc_queue_message
 *
 **************************************************************************/
अटल पूर्णांक
vchiq_ioc_queue_message(अचिन्हित पूर्णांक handle,
			काष्ठा vchiq_element *elements,
			अचिन्हित दीर्घ count)
अणु
	काष्ठा vchiq_io_copy_callback_context context;
	क्रमागत vchiq_status status = VCHIQ_SUCCESS;
	अचिन्हित दीर्घ i;
	माप_प्रकार total_size = 0;

	context.element = elements;
	context.element_offset = 0;
	context.elements_to_go = count;

	क्रम (i = 0; i < count; i++) अणु
		अगर (!elements[i].data && elements[i].size != 0)
			वापस -EFAULT;

		total_size += elements[i].size;
	पूर्ण

	status = vchiq_queue_message(handle, vchiq_ioc_copy_element_data,
				     &context, total_size);

	अगर (status == VCHIQ_ERROR)
		वापस -EIO;
	अन्यथा अगर (status == VCHIQ_RETRY)
		वापस -EINTR;
	वापस 0;
पूर्ण

अटल पूर्णांक vchiq_ioc_create_service(काष्ठा vchiq_instance *instance,
				    काष्ठा vchiq_create_service *args)
अणु
	काष्ठा user_service *user_service = शून्य;
	काष्ठा vchiq_service *service;
	क्रमागत vchiq_status status = VCHIQ_SUCCESS;
	काष्ठा vchiq_service_params_kernel params;
	पूर्णांक srvstate;

	user_service = kदो_स्मृति(माप(*user_service), GFP_KERNEL);
	अगर (!user_service)
		वापस -ENOMEM;

	अगर (args->is_खोलो) अणु
		अगर (!instance->connected) अणु
			kमुक्त(user_service);
			वापस -ENOTCONN;
		पूर्ण
		srvstate = VCHIQ_SRVSTATE_OPENING;
	पूर्ण अन्यथा अणु
		srvstate = instance->connected ?
			 VCHIQ_SRVSTATE_LISTENING : VCHIQ_SRVSTATE_HIDDEN;
	पूर्ण

	params = (काष्ठा vchiq_service_params_kernel) अणु
		.fourcc   = args->params.fourcc,
		.callback = service_callback,
		.userdata = user_service,
		.version  = args->params.version,
		.version_min = args->params.version_min,
	पूर्ण;
	service = vchiq_add_service_पूर्णांकernal(instance->state, &params,
					     srvstate, instance,
					     user_service_मुक्त);
	अगर (!service) अणु
		kमुक्त(user_service);
		वापस -EEXIST;
	पूर्ण

	user_service->service = service;
	user_service->userdata = args->params.userdata;
	user_service->instance = instance;
	user_service->is_vchi = (args->is_vchi != 0);
	user_service->dequeue_pending = 0;
	user_service->बंद_pending = 0;
	user_service->message_available_pos = instance->completion_हटाओ - 1;
	user_service->msg_insert = 0;
	user_service->msg_हटाओ = 0;
	init_completion(&user_service->insert_event);
	init_completion(&user_service->हटाओ_event);
	init_completion(&user_service->बंद_event);

	अगर (args->is_खोलो) अणु
		status = vchiq_खोलो_service_पूर्णांकernal(service, instance->pid);
		अगर (status != VCHIQ_SUCCESS) अणु
			vchiq_हटाओ_service(service->handle);
			वापस (status == VCHIQ_RETRY) ?
				-EINTR : -EIO;
		पूर्ण
	पूर्ण
	args->handle = service->handle;

	वापस 0;
पूर्ण

अटल पूर्णांक vchiq_ioc_dequeue_message(काष्ठा vchiq_instance *instance,
				     काष्ठा vchiq_dequeue_message *args)
अणु
	काष्ठा user_service *user_service;
	काष्ठा vchiq_service *service;
	काष्ठा vchiq_header *header;
	पूर्णांक ret;

	DEBUG_INITIALISE(g_state.local)
	DEBUG_TRACE(DEQUEUE_MESSAGE_LINE);
	service = find_service_क्रम_instance(instance, args->handle);
	अगर (!service)
		वापस -EINVAL;

	user_service = (काष्ठा user_service *)service->base.userdata;
	अगर (user_service->is_vchi == 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	spin_lock(&msg_queue_spinlock);
	अगर (user_service->msg_हटाओ == user_service->msg_insert) अणु
		अगर (!args->blocking) अणु
			spin_unlock(&msg_queue_spinlock);
			DEBUG_TRACE(DEQUEUE_MESSAGE_LINE);
			ret = -EWOULDBLOCK;
			जाओ out;
		पूर्ण
		user_service->dequeue_pending = 1;
		ret = 0;
		करो अणु
			spin_unlock(&msg_queue_spinlock);
			DEBUG_TRACE(DEQUEUE_MESSAGE_LINE);
			अगर (रुको_क्रम_completion_पूर्णांकerruptible(
				&user_service->insert_event)) अणु
				vchiq_log_info(vchiq_arm_log_level,
					"DEQUEUE_MESSAGE interrupted");
				ret = -EINTR;
				अवरोध;
			पूर्ण
			spin_lock(&msg_queue_spinlock);
		पूर्ण जबतक (user_service->msg_हटाओ ==
			user_service->msg_insert);

		अगर (ret)
			जाओ out;
	पूर्ण

	BUG_ON((पूर्णांक)(user_service->msg_insert -
		user_service->msg_हटाओ) < 0);

	header = user_service->msg_queue[user_service->msg_हटाओ &
		(MSG_QUEUE_SIZE - 1)];
	user_service->msg_हटाओ++;
	spin_unlock(&msg_queue_spinlock);

	complete(&user_service->हटाओ_event);
	अगर (!header) अणु
		ret = -ENOTCONN;
	पूर्ण अन्यथा अगर (header->size <= args->bufsize) अणु
		/* Copy to user space अगर msgbuf is not शून्य */
		अगर (!args->buf || (copy_to_user(args->buf,
					header->data, header->size) == 0)) अणु
			ret = header->size;
			vchiq_release_message(service->handle, header);
		पूर्ण अन्यथा
			ret = -EFAULT;
	पूर्ण अन्यथा अणु
		vchiq_log_error(vchiq_arm_log_level,
			"header %pK: bufsize %x < size %x",
			header, args->bufsize, header->size);
		WARN(1, "invalid size\n");
		ret = -EMSGSIZE;
	पूर्ण
	DEBUG_TRACE(DEQUEUE_MESSAGE_LINE);
out:
	unlock_service(service);
	वापस ret;
पूर्ण

अटल पूर्णांक vchiq_irq_queue_bulk_tx_rx(काष्ठा vchiq_instance *instance,
				      काष्ठा vchiq_queue_bulk_transfer *args,
				      क्रमागत vchiq_bulk_dir dir,
				      क्रमागत vchiq_bulk_mode __user *mode)
अणु
	काष्ठा vchiq_service *service;
	काष्ठा bulk_रुकोer_node *रुकोer = शून्य;
	bool found = false;
	व्योम *userdata;
	पूर्णांक status = 0;
	पूर्णांक ret;

	service = find_service_क्रम_instance(instance, args->handle);
	अगर (!service)
		वापस -EINVAL;

	अगर (args->mode == VCHIQ_BULK_MODE_BLOCKING) अणु
		रुकोer = kzalloc(माप(काष्ठा bulk_रुकोer_node),
			GFP_KERNEL);
		अगर (!रुकोer) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		userdata = &रुकोer->bulk_रुकोer;
	पूर्ण अन्यथा अगर (args->mode == VCHIQ_BULK_MODE_WAITING) अणु
		mutex_lock(&instance->bulk_रुकोer_list_mutex);
		list_क्रम_each_entry(रुकोer, &instance->bulk_रुकोer_list,
				    list) अणु
			अगर (रुकोer->pid == current->pid) अणु
				list_del(&रुकोer->list);
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&instance->bulk_रुकोer_list_mutex);
		अगर (!found) अणु
			vchiq_log_error(vchiq_arm_log_level,
				"no bulk_waiter found for pid %d",
				current->pid);
			ret = -ESRCH;
			जाओ out;
		पूर्ण
		vchiq_log_info(vchiq_arm_log_level,
			"found bulk_waiter %pK for pid %d", रुकोer,
			current->pid);
		userdata = &रुकोer->bulk_रुकोer;
	पूर्ण अन्यथा अणु
		userdata = args->userdata;
	पूर्ण

	status = vchiq_bulk_transfer(args->handle, शून्य, args->data, args->size,
				     userdata, args->mode, dir);

	अगर (!रुकोer) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर ((status != VCHIQ_RETRY) || fatal_संकेत_pending(current) ||
		!रुकोer->bulk_रुकोer.bulk) अणु
		अगर (रुकोer->bulk_रुकोer.bulk) अणु
			/* Cancel the संकेत when the transfer completes. */
			spin_lock(&bulk_रुकोer_spinlock);
			रुकोer->bulk_रुकोer.bulk->userdata = शून्य;
			spin_unlock(&bulk_रुकोer_spinlock);
		पूर्ण
		kमुक्त(रुकोer);
		ret = 0;
	पूर्ण अन्यथा अणु
		स्थिर क्रमागत vchiq_bulk_mode mode_रुकोing =
			VCHIQ_BULK_MODE_WAITING;
		रुकोer->pid = current->pid;
		mutex_lock(&instance->bulk_रुकोer_list_mutex);
		list_add(&रुकोer->list, &instance->bulk_रुकोer_list);
		mutex_unlock(&instance->bulk_रुकोer_list_mutex);
		vchiq_log_info(vchiq_arm_log_level,
			"saved bulk_waiter %pK for pid %d",
			रुकोer, current->pid);

		ret = put_user(mode_रुकोing, mode);
	पूर्ण
out:
	unlock_service(service);
	अगर (ret)
		वापस ret;
	अन्यथा अगर (status == VCHIQ_ERROR)
		वापस -EIO;
	अन्यथा अगर (status == VCHIQ_RETRY)
		वापस -EINTR;
	वापस 0;
पूर्ण

/* पढ़ो a user poपूर्णांकer value from an array poपूर्णांकers in user space */
अटल अंतरभूत पूर्णांक vchiq_get_user_ptr(व्योम __user **buf, व्योम __user *ubuf, पूर्णांक index)
अणु
	पूर्णांक ret;

	अगर (in_compat_syscall()) अणु
		compat_uptr_t ptr32;
		compat_uptr_t __user *uptr = ubuf;
		ret = get_user(ptr32, uptr + index);
		अगर (ret)
			वापस ret;

		*buf = compat_ptr(ptr32);
	पूर्ण अन्यथा अणु
		uपूर्णांकptr_t ptr, __user *uptr = ubuf;
		ret = get_user(ptr, uptr + index);

		अगर (ret)
			वापस ret;

		*buf = (व्योम __user *)ptr;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा vchiq_completion_data32 अणु
	क्रमागत vchiq_reason reason;
	compat_uptr_t header;
	compat_uptr_t service_userdata;
	compat_uptr_t bulk_userdata;
पूर्ण;

अटल पूर्णांक vchiq_put_completion(काष्ठा vchiq_completion_data __user *buf,
				काष्ठा vchiq_completion_data *completion,
				पूर्णांक index)
अणु
	काष्ठा vchiq_completion_data32 __user *buf32 = (व्योम __user *)buf;

	अगर (in_compat_syscall()) अणु
		काष्ठा vchiq_completion_data32 पंचांगp = अणु
			.reason		  = completion->reason,
			.header		  = ptr_to_compat(completion->header),
			.service_userdata = ptr_to_compat(completion->service_userdata),
			.bulk_userdata	  = ptr_to_compat(completion->bulk_userdata),
		पूर्ण;
		अगर (copy_to_user(&buf32[index], &पंचांगp, माप(पंचांगp)))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(&buf[index], completion, माप(*completion)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vchiq_ioc_aरुको_completion(काष्ठा vchiq_instance *instance,
				      काष्ठा vchiq_aरुको_completion *args,
				      पूर्णांक __user *msgbufcountp)
अणु
	पूर्णांक msgbufcount;
	पूर्णांक हटाओ;
	पूर्णांक ret;

	DEBUG_INITIALISE(g_state.local)

	DEBUG_TRACE(AWAIT_COMPLETION_LINE);
	अगर (!instance->connected) अणु
		वापस -ENOTCONN;
	पूर्ण

	mutex_lock(&instance->completion_mutex);

	DEBUG_TRACE(AWAIT_COMPLETION_LINE);
	जबतक ((instance->completion_हटाओ ==
		instance->completion_insert)
		&& !instance->closing) अणु
		पूर्णांक rc;

		DEBUG_TRACE(AWAIT_COMPLETION_LINE);
		mutex_unlock(&instance->completion_mutex);
		rc = रुको_क्रम_completion_पूर्णांकerruptible(
					&instance->insert_event);
		mutex_lock(&instance->completion_mutex);
		अगर (rc) अणु
			DEBUG_TRACE(AWAIT_COMPLETION_LINE);
			vchiq_log_info(vchiq_arm_log_level,
				"AWAIT_COMPLETION interrupted");
			ret = -EINTR;
			जाओ out;
		पूर्ण
	पूर्ण
	DEBUG_TRACE(AWAIT_COMPLETION_LINE);

	msgbufcount = args->msgbufcount;
	हटाओ = instance->completion_हटाओ;

	क्रम (ret = 0; ret < args->count; ret++) अणु
		काष्ठा vchiq_completion_data_kernel *completion;
		काष्ठा vchiq_completion_data user_completion;
		काष्ठा vchiq_service *service;
		काष्ठा user_service *user_service;
		काष्ठा vchiq_header *header;

		अगर (हटाओ == instance->completion_insert)
			अवरोध;

		completion = &instance->completions[
			हटाओ & (MAX_COMPLETIONS - 1)];

		/*
		 * A पढ़ो memory barrier is needed to stop
		 * prefetch of a stale completion record
		 */
		rmb();

		service = completion->service_userdata;
		user_service = service->base.userdata;

		स_रखो(&user_completion, 0, माप(user_completion));
		user_completion = (काष्ठा vchiq_completion_data) अणु
			.reason = completion->reason,
			.service_userdata = user_service->userdata,
		पूर्ण;

		header = completion->header;
		अगर (header) अणु
			व्योम __user *msgbuf;
			पूर्णांक msglen;

			msglen = header->size + माप(काष्ठा vchiq_header);
			/* This must be a VCHIQ-style service */
			अगर (args->msgbufsize < msglen) अणु
				vchiq_log_error(vchiq_arm_log_level,
					"header %pK: msgbufsize %x < msglen %x",
					header, args->msgbufsize, msglen);
				WARN(1, "invalid message size\n");
				अगर (ret == 0)
					ret = -EMSGSIZE;
				अवरोध;
			पूर्ण
			अगर (msgbufcount <= 0)
				/* Stall here क्रम lack of a buffer क्रम the message. */
				अवरोध;
			/* Get the poपूर्णांकer from user space */
			msgbufcount--;
			अगर (vchiq_get_user_ptr(&msgbuf, args->msgbufs,
						msgbufcount)) अणु
				अगर (ret == 0)
					ret = -EFAULT;
				अवरोध;
			पूर्ण

			/* Copy the message to user space */
			अगर (copy_to_user(msgbuf, header, msglen)) अणु
				अगर (ret == 0)
					ret = -EFAULT;
				अवरोध;
			पूर्ण

			/* Now it has been copied, the message can be released. */
			vchiq_release_message(service->handle, header);

			/* The completion must poपूर्णांक to the msgbuf. */
			user_completion.header = msgbuf;
		पूर्ण

		अगर ((completion->reason == VCHIQ_SERVICE_CLOSED) &&
		    !instance->use_बंद_delivered)
			unlock_service(service);

		/*
		 * FIXME: address space mismatch, करोes bulk_userdata
		 * actually poपूर्णांक to user or kernel memory?
		 */
		user_completion.bulk_userdata = completion->bulk_userdata;

		अगर (vchiq_put_completion(args->buf, &user_completion, ret)) अणु
			अगर (ret == 0)
				ret = -EFAULT;
			अवरोध;
		पूर्ण

		/*
		 * Ensure that the above copy has completed
		 * beक्रमe advancing the हटाओ poपूर्णांकer.
		 */
		mb();
		हटाओ++;
		instance->completion_हटाओ = हटाओ;
	पूर्ण

	अगर (msgbufcount != args->msgbufcount) अणु
		अगर (put_user(msgbufcount, msgbufcountp))
			ret = -EFAULT;
	पूर्ण
out:
	अगर (ret)
		complete(&instance->हटाओ_event);
	mutex_unlock(&instance->completion_mutex);
	DEBUG_TRACE(AWAIT_COMPLETION_LINE);

	वापस ret;
पूर्ण

/****************************************************************************
 *
 *   vchiq_ioctl
 *
 ***************************************************************************/
अटल दीर्घ
vchiq_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vchiq_instance *instance = file->निजी_data;
	क्रमागत vchiq_status status = VCHIQ_SUCCESS;
	काष्ठा vchiq_service *service = शून्य;
	दीर्घ ret = 0;
	पूर्णांक i, rc;

	vchiq_log_trace(vchiq_arm_log_level,
		"%s - instance %pK, cmd %s, arg %lx",
		__func__, instance,
		((_IOC_TYPE(cmd) == VCHIQ_IOC_MAGIC) &&
		(_IOC_NR(cmd) <= VCHIQ_IOC_MAX)) ?
		ioctl_names[_IOC_NR(cmd)] : "<invalid>", arg);

	चयन (cmd) अणु
	हाल VCHIQ_IOC_SHUTDOWN:
		अगर (!instance->connected)
			अवरोध;

		/* Remove all services */
		i = 0;
		जबतक ((service = next_service_by_instance(instance->state,
			instance, &i))) अणु
			status = vchiq_हटाओ_service(service->handle);
			unlock_service(service);
			अगर (status != VCHIQ_SUCCESS)
				अवरोध;
		पूर्ण
		service = शून्य;

		अगर (status == VCHIQ_SUCCESS) अणु
			/* Wake the completion thपढ़ो and ask it to निकास */
			instance->closing = 1;
			complete(&instance->insert_event);
		पूर्ण

		अवरोध;

	हाल VCHIQ_IOC_CONNECT:
		अगर (instance->connected) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		rc = mutex_lock_समाप्तable(&instance->state->mutex);
		अगर (rc) अणु
			vchiq_log_error(vchiq_arm_log_level,
				"vchiq: connect: could not lock mutex for state %d: %d",
				instance->state->id, rc);
			ret = -EINTR;
			अवरोध;
		पूर्ण
		status = vchiq_connect_पूर्णांकernal(instance->state, instance);
		mutex_unlock(&instance->state->mutex);

		अगर (status == VCHIQ_SUCCESS)
			instance->connected = 1;
		अन्यथा
			vchiq_log_error(vchiq_arm_log_level,
				"vchiq: could not connect: %d", status);
		अवरोध;

	हाल VCHIQ_IOC_CREATE_SERVICE: अणु
		काष्ठा vchiq_create_service __user *argp;
		काष्ठा vchiq_create_service args;

		argp = (व्योम __user *)arg;
		अगर (copy_from_user(&args, argp, माप(args))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret = vchiq_ioc_create_service(instance, &args);
		अगर (ret < 0)
			अवरोध;

		अगर (put_user(args.handle, &argp->handle)) अणु
			vchiq_हटाओ_service(args.handle);
			ret = -EFAULT;
		पूर्ण
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_CLOSE_SERVICE:
	हाल VCHIQ_IOC_REMOVE_SERVICE: अणु
		अचिन्हित पूर्णांक handle = (अचिन्हित पूर्णांक)arg;
		काष्ठा user_service *user_service;

		service = find_service_क्रम_instance(instance, handle);
		अगर (!service) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		user_service = service->base.userdata;

		/*
		 * बंद_pending is false on first entry, and when the
		 * रुको in vchiq_बंद_service has been पूर्णांकerrupted.
		 */
		अगर (!user_service->बंद_pending) अणु
			status = (cmd == VCHIQ_IOC_CLOSE_SERVICE) ?
				 vchiq_बंद_service(service->handle) :
				 vchiq_हटाओ_service(service->handle);
			अगर (status != VCHIQ_SUCCESS)
				अवरोध;
		पूर्ण

		/*
		 * बंद_pending is true once the underlying service
		 * has been बंदd until the client library calls the
		 * CLOSE_DELIVERED ioctl, संकेतling बंद_event.
		 */
		अगर (user_service->बंद_pending &&
			रुको_क्रम_completion_पूर्णांकerruptible(
				&user_service->बंद_event))
			status = VCHIQ_RETRY;
		अवरोध;
	पूर्ण

	हाल VCHIQ_IOC_USE_SERVICE:
	हाल VCHIQ_IOC_RELEASE_SERVICE:	अणु
		अचिन्हित पूर्णांक handle = (अचिन्हित पूर्णांक)arg;

		service = find_service_क्रम_instance(instance, handle);
		अगर (service) अणु
			status = (cmd == VCHIQ_IOC_USE_SERVICE)	?
				vchiq_use_service_पूर्णांकernal(service) :
				vchiq_release_service_पूर्णांकernal(service);
			अगर (status != VCHIQ_SUCCESS) अणु
				vchiq_log_error(vchiq_susp_log_level,
					"%s: cmd %s returned error %d for service %c%c%c%c:%03d",
					__func__,
					(cmd == VCHIQ_IOC_USE_SERVICE) ?
						"VCHIQ_IOC_USE_SERVICE" :
						"VCHIQ_IOC_RELEASE_SERVICE",
					status,
					VCHIQ_FOURCC_AS_4CHARS(
						service->base.fourcc),
					service->client_id);
				ret = -EINVAL;
			पूर्ण
		पूर्ण अन्यथा
			ret = -EINVAL;
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_QUEUE_MESSAGE: अणु
		काष्ठा vchiq_queue_message args;

		अगर (copy_from_user(&args, (स्थिर व्योम __user *)arg,
				   माप(args))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		service = find_service_क्रम_instance(instance, args.handle);

		अगर (service && (args.count <= MAX_ELEMENTS)) अणु
			/* Copy elements पूर्णांकo kernel space */
			काष्ठा vchiq_element elements[MAX_ELEMENTS];

			अगर (copy_from_user(elements, args.elements,
				args.count * माप(काष्ठा vchiq_element)) == 0)
				ret = vchiq_ioc_queue_message(args.handle, elements,
							      args.count);
			अन्यथा
				ret = -EFAULT;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_QUEUE_BULK_TRANSMIT:
	हाल VCHIQ_IOC_QUEUE_BULK_RECEIVE: अणु
		काष्ठा vchiq_queue_bulk_transfer args;
		काष्ठा vchiq_queue_bulk_transfer __user *argp;

		क्रमागत vchiq_bulk_dir dir =
			(cmd == VCHIQ_IOC_QUEUE_BULK_TRANSMIT) ?
			VCHIQ_BULK_TRANSMIT : VCHIQ_BULK_RECEIVE;

		argp = (व्योम __user *)arg;
		अगर (copy_from_user(&args, argp, माप(args))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret = vchiq_irq_queue_bulk_tx_rx(instance, &args,
						 dir, &argp->mode);
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_AWAIT_COMPLETION: अणु
		काष्ठा vchiq_aरुको_completion args;
		काष्ठा vchiq_aरुको_completion __user *argp;

		argp = (व्योम __user *)arg;
		अगर (copy_from_user(&args, argp, माप(args))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret = vchiq_ioc_aरुको_completion(instance, &args,
						 &argp->msgbufcount);
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_DEQUEUE_MESSAGE: अणु
		काष्ठा vchiq_dequeue_message args;

		अगर (copy_from_user(&args, (स्थिर व्योम __user *)arg,
				   माप(args))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret = vchiq_ioc_dequeue_message(instance, &args);
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_GET_CLIENT_ID: अणु
		अचिन्हित पूर्णांक handle = (अचिन्हित पूर्णांक)arg;

		ret = vchiq_get_client_id(handle);
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_GET_CONFIG: अणु
		काष्ठा vchiq_get_config args;
		काष्ठा vchiq_config config;

		अगर (copy_from_user(&args, (स्थिर व्योम __user *)arg,
				   माप(args))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (args.config_size > माप(config)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		vchiq_get_config(&config);
		अगर (copy_to_user(args.pconfig, &config, args.config_size)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_SET_SERVICE_OPTION: अणु
		काष्ठा vchiq_set_service_option args;

		अगर (copy_from_user(&args, (स्थिर व्योम __user *)arg,
				   माप(args))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		service = find_service_क्रम_instance(instance, args.handle);
		अगर (!service) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		status = vchiq_set_service_option(
				args.handle, args.option, args.value);
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_LIB_VERSION: अणु
		अचिन्हित पूर्णांक lib_version = (अचिन्हित पूर्णांक)arg;

		अगर (lib_version < VCHIQ_VERSION_MIN)
			ret = -EINVAL;
		अन्यथा अगर (lib_version >= VCHIQ_VERSION_CLOSE_DELIVERED)
			instance->use_बंद_delivered = 1;
	पूर्ण अवरोध;

	हाल VCHIQ_IOC_CLOSE_DELIVERED: अणु
		अचिन्हित पूर्णांक handle = (अचिन्हित पूर्णांक)arg;

		service = find_बंदd_service_क्रम_instance(instance, handle);
		अगर (service) अणु
			काष्ठा user_service *user_service =
				(काष्ठा user_service *)service->base.userdata;
			बंद_delivered(user_service);
		पूर्ण अन्यथा
			ret = -EINVAL;
	पूर्ण अवरोध;

	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण

	अगर (service)
		unlock_service(service);

	अगर (ret == 0) अणु
		अगर (status == VCHIQ_ERROR)
			ret = -EIO;
		अन्यथा अगर (status == VCHIQ_RETRY)
			ret = -EINTR;
	पूर्ण

	अगर ((status == VCHIQ_SUCCESS) && (ret < 0) && (ret != -EINTR) &&
		(ret != -EWOULDBLOCK))
		vchiq_log_info(vchiq_arm_log_level,
			"  ioctl instance %pK, cmd %s -> status %d, %ld",
			instance,
			(_IOC_NR(cmd) <= VCHIQ_IOC_MAX) ?
				ioctl_names[_IOC_NR(cmd)] :
				"<invalid>",
			status, ret);
	अन्यथा
		vchiq_log_trace(vchiq_arm_log_level,
			"  ioctl instance %pK, cmd %s -> status %d, %ld",
			instance,
			(_IOC_NR(cmd) <= VCHIQ_IOC_MAX) ?
				ioctl_names[_IOC_NR(cmd)] :
				"<invalid>",
			status, ret);

	वापस ret;
पूर्ण

#अगर defined(CONFIG_COMPAT)

काष्ठा vchiq_service_params32 अणु
	पूर्णांक fourcc;
	compat_uptr_t callback;
	compat_uptr_t userdata;
	लघु version; /* Increment क्रम non-trivial changes */
	लघु version_min; /* Update क्रम incompatible changes */
पूर्ण;

काष्ठा vchiq_create_service32 अणु
	काष्ठा vchiq_service_params32 params;
	पूर्णांक is_खोलो;
	पूर्णांक is_vchi;
	अचिन्हित पूर्णांक handle; /* OUT */
पूर्ण;

#घोषणा VCHIQ_IOC_CREATE_SERVICE32 \
	_IOWR(VCHIQ_IOC_MAGIC, 2, काष्ठा vchiq_create_service32)

अटल दीर्घ
vchiq_compat_ioctl_create_service(
	काष्ठा file *file,
	अचिन्हित पूर्णांक cmd,
	काष्ठा vchiq_create_service32 __user *ptrargs32)
अणु
	काष्ठा vchiq_create_service args;
	काष्ठा vchiq_create_service32 args32;
	दीर्घ ret;

	अगर (copy_from_user(&args32, ptrargs32, माप(args32)))
		वापस -EFAULT;

	args = (काष्ठा vchiq_create_service) अणु
		.params = अणु
			.fourcc	     = args32.params.fourcc,
			.callback    = compat_ptr(args32.params.callback),
			.userdata    = compat_ptr(args32.params.userdata),
			.version     = args32.params.version,
			.version_min = args32.params.version_min,
		पूर्ण,
		.is_खोलो = args32.is_खोलो,
		.is_vchi = args32.is_vchi,
		.handle  = args32.handle,
	पूर्ण;

	ret = vchiq_ioc_create_service(file->निजी_data, &args);
	अगर (ret < 0)
		वापस ret;

	अगर (put_user(args.handle, &ptrargs32->handle)) अणु
		vchiq_हटाओ_service(args.handle);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा vchiq_element32 अणु
	compat_uptr_t data;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा vchiq_queue_message32 अणु
	अचिन्हित पूर्णांक handle;
	अचिन्हित पूर्णांक count;
	compat_uptr_t elements;
पूर्ण;

#घोषणा VCHIQ_IOC_QUEUE_MESSAGE32 \
	_IOW(VCHIQ_IOC_MAGIC,  4, काष्ठा vchiq_queue_message32)

अटल दीर्घ
vchiq_compat_ioctl_queue_message(काष्ठा file *file,
				 अचिन्हित पूर्णांक cmd,
				 काष्ठा vchiq_queue_message32 __user *arg)
अणु
	काष्ठा vchiq_queue_message args;
	काष्ठा vchiq_queue_message32 args32;
	काष्ठा vchiq_service *service;
	पूर्णांक ret;

	अगर (copy_from_user(&args32, arg, माप(args32)))
		वापस -EFAULT;

	args = (काष्ठा vchiq_queue_message) अणु
		.handle   = args32.handle,
		.count    = args32.count,
		.elements = compat_ptr(args32.elements),
	पूर्ण;

	अगर (args32.count > MAX_ELEMENTS)
		वापस -EINVAL;

	service = find_service_क्रम_instance(file->निजी_data, args.handle);
	अगर (!service)
		वापस -EINVAL;

	अगर (args32.elements && args32.count) अणु
		काष्ठा vchiq_element32 element32[MAX_ELEMENTS];
		काष्ठा vchiq_element elements[MAX_ELEMENTS];
		अचिन्हित पूर्णांक count;

		अगर (copy_from_user(&element32, args.elements,
				   माप(element32))) अणु
			unlock_service(service);
			वापस -EFAULT;
		पूर्ण

		क्रम (count = 0; count < args32.count; count++) अणु
			elements[count].data =
				compat_ptr(element32[count].data);
			elements[count].size = element32[count].size;
		पूर्ण
		ret = vchiq_ioc_queue_message(args.handle, elements,
					      args.count);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	unlock_service(service);

	वापस ret;
पूर्ण

काष्ठा vchiq_queue_bulk_transfer32 अणु
	अचिन्हित पूर्णांक handle;
	compat_uptr_t data;
	अचिन्हित पूर्णांक size;
	compat_uptr_t userdata;
	क्रमागत vchiq_bulk_mode mode;
पूर्ण;

#घोषणा VCHIQ_IOC_QUEUE_BULK_TRANSMIT32 \
	_IOWR(VCHIQ_IOC_MAGIC, 5, काष्ठा vchiq_queue_bulk_transfer32)
#घोषणा VCHIQ_IOC_QUEUE_BULK_RECEIVE32 \
	_IOWR(VCHIQ_IOC_MAGIC, 6, काष्ठा vchiq_queue_bulk_transfer32)

अटल दीर्घ
vchiq_compat_ioctl_queue_bulk(काष्ठा file *file,
			      अचिन्हित पूर्णांक cmd,
			      काष्ठा vchiq_queue_bulk_transfer32 __user *argp)
अणु
	काष्ठा vchiq_queue_bulk_transfer32 args32;
	काष्ठा vchiq_queue_bulk_transfer args;
	क्रमागत vchiq_bulk_dir dir = (cmd == VCHIQ_IOC_QUEUE_BULK_TRANSMIT32) ?
				  VCHIQ_BULK_TRANSMIT : VCHIQ_BULK_RECEIVE;

	अगर (copy_from_user(&args32, argp, माप(args32)))
		वापस -EFAULT;

	args = (काष्ठा vchiq_queue_bulk_transfer) अणु
		.handle   = args32.handle,
		.data	  = compat_ptr(args32.data),
		.size	  = args32.size,
		.userdata = compat_ptr(args32.userdata),
		.mode	  = args32.mode,
	पूर्ण;

	वापस vchiq_irq_queue_bulk_tx_rx(file->निजी_data, &args,
					  dir, &argp->mode);
पूर्ण

काष्ठा vchiq_aरुको_completion32 अणु
	अचिन्हित पूर्णांक count;
	compat_uptr_t buf;
	अचिन्हित पूर्णांक msgbufsize;
	अचिन्हित पूर्णांक msgbufcount; /* IN/OUT */
	compat_uptr_t msgbufs;
पूर्ण;

#घोषणा VCHIQ_IOC_AWAIT_COMPLETION32 \
	_IOWR(VCHIQ_IOC_MAGIC, 7, काष्ठा vchiq_aरुको_completion32)

अटल दीर्घ
vchiq_compat_ioctl_aरुको_completion(काष्ठा file *file,
				    अचिन्हित पूर्णांक cmd,
				    काष्ठा vchiq_aरुको_completion32 __user *argp)
अणु
	काष्ठा vchiq_aरुको_completion args;
	काष्ठा vchiq_aरुको_completion32 args32;

	अगर (copy_from_user(&args32, argp, माप(args32)))
		वापस -EFAULT;

	args = (काष्ठा vchiq_aरुको_completion) अणु
		.count		= args32.count,
		.buf		= compat_ptr(args32.buf),
		.msgbufsize	= args32.msgbufsize,
		.msgbufcount	= args32.msgbufcount,
		.msgbufs	= compat_ptr(args32.msgbufs),
	पूर्ण;

	वापस vchiq_ioc_aरुको_completion(file->निजी_data, &args,
					  &argp->msgbufcount);
पूर्ण

काष्ठा vchiq_dequeue_message32 अणु
	अचिन्हित पूर्णांक handle;
	पूर्णांक blocking;
	अचिन्हित पूर्णांक bufsize;
	compat_uptr_t buf;
पूर्ण;

#घोषणा VCHIQ_IOC_DEQUEUE_MESSAGE32 \
	_IOWR(VCHIQ_IOC_MAGIC, 8, काष्ठा vchiq_dequeue_message32)

अटल दीर्घ
vchiq_compat_ioctl_dequeue_message(काष्ठा file *file,
				   अचिन्हित पूर्णांक cmd,
				   काष्ठा vchiq_dequeue_message32 __user *arg)
अणु
	काष्ठा vchiq_dequeue_message32 args32;
	काष्ठा vchiq_dequeue_message args;

	अगर (copy_from_user(&args32, arg, माप(args32)))
		वापस -EFAULT;

	args = (काष्ठा vchiq_dequeue_message) अणु
		.handle		= args32.handle,
		.blocking	= args32.blocking,
		.bufsize	= args32.bufsize,
		.buf		= compat_ptr(args32.buf),
	पूर्ण;

	वापस vchiq_ioc_dequeue_message(file->निजी_data, &args);
पूर्ण

काष्ठा vchiq_get_config32 अणु
	अचिन्हित पूर्णांक config_size;
	compat_uptr_t pconfig;
पूर्ण;

#घोषणा VCHIQ_IOC_GET_CONFIG32 \
	_IOWR(VCHIQ_IOC_MAGIC, 10, काष्ठा vchiq_get_config32)

अटल दीर्घ
vchiq_compat_ioctl_get_config(काष्ठा file *file,
			      अचिन्हित पूर्णांक cmd,
			      काष्ठा vchiq_get_config32 __user *arg)
अणु
	काष्ठा vchiq_get_config32 args32;
	काष्ठा vchiq_config config;
	व्योम __user *ptr;

	अगर (copy_from_user(&args32, arg, माप(args32)))
		वापस -EFAULT;
	अगर (args32.config_size > माप(config))
		वापस -EINVAL;

	vchiq_get_config(&config);
	ptr = compat_ptr(args32.pconfig);
	अगर (copy_to_user(ptr, &config, args32.config_size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ
vchiq_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = compat_ptr(arg);
	चयन (cmd) अणु
	हाल VCHIQ_IOC_CREATE_SERVICE32:
		वापस vchiq_compat_ioctl_create_service(file, cmd, argp);
	हाल VCHIQ_IOC_QUEUE_MESSAGE32:
		वापस vchiq_compat_ioctl_queue_message(file, cmd, argp);
	हाल VCHIQ_IOC_QUEUE_BULK_TRANSMIT32:
	हाल VCHIQ_IOC_QUEUE_BULK_RECEIVE32:
		वापस vchiq_compat_ioctl_queue_bulk(file, cmd, argp);
	हाल VCHIQ_IOC_AWAIT_COMPLETION32:
		वापस vchiq_compat_ioctl_aरुको_completion(file, cmd, argp);
	हाल VCHIQ_IOC_DEQUEUE_MESSAGE32:
		वापस vchiq_compat_ioctl_dequeue_message(file, cmd, argp);
	हाल VCHIQ_IOC_GET_CONFIG32:
		वापस vchiq_compat_ioctl_get_config(file, cmd, argp);
	शेष:
		वापस vchiq_ioctl(file, cmd, (अचिन्हित दीर्घ)argp);
	पूर्ण
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक vchiq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vchiq_state *state = vchiq_get_state();
	काष्ठा vchiq_instance *instance;

	vchiq_log_info(vchiq_arm_log_level, "vchiq_open");

	अगर (!state) अणु
		vchiq_log_error(vchiq_arm_log_level,
				"vchiq has no connection to VideoCore");
		वापस -ENOTCONN;
	पूर्ण

	instance = kzalloc(माप(*instance), GFP_KERNEL);
	अगर (!instance)
		वापस -ENOMEM;

	instance->state = state;
	instance->pid = current->tgid;

	vchiq_debugfs_add_instance(instance);

	init_completion(&instance->insert_event);
	init_completion(&instance->हटाओ_event);
	mutex_init(&instance->completion_mutex);
	mutex_init(&instance->bulk_रुकोer_list_mutex);
	INIT_LIST_HEAD(&instance->bulk_रुकोer_list);

	file->निजी_data = instance;

	वापस 0;
पूर्ण

अटल पूर्णांक vchiq_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vchiq_instance *instance = file->निजी_data;
	काष्ठा vchiq_state *state = vchiq_get_state();
	काष्ठा vchiq_service *service;
	पूर्णांक ret = 0;
	पूर्णांक i;

	vchiq_log_info(vchiq_arm_log_level, "%s: instance=%lx", __func__,
		       (अचिन्हित दीर्घ)instance);

	अगर (!state) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	/* Ensure videocore is awake to allow termination. */
	vchiq_use_पूर्णांकernal(instance->state, शून्य, USE_TYPE_VCHIQ);

	mutex_lock(&instance->completion_mutex);

	/* Wake the completion thपढ़ो and ask it to निकास */
	instance->closing = 1;
	complete(&instance->insert_event);

	mutex_unlock(&instance->completion_mutex);

	/* Wake the slot handler अगर the completion queue is full. */
	complete(&instance->हटाओ_event);

	/* Mark all services क्रम termination... */
	i = 0;
	जबतक ((service = next_service_by_instance(state, instance, &i))) अणु
		काष्ठा user_service *user_service = service->base.userdata;

		/* Wake the slot handler अगर the msg queue is full. */
		complete(&user_service->हटाओ_event);

		vchiq_terminate_service_पूर्णांकernal(service);
		unlock_service(service);
	पूर्ण

	/* ...and रुको क्रम them to die */
	i = 0;
	जबतक ((service = next_service_by_instance(state, instance, &i))) अणु
		काष्ठा user_service *user_service = service->base.userdata;

		रुको_क्रम_completion(&service->हटाओ_event);

		BUG_ON(service->srvstate != VCHIQ_SRVSTATE_FREE);

		spin_lock(&msg_queue_spinlock);

		जबतक (user_service->msg_हटाओ != user_service->msg_insert) अणु
			काष्ठा vchiq_header *header;
			पूर्णांक m = user_service->msg_हटाओ & (MSG_QUEUE_SIZE - 1);

			header = user_service->msg_queue[m];
			user_service->msg_हटाओ++;
			spin_unlock(&msg_queue_spinlock);

			अगर (header)
				vchiq_release_message(service->handle, header);
			spin_lock(&msg_queue_spinlock);
		पूर्ण

		spin_unlock(&msg_queue_spinlock);

		unlock_service(service);
	पूर्ण

	/* Release any बंदd services */
	जबतक (instance->completion_हटाओ !=
		instance->completion_insert) अणु
		काष्ठा vchiq_completion_data_kernel *completion;
		काष्ठा vchiq_service *service;

		completion = &instance->completions[
			instance->completion_हटाओ & (MAX_COMPLETIONS - 1)];
		service = completion->service_userdata;
		अगर (completion->reason == VCHIQ_SERVICE_CLOSED) अणु
			काष्ठा user_service *user_service =
							service->base.userdata;

			/* Wake any blocked user-thपढ़ो */
			अगर (instance->use_बंद_delivered)
				complete(&user_service->बंद_event);
			unlock_service(service);
		पूर्ण
		instance->completion_हटाओ++;
	पूर्ण

	/* Release the PEER service count. */
	vchiq_release_पूर्णांकernal(instance->state, शून्य);

	अणु
		काष्ठा bulk_रुकोer_node *रुकोer, *next;

		list_क्रम_each_entry_safe(रुकोer, next,
					 &instance->bulk_रुकोer_list, list) अणु
			list_del(&रुकोer->list);
			vchiq_log_info(vchiq_arm_log_level,
				"bulk_waiter - cleaned up %pK for pid %d",
				रुकोer, रुकोer->pid);
			kमुक्त(रुकोer);
		पूर्ण
	पूर्ण

	vchiq_debugfs_हटाओ_instance(instance);

	kमुक्त(instance);
	file->निजी_data = शून्य;

out:
	वापस ret;
पूर्ण

/****************************************************************************
 *
 *   vchiq_dump
 *
 ***************************************************************************/

पूर्णांक vchiq_dump(व्योम *dump_context, स्थिर अक्षर *str, पूर्णांक len)
अणु
	काष्ठा dump_context *context = (काष्ठा dump_context *)dump_context;
	पूर्णांक copy_bytes;

	अगर (context->actual >= context->space)
		वापस 0;

	अगर (context->offset > 0) अणु
		पूर्णांक skip_bytes = min_t(पूर्णांक, len, context->offset);

		str += skip_bytes;
		len -= skip_bytes;
		context->offset -= skip_bytes;
		अगर (context->offset > 0)
			वापस 0;
	पूर्ण
	copy_bytes = min_t(पूर्णांक, len, context->space - context->actual);
	अगर (copy_bytes == 0)
		वापस 0;
	अगर (copy_to_user(context->buf + context->actual, str,
			 copy_bytes))
		वापस -EFAULT;
	context->actual += copy_bytes;
	len -= copy_bytes;

	/*
	 * If the terminating NUL is included in the length, then it
	 * marks the end of a line and should be replaced with a
	 * carriage वापस.
	 */
	अगर ((len == 0) && (str[copy_bytes - 1] == '\0')) अणु
		अक्षर cr = '\n';

		अगर (copy_to_user(context->buf + context->actual - 1,
				 &cr, 1))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/****************************************************************************
 *
 *   vchiq_dump_platक्रमm_instance_state
 *
 ***************************************************************************/

पूर्णांक vchiq_dump_platक्रमm_instances(व्योम *dump_context)
अणु
	काष्ठा vchiq_state *state = vchiq_get_state();
	अक्षर buf[80];
	पूर्णांक len;
	पूर्णांक i;

	/*
	 * There is no list of instances, so instead scan all services,
	 * marking those that have been dumped.
	 */

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < state->unused_service; i++) अणु
		काष्ठा vchiq_service *service;
		काष्ठा vchiq_instance *instance;

		service = rcu_dereference(state->services[i]);
		अगर (!service || service->base.callback != service_callback)
			जारी;

		instance = service->instance;
		अगर (instance)
			instance->mark = 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	क्रम (i = 0; i < state->unused_service; i++) अणु
		काष्ठा vchiq_service *service;
		काष्ठा vchiq_instance *instance;
		पूर्णांक err;

		rcu_पढ़ो_lock();
		service = rcu_dereference(state->services[i]);
		अगर (!service || service->base.callback != service_callback) अणु
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण

		instance = service->instance;
		अगर (!instance || instance->mark) अणु
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण
		rcu_पढ़ो_unlock();

		len = snम_लिखो(buf, माप(buf),
			       "Instance %pK: pid %d,%s completions %d/%d",
			       instance, instance->pid,
			       instance->connected ? " connected, " :
			       "",
			       instance->completion_insert -
			       instance->completion_हटाओ,
			       MAX_COMPLETIONS);
		err = vchiq_dump(dump_context, buf, len + 1);
		अगर (err)
			वापस err;
		instance->mark = 1;
	पूर्ण
	वापस 0;
पूर्ण

/****************************************************************************
 *
 *   vchiq_dump_platक्रमm_service_state
 *
 ***************************************************************************/

पूर्णांक vchiq_dump_platक्रमm_service_state(व्योम *dump_context,
				      काष्ठा vchiq_service *service)
अणु
	काष्ठा user_service *user_service =
			(काष्ठा user_service *)service->base.userdata;
	अक्षर buf[80];
	पूर्णांक len;

	len = scnम_लिखो(buf, माप(buf), "  instance %pK", service->instance);

	अगर ((service->base.callback == service_callback) &&
		user_service->is_vchi) अणु
		len += scnम_लिखो(buf + len, माप(buf) - len,
			", %d/%d messages",
			user_service->msg_insert - user_service->msg_हटाओ,
			MSG_QUEUE_SIZE);

		अगर (user_service->dequeue_pending)
			len += scnम_लिखो(buf + len, माप(buf) - len,
				" (dequeue pending)");
	पूर्ण

	वापस vchiq_dump(dump_context, buf, len + 1);
पूर्ण

/****************************************************************************
 *
 *   vchiq_पढ़ो
 *
 ***************************************************************************/

अटल sमाप_प्रकार
vchiq_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
	माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dump_context context;
	पूर्णांक err;

	context.buf = buf;
	context.actual = 0;
	context.space = count;
	context.offset = *ppos;

	err = vchiq_dump_state(&context, &g_state);
	अगर (err)
		वापस err;

	*ppos += context.actual;

	वापस context.actual;
पूर्ण

काष्ठा vchiq_state *
vchiq_get_state(व्योम)
अणु

	अगर (!g_state.remote)
		prपूर्णांकk(KERN_ERR "%s: g_state.remote == NULL\n", __func__);
	अन्यथा अगर (g_state.remote->initialised != 1)
		prपूर्णांकk(KERN_NOTICE "%s: g_state.remote->initialised != 1 (%d)\n",
			__func__, g_state.remote->initialised);

	वापस (g_state.remote &&
		(g_state.remote->initialised == 1)) ? &g_state : शून्य;
पूर्ण

अटल स्थिर काष्ठा file_operations
vchiq_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = vchiq_ioctl,
#अगर defined(CONFIG_COMPAT)
	.compat_ioctl = vchiq_compat_ioctl,
#पूर्ण_अगर
	.खोलो = vchiq_खोलो,
	.release = vchiq_release,
	.पढ़ो = vchiq_पढ़ो
पूर्ण;

/*
 * Autosuspend related functionality
 */

अटल क्रमागत vchiq_status
vchiq_keepalive_vchiq_callback(क्रमागत vchiq_reason reason,
	काष्ठा vchiq_header *header,
	अचिन्हित पूर्णांक service_user,
	व्योम *bulk_user)
अणु
	vchiq_log_error(vchiq_susp_log_level,
		"%s callback reason %d", __func__, reason);
	वापस 0;
पूर्ण

अटल पूर्णांक
vchiq_keepalive_thपढ़ो_func(व्योम *v)
अणु
	काष्ठा vchiq_state *state = (काष्ठा vchiq_state *)v;
	काष्ठा vchiq_arm_state *arm_state = vchiq_platक्रमm_get_arm_state(state);

	क्रमागत vchiq_status status;
	काष्ठा vchiq_instance *instance;
	अचिन्हित पूर्णांक ka_handle;

	काष्ठा vchiq_service_params_kernel params = अणु
		.fourcc      = VCHIQ_MAKE_FOURCC('K', 'E', 'E', 'P'),
		.callback    = vchiq_keepalive_vchiq_callback,
		.version     = KEEPALIVE_VER,
		.version_min = KEEPALIVE_VER_MIN
	पूर्ण;

	status = vchiq_initialise(&instance);
	अगर (status != VCHIQ_SUCCESS) अणु
		vchiq_log_error(vchiq_susp_log_level,
			"%s vchiq_initialise failed %d", __func__, status);
		जाओ निकास;
	पूर्ण

	status = vchiq_connect(instance);
	अगर (status != VCHIQ_SUCCESS) अणु
		vchiq_log_error(vchiq_susp_log_level,
			"%s vchiq_connect failed %d", __func__, status);
		जाओ shutकरोwn;
	पूर्ण

	status = vchiq_add_service(instance, &params, &ka_handle);
	अगर (status != VCHIQ_SUCCESS) अणु
		vchiq_log_error(vchiq_susp_log_level,
			"%s vchiq_open_service failed %d", __func__, status);
		जाओ shutकरोwn;
	पूर्ण

	जबतक (1) अणु
		दीर्घ rc = 0, uc = 0;

		अगर (रुको_क्रम_completion_पूर्णांकerruptible(&arm_state->ka_evt)) अणु
			vchiq_log_error(vchiq_susp_log_level,
				"%s interrupted", __func__);
			flush_संकेतs(current);
			जारी;
		पूर्ण

		/*
		 * पढ़ो and clear counters.  Do release_count then use_count to
		 * prevent getting more releases than uses
		 */
		rc = atomic_xchg(&arm_state->ka_release_count, 0);
		uc = atomic_xchg(&arm_state->ka_use_count, 0);

		/*
		 * Call use/release service the requisite number of बार.
		 * Process use beक्रमe release so use counts करोn't go negative
		 */
		जबतक (uc--) अणु
			atomic_inc(&arm_state->ka_use_ack_count);
			status = vchiq_use_service(ka_handle);
			अगर (status != VCHIQ_SUCCESS) अणु
				vchiq_log_error(vchiq_susp_log_level,
					"%s vchiq_use_service error %d",
					__func__, status);
			पूर्ण
		पूर्ण
		जबतक (rc--) अणु
			status = vchiq_release_service(ka_handle);
			अगर (status != VCHIQ_SUCCESS) अणु
				vchiq_log_error(vchiq_susp_log_level,
					"%s vchiq_release_service error %d",
					__func__, status);
			पूर्ण
		पूर्ण
	पूर्ण

shutकरोwn:
	vchiq_shutकरोwn(instance);
निकास:
	वापस 0;
पूर्ण

क्रमागत vchiq_status
vchiq_arm_init_state(काष्ठा vchiq_state *state,
		     काष्ठा vchiq_arm_state *arm_state)
अणु
	अगर (arm_state) अणु
		rwlock_init(&arm_state->susp_res_lock);

		init_completion(&arm_state->ka_evt);
		atomic_set(&arm_state->ka_use_count, 0);
		atomic_set(&arm_state->ka_use_ack_count, 0);
		atomic_set(&arm_state->ka_release_count, 0);

		arm_state->state = state;
		arm_state->first_connect = 0;

	पूर्ण
	वापस VCHIQ_SUCCESS;
पूर्ण

क्रमागत vchiq_status
vchiq_use_पूर्णांकernal(काष्ठा vchiq_state *state, काष्ठा vchiq_service *service,
		   क्रमागत USE_TYPE_E use_type)
अणु
	काष्ठा vchiq_arm_state *arm_state = vchiq_platक्रमm_get_arm_state(state);
	क्रमागत vchiq_status ret = VCHIQ_SUCCESS;
	अक्षर entity[16];
	पूर्णांक *entity_uc;
	पूर्णांक local_uc;

	अगर (!arm_state) अणु
		ret = VCHIQ_ERROR;
		जाओ out;
	पूर्ण

	vchiq_log_trace(vchiq_susp_log_level, "%s", __func__);

	अगर (use_type == USE_TYPE_VCHIQ) अणु
		प्र_लिखो(entity, "VCHIQ:   ");
		entity_uc = &arm_state->peer_use_count;
	पूर्ण अन्यथा अगर (service) अणु
		प्र_लिखो(entity, "%c%c%c%c:%03d",
			VCHIQ_FOURCC_AS_4CHARS(service->base.fourcc),
			service->client_id);
		entity_uc = &service->service_use_count;
	पूर्ण अन्यथा अणु
		vchiq_log_error(vchiq_susp_log_level, "%s null service ptr", __func__);
		ret = VCHIQ_ERROR;
		जाओ out;
	पूर्ण

	ग_लिखो_lock_bh(&arm_state->susp_res_lock);
	local_uc = ++arm_state->videocore_use_count;
	++(*entity_uc);

	vchiq_log_trace(vchiq_susp_log_level,
		"%s %s count %d, state count %d",
		__func__, entity, *entity_uc, local_uc);

	ग_लिखो_unlock_bh(&arm_state->susp_res_lock);

	अगर (ret == VCHIQ_SUCCESS) अणु
		क्रमागत vchiq_status status = VCHIQ_SUCCESS;
		दीर्घ ack_cnt = atomic_xchg(&arm_state->ka_use_ack_count, 0);

		जबतक (ack_cnt && (status == VCHIQ_SUCCESS)) अणु
			/* Send the use notअगरy to videocore */
			status = vchiq_send_remote_use_active(state);
			अगर (status == VCHIQ_SUCCESS)
				ack_cnt--;
			अन्यथा
				atomic_add(ack_cnt,
					&arm_state->ka_use_ack_count);
		पूर्ण
	पूर्ण

out:
	vchiq_log_trace(vchiq_susp_log_level, "%s exit %d", __func__, ret);
	वापस ret;
पूर्ण

क्रमागत vchiq_status
vchiq_release_पूर्णांकernal(काष्ठा vchiq_state *state, काष्ठा vchiq_service *service)
अणु
	काष्ठा vchiq_arm_state *arm_state = vchiq_platक्रमm_get_arm_state(state);
	क्रमागत vchiq_status ret = VCHIQ_SUCCESS;
	अक्षर entity[16];
	पूर्णांक *entity_uc;

	अगर (!arm_state) अणु
		ret = VCHIQ_ERROR;
		जाओ out;
	पूर्ण

	vchiq_log_trace(vchiq_susp_log_level, "%s", __func__);

	अगर (service) अणु
		प्र_लिखो(entity, "%c%c%c%c:%03d",
			VCHIQ_FOURCC_AS_4CHARS(service->base.fourcc),
			service->client_id);
		entity_uc = &service->service_use_count;
	पूर्ण अन्यथा अणु
		प्र_लिखो(entity, "PEER:   ");
		entity_uc = &arm_state->peer_use_count;
	पूर्ण

	ग_लिखो_lock_bh(&arm_state->susp_res_lock);
	अगर (!arm_state->videocore_use_count || !(*entity_uc)) अणु
		/* Don't use BUG_ON - don't allow user thपढ़ो to crash kernel */
		WARN_ON(!arm_state->videocore_use_count);
		WARN_ON(!(*entity_uc));
		ret = VCHIQ_ERROR;
		जाओ unlock;
	पूर्ण
	--arm_state->videocore_use_count;
	--(*entity_uc);

	vchiq_log_trace(vchiq_susp_log_level,
		"%s %s count %d, state count %d",
		__func__, entity, *entity_uc,
		arm_state->videocore_use_count);

unlock:
	ग_लिखो_unlock_bh(&arm_state->susp_res_lock);

out:
	vchiq_log_trace(vchiq_susp_log_level, "%s exit %d", __func__, ret);
	वापस ret;
पूर्ण

व्योम
vchiq_on_remote_use(काष्ठा vchiq_state *state)
अणु
	काष्ठा vchiq_arm_state *arm_state = vchiq_platक्रमm_get_arm_state(state);

	vchiq_log_trace(vchiq_susp_log_level, "%s", __func__);
	atomic_inc(&arm_state->ka_use_count);
	complete(&arm_state->ka_evt);
पूर्ण

व्योम
vchiq_on_remote_release(काष्ठा vchiq_state *state)
अणु
	काष्ठा vchiq_arm_state *arm_state = vchiq_platक्रमm_get_arm_state(state);

	vchiq_log_trace(vchiq_susp_log_level, "%s", __func__);
	atomic_inc(&arm_state->ka_release_count);
	complete(&arm_state->ka_evt);
पूर्ण

क्रमागत vchiq_status
vchiq_use_service_पूर्णांकernal(काष्ठा vchiq_service *service)
अणु
	वापस vchiq_use_पूर्णांकernal(service->state, service, USE_TYPE_SERVICE);
पूर्ण

क्रमागत vchiq_status
vchiq_release_service_पूर्णांकernal(काष्ठा vchiq_service *service)
अणु
	वापस vchiq_release_पूर्णांकernal(service->state, service);
पूर्ण

काष्ठा vchiq_debugfs_node *
vchiq_instance_get_debugfs_node(काष्ठा vchiq_instance *instance)
अणु
	वापस &instance->debugfs_node;
पूर्ण

पूर्णांक
vchiq_instance_get_use_count(काष्ठा vchiq_instance *instance)
अणु
	काष्ठा vchiq_service *service;
	पूर्णांक use_count = 0, i;

	i = 0;
	rcu_पढ़ो_lock();
	जबतक ((service = __next_service_by_instance(instance->state,
						     instance, &i)))
		use_count += service->service_use_count;
	rcu_पढ़ो_unlock();
	वापस use_count;
पूर्ण

पूर्णांक
vchiq_instance_get_pid(काष्ठा vchiq_instance *instance)
अणु
	वापस instance->pid;
पूर्ण

पूर्णांक
vchiq_instance_get_trace(काष्ठा vchiq_instance *instance)
अणु
	वापस instance->trace;
पूर्ण

व्योम
vchiq_instance_set_trace(काष्ठा vchiq_instance *instance, पूर्णांक trace)
अणु
	काष्ठा vchiq_service *service;
	पूर्णांक i;

	i = 0;
	rcu_पढ़ो_lock();
	जबतक ((service = __next_service_by_instance(instance->state,
						     instance, &i)))
		service->trace = trace;
	rcu_पढ़ो_unlock();
	instance->trace = (trace != 0);
पूर्ण

क्रमागत vchiq_status
vchiq_use_service(अचिन्हित पूर्णांक handle)
अणु
	क्रमागत vchiq_status ret = VCHIQ_ERROR;
	काष्ठा vchiq_service *service = find_service_by_handle(handle);

	अगर (service) अणु
		ret = vchiq_use_पूर्णांकernal(service->state, service,
				USE_TYPE_SERVICE);
		unlock_service(service);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vchiq_use_service);

क्रमागत vchiq_status
vchiq_release_service(अचिन्हित पूर्णांक handle)
अणु
	क्रमागत vchiq_status ret = VCHIQ_ERROR;
	काष्ठा vchiq_service *service = find_service_by_handle(handle);

	अगर (service) अणु
		ret = vchiq_release_पूर्णांकernal(service->state, service);
		unlock_service(service);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vchiq_release_service);

काष्ठा service_data_काष्ठा अणु
	पूर्णांक fourcc;
	पूर्णांक clientid;
	पूर्णांक use_count;
पूर्ण;

व्योम
vchiq_dump_service_use_state(काष्ठा vchiq_state *state)
अणु
	काष्ठा vchiq_arm_state *arm_state = vchiq_platक्रमm_get_arm_state(state);
	काष्ठा service_data_काष्ठा *service_data;
	पूर्णांक i, found = 0;
	/*
	 * If there's more than 64 services, only dump ones with
	 * non-zero counts
	 */
	पूर्णांक only_nonzero = 0;
	अटल स्थिर अक्षर *nz = "<-- preventing suspend";

	पूर्णांक peer_count;
	पूर्णांक vc_use_count;
	पूर्णांक active_services;

	अगर (!arm_state)
		वापस;

	service_data = kदो_स्मृति_array(MAX_SERVICES, माप(*service_data),
				     GFP_KERNEL);
	अगर (!service_data)
		वापस;

	पढ़ो_lock_bh(&arm_state->susp_res_lock);
	peer_count = arm_state->peer_use_count;
	vc_use_count = arm_state->videocore_use_count;
	active_services = state->unused_service;
	अगर (active_services > MAX_SERVICES)
		only_nonzero = 1;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < active_services; i++) अणु
		काष्ठा vchiq_service *service_ptr =
			rcu_dereference(state->services[i]);

		अगर (!service_ptr)
			जारी;

		अगर (only_nonzero && !service_ptr->service_use_count)
			जारी;

		अगर (service_ptr->srvstate == VCHIQ_SRVSTATE_FREE)
			जारी;

		service_data[found].fourcc = service_ptr->base.fourcc;
		service_data[found].clientid = service_ptr->client_id;
		service_data[found].use_count = service_ptr->service_use_count;
		found++;
		अगर (found >= MAX_SERVICES)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	पढ़ो_unlock_bh(&arm_state->susp_res_lock);

	अगर (only_nonzero)
		vchiq_log_warning(vchiq_susp_log_level, "Too many active "
			"services (%d).  Only dumping up to first %d services "
			"with non-zero use-count", active_services, found);

	क्रम (i = 0; i < found; i++) अणु
		vchiq_log_warning(vchiq_susp_log_level,
			"----- %c%c%c%c:%d service count %d %s",
			VCHIQ_FOURCC_AS_4CHARS(service_data[i].fourcc),
			service_data[i].clientid,
			service_data[i].use_count,
			service_data[i].use_count ? nz : "");
	पूर्ण
	vchiq_log_warning(vchiq_susp_log_level,
		"----- VCHIQ use count count %d", peer_count);
	vchiq_log_warning(vchiq_susp_log_level,
		"--- Overall vchiq instance use count %d", vc_use_count);

	kमुक्त(service_data);
पूर्ण

क्रमागत vchiq_status
vchiq_check_service(काष्ठा vchiq_service *service)
अणु
	काष्ठा vchiq_arm_state *arm_state;
	क्रमागत vchiq_status ret = VCHIQ_ERROR;

	अगर (!service || !service->state)
		जाओ out;

	vchiq_log_trace(vchiq_susp_log_level, "%s", __func__);

	arm_state = vchiq_platक्रमm_get_arm_state(service->state);

	पढ़ो_lock_bh(&arm_state->susp_res_lock);
	अगर (service->service_use_count)
		ret = VCHIQ_SUCCESS;
	पढ़ो_unlock_bh(&arm_state->susp_res_lock);

	अगर (ret == VCHIQ_ERROR) अणु
		vchiq_log_error(vchiq_susp_log_level,
			"%s ERROR - %c%c%c%c:%d service count %d, state count %d", __func__,
			VCHIQ_FOURCC_AS_4CHARS(service->base.fourcc),
			service->client_id, service->service_use_count,
			arm_state->videocore_use_count);
		vchiq_dump_service_use_state(service->state);
	पूर्ण
out:
	वापस ret;
पूर्ण

व्योम vchiq_platक्रमm_conn_state_changed(काष्ठा vchiq_state *state,
				       क्रमागत vchiq_connstate oldstate,
				       क्रमागत vchiq_connstate newstate)
अणु
	काष्ठा vchiq_arm_state *arm_state = vchiq_platक्रमm_get_arm_state(state);
	अक्षर thपढ़ोname[16];

	vchiq_log_info(vchiq_susp_log_level, "%d: %s->%s", state->id,
		get_conn_state_name(oldstate), get_conn_state_name(newstate));
	अगर (state->conn_state != VCHIQ_CONNSTATE_CONNECTED)
		वापस;

	ग_लिखो_lock_bh(&arm_state->susp_res_lock);
	अगर (arm_state->first_connect) अणु
		ग_लिखो_unlock_bh(&arm_state->susp_res_lock);
		वापस;
	पूर्ण

	arm_state->first_connect = 1;
	ग_लिखो_unlock_bh(&arm_state->susp_res_lock);
	snम_लिखो(thपढ़ोname, माप(thपढ़ोname), "vchiq-keep/%d",
		 state->id);
	arm_state->ka_thपढ़ो = kthपढ़ो_create(&vchiq_keepalive_thपढ़ो_func,
					      (व्योम *)state,
					      thपढ़ोname);
	अगर (IS_ERR(arm_state->ka_thपढ़ो)) अणु
		vchiq_log_error(vchiq_susp_log_level,
				"vchiq: FATAL: couldn't create thread %s",
				thपढ़ोname);
	पूर्ण अन्यथा अणु
		wake_up_process(arm_state->ka_thपढ़ो);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id vchiq_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-vchiq", .data = &bcm2835_drvdata पूर्ण,
	अणु .compatible = "brcm,bcm2836-vchiq", .data = &bcm2836_drvdata पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vchiq_of_match);

अटल काष्ठा platक्रमm_device *
vchiq_रेजिस्टर_child(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name)
अणु
	काष्ठा platक्रमm_device_info pdevinfo;
	काष्ठा platक्रमm_device *child;

	स_रखो(&pdevinfo, 0, माप(pdevinfo));

	pdevinfo.parent = &pdev->dev;
	pdevinfo.name = name;
	pdevinfo.id = PLATFORM_DEVID_NONE;
	pdevinfo.dma_mask = DMA_BIT_MASK(32);

	child = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	अगर (IS_ERR(child)) अणु
		dev_warn(&pdev->dev, "%s not registered\n", name);
		child = शून्य;
	पूर्ण

	वापस child;
पूर्ण

अटल पूर्णांक vchiq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *fw_node;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा vchiq_drvdata *drvdata;
	काष्ठा device *vchiq_dev;
	पूर्णांक err;

	of_id = of_match_node(vchiq_of_match, pdev->dev.of_node);
	drvdata = (काष्ठा vchiq_drvdata *)of_id->data;
	अगर (!drvdata)
		वापस -EINVAL;

	fw_node = of_find_compatible_node(शून्य, शून्य,
					  "raspberrypi,bcm2835-firmware");
	अगर (!fw_node) अणु
		dev_err(&pdev->dev, "Missing firmware node\n");
		वापस -ENOENT;
	पूर्ण

	drvdata->fw = devm_rpi_firmware_get(&pdev->dev, fw_node);
	of_node_put(fw_node);
	अगर (!drvdata->fw)
		वापस -EPROBE_DEFER;

	platक्रमm_set_drvdata(pdev, drvdata);

	err = vchiq_platक्रमm_init(pdev, &g_state);
	अगर (err)
		जाओ failed_platक्रमm_init;

	cdev_init(&vchiq_cdev, &vchiq_fops);
	vchiq_cdev.owner = THIS_MODULE;
	err = cdev_add(&vchiq_cdev, vchiq_devid, 1);
	अगर (err) अणु
		vchiq_log_error(vchiq_arm_log_level,
			"Unable to register device");
		जाओ failed_platक्रमm_init;
	पूर्ण

	vchiq_dev = device_create(vchiq_class, &pdev->dev, vchiq_devid, शून्य,
				  "vchiq");
	अगर (IS_ERR(vchiq_dev)) अणु
		err = PTR_ERR(vchiq_dev);
		जाओ failed_device_create;
	पूर्ण

	vchiq_debugfs_init();

	vchiq_log_info(vchiq_arm_log_level,
		"vchiq: initialised - version %d (min %d), device %d.%d",
		VCHIQ_VERSION, VCHIQ_VERSION_MIN,
		MAJOR(vchiq_devid), MINOR(vchiq_devid));

	bcm2835_camera = vchiq_रेजिस्टर_child(pdev, "bcm2835-camera");
	bcm2835_audio = vchiq_रेजिस्टर_child(pdev, "bcm2835_audio");

	वापस 0;

failed_device_create:
	cdev_del(&vchiq_cdev);
failed_platक्रमm_init:
	vchiq_log_warning(vchiq_arm_log_level, "could not load vchiq");
	वापस err;
पूर्ण

अटल पूर्णांक vchiq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	platक्रमm_device_unरेजिस्टर(bcm2835_audio);
	platक्रमm_device_unरेजिस्टर(bcm2835_camera);
	vchiq_debugfs_deinit();
	device_destroy(vchiq_class, vchiq_devid);
	cdev_del(&vchiq_cdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vchiq_driver = अणु
	.driver = अणु
		.name = "bcm2835_vchiq",
		.of_match_table = vchiq_of_match,
	पूर्ण,
	.probe = vchiq_probe,
	.हटाओ = vchiq_हटाओ,
पूर्ण;

अटल पूर्णांक __init vchiq_driver_init(व्योम)
अणु
	पूर्णांक ret;

	vchiq_class = class_create(THIS_MODULE, DEVICE_NAME);
	अगर (IS_ERR(vchiq_class)) अणु
		pr_err("Failed to create vchiq class\n");
		वापस PTR_ERR(vchiq_class);
	पूर्ण

	ret = alloc_chrdev_region(&vchiq_devid, 0, 1, DEVICE_NAME);
	अगर (ret) अणु
		pr_err("Failed to allocate vchiq's chrdev region\n");
		जाओ class_destroy;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&vchiq_driver);
	अगर (ret) अणु
		pr_err("Failed to register vchiq driver\n");
		जाओ region_unरेजिस्टर;
	पूर्ण

	वापस 0;

region_unरेजिस्टर:
	unरेजिस्टर_chrdev_region(vchiq_devid, 1);

class_destroy:
	class_destroy(vchiq_class);

	वापस ret;
पूर्ण
module_init(vchiq_driver_init);

अटल व्योम __निकास vchiq_driver_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vchiq_driver);
	unरेजिस्टर_chrdev_region(vchiq_devid, 1);
	class_destroy(vchiq_class);
पूर्ण
module_निकास(vchiq_driver_निकास);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Videocore VCHIQ driver");
MODULE_AUTHOR("Broadcom Corporation");
