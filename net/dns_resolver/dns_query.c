<शैली गुरु>
/* Upcall routine, deचिन्हित to work as a key type and working through
 * /sbin/request-key to contact userspace when handling DNS queries.
 *
 * See Documentation/networking/dns_resolver.rst
 *
 *   Copyright (c) 2007 Igor Mammeकरोv
 *   Author(s): Igor Mammeकरोv (niallain@gmail.com)
 *              Steve French (sfrench@us.ibm.com)
 *              Wang Lei (wang840925@gmail.com)
 *		David Howells (dhowells@redhat.com)
 *
 *   The upcall wrapper used to make an arbitrary DNS query.
 *
 *   This function requires the appropriate userspace tool dns.upcall to be
 *   installed and something like the following lines should be added to the
 *   /etc/request-key.conf file:
 *
 *	create dns_resolver * * /sbin/dns.upcall %k
 *
 *   For example to use this module to query AFSDB RR:
 *
 *	create dns_resolver afsdb:* * /sbin/dns.afsdb %k
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
 *   aदीर्घ with this library; अगर not, see <http://www.gnu.org/licenses/>.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/dns_resolver.h>
#समावेश <linux/err.h>
#समावेश <net/net_namespace.h>

#समावेश <keys/dns_resolver-type.h>
#समावेश <keys/user-type.h>

#समावेश "internal.h"

/**
 * dns_query - Query the DNS
 * @net: The network namespace to operate in.
 * @type: Query type (or शून्य क्रम straight host->IP lookup)
 * @name: Name to look up
 * @namelen: Length of name
 * @options: Request options (or शून्य अगर no options)
 * @_result: Where to place the वापसed data (or शून्य)
 * @_expiry: Where to store the result expiry समय (or शून्य)
 * @invalidate: Always invalidate the key after use
 *
 * The data will be वापसed in the poपूर्णांकer at *result, अगर provided, and the
 * caller is responsible क्रम मुक्तing it.
 *
 * The description should be of the क्रमm "[<query_type>:]<domain_name>", and
 * the options need to be appropriate क्रम the query type requested.  If no
 * query_type is given, then the query is a straight hostname to IP address
 * lookup.
 *
 * The DNS resolution lookup is perक्रमmed by upcalling to userspace by way of
 * requesting a key of type dns_resolver.
 *
 * Returns the size of the result on success, -ve error code otherwise.
 */
पूर्णांक dns_query(काष्ठा net *net,
	      स्थिर अक्षर *type, स्थिर अक्षर *name, माप_प्रकार namelen,
	      स्थिर अक्षर *options, अक्षर **_result, समय64_t *_expiry,
	      bool invalidate)
अणु
	काष्ठा key *rkey;
	काष्ठा user_key_payload *upayload;
	स्थिर काष्ठा cred *saved_cred;
	माप_प्रकार typelen, desclen;
	अक्षर *desc, *cp;
	पूर्णांक ret, len;

	kenter("%s,%*.*s,%zu,%s",
	       type, (पूर्णांक)namelen, (पूर्णांक)namelen, name, namelen, options);

	अगर (!name || namelen == 0)
		वापस -EINVAL;

	/* स्थिरruct the query key description as "[<type>:]<name>" */
	typelen = 0;
	desclen = 0;
	अगर (type) अणु
		typelen = म_माप(type);
		अगर (typelen < 1)
			वापस -EINVAL;
		desclen += typelen + 1;
	पूर्ण

	अगर (namelen < 3 || namelen > 255)
		वापस -EINVAL;
	desclen += namelen + 1;

	desc = kदो_स्मृति(desclen, GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	cp = desc;
	अगर (type) अणु
		स_नकल(cp, type, typelen);
		cp += typelen;
		*cp++ = ':';
	पूर्ण
	स_नकल(cp, name, namelen);
	cp += namelen;
	*cp = '\0';

	अगर (!options)
		options = "";
	kdebug("call request_key(,%s,%s)", desc, options);

	/* make the upcall, using special credentials to prevent the use of
	 * add_key() to preinstall malicious redirections
	 */
	saved_cred = override_creds(dns_resolver_cache);
	rkey = request_key_net(&key_type_dns_resolver, desc, net, options);
	revert_creds(saved_cred);
	kमुक्त(desc);
	अगर (IS_ERR(rkey)) अणु
		ret = PTR_ERR(rkey);
		जाओ out;
	पूर्ण

	करोwn_पढ़ो(&rkey->sem);
	set_bit(KEY_FLAG_ROOT_CAN_INVAL, &rkey->flags);
	rkey->perm |= KEY_USR_VIEW;

	ret = key_validate(rkey);
	अगर (ret < 0)
		जाओ put;

	/* If the DNS server gave an error, वापस that to the caller */
	ret = PTR_ERR(rkey->payload.data[dns_key_error]);
	अगर (ret)
		जाओ put;

	upayload = user_key_payload_locked(rkey);
	len = upayload->datalen;

	अगर (_result) अणु
		ret = -ENOMEM;
		*_result = kmemdup_nul(upayload->data, len, GFP_KERNEL);
		अगर (!*_result)
			जाओ put;
	पूर्ण

	अगर (_expiry)
		*_expiry = rkey->expiry;

	ret = len;
put:
	up_पढ़ो(&rkey->sem);
	अगर (invalidate)
		key_invalidate(rkey);
	key_put(rkey);
out:
	kleave(" = %d", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dns_query);
