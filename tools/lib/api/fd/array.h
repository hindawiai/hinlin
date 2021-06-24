<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __API_FD_ARRAY__
#घोषणा __API_FD_ARRAY__

#समावेश <मानकपन.स>

काष्ठा pollfd;

/**
 * काष्ठा fdarray: Array of file descriptors
 *
 * @priv: Per array entry priv area, users should access just its contents,
 *	  not set it to anything, as it is kept in synch with @entries, being
 *	  पुनः_स्मृति'ed, * क्रम instance, in fdarray__अणुgrow,filterपूर्ण.
 *
 *	  I.e. using 'fda->priv[N].idx = * value' where N < fda->nr is ok,
 *	  but करोing 'fda->priv = malloc(M)' is not allowed.
 */
काष्ठा fdarray अणु
	पूर्णांक	       nr;
	पूर्णांक	       nr_alloc;
	पूर्णांक	       nr_स्वतःgrow;
	काष्ठा pollfd *entries;
	काष्ठा priv अणु
		जोड़ अणु
			पूर्णांक    idx;
			व्योम   *ptr;
		पूर्ण;
		अचिन्हित पूर्णांक flags;
	पूर्ण *priv;
पूर्ण;

क्रमागत fdarray_flags अणु
	fdarray_flag__शेष	    = 0x00000000,
	fdarray_flag__nonfilterable = 0x00000001
पूर्ण;

व्योम fdarray__init(काष्ठा fdarray *fda, पूर्णांक nr_स्वतःgrow);
व्योम fdarray__निकास(काष्ठा fdarray *fda);

काष्ठा fdarray *fdarray__new(पूर्णांक nr_alloc, पूर्णांक nr_स्वतःgrow);
व्योम fdarray__delete(काष्ठा fdarray *fda);

पूर्णांक fdarray__add(काष्ठा fdarray *fda, पूर्णांक fd, लघु revents, क्रमागत fdarray_flags flags);
पूर्णांक fdarray__poll(काष्ठा fdarray *fda, पूर्णांक समयout);
पूर्णांक fdarray__filter(काष्ठा fdarray *fda, लघु revents,
		    व्योम (*entry_deकाष्ठाor)(काष्ठा fdarray *fda, पूर्णांक fd, व्योम *arg),
		    व्योम *arg);
पूर्णांक fdarray__grow(काष्ठा fdarray *fda, पूर्णांक extra);
पूर्णांक fdarray__ख_लिखो(काष्ठा fdarray *fda, खाता *fp);

अटल अंतरभूत पूर्णांक fdarray__available_entries(काष्ठा fdarray *fda)
अणु
	वापस fda->nr_alloc - fda->nr;
पूर्ण

#पूर्ण_अगर /* __API_FD_ARRAY__ */
