<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  User level driver support क्रम input subप्रणाली
 *
 * Heavily based on evdev.c by Vojtech Pavlik
 *
 * Author: Aristeu Sergio Rozanski Filho <aris@cathedralद_असल.org>
 *
 * Changes/Revisions:
 *	0.4	01/09/2014 (Benjamin Tissoires <benjamin.tissoires@redhat.com>)
 *		- add UI_GET_SYSNAME ioctl
 *	0.3	09/04/2006 (Anssi Hannula <anssi.hannula@gmail.com>)
 *		- updated ff support क्रम the changes in kernel पूर्णांकerface
 *		- added MODULE_VERSION
 *	0.2	16/10/2004 (Micah Dowty <micah@navi.cx>)
 *		- added क्रमce feedback support
 *              - added UI_SET_PHYS
 *	0.1	20/06/2002
 *		- first खुला version
 */
#समावेश <uapi/linux/uinput.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/overflow.h>
#समावेश <linux/input/mt.h>
#समावेश "../input-compat.h"

#घोषणा UINPUT_NAME		"uinput"
#घोषणा UINPUT_BUFFER_SIZE	16
#घोषणा UINPUT_NUM_REQUESTS	16

क्रमागत uinput_state अणु UIST_NEW_DEVICE, UIST_SETUP_COMPLETE, UIST_CREATED पूर्ण;

काष्ठा uinput_request अणु
	अचिन्हित पूर्णांक		id;
	अचिन्हित पूर्णांक		code;	/* UI_FF_UPLOAD, UI_FF_ERASE */

	पूर्णांक			retval;
	काष्ठा completion	करोne;

	जोड़ अणु
		अचिन्हित पूर्णांक	effect_id;
		काष्ठा अणु
			काष्ठा ff_effect *effect;
			काष्ठा ff_effect *old;
		पूर्ण upload;
	पूर्ण u;
पूर्ण;

काष्ठा uinput_device अणु
	काष्ठा input_dev	*dev;
	काष्ठा mutex		mutex;
	क्रमागत uinput_state	state;
	रुको_queue_head_t	रुकोq;
	अचिन्हित अक्षर		पढ़ोy;
	अचिन्हित अक्षर		head;
	अचिन्हित अक्षर		tail;
	काष्ठा input_event	buff[UINPUT_BUFFER_SIZE];
	अचिन्हित पूर्णांक		ff_effects_max;

	काष्ठा uinput_request	*requests[UINPUT_NUM_REQUESTS];
	रुको_queue_head_t	requests_रुकोq;
	spinlock_t		requests_lock;
पूर्ण;

अटल पूर्णांक uinput_dev_event(काष्ठा input_dev *dev,
			    अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा uinput_device	*udev = input_get_drvdata(dev);
	काष्ठा बारpec64	ts;

	kसमय_get_ts64(&ts);

	udev->buff[udev->head] = (काष्ठा input_event) अणु
		.input_event_sec = ts.tv_sec,
		.input_event_usec = ts.tv_nsec / NSEC_PER_USEC,
		.type = type,
		.code = code,
		.value = value,
	पूर्ण;

	udev->head = (udev->head + 1) % UINPUT_BUFFER_SIZE;

	wake_up_पूर्णांकerruptible(&udev->रुकोq);

	वापस 0;
पूर्ण

/* Atomically allocate an ID क्रम the given request. Returns 0 on success. */
अटल bool uinput_request_alloc_id(काष्ठा uinput_device *udev,
				    काष्ठा uinput_request *request)
अणु
	अचिन्हित पूर्णांक id;
	bool reserved = false;

	spin_lock(&udev->requests_lock);

	क्रम (id = 0; id < UINPUT_NUM_REQUESTS; id++) अणु
		अगर (!udev->requests[id]) अणु
			request->id = id;
			udev->requests[id] = request;
			reserved = true;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&udev->requests_lock);
	वापस reserved;
पूर्ण

अटल काष्ठा uinput_request *uinput_request_find(काष्ठा uinput_device *udev,
						  अचिन्हित पूर्णांक id)
अणु
	/* Find an input request, by ID. Returns शून्य अगर the ID isn't valid. */
	अगर (id >= UINPUT_NUM_REQUESTS)
		वापस शून्य;

	वापस udev->requests[id];
पूर्ण

अटल पूर्णांक uinput_request_reserve_slot(काष्ठा uinput_device *udev,
				       काष्ठा uinput_request *request)
अणु
	/* Allocate slot. If none are available right away, रुको. */
	वापस रुको_event_पूर्णांकerruptible(udev->requests_रुकोq,
					uinput_request_alloc_id(udev, request));
पूर्ण

अटल व्योम uinput_request_release_slot(काष्ठा uinput_device *udev,
					अचिन्हित पूर्णांक id)
अणु
	/* Mark slot as available */
	spin_lock(&udev->requests_lock);
	udev->requests[id] = शून्य;
	spin_unlock(&udev->requests_lock);

	wake_up(&udev->requests_रुकोq);
पूर्ण

अटल पूर्णांक uinput_request_send(काष्ठा uinput_device *udev,
			       काष्ठा uinput_request *request)
अणु
	पूर्णांक retval;

	retval = mutex_lock_पूर्णांकerruptible(&udev->mutex);
	अगर (retval)
		वापस retval;

	अगर (udev->state != UIST_CREATED) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	init_completion(&request->करोne);

	/*
	 * Tell our userspace application about this new request
	 * by queueing an input event.
	 */
	uinput_dev_event(udev->dev, EV_UINPUT, request->code, request->id);

 out:
	mutex_unlock(&udev->mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक uinput_request_submit(काष्ठा uinput_device *udev,
				 काष्ठा uinput_request *request)
अणु
	पूर्णांक retval;

	retval = uinput_request_reserve_slot(udev, request);
	अगर (retval)
		वापस retval;

	retval = uinput_request_send(udev, request);
	अगर (retval)
		जाओ out;

	अगर (!रुको_क्रम_completion_समयout(&request->करोne, 30 * HZ)) अणु
		retval = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	retval = request->retval;

 out:
	uinput_request_release_slot(udev, request->id);
	वापस retval;
पूर्ण

/*
 * Fail all outstanding requests so handlers करोn't रुको क्रम the userspace
 * to finish processing them.
 */
अटल व्योम uinput_flush_requests(काष्ठा uinput_device *udev)
अणु
	काष्ठा uinput_request *request;
	पूर्णांक i;

	spin_lock(&udev->requests_lock);

	क्रम (i = 0; i < UINPUT_NUM_REQUESTS; i++) अणु
		request = udev->requests[i];
		अगर (request) अणु
			request->retval = -ENODEV;
			complete(&request->करोne);
		पूर्ण
	पूर्ण

	spin_unlock(&udev->requests_lock);
पूर्ण

अटल व्योम uinput_dev_set_gain(काष्ठा input_dev *dev, u16 gain)
अणु
	uinput_dev_event(dev, EV_FF, FF_GAIN, gain);
पूर्ण

अटल व्योम uinput_dev_set_स्वतःcenter(काष्ठा input_dev *dev, u16 magnitude)
अणु
	uinput_dev_event(dev, EV_FF, FF_AUTOCENTER, magnitude);
पूर्ण

अटल पूर्णांक uinput_dev_playback(काष्ठा input_dev *dev, पूर्णांक effect_id, पूर्णांक value)
अणु
	वापस uinput_dev_event(dev, EV_FF, effect_id, value);
पूर्ण

अटल पूर्णांक uinput_dev_upload_effect(काष्ठा input_dev *dev,
				    काष्ठा ff_effect *effect,
				    काष्ठा ff_effect *old)
अणु
	काष्ठा uinput_device *udev = input_get_drvdata(dev);
	काष्ठा uinput_request request;

	/*
	 * uinput driver करोes not currently support periodic effects with
	 * custom waveक्रमm since it करोes not have a way to pass buffer of
	 * samples (custom_data) to userspace. If ever there is a device
	 * supporting custom waveक्रमms we would need to define an additional
	 * ioctl (UI_UPLOAD_SAMPLES) but क्रम now we just bail out.
	 */
	अगर (effect->type == FF_PERIODIC &&
			effect->u.periodic.waveक्रमm == FF_CUSTOM)
		वापस -EINVAL;

	request.code = UI_FF_UPLOAD;
	request.u.upload.effect = effect;
	request.u.upload.old = old;

	वापस uinput_request_submit(udev, &request);
पूर्ण

अटल पूर्णांक uinput_dev_erase_effect(काष्ठा input_dev *dev, पूर्णांक effect_id)
अणु
	काष्ठा uinput_device *udev = input_get_drvdata(dev);
	काष्ठा uinput_request request;

	अगर (!test_bit(EV_FF, dev->evbit))
		वापस -ENOSYS;

	request.code = UI_FF_ERASE;
	request.u.effect_id = effect_id;

	वापस uinput_request_submit(udev, &request);
पूर्ण

अटल पूर्णांक uinput_dev_flush(काष्ठा input_dev *dev, काष्ठा file *file)
अणु
	/*
	 * If we are called with file == शून्य that means we are tearing
	 * करोwn the device, and thereक्रमe we can not handle FF erase
	 * requests: either we are handling UI_DEV_DESTROY (and holding
	 * the udev->mutex), or the file descriptor is बंदd and there is
	 * nobody on the other side anymore.
	 */
	वापस file ? input_ff_flush(dev, file) : 0;
पूर्ण

अटल व्योम uinput_destroy_device(काष्ठा uinput_device *udev)
अणु
	स्थिर अक्षर *name, *phys;
	काष्ठा input_dev *dev = udev->dev;
	क्रमागत uinput_state old_state = udev->state;

	udev->state = UIST_NEW_DEVICE;

	अगर (dev) अणु
		name = dev->name;
		phys = dev->phys;
		अगर (old_state == UIST_CREATED) अणु
			uinput_flush_requests(udev);
			input_unरेजिस्टर_device(dev);
		पूर्ण अन्यथा अणु
			input_मुक्त_device(dev);
		पूर्ण
		kमुक्त(name);
		kमुक्त(phys);
		udev->dev = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक uinput_create_device(काष्ठा uinput_device *udev)
अणु
	काष्ठा input_dev *dev = udev->dev;
	पूर्णांक error, nslot;

	अगर (udev->state != UIST_SETUP_COMPLETE) अणु
		prपूर्णांकk(KERN_DEBUG "%s: write device info first\n", UINPUT_NAME);
		वापस -EINVAL;
	पूर्ण

	अगर (test_bit(EV_ABS, dev->evbit)) अणु
		input_alloc_असलinfo(dev);
		अगर (!dev->असलinfo) अणु
			error = -EINVAL;
			जाओ fail1;
		पूर्ण

		अगर (test_bit(ABS_MT_SLOT, dev->असलbit)) अणु
			nslot = input_असल_get_max(dev, ABS_MT_SLOT) + 1;
			error = input_mt_init_slots(dev, nslot, 0);
			अगर (error)
				जाओ fail1;
		पूर्ण अन्यथा अगर (test_bit(ABS_MT_POSITION_X, dev->असलbit)) अणु
			input_set_events_per_packet(dev, 60);
		पूर्ण
	पूर्ण

	अगर (test_bit(EV_FF, dev->evbit) && !udev->ff_effects_max) अणु
		prपूर्णांकk(KERN_DEBUG "%s: ff_effects_max should be non-zero when FF_BIT is set\n",
			UINPUT_NAME);
		error = -EINVAL;
		जाओ fail1;
	पूर्ण

	अगर (udev->ff_effects_max) अणु
		error = input_ff_create(dev, udev->ff_effects_max);
		अगर (error)
			जाओ fail1;

		dev->ff->upload = uinput_dev_upload_effect;
		dev->ff->erase = uinput_dev_erase_effect;
		dev->ff->playback = uinput_dev_playback;
		dev->ff->set_gain = uinput_dev_set_gain;
		dev->ff->set_स्वतःcenter = uinput_dev_set_स्वतःcenter;
		/*
		 * The standard input_ff_flush() implementation करोes
		 * not quite work क्रम uinput as we can't reasonably
		 * handle FF requests during device tearकरोwn.
		 */
		dev->flush = uinput_dev_flush;
	पूर्ण

	dev->event = uinput_dev_event;

	input_set_drvdata(udev->dev, udev);

	error = input_रेजिस्टर_device(udev->dev);
	अगर (error)
		जाओ fail2;

	udev->state = UIST_CREATED;

	वापस 0;

 fail2:	input_ff_destroy(dev);
 fail1: uinput_destroy_device(udev);
	वापस error;
पूर्ण

अटल पूर्णांक uinput_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा uinput_device *newdev;

	newdev = kzalloc(माप(काष्ठा uinput_device), GFP_KERNEL);
	अगर (!newdev)
		वापस -ENOMEM;

	mutex_init(&newdev->mutex);
	spin_lock_init(&newdev->requests_lock);
	init_रुकोqueue_head(&newdev->requests_रुकोq);
	init_रुकोqueue_head(&newdev->रुकोq);
	newdev->state = UIST_NEW_DEVICE;

	file->निजी_data = newdev;
	stream_खोलो(inode, file);

	वापस 0;
पूर्ण

अटल पूर्णांक uinput_validate_असलinfo(काष्ठा input_dev *dev, अचिन्हित पूर्णांक code,
				   स्थिर काष्ठा input_असलinfo *असल)
अणु
	पूर्णांक min, max, range;

	min = असल->minimum;
	max = असल->maximum;

	अगर ((min != 0 || max != 0) && max < min) अणु
		prपूर्णांकk(KERN_DEBUG
		       "%s: invalid abs[%02x] min:%d max:%d\n",
		       UINPUT_NAME, code, min, max);
		वापस -EINVAL;
	पूर्ण

	अगर (!check_sub_overflow(max, min, &range) && असल->flat > range) अणु
		prपूर्णांकk(KERN_DEBUG
		       "%s: abs_flat #%02x out of range: %d (min:%d/max:%d)\n",
		       UINPUT_NAME, code, असल->flat, min, max);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uinput_validate_असलbits(काष्ठा input_dev *dev)
अणु
	अचिन्हित पूर्णांक cnt;
	पूर्णांक error;

	अगर (!test_bit(EV_ABS, dev->evbit))
		वापस 0;

	/*
	 * Check अगर असलmin/असलmax/असलfuzz/असलflat are sane.
	 */

	क्रम_each_set_bit(cnt, dev->असलbit, ABS_CNT) अणु
		अगर (!dev->असलinfo)
			वापस -EINVAL;

		error = uinput_validate_असलinfo(dev, cnt, &dev->असलinfo[cnt]);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uinput_dev_setup(काष्ठा uinput_device *udev,
			    काष्ठा uinput_setup __user *arg)
अणु
	काष्ठा uinput_setup setup;
	काष्ठा input_dev *dev;

	अगर (udev->state == UIST_CREATED)
		वापस -EINVAL;

	अगर (copy_from_user(&setup, arg, माप(setup)))
		वापस -EFAULT;

	अगर (!setup.name[0])
		वापस -EINVAL;

	dev = udev->dev;
	dev->id = setup.id;
	udev->ff_effects_max = setup.ff_effects_max;

	kमुक्त(dev->name);
	dev->name = kstrndup(setup.name, UINPUT_MAX_NAME_SIZE, GFP_KERNEL);
	अगर (!dev->name)
		वापस -ENOMEM;

	udev->state = UIST_SETUP_COMPLETE;
	वापस 0;
पूर्ण

अटल पूर्णांक uinput_असल_setup(काष्ठा uinput_device *udev,
			    काष्ठा uinput_setup __user *arg, माप_प्रकार size)
अणु
	काष्ठा uinput_असल_setup setup = अणुपूर्ण;
	काष्ठा input_dev *dev;
	पूर्णांक error;

	अगर (size > माप(setup))
		वापस -E2BIG;

	अगर (udev->state == UIST_CREATED)
		वापस -EINVAL;

	अगर (copy_from_user(&setup, arg, size))
		वापस -EFAULT;

	अगर (setup.code > ABS_MAX)
		वापस -दुस्फल;

	dev = udev->dev;

	error = uinput_validate_असलinfo(dev, setup.code, &setup.असलinfo);
	अगर (error)
		वापस error;

	input_alloc_असलinfo(dev);
	अगर (!dev->असलinfo)
		वापस -ENOMEM;

	set_bit(setup.code, dev->असलbit);
	dev->असलinfo[setup.code] = setup.असलinfo;
	वापस 0;
पूर्ण

/* legacy setup via ग_लिखो() */
अटल पूर्णांक uinput_setup_device_legacy(काष्ठा uinput_device *udev,
				      स्थिर अक्षर __user *buffer, माप_प्रकार count)
अणु
	काष्ठा uinput_user_dev	*user_dev;
	काष्ठा input_dev	*dev;
	पूर्णांक			i;
	पूर्णांक			retval;

	अगर (count != माप(काष्ठा uinput_user_dev))
		वापस -EINVAL;

	अगर (!udev->dev) अणु
		udev->dev = input_allocate_device();
		अगर (!udev->dev)
			वापस -ENOMEM;
	पूर्ण

	dev = udev->dev;

	user_dev = memdup_user(buffer, माप(काष्ठा uinput_user_dev));
	अगर (IS_ERR(user_dev))
		वापस PTR_ERR(user_dev);

	udev->ff_effects_max = user_dev->ff_effects_max;

	/* Ensure name is filled in */
	अगर (!user_dev->name[0]) अणु
		retval = -EINVAL;
		जाओ निकास;
	पूर्ण

	kमुक्त(dev->name);
	dev->name = kstrndup(user_dev->name, UINPUT_MAX_NAME_SIZE,
			     GFP_KERNEL);
	अगर (!dev->name) अणु
		retval = -ENOMEM;
		जाओ निकास;
	पूर्ण

	dev->id.bustype	= user_dev->id.bustype;
	dev->id.venकरोr	= user_dev->id.venकरोr;
	dev->id.product	= user_dev->id.product;
	dev->id.version	= user_dev->id.version;

	क्रम (i = 0; i < ABS_CNT; i++) अणु
		input_असल_set_max(dev, i, user_dev->असलmax[i]);
		input_असल_set_min(dev, i, user_dev->असलmin[i]);
		input_असल_set_fuzz(dev, i, user_dev->असलfuzz[i]);
		input_असल_set_flat(dev, i, user_dev->असलflat[i]);
	पूर्ण

	retval = uinput_validate_असलbits(dev);
	अगर (retval < 0)
		जाओ निकास;

	udev->state = UIST_SETUP_COMPLETE;
	retval = count;

 निकास:
	kमुक्त(user_dev);
	वापस retval;
पूर्ण

अटल sमाप_प्रकार uinput_inject_events(काष्ठा uinput_device *udev,
				    स्थिर अक्षर __user *buffer, माप_प्रकार count)
अणु
	काष्ठा input_event ev;
	माप_प्रकार bytes = 0;

	अगर (count != 0 && count < input_event_size())
		वापस -EINVAL;

	जबतक (bytes + input_event_size() <= count) अणु
		/*
		 * Note that even अगर some events were fetched successfully
		 * we are still going to वापस EFAULT instead of partial
		 * count to let userspace know that it got it's buffers
		 * all wrong.
		 */
		अगर (input_event_from_user(buffer + bytes, &ev))
			वापस -EFAULT;

		input_event(udev->dev, ev.type, ev.code, ev.value);
		bytes += input_event_size();
		cond_resched();
	पूर्ण

	वापस bytes;
पूर्ण

अटल sमाप_प्रकार uinput_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा uinput_device *udev = file->निजी_data;
	पूर्णांक retval;

	अगर (count == 0)
		वापस 0;

	retval = mutex_lock_पूर्णांकerruptible(&udev->mutex);
	अगर (retval)
		वापस retval;

	retval = udev->state == UIST_CREATED ?
			uinput_inject_events(udev, buffer, count) :
			uinput_setup_device_legacy(udev, buffer, count);

	mutex_unlock(&udev->mutex);

	वापस retval;
पूर्ण

अटल bool uinput_fetch_next_event(काष्ठा uinput_device *udev,
				    काष्ठा input_event *event)
अणु
	bool have_event;

	spin_lock_irq(&udev->dev->event_lock);

	have_event = udev->head != udev->tail;
	अगर (have_event) अणु
		*event = udev->buff[udev->tail];
		udev->tail = (udev->tail + 1) % UINPUT_BUFFER_SIZE;
	पूर्ण

	spin_unlock_irq(&udev->dev->event_lock);

	वापस have_event;
पूर्ण

अटल sमाप_प्रकार uinput_events_to_user(काष्ठा uinput_device *udev,
				     अक्षर __user *buffer, माप_प्रकार count)
अणु
	काष्ठा input_event event;
	माप_प्रकार पढ़ो = 0;

	जबतक (पढ़ो + input_event_size() <= count &&
	       uinput_fetch_next_event(udev, &event)) अणु

		अगर (input_event_to_user(buffer + पढ़ो, &event))
			वापस -EFAULT;

		पढ़ो += input_event_size();
	पूर्ण

	वापस पढ़ो;
पूर्ण

अटल sमाप_प्रकार uinput_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा uinput_device *udev = file->निजी_data;
	sमाप_प्रकार retval;

	अगर (count != 0 && count < input_event_size())
		वापस -EINVAL;

	करो अणु
		retval = mutex_lock_पूर्णांकerruptible(&udev->mutex);
		अगर (retval)
			वापस retval;

		अगर (udev->state != UIST_CREATED)
			retval = -ENODEV;
		अन्यथा अगर (udev->head == udev->tail &&
			 (file->f_flags & O_NONBLOCK))
			retval = -EAGAIN;
		अन्यथा
			retval = uinput_events_to_user(udev, buffer, count);

		mutex_unlock(&udev->mutex);

		अगर (retval || count == 0)
			अवरोध;

		अगर (!(file->f_flags & O_NONBLOCK))
			retval = रुको_event_पूर्णांकerruptible(udev->रुकोq,
						  udev->head != udev->tail ||
						  udev->state != UIST_CREATED);
	पूर्ण जबतक (retval == 0);

	वापस retval;
पूर्ण

अटल __poll_t uinput_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा uinput_device *udev = file->निजी_data;
	__poll_t mask = EPOLLOUT | EPOLLWRNORM; /* uinput is always writable */

	poll_रुको(file, &udev->रुकोq, रुको);

	अगर (udev->head != udev->tail)
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल पूर्णांक uinput_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा uinput_device *udev = file->निजी_data;

	uinput_destroy_device(udev);
	kमुक्त(udev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा uinput_ff_upload_compat अणु
	__u32			request_id;
	__s32			retval;
	काष्ठा ff_effect_compat	effect;
	काष्ठा ff_effect_compat	old;
पूर्ण;

अटल पूर्णांक uinput_ff_upload_to_user(अक्षर __user *buffer,
				    स्थिर काष्ठा uinput_ff_upload *ff_up)
अणु
	अगर (in_compat_syscall()) अणु
		काष्ठा uinput_ff_upload_compat ff_up_compat;

		ff_up_compat.request_id = ff_up->request_id;
		ff_up_compat.retval = ff_up->retval;
		/*
		 * It so happens that the poपूर्णांकer that gives us the trouble
		 * is the last field in the काष्ठाure. Since we करोn't support
		 * custom waveक्रमms in uinput anyway we can just copy the whole
		 * thing (to the compat size) and ignore the poपूर्णांकer.
		 */
		स_नकल(&ff_up_compat.effect, &ff_up->effect,
			माप(काष्ठा ff_effect_compat));
		स_नकल(&ff_up_compat.old, &ff_up->old,
			माप(काष्ठा ff_effect_compat));

		अगर (copy_to_user(buffer, &ff_up_compat,
				 माप(काष्ठा uinput_ff_upload_compat)))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(buffer, ff_up,
				 माप(काष्ठा uinput_ff_upload)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uinput_ff_upload_from_user(स्थिर अक्षर __user *buffer,
				      काष्ठा uinput_ff_upload *ff_up)
अणु
	अगर (in_compat_syscall()) अणु
		काष्ठा uinput_ff_upload_compat ff_up_compat;

		अगर (copy_from_user(&ff_up_compat, buffer,
				   माप(काष्ठा uinput_ff_upload_compat)))
			वापस -EFAULT;

		ff_up->request_id = ff_up_compat.request_id;
		ff_up->retval = ff_up_compat.retval;
		स_नकल(&ff_up->effect, &ff_up_compat.effect,
			माप(काष्ठा ff_effect_compat));
		स_नकल(&ff_up->old, &ff_up_compat.old,
			माप(काष्ठा ff_effect_compat));

	पूर्ण अन्यथा अणु
		अगर (copy_from_user(ff_up, buffer,
				   माप(काष्ठा uinput_ff_upload)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक uinput_ff_upload_to_user(अक्षर __user *buffer,
				    स्थिर काष्ठा uinput_ff_upload *ff_up)
अणु
	अगर (copy_to_user(buffer, ff_up, माप(काष्ठा uinput_ff_upload)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक uinput_ff_upload_from_user(स्थिर अक्षर __user *buffer,
				      काष्ठा uinput_ff_upload *ff_up)
अणु
	अगर (copy_from_user(ff_up, buffer, माप(काष्ठा uinput_ff_upload)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#पूर्ण_अगर

#घोषणा uinput_set_bit(_arg, _bit, _max)		\
(अणु							\
	पूर्णांक __ret = 0;					\
	अगर (udev->state == UIST_CREATED)		\
		__ret =  -EINVAL;			\
	अन्यथा अगर ((_arg) > (_max))			\
		__ret = -EINVAL;			\
	अन्यथा set_bit((_arg), udev->dev->_bit);		\
	__ret;						\
पूर्ण)

अटल पूर्णांक uinput_str_to_user(व्योम __user *dest, स्थिर अक्षर *str,
			      अचिन्हित पूर्णांक maxlen)
अणु
	अक्षर __user *p = dest;
	पूर्णांक len, ret;

	अगर (!str)
		वापस -ENOENT;

	अगर (maxlen == 0)
		वापस -EINVAL;

	len = म_माप(str) + 1;
	अगर (len > maxlen)
		len = maxlen;

	ret = copy_to_user(p, str, len);
	अगर (ret)
		वापस -EFAULT;

	/* क्रमce terminating '\0' */
	ret = put_user(0, p + len - 1);
	वापस ret ? -EFAULT : len;
पूर्ण

अटल दीर्घ uinput_ioctl_handler(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg, व्योम __user *p)
अणु
	पूर्णांक			retval;
	काष्ठा uinput_device	*udev = file->निजी_data;
	काष्ठा uinput_ff_upload ff_up;
	काष्ठा uinput_ff_erase  ff_erase;
	काष्ठा uinput_request   *req;
	अक्षर			*phys;
	स्थिर अक्षर		*name;
	अचिन्हित पूर्णांक		size;

	retval = mutex_lock_पूर्णांकerruptible(&udev->mutex);
	अगर (retval)
		वापस retval;

	अगर (!udev->dev) अणु
		udev->dev = input_allocate_device();
		अगर (!udev->dev) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (cmd) अणु
	हाल UI_GET_VERSION:
		अगर (put_user(UINPUT_VERSION, (अचिन्हित पूर्णांक __user *)p))
			retval = -EFAULT;
		जाओ out;

	हाल UI_DEV_CREATE:
		retval = uinput_create_device(udev);
		जाओ out;

	हाल UI_DEV_DESTROY:
		uinput_destroy_device(udev);
		जाओ out;

	हाल UI_DEV_SETUP:
		retval = uinput_dev_setup(udev, p);
		जाओ out;

	/* UI_ABS_SETUP is handled in the variable size ioctls */

	हाल UI_SET_EVBIT:
		retval = uinput_set_bit(arg, evbit, EV_MAX);
		जाओ out;

	हाल UI_SET_KEYBIT:
		retval = uinput_set_bit(arg, keybit, KEY_MAX);
		जाओ out;

	हाल UI_SET_RELBIT:
		retval = uinput_set_bit(arg, relbit, REL_MAX);
		जाओ out;

	हाल UI_SET_ABSBIT:
		retval = uinput_set_bit(arg, असलbit, ABS_MAX);
		जाओ out;

	हाल UI_SET_MSCBIT:
		retval = uinput_set_bit(arg, mscbit, MSC_MAX);
		जाओ out;

	हाल UI_SET_LEDBIT:
		retval = uinput_set_bit(arg, ledbit, LED_MAX);
		जाओ out;

	हाल UI_SET_SNDBIT:
		retval = uinput_set_bit(arg, sndbit, SND_MAX);
		जाओ out;

	हाल UI_SET_FFBIT:
		retval = uinput_set_bit(arg, ffbit, FF_MAX);
		जाओ out;

	हाल UI_SET_SWBIT:
		retval = uinput_set_bit(arg, swbit, SW_MAX);
		जाओ out;

	हाल UI_SET_PROPBIT:
		retval = uinput_set_bit(arg, propbit, INPUT_PROP_MAX);
		जाओ out;

	हाल UI_SET_PHYS:
		अगर (udev->state == UIST_CREATED) अणु
			retval = -EINVAL;
			जाओ out;
		पूर्ण

		phys = strndup_user(p, 1024);
		अगर (IS_ERR(phys)) अणु
			retval = PTR_ERR(phys);
			जाओ out;
		पूर्ण

		kमुक्त(udev->dev->phys);
		udev->dev->phys = phys;
		जाओ out;

	हाल UI_BEGIN_FF_UPLOAD:
		retval = uinput_ff_upload_from_user(p, &ff_up);
		अगर (retval)
			जाओ out;

		req = uinput_request_find(udev, ff_up.request_id);
		अगर (!req || req->code != UI_FF_UPLOAD ||
		    !req->u.upload.effect) अणु
			retval = -EINVAL;
			जाओ out;
		पूर्ण

		ff_up.retval = 0;
		ff_up.effect = *req->u.upload.effect;
		अगर (req->u.upload.old)
			ff_up.old = *req->u.upload.old;
		अन्यथा
			स_रखो(&ff_up.old, 0, माप(काष्ठा ff_effect));

		retval = uinput_ff_upload_to_user(p, &ff_up);
		जाओ out;

	हाल UI_BEGIN_FF_ERASE:
		अगर (copy_from_user(&ff_erase, p, माप(ff_erase))) अणु
			retval = -EFAULT;
			जाओ out;
		पूर्ण

		req = uinput_request_find(udev, ff_erase.request_id);
		अगर (!req || req->code != UI_FF_ERASE) अणु
			retval = -EINVAL;
			जाओ out;
		पूर्ण

		ff_erase.retval = 0;
		ff_erase.effect_id = req->u.effect_id;
		अगर (copy_to_user(p, &ff_erase, माप(ff_erase))) अणु
			retval = -EFAULT;
			जाओ out;
		पूर्ण

		जाओ out;

	हाल UI_END_FF_UPLOAD:
		retval = uinput_ff_upload_from_user(p, &ff_up);
		अगर (retval)
			जाओ out;

		req = uinput_request_find(udev, ff_up.request_id);
		अगर (!req || req->code != UI_FF_UPLOAD ||
		    !req->u.upload.effect) अणु
			retval = -EINVAL;
			जाओ out;
		पूर्ण

		req->retval = ff_up.retval;
		complete(&req->करोne);
		जाओ out;

	हाल UI_END_FF_ERASE:
		अगर (copy_from_user(&ff_erase, p, माप(ff_erase))) अणु
			retval = -EFAULT;
			जाओ out;
		पूर्ण

		req = uinput_request_find(udev, ff_erase.request_id);
		अगर (!req || req->code != UI_FF_ERASE) अणु
			retval = -EINVAL;
			जाओ out;
		पूर्ण

		req->retval = ff_erase.retval;
		complete(&req->करोne);
		जाओ out;
	पूर्ण

	size = _IOC_SIZE(cmd);

	/* Now check variable-length commands */
	चयन (cmd & ~IOCSIZE_MASK) अणु
	हाल UI_GET_SYSNAME(0):
		अगर (udev->state != UIST_CREATED) अणु
			retval = -ENOENT;
			जाओ out;
		पूर्ण
		name = dev_name(&udev->dev->dev);
		retval = uinput_str_to_user(p, name, size);
		जाओ out;

	हाल UI_ABS_SETUP & ~IOCSIZE_MASK:
		retval = uinput_असल_setup(udev, p, size);
		जाओ out;
	पूर्ण

	retval = -EINVAL;
 out:
	mutex_unlock(&udev->mutex);
	वापस retval;
पूर्ण

अटल दीर्घ uinput_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस uinput_ioctl_handler(file, cmd, arg, (व्योम __user *)arg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT

/*
 * These IOCTLs change their size and thus their numbers between
 * 32 and 64 bits.
 */
#घोषणा UI_SET_PHYS_COMPAT		\
	_IOW(UINPUT_IOCTL_BASE, 108, compat_uptr_t)
#घोषणा UI_BEGIN_FF_UPLOAD_COMPAT	\
	_IOWR(UINPUT_IOCTL_BASE, 200, काष्ठा uinput_ff_upload_compat)
#घोषणा UI_END_FF_UPLOAD_COMPAT		\
	_IOW(UINPUT_IOCTL_BASE, 201, काष्ठा uinput_ff_upload_compat)

अटल दीर्घ uinput_compat_ioctl(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल UI_SET_PHYS_COMPAT:
		cmd = UI_SET_PHYS;
		अवरोध;
	हाल UI_BEGIN_FF_UPLOAD_COMPAT:
		cmd = UI_BEGIN_FF_UPLOAD;
		अवरोध;
	हाल UI_END_FF_UPLOAD_COMPAT:
		cmd = UI_END_FF_UPLOAD;
		अवरोध;
	पूर्ण

	वापस uinput_ioctl_handler(file, cmd, arg, compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations uinput_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= uinput_खोलो,
	.release	= uinput_release,
	.पढ़ो		= uinput_पढ़ो,
	.ग_लिखो		= uinput_ग_लिखो,
	.poll		= uinput_poll,
	.unlocked_ioctl	= uinput_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= uinput_compat_ioctl,
#पूर्ण_अगर
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice uinput_misc = अणु
	.fops		= &uinput_fops,
	.minor		= UINPUT_MINOR,
	.name		= UINPUT_NAME,
पूर्ण;
module_misc_device(uinput_misc);

MODULE_ALIAS_MISCDEV(UINPUT_MINOR);
MODULE_ALIAS("devname:" UINPUT_NAME);

MODULE_AUTHOR("Aristeu Sergio Rozanski Filho");
MODULE_DESCRIPTION("User level driver support for input subsystem");
MODULE_LICENSE("GPL");
