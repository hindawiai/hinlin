<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 2007 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "ecryptfs_kernel.h"

/**
 * ecryptfs_ग_लिखो_lower
 * @ecryptfs_inode: The eCryptfs inode
 * @data: Data to ग_लिखो
 * @offset: Byte offset in the lower file to which to ग_लिखो the data
 * @size: Number of bytes from @data to ग_लिखो at @offset in the lower
 *        file
 *
 * Write data to the lower file.
 *
 * Returns bytes written on success; less than zero on error
 */
पूर्णांक ecryptfs_ग_लिखो_lower(काष्ठा inode *ecryptfs_inode, अक्षर *data,
			 loff_t offset, माप_प्रकार size)
अणु
	काष्ठा file *lower_file;
	sमाप_प्रकार rc;

	lower_file = ecryptfs_inode_to_निजी(ecryptfs_inode)->lower_file;
	अगर (!lower_file)
		वापस -EIO;
	rc = kernel_ग_लिखो(lower_file, data, size, &offset);
	mark_inode_dirty_sync(ecryptfs_inode);
	वापस rc;
पूर्ण

/**
 * ecryptfs_ग_लिखो_lower_page_segment
 * @ecryptfs_inode: The eCryptfs inode
 * @page_क्रम_lower: The page containing the data to be written to the
 *                  lower file
 * @offset_in_page: The offset in the @page_क्रम_lower from which to
 *                  start writing the data
 * @size: The amount of data from @page_क्रम_lower to ग_लिखो to the
 *        lower file
 *
 * Determines the byte offset in the file क्रम the given page and
 * offset within the page, maps the page, and makes the call to ग_लिखो
 * the contents of @page_क्रम_lower to the lower inode.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक ecryptfs_ग_लिखो_lower_page_segment(काष्ठा inode *ecryptfs_inode,
				      काष्ठा page *page_क्रम_lower,
				      माप_प्रकार offset_in_page, माप_प्रकार size)
अणु
	अक्षर *virt;
	loff_t offset;
	पूर्णांक rc;

	offset = ((((loff_t)page_क्रम_lower->index) << PAGE_SHIFT)
		  + offset_in_page);
	virt = kmap(page_क्रम_lower);
	rc = ecryptfs_ग_लिखो_lower(ecryptfs_inode, virt, offset, size);
	अगर (rc > 0)
		rc = 0;
	kunmap(page_क्रम_lower);
	वापस rc;
पूर्ण

/**
 * ecryptfs_ग_लिखो
 * @ecryptfs_inode: The eCryptfs file पूर्णांकo which to ग_लिखो
 * @data: Virtual address where data to ग_लिखो is located
 * @offset: Offset in the eCryptfs file at which to begin writing the
 *          data from @data
 * @size: The number of bytes to ग_लिखो from @data
 *
 * Write an arbitrary amount of data to an arbitrary location in the
 * eCryptfs inode page cache. This is करोne on a page-by-page, and then
 * by an extent-by-extent, basis; inभागidual extents are encrypted and
 * written to the lower page cache (via VFS ग_लिखोs). This function
 * takes care of all the address translation to locations in the lower
 * fileप्रणाली; it also handles truncate events, writing out zeros
 * where necessary.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक ecryptfs_ग_लिखो(काष्ठा inode *ecryptfs_inode, अक्षर *data, loff_t offset,
		   माप_प्रकार size)
अणु
	काष्ठा page *ecryptfs_page;
	काष्ठा ecryptfs_crypt_stat *crypt_stat;
	अक्षर *ecryptfs_page_virt;
	loff_t ecryptfs_file_size = i_size_पढ़ो(ecryptfs_inode);
	loff_t data_offset = 0;
	loff_t pos;
	पूर्णांक rc = 0;

	crypt_stat = &ecryptfs_inode_to_निजी(ecryptfs_inode)->crypt_stat;
	/*
	 * अगर we are writing beyond current size, then start pos
	 * at the current size - we'll fill in zeros from there.
	 */
	अगर (offset > ecryptfs_file_size)
		pos = ecryptfs_file_size;
	अन्यथा
		pos = offset;
	जबतक (pos < (offset + size)) अणु
		pgoff_t ecryptfs_page_idx = (pos >> PAGE_SHIFT);
		माप_प्रकार start_offset_in_page = (pos & ~PAGE_MASK);
		माप_प्रकार num_bytes = (PAGE_SIZE - start_offset_in_page);
		loff_t total_reमुख्यing_bytes = ((offset + size) - pos);

		अगर (fatal_संकेत_pending(current)) अणु
			rc = -EINTR;
			अवरोध;
		पूर्ण

		अगर (num_bytes > total_reमुख्यing_bytes)
			num_bytes = total_reमुख्यing_bytes;
		अगर (pos < offset) अणु
			/* reमुख्यing zeros to ग_लिखो, up to destination offset */
			loff_t total_reमुख्यing_zeros = (offset - pos);

			अगर (num_bytes > total_reमुख्यing_zeros)
				num_bytes = total_reमुख्यing_zeros;
		पूर्ण
		ecryptfs_page = ecryptfs_get_locked_page(ecryptfs_inode,
							 ecryptfs_page_idx);
		अगर (IS_ERR(ecryptfs_page)) अणु
			rc = PTR_ERR(ecryptfs_page);
			prपूर्णांकk(KERN_ERR "%s: Error getting page at "
			       "index [%ld] from eCryptfs inode "
			       "mapping; rc = [%d]\n", __func__,
			       ecryptfs_page_idx, rc);
			जाओ out;
		पूर्ण
		ecryptfs_page_virt = kmap_atomic(ecryptfs_page);

		/*
		 * pos: where we're now writing, offset: where the request was
		 * If current pos is beक्रमe request, we are filling zeros
		 * If we are at or beyond request, we are writing the *data*
		 * If we're in a fresh page beyond eof, zero it in either हाल
		 */
		अगर (pos < offset || !start_offset_in_page) अणु
			/* We are extending past the previous end of the file.
			 * Fill in zero values to the end of the page */
			स_रखो(((अक्षर *)ecryptfs_page_virt
				+ start_offset_in_page), 0,
				PAGE_SIZE - start_offset_in_page);
		पूर्ण

		/* pos >= offset, we are now writing the data request */
		अगर (pos >= offset) अणु
			स_नकल(((अक्षर *)ecryptfs_page_virt
				+ start_offset_in_page),
			       (data + data_offset), num_bytes);
			data_offset += num_bytes;
		पूर्ण
		kunmap_atomic(ecryptfs_page_virt);
		flush_dcache_page(ecryptfs_page);
		SetPageUptodate(ecryptfs_page);
		unlock_page(ecryptfs_page);
		अगर (crypt_stat->flags & ECRYPTFS_ENCRYPTED)
			rc = ecryptfs_encrypt_page(ecryptfs_page);
		अन्यथा
			rc = ecryptfs_ग_लिखो_lower_page_segment(ecryptfs_inode,
						ecryptfs_page,
						start_offset_in_page,
						data_offset);
		put_page(ecryptfs_page);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: Error encrypting "
			       "page; rc = [%d]\n", __func__, rc);
			जाओ out;
		पूर्ण
		pos += num_bytes;
	पूर्ण
	अगर (pos > ecryptfs_file_size) अणु
		i_size_ग_लिखो(ecryptfs_inode, pos);
		अगर (crypt_stat->flags & ECRYPTFS_ENCRYPTED) अणु
			पूर्णांक rc2;

			rc2 = ecryptfs_ग_लिखो_inode_माप_प्रकारo_metadata(
								ecryptfs_inode);
			अगर (rc2) अणु
				prपूर्णांकk(KERN_ERR	"Problem with "
				       "ecryptfs_write_inode_size_to_metadata; "
				       "rc = [%d]\n", rc2);
				अगर (!rc)
					rc = rc2;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस rc;
पूर्ण

/**
 * ecryptfs_पढ़ो_lower
 * @data: The पढ़ो data is stored here by this function
 * @offset: Byte offset in the lower file from which to पढ़ो the data
 * @size: Number of bytes to पढ़ो from @offset of the lower file and
 *        store पूर्णांकo @data
 * @ecryptfs_inode: The eCryptfs inode
 *
 * Read @size bytes of data at byte offset @offset from the lower
 * inode पूर्णांकo memory location @data.
 *
 * Returns bytes पढ़ो on success; 0 on खातापूर्ण; less than zero on error
 */
पूर्णांक ecryptfs_पढ़ो_lower(अक्षर *data, loff_t offset, माप_प्रकार size,
			काष्ठा inode *ecryptfs_inode)
अणु
	काष्ठा file *lower_file;
	lower_file = ecryptfs_inode_to_निजी(ecryptfs_inode)->lower_file;
	अगर (!lower_file)
		वापस -EIO;
	वापस kernel_पढ़ो(lower_file, data, size, &offset);
पूर्ण

/**
 * ecryptfs_पढ़ो_lower_page_segment
 * @page_क्रम_ecryptfs: The page पूर्णांकo which data क्रम eCryptfs will be
 *                     written
 * @page_index: Page index in @page_क्रम_ecryptfs from which to start
 *		writing
 * @offset_in_page: Offset in @page_क्रम_ecryptfs from which to start
 *                  writing
 * @size: The number of bytes to ग_लिखो पूर्णांकo @page_क्रम_ecryptfs
 * @ecryptfs_inode: The eCryptfs inode
 *
 * Determines the byte offset in the file क्रम the given page and
 * offset within the page, maps the page, and makes the call to पढ़ो
 * the contents of @page_क्रम_ecryptfs from the lower inode.
 *
 * Returns zero on success; non-zero otherwise
 */
पूर्णांक ecryptfs_पढ़ो_lower_page_segment(काष्ठा page *page_क्रम_ecryptfs,
				     pgoff_t page_index,
				     माप_प्रकार offset_in_page, माप_प्रकार size,
				     काष्ठा inode *ecryptfs_inode)
अणु
	अक्षर *virt;
	loff_t offset;
	पूर्णांक rc;

	offset = ((((loff_t)page_index) << PAGE_SHIFT) + offset_in_page);
	virt = kmap(page_क्रम_ecryptfs);
	rc = ecryptfs_पढ़ो_lower(virt, offset, size, ecryptfs_inode);
	अगर (rc > 0)
		rc = 0;
	kunmap(page_क्रम_ecryptfs);
	flush_dcache_page(page_क्रम_ecryptfs);
	वापस rc;
पूर्ण
