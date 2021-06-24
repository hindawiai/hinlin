<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010, Intel Corporation.
 *
 * Author: John Fastabend <john.r.fastabend@पूर्णांकel.com>
 */

#समावेश <linux/rtnetlink.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/export.h>
#समावेश <net/dcbevent.h>

अटल ATOMIC_NOTIFIER_HEAD(dcbevent_notअगर_chain);

पूर्णांक रेजिस्टर_dcbevent_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&dcbevent_notअगर_chain, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_dcbevent_notअगरier);

पूर्णांक unरेजिस्टर_dcbevent_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&dcbevent_notअगर_chain, nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_dcbevent_notअगरier);

पूर्णांक call_dcbevent_notअगरiers(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस atomic_notअगरier_call_chain(&dcbevent_notअगर_chain, val, v);
पूर्ण
