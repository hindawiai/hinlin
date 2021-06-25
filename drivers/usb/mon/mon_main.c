<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The USB Monitor, inspired by Dave Harding's USBMon.
 *
 * mon_मुख्य.c: Main file, module initiation and निकास, registrations, etc.
 *
 * Copyright (C) 2005 Pete Zaitcev (zaitcev@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/slab.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mutex.h>

#समावेश "usb_mon.h"


अटल व्योम mon_stop(काष्ठा mon_bus *mbus);
अटल व्योम mon_dissolve(काष्ठा mon_bus *mbus, काष्ठा usb_bus *ubus);
अटल व्योम mon_bus_drop(काष्ठा kref *r);
अटल व्योम mon_bus_init(काष्ठा usb_bus *ubus);

DEFINE_MUTEX(mon_lock);

काष्ठा mon_bus mon_bus0;		/* Pseuकरो bus meaning "all buses" */
अटल LIST_HEAD(mon_buses);		/* All buses we know: काष्ठा mon_bus */

/*
 * Link a पढ़ोer पूर्णांकo the bus.
 *
 * This must be called with mon_lock taken because of mbus->ref.
 */
व्योम mon_पढ़ोer_add(काष्ठा mon_bus *mbus, काष्ठा mon_पढ़ोer *r)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *p;

	spin_lock_irqsave(&mbus->lock, flags);
	अगर (mbus->nपढ़ोers == 0) अणु
		अगर (mbus == &mon_bus0) अणु
			list_क्रम_each (p, &mon_buses) अणु
				काष्ठा mon_bus *m1;
				m1 = list_entry(p, काष्ठा mon_bus, bus_link);
				m1->u_bus->monitored = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			mbus->u_bus->monitored = 1;
		पूर्ण
	पूर्ण
	mbus->nपढ़ोers++;
	list_add_tail(&r->r_link, &mbus->r_list);
	spin_unlock_irqrestore(&mbus->lock, flags);

	kref_get(&mbus->ref);
पूर्ण

/*
 * Unlink पढ़ोer from the bus.
 *
 * This is called with mon_lock taken, so we can decrement mbus->ref.
 */
व्योम mon_पढ़ोer_del(काष्ठा mon_bus *mbus, काष्ठा mon_पढ़ोer *r)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mbus->lock, flags);
	list_del(&r->r_link);
	--mbus->nपढ़ोers;
	अगर (mbus->nपढ़ोers == 0)
		mon_stop(mbus);
	spin_unlock_irqrestore(&mbus->lock, flags);

	kref_put(&mbus->ref, mon_bus_drop);
पूर्ण

/*
 */
अटल व्योम mon_bus_submit(काष्ठा mon_bus *mbus, काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *pos;
	काष्ठा mon_पढ़ोer *r;

	spin_lock_irqsave(&mbus->lock, flags);
	mbus->cnt_events++;
	list_क्रम_each (pos, &mbus->r_list) अणु
		r = list_entry(pos, काष्ठा mon_पढ़ोer, r_link);
		r->rnf_submit(r->r_data, urb);
	पूर्ण
	spin_unlock_irqrestore(&mbus->lock, flags);
पूर्ण

अटल व्योम mon_submit(काष्ठा usb_bus *ubus, काष्ठा urb *urb)
अणु
	काष्ठा mon_bus *mbus;

	mbus = ubus->mon_bus;
	अगर (mbus != शून्य)
		mon_bus_submit(mbus, urb);
	mon_bus_submit(&mon_bus0, urb);
पूर्ण

/*
 */
अटल व्योम mon_bus_submit_error(काष्ठा mon_bus *mbus, काष्ठा urb *urb, पूर्णांक error)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *pos;
	काष्ठा mon_पढ़ोer *r;

	spin_lock_irqsave(&mbus->lock, flags);
	mbus->cnt_events++;
	list_क्रम_each (pos, &mbus->r_list) अणु
		r = list_entry(pos, काष्ठा mon_पढ़ोer, r_link);
		r->rnf_error(r->r_data, urb, error);
	पूर्ण
	spin_unlock_irqrestore(&mbus->lock, flags);
पूर्ण

अटल व्योम mon_submit_error(काष्ठा usb_bus *ubus, काष्ठा urb *urb, पूर्णांक error)
अणु
	काष्ठा mon_bus *mbus;

	mbus = ubus->mon_bus;
	अगर (mbus != शून्य)
		mon_bus_submit_error(mbus, urb, error);
	mon_bus_submit_error(&mon_bus0, urb, error);
पूर्ण

/*
 */
अटल व्योम mon_bus_complete(काष्ठा mon_bus *mbus, काष्ठा urb *urb, पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *pos;
	काष्ठा mon_पढ़ोer *r;

	spin_lock_irqsave(&mbus->lock, flags);
	mbus->cnt_events++;
	list_क्रम_each (pos, &mbus->r_list) अणु
		r = list_entry(pos, काष्ठा mon_पढ़ोer, r_link);
		r->rnf_complete(r->r_data, urb, status);
	पूर्ण
	spin_unlock_irqrestore(&mbus->lock, flags);
पूर्ण

अटल व्योम mon_complete(काष्ठा usb_bus *ubus, काष्ठा urb *urb, पूर्णांक status)
अणु
	काष्ठा mon_bus *mbus;

	mbus = ubus->mon_bus;
	अगर (mbus != शून्य)
		mon_bus_complete(mbus, urb, status);
	mon_bus_complete(&mon_bus0, urb, status);
पूर्ण

/* पूर्णांक (*unlink_urb) (काष्ठा urb *urb, पूर्णांक status); */

/*
 * Stop monitoring.
 */
अटल व्योम mon_stop(काष्ठा mon_bus *mbus)
अणु
	काष्ठा usb_bus *ubus;
	काष्ठा list_head *p;

	अगर (mbus == &mon_bus0) अणु
		list_क्रम_each (p, &mon_buses) अणु
			mbus = list_entry(p, काष्ठा mon_bus, bus_link);
			/*
			 * We करो not change nपढ़ोers here, so rely on mon_lock.
			 */
			अगर (mbus->nपढ़ोers == 0 && (ubus = mbus->u_bus) != शून्य)
				ubus->monitored = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * A stop can be called क्रम a dissolved mon_bus in हाल of
		 * a पढ़ोer staying across an rmmod foo_hcd, so test ->u_bus.
		 */
		अगर (mon_bus0.nपढ़ोers == 0 && (ubus = mbus->u_bus) != शून्य) अणु
			ubus->monitored = 0;
			mb();
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Add a USB bus (usually by a modprobe foo-hcd)
 *
 * This करोes not वापस an error code because the core cannot care less
 * अगर monitoring is not established.
 */
अटल व्योम mon_bus_add(काष्ठा usb_bus *ubus)
अणु
	mon_bus_init(ubus);
	mutex_lock(&mon_lock);
	अगर (mon_bus0.nपढ़ोers != 0)
		ubus->monitored = 1;
	mutex_unlock(&mon_lock);
पूर्ण

/*
 * Remove a USB bus (either from rmmod foo-hcd or from a hot-हटाओ event).
 */
अटल व्योम mon_bus_हटाओ(काष्ठा usb_bus *ubus)
अणु
	काष्ठा mon_bus *mbus = ubus->mon_bus;

	mutex_lock(&mon_lock);
	list_del(&mbus->bus_link);
	अगर (mbus->text_inited)
		mon_text_del(mbus);
	अगर (mbus->bin_inited)
		mon_bin_del(mbus);

	mon_dissolve(mbus, ubus);
	kref_put(&mbus->ref, mon_bus_drop);
	mutex_unlock(&mon_lock);
पूर्ण

अटल पूर्णांक mon_notअगरy(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ action,
		      व्योम *dev)
अणु
	चयन (action) अणु
	हाल USB_BUS_ADD:
		mon_bus_add(dev);
		अवरोध;
	हाल USB_BUS_REMOVE:
		mon_bus_हटाओ(dev);
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block mon_nb = अणु
	.notअगरier_call = 	mon_notअगरy,
पूर्ण;

/*
 * Ops
 */
अटल स्थिर काष्ठा usb_mon_operations mon_ops_0 = अणु
	.urb_submit =	mon_submit,
	.urb_submit_error = mon_submit_error,
	.urb_complete =	mon_complete,
पूर्ण;

/*
 * Tear usb_bus and mon_bus apart.
 */
अटल व्योम mon_dissolve(काष्ठा mon_bus *mbus, काष्ठा usb_bus *ubus)
अणु

	अगर (ubus->monitored) अणु
		ubus->monitored = 0;
		mb();
	पूर्ण

	ubus->mon_bus = शून्य;
	mbus->u_bus = शून्य;
	mb();

	/* We want synchronize_irq() here, but that needs an argument. */
पूर्ण

/*
 */
अटल व्योम mon_bus_drop(काष्ठा kref *r)
अणु
	काष्ठा mon_bus *mbus = container_of(r, काष्ठा mon_bus, ref);
	kमुक्त(mbus);
पूर्ण

/*
 * Initialize a bus क्रम us:
 *  - allocate mon_bus
 *  - refcount USB bus काष्ठा
 *  - link
 */
अटल व्योम mon_bus_init(काष्ठा usb_bus *ubus)
अणु
	काष्ठा mon_bus *mbus;

	mbus = kzalloc(माप(काष्ठा mon_bus), GFP_KERNEL);
	अगर (mbus == शून्य)
		जाओ err_alloc;
	kref_init(&mbus->ref);
	spin_lock_init(&mbus->lock);
	INIT_LIST_HEAD(&mbus->r_list);

	/*
	 * We करोn't need to take a reference to ubus, because we receive
	 * a notअगरication अगर the bus is about to be हटाओd.
	 */
	mbus->u_bus = ubus;
	ubus->mon_bus = mbus;

	mbus->text_inited = mon_text_add(mbus, ubus);
	mbus->bin_inited = mon_bin_add(mbus, ubus);

	mutex_lock(&mon_lock);
	list_add_tail(&mbus->bus_link, &mon_buses);
	mutex_unlock(&mon_lock);
	वापस;

err_alloc:
	वापस;
पूर्ण

अटल व्योम mon_bus0_init(व्योम)
अणु
	काष्ठा mon_bus *mbus = &mon_bus0;

	kref_init(&mbus->ref);
	spin_lock_init(&mbus->lock);
	INIT_LIST_HEAD(&mbus->r_list);

	mbus->text_inited = mon_text_add(mbus, शून्य);
	mbus->bin_inited = mon_bin_add(mbus, शून्य);
पूर्ण

/*
 * Search a USB bus by number. Notice that USB bus numbers start from one,
 * which we may later use to identअगरy "all" with zero.
 *
 * This function must be called with mon_lock held.
 *
 * This is obviously inefficient and may be revised in the future.
 */
काष्ठा mon_bus *mon_bus_lookup(अचिन्हित पूर्णांक num)
अणु
	काष्ठा list_head *p;
	काष्ठा mon_bus *mbus;

	अगर (num == 0) अणु
		वापस &mon_bus0;
	पूर्ण
	list_क्रम_each (p, &mon_buses) अणु
		mbus = list_entry(p, काष्ठा mon_bus, bus_link);
		अगर (mbus->u_bus->busnum == num) अणु
			वापस mbus;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक __init mon_init(व्योम)
अणु
	काष्ठा usb_bus *ubus;
	पूर्णांक rc, id;

	अगर ((rc = mon_text_init()) != 0)
		जाओ err_text;
	अगर ((rc = mon_bin_init()) != 0)
		जाओ err_bin;

	mon_bus0_init();

	अगर (usb_mon_रेजिस्टर(&mon_ops_0) != 0) अणु
		prपूर्णांकk(KERN_NOTICE TAG ": unable to register with the core\n");
		rc = -ENODEV;
		जाओ err_reg;
	पूर्ण
	// MOD_INC_USE_COUNT(which_module?);

	mutex_lock(&usb_bus_idr_lock);
	idr_क्रम_each_entry(&usb_bus_idr, ubus, id)
		mon_bus_init(ubus);
	usb_रेजिस्टर_notअगरy(&mon_nb);
	mutex_unlock(&usb_bus_idr_lock);
	वापस 0;

err_reg:
	mon_bin_निकास();
err_bin:
	mon_text_निकास();
err_text:
	वापस rc;
पूर्ण

अटल व्योम __निकास mon_निकास(व्योम)
अणु
	काष्ठा mon_bus *mbus;
	काष्ठा list_head *p;

	usb_unरेजिस्टर_notअगरy(&mon_nb);
	usb_mon_deरेजिस्टर();

	mutex_lock(&mon_lock);

	जबतक (!list_empty(&mon_buses)) अणु
		p = mon_buses.next;
		mbus = list_entry(p, काष्ठा mon_bus, bus_link);
		list_del(p);

		अगर (mbus->text_inited)
			mon_text_del(mbus);
		अगर (mbus->bin_inited)
			mon_bin_del(mbus);

		/*
		 * This never happens, because the खोलो/बंद paths in
		 * file level मुख्यtain module use counters and so rmmod fails
		 * beक्रमe reaching here. However, better be safe...
		 */
		अगर (mbus->nपढ़ोers) अणु
			prपूर्णांकk(KERN_ERR TAG
			    ": Outstanding opens (%d) on usb%d, leaking...\n",
			    mbus->nपढ़ोers, mbus->u_bus->busnum);
			kref_get(&mbus->ref); /* Force leak */
		पूर्ण

		mon_dissolve(mbus, mbus->u_bus);
		kref_put(&mbus->ref, mon_bus_drop);
	पूर्ण

	mbus = &mon_bus0;
	अगर (mbus->text_inited)
		mon_text_del(mbus);
	अगर (mbus->bin_inited)
		mon_bin_del(mbus);

	mutex_unlock(&mon_lock);

	mon_text_निकास();
	mon_bin_निकास();
पूर्ण

module_init(mon_init);
module_निकास(mon_निकास);

MODULE_LICENSE("GPL");
