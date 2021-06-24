<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 * Copyright (C) 2015 Nobuo Iwata
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "usbip_common.h"

काष्ठा usbip_event अणु
	काष्ठा list_head node;
	काष्ठा usbip_device *ud;
पूर्ण;

अटल DEFINE_SPINLOCK(event_lock);
अटल LIST_HEAD(event_list);

अटल व्योम set_event(काष्ठा usbip_device *ud, अचिन्हित दीर्घ event)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ud->lock, flags);
	ud->event |= event;
	spin_unlock_irqrestore(&ud->lock, flags);
पूर्ण

अटल व्योम unset_event(काष्ठा usbip_device *ud, अचिन्हित दीर्घ event)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ud->lock, flags);
	ud->event &= ~event;
	spin_unlock_irqrestore(&ud->lock, flags);
पूर्ण

अटल काष्ठा usbip_device *get_event(व्योम)
अणु
	काष्ठा usbip_event *ue = शून्य;
	काष्ठा usbip_device *ud = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&event_lock, flags);
	अगर (!list_empty(&event_list)) अणु
		ue = list_first_entry(&event_list, काष्ठा usbip_event, node);
		list_del(&ue->node);
	पूर्ण
	spin_unlock_irqrestore(&event_lock, flags);

	अगर (ue) अणु
		ud = ue->ud;
		kमुक्त(ue);
	पूर्ण
	वापस ud;
पूर्ण

अटल काष्ठा task_काष्ठा *worker_context;

अटल व्योम event_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usbip_device *ud;

	अगर (worker_context == शून्य) अणु
		worker_context = current;
	पूर्ण

	जबतक ((ud = get_event()) != शून्य) अणु
		usbip_dbg_eh("pending event %lx\n", ud->event);

		mutex_lock(&ud->sysfs_lock);
		/*
		 * NOTE: shutकरोwn must come first.
		 * Shutकरोwn the device.
		 */
		अगर (ud->event & USBIP_EH_SHUTDOWN) अणु
			ud->eh_ops.shutकरोwn(ud);
			unset_event(ud, USBIP_EH_SHUTDOWN);
		पूर्ण

		/* Reset the device. */
		अगर (ud->event & USBIP_EH_RESET) अणु
			ud->eh_ops.reset(ud);
			unset_event(ud, USBIP_EH_RESET);
		पूर्ण

		/* Mark the device as unusable. */
		अगर (ud->event & USBIP_EH_UNUSABLE) अणु
			ud->eh_ops.unusable(ud);
			unset_event(ud, USBIP_EH_UNUSABLE);
		पूर्ण
		mutex_unlock(&ud->sysfs_lock);

		wake_up(&ud->eh_रुकोq);
	पूर्ण
पूर्ण

पूर्णांक usbip_start_eh(काष्ठा usbip_device *ud)
अणु
	init_रुकोqueue_head(&ud->eh_रुकोq);
	ud->event = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbip_start_eh);

व्योम usbip_stop_eh(काष्ठा usbip_device *ud)
अणु
	अचिन्हित दीर्घ pending = ud->event & ~USBIP_EH_BYE;

	अगर (!(ud->event & USBIP_EH_BYE))
		usbip_dbg_eh("usbip_eh stopping but not removed\n");

	अगर (pending)
		usbip_dbg_eh("usbip_eh waiting completion %lx\n", pending);

	रुको_event_पूर्णांकerruptible(ud->eh_रुकोq, !(ud->event & ~USBIP_EH_BYE));
	usbip_dbg_eh("usbip_eh has stopped\n");
पूर्ण
EXPORT_SYMBOL_GPL(usbip_stop_eh);

#घोषणा WORK_QUEUE_NAME "usbip_event"

अटल काष्ठा workqueue_काष्ठा *usbip_queue;
अटल DECLARE_WORK(usbip_work, event_handler);

पूर्णांक usbip_init_eh(व्योम)
अणु
	usbip_queue = create_singlethपढ़ो_workqueue(WORK_QUEUE_NAME);
	अगर (usbip_queue == शून्य) अणु
		pr_err("failed to create usbip_event\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम usbip_finish_eh(व्योम)
अणु
	flush_workqueue(usbip_queue);
	destroy_workqueue(usbip_queue);
	usbip_queue = शून्य;
पूर्ण

व्योम usbip_event_add(काष्ठा usbip_device *ud, अचिन्हित दीर्घ event)
अणु
	काष्ठा usbip_event *ue;
	अचिन्हित दीर्घ flags;

	अगर (ud->event & USBIP_EH_BYE)
		वापस;

	set_event(ud, event);

	spin_lock_irqsave(&event_lock, flags);

	list_क्रम_each_entry_reverse(ue, &event_list, node) अणु
		अगर (ue->ud == ud)
			जाओ out;
	पूर्ण

	ue = kदो_स्मृति(माप(काष्ठा usbip_event), GFP_ATOMIC);
	अगर (ue == शून्य)
		जाओ out;

	ue->ud = ud;

	list_add_tail(&ue->node, &event_list);
	queue_work(usbip_queue, &usbip_work);

out:
	spin_unlock_irqrestore(&event_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(usbip_event_add);

पूर्णांक usbip_event_happened(काष्ठा usbip_device *ud)
अणु
	पूर्णांक happened = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ud->lock, flags);
	अगर (ud->event != 0)
		happened = 1;
	spin_unlock_irqrestore(&ud->lock, flags);

	वापस happened;
पूर्ण
EXPORT_SYMBOL_GPL(usbip_event_happened);

पूर्णांक usbip_in_eh(काष्ठा task_काष्ठा *task)
अणु
	अगर (task == worker_context)
		वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usbip_in_eh);
