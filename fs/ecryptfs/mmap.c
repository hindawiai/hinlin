<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 * This is where eCryptfs coordinates the symmetric encryption and
 * decryption of the file data as it passes between the lower
 * encrypted file and the upper decrypted file.
 *
 * Copyright (C) 1997-2003 Erez Zaकरोk
 * Copyright (C) 2001-2003 Stony Brook University
 * Copyright (C) 2004-2007 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/mount.h>
#समावेश <linux/file.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/xattr.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "ecryptfs_kernel.h"

/*
 * ecryptfs_get_locked_page
 *
 * Get one page from cache or lower f/s, वापस error otherwise.
 *
 * Returns locked and up-to-date page (अगर ok), with increased
 * refcnt.
 */
काष्ठा page *ecryptfs_get_locked_page(काष्ठा inode *inode, loff_t index)
अणु
	काष्ठा page *page = पढ़ो_mapping_page(inode->i_mapping, index, शून्य);
	अगर (!IS_ERR(page))
		lock_page(page);
	वापस page;
पूर्ण

/**
 * ecryptfs_ग_लिखोpage
 * @page: Page that is locked beक्रमe this call is made
 * @wbc: Write-back control काष्ठाure
 *
 * Returns zero on success; non-zero otherwise
 *
 * This is where we encrypt the data and pass the encrypted data to
 * the lower fileप्रणाली.  In OpenPGP-compatible mode, we operate on
 * entire underlying packets.
 */
अटल पूर्णांक ecryptfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक rc;

	rc = ecryptfs_encrypt_page(page);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Error encrypting "
				"page (upper index [0x%.16lx])\n", page->index);
		ClearPageUptodate(page);
		जाओ out;
	पूर्ण
	SetPageUptodate(page);
out:
	unlock_page(page);
	वापस rc;
पूर्ण

अटल व्योम strip_xattr_flag(अक्षर *page_virt,
			     काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	अगर (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR) अणु
		माप_प्रकार written;

		crypt_stat->flags &= ~ECRYPTFS_METADATA_IN_XATTR;
		ecryptfs_ग_लिखो_crypt_stat_flags(page_virt, crypt_stat,
						&written);
		crypt_stat->flags |= ECRYPTFS_METADATA_IN_XATTR;
	पूर्ण
पूर्ण

/*
 *   Header Extent:
 *     Octets 0-7:        Unencrypted file size (big-endian)
 *     Octets 8-15:       eCryptfs special marker
 *     Octets 16-19:      Flags
 *      Octet 16:         File क्रमmat version number (between 0 and 255)
 *      Octets 17-18:     Reserved
 *      Octet 19:         Bit 1 (lsb): Reserved
 *                        Bit 2: Encrypted?
 *                        Bits 3-8: Reserved
 *     Octets 20-23:      Header extent size (big-endian)
 *     Octets 24-25:      Number of header extents at front of file
 *                        (big-endian)
 *     Octet  26:         Begin RFC 2440 authentication token packet set
 */

/**
 * ecryptfs_copy_up_encrypted_with_header
 * @page: Sort of a ``भव'' representation of the encrypted lower
 *        file. The actual lower file करोes not have the metadata in
 *        the header. This is locked.
 * @crypt_stat: The eCryptfs inode's cryptographic context
 *
 * The ``view'' is the version of the file that userspace winds up
 * seeing, with the header inक्रमmation inserted.
 */
अटल पूर्णांक
ecryptfs_copy_up_encrypted_with_header(काष्ठा page *page,
				       काष्ठा ecryptfs_crypt_stat *crypt_stat)
अणु
	loff_t extent_num_in_page = 0;
	loff_t num_extents_per_page = (PAGE_SIZE
				       / crypt_stat->extent_size);
	पूर्णांक rc = 0;

	जबतक (extent_num_in_page < num_extents_per_page) अणु
		loff_t view_extent_num = ((((loff_t)page->index)
					   * num_extents_per_page)
					  + extent_num_in_page);
		माप_प्रकार num_header_extents_at_front =
			(crypt_stat->metadata_size / crypt_stat->extent_size);

		अगर (view_extent_num < num_header_extents_at_front) अणु
			/* This is a header extent */
			अक्षर *page_virt;

			page_virt = kmap_atomic(page);
			स_रखो(page_virt, 0, PAGE_SIZE);
			/* TODO: Support more than one header extent */
			अगर (view_extent_num == 0) अणु
				माप_प्रकार written;

				rc = ecryptfs_पढ़ो_xattr_region(
					page_virt, page->mapping->host);
				strip_xattr_flag(page_virt + 16, crypt_stat);
				ecryptfs_ग_लिखो_header_metadata(page_virt + 20,
							       crypt_stat,
							       &written);
			पूर्ण
			kunmap_atomic(page_virt);
			flush_dcache_page(page);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR "%s: Error reading xattr "
				       "region; rc = [%d]\n", __func__, rc);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* This is an encrypted data extent */
			loff_t lower_offset =
				((view_extent_num * crypt_stat->extent_size)
				 - crypt_stat->metadata_size);

			rc = ecryptfs_पढ़ो_lower_page_segment(
				page, (lower_offset >> PAGE_SHIFT),
				(lower_offset & ~PAGE_MASK),
				crypt_stat->extent_size, page->mapping->host);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR "%s: Error attempting to read "
				       "extent at offset [%lld] in the lower "
				       "file; rc = [%d]\n", __func__,
				       lower_offset, rc);
				जाओ out;
			पूर्ण
		पूर्ण
		extent_num_in_page++;
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_पढ़ोpage
 * @file: An eCryptfs file
 * @page: Page from eCryptfs inode mapping पूर्णांकo which to stick the पढ़ो data
 *
 * Read in a page, decrypting अगर necessary.
 *
 * Returns zero on success; non-zero on error.
 */
अटल पूर्णांक ecryptfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा ecryptfs_crypt_stat *crypt_stat =
		&ecryptfs_inode_to_निजी(page->mapping->host)->crypt_stat;
	पूर्णांक rc = 0;

	अगर (!crypt_stat || !(crypt_stat->flags & ECRYPTFS_ENCRYPTED)) अणु
		rc = ecryptfs_पढ़ो_lower_page_segment(page, page->index, 0,
						      PAGE_SIZE,
						      page->mapping->host);
	पूर्ण अन्यथा अगर (crypt_stat->flags & ECRYPTFS_VIEW_AS_ENCRYPTED) अणु
		अगर (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR) अणु
			rc = ecryptfs_copy_up_encrypted_with_header(page,
								    crypt_stat);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR "%s: Error attempting to copy "
				       "the encrypted content from the lower "
				       "file whilst inserting the metadata "
				       "from the xattr into the header; rc = "
				       "[%d]\n", __func__, rc);
				जाओ out;
			पूर्ण

		पूर्ण अन्यथा अणु
			rc = ecryptfs_पढ़ो_lower_page_segment(
				page, page->index, 0, PAGE_SIZE,
				page->mapping->host);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR "Error reading page; rc = "
				       "[%d]\n", rc);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = ecryptfs_decrypt_page(page);
		अगर (rc) अणु
			ecryptfs_prपूर्णांकk(KERN_ERR, "Error decrypting page; "
					"rc = [%d]\n", rc);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (rc)
		ClearPageUptodate(page);
	अन्यथा
		SetPageUptodate(page);
	ecryptfs_prपूर्णांकk(KERN_DEBUG, "Unlocking page with index = [0x%.16lx]\n",
			page->index);
	unlock_page(page);
	वापस rc;
पूर्ण

/*
 * Called with lower inode mutex held.
 */
अटल पूर्णांक fill_zeros_to_end_of_page(काष्ठा page *page, अचिन्हित पूर्णांक to)
अणु
	काष्ठा inode *inode = page->mapping->host;
	पूर्णांक end_byte_in_page;

	अगर ((i_size_पढ़ो(inode) / PAGE_SIZE) != page->index)
		जाओ out;
	end_byte_in_page = i_size_पढ़ो(inode) % PAGE_SIZE;
	अगर (to > end_byte_in_page)
		end_byte_in_page = to;
	zero_user_segment(page, end_byte_in_page, PAGE_SIZE);
out:
	वापस 0;
पूर्ण

/**
 * ecryptfs_ग_लिखो_begin
 * @file: The eCryptfs file
 * @mapping: The eCryptfs object
 * @pos: The file offset at which to start writing
 * @len: Length of the ग_लिखो
 * @flags: Various flags
 * @pagep: Poपूर्णांकer to वापस the page
 * @fsdata: Poपूर्णांकer to वापस fs data (unused)
 *
 * This function must zero any hole we create
 *
 * Returns zero on success; non-zero otherwise
 */
अटल पूर्णांक ecryptfs_ग_लिखो_begin(काष्ठा file *file,
			काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	pgoff_t index = pos >> PAGE_SHIFT;
	काष्ठा page *page;
	loff_t prev_page_end_size;
	पूर्णांक rc = 0;

	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;
	*pagep = page;

	prev_page_end_size = ((loff_t)index << PAGE_SHIFT);
	अगर (!PageUptodate(page)) अणु
		काष्ठा ecryptfs_crypt_stat *crypt_stat =
			&ecryptfs_inode_to_निजी(mapping->host)->crypt_stat;

		अगर (!(crypt_stat->flags & ECRYPTFS_ENCRYPTED)) अणु
			rc = ecryptfs_पढ़ो_lower_page_segment(
				page, index, 0, PAGE_SIZE, mapping->host);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR "%s: Error attempting to read "
				       "lower page segment; rc = [%d]\n",
				       __func__, rc);
				ClearPageUptodate(page);
				जाओ out;
			पूर्ण अन्यथा
				SetPageUptodate(page);
		पूर्ण अन्यथा अगर (crypt_stat->flags & ECRYPTFS_VIEW_AS_ENCRYPTED) अणु
			अगर (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR) अणु
				rc = ecryptfs_copy_up_encrypted_with_header(
					page, crypt_stat);
				अगर (rc) अणु
					prपूर्णांकk(KERN_ERR "%s: Error attempting "
					       "to copy the encrypted content "
					       "from the lower file whilst "
					       "inserting the metadata from "
					       "the xattr into the header; rc "
					       "= [%d]\n", __func__, rc);
					ClearPageUptodate(page);
					जाओ out;
				पूर्ण
				SetPageUptodate(page);
			पूर्ण अन्यथा अणु
				rc = ecryptfs_पढ़ो_lower_page_segment(
					page, index, 0, PAGE_SIZE,
					mapping->host);
				अगर (rc) अणु
					prपूर्णांकk(KERN_ERR "%s: Error reading "
					       "page; rc = [%d]\n",
					       __func__, rc);
					ClearPageUptodate(page);
					जाओ out;
				पूर्ण
				SetPageUptodate(page);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (prev_page_end_size
			    >= i_size_पढ़ो(page->mapping->host)) अणु
				zero_user(page, 0, PAGE_SIZE);
				SetPageUptodate(page);
			पूर्ण अन्यथा अगर (len < PAGE_SIZE) अणु
				rc = ecryptfs_decrypt_page(page);
				अगर (rc) अणु
					prपूर्णांकk(KERN_ERR "%s: Error decrypting "
					       "page at index [%ld]; "
					       "rc = [%d]\n",
					       __func__, page->index, rc);
					ClearPageUptodate(page);
					जाओ out;
				पूर्ण
				SetPageUptodate(page);
			पूर्ण
		पूर्ण
	पूर्ण
	/* If creating a page or more of holes, zero them out via truncate.
	 * Note, this will increase i_size. */
	अगर (index != 0) अणु
		अगर (prev_page_end_size > i_size_पढ़ो(page->mapping->host)) अणु
			rc = ecryptfs_truncate(file->f_path.dentry,
					       prev_page_end_size);
			अगर (rc) अणु
				prपूर्णांकk(KERN_ERR "%s: Error on attempt to "
				       "truncate to (higher) offset [%lld];"
				       " rc = [%d]\n", __func__,
				       prev_page_end_size, rc);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Writing to a new page, and creating a small hole from start
	 * of page?  Zero it out. */
	अगर ((i_size_पढ़ो(mapping->host) == prev_page_end_size)
	    && (pos != 0))
		zero_user(page, 0, PAGE_SIZE);
out:
	अगर (unlikely(rc)) अणु
		unlock_page(page);
		put_page(page);
		*pagep = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * ecryptfs_ग_लिखो_inode_माप_प्रकारo_header
 *
 * Writes the lower file size to the first 8 bytes of the header.
 *
 * Returns zero on success; non-zero on error.
 */
अटल पूर्णांक ecryptfs_ग_लिखो_inode_माप_प्रकारo_header(काष्ठा inode *ecryptfs_inode)
अणु
	अक्षर *file_size_virt;
	पूर्णांक rc;

	file_size_virt = kदो_स्मृति(माप(u64), GFP_KERNEL);
	अगर (!file_size_virt) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	put_unaligned_be64(i_size_पढ़ो(ecryptfs_inode), file_size_virt);
	rc = ecryptfs_ग_लिखो_lower(ecryptfs_inode, file_size_virt, 0,
				  माप(u64));
	kमुक्त(file_size_virt);
	अगर (rc < 0)
		prपूर्णांकk(KERN_ERR "%s: Error writing file size to header; "
		       "rc = [%d]\n", __func__, rc);
	अन्यथा
		rc = 0;
out:
	वापस rc;
पूर्ण

काष्ठा kmem_cache *ecryptfs_xattr_cache;

अटल पूर्णांक ecryptfs_ग_लिखो_inode_माप_प्रकारo_xattr(काष्ठा inode *ecryptfs_inode)
अणु
	sमाप_प्रकार size;
	व्योम *xattr_virt;
	काष्ठा dentry *lower_dentry =
		ecryptfs_inode_to_निजी(ecryptfs_inode)->lower_file->f_path.dentry;
	काष्ठा inode *lower_inode = d_inode(lower_dentry);
	पूर्णांक rc;

	अगर (!(lower_inode->i_opflags & IOP_XATTR)) अणु
		prपूर्णांकk(KERN_WARNING
		       "No support for setting xattr in lower filesystem\n");
		rc = -ENOSYS;
		जाओ out;
	पूर्ण
	xattr_virt = kmem_cache_alloc(ecryptfs_xattr_cache, GFP_KERNEL);
	अगर (!xattr_virt) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	inode_lock(lower_inode);
	size = __vfs_getxattr(lower_dentry, lower_inode, ECRYPTFS_XATTR_NAME,
			      xattr_virt, PAGE_SIZE);
	अगर (size < 0)
		size = 8;
	put_unaligned_be64(i_size_पढ़ो(ecryptfs_inode), xattr_virt);
	rc = __vfs_setxattr(&init_user_ns, lower_dentry, lower_inode,
			    ECRYPTFS_XATTR_NAME, xattr_virt, size, 0);
	inode_unlock(lower_inode);
	अगर (rc)
		prपूर्णांकk(KERN_ERR "Error whilst attempting to write inode size "
		       "to lower file xattr; rc = [%d]\n", rc);
	kmem_cache_मुक्त(ecryptfs_xattr_cache, xattr_virt);
out:
	वापस rc;
पूर्ण

पूर्णांक ecryptfs_ग_लिखो_inode_माप_प्रकारo_metadata(काष्ठा inode *ecryptfs_inode)
अणु
	काष्ठा ecryptfs_crypt_stat *crypt_stat;

	crypt_stat = &ecryptfs_inode_to_निजी(ecryptfs_inode)->crypt_stat;
	BUG_ON(!(crypt_stat->flags & ECRYPTFS_ENCRYPTED));
	अगर (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR)
		वापस ecryptfs_ग_लिखो_inode_माप_प्रकारo_xattr(ecryptfs_inode);
	अन्यथा
		वापस ecryptfs_ग_लिखो_inode_माप_प्रकारo_header(ecryptfs_inode);
पूर्ण

/**
 * ecryptfs_ग_लिखो_end
 * @file: The eCryptfs file object
 * @mapping: The eCryptfs object
 * @pos: The file position
 * @len: The length of the data (unused)
 * @copied: The amount of data copied
 * @page: The eCryptfs page
 * @fsdata: The fsdata (unused)
 */
अटल पूर्णांक ecryptfs_ग_लिखो_end(काष्ठा file *file,
			काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	pgoff_t index = pos >> PAGE_SHIFT;
	अचिन्हित from = pos & (PAGE_SIZE - 1);
	अचिन्हित to = from + copied;
	काष्ठा inode *ecryptfs_inode = mapping->host;
	काष्ठा ecryptfs_crypt_stat *crypt_stat =
		&ecryptfs_inode_to_निजी(ecryptfs_inode)->crypt_stat;
	पूर्णांक rc;

	ecryptfs_prपूर्णांकk(KERN_DEBUG, "Calling fill_zeros_to_end_of_page"
			"(page w/ index = [0x%.16lx], to = [%d])\n", index, to);
	अगर (!(crypt_stat->flags & ECRYPTFS_ENCRYPTED)) अणु
		rc = ecryptfs_ग_लिखो_lower_page_segment(ecryptfs_inode, page, 0,
						       to);
		अगर (!rc) अणु
			rc = copied;
			fsstack_copy_inode_size(ecryptfs_inode,
				ecryptfs_inode_to_lower(ecryptfs_inode));
		पूर्ण
		जाओ out;
	पूर्ण
	अगर (!PageUptodate(page)) अणु
		अगर (copied < PAGE_SIZE) अणु
			rc = 0;
			जाओ out;
		पूर्ण
		SetPageUptodate(page);
	पूर्ण
	/* Fills in zeros अगर 'to' goes beyond inode size */
	rc = fill_zeros_to_end_of_page(page, to);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Error attempting to fill "
			"zeros in page with index = [0x%.16lx]\n", index);
		जाओ out;
	पूर्ण
	rc = ecryptfs_encrypt_page(page);
	अगर (rc) अणु
		ecryptfs_prपूर्णांकk(KERN_WARNING, "Error encrypting page (upper "
				"index [0x%.16lx])\n", index);
		जाओ out;
	पूर्ण
	अगर (pos + copied > i_size_पढ़ो(ecryptfs_inode)) अणु
		i_size_ग_लिखो(ecryptfs_inode, pos + copied);
		ecryptfs_prपूर्णांकk(KERN_DEBUG, "Expanded file size to "
			"[0x%.16llx]\n",
			(अचिन्हित दीर्घ दीर्घ)i_size_पढ़ो(ecryptfs_inode));
	पूर्ण
	rc = ecryptfs_ग_लिखो_inode_माप_प्रकारo_metadata(ecryptfs_inode);
	अगर (rc)
		prपूर्णांकk(KERN_ERR "Error writing inode size to metadata; "
		       "rc = [%d]\n", rc);
	अन्यथा
		rc = copied;
out:
	unlock_page(page);
	put_page(page);
	वापस rc;
पूर्ण

अटल sector_t ecryptfs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	काष्ठा inode *lower_inode = ecryptfs_inode_to_lower(mapping->host);
	पूर्णांक ret = bmap(lower_inode, &block);

	अगर (ret)
		वापस 0;
	वापस block;
पूर्ण

स्थिर काष्ठा address_space_operations ecryptfs_aops = अणु
	.ग_लिखोpage = ecryptfs_ग_लिखोpage,
	.पढ़ोpage = ecryptfs_पढ़ोpage,
	.ग_लिखो_begin = ecryptfs_ग_लिखो_begin,
	.ग_लिखो_end = ecryptfs_ग_लिखो_end,
	.bmap = ecryptfs_bmap,
पूर्ण;
