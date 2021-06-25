<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * filecheck.h
 *
 * Online file check.
 *
 * Copyright (C) 2016 SuSE.  All rights reserved.
 */


#अगर_अघोषित खाताCHECK_H
#घोषणा खाताCHECK_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>


/* File check त्रुटि_सं */
क्रमागत अणु
	OCFS2_खाताCHECK_ERR_SUCCESS = 0,	/* Success */
	OCFS2_खाताCHECK_ERR_FAILED = 1000,	/* Other failure */
	OCFS2_खाताCHECK_ERR_INPROGRESS,		/* In progress */
	OCFS2_खाताCHECK_ERR_READONLY,		/* Read only */
	OCFS2_खाताCHECK_ERR_INJBD,		/* Buffer in jbd */
	OCFS2_खाताCHECK_ERR_INVALIDINO,		/* Invalid ino */
	OCFS2_खाताCHECK_ERR_BLOCKECC,		/* Block ecc */
	OCFS2_खाताCHECK_ERR_BLOCKNO,		/* Block number */
	OCFS2_खाताCHECK_ERR_VALIDFLAG,		/* Inode valid flag */
	OCFS2_खाताCHECK_ERR_GENERATION,		/* Inode generation */
	OCFS2_खाताCHECK_ERR_UNSUPPORTED		/* Unsupported */
पूर्ण;

#घोषणा OCFS2_खाताCHECK_ERR_START	OCFS2_खाताCHECK_ERR_FAILED
#घोषणा OCFS2_खाताCHECK_ERR_END		OCFS2_खाताCHECK_ERR_UNSUPPORTED

काष्ठा ocfs2_filecheck अणु
	काष्ठा list_head fc_head;	/* File check entry list head */
	spinlock_t fc_lock;
	अचिन्हित पूर्णांक fc_max;	/* Maximum number of entry in list */
	अचिन्हित पूर्णांक fc_size;	/* Current entry count in list */
	अचिन्हित पूर्णांक fc_करोne;	/* Finished entry count in list */
पूर्ण;

#घोषणा OCFS2_खाताCHECK_MAXSIZE		100
#घोषणा OCFS2_खाताCHECK_MINSIZE		10

/* File check operation type */
क्रमागत अणु
	OCFS2_खाताCHECK_TYPE_CHK = 0,	/* Check a file(inode) */
	OCFS2_खाताCHECK_TYPE_FIX,	/* Fix a file(inode) */
	OCFS2_खाताCHECK_TYPE_SET = 100	/* Set entry list maximum size */
पूर्ण;

काष्ठा ocfs2_filecheck_sysfs_entry अणु	/* sysfs entry per partition */
	काष्ठा kobject fs_kobj;
	काष्ठा completion fs_kobj_unरेजिस्टर;
	काष्ठा ocfs2_filecheck *fs_fcheck;
पूर्ण;


पूर्णांक ocfs2_filecheck_create_sysfs(काष्ठा ocfs2_super *osb);
व्योम ocfs2_filecheck_हटाओ_sysfs(काष्ठा ocfs2_super *osb);

#पूर्ण_अगर  /* खाताCHECK_H */
