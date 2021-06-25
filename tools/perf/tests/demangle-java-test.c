<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश "tests.h"
#समावेश "session.h"
#समावेश "debug.h"
#समावेश "demangle-java.h"

पूर्णांक test__demangle_java(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक ret = TEST_OK;
	अक्षर *buf = शून्य;
	माप_प्रकार i;

	काष्ठा अणु
		स्थिर अक्षर *mangled, *demangled;
	पूर्ण test_हालs[] = अणु
		अणु "Ljava/lang/StringLatin1;equals([B[B)Z",
		  "boolean java.lang.StringLatin1.equals(byte[], byte[])" पूर्ण,
		अणु "Ljava/util/zip/ZipUtils;CENSIZ([BI)J",
		  "long java.util.zip.ZipUtils.CENSIZ(byte[], int)" पूर्ण,
		अणु "Ljava/util/regex/Pattern$BmpCharProperty;match(Ljava/util/regex/Matcher;ILjava/lang/CharSequence;)Z",
		  "boolean java.util.regex.Pattern$BmpCharProperty.match(java.util.regex.Matcher, int, java.lang.CharSequence)" पूर्ण,
		अणु "Ljava/lang/AbstractStringBuilder;appendChars(Ljava/lang/String;II)V",
		  "void java.lang.AbstractStringBuilder.appendChars(java.lang.String, int, int)" पूर्ण,
		अणु "Ljava/lang/Object;<init>()V",
		  "void java.lang.Object<init>()" पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < माप(test_हालs) / माप(test_हालs[0]); i++) अणु
		buf = java_demangle_sym(test_हालs[i].mangled, 0);
		अगर (म_भेद(buf, test_हालs[i].demangled)) अणु
			pr_debug("FAILED: %s: %s != %s\n", test_हालs[i].mangled,
				 buf, test_हालs[i].demangled);
			ret = TEST_FAIL;
		पूर्ण
		मुक्त(buf);
	पूर्ण

	वापस ret;
पूर्ण
