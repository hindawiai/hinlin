<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012  Google, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/percpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/atomic.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/err.h>
#समावेश <linux/cache.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/barrier.h>
#समावेश "internal.h"

/* This करोesn't need to be atomic: speed is chosen over correctness here. */
अटल u64 pstore_ftrace_stamp;

अटल व्योम notrace pstore_ftrace_call(अचिन्हित दीर्घ ip,
				       अचिन्हित दीर्घ parent_ip,
				       काष्ठा ftrace_ops *op,
				       काष्ठा ftrace_regs *fregs)
अणु
	पूर्णांक bit;
	अचिन्हित दीर्घ flags;
	काष्ठा pstore_ftrace_record rec = अणुपूर्ण;
	काष्ठा pstore_record record = अणु
		.type = PSTORE_TYPE_FTRACE,
		.buf = (अक्षर *)&rec,
		.size = माप(rec),
		.psi = psinfo,
	पूर्ण;

	अगर (unlikely(oops_in_progress))
		वापस;

	bit = ftrace_test_recursion_trylock(ip, parent_ip);
	अगर (bit < 0)
		वापस;

	local_irq_save(flags);

	rec.ip = ip;
	rec.parent_ip = parent_ip;
	pstore_ftrace_ग_लिखो_बारtamp(&rec, pstore_ftrace_stamp++);
	pstore_ftrace_encode_cpu(&rec, raw_smp_processor_id());
	psinfo->ग_लिखो(&record);

	local_irq_restore(flags);
	ftrace_test_recursion_unlock(bit);
पूर्ण

अटल काष्ठा ftrace_ops pstore_ftrace_ops __पढ़ो_mostly = अणु
	.func	= pstore_ftrace_call,
पूर्ण;

अटल DEFINE_MUTEX(pstore_ftrace_lock);
अटल bool pstore_ftrace_enabled;

अटल sमाप_प्रकार pstore_ftrace_knob_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	u8 on;
	sमाप_प्रकार ret;

	ret = kstrtou8_from_user(buf, count, 2, &on);
	अगर (ret)
		वापस ret;

	mutex_lock(&pstore_ftrace_lock);

	अगर (!on ^ pstore_ftrace_enabled)
		जाओ out;

	अगर (on) अणु
		ftrace_ops_set_global_filter(&pstore_ftrace_ops);
		ret = रेजिस्टर_ftrace_function(&pstore_ftrace_ops);
	पूर्ण अन्यथा अणु
		ret = unरेजिस्टर_ftrace_function(&pstore_ftrace_ops);
	पूर्ण

	अगर (ret) अणु
		pr_err("%s: unable to %sregister ftrace ops: %zd\n",
		       __func__, on ? "" : "un", ret);
		जाओ err;
	पूर्ण

	pstore_ftrace_enabled = on;
out:
	ret = count;
err:
	mutex_unlock(&pstore_ftrace_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार pstore_ftrace_knob_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर val[] = अणु '0' + pstore_ftrace_enabled, '\n' पूर्ण;

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, val, माप(val));
पूर्ण

अटल स्थिर काष्ठा file_operations pstore_knob_fops = अणु
	.खोलो	= simple_खोलो,
	.पढ़ो	= pstore_ftrace_knob_पढ़ो,
	.ग_लिखो	= pstore_ftrace_knob_ग_लिखो,
पूर्ण;

अटल काष्ठा dentry *pstore_ftrace_dir;

व्योम pstore_रेजिस्टर_ftrace(व्योम)
अणु
	अगर (!psinfo->ग_लिखो)
		वापस;

	pstore_ftrace_dir = debugfs_create_dir("pstore", शून्य);

	debugfs_create_file("record_ftrace", 0600, pstore_ftrace_dir, शून्य,
			    &pstore_knob_fops);
पूर्ण

व्योम pstore_unरेजिस्टर_ftrace(व्योम)
अणु
	mutex_lock(&pstore_ftrace_lock);
	अगर (pstore_ftrace_enabled) अणु
		unरेजिस्टर_ftrace_function(&pstore_ftrace_ops);
		pstore_ftrace_enabled = false;
	पूर्ण
	mutex_unlock(&pstore_ftrace_lock);

	debugfs_हटाओ_recursive(pstore_ftrace_dir);
पूर्ण

sमाप_प्रकार pstore_ftrace_combine_log(अक्षर **dest_log, माप_प्रकार *dest_log_size,
				  स्थिर अक्षर *src_log, माप_प्रकार src_log_size)
अणु
	माप_प्रकार dest_size, src_size, total, dest_off, src_off;
	माप_प्रकार dest_idx = 0, src_idx = 0, merged_idx = 0;
	व्योम *merged_buf;
	काष्ठा pstore_ftrace_record *drec, *srec, *mrec;
	माप_प्रकार record_size = माप(काष्ठा pstore_ftrace_record);

	dest_off = *dest_log_size % record_size;
	dest_size = *dest_log_size - dest_off;

	src_off = src_log_size % record_size;
	src_size = src_log_size - src_off;

	total = dest_size + src_size;
	merged_buf = kदो_स्मृति(total, GFP_KERNEL);
	अगर (!merged_buf)
		वापस -ENOMEM;

	drec = (काष्ठा pstore_ftrace_record *)(*dest_log + dest_off);
	srec = (काष्ठा pstore_ftrace_record *)(src_log + src_off);
	mrec = (काष्ठा pstore_ftrace_record *)(merged_buf);

	जबतक (dest_size > 0 && src_size > 0) अणु
		अगर (pstore_ftrace_पढ़ो_बारtamp(&drec[dest_idx]) <
		    pstore_ftrace_पढ़ो_बारtamp(&srec[src_idx])) अणु
			mrec[merged_idx++] = drec[dest_idx++];
			dest_size -= record_size;
		पूर्ण अन्यथा अणु
			mrec[merged_idx++] = srec[src_idx++];
			src_size -= record_size;
		पूर्ण
	पूर्ण

	जबतक (dest_size > 0) अणु
		mrec[merged_idx++] = drec[dest_idx++];
		dest_size -= record_size;
	पूर्ण

	जबतक (src_size > 0) अणु
		mrec[merged_idx++] = srec[src_idx++];
		src_size -= record_size;
	पूर्ण

	kमुक्त(*dest_log);
	*dest_log = merged_buf;
	*dest_log_size = total;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pstore_ftrace_combine_log);
