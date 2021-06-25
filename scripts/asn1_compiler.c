<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Simplअगरied ASN.1 notation parser
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/asn1_ber_bytecode.h>

क्रमागत token_type अणु
	सूचीECTIVE_ABSENT,
	सूचीECTIVE_ALL,
	सूचीECTIVE_ANY,
	सूचीECTIVE_APPLICATION,
	सूचीECTIVE_AUTOMATIC,
	सूचीECTIVE_BEGIN,
	सूचीECTIVE_BIT,
	सूचीECTIVE_BMPString,
	सूचीECTIVE_BOOLEAN,
	सूचीECTIVE_BY,
	सूचीECTIVE_CHARACTER,
	सूचीECTIVE_CHOICE,
	सूचीECTIVE_CLASS,
	सूचीECTIVE_COMPONENT,
	सूचीECTIVE_COMPONENTS,
	सूचीECTIVE_CONSTRAINED,
	सूचीECTIVE_CONTAINING,
	सूचीECTIVE_DEFAULT,
	सूचीECTIVE_DEFINED,
	सूचीECTIVE_DEFINITIONS,
	सूचीECTIVE_EMBEDDED,
	सूचीECTIVE_ENCODED,
	सूचीECTIVE_ENCODING_CONTROL,
	सूचीECTIVE_END,
	सूचीECTIVE_ENUMERATED,
	सूचीECTIVE_EXCEPT,
	सूचीECTIVE_EXPLICIT,
	सूचीECTIVE_EXPORTS,
	सूचीECTIVE_EXTENSIBILITY,
	सूचीECTIVE_EXTERNAL,
	सूचीECTIVE_FALSE,
	सूचीECTIVE_FROM,
	सूचीECTIVE_GeneralString,
	सूचीECTIVE_GeneralizedTime,
	सूचीECTIVE_GraphicString,
	सूचीECTIVE_IA5String,
	सूचीECTIVE_IDENTIFIER,
	सूचीECTIVE_IMPLICIT,
	सूचीECTIVE_IMPLIED,
	सूचीECTIVE_IMPORTS,
	सूचीECTIVE_INCLUDES,
	सूचीECTIVE_INSTANCE,
	सूचीECTIVE_INSTRUCTIONS,
	सूचीECTIVE_INTEGER,
	सूचीECTIVE_INTERSECTION,
	सूचीECTIVE_ISO646String,
	सूचीECTIVE_MAX,
	सूचीECTIVE_MIN,
	सूचीECTIVE_MINUS_अनन्त,
	सूचीECTIVE_शून्य,
	सूचीECTIVE_NumericString,
	सूचीECTIVE_OBJECT,
	सूचीECTIVE_OCTET,
	सूचीECTIVE_OF,
	सूचीECTIVE_OPTIONAL,
	सूचीECTIVE_ObjectDescriptor,
	सूचीECTIVE_PATTERN,
	सूचीECTIVE_PDV,
	सूचीECTIVE_PLUS_अनन्त,
	सूचीECTIVE_PRESENT,
	सूचीECTIVE_PRIVATE,
	सूचीECTIVE_Prपूर्णांकableString,
	सूचीECTIVE_REAL,
	सूचीECTIVE_RELATIVE_OID,
	सूचीECTIVE_SEQUENCE,
	सूचीECTIVE_SET,
	सूचीECTIVE_SIZE,
	सूचीECTIVE_STRING,
	सूचीECTIVE_SYNTAX,
	सूचीECTIVE_T61String,
	सूचीECTIVE_TAGS,
	सूचीECTIVE_TRUE,
	सूचीECTIVE_TeletexString,
	सूचीECTIVE_UNION,
	सूचीECTIVE_UNIQUE,
	सूचीECTIVE_UNIVERSAL,
	सूचीECTIVE_UTCTime,
	सूचीECTIVE_UTF8String,
	सूचीECTIVE_UniversalString,
	सूचीECTIVE_VideotexString,
	सूचीECTIVE_VisibleString,
	सूचीECTIVE_WITH,
	NR__सूचीECTIVES,
	TOKEN_ASSIGNMENT = NR__सूचीECTIVES,
	TOKEN_OPEN_CURLY,
	TOKEN_CLOSE_CURLY,
	TOKEN_OPEN_SQUARE,
	TOKEN_CLOSE_SQUARE,
	TOKEN_OPEN_ACTION,
	TOKEN_CLOSE_ACTION,
	TOKEN_COMMA,
	TOKEN_NUMBER,
	TOKEN_TYPE_NAME,
	TOKEN_ELEMENT_NAME,
	NR__TOKENS
पूर्ण;

अटल स्थिर अचिन्हित अक्षर token_to_tag[NR__TOKENS] = अणु
	/* EOC goes first */
	[सूचीECTIVE_BOOLEAN]		= ASN1_BOOL,
	[सूचीECTIVE_INTEGER]		= ASN1_INT,
	[सूचीECTIVE_BIT]			= ASN1_BTS,
	[सूचीECTIVE_OCTET]		= ASN1_OTS,
	[सूचीECTIVE_शून्य]		= ASN1_शून्य,
	[सूचीECTIVE_OBJECT]		= ASN1_OID,
	[सूचीECTIVE_ObjectDescriptor]	= ASN1_ODE,
	[सूचीECTIVE_EXTERNAL]		= ASN1_EXT,
	[सूचीECTIVE_REAL]		= ASN1_REAL,
	[सूचीECTIVE_ENUMERATED]		= ASN1_ENUM,
	[सूचीECTIVE_EMBEDDED]		= 0,
	[सूचीECTIVE_UTF8String]		= ASN1_UTF8STR,
	[सूचीECTIVE_RELATIVE_OID]	= ASN1_RELOID,
	/* 14 */
	/* 15 */
	[सूचीECTIVE_SEQUENCE]		= ASN1_SEQ,
	[सूचीECTIVE_SET]			= ASN1_SET,
	[सूचीECTIVE_NumericString]	= ASN1_NUMSTR,
	[सूचीECTIVE_Prपूर्णांकableString]	= ASN1_PRNSTR,
	[सूचीECTIVE_T61String]		= ASN1_TEXSTR,
	[सूचीECTIVE_TeletexString]	= ASN1_TEXSTR,
	[सूचीECTIVE_VideotexString]	= ASN1_VIDSTR,
	[सूचीECTIVE_IA5String]		= ASN1_IA5STR,
	[सूचीECTIVE_UTCTime]		= ASN1_UNITIM,
	[सूचीECTIVE_GeneralizedTime]	= ASN1_GENTIM,
	[सूचीECTIVE_GraphicString]	= ASN1_GRASTR,
	[सूचीECTIVE_VisibleString]	= ASN1_VISSTR,
	[सूचीECTIVE_GeneralString]	= ASN1_GENSTR,
	[सूचीECTIVE_UniversalString]	= ASN1_UNITIM,
	[सूचीECTIVE_CHARACTER]		= ASN1_CHRSTR,
	[सूचीECTIVE_BMPString]		= ASN1_BMPSTR,
पूर्ण;

अटल स्थिर अक्षर asn1_classes[4][5] = अणु
	[ASN1_UNIV]	= "UNIV",
	[ASN1_APPL]	= "APPL",
	[ASN1_CONT]	= "CONT",
	[ASN1_PRIV]	= "PRIV"
पूर्ण;

अटल स्थिर अक्षर asn1_methods[2][5] = अणु
	[ASN1_UNIV]	= "PRIM",
	[ASN1_APPL]	= "CONS"
पूर्ण;

अटल स्थिर अक्षर *स्थिर asn1_universal_tags[32] = अणु
	"EOC",
	"BOOL",
	"INT",
	"BTS",
	"OTS",
	"NULL",
	"OID",
	"ODE",
	"EXT",
	"REAL",
	"ENUM",
	"EPDV",
	"UTF8STR",
	"RELOID",
	शून्य,		/* 14 */
	शून्य,		/* 15 */
	"SEQ",
	"SET",
	"NUMSTR",
	"PRNSTR",
	"TEXSTR",
	"VIDSTR",
	"IA5STR",
	"UNITIM",
	"GENTIM",
	"GRASTR",
	"VISSTR",
	"GENSTR",
	"UNISTR",
	"CHRSTR",
	"BMPSTR",
	शून्य		/* 31 */
पूर्ण;

अटल स्थिर अक्षर *filename;
अटल स्थिर अक्षर *grammar_name;
अटल स्थिर अक्षर *outputname;
अटल स्थिर अक्षर *headername;

अटल स्थिर अक्षर *स्थिर directives[NR__सूचीECTIVES] = अणु
#घोषणा _(X) [सूचीECTIVE_##X] = #X
	_(ABSENT),
	_(ALL),
	_(ANY),
	_(APPLICATION),
	_(AUTOMATIC),
	_(BEGIN),
	_(BIT),
	_(BMPString),
	_(BOOLEAN),
	_(BY),
	_(CHARACTER),
	_(CHOICE),
	_(CLASS),
	_(COMPONENT),
	_(COMPONENTS),
	_(CONSTRAINED),
	_(CONTAINING),
	_(DEFAULT),
	_(DEFINED),
	_(DEFINITIONS),
	_(EMBEDDED),
	_(ENCODED),
	[सूचीECTIVE_ENCODING_CONTROL] = "ENCODING-CONTROL",
	_(END),
	_(ENUMERATED),
	_(EXCEPT),
	_(EXPLICIT),
	_(EXPORTS),
	_(EXTENSIBILITY),
	_(EXTERNAL),
	_(FALSE),
	_(FROM),
	_(GeneralString),
	_(GeneralizedTime),
	_(GraphicString),
	_(IA5String),
	_(IDENTIFIER),
	_(IMPLICIT),
	_(IMPLIED),
	_(IMPORTS),
	_(INCLUDES),
	_(INSTANCE),
	_(INSTRUCTIONS),
	_(INTEGER),
	_(INTERSECTION),
	_(ISO646String),
	_(MAX),
	_(MIN),
	[सूचीECTIVE_MINUS_अनन्त] = "MINUS-INFINITY",
	[सूचीECTIVE_शून्य] = "NULL",
	_(NumericString),
	_(OBJECT),
	_(OCTET),
	_(OF),
	_(OPTIONAL),
	_(ObjectDescriptor),
	_(PATTERN),
	_(PDV),
	[सूचीECTIVE_PLUS_अनन्त] = "PLUS-INFINITY",
	_(PRESENT),
	_(PRIVATE),
	_(Prपूर्णांकableString),
	_(REAL),
	[सूचीECTIVE_RELATIVE_OID] = "RELATIVE-OID",
	_(SEQUENCE),
	_(SET),
	_(SIZE),
	_(STRING),
	_(SYNTAX),
	_(T61String),
	_(TAGS),
	_(TRUE),
	_(TeletexString),
	_(UNION),
	_(UNIQUE),
	_(UNIVERSAL),
	_(UTCTime),
	_(UTF8String),
	_(UniversalString),
	_(VideotexString),
	_(VisibleString),
	_(WITH)
पूर्ण;

काष्ठा action अणु
	काष्ठा action	*next;
	अक्षर		*name;
	अचिन्हित अक्षर	index;
पूर्ण;

अटल काष्ठा action *action_list;
अटल अचिन्हित nr_actions;

काष्ठा token अणु
	अचिन्हित लघु	line;
	क्रमागत token_type	token_type : 8;
	अचिन्हित अक्षर	size;
	काष्ठा action	*action;
	अक्षर		*content;
	काष्ठा type	*type;
पूर्ण;

अटल काष्ठा token *token_list;
अटल अचिन्हित nr_tokens;
अटल bool verbose_opt;
अटल bool debug_opt;

#घोषणा verbose(fmt, ...) करो अणु अगर (verbose_opt) म_लिखो(fmt, ## __VA_ARGS__); पूर्ण जबतक (0)
#घोषणा debug(fmt, ...) करो अणु अगर (debug_opt) म_लिखो(fmt, ## __VA_ARGS__); पूर्ण जबतक (0)

अटल पूर्णांक directive_compare(स्थिर व्योम *_key, स्थिर व्योम *_pdir)
अणु
	स्थिर काष्ठा token *token = _key;
	स्थिर अक्षर *स्थिर *pdir = _pdir, *dir = *pdir;
	माप_प्रकार dlen, clen;
	पूर्णांक val;

	dlen = म_माप(dir);
	clen = (dlen < token->size) ? dlen : token->size;

	//debug("cmp(%s,%s) = ", token->content, dir);

	val = स_भेद(token->content, dir, clen);
	अगर (val != 0) अणु
		//debug("%d [cmp]\n", val);
		वापस val;
	पूर्ण

	अगर (dlen == token->size) अणु
		//debug("0\n");
		वापस 0;
	पूर्ण
	//debug("%d\n", (पूर्णांक)dlen - (पूर्णांक)token->size);
	वापस dlen - token->size; /* लघुer -> negative */
पूर्ण

/*
 * Tokenise an ASN.1 grammar
 */
अटल व्योम tokenise(अक्षर *buffer, अक्षर *end)
अणु
	काष्ठा token *tokens;
	अक्षर *line, *nl, *start, *p, *q;
	अचिन्हित tix, lineno;

	/* Assume we're going to have half as many tokens as we have
	 * अक्षरacters
	 */
	token_list = tokens = सुस्मृति((end - buffer) / 2, माप(काष्ठा token));
	अगर (!tokens) अणु
		लिखो_त्रुटि(शून्य);
		निकास(1);
	पूर्ण
	tix = 0;

	lineno = 0;
	जबतक (buffer < end) अणु
		/* First of all, अवरोध out a line */
		lineno++;
		line = buffer;
		nl = स_प्रथम(line, '\n', end - buffer);
		अगर (!nl) अणु
			buffer = nl = end;
		पूर्ण अन्यथा अणु
			buffer = nl + 1;
			*nl = '\0';
		पूर्ण

		/* Remove "--" comments */
		p = line;
	next_comment:
		जबतक ((p = स_प्रथम(p, '-', nl - p))) अणु
			अगर (p[1] == '-') अणु
				/* Found a comment; see अगर there's a terminator */
				q = p + 2;
				जबतक ((q = स_प्रथम(q, '-', nl - q))) अणु
					अगर (q[1] == '-') अणु
						/* There is - excise the comment */
						q += 2;
						स_हटाओ(p, q, nl - q);
						जाओ next_comment;
					पूर्ण
					q++;
				पूर्ण
				*p = '\0';
				nl = p;
				अवरोध;
			पूर्ण अन्यथा अणु
				p++;
			पूर्ण
		पूर्ण

		p = line;
		जबतक (p < nl) अणु
			/* Skip white space */
			जबतक (p < nl && है_खाली(*p))
				*(p++) = 0;
			अगर (p >= nl)
				अवरोध;

			tokens[tix].line = lineno;
			start = p;

			/* Handle string tokens */
			अगर (है_अक्षर(*p)) अणु
				स्थिर अक्षर **dir;

				/* Can be a directive, type name or element
				 * name.  Find the end of the name.
				 */
				q = p + 1;
				जबतक (q < nl && (है_अक्षर_अंक(*q) || *q == '-' || *q == '_'))
					q++;
				tokens[tix].size = q - p;
				p = q;

				tokens[tix].content = दो_स्मृति(tokens[tix].size + 1);
				अगर (!tokens[tix].content) अणु
					लिखो_त्रुटि(शून्य);
					निकास(1);
				पूर्ण
				स_नकल(tokens[tix].content, start, tokens[tix].size);
				tokens[tix].content[tokens[tix].size] = 0;
				
				/* If it begins with a lowerहाल letter then
				 * it's an element name
				 */
				अगर (है_छोटा(tokens[tix].content[0])) अणु
					tokens[tix++].token_type = TOKEN_ELEMENT_NAME;
					जारी;
				पूर्ण

				/* Otherwise we need to search the directive
				 * table
				 */
				dir = द्वा_खोज(&tokens[tix], directives,
					      माप(directives) / माप(directives[1]),
					      माप(directives[1]),
					      directive_compare);
				अगर (dir) अणु
					tokens[tix++].token_type = dir - directives;
					जारी;
				पूर्ण

				tokens[tix++].token_type = TOKEN_TYPE_NAME;
				जारी;
			पूर्ण

			/* Handle numbers */
			अगर (है_अंक(*p)) अणु
				/* Find the end of the number */
				q = p + 1;
				जबतक (q < nl && (है_अंक(*q)))
					q++;
				tokens[tix].size = q - p;
				p = q;
				tokens[tix].content = दो_स्मृति(tokens[tix].size + 1);
				अगर (!tokens[tix].content) अणु
					लिखो_त्रुटि(शून्य);
					निकास(1);
				पूर्ण
				स_नकल(tokens[tix].content, start, tokens[tix].size);
				tokens[tix].content[tokens[tix].size] = 0;
				tokens[tix++].token_type = TOKEN_NUMBER;
				जारी;
			पूर्ण

			अगर (nl - p >= 3) अणु
				अगर (स_भेद(p, "::=", 3) == 0) अणु
					p += 3;
					tokens[tix].size = 3;
					tokens[tix].content = "::=";
					tokens[tix++].token_type = TOKEN_ASSIGNMENT;
					जारी;
				पूर्ण
			पूर्ण

			अगर (nl - p >= 2) अणु
				अगर (स_भेद(p, "({", 2) == 0) अणु
					p += 2;
					tokens[tix].size = 2;
					tokens[tix].content = "({";
					tokens[tix++].token_type = TOKEN_OPEN_ACTION;
					जारी;
				पूर्ण
				अगर (स_भेद(p, "})", 2) == 0) अणु
					p += 2;
					tokens[tix].size = 2;
					tokens[tix].content = "})";
					tokens[tix++].token_type = TOKEN_CLOSE_ACTION;
					जारी;
				पूर्ण
			पूर्ण

			अगर (nl - p >= 1) अणु
				tokens[tix].size = 1;
				चयन (*p) अणु
				हाल '{':
					p += 1;
					tokens[tix].content = "{";
					tokens[tix++].token_type = TOKEN_OPEN_CURLY;
					जारी;
				हाल '}':
					p += 1;
					tokens[tix].content = "}";
					tokens[tix++].token_type = TOKEN_CLOSE_CURLY;
					जारी;
				हाल '[':
					p += 1;
					tokens[tix].content = "[";
					tokens[tix++].token_type = TOKEN_OPEN_SQUARE;
					जारी;
				हाल ']':
					p += 1;
					tokens[tix].content = "]";
					tokens[tix++].token_type = TOKEN_CLOSE_SQUARE;
					जारी;
				हाल ',':
					p += 1;
					tokens[tix].content = ",";
					tokens[tix++].token_type = TOKEN_COMMA;
					जारी;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण

			ख_लिखो(मानक_त्रुटि, "%s:%u: Unknown character in grammar: '%c'\n",
				filename, lineno, *p);
			निकास(1);
		पूर्ण
	पूर्ण

	nr_tokens = tix;
	verbose("Extracted %u tokens\n", nr_tokens);

#अगर 0
	अणु
		पूर्णांक n;
		क्रम (n = 0; n < nr_tokens; n++)
			debug("Token %3u: '%s'\n", n, token_list[n].content);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम build_type_list(व्योम);
अटल व्योम parse(व्योम);
अटल व्योम dump_elements(व्योम);
अटल व्योम render(खाता *out, खाता *hdr);

/*
 *
 */
पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा stat st;
	sमाप_प्रकार पढ़ोlen;
	खाता *out, *hdr;
	अक्षर *buffer, *p;
	अक्षर *kbuild_verbose;
	पूर्णांक fd;

	kbuild_verbose = दो_पर्या("KBUILD_VERBOSE");
	अगर (kbuild_verbose)
		verbose_opt = म_से_प(kbuild_verbose);

	जबतक (argc > 4) अणु
		अगर (म_भेद(argv[1], "-v") == 0)
			verbose_opt = true;
		अन्यथा अगर (म_भेद(argv[1], "-d") == 0)
			debug_opt = true;
		अन्यथा
			अवरोध;
		स_हटाओ(&argv[1], &argv[2], (argc - 2) * माप(अक्षर *));
		argc--;
	पूर्ण

	अगर (argc != 4) अणु
		ख_लिखो(मानक_त्रुटि, "Format: %s [-v] [-d] <grammar-file> <c-file> <hdr-file>\n",
			argv[0]);
		निकास(2);
	पूर्ण

	filename = argv[1];
	outputname = argv[2];
	headername = argv[3];

	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0) अणु
		लिखो_त्रुटि(filename);
		निकास(1);
	पूर्ण

	अगर (ख_स्थिति(fd, &st) < 0) अणु
		लिखो_त्रुटि(filename);
		निकास(1);
	पूर्ण

	अगर (!(buffer = दो_स्मृति(st.st_size + 1))) अणु
		लिखो_त्रुटि(शून्य);
		निकास(1);
	पूर्ण

	अगर ((पढ़ोlen = पढ़ो(fd, buffer, st.st_size)) < 0) अणु
		लिखो_त्रुटि(filename);
		निकास(1);
	पूर्ण

	अगर (बंद(fd) < 0) अणु
		लिखो_त्रुटि(filename);
		निकास(1);
	पूर्ण

	अगर (पढ़ोlen != st.st_size) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Short read\n", filename);
		निकास(1);
	पूर्ण

	p = म_खोजप(argv[1], '/');
	p = p ? p + 1 : argv[1];
	grammar_name = strdup(p);
	अगर (!p) अणु
		लिखो_त्रुटि(शून्य);
		निकास(1);
	पूर्ण
	p = म_अक्षर(grammar_name, '.');
	अगर (p)
		*p = '\0';

	buffer[पढ़ोlen] = 0;
	tokenise(buffer, buffer + पढ़ोlen);
	build_type_list();
	parse();
	dump_elements();

	out = ख_खोलो(outputname, "w");
	अगर (!out) अणु
		लिखो_त्रुटि(outputname);
		निकास(1);
	पूर्ण

	hdr = ख_खोलो(headername, "w");
	अगर (!hdr) अणु
		लिखो_त्रुटि(headername);
		निकास(1);
	पूर्ण

	render(out, hdr);

	अगर (ख_बंद(out) < 0) अणु
		लिखो_त्रुटि(outputname);
		निकास(1);
	पूर्ण

	अगर (ख_बंद(hdr) < 0) अणु
		लिखो_त्रुटि(headername);
		निकास(1);
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत compound अणु
	NOT_COMPOUND,
	SET,
	SET_OF,
	SEQUENCE,
	SEQUENCE_OF,
	CHOICE,
	ANY,
	TYPE_REF,
	TAG_OVERRIDE
पूर्ण;

काष्ठा element अणु
	काष्ठा type	*type_def;
	काष्ठा token	*name;
	काष्ठा token	*type;
	काष्ठा action	*action;
	काष्ठा element	*children;
	काष्ठा element	*next;
	काष्ठा element	*render_next;
	काष्ठा element	*list_next;
	uपूर्णांक8_t		n_elements;
	क्रमागत compound	compound : 8;
	क्रमागत asn1_class	class : 8;
	क्रमागत asn1_method method : 8;
	uपूर्णांक8_t		tag;
	अचिन्हित	entry_index;
	अचिन्हित	flags;
#घोषणा ELEMENT_IMPLICIT	0x0001
#घोषणा ELEMENT_EXPLICIT	0x0002
#घोषणा ELEMENT_TAG_SPECIFIED	0x0004
#घोषणा ELEMENT_RENDERED	0x0008
#घोषणा ELEMENT_SKIPPABLE	0x0010
#घोषणा ELEMENT_CONDITIONAL	0x0020
पूर्ण;

काष्ठा type अणु
	काष्ठा token	*name;
	काष्ठा token	*def;
	काष्ठा element	*element;
	अचिन्हित	ref_count;
	अचिन्हित	flags;
#घोषणा TYPE_STOP_MARKER	0x0001
#घोषणा TYPE_BEGIN		0x0002
पूर्ण;

अटल काष्ठा type *type_list;
अटल काष्ठा type **type_index;
अटल अचिन्हित nr_types;

अटल पूर्णांक type_index_compare(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर काष्ठा type *स्थिर *a = _a, *स्थिर *b = _b;

	अगर ((*a)->name->size != (*b)->name->size)
		वापस (*a)->name->size - (*b)->name->size;
	अन्यथा
		वापस स_भेद((*a)->name->content, (*b)->name->content,
			      (*a)->name->size);
पूर्ण

अटल पूर्णांक type_finder(स्थिर व्योम *_key, स्थिर व्योम *_ti)
अणु
	स्थिर काष्ठा token *token = _key;
	स्थिर काष्ठा type *स्थिर *ti = _ti;
	स्थिर काष्ठा type *type = *ti;

	अगर (token->size != type->name->size)
		वापस token->size - type->name->size;
	अन्यथा
		वापस स_भेद(token->content, type->name->content,
			      token->size);
पूर्ण

/*
 * Build up a list of types and a sorted index to that list.
 */
अटल व्योम build_type_list(व्योम)
अणु
	काष्ठा type *types;
	अचिन्हित nr, t, n;

	nr = 0;
	क्रम (n = 0; n < nr_tokens - 1; n++)
		अगर (token_list[n + 0].token_type == TOKEN_TYPE_NAME &&
		    token_list[n + 1].token_type == TOKEN_ASSIGNMENT)
			nr++;

	अगर (nr == 0) अणु
		ख_लिखो(मानक_त्रुटि, "%s: No defined types\n", filename);
		निकास(1);
	पूर्ण

	nr_types = nr;
	types = type_list = सुस्मृति(nr + 1, माप(type_list[0]));
	अगर (!type_list) अणु
		लिखो_त्रुटि(शून्य);
		निकास(1);
	पूर्ण
	type_index = सुस्मृति(nr, माप(type_index[0]));
	अगर (!type_index) अणु
		लिखो_त्रुटि(शून्य);
		निकास(1);
	पूर्ण

	t = 0;
	types[t].flags |= TYPE_BEGIN;
	क्रम (n = 0; n < nr_tokens - 1; n++) अणु
		अगर (token_list[n + 0].token_type == TOKEN_TYPE_NAME &&
		    token_list[n + 1].token_type == TOKEN_ASSIGNMENT) अणु
			types[t].name = &token_list[n];
			type_index[t] = &types[t];
			t++;
		पूर्ण
	पूर्ण
	types[t].name = &token_list[n + 1];
	types[t].flags |= TYPE_STOP_MARKER;

	क्विक(type_index, nr, माप(type_index[0]), type_index_compare);

	verbose("Extracted %u types\n", nr_types);
#अगर 0
	क्रम (n = 0; n < nr_types; n++) अणु
		काष्ठा type *type = type_index[n];
		debug("- %*.*s\n", type->name->content);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल काष्ठा element *parse_type(काष्ठा token **_cursor, काष्ठा token *stop,
				  काष्ठा token *name);

/*
 * Parse the token stream
 */
अटल व्योम parse(व्योम)
अणु
	काष्ठा token *cursor;
	काष्ठा type *type;

	/* Parse one type definition statement at a समय */
	type = type_list;
	करो अणु
		cursor = type->name;

		अगर (cursor[0].token_type != TOKEN_TYPE_NAME ||
		    cursor[1].token_type != TOKEN_ASSIGNMENT)
			पात();
		cursor += 2;

		type->element = parse_type(&cursor, type[1].name, शून्य);
		type->element->type_def = type;

		अगर (cursor != type[1].name) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d: Parse error at token '%s'\n",
				filename, cursor->line, cursor->content);
			निकास(1);
		पूर्ण

	पूर्ण जबतक (type++, !(type->flags & TYPE_STOP_MARKER));

	verbose("Extracted %u actions\n", nr_actions);
पूर्ण

अटल काष्ठा element *element_list;

अटल काष्ठा element *alloc_elem(काष्ठा token *type)
अणु
	काष्ठा element *e = सुस्मृति(1, माप(*e));
	अगर (!e) अणु
		लिखो_त्रुटि(शून्य);
		निकास(1);
	पूर्ण
	e->list_next = element_list;
	element_list = e;
	वापस e;
पूर्ण

अटल काष्ठा element *parse_compound(काष्ठा token **_cursor, काष्ठा token *end,
				      पूर्णांक alternates);

/*
 * Parse one type definition statement
 */
अटल काष्ठा element *parse_type(काष्ठा token **_cursor, काष्ठा token *end,
				  काष्ठा token *name)
अणु
	काष्ठा element *top, *element;
	काष्ठा action *action, **ppaction;
	काष्ठा token *cursor = *_cursor;
	काष्ठा type **ref;
	अक्षर *p;
	पूर्णांक labelled = 0, implicit = 0;

	top = element = alloc_elem(cursor);
	element->class = ASN1_UNIV;
	element->method = ASN1_PRIM;
	element->tag = token_to_tag[cursor->token_type];
	element->name = name;

	/* Extract the tag value अगर one given */
	अगर (cursor->token_type == TOKEN_OPEN_SQUARE) अणु
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
		चयन (cursor->token_type) अणु
		हाल सूचीECTIVE_UNIVERSAL:
			element->class = ASN1_UNIV;
			cursor++;
			अवरोध;
		हाल सूचीECTIVE_APPLICATION:
			element->class = ASN1_APPL;
			cursor++;
			अवरोध;
		हाल TOKEN_NUMBER:
			element->class = ASN1_CONT;
			अवरोध;
		हाल सूचीECTIVE_PRIVATE:
			element->class = ASN1_PRIV;
			cursor++;
			अवरोध;
		शेष:
			ख_लिखो(मानक_त्रुटि, "%s:%d: Unrecognised tag class token '%s'\n",
				filename, cursor->line, cursor->content);
			निकास(1);
		पूर्ण

		अगर (cursor >= end)
			जाओ overrun_error;
		अगर (cursor->token_type != TOKEN_NUMBER) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d: Missing tag number '%s'\n",
				filename, cursor->line, cursor->content);
			निकास(1);
		पूर्ण

		element->tag &= ~0x1f;
		element->tag |= म_से_अदीर्घ(cursor->content, &p, 10);
		element->flags |= ELEMENT_TAG_SPECIFIED;
		अगर (p - cursor->content != cursor->size)
			पात();
		cursor++;

		अगर (cursor >= end)
			जाओ overrun_error;
		अगर (cursor->token_type != TOKEN_CLOSE_SQUARE) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d: Missing closing square bracket '%s'\n",
				filename, cursor->line, cursor->content);
			निकास(1);
		पूर्ण
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
		labelled = 1;
	पूर्ण

	/* Handle implicit and explicit markers */
	अगर (cursor->token_type == सूचीECTIVE_IMPLICIT) अणु
		element->flags |= ELEMENT_IMPLICIT;
		implicit = 1;
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
	पूर्ण अन्यथा अगर (cursor->token_type == सूचीECTIVE_EXPLICIT) अणु
		element->flags |= ELEMENT_EXPLICIT;
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
	पूर्ण

	अगर (labelled) अणु
		अगर (!implicit)
			element->method |= ASN1_CONS;
		element->compound = implicit ? TAG_OVERRIDE : SEQUENCE;
		element->children = alloc_elem(cursor);
		element = element->children;
		element->class = ASN1_UNIV;
		element->method = ASN1_PRIM;
		element->tag = token_to_tag[cursor->token_type];
		element->name = name;
	पूर्ण

	/* Extract the type we're expecting here */
	element->type = cursor;
	चयन (cursor->token_type) अणु
	हाल सूचीECTIVE_ANY:
		element->compound = ANY;
		cursor++;
		अवरोध;

	हाल सूचीECTIVE_शून्य:
	हाल सूचीECTIVE_BOOLEAN:
	हाल सूचीECTIVE_ENUMERATED:
	हाल सूचीECTIVE_INTEGER:
		element->compound = NOT_COMPOUND;
		cursor++;
		अवरोध;

	हाल सूचीECTIVE_EXTERNAL:
		element->method = ASN1_CONS;

	हाल सूचीECTIVE_BMPString:
	हाल सूचीECTIVE_GeneralString:
	हाल सूचीECTIVE_GraphicString:
	हाल सूचीECTIVE_IA5String:
	हाल सूचीECTIVE_ISO646String:
	हाल सूचीECTIVE_NumericString:
	हाल सूचीECTIVE_Prपूर्णांकableString:
	हाल सूचीECTIVE_T61String:
	हाल सूचीECTIVE_TeletexString:
	हाल सूचीECTIVE_UniversalString:
	हाल सूचीECTIVE_UTF8String:
	हाल सूचीECTIVE_VideotexString:
	हाल सूचीECTIVE_VisibleString:
	हाल सूचीECTIVE_ObjectDescriptor:
	हाल सूचीECTIVE_GeneralizedTime:
	हाल सूचीECTIVE_UTCTime:
		element->compound = NOT_COMPOUND;
		cursor++;
		अवरोध;

	हाल सूचीECTIVE_BIT:
	हाल सूचीECTIVE_OCTET:
		element->compound = NOT_COMPOUND;
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
		अगर (cursor->token_type != सूचीECTIVE_STRING)
			जाओ parse_error;
		cursor++;
		अवरोध;

	हाल सूचीECTIVE_OBJECT:
		element->compound = NOT_COMPOUND;
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
		अगर (cursor->token_type != सूचीECTIVE_IDENTIFIER)
			जाओ parse_error;
		cursor++;
		अवरोध;

	हाल TOKEN_TYPE_NAME:
		element->compound = TYPE_REF;
		ref = द्वा_खोज(cursor, type_index, nr_types, माप(type_index[0]),
			      type_finder);
		अगर (!ref) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d: Type '%s' undefined\n",
				filename, cursor->line, cursor->content);
			निकास(1);
		पूर्ण
		cursor->type = *ref;
		(*ref)->ref_count++;
		cursor++;
		अवरोध;

	हाल सूचीECTIVE_CHOICE:
		element->compound = CHOICE;
		cursor++;
		element->children = parse_compound(&cursor, end, 1);
		अवरोध;

	हाल सूचीECTIVE_SEQUENCE:
		element->compound = SEQUENCE;
		element->method = ASN1_CONS;
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
		अगर (cursor->token_type == सूचीECTIVE_OF) अणु
			element->compound = SEQUENCE_OF;
			cursor++;
			अगर (cursor >= end)
				जाओ overrun_error;
			element->children = parse_type(&cursor, end, शून्य);
		पूर्ण अन्यथा अणु
			element->children = parse_compound(&cursor, end, 0);
		पूर्ण
		अवरोध;

	हाल सूचीECTIVE_SET:
		element->compound = SET;
		element->method = ASN1_CONS;
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
		अगर (cursor->token_type == सूचीECTIVE_OF) अणु
			element->compound = SET_OF;
			cursor++;
			अगर (cursor >= end)
				जाओ parse_error;
			element->children = parse_type(&cursor, end, शून्य);
		पूर्ण अन्यथा अणु
			element->children = parse_compound(&cursor, end, 1);
		पूर्ण
		अवरोध;

	शेष:
		ख_लिखो(मानक_त्रुटि, "%s:%d: Token '%s' does not introduce a type\n",
			filename, cursor->line, cursor->content);
		निकास(1);
	पूर्ण

	/* Handle elements that are optional */
	अगर (cursor < end && (cursor->token_type == सूचीECTIVE_OPTIONAL ||
			     cursor->token_type == सूचीECTIVE_DEFAULT)
	    ) अणु
		cursor++;
		top->flags |= ELEMENT_SKIPPABLE;
	पूर्ण

	अगर (cursor < end && cursor->token_type == TOKEN_OPEN_ACTION) अणु
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
		अगर (cursor->token_type != TOKEN_ELEMENT_NAME) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d: Token '%s' is not an action function name\n",
				filename, cursor->line, cursor->content);
			निकास(1);
		पूर्ण

		action = दो_स्मृति(माप(काष्ठा action));
		अगर (!action) अणु
			लिखो_त्रुटि(शून्य);
			निकास(1);
		पूर्ण
		action->index = 0;
		action->name = cursor->content;

		क्रम (ppaction = &action_list;
		     *ppaction;
		     ppaction = &(*ppaction)->next
		     ) अणु
			पूर्णांक cmp = म_भेद(action->name, (*ppaction)->name);
			अगर (cmp == 0) अणु
				मुक्त(action);
				action = *ppaction;
				जाओ found;
			पूर्ण
			अगर (cmp < 0) अणु
				action->next = *ppaction;
				*ppaction = action;
				nr_actions++;
				जाओ found;
			पूर्ण
		पूर्ण
		action->next = शून्य;
		*ppaction = action;
		nr_actions++;
	found:

		element->action = action;
		cursor->action = action;
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
		अगर (cursor->token_type != TOKEN_CLOSE_ACTION) अणु
			ख_लिखो(मानक_त्रुटि, "%s:%d: Missing close action, got '%s'\n",
				filename, cursor->line, cursor->content);
			निकास(1);
		पूर्ण
		cursor++;
	पूर्ण

	*_cursor = cursor;
	वापस top;

parse_error:
	ख_लिखो(मानक_त्रुटि, "%s:%d: Unexpected token '%s'\n",
		filename, cursor->line, cursor->content);
	निकास(1);

overrun_error:
	ख_लिखो(मानक_त्रुटि, "%s: Unexpectedly hit EOF\n", filename);
	निकास(1);
पूर्ण

/*
 * Parse a compound type list
 */
अटल काष्ठा element *parse_compound(काष्ठा token **_cursor, काष्ठा token *end,
				      पूर्णांक alternates)
अणु
	काष्ठा element *children, **child_p = &children, *element;
	काष्ठा token *cursor = *_cursor, *name;

	अगर (cursor->token_type != TOKEN_OPEN_CURLY) अणु
		ख_लिखो(मानक_त्रुटि, "%s:%d: Expected compound to start with brace not '%s'\n",
			filename, cursor->line, cursor->content);
		निकास(1);
	पूर्ण
	cursor++;
	अगर (cursor >= end)
		जाओ overrun_error;

	अगर (cursor->token_type == TOKEN_OPEN_CURLY) अणु
		ख_लिखो(मानक_त्रुटि, "%s:%d: Empty compound\n",
			filename, cursor->line);
		निकास(1);
	पूर्ण

	क्रम (;;) अणु
		name = शून्य;
		अगर (cursor->token_type == TOKEN_ELEMENT_NAME) अणु
			name = cursor;
			cursor++;
			अगर (cursor >= end)
				जाओ overrun_error;
		पूर्ण

		element = parse_type(&cursor, end, name);
		अगर (alternates)
			element->flags |= ELEMENT_SKIPPABLE | ELEMENT_CONDITIONAL;

		*child_p = element;
		child_p = &element->next;

		अगर (cursor >= end)
			जाओ overrun_error;
		अगर (cursor->token_type != TOKEN_COMMA)
			अवरोध;
		cursor++;
		अगर (cursor >= end)
			जाओ overrun_error;
	पूर्ण

	children->flags &= ~ELEMENT_CONDITIONAL;

	अगर (cursor->token_type != TOKEN_CLOSE_CURLY) अणु
		ख_लिखो(मानक_त्रुटि, "%s:%d: Expected compound closure, got '%s'\n",
			filename, cursor->line, cursor->content);
		निकास(1);
	पूर्ण
	cursor++;

	*_cursor = cursor;
	वापस children;

overrun_error:
	ख_लिखो(मानक_त्रुटि, "%s: Unexpectedly hit EOF\n", filename);
	निकास(1);
पूर्ण

अटल व्योम dump_element(स्थिर काष्ठा element *e, पूर्णांक level)
अणु
	स्थिर काष्ठा element *c;
	स्थिर काष्ठा type *t = e->type_def;
	स्थिर अक्षर *name = e->name ? e->name->content : ".";
	स्थिर अक्षर *tname = t && t->name ? t->name->content : ".";
	अक्षर tag[32];

	अगर (e->class == 0 && e->method == 0 && e->tag == 0)
		म_नकल(tag, "<...>");
	अन्यथा अगर (e->class == ASN1_UNIV)
		प्र_लिखो(tag, "%s %s %s",
			asn1_classes[e->class],
			asn1_methods[e->method],
			asn1_universal_tags[e->tag]);
	अन्यथा
		प्र_लिखो(tag, "%s %s %u",
			asn1_classes[e->class],
			asn1_methods[e->method],
			e->tag);

	म_लिखो("%c%c%c%c%c %c %*s[*] \e[33m%s\e[m %s %s \e[35m%s\e[m\n",
	       e->flags & ELEMENT_IMPLICIT ? 'I' : '-',
	       e->flags & ELEMENT_EXPLICIT ? 'E' : '-',
	       e->flags & ELEMENT_TAG_SPECIFIED ? 'T' : '-',
	       e->flags & ELEMENT_SKIPPABLE ? 'S' : '-',
	       e->flags & ELEMENT_CONDITIONAL ? 'C' : '-',
	       "-tTqQcaro"[e->compound],
	       level, "",
	       tag,
	       tname,
	       name,
	       e->action ? e->action->name : "");
	अगर (e->compound == TYPE_REF)
		dump_element(e->type->type->element, level + 3);
	अन्यथा
		क्रम (c = e->children; c; c = c->next)
			dump_element(c, level + 3);
पूर्ण

अटल व्योम dump_elements(व्योम)
अणु
	अगर (debug_opt)
		dump_element(type_list[0].element, 0);
पूर्ण

अटल व्योम render_element(खाता *out, काष्ठा element *e, काष्ठा element *tag);
अटल व्योम render_out_of_line_list(खाता *out);

अटल पूर्णांक nr_entries;
अटल पूर्णांक render_depth = 1;
अटल काष्ठा element *render_list, **render_list_p = &render_list;

__attribute__((क्रमmat(म_लिखो, 2, 3)))
अटल व्योम render_opcode(खाता *out, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;

	अगर (out) अणु
		ख_लिखो(out, "\t[%4d] =%*s", nr_entries, render_depth, "");
		बहु_शुरू(va, fmt);
		भख_लिखो(out, fmt, va);
		बहु_पूर्ण(va);
	पूर्ण
	nr_entries++;
पूर्ण

__attribute__((क्रमmat(म_लिखो, 2, 3)))
अटल व्योम render_more(खाता *out, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;

	अगर (out) अणु
		बहु_शुरू(va, fmt);
		भख_लिखो(out, fmt, va);
		बहु_पूर्ण(va);
	पूर्ण
पूर्ण

/*
 * Render the grammar पूर्णांकo a state machine definition.
 */
अटल व्योम render(खाता *out, खाता *hdr)
अणु
	काष्ठा element *e;
	काष्ठा action *action;
	काष्ठा type *root;
	पूर्णांक index;

	ख_लिखो(hdr, "/*\n");
	ख_लिखो(hdr, " * Automatically generated by asn1_compiler.  Do not edit\n");
	ख_लिखो(hdr, " *\n");
	ख_लिखो(hdr, " * ASN.1 parser for %s\n", grammar_name);
	ख_लिखो(hdr, " */\n");
	ख_लिखो(hdr, "#include <linux/asn1_decoder.h>\n");
	ख_लिखो(hdr, "\n");
	ख_लिखो(hdr, "extern const struct asn1_decoder %s_decoder;\n", grammar_name);
	अगर (ख_त्रुटि(hdr)) अणु
		लिखो_त्रुटि(headername);
		निकास(1);
	पूर्ण

	ख_लिखो(out, "/*\n");
	ख_लिखो(out, " * Automatically generated by asn1_compiler.  Do not edit\n");
	ख_लिखो(out, " *\n");
	ख_लिखो(out, " * ASN.1 parser for %s\n", grammar_name);
	ख_लिखो(out, " */\n");
	ख_लिखो(out, "#include <linux/asn1_ber_bytecode.h>\n");
	ख_लिखो(out, "#include \"%s.asn1.h\"\n", grammar_name);
	ख_लिखो(out, "\n");
	अगर (ख_त्रुटि(out)) अणु
		लिखो_त्रुटि(outputname);
		निकास(1);
	पूर्ण

	/* Tabulate the action functions we might have to call */
	ख_लिखो(hdr, "\n");
	index = 0;
	क्रम (action = action_list; action; action = action->next) अणु
		action->index = index++;
		ख_लिखो(hdr,
			"extern int %s(void *, size_t, unsigned char,"
			" const void *, size_t);\n",
			action->name);
	पूर्ण
	ख_लिखो(hdr, "\n");

	ख_लिखो(out, "enum %s_actions {\n", grammar_name);
	क्रम (action = action_list; action; action = action->next)
		ख_लिखो(out, "\tACT_%s = %u,\n",
			action->name, action->index);
	ख_लिखो(out, "\tNR__%s_actions = %u\n", grammar_name, nr_actions);
	ख_लिखो(out, "};\n");

	ख_लिखो(out, "\n");
	ख_लिखो(out, "static const asn1_action_t %s_action_table[NR__%s_actions] = {\n",
		grammar_name, grammar_name);
	क्रम (action = action_list; action; action = action->next)
		ख_लिखो(out, "\t[%4u] = %s,\n", action->index, action->name);
	ख_लिखो(out, "};\n");

	अगर (ख_त्रुटि(out)) अणु
		लिखो_त्रुटि(outputname);
		निकास(1);
	पूर्ण

	/* We करो two passes - the first one calculates all the offsets */
	verbose("Pass 1\n");
	nr_entries = 0;
	root = &type_list[0];
	render_element(शून्य, root->element, शून्य);
	render_opcode(शून्य, "ASN1_OP_COMPLETE,\n");
	render_out_of_line_list(शून्य);

	क्रम (e = element_list; e; e = e->list_next)
		e->flags &= ~ELEMENT_RENDERED;

	/* And then we actually render */
	verbose("Pass 2\n");
	ख_लिखो(out, "\n");
	ख_लिखो(out, "static const unsigned char %s_machine[] = {\n",
		grammar_name);

	nr_entries = 0;
	root = &type_list[0];
	render_element(out, root->element, शून्य);
	render_opcode(out, "ASN1_OP_COMPLETE,\n");
	render_out_of_line_list(out);

	ख_लिखो(out, "};\n");

	ख_लिखो(out, "\n");
	ख_लिखो(out, "const struct asn1_decoder %s_decoder = {\n", grammar_name);
	ख_लिखो(out, "\t.machine = %s_machine,\n", grammar_name);
	ख_लिखो(out, "\t.machlen = sizeof(%s_machine),\n", grammar_name);
	ख_लिखो(out, "\t.actions = %s_action_table,\n", grammar_name);
	ख_लिखो(out, "};\n");
पूर्ण

/*
 * Render the out-of-line elements
 */
अटल व्योम render_out_of_line_list(खाता *out)
अणु
	काष्ठा element *e, *ce;
	स्थिर अक्षर *act;
	पूर्णांक entry;

	जबतक ((e = render_list)) अणु
		render_list = e->render_next;
		अगर (!render_list)
			render_list_p = &render_list;

		render_more(out, "\n");
		e->entry_index = entry = nr_entries;
		render_depth++;
		क्रम (ce = e->children; ce; ce = ce->next)
			render_element(out, ce, शून्य);
		render_depth--;

		act = e->action ? "_ACT" : "";
		चयन (e->compound) अणु
		हाल SEQUENCE:
			render_opcode(out, "ASN1_OP_END_SEQ%s,\n", act);
			अवरोध;
		हाल SEQUENCE_OF:
			render_opcode(out, "ASN1_OP_END_SEQ_OF%s,\n", act);
			render_opcode(out, "_jump_target(%u),\n", entry);
			अवरोध;
		हाल SET:
			render_opcode(out, "ASN1_OP_END_SET%s,\n", act);
			अवरोध;
		हाल SET_OF:
			render_opcode(out, "ASN1_OP_END_SET_OF%s,\n", act);
			render_opcode(out, "_jump_target(%u),\n", entry);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (e->action)
			render_opcode(out, "_action(ACT_%s),\n",
				      e->action->name);
		render_opcode(out, "ASN1_OP_RETURN,\n");
	पूर्ण
पूर्ण

/*
 * Render an element.
 */
अटल व्योम render_element(खाता *out, काष्ठा element *e, काष्ठा element *tag)
अणु
	काष्ठा element *ec, *x;
	स्थिर अक्षर *cond, *act;
	पूर्णांक entry, skippable = 0, outofline = 0;

	अगर (e->flags & ELEMENT_SKIPPABLE ||
	    (tag && tag->flags & ELEMENT_SKIPPABLE))
		skippable = 1;

	अगर ((e->type_def && e->type_def->ref_count > 1) ||
	    skippable)
		outofline = 1;

	अगर (e->type_def && out) अणु
		render_more(out, "\t// %s\n", e->type_def->name->content);
	पूर्ण

	/* Render the operation */
	cond = (e->flags & ELEMENT_CONDITIONAL ||
		(tag && tag->flags & ELEMENT_CONDITIONAL)) ? "COND_" : "";
	act = e->action ? "_ACT" : "";
	चयन (e->compound) अणु
	हाल ANY:
		render_opcode(out, "ASN1_OP_%sMATCH_ANY%s%s,",
			      cond, act, skippable ? "_OR_SKIP" : "");
		अगर (e->name)
			render_more(out, "\t\t// %s", e->name->content);
		render_more(out, "\n");
		जाओ करोnt_render_tag;

	हाल TAG_OVERRIDE:
		render_element(out, e->children, e);
		वापस;

	हाल SEQUENCE:
	हाल SEQUENCE_OF:
	हाल SET:
	हाल SET_OF:
		render_opcode(out, "ASN1_OP_%sMATCH%s%s,",
			      cond,
			      outofline ? "_JUMP" : "",
			      skippable ? "_OR_SKIP" : "");
		अवरोध;

	हाल CHOICE:
		जाओ करोnt_render_tag;

	हाल TYPE_REF:
		अगर (e->class == ASN1_UNIV && e->method == ASN1_PRIM && e->tag == 0)
			जाओ करोnt_render_tag;
	शेष:
		render_opcode(out, "ASN1_OP_%sMATCH%s%s,",
			      cond, act,
			      skippable ? "_OR_SKIP" : "");
		अवरोध;
	पूर्ण

	x = tag ?: e;
	अगर (x->name)
		render_more(out, "\t\t// %s", x->name->content);
	render_more(out, "\n");

	/* Render the tag */
	अगर (!tag || !(tag->flags & ELEMENT_TAG_SPECIFIED))
		tag = e;

	अगर (tag->class == ASN1_UNIV &&
	    tag->tag != 14 &&
	    tag->tag != 15 &&
	    tag->tag != 31)
		render_opcode(out, "_tag(%s, %s, %s),\n",
			      asn1_classes[tag->class],
			      asn1_methods[tag->method | e->method],
			      asn1_universal_tags[tag->tag]);
	अन्यथा
		render_opcode(out, "_tagn(%s, %s, %2u),\n",
			      asn1_classes[tag->class],
			      asn1_methods[tag->method | e->method],
			      tag->tag);
	tag = शून्य;
करोnt_render_tag:

	/* Deal with compound types */
	चयन (e->compound) अणु
	हाल TYPE_REF:
		render_element(out, e->type->type->element, tag);
		अगर (e->action)
			render_opcode(out, "ASN1_OP_%sACT,\n",
				      skippable ? "MAYBE_" : "");
		अवरोध;

	हाल SEQUENCE:
		अगर (outofline) अणु
			/* Render out-of-line क्रम multiple use or
			 * skipability */
			render_opcode(out, "_jump_target(%u),", e->entry_index);
			अगर (e->type_def && e->type_def->name)
				render_more(out, "\t\t// --> %s",
					    e->type_def->name->content);
			render_more(out, "\n");
			अगर (!(e->flags & ELEMENT_RENDERED)) अणु
				e->flags |= ELEMENT_RENDERED;
				*render_list_p = e;
				render_list_p = &e->render_next;
			पूर्ण
			वापस;
		पूर्ण अन्यथा अणु
			/* Render अंतरभूत क्रम single use */
			render_depth++;
			क्रम (ec = e->children; ec; ec = ec->next)
				render_element(out, ec, शून्य);
			render_depth--;
			render_opcode(out, "ASN1_OP_END_SEQ%s,\n", act);
		पूर्ण
		अवरोध;

	हाल SEQUENCE_OF:
	हाल SET_OF:
		अगर (outofline) अणु
			/* Render out-of-line क्रम multiple use or
			 * skipability */
			render_opcode(out, "_jump_target(%u),", e->entry_index);
			अगर (e->type_def && e->type_def->name)
				render_more(out, "\t\t// --> %s",
					    e->type_def->name->content);
			render_more(out, "\n");
			अगर (!(e->flags & ELEMENT_RENDERED)) अणु
				e->flags |= ELEMENT_RENDERED;
				*render_list_p = e;
				render_list_p = &e->render_next;
			पूर्ण
			वापस;
		पूर्ण अन्यथा अणु
			/* Render अंतरभूत क्रम single use */
			entry = nr_entries;
			render_depth++;
			render_element(out, e->children, शून्य);
			render_depth--;
			अगर (e->compound == SEQUENCE_OF)
				render_opcode(out, "ASN1_OP_END_SEQ_OF%s,\n", act);
			अन्यथा
				render_opcode(out, "ASN1_OP_END_SET_OF%s,\n", act);
			render_opcode(out, "_jump_target(%u),\n", entry);
		पूर्ण
		अवरोध;

	हाल SET:
		/* I can't think of a nice way to करो SET support without having
		 * a stack of biपंचांगasks to make sure no element is repeated.
		 * The biपंचांगask has also to be checked that no non-optional
		 * elements are left out whilst not preventing optional
		 * elements from being left out.
		 */
		ख_लिखो(मानक_त्रुटि, "The ASN.1 SET type is not currently supported.\n");
		निकास(1);

	हाल CHOICE:
		क्रम (ec = e->children; ec; ec = ec->next)
			render_element(out, ec, ec);
		अगर (!skippable)
			render_opcode(out, "ASN1_OP_COND_FAIL,\n");
		अगर (e->action)
			render_opcode(out, "ASN1_OP_ACT,\n");
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (e->action)
		render_opcode(out, "_action(ACT_%s),\n", e->action->name);
पूर्ण
