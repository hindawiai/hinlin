<शैली गुरु>
/*
 * Copyright IBM Corporation, 2010
 * Author Venkateswararao Jujjuri <jvrao@linux.vnet.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश "trans_common.h"

/**
 * p9_release_pages - Release pages after the transaction.
 * @pages: array of pages to be put
 * @nr_pages: size of array
 */
व्योम p9_release_pages(काष्ठा page **pages, पूर्णांक nr_pages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_pages; i++)
		अगर (pages[i])
			put_page(pages[i]);
पूर्ण
EXPORT_SYMBOL(p9_release_pages);
