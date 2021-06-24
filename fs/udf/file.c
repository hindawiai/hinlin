<शैली गुरु>
/*
 * file.c
 *
 * PURPOSE
 *  File handling routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *  This file is distributed under the terms of the GNU General Public
 *  License (GPL). Copies of the GPL can be obtained from:
 *    ftp://prep.ai.mit.edu/pub/gnu/GPL
 *  Each contributing author retains all rights to their own work.
 *
 *  (C) 1998-1999 Dave Boynton
 *  (C) 1998-2004 Ben Fennema
 *  (C) 1999-2000 Stelias Computing Inc
 *
 * HISTORY
 *
 *  10/02/98 dgb  Attempt to पूर्णांकegrate पूर्णांकo udf.o
 *  10/07/98      Switched to using generic_पढ़ोpage, etc., like isofs
 *                And it works!
 *  12/06/98 blf  Added udf_file_पढ़ो. uses generic_file_पढ़ो क्रम all हालs but
 *                ICBTAG_FLAG_AD_IN_ICB.
 *  04/06/99      64 bit file handling on 32 bit प्रणालीs taken from ext2 file.c
 *  05/12/99      Preliminary file ग_लिखो support
 */

#समावेश "udfdecl.h"
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स> /* स_रखो */
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/uपन.स>

#समावेश "udf_i.h"
#समावेश "udf_sb.h"

अटल व्योम __udf_adinicb_पढ़ोpage(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	अक्षर *kaddr;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	loff_t isize = i_size_पढ़ो(inode);

	/*
	 * We have to be careful here as truncate can change i_size under us.
	 * So just sample it once and use the same value everywhere.
	 */
	kaddr = kmap_atomic(page);
	स_नकल(kaddr, iinfo->i_data + iinfo->i_lenEAttr, isize);
	स_रखो(kaddr + isize, 0, PAGE_SIZE - isize);
	flush_dcache_page(page);
	SetPageUptodate(page);
	kunmap_atomic(kaddr);
पूर्ण

अटल पूर्णांक udf_adinicb_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	BUG_ON(!PageLocked(page));
	__udf_adinicb_पढ़ोpage(page);
	unlock_page(page);

	वापस 0;
पूर्ण

अटल पूर्णांक udf_adinicb_ग_लिखोpage(काष्ठा page *page,
				 काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	अक्षर *kaddr;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	BUG_ON(!PageLocked(page));

	kaddr = kmap_atomic(page);
	स_नकल(iinfo->i_data + iinfo->i_lenEAttr, kaddr, i_size_पढ़ो(inode));
	SetPageUptodate(page);
	kunmap_atomic(kaddr);
	mark_inode_dirty(inode);
	unlock_page(page);

	वापस 0;
पूर्ण

अटल पूर्णांक udf_adinicb_ग_लिखो_begin(काष्ठा file *file,
			काष्ठा address_space *mapping, loff_t pos,
			अचिन्हित len, अचिन्हित flags, काष्ठा page **pagep,
			व्योम **fsdata)
अणु
	काष्ठा page *page;

	अगर (WARN_ON_ONCE(pos >= PAGE_SIZE))
		वापस -EIO;
	page = grab_cache_page_ग_लिखो_begin(mapping, 0, flags);
	अगर (!page)
		वापस -ENOMEM;
	*pagep = page;

	अगर (!PageUptodate(page))
		__udf_adinicb_पढ़ोpage(page);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार udf_adinicb_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	/* Fallback to buffered I/O. */
	वापस 0;
पूर्ण

अटल पूर्णांक udf_adinicb_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
				 loff_t pos, अचिन्हित len, अचिन्हित copied,
				 काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = page->mapping->host;
	loff_t last_pos = pos + copied;
	अगर (last_pos > inode->i_size)
		i_size_ग_लिखो(inode, last_pos);
	set_page_dirty(page);
	unlock_page(page);
	put_page(page);
	वापस copied;
पूर्ण

स्थिर काष्ठा address_space_operations udf_adinicb_aops = अणु
	.पढ़ोpage	= udf_adinicb_पढ़ोpage,
	.ग_लिखोpage	= udf_adinicb_ग_लिखोpage,
	.ग_लिखो_begin	= udf_adinicb_ग_लिखो_begin,
	.ग_लिखो_end	= udf_adinicb_ग_लिखो_end,
	.direct_IO	= udf_adinicb_direct_IO,
पूर्ण;

अटल sमाप_प्रकार udf_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	sमाप_प्रकार retval;
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	पूर्णांक err;

	inode_lock(inode);

	retval = generic_ग_लिखो_checks(iocb, from);
	अगर (retval <= 0)
		जाओ out;

	करोwn_ग_लिखो(&iinfo->i_data_sem);
	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) अणु
		loff_t end = iocb->ki_pos + iov_iter_count(from);

		अगर (inode->i_sb->s_blocksize <
				(udf_file_entry_alloc_offset(inode) + end)) अणु
			err = udf_expand_file_adinicb(inode);
			अगर (err) अणु
				inode_unlock(inode);
				udf_debug("udf_expand_adinicb: err=%d\n", err);
				वापस err;
			पूर्ण
		पूर्ण अन्यथा अणु
			iinfo->i_lenAlloc = max(end, inode->i_size);
			up_ग_लिखो(&iinfo->i_data_sem);
		पूर्ण
	पूर्ण अन्यथा
		up_ग_लिखो(&iinfo->i_data_sem);

	retval = __generic_file_ग_लिखो_iter(iocb, from);
out:
	inode_unlock(inode);

	अगर (retval > 0) अणु
		mark_inode_dirty(inode);
		retval = generic_ग_लिखो_sync(iocb, retval);
	पूर्ण

	वापस retval;
पूर्ण

दीर्घ udf_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	दीर्घ old_block, new_block;
	पूर्णांक result;

	अगर (file_permission(filp, MAY_READ) != 0) अणु
		udf_debug("no permission to access inode %lu\n", inode->i_ino);
		वापस -EPERM;
	पूर्ण

	अगर (!arg && ((cmd == UDF_GETVOLIDENT) || (cmd == UDF_GETEASIZE) ||
		     (cmd == UDF_RELOCATE_BLOCKS) || (cmd == UDF_GETEABLOCK))) अणु
		udf_debug("invalid argument to udf_ioctl\n");
		वापस -EINVAL;
	पूर्ण

	चयन (cmd) अणु
	हाल UDF_GETVOLIDENT:
		अगर (copy_to_user((अक्षर __user *)arg,
				 UDF_SB(inode->i_sb)->s_volume_ident, 32))
			वापस -EFAULT;
		वापस 0;
	हाल UDF_RELOCATE_BLOCKS:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
		अगर (get_user(old_block, (दीर्घ __user *)arg))
			वापस -EFAULT;
		result = udf_relocate_blocks(inode->i_sb,
						old_block, &new_block);
		अगर (result == 0)
			result = put_user(new_block, (दीर्घ __user *)arg);
		वापस result;
	हाल UDF_GETEASIZE:
		वापस put_user(UDF_I(inode)->i_lenEAttr, (पूर्णांक __user *)arg);
	हाल UDF_GETEABLOCK:
		वापस copy_to_user((अक्षर __user *)arg,
				    UDF_I(inode)->i_data,
				    UDF_I(inode)->i_lenEAttr) ? -EFAULT : 0;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक udf_release_file(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर (filp->f_mode & FMODE_WRITE &&
	    atomic_पढ़ो(&inode->i_ग_लिखोcount) == 1) अणु
		/*
		 * Grab i_mutex to aव्योम races with ग_लिखोs changing i_size
		 * जबतक we are running.
		 */
		inode_lock(inode);
		करोwn_ग_लिखो(&UDF_I(inode)->i_data_sem);
		udf_discard_pपुनः_स्मृति(inode);
		udf_truncate_tail_extent(inode);
		up_ग_लिखो(&UDF_I(inode)->i_data_sem);
		inode_unlock(inode);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations udf_file_operations = अणु
	.पढ़ो_iter		= generic_file_पढ़ो_iter,
	.unlocked_ioctl		= udf_ioctl,
	.खोलो			= generic_file_खोलो,
	.mmap			= generic_file_mmap,
	.ग_लिखो_iter		= udf_file_ग_लिखो_iter,
	.release		= udf_release_file,
	.fsync			= generic_file_fsync,
	.splice_पढ़ो		= generic_file_splice_पढ़ो,
	.llseek			= generic_file_llseek,
पूर्ण;

अटल पूर्णांक udf_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		       काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	अगर ((attr->ia_valid & ATTR_UID) &&
	    UDF_QUERY_FLAG(sb, UDF_FLAG_UID_SET) &&
	    !uid_eq(attr->ia_uid, UDF_SB(sb)->s_uid))
		वापस -EPERM;
	अगर ((attr->ia_valid & ATTR_GID) &&
	    UDF_QUERY_FLAG(sb, UDF_FLAG_GID_SET) &&
	    !gid_eq(attr->ia_gid, UDF_SB(sb)->s_gid))
		वापस -EPERM;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_पढ़ो(inode)) अणु
		error = udf_setsize(inode, attr->ia_size);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (attr->ia_valid & ATTR_MODE)
		udf_update_extra_perms(inode, attr->ia_mode);

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations udf_file_inode_operations = अणु
	.setattr		= udf_setattr,
पूर्ण;
