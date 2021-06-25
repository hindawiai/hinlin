<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित UTIL_H
#घोषणा UTIL_H

#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <getopt.h>

/*
 * Copyright 2011 The Chromium Authors, All Rights Reserved.
 * Copyright 2008 Jon Loeliger, Freescale Semiconductor, Inc.
 */

#अगर_घोषित __GNUC__
#अगर_घोषित __clang__
#घोषणा PRINTF(i, j)	__attribute__((क्रमmat (म_लिखो, i, j)))
#अन्यथा
#घोषणा PRINTF(i, j)	__attribute__((क्रमmat (gnu_म_लिखो, i, j)))
#पूर्ण_अगर
#घोषणा NORETURN	__attribute__((noवापस))
#अन्यथा
#घोषणा PRINTF(i, j)
#घोषणा NORETURN
#पूर्ण_अगर

#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))

#घोषणा stringअगरy(s)	stringअगरy_(s)
#घोषणा stringअगरy_(s)	#s

अटल अंतरभूत व्योम NORETURN PRINTF(1, 2) die(स्थिर अक्षर *str, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, str);
	ख_लिखो(मानक_त्रुटि, "FATAL ERROR: ");
	भख_लिखो(मानक_त्रुटि, str, ap);
	बहु_पूर्ण(ap);
	निकास(1);
पूर्ण

अटल अंतरभूत व्योम *xदो_स्मृति(माप_प्रकार len)
अणु
	व्योम *new = दो_स्मृति(len);

	अगर (!new)
		die("malloc() failed\n");

	वापस new;
पूर्ण

अटल अंतरभूत व्योम *xपुनः_स्मृति(व्योम *p, माप_प्रकार len)
अणु
	व्योम *new = पुनः_स्मृति(p, len);

	अगर (!new)
		die("realloc() failed (len=%zd)\n", len);

	वापस new;
पूर्ण

बाह्य अक्षर *xstrdup(स्थिर अक्षर *s);

बाह्य पूर्णांक PRINTF(2, 3) xaप्र_लिखो(अक्षर **strp, स्थिर अक्षर *fmt, ...);
बाह्य पूर्णांक PRINTF(2, 3) xaप्र_लिखो_append(अक्षर **strp, स्थिर अक्षर *fmt, ...);
बाह्य पूर्णांक xaभम_लिखो_append(अक्षर **strp, स्थिर अक्षर *fmt, बहु_सूची ap);
बाह्य अक्षर *join_path(स्थिर अक्षर *path, स्थिर अक्षर *name);

/**
 * Check a property of a given length to see अगर it is all prपूर्णांकable and
 * has a valid terminator. The property can contain either a single string,
 * or multiple strings each of non-zero length.
 *
 * @param data	The string to check
 * @param len	The string length including terminator
 * @वापस 1 अगर a valid prपूर्णांकable string, 0 अगर not
 */
bool util_is_prपूर्णांकable_string(स्थिर व्योम *data, पूर्णांक len);

/*
 * Parse an escaped अक्षरacter starting at index i in string s.  The resulting
 * अक्षरacter will be वापसed and the index i will be updated to poपूर्णांक at the
 * अक्षरacter directly after the end of the encoding, this may be the '\0'
 * terminator of the string.
 */
अक्षर get_escape_अक्षर(स्थिर अक्षर *s, पूर्णांक *i);

/**
 * Read a device tree file पूर्णांकo a buffer. This will report any errors on
 * मानक_त्रुटि.
 *
 * @param filename	The filename to पढ़ो, or - क्रम मानक_निवेश
 * @param len		If non-शून्य, the amount of data we managed to पढ़ो
 * @वापस Poपूर्णांकer to allocated buffer containing fdt, or शून्य on error
 */
अक्षर *utilfdt_पढ़ो(स्थिर अक्षर *filename, माप_प्रकार *len);

/**
 * Read a device tree file पूर्णांकo a buffer. Does not report errors, but only
 * वापसs them. The value वापसed can be passed to म_त्रुटि() to obtain
 * an error message क्रम the user.
 *
 * @param filename	The filename to पढ़ो, or - क्रम मानक_निवेश
 * @param buffp		Returns poपूर्णांकer to buffer containing fdt
 * @param len		If non-शून्य, the amount of data we managed to पढ़ो
 * @वापस 0 अगर ok, अन्यथा an त्रुटि_सं value representing the error
 */
पूर्णांक utilfdt_पढ़ो_err(स्थिर अक्षर *filename, अक्षर **buffp, माप_प्रकार *len);

/**
 * Write a device tree buffer to a file. This will report any errors on
 * मानक_त्रुटि.
 *
 * @param filename	The filename to ग_लिखो, or - क्रम मानक_निकास
 * @param blob		Poपूर्णांकer to buffer containing fdt
 * @वापस 0 अगर ok, -1 on error
 */
पूर्णांक utilfdt_ग_लिखो(स्थिर अक्षर *filename, स्थिर व्योम *blob);

/**
 * Write a device tree buffer to a file. Does not report errors, but only
 * वापसs them. The value वापसed can be passed to म_त्रुटि() to obtain
 * an error message क्रम the user.
 *
 * @param filename	The filename to ग_लिखो, or - क्रम मानक_निकास
 * @param blob		Poपूर्णांकer to buffer containing fdt
 * @वापस 0 अगर ok, अन्यथा an त्रुटि_सं value representing the error
 */
पूर्णांक utilfdt_ग_लिखो_err(स्थिर अक्षर *filename, स्थिर व्योम *blob);

/**
 * Decode a data type string. The purpose of this string
 *
 * The string consists of an optional अक्षरacter followed by the type:
 *	Modअगरier अक्षरacters:
 *		hh or b	1 byte
 *		h	2 byte
 *		l	4 byte, शेष
 *
 *	Type अक्षरacter:
 *		s	string
 *		i	चिन्हित पूर्णांकeger
 *		u	अचिन्हित पूर्णांकeger
 *		x	hex
 *
 * TODO: Implement ll modअगरier (8 bytes)
 * TODO: Implement o type (octal)
 *
 * @param fmt		Format string to process
 * @param type		Returns type found(s/d/u/x), or 0 अगर none
 * @param size		Returns size found(1,2,4,8) or 4 अगर none
 * @वापस 0 अगर ok, -1 on error (no type given, or other invalid क्रमmat)
 */
पूर्णांक utilfdt_decode_type(स्थिर अक्षर *fmt, पूर्णांक *type, पूर्णांक *size);

/*
 * This is a usage message fragment क्रम the -t option. It is the क्रमmat
 * supported by utilfdt_decode_type.
 */

#घोषणा USAGE_TYPE_MSG \
	"<type>\ts=string, i=int, u=unsigned, x=hex\n" \
	"\tOptional modifier prefix:\n" \
	"\t\thh or b=byte, h=2 byte, l=4 byte (default)";

/**
 * Prपूर्णांक property data in a पढ़ोable क्रमmat to मानक_निकास
 *
 * Properties that look like strings will be prपूर्णांकed as strings. Otherwise
 * the data will be displayed either as cells (अगर len is a multiple of 4
 * bytes) or bytes.
 *
 * If len is 0 then this function करोes nothing.
 *
 * @param data	Poपूर्णांकers to property data
 * @param len	Length of property data
 */
व्योम utilfdt_prपूर्णांक_data(स्थिर अक्षर *data, पूर्णांक len);

/**
 * Show source version and निकास
 */
व्योम NORETURN util_version(व्योम);

/**
 * Show usage and निकास
 *
 * This helps standardize the output of various utils.  You most likely want
 * to use the usage() helper below rather than call this.
 *
 * @param errmsg	If non-शून्य, an error message to display
 * @param synopsis	The initial example usage text (and possible examples)
 * @param लघु_opts	The string of लघु options
 * @param दीर्घ_opts	The काष्ठाure of दीर्घ options
 * @param opts_help	An array of help strings (should align with दीर्घ_opts)
 */
व्योम NORETURN util_usage(स्थिर अक्षर *errmsg, स्थिर अक्षर *synopsis,
			 स्थिर अक्षर *लघु_opts,
			 काष्ठा option स्थिर दीर्घ_opts[],
			 स्थिर अक्षर * स्थिर opts_help[]);

/**
 * Show usage and निकास
 *
 * If you name all your usage variables with usage_xxx, then you can call this
 * help macro rather than expanding all arguments yourself.
 *
 * @param errmsg	If non-शून्य, an error message to display
 */
#घोषणा usage(errmsg) \
	util_usage(errmsg, usage_synopsis, usage_लघु_opts, \
		   usage_दीर्घ_opts, usage_opts_help)

/**
 * Call getopt_दीर्घ() with standard options
 *
 * Since all util code runs getopt in the same way, provide a helper.
 */
#घोषणा util_getopt_दीर्घ() getopt_दीर्घ(argc, argv, usage_लघु_opts, \
				       usage_दीर्घ_opts, शून्य)

/* Helper क्रम aligning दीर्घ_opts array */
#घोषणा a_argument required_argument

/* Helper क्रम usage_लघु_opts string स्थिरant */
#घोषणा USAGE_COMMON_SHORT_OPTS "hV"

/* Helper क्रम usage_दीर्घ_opts option array */
#घोषणा USAGE_COMMON_LONG_OPTS \
	अणु"help",      no_argument, शून्य, 'h'पूर्ण, \
	अणु"version",   no_argument, शून्य, 'V'पूर्ण, \
	अणुशून्य,        no_argument, शून्य, 0x0पूर्ण

/* Helper क्रम usage_opts_help array */
#घोषणा USAGE_COMMON_OPTS_HELP \
	"Print this help and exit", \
	"Print version and exit", \
	शून्य

/* Helper क्रम getopt हाल statements */
#घोषणा हाल_USAGE_COMMON_FLAGS \
	हाल 'h': usage(शून्य); \
	हाल 'V': util_version(); \
	हाल '?': usage("unknown option");

#पूर्ण_अगर /* UTIL_H */
