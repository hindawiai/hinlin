<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RomFS storage access routines
 *
 * Copyright तऊ 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/fs.h>
#समावेश <linux/mtd/super.h>
#समावेश <linux/buffer_head.h>
#समावेश "internal.h"

#अगर !defined(CONFIG_ROMFS_ON_MTD) && !defined(CONFIG_ROMFS_ON_BLOCK)
#त्रुटि no ROMFS backing store पूर्णांकerface configured
#पूर्ण_अगर

#अगर_घोषित CONFIG_ROMFS_ON_MTD
#घोषणा ROMFS_MTD_READ(sb, ...) mtd_पढ़ो((sb)->s_mtd, ##__VA_ARGS__)

/*
 * पढ़ो data from an romfs image on an MTD device
 */
अटल पूर्णांक romfs_mtd_पढ़ो(काष्ठा super_block *sb, अचिन्हित दीर्घ pos,
			  व्योम *buf, माप_प्रकार buflen)
अणु
	माप_प्रकार rlen;
	पूर्णांक ret;

	ret = ROMFS_MTD_READ(sb, pos, buflen, &rlen, buf);
	वापस (ret < 0 || rlen != buflen) ? -EIO : 0;
पूर्ण

/*
 * determine the length of a string in a romfs image on an MTD device
 */
अटल sमाप_प्रकार romfs_mtd_strnlen(काष्ठा super_block *sb,
				 अचिन्हित दीर्घ pos, माप_प्रकार maxlen)
अणु
	sमाप_प्रकार n = 0;
	माप_प्रकार segment;
	u_अक्षर buf[16], *p;
	माप_प्रकार len;
	पूर्णांक ret;

	/* scan the string up to 16 bytes at a समय */
	जबतक (maxlen > 0) अणु
		segment = min_t(माप_प्रकार, maxlen, 16);
		ret = ROMFS_MTD_READ(sb, pos, segment, &len, buf);
		अगर (ret < 0)
			वापस ret;
		p = स_प्रथम(buf, 0, len);
		अगर (p)
			वापस n + (p - buf);
		maxlen -= len;
		pos += len;
		n += len;
	पूर्ण

	वापस n;
पूर्ण

/*
 * compare a string to one in a romfs image on MTD
 * - वापस 1 अगर matched, 0 अगर dअगरfer, -ve अगर error
 */
अटल पूर्णांक romfs_mtd_म_भेद(काष्ठा super_block *sb, अचिन्हित दीर्घ pos,
			    स्थिर अक्षर *str, माप_प्रकार size)
अणु
	u_अक्षर buf[17];
	माप_प्रकार len, segment;
	पूर्णांक ret;

	/* scan the string up to 16 bytes at a समय, and attempt to grab the
	 * trailing NUL whilst we're at it */
	buf[0] = 0xff;

	जबतक (size > 0) अणु
		segment = min_t(माप_प्रकार, size + 1, 17);
		ret = ROMFS_MTD_READ(sb, pos, segment, &len, buf);
		अगर (ret < 0)
			वापस ret;
		len--;
		अगर (स_भेद(buf, str, len) != 0)
			वापस 0;
		buf[0] = buf[len];
		size -= len;
		pos += len;
		str += len;
	पूर्ण

	/* check the trailing NUL was */
	अगर (buf[0])
		वापस 0;

	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_ROMFS_ON_MTD */

#अगर_घोषित CONFIG_ROMFS_ON_BLOCK
/*
 * पढ़ो data from an romfs image on a block device
 */
अटल पूर्णांक romfs_blk_पढ़ो(काष्ठा super_block *sb, अचिन्हित दीर्घ pos,
			  व्योम *buf, माप_प्रकार buflen)
अणु
	काष्ठा buffer_head *bh;
	अचिन्हित दीर्घ offset;
	माप_प्रकार segment;

	/* copy the string up to blocksize bytes at a समय */
	जबतक (buflen > 0) अणु
		offset = pos & (ROMBSIZE - 1);
		segment = min_t(माप_प्रकार, buflen, ROMBSIZE - offset);
		bh = sb_bपढ़ो(sb, pos >> ROMBSBITS);
		अगर (!bh)
			वापस -EIO;
		स_नकल(buf, bh->b_data + offset, segment);
		brअन्यथा(bh);
		buf += segment;
		buflen -= segment;
		pos += segment;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * determine the length of a string in romfs on a block device
 */
अटल sमाप_प्रकार romfs_blk_strnlen(काष्ठा super_block *sb,
				 अचिन्हित दीर्घ pos, माप_प्रकार limit)
अणु
	काष्ठा buffer_head *bh;
	अचिन्हित दीर्घ offset;
	sमाप_प्रकार n = 0;
	माप_प्रकार segment;
	u_अक्षर *buf, *p;

	/* scan the string up to blocksize bytes at a समय */
	जबतक (limit > 0) अणु
		offset = pos & (ROMBSIZE - 1);
		segment = min_t(माप_प्रकार, limit, ROMBSIZE - offset);
		bh = sb_bपढ़ो(sb, pos >> ROMBSBITS);
		अगर (!bh)
			वापस -EIO;
		buf = bh->b_data + offset;
		p = स_प्रथम(buf, 0, segment);
		brअन्यथा(bh);
		अगर (p)
			वापस n + (p - buf);
		limit -= segment;
		pos += segment;
		n += segment;
	पूर्ण

	वापस n;
पूर्ण

/*
 * compare a string to one in a romfs image on a block device
 * - वापस 1 अगर matched, 0 अगर dअगरfer, -ve अगर error
 */
अटल पूर्णांक romfs_blk_म_भेद(काष्ठा super_block *sb, अचिन्हित दीर्घ pos,
			    स्थिर अक्षर *str, माप_प्रकार size)
अणु
	काष्ठा buffer_head *bh;
	अचिन्हित दीर्घ offset;
	माप_प्रकार segment;
	bool matched, terminated = false;

	/* compare string up to a block at a समय */
	जबतक (size > 0) अणु
		offset = pos & (ROMBSIZE - 1);
		segment = min_t(माप_प्रकार, size, ROMBSIZE - offset);
		bh = sb_bपढ़ो(sb, pos >> ROMBSBITS);
		अगर (!bh)
			वापस -EIO;
		matched = (स_भेद(bh->b_data + offset, str, segment) == 0);

		size -= segment;
		pos += segment;
		str += segment;
		अगर (matched && size == 0 && offset + segment < ROMBSIZE) अणु
			अगर (!bh->b_data[offset + segment])
				terminated = true;
			अन्यथा
				matched = false;
		पूर्ण
		brअन्यथा(bh);
		अगर (!matched)
			वापस 0;
	पूर्ण

	अगर (!terminated) अणु
		/* the terminating NUL must be on the first byte of the next
		 * block */
		BUG_ON((pos & (ROMBSIZE - 1)) != 0);
		bh = sb_bपढ़ो(sb, pos >> ROMBSBITS);
		अगर (!bh)
			वापस -EIO;
		matched = !bh->b_data[0];
		brअन्यथा(bh);
		अगर (!matched)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_ROMFS_ON_BLOCK */

/*
 * पढ़ो data from the romfs image
 */
पूर्णांक romfs_dev_पढ़ो(काष्ठा super_block *sb, अचिन्हित दीर्घ pos,
		   व्योम *buf, माप_प्रकार buflen)
अणु
	माप_प्रकार limit;

	limit = romfs_maxsize(sb);
	अगर (pos >= limit || buflen > limit - pos)
		वापस -EIO;

#अगर_घोषित CONFIG_ROMFS_ON_MTD
	अगर (sb->s_mtd)
		वापस romfs_mtd_पढ़ो(sb, pos, buf, buflen);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ROMFS_ON_BLOCK
	अगर (sb->s_bdev)
		वापस romfs_blk_पढ़ो(sb, pos, buf, buflen);
#पूर्ण_अगर
	वापस -EIO;
पूर्ण

/*
 * determine the length of a string in romfs
 */
sमाप_प्रकार romfs_dev_strnlen(काष्ठा super_block *sb,
			  अचिन्हित दीर्घ pos, माप_प्रकार maxlen)
अणु
	माप_प्रकार limit;

	limit = romfs_maxsize(sb);
	अगर (pos >= limit)
		वापस -EIO;
	अगर (maxlen > limit - pos)
		maxlen = limit - pos;

#अगर_घोषित CONFIG_ROMFS_ON_MTD
	अगर (sb->s_mtd)
		वापस romfs_mtd_strnlen(sb, pos, maxlen);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ROMFS_ON_BLOCK
	अगर (sb->s_bdev)
		वापस romfs_blk_strnlen(sb, pos, maxlen);
#पूर्ण_अगर
	वापस -EIO;
पूर्ण

/*
 * compare a string to one in romfs
 * - the string to be compared to, str, may not be NUL-terminated; instead the
 *   string is of the specअगरied size
 * - वापस 1 अगर matched, 0 अगर dअगरfer, -ve अगर error
 */
पूर्णांक romfs_dev_म_भेद(काष्ठा super_block *sb, अचिन्हित दीर्घ pos,
		     स्थिर अक्षर *str, माप_प्रकार size)
अणु
	माप_प्रकार limit;

	limit = romfs_maxsize(sb);
	अगर (pos >= limit)
		वापस -EIO;
	अगर (size > ROMFS_MAXFN)
		वापस -ENAMETOOLONG;
	अगर (size + 1 > limit - pos)
		वापस -EIO;

#अगर_घोषित CONFIG_ROMFS_ON_MTD
	अगर (sb->s_mtd)
		वापस romfs_mtd_म_भेद(sb, pos, str, size);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ROMFS_ON_BLOCK
	अगर (sb->s_bdev)
		वापस romfs_blk_म_भेद(sb, pos, str, size);
#पूर्ण_अगर
	वापस -EIO;
पूर्ण
