<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "util/copyfile.h"
#समावेश "util/namespaces.h"
#समावेश <पूर्णांकernal/lib.h>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

अटल पूर्णांक slow_copyfile(स्थिर अक्षर *from, स्थिर अक्षर *to, काष्ठा nsinfo *nsi)
अणु
	पूर्णांक err = -1;
	अक्षर *line = शून्य;
	माप_प्रकार n;
	खाता *from_fp, *to_fp;
	काष्ठा nscookie nsc;

	nsinfo__mountns_enter(nsi, &nsc);
	from_fp = ख_खोलो(from, "r");
	nsinfo__mountns_निकास(&nsc);
	अगर (from_fp == शून्य)
		जाओ out;

	to_fp = ख_खोलो(to, "w");
	अगर (to_fp == शून्य)
		जाओ out_ख_बंद_from;

	जबतक (getline(&line, &n, from_fp) > 0)
		अगर (ख_माला_दो(line, to_fp) == खातापूर्ण)
			जाओ out_ख_बंद_to;
	err = 0;
out_ख_बंद_to:
	ख_बंद(to_fp);
	मुक्त(line);
out_ख_बंद_from:
	ख_बंद(from_fp);
out:
	वापस err;
पूर्ण

पूर्णांक copyfile_offset(पूर्णांक अगरd, loff_t off_in, पूर्णांक ofd, loff_t off_out, u64 size)
अणु
	व्योम *ptr;
	loff_t pgoff;

	pgoff = off_in & ~(page_size - 1);
	off_in -= pgoff;

	ptr = mmap(शून्य, off_in + size, PROT_READ, MAP_PRIVATE, अगरd, pgoff);
	अगर (ptr == MAP_FAILED)
		वापस -1;

	जबतक (size) अणु
		sमाप_प्रकार ret = pग_लिखो(ofd, ptr + off_in, size, off_out);
		अगर (ret < 0 && त्रुटि_सं == EINTR)
			जारी;
		अगर (ret <= 0)
			अवरोध;

		size -= ret;
		off_in += ret;
		off_out += ret;
	पूर्ण
	munmap(ptr, off_in + size);

	वापस size ? -1 : 0;
पूर्ण

अटल पूर्णांक copyfile_mode_ns(स्थिर अक्षर *from, स्थिर अक्षर *to, mode_t mode,
			    काष्ठा nsinfo *nsi)
अणु
	पूर्णांक fromfd, tofd;
	काष्ठा stat st;
	पूर्णांक err;
	अक्षर *पंचांगp = शून्य, *ptr = शून्य;
	काष्ठा nscookie nsc;

	nsinfo__mountns_enter(nsi, &nsc);
	err = stat(from, &st);
	nsinfo__mountns_निकास(&nsc);
	अगर (err)
		जाओ out;
	err = -1;

	/* extra 'x' at the end is to reserve space for '.' */
	अगर (aप्र_लिखो(&पंचांगp, "%s.XXXXXXx", to) < 0) अणु
		पंचांगp = शून्य;
		जाओ out;
	पूर्ण
	ptr = म_खोजप(पंचांगp, '/');
	अगर (!ptr)
		जाओ out;
	ptr = स_हटाओ(ptr + 1, ptr, म_माप(ptr) - 1);
	*ptr = '.';

	tofd = mkstemp(पंचांगp);
	अगर (tofd < 0)
		जाओ out;

	अगर (st.st_size == 0) अणु /* /proc? करो it slowly... */
		err = slow_copyfile(from, पंचांगp, nsi);
		अगर (!err && fchmod(tofd, mode))
			err = -1;
		जाओ out_बंद_to;
	पूर्ण

	अगर (fchmod(tofd, mode))
		जाओ out_बंद_to;

	nsinfo__mountns_enter(nsi, &nsc);
	fromfd = खोलो(from, O_RDONLY);
	nsinfo__mountns_निकास(&nsc);
	अगर (fromfd < 0)
		जाओ out_बंद_to;

	err = copyfile_offset(fromfd, 0, tofd, 0, st.st_size);

	बंद(fromfd);
out_बंद_to:
	बंद(tofd);
	अगर (!err)
		err = link(पंचांगp, to);
	unlink(पंचांगp);
out:
	मुक्त(पंचांगp);
	वापस err;
पूर्ण

पूर्णांक copyfile_ns(स्थिर अक्षर *from, स्थिर अक्षर *to, काष्ठा nsinfo *nsi)
अणु
	वापस copyfile_mode_ns(from, to, 0755, nsi);
पूर्ण

पूर्णांक copyfile_mode(स्थिर अक्षर *from, स्थिर अक्षर *to, mode_t mode)
अणु
	वापस copyfile_mode_ns(from, to, mode, शून्य);
पूर्ण

पूर्णांक copyfile(स्थिर अक्षर *from, स्थिर अक्षर *to)
अणु
	वापस copyfile_mode(from, to, 0755);
पूर्ण
