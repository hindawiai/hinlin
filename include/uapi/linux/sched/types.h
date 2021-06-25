<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SCHED_TYPES_H
#घोषणा _UAPI_LINUX_SCHED_TYPES_H

#समावेश <linux/types.h>

काष्ठा sched_param अणु
	पूर्णांक sched_priority;
पूर्ण;

#घोषणा SCHED_ATTR_SIZE_VER0	48	/* माप first published काष्ठा */
#घोषणा SCHED_ATTR_SIZE_VER1	56	/* add: util_अणुmin,maxपूर्ण */

/*
 * Extended scheduling parameters data काष्ठाure.
 *
 * This is needed because the original काष्ठा sched_param can not be
 * altered without पूर्णांकroducing ABI issues with legacy applications
 * (e.g., in sched_getparam()).
 *
 * However, the possibility of specअगरying more than just a priority क्रम
 * the tasks may be useful क्रम a wide variety of application fields, e.g.,
 * mulसमयdia, streaming, स्वतःmation and control, and many others.
 *
 * This variant (sched_attr) allows to define additional attributes to
 * improve the scheduler knowledge about task requirements.
 *
 * Scheduling Class Attributes
 * ===========================
 *
 * A subset of sched_attr attributes specअगरies the
 * scheduling policy and relative POSIX attributes:
 *
 *  @size		size of the काष्ठाure, क्रम fwd/bwd compat.
 *
 *  @sched_policy	task's scheduling policy
 *  @sched_nice		task's nice value      (SCHED_NORMAL/BATCH)
 *  @sched_priority	task's अटल priority (SCHED_FIFO/RR)
 *
 * Certain more advanced scheduling features can be controlled by a
 * predefined set of flags via the attribute:
 *
 *  @sched_flags	क्रम customizing the scheduler behaviour
 *
 * Sporadic Time-Constrained Task Attributes
 * =========================================
 *
 * A subset of sched_attr attributes allows to describe a so-called
 * sporadic समय-स्थिरrained task.
 *
 * In such a model a task is specअगरied by:
 *  - the activation period or minimum instance पूर्णांकer-arrival समय;
 *  - the maximum (or average, depending on the actual scheduling
 *    discipline) computation समय of all instances, a.k.a. runसमय;
 *  - the deadline (relative to the actual activation समय) of each
 *    instance.
 * Very briefly, a periodic (sporadic) task asks क्रम the execution of
 * some specअगरic computation --which is typically called an instance--
 * (at most) every period. Moreover, each instance typically lasts no more
 * than the runसमय and must be completed by समय instant t equal to
 * the instance activation समय + the deadline.
 *
 * This is reflected by the following fields of the sched_attr काष्ठाure:
 *
 *  @sched_deadline	representative of the task's deadline
 *  @sched_runसमय	representative of the task's runसमय
 *  @sched_period	representative of the task's period
 *
 * Given this task model, there are a multiplicity of scheduling algorithms
 * and policies, that can be used to ensure all the tasks will make their
 * timing स्थिरraपूर्णांकs.
 *
 * As of now, the SCHED_DEADLINE policy (sched_dl scheduling class) is the
 * only user of this new पूर्णांकerface. More inक्रमmation about the algorithm
 * available in the scheduling class file or in Documentation/.
 *
 * Task Utilization Attributes
 * ===========================
 *
 * A subset of sched_attr attributes allows to specअगरy the utilization
 * expected क्रम a task. These attributes allow to inक्रमm the scheduler about
 * the utilization boundaries within which it should schedule the task. These
 * boundaries are valuable hपूर्णांकs to support scheduler decisions on both task
 * placement and frequency selection.
 *
 *  @sched_util_min	represents the minimum utilization
 *  @sched_util_max	represents the maximum utilization
 *
 * Utilization is a value in the range [0..SCHED_CAPACITY_SCALE]. It
 * represents the percentage of CPU समय used by a task when running at the
 * maximum frequency on the highest capacity CPU of the प्रणाली. For example, a
 * 20% utilization task is a task running क्रम 2ms every 10ms at maximum
 * frequency.
 *
 * A task with a min utilization value bigger than 0 is more likely scheduled
 * on a CPU with a capacity big enough to fit the specअगरied value.
 * A task with a max utilization value smaller than 1024 is more likely
 * scheduled on a CPU with no more capacity than the specअगरied value.
 *
 * A task utilization boundary can be reset by setting the attribute to -1.
 */
काष्ठा sched_attr अणु
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE */
	__u64 sched_runसमय;
	__u64 sched_deadline;
	__u64 sched_period;

	/* Utilization hपूर्णांकs */
	__u32 sched_util_min;
	__u32 sched_util_max;

पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_SCHED_TYPES_H */
