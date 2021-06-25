<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 * Authors: Waiman Long <दीर्घman@redhat.com>
 */

#समावेश "lock_events.h"

#अगर_घोषित CONFIG_LOCK_EVENT_COUNTS
#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
/*
 * Collect pvqspinlock locking event counts
 */
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/fs.h>

#घोषणा EVENT_COUNT(ev)	lockevents[LOCKEVENT_ ## ev]

/*
 * PV specअगरic per-cpu counter
 */
अटल DEFINE_PER_CPU(u64, pv_kick_समय);

/*
 * Function to पढ़ो and वापस the PV qspinlock counts.
 *
 * The following counters are handled specially:
 * 1. pv_latency_kick
 *    Average kick latency (ns) = pv_latency_kick/pv_kick_unlock
 * 2. pv_latency_wake
 *    Average wake latency (ns) = pv_latency_wake/pv_kick_wake
 * 3. pv_hash_hops
 *    Average hops/hash = pv_hash_hops/pv_kick_unlock
 */
sमाप_प्रकार lockevent_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
		       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[64];
	पूर्णांक cpu, id, len;
	u64 sum = 0, kicks = 0;

	/*
	 * Get the counter ID stored in file->f_inode->i_निजी
	 */
	id = (दीर्घ)file_inode(file)->i_निजी;

	अगर (id >= lockevent_num)
		वापस -EBADF;

	क्रम_each_possible_cpu(cpu) अणु
		sum += per_cpu(lockevents[id], cpu);
		/*
		 * Need to sum additional counters क्रम some of them
		 */
		चयन (id) अणु

		हाल LOCKEVENT_pv_latency_kick:
		हाल LOCKEVENT_pv_hash_hops:
			kicks += per_cpu(EVENT_COUNT(pv_kick_unlock), cpu);
			अवरोध;

		हाल LOCKEVENT_pv_latency_wake:
			kicks += per_cpu(EVENT_COUNT(pv_kick_wake), cpu);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (id == LOCKEVENT_pv_hash_hops) अणु
		u64 frac = 0;

		अगर (kicks) अणु
			frac = 100ULL * करो_भाग(sum, kicks);
			frac = DIV_ROUND_CLOSEST_ULL(frac, kicks);
		पूर्ण

		/*
		 * Return a X.XX decimal number
		 */
		len = snम_लिखो(buf, माप(buf) - 1, "%llu.%02llu\n",
			       sum, frac);
	पूर्ण अन्यथा अणु
		/*
		 * Round to the nearest ns
		 */
		अगर ((id == LOCKEVENT_pv_latency_kick) ||
		    (id == LOCKEVENT_pv_latency_wake)) अणु
			अगर (kicks)
				sum = DIV_ROUND_CLOSEST_ULL(sum, kicks);
		पूर्ण
		len = snम_लिखो(buf, माप(buf) - 1, "%llu\n", sum);
	पूर्ण

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

/*
 * PV hash hop count
 */
अटल अंतरभूत व्योम lockevent_pv_hop(पूर्णांक hopcnt)
अणु
	this_cpu_add(EVENT_COUNT(pv_hash_hops), hopcnt);
पूर्ण

/*
 * Replacement function क्रम pv_kick()
 */
अटल अंतरभूत व्योम __pv_kick(पूर्णांक cpu)
अणु
	u64 start = sched_घड़ी();

	per_cpu(pv_kick_समय, cpu) = start;
	pv_kick(cpu);
	this_cpu_add(EVENT_COUNT(pv_latency_kick), sched_घड़ी() - start);
पूर्ण

/*
 * Replacement function क्रम pv_रुको()
 */
अटल अंतरभूत व्योम __pv_रुको(u8 *ptr, u8 val)
अणु
	u64 *pkick_समय = this_cpu_ptr(&pv_kick_समय);

	*pkick_समय = 0;
	pv_रुको(ptr, val);
	अगर (*pkick_समय) अणु
		this_cpu_add(EVENT_COUNT(pv_latency_wake),
			     sched_घड़ी() - *pkick_समय);
		lockevent_inc(pv_kick_wake);
	पूर्ण
पूर्ण

#घोषणा pv_kick(c)	__pv_kick(c)
#घोषणा pv_रुको(p, v)	__pv_रुको(p, v)

#पूर्ण_अगर /* CONFIG_PARAVIRT_SPINLOCKS */

#अन्यथा /* CONFIG_LOCK_EVENT_COUNTS */

अटल अंतरभूत व्योम lockevent_pv_hop(पूर्णांक hopcnt)	अणु पूर्ण

#पूर्ण_अगर /* CONFIG_LOCK_EVENT_COUNTS */
