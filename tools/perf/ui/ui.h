<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_UI_H_
#घोषणा _PERF_UI_H_ 1

#समावेश <pthपढ़ो.h>
#समावेश <stdbool.h>
#समावेश <linux/compiler.h>

बाह्य pthपढ़ो_mutex_t ui__lock;
बाह्य व्योम *perf_gtk_handle;

बाह्य पूर्णांक use_browser;

व्योम setup_browser(bool fallback_to_pager);
व्योम निकास_browser(bool रुको_क्रम_ok);

#अगर_घोषित HAVE_SLANG_SUPPORT
पूर्णांक ui__init(व्योम);
व्योम ui__निकास(bool रुको_क्रम_ok);
#अन्यथा
अटल अंतरभूत पूर्णांक ui__init(व्योम)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत व्योम ui__निकास(bool रुको_क्रम_ok __maybe_unused) अणुपूर्ण
#पूर्ण_अगर

व्योम ui__refresh_dimensions(bool क्रमce);

काष्ठा option;

पूर्णांक stdio__config_color(स्थिर काष्ठा option *opt, स्थिर अक्षर *mode, पूर्णांक unset);

#पूर्ण_अगर /* _PERF_UI_H_ */
