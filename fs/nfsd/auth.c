<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de> */

#समावेश <linux/sched.h>
#समावेश "nfsd.h"
#समावेश "auth.h"

पूर्णांक nfsexp_flags(काष्ठा svc_rqst *rqstp, काष्ठा svc_export *exp)
अणु
	काष्ठा exp_flavor_info *f;
	काष्ठा exp_flavor_info *end = exp->ex_flavors + exp->ex_nflavors;

	क्रम (f = exp->ex_flavors; f < end; f++) अणु
		अगर (f->pseuकरोflavor == rqstp->rq_cred.cr_flavor)
			वापस f->flags;
	पूर्ण
	वापस exp->ex_flags;

पूर्ण

पूर्णांक nfsd_setuser(काष्ठा svc_rqst *rqstp, काष्ठा svc_export *exp)
अणु
	काष्ठा group_info *rqgi;
	काष्ठा group_info *gi;
	काष्ठा cred *new;
	पूर्णांक i;
	पूर्णांक flags = nfsexp_flags(rqstp, exp);

	validate_process_creds();

	/* discard any old override beक्रमe preparing the new set */
	revert_creds(get_cred(current_real_cred()));
	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	new->fsuid = rqstp->rq_cred.cr_uid;
	new->fsgid = rqstp->rq_cred.cr_gid;

	rqgi = rqstp->rq_cred.cr_group_info;

	अगर (flags & NFSEXP_ALLSQUASH) अणु
		new->fsuid = exp->ex_anon_uid;
		new->fsgid = exp->ex_anon_gid;
		gi = groups_alloc(0);
		अगर (!gi)
			जाओ oom;
	पूर्ण अन्यथा अगर (flags & NFSEXP_ROOTSQUASH) अणु
		अगर (uid_eq(new->fsuid, GLOBAL_ROOT_UID))
			new->fsuid = exp->ex_anon_uid;
		अगर (gid_eq(new->fsgid, GLOBAL_ROOT_GID))
			new->fsgid = exp->ex_anon_gid;

		gi = groups_alloc(rqgi->ngroups);
		अगर (!gi)
			जाओ oom;

		क्रम (i = 0; i < rqgi->ngroups; i++) अणु
			अगर (gid_eq(GLOBAL_ROOT_GID, rqgi->gid[i]))
				gi->gid[i] = exp->ex_anon_gid;
			अन्यथा
				gi->gid[i] = rqgi->gid[i];
		पूर्ण

		/* Each thपढ़ो allocates its own gi, no race */
		groups_sort(gi);
	पूर्ण अन्यथा अणु
		gi = get_group_info(rqgi);
	पूर्ण

	अगर (uid_eq(new->fsuid, INVALID_UID))
		new->fsuid = exp->ex_anon_uid;
	अगर (gid_eq(new->fsgid, INVALID_GID))
		new->fsgid = exp->ex_anon_gid;

	set_groups(new, gi);
	put_group_info(gi);

	अगर (!uid_eq(new->fsuid, GLOBAL_ROOT_UID))
		new->cap_effective = cap_drop_nfsd_set(new->cap_effective);
	अन्यथा
		new->cap_effective = cap_उठाओ_nfsd_set(new->cap_effective,
							new->cap_permitted);
	validate_process_creds();
	put_cred(override_creds(new));
	put_cred(new);
	validate_process_creds();
	वापस 0;

oom:
	पात_creds(new);
	वापस -ENOMEM;
पूर्ण

