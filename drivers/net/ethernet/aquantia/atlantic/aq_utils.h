<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * aQuantia Corporation Network Driver
 * Copyright (C) 2014-2017 aQuantia Corporation. All rights reserved
 */

/* File aq_utils.h: Useful macro and काष्ठाures used in all layers of driver. */

#अगर_अघोषित AQ_UTILS_H
#घोषणा AQ_UTILS_H

#समावेश "aq_common.h"

अटल अंतरभूत व्योम aq_utils_obj_set(atomic_t *flags, u32 mask)
अणु
	अचिन्हित दीर्घ flags_old, flags_new;

	करो अणु
		flags_old = atomic_पढ़ो(flags);
		flags_new = flags_old | (mask);
	पूर्ण जबतक (atomic_cmpxchg(flags, flags_old, flags_new) != flags_old);
पूर्ण

अटल अंतरभूत व्योम aq_utils_obj_clear(atomic_t *flags, u32 mask)
अणु
	अचिन्हित दीर्घ flags_old, flags_new;

	करो अणु
		flags_old = atomic_पढ़ो(flags);
		flags_new = flags_old & ~(mask);
	पूर्ण जबतक (atomic_cmpxchg(flags, flags_old, flags_new) != flags_old);
पूर्ण

अटल अंतरभूत bool aq_utils_obj_test(atomic_t *flags, u32 mask)
अणु
	वापस atomic_पढ़ो(flags) & mask;
पूर्ण

#पूर्ण_अगर /* AQ_UTILS_H */
