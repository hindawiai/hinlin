<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Character device driver क्रम extended error reporting.
 *
 *  Copyright IBM Corp. 2005
 *  extended error reporting क्रम DASD ECKD devices
 *  Author(s): Stefan Weinhuber <wein@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "dasd-eckd"

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/ebcdic.h>

#समावेश "dasd_int.h"
#समावेश "dasd_eckd.h"

#अगर_घोषित PRINTK_HEADER
#अघोषित PRINTK_HEADER
#पूर्ण_अगर				/* PRINTK_HEADER */
#घोषणा PRINTK_HEADER "dasd(eer):"

/*
 * SECTION: the पूर्णांकernal buffer
 */

/*
 * The पूर्णांकernal buffer is meant to store obaque blobs of data, so it करोes
 * not know of higher level concepts like triggers.
 * It consists of a number of pages that are used as a ringbuffer. Each data
 * blob is stored in a simple record that consists of an पूर्णांकeger, which
 * contains the size of the following data, and the data bytes themselfes.
 *
 * To allow क्रम multiple independent पढ़ोers we create one पूर्णांकernal buffer
 * each समय the device is खोलोed and destroy the buffer when the file is
 * बंदd again. The number of pages used क्रम this buffer is determined by
 * the module parmeter eer_pages.
 *
 * One record can be written to a buffer by using the functions
 * - dasd_eer_start_record (one समय per record to ग_लिखो the size to the
 *                          buffer and reserve the space क्रम the data)
 * - dasd_eer_ग_लिखो_buffer (one or more बार per record to ग_लिखो the data)
 * The data can be written in several steps but you will have to compute
 * the total size up front क्रम the invocation of dasd_eer_start_record.
 * If the ringbuffer is full, dasd_eer_start_record will हटाओ the required
 * number of old records.
 *
 * A record is typically पढ़ो in two steps, first पढ़ो the पूर्णांकeger that
 * specअगरies the size of the following data, then पढ़ो the data.
 * Both can be करोne by
 * - dasd_eer_पढ़ो_buffer
 *
 * For all mentioned functions you need to get the bufferlock first and keep
 * it until a complete record is written or पढ़ो.
 *
 * All inक्रमmation necessary to keep track of an पूर्णांकernal buffer is kept in
 * a काष्ठा eerbuffer. The buffer specअगरic to a file poपूर्णांकer is strored in
 * the निजी_data field of that file. To be able to ग_लिखो data to all
 * existing buffers, each buffer is also added to the bufferlist.
 * If the user करोes not want to पढ़ो a complete record in one go, we have to
 * keep track of the rest of the record. residual stores the number of bytes
 * that are still to deliver. If the rest of the record is invalidated between
 * two पढ़ोs then residual will be set to -1 so that the next पढ़ो will fail.
 * All entries in the eerbuffer काष्ठाure are रक्षित with the bufferlock.
 * To aव्योम races between writing to a buffer on the one side and creating
 * and destroying buffers on the other side, the bufferlock must also be used
 * to protect the bufferlist.
 */

अटल पूर्णांक eer_pages = 5;
module_param(eer_pages, पूर्णांक, S_IRUGO|S_IWUSR);

काष्ठा eerbuffer अणु
	काष्ठा list_head list;
	अक्षर **buffer;
	पूर्णांक buffersize;
	पूर्णांक buffer_page_count;
	पूर्णांक head;
        पूर्णांक tail;
	पूर्णांक residual;
पूर्ण;

अटल LIST_HEAD(bufferlist);
अटल DEFINE_SPINLOCK(bufferlock);
अटल DECLARE_WAIT_QUEUE_HEAD(dasd_eer_पढ़ो_रुको_queue);

/*
 * How many मुक्त bytes are available on the buffer.
 * Needs to be called with bufferlock held.
 */
अटल पूर्णांक dasd_eer_get_मुक्त_bytes(काष्ठा eerbuffer *eerb)
अणु
	अगर (eerb->head < eerb->tail)
		वापस eerb->tail - eerb->head - 1;
	वापस eerb->buffersize - eerb->head + eerb->tail -1;
पूर्ण

/*
 * How many bytes of buffer space are used.
 * Needs to be called with bufferlock held.
 */
अटल पूर्णांक dasd_eer_get_filled_bytes(काष्ठा eerbuffer *eerb)
अणु

	अगर (eerb->head >= eerb->tail)
		वापस eerb->head - eerb->tail;
	वापस eerb->buffersize - eerb->tail + eerb->head;
पूर्ण

/*
 * The dasd_eer_ग_लिखो_buffer function just copies count bytes of data
 * to the buffer. Make sure to call dasd_eer_start_record first, to
 * make sure that enough मुक्त space is available.
 * Needs to be called with bufferlock held.
 */
अटल व्योम dasd_eer_ग_लिखो_buffer(काष्ठा eerbuffer *eerb,
				  अक्षर *data, पूर्णांक count)
अणु

	अचिन्हित दीर्घ headindex,localhead;
	अचिन्हित दीर्घ rest, len;
	अक्षर *nextdata;

	nextdata = data;
	rest = count;
	जबतक (rest > 0) अणु
 		headindex = eerb->head / PAGE_SIZE;
 		localhead = eerb->head % PAGE_SIZE;
		len = min(rest, PAGE_SIZE - localhead);
		स_नकल(eerb->buffer[headindex]+localhead, nextdata, len);
		nextdata += len;
		rest -= len;
		eerb->head += len;
		अगर (eerb->head == eerb->buffersize)
			eerb->head = 0; /* wrap around */
		BUG_ON(eerb->head > eerb->buffersize);
	पूर्ण
पूर्ण

/*
 * Needs to be called with bufferlock held.
 */
अटल पूर्णांक dasd_eer_पढ़ो_buffer(काष्ठा eerbuffer *eerb, अक्षर *data, पूर्णांक count)
अणु

	अचिन्हित दीर्घ tailindex,localtail;
	अचिन्हित दीर्घ rest, len, finalcount;
	अक्षर *nextdata;

	finalcount = min(count, dasd_eer_get_filled_bytes(eerb));
	nextdata = data;
	rest = finalcount;
	जबतक (rest > 0) अणु
 		tailindex = eerb->tail / PAGE_SIZE;
 		localtail = eerb->tail % PAGE_SIZE;
		len = min(rest, PAGE_SIZE - localtail);
		स_नकल(nextdata, eerb->buffer[tailindex] + localtail, len);
		nextdata += len;
		rest -= len;
		eerb->tail += len;
		अगर (eerb->tail == eerb->buffersize)
			eerb->tail = 0; /* wrap around */
		BUG_ON(eerb->tail > eerb->buffersize);
	पूर्ण
	वापस finalcount;
पूर्ण

/*
 * Whenever you want to ग_लिखो a blob of data to the पूर्णांकernal buffer you
 * have to start by using this function first. It will ग_लिखो the number
 * of bytes that will be written to the buffer. If necessary it will हटाओ
 * old records to make room क्रम the new one.
 * Needs to be called with bufferlock held.
 */
अटल पूर्णांक dasd_eer_start_record(काष्ठा eerbuffer *eerb, पूर्णांक count)
अणु
	पूर्णांक tailcount;

	अगर (count + माप(count) > eerb->buffersize)
		वापस -ENOMEM;
	जबतक (dasd_eer_get_मुक्त_bytes(eerb) < count + माप(count)) अणु
		अगर (eerb->residual > 0) अणु
			eerb->tail += eerb->residual;
			अगर (eerb->tail >= eerb->buffersize)
				eerb->tail -= eerb->buffersize;
			eerb->residual = -1;
		पूर्ण
		dasd_eer_पढ़ो_buffer(eerb, (अक्षर *) &tailcount,
				     माप(tailcount));
		eerb->tail += tailcount;
		अगर (eerb->tail >= eerb->buffersize)
			eerb->tail -= eerb->buffersize;
	पूर्ण
	dasd_eer_ग_लिखो_buffer(eerb, (अक्षर*) &count, माप(count));

	वापस 0;
पूर्ण;

/*
 * Release pages that are not used anymore.
 */
अटल व्योम dasd_eer_मुक्त_buffer_pages(अक्षर **buf, पूर्णांक no_pages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < no_pages; i++)
		मुक्त_page((अचिन्हित दीर्घ) buf[i]);
पूर्ण

/*
 * Allocate a new set of memory pages.
 */
अटल पूर्णांक dasd_eer_allocate_buffer_pages(अक्षर **buf, पूर्णांक no_pages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < no_pages; i++) अणु
		buf[i] = (अक्षर *) get_zeroed_page(GFP_KERNEL);
		अगर (!buf[i]) अणु
			dasd_eer_मुक्त_buffer_pages(buf, i);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * SECTION: The extended error reporting functionality
 */

/*
 * When a DASD device driver wants to report an error, it calls the
 * function dasd_eer_ग_लिखो and gives the respective trigger ID as
 * parameter. Currently there are four kinds of triggers:
 *
 * DASD_EER_FATALERROR:  all kinds of unrecoverable I/O problems
 * DASD_EER_PPRCSUSPEND: PPRC was suspended
 * DASD_EER_NOPATH:      There is no path to the device left.
 * DASD_EER_STATECHANGE: The state of the device has changed.
 *
 * For the first three triggers all required inक्रमmation can be supplied by
 * the caller. For these triggers a record is written by the function
 * dasd_eer_ग_लिखो_standard_trigger.
 *
 * The DASD_EER_STATECHANGE trigger is special since a sense subप्रणाली
 * status ccw need to be executed to gather the necessary sense data first.
 * The dasd_eer_snss function will queue the SNSS request and the request
 * callback will then call dasd_eer_ग_लिखो with the DASD_EER_STATCHANGE
 * trigger.
 *
 * To aव्योम memory allocations at runसमय, the necessary memory is allocated
 * when the extended error reporting is enabled क्रम a device (by
 * dasd_eer_probe). There is one sense subप्रणाली status request क्रम each
 * eer enabled DASD device. The presence of the cqr in device->eer_cqr
 * indicates that eer is enable क्रम the device. The use of the snss request
 * is रक्षित by the DASD_FLAG_EER_IN_USE bit. When this flag indicates
 * that the cqr is currently in use, dasd_eer_snss cannot start a second
 * request but sets the DASD_FLAG_EER_SNSS flag instead. The callback of
 * the SNSS request will check the bit and call dasd_eer_snss again.
 */

#घोषणा SNSS_DATA_SIZE 44

#घोषणा DASD_EER_BUSID_SIZE 10
काष्ठा dasd_eer_header अणु
	__u32 total_size;
	__u32 trigger;
	__u64 tv_sec;
	__u64 tv_usec;
	अक्षर busid[DASD_EER_BUSID_SIZE];
पूर्ण __attribute__ ((packed));

/*
 * The following function can be used क्रम those triggers that have
 * all necessary data available when the function is called.
 * If the parameter cqr is not शून्य, the chain of requests will be searched
 * क्रम valid sense data, and all valid sense data sets will be added to
 * the triggers data.
 */
अटल व्योम dasd_eer_ग_लिखो_standard_trigger(काष्ठा dasd_device *device,
					    काष्ठा dasd_ccw_req *cqr,
					    पूर्णांक trigger)
अणु
	काष्ठा dasd_ccw_req *temp_cqr;
	पूर्णांक data_size;
	काष्ठा बारpec64 ts;
	काष्ठा dasd_eer_header header;
	अचिन्हित दीर्घ flags;
	काष्ठा eerbuffer *eerb;
	अक्षर *sense;

	/* go through cqr chain and count the valid sense data sets */
	data_size = 0;
	क्रम (temp_cqr = cqr; temp_cqr; temp_cqr = temp_cqr->refers)
		अगर (dasd_get_sense(&temp_cqr->irb))
			data_size += 32;

	header.total_size = माप(header) + data_size + 4; /* "EOR" */
	header.trigger = trigger;
	kसमय_get_real_ts64(&ts);
	header.tv_sec = ts.tv_sec;
	header.tv_usec = ts.tv_nsec / NSEC_PER_USEC;
	strlcpy(header.busid, dev_name(&device->cdev->dev),
		DASD_EER_BUSID_SIZE);

	spin_lock_irqsave(&bufferlock, flags);
	list_क्रम_each_entry(eerb, &bufferlist, list) अणु
		dasd_eer_start_record(eerb, header.total_size);
		dasd_eer_ग_लिखो_buffer(eerb, (अक्षर *) &header, माप(header));
		क्रम (temp_cqr = cqr; temp_cqr; temp_cqr = temp_cqr->refers) अणु
			sense = dasd_get_sense(&temp_cqr->irb);
			अगर (sense)
				dasd_eer_ग_लिखो_buffer(eerb, sense, 32);
		पूर्ण
		dasd_eer_ग_लिखो_buffer(eerb, "EOR", 4);
	पूर्ण
	spin_unlock_irqrestore(&bufferlock, flags);
	wake_up_पूर्णांकerruptible(&dasd_eer_पढ़ो_रुको_queue);
पूर्ण

/*
 * This function ग_लिखोs a DASD_EER_STATECHANGE trigger.
 */
अटल व्योम dasd_eer_ग_लिखो_snss_trigger(काष्ठा dasd_device *device,
					काष्ठा dasd_ccw_req *cqr,
					पूर्णांक trigger)
अणु
	पूर्णांक data_size;
	पूर्णांक snss_rc;
	काष्ठा बारpec64 ts;
	काष्ठा dasd_eer_header header;
	अचिन्हित दीर्घ flags;
	काष्ठा eerbuffer *eerb;

	snss_rc = (cqr->status == DASD_CQR_DONE) ? 0 : -EIO;
	अगर (snss_rc)
		data_size = 0;
	अन्यथा
		data_size = SNSS_DATA_SIZE;

	header.total_size = माप(header) + data_size + 4; /* "EOR" */
	header.trigger = DASD_EER_STATECHANGE;
	kसमय_get_real_ts64(&ts);
	header.tv_sec = ts.tv_sec;
	header.tv_usec = ts.tv_nsec / NSEC_PER_USEC;
	strlcpy(header.busid, dev_name(&device->cdev->dev),
		DASD_EER_BUSID_SIZE);

	spin_lock_irqsave(&bufferlock, flags);
	list_क्रम_each_entry(eerb, &bufferlist, list) अणु
		dasd_eer_start_record(eerb, header.total_size);
		dasd_eer_ग_लिखो_buffer(eerb, (अक्षर *) &header , माप(header));
		अगर (!snss_rc)
			dasd_eer_ग_लिखो_buffer(eerb, cqr->data, SNSS_DATA_SIZE);
		dasd_eer_ग_लिखो_buffer(eerb, "EOR", 4);
	पूर्ण
	spin_unlock_irqrestore(&bufferlock, flags);
	wake_up_पूर्णांकerruptible(&dasd_eer_पढ़ो_रुको_queue);
पूर्ण

/*
 * This function is called क्रम all triggers. It calls the appropriate
 * function that ग_लिखोs the actual trigger records.
 */
व्योम dasd_eer_ग_लिखो(काष्ठा dasd_device *device, काष्ठा dasd_ccw_req *cqr,
		    अचिन्हित पूर्णांक id)
अणु
	अगर (!device->eer_cqr)
		वापस;
	चयन (id) अणु
	हाल DASD_EER_FATALERROR:
	हाल DASD_EER_PPRCSUSPEND:
		dasd_eer_ग_लिखो_standard_trigger(device, cqr, id);
		अवरोध;
	हाल DASD_EER_NOPATH:
	हाल DASD_EER_NOSPC:
		dasd_eer_ग_लिखो_standard_trigger(device, शून्य, id);
		अवरोध;
	हाल DASD_EER_STATECHANGE:
		dasd_eer_ग_लिखो_snss_trigger(device, cqr, id);
		अवरोध;
	शेष: /* unknown trigger, so we ग_लिखो it without any sense data */
		dasd_eer_ग_लिखो_standard_trigger(device, शून्य, id);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dasd_eer_ग_लिखो);

/*
 * Start a sense subप्रणाली status request.
 * Needs to be called with the device held.
 */
व्योम dasd_eer_snss(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;

	cqr = device->eer_cqr;
	अगर (!cqr)	/* Device not eer enabled. */
		वापस;
	अगर (test_and_set_bit(DASD_FLAG_EER_IN_USE, &device->flags)) अणु
		/* Sense subप्रणाली status request in use. */
		set_bit(DASD_FLAG_EER_SNSS, &device->flags);
		वापस;
	पूर्ण
	/* cdev is alपढ़ोy locked, can't use dasd_add_request_head */
	clear_bit(DASD_FLAG_EER_SNSS, &device->flags);
	cqr->status = DASD_CQR_QUEUED;
	list_add(&cqr->devlist, &device->ccw_queue);
	dasd_schedule_device_bh(device);
पूर्ण

/*
 * Callback function क्रम use with sense subप्रणाली status request.
 */
अटल व्योम dasd_eer_snss_cb(काष्ठा dasd_ccw_req *cqr, व्योम *data)
अणु
	काष्ठा dasd_device *device = cqr->startdev;
	अचिन्हित दीर्घ flags;

	dasd_eer_ग_लिखो(device, cqr, DASD_EER_STATECHANGE);
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	अगर (device->eer_cqr == cqr) अणु
		clear_bit(DASD_FLAG_EER_IN_USE, &device->flags);
		अगर (test_bit(DASD_FLAG_EER_SNSS, &device->flags))
			/* Another SNSS has been requested in the meanसमय. */
			dasd_eer_snss(device);
		cqr = शून्य;
	पूर्ण
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	अगर (cqr)
		/*
		 * Extended error recovery has been चयनed off जबतक
		 * the SNSS request was running. It could even have
		 * been चयनed off and on again in which हाल there
		 * is a new ccw in device->eer_cqr. Free the "old"
		 * snss request now.
		 */
		dasd_sमुक्त_request(cqr, device);
पूर्ण

/*
 * Enable error reporting on a given device.
 */
पूर्णांक dasd_eer_enable(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा ccw1 *ccw;
	पूर्णांक rc = 0;

	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	अगर (device->eer_cqr)
		जाओ out;
	अन्यथा अगर (!device->discipline ||
		 म_भेद(device->discipline->name, "ECKD"))
		rc = -EMEDIUMTYPE;
	अन्यथा अगर (test_bit(DASD_FLAG_OFFLINE, &device->flags))
		rc = -EBUSY;

	अगर (rc)
		जाओ out;

	cqr = dasd_sदो_स्मृति_request(DASD_ECKD_MAGIC, 1 /* SNSS */,
				   SNSS_DATA_SIZE, device, शून्य);
	अगर (IS_ERR(cqr)) अणु
		rc = -ENOMEM;
		cqr = शून्य;
		जाओ out;
	पूर्ण

	cqr->startdev = device;
	cqr->retries = 255;
	cqr->expires = 10 * HZ;
	clear_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags);
	set_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags);

	ccw = cqr->cpaddr;
	ccw->cmd_code = DASD_ECKD_CCW_SNSS;
	ccw->count = SNSS_DATA_SIZE;
	ccw->flags = 0;
	ccw->cda = (__u32)(addr_t) cqr->data;

	cqr->buildclk = get_tod_घड़ी();
	cqr->status = DASD_CQR_FILLED;
	cqr->callback = dasd_eer_snss_cb;

	अगर (!device->eer_cqr) अणु
		device->eer_cqr = cqr;
		cqr = शून्य;
	पूर्ण

out:
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);

	अगर (cqr)
		dasd_sमुक्त_request(cqr, device);

	वापस rc;
पूर्ण

/*
 * Disable error reporting on a given device.
 */
व्योम dasd_eer_disable(काष्ठा dasd_device *device)
अणु
	काष्ठा dasd_ccw_req *cqr;
	अचिन्हित दीर्घ flags;
	पूर्णांक in_use;

	अगर (!device->eer_cqr)
		वापस;
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	cqr = device->eer_cqr;
	device->eer_cqr = शून्य;
	clear_bit(DASD_FLAG_EER_SNSS, &device->flags);
	in_use = test_and_clear_bit(DASD_FLAG_EER_IN_USE, &device->flags);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	अगर (cqr && !in_use)
		dasd_sमुक्त_request(cqr, device);
पूर्ण

/*
 * SECTION: the device operations
 */

/*
 * On the one side we need a lock to access our पूर्णांकernal buffer, on the
 * other side a copy_to_user can sleep. So we need to copy the data we have
 * to transfer in a पढ़ोbuffer, which is रक्षित by the पढ़ोbuffer_mutex.
 */
अटल अक्षर पढ़ोbuffer[PAGE_SIZE];
अटल DEFINE_MUTEX(पढ़ोbuffer_mutex);

अटल पूर्णांक dasd_eer_खोलो(काष्ठा inode *inp, काष्ठा file *filp)
अणु
	काष्ठा eerbuffer *eerb;
	अचिन्हित दीर्घ flags;

	eerb = kzalloc(माप(काष्ठा eerbuffer), GFP_KERNEL);
	अगर (!eerb)
		वापस -ENOMEM;
	eerb->buffer_page_count = eer_pages;
	अगर (eerb->buffer_page_count < 1 ||
	    eerb->buffer_page_count > पूर्णांक_उच्च / PAGE_SIZE) अणु
		kमुक्त(eerb);
		DBF_EVENT(DBF_WARNING, "can't open device since module "
			"parameter eer_pages is smaller than 1 or"
			" bigger than %d", (पूर्णांक)(पूर्णांक_उच्च / PAGE_SIZE));
		वापस -EINVAL;
	पूर्ण
	eerb->buffersize = eerb->buffer_page_count * PAGE_SIZE;
	eerb->buffer = kदो_स्मृति_array(eerb->buffer_page_count, माप(अक्षर *),
				     GFP_KERNEL);
        अगर (!eerb->buffer) अणु
		kमुक्त(eerb);
                वापस -ENOMEM;
	पूर्ण
	अगर (dasd_eer_allocate_buffer_pages(eerb->buffer,
					   eerb->buffer_page_count)) अणु
		kमुक्त(eerb->buffer);
		kमुक्त(eerb);
		वापस -ENOMEM;
	पूर्ण
	filp->निजी_data = eerb;
	spin_lock_irqsave(&bufferlock, flags);
	list_add(&eerb->list, &bufferlist);
	spin_unlock_irqrestore(&bufferlock, flags);

	वापस nonseekable_खोलो(inp,filp);
पूर्ण

अटल पूर्णांक dasd_eer_बंद(काष्ठा inode *inp, काष्ठा file *filp)
अणु
	काष्ठा eerbuffer *eerb;
	अचिन्हित दीर्घ flags;

	eerb = (काष्ठा eerbuffer *) filp->निजी_data;
	spin_lock_irqsave(&bufferlock, flags);
	list_del(&eerb->list);
	spin_unlock_irqrestore(&bufferlock, flags);
	dasd_eer_मुक्त_buffer_pages(eerb->buffer, eerb->buffer_page_count);
	kमुक्त(eerb->buffer);
	kमुक्त(eerb);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dasd_eer_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक tc,rc;
	पूर्णांक tailcount,effective_count;
        अचिन्हित दीर्घ flags;
	काष्ठा eerbuffer *eerb;

	eerb = (काष्ठा eerbuffer *) filp->निजी_data;
	अगर (mutex_lock_पूर्णांकerruptible(&पढ़ोbuffer_mutex))
		वापस -ERESTARTSYS;

	spin_lock_irqsave(&bufferlock, flags);

	अगर (eerb->residual < 0) अणु /* the reमुख्यder of this record */
		                  /* has been deleted             */
		eerb->residual = 0;
		spin_unlock_irqrestore(&bufferlock, flags);
		mutex_unlock(&पढ़ोbuffer_mutex);
		वापस -EIO;
	पूर्ण अन्यथा अगर (eerb->residual > 0) अणु
		/* OK we still have a second half of a record to deliver */
		effective_count = min(eerb->residual, (पूर्णांक) count);
		eerb->residual -= effective_count;
	पूर्ण अन्यथा अणु
		tc = 0;
		जबतक (!tc) अणु
			tc = dasd_eer_पढ़ो_buffer(eerb, (अक्षर *) &tailcount,
						  माप(tailcount));
			अगर (!tc) अणु
				/* no data available */
				spin_unlock_irqrestore(&bufferlock, flags);
				mutex_unlock(&पढ़ोbuffer_mutex);
				अगर (filp->f_flags & O_NONBLOCK)
					वापस -EAGAIN;
				rc = रुको_event_पूर्णांकerruptible(
					dasd_eer_पढ़ो_रुको_queue,
					eerb->head != eerb->tail);
				अगर (rc)
					वापस rc;
				अगर (mutex_lock_पूर्णांकerruptible(&पढ़ोbuffer_mutex))
					वापस -ERESTARTSYS;
				spin_lock_irqsave(&bufferlock, flags);
			पूर्ण
		पूर्ण
		WARN_ON(tc != माप(tailcount));
		effective_count = min(tailcount,(पूर्णांक)count);
		eerb->residual = tailcount - effective_count;
	पूर्ण

	tc = dasd_eer_पढ़ो_buffer(eerb, पढ़ोbuffer, effective_count);
	WARN_ON(tc != effective_count);

	spin_unlock_irqrestore(&bufferlock, flags);

	अगर (copy_to_user(buf, पढ़ोbuffer, effective_count)) अणु
		mutex_unlock(&पढ़ोbuffer_mutex);
		वापस -EFAULT;
	पूर्ण

	mutex_unlock(&पढ़ोbuffer_mutex);
	वापस effective_count;
पूर्ण

अटल __poll_t dasd_eer_poll(काष्ठा file *filp, poll_table *ptable)
अणु
	__poll_t mask;
	अचिन्हित दीर्घ flags;
	काष्ठा eerbuffer *eerb;

	eerb = (काष्ठा eerbuffer *) filp->निजी_data;
	poll_रुको(filp, &dasd_eer_पढ़ो_रुको_queue, ptable);
	spin_lock_irqsave(&bufferlock, flags);
	अगर (eerb->head != eerb->tail)
		mask = EPOLLIN | EPOLLRDNORM ;
	अन्यथा
		mask = 0;
	spin_unlock_irqrestore(&bufferlock, flags);
	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations dasd_eer_fops = अणु
	.खोलो		= &dasd_eer_खोलो,
	.release	= &dasd_eer_बंद,
	.पढ़ो		= &dasd_eer_पढ़ो,
	.poll		= &dasd_eer_poll,
	.owner		= THIS_MODULE,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice *dasd_eer_dev = शून्य;

पूर्णांक __init dasd_eer_init(व्योम)
अणु
	पूर्णांक rc;

	dasd_eer_dev = kzalloc(माप(*dasd_eer_dev), GFP_KERNEL);
	अगर (!dasd_eer_dev)
		वापस -ENOMEM;

	dasd_eer_dev->minor = MISC_DYNAMIC_MINOR;
	dasd_eer_dev->name  = "dasd_eer";
	dasd_eer_dev->fops  = &dasd_eer_fops;

	rc = misc_रेजिस्टर(dasd_eer_dev);
	अगर (rc) अणु
		kमुक्त(dasd_eer_dev);
		dasd_eer_dev = शून्य;
		DBF_EVENT(DBF_ERR, "%s", "dasd_eer_init could not "
		       "register misc device");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dasd_eer_निकास(व्योम)
अणु
	अगर (dasd_eer_dev) अणु
		misc_deरेजिस्टर(dasd_eer_dev);
		kमुक्त(dasd_eer_dev);
		dasd_eer_dev = शून्य;
	पूर्ण
पूर्ण
