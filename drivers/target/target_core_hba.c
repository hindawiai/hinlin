<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_hba.c
 *
 * This file contains the TCM HBA Transport related functions.
 *
 * (c) Copyright 2003-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/net.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"

अटल LIST_HEAD(backend_list);
अटल DEFINE_MUTEX(backend_mutex);

अटल u32 hba_id_counter;

अटल DEFINE_SPINLOCK(hba_lock);
अटल LIST_HEAD(hba_list);


पूर्णांक transport_backend_रेजिस्टर(स्थिर काष्ठा target_backend_ops *ops)
अणु
	काष्ठा target_backend *tb, *old;

	tb = kzalloc(माप(*tb), GFP_KERNEL);
	अगर (!tb)
		वापस -ENOMEM;
	tb->ops = ops;

	mutex_lock(&backend_mutex);
	list_क्रम_each_entry(old, &backend_list, list) अणु
		अगर (!म_भेद(old->ops->name, ops->name)) अणु
			pr_err("backend %s already registered.\n", ops->name);
			mutex_unlock(&backend_mutex);
			kमुक्त(tb);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	target_setup_backend_cits(tb);
	list_add_tail(&tb->list, &backend_list);
	mutex_unlock(&backend_mutex);

	pr_debug("TCM: Registered subsystem plugin: %s struct module: %p\n",
			ops->name, ops->owner);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(transport_backend_रेजिस्टर);

व्योम target_backend_unरेजिस्टर(स्थिर काष्ठा target_backend_ops *ops)
अणु
	काष्ठा target_backend *tb;

	mutex_lock(&backend_mutex);
	list_क्रम_each_entry(tb, &backend_list, list) अणु
		अगर (tb->ops == ops) अणु
			list_del(&tb->list);
			mutex_unlock(&backend_mutex);
			/*
			 * Wait क्रम any outstanding backend driver ->rcu_head
			 * callbacks to complete post TBO->मुक्त_device() ->
			 * call_rcu(), beक्रमe allowing backend driver module
			 * unload of target_backend_ops->owner to proceed.
			 */
			rcu_barrier();
			kमुक्त(tb);
			वापस;
		पूर्ण
	पूर्ण
	mutex_unlock(&backend_mutex);
पूर्ण
EXPORT_SYMBOL(target_backend_unरेजिस्टर);

अटल काष्ठा target_backend *core_get_backend(स्थिर अक्षर *name)
अणु
	काष्ठा target_backend *tb;

	mutex_lock(&backend_mutex);
	list_क्रम_each_entry(tb, &backend_list, list) अणु
		अगर (!म_भेद(tb->ops->name, name))
			जाओ found;
	पूर्ण
	mutex_unlock(&backend_mutex);
	वापस शून्य;
found:
	अगर (tb->ops->owner && !try_module_get(tb->ops->owner))
		tb = शून्य;
	mutex_unlock(&backend_mutex);
	वापस tb;
पूर्ण

काष्ठा se_hba *
core_alloc_hba(स्थिर अक्षर *plugin_name, u32 plugin_dep_id, u32 hba_flags)
अणु
	काष्ठा se_hba *hba;
	पूर्णांक ret = 0;

	hba = kzalloc(माप(*hba), GFP_KERNEL);
	अगर (!hba) अणु
		pr_err("Unable to allocate struct se_hba\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	spin_lock_init(&hba->device_lock);
	mutex_init(&hba->hba_access_mutex);

	hba->hba_index = scsi_get_new_index(SCSI_INST_INDEX);
	hba->hba_flags |= hba_flags;

	hba->backend = core_get_backend(plugin_name);
	अगर (!hba->backend) अणु
		ret = -EINVAL;
		जाओ out_मुक्त_hba;
	पूर्ण

	ret = hba->backend->ops->attach_hba(hba, plugin_dep_id);
	अगर (ret < 0)
		जाओ out_module_put;

	spin_lock(&hba_lock);
	hba->hba_id = hba_id_counter++;
	list_add_tail(&hba->hba_node, &hba_list);
	spin_unlock(&hba_lock);

	pr_debug("CORE_HBA[%d] - Attached HBA to Generic Target"
			" Core\n", hba->hba_id);

	वापस hba;

out_module_put:
	module_put(hba->backend->ops->owner);
	hba->backend = शून्य;
out_मुक्त_hba:
	kमुक्त(hba);
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक
core_delete_hba(काष्ठा se_hba *hba)
अणु
	WARN_ON(hba->dev_count);

	hba->backend->ops->detach_hba(hba);

	spin_lock(&hba_lock);
	list_del(&hba->hba_node);
	spin_unlock(&hba_lock);

	pr_debug("CORE_HBA[%d] - Detached HBA from Generic Target"
			" Core\n", hba->hba_id);

	module_put(hba->backend->ops->owner);

	hba->backend = शून्य;
	kमुक्त(hba);
	वापस 0;
पूर्ण

bool target_sense_desc_क्रमmat(काष्ठा se_device *dev)
अणु
	वापस (dev) ? dev->transport->get_blocks(dev) > U32_MAX : false;
पूर्ण
