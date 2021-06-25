<शैली गुरु>
/* Copyright (C) 2006 by Paolo Giarrusso - modअगरied from glibc' execvp.c.
   Original copyright notice follows:

   Copyright (C) 1991,92,1995-99,2002,2004 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is मुक्त software; you can redistribute it and/or
   modअगरy it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License क्रम more details.

   You should have received a copy of the GNU Lesser General Public
   License aदीर्घ with the GNU C Library; अगर not, ग_लिखो to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */
#समावेश <unistd.h>

#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>

#अगर_अघोषित TEST
#समावेश <um_दो_स्मृति.h>
#अन्यथा
#समावेश <मानकपन.स>
#घोषणा um_kदो_स्मृति दो_स्मृति
#पूर्ण_अगर
#समावेश <os.h>

/* Execute खाता, searching in the `PATH' environment variable अगर it contains
   no slashes, with arguments ARGV and environment from `environ'.  */
पूर्णांक execvp_noalloc(अक्षर *buf, स्थिर अक्षर *file, अक्षर *स्थिर argv[])
अणु
	अगर (*file == '\0') अणु
		वापस -ENOENT;
	पूर्ण

	अगर (म_अक्षर (file, '/') != शून्य) अणु
		/* Don't search when it contains a slash.  */
		execv(file, argv);
	पूर्ण अन्यथा अणु
		पूर्णांक got_eacces;
		माप_प्रकार len, pathlen;
		अक्षर *name, *p;
		अक्षर *path = दो_पर्या("PATH");
		अगर (path == शून्य)
			path = ":/bin:/usr/bin";

		len = म_माप(file) + 1;
		pathlen = म_माप(path);
		/* Copy the file name at the top.  */
		name = स_नकल(buf + pathlen + 1, file, len);
		/* And add the slash.  */
		*--name = '/';

		got_eacces = 0;
		p = path;
		करो अणु
			अक्षर *startp;

			path = p;
			//Let's aव्योम this GNU extension.
			//p = म_अक्षरnul (path, ':');
			p = म_अक्षर(path, ':');
			अगर (!p)
				p = म_अक्षर(path, '\0');

			अगर (p == path)
				/* Two adjacent colons, or a colon at the beginning or the end
				   of `PATH' means to search the current directory.  */
				startp = name + 1;
			अन्यथा
				startp = स_नकल(name - (p - path), path, p - path);

			/* Try to execute this name.  If it works, execv will not वापस.  */
			execv(startp, argv);

			/*
			अगर (त्रुटि_सं == ENOEXEC) अणु
			पूर्ण
			*/

			चयन (त्रुटि_सं) अणु
				हाल EACCES:
					/* Record the we got a `Permission denied' error.  If we end
					   up finding no executable we can use, we want to diagnose
					   that we did find one but were denied access.  */
					got_eacces = 1;
				हाल ENOENT:
				हाल ESTALE:
				हाल ENOTसूची:
					/* Those errors indicate the file is missing or not executable
					   by us, in which हाल we want to just try the next path
					   directory.  */
				हाल ENODEV:
				हाल ETIMEDOUT:
					/* Some strange fileप्रणालीs like AFS वापस even
					   stranger error numbers.  They cannot reasonably mean
					   anything अन्यथा so ignore those, too.  */
				हाल ENOEXEC:
					/* We won't go searching क्रम the shell
					 * अगर it is not executable - the Linux
					 * kernel alपढ़ोy handles this enough,
					 * क्रम us. */
					अवरोध;

				शेष:
					/* Some other error means we found an executable file, but
					   something went wrong executing it; वापस the error to our
					   caller.  */
					वापस -त्रुटि_सं;
			पूर्ण
		पूर्ण जबतक (*p++ != '\0');

		/* We tried every element and none of them worked.  */
		अगर (got_eacces)
			/* At least one failure was due to permissions, so report that
			   error.  */
			वापस -EACCES;
	पूर्ण

	/* Return the error from the last attempt (probably ENOENT).  */
	वापस -त्रुटि_सं;
पूर्ण
#अगर_घोषित TEST
पूर्णांक मुख्य(पूर्णांक argc, अक्षर**argv)
अणु
	अक्षर buf[PATH_MAX];
	पूर्णांक ret;
	argc--;
	अगर (!argc) अणु
		os_warn("Not enough arguments\n");
		वापस 1;
	पूर्ण
	argv++;
	अगर (ret = execvp_noalloc(buf, argv[0], argv)) अणु
		त्रुटि_सं = -ret;
		लिखो_त्रुटि("execvp_noalloc");
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर
