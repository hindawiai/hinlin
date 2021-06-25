<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश "builtin.h"
#समावेश "perf.h"

#समावेश "util/evlist.h" // क्रम काष्ठा evsel_str_handler
#समावेश "util/evsel.h"
#समावेश "util/symbol.h"
#समावेश "util/thread.h"
#समावेश "util/header.h"

#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश "util/trace-event.h"

#समावेश "util/debug.h"
#समावेश "util/session.h"
#समावेश "util/tool.h"
#समावेश "util/data.h"

#समावेश <sys/types.h>
#समावेश <sys/prctl.h>
#समावेश <semaphore.h>
#समावेश <pthपढ़ो.h>
#समावेश <गणित.स>
#समावेश <सीमा.स>

#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <linux/err.h>

अटल काष्ठा perf_session *session;

/* based on kernel/lockdep.c */
#घोषणा LOCKHASH_BITS		12
#घोषणा LOCKHASH_SIZE		(1UL << LOCKHASH_BITS)

अटल काष्ठा list_head lockhash_table[LOCKHASH_SIZE];

#घोषणा __lockhashfn(key)	hash_दीर्घ((अचिन्हित दीर्घ)key, LOCKHASH_BITS)
#घोषणा lockhashentry(key)	(lockhash_table + __lockhashfn((key)))

काष्ठा lock_stat अणु
	काष्ठा list_head	hash_entry;
	काष्ठा rb_node		rb;		/* used क्रम sorting */

	/*
	 * FIXME: evsel__पूर्णांकval() वापसs u64,
	 * so address of lockdep_map should be treated as 64bit.
	 * Is there more better solution?
	 */
	व्योम			*addr;		/* address of lockdep_map, used as ID */
	अक्षर			*name;		/* क्रम म_नकल(), we cannot use स्थिर */

	अचिन्हित पूर्णांक		nr_acquire;
	अचिन्हित पूर्णांक		nr_acquired;
	अचिन्हित पूर्णांक		nr_contended;
	अचिन्हित पूर्णांक		nr_release;

	अचिन्हित पूर्णांक		nr_पढ़ोlock;
	अचिन्हित पूर्णांक		nr_trylock;

	/* these बार are in nano sec. */
	u64                     avg_रुको_समय;
	u64			रुको_समय_प्रकारotal;
	u64			रुको_समय_min;
	u64			रुको_समय_max;

	पूर्णांक			discard; /* flag of blacklist */
पूर्ण;

/*
 * States of lock_seq_stat
 *
 * UNINITIALIZED is required क्रम detecting first event of acquire.
 * As the nature of lock events, there is no guarantee
 * that the first event क्रम the locks are acquire,
 * it can be acquired, contended or release.
 */
#घोषणा SEQ_STATE_UNINITIALIZED      0	       /* initial state */
#घोषणा SEQ_STATE_RELEASED	1
#घोषणा SEQ_STATE_ACQUIRING	2
#घोषणा SEQ_STATE_ACQUIRED	3
#घोषणा SEQ_STATE_READ_ACQUIRED	4
#घोषणा SEQ_STATE_CONTENDED	5

/*
 * MAX_LOCK_DEPTH
 * Imported from include/linux/sched.h.
 * Should this be synchronized?
 */
#घोषणा MAX_LOCK_DEPTH 48

/*
 * काष्ठा lock_seq_stat:
 * Place to put on state of one lock sequence
 * 1) acquire -> acquired -> release
 * 2) acquire -> contended -> acquired -> release
 * 3) acquire (with पढ़ो or try) -> release
 * 4) Are there other patterns?
 */
काष्ठा lock_seq_stat अणु
	काष्ठा list_head        list;
	पूर्णांक			state;
	u64			prev_event_समय;
	व्योम                    *addr;

	पूर्णांक                     पढ़ो_count;
पूर्ण;

काष्ठा thपढ़ो_stat अणु
	काष्ठा rb_node		rb;

	u32                     tid;
	काष्ठा list_head        seq_list;
पूर्ण;

अटल काष्ठा rb_root		thपढ़ो_stats;

अटल काष्ठा thपढ़ो_stat *thपढ़ो_stat_find(u32 tid)
अणु
	काष्ठा rb_node *node;
	काष्ठा thपढ़ो_stat *st;

	node = thपढ़ो_stats.rb_node;
	जबतक (node) अणु
		st = container_of(node, काष्ठा thपढ़ो_stat, rb);
		अगर (st->tid == tid)
			वापस st;
		अन्यथा अगर (tid < st->tid)
			node = node->rb_left;
		अन्यथा
			node = node->rb_right;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम thपढ़ो_stat_insert(काष्ठा thपढ़ो_stat *new)
अणु
	काष्ठा rb_node **rb = &thपढ़ो_stats.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा thपढ़ो_stat *p;

	जबतक (*rb) अणु
		p = container_of(*rb, काष्ठा thपढ़ो_stat, rb);
		parent = *rb;

		अगर (new->tid < p->tid)
			rb = &(*rb)->rb_left;
		अन्यथा अगर (new->tid > p->tid)
			rb = &(*rb)->rb_right;
		अन्यथा
			BUG_ON("inserting invalid thread_stat\n");
	पूर्ण

	rb_link_node(&new->rb, parent, rb);
	rb_insert_color(&new->rb, &thपढ़ो_stats);
पूर्ण

अटल काष्ठा thपढ़ो_stat *thपढ़ो_stat_findnew_after_first(u32 tid)
अणु
	काष्ठा thपढ़ो_stat *st;

	st = thपढ़ो_stat_find(tid);
	अगर (st)
		वापस st;

	st = zalloc(माप(काष्ठा thपढ़ो_stat));
	अगर (!st) अणु
		pr_err("memory allocation failed\n");
		वापस शून्य;
	पूर्ण

	st->tid = tid;
	INIT_LIST_HEAD(&st->seq_list);

	thपढ़ो_stat_insert(st);

	वापस st;
पूर्ण

अटल काष्ठा thपढ़ो_stat *thपढ़ो_stat_findnew_first(u32 tid);
अटल काष्ठा thपढ़ो_stat *(*thपढ़ो_stat_findnew)(u32 tid) =
	thपढ़ो_stat_findnew_first;

अटल काष्ठा thपढ़ो_stat *thपढ़ो_stat_findnew_first(u32 tid)
अणु
	काष्ठा thपढ़ो_stat *st;

	st = zalloc(माप(काष्ठा thपढ़ो_stat));
	अगर (!st) अणु
		pr_err("memory allocation failed\n");
		वापस शून्य;
	पूर्ण
	st->tid = tid;
	INIT_LIST_HEAD(&st->seq_list);

	rb_link_node(&st->rb, शून्य, &thपढ़ो_stats.rb_node);
	rb_insert_color(&st->rb, &thपढ़ो_stats);

	thपढ़ो_stat_findnew = thपढ़ो_stat_findnew_after_first;
	वापस st;
पूर्ण

/* build simple key function one is bigger than two */
#घोषणा SINGLE_KEY(member)						\
	अटल पूर्णांक lock_stat_key_ ## member(काष्ठा lock_stat *one,	\
					 काष्ठा lock_stat *two)		\
	अणु								\
		वापस one->member > two->member;			\
	पूर्ण

SINGLE_KEY(nr_acquired)
SINGLE_KEY(nr_contended)
SINGLE_KEY(avg_रुको_समय)
SINGLE_KEY(रुको_समय_प्रकारotal)
SINGLE_KEY(रुको_समय_max)

अटल पूर्णांक lock_stat_key_रुको_समय_min(काष्ठा lock_stat *one,
					काष्ठा lock_stat *two)
अणु
	u64 s1 = one->रुको_समय_min;
	u64 s2 = two->रुको_समय_min;
	अगर (s1 == ULदीर्घ_उच्च)
		s1 = 0;
	अगर (s2 == ULदीर्घ_उच्च)
		s2 = 0;
	वापस s1 > s2;
पूर्ण

काष्ठा lock_key अणु
	/*
	 * name: the value क्रम specअगरy by user
	 * this should be simpler than raw name of member
	 * e.g. nr_acquired -> acquired, रुको_समय_प्रकारotal -> रुको_total
	 */
	स्थिर अक्षर		*name;
	पूर्णांक			(*key)(काष्ठा lock_stat*, काष्ठा lock_stat*);
पूर्ण;

अटल स्थिर अक्षर		*sort_key = "acquired";

अटल पूर्णांक			(*compare)(काष्ठा lock_stat *, काष्ठा lock_stat *);

अटल काष्ठा rb_root		result;	/* place to store sorted data */

#घोषणा DEF_KEY_LOCK(name, fn_suffix)	\
	अणु #name, lock_stat_key_ ## fn_suffix पूर्ण
काष्ठा lock_key keys[] = अणु
	DEF_KEY_LOCK(acquired, nr_acquired),
	DEF_KEY_LOCK(contended, nr_contended),
	DEF_KEY_LOCK(avg_रुको, avg_रुको_समय),
	DEF_KEY_LOCK(रुको_total, रुको_समय_प्रकारotal),
	DEF_KEY_LOCK(रुको_min, रुको_समय_min),
	DEF_KEY_LOCK(रुको_max, रुको_समय_max),

	/* extra comparisons much complicated should be here */

	अणु शून्य, शून्य पूर्ण
पूर्ण;

अटल पूर्णांक select_key(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; keys[i].name; i++) अणु
		अगर (!म_भेद(keys[i].name, sort_key)) अणु
			compare = keys[i].key;
			वापस 0;
		पूर्ण
	पूर्ण

	pr_err("Unknown compare key: %s\n", sort_key);

	वापस -1;
पूर्ण

अटल व्योम insert_to_result(काष्ठा lock_stat *st,
			     पूर्णांक (*bigger)(काष्ठा lock_stat *, काष्ठा lock_stat *))
अणु
	काष्ठा rb_node **rb = &result.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा lock_stat *p;

	जबतक (*rb) अणु
		p = container_of(*rb, काष्ठा lock_stat, rb);
		parent = *rb;

		अगर (bigger(st, p))
			rb = &(*rb)->rb_left;
		अन्यथा
			rb = &(*rb)->rb_right;
	पूर्ण

	rb_link_node(&st->rb, parent, rb);
	rb_insert_color(&st->rb, &result);
पूर्ण

/* वापसs left most element of result, and erase it */
अटल काष्ठा lock_stat *pop_from_result(व्योम)
अणु
	काष्ठा rb_node *node = result.rb_node;

	अगर (!node)
		वापस शून्य;

	जबतक (node->rb_left)
		node = node->rb_left;

	rb_erase(node, &result);
	वापस container_of(node, काष्ठा lock_stat, rb);
पूर्ण

अटल काष्ठा lock_stat *lock_stat_findnew(व्योम *addr, स्थिर अक्षर *name)
अणु
	काष्ठा list_head *entry = lockhashentry(addr);
	काष्ठा lock_stat *ret, *new;

	list_क्रम_each_entry(ret, entry, hash_entry) अणु
		अगर (ret->addr == addr)
			वापस ret;
	पूर्ण

	new = zalloc(माप(काष्ठा lock_stat));
	अगर (!new)
		जाओ alloc_failed;

	new->addr = addr;
	new->name = zalloc(माप(अक्षर) * म_माप(name) + 1);
	अगर (!new->name) अणु
		मुक्त(new);
		जाओ alloc_failed;
	पूर्ण

	म_नकल(new->name, name);
	new->रुको_समय_min = ULदीर्घ_उच्च;

	list_add(&new->hash_entry, entry);
	वापस new;

alloc_failed:
	pr_err("memory allocation failed\n");
	वापस शून्य;
पूर्ण

काष्ठा trace_lock_handler अणु
	पूर्णांक (*acquire_event)(काष्ठा evsel *evsel,
			     काष्ठा perf_sample *sample);

	पूर्णांक (*acquired_event)(काष्ठा evsel *evsel,
			      काष्ठा perf_sample *sample);

	पूर्णांक (*contended_event)(काष्ठा evsel *evsel,
			       काष्ठा perf_sample *sample);

	पूर्णांक (*release_event)(काष्ठा evsel *evsel,
			     काष्ठा perf_sample *sample);
पूर्ण;

अटल काष्ठा lock_seq_stat *get_seq(काष्ठा thपढ़ो_stat *ts, व्योम *addr)
अणु
	काष्ठा lock_seq_stat *seq;

	list_क्रम_each_entry(seq, &ts->seq_list, list) अणु
		अगर (seq->addr == addr)
			वापस seq;
	पूर्ण

	seq = zalloc(माप(काष्ठा lock_seq_stat));
	अगर (!seq) अणु
		pr_err("memory allocation failed\n");
		वापस शून्य;
	पूर्ण
	seq->state = SEQ_STATE_UNINITIALIZED;
	seq->addr = addr;

	list_add(&seq->list, &ts->seq_list);
	वापस seq;
पूर्ण

क्रमागत broken_state अणु
	BROKEN_ACQUIRE,
	BROKEN_ACQUIRED,
	BROKEN_CONTENDED,
	BROKEN_RELEASE,
	BROKEN_MAX,
पूर्ण;

अटल पूर्णांक bad_hist[BROKEN_MAX];

क्रमागत acquire_flags अणु
	TRY_LOCK = 1,
	READ_LOCK = 2,
पूर्ण;

अटल पूर्णांक report_lock_acquire_event(काष्ठा evsel *evsel,
				     काष्ठा perf_sample *sample)
अणु
	व्योम *addr;
	काष्ठा lock_stat *ls;
	काष्ठा thपढ़ो_stat *ts;
	काष्ठा lock_seq_stat *seq;
	स्थिर अक्षर *name = evsel__strval(evsel, sample, "name");
	u64 पंचांगp	 = evsel__पूर्णांकval(evsel, sample, "lockdep_addr");
	पूर्णांक flag = evsel__पूर्णांकval(evsel, sample, "flags");

	स_नकल(&addr, &पंचांगp, माप(व्योम *));

	ls = lock_stat_findnew(addr, name);
	अगर (!ls)
		वापस -ENOMEM;
	अगर (ls->discard)
		वापस 0;

	ts = thपढ़ो_stat_findnew(sample->tid);
	अगर (!ts)
		वापस -ENOMEM;

	seq = get_seq(ts, addr);
	अगर (!seq)
		वापस -ENOMEM;

	चयन (seq->state) अणु
	हाल SEQ_STATE_UNINITIALIZED:
	हाल SEQ_STATE_RELEASED:
		अगर (!flag) अणु
			seq->state = SEQ_STATE_ACQUIRING;
		पूर्ण अन्यथा अणु
			अगर (flag & TRY_LOCK)
				ls->nr_trylock++;
			अगर (flag & READ_LOCK)
				ls->nr_पढ़ोlock++;
			seq->state = SEQ_STATE_READ_ACQUIRED;
			seq->पढ़ो_count = 1;
			ls->nr_acquired++;
		पूर्ण
		अवरोध;
	हाल SEQ_STATE_READ_ACQUIRED:
		अगर (flag & READ_LOCK) अणु
			seq->पढ़ो_count++;
			ls->nr_acquired++;
			जाओ end;
		पूर्ण अन्यथा अणु
			जाओ broken;
		पूर्ण
		अवरोध;
	हाल SEQ_STATE_ACQUIRED:
	हाल SEQ_STATE_ACQUIRING:
	हाल SEQ_STATE_CONTENDED:
broken:
		/* broken lock sequence, discard it */
		ls->discard = 1;
		bad_hist[BROKEN_ACQUIRE]++;
		list_del_init(&seq->list);
		मुक्त(seq);
		जाओ end;
	शेष:
		BUG_ON("Unknown state of lock sequence found!\n");
		अवरोध;
	पूर्ण

	ls->nr_acquire++;
	seq->prev_event_समय = sample->समय;
end:
	वापस 0;
पूर्ण

अटल पूर्णांक report_lock_acquired_event(काष्ठा evsel *evsel,
				      काष्ठा perf_sample *sample)
अणु
	व्योम *addr;
	काष्ठा lock_stat *ls;
	काष्ठा thपढ़ो_stat *ts;
	काष्ठा lock_seq_stat *seq;
	u64 contended_term;
	स्थिर अक्षर *name = evsel__strval(evsel, sample, "name");
	u64 पंचांगp = evsel__पूर्णांकval(evsel, sample, "lockdep_addr");

	स_नकल(&addr, &पंचांगp, माप(व्योम *));

	ls = lock_stat_findnew(addr, name);
	अगर (!ls)
		वापस -ENOMEM;
	अगर (ls->discard)
		वापस 0;

	ts = thपढ़ो_stat_findnew(sample->tid);
	अगर (!ts)
		वापस -ENOMEM;

	seq = get_seq(ts, addr);
	अगर (!seq)
		वापस -ENOMEM;

	चयन (seq->state) अणु
	हाल SEQ_STATE_UNINITIALIZED:
		/* orphan event, करो nothing */
		वापस 0;
	हाल SEQ_STATE_ACQUIRING:
		अवरोध;
	हाल SEQ_STATE_CONTENDED:
		contended_term = sample->समय - seq->prev_event_समय;
		ls->रुको_समय_प्रकारotal += contended_term;
		अगर (contended_term < ls->रुको_समय_min)
			ls->रुको_समय_min = contended_term;
		अगर (ls->रुको_समय_max < contended_term)
			ls->रुको_समय_max = contended_term;
		अवरोध;
	हाल SEQ_STATE_RELEASED:
	हाल SEQ_STATE_ACQUIRED:
	हाल SEQ_STATE_READ_ACQUIRED:
		/* broken lock sequence, discard it */
		ls->discard = 1;
		bad_hist[BROKEN_ACQUIRED]++;
		list_del_init(&seq->list);
		मुक्त(seq);
		जाओ end;
	शेष:
		BUG_ON("Unknown state of lock sequence found!\n");
		अवरोध;
	पूर्ण

	seq->state = SEQ_STATE_ACQUIRED;
	ls->nr_acquired++;
	ls->avg_रुको_समय = ls->nr_contended ? ls->रुको_समय_प्रकारotal/ls->nr_contended : 0;
	seq->prev_event_समय = sample->समय;
end:
	वापस 0;
पूर्ण

अटल पूर्णांक report_lock_contended_event(काष्ठा evsel *evsel,
				       काष्ठा perf_sample *sample)
अणु
	व्योम *addr;
	काष्ठा lock_stat *ls;
	काष्ठा thपढ़ो_stat *ts;
	काष्ठा lock_seq_stat *seq;
	स्थिर अक्षर *name = evsel__strval(evsel, sample, "name");
	u64 पंचांगp = evsel__पूर्णांकval(evsel, sample, "lockdep_addr");

	स_नकल(&addr, &पंचांगp, माप(व्योम *));

	ls = lock_stat_findnew(addr, name);
	अगर (!ls)
		वापस -ENOMEM;
	अगर (ls->discard)
		वापस 0;

	ts = thपढ़ो_stat_findnew(sample->tid);
	अगर (!ts)
		वापस -ENOMEM;

	seq = get_seq(ts, addr);
	अगर (!seq)
		वापस -ENOMEM;

	चयन (seq->state) अणु
	हाल SEQ_STATE_UNINITIALIZED:
		/* orphan event, करो nothing */
		वापस 0;
	हाल SEQ_STATE_ACQUIRING:
		अवरोध;
	हाल SEQ_STATE_RELEASED:
	हाल SEQ_STATE_ACQUIRED:
	हाल SEQ_STATE_READ_ACQUIRED:
	हाल SEQ_STATE_CONTENDED:
		/* broken lock sequence, discard it */
		ls->discard = 1;
		bad_hist[BROKEN_CONTENDED]++;
		list_del_init(&seq->list);
		मुक्त(seq);
		जाओ end;
	शेष:
		BUG_ON("Unknown state of lock sequence found!\n");
		अवरोध;
	पूर्ण

	seq->state = SEQ_STATE_CONTENDED;
	ls->nr_contended++;
	ls->avg_रुको_समय = ls->रुको_समय_प्रकारotal/ls->nr_contended;
	seq->prev_event_समय = sample->समय;
end:
	वापस 0;
पूर्ण

अटल पूर्णांक report_lock_release_event(काष्ठा evsel *evsel,
				     काष्ठा perf_sample *sample)
अणु
	व्योम *addr;
	काष्ठा lock_stat *ls;
	काष्ठा thपढ़ो_stat *ts;
	काष्ठा lock_seq_stat *seq;
	स्थिर अक्षर *name = evsel__strval(evsel, sample, "name");
	u64 पंचांगp = evsel__पूर्णांकval(evsel, sample, "lockdep_addr");

	स_नकल(&addr, &पंचांगp, माप(व्योम *));

	ls = lock_stat_findnew(addr, name);
	अगर (!ls)
		वापस -ENOMEM;
	अगर (ls->discard)
		वापस 0;

	ts = thपढ़ो_stat_findnew(sample->tid);
	अगर (!ts)
		वापस -ENOMEM;

	seq = get_seq(ts, addr);
	अगर (!seq)
		वापस -ENOMEM;

	चयन (seq->state) अणु
	हाल SEQ_STATE_UNINITIALIZED:
		जाओ end;
	हाल SEQ_STATE_ACQUIRED:
		अवरोध;
	हाल SEQ_STATE_READ_ACQUIRED:
		seq->पढ़ो_count--;
		BUG_ON(seq->पढ़ो_count < 0);
		अगर (seq->पढ़ो_count) अणु
			ls->nr_release++;
			जाओ end;
		पूर्ण
		अवरोध;
	हाल SEQ_STATE_ACQUIRING:
	हाल SEQ_STATE_CONTENDED:
	हाल SEQ_STATE_RELEASED:
		/* broken lock sequence, discard it */
		ls->discard = 1;
		bad_hist[BROKEN_RELEASE]++;
		जाओ मुक्त_seq;
	शेष:
		BUG_ON("Unknown state of lock sequence found!\n");
		अवरोध;
	पूर्ण

	ls->nr_release++;
मुक्त_seq:
	list_del_init(&seq->list);
	मुक्त(seq);
end:
	वापस 0;
पूर्ण

/* lock oriented handlers */
/* TODO: handlers क्रम CPU oriented, thपढ़ो oriented */
अटल काष्ठा trace_lock_handler report_lock_ops  = अणु
	.acquire_event		= report_lock_acquire_event,
	.acquired_event		= report_lock_acquired_event,
	.contended_event	= report_lock_contended_event,
	.release_event		= report_lock_release_event,
पूर्ण;

अटल काष्ठा trace_lock_handler *trace_handler;

अटल पूर्णांक evsel__process_lock_acquire(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	अगर (trace_handler->acquire_event)
		वापस trace_handler->acquire_event(evsel, sample);
	वापस 0;
पूर्ण

अटल पूर्णांक evsel__process_lock_acquired(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	अगर (trace_handler->acquired_event)
		वापस trace_handler->acquired_event(evsel, sample);
	वापस 0;
पूर्ण

अटल पूर्णांक evsel__process_lock_contended(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	अगर (trace_handler->contended_event)
		वापस trace_handler->contended_event(evsel, sample);
	वापस 0;
पूर्ण

अटल पूर्णांक evsel__process_lock_release(काष्ठा evsel *evsel, काष्ठा perf_sample *sample)
अणु
	अगर (trace_handler->release_event)
		वापस trace_handler->release_event(evsel, sample);
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_bad_events(पूर्णांक bad, पूर्णांक total)
अणु
	/* Output क्रम debug, this have to be हटाओd */
	पूर्णांक i;
	स्थिर अक्षर *name[4] =
		अणु "acquire", "acquired", "contended", "release" पूर्ण;

	pr_info("\n=== output for debug===\n\n");
	pr_info("bad: %d, total: %d\n", bad, total);
	pr_info("bad rate: %.2f %%\n", (द्विगुन)bad / (द्विगुन)total * 100);
	pr_info("histogram of events caused bad sequence\n");
	क्रम (i = 0; i < BROKEN_MAX; i++)
		pr_info(" %10s: %d\n", name[i], bad_hist[i]);
पूर्ण

/* TODO: various way to prपूर्णांक, coloring, nano or milli sec */
अटल व्योम prपूर्णांक_result(व्योम)
अणु
	काष्ठा lock_stat *st;
	अक्षर cut_name[20];
	पूर्णांक bad, total;

	pr_info("%20s ", "Name");
	pr_info("%10s ", "acquired");
	pr_info("%10s ", "contended");

	pr_info("%15s ", "avg wait (ns)");
	pr_info("%15s ", "total wait (ns)");
	pr_info("%15s ", "max wait (ns)");
	pr_info("%15s ", "min wait (ns)");

	pr_info("\n\n");

	bad = total = 0;
	जबतक ((st = pop_from_result())) अणु
		total++;
		अगर (st->discard) अणु
			bad++;
			जारी;
		पूर्ण
		bzero(cut_name, 20);

		अगर (म_माप(st->name) < 16) अणु
			/* output raw name */
			pr_info("%20s ", st->name);
		पूर्ण अन्यथा अणु
			म_नकलन(cut_name, st->name, 16);
			cut_name[16] = '.';
			cut_name[17] = '.';
			cut_name[18] = '.';
			cut_name[19] = '\0';
			/* cut off name क्रम saving output style */
			pr_info("%20s ", cut_name);
		पूर्ण

		pr_info("%10u ", st->nr_acquired);
		pr_info("%10u ", st->nr_contended);

		pr_info("%15" PRIu64 " ", st->avg_रुको_समय);
		pr_info("%15" PRIu64 " ", st->रुको_समय_प्रकारotal);
		pr_info("%15" PRIu64 " ", st->रुको_समय_max);
		pr_info("%15" PRIu64 " ", st->रुको_समय_min == ULदीर्घ_उच्च ?
		       0 : st->रुको_समय_min);
		pr_info("\n");
	पूर्ण

	prपूर्णांक_bad_events(bad, total);
पूर्ण

अटल bool info_thपढ़ोs, info_map;

अटल व्योम dump_thपढ़ोs(व्योम)
अणु
	काष्ठा thपढ़ो_stat *st;
	काष्ठा rb_node *node;
	काष्ठा thपढ़ो *t;

	pr_info("%10s: comm\n", "Thread ID");

	node = rb_first(&thपढ़ो_stats);
	जबतक (node) अणु
		st = container_of(node, काष्ठा thपढ़ो_stat, rb);
		t = perf_session__findnew(session, st->tid);
		pr_info("%10d: %s\n", st->tid, thपढ़ो__comm_str(t));
		node = rb_next(node);
		thपढ़ो__put(t);
	पूर्ण
पूर्ण

अटल व्योम dump_map(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा lock_stat *st;

	pr_info("Address of instance: name of class\n");
	क्रम (i = 0; i < LOCKHASH_SIZE; i++) अणु
		list_क्रम_each_entry(st, &lockhash_table[i], hash_entry) अणु
			pr_info(" %p: %s\n", st->addr, st->name);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dump_info(व्योम)
अणु
	पूर्णांक rc = 0;

	अगर (info_thपढ़ोs)
		dump_thपढ़ोs();
	अन्यथा अगर (info_map)
		dump_map();
	अन्यथा अणु
		rc = -1;
		pr_err("Unknown type of information\n");
	पूर्ण

	वापस rc;
पूर्ण

प्रकार पूर्णांक (*tracepoपूर्णांक_handler)(काष्ठा evsel *evsel,
				  काष्ठा perf_sample *sample);

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool __maybe_unused,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	पूर्णांक err = 0;
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid,
							sample->tid);

	अगर (thपढ़ो == शून्य) अणु
		pr_debug("problem processing %d event, skipping it.\n",
			event->header.type);
		वापस -1;
	पूर्ण

	अगर (evsel->handler != शून्य) अणु
		tracepoपूर्णांक_handler f = evsel->handler;
		err = f(evsel, sample);
	पूर्ण

	thपढ़ो__put(thपढ़ो);

	वापस err;
पूर्ण

अटल व्योम sort_result(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा lock_stat *st;

	क्रम (i = 0; i < LOCKHASH_SIZE; i++) अणु
		list_क्रम_each_entry(st, &lockhash_table[i], hash_entry) अणु
			insert_to_result(st, compare);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा evsel_str_handler lock_tracepoपूर्णांकs[] = अणु
	अणु "lock:lock_acquire",	 evsel__process_lock_acquire,   पूर्ण, /* CONFIG_LOCKDEP */
	अणु "lock:lock_acquired",	 evsel__process_lock_acquired,  पूर्ण, /* CONFIG_LOCKDEP, CONFIG_LOCK_STAT */
	अणु "lock:lock_contended", evsel__process_lock_contended, पूर्ण, /* CONFIG_LOCKDEP, CONFIG_LOCK_STAT */
	अणु "lock:lock_release",	 evsel__process_lock_release,   पूर्ण, /* CONFIG_LOCKDEP */
पूर्ण;

अटल bool क्रमce;

अटल पूर्णांक __cmd_report(bool display_info)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा perf_tool eops = अणु
		.sample		 = process_sample_event,
		.comm		 = perf_event__process_comm,
		.namespaces	 = perf_event__process_namespaces,
		.ordered_events	 = true,
	पूर्ण;
	काष्ठा perf_data data = अणु
		.path  = input_name,
		.mode  = PERF_DATA_MODE_READ,
		.क्रमce = क्रमce,
	पूर्ण;

	session = perf_session__new(&data, false, &eops);
	अगर (IS_ERR(session)) अणु
		pr_err("Initializing perf session failed\n");
		वापस PTR_ERR(session);
	पूर्ण

	symbol__init(&session->header.env);

	अगर (!perf_session__has_traces(session, "lock record"))
		जाओ out_delete;

	अगर (perf_session__set_tracepoपूर्णांकs_handlers(session, lock_tracepoपूर्णांकs)) अणु
		pr_err("Initializing perf session tracepoint handlers failed\n");
		जाओ out_delete;
	पूर्ण

	अगर (select_key())
		जाओ out_delete;

	err = perf_session__process_events(session);
	अगर (err)
		जाओ out_delete;

	setup_pager();
	अगर (display_info) /* used क्रम info subcommand */
		err = dump_info();
	अन्यथा अणु
		sort_result();
		prपूर्णांक_result();
	पूर्ण

out_delete:
	perf_session__delete(session);
	वापस err;
पूर्ण

अटल पूर्णांक __cmd_record(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *record_args[] = अणु
		"record", "-R", "-m", "1024", "-c", "1",
	पूर्ण;
	अचिन्हित पूर्णांक rec_argc, i, j, ret;
	स्थिर अक्षर **rec_argv;

	क्रम (i = 0; i < ARRAY_SIZE(lock_tracepoपूर्णांकs); i++) अणु
		अगर (!is_valid_tracepoपूर्णांक(lock_tracepoपूर्णांकs[i].name)) अणु
				pr_err("tracepoint %s is not enabled. "
				       "Are CONFIG_LOCKDEP and CONFIG_LOCK_STAT enabled?\n",
				       lock_tracepoपूर्णांकs[i].name);
				वापस 1;
		पूर्ण
	पूर्ण

	rec_argc = ARRAY_SIZE(record_args) + argc - 1;
	/* factor of 2 is क्रम -e in front of each tracepoपूर्णांक */
	rec_argc += 2 * ARRAY_SIZE(lock_tracepoपूर्णांकs);

	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));
	अगर (!rec_argv)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(record_args); i++)
		rec_argv[i] = strdup(record_args[i]);

	क्रम (j = 0; j < ARRAY_SIZE(lock_tracepoपूर्णांकs); j++) अणु
		rec_argv[i++] = "-e";
		rec_argv[i++] = strdup(lock_tracepoपूर्णांकs[j].name);
	पूर्ण

	क्रम (j = 1; j < (अचिन्हित पूर्णांक)argc; j++, i++)
		rec_argv[i] = argv[j];

	BUG_ON(i != rec_argc);

	ret = cmd_record(i, rec_argv);
	मुक्त(rec_argv);
	वापस ret;
पूर्ण

पूर्णांक cmd_lock(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर काष्ठा option lock_options[] = अणु
	OPT_STRING('i', "input", &input_name, "file", "input file name"),
	OPT_INCR('v', "verbose", &verbose, "be more verbose (show symbol address, etc)"),
	OPT_BOOLEAN('D', "dump-raw-trace", &dump_trace, "dump raw trace in ASCII"),
	OPT_BOOLEAN('f', "force", &force, "don't complain, करो it"),
	OPT_END()
	पूर्ण;

	स्थिर काष्ठा option info_options[] = अणु
	OPT_BOOLEAN('t', "threads", &info_thपढ़ोs,
		    "dump thread list in perf.data"),
	OPT_BOOLEAN('m', "map", &info_map,
		    "map of lock instances (address:name table)"),
	OPT_PARENT(lock_options)
	पूर्ण;

	स्थिर काष्ठा option report_options[] = अणु
	OPT_STRING('k', "key", &sort_key, "acquired",
		    "key for sorting (acquired / contended / avg_wait / wait_total / wait_max / wait_min)"),
	/* TODO: type */
	OPT_PARENT(lock_options)
	पूर्ण;

	स्थिर अक्षर * स्थिर info_usage[] = अणु
		"perf lock info [<options>]",
		शून्य
	पूर्ण;
	स्थिर अक्षर *स्थिर lock_subcommands[] = अणु "record", "report", "script",
						 "info", शून्य पूर्ण;
	स्थिर अक्षर *lock_usage[] = अणु
		शून्य,
		शून्य
	पूर्ण;
	स्थिर अक्षर * स्थिर report_usage[] = अणु
		"perf lock report [<options>]",
		शून्य
	पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;

	क्रम (i = 0; i < LOCKHASH_SIZE; i++)
		INIT_LIST_HEAD(lockhash_table + i);

	argc = parse_options_subcommand(argc, argv, lock_options, lock_subcommands,
					lock_usage, PARSE_OPT_STOP_AT_NON_OPTION);
	अगर (!argc)
		usage_with_options(lock_usage, lock_options);

	अगर (!म_भेदन(argv[0], "rec", 3)) अणु
		वापस __cmd_record(argc, argv);
	पूर्ण अन्यथा अगर (!म_भेदन(argv[0], "report", 6)) अणु
		trace_handler = &report_lock_ops;
		अगर (argc) अणु
			argc = parse_options(argc, argv,
					     report_options, report_usage, 0);
			अगर (argc)
				usage_with_options(report_usage, report_options);
		पूर्ण
		rc = __cmd_report(false);
	पूर्ण अन्यथा अगर (!म_भेद(argv[0], "script")) अणु
		/* Aliased to 'perf script' */
		वापस cmd_script(argc, argv);
	पूर्ण अन्यथा अगर (!म_भेद(argv[0], "info")) अणु
		अगर (argc) अणु
			argc = parse_options(argc, argv,
					     info_options, info_usage, 0);
			अगर (argc)
				usage_with_options(info_usage, info_options);
		पूर्ण
		/* recycling report_lock_ops */
		trace_handler = &report_lock_ops;
		rc = __cmd_report(true);
	पूर्ण अन्यथा अणु
		usage_with_options(lock_usage, lock_options);
	पूर्ण

	वापस rc;
पूर्ण
