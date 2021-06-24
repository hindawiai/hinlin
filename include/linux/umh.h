<शैली गुरु>
#अगर_अघोषित __LINUX_UMH_H__
#घोषणा __LINUX_UMH_H__

#समावेश <linux/gfp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/compiler.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sysctl.h>

काष्ठा cred;
काष्ठा file;

#घोषणा UMH_NO_WAIT	0	/* करोn't रुको at all */
#घोषणा UMH_WAIT_EXEC	1	/* रुको क्रम the exec, but not the process */
#घोषणा UMH_WAIT_PROC	2	/* रुको क्रम the process to complete */
#घोषणा UMH_KILLABLE	4	/* रुको क्रम EXEC/PROC समाप्तable */

काष्ठा subprocess_info अणु
	काष्ठा work_काष्ठा work;
	काष्ठा completion *complete;
	स्थिर अक्षर *path;
	अक्षर **argv;
	अक्षर **envp;
	पूर्णांक रुको;
	पूर्णांक retval;
	पूर्णांक (*init)(काष्ठा subprocess_info *info, काष्ठा cred *new);
	व्योम (*cleanup)(काष्ठा subprocess_info *info);
	व्योम *data;
पूर्ण __अक्रमomize_layout;

बाह्य पूर्णांक
call_usermodehelper(स्थिर अक्षर *path, अक्षर **argv, अक्षर **envp, पूर्णांक रुको);

बाह्य काष्ठा subprocess_info *
call_usermodehelper_setup(स्थिर अक्षर *path, अक्षर **argv, अक्षर **envp,
			  gfp_t gfp_mask,
			  पूर्णांक (*init)(काष्ठा subprocess_info *info, काष्ठा cred *new),
			  व्योम (*cleanup)(काष्ठा subprocess_info *), व्योम *data);

बाह्य पूर्णांक
call_usermodehelper_exec(काष्ठा subprocess_info *info, पूर्णांक रुको);

बाह्य काष्ठा ctl_table usermodehelper_table[];

क्रमागत umh_disable_depth अणु
	UMH_ENABLED = 0,
	UMH_FREEZING,
	UMH_DISABLED,
पूर्ण;

बाह्य पूर्णांक __usermodehelper_disable(क्रमागत umh_disable_depth depth);
बाह्य व्योम __usermodehelper_set_disable_depth(क्रमागत umh_disable_depth depth);

अटल अंतरभूत पूर्णांक usermodehelper_disable(व्योम)
अणु
	वापस __usermodehelper_disable(UMH_DISABLED);
पूर्ण

अटल अंतरभूत व्योम usermodehelper_enable(व्योम)
अणु
	__usermodehelper_set_disable_depth(UMH_ENABLED);
पूर्ण

बाह्य पूर्णांक usermodehelper_पढ़ो_trylock(व्योम);
बाह्य दीर्घ usermodehelper_पढ़ो_lock_रुको(दीर्घ समयout);
बाह्य व्योम usermodehelper_पढ़ो_unlock(व्योम);

#पूर्ण_अगर /* __LINUX_UMH_H__ */
