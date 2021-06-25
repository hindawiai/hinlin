<शैली गुरु>
/*
 *   DNS Resolver upcall management क्रम CIFS DFS and AFS
 *   Handles host name to IP address resolution and DNS query क्रम AFSDB RR.
 *
 *   Copyright (c) International Business Machines  Corp., 2008
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *              Wang Lei (wang840925@gmail.com)
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#अगर_अघोषित _LINUX_DNS_RESOLVER_H
#घोषणा _LINUX_DNS_RESOLVER_H

#समावेश <uapi/linux/dns_resolver.h>

काष्ठा net;
बाह्य पूर्णांक dns_query(काष्ठा net *net, स्थिर अक्षर *type, स्थिर अक्षर *name, माप_प्रकार namelen,
		     स्थिर अक्षर *options, अक्षर **_result, समय64_t *_expiry,
		     bool invalidate);

#पूर्ण_अगर /* _LINUX_DNS_RESOLVER_H */
