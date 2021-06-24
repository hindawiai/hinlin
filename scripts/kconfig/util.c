<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002-2005 Roman Zippel <zippel@linux-m68k.org>
 * Copyright (C) 2002-2005 Sam Ravnborg <sam@ravnborg.org>
 */

#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "lkc.h"

/* file alपढ़ोy present in list? If not add it */
काष्ठा file *file_lookup(स्थिर अक्षर *name)
अणु
	काष्ठा file *file;

	क्रम (file = file_list; file; file = file->next) अणु
		अगर (!म_भेद(name, file->name)) अणु
			वापस file;
		पूर्ण
	पूर्ण

	file = xदो_स्मृति(माप(*file));
	स_रखो(file, 0, माप(*file));
	file->name = xstrdup(name);
	file->next = file_list;
	file_list = file;
	वापस file;
पूर्ण

/* Allocate initial growable string */
काष्ठा gstr str_new(व्योम)
अणु
	काष्ठा gstr gs;
	gs.s = xदो_स्मृति(माप(अक्षर) * 64);
	gs.len = 64;
	gs.max_width = 0;
	म_नकल(gs.s, "\0");
	वापस gs;
पूर्ण

/* Free storage क्रम growable string */
व्योम str_मुक्त(काष्ठा gstr *gs)
अणु
	अगर (gs->s)
		मुक्त(gs->s);
	gs->s = शून्य;
	gs->len = 0;
पूर्ण

/* Append to growable string */
व्योम str_append(काष्ठा gstr *gs, स्थिर अक्षर *s)
अणु
	माप_प्रकार l;
	अगर (s) अणु
		l = म_माप(gs->s) + म_माप(s) + 1;
		अगर (l > gs->len) अणु
			gs->s = xपुनः_स्मृति(gs->s, l);
			gs->len = l;
		पूर्ण
		म_जोड़ो(gs->s, s);
	पूर्ण
पूर्ण

/* Append म_लिखो क्रमmatted string to growable string */
व्योम str_म_लिखो(काष्ठा gstr *gs, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	अक्षर s[10000]; /* big enough... */
	बहु_शुरू(ap, fmt);
	vsnम_लिखो(s, माप(s), fmt, ap);
	str_append(gs, s);
	बहु_पूर्ण(ap);
पूर्ण

/* Retrieve value of growable string */
स्थिर अक्षर *str_get(काष्ठा gstr *gs)
अणु
	वापस gs->s;
पूर्ण

व्योम *xदो_स्मृति(माप_प्रकार size)
अणु
	व्योम *p = दो_स्मृति(size);
	अगर (p)
		वापस p;
	ख_लिखो(मानक_त्रुटि, "Out of memory.\n");
	निकास(1);
पूर्ण

व्योम *xसुस्मृति(माप_प्रकार nmemb, माप_प्रकार size)
अणु
	व्योम *p = सुस्मृति(nmemb, size);
	अगर (p)
		वापस p;
	ख_लिखो(मानक_त्रुटि, "Out of memory.\n");
	निकास(1);
पूर्ण

व्योम *xपुनः_स्मृति(व्योम *p, माप_प्रकार size)
अणु
	p = पुनः_स्मृति(p, size);
	अगर (p)
		वापस p;
	ख_लिखो(मानक_त्रुटि, "Out of memory.\n");
	निकास(1);
पूर्ण

अक्षर *xstrdup(स्थिर अक्षर *s)
अणु
	अक्षर *p;

	p = strdup(s);
	अगर (p)
		वापस p;
	ख_लिखो(मानक_त्रुटि, "Out of memory.\n");
	निकास(1);
पूर्ण

अक्षर *xstrndup(स्थिर अक्षर *s, माप_प्रकार n)
अणु
	अक्षर *p;

	p = strndup(s, n);
	अगर (p)
		वापस p;
	ख_लिखो(मानक_त्रुटि, "Out of memory.\n");
	निकास(1);
पूर्ण
