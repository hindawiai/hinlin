<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश "edac_module.h"

अटल काष्ठा workqueue_काष्ठा *wq;

bool edac_queue_work(काष्ठा delayed_work *work, अचिन्हित दीर्घ delay)
अणु
	वापस queue_delayed_work(wq, work, delay);
पूर्ण
EXPORT_SYMBOL_GPL(edac_queue_work);

bool edac_mod_work(काष्ठा delayed_work *work, अचिन्हित दीर्घ delay)
अणु
	वापस mod_delayed_work(wq, work, delay);
पूर्ण
EXPORT_SYMBOL_GPL(edac_mod_work);

bool edac_stop_work(काष्ठा delayed_work *work)
अणु
	bool ret;

	ret = cancel_delayed_work_sync(work);
	flush_workqueue(wq);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(edac_stop_work);

पूर्णांक edac_workqueue_setup(व्योम)
अणु
	wq = alloc_ordered_workqueue("edac-poller", WQ_MEM_RECLAIM);
	अगर (!wq)
		वापस -ENODEV;
	अन्यथा
		वापस 0;
पूर्ण

व्योम edac_workqueue_tearकरोwn(व्योम)
अणु
	flush_workqueue(wq);
	destroy_workqueue(wq);
	wq = शून्य;
पूर्ण
