<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2011 The Chromium Authors, All Rights Reserved.
 * Copyright 2008 Jon Loeliger, Freescale Semiconductor, Inc.
 *
 * util_is_prपूर्णांकable_string contributed by
 *	Pantelis Antoniou <pantelis.antoniou AT gmail.com>
 */

#समावेश <प्रकार.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <पूर्णांकtypes.h>

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <unistd.h>

#समावेश "libfdt.h"
#समावेश "util.h"
#समावेश "version_gen.h"

अक्षर *xstrdup(स्थिर अक्षर *s)
अणु
	पूर्णांक len = म_माप(s) + 1;
	अक्षर *d = xदो_स्मृति(len);

	स_नकल(d, s, len);

	वापस d;
पूर्ण

पूर्णांक xaभम_लिखो_append(अक्षर **strp, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	पूर्णांक n, size = 0;	/* start with 128 bytes */
	अक्षर *p;
	बहु_सूची ap_copy;

	p = *strp;
	अगर (p)
		size = म_माप(p);

	va_copy(ap_copy, ap);
	n = vsnम_लिखो(शून्य, 0, fmt, ap_copy) + 1;
	बहु_पूर्ण(ap_copy);

	p = xपुनः_स्मृति(p, size + n);

	n = vsnम_लिखो(p + size, n, fmt, ap);

	*strp = p;
	वापस म_माप(p);
पूर्ण

पूर्णांक xaप्र_लिखो_append(अक्षर **strp, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक n;
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	n = xaभम_लिखो_append(strp, fmt, ap);
	बहु_पूर्ण(ap);

	वापस n;
पूर्ण

पूर्णांक xaप्र_लिखो(अक्षर **strp, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक n;
	बहु_सूची ap;

	*strp = शून्य;

	बहु_शुरू(ap, fmt);
	n = xaभम_लिखो_append(strp, fmt, ap);
	बहु_पूर्ण(ap);

	वापस n;
पूर्ण

अक्षर *join_path(स्थिर अक्षर *path, स्थिर अक्षर *name)
अणु
	पूर्णांक lenp = म_माप(path);
	पूर्णांक lenn = म_माप(name);
	पूर्णांक len;
	पूर्णांक needslash = 1;
	अक्षर *str;

	len = lenp + lenn + 2;
	अगर ((lenp > 0) && (path[lenp-1] == '/')) अणु
		needslash = 0;
		len--;
	पूर्ण

	str = xदो_स्मृति(len);
	स_नकल(str, path, lenp);
	अगर (needslash) अणु
		str[lenp] = '/';
		lenp++;
	पूर्ण
	स_नकल(str+lenp, name, lenn+1);
	वापस str;
पूर्ण

bool util_is_prपूर्णांकable_string(स्थिर व्योम *data, पूर्णांक len)
अणु
	स्थिर अक्षर *s = data;
	स्थिर अक्षर *ss, *se;

	/* zero length is not */
	अगर (len == 0)
		वापस 0;

	/* must terminate with zero */
	अगर (s[len - 1] != '\0')
		वापस 0;

	se = s + len;

	जबतक (s < se) अणु
		ss = s;
		जबतक (s < se && *s && है_छाप((अचिन्हित अक्षर)*s))
			s++;

		/* not zero, or not करोne yet */
		अगर (*s != '\0' || s == ss)
			वापस 0;

		s++;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Parse a octal encoded अक्षरacter starting at index i in string s.  The
 * resulting अक्षरacter will be वापसed and the index i will be updated to
 * poपूर्णांक at the अक्षरacter directly after the end of the encoding, this may be
 * the '\0' terminator of the string.
 */
अटल अक्षर get_oct_अक्षर(स्थिर अक्षर *s, पूर्णांक *i)
अणु
	अक्षर x[4];
	अक्षर *endx;
	दीर्घ val;

	x[3] = '\0';
	म_नकलन(x, s + *i, 3);

	val = म_से_दीर्घ(x, &endx, 8);

	निश्चित(endx > x);

	(*i) += endx - x;
	वापस val;
पूर्ण

/*
 * Parse a hexadecimal encoded अक्षरacter starting at index i in string s.  The
 * resulting अक्षरacter will be वापसed and the index i will be updated to
 * poपूर्णांक at the अक्षरacter directly after the end of the encoding, this may be
 * the '\0' terminator of the string.
 */
अटल अक्षर get_hex_अक्षर(स्थिर अक्षर *s, पूर्णांक *i)
अणु
	अक्षर x[3];
	अक्षर *endx;
	दीर्घ val;

	x[2] = '\0';
	म_नकलन(x, s + *i, 2);

	val = म_से_दीर्घ(x, &endx, 16);
	अगर (!(endx  > x))
		die("\\x used with no following hex digits\n");

	(*i) += endx - x;
	वापस val;
पूर्ण

अक्षर get_escape_अक्षर(स्थिर अक्षर *s, पूर्णांक *i)
अणु
	अक्षर	c = s[*i];
	पूर्णांक	j = *i + 1;
	अक्षर	val;

	चयन (c) अणु
	हाल 'a':
		val = '\a';
		अवरोध;
	हाल 'b':
		val = '\b';
		अवरोध;
	हाल 't':
		val = '\t';
		अवरोध;
	हाल 'n':
		val = '\n';
		अवरोध;
	हाल 'v':
		val = '\v';
		अवरोध;
	हाल 'f':
		val = '\f';
		अवरोध;
	हाल 'r':
		val = '\r';
		अवरोध;
	हाल '0':
	हाल '1':
	हाल '2':
	हाल '3':
	हाल '4':
	हाल '5':
	हाल '6':
	हाल '7':
		j--; /* need to re-पढ़ो the first digit as
		      * part of the octal value */
		val = get_oct_अक्षर(s, &j);
		अवरोध;
	हाल 'x':
		val = get_hex_अक्षर(s, &j);
		अवरोध;
	शेष:
		val = c;
	पूर्ण

	(*i) = j;
	वापस val;
पूर्ण

पूर्णांक utilfdt_पढ़ो_err(स्थिर अक्षर *filename, अक्षर **buffp, माप_प्रकार *len)
अणु
	पूर्णांक fd = 0;	/* assume मानक_निवेश */
	अक्षर *buf = शून्य;
	माप_प्रकार bufsize = 1024, offset = 0;
	पूर्णांक ret = 0;

	*buffp = शून्य;
	अगर (म_भेद(filename, "-") != 0) अणु
		fd = खोलो(filename, O_RDONLY);
		अगर (fd < 0)
			वापस त्रुटि_सं;
	पूर्ण

	/* Loop until we have पढ़ो everything */
	buf = xदो_स्मृति(bufsize);
	करो अणु
		/* Expand the buffer to hold the next chunk */
		अगर (offset == bufsize) अणु
			bufsize *= 2;
			buf = xपुनः_स्मृति(buf, bufsize);
		पूर्ण

		ret = पढ़ो(fd, &buf[offset], bufsize - offset);
		अगर (ret < 0) अणु
			ret = त्रुटि_सं;
			अवरोध;
		पूर्ण
		offset += ret;
	पूर्ण जबतक (ret != 0);

	/* Clean up, including closing मानक_निवेश; वापस त्रुटि_सं on error */
	बंद(fd);
	अगर (ret)
		मुक्त(buf);
	अन्यथा
		*buffp = buf;
	अगर (len)
		*len = bufsize;
	वापस ret;
पूर्ण

अक्षर *utilfdt_पढ़ो(स्थिर अक्षर *filename, माप_प्रकार *len)
अणु
	अक्षर *buff;
	पूर्णांक ret = utilfdt_पढ़ो_err(filename, &buff, len);

	अगर (ret) अणु
		ख_लिखो(मानक_त्रुटि, "Couldn't open blob from '%s': %s\n", filename,
			म_त्रुटि(ret));
		वापस शून्य;
	पूर्ण
	/* Successful पढ़ो */
	वापस buff;
पूर्ण

पूर्णांक utilfdt_ग_लिखो_err(स्थिर अक्षर *filename, स्थिर व्योम *blob)
अणु
	पूर्णांक fd = 1;	/* assume मानक_निकास */
	पूर्णांक totalsize;
	पूर्णांक offset;
	पूर्णांक ret = 0;
	स्थिर अक्षर *ptr = blob;

	अगर (म_भेद(filename, "-") != 0) अणु
		fd = खोलो(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		अगर (fd < 0)
			वापस त्रुटि_सं;
	पूर्ण

	totalsize = fdt_totalsize(blob);
	offset = 0;

	जबतक (offset < totalsize) अणु
		ret = ग_लिखो(fd, ptr + offset, totalsize - offset);
		अगर (ret < 0) अणु
			ret = -त्रुटि_सं;
			अवरोध;
		पूर्ण
		offset += ret;
	पूर्ण
	/* Close the file/मानक_निवेश; वापस त्रुटि_सं on error */
	अगर (fd != 1)
		बंद(fd);
	वापस ret < 0 ? -ret : 0;
पूर्ण


पूर्णांक utilfdt_ग_लिखो(स्थिर अक्षर *filename, स्थिर व्योम *blob)
अणु
	पूर्णांक ret = utilfdt_ग_लिखो_err(filename, blob);

	अगर (ret) अणु
		ख_लिखो(मानक_त्रुटि, "Couldn't write blob to '%s': %s\n", filename,
			म_त्रुटि(ret));
	पूर्ण
	वापस ret ? -1 : 0;
पूर्ण

पूर्णांक utilfdt_decode_type(स्थिर अक्षर *fmt, पूर्णांक *type, पूर्णांक *size)
अणु
	पूर्णांक qualअगरier = 0;

	अगर (!*fmt)
		वापस -1;

	/* get the conversion qualअगरier */
	*size = -1;
	अगर (म_अक्षर("hlLb", *fmt)) अणु
		qualअगरier = *fmt++;
		अगर (qualअगरier == *fmt) अणु
			चयन (*fmt++) अणु
/* TODO:		हाल 'l': qualifier = 'L'; अवरोध;*/
			हाल 'h':
				qualअगरier = 'b';
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* we should now have a type */
	अगर ((*fmt == '\0') || !म_अक्षर("iuxs", *fmt))
		वापस -1;

	/* convert qualअगरier (bhL) to byte size */
	अगर (*fmt != 's')
		*size = qualअगरier == 'b' ? 1 :
				qualअगरier == 'h' ? 2 :
				qualअगरier == 'l' ? 4 : -1;
	*type = *fmt++;

	/* that should be it! */
	अगर (*fmt)
		वापस -1;
	वापस 0;
पूर्ण

व्योम utilfdt_prपूर्णांक_data(स्थिर अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक i;
	स्थिर अक्षर *s;

	/* no data, करोn't prपूर्णांक */
	अगर (len == 0)
		वापस;

	अगर (util_is_prपूर्णांकable_string(data, len)) अणु
		म_लिखो(" = ");

		s = data;
		करो अणु
			म_लिखो("\"%s\"", s);
			s += म_माप(s) + 1;
			अगर (s < data + len)
				म_लिखो(", ");
		पूर्ण जबतक (s < data + len);

	पूर्ण अन्यथा अगर ((len % 4) == 0) अणु
		स्थिर fdt32_t *cell = (स्थिर fdt32_t *)data;

		म_लिखो(" = <");
		क्रम (i = 0, len /= 4; i < len; i++)
			म_लिखो("0x%08" PRIx32 "%s", fdt32_to_cpu(cell[i]),
			       i < (len - 1) ? " " : "");
		म_लिखो(">");
	पूर्ण अन्यथा अणु
		स्थिर अचिन्हित अक्षर *p = (स्थिर अचिन्हित अक्षर *)data;
		म_लिखो(" = [");
		क्रम (i = 0; i < len; i++)
			म_लिखो("%02x%s", *p++, i < len - 1 ? " " : "");
		म_लिखो("]");
	पूर्ण
पूर्ण

व्योम NORETURN util_version(व्योम)
अणु
	म_लिखो("Version: %s\n", DTC_VERSION);
	निकास(0);
पूर्ण

व्योम NORETURN util_usage(स्थिर अक्षर *errmsg, स्थिर अक्षर *synopsis,
			 स्थिर अक्षर *लघु_opts,
			 काष्ठा option स्थिर दीर्घ_opts[],
			 स्थिर अक्षर * स्थिर opts_help[])
अणु
	खाता *fp = errmsg ? मानक_त्रुटि : मानक_निकास;
	स्थिर अक्षर a_arg[] = "<arg>";
	माप_प्रकार a_arg_len = म_माप(a_arg) + 1;
	माप_प्रकार i;
	पूर्णांक optlen;

	ख_लिखो(fp,
		"Usage: %s\n"
		"\n"
		"Options: -[%s]\n", synopsis, लघु_opts);

	/* prescan the --दीर्घ opt length to स्वतः-align */
	optlen = 0;
	क्रम (i = 0; दीर्घ_opts[i].name; ++i) अणु
		/* +1 is क्रम space between --opt and help text */
		पूर्णांक l = म_माप(दीर्घ_opts[i].name) + 1;
		अगर (दीर्घ_opts[i].has_arg == a_argument)
			l += a_arg_len;
		अगर (optlen < l)
			optlen = l;
	पूर्ण

	क्रम (i = 0; दीर्घ_opts[i].name; ++i) अणु
		/* helps when adding new applets or options */
		निश्चित(opts_help[i] != शून्य);

		/* first output the लघु flag अगर it has one */
		अगर (दीर्घ_opts[i].val > '~')
			ख_लिखो(fp, "      ");
		अन्यथा
			ख_लिखो(fp, "  -%c, ", दीर्घ_opts[i].val);

		/* then the दीर्घ flag */
		अगर (दीर्घ_opts[i].has_arg == no_argument)
			ख_लिखो(fp, "--%-*s", optlen, दीर्घ_opts[i].name);
		अन्यथा
			ख_लिखो(fp, "--%s %s%*s", दीर्घ_opts[i].name, a_arg,
				(पूर्णांक)(optlen - म_माप(दीर्घ_opts[i].name) - a_arg_len), "");

		/* finally the help text */
		ख_लिखो(fp, "%s\n", opts_help[i]);
	पूर्ण

	अगर (errmsg) अणु
		ख_लिखो(fp, "\nError: %s\n", errmsg);
		निकास(निकास_त्रुटि);
	पूर्ण अन्यथा
		निकास(निकास_सफल);
पूर्ण
