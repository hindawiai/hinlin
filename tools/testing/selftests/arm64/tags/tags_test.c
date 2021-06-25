<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <मानक_निवेशt.h>
#समावेश <sys/prctl.h>
#समावेश <sys/utsname.h>

#घोषणा SHIFT_TAG(tag)		((uपूर्णांक64_t)(tag) << 56)
#घोषणा SET_TAG(ptr, tag)	(((uपूर्णांक64_t)(ptr) & ~SHIFT_TAG(0xff)) | \
					SHIFT_TAG(tag))

पूर्णांक मुख्य(व्योम)
अणु
	अटल पूर्णांक tbi_enabled = 0;
	अचिन्हित दीर्घ tag = 0;
	काष्ठा utsname *ptr;
	पूर्णांक err;

	अगर (prctl(PR_SET_TAGGED_ADDR_CTRL, PR_TAGGED_ADDR_ENABLE, 0, 0, 0) == 0)
		tbi_enabled = 1;
	ptr = (काष्ठा utsname *)दो_स्मृति(माप(*ptr));
	अगर (tbi_enabled)
		tag = 0x42;
	ptr = (काष्ठा utsname *)SET_TAG(ptr, tag);
	err = uname(ptr);
	मुक्त(ptr);

	वापस err;
पूर्ण
