<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqnr.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

/*
 * /proc/पूर्णांकerrupts
 */
अटल व्योम *पूर्णांक_seq_start(काष्ठा seq_file *f, loff_t *pos)
अणु
	वापस (*pos <= nr_irqs) ? pos : शून्य;
पूर्ण

अटल व्योम *पूर्णांक_seq_next(काष्ठा seq_file *f, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	अगर (*pos > nr_irqs)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम पूर्णांक_seq_stop(काष्ठा seq_file *f, व्योम *v)
अणु
	/* Nothing to करो */
पूर्ण

अटल स्थिर काष्ठा seq_operations पूर्णांक_seq_ops = अणु
	.start = पूर्णांक_seq_start,
	.next  = पूर्णांक_seq_next,
	.stop  = पूर्णांक_seq_stop,
	.show  = show_पूर्णांकerrupts
पूर्ण;

अटल पूर्णांक __init proc_पूर्णांकerrupts_init(व्योम)
अणु
	proc_create_seq("interrupts", 0, शून्य, &पूर्णांक_seq_ops);
	वापस 0;
पूर्ण
fs_initcall(proc_पूर्णांकerrupts_init);
