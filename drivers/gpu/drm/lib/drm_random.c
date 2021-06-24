<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "drm_random.h"

अटल अंतरभूत u32 drm_pअक्रमom_u32_max_state(u32 ep_ro, काष्ठा rnd_state *state)
अणु
	वापस upper_32_bits((u64)pअक्रमom_u32_state(state) * ep_ro);
पूर्ण

व्योम drm_अक्रमom_reorder(अचिन्हित पूर्णांक *order, अचिन्हित पूर्णांक count,
			काष्ठा rnd_state *state)
अणु
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < count; ++i) अणु
		BUILD_BUG_ON(माप(अचिन्हित पूर्णांक) > माप(u32));
		j = drm_pअक्रमom_u32_max_state(count, state);
		swap(order[i], order[j]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_अक्रमom_reorder);

अचिन्हित पूर्णांक *drm_अक्रमom_order(अचिन्हित पूर्णांक count, काष्ठा rnd_state *state)
अणु
	अचिन्हित पूर्णांक *order, i;

	order = kदो_स्मृति_array(count, माप(*order), GFP_KERNEL);
	अगर (!order)
		वापस order;

	क्रम (i = 0; i < count; i++)
		order[i] = i;

	drm_अक्रमom_reorder(order, count, state);
	वापस order;
पूर्ण
EXPORT_SYMBOL(drm_अक्रमom_order);
