<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * padata.h - header क्रम the padata parallelization पूर्णांकerface
 *
 * Copyright (C) 2008, 2009 secunet Security Networks AG
 * Copyright (C) 2008, 2009 Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 *
 * Copyright (c) 2020 Oracle and/or its affiliates.
 * Author: Daniel Jordan <daniel.m.jordan@oracle.com>
 */

#अगर_अघोषित PADATA_H
#घोषणा PADATA_H

#समावेश <linux/compiler_types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/kobject.h>

#घोषणा PADATA_CPU_SERIAL   0x01
#घोषणा PADATA_CPU_PARALLEL 0x02

/**
 * काष्ठा padata_priv - Represents one job
 *
 * @list: List entry, to attach to the padata lists.
 * @pd: Poपूर्णांकer to the पूर्णांकernal control काष्ठाure.
 * @cb_cpu: Callback cpu क्रम serializatioon.
 * @seq_nr: Sequence number of the parallelized data object.
 * @info: Used to pass inक्रमmation from the parallel to the serial function.
 * @parallel: Parallel execution function.
 * @serial: Serial complete function.
 */
काष्ठा padata_priv अणु
	काष्ठा list_head	list;
	काष्ठा parallel_data	*pd;
	पूर्णांक			cb_cpu;
	अचिन्हित पूर्णांक		seq_nr;
	पूर्णांक			info;
	व्योम                    (*parallel)(काष्ठा padata_priv *padata);
	व्योम                    (*serial)(काष्ठा padata_priv *padata);
पूर्ण;

/**
 * काष्ठा padata_list - one per work type per CPU
 *
 * @list: List head.
 * @lock: List lock.
 */
काष्ठा padata_list अणु
	काष्ठा list_head        list;
	spinlock_t              lock;
पूर्ण;

/**
* काष्ठा padata_serial_queue - The percpu padata serial queue
*
* @serial: List to रुको क्रम serialization after reordering.
* @work: work काष्ठा क्रम serialization.
* @pd: Backpoपूर्णांकer to the पूर्णांकernal control काष्ठाure.
*/
काष्ठा padata_serial_queue अणु
       काष्ठा padata_list    serial;
       काष्ठा work_काष्ठा    work;
       काष्ठा parallel_data *pd;
पूर्ण;

/**
 * काष्ठा padata_cpumask - The cpumasks क्रम the parallel/serial workers
 *
 * @pcpu: cpumask क्रम the parallel workers.
 * @cbcpu: cpumask क्रम the serial (callback) workers.
 */
काष्ठा padata_cpumask अणु
	cpumask_var_t	pcpu;
	cpumask_var_t	cbcpu;
पूर्ण;

/**
 * काष्ठा parallel_data - Internal control काष्ठाure, covers everything
 * that depends on the cpumask in use.
 *
 * @ps: padata_shell object.
 * @reorder_list: percpu reorder lists
 * @squeue: percpu padata queues used क्रम serialuzation.
 * @refcnt: Number of objects holding a reference on this parallel_data.
 * @seq_nr: Sequence number of the parallelized data object.
 * @processed: Number of alपढ़ोy processed objects.
 * @cpu: Next CPU to be processed.
 * @cpumask: The cpumasks in use क्रम parallel and serial workers.
 * @reorder_work: work काष्ठा क्रम reordering.
 * @lock: Reorder lock.
 */
काष्ठा parallel_data अणु
	काष्ठा padata_shell		*ps;
	काष्ठा padata_list		__percpu *reorder_list;
	काष्ठा padata_serial_queue	__percpu *squeue;
	atomic_t			refcnt;
	अचिन्हित पूर्णांक			seq_nr;
	अचिन्हित पूर्णांक			processed;
	पूर्णांक				cpu;
	काष्ठा padata_cpumask		cpumask;
	काष्ठा work_काष्ठा		reorder_work;
	spinlock_t                      ____cacheline_aligned lock;
पूर्ण;

/**
 * काष्ठा padata_shell - Wrapper around काष्ठा parallel_data, its
 * purpose is to allow the underlying control काष्ठाure to be replaced
 * on the fly using RCU.
 *
 * @pinst: padat instance.
 * @pd: Actual parallel_data काष्ठाure which may be substituted on the fly.
 * @opd: Poपूर्णांकer to old pd to be मुक्तd by padata_replace.
 * @list: List entry in padata_instance list.
 */
काष्ठा padata_shell अणु
	काष्ठा padata_instance		*pinst;
	काष्ठा parallel_data __rcu	*pd;
	काष्ठा parallel_data		*opd;
	काष्ठा list_head		list;
पूर्ण;

/**
 * काष्ठा padata_mt_job - represents one multithपढ़ोed job
 *
 * @thपढ़ो_fn: Called क्रम each chunk of work that a padata thपढ़ो करोes.
 * @fn_arg: The thपढ़ो function argument.
 * @start: The start of the job (units are job-specअगरic).
 * @size: size of this node's work (units are job-specअगरic).
 * @align: Ranges passed to the thपढ़ो function fall on this boundary, with the
 *         possible exceptions of the beginning and end of the job.
 * @min_chunk: The minimum chunk size in job-specअगरic units.  This allows
 *             the client to communicate the minimum amount of work that's
 *             appropriate क्रम one worker thपढ़ो to करो at once.
 * @max_thपढ़ोs: Max thपढ़ोs to use क्रम the job, actual number may be less
 *               depending on task size and minimum chunk size.
 */
काष्ठा padata_mt_job अणु
	व्योम (*thपढ़ो_fn)(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, व्योम *arg);
	व्योम			*fn_arg;
	अचिन्हित दीर्घ		start;
	अचिन्हित दीर्घ		size;
	अचिन्हित दीर्घ		align;
	अचिन्हित दीर्घ		min_chunk;
	पूर्णांक			max_thपढ़ोs;
पूर्ण;

/**
 * काष्ठा padata_instance - The overall control काष्ठाure.
 *
 * @cpu_online_node: Linkage क्रम CPU online callback.
 * @cpu_dead_node: Linkage क्रम CPU offline callback.
 * @parallel_wq: The workqueue used क्रम parallel work.
 * @serial_wq: The workqueue used क्रम serial work.
 * @pslist: List of padata_shell objects attached to this instance.
 * @cpumask: User supplied cpumasks क्रम parallel and serial works.
 * @kobj: padata instance kernel object.
 * @lock: padata instance lock.
 * @flags: padata flags.
 */
काष्ठा padata_instance अणु
	काष्ठा hlist_node		cpu_online_node;
	काष्ठा hlist_node		cpu_dead_node;
	काष्ठा workqueue_काष्ठा		*parallel_wq;
	काष्ठा workqueue_काष्ठा		*serial_wq;
	काष्ठा list_head		pslist;
	काष्ठा padata_cpumask		cpumask;
	काष्ठा kobject                   kobj;
	काष्ठा mutex			 lock;
	u8				 flags;
#घोषणा	PADATA_INIT	1
#घोषणा	PADATA_RESET	2
#घोषणा	PADATA_INVALID	4
पूर्ण;

#अगर_घोषित CONFIG_PADATA
बाह्य व्योम __init padata_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __init padata_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य काष्ठा padata_instance *padata_alloc(स्थिर अक्षर *name);
बाह्य व्योम padata_मुक्त(काष्ठा padata_instance *pinst);
बाह्य काष्ठा padata_shell *padata_alloc_shell(काष्ठा padata_instance *pinst);
बाह्य व्योम padata_मुक्त_shell(काष्ठा padata_shell *ps);
बाह्य पूर्णांक padata_करो_parallel(काष्ठा padata_shell *ps,
			      काष्ठा padata_priv *padata, पूर्णांक *cb_cpu);
बाह्य व्योम padata_करो_serial(काष्ठा padata_priv *padata);
बाह्य व्योम __init padata_करो_multithपढ़ोed(काष्ठा padata_mt_job *job);
बाह्य पूर्णांक padata_set_cpumask(काष्ठा padata_instance *pinst, पूर्णांक cpumask_type,
			      cpumask_var_t cpumask);
#पूर्ण_अगर
