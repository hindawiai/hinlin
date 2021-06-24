<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 SGI.
 * All rights reserved.
 */

#समावेश "utf8n.h"

काष्ठा utf8data अणु
	अचिन्हित पूर्णांक maxage;
	अचिन्हित पूर्णांक offset;
पूर्ण;

#घोषणा __INCLUDED_FROM_UTF8NORM_C__
#समावेश "utf8data.h"
#अघोषित __INCLUDED_FROM_UTF8NORM_C__

पूर्णांक utf8version_is_supported(u8 maj, u8 min, u8 rev)
अणु
	पूर्णांक i = ARRAY_SIZE(utf8agetab) - 1;
	अचिन्हित पूर्णांक sb_utf8version = UNICODE_AGE(maj, min, rev);

	जबतक (i >= 0 && utf8agetab[i] != 0) अणु
		अगर (sb_utf8version == utf8agetab[i])
			वापस 1;
		i--;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(utf8version_is_supported);

पूर्णांक utf8version_latest(व्योम)
अणु
	वापस utf8vers;
पूर्ण
EXPORT_SYMBOL(utf8version_latest);

/*
 * UTF-8 valid ranges.
 *
 * The UTF-8 encoding spपढ़ोs the bits of a 32bit word over several
 * bytes. This table gives the ranges that can be held and how they'd
 * be represented.
 *
 * 0x00000000 0x0000007F: 0xxxxxxx
 * 0x00000000 0x000007FF: 110xxxxx 10xxxxxx
 * 0x00000000 0x0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
 * 0x00000000 0x001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 * 0x00000000 0x03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 * 0x00000000 0x7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 * There is an additional requirement on UTF-8, in that only the
 * लघुest representation of a 32bit value is to be used.  A decoder
 * must not decode sequences that करो not satisfy this requirement.
 * Thus the allowed ranges have a lower bound.
 *
 * 0x00000000 0x0000007F: 0xxxxxxx
 * 0x00000080 0x000007FF: 110xxxxx 10xxxxxx
 * 0x00000800 0x0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
 * 0x00010000 0x001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 * 0x00200000 0x03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 * 0x04000000 0x7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 * Actual unicode अक्षरacters are limited to the range 0x0 - 0x10FFFF,
 * 17 planes of 65536 values.  This limits the sequences actually seen
 * even more, to just the following.
 *
 *          0 -     0x7F: 0                   - 0x7F
 *       0x80 -    0x7FF: 0xC2 0x80           - 0xDF 0xBF
 *      0x800 -   0xFFFF: 0xE0 0xA0 0x80      - 0xEF 0xBF 0xBF
 *    0x10000 - 0x10FFFF: 0xF0 0x90 0x80 0x80 - 0xF4 0x8F 0xBF 0xBF
 *
 * Within those ranges the surrogates 0xD800 - 0xDFFF are not allowed.
 *
 * Note that the दीर्घest sequence seen with valid usage is 4 bytes,
 * the same a single UTF-32 अक्षरacter.  This makes the UTF-8
 * representation of Unicode strictly smaller than UTF-32.
 *
 * The लघुest sequence requirement was पूर्णांकroduced by:
 *    Corrigendum #1: UTF-8 Shortest Form
 * It can be found here:
 *    http://www.unicode.org/versions/corrigendum1.hपंचांगl
 *
 */

/*
 * Return the number of bytes used by the current UTF-8 sequence.
 * Assumes the input poपूर्णांकs to the first byte of a valid UTF-8
 * sequence.
 */
अटल अंतरभूत पूर्णांक utf8clen(स्थिर अक्षर *s)
अणु
	अचिन्हित अक्षर c = *s;

	वापस 1 + (c >= 0xC0) + (c >= 0xE0) + (c >= 0xF0);
पूर्ण

/*
 * Decode a 3-byte UTF-8 sequence.
 */
अटल अचिन्हित पूर्णांक
utf8decode3(स्थिर अक्षर *str)
अणु
	अचिन्हित पूर्णांक		uc;

	uc = *str++ & 0x0F;
	uc <<= 6;
	uc |= *str++ & 0x3F;
	uc <<= 6;
	uc |= *str++ & 0x3F;

	वापस uc;
पूर्ण

/*
 * Encode a 3-byte UTF-8 sequence.
 */
अटल पूर्णांक
utf8encode3(अक्षर *str, अचिन्हित पूर्णांक val)
अणु
	str[2] = (val & 0x3F) | 0x80;
	val >>= 6;
	str[1] = (val & 0x3F) | 0x80;
	val >>= 6;
	str[0] = val | 0xE0;

	वापस 3;
पूर्ण

/*
 * utf8trie_t
 *
 * A compact binary tree, used to decode UTF-8 अक्षरacters.
 *
 * Internal nodes are one byte क्रम the node itself, and up to three
 * bytes क्रम an offset पूर्णांकo the tree.  The first byte contains the
 * following inक्रमmation:
 *  NEXTBYTE  - flag        - advance to next byte अगर set
 *  BITNUM    - 3 bit field - the bit number to tested
 *  OFFLEN    - 2 bit field - number of bytes in the offset
 * अगर offlen == 0 (non-branching node)
 *  RIGHTPATH - 1 bit field - set अगर the following node is क्रम the
 *                            right-hand path (tested bit is set)
 *  TRIENODE  - 1 bit field - set अगर the following node is an पूर्णांकernal
 *                            node, otherwise it is a leaf node
 * अगर offlen != 0 (branching node)
 *  LEFTNODE  - 1 bit field - set अगर the left-hand node is पूर्णांकernal
 *  RIGHTNODE - 1 bit field - set अगर the right-hand node is पूर्णांकernal
 *
 * Due to the way utf8 works, there cannot be branching nodes with
 * NEXTBYTE set, and moreover those nodes always have a righthand
 * descendant.
 */
प्रकार स्थिर अचिन्हित अक्षर utf8trie_t;
#घोषणा BITNUM		0x07
#घोषणा NEXTBYTE	0x08
#घोषणा OFFLEN		0x30
#घोषणा OFFLEN_SHIFT	4
#घोषणा RIGHTPATH	0x40
#घोषणा TRIENODE	0x80
#घोषणा RIGHTNODE	0x40
#घोषणा LEFTNODE	0x80

/*
 * utf8leaf_t
 *
 * The leaves of the trie are embedded in the trie, and so the same
 * underlying datatype: अचिन्हित अक्षर.
 *
 * leaf[0]: The unicode version, stored as a generation number that is
 *          an index पूर्णांकo utf8agetab[].  With this we can filter code
 *          poपूर्णांकs based on the unicode version in which they were
 *          defined.  The CCC of a non-defined code poपूर्णांक is 0.
 * leaf[1]: Canonical Combining Class. During normalization, we need
 *          to करो a stable sort पूर्णांकo ascending order of all अक्षरacters
 *          with a non-zero CCC that occur between two अक्षरacters with
 *          a CCC of 0, or at the begin or end of a string.
 *          The unicode standard guarantees that all CCC values are
 *          between 0 and 254 inclusive, which leaves 255 available as
 *          a special value.
 *          Code poपूर्णांकs with CCC 0 are known as stoppers.
 * leaf[2]: Decomposition. If leaf[1] == 255, then leaf[2] is the
 *          start of a NUL-terminated string that is the decomposition
 *          of the अक्षरacter.
 *          The CCC of a decomposable अक्षरacter is the same as the CCC
 *          of the first अक्षरacter of its decomposition.
 *          Some अक्षरacters decompose as the empty string: these are
 *          अक्षरacters with the Default_Ignorable_Code_Poपूर्णांक property.
 *          These करो affect normalization, as they all have CCC 0.
 *
 * The decompositions in the trie have been fully expanded, with the
 * exception of Hangul syllables, which are decomposed algorithmically.
 *
 * Casefolding, अगर applicable, is also करोne using decompositions.
 *
 * The trie is स्थिरructed in such a way that leaves exist क्रम all
 * UTF-8 sequences that match the criteria from the "UTF-8 valid
 * ranges" comment above, and only क्रम those sequences.  Thereक्रमe a
 * lookup in the trie can be used to validate the UTF-8 input.
 */
प्रकार स्थिर अचिन्हित अक्षर utf8leaf_t;

#घोषणा LEAF_GEN(LEAF)	((LEAF)[0])
#घोषणा LEAF_CCC(LEAF)	((LEAF)[1])
#घोषणा LEAF_STR(LEAF)	((स्थिर अक्षर *)((LEAF) + 2))

#घोषणा MINCCC		(0)
#घोषणा MAXCCC		(254)
#घोषणा STOPPER		(0)
#घोषणा	DECOMPOSE	(255)

/* Marker क्रम hangul syllable decomposition. */
#घोषणा HANGUL		((अक्षर)(255))
/* Size of the synthesized leaf used क्रम Hangul syllable decomposition. */
#घोषणा UTF8HANGULLEAF	(12)

/*
 * Hangul decomposition (algorithm from Section 3.12 of Unicode 6.3.0)
 *
 * AC00;<Hangul Syllable, First>;Lo;0;L;;;;;N;;;;;
 * D7A3;<Hangul Syllable, Last>;Lo;0;L;;;;;N;;;;;
 *
 * SBase = 0xAC00
 * LBase = 0x1100
 * VBase = 0x1161
 * TBase = 0x11A7
 * LCount = 19
 * VCount = 21
 * TCount = 28
 * NCount = 588 (VCount * TCount)
 * SCount = 11172 (LCount * NCount)
 *
 * Decomposition:
 *   SIndex = s - SBase
 *
 * LV (Canonical/Full)
 *   LIndex = SIndex / NCount
 *   VIndex = (Sindex % NCount) / TCount
 *   LPart = LBase + LIndex
 *   VPart = VBase + VIndex
 *
 * LVT (Canonical)
 *   LVIndex = (SIndex / TCount) * TCount
 *   TIndex = (Sindex % TCount)
 *   LVPart = SBase + LVIndex
 *   TPart = TBase + TIndex
 *
 * LVT (Full)
 *   LIndex = SIndex / NCount
 *   VIndex = (Sindex % NCount) / TCount
 *   TIndex = (Sindex % TCount)
 *   LPart = LBase + LIndex
 *   VPart = VBase + VIndex
 *   अगर (TIndex == 0) अणु
 *          d = <LPart, VPart>
 *   पूर्ण अन्यथा अणु
 *          TPart = TBase + TIndex
 *          d = <LPart, TPart, VPart>
 *   पूर्ण
 */

/* Constants */
#घोषणा SB	(0xAC00)
#घोषणा LB	(0x1100)
#घोषणा VB	(0x1161)
#घोषणा TB	(0x11A7)
#घोषणा LC	(19)
#घोषणा VC	(21)
#घोषणा TC	(28)
#घोषणा NC	(VC * TC)
#घोषणा SC	(LC * NC)

/* Algorithmic decomposition of hangul syllable. */
अटल utf8leaf_t *
utf8hangul(स्थिर अक्षर *str, अचिन्हित अक्षर *hangul)
अणु
	अचिन्हित पूर्णांक	si;
	अचिन्हित पूर्णांक	li;
	अचिन्हित पूर्णांक	vi;
	अचिन्हित पूर्णांक	ti;
	अचिन्हित अक्षर	*h;

	/* Calculate the SI, LI, VI, and TI values. */
	si = utf8decode3(str) - SB;
	li = si / NC;
	vi = (si % NC) / TC;
	ti = si % TC;

	/* Fill in base of leaf. */
	h = hangul;
	LEAF_GEN(h) = 2;
	LEAF_CCC(h) = DECOMPOSE;
	h += 2;

	/* Add LPart, a 3-byte UTF-8 sequence. */
	h += utf8encode3((अक्षर *)h, li + LB);

	/* Add VPart, a 3-byte UTF-8 sequence. */
	h += utf8encode3((अक्षर *)h, vi + VB);

	/* Add TPart अगर required, also a 3-byte UTF-8 sequence. */
	अगर (ti)
		h += utf8encode3((अक्षर *)h, ti + TB);

	/* Terminate string. */
	h[0] = '\0';

	वापस hangul;
पूर्ण

/*
 * Use trie to scan s, touching at most len bytes.
 * Returns the leaf अगर one exists, शून्य otherwise.
 *
 * A non-शून्य वापस guarantees that the UTF-8 sequence starting at s
 * is well-क्रमmed and corresponds to a known unicode code poपूर्णांक.  The
 * लघुhand क्रम this will be "is valid UTF-8 unicode".
 */
अटल utf8leaf_t *utf8nlookup(स्थिर काष्ठा utf8data *data,
			       अचिन्हित अक्षर *hangul, स्थिर अक्षर *s, माप_प्रकार len)
अणु
	utf8trie_t	*trie = शून्य;
	पूर्णांक		offlen;
	पूर्णांक		offset;
	पूर्णांक		mask;
	पूर्णांक		node;

	अगर (!data)
		वापस शून्य;
	अगर (len == 0)
		वापस शून्य;

	trie = utf8data + data->offset;
	node = 1;
	जबतक (node) अणु
		offlen = (*trie & OFFLEN) >> OFFLEN_SHIFT;
		अगर (*trie & NEXTBYTE) अणु
			अगर (--len == 0)
				वापस शून्य;
			s++;
		पूर्ण
		mask = 1 << (*trie & BITNUM);
		अगर (*s & mask) अणु
			/* Right leg */
			अगर (offlen) अणु
				/* Right node at offset of trie */
				node = (*trie & RIGHTNODE);
				offset = trie[offlen];
				जबतक (--offlen) अणु
					offset <<= 8;
					offset |= trie[offlen];
				पूर्ण
				trie += offset;
			पूर्ण अन्यथा अगर (*trie & RIGHTPATH) अणु
				/* Right node after this node */
				node = (*trie & TRIENODE);
				trie++;
			पूर्ण अन्यथा अणु
				/* No right node. */
				वापस शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Left leg */
			अगर (offlen) अणु
				/* Left node after this node. */
				node = (*trie & LEFTNODE);
				trie += offlen + 1;
			पूर्ण अन्यथा अगर (*trie & RIGHTPATH) अणु
				/* No left node. */
				वापस शून्य;
			पूर्ण अन्यथा अणु
				/* Left node after this node */
				node = (*trie & TRIENODE);
				trie++;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * Hangul decomposition is करोne algorithmically. These are the
	 * codepoपूर्णांकs >= 0xAC00 and <= 0xD7A3. Their UTF-8 encoding is
	 * always 3 bytes दीर्घ, so s has been advanced twice, and the
	 * start of the sequence is at s-2.
	 */
	अगर (LEAF_CCC(trie) == DECOMPOSE && LEAF_STR(trie)[0] == HANGUL)
		trie = utf8hangul(s - 2, hangul);
	वापस trie;
पूर्ण

/*
 * Use trie to scan s.
 * Returns the leaf अगर one exists, शून्य otherwise.
 *
 * Forwards to utf8nlookup().
 */
अटल utf8leaf_t *utf8lookup(स्थिर काष्ठा utf8data *data,
			      अचिन्हित अक्षर *hangul, स्थिर अक्षर *s)
अणु
	वापस utf8nlookup(data, hangul, s, (माप_प्रकार)-1);
पूर्ण

/*
 * Maximum age of any अक्षरacter in s.
 * Return -1 अगर s is not valid UTF-8 unicode.
 * Return 0 अगर only non-asचिन्हित code poपूर्णांकs are used.
 */
पूर्णांक utf8agemax(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s)
अणु
	utf8leaf_t	*leaf;
	पूर्णांक		age = 0;
	पूर्णांक		leaf_age;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!data)
		वापस -1;

	जबतक (*s) अणु
		leaf = utf8lookup(data, hangul, s);
		अगर (!leaf)
			वापस -1;

		leaf_age = utf8agetab[LEAF_GEN(leaf)];
		अगर (leaf_age <= data->maxage && leaf_age > age)
			age = leaf_age;
		s += utf8clen(s);
	पूर्ण
	वापस age;
पूर्ण
EXPORT_SYMBOL(utf8agemax);

/*
 * Minimum age of any अक्षरacter in s.
 * Return -1 अगर s is not valid UTF-8 unicode.
 * Return 0 अगर non-asचिन्हित code poपूर्णांकs are used.
 */
पूर्णांक utf8agemin(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s)
अणु
	utf8leaf_t	*leaf;
	पूर्णांक		age;
	पूर्णांक		leaf_age;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!data)
		वापस -1;
	age = data->maxage;
	जबतक (*s) अणु
		leaf = utf8lookup(data, hangul, s);
		अगर (!leaf)
			वापस -1;
		leaf_age = utf8agetab[LEAF_GEN(leaf)];
		अगर (leaf_age <= data->maxage && leaf_age < age)
			age = leaf_age;
		s += utf8clen(s);
	पूर्ण
	वापस age;
पूर्ण
EXPORT_SYMBOL(utf8agemin);

/*
 * Maximum age of any अक्षरacter in s, touch at most len bytes.
 * Return -1 अगर s is not valid UTF-8 unicode.
 */
पूर्णांक utf8nagemax(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s, माप_प्रकार len)
अणु
	utf8leaf_t	*leaf;
	पूर्णांक		age = 0;
	पूर्णांक		leaf_age;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!data)
		वापस -1;

	जबतक (len && *s) अणु
		leaf = utf8nlookup(data, hangul, s, len);
		अगर (!leaf)
			वापस -1;
		leaf_age = utf8agetab[LEAF_GEN(leaf)];
		अगर (leaf_age <= data->maxage && leaf_age > age)
			age = leaf_age;
		len -= utf8clen(s);
		s += utf8clen(s);
	पूर्ण
	वापस age;
पूर्ण
EXPORT_SYMBOL(utf8nagemax);

/*
 * Maximum age of any अक्षरacter in s, touch at most len bytes.
 * Return -1 अगर s is not valid UTF-8 unicode.
 */
पूर्णांक utf8nagemin(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s, माप_प्रकार len)
अणु
	utf8leaf_t	*leaf;
	पूर्णांक		leaf_age;
	पूर्णांक		age;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!data)
		वापस -1;
	age = data->maxage;
	जबतक (len && *s) अणु
		leaf = utf8nlookup(data, hangul, s, len);
		अगर (!leaf)
			वापस -1;
		leaf_age = utf8agetab[LEAF_GEN(leaf)];
		अगर (leaf_age <= data->maxage && leaf_age < age)
			age = leaf_age;
		len -= utf8clen(s);
		s += utf8clen(s);
	पूर्ण
	वापस age;
पूर्ण
EXPORT_SYMBOL(utf8nagemin);

/*
 * Length of the normalization of s.
 * Return -1 अगर s is not valid UTF-8 unicode.
 *
 * A string of Default_Ignorable_Code_Poपूर्णांक has length 0.
 */
sमाप_प्रकार utf8len(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s)
अणु
	utf8leaf_t	*leaf;
	माप_प्रकार		ret = 0;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!data)
		वापस -1;
	जबतक (*s) अणु
		leaf = utf8lookup(data, hangul, s);
		अगर (!leaf)
			वापस -1;
		अगर (utf8agetab[LEAF_GEN(leaf)] > data->maxage)
			ret += utf8clen(s);
		अन्यथा अगर (LEAF_CCC(leaf) == DECOMPOSE)
			ret += म_माप(LEAF_STR(leaf));
		अन्यथा
			ret += utf8clen(s);
		s += utf8clen(s);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(utf8len);

/*
 * Length of the normalization of s, touch at most len bytes.
 * Return -1 अगर s is not valid UTF-8 unicode.
 */
sमाप_प्रकार utf8nlen(स्थिर काष्ठा utf8data *data, स्थिर अक्षर *s, माप_प्रकार len)
अणु
	utf8leaf_t	*leaf;
	माप_प्रकार		ret = 0;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!data)
		वापस -1;
	जबतक (len && *s) अणु
		leaf = utf8nlookup(data, hangul, s, len);
		अगर (!leaf)
			वापस -1;
		अगर (utf8agetab[LEAF_GEN(leaf)] > data->maxage)
			ret += utf8clen(s);
		अन्यथा अगर (LEAF_CCC(leaf) == DECOMPOSE)
			ret += म_माप(LEAF_STR(leaf));
		अन्यथा
			ret += utf8clen(s);
		len -= utf8clen(s);
		s += utf8clen(s);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(utf8nlen);

/*
 * Set up an utf8cursor क्रम use by utf8byte().
 *
 *   u8c    : poपूर्णांकer to cursor.
 *   data   : स्थिर काष्ठा utf8data to use क्रम normalization.
 *   s      : string.
 *   len    : length of s.
 *
 * Returns -1 on error, 0 on success.
 */
पूर्णांक utf8ncursor(काष्ठा utf8cursor *u8c, स्थिर काष्ठा utf8data *data,
		स्थिर अक्षर *s, माप_प्रकार len)
अणु
	अगर (!data)
		वापस -1;
	अगर (!s)
		वापस -1;
	u8c->data = data;
	u8c->s = s;
	u8c->p = शून्य;
	u8c->ss = शून्य;
	u8c->sp = शून्य;
	u8c->len = len;
	u8c->slen = 0;
	u8c->ccc = STOPPER;
	u8c->nccc = STOPPER;
	/* Check we didn't clobber the maximum length. */
	अगर (u8c->len != len)
		वापस -1;
	/* The first byte of s may not be an utf8 continuation. */
	अगर (len > 0 && (*s & 0xC0) == 0x80)
		वापस -1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(utf8ncursor);

/*
 * Set up an utf8cursor क्रम use by utf8byte().
 *
 *   u8c    : poपूर्णांकer to cursor.
 *   data   : स्थिर काष्ठा utf8data to use क्रम normalization.
 *   s      : NUL-terminated string.
 *
 * Returns -1 on error, 0 on success.
 */
पूर्णांक utf8cursor(काष्ठा utf8cursor *u8c, स्थिर काष्ठा utf8data *data,
	       स्थिर अक्षर *s)
अणु
	वापस utf8ncursor(u8c, data, s, (अचिन्हित पूर्णांक)-1);
पूर्ण
EXPORT_SYMBOL(utf8cursor);

/*
 * Get one byte from the normalized क्रमm of the string described by u8c.
 *
 * Returns the byte cast to an अचिन्हित अक्षर on succes, and -1 on failure.
 *
 * The cursor keeps track of the location in the string in u8c->s.
 * When a अक्षरacter is decomposed, the current location is stored in
 * u8c->p, and u8c->s is set to the start of the decomposition. Note
 * that bytes from a decomposition करो not count against u8c->len.
 *
 * Characters are emitted अगर they match the current CCC in u8c->ccc.
 * Hitting end-of-string जबतक u8c->ccc == STOPPER means we're करोne,
 * and the function वापसs 0 in that हाल.
 *
 * Sorting by CCC is करोne by repeatedly scanning the string.  The
 * values of u8c->s and u8c->p are stored in u8c->ss and u8c->sp at
 * the start of the scan.  The first pass finds the lowest CCC to be
 * emitted and stores it in u8c->nccc, the second pass emits the
 * अक्षरacters with this CCC and finds the next lowest CCC. This limits
 * the number of passes to 1 + the number of dअगरferent CCCs in the
 * sequence being scanned.
 *
 * Thereक्रमe:
 *  u8c->p  != शून्य -> a decomposition is being scanned.
 *  u8c->ss != शून्य -> this is a repeating scan.
 *  u8c->ccc == -1   -> this is the first scan of a repeating scan.
 */
पूर्णांक utf8byte(काष्ठा utf8cursor *u8c)
अणु
	utf8leaf_t *leaf;
	पूर्णांक ccc;

	क्रम (;;) अणु
		/* Check क्रम the end of a decomposed अक्षरacter. */
		अगर (u8c->p && *u8c->s == '\0') अणु
			u8c->s = u8c->p;
			u8c->p = शून्य;
		पूर्ण

		/* Check क्रम end-of-string. */
		अगर (!u8c->p && (u8c->len == 0 || *u8c->s == '\0')) अणु
			/* There is no next byte. */
			अगर (u8c->ccc == STOPPER)
				वापस 0;
			/* End-of-string during a scan counts as a stopper. */
			ccc = STOPPER;
			जाओ ccc_mismatch;
		पूर्ण अन्यथा अगर ((*u8c->s & 0xC0) == 0x80) अणु
			/* This is a continuation of the current अक्षरacter. */
			अगर (!u8c->p)
				u8c->len--;
			वापस (अचिन्हित अक्षर)*u8c->s++;
		पूर्ण

		/* Look up the data क्रम the current अक्षरacter. */
		अगर (u8c->p) अणु
			leaf = utf8lookup(u8c->data, u8c->hangul, u8c->s);
		पूर्ण अन्यथा अणु
			leaf = utf8nlookup(u8c->data, u8c->hangul,
					   u8c->s, u8c->len);
		पूर्ण

		/* No leaf found implies that the input is a binary blob. */
		अगर (!leaf)
			वापस -1;

		ccc = LEAF_CCC(leaf);
		/* Characters that are too new have CCC 0. */
		अगर (utf8agetab[LEAF_GEN(leaf)] > u8c->data->maxage) अणु
			ccc = STOPPER;
		पूर्ण अन्यथा अगर (ccc == DECOMPOSE) अणु
			u8c->len -= utf8clen(u8c->s);
			u8c->p = u8c->s + utf8clen(u8c->s);
			u8c->s = LEAF_STR(leaf);
			/* Empty decomposition implies CCC 0. */
			अगर (*u8c->s == '\0') अणु
				अगर (u8c->ccc == STOPPER)
					जारी;
				ccc = STOPPER;
				जाओ ccc_mismatch;
			पूर्ण

			leaf = utf8lookup(u8c->data, u8c->hangul, u8c->s);
			अगर (!leaf)
				वापस -1;
			ccc = LEAF_CCC(leaf);
		पूर्ण

		/*
		 * If this is not a stopper, then see अगर it updates
		 * the next canonical class to be emitted.
		 */
		अगर (ccc != STOPPER && u8c->ccc < ccc && ccc < u8c->nccc)
			u8c->nccc = ccc;

		/*
		 * Return the current byte अगर this is the current
		 * combining class.
		 */
		अगर (ccc == u8c->ccc) अणु
			अगर (!u8c->p)
				u8c->len--;
			वापस (अचिन्हित अक्षर)*u8c->s++;
		पूर्ण

		/* Current combining class mismatch. */
ccc_mismatch:
		अगर (u8c->nccc == STOPPER) अणु
			/*
			 * Scan क्रमward क्रम the first canonical class
			 * to be emitted.  Save the position from
			 * which to restart.
			 */
			u8c->ccc = MINCCC - 1;
			u8c->nccc = ccc;
			u8c->sp = u8c->p;
			u8c->ss = u8c->s;
			u8c->slen = u8c->len;
			अगर (!u8c->p)
				u8c->len -= utf8clen(u8c->s);
			u8c->s += utf8clen(u8c->s);
		पूर्ण अन्यथा अगर (ccc != STOPPER) अणु
			/* Not a stopper, and not the ccc we're emitting. */
			अगर (!u8c->p)
				u8c->len -= utf8clen(u8c->s);
			u8c->s += utf8clen(u8c->s);
		पूर्ण अन्यथा अगर (u8c->nccc != MAXCCC + 1) अणु
			/* At a stopper, restart क्रम next ccc. */
			u8c->ccc = u8c->nccc;
			u8c->nccc = MAXCCC + 1;
			u8c->s = u8c->ss;
			u8c->p = u8c->sp;
			u8c->len = u8c->slen;
		पूर्ण अन्यथा अणु
			/* All करोne, proceed from here. */
			u8c->ccc = STOPPER;
			u8c->nccc = STOPPER;
			u8c->sp = शून्य;
			u8c->ss = शून्य;
			u8c->slen = 0;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(utf8byte);

स्थिर काष्ठा utf8data *utf8nfdi(अचिन्हित पूर्णांक maxage)
अणु
	पूर्णांक i = ARRAY_SIZE(utf8nfdidata) - 1;

	जबतक (maxage < utf8nfdidata[i].maxage)
		i--;
	अगर (maxage > utf8nfdidata[i].maxage)
		वापस शून्य;
	वापस &utf8nfdidata[i];
पूर्ण
EXPORT_SYMBOL(utf8nfdi);

स्थिर काष्ठा utf8data *utf8nfdicf(अचिन्हित पूर्णांक maxage)
अणु
	पूर्णांक i = ARRAY_SIZE(utf8nfdicfdata) - 1;

	जबतक (maxage < utf8nfdicfdata[i].maxage)
		i--;
	अगर (maxage > utf8nfdicfdata[i].maxage)
		वापस शून्य;
	वापस &utf8nfdicfdata[i];
पूर्ण
EXPORT_SYMBOL(utf8nfdicf);
