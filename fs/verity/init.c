<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs-verity module initialization and logging
 *
 * Copyright 2019 Google LLC
 */

#समावेश "fsverity_private.h"

#समावेश <linux/ratelimit.h>

व्योम fsverity_msg(स्थिर काष्ठा inode *inode, स्थिर अक्षर *level,
		  स्थिर अक्षर *fmt, ...)
अणु
	अटल DEFINE_RATELIMIT_STATE(rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!__ratelimit(&rs))
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	अगर (inode)
		prपूर्णांकk("%sfs-verity (%s, inode %lu): %pV\n",
		       level, inode->i_sb->s_id, inode->i_ino, &vaf);
	अन्यथा
		prपूर्णांकk("%sfs-verity: %pV\n", level, &vaf);
	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक __init fsverity_init(व्योम)
अणु
	पूर्णांक err;

	fsverity_check_hash_algs();

	err = fsverity_init_info_cache();
	अगर (err)
		वापस err;

	err = fsverity_init_workqueue();
	अगर (err)
		जाओ err_निकास_info_cache;

	err = fsverity_init_signature();
	अगर (err)
		जाओ err_निकास_workqueue;

	pr_debug("Initialized fs-verity\n");
	वापस 0;

err_निकास_workqueue:
	fsverity_निकास_workqueue();
err_निकास_info_cache:
	fsverity_निकास_info_cache();
	वापस err;
पूर्ण
late_initcall(fsverity_init)
