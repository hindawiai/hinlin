<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause)
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2012 David Gibson, IBM Corporation.
 */
#समावेश "libfdt_env.h"

#समावेश <fdt.h>
#समावेश <libfdt.h>

#समावेश "libfdt_internal.h"

पूर्णांक fdt_create_empty_tree(व्योम *buf, पूर्णांक bufsize)
अणु
	पूर्णांक err;

	err = fdt_create(buf, bufsize);
	अगर (err)
		वापस err;

	err = fdt_finish_reservemap(buf);
	अगर (err)
		वापस err;

	err = fdt_begin_node(buf, "");
	अगर (err)
		वापस err;

	err =  fdt_end_node(buf);
	अगर (err)
		वापस err;

	err = fdt_finish(buf);
	अगर (err)
		वापस err;

	वापस fdt_खोलो_पूर्णांकo(buf, buf, bufsize);
पूर्ण
