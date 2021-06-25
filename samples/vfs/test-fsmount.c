<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* fd-based mount test.
 *
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sys/prctl.h>
#समावेश <sys/रुको.h>
#समावेश <linux/mount.h>
#समावेश <linux/unistd.h>

#घोषणा E(x) करो अणु अगर ((x) == -1) अणु लिखो_त्रुटि(#x); निकास(1); पूर्ण पूर्ण जबतक(0)

अटल व्योम check_messages(पूर्णांक fd)
अणु
	अक्षर buf[4096];
	पूर्णांक err, n;

	err = त्रुटि_सं;

	क्रम (;;) अणु
		n = पढ़ो(fd, buf, माप(buf));
		अगर (n < 0)
			अवरोध;
		n -= 2;

		चयन (buf[0]) अणु
		हाल 'e':
			ख_लिखो(मानक_त्रुटि, "Error: %*.*s\n", n, n, buf + 2);
			अवरोध;
		हाल 'w':
			ख_लिखो(मानक_त्रुटि, "Warning: %*.*s\n", n, n, buf + 2);
			अवरोध;
		हाल 'i':
			ख_लिखो(मानक_त्रुटि, "Info: %*.*s\n", n, n, buf + 2);
			अवरोध;
		पूर्ण
	पूर्ण

	त्रुटि_सं = err;
पूर्ण

अटल __attribute__((noवापस))
व्योम mount_error(पूर्णांक fd, स्थिर अक्षर *s)
अणु
	check_messages(fd);
	ख_लिखो(मानक_त्रुटि, "%s: %m\n", s);
	निकास(1);
पूर्ण

/* Hope -1 isn't a syscall */
#अगर_अघोषित __NR_fsखोलो
#घोषणा __NR_fsखोलो -1
#पूर्ण_अगर
#अगर_अघोषित __NR_fsmount
#घोषणा __NR_fsmount -1
#पूर्ण_अगर
#अगर_अघोषित __NR_fsconfig
#घोषणा __NR_fsconfig -1
#पूर्ण_अगर
#अगर_अघोषित __NR_move_mount
#घोषणा __NR_move_mount -1
#पूर्ण_अगर


अटल अंतरभूत पूर्णांक fsखोलो(स्थिर अक्षर *fs_name, अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_fsखोलो, fs_name, flags);
पूर्ण

अटल अंतरभूत पूर्णांक fsmount(पूर्णांक fsfd, अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक ms_flags)
अणु
	वापस syscall(__NR_fsmount, fsfd, flags, ms_flags);
पूर्ण

अटल अंतरभूत पूर्णांक fsconfig(पूर्णांक fsfd, अचिन्हित पूर्णांक cmd,
			   स्थिर अक्षर *key, स्थिर व्योम *val, पूर्णांक aux)
अणु
	वापस syscall(__NR_fsconfig, fsfd, cmd, key, val, aux);
पूर्ण

अटल अंतरभूत पूर्णांक move_mount(पूर्णांक from_dfd, स्थिर अक्षर *from_pathname,
			     पूर्णांक to_dfd, स्थिर अक्षर *to_pathname,
			     अचिन्हित पूर्णांक flags)
अणु
	वापस syscall(__NR_move_mount,
		       from_dfd, from_pathname,
		       to_dfd, to_pathname, flags);
पूर्ण

#घोषणा E_fsconfig(fd, cmd, key, val, aux)				\
	करो अणु								\
		अगर (fsconfig(fd, cmd, key, val, aux) == -1)		\
			mount_error(fd, key ?: "create");		\
	पूर्ण जबतक (0)

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक fsfd, mfd;

	/* Mount a खुलाally available AFS fileप्रणाली */
	fsfd = fsखोलो("afs", 0);
	अगर (fsfd == -1) अणु
		लिखो_त्रुटि("fsopen");
		निकास(1);
	पूर्ण

	E_fsconfig(fsfd, FSCONFIG_SET_STRING, "source", "#grand.central.org:root.cell.", 0);
	E_fsconfig(fsfd, FSCONFIG_CMD_CREATE, शून्य, शून्य, 0);

	mfd = fsmount(fsfd, 0, MOUNT_ATTR_RDONLY);
	अगर (mfd < 0)
		mount_error(fsfd, "fsmount");
	E(बंद(fsfd));

	अगर (move_mount(mfd, "", AT_FDCWD, "/mnt", MOVE_MOUNT_F_EMPTY_PATH) < 0) अणु
		लिखो_त्रुटि("move_mount");
		निकास(1);
	पूर्ण

	E(बंद(mfd));
	निकास(0);
पूर्ण
