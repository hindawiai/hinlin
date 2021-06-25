<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Pvpanic Device Support
 *
 *  Copyright (C) 2013 Fujitsu.
 *  Copyright (C) 2018 ZTE.
 *  Copyright (C) 2021 Oracle.
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>
#समावेश <linux/cdev.h>
#समावेश <linux/list.h>

#समावेश <uapi/misc/pvpanic.h>

#समावेश "pvpanic.h"

MODULE_AUTHOR("Mihai Carabas <mihai.carabas@oracle.com>");
MODULE_DESCRIPTION("pvpanic device driver ");
MODULE_LICENSE("GPL");

अटल काष्ठा list_head pvpanic_list;
अटल spinlock_t pvpanic_lock;

अटल व्योम
pvpanic_send_event(अचिन्हित पूर्णांक event)
अणु
	काष्ठा pvpanic_instance *pi_cur;

	spin_lock(&pvpanic_lock);
	list_क्रम_each_entry(pi_cur, &pvpanic_list, list) अणु
		अगर (event & pi_cur->capability & pi_cur->events)
			ioग_लिखो8(event, pi_cur->base);
	पूर्ण
	spin_unlock(&pvpanic_lock);
पूर्ण

अटल पूर्णांक
pvpanic_panic_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ code,
		     व्योम *unused)
अणु
	अचिन्हित पूर्णांक event = PVPANIC_PANICKED;

	अगर (kexec_crash_loaded())
		event = PVPANIC_CRASH_LOADED;

	pvpanic_send_event(event);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block pvpanic_panic_nb = अणु
	.notअगरier_call = pvpanic_panic_notअगरy,
	.priority = 1, /* let this called beक्रमe broken drm_fb_helper */
पूर्ण;

पूर्णांक pvpanic_probe(काष्ठा pvpanic_instance *pi)
अणु
	अगर (!pi || !pi->base)
		वापस -EINVAL;

	spin_lock(&pvpanic_lock);
	list_add(&pi->list, &pvpanic_list);
	spin_unlock(&pvpanic_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pvpanic_probe);

व्योम pvpanic_हटाओ(काष्ठा pvpanic_instance *pi)
अणु
	काष्ठा pvpanic_instance *pi_cur, *pi_next;

	अगर (!pi)
		वापस;

	spin_lock(&pvpanic_lock);
	list_क्रम_each_entry_safe(pi_cur, pi_next, &pvpanic_list, list) अणु
		अगर (pi_cur == pi) अणु
			list_del(&pi_cur->list);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&pvpanic_lock);
पूर्ण
EXPORT_SYMBOL_GPL(pvpanic_हटाओ);

अटल पूर्णांक pvpanic_init(व्योम)
अणु
	INIT_LIST_HEAD(&pvpanic_list);
	spin_lock_init(&pvpanic_lock);

	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
				       &pvpanic_panic_nb);

	वापस 0;
पूर्ण

अटल व्योम pvpanic_निकास(व्योम)
अणु
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list,
					 &pvpanic_panic_nb);

पूर्ण

module_init(pvpanic_init);
module_निकास(pvpanic_निकास);
