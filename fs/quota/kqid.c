<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/quota.h>
#समावेश <linux/export.h>

/**
 *	qid_eq - Test to see अगर to kquid values are the same
 *	@left: A qid value
 *	@right: Another quid value
 *
 *	Return true अगर the two qid values are equal and false otherwise.
 */
bool qid_eq(काष्ठा kqid left, काष्ठा kqid right)
अणु
	अगर (left.type != right.type)
		वापस false;
	चयन(left.type) अणु
	हाल USRQUOTA:
		वापस uid_eq(left.uid, right.uid);
	हाल GRPQUOTA:
		वापस gid_eq(left.gid, right.gid);
	हाल PRJQUOTA:
		वापस projid_eq(left.projid, right.projid);
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qid_eq);

/**
 *	qid_lt - Test to see अगर one qid value is less than another
 *	@left: The possibly lesser qid value
 *	@right: The possibly greater qid value
 *
 *	Return true अगर left is less than right and false otherwise.
 */
bool qid_lt(काष्ठा kqid left, काष्ठा kqid right)
अणु
	अगर (left.type < right.type)
		वापस true;
	अगर (left.type > right.type)
		वापस false;
	चयन (left.type) अणु
	हाल USRQUOTA:
		वापस uid_lt(left.uid, right.uid);
	हाल GRPQUOTA:
		वापस gid_lt(left.gid, right.gid);
	हाल PRJQUOTA:
		वापस projid_lt(left.projid, right.projid);
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qid_lt);

/**
 *	from_kqid - Create a qid from a kqid user-namespace pair.
 *	@targ: The user namespace we want a qid in.
 *	@kqid: The kernel पूर्णांकernal quota identअगरier to start with.
 *
 *	Map @kqid पूर्णांकo the user-namespace specअगरied by @targ and
 *	वापस the resulting qid.
 *
 *	There is always a mapping पूर्णांकo the initial user_namespace.
 *
 *	If @kqid has no mapping in @targ (qid_t)-1 is वापसed.
 */
qid_t from_kqid(काष्ठा user_namespace *targ, काष्ठा kqid kqid)
अणु
	चयन (kqid.type) अणु
	हाल USRQUOTA:
		वापस from_kuid(targ, kqid.uid);
	हाल GRPQUOTA:
		वापस from_kgid(targ, kqid.gid);
	हाल PRJQUOTA:
		वापस from_kprojid(targ, kqid.projid);
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(from_kqid);

/**
 *	from_kqid_munged - Create a qid from a kqid user-namespace pair.
 *	@targ: The user namespace we want a qid in.
 *	@kqid: The kernel पूर्णांकernal quota identअगरier to start with.
 *
 *	Map @kqid पूर्णांकo the user-namespace specअगरied by @targ and
 *	वापस the resulting qid.
 *
 *	There is always a mapping पूर्णांकo the initial user_namespace.
 *
 *	Unlike from_kqid from_kqid_munged never fails and always
 *	वापसs a valid projid.  This makes from_kqid_munged
 *	appropriate क्रम use in places where failing to provide
 *	a qid_t is not a good option.
 *
 *	If @kqid has no mapping in @targ the kqid.type specअगरic
 *	overflow identअगरier is वापसed.
 */
qid_t from_kqid_munged(काष्ठा user_namespace *targ, काष्ठा kqid kqid)
अणु
	चयन (kqid.type) अणु
	हाल USRQUOTA:
		वापस from_kuid_munged(targ, kqid.uid);
	हाल GRPQUOTA:
		वापस from_kgid_munged(targ, kqid.gid);
	हाल PRJQUOTA:
		वापस from_kprojid_munged(targ, kqid.projid);
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(from_kqid_munged);

/**
 *	qid_valid - Report अगर a valid value is stored in a kqid.
 *	@qid: The kernel पूर्णांकernal quota identअगरier to test.
 */
bool qid_valid(काष्ठा kqid qid)
अणु
	चयन (qid.type) अणु
	हाल USRQUOTA:
		वापस uid_valid(qid.uid);
	हाल GRPQUOTA:
		वापस gid_valid(qid.gid);
	हाल PRJQUOTA:
		वापस projid_valid(qid.projid);
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qid_valid);
