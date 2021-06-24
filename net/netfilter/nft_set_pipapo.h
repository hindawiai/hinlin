<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#अगर_अघोषित _NFT_SET_PIPAPO_H

#समावेश <linux/log2.h>
#समावेश <net/ipv6.h>			/* For the maximum length of a field */

/* Count of concatenated fields depends on count of 32-bit nftables रेजिस्टरs */
#घोषणा NFT_PIPAPO_MAX_FIELDS		NFT_REG32_COUNT

/* Restrict usage to multiple fields, make sure rbtree is used otherwise */
#घोषणा NFT_PIPAPO_MIN_FIELDS		2

/* Largest supported field size */
#घोषणा NFT_PIPAPO_MAX_BYTES		(माप(काष्ठा in6_addr))
#घोषणा NFT_PIPAPO_MAX_BITS		(NFT_PIPAPO_MAX_BYTES * BITS_PER_BYTE)

/* Bits to be grouped together in table buckets depending on set size */
#घोषणा NFT_PIPAPO_GROUP_BITS_INIT	NFT_PIPAPO_GROUP_BITS_SMALL_SET
#घोषणा NFT_PIPAPO_GROUP_BITS_SMALL_SET	8
#घोषणा NFT_PIPAPO_GROUP_BITS_LARGE_SET	4
#घोषणा NFT_PIPAPO_GROUP_BITS_ARE_8_OR_4				\
	BUILD_BUG_ON((NFT_PIPAPO_GROUP_BITS_SMALL_SET != 8) ||		\
		     (NFT_PIPAPO_GROUP_BITS_LARGE_SET != 4))
#घोषणा NFT_PIPAPO_GROUPS_PER_BYTE(f)	(BITS_PER_BYTE / (f)->bb)

/* If a lookup table माला_लो bigger than NFT_PIPAPO_LT_SIZE_HIGH, चयन to the
 * small group width, and चयन to the big group width अगर the table माला_लो
 * smaller than NFT_PIPAPO_LT_SIZE_LOW.
 *
 * Picking 2MiB as threshold (क्रम a single table) aव्योमs as much as possible
 * crossing page boundaries on most architectures (x86-64 and MIPS huge pages,
 * ARMv7 supersections, POWER "large" pages, SPARC Level 1 regions, etc.), which
 * keeps perक्रमmance nice in हाल kvदो_स्मृति() gives us non-contiguous areas.
 */
#घोषणा NFT_PIPAPO_LT_SIZE_THRESHOLD	(1 << 21)
#घोषणा NFT_PIPAPO_LT_SIZE_HYSTERESIS	(1 << 16)
#घोषणा NFT_PIPAPO_LT_SIZE_HIGH		NFT_PIPAPO_LT_SIZE_THRESHOLD
#घोषणा NFT_PIPAPO_LT_SIZE_LOW		NFT_PIPAPO_LT_SIZE_THRESHOLD -	\
					NFT_PIPAPO_LT_SIZE_HYSTERESIS

/* Fields are padded to 32 bits in input रेजिस्टरs */
#घोषणा NFT_PIPAPO_GROUPS_PADDED_SIZE(f)				\
	(round_up((f)->groups / NFT_PIPAPO_GROUPS_PER_BYTE(f), माप(u32)))
#घोषणा NFT_PIPAPO_GROUPS_PADDING(f)					\
	(NFT_PIPAPO_GROUPS_PADDED_SIZE(f) - (f)->groups /		\
					    NFT_PIPAPO_GROUPS_PER_BYTE(f))

/* Number of buckets given by 2 ^ n, with n bucket bits */
#घोषणा NFT_PIPAPO_BUCKETS(bb)		(1 << (bb))

/* Each n-bit range maps to up to n * 2 rules */
#घोषणा NFT_PIPAPO_MAP_NBITS		(स्थिर_ilog2(NFT_PIPAPO_MAX_BITS * 2))

/* Use the rest of mapping table buckets क्रम rule indices, but it makes no sense
 * to exceed 32 bits
 */
#अगर BITS_PER_LONG == 64
#घोषणा NFT_PIPAPO_MAP_TOBITS		32
#अन्यथा
#घोषणा NFT_PIPAPO_MAP_TOBITS		(BITS_PER_LONG - NFT_PIPAPO_MAP_NBITS)
#पूर्ण_अगर

/* ...which gives us the highest allowed index क्रम a rule */
#घोषणा NFT_PIPAPO_RULE0_MAX		((1UL << (NFT_PIPAPO_MAP_TOBITS - 1)) \
					- (1UL << NFT_PIPAPO_MAP_NBITS))

/* Definitions क्रम vectorised implementations */
#अगर_घोषित NFT_PIPAPO_ALIGN
#घोषणा NFT_PIPAPO_ALIGN_HEADROOM					\
	(NFT_PIPAPO_ALIGN - ARCH_KMALLOC_MINALIGN)
#घोषणा NFT_PIPAPO_LT_ALIGN(lt)		(PTR_ALIGN((lt), NFT_PIPAPO_ALIGN))
#घोषणा NFT_PIPAPO_LT_ASSIGN(field, x)					\
	करो अणु								\
		(field)->lt_aligned = NFT_PIPAPO_LT_ALIGN(x);		\
		(field)->lt = (x);					\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा NFT_PIPAPO_ALIGN_HEADROOM	0
#घोषणा NFT_PIPAPO_LT_ALIGN(lt)		(lt)
#घोषणा NFT_PIPAPO_LT_ASSIGN(field, x)	((field)->lt = (x))
#पूर्ण_अगर /* NFT_PIPAPO_ALIGN */

#घोषणा nft_pipapo_क्रम_each_field(field, index, match)		\
	क्रम ((field) = (match)->f, (index) = 0;			\
	     (index) < (match)->field_count;			\
	     (index)++, (field)++)

/**
 * जोड़ nft_pipapo_map_bucket - Bucket of mapping table
 * @to:		First rule number (in next field) this rule maps to
 * @n:		Number of rules (in next field) this rule maps to
 * @e:		If there's no next field, poपूर्णांकer to element this rule maps to
 */
जोड़ nft_pipapo_map_bucket अणु
	काष्ठा अणु
#अगर BITS_PER_LONG == 64
		अटल_निश्चित(NFT_PIPAPO_MAP_TOBITS <= 32);
		u32 to;

		अटल_निश्चित(NFT_PIPAPO_MAP_NBITS <= 32);
		u32 n;
#अन्यथा
		अचिन्हित दीर्घ to:NFT_PIPAPO_MAP_TOBITS;
		अचिन्हित दीर्घ  n:NFT_PIPAPO_MAP_NBITS;
#पूर्ण_अगर
	पूर्ण;
	काष्ठा nft_pipapo_elem *e;
पूर्ण;

/**
 * काष्ठा nft_pipapo_field - Lookup, mapping tables and related data क्रम a field
 * @groups:	Amount of bit groups
 * @rules:	Number of inserted rules
 * @bsize:	Size of each bucket in lookup table, in दीर्घs
 * @bb:		Number of bits grouped together in lookup table buckets
 * @lt:		Lookup table: 'groups' rows of buckets
 * @lt_aligned:	Version of @lt aligned to NFT_PIPAPO_ALIGN bytes
 * @mt:		Mapping table: one bucket per rule
 */
काष्ठा nft_pipapo_field अणु
	पूर्णांक groups;
	अचिन्हित दीर्घ rules;
	माप_प्रकार bsize;
	पूर्णांक bb;
#अगर_घोषित NFT_PIPAPO_ALIGN
	अचिन्हित दीर्घ *lt_aligned;
#पूर्ण_अगर
	अचिन्हित दीर्घ *lt;
	जोड़ nft_pipapo_map_bucket *mt;
पूर्ण;

/**
 * काष्ठा nft_pipapo_match - Data used क्रम lookup and matching
 * @field_count		Amount of fields in set
 * @scratch:		Pपुनः_स्मृतिated per-CPU maps क्रम partial matching results
 * @scratch_aligned:	Version of @scratch aligned to NFT_PIPAPO_ALIGN bytes
 * @bsize_max:		Maximum lookup table bucket size of all fields, in दीर्घs
 * @rcu			Matching data is swapped on commits
 * @f:			Fields, with lookup and mapping tables
 */
काष्ठा nft_pipapo_match अणु
	पूर्णांक field_count;
#अगर_घोषित NFT_PIPAPO_ALIGN
	अचिन्हित दीर्घ * __percpu *scratch_aligned;
#पूर्ण_अगर
	अचिन्हित दीर्घ * __percpu *scratch;
	माप_प्रकार bsize_max;
	काष्ठा rcu_head rcu;
	काष्ठा nft_pipapo_field f[];
पूर्ण;

/**
 * काष्ठा nft_pipapo - Representation of a set
 * @match:	Currently in-use matching data
 * @clone:	Copy where pending insertions and deletions are kept
 * @width:	Total bytes to be matched क्रम one packet, including padding
 * @dirty:	Working copy has pending insertions or deletions
 * @last_gc:	Timestamp of last garbage collection run, jअगरfies
 */
काष्ठा nft_pipapo अणु
	काष्ठा nft_pipapo_match __rcu *match;
	काष्ठा nft_pipapo_match *clone;
	पूर्णांक width;
	bool dirty;
	अचिन्हित दीर्घ last_gc;
पूर्ण;

काष्ठा nft_pipapo_elem;

/**
 * काष्ठा nft_pipapo_elem - API-facing representation of single set element
 * @ext:	nftables API extensions
 */
काष्ठा nft_pipapo_elem अणु
	काष्ठा nft_set_ext ext;
पूर्ण;

पूर्णांक pipapo_refill(अचिन्हित दीर्घ *map, पूर्णांक len, पूर्णांक rules, अचिन्हित दीर्घ *dst,
		  जोड़ nft_pipapo_map_bucket *mt, bool match_only);
bool nft_pipapo_lookup(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
		       स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext);

/**
 * pipapo_and_field_buckets_4bit() - Intersect 4-bit buckets
 * @f:		Field including lookup table
 * @dst:	Area to store result
 * @data:	Input data selecting table buckets
 */
अटल अंतरभूत व्योम pipapo_and_field_buckets_4bit(काष्ठा nft_pipapo_field *f,
						 अचिन्हित दीर्घ *dst,
						 स्थिर u8 *data)
अणु
	अचिन्हित दीर्घ *lt = NFT_PIPAPO_LT_ALIGN(f->lt);
	पूर्णांक group;

	क्रम (group = 0; group < f->groups; group += BITS_PER_BYTE / 4, data++) अणु
		u8 v;

		v = *data >> 4;
		__biपंचांगap_and(dst, dst, lt + v * f->bsize,
			     f->bsize * BITS_PER_LONG);
		lt += f->bsize * NFT_PIPAPO_BUCKETS(4);

		v = *data & 0x0f;
		__biपंचांगap_and(dst, dst, lt + v * f->bsize,
			     f->bsize * BITS_PER_LONG);
		lt += f->bsize * NFT_PIPAPO_BUCKETS(4);
	पूर्ण
पूर्ण

/**
 * pipapo_and_field_buckets_8bit() - Intersect 8-bit buckets
 * @f:		Field including lookup table
 * @dst:	Area to store result
 * @data:	Input data selecting table buckets
 */
अटल अंतरभूत व्योम pipapo_and_field_buckets_8bit(काष्ठा nft_pipapo_field *f,
						 अचिन्हित दीर्घ *dst,
						 स्थिर u8 *data)
अणु
	अचिन्हित दीर्घ *lt = NFT_PIPAPO_LT_ALIGN(f->lt);
	पूर्णांक group;

	क्रम (group = 0; group < f->groups; group++, data++) अणु
		__biपंचांगap_and(dst, dst, lt + *data * f->bsize,
			     f->bsize * BITS_PER_LONG);
		lt += f->bsize * NFT_PIPAPO_BUCKETS(8);
	पूर्ण
पूर्ण

/**
 * pipapo_estimate_size() - Estimate worst-हाल क्रम set size
 * @desc:	Set description, element count and field description used here
 *
 * The size क्रम this set type can vary dramatically, as it depends on the number
 * of rules (composing neपंचांगasks) the entries expand to. We compute the worst
 * हाल here.
 *
 * In general, क्रम a non-ranged entry or a single composing neपंचांगask, we need
 * one bit in each of the sixteen NFT_PIPAPO_BUCKETS, क्रम each 4-bit group (that
 * is, each input bit needs four bits of matching data), plus a bucket in the
 * mapping table क्रम each field.
 *
 * Return: worst-हाल set size in bytes, 0 on any overflow
 */
अटल u64 pipapo_estimate_size(स्थिर काष्ठा nft_set_desc *desc)
अणु
	अचिन्हित दीर्घ entry_size;
	u64 size;
	पूर्णांक i;

	क्रम (i = 0, entry_size = 0; i < desc->field_count; i++) अणु
		अचिन्हित दीर्घ rules;

		अगर (desc->field_len[i] > NFT_PIPAPO_MAX_BYTES)
			वापस 0;

		/* Worst-हाल ranges क्रम each concatenated field: each n-bit
		 * field can expand to up to n * 2 rules in each bucket, and
		 * each rule also needs a mapping bucket.
		 */
		rules = ilog2(desc->field_len[i] * BITS_PER_BYTE) * 2;
		entry_size += rules *
			      NFT_PIPAPO_BUCKETS(NFT_PIPAPO_GROUP_BITS_INIT) /
			      BITS_PER_BYTE;
		entry_size += rules * माप(जोड़ nft_pipapo_map_bucket);
	पूर्ण

	/* Rules in lookup and mapping tables are needed क्रम each entry */
	size = desc->size * entry_size;
	अगर (size && भाग_u64(size, desc->size) != entry_size)
		वापस 0;

	size += माप(काष्ठा nft_pipapo) + माप(काष्ठा nft_pipapo_match) * 2;

	size += माप(काष्ठा nft_pipapo_field) * desc->field_count;

	वापस size;
पूर्ण

#पूर्ण_अगर /* _NFT_SET_PIPAPO_H */
