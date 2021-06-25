<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#समावेश "percpu_freelist.h"

पूर्णांक pcpu_मुक्तlist_init(काष्ठा pcpu_मुक्तlist *s)
अणु
	पूर्णांक cpu;

	s->मुक्तlist = alloc_percpu(काष्ठा pcpu_मुक्तlist_head);
	अगर (!s->मुक्तlist)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा pcpu_मुक्तlist_head *head = per_cpu_ptr(s->मुक्तlist, cpu);

		raw_spin_lock_init(&head->lock);
		head->first = शून्य;
	पूर्ण
	raw_spin_lock_init(&s->extralist.lock);
	s->extralist.first = शून्य;
	वापस 0;
पूर्ण

व्योम pcpu_मुक्तlist_destroy(काष्ठा pcpu_मुक्तlist *s)
अणु
	मुक्त_percpu(s->मुक्तlist);
पूर्ण

अटल अंतरभूत व्योम pcpu_मुक्तlist_push_node(काष्ठा pcpu_मुक्तlist_head *head,
					   काष्ठा pcpu_मुक्तlist_node *node)
अणु
	node->next = head->first;
	head->first = node;
पूर्ण

अटल अंतरभूत व्योम ___pcpu_मुक्तlist_push(काष्ठा pcpu_मुक्तlist_head *head,
					 काष्ठा pcpu_मुक्तlist_node *node)
अणु
	raw_spin_lock(&head->lock);
	pcpu_मुक्तlist_push_node(head, node);
	raw_spin_unlock(&head->lock);
पूर्ण

अटल अंतरभूत bool pcpu_मुक्तlist_try_push_extra(काष्ठा pcpu_मुक्तlist *s,
						काष्ठा pcpu_मुक्तlist_node *node)
अणु
	अगर (!raw_spin_trylock(&s->extralist.lock))
		वापस false;

	pcpu_मुक्तlist_push_node(&s->extralist, node);
	raw_spin_unlock(&s->extralist.lock);
	वापस true;
पूर्ण

अटल अंतरभूत व्योम ___pcpu_मुक्तlist_push_nmi(काष्ठा pcpu_मुक्तlist *s,
					     काष्ठा pcpu_मुक्तlist_node *node)
अणु
	पूर्णांक cpu, orig_cpu;

	orig_cpu = cpu = raw_smp_processor_id();
	जबतक (1) अणु
		काष्ठा pcpu_मुक्तlist_head *head;

		head = per_cpu_ptr(s->मुक्तlist, cpu);
		अगर (raw_spin_trylock(&head->lock)) अणु
			pcpu_मुक्तlist_push_node(head, node);
			raw_spin_unlock(&head->lock);
			वापस;
		पूर्ण
		cpu = cpumask_next(cpu, cpu_possible_mask);
		अगर (cpu >= nr_cpu_ids)
			cpu = 0;

		/* cannot lock any per cpu lock, try extralist */
		अगर (cpu == orig_cpu &&
		    pcpu_मुक्तlist_try_push_extra(s, node))
			वापस;
	पूर्ण
पूर्ण

व्योम __pcpu_मुक्तlist_push(काष्ठा pcpu_मुक्तlist *s,
			काष्ठा pcpu_मुक्तlist_node *node)
अणु
	अगर (in_nmi())
		___pcpu_मुक्तlist_push_nmi(s, node);
	अन्यथा
		___pcpu_मुक्तlist_push(this_cpu_ptr(s->मुक्तlist), node);
पूर्ण

व्योम pcpu_मुक्तlist_push(काष्ठा pcpu_मुक्तlist *s,
			काष्ठा pcpu_मुक्तlist_node *node)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__pcpu_मुक्तlist_push(s, node);
	local_irq_restore(flags);
पूर्ण

व्योम pcpu_मुक्तlist_populate(काष्ठा pcpu_मुक्तlist *s, व्योम *buf, u32 elem_size,
			    u32 nr_elems)
अणु
	काष्ठा pcpu_मुक्तlist_head *head;
	पूर्णांक i, cpu, pcpu_entries;

	pcpu_entries = nr_elems / num_possible_cpus() + 1;
	i = 0;

	क्रम_each_possible_cpu(cpu) अणु
again:
		head = per_cpu_ptr(s->मुक्तlist, cpu);
		/* No locking required as this is not visible yet. */
		pcpu_मुक्तlist_push_node(head, buf);
		i++;
		buf += elem_size;
		अगर (i == nr_elems)
			अवरोध;
		अगर (i % pcpu_entries)
			जाओ again;
	पूर्ण
पूर्ण

अटल काष्ठा pcpu_मुक्तlist_node *___pcpu_मुक्तlist_pop(काष्ठा pcpu_मुक्तlist *s)
अणु
	काष्ठा pcpu_मुक्तlist_head *head;
	काष्ठा pcpu_मुक्तlist_node *node;
	पूर्णांक orig_cpu, cpu;

	orig_cpu = cpu = raw_smp_processor_id();
	जबतक (1) अणु
		head = per_cpu_ptr(s->मुक्तlist, cpu);
		raw_spin_lock(&head->lock);
		node = head->first;
		अगर (node) अणु
			head->first = node->next;
			raw_spin_unlock(&head->lock);
			वापस node;
		पूर्ण
		raw_spin_unlock(&head->lock);
		cpu = cpumask_next(cpu, cpu_possible_mask);
		अगर (cpu >= nr_cpu_ids)
			cpu = 0;
		अगर (cpu == orig_cpu)
			अवरोध;
	पूर्ण

	/* per cpu lists are all empty, try extralist */
	raw_spin_lock(&s->extralist.lock);
	node = s->extralist.first;
	अगर (node)
		s->extralist.first = node->next;
	raw_spin_unlock(&s->extralist.lock);
	वापस node;
पूर्ण

अटल काष्ठा pcpu_मुक्तlist_node *
___pcpu_मुक्तlist_pop_nmi(काष्ठा pcpu_मुक्तlist *s)
अणु
	काष्ठा pcpu_मुक्तlist_head *head;
	काष्ठा pcpu_मुक्तlist_node *node;
	पूर्णांक orig_cpu, cpu;

	orig_cpu = cpu = raw_smp_processor_id();
	जबतक (1) अणु
		head = per_cpu_ptr(s->मुक्तlist, cpu);
		अगर (raw_spin_trylock(&head->lock)) अणु
			node = head->first;
			अगर (node) अणु
				head->first = node->next;
				raw_spin_unlock(&head->lock);
				वापस node;
			पूर्ण
			raw_spin_unlock(&head->lock);
		पूर्ण
		cpu = cpumask_next(cpu, cpu_possible_mask);
		अगर (cpu >= nr_cpu_ids)
			cpu = 0;
		अगर (cpu == orig_cpu)
			अवरोध;
	पूर्ण

	/* cannot pop from per cpu lists, try extralist */
	अगर (!raw_spin_trylock(&s->extralist.lock))
		वापस शून्य;
	node = s->extralist.first;
	अगर (node)
		s->extralist.first = node->next;
	raw_spin_unlock(&s->extralist.lock);
	वापस node;
पूर्ण

काष्ठा pcpu_मुक्तlist_node *__pcpu_मुक्तlist_pop(काष्ठा pcpu_मुक्तlist *s)
अणु
	अगर (in_nmi())
		वापस ___pcpu_मुक्तlist_pop_nmi(s);
	वापस ___pcpu_मुक्तlist_pop(s);
पूर्ण

काष्ठा pcpu_मुक्तlist_node *pcpu_मुक्तlist_pop(काष्ठा pcpu_मुक्तlist *s)
अणु
	काष्ठा pcpu_मुक्तlist_node *ret;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	ret = __pcpu_मुक्तlist_pop(s);
	local_irq_restore(flags);
	वापस ret;
पूर्ण
