<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/svcauth_gss.h
 *
 * Bruce Fields <bfields@umich.edu>
 * Copyright (c) 2002 The Regents of the University of Michigan
 */

#अगर_अघोषित _LINUX_SUNRPC_SVCAUTH_GSS_H
#घोषणा _LINUX_SUNRPC_SVCAUTH_GSS_H

#समावेश <linux/sched.h>
#समावेश <linux/sunrpc/types.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/svcauth.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/auth_gss.h>

पूर्णांक gss_svc_init(व्योम);
व्योम gss_svc_shutकरोwn(व्योम);
पूर्णांक gss_svc_init_net(काष्ठा net *net);
व्योम gss_svc_shutकरोwn_net(काष्ठा net *net);
काष्ठा auth_करोमुख्य *svcauth_gss_रेजिस्टर_pseuकरोflavor(u32 pseuकरोflavor,
						      अक्षर *name);
u32 svcauth_gss_flavor(काष्ठा auth_करोमुख्य *करोm);

#पूर्ण_अगर /* _LINUX_SUNRPC_SVCAUTH_GSS_H */
