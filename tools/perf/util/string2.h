<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_STRING_H
#घोषणा PERF_STRING_H

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <sys/types.h> // pid_t
#समावेश <मानकघोष.स>
#समावेश <माला.स>

बाह्य स्थिर अक्षर *graph_करोtted_line;
बाह्य स्थिर अक्षर *करोts;

s64 perf_म_से_दl(स्थिर अक्षर *str);
bool strglobmatch(स्थिर अक्षर *str, स्थिर अक्षर *pat);
bool strglobmatch_noहाल(स्थिर अक्षर *str, स्थिर अक्षर *pat);
bool strlazymatch(स्थिर अक्षर *str, स्थिर अक्षर *pat);
अटल अंतरभूत bool strisglob(स्थिर अक्षर *str)
अणु
	वापस strpbrk(str, "*?[") != शून्य;
पूर्ण
पूर्णांक strtailcmp(स्थिर अक्षर *s1, स्थिर अक्षर *s2);

अक्षर *aप्र_लिखो_expr_inout_पूर्णांकs(स्थिर अक्षर *var, bool in, माप_प्रकार nपूर्णांकs, पूर्णांक *पूर्णांकs);

अटल अंतरभूत अक्षर *aप्र_लिखो_expr_in_पूर्णांकs(स्थिर अक्षर *var, माप_प्रकार nपूर्णांकs, पूर्णांक *पूर्णांकs)
अणु
	वापस aप्र_लिखो_expr_inout_पूर्णांकs(var, true, nपूर्णांकs, पूर्णांकs);
पूर्ण

अटल अंतरभूत अक्षर *aप्र_लिखो_expr_not_in_पूर्णांकs(स्थिर अक्षर *var, माप_प्रकार nपूर्णांकs, पूर्णांक *पूर्णांकs)
अणु
	वापस aप्र_लिखो_expr_inout_पूर्णांकs(var, false, nपूर्णांकs, पूर्णांकs);
पूर्ण

अक्षर *aप्र_लिखो__tp_filter_pids(माप_प्रकार npids, pid_t *pids);

अक्षर *strpbrk_esc(अक्षर *str, स्थिर अक्षर *stopset);
अक्षर *strdup_esc(स्थिर अक्षर *str);

अचिन्हित पूर्णांक hex(अक्षर c);

#पूर्ण_अगर /* PERF_STRING_H */
