<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_UI_UTIL_H_
#घोषणा _PERF_UI_UTIL_H_ 1

#समावेश <मानकतर्क.स>

पूर्णांक ui__अ_लोh(पूर्णांक delay_secs);
पूर्णांक ui__popup_menu(पूर्णांक argc, अक्षर * स्थिर argv[], पूर्णांक *keyp);
पूर्णांक ui__help_winकरोw(स्थिर अक्षर *text);
पूर्णांक ui__dialog_yesno(स्थिर अक्षर *msg);
व्योम __ui__info_winकरोw(स्थिर अक्षर *title, स्थिर अक्षर *text, स्थिर अक्षर *निकास_msg);
व्योम ui__info_winकरोw(स्थिर अक्षर *title, स्थिर अक्षर *text);
पूर्णांक ui__question_winकरोw(स्थिर अक्षर *title, स्थिर अक्षर *text,
			स्थिर अक्षर *निकास_msg, पूर्णांक delay_secs);

काष्ठा perf_error_ops अणु
	पूर्णांक (*error)(स्थिर अक्षर *क्रमmat, बहु_सूची args);
	पूर्णांक (*warning)(स्थिर अक्षर *क्रमmat, बहु_सूची args);
पूर्ण;

पूर्णांक perf_error__रेजिस्टर(काष्ठा perf_error_ops *eops);
पूर्णांक perf_error__unरेजिस्टर(काष्ठा perf_error_ops *eops);

#पूर्ण_अगर /* _PERF_UI_UTIL_H_ */
