<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * pkey table
 *
 * SELinux must keep a mapping of pkeys to labels/SIDs.  This
 * mapping is मुख्यtained as part of the normal policy but a fast cache is
 * needed to reduce the lookup overhead.
 */

/*
 * (c) Mellanox Technologies, 2016
 */

#अगर_अघोषित _SELINUX_IB_PKEY_H
#घोषणा _SELINUX_IB_PKEY_H

#अगर_घोषित CONFIG_SECURITY_INFINIBAND
व्योम sel_ib_pkey_flush(व्योम);
पूर्णांक sel_ib_pkey_sid(u64 subnet_prefix, u16 pkey, u32 *sid);
#अन्यथा
अटल अंतरभूत व्योम sel_ib_pkey_flush(व्योम)
अणु
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक sel_ib_pkey_sid(u64 subnet_prefix, u16 pkey, u32 *sid)
अणु
	*sid = SECINITSID_UNLABELED;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
