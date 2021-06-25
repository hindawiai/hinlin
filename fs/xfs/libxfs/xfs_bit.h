<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000,2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_BIT_H__
#घोषणा	__XFS_BIT_H__

/*
 * XFS bit manipulation routines.
 */

/*
 * masks with n high/low bits set, 64-bit values
 */
अटल अंतरभूत uपूर्णांक64_t xfs_mask64hi(पूर्णांक n)
अणु
	वापस (uपूर्णांक64_t)-1 << (64 - (n));
पूर्ण
अटल अंतरभूत uपूर्णांक32_t xfs_mask32lo(पूर्णांक n)
अणु
	वापस ((uपूर्णांक32_t)1 << (n)) - 1;
पूर्ण
अटल अंतरभूत uपूर्णांक64_t xfs_mask64lo(पूर्णांक n)
अणु
	वापस ((uपूर्णांक64_t)1 << (n)) - 1;
पूर्ण

/* Get high bit set out of 32-bit argument, -1 अगर none set */
अटल अंतरभूत पूर्णांक xfs_highbit32(uपूर्णांक32_t v)
अणु
	वापस fls(v) - 1;
पूर्ण

/* Get high bit set out of 64-bit argument, -1 अगर none set */
अटल अंतरभूत पूर्णांक xfs_highbit64(uपूर्णांक64_t v)
अणु
	वापस fls64(v) - 1;
पूर्ण

/* Get low bit set out of 32-bit argument, -1 अगर none set */
अटल अंतरभूत पूर्णांक xfs_lowbit32(uपूर्णांक32_t v)
अणु
	वापस ffs(v) - 1;
पूर्ण

/* Get low bit set out of 64-bit argument, -1 अगर none set */
अटल अंतरभूत पूर्णांक xfs_lowbit64(uपूर्णांक64_t v)
अणु
	uपूर्णांक32_t	w = (uपूर्णांक32_t)v;
	पूर्णांक		n = 0;

	अगर (w) अणु	/* lower bits */
		n = ffs(w);
	पूर्ण अन्यथा अणु	/* upper bits */
		w = (uपूर्णांक32_t)(v >> 32);
		अगर (w) अणु
			n = ffs(w);
			अगर (n)
				n += 32;
		पूर्ण
	पूर्ण
	वापस n - 1;
पूर्ण

/* Return whether biपंचांगap is empty (1 == empty) */
बाह्य पूर्णांक xfs_biपंचांगap_empty(uपूर्णांक *map, uपूर्णांक size);

/* Count continuous one bits in map starting with start_bit */
बाह्य पूर्णांक xfs_contig_bits(uपूर्णांक *map, uपूर्णांक size, uपूर्णांक start_bit);

/* Find next set bit in map */
बाह्य पूर्णांक xfs_next_bit(uपूर्णांक *map, uपूर्णांक size, uपूर्णांक start_bit);

#पूर्ण_अगर	/* __XFS_BIT_H__ */
