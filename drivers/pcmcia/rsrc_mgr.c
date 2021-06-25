<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rsrc_mgr.c -- Resource management routines and/or wrappers
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

पूर्णांक अटल_init(काष्ठा pcmcia_socket *s)
अणु
	/* the good thing about SS_CAP_STATIC_MAP sockets is
	 * that they करोn't need a resource database */

	s->resource_setup_करोne = 1;

	वापस 0;
पूर्ण

काष्ठा resource *pcmcia_make_resource(resource_माप_प्रकार start,
					resource_माप_प्रकार end,
					अचिन्हित दीर्घ flags, स्थिर अक्षर *name)
अणु
	काष्ठा resource *res = kzalloc(माप(*res), GFP_KERNEL);

	अगर (res) अणु
		res->name = name;
		res->start = start;
		res->end = start + end - 1;
		res->flags = flags;
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक अटल_find_io(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक attr,
			अचिन्हित पूर्णांक *base, अचिन्हित पूर्णांक num,
			अचिन्हित पूर्णांक align, काष्ठा resource **parent)
अणु
	अगर (!s->io_offset)
		वापस -EINVAL;
	*base = s->io_offset | (*base & 0x0fff);
	*parent = शून्य;

	वापस 0;
पूर्ण


काष्ठा pccard_resource_ops pccard_अटल_ops = अणु
	.validate_mem = शून्य,
	.find_io = अटल_find_io,
	.find_mem = शून्य,
	.init = अटल_init,
	.निकास = शून्य,
पूर्ण;
EXPORT_SYMBOL(pccard_अटल_ops);


MODULE_AUTHOR("David A. Hinds, Dominik Brodowski");
MODULE_LICENSE("GPL");
MODULE_ALIAS("rsrc_nonstatic");
