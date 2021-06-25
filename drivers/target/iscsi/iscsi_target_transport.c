<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <target/iscsi/iscsi_transport.h>

अटल LIST_HEAD(g_transport_list);
अटल DEFINE_MUTEX(transport_mutex);

काष्ठा iscsit_transport *iscsit_get_transport(पूर्णांक type)
अणु
	काष्ठा iscsit_transport *t;

	mutex_lock(&transport_mutex);
	list_क्रम_each_entry(t, &g_transport_list, t_node) अणु
		अगर (t->transport_type == type) अणु
			अगर (t->owner && !try_module_get(t->owner)) अणु
				t = शून्य;
			पूर्ण
			mutex_unlock(&transport_mutex);
			वापस t;
		पूर्ण
	पूर्ण
	mutex_unlock(&transport_mutex);

	वापस शून्य;
पूर्ण

व्योम iscsit_put_transport(काष्ठा iscsit_transport *t)
अणु
	module_put(t->owner);
पूर्ण

व्योम iscsit_रेजिस्टर_transport(काष्ठा iscsit_transport *t)
अणु
	INIT_LIST_HEAD(&t->t_node);

	mutex_lock(&transport_mutex);
	list_add_tail(&t->t_node, &g_transport_list);
	mutex_unlock(&transport_mutex);

	pr_debug("Registered iSCSI transport: %s\n", t->name);
पूर्ण
EXPORT_SYMBOL(iscsit_रेजिस्टर_transport);

व्योम iscsit_unरेजिस्टर_transport(काष्ठा iscsit_transport *t)
अणु
	mutex_lock(&transport_mutex);
	list_del(&t->t_node);
	mutex_unlock(&transport_mutex);

	pr_debug("Unregistered iSCSI transport: %s\n", t->name);
पूर्ण
EXPORT_SYMBOL(iscsit_unरेजिस्टर_transport);
