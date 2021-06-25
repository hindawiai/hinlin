<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NetLabel Kernel API
 *
 * This file defines the kernel API क्रम the NetLabel प्रणाली.  The NetLabel
 * प्रणाली manages अटल and dynamic label mappings क्रम network protocols such
 * as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006, 2008
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/audit.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/netlabel.h>
#समावेश <net/cipso_ipv4.h>
#समावेश <net/calipso.h>
#समावेश <यंत्र/bug.h>
#समावेश <linux/atomic.h>

#समावेश "netlabel_domainhash.h"
#समावेश "netlabel_unlabeled.h"
#समावेश "netlabel_cipso_v4.h"
#समावेश "netlabel_calipso.h"
#समावेश "netlabel_user.h"
#समावेश "netlabel_mgmt.h"
#समावेश "netlabel_addrlist.h"

/*
 * Configuration Functions
 */

/**
 * netlbl_cfg_map_del - Remove a NetLabel/LSM करोमुख्य mapping
 * @करोमुख्य: the करोमुख्य mapping to हटाओ
 * @family: address family
 * @addr: IP address
 * @mask: IP address mask
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes a NetLabel/LSM करोमुख्य mapping.  A @करोमुख्य value of शून्य causes the
 * शेष करोमुख्य mapping to be हटाओd.  Returns zero on success, negative
 * values on failure.
 *
 */
पूर्णांक netlbl_cfg_map_del(स्थिर अक्षर *करोमुख्य,
		       u16 family,
		       स्थिर व्योम *addr,
		       स्थिर व्योम *mask,
		       काष्ठा netlbl_audit *audit_info)
अणु
	अगर (addr == शून्य && mask == शून्य) अणु
		वापस netlbl_करोmhsh_हटाओ(करोमुख्य, family, audit_info);
	पूर्ण अन्यथा अगर (addr != शून्य && mask != शून्य) अणु
		चयन (family) अणु
		हाल AF_INET:
			वापस netlbl_करोmhsh_हटाओ_af4(करोमुख्य, addr, mask,
							audit_info);
#अगर IS_ENABLED(CONFIG_IPV6)
		हाल AF_INET6:
			वापस netlbl_करोmhsh_हटाओ_af6(करोमुख्य, addr, mask,
							audit_info);
#पूर्ण_अगर /* IPv6 */
		शेष:
			वापस -EPFNOSUPPORT;
		पूर्ण
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

/**
 * netlbl_cfg_unlbl_map_add - Add a new unlabeled mapping
 * @करोमुख्य: the करोमुख्य mapping to add
 * @family: address family
 * @addr: IP address
 * @mask: IP address mask
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Adds a new unlabeled NetLabel/LSM करोमुख्य mapping.  A @करोमुख्य value of शून्य
 * causes a new शेष करोमुख्य mapping to be added.  Returns zero on success,
 * negative values on failure.
 *
 */
पूर्णांक netlbl_cfg_unlbl_map_add(स्थिर अक्षर *करोमुख्य,
			     u16 family,
			     स्थिर व्योम *addr,
			     स्थिर व्योम *mask,
			     काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = -ENOMEM;
	काष्ठा netlbl_करोm_map *entry;
	काष्ठा netlbl_करोmaddr_map *addrmap = शून्य;
	काष्ठा netlbl_करोmaddr4_map *map4 = शून्य;
	काष्ठा netlbl_करोmaddr6_map *map6 = शून्य;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (entry == शून्य)
		वापस -ENOMEM;
	अगर (करोमुख्य != शून्य) अणु
		entry->करोमुख्य = kstrdup(करोमुख्य, GFP_ATOMIC);
		अगर (entry->करोमुख्य == शून्य)
			जाओ cfg_unlbl_map_add_failure;
	पूर्ण
	entry->family = family;

	अगर (addr == शून्य && mask == शून्य)
		entry->def.type = NETLBL_NLTYPE_UNLABELED;
	अन्यथा अगर (addr != शून्य && mask != शून्य) अणु
		addrmap = kzalloc(माप(*addrmap), GFP_ATOMIC);
		अगर (addrmap == शून्य)
			जाओ cfg_unlbl_map_add_failure;
		INIT_LIST_HEAD(&addrmap->list4);
		INIT_LIST_HEAD(&addrmap->list6);

		चयन (family) अणु
		हाल AF_INET: अणु
			स्थिर काष्ठा in_addr *addr4 = addr;
			स्थिर काष्ठा in_addr *mask4 = mask;
			map4 = kzalloc(माप(*map4), GFP_ATOMIC);
			अगर (map4 == शून्य)
				जाओ cfg_unlbl_map_add_failure;
			map4->def.type = NETLBL_NLTYPE_UNLABELED;
			map4->list.addr = addr4->s_addr & mask4->s_addr;
			map4->list.mask = mask4->s_addr;
			map4->list.valid = 1;
			ret_val = netlbl_af4list_add(&map4->list,
						     &addrmap->list4);
			अगर (ret_val != 0)
				जाओ cfg_unlbl_map_add_failure;
			अवरोध;
			पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		हाल AF_INET6: अणु
			स्थिर काष्ठा in6_addr *addr6 = addr;
			स्थिर काष्ठा in6_addr *mask6 = mask;
			map6 = kzalloc(माप(*map6), GFP_ATOMIC);
			अगर (map6 == शून्य)
				जाओ cfg_unlbl_map_add_failure;
			map6->def.type = NETLBL_NLTYPE_UNLABELED;
			map6->list.addr = *addr6;
			map6->list.addr.s6_addr32[0] &= mask6->s6_addr32[0];
			map6->list.addr.s6_addr32[1] &= mask6->s6_addr32[1];
			map6->list.addr.s6_addr32[2] &= mask6->s6_addr32[2];
			map6->list.addr.s6_addr32[3] &= mask6->s6_addr32[3];
			map6->list.mask = *mask6;
			map6->list.valid = 1;
			ret_val = netlbl_af6list_add(&map6->list,
						     &addrmap->list6);
			अगर (ret_val != 0)
				जाओ cfg_unlbl_map_add_failure;
			अवरोध;
			पूर्ण
#पूर्ण_अगर /* IPv6 */
		शेष:
			जाओ cfg_unlbl_map_add_failure;
		पूर्ण

		entry->def.addrsel = addrmap;
		entry->def.type = NETLBL_NLTYPE_ADDRSELECT;
	पूर्ण अन्यथा अणु
		ret_val = -EINVAL;
		जाओ cfg_unlbl_map_add_failure;
	पूर्ण

	ret_val = netlbl_करोmhsh_add(entry, audit_info);
	अगर (ret_val != 0)
		जाओ cfg_unlbl_map_add_failure;

	वापस 0;

cfg_unlbl_map_add_failure:
	kमुक्त(entry->करोमुख्य);
	kमुक्त(entry);
	kमुक्त(addrmap);
	kमुक्त(map4);
	kमुक्त(map6);
	वापस ret_val;
पूर्ण


/**
 * netlbl_cfg_unlbl_अटल_add - Adds a new अटल label
 * @net: network namespace
 * @dev_name: पूर्णांकerface name
 * @addr: IP address in network byte order (काष्ठा in[6]_addr)
 * @mask: address mask in network byte order (काष्ठा in[6]_addr)
 * @family: address family
 * @secid: LSM secid value क्रम the entry
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Adds a new NetLabel अटल label to be used when protocol provided labels
 * are not present on incoming traffic.  If @dev_name is शून्य then the शेष
 * पूर्णांकerface will be used.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक netlbl_cfg_unlbl_अटल_add(काष्ठा net *net,
				स्थिर अक्षर *dev_name,
				स्थिर व्योम *addr,
				स्थिर व्योम *mask,
				u16 family,
				u32 secid,
				काष्ठा netlbl_audit *audit_info)
अणु
	u32 addr_len;

	चयन (family) अणु
	हाल AF_INET:
		addr_len = माप(काष्ठा in_addr);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		addr_len = माप(काष्ठा in6_addr);
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	शेष:
		वापस -EPFNOSUPPORT;
	पूर्ण

	वापस netlbl_unlhsh_add(net,
				 dev_name, addr, mask, addr_len,
				 secid, audit_info);
पूर्ण

/**
 * netlbl_cfg_unlbl_अटल_del - Removes an existing अटल label
 * @net: network namespace
 * @dev_name: पूर्णांकerface name
 * @addr: IP address in network byte order (काष्ठा in[6]_addr)
 * @mask: address mask in network byte order (काष्ठा in[6]_addr)
 * @family: address family
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Removes an existing NetLabel अटल label used when protocol provided labels
 * are not present on incoming traffic.  If @dev_name is शून्य then the शेष
 * पूर्णांकerface will be used.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक netlbl_cfg_unlbl_अटल_del(काष्ठा net *net,
				स्थिर अक्षर *dev_name,
				स्थिर व्योम *addr,
				स्थिर व्योम *mask,
				u16 family,
				काष्ठा netlbl_audit *audit_info)
अणु
	u32 addr_len;

	चयन (family) अणु
	हाल AF_INET:
		addr_len = माप(काष्ठा in_addr);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		addr_len = माप(काष्ठा in6_addr);
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	शेष:
		वापस -EPFNOSUPPORT;
	पूर्ण

	वापस netlbl_unlhsh_हटाओ(net,
				    dev_name, addr, mask, addr_len,
				    audit_info);
पूर्ण

/**
 * netlbl_cfg_cipsov4_add - Add a new CIPSOv4 DOI definition
 * @करोi_def: CIPSO DOI definition
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Add a new CIPSO DOI definition as defined by @करोi_def.  Returns zero on
 * success and negative values on failure.
 *
 */
पूर्णांक netlbl_cfg_cipsov4_add(काष्ठा cipso_v4_करोi *करोi_def,
			   काष्ठा netlbl_audit *audit_info)
अणु
	वापस cipso_v4_करोi_add(करोi_def, audit_info);
पूर्ण

/**
 * netlbl_cfg_cipsov4_del - Remove an existing CIPSOv4 DOI definition
 * @करोi: CIPSO DOI
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Remove an existing CIPSO DOI definition matching @करोi.  Returns zero on
 * success and negative values on failure.
 *
 */
व्योम netlbl_cfg_cipsov4_del(u32 करोi, काष्ठा netlbl_audit *audit_info)
अणु
	cipso_v4_करोi_हटाओ(करोi, audit_info);
पूर्ण

/**
 * netlbl_cfg_cipsov4_map_add - Add a new CIPSOv4 DOI mapping
 * @करोi: the CIPSO DOI
 * @करोमुख्य: the करोमुख्य mapping to add
 * @addr: IP address
 * @mask: IP address mask
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Add a new NetLabel/LSM करोमुख्य mapping क्रम the given CIPSO DOI to the NetLabel
 * subप्रणाली.  A @करोमुख्य value of शून्य adds a new शेष करोमुख्य mapping.
 * Returns zero on success, negative values on failure.
 *
 */
पूर्णांक netlbl_cfg_cipsov4_map_add(u32 करोi,
			       स्थिर अक्षर *करोमुख्य,
			       स्थिर काष्ठा in_addr *addr,
			       स्थिर काष्ठा in_addr *mask,
			       काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = -ENOMEM;
	काष्ठा cipso_v4_करोi *करोi_def;
	काष्ठा netlbl_करोm_map *entry;
	काष्ठा netlbl_करोmaddr_map *addrmap = शून्य;
	काष्ठा netlbl_करोmaddr4_map *addrinfo = शून्य;

	करोi_def = cipso_v4_करोi_getdef(करोi);
	अगर (करोi_def == शून्य)
		वापस -ENOENT;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (entry == शून्य)
		जाओ out_entry;
	entry->family = AF_INET;
	अगर (करोमुख्य != शून्य) अणु
		entry->करोमुख्य = kstrdup(करोमुख्य, GFP_ATOMIC);
		अगर (entry->करोमुख्य == शून्य)
			जाओ out_करोमुख्य;
	पूर्ण

	अगर (addr == शून्य && mask == शून्य) अणु
		entry->def.cipso = करोi_def;
		entry->def.type = NETLBL_NLTYPE_CIPSOV4;
	पूर्ण अन्यथा अगर (addr != शून्य && mask != शून्य) अणु
		addrmap = kzalloc(माप(*addrmap), GFP_ATOMIC);
		अगर (addrmap == शून्य)
			जाओ out_addrmap;
		INIT_LIST_HEAD(&addrmap->list4);
		INIT_LIST_HEAD(&addrmap->list6);

		addrinfo = kzalloc(माप(*addrinfo), GFP_ATOMIC);
		अगर (addrinfo == शून्य)
			जाओ out_addrinfo;
		addrinfo->def.cipso = करोi_def;
		addrinfo->def.type = NETLBL_NLTYPE_CIPSOV4;
		addrinfo->list.addr = addr->s_addr & mask->s_addr;
		addrinfo->list.mask = mask->s_addr;
		addrinfo->list.valid = 1;
		ret_val = netlbl_af4list_add(&addrinfo->list, &addrmap->list4);
		अगर (ret_val != 0)
			जाओ cfg_cipsov4_map_add_failure;

		entry->def.addrsel = addrmap;
		entry->def.type = NETLBL_NLTYPE_ADDRSELECT;
	पूर्ण अन्यथा अणु
		ret_val = -EINVAL;
		जाओ out_addrmap;
	पूर्ण

	ret_val = netlbl_करोmhsh_add(entry, audit_info);
	अगर (ret_val != 0)
		जाओ cfg_cipsov4_map_add_failure;

	वापस 0;

cfg_cipsov4_map_add_failure:
	kमुक्त(addrinfo);
out_addrinfo:
	kमुक्त(addrmap);
out_addrmap:
	kमुक्त(entry->करोमुख्य);
out_करोमुख्य:
	kमुक्त(entry);
out_entry:
	cipso_v4_करोi_putdef(करोi_def);
	वापस ret_val;
पूर्ण

/**
 * netlbl_cfg_calipso_add - Add a new CALIPSO DOI definition
 * @करोi_def: CALIPSO DOI definition
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Add a new CALIPSO DOI definition as defined by @करोi_def.  Returns zero on
 * success and negative values on failure.
 *
 */
पूर्णांक netlbl_cfg_calipso_add(काष्ठा calipso_करोi *करोi_def,
			   काष्ठा netlbl_audit *audit_info)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	वापस calipso_करोi_add(करोi_def, audit_info);
#अन्यथा /* IPv6 */
	वापस -ENOSYS;
#पूर्ण_अगर /* IPv6 */
पूर्ण

/**
 * netlbl_cfg_calipso_del - Remove an existing CALIPSO DOI definition
 * @करोi: CALIPSO DOI
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Remove an existing CALIPSO DOI definition matching @करोi.  Returns zero on
 * success and negative values on failure.
 *
 */
व्योम netlbl_cfg_calipso_del(u32 करोi, काष्ठा netlbl_audit *audit_info)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	calipso_करोi_हटाओ(करोi, audit_info);
#पूर्ण_अगर /* IPv6 */
पूर्ण

/**
 * netlbl_cfg_calipso_map_add - Add a new CALIPSO DOI mapping
 * @करोi: the CALIPSO DOI
 * @करोमुख्य: the करोमुख्य mapping to add
 * @addr: IP address
 * @mask: IP address mask
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Add a new NetLabel/LSM करोमुख्य mapping क्रम the given CALIPSO DOI to the
 * NetLabel subप्रणाली.  A @करोमुख्य value of शून्य adds a new शेष करोमुख्य
 * mapping.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक netlbl_cfg_calipso_map_add(u32 करोi,
			       स्थिर अक्षर *करोमुख्य,
			       स्थिर काष्ठा in6_addr *addr,
			       स्थिर काष्ठा in6_addr *mask,
			       काष्ठा netlbl_audit *audit_info)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्णांक ret_val = -ENOMEM;
	काष्ठा calipso_करोi *करोi_def;
	काष्ठा netlbl_करोm_map *entry;
	काष्ठा netlbl_करोmaddr_map *addrmap = शून्य;
	काष्ठा netlbl_करोmaddr6_map *addrinfo = शून्य;

	करोi_def = calipso_करोi_getdef(करोi);
	अगर (करोi_def == शून्य)
		वापस -ENOENT;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (entry == शून्य)
		जाओ out_entry;
	entry->family = AF_INET6;
	अगर (करोमुख्य != शून्य) अणु
		entry->करोमुख्य = kstrdup(करोमुख्य, GFP_ATOMIC);
		अगर (entry->करोमुख्य == शून्य)
			जाओ out_करोमुख्य;
	पूर्ण

	अगर (addr == शून्य && mask == शून्य) अणु
		entry->def.calipso = करोi_def;
		entry->def.type = NETLBL_NLTYPE_CALIPSO;
	पूर्ण अन्यथा अगर (addr != शून्य && mask != शून्य) अणु
		addrmap = kzalloc(माप(*addrmap), GFP_ATOMIC);
		अगर (addrmap == शून्य)
			जाओ out_addrmap;
		INIT_LIST_HEAD(&addrmap->list4);
		INIT_LIST_HEAD(&addrmap->list6);

		addrinfo = kzalloc(माप(*addrinfo), GFP_ATOMIC);
		अगर (addrinfo == शून्य)
			जाओ out_addrinfo;
		addrinfo->def.calipso = करोi_def;
		addrinfo->def.type = NETLBL_NLTYPE_CALIPSO;
		addrinfo->list.addr = *addr;
		addrinfo->list.addr.s6_addr32[0] &= mask->s6_addr32[0];
		addrinfo->list.addr.s6_addr32[1] &= mask->s6_addr32[1];
		addrinfo->list.addr.s6_addr32[2] &= mask->s6_addr32[2];
		addrinfo->list.addr.s6_addr32[3] &= mask->s6_addr32[3];
		addrinfo->list.mask = *mask;
		addrinfo->list.valid = 1;
		ret_val = netlbl_af6list_add(&addrinfo->list, &addrmap->list6);
		अगर (ret_val != 0)
			जाओ cfg_calipso_map_add_failure;

		entry->def.addrsel = addrmap;
		entry->def.type = NETLBL_NLTYPE_ADDRSELECT;
	पूर्ण अन्यथा अणु
		ret_val = -EINVAL;
		जाओ out_addrmap;
	पूर्ण

	ret_val = netlbl_करोmhsh_add(entry, audit_info);
	अगर (ret_val != 0)
		जाओ cfg_calipso_map_add_failure;

	वापस 0;

cfg_calipso_map_add_failure:
	kमुक्त(addrinfo);
out_addrinfo:
	kमुक्त(addrmap);
out_addrmap:
	kमुक्त(entry->करोमुख्य);
out_करोमुख्य:
	kमुक्त(entry);
out_entry:
	calipso_करोi_putdef(करोi_def);
	वापस ret_val;
#अन्यथा /* IPv6 */
	वापस -ENOSYS;
#पूर्ण_अगर /* IPv6 */
पूर्ण

/*
 * Security Attribute Functions
 */

#घोषणा _CM_F_NONE	0x00000000
#घोषणा _CM_F_ALLOC	0x00000001
#घोषणा _CM_F_WALK	0x00000002

/**
 * _netlbl_caपंचांगap_getnode - Get a inभागidual node from a caपंचांगap
 * @caपंचांगap: poपूर्णांकer to the category biपंचांगap
 * @offset: the requested offset
 * @cm_flags: caपंचांगap flags, see _CM_F_*
 * @gfp_flags: memory allocation flags
 *
 * Description:
 * Iterate through the caपंचांगap looking क्रम the node associated with @offset.
 * If the _CM_F_ALLOC flag is set in @cm_flags and there is no associated node,
 * one will be created and inserted पूर्णांकo the caपंचांगap.  If the _CM_F_WALK flag is
 * set in @cm_flags and there is no associated node, the next highest node will
 * be वापसed.  Returns a poपूर्णांकer to the node on success, शून्य on failure.
 *
 */
अटल काष्ठा netlbl_lsm_caपंचांगap *_netlbl_caपंचांगap_getnode(
					     काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
					     u32 offset,
					     अचिन्हित पूर्णांक cm_flags,
					     gfp_t gfp_flags)
अणु
	काष्ठा netlbl_lsm_caपंचांगap *iter = *caपंचांगap;
	काष्ठा netlbl_lsm_caपंचांगap *prev = शून्य;

	अगर (iter == शून्य)
		जाओ caपंचांगap_getnode_alloc;
	अगर (offset < iter->startbit)
		जाओ caपंचांगap_getnode_walk;
	जबतक (iter && offset >= (iter->startbit + NETLBL_CATMAP_SIZE)) अणु
		prev = iter;
		iter = iter->next;
	पूर्ण
	अगर (iter == शून्य || offset < iter->startbit)
		जाओ caपंचांगap_getnode_walk;

	वापस iter;

caपंचांगap_getnode_walk:
	अगर (cm_flags & _CM_F_WALK)
		वापस iter;
caपंचांगap_getnode_alloc:
	अगर (!(cm_flags & _CM_F_ALLOC))
		वापस शून्य;

	iter = netlbl_caपंचांगap_alloc(gfp_flags);
	अगर (iter == शून्य)
		वापस शून्य;
	iter->startbit = offset & ~(NETLBL_CATMAP_SIZE - 1);

	अगर (prev == शून्य) अणु
		iter->next = *caपंचांगap;
		*caपंचांगap = iter;
	पूर्ण अन्यथा अणु
		iter->next = prev->next;
		prev->next = iter;
	पूर्ण

	वापस iter;
पूर्ण

/**
 * netlbl_caपंचांगap_walk - Walk a LSM secattr caपंचांगap looking क्रम a bit
 * @caपंचांगap: the category biपंचांगap
 * @offset: the offset to start searching at, in bits
 *
 * Description:
 * This function walks a LSM secattr category biपंचांगap starting at @offset and
 * वापसs the spot of the first set bit or -ENOENT अगर no bits are set.
 *
 */
पूर्णांक netlbl_caपंचांगap_walk(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap, u32 offset)
अणु
	काष्ठा netlbl_lsm_caपंचांगap *iter;
	u32 idx;
	u32 bit;
	NETLBL_CATMAP_MAPTYPE biपंचांगap;

	iter = _netlbl_caपंचांगap_getnode(&caपंचांगap, offset, _CM_F_WALK, 0);
	अगर (iter == शून्य)
		वापस -ENOENT;
	अगर (offset > iter->startbit) अणु
		offset -= iter->startbit;
		idx = offset / NETLBL_CATMAP_MAPSIZE;
		bit = offset % NETLBL_CATMAP_MAPSIZE;
	पूर्ण अन्यथा अणु
		idx = 0;
		bit = 0;
	पूर्ण
	biपंचांगap = iter->biपंचांगap[idx] >> bit;

	क्रम (;;) अणु
		अगर (biपंचांगap != 0) अणु
			जबतक ((biपंचांगap & NETLBL_CATMAP_BIT) == 0) अणु
				biपंचांगap >>= 1;
				bit++;
			पूर्ण
			वापस iter->startbit +
			       (NETLBL_CATMAP_MAPSIZE * idx) + bit;
		पूर्ण
		अगर (++idx >= NETLBL_CATMAP_MAPCNT) अणु
			अगर (iter->next != शून्य) अणु
				iter = iter->next;
				idx = 0;
			पूर्ण अन्यथा
				वापस -ENOENT;
		पूर्ण
		biपंचांगap = iter->biपंचांगap[idx];
		bit = 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL(netlbl_caपंचांगap_walk);

/**
 * netlbl_caपंचांगap_walkrng - Find the end of a string of set bits
 * @caपंचांगap: the category biपंचांगap
 * @offset: the offset to start searching at, in bits
 *
 * Description:
 * This function walks a LSM secattr category biपंचांगap starting at @offset and
 * वापसs the spot of the first cleared bit or -ENOENT अगर the offset is past
 * the end of the biपंचांगap.
 *
 */
पूर्णांक netlbl_caपंचांगap_walkrng(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap, u32 offset)
अणु
	काष्ठा netlbl_lsm_caपंचांगap *iter;
	काष्ठा netlbl_lsm_caपंचांगap *prev = शून्य;
	u32 idx;
	u32 bit;
	NETLBL_CATMAP_MAPTYPE biपंचांगask;
	NETLBL_CATMAP_MAPTYPE biपंचांगap;

	iter = _netlbl_caपंचांगap_getnode(&caपंचांगap, offset, _CM_F_WALK, 0);
	अगर (iter == शून्य)
		वापस -ENOENT;
	अगर (offset > iter->startbit) अणु
		offset -= iter->startbit;
		idx = offset / NETLBL_CATMAP_MAPSIZE;
		bit = offset % NETLBL_CATMAP_MAPSIZE;
	पूर्ण अन्यथा अणु
		idx = 0;
		bit = 0;
	पूर्ण
	biपंचांगask = NETLBL_CATMAP_BIT << bit;

	क्रम (;;) अणु
		biपंचांगap = iter->biपंचांगap[idx];
		जबतक (biपंचांगask != 0 && (biपंचांगap & biपंचांगask) != 0) अणु
			biपंचांगask <<= 1;
			bit++;
		पूर्ण

		अगर (prev && idx == 0 && bit == 0)
			वापस prev->startbit + NETLBL_CATMAP_SIZE - 1;
		अन्यथा अगर (biपंचांगask != 0)
			वापस iter->startbit +
				(NETLBL_CATMAP_MAPSIZE * idx) + bit - 1;
		अन्यथा अगर (++idx >= NETLBL_CATMAP_MAPCNT) अणु
			अगर (iter->next == शून्य)
				वापस iter->startbit + NETLBL_CATMAP_SIZE - 1;
			prev = iter;
			iter = iter->next;
			idx = 0;
		पूर्ण
		biपंचांगask = NETLBL_CATMAP_BIT;
		bit = 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * netlbl_caपंचांगap_getदीर्घ - Export an अचिन्हित दीर्घ biपंचांगap
 * @caपंचांगap: poपूर्णांकer to the category biपंचांगap
 * @offset: poपूर्णांकer to the requested offset
 * @biपंचांगap: the exported biपंचांगap
 *
 * Description:
 * Export a biपंचांगap with an offset greater than or equal to @offset and वापस
 * it in @biपंचांगap.  The @offset must be aligned to an अचिन्हित दीर्घ and will be
 * updated on वापस अगर dअगरferent from what was requested; अगर the caपंचांगap is
 * empty at the requested offset and beyond, the @offset is set to (u32)-1.
 * Returns zero on sucess, negative values on failure.
 *
 */
पूर्णांक netlbl_caपंचांगap_getदीर्घ(काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap,
			  u32 *offset,
			  अचिन्हित दीर्घ *biपंचांगap)
अणु
	काष्ठा netlbl_lsm_caपंचांगap *iter;
	u32 off = *offset;
	u32 idx;

	/* only allow aligned offsets */
	अगर ((off & (BITS_PER_LONG - 1)) != 0)
		वापस -EINVAL;

	/* a null caपंचांगap is equivalent to an empty one */
	अगर (!caपंचांगap) अणु
		*offset = (u32)-1;
		वापस 0;
	पूर्ण

	अगर (off < caपंचांगap->startbit) अणु
		off = caपंचांगap->startbit;
		*offset = off;
	पूर्ण
	iter = _netlbl_caपंचांगap_getnode(&caपंचांगap, off, _CM_F_WALK, 0);
	अगर (iter == शून्य) अणु
		*offset = (u32)-1;
		वापस 0;
	पूर्ण

	अगर (off < iter->startbit) अणु
		*offset = iter->startbit;
		off = 0;
	पूर्ण अन्यथा
		off -= iter->startbit;
	idx = off / NETLBL_CATMAP_MAPSIZE;
	*biपंचांगap = iter->biपंचांगap[idx] >> (off % NETLBL_CATMAP_MAPSIZE);

	वापस 0;
पूर्ण

/**
 * netlbl_caपंचांगap_setbit - Set a bit in a LSM secattr caपंचांगap
 * @caपंचांगap: poपूर्णांकer to the category biपंचांगap
 * @bit: the bit to set
 * @flags: memory allocation flags
 *
 * Description:
 * Set the bit specअगरied by @bit in @caपंचांगap.  Returns zero on success,
 * negative values on failure.
 *
 */
पूर्णांक netlbl_caपंचांगap_setbit(काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
			 u32 bit,
			 gfp_t flags)
अणु
	काष्ठा netlbl_lsm_caपंचांगap *iter;
	u32 idx;

	iter = _netlbl_caपंचांगap_getnode(caपंचांगap, bit, _CM_F_ALLOC, flags);
	अगर (iter == शून्य)
		वापस -ENOMEM;

	bit -= iter->startbit;
	idx = bit / NETLBL_CATMAP_MAPSIZE;
	iter->biपंचांगap[idx] |= NETLBL_CATMAP_BIT << (bit % NETLBL_CATMAP_MAPSIZE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(netlbl_caपंचांगap_setbit);

/**
 * netlbl_caपंचांगap_setrng - Set a range of bits in a LSM secattr caपंचांगap
 * @caपंचांगap: poपूर्णांकer to the category biपंचांगap
 * @start: the starting bit
 * @end: the last bit in the string
 * @flags: memory allocation flags
 *
 * Description:
 * Set a range of bits, starting at @start and ending with @end.  Returns zero
 * on success, negative values on failure.
 *
 */
पूर्णांक netlbl_caपंचांगap_setrng(काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
			 u32 start,
			 u32 end,
			 gfp_t flags)
अणु
	पूर्णांक rc = 0;
	u32 spot = start;

	जबतक (rc == 0 && spot <= end) अणु
		अगर (((spot & (BITS_PER_LONG - 1)) == 0) &&
		    ((end - spot) > BITS_PER_LONG)) अणु
			rc = netlbl_caपंचांगap_setदीर्घ(caपंचांगap,
						   spot,
						   (अचिन्हित दीर्घ)-1,
						   flags);
			spot += BITS_PER_LONG;
		पूर्ण अन्यथा
			rc = netlbl_caपंचांगap_setbit(caपंचांगap, spot++, flags);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * netlbl_caपंचांगap_setदीर्घ - Import an अचिन्हित दीर्घ biपंचांगap
 * @caपंचांगap: poपूर्णांकer to the category biपंचांगap
 * @offset: offset to the start of the imported biपंचांगap
 * @biपंचांगap: the biपंचांगap to import
 * @flags: memory allocation flags
 *
 * Description:
 * Import the biपंचांगap specअगरied in @biपंचांगap पूर्णांकo @caपंचांगap, using the offset
 * in @offset.  The offset must be aligned to an अचिन्हित दीर्घ.  Returns zero
 * on success, negative values on failure.
 *
 */
पूर्णांक netlbl_caपंचांगap_setदीर्घ(काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap,
			  u32 offset,
			  अचिन्हित दीर्घ biपंचांगap,
			  gfp_t flags)
अणु
	काष्ठा netlbl_lsm_caपंचांगap *iter;
	u32 idx;

	/* only allow aligned offsets */
	अगर ((offset & (BITS_PER_LONG - 1)) != 0)
		वापस -EINVAL;

	iter = _netlbl_caपंचांगap_getnode(caपंचांगap, offset, _CM_F_ALLOC, flags);
	अगर (iter == शून्य)
		वापस -ENOMEM;

	offset -= iter->startbit;
	idx = offset / NETLBL_CATMAP_MAPSIZE;
	iter->biपंचांगap[idx] |= biपंचांगap << (offset % NETLBL_CATMAP_MAPSIZE);

	वापस 0;
पूर्ण

/* Biपंचांगap functions
 */

/**
 * netlbl_biपंचांगap_walk - Walk a biपंचांगap looking क्रम a bit
 * @biपंचांगap: the biपंचांगap
 * @biपंचांगap_len: length in bits
 * @offset: starting offset
 * @state: अगर non-zero, look क्रम a set (1) bit अन्यथा look क्रम a cleared (0) bit
 *
 * Description:
 * Starting at @offset, walk the biपंचांगap from left to right until either the
 * desired bit is found or we reach the end.  Return the bit offset, -1 अगर
 * not found, or -2 अगर error.
 */
पूर्णांक netlbl_biपंचांगap_walk(स्थिर अचिन्हित अक्षर *biपंचांगap, u32 biपंचांगap_len,
		       u32 offset, u8 state)
अणु
	u32 bit_spot;
	u32 byte_offset;
	अचिन्हित अक्षर biपंचांगask;
	अचिन्हित अक्षर byte;

	byte_offset = offset / 8;
	byte = biपंचांगap[byte_offset];
	bit_spot = offset;
	biपंचांगask = 0x80 >> (offset % 8);

	जबतक (bit_spot < biपंचांगap_len) अणु
		अगर ((state && (byte & biपंचांगask) == biपंचांगask) ||
		    (state == 0 && (byte & biपंचांगask) == 0))
			वापस bit_spot;

		अगर (++bit_spot >= biपंचांगap_len)
			वापस -1;
		biपंचांगask >>= 1;
		अगर (biपंचांगask == 0) अणु
			byte = biपंचांगap[++byte_offset];
			biपंचांगask = 0x80;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण
EXPORT_SYMBOL(netlbl_biपंचांगap_walk);

/**
 * netlbl_biपंचांगap_setbit - Sets a single bit in a biपंचांगap
 * @biपंचांगap: the biपंचांगap
 * @bit: the bit
 * @state: अगर non-zero, set the bit (1) अन्यथा clear the bit (0)
 *
 * Description:
 * Set a single bit in the biपंचांगask.  Returns zero on success, negative values
 * on error.
 */
व्योम netlbl_biपंचांगap_setbit(अचिन्हित अक्षर *biपंचांगap, u32 bit, u8 state)
अणु
	u32 byte_spot;
	u8 biपंचांगask;

	/* gcc always rounds to zero when करोing पूर्णांकeger भागision */
	byte_spot = bit / 8;
	biपंचांगask = 0x80 >> (bit % 8);
	अगर (state)
		biपंचांगap[byte_spot] |= biपंचांगask;
	अन्यथा
		biपंचांगap[byte_spot] &= ~biपंचांगask;
पूर्ण
EXPORT_SYMBOL(netlbl_biपंचांगap_setbit);

/*
 * LSM Functions
 */

/**
 * netlbl_enabled - Determine अगर the NetLabel subप्रणाली is enabled
 *
 * Description:
 * The LSM can use this function to determine अगर it should use NetLabel
 * security attributes in it's enक्रमcement mechanism.  Currently, NetLabel is
 * considered to be enabled when it's configuration contains a valid setup क्रम
 * at least one labeled protocol (i.e. NetLabel can understand incoming
 * labeled packets of at least one type); otherwise NetLabel is considered to
 * be disabled.
 *
 */
पूर्णांक netlbl_enabled(व्योम)
अणु
	/* At some poपूर्णांक we probably want to expose this mechanism to the user
	 * as well so that admins can toggle NetLabel regardless of the
	 * configuration */
	वापस (atomic_पढ़ो(&netlabel_mgmt_protocount) > 0);
पूर्ण

/**
 * netlbl_sock_setattr - Label a socket using the correct protocol
 * @sk: the socket to label
 * @family: protocol family
 * @secattr: the security attributes
 *
 * Description:
 * Attach the correct label to the given socket using the security attributes
 * specअगरied in @secattr.  This function requires exclusive access to @sk,
 * which means it either needs to be in the process of being created or locked.
 * Returns zero on success, -EDESTADDRREQ अगर the करोमुख्य is configured to use
 * network address selectors (can't blindly label the socket), and negative
 * values on all other failures.
 *
 */
पूर्णांक netlbl_sock_setattr(काष्ठा sock *sk,
			u16 family,
			स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	काष्ठा netlbl_करोm_map *करोm_entry;

	rcu_पढ़ो_lock();
	करोm_entry = netlbl_करोmhsh_getentry(secattr->करोमुख्य, family);
	अगर (करोm_entry == शून्य) अणु
		ret_val = -ENOENT;
		जाओ socket_setattr_वापस;
	पूर्ण
	चयन (family) अणु
	हाल AF_INET:
		चयन (करोm_entry->def.type) अणु
		हाल NETLBL_NLTYPE_ADDRSELECT:
			ret_val = -EDESTADDRREQ;
			अवरोध;
		हाल NETLBL_NLTYPE_CIPSOV4:
			ret_val = cipso_v4_sock_setattr(sk,
							करोm_entry->def.cipso,
							secattr);
			अवरोध;
		हाल NETLBL_NLTYPE_UNLABELED:
			ret_val = 0;
			अवरोध;
		शेष:
			ret_val = -ENOENT;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		चयन (करोm_entry->def.type) अणु
		हाल NETLBL_NLTYPE_ADDRSELECT:
			ret_val = -EDESTADDRREQ;
			अवरोध;
		हाल NETLBL_NLTYPE_CALIPSO:
			ret_val = calipso_sock_setattr(sk,
						       करोm_entry->def.calipso,
						       secattr);
			अवरोध;
		हाल NETLBL_NLTYPE_UNLABELED:
			ret_val = 0;
			अवरोध;
		शेष:
			ret_val = -ENOENT;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	शेष:
		ret_val = -EPROTONOSUPPORT;
	पूर्ण

socket_setattr_वापस:
	rcu_पढ़ो_unlock();
	वापस ret_val;
पूर्ण

/**
 * netlbl_sock_delattr - Delete all the NetLabel labels on a socket
 * @sk: the socket
 *
 * Description:
 * Remove all the NetLabel labeling from @sk.  The caller is responsible क्रम
 * ensuring that @sk is locked.
 *
 */
व्योम netlbl_sock_delattr(काष्ठा sock *sk)
अणु
	चयन (sk->sk_family) अणु
	हाल AF_INET:
		cipso_v4_sock_delattr(sk);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		calipso_sock_delattr(sk);
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	पूर्ण
पूर्ण

/**
 * netlbl_sock_getattr - Determine the security attributes of a sock
 * @sk: the sock
 * @secattr: the security attributes
 *
 * Description:
 * Examines the given sock to see अगर any NetLabel style labeling has been
 * applied to the sock, अगर so it parses the socket label and वापसs the
 * security attributes in @secattr.  Returns zero on success, negative values
 * on failure.
 *
 */
पूर्णांक netlbl_sock_getattr(काष्ठा sock *sk,
			काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;

	चयन (sk->sk_family) अणु
	हाल AF_INET:
		ret_val = cipso_v4_sock_getattr(sk, secattr);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		ret_val = calipso_sock_getattr(sk, secattr);
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	शेष:
		ret_val = -EPROTONOSUPPORT;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * netlbl_conn_setattr - Label a connected socket using the correct protocol
 * @sk: the socket to label
 * @addr: the destination address
 * @secattr: the security attributes
 *
 * Description:
 * Attach the correct label to the given connected socket using the security
 * attributes specअगरied in @secattr.  The caller is responsible क्रम ensuring
 * that @sk is locked.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक netlbl_conn_setattr(काष्ठा sock *sk,
			काष्ठा sockaddr *addr,
			स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	काष्ठा sockaddr_in *addr4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा sockaddr_in6 *addr6;
#पूर्ण_अगर
	काष्ठा netlbl_करोmmap_def *entry;

	rcu_पढ़ो_lock();
	चयन (addr->sa_family) अणु
	हाल AF_INET:
		addr4 = (काष्ठा sockaddr_in *)addr;
		entry = netlbl_करोmhsh_getentry_af4(secattr->करोमुख्य,
						   addr4->sin_addr.s_addr);
		अगर (entry == शून्य) अणु
			ret_val = -ENOENT;
			जाओ conn_setattr_वापस;
		पूर्ण
		चयन (entry->type) अणु
		हाल NETLBL_NLTYPE_CIPSOV4:
			ret_val = cipso_v4_sock_setattr(sk,
							entry->cipso, secattr);
			अवरोध;
		हाल NETLBL_NLTYPE_UNLABELED:
			/* just delete the protocols we support क्रम right now
			 * but we could हटाओ other protocols अगर needed */
			netlbl_sock_delattr(sk);
			ret_val = 0;
			अवरोध;
		शेष:
			ret_val = -ENOENT;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		addr6 = (काष्ठा sockaddr_in6 *)addr;
		entry = netlbl_करोmhsh_getentry_af6(secattr->करोमुख्य,
						   &addr6->sin6_addr);
		अगर (entry == शून्य) अणु
			ret_val = -ENOENT;
			जाओ conn_setattr_वापस;
		पूर्ण
		चयन (entry->type) अणु
		हाल NETLBL_NLTYPE_CALIPSO:
			ret_val = calipso_sock_setattr(sk,
						       entry->calipso, secattr);
			अवरोध;
		हाल NETLBL_NLTYPE_UNLABELED:
			/* just delete the protocols we support क्रम right now
			 * but we could हटाओ other protocols अगर needed */
			netlbl_sock_delattr(sk);
			ret_val = 0;
			अवरोध;
		शेष:
			ret_val = -ENOENT;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	शेष:
		ret_val = -EPROTONOSUPPORT;
	पूर्ण

conn_setattr_वापस:
	rcu_पढ़ो_unlock();
	वापस ret_val;
पूर्ण

/**
 * netlbl_req_setattr - Label a request socket using the correct protocol
 * @req: the request socket to label
 * @secattr: the security attributes
 *
 * Description:
 * Attach the correct label to the given socket using the security attributes
 * specअगरied in @secattr.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक netlbl_req_setattr(काष्ठा request_sock *req,
		       स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	काष्ठा netlbl_करोmmap_def *entry;
	काष्ठा inet_request_sock *ireq = inet_rsk(req);

	rcu_पढ़ो_lock();
	चयन (req->rsk_ops->family) अणु
	हाल AF_INET:
		entry = netlbl_करोmhsh_getentry_af4(secattr->करोमुख्य,
						   ireq->ir_rmt_addr);
		अगर (entry == शून्य) अणु
			ret_val = -ENOENT;
			जाओ req_setattr_वापस;
		पूर्ण
		चयन (entry->type) अणु
		हाल NETLBL_NLTYPE_CIPSOV4:
			ret_val = cipso_v4_req_setattr(req,
						       entry->cipso, secattr);
			अवरोध;
		हाल NETLBL_NLTYPE_UNLABELED:
			netlbl_req_delattr(req);
			ret_val = 0;
			अवरोध;
		शेष:
			ret_val = -ENOENT;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		entry = netlbl_करोmhsh_getentry_af6(secattr->करोमुख्य,
						   &ireq->ir_v6_rmt_addr);
		अगर (entry == शून्य) अणु
			ret_val = -ENOENT;
			जाओ req_setattr_वापस;
		पूर्ण
		चयन (entry->type) अणु
		हाल NETLBL_NLTYPE_CALIPSO:
			ret_val = calipso_req_setattr(req,
						      entry->calipso, secattr);
			अवरोध;
		हाल NETLBL_NLTYPE_UNLABELED:
			netlbl_req_delattr(req);
			ret_val = 0;
			अवरोध;
		शेष:
			ret_val = -ENOENT;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	शेष:
		ret_val = -EPROTONOSUPPORT;
	पूर्ण

req_setattr_वापस:
	rcu_पढ़ो_unlock();
	वापस ret_val;
पूर्ण

/**
* netlbl_req_delattr - Delete all the NetLabel labels on a socket
* @req: the socket
*
* Description:
* Remove all the NetLabel labeling from @req.
*
*/
व्योम netlbl_req_delattr(काष्ठा request_sock *req)
अणु
	चयन (req->rsk_ops->family) अणु
	हाल AF_INET:
		cipso_v4_req_delattr(req);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		calipso_req_delattr(req);
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	पूर्ण
पूर्ण

/**
 * netlbl_skbuff_setattr - Label a packet using the correct protocol
 * @skb: the packet
 * @family: protocol family
 * @secattr: the security attributes
 *
 * Description:
 * Attach the correct label to the given packet using the security attributes
 * specअगरied in @secattr.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक netlbl_skbuff_setattr(काष्ठा sk_buff *skb,
			  u16 family,
			  स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक ret_val;
	काष्ठा iphdr *hdr4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा ipv6hdr *hdr6;
#पूर्ण_अगर
	काष्ठा netlbl_करोmmap_def *entry;

	rcu_पढ़ो_lock();
	चयन (family) अणु
	हाल AF_INET:
		hdr4 = ip_hdr(skb);
		entry = netlbl_करोmhsh_getentry_af4(secattr->करोमुख्य,
						   hdr4->daddr);
		अगर (entry == शून्य) अणु
			ret_val = -ENOENT;
			जाओ skbuff_setattr_वापस;
		पूर्ण
		चयन (entry->type) अणु
		हाल NETLBL_NLTYPE_CIPSOV4:
			ret_val = cipso_v4_skbuff_setattr(skb, entry->cipso,
							  secattr);
			अवरोध;
		हाल NETLBL_NLTYPE_UNLABELED:
			/* just delete the protocols we support क्रम right now
			 * but we could हटाओ other protocols अगर needed */
			ret_val = cipso_v4_skbuff_delattr(skb);
			अवरोध;
		शेष:
			ret_val = -ENOENT;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		hdr6 = ipv6_hdr(skb);
		entry = netlbl_करोmhsh_getentry_af6(secattr->करोमुख्य,
						   &hdr6->daddr);
		अगर (entry == शून्य) अणु
			ret_val = -ENOENT;
			जाओ skbuff_setattr_वापस;
		पूर्ण
		चयन (entry->type) अणु
		हाल NETLBL_NLTYPE_CALIPSO:
			ret_val = calipso_skbuff_setattr(skb, entry->calipso,
							 secattr);
			अवरोध;
		हाल NETLBL_NLTYPE_UNLABELED:
			/* just delete the protocols we support क्रम right now
			 * but we could हटाओ other protocols अगर needed */
			ret_val = calipso_skbuff_delattr(skb);
			अवरोध;
		शेष:
			ret_val = -ENOENT;
		पूर्ण
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	शेष:
		ret_val = -EPROTONOSUPPORT;
	पूर्ण

skbuff_setattr_वापस:
	rcu_पढ़ो_unlock();
	वापस ret_val;
पूर्ण

/**
 * netlbl_skbuff_getattr - Determine the security attributes of a packet
 * @skb: the packet
 * @family: protocol family
 * @secattr: the security attributes
 *
 * Description:
 * Examines the given packet to see अगर a recognized क्रमm of packet labeling
 * is present, अगर so it parses the packet label and वापसs the security
 * attributes in @secattr.  Returns zero on success, negative values on
 * failure.
 *
 */
पूर्णांक netlbl_skbuff_getattr(स्थिर काष्ठा sk_buff *skb,
			  u16 family,
			  काष्ठा netlbl_lsm_secattr *secattr)
अणु
	अचिन्हित अक्षर *ptr;

	चयन (family) अणु
	हाल AF_INET:
		ptr = cipso_v4_optptr(skb);
		अगर (ptr && cipso_v4_getattr(ptr, secattr) == 0)
			वापस 0;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		ptr = calipso_optptr(skb);
		अगर (ptr && calipso_getattr(ptr, secattr) == 0)
			वापस 0;
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	पूर्ण

	वापस netlbl_unlabel_getattr(skb, family, secattr);
पूर्ण

/**
 * netlbl_skbuff_err - Handle a LSM error on a sk_buff
 * @skb: the packet
 * @family: the family
 * @error: the error code
 * @gateway: true अगर host is acting as a gateway, false otherwise
 *
 * Description:
 * Deal with a LSM problem when handling the packet in @skb, typically this is
 * a permission denied problem (-EACCES).  The correct action is determined
 * according to the packet's labeling protocol.
 *
 */
व्योम netlbl_skbuff_err(काष्ठा sk_buff *skb, u16 family, पूर्णांक error, पूर्णांक gateway)
अणु
	चयन (family) अणु
	हाल AF_INET:
		अगर (cipso_v4_optptr(skb))
			cipso_v4_error(skb, error, gateway);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * netlbl_cache_invalidate - Invalidate all of the NetLabel protocol caches
 *
 * Description:
 * For all of the NetLabel protocols that support some क्रमm of label mapping
 * cache, invalidate the cache.  Returns zero on success, negative values on
 * error.
 *
 */
व्योम netlbl_cache_invalidate(व्योम)
अणु
	cipso_v4_cache_invalidate();
#अगर IS_ENABLED(CONFIG_IPV6)
	calipso_cache_invalidate();
#पूर्ण_अगर /* IPv6 */
पूर्ण

/**
 * netlbl_cache_add - Add an entry to a NetLabel protocol cache
 * @skb: the packet
 * @family: the family
 * @secattr: the packet's security attributes
 *
 * Description:
 * Add the LSM security attributes क्रम the given packet to the underlying
 * NetLabel protocol's label mapping cache.  Returns zero on success, negative
 * values on error.
 *
 */
पूर्णांक netlbl_cache_add(स्थिर काष्ठा sk_buff *skb, u16 family,
		     स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	अचिन्हित अक्षर *ptr;

	अगर ((secattr->flags & NETLBL_SECATTR_CACHE) == 0)
		वापस -ENOMSG;

	चयन (family) अणु
	हाल AF_INET:
		ptr = cipso_v4_optptr(skb);
		अगर (ptr)
			वापस cipso_v4_cache_add(ptr, secattr);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		ptr = calipso_optptr(skb);
		अगर (ptr)
			वापस calipso_cache_add(ptr, secattr);
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	पूर्ण
	वापस -ENOMSG;
पूर्ण

/*
 * Protocol Engine Functions
 */

/**
 * netlbl_audit_start - Start an audit message
 * @type: audit message type
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Start an audit message using the type specअगरied in @type and fill the audit
 * message with some fields common to all NetLabel audit messages.  This
 * function should only be used by protocol engines, not LSMs.  Returns a
 * poपूर्णांकer to the audit buffer on success, शून्य on failure.
 *
 */
काष्ठा audit_buffer *netlbl_audit_start(पूर्णांक type,
					काष्ठा netlbl_audit *audit_info)
अणु
	वापस netlbl_audit_start_common(type, audit_info);
पूर्ण
EXPORT_SYMBOL(netlbl_audit_start);

/*
 * Setup Functions
 */

/**
 * netlbl_init - Initialize NetLabel
 *
 * Description:
 * Perक्रमm the required NetLabel initialization beक्रमe first use.
 *
 */
अटल पूर्णांक __init netlbl_init(व्योम)
अणु
	पूर्णांक ret_val;

	prपूर्णांकk(KERN_INFO "NetLabel: Initializing\n");
	prपूर्णांकk(KERN_INFO "NetLabel:  domain hash size = %u\n",
	       (1 << NETLBL_DOMHSH_BITSIZE));
	prपूर्णांकk(KERN_INFO "NetLabel:  protocols = UNLABELED CIPSOv4 CALIPSO\n");

	ret_val = netlbl_करोmhsh_init(NETLBL_DOMHSH_BITSIZE);
	अगर (ret_val != 0)
		जाओ init_failure;

	ret_val = netlbl_unlabel_init(NETLBL_UNLHSH_BITSIZE);
	अगर (ret_val != 0)
		जाओ init_failure;

	ret_val = netlbl_netlink_init();
	अगर (ret_val != 0)
		जाओ init_failure;

	ret_val = netlbl_unlabel_defconf();
	अगर (ret_val != 0)
		जाओ init_failure;
	prपूर्णांकk(KERN_INFO "NetLabel:  unlabeled traffic allowed by default\n");

	वापस 0;

init_failure:
	panic("NetLabel: failed to initialize properly (%d)\n", ret_val);
पूर्ण

subsys_initcall(netlbl_init);
