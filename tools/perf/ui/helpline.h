<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_UI_HELPLINE_H_
#घोषणा _PERF_UI_HELPLINE_H_ 1

#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>

काष्ठा ui_helpline अणु
	व्योम (*pop)(व्योम);
	व्योम (*push)(स्थिर अक्षर *msg);
	पूर्णांक  (*show)(स्थिर अक्षर *fmt, बहु_सूची ap);
पूर्ण;

बाह्य काष्ठा ui_helpline *helpline_fns;

व्योम ui_helpline__init(व्योम);

व्योम ui_helpline__pop(व्योम);
व्योम ui_helpline__push(स्थिर अक्षर *msg);
व्योम ui_helpline__vpush(स्थिर अक्षर *fmt, बहु_सूची ap);
व्योम ui_helpline__fpush(स्थिर अक्षर *fmt, ...);
व्योम ui_helpline__माला_दो(स्थिर अक्षर *msg);
व्योम ui_helpline__म_लिखो(स्थिर अक्षर *fmt, ...);
पूर्णांक  ui_helpline__vshow(स्थिर अक्षर *fmt, बहु_सूची ap);

बाह्य अक्षर ui_helpline__current[512];
बाह्य अक्षर ui_helpline__last_msg[];

#पूर्ण_अगर /* _PERF_UI_HELPLINE_H_ */
