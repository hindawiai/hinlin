<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 *   Copyright 2007 rPath, Inc. - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * Simple command-line parser क्रम early boot.
 */

#समावेश "boot.h"

अटल अंतरभूत पूर्णांक myहै_खाली(u8 c)
अणु
	वापस c <= ' ';	/* Close enough approximation */
पूर्ण

/*
 * Find a non-boolean option, that is, "option=argument".  In accordance
 * with standard Linux practice, अगर this option is repeated, this वापसs
 * the last instance on the command line.
 *
 * Returns the length of the argument (regardless of अगर it was
 * truncated to fit in the buffer), or -1 on not found.
 */
पूर्णांक __cmdline_find_option(अचिन्हित दीर्घ cmdline_ptr, स्थिर अक्षर *option, अक्षर *buffer, पूर्णांक bufsize)
अणु
	addr_t cptr;
	अक्षर c;
	पूर्णांक len = -1;
	स्थिर अक्षर *opptr = शून्य;
	अक्षर *bufptr = buffer;
	क्रमागत अणु
		st_wordstart,	/* Start of word/after whitespace */
		st_wordcmp,	/* Comparing this word */
		st_wordskip,	/* Miscompare, skip */
		st_bufcpy	/* Copying this to buffer */
	पूर्ण state = st_wordstart;

	अगर (!cmdline_ptr)
		वापस -1;      /* No command line */

	cptr = cmdline_ptr & 0xf;
	set_fs(cmdline_ptr >> 4);

	जबतक (cptr < 0x10000 && (c = rdfs8(cptr++))) अणु
		चयन (state) अणु
		हाल st_wordstart:
			अगर (myहै_खाली(c))
				अवरोध;

			/* अन्यथा */
			state = st_wordcmp;
			opptr = option;
			fallthrough;

		हाल st_wordcmp:
			अगर (c == '=' && !*opptr) अणु
				len = 0;
				bufptr = buffer;
				state = st_bufcpy;
			पूर्ण अन्यथा अगर (myहै_खाली(c)) अणु
				state = st_wordstart;
			पूर्ण अन्यथा अगर (c != *opptr++) अणु
				state = st_wordskip;
			पूर्ण
			अवरोध;

		हाल st_wordskip:
			अगर (myहै_खाली(c))
				state = st_wordstart;
			अवरोध;

		हाल st_bufcpy:
			अगर (myहै_खाली(c)) अणु
				state = st_wordstart;
			पूर्ण अन्यथा अणु
				अगर (len < bufsize-1)
					*bufptr++ = c;
				len++;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bufsize)
		*bufptr = '\0';

	वापस len;
पूर्ण

/*
 * Find a boolean option (like quiet,noapic,nosmp....)
 *
 * Returns the position of that option (starts counting with 1)
 * or 0 on not found
 */
पूर्णांक __cmdline_find_option_bool(अचिन्हित दीर्घ cmdline_ptr, स्थिर अक्षर *option)
अणु
	addr_t cptr;
	अक्षर c;
	पूर्णांक pos = 0, wstart = 0;
	स्थिर अक्षर *opptr = शून्य;
	क्रमागत अणु
		st_wordstart,	/* Start of word/after whitespace */
		st_wordcmp,	/* Comparing this word */
		st_wordskip,	/* Miscompare, skip */
	पूर्ण state = st_wordstart;

	अगर (!cmdline_ptr)
		वापस -1;      /* No command line */

	cptr = cmdline_ptr & 0xf;
	set_fs(cmdline_ptr >> 4);

	जबतक (cptr < 0x10000) अणु
		c = rdfs8(cptr++);
		pos++;

		चयन (state) अणु
		हाल st_wordstart:
			अगर (!c)
				वापस 0;
			अन्यथा अगर (myहै_खाली(c))
				अवरोध;

			state = st_wordcmp;
			opptr = option;
			wstart = pos;
			fallthrough;

		हाल st_wordcmp:
			अगर (!*opptr)
				अगर (!c || myहै_खाली(c))
					वापस wstart;
				अन्यथा
					state = st_wordskip;
			अन्यथा अगर (!c)
				वापस 0;
			अन्यथा अगर (c != *opptr++)
				state = st_wordskip;
			अवरोध;

		हाल st_wordskip:
			अगर (!c)
				वापस 0;
			अन्यथा अगर (myहै_खाली(c))
				state = st_wordstart;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;	/* Buffer overrun */
पूर्ण
