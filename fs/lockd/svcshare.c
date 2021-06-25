<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/lockd/svcshare.c
 *
 * Management of DOS shares.
 *
 * Copyright (C) 1996 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/समय.स>
#समावेश <linux/unistd.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/lockd/lockd.h>
#समावेश <linux/lockd/share.h>

अटल अंतरभूत पूर्णांक
nlm_cmp_owner(काष्ठा nlm_share *share, काष्ठा xdr_netobj *oh)
अणु
	वापस share->s_owner.len == oh->len
	    && !स_भेद(share->s_owner.data, oh->data, oh->len);
पूर्ण

__be32
nlmsvc_share_file(काष्ठा nlm_host *host, काष्ठा nlm_file *file,
			काष्ठा nlm_args *argp)
अणु
	काष्ठा nlm_share	*share;
	काष्ठा xdr_netobj	*oh = &argp->lock.oh;
	u8			*ohdata;

	क्रम (share = file->f_shares; share; share = share->s_next) अणु
		अगर (share->s_host == host && nlm_cmp_owner(share, oh))
			जाओ update;
		अगर ((argp->fsm_access & share->s_mode)
		 || (argp->fsm_mode   & share->s_access ))
			वापस nlm_lck_denied;
	पूर्ण

	share = kदो_स्मृति(माप(*share) + oh->len,
						GFP_KERNEL);
	अगर (share == शून्य)
		वापस nlm_lck_denied_nolocks;

	/* Copy owner handle */
	ohdata = (u8 *) (share + 1);
	स_नकल(ohdata, oh->data, oh->len);

	share->s_file	    = file;
	share->s_host       = host;
	share->s_owner.data = ohdata;
	share->s_owner.len  = oh->len;
	share->s_next       = file->f_shares;
	file->f_shares      = share;

update:
	share->s_access = argp->fsm_access;
	share->s_mode   = argp->fsm_mode;
	वापस nlm_granted;
पूर्ण

/*
 * Delete a share.
 */
__be32
nlmsvc_unshare_file(काष्ठा nlm_host *host, काष्ठा nlm_file *file,
			काष्ठा nlm_args *argp)
अणु
	काष्ठा nlm_share	*share, **shpp;
	काष्ठा xdr_netobj	*oh = &argp->lock.oh;

	क्रम (shpp = &file->f_shares; (share = *shpp) != शून्य;
					shpp = &share->s_next) अणु
		अगर (share->s_host == host && nlm_cmp_owner(share, oh)) अणु
			*shpp = share->s_next;
			kमुक्त(share);
			वापस nlm_granted;
		पूर्ण
	पूर्ण

	/* X/Open spec says वापस success even अगर there was no
	 * corresponding share. */
	वापस nlm_granted;
पूर्ण

/*
 * Traverse all shares क्रम a given file, and delete
 * those owned by the given (type of) host
 */
व्योम nlmsvc_traverse_shares(काष्ठा nlm_host *host, काष्ठा nlm_file *file,
		nlm_host_match_fn_t match)
अणु
	काष्ठा nlm_share	*share, **shpp;

	shpp = &file->f_shares;
	जबतक ((share = *shpp) !=  शून्य) अणु
		अगर (match(share->s_host, host)) अणु
			*shpp = share->s_next;
			kमुक्त(share);
			जारी;
		पूर्ण
		shpp = &share->s_next;
	पूर्ण
पूर्ण
