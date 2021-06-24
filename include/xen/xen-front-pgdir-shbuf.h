<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 * Xen frontend/backend page directory based shared buffer
 * helper module.
 *
 * Copyright (C) 2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_FRONT_PGसूची_SHBUF_H_
#घोषणा __XEN_FRONT_PGसूची_SHBUF_H_

#समावेश <linux/kernel.h>

#समावेश <xen/grant_table.h>

काष्ठा xen_front_pgdir_shbuf_ops;

काष्ठा xen_front_pgdir_shbuf अणु
	/*
	 * Number of references granted क्रम the backend use:
	 *
	 *  - क्रम frontend allocated/imported buffers this holds the number
	 *    of grant references क्रम the page directory and the pages
	 *    of the buffer
	 *
	 *  - क्रम the buffer provided by the backend this only holds the number
	 *    of grant references क्रम the page directory itself as grant
	 *    references क्रम the buffer will be provided by the backend.
	 */
	पूर्णांक num_grefs;
	grant_ref_t *grefs;
	/* Page directory backing storage. */
	u8 *directory;

	/*
	 * Number of pages क्रम the shared buffer itself (excluding the page
	 * directory).
	 */
	पूर्णांक num_pages;
	/*
	 * Backing storage of the shared buffer: these are the pages being
	 * shared.
	 */
	काष्ठा page **pages;

	काष्ठा xenbus_device *xb_dev;

	/* These are the ops used पूर्णांकernally depending on be_alloc mode. */
	स्थिर काष्ठा xen_front_pgdir_shbuf_ops *ops;

	/* Xen map handles क्रम the buffer allocated by the backend. */
	grant_handle_t *backend_map_handles;
पूर्ण;

काष्ठा xen_front_pgdir_shbuf_cfg अणु
	काष्ठा xenbus_device *xb_dev;

	/* Number of pages of the buffer backing storage. */
	पूर्णांक num_pages;
	/* Pages of the buffer to be shared. */
	काष्ठा page **pages;

	/*
	 * This is allocated outside because there are use-हालs when
	 * the buffer काष्ठाure is allocated as a part of a bigger one.
	 */
	काष्ठा xen_front_pgdir_shbuf *pgdir;
	/*
	 * Mode of grant reference sharing: अगर set then backend will share
	 * grant references to the buffer with the frontend.
	 */
	पूर्णांक be_alloc;
पूर्ण;

पूर्णांक xen_front_pgdir_shbuf_alloc(काष्ठा xen_front_pgdir_shbuf_cfg *cfg);

grant_ref_t
xen_front_pgdir_shbuf_get_dir_start(काष्ठा xen_front_pgdir_shbuf *buf);

पूर्णांक xen_front_pgdir_shbuf_map(काष्ठा xen_front_pgdir_shbuf *buf);

पूर्णांक xen_front_pgdir_shbuf_unmap(काष्ठा xen_front_pgdir_shbuf *buf);

व्योम xen_front_pgdir_shbuf_मुक्त(काष्ठा xen_front_pgdir_shbuf *buf);

#पूर्ण_अगर /* __XEN_FRONT_PGसूची_SHBUF_H_ */
