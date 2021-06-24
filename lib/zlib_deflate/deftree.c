<शैली गुरु>
/* +++ trees.c */
/* trees.c -- output deflated data using Huffman coding
 * Copyright (C) 1995-1996 Jean-loup Gailly
 * For conditions of distribution and use, see copyright notice in zlib.h 
 */

/*
 *  ALGORITHM
 *
 *      The "deflation" process uses several Huffman trees. The more
 *      common source values are represented by लघुer bit sequences.
 *
 *      Each code tree is stored in a compressed क्रमm which is itself
 * a Huffman encoding of the lengths of all the code strings (in
 * ascending order by source values).  The actual code strings are
 * reस्थिरructed from the lengths in the inflate process, as described
 * in the deflate specअगरication.
 *
 *  REFERENCES
 *
 *      Deutsch, L.P.,"'Deflate' Compressed Data Format Specification".
 *      Available in ftp.uu.net:/pub/archiving/zip/करोc/deflate-1.1.करोc
 *
 *      Storer, James A.
 *          Data Compression:  Methods and Theory, pp. 49-50.
 *          Computer Science Press, 1988.  ISBN 0-7167-8156-5.
 *
 *      Sedgewick, R.
 *          Algorithms, p290.
 *          Addison-Wesley, 1983. ISBN 0-201-06672-6.
 */

/* From: trees.c,v 1.11 1996/07/24 13:41:06 me Exp $ */

/* #समावेश "deflate.h" */

#समावेश <linux/zutil.h>
#समावेश <linux/bitrev.h>
#समावेश "defutil.h"

#अगर_घोषित DEBUG_ZLIB
#  include <प्रकार.स>
#पूर्ण_अगर

/* ===========================================================================
 * Constants
 */

#घोषणा MAX_BL_BITS 7
/* Bit length codes must not exceed MAX_BL_BITS bits */

#घोषणा END_BLOCK 256
/* end of block literal code */

#घोषणा REP_3_6      16
/* repeat previous bit length 3-6 बार (2 bits of repeat count) */

#घोषणा REPZ_3_10    17
/* repeat a zero length 3-10 बार  (3 bits of repeat count) */

#घोषणा REPZ_11_138  18
/* repeat a zero length 11-138 बार  (7 bits of repeat count) */

अटल स्थिर पूर्णांक extra_lbits[LENGTH_CODES] /* extra bits क्रम each length code */
   = अणु0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0पूर्ण;

अटल स्थिर पूर्णांक extra_dbits[D_CODES] /* extra bits क्रम each distance code */
   = अणु0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13पूर्ण;

अटल स्थिर पूर्णांक extra_blbits[BL_CODES]/* extra bits क्रम each bit length code */
   = अणु0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7पूर्ण;

अटल स्थिर uch bl_order[BL_CODES]
   = अणु16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15पूर्ण;
/* The lengths of the bit length codes are sent in order of decreasing
 * probability, to aव्योम transmitting the lengths क्रम unused bit length codes.
 */

/* ===========================================================================
 * Local data. These are initialized only once.
 */

अटल ct_data अटल_ltree[L_CODES+2];
/* The अटल literal tree. Since the bit lengths are imposed, there is no
 * need क्रम the L_CODES extra codes used during heap स्थिरruction. However
 * The codes 286 and 287 are needed to build a canonical tree (see zlib_tr_init
 * below).
 */

अटल ct_data अटल_dtree[D_CODES];
/* The अटल distance tree. (Actually a trivial tree since all codes use
 * 5 bits.)
 */

अटल uch dist_code[512];
/* distance codes. The first 256 values correspond to the distances
 * 3 .. 258, the last 256 values correspond to the top 8 bits of
 * the 15 bit distances.
 */

अटल uch length_code[MAX_MATCH-MIN_MATCH+1];
/* length code क्रम each normalized match length (0 == MIN_MATCH) */

अटल पूर्णांक base_length[LENGTH_CODES];
/* First normalized length क्रम each code (0 = MIN_MATCH) */

अटल पूर्णांक base_dist[D_CODES];
/* First normalized distance क्रम each code (0 = distance of 1) */

काष्ठा अटल_tree_desc_s अणु
    स्थिर ct_data *अटल_tree;  /* अटल tree or शून्य */
    स्थिर पूर्णांक *extra_bits;       /* extra bits क्रम each code or शून्य */
    पूर्णांक     extra_base;          /* base index क्रम extra_bits */
    पूर्णांक     elems;               /* max number of elements in the tree */
    पूर्णांक     max_length;          /* max bit length क्रम the codes */
पूर्ण;

अटल अटल_tree_desc  अटल_l_desc =
अणुअटल_ltree, extra_lbits, LITERALS+1, L_CODES, MAX_BITSपूर्ण;

अटल अटल_tree_desc  अटल_d_desc =
अणुअटल_dtree, extra_dbits, 0,          D_CODES, MAX_BITSपूर्ण;

अटल अटल_tree_desc  अटल_bl_desc =
अणु(स्थिर ct_data *)0, extra_blbits, 0,   BL_CODES, MAX_BL_BITSपूर्ण;

/* ===========================================================================
 * Local (अटल) routines in this file.
 */

अटल व्योम tr_अटल_init (व्योम);
अटल व्योम init_block     (deflate_state *s);
अटल व्योम pqकरोwnheap     (deflate_state *s, ct_data *tree, पूर्णांक k);
अटल व्योम gen_bitlen     (deflate_state *s, tree_desc *desc);
अटल व्योम gen_codes      (ct_data *tree, पूर्णांक max_code, ush *bl_count);
अटल व्योम build_tree     (deflate_state *s, tree_desc *desc);
अटल व्योम scan_tree      (deflate_state *s, ct_data *tree, पूर्णांक max_code);
अटल व्योम send_tree      (deflate_state *s, ct_data *tree, पूर्णांक max_code);
अटल पूर्णांक  build_bl_tree  (deflate_state *s);
अटल व्योम send_all_trees (deflate_state *s, पूर्णांक lcodes, पूर्णांक dcodes,
                           पूर्णांक blcodes);
अटल व्योम compress_block (deflate_state *s, ct_data *ltree,
                           ct_data *dtree);
अटल व्योम set_data_type  (deflate_state *s);
अटल व्योम bi_flush       (deflate_state *s);
अटल व्योम copy_block     (deflate_state *s, अक्षर *buf, अचिन्हित len,
                           पूर्णांक header);

#अगर_अघोषित DEBUG_ZLIB
#  define send_code(s, c, tree) send_bits(s, tree[c].Code, tree[c].Len)
   /* Send a code of the given tree. c and tree must not have side effects */

#अन्यथा /* DEBUG_ZLIB */
#  define send_code(s, c, tree) \
     अणु अगर (z_verbose>2) ख_लिखो(मानक_त्रुटि,"\ncd %3d ",(c)); \
       send_bits(s, tree[c].Code, tree[c].Len); पूर्ण
#पूर्ण_अगर

#घोषणा d_code(dist) \
   ((dist) < 256 ? dist_code[dist] : dist_code[256+((dist)>>7)])
/* Mapping from a distance to a distance code. dist is the distance - 1 and
 * must not have side effects. dist_code[256] and dist_code[257] are never
 * used.
 */

/* ===========================================================================
 * Initialize the various 'constant' tables. In a multi-thपढ़ोed environment,
 * this function may be called by two thपढ़ोs concurrently, but this is
 * harmless since both invocations करो exactly the same thing.
 */
अटल व्योम tr_अटल_init(व्योम)
अणु
    अटल पूर्णांक अटल_init_करोne;
    पूर्णांक n;        /* iterates over tree elements */
    पूर्णांक bits;     /* bit counter */
    पूर्णांक length;   /* length value */
    पूर्णांक code;     /* code value */
    पूर्णांक dist;     /* distance index */
    ush bl_count[MAX_BITS+1];
    /* number of codes at each bit length क्रम an optimal tree */

    अगर (अटल_init_करोne) वापस;

    /* Initialize the mapping length (0..255) -> length code (0..28) */
    length = 0;
    क्रम (code = 0; code < LENGTH_CODES-1; code++) अणु
        base_length[code] = length;
        क्रम (n = 0; n < (1<<extra_lbits[code]); n++) अणु
            length_code[length++] = (uch)code;
        पूर्ण
    पूर्ण
    Assert (length == 256, "tr_static_init: length != 256");
    /* Note that the length 255 (match length 258) can be represented
     * in two dअगरferent ways: code 284 + 5 bits or code 285, so we
     * overग_लिखो length_code[255] to use the best encoding:
     */
    length_code[length-1] = (uch)code;

    /* Initialize the mapping dist (0..32K) -> dist code (0..29) */
    dist = 0;
    क्रम (code = 0 ; code < 16; code++) अणु
        base_dist[code] = dist;
        क्रम (n = 0; n < (1<<extra_dbits[code]); n++) अणु
            dist_code[dist++] = (uch)code;
        पूर्ण
    पूर्ण
    Assert (dist == 256, "tr_static_init: dist != 256");
    dist >>= 7; /* from now on, all distances are भागided by 128 */
    क्रम ( ; code < D_CODES; code++) अणु
        base_dist[code] = dist << 7;
        क्रम (n = 0; n < (1<<(extra_dbits[code]-7)); n++) अणु
            dist_code[256 + dist++] = (uch)code;
        पूर्ण
    पूर्ण
    Assert (dist == 256, "tr_static_init: 256+dist != 512");

    /* Conकाष्ठा the codes of the अटल literal tree */
    क्रम (bits = 0; bits <= MAX_BITS; bits++) bl_count[bits] = 0;
    n = 0;
    जबतक (n <= 143) अटल_ltree[n++].Len = 8, bl_count[8]++;
    जबतक (n <= 255) अटल_ltree[n++].Len = 9, bl_count[9]++;
    जबतक (n <= 279) अटल_ltree[n++].Len = 7, bl_count[7]++;
    जबतक (n <= 287) अटल_ltree[n++].Len = 8, bl_count[8]++;
    /* Codes 286 and 287 करो not exist, but we must include them in the
     * tree स्थिरruction to get a canonical Huffman tree (दीर्घest code
     * all ones)
     */
    gen_codes((ct_data *)अटल_ltree, L_CODES+1, bl_count);

    /* The अटल distance tree is trivial: */
    क्रम (n = 0; n < D_CODES; n++) अणु
        अटल_dtree[n].Len = 5;
        अटल_dtree[n].Code = bitrev32((u32)n) >> (32 - 5);
    पूर्ण
    अटल_init_करोne = 1;
पूर्ण

/* ===========================================================================
 * Initialize the tree data काष्ठाures क्रम a new zlib stream.
 */
व्योम zlib_tr_init(
	deflate_state *s
)
अणु
    tr_अटल_init();

    s->compressed_len = 0L;

    s->l_desc.dyn_tree = s->dyn_ltree;
    s->l_desc.stat_desc = &अटल_l_desc;

    s->d_desc.dyn_tree = s->dyn_dtree;
    s->d_desc.stat_desc = &अटल_d_desc;

    s->bl_desc.dyn_tree = s->bl_tree;
    s->bl_desc.stat_desc = &अटल_bl_desc;

    s->bi_buf = 0;
    s->bi_valid = 0;
    s->last_eob_len = 8; /* enough lookahead क्रम inflate */
#अगर_घोषित DEBUG_ZLIB
    s->bits_sent = 0L;
#पूर्ण_अगर

    /* Initialize the first block of the first file: */
    init_block(s);
पूर्ण

/* ===========================================================================
 * Initialize a new block.
 */
अटल व्योम init_block(
	deflate_state *s
)
अणु
    पूर्णांक n; /* iterates over tree elements */

    /* Initialize the trees. */
    क्रम (n = 0; n < L_CODES;  n++) s->dyn_ltree[n].Freq = 0;
    क्रम (n = 0; n < D_CODES;  n++) s->dyn_dtree[n].Freq = 0;
    क्रम (n = 0; n < BL_CODES; n++) s->bl_tree[n].Freq = 0;

    s->dyn_ltree[END_BLOCK].Freq = 1;
    s->opt_len = s->अटल_len = 0L;
    s->last_lit = s->matches = 0;
पूर्ण

#घोषणा SMALLEST 1
/* Index within the heap array of least frequent node in the Huffman tree */


/* ===========================================================================
 * Remove the smallest element from the heap and recreate the heap with
 * one less element. Updates heap and heap_len.
 */
#घोषणा pqहटाओ(s, tree, top) \
अणु\
    top = s->heap[SMALLEST]; \
    s->heap[SMALLEST] = s->heap[s->heap_len--]; \
    pqकरोwnheap(s, tree, SMALLEST); \
पूर्ण

/* ===========================================================================
 * Compares to subtrees, using the tree depth as tie अवरोधer when
 * the subtrees have equal frequency. This minimizes the worst हाल length.
 */
#घोषणा smaller(tree, n, m, depth) \
   (tree[n].Freq < tree[m].Freq || \
   (tree[n].Freq == tree[m].Freq && depth[n] <= depth[m]))

/* ===========================================================================
 * Restore the heap property by moving करोwn the tree starting at node k,
 * exchanging a node with the smallest of its two sons अगर necessary, stopping
 * when the heap property is re-established (each father smaller than its
 * two sons).
 */
अटल व्योम pqकरोwnheap(
	deflate_state *s,
	ct_data *tree,  /* the tree to restore */
	पूर्णांक k		/* node to move करोwn */
)
अणु
    पूर्णांक v = s->heap[k];
    पूर्णांक j = k << 1;  /* left son of k */
    जबतक (j <= s->heap_len) अणु
        /* Set j to the smallest of the two sons: */
        अगर (j < s->heap_len &&
            smaller(tree, s->heap[j+1], s->heap[j], s->depth)) अणु
            j++;
        पूर्ण
        /* Exit अगर v is smaller than both sons */
        अगर (smaller(tree, v, s->heap[j], s->depth)) अवरोध;

        /* Exchange v with the smallest son */
        s->heap[k] = s->heap[j];  k = j;

        /* And जारी करोwn the tree, setting j to the left son of k */
        j <<= 1;
    पूर्ण
    s->heap[k] = v;
पूर्ण

/* ===========================================================================
 * Compute the optimal bit lengths क्रम a tree and update the total bit length
 * क्रम the current block.
 * IN निश्चितion: the fields freq and dad are set, heap[heap_max] and
 *    above are the tree nodes sorted by increasing frequency.
 * OUT निश्चितions: the field len is set to the optimal bit length, the
 *     array bl_count contains the frequencies क्रम each bit length.
 *     The length opt_len is updated; अटल_len is also updated अगर stree is
 *     not null.
 */
अटल व्योम gen_bitlen(
	deflate_state *s,
	tree_desc *desc    /* the tree descriptor */
)
अणु
    ct_data *tree        = desc->dyn_tree;
    पूर्णांक max_code         = desc->max_code;
    स्थिर ct_data *stree = desc->stat_desc->अटल_tree;
    स्थिर पूर्णांक *extra     = desc->stat_desc->extra_bits;
    पूर्णांक base             = desc->stat_desc->extra_base;
    पूर्णांक max_length       = desc->stat_desc->max_length;
    पूर्णांक h;              /* heap index */
    पूर्णांक n, m;           /* iterate over the tree elements */
    पूर्णांक bits;           /* bit length */
    पूर्णांक xbits;          /* extra bits */
    ush f;              /* frequency */
    पूर्णांक overflow = 0;   /* number of elements with bit length too large */

    क्रम (bits = 0; bits <= MAX_BITS; bits++) s->bl_count[bits] = 0;

    /* In a first pass, compute the optimal bit lengths (which may
     * overflow in the हाल of the bit length tree).
     */
    tree[s->heap[s->heap_max]].Len = 0; /* root of the heap */

    क्रम (h = s->heap_max+1; h < HEAP_SIZE; h++) अणु
        n = s->heap[h];
        bits = tree[tree[n].Dad].Len + 1;
        अगर (bits > max_length) bits = max_length, overflow++;
        tree[n].Len = (ush)bits;
        /* We overग_लिखो tree[n].Dad which is no दीर्घer needed */

        अगर (n > max_code) जारी; /* not a leaf node */

        s->bl_count[bits]++;
        xbits = 0;
        अगर (n >= base) xbits = extra[n-base];
        f = tree[n].Freq;
        s->opt_len += (ulg)f * (bits + xbits);
        अगर (stree) s->अटल_len += (ulg)f * (stree[n].Len + xbits);
    पूर्ण
    अगर (overflow == 0) वापस;

    Trace((मानक_त्रुटि,"\nbit length overflow\n"));
    /* This happens क्रम example on obj2 and pic of the Calgary corpus */

    /* Find the first bit length which could increase: */
    करो अणु
        bits = max_length-1;
        जबतक (s->bl_count[bits] == 0) bits--;
        s->bl_count[bits]--;      /* move one leaf करोwn the tree */
        s->bl_count[bits+1] += 2; /* move one overflow item as its brother */
        s->bl_count[max_length]--;
        /* The brother of the overflow item also moves one step up,
         * but this करोes not affect bl_count[max_length]
         */
        overflow -= 2;
    पूर्ण जबतक (overflow > 0);

    /* Now recompute all bit lengths, scanning in increasing frequency.
     * h is still equal to HEAP_SIZE. (It is simpler to reस्थिरruct all
     * lengths instead of fixing only the wrong ones. This idea is taken
     * from 'ar' written by Haruhiko Okumura.)
     */
    क्रम (bits = max_length; bits != 0; bits--) अणु
        n = s->bl_count[bits];
        जबतक (n != 0) अणु
            m = s->heap[--h];
            अगर (m > max_code) जारी;
            अगर (tree[m].Len != (अचिन्हित) bits) अणु
                Trace((मानक_त्रुटि,"code %d bits %d->%d\n", m, tree[m].Len, bits));
                s->opt_len += ((दीर्घ)bits - (दीर्घ)tree[m].Len)
                              *(दीर्घ)tree[m].Freq;
                tree[m].Len = (ush)bits;
            पूर्ण
            n--;
        पूर्ण
    पूर्ण
पूर्ण

/* ===========================================================================
 * Generate the codes क्रम a given tree and bit counts (which need not be
 * optimal).
 * IN निश्चितion: the array bl_count contains the bit length statistics क्रम
 * the given tree and the field len is set क्रम all tree elements.
 * OUT निश्चितion: the field code is set क्रम all tree elements of non
 *     zero code length.
 */
अटल व्योम gen_codes(
	ct_data *tree,             /* the tree to decorate */
	पूर्णांक max_code,              /* largest code with non zero frequency */
	ush *bl_count             /* number of codes at each bit length */
)
अणु
    ush next_code[MAX_BITS+1]; /* next code value क्रम each bit length */
    ush code = 0;              /* running code value */
    पूर्णांक bits;                  /* bit index */
    पूर्णांक n;                     /* code index */

    /* The distribution counts are first used to generate the code values
     * without bit reversal.
     */
    क्रम (bits = 1; bits <= MAX_BITS; bits++) अणु
        next_code[bits] = code = (code + bl_count[bits-1]) << 1;
    पूर्ण
    /* Check that the bit counts in bl_count are consistent. The last code
     * must be all ones.
     */
    Assert (code + bl_count[MAX_BITS]-1 == (1<<MAX_BITS)-1,
            "inconsistent bit counts");
    Tracev((मानक_त्रुटि,"\ngen_codes: max_code %d ", max_code));

    क्रम (n = 0;  n <= max_code; n++) अणु
        पूर्णांक len = tree[n].Len;
        अगर (len == 0) जारी;
        /* Now reverse the bits */
        tree[n].Code = bitrev32((u32)(next_code[len]++)) >> (32 - len);

        Tracecv(tree != अटल_ltree, (मानक_त्रुटि,"\nn %3d %c l %2d c %4x (%x) ",
             n, (है_चित्र(n) ? n : ' '), len, tree[n].Code, next_code[len]-1));
    पूर्ण
पूर्ण

/* ===========================================================================
 * Conकाष्ठा one Huffman tree and assigns the code bit strings and lengths.
 * Update the total bit length क्रम the current block.
 * IN निश्चितion: the field freq is set क्रम all tree elements.
 * OUT निश्चितions: the fields len and code are set to the optimal bit length
 *     and corresponding code. The length opt_len is updated; अटल_len is
 *     also updated अगर stree is not null. The field max_code is set.
 */
अटल व्योम build_tree(
	deflate_state *s,
	tree_desc *desc	 /* the tree descriptor */
)
अणु
    ct_data *tree         = desc->dyn_tree;
    स्थिर ct_data *stree  = desc->stat_desc->अटल_tree;
    पूर्णांक elems             = desc->stat_desc->elems;
    पूर्णांक n, m;          /* iterate over heap elements */
    पूर्णांक max_code = -1; /* largest code with non zero frequency */
    पूर्णांक node;          /* new node being created */

    /* Conकाष्ठा the initial heap, with least frequent element in
     * heap[SMALLEST]. The sons of heap[n] are heap[2*n] and heap[2*n+1].
     * heap[0] is not used.
     */
    s->heap_len = 0, s->heap_max = HEAP_SIZE;

    क्रम (n = 0; n < elems; n++) अणु
        अगर (tree[n].Freq != 0) अणु
            s->heap[++(s->heap_len)] = max_code = n;
            s->depth[n] = 0;
        पूर्ण अन्यथा अणु
            tree[n].Len = 0;
        पूर्ण
    पूर्ण

    /* The pkzip क्रमmat requires that at least one distance code exists,
     * and that at least one bit should be sent even अगर there is only one
     * possible code. So to aव्योम special checks later on we क्रमce at least
     * two codes of non zero frequency.
     */
    जबतक (s->heap_len < 2) अणु
        node = s->heap[++(s->heap_len)] = (max_code < 2 ? ++max_code : 0);
        tree[node].Freq = 1;
        s->depth[node] = 0;
        s->opt_len--; अगर (stree) s->अटल_len -= stree[node].Len;
        /* node is 0 or 1 so it करोes not have extra bits */
    पूर्ण
    desc->max_code = max_code;

    /* The elements heap[heap_len/2+1 .. heap_len] are leaves of the tree,
     * establish sub-heaps of increasing lengths:
     */
    क्रम (n = s->heap_len/2; n >= 1; n--) pqकरोwnheap(s, tree, n);

    /* Conकाष्ठा the Huffman tree by repeatedly combining the least two
     * frequent nodes.
     */
    node = elems;              /* next पूर्णांकernal node of the tree */
    करो अणु
        pqहटाओ(s, tree, n);  /* n = node of least frequency */
        m = s->heap[SMALLEST]; /* m = node of next least frequency */

        s->heap[--(s->heap_max)] = n; /* keep the nodes sorted by frequency */
        s->heap[--(s->heap_max)] = m;

        /* Create a new node father of n and m */
        tree[node].Freq = tree[n].Freq + tree[m].Freq;
        s->depth[node] = (uch) (max(s->depth[n], s->depth[m]) + 1);
        tree[n].Dad = tree[m].Dad = (ush)node;
#अगर_घोषित DUMP_BL_TREE
        अगर (tree == s->bl_tree) अणु
            ख_लिखो(मानक_त्रुटि,"\nnode %d(%d), sons %d(%d) %d(%d)",
                    node, tree[node].Freq, n, tree[n].Freq, m, tree[m].Freq);
        पूर्ण
#पूर्ण_अगर
        /* and insert the new node in the heap */
        s->heap[SMALLEST] = node++;
        pqकरोwnheap(s, tree, SMALLEST);

    पूर्ण जबतक (s->heap_len >= 2);

    s->heap[--(s->heap_max)] = s->heap[SMALLEST];

    /* At this poपूर्णांक, the fields freq and dad are set. We can now
     * generate the bit lengths.
     */
    gen_bitlen(s, (tree_desc *)desc);

    /* The field len is now set, we can generate the bit codes */
    gen_codes ((ct_data *)tree, max_code, s->bl_count);
पूर्ण

/* ===========================================================================
 * Scan a literal or distance tree to determine the frequencies of the codes
 * in the bit length tree.
 */
अटल व्योम scan_tree(
	deflate_state *s,
	ct_data *tree,   /* the tree to be scanned */
	पूर्णांक max_code     /* and its largest code of non zero frequency */
)
अणु
    पूर्णांक n;                     /* iterates over all tree elements */
    पूर्णांक prevlen = -1;          /* last emitted length */
    पूर्णांक curlen;                /* length of current code */
    पूर्णांक nextlen = tree[0].Len; /* length of next code */
    पूर्णांक count = 0;             /* repeat count of the current code */
    पूर्णांक max_count = 7;         /* max repeat count */
    पूर्णांक min_count = 4;         /* min repeat count */

    अगर (nextlen == 0) max_count = 138, min_count = 3;
    tree[max_code+1].Len = (ush)0xffff; /* guard */

    क्रम (n = 0; n <= max_code; n++) अणु
        curlen = nextlen; nextlen = tree[n+1].Len;
        अगर (++count < max_count && curlen == nextlen) अणु
            जारी;
        पूर्ण अन्यथा अगर (count < min_count) अणु
            s->bl_tree[curlen].Freq += count;
        पूर्ण अन्यथा अगर (curlen != 0) अणु
            अगर (curlen != prevlen) s->bl_tree[curlen].Freq++;
            s->bl_tree[REP_3_6].Freq++;
        पूर्ण अन्यथा अगर (count <= 10) अणु
            s->bl_tree[REPZ_3_10].Freq++;
        पूर्ण अन्यथा अणु
            s->bl_tree[REPZ_11_138].Freq++;
        पूर्ण
        count = 0; prevlen = curlen;
        अगर (nextlen == 0) अणु
            max_count = 138, min_count = 3;
        पूर्ण अन्यथा अगर (curlen == nextlen) अणु
            max_count = 6, min_count = 3;
        पूर्ण अन्यथा अणु
            max_count = 7, min_count = 4;
        पूर्ण
    पूर्ण
पूर्ण

/* ===========================================================================
 * Send a literal or distance tree in compressed क्रमm, using the codes in
 * bl_tree.
 */
अटल व्योम send_tree(
	deflate_state *s,
	ct_data *tree, /* the tree to be scanned */
	पूर्णांक max_code   /* and its largest code of non zero frequency */
)
अणु
    पूर्णांक n;                     /* iterates over all tree elements */
    पूर्णांक prevlen = -1;          /* last emitted length */
    पूर्णांक curlen;                /* length of current code */
    पूर्णांक nextlen = tree[0].Len; /* length of next code */
    पूर्णांक count = 0;             /* repeat count of the current code */
    पूर्णांक max_count = 7;         /* max repeat count */
    पूर्णांक min_count = 4;         /* min repeat count */

    /* tree[max_code+1].Len = -1; */  /* guard alपढ़ोy set */
    अगर (nextlen == 0) max_count = 138, min_count = 3;

    क्रम (n = 0; n <= max_code; n++) अणु
        curlen = nextlen; nextlen = tree[n+1].Len;
        अगर (++count < max_count && curlen == nextlen) अणु
            जारी;
        पूर्ण अन्यथा अगर (count < min_count) अणु
            करो अणु send_code(s, curlen, s->bl_tree); पूर्ण जबतक (--count != 0);

        पूर्ण अन्यथा अगर (curlen != 0) अणु
            अगर (curlen != prevlen) अणु
                send_code(s, curlen, s->bl_tree); count--;
            पूर्ण
            Assert(count >= 3 && count <= 6, " 3_6?");
            send_code(s, REP_3_6, s->bl_tree); send_bits(s, count-3, 2);

        पूर्ण अन्यथा अगर (count <= 10) अणु
            send_code(s, REPZ_3_10, s->bl_tree); send_bits(s, count-3, 3);

        पूर्ण अन्यथा अणु
            send_code(s, REPZ_11_138, s->bl_tree); send_bits(s, count-11, 7);
        पूर्ण
        count = 0; prevlen = curlen;
        अगर (nextlen == 0) अणु
            max_count = 138, min_count = 3;
        पूर्ण अन्यथा अगर (curlen == nextlen) अणु
            max_count = 6, min_count = 3;
        पूर्ण अन्यथा अणु
            max_count = 7, min_count = 4;
        पूर्ण
    पूर्ण
पूर्ण

/* ===========================================================================
 * Conकाष्ठा the Huffman tree क्रम the bit lengths and वापस the index in
 * bl_order of the last bit length code to send.
 */
अटल पूर्णांक build_bl_tree(
	deflate_state *s
)
अणु
    पूर्णांक max_blindex;  /* index of last bit length code of non zero freq */

    /* Determine the bit length frequencies क्रम literal and distance trees */
    scan_tree(s, (ct_data *)s->dyn_ltree, s->l_desc.max_code);
    scan_tree(s, (ct_data *)s->dyn_dtree, s->d_desc.max_code);

    /* Build the bit length tree: */
    build_tree(s, (tree_desc *)(&(s->bl_desc)));
    /* opt_len now includes the length of the tree representations, except
     * the lengths of the bit lengths codes and the 5+5+4 bits क्रम the counts.
     */

    /* Determine the number of bit length codes to send. The pkzip क्रमmat
     * requires that at least 4 bit length codes be sent. (appnote.txt says
     * 3 but the actual value used is 4.)
     */
    क्रम (max_blindex = BL_CODES-1; max_blindex >= 3; max_blindex--) अणु
        अगर (s->bl_tree[bl_order[max_blindex]].Len != 0) अवरोध;
    पूर्ण
    /* Update opt_len to include the bit length tree and counts */
    s->opt_len += 3*(max_blindex+1) + 5+5+4;
    Tracev((मानक_त्रुटि, "\ndyn trees: dyn %ld, stat %ld",
            s->opt_len, s->अटल_len));

    वापस max_blindex;
पूर्ण

/* ===========================================================================
 * Send the header क्रम a block using dynamic Huffman trees: the counts, the
 * lengths of the bit length codes, the literal tree and the distance tree.
 * IN निश्चितion: lcodes >= 257, dcodes >= 1, blcodes >= 4.
 */
अटल व्योम send_all_trees(
	deflate_state *s,
	पूर्णांक lcodes,  /* number of codes क्रम each tree */
	पूर्णांक dcodes,  /* number of codes क्रम each tree */
	पूर्णांक blcodes  /* number of codes क्रम each tree */
)
अणु
    पूर्णांक rank;                    /* index in bl_order */

    Assert (lcodes >= 257 && dcodes >= 1 && blcodes >= 4, "not enough codes");
    Assert (lcodes <= L_CODES && dcodes <= D_CODES && blcodes <= BL_CODES,
            "too many codes");
    Tracev((मानक_त्रुटि, "\nbl counts: "));
    send_bits(s, lcodes-257, 5); /* not +255 as stated in appnote.txt */
    send_bits(s, dcodes-1,   5);
    send_bits(s, blcodes-4,  4); /* not -3 as stated in appnote.txt */
    क्रम (rank = 0; rank < blcodes; rank++) अणु
        Tracev((मानक_त्रुटि, "\nbl code %2d ", bl_order[rank]));
        send_bits(s, s->bl_tree[bl_order[rank]].Len, 3);
    पूर्ण
    Tracev((मानक_त्रुटि, "\nbl tree: sent %ld", s->bits_sent));

    send_tree(s, (ct_data *)s->dyn_ltree, lcodes-1); /* literal tree */
    Tracev((मानक_त्रुटि, "\nlit tree: sent %ld", s->bits_sent));

    send_tree(s, (ct_data *)s->dyn_dtree, dcodes-1); /* distance tree */
    Tracev((मानक_त्रुटि, "\ndist tree: sent %ld", s->bits_sent));
पूर्ण

/* ===========================================================================
 * Send a stored block
 */
व्योम zlib_tr_stored_block(
	deflate_state *s,
	अक्षर *buf,        /* input block */
	ulg stored_len,   /* length of input block */
	पूर्णांक eof           /* true अगर this is the last block क्रम a file */
)
अणु
    send_bits(s, (STORED_BLOCK<<1)+eof, 3);  /* send block type */
    s->compressed_len = (s->compressed_len + 3 + 7) & (ulg)~7L;
    s->compressed_len += (stored_len + 4) << 3;

    copy_block(s, buf, (अचिन्हित)stored_len, 1); /* with header */
पूर्ण

/* Send just the `stored block' type code without any length bytes or data.
 */
व्योम zlib_tr_stored_type_only(
	deflate_state *s
)
अणु
    send_bits(s, (STORED_BLOCK << 1), 3);
    bi_windup(s);
    s->compressed_len = (s->compressed_len + 3) & ~7L;
पूर्ण


/* ===========================================================================
 * Send one empty अटल block to give enough lookahead क्रम inflate.
 * This takes 10 bits, of which 7 may reमुख्य in the bit buffer.
 * The current inflate code requires 9 bits of lookahead. If the
 * last two codes क्रम the previous block (real code plus EOB) were coded
 * on 5 bits or less, inflate may have only 5+3 bits of lookahead to decode
 * the last real code. In this हाल we send two empty अटल blocks instead
 * of one. (There are no problems अगर the previous block is stored or fixed.)
 * To simplअगरy the code, we assume the worst हाल of last real code encoded
 * on one bit only.
 */
व्योम zlib_tr_align(
	deflate_state *s
)
अणु
    send_bits(s, STATIC_TREES<<1, 3);
    send_code(s, END_BLOCK, अटल_ltree);
    s->compressed_len += 10L; /* 3 क्रम block type, 7 क्रम EOB */
    bi_flush(s);
    /* Of the 10 bits क्रम the empty block, we have alपढ़ोy sent
     * (10 - bi_valid) bits. The lookahead क्रम the last real code (beक्रमe
     * the EOB of the previous block) was thus at least one plus the length
     * of the EOB plus what we have just sent of the empty अटल block.
     */
    अगर (1 + s->last_eob_len + 10 - s->bi_valid < 9) अणु
        send_bits(s, STATIC_TREES<<1, 3);
        send_code(s, END_BLOCK, अटल_ltree);
        s->compressed_len += 10L;
        bi_flush(s);
    पूर्ण
    s->last_eob_len = 7;
पूर्ण

/* ===========================================================================
 * Determine the best encoding क्रम the current block: dynamic trees, अटल
 * trees or store, and output the encoded block to the zip file. This function
 * वापसs the total compressed length क्रम the file so far.
 */
ulg zlib_tr_flush_block(
	deflate_state *s,
	अक्षर *buf,        /* input block, or शून्य अगर too old */
	ulg stored_len,   /* length of input block */
	पूर्णांक eof           /* true अगर this is the last block क्रम a file */
)
अणु
    ulg opt_lenb, अटल_lenb; /* opt_len and अटल_len in bytes */
    पूर्णांक max_blindex = 0;  /* index of last bit length code of non zero freq */

    /* Build the Huffman trees unless a stored block is क्रमced */
    अगर (s->level > 0) अणु

	 /* Check अगर the file is ascii or binary */
	अगर (s->data_type == Z_UNKNOWN) set_data_type(s);

	/* Conकाष्ठा the literal and distance trees */
	build_tree(s, (tree_desc *)(&(s->l_desc)));
	Tracev((मानक_त्रुटि, "\nlit data: dyn %ld, stat %ld", s->opt_len,
		s->अटल_len));

	build_tree(s, (tree_desc *)(&(s->d_desc)));
	Tracev((मानक_त्रुटि, "\ndist data: dyn %ld, stat %ld", s->opt_len,
		s->अटल_len));
	/* At this poपूर्णांक, opt_len and अटल_len are the total bit lengths of
	 * the compressed block data, excluding the tree representations.
	 */

	/* Build the bit length tree क्रम the above two trees, and get the index
	 * in bl_order of the last bit length code to send.
	 */
	max_blindex = build_bl_tree(s);

	/* Determine the best encoding. Compute first the block length in bytes*/
	opt_lenb = (s->opt_len+3+7)>>3;
	अटल_lenb = (s->अटल_len+3+7)>>3;

	Tracev((मानक_त्रुटि, "\nopt %lu(%lu) stat %lu(%lu) stored %lu lit %u ",
		opt_lenb, s->opt_len, अटल_lenb, s->अटल_len, stored_len,
		s->last_lit));

	अगर (अटल_lenb <= opt_lenb) opt_lenb = अटल_lenb;

    पूर्ण अन्यथा अणु
        Assert(buf != (अक्षर*)0, "lost buf");
	opt_lenb = अटल_lenb = stored_len + 5; /* क्रमce a stored block */
    पूर्ण

    /* If compression failed and this is the first and last block,
     * and अगर the .zip file can be seeked (to reग_लिखो the local header),
     * the whole file is transक्रमmed पूर्णांकo a stored file:
     */
#अगर_घोषित STORED_खाता_OK
#  अगरdef FORCE_STORED_खाता
    अगर (eof && s->compressed_len == 0L) अणु /* क्रमce stored file */
#  अन्यथा
    अगर (stored_len <= opt_lenb && eof && s->compressed_len==0L && seekable()) अणु
#  endअगर
        /* Since LIT_बफ_मानE <= 2*WSIZE, the input data must be there: */
        अगर (buf == (अक्षर*)0) error ("block vanished");

        copy_block(s, buf, (अचिन्हित)stored_len, 0); /* without header */
        s->compressed_len = stored_len << 3;
        s->method = STORED;
    पूर्ण अन्यथा
#पूर्ण_अगर /* STORED_खाता_OK */

#अगर_घोषित FORCE_STORED
    अगर (buf != (अक्षर*)0) अणु /* क्रमce stored block */
#अन्यथा
    अगर (stored_len+4 <= opt_lenb && buf != (अक्षर*)0) अणु
                       /* 4: two words क्रम the lengths */
#पूर्ण_अगर
        /* The test buf != शून्य is only necessary अगर LIT_बफ_मानE > WSIZE.
         * Otherwise we can't have processed more than WSIZE input bytes since
         * the last block flush, because compression would have been
         * successful. If LIT_बफ_मानE <= WSIZE, it is never too late to
         * transक्रमm a block पूर्णांकo a stored block.
         */
        zlib_tr_stored_block(s, buf, stored_len, eof);

#अगर_घोषित FORCE_STATIC
    पूर्ण अन्यथा अगर (अटल_lenb >= 0) अणु /* क्रमce अटल trees */
#अन्यथा
    पूर्ण अन्यथा अगर (अटल_lenb == opt_lenb) अणु
#पूर्ण_अगर
        send_bits(s, (STATIC_TREES<<1)+eof, 3);
        compress_block(s, (ct_data *)अटल_ltree, (ct_data *)अटल_dtree);
        s->compressed_len += 3 + s->अटल_len;
    पूर्ण अन्यथा अणु
        send_bits(s, (DYN_TREES<<1)+eof, 3);
        send_all_trees(s, s->l_desc.max_code+1, s->d_desc.max_code+1,
                       max_blindex+1);
        compress_block(s, (ct_data *)s->dyn_ltree, (ct_data *)s->dyn_dtree);
        s->compressed_len += 3 + s->opt_len;
    पूर्ण
    Assert (s->compressed_len == s->bits_sent, "bad compressed size");
    init_block(s);

    अगर (eof) अणु
        bi_windup(s);
        s->compressed_len += 7;  /* align on byte boundary */
    पूर्ण
    Tracev((मानक_त्रुटि,"\ncomprlen %lu(%lu) ", s->compressed_len>>3,
           s->compressed_len-7*eof));

    वापस s->compressed_len >> 3;
पूर्ण

/* ===========================================================================
 * Save the match info and tally the frequency counts. Return true अगर
 * the current block must be flushed.
 */
पूर्णांक zlib_tr_tally(
	deflate_state *s,
	अचिन्हित dist,  /* distance of matched string */
	अचिन्हित lc     /* match length-MIN_MATCH or unmatched अक्षर (अगर dist==0) */
)
अणु
    s->d_buf[s->last_lit] = (ush)dist;
    s->l_buf[s->last_lit++] = (uch)lc;
    अगर (dist == 0) अणु
        /* lc is the unmatched अक्षर */
        s->dyn_ltree[lc].Freq++;
    पूर्ण अन्यथा अणु
        s->matches++;
        /* Here, lc is the match length - MIN_MATCH */
        dist--;             /* dist = match distance - 1 */
        Assert((ush)dist < (ush)MAX_DIST(s) &&
               (ush)lc <= (ush)(MAX_MATCH-MIN_MATCH) &&
               (ush)d_code(dist) < (ush)D_CODES,  "zlib_tr_tally: bad match");

        s->dyn_ltree[length_code[lc]+LITERALS+1].Freq++;
        s->dyn_dtree[d_code(dist)].Freq++;
    पूर्ण

    /* Try to guess अगर it is profitable to stop the current block here */
    अगर ((s->last_lit & 0xfff) == 0 && s->level > 2) अणु
        /* Compute an upper bound क्रम the compressed length */
        ulg out_length = (ulg)s->last_lit*8L;
        ulg in_length = (ulg)((दीर्घ)s->strstart - s->block_start);
        पूर्णांक dcode;
        क्रम (dcode = 0; dcode < D_CODES; dcode++) अणु
            out_length += (ulg)s->dyn_dtree[dcode].Freq *
                (5L+extra_dbits[dcode]);
        पूर्ण
        out_length >>= 3;
        Tracev((मानक_त्रुटि,"\nlast_lit %u, in %ld, out ~%ld(%ld%%) ",
               s->last_lit, in_length, out_length,
               100L - out_length*100L/in_length));
        अगर (s->matches < s->last_lit/2 && out_length < in_length/2) वापस 1;
    पूर्ण
    वापस (s->last_lit == s->lit_bufsize-1);
    /* We aव्योम equality with lit_bufsize because of wraparound at 64K
     * on 16 bit machines and because stored blocks are restricted to
     * 64K-1 bytes.
     */
पूर्ण

/* ===========================================================================
 * Send the block data compressed using the given Huffman trees
 */
अटल व्योम compress_block(
	deflate_state *s,
	ct_data *ltree, /* literal tree */
	ct_data *dtree  /* distance tree */
)
अणु
    अचिन्हित dist;      /* distance of matched string */
    पूर्णांक lc;             /* match length or unmatched अक्षर (अगर dist == 0) */
    अचिन्हित lx = 0;    /* running index in l_buf */
    अचिन्हित code;      /* the code to send */
    पूर्णांक extra;          /* number of extra bits to send */

    अगर (s->last_lit != 0) करो अणु
        dist = s->d_buf[lx];
        lc = s->l_buf[lx++];
        अगर (dist == 0) अणु
            send_code(s, lc, ltree); /* send a literal byte */
            Tracecv(है_चित्र(lc), (मानक_त्रुटि," '%c' ", lc));
        पूर्ण अन्यथा अणु
            /* Here, lc is the match length - MIN_MATCH */
            code = length_code[lc];
            send_code(s, code+LITERALS+1, ltree); /* send the length code */
            extra = extra_lbits[code];
            अगर (extra != 0) अणु
                lc -= base_length[code];
                send_bits(s, lc, extra);       /* send the extra length bits */
            पूर्ण
            dist--; /* dist is now the match distance - 1 */
            code = d_code(dist);
            Assert (code < D_CODES, "bad d_code");

            send_code(s, code, dtree);       /* send the distance code */
            extra = extra_dbits[code];
            अगर (extra != 0) अणु
                dist -= base_dist[code];
                send_bits(s, dist, extra);   /* send the extra distance bits */
            पूर्ण
        पूर्ण /* literal or match pair ? */

        /* Check that the overlay between pending_buf and d_buf+l_buf is ok: */
        Assert(s->pending < s->lit_bufsize + 2*lx, "pendingBuf overflow");

    पूर्ण जबतक (lx < s->last_lit);

    send_code(s, END_BLOCK, ltree);
    s->last_eob_len = ltree[END_BLOCK].Len;
पूर्ण

/* ===========================================================================
 * Set the data type to ASCII or BINARY, using a crude approximation:
 * binary अगर more than 20% of the bytes are <= 6 or >= 128, ascii otherwise.
 * IN निश्चितion: the fields freq of dyn_ltree are set and the total of all
 * frequencies करोes not exceed 64K (to fit in an पूर्णांक on 16 bit machines).
 */
अटल व्योम set_data_type(
	deflate_state *s
)
अणु
    पूर्णांक n = 0;
    अचिन्हित ascii_freq = 0;
    अचिन्हित bin_freq = 0;
    जबतक (n < 7)        bin_freq += s->dyn_ltree[n++].Freq;
    जबतक (n < 128)    ascii_freq += s->dyn_ltree[n++].Freq;
    जबतक (n < LITERALS) bin_freq += s->dyn_ltree[n++].Freq;
    s->data_type = (Byte)(bin_freq > (ascii_freq >> 2) ? Z_BINARY : Z_ASCII);
पूर्ण

/* ===========================================================================
 * Copy a stored block, storing first the length and its
 * one's complement अगर requested.
 */
अटल व्योम copy_block(
	deflate_state *s,
	अक्षर    *buf,     /* the input data */
	अचिन्हित len,     /* its length */
	पूर्णांक      header   /* true अगर block header must be written */
)
अणु
    bi_windup(s);        /* align on byte boundary */
    s->last_eob_len = 8; /* enough lookahead क्रम inflate */

    अगर (header) अणु
        put_लघु(s, (ush)len);   
        put_लघु(s, (ush)~len);
#अगर_घोषित DEBUG_ZLIB
        s->bits_sent += 2*16;
#पूर्ण_अगर
    पूर्ण
#अगर_घोषित DEBUG_ZLIB
    s->bits_sent += (ulg)len<<3;
#पूर्ण_अगर
    /* bundle up the put_byte(s, *buf++) calls */
    स_नकल(&s->pending_buf[s->pending], buf, len);
    s->pending += len;
पूर्ण

