<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * Authors: Waiman Long <waiman.दीर्घ@hpe.com>
 */

/*
 * Collect locking event counts
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/fs.h>

#समावेश "lock_events.h"

#अघोषित  LOCK_EVENT
#घोषणा LOCK_EVENT(name)	[LOCKEVENT_ ## name] = #name,

#घोषणा LOCK_EVENTS_सूची		"lock_event_counts"

/*
 * When CONFIG_LOCK_EVENT_COUNTS is enabled, event counts of dअगरferent
 * types of locks will be reported under the <debugfs>/lock_event_counts/
 * directory. See lock_events_list.h क्रम the list of available locking
 * events.
 *
 * Writing to the special ".reset_counts" file will reset all the above
 * locking event counts. This is a very slow operation and so should not
 * be करोne frequently.
 *
 * These event counts are implemented as per-cpu variables which are
 * summed and computed whenever the corresponding debugfs files are पढ़ो. This
 * minimizes added overhead making the counts usable even in a production
 * environment.
 */
अटल स्थिर अक्षर * स्थिर lockevent_names[lockevent_num + 1] = अणु

#समावेश "lock_events_list.h"

	[LOCKEVENT_reset_cnts] = ".reset_counts",
पूर्ण;

/*
 * Per-cpu counts
 */
DEFINE_PER_CPU(अचिन्हित दीर्घ, lockevents[lockevent_num]);

/*
 * The lockevent_पढ़ो() function can be overridden.
 */
sमाप_प्रकार __weak lockevent_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[64];
	पूर्णांक cpu, id, len;
	u64 sum = 0;

	/*
	 * Get the counter ID stored in file->f_inode->i_निजी
	 */
	id = (दीर्घ)file_inode(file)->i_निजी;

	अगर (id >= lockevent_num)
		वापस -EBADF;

	क्रम_each_possible_cpu(cpu)
		sum += per_cpu(lockevents[id], cpu);
	len = snम_लिखो(buf, माप(buf) - 1, "%llu\n", sum);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

/*
 * Function to handle ग_लिखो request
 *
 * When idx = reset_cnts, reset all the counts.
 */
अटल sमाप_प्रकार lockevent_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक cpu;

	/*
	 * Get the counter ID stored in file->f_inode->i_निजी
	 */
	अगर ((दीर्घ)file_inode(file)->i_निजी != LOCKEVENT_reset_cnts)
		वापस count;

	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक i;
		अचिन्हित दीर्घ *ptr = per_cpu_ptr(lockevents, cpu);

		क्रम (i = 0 ; i < lockevent_num; i++)
			WRITE_ONCE(ptr[i], 0);
	पूर्ण
	वापस count;
पूर्ण

/*
 * Debugfs data काष्ठाures
 */
अटल स्थिर काष्ठा file_operations fops_lockevent = अणु
	.पढ़ो = lockevent_पढ़ो,
	.ग_लिखो = lockevent_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
#समावेश <यंत्र/paravirt.h>

अटल bool __init skip_lockevent(स्थिर अक्षर *name)
अणु
	अटल पूर्णांक pv_on __initdata = -1;

	अगर (pv_on < 0)
		pv_on = !pv_is_native_spin_unlock();
	/*
	 * Skip PV qspinlock events on bare metal.
	 */
	अगर (!pv_on && !स_भेद(name, "pv_", 3))
		वापस true;
	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत bool skip_lockevent(स्थिर अक्षर *name)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Initialize debugfs क्रम the locking event counts.
 */
अटल पूर्णांक __init init_lockevent_counts(व्योम)
अणु
	काष्ठा dentry *d_counts = debugfs_create_dir(LOCK_EVENTS_सूची, शून्य);
	पूर्णांक i;

	अगर (!d_counts)
		जाओ out;

	/*
	 * Create the debugfs files
	 *
	 * As पढ़ोing from and writing to the stat files can be slow, only
	 * root is allowed to करो the पढ़ो/ग_लिखो to limit impact to प्रणाली
	 * perक्रमmance.
	 */
	क्रम (i = 0; i < lockevent_num; i++) अणु
		अगर (skip_lockevent(lockevent_names[i]))
			जारी;
		अगर (!debugfs_create_file(lockevent_names[i], 0400, d_counts,
					 (व्योम *)(दीर्घ)i, &fops_lockevent))
			जाओ fail_unकरो;
	पूर्ण

	अगर (!debugfs_create_file(lockevent_names[LOCKEVENT_reset_cnts], 0200,
				 d_counts, (व्योम *)(दीर्घ)LOCKEVENT_reset_cnts,
				 &fops_lockevent))
		जाओ fail_unकरो;

	वापस 0;
fail_unकरो:
	debugfs_हटाओ_recursive(d_counts);
out:
	pr_warn("Could not create '%s' debugfs entries\n", LOCK_EVENTS_सूची);
	वापस -ENOMEM;
पूर्ण
fs_initcall(init_lockevent_counts);
