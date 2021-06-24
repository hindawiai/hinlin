<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2020 ARM Limited */

/*
 * Below definitions may be found in kernel headers, However, they are
 * redefined here to decouple the MTE selftests compilations from them.
 */
#अगर_अघोषित SEGV_MTEAERR
#घोषणा	SEGV_MTEAERR	8
#पूर्ण_अगर
#अगर_अघोषित SEGV_MTESERR
#घोषणा	SEGV_MTESERR	9
#पूर्ण_अगर
#अगर_अघोषित PROT_MTE
#घोषणा PROT_MTE	 0x20
#पूर्ण_अगर
#अगर_अघोषित HWCAP2_MTE
#घोषणा HWCAP2_MTE	(1 << 18)
#पूर्ण_अगर

#अगर_अघोषित PR_MTE_TCF_SHIFT
#घोषणा PR_MTE_TCF_SHIFT	1
#पूर्ण_अगर
#अगर_अघोषित PR_MTE_TCF_NONE
#घोषणा PR_MTE_TCF_NONE		(0UL << PR_MTE_TCF_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित PR_MTE_TCF_SYNC
#घोषणा	PR_MTE_TCF_SYNC		(1UL << PR_MTE_TCF_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित PR_MTE_TCF_ASYNC
#घोषणा PR_MTE_TCF_ASYNC	(2UL << PR_MTE_TCF_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित PR_MTE_TAG_SHIFT
#घोषणा	PR_MTE_TAG_SHIFT	3
#पूर्ण_अगर

/* MTE Hardware feature definitions below. */
#घोषणा MT_TAG_SHIFT		56
#घोषणा MT_TAG_MASK		0xFUL
#घोषणा MT_FREE_TAG		0x0UL
#घोषणा MT_GRANULE_SIZE         16
#घोषणा MT_TAG_COUNT		16
#घोषणा MT_INCLUDE_TAG_MASK	0xFFFF
#घोषणा MT_EXCLUDE_TAG_MASK	0x0

#घोषणा MT_ALIGN_GRANULE	(MT_GRANULE_SIZE - 1)
#घोषणा MT_CLEAR_TAG(x)		((x) & ~(MT_TAG_MASK << MT_TAG_SHIFT))
#घोषणा MT_SET_TAG(x, y)	((x) | (y << MT_TAG_SHIFT))
#घोषणा MT_FETCH_TAG(x)		((x >> MT_TAG_SHIFT) & (MT_TAG_MASK))
#घोषणा MT_ALIGN_UP(x)		((x + MT_ALIGN_GRANULE) & ~(MT_ALIGN_GRANULE))

#घोषणा MT_PSTATE_TCO_SHIFT	25
#घोषणा MT_PSTATE_TCO_MASK	~(0x1 << MT_PSTATE_TCO_SHIFT)
#घोषणा MT_PSTATE_TCO_EN	1
#घोषणा MT_PSTATE_TCO_DIS	0

#घोषणा MT_EXCLUDE_TAG(x)		(1 << (x))
#घोषणा MT_INCLUDE_VALID_TAG(x)		(MT_INCLUDE_TAG_MASK ^ MT_EXCLUDE_TAG(x))
#घोषणा MT_INCLUDE_VALID_TAGS(x)	(MT_INCLUDE_TAG_MASK ^ (x))
#घोषणा MTE_ALLOW_NON_ZERO_TAG		MT_INCLUDE_VALID_TAG(0)
