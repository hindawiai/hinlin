<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines  Corp., 2000-2004
 *   Copyright (C) Christoph Hellwig, 2002
 */

#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/slab.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/security.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_debug.h"
#समावेश "jfs_dinode.h"
#समावेश "jfs_extent.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_xattr.h"
#समावेश "jfs_acl.h"

/*
 *	jfs_xattr.c: extended attribute service
 *
 * Overall design --
 *
 * Format:
 *
 *   Extended attribute lists (jfs_ea_list) consist of an overall size (32 bit
 *   value) and a variable (0 or more) number of extended attribute
 *   entries.  Each extended attribute entry (jfs_ea) is a <name,value> द्विगुन
 *   where <name> is स्थिरructed from a null-terminated ascii string
 *   (1 ... 255 bytes in the name) and <value> is arbitrary 8 bit data
 *   (1 ... 65535 bytes).  The in-memory क्रमmat is
 *
 *   0       1        2        4                4 + namelen + 1
 *   +-------+--------+--------+----------------+-------------------+
 *   | Flags | Name   | Value  | Name String \0 | Data . . . .      |
 *   |       | Length | Length |                |                   |
 *   +-------+--------+--------+----------------+-------------------+
 *
 *   A jfs_ea_list then is काष्ठाured as
 *
 *   0            4                   4 + EA_SIZE(ea1)
 *   +------------+-------------------+--------------------+-----
 *   | Overall EA | First FEA Element | Second FEA Element | .....
 *   | List Size  |                   |                    |
 *   +------------+-------------------+--------------------+-----
 *
 *   On-disk:
 *
 *	FEALISTs are stored on disk using blocks allocated by dbAlloc() and
 *	written directly. An EA list may be in-lined in the inode अगर there is
 *	sufficient room available.
 */

काष्ठा ea_buffer अणु
	पूर्णांक flag;		/* Indicates what storage xattr poपूर्णांकs to */
	पूर्णांक max_size;		/* largest xattr that fits in current buffer */
	dxd_t new_ea;		/* dxd to replace ea when modअगरying xattr */
	काष्ठा metapage *mp;	/* metapage containing ea list */
	काष्ठा jfs_ea_list *xattr;	/* buffer containing ea list */
पूर्ण;

/*
 * ea_buffer.flag values
 */
#घोषणा EA_INLINE	0x0001
#घोषणा EA_EXTENT	0x0002
#घोषणा EA_NEW		0x0004
#घोषणा EA_MALLOC	0x0008


/*
 * Mapping of on-disk attribute names: क्रम on-disk attribute names with an
 * unknown prefix (not "system.", "user.", "security.", or "trusted."), the
 * prefix "os2." is prepended.  On the way back to disk, "os2." prefixes are
 * stripped and we make sure that the reमुख्यing name करोes not start with one
 * of the know prefixes.
 */

अटल पूर्णांक is_known_namespace(स्थिर अक्षर *name)
अणु
	अगर (म_भेदन(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN) &&
	    म_भेदन(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN) &&
	    म_भेदन(name, XATTR_SECURITY_PREFIX, XATTR_SECURITY_PREFIX_LEN) &&
	    म_भेदन(name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक name_size(काष्ठा jfs_ea *ea)
अणु
	अगर (is_known_namespace(ea->name))
		वापस ea->namelen;
	अन्यथा
		वापस ea->namelen + XATTR_OS2_PREFIX_LEN;
पूर्ण

अटल अंतरभूत पूर्णांक copy_name(अक्षर *buffer, काष्ठा jfs_ea *ea)
अणु
	पूर्णांक len = ea->namelen;

	अगर (!is_known_namespace(ea->name)) अणु
		स_नकल(buffer, XATTR_OS2_PREFIX, XATTR_OS2_PREFIX_LEN);
		buffer += XATTR_OS2_PREFIX_LEN;
		len += XATTR_OS2_PREFIX_LEN;
	पूर्ण
	स_नकल(buffer, ea->name, ea->namelen);
	buffer[ea->namelen] = 0;

	वापस len;
पूर्ण

/* Forward references */
अटल व्योम ea_release(काष्ठा inode *inode, काष्ठा ea_buffer *ea_buf);

/*
 * NAME: ea_ग_लिखो_अंतरभूत
 *
 * FUNCTION: Attempt to ग_लिखो an EA अंतरभूत अगर area is available
 *
 * PRE CONDITIONS:
 *	Alपढ़ोy verअगरied that the specअगरied EA is small enough to fit अंतरभूत
 *
 * PARAMETERS:
 *	ip	- Inode poपूर्णांकer
 *	ealist	- EA list poपूर्णांकer
 *	size	- size of ealist in bytes
 *	ea	- dxd_t काष्ठाure to be filled in with necessary EA inक्रमmation
 *		  अगर we successfully copy the EA अंतरभूत
 *
 * NOTES:
 *	Checks अगर the inode's अंतरभूत area is available.  If so, copies EA अंतरभूत
 *	and sets <ea> fields appropriately.  Otherwise, वापसs failure, EA will
 *	have to be put पूर्णांकo an extent.
 *
 * RETURNS: 0 क्रम successful copy to अंतरभूत area; -1 अगर area not available
 */
अटल पूर्णांक ea_ग_लिखो_अंतरभूत(काष्ठा inode *ip, काष्ठा jfs_ea_list *ealist,
			   पूर्णांक size, dxd_t * ea)
अणु
	काष्ठा jfs_inode_info *ji = JFS_IP(ip);

	/*
	 * Make sure we have an EA -- the शून्य EA list is valid, but you
	 * can't copy it!
	 */
	अगर (ealist && size > माप (काष्ठा jfs_ea_list)) अणु
		निश्चित(size <= माप (ji->i_अंतरभूत_ea));

		/*
		 * See अगर the space is available or अगर it is alपढ़ोy being
		 * used क्रम an अंतरभूत EA.
		 */
		अगर (!(ji->mode2 & INLINEEA) && !(ji->ea.flag & DXD_INLINE))
			वापस -EPERM;

		DXDsize(ea, size);
		DXDlength(ea, 0);
		DXDaddress(ea, 0);
		स_नकल(ji->i_अंतरभूत_ea, ealist, size);
		ea->flag = DXD_INLINE;
		ji->mode2 &= ~INLINEEA;
	पूर्ण अन्यथा अणु
		ea->flag = 0;
		DXDsize(ea, 0);
		DXDlength(ea, 0);
		DXDaddress(ea, 0);

		/* Free up INLINE area */
		अगर (ji->ea.flag & DXD_INLINE)
			ji->mode2 |= INLINEEA;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * NAME: ea_ग_लिखो
 *
 * FUNCTION: Write an EA क्रम an inode
 *
 * PRE CONDITIONS: EA has been verअगरied
 *
 * PARAMETERS:
 *	ip	- Inode poपूर्णांकer
 *	ealist	- EA list poपूर्णांकer
 *	size	- size of ealist in bytes
 *	ea	- dxd_t काष्ठाure to be filled in appropriately with where the
 *		  EA was copied
 *
 * NOTES: Will ग_लिखो EA अंतरभूत अगर able to, otherwise allocates blocks क्रम an
 *	extent and synchronously ग_लिखोs it to those blocks.
 *
 * RETURNS: 0 क्रम success; Anything अन्यथा indicates failure
 */
अटल पूर्णांक ea_ग_लिखो(काष्ठा inode *ip, काष्ठा jfs_ea_list *ealist, पूर्णांक size,
		       dxd_t * ea)
अणु
	काष्ठा super_block *sb = ip->i_sb;
	काष्ठा jfs_inode_info *ji = JFS_IP(ip);
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	पूर्णांक nblocks;
	s64 blkno;
	पूर्णांक rc = 0, i;
	अक्षर *cp;
	s32 nbytes, nb;
	s32 bytes_to_ग_लिखो;
	काष्ठा metapage *mp;

	/*
	 * Quick check to see अगर this is an in-linable EA.  Short EAs
	 * and empty EAs are all in-linable, provided the space exists.
	 */
	अगर (!ealist || size <= माप (ji->i_अंतरभूत_ea)) अणु
		अगर (!ea_ग_लिखो_अंतरभूत(ip, ealist, size, ea))
			वापस 0;
	पूर्ण

	/* figure out how many blocks we need */
	nblocks = (size + (sb->s_blocksize - 1)) >> sb->s_blocksize_bits;

	/* Allocate new blocks to quota. */
	rc = dquot_alloc_block(ip, nblocks);
	अगर (rc)
		वापस rc;

	rc = dbAlloc(ip, INOHINT(ip), nblocks, &blkno);
	अगर (rc) अणु
		/*Rollback quota allocation. */
		dquot_मुक्त_block(ip, nblocks);
		वापस rc;
	पूर्ण

	/*
	 * Now have nblocks worth of storage to stuff पूर्णांकo the FEALIST.
	 * loop over the FEALIST copying data पूर्णांकo the buffer one page at
	 * a समय.
	 */
	cp = (अक्षर *) ealist;
	nbytes = size;
	क्रम (i = 0; i < nblocks; i += sbi->nbperpage) अणु
		/*
		 * Determine how many bytes क्रम this request, and round up to
		 * the nearest aggregate block size
		 */
		nb = min(PSIZE, nbytes);
		bytes_to_ग_लिखो =
		    ((((nb + sb->s_blocksize - 1)) >> sb->s_blocksize_bits))
		    << sb->s_blocksize_bits;

		अगर (!(mp = get_metapage(ip, blkno + i, bytes_to_ग_लिखो, 1))) अणु
			rc = -EIO;
			जाओ failed;
		पूर्ण

		स_नकल(mp->data, cp, nb);

		/*
		 * We really need a way to propagate errors क्रम
		 * क्रमced ग_लिखोs like this one.  --hch
		 *
		 * (__ग_लिखो_metapage => release_metapage => flush_metapage)
		 */
#अगर_घोषित _JFS_FIXME
		अगर ((rc = flush_metapage(mp))) अणु
			/*
			 * the ग_लिखो failed -- this means that the buffer
			 * is still asचिन्हित and the blocks are not being
			 * used.  this seems like the best error recovery
			 * we can get ...
			 */
			जाओ failed;
		पूर्ण
#अन्यथा
		flush_metapage(mp);
#पूर्ण_अगर

		cp += PSIZE;
		nbytes -= nb;
	पूर्ण

	ea->flag = DXD_EXTENT;
	DXDsize(ea, le32_to_cpu(ealist->size));
	DXDlength(ea, nblocks);
	DXDaddress(ea, blkno);

	/* Free up INLINE area */
	अगर (ji->ea.flag & DXD_INLINE)
		ji->mode2 |= INLINEEA;

	वापस 0;

      failed:
	/* Rollback quota allocation. */
	dquot_मुक्त_block(ip, nblocks);

	dbFree(ip, blkno, nblocks);
	वापस rc;
पूर्ण

/*
 * NAME: ea_पढ़ो_अंतरभूत
 *
 * FUNCTION: Read an अंतरभूतd EA पूर्णांकo user's buffer
 *
 * PARAMETERS:
 *	ip	- Inode poपूर्णांकer
 *	ealist	- Poपूर्णांकer to buffer to fill in with EA
 *
 * RETURNS: 0
 */
अटल पूर्णांक ea_पढ़ो_अंतरभूत(काष्ठा inode *ip, काष्ठा jfs_ea_list *ealist)
अणु
	काष्ठा jfs_inode_info *ji = JFS_IP(ip);
	पूर्णांक ea_size = sizeDXD(&ji->ea);

	अगर (ea_size == 0) अणु
		ealist->size = 0;
		वापस 0;
	पूर्ण

	/* Sanity Check */
	अगर ((sizeDXD(&ji->ea) > माप (ji->i_अंतरभूत_ea)))
		वापस -EIO;
	अगर (le32_to_cpu(((काष्ठा jfs_ea_list *) &ji->i_अंतरभूत_ea)->size)
	    != ea_size)
		वापस -EIO;

	स_नकल(ealist, ji->i_अंतरभूत_ea, ea_size);
	वापस 0;
पूर्ण

/*
 * NAME: ea_पढ़ो
 *
 * FUNCTION: copy EA data पूर्णांकo user's buffer
 *
 * PARAMETERS:
 *	ip	- Inode poपूर्णांकer
 *	ealist	- Poपूर्णांकer to buffer to fill in with EA
 *
 * NOTES:  If EA is अंतरभूत calls ea_पढ़ो_अंतरभूत() to copy EA.
 *
 * RETURNS: 0 क्रम success; other indicates failure
 */
अटल पूर्णांक ea_पढ़ो(काष्ठा inode *ip, काष्ठा jfs_ea_list *ealist)
अणु
	काष्ठा super_block *sb = ip->i_sb;
	काष्ठा jfs_inode_info *ji = JFS_IP(ip);
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	पूर्णांक nblocks;
	s64 blkno;
	अक्षर *cp = (अक्षर *) ealist;
	पूर्णांक i;
	पूर्णांक nbytes, nb;
	s32 bytes_to_पढ़ो;
	काष्ठा metapage *mp;

	/* quick check क्रम in-line EA */
	अगर (ji->ea.flag & DXD_INLINE)
		वापस ea_पढ़ो_अंतरभूत(ip, ealist);

	nbytes = sizeDXD(&ji->ea);
	अगर (!nbytes) अणु
		jfs_error(sb, "nbytes is 0\n");
		वापस -EIO;
	पूर्ण

	/*
	 * Figure out how many blocks were allocated when this EA list was
	 * originally written to disk.
	 */
	nblocks = lengthDXD(&ji->ea) << sbi->l2nbperpage;
	blkno = addressDXD(&ji->ea) << sbi->l2nbperpage;

	/*
	 * I have found the disk blocks which were originally used to store
	 * the FEALIST.  now i loop over each contiguous block copying the
	 * data पूर्णांकo the buffer.
	 */
	क्रम (i = 0; i < nblocks; i += sbi->nbperpage) अणु
		/*
		 * Determine how many bytes क्रम this request, and round up to
		 * the nearest aggregate block size
		 */
		nb = min(PSIZE, nbytes);
		bytes_to_पढ़ो =
		    ((((nb + sb->s_blocksize - 1)) >> sb->s_blocksize_bits))
		    << sb->s_blocksize_bits;

		अगर (!(mp = पढ़ो_metapage(ip, blkno + i, bytes_to_पढ़ो, 1)))
			वापस -EIO;

		स_नकल(cp, mp->data, nb);
		release_metapage(mp);

		cp += PSIZE;
		nbytes -= nb;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * NAME: ea_get
 *
 * FUNCTION: Returns buffer containing existing extended attributes.
 *	     The size of the buffer will be the larger of the existing
 *	     attributes size, or min_size.
 *
 *	     The buffer, which may be अंतरभूतd in the inode or in the
 *	     page cache must be release by calling ea_release or ea_put
 *
 * PARAMETERS:
 *	inode	- Inode poपूर्णांकer
 *	ea_buf	- Structure to be populated with ealist and its metadata
 *	min_size- minimum size of buffer to be वापसed
 *
 * RETURNS: 0 क्रम success; Other indicates failure
 */
अटल पूर्णांक ea_get(काष्ठा inode *inode, काष्ठा ea_buffer *ea_buf, पूर्णांक min_size)
अणु
	काष्ठा jfs_inode_info *ji = JFS_IP(inode);
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक size;
	पूर्णांक ea_size = sizeDXD(&ji->ea);
	पूर्णांक blocks_needed, current_blocks;
	s64 blkno;
	पूर्णांक rc;
	पूर्णांक quota_allocation = 0;

	/* When fsck.jfs clears a bad ea, it करोesn't clear the size */
	अगर (ji->ea.flag == 0)
		ea_size = 0;

	अगर (ea_size == 0) अणु
		अगर (min_size == 0) अणु
			ea_buf->flag = 0;
			ea_buf->max_size = 0;
			ea_buf->xattr = शून्य;
			वापस 0;
		पूर्ण
		अगर ((min_size <= माप (ji->i_अंतरभूत_ea)) &&
		    (ji->mode2 & INLINEEA)) अणु
			ea_buf->flag = EA_INLINE | EA_NEW;
			ea_buf->max_size = माप (ji->i_अंतरभूत_ea);
			ea_buf->xattr = (काष्ठा jfs_ea_list *) ji->i_अंतरभूत_ea;
			DXDlength(&ea_buf->new_ea, 0);
			DXDaddress(&ea_buf->new_ea, 0);
			ea_buf->new_ea.flag = DXD_INLINE;
			DXDsize(&ea_buf->new_ea, min_size);
			वापस 0;
		पूर्ण
		current_blocks = 0;
	पूर्ण अन्यथा अगर (ji->ea.flag & DXD_INLINE) अणु
		अगर (min_size <= माप (ji->i_अंतरभूत_ea)) अणु
			ea_buf->flag = EA_INLINE;
			ea_buf->max_size = माप (ji->i_अंतरभूत_ea);
			ea_buf->xattr = (काष्ठा jfs_ea_list *) ji->i_अंतरभूत_ea;
			जाओ size_check;
		पूर्ण
		current_blocks = 0;
	पूर्ण अन्यथा अणु
		अगर (!(ji->ea.flag & DXD_EXTENT)) अणु
			jfs_error(sb, "invalid ea.flag\n");
			वापस -EIO;
		पूर्ण
		current_blocks = (ea_size + sb->s_blocksize - 1) >>
		    sb->s_blocksize_bits;
	पूर्ण
	size = max(min_size, ea_size);

	अगर (size > PSIZE) अणु
		/*
		 * To keep the rest of the code simple.  Allocate a
		 * contiguous buffer to work with. Make the buffer large
		 * enough to make use of the whole extent.
		 */
		ea_buf->max_size = (size + sb->s_blocksize - 1) &
		    ~(sb->s_blocksize - 1);

		ea_buf->xattr = kदो_स्मृति(ea_buf->max_size, GFP_KERNEL);
		अगर (ea_buf->xattr == शून्य)
			वापस -ENOMEM;

		ea_buf->flag = EA_MALLOC;

		अगर (ea_size == 0)
			वापस 0;

		अगर ((rc = ea_पढ़ो(inode, ea_buf->xattr))) अणु
			kमुक्त(ea_buf->xattr);
			ea_buf->xattr = शून्य;
			वापस rc;
		पूर्ण
		जाओ size_check;
	पूर्ण
	blocks_needed = (min_size + sb->s_blocksize - 1) >>
	    sb->s_blocksize_bits;

	अगर (blocks_needed > current_blocks) अणु
		/* Allocate new blocks to quota. */
		rc = dquot_alloc_block(inode, blocks_needed);
		अगर (rc)
			वापस -EDQUOT;

		quota_allocation = blocks_needed;

		rc = dbAlloc(inode, INOHINT(inode), (s64) blocks_needed,
			     &blkno);
		अगर (rc)
			जाओ clean_up;

		DXDlength(&ea_buf->new_ea, blocks_needed);
		DXDaddress(&ea_buf->new_ea, blkno);
		ea_buf->new_ea.flag = DXD_EXTENT;
		DXDsize(&ea_buf->new_ea, min_size);

		ea_buf->flag = EA_EXTENT | EA_NEW;

		ea_buf->mp = get_metapage(inode, blkno,
					  blocks_needed << sb->s_blocksize_bits,
					  1);
		अगर (ea_buf->mp == शून्य) अणु
			dbFree(inode, blkno, (s64) blocks_needed);
			rc = -EIO;
			जाओ clean_up;
		पूर्ण
		ea_buf->xattr = ea_buf->mp->data;
		ea_buf->max_size = (min_size + sb->s_blocksize - 1) &
		    ~(sb->s_blocksize - 1);
		अगर (ea_size == 0)
			वापस 0;
		अगर ((rc = ea_पढ़ो(inode, ea_buf->xattr))) अणु
			discard_metapage(ea_buf->mp);
			dbFree(inode, blkno, (s64) blocks_needed);
			जाओ clean_up;
		पूर्ण
		जाओ size_check;
	पूर्ण
	ea_buf->flag = EA_EXTENT;
	ea_buf->mp = पढ़ो_metapage(inode, addressDXD(&ji->ea),
				   lengthDXD(&ji->ea) << sb->s_blocksize_bits,
				   1);
	अगर (ea_buf->mp == शून्य) अणु
		rc = -EIO;
		जाओ clean_up;
	पूर्ण
	ea_buf->xattr = ea_buf->mp->data;
	ea_buf->max_size = (ea_size + sb->s_blocksize - 1) &
	    ~(sb->s_blocksize - 1);

      size_check:
	अगर (EALIST_SIZE(ea_buf->xattr) != ea_size) अणु
		prपूर्णांकk(KERN_ERR "ea_get: invalid extended attribute\n");
		prपूर्णांक_hex_dump(KERN_ERR, "", DUMP_PREFIX_ADDRESS, 16, 1,
				     ea_buf->xattr, ea_size, 1);
		ea_release(inode, ea_buf);
		rc = -EIO;
		जाओ clean_up;
	पूर्ण

	वापस ea_size;

      clean_up:
	/* Rollback quota allocation */
	अगर (quota_allocation)
		dquot_मुक्त_block(inode, quota_allocation);

	वापस (rc);
पूर्ण

अटल व्योम ea_release(काष्ठा inode *inode, काष्ठा ea_buffer *ea_buf)
अणु
	अगर (ea_buf->flag & EA_MALLOC)
		kमुक्त(ea_buf->xattr);
	अन्यथा अगर (ea_buf->flag & EA_EXTENT) अणु
		निश्चित(ea_buf->mp);
		release_metapage(ea_buf->mp);

		अगर (ea_buf->flag & EA_NEW)
			dbFree(inode, addressDXD(&ea_buf->new_ea),
			       lengthDXD(&ea_buf->new_ea));
	पूर्ण
पूर्ण

अटल पूर्णांक ea_put(tid_t tid, काष्ठा inode *inode, काष्ठा ea_buffer *ea_buf,
		  पूर्णांक new_size)
अणु
	काष्ठा jfs_inode_info *ji = JFS_IP(inode);
	अचिन्हित दीर्घ old_blocks, new_blocks;
	पूर्णांक rc = 0;

	अगर (new_size == 0) अणु
		ea_release(inode, ea_buf);
		ea_buf = शून्य;
	पूर्ण अन्यथा अगर (ea_buf->flag & EA_INLINE) अणु
		निश्चित(new_size <= माप (ji->i_अंतरभूत_ea));
		ji->mode2 &= ~INLINEEA;
		ea_buf->new_ea.flag = DXD_INLINE;
		DXDsize(&ea_buf->new_ea, new_size);
		DXDaddress(&ea_buf->new_ea, 0);
		DXDlength(&ea_buf->new_ea, 0);
	पूर्ण अन्यथा अगर (ea_buf->flag & EA_MALLOC) अणु
		rc = ea_ग_लिखो(inode, ea_buf->xattr, new_size, &ea_buf->new_ea);
		kमुक्त(ea_buf->xattr);
	पूर्ण अन्यथा अगर (ea_buf->flag & EA_NEW) अणु
		/* We have alपढ़ोy allocated a new dxd */
		flush_metapage(ea_buf->mp);
	पूर्ण अन्यथा अणु
		/* ->xattr must poपूर्णांक to original ea's metapage */
		rc = ea_ग_लिखो(inode, ea_buf->xattr, new_size, &ea_buf->new_ea);
		discard_metapage(ea_buf->mp);
	पूर्ण
	अगर (rc)
		वापस rc;

	old_blocks = new_blocks = 0;

	अगर (ji->ea.flag & DXD_EXTENT) अणु
		invalidate_dxd_metapages(inode, ji->ea);
		old_blocks = lengthDXD(&ji->ea);
	पूर्ण

	अगर (ea_buf) अणु
		txEA(tid, inode, &ji->ea, &ea_buf->new_ea);
		अगर (ea_buf->new_ea.flag & DXD_EXTENT) अणु
			new_blocks = lengthDXD(&ea_buf->new_ea);
			अगर (ji->ea.flag & DXD_INLINE)
				ji->mode2 |= INLINEEA;
		पूर्ण
		ji->ea = ea_buf->new_ea;
	पूर्ण अन्यथा अणु
		txEA(tid, inode, &ji->ea, शून्य);
		अगर (ji->ea.flag & DXD_INLINE)
			ji->mode2 |= INLINEEA;
		ji->ea.flag = 0;
		ji->ea.size = 0;
	पूर्ण

	/* If old blocks exist, they must be हटाओd from quota allocation. */
	अगर (old_blocks)
		dquot_मुक्त_block(inode, old_blocks);

	inode->i_स_समय = current_समय(inode);

	वापस 0;
पूर्ण

पूर्णांक __jfs_setxattr(tid_t tid, काष्ठा inode *inode, स्थिर अक्षर *name,
		   स्थिर व्योम *value, माप_प्रकार value_len, पूर्णांक flags)
अणु
	काष्ठा jfs_ea_list *ealist;
	काष्ठा jfs_ea *ea, *old_ea = शून्य, *next_ea = शून्य;
	काष्ठा ea_buffer ea_buf;
	पूर्णांक old_ea_size = 0;
	पूर्णांक xattr_size;
	पूर्णांक new_size;
	पूर्णांक namelen = म_माप(name);
	पूर्णांक found = 0;
	पूर्णांक rc;
	पूर्णांक length;

	करोwn_ग_लिखो(&JFS_IP(inode)->xattr_sem);

	xattr_size = ea_get(inode, &ea_buf, 0);
	अगर (xattr_size < 0) अणु
		rc = xattr_size;
		जाओ out;
	पूर्ण

      again:
	ealist = (काष्ठा jfs_ea_list *) ea_buf.xattr;
	new_size = माप (काष्ठा jfs_ea_list);

	अगर (xattr_size) अणु
		क्रम (ea = FIRST_EA(ealist); ea < END_EALIST(ealist);
		     ea = NEXT_EA(ea)) अणु
			अगर ((namelen == ea->namelen) &&
			    (स_भेद(name, ea->name, namelen) == 0)) अणु
				found = 1;
				अगर (flags & XATTR_CREATE) अणु
					rc = -EEXIST;
					जाओ release;
				पूर्ण
				old_ea = ea;
				old_ea_size = EA_SIZE(ea);
				next_ea = NEXT_EA(ea);
			पूर्ण अन्यथा
				new_size += EA_SIZE(ea);
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		अगर (flags & XATTR_REPLACE) अणु
			rc = -ENODATA;
			जाओ release;
		पूर्ण
		अगर (value == शून्य) अणु
			rc = 0;
			जाओ release;
		पूर्ण
	पूर्ण
	अगर (value)
		new_size += माप (काष्ठा jfs_ea) + namelen + 1 + value_len;

	अगर (new_size > ea_buf.max_size) अणु
		/*
		 * We need to allocate more space क्रम merged ea list.
		 * We should only have loop to again: once.
		 */
		ea_release(inode, &ea_buf);
		xattr_size = ea_get(inode, &ea_buf, new_size);
		अगर (xattr_size < 0) अणु
			rc = xattr_size;
			जाओ out;
		पूर्ण
		जाओ again;
	पूर्ण

	/* Remove old ea of the same name */
	अगर (found) अणु
		/* number of bytes following target EA */
		length = (अक्षर *) END_EALIST(ealist) - (अक्षर *) next_ea;
		अगर (length > 0)
			स_हटाओ(old_ea, next_ea, length);
		xattr_size -= old_ea_size;
	पूर्ण

	/* Add new entry to the end */
	अगर (value) अणु
		अगर (xattr_size == 0)
			/* Completely new ea list */
			xattr_size = माप (काष्ठा jfs_ea_list);

		/*
		 * The size of EA value is limitted by on-disk क्रमmat up to
		 *  __le16, there would be an overflow अगर the size is equal
		 * to XATTR_SIZE_MAX (65536).  In order to aव्योम this issue,
		 * we can pre-checkup the value size against अच_लघु_उच्च, and
		 * वापस -E2BIG in this हाल, which is consistent with the
		 * VFS setxattr पूर्णांकerface.
		 */
		अगर (value_len >= अच_लघु_उच्च) अणु
			rc = -E2BIG;
			जाओ release;
		पूर्ण

		ea = (काष्ठा jfs_ea *) ((अक्षर *) ealist + xattr_size);
		ea->flag = 0;
		ea->namelen = namelen;
		ea->valuelen = (cpu_to_le16(value_len));
		स_नकल(ea->name, name, namelen);
		ea->name[namelen] = 0;
		अगर (value_len)
			स_नकल(&ea->name[namelen + 1], value, value_len);
		xattr_size += EA_SIZE(ea);
	पूर्ण

	/* DEBUG - If we did this right, these number match */
	अगर (xattr_size != new_size) अणु
		prपूर्णांकk(KERN_ERR
		       "__jfs_setxattr: xattr_size = %d, new_size = %d\n",
		       xattr_size, new_size);

		rc = -EINVAL;
		जाओ release;
	पूर्ण

	/*
	 * If we're left with an empty list, there's no ea
	 */
	अगर (new_size == माप (काष्ठा jfs_ea_list))
		new_size = 0;

	ealist->size = cpu_to_le32(new_size);

	rc = ea_put(tid, inode, &ea_buf, new_size);

	जाओ out;
      release:
	ea_release(inode, &ea_buf);
      out:
	up_ग_लिखो(&JFS_IP(inode)->xattr_sem);

	वापस rc;
पूर्ण

sमाप_प्रकार __jfs_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *data,
		       माप_प्रकार buf_size)
अणु
	काष्ठा jfs_ea_list *ealist;
	काष्ठा jfs_ea *ea;
	काष्ठा ea_buffer ea_buf;
	पूर्णांक xattr_size;
	sमाप_प्रकार size;
	पूर्णांक namelen = म_माप(name);
	अक्षर *value;

	करोwn_पढ़ो(&JFS_IP(inode)->xattr_sem);

	xattr_size = ea_get(inode, &ea_buf, 0);

	अगर (xattr_size < 0) अणु
		size = xattr_size;
		जाओ out;
	पूर्ण

	अगर (xattr_size == 0)
		जाओ not_found;

	ealist = (काष्ठा jfs_ea_list *) ea_buf.xattr;

	/* Find the named attribute */
	क्रम (ea = FIRST_EA(ealist); ea < END_EALIST(ealist); ea = NEXT_EA(ea))
		अगर ((namelen == ea->namelen) &&
		    स_भेद(name, ea->name, namelen) == 0) अणु
			/* Found it */
			size = le16_to_cpu(ea->valuelen);
			अगर (!data)
				जाओ release;
			अन्यथा अगर (size > buf_size) अणु
				size = -दुस्फल;
				जाओ release;
			पूर्ण
			value = ((अक्षर *) &ea->name) + ea->namelen + 1;
			स_नकल(data, value, size);
			जाओ release;
		पूर्ण
      not_found:
	size = -ENODATA;
      release:
	ea_release(inode, &ea_buf);
      out:
	up_पढ़ो(&JFS_IP(inode)->xattr_sem);

	वापस size;
पूर्ण

/*
 * No special permissions are needed to list attributes except क्रम trusted.*
 */
अटल अंतरभूत पूर्णांक can_list(काष्ठा jfs_ea *ea)
अणु
	वापस (म_भेदन(ea->name, XATTR_TRUSTED_PREFIX,
			    XATTR_TRUSTED_PREFIX_LEN) ||
		capable(CAP_SYS_ADMIN));
पूर्ण

sमाप_प्रकार jfs_listxattr(काष्ठा dentry * dentry, अक्षर *data, माप_प्रकार buf_size)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	अक्षर *buffer;
	sमाप_प्रकार size = 0;
	पूर्णांक xattr_size;
	काष्ठा jfs_ea_list *ealist;
	काष्ठा jfs_ea *ea;
	काष्ठा ea_buffer ea_buf;

	करोwn_पढ़ो(&JFS_IP(inode)->xattr_sem);

	xattr_size = ea_get(inode, &ea_buf, 0);
	अगर (xattr_size < 0) अणु
		size = xattr_size;
		जाओ out;
	पूर्ण

	अगर (xattr_size == 0)
		जाओ release;

	ealist = (काष्ठा jfs_ea_list *) ea_buf.xattr;

	/* compute required size of list */
	क्रम (ea = FIRST_EA(ealist); ea < END_EALIST(ealist); ea = NEXT_EA(ea)) अणु
		अगर (can_list(ea))
			size += name_size(ea) + 1;
	पूर्ण

	अगर (!data)
		जाओ release;

	अगर (size > buf_size) अणु
		size = -दुस्फल;
		जाओ release;
	पूर्ण

	/* Copy attribute names to buffer */
	buffer = data;
	क्रम (ea = FIRST_EA(ealist); ea < END_EALIST(ealist); ea = NEXT_EA(ea)) अणु
		अगर (can_list(ea)) अणु
			पूर्णांक namelen = copy_name(buffer, ea);
			buffer += namelen + 1;
		पूर्ण
	पूर्ण

      release:
	ea_release(inode, &ea_buf);
      out:
	up_पढ़ो(&JFS_IP(inode)->xattr_sem);
	वापस size;
पूर्ण

अटल पूर्णांक __jfs_xattr_set(काष्ठा inode *inode, स्थिर अक्षर *name,
			   स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा jfs_inode_info *ji = JFS_IP(inode);
	tid_t tid;
	पूर्णांक rc;

	tid = txBegin(inode->i_sb, 0);
	mutex_lock(&ji->commit_mutex);
	rc = __jfs_setxattr(tid, inode, name, value, size, flags);
	अगर (!rc)
		rc = txCommit(tid, 1, &inode, 0);
	txEnd(tid);
	mutex_unlock(&ji->commit_mutex);

	वापस rc;
पूर्ण

अटल पूर्णांक jfs_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			 काष्ठा dentry *unused, काष्ठा inode *inode,
			 स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	name = xattr_full_name(handler, name);
	वापस __jfs_getxattr(inode, name, value, size);
पूर्ण

अटल पूर्णांक jfs_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			 काष्ठा user_namespace *mnt_userns,
			 काष्ठा dentry *unused, काष्ठा inode *inode,
			 स्थिर अक्षर *name, स्थिर व्योम *value,
			 माप_प्रकार size, पूर्णांक flags)
अणु
	name = xattr_full_name(handler, name);
	वापस __jfs_xattr_set(inode, name, value, size, flags);
पूर्ण

अटल पूर्णांक jfs_xattr_get_os2(स्थिर काष्ठा xattr_handler *handler,
			     काष्ठा dentry *unused, काष्ठा inode *inode,
			     स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	अगर (is_known_namespace(name))
		वापस -EOPNOTSUPP;
	वापस __jfs_getxattr(inode, name, value, size);
पूर्ण

अटल पूर्णांक jfs_xattr_set_os2(स्थिर काष्ठा xattr_handler *handler,
			     काष्ठा user_namespace *mnt_userns,
			     काष्ठा dentry *unused, काष्ठा inode *inode,
			     स्थिर अक्षर *name, स्थिर व्योम *value,
			     माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (is_known_namespace(name))
		वापस -EOPNOTSUPP;
	वापस __jfs_xattr_set(inode, name, value, size, flags);
पूर्ण

अटल स्थिर काष्ठा xattr_handler jfs_user_xattr_handler = अणु
	.prefix = XATTR_USER_PREFIX,
	.get = jfs_xattr_get,
	.set = jfs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler jfs_os2_xattr_handler = अणु
	.prefix = XATTR_OS2_PREFIX,
	.get = jfs_xattr_get_os2,
	.set = jfs_xattr_set_os2,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler jfs_security_xattr_handler = अणु
	.prefix = XATTR_SECURITY_PREFIX,
	.get = jfs_xattr_get,
	.set = jfs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler jfs_trusted_xattr_handler = अणु
	.prefix = XATTR_TRUSTED_PREFIX,
	.get = jfs_xattr_get,
	.set = jfs_xattr_set,
पूर्ण;

स्थिर काष्ठा xattr_handler *jfs_xattr_handlers[] = अणु
#अगर_घोषित CONFIG_JFS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	&jfs_os2_xattr_handler,
	&jfs_user_xattr_handler,
	&jfs_security_xattr_handler,
	&jfs_trusted_xattr_handler,
	शून्य,
पूर्ण;


#अगर_घोषित CONFIG_JFS_SECURITY
अटल पूर्णांक jfs_initxattrs(काष्ठा inode *inode, स्थिर काष्ठा xattr *xattr_array,
			  व्योम *fs_info)
अणु
	स्थिर काष्ठा xattr *xattr;
	tid_t *tid = fs_info;
	अक्षर *name;
	पूर्णांक err = 0;

	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु
		name = kदो_स्मृति(XATTR_SECURITY_PREFIX_LEN +
			       म_माप(xattr->name) + 1, GFP_NOFS);
		अगर (!name) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण
		म_नकल(name, XATTR_SECURITY_PREFIX);
		म_नकल(name + XATTR_SECURITY_PREFIX_LEN, xattr->name);

		err = __jfs_setxattr(*tid, inode, name,
				     xattr->value, xattr->value_len, 0);
		kमुक्त(name);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक jfs_init_security(tid_t tid, काष्ठा inode *inode, काष्ठा inode *dir,
		      स्थिर काष्ठा qstr *qstr)
अणु
	वापस security_inode_init_security(inode, dir, qstr,
					    &jfs_initxattrs, &tid);
पूर्ण
#पूर्ण_अगर
