<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश <core/option.h>
#समावेश <core/debug.h>

स्थिर अक्षर *
nvkm_stropt(स्थिर अक्षर *optstr, स्थिर अक्षर *opt, पूर्णांक *arglen)
अणु
	जबतक (optstr && *optstr != '\0') अणु
		पूर्णांक len = म_खोज(optstr, ",=");
		चयन (optstr[len]) अणु
		हाल '=':
			अगर (!strnहालcmpz(optstr, opt, len)) अणु
				optstr += len + 1;
				*arglen = म_खोज(optstr, ",=");
				वापस *arglen ? optstr : शून्य;
			पूर्ण
			optstr++;
			अवरोध;
		हाल ',':
			optstr++;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		optstr += len;
	पूर्ण

	वापस शून्य;
पूर्ण

bool
nvkm_boolopt(स्थिर अक्षर *optstr, स्थिर अक्षर *opt, bool value)
अणु
	पूर्णांक arglen;

	optstr = nvkm_stropt(optstr, opt, &arglen);
	अगर (optstr) अणु
		अगर (!strnहालcmpz(optstr, "0", arglen) ||
		    !strnहालcmpz(optstr, "no", arglen) ||
		    !strnहालcmpz(optstr, "off", arglen) ||
		    !strnहालcmpz(optstr, "false", arglen))
			value = false;
		अन्यथा
		अगर (!strnहालcmpz(optstr, "1", arglen) ||
		    !strnहालcmpz(optstr, "yes", arglen) ||
		    !strnहालcmpz(optstr, "on", arglen) ||
		    !strnहालcmpz(optstr, "true", arglen))
			value = true;
	पूर्ण

	वापस value;
पूर्ण

दीर्घ
nvkm_दीर्घopt(स्थिर अक्षर *optstr, स्थिर अक्षर *opt, दीर्घ value)
अणु
	दीर्घ result = value;
	पूर्णांक arglen;
	अक्षर *s;

	optstr = nvkm_stropt(optstr, opt, &arglen);
	अगर (optstr && (s = kstrndup(optstr, arglen, GFP_KERNEL))) अणु
		पूर्णांक ret = kम_से_दीर्घ(s, 0, &value);
		अगर (ret == 0)
			result = value;
		kमुक्त(s);
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक
nvkm_dbgopt(स्थिर अक्षर *optstr, स्थिर अक्षर *sub)
अणु
	पूर्णांक mode = 1, level = CONFIG_NOUVEAU_DEBUG_DEFAULT;

	जबतक (optstr) अणु
		पूर्णांक len = म_खोज(optstr, ",=");
		चयन (optstr[len]) अणु
		हाल '=':
			अगर (strnहालcmpz(optstr, sub, len))
				mode = 0;
			optstr++;
			अवरोध;
		शेष:
			अगर (mode) अणु
				अगर (!strnहालcmpz(optstr, "fatal", len))
					level = NV_DBG_FATAL;
				अन्यथा अगर (!strnहालcmpz(optstr, "error", len))
					level = NV_DBG_ERROR;
				अन्यथा अगर (!strnहालcmpz(optstr, "warn", len))
					level = NV_DBG_WARN;
				अन्यथा अगर (!strnहालcmpz(optstr, "info", len))
					level = NV_DBG_INFO;
				अन्यथा अगर (!strnहालcmpz(optstr, "debug", len))
					level = NV_DBG_DEBUG;
				अन्यथा अगर (!strnहालcmpz(optstr, "trace", len))
					level = NV_DBG_TRACE;
				अन्यथा अगर (!strnहालcmpz(optstr, "paranoia", len))
					level = NV_DBG_PARANOIA;
				अन्यथा अगर (!strnहालcmpz(optstr, "spam", len))
					level = NV_DBG_SPAM;
			पूर्ण

			अगर (optstr[len] != '\0') अणु
				optstr++;
				mode = 1;
				अवरोध;
			पूर्ण

			वापस level;
		पूर्ण
		optstr += len;
	पूर्ण

	वापस level;
पूर्ण
