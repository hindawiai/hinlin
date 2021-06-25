<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Definitions of काष्ठाures and functions क्रम quota क्रमmats using trie
 */

#अगर_अघोषित _LINUX_DQBLK_QTREE_H
#घोषणा _LINUX_DQBLK_QTREE_H

#समावेश <linux/types.h>

/* Numbers of blocks needed क्रम updates - we count with the smallest
 * possible block size (1024) */
#घोषणा QTREE_INIT_ALLOC 4
#घोषणा QTREE_INIT_REWRITE 2
#घोषणा QTREE_DEL_ALLOC 0
#घोषणा QTREE_DEL_REWRITE 6

काष्ठा dquot;
काष्ठा kqid;

/* Operations */
काष्ठा qtree_fmt_operations अणु
	व्योम (*mem2disk_dqblk)(व्योम *disk, काष्ठा dquot *dquot);	/* Convert given entry from in memory क्रमmat to disk one */
	व्योम (*disk2mem_dqblk)(काष्ठा dquot *dquot, व्योम *disk);	/* Convert given entry from disk क्रमmat to in memory one */
	पूर्णांक (*is_id)(व्योम *disk, काष्ठा dquot *dquot);	/* Is this काष्ठाure क्रम given id? */
पूर्ण;

/* Inmemory copy of version specअगरic inक्रमmation */
काष्ठा qtree_mem_dqinfo अणु
	काष्ठा super_block *dqi_sb;	/* Sb quota is on */
	पूर्णांक dqi_type;			/* Quota type */
	अचिन्हित पूर्णांक dqi_blocks;	/* # of blocks in quota file */
	अचिन्हित पूर्णांक dqi_मुक्त_blk;	/* First block in list of मुक्त blocks */
	अचिन्हित पूर्णांक dqi_मुक्त_entry;	/* First block with मुक्त entry */
	अचिन्हित पूर्णांक dqi_blocksize_bits;	/* Block size of quota file */
	अचिन्हित पूर्णांक dqi_entry_size;	/* Size of quota entry in quota file */
	अचिन्हित पूर्णांक dqi_usable_bs;	/* Space usable in block क्रम quota data */
	अचिन्हित पूर्णांक dqi_qtree_depth;	/* Precomputed depth of quota tree */
	स्थिर काष्ठा qtree_fmt_operations *dqi_ops; /* Operations क्रम entry manipulation */
पूर्ण;

पूर्णांक qtree_ग_लिखो_dquot(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot);
पूर्णांक qtree_पढ़ो_dquot(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot);
पूर्णांक qtree_delete_dquot(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot);
पूर्णांक qtree_release_dquot(काष्ठा qtree_mem_dqinfo *info, काष्ठा dquot *dquot);
पूर्णांक qtree_entry_unused(काष्ठा qtree_mem_dqinfo *info, अक्षर *disk);
अटल अंतरभूत पूर्णांक qtree_depth(काष्ठा qtree_mem_dqinfo *info)
अणु
	अचिन्हित पूर्णांक epb = info->dqi_usable_bs >> 2;
	अचिन्हित दीर्घ दीर्घ entries = epb;
	पूर्णांक i;

	क्रम (i = 1; entries < (1ULL << 32); i++)
		entries *= epb;
	वापस i;
पूर्ण
पूर्णांक qtree_get_next_id(काष्ठा qtree_mem_dqinfo *info, काष्ठा kqid *qid);

#पूर्ण_अगर /* _LINUX_DQBLK_QTREE_H */
