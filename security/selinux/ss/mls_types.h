<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Type definitions क्रम the multi-level security (MLS) policy.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
/*
 * Updated: Trusted Computer Solutions, Inc. <dgoeddel@trustedcs.com>
 *
 *	Support क्रम enhanced MLS infraकाष्ठाure.
 *
 * Copyright (C) 2004-2005 Trusted Computer Solutions, Inc.
 */

#अगर_अघोषित _SS_MLS_TYPES_H_
#घोषणा _SS_MLS_TYPES_H_

#समावेश "security.h"
#समावेश "ebitmap.h"

काष्ठा mls_level अणु
	u32 sens;		/* sensitivity */
	काष्ठा ebiपंचांगap cat;	/* category set */
पूर्ण;

काष्ठा mls_range अणु
	काष्ठा mls_level level[2]; /* low == level[0], high == level[1] */
पूर्ण;

अटल अंतरभूत पूर्णांक mls_level_eq(काष्ठा mls_level *l1, काष्ठा mls_level *l2)
अणु
	वापस ((l1->sens == l2->sens) &&
		ebiपंचांगap_cmp(&l1->cat, &l2->cat));
पूर्ण

अटल अंतरभूत पूर्णांक mls_level_करोm(काष्ठा mls_level *l1, काष्ठा mls_level *l2)
अणु
	वापस ((l1->sens >= l2->sens) &&
		ebiपंचांगap_contains(&l1->cat, &l2->cat, 0));
पूर्ण

#घोषणा mls_level_incomp(l1, l2) \
(!mls_level_करोm((l1), (l2)) && !mls_level_करोm((l2), (l1)))

#घोषणा mls_level_between(l1, l2, l3) \
(mls_level_करोm((l1), (l2)) && mls_level_करोm((l3), (l1)))

#घोषणा mls_range_contains(r1, r2) \
(mls_level_करोm(&(r2).level[0], &(r1).level[0]) && \
 mls_level_करोm(&(r1).level[1], &(r2).level[1]))

#पूर्ण_अगर	/* _SS_MLS_TYPES_H_ */
