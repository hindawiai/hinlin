<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause)
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2006 David Gibson, IBM Corporation.
 */
#समावेश "libfdt_env.h"

#समावेश <fdt.h>
#समावेश <libfdt.h>

#समावेश "libfdt_internal.h"

पूर्णांक fdt_setprop_inplace_namelen_partial(व्योम *fdt, पूर्णांक nodeoffset,
					स्थिर अक्षर *name, पूर्णांक namelen,
					uपूर्णांक32_t idx, स्थिर व्योम *val,
					पूर्णांक len)
अणु
	व्योम *propval;
	पूर्णांक proplen;

	propval = fdt_getprop_namelen_w(fdt, nodeoffset, name, namelen,
					&proplen);
	अगर (!propval)
		वापस proplen;

	अगर ((अचिन्हित)proplen < (len + idx))
		वापस -FDT_ERR_NOSPACE;

	स_नकल((अक्षर *)propval + idx, val, len);
	वापस 0;
पूर्ण

पूर्णांक fdt_setprop_inplace(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
			स्थिर व्योम *val, पूर्णांक len)
अणु
	स्थिर व्योम *propval;
	पूर्णांक proplen;

	propval = fdt_getprop(fdt, nodeoffset, name, &proplen);
	अगर (!propval)
		वापस proplen;

	अगर (proplen != len)
		वापस -FDT_ERR_NOSPACE;

	वापस fdt_setprop_inplace_namelen_partial(fdt, nodeoffset, name,
						   म_माप(name), 0,
						   val, len);
पूर्ण

अटल व्योम fdt_nop_region_(व्योम *start, पूर्णांक len)
अणु
	fdt32_t *p;

	क्रम (p = start; (अक्षर *)p < ((अक्षर *)start + len); p++)
		*p = cpu_to_fdt32(FDT_NOP);
पूर्ण

पूर्णांक fdt_nop_property(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name)
अणु
	काष्ठा fdt_property *prop;
	पूर्णांक len;

	prop = fdt_get_property_w(fdt, nodeoffset, name, &len);
	अगर (!prop)
		वापस len;

	fdt_nop_region_(prop, len + माप(*prop));

	वापस 0;
पूर्ण

पूर्णांक fdt_node_end_offset_(व्योम *fdt, पूर्णांक offset)
अणु
	पूर्णांक depth = 0;

	जबतक ((offset >= 0) && (depth >= 0))
		offset = fdt_next_node(fdt, offset, &depth);

	वापस offset;
पूर्ण

पूर्णांक fdt_nop_node(व्योम *fdt, पूर्णांक nodeoffset)
अणु
	पूर्णांक enकरोffset;

	enकरोffset = fdt_node_end_offset_(fdt, nodeoffset);
	अगर (enकरोffset < 0)
		वापस enकरोffset;

	fdt_nop_region_(fdt_offset_ptr_w(fdt, nodeoffset, 0),
			enकरोffset - nodeoffset);
	वापस 0;
पूर्ण
