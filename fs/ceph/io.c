<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Trond Myklebust
 * Copyright (c) 2019 Jeff Layton
 *
 * I/O and data path helper functionality.
 *
 * Heavily borrowed from equivalent code in fs/nfs/io.c
 */

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/fs.h>

#समावेश "super.h"
#समावेश "io.h"

/* Call with exclusively locked inode->i_rwsem */
अटल व्योम ceph_block_o_direct(काष्ठा ceph_inode_info *ci, काष्ठा inode *inode)
अणु
	lockdep_निश्चित_held_ग_लिखो(&inode->i_rwsem);

	अगर (READ_ONCE(ci->i_ceph_flags) & CEPH_I_OसूचीECT) अणु
		spin_lock(&ci->i_ceph_lock);
		ci->i_ceph_flags &= ~CEPH_I_OसूचीECT;
		spin_unlock(&ci->i_ceph_lock);
		inode_dio_रुको(inode);
	पूर्ण
पूर्ण

/**
 * ceph_start_io_पढ़ो - declare the file is being used क्रम buffered पढ़ोs
 * @inode: file inode
 *
 * Declare that a buffered पढ़ो operation is about to start, and ensure
 * that we block all direct I/O.
 * On निकास, the function ensures that the CEPH_I_OसूचीECT flag is unset,
 * and holds a shared lock on inode->i_rwsem to ensure that the flag
 * cannot be changed.
 * In practice, this means that buffered पढ़ो operations are allowed to
 * execute in parallel, thanks to the shared lock, whereas direct I/O
 * operations need to रुको to grab an exclusive lock in order to set
 * CEPH_I_OसूचीECT.
 * Note that buffered ग_लिखोs and truncates both take a ग_लिखो lock on
 * inode->i_rwsem, meaning that those are serialised w.r.t. the पढ़ोs.
 */
व्योम
ceph_start_io_पढ़ो(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);

	/* Be an optimist! */
	करोwn_पढ़ो(&inode->i_rwsem);
	अगर (!(READ_ONCE(ci->i_ceph_flags) & CEPH_I_OसूचीECT))
		वापस;
	up_पढ़ो(&inode->i_rwsem);
	/* Slow path.... */
	करोwn_ग_लिखो(&inode->i_rwsem);
	ceph_block_o_direct(ci, inode);
	करोwngrade_ग_लिखो(&inode->i_rwsem);
पूर्ण

/**
 * ceph_end_io_पढ़ो - declare that the buffered पढ़ो operation is करोne
 * @inode: file inode
 *
 * Declare that a buffered पढ़ो operation is करोne, and release the shared
 * lock on inode->i_rwsem.
 */
व्योम
ceph_end_io_पढ़ो(काष्ठा inode *inode)
अणु
	up_पढ़ो(&inode->i_rwsem);
पूर्ण

/**
 * ceph_start_io_ग_लिखो - declare the file is being used क्रम buffered ग_लिखोs
 * @inode: file inode
 *
 * Declare that a buffered ग_लिखो operation is about to start, and ensure
 * that we block all direct I/O.
 */
व्योम
ceph_start_io_ग_लिखो(काष्ठा inode *inode)
अणु
	करोwn_ग_लिखो(&inode->i_rwsem);
	ceph_block_o_direct(ceph_inode(inode), inode);
पूर्ण

/**
 * ceph_end_io_ग_लिखो - declare that the buffered ग_लिखो operation is करोne
 * @inode: file inode
 *
 * Declare that a buffered ग_लिखो operation is करोne, and release the
 * lock on inode->i_rwsem.
 */
व्योम
ceph_end_io_ग_लिखो(काष्ठा inode *inode)
अणु
	up_ग_लिखो(&inode->i_rwsem);
पूर्ण

/* Call with exclusively locked inode->i_rwsem */
अटल व्योम ceph_block_buffered(काष्ठा ceph_inode_info *ci, काष्ठा inode *inode)
अणु
	lockdep_निश्चित_held_ग_लिखो(&inode->i_rwsem);

	अगर (!(READ_ONCE(ci->i_ceph_flags) & CEPH_I_OसूचीECT)) अणु
		spin_lock(&ci->i_ceph_lock);
		ci->i_ceph_flags |= CEPH_I_OसूचीECT;
		spin_unlock(&ci->i_ceph_lock);
		/* FIXME: unmap_mapping_range? */
		filemap_ग_लिखो_and_रुको(inode->i_mapping);
	पूर्ण
पूर्ण

/**
 * ceph_start_io_direct - declare the file is being used क्रम direct i/o
 * @inode: file inode
 *
 * Declare that a direct I/O operation is about to start, and ensure
 * that we block all buffered I/O.
 * On निकास, the function ensures that the CEPH_I_OसूचीECT flag is set,
 * and holds a shared lock on inode->i_rwsem to ensure that the flag
 * cannot be changed.
 * In practice, this means that direct I/O operations are allowed to
 * execute in parallel, thanks to the shared lock, whereas buffered I/O
 * operations need to रुको to grab an exclusive lock in order to clear
 * CEPH_I_OसूचीECT.
 * Note that buffered ग_लिखोs and truncates both take a ग_लिखो lock on
 * inode->i_rwsem, meaning that those are serialised w.r.t. O_सूचीECT.
 */
व्योम
ceph_start_io_direct(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);

	/* Be an optimist! */
	करोwn_पढ़ो(&inode->i_rwsem);
	अगर (READ_ONCE(ci->i_ceph_flags) & CEPH_I_OसूचीECT)
		वापस;
	up_पढ़ो(&inode->i_rwsem);
	/* Slow path.... */
	करोwn_ग_लिखो(&inode->i_rwsem);
	ceph_block_buffered(ci, inode);
	करोwngrade_ग_लिखो(&inode->i_rwsem);
पूर्ण

/**
 * ceph_end_io_direct - declare that the direct i/o operation is करोne
 * @inode: file inode
 *
 * Declare that a direct I/O operation is करोne, and release the shared
 * lock on inode->i_rwsem.
 */
व्योम
ceph_end_io_direct(काष्ठा inode *inode)
अणु
	up_पढ़ो(&inode->i_rwsem);
पूर्ण
