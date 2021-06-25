<शैली गुरु>
/* Key type used to cache DNS lookups made by the kernel
 *
 * See Documentation/networking/dns_resolver.rst
 *
 *   Copyright (c) 2007 Igor Mammeकरोv
 *   Author(s): Igor Mammeकरोv (niallain@gmail.com)
 *              Steve French (sfrench@us.ibm.com)
 *              Wang Lei (wang840925@gmail.com)
 *		David Howells (dhowells@redhat.com)
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
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/keyctl.h>
#समावेश <linux/err.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/dns_resolver.h>
#समावेश <keys/dns_resolver-type.h>
#समावेश <keys/user-type.h>
#समावेश "internal.h"

MODULE_DESCRIPTION("DNS Resolver");
MODULE_AUTHOR("Wang Lei");
MODULE_LICENSE("GPL");

अचिन्हित पूर्णांक dns_resolver_debug;
module_param_named(debug, dns_resolver_debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "DNS Resolver debugging mask");

स्थिर काष्ठा cred *dns_resolver_cache;

#घोषणा	DNS_ERRORNO_OPTION	"dnserror"

/*
 * Preparse instantiation data क्रम a dns_resolver key.
 *
 * For normal hostname lookups, the data must be a NUL-terminated string, with
 * the NUL अक्षर accounted in datalen.
 *
 * If the data contains a '#' अक्षरacters, then we take the clause after each
 * one to be an option of the क्रमm 'key=value'.  The actual data of पूर्णांकerest is
 * the string leading up to the first '#'.  For instance:
 *
 *        "ip1,ip2,...#foo=bar"
 *
 * For server list requests, the data must begin with a NUL अक्षर and be
 * followed by a byte indicating the version of the data क्रमmat.  Version 1
 * looks something like (note this is packed):
 *
 *	u8      Non-string marker (ie. 0)
 *	u8	Content (DNS_PAYLOAD_IS_*)
 *	u8	Version (e.g. 1)
 *	u8	Source of server list
 *	u8	Lookup status of server list
 *	u8	Number of servers
 *	क्रमeach-server अणु
 *		__le16	Name length
 *		__le16	Priority (as per SRV record, low first)
 *		__le16	Weight (as per SRV record, higher first)
 *		__le16	Port
 *		u8	Source of address list
 *		u8	Lookup status of address list
 *		u8	Protocol (DNS_SERVER_PROTOCOL_*)
 *		u8	Number of addresses
 *		अक्षर[]	Name (not NUL-terminated)
 *		क्रमeach-address अणु
 *			u8		Family (DNS_ADDRESS_IS_*)
 *			जोड़ अणु
 *				u8[4]	ipv4_addr
 *				u8[16]	ipv6_addr
 *			पूर्ण
 *		पूर्ण
 *	पूर्ण
 *
 */
अटल पूर्णांक
dns_resolver_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	स्थिर काष्ठा dns_payload_header *bin;
	काष्ठा user_key_payload *upayload;
	अचिन्हित दीर्घ dत्रुटि_सं;
	पूर्णांक ret;
	पूर्णांक datalen = prep->datalen, result_len = 0;
	स्थिर अक्षर *data = prep->data, *end, *opt;

	अगर (datalen <= 1 || !data)
		वापस -EINVAL;

	अगर (data[0] == 0) अणु
		/* It may be a server list. */
		अगर (datalen <= माप(*bin))
			वापस -EINVAL;

		bin = (स्थिर काष्ठा dns_payload_header *)data;
		kenter("[%u,%u],%u", bin->content, bin->version, datalen);
		अगर (bin->content != DNS_PAYLOAD_IS_SERVER_LIST) अणु
			pr_warn_ratelimited(
				"dns_resolver: Unsupported content type (%u)\n",
				bin->content);
			वापस -EINVAL;
		पूर्ण

		अगर (bin->version != 1) अणु
			pr_warn_ratelimited(
				"dns_resolver: Unsupported server list version (%u)\n",
				bin->version);
			वापस -EINVAL;
		पूर्ण

		result_len = datalen;
		जाओ store_result;
	पूर्ण

	kenter("'%*.*s',%u", datalen, datalen, data, datalen);

	अगर (!data || data[datalen - 1] != '\0')
		वापस -EINVAL;
	datalen--;

	/* deal with any options embedded in the data */
	end = data + datalen;
	opt = स_प्रथम(data, '#', datalen);
	अगर (!opt) अणु
		/* no options: the entire data is the result */
		kdebug("no options");
		result_len = datalen;
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *next_opt;

		result_len = opt - data;
		opt++;
		kdebug("options: '%s'", opt);
		करो अणु
			पूर्णांक opt_len, opt_nlen;
			स्थिर अक्षर *eq;
			अक्षर optval[128];

			next_opt = स_प्रथम(opt, '#', end - opt) ?: end;
			opt_len = next_opt - opt;
			अगर (opt_len <= 0 || opt_len > माप(optval)) अणु
				pr_warn_ratelimited("Invalid option length (%d) for dns_resolver key\n",
						    opt_len);
				वापस -EINVAL;
			पूर्ण

			eq = स_प्रथम(opt, '=', opt_len);
			अगर (eq) अणु
				opt_nlen = eq - opt;
				eq++;
				स_नकल(optval, eq, next_opt - eq);
				optval[next_opt - eq] = '\0';
			पूर्ण अन्यथा अणु
				opt_nlen = opt_len;
				optval[0] = '\0';
			पूर्ण

			kdebug("option '%*.*s' val '%s'",
			       opt_nlen, opt_nlen, opt, optval);

			/* see अगर it's an error number representing a DNS error
			 * that's to be recorded as the result in this key */
			अगर (opt_nlen == माप(DNS_ERRORNO_OPTION) - 1 &&
			    स_भेद(opt, DNS_ERRORNO_OPTION, opt_nlen) == 0) अणु
				kdebug("dns error number option");

				ret = kम_से_अदीर्घ(optval, 10, &dत्रुटि_सं);
				अगर (ret < 0)
					जाओ bad_option_value;

				अगर (dत्रुटि_सं < 1 || dत्रुटि_सं > 511)
					जाओ bad_option_value;

				kdebug("dns error no. = %lu", dत्रुटि_सं);
				prep->payload.data[dns_key_error] = ERR_PTR(-dत्रुटि_सं);
				जारी;
			पूर्ण

		bad_option_value:
			pr_warn_ratelimited("Option '%*.*s' to dns_resolver key: bad/missing value\n",
					    opt_nlen, opt_nlen, opt);
			वापस -EINVAL;
		पूर्ण जबतक (opt = next_opt + 1, opt < end);
	पूर्ण

	/* करोn't cache the result if we're caching an error saying there's no
	 * result */
	अगर (prep->payload.data[dns_key_error]) अणु
		kleave(" = 0 [h_error %ld]", PTR_ERR(prep->payload.data[dns_key_error]));
		वापस 0;
	पूर्ण

store_result:
	kdebug("store result");
	prep->quotalen = result_len;

	upayload = kदो_स्मृति(माप(*upayload) + result_len + 1, GFP_KERNEL);
	अगर (!upayload) अणु
		kleave(" = -ENOMEM");
		वापस -ENOMEM;
	पूर्ण

	upayload->datalen = result_len;
	स_नकल(upayload->data, data, result_len);
	upayload->data[result_len] = '\0';

	prep->payload.data[dns_key_data] = upayload;
	kleave(" = 0");
	वापस 0;
पूर्ण

/*
 * Clean up the preparse data
 */
अटल व्योम dns_resolver_मुक्त_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	pr_devel("==>%s()\n", __func__);

	kमुक्त(prep->payload.data[dns_key_data]);
पूर्ण

/*
 * The description is of the क्रमm "[<type>:]<domain_name>"
 *
 * The करोमुख्य name may be a simple name or an असलolute करोमुख्य name (which
 * should end with a period).  The करोमुख्य name is हाल-independent.
 */
अटल bool dns_resolver_cmp(स्थिर काष्ठा key *key,
			     स्थिर काष्ठा key_match_data *match_data)
अणु
	पूर्णांक slen, dlen, ret = 0;
	स्थिर अक्षर *src = key->description, *dsp = match_data->raw_data;

	kenter("%s,%s", src, dsp);

	अगर (!src || !dsp)
		जाओ no_match;

	अगर (strहालcmp(src, dsp) == 0)
		जाओ matched;

	slen = म_माप(src);
	dlen = म_माप(dsp);
	अगर (slen <= 0 || dlen <= 0)
		जाओ no_match;
	अगर (src[slen - 1] == '.')
		slen--;
	अगर (dsp[dlen - 1] == '.')
		dlen--;
	अगर (slen != dlen || strnहालcmp(src, dsp, slen) != 0)
		जाओ no_match;

matched:
	ret = 1;
no_match:
	kleave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Preparse the match criterion.
 */
अटल पूर्णांक dns_resolver_match_preparse(काष्ठा key_match_data *match_data)
अणु
	match_data->lookup_type = KEYRING_SEARCH_LOOKUP_ITERATE;
	match_data->cmp = dns_resolver_cmp;
	वापस 0;
पूर्ण

/*
 * Describe a DNS key
 */
अटल व्योम dns_resolver_describe(स्थिर काष्ठा key *key, काष्ठा seq_file *m)
अणु
	seq_माला_दो(m, key->description);
	अगर (key_is_positive(key)) अणु
		पूर्णांक err = PTR_ERR(key->payload.data[dns_key_error]);

		अगर (err)
			seq_म_लिखो(m, ": %d", err);
		अन्यथा
			seq_म_लिखो(m, ": %u", key->datalen);
	पूर्ण
पूर्ण

/*
 * पढ़ो the DNS data
 * - the key's semaphore is पढ़ो-locked
 */
अटल दीर्घ dns_resolver_पढ़ो(स्थिर काष्ठा key *key,
			      अक्षर *buffer, माप_प्रकार buflen)
अणु
	पूर्णांक err = PTR_ERR(key->payload.data[dns_key_error]);

	अगर (err)
		वापस err;

	वापस user_पढ़ो(key, buffer, buflen);
पूर्ण

काष्ठा key_type key_type_dns_resolver = अणु
	.name		= "dns_resolver",
	.flags		= KEY_TYPE_NET_DOMAIN,
	.preparse	= dns_resolver_preparse,
	.मुक्त_preparse	= dns_resolver_मुक्त_preparse,
	.instantiate	= generic_key_instantiate,
	.match_preparse	= dns_resolver_match_preparse,
	.revoke		= user_revoke,
	.destroy	= user_destroy,
	.describe	= dns_resolver_describe,
	.पढ़ो		= dns_resolver_पढ़ो,
पूर्ण;

अटल पूर्णांक __init init_dns_resolver(व्योम)
अणु
	काष्ठा cred *cred;
	काष्ठा key *keyring;
	पूर्णांक ret;

	/* create an override credential set with a special thपढ़ो keyring in
	 * which DNS requests are cached
	 *
	 * this is used to prevent malicious redirections from being installed
	 * with add_key().
	 */
	cred = prepare_kernel_cred(शून्य);
	अगर (!cred)
		वापस -ENOMEM;

	keyring = keyring_alloc(".dns_resolver",
				GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, cred,
				(KEY_POS_ALL & ~KEY_POS_SETATTR) |
				KEY_USR_VIEW | KEY_USR_READ,
				KEY_ALLOC_NOT_IN_QUOTA, शून्य, शून्य);
	अगर (IS_ERR(keyring)) अणु
		ret = PTR_ERR(keyring);
		जाओ failed_put_cred;
	पूर्ण

	ret = रेजिस्टर_key_type(&key_type_dns_resolver);
	अगर (ret < 0)
		जाओ failed_put_key;

	/* inकाष्ठा request_key() to use this special keyring as a cache क्रम
	 * the results it looks up */
	set_bit(KEY_FLAG_ROOT_CAN_CLEAR, &keyring->flags);
	cred->thपढ़ो_keyring = keyring;
	cred->jit_keyring = KEY_REQKEY_DEFL_THREAD_KEYRING;
	dns_resolver_cache = cred;

	kdebug("DNS resolver keyring: %d\n", key_serial(keyring));
	वापस 0;

failed_put_key:
	key_put(keyring);
failed_put_cred:
	put_cred(cred);
	वापस ret;
पूर्ण

अटल व्योम __निकास निकास_dns_resolver(व्योम)
अणु
	key_revoke(dns_resolver_cache->thपढ़ो_keyring);
	unरेजिस्टर_key_type(&key_type_dns_resolver);
	put_cred(dns_resolver_cache);
पूर्ण

module_init(init_dns_resolver)
module_निकास(निकास_dns_resolver)
MODULE_LICENSE("GPL");
