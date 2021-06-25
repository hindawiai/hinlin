<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_OWNER_MATCH_H
#घोषणा _XT_OWNER_MATCH_H

#समावेश <linux/types.h>

क्रमागत अणु
	XT_OWNER_UID          = 1 << 0,
	XT_OWNER_GID          = 1 << 1,
	XT_OWNER_SOCKET       = 1 << 2,
	XT_OWNER_SUPPL_GROUPS = 1 << 3,
पूर्ण;

#घोषणा XT_OWNER_MASK	(XT_OWNER_UID | 	\
			 XT_OWNER_GID | 	\
			 XT_OWNER_SOCKET |	\
			 XT_OWNER_SUPPL_GROUPS)

काष्ठा xt_owner_match_info अणु
	__u32 uid_min, uid_max;
	__u32 gid_min, gid_max;
	__u8 match, invert;
पूर्ण;

#पूर्ण_अगर /* _XT_OWNER_MATCH_H */
