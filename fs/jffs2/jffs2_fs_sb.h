<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#अगर_अघोषित _JFFS2_FS_SB
#घोषणा _JFFS2_FS_SB

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/समयr.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/rwsem.h>

#घोषणा JFFS2_SB_FLAG_RO 1
#घोषणा JFFS2_SB_FLAG_SCANNING 2 /* Flash scanning is in progress */
#घोषणा JFFS2_SB_FLAG_BUILDING 4 /* File प्रणाली building is in progress */

काष्ठा jffs2_inodirty;

काष्ठा jffs2_mount_opts अणु
	bool override_compr;
	अचिन्हित पूर्णांक compr;

	/* The size of the reserved pool. The reserved pool is the JFFS2 flash
	 * space which may only be used by root cannot be used by the other
	 * users. This is implemented simply by means of not allowing the
	 * latter users to ग_लिखो to the file प्रणाली अगर the amount अगर the
	 * available space is less then 'rp_size'. */
	bool set_rp_size;
	अचिन्हित पूर्णांक rp_size;
पूर्ण;

/* A काष्ठा क्रम the overall file प्रणाली control.  Poपूर्णांकers to
   jffs2_sb_info काष्ठाs are named `c' in the source code.
   Nee jffs_control
*/
काष्ठा jffs2_sb_info अणु
	काष्ठा mtd_info *mtd;

	uपूर्णांक32_t highest_ino;
	uपूर्णांक32_t check_ino;		/* *NEXT* inode to be checked */

	अचिन्हित पूर्णांक flags;

	काष्ठा task_काष्ठा *gc_task;	/* GC task काष्ठा */
	काष्ठा completion gc_thपढ़ो_start; /* GC thपढ़ो start completion */
	काष्ठा completion gc_thपढ़ो_निकास; /* GC thपढ़ो निकास completion port */

	काष्ठा mutex alloc_sem;		/* Used to protect all the following
					   fields, and also to protect against
					   out-of-order writing of nodes. And GC. */
	uपूर्णांक32_t cleanmarker_size;	/* Size of an _अंतरभूत_ CLEANMARKER
					 (i.e. zero क्रम OOB CLEANMARKER */

	uपूर्णांक32_t flash_size;
	uपूर्णांक32_t used_size;
	uपूर्णांक32_t dirty_size;
	uपूर्णांक32_t wasted_size;
	uपूर्णांक32_t मुक्त_size;
	uपूर्णांक32_t erasing_size;
	uपूर्णांक32_t bad_size;
	uपूर्णांक32_t sector_size;
	uपूर्णांक32_t unchecked_size;

	uपूर्णांक32_t nr_मुक्त_blocks;
	uपूर्णांक32_t nr_erasing_blocks;

	/* Number of मुक्त blocks there must be beक्रमe we... */
	uपूर्णांक8_t resv_blocks_ग_लिखो;	/* ... allow a normal fileप्रणाली ग_लिखो */
	uपूर्णांक8_t resv_blocks_deletion;	/* ... allow a normal fileप्रणाली deletion */
	uपूर्णांक8_t resv_blocks_gctrigger;	/* ... wake up the GC thपढ़ो */
	uपूर्णांक8_t resv_blocks_gcbad;	/* ... pick a block from the bad_list to GC */
	uपूर्णांक8_t resv_blocks_gcmerge;	/* ... merge pages when garbage collecting */
	/* Number of 'very dirty' blocks beक्रमe we trigger immediate GC */
	uपूर्णांक8_t vdirty_blocks_gctrigger;

	uपूर्णांक32_t nospc_dirty_size;

	uपूर्णांक32_t nr_blocks;
	काष्ठा jffs2_eraseblock *blocks;	/* The whole array of blocks. Used क्रम getting blocks
						 * from the offset (blocks[ofs / sector_size]) */
	काष्ठा jffs2_eraseblock *nextblock;	/* The block we're currently filling */

	काष्ठा jffs2_eraseblock *gcblock;	/* The block we're currently garbage-collecting */

	काष्ठा list_head clean_list;		/* Blocks 100% full of clean data */
	काष्ठा list_head very_dirty_list;	/* Blocks with lots of dirty space */
	काष्ठा list_head dirty_list;		/* Blocks with some dirty space */
	काष्ठा list_head erasable_list;		/* Blocks which are completely dirty, and need erasing */
	काष्ठा list_head erasable_pending_wbuf_list;	/* Blocks which need erasing but only after the current wbuf is flushed */
	काष्ठा list_head erasing_list;		/* Blocks which are currently erasing */
	काष्ठा list_head erase_checking_list;	/* Blocks which are being checked and marked */
	काष्ठा list_head erase_pending_list;	/* Blocks which need erasing now */
	काष्ठा list_head erase_complete_list;	/* Blocks which are erased and need the clean marker written to them */
	काष्ठा list_head मुक्त_list;		/* Blocks which are मुक्त and पढ़ोy to be used */
	काष्ठा list_head bad_list;		/* Bad blocks. */
	काष्ठा list_head bad_used_list;		/* Bad blocks with valid data in. */

	spinlock_t erase_completion_lock;	/* Protect मुक्त_list and erasing_list
						   against erase completion handler */
	रुको_queue_head_t erase_रुको;		/* For रुकोing क्रम erases to complete */

	रुको_queue_head_t inocache_wq;
	पूर्णांक inocache_hashsize;
	काष्ठा jffs2_inode_cache **inocache_list;
	spinlock_t inocache_lock;

	/* Sem to allow jffs2_garbage_collect_deletion_dirent to
	   drop the erase_completion_lock जबतक it's holding a poपूर्णांकer
	   to an obsoleted node. I करोn't like this. Alternatives welcomed. */
	काष्ठा mutex erase_मुक्त_sem;

	uपूर्णांक32_t wbuf_pagesize; /* 0 क्रम NOR and other flashes with no wbuf */

#अगर_घोषित CONFIG_JFFS2_FS_WBUF_VERIFY
	अचिन्हित अक्षर *wbuf_verअगरy; /* पढ़ो-back buffer क्रम verअगरication */
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
	अचिन्हित अक्षर *wbuf; /* Write-behind buffer क्रम न_अंकD flash */
	uपूर्णांक32_t wbuf_ofs;
	uपूर्णांक32_t wbuf_len;
	काष्ठा jffs2_inodirty *wbuf_inodes;
	काष्ठा rw_semaphore wbuf_sem;	/* Protects the ग_लिखो buffer */

	काष्ठा delayed_work wbuf_dwork; /* ग_लिखो-buffer ग_लिखो-out work */

	अचिन्हित अक्षर *oobbuf;
	पूर्णांक oobavail; /* How many bytes are available क्रम JFFS2 in OOB */
#पूर्ण_अगर

	काष्ठा jffs2_summary *summary;		/* Summary inक्रमmation */
	काष्ठा jffs2_mount_opts mount_opts;

#अगर_घोषित CONFIG_JFFS2_FS_XATTR
#घोषणा XATTRINDEX_HASHSIZE	(57)
	uपूर्णांक32_t highest_xid;
	uपूर्णांक32_t highest_xseqno;
	काष्ठा list_head xattrindex[XATTRINDEX_HASHSIZE];
	काष्ठा list_head xattr_unchecked;
	काष्ठा list_head xattr_dead_list;
	काष्ठा jffs2_xattr_ref *xref_dead_list;
	काष्ठा jffs2_xattr_ref *xref_temp;
	काष्ठा rw_semaphore xattr_sem;
	uपूर्णांक32_t xdatum_mem_usage;
	uपूर्णांक32_t xdatum_mem_threshold;
#पूर्ण_अगर
	/* OS-निजी poपूर्णांकer क्रम getting back to master superblock info */
	व्योम *os_priv;
पूर्ण;

#पूर्ण_अगर /* _JFFS2_FS_SB */
