<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */
#समावेश "array.h"
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>

व्योम fdarray__init(काष्ठा fdarray *fda, पूर्णांक nr_स्वतःgrow)
अणु
	fda->entries	 = शून्य;
	fda->priv	 = शून्य;
	fda->nr		 = fda->nr_alloc = 0;
	fda->nr_स्वतःgrow = nr_स्वतःgrow;
पूर्ण

पूर्णांक fdarray__grow(काष्ठा fdarray *fda, पूर्णांक nr)
अणु
	काष्ठा priv *priv;
	पूर्णांक nr_alloc = fda->nr_alloc + nr;
	माप_प्रकार psize = माप(fda->priv[0]) * nr_alloc;
	माप_प्रकार size  = माप(काष्ठा pollfd) * nr_alloc;
	काष्ठा pollfd *entries = पुनः_स्मृति(fda->entries, size);

	अगर (entries == शून्य)
		वापस -ENOMEM;

	priv = पुनः_स्मृति(fda->priv, psize);
	अगर (priv == शून्य) अणु
		मुक्त(entries);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(&entries[fda->nr_alloc], 0, माप(काष्ठा pollfd) * nr);
	स_रखो(&priv[fda->nr_alloc], 0, माप(fda->priv[0]) * nr);

	fda->nr_alloc = nr_alloc;
	fda->entries  = entries;
	fda->priv     = priv;
	वापस 0;
पूर्ण

काष्ठा fdarray *fdarray__new(पूर्णांक nr_alloc, पूर्णांक nr_स्वतःgrow)
अणु
	काष्ठा fdarray *fda = सुस्मृति(1, माप(*fda));

	अगर (fda != शून्य) अणु
		अगर (fdarray__grow(fda, nr_alloc)) अणु
			मुक्त(fda);
			fda = शून्य;
		पूर्ण अन्यथा अणु
			fda->nr_स्वतःgrow = nr_स्वतःgrow;
		पूर्ण
	पूर्ण

	वापस fda;
पूर्ण

व्योम fdarray__निकास(काष्ठा fdarray *fda)
अणु
	मुक्त(fda->entries);
	मुक्त(fda->priv);
	fdarray__init(fda, 0);
पूर्ण

व्योम fdarray__delete(काष्ठा fdarray *fda)
अणु
	fdarray__निकास(fda);
	मुक्त(fda);
पूर्ण

पूर्णांक fdarray__add(काष्ठा fdarray *fda, पूर्णांक fd, लघु revents, क्रमागत fdarray_flags flags)
अणु
	पूर्णांक pos = fda->nr;

	अगर (fda->nr == fda->nr_alloc &&
	    fdarray__grow(fda, fda->nr_स्वतःgrow) < 0)
		वापस -ENOMEM;

	fda->entries[fda->nr].fd     = fd;
	fda->entries[fda->nr].events = revents;
	fda->priv[fda->nr].flags = flags;
	fda->nr++;
	वापस pos;
पूर्ण

पूर्णांक fdarray__filter(काष्ठा fdarray *fda, लघु revents,
		    व्योम (*entry_deकाष्ठाor)(काष्ठा fdarray *fda, पूर्णांक fd, व्योम *arg),
		    व्योम *arg)
अणु
	पूर्णांक fd, nr = 0;

	अगर (fda->nr == 0)
		वापस 0;

	क्रम (fd = 0; fd < fda->nr; ++fd) अणु
		अगर (!fda->entries[fd].events)
			जारी;

		अगर (fda->entries[fd].revents & revents) अणु
			अगर (entry_deकाष्ठाor)
				entry_deकाष्ठाor(fda, fd, arg);

			fda->entries[fd].revents = fda->entries[fd].events = 0;
			जारी;
		पूर्ण

		अगर (!(fda->priv[fd].flags & fdarray_flag__nonfilterable))
			++nr;
	पूर्ण

	वापस nr;
पूर्ण

पूर्णांक fdarray__poll(काष्ठा fdarray *fda, पूर्णांक समयout)
अणु
	वापस poll(fda->entries, fda->nr, समयout);
पूर्ण

पूर्णांक fdarray__ख_लिखो(काष्ठा fdarray *fda, खाता *fp)
अणु
	पूर्णांक fd, prपूर्णांकed = ख_लिखो(fp, "%d [ ", fda->nr);

	क्रम (fd = 0; fd < fda->nr; ++fd)
		prपूर्णांकed += ख_लिखो(fp, "%s%d", fd ? ", " : "", fda->entries[fd].fd);

	वापस prपूर्णांकed + ख_लिखो(fp, " ]");
पूर्ण
