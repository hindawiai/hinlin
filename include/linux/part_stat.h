<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PART_STAT_H
#घोषणा _LINUX_PART_STAT_H

#समावेश <linux/genhd.h>

काष्ठा disk_stats अणु
	u64 nsecs[NR_STAT_GROUPS];
	अचिन्हित दीर्घ sectors[NR_STAT_GROUPS];
	अचिन्हित दीर्घ ios[NR_STAT_GROUPS];
	अचिन्हित दीर्घ merges[NR_STAT_GROUPS];
	अचिन्हित दीर्घ io_ticks;
	local_t in_flight[2];
पूर्ण;

/*
 * Macros to operate on percpu disk statistics:
 *
 * अणुdisk|part|allपूर्ण_stat_अणुadd|sub|inc|decपूर्ण() modअगरy the stat counters and should
 * be called between disk_stat_lock() and disk_stat_unlock().
 *
 * part_stat_पढ़ो() can be called at any समय.
 */
#घोषणा part_stat_lock()	preempt_disable()
#घोषणा part_stat_unlock()	preempt_enable()

#घोषणा part_stat_get_cpu(part, field, cpu)				\
	(per_cpu_ptr((part)->bd_stats, (cpu))->field)

#घोषणा part_stat_get(part, field)					\
	part_stat_get_cpu(part, field, smp_processor_id())

#घोषणा part_stat_पढ़ो(part, field)					\
(अणु									\
	typeof((part)->bd_stats->field) res = 0;			\
	अचिन्हित पूर्णांक _cpu;						\
	क्रम_each_possible_cpu(_cpu)					\
		res += per_cpu_ptr((part)->bd_stats, _cpu)->field; \
	res;								\
पूर्ण)

अटल अंतरभूत व्योम part_stat_set_all(काष्ठा block_device *part, पूर्णांक value)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i)
		स_रखो(per_cpu_ptr(part->bd_stats, i), value,
				माप(काष्ठा disk_stats));
पूर्ण

#घोषणा part_stat_पढ़ो_accum(part, field)				\
	(part_stat_पढ़ो(part, field[STAT_READ]) +			\
	 part_stat_पढ़ो(part, field[STAT_WRITE]) +			\
	 part_stat_पढ़ो(part, field[STAT_DISCARD]))

#घोषणा __part_stat_add(part, field, addnd)				\
	__this_cpu_add((part)->bd_stats->field, addnd)

#घोषणा part_stat_add(part, field, addnd)	करो अणु			\
	__part_stat_add((part), field, addnd);				\
	अगर ((part)->bd_partno)						\
		__part_stat_add(bdev_whole(part), field, addnd);	\
पूर्ण जबतक (0)

#घोषणा part_stat_dec(part, field)					\
	part_stat_add(part, field, -1)
#घोषणा part_stat_inc(part, field)					\
	part_stat_add(part, field, 1)
#घोषणा part_stat_sub(part, field, subnd)				\
	part_stat_add(part, field, -subnd)

#घोषणा part_stat_local_dec(part, field)				\
	local_dec(&(part_stat_get(part, field)))
#घोषणा part_stat_local_inc(part, field)				\
	local_inc(&(part_stat_get(part, field)))
#घोषणा part_stat_local_पढ़ो(part, field)				\
	local_पढ़ो(&(part_stat_get(part, field)))
#घोषणा part_stat_local_पढ़ो_cpu(part, field, cpu)			\
	local_पढ़ो(&(part_stat_get_cpu(part, field, cpu)))

#पूर्ण_अगर /* _LINUX_PART_STAT_H */
