<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_THREAD_H
#घोषणा __PERF_THREAD_H

#समावेश <linux/refcount.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/list.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश "srccode.h"
#समावेश "symbol_conf.h"
#समावेश <strlist.h>
#समावेश <पूर्णांकlist.h>
#समावेश "rwsem.h"
#समावेश "event.h"
#समावेश "callchain.h"

काष्ठा addr_location;
काष्ठा map;
काष्ठा perf_record_namespaces;
काष्ठा thपढ़ो_stack;
काष्ठा unwind_libunwind_ops;

काष्ठा lbr_stitch अणु
	काष्ठा list_head		lists;
	काष्ठा list_head		मुक्त_lists;
	काष्ठा perf_sample		prev_sample;
	काष्ठा callchain_cursor_node	*prev_lbr_cursor;
पूर्ण;

काष्ठा thपढ़ो अणु
	जोड़ अणु
		काष्ठा rb_node	 rb_node;
		काष्ठा list_head node;
	पूर्ण;
	काष्ठा maps		*maps;
	pid_t			pid_; /* Not all tools update this */
	pid_t			tid;
	pid_t			ppid;
	पूर्णांक			cpu;
	refcount_t		refcnt;
	bool			comm_set;
	पूर्णांक			comm_len;
	bool			dead; /* अगर set thपढ़ो has निकासed */
	काष्ठा list_head	namespaces_list;
	काष्ठा rw_semaphore	namespaces_lock;
	काष्ठा list_head	comm_list;
	काष्ठा rw_semaphore	comm_lock;
	u64			db_id;

	व्योम			*priv;
	काष्ठा thपढ़ो_stack	*ts;
	काष्ठा nsinfo		*nsinfo;
	काष्ठा srccode_state	srccode_state;
	bool			filter;
	पूर्णांक			filter_entry_depth;

	/* LBR call stack stitch */
	bool			lbr_stitch_enable;
	काष्ठा lbr_stitch	*lbr_stitch;
पूर्ण;

काष्ठा machine;
काष्ठा namespaces;
काष्ठा comm;

काष्ठा thपढ़ो *thपढ़ो__new(pid_t pid, pid_t tid);
पूर्णांक thपढ़ो__init_maps(काष्ठा thपढ़ो *thपढ़ो, काष्ठा machine *machine);
व्योम thपढ़ो__delete(काष्ठा thपढ़ो *thपढ़ो);

काष्ठा thपढ़ो *thपढ़ो__get(काष्ठा thपढ़ो *thपढ़ो);
व्योम thपढ़ो__put(काष्ठा thपढ़ो *thपढ़ो);

अटल अंतरभूत व्योम __thपढ़ो__zput(काष्ठा thपढ़ो **thपढ़ो)
अणु
	thपढ़ो__put(*thपढ़ो);
	*thपढ़ो = शून्य;
पूर्ण

#घोषणा thपढ़ो__zput(thपढ़ो) __thपढ़ो__zput(&thपढ़ो)

अटल अंतरभूत व्योम thपढ़ो__निकासed(काष्ठा thपढ़ो *thपढ़ो)
अणु
	thपढ़ो->dead = true;
पूर्ण

काष्ठा namespaces *thपढ़ो__namespaces(काष्ठा thपढ़ो *thपढ़ो);
पूर्णांक thपढ़ो__set_namespaces(काष्ठा thपढ़ो *thपढ़ो, u64 बारtamp,
			   काष्ठा perf_record_namespaces *event);

पूर्णांक __thपढ़ो__set_comm(काष्ठा thपढ़ो *thपढ़ो, स्थिर अक्षर *comm, u64 बारtamp,
		       bool exec);
अटल अंतरभूत पूर्णांक thपढ़ो__set_comm(काष्ठा thपढ़ो *thपढ़ो, स्थिर अक्षर *comm,
				   u64 बारtamp)
अणु
	वापस __thपढ़ो__set_comm(thपढ़ो, comm, बारtamp, false);
पूर्ण

पूर्णांक thपढ़ो__set_comm_from_proc(काष्ठा thपढ़ो *thपढ़ो);

पूर्णांक thपढ़ो__comm_len(काष्ठा thपढ़ो *thपढ़ो);
काष्ठा comm *thपढ़ो__comm(स्थिर काष्ठा thपढ़ो *thपढ़ो);
काष्ठा comm *thपढ़ो__exec_comm(स्थिर काष्ठा thपढ़ो *thपढ़ो);
स्थिर अक्षर *thपढ़ो__comm_str(काष्ठा thपढ़ो *thपढ़ो);
पूर्णांक thपढ़ो__insert_map(काष्ठा thपढ़ो *thपढ़ो, काष्ठा map *map);
पूर्णांक thपढ़ो__विभाजन(काष्ठा thपढ़ो *thपढ़ो, काष्ठा thपढ़ो *parent, u64 बारtamp, bool करो_maps_clone);
माप_प्रकार thपढ़ो__ख_लिखो(काष्ठा thपढ़ो *thपढ़ो, खाता *fp);

काष्ठा thपढ़ो *thपढ़ो__मुख्य_thपढ़ो(काष्ठा machine *machine, काष्ठा thपढ़ो *thपढ़ो);

काष्ठा map *thपढ़ो__find_map(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode, u64 addr,
			     काष्ठा addr_location *al);
काष्ठा map *thपढ़ो__find_map_fb(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode, u64 addr,
				काष्ठा addr_location *al);

काष्ठा symbol *thपढ़ो__find_symbol(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode,
				   u64 addr, काष्ठा addr_location *al);
काष्ठा symbol *thपढ़ो__find_symbol_fb(काष्ठा thपढ़ो *thपढ़ो, u8 cpumode,
				      u64 addr, काष्ठा addr_location *al);

व्योम thपढ़ो__find_cpumode_addr_location(काष्ठा thपढ़ो *thपढ़ो, u64 addr,
					काष्ठा addr_location *al);

पूर्णांक thपढ़ो__स_नकल(काष्ठा thपढ़ो *thपढ़ो, काष्ठा machine *machine,
		   व्योम *buf, u64 ip, पूर्णांक len, bool *is64bit);

अटल अंतरभूत व्योम *thपढ़ो__priv(काष्ठा thपढ़ो *thपढ़ो)
अणु
	वापस thपढ़ो->priv;
पूर्ण

अटल अंतरभूत व्योम thपढ़ो__set_priv(काष्ठा thपढ़ो *thपढ़ो, व्योम *p)
अणु
	thपढ़ो->priv = p;
पूर्ण

अटल अंतरभूत bool thपढ़ो__is_filtered(काष्ठा thपढ़ो *thपढ़ो)
अणु
	अगर (symbol_conf.comm_list &&
	    !strlist__has_entry(symbol_conf.comm_list, thपढ़ो__comm_str(thपढ़ो))) अणु
		वापस true;
	पूर्ण

	अगर (symbol_conf.pid_list &&
	    !पूर्णांकlist__has_entry(symbol_conf.pid_list, thपढ़ो->pid_)) अणु
		वापस true;
	पूर्ण

	अगर (symbol_conf.tid_list &&
	    !पूर्णांकlist__has_entry(symbol_conf.tid_list, thपढ़ो->tid)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम thपढ़ो__मुक्त_stitch_list(काष्ठा thपढ़ो *thपढ़ो);

#पूर्ण_अगर	/* __PERF_THREAD_H */
