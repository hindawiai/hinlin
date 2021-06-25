<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Network event notअगरiers
 *
 *	Authors:
 *      Tom Tucker             <tom@खोलोgridcomputing.com>
 *      Steve Wise             <swise@खोलोgridcomputing.com>
 *
 *	Fixes:
 */

#समावेश <linux/rtnetlink.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/export.h>
#समावेश <net/netevent.h>

अटल ATOMIC_NOTIFIER_HEAD(netevent_notअगर_chain);

/**
 *	रेजिस्टर_netevent_notअगरier - रेजिस्टर a netevent notअगरier block
 *	@nb: notअगरier
 *
 *	Register a notअगरier to be called when a netevent occurs.
 *	The notअगरier passed is linked पूर्णांकo the kernel काष्ठाures and must
 *	not be reused until it has been unरेजिस्टरed. A negative त्रुटि_सं code
 *	is वापसed on a failure.
 */
पूर्णांक रेजिस्टर_netevent_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&netevent_notअगर_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_netevent_notअगरier);

/**
 *	unरेजिस्टर_netevent_notअगरier - unरेजिस्टर a netevent notअगरier block
 *	@nb: notअगरier
 *
 *	Unरेजिस्टर a notअगरier previously रेजिस्टरed by
 *	रेजिस्टर_neigh_notअगरier(). The notअगरier is unlinked पूर्णांकo the
 *	kernel काष्ठाures and may then be reused. A negative त्रुटि_सं code
 *	is वापसed on a failure.
 */

पूर्णांक unरेजिस्टर_netevent_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&netevent_notअगर_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_netevent_notअगरier);

/**
 *	call_netevent_notअगरiers - call all netevent notअगरier blocks
 *      @val: value passed unmodअगरied to notअगरier function
 *      @v:   poपूर्णांकer passed unmodअगरied to notअगरier function
 *
 *	Call all neighbour notअगरier blocks.  Parameters and वापस value
 *	are as क्रम notअगरier_call_chain().
 */

पूर्णांक call_netevent_notअगरiers(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस atomic_notअगरier_call_chain(&netevent_notअगर_chain, val, v);
पूर्ण
EXPORT_SYMBOL_GPL(call_netevent_notअगरiers);
