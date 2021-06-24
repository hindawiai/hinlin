<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Facebook
 */
#घोषणा _GNU_SOURCE
#समावेश <linux/types.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <linux/bpf.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <sched.h>
#समावेश <sys/रुको.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/resource.h>
#समावेश <fcntl.h>
#समावेश <मानककोष.स>
#समावेश <समय.स>

#समावेश <bpf/bpf.h>
#समावेश "bpf_util.h"

#घोषणा min(a, b) ((a) < (b) ? (a) : (b))
#अगर_अघोषित दुरत्व
# define दुरत्व(TYPE, MEMBER)	((माप_प्रकार)&((TYPE *)0)->MEMBER)
#पूर्ण_अगर
#घोषणा container_of(ptr, type, member) (अणु			\
	स्थिर typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (अक्षर *)__mptr - दुरत्व(type,member) );पूर्ण)

अटल पूर्णांक nr_cpus;
अटल अचिन्हित दीर्घ दीर्घ *dist_keys;
अटल अचिन्हित पूर्णांक dist_key_counts;

काष्ठा list_head अणु
	काष्ठा list_head *next, *prev;
पूर्ण;

अटल अंतरभूत व्योम INIT_LIST_HEAD(काष्ठा list_head *list)
अणु
	list->next = list;
	list->prev = list;
पूर्ण

अटल अंतरभूत पूर्णांक list_empty(स्थिर काष्ठा list_head *head)
अणु
	वापस head->next == head;
पूर्ण

अटल अंतरभूत व्योम __list_add(काष्ठा list_head *new,
			      काष्ठा list_head *prev,
			      काष्ठा list_head *next)
अणु
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
पूर्ण

अटल अंतरभूत व्योम list_add(काष्ठा list_head *new, काष्ठा list_head *head)
अणु
	__list_add(new, head, head->next);
पूर्ण

अटल अंतरभूत व्योम __list_del(काष्ठा list_head *prev, काष्ठा list_head *next)
अणु
	next->prev = prev;
	prev->next = next;
पूर्ण

अटल अंतरभूत व्योम __list_del_entry(काष्ठा list_head *entry)
अणु
	__list_del(entry->prev, entry->next);
पूर्ण

अटल अंतरभूत व्योम list_move(काष्ठा list_head *list, काष्ठा list_head *head)
अणु
	__list_del_entry(list);
	list_add(list, head);
पूर्ण

#घोषणा list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#घोषणा list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

काष्ठा pfect_lru_node अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ दीर्घ key;
पूर्ण;

काष्ठा pfect_lru अणु
	काष्ठा list_head list;
	काष्ठा pfect_lru_node *मुक्त_nodes;
	अचिन्हित पूर्णांक cur_size;
	अचिन्हित पूर्णांक lru_size;
	अचिन्हित पूर्णांक nr_unique;
	अचिन्हित पूर्णांक nr_misses;
	अचिन्हित पूर्णांक total;
	पूर्णांक map_fd;
पूर्ण;

अटल व्योम pfect_lru_init(काष्ठा pfect_lru *lru, अचिन्हित पूर्णांक lru_size,
			   अचिन्हित पूर्णांक nr_possible_elems)
अणु
	lru->map_fd = bpf_create_map(BPF_MAP_TYPE_HASH,
				     माप(अचिन्हित दीर्घ दीर्घ),
				     माप(काष्ठा pfect_lru_node *),
				     nr_possible_elems, 0);
	निश्चित(lru->map_fd != -1);

	lru->मुक्त_nodes = दो_स्मृति(lru_size * माप(काष्ठा pfect_lru_node));
	निश्चित(lru->मुक्त_nodes);

	INIT_LIST_HEAD(&lru->list);
	lru->cur_size = 0;
	lru->lru_size = lru_size;
	lru->nr_unique = lru->nr_misses = lru->total = 0;
पूर्ण

अटल व्योम pfect_lru_destroy(काष्ठा pfect_lru *lru)
अणु
	बंद(lru->map_fd);
	मुक्त(lru->मुक्त_nodes);
पूर्ण

अटल पूर्णांक pfect_lru_lookup_or_insert(काष्ठा pfect_lru *lru,
				      अचिन्हित दीर्घ दीर्घ key)
अणु
	काष्ठा pfect_lru_node *node = शून्य;
	पूर्णांक seen = 0;

	lru->total++;
	अगर (!bpf_map_lookup_elem(lru->map_fd, &key, &node)) अणु
		अगर (node) अणु
			list_move(&node->list, &lru->list);
			वापस 1;
		पूर्ण
		seen = 1;
	पूर्ण

	अगर (lru->cur_size < lru->lru_size) अणु
		node =  &lru->मुक्त_nodes[lru->cur_size++];
		INIT_LIST_HEAD(&node->list);
	पूर्ण अन्यथा अणु
		काष्ठा pfect_lru_node *null_node = शून्य;

		node = list_last_entry(&lru->list,
				       काष्ठा pfect_lru_node,
				       list);
		bpf_map_update_elem(lru->map_fd, &node->key, &null_node, BPF_EXIST);
	पूर्ण

	node->key = key;
	list_move(&node->list, &lru->list);

	lru->nr_misses++;
	अगर (seen) अणु
		निश्चित(!bpf_map_update_elem(lru->map_fd, &key, &node, BPF_EXIST));
	पूर्ण अन्यथा अणु
		lru->nr_unique++;
		निश्चित(!bpf_map_update_elem(lru->map_fd, &key, &node, BPF_NOEXIST));
	पूर्ण

	वापस seen;
पूर्ण

अटल अचिन्हित पूर्णांक पढ़ो_keys(स्थिर अक्षर *dist_file,
			      अचिन्हित दीर्घ दीर्घ **keys)
अणु
	काष्ठा stat fst;
	अचिन्हित दीर्घ दीर्घ *retkeys;
	अचिन्हित पूर्णांक counts = 0;
	पूर्णांक dist_fd;
	अक्षर *b, *l;
	पूर्णांक i;

	dist_fd = खोलो(dist_file, 0);
	निश्चित(dist_fd != -1);

	निश्चित(ख_स्थिति(dist_fd, &fst) == 0);
	b = दो_स्मृति(fst.st_size);
	निश्चित(b);

	निश्चित(पढ़ो(dist_fd, b, fst.st_size) == fst.st_size);
	बंद(dist_fd);
	क्रम (i = 0; i < fst.st_size; i++) अणु
		अगर (b[i] == '\n')
			counts++;
	पूर्ण
	counts++; /* in हाल the last line has no \न */

	retkeys = दो_स्मृति(counts * माप(अचिन्हित दीर्घ दीर्घ));
	निश्चित(retkeys);

	counts = 0;
	क्रम (l = म_मोहर(b, "\n"); l; l = म_मोहर(शून्य, "\n"))
		retkeys[counts++] = म_से_अदीर्घl(l, शून्य, 10);
	मुक्त(b);

	*keys = retkeys;

	वापस counts;
पूर्ण

अटल पूर्णांक create_map(पूर्णांक map_type, पूर्णांक map_flags, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक map_fd;

	map_fd = bpf_create_map(map_type, माप(अचिन्हित दीर्घ दीर्घ),
				माप(अचिन्हित दीर्घ दीर्घ), size, map_flags);

	अगर (map_fd == -1)
		लिखो_त्रुटि("bpf_create_map");

	वापस map_fd;
पूर्ण

अटल पूर्णांक sched_next_online(पूर्णांक pid, पूर्णांक next_to_try)
अणु
	cpu_set_t cpuset;

	अगर (next_to_try == nr_cpus)
		वापस -1;

	जबतक (next_to_try < nr_cpus) अणु
		CPU_ZERO(&cpuset);
		CPU_SET(next_to_try++, &cpuset);
		अगर (!sched_setaffinity(pid, माप(cpuset), &cpuset))
			अवरोध;
	पूर्ण

	वापस next_to_try;
पूर्ण

अटल व्योम run_parallel(अचिन्हित पूर्णांक tasks, व्योम (*fn)(पूर्णांक i, व्योम *data),
			 व्योम *data)
अणु
	पूर्णांक next_sched_cpu = 0;
	pid_t pid[tasks];
	पूर्णांक i;

	क्रम (i = 0; i < tasks; i++) अणु
		pid[i] = विभाजन();
		अगर (pid[i] == 0) अणु
			next_sched_cpu = sched_next_online(0, next_sched_cpu);
			fn(i, data);
			निकास(0);
		पूर्ण अन्यथा अगर (pid[i] == -1) अणु
			म_लिखो("couldn't spawn #%d process\n", i);
			निकास(1);
		पूर्ण
		/* It is mostly redundant and just allow the parent
		 * process to update next_shced_cpu क्रम the next child
		 * process
		 */
		next_sched_cpu = sched_next_online(pid[i], next_sched_cpu);
	पूर्ण
	क्रम (i = 0; i < tasks; i++) अणु
		पूर्णांक status;

		निश्चित(रुकोpid(pid[i], &status, 0) == pid[i]);
		निश्चित(status == 0);
	पूर्ण
पूर्ण

अटल व्योम करो_test_lru_dist(पूर्णांक task, व्योम *data)
अणु
	अचिन्हित पूर्णांक nr_misses = 0;
	काष्ठा pfect_lru pfect_lru;
	अचिन्हित दीर्घ दीर्घ key, value = 1234;
	अचिन्हित पूर्णांक i;

	अचिन्हित पूर्णांक lru_map_fd = ((अचिन्हित पूर्णांक *)data)[0];
	अचिन्हित पूर्णांक lru_size = ((अचिन्हित पूर्णांक *)data)[1];
	अचिन्हित दीर्घ दीर्घ key_offset = task * dist_key_counts;

	pfect_lru_init(&pfect_lru, lru_size, dist_key_counts);

	क्रम (i = 0; i < dist_key_counts; i++) अणु
		key = dist_keys[i] + key_offset;

		pfect_lru_lookup_or_insert(&pfect_lru, key);

		अगर (!bpf_map_lookup_elem(lru_map_fd, &key, &value))
			जारी;

		अगर (bpf_map_update_elem(lru_map_fd, &key, &value, BPF_NOEXIST)) अणु
			म_लिखो("bpf_map_update_elem(lru_map_fd, %llu): errno:%d\n",
			       key, त्रुटि_सं);
			निश्चित(0);
		पूर्ण

		nr_misses++;
	पूर्ण

	म_लिखो("    task:%d BPF LRU: nr_unique:%u(/%u) nr_misses:%u(/%u)\n",
	       task, pfect_lru.nr_unique, dist_key_counts, nr_misses,
	       dist_key_counts);
	म_लिखो("    task:%d Perfect LRU: nr_unique:%u(/%u) nr_misses:%u(/%u)\n",
	       task, pfect_lru.nr_unique, pfect_lru.total,
	       pfect_lru.nr_misses, pfect_lru.total);

	pfect_lru_destroy(&pfect_lru);
	बंद(lru_map_fd);
पूर्ण

अटल व्योम test_parallel_lru_dist(पूर्णांक map_type, पूर्णांक map_flags,
				   पूर्णांक nr_tasks, अचिन्हित पूर्णांक lru_size)
अणु
	पूर्णांक child_data[2];
	पूर्णांक lru_map_fd;

	म_लिखो("%s (map_type:%d map_flags:0x%X):\n", __func__, map_type,
	       map_flags);

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		lru_map_fd = create_map(map_type, map_flags,
					nr_cpus * lru_size);
	अन्यथा
		lru_map_fd = create_map(map_type, map_flags,
					nr_tasks * lru_size);
	निश्चित(lru_map_fd != -1);

	child_data[0] = lru_map_fd;
	child_data[1] = lru_size;

	run_parallel(nr_tasks, करो_test_lru_dist, child_data);

	बंद(lru_map_fd);
पूर्ण

अटल व्योम test_lru_loss0(पूर्णांक map_type, पूर्णांक map_flags)
अणु
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	अचिन्हित पूर्णांक old_unused_losses = 0;
	अचिन्हित पूर्णांक new_unused_losses = 0;
	अचिन्हित पूर्णांक used_losses = 0;
	पूर्णांक map_fd;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, 0) != -1);

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		map_fd = create_map(map_type, map_flags, 900 * nr_cpus);
	अन्यथा
		map_fd = create_map(map_type, map_flags, 900);

	निश्चित(map_fd != -1);

	value[0] = 1234;

	क्रम (key = 1; key <= 1000; key++) अणु
		पूर्णांक start_key, end_key;

		निश्चित(bpf_map_update_elem(map_fd, &key, value, BPF_NOEXIST) == 0);

		start_key = 101;
		end_key = min(key, 900);

		जबतक (start_key <= end_key) अणु
			bpf_map_lookup_elem(map_fd, &start_key, value);
			start_key++;
		पूर्ण
	पूर्ण

	क्रम (key = 1; key <= 1000; key++) अणु
		अगर (bpf_map_lookup_elem(map_fd, &key, value)) अणु
			अगर (key <= 100)
				old_unused_losses++;
			अन्यथा अगर (key <= 900)
				used_losses++;
			अन्यथा
				new_unused_losses++;
		पूर्ण
	पूर्ण

	बंद(map_fd);

	म_लिखो("older-elem-losses:%d(/100) active-elem-losses:%d(/800) "
	       "newer-elem-losses:%d(/100)\n",
	       old_unused_losses, used_losses, new_unused_losses);
पूर्ण

अटल व्योम test_lru_loss1(पूर्णांक map_type, पूर्णांक map_flags)
अणु
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	पूर्णांक map_fd;
	अचिन्हित पूर्णांक nr_losses = 0;

	म_लिखो("%s (map_type:%d map_flags:0x%X): ", __func__, map_type,
	       map_flags);

	निश्चित(sched_next_online(0, 0) != -1);

	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		map_fd = create_map(map_type, map_flags, 1000 * nr_cpus);
	अन्यथा
		map_fd = create_map(map_type, map_flags, 1000);

	निश्चित(map_fd != -1);

	value[0] = 1234;

	क्रम (key = 1; key <= 1000; key++)
		निश्चित(!bpf_map_update_elem(map_fd, &key, value, BPF_NOEXIST));

	क्रम (key = 1; key <= 1000; key++) अणु
		अगर (bpf_map_lookup_elem(map_fd, &key, value))
			nr_losses++;
	पूर्ण

	बंद(map_fd);

	म_लिखो("nr_losses:%d(/1000)\n", nr_losses);
पूर्ण

अटल व्योम करो_test_parallel_lru_loss(पूर्णांक task, व्योम *data)
अणु
	स्थिर अचिन्हित पूर्णांक nr_stable_elems = 1000;
	स्थिर अचिन्हित पूर्णांक nr_repeats = 100000;

	पूर्णांक map_fd = *(पूर्णांक *)data;
	अचिन्हित दीर्घ दीर्घ stable_base;
	अचिन्हित दीर्घ दीर्घ key, value[nr_cpus];
	अचिन्हित दीर्घ दीर्घ next_ins_key;
	अचिन्हित पूर्णांक nr_losses = 0;
	अचिन्हित पूर्णांक i;

	stable_base = task * nr_repeats * 2 + 1;
	next_ins_key = stable_base;
	value[0] = 1234;
	क्रम (i = 0; i < nr_stable_elems; i++) अणु
		निश्चित(bpf_map_update_elem(map_fd, &next_ins_key, value,
				       BPF_NOEXIST) == 0);
		next_ins_key++;
	पूर्ण

	क्रम (i = 0; i < nr_repeats; i++) अणु
		पूर्णांक rn;

		rn = अक्रम();

		अगर (rn % 10) अणु
			key = rn % nr_stable_elems + stable_base;
			bpf_map_lookup_elem(map_fd, &key, value);
		पूर्ण अन्यथा अणु
			bpf_map_update_elem(map_fd, &next_ins_key, value,
					BPF_NOEXIST);
			next_ins_key++;
		पूर्ण
	पूर्ण

	key = stable_base;
	क्रम (i = 0; i < nr_stable_elems; i++) अणु
		अगर (bpf_map_lookup_elem(map_fd, &key, value))
			nr_losses++;
		key++;
	पूर्ण

	म_लिखो("    task:%d nr_losses:%u\n", task, nr_losses);
पूर्ण

अटल व्योम test_parallel_lru_loss(पूर्णांक map_type, पूर्णांक map_flags, पूर्णांक nr_tasks)
अणु
	पूर्णांक map_fd;

	म_लिखो("%s (map_type:%d map_flags:0x%X):\n", __func__, map_type,
	       map_flags);

	/* Give 20% more than the active working set */
	अगर (map_flags & BPF_F_NO_COMMON_LRU)
		map_fd = create_map(map_type, map_flags,
				    nr_cpus * (1000 + 200));
	अन्यथा
		map_fd = create_map(map_type, map_flags,
				    nr_tasks * (1000 + 200));

	निश्चित(map_fd != -1);

	run_parallel(nr_tasks, करो_test_parallel_lru_loss, &map_fd);

	बंद(map_fd);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक map_flags[] = अणु0, BPF_F_NO_COMMON_LRUपूर्ण;
	स्थिर अक्षर *dist_file;
	पूर्णांक nr_tasks = 1;
	पूर्णांक lru_size;
	पूर्णांक f;

	अगर (argc < 4) अणु
		म_लिखो("Usage: %s <dist-file> <lru-size> <nr-tasks>\n",
		       argv[0]);
		वापस -1;
	पूर्ण

	dist_file = argv[1];
	lru_size = म_से_प(argv[2]);
	nr_tasks = म_से_प(argv[3]);

	रखो_बफ(मानक_निकास, शून्य);

	बेक्रम(समय(शून्य));

	nr_cpus = bpf_num_possible_cpus();
	निश्चित(nr_cpus != -1);
	म_लिखो("nr_cpus:%d\n\n", nr_cpus);

	nr_tasks = min(nr_tasks, nr_cpus);

	dist_key_counts = पढ़ो_keys(dist_file, &dist_keys);
	अगर (!dist_key_counts) अणु
		म_लिखो("%s has no key\n", dist_file);
		वापस -1;
	पूर्ण

	क्रम (f = 0; f < माप(map_flags) / माप(*map_flags); f++) अणु
		test_lru_loss0(BPF_MAP_TYPE_LRU_HASH, map_flags[f]);
		test_lru_loss1(BPF_MAP_TYPE_LRU_HASH, map_flags[f]);
		test_parallel_lru_loss(BPF_MAP_TYPE_LRU_HASH, map_flags[f],
				       nr_tasks);
		test_parallel_lru_dist(BPF_MAP_TYPE_LRU_HASH, map_flags[f],
				       nr_tasks, lru_size);
		म_लिखो("\n");
	पूर्ण

	मुक्त(dist_keys);

	वापस 0;
पूर्ण
