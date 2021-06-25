<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित XEN_HVC_CONSOLE_H
#घोषणा XEN_HVC_CONSOLE_H

बाह्य काष्ठा console xenboot_console;

#अगर_घोषित CONFIG_HVC_XEN
व्योम xen_console_resume(व्योम);
व्योम xen_raw_console_ग_लिखो(स्थिर अक्षर *str);
__म_लिखो(1, 2)
व्योम xen_raw_prपूर्णांकk(स्थिर अक्षर *fmt, ...);
#अन्यथा
अटल अंतरभूत व्योम xen_console_resume(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम xen_raw_console_ग_लिखो(स्थिर अक्षर *str) अणु पूर्ण
अटल अंतरभूत __म_लिखो(1, 2)
व्योम xen_raw_prपूर्णांकk(स्थिर अक्षर *fmt, ...) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* XEN_HVC_CONSOLE_H */
