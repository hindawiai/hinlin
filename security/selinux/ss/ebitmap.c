<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementation of the extensible biपंचांगap type.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
/*
 * Updated: Hewlett-Packard <paul@paul-moore.com>
 *
 *      Added support to import/export the NetLabel category biपंचांगap
 *
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */
/*
 * Updated: KaiGai Kohei <kaigai@ak.jp.nec.com>
 *      Applied standard bit operations to improve biपंचांगap scanning.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jhash.h>
#समावेश <net/netlabel.h>
#समावेश "ebitmap.h"
#समावेश "policydb.h"

#घोषणा BITS_PER_U64	(माप(u64) * 8)

अटल काष्ठा kmem_cache *ebiपंचांगap_node_cachep __ro_after_init;

पूर्णांक ebiपंचांगap_cmp(काष्ठा ebiपंचांगap *e1, काष्ठा ebiपंचांगap *e2)
अणु
	काष्ठा ebiपंचांगap_node *n1, *n2;

	अगर (e1->highbit != e2->highbit)
		वापस 0;

	n1 = e1->node;
	n2 = e2->node;
	जबतक (n1 && n2 &&
	       (n1->startbit == n2->startbit) &&
	       !स_भेद(n1->maps, n2->maps, EBITMAP_SIZE / 8)) अणु
		n1 = n1->next;
		n2 = n2->next;
	पूर्ण

	अगर (n1 || n2)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक ebiपंचांगap_cpy(काष्ठा ebiपंचांगap *dst, काष्ठा ebiपंचांगap *src)
अणु
	काष्ठा ebiपंचांगap_node *n, *new, *prev;

	ebiपंचांगap_init(dst);
	n = src->node;
	prev = शून्य;
	जबतक (n) अणु
		new = kmem_cache_zalloc(ebiपंचांगap_node_cachep, GFP_ATOMIC);
		अगर (!new) अणु
			ebiपंचांगap_destroy(dst);
			वापस -ENOMEM;
		पूर्ण
		new->startbit = n->startbit;
		स_नकल(new->maps, n->maps, EBITMAP_SIZE / 8);
		new->next = शून्य;
		अगर (prev)
			prev->next = new;
		अन्यथा
			dst->node = new;
		prev = new;
		n = n->next;
	पूर्ण

	dst->highbit = src->highbit;
	वापस 0;
पूर्ण

पूर्णांक ebiपंचांगap_and(काष्ठा ebiपंचांगap *dst, काष्ठा ebiपंचांगap *e1, काष्ठा ebiपंचांगap *e2)
अणु
	काष्ठा ebiपंचांगap_node *n;
	पूर्णांक bit, rc;

	ebiपंचांगap_init(dst);

	ebiपंचांगap_क्रम_each_positive_bit(e1, n, bit) अणु
		अगर (ebiपंचांगap_get_bit(e2, bit)) अणु
			rc = ebiपंचांगap_set_bit(dst, bit, 1);
			अगर (rc < 0)
				वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


#अगर_घोषित CONFIG_NETLABEL
/**
 * ebiपंचांगap_netlbl_export - Export an ebiपंचांगap पूर्णांकo a NetLabel category biपंचांगap
 * @ebmap: the ebiपंचांगap to export
 * @caपंचांगap: the NetLabel category biपंचांगap
 *
 * Description:
 * Export a SELinux extensibile biपंचांगap पूर्णांकo a NetLabel category biपंचांगap.
 * Returns zero on success, negative values on error.
 *
 */
पूर्णांक ebiपंचांगap_netlbl_export(काष्ठा ebiपंचांगap *ebmap,
			  काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap)
अणु
	काष्ठा ebiपंचांगap_node *e_iter = ebmap->node;
	अचिन्हित दीर्घ e_map;
	u32 offset;
	अचिन्हित पूर्णांक iter;
	पूर्णांक rc;

	अगर (e_iter == शून्य) अणु
		*caपंचांगap = शून्य;
		वापस 0;
	पूर्ण

	अगर (*caपंचांगap != शून्य)
		netlbl_caपंचांगap_मुक्त(*caपंचांगap);
	*caपंचांगap = शून्य;

	जबतक (e_iter) अणु
		offset = e_iter->startbit;
		क्रम (iter = 0; iter < EBITMAP_UNIT_NUMS; iter++) अणु
			e_map = e_iter->maps[iter];
			अगर (e_map != 0) अणु
				rc = netlbl_caपंचांगap_setदीर्घ(caपंचांगap,
							   offset,
							   e_map,
							   GFP_ATOMIC);
				अगर (rc != 0)
					जाओ netlbl_export_failure;
			पूर्ण
			offset += EBITMAP_UNIT_SIZE;
		पूर्ण
		e_iter = e_iter->next;
	पूर्ण

	वापस 0;

netlbl_export_failure:
	netlbl_caपंचांगap_मुक्त(*caपंचांगap);
	वापस -ENOMEM;
पूर्ण

/**
 * ebiपंचांगap_netlbl_import - Import a NetLabel category biपंचांगap पूर्णांकo an ebiपंचांगap
 * @ebmap: the ebiपंचांगap to import
 * @caपंचांगap: the NetLabel category biपंचांगap
 *
 * Description:
 * Import a NetLabel category biपंचांगap पूर्णांकo a SELinux extensibile biपंचांगap.
 * Returns zero on success, negative values on error.
 *
 */
पूर्णांक ebiपंचांगap_netlbl_import(काष्ठा ebiपंचांगap *ebmap,
			  काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap)
अणु
	पूर्णांक rc;
	काष्ठा ebiपंचांगap_node *e_iter = शून्य;
	काष्ठा ebiपंचांगap_node *e_prev = शून्य;
	u32 offset = 0, idx;
	अचिन्हित दीर्घ biपंचांगap;

	क्रम (;;) अणु
		rc = netlbl_caपंचांगap_getदीर्घ(caपंचांगap, &offset, &biपंचांगap);
		अगर (rc < 0)
			जाओ netlbl_import_failure;
		अगर (offset == (u32)-1)
			वापस 0;

		/* करोn't waste ebiपंचांगap space अगर the netlabel biपंचांगap is empty */
		अगर (biपंचांगap == 0) अणु
			offset += EBITMAP_UNIT_SIZE;
			जारी;
		पूर्ण

		अगर (e_iter == शून्य ||
		    offset >= e_iter->startbit + EBITMAP_SIZE) अणु
			e_prev = e_iter;
			e_iter = kmem_cache_zalloc(ebiपंचांगap_node_cachep, GFP_ATOMIC);
			अगर (e_iter == शून्य)
				जाओ netlbl_import_failure;
			e_iter->startbit = offset - (offset % EBITMAP_SIZE);
			अगर (e_prev == शून्य)
				ebmap->node = e_iter;
			अन्यथा
				e_prev->next = e_iter;
			ebmap->highbit = e_iter->startbit + EBITMAP_SIZE;
		पूर्ण

		/* offset will always be aligned to an अचिन्हित दीर्घ */
		idx = EBITMAP_NODE_INDEX(e_iter, offset);
		e_iter->maps[idx] = biपंचांगap;

		/* next */
		offset += EBITMAP_UNIT_SIZE;
	पूर्ण

	/* NOTE: we should never reach this वापस */
	वापस 0;

netlbl_import_failure:
	ebiपंचांगap_destroy(ebmap);
	वापस -ENOMEM;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */

/*
 * Check to see अगर all the bits set in e2 are also set in e1. Optionally,
 * अगर last_e2bit is non-zero, the highest set bit in e2 cannot exceed
 * last_e2bit.
 */
पूर्णांक ebiपंचांगap_contains(काष्ठा ebiपंचांगap *e1, काष्ठा ebiपंचांगap *e2, u32 last_e2bit)
अणु
	काष्ठा ebiपंचांगap_node *n1, *n2;
	पूर्णांक i;

	अगर (e1->highbit < e2->highbit)
		वापस 0;

	n1 = e1->node;
	n2 = e2->node;

	जबतक (n1 && n2 && (n1->startbit <= n2->startbit)) अणु
		अगर (n1->startbit < n2->startbit) अणु
			n1 = n1->next;
			जारी;
		पूर्ण
		क्रम (i = EBITMAP_UNIT_NUMS - 1; (i >= 0) && !n2->maps[i]; )
			i--;	/* Skip trailing शून्य map entries */
		अगर (last_e2bit && (i >= 0)) अणु
			u32 lastsetbit = n2->startbit + i * EBITMAP_UNIT_SIZE +
					 __fls(n2->maps[i]);
			अगर (lastsetbit > last_e2bit)
				वापस 0;
		पूर्ण

		जबतक (i >= 0) अणु
			अगर ((n1->maps[i] & n2->maps[i]) != n2->maps[i])
				वापस 0;
			i--;
		पूर्ण

		n1 = n1->next;
		n2 = n2->next;
	पूर्ण

	अगर (n2)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक ebiपंचांगap_get_bit(काष्ठा ebiपंचांगap *e, अचिन्हित दीर्घ bit)
अणु
	काष्ठा ebiपंचांगap_node *n;

	अगर (e->highbit < bit)
		वापस 0;

	n = e->node;
	जबतक (n && (n->startbit <= bit)) अणु
		अगर ((n->startbit + EBITMAP_SIZE) > bit)
			वापस ebiपंचांगap_node_get_bit(n, bit);
		n = n->next;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ebiपंचांगap_set_bit(काष्ठा ebiपंचांगap *e, अचिन्हित दीर्घ bit, पूर्णांक value)
अणु
	काष्ठा ebiपंचांगap_node *n, *prev, *new;

	prev = शून्य;
	n = e->node;
	जबतक (n && n->startbit <= bit) अणु
		अगर ((n->startbit + EBITMAP_SIZE) > bit) अणु
			अगर (value) अणु
				ebiपंचांगap_node_set_bit(n, bit);
			पूर्ण अन्यथा अणु
				अचिन्हित पूर्णांक s;

				ebiपंचांगap_node_clr_bit(n, bit);

				s = find_first_bit(n->maps, EBITMAP_SIZE);
				अगर (s < EBITMAP_SIZE)
					वापस 0;

				/* drop this node from the biपंचांगap */
				अगर (!n->next) अणु
					/*
					 * this was the highest map
					 * within the biपंचांगap
					 */
					अगर (prev)
						e->highbit = prev->startbit
							     + EBITMAP_SIZE;
					अन्यथा
						e->highbit = 0;
				पूर्ण
				अगर (prev)
					prev->next = n->next;
				अन्यथा
					e->node = n->next;
				kmem_cache_मुक्त(ebiपंचांगap_node_cachep, n);
			पूर्ण
			वापस 0;
		पूर्ण
		prev = n;
		n = n->next;
	पूर्ण

	अगर (!value)
		वापस 0;

	new = kmem_cache_zalloc(ebiपंचांगap_node_cachep, GFP_ATOMIC);
	अगर (!new)
		वापस -ENOMEM;

	new->startbit = bit - (bit % EBITMAP_SIZE);
	ebiपंचांगap_node_set_bit(new, bit);

	अगर (!n)
		/* this node will be the highest map within the biपंचांगap */
		e->highbit = new->startbit + EBITMAP_SIZE;

	अगर (prev) अणु
		new->next = prev->next;
		prev->next = new;
	पूर्ण अन्यथा अणु
		new->next = e->node;
		e->node = new;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ebiपंचांगap_destroy(काष्ठा ebiपंचांगap *e)
अणु
	काष्ठा ebiपंचांगap_node *n, *temp;

	अगर (!e)
		वापस;

	n = e->node;
	जबतक (n) अणु
		temp = n;
		n = n->next;
		kmem_cache_मुक्त(ebiपंचांगap_node_cachep, temp);
	पूर्ण

	e->highbit = 0;
	e->node = शून्य;
	वापस;
पूर्ण

पूर्णांक ebiपंचांगap_पढ़ो(काष्ठा ebiपंचांगap *e, व्योम *fp)
अणु
	काष्ठा ebiपंचांगap_node *n = शून्य;
	u32 mapunit, count, startbit, index;
	__le32 ebiपंचांगap_start;
	u64 map;
	__le64 mapbits;
	__le32 buf[3];
	पूर्णांक rc, i;

	ebiपंचांगap_init(e);

	rc = next_entry(buf, fp, माप buf);
	अगर (rc < 0)
		जाओ out;

	mapunit = le32_to_cpu(buf[0]);
	e->highbit = le32_to_cpu(buf[1]);
	count = le32_to_cpu(buf[2]);

	अगर (mapunit != BITS_PER_U64) अणु
		pr_err("SELinux: ebitmap: map size %u does not "
		       "match my size %zd (high bit was %d)\n",
		       mapunit, BITS_PER_U64, e->highbit);
		जाओ bad;
	पूर्ण

	/* round up e->highbit */
	e->highbit += EBITMAP_SIZE - 1;
	e->highbit -= (e->highbit % EBITMAP_SIZE);

	अगर (!e->highbit) अणु
		e->node = शून्य;
		जाओ ok;
	पूर्ण

	अगर (e->highbit && !count)
		जाओ bad;

	क्रम (i = 0; i < count; i++) अणु
		rc = next_entry(&ebiपंचांगap_start, fp, माप(u32));
		अगर (rc < 0) अणु
			pr_err("SELinux: ebitmap: truncated map\n");
			जाओ bad;
		पूर्ण
		startbit = le32_to_cpu(ebiपंचांगap_start);

		अगर (startbit & (mapunit - 1)) अणु
			pr_err("SELinux: ebitmap start bit (%d) is "
			       "not a multiple of the map unit size (%u)\n",
			       startbit, mapunit);
			जाओ bad;
		पूर्ण
		अगर (startbit > e->highbit - mapunit) अणु
			pr_err("SELinux: ebitmap start bit (%d) is "
			       "beyond the end of the bitmap (%u)\n",
			       startbit, (e->highbit - mapunit));
			जाओ bad;
		पूर्ण

		अगर (!n || startbit >= n->startbit + EBITMAP_SIZE) अणु
			काष्ठा ebiपंचांगap_node *पंचांगp;
			पंचांगp = kmem_cache_zalloc(ebiपंचांगap_node_cachep, GFP_KERNEL);
			अगर (!पंचांगp) अणु
				pr_err("SELinux: ebitmap: out of memory\n");
				rc = -ENOMEM;
				जाओ bad;
			पूर्ण
			/* round करोwn */
			पंचांगp->startbit = startbit - (startbit % EBITMAP_SIZE);
			अगर (n)
				n->next = पंचांगp;
			अन्यथा
				e->node = पंचांगp;
			n = पंचांगp;
		पूर्ण अन्यथा अगर (startbit <= n->startbit) अणु
			pr_err("SELinux: ebitmap: start bit %d"
			       " comes after start bit %d\n",
			       startbit, n->startbit);
			जाओ bad;
		पूर्ण

		rc = next_entry(&mapbits, fp, माप(u64));
		अगर (rc < 0) अणु
			pr_err("SELinux: ebitmap: truncated map\n");
			जाओ bad;
		पूर्ण
		map = le64_to_cpu(mapbits);

		index = (startbit - n->startbit) / EBITMAP_UNIT_SIZE;
		जबतक (map) अणु
			n->maps[index++] = map & (-1UL);
			map = EBITMAP_SHIFT_UNIT_SIZE(map);
		पूर्ण
	पूर्ण
ok:
	rc = 0;
out:
	वापस rc;
bad:
	अगर (!rc)
		rc = -EINVAL;
	ebiपंचांगap_destroy(e);
	जाओ out;
पूर्ण

पूर्णांक ebiपंचांगap_ग_लिखो(काष्ठा ebiपंचांगap *e, व्योम *fp)
अणु
	काष्ठा ebiपंचांगap_node *n;
	u32 count;
	__le32 buf[3];
	u64 map;
	पूर्णांक bit, last_bit, last_startbit, rc;

	buf[0] = cpu_to_le32(BITS_PER_U64);

	count = 0;
	last_bit = 0;
	last_startbit = -1;
	ebiपंचांगap_क्रम_each_positive_bit(e, n, bit) अणु
		अगर (roundकरोwn(bit, (पूर्णांक)BITS_PER_U64) > last_startbit) अणु
			count++;
			last_startbit = roundकरोwn(bit, BITS_PER_U64);
		पूर्ण
		last_bit = roundup(bit + 1, BITS_PER_U64);
	पूर्ण
	buf[1] = cpu_to_le32(last_bit);
	buf[2] = cpu_to_le32(count);

	rc = put_entry(buf, माप(u32), 3, fp);
	अगर (rc)
		वापस rc;

	map = 0;
	last_startbit = पूर्णांक_न्यून;
	ebiपंचांगap_क्रम_each_positive_bit(e, n, bit) अणु
		अगर (roundकरोwn(bit, (पूर्णांक)BITS_PER_U64) > last_startbit) अणु
			__le64 buf64[1];

			/* this is the very first bit */
			अगर (!map) अणु
				last_startbit = roundकरोwn(bit, BITS_PER_U64);
				map = (u64)1 << (bit - last_startbit);
				जारी;
			पूर्ण

			/* ग_लिखो the last node */
			buf[0] = cpu_to_le32(last_startbit);
			rc = put_entry(buf, माप(u32), 1, fp);
			अगर (rc)
				वापस rc;

			buf64[0] = cpu_to_le64(map);
			rc = put_entry(buf64, माप(u64), 1, fp);
			अगर (rc)
				वापस rc;

			/* set up क्रम the next node */
			map = 0;
			last_startbit = roundकरोwn(bit, BITS_PER_U64);
		पूर्ण
		map |= (u64)1 << (bit - last_startbit);
	पूर्ण
	/* ग_लिखो the last node */
	अगर (map) अणु
		__le64 buf64[1];

		/* ग_लिखो the last node */
		buf[0] = cpu_to_le32(last_startbit);
		rc = put_entry(buf, माप(u32), 1, fp);
		अगर (rc)
			वापस rc;

		buf64[0] = cpu_to_le64(map);
		rc = put_entry(buf64, माप(u64), 1, fp);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

u32 ebiपंचांगap_hash(स्थिर काष्ठा ebiपंचांगap *e, u32 hash)
अणु
	काष्ठा ebiपंचांगap_node *node;

	/* need to change hash even अगर ebiपंचांगap is empty */
	hash = jhash_1word(e->highbit, hash);
	क्रम (node = e->node; node; node = node->next) अणु
		hash = jhash_1word(node->startbit, hash);
		hash = jhash(node->maps, माप(node->maps), hash);
	पूर्ण
	वापस hash;
पूर्ण

व्योम __init ebiपंचांगap_cache_init(व्योम)
अणु
	ebiपंचांगap_node_cachep = kmem_cache_create("ebitmap_node",
							माप(काष्ठा ebiपंचांगap_node),
							0, SLAB_PANIC, शून्य);
पूर्ण
