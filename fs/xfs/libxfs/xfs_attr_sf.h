<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000,2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_ATTR_SF_H__
#घोषणा	__XFS_ATTR_SF_H__

/*
 * Attribute storage when stored inside the inode.
 *
 * Small attribute lists are packed as tightly as possible so as
 * to fit पूर्णांकo the literal area of the inode.
 */
प्रकार काष्ठा xfs_attr_sf_hdr xfs_attr_sf_hdr_t;

/*
 * We generate this then sort it, attr_list() must वापस things in hash-order.
 */
प्रकार काष्ठा xfs_attr_sf_sort अणु
	uपूर्णांक8_t		entno;		/* entry number in original list */
	uपूर्णांक8_t		namelen;	/* length of name value (no null) */
	uपूर्णांक8_t		valuelen;	/* length of value */
	uपूर्णांक8_t		flags;		/* flags bits (see xfs_attr_leaf.h) */
	xfs_dahash_t	hash;		/* this entry's hash value */
	अचिन्हित अक्षर	*name;		/* name value, poपूर्णांकer पूर्णांकo buffer */
पूर्ण xfs_attr_sf_sort_t;

#घोषणा XFS_ATTR_SF_ENTSIZE_MAX			/* max space क्रम name&value */ \
	((1 << (NBBY*(पूर्णांक)माप(uपूर्णांक8_t))) - 1)

/* space name/value uses */
अटल अंतरभूत पूर्णांक xfs_attr_sf_entsize_byname(uपूर्णांक8_t nlen, uपूर्णांक8_t vlen)
अणु
	वापस माप(काष्ठा xfs_attr_sf_entry) + nlen + vlen;
पूर्ण

/* space an entry uses */
अटल अंतरभूत पूर्णांक xfs_attr_sf_entsize(काष्ठा xfs_attr_sf_entry *sfep)
अणु
	वापस काष्ठा_size(sfep, nameval, sfep->namelen + sfep->valuelen);
पूर्ण

/* next entry in काष्ठा */
अटल अंतरभूत काष्ठा xfs_attr_sf_entry *
xfs_attr_sf_nextentry(काष्ठा xfs_attr_sf_entry *sfep)
अणु
	वापस (व्योम *)sfep + xfs_attr_sf_entsize(sfep);
पूर्ण

#पूर्ण_अगर	/* __XFS_ATTR_SF_H__ */
