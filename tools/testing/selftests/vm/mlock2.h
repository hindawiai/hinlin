<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <syscall.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#अगर_अघोषित MLOCK_ONFAULT
#घोषणा MLOCK_ONFAULT 1
#पूर्ण_अगर

#अगर_अघोषित MCL_ONFAULT
#घोषणा MCL_ONFAULT (MCL_FUTURE << 1)
#पूर्ण_अगर

अटल पूर्णांक mlock2_(व्योम *start, माप_प्रकार len, पूर्णांक flags)
अणु
#अगर_घोषित __NR_mlock2
	वापस syscall(__NR_mlock2, start, len, flags);
#अन्यथा
	त्रुटि_सं = ENOSYS;
	वापस -1;
#पूर्ण_अगर
पूर्ण

अटल खाता *seek_to_smaps_entry(अचिन्हित दीर्घ addr)
अणु
	खाता *file;
	अक्षर *line = शून्य;
	माप_प्रकार size = 0;
	अचिन्हित दीर्घ start, end;
	अक्षर perms[5];
	अचिन्हित दीर्घ offset;
	अक्षर dev[32];
	अचिन्हित दीर्घ inode;
	अक्षर path[बफ_मान];

	file = ख_खोलो("/proc/self/smaps", "r");
	अगर (!file) अणु
		लिखो_त्रुटि("fopen smaps");
		_निकास(1);
	पूर्ण

	जबतक (getline(&line, &size, file) > 0) अणु
		अगर (माला_पूछो(line, "%lx-%lx %s %lx %s %lu %s\n",
			   &start, &end, perms, &offset, dev, &inode, path) < 6)
			जाओ next;

		अगर (start <= addr && addr < end)
			जाओ out;

next:
		मुक्त(line);
		line = शून्य;
		size = 0;
	पूर्ण

	ख_बंद(file);
	file = शून्य;

out:
	मुक्त(line);
	वापस file;
पूर्ण
