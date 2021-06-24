<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "reiserfs.h"
#समावेश <linux/mutex.h>

/*
 * The previous reiserfs locking scheme was heavily based on
 * the tricky properties of the Bkl:
 *
 * - it was acquired recursively by a same task
 * - the perक्रमmances relied on the release-जबतक-schedule() property
 *
 * Now that we replace it by a mutex, we still want to keep the same
 * recursive property to aव्योम big changes in the code काष्ठाure.
 * We use our own lock_owner here because the owner field on a mutex
 * is only available in SMP or mutex debugging, also we only need this field
 * क्रम this mutex, no need क्रम a प्रणाली wide mutex facility.
 *
 * Also this lock is often released beक्रमe a call that could block because
 * reiserfs perक्रमmances were partially based on the release जबतक schedule()
 * property of the Bkl.
 */
व्योम reiserfs_ग_लिखो_lock(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_sb_info *sb_i = REISERFS_SB(s);

	अगर (sb_i->lock_owner != current) अणु
		mutex_lock(&sb_i->lock);
		sb_i->lock_owner = current;
	पूर्ण

	/* No need to protect it, only the current task touches it */
	sb_i->lock_depth++;
पूर्ण

व्योम reiserfs_ग_लिखो_unlock(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_sb_info *sb_i = REISERFS_SB(s);

	/*
	 * Are we unlocking without even holding the lock?
	 * Such a situation must उठाओ a BUG() अगर we करोn't want
	 * to corrupt the data.
	 */
	BUG_ON(sb_i->lock_owner != current);

	अगर (--sb_i->lock_depth == -1) अणु
		sb_i->lock_owner = शून्य;
		mutex_unlock(&sb_i->lock);
	पूर्ण
पूर्ण

पूर्णांक __must_check reiserfs_ग_लिखो_unlock_nested(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_sb_info *sb_i = REISERFS_SB(s);
	पूर्णांक depth;

	/* this can happen when the lock isn't always held */
	अगर (sb_i->lock_owner != current)
		वापस -1;

	depth = sb_i->lock_depth;

	sb_i->lock_depth = -1;
	sb_i->lock_owner = शून्य;
	mutex_unlock(&sb_i->lock);

	वापस depth;
पूर्ण

व्योम reiserfs_ग_लिखो_lock_nested(काष्ठा super_block *s, पूर्णांक depth)
अणु
	काष्ठा reiserfs_sb_info *sb_i = REISERFS_SB(s);

	/* this can happen when the lock isn't always held */
	अगर (depth == -1)
		वापस;

	mutex_lock(&sb_i->lock);
	sb_i->lock_owner = current;
	sb_i->lock_depth = depth;
पूर्ण

/*
 * Utility function to क्रमce a BUG अगर it is called without the superblock
 * ग_लिखो lock held.  caller is the string prपूर्णांकed just beक्रमe calling BUG()
 */
व्योम reiserfs_check_lock_depth(काष्ठा super_block *sb, अक्षर *caller)
अणु
	काष्ठा reiserfs_sb_info *sb_i = REISERFS_SB(sb);

	WARN_ON(sb_i->lock_depth < 0);
पूर्ण

#अगर_घोषित CONFIG_REISERFS_CHECK
व्योम reiserfs_lock_check_recursive(काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_sb_info *sb_i = REISERFS_SB(sb);

	WARN_ONCE((sb_i->lock_depth > 0), "Unwanted recursive reiserfs lock!\n");
पूर्ण
#पूर्ण_अगर
