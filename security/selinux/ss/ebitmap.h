<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * An extensible biपंचांगap is a biपंचांगap that supports an
 * arbitrary number of bits.  Extensible biपंचांगaps are
 * used to represent sets of values, such as types,
 * roles, categories, and classes.
 *
 * Each extensible biपंचांगap is implemented as a linked
 * list of biपंचांगap nodes, where each biपंचांगap node has
 * an explicitly specअगरied starting bit position within
 * the total biपंचांगap.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#अगर_अघोषित _SS_EBITMAP_H_
#घोषणा _SS_EBITMAP_H_

#समावेश <net/netlabel.h>

#अगर_घोषित CONFIG_64BIT
#घोषणा	EBITMAP_NODE_SIZE	64
#अन्यथा
#घोषणा	EBITMAP_NODE_SIZE	32
#पूर्ण_अगर

#घोषणा EBITMAP_UNIT_NUMS	((EBITMAP_NODE_SIZE-माप(व्योम *)-माप(u32))\
					/ माप(अचिन्हित दीर्घ))
#घोषणा EBITMAP_UNIT_SIZE	BITS_PER_LONG
#घोषणा EBITMAP_SIZE		(EBITMAP_UNIT_NUMS * EBITMAP_UNIT_SIZE)
#घोषणा EBITMAP_BIT		1ULL
#घोषणा EBITMAP_SHIFT_UNIT_SIZE(x)					\
	(((x) >> EBITMAP_UNIT_SIZE / 2) >> EBITMAP_UNIT_SIZE / 2)

काष्ठा ebiपंचांगap_node अणु
	काष्ठा ebiपंचांगap_node *next;
	अचिन्हित दीर्घ maps[EBITMAP_UNIT_NUMS];
	u32 startbit;
पूर्ण;

काष्ठा ebiपंचांगap अणु
	काष्ठा ebiपंचांगap_node *node;	/* first node in the biपंचांगap */
	u32 highbit;	/* highest position in the total biपंचांगap */
पूर्ण;

#घोषणा ebiपंचांगap_length(e) ((e)->highbit)

अटल अंतरभूत अचिन्हित पूर्णांक ebiपंचांगap_start_positive(काष्ठा ebiपंचांगap *e,
						  काष्ठा ebiपंचांगap_node **n)
अणु
	अचिन्हित पूर्णांक ofs;

	क्रम (*n = e->node; *n; *n = (*n)->next) अणु
		ofs = find_first_bit((*n)->maps, EBITMAP_SIZE);
		अगर (ofs < EBITMAP_SIZE)
			वापस (*n)->startbit + ofs;
	पूर्ण
	वापस ebiपंचांगap_length(e);
पूर्ण

अटल अंतरभूत व्योम ebiपंचांगap_init(काष्ठा ebiपंचांगap *e)
अणु
	स_रखो(e, 0, माप(*e));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ebiपंचांगap_next_positive(काष्ठा ebiपंचांगap *e,
						 काष्ठा ebiपंचांगap_node **n,
						 अचिन्हित पूर्णांक bit)
अणु
	अचिन्हित पूर्णांक ofs;

	ofs = find_next_bit((*n)->maps, EBITMAP_SIZE, bit - (*n)->startbit + 1);
	अगर (ofs < EBITMAP_SIZE)
		वापस ofs + (*n)->startbit;

	क्रम (*n = (*n)->next; *n; *n = (*n)->next) अणु
		ofs = find_first_bit((*n)->maps, EBITMAP_SIZE);
		अगर (ofs < EBITMAP_SIZE)
			वापस ofs + (*n)->startbit;
	पूर्ण
	वापस ebiपंचांगap_length(e);
पूर्ण

#घोषणा EBITMAP_NODE_INDEX(node, bit)	\
	(((bit) - (node)->startbit) / EBITMAP_UNIT_SIZE)
#घोषणा EBITMAP_NODE_OFFSET(node, bit)	\
	(((bit) - (node)->startbit) % EBITMAP_UNIT_SIZE)

अटल अंतरभूत पूर्णांक ebiपंचांगap_node_get_bit(काष्ठा ebiपंचांगap_node *n,
				       अचिन्हित पूर्णांक bit)
अणु
	अचिन्हित पूर्णांक index = EBITMAP_NODE_INDEX(n, bit);
	अचिन्हित पूर्णांक ofs = EBITMAP_NODE_OFFSET(n, bit);

	BUG_ON(index >= EBITMAP_UNIT_NUMS);
	अगर ((n->maps[index] & (EBITMAP_BIT << ofs)))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ebiपंचांगap_node_set_bit(काष्ठा ebiपंचांगap_node *n,
					अचिन्हित पूर्णांक bit)
अणु
	अचिन्हित पूर्णांक index = EBITMAP_NODE_INDEX(n, bit);
	अचिन्हित पूर्णांक ofs = EBITMAP_NODE_OFFSET(n, bit);

	BUG_ON(index >= EBITMAP_UNIT_NUMS);
	n->maps[index] |= (EBITMAP_BIT << ofs);
पूर्ण

अटल अंतरभूत व्योम ebiपंचांगap_node_clr_bit(काष्ठा ebiपंचांगap_node *n,
					अचिन्हित पूर्णांक bit)
अणु
	अचिन्हित पूर्णांक index = EBITMAP_NODE_INDEX(n, bit);
	अचिन्हित पूर्णांक ofs = EBITMAP_NODE_OFFSET(n, bit);

	BUG_ON(index >= EBITMAP_UNIT_NUMS);
	n->maps[index] &= ~(EBITMAP_BIT << ofs);
पूर्ण

#घोषणा ebiपंचांगap_क्रम_each_positive_bit(e, n, bit)	\
	क्रम (bit = ebiपंचांगap_start_positive(e, &n);	\
	     bit < ebiपंचांगap_length(e);			\
	     bit = ebiपंचांगap_next_positive(e, &n, bit))	\

पूर्णांक ebiपंचांगap_cmp(काष्ठा ebiपंचांगap *e1, काष्ठा ebiपंचांगap *e2);
पूर्णांक ebiपंचांगap_cpy(काष्ठा ebiपंचांगap *dst, काष्ठा ebiपंचांगap *src);
पूर्णांक ebiपंचांगap_and(काष्ठा ebiपंचांगap *dst, काष्ठा ebiपंचांगap *e1, काष्ठा ebiपंचांगap *e2);
पूर्णांक ebiपंचांगap_contains(काष्ठा ebiपंचांगap *e1, काष्ठा ebiपंचांगap *e2, u32 last_e2bit);
पूर्णांक ebiपंचांगap_get_bit(काष्ठा ebiपंचांगap *e, अचिन्हित दीर्घ bit);
पूर्णांक ebiपंचांगap_set_bit(काष्ठा ebiपंचांगap *e, अचिन्हित दीर्घ bit, पूर्णांक value);
व्योम ebiपंचांगap_destroy(काष्ठा ebiपंचांगap *e);
पूर्णांक ebiपंचांगap_पढ़ो(काष्ठा ebiपंचांगap *e, व्योम *fp);
पूर्णांक ebiपंचांगap_ग_लिखो(काष्ठा ebiपंचांगap *e, व्योम *fp);
u32 ebiपंचांगap_hash(स्थिर काष्ठा ebiपंचांगap *e, u32 hash);

#अगर_घोषित CONFIG_NETLABEL
पूर्णांक ebiपंचांगap_netlbl_export(काष्ठा ebiपंचांगap *ebmap,
			  काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap);
पूर्णांक ebiपंचांगap_netlbl_import(काष्ठा ebiपंचांगap *ebmap,
			  काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap);
#अन्यथा
अटल अंतरभूत पूर्णांक ebiपंचांगap_netlbl_export(काष्ठा ebiपंचांगap *ebmap,
					काष्ठा netlbl_lsm_caपंचांगap **caपंचांगap)
अणु
	वापस -ENOMEM;
पूर्ण
अटल अंतरभूत पूर्णांक ebiपंचांगap_netlbl_import(काष्ठा ebiपंचांगap *ebmap,
					काष्ठा netlbl_lsm_caपंचांगap *caपंचांगap)
अणु
	वापस -ENOMEM;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* _SS_EBITMAP_H_ */
