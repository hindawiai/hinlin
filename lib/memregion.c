<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* identअगरiers क्रम device / perक्रमmance-dअगरferentiated memory regions */
#समावेश <linux/idr.h>
#समावेश <linux/types.h>
#समावेश <linux/memregion.h>

अटल DEFINE_IDA(memregion_ids);

पूर्णांक memregion_alloc(gfp_t gfp)
अणु
	वापस ida_alloc(&memregion_ids, gfp);
पूर्ण
EXPORT_SYMBOL(memregion_alloc);

व्योम memregion_मुक्त(पूर्णांक id)
अणु
	ida_मुक्त(&memregion_ids, id);
पूर्ण
EXPORT_SYMBOL(memregion_मुक्त);
