<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Test the statx() प्रणाली call.
 *
 * Note that the output of this program is पूर्णांकended to look like the output of
 * /bin/stat where possible.
 *
 * Copyright (C) 2015 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा _GNU_SOURCE
#घोषणा _ATखाता_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <समय.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/fcntl.h>
#घोषणा statx foo
#घोषणा statx_बारtamp foo_बारtamp
काष्ठा statx;
काष्ठा statx_बारtamp;
#समावेश <sys/स्थिति.स>
#अघोषित statx
#अघोषित statx_बारtamp

#घोषणा AT_STATX_SYNC_TYPE	0x6000
#घोषणा AT_STATX_SYNC_AS_STAT	0x0000
#घोषणा AT_STATX_FORCE_SYNC	0x2000
#घोषणा AT_STATX_DONT_SYNC	0x4000

#अगर_अघोषित __NR_statx
#घोषणा __NR_statx -1
#पूर्ण_अगर

अटल __attribute__((unused))
sमाप_प्रकार statx(पूर्णांक dfd, स्थिर अक्षर *filename, अचिन्हित flags,
	      अचिन्हित पूर्णांक mask, काष्ठा statx *buffer)
अणु
	वापस syscall(__NR_statx, dfd, filename, flags, mask, buffer);
पूर्ण

अटल व्योम prपूर्णांक_समय(स्थिर अक्षर *field, काष्ठा statx_बारtamp *ts)
अणु
	काष्ठा पंचांग पंचांग;
	समय_प्रकार tim;
	अक्षर buffer[100];
	पूर्णांक len;

	tim = ts->tv_sec;
	अगर (!स_स्थानीय_r(&tim, &पंचांग)) अणु
		लिखो_त्रुटि("localtime_r");
		निकास(1);
	पूर्ण
	len = स_माला(buffer, 100, "%F %T", &पंचांग);
	अगर (len == 0) अणु
		लिखो_त्रुटि("strftime");
		निकास(1);
	पूर्ण
	म_लिखो("%s", field);
	ख_डालो(buffer, 1, len, मानक_निकास);
	म_लिखो(".%09u", ts->tv_nsec);
	len = स_माला(buffer, 100, "%z", &पंचांग);
	अगर (len == 0) अणु
		लिखो_त्रुटि("strftime2");
		निकास(1);
	पूर्ण
	ख_डालो(buffer, 1, len, मानक_निकास);
	म_लिखो("\n");
पूर्ण

अटल व्योम dump_statx(काष्ठा statx *stx)
अणु
	अक्षर buffer[256], ft = '?';

	म_लिखो("results=%x\n", stx->stx_mask);

	म_लिखो(" ");
	अगर (stx->stx_mask & STATX_SIZE)
		म_लिखो(" Size: %-15llu", (अचिन्हित दीर्घ दीर्घ)stx->stx_size);
	अगर (stx->stx_mask & STATX_BLOCKS)
		म_लिखो(" Blocks: %-10llu", (अचिन्हित दीर्घ दीर्घ)stx->stx_blocks);
	म_लिखो(" IO Block: %-6llu", (अचिन्हित दीर्घ दीर्घ)stx->stx_blksize);
	अगर (stx->stx_mask & STATX_TYPE) अणु
		चयन (stx->stx_mode & S_IFMT) अणु
		हाल S_IFIFO:	म_लिखो("  FIFO\n");			ft = 'p'; अवरोध;
		हाल S_IFCHR:	म_लिखो("  character special file\n");	ft = 'c'; अवरोध;
		हाल S_IFसूची:	म_लिखो("  directory\n");		ft = 'd'; अवरोध;
		हाल S_IFBLK:	म_लिखो("  block special file\n");	ft = 'b'; अवरोध;
		हाल S_IFREG:	म_लिखो("  regular file\n");		ft = '-'; अवरोध;
		हाल S_IFLNK:	म_लिखो("  symbolic link\n");		ft = 'l'; अवरोध;
		हाल S_IFSOCK:	म_लिखो("  socket\n");			ft = 's'; अवरोध;
		शेष:
			म_लिखो(" unknown type (%o)\n", stx->stx_mode & S_IFMT);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		म_लिखो(" no type\n");
	पूर्ण

	प्र_लिखो(buffer, "%02x:%02x", stx->stx_dev_major, stx->stx_dev_minor);
	म_लिखो("Device: %-15s", buffer);
	अगर (stx->stx_mask & STATX_INO)
		म_लिखो(" Inode: %-11llu", (अचिन्हित दीर्घ दीर्घ) stx->stx_ino);
	अगर (stx->stx_mask & STATX_NLINK)
		म_लिखो(" Links: %-5u", stx->stx_nlink);
	अगर (stx->stx_mask & STATX_TYPE) अणु
		चयन (stx->stx_mode & S_IFMT) अणु
		हाल S_IFBLK:
		हाल S_IFCHR:
			म_लिखो(" Device type: %u,%u",
			       stx->stx_rdev_major, stx->stx_rdev_minor);
			अवरोध;
		पूर्ण
	पूर्ण
	म_लिखो("\n");

	अगर (stx->stx_mask & STATX_MODE)
		म_लिखो("Access: (%04o/%c%c%c%c%c%c%c%c%c%c)  ",
		       stx->stx_mode & 07777,
		       ft,
		       stx->stx_mode & S_IRUSR ? 'r' : '-',
		       stx->stx_mode & S_IWUSR ? 'w' : '-',
		       stx->stx_mode & S_IXUSR ? 'x' : '-',
		       stx->stx_mode & S_IRGRP ? 'r' : '-',
		       stx->stx_mode & S_IWGRP ? 'w' : '-',
		       stx->stx_mode & S_IXGRP ? 'x' : '-',
		       stx->stx_mode & S_IROTH ? 'r' : '-',
		       stx->stx_mode & S_IWOTH ? 'w' : '-',
		       stx->stx_mode & S_IXOTH ? 'x' : '-');
	अगर (stx->stx_mask & STATX_UID)
		म_लिखो("Uid: %5d   ", stx->stx_uid);
	अगर (stx->stx_mask & STATX_GID)
		म_लिखो("Gid: %5d\n", stx->stx_gid);

	अगर (stx->stx_mask & STATX_ATIME)
		prपूर्णांक_समय("Access: ", &stx->stx_aसमय);
	अगर (stx->stx_mask & STATX_MTIME)
		prपूर्णांक_समय("Modify: ", &stx->stx_mसमय);
	अगर (stx->stx_mask & STATX_CTIME)
		prपूर्णांक_समय("Change: ", &stx->stx_स_समय);
	अगर (stx->stx_mask & STATX_BTIME)
		prपूर्णांक_समय(" Birth: ", &stx->stx_bसमय);

	अगर (stx->stx_attributes_mask) अणु
		अचिन्हित अक्षर bits, mbits;
		पूर्णांक loop, byte;

		अटल अक्षर attr_representation[64 + 1] =
			/* STATX_ATTR_ flags: */
			"????????"	/* 63-56 */
			"????????"	/* 55-48 */
			"????????"	/* 47-40 */
			"????????"	/* 39-32 */
			"????????"	/* 31-24	0x00000000-ff000000 */
			"????????"	/* 23-16	0x00000000-00ff0000 */
			"???me???"	/* 15- 8	0x00000000-0000ff00 */
			"?dai?c??"	/*  7- 0	0x00000000-000000ff */
			;

		म_लिखो("Attributes: %016llx (",
		       (अचिन्हित दीर्घ दीर्घ)stx->stx_attributes);
		क्रम (byte = 64 - 8; byte >= 0; byte -= 8) अणु
			bits = stx->stx_attributes >> byte;
			mbits = stx->stx_attributes_mask >> byte;
			क्रम (loop = 7; loop >= 0; loop--) अणु
				पूर्णांक bit = byte + loop;

				अगर (!(mbits & 0x80))
					अक्षर_दो('.');	/* Not supported */
				अन्यथा अगर (bits & 0x80)
					अक्षर_दो(attr_representation[63 - bit]);
				अन्यथा
					अक्षर_दो('-');	/* Not set */
				bits <<= 1;
				mbits <<= 1;
			पूर्ण
			अगर (byte)
				अक्षर_दो(' ');
		पूर्ण
		म_लिखो(")\n");
	पूर्ण
पूर्ण

अटल व्योम dump_hex(अचिन्हित दीर्घ दीर्घ *data, पूर्णांक from, पूर्णांक to)
अणु
	अचिन्हित offset, prपूर्णांक_offset = 1, col = 0;

	from /= 8;
	to = (to + 7) / 8;

	क्रम (offset = from; offset < to; offset++) अणु
		अगर (prपूर्णांक_offset) अणु
			म_लिखो("%04x: ", offset * 8);
			prपूर्णांक_offset = 0;
		पूर्ण
		म_लिखो("%016llx", data[offset]);
		col++;
		अगर ((col & 3) == 0) अणु
			म_लिखो("\n");
			prपूर्णांक_offset = 1;
		पूर्ण अन्यथा अणु
			म_लिखो(" ");
		पूर्ण
	पूर्ण

	अगर (!prपूर्णांक_offset)
		म_लिखो("\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा statx stx;
	पूर्णांक ret, raw = 0, atflag = AT_SYMLINK_NOFOLLOW;

	अचिन्हित पूर्णांक mask = STATX_BASIC_STATS | STATX_BTIME;

	क्रम (argv++; *argv; argv++) अणु
		अगर (म_भेद(*argv, "-F") == 0) अणु
			atflag &= ~AT_STATX_SYNC_TYPE;
			atflag |= AT_STATX_FORCE_SYNC;
			जारी;
		पूर्ण
		अगर (म_भेद(*argv, "-D") == 0) अणु
			atflag &= ~AT_STATX_SYNC_TYPE;
			atflag |= AT_STATX_DONT_SYNC;
			जारी;
		पूर्ण
		अगर (म_भेद(*argv, "-L") == 0) अणु
			atflag &= ~AT_SYMLINK_NOFOLLOW;
			जारी;
		पूर्ण
		अगर (म_भेद(*argv, "-O") == 0) अणु
			mask &= ~STATX_BASIC_STATS;
			जारी;
		पूर्ण
		अगर (म_भेद(*argv, "-A") == 0) अणु
			atflag |= AT_NO_AUTOMOUNT;
			जारी;
		पूर्ण
		अगर (म_भेद(*argv, "-R") == 0) अणु
			raw = 1;
			जारी;
		पूर्ण

		स_रखो(&stx, 0xbf, माप(stx));
		ret = statx(AT_FDCWD, *argv, atflag, mask, &stx);
		म_लिखो("statx(%s) = %d\n", *argv, ret);
		अगर (ret < 0) अणु
			लिखो_त्रुटि(*argv);
			निकास(1);
		पूर्ण

		अगर (raw)
			dump_hex((अचिन्हित दीर्घ दीर्घ *)&stx, 0, माप(stx));

		dump_statx(&stx);
	पूर्ण
	वापस 0;
पूर्ण
