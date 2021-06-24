<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Author: Aleksa Sarai <cyphar@cyphar.com>
 * Copyright (C) 2018-2019 SUSE LLC.
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <सीमा.स>

#समावेश "helpers.h"

bool needs_खोलोat2(स्थिर काष्ठा खोलो_how *how)
अणु
	वापस how->resolve != 0;
पूर्ण

पूर्णांक raw_खोलोat2(पूर्णांक dfd, स्थिर अक्षर *path, व्योम *how, माप_प्रकार size)
अणु
	पूर्णांक ret = syscall(__NR_खोलोat2, dfd, path, how, size);
	वापस ret >= 0 ? ret : -त्रुटि_सं;
पूर्ण

पूर्णांक sys_खोलोat2(पूर्णांक dfd, स्थिर अक्षर *path, काष्ठा खोलो_how *how)
अणु
	वापस raw_खोलोat2(dfd, path, how, माप(*how));
पूर्ण

पूर्णांक sys_खोलोat(पूर्णांक dfd, स्थिर अक्षर *path, काष्ठा खोलो_how *how)
अणु
	पूर्णांक ret = खोलोat(dfd, path, how->flags, how->mode);
	वापस ret >= 0 ? ret : -त्रुटि_सं;
पूर्ण

पूर्णांक sys_नामat2(पूर्णांक olddirfd, स्थिर अक्षर *oldpath,
		  पूर्णांक newdirfd, स्थिर अक्षर *newpath, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret = syscall(__NR_नामat2, olddirfd, oldpath,
					  newdirfd, newpath, flags);
	वापस ret >= 0 ? ret : -त्रुटि_सं;
पूर्ण

पूर्णांक touchat(पूर्णांक dfd, स्थिर अक्षर *path)
अणु
	पूर्णांक fd = खोलोat(dfd, path, O_CREAT, 0700);
	अगर (fd >= 0)
		बंद(fd);
	वापस fd;
पूर्ण

अक्षर *fdपढ़ोlink(पूर्णांक fd)
अणु
	अक्षर *target, *पंचांगp;

	E_aप्र_लिखो(&पंचांगp, "/proc/self/fd/%d", fd);

	target = दो_स्मृति(PATH_MAX);
	अगर (!target)
		ksft_निकास_fail_msg("fdreadlink: malloc failed\n");
	स_रखो(target, 0, PATH_MAX);

	E_पढ़ोlink(पंचांगp, target, PATH_MAX);
	मुक्त(पंचांगp);
	वापस target;
पूर्ण

bool fdequal(पूर्णांक fd, पूर्णांक dfd, स्थिर अक्षर *path)
अणु
	अक्षर *fdpath, *dfdpath, *other;
	bool cmp;

	fdpath = fdपढ़ोlink(fd);
	dfdpath = fdपढ़ोlink(dfd);

	अगर (!path)
		E_aप्र_लिखो(&other, "%s", dfdpath);
	अन्यथा अगर (*path == '/')
		E_aप्र_लिखो(&other, "%s", path);
	अन्यथा
		E_aप्र_लिखो(&other, "%s/%s", dfdpath, path);

	cmp = !म_भेद(fdpath, other);

	मुक्त(fdpath);
	मुक्त(dfdpath);
	मुक्त(other);
	वापस cmp;
पूर्ण

bool खोलोat2_supported = false;

व्योम __attribute__((स्थिरructor)) init(व्योम)
अणु
	काष्ठा खोलो_how how = अणुपूर्ण;
	पूर्णांक fd;

	BUILD_BUG_ON(माप(काष्ठा खोलो_how) != OPEN_HOW_SIZE_VER0);

	/* Check खोलोat2(2) support. */
	fd = sys_खोलोat2(AT_FDCWD, ".", &how);
	खोलोat2_supported = (fd >= 0);

	अगर (fd >= 0)
		बंद(fd);
पूर्ण
