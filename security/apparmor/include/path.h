<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor basic path manipulation function definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#अगर_अघोषित __AA_PATH_H
#घोषणा __AA_PATH_H

क्रमागत path_flags अणु
	PATH_IS_सूची = 0x1,		/* path is a directory */
	PATH_CONNECT_PATH = 0x4,	/* connect disconnected paths to / */
	PATH_CHROOT_REL = 0x8,		/* करो path lookup relative to chroot */
	PATH_CHROOT_NSCONNECT = 0x10,	/* connect paths that are at ns root */

	PATH_DELEGATE_DELETED = 0x08000, /* delegate deleted files */
	PATH_MEDIATE_DELETED = 0x10000,	 /* mediate deleted paths */
पूर्ण;

पूर्णांक aa_path_name(स्थिर काष्ठा path *path, पूर्णांक flags, अक्षर *buffer,
		 स्थिर अक्षर **name, स्थिर अक्षर **info,
		 स्थिर अक्षर *disconnected);

#घोषणा IN_ATOMIC true
अक्षर *aa_get_buffer(bool in_atomic);
व्योम aa_put_buffer(अक्षर *buf);

#पूर्ण_अगर /* __AA_PATH_H */
