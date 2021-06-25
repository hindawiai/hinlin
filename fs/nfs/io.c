<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Trond Myklebust
 *
 * I/O and data path helper functionality.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/fs.h>
#समावेश <linux/nfs_fs.h>

#समावेश "internal.h"

/* Call with exclusively locked inode->i_rwsem */
अटल व्योम nfs_block_o_direct(काष्ठा nfs_inode *nfsi, काष्ठा inode *inode)
अणु
	अगर (test_bit(NFS_INO_OसूचीECT, &nfsi->flags)) अणु
		clear_bit(NFS_INO_OसूचीECT, &nfsi->flags);
		inode_dio_रुको(inode);
	पूर्ण
पूर्ण

/**
 * nfs_start_io_पढ़ो - declare the file is being used क्रम buffered पढ़ोs
 * @inode: file inode
 *
 * Declare that a buffered पढ़ो operation is about to start, and ensure
 * that we block all direct I/O.
 * On निकास, the function ensures that the NFS_INO_OसूचीECT flag is unset,
 * and holds a shared lock on inode->i_rwsem to ensure that the flag
 * cannot be changed.
 * In practice, this means that buffered पढ़ो operations are allowed to
 * execute in parallel, thanks to the shared lock, whereas direct I/O
 * operations need to रुको to grab an exclusive lock in order to set
 * NFS_INO_OसूचीECT.
 * Note that buffered ग_लिखोs and truncates both take a ग_लिखो lock on
 * inode->i_rwsem, meaning that those are serialised w.r.t. the पढ़ोs.
 */
व्योम
nfs_start_io_पढ़ो(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	/* Be an optimist! */
	करोwn_पढ़ो(&inode->i_rwsem);
	अगर (test_bit(NFS_INO_OसूचीECT, &nfsi->flags) == 0)
		वापस;
	up_पढ़ो(&inode->i_rwsem);
	/* Slow path.... */
	करोwn_ग_लिखो(&inode->i_rwsem);
	nfs_block_o_direct(nfsi, inode);
	करोwngrade_ग_लिखो(&inode->i_rwsem);
पूर्ण

/**
 * nfs_end_io_पढ़ो - declare that the buffered पढ़ो operation is करोne
 * @inode: file inode
 *
 * Declare that a buffered पढ़ो operation is करोne, and release the shared
 * lock on inode->i_rwsem.
 */
व्योम
nfs_end_io_पढ़ो(काष्ठा inode *inode)
अणु
	up_पढ़ो(&inode->i_rwsem);
पूर्ण

/**
 * nfs_start_io_ग_लिखो - declare the file is being used क्रम buffered ग_लिखोs
 * @inode: file inode
 *
 * Declare that a buffered पढ़ो operation is about to start, and ensure
 * that we block all direct I/O.
 */
व्योम
nfs_start_io_ग_लिखो(काष्ठा inode *inode)
अणु
	करोwn_ग_लिखो(&inode->i_rwsem);
	nfs_block_o_direct(NFS_I(inode), inode);
पूर्ण

/**
 * nfs_end_io_ग_लिखो - declare that the buffered ग_लिखो operation is करोne
 * @inode: file inode
 *
 * Declare that a buffered ग_लिखो operation is करोne, and release the
 * lock on inode->i_rwsem.
 */
व्योम
nfs_end_io_ग_लिखो(काष्ठा inode *inode)
अणु
	up_ग_लिखो(&inode->i_rwsem);
पूर्ण

/* Call with exclusively locked inode->i_rwsem */
अटल व्योम nfs_block_buffered(काष्ठा nfs_inode *nfsi, काष्ठा inode *inode)
अणु
	अगर (!test_bit(NFS_INO_OसूचीECT, &nfsi->flags)) अणु
		set_bit(NFS_INO_OसूचीECT, &nfsi->flags);
		nfs_sync_mapping(inode->i_mapping);
	पूर्ण
पूर्ण

/**
 * nfs_start_io_direct - declare the file is being used क्रम direct i/o
 * @inode: file inode
 *
 * Declare that a direct I/O operation is about to start, and ensure
 * that we block all buffered I/O.
 * On निकास, the function ensures that the NFS_INO_OसूचीECT flag is set,
 * and holds a shared lock on inode->i_rwsem to ensure that the flag
 * cannot be changed.
 * In practice, this means that direct I/O operations are allowed to
 * execute in parallel, thanks to the shared lock, whereas buffered I/O
 * operations need to रुको to grab an exclusive lock in order to clear
 * NFS_INO_OसूचीECT.
 * Note that buffered ग_लिखोs and truncates both take a ग_लिखो lock on
 * inode->i_rwsem, meaning that those are serialised w.r.t. O_सूचीECT.
 */
व्योम
nfs_start_io_direct(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	/* Be an optimist! */
	करोwn_पढ़ो(&inode->i_rwsem);
	अगर (test_bit(NFS_INO_OसूचीECT, &nfsi->flags) != 0)
		वापस;
	up_पढ़ो(&inode->i_rwsem);
	/* Slow path.... */
	करोwn_ग_लिखो(&inode->i_rwsem);
	nfs_block_buffered(nfsi, inode);
	करोwngrade_ग_लिखो(&inode->i_rwsem);
पूर्ण

/**
 * nfs_end_io_direct - declare that the direct i/o operation is करोne
 * @inode: file inode
 *
 * Declare that a direct I/O operation is करोne, and release the shared
 * lock on inode->i_rwsem.
 */
व्योम
nfs_end_io_direct(काष्ठा inode *inode)
अणु
	up_पढ़ो(&inode->i_rwsem);
पूर्ण
