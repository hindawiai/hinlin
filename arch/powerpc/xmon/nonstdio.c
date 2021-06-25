<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 1996-2005 Paul Mackerras.
 */
#समावेश <linux/माला.स>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/समय.स>
#समावेश "nonstdio.h"

अटल bool paginating, paginate_skipping;
अटल अचिन्हित दीर्घ paginate_lpp; /* Lines Per Page */
अटल अचिन्हित दीर्घ paginate_pos;

व्योम xmon_start_pagination(व्योम)
अणु
	paginating = true;
	paginate_skipping = false;
	paginate_pos = 0;
पूर्ण

व्योम xmon_end_pagination(व्योम)
अणु
	paginating = false;
पूर्ण

व्योम xmon_set_pagination_lpp(अचिन्हित दीर्घ lpp)
अणु
	paginate_lpp = lpp;
पूर्ण

अटल पूर्णांक xmon_पढ़ोअक्षर(व्योम)
अणु
	अगर (udbg_अ_लो)
		वापस udbg_अ_लो();
	वापस -1;
पूर्ण

अटल पूर्णांक xmon_ग_लिखो(स्थिर अक्षर *ptr, पूर्णांक nb)
अणु
	पूर्णांक rv = 0;
	स्थिर अक्षर *p = ptr, *q;
	स्थिर अक्षर msg[] = "[Hit a key (a:all, q:truncate, any:next page)]";

	अगर (nb <= 0)
		वापस rv;

	अगर (paginating && paginate_skipping)
		वापस nb;

	अगर (paginate_lpp) अणु
		जबतक (paginating && (q = म_अक्षर(p, '\n'))) अणु
			rv += udbg_ग_लिखो(p, q - p + 1);
			p = q + 1;
			paginate_pos++;

			अगर (paginate_pos >= paginate_lpp) अणु
				udbg_ग_लिखो(msg, म_माप(msg));

				चयन (xmon_पढ़ोअक्षर()) अणु
				हाल 'a':
					paginating = false;
					अवरोध;
				हाल 'q':
					paginate_skipping = true;
					अवरोध;
				शेष:
					/* nothing */
					अवरोध;
				पूर्ण

				paginate_pos = 0;
				udbg_ग_लिखो("\r\n", 2);

				अगर (paginate_skipping)
					वापस nb;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rv + udbg_ग_लिखो(p, nb - (p - ptr));
पूर्ण

पूर्णांक xmon_अक्षर_दो(पूर्णांक c)
अणु
	अक्षर ch = c;

	अगर (c == '\n')
		xmon_अक्षर_दो('\r');
	वापस xmon_ग_लिखो(&ch, 1) == 1? c: -1;
पूर्ण

अटल अक्षर line[256];
अटल अक्षर *lineptr;
अटल पूर्णांक lineleft;

अटल पूर्णांक xmon_अक्षर_लो(व्योम)
अणु
	पूर्णांक c;

	अगर (lineleft == 0) अणु
		lineptr = line;
		क्रम (;;) अणु
			c = xmon_पढ़ोअक्षर();
			अगर (c == -1 || c == 4)
				अवरोध;
			अगर (c == '\r' || c == '\n') अणु
				*lineptr++ = '\n';
				xmon_अक्षर_दो('\n');
				अवरोध;
			पूर्ण
			चयन (c) अणु
			हाल 0177:
			हाल '\b':
				अगर (lineptr > line) अणु
					xmon_अक्षर_दो('\b');
					xmon_अक्षर_दो(' ');
					xmon_अक्षर_दो('\b');
					--lineptr;
				पूर्ण
				अवरोध;
			हाल 'U' & 0x1F:
				जबतक (lineptr > line) अणु
					xmon_अक्षर_दो('\b');
					xmon_अक्षर_दो(' ');
					xmon_अक्षर_दो('\b');
					--lineptr;
				पूर्ण
				अवरोध;
			शेष:
				अगर (lineptr >= &line[माप(line) - 1])
					xmon_अक्षर_दो('\a');
				अन्यथा अणु
					xmon_अक्षर_दो(c);
					*lineptr++ = c;
				पूर्ण
			पूर्ण
		पूर्ण
		lineleft = lineptr - line;
		lineptr = line;
	पूर्ण
	अगर (lineleft == 0)
		वापस -1;
	--lineleft;
	वापस *lineptr++;
पूर्ण

अक्षर *xmon_माला_लो(अक्षर *str, पूर्णांक nb)
अणु
	अक्षर *p;
	पूर्णांक c;

	क्रम (p = str; p < str + nb - 1; ) अणु
		c = xmon_अक्षर_लो();
		अगर (c == -1) अणु
			अगर (p == str)
				वापस शून्य;
			अवरोध;
		पूर्ण
		*p++ = c;
		अगर (c == '\n')
			अवरोध;
	पूर्ण
	*p = 0;
	वापस str;
पूर्ण

व्योम xmon_म_लिखो(स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;
	अटल अक्षर xmon_outbuf[1024];
	पूर्णांक rc, n;

	बहु_शुरू(args, क्रमmat);
	n = vsnम_लिखो(xmon_outbuf, माप(xmon_outbuf), क्रमmat, args);
	बहु_पूर्ण(args);

	rc = xmon_ग_लिखो(xmon_outbuf, n);

	अगर (n && rc == 0) अणु
		/* No udbg hooks, fallback to prपूर्णांकk() - dangerous */
		pr_cont("%s", xmon_outbuf);
	पूर्ण
पूर्ण

व्योम xmon_माला_दो(स्थिर अक्षर *str)
अणु
	xmon_ग_लिखो(str, म_माप(str));
पूर्ण
