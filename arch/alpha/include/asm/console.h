<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __AXP_CONSOLE_H
#घोषणा __AXP_CONSOLE_H

#समावेश <uapi/यंत्र/console.h>

#अगर_अघोषित __ASSEMBLY__
बाह्य दीर्घ callback_माला_दो(दीर्घ unit, स्थिर अक्षर *s, दीर्घ length);
बाह्य दीर्घ callback_अ_लो(दीर्घ unit);
बाह्य दीर्घ callback_खोलो_console(व्योम);
बाह्य दीर्घ callback_बंद_console(व्योम);
बाह्य दीर्घ callback_खोलो(स्थिर अक्षर *device, दीर्घ length);
बाह्य दीर्घ callback_बंद(दीर्घ unit);
बाह्य दीर्घ callback_पढ़ो(दीर्घ channel, दीर्घ count, स्थिर अक्षर *buf, दीर्घ lbn);
बाह्य दीर्घ callback_दो_पर्या(दीर्घ id, स्थिर अक्षर *buf, अचिन्हित दीर्घ buf_size);
बाह्य दीर्घ callback_setenv(दीर्घ id, स्थिर अक्षर *buf, अचिन्हित दीर्घ buf_size);
बाह्य दीर्घ callback_save_env(व्योम);

बाह्य पूर्णांक srm_fixup(अचिन्हित दीर्घ new_callback_addr,
		     अचिन्हित दीर्घ new_hwrpb_addr);
बाह्य दीर्घ srm_माला_दो(स्थिर अक्षर *, दीर्घ);
बाह्य दीर्घ srm_prपूर्णांकk(स्थिर अक्षर *, ...)
	__attribute__ ((क्रमmat (म_लिखो, 1, 2)));

काष्ठा crb_काष्ठा;
काष्ठा hwrpb_काष्ठा;
बाह्य पूर्णांक callback_init_करोne;
बाह्य व्योम * callback_init(व्योम *);
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __AXP_CONSOLE_H */
