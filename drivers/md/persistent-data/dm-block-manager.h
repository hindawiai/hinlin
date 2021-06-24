<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित _LINUX_DM_BLOCK_MANAGER_H
#घोषणा _LINUX_DM_BLOCK_MANAGER_H

#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>

/*----------------------------------------------------------------*/

/*
 * Block number.
 */
प्रकार uपूर्णांक64_t dm_block_t;
काष्ठा dm_block;

dm_block_t dm_block_location(काष्ठा dm_block *b);
व्योम *dm_block_data(काष्ठा dm_block *b);

/*----------------------------------------------------------------*/

/*
 * @name should be a unique identअगरier क्रम the block manager, no दीर्घer
 * than 32 अक्षरs.
 *
 * @max_held_per_thपढ़ो should be the maximum number of locks, पढ़ो or
 * ग_लिखो, that an inभागidual thपढ़ो holds at any one समय.
 */
काष्ठा dm_block_manager;
काष्ठा dm_block_manager *dm_block_manager_create(
	काष्ठा block_device *bdev, अचिन्हित block_size,
	अचिन्हित max_held_per_thपढ़ो);
व्योम dm_block_manager_destroy(काष्ठा dm_block_manager *bm);

अचिन्हित dm_bm_block_size(काष्ठा dm_block_manager *bm);
dm_block_t dm_bm_nr_blocks(काष्ठा dm_block_manager *bm);

/*----------------------------------------------------------------*/

/*
 * The validator allows the caller to verअगरy newly-पढ़ो data and modअगरy
 * the data just beक्रमe writing, e.g. to calculate checksums.  It's
 * important to be consistent with your use of validators.  The only समय
 * you can change validators is अगर you call dm_bm_ग_लिखो_lock_zero.
 */
काष्ठा dm_block_validator अणु
	स्थिर अक्षर *name;
	व्योम (*prepare_क्रम_ग_लिखो)(काष्ठा dm_block_validator *v, काष्ठा dm_block *b, माप_प्रकार block_size);

	/*
	 * Return 0 अगर the checksum is valid or < 0 on error.
	 */
	पूर्णांक (*check)(काष्ठा dm_block_validator *v, काष्ठा dm_block *b, माप_प्रकार block_size);
पूर्ण;

/*----------------------------------------------------------------*/

/*
 * You can have multiple concurrent पढ़ोers or a single ग_लिखोr holding a
 * block lock.
 */

/*
 * dm_bm_lock() locks a block and वापसs through @result a poपूर्णांकer to
 * memory that holds a copy of that block.  If you have ग_लिखो-locked the
 * block then any changes you make to memory poपूर्णांकed to by @result will be
 * written back to the disk someसमय after dm_bm_unlock is called.
 */
पूर्णांक dm_bm_पढ़ो_lock(काष्ठा dm_block_manager *bm, dm_block_t b,
		    काष्ठा dm_block_validator *v,
		    काष्ठा dm_block **result);

पूर्णांक dm_bm_ग_लिखो_lock(काष्ठा dm_block_manager *bm, dm_block_t b,
		     काष्ठा dm_block_validator *v,
		     काष्ठा dm_block **result);

/*
 * The *_try_lock variants वापस -EWOULDBLOCK अगर the block isn't
 * available immediately.
 */
पूर्णांक dm_bm_पढ़ो_try_lock(काष्ठा dm_block_manager *bm, dm_block_t b,
			काष्ठा dm_block_validator *v,
			काष्ठा dm_block **result);

/*
 * Use dm_bm_ग_लिखो_lock_zero() when you know you're going to
 * overग_लिखो the block completely.  It saves a disk पढ़ो.
 */
पूर्णांक dm_bm_ग_लिखो_lock_zero(काष्ठा dm_block_manager *bm, dm_block_t b,
			  काष्ठा dm_block_validator *v,
			  काष्ठा dm_block **result);

व्योम dm_bm_unlock(काष्ठा dm_block *b);

/*
 * It's a common idiom to have a superblock that should be committed last.
 *
 * @superblock should be ग_लिखो-locked on entry. It will be unlocked during
 * this function.  All dirty blocks are guaranteed to be written and flushed
 * beक्रमe the superblock.
 *
 * This method always blocks.
 */
पूर्णांक dm_bm_flush(काष्ठा dm_block_manager *bm);

/*
 * Request data is prefetched पूर्णांकo the cache.
 */
व्योम dm_bm_prefetch(काष्ठा dm_block_manager *bm, dm_block_t b);

/*
 * Switches the bm to a पढ़ो only mode.  Once पढ़ो-only mode
 * has been entered the following functions will वापस -EPERM.
 *
 *   dm_bm_ग_लिखो_lock
 *   dm_bm_ग_लिखो_lock_zero
 *   dm_bm_flush_and_unlock
 *
 * Additionally you should not use dm_bm_unlock_move, however no error will
 * be वापसed अगर you करो.
 */
bool dm_bm_is_पढ़ो_only(काष्ठा dm_block_manager *bm);
व्योम dm_bm_set_पढ़ो_only(काष्ठा dm_block_manager *bm);
व्योम dm_bm_set_पढ़ो_ग_लिखो(काष्ठा dm_block_manager *bm);

u32 dm_bm_checksum(स्थिर व्योम *data, माप_प्रकार len, u32 init_xor);

/*----------------------------------------------------------------*/

#पूर्ण_अगर	/* _LINUX_DM_BLOCK_MANAGER_H */
