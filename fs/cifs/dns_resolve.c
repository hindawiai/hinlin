<शैली गुरु>
/*
 *  fs/cअगरs/dns_resolve.c
 *
 *   Copyright (c) 2007 Igor Mammeकरोv
 *   Author(s): Igor Mammeकरोv (niallain@gmail.com)
 *              Steve French (sfrench@us.ibm.com)
 *              Wang Lei (wang840925@gmail.com)
 *		David Howells (dhowells@redhat.com)
 *
 *   Contains the CIFS DFS upcall routines used क्रम hostname to
 *   IP address translation.
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

#समावेश <linux/slab.h>
#समावेश <linux/dns_resolver.h>
#समावेश "dns_resolve.h"
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"

/**
 * dns_resolve_server_name_to_ip - Resolve UNC server name to ip address.
 * @unc: UNC path specअगरying the server (with '/' as delimiter)
 * @ip_addr: Where to वापस the IP address.
 *
 * The IP address will be वापसed in string क्रमm, and the caller is
 * responsible क्रम मुक्तing it.
 *
 * Returns length of result on success, -ve on error.
 */
पूर्णांक
dns_resolve_server_name_to_ip(स्थिर अक्षर *unc, अक्षर **ip_addr)
अणु
	काष्ठा sockaddr_storage ss;
	स्थिर अक्षर *hostname, *sep;
	अक्षर *name;
	पूर्णांक len, rc;

	अगर (!ip_addr || !unc)
		वापस -EINVAL;

	len = म_माप(unc);
	अगर (len < 3) अणु
		cअगरs_dbg(FYI, "%s: unc is too short: %s\n", __func__, unc);
		वापस -EINVAL;
	पूर्ण

	/* Discount leading slashes क्रम cअगरs */
	len -= 2;
	hostname = unc + 2;

	/* Search क्रम server name delimiter */
	sep = स_प्रथम(hostname, '/', len);
	अगर (sep)
		len = sep - hostname;
	अन्यथा
		cअगरs_dbg(FYI, "%s: probably server name is whole unc: %s\n",
			 __func__, unc);

	/* Try to पूर्णांकerpret hostname as an IPv4 or IPv6 address */
	rc = cअगरs_convert_address((काष्ठा sockaddr *)&ss, hostname, len);
	अगर (rc > 0)
		जाओ name_is_IP_address;

	/* Perक्रमm the upcall */
	rc = dns_query(current->nsproxy->net_ns, शून्य, hostname, len,
		       शून्य, ip_addr, शून्य, false);
	अगर (rc < 0)
		cअगरs_dbg(FYI, "%s: unable to resolve: %*.*s\n",
			 __func__, len, len, hostname);
	अन्यथा
		cअगरs_dbg(FYI, "%s: resolved: %*.*s to %s\n",
			 __func__, len, len, hostname, *ip_addr);
	वापस rc;

name_is_IP_address:
	name = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;
	स_नकल(name, hostname, len);
	name[len] = 0;
	cअगरs_dbg(FYI, "%s: unc is IP, skipping dns upcall: %s\n",
		 __func__, name);
	*ip_addr = name;
	वापस 0;
पूर्ण
