<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/kernel.h>
#समावेश <linux/key.h>
#समावेश "common.h"

पूर्णांक load_certअगरicate_list(स्थिर u8 cert_list[],
			  स्थिर अचिन्हित दीर्घ list_size,
			  स्थिर काष्ठा key *keyring)
अणु
	key_ref_t key;
	स्थिर u8 *p, *end;
	माप_प्रकार plen;

	p = cert_list;
	end = p + list_size;
	जबतक (p < end) अणु
		/* Each cert begins with an ASN.1 SEQUENCE tag and must be more
		 * than 256 bytes in size.
		 */
		अगर (end - p < 4)
			जाओ करोdgy_cert;
		अगर (p[0] != 0x30 &&
		    p[1] != 0x82)
			जाओ करोdgy_cert;
		plen = (p[2] << 8) | p[3];
		plen += 4;
		अगर (plen > end - p)
			जाओ करोdgy_cert;

		key = key_create_or_update(make_key_ref(keyring, 1),
					   "asymmetric",
					   शून्य,
					   p,
					   plen,
					   ((KEY_POS_ALL & ~KEY_POS_SETATTR) |
					   KEY_USR_VIEW | KEY_USR_READ),
					   KEY_ALLOC_NOT_IN_QUOTA |
					   KEY_ALLOC_BUILT_IN |
					   KEY_ALLOC_BYPASS_RESTRICTION);
		अगर (IS_ERR(key)) अणु
			pr_err("Problem loading in-kernel X.509 certificate (%ld)\n",
			       PTR_ERR(key));
		पूर्ण अन्यथा अणु
			pr_notice("Loaded X.509 cert '%s'\n",
				  key_ref_to_ptr(key)->description);
			key_ref_put(key);
		पूर्ण
		p += plen;
	पूर्ण

	वापस 0;

करोdgy_cert:
	pr_err("Problem parsing in-kernel X.509 certificate list\n");
	वापस 0;
पूर्ण
