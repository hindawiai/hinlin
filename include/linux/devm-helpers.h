<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __LINUX_DEVM_HELPERS_H
#घोषणा __LINUX_DEVM_HELPERS_H

/*
 * Functions which करो स्वतःmatically cancel operations or release resources upon
 * driver detach.
 *
 * These should be helpful to aव्योम mixing the manual and devm-based resource
 * management which can be source of annoying, rarely occurring,
 * hard-to-reproduce bugs.
 *
 * Please take पूर्णांकo account that devm based cancellation may be perक्रमmed some
 * समय after the हटाओ() is ran.
 *
 * Thus mixing devm and manual resource management can easily cause problems
 * when unwinding operations with dependencies. IRQ scheduling a work in a queue
 * is typical example where IRQs are often devm-managed and WQs are manually
 * cleaned at हटाओ(). If IRQs are not manually मुक्तd at हटाओ() (and this is
 * often the हाल when we use devm क्रम IRQs) we have a period of समय after
 * हटाओ() - and beक्रमe devm managed IRQs are मुक्तd - where new IRQ may fire
 * and schedule a work item which won't be cancelled because हटाओ() was
 * alपढ़ोy ran.
 */

#समावेश <linux/device.h>
#समावेश <linux/workqueue.h>

अटल अंतरभूत व्योम devm_delayed_work_drop(व्योम *res)
अणु
	cancel_delayed_work_sync(res);
पूर्ण

/**
 * devm_delayed_work_स्वतःcancel - Resource-managed delayed work allocation
 * @dev:	Device which lअगरeसमय work is bound to
 * @w:		Work item to be queued
 * @worker:	Worker function
 *
 * Initialize delayed work which is स्वतःmatically cancelled when driver is
 * detached. A few drivers need delayed work which must be cancelled beक्रमe
 * driver is detached to aव्योम accessing हटाओd resources.
 * devm_delayed_work_स्वतःcancel() can be used to omit the explicit
 * cancelleation when driver is detached.
 */
अटल अंतरभूत पूर्णांक devm_delayed_work_स्वतःcancel(काष्ठा device *dev,
					       काष्ठा delayed_work *w,
					       work_func_t worker)
अणु
	INIT_DELAYED_WORK(w, worker);
	वापस devm_add_action(dev, devm_delayed_work_drop, w);
पूर्ण

#पूर्ण_अगर
