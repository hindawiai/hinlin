<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000,2002-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_ATTR_H__
#घोषणा	__XFS_ATTR_H__

काष्ठा xfs_inode;
काष्ठा xfs_da_args;
काष्ठा xfs_attr_list_context;

/*
 * Large attribute lists are काष्ठाured around Btrees where all the data
 * elements are in the leaf nodes.  Attribute names are hashed पूर्णांकo an पूर्णांक,
 * then that पूर्णांक is used as the index पूर्णांकo the Btree.  Since the hashval
 * of an attribute name may not be unique, we may have duplicate keys.
 * The पूर्णांकernal links in the Btree are logical block offsets पूर्णांकo the file.
 *
 * Small attribute lists use a dअगरferent क्रमmat and are packed as tightly
 * as possible so as to fit पूर्णांकo the literal area of the inode.
 */

/*
 * The maximum size (पूर्णांकo the kernel or वापसed from the kernel) of an
 * attribute value or the buffer used क्रम an attr_list() call.  Larger
 * sizes will result in an दुस्फल वापस code.
 */
#घोषणा	ATTR_MAX_VALUELEN	(64*1024)	/* max length of a value */

/*
 * Kernel-पूर्णांकernal version of the attrlist cursor.
 */
काष्ठा xfs_attrlist_cursor_kern अणु
	__u32	hashval;	/* hash value of next entry to add */
	__u32	blkno;		/* block containing entry (suggestion) */
	__u32	offset;		/* offset in list of equal-hashvals */
	__u16	pad1;		/* padding to match user-level */
	__u8	pad2;		/* padding to match user-level */
	__u8	initted;	/* T/F: cursor has been initialized */
पूर्ण;


/*========================================================================
 * Structure used to pass context around among the routines.
 *========================================================================*/


/* व्योम; state communicated via *context */
प्रकार व्योम (*put_listent_func_t)(काष्ठा xfs_attr_list_context *, पूर्णांक,
			      अचिन्हित अक्षर *, पूर्णांक, पूर्णांक);

काष्ठा xfs_attr_list_context अणु
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_inode	*dp;		/* inode */
	काष्ठा xfs_attrlist_cursor_kern cursor;	/* position in list */
	व्योम			*buffer;	/* output buffer */

	/*
	 * Abort attribute list iteration अगर non-zero.  Can be used to pass
	 * error values to the xfs_attr_list caller.
	 */
	पूर्णांक			seen_enough;
	bool			allow_incomplete;

	sमाप_प्रकार			count;		/* num used entries */
	पूर्णांक			dupcnt;		/* count dup hashvals seen */
	पूर्णांक			bufsize;	/* total buffer size */
	पूर्णांक			firstu;		/* first used byte in buffer */
	अचिन्हित पूर्णांक		attr_filter;	/* XFS_ATTR_अणुROOT,SECUREपूर्ण */
	पूर्णांक			resynch;	/* T/F: resynch with cursor */
	put_listent_func_t	put_listent;	/* list output fmt function */
	पूर्णांक			index;		/* index पूर्णांकo output buffer */
पूर्ण;


/*========================================================================
 * Function prototypes क्रम the kernel.
 *========================================================================*/

/*
 * Overall बाह्यal पूर्णांकerface routines.
 */
पूर्णांक xfs_attr_inactive(काष्ठा xfs_inode *dp);
पूर्णांक xfs_attr_list_ilocked(काष्ठा xfs_attr_list_context *);
पूर्णांक xfs_attr_list(काष्ठा xfs_attr_list_context *);
पूर्णांक xfs_inode_hasattr(काष्ठा xfs_inode *ip);
bool xfs_attr_is_leaf(काष्ठा xfs_inode *ip);
पूर्णांक xfs_attr_get_ilocked(काष्ठा xfs_da_args *args);
पूर्णांक xfs_attr_get(काष्ठा xfs_da_args *args);
पूर्णांक xfs_attr_set(काष्ठा xfs_da_args *args);
पूर्णांक xfs_attr_set_args(काष्ठा xfs_da_args *args);
पूर्णांक xfs_has_attr(काष्ठा xfs_da_args *args);
पूर्णांक xfs_attr_हटाओ_args(काष्ठा xfs_da_args *args);
bool xfs_attr_namecheck(स्थिर व्योम *name, माप_प्रकार length);

#पूर्ण_अगर	/* __XFS_ATTR_H__ */
