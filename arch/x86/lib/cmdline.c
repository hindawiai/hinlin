<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Misc librarized functions क्रम cmdline poking.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <यंत्र/setup.h>

अटल अंतरभूत पूर्णांक myहै_खाली(u8 c)
अणु
	वापस c <= ' ';	/* Close enough approximation */
पूर्ण

/**
 * Find a boolean option (like quiet,noapic,nosmp....)
 *
 * @cmdline: the cmdline string
 * @option: option string to look क्रम
 *
 * Returns the position of that @option (starts counting with 1)
 * or 0 on not found.  @option will only be found अगर it is found
 * as an entire word in @cmdline.  For instance, अगर @option="car"
 * then a cmdline which contains "cart" will not match.
 */
अटल पूर्णांक
__cmdline_find_option_bool(स्थिर अक्षर *cmdline, पूर्णांक max_cmdline_size,
			   स्थिर अक्षर *option)
अणु
	अक्षर c;
	पूर्णांक pos = 0, wstart = 0;
	स्थिर अक्षर *opptr = शून्य;
	क्रमागत अणु
		st_wordstart = 0,	/* Start of word/after whitespace */
		st_wordcmp,	/* Comparing this word */
		st_wordskip,	/* Miscompare, skip */
	पूर्ण state = st_wordstart;

	अगर (!cmdline)
		वापस -1;      /* No command line */

	/*
	 * This 'pos' check ensures we करो not overrun
	 * a non-शून्य-terminated 'cmdline'
	 */
	जबतक (pos < max_cmdline_size) अणु
		c = *(अक्षर *)cmdline++;
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
			अगर (!*opptr) अणु
				/*
				 * We matched all the way to the end of the
				 * option we were looking क्रम.  If the
				 * command-line has a space _or_ ends, then
				 * we matched!
				 */
				अगर (!c || myहै_खाली(c))
					वापस wstart;
				/*
				 * We hit the end of the option, but _not_
				 * the end of a word on the cmdline.  Not
				 * a match.
				 */
			पूर्ण अन्यथा अगर (!c) अणु
				/*
				 * Hit the शून्य terminator on the end of
				 * cmdline.
				 */
				वापस 0;
			पूर्ण अन्यथा अगर (c == *opptr++) अणु
				/*
				 * We are currently matching, so जारी
				 * to the next अक्षरacter on the cmdline.
				 */
				अवरोध;
			पूर्ण
			state = st_wordskip;
			fallthrough;

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

/*
 * Find a non-boolean option (i.e. option=argument). In accordance with
 * standard Linux practice, अगर this option is repeated, this वापसs the
 * last instance on the command line.
 *
 * @cmdline: the cmdline string
 * @max_cmdline_size: the maximum size of cmdline
 * @option: option string to look क्रम
 * @buffer: memory buffer to वापस the option argument
 * @bufsize: size of the supplied memory buffer
 *
 * Returns the length of the argument (regardless of अगर it was
 * truncated to fit in the buffer), or -1 on not found.
 */
अटल पूर्णांक
__cmdline_find_option(स्थिर अक्षर *cmdline, पूर्णांक max_cmdline_size,
		      स्थिर अक्षर *option, अक्षर *buffer, पूर्णांक bufsize)
अणु
	अक्षर c;
	पूर्णांक pos = 0, len = -1;
	स्थिर अक्षर *opptr = शून्य;
	अक्षर *bufptr = buffer;
	क्रमागत अणु
		st_wordstart = 0,	/* Start of word/after whitespace */
		st_wordcmp,	/* Comparing this word */
		st_wordskip,	/* Miscompare, skip */
		st_bufcpy,	/* Copying this to buffer */
	पूर्ण state = st_wordstart;

	अगर (!cmdline)
		वापस -1;      /* No command line */

	/*
	 * This 'pos' check ensures we करो not overrun
	 * a non-शून्य-terminated 'cmdline'
	 */
	जबतक (pos++ < max_cmdline_size) अणु
		c = *(अक्षर *)cmdline++;
		अगर (!c)
			अवरोध;

		चयन (state) अणु
		हाल st_wordstart:
			अगर (myहै_खाली(c))
				अवरोध;

			state = st_wordcmp;
			opptr = option;
			fallthrough;

		हाल st_wordcmp:
			अगर ((c == '=') && !*opptr) अणु
				/*
				 * We matched all the way to the end of the
				 * option we were looking क्रम, prepare to
				 * copy the argument.
				 */
				len = 0;
				bufptr = buffer;
				state = st_bufcpy;
				अवरोध;
			पूर्ण अन्यथा अगर (c == *opptr++) अणु
				/*
				 * We are currently matching, so जारी
				 * to the next अक्षरacter on the cmdline.
				 */
				अवरोध;
			पूर्ण
			state = st_wordskip;
			fallthrough;

		हाल st_wordskip:
			अगर (myहै_खाली(c))
				state = st_wordstart;
			अवरोध;

		हाल st_bufcpy:
			अगर (myहै_खाली(c)) अणु
				state = st_wordstart;
			पूर्ण अन्यथा अणु
				/*
				 * Increment len, but करोn't overrun the
				 * supplied buffer and leave room क्रम the
				 * शून्य terminator.
				 */
				अगर (++len < bufsize)
					*bufptr++ = c;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bufsize)
		*bufptr = '\0';

	वापस len;
पूर्ण

पूर्णांक cmdline_find_option_bool(स्थिर अक्षर *cmdline, स्थिर अक्षर *option)
अणु
	वापस __cmdline_find_option_bool(cmdline, COMMAND_LINE_SIZE, option);
पूर्ण

पूर्णांक cmdline_find_option(स्थिर अक्षर *cmdline, स्थिर अक्षर *option, अक्षर *buffer,
			पूर्णांक bufsize)
अणु
	वापस __cmdline_find_option(cmdline, COMMAND_LINE_SIZE, option,
				     buffer, bufsize);
पूर्ण
