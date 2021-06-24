<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Hammerspace Inc
 */

#समावेश <linux/module.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/rcupdate.h>

#समावेश "nfs4_fs.h"
#समावेश "netns.h"
#समावेश "sysfs.h"

काष्ठा kobject *nfs_client_kobj;
अटल काष्ठा kset *nfs_client_kset;

अटल व्योम nfs_netns_object_release(काष्ठा kobject *kobj)
अणु
	kमुक्त(kobj);
पूर्ण

अटल स्थिर काष्ठा kobj_ns_type_operations *nfs_netns_object_child_ns_type(
		काष्ठा kobject *kobj)
अणु
	वापस &net_ns_type_operations;
पूर्ण

अटल काष्ठा kobj_type nfs_netns_object_type = अणु
	.release = nfs_netns_object_release,
	.sysfs_ops = &kobj_sysfs_ops,
	.child_ns_type = nfs_netns_object_child_ns_type,
पूर्ण;

अटल काष्ठा kobject *nfs_netns_object_alloc(स्थिर अक्षर *name,
		काष्ठा kset *kset, काष्ठा kobject *parent)
अणु
	काष्ठा kobject *kobj;

	kobj = kzalloc(माप(*kobj), GFP_KERNEL);
	अगर (kobj) अणु
		kobj->kset = kset;
		अगर (kobject_init_and_add(kobj, &nfs_netns_object_type,
					parent, "%s", name) == 0)
			वापस kobj;
		kobject_put(kobj);
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक nfs_sysfs_init(व्योम)
अणु
	nfs_client_kset = kset_create_and_add("nfs", शून्य, fs_kobj);
	अगर (!nfs_client_kset)
		वापस -ENOMEM;
	nfs_client_kobj = nfs_netns_object_alloc("net", nfs_client_kset, शून्य);
	अगर  (!nfs_client_kobj) अणु
		kset_unरेजिस्टर(nfs_client_kset);
		nfs_client_kset = शून्य;
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम nfs_sysfs_निकास(व्योम)
अणु
	kobject_put(nfs_client_kobj);
	kset_unरेजिस्टर(nfs_client_kset);
पूर्ण

अटल sमाप_प्रकार nfs_netns_identअगरier_show(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nfs_netns_client *c = container_of(kobj,
			काष्ठा nfs_netns_client,
			kobject);
	sमाप_प्रकार ret;

	rcu_पढ़ो_lock();
	ret = scnम_लिखो(buf, PAGE_SIZE, "%s\n", rcu_dereference(c->identअगरier));
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/* Strip trailing '\n' */
अटल माप_प्रकार nfs_string_strip(स्थिर अक्षर *c, माप_प्रकार len)
अणु
	जबतक (len > 0 && c[len-1] == '\n')
		--len;
	वापस len;
पूर्ण

अटल sमाप_प्रकार nfs_netns_identअगरier_store(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nfs_netns_client *c = container_of(kobj,
			काष्ठा nfs_netns_client,
			kobject);
	स्थिर अक्षर *old;
	अक्षर *p;
	माप_प्रकार len;

	len = nfs_string_strip(buf, min_t(माप_प्रकार, count, CONTAINER_ID_MAXLEN));
	अगर (!len)
		वापस 0;
	p = kmemdup_nul(buf, len, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;
	old = rcu_dereference_रक्षित(xchg(&c->identअगरier, (अक्षर __rcu *)p), 1);
	अगर (old) अणु
		synchronize_rcu();
		kमुक्त(old);
	पूर्ण
	वापस count;
पूर्ण

अटल व्योम nfs_netns_client_release(काष्ठा kobject *kobj)
अणु
	काष्ठा nfs_netns_client *c = container_of(kobj,
			काष्ठा nfs_netns_client,
			kobject);

	kमुक्त(rcu_dereference_raw(c->identअगरier));
	kमुक्त(c);
पूर्ण

अटल स्थिर व्योम *nfs_netns_client_namespace(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा nfs_netns_client, kobject)->net;
पूर्ण

अटल काष्ठा kobj_attribute nfs_netns_client_id = __ATTR(identअगरier,
		0644, nfs_netns_identअगरier_show, nfs_netns_identअगरier_store);

अटल काष्ठा attribute *nfs_netns_client_attrs[] = अणु
	&nfs_netns_client_id.attr,
	शून्य,
पूर्ण;

अटल काष्ठा kobj_type nfs_netns_client_type = अणु
	.release = nfs_netns_client_release,
	.शेष_attrs = nfs_netns_client_attrs,
	.sysfs_ops = &kobj_sysfs_ops,
	.namespace = nfs_netns_client_namespace,
पूर्ण;

अटल काष्ठा nfs_netns_client *nfs_netns_client_alloc(काष्ठा kobject *parent,
		काष्ठा net *net)
अणु
	काष्ठा nfs_netns_client *p;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (p) अणु
		p->net = net;
		p->kobject.kset = nfs_client_kset;
		अगर (kobject_init_and_add(&p->kobject, &nfs_netns_client_type,
					parent, "nfs_client") == 0)
			वापस p;
		kobject_put(&p->kobject);
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम nfs_netns_sysfs_setup(काष्ठा nfs_net *netns, काष्ठा net *net)
अणु
	काष्ठा nfs_netns_client *clp;

	clp = nfs_netns_client_alloc(nfs_client_kobj, net);
	अगर (clp) अणु
		netns->nfs_client = clp;
		kobject_uevent(&clp->kobject, KOBJ_ADD);
	पूर्ण
पूर्ण

व्योम nfs_netns_sysfs_destroy(काष्ठा nfs_net *netns)
अणु
	काष्ठा nfs_netns_client *clp = netns->nfs_client;

	अगर (clp) अणु
		kobject_uevent(&clp->kobject, KOBJ_REMOVE);
		kobject_del(&clp->kobject);
		kobject_put(&clp->kobject);
		netns->nfs_client = शून्य;
	पूर्ण
पूर्ण
