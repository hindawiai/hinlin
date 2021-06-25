<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause)
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2014 David Gibson <david@gibson.dropbear.id.au>
 * Copyright (C) 2018 embedded brains GmbH
 */
#समावेश "libfdt_env.h"

#समावेश <fdt.h>
#समावेश <libfdt.h>

#समावेश "libfdt_internal.h"

अटल पूर्णांक fdt_cells(स्थिर व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name)
अणु
	स्थिर fdt32_t *c;
	uपूर्णांक32_t val;
	पूर्णांक len;

	c = fdt_getprop(fdt, nodeoffset, name, &len);
	अगर (!c)
		वापस len;

	अगर (len != माप(*c))
		वापस -FDT_ERR_BADNCELLS;

	val = fdt32_to_cpu(*c);
	अगर (val > FDT_MAX_NCELLS)
		वापस -FDT_ERR_BADNCELLS;

	वापस (पूर्णांक)val;
पूर्ण

पूर्णांक fdt_address_cells(स्थिर व्योम *fdt, पूर्णांक nodeoffset)
अणु
	पूर्णांक val;

	val = fdt_cells(fdt, nodeoffset, "#address-cells");
	अगर (val == 0)
		वापस -FDT_ERR_BADNCELLS;
	अगर (val == -FDT_ERR_NOTFOUND)
		वापस 2;
	वापस val;
पूर्ण

पूर्णांक fdt_size_cells(स्थिर व्योम *fdt, पूर्णांक nodeoffset)
अणु
	पूर्णांक val;

	val = fdt_cells(fdt, nodeoffset, "#size-cells");
	अगर (val == -FDT_ERR_NOTFOUND)
		वापस 1;
	वापस val;
पूर्ण

/* This function assumes that [address|size]_cells is 1 or 2 */
पूर्णांक fdt_appendprop_addrrange(व्योम *fdt, पूर्णांक parent, पूर्णांक nodeoffset,
			     स्थिर अक्षर *name, uपूर्णांक64_t addr, uपूर्णांक64_t size)
अणु
	पूर्णांक addr_cells, size_cells, ret;
	uपूर्णांक8_t data[माप(fdt64_t) * 2], *prop;

	ret = fdt_address_cells(fdt, parent);
	अगर (ret < 0)
		वापस ret;
	addr_cells = ret;

	ret = fdt_size_cells(fdt, parent);
	अगर (ret < 0)
		वापस ret;
	size_cells = ret;

	/* check validity of address */
	prop = data;
	अगर (addr_cells == 1) अणु
		अगर ((addr > UINT32_MAX) || ((UINT32_MAX + 1 - addr) < size))
			वापस -FDT_ERR_BADVALUE;

		fdt32_st(prop, (uपूर्णांक32_t)addr);
	पूर्ण अन्यथा अगर (addr_cells == 2) अणु
		fdt64_st(prop, addr);
	पूर्ण अन्यथा अणु
		वापस -FDT_ERR_BADNCELLS;
	पूर्ण

	/* check validity of size */
	prop += addr_cells * माप(fdt32_t);
	अगर (size_cells == 1) अणु
		अगर (size > UINT32_MAX)
			वापस -FDT_ERR_BADVALUE;

		fdt32_st(prop, (uपूर्णांक32_t)size);
	पूर्ण अन्यथा अगर (size_cells == 2) अणु
		fdt64_st(prop, size);
	पूर्ण अन्यथा अणु
		वापस -FDT_ERR_BADNCELLS;
	पूर्ण

	वापस fdt_appendprop(fdt, nodeoffset, name, data,
			      (addr_cells + size_cells) * माप(fdt32_t));
पूर्ण
