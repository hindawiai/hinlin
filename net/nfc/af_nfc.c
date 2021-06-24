<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 *
 * Authors:
 *    Aloisio Almeida Jr <aloisio.almeida@खोलोbossa.org>
 *    Lauro Ramos Venancio <lauro.venancio@खोलोbossa.org>
 */

#समावेश <linux/nfc.h>
#समावेश <linux/module.h>

#समावेश "nfc.h"

अटल DEFINE_RWLOCK(proto_tab_lock);
अटल स्थिर काष्ठा nfc_protocol *proto_tab[NFC_SOCKPROTO_MAX];

अटल पूर्णांक nfc_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक proto,
			   पूर्णांक kern)
अणु
	पूर्णांक rc = -EPROTONOSUPPORT;

	अगर (net != &init_net)
		वापस -EAFNOSUPPORT;

	अगर (proto < 0 || proto >= NFC_SOCKPROTO_MAX)
		वापस -EINVAL;

	पढ़ो_lock(&proto_tab_lock);
	अगर (proto_tab[proto] &&	try_module_get(proto_tab[proto]->owner)) अणु
		rc = proto_tab[proto]->create(net, sock, proto_tab[proto], kern);
		module_put(proto_tab[proto]->owner);
	पूर्ण
	पढ़ो_unlock(&proto_tab_lock);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_proto_family nfc_sock_family_ops = अणु
	.owner  = THIS_MODULE,
	.family = PF_NFC,
	.create = nfc_sock_create,
पूर्ण;

पूर्णांक nfc_proto_रेजिस्टर(स्थिर काष्ठा nfc_protocol *nfc_proto)
अणु
	पूर्णांक rc;

	अगर (nfc_proto->id < 0 || nfc_proto->id >= NFC_SOCKPROTO_MAX)
		वापस -EINVAL;

	rc = proto_रेजिस्टर(nfc_proto->proto, 0);
	अगर (rc)
		वापस rc;

	ग_लिखो_lock(&proto_tab_lock);
	अगर (proto_tab[nfc_proto->id])
		rc = -EBUSY;
	अन्यथा
		proto_tab[nfc_proto->id] = nfc_proto;
	ग_लिखो_unlock(&proto_tab_lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(nfc_proto_रेजिस्टर);

व्योम nfc_proto_unरेजिस्टर(स्थिर काष्ठा nfc_protocol *nfc_proto)
अणु
	ग_लिखो_lock(&proto_tab_lock);
	proto_tab[nfc_proto->id] = शून्य;
	ग_लिखो_unlock(&proto_tab_lock);

	proto_unरेजिस्टर(nfc_proto->proto);
पूर्ण
EXPORT_SYMBOL(nfc_proto_unरेजिस्टर);

पूर्णांक __init af_nfc_init(व्योम)
अणु
	वापस sock_रेजिस्टर(&nfc_sock_family_ops);
पूर्ण

व्योम af_nfc_निकास(व्योम)
अणु
	sock_unरेजिस्टर(PF_NFC);
पूर्ण
