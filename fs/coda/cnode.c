<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* cnode related routines क्रम the coda kernel code
   (C) 1996 Peter Braam
   */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>

#समावेश <linux/coda.h>
#समावेश <linux/pagemap.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"

अटल अंतरभूत पूर्णांक coda_fideq(काष्ठा CodaFid *fid1, काष्ठा CodaFid *fid2)
अणु
	वापस स_भेद(fid1, fid2, माप(*fid1)) == 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations coda_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.setattr	= coda_setattr,
पूर्ण;

/* cnode.c */
अटल व्योम coda_fill_inode(काष्ठा inode *inode, काष्ठा coda_vattr *attr)
अणु
        coda_vattr_to_iattr(inode, attr);

        अगर (S_ISREG(inode->i_mode)) अणु
                inode->i_op = &coda_file_inode_operations;
                inode->i_fop = &coda_file_operations;
        पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
                inode->i_op = &coda_dir_inode_operations;
                inode->i_fop = &coda_dir_operations;
        पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_op = &coda_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_data.a_ops = &coda_symlink_aops;
		inode->i_mapping = &inode->i_data;
	पूर्ण अन्यथा
                init_special_inode(inode, inode->i_mode, huge_decode_dev(attr->va_rdev));
पूर्ण

अटल पूर्णांक coda_test_inode(काष्ठा inode *inode, व्योम *data)
अणु
	काष्ठा CodaFid *fid = (काष्ठा CodaFid *)data;
	काष्ठा coda_inode_info *cii = ITOC(inode);
	वापस coda_fideq(&cii->c_fid, fid);
पूर्ण

अटल पूर्णांक coda_set_inode(काष्ठा inode *inode, व्योम *data)
अणु
	काष्ठा CodaFid *fid = (काष्ठा CodaFid *)data;
	काष्ठा coda_inode_info *cii = ITOC(inode);
	cii->c_fid = *fid;
	वापस 0;
पूर्ण

काष्ठा inode * coda_iget(काष्ठा super_block * sb, काष्ठा CodaFid * fid,
			 काष्ठा coda_vattr * attr)
अणु
	काष्ठा inode *inode;
	काष्ठा coda_inode_info *cii;
	अचिन्हित दीर्घ hash = coda_f2i(fid);

	inode = iget5_locked(sb, hash, coda_test_inode, coda_set_inode, fid);

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	अगर (inode->i_state & I_NEW) अणु
		cii = ITOC(inode);
		/* we still need to set i_ino क्रम things like stat(2) */
		inode->i_ino = hash;
		/* inode is locked and unique, no need to grab cii->c_lock */
		cii->c_mapcount = 0;
		unlock_new_inode(inode);
	पूर्ण

	/* always replace the attributes, type might have changed */
	coda_fill_inode(inode, attr);
	वापस inode;
पूर्ण

/* this is effectively coda_iget:
   - get attributes (might be cached)
   - get the inode क्रम the fid using vfs iget
   - link the two up अगर this is needed
   - fill in the attributes
*/
काष्ठा inode *coda_cnode_make(काष्ठा CodaFid *fid, काष्ठा super_block *sb)
अणु
        काष्ठा coda_vattr attr;
	काष्ठा inode *inode;
        पूर्णांक error;
        
	/* We get inode numbers from Venus -- see venus source */
	error = venus_getattr(sb, fid, &attr);
	अगर (error)
		वापस ERR_PTR(error);

	inode = coda_iget(sb, fid, &attr);
	अगर (IS_ERR(inode))
		pr_warn("%s: coda_iget failed\n", __func__);
	वापस inode;
पूर्ण


/* Although we treat Coda file identअगरiers as immutable, there is one
 * special हाल क्रम files created during a disconnection where they may
 * not be globally unique. When an identअगरier collision is detected we
 * first try to flush the cached inode from the kernel and finally
 * resort to renaming/rehashing in-place. Userspace remembers both old
 * and new values of the identअगरier to handle any in-flight upcalls.
 * The real solution is to use globally unique UUIDs as identअगरiers, but
 * retrofitting the existing userspace code क्रम this is non-trivial. */
व्योम coda_replace_fid(काष्ठा inode *inode, काष्ठा CodaFid *oldfid, 
		      काष्ठा CodaFid *newfid)
अणु
	काष्ठा coda_inode_info *cii = ITOC(inode);
	अचिन्हित दीर्घ hash = coda_f2i(newfid);
	
	BUG_ON(!coda_fideq(&cii->c_fid, oldfid));

	/* replace fid and rehash inode */
	/* XXX we probably need to hold some lock here! */
	हटाओ_inode_hash(inode);
	cii->c_fid = *newfid;
	inode->i_ino = hash;
	__insert_inode_hash(inode, hash);
पूर्ण

/* convert a fid to an inode. */
काष्ठा inode *coda_fid_to_inode(काष्ठा CodaFid *fid, काष्ठा super_block *sb) 
अणु
	काष्ठा inode *inode;
	अचिन्हित दीर्घ hash = coda_f2i(fid);

	inode = ilookup5(sb, hash, coda_test_inode, fid);
	अगर ( !inode )
		वापस शून्य;

	/* we should never see newly created inodes because we पूर्णांकentionally
	 * fail in the initialization callback */
	BUG_ON(inode->i_state & I_NEW);

	वापस inode;
पूर्ण

काष्ठा coda_file_info *coda_ftoc(काष्ठा file *file)
अणु
	काष्ठा coda_file_info *cfi = file->निजी_data;

	BUG_ON(!cfi || cfi->cfi_magic != CODA_MAGIC);

	वापस cfi;

पूर्ण

/* the CONTROL inode is made without asking attributes from Venus */
काष्ठा inode *coda_cnode_makectl(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode = new_inode(sb);
	अगर (inode) अणु
		inode->i_ino = CTL_INO;
		inode->i_op = &coda_ioctl_inode_operations;
		inode->i_fop = &coda_ioctl_operations;
		inode->i_mode = 0444;
		वापस inode;
	पूर्ण
	वापस ERR_PTR(-ENOMEM);
पूर्ण

