<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Netlink message type permission tables, क्रम user generated messages.
 *
 * Author: James Morris <jmorris@redhat.com>
 *
 * Copyright (C) 2004 Red Hat, Inc., James Morris <jmorris@redhat.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर.h>
#समावेश <linux/inet_diag.h>
#समावेश <linux/xfrm.h>
#समावेश <linux/audit.h>
#समावेश <linux/sock_diag.h>

#समावेश "flask.h"
#समावेश "av_permissions.h"
#समावेश "security.h"

काष्ठा nlmsg_perm अणु
	u16	nlmsg_type;
	u32	perm;
पूर्ण;

अटल स्थिर काष्ठा nlmsg_perm nlmsg_route_perms[] =
अणु
	अणु RTM_NEWLINK,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELLINK,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETLINK,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_SETLINK,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_NEWADDR,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELADDR,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETADDR,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWROUTE,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELROUTE,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETROUTE,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWNEIGH,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELNEIGH,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETNEIGH,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWRULE,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELRULE,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETRULE,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWQDISC,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELQDISC,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETQDISC,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWTCLASS,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELTCLASS,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETTCLASS,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWTFILTER,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELTFILTER,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETTFILTER,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWACTION,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELACTION,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETACTION,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWPREFIX,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETMULTICAST,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_GETANYCAST,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_GETNEIGHTBL,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_SETNEIGHTBL,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_NEWADDRLABEL,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELADDRLABEL,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETADDRLABEL,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_GETDCB,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_SETDCB,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_NEWNETCONF,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELNETCONF,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETNETCONF,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWMDB,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELMDB,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE  पूर्ण,
	अणु RTM_GETMDB,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWNSID,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELNSID,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_GETNSID,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWSTATS,		NETLINK_ROUTE_SOCKET__NLMSG_READ पूर्ण,
	अणु RTM_GETSTATS,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWCACHEREPORT,	NETLINK_ROUTE_SOCKET__NLMSG_READ पूर्ण,
	अणु RTM_NEWCHAIN,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELCHAIN,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETCHAIN,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWNEXTHOP,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELNEXTHOP,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETNEXTHOP,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWLINKPROP,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELLINKPROP,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_NEWVLAN,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELVLAN,		NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETVLAN,		NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
	अणु RTM_NEWNEXTHOPBUCKET,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_DELNEXTHOPBUCKET,	NETLINK_ROUTE_SOCKET__NLMSG_WRITE पूर्ण,
	अणु RTM_GETNEXTHOPBUCKET,	NETLINK_ROUTE_SOCKET__NLMSG_READ  पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nlmsg_perm nlmsg_tcpdiag_perms[] =
अणु
	अणु TCPDIAG_GETSOCK,	NETLINK_TCPDIAG_SOCKET__NLMSG_READ पूर्ण,
	अणु DCCPDIAG_GETSOCK,	NETLINK_TCPDIAG_SOCKET__NLMSG_READ पूर्ण,
	अणु SOCK_DIAG_BY_FAMILY,	NETLINK_TCPDIAG_SOCKET__NLMSG_READ पूर्ण,
	अणु SOCK_DESTROY,		NETLINK_TCPDIAG_SOCKET__NLMSG_WRITE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nlmsg_perm nlmsg_xfrm_perms[] =
अणु
	अणु XFRM_MSG_NEWSA,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_DELSA,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_GETSA,	NETLINK_XFRM_SOCKET__NLMSG_READ  पूर्ण,
	अणु XFRM_MSG_NEWPOLICY,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_DELPOLICY,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_GETPOLICY,	NETLINK_XFRM_SOCKET__NLMSG_READ  पूर्ण,
	अणु XFRM_MSG_ALLOCSPI,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_ACQUIRE,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_EXPIRE,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_UPDPOLICY,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_UPDSA,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_POLEXPIRE,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_FLUSHSA,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_FLUSHPOLICY,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_NEWAE,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_GETAE,	NETLINK_XFRM_SOCKET__NLMSG_READ  पूर्ण,
	अणु XFRM_MSG_REPORT,	NETLINK_XFRM_SOCKET__NLMSG_READ  पूर्ण,
	अणु XFRM_MSG_MIGRATE,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_NEWSADINFO,	NETLINK_XFRM_SOCKET__NLMSG_READ  पूर्ण,
	अणु XFRM_MSG_GETSADINFO,	NETLINK_XFRM_SOCKET__NLMSG_READ  पूर्ण,
	अणु XFRM_MSG_NEWSPDINFO,	NETLINK_XFRM_SOCKET__NLMSG_WRITE पूर्ण,
	अणु XFRM_MSG_GETSPDINFO,	NETLINK_XFRM_SOCKET__NLMSG_READ  पूर्ण,
	अणु XFRM_MSG_MAPPING,	NETLINK_XFRM_SOCKET__NLMSG_READ  पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nlmsg_perm nlmsg_audit_perms[] =
अणु
	अणु AUDIT_GET,		NETLINK_AUDIT_SOCKET__NLMSG_READ     पूर्ण,
	अणु AUDIT_SET,		NETLINK_AUDIT_SOCKET__NLMSG_WRITE    पूर्ण,
	अणु AUDIT_LIST,		NETLINK_AUDIT_SOCKET__NLMSG_READPRIV पूर्ण,
	अणु AUDIT_ADD,		NETLINK_AUDIT_SOCKET__NLMSG_WRITE    पूर्ण,
	अणु AUDIT_DEL,		NETLINK_AUDIT_SOCKET__NLMSG_WRITE    पूर्ण,
	अणु AUDIT_LIST_RULES,	NETLINK_AUDIT_SOCKET__NLMSG_READPRIV पूर्ण,
	अणु AUDIT_ADD_RULE,	NETLINK_AUDIT_SOCKET__NLMSG_WRITE    पूर्ण,
	अणु AUDIT_DEL_RULE,	NETLINK_AUDIT_SOCKET__NLMSG_WRITE    पूर्ण,
	अणु AUDIT_USER,		NETLINK_AUDIT_SOCKET__NLMSG_RELAY    पूर्ण,
	अणु AUDIT_SIGNAL_INFO,	NETLINK_AUDIT_SOCKET__NLMSG_READ     पूर्ण,
	अणु AUDIT_TRIM,		NETLINK_AUDIT_SOCKET__NLMSG_WRITE    पूर्ण,
	अणु AUDIT_MAKE_EQUIV,	NETLINK_AUDIT_SOCKET__NLMSG_WRITE    पूर्ण,
	अणु AUDIT_TTY_GET,	NETLINK_AUDIT_SOCKET__NLMSG_READ     पूर्ण,
	अणु AUDIT_TTY_SET,	NETLINK_AUDIT_SOCKET__NLMSG_TTY_AUDIT	पूर्ण,
	अणु AUDIT_GET_FEATURE,	NETLINK_AUDIT_SOCKET__NLMSG_READ     पूर्ण,
	अणु AUDIT_SET_FEATURE,	NETLINK_AUDIT_SOCKET__NLMSG_WRITE    पूर्ण,
पूर्ण;


अटल पूर्णांक nlmsg_perm(u16 nlmsg_type, u32 *perm, स्थिर काष्ठा nlmsg_perm *tab, माप_प्रकार tअसलize)
अणु
	पूर्णांक i, err = -EINVAL;

	क्रम (i = 0; i < tअसलize/माप(काष्ठा nlmsg_perm); i++)
		अगर (nlmsg_type == tab[i].nlmsg_type) अणु
			*perm = tab[i].perm;
			err = 0;
			अवरोध;
		पूर्ण

	वापस err;
पूर्ण

पूर्णांक selinux_nlmsg_lookup(u16 sclass, u16 nlmsg_type, u32 *perm)
अणु
	पूर्णांक err = 0;

	चयन (sclass) अणु
	हाल SECCLASS_NETLINK_ROUTE_SOCKET:
		/* RTM_MAX always poपूर्णांकs to RTM_SETxxxx, ie RTM_NEWxxx + 3.
		 * If the BUILD_BUG_ON() below fails you must update the
		 * काष्ठाures at the top of this file with the new mappings
		 * beक्रमe updating the BUILD_BUG_ON() macro!
		 */
		BUILD_BUG_ON(RTM_MAX != (RTM_NEWNEXTHOPBUCKET + 3));
		err = nlmsg_perm(nlmsg_type, perm, nlmsg_route_perms,
				 माप(nlmsg_route_perms));
		अवरोध;

	हाल SECCLASS_NETLINK_TCPDIAG_SOCKET:
		err = nlmsg_perm(nlmsg_type, perm, nlmsg_tcpdiag_perms,
				 माप(nlmsg_tcpdiag_perms));
		अवरोध;

	हाल SECCLASS_NETLINK_XFRM_SOCKET:
		/* If the BUILD_BUG_ON() below fails you must update the
		 * काष्ठाures at the top of this file with the new mappings
		 * beक्रमe updating the BUILD_BUG_ON() macro!
		 */
		BUILD_BUG_ON(XFRM_MSG_MAX != XFRM_MSG_MAPPING);
		err = nlmsg_perm(nlmsg_type, perm, nlmsg_xfrm_perms,
				 माप(nlmsg_xfrm_perms));
		अवरोध;

	हाल SECCLASS_NETLINK_AUDIT_SOCKET:
		अगर ((nlmsg_type >= AUDIT_FIRST_USER_MSG &&
		     nlmsg_type <= AUDIT_LAST_USER_MSG) ||
		    (nlmsg_type >= AUDIT_FIRST_USER_MSG2 &&
		     nlmsg_type <= AUDIT_LAST_USER_MSG2)) अणु
			*perm = NETLINK_AUDIT_SOCKET__NLMSG_RELAY;
		पूर्ण अन्यथा अणु
			err = nlmsg_perm(nlmsg_type, perm, nlmsg_audit_perms,
					 माप(nlmsg_audit_perms));
		पूर्ण
		अवरोध;

	/* No messaging from userspace, or class unknown/unhandled */
	शेष:
		err = -ENOENT;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण
