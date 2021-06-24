<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KERNEL_FTRACE_INTERNAL_H
#घोषणा  _LINUX_KERNEL_FTRACE_INTERNAL_H

#अगर_घोषित CONFIG_FUNCTION_TRACER

बाह्य काष्ठा mutex ftrace_lock;
बाह्य काष्ठा ftrace_ops global_ops;

#अगर_घोषित CONFIG_DYNAMIC_FTRACE

पूर्णांक ftrace_startup(काष्ठा ftrace_ops *ops, पूर्णांक command);
पूर्णांक ftrace_shutकरोwn(काष्ठा ftrace_ops *ops, पूर्णांक command);
पूर्णांक ftrace_ops_test(काष्ठा ftrace_ops *ops, अचिन्हित दीर्घ ip, व्योम *regs);

#अन्यथा /* !CONFIG_DYNAMIC_FTRACE */

पूर्णांक __रेजिस्टर_ftrace_function(काष्ठा ftrace_ops *ops);
पूर्णांक __unरेजिस्टर_ftrace_function(काष्ठा ftrace_ops *ops);
/* Keep as macros so we करो not need to define the commands */
# define ftrace_startup(ops, command)					\
	(अणु								\
		पूर्णांक ___ret = __रेजिस्टर_ftrace_function(ops);		\
		अगर (!___ret)						\
			(ops)->flags |= FTRACE_OPS_FL_ENABLED;		\
		___ret;							\
	पूर्ण)
# define ftrace_shutकरोwn(ops, command)					\
	(अणु								\
		पूर्णांक ___ret = __unरेजिस्टर_ftrace_function(ops);		\
		अगर (!___ret)						\
			(ops)->flags &= ~FTRACE_OPS_FL_ENABLED;		\
		___ret;							\
	पूर्ण)
अटल अंतरभूत पूर्णांक
ftrace_ops_test(काष्ठा ftrace_ops *ops, अचिन्हित दीर्घ ip, व्योम *regs)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_FTRACE */

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
बाह्य पूर्णांक ftrace_graph_active;
व्योम update_function_graph_func(व्योम);
#अन्यथा /* !CONFIG_FUNCTION_GRAPH_TRACER */
# define ftrace_graph_active 0
अटल अंतरभूत व्योम update_function_graph_func(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

#अन्यथा /* !CONFIG_FUNCTION_TRACER */
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

#पूर्ण_अगर
