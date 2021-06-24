<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SCLP Store Data support and sysfs पूर्णांकerface
 *
 * Copyright IBM Corp. 2017
 */

#घोषणा KMSG_COMPONENT "sclp_sd"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/completion.h>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/async.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>

#समावेश <यंत्र/pgभाग.स>

#समावेश "sclp.h"

#घोषणा SD_EQ_STORE_DATA	0
#घोषणा SD_EQ_HALT		1
#घोषणा SD_EQ_SIZE		2

#घोषणा SD_DI_CONFIG		3

काष्ठा sclp_sd_evbuf अणु
	काष्ठा evbuf_header hdr;
	u8 eq;
	u8 di;
	u8 rflags;
	u64 :56;
	u32 id;
	u16 :16;
	u8 fmt;
	u8 status;
	u64 sat;
	u64 sa;
	u32 esize;
	u32 dsize;
पूर्ण __packed;

काष्ठा sclp_sd_sccb अणु
	काष्ठा sccb_header hdr;
	काष्ठा sclp_sd_evbuf evbuf;
पूर्ण __packed __aligned(PAGE_SIZE);

/**
 * काष्ठा sclp_sd_data - Result of a Store Data request
 * @esize_bytes: Resulting esize in bytes
 * @dsize_bytes: Resulting dsize in bytes
 * @data: Poपूर्णांकer to data - must be released using vमुक्त()
 */
काष्ठा sclp_sd_data अणु
	माप_प्रकार esize_bytes;
	माप_प्रकार dsize_bytes;
	व्योम *data;
पूर्ण;

/**
 * काष्ठा sclp_sd_listener - Listener क्रम asynchronous Store Data response
 * @list: For enqueueing this काष्ठा
 * @id: Event ID of response to listen क्रम
 * @completion: Can be used to रुको क्रम response
 * @evbuf: Contains the resulting Store Data response after completion
 */
काष्ठा sclp_sd_listener अणु
	काष्ठा list_head list;
	u32 id;
	काष्ठा completion completion;
	काष्ठा sclp_sd_evbuf evbuf;
पूर्ण;

/**
 * काष्ठा sclp_sd_file - Sysfs representation of a Store Data entity
 * @kobj: Kobject
 * @data_attr: Attribute क्रम accessing data contents
 * @data_mutex: Mutex to serialize access and updates to @data
 * @data: Data associated with this entity
 * @di: DI value associated with this entity
 */
काष्ठा sclp_sd_file अणु
	काष्ठा kobject kobj;
	काष्ठा bin_attribute data_attr;
	काष्ठा mutex data_mutex;
	काष्ठा sclp_sd_data data;
	u8 di;
पूर्ण;
#घोषणा to_sd_file(x) container_of(x, काष्ठा sclp_sd_file, kobj)

अटल काष्ठा kset *sclp_sd_kset;
अटल काष्ठा sclp_sd_file *config_file;

अटल LIST_HEAD(sclp_sd_queue);
अटल DEFINE_SPINLOCK(sclp_sd_queue_lock);

/**
 * sclp_sd_listener_add() - Add listener क्रम Store Data responses
 * @listener: Listener to add
 */
अटल व्योम sclp_sd_listener_add(काष्ठा sclp_sd_listener *listener)
अणु
	spin_lock_irq(&sclp_sd_queue_lock);
	list_add_tail(&listener->list, &sclp_sd_queue);
	spin_unlock_irq(&sclp_sd_queue_lock);
पूर्ण

/**
 * sclp_sd_listener_हटाओ() - Remove listener क्रम Store Data responses
 * @listener: Listener to हटाओ
 */
अटल व्योम sclp_sd_listener_हटाओ(काष्ठा sclp_sd_listener *listener)
अणु
	spin_lock_irq(&sclp_sd_queue_lock);
	list_del(&listener->list);
	spin_unlock_irq(&sclp_sd_queue_lock);
पूर्ण

/**
 * sclp_sd_listener_init() - Initialize a Store Data response listener
 * @id: Event ID to listen क्रम
 *
 * Initialize a listener क्रम asynchronous Store Data responses. This listener
 * can afterwards be used to रुको क्रम a specअगरic response and to retrieve
 * the associated response data.
 */
अटल व्योम sclp_sd_listener_init(काष्ठा sclp_sd_listener *listener, u32 id)
अणु
	स_रखो(listener, 0, माप(*listener));
	listener->id = id;
	init_completion(&listener->completion);
पूर्ण

/**
 * sclp_sd_receiver() - Receiver क्रम Store Data events
 * @evbuf_hdr: Header of received events
 *
 * Process Store Data events and complete listeners with matching event IDs.
 */
अटल व्योम sclp_sd_receiver(काष्ठा evbuf_header *evbuf_hdr)
अणु
	काष्ठा sclp_sd_evbuf *evbuf = (काष्ठा sclp_sd_evbuf *) evbuf_hdr;
	काष्ठा sclp_sd_listener *listener;
	पूर्णांक found = 0;

	pr_debug("received event (id=0x%08x)\n", evbuf->id);
	spin_lock(&sclp_sd_queue_lock);
	list_क्रम_each_entry(listener, &sclp_sd_queue, list) अणु
		अगर (listener->id != evbuf->id)
			जारी;

		listener->evbuf = *evbuf;
		complete(&listener->completion);
		found = 1;
		अवरोध;
	पूर्ण
	spin_unlock(&sclp_sd_queue_lock);

	अगर (!found)
		pr_debug("unsolicited event (id=0x%08x)\n", evbuf->id);
पूर्ण

अटल काष्ठा sclp_रेजिस्टर sclp_sd_रेजिस्टर = अणु
	.send_mask = EVTYP_STORE_DATA_MASK,
	.receive_mask = EVTYP_STORE_DATA_MASK,
	.receiver_fn = sclp_sd_receiver,
पूर्ण;

/**
 * sclp_sd_sync() - Perक्रमm Store Data request synchronously
 * @page: Address of work page - must be below 2GB
 * @eq: Input EQ value
 * @di: Input DI value
 * @sat: Input SAT value
 * @sa: Input SA value used to specअगरy the address of the target buffer
 * @dsize_ptr: Optional poपूर्णांकer to input and output DSIZE value
 * @esize_ptr: Optional poपूर्णांकer to output ESIZE value
 *
 * Perक्रमm Store Data request with specअगरied parameters and रुको क्रम completion.
 *
 * Return %0 on success and store resulting DSIZE and ESIZE values in
 * @dsize_ptr and @esize_ptr (अगर provided). Return non-zero on error.
 */
अटल पूर्णांक sclp_sd_sync(अचिन्हित दीर्घ page, u8 eq, u8 di, u64 sat, u64 sa,
			u32 *dsize_ptr, u32 *esize_ptr)
अणु
	काष्ठा sclp_sd_sccb *sccb = (व्योम *) page;
	काष्ठा sclp_sd_listener listener;
	काष्ठा sclp_sd_evbuf *evbuf;
	पूर्णांक rc;

	sclp_sd_listener_init(&listener, (u32) (addr_t) sccb);
	sclp_sd_listener_add(&listener);

	/* Prepare SCCB */
	स_रखो(sccb, 0, PAGE_SIZE);
	sccb->hdr.length = माप(sccb->hdr) + माप(sccb->evbuf);
	evbuf = &sccb->evbuf;
	evbuf->hdr.length = माप(*evbuf);
	evbuf->hdr.type = EVTYP_STORE_DATA;
	evbuf->eq = eq;
	evbuf->di = di;
	evbuf->id = listener.id;
	evbuf->fmt = 1;
	evbuf->sat = sat;
	evbuf->sa = sa;
	अगर (dsize_ptr)
		evbuf->dsize = *dsize_ptr;

	/* Perक्रमm command */
	pr_debug("request (eq=%d, di=%d, id=0x%08x)\n", eq, di, listener.id);
	rc = sclp_sync_request(SCLP_CMDW_WRITE_EVENT_DATA, sccb);
	pr_debug("request done (rc=%d)\n", rc);
	अगर (rc)
		जाओ out;

	/* Evaluate response */
	अगर (sccb->hdr.response_code == 0x73f0) अणु
		pr_debug("event not supported\n");
		rc = -EIO;
		जाओ out_हटाओ;
	पूर्ण
	अगर (sccb->hdr.response_code != 0x0020 || !(evbuf->hdr.flags & 0x80)) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	अगर (!(evbuf->rflags & 0x80)) अणु
		rc = रुको_क्रम_completion_पूर्णांकerruptible(&listener.completion);
		अगर (rc)
			जाओ out;
		evbuf = &listener.evbuf;
	पूर्ण
	चयन (evbuf->status) अणु
	हाल 0:
		अगर (dsize_ptr)
			*dsize_ptr = evbuf->dsize;
		अगर (esize_ptr)
			*esize_ptr = evbuf->esize;
		pr_debug("success (dsize=%u, esize=%u)\n", evbuf->dsize,
			 evbuf->esize);
		अवरोध;
	हाल 3:
		rc = -ENOENT;
		अवरोध;
	शेष:
		rc = -EIO;
		अवरोध;

	पूर्ण

out:
	अगर (rc && rc != -ENOENT) अणु
		/* Provide some inक्रमmation about what went wrong */
		pr_warn("Store Data request failed (eq=%d, di=%d, "
			"response=0x%04x, flags=0x%02x, status=%d, rc=%d)\n",
			eq, di, sccb->hdr.response_code, evbuf->hdr.flags,
			evbuf->status, rc);
	पूर्ण

out_हटाओ:
	sclp_sd_listener_हटाओ(&listener);

	वापस rc;
पूर्ण

/**
 * sclp_sd_store_data() - Obtain data क्रम specअगरied Store Data entity
 * @result: Resulting data
 * @di: DI value associated with this entity
 *
 * Perक्रमm a series of Store Data requests to obtain the size and contents of
 * the specअगरied Store Data entity.
 *
 * Return:
 *   %0:       Success - result is stored in @result. @result->data must be
 *	       released using vमुक्त() after use.
 *   %-ENOENT: No data available क्रम this entity
 *   %<0:      Other error
 */
अटल पूर्णांक sclp_sd_store_data(काष्ठा sclp_sd_data *result, u8 di)
अणु
	u32 dsize = 0, esize = 0;
	अचिन्हित दीर्घ page, asce = 0;
	व्योम *data = शून्य;
	पूर्णांक rc;

	page = __get_मुक्त_page(GFP_KERNEL | GFP_DMA);
	अगर (!page)
		वापस -ENOMEM;

	/* Get size */
	rc = sclp_sd_sync(page, SD_EQ_SIZE, di, 0, 0, &dsize, &esize);
	अगर (rc)
		जाओ out;
	अगर (dsize == 0)
		जाओ out_result;

	/* Allocate memory */
	data = vzalloc(array_size((माप_प्रकार)dsize, PAGE_SIZE));
	अगर (!data) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Get translation table क्रम buffer */
	asce = base_asce_alloc((अचिन्हित दीर्घ) data, dsize);
	अगर (!asce) अणु
		vमुक्त(data);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Get data */
	rc = sclp_sd_sync(page, SD_EQ_STORE_DATA, di, asce, (u64) data, &dsize,
			  &esize);
	अगर (rc) अणु
		/* Cancel running request अगर पूर्णांकerrupted */
		अगर (rc == -ERESTARTSYS)
			sclp_sd_sync(page, SD_EQ_HALT, di, 0, 0, शून्य, शून्य);
		vमुक्त(data);
		जाओ out;
	पूर्ण

out_result:
	result->esize_bytes = (माप_प्रकार) esize * PAGE_SIZE;
	result->dsize_bytes = (माप_प्रकार) dsize * PAGE_SIZE;
	result->data = data;

out:
	base_asce_मुक्त(asce);
	मुक्त_page(page);

	वापस rc;
पूर्ण

/**
 * sclp_sd_data_reset() - Reset Store Data result buffer
 * @data: Data buffer to reset
 *
 * Reset @data to initial state and release associated memory.
 */
अटल व्योम sclp_sd_data_reset(काष्ठा sclp_sd_data *data)
अणु
	vमुक्त(data->data);
	data->data = शून्य;
	data->dsize_bytes = 0;
	data->esize_bytes = 0;
पूर्ण

/**
 * sclp_sd_file_release() - Release function क्रम sclp_sd_file object
 * @kobj: Kobject embedded in sclp_sd_file object
 */
अटल व्योम sclp_sd_file_release(काष्ठा kobject *kobj)
अणु
	काष्ठा sclp_sd_file *sd_file = to_sd_file(kobj);

	sclp_sd_data_reset(&sd_file->data);
	kमुक्त(sd_file);
पूर्ण

/**
 * sclp_sd_file_update() - Update contents of sclp_sd_file object
 * @sd_file: Object to update
 *
 * Obtain the current version of data associated with the Store Data entity
 * @sd_file.
 *
 * On success, वापस %0 and generate a KOBJ_CHANGE event to indicate that the
 * data may have changed. Return non-zero otherwise.
 */
अटल पूर्णांक sclp_sd_file_update(काष्ठा sclp_sd_file *sd_file)
अणु
	स्थिर अक्षर *name = kobject_name(&sd_file->kobj);
	काष्ठा sclp_sd_data data;
	पूर्णांक rc;

	rc = sclp_sd_store_data(&data, sd_file->di);
	अगर (rc) अणु
		अगर (rc == -ENOENT) अणु
			pr_info("No data is available for the %s data entity\n",
				 name);
		पूर्ण
		वापस rc;
	पूर्ण

	mutex_lock(&sd_file->data_mutex);
	sclp_sd_data_reset(&sd_file->data);
	sd_file->data = data;
	mutex_unlock(&sd_file->data_mutex);

	pr_info("A %zu-byte %s data entity was retrieved\n", data.dsize_bytes,
		name);
	kobject_uevent(&sd_file->kobj, KOBJ_CHANGE);

	वापस 0;
पूर्ण

/**
 * sclp_sd_file_update_async() - Wrapper क्रम asynchronous update call
 * @data: Object to update
 */
अटल व्योम sclp_sd_file_update_async(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा sclp_sd_file *sd_file = data;

	sclp_sd_file_update(sd_file);
पूर्ण

/**
 * reload_store() - Store function क्रम "reload" sysfs attribute
 * @kobj: Kobject of sclp_sd_file object
 *
 * Initiate a reload of the data associated with an sclp_sd_file object.
 */
अटल sमाप_प्रकार reload_store(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sclp_sd_file *sd_file = to_sd_file(kobj);

	sclp_sd_file_update(sd_file);

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute reload_attr = __ATTR_WO(reload);

अटल काष्ठा attribute *sclp_sd_file_शेष_attrs[] = अणु
	&reload_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type sclp_sd_file_ktype = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.release = sclp_sd_file_release,
	.शेष_attrs = sclp_sd_file_शेष_attrs,
पूर्ण;

/**
 * data_पढ़ो() - Read function क्रम "read" sysfs attribute
 * @kobj: Kobject of sclp_sd_file object
 * @buffer: Target buffer
 * @off: Requested file offset
 * @size: Requested number of bytes
 *
 * Store the requested portion of the Store Data entity contents पूर्णांकo the
 * specअगरied buffer. Return the number of bytes stored on success, or %0
 * on खातापूर्ण.
 */
अटल sमाप_प्रकार data_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
			 काष्ठा bin_attribute *attr, अक्षर *buffer,
			 loff_t off, माप_प्रकार size)
अणु
	काष्ठा sclp_sd_file *sd_file = to_sd_file(kobj);
	माप_प्रकार data_size;
	अक्षर *data;

	mutex_lock(&sd_file->data_mutex);

	data = sd_file->data.data;
	data_size = sd_file->data.dsize_bytes;
	अगर (!data || off >= data_size) अणु
		size = 0;
	पूर्ण अन्यथा अणु
		अगर (off + size > data_size)
			size = data_size - off;
		स_नकल(buffer, data + off, size);
	पूर्ण

	mutex_unlock(&sd_file->data_mutex);

	वापस size;
पूर्ण

/**
 * sclp_sd_file_create() - Add a sysfs file representing a Store Data entity
 * @name: Name of file
 * @di: DI value associated with this entity
 *
 * Create a sysfs directory with the given @name located under
 *
 *   /sys/firmware/sclp_sd/
 *
 * The files in this directory can be used to access the contents of the Store
 * Data entity associated with @DI.
 *
 * Return poपूर्णांकer to resulting sclp_sd_file object on success, %शून्य otherwise.
 * The object must be मुक्तd by calling kobject_put() on the embedded kobject
 * poपूर्णांकer after use.
 */
अटल __init काष्ठा sclp_sd_file *sclp_sd_file_create(स्थिर अक्षर *name, u8 di)
अणु
	काष्ठा sclp_sd_file *sd_file;
	पूर्णांक rc;

	sd_file = kzalloc(माप(*sd_file), GFP_KERNEL);
	अगर (!sd_file)
		वापस शून्य;
	sd_file->di = di;
	mutex_init(&sd_file->data_mutex);

	/* Create kobject located under /sys/firmware/sclp_sd/ */
	sd_file->kobj.kset = sclp_sd_kset;
	rc = kobject_init_and_add(&sd_file->kobj, &sclp_sd_file_ktype, शून्य,
				  "%s", name);
	अगर (rc) अणु
		kobject_put(&sd_file->kobj);
		वापस शून्य;
	पूर्ण

	sysfs_bin_attr_init(&sd_file->data_attr);
	sd_file->data_attr.attr.name = "data";
	sd_file->data_attr.attr.mode = 0444;
	sd_file->data_attr.पढ़ो = data_पढ़ो;

	rc = sysfs_create_bin_file(&sd_file->kobj, &sd_file->data_attr);
	अगर (rc) अणु
		kobject_put(&sd_file->kobj);
		वापस शून्य;
	पूर्ण

	/*
	 * For completeness only - users पूर्णांकerested in entity data should listen
	 * क्रम KOBJ_CHANGE instead.
	 */
	kobject_uevent(&sd_file->kobj, KOBJ_ADD);

	/* Don't let a slow Store Data request delay further initialization */
	async_schedule(sclp_sd_file_update_async, sd_file);

	वापस sd_file;
पूर्ण

/**
 * sclp_sd_init() - Initialize sclp_sd support and रेजिस्टर sysfs files
 */
अटल __init पूर्णांक sclp_sd_init(व्योम)
अणु
	पूर्णांक rc;

	rc = sclp_रेजिस्टर(&sclp_sd_रेजिस्टर);
	अगर (rc)
		वापस rc;

	/* Create kset named "sclp_sd" located under /sys/firmware/ */
	rc = -ENOMEM;
	sclp_sd_kset = kset_create_and_add("sclp_sd", शून्य, firmware_kobj);
	अगर (!sclp_sd_kset)
		जाओ err_kset;

	rc = -EINVAL;
	config_file = sclp_sd_file_create("config", SD_DI_CONFIG);
	अगर (!config_file)
		जाओ err_config;

	वापस 0;

err_config:
	kset_unरेजिस्टर(sclp_sd_kset);
err_kset:
	sclp_unरेजिस्टर(&sclp_sd_रेजिस्टर);

	वापस rc;
पूर्ण
device_initcall(sclp_sd_init);
