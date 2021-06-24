<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/seq_file.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/module.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/fs.h>

#समावेश "trace_output.h"

काष्ठा recursed_functions अणु
	अचिन्हित दीर्घ		ip;
	अचिन्हित दीर्घ		parent_ip;
पूर्ण;

अटल काष्ठा recursed_functions recursed_functions[CONFIG_FTRACE_RECORD_RECURSION_SIZE];
अटल atomic_t nr_records;

/*
 * Cache the last found function. Yes, updates to this is racey, but
 * so is memory cache ;-)
 */
अटल अचिन्हित दीर्घ cached_function;

व्योम ftrace_record_recursion(अचिन्हित दीर्घ ip, अचिन्हित दीर्घ parent_ip)
अणु
	पूर्णांक index = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ old;

 again:
	/* First check the last one recorded */
	अगर (ip == cached_function)
		वापस;

	i = atomic_पढ़ो(&nr_records);
	/* nr_records is -1 when clearing records */
	smp_mb__after_atomic();
	अगर (i < 0)
		वापस;

	/*
	 * If there's two ग_लिखोrs and this ग_लिखोr comes in second,
	 * the cmpxchg() below to update the ip will fail. Then this
	 * ग_लिखोr will try again. It is possible that index will now
	 * be greater than nr_records. This is because the ग_लिखोr
	 * that succeeded has not updated the nr_records yet.
	 * This ग_लिखोr could keep trying again until the other ग_लिखोr
	 * updates nr_records. But अगर the other ग_लिखोr takes an
	 * पूर्णांकerrupt, and that पूर्णांकerrupt locks up that CPU, we करो
	 * not want this CPU to lock up due to the recursion protection,
	 * and have a bug report showing this CPU as the cause of
	 * locking up the computer. To not lose this record, this
	 * ग_लिखोr will simply use the next position to update the
	 * recursed_functions, and it will update the nr_records
	 * accordingly.
	 */
	अगर (index < i)
		index = i;
	अगर (index >= CONFIG_FTRACE_RECORD_RECURSION_SIZE)
		वापस;

	क्रम (i = index - 1; i >= 0; i--) अणु
		अगर (recursed_functions[i].ip == ip) अणु
			cached_function = ip;
			वापस;
		पूर्ण
	पूर्ण

	cached_function = ip;

	/*
	 * We only want to add a function अगर it hasn't been added beक्रमe.
	 * Add to the current location beक्रमe incrementing the count.
	 * If it fails to add, then increment the index (save in i)
	 * and try again.
	 */
	old = cmpxchg(&recursed_functions[index].ip, 0, ip);
	अगर (old != 0) अणु
		/* Did something अन्यथा alपढ़ोy added this क्रम us? */
		अगर (old == ip)
			वापस;
		/* Try the next location (use i क्रम the next index) */
		index++;
		जाओ again;
	पूर्ण

	recursed_functions[index].parent_ip = parent_ip;

	/*
	 * It's still possible that we could race with the clearing
	 *    CPU0                                    CPU1
	 *    ----                                    ----
	 *                                       ip = func
	 *  nr_records = -1;
	 *  recursed_functions[0] = 0;
	 *                                       i = -1
	 *                                       अगर (i < 0)
	 *  nr_records = 0;
	 *  (new recursion detected)
	 *      recursed_functions[0] = func
	 *                                            cmpxchg(recursed_functions[0],
	 *                                                    func, 0)
	 *
	 * But the worse that could happen is that we get a zero in
	 * the recursed_functions array, and it's likely that "func" will
	 * be recorded again.
	 */
	i = atomic_पढ़ो(&nr_records);
	smp_mb__after_atomic();
	अगर (i < 0)
		cmpxchg(&recursed_functions[index].ip, ip, 0);
	अन्यथा अगर (i <= index)
		atomic_cmpxchg(&nr_records, i, index + 1);
पूर्ण
EXPORT_SYMBOL_GPL(ftrace_record_recursion);

अटल DEFINE_MUTEX(recursed_function_lock);
अटल काष्ठा trace_seq *tseq;

अटल व्योम *recursed_function_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	व्योम *ret = शून्य;
	पूर्णांक index;

	mutex_lock(&recursed_function_lock);
	index = atomic_पढ़ो(&nr_records);
	अगर (*pos < index) अणु
		ret = &recursed_functions[*pos];
	पूर्ण

	tseq = kzalloc(माप(*tseq), GFP_KERNEL);
	अगर (!tseq)
		वापस ERR_PTR(-ENOMEM);

	trace_seq_init(tseq);

	वापस ret;
पूर्ण

अटल व्योम *recursed_function_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	पूर्णांक index;
	पूर्णांक p;

	index = atomic_पढ़ो(&nr_records);
	p = ++(*pos);

	वापस p < index ? &recursed_functions[p] : शून्य;
पूर्ण

अटल व्योम recursed_function_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	kमुक्त(tseq);
	mutex_unlock(&recursed_function_lock);
पूर्ण

अटल पूर्णांक recursed_function_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा recursed_functions *record = v;
	पूर्णांक ret = 0;

	अगर (record) अणु
		trace_seq_prपूर्णांक_sym(tseq, record->parent_ip, true);
		trace_seq_माला_दो(tseq, ":\t");
		trace_seq_prपूर्णांक_sym(tseq, record->ip, true);
		trace_seq_अ_दो(tseq, '\n');
		ret = trace_prपूर्णांक_seq(m, tseq);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा seq_operations recursed_function_seq_ops = अणु
	.start  = recursed_function_seq_start,
	.next   = recursed_function_seq_next,
	.stop   = recursed_function_seq_stop,
	.show   = recursed_function_seq_show
पूर्ण;

अटल पूर्णांक recursed_function_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&recursed_function_lock);
	/* If this file was खोलोed क्रम ग_लिखो, then erase contents */
	अगर ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC)) अणु
		/* disable updating records */
		atomic_set(&nr_records, -1);
		smp_mb__after_atomic();
		स_रखो(recursed_functions, 0, माप(recursed_functions));
		smp_wmb();
		/* enable them again */
		atomic_set(&nr_records, 0);
	पूर्ण
	अगर (file->f_mode & FMODE_READ)
		ret = seq_खोलो(file, &recursed_function_seq_ops);
	mutex_unlock(&recursed_function_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार recursed_function_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *buffer,
				       माप_प्रकार count, loff_t *ppos)
अणु
	वापस count;
पूर्ण

अटल पूर्णांक recursed_function_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (file->f_mode & FMODE_READ)
		seq_release(inode, file);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations recursed_functions_fops = अणु
	.खोलो           = recursed_function_खोलो,
	.ग_लिखो		= recursed_function_ग_लिखो,
	.पढ़ो           = seq_पढ़ो,
	.llseek         = seq_lseek,
	.release        = recursed_function_release,
पूर्ण;

__init अटल पूर्णांक create_recursed_functions(व्योम)
अणु
	काष्ठा dentry *dentry;

	dentry = trace_create_file("recursed_functions", 0644, शून्य, शून्य,
				   &recursed_functions_fops);
	अगर (!dentry)
		pr_warn("WARNING: Failed to create recursed_functions\n");
	वापस 0;
पूर्ण

fs_initcall(create_recursed_functions);
