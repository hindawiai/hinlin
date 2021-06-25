<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SUBCMD_UTIL_H
#घोषणा __SUBCMD_UTIL_H

#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>

#घोषणा NORETURN __attribute__((__noवापस__))

अटल अंतरभूत व्योम report(स्थिर अक्षर *prefix, स्थिर अक्षर *err, बहु_सूची params)
अणु
	अक्षर msg[1024];
	vsnम_लिखो(msg, माप(msg), err, params);
	ख_लिखो(मानक_त्रुटि, " %s%s\n", prefix, msg);
पूर्ण

अटल NORETURN अंतरभूत व्योम die(स्थिर अक्षर *err, ...)
अणु
	बहु_सूची params;

	बहु_शुरू(params, err);
	report(" Fatal: ", err, params);
	निकास(128);
	बहु_पूर्ण(params);
पूर्ण

#घोषणा zमुक्त(ptr) (अणु मुक्त(*ptr); *ptr = शून्य; पूर्ण)

#घोषणा alloc_nr(x) (((x)+16)*3/2)

/*
 * Realloc the buffer poपूर्णांकed at by variable 'x' so that it can hold
 * at least 'nr' entries; the number of entries currently allocated
 * is 'alloc', using the standard growing factor alloc_nr() macro.
 *
 * DO NOT USE any expression with side-effect क्रम 'x' or 'alloc'.
 */
#घोषणा ALLOC_GROW(x, nr, alloc) \
	करो अणु \
		अगर ((nr) > alloc) अणु \
			अगर (alloc_nr(alloc) < (nr)) \
				alloc = (nr); \
			अन्यथा \
				alloc = alloc_nr(alloc); \
			x = xपुनः_स्मृति((x), alloc * माप(*(x))); \
		पूर्ण \
	पूर्ण जबतक(0)

अटल अंतरभूत व्योम *xपुनः_स्मृति(व्योम *ptr, माप_प्रकार size)
अणु
	व्योम *ret = पुनः_स्मृति(ptr, size);
	अगर (!ret && !size)
		ret = पुनः_स्मृति(ptr, 1);
	अगर (!ret) अणु
		ret = पुनः_स्मृति(ptr, size);
		अगर (!ret && !size)
			ret = पुनः_स्मृति(ptr, 1);
		अगर (!ret)
			die("Out of memory, realloc failed");
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा aम_जोड़ोf(out, fmt, ...)						\
(अणु									\
	अक्षर *पंचांगp = *(out);						\
	अगर (aप्र_लिखो((out), "%s" fmt, पंचांगp ?: "", ## __VA_ARGS__) == -1)	\
		die("asprintf failed");					\
	मुक्त(पंचांगp);							\
पूर्ण)

अटल अंतरभूत व्योम aम_जोड़ो(अक्षर **out, स्थिर अक्षर *add)
अणु
	अक्षर *पंचांगp = *out;

	अगर (aप्र_लिखो(out, "%s%s", पंचांगp ?: "", add) == -1)
		die("asprintf failed");

	मुक्त(पंचांगp);
पूर्ण

#पूर्ण_अगर /* __SUBCMD_UTIL_H */
