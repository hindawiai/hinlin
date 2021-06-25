<शैली गुरु>
/*
 * Implementation of the access vector table type.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */

/* Updated: Frank Mayer <mayerf@tresys.com> and Karl MacMillan <kmacmillan@tresys.com>
 *
 *	Added conditional policy language extensions
 *
 * Copyright (C) 2003 Tresys Technology, LLC
 *	This program is मुक्त software; you can redistribute it and/or modअगरy
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, version 2.
 *
 * Updated: Yuichi Nakamura <ynakam@hitachisoft.jp>
 *	Tuned number of hash slots क्रम avtab to reduce memory usage
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश "avtab.h"
#समावेश "policydb.h"

अटल काष्ठा kmem_cache *avtab_node_cachep __ro_after_init;
अटल काष्ठा kmem_cache *avtab_xperms_cachep __ro_after_init;

/* Based on MurmurHash3, written by Austin Appleby and placed in the
 * खुला करोमुख्य.
 */
अटल अंतरभूत पूर्णांक avtab_hash(काष्ठा avtab_key *keyp, u32 mask)
अणु
	अटल स्थिर u32 c1 = 0xcc9e2d51;
	अटल स्थिर u32 c2 = 0x1b873593;
	अटल स्थिर u32 r1 = 15;
	अटल स्थिर u32 r2 = 13;
	अटल स्थिर u32 m  = 5;
	अटल स्थिर u32 n  = 0xe6546b64;

	u32 hash = 0;

#घोषणा mix(input) अणु \
	u32 v = input; \
	v *= c1; \
	v = (v << r1) | (v >> (32 - r1)); \
	v *= c2; \
	hash ^= v; \
	hash = (hash << r2) | (hash >> (32 - r2)); \
	hash = hash * m + n; \
पूर्ण

	mix(keyp->target_class);
	mix(keyp->target_type);
	mix(keyp->source_type);

#अघोषित mix

	hash ^= hash >> 16;
	hash *= 0x85ebca6b;
	hash ^= hash >> 13;
	hash *= 0xc2b2ae35;
	hash ^= hash >> 16;

	वापस hash & mask;
पूर्ण

अटल काष्ठा avtab_node*
avtab_insert_node(काष्ठा avtab *h, पूर्णांक hvalue,
		  काष्ठा avtab_node *prev, काष्ठा avtab_node *cur,
		  काष्ठा avtab_key *key, काष्ठा avtab_datum *datum)
अणु
	काष्ठा avtab_node *newnode;
	काष्ठा avtab_extended_perms *xperms;
	newnode = kmem_cache_zalloc(avtab_node_cachep, GFP_KERNEL);
	अगर (newnode == शून्य)
		वापस शून्य;
	newnode->key = *key;

	अगर (key->specअगरied & AVTAB_XPERMS) अणु
		xperms = kmem_cache_zalloc(avtab_xperms_cachep, GFP_KERNEL);
		अगर (xperms == शून्य) अणु
			kmem_cache_मुक्त(avtab_node_cachep, newnode);
			वापस शून्य;
		पूर्ण
		*xperms = *(datum->u.xperms);
		newnode->datum.u.xperms = xperms;
	पूर्ण अन्यथा अणु
		newnode->datum.u.data = datum->u.data;
	पूर्ण

	अगर (prev) अणु
		newnode->next = prev->next;
		prev->next = newnode;
	पूर्ण अन्यथा अणु
		काष्ठा avtab_node **n = &h->htable[hvalue];

		newnode->next = *n;
		*n = newnode;
	पूर्ण

	h->nel++;
	वापस newnode;
पूर्ण

अटल पूर्णांक avtab_insert(काष्ठा avtab *h, काष्ठा avtab_key *key, काष्ठा avtab_datum *datum)
अणु
	पूर्णांक hvalue;
	काष्ठा avtab_node *prev, *cur, *newnode;
	u16 specअगरied = key->specअगरied & ~(AVTAB_ENABLED|AVTAB_ENABLED_OLD);

	अगर (!h || !h->nslot)
		वापस -EINVAL;

	hvalue = avtab_hash(key, h->mask);
	क्रम (prev = शून्य, cur = h->htable[hvalue];
	     cur;
	     prev = cur, cur = cur->next) अणु
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class == cur->key.target_class &&
		    (specअगरied & cur->key.specअगरied)) अणु
			/* extended perms may not be unique */
			अगर (specअगरied & AVTAB_XPERMS)
				अवरोध;
			वापस -EEXIST;
		पूर्ण
		अगर (key->source_type < cur->key.source_type)
			अवरोध;
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type < cur->key.target_type)
			अवरोध;
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class < cur->key.target_class)
			अवरोध;
	पूर्ण

	newnode = avtab_insert_node(h, hvalue, prev, cur, key, datum);
	अगर (!newnode)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Unlike avtab_insert(), this function allow multiple insertions of the same
 * key/specअगरied mask पूर्णांकo the table, as needed by the conditional avtab.
 * It also वापसs a poपूर्णांकer to the node inserted.
 */
काष्ठा avtab_node *
avtab_insert_nonunique(काष्ठा avtab *h, काष्ठा avtab_key *key, काष्ठा avtab_datum *datum)
अणु
	पूर्णांक hvalue;
	काष्ठा avtab_node *prev, *cur;
	u16 specअगरied = key->specअगरied & ~(AVTAB_ENABLED|AVTAB_ENABLED_OLD);

	अगर (!h || !h->nslot)
		वापस शून्य;
	hvalue = avtab_hash(key, h->mask);
	क्रम (prev = शून्य, cur = h->htable[hvalue];
	     cur;
	     prev = cur, cur = cur->next) अणु
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class == cur->key.target_class &&
		    (specअगरied & cur->key.specअगरied))
			अवरोध;
		अगर (key->source_type < cur->key.source_type)
			अवरोध;
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type < cur->key.target_type)
			अवरोध;
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class < cur->key.target_class)
			अवरोध;
	पूर्ण
	वापस avtab_insert_node(h, hvalue, prev, cur, key, datum);
पूर्ण

काष्ठा avtab_datum *avtab_search(काष्ठा avtab *h, काष्ठा avtab_key *key)
अणु
	पूर्णांक hvalue;
	काष्ठा avtab_node *cur;
	u16 specअगरied = key->specअगरied & ~(AVTAB_ENABLED|AVTAB_ENABLED_OLD);

	अगर (!h || !h->nslot)
		वापस शून्य;

	hvalue = avtab_hash(key, h->mask);
	क्रम (cur = h->htable[hvalue]; cur;
	     cur = cur->next) अणु
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class == cur->key.target_class &&
		    (specअगरied & cur->key.specअगरied))
			वापस &cur->datum;

		अगर (key->source_type < cur->key.source_type)
			अवरोध;
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type < cur->key.target_type)
			अवरोध;
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class < cur->key.target_class)
			अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

/* This search function वापसs a node poपूर्णांकer, and can be used in
 * conjunction with avtab_search_next_node()
 */
काष्ठा avtab_node*
avtab_search_node(काष्ठा avtab *h, काष्ठा avtab_key *key)
अणु
	पूर्णांक hvalue;
	काष्ठा avtab_node *cur;
	u16 specअगरied = key->specअगरied & ~(AVTAB_ENABLED|AVTAB_ENABLED_OLD);

	अगर (!h || !h->nslot)
		वापस शून्य;

	hvalue = avtab_hash(key, h->mask);
	क्रम (cur = h->htable[hvalue]; cur;
	     cur = cur->next) अणु
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class == cur->key.target_class &&
		    (specअगरied & cur->key.specअगरied))
			वापस cur;

		अगर (key->source_type < cur->key.source_type)
			अवरोध;
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type < cur->key.target_type)
			अवरोध;
		अगर (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class < cur->key.target_class)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा avtab_node*
avtab_search_node_next(काष्ठा avtab_node *node, पूर्णांक specअगरied)
अणु
	काष्ठा avtab_node *cur;

	अगर (!node)
		वापस शून्य;

	specअगरied &= ~(AVTAB_ENABLED|AVTAB_ENABLED_OLD);
	क्रम (cur = node->next; cur; cur = cur->next) अणु
		अगर (node->key.source_type == cur->key.source_type &&
		    node->key.target_type == cur->key.target_type &&
		    node->key.target_class == cur->key.target_class &&
		    (specअगरied & cur->key.specअगरied))
			वापस cur;

		अगर (node->key.source_type < cur->key.source_type)
			अवरोध;
		अगर (node->key.source_type == cur->key.source_type &&
		    node->key.target_type < cur->key.target_type)
			अवरोध;
		अगर (node->key.source_type == cur->key.source_type &&
		    node->key.target_type == cur->key.target_type &&
		    node->key.target_class < cur->key.target_class)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम avtab_destroy(काष्ठा avtab *h)
अणु
	पूर्णांक i;
	काष्ठा avtab_node *cur, *temp;

	अगर (!h)
		वापस;

	क्रम (i = 0; i < h->nslot; i++) अणु
		cur = h->htable[i];
		जबतक (cur) अणु
			temp = cur;
			cur = cur->next;
			अगर (temp->key.specअगरied & AVTAB_XPERMS)
				kmem_cache_मुक्त(avtab_xperms_cachep,
						temp->datum.u.xperms);
			kmem_cache_मुक्त(avtab_node_cachep, temp);
		पूर्ण
	पूर्ण
	kvमुक्त(h->htable);
	h->htable = शून्य;
	h->nel = 0;
	h->nslot = 0;
	h->mask = 0;
पूर्ण

व्योम avtab_init(काष्ठा avtab *h)
अणु
	h->htable = शून्य;
	h->nel = 0;
	h->nslot = 0;
	h->mask = 0;
पूर्ण

अटल पूर्णांक avtab_alloc_common(काष्ठा avtab *h, u32 nslot)
अणु
	अगर (!nslot)
		वापस 0;

	h->htable = kvसुस्मृति(nslot, माप(व्योम *), GFP_KERNEL);
	अगर (!h->htable)
		वापस -ENOMEM;

	h->nslot = nslot;
	h->mask = nslot - 1;
	वापस 0;
पूर्ण

पूर्णांक avtab_alloc(काष्ठा avtab *h, u32 nrules)
अणु
	पूर्णांक rc;
	u32 nslot = 0;

	अगर (nrules != 0) अणु
		u32 shअगरt = 1;
		u32 work = nrules >> 3;
		जबतक (work) अणु
			work >>= 1;
			shअगरt++;
		पूर्ण
		nslot = 1 << shअगरt;
		अगर (nslot > MAX_AVTAB_HASH_BUCKETS)
			nslot = MAX_AVTAB_HASH_BUCKETS;

		rc = avtab_alloc_common(h, nslot);
		अगर (rc)
			वापस rc;
	पूर्ण

	pr_debug("SELinux: %d avtab hash slots, %d rules.\n", nslot, nrules);
	वापस 0;
पूर्ण

पूर्णांक avtab_alloc_dup(काष्ठा avtab *new, स्थिर काष्ठा avtab *orig)
अणु
	वापस avtab_alloc_common(new, orig->nslot);
पूर्ण

व्योम avtab_hash_eval(काष्ठा avtab *h, अक्षर *tag)
अणु
	पूर्णांक i, chain_len, slots_used, max_chain_len;
	अचिन्हित दीर्घ दीर्घ chain2_len_sum;
	काष्ठा avtab_node *cur;

	slots_used = 0;
	max_chain_len = 0;
	chain2_len_sum = 0;
	क्रम (i = 0; i < h->nslot; i++) अणु
		cur = h->htable[i];
		अगर (cur) अणु
			slots_used++;
			chain_len = 0;
			जबतक (cur) अणु
				chain_len++;
				cur = cur->next;
			पूर्ण

			अगर (chain_len > max_chain_len)
				max_chain_len = chain_len;
			chain2_len_sum += chain_len * chain_len;
		पूर्ण
	पूर्ण

	pr_debug("SELinux: %s:  %d entries and %d/%d buckets used, "
	       "दीर्घest chain length %d sum of chain length^2 %llu\न",
	       tag, h->nel, slots_used, h->nslot, max_chain_len,
	       chain2_len_sum);
पूर्ण

अटल uपूर्णांक16_t spec_order[] = अणु
	AVTAB_ALLOWED,
	AVTAB_AUDITDENY,
	AVTAB_AUDITALLOW,
	AVTAB_TRANSITION,
	AVTAB_CHANGE,
	AVTAB_MEMBER,
	AVTAB_XPERMS_ALLOWED,
	AVTAB_XPERMS_AUDITALLOW,
	AVTAB_XPERMS_DONTAUDIT
पूर्ण;

पूर्णांक avtab_पढ़ो_item(काष्ठा avtab *a, व्योम *fp, काष्ठा policydb *pol,
		    पूर्णांक (*insertf)(काष्ठा avtab *a, काष्ठा avtab_key *k,
				   काष्ठा avtab_datum *d, व्योम *p),
		    व्योम *p)
अणु
	__le16 buf16[4];
	u16 enabled;
	u32 items, items2, val, vers = pol->policyvers;
	काष्ठा avtab_key key;
	काष्ठा avtab_datum datum;
	काष्ठा avtab_extended_perms xperms;
	__le32 buf32[ARRAY_SIZE(xperms.perms.p)];
	पूर्णांक i, rc;
	अचिन्हित set;

	स_रखो(&key, 0, माप(काष्ठा avtab_key));
	स_रखो(&datum, 0, माप(काष्ठा avtab_datum));

	अगर (vers < POLICYDB_VERSION_AVTAB) अणु
		rc = next_entry(buf32, fp, माप(u32));
		अगर (rc) अणु
			pr_err("SELinux: avtab: truncated entry\n");
			वापस rc;
		पूर्ण
		items2 = le32_to_cpu(buf32[0]);
		अगर (items2 > ARRAY_SIZE(buf32)) अणु
			pr_err("SELinux: avtab: entry overflow\n");
			वापस -EINVAL;

		पूर्ण
		rc = next_entry(buf32, fp, माप(u32)*items2);
		अगर (rc) अणु
			pr_err("SELinux: avtab: truncated entry\n");
			वापस rc;
		पूर्ण
		items = 0;

		val = le32_to_cpu(buf32[items++]);
		key.source_type = (u16)val;
		अगर (key.source_type != val) अणु
			pr_err("SELinux: avtab: truncated source type\n");
			वापस -EINVAL;
		पूर्ण
		val = le32_to_cpu(buf32[items++]);
		key.target_type = (u16)val;
		अगर (key.target_type != val) अणु
			pr_err("SELinux: avtab: truncated target type\n");
			वापस -EINVAL;
		पूर्ण
		val = le32_to_cpu(buf32[items++]);
		key.target_class = (u16)val;
		अगर (key.target_class != val) अणु
			pr_err("SELinux: avtab: truncated target class\n");
			वापस -EINVAL;
		पूर्ण

		val = le32_to_cpu(buf32[items++]);
		enabled = (val & AVTAB_ENABLED_OLD) ? AVTAB_ENABLED : 0;

		अगर (!(val & (AVTAB_AV | AVTAB_TYPE))) अणु
			pr_err("SELinux: avtab: null entry\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((val & AVTAB_AV) &&
		    (val & AVTAB_TYPE)) अणु
			pr_err("SELinux: avtab: entry has both access vectors and types\n");
			वापस -EINVAL;
		पूर्ण
		अगर (val & AVTAB_XPERMS) अणु
			pr_err("SELinux: avtab: entry has extended permissions\n");
			वापस -EINVAL;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(spec_order); i++) अणु
			अगर (val & spec_order[i]) अणु
				key.specअगरied = spec_order[i] | enabled;
				datum.u.data = le32_to_cpu(buf32[items++]);
				rc = insertf(a, &key, &datum, p);
				अगर (rc)
					वापस rc;
			पूर्ण
		पूर्ण

		अगर (items != items2) अणु
			pr_err("SELinux: avtab: entry only had %d items, expected %d\n",
			       items2, items);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	rc = next_entry(buf16, fp, माप(u16)*4);
	अगर (rc) अणु
		pr_err("SELinux: avtab: truncated entry\n");
		वापस rc;
	पूर्ण

	items = 0;
	key.source_type = le16_to_cpu(buf16[items++]);
	key.target_type = le16_to_cpu(buf16[items++]);
	key.target_class = le16_to_cpu(buf16[items++]);
	key.specअगरied = le16_to_cpu(buf16[items++]);

	अगर (!policydb_type_isvalid(pol, key.source_type) ||
	    !policydb_type_isvalid(pol, key.target_type) ||
	    !policydb_class_isvalid(pol, key.target_class)) अणु
		pr_err("SELinux: avtab: invalid type or class\n");
		वापस -EINVAL;
	पूर्ण

	set = 0;
	क्रम (i = 0; i < ARRAY_SIZE(spec_order); i++) अणु
		अगर (key.specअगरied & spec_order[i])
			set++;
	पूर्ण
	अगर (!set || set > 1) अणु
		pr_err("SELinux:  avtab:  more than one specifier\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((vers < POLICYDB_VERSION_XPERMS_IOCTL) &&
			(key.specअगरied & AVTAB_XPERMS)) अणु
		pr_err("SELinux:  avtab:  policy version %u does not "
				"support extended permissions rules and one "
				"was specified\n", vers);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (key.specअगरied & AVTAB_XPERMS) अणु
		स_रखो(&xperms, 0, माप(काष्ठा avtab_extended_perms));
		rc = next_entry(&xperms.specअगरied, fp, माप(u8));
		अगर (rc) अणु
			pr_err("SELinux: avtab: truncated entry\n");
			वापस rc;
		पूर्ण
		rc = next_entry(&xperms.driver, fp, माप(u8));
		अगर (rc) अणु
			pr_err("SELinux: avtab: truncated entry\n");
			वापस rc;
		पूर्ण
		rc = next_entry(buf32, fp, माप(u32)*ARRAY_SIZE(xperms.perms.p));
		अगर (rc) अणु
			pr_err("SELinux: avtab: truncated entry\n");
			वापस rc;
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(xperms.perms.p); i++)
			xperms.perms.p[i] = le32_to_cpu(buf32[i]);
		datum.u.xperms = &xperms;
	पूर्ण अन्यथा अणु
		rc = next_entry(buf32, fp, माप(u32));
		अगर (rc) अणु
			pr_err("SELinux: avtab: truncated entry\n");
			वापस rc;
		पूर्ण
		datum.u.data = le32_to_cpu(*buf32);
	पूर्ण
	अगर ((key.specअगरied & AVTAB_TYPE) &&
	    !policydb_type_isvalid(pol, datum.u.data)) अणु
		pr_err("SELinux: avtab: invalid type\n");
		वापस -EINVAL;
	पूर्ण
	वापस insertf(a, &key, &datum, p);
पूर्ण

अटल पूर्णांक avtab_insertf(काष्ठा avtab *a, काष्ठा avtab_key *k,
			 काष्ठा avtab_datum *d, व्योम *p)
अणु
	वापस avtab_insert(a, k, d);
पूर्ण

पूर्णांक avtab_पढ़ो(काष्ठा avtab *a, व्योम *fp, काष्ठा policydb *pol)
अणु
	पूर्णांक rc;
	__le32 buf[1];
	u32 nel, i;


	rc = next_entry(buf, fp, माप(u32));
	अगर (rc < 0) अणु
		pr_err("SELinux: avtab: truncated table\n");
		जाओ bad;
	पूर्ण
	nel = le32_to_cpu(buf[0]);
	अगर (!nel) अणु
		pr_err("SELinux: avtab: table is empty\n");
		rc = -EINVAL;
		जाओ bad;
	पूर्ण

	rc = avtab_alloc(a, nel);
	अगर (rc)
		जाओ bad;

	क्रम (i = 0; i < nel; i++) अणु
		rc = avtab_पढ़ो_item(a, fp, pol, avtab_insertf, शून्य);
		अगर (rc) अणु
			अगर (rc == -ENOMEM)
				pr_err("SELinux: avtab: out of memory\n");
			अन्यथा अगर (rc == -EEXIST)
				pr_err("SELinux: avtab: duplicate entry\n");

			जाओ bad;
		पूर्ण
	पूर्ण

	rc = 0;
out:
	वापस rc;

bad:
	avtab_destroy(a);
	जाओ out;
पूर्ण

पूर्णांक avtab_ग_लिखो_item(काष्ठा policydb *p, काष्ठा avtab_node *cur, व्योम *fp)
अणु
	__le16 buf16[4];
	__le32 buf32[ARRAY_SIZE(cur->datum.u.xperms->perms.p)];
	पूर्णांक rc;
	अचिन्हित पूर्णांक i;

	buf16[0] = cpu_to_le16(cur->key.source_type);
	buf16[1] = cpu_to_le16(cur->key.target_type);
	buf16[2] = cpu_to_le16(cur->key.target_class);
	buf16[3] = cpu_to_le16(cur->key.specअगरied);
	rc = put_entry(buf16, माप(u16), 4, fp);
	अगर (rc)
		वापस rc;

	अगर (cur->key.specअगरied & AVTAB_XPERMS) अणु
		rc = put_entry(&cur->datum.u.xperms->specअगरied, माप(u8), 1, fp);
		अगर (rc)
			वापस rc;
		rc = put_entry(&cur->datum.u.xperms->driver, माप(u8), 1, fp);
		अगर (rc)
			वापस rc;
		क्रम (i = 0; i < ARRAY_SIZE(cur->datum.u.xperms->perms.p); i++)
			buf32[i] = cpu_to_le32(cur->datum.u.xperms->perms.p[i]);
		rc = put_entry(buf32, माप(u32),
				ARRAY_SIZE(cur->datum.u.xperms->perms.p), fp);
	पूर्ण अन्यथा अणु
		buf32[0] = cpu_to_le32(cur->datum.u.data);
		rc = put_entry(buf32, माप(u32), 1, fp);
	पूर्ण
	अगर (rc)
		वापस rc;
	वापस 0;
पूर्ण

पूर्णांक avtab_ग_लिखो(काष्ठा policydb *p, काष्ठा avtab *a, व्योम *fp)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;
	काष्ठा avtab_node *cur;
	__le32 buf[1];

	buf[0] = cpu_to_le32(a->nel);
	rc = put_entry(buf, माप(u32), 1, fp);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < a->nslot; i++) अणु
		क्रम (cur = a->htable[i]; cur;
		     cur = cur->next) अणु
			rc = avtab_ग_लिखो_item(p, cur, fp);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

व्योम __init avtab_cache_init(व्योम)
अणु
	avtab_node_cachep = kmem_cache_create("avtab_node",
					      माप(काष्ठा avtab_node),
					      0, SLAB_PANIC, शून्य);
	avtab_xperms_cachep = kmem_cache_create("avtab_extended_perms",
						माप(काष्ठा avtab_extended_perms),
						0, SLAB_PANIC, शून्य);
पूर्ण
