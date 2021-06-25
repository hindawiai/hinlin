<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* 
 * QNX4 file प्रणाली, Linux implementation.
 * 
 * Version : 0.2.1
 * 
 * Using parts of the xiafs fileप्रणाली.
 * 
 * History :
 * 
 * 01-06-1998 by Riअक्षरd Frowijn : first release.
 * 21-06-1998 by Frank Denis : dcache support, fixed error codes.
 * 04-07-1998 by Frank Denis : first step क्रम सूची_हटाओ/unlink.
 */

#समावेश <linux/buffer_head.h>
#समावेश "qnx4.h"


/*
 * check अगर the filename is correct. For some obscure reason, qnx ग_लिखोs a
 * new file twice in the directory entry, first with all possible options at 0
 * and क्रम a second समय the way it is, they want us not to access the qnx
 * fileप्रणाली when whe are using linux.
 */
अटल पूर्णांक qnx4_match(पूर्णांक len, स्थिर अक्षर *name,
		      काष्ठा buffer_head *bh, अचिन्हित दीर्घ *offset)
अणु
	काष्ठा qnx4_inode_entry *de;
	पूर्णांक namelen, thislen;

	अगर (bh == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "qnx4: matching unassigned buffer !\n");
		वापस 0;
	पूर्ण
	de = (काष्ठा qnx4_inode_entry *) (bh->b_data + *offset);
	*offset += QNX4_सूची_ENTRY_SIZE;
	अगर ((de->di_status & QNX4_खाता_LINK) != 0) अणु
		namelen = QNX4_NAME_MAX;
	पूर्ण अन्यथा अणु
		namelen = QNX4_SHORT_NAME_MAX;
	पूर्ण
	thislen = म_माप( de->di_fname );
	अगर ( thislen > namelen )
		thislen = namelen;
	अगर (len != thislen) अणु
		वापस 0;
	पूर्ण
	अगर (म_भेदन(name, de->di_fname, len) == 0) अणु
		अगर ((de->di_status & (QNX4_खाता_USED|QNX4_खाता_LINK)) != 0) अणु
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा buffer_head *qnx4_find_entry(पूर्णांक len, काष्ठा inode *dir,
	   स्थिर अक्षर *name, काष्ठा qnx4_inode_entry **res_dir, पूर्णांक *ino)
अणु
	अचिन्हित दीर्घ block, offset, blkofs;
	काष्ठा buffer_head *bh;

	*res_dir = शून्य;
	bh = शून्य;
	block = offset = blkofs = 0;
	जबतक (blkofs * QNX4_BLOCK_SIZE + offset < dir->i_size) अणु
		अगर (!bh) अणु
			block = qnx4_block_map(dir, blkofs);
			अगर (block)
				bh = sb_bपढ़ो(dir->i_sb, block);
			अगर (!bh) अणु
				blkofs++;
				जारी;
			पूर्ण
		पूर्ण
		*res_dir = (काष्ठा qnx4_inode_entry *) (bh->b_data + offset);
		अगर (qnx4_match(len, name, bh, &offset)) अणु
			*ino = block * QNX4_INODES_PER_BLOCK +
			    (offset / QNX4_सूची_ENTRY_SIZE) - 1;
			वापस bh;
		पूर्ण
		अगर (offset < bh->b_size) अणु
			जारी;
		पूर्ण
		brअन्यथा(bh);
		bh = शून्य;
		offset = 0;
		blkofs++;
	पूर्ण
	brअन्यथा(bh);
	*res_dir = शून्य;
	वापस शून्य;
पूर्ण

काष्ठा dentry * qnx4_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ino;
	काष्ठा qnx4_inode_entry *de;
	काष्ठा qnx4_link_info *lnk;
	काष्ठा buffer_head *bh;
	स्थिर अक्षर *name = dentry->d_name.name;
	पूर्णांक len = dentry->d_name.len;
	काष्ठा inode *foundinode = शून्य;

	अगर (!(bh = qnx4_find_entry(len, dir, name, &de, &ino)))
		जाओ out;
	/* The entry is linked, let's get the real info */
	अगर ((de->di_status & QNX4_खाता_LINK) == QNX4_खाता_LINK) अणु
		lnk = (काष्ठा qnx4_link_info *) de;
		ino = (le32_to_cpu(lnk->dl_inode_blk) - 1) *
                    QNX4_INODES_PER_BLOCK +
		    lnk->dl_inode_ndx;
	पूर्ण
	brअन्यथा(bh);

	foundinode = qnx4_iget(dir->i_sb, ino);
	अगर (IS_ERR(foundinode))
		QNX4DEBUG((KERN_ERR "qnx4: lookup->iget -> error %ld\n",
			   PTR_ERR(foundinode)));
out:
	वापस d_splice_alias(foundinode, dentry);
पूर्ण
