<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/lockd/share.h
 *
 * DOS share management क्रम lockd.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित LINUX_LOCKD_SHARE_H
#घोषणा LINUX_LOCKD_SHARE_H

/*
 * DOS share क्रम a specअगरic file
 */
काष्ठा nlm_share अणु
	काष्ठा nlm_share *	s_next;		/* linked list */
	काष्ठा nlm_host *	s_host;		/* client host */
	काष्ठा nlm_file *	s_file;		/* shared file */
	काष्ठा xdr_netobj	s_owner;	/* owner handle */
	u32			s_access;	/* access mode */
	u32			s_mode;		/* deny mode */
पूर्ण;

__be32	nlmsvc_share_file(काष्ठा nlm_host *, काष्ठा nlm_file *,
					       काष्ठा nlm_args *);
__be32	nlmsvc_unshare_file(काष्ठा nlm_host *, काष्ठा nlm_file *,
					       काष्ठा nlm_args *);
व्योम	nlmsvc_traverse_shares(काष्ठा nlm_host *, काष्ठा nlm_file *,
					       nlm_host_match_fn_t);

#पूर्ण_अगर /* LINUX_LOCKD_SHARE_H */
