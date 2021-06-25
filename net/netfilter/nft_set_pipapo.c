<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/* PIPAPO: PIle PAcket POlicies: set क्रम arbitrary concatenations of ranges
 *
 * Copyright (c) 2019-2020 Red Hat GmbH
 *
 * Author: Stefano Brivio <sbrivio@redhat.com>
 */

/**
 * DOC: Theory of Operation
 *
 *
 * Problem
 * -------
 *
 * Match packet bytes against entries composed of ranged or non-ranged packet
 * field specअगरiers, mapping them to arbitrary references. For example:
 *
 * ::
 *
 *               --- fields --->
 *      |    [net],[port],[net]... => [reference]
 *   entries [net],[port],[net]... => [reference]
 *      |    [net],[port],[net]... => [reference]
 *      V    ...
 *
 * where [net] fields can be IP ranges or neपंचांगasks, and [port] fields are port
 * ranges. Arbitrary packet fields can be matched.
 *
 *
 * Algorithm Overview
 * ------------------
 *
 * This algorithm is loosely inspired by [Ligatti 2010], and fundamentally
 * relies on the consideration that every contiguous range in a space of b bits
 * can be converted पूर्णांकo b * 2 neपंचांगasks, from Theorem 3 in [Rottenstreich 2010],
 * as also illustrated in Section 9 of [Kogan 2014].
 *
 * Classअगरication against a number of entries, that require matching given bits
 * of a packet field, is perक्रमmed by grouping those bits in sets of arbitrary
 * size, and classअगरying packet bits one group at a समय.
 *
 * Example:
 *   to match the source port (16 bits) of a packet, we can भागide those 16 bits
 *   in 4 groups of 4 bits each. Given the entry:
 *      0000 0001 0101 1001
 *   and a packet with source port:
 *      0000 0001 1010 1001
 *   first and second groups match, but the third करोesn't. We conclude that the
 *   packet करोesn't match the given entry.
 *
 * Translate the set to a sequence of lookup tables, one per field. Each table
 * has two dimensions: bit groups to be matched क्रम a single packet field, and
 * all the possible values of said groups (buckets). Input entries are
 * represented as one or more rules, depending on the number of composing
 * neपंचांगasks क्रम the given field specअगरier, and a group match is indicated as a
 * set bit, with number corresponding to the rule index, in all the buckets
 * whose value matches the entry क्रम a given group.
 *
 * Rules are mapped between fields through an array of x, n pairs, with each
 * item mapping a matched rule to one or more rules. The position of the pair in
 * the array indicates the matched rule to be mapped to the next field, x
 * indicates the first rule index in the next field, and n the amount of
 * next-field rules the current rule maps to.
 *
 * The mapping array क्रम the last field maps to the desired references.
 *
 * To match, we perक्रमm table lookups using the values of grouped packet bits,
 * and use a sequence of bitwise operations to progressively evaluate rule
 * matching.
 *
 * A stand-alone, reference implementation, also including notes about possible
 * future optimisations, is available at:
 *    https://pipapo.lameexcu.se/
 *
 * Insertion
 * ---------
 *
 * - For each packet field:
 *
 *   - भागide the b packet bits we want to classअगरy पूर्णांकo groups of size t,
 *     obtaining उच्चमान(b / t) groups
 *
 *      Example: match on destination IP address, with t = 4: 32 bits, 8 groups
 *      of 4 bits each
 *
 *   - allocate a lookup table with one column ("bucket") क्रम each possible
 *     value of a group, and with one row क्रम each group
 *
 *      Example: 8 groups, 2^4 buckets:
 *
 * ::
 *
 *                     bucket
 *      group  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *        0
 *        1
 *        2
 *        3
 *        4
 *        5
 *        6
 *        7
 *
 *   - map the bits we want to classअगरy क्रम the current field, क्रम a given
 *     entry, to a single rule क्रम non-ranged and neपंचांगask set items, and to one
 *     or multiple rules क्रम ranges. Ranges are expanded to composing neपंचांगasks
 *     by pipapo_expand().
 *
 *      Example: 2 entries, 10.0.0.5:1024 and 192.168.1.0-192.168.2.1:2048
 *      - rule #0: 10.0.0.5
 *      - rule #1: 192.168.1.0/24
 *      - rule #2: 192.168.2.0/31
 *
 *   - insert references to the rules in the lookup table, selecting buckets
 *     according to bit values of a rule in the given group. This is करोne by
 *     pipapo_insert().
 *
 *      Example: given:
 *      - rule #0: 10.0.0.5 mapping to buckets
 *        < 0 10  0 0   0 0  0 5 >
 *      - rule #1: 192.168.1.0/24 mapping to buckets
 *        < 12 0  10 8  0 1  < 0..15 > < 0..15 > >
 *      - rule #2: 192.168.2.0/31 mapping to buckets
 *        < 12 0  10 8  0 2  0 < 0..1 > >
 *
 *      these bits are set in the lookup table:
 *
 * ::
 *
 *                     bucket
 *      group  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *        0    0                                              1,2
 *        1   1,2                                      0
 *        2    0                                      1,2
 *        3    0                              1,2
 *        4  0,1,2
 *        5    0   1   2
 *        6  0,1,2 1   1   1   1   1   1   1   1   1   1   1   1   1   1   1
 *        7   1,2 1,2  1   1   1  0,1  1   1   1   1   1   1   1   1   1   1
 *
 *   - अगर this is not the last field in the set, fill a mapping array that maps
 *     rules from the lookup table to rules beदीर्घing to the same entry in
 *     the next lookup table, करोne by pipapo_map().
 *
 *     Note that as rules map to contiguous ranges of rules, given how neपंचांगask
 *     expansion and insertion is perक्रमmed, &जोड़ nft_pipapo_map_bucket stores
 *     this inक्रमmation as pairs of first rule index, rule count.
 *
 *      Example: 2 entries, 10.0.0.5:1024 and 192.168.1.0-192.168.2.1:2048,
 *      given lookup table #0 क्रम field 0 (see example above):
 *
 * ::
 *
 *                     bucket
 *      group  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *        0    0                                              1,2
 *        1   1,2                                      0
 *        2    0                                      1,2
 *        3    0                              1,2
 *        4  0,1,2
 *        5    0   1   2
 *        6  0,1,2 1   1   1   1   1   1   1   1   1   1   1   1   1   1   1
 *        7   1,2 1,2  1   1   1  0,1  1   1   1   1   1   1   1   1   1   1
 *
 *      and lookup table #1 क्रम field 1 with:
 *      - rule #0: 1024 mapping to buckets
 *        < 0  0  4  0 >
 *      - rule #1: 2048 mapping to buckets
 *        < 0  0  5  0 >
 *
 * ::
 *
 *                     bucket
 *      group  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *        0   0,1
 *        1   0,1
 *        2                    0   1
 *        3   0,1
 *
 *      we need to map rules क्रम 10.0.0.5 in lookup table #0 (rule #0) to 1024
 *      in lookup table #1 (rule #0) and rules क्रम 192.168.1.0-192.168.2.1
 *      (rules #1, #2) to 2048 in lookup table #2 (rule #1):
 *
 * ::
 *
 *       rule indices in current field: 0    1    2
 *       map to rules in next field:    0    1    1
 *
 *   - अगर this is the last field in the set, fill a mapping array that maps
 *     rules from the last lookup table to element poपूर्णांकers, also करोne by
 *     pipapo_map().
 *
 *     Note that, in this implementation, we have two elements (start, end) क्रम
 *     each entry. The poपूर्णांकer to the end element is stored in this array, and
 *     the poपूर्णांकer to the start element is linked from it.
 *
 *      Example: entry 10.0.0.5:1024 has a corresponding &काष्ठा nft_pipapo_elem
 *      poपूर्णांकer, 0x66, and element क्रम 192.168.1.0-192.168.2.1:2048 is at 0x42.
 *      From the rules of lookup table #1 as mapped above:
 *
 * ::
 *
 *       rule indices in last field:    0    1
 *       map to elements:             0x66  0x42
 *
 *
 * Matching
 * --------
 *
 * We use a result biपंचांगap, with the size of a single lookup table bucket, to
 * represent the matching state that applies at every algorithm step. This is
 * करोne by pipapo_lookup().
 *
 * - For each packet field:
 *
 *   - start with an all-ones result biपंचांगap (res_map in pipapo_lookup())
 *
 *   - perक्रमm a lookup पूर्णांकo the table corresponding to the current field,
 *     क्रम each group, and at every group, AND the current result biपंचांगap with
 *     the value from the lookup table bucket
 *
 * ::
 *
 *      Example: 192.168.1.5 < 12 0  10 8  0 1  0 5 >, with lookup table from
 *      insertion examples.
 *      Lookup table buckets are at least 3 bits wide, we'll assume 8 bits क्रम
 *      convenience in this example. Initial result biपंचांगap is 0xff, the steps
 *      below show the value of the result biपंचांगap after each group is processed:
 *
 *                     bucket
 *      group  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *        0    0                                              1,2
 *        result biपंचांगap is now: 0xff & 0x6 [bucket 12] = 0x6
 *
 *        1   1,2                                      0
 *        result biपंचांगap is now: 0x6 & 0x6 [bucket 0] = 0x6
 *
 *        2    0                                      1,2
 *        result biपंचांगap is now: 0x6 & 0x6 [bucket 10] = 0x6
 *
 *        3    0                              1,2
 *        result biपंचांगap is now: 0x6 & 0x6 [bucket 8] = 0x6
 *
 *        4  0,1,2
 *        result biपंचांगap is now: 0x6 & 0x7 [bucket 0] = 0x6
 *
 *        5    0   1   2
 *        result biपंचांगap is now: 0x6 & 0x2 [bucket 1] = 0x2
 *
 *        6  0,1,2 1   1   1   1   1   1   1   1   1   1   1   1   1   1   1
 *        result biपंचांगap is now: 0x2 & 0x7 [bucket 0] = 0x2
 *
 *        7   1,2 1,2  1   1   1  0,1  1   1   1   1   1   1   1   1   1   1
 *        final result biपंचांगap क्रम this field is: 0x2 & 0x3 [bucket 5] = 0x2
 *
 *   - at the next field, start with a new, all-zeroes result biपंचांगap. For each
 *     bit set in the previous result biपंचांगap, fill the new result biपंचांगap
 *     (fill_map in pipapo_lookup()) with the rule indices from the
 *     corresponding buckets of the mapping field क्रम this field, करोne by
 *     pipapo_refill()
 *
 *      Example: with mapping table from insertion examples, with the current
 *      result biपंचांगap from the previous example, 0x02:
 *
 * ::
 *
 *       rule indices in current field: 0    1    2
 *       map to rules in next field:    0    1    1
 *
 *      the new result biपंचांगap will be 0x02: rule 1 was set, and rule 1 will be
 *      set.
 *
 *      We can now extend this example to cover the second iteration of the step
 *      above (lookup and AND biपंचांगap): assuming the port field is
 *      2048 < 0  0  5  0 >, with starting result biपंचांगap 0x2, and lookup table
 *      क्रम "port" field from pre-computation example:
 *
 * ::
 *
 *                     bucket
 *      group  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *        0   0,1
 *        1   0,1
 *        2                    0   1
 *        3   0,1
 *
 *       operations are: 0x2 & 0x3 [bucket 0] & 0x3 [bucket 0] & 0x2 [bucket 5]
 *       & 0x3 [bucket 0], resulting biपंचांगap is 0x2.
 *
 *   - अगर this is the last field in the set, look up the value from the mapping
 *     array corresponding to the final result biपंचांगap
 *
 *      Example: 0x2 resulting biपंचांगap from 192.168.1.5:2048, mapping array क्रम
 *      last field from insertion example:
 *
 * ::
 *
 *       rule indices in last field:    0    1
 *       map to elements:             0x66  0x42
 *
 *      the matching element is at 0x42.
 *
 *
 * References
 * ----------
 *
 * [Ligatti 2010]
 *      A Packet-classअगरication Algorithm क्रम Arbitrary Biपंचांगask Rules, with
 *      Automatic Time-space Tradeoffs
 *      Jay Ligatti, Josh Kuhn, and Chris Gage.
 *      Proceedings of the IEEE International Conference on Computer
 *      Communication Networks (ICCCN), August 2010.
 *      https://www.cse.usf.edu/~ligatti/papers/grouper-conf.pdf
 *
 * [Rottenstreich 2010]
 *      Worst-Case TCAM Rule Expansion
 *      Ori Rottenstreich and Isaac Keslassy.
 *      2010 Proceedings IEEE INFOCOM, San Diego, CA, 2010.
 *      http://citeseerx.ist.psu.edu/viewकरोc/करोwnload?करोi=10.1.1.212.4592&rep=rep1&type=pdf
 *
 * [Kogan 2014]
 *      SAX-PAC (Scalable And eXpressive PAcket Classअगरication)
 *      Kirill Kogan, Sergey Nikolenko, Ori Rottenstreich, William Culhane,
 *      and Patrick Eugster.
 *      Proceedings of the 2014 ACM conference on SIGCOMM, August 2014.
 *      https://www.sigcomm.org/sites/शेष/files/ccr/papers/2014/August/2619239-2626294.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <uapi/linux/netfilter/nf_tables.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>

#समावेश "nft_set_pipapo_avx2.h"
#समावेश "nft_set_pipapo.h"

/* Current working biपंचांगap index, toggled between field matches */
अटल DEFINE_PER_CPU(bool, nft_pipapo_scratch_index);

/**
 * pipapo_refill() - For each set bit, set bits from selected mapping table item
 * @map:	Biपंचांगap to be scanned क्रम set bits
 * @len:	Length of biपंचांगap in दीर्घs
 * @rules:	Number of rules in field
 * @dst:	Destination biपंचांगap
 * @mt:		Mapping table containing bit set specअगरiers
 * @match_only:	Find a single bit and वापस, करोn't fill
 *
 * Iteration over set bits with __builtin_ctzl(): Daniel Lemire, खुला करोमुख्य.
 *
 * For each bit set in map, select the bucket from mapping table with index
 * corresponding to the position of the bit set. Use start bit and amount of
 * bits specअगरied in bucket to fill region in dst.
 *
 * Return: -1 on no match, bit position on 'match_only', 0 otherwise.
 */
पूर्णांक pipapo_refill(अचिन्हित दीर्घ *map, पूर्णांक len, पूर्णांक rules, अचिन्हित दीर्घ *dst,
		  जोड़ nft_pipapo_map_bucket *mt, bool match_only)
अणु
	अचिन्हित दीर्घ bitset;
	पूर्णांक k, ret = -1;

	क्रम (k = 0; k < len; k++) अणु
		bitset = map[k];
		जबतक (bitset) अणु
			अचिन्हित दीर्घ t = bitset & -bitset;
			पूर्णांक r = __builtin_ctzl(bitset);
			पूर्णांक i = k * BITS_PER_LONG + r;

			अगर (unlikely(i >= rules)) अणु
				map[k] = 0;
				वापस -1;
			पूर्ण

			अगर (match_only) अणु
				biपंचांगap_clear(map, i, 1);
				वापस i;
			पूर्ण

			ret = 0;

			biपंचांगap_set(dst, mt[i].to, mt[i].n);

			bitset ^= t;
		पूर्ण
		map[k] = 0;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nft_pipapo_lookup() - Lookup function
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @key:	nftables API element representation containing key data
 * @ext:	nftables API extension poपूर्णांकer, filled with matching reference
 *
 * For more details, see DOC: Theory of Operation.
 *
 * Return: true on match, false otherwise.
 */
bool nft_pipapo_lookup(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
		       स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	अचिन्हित दीर्घ *res_map, *fill_map;
	u8 genmask = nft_genmask_cur(net);
	स्थिर u8 *rp = (स्थिर u8 *)key;
	काष्ठा nft_pipapo_match *m;
	काष्ठा nft_pipapo_field *f;
	bool map_index;
	पूर्णांक i;

	local_bh_disable();

	map_index = raw_cpu_पढ़ो(nft_pipapo_scratch_index);

	m = rcu_dereference(priv->match);

	अगर (unlikely(!m || !*raw_cpu_ptr(m->scratch)))
		जाओ out;

	res_map  = *raw_cpu_ptr(m->scratch) + (map_index ? m->bsize_max : 0);
	fill_map = *raw_cpu_ptr(m->scratch) + (map_index ? 0 : m->bsize_max);

	स_रखो(res_map, 0xff, m->bsize_max * माप(*res_map));

	nft_pipapo_क्रम_each_field(f, i, m) अणु
		bool last = i == m->field_count - 1;
		पूर्णांक b;

		/* For each bit group: select lookup table bucket depending on
		 * packet bytes value, then AND bucket value
		 */
		अगर (likely(f->bb == 8))
			pipapo_and_field_buckets_8bit(f, res_map, rp);
		अन्यथा
			pipapo_and_field_buckets_4bit(f, res_map, rp);
		NFT_PIPAPO_GROUP_BITS_ARE_8_OR_4;

		rp += f->groups / NFT_PIPAPO_GROUPS_PER_BYTE(f);

		/* Now populate the biपंचांगap क्रम the next field, unless this is
		 * the last field, in which हाल वापस the matched 'ext'
		 * poपूर्णांकer अगर any.
		 *
		 * Now res_map contains the matching biपंचांगap, and fill_map is the
		 * biपंचांगap क्रम the next field.
		 */
next_match:
		b = pipapo_refill(res_map, f->bsize, f->rules, fill_map, f->mt,
				  last);
		अगर (b < 0) अणु
			raw_cpu_ग_लिखो(nft_pipapo_scratch_index, map_index);
			local_bh_enable();

			वापस false;
		पूर्ण

		अगर (last) अणु
			*ext = &f->mt[b].e->ext;
			अगर (unlikely(nft_set_elem_expired(*ext) ||
				     !nft_set_elem_active(*ext, genmask)))
				जाओ next_match;

			/* Last field: we're just वापसing the key without
			 * filling the initial biपंचांगap क्रम the next field, so the
			 * current inactive biपंचांगap is clean and can be reused as
			 * *next* biपंचांगap (not initial) क्रम the next packet.
			 */
			raw_cpu_ग_लिखो(nft_pipapo_scratch_index, map_index);
			local_bh_enable();

			वापस true;
		पूर्ण

		/* Swap biपंचांगap indices: res_map is the initial biपंचांगap क्रम the
		 * next field, and fill_map is guaranteed to be all-zeroes at
		 * this poपूर्णांक.
		 */
		map_index = !map_index;
		swap(res_map, fill_map);

		rp += NFT_PIPAPO_GROUPS_PADDING(f);
	पूर्ण

out:
	local_bh_enable();
	वापस false;
पूर्ण

/**
 * pipapo_get() - Get matching element reference given key data
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @data:	Key data to be matched against existing elements
 * @genmask:	If set, check that element is active in given genmask
 *
 * This is essentially the same as the lookup function, except that it matches
 * key data against the uncommitted copy and करोesn't use pपुनः_स्मृतिated maps क्रम
 * biपंचांगap results.
 *
 * Return: poपूर्णांकer to &काष्ठा nft_pipapo_elem on match, error poपूर्णांकer otherwise.
 */
अटल काष्ठा nft_pipapo_elem *pipapo_get(स्थिर काष्ठा net *net,
					  स्थिर काष्ठा nft_set *set,
					  स्थिर u8 *data, u8 genmask)
अणु
	काष्ठा nft_pipapo_elem *ret = ERR_PTR(-ENOENT);
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	काष्ठा nft_pipapo_match *m = priv->clone;
	अचिन्हित दीर्घ *res_map, *fill_map = शून्य;
	काष्ठा nft_pipapo_field *f;
	पूर्णांक i;

	res_map = kदो_स्मृति_array(m->bsize_max, माप(*res_map), GFP_ATOMIC);
	अगर (!res_map) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	fill_map = kसुस्मृति(m->bsize_max, माप(*res_map), GFP_ATOMIC);
	अगर (!fill_map) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	स_रखो(res_map, 0xff, m->bsize_max * माप(*res_map));

	nft_pipapo_क्रम_each_field(f, i, m) अणु
		bool last = i == m->field_count - 1;
		पूर्णांक b;

		/* For each bit group: select lookup table bucket depending on
		 * packet bytes value, then AND bucket value
		 */
		अगर (f->bb == 8)
			pipapo_and_field_buckets_8bit(f, res_map, data);
		अन्यथा अगर (f->bb == 4)
			pipapo_and_field_buckets_4bit(f, res_map, data);
		अन्यथा
			BUG();

		data += f->groups / NFT_PIPAPO_GROUPS_PER_BYTE(f);

		/* Now populate the biपंचांगap क्रम the next field, unless this is
		 * the last field, in which हाल वापस the matched 'ext'
		 * poपूर्णांकer अगर any.
		 *
		 * Now res_map contains the matching biपंचांगap, and fill_map is the
		 * biपंचांगap क्रम the next field.
		 */
next_match:
		b = pipapo_refill(res_map, f->bsize, f->rules, fill_map, f->mt,
				  last);
		अगर (b < 0)
			जाओ out;

		अगर (last) अणु
			अगर (nft_set_elem_expired(&f->mt[b].e->ext) ||
			    (genmask &&
			     !nft_set_elem_active(&f->mt[b].e->ext, genmask)))
				जाओ next_match;

			ret = f->mt[b].e;
			जाओ out;
		पूर्ण

		data += NFT_PIPAPO_GROUPS_PADDING(f);

		/* Swap biपंचांगap indices: fill_map will be the initial biपंचांगap क्रम
		 * the next field (i.e. the new res_map), and res_map is
		 * guaranteed to be all-zeroes at this poपूर्णांक, पढ़ोy to be filled
		 * according to the next mapping table.
		 */
		swap(res_map, fill_map);
	पूर्ण

out:
	kमुक्त(fill_map);
	kमुक्त(res_map);
	वापस ret;
पूर्ण

/**
 * nft_pipapo_get() - Get matching element reference given key data
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @elem:	nftables API element representation containing key data
 * @flags:	Unused
 */
अटल व्योम *nft_pipapo_get(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			    स्थिर काष्ठा nft_set_elem *elem, अचिन्हित पूर्णांक flags)
अणु
	वापस pipapo_get(net, set, (स्थिर u8 *)elem->key.val.data,
			  nft_genmask_cur(net));
पूर्ण

/**
 * pipapo_resize() - Resize lookup or mapping table, or both
 * @f:		Field containing lookup and mapping tables
 * @old_rules:	Previous amount of rules in field
 * @rules:	New amount of rules
 *
 * Increase, decrease or मुख्यtain tables size depending on new amount of rules,
 * and copy data over. In हाल the new size is smaller, throw away data क्रम
 * highest-numbered rules.
 *
 * Return: 0 on success, -ENOMEM on allocation failure.
 */
अटल पूर्णांक pipapo_resize(काष्ठा nft_pipapo_field *f, पूर्णांक old_rules, पूर्णांक rules)
अणु
	दीर्घ *new_lt = शून्य, *new_p, *old_lt = f->lt, *old_p;
	जोड़ nft_pipapo_map_bucket *new_mt, *old_mt = f->mt;
	माप_प्रकार new_bucket_size, copy;
	पूर्णांक group, bucket;

	new_bucket_size = DIV_ROUND_UP(rules, BITS_PER_LONG);
#अगर_घोषित NFT_PIPAPO_ALIGN
	new_bucket_size = roundup(new_bucket_size,
				  NFT_PIPAPO_ALIGN / माप(*new_lt));
#पूर्ण_अगर

	अगर (new_bucket_size == f->bsize)
		जाओ mt;

	अगर (new_bucket_size > f->bsize)
		copy = f->bsize;
	अन्यथा
		copy = new_bucket_size;

	new_lt = kvzalloc(f->groups * NFT_PIPAPO_BUCKETS(f->bb) *
			  new_bucket_size * माप(*new_lt) +
			  NFT_PIPAPO_ALIGN_HEADROOM,
			  GFP_KERNEL);
	अगर (!new_lt)
		वापस -ENOMEM;

	new_p = NFT_PIPAPO_LT_ALIGN(new_lt);
	old_p = NFT_PIPAPO_LT_ALIGN(old_lt);

	क्रम (group = 0; group < f->groups; group++) अणु
		क्रम (bucket = 0; bucket < NFT_PIPAPO_BUCKETS(f->bb); bucket++) अणु
			स_नकल(new_p, old_p, copy * माप(*new_p));
			new_p += copy;
			old_p += copy;

			अगर (new_bucket_size > f->bsize)
				new_p += new_bucket_size - f->bsize;
			अन्यथा
				old_p += f->bsize - new_bucket_size;
		पूर्ण
	पूर्ण

mt:
	new_mt = kvदो_स्मृति(rules * माप(*new_mt), GFP_KERNEL);
	अगर (!new_mt) अणु
		kvमुक्त(new_lt);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(new_mt, f->mt, min(old_rules, rules) * माप(*new_mt));
	अगर (rules > old_rules) अणु
		स_रखो(new_mt + old_rules, 0,
		       (rules - old_rules) * माप(*new_mt));
	पूर्ण

	अगर (new_lt) अणु
		f->bsize = new_bucket_size;
		NFT_PIPAPO_LT_ASSIGN(f, new_lt);
		kvमुक्त(old_lt);
	पूर्ण

	f->mt = new_mt;
	kvमुक्त(old_mt);

	वापस 0;
पूर्ण

/**
 * pipapo_bucket_set() - Set rule bit in bucket given group and group value
 * @f:		Field containing lookup table
 * @rule:	Rule index
 * @group:	Group index
 * @v:		Value of bit group
 */
अटल व्योम pipapo_bucket_set(काष्ठा nft_pipapo_field *f, पूर्णांक rule, पूर्णांक group,
			      पूर्णांक v)
अणु
	अचिन्हित दीर्घ *pos;

	pos = NFT_PIPAPO_LT_ALIGN(f->lt);
	pos += f->bsize * NFT_PIPAPO_BUCKETS(f->bb) * group;
	pos += f->bsize * v;

	__set_bit(rule, pos);
पूर्ण

/**
 * pipapo_lt_4b_to_8b() - Switch lookup table group width from 4 bits to 8 bits
 * @old_groups:	Number of current groups
 * @bsize:	Size of one bucket, in दीर्घs
 * @old_lt:	Poपूर्णांकer to the current lookup table
 * @new_lt:	Poपूर्णांकer to the new, pre-allocated lookup table
 *
 * Each bucket with index b in the new lookup table, beदीर्घing to group g, is
 * filled with the bit पूर्णांकersection between:
 * - bucket with index given by the upper 4 bits of b, from group g, and
 * - bucket with index given by the lower 4 bits of b, from group g + 1
 *
 * That is, given buckets from the new lookup table N(x, y) and the old lookup
 * table O(x, y), with x bucket index, and y group index:
 *
 *	N(b, g) := O(b / 16, g) & O(b % 16, g + 1)
 *
 * This ensures equivalence of the matching results on lookup. Two examples in
 * pictures:
 *
 *              bucket
 *  group  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 ... 254 255
 *    0                ^
 *    1                |                                                 ^
 *   ...             ( & )                                               |
 *                  /     \                                              |
 *                 /       \                                         .-( & )-.
 *                /  bucket \                                        |       |
 *      group  0 / 1   2   3 \ 4   5   6   7   8   9  10  11  12  13 |14  15 |
 *        0     /             \                                      |       |
 *        1                    \                                     |       |
 *        2                                                          |     --'
 *        3                                                          '-
 *       ...
 */
अटल व्योम pipapo_lt_4b_to_8b(पूर्णांक old_groups, पूर्णांक bsize,
			       अचिन्हित दीर्घ *old_lt, अचिन्हित दीर्घ *new_lt)
अणु
	पूर्णांक g, b, i;

	क्रम (g = 0; g < old_groups / 2; g++) अणु
		पूर्णांक src_g0 = g * 2, src_g1 = g * 2 + 1;

		क्रम (b = 0; b < NFT_PIPAPO_BUCKETS(8); b++) अणु
			पूर्णांक src_b0 = b / NFT_PIPAPO_BUCKETS(4);
			पूर्णांक src_b1 = b % NFT_PIPAPO_BUCKETS(4);
			पूर्णांक src_i0 = src_g0 * NFT_PIPAPO_BUCKETS(4) + src_b0;
			पूर्णांक src_i1 = src_g1 * NFT_PIPAPO_BUCKETS(4) + src_b1;

			क्रम (i = 0; i < bsize; i++) अणु
				*new_lt = old_lt[src_i0 * bsize + i] &
					  old_lt[src_i1 * bsize + i];
				new_lt++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * pipapo_lt_8b_to_4b() - Switch lookup table group width from 8 bits to 4 bits
 * @old_groups:	Number of current groups
 * @bsize:	Size of one bucket, in दीर्घs
 * @old_lt:	Poपूर्णांकer to the current lookup table
 * @new_lt:	Poपूर्णांकer to the new, pre-allocated lookup table
 *
 * Each bucket with index b in the new lookup table, beदीर्घing to group g, is
 * filled with the bit जोड़ of:
 * - all the buckets with index such that the upper four bits of the lower byte
 *   equal b, from group g, with g odd
 * - all the buckets with index such that the lower four bits equal b, from
 *   group g, with g even
 *
 * That is, given buckets from the new lookup table N(x, y) and the old lookup
 * table O(x, y), with x bucket index, and y group index:
 *
 *	- with g odd:  N(b, g) := U(O(x, g) क्रम each x : x = (b & 0xf0) >> 4)
 *	- with g even: N(b, g) := U(O(x, g) क्रम each x : x = b & 0x0f)
 *
 * where U() denotes the arbitrary जोड़ operation (binary OR of n terms). This
 * ensures equivalence of the matching results on lookup.
 */
अटल व्योम pipapo_lt_8b_to_4b(पूर्णांक old_groups, पूर्णांक bsize,
			       अचिन्हित दीर्घ *old_lt, अचिन्हित दीर्घ *new_lt)
अणु
	पूर्णांक g, b, bsrc, i;

	स_रखो(new_lt, 0, old_groups * 2 * NFT_PIPAPO_BUCKETS(4) * bsize *
			  माप(अचिन्हित दीर्घ));

	क्रम (g = 0; g < old_groups * 2; g += 2) अणु
		पूर्णांक src_g = g / 2;

		क्रम (b = 0; b < NFT_PIPAPO_BUCKETS(4); b++) अणु
			क्रम (bsrc = NFT_PIPAPO_BUCKETS(8) * src_g;
			     bsrc < NFT_PIPAPO_BUCKETS(8) * (src_g + 1);
			     bsrc++) अणु
				अगर (((bsrc & 0xf0) >> 4) != b)
					जारी;

				क्रम (i = 0; i < bsize; i++)
					new_lt[i] |= old_lt[bsrc * bsize + i];
			पूर्ण

			new_lt += bsize;
		पूर्ण

		क्रम (b = 0; b < NFT_PIPAPO_BUCKETS(4); b++) अणु
			क्रम (bsrc = NFT_PIPAPO_BUCKETS(8) * src_g;
			     bsrc < NFT_PIPAPO_BUCKETS(8) * (src_g + 1);
			     bsrc++) अणु
				अगर ((bsrc & 0x0f) != b)
					जारी;

				क्रम (i = 0; i < bsize; i++)
					new_lt[i] |= old_lt[bsrc * bsize + i];
			पूर्ण

			new_lt += bsize;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * pipapo_lt_bits_adjust() - Adjust group size क्रम lookup table अगर needed
 * @f:		Field containing lookup table
 */
अटल व्योम pipapo_lt_bits_adjust(काष्ठा nft_pipapo_field *f)
अणु
	अचिन्हित दीर्घ *new_lt;
	पूर्णांक groups, bb;
	माप_प्रकार lt_size;

	lt_size = f->groups * NFT_PIPAPO_BUCKETS(f->bb) * f->bsize *
		  माप(*f->lt);

	अगर (f->bb == NFT_PIPAPO_GROUP_BITS_SMALL_SET &&
	    lt_size > NFT_PIPAPO_LT_SIZE_HIGH) अणु
		groups = f->groups * 2;
		bb = NFT_PIPAPO_GROUP_BITS_LARGE_SET;

		lt_size = groups * NFT_PIPAPO_BUCKETS(bb) * f->bsize *
			  माप(*f->lt);
	पूर्ण अन्यथा अगर (f->bb == NFT_PIPAPO_GROUP_BITS_LARGE_SET &&
		   lt_size < NFT_PIPAPO_LT_SIZE_LOW) अणु
		groups = f->groups / 2;
		bb = NFT_PIPAPO_GROUP_BITS_SMALL_SET;

		lt_size = groups * NFT_PIPAPO_BUCKETS(bb) * f->bsize *
			  माप(*f->lt);

		/* Don't increase group width अगर the resulting lookup table size
		 * would exceed the upper size threshold क्रम a "small" set.
		 */
		अगर (lt_size > NFT_PIPAPO_LT_SIZE_HIGH)
			वापस;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	new_lt = kvzalloc(lt_size + NFT_PIPAPO_ALIGN_HEADROOM, GFP_KERNEL);
	अगर (!new_lt)
		वापस;

	NFT_PIPAPO_GROUP_BITS_ARE_8_OR_4;
	अगर (f->bb == 4 && bb == 8) अणु
		pipapo_lt_4b_to_8b(f->groups, f->bsize,
				   NFT_PIPAPO_LT_ALIGN(f->lt),
				   NFT_PIPAPO_LT_ALIGN(new_lt));
	पूर्ण अन्यथा अगर (f->bb == 8 && bb == 4) अणु
		pipapo_lt_8b_to_4b(f->groups, f->bsize,
				   NFT_PIPAPO_LT_ALIGN(f->lt),
				   NFT_PIPAPO_LT_ALIGN(new_lt));
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	f->groups = groups;
	f->bb = bb;
	kvमुक्त(f->lt);
	NFT_PIPAPO_LT_ASSIGN(f, new_lt);
पूर्ण

/**
 * pipapo_insert() - Insert new rule in field given input key and mask length
 * @f:		Field containing lookup table
 * @k:		Input key क्रम classअगरication, without nftables padding
 * @mask_bits:	Length of mask; matches field length क्रम non-ranged entry
 *
 * Insert a new rule reference in lookup buckets corresponding to k and
 * mask_bits.
 *
 * Return: 1 on success (one rule inserted), negative error code on failure.
 */
अटल पूर्णांक pipapo_insert(काष्ठा nft_pipapo_field *f, स्थिर uपूर्णांक8_t *k,
			 पूर्णांक mask_bits)
अणु
	पूर्णांक rule = f->rules++, group, ret, bit_offset = 0;

	ret = pipapo_resize(f, f->rules - 1, f->rules);
	अगर (ret)
		वापस ret;

	क्रम (group = 0; group < f->groups; group++) अणु
		पूर्णांक i, v;
		u8 mask;

		v = k[group / (BITS_PER_BYTE / f->bb)];
		v &= GENMASK(BITS_PER_BYTE - bit_offset - 1, 0);
		v >>= (BITS_PER_BYTE - bit_offset) - f->bb;

		bit_offset += f->bb;
		bit_offset %= BITS_PER_BYTE;

		अगर (mask_bits >= (group + 1) * f->bb) अणु
			/* Not masked */
			pipapo_bucket_set(f, rule, group, v);
		पूर्ण अन्यथा अगर (mask_bits <= group * f->bb) अणु
			/* Completely masked */
			क्रम (i = 0; i < NFT_PIPAPO_BUCKETS(f->bb); i++)
				pipapo_bucket_set(f, rule, group, i);
		पूर्ण अन्यथा अणु
			/* The mask limit falls on this group */
			mask = GENMASK(f->bb - 1, 0);
			mask >>= mask_bits - group * f->bb;
			क्रम (i = 0; i < NFT_PIPAPO_BUCKETS(f->bb); i++) अणु
				अगर ((i & ~mask) == (v & ~mask))
					pipapo_bucket_set(f, rule, group, i);
			पूर्ण
		पूर्ण
	पूर्ण

	pipapo_lt_bits_adjust(f);

	वापस 1;
पूर्ण

/**
 * pipapo_step_dअगरf() - Check अगर setting @step bit in neपंचांगask would change it
 * @base:	Mask we are expanding
 * @step:	Step bit क्रम given expansion step
 * @len:	Total length of mask space (set and unset bits), bytes
 *
 * Convenience function क्रम mask expansion.
 *
 * Return: true अगर step bit changes mask (i.e. isn't set), false otherwise.
 */
अटल bool pipapo_step_dअगरf(u8 *base, पूर्णांक step, पूर्णांक len)
अणु
	/* Network order, byte-addressed */
#अगर_घोषित __BIG_ENDIAN__
	वापस !(BIT(step % BITS_PER_BYTE) & base[step / BITS_PER_BYTE]);
#अन्यथा
	वापस !(BIT(step % BITS_PER_BYTE) &
		 base[len - 1 - step / BITS_PER_BYTE]);
#पूर्ण_अगर
पूर्ण

/**
 * pipapo_step_after_end() - Check अगर mask exceeds range end with given step
 * @base:	Mask we are expanding
 * @end:	End of range
 * @step:	Step bit क्रम given expansion step, highest bit to be set
 * @len:	Total length of mask space (set and unset bits), bytes
 *
 * Convenience function क्रम mask expansion.
 *
 * Return: true अगर mask exceeds range setting step bits, false otherwise.
 */
अटल bool pipapo_step_after_end(स्थिर u8 *base, स्थिर u8 *end, पूर्णांक step,
				  पूर्णांक len)
अणु
	u8 पंचांगp[NFT_PIPAPO_MAX_BYTES];
	पूर्णांक i;

	स_नकल(पंचांगp, base, len);

	/* Network order, byte-addressed */
	क्रम (i = 0; i <= step; i++)
#अगर_घोषित __BIG_ENDIAN__
		पंचांगp[i / BITS_PER_BYTE] |= BIT(i % BITS_PER_BYTE);
#अन्यथा
		पंचांगp[len - 1 - i / BITS_PER_BYTE] |= BIT(i % BITS_PER_BYTE);
#पूर्ण_अगर

	वापस स_भेद(पंचांगp, end, len) > 0;
पूर्ण

/**
 * pipapo_base_sum() - Sum step bit to given len-sized neपंचांगask base with carry
 * @base:	Neपंचांगask base
 * @step:	Step bit to sum
 * @len:	Neपंचांगask length, bytes
 */
अटल व्योम pipapo_base_sum(u8 *base, पूर्णांक step, पूर्णांक len)
अणु
	bool carry = false;
	पूर्णांक i;

	/* Network order, byte-addressed */
#अगर_घोषित __BIG_ENDIAN__
	क्रम (i = step / BITS_PER_BYTE; i < len; i++) अणु
#अन्यथा
	क्रम (i = len - 1 - step / BITS_PER_BYTE; i >= 0; i--) अणु
#पूर्ण_अगर
		अगर (carry)
			base[i]++;
		अन्यथा
			base[i] += 1 << (step % BITS_PER_BYTE);

		अगर (base[i])
			अवरोध;

		carry = true;
	पूर्ण
पूर्ण

/**
 * pipapo_expand() - Expand to composing neपंचांगasks, insert पूर्णांकo lookup table
 * @f:		Field containing lookup table
 * @start:	Start of range
 * @end:	End of range
 * @len:	Length of value in bits
 *
 * Expand range to composing neपंचांगasks and insert corresponding rule references
 * in lookup buckets.
 *
 * Return: number of inserted rules on success, negative error code on failure.
 */
अटल पूर्णांक pipapo_expand(काष्ठा nft_pipapo_field *f,
			 स्थिर u8 *start, स्थिर u8 *end, पूर्णांक len)
अणु
	पूर्णांक step, masks = 0, bytes = DIV_ROUND_UP(len, BITS_PER_BYTE);
	u8 base[NFT_PIPAPO_MAX_BYTES];

	स_नकल(base, start, bytes);
	जबतक (स_भेद(base, end, bytes) <= 0) अणु
		पूर्णांक err;

		step = 0;
		जबतक (pipapo_step_dअगरf(base, step, bytes)) अणु
			अगर (pipapo_step_after_end(base, end, step, bytes))
				अवरोध;

			step++;
			अगर (step >= len) अणु
				अगर (!masks) अणु
					pipapo_insert(f, base, 0);
					masks = 1;
				पूर्ण
				जाओ out;
			पूर्ण
		पूर्ण

		err = pipapo_insert(f, base, len - step);

		अगर (err < 0)
			वापस err;

		masks++;
		pipapo_base_sum(base, step, bytes);
	पूर्ण
out:
	वापस masks;
पूर्ण

/**
 * pipapo_map() - Insert rules in mapping tables, mapping them between fields
 * @m:		Matching data, including mapping table
 * @map:	Table of rule maps: array of first rule and amount of rules
 *		in next field a given rule maps to, क्रम each field
 * @e:		For last field, nft_set_ext poपूर्णांकer matching rules map to
 */
अटल व्योम pipapo_map(काष्ठा nft_pipapo_match *m,
		       जोड़ nft_pipapo_map_bucket map[NFT_PIPAPO_MAX_FIELDS],
		       काष्ठा nft_pipapo_elem *e)
अणु
	काष्ठा nft_pipapo_field *f;
	पूर्णांक i, j;

	क्रम (i = 0, f = m->f; i < m->field_count - 1; i++, f++) अणु
		क्रम (j = 0; j < map[i].n; j++) अणु
			f->mt[map[i].to + j].to = map[i + 1].to;
			f->mt[map[i].to + j].n = map[i + 1].n;
		पूर्ण
	पूर्ण

	/* Last field: map to ext instead of mapping to next field */
	क्रम (j = 0; j < map[i].n; j++)
		f->mt[map[i].to + j].e = e;
पूर्ण

/**
 * pipapo_पुनः_स्मृति_scratch() - Reallocate scratch maps क्रम partial match results
 * @clone:	Copy of matching data with pending insertions and deletions
 * @bsize_max:	Maximum bucket size, scratch maps cover two buckets
 *
 * Return: 0 on success, -ENOMEM on failure.
 */
अटल पूर्णांक pipapo_पुनः_स्मृति_scratch(काष्ठा nft_pipapo_match *clone,
				  अचिन्हित दीर्घ bsize_max)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		अचिन्हित दीर्घ *scratch;
#अगर_घोषित NFT_PIPAPO_ALIGN
		अचिन्हित दीर्घ *scratch_aligned;
#पूर्ण_अगर

		scratch = kzalloc_node(bsize_max * माप(*scratch) * 2 +
				       NFT_PIPAPO_ALIGN_HEADROOM,
				       GFP_KERNEL, cpu_to_node(i));
		अगर (!scratch) अणु
			/* On failure, there's no need to unकरो previous
			 * allocations: this means that some scratch maps have
			 * a bigger allocated size now (this is only called on
			 * insertion), but the extra space won't be used by any
			 * CPU as new elements are not inserted and m->bsize_max
			 * is not updated.
			 */
			वापस -ENOMEM;
		पूर्ण

		kमुक्त(*per_cpu_ptr(clone->scratch, i));

		*per_cpu_ptr(clone->scratch, i) = scratch;

#अगर_घोषित NFT_PIPAPO_ALIGN
		scratch_aligned = NFT_PIPAPO_LT_ALIGN(scratch);
		*per_cpu_ptr(clone->scratch_aligned, i) = scratch_aligned;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nft_pipapo_insert() - Validate and insert ranged elements
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @elem:	nftables API element representation containing key data
 * @ext2:	Filled with poपूर्णांकer to &काष्ठा nft_set_ext in inserted element
 *
 * Return: 0 on success, error poपूर्णांकer on failure.
 */
अटल पूर्णांक nft_pipapo_insert(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			     स्थिर काष्ठा nft_set_elem *elem,
			     काष्ठा nft_set_ext **ext2)
अणु
	स्थिर काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);
	जोड़ nft_pipapo_map_bucket rulemap[NFT_PIPAPO_MAX_FIELDS];
	स्थिर u8 *start = (स्थिर u8 *)elem->key.val.data, *end;
	काष्ठा nft_pipapo_elem *e = elem->priv, *dup;
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	काष्ठा nft_pipapo_match *m = priv->clone;
	u8 genmask = nft_genmask_next(net);
	काष्ठा nft_pipapo_field *f;
	पूर्णांक i, bsize_max, err = 0;

	अगर (nft_set_ext_exists(ext, NFT_SET_EXT_KEY_END))
		end = (स्थिर u8 *)nft_set_ext_key_end(ext)->data;
	अन्यथा
		end = start;

	dup = pipapo_get(net, set, start, genmask);
	अगर (!IS_ERR(dup)) अणु
		/* Check अगर we alपढ़ोy have the same exact entry */
		स्थिर काष्ठा nft_data *dup_key, *dup_end;

		dup_key = nft_set_ext_key(&dup->ext);
		अगर (nft_set_ext_exists(&dup->ext, NFT_SET_EXT_KEY_END))
			dup_end = nft_set_ext_key_end(&dup->ext);
		अन्यथा
			dup_end = dup_key;

		अगर (!स_भेद(start, dup_key->data, माप(*dup_key->data)) &&
		    !स_भेद(end, dup_end->data, माप(*dup_end->data))) अणु
			*ext2 = &dup->ext;
			वापस -EEXIST;
		पूर्ण

		वापस -ENOTEMPTY;
	पूर्ण

	अगर (PTR_ERR(dup) == -ENOENT) अणु
		/* Look क्रम partially overlapping entries */
		dup = pipapo_get(net, set, end, nft_genmask_next(net));
	पूर्ण

	अगर (PTR_ERR(dup) != -ENOENT) अणु
		अगर (IS_ERR(dup))
			वापस PTR_ERR(dup);
		*ext2 = &dup->ext;
		वापस -ENOTEMPTY;
	पूर्ण

	/* Validate */
	nft_pipapo_क्रम_each_field(f, i, m) अणु
		स्थिर u8 *start_p = start, *end_p = end;

		अगर (f->rules >= (अचिन्हित दीर्घ)NFT_PIPAPO_RULE0_MAX)
			वापस -ENOSPC;

		अगर (स_भेद(start_p, end_p,
			   f->groups / NFT_PIPAPO_GROUPS_PER_BYTE(f)) > 0)
			वापस -EINVAL;

		start_p += NFT_PIPAPO_GROUPS_PADDED_SIZE(f);
		end_p += NFT_PIPAPO_GROUPS_PADDED_SIZE(f);
	पूर्ण

	/* Insert */
	priv->dirty = true;

	bsize_max = m->bsize_max;

	nft_pipapo_क्रम_each_field(f, i, m) अणु
		पूर्णांक ret;

		rulemap[i].to = f->rules;

		ret = स_भेद(start, end,
			     f->groups / NFT_PIPAPO_GROUPS_PER_BYTE(f));
		अगर (!ret)
			ret = pipapo_insert(f, start, f->groups * f->bb);
		अन्यथा
			ret = pipapo_expand(f, start, end, f->groups * f->bb);

		अगर (f->bsize > bsize_max)
			bsize_max = f->bsize;

		rulemap[i].n = ret;

		start += NFT_PIPAPO_GROUPS_PADDED_SIZE(f);
		end += NFT_PIPAPO_GROUPS_PADDED_SIZE(f);
	पूर्ण

	अगर (!*get_cpu_ptr(m->scratch) || bsize_max > m->bsize_max) अणु
		put_cpu_ptr(m->scratch);

		err = pipapo_पुनः_स्मृति_scratch(m, bsize_max);
		अगर (err)
			वापस err;

		m->bsize_max = bsize_max;
	पूर्ण अन्यथा अणु
		put_cpu_ptr(m->scratch);
	पूर्ण

	*ext2 = &e->ext;

	pipapo_map(m, rulemap, e);

	वापस 0;
पूर्ण

/**
 * pipapo_clone() - Clone matching data to create new working copy
 * @old:	Existing matching data
 *
 * Return: copy of matching data passed as 'old', error poपूर्णांकer on failure
 */
अटल काष्ठा nft_pipapo_match *pipapo_clone(काष्ठा nft_pipapo_match *old)
अणु
	काष्ठा nft_pipapo_field *dst, *src;
	काष्ठा nft_pipapo_match *new;
	पूर्णांक i;

	new = kदो_स्मृति(माप(*new) + माप(*dst) * old->field_count,
		      GFP_KERNEL);
	अगर (!new)
		वापस ERR_PTR(-ENOMEM);

	new->field_count = old->field_count;
	new->bsize_max = old->bsize_max;

	new->scratch = alloc_percpu(*new->scratch);
	अगर (!new->scratch)
		जाओ out_scratch;

#अगर_घोषित NFT_PIPAPO_ALIGN
	new->scratch_aligned = alloc_percpu(*new->scratch_aligned);
	अगर (!new->scratch_aligned)
		जाओ out_scratch;
#पूर्ण_अगर

	rcu_head_init(&new->rcu);

	src = old->f;
	dst = new->f;

	क्रम (i = 0; i < old->field_count; i++) अणु
		अचिन्हित दीर्घ *new_lt;

		स_नकल(dst, src, दुरत्व(काष्ठा nft_pipapo_field, lt));

		new_lt = kvzalloc(src->groups * NFT_PIPAPO_BUCKETS(src->bb) *
				  src->bsize * माप(*dst->lt) +
				  NFT_PIPAPO_ALIGN_HEADROOM,
				  GFP_KERNEL);
		अगर (!new_lt)
			जाओ out_lt;

		NFT_PIPAPO_LT_ASSIGN(dst, new_lt);

		स_नकल(NFT_PIPAPO_LT_ALIGN(new_lt),
		       NFT_PIPAPO_LT_ALIGN(src->lt),
		       src->bsize * माप(*dst->lt) *
		       src->groups * NFT_PIPAPO_BUCKETS(src->bb));

		dst->mt = kvदो_स्मृति(src->rules * माप(*src->mt), GFP_KERNEL);
		अगर (!dst->mt)
			जाओ out_mt;

		स_नकल(dst->mt, src->mt, src->rules * माप(*src->mt));
		src++;
		dst++;
	पूर्ण

	वापस new;

out_mt:
	kvमुक्त(dst->lt);
out_lt:
	क्रम (dst--; i > 0; i--) अणु
		kvमुक्त(dst->mt);
		kvमुक्त(dst->lt);
		dst--;
	पूर्ण
#अगर_घोषित NFT_PIPAPO_ALIGN
	मुक्त_percpu(new->scratch_aligned);
#पूर्ण_अगर
out_scratch:
	मुक्त_percpu(new->scratch);
	kमुक्त(new);

	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * pipapo_rules_same_key() - Get number of rules originated from the same entry
 * @f:		Field containing mapping table
 * @first:	Index of first rule in set of rules mapping to same entry
 *
 * Using the fact that all rules in a field that originated from the same entry
 * will map to the same set of rules in the next field, or to the same element
 * reference, वापस the cardinality of the set of rules that originated from
 * the same entry as the rule with index @first, @first rule included.
 *
 * In pictures:
 *				rules
 *	field #0		0    1    2    3    4
 *		map to:		0    1   2-4  2-4  5-9
 *				.    .    .......   . ...
 *				|    |    |    | \   \
 *				|    |    |    |  \   \
 *				|    |    |    |   \   \
 *				'    '    '    '    '   \
 *	in field #1		0    1    2    3    4    5 ...
 *
 * अगर this is called क्रम rule 2 on field #0, it will वापस 3, as also rules 2
 * and 3 in field 0 map to the same set of rules (2, 3, 4) in the next field.
 *
 * For the last field in a set, we can rely on associated entries to map to the
 * same element references.
 *
 * Return: Number of rules that originated from the same entry as @first.
 */
अटल पूर्णांक pipapo_rules_same_key(काष्ठा nft_pipapo_field *f, पूर्णांक first)
अणु
	काष्ठा nft_pipapo_elem *e = शून्य; /* Keep gcc happy */
	पूर्णांक r;

	क्रम (r = first; r < f->rules; r++) अणु
		अगर (r != first && e != f->mt[r].e)
			वापस r - first;

		e = f->mt[r].e;
	पूर्ण

	अगर (r != first)
		वापस r - first;

	वापस 0;
पूर्ण

/**
 * pipapo_unmap() - Remove rules from mapping tables, rक्रमागतber reमुख्यing ones
 * @mt:		Mapping array
 * @rules:	Original amount of rules in mapping table
 * @start:	First rule index to be हटाओd
 * @n:		Amount of rules to be हटाओd
 * @to_offset:	First rule index, in next field, this group of rules maps to
 * @is_last:	If this is the last field, delete reference from mapping array
 *
 * This is used to unmap rules from the mapping table क्रम a single field,
 * मुख्यtaining consistency and compactness क्रम the existing ones.
 *
 * In pictures: let's assume that we want to delete rules 2 and 3 from the
 * following mapping array:
 *
 *                 rules
 *               0      1      2      3      4
 *      map to:  4-10   4-10   11-15  11-15  16-18
 *
 * the result will be:
 *
 *                 rules
 *               0      1      2
 *      map to:  4-10   4-10   11-13
 *
 * क्रम fields beक्रमe the last one. In हाल this is the mapping table क्रम the
 * last field in a set, and rules map to poपूर्णांकers to &काष्ठा nft_pipapo_elem:
 *
 *                      rules
 *                        0      1      2      3      4
 *  element poपूर्णांकers:  0x42   0x42   0x33   0x33   0x44
 *
 * the result will be:
 *
 *                      rules
 *                        0      1      2
 *  element poपूर्णांकers:  0x42   0x42   0x44
 */
अटल व्योम pipapo_unmap(जोड़ nft_pipapo_map_bucket *mt, पूर्णांक rules,
			 पूर्णांक start, पूर्णांक n, पूर्णांक to_offset, bool is_last)
अणु
	पूर्णांक i;

	स_हटाओ(mt + start, mt + start + n, (rules - start - n) * माप(*mt));
	स_रखो(mt + rules - n, 0, n * माप(*mt));

	अगर (is_last)
		वापस;

	क्रम (i = start; i < rules - n; i++)
		mt[i].to -= to_offset;
पूर्ण

/**
 * pipapo_drop() - Delete entry from lookup and mapping tables, given rule map
 * @m:		Matching data
 * @rulemap:	Table of rule maps, arrays of first rule and amount of rules
 *		in next field a given entry maps to, क्रम each field
 *
 * For each rule in lookup table buckets mapping to this set of rules, drop
 * all bits set in lookup table mapping. In pictures, assuming we want to drop
 * rules 0 and 1 from this lookup table:
 *
 *                     bucket
 *      group  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *        0    0                                              1,2
 *        1   1,2                                      0
 *        2    0                                      1,2
 *        3    0                              1,2
 *        4  0,1,2
 *        5    0   1   2
 *        6  0,1,2 1   1   1   1   1   1   1   1   1   1   1   1   1   1   1
 *        7   1,2 1,2  1   1   1  0,1  1   1   1   1   1   1   1   1   1   1
 *
 * rule 2 becomes rule 0, and the result will be:
 *
 *                     bucket
 *      group  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *        0                                                    0
 *        1    0
 *        2                                            0
 *        3                                    0
 *        4    0
 *        5            0
 *        6    0
 *        7    0   0
 *
 * once this is करोne, call unmap() to drop all the corresponding rule references
 * from mapping tables.
 */
अटल व्योम pipapo_drop(काष्ठा nft_pipapo_match *m,
			जोड़ nft_pipapo_map_bucket rulemap[])
अणु
	काष्ठा nft_pipapo_field *f;
	पूर्णांक i;

	nft_pipapo_क्रम_each_field(f, i, m) अणु
		पूर्णांक g;

		क्रम (g = 0; g < f->groups; g++) अणु
			अचिन्हित दीर्घ *pos;
			पूर्णांक b;

			pos = NFT_PIPAPO_LT_ALIGN(f->lt) + g *
			      NFT_PIPAPO_BUCKETS(f->bb) * f->bsize;

			क्रम (b = 0; b < NFT_PIPAPO_BUCKETS(f->bb); b++) अणु
				biपंचांगap_cut(pos, pos, rulemap[i].to,
					   rulemap[i].n,
					   f->bsize * BITS_PER_LONG);

				pos += f->bsize;
			पूर्ण
		पूर्ण

		pipapo_unmap(f->mt, f->rules, rulemap[i].to, rulemap[i].n,
			     rulemap[i + 1].n, i == m->field_count - 1);
		अगर (pipapo_resize(f, f->rules, f->rules - rulemap[i].n)) अणु
			/* We can ignore this, a failure to shrink tables करोwn
			 * करोesn't make tables invalid.
			 */
			;
		पूर्ण
		f->rules -= rulemap[i].n;

		pipapo_lt_bits_adjust(f);
	पूर्ण
पूर्ण

/**
 * pipapo_gc() - Drop expired entries from set, destroy start and end elements
 * @set:	nftables API set representation
 * @m:		Matching data
 */
अटल व्योम pipapo_gc(स्थिर काष्ठा nft_set *set, काष्ठा nft_pipapo_match *m)
अणु
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	पूर्णांक rules_f0, first_rule = 0;
	काष्ठा nft_pipapo_elem *e;

	जबतक ((rules_f0 = pipapo_rules_same_key(m->f, first_rule))) अणु
		जोड़ nft_pipapo_map_bucket rulemap[NFT_PIPAPO_MAX_FIELDS];
		काष्ठा nft_pipapo_field *f;
		पूर्णांक i, start, rules_fx;

		start = first_rule;
		rules_fx = rules_f0;

		nft_pipapo_क्रम_each_field(f, i, m) अणु
			rulemap[i].to = start;
			rulemap[i].n = rules_fx;

			अगर (i < m->field_count - 1) अणु
				rules_fx = f->mt[start].n;
				start = f->mt[start].to;
			पूर्ण
		पूर्ण

		/* Pick the last field, and its last index */
		f--;
		i--;
		e = f->mt[rulemap[i].to].e;
		अगर (nft_set_elem_expired(&e->ext) &&
		    !nft_set_elem_mark_busy(&e->ext)) अणु
			priv->dirty = true;
			pipapo_drop(m, rulemap);

			rcu_barrier();
			nft_set_elem_destroy(set, e, true);

			/* And check again current first rule, which is now the
			 * first we haven't checked.
			 */
		पूर्ण अन्यथा अणु
			first_rule += rules_f0;
		पूर्ण
	पूर्ण

	e = nft_set_catchall_gc(set);
	अगर (e)
		nft_set_elem_destroy(set, e, true);

	priv->last_gc = jअगरfies;
पूर्ण

/**
 * pipapo_मुक्त_fields() - Free per-field tables contained in matching data
 * @m:		Matching data
 */
अटल व्योम pipapo_मुक्त_fields(काष्ठा nft_pipapo_match *m)
अणु
	काष्ठा nft_pipapo_field *f;
	पूर्णांक i;

	nft_pipapo_क्रम_each_field(f, i, m) अणु
		kvमुक्त(f->lt);
		kvमुक्त(f->mt);
	पूर्ण
पूर्ण

/**
 * pipapo_reclaim_match - RCU callback to मुक्त fields from old matching data
 * @rcu:	RCU head
 */
अटल व्योम pipapo_reclaim_match(काष्ठा rcu_head *rcu)
अणु
	काष्ठा nft_pipapo_match *m;
	पूर्णांक i;

	m = container_of(rcu, काष्ठा nft_pipapo_match, rcu);

	क्रम_each_possible_cpu(i)
		kमुक्त(*per_cpu_ptr(m->scratch, i));

#अगर_घोषित NFT_PIPAPO_ALIGN
	मुक्त_percpu(m->scratch_aligned);
#पूर्ण_अगर
	मुक्त_percpu(m->scratch);

	pipapo_मुक्त_fields(m);

	kमुक्त(m);
पूर्ण

/**
 * pipapo_commit() - Replace lookup data with current working copy
 * @set:	nftables API set representation
 *
 * While at it, check अगर we should perक्रमm garbage collection on the working
 * copy beक्रमe committing it क्रम lookup, and करोn't replace the table अगर the
 * working copy करोesn't have pending changes.
 *
 * We also need to create a new working copy क्रम subsequent insertions and
 * deletions.
 */
अटल व्योम pipapo_commit(स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	काष्ठा nft_pipapo_match *new_clone, *old;

	अगर (समय_after_eq(jअगरfies, priv->last_gc + nft_set_gc_पूर्णांकerval(set)))
		pipapo_gc(set, priv->clone);

	अगर (!priv->dirty)
		वापस;

	new_clone = pipapo_clone(priv->clone);
	अगर (IS_ERR(new_clone))
		वापस;

	priv->dirty = false;

	old = rcu_access_poपूर्णांकer(priv->match);
	rcu_assign_poपूर्णांकer(priv->match, priv->clone);
	अगर (old)
		call_rcu(&old->rcu, pipapo_reclaim_match);

	priv->clone = new_clone;
पूर्ण

/**
 * nft_pipapo_activate() - Mark element reference as active given key, commit
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @elem:	nftables API element representation containing key data
 *
 * On insertion, elements are added to a copy of the matching data currently
 * in use क्रम lookups, and not directly inserted पूर्णांकo current lookup data, so
 * we'll take care of that by calling pipapo_commit() here. Both
 * nft_pipapo_insert() and nft_pipapo_activate() are called once क्रम each
 * element, hence we can't purpose either one as a real commit operation.
 */
अटल व्योम nft_pipapo_activate(स्थिर काष्ठा net *net,
				स्थिर काष्ठा nft_set *set,
				स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_pipapo_elem *e;

	e = pipapo_get(net, set, (स्थिर u8 *)elem->key.val.data, 0);
	अगर (IS_ERR(e))
		वापस;

	nft_set_elem_change_active(net, set, &e->ext);
	nft_set_elem_clear_busy(&e->ext);

	pipapo_commit(set);
पूर्ण

/**
 * pipapo_deactivate() - Check that element is in set, mark as inactive
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @data:	Input key data
 * @ext:	nftables API extension poपूर्णांकer, used to check क्रम end element
 *
 * This is a convenience function that can be called from both
 * nft_pipapo_deactivate() and nft_pipapo_flush(), as they are in fact the same
 * operation.
 *
 * Return: deactivated element अगर found, शून्य otherwise.
 */
अटल व्योम *pipapo_deactivate(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			       स्थिर u8 *data, स्थिर काष्ठा nft_set_ext *ext)
अणु
	काष्ठा nft_pipapo_elem *e;

	e = pipapo_get(net, set, data, nft_genmask_next(net));
	अगर (IS_ERR(e))
		वापस शून्य;

	nft_set_elem_change_active(net, set, &e->ext);

	वापस e;
पूर्ण

/**
 * nft_pipapo_deactivate() - Call pipapo_deactivate() to make element inactive
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @elem:	nftables API element representation containing key data
 *
 * Return: deactivated element अगर found, शून्य otherwise.
 */
अटल व्योम *nft_pipapo_deactivate(स्थिर काष्ठा net *net,
				   स्थिर काष्ठा nft_set *set,
				   स्थिर काष्ठा nft_set_elem *elem)
अणु
	स्थिर काष्ठा nft_set_ext *ext = nft_set_elem_ext(set, elem->priv);

	वापस pipapo_deactivate(net, set, (स्थिर u8 *)elem->key.val.data, ext);
पूर्ण

/**
 * nft_pipapo_flush() - Call pipapo_deactivate() to make element inactive
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @elem:	nftables API element representation containing key data
 *
 * This is functionally the same as nft_pipapo_deactivate(), with a slightly
 * dअगरferent पूर्णांकerface, and it's also called once क्रम each element in a set
 * being flushed, so we can't implement, strictly speaking, a flush operation,
 * which would otherwise be as simple as allocating an empty copy of the
 * matching data.
 *
 * Note that we could in theory करो that, mark the set as flushed, and ignore
 * subsequent calls, but we would leak all the elements after the first one,
 * because they wouldn't then be मुक्तd as result of API calls.
 *
 * Return: true अगर element was found and deactivated.
 */
अटल bool nft_pipapo_flush(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			     व्योम *elem)
अणु
	काष्ठा nft_pipapo_elem *e = elem;

	वापस pipapo_deactivate(net, set, (स्थिर u8 *)nft_set_ext_key(&e->ext),
				 &e->ext);
पूर्ण

/**
 * pipapo_get_boundaries() - Get byte पूर्णांकerval क्रम associated rules
 * @f:		Field including lookup table
 * @first_rule:	First rule (lowest index)
 * @rule_count:	Number of associated rules
 * @left:	Byte expression क्रम left boundary (start of range)
 * @right:	Byte expression क्रम right boundary (end of range)
 *
 * Given the first rule and amount of rules that originated from the same entry,
 * build the original range associated with the entry, and calculate the length
 * of the originating neपंचांगask.
 *
 * In pictures:
 *
 *                     bucket
 *      group  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
 *        0                                                   1,2
 *        1   1,2
 *        2                                           1,2
 *        3                                   1,2
 *        4   1,2
 *        5        1   2
 *        6   1,2  1   1   1   1   1   1   1   1   1   1   1   1   1   1   1
 *        7   1,2 1,2  1   1   1   1   1   1   1   1   1   1   1   1   1   1
 *
 * this is the lookup table corresponding to the IPv4 range
 * 192.168.1.0-192.168.2.1, which was expanded to the two composing neपंचांगasks,
 * rule #1: 192.168.1.0/24, and rule #2: 192.168.2.0/31.
 *
 * This function fills @left and @right with the byte values of the lefपंचांगost
 * and righपंचांगost bucket indices क्रम the lowest and highest rule indices,
 * respectively. If @first_rule is 1 and @rule_count is 2, we obtain, in
 * nibbles:
 *   left:  < 12, 0, 10, 8, 0, 1, 0, 0 >
 *   right: < 12, 0, 10, 8, 0, 2, 2, 1 >
 * corresponding to bytes:
 *   left:  < 192, 168, 1, 0 >
 *   right: < 192, 168, 2, 1 >
 * with mask length irrelevant here, unused on वापस, as the range is alपढ़ोy
 * defined by its start and end poपूर्णांकs. The mask length is relevant क्रम a single
 * ranged entry instead: अगर @first_rule is 1 and @rule_count is 1, we ignore
 * rule 2 above: @left becomes < 192, 168, 1, 0 >, @right becomes
 * < 192, 168, 1, 255 >, and the mask length, calculated from the distances
 * between lefपंचांगost and righपंचांगost bucket indices क्रम each group, would be 24.
 *
 * Return: mask length, in bits.
 */
अटल पूर्णांक pipapo_get_boundaries(काष्ठा nft_pipapo_field *f, पूर्णांक first_rule,
				 पूर्णांक rule_count, u8 *left, u8 *right)
अणु
	पूर्णांक g, mask_len = 0, bit_offset = 0;
	u8 *l = left, *r = right;

	क्रम (g = 0; g < f->groups; g++) अणु
		पूर्णांक b, x0, x1;

		x0 = -1;
		x1 = -1;
		क्रम (b = 0; b < NFT_PIPAPO_BUCKETS(f->bb); b++) अणु
			अचिन्हित दीर्घ *pos;

			pos = NFT_PIPAPO_LT_ALIGN(f->lt) +
			      (g * NFT_PIPAPO_BUCKETS(f->bb) + b) * f->bsize;
			अगर (test_bit(first_rule, pos) && x0 == -1)
				x0 = b;
			अगर (test_bit(first_rule + rule_count - 1, pos))
				x1 = b;
		पूर्ण

		*l |= x0 << (BITS_PER_BYTE - f->bb - bit_offset);
		*r |= x1 << (BITS_PER_BYTE - f->bb - bit_offset);

		bit_offset += f->bb;
		अगर (bit_offset >= BITS_PER_BYTE) अणु
			bit_offset %= BITS_PER_BYTE;
			l++;
			r++;
		पूर्ण

		अगर (x1 - x0 == 0)
			mask_len += 4;
		अन्यथा अगर (x1 - x0 == 1)
			mask_len += 3;
		अन्यथा अगर (x1 - x0 == 3)
			mask_len += 2;
		अन्यथा अगर (x1 - x0 == 7)
			mask_len += 1;
	पूर्ण

	वापस mask_len;
पूर्ण

/**
 * pipapo_match_field() - Match rules against byte ranges
 * @f:		Field including the lookup table
 * @first_rule:	First of associated rules originating from same entry
 * @rule_count:	Amount of associated rules
 * @start:	Start of range to be matched
 * @end:	End of range to be matched
 *
 * Return: true on match, false otherwise.
 */
अटल bool pipapo_match_field(काष्ठा nft_pipapo_field *f,
			       पूर्णांक first_rule, पूर्णांक rule_count,
			       स्थिर u8 *start, स्थिर u8 *end)
अणु
	u8 right[NFT_PIPAPO_MAX_BYTES] = अणु 0 पूर्ण;
	u8 left[NFT_PIPAPO_MAX_BYTES] = अणु 0 पूर्ण;

	pipapo_get_boundaries(f, first_rule, rule_count, left, right);

	वापस !स_भेद(start, left,
		       f->groups / NFT_PIPAPO_GROUPS_PER_BYTE(f)) &&
	       !स_भेद(end, right, f->groups / NFT_PIPAPO_GROUPS_PER_BYTE(f));
पूर्ण

/**
 * nft_pipapo_हटाओ() - Remove element given key, commit
 * @net:	Network namespace
 * @set:	nftables API set representation
 * @elem:	nftables API element representation containing key data
 *
 * Similarly to nft_pipapo_activate(), this is used as commit operation by the
 * API, but it's called once per element in the pending transaction, so we can't
 * implement this as a single commit operation. Closest we can get is to हटाओ
 * the matched element here, अगर any, and commit the updated matching data.
 */
अटल व्योम nft_pipapo_हटाओ(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			      स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	काष्ठा nft_pipapo_match *m = priv->clone;
	काष्ठा nft_pipapo_elem *e = elem->priv;
	पूर्णांक rules_f0, first_rule = 0;
	स्थिर u8 *data;

	data = (स्थिर u8 *)nft_set_ext_key(&e->ext);

	e = pipapo_get(net, set, data, 0);
	अगर (IS_ERR(e))
		वापस;

	जबतक ((rules_f0 = pipapo_rules_same_key(m->f, first_rule))) अणु
		जोड़ nft_pipapo_map_bucket rulemap[NFT_PIPAPO_MAX_FIELDS];
		स्थिर u8 *match_start, *match_end;
		काष्ठा nft_pipapo_field *f;
		पूर्णांक i, start, rules_fx;

		match_start = data;
		match_end = (स्थिर u8 *)nft_set_ext_key_end(&e->ext)->data;

		start = first_rule;
		rules_fx = rules_f0;

		nft_pipapo_क्रम_each_field(f, i, m) अणु
			अगर (!pipapo_match_field(f, start, rules_fx,
						match_start, match_end))
				अवरोध;

			rulemap[i].to = start;
			rulemap[i].n = rules_fx;

			rules_fx = f->mt[start].n;
			start = f->mt[start].to;

			match_start += NFT_PIPAPO_GROUPS_PADDED_SIZE(f);
			match_end += NFT_PIPAPO_GROUPS_PADDED_SIZE(f);
		पूर्ण

		अगर (i == m->field_count) अणु
			priv->dirty = true;
			pipapo_drop(m, rulemap);
			pipapo_commit(set);
			वापस;
		पूर्ण

		first_rule += rules_f0;
	पूर्ण
पूर्ण

/**
 * nft_pipapo_walk() - Walk over elements
 * @ctx:	nftables API context
 * @set:	nftables API set representation
 * @iter:	Iterator
 *
 * As elements are referenced in the mapping array क्रम the last field, directly
 * scan that array: there's no need to follow rule mappings from the first
 * field.
 */
अटल व्योम nft_pipapo_walk(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			    काष्ठा nft_set_iter *iter)
अणु
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	काष्ठा nft_pipapo_match *m;
	काष्ठा nft_pipapo_field *f;
	पूर्णांक i, r;

	rcu_पढ़ो_lock();
	m = rcu_dereference(priv->match);

	अगर (unlikely(!m))
		जाओ out;

	क्रम (i = 0, f = m->f; i < m->field_count - 1; i++, f++)
		;

	क्रम (r = 0; r < f->rules; r++) अणु
		काष्ठा nft_pipapo_elem *e;
		काष्ठा nft_set_elem elem;

		अगर (r < f->rules - 1 && f->mt[r + 1].e == f->mt[r].e)
			जारी;

		अगर (iter->count < iter->skip)
			जाओ cont;

		e = f->mt[r].e;
		अगर (nft_set_elem_expired(&e->ext))
			जाओ cont;

		elem.priv = e;

		iter->err = iter->fn(ctx, set, iter, &elem);
		अगर (iter->err < 0)
			जाओ out;

cont:
		iter->count++;
	पूर्ण

out:
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * nft_pipapo_privsize() - Return the size of निजी data क्रम the set
 * @nla:	netlink attributes, ignored as size करोesn't depend on them
 * @desc:	Set description, ignored as size करोesn't depend on it
 *
 * Return: size of निजी data क्रम this set implementation, in bytes
 */
अटल u64 nft_pipapo_privsize(स्थिर काष्ठा nlattr * स्थिर nla[],
			       स्थिर काष्ठा nft_set_desc *desc)
अणु
	वापस माप(काष्ठा nft_pipapo);
पूर्ण

/**
 * nft_pipapo_estimate() - Set size, space and lookup complनिकासy
 * @desc:	Set description, element count and field description used
 * @features:	Flags: NFT_SET_INTERVAL needs to be there
 * @est:	Storage क्रम estimation data
 *
 * Return: true अगर set description is compatible, false otherwise
 */
अटल bool nft_pipapo_estimate(स्थिर काष्ठा nft_set_desc *desc, u32 features,
				काष्ठा nft_set_estimate *est)
अणु
	अगर (!(features & NFT_SET_INTERVAL) ||
	    desc->field_count < NFT_PIPAPO_MIN_FIELDS)
		वापस false;

	est->size = pipapo_estimate_size(desc);
	अगर (!est->size)
		वापस false;

	est->lookup = NFT_SET_CLASS_O_LOG_N;

	est->space = NFT_SET_CLASS_O_N;

	वापस true;
पूर्ण

/**
 * nft_pipapo_init() - Initialise data क्रम a set instance
 * @set:	nftables API set representation
 * @desc:	Set description
 * @nla:	netlink attributes
 *
 * Validate number and size of fields passed as NFTA_SET_DESC_CONCAT netlink
 * attributes, initialise पूर्णांकernal set parameters, current instance of matching
 * data and a copy क्रम subsequent insertions.
 *
 * Return: 0 on success, negative error code on failure.
 */
अटल पूर्णांक nft_pipapo_init(स्थिर काष्ठा nft_set *set,
			   स्थिर काष्ठा nft_set_desc *desc,
			   स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	काष्ठा nft_pipapo_match *m;
	काष्ठा nft_pipapo_field *f;
	पूर्णांक err, i, field_count;

	field_count = desc->field_count ? : 1;

	अगर (field_count > NFT_PIPAPO_MAX_FIELDS)
		वापस -EINVAL;

	m = kदो_स्मृति(माप(*priv->match) + माप(*f) * field_count,
		    GFP_KERNEL);
	अगर (!m)
		वापस -ENOMEM;

	m->field_count = field_count;
	m->bsize_max = 0;

	m->scratch = alloc_percpu(अचिन्हित दीर्घ *);
	अगर (!m->scratch) अणु
		err = -ENOMEM;
		जाओ out_scratch;
	पूर्ण
	क्रम_each_possible_cpu(i)
		*per_cpu_ptr(m->scratch, i) = शून्य;

#अगर_घोषित NFT_PIPAPO_ALIGN
	m->scratch_aligned = alloc_percpu(अचिन्हित दीर्घ *);
	अगर (!m->scratch_aligned) अणु
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	क्रम_each_possible_cpu(i)
		*per_cpu_ptr(m->scratch_aligned, i) = शून्य;
#पूर्ण_अगर

	rcu_head_init(&m->rcu);

	nft_pipapo_क्रम_each_field(f, i, m) अणु
		पूर्णांक len = desc->field_len[i] ? : set->klen;

		f->bb = NFT_PIPAPO_GROUP_BITS_INIT;
		f->groups = len * NFT_PIPAPO_GROUPS_PER_BYTE(f);

		priv->width += round_up(len, माप(u32));

		f->bsize = 0;
		f->rules = 0;
		NFT_PIPAPO_LT_ASSIGN(f, शून्य);
		f->mt = शून्य;
	पूर्ण

	/* Create an initial clone of matching data क्रम next insertion */
	priv->clone = pipapo_clone(m);
	अगर (IS_ERR(priv->clone)) अणु
		err = PTR_ERR(priv->clone);
		जाओ out_मुक्त;
	पूर्ण

	priv->dirty = false;

	rcu_assign_poपूर्णांकer(priv->match, m);

	वापस 0;

out_मुक्त:
#अगर_घोषित NFT_PIPAPO_ALIGN
	मुक्त_percpu(m->scratch_aligned);
#पूर्ण_अगर
	मुक्त_percpu(m->scratch);
out_scratch:
	kमुक्त(m);

	वापस err;
पूर्ण

/**
 * nft_pipapo_destroy() - Free निजी data क्रम set and all committed elements
 * @set:	nftables API set representation
 */
अटल व्योम nft_pipapo_destroy(स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_pipapo *priv = nft_set_priv(set);
	काष्ठा nft_pipapo_match *m;
	काष्ठा nft_pipapo_field *f;
	पूर्णांक i, r, cpu;

	m = rcu_dereference_रक्षित(priv->match, true);
	अगर (m) अणु
		rcu_barrier();

		क्रम (i = 0, f = m->f; i < m->field_count - 1; i++, f++)
			;

		क्रम (r = 0; r < f->rules; r++) अणु
			काष्ठा nft_pipapo_elem *e;

			अगर (r < f->rules - 1 && f->mt[r + 1].e == f->mt[r].e)
				जारी;

			e = f->mt[r].e;

			nft_set_elem_destroy(set, e, true);
		पूर्ण

#अगर_घोषित NFT_PIPAPO_ALIGN
		मुक्त_percpu(m->scratch_aligned);
#पूर्ण_अगर
		क्रम_each_possible_cpu(cpu)
			kमुक्त(*per_cpu_ptr(m->scratch, cpu));
		मुक्त_percpu(m->scratch);
		pipapo_मुक्त_fields(m);
		kमुक्त(m);
		priv->match = शून्य;
	पूर्ण

	अगर (priv->clone) अणु
#अगर_घोषित NFT_PIPAPO_ALIGN
		मुक्त_percpu(priv->clone->scratch_aligned);
#पूर्ण_अगर
		क्रम_each_possible_cpu(cpu)
			kमुक्त(*per_cpu_ptr(priv->clone->scratch, cpu));
		मुक्त_percpu(priv->clone->scratch);

		pipapo_मुक्त_fields(priv->clone);
		kमुक्त(priv->clone);
		priv->clone = शून्य;
	पूर्ण
पूर्ण

/**
 * nft_pipapo_gc_init() - Initialise garbage collection
 * @set:	nftables API set representation
 *
 * Instead of actually setting up a periodic work क्रम garbage collection, as
 * this operation requires a swap of matching data with the working copy, we'll
 * करो that opportunistically with other commit operations अगर the पूर्णांकerval is
 * elapsed, so we just need to set the current jअगरfies बारtamp here.
 */
अटल व्योम nft_pipapo_gc_init(स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_pipapo *priv = nft_set_priv(set);

	priv->last_gc = jअगरfies;
पूर्ण

स्थिर काष्ठा nft_set_type nft_set_pipapo_type = अणु
	.features	= NFT_SET_INTERVAL | NFT_SET_MAP | NFT_SET_OBJECT |
			  NFT_SET_TIMEOUT,
	.ops		= अणु
		.lookup		= nft_pipapo_lookup,
		.insert		= nft_pipapo_insert,
		.activate	= nft_pipapo_activate,
		.deactivate	= nft_pipapo_deactivate,
		.flush		= nft_pipapo_flush,
		.हटाओ		= nft_pipapo_हटाओ,
		.walk		= nft_pipapo_walk,
		.get		= nft_pipapo_get,
		.privsize	= nft_pipapo_privsize,
		.estimate	= nft_pipapo_estimate,
		.init		= nft_pipapo_init,
		.destroy	= nft_pipapo_destroy,
		.gc_init	= nft_pipapo_gc_init,
		.elemsize	= दुरत्व(काष्ठा nft_pipapo_elem, ext),
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_X86_64) && !defined(CONFIG_UML)
स्थिर काष्ठा nft_set_type nft_set_pipapo_avx2_type = अणु
	.features	= NFT_SET_INTERVAL | NFT_SET_MAP | NFT_SET_OBJECT |
			  NFT_SET_TIMEOUT,
	.ops		= अणु
		.lookup		= nft_pipapo_avx2_lookup,
		.insert		= nft_pipapo_insert,
		.activate	= nft_pipapo_activate,
		.deactivate	= nft_pipapo_deactivate,
		.flush		= nft_pipapo_flush,
		.हटाओ		= nft_pipapo_हटाओ,
		.walk		= nft_pipapo_walk,
		.get		= nft_pipapo_get,
		.privsize	= nft_pipapo_privsize,
		.estimate	= nft_pipapo_avx2_estimate,
		.init		= nft_pipapo_init,
		.destroy	= nft_pipapo_destroy,
		.gc_init	= nft_pipapo_gc_init,
		.elemsize	= दुरत्व(काष्ठा nft_pipapo_elem, ext),
	पूर्ण,
पूर्ण;
#पूर्ण_अगर
