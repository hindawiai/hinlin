<शैली गुरु>
/*
 * Copyright (C) 2004 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 *
 * Multipath.
 */

#अगर_अघोषित	DM_MPATH_H
#घोषणा	DM_MPATH_H

काष्ठा dm_dev;

काष्ठा dm_path अणु
	काष्ठा dm_dev *dev;	/* Read-only */
	व्योम *pscontext;	/* For path-selector use */
पूर्ण;

/* Callback क्रम hwh_pg_init_fn to use when complete */
व्योम dm_pg_init_complete(काष्ठा dm_path *path, अचिन्हित err_flags);

#पूर्ण_अगर
