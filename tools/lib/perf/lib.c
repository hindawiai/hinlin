<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <unistd.h>
#समावेश <stdbool.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <पूर्णांकernal/lib.h>

अचिन्हित पूर्णांक page_size;

अटल sमाप_प्रकार ion(bool is_पढ़ो, पूर्णांक fd, व्योम *buf, माप_प्रकार n)
अणु
	व्योम *buf_start = buf;
	माप_प्रकार left = n;

	जबतक (left) अणु
		/* buf must be treated as स्थिर अगर !is_पढ़ो. */
		sमाप_प्रकार ret = is_पढ़ो ? पढ़ो(fd, buf, left) :
					ग_लिखो(fd, buf, left);

		अगर (ret < 0 && त्रुटि_सं == EINTR)
			जारी;
		अगर (ret <= 0)
			वापस ret;

		left -= ret;
		buf  += ret;
	पूर्ण

	BUG_ON((माप_प्रकार)(buf - buf_start) != n);
	वापस n;
पूर्ण

/*
 * Read exactly 'n' bytes or वापस an error.
 */
sमाप_प्रकार पढ़ोn(पूर्णांक fd, व्योम *buf, माप_प्रकार n)
अणु
	वापस ion(true, fd, buf, n);
पूर्ण

/*
 * Write exactly 'n' bytes or वापस an error.
 */
sमाप_प्रकार ग_लिखोn(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार n)
अणु
	/* ion करोes not modअगरy buf. */
	वापस ion(false, fd, (व्योम *)buf, n);
पूर्ण
