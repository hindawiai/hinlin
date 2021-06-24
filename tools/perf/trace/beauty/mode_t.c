<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>

/* From include/linux/स्थिति.स */
#अगर_अघोषित S_IRWXUGO
#घोषणा S_IRWXUGO	(S_IRWXU|S_IRWXG|S_IRWXO)
#पूर्ण_अगर
#अगर_अघोषित S_IALLUGO
#घोषणा S_IALLUGO	(S_ISUID|S_ISGID|S_ISVTX|S_IRWXUGO)
#पूर्ण_अगर
#अगर_अघोषित S_IRUGO
#घोषणा S_IRUGO         (S_IRUSR|S_IRGRP|S_IROTH)
#पूर्ण_अगर
#अगर_अघोषित S_IWUGO
#घोषणा S_IWUGO         (S_IWUSR|S_IWGRP|S_IWOTH)
#पूर्ण_अगर
#अगर_अघोषित S_IXUGO
#घोषणा S_IXUGO         (S_IXUSR|S_IXGRP|S_IXOTH)
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_mode_t(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "S_";
	पूर्णांक prपूर्णांकed = 0, mode = arg->val;

#घोषणा	P_MODE(n) \
	अगर ((mode & S_##n) == S_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", prपूर्णांकed ? "|" : "", show_prefix ? prefix : "", #n); \
		mode &= ~S_##n; \
	पूर्ण

	P_MODE(IALLUGO);
	P_MODE(IRWXUGO);
	P_MODE(IRUGO);
	P_MODE(IWUGO);
	P_MODE(IXUGO);
	P_MODE(IFMT);
	P_MODE(IFSOCK);
	P_MODE(IFLNK);
	P_MODE(IFREG);
	P_MODE(IFBLK);
	P_MODE(IFसूची);
	P_MODE(IFCHR);
	P_MODE(IFIFO);
	P_MODE(ISUID);
	P_MODE(ISGID);
	P_MODE(ISVTX);
	P_MODE(IRWXU);
	P_MODE(IRUSR);
	P_MODE(IWUSR);
	P_MODE(IXUSR);
	P_MODE(IRWXG);
	P_MODE(IRGRP);
	P_MODE(IWGRP);
	P_MODE(IXGRP);
	P_MODE(IRWXO);
	P_MODE(IROTH);
	P_MODE(IWOTH);
	P_MODE(IXOTH);
#अघोषित P_MODE

	अगर (mode)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%#x", prपूर्णांकed ? "|" : "", mode);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_MODE_T syscall_arg__scnम_लिखो_mode_t
