<शैली गुरु>
/*
 * Copyright (c) 2002 - 2011 Tony Finch <करोt@करोtat.at>
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * unअगरdef - हटाओ अगरdef'ed lines
 *
 * This code was derived from software contributed to Berkeley by Dave Yost.
 * It was rewritten to support ANSI C by Tony Finch. The original version
 * of unअगरdef carried the 4-clause BSD copyright licence. None of its code
 * reमुख्यs in this version (though some of the names reमुख्य) so it now
 * carries a more liberal licence.
 *
 *  Wishlist:
 *      provide an option which will append the name of the
 *        appropriate symbol after #अन्यथा's and #endif's
 *      provide an option which will check symbols after
 *        #अन्यथा's and #endif's to see that they match their
 *        corresponding #अगर_घोषित or #अगर_अघोषित
 *
 *   These require better buffer handling, which would also make
 *   it possible to handle all "dodgy" directives correctly.
 */

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>

#समावेश <प्रकार.स>
#समावेश <err.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

स्थिर अक्षर copyright[] =
    "@(#) $Version: unifdef-2.5 $\n"
    "@(#) $Author: Tony Finch (dot@dotat.at) $\n"
    "@(#) $URL: http://dotat.at/prog/unifdef $\n"
;

/* types of input lines: */
प्रकार क्रमागत अणु
	LT_TRUEI,		/* a true #अगर with ignore flag */
	LT_FALSEI,		/* a false #अगर with ignore flag */
	LT_IF,			/* an unknown #अगर */
	LT_TRUE,		/* a true #अगर */
	LT_FALSE,		/* a false #अगर */
	LT_ELIF,		/* an unknown #या_अगर */
	LT_ELTRUE,		/* a true #या_अगर */
	LT_ELFALSE,		/* a false #या_अगर */
	LT_ELSE,		/* #अन्यथा */
	LT_ENDIF,		/* #पूर्ण_अगर */
	LT_DODGY,		/* flag: directive is not on one line */
	LT_DODGY_LAST = LT_DODGY + LT_ENDIF,
	LT_PLAIN,		/* ordinary line */
	LT_खातापूर्ण,			/* end of file */
	LT_ERROR,		/* unevaluable #अगर */
	LT_COUNT
पूर्ण Linetype;

अटल अक्षर स्थिर * स्थिर linetype_name[] = अणु
	"TRUEI", "FALSEI", "IF", "TRUE", "FALSE",
	"ELIF", "ELTRUE", "ELFALSE", "ELSE", "ENDIF",
	"DODGY TRUEI", "DODGY FALSEI",
	"DODGY IF", "DODGY TRUE", "DODGY FALSE",
	"DODGY ELIF", "DODGY ELTRUE", "DODGY ELFALSE",
	"DODGY ELSE", "DODGY ENDIF",
	"PLAIN", "EOF", "ERROR"
पूर्ण;

/* state of #अगर processing */
प्रकार क्रमागत अणु
	IS_OUTSIDE,
	IS_FALSE_PREFIX,	/* false #अगर followed by false #या_अगरs */
	IS_TRUE_PREFIX,		/* first non-false #(el)अगर is true */
	IS_PASS_MIDDLE,		/* first non-false #(el)अगर is unknown */
	IS_FALSE_MIDDLE,	/* a false #या_अगर after a pass state */
	IS_TRUE_MIDDLE,		/* a true #या_अगर after a pass state */
	IS_PASS_ELSE,		/* an अन्यथा after a pass state */
	IS_FALSE_ELSE,		/* an अन्यथा after a true state */
	IS_TRUE_ELSE,		/* an अन्यथा after only false states */
	IS_FALSE_TRAILER,	/* #या_अगरs after a true are false */
	IS_COUNT
पूर्ण Iख_स्थितिe;

अटल अक्षर स्थिर * स्थिर अगरstate_name[] = अणु
	"OUTSIDE", "FALSE_PREFIX", "TRUE_PREFIX",
	"PASS_MIDDLE", "FALSE_MIDDLE", "TRUE_MIDDLE",
	"PASS_ELSE", "FALSE_ELSE", "TRUE_ELSE",
	"FALSE_TRAILER"
पूर्ण;

/* state of comment parser */
प्रकार क्रमागत अणु
	NO_COMMENT = false,	/* outside a comment */
	C_COMMENT,		/* in a comment like this one */
	CXX_COMMENT,		/* between // and end of line */
	STARTING_COMMENT,	/* just after slash-backslash-newline */
	FINISHING_COMMENT,	/* star-backslash-newline in a C comment */
	CHAR_LITERAL,		/* inside '' */
	STRING_LITERAL		/* inside "" */
पूर्ण Comment_state;

अटल अक्षर स्थिर * स्थिर comment_name[] = अणु
	"NO", "C", "CXX", "STARTING", "FINISHING", "CHAR", "STRING"
पूर्ण;

/* state of preprocessor line parser */
प्रकार क्रमागत अणु
	LS_START,		/* only space and comments on this line */
	LS_HASH,		/* only space, comments, and a hash */
	LS_सूचीTY		/* this line can't be a preprocessor line */
पूर्ण Line_state;

अटल अक्षर स्थिर * स्थिर linestate_name[] = अणु
	"START", "HASH", "DIRTY"
पूर्ण;

/*
 * Minimum translation limits from ISO/IEC 9899:1999 5.2.4.1
 */
#घोषणा	MAXDEPTH        64			/* maximum #अगर nesting */
#घोषणा	MAXLINE         4096			/* maximum length of line */
#घोषणा	MAXSYMS         4096			/* maximum number of symbols */

/*
 * Someबार when editing a keyword the replacement text is दीर्घer, so
 * we leave some space at the end of the tline buffer to accommodate this.
 */
#घोषणा	EDITSLOP        10

/*
 * For temporary filenames
 */
#घोषणा TEMPLATE        "unifdef.XXXXXX"

/*
 * Globals.
 */

अटल bool             compblank;		/* -B: compress blank lines */
अटल bool             lnblank;		/* -b: blank deleted lines */
अटल bool             complement;		/* -c: करो the complement */
अटल bool             debugging;		/* -d: debugging reports */
अटल bool             iocccok;		/* -e: fewer IOCCC errors */
अटल bool             strictlogic;		/* -K: keep ambiguous #अगरs */
अटल bool             समाप्तस्थिरs;		/* -k: eval स्थिरant #अगरs */
अटल bool             lnnum;			/* -n: add #पंक्ति directives */
अटल bool             symlist;		/* -s: output symbol list */
अटल bool             symdepth;		/* -S: output symbol depth */
अटल bool             text;			/* -t: this is a text file */

अटल स्थिर अक्षर      *symname[MAXSYMS];	/* symbol name */
अटल स्थिर अक्षर      *value[MAXSYMS];		/* -Dsym=value */
अटल bool             ignore[MAXSYMS];	/* -iDsym or -iUsym */
अटल पूर्णांक              nsyms;			/* number of symbols */

अटल खाता            *input;			/* input file poपूर्णांकer */
अटल स्थिर अक्षर      *filename;		/* input file name */
अटल पूर्णांक              linक्रमागत;		/* current line number */
अटल खाता            *output;			/* output file poपूर्णांकer */
अटल स्थिर अक्षर      *ofilename;		/* output file name */
अटल bool             overwriting;		/* output overग_लिखोs input */
अटल अक्षर             tempname[खातानाम_उच्च];	/* used when overwriting */

अटल अक्षर             tline[MAXLINE+EDITSLOP];/* input buffer plus space */
अटल अक्षर            *keyword;		/* used क्रम editing #या_अगर's */

अटल स्थिर अक्षर      *newline;		/* input file क्रमmat */
अटल स्थिर अक्षर       newline_unix[] = "\n";
अटल स्थिर अक्षर       newline_crlf[] = "\r\n";

अटल Comment_state    incomment;		/* comment parser state */
अटल Line_state       linestate;		/* #अगर line parser state */
अटल Iख_स्थितिe          अगरstate[MAXDEPTH];	/* #अगर processor state */
अटल bool             ignoring[MAXDEPTH];	/* ignore comments state */
अटल पूर्णांक              stअगरline[MAXDEPTH];	/* start of current #अगर */
अटल पूर्णांक              depth;			/* current #अगर nesting */
अटल पूर्णांक              delcount;		/* count of deleted lines */
अटल अचिन्हित         blankcount;		/* count of blank lines */
अटल अचिन्हित         blankmax;		/* maximum recent blankcount */
अटल bool             स्थिरexpr;		/* स्थिरant #अगर expression */
अटल bool             zerosyms = true;	/* to क्रमmat symdepth output */
अटल bool             firstsym;		/* ditto */

अटल पूर्णांक              निकासstat;		/* program निकास status */

अटल व्योम             addsym(bool, bool, अक्षर *);
अटल व्योम             बंदout(व्योम);
अटल व्योम             debug(स्थिर अक्षर *, ...);
अटल व्योम             करोne(व्योम);
अटल व्योम             error(स्थिर अक्षर *);
अटल पूर्णांक              findsym(स्थिर अक्षर *);
अटल व्योम             flushline(bool);
अटल Linetype         parseline(व्योम);
अटल Linetype         अगरeval(स्थिर अक्षर **);
अटल व्योम             ignoreoff(व्योम);
अटल व्योम             ignoreon(व्योम);
अटल व्योम             keywordedit(स्थिर अक्षर *);
अटल व्योम             nest(व्योम);
अटल व्योम             process(व्योम);
अटल स्थिर अक्षर      *skipargs(स्थिर अक्षर *);
अटल स्थिर अक्षर      *skipcomment(स्थिर अक्षर *);
अटल स्थिर अक्षर      *skipsym(स्थिर अक्षर *);
अटल व्योम             state(Iख_स्थितिe);
अटल पूर्णांक              strlcmp(स्थिर अक्षर *, स्थिर अक्षर *, माप_प्रकार);
अटल व्योम             unnest(व्योम);
अटल व्योम             usage(व्योम);
अटल व्योम             version(व्योम);

#घोषणा endsym(c) (!है_अक्षर_अंक((अचिन्हित अक्षर)c) && c != '_')

/*
 * The मुख्य program.
 */
पूर्णांक
मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक opt;

	जबतक ((opt = getopt(argc, argv, "i:D:U:I:o:bBcdeKklnsStV")) != -1)
		चयन (opt) अणु
		हाल 'i': /* treat stuff controlled by these symbols as text */
			/*
			 * For strict backwards-compatibility the U or D
			 * should be immediately after the -i but it करोesn't
			 * matter much अगर we relax that requirement.
			 */
			opt = *optarg++;
			अगर (opt == 'D')
				addsym(true, true, optarg);
			अन्यथा अगर (opt == 'U')
				addsym(true, false, optarg);
			अन्यथा
				usage();
			अवरोध;
		हाल 'D': /* define a symbol */
			addsym(false, true, optarg);
			अवरोध;
		हाल 'U': /* undef a symbol */
			addsym(false, false, optarg);
			अवरोध;
		हाल 'I': /* no-op क्रम compatibility with cpp */
			अवरोध;
		हाल 'b': /* blank deleted lines instead of omitting them */
		हाल 'l': /* backwards compatibility */
			lnblank = true;
			अवरोध;
		हाल 'B': /* compress blank lines around हटाओd section */
			compblank = true;
			अवरोध;
		हाल 'c': /* treat -D as -U and vice versa */
			complement = true;
			अवरोध;
		हाल 'd':
			debugging = true;
			अवरोध;
		हाल 'e': /* fewer errors from करोdgy lines */
			iocccok = true;
			अवरोध;
		हाल 'K': /* keep ambiguous #अगरs */
			strictlogic = true;
			अवरोध;
		हाल 'k': /* process स्थिरant #अगरs */
			समाप्तस्थिरs = true;
			अवरोध;
		हाल 'n': /* add #पंक्ति directive after deleted lines */
			lnnum = true;
			अवरोध;
		हाल 'o': /* output to a file */
			ofilename = optarg;
			अवरोध;
		हाल 's': /* only output list of symbols that control #अगरs */
			symlist = true;
			अवरोध;
		हाल 'S': /* list symbols with their nesting depth */
			symlist = symdepth = true;
			अवरोध;
		हाल 't': /* don't parse C comments */
			text = true;
			अवरोध;
		हाल 'V': /* prपूर्णांक version */
			version();
		शेष:
			usage();
		पूर्ण
	argc -= optind;
	argv += optind;
	अगर (compblank && lnblank)
		errx(2, "-B and -b are mutually exclusive");
	अगर (argc > 1) अणु
		errx(2, "can only do one file");
	पूर्ण अन्यथा अगर (argc == 1 && म_भेद(*argv, "-") != 0) अणु
		filename = *argv;
		input = ख_खोलो(filename, "rb");
		अगर (input == शून्य)
			err(2, "can't open %s", filename);
	पूर्ण अन्यथा अणु
		filename = "[stdin]";
		input = मानक_निवेश;
	पूर्ण
	अगर (ofilename == शून्य) अणु
		ofilename = "[stdout]";
		output = मानक_निकास;
	पूर्ण अन्यथा अणु
		काष्ठा stat ist, ost;
		अगर (stat(ofilename, &ost) == 0 &&
		    ख_स्थिति(fileno(input), &ist) == 0)
			overwriting = (ist.st_dev == ost.st_dev
				    && ist.st_ino == ost.st_ino);
		अगर (overwriting) अणु
			स्थिर अक्षर *dirsep;
			पूर्णांक ofd;

			dirsep = म_खोजप(ofilename, '/');
			अगर (dirsep != शून्य)
				snम_लिखो(tempname, माप(tempname),
				    "%.*s/" TEMPLATE,
				    (पूर्णांक)(dirsep - ofilename), ofilename);
			अन्यथा
				snम_लिखो(tempname, माप(tempname),
				    TEMPLATE);
			ofd = mkstemp(tempname);
			अगर (ofd != -1)
				output = fकरोpen(ofd, "wb+");
			अगर (output == शून्य)
				err(2, "can't create temporary file");
			fchmod(ofd, ist.st_mode & (S_IRWXU|S_IRWXG|S_IRWXO));
		पूर्ण अन्यथा अणु
			output = ख_खोलो(ofilename, "wb");
			अगर (output == शून्य)
				err(2, "can't open %s", ofilename);
		पूर्ण
	पूर्ण
	process();
	पात(); /* bug */
पूर्ण

अटल व्योम
version(व्योम)
अणु
	स्थिर अक्षर *c = copyright;
	क्रम (;;) अणु
		जबतक (*++c != '$')
			अगर (*c == '\0')
				निकास(0);
		जबतक (*++c != '$')
			अ_दो(*c, मानक_त्रुटि);
		अ_दो('\n', मानक_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम
usage(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "usage: unifdef [-bBcdeKknsStV] [-Ipath]"
	    " [-Dsym[=val]] [-Usym] [-iDsym[=val]] [-iUsym] ... [file]\n");
	निकास(2);
पूर्ण

/*
 * A state transition function alters the global #अगर processing state
 * in a particular way. The table below is indexed by the current
 * processing state and the type of the current line.
 *
 * Nesting is handled by keeping a stack of states; some transition
 * functions increase or decrease the depth. They also मुख्यtain the
 * ignore state on a stack. In some complicated हालs they have to
 * alter the preprocessor directive, as follows.
 *
 * When we have processed a group that starts off with a known-false
 * #अगर/#या_अगर sequence (which has thereक्रमe been deleted) followed by a
 * #या_अगर that we करोn't understand and thereक्रमe must keep, we edit the
 * latter पूर्णांकo a #अगर to keep the nesting correct. We use स_नकल() to
 * overग_लिखो the 4 byte token "elif" with "if  " without a '\0' byte.
 *
 * When we find a true #या_अगर in a group, the following block will
 * always be kept and the rest of the sequence after the next #या_अगर or
 * #अन्यथा will be discarded. We edit the #या_अगर पूर्णांकo a #अन्यथा and the
 * following directive to #पूर्ण_अगर since this has the desired behaviour.
 *
 * "Dodgy" directives are split across multiple lines, the most common
 * example being a multi-line comment hanging off the right of the
 * directive. We can handle them correctly only अगर there is no change
 * from prपूर्णांकing to dropping (or vice versa) caused by that directive.
 * If the directive is the first of a group we have a choice between
 * failing with an error, or passing it through unchanged instead of
 * evaluating it. The latter is not the शेष to aव्योम questions from
 * users about unअगरdef unexpectedly leaving behind preprocessor directives.
 */
प्रकार व्योम state_fn(व्योम);

/* report an error */
अटल व्योम Eelअगर (व्योम) अणु error("Inappropriate #elif"); पूर्ण
अटल व्योम Eअन्यथा (व्योम) अणु error("Inappropriate #else"); पूर्ण
अटल व्योम Eendअगर(व्योम) अणु error("Inappropriate #endif"); पूर्ण
अटल व्योम Eeof  (व्योम) अणु error("Premature EOF"); पूर्ण
अटल व्योम Eioccc(व्योम) अणु error("Obfuscated preprocessor control line"); पूर्ण
/* plain line handling */
अटल व्योम prपूर्णांक (व्योम) अणु flushline(true); पूर्ण
अटल व्योम drop  (व्योम) अणु flushline(false); पूर्ण
/* output lacks group's start line */
अटल व्योम Strue (व्योम) अणु drop();  ignoreoff(); state(IS_TRUE_PREFIX); पूर्ण
अटल व्योम Sfalse(व्योम) अणु drop();  ignoreoff(); state(IS_FALSE_PREFIX); पूर्ण
अटल व्योम Sअन्यथा (व्योम) अणु drop();               state(IS_TRUE_ELSE); पूर्ण
/* prपूर्णांक/pass this block */
अटल व्योम Pelअगर (व्योम) अणु prपूर्णांक(); ignoreoff(); state(IS_PASS_MIDDLE); पूर्ण
अटल व्योम Pअन्यथा (व्योम) अणु prपूर्णांक();              state(IS_PASS_ELSE); पूर्ण
अटल व्योम Pendअगर(व्योम) अणु prपूर्णांक(); unnest(); पूर्ण
/* discard this block */
अटल व्योम Dfalse(व्योम) अणु drop();  ignoreoff(); state(IS_FALSE_TRAILER); पूर्ण
अटल व्योम Delअगर (व्योम) अणु drop();  ignoreoff(); state(IS_FALSE_MIDDLE); पूर्ण
अटल व्योम Dअन्यथा (व्योम) अणु drop();               state(IS_FALSE_ELSE); पूर्ण
अटल व्योम Dendअगर(व्योम) अणु drop();  unnest(); पूर्ण
/* first line of group */
अटल व्योम Fdrop (व्योम) अणु nest();  Dfalse(); पूर्ण
अटल व्योम Fpass (व्योम) अणु nest();  Pelअगर(); पूर्ण
अटल व्योम Ftrue (व्योम) अणु nest();  Strue(); पूर्ण
अटल व्योम Ffalse(व्योम) अणु nest();  Sfalse(); पूर्ण
/* variable pedantry क्रम obfuscated lines */
अटल व्योम Oअगरfy (व्योम) अणु अगर (!iocccok) Eioccc(); Fpass(); ignoreon(); पूर्ण
अटल व्योम Oअगर   (व्योम) अणु अगर (!iocccok) Eioccc(); Fpass(); पूर्ण
अटल व्योम Oelअगर (व्योम) अणु अगर (!iocccok) Eioccc(); Pelअगर(); पूर्ण
/* ignore comments in this block */
अटल व्योम Idrop (व्योम) अणु Fdrop();  ignoreon(); पूर्ण
अटल व्योम Itrue (व्योम) अणु Ftrue();  ignoreon(); पूर्ण
अटल व्योम Ifalse(व्योम) अणु Ffalse(); ignoreon(); पूर्ण
/* modअगरy this line */
अटल व्योम Mpass (व्योम) अणु स_नकल(keyword, "if  ", 4); Pelअगर(); पूर्ण
अटल व्योम Mtrue (व्योम) अणु keywordedit("else");  state(IS_TRUE_MIDDLE); पूर्ण
अटल व्योम Melअगर (व्योम) अणु keywordedit("endif"); state(IS_FALSE_TRAILER); पूर्ण
अटल व्योम Mअन्यथा (व्योम) अणु keywordedit("endif"); state(IS_FALSE_ELSE); पूर्ण

अटल state_fn * स्थिर trans_table[IS_COUNT][LT_COUNT] = अणु
/* IS_OUTSIDE */
अणु Itrue, Ifalse,Fpass, Ftrue, Ffalse,Eelअगर, Eelअगर, Eelअगर, Eअन्यथा, Eendअगर,
  Oअगरfy, Oअगरfy, Fpass, Oअगर,   Oअगर,   Eelअगर, Eelअगर, Eelअगर, Eअन्यथा, Eendअगर,
  prपूर्णांक, करोne,  पात पूर्ण,
/* IS_FALSE_PREFIX */
अणु Idrop, Idrop, Fdrop, Fdrop, Fdrop, Mpass, Strue, Sfalse,Sअन्यथा, Dendअगर,
  Idrop, Idrop, Fdrop, Fdrop, Fdrop, Mpass, Eioccc,Eioccc,Eioccc,Eioccc,
  drop,  Eeof,  पात पूर्ण,
/* IS_TRUE_PREFIX */
अणु Itrue, Ifalse,Fpass, Ftrue, Ffalse,Dfalse,Dfalse,Dfalse,Dअन्यथा, Dendअगर,
  Oअगरfy, Oअगरfy, Fpass, Oअगर,   Oअगर,   Eioccc,Eioccc,Eioccc,Eioccc,Eioccc,
  prपूर्णांक, Eeof,  पात पूर्ण,
/* IS_PASS_MIDDLE */
अणु Itrue, Ifalse,Fpass, Ftrue, Ffalse,Pelअगर, Mtrue, Delअगर, Pअन्यथा, Pendअगर,
  Oअगरfy, Oअगरfy, Fpass, Oअगर,   Oअगर,   Pelअगर, Oelअगर, Oelअगर, Pअन्यथा, Pendअगर,
  prपूर्णांक, Eeof,  पात पूर्ण,
/* IS_FALSE_MIDDLE */
अणु Idrop, Idrop, Fdrop, Fdrop, Fdrop, Pelअगर, Mtrue, Delअगर, Pअन्यथा, Pendअगर,
  Idrop, Idrop, Fdrop, Fdrop, Fdrop, Eioccc,Eioccc,Eioccc,Eioccc,Eioccc,
  drop,  Eeof,  पात पूर्ण,
/* IS_TRUE_MIDDLE */
अणु Itrue, Ifalse,Fpass, Ftrue, Ffalse,Melअगर, Melअगर, Melअगर, Mअन्यथा, Pendअगर,
  Oअगरfy, Oअगरfy, Fpass, Oअगर,   Oअगर,   Eioccc,Eioccc,Eioccc,Eioccc,Pendअगर,
  prपूर्णांक, Eeof,  पात पूर्ण,
/* IS_PASS_ELSE */
अणु Itrue, Ifalse,Fpass, Ftrue, Ffalse,Eelअगर, Eelअगर, Eelअगर, Eअन्यथा, Pendअगर,
  Oअगरfy, Oअगरfy, Fpass, Oअगर,   Oअगर,   Eelअगर, Eelअगर, Eelअगर, Eअन्यथा, Pendअगर,
  prपूर्णांक, Eeof,  पात पूर्ण,
/* IS_FALSE_ELSE */
अणु Idrop, Idrop, Fdrop, Fdrop, Fdrop, Eelअगर, Eelअगर, Eelअगर, Eअन्यथा, Dendअगर,
  Idrop, Idrop, Fdrop, Fdrop, Fdrop, Eelअगर, Eelअगर, Eelअगर, Eअन्यथा, Eioccc,
  drop,  Eeof,  पात पूर्ण,
/* IS_TRUE_ELSE */
अणु Itrue, Ifalse,Fpass, Ftrue, Ffalse,Eelअगर, Eelअगर, Eelअगर, Eअन्यथा, Dendअगर,
  Oअगरfy, Oअगरfy, Fpass, Oअगर,   Oअगर,   Eelअगर, Eelअगर, Eelअगर, Eअन्यथा, Eioccc,
  prपूर्णांक, Eeof,  पात पूर्ण,
/* IS_FALSE_TRAILER */
अणु Idrop, Idrop, Fdrop, Fdrop, Fdrop, Dfalse,Dfalse,Dfalse,Dअन्यथा, Dendअगर,
  Idrop, Idrop, Fdrop, Fdrop, Fdrop, Dfalse,Dfalse,Dfalse,Dअन्यथा, Eioccc,
  drop,  Eeof,  पात पूर्ण
/*TRUEI  FALSEI IF     TRUE   FALSE  ELIF   ELTRUE ELFALSE ELSE  ENDIF
  TRUEI  FALSEI IF     TRUE   FALSE  ELIF   ELTRUE ELFALSE ELSE  ENDIF (DODGY)
  PLAIN  खातापूर्ण    ERROR */
पूर्ण;

/*
 * State machine utility functions
 */
अटल व्योम
ignoreoff(व्योम)
अणु
	अगर (depth == 0)
		पात(); /* bug */
	ignoring[depth] = ignoring[depth-1];
पूर्ण
अटल व्योम
ignoreon(व्योम)
अणु
	ignoring[depth] = true;
पूर्ण
अटल व्योम
keywordedit(स्थिर अक्षर *replacement)
अणु
	snम_लिखो(keyword, tline + माप(tline) - keyword,
	    "%s%s", replacement, newline);
	prपूर्णांक();
पूर्ण
अटल व्योम
nest(व्योम)
अणु
	अगर (depth > MAXDEPTH-1)
		पात(); /* bug */
	अगर (depth == MAXDEPTH-1)
		error("Too many levels of nesting");
	depth += 1;
	stअगरline[depth] = linक्रमागत;
पूर्ण
अटल व्योम
unnest(व्योम)
अणु
	अगर (depth == 0)
		पात(); /* bug */
	depth -= 1;
पूर्ण
अटल व्योम
state(Iख_स्थितिe is)
अणु
	अगरstate[depth] = is;
पूर्ण

/*
 * Write a line to the output or not, according to command line options.
 */
अटल व्योम
flushline(bool keep)
अणु
	अगर (symlist)
		वापस;
	अगर (keep ^ complement) अणु
		bool blankline = tline[म_अखोज(tline, " \t\r\n")] == '\0';
		अगर (blankline && compblank && blankcount != blankmax) अणु
			delcount += 1;
			blankcount += 1;
		पूर्ण अन्यथा अणु
			अगर (lnnum && delcount > 0)
				म_लिखो("#line %d%s", linक्रमागत, newline);
			ख_माला_दो(tline, output);
			delcount = 0;
			blankmax = blankcount = blankline ? blankcount + 1 : 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (lnblank)
			ख_माला_दो(newline, output);
		निकासstat = 1;
		delcount += 1;
		blankcount = 0;
	पूर्ण
	अगर (debugging)
		ख_साफ(output);
पूर्ण

/*
 * The driver क्रम the state machine.
 */
अटल व्योम
process(व्योम)
अणु
	/* When compressing blank lines, act as अगर the file
	   is preceded by a large number of blank lines. */
	blankmax = blankcount = 1000;
	क्रम (;;) अणु
		Linetype lineval = parseline();
		trans_table[अगरstate[depth]][lineval]();
		debug("process line %d %s -> %s depth %d",
		    linक्रमागत, linetype_name[lineval],
		    अगरstate_name[अगरstate[depth]], depth);
	पूर्ण
पूर्ण

/*
 * Flush the output and handle errors.
 */
अटल व्योम
बंदout(व्योम)
अणु
	अगर (symdepth && !zerosyms)
		म_लिखो("\n");
	अगर (ख_बंद(output) == खातापूर्ण) अणु
		warn("couldn't write to %s", ofilename);
		अगर (overwriting) अणु
			unlink(tempname);
			errx(2, "%s unchanged", filename);
		पूर्ण अन्यथा अणु
			निकास(2);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Clean up and निकास.
 */
अटल व्योम
करोne(व्योम)
अणु
	अगर (incomment)
		error("EOF in comment");
	बंदout();
	अगर (overwriting && नाम(tempname, ofilename) == -1) अणु
		warn("couldn't rename temporary file");
		unlink(tempname);
		errx(2, "%s unchanged", ofilename);
	पूर्ण
	निकास(निकासstat);
पूर्ण

/*
 * Parse a line and determine its type. We keep the preprocessor line
 * parser state between calls in the global variable linestate, with
 * help from skipcomment().
 */
अटल Linetype
parseline(व्योम)
अणु
	स्थिर अक्षर *cp;
	पूर्णांक cursym;
	पूर्णांक kwlen;
	Linetype retval;
	Comment_state wascomment;

	linक्रमागत++;
	अगर (ख_माला_लो(tline, MAXLINE, input) == शून्य)
		वापस (LT_खातापूर्ण);
	अगर (newline == शून्य) अणु
		अगर (म_खोजप(tline, '\n') == strrchr(tline, '\r') + 1)
			newline = newline_crlf;
		अन्यथा
			newline = newline_unix;
	पूर्ण
	retval = LT_PLAIN;
	wascomment = incomment;
	cp = skipcomment(tline);
	अगर (linestate == LS_START) अणु
		अगर (*cp == '#') अणु
			linestate = LS_HASH;
			firstsym = true;
			cp = skipcomment(cp + 1);
		पूर्ण अन्यथा अगर (*cp != '\0')
			linestate = LS_सूचीTY;
	पूर्ण
	अगर (!incomment && linestate == LS_HASH) अणु
		keyword = tline + (cp - tline);
		cp = skipsym(cp);
		kwlen = cp - keyword;
		/* no way can we deal with a continuation inside a keyword */
		अगर (म_भेदन(cp, "\\\r\n", 3) == 0 ||
		    म_भेदन(cp, "\\\n", 2) == 0)
			Eioccc();
		अगर (strlcmp("ifdef", keyword, kwlen) == 0 ||
		    strlcmp("ifndef", keyword, kwlen) == 0) अणु
			cp = skipcomment(cp);
			अगर ((cursym = findsym(cp)) < 0)
				retval = LT_IF;
			अन्यथा अणु
				retval = (keyword[2] == 'n')
				    ? LT_FALSE : LT_TRUE;
				अगर (value[cursym] == शून्य)
					retval = (retval == LT_TRUE)
					    ? LT_FALSE : LT_TRUE;
				अगर (ignore[cursym])
					retval = (retval == LT_TRUE)
					    ? LT_TRUEI : LT_FALSEI;
			पूर्ण
			cp = skipsym(cp);
		पूर्ण अन्यथा अगर (strlcmp("if", keyword, kwlen) == 0)
			retval = अगरeval(&cp);
		अन्यथा अगर (strlcmp("elif", keyword, kwlen) == 0)
			retval = अगरeval(&cp) - LT_IF + LT_ELIF;
		अन्यथा अगर (strlcmp("else", keyword, kwlen) == 0)
			retval = LT_ELSE;
		अन्यथा अगर (strlcmp("endif", keyword, kwlen) == 0)
			retval = LT_ENDIF;
		अन्यथा अणु
			linestate = LS_सूचीTY;
			retval = LT_PLAIN;
		पूर्ण
		cp = skipcomment(cp);
		अगर (*cp != '\0') अणु
			linestate = LS_सूचीTY;
			अगर (retval == LT_TRUE || retval == LT_FALSE ||
			    retval == LT_TRUEI || retval == LT_FALSEI)
				retval = LT_IF;
			अगर (retval == LT_ELTRUE || retval == LT_ELFALSE)
				retval = LT_ELIF;
		पूर्ण
		अगर (retval != LT_PLAIN && (wascomment || incomment)) अणु
			retval += LT_DODGY;
			अगर (incomment)
				linestate = LS_सूचीTY;
		पूर्ण
		/* skipcomment normally changes the state, except
		   अगर the last line of the file lacks a newline, or
		   अगर there is too much whitespace in a directive */
		अगर (linestate == LS_HASH) अणु
			माप_प्रकार len = cp - tline;
			अगर (ख_माला_लो(tline + len, MAXLINE - len, input) == शून्य) अणु
				/* append the missing newline */
				म_नकल(tline + len, newline);
				cp += म_माप(newline);
				linestate = LS_START;
			पूर्ण अन्यथा अणु
				linestate = LS_सूचीTY;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (linestate == LS_सूचीTY) अणु
		जबतक (*cp != '\0')
			cp = skipcomment(cp + 1);
	पूर्ण
	debug("parser line %d state %s comment %s line", linक्रमागत,
	    comment_name[incomment], linestate_name[linestate]);
	वापस (retval);
पूर्ण

/*
 * These are the binary चालकs that are supported by the expression
 * evaluator.
 */
अटल Linetype op_strict(पूर्णांक *p, पूर्णांक v, Linetype at, Linetype bt) अणु
	अगर(at == LT_IF || bt == LT_IF) वापस (LT_IF);
	वापस (*p = v, v ? LT_TRUE : LT_FALSE);
पूर्ण
अटल Linetype op_lt(पूर्णांक *p, Linetype at, पूर्णांक a, Linetype bt, पूर्णांक b) अणु
	वापस op_strict(p, a < b, at, bt);
पूर्ण
अटल Linetype op_gt(पूर्णांक *p, Linetype at, पूर्णांक a, Linetype bt, पूर्णांक b) अणु
	वापस op_strict(p, a > b, at, bt);
पूर्ण
अटल Linetype op_le(पूर्णांक *p, Linetype at, पूर्णांक a, Linetype bt, पूर्णांक b) अणु
	वापस op_strict(p, a <= b, at, bt);
पूर्ण
अटल Linetype op_ge(पूर्णांक *p, Linetype at, पूर्णांक a, Linetype bt, पूर्णांक b) अणु
	वापस op_strict(p, a >= b, at, bt);
पूर्ण
अटल Linetype op_eq(पूर्णांक *p, Linetype at, पूर्णांक a, Linetype bt, पूर्णांक b) अणु
	वापस op_strict(p, a == b, at, bt);
पूर्ण
अटल Linetype op_ne(पूर्णांक *p, Linetype at, पूर्णांक a, Linetype bt, पूर्णांक b) अणु
	वापस op_strict(p, a != b, at, bt);
पूर्ण
अटल Linetype op_or(पूर्णांक *p, Linetype at, पूर्णांक a, Linetype bt, पूर्णांक b) अणु
	अगर (!strictlogic && (at == LT_TRUE || bt == LT_TRUE))
		वापस (*p = 1, LT_TRUE);
	वापस op_strict(p, a || b, at, bt);
पूर्ण
अटल Linetype op_and(पूर्णांक *p, Linetype at, पूर्णांक a, Linetype bt, पूर्णांक b) अणु
	अगर (!strictlogic && (at == LT_FALSE || bt == LT_FALSE))
		वापस (*p = 0, LT_FALSE);
	वापस op_strict(p, a && b, at, bt);
पूर्ण

/*
 * An evaluation function takes three arguments, as follows: (1) a poपूर्णांकer to
 * an element of the precedence table which lists the चालकs at the current
 * level of precedence; (2) a poपूर्णांकer to an पूर्णांकeger which will receive the
 * value of the expression; and (3) a poपूर्णांकer to a अक्षर* that poपूर्णांकs to the
 * expression to be evaluated and that is updated to the end of the expression
 * when evaluation is complete. The function वापसs LT_FALSE अगर the value of
 * the expression is zero, LT_TRUE अगर it is non-zero, LT_IF अगर the expression
 * depends on an unknown symbol, or LT_ERROR अगर there is a parse failure.
 */
काष्ठा ops;

प्रकार Linetype eval_fn(स्थिर काष्ठा ops *, पूर्णांक *, स्थिर अक्षर **);

अटल eval_fn eval_table, eval_unary;

/*
 * The precedence table. Expressions involving binary चालकs are evaluated
 * in a table-driven way by eval_table. When it evaluates a subexpression it
 * calls the inner function with its first argument poपूर्णांकing to the next
 * element of the table. Innermost expressions have special non-table-driven
 * handling.
 */
अटल स्थिर काष्ठा ops अणु
	eval_fn *inner;
	काष्ठा op अणु
		स्थिर अक्षर *str;
		Linetype (*fn)(पूर्णांक *, Linetype, पूर्णांक, Linetype, पूर्णांक);
	पूर्ण op[5];
पूर्ण eval_ops[] = अणु
	अणु eval_table, अणु अणु "||", op_or पूर्ण पूर्ण पूर्ण,
	अणु eval_table, अणु अणु "&&", op_and पूर्ण पूर्ण पूर्ण,
	अणु eval_table, अणु अणु "==", op_eq पूर्ण,
			अणु "!=", op_ne पूर्ण पूर्ण पूर्ण,
	अणु eval_unary, अणु अणु "<=", op_le पूर्ण,
			अणु ">=", op_ge पूर्ण,
			अणु "<", op_lt पूर्ण,
			अणु ">", op_gt पूर्ण पूर्ण पूर्ण
पूर्ण;

/*
 * Function क्रम evaluating the innermost parts of expressions,
 * viz. !expr (expr) number defined(symbol) symbol
 * We reset the स्थिरexpr flag in the last two हालs.
 */
अटल Linetype
eval_unary(स्थिर काष्ठा ops *ops, पूर्णांक *valp, स्थिर अक्षर **cpp)
अणु
	स्थिर अक्षर *cp;
	अक्षर *ep;
	पूर्णांक sym;
	bool defparen;
	Linetype lt;

	cp = skipcomment(*cpp);
	अगर (*cp == '!') अणु
		debug("eval%d !", ops - eval_ops);
		cp++;
		lt = eval_unary(ops, valp, &cp);
		अगर (lt == LT_ERROR)
			वापस (LT_ERROR);
		अगर (lt != LT_IF) अणु
			*valp = !*valp;
			lt = *valp ? LT_TRUE : LT_FALSE;
		पूर्ण
	पूर्ण अन्यथा अगर (*cp == '(') अणु
		cp++;
		debug("eval%d (", ops - eval_ops);
		lt = eval_table(eval_ops, valp, &cp);
		अगर (lt == LT_ERROR)
			वापस (LT_ERROR);
		cp = skipcomment(cp);
		अगर (*cp++ != ')')
			वापस (LT_ERROR);
	पूर्ण अन्यथा अगर (है_अंक((अचिन्हित अक्षर)*cp)) अणु
		debug("eval%d number", ops - eval_ops);
		*valp = म_से_दीर्घ(cp, &ep, 0);
		अगर (ep == cp)
			वापस (LT_ERROR);
		lt = *valp ? LT_TRUE : LT_FALSE;
		cp = skipsym(cp);
	पूर्ण अन्यथा अगर (म_भेदन(cp, "defined", 7) == 0 && endsym(cp[7])) अणु
		cp = skipcomment(cp+7);
		debug("eval%d defined", ops - eval_ops);
		अगर (*cp == '(') अणु
			cp = skipcomment(cp+1);
			defparen = true;
		पूर्ण अन्यथा अणु
			defparen = false;
		पूर्ण
		sym = findsym(cp);
		अगर (sym < 0) अणु
			lt = LT_IF;
		पूर्ण अन्यथा अणु
			*valp = (value[sym] != शून्य);
			lt = *valp ? LT_TRUE : LT_FALSE;
		पूर्ण
		cp = skipsym(cp);
		cp = skipcomment(cp);
		अगर (defparen && *cp++ != ')')
			वापस (LT_ERROR);
		स्थिरexpr = false;
	पूर्ण अन्यथा अगर (!endsym(*cp)) अणु
		debug("eval%d symbol", ops - eval_ops);
		sym = findsym(cp);
		cp = skipsym(cp);
		अगर (sym < 0) अणु
			lt = LT_IF;
			cp = skipargs(cp);
		पूर्ण अन्यथा अगर (value[sym] == शून्य) अणु
			*valp = 0;
			lt = LT_FALSE;
		पूर्ण अन्यथा अणु
			*valp = म_से_दीर्घ(value[sym], &ep, 0);
			अगर (*ep != '\0' || ep == value[sym])
				वापस (LT_ERROR);
			lt = *valp ? LT_TRUE : LT_FALSE;
			cp = skipargs(cp);
		पूर्ण
		स्थिरexpr = false;
	पूर्ण अन्यथा अणु
		debug("eval%d bad expr", ops - eval_ops);
		वापस (LT_ERROR);
	पूर्ण

	*cpp = cp;
	debug("eval%d = %d", ops - eval_ops, *valp);
	वापस (lt);
पूर्ण

/*
 * Table-driven evaluation of binary चालकs.
 */
अटल Linetype
eval_table(स्थिर काष्ठा ops *ops, पूर्णांक *valp, स्थिर अक्षर **cpp)
अणु
	स्थिर काष्ठा op *op;
	स्थिर अक्षर *cp;
	पूर्णांक val;
	Linetype lt, rt;

	debug("eval%d", ops - eval_ops);
	cp = *cpp;
	lt = ops->inner(ops+1, valp, &cp);
	अगर (lt == LT_ERROR)
		वापस (LT_ERROR);
	क्रम (;;) अणु
		cp = skipcomment(cp);
		क्रम (op = ops->op; op->str != शून्य; op++)
			अगर (म_भेदन(cp, op->str, म_माप(op->str)) == 0)
				अवरोध;
		अगर (op->str == शून्य)
			अवरोध;
		cp += म_माप(op->str);
		debug("eval%d %s", ops - eval_ops, op->str);
		rt = ops->inner(ops+1, &val, &cp);
		अगर (rt == LT_ERROR)
			वापस (LT_ERROR);
		lt = op->fn(valp, lt, *valp, rt, val);
	पूर्ण

	*cpp = cp;
	debug("eval%d = %d", ops - eval_ops, *valp);
	debug("eval%d lt = %s", ops - eval_ops, linetype_name[lt]);
	वापस (lt);
पूर्ण

/*
 * Evaluate the expression on a #अगर or #या_अगर line. If we can work out
 * the result we वापस LT_TRUE or LT_FALSE accordingly, otherwise we
 * वापस just a generic LT_IF.
 */
अटल Linetype
अगरeval(स्थिर अक्षर **cpp)
अणु
	पूर्णांक ret;
	पूर्णांक val = 0;

	debug("eval %s", *cpp);
	स्थिरexpr = समाप्तस्थिरs ? false : true;
	ret = eval_table(eval_ops, &val, cpp);
	debug("eval = %d", val);
	वापस (स्थिरexpr ? LT_IF : ret == LT_ERROR ? LT_IF : ret);
पूर्ण

/*
 * Skip over comments, strings, and अक्षरacter literals and stop at the
 * next अक्षरacter position that is not whitespace. Between calls we keep
 * the comment state in the global variable incomment, and we also adjust
 * the global variable linestate when we see a newline.
 * XXX: करोesn't cope with the buffer splitting inside a state transition.
 */
अटल स्थिर अक्षर *
skipcomment(स्थिर अक्षर *cp)
अणु
	अगर (text || ignoring[depth]) अणु
		क्रम (; है_खाली((अचिन्हित अक्षर)*cp); cp++)
			अगर (*cp == '\n')
				linestate = LS_START;
		वापस (cp);
	पूर्ण
	जबतक (*cp != '\0')
		/* करोn't reset to LS_START after a line continuation */
		अगर (म_भेदन(cp, "\\\r\n", 3) == 0)
			cp += 3;
		अन्यथा अगर (म_भेदन(cp, "\\\n", 2) == 0)
			cp += 2;
		अन्यथा चयन (incomment) अणु
		हाल NO_COMMENT:
			अगर (म_भेदन(cp, "/\\\r\n", 4) == 0) अणु
				incomment = STARTING_COMMENT;
				cp += 4;
			पूर्ण अन्यथा अगर (म_भेदन(cp, "/\\\n", 3) == 0) अणु
				incomment = STARTING_COMMENT;
				cp += 3;
			पूर्ण अन्यथा अगर (म_भेदन(cp, "/*", 2) == 0) अणु
				incomment = C_COMMENT;
				cp += 2;
			पूर्ण अन्यथा अगर (म_भेदन(cp, "//", 2) == 0) अणु
				incomment = CXX_COMMENT;
				cp += 2;
			पूर्ण अन्यथा अगर (म_भेदन(cp, "\'", 1) == 0) अणु
				incomment = CHAR_LITERAL;
				linestate = LS_सूचीTY;
				cp += 1;
			पूर्ण अन्यथा अगर (म_भेदन(cp, "\"", 1) == 0) अणु
				incomment = STRING_LITERAL;
				linestate = LS_सूचीTY;
				cp += 1;
			पूर्ण अन्यथा अगर (म_भेदन(cp, "\n", 1) == 0) अणु
				linestate = LS_START;
				cp += 1;
			पूर्ण अन्यथा अगर (म_अक्षर(" \r\t", *cp) != शून्य) अणु
				cp += 1;
			पूर्ण अन्यथा
				वापस (cp);
			जारी;
		हाल CXX_COMMENT:
			अगर (म_भेदन(cp, "\n", 1) == 0) अणु
				incomment = NO_COMMENT;
				linestate = LS_START;
			पूर्ण
			cp += 1;
			जारी;
		हाल CHAR_LITERAL:
		हाल STRING_LITERAL:
			अगर ((incomment == CHAR_LITERAL && cp[0] == '\'') ||
			    (incomment == STRING_LITERAL && cp[0] == '\"')) अणु
				incomment = NO_COMMENT;
				cp += 1;
			पूर्ण अन्यथा अगर (cp[0] == '\\') अणु
				अगर (cp[1] == '\0')
					cp += 1;
				अन्यथा
					cp += 2;
			पूर्ण अन्यथा अगर (म_भेदन(cp, "\n", 1) == 0) अणु
				अगर (incomment == CHAR_LITERAL)
					error("unterminated char literal");
				अन्यथा
					error("unterminated string literal");
			पूर्ण अन्यथा
				cp += 1;
			जारी;
		हाल C_COMMENT:
			अगर (म_भेदन(cp, "*\\\r\n", 4) == 0) अणु
				incomment = FINISHING_COMMENT;
				cp += 4;
			पूर्ण अन्यथा अगर (म_भेदन(cp, "*\\\n", 3) == 0) अणु
				incomment = FINISHING_COMMENT;
				cp += 3;
			पूर्ण अन्यथा अगर (म_भेदन(cp, "*/", 2) == 0) अणु
				incomment = NO_COMMENT;
				cp += 2;
			पूर्ण अन्यथा
				cp += 1;
			जारी;
		हाल STARTING_COMMENT:
			अगर (*cp == '*') अणु
				incomment = C_COMMENT;
				cp += 1;
			पूर्ण अन्यथा अगर (*cp == '/') अणु
				incomment = CXX_COMMENT;
				cp += 1;
			पूर्ण अन्यथा अणु
				incomment = NO_COMMENT;
				linestate = LS_सूचीTY;
			पूर्ण
			जारी;
		हाल FINISHING_COMMENT:
			अगर (*cp == '/') अणु
				incomment = NO_COMMENT;
				cp += 1;
			पूर्ण अन्यथा
				incomment = C_COMMENT;
			जारी;
		शेष:
			पात(); /* bug */
		पूर्ण
	वापस (cp);
पूर्ण

/*
 * Skip macro arguments.
 */
अटल स्थिर अक्षर *
skipargs(स्थिर अक्षर *cp)
अणु
	स्थिर अक्षर *ocp = cp;
	पूर्णांक level = 0;
	cp = skipcomment(cp);
	अगर (*cp != '(')
		वापस (cp);
	करो अणु
		अगर (*cp == '(')
			level++;
		अगर (*cp == ')')
			level--;
		cp = skipcomment(cp+1);
	पूर्ण जबतक (level != 0 && *cp != '\0');
	अगर (level == 0)
		वापस (cp);
	अन्यथा
	/* Rewind and re-detect the syntax error later. */
		वापस (ocp);
पूर्ण

/*
 * Skip over an identअगरier.
 */
अटल स्थिर अक्षर *
skipsym(स्थिर अक्षर *cp)
अणु
	जबतक (!endsym(*cp))
		++cp;
	वापस (cp);
पूर्ण

/*
 * Look क्रम the symbol in the symbol table. If it is found, we वापस
 * the symbol table index, अन्यथा we वापस -1.
 */
अटल पूर्णांक
findsym(स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *cp;
	पूर्णांक symind;

	cp = skipsym(str);
	अगर (cp == str)
		वापस (-1);
	अगर (symlist) अणु
		अगर (symdepth && firstsym)
			म_लिखो("%s%3d", zerosyms ? "" : "\n", depth);
		firstsym = zerosyms = false;
		म_लिखो("%s%.*s%s",
		    symdepth ? " " : "",
		    (पूर्णांक)(cp-str), str,
		    symdepth ? "" : "\n");
		/* we करोn't care about the value of the symbol */
		वापस (0);
	पूर्ण
	क्रम (symind = 0; symind < nsyms; ++symind) अणु
		अगर (strlcmp(symname[symind], str, cp-str) == 0) अणु
			debug("findsym %s %s", symname[symind],
			    value[symind] ? value[symind] : "");
			वापस (symind);
		पूर्ण
	पूर्ण
	वापस (-1);
पूर्ण

/*
 * Add a symbol to the symbol table.
 */
अटल व्योम
addsym(bool ignorethis, bool definethis, अक्षर *sym)
अणु
	पूर्णांक symind;
	अक्षर *val;

	symind = findsym(sym);
	अगर (symind < 0) अणु
		अगर (nsyms >= MAXSYMS)
			errx(2, "too many symbols");
		symind = nsyms++;
	पूर्ण
	symname[symind] = sym;
	ignore[symind] = ignorethis;
	val = sym + (skipsym(sym) - sym);
	अगर (definethis) अणु
		अगर (*val == '=') अणु
			value[symind] = val+1;
			*val = '\0';
		पूर्ण अन्यथा अगर (*val == '\0')
			value[symind] = "1";
		अन्यथा
			usage();
	पूर्ण अन्यथा अणु
		अगर (*val != '\0')
			usage();
		value[symind] = शून्य;
	पूर्ण
	debug("addsym %s=%s", symname[symind],
	    value[symind] ? value[symind] : "undef");
पूर्ण

/*
 * Compare s with n अक्षरacters of t.
 * The same as म_भेदन() except that it checks that s[n] == '\0'.
 */
अटल पूर्णांक
strlcmp(स्थिर अक्षर *s, स्थिर अक्षर *t, माप_प्रकार n)
अणु
	जबतक (n-- && *t != '\0')
		अगर (*s != *t)
			वापस ((अचिन्हित अक्षर)*s - (अचिन्हित अक्षर)*t);
		अन्यथा
			++s, ++t;
	वापस ((अचिन्हित अक्षर)*s);
पूर्ण

/*
 * Diagnostics.
 */
अटल व्योम
debug(स्थिर अक्षर *msg, ...)
अणु
	बहु_सूची ap;

	अगर (debugging) अणु
		बहु_शुरू(ap, msg);
		vwarnx(msg, ap);
		बहु_पूर्ण(ap);
	पूर्ण
पूर्ण

अटल व्योम
error(स्थिर अक्षर *msg)
अणु
	अगर (depth == 0)
		warnx("%s: %d: %s", filename, linक्रमागत, msg);
	अन्यथा
		warnx("%s: %d: %s (#if line %d depth %d)",
		    filename, linक्रमागत, msg, stअगरline[depth], depth);
	बंदout();
	errx(2, "output may be truncated");
पूर्ण
