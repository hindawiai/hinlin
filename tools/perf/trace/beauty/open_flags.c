<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>

#अगर_अघोषित O_सूचीECT
#घोषणा O_सूचीECT	00040000
#पूर्ण_अगर

#अगर_अघोषित O_सूचीECTORY
#घोषणा O_सूचीECTORY	00200000
#पूर्ण_अगर

#अगर_अघोषित O_NOATIME
#घोषणा O_NOATIME	01000000
#पूर्ण_अगर

#अगर_अघोषित O_TMPखाता
#घोषणा O_TMPखाता	020000000
#पूर्ण_अगर

#अघोषित O_LARGEखाता
#घोषणा O_LARGEखाता	00100000

माप_प्रकार खोलो__scnम_लिखो_flags(अचिन्हित दीर्घ flags, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	स्थिर अक्षर *prefix = "O_";
	पूर्णांक prपूर्णांकed = 0;

	अगर ((flags & O_ACCMODE) == O_RDONLY)
		prपूर्णांकed = scnम_लिखो(bf, size, "%s%s", show_prefix ? prefix : "", "RDONLY");
	अगर (flags == 0)
		वापस prपूर्णांकed;
#घोषणा	P_FLAG(n) \
	अगर (flags & O_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		flags &= ~O_##n; \
	पूर्ण

	P_FLAG(RDWR);
	P_FLAG(APPEND);
	P_FLAG(ASYNC);
	P_FLAG(CLOEXEC);
	P_FLAG(CREAT);
	P_FLAG(सूचीECT);
	P_FLAG(सूचीECTORY);
	P_FLAG(EXCL);
	P_FLAG(LARGEखाता);
	P_FLAG(NOFOLLOW);
	P_FLAG(TMPखाता);
	P_FLAG(NOATIME);
	P_FLAG(NOCTTY);
#अगर_घोषित O_NONBLOCK
	P_FLAG(NONBLOCK);
#या_अगर O_NDELAY
	P_FLAG(NDELAY);
#पूर्ण_अगर
#अगर_घोषित O_PATH
	P_FLAG(PATH);
#पूर्ण_अगर
#अगर_घोषित O_DSYNC
	अगर ((flags & O_SYNC) == O_SYNC)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", "SYNC");
	अन्यथा अणु
		P_FLAG(DSYNC);
	पूर्ण
#अन्यथा
	P_FLAG(SYNC);
#पूर्ण_अगर
	P_FLAG(TRUNC);
	P_FLAG(WRONLY);
#अघोषित P_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", flags);

	वापस prपूर्णांकed;
पूर्ण

माप_प्रकार syscall_arg__scnम_लिखो_खोलो_flags(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	पूर्णांक flags = arg->val;

	अगर (!(flags & O_CREAT))
		arg->mask |= 1 << (arg->idx + 1); /* Mask the mode parm */

	वापस खोलो__scnम_लिखो_flags(flags, bf, size, arg->show_string_prefix);
पूर्ण
