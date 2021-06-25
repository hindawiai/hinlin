<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) 2020, Microsoft Corporation.
 *
 *   Author(s): Steve French <stfrench@microsoft.com>
 *              Suresh Jayaraman <sjayaraman@suse.de>
 *              Jeff Layton <jlayton@kernel.org>
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/inet.h>
#समावेश <linux/प्रकार.स>
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"

/* extract the host portion of the UNC string */
अक्षर *extract_hostname(स्थिर अक्षर *unc)
अणु
	स्थिर अक्षर *src;
	अक्षर *dst, *delim;
	अचिन्हित पूर्णांक len;

	/* skip द्विगुन अक्षरs at beginning of string */
	/* BB: check validity of these bytes? */
	अगर (म_माप(unc) < 3)
		वापस ERR_PTR(-EINVAL);
	क्रम (src = unc; *src && *src == '\\'; src++)
		;
	अगर (!*src)
		वापस ERR_PTR(-EINVAL);

	/* delimiter between hostname and shaनाम is always '\\' now */
	delim = म_अक्षर(src, '\\');
	अगर (!delim)
		वापस ERR_PTR(-EINVAL);

	len = delim - src;
	dst = kदो_स्मृति((len + 1), GFP_KERNEL);
	अगर (dst == शून्य)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(dst, src, len);
	dst[len] = '\0';

	वापस dst;
पूर्ण

अक्षर *extract_shaनाम(स्थिर अक्षर *unc)
अणु
	स्थिर अक्षर *src;
	अक्षर *delim, *dst;

	/* skip द्विगुन अक्षरs at the beginning */
	src = unc + 2;

	/* share name is always preceded by '\\' now */
	delim = म_अक्षर(src, '\\');
	अगर (!delim)
		वापस ERR_PTR(-EINVAL);
	delim++;

	/* caller has to मुक्त the memory */
	dst = kstrdup(delim, GFP_KERNEL);
	अगर (!dst)
		वापस ERR_PTR(-ENOMEM);

	वापस dst;
पूर्ण
