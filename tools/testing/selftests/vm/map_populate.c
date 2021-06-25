<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Dmitry Safonov, Arista Networks
 *
 * MAP_POPULATE | MAP_PRIVATE should COW VMA pages.
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sys/mman.h>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#अगर_अघोषित MMAP_SZ
#घोषणा MMAP_SZ		4096
#पूर्ण_अगर

#घोषणा BUG_ON(condition, description)					\
	करो अणु								\
		अगर (condition) अणु					\
			ख_लिखो(मानक_त्रुटि, "[FAIL]\t%s:%d\t%s:%s\n", __func__, \
				__LINE__, (description), म_त्रुटि(त्रुटि_सं)); \
			निकास(1);					\
		पूर्ण							\
	पूर्ण जबतक (0)

अटल पूर्णांक parent_f(पूर्णांक sock, अचिन्हित दीर्घ *smap, पूर्णांक child)
अणु
	पूर्णांक status, ret;

	ret = पढ़ो(sock, &status, माप(पूर्णांक));
	BUG_ON(ret <= 0, "read(sock)");

	*smap = 0x22222BAD;
	ret = msync(smap, MMAP_SZ, MS_SYNC);
	BUG_ON(ret, "msync()");

	ret = ग_लिखो(sock, &status, माप(पूर्णांक));
	BUG_ON(ret <= 0, "write(sock)");

	रुकोpid(child, &status, 0);
	BUG_ON(!WIFEXITED(status), "child in unexpected state");

	वापस WEXITSTATUS(status);
पूर्ण

अटल पूर्णांक child_f(पूर्णांक sock, अचिन्हित दीर्घ *smap, पूर्णांक fd)
अणु
	पूर्णांक ret, buf = 0;

	smap = mmap(0, MMAP_SZ, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_POPULATE, fd, 0);
	BUG_ON(smap == MAP_FAILED, "mmap()");

	BUG_ON(*smap != 0xdeadbabe, "MAP_PRIVATE | MAP_POPULATE changed file");

	ret = ग_लिखो(sock, &buf, माप(पूर्णांक));
	BUG_ON(ret <= 0, "write(sock)");

	ret = पढ़ो(sock, &buf, माप(पूर्णांक));
	BUG_ON(ret <= 0, "read(sock)");

	BUG_ON(*smap == 0x22222BAD, "MAP_POPULATE didn't COW private page");
	BUG_ON(*smap != 0xdeadbabe, "mapping was corrupted");

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक sock[2], child, ret;
	खाता *fपंचांगp;
	अचिन्हित दीर्घ *smap;

	fपंचांगp = क्षणिक_ख();
	BUG_ON(fपंचांगp == 0, "tmpfile()");

	ret = ftruncate(fileno(fपंचांगp), MMAP_SZ);
	BUG_ON(ret, "ftruncate()");

	smap = mmap(0, MMAP_SZ, PROT_READ | PROT_WRITE,
			MAP_SHARED, fileno(fपंचांगp), 0);
	BUG_ON(smap == MAP_FAILED, "mmap()");

	*smap = 0xdeadbabe;
	/* Probably unnecessary, but let it be. */
	ret = msync(smap, MMAP_SZ, MS_SYNC);
	BUG_ON(ret, "msync()");

	ret = socketpair(PF_LOCAL, SOCK_SEQPACKET, 0, sock);
	BUG_ON(ret, "socketpair()");

	child = विभाजन();
	BUG_ON(child == -1, "fork()");

	अगर (child) अणु
		ret = बंद(sock[0]);
		BUG_ON(ret, "close()");

		वापस parent_f(sock[1], smap, child);
	पूर्ण

	ret = बंद(sock[1]);
	BUG_ON(ret, "close()");

	वापस child_f(sock[0], smap, fileno(fपंचांगp));
पूर्ण
