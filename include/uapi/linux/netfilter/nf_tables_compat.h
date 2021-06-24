<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _NFT_COMPAT_NFNETLINK_H_
#घोषणा _NFT_COMPAT_NFNETLINK_H_

क्रमागत nft_target_attributes अणु
	NFTA_TARGET_UNSPEC,
	NFTA_TARGET_NAME,
	NFTA_TARGET_REV,
	NFTA_TARGET_INFO,
	__NFTA_TARGET_MAX
पूर्ण;
#घोषणा NFTA_TARGET_MAX		(__NFTA_TARGET_MAX - 1)

क्रमागत nft_match_attributes अणु
	NFTA_MATCH_UNSPEC,
	NFTA_MATCH_NAME,
	NFTA_MATCH_REV,
	NFTA_MATCH_INFO,
	__NFTA_MATCH_MAX
पूर्ण;
#घोषणा NFTA_MATCH_MAX		(__NFTA_MATCH_MAX - 1)

#घोषणा NFT_COMPAT_NAME_MAX	32

क्रमागत अणु
	NFNL_MSG_COMPAT_GET,
	NFNL_MSG_COMPAT_MAX
पूर्ण;

क्रमागत अणु
	NFTA_COMPAT_UNSPEC = 0,
	NFTA_COMPAT_NAME,
	NFTA_COMPAT_REV,
	NFTA_COMPAT_TYPE,
	__NFTA_COMPAT_MAX,
पूर्ण;
#घोषणा NFTA_COMPAT_MAX (__NFTA_COMPAT_MAX - 1)

#पूर्ण_अगर
