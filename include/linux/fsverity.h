<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs-verity: पढ़ो-only file-based authenticity protection
 *
 * This header declares the पूर्णांकerface between the fs/verity/ support layer and
 * fileप्रणालीs that support fs-verity.
 *
 * Copyright 2019 Google LLC
 */

#अगर_अघोषित _LINUX_FSVERITY_H
#घोषणा _LINUX_FSVERITY_H

#समावेश <linux/fs.h>
#समावेश <uapi/linux/fsverity.h>

/* Verity operations क्रम fileप्रणालीs */
काष्ठा fsverity_operations अणु

	/**
	 * Begin enabling verity on the given file.
	 *
	 * @filp: a पढ़ोonly file descriptor क्रम the file
	 *
	 * The fileप्रणाली must करो any needed fileप्रणाली-specअगरic preparations
	 * क्रम enabling verity, e.g. evicting अंतरभूत data.  It also must वापस
	 * -EBUSY अगर verity is alपढ़ोy being enabled on the given file.
	 *
	 * i_rwsem is held क्रम ग_लिखो.
	 *
	 * Return: 0 on success, -त्रुटि_सं on failure
	 */
	पूर्णांक (*begin_enable_verity)(काष्ठा file *filp);

	/**
	 * End enabling verity on the given file.
	 *
	 * @filp: a पढ़ोonly file descriptor क्रम the file
	 * @desc: the verity descriptor to ग_लिखो, or शून्य on failure
	 * @desc_size: size of verity descriptor, or 0 on failure
	 * @merkle_tree_size: total bytes the Merkle tree took up
	 *
	 * If desc == शून्य, then enabling verity failed and the fileप्रणाली only
	 * must करो any necessary cleanups.  Else, it must also store the given
	 * verity descriptor to a fs-specअगरic location associated with the inode
	 * and करो any fs-specअगरic actions needed to mark the inode as a verity
	 * inode, e.g. setting a bit in the on-disk inode.  The fileप्रणाली is
	 * also responsible क्रम setting the S_VERITY flag in the VFS inode.
	 *
	 * i_rwsem is held क्रम ग_लिखो, but it may have been dropped between
	 * ->begin_enable_verity() and ->end_enable_verity().
	 *
	 * Return: 0 on success, -त्रुटि_सं on failure
	 */
	पूर्णांक (*end_enable_verity)(काष्ठा file *filp, स्थिर व्योम *desc,
				 माप_प्रकार desc_size, u64 merkle_tree_size);

	/**
	 * Get the verity descriptor of the given inode.
	 *
	 * @inode: an inode with the S_VERITY flag set
	 * @buf: buffer in which to place the verity descriptor
	 * @bufsize: size of @buf, or 0 to retrieve the size only
	 *
	 * If bufsize == 0, then the size of the verity descriptor is वापसed.
	 * Otherwise the verity descriptor is written to 'buf' and its actual
	 * size is वापसed; -दुस्फल is वापसed अगर it's too large.  This may be
	 * called by multiple processes concurrently on the same inode.
	 *
	 * Return: the size on success, -त्रुटि_सं on failure
	 */
	पूर्णांक (*get_verity_descriptor)(काष्ठा inode *inode, व्योम *buf,
				     माप_प्रकार bufsize);

	/**
	 * Read a Merkle tree page of the given inode.
	 *
	 * @inode: the inode
	 * @index: 0-based index of the page within the Merkle tree
	 * @num_ra_pages: The number of Merkle tree pages that should be
	 *		  prefetched starting at @index अगर the page at @index
	 *		  isn't alपढ़ोy cached.  Implementations may ignore this
	 *		  argument; it's only a perक्रमmance optimization.
	 *
	 * This can be called at any समय on an खोलो verity file, as well as
	 * between ->begin_enable_verity() and ->end_enable_verity().  It may be
	 * called by multiple processes concurrently, even with the same page.
	 *
	 * Note that this must retrieve a *page*, not necessarily a *block*.
	 *
	 * Return: the page on success, ERR_PTR() on failure
	 */
	काष्ठा page *(*पढ़ो_merkle_tree_page)(काष्ठा inode *inode,
					      pgoff_t index,
					      अचिन्हित दीर्घ num_ra_pages);

	/**
	 * Write a Merkle tree block to the given inode.
	 *
	 * @inode: the inode क्रम which the Merkle tree is being built
	 * @buf: block to ग_लिखो
	 * @index: 0-based index of the block within the Merkle tree
	 * @log_blocksize: log base 2 of the Merkle tree block size
	 *
	 * This is only called between ->begin_enable_verity() and
	 * ->end_enable_verity().
	 *
	 * Return: 0 on success, -त्रुटि_सं on failure
	 */
	पूर्णांक (*ग_लिखो_merkle_tree_block)(काष्ठा inode *inode, स्थिर व्योम *buf,
				       u64 index, पूर्णांक log_blocksize);
पूर्ण;

#अगर_घोषित CONFIG_FS_VERITY

अटल अंतरभूत काष्ठा fsverity_info *fsverity_get_info(स्थिर काष्ठा inode *inode)
अणु
	/*
	 * Pairs with the cmpxchg_release() in fsverity_set_info().
	 * I.e., another task may publish ->i_verity_info concurrently,
	 * executing a RELEASE barrier.  We need to use smp_load_acquire() here
	 * to safely ACQUIRE the memory the other task published.
	 */
	वापस smp_load_acquire(&inode->i_verity_info);
पूर्ण

/* enable.c */

पूर्णांक fsverity_ioctl_enable(काष्ठा file *filp, स्थिर व्योम __user *arg);

/* measure.c */

पूर्णांक fsverity_ioctl_measure(काष्ठा file *filp, व्योम __user *arg);

/* खोलो.c */

पूर्णांक fsverity_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp);
पूर्णांक fsverity_prepare_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr);
व्योम fsverity_cleanup_inode(काष्ठा inode *inode);

/* पढ़ो_metadata.c */

पूर्णांक fsverity_ioctl_पढ़ो_metadata(काष्ठा file *filp, स्थिर व्योम __user *uarg);

/* verअगरy.c */

bool fsverity_verअगरy_page(काष्ठा page *page);
व्योम fsverity_verअगरy_bio(काष्ठा bio *bio);
व्योम fsverity_enqueue_verअगरy_work(काष्ठा work_काष्ठा *work);

#अन्यथा /* !CONFIG_FS_VERITY */

अटल अंतरभूत काष्ठा fsverity_info *fsverity_get_info(स्थिर काष्ठा inode *inode)
अणु
	वापस शून्य;
पूर्ण

/* enable.c */

अटल अंतरभूत पूर्णांक fsverity_ioctl_enable(काष्ठा file *filp,
					स्थिर व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/* measure.c */

अटल अंतरभूत पूर्णांक fsverity_ioctl_measure(काष्ठा file *filp, व्योम __user *arg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/* खोलो.c */

अटल अंतरभूत पूर्णांक fsverity_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस IS_VERITY(inode) ? -EOPNOTSUPP : 0;
पूर्ण

अटल अंतरभूत पूर्णांक fsverity_prepare_setattr(काष्ठा dentry *dentry,
					   काष्ठा iattr *attr)
अणु
	वापस IS_VERITY(d_inode(dentry)) ? -EOPNOTSUPP : 0;
पूर्ण

अटल अंतरभूत व्योम fsverity_cleanup_inode(काष्ठा inode *inode)
अणु
पूर्ण

/* पढ़ो_metadata.c */

अटल अंतरभूत पूर्णांक fsverity_ioctl_पढ़ो_metadata(काष्ठा file *filp,
					       स्थिर व्योम __user *uarg)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

/* verअगरy.c */

अटल अंतरभूत bool fsverity_verअगरy_page(काष्ठा page *page)
अणु
	WARN_ON(1);
	वापस false;
पूर्ण

अटल अंतरभूत व्योम fsverity_verअगरy_bio(काष्ठा bio *bio)
अणु
	WARN_ON(1);
पूर्ण

अटल अंतरभूत व्योम fsverity_enqueue_verअगरy_work(काष्ठा work_काष्ठा *work)
अणु
	WARN_ON(1);
पूर्ण

#पूर्ण_अगर	/* !CONFIG_FS_VERITY */

/**
 * fsverity_active() - करो पढ़ोs from the inode need to go through fs-verity?
 * @inode: inode to check
 *
 * This checks whether ->i_verity_info has been set.
 *
 * Fileप्रणालीs call this from ->पढ़ोpages() to check whether the pages need to
 * be verअगरied or not.  Don't use IS_VERITY() for this purpose; it's subject to
 * a race condition where the file is being पढ़ो concurrently with
 * FS_IOC_ENABLE_VERITY completing.  (S_VERITY is set beक्रमe ->i_verity_info.)
 *
 * Return: true अगर पढ़ोs need to go through fs-verity, otherwise false
 */
अटल अंतरभूत bool fsverity_active(स्थिर काष्ठा inode *inode)
अणु
	वापस fsverity_get_info(inode) != शून्य;
पूर्ण

#पूर्ण_अगर	/* _LINUX_FSVERITY_H */
