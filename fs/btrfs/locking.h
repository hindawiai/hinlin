<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Oracle.  All rights reserved.
 */

#अगर_अघोषित BTRFS_LOCKING_H
#घोषणा BTRFS_LOCKING_H

#समावेश <linux/atomic.h>
#समावेश <linux/रुको.h>
#समावेश <linux/percpu_counter.h>
#समावेश "extent_io.h"

#घोषणा BTRFS_WRITE_LOCK 1
#घोषणा BTRFS_READ_LOCK 2

/*
 * We are limited in number of subclasses by MAX_LOCKDEP_SUBCLASSES, which at
 * the समय of this patch is 8, which is how many we use.  Keep this in mind अगर
 * you decide you want to add another subclass.
 */
क्रमागत btrfs_lock_nesting अणु
	BTRFS_NESTING_NORMAL,

	/*
	 * When we COW a block we are holding the lock on the original block,
	 * and since our lockdep maps are rootid+level, this confuses lockdep
	 * when we lock the newly allocated COW'd block.  Handle this by having
	 * a subclass क्रम COW'ed blocks so that lockdep doesn't complain.
	 */
	BTRFS_NESTING_COW,

	/*
	 * Oftenबार we need to lock adjacent nodes on the same level जबतक
	 * still holding the lock on the original node we searched to, such as
	 * क्रम searching क्रमward or क्रम split/balance.
	 *
	 * Because of this we need to indicate to lockdep that this is
	 * acceptable by having a dअगरferent subclass क्रम each of these
	 * operations.
	 */
	BTRFS_NESTING_LEFT,
	BTRFS_NESTING_RIGHT,

	/*
	 * When splitting we will be holding a lock on the left/right node when
	 * we need to cow that node, thus we need a new set of subclasses क्रम
	 * these two operations.
	 */
	BTRFS_NESTING_LEFT_COW,
	BTRFS_NESTING_RIGHT_COW,

	/*
	 * When splitting we may push nodes to the left or right, but still use
	 * the subsequent nodes in our path, keeping our locks on those adjacent
	 * blocks.  Thus when we go to allocate a new split block we've alपढ़ोy
	 * used up all of our available subclasses, so this subclass exists to
	 * handle this हाल where we need to allocate a new split block.
	 */
	BTRFS_NESTING_SPLIT,

	/*
	 * When promoting a new block to a root we need to have a special
	 * subclass so we करोn't confuse lockdep, as it will appear that we are
	 * locking a higher level node beक्रमe a lower level one.  Copying also
	 * has this problem as it appears we're locking the same block again
	 * when we make a snapshot of an existing root.
	 */
	BTRFS_NESTING_NEW_ROOT,

	/*
	 * We are limited to MAX_LOCKDEP_SUBLCLASSES number of subclasses, so
	 * add this in here and add a अटल_निश्चित to keep us from going over
	 * the limit.  As of this writing we're limited to 8, and we're
	 * definitely using 8, hence this check to keep us from messing up in
	 * the future.
	 */
	BTRFS_NESTING_MAX,
पूर्ण;

अटल_निश्चित(BTRFS_NESTING_MAX <= MAX_LOCKDEP_SUBCLASSES,
	      "too many lock subclasses defined");

काष्ठा btrfs_path;

व्योम __btrfs_tree_lock(काष्ठा extent_buffer *eb, क्रमागत btrfs_lock_nesting nest);
व्योम btrfs_tree_lock(काष्ठा extent_buffer *eb);
व्योम btrfs_tree_unlock(काष्ठा extent_buffer *eb);

व्योम __btrfs_tree_पढ़ो_lock(काष्ठा extent_buffer *eb, क्रमागत btrfs_lock_nesting nest);
व्योम btrfs_tree_पढ़ो_lock(काष्ठा extent_buffer *eb);
व्योम btrfs_tree_पढ़ो_unlock(काष्ठा extent_buffer *eb);
पूर्णांक btrfs_try_tree_पढ़ो_lock(काष्ठा extent_buffer *eb);
पूर्णांक btrfs_try_tree_ग_लिखो_lock(काष्ठा extent_buffer *eb);
काष्ठा extent_buffer *btrfs_lock_root_node(काष्ठा btrfs_root *root);
काष्ठा extent_buffer *btrfs_पढ़ो_lock_root_node(काष्ठा btrfs_root *root);

#अगर_घोषित CONFIG_BTRFS_DEBUG
अटल अंतरभूत व्योम btrfs_निश्चित_tree_locked(काष्ठा extent_buffer *eb) अणु
	lockdep_निश्चित_held(&eb->lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम btrfs_निश्चित_tree_locked(काष्ठा extent_buffer *eb) अणु पूर्ण
#पूर्ण_अगर

व्योम btrfs_unlock_up_safe(काष्ठा btrfs_path *path, पूर्णांक level);

अटल अंतरभूत व्योम btrfs_tree_unlock_rw(काष्ठा extent_buffer *eb, पूर्णांक rw)
अणु
	अगर (rw == BTRFS_WRITE_LOCK)
		btrfs_tree_unlock(eb);
	अन्यथा अगर (rw == BTRFS_READ_LOCK)
		btrfs_tree_पढ़ो_unlock(eb);
	अन्यथा
		BUG();
पूर्ण

काष्ठा btrfs_drew_lock अणु
	atomic_t पढ़ोers;
	काष्ठा percpu_counter ग_लिखोrs;
	रुको_queue_head_t pending_ग_लिखोrs;
	रुको_queue_head_t pending_पढ़ोers;
पूर्ण;

पूर्णांक btrfs_drew_lock_init(काष्ठा btrfs_drew_lock *lock);
व्योम btrfs_drew_lock_destroy(काष्ठा btrfs_drew_lock *lock);
व्योम btrfs_drew_ग_लिखो_lock(काष्ठा btrfs_drew_lock *lock);
bool btrfs_drew_try_ग_लिखो_lock(काष्ठा btrfs_drew_lock *lock);
व्योम btrfs_drew_ग_लिखो_unlock(काष्ठा btrfs_drew_lock *lock);
व्योम btrfs_drew_पढ़ो_lock(काष्ठा btrfs_drew_lock *lock);
व्योम btrfs_drew_पढ़ो_unlock(काष्ठा btrfs_drew_lock *lock);

#पूर्ण_अगर
