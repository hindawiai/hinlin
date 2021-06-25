<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IVERSION_H
#घोषणा _LINUX_IVERSION_H

#समावेश <linux/fs.h>

/*
 * The inode->i_version field:
 * ---------------------------
 * The change attribute (i_version) is mandated by NFSv4 and is mostly क्रम
 * knfsd, but is also used क्रम other purposes (e.g. IMA). The i_version must
 * appear dअगरferent to observers अगर there was a change to the inode's data or
 * metadata since it was last queried.
 *
 * Observers see the i_version as a 64-bit number that never decreases. If it
 * reमुख्यs the same since it was last checked, then nothing has changed in the
 * inode. If it's dअगरferent then something has changed. Observers cannot infer
 * anything about the nature or magnitude of the changes from the value, only
 * that the inode has changed in some fashion.
 *
 * Not all fileप्रणालीs properly implement the i_version counter. Subप्रणालीs that
 * want to use i_version field on an inode should first check whether the
 * fileप्रणाली sets the SB_I_VERSION flag (usually via the IS_I_VERSION macro).
 *
 * Those that set SB_I_VERSION will स्वतःmatically have their i_version counter
 * incremented on ग_लिखोs to normal files. If the SB_I_VERSION is not set, then
 * the VFS will not touch it on ग_लिखोs, and the fileप्रणाली can use it how it
 * wishes. Note that the fileप्रणाली is always responsible क्रम updating the
 * i_version on namespace changes in directories (सूची_गढ़ो, सूची_हटाओ, unlink, etc.).
 * We consider these sorts of fileप्रणालीs to have a kernel-managed i_version.
 *
 * It may be impractical क्रम fileप्रणालीs to keep i_version updates atomic with
 * respect to the changes that cause them.  They should, however, guarantee
 * that i_version updates are never visible beक्रमe the changes that caused
 * them.  Also, i_version updates should never be delayed दीर्घer than it takes
 * the original change to reach disk.
 *
 * This implementation uses the low bit in the i_version field as a flag to
 * track when the value has been queried. If it has not been queried since it
 * was last incremented, we can skip the increment in most हालs.
 *
 * In the event that we're updating the स_समय, we will usually go ahead and
 * bump the i_version anyway. Since that has to go to stable storage in some
 * fashion, we might as well increment it as well.
 *
 * With this implementation, the value should always appear to observers to
 * increase over समय अगर the file has changed. It's recommended to use
 * inode_eq_iversion() helper to compare values.
 *
 * Note that some fileप्रणालीs (e.g. NFS and AFS) just use the field to store
 * a server-provided value (क्रम the most part). For that reason, those
 * fileप्रणालीs करो not set SB_I_VERSION. These fileप्रणालीs are considered to
 * have a self-managed i_version.
 *
 * Persistently storing the i_version
 * ----------------------------------
 * Queries of the i_version field are not gated on them hitting the backing
 * store. It's always possible that the host could crash after allowing
 * a query of the value but beक्रमe it has made it to disk.
 *
 * To mitigate this problem, fileप्रणालीs should always use
 * inode_set_iversion_queried when loading an existing inode from disk. This
 * ensures that the next attempted inode increment will result in the value
 * changing.
 *
 * Storing the value to disk thereक्रमe करोes not count as a query, so those
 * fileप्रणालीs should use inode_peek_iversion to grab the value to be stored.
 * There is no need to flag the value as having been queried in that हाल.
 */

/*
 * We borrow the lowest bit in the i_version to use as a flag to tell whether
 * it has been queried since we last incremented it. If it has, then we must
 * increment it on the next change. After that, we can clear the flag and
 * aव्योम incrementing it again until it has again been queried.
 */
#घोषणा I_VERSION_QUERIED_SHIFT	(1)
#घोषणा I_VERSION_QUERIED	(1ULL << (I_VERSION_QUERIED_SHIFT - 1))
#घोषणा I_VERSION_INCREMENT	(1ULL << I_VERSION_QUERIED_SHIFT)

/**
 * inode_set_iversion_raw - set i_version to the specअगरied raw value
 * @inode: inode to set
 * @val: new i_version value to set
 *
 * Set @inode's i_version field to @val. This function is क्रम use by
 * fileप्रणालीs that self-manage the i_version.
 *
 * For example, the NFS client stores its NFSv4 change attribute in this way,
 * and the AFS client stores the data_version from the server here.
 */
अटल अंतरभूत व्योम
inode_set_iversion_raw(काष्ठा inode *inode, u64 val)
अणु
	atomic64_set(&inode->i_version, val);
पूर्ण

/**
 * inode_peek_iversion_raw - grab a "raw" iversion value
 * @inode: inode from which i_version should be पढ़ो
 *
 * Grab a "raw" inode->i_version value and वापस it. The i_version is not
 * flagged or converted in any way. This is mostly used to access a self-managed
 * i_version.
 *
 * With those fileप्रणालीs, we want to treat the i_version as an entirely
 * opaque value.
 */
अटल अंतरभूत u64
inode_peek_iversion_raw(स्थिर काष्ठा inode *inode)
अणु
	वापस atomic64_पढ़ो(&inode->i_version);
पूर्ण

/**
 * inode_set_max_iversion_raw - update i_version new value is larger
 * @inode: inode to set
 * @val: new i_version to set
 *
 * Some self-managed fileप्रणालीs (e.g Ceph) will only update the i_version
 * value अगर the new value is larger than the one we alपढ़ोy have.
 */
अटल अंतरभूत व्योम
inode_set_max_iversion_raw(काष्ठा inode *inode, u64 val)
अणु
	u64 cur, old;

	cur = inode_peek_iversion_raw(inode);
	क्रम (;;) अणु
		अगर (cur > val)
			अवरोध;
		old = atomic64_cmpxchg(&inode->i_version, cur, val);
		अगर (likely(old == cur))
			अवरोध;
		cur = old;
	पूर्ण
पूर्ण

/**
 * inode_set_iversion - set i_version to a particular value
 * @inode: inode to set
 * @val: new i_version value to set
 *
 * Set @inode's i_version field to @val. This function is क्रम fileप्रणालीs with
 * a kernel-managed i_version, क्रम initializing a newly-created inode from
 * scratch.
 *
 * In this हाल, we करो not set the QUERIED flag since we know that this value
 * has never been queried.
 */
अटल अंतरभूत व्योम
inode_set_iversion(काष्ठा inode *inode, u64 val)
अणु
	inode_set_iversion_raw(inode, val << I_VERSION_QUERIED_SHIFT);
पूर्ण

/**
 * inode_set_iversion_queried - set i_version to a particular value as quereied
 * @inode: inode to set
 * @val: new i_version value to set
 *
 * Set @inode's i_version field to @val, and flag it क्रम increment on the next
 * change.
 *
 * Fileप्रणालीs that persistently store the i_version on disk should use this
 * when loading an existing inode from disk.
 *
 * When loading in an i_version value from a backing store, we can't be certain
 * that it wasn't previously viewed beक्रमe being stored. Thus, we must assume
 * that it was, to ensure that we करोn't end up handing out the same value क्रम
 * dअगरferent versions of the same inode.
 */
अटल अंतरभूत व्योम
inode_set_iversion_queried(काष्ठा inode *inode, u64 val)
अणु
	inode_set_iversion_raw(inode, (val << I_VERSION_QUERIED_SHIFT) |
				I_VERSION_QUERIED);
पूर्ण

/**
 * inode_maybe_inc_iversion - increments i_version
 * @inode: inode with the i_version that should be updated
 * @क्रमce: increment the counter even अगर it's not necessary?
 *
 * Every समय the inode is modअगरied, the i_version field must be seen to have
 * changed by any observer.
 *
 * If "force" is set or the QUERIED flag is set, then ensure that we increment
 * the value, and clear the queried flag.
 *
 * In the common हाल where neither is set, then we can वापस "false" without
 * updating i_version.
 *
 * If this function वापसs false, and no other metadata has changed, then we
 * can aव्योम logging the metadata.
 */
अटल अंतरभूत bool
inode_maybe_inc_iversion(काष्ठा inode *inode, bool क्रमce)
अणु
	u64 cur, old, new;

	/*
	 * The i_version field is not strictly ordered with any other inode
	 * inक्रमmation, but the legacy inode_inc_iversion code used a spinlock
	 * to serialize increments.
	 *
	 * Here, we add full memory barriers to ensure that any de-facto
	 * ordering with other info is preserved.
	 *
	 * This barrier pairs with the barrier in inode_query_iversion()
	 */
	smp_mb();
	cur = inode_peek_iversion_raw(inode);
	क्रम (;;) अणु
		/* If flag is clear then we needn't करो anything */
		अगर (!क्रमce && !(cur & I_VERSION_QUERIED))
			वापस false;

		/* Since lowest bit is flag, add 2 to aव्योम it */
		new = (cur & ~I_VERSION_QUERIED) + I_VERSION_INCREMENT;

		old = atomic64_cmpxchg(&inode->i_version, cur, new);
		अगर (likely(old == cur))
			अवरोध;
		cur = old;
	पूर्ण
	वापस true;
पूर्ण


/**
 * inode_inc_iversion - क्रमcibly increment i_version
 * @inode: inode that needs to be updated
 *
 * Forcbily increment the i_version field. This always results in a change to
 * the observable value.
 */
अटल अंतरभूत व्योम
inode_inc_iversion(काष्ठा inode *inode)
अणु
	inode_maybe_inc_iversion(inode, true);
पूर्ण

/**
 * inode_iversion_need_inc - is the i_version in need of being incremented?
 * @inode: inode to check
 *
 * Returns whether the inode->i_version counter needs incrementing on the next
 * change. Just fetch the value and check the QUERIED flag.
 */
अटल अंतरभूत bool
inode_iversion_need_inc(काष्ठा inode *inode)
अणु
	वापस inode_peek_iversion_raw(inode) & I_VERSION_QUERIED;
पूर्ण

/**
 * inode_inc_iversion_raw - क्रमcibly increment raw i_version
 * @inode: inode that needs to be updated
 *
 * Forcbily increment the raw i_version field. This always results in a change
 * to the raw value.
 *
 * NFS will use the i_version field to store the value from the server. It
 * mostly treats it as opaque, but in the हाल where it holds a ग_लिखो
 * delegation, it must increment the value itself. This function करोes that.
 */
अटल अंतरभूत व्योम
inode_inc_iversion_raw(काष्ठा inode *inode)
अणु
	atomic64_inc(&inode->i_version);
पूर्ण

/**
 * inode_peek_iversion - पढ़ो i_version without flagging it to be incremented
 * @inode: inode from which i_version should be पढ़ो
 *
 * Read the inode i_version counter क्रम an inode without रेजिस्टरing it as a
 * query.
 *
 * This is typically used by local fileप्रणालीs that need to store an i_version
 * on disk. In that situation, it's not necessary to flag it as having been
 * viewed, as the result won't be used to gauge changes from that poपूर्णांक.
 */
अटल अंतरभूत u64
inode_peek_iversion(स्थिर काष्ठा inode *inode)
अणु
	वापस inode_peek_iversion_raw(inode) >> I_VERSION_QUERIED_SHIFT;
पूर्ण

/**
 * inode_query_iversion - पढ़ो i_version क्रम later use
 * @inode: inode from which i_version should be पढ़ो
 *
 * Read the inode i_version counter. This should be used by callers that wish
 * to store the वापसed i_version क्रम later comparison. This will guarantee
 * that a later query of the i_version will result in a dअगरferent value अगर
 * anything has changed.
 *
 * In this implementation, we fetch the current value, set the QUERIED flag and
 * then try to swap it पूर्णांकo place with a cmpxchg, अगर it wasn't alपढ़ोy set. If
 * that fails, we try again with the newly fetched value from the cmpxchg.
 */
अटल अंतरभूत u64
inode_query_iversion(काष्ठा inode *inode)
अणु
	u64 cur, old, new;

	cur = inode_peek_iversion_raw(inode);
	क्रम (;;) अणु
		/* If flag is alपढ़ोy set, then no need to swap */
		अगर (cur & I_VERSION_QUERIED) अणु
			/*
			 * This barrier (and the implicit barrier in the
			 * cmpxchg below) pairs with the barrier in
			 * inode_maybe_inc_iversion().
			 */
			smp_mb();
			अवरोध;
		पूर्ण

		new = cur | I_VERSION_QUERIED;
		old = atomic64_cmpxchg(&inode->i_version, cur, new);
		अगर (likely(old == cur))
			अवरोध;
		cur = old;
	पूर्ण
	वापस cur >> I_VERSION_QUERIED_SHIFT;
पूर्ण

/*
 * For fileप्रणालीs without any sort of change attribute, the best we can
 * करो is fake one up from the स_समय:
 */
अटल अंतरभूत u64 समय_प्रकारo_chattr(काष्ठा बारpec64 *t)
अणु
	u64 chattr = t->tv_sec;

	chattr <<= 32;
	chattr += t->tv_nsec;
	वापस chattr;
पूर्ण

/**
 * inode_eq_iversion_raw - check whether the raw i_version counter has changed
 * @inode: inode to check
 * @old: old value to check against its i_version
 *
 * Compare the current raw i_version counter with a previous one. Returns true
 * अगर they are the same or false अगर they are dअगरferent.
 */
अटल अंतरभूत bool
inode_eq_iversion_raw(स्थिर काष्ठा inode *inode, u64 old)
अणु
	वापस inode_peek_iversion_raw(inode) == old;
पूर्ण

/**
 * inode_eq_iversion - check whether the i_version counter has changed
 * @inode: inode to check
 * @old: old value to check against its i_version
 *
 * Compare an i_version counter with a previous one. Returns true अगर they are
 * the same, and false अगर they are dअगरferent.
 *
 * Note that we करोn't need to set the QUERIED flag in this हाल, as the value
 * in the inode is not being recorded क्रम later use.
 */
अटल अंतरभूत bool
inode_eq_iversion(स्थिर काष्ठा inode *inode, u64 old)
अणु
	वापस inode_peek_iversion(inode) == old;
पूर्ण
#पूर्ण_अगर
