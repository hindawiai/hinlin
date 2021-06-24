<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Written 1992,1993 by Werner Almesberger
 *  22/11/2000 - Fixed fat_date_unix2करोs क्रम dates earlier than 01/01/1980
 *		 and date_करोs2unix क्रम date==0 by Igor Zhbanov(bsg@uniyar.ac.ru)
 * Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/buffer_head.h>

#समावेश "exfat_raw.h"
#समावेश "exfat_fs.h"

/*
 * exfat_fs_error reports a file प्रणाली problem that might indicate fa data
 * corruption/inconsistency. Depending on 'errors' mount option the
 * panic() is called, or error message is prपूर्णांकed FAT and nothing is करोne,
 * or fileप्रणाली is remounted पढ़ो-only (शेष behavior).
 * In हाल the file प्रणाली is remounted पढ़ो-only, it can be made writable
 * again by remounting it.
 */
व्योम __exfat_fs_error(काष्ठा super_block *sb, पूर्णांक report, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा exfat_mount_options *opts = &EXFAT_SB(sb)->options;
	बहु_सूची args;
	काष्ठा va_क्रमmat vaf;

	अगर (report) अणु
		बहु_शुरू(args, fmt);
		vaf.fmt = fmt;
		vaf.va = &args;
		exfat_err(sb, "error, %pV", &vaf);
		बहु_पूर्ण(args);
	पूर्ण

	अगर (opts->errors == EXFAT_ERRORS_PANIC) अणु
		panic("exFAT-fs (%s): fs panic from previous error\n",
			sb->s_id);
	पूर्ण अन्यथा अगर (opts->errors == EXFAT_ERRORS_RO && !sb_rकरोnly(sb)) अणु
		sb->s_flags |= SB_RDONLY;
		exfat_err(sb, "Filesystem has been set read-only");
	पूर्ण
पूर्ण

/*
 * exfat_msg() - prपूर्णांक preक्रमmated EXFAT specअगरic messages.
 * All logs except what uses exfat_fs_error() should be written by exfat_msg()
 */
व्योम exfat_msg(काष्ठा super_block *sb, स्थिर अक्षर *level, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	/* level means KERN_ pacility level */
	prपूर्णांकk("%sexFAT-fs (%s): %pV\n", level, sb->s_id, &vaf);
	बहु_पूर्ण(args);
पूर्ण

#घोषणा SECS_PER_MIN    (60)
#घोषणा TIMEZONE_SEC(x)	((x) * 15 * SECS_PER_MIN)

अटल व्योम exfat_adjust_tz(काष्ठा बारpec64 *ts, u8 tz_off)
अणु
	अगर (tz_off <= 0x3F)
		ts->tv_sec -= TIMEZONE_SEC(tz_off);
	अन्यथा /* 0x40 <= (tz_off & 0x7F) <=0x7F */
		ts->tv_sec += TIMEZONE_SEC(0x80 - tz_off);
पूर्ण

/* Convert a EXFAT समय/date pair to a UNIX date (seconds since 1 1 70). */
व्योम exfat_get_entry_समय(काष्ठा exfat_sb_info *sbi, काष्ठा बारpec64 *ts,
		u8 tz, __le16 समय, __le16 date, u8 समय_cs)
अणु
	u16 t = le16_to_cpu(समय);
	u16 d = le16_to_cpu(date);

	ts->tv_sec = स_गढ़ो64(1980 + (d >> 9), d >> 5 & 0x000F, d & 0x001F,
			      t >> 11, (t >> 5) & 0x003F, (t & 0x001F) << 1);


	/* समय_cs field represent 0 ~ 199cs(1990 ms) */
	अगर (समय_cs) अणु
		ts->tv_sec += समय_cs / 100;
		ts->tv_nsec = (समय_cs % 100) * 10 * NSEC_PER_MSEC;
	पूर्ण अन्यथा
		ts->tv_nsec = 0;

	अगर (tz & EXFAT_TZ_VALID)
		/* Adjust समयzone to UTC0. */
		exfat_adjust_tz(ts, tz & ~EXFAT_TZ_VALID);
	अन्यथा
		/* Convert from local समय to UTC using समय_offset. */
		ts->tv_sec -= sbi->options.समय_offset * SECS_PER_MIN;
पूर्ण

/* Convert linear UNIX date to a EXFAT समय/date pair. */
व्योम exfat_set_entry_समय(काष्ठा exfat_sb_info *sbi, काष्ठा बारpec64 *ts,
		u8 *tz, __le16 *समय, __le16 *date, u8 *समय_cs)
अणु
	काष्ठा पंचांग पंचांग;
	u16 t, d;

	समय64_to_पंचांग(ts->tv_sec, 0, &पंचांग);
	t = (पंचांग.पंचांग_hour << 11) | (पंचांग.पंचांग_min << 5) | (पंचांग.पंचांग_sec >> 1);
	d = ((पंचांग.पंचांग_year - 80) <<  9) | ((पंचांग.पंचांग_mon + 1) << 5) | पंचांग.पंचांग_mday;

	*समय = cpu_to_le16(t);
	*date = cpu_to_le16(d);

	/* समय_cs field represent 0 ~ 199cs(1990 ms) */
	अगर (समय_cs)
		*समय_cs = (पंचांग.पंचांग_sec & 1) * 100 +
			ts->tv_nsec / (10 * NSEC_PER_MSEC);

	/*
	 * Record 00h value क्रम OffsetFromUtc field and 1 value क्रम OffsetValid
	 * to indicate that local समय and UTC are the same.
	 */
	*tz = EXFAT_TZ_VALID;
पूर्ण

/*
 * The बारtamp क्रम access_समय has द्विगुन seconds granularity.
 * (There is no 10msIncrement field क्रम access_समय unlike create/modअगरy_समय)
 * aसमय also has only a 2-second resolution.
 */
व्योम exfat_truncate_aसमय(काष्ठा बारpec64 *ts)
अणु
	ts->tv_sec = round_करोwn(ts->tv_sec, 2);
	ts->tv_nsec = 0;
पूर्ण

u16 exfat_calc_chksum16(व्योम *data, पूर्णांक len, u16 chksum, पूर्णांक type)
अणु
	पूर्णांक i;
	u8 *c = (u8 *)data;

	क्रम (i = 0; i < len; i++, c++) अणु
		अगर (unlikely(type == CS_सूची_ENTRY && (i == 2 || i == 3)))
			जारी;
		chksum = ((chksum << 15) | (chksum >> 1)) + *c;
	पूर्ण
	वापस chksum;
पूर्ण

u32 exfat_calc_chksum32(व्योम *data, पूर्णांक len, u32 chksum, पूर्णांक type)
अणु
	पूर्णांक i;
	u8 *c = (u8 *)data;

	क्रम (i = 0; i < len; i++, c++) अणु
		अगर (unlikely(type == CS_BOOT_SECTOR &&
			     (i == 106 || i == 107 || i == 112)))
			जारी;
		chksum = ((chksum << 31) | (chksum >> 1)) + *c;
	पूर्ण
	वापस chksum;
पूर्ण

व्योम exfat_update_bh(काष्ठा buffer_head *bh, पूर्णांक sync)
अणु
	set_buffer_uptodate(bh);
	mark_buffer_dirty(bh);

	अगर (sync)
		sync_dirty_buffer(bh);
पूर्ण

पूर्णांक exfat_update_bhs(काष्ठा buffer_head **bhs, पूर्णांक nr_bhs, पूर्णांक sync)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < nr_bhs; i++) अणु
		set_buffer_uptodate(bhs[i]);
		mark_buffer_dirty(bhs[i]);
		अगर (sync)
			ग_लिखो_dirty_buffer(bhs[i], 0);
	पूर्ण

	क्रम (i = 0; i < nr_bhs && sync; i++) अणु
		रुको_on_buffer(bhs[i]);
		अगर (!err && !buffer_uptodate(bhs[i]))
			err = -EIO;
	पूर्ण
	वापस err;
पूर्ण

व्योम exfat_chain_set(काष्ठा exfat_chain *ec, अचिन्हित पूर्णांक dir,
		अचिन्हित पूर्णांक size, अचिन्हित अक्षर flags)
अणु
	ec->dir = dir;
	ec->size = size;
	ec->flags = flags;
पूर्ण

व्योम exfat_chain_dup(काष्ठा exfat_chain *dup, काष्ठा exfat_chain *ec)
अणु
	वापस exfat_chain_set(dup, ec->dir, ec->size, ec->flags);
पूर्ण
