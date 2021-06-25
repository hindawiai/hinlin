<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mtd/mtd.h>
#समावेश "nodelist.h"

पूर्णांक jffs2_flash_direct_ग_लिखोv(काष्ठा jffs2_sb_info *c, स्थिर काष्ठा kvec *vecs,
			      अचिन्हित दीर्घ count, loff_t to, माप_प्रकार *retlen)
अणु
	अगर (!jffs2_is_ग_लिखोbuffered(c)) अणु
		अगर (jffs2_sum_active()) अणु
			पूर्णांक res;
			res = jffs2_sum_add_kvec(c, vecs, count, (uपूर्णांक32_t) to);
			अगर (res) अणु
				वापस res;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस mtd_ग_लिखोv(c->mtd, vecs, count, to, retlen);
पूर्ण

पूर्णांक jffs2_flash_direct_ग_लिखो(काष्ठा jffs2_sb_info *c, loff_t ofs, माप_प्रकार len,
			माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	पूर्णांक ret;
	ret = mtd_ग_लिखो(c->mtd, ofs, len, retlen, buf);

	अगर (jffs2_sum_active()) अणु
		काष्ठा kvec vecs[1];
		पूर्णांक res;

		vecs[0].iov_base = (अचिन्हित अक्षर *) buf;
		vecs[0].iov_len = len;

		res = jffs2_sum_add_kvec(c, vecs, 1, (uपूर्णांक32_t) ofs);
		अगर (res) अणु
			वापस res;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
