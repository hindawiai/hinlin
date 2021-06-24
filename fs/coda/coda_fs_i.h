<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  coda_fs_i.h
 *
 *  Copyright (C) 1998 Carnegie Mellon University
 *
 */

#अगर_अघोषित _LINUX_CODA_FS_I
#घोषणा _LINUX_CODA_FS_I

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/coda.h>

/*
 * coda fs inode data
 * c_lock protects accesses to c_flags, c_mapcount, c_cached_epoch, c_uid and
 * c_cached_perm.
 * vfs_inode is set only when the inode is created and never changes.
 * c_fid is set when the inode is created and should be considered immutable.
 */
काष्ठा coda_inode_info अणु
	काष्ठा CodaFid	   c_fid;	/* Coda identअगरier */
	u_लघु	           c_flags;     /* flags (see below) */
	अचिन्हित पूर्णांक	   c_mapcount;  /* nr of बार this inode is mapped */
	अचिन्हित पूर्णांक	   c_cached_epoch; /* epoch क्रम cached permissions */
	kuid_t		   c_uid;	/* fsuid क्रम cached permissions */
	अचिन्हित पूर्णांक       c_cached_perm; /* cached access permissions */
	spinlock_t	   c_lock;
	काष्ठा inode	   vfs_inode;
पूर्ण;

/*
 * coda fs file निजी data
 */
#घोषणा CODA_MAGIC 0xC0DAC0DA
काष्ठा coda_file_info अणु
	पूर्णांक		   cfi_magic;	  /* magic number */
	काष्ठा file	  *cfi_container; /* container file क्रम this cnode */
	अचिन्हित पूर्णांक	   cfi_mapcount;  /* nr of बार this file is mapped */
	bool		   cfi_access_पूर्णांकent; /* is access पूर्णांकent supported */
पूर्ण;

/* flags */
#घोषणा C_VATTR       0x1   /* Validity of vattr in inode */
#घोषणा C_FLUSH       0x2   /* used after a flush */
#घोषणा C_DYING       0x4   /* from venus (which died) */
#घोषणा C_PURGE       0x8

काष्ठा inode *coda_cnode_make(काष्ठा CodaFid *, काष्ठा super_block *);
काष्ठा inode *coda_iget(काष्ठा super_block *sb, काष्ठा CodaFid *fid, काष्ठा coda_vattr *attr);
काष्ठा inode *coda_cnode_makectl(काष्ठा super_block *sb);
काष्ठा inode *coda_fid_to_inode(काष्ठा CodaFid *fid, काष्ठा super_block *sb);
काष्ठा coda_file_info *coda_ftoc(काष्ठा file *file);
व्योम coda_replace_fid(काष्ठा inode *, काष्ठा CodaFid *, काष्ठा CodaFid *);

#पूर्ण_अगर
