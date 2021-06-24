<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_MACHINE_H
#घोषणा __PERF_MACHINE_H

#समावेश <sys/types.h>
#समावेश <linux/rbtree.h>
#समावेश "maps.h"
#समावेश "dsos.h"
#समावेश "rwsem.h"

काष्ठा addr_location;
काष्ठा branch_stack;
काष्ठा dso;
काष्ठा dso_id;
काष्ठा evsel;
काष्ठा perf_sample;
काष्ठा symbol;
काष्ठा target;
काष्ठा thपढ़ो;
जोड़ perf_event;

/* Native host kernel uses -1 as pid index in machine */
#घोषणा	HOST_KERNEL_ID			(-1)
#घोषणा	DEFAULT_GUEST_KERNEL_ID		(0)

बाह्य स्थिर अक्षर *ref_reloc_sym_names[];

काष्ठा vdso_info;

#घोषणा THREADS__TABLE_BITS	8
#घोषणा THREADS__TABLE_SIZE	(1 << THREADS__TABLE_BITS)

काष्ठा thपढ़ोs अणु
	काष्ठा rb_root_cached  entries;
	काष्ठा rw_semaphore    lock;
	अचिन्हित पूर्णांक	       nr;
	काष्ठा list_head       dead;
	काष्ठा thपढ़ो	       *last_match;
पूर्ण;

काष्ठा machine अणु
	काष्ठा rb_node	  rb_node;
	pid_t		  pid;
	u16		  id_hdr_size;
	bool		  comm_exec;
	bool		  kptr_restrict_warned;
	bool		  single_address_space;
	अक्षर		  *root_dir;
	अक्षर		  *mmap_name;
	काष्ठा thपढ़ोs    thपढ़ोs[THREADS__TABLE_SIZE];
	काष्ठा vdso_info  *vdso_info;
	काष्ठा perf_env   *env;
	काष्ठा dsos	  dsos;
	काष्ठा maps	  kmaps;
	काष्ठा map	  *vmlinux_map;
	u64		  kernel_start;
	pid_t		  *current_tid;
	जोड़ अणु /* Tool specअगरic area */
		व्योम	  *priv;
		u64	  db_id;
	पूर्ण;
	bool		  trampolines_mapped;
पूर्ण;

अटल अंतरभूत काष्ठा thपढ़ोs *machine__thपढ़ोs(काष्ठा machine *machine, pid_t tid)
अणु
	/* Cast it to handle tid == -1 */
	वापस &machine->thपढ़ोs[(अचिन्हित पूर्णांक)tid % THREADS__TABLE_SIZE];
पूर्ण

/*
 * The मुख्य kernel (vmlinux) map
 */
अटल अंतरभूत
काष्ठा map *machine__kernel_map(काष्ठा machine *machine)
अणु
	वापस machine->vmlinux_map;
पूर्ण

/*
 * kernel (the one वापसed by machine__kernel_map()) plus kernel modules maps
 */
अटल अंतरभूत
काष्ठा maps *machine__kernel_maps(काष्ठा machine *machine)
अणु
	वापस &machine->kmaps;
पूर्ण

पूर्णांक machine__get_kernel_start(काष्ठा machine *machine);

अटल अंतरभूत u64 machine__kernel_start(काष्ठा machine *machine)
अणु
	अगर (!machine->kernel_start)
		machine__get_kernel_start(machine);
	वापस machine->kernel_start;
पूर्ण

अटल अंतरभूत bool machine__kernel_ip(काष्ठा machine *machine, u64 ip)
अणु
	u64 kernel_start = machine__kernel_start(machine);

	वापस ip >= kernel_start;
पूर्ण

u8 machine__addr_cpumode(काष्ठा machine *machine, u8 cpumode, u64 addr);

काष्ठा thपढ़ो *machine__find_thपढ़ो(काष्ठा machine *machine, pid_t pid,
				    pid_t tid);
काष्ठा thपढ़ो *machine__idle_thपढ़ो(काष्ठा machine *machine);
काष्ठा comm *machine__thपढ़ो_exec_comm(काष्ठा machine *machine,
				       काष्ठा thपढ़ो *thपढ़ो);

पूर्णांक machine__process_comm_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample);
पूर्णांक machine__process_निकास_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample);
पूर्णांक machine__process_विभाजन_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample);
पूर्णांक machine__process_lost_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample);
पूर्णांक machine__process_lost_samples_event(काष्ठा machine *machine, जोड़ perf_event *event,
					काष्ठा perf_sample *sample);
पूर्णांक machine__process_aux_event(काष्ठा machine *machine,
			       जोड़ perf_event *event);
पूर्णांक machine__process_itrace_start_event(काष्ठा machine *machine,
					जोड़ perf_event *event);
पूर्णांक machine__process_चयन_event(काष्ठा machine *machine,
				  जोड़ perf_event *event);
पूर्णांक machine__process_namespaces_event(काष्ठा machine *machine,
				      जोड़ perf_event *event,
				      काष्ठा perf_sample *sample);
पूर्णांक machine__process_cgroup_event(काष्ठा machine *machine,
				  जोड़ perf_event *event,
				  काष्ठा perf_sample *sample);
पूर्णांक machine__process_mmap_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample);
पूर्णांक machine__process_mmap2_event(काष्ठा machine *machine, जोड़ perf_event *event,
				 काष्ठा perf_sample *sample);
पूर्णांक machine__process_ksymbol(काष्ठा machine *machine,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample);
पूर्णांक machine__process_text_poke(काष्ठा machine *machine,
			       जोड़ perf_event *event,
			       काष्ठा perf_sample *sample);
पूर्णांक machine__process_event(काष्ठा machine *machine, जोड़ perf_event *event,
				काष्ठा perf_sample *sample);

प्रकार व्योम (*machine__process_t)(काष्ठा machine *machine, व्योम *data);

काष्ठा machines अणु
	काष्ठा machine host;
	काष्ठा rb_root_cached guests;
पूर्ण;

व्योम machines__init(काष्ठा machines *machines);
व्योम machines__निकास(काष्ठा machines *machines);

व्योम machines__process_guests(काष्ठा machines *machines,
			      machine__process_t process, व्योम *data);

काष्ठा machine *machines__add(काष्ठा machines *machines, pid_t pid,
			      स्थिर अक्षर *root_dir);
काष्ठा machine *machines__find_host(काष्ठा machines *machines);
काष्ठा machine *machines__find(काष्ठा machines *machines, pid_t pid);
काष्ठा machine *machines__findnew(काष्ठा machines *machines, pid_t pid);
काष्ठा machine *machines__find_guest(काष्ठा machines *machines, pid_t pid);

व्योम machines__set_id_hdr_size(काष्ठा machines *machines, u16 id_hdr_size);
व्योम machines__set_comm_exec(काष्ठा machines *machines, bool comm_exec);

काष्ठा machine *machine__new_host(व्योम);
काष्ठा machine *machine__new_kallsyms(व्योम);
पूर्णांक machine__init(काष्ठा machine *machine, स्थिर अक्षर *root_dir, pid_t pid);
व्योम machine__निकास(काष्ठा machine *machine);
व्योम machine__delete_thपढ़ोs(काष्ठा machine *machine);
व्योम machine__delete(काष्ठा machine *machine);
व्योम machine__हटाओ_thपढ़ो(काष्ठा machine *machine, काष्ठा thपढ़ो *th);

काष्ठा branch_info *sample__resolve_bstack(काष्ठा perf_sample *sample,
					   काष्ठा addr_location *al);
काष्ठा mem_info *sample__resolve_mem(काष्ठा perf_sample *sample,
				     काष्ठा addr_location *al);

काष्ठा callchain_cursor;

पूर्णांक thपढ़ो__resolve_callchain(काष्ठा thपढ़ो *thपढ़ो,
			      काष्ठा callchain_cursor *cursor,
			      काष्ठा evsel *evsel,
			      काष्ठा perf_sample *sample,
			      काष्ठा symbol **parent,
			      काष्ठा addr_location *root_al,
			      पूर्णांक max_stack);

/*
 * Default guest kernel is defined by parameter --guestkallsyms
 * and --guesपंचांगodules
 */
अटल अंतरभूत bool machine__is_शेष_guest(काष्ठा machine *machine)
अणु
	वापस machine ? machine->pid == DEFAULT_GUEST_KERNEL_ID : false;
पूर्ण

अटल अंतरभूत bool machine__is_host(काष्ठा machine *machine)
अणु
	वापस machine ? machine->pid == HOST_KERNEL_ID : false;
पूर्ण

bool machine__is(काष्ठा machine *machine, स्थिर अक्षर *arch);
पूर्णांक machine__nr_cpus_avail(काष्ठा machine *machine);

काष्ठा thपढ़ो *__machine__findnew_thपढ़ो(काष्ठा machine *machine, pid_t pid, pid_t tid);
काष्ठा thपढ़ो *machine__findnew_thपढ़ो(काष्ठा machine *machine, pid_t pid, pid_t tid);

काष्ठा dso *machine__findnew_dso_id(काष्ठा machine *machine, स्थिर अक्षर *filename, काष्ठा dso_id *id);
काष्ठा dso *machine__findnew_dso(काष्ठा machine *machine, स्थिर अक्षर *filename);

माप_प्रकार machine__ख_लिखो(काष्ठा machine *machine, खाता *fp);

अटल अंतरभूत
काष्ठा symbol *machine__find_kernel_symbol(काष्ठा machine *machine, u64 addr,
					   काष्ठा map **mapp)
अणु
	वापस maps__find_symbol(&machine->kmaps, addr, mapp);
पूर्ण

अटल अंतरभूत
काष्ठा symbol *machine__find_kernel_symbol_by_name(काष्ठा machine *machine,
						   स्थिर अक्षर *name,
						   काष्ठा map **mapp)
अणु
	वापस maps__find_symbol_by_name(&machine->kmaps, name, mapp);
पूर्ण

पूर्णांक arch__fix_module_text_start(u64 *start, u64 *size, स्थिर अक्षर *name);

पूर्णांक machine__load_kallsyms(काष्ठा machine *machine, स्थिर अक्षर *filename);

पूर्णांक machine__load_vmlinux_path(काष्ठा machine *machine);

माप_प्रकार machine__ख_लिखो_dsos_buildid(काष्ठा machine *machine, खाता *fp,
				     bool (skip)(काष्ठा dso *dso, पूर्णांक parm), पूर्णांक parm);
माप_प्रकार machines__ख_लिखो_dsos(काष्ठा machines *machines, खाता *fp);
माप_प्रकार machines__ख_लिखो_dsos_buildid(काष्ठा machines *machines, खाता *fp,
				     bool (skip)(काष्ठा dso *dso, पूर्णांक parm), पूर्णांक parm);

व्योम machine__destroy_kernel_maps(काष्ठा machine *machine);
पूर्णांक machine__create_kernel_maps(काष्ठा machine *machine);

पूर्णांक machines__create_kernel_maps(काष्ठा machines *machines, pid_t pid);
पूर्णांक machines__create_guest_kernel_maps(काष्ठा machines *machines);
व्योम machines__destroy_kernel_maps(काष्ठा machines *machines);

माप_प्रकार machine__ख_लिखो_vmlinux_path(काष्ठा machine *machine, खाता *fp);

प्रकार पूर्णांक (*machine__dso_t)(काष्ठा dso *dso, काष्ठा machine *machine, व्योम *priv);

पूर्णांक machine__क्रम_each_dso(काष्ठा machine *machine, machine__dso_t fn,
			  व्योम *priv);
पूर्णांक machine__क्रम_each_thपढ़ो(काष्ठा machine *machine,
			     पूर्णांक (*fn)(काष्ठा thपढ़ो *thपढ़ो, व्योम *p),
			     व्योम *priv);
पूर्णांक machines__क्रम_each_thपढ़ो(काष्ठा machines *machines,
			      पूर्णांक (*fn)(काष्ठा thपढ़ो *thपढ़ो, व्योम *p),
			      व्योम *priv);

pid_t machine__get_current_tid(काष्ठा machine *machine, पूर्णांक cpu);
पूर्णांक machine__set_current_tid(काष्ठा machine *machine, पूर्णांक cpu, pid_t pid,
			     pid_t tid);
/*
 * For use with libtraceevent's tep_set_function_resolver()
 */
अक्षर *machine__resolve_kernel_addr(व्योम *vmachine, अचिन्हित दीर्घ दीर्घ *addrp, अक्षर **modp);

व्योम machine__get_kallsyms_filename(काष्ठा machine *machine, अक्षर *buf,
				    माप_प्रकार bufsz);

पूर्णांक machine__create_extra_kernel_maps(काष्ठा machine *machine,
				      काष्ठा dso *kernel);

/* Kernel-space maps क्रम symbols that are outside the मुख्य kernel map and module maps */
काष्ठा extra_kernel_map अणु
	u64 start;
	u64 end;
	u64 pgoff;
	अक्षर name[KMAP_NAME_LEN];
पूर्ण;

पूर्णांक machine__create_extra_kernel_map(काष्ठा machine *machine,
				     काष्ठा dso *kernel,
				     काष्ठा extra_kernel_map *xm);

पूर्णांक machine__map_x86_64_entry_trampolines(काष्ठा machine *machine,
					  काष्ठा dso *kernel);

#पूर्ण_अगर /* __PERF_MACHINE_H */
