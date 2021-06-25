<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2019 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_SCRUB_ATTR_H__
#घोषणा __XFS_SCRUB_ATTR_H__

/*
 * Temporary storage क्रम online scrub and repair of extended attributes.
 */
काष्ठा xchk_xattr_buf अणु
	/* Size of @buf, in bytes. */
	माप_प्रकार			sz;

	/*
	 * Memory buffer -- either used क्रम extracting attr values जबतक
	 * walking the attributes; or क्रम computing attr block biपंचांगaps when
	 * checking the attribute tree.
	 *
	 * Each biपंचांगap contains enough bits to track every byte in an attr
	 * block (rounded up to the size of an अचिन्हित दीर्घ).  The attr block
	 * used space biपंचांगap starts at the beginning of the buffer; the मुक्त
	 * space biपंचांगap follows immediately after; and we have a third buffer
	 * क्रम storing पूर्णांकermediate biपंचांगap results.
	 */
	uपूर्णांक8_t			buf[0];
पूर्ण;

/* A place to store attribute values. */
अटल अंतरभूत uपूर्णांक8_t *
xchk_xattr_valuebuf(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xchk_xattr_buf	*ab = sc->buf;

	वापस ab->buf;
पूर्ण

/* A biपंचांगap of space usage computed by walking an attr leaf block. */
अटल अंतरभूत अचिन्हित दीर्घ *
xchk_xattr_usedmap(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xchk_xattr_buf	*ab = sc->buf;

	वापस (अचिन्हित दीर्घ *)ab->buf;
पूर्ण

/* A biपंचांगap of मुक्त space computed by walking attr leaf block मुक्त info. */
अटल अंतरभूत अचिन्हित दीर्घ *
xchk_xattr_मुक्तmap(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_xattr_usedmap(sc) +
			BITS_TO_LONGS(sc->mp->m_attr_geo->blksize);
पूर्ण

/* A biपंचांगap used to hold temporary results. */
अटल अंतरभूत अचिन्हित दीर्घ *
xchk_xattr_dsपंचांगap(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_xattr_मुक्तmap(sc) +
			BITS_TO_LONGS(sc->mp->m_attr_geo->blksize);
पूर्ण

पूर्णांक xchk_setup_xattr_buf(काष्ठा xfs_scrub *sc, माप_प्रकार value_size,
		xfs_km_flags_t flags);

#पूर्ण_अगर	/* __XFS_SCRUB_ATTR_H__ */
