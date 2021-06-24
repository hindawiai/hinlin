<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __JVMTI_AGENT_H__
#घोषणा __JVMTI_AGENT_H__

#समावेश <sys/types.h>
#समावेश <मानक_निवेशt.h>
#समावेश <jvmti.h>

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ	pc;
	पूर्णांक		line_number;
	पूर्णांक		discrim; /* discriminator -- 0 क्रम now */
	jmethodID	methodID;
पूर्ण jvmti_line_info_t;

व्योम *jvmti_खोलो(व्योम);
पूर्णांक   jvmti_बंद(व्योम *agent);
पूर्णांक   jvmti_ग_लिखो_code(व्योम *agent, अक्षर स्थिर *symbol_name,
		       uपूर्णांक64_t vma, व्योम स्थिर *code,
		       स्थिर अचिन्हित पूर्णांक code_size);

पूर्णांक   jvmti_ग_लिखो_debug_info(व्योम *agent, uपूर्णांक64_t code, पूर्णांक nr_lines,
			     jvmti_line_info_t *li,
			     स्थिर अक्षर * स्थिर * file_names);

#अगर defined(__cplusplus)
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* __JVMTI_H__ */
