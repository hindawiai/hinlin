<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * User-space I/O driver support क्रम HID subप्रणाली
 * Copyright (c) 2012 David Herrmann
 */

/*
 */

#समावेश <linux/atomic.h>
#समावेश <linux/compat.h>
#समावेश <linux/cred.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uhid.h>
#समावेश <linux/रुको.h>

#घोषणा UHID_NAME	"uhid"
#घोषणा UHID_बफ_मानE	32

काष्ठा uhid_device अणु
	काष्ठा mutex devlock;
	bool running;

	__u8 *rd_data;
	uपूर्णांक rd_size;

	काष्ठा hid_device *hid;
	काष्ठा uhid_event input_buf;

	रुको_queue_head_t रुकोq;
	spinlock_t qlock;
	__u8 head;
	__u8 tail;
	काष्ठा uhid_event *outq[UHID_बफ_मानE];

	/* blocking GET_REPORT support; state changes रक्षित by qlock */
	काष्ठा mutex report_lock;
	रुको_queue_head_t report_रुको;
	bool report_running;
	u32 report_id;
	u32 report_type;
	काष्ठा uhid_event report_buf;
	काष्ठा work_काष्ठा worker;
पूर्ण;

अटल काष्ठा miscdevice uhid_misc;

अटल व्योम uhid_device_add_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा uhid_device *uhid = container_of(work, काष्ठा uhid_device, worker);
	पूर्णांक ret;

	ret = hid_add_device(uhid->hid);
	अगर (ret) अणु
		hid_err(uhid->hid, "Cannot register HID device: error %d\n", ret);

		hid_destroy_device(uhid->hid);
		uhid->hid = शून्य;
		uhid->running = false;
	पूर्ण
पूर्ण

अटल व्योम uhid_queue(काष्ठा uhid_device *uhid, काष्ठा uhid_event *ev)
अणु
	__u8 newhead;

	newhead = (uhid->head + 1) % UHID_बफ_मानE;

	अगर (newhead != uhid->tail) अणु
		uhid->outq[uhid->head] = ev;
		uhid->head = newhead;
		wake_up_पूर्णांकerruptible(&uhid->रुकोq);
	पूर्ण अन्यथा अणु
		hid_warn(uhid->hid, "Output queue is full\n");
		kमुक्त(ev);
	पूर्ण
पूर्ण

अटल पूर्णांक uhid_queue_event(काष्ठा uhid_device *uhid, __u32 event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा uhid_event *ev;

	ev = kzalloc(माप(*ev), GFP_KERNEL);
	अगर (!ev)
		वापस -ENOMEM;

	ev->type = event;

	spin_lock_irqsave(&uhid->qlock, flags);
	uhid_queue(uhid, ev);
	spin_unlock_irqrestore(&uhid->qlock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक uhid_hid_start(काष्ठा hid_device *hid)
अणु
	काष्ठा uhid_device *uhid = hid->driver_data;
	काष्ठा uhid_event *ev;
	अचिन्हित दीर्घ flags;

	ev = kzalloc(माप(*ev), GFP_KERNEL);
	अगर (!ev)
		वापस -ENOMEM;

	ev->type = UHID_START;

	अगर (hid->report_क्रमागत[HID_FEATURE_REPORT].numbered)
		ev->u.start.dev_flags |= UHID_DEV_NUMBERED_FEATURE_REPORTS;
	अगर (hid->report_क्रमागत[HID_OUTPUT_REPORT].numbered)
		ev->u.start.dev_flags |= UHID_DEV_NUMBERED_OUTPUT_REPORTS;
	अगर (hid->report_क्रमागत[HID_INPUT_REPORT].numbered)
		ev->u.start.dev_flags |= UHID_DEV_NUMBERED_INPUT_REPORTS;

	spin_lock_irqsave(&uhid->qlock, flags);
	uhid_queue(uhid, ev);
	spin_unlock_irqrestore(&uhid->qlock, flags);

	वापस 0;
पूर्ण

अटल व्योम uhid_hid_stop(काष्ठा hid_device *hid)
अणु
	काष्ठा uhid_device *uhid = hid->driver_data;

	hid->claimed = 0;
	uhid_queue_event(uhid, UHID_STOP);
पूर्ण

अटल पूर्णांक uhid_hid_खोलो(काष्ठा hid_device *hid)
अणु
	काष्ठा uhid_device *uhid = hid->driver_data;

	वापस uhid_queue_event(uhid, UHID_OPEN);
पूर्ण

अटल व्योम uhid_hid_बंद(काष्ठा hid_device *hid)
अणु
	काष्ठा uhid_device *uhid = hid->driver_data;

	uhid_queue_event(uhid, UHID_CLOSE);
पूर्ण

अटल पूर्णांक uhid_hid_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा uhid_device *uhid = hid->driver_data;

	वापस hid_parse_report(hid, uhid->rd_data, uhid->rd_size);
पूर्ण

/* must be called with report_lock held */
अटल पूर्णांक __uhid_report_queue_and_रुको(काष्ठा uhid_device *uhid,
					काष्ठा uhid_event *ev,
					__u32 *report_id)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&uhid->qlock, flags);
	*report_id = ++uhid->report_id;
	uhid->report_type = ev->type + 1;
	uhid->report_running = true;
	uhid_queue(uhid, ev);
	spin_unlock_irqrestore(&uhid->qlock, flags);

	ret = रुको_event_पूर्णांकerruptible_समयout(uhid->report_रुको,
				!uhid->report_running || !uhid->running,
				5 * HZ);
	अगर (!ret || !uhid->running || uhid->report_running)
		ret = -EIO;
	अन्यथा अगर (ret < 0)
		ret = -ERESTARTSYS;
	अन्यथा
		ret = 0;

	uhid->report_running = false;

	वापस ret;
पूर्ण

अटल व्योम uhid_report_wake_up(काष्ठा uhid_device *uhid, u32 id,
				स्थिर काष्ठा uhid_event *ev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uhid->qlock, flags);

	/* id क्रम old report; drop it silently */
	अगर (uhid->report_type != ev->type || uhid->report_id != id)
		जाओ unlock;
	अगर (!uhid->report_running)
		जाओ unlock;

	स_नकल(&uhid->report_buf, ev, माप(*ev));
	uhid->report_running = false;
	wake_up_पूर्णांकerruptible(&uhid->report_रुको);

unlock:
	spin_unlock_irqrestore(&uhid->qlock, flags);
पूर्ण

अटल पूर्णांक uhid_hid_get_report(काष्ठा hid_device *hid, अचिन्हित अक्षर rnum,
			       u8 *buf, माप_प्रकार count, u8 rtype)
अणु
	काष्ठा uhid_device *uhid = hid->driver_data;
	काष्ठा uhid_get_report_reply_req *req;
	काष्ठा uhid_event *ev;
	पूर्णांक ret;

	अगर (!uhid->running)
		वापस -EIO;

	ev = kzalloc(माप(*ev), GFP_KERNEL);
	अगर (!ev)
		वापस -ENOMEM;

	ev->type = UHID_GET_REPORT;
	ev->u.get_report.rnum = rnum;
	ev->u.get_report.rtype = rtype;

	ret = mutex_lock_पूर्णांकerruptible(&uhid->report_lock);
	अगर (ret) अणु
		kमुक्त(ev);
		वापस ret;
	पूर्ण

	/* this _always_ takes ownership of @ev */
	ret = __uhid_report_queue_and_रुको(uhid, ev, &ev->u.get_report.id);
	अगर (ret)
		जाओ unlock;

	req = &uhid->report_buf.u.get_report_reply;
	अगर (req->err) अणु
		ret = -EIO;
	पूर्ण अन्यथा अणु
		ret = min3(count, (माप_प्रकार)req->size, (माप_प्रकार)UHID_DATA_MAX);
		स_नकल(buf, req->data, ret);
	पूर्ण

unlock:
	mutex_unlock(&uhid->report_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक uhid_hid_set_report(काष्ठा hid_device *hid, अचिन्हित अक्षर rnum,
			       स्थिर u8 *buf, माप_प्रकार count, u8 rtype)
अणु
	काष्ठा uhid_device *uhid = hid->driver_data;
	काष्ठा uhid_event *ev;
	पूर्णांक ret;

	अगर (!uhid->running || count > UHID_DATA_MAX)
		वापस -EIO;

	ev = kzalloc(माप(*ev), GFP_KERNEL);
	अगर (!ev)
		वापस -ENOMEM;

	ev->type = UHID_SET_REPORT;
	ev->u.set_report.rnum = rnum;
	ev->u.set_report.rtype = rtype;
	ev->u.set_report.size = count;
	स_नकल(ev->u.set_report.data, buf, count);

	ret = mutex_lock_पूर्णांकerruptible(&uhid->report_lock);
	अगर (ret) अणु
		kमुक्त(ev);
		वापस ret;
	पूर्ण

	/* this _always_ takes ownership of @ev */
	ret = __uhid_report_queue_and_रुको(uhid, ev, &ev->u.set_report.id);
	अगर (ret)
		जाओ unlock;

	अगर (uhid->report_buf.u.set_report_reply.err)
		ret = -EIO;
	अन्यथा
		ret = count;

unlock:
	mutex_unlock(&uhid->report_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक uhid_hid_raw_request(काष्ठा hid_device *hid, अचिन्हित अक्षर reportnum,
				__u8 *buf, माप_प्रकार len, अचिन्हित अक्षर rtype,
				पूर्णांक reqtype)
अणु
	u8 u_rtype;

	चयन (rtype) अणु
	हाल HID_FEATURE_REPORT:
		u_rtype = UHID_FEATURE_REPORT;
		अवरोध;
	हाल HID_OUTPUT_REPORT:
		u_rtype = UHID_OUTPUT_REPORT;
		अवरोध;
	हाल HID_INPUT_REPORT:
		u_rtype = UHID_INPUT_REPORT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (reqtype) अणु
	हाल HID_REQ_GET_REPORT:
		वापस uhid_hid_get_report(hid, reportnum, buf, len, u_rtype);
	हाल HID_REQ_SET_REPORT:
		वापस uhid_hid_set_report(hid, reportnum, buf, len, u_rtype);
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक uhid_hid_output_raw(काष्ठा hid_device *hid, __u8 *buf, माप_प्रकार count,
			       अचिन्हित अक्षर report_type)
अणु
	काष्ठा uhid_device *uhid = hid->driver_data;
	__u8 rtype;
	अचिन्हित दीर्घ flags;
	काष्ठा uhid_event *ev;

	चयन (report_type) अणु
	हाल HID_FEATURE_REPORT:
		rtype = UHID_FEATURE_REPORT;
		अवरोध;
	हाल HID_OUTPUT_REPORT:
		rtype = UHID_OUTPUT_REPORT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (count < 1 || count > UHID_DATA_MAX)
		वापस -EINVAL;

	ev = kzalloc(माप(*ev), GFP_KERNEL);
	अगर (!ev)
		वापस -ENOMEM;

	ev->type = UHID_OUTPUT;
	ev->u.output.size = count;
	ev->u.output.rtype = rtype;
	स_नकल(ev->u.output.data, buf, count);

	spin_lock_irqsave(&uhid->qlock, flags);
	uhid_queue(uhid, ev);
	spin_unlock_irqrestore(&uhid->qlock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक uhid_hid_output_report(काष्ठा hid_device *hid, __u8 *buf,
				  माप_प्रकार count)
अणु
	वापस uhid_hid_output_raw(hid, buf, count, HID_OUTPUT_REPORT);
पूर्ण

काष्ठा hid_ll_driver uhid_hid_driver = अणु
	.start = uhid_hid_start,
	.stop = uhid_hid_stop,
	.खोलो = uhid_hid_खोलो,
	.बंद = uhid_hid_बंद,
	.parse = uhid_hid_parse,
	.raw_request = uhid_hid_raw_request,
	.output_report = uhid_hid_output_report,
पूर्ण;
EXPORT_SYMBOL_GPL(uhid_hid_driver);

#अगर_घोषित CONFIG_COMPAT

/* Apparently we haven't stepped on these rakes enough बार yet. */
काष्ठा uhid_create_req_compat अणु
	__u8 name[128];
	__u8 phys[64];
	__u8 uniq[64];

	compat_uptr_t rd_data;
	__u16 rd_size;

	__u16 bus;
	__u32 venकरोr;
	__u32 product;
	__u32 version;
	__u32 country;
पूर्ण __attribute__((__packed__));

अटल पूर्णांक uhid_event_from_user(स्थिर अक्षर __user *buffer, माप_प्रकार len,
				काष्ठा uhid_event *event)
अणु
	अगर (in_compat_syscall()) अणु
		u32 type;

		अगर (get_user(type, buffer))
			वापस -EFAULT;

		अगर (type == UHID_CREATE) अणु
			/*
			 * This is our messed up request with compat poपूर्णांकer.
			 * It is largish (more than 256 bytes) so we better
			 * allocate it from the heap.
			 */
			काष्ठा uhid_create_req_compat *compat;

			compat = kzalloc(माप(*compat), GFP_KERNEL);
			अगर (!compat)
				वापस -ENOMEM;

			buffer += माप(type);
			len -= माप(type);
			अगर (copy_from_user(compat, buffer,
					   min(len, माप(*compat)))) अणु
				kमुक्त(compat);
				वापस -EFAULT;
			पूर्ण

			/* Shuffle the data over to proper काष्ठाure */
			event->type = type;

			स_नकल(event->u.create.name, compat->name,
				माप(compat->name));
			स_नकल(event->u.create.phys, compat->phys,
				माप(compat->phys));
			स_नकल(event->u.create.uniq, compat->uniq,
				माप(compat->uniq));

			event->u.create.rd_data = compat_ptr(compat->rd_data);
			event->u.create.rd_size = compat->rd_size;

			event->u.create.bus = compat->bus;
			event->u.create.venकरोr = compat->venकरोr;
			event->u.create.product = compat->product;
			event->u.create.version = compat->version;
			event->u.create.country = compat->country;

			kमुक्त(compat);
			वापस 0;
		पूर्ण
		/* All others can be copied directly */
	पूर्ण

	अगर (copy_from_user(event, buffer, min(len, माप(*event))))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक uhid_event_from_user(स्थिर अक्षर __user *buffer, माप_प्रकार len,
				काष्ठा uhid_event *event)
अणु
	अगर (copy_from_user(event, buffer, min(len, माप(*event))))
		वापस -EFAULT;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक uhid_dev_create2(काष्ठा uhid_device *uhid,
			    स्थिर काष्ठा uhid_event *ev)
अणु
	काष्ठा hid_device *hid;
	माप_प्रकार rd_size, len;
	व्योम *rd_data;
	पूर्णांक ret;

	अगर (uhid->running)
		वापस -EALREADY;

	rd_size = ev->u.create2.rd_size;
	अगर (rd_size <= 0 || rd_size > HID_MAX_DESCRIPTOR_SIZE)
		वापस -EINVAL;

	rd_data = kmemdup(ev->u.create2.rd_data, rd_size, GFP_KERNEL);
	अगर (!rd_data)
		वापस -ENOMEM;

	uhid->rd_size = rd_size;
	uhid->rd_data = rd_data;

	hid = hid_allocate_device();
	अगर (IS_ERR(hid)) अणु
		ret = PTR_ERR(hid);
		जाओ err_मुक्त;
	पूर्ण

	/* @hid is zero-initialized, म_नकलन() is correct, strlcpy() not */
	len = min(माप(hid->name), माप(ev->u.create2.name)) - 1;
	म_नकलन(hid->name, ev->u.create2.name, len);
	len = min(माप(hid->phys), माप(ev->u.create2.phys)) - 1;
	म_नकलन(hid->phys, ev->u.create2.phys, len);
	len = min(माप(hid->uniq), माप(ev->u.create2.uniq)) - 1;
	म_नकलन(hid->uniq, ev->u.create2.uniq, len);

	hid->ll_driver = &uhid_hid_driver;
	hid->bus = ev->u.create2.bus;
	hid->venकरोr = ev->u.create2.venकरोr;
	hid->product = ev->u.create2.product;
	hid->version = ev->u.create2.version;
	hid->country = ev->u.create2.country;
	hid->driver_data = uhid;
	hid->dev.parent = uhid_misc.this_device;

	uhid->hid = hid;
	uhid->running = true;

	/* Adding of a HID device is करोne through a worker, to allow HID drivers
	 * which use feature requests during .probe to work, without they would
	 * be blocked on devlock, which is held by uhid_अक्षर_ग_लिखो.
	 */
	schedule_work(&uhid->worker);

	वापस 0;

err_मुक्त:
	kमुक्त(uhid->rd_data);
	uhid->rd_data = शून्य;
	uhid->rd_size = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक uhid_dev_create(काष्ठा uhid_device *uhid,
			   काष्ठा uhid_event *ev)
अणु
	काष्ठा uhid_create_req orig;

	orig = ev->u.create;

	अगर (orig.rd_size <= 0 || orig.rd_size > HID_MAX_DESCRIPTOR_SIZE)
		वापस -EINVAL;
	अगर (copy_from_user(&ev->u.create2.rd_data, orig.rd_data, orig.rd_size))
		वापस -EFAULT;

	स_नकल(ev->u.create2.name, orig.name, माप(orig.name));
	स_नकल(ev->u.create2.phys, orig.phys, माप(orig.phys));
	स_नकल(ev->u.create2.uniq, orig.uniq, माप(orig.uniq));
	ev->u.create2.rd_size = orig.rd_size;
	ev->u.create2.bus = orig.bus;
	ev->u.create2.venकरोr = orig.venकरोr;
	ev->u.create2.product = orig.product;
	ev->u.create2.version = orig.version;
	ev->u.create2.country = orig.country;

	वापस uhid_dev_create2(uhid, ev);
पूर्ण

अटल पूर्णांक uhid_dev_destroy(काष्ठा uhid_device *uhid)
अणु
	अगर (!uhid->running)
		वापस -EINVAL;

	uhid->running = false;
	wake_up_पूर्णांकerruptible(&uhid->report_रुको);

	cancel_work_sync(&uhid->worker);

	hid_destroy_device(uhid->hid);
	kमुक्त(uhid->rd_data);

	वापस 0;
पूर्ण

अटल पूर्णांक uhid_dev_input(काष्ठा uhid_device *uhid, काष्ठा uhid_event *ev)
अणु
	अगर (!uhid->running)
		वापस -EINVAL;

	hid_input_report(uhid->hid, HID_INPUT_REPORT, ev->u.input.data,
			 min_t(माप_प्रकार, ev->u.input.size, UHID_DATA_MAX), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक uhid_dev_input2(काष्ठा uhid_device *uhid, काष्ठा uhid_event *ev)
अणु
	अगर (!uhid->running)
		वापस -EINVAL;

	hid_input_report(uhid->hid, HID_INPUT_REPORT, ev->u.input2.data,
			 min_t(माप_प्रकार, ev->u.input2.size, UHID_DATA_MAX), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक uhid_dev_get_report_reply(काष्ठा uhid_device *uhid,
				     काष्ठा uhid_event *ev)
अणु
	अगर (!uhid->running)
		वापस -EINVAL;

	uhid_report_wake_up(uhid, ev->u.get_report_reply.id, ev);
	वापस 0;
पूर्ण

अटल पूर्णांक uhid_dev_set_report_reply(काष्ठा uhid_device *uhid,
				     काष्ठा uhid_event *ev)
अणु
	अगर (!uhid->running)
		वापस -EINVAL;

	uhid_report_wake_up(uhid, ev->u.set_report_reply.id, ev);
	वापस 0;
पूर्ण

अटल पूर्णांक uhid_अक्षर_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा uhid_device *uhid;

	uhid = kzalloc(माप(*uhid), GFP_KERNEL);
	अगर (!uhid)
		वापस -ENOMEM;

	mutex_init(&uhid->devlock);
	mutex_init(&uhid->report_lock);
	spin_lock_init(&uhid->qlock);
	init_रुकोqueue_head(&uhid->रुकोq);
	init_रुकोqueue_head(&uhid->report_रुको);
	uhid->running = false;
	INIT_WORK(&uhid->worker, uhid_device_add_worker);

	file->निजी_data = uhid;
	stream_खोलो(inode, file);

	वापस 0;
पूर्ण

अटल पूर्णांक uhid_अक्षर_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा uhid_device *uhid = file->निजी_data;
	अचिन्हित पूर्णांक i;

	uhid_dev_destroy(uhid);

	क्रम (i = 0; i < UHID_बफ_मानE; ++i)
		kमुक्त(uhid->outq[i]);

	kमुक्त(uhid);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार uhid_अक्षर_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा uhid_device *uhid = file->निजी_data;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	माप_प्रकार len;

	/* they need at least the "type" member of uhid_event */
	अगर (count < माप(__u32))
		वापस -EINVAL;

try_again:
	अगर (file->f_flags & O_NONBLOCK) अणु
		अगर (uhid->head == uhid->tail)
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		ret = रुको_event_पूर्णांकerruptible(uhid->रुकोq,
						uhid->head != uhid->tail);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&uhid->devlock);
	अगर (ret)
		वापस ret;

	अगर (uhid->head == uhid->tail) अणु
		mutex_unlock(&uhid->devlock);
		जाओ try_again;
	पूर्ण अन्यथा अणु
		len = min(count, माप(**uhid->outq));
		अगर (copy_to_user(buffer, uhid->outq[uhid->tail], len)) अणु
			ret = -EFAULT;
		पूर्ण अन्यथा अणु
			kमुक्त(uhid->outq[uhid->tail]);
			uhid->outq[uhid->tail] = शून्य;

			spin_lock_irqsave(&uhid->qlock, flags);
			uhid->tail = (uhid->tail + 1) % UHID_बफ_मानE;
			spin_unlock_irqrestore(&uhid->qlock, flags);
		पूर्ण
	पूर्ण

	mutex_unlock(&uhid->devlock);
	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार uhid_अक्षर_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा uhid_device *uhid = file->निजी_data;
	पूर्णांक ret;
	माप_प्रकार len;

	/* we need at least the "type" member of uhid_event */
	अगर (count < माप(__u32))
		वापस -EINVAL;

	ret = mutex_lock_पूर्णांकerruptible(&uhid->devlock);
	अगर (ret)
		वापस ret;

	स_रखो(&uhid->input_buf, 0, माप(uhid->input_buf));
	len = min(count, माप(uhid->input_buf));

	ret = uhid_event_from_user(buffer, len, &uhid->input_buf);
	अगर (ret)
		जाओ unlock;

	चयन (uhid->input_buf.type) अणु
	हाल UHID_CREATE:
		/*
		 * 'struct uhid_create_req' contains a __user poपूर्णांकer which is
		 * copied from, so it's unsafe to allow this with elevated
		 * privileges (e.g. from a setuid binary) or via kernel_ग_लिखो().
		 */
		अगर (file->f_cred != current_cred() || uaccess_kernel()) अणु
			pr_err_once("UHID_CREATE from different security context by process %d (%s), this is not allowed.\n",
				    task_tgid_vnr(current), current->comm);
			ret = -EACCES;
			जाओ unlock;
		पूर्ण
		ret = uhid_dev_create(uhid, &uhid->input_buf);
		अवरोध;
	हाल UHID_CREATE2:
		ret = uhid_dev_create2(uhid, &uhid->input_buf);
		अवरोध;
	हाल UHID_DESTROY:
		ret = uhid_dev_destroy(uhid);
		अवरोध;
	हाल UHID_INPUT:
		ret = uhid_dev_input(uhid, &uhid->input_buf);
		अवरोध;
	हाल UHID_INPUT2:
		ret = uhid_dev_input2(uhid, &uhid->input_buf);
		अवरोध;
	हाल UHID_GET_REPORT_REPLY:
		ret = uhid_dev_get_report_reply(uhid, &uhid->input_buf);
		अवरोध;
	हाल UHID_SET_REPORT_REPLY:
		ret = uhid_dev_set_report_reply(uhid, &uhid->input_buf);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

unlock:
	mutex_unlock(&uhid->devlock);

	/* वापस "count" not "len" to not confuse the caller */
	वापस ret ? ret : count;
पूर्ण

अटल __poll_t uhid_अक्षर_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा uhid_device *uhid = file->निजी_data;
	__poll_t mask = EPOLLOUT | EPOLLWRNORM; /* uhid is always writable */

	poll_रुको(file, &uhid->रुकोq, रुको);

	अगर (uhid->head != uhid->tail)
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations uhid_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= uhid_अक्षर_खोलो,
	.release	= uhid_अक्षर_release,
	.पढ़ो		= uhid_अक्षर_पढ़ो,
	.ग_लिखो		= uhid_अक्षर_ग_लिखो,
	.poll		= uhid_अक्षर_poll,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice uhid_misc = अणु
	.fops		= &uhid_fops,
	.minor		= UHID_MINOR,
	.name		= UHID_NAME,
पूर्ण;
module_misc_device(uhid_misc);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Herrmann <dh.herrmann@gmail.com>");
MODULE_DESCRIPTION("User-space I/O driver support for HID subsystem");
MODULE_ALIAS_MISCDEV(UHID_MINOR);
MODULE_ALIAS("devname:" UHID_NAME);
