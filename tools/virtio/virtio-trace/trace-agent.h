<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TRACE_AGENT_H__
#घोषणा __TRACE_AGENT_H__
#समावेश <pthपढ़ो.h>
#समावेश <stdbool.h>

#घोषणा MAX_CPUS	256
#घोषणा PIPE_INIT       (1024*1024)

/*
 * agent_info - काष्ठाure managing total inक्रमmation of guest agent
 * @pipe_size:	size of pipe (शेष 1MB)
 * @use_मानक_निकास:	set to true when o option is added (शेष false)
 * @cpus:	total number of CPUs
 * @ctl_fd:	fd of control path, /dev/virtio-ports/agent-ctl-path
 * @rw_ti:	काष्ठाure managing inक्रमmation of पढ़ो/ग_लिखो thपढ़ोs
 */
काष्ठा agent_info अणु
	अचिन्हित दीर्घ pipe_size;
	bool use_मानक_निकास;
	पूर्णांक cpus;
	पूर्णांक ctl_fd;
	काष्ठा rw_thपढ़ो_info *rw_ti[MAX_CPUS];
पूर्ण;

/*
 * rw_thपढ़ो_info - काष्ठाure managing a पढ़ो/ग_लिखो thपढ़ो a cpu
 * @cpu_num:	cpu number operating this पढ़ो/ग_लिखो thपढ़ो
 * @in_fd:	fd of पढ़ोing trace data path in cpu_num
 * @out_fd:	fd of writing trace data path in cpu_num
 * @पढ़ो_pipe:	fd of पढ़ो pipe
 * @ग_लिखो_pipe:	fd of ग_लिखो pipe
 * @pipe_size:	size of pipe (शेष 1MB)
 */
काष्ठा rw_thपढ़ो_info अणु
	पूर्णांक cpu_num;
	पूर्णांक in_fd;
	पूर्णांक out_fd;
	पूर्णांक पढ़ो_pipe;
	पूर्णांक ग_लिखो_pipe;
	अचिन्हित दीर्घ pipe_size;
पूर्ण;

/* use क्रम stopping rw thपढ़ोs */
बाह्य bool global_sig_receive;

/* use क्रम notअगरication */
बाह्य bool global_run_operation;
बाह्य pthपढ़ो_mutex_t mutex_notअगरy;
बाह्य pthपढ़ो_cond_t cond_wakeup;

/* क्रम controller of पढ़ो/ग_लिखो thपढ़ोs */
बाह्य पूर्णांक rw_ctl_init(स्थिर अक्षर *ctl_path);
बाह्य व्योम *rw_ctl_loop(पूर्णांक ctl_fd);

/* क्रम trace पढ़ो/ग_लिखो thपढ़ो */
बाह्य व्योम *rw_thपढ़ो_info_new(व्योम);
बाह्य व्योम *rw_thपढ़ो_init(पूर्णांक cpu, स्थिर अक्षर *in_path, स्थिर अक्षर *out_path,
			bool मानक_निकास_flag, अचिन्हित दीर्घ pipe_size,
			काष्ठा rw_thपढ़ो_info *rw_ti);
बाह्य pthपढ़ो_t rw_thपढ़ो_run(काष्ठा rw_thपढ़ो_info *rw_ti);

अटल अंतरभूत व्योम *zalloc(माप_प्रकार size)
अणु
	वापस सुस्मृति(1, size);
पूर्ण

#घोषणा pr_err(क्रमmat, ...) ख_लिखो(मानक_त्रुटि, क्रमmat, ## __VA_ARGS__)
#घोषणा pr_info(क्रमmat, ...) ख_लिखो(मानक_निकास, क्रमmat, ## __VA_ARGS__)
#अगर_घोषित DEBUG
#घोषणा pr_debug(क्रमmat, ...) ख_लिखो(मानक_त्रुटि, क्रमmat, ## __VA_ARGS__)
#अन्यथा
#घोषणा pr_debug(क्रमmat, ...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /*__TRACE_AGENT_H__*/
