<शैली गुरु>
/*
 * Copyright (c) 2014 SGI.
 * All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो the Free Software Foundation,
 * Inc.,  51 Franklin St, Fअगरth Floor, Boston, MA  02110-1301  USA
 */

/* Generator क्रम a compact trie क्रम unicode normalization */

#समावेश <sys/types.h>
#समावेश <मानकघोष.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <निश्चित.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>

/* Default names of the in- and output files. */

#घोषणा AGE_NAME	"DerivedAge.txt"
#घोषणा CCC_NAME	"DerivedCombiningClass.txt"
#घोषणा PROP_NAME	"DerivedCoreProperties.txt"
#घोषणा DATA_NAME	"UnicodeData.txt"
#घोषणा FOLD_NAME	"CaseFolding.txt"
#घोषणा NORM_NAME	"NormalizationCorrections.txt"
#घोषणा TEST_NAME	"NormalizationTest.txt"
#घोषणा UTF8_NAME	"utf8data.h"

स्थिर अक्षर	*age_name  = AGE_NAME;
स्थिर अक्षर	*ccc_name  = CCC_NAME;
स्थिर अक्षर	*prop_name = PROP_NAME;
स्थिर अक्षर	*data_name = DATA_NAME;
स्थिर अक्षर	*fold_name = FOLD_NAME;
स्थिर अक्षर	*norm_name = NORM_NAME;
स्थिर अक्षर	*test_name = TEST_NAME;
स्थिर अक्षर	*utf8_name = UTF8_NAME;

पूर्णांक verbose = 0;

/* An arbitrary line size limit on input lines. */

#घोषणा LINESIZE	1024
अक्षर line[LINESIZE];
अक्षर buf0[LINESIZE];
अक्षर buf1[LINESIZE];
अक्षर buf2[LINESIZE];
अक्षर buf3[LINESIZE];

स्थिर अक्षर *argv0;

#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))

/* ------------------------------------------------------------------ */

/*
 * Unicode version numbers consist of three parts: major, minor, and a
 * revision.  These numbers are packed पूर्णांकo an अचिन्हित पूर्णांक to obtain
 * a single version number.
 *
 * To save space in the generated trie, the unicode version is not
 * stored directly, instead we calculate a generation number from the
 * unicode versions seen in the DerivedAge file, and use that as an
 * index पूर्णांकo a table of unicode versions.
 */
#घोषणा UNICODE_MAJ_SHIFT		(16)
#घोषणा UNICODE_MIN_SHIFT		(8)

#घोषणा UNICODE_MAJ_MAX			((अचिन्हित लघु)-1)
#घोषणा UNICODE_MIN_MAX			((अचिन्हित अक्षर)-1)
#घोषणा UNICODE_REV_MAX			((अचिन्हित अक्षर)-1)

#घोषणा UNICODE_AGE(MAJ,MIN,REV)			\
	(((अचिन्हित पूर्णांक)(MAJ) << UNICODE_MAJ_SHIFT) |	\
	 ((अचिन्हित पूर्णांक)(MIN) << UNICODE_MIN_SHIFT) |	\
	 ((अचिन्हित पूर्णांक)(REV)))

अचिन्हित पूर्णांक *ages;
पूर्णांक ages_count;

अचिन्हित पूर्णांक unicode_maxage;

अटल पूर्णांक age_valid(अचिन्हित पूर्णांक major, अचिन्हित पूर्णांक minor,
		     अचिन्हित पूर्णांक revision)
अणु
	अगर (major > UNICODE_MAJ_MAX)
		वापस 0;
	अगर (minor > UNICODE_MIN_MAX)
		वापस 0;
	अगर (revision > UNICODE_REV_MAX)
		वापस 0;
	वापस 1;
पूर्ण

/* ------------------------------------------------------------------ */

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
प्रकार अचिन्हित अक्षर utf8trie_t;
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
 * underlying datatype, अचिन्हित अक्षर.
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
 * The decompositions in the trie have been fully expanded.
 *
 * Casefolding, अगर applicable, is also करोne using decompositions.
 */
प्रकार अचिन्हित अक्षर utf8leaf_t;

#घोषणा LEAF_GEN(LEAF)	((LEAF)[0])
#घोषणा LEAF_CCC(LEAF)	((LEAF)[1])
#घोषणा LEAF_STR(LEAF)	((स्थिर अक्षर*)((LEAF) + 2))

#घोषणा MAXGEN		(255)

#घोषणा MINCCC		(0)
#घोषणा MAXCCC		(254)
#घोषणा STOPPER		(0)
#घोषणा DECOMPOSE	(255)
#घोषणा HANGUL		((अक्षर)(255))

#घोषणा UTF8HANGULLEAF	(12)

काष्ठा tree;
अटल utf8leaf_t *utf8nlookup(काष्ठा tree *, अचिन्हित अक्षर *,
			       स्थिर अक्षर *, माप_प्रकार);
अटल utf8leaf_t *utf8lookup(काष्ठा tree *, अचिन्हित अक्षर *, स्थिर अक्षर *);

अचिन्हित अक्षर *utf8data;
माप_प्रकार utf8data_size;

utf8trie_t *nfdi;
utf8trie_t *nfdicf;

/* ------------------------------------------------------------------ */

/*
 * UTF8 valid ranges.
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
 *          0 -     0x7f: 0                     0x7f
 *       0x80 -    0x7ff: 0xc2 0x80             0xdf 0xbf
 *      0x800 -   0xffff: 0xe0 0xa0 0x80        0xef 0xbf 0xbf
 *    0x10000 - 0x10ffff: 0xf0 0x90 0x80 0x80   0xf4 0x8f 0xbf 0xbf
 *
 * Even within those ranges not all values are allowed: the surrogates
 * 0xd800 - 0xdfff should never be seen.
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

#घोषणा UTF8_2_BITS     0xC0
#घोषणा UTF8_3_BITS     0xE0
#घोषणा UTF8_4_BITS     0xF0
#घोषणा UTF8_N_BITS     0x80
#घोषणा UTF8_2_MASK     0xE0
#घोषणा UTF8_3_MASK     0xF0
#घोषणा UTF8_4_MASK     0xF8
#घोषणा UTF8_N_MASK     0xC0
#घोषणा UTF8_V_MASK     0x3F
#घोषणा UTF8_V_SHIFT    6

अटल पूर्णांक utf8encode(अक्षर *str, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक len;

	अगर (val < 0x80) अणु
		str[0] = val;
		len = 1;
	पूर्ण अन्यथा अगर (val < 0x800) अणु
		str[1] = val & UTF8_V_MASK;
		str[1] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[0] = val;
		str[0] |= UTF8_2_BITS;
		len = 2;
	पूर्ण अन्यथा अगर (val < 0x10000) अणु
		str[2] = val & UTF8_V_MASK;
		str[2] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[1] = val & UTF8_V_MASK;
		str[1] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[0] = val;
		str[0] |= UTF8_3_BITS;
		len = 3;
	पूर्ण अन्यथा अगर (val < 0x110000) अणु
		str[3] = val & UTF8_V_MASK;
		str[3] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[2] = val & UTF8_V_MASK;
		str[2] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[1] = val & UTF8_V_MASK;
		str[1] |= UTF8_N_BITS;
		val >>= UTF8_V_SHIFT;
		str[0] = val;
		str[0] |= UTF8_4_BITS;
		len = 4;
	पूर्ण अन्यथा अणु
		म_लिखो("%#x: illegal val\n", val);
		len = 0;
	पूर्ण
	वापस len;
पूर्ण

अटल अचिन्हित पूर्णांक utf8decode(स्थिर अक्षर *str)
अणु
	स्थिर अचिन्हित अक्षर *s = (स्थिर अचिन्हित अक्षर*)str;
	अचिन्हित पूर्णांक uniअक्षर = 0;

	अगर (*s < 0x80) अणु
		uniअक्षर = *s;
	पूर्ण अन्यथा अगर (*s < UTF8_3_BITS) अणु
		uniअक्षर = *s++ & 0x1F;
		uniअक्षर <<= UTF8_V_SHIFT;
		uniअक्षर |= *s & 0x3F;
	पूर्ण अन्यथा अगर (*s < UTF8_4_BITS) अणु
		uniअक्षर = *s++ & 0x0F;
		uniअक्षर <<= UTF8_V_SHIFT;
		uniअक्षर |= *s++ & 0x3F;
		uniअक्षर <<= UTF8_V_SHIFT;
		uniअक्षर |= *s & 0x3F;
	पूर्ण अन्यथा अणु
		uniअक्षर = *s++ & 0x0F;
		uniअक्षर <<= UTF8_V_SHIFT;
		uniअक्षर |= *s++ & 0x3F;
		uniअक्षर <<= UTF8_V_SHIFT;
		uniअक्षर |= *s++ & 0x3F;
		uniअक्षर <<= UTF8_V_SHIFT;
		uniअक्षर |= *s & 0x3F;
	पूर्ण
	वापस uniअक्षर;
पूर्ण

अटल पूर्णांक utf32valid(अचिन्हित पूर्णांक uniअक्षर)
अणु
	वापस uniअक्षर < 0x110000;
पूर्ण

#घोषणा HANGUL_SYLLABLE(U)	((U) >= 0xAC00 && (U) <= 0xD7A3)

#घोषणा NODE 1
#घोषणा LEAF 0

काष्ठा tree अणु
	व्योम *root;
	पूर्णांक childnode;
	स्थिर अक्षर *type;
	अचिन्हित पूर्णांक maxage;
	काष्ठा tree *next;
	पूर्णांक (*leaf_equal)(व्योम *, व्योम *);
	व्योम (*leaf_prपूर्णांक)(व्योम *, पूर्णांक);
	पूर्णांक (*leaf_mark)(व्योम *);
	पूर्णांक (*leaf_size)(व्योम *);
	पूर्णांक *(*leaf_index)(काष्ठा tree *, व्योम *);
	अचिन्हित अक्षर *(*leaf_emit)(व्योम *, अचिन्हित अक्षर *);
	पूर्णांक leafindex[0x110000];
	पूर्णांक index;
पूर्ण;

काष्ठा node अणु
	पूर्णांक index;
	पूर्णांक offset;
	पूर्णांक mark;
	पूर्णांक size;
	काष्ठा node *parent;
	व्योम *left;
	व्योम *right;
	अचिन्हित अक्षर bitnum;
	अचिन्हित अक्षर nextbyte;
	अचिन्हित अक्षर leftnode;
	अचिन्हित अक्षर rightnode;
	अचिन्हित पूर्णांक keybits;
	अचिन्हित पूर्णांक keymask;
पूर्ण;

/*
 * Example lookup function क्रम a tree.
 */
अटल व्योम *lookup(काष्ठा tree *tree, स्थिर अक्षर *key)
अणु
	काष्ठा node *node;
	व्योम *leaf = शून्य;

	node = tree->root;
	जबतक (!leaf && node) अणु
		अगर (node->nextbyte)
			key++;
		अगर (*key & (1 << (node->bitnum & 7))) अणु
			/* Right leg */
			अगर (node->rightnode == NODE) अणु
				node = node->right;
			पूर्ण अन्यथा अगर (node->rightnode == LEAF) अणु
				leaf = node->right;
			पूर्ण अन्यथा अणु
				node = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Left leg */
			अगर (node->leftnode == NODE) अणु
				node = node->left;
			पूर्ण अन्यथा अगर (node->leftnode == LEAF) अणु
				leaf = node->left;
			पूर्ण अन्यथा अणु
				node = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस leaf;
पूर्ण

/*
 * A simple non-recursive tree walker: keep track of visits to the
 * left and right branches in the lefपंचांगask and righपंचांगask.
 */
अटल व्योम tree_walk(काष्ठा tree *tree)
अणु
	काष्ठा node *node;
	अचिन्हित पूर्णांक lefपंचांगask;
	अचिन्हित पूर्णांक righपंचांगask;
	अचिन्हित पूर्णांक biपंचांगask;
	पूर्णांक indent = 1;
	पूर्णांक nodes, singletons, leaves;

	nodes = singletons = leaves = 0;

	म_लिखो("%s_%x root %p\n", tree->type, tree->maxage, tree->root);
	अगर (tree->childnode == LEAF) अणु
		निश्चित(tree->root);
		tree->leaf_prपूर्णांक(tree->root, indent);
		leaves = 1;
	पूर्ण अन्यथा अणु
		निश्चित(tree->childnode == NODE);
		node = tree->root;
		lefपंचांगask = righपंचांगask = 0;
		जबतक (node) अणु
			म_लिखो("%*snode @ %p bitnum %d nextbyte %d"
			       " left %p right %p mask %x bits %x\n",
				indent, "", node,
				node->bitnum, node->nextbyte,
				node->left, node->right,
				node->keymask, node->keybits);
			nodes += 1;
			अगर (!(node->left && node->right))
				singletons += 1;

			जबतक (node) अणु
				biपंचांगask = 1 << node->bitnum;
				अगर ((lefपंचांगask & biपंचांगask) == 0) अणु
					lefपंचांगask |= biपंचांगask;
					अगर (node->leftnode == LEAF) अणु
						निश्चित(node->left);
						tree->leaf_prपूर्णांक(node->left,
								 indent+1);
						leaves += 1;
					पूर्ण अन्यथा अगर (node->left) अणु
						निश्चित(node->leftnode == NODE);
						indent += 1;
						node = node->left;
						अवरोध;
					पूर्ण
				पूर्ण
				अगर ((righपंचांगask & biपंचांगask) == 0) अणु
					righपंचांगask |= biपंचांगask;
					अगर (node->rightnode == LEAF) अणु
						निश्चित(node->right);
						tree->leaf_prपूर्णांक(node->right,
								 indent+1);
						leaves += 1;
					पूर्ण अन्यथा अगर (node->right) अणु
						निश्चित(node->rightnode == NODE);
						indent += 1;
						node = node->right;
						अवरोध;
					पूर्ण
				पूर्ण
				lefपंचांगask &= ~biपंचांगask;
				righपंचांगask &= ~biपंचांगask;
				node = node->parent;
				indent -= 1;
			पूर्ण
		पूर्ण
	पूर्ण
	म_लिखो("nodes %d leaves %d singletons %d\n",
	       nodes, leaves, singletons);
पूर्ण

/*
 * Allocate an initialize a new पूर्णांकernal node.
 */
अटल काष्ठा node *alloc_node(काष्ठा node *parent)
अणु
	काष्ठा node *node;
	पूर्णांक bitnum;

	node = दो_स्मृति(माप(*node));
	node->left = node->right = शून्य;
	node->parent = parent;
	node->leftnode = NODE;
	node->rightnode = NODE;
	node->keybits = 0;
	node->keymask = 0;
	node->mark = 0;
	node->index = 0;
	node->offset = -1;
	node->size = 4;

	अगर (node->parent) अणु
		bitnum = parent->bitnum;
		अगर ((bitnum & 7) == 0) अणु
			node->bitnum = bitnum + 7 + 8;
			node->nextbyte = 1;
		पूर्ण अन्यथा अणु
			node->bitnum = bitnum - 1;
			node->nextbyte = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		node->bitnum = 7;
		node->nextbyte = 0;
	पूर्ण

	वापस node;
पूर्ण

/*
 * Insert a new leaf पूर्णांकo the tree, and collapse any subtrees that are
 * fully populated and end in identical leaves. A nextbyte tagged
 * पूर्णांकernal node will not be हटाओd to preserve the tree's पूर्णांकegrity.
 * Note that due to the काष्ठाure of utf8, no nextbyte tagged node
 * will be a candidate क्रम removal.
 */
अटल पूर्णांक insert(काष्ठा tree *tree, अक्षर *key, पूर्णांक keylen, व्योम *leaf)
अणु
	काष्ठा node *node;
	काष्ठा node *parent;
	व्योम **cursor;
	पूर्णांक keybits;

	निश्चित(keylen >= 1 && keylen <= 4);

	node = शून्य;
	cursor = &tree->root;
	keybits = 8 * keylen;

	/* Insert, creating path aदीर्घ the way. */
	जबतक (keybits) अणु
		अगर (!*cursor)
			*cursor = alloc_node(node);
		node = *cursor;
		अगर (node->nextbyte)
			key++;
		अगर (*key & (1 << (node->bitnum & 7)))
			cursor = &node->right;
		अन्यथा
			cursor = &node->left;
		keybits--;
	पूर्ण
	*cursor = leaf;

	/* Merge subtrees अगर possible. */
	जबतक (node) अणु
		अगर (*key & (1 << (node->bitnum & 7)))
			node->rightnode = LEAF;
		अन्यथा
			node->leftnode = LEAF;
		अगर (node->nextbyte)
			अवरोध;
		अगर (node->leftnode == NODE || node->rightnode == NODE)
			अवरोध;
		निश्चित(node->left);
		निश्चित(node->right);
		/* Compare */
		अगर (! tree->leaf_equal(node->left, node->right))
			अवरोध;
		/* Keep left, drop right leaf. */
		leaf = node->left;
		/* Check in parent */
		parent = node->parent;
		अगर (!parent) अणु
			/* root of tree! */
			tree->root = leaf;
			tree->childnode = LEAF;
		पूर्ण अन्यथा अगर (parent->left == node) अणु
			parent->left = leaf;
			parent->leftnode = LEAF;
			अगर (parent->right) अणु
				parent->keymask = 0;
				parent->keybits = 0;
			पूर्ण अन्यथा अणु
				parent->keymask |= (1 << node->bitnum);
			पूर्ण
		पूर्ण अन्यथा अगर (parent->right == node) अणु
			parent->right = leaf;
			parent->rightnode = LEAF;
			अगर (parent->left) अणु
				parent->keymask = 0;
				parent->keybits = 0;
			पूर्ण अन्यथा अणु
				parent->keymask |= (1 << node->bitnum);
				parent->keybits |= (1 << node->bitnum);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* पूर्णांकernal tree error */
			निश्चित(0);
		पूर्ण
		मुक्त(node);
		node = parent;
	पूर्ण

	/* Propagate keymasks up aदीर्घ singleton chains. */
	जबतक (node) अणु
		parent = node->parent;
		अगर (!parent)
			अवरोध;
		/* Nix the mask क्रम parents with two children. */
		अगर (node->keymask == 0) अणु
			parent->keymask = 0;
			parent->keybits = 0;
		पूर्ण अन्यथा अगर (parent->left && parent->right) अणु
			parent->keymask = 0;
			parent->keybits = 0;
		पूर्ण अन्यथा अणु
			निश्चित((parent->keymask & node->keymask) == 0);
			parent->keymask |= node->keymask;
			parent->keymask |= (1 << parent->bitnum);
			parent->keybits |= node->keybits;
			अगर (parent->right)
				parent->keybits |= (1 << parent->bitnum);
		पूर्ण
		node = parent;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Prune पूर्णांकernal nodes.
 *
 * Fully populated subtrees that end at the same leaf have alपढ़ोy
 * been collapsed.  There are still पूर्णांकernal nodes that have क्रम both
 * their left and right branches a sequence of singletons that make
 * identical choices and end in identical leaves.  The keymask and
 * keybits collected in the nodes describe the choices made in these
 * singleton chains.  When they are identical क्रम the left and right
 * branch of a node, and the two leaves comare identical, the node in
 * question can be हटाओd.
 *
 * Note that nodes with the nextbyte tag set will not be हटाओd by
 * this to ensure tree पूर्णांकegrity.  Note as well that the काष्ठाure of
 * utf8 ensures that these nodes would not have been candidates क्रम
 * removal in any हाल.
 */
अटल व्योम prune(काष्ठा tree *tree)
अणु
	काष्ठा node *node;
	काष्ठा node *left;
	काष्ठा node *right;
	काष्ठा node *parent;
	व्योम *leftleaf;
	व्योम *rightleaf;
	अचिन्हित पूर्णांक lefपंचांगask;
	अचिन्हित पूर्णांक righपंचांगask;
	अचिन्हित पूर्णांक biपंचांगask;
	पूर्णांक count;

	अगर (verbose > 0)
		म_लिखो("Pruning %s_%x\n", tree->type, tree->maxage);

	count = 0;
	अगर (tree->childnode == LEAF)
		वापस;
	अगर (!tree->root)
		वापस;

	lefपंचांगask = righपंचांगask = 0;
	node = tree->root;
	जबतक (node) अणु
		अगर (node->nextbyte)
			जाओ advance;
		अगर (node->leftnode == LEAF)
			जाओ advance;
		अगर (node->rightnode == LEAF)
			जाओ advance;
		अगर (!node->left)
			जाओ advance;
		अगर (!node->right)
			जाओ advance;
		left = node->left;
		right = node->right;
		अगर (left->keymask == 0)
			जाओ advance;
		अगर (right->keymask == 0)
			जाओ advance;
		अगर (left->keymask != right->keymask)
			जाओ advance;
		अगर (left->keybits != right->keybits)
			जाओ advance;
		leftleaf = शून्य;
		जबतक (!leftleaf) अणु
			निश्चित(left->left || left->right);
			अगर (left->leftnode == LEAF)
				leftleaf = left->left;
			अन्यथा अगर (left->rightnode == LEAF)
				leftleaf = left->right;
			अन्यथा अगर (left->left)
				left = left->left;
			अन्यथा अगर (left->right)
				left = left->right;
			अन्यथा
				निश्चित(0);
		पूर्ण
		rightleaf = शून्य;
		जबतक (!rightleaf) अणु
			निश्चित(right->left || right->right);
			अगर (right->leftnode == LEAF)
				rightleaf = right->left;
			अन्यथा अगर (right->rightnode == LEAF)
				rightleaf = right->right;
			अन्यथा अगर (right->left)
				right = right->left;
			अन्यथा अगर (right->right)
				right = right->right;
			अन्यथा
				निश्चित(0);
		पूर्ण
		अगर (! tree->leaf_equal(leftleaf, rightleaf))
			जाओ advance;
		/*
		 * This node has identical singleton-only subtrees.
		 * Remove it.
		 */
		parent = node->parent;
		left = node->left;
		right = node->right;
		अगर (parent->left == node)
			parent->left = left;
		अन्यथा अगर (parent->right == node)
			parent->right = left;
		अन्यथा
			निश्चित(0);
		left->parent = parent;
		left->keymask |= (1 << node->bitnum);
		node->left = शून्य;
		जबतक (node) अणु
			biपंचांगask = 1 << node->bitnum;
			lefपंचांगask &= ~biपंचांगask;
			righपंचांगask &= ~biपंचांगask;
			अगर (node->leftnode == NODE && node->left) अणु
				left = node->left;
				मुक्त(node);
				count++;
				node = left;
			पूर्ण अन्यथा अगर (node->rightnode == NODE && node->right) अणु
				right = node->right;
				मुक्त(node);
				count++;
				node = right;
			पूर्ण अन्यथा अणु
				node = शून्य;
			पूर्ण
		पूर्ण
		/* Propagate keymasks up aदीर्घ singleton chains. */
		node = parent;
		/* Force re-check */
		biपंचांगask = 1 << node->bitnum;
		lefपंचांगask &= ~biपंचांगask;
		righपंचांगask &= ~biपंचांगask;
		क्रम (;;) अणु
			अगर (node->left && node->right)
				अवरोध;
			अगर (node->left) अणु
				left = node->left;
				node->keymask |= left->keymask;
				node->keybits |= left->keybits;
			पूर्ण
			अगर (node->right) अणु
				right = node->right;
				node->keymask |= right->keymask;
				node->keybits |= right->keybits;
			पूर्ण
			node->keymask |= (1 << node->bitnum);
			node = node->parent;
			/* Force re-check */
			biपंचांगask = 1 << node->bitnum;
			lefपंचांगask &= ~biपंचांगask;
			righपंचांगask &= ~biपंचांगask;
		पूर्ण
	advance:
		biपंचांगask = 1 << node->bitnum;
		अगर ((lefपंचांगask & biपंचांगask) == 0 &&
		    node->leftnode == NODE &&
		    node->left) अणु
			lefपंचांगask |= biपंचांगask;
			node = node->left;
		पूर्ण अन्यथा अगर ((righपंचांगask & biपंचांगask) == 0 &&
			   node->rightnode == NODE &&
			   node->right) अणु
			righपंचांगask |= biपंचांगask;
			node = node->right;
		पूर्ण अन्यथा अणु
			lefपंचांगask &= ~biपंचांगask;
			righपंचांगask &= ~biपंचांगask;
			node = node->parent;
		पूर्ण
	पूर्ण
	अगर (verbose > 0)
		म_लिखो("Pruned %d nodes\n", count);
पूर्ण

/*
 * Mark the nodes in the tree that lead to leaves that must be
 * emitted.
 */
अटल व्योम mark_nodes(काष्ठा tree *tree)
अणु
	काष्ठा node *node;
	काष्ठा node *n;
	अचिन्हित पूर्णांक lefपंचांगask;
	अचिन्हित पूर्णांक righपंचांगask;
	अचिन्हित पूर्णांक biपंचांगask;
	पूर्णांक marked;

	marked = 0;
	अगर (verbose > 0)
		म_लिखो("Marking %s_%x\n", tree->type, tree->maxage);
	अगर (tree->childnode == LEAF)
		जाओ करोne;

	निश्चित(tree->childnode == NODE);
	node = tree->root;
	lefपंचांगask = righपंचांगask = 0;
	जबतक (node) अणु
		biपंचांगask = 1 << node->bitnum;
		अगर ((lefपंचांगask & biपंचांगask) == 0) अणु
			lefपंचांगask |= biपंचांगask;
			अगर (node->leftnode == LEAF) अणु
				निश्चित(node->left);
				अगर (tree->leaf_mark(node->left)) अणु
					n = node;
					जबतक (n && !n->mark) अणु
						marked++;
						n->mark = 1;
						n = n->parent;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (node->left) अणु
				निश्चित(node->leftnode == NODE);
				node = node->left;
				जारी;
			पूर्ण
		पूर्ण
		अगर ((righपंचांगask & biपंचांगask) == 0) अणु
			righपंचांगask |= biपंचांगask;
			अगर (node->rightnode == LEAF) अणु
				निश्चित(node->right);
				अगर (tree->leaf_mark(node->right)) अणु
					n = node;
					जबतक (n && !n->mark) अणु
						marked++;
						n->mark = 1;
						n = n->parent;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (node->right) अणु
				निश्चित(node->rightnode == NODE);
				node = node->right;
				जारी;
			पूर्ण
		पूर्ण
		lefपंचांगask &= ~biपंचांगask;
		righपंचांगask &= ~biपंचांगask;
		node = node->parent;
	पूर्ण

	/* second pass: left siblings and singletons */

	निश्चित(tree->childnode == NODE);
	node = tree->root;
	lefपंचांगask = righपंचांगask = 0;
	जबतक (node) अणु
		biपंचांगask = 1 << node->bitnum;
		अगर ((lefपंचांगask & biपंचांगask) == 0) अणु
			lefपंचांगask |= biपंचांगask;
			अगर (node->leftnode == LEAF) अणु
				निश्चित(node->left);
				अगर (tree->leaf_mark(node->left)) अणु
					n = node;
					जबतक (n && !n->mark) अणु
						marked++;
						n->mark = 1;
						n = n->parent;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (node->left) अणु
				निश्चित(node->leftnode == NODE);
				node = node->left;
				अगर (!node->mark && node->parent->mark) अणु
					marked++;
					node->mark = 1;
				पूर्ण
				जारी;
			पूर्ण
		पूर्ण
		अगर ((righपंचांगask & biपंचांगask) == 0) अणु
			righपंचांगask |= biपंचांगask;
			अगर (node->rightnode == LEAF) अणु
				निश्चित(node->right);
				अगर (tree->leaf_mark(node->right)) अणु
					n = node;
					जबतक (n && !n->mark) अणु
						marked++;
						n->mark = 1;
						n = n->parent;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (node->right) अणु
				निश्चित(node->rightnode == NODE);
				node = node->right;
				अगर (!node->mark && node->parent->mark &&
				    !node->parent->left) अणु
					marked++;
					node->mark = 1;
				पूर्ण
				जारी;
			पूर्ण
		पूर्ण
		lefपंचांगask &= ~biपंचांगask;
		righपंचांगask &= ~biपंचांगask;
		node = node->parent;
	पूर्ण
करोne:
	अगर (verbose > 0)
		म_लिखो("Marked %d nodes\n", marked);
पूर्ण

/*
 * Compute the index of each node and leaf, which is the offset in the
 * emitted trie.  These values must be pre-computed because relative
 * offsets between nodes are used to navigate the tree.
 */
अटल पूर्णांक index_nodes(काष्ठा tree *tree, पूर्णांक index)
अणु
	काष्ठा node *node;
	अचिन्हित पूर्णांक lefपंचांगask;
	अचिन्हित पूर्णांक righपंचांगask;
	अचिन्हित पूर्णांक biपंचांगask;
	पूर्णांक count;
	पूर्णांक indent;

	/* Align to a cache line (or half a cache line?). */
	जबतक (index % 64)
		index++;
	tree->index = index;
	indent = 1;
	count = 0;

	अगर (verbose > 0)
		म_लिखो("Indexing %s_%x: %d\n", tree->type, tree->maxage, index);
	अगर (tree->childnode == LEAF) अणु
		index += tree->leaf_size(tree->root);
		जाओ करोne;
	पूर्ण

	निश्चित(tree->childnode == NODE);
	node = tree->root;
	lefपंचांगask = righपंचांगask = 0;
	जबतक (node) अणु
		अगर (!node->mark)
			जाओ skip;
		count++;
		अगर (node->index != index)
			node->index = index;
		index += node->size;
skip:
		जबतक (node) अणु
			biपंचांगask = 1 << node->bitnum;
			अगर (node->mark && (lefपंचांगask & biपंचांगask) == 0) अणु
				lefपंचांगask |= biपंचांगask;
				अगर (node->leftnode == LEAF) अणु
					निश्चित(node->left);
					*tree->leaf_index(tree, node->left) =
									index;
					index += tree->leaf_size(node->left);
					count++;
				पूर्ण अन्यथा अगर (node->left) अणु
					निश्चित(node->leftnode == NODE);
					indent += 1;
					node = node->left;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (node->mark && (righपंचांगask & biपंचांगask) == 0) अणु
				righपंचांगask |= biपंचांगask;
				अगर (node->rightnode == LEAF) अणु
					निश्चित(node->right);
					*tree->leaf_index(tree, node->right) = index;
					index += tree->leaf_size(node->right);
					count++;
				पूर्ण अन्यथा अगर (node->right) अणु
					निश्चित(node->rightnode == NODE);
					indent += 1;
					node = node->right;
					अवरोध;
				पूर्ण
			पूर्ण
			lefपंचांगask &= ~biपंचांगask;
			righपंचांगask &= ~biपंचांगask;
			node = node->parent;
			indent -= 1;
		पूर्ण
	पूर्ण
करोne:
	/* Round up to a multiple of 16 */
	जबतक (index % 16)
		index++;
	अगर (verbose > 0)
		म_लिखो("Final index %d\n", index);
	वापस index;
पूर्ण

/*
 * Mark the nodes in a subtree, helper क्रम size_nodes().
 */
अटल पूर्णांक mark_subtree(काष्ठा node *node)
अणु
	पूर्णांक changed;

	अगर (!node || node->mark)
		वापस 0;
	node->mark = 1;
	node->index = node->parent->index;
	changed = 1;
	अगर (node->leftnode == NODE)
		changed += mark_subtree(node->left);
	अगर (node->rightnode == NODE)
		changed += mark_subtree(node->right);
	वापस changed;
पूर्ण

/*
 * Compute the size of nodes and leaves. We start by assuming that
 * each node needs to store a three-byte offset. The indexes of the
 * nodes are calculated based on that, and then this function is
 * called to see अगर the sizes of some nodes can be reduced.  This is
 * repeated until no more changes are seen.
 */
अटल पूर्णांक size_nodes(काष्ठा tree *tree)
अणु
	काष्ठा tree *next;
	काष्ठा node *node;
	काष्ठा node *right;
	काष्ठा node *n;
	अचिन्हित पूर्णांक lefपंचांगask;
	अचिन्हित पूर्णांक righपंचांगask;
	अचिन्हित पूर्णांक biपंचांगask;
	अचिन्हित पूर्णांक pathbits;
	अचिन्हित पूर्णांक pathmask;
	अचिन्हित पूर्णांक nbit;
	पूर्णांक changed;
	पूर्णांक offset;
	पूर्णांक size;
	पूर्णांक indent;

	indent = 1;
	changed = 0;
	size = 0;

	अगर (verbose > 0)
		म_लिखो("Sizing %s_%x\n", tree->type, tree->maxage);
	अगर (tree->childnode == LEAF)
		जाओ करोne;

	निश्चित(tree->childnode == NODE);
	pathbits = 0;
	pathmask = 0;
	node = tree->root;
	lefपंचांगask = righपंचांगask = 0;
	जबतक (node) अणु
		अगर (!node->mark)
			जाओ skip;
		offset = 0;
		अगर (!node->left || !node->right) अणु
			size = 1;
		पूर्ण अन्यथा अणु
			अगर (node->rightnode == NODE) अणु
				/*
				 * If the right node is not marked,
				 * look क्रम a corresponding node in
				 * the next tree.  Such a node need
				 * not exist.
				 */
				right = node->right;
				next = tree->next;
				जबतक (!right->mark) अणु
					निश्चित(next);
					n = next->root;
					जबतक (n->bitnum != node->bitnum) अणु
						nbit = 1 << n->bitnum;
						अगर (!(pathmask & nbit))
							अवरोध;
						अगर (pathbits & nbit) अणु
							अगर (n->rightnode == LEAF)
								अवरोध;
							n = n->right;
						पूर्ण अन्यथा अणु
							अगर (n->leftnode == LEAF)
								अवरोध;
							n = n->left;
						पूर्ण
					पूर्ण
					अगर (n->bitnum != node->bitnum)
						अवरोध;
					n = n->right;
					right = n;
					next = next->next;
				पूर्ण
				/* Make sure the right node is marked. */
				अगर (!right->mark)
					changed += mark_subtree(right);
				offset = right->index - node->index;
			पूर्ण अन्यथा अणु
				offset = *tree->leaf_index(tree, node->right);
				offset -= node->index;
			पूर्ण
			निश्चित(offset >= 0);
			निश्चित(offset <= 0xffffff);
			अगर (offset <= 0xff) अणु
				size = 2;
			पूर्ण अन्यथा अगर (offset <= 0xffff) अणु
				size = 3;
			पूर्ण अन्यथा अणु /* offset <= 0xffffff */
				size = 4;
			पूर्ण
		पूर्ण
		अगर (node->size != size || node->offset != offset) अणु
			node->size = size;
			node->offset = offset;
			changed++;
		पूर्ण
skip:
		जबतक (node) अणु
			biपंचांगask = 1 << node->bitnum;
			pathmask |= biपंचांगask;
			अगर (node->mark && (lefपंचांगask & biपंचांगask) == 0) अणु
				lefपंचांगask |= biपंचांगask;
				अगर (node->leftnode == LEAF) अणु
					निश्चित(node->left);
				पूर्ण अन्यथा अगर (node->left) अणु
					निश्चित(node->leftnode == NODE);
					indent += 1;
					node = node->left;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (node->mark && (righपंचांगask & biपंचांगask) == 0) अणु
				righपंचांगask |= biपंचांगask;
				pathbits |= biपंचांगask;
				अगर (node->rightnode == LEAF) अणु
					निश्चित(node->right);
				पूर्ण अन्यथा अगर (node->right) अणु
					निश्चित(node->rightnode == NODE);
					indent += 1;
					node = node->right;
					अवरोध;
				पूर्ण
			पूर्ण
			lefपंचांगask &= ~biपंचांगask;
			righपंचांगask &= ~biपंचांगask;
			pathmask &= ~biपंचांगask;
			pathbits &= ~biपंचांगask;
			node = node->parent;
			indent -= 1;
		पूर्ण
	पूर्ण
करोne:
	अगर (verbose > 0)
		म_लिखो("Found %d changes\n", changed);
	वापस changed;
पूर्ण

/*
 * Emit a trie क्रम the given tree पूर्णांकo the data array.
 */
अटल व्योम emit(काष्ठा tree *tree, अचिन्हित अक्षर *data)
अणु
	काष्ठा node *node;
	अचिन्हित पूर्णांक lefपंचांगask;
	अचिन्हित पूर्णांक righपंचांगask;
	अचिन्हित पूर्णांक biपंचांगask;
	पूर्णांक offlen;
	पूर्णांक offset;
	पूर्णांक index;
	पूर्णांक indent;
	पूर्णांक size;
	पूर्णांक bytes;
	पूर्णांक leaves;
	पूर्णांक nodes[4];
	अचिन्हित अक्षर byte;

	nodes[0] = nodes[1] = nodes[2] = nodes[3] = 0;
	leaves = 0;
	bytes = 0;
	index = tree->index;
	data += index;
	indent = 1;
	अगर (verbose > 0)
		म_लिखो("Emitting %s_%x\n", tree->type, tree->maxage);
	अगर (tree->childnode == LEAF) अणु
		निश्चित(tree->root);
		tree->leaf_emit(tree->root, data);
		size = tree->leaf_size(tree->root);
		index += size;
		leaves++;
		जाओ करोne;
	पूर्ण

	निश्चित(tree->childnode == NODE);
	node = tree->root;
	lefपंचांगask = righपंचांगask = 0;
	जबतक (node) अणु
		अगर (!node->mark)
			जाओ skip;
		निश्चित(node->offset != -1);
		निश्चित(node->index == index);

		byte = 0;
		अगर (node->nextbyte)
			byte |= NEXTBYTE;
		byte |= (node->bitnum & BITNUM);
		अगर (node->left && node->right) अणु
			अगर (node->leftnode == NODE)
				byte |= LEFTNODE;
			अगर (node->rightnode == NODE)
				byte |= RIGHTNODE;
			अगर (node->offset <= 0xff)
				offlen = 1;
			अन्यथा अगर (node->offset <= 0xffff)
				offlen = 2;
			अन्यथा
				offlen = 3;
			nodes[offlen]++;
			offset = node->offset;
			byte |= offlen << OFFLEN_SHIFT;
			*data++ = byte;
			index++;
			जबतक (offlen--) अणु
				*data++ = offset & 0xff;
				index++;
				offset >>= 8;
			पूर्ण
		पूर्ण अन्यथा अगर (node->left) अणु
			अगर (node->leftnode == NODE)
				byte |= TRIENODE;
			nodes[0]++;
			*data++ = byte;
			index++;
		पूर्ण अन्यथा अगर (node->right) अणु
			byte |= RIGHTNODE;
			अगर (node->rightnode == NODE)
				byte |= TRIENODE;
			nodes[0]++;
			*data++ = byte;
			index++;
		पूर्ण अन्यथा अणु
			निश्चित(0);
		पूर्ण
skip:
		जबतक (node) अणु
			biपंचांगask = 1 << node->bitnum;
			अगर (node->mark && (lefपंचांगask & biपंचांगask) == 0) अणु
				lefपंचांगask |= biपंचांगask;
				अगर (node->leftnode == LEAF) अणु
					निश्चित(node->left);
					data = tree->leaf_emit(node->left,
							       data);
					size = tree->leaf_size(node->left);
					index += size;
					bytes += size;
					leaves++;
				पूर्ण अन्यथा अगर (node->left) अणु
					निश्चित(node->leftnode == NODE);
					indent += 1;
					node = node->left;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (node->mark && (righपंचांगask & biपंचांगask) == 0) अणु
				righपंचांगask |= biपंचांगask;
				अगर (node->rightnode == LEAF) अणु
					निश्चित(node->right);
					data = tree->leaf_emit(node->right,
							       data);
					size = tree->leaf_size(node->right);
					index += size;
					bytes += size;
					leaves++;
				पूर्ण अन्यथा अगर (node->right) अणु
					निश्चित(node->rightnode == NODE);
					indent += 1;
					node = node->right;
					अवरोध;
				पूर्ण
			पूर्ण
			lefपंचांगask &= ~biपंचांगask;
			righपंचांगask &= ~biपंचांगask;
			node = node->parent;
			indent -= 1;
		पूर्ण
	पूर्ण
करोne:
	अगर (verbose > 0) अणु
		म_लिखो("Emitted %d (%d) leaves",
			leaves, bytes);
		म_लिखो(" %d (%d+%d+%d+%d) nodes",
			nodes[0] + nodes[1] + nodes[2] + nodes[3],
			nodes[0], nodes[1], nodes[2], nodes[3]);
		म_लिखो(" %d total\n", index - tree->index);
	पूर्ण
पूर्ण

/* ------------------------------------------------------------------ */

/*
 * Unicode data.
 *
 * We need to keep track of the Canonical Combining Class, the Age,
 * and decompositions क्रम a code poपूर्णांक.
 *
 * For the Age, we store the index पूर्णांकo the ages table.  Effectively
 * this is a generation number that the table maps to a unicode
 * version.
 *
 * The correction field is used to indicate that this entry is in the
 * corrections array, which contains decompositions that were
 * corrected in later revisions.  The value of the correction field is
 * the Unicode version in which the mapping was corrected.
 */
काष्ठा unicode_data अणु
	अचिन्हित पूर्णांक code;
	पूर्णांक ccc;
	पूर्णांक gen;
	पूर्णांक correction;
	अचिन्हित पूर्णांक *utf32nfdi;
	अचिन्हित पूर्णांक *utf32nfdicf;
	अक्षर *utf8nfdi;
	अक्षर *utf8nfdicf;
पूर्ण;

काष्ठा unicode_data unicode_data[0x110000];
काष्ठा unicode_data *corrections;
पूर्णांक    corrections_count;

काष्ठा tree *nfdi_tree;
काष्ठा tree *nfdicf_tree;

काष्ठा tree *trees;
पूर्णांक          trees_count;

/*
 * Check the corrections array to see अगर this entry was corrected at
 * some poपूर्णांक.
 */
अटल काष्ठा unicode_data *corrections_lookup(काष्ठा unicode_data *u)
अणु
	पूर्णांक i;

	क्रम (i = 0; i != corrections_count; i++)
		अगर (u->code == corrections[i].code)
			वापस &corrections[i];
	वापस u;
पूर्ण

अटल पूर्णांक nfdi_equal(व्योम *l, व्योम *r)
अणु
	काष्ठा unicode_data *left = l;
	काष्ठा unicode_data *right = r;

	अगर (left->gen != right->gen)
		वापस 0;
	अगर (left->ccc != right->ccc)
		वापस 0;
	अगर (left->utf8nfdi && right->utf8nfdi &&
	    म_भेद(left->utf8nfdi, right->utf8nfdi) == 0)
		वापस 1;
	अगर (left->utf8nfdi || right->utf8nfdi)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक nfdicf_equal(व्योम *l, व्योम *r)
अणु
	काष्ठा unicode_data *left = l;
	काष्ठा unicode_data *right = r;

	अगर (left->gen != right->gen)
		वापस 0;
	अगर (left->ccc != right->ccc)
		वापस 0;
	अगर (left->utf8nfdicf && right->utf8nfdicf &&
	    म_भेद(left->utf8nfdicf, right->utf8nfdicf) == 0)
		वापस 1;
	अगर (left->utf8nfdicf && right->utf8nfdicf)
		वापस 0;
	अगर (left->utf8nfdicf || right->utf8nfdicf)
		वापस 0;
	अगर (left->utf8nfdi && right->utf8nfdi &&
	    म_भेद(left->utf8nfdi, right->utf8nfdi) == 0)
		वापस 1;
	अगर (left->utf8nfdi || right->utf8nfdi)
		वापस 0;
	वापस 1;
पूर्ण

अटल व्योम nfdi_prपूर्णांक(व्योम *l, पूर्णांक indent)
अणु
	काष्ठा unicode_data *leaf = l;

	म_लिखो("%*sleaf @ %p code %X ccc %d gen %d", indent, "", leaf,
		leaf->code, leaf->ccc, leaf->gen);

	अगर (leaf->utf8nfdi && leaf->utf8nfdi[0] == HANGUL)
		म_लिखो(" nfdi \"%s\"", "HANGUL SYLLABLE");
	अन्यथा अगर (leaf->utf8nfdi)
		म_लिखो(" nfdi \"%s\"", (स्थिर अक्षर*)leaf->utf8nfdi);

	म_लिखो("\n");
पूर्ण

अटल व्योम nfdicf_prपूर्णांक(व्योम *l, पूर्णांक indent)
अणु
	काष्ठा unicode_data *leaf = l;

	म_लिखो("%*sleaf @ %p code %X ccc %d gen %d", indent, "", leaf,
		leaf->code, leaf->ccc, leaf->gen);

	अगर (leaf->utf8nfdicf)
		म_लिखो(" nfdicf \"%s\"", (स्थिर अक्षर*)leaf->utf8nfdicf);
	अन्यथा अगर (leaf->utf8nfdi && leaf->utf8nfdi[0] == HANGUL)
		म_लिखो(" nfdi \"%s\"", "HANGUL SYLLABLE");
	अन्यथा अगर (leaf->utf8nfdi)
		म_लिखो(" nfdi \"%s\"", (स्थिर अक्षर*)leaf->utf8nfdi);
	म_लिखो("\n");
पूर्ण

अटल पूर्णांक nfdi_mark(व्योम *l)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक nfdicf_mark(व्योम *l)
अणु
	काष्ठा unicode_data *leaf = l;

	अगर (leaf->utf8nfdicf)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक correction_mark(व्योम *l)
अणु
	काष्ठा unicode_data *leaf = l;

	वापस leaf->correction;
पूर्ण

अटल पूर्णांक nfdi_size(व्योम *l)
अणु
	काष्ठा unicode_data *leaf = l;
	पूर्णांक size = 2;

	अगर (HANGUL_SYLLABLE(leaf->code))
		size += 1;
	अन्यथा अगर (leaf->utf8nfdi)
		size += म_माप(leaf->utf8nfdi) + 1;
	वापस size;
पूर्ण

अटल पूर्णांक nfdicf_size(व्योम *l)
अणु
	काष्ठा unicode_data *leaf = l;
	पूर्णांक size = 2;

	अगर (HANGUL_SYLLABLE(leaf->code))
		size += 1;
	अन्यथा अगर (leaf->utf8nfdicf)
		size += म_माप(leaf->utf8nfdicf) + 1;
	अन्यथा अगर (leaf->utf8nfdi)
		size += म_माप(leaf->utf8nfdi) + 1;
	वापस size;
पूर्ण

अटल पूर्णांक *nfdi_index(काष्ठा tree *tree, व्योम *l)
अणु
	काष्ठा unicode_data *leaf = l;

	वापस &tree->leafindex[leaf->code];
पूर्ण

अटल पूर्णांक *nfdicf_index(काष्ठा tree *tree, व्योम *l)
अणु
	काष्ठा unicode_data *leaf = l;

	वापस &tree->leafindex[leaf->code];
पूर्ण

अटल अचिन्हित अक्षर *nfdi_emit(व्योम *l, अचिन्हित अक्षर *data)
अणु
	काष्ठा unicode_data *leaf = l;
	अचिन्हित अक्षर *s;

	*data++ = leaf->gen;

	अगर (HANGUL_SYLLABLE(leaf->code)) अणु
		*data++ = DECOMPOSE;
		*data++ = HANGUL;
	पूर्ण अन्यथा अगर (leaf->utf8nfdi) अणु
		*data++ = DECOMPOSE;
		s = (अचिन्हित अक्षर*)leaf->utf8nfdi;
		जबतक ((*data++ = *s++) != 0)
			;
	पूर्ण अन्यथा अणु
		*data++ = leaf->ccc;
	पूर्ण
	वापस data;
पूर्ण

अटल अचिन्हित अक्षर *nfdicf_emit(व्योम *l, अचिन्हित अक्षर *data)
अणु
	काष्ठा unicode_data *leaf = l;
	अचिन्हित अक्षर *s;

	*data++ = leaf->gen;

	अगर (HANGUL_SYLLABLE(leaf->code)) अणु
		*data++ = DECOMPOSE;
		*data++ = HANGUL;
	पूर्ण अन्यथा अगर (leaf->utf8nfdicf) अणु
		*data++ = DECOMPOSE;
		s = (अचिन्हित अक्षर*)leaf->utf8nfdicf;
		जबतक ((*data++ = *s++) != 0)
			;
	पूर्ण अन्यथा अगर (leaf->utf8nfdi) अणु
		*data++ = DECOMPOSE;
		s = (अचिन्हित अक्षर*)leaf->utf8nfdi;
		जबतक ((*data++ = *s++) != 0)
			;
	पूर्ण अन्यथा अणु
		*data++ = leaf->ccc;
	पूर्ण
	वापस data;
पूर्ण

अटल व्योम utf8_create(काष्ठा unicode_data *data)
अणु
	अक्षर utf[18*4+1];
	अक्षर *u;
	अचिन्हित पूर्णांक *um;
	पूर्णांक i;

	अगर (data->utf8nfdi) अणु
		निश्चित(data->utf8nfdi[0] == HANGUL);
		वापस;
	पूर्ण

	u = utf;
	um = data->utf32nfdi;
	अगर (um) अणु
		क्रम (i = 0; um[i]; i++)
			u += utf8encode(u, um[i]);
		*u = '\0';
		data->utf8nfdi = strdup(utf);
	पूर्ण
	u = utf;
	um = data->utf32nfdicf;
	अगर (um) अणु
		क्रम (i = 0; um[i]; i++)
			u += utf8encode(u, um[i]);
		*u = '\0';
		अगर (!data->utf8nfdi || म_भेद(data->utf8nfdi, utf))
			data->utf8nfdicf = strdup(utf);
	पूर्ण
पूर्ण

अटल व्योम utf8_init(व्योम)
अणु
	अचिन्हित पूर्णांक uniअक्षर;
	पूर्णांक i;

	क्रम (uniअक्षर = 0; uniअक्षर != 0x110000; uniअक्षर++)
		utf8_create(&unicode_data[uniअक्षर]);

	क्रम (i = 0; i != corrections_count; i++)
		utf8_create(&corrections[i]);
पूर्ण

अटल व्योम trees_init(व्योम)
अणु
	काष्ठा unicode_data *data;
	अचिन्हित पूर्णांक maxage;
	अचिन्हित पूर्णांक nextage;
	पूर्णांक count;
	पूर्णांक i;
	पूर्णांक j;

	/* Count the number of dअगरferent ages. */
	count = 0;
	nextage = (अचिन्हित पूर्णांक)-1;
	करो अणु
		maxage = nextage;
		nextage = 0;
		क्रम (i = 0; i <= corrections_count; i++) अणु
			data = &corrections[i];
			अगर (nextage < data->correction &&
			    data->correction < maxage)
				nextage = data->correction;
		पूर्ण
		count++;
	पूर्ण जबतक (nextage);

	/* Two trees per age: nfdi and nfdicf */
	trees_count = count * 2;
	trees = सुस्मृति(trees_count, माप(काष्ठा tree));

	/* Assign ages to the trees. */
	count = trees_count;
	nextage = (अचिन्हित पूर्णांक)-1;
	करो अणु
		maxage = nextage;
		trees[--count].maxage = maxage;
		trees[--count].maxage = maxage;
		nextage = 0;
		क्रम (i = 0; i <= corrections_count; i++) अणु
			data = &corrections[i];
			अगर (nextage < data->correction &&
			    data->correction < maxage)
				nextage = data->correction;
		पूर्ण
	पूर्ण जबतक (nextage);

	/* The ages asचिन्हित above are off by one. */
	क्रम (i = 0; i != trees_count; i++) अणु
		j = 0;
		जबतक (ages[j] < trees[i].maxage)
			j++;
		trees[i].maxage = ages[j-1];
	पूर्ण

	/* Set up the क्रमwarding between trees. */
	trees[trees_count-2].next = &trees[trees_count-1];
	trees[trees_count-1].leaf_mark = nfdi_mark;
	trees[trees_count-2].leaf_mark = nfdicf_mark;
	क्रम (i = 0; i != trees_count-2; i += 2) अणु
		trees[i].next = &trees[trees_count-2];
		trees[i].leaf_mark = correction_mark;
		trees[i+1].next = &trees[trees_count-1];
		trees[i+1].leaf_mark = correction_mark;
	पूर्ण

	/* Assign the callouts. */
	क्रम (i = 0; i != trees_count; i += 2) अणु
		trees[i].type = "nfdicf";
		trees[i].leaf_equal = nfdicf_equal;
		trees[i].leaf_prपूर्णांक = nfdicf_prपूर्णांक;
		trees[i].leaf_size = nfdicf_size;
		trees[i].leaf_index = nfdicf_index;
		trees[i].leaf_emit = nfdicf_emit;

		trees[i+1].type = "nfdi";
		trees[i+1].leaf_equal = nfdi_equal;
		trees[i+1].leaf_prपूर्णांक = nfdi_prपूर्णांक;
		trees[i+1].leaf_size = nfdi_size;
		trees[i+1].leaf_index = nfdi_index;
		trees[i+1].leaf_emit = nfdi_emit;
	पूर्ण

	/* Finish init. */
	क्रम (i = 0; i != trees_count; i++)
		trees[i].childnode = NODE;
पूर्ण

अटल व्योम trees_populate(व्योम)
अणु
	काष्ठा unicode_data *data;
	अचिन्हित पूर्णांक uniअक्षर;
	अक्षर keyval[4];
	पूर्णांक keylen;
	पूर्णांक i;

	क्रम (i = 0; i != trees_count; i++) अणु
		अगर (verbose > 0) अणु
			म_लिखो("Populating %s_%x\n",
				trees[i].type, trees[i].maxage);
		पूर्ण
		क्रम (uniअक्षर = 0; uniअक्षर != 0x110000; uniअक्षर++) अणु
			अगर (unicode_data[uniअक्षर].gen < 0)
				जारी;
			keylen = utf8encode(keyval, uniअक्षर);
			data = corrections_lookup(&unicode_data[uniअक्षर]);
			अगर (data->correction <= trees[i].maxage)
				data = &unicode_data[uniअक्षर];
			insert(&trees[i], keyval, keylen, data);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम trees_reduce(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक size;
	पूर्णांक changed;

	क्रम (i = 0; i != trees_count; i++)
		prune(&trees[i]);
	क्रम (i = 0; i != trees_count; i++)
		mark_nodes(&trees[i]);
	करो अणु
		size = 0;
		क्रम (i = 0; i != trees_count; i++)
			size = index_nodes(&trees[i], size);
		changed = 0;
		क्रम (i = 0; i != trees_count; i++)
			changed += size_nodes(&trees[i]);
	पूर्ण जबतक (changed);

	utf8data = सुस्मृति(size, 1);
	utf8data_size = size;
	क्रम (i = 0; i != trees_count; i++)
		emit(&trees[i], utf8data);

	अगर (verbose > 0) अणु
		क्रम (i = 0; i != trees_count; i++) अणु
			म_लिखो("%s_%x idx %d\n",
				trees[i].type, trees[i].maxage, trees[i].index);
		पूर्ण
	पूर्ण

	nfdi = utf8data + trees[trees_count-1].index;
	nfdicf = utf8data + trees[trees_count-2].index;

	nfdi_tree = &trees[trees_count-1];
	nfdicf_tree = &trees[trees_count-2];
पूर्ण

अटल व्योम verअगरy(काष्ठा tree *tree)
अणु
	काष्ठा unicode_data *data;
	utf8leaf_t	*leaf;
	अचिन्हित पूर्णांक	uniअक्षर;
	अक्षर		key[4];
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];
	पूर्णांक		report;
	पूर्णांक		nocf;

	अगर (verbose > 0)
		म_लिखो("Verifying %s_%x\n", tree->type, tree->maxage);
	nocf = म_भेद(tree->type, "nfdicf");

	क्रम (uniअक्षर = 0; uniअक्षर != 0x110000; uniअक्षर++) अणु
		report = 0;
		data = corrections_lookup(&unicode_data[uniअक्षर]);
		अगर (data->correction <= tree->maxage)
			data = &unicode_data[uniअक्षर];
		utf8encode(key,uniअक्षर);
		leaf = utf8lookup(tree, hangul, key);

		अगर (!leaf) अणु
			अगर (data->gen != -1)
				report++;
			अगर (uniअक्षर < 0xd800 || uniअक्षर > 0xdfff)
				report++;
		पूर्ण अन्यथा अणु
			अगर (uniअक्षर >= 0xd800 && uniअक्षर <= 0xdfff)
				report++;
			अगर (data->gen == -1)
				report++;
			अगर (data->gen != LEAF_GEN(leaf))
				report++;
			अगर (LEAF_CCC(leaf) == DECOMPOSE) अणु
				अगर (HANGUL_SYLLABLE(data->code)) अणु
					अगर (data->utf8nfdi[0] != HANGUL)
						report++;
				पूर्ण अन्यथा अगर (nocf) अणु
					अगर (!data->utf8nfdi) अणु
						report++;
					पूर्ण अन्यथा अगर (म_भेद(data->utf8nfdi,
							  LEAF_STR(leaf))) अणु
						report++;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (!data->utf8nfdicf &&
					    !data->utf8nfdi) अणु
						report++;
					पूर्ण अन्यथा अगर (data->utf8nfdicf) अणु
						अगर (म_भेद(data->utf8nfdicf,
							   LEAF_STR(leaf)))
							report++;
					पूर्ण अन्यथा अगर (म_भेद(data->utf8nfdi,
							  LEAF_STR(leaf))) अणु
						report++;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (data->ccc != LEAF_CCC(leaf)) अणु
				report++;
			पूर्ण
		पूर्ण
		अगर (report) अणु
			म_लिखो("%X code %X gen %d ccc %d"
				" nfdi -> \"%s\"",
				uniअक्षर, data->code, data->gen,
				data->ccc,
				data->utf8nfdi);
			अगर (leaf) अणु
				म_लिखो(" gen %d ccc %d"
					" nfdi -> \"%s\"",
					LEAF_GEN(leaf),
					LEAF_CCC(leaf),
					LEAF_CCC(leaf) == DECOMPOSE ?
						LEAF_STR(leaf) : "");
			पूर्ण
			म_लिखो("\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम trees_verअगरy(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i != trees_count; i++)
		verअगरy(&trees[i]);
पूर्ण

/* ------------------------------------------------------------------ */

अटल व्योम help(व्योम)
अणु
	म_लिखो("Usage: %s [options]\n", argv0);
	म_लिखो("\n");
	म_लिखो("This program creates an a data trie used for parsing and\n");
	म_लिखो("normalization of UTF-8 strings. The trie is derived from\n");
	म_लिखो("a set of input files from the Unicode character database\n");
	म_लिखो("found at: http://www.unicode.org/Public/UCD/latest/ucd/\n");
	म_लिखो("\n");
	म_लिखो("The generated tree supports two normalization forms:\n");
	म_लिखो("\n");
	म_लिखो("\tnfdi:\n");
	म_लिखो("\t- Apply unicode normalization form NFD.\n");
	म_लिखो("\t- Remove any Default_Ignorable_Code_Point.\n");
	म_लिखो("\n");
	म_लिखो("\tnfdicf:\n");
	म_लिखो("\t- Apply unicode normalization form NFD.\n");
	म_लिखो("\t- Remove any Default_Ignorable_Code_Point.\n");
	म_लिखो("\t- Apply a full casefold (C + F).\n");
	म_लिखो("\n");
	म_लिखो("These forms were chosen as being most useful when dealing\n");
	म_लिखो("with file names: NFD catches most cases where characters\n");
	म_लिखो("should be considered equivalent. The ignorables are mostly\n");
	म_लिखो("invisible, making names hard to type.\n");
	म_लिखो("\n");
	म_लिखो("The options to specify the files to be used are listed\n");
	म_लिखो("below with their default values, which are the names used\n");
	म_लिखो("by version 11.0.0 of the Unicode Character Database.\n");
	म_लिखो("\n");
	म_लिखो("The input files:\n");
	म_लिखो("\t-a %s\n", AGE_NAME);
	म_लिखो("\t-c %s\n", CCC_NAME);
	म_लिखो("\t-p %s\n", PROP_NAME);
	म_लिखो("\t-d %s\n", DATA_NAME);
	म_लिखो("\t-f %s\n", FOLD_NAME);
	म_लिखो("\t-n %s\n", NORM_NAME);
	म_लिखो("\n");
	म_लिखो("Additionally, the generated tables are tested using:\n");
	म_लिखो("\t-t %s\n", TEST_NAME);
	म_लिखो("\n");
	म_लिखो("Finally, the output file:\n");
	म_लिखो("\t-o %s\n", UTF8_NAME);
	म_लिखो("\n");
पूर्ण

अटल व्योम usage(व्योम)
अणु
	help();
	निकास(1);
पूर्ण

अटल व्योम खोलो_fail(स्थिर अक्षर *name, पूर्णांक error)
अणु
	म_लिखो("Error %d opening %s: %s\n", error, name, म_त्रुटि(error));
	निकास(1);
पूर्ण

अटल व्योम file_fail(स्थिर अक्षर *filename)
अणु
	म_लिखो("Error parsing %s\n", filename);
	निकास(1);
पूर्ण

अटल व्योम line_fail(स्थिर अक्षर *filename, स्थिर अक्षर *line)
अणु
	म_लिखो("Error parsing %s:%s\n", filename, line);
	निकास(1);
पूर्ण

/* ------------------------------------------------------------------ */

अटल व्योम prपूर्णांक_utf32(अचिन्हित पूर्णांक *utf32str)
अणु
	पूर्णांक	i;

	क्रम (i = 0; utf32str[i]; i++)
		म_लिखो(" %X", utf32str[i]);
पूर्ण

अटल व्योम prपूर्णांक_utf32nfdi(अचिन्हित पूर्णांक uniअक्षर)
अणु
	म_लिखो(" %X ->", uniअक्षर);
	prपूर्णांक_utf32(unicode_data[uniअक्षर].utf32nfdi);
	म_लिखो("\n");
पूर्ण

अटल व्योम prपूर्णांक_utf32nfdicf(अचिन्हित पूर्णांक uniअक्षर)
अणु
	म_लिखो(" %X ->", uniअक्षर);
	prपूर्णांक_utf32(unicode_data[uniअक्षर].utf32nfdicf);
	म_लिखो("\n");
पूर्ण

/* ------------------------------------------------------------------ */

अटल व्योम age_init(व्योम)
अणु
	खाता *file;
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक last;
	अचिन्हित पूर्णांक uniअक्षर;
	अचिन्हित पूर्णांक major;
	अचिन्हित पूर्णांक minor;
	अचिन्हित पूर्णांक revision;
	पूर्णांक gen;
	पूर्णांक count;
	पूर्णांक ret;

	अगर (verbose > 0)
		म_लिखो("Parsing %s\n", age_name);

	file = ख_खोलो(age_name, "r");
	अगर (!file)
		खोलो_fail(age_name, त्रुटि_सं);
	count = 0;

	gen = 0;
	जबतक (ख_माला_लो(line, LINESIZE, file)) अणु
		ret = माला_पूछो(line, "# Age=V%d_%d_%d",
				&major, &minor, &revision);
		अगर (ret == 3) अणु
			ages_count++;
			अगर (verbose > 1)
				म_लिखो(" Age V%d_%d_%d\n",
					major, minor, revision);
			अगर (!age_valid(major, minor, revision))
				line_fail(age_name, line);
			जारी;
		पूर्ण
		ret = माला_पूछो(line, "# Age=V%d_%d", &major, &minor);
		अगर (ret == 2) अणु
			ages_count++;
			अगर (verbose > 1)
				म_लिखो(" Age V%d_%d\n", major, minor);
			अगर (!age_valid(major, minor, 0))
				line_fail(age_name, line);
			जारी;
		पूर्ण
	पूर्ण

	/* We must have found something above. */
	अगर (verbose > 1)
		म_लिखो("%d age entries\n", ages_count);
	अगर (ages_count == 0 || ages_count > MAXGEN)
		file_fail(age_name);

	/* There is a 0 entry. */
	ages_count++;
	ages = सुस्मृति(ages_count + 1, माप(*ages));
	/* And a guard entry. */
	ages[ages_count] = (अचिन्हित पूर्णांक)-1;

	शुरुआत(file);
	count = 0;
	gen = 0;
	जबतक (ख_माला_लो(line, LINESIZE, file)) अणु
		ret = माला_पूछो(line, "# Age=V%d_%d_%d",
				&major, &minor, &revision);
		अगर (ret == 3) अणु
			ages[++gen] =
				UNICODE_AGE(major, minor, revision);
			अगर (verbose > 1)
				म_लिखो(" Age V%d_%d_%d = gen %d\n",
					major, minor, revision, gen);
			अगर (!age_valid(major, minor, revision))
				line_fail(age_name, line);
			जारी;
		पूर्ण
		ret = माला_पूछो(line, "# Age=V%d_%d", &major, &minor);
		अगर (ret == 2) अणु
			ages[++gen] = UNICODE_AGE(major, minor, 0);
			अगर (verbose > 1)
				म_लिखो(" Age V%d_%d = %d\n",
					major, minor, gen);
			अगर (!age_valid(major, minor, 0))
				line_fail(age_name, line);
			जारी;
		पूर्ण
		ret = माला_पूछो(line, "%X..%X ; %d.%d #",
			     &first, &last, &major, &minor);
		अगर (ret == 4) अणु
			क्रम (uniअक्षर = first; uniअक्षर <= last; uniअक्षर++)
				unicode_data[uniअक्षर].gen = gen;
			count += 1 + last - first;
			अगर (verbose > 1)
				म_लिखो("  %X..%X gen %d\n", first, last, gen);
			अगर (!utf32valid(first) || !utf32valid(last))
				line_fail(age_name, line);
			जारी;
		पूर्ण
		ret = माला_पूछो(line, "%X ; %d.%d #", &uniअक्षर, &major, &minor);
		अगर (ret == 3) अणु
			unicode_data[uniअक्षर].gen = gen;
			count++;
			अगर (verbose > 1)
				म_लिखो("  %X gen %d\n", uniअक्षर, gen);
			अगर (!utf32valid(uniअक्षर))
				line_fail(age_name, line);
			जारी;
		पूर्ण
	पूर्ण
	unicode_maxage = ages[gen];
	ख_बंद(file);

	/* Nix surrogate block */
	अगर (verbose > 1)
		म_लिखो(" Removing surrogate block D800..DFFF\n");
	क्रम (uniअक्षर = 0xd800; uniअक्षर <= 0xdfff; uniअक्षर++)
		unicode_data[uniअक्षर].gen = -1;

	अगर (verbose > 0)
	        म_लिखो("Found %d entries\n", count);
	अगर (count == 0)
		file_fail(age_name);
पूर्ण

अटल व्योम ccc_init(व्योम)
अणु
	खाता *file;
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक last;
	अचिन्हित पूर्णांक uniअक्षर;
	अचिन्हित पूर्णांक value;
	पूर्णांक count;
	पूर्णांक ret;

	अगर (verbose > 0)
		म_लिखो("Parsing %s\n", ccc_name);

	file = ख_खोलो(ccc_name, "r");
	अगर (!file)
		खोलो_fail(ccc_name, त्रुटि_सं);

	count = 0;
	जबतक (ख_माला_लो(line, LINESIZE, file)) अणु
		ret = माला_पूछो(line, "%X..%X ; %d #", &first, &last, &value);
		अगर (ret == 3) अणु
			क्रम (uniअक्षर = first; uniअक्षर <= last; uniअक्षर++) अणु
				unicode_data[uniअक्षर].ccc = value;
                                count++;
			पूर्ण
			अगर (verbose > 1)
				म_लिखो(" %X..%X ccc %d\n", first, last, value);
			अगर (!utf32valid(first) || !utf32valid(last))
				line_fail(ccc_name, line);
			जारी;
		पूर्ण
		ret = माला_पूछो(line, "%X ; %d #", &uniअक्षर, &value);
		अगर (ret == 2) अणु
			unicode_data[uniअक्षर].ccc = value;
                        count++;
			अगर (verbose > 1)
				म_लिखो(" %X ccc %d\n", uniअक्षर, value);
			अगर (!utf32valid(uniअक्षर))
				line_fail(ccc_name, line);
			जारी;
		पूर्ण
	पूर्ण
	ख_बंद(file);

	अगर (verbose > 0)
		म_लिखो("Found %d entries\n", count);
	अगर (count == 0)
		file_fail(ccc_name);
पूर्ण

अटल पूर्णांक ignore_compatibility_क्रमm(अक्षर *type)
अणु
	पूर्णांक i;
	अक्षर *ignored_types[] = अणु"font", "noBreak", "initial", "medial",
				 "final", "isolated", "circle", "super",
				 "sub", "vertical", "wide", "narrow",
				 "small", "square", "fraction", "compat"पूर्ण;

	क्रम (i = 0 ; i < ARRAY_SIZE(ignored_types); i++)
		अगर (म_भेद(type, ignored_types[i]) == 0)
			वापस 1;
	वापस 0;
पूर्ण

अटल व्योम nfdi_init(व्योम)
अणु
	खाता *file;
	अचिन्हित पूर्णांक uniअक्षर;
	अचिन्हित पूर्णांक mapping[19]; /* Magic - guaranteed not to be exceeded. */
	अक्षर *s;
	अक्षर *type;
	अचिन्हित पूर्णांक *um;
	पूर्णांक count;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (verbose > 0)
		म_लिखो("Parsing %s\n", data_name);
	file = ख_खोलो(data_name, "r");
	अगर (!file)
		खोलो_fail(data_name, त्रुटि_सं);

	count = 0;
	जबतक (ख_माला_लो(line, LINESIZE, file)) अणु
		ret = माला_पूछो(line, "%X;%*[^;];%*[^;];%*[^;];%*[^;];%[^;];",
			     &uniअक्षर, buf0);
		अगर (ret != 2)
			जारी;
		अगर (!utf32valid(uniअक्षर))
			line_fail(data_name, line);

		s = buf0;
		/* skip over <tag> */
		अगर (*s == '<') अणु
			type = ++s;
			जबतक (*++s != '>');
			*s++ = '\0';
			अगर(ignore_compatibility_क्रमm(type))
				जारी;
		पूर्ण
		/* decode the decomposition पूर्णांकo UTF-32 */
		i = 0;
		जबतक (*s) अणु
			mapping[i] = म_से_अदीर्घ(s, &s, 16);
			अगर (!utf32valid(mapping[i]))
				line_fail(data_name, line);
			i++;
		पूर्ण
		mapping[i++] = 0;

		um = दो_स्मृति(i * माप(अचिन्हित पूर्णांक));
		स_नकल(um, mapping, i * माप(अचिन्हित पूर्णांक));
		unicode_data[uniअक्षर].utf32nfdi = um;

		अगर (verbose > 1)
			prपूर्णांक_utf32nfdi(uniअक्षर);
		count++;
	पूर्ण
	ख_बंद(file);
	अगर (verbose > 0)
		म_लिखो("Found %d entries\n", count);
	अगर (count == 0)
		file_fail(data_name);
पूर्ण

अटल व्योम nfdicf_init(व्योम)
अणु
	खाता *file;
	अचिन्हित पूर्णांक uniअक्षर;
	अचिन्हित पूर्णांक mapping[19]; /* Magic - guaranteed not to be exceeded. */
	अक्षर status;
	अक्षर *s;
	अचिन्हित पूर्णांक *um;
	पूर्णांक i;
	पूर्णांक count;
	पूर्णांक ret;

	अगर (verbose > 0)
		म_लिखो("Parsing %s\n", fold_name);
	file = ख_खोलो(fold_name, "r");
	अगर (!file)
		खोलो_fail(fold_name, त्रुटि_सं);

	count = 0;
	जबतक (ख_माला_लो(line, LINESIZE, file)) अणु
		ret = माला_पूछो(line, "%X; %c; %[^;];", &uniअक्षर, &status, buf0);
		अगर (ret != 3)
			जारी;
		अगर (!utf32valid(uniअक्षर))
			line_fail(fold_name, line);
		/* Use the C+F हालfold. */
		अगर (status != 'C' && status != 'F')
			जारी;
		s = buf0;
		अगर (*s == '<')
			जबतक (*s++ != ' ')
				;
		i = 0;
		जबतक (*s) अणु
			mapping[i] = म_से_अदीर्घ(s, &s, 16);
			अगर (!utf32valid(mapping[i]))
				line_fail(fold_name, line);
			i++;
		पूर्ण
		mapping[i++] = 0;

		um = दो_स्मृति(i * माप(अचिन्हित पूर्णांक));
		स_नकल(um, mapping, i * माप(अचिन्हित पूर्णांक));
		unicode_data[uniअक्षर].utf32nfdicf = um;

		अगर (verbose > 1)
			prपूर्णांक_utf32nfdicf(uniअक्षर);
		count++;
	पूर्ण
	ख_बंद(file);
	अगर (verbose > 0)
		म_लिखो("Found %d entries\n", count);
	अगर (count == 0)
		file_fail(fold_name);
पूर्ण

अटल व्योम ignore_init(व्योम)
अणु
	खाता *file;
	अचिन्हित पूर्णांक uniअक्षर;
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक last;
	अचिन्हित पूर्णांक *um;
	पूर्णांक count;
	पूर्णांक ret;

	अगर (verbose > 0)
		म_लिखो("Parsing %s\n", prop_name);
	file = ख_खोलो(prop_name, "r");
	अगर (!file)
		खोलो_fail(prop_name, त्रुटि_सं);
	निश्चित(file);
	count = 0;
	जबतक (ख_माला_लो(line, LINESIZE, file)) अणु
		ret = माला_पूछो(line, "%X..%X ; %s # ", &first, &last, buf0);
		अगर (ret == 3) अणु
			अगर (म_भेद(buf0, "Default_Ignorable_Code_Point"))
				जारी;
			अगर (!utf32valid(first) || !utf32valid(last))
				line_fail(prop_name, line);
			क्रम (uniअक्षर = first; uniअक्षर <= last; uniअक्षर++) अणु
				मुक्त(unicode_data[uniअक्षर].utf32nfdi);
				um = दो_स्मृति(माप(अचिन्हित पूर्णांक));
				*um = 0;
				unicode_data[uniअक्षर].utf32nfdi = um;
				मुक्त(unicode_data[uniअक्षर].utf32nfdicf);
				um = दो_स्मृति(माप(अचिन्हित पूर्णांक));
				*um = 0;
				unicode_data[uniअक्षर].utf32nfdicf = um;
				count++;
			पूर्ण
			अगर (verbose > 1)
				म_लिखो(" %X..%X Default_Ignorable_Code_Point\n",
					first, last);
			जारी;
		पूर्ण
		ret = माला_पूछो(line, "%X ; %s # ", &uniअक्षर, buf0);
		अगर (ret == 2) अणु
			अगर (म_भेद(buf0, "Default_Ignorable_Code_Point"))
				जारी;
			अगर (!utf32valid(uniअक्षर))
				line_fail(prop_name, line);
			मुक्त(unicode_data[uniअक्षर].utf32nfdi);
			um = दो_स्मृति(माप(अचिन्हित पूर्णांक));
			*um = 0;
			unicode_data[uniअक्षर].utf32nfdi = um;
			मुक्त(unicode_data[uniअक्षर].utf32nfdicf);
			um = दो_स्मृति(माप(अचिन्हित पूर्णांक));
			*um = 0;
			unicode_data[uniअक्षर].utf32nfdicf = um;
			अगर (verbose > 1)
				म_लिखो(" %X Default_Ignorable_Code_Point\n",
					uniअक्षर);
			count++;
			जारी;
		पूर्ण
	पूर्ण
	ख_बंद(file);

	अगर (verbose > 0)
		म_लिखो("Found %d entries\n", count);
	अगर (count == 0)
		file_fail(prop_name);
पूर्ण

अटल व्योम corrections_init(व्योम)
अणु
	खाता *file;
	अचिन्हित पूर्णांक uniअक्षर;
	अचिन्हित पूर्णांक major;
	अचिन्हित पूर्णांक minor;
	अचिन्हित पूर्णांक revision;
	अचिन्हित पूर्णांक age;
	अचिन्हित पूर्णांक *um;
	अचिन्हित पूर्णांक mapping[19]; /* Magic - guaranteed not to be exceeded. */
	अक्षर *s;
	पूर्णांक i;
	पूर्णांक count;
	पूर्णांक ret;

	अगर (verbose > 0)
		म_लिखो("Parsing %s\n", norm_name);
	file = ख_खोलो(norm_name, "r");
	अगर (!file)
		खोलो_fail(norm_name, त्रुटि_सं);

	count = 0;
	जबतक (ख_माला_लो(line, LINESIZE, file)) अणु
		ret = माला_पूछो(line, "%X;%[^;];%[^;];%d.%d.%d #",
				&uniअक्षर, buf0, buf1,
				&major, &minor, &revision);
		अगर (ret != 6)
			जारी;
		अगर (!utf32valid(uniअक्षर) || !age_valid(major, minor, revision))
			line_fail(norm_name, line);
		count++;
	पूर्ण
	corrections = सुस्मृति(count, माप(काष्ठा unicode_data));
	corrections_count = count;
	शुरुआत(file);

	count = 0;
	जबतक (ख_माला_लो(line, LINESIZE, file)) अणु
		ret = माला_पूछो(line, "%X;%[^;];%[^;];%d.%d.%d #",
				&uniअक्षर, buf0, buf1,
				&major, &minor, &revision);
		अगर (ret != 6)
			जारी;
		अगर (!utf32valid(uniअक्षर) || !age_valid(major, minor, revision))
			line_fail(norm_name, line);
		corrections[count] = unicode_data[uniअक्षर];
		निश्चित(corrections[count].code == uniअक्षर);
		age = UNICODE_AGE(major, minor, revision);
		corrections[count].correction = age;

		i = 0;
		s = buf0;
		जबतक (*s) अणु
			mapping[i] = म_से_अदीर्घ(s, &s, 16);
			अगर (!utf32valid(mapping[i]))
				line_fail(norm_name, line);
			i++;
		पूर्ण
		mapping[i++] = 0;

		um = दो_स्मृति(i * माप(अचिन्हित पूर्णांक));
		स_नकल(um, mapping, i * माप(अचिन्हित पूर्णांक));
		corrections[count].utf32nfdi = um;

		अगर (verbose > 1)
			म_लिखो(" %X -> %s -> %s V%d_%d_%d\n",
				uniअक्षर, buf0, buf1, major, minor, revision);
		count++;
	पूर्ण
	ख_बंद(file);

	अगर (verbose > 0)
	        म_लिखो("Found %d entries\n", count);
	अगर (count == 0)
		file_fail(norm_name);
पूर्ण

/* ------------------------------------------------------------------ */

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
 *          d = <LPart, VPart, TPart>
 *   पूर्ण
 *
 */

अटल व्योम hangul_decompose(व्योम)
अणु
	अचिन्हित पूर्णांक sb = 0xAC00;
	अचिन्हित पूर्णांक lb = 0x1100;
	अचिन्हित पूर्णांक vb = 0x1161;
	अचिन्हित पूर्णांक tb = 0x11a7;
	/* अचिन्हित पूर्णांक lc = 19; */
	अचिन्हित पूर्णांक vc = 21;
	अचिन्हित पूर्णांक tc = 28;
	अचिन्हित पूर्णांक nc = (vc * tc);
	/* अचिन्हित पूर्णांक sc = (lc * nc); */
	अचिन्हित पूर्णांक uniअक्षर;
	अचिन्हित पूर्णांक mapping[4];
	अचिन्हित पूर्णांक *um;
        पूर्णांक count;
	पूर्णांक i;

	अगर (verbose > 0)
		म_लिखो("Decomposing hangul\n");
	/* Hangul */
	count = 0;
	क्रम (uniअक्षर = 0xAC00; uniअक्षर <= 0xD7A3; uniअक्षर++) अणु
		अचिन्हित पूर्णांक si = uniअक्षर - sb;
		अचिन्हित पूर्णांक li = si / nc;
		अचिन्हित पूर्णांक vi = (si % nc) / tc;
		अचिन्हित पूर्णांक ti = si % tc;

		i = 0;
		mapping[i++] = lb + li;
		mapping[i++] = vb + vi;
		अगर (ti)
			mapping[i++] = tb + ti;
		mapping[i++] = 0;

		निश्चित(!unicode_data[uniअक्षर].utf32nfdi);
		um = दो_स्मृति(i * माप(अचिन्हित पूर्णांक));
		स_नकल(um, mapping, i * माप(अचिन्हित पूर्णांक));
		unicode_data[uniअक्षर].utf32nfdi = um;

		निश्चित(!unicode_data[uniअक्षर].utf32nfdicf);
		um = दो_स्मृति(i * माप(अचिन्हित पूर्णांक));
		स_नकल(um, mapping, i * माप(अचिन्हित पूर्णांक));
		unicode_data[uniअक्षर].utf32nfdicf = um;

		/*
		 * Add a cookie as a reminder that the hangul syllable
		 * decompositions must not be stored in the generated
		 * trie.
		 */
		unicode_data[uniअक्षर].utf8nfdi = दो_स्मृति(2);
		unicode_data[uniअक्षर].utf8nfdi[0] = HANGUL;
		unicode_data[uniअक्षर].utf8nfdi[1] = '\0';

		अगर (verbose > 1)
			prपूर्णांक_utf32nfdi(uniअक्षर);

		count++;
	पूर्ण
	अगर (verbose > 0)
		म_लिखो("Created %d entries\n", count);
पूर्ण

अटल व्योम nfdi_decompose(व्योम)
अणु
	अचिन्हित पूर्णांक uniअक्षर;
	अचिन्हित पूर्णांक mapping[19]; /* Magic - guaranteed not to be exceeded. */
	अचिन्हित पूर्णांक *um;
	अचिन्हित पूर्णांक *dc;
	पूर्णांक count;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक ret;

	अगर (verbose > 0)
		म_लिखो("Decomposing nfdi\n");

	count = 0;
	क्रम (uniअक्षर = 0; uniअक्षर != 0x110000; uniअक्षर++) अणु
		अगर (!unicode_data[uniअक्षर].utf32nfdi)
			जारी;
		क्रम (;;) अणु
			ret = 1;
			i = 0;
			um = unicode_data[uniअक्षर].utf32nfdi;
			जबतक (*um) अणु
				dc = unicode_data[*um].utf32nfdi;
				अगर (dc) अणु
					क्रम (j = 0; dc[j]; j++)
						mapping[i++] = dc[j];
					ret = 0;
				पूर्ण अन्यथा अणु
					mapping[i++] = *um;
				पूर्ण
				um++;
			पूर्ण
			mapping[i++] = 0;
			अगर (ret)
				अवरोध;
			मुक्त(unicode_data[uniअक्षर].utf32nfdi);
			um = दो_स्मृति(i * माप(अचिन्हित पूर्णांक));
			स_नकल(um, mapping, i * माप(अचिन्हित पूर्णांक));
			unicode_data[uniअक्षर].utf32nfdi = um;
		पूर्ण
		/* Add this decomposition to nfdicf अगर there is no entry. */
		अगर (!unicode_data[uniअक्षर].utf32nfdicf) अणु
			um = दो_स्मृति(i * माप(अचिन्हित पूर्णांक));
			स_नकल(um, mapping, i * माप(अचिन्हित पूर्णांक));
			unicode_data[uniअक्षर].utf32nfdicf = um;
		पूर्ण
		अगर (verbose > 1)
			prपूर्णांक_utf32nfdi(uniअक्षर);
		count++;
	पूर्ण
	अगर (verbose > 0)
		म_लिखो("Processed %d entries\n", count);
पूर्ण

अटल व्योम nfdicf_decompose(व्योम)
अणु
	अचिन्हित पूर्णांक uniअक्षर;
	अचिन्हित पूर्णांक mapping[19]; /* Magic - guaranteed not to be exceeded. */
	अचिन्हित पूर्णांक *um;
	अचिन्हित पूर्णांक *dc;
	पूर्णांक count;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक ret;

	अगर (verbose > 0)
		म_लिखो("Decomposing nfdicf\n");
	count = 0;
	क्रम (uniअक्षर = 0; uniअक्षर != 0x110000; uniअक्षर++) अणु
		अगर (!unicode_data[uniअक्षर].utf32nfdicf)
			जारी;
		क्रम (;;) अणु
			ret = 1;
			i = 0;
			um = unicode_data[uniअक्षर].utf32nfdicf;
			जबतक (*um) अणु
				dc = unicode_data[*um].utf32nfdicf;
				अगर (dc) अणु
					क्रम (j = 0; dc[j]; j++)
						mapping[i++] = dc[j];
					ret = 0;
				पूर्ण अन्यथा अणु
					mapping[i++] = *um;
				पूर्ण
				um++;
			पूर्ण
			mapping[i++] = 0;
			अगर (ret)
				अवरोध;
			मुक्त(unicode_data[uniअक्षर].utf32nfdicf);
			um = दो_स्मृति(i * माप(अचिन्हित पूर्णांक));
			स_नकल(um, mapping, i * माप(अचिन्हित पूर्णांक));
			unicode_data[uniअक्षर].utf32nfdicf = um;
		पूर्ण
		अगर (verbose > 1)
			prपूर्णांक_utf32nfdicf(uniअक्षर);
		count++;
	पूर्ण
	अगर (verbose > 0)
		म_लिखो("Processed %d entries\n", count);
पूर्ण

/* ------------------------------------------------------------------ */

पूर्णांक utf8agemax(काष्ठा tree *, स्थिर अक्षर *);
पूर्णांक utf8nagemax(काष्ठा tree *, स्थिर अक्षर *, माप_प्रकार);
पूर्णांक utf8agemin(काष्ठा tree *, स्थिर अक्षर *);
पूर्णांक utf8nagemin(काष्ठा tree *, स्थिर अक्षर *, माप_प्रकार);
sमाप_प्रकार utf8len(काष्ठा tree *, स्थिर अक्षर *);
sमाप_प्रकार utf8nlen(काष्ठा tree *, स्थिर अक्षर *, माप_प्रकार);
काष्ठा utf8cursor;
पूर्णांक utf8cursor(काष्ठा utf8cursor *, काष्ठा tree *, स्थिर अक्षर *);
पूर्णांक utf8ncursor(काष्ठा utf8cursor *, काष्ठा tree *, स्थिर अक्षर *, माप_प्रकार);
पूर्णांक utf8byte(काष्ठा utf8cursor *);

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
 *          d = <LPart, VPart, TPart>
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
अटल utf8leaf_t *utf8hangul(स्थिर अक्षर *str, अचिन्हित अक्षर *hangul)
अणु
	अचिन्हित पूर्णांक	si;
	अचिन्हित पूर्णांक	li;
	अचिन्हित पूर्णांक	vi;
	अचिन्हित पूर्णांक	ti;
	अचिन्हित अक्षर	*h;

	/* Calculate the SI, LI, VI, and TI values. */
	si = utf8decode(str) - SB;
	li = si / NC;
	vi = (si % NC) / TC;
	ti = si % TC;

	/* Fill in base of leaf. */
	h = hangul;
	LEAF_GEN(h) = 2;
	LEAF_CCC(h) = DECOMPOSE;
	h += 2;

	/* Add LPart, a 3-byte UTF-8 sequence. */
	h += utf8encode((अक्षर *)h, li + LB);

	/* Add VPart, a 3-byte UTF-8 sequence. */
	h += utf8encode((अक्षर *)h, vi + VB);

	/* Add TPart अगर required, also a 3-byte UTF-8 sequence. */
	अगर (ti)
		h += utf8encode((अक्षर *)h, ti + TB);

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
अटल utf8leaf_t *utf8nlookup(काष्ठा tree *tree, अचिन्हित अक्षर *hangul,
			       स्थिर अक्षर *s, माप_प्रकार len)
अणु
	utf8trie_t	*trie;
	पूर्णांक		offlen;
	पूर्णांक		offset;
	पूर्णांक		mask;
	पूर्णांक		node;

	अगर (!tree)
		वापस शून्य;
	अगर (len == 0)
		वापस शून्य;
	node = 1;
	trie = utf8data + tree->index;
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
 * Forwards to trie_nlookup().
 */
अटल utf8leaf_t *utf8lookup(काष्ठा tree *tree, अचिन्हित अक्षर *hangul,
			      स्थिर अक्षर *s)
अणु
	वापस utf8nlookup(tree, hangul, s, (माप_प्रकार)-1);
पूर्ण

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
 * Maximum age of any अक्षरacter in s.
 * Return -1 अगर s is not valid UTF-8 unicode.
 * Return 0 अगर only non-asचिन्हित code poपूर्णांकs are used.
 */
पूर्णांक utf8agemax(काष्ठा tree *tree, स्थिर अक्षर *s)
अणु
	utf8leaf_t	*leaf;
	पूर्णांक		age = 0;
	पूर्णांक		leaf_age;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!tree)
		वापस -1;

	जबतक (*s) अणु
		leaf = utf8lookup(tree, hangul, s);
		अगर (!leaf)
			वापस -1;
		leaf_age = ages[LEAF_GEN(leaf)];
		अगर (leaf_age <= tree->maxage && leaf_age > age)
			age = leaf_age;
		s += utf8clen(s);
	पूर्ण
	वापस age;
पूर्ण

/*
 * Minimum age of any अक्षरacter in s.
 * Return -1 अगर s is not valid UTF-8 unicode.
 * Return 0 अगर non-asचिन्हित code poपूर्णांकs are used.
 */
पूर्णांक utf8agemin(काष्ठा tree *tree, स्थिर अक्षर *s)
अणु
	utf8leaf_t	*leaf;
	पूर्णांक		age;
	पूर्णांक		leaf_age;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!tree)
		वापस -1;
	age = tree->maxage;
	जबतक (*s) अणु
		leaf = utf8lookup(tree, hangul, s);
		अगर (!leaf)
			वापस -1;
		leaf_age = ages[LEAF_GEN(leaf)];
		अगर (leaf_age <= tree->maxage && leaf_age < age)
			age = leaf_age;
		s += utf8clen(s);
	पूर्ण
	वापस age;
पूर्ण

/*
 * Maximum age of any अक्षरacter in s, touch at most len bytes.
 * Return -1 अगर s is not valid UTF-8 unicode.
 */
पूर्णांक utf8nagemax(काष्ठा tree *tree, स्थिर अक्षर *s, माप_प्रकार len)
अणु
	utf8leaf_t	*leaf;
	पूर्णांक		age = 0;
	पूर्णांक		leaf_age;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!tree)
		वापस -1;

        जबतक (len && *s) अणु
		leaf = utf8nlookup(tree, hangul, s, len);
		अगर (!leaf)
			वापस -1;
		leaf_age = ages[LEAF_GEN(leaf)];
		अगर (leaf_age <= tree->maxage && leaf_age > age)
			age = leaf_age;
		len -= utf8clen(s);
		s += utf8clen(s);
	पूर्ण
	वापस age;
पूर्ण

/*
 * Maximum age of any अक्षरacter in s, touch at most len bytes.
 * Return -1 अगर s is not valid UTF-8 unicode.
 */
पूर्णांक utf8nagemin(काष्ठा tree *tree, स्थिर अक्षर *s, माप_प्रकार len)
अणु
	utf8leaf_t	*leaf;
	पूर्णांक		leaf_age;
	पूर्णांक		age;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!tree)
		वापस -1;
	age = tree->maxage;
        जबतक (len && *s) अणु
		leaf = utf8nlookup(tree, hangul, s, len);
		अगर (!leaf)
			वापस -1;
		leaf_age = ages[LEAF_GEN(leaf)];
		अगर (leaf_age <= tree->maxage && leaf_age < age)
			age = leaf_age;
		len -= utf8clen(s);
		s += utf8clen(s);
	पूर्ण
	वापस age;
पूर्ण

/*
 * Length of the normalization of s.
 * Return -1 अगर s is not valid UTF-8 unicode.
 *
 * A string of Default_Ignorable_Code_Poपूर्णांक has length 0.
 */
sमाप_प्रकार utf8len(काष्ठा tree *tree, स्थिर अक्षर *s)
अणु
	utf8leaf_t	*leaf;
	माप_प्रकार		ret = 0;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!tree)
		वापस -1;
	जबतक (*s) अणु
		leaf = utf8lookup(tree, hangul, s);
		अगर (!leaf)
			वापस -1;
		अगर (ages[LEAF_GEN(leaf)] > tree->maxage)
			ret += utf8clen(s);
		अन्यथा अगर (LEAF_CCC(leaf) == DECOMPOSE)
			ret += म_माप(LEAF_STR(leaf));
		अन्यथा
			ret += utf8clen(s);
		s += utf8clen(s);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Length of the normalization of s, touch at most len bytes.
 * Return -1 अगर s is not valid UTF-8 unicode.
 */
sमाप_प्रकार utf8nlen(काष्ठा tree *tree, स्थिर अक्षर *s, माप_प्रकार len)
अणु
	utf8leaf_t	*leaf;
	माप_प्रकार		ret = 0;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];

	अगर (!tree)
		वापस -1;
	जबतक (len && *s) अणु
		leaf = utf8nlookup(tree, hangul, s, len);
		अगर (!leaf)
			वापस -1;
		अगर (ages[LEAF_GEN(leaf)] > tree->maxage)
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

/*
 * Cursor काष्ठाure used by the normalizer.
 */
काष्ठा utf8cursor अणु
	काष्ठा tree	*tree;
	स्थिर अक्षर	*s;
	स्थिर अक्षर	*p;
	स्थिर अक्षर	*ss;
	स्थिर अक्षर	*sp;
	अचिन्हित पूर्णांक	len;
	अचिन्हित पूर्णांक	slen;
	लघु पूर्णांक	ccc;
	लघु पूर्णांक	nccc;
	अचिन्हित पूर्णांक	uniअक्षर;
	अचिन्हित अक्षर	hangul[UTF8HANGULLEAF];
पूर्ण;

/*
 * Set up an utf8cursor क्रम use by utf8byte().
 *
 *   s      : string.
 *   len    : length of s.
 *   u8c    : poपूर्णांकer to cursor.
 *   trie   : utf8trie_t to use क्रम normalization.
 *
 * Returns -1 on error, 0 on success.
 */
पूर्णांक utf8ncursor(काष्ठा utf8cursor *u8c, काष्ठा tree *tree, स्थिर अक्षर *s,
		माप_प्रकार len)
अणु
	अगर (!tree)
		वापस -1;
	अगर (!s)
		वापस -1;
	u8c->tree = tree;
	u8c->s = s;
	u8c->p = शून्य;
	u8c->ss = शून्य;
	u8c->sp = शून्य;
	u8c->len = len;
	u8c->slen = 0;
	u8c->ccc = STOPPER;
	u8c->nccc = STOPPER;
	u8c->uniअक्षर = 0;
	/* Check we didn't clobber the maximum length. */
	अगर (u8c->len != len)
		वापस -1;
	/* The first byte of s may not be an utf8 continuation. */
	अगर (len > 0 && (*s & 0xC0) == 0x80)
		वापस -1;
	वापस 0;
पूर्ण

/*
 * Set up an utf8cursor क्रम use by utf8byte().
 *
 *   s      : NUL-terminated string.
 *   u8c    : poपूर्णांकer to cursor.
 *   trie   : utf8trie_t to use क्रम normalization.
 *
 * Returns -1 on error, 0 on success.
 */
पूर्णांक utf8cursor(काष्ठा utf8cursor *u8c, काष्ठा tree *tree, स्थिर अक्षर *s)
अणु
	वापस utf8ncursor(u8c, tree, s, (अचिन्हित पूर्णांक)-1);
पूर्ण

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
 *  u8c->ccc == -1  -> this is the first scan of a repeating scan.
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
			leaf = utf8lookup(u8c->tree, u8c->hangul, u8c->s);
		पूर्ण अन्यथा अणु
			leaf = utf8nlookup(u8c->tree, u8c->hangul,
					   u8c->s, u8c->len);
		पूर्ण

		/* No leaf found implies that the input is a binary blob. */
		अगर (!leaf)
			वापस -1;

		/* Characters that are too new have CCC 0. */
		अगर (ages[LEAF_GEN(leaf)] > u8c->tree->maxage) अणु
			ccc = STOPPER;
		पूर्ण अन्यथा अगर ((ccc = LEAF_CCC(leaf)) == DECOMPOSE) अणु
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
			leaf = utf8lookup(u8c->tree, u8c->hangul, u8c->s);
			ccc = LEAF_CCC(leaf);
		पूर्ण
		u8c->uniअक्षर = utf8decode(u8c->s);

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
			निश्चित(u8c->ccc == STOPPER);
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

/* ------------------------------------------------------------------ */

अटल पूर्णांक normalize_line(काष्ठा tree *tree)
अणु
	अक्षर *s;
	अक्षर *t;
	पूर्णांक c;
	काष्ठा utf8cursor u8c;

	/* First test: null-terminated string. */
	s = buf2;
	t = buf3;
	अगर (utf8cursor(&u8c, tree, s))
		वापस -1;
	जबतक ((c = utf8byte(&u8c)) > 0)
		अगर (c != (अचिन्हित अक्षर)*t++)
			वापस -1;
	अगर (c < 0)
		वापस -1;
	अगर (*t != 0)
		वापस -1;

	/* Second test: length-limited string. */
	s = buf2;
	/* Replace NUL with a value that will cause an error अगर seen. */
	s[म_माप(s) + 1] = -1;
	t = buf3;
	अगर (utf8cursor(&u8c, tree, s))
		वापस -1;
	जबतक ((c = utf8byte(&u8c)) > 0)
		अगर (c != (अचिन्हित अक्षर)*t++)
			वापस -1;
	अगर (c < 0)
		वापस -1;
	अगर (*t != 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम normalization_test(व्योम)
अणु
	खाता *file;
	अचिन्हित पूर्णांक uniअक्षर;
	काष्ठा unicode_data *data;
	अक्षर *s;
	अक्षर *t;
	पूर्णांक ret;
	पूर्णांक ignorables;
	पूर्णांक tests = 0;
	पूर्णांक failures = 0;

	अगर (verbose > 0)
		म_लिखो("Parsing %s\n", test_name);
	/* Step one, पढ़ो data from file. */
	file = ख_खोलो(test_name, "r");
	अगर (!file)
		खोलो_fail(test_name, त्रुटि_सं);

	जबतक (ख_माला_लो(line, LINESIZE, file)) अणु
		ret = माला_पूछो(line, "%[^;];%*[^;];%[^;];%*[^;];%*[^;];",
			     buf0, buf1);
		अगर (ret != 2 || *line == '#')
			जारी;
		s = buf0;
		t = buf2;
		जबतक (*s) अणु
			uniअक्षर = म_से_अदीर्घ(s, &s, 16);
			t += utf8encode(t, uniअक्षर);
		पूर्ण
		*t = '\0';

		ignorables = 0;
		s = buf1;
		t = buf3;
		जबतक (*s) अणु
			uniअक्षर = म_से_अदीर्घ(s, &s, 16);
			data = &unicode_data[uniअक्षर];
			अगर (data->utf8nfdi && !*data->utf8nfdi)
				ignorables = 1;
			अन्यथा
				t += utf8encode(t, uniअक्षर);
		पूर्ण
		*t = '\0';

		tests++;
		अगर (normalize_line(nfdi_tree) < 0) अणु
			म_लिखो("Line %s -> %s", buf0, buf1);
			अगर (ignorables)
				म_लिखो(" (ignorables removed)");
			म_लिखो(" failure\n");
			failures++;
		पूर्ण
	पूर्ण
	ख_बंद(file);
	अगर (verbose > 0)
		म_लिखो("Ran %d tests with %d failures\n", tests, failures);
	अगर (failures)
		file_fail(test_name);
पूर्ण

/* ------------------------------------------------------------------ */

अटल व्योम ग_लिखो_file(व्योम)
अणु
	खाता *file;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक t;
	पूर्णांक gen;

	अगर (verbose > 0)
		म_लिखो("Writing %s\n", utf8_name);
	file = ख_खोलो(utf8_name, "w");
	अगर (!file)
		खोलो_fail(utf8_name, त्रुटि_सं);

	ख_लिखो(file, "/* This file is generated code, do not edit. */\n");
	ख_लिखो(file, "#ifndef __INCLUDED_FROM_UTF8NORM_C__\n");
	ख_लिखो(file, "#error Only nls_utf8-norm.c should include this file.\n");
	ख_लिखो(file, "#endif\n");
	ख_लिखो(file, "\n");
	ख_लिखो(file, "static const unsigned int utf8vers = %#x;\n",
		unicode_maxage);
	ख_लिखो(file, "\n");
	ख_लिखो(file, "static const unsigned int utf8agetab[] = {\n");
	क्रम (i = 0; i != ages_count; i++)
		ख_लिखो(file, "\t%#x%s\n", ages[i],
			ages[i] == unicode_maxage ? "" : ",");
	ख_लिखो(file, "};\n");
	ख_लिखो(file, "\n");
	ख_लिखो(file, "static const struct utf8data utf8nfdicfdata[] = {\n");
	t = 0;
	क्रम (gen = 0; gen < ages_count; gen++) अणु
		ख_लिखो(file, "\t{ %#x, %d }%s\n",
			ages[gen], trees[t].index,
			ages[gen] == unicode_maxage ? "" : ",");
		अगर (trees[t].maxage == ages[gen])
			t += 2;
	पूर्ण
	ख_लिखो(file, "};\n");
	ख_लिखो(file, "\n");
	ख_लिखो(file, "static const struct utf8data utf8nfdidata[] = {\n");
	t = 1;
	क्रम (gen = 0; gen < ages_count; gen++) अणु
		ख_लिखो(file, "\t{ %#x, %d }%s\n",
			ages[gen], trees[t].index,
			ages[gen] == unicode_maxage ? "" : ",");
		अगर (trees[t].maxage == ages[gen])
			t += 2;
	पूर्ण
	ख_लिखो(file, "};\n");
	ख_लिखो(file, "\n");
	ख_लिखो(file, "static const unsigned char utf8data[%zd] = {\n",
		utf8data_size);
	t = 0;
	क्रम (i = 0; i != utf8data_size; i += 16) अणु
		अगर (i == trees[t].index) अणु
			ख_लिखो(file, "\t/* %s_%x */\n",
				trees[t].type, trees[t].maxage);
			अगर (t < trees_count-1)
				t++;
		पूर्ण
		ख_लिखो(file, "\t");
		क्रम (j = i; j != i + 16; j++)
			ख_लिखो(file, "0x%.2x%s", utf8data[j],
				(j < utf8data_size -1 ? "," : ""));
		ख_लिखो(file, "\n");
	पूर्ण
	ख_लिखो(file, "};\n");
	ख_बंद(file);
पूर्ण

/* ------------------------------------------------------------------ */

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अचिन्हित पूर्णांक uniअक्षर;
	पूर्णांक opt;

	argv0 = argv[0];

	जबतक ((opt = getopt(argc, argv, "a:c:d:f:hn:o:p:t:v")) != -1) अणु
		चयन (opt) अणु
		हाल 'a':
			age_name = optarg;
			अवरोध;
		हाल 'c':
			ccc_name = optarg;
			अवरोध;
		हाल 'd':
			data_name = optarg;
			अवरोध;
		हाल 'f':
			fold_name = optarg;
			अवरोध;
		हाल 'n':
			norm_name = optarg;
			अवरोध;
		हाल 'o':
			utf8_name = optarg;
			अवरोध;
		हाल 'p':
			prop_name = optarg;
			अवरोध;
		हाल 't':
			test_name = optarg;
			अवरोध;
		हाल 'v':
			verbose++;
			अवरोध;
		हाल 'h':
			help();
			निकास(0);
		शेष:
			usage();
		पूर्ण
	पूर्ण

	अगर (verbose > 1)
		help();
	क्रम (uniअक्षर = 0; uniअक्षर != 0x110000; uniअक्षर++)
		unicode_data[uniअक्षर].code = uniअक्षर;
	age_init();
	ccc_init();
	nfdi_init();
	nfdicf_init();
	ignore_init();
	corrections_init();
	hangul_decompose();
	nfdi_decompose();
	nfdicf_decompose();
	utf8_init();
	trees_init();
	trees_populate();
	trees_reduce();
	trees_verअगरy();
	/* Prevent "unused function" warning. */
	(व्योम)lookup(nfdi_tree, " ");
	अगर (verbose > 2)
		tree_walk(nfdi_tree);
	अगर (verbose > 2)
		tree_walk(nfdicf_tree);
	normalization_test();
	ग_लिखो_file();

	वापस 0;
पूर्ण
