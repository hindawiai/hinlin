<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rsrc_iodyn.c -- Resource management routines क्रम MEM-अटल sockets.
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999		David A. Hinds
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <pcmcia/ss.h>
#समावेश <pcmcia/cistpl.h>
#समावेश "cs_internal.h"


काष्ठा pcmcia_align_data अणु
	अचिन्हित दीर्घ	mask;
	अचिन्हित दीर्घ	offset;
पूर्ण;

अटल resource_माप_प्रकार pcmcia_align(व्योम *align_data,
				स्थिर काष्ठा resource *res,
				resource_माप_प्रकार size, resource_माप_प्रकार align)
अणु
	काष्ठा pcmcia_align_data *data = align_data;
	resource_माप_प्रकार start;

	start = (res->start & ~data->mask) + data->offset;
	अगर (start < res->start)
		start += data->mask + 1;

#अगर_घोषित CONFIG_X86
	अगर (res->flags & IORESOURCE_IO) अणु
		अगर (start & 0x300)
			start = (start + 0x3ff) & ~0x3ff;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_M68K
	अगर (res->flags & IORESOURCE_IO) अणु
		अगर ((res->start + size - 1) >= 1024)
			start = res->end;
	पूर्ण
#पूर्ण_अगर

	वापस start;
पूर्ण


अटल काष्ठा resource *__iodyn_find_io_region(काष्ठा pcmcia_socket *s,
					अचिन्हित दीर्घ base, पूर्णांक num,
					अचिन्हित दीर्घ align)
अणु
	काष्ठा resource *res = pcmcia_make_resource(0, num, IORESOURCE_IO,
						dev_name(&s->dev));
	काष्ठा pcmcia_align_data data;
	अचिन्हित दीर्घ min = base;
	पूर्णांक ret;

	data.mask = align - 1;
	data.offset = base & data.mask;

#अगर_घोषित CONFIG_PCI
	अगर (s->cb_dev) अणु
		ret = pci_bus_alloc_resource(s->cb_dev->bus, res, num, 1,
					     min, 0, pcmcia_align, &data);
	पूर्ण अन्यथा
#पूर्ण_अगर
		ret = allocate_resource(&ioport_resource, res, num, min, ~0UL,
					1, pcmcia_align, &data);

	अगर (ret != 0) अणु
		kमुक्त(res);
		res = शून्य;
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक iodyn_find_io(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक attr,
			अचिन्हित पूर्णांक *base, अचिन्हित पूर्णांक num,
			अचिन्हित पूर्णांक align, काष्ठा resource **parent)
अणु
	पूर्णांक i, ret = 0;

	/* Check क्रम an alपढ़ोy-allocated winकरोw that must conflict with
	 * what was asked क्रम.  It is a hack because it करोes not catch all
	 * potential conflicts, just the most obvious ones.
	 */
	क्रम (i = 0; i < MAX_IO_WIN; i++) अणु
		अगर (!s->io[i].res)
			जारी;

		अगर (!*base)
			जारी;

		अगर ((s->io[i].res->start & (align-1)) == *base)
			वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < MAX_IO_WIN; i++) अणु
		काष्ठा resource *res = s->io[i].res;
		अचिन्हित पूर्णांक try;

		अगर (res && (res->flags & IORESOURCE_BITS) !=
			(attr & IORESOURCE_BITS))
			जारी;

		अगर (!res) अणु
			अगर (align == 0)
				align = 0x10000;

			res = s->io[i].res = __iodyn_find_io_region(s, *base,
								num, align);
			अगर (!res)
				वापस -EINVAL;

			*base = res->start;
			s->io[i].res->flags =
				((res->flags & ~IORESOURCE_BITS) |
					(attr & IORESOURCE_BITS));
			s->io[i].InUse = num;
			*parent = res;
			वापस 0;
		पूर्ण

		/* Try to extend top of winकरोw */
		try = res->end + 1;
		अगर ((*base == 0) || (*base == try)) अणु
			अगर (adjust_resource(s->io[i].res, res->start,
					    resource_size(res) + num))
				जारी;
			*base = try;
			s->io[i].InUse += num;
			*parent = res;
			वापस 0;
		पूर्ण

		/* Try to extend bottom of winकरोw */
		try = res->start - num;
		अगर ((*base == 0) || (*base == try)) अणु
			अगर (adjust_resource(s->io[i].res,
					    res->start - num,
					    resource_size(res) + num))
				जारी;
			*base = try;
			s->io[i].InUse += num;
			*parent = res;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण


काष्ठा pccard_resource_ops pccard_iodyn_ops = अणु
	.validate_mem = शून्य,
	.find_io = iodyn_find_io,
	.find_mem = शून्य,
	.init = अटल_init,
	.निकास = शून्य,
पूर्ण;
EXPORT_SYMBOL(pccard_iodyn_ops);
