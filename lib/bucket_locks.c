<शैली गुरु>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

/* Allocate an array of spinlocks to be accessed by a hash. Two arguments
 * indicate the number of elements to allocate in the array. max_size
 * gives the maximum number of elements to allocate. cpu_mult gives
 * the number of locks per CPU to allocate. The size is rounded up
 * to a घातer of 2 to be suitable as a hash table.
 */

पूर्णांक __alloc_bucket_spinlocks(spinlock_t **locks, अचिन्हित पूर्णांक *locks_mask,
			     माप_प्रकार max_size, अचिन्हित पूर्णांक cpu_mult, gfp_t gfp,
			     स्थिर अक्षर *name, काष्ठा lock_class_key *key)
अणु
	spinlock_t *tlocks = शून्य;
	अचिन्हित पूर्णांक i, size;
#अगर defined(CONFIG_PROVE_LOCKING)
	अचिन्हित पूर्णांक nr_pcpus = 2;
#अन्यथा
	अचिन्हित पूर्णांक nr_pcpus = num_possible_cpus();
#पूर्ण_अगर

	अगर (cpu_mult) अणु
		nr_pcpus = min_t(अचिन्हित पूर्णांक, nr_pcpus, 64UL);
		size = min_t(अचिन्हित पूर्णांक, nr_pcpus * cpu_mult, max_size);
	पूर्ण अन्यथा अणु
		size = max_size;
	पूर्ण

	अगर (माप(spinlock_t) != 0) अणु
		tlocks = kvदो_स्मृति_array(size, माप(spinlock_t), gfp);
		अगर (!tlocks)
			वापस -ENOMEM;
		क्रम (i = 0; i < size; i++) अणु
			spin_lock_init(&tlocks[i]);
			lockdep_init_map(&tlocks[i].dep_map, name, key, 0);
		पूर्ण
	पूर्ण

	*locks = tlocks;
	*locks_mask = size - 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__alloc_bucket_spinlocks);

व्योम मुक्त_bucket_spinlocks(spinlock_t *locks)
अणु
	kvमुक्त(locks);
पूर्ण
EXPORT_SYMBOL(मुक्त_bucket_spinlocks);
