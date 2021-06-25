<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Structure dynamic extension infraकाष्ठाure
 * Copyright (C) 2004 Rusty Russell IBM Corporation
 * Copyright (C) 2007 Netfilter Core Team <coreteam@netfilter.org>
 * Copyright (C) 2007 USAGI/WIDE Project <http://www.linux-ipv6.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>

अटल काष्ठा nf_ct_ext_type __rcu *nf_ct_ext_types[NF_CT_EXT_NUM];
अटल DEFINE_MUTEX(nf_ct_ext_type_mutex);
#घोषणा NF_CT_EXT_PREALLOC	128u /* conntrack events are on by शेष */

व्योम nf_ct_ext_destroy(काष्ठा nf_conn *ct)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा nf_ct_ext_type *t;

	क्रम (i = 0; i < NF_CT_EXT_NUM; i++) अणु
		rcu_पढ़ो_lock();
		t = rcu_dereference(nf_ct_ext_types[i]);

		/* Here the nf_ct_ext_type might have been unरेजिस्टरd.
		 * I.e., it has responsible to cleanup निजी
		 * area in all conntracks when it is unरेजिस्टरd.
		 */
		अगर (t && t->destroy)
			t->destroy(ct);
		rcu_पढ़ो_unlock();
	पूर्ण

	kमुक्त(ct->ext);
पूर्ण

व्योम *nf_ct_ext_add(काष्ठा nf_conn *ct, क्रमागत nf_ct_ext_id id, gfp_t gfp)
अणु
	अचिन्हित पूर्णांक newlen, newoff, oldlen, alloc;
	काष्ठा nf_ct_ext_type *t;
	काष्ठा nf_ct_ext *new;

	/* Conntrack must not be confirmed to aव्योम races on पुनः_स्मृतिation. */
	WARN_ON(nf_ct_is_confirmed(ct));


	अगर (ct->ext) अणु
		स्थिर काष्ठा nf_ct_ext *old = ct->ext;

		अगर (__nf_ct_ext_exist(old, id))
			वापस शून्य;
		oldlen = old->len;
	पूर्ण अन्यथा अणु
		oldlen = माप(*new);
	पूर्ण

	rcu_पढ़ो_lock();
	t = rcu_dereference(nf_ct_ext_types[id]);
	अगर (!t) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण

	newoff = ALIGN(oldlen, t->align);
	newlen = newoff + t->len;
	rcu_पढ़ो_unlock();

	alloc = max(newlen, NF_CT_EXT_PREALLOC);
	new = kपुनः_स्मृति(ct->ext, alloc, gfp);
	अगर (!new)
		वापस शून्य;

	अगर (!ct->ext)
		स_रखो(new->offset, 0, माप(new->offset));

	new->offset[id] = newoff;
	new->len = newlen;
	स_रखो((व्योम *)new + newoff, 0, newlen - newoff);

	ct->ext = new;
	वापस (व्योम *)new + newoff;
पूर्ण
EXPORT_SYMBOL(nf_ct_ext_add);

/* This MUST be called in process context. */
पूर्णांक nf_ct_extend_रेजिस्टर(स्थिर काष्ठा nf_ct_ext_type *type)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&nf_ct_ext_type_mutex);
	अगर (nf_ct_ext_types[type->id]) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	rcu_assign_poपूर्णांकer(nf_ct_ext_types[type->id], type);
out:
	mutex_unlock(&nf_ct_ext_type_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_extend_रेजिस्टर);

/* This MUST be called in process context. */
व्योम nf_ct_extend_unरेजिस्टर(स्थिर काष्ठा nf_ct_ext_type *type)
अणु
	mutex_lock(&nf_ct_ext_type_mutex);
	RCU_INIT_POINTER(nf_ct_ext_types[type->id], शून्य);
	mutex_unlock(&nf_ct_ext_type_mutex);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(nf_ct_extend_unरेजिस्टर);
