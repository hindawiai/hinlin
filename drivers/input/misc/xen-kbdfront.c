<शैली गुरु>
/*
 * Xen para-भव input device
 *
 * Copyright (C) 2005 Anthony Liguori <aliguori@us.ibm.com>
 * Copyright (C) 2006-2008 Red Hat, Inc., Markus Armbruster <armbru@redhat.com>
 *
 *  Based on linux/drivers/input/mouse/sermouse.c
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/xen.h>
#समावेश <xen/events.h>
#समावेश <xen/page.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>
#समावेश <xen/पूर्णांकerface/io/fbअगर.h>
#समावेश <xen/पूर्णांकerface/io/kbdअगर.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/platक्रमm_pci.h>

काष्ठा xenkbd_info अणु
	काष्ठा input_dev *kbd;
	काष्ठा input_dev *ptr;
	काष्ठा input_dev *mtouch;
	काष्ठा xenkbd_page *page;
	पूर्णांक gref;
	पूर्णांक irq;
	काष्ठा xenbus_device *xbdev;
	अक्षर phys[32];
	/* current MT slot/contact ID we are injecting events in */
	पूर्णांक mtouch_cur_contact_id;
पूर्ण;

क्रमागत अणु KPARAM_X, KPARAM_Y, KPARAM_CNT पूर्ण;
अटल पूर्णांक ptr_size[KPARAM_CNT] = अणु XENFB_WIDTH, XENFB_HEIGHT पूर्ण;
module_param_array(ptr_size, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(ptr_size,
	"Pointing device width, height in pixels (default 800,600)");

अटल पूर्णांक xenkbd_हटाओ(काष्ठा xenbus_device *);
अटल पूर्णांक xenkbd_connect_backend(काष्ठा xenbus_device *, काष्ठा xenkbd_info *);
अटल व्योम xenkbd_disconnect_backend(काष्ठा xenkbd_info *);

/*
 * Note: अगर you need to send out events, see xenfb_करो_update() क्रम how
 * to करो that.
 */

अटल व्योम xenkbd_handle_motion_event(काष्ठा xenkbd_info *info,
				       काष्ठा xenkbd_motion *motion)
अणु
	अगर (unlikely(!info->ptr))
		वापस;

	input_report_rel(info->ptr, REL_X, motion->rel_x);
	input_report_rel(info->ptr, REL_Y, motion->rel_y);
	अगर (motion->rel_z)
		input_report_rel(info->ptr, REL_WHEEL, -motion->rel_z);
	input_sync(info->ptr);
पूर्ण

अटल व्योम xenkbd_handle_position_event(काष्ठा xenkbd_info *info,
					 काष्ठा xenkbd_position *pos)
अणु
	अगर (unlikely(!info->ptr))
		वापस;

	input_report_असल(info->ptr, ABS_X, pos->असल_x);
	input_report_असल(info->ptr, ABS_Y, pos->असल_y);
	अगर (pos->rel_z)
		input_report_rel(info->ptr, REL_WHEEL, -pos->rel_z);
	input_sync(info->ptr);
पूर्ण

अटल व्योम xenkbd_handle_key_event(काष्ठा xenkbd_info *info,
				    काष्ठा xenkbd_key *key)
अणु
	काष्ठा input_dev *dev;
	पूर्णांक value = key->pressed;

	अगर (test_bit(key->keycode, info->ptr->keybit)) अणु
		dev = info->ptr;
	पूर्ण अन्यथा अगर (test_bit(key->keycode, info->kbd->keybit)) अणु
		dev = info->kbd;
		अगर (key->pressed && test_bit(key->keycode, info->kbd->key))
			value = 2; /* Mark as स्वतःrepeat */
	पूर्ण अन्यथा अणु
		pr_warn("unhandled keycode 0x%x\n", key->keycode);
		वापस;
	पूर्ण

	अगर (unlikely(!dev))
		वापस;

	input_event(dev, EV_KEY, key->keycode, value);
	input_sync(dev);
पूर्ण

अटल व्योम xenkbd_handle_mt_event(काष्ठा xenkbd_info *info,
				   काष्ठा xenkbd_mtouch *mtouch)
अणु
	अगर (unlikely(!info->mtouch))
		वापस;

	अगर (mtouch->contact_id != info->mtouch_cur_contact_id) अणु
		info->mtouch_cur_contact_id = mtouch->contact_id;
		input_mt_slot(info->mtouch, mtouch->contact_id);
	पूर्ण

	चयन (mtouch->event_type) अणु
	हाल XENKBD_MT_EV_DOWN:
		input_mt_report_slot_state(info->mtouch, MT_TOOL_FINGER, true);
		fallthrough;

	हाल XENKBD_MT_EV_MOTION:
		input_report_असल(info->mtouch, ABS_MT_POSITION_X,
				 mtouch->u.pos.असल_x);
		input_report_असल(info->mtouch, ABS_MT_POSITION_Y,
				 mtouch->u.pos.असल_y);
		अवरोध;

	हाल XENKBD_MT_EV_SHAPE:
		input_report_असल(info->mtouch, ABS_MT_TOUCH_MAJOR,
				 mtouch->u.shape.major);
		input_report_असल(info->mtouch, ABS_MT_TOUCH_MINOR,
				 mtouch->u.shape.minor);
		अवरोध;

	हाल XENKBD_MT_EV_ORIENT:
		input_report_असल(info->mtouch, ABS_MT_ORIENTATION,
				 mtouch->u.orientation);
		अवरोध;

	हाल XENKBD_MT_EV_UP:
		input_mt_report_slot_inactive(info->mtouch);
		अवरोध;

	हाल XENKBD_MT_EV_SYN:
		input_mt_sync_frame(info->mtouch);
		input_sync(info->mtouch);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xenkbd_handle_event(काष्ठा xenkbd_info *info,
				जोड़ xenkbd_in_event *event)
अणु
	चयन (event->type) अणु
	हाल XENKBD_TYPE_MOTION:
		xenkbd_handle_motion_event(info, &event->motion);
		अवरोध;

	हाल XENKBD_TYPE_KEY:
		xenkbd_handle_key_event(info, &event->key);
		अवरोध;

	हाल XENKBD_TYPE_POS:
		xenkbd_handle_position_event(info, &event->pos);
		अवरोध;

	हाल XENKBD_TYPE_MTOUCH:
		xenkbd_handle_mt_event(info, &event->mtouch);
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t input_handler(पूर्णांक rq, व्योम *dev_id)
अणु
	काष्ठा xenkbd_info *info = dev_id;
	काष्ठा xenkbd_page *page = info->page;
	__u32 cons, prod;

	prod = page->in_prod;
	अगर (prod == page->in_cons)
		वापस IRQ_HANDLED;
	rmb();			/* ensure we see ring contents up to prod */
	क्रम (cons = page->in_cons; cons != prod; cons++)
		xenkbd_handle_event(info, &XENKBD_IN_RING_REF(page, cons));
	mb();			/* ensure we got ring contents */
	page->in_cons = cons;
	notअगरy_remote_via_irq(info->irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xenkbd_probe(काष्ठा xenbus_device *dev,
				  स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक ret, i;
	bool with_mtouch, with_kbd, with_ptr;
	काष्ठा xenkbd_info *info;
	काष्ठा input_dev *kbd, *ptr, *mtouch;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		xenbus_dev_fatal(dev, -ENOMEM, "allocating info structure");
		वापस -ENOMEM;
	पूर्ण
	dev_set_drvdata(&dev->dev, info);
	info->xbdev = dev;
	info->irq = -1;
	info->gref = -1;
	snम_लिखो(info->phys, माप(info->phys), "xenbus/%s", dev->nodename);

	info->page = (व्योम *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);
	अगर (!info->page)
		जाओ error_nomem;

	/*
	 * The below are reverse logic, e.g. अगर the feature is set, then
	 * करो not expose the corresponding भव device.
	 */
	with_kbd = !xenbus_पढ़ो_अचिन्हित(dev->otherend,
					 XENKBD_FIELD_FEAT_DSBL_KEYBRD, 0);

	with_ptr = !xenbus_पढ़ो_अचिन्हित(dev->otherend,
					 XENKBD_FIELD_FEAT_DSBL_POINTER, 0);

	/* Direct logic: अगर set, then create multi-touch device. */
	with_mtouch = xenbus_पढ़ो_अचिन्हित(dev->otherend,
					   XENKBD_FIELD_FEAT_MTOUCH, 0);
	अगर (with_mtouch) अणु
		ret = xenbus_ग_लिखो(XBT_NIL, dev->nodename,
				   XENKBD_FIELD_REQ_MTOUCH, "1");
		अगर (ret) अणु
			pr_warn("xenkbd: can't request multi-touch");
			with_mtouch = 0;
		पूर्ण
	पूर्ण

	/* keyboard */
	अगर (with_kbd) अणु
		kbd = input_allocate_device();
		अगर (!kbd)
			जाओ error_nomem;
		kbd->name = "Xen Virtual Keyboard";
		kbd->phys = info->phys;
		kbd->id.bustype = BUS_PCI;
		kbd->id.venकरोr = 0x5853;
		kbd->id.product = 0xffff;

		__set_bit(EV_KEY, kbd->evbit);
		क्रम (i = KEY_ESC; i < KEY_UNKNOWN; i++)
			__set_bit(i, kbd->keybit);
		क्रम (i = KEY_OK; i < KEY_MAX; i++)
			__set_bit(i, kbd->keybit);

		ret = input_रेजिस्टर_device(kbd);
		अगर (ret) अणु
			input_मुक्त_device(kbd);
			xenbus_dev_fatal(dev, ret,
					 "input_register_device(kbd)");
			जाओ error;
		पूर्ण
		info->kbd = kbd;
	पूर्ण

	/* poपूर्णांकing device */
	अगर (with_ptr) अणु
		अचिन्हित पूर्णांक असल;

		/* Set input असल params to match backend screen res */
		असल = xenbus_पढ़ो_अचिन्हित(dev->otherend,
					   XENKBD_FIELD_FEAT_ABS_POINTER, 0);
		ptr_size[KPARAM_X] = xenbus_पढ़ो_अचिन्हित(dev->otherend,
							  XENKBD_FIELD_WIDTH,
							  ptr_size[KPARAM_X]);
		ptr_size[KPARAM_Y] = xenbus_पढ़ो_अचिन्हित(dev->otherend,
							  XENKBD_FIELD_HEIGHT,
							  ptr_size[KPARAM_Y]);
		अगर (असल) अणु
			ret = xenbus_ग_लिखो(XBT_NIL, dev->nodename,
					   XENKBD_FIELD_REQ_ABS_POINTER, "1");
			अगर (ret) अणु
				pr_warn("xenkbd: can't request abs-pointer\n");
				असल = 0;
			पूर्ण
		पूर्ण

		ptr = input_allocate_device();
		अगर (!ptr)
			जाओ error_nomem;
		ptr->name = "Xen Virtual Pointer";
		ptr->phys = info->phys;
		ptr->id.bustype = BUS_PCI;
		ptr->id.venकरोr = 0x5853;
		ptr->id.product = 0xfffe;

		अगर (असल) अणु
			__set_bit(EV_ABS, ptr->evbit);
			input_set_असल_params(ptr, ABS_X, 0,
					     ptr_size[KPARAM_X], 0, 0);
			input_set_असल_params(ptr, ABS_Y, 0,
					     ptr_size[KPARAM_Y], 0, 0);
		पूर्ण अन्यथा अणु
			input_set_capability(ptr, EV_REL, REL_X);
			input_set_capability(ptr, EV_REL, REL_Y);
		पूर्ण
		input_set_capability(ptr, EV_REL, REL_WHEEL);

		__set_bit(EV_KEY, ptr->evbit);
		क्रम (i = BTN_LEFT; i <= BTN_TASK; i++)
			__set_bit(i, ptr->keybit);

		ret = input_रेजिस्टर_device(ptr);
		अगर (ret) अणु
			input_मुक्त_device(ptr);
			xenbus_dev_fatal(dev, ret,
					 "input_register_device(ptr)");
			जाओ error;
		पूर्ण
		info->ptr = ptr;
	पूर्ण

	/* multi-touch device */
	अगर (with_mtouch) अणु
		पूर्णांक num_cont, width, height;

		mtouch = input_allocate_device();
		अगर (!mtouch)
			जाओ error_nomem;

		num_cont = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
						XENKBD_FIELD_MT_NUM_CONTACTS,
						1);
		width = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
					     XENKBD_FIELD_MT_WIDTH,
					     XENFB_WIDTH);
		height = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
					      XENKBD_FIELD_MT_HEIGHT,
					      XENFB_HEIGHT);

		mtouch->name = "Xen Virtual Multi-touch";
		mtouch->phys = info->phys;
		mtouch->id.bustype = BUS_PCI;
		mtouch->id.venकरोr = 0x5853;
		mtouch->id.product = 0xfffd;

		input_set_असल_params(mtouch, ABS_MT_TOUCH_MAJOR,
				     0, 255, 0, 0);
		input_set_असल_params(mtouch, ABS_MT_POSITION_X,
				     0, width, 0, 0);
		input_set_असल_params(mtouch, ABS_MT_POSITION_Y,
				     0, height, 0, 0);

		ret = input_mt_init_slots(mtouch, num_cont, INPUT_MT_सूचीECT);
		अगर (ret) अणु
			input_मुक्त_device(mtouch);
			xenbus_dev_fatal(info->xbdev, ret,
					 "input_mt_init_slots");
			जाओ error;
		पूर्ण

		ret = input_रेजिस्टर_device(mtouch);
		अगर (ret) अणु
			input_मुक्त_device(mtouch);
			xenbus_dev_fatal(info->xbdev, ret,
					 "input_register_device(mtouch)");
			जाओ error;
		पूर्ण
		info->mtouch_cur_contact_id = -1;
		info->mtouch = mtouch;
	पूर्ण

	अगर (!(with_kbd || with_ptr || with_mtouch)) अणु
		ret = -ENXIO;
		जाओ error;
	पूर्ण

	ret = xenkbd_connect_backend(dev, info);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

 error_nomem:
	ret = -ENOMEM;
	xenbus_dev_fatal(dev, ret, "allocating device memory");
 error:
	xenkbd_हटाओ(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक xenkbd_resume(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xenkbd_info *info = dev_get_drvdata(&dev->dev);

	xenkbd_disconnect_backend(info);
	स_रखो(info->page, 0, PAGE_SIZE);
	वापस xenkbd_connect_backend(dev, info);
पूर्ण

अटल पूर्णांक xenkbd_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xenkbd_info *info = dev_get_drvdata(&dev->dev);

	xenkbd_disconnect_backend(info);
	अगर (info->kbd)
		input_unरेजिस्टर_device(info->kbd);
	अगर (info->ptr)
		input_unरेजिस्टर_device(info->ptr);
	अगर (info->mtouch)
		input_unरेजिस्टर_device(info->mtouch);
	मुक्त_page((अचिन्हित दीर्घ)info->page);
	kमुक्त(info);
	वापस 0;
पूर्ण

अटल पूर्णांक xenkbd_connect_backend(काष्ठा xenbus_device *dev,
				  काष्ठा xenkbd_info *info)
अणु
	पूर्णांक ret, evtchn;
	काष्ठा xenbus_transaction xbt;

	ret = gnttab_grant_क्रमeign_access(dev->otherend_id,
	                                  virt_to_gfn(info->page), 0);
	अगर (ret < 0)
		वापस ret;
	info->gref = ret;

	ret = xenbus_alloc_evtchn(dev, &evtchn);
	अगर (ret)
		जाओ error_grant;
	ret = bind_evtchn_to_irqhandler(evtchn, input_handler,
					0, dev->devicetype, info);
	अगर (ret < 0) अणु
		xenbus_dev_fatal(dev, ret, "bind_evtchn_to_irqhandler");
		जाओ error_evtchan;
	पूर्ण
	info->irq = ret;

 again:
	ret = xenbus_transaction_start(&xbt);
	अगर (ret) अणु
		xenbus_dev_fatal(dev, ret, "starting transaction");
		जाओ error_irqh;
	पूर्ण
	ret = xenbus_म_लिखो(xbt, dev->nodename, XENKBD_FIELD_RING_REF, "%lu",
			    virt_to_gfn(info->page));
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_म_लिखो(xbt, dev->nodename, XENKBD_FIELD_RING_GREF,
			    "%u", info->gref);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_म_लिखो(xbt, dev->nodename, XENKBD_FIELD_EVT_CHANNEL, "%u",
			    evtchn);
	अगर (ret)
		जाओ error_xenbus;
	ret = xenbus_transaction_end(xbt, 0);
	अगर (ret) अणु
		अगर (ret == -EAGAIN)
			जाओ again;
		xenbus_dev_fatal(dev, ret, "completing transaction");
		जाओ error_irqh;
	पूर्ण

	xenbus_चयन_state(dev, XenbusStateInitialised);
	वापस 0;

 error_xenbus:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, ret, "writing xenstore");
 error_irqh:
	unbind_from_irqhandler(info->irq, info);
	info->irq = -1;
 error_evtchan:
	xenbus_मुक्त_evtchn(dev, evtchn);
 error_grant:
	gnttab_end_क्रमeign_access(info->gref, 0, 0UL);
	info->gref = -1;
	वापस ret;
पूर्ण

अटल व्योम xenkbd_disconnect_backend(काष्ठा xenkbd_info *info)
अणु
	अगर (info->irq >= 0)
		unbind_from_irqhandler(info->irq, info);
	info->irq = -1;
	अगर (info->gref >= 0)
		gnttab_end_क्रमeign_access(info->gref, 0, 0UL);
	info->gref = -1;
पूर्ण

अटल व्योम xenkbd_backend_changed(काष्ठा xenbus_device *dev,
				   क्रमागत xenbus_state backend_state)
अणु
	चयन (backend_state) अणु
	हाल XenbusStateInitialising:
	हाल XenbusStateInitialised:
	हाल XenbusStateReconfiguring:
	हाल XenbusStateReconfigured:
	हाल XenbusStateUnknown:
		अवरोध;

	हाल XenbusStateInitWait:
		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateConnected:
		/*
		 * Work around xenbus race condition: If backend goes
		 * through InitWait to Connected fast enough, we can
		 * get Connected twice here.
		 */
		अगर (dev->state != XenbusStateConnected)
			xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosed:
		अगर (dev->state == XenbusStateClosed)
			अवरोध;
		fallthrough;	/* Missed the backend's CLOSING state */
	हाल XenbusStateClosing:
		xenbus_frontend_बंदd(dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id xenkbd_ids[] = अणु
	अणु XENKBD_DRIVER_NAME पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver xenkbd_driver = अणु
	.ids = xenkbd_ids,
	.probe = xenkbd_probe,
	.हटाओ = xenkbd_हटाओ,
	.resume = xenkbd_resume,
	.otherend_changed = xenkbd_backend_changed,
पूर्ण;

अटल पूर्णांक __init xenkbd_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	/* Nothing to करो अगर running in करोm0. */
	अगर (xen_initial_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_has_pv_devices())
		वापस -ENODEV;

	वापस xenbus_रेजिस्टर_frontend(&xenkbd_driver);
पूर्ण

अटल व्योम __निकास xenkbd_cleanup(व्योम)
अणु
	xenbus_unरेजिस्टर_driver(&xenkbd_driver);
पूर्ण

module_init(xenkbd_init);
module_निकास(xenkbd_cleanup);

MODULE_DESCRIPTION("Xen virtual keyboard/pointer device frontend");
MODULE_LICENSE("GPL");
MODULE_ALIAS("xen:" XENKBD_DRIVER_NAME);
