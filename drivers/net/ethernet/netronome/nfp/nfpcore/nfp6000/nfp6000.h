<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2017 Netronome Systems, Inc. */

#अगर_अघोषित NFP6000_NFP6000_H
#घोषणा NFP6000_NFP6000_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

/* CPP Target IDs */
#घोषणा NFP_CPP_TARGET_INVALID          0
#घोषणा NFP_CPP_TARGET_NBI              1
#घोषणा NFP_CPP_TARGET_QDR              2
#घोषणा NFP_CPP_TARGET_ILA              6
#घोषणा NFP_CPP_TARGET_MU               7
#घोषणा NFP_CPP_TARGET_PCIE             9
#घोषणा NFP_CPP_TARGET_ARM              10
#घोषणा NFP_CPP_TARGET_CRYPTO           12
#घोषणा NFP_CPP_TARGET_ISLAND_XPB       14      /* Shared with CAP */
#घोषणा NFP_CPP_TARGET_ISLAND_CAP       14      /* Shared with XPB */
#घोषणा NFP_CPP_TARGET_CT_XPB           14
#घोषणा NFP_CPP_TARGET_LOCAL_SCRATCH    15
#घोषणा NFP_CPP_TARGET_CLS              NFP_CPP_TARGET_LOCAL_SCRATCH

#घोषणा NFP_ISL_EMEM0			24

#घोषणा NFP_MU_ADDR_ACCESS_TYPE_MASK	3ULL
#घोषणा NFP_MU_ADDR_ACCESS_TYPE_सूचीECT	2ULL

#घोषणा PUSHPULL(_pull, _push)		((_pull) << 4 | (_push) << 0)
#घोषणा PUSH_WIDTH(_pushpull)		pushpull_width((_pushpull) >> 0)
#घोषणा PULL_WIDTH(_pushpull)		pushpull_width((_pushpull) >> 4)

अटल अंतरभूत पूर्णांक pushpull_width(पूर्णांक pp)
अणु
	pp &= 0xf;

	अगर (pp == 0)
		वापस -EINVAL;
	वापस 2 << pp;
पूर्ण

अटल अंतरभूत पूर्णांक nfp_cppat_mu_locality_lsb(पूर्णांक mode, bool addr40)
अणु
	चयन (mode) अणु
	हाल 0 ... 3:
		वापस addr40 ? 38 : 30;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक nfp_target_pushpull(u32 cpp_id, u64 address);
पूर्णांक nfp_target_cpp(u32 cpp_island_id, u64 cpp_island_address,
		   u32 *cpp_target_id, u64 *cpp_target_address,
		   स्थिर u32 *imb_table);

#पूर्ण_अगर /* NFP6000_NFP6000_H */
