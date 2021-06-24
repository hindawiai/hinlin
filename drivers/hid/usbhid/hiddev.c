<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2001 Paul Stewart
 *  Copyright (c) 2001 Vojtech Pavlik
 *
 *  HID अक्षर devices, giving access to raw HID device events.
 */

/*
 *
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to Paul Stewart <stewart@wetlogic.net>
 */

#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/usb.h>
#समावेश <linux/hid.h>
#समावेश <linux/hiddev.h>
#समावेश <linux/compat.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/nospec.h>
#समावेश "usbhid.h"

#अगर_घोषित CONFIG_USB_DYNAMIC_MINORS
#घोषणा HIDDEV_MINOR_BASE	0
#घोषणा HIDDEV_MINORS		256
#अन्यथा
#घोषणा HIDDEV_MINOR_BASE	96
#घोषणा HIDDEV_MINORS		16
#पूर्ण_अगर
#घोषणा HIDDEV_BUFFER_SIZE	2048

काष्ठा hiddev_list अणु
	काष्ठा hiddev_usage_ref buffer[HIDDEV_BUFFER_SIZE];
	पूर्णांक head;
	पूर्णांक tail;
	अचिन्हित flags;
	काष्ठा fasync_काष्ठा *fasync;
	काष्ठा hiddev *hiddev;
	काष्ठा list_head node;
	काष्ठा mutex thपढ़ो_lock;
पूर्ण;

/*
 * Find a report, given the report's type and ID.  The ID can be specअगरied
 * indirectly by REPORT_ID_FIRST (which वापसs the first report of the given
 * type) or by (REPORT_ID_NEXT | old_id), which वापसs the next report of the
 * given type which follows old_id.
 */
अटल काष्ठा hid_report *
hiddev_lookup_report(काष्ठा hid_device *hid, काष्ठा hiddev_report_info *rinfo)
अणु
	अचिन्हित पूर्णांक flags = rinfo->report_id & ~HID_REPORT_ID_MASK;
	अचिन्हित पूर्णांक rid = rinfo->report_id & HID_REPORT_ID_MASK;
	काष्ठा hid_report_क्रमागत *report_क्रमागत;
	काष्ठा hid_report *report;
	काष्ठा list_head *list;

	अगर (rinfo->report_type < HID_REPORT_TYPE_MIN ||
	    rinfo->report_type > HID_REPORT_TYPE_MAX)
		वापस शून्य;

	report_क्रमागत = hid->report_क्रमागत +
		(rinfo->report_type - HID_REPORT_TYPE_MIN);

	चयन (flags) अणु
	हाल 0: /* Nothing to करो -- report_id is alपढ़ोy set correctly */
		अवरोध;

	हाल HID_REPORT_ID_FIRST:
		अगर (list_empty(&report_क्रमागत->report_list))
			वापस शून्य;

		list = report_क्रमागत->report_list.next;
		report = list_entry(list, काष्ठा hid_report, list);
		rinfo->report_id = report->id;
		अवरोध;

	हाल HID_REPORT_ID_NEXT:
		report = report_क्रमागत->report_id_hash[rid];
		अगर (!report)
			वापस शून्य;

		list = report->list.next;
		अगर (list == &report_क्रमागत->report_list)
			वापस शून्य;

		report = list_entry(list, काष्ठा hid_report, list);
		rinfo->report_id = report->id;
		अवरोध;

	शेष:
		वापस शून्य;
	पूर्ण

	वापस report_क्रमागत->report_id_hash[rinfo->report_id];
पूर्ण

/*
 * Perक्रमm an exhaustive search of the report table क्रम a usage, given its
 * type and usage id.
 */
अटल काष्ठा hid_field *
hiddev_lookup_usage(काष्ठा hid_device *hid, काष्ठा hiddev_usage_ref *uref)
अणु
	पूर्णांक i, j;
	काष्ठा hid_report *report;
	काष्ठा hid_report_क्रमागत *report_क्रमागत;
	काष्ठा hid_field *field;

	अगर (uref->report_type < HID_REPORT_TYPE_MIN ||
	    uref->report_type > HID_REPORT_TYPE_MAX)
		वापस शून्य;

	report_क्रमागत = hid->report_क्रमागत +
		(uref->report_type - HID_REPORT_TYPE_MIN);

	list_क्रम_each_entry(report, &report_क्रमागत->report_list, list) अणु
		क्रम (i = 0; i < report->maxfield; i++) अणु
			field = report->field[i];
			क्रम (j = 0; j < field->maxusage; j++) अणु
				अगर (field->usage[j].hid == uref->usage_code) अणु
					uref->report_id = report->id;
					uref->field_index = i;
					uref->usage_index = j;
					वापस field;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम hiddev_send_event(काष्ठा hid_device *hid,
			      काष्ठा hiddev_usage_ref *uref)
अणु
	काष्ठा hiddev *hiddev = hid->hiddev;
	काष्ठा hiddev_list *list;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hiddev->list_lock, flags);
	list_क्रम_each_entry(list, &hiddev->list, node) अणु
		अगर (uref->field_index != HID_FIELD_INDEX_NONE ||
		    (list->flags & HIDDEV_FLAG_REPORT) != 0) अणु
			list->buffer[list->head] = *uref;
			list->head = (list->head + 1) &
				(HIDDEV_BUFFER_SIZE - 1);
			समाप्त_fasync(&list->fasync, SIGIO, POLL_IN);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hiddev->list_lock, flags);

	wake_up_पूर्णांकerruptible(&hiddev->रुको);
पूर्ण

/*
 * This is where hid.c calls पूर्णांकo hiddev to pass an event that occurred over
 * the पूर्णांकerrupt pipe
 */
व्योम hiddev_hid_event(काष्ठा hid_device *hid, काष्ठा hid_field *field,
		      काष्ठा hid_usage *usage, __s32 value)
अणु
	अचिन्हित type = field->report_type;
	काष्ठा hiddev_usage_ref uref;

	uref.report_type =
	  (type == HID_INPUT_REPORT) ? HID_REPORT_TYPE_INPUT :
	  ((type == HID_OUTPUT_REPORT) ? HID_REPORT_TYPE_OUTPUT :
	   ((type == HID_FEATURE_REPORT) ? HID_REPORT_TYPE_FEATURE : 0));
	uref.report_id = field->report->id;
	uref.field_index = field->index;
	uref.usage_index = (usage - field->usage);
	uref.usage_code = usage->hid;
	uref.value = value;

	hiddev_send_event(hid, &uref);
पूर्ण
EXPORT_SYMBOL_GPL(hiddev_hid_event);

व्योम hiddev_report_event(काष्ठा hid_device *hid, काष्ठा hid_report *report)
अणु
	अचिन्हित type = report->type;
	काष्ठा hiddev_usage_ref uref;

	स_रखो(&uref, 0, माप(uref));
	uref.report_type =
	  (type == HID_INPUT_REPORT) ? HID_REPORT_TYPE_INPUT :
	  ((type == HID_OUTPUT_REPORT) ? HID_REPORT_TYPE_OUTPUT :
	   ((type == HID_FEATURE_REPORT) ? HID_REPORT_TYPE_FEATURE : 0));
	uref.report_id = report->id;
	uref.field_index = HID_FIELD_INDEX_NONE;

	hiddev_send_event(hid, &uref);
पूर्ण

/*
 * fasync file op
 */
अटल पूर्णांक hiddev_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा hiddev_list *list = file->निजी_data;

	वापस fasync_helper(fd, file, on, &list->fasync);
पूर्ण


/*
 * release file op
 */
अटल पूर्णांक hiddev_release(काष्ठा inode * inode, काष्ठा file * file)
अणु
	काष्ठा hiddev_list *list = file->निजी_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list->hiddev->list_lock, flags);
	list_del(&list->node);
	spin_unlock_irqrestore(&list->hiddev->list_lock, flags);

	mutex_lock(&list->hiddev->existancelock);
	अगर (!--list->hiddev->खोलो) अणु
		अगर (list->hiddev->exist) अणु
			hid_hw_बंद(list->hiddev->hid);
			hid_hw_घातer(list->hiddev->hid, PM_HINT_NORMAL);
		पूर्ण अन्यथा अणु
			mutex_unlock(&list->hiddev->existancelock);
			kमुक्त(list->hiddev);
			vमुक्त(list);
			वापस 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&list->hiddev->existancelock);
	vमुक्त(list);

	वापस 0;
पूर्ण

अटल पूर्णांक __hiddev_खोलो(काष्ठा hiddev *hiddev, काष्ठा file *file)
अणु
	काष्ठा hiddev_list *list;
	पूर्णांक error;

	lockdep_निश्चित_held(&hiddev->existancelock);

	list = vzalloc(माप(*list));
	अगर (!list)
		वापस -ENOMEM;

	mutex_init(&list->thपढ़ो_lock);
	list->hiddev = hiddev;

	अगर (!hiddev->खोलो++) अणु
		error = hid_hw_घातer(hiddev->hid, PM_HINT_FULLON);
		अगर (error < 0)
			जाओ err_drop_count;

		error = hid_hw_खोलो(hiddev->hid);
		अगर (error < 0)
			जाओ err_normal_घातer;
	पूर्ण

	spin_lock_irq(&hiddev->list_lock);
	list_add_tail(&list->node, &hiddev->list);
	spin_unlock_irq(&hiddev->list_lock);

	file->निजी_data = list;

	वापस 0;

err_normal_घातer:
	hid_hw_घातer(hiddev->hid, PM_HINT_NORMAL);
err_drop_count:
	hiddev->खोलो--;
	vमुक्त(list);
	वापस error;
पूर्ण

/*
 * खोलो file op
 */
अटल पूर्णांक hiddev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा hid_device *hid;
	काष्ठा hiddev *hiddev;
	पूर्णांक res;

	पूर्णांकf = usbhid_find_पूर्णांकerface(iminor(inode));
	अगर (!पूर्णांकf)
		वापस -ENODEV;

	hid = usb_get_पूर्णांकfdata(पूर्णांकf);
	hiddev = hid->hiddev;

	mutex_lock(&hiddev->existancelock);
	res = hiddev->exist ? __hiddev_खोलो(hiddev, file) : -ENODEV;
	mutex_unlock(&hiddev->existancelock);

	वापस res;
पूर्ण

/*
 * "write" file op
 */
अटल sमाप_प्रकार hiddev_ग_लिखो(काष्ठा file * file, स्थिर अक्षर __user * buffer, माप_प्रकार count, loff_t *ppos)
अणु
	वापस -EINVAL;
पूर्ण

/*
 * "read" file op
 */
अटल sमाप_प्रकार hiddev_पढ़ो(काष्ठा file * file, अक्षर __user * buffer, माप_प्रकार count, loff_t *ppos)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा hiddev_list *list = file->निजी_data;
	पूर्णांक event_size;
	पूर्णांक retval;

	event_size = ((list->flags & HIDDEV_FLAG_UREF) != 0) ?
		माप(काष्ठा hiddev_usage_ref) : माप(काष्ठा hiddev_event);

	अगर (count < event_size)
		वापस 0;

	/* lock against other thपढ़ोs */
	retval = mutex_lock_पूर्णांकerruptible(&list->thपढ़ो_lock);
	अगर (retval)
		वापस -ERESTARTSYS;

	जबतक (retval == 0) अणु
		अगर (list->head == list->tail) अणु
			prepare_to_रुको(&list->hiddev->रुको, &रुको, TASK_INTERRUPTIBLE);

			जबतक (list->head == list->tail) अणु
				अगर (संकेत_pending(current)) अणु
					retval = -ERESTARTSYS;
					अवरोध;
				पूर्ण
				अगर (!list->hiddev->exist) अणु
					retval = -EIO;
					अवरोध;
				पूर्ण
				अगर (file->f_flags & O_NONBLOCK) अणु
					retval = -EAGAIN;
					अवरोध;
				पूर्ण

				/* let O_NONBLOCK tasks run */
				mutex_unlock(&list->thपढ़ो_lock);
				schedule();
				अगर (mutex_lock_पूर्णांकerruptible(&list->thपढ़ो_lock)) अणु
					finish_रुको(&list->hiddev->रुको, &रुको);
					वापस -EINTR;
				पूर्ण
				set_current_state(TASK_INTERRUPTIBLE);
			पूर्ण
			finish_रुको(&list->hiddev->रुको, &रुको);

		पूर्ण

		अगर (retval) अणु
			mutex_unlock(&list->thपढ़ो_lock);
			वापस retval;
		पूर्ण


		जबतक (list->head != list->tail &&
		       retval + event_size <= count) अणु
			अगर ((list->flags & HIDDEV_FLAG_UREF) == 0) अणु
				अगर (list->buffer[list->tail].field_index != HID_FIELD_INDEX_NONE) अणु
					काष्ठा hiddev_event event;

					event.hid = list->buffer[list->tail].usage_code;
					event.value = list->buffer[list->tail].value;
					अगर (copy_to_user(buffer + retval, &event, माप(काष्ठा hiddev_event))) अणु
						mutex_unlock(&list->thपढ़ो_lock);
						वापस -EFAULT;
					पूर्ण
					retval += माप(काष्ठा hiddev_event);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (list->buffer[list->tail].field_index != HID_FIELD_INDEX_NONE ||
				    (list->flags & HIDDEV_FLAG_REPORT) != 0) अणु

					अगर (copy_to_user(buffer + retval, list->buffer + list->tail, माप(काष्ठा hiddev_usage_ref))) अणु
						mutex_unlock(&list->thपढ़ो_lock);
						वापस -EFAULT;
					पूर्ण
					retval += माप(काष्ठा hiddev_usage_ref);
				पूर्ण
			पूर्ण
			list->tail = (list->tail + 1) & (HIDDEV_BUFFER_SIZE - 1);
		पूर्ण

	पूर्ण
	mutex_unlock(&list->thपढ़ो_lock);

	वापस retval;
पूर्ण

/*
 * "poll" file op
 * No kernel lock - fine
 */
अटल __poll_t hiddev_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा hiddev_list *list = file->निजी_data;

	poll_रुको(file, &list->hiddev->रुको, रुको);
	अगर (list->head != list->tail)
		वापस EPOLLIN | EPOLLRDNORM | EPOLLOUT;
	अगर (!list->hiddev->exist)
		वापस EPOLLERR | EPOLLHUP;
	वापस 0;
पूर्ण

/*
 * "ioctl" file op
 */
अटल noअंतरभूत पूर्णांक hiddev_ioctl_usage(काष्ठा hiddev *hiddev, अचिन्हित पूर्णांक cmd, व्योम __user *user_arg)
अणु
	काष्ठा hid_device *hid = hiddev->hid;
	काष्ठा hiddev_report_info rinfo;
	काष्ठा hiddev_usage_ref_multi *uref_multi = शून्य;
	काष्ठा hiddev_usage_ref *uref;
	काष्ठा hid_report *report;
	काष्ठा hid_field *field;
	पूर्णांक i;

	uref_multi = kदो_स्मृति(माप(काष्ठा hiddev_usage_ref_multi), GFP_KERNEL);
	अगर (!uref_multi)
		वापस -ENOMEM;
	uref = &uref_multi->uref;
	अगर (cmd == HIDIOCGUSAGES || cmd == HIDIOCSUSAGES) अणु
		अगर (copy_from_user(uref_multi, user_arg,
				   माप(*uref_multi)))
			जाओ fault;
	पूर्ण अन्यथा अणु
		अगर (copy_from_user(uref, user_arg, माप(*uref)))
			जाओ fault;
	पूर्ण

	चयन (cmd) अणु
	हाल HIDIOCGUCODE:
		rinfo.report_type = uref->report_type;
		rinfo.report_id = uref->report_id;
		अगर ((report = hiddev_lookup_report(hid, &rinfo)) == शून्य)
			जाओ inval;

		अगर (uref->field_index >= report->maxfield)
			जाओ inval;
		uref->field_index = array_index_nospec(uref->field_index,
						       report->maxfield);

		field = report->field[uref->field_index];
		अगर (uref->usage_index >= field->maxusage)
			जाओ inval;
		uref->usage_index = array_index_nospec(uref->usage_index,
						       field->maxusage);

		uref->usage_code = field->usage[uref->usage_index].hid;

		अगर (copy_to_user(user_arg, uref, माप(*uref)))
			जाओ fault;

		जाओ goodवापस;

	शेष:
		अगर (cmd != HIDIOCGUSAGE &&
		    cmd != HIDIOCGUSAGES &&
		    uref->report_type == HID_REPORT_TYPE_INPUT)
			जाओ inval;

		अगर (uref->report_id == HID_REPORT_ID_UNKNOWN) अणु
			field = hiddev_lookup_usage(hid, uref);
			अगर (field == शून्य)
				जाओ inval;
		पूर्ण अन्यथा अणु
			rinfo.report_type = uref->report_type;
			rinfo.report_id = uref->report_id;
			अगर ((report = hiddev_lookup_report(hid, &rinfo)) == शून्य)
				जाओ inval;

			अगर (uref->field_index >= report->maxfield)
				जाओ inval;
			uref->field_index = array_index_nospec(uref->field_index,
							       report->maxfield);

			field = report->field[uref->field_index];

			अगर (cmd == HIDIOCGCOLLECTIONINDEX) अणु
				अगर (uref->usage_index >= field->maxusage)
					जाओ inval;
				uref->usage_index =
					array_index_nospec(uref->usage_index,
							   field->maxusage);
			पूर्ण अन्यथा अगर (uref->usage_index >= field->report_count)
				जाओ inval;
		पूर्ण

		अगर (cmd == HIDIOCGUSAGES || cmd == HIDIOCSUSAGES) अणु
			अगर (uref_multi->num_values > HID_MAX_MULTI_USAGES ||
			    uref->usage_index + uref_multi->num_values >
			    field->report_count)
				जाओ inval;

			uref->usage_index =
				array_index_nospec(uref->usage_index,
						   field->report_count -
						   uref_multi->num_values);
		पूर्ण

		चयन (cmd) अणु
		हाल HIDIOCGUSAGE:
			अगर (uref->usage_index >= field->report_count)
				जाओ inval;
			uref->value = field->value[uref->usage_index];
			अगर (copy_to_user(user_arg, uref, माप(*uref)))
				जाओ fault;
			जाओ goodवापस;

		हाल HIDIOCSUSAGE:
			अगर (uref->usage_index >= field->report_count)
				जाओ inval;
			field->value[uref->usage_index] = uref->value;
			जाओ goodवापस;

		हाल HIDIOCGCOLLECTIONINDEX:
			i = field->usage[uref->usage_index].collection_index;
			kमुक्त(uref_multi);
			वापस i;
		हाल HIDIOCGUSAGES:
			क्रम (i = 0; i < uref_multi->num_values; i++)
				uref_multi->values[i] =
				    field->value[uref->usage_index + i];
			अगर (copy_to_user(user_arg, uref_multi,
					 माप(*uref_multi)))
				जाओ fault;
			जाओ goodवापस;
		हाल HIDIOCSUSAGES:
			क्रम (i = 0; i < uref_multi->num_values; i++)
				field->value[uref->usage_index + i] =
				    uref_multi->values[i];
			जाओ goodवापस;
		पूर्ण

goodवापस:
		kमुक्त(uref_multi);
		वापस 0;
fault:
		kमुक्त(uref_multi);
		वापस -EFAULT;
inval:
		kमुक्त(uref_multi);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल noअंतरभूत पूर्णांक hiddev_ioctl_string(काष्ठा hiddev *hiddev, अचिन्हित पूर्णांक cmd, व्योम __user *user_arg)
अणु
	काष्ठा hid_device *hid = hiddev->hid;
	काष्ठा usb_device *dev = hid_to_usb_dev(hid);
	पूर्णांक idx, len;
	अक्षर *buf;

	अगर (get_user(idx, (पूर्णांक __user *)user_arg))
		वापस -EFAULT;

	अगर ((buf = kदो_स्मृति(HID_STRING_SIZE, GFP_KERNEL)) == शून्य)
		वापस -ENOMEM;

	अगर ((len = usb_string(dev, idx, buf, HID_STRING_SIZE-1)) < 0) अणु
		kमुक्त(buf);
		वापस -EINVAL;
	पूर्ण

	अगर (copy_to_user(user_arg+माप(पूर्णांक), buf, len+1)) अणु
		kमुक्त(buf);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(buf);

	वापस len;
पूर्ण

अटल दीर्घ hiddev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hiddev_list *list = file->निजी_data;
	काष्ठा hiddev *hiddev = list->hiddev;
	काष्ठा hid_device *hid;
	काष्ठा hiddev_collection_info cinfo;
	काष्ठा hiddev_report_info rinfo;
	काष्ठा hiddev_field_info finfo;
	काष्ठा hiddev_devinfo dinfo;
	काष्ठा hid_report *report;
	काष्ठा hid_field *field;
	व्योम __user *user_arg = (व्योम __user *)arg;
	पूर्णांक i, r = -EINVAL;

	/* Called without BKL by compat methods so no BKL taken */

	mutex_lock(&hiddev->existancelock);
	अगर (!hiddev->exist) अणु
		r = -ENODEV;
		जाओ ret_unlock;
	पूर्ण

	hid = hiddev->hid;

	चयन (cmd) अणु

	हाल HIDIOCGVERSION:
		r = put_user(HID_VERSION, (पूर्णांक __user *)arg) ?
			-EFAULT : 0;
		अवरोध;

	हाल HIDIOCAPPLICATION:
		अगर (arg >= hid->maxapplication)
			अवरोध;

		क्रम (i = 0; i < hid->maxcollection; i++)
			अगर (hid->collection[i].type ==
			    HID_COLLECTION_APPLICATION && arg-- == 0)
				अवरोध;

		अगर (i < hid->maxcollection)
			r = hid->collection[i].usage;
		अवरोध;

	हाल HIDIOCGDEVINFO:
		अणु
			काष्ठा usb_device *dev = hid_to_usb_dev(hid);
			काष्ठा usbhid_device *usbhid = hid->driver_data;

			स_रखो(&dinfo, 0, माप(dinfo));

			dinfo.bustype = BUS_USB;
			dinfo.busnum = dev->bus->busnum;
			dinfo.devnum = dev->devnum;
			dinfo.अगरnum = usbhid->अगरnum;
			dinfo.venकरोr = le16_to_cpu(dev->descriptor.idVenकरोr);
			dinfo.product = le16_to_cpu(dev->descriptor.idProduct);
			dinfo.version = le16_to_cpu(dev->descriptor.bcdDevice);
			dinfo.num_applications = hid->maxapplication;

			r = copy_to_user(user_arg, &dinfo, माप(dinfo)) ?
				-EFAULT : 0;
			अवरोध;
		पूर्ण

	हाल HIDIOCGFLAG:
		r = put_user(list->flags, (पूर्णांक __user *)arg) ?
			-EFAULT : 0;
		अवरोध;

	हाल HIDIOCSFLAG:
		अणु
			पूर्णांक newflags;

			अगर (get_user(newflags, (पूर्णांक __user *)arg)) अणु
				r = -EFAULT;
				अवरोध;
			पूर्ण

			अगर ((newflags & ~HIDDEV_FLAGS) != 0 ||
			    ((newflags & HIDDEV_FLAG_REPORT) != 0 &&
			     (newflags & HIDDEV_FLAG_UREF) == 0))
				अवरोध;

			list->flags = newflags;

			r = 0;
			अवरोध;
		पूर्ण

	हाल HIDIOCGSTRING:
		r = hiddev_ioctl_string(hiddev, cmd, user_arg);
		अवरोध;

	हाल HIDIOCINITREPORT:
		usbhid_init_reports(hid);
		hiddev->initialized = true;
		r = 0;
		अवरोध;

	हाल HIDIOCGREPORT:
		अगर (copy_from_user(&rinfo, user_arg, माप(rinfo))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (rinfo.report_type == HID_REPORT_TYPE_OUTPUT)
			अवरोध;

		report = hiddev_lookup_report(hid, &rinfo);
		अगर (report == शून्य)
			अवरोध;

		hid_hw_request(hid, report, HID_REQ_GET_REPORT);
		hid_hw_रुको(hid);

		r = 0;
		अवरोध;

	हाल HIDIOCSREPORT:
		अगर (copy_from_user(&rinfo, user_arg, माप(rinfo))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (rinfo.report_type == HID_REPORT_TYPE_INPUT)
			अवरोध;

		report = hiddev_lookup_report(hid, &rinfo);
		अगर (report == शून्य)
			अवरोध;

		hid_hw_request(hid, report, HID_REQ_SET_REPORT);
		hid_hw_रुको(hid);

		r = 0;
		अवरोध;

	हाल HIDIOCGREPORTINFO:
		अगर (copy_from_user(&rinfo, user_arg, माप(rinfo))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		report = hiddev_lookup_report(hid, &rinfo);
		अगर (report == शून्य)
			अवरोध;

		rinfo.num_fields = report->maxfield;

		r = copy_to_user(user_arg, &rinfo, माप(rinfo)) ?
			-EFAULT : 0;
		अवरोध;

	हाल HIDIOCGFIELDINFO:
		अगर (copy_from_user(&finfo, user_arg, माप(finfo))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		rinfo.report_type = finfo.report_type;
		rinfo.report_id = finfo.report_id;

		report = hiddev_lookup_report(hid, &rinfo);
		अगर (report == शून्य)
			अवरोध;

		अगर (finfo.field_index >= report->maxfield)
			अवरोध;
		finfo.field_index = array_index_nospec(finfo.field_index,
						       report->maxfield);

		field = report->field[finfo.field_index];
		स_रखो(&finfo, 0, माप(finfo));
		finfo.report_type = rinfo.report_type;
		finfo.report_id = rinfo.report_id;
		finfo.field_index = field->report_count - 1;
		finfo.maxusage = field->maxusage;
		finfo.flags = field->flags;
		finfo.physical = field->physical;
		finfo.logical = field->logical;
		finfo.application = field->application;
		finfo.logical_minimum = field->logical_minimum;
		finfo.logical_maximum = field->logical_maximum;
		finfo.physical_minimum = field->physical_minimum;
		finfo.physical_maximum = field->physical_maximum;
		finfo.unit_exponent = field->unit_exponent;
		finfo.unit = field->unit;

		r = copy_to_user(user_arg, &finfo, माप(finfo)) ?
			-EFAULT : 0;
		अवरोध;

	हाल HIDIOCGUCODE:
	हाल HIDIOCGUSAGE:
	हाल HIDIOCSUSAGE:
	हाल HIDIOCGUSAGES:
	हाल HIDIOCSUSAGES:
	हाल HIDIOCGCOLLECTIONINDEX:
		अगर (!hiddev->initialized) अणु
			usbhid_init_reports(hid);
			hiddev->initialized = true;
		पूर्ण
		r = hiddev_ioctl_usage(hiddev, cmd, user_arg);
		अवरोध;

	हाल HIDIOCGCOLLECTIONINFO:
		अगर (copy_from_user(&cinfo, user_arg, माप(cinfo))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (cinfo.index >= hid->maxcollection)
			अवरोध;
		cinfo.index = array_index_nospec(cinfo.index,
						 hid->maxcollection);

		cinfo.type = hid->collection[cinfo.index].type;
		cinfo.usage = hid->collection[cinfo.index].usage;
		cinfo.level = hid->collection[cinfo.index].level;

		r = copy_to_user(user_arg, &cinfo, माप(cinfo)) ?
			-EFAULT : 0;
		अवरोध;

	शेष:
		अगर (_IOC_TYPE(cmd) != 'H' || _IOC_सूची(cmd) != _IOC_READ)
			अवरोध;

		अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCGNAME(0))) अणु
			पूर्णांक len = म_माप(hid->name) + 1;
			अगर (len > _IOC_SIZE(cmd))
				 len = _IOC_SIZE(cmd);
			r = copy_to_user(user_arg, hid->name, len) ?
				-EFAULT : len;
			अवरोध;
		पूर्ण

		अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCGPHYS(0))) अणु
			पूर्णांक len = म_माप(hid->phys) + 1;
			अगर (len > _IOC_SIZE(cmd))
				len = _IOC_SIZE(cmd);
			r = copy_to_user(user_arg, hid->phys, len) ?
				-EFAULT : len;
			अवरोध;
		पूर्ण
	पूर्ण

ret_unlock:
	mutex_unlock(&hiddev->existancelock);
	वापस r;
पूर्ण

अटल स्थिर काष्ठा file_operations hiddev_fops = अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		hiddev_पढ़ो,
	.ग_लिखो =	hiddev_ग_लिखो,
	.poll =		hiddev_poll,
	.खोलो =		hiddev_खोलो,
	.release =	hiddev_release,
	.unlocked_ioctl =	hiddev_ioctl,
	.fasync =	hiddev_fasync,
	.compat_ioctl	= compat_ptr_ioctl,
	.llseek		= noop_llseek,
पूर्ण;

अटल अक्षर *hiddev_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "usb/%s", dev_name(dev));
पूर्ण

अटल काष्ठा usb_class_driver hiddev_class = अणु
	.name =		"hiddev%d",
	.devnode =	hiddev_devnode,
	.fops =		&hiddev_fops,
	.minor_base =	HIDDEV_MINOR_BASE,
पूर्ण;

/*
 * This is where hid.c calls us to connect a hid device to the hiddev driver
 */
पूर्णांक hiddev_connect(काष्ठा hid_device *hid, अचिन्हित पूर्णांक क्रमce)
अणु
	काष्ठा hiddev *hiddev;
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	पूर्णांक retval;

	अगर (!क्रमce) अणु
		अचिन्हित पूर्णांक i;
		क्रम (i = 0; i < hid->maxcollection; i++)
			अगर (hid->collection[i].type ==
			    HID_COLLECTION_APPLICATION &&
			    !IS_INPUT_APPLICATION(hid->collection[i].usage))
				अवरोध;

		अगर (i == hid->maxcollection)
			वापस -EINVAL;
	पूर्ण

	अगर (!(hiddev = kzalloc(माप(काष्ठा hiddev), GFP_KERNEL)))
		वापस -ENOMEM;

	init_रुकोqueue_head(&hiddev->रुको);
	INIT_LIST_HEAD(&hiddev->list);
	spin_lock_init(&hiddev->list_lock);
	mutex_init(&hiddev->existancelock);
	hid->hiddev = hiddev;
	hiddev->hid = hid;
	hiddev->exist = 1;
	retval = usb_रेजिस्टर_dev(usbhid->पूर्णांकf, &hiddev_class);
	अगर (retval) अणु
		hid_err(hid, "Not able to get a minor for this device\n");
		hid->hiddev = शून्य;
		kमुक्त(hiddev);
		वापस retval;
	पूर्ण

	/*
	 * If HID_QUIRK_NO_INIT_REPORTS is set, make sure we करोn't initialize
	 * the reports.
	 */
	hiddev->initialized = hid->quirks & HID_QUIRK_NO_INIT_REPORTS;

	hiddev->minor = usbhid->पूर्णांकf->minor;

	वापस 0;
पूर्ण

/*
 * This is where hid.c calls us to disconnect a hiddev device from the
 * corresponding hid device (usually because the usb device has disconnected)
 */
अटल काष्ठा usb_class_driver hiddev_class;
व्योम hiddev_disconnect(काष्ठा hid_device *hid)
अणु
	काष्ठा hiddev *hiddev = hid->hiddev;
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	usb_deरेजिस्टर_dev(usbhid->पूर्णांकf, &hiddev_class);

	mutex_lock(&hiddev->existancelock);
	hiddev->exist = 0;

	अगर (hiddev->खोलो) अणु
		hid_hw_बंद(hiddev->hid);
		wake_up_पूर्णांकerruptible(&hiddev->रुको);
		mutex_unlock(&hiddev->existancelock);
	पूर्ण अन्यथा अणु
		mutex_unlock(&hiddev->existancelock);
		kमुक्त(hiddev);
	पूर्ण
पूर्ण
