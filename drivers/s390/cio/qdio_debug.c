<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright IBM Corp. 2008, 2009
 *
 *  Author: Jan Glauber (jang@linux.vnet.ibm.com)
 */
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/debug.h>
#समावेश "qdio_debug.h"
#समावेश "qdio.h"

debug_info_t *qdio_dbf_setup;
debug_info_t *qdio_dbf_error;

अटल काष्ठा dentry *debugfs_root;
#घोषणा QDIO_DEBUGFS_NAME_LEN	10
#घोषणा QDIO_DBF_NAME_LEN	20

काष्ठा qdio_dbf_entry अणु
	अक्षर dbf_name[QDIO_DBF_NAME_LEN];
	debug_info_t *dbf_info;
	काष्ठा list_head dbf_list;
पूर्ण;

अटल LIST_HEAD(qdio_dbf_list);
अटल DEFINE_MUTEX(qdio_dbf_list_mutex);

अटल debug_info_t *qdio_get_dbf_entry(अक्षर *name)
अणु
	काष्ठा qdio_dbf_entry *entry;
	debug_info_t *rc = शून्य;

	mutex_lock(&qdio_dbf_list_mutex);
	list_क्रम_each_entry(entry, &qdio_dbf_list, dbf_list) अणु
		अगर (म_भेद(entry->dbf_name, name) == 0) अणु
			rc = entry->dbf_info;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&qdio_dbf_list_mutex);
	वापस rc;
पूर्ण

अटल व्योम qdio_clear_dbf_list(व्योम)
अणु
	काष्ठा qdio_dbf_entry *entry, *पंचांगp;

	mutex_lock(&qdio_dbf_list_mutex);
	list_क्रम_each_entry_safe(entry, पंचांगp, &qdio_dbf_list, dbf_list) अणु
		list_del(&entry->dbf_list);
		debug_unरेजिस्टर(entry->dbf_info);
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&qdio_dbf_list_mutex);
पूर्ण

पूर्णांक qdio_allocate_dbf(काष्ठा qdio_irq *irq_ptr)
अणु
	अक्षर text[QDIO_DBF_NAME_LEN];
	काष्ठा qdio_dbf_entry *new_entry;

	DBF_EVENT("irq:%8lx", (अचिन्हित दीर्घ)irq_ptr);

	/* allocate trace view क्रम the पूर्णांकerface */
	snम_लिखो(text, QDIO_DBF_NAME_LEN, "qdio_%s",
		 dev_name(&irq_ptr->cdev->dev));
	irq_ptr->debug_area = qdio_get_dbf_entry(text);
	अगर (irq_ptr->debug_area)
		DBF_DEV_EVENT(DBF_ERR, irq_ptr, "dbf reused");
	अन्यथा अणु
		irq_ptr->debug_area = debug_रेजिस्टर(text, 2, 1, 16);
		अगर (!irq_ptr->debug_area)
			वापस -ENOMEM;
		अगर (debug_रेजिस्टर_view(irq_ptr->debug_area,
						&debug_hex_ascii_view)) अणु
			debug_unरेजिस्टर(irq_ptr->debug_area);
			वापस -ENOMEM;
		पूर्ण
		debug_set_level(irq_ptr->debug_area, DBF_WARN);
		DBF_DEV_EVENT(DBF_ERR, irq_ptr, "dbf created");
		new_entry = kzalloc(माप(काष्ठा qdio_dbf_entry), GFP_KERNEL);
		अगर (!new_entry) अणु
			debug_unरेजिस्टर(irq_ptr->debug_area);
			वापस -ENOMEM;
		पूर्ण
		strlcpy(new_entry->dbf_name, text, QDIO_DBF_NAME_LEN);
		new_entry->dbf_info = irq_ptr->debug_area;
		mutex_lock(&qdio_dbf_list_mutex);
		list_add(&new_entry->dbf_list, &qdio_dbf_list);
		mutex_unlock(&qdio_dbf_list_mutex);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qstat_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अचिन्हित अक्षर state;
	काष्ठा qdio_q *q = m->निजी;
	पूर्णांक i;

	अगर (!q)
		वापस 0;

	seq_म_लिखो(m, "Timestamp: %llx\n", q->बारtamp);
	seq_म_लिखो(m, "Last Data IRQ: %llx  Last AI: %llx\n",
		   q->irq_ptr->last_data_irq_समय, last_ai_समय);
	seq_म_लिखो(m, "nr_used: %d  ftc: %d\n",
		   atomic_पढ़ो(&q->nr_buf_used), q->first_to_check);
	अगर (q->is_input_q) अणु
		seq_म_लिखो(m, "batch start: %u  batch count: %u\n",
			   q->u.in.batch_start, q->u.in.batch_count);
		seq_म_लिखो(m, "DSCI: %x   IRQs disabled: %u\n",
			   *(u8 *)q->irq_ptr->dsci,
			   test_bit(QDIO_IRQ_DISABLED,
				    &q->irq_ptr->poll_state));
	पूर्ण
	seq_म_लिखो(m, "SBAL states:\n");
	seq_म_लिखो(m, "|0      |8      |16     |24     |32     |40     |48     |56  63|\n");

	क्रम (i = 0; i < QDIO_MAX_BUFFERS_PER_Q; i++) अणु
		debug_get_buf_state(q, i, &state);
		चयन (state) अणु
		हाल SLSB_P_INPUT_NOT_INIT:
		हाल SLSB_P_OUTPUT_NOT_INIT:
			seq_म_लिखो(m, "N");
			अवरोध;
		हाल SLSB_P_OUTPUT_PENDING:
			seq_म_लिखो(m, "P");
			अवरोध;
		हाल SLSB_P_INPUT_PRIMED:
		हाल SLSB_CU_OUTPUT_PRIMED:
			seq_म_लिखो(m, "+");
			अवरोध;
		हाल SLSB_P_INPUT_ACK:
			seq_म_लिखो(m, "A");
			अवरोध;
		हाल SLSB_P_INPUT_ERROR:
		हाल SLSB_P_OUTPUT_ERROR:
			seq_म_लिखो(m, "x");
			अवरोध;
		हाल SLSB_CU_INPUT_EMPTY:
		हाल SLSB_P_OUTPUT_EMPTY:
			seq_म_लिखो(m, "-");
			अवरोध;
		हाल SLSB_P_INPUT_HALTED:
		हाल SLSB_P_OUTPUT_HALTED:
			seq_म_लिखो(m, ".");
			अवरोध;
		शेष:
			seq_म_लिखो(m, "?");
		पूर्ण
		अगर (i == 63)
			seq_म_लिखो(m, "\n");
	पूर्ण
	seq_म_लिखो(m, "\n");
	seq_म_लिखो(m, "|64     |72     |80     |88     |96     |104    |112    |   127|\n");

	seq_म_लिखो(m, "\nSBAL statistics:");
	अगर (!q->irq_ptr->perf_stat_enabled) अणु
		seq_म_लिखो(m, " disabled\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(m, "\n1          2..        4..        8..        "
		   "16..       32..       64..       128\n");
	क्रम (i = 0; i < ARRAY_SIZE(q->q_stats.nr_sbals); i++)
		seq_म_लिखो(m, "%-10u ", q->q_stats.nr_sbals[i]);
	seq_म_लिखो(m, "\nError      NOP        Total\n%-10u %-10u %-10u\n\n",
		   q->q_stats.nr_sbal_error, q->q_stats.nr_sbal_nop,
		   q->q_stats.nr_sbal_total);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(qstat);

अटल पूर्णांक ssqd_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ccw_device *cdev = m->निजी;
	काष्ठा qdio_ssqd_desc ssqd;
	पूर्णांक rc;

	rc = qdio_get_ssqd_desc(cdev, &ssqd);
	अगर (rc)
		वापस rc;

	seq_hex_dump(m, "", DUMP_PREFIX_NONE, 16, 4, &ssqd, माप(ssqd),
		     false);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ssqd);

अटल अक्षर *qperf_names[] = अणु
	"Assumed adapter interrupts",
	"QDIO interrupts",
	"Requested PCIs",
	"Outbound tasklet runs",
	"SIGA read",
	"SIGA write",
	"SIGA sync",
	"Inbound calls",
	"Inbound stop_polling",
	"Inbound queue full",
	"Outbound calls",
	"Outbound handler",
	"Outbound queue full",
	"Outbound fast_requeue",
	"Outbound target_full",
	"QEBSM eqbs",
	"QEBSM eqbs partial",
	"QEBSM sqbs",
	"QEBSM sqbs partial",
	"Discarded interrupts"
पूर्ण;

अटल पूर्णांक qperf_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा qdio_irq *irq_ptr = m->निजी;
	अचिन्हित पूर्णांक *stat;
	पूर्णांक i;

	अगर (!irq_ptr)
		वापस 0;
	अगर (!irq_ptr->perf_stat_enabled) अणु
		seq_म_लिखो(m, "disabled\n");
		वापस 0;
	पूर्ण
	stat = (अचिन्हित पूर्णांक *)&irq_ptr->perf_stat;

	क्रम (i = 0; i < ARRAY_SIZE(qperf_names); i++)
		seq_म_लिखो(m, "%26s:\t%u\n",
			   qperf_names[i], *(stat + i));
	वापस 0;
पूर्ण

अटल sमाप_प्रकार qperf_seq_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			       माप_प्रकार count, loff_t *off)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा qdio_irq *irq_ptr = seq->निजी;
	काष्ठा qdio_q *q;
	अचिन्हित दीर्घ val;
	पूर्णांक ret, i;

	अगर (!irq_ptr)
		वापस 0;

	ret = kम_से_अदीर्घ_from_user(ubuf, count, 10, &val);
	अगर (ret)
		वापस ret;

	चयन (val) अणु
	हाल 0:
		irq_ptr->perf_stat_enabled = 0;
		स_रखो(&irq_ptr->perf_stat, 0, माप(irq_ptr->perf_stat));
		क्रम_each_input_queue(irq_ptr, q, i)
			स_रखो(&q->q_stats, 0, माप(q->q_stats));
		क्रम_each_output_queue(irq_ptr, q, i)
			स_रखो(&q->q_stats, 0, माप(q->q_stats));
		अवरोध;
	हाल 1:
		irq_ptr->perf_stat_enabled = 1;
		अवरोध;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक qperf_seq_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, qperf_show,
			   file_inode(filp)->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_perf_fops = अणु
	.owner	 = THIS_MODULE,
	.खोलो	 = qperf_seq_खोलो,
	.पढ़ो	 = seq_पढ़ो,
	.ग_लिखो	 = qperf_seq_ग_लिखो,
	.llseek  = seq_lseek,
	.release = single_release,
पूर्ण;

अटल व्योम setup_debugfs_entry(काष्ठा dentry *parent, काष्ठा qdio_q *q)
अणु
	अक्षर name[QDIO_DEBUGFS_NAME_LEN];

	snम_लिखो(name, QDIO_DEBUGFS_NAME_LEN, "%s_%d",
		 q->is_input_q ? "input" : "output",
		 q->nr);
	debugfs_create_file(name, 0444, parent, q, &qstat_fops);
पूर्ण

व्योम qdio_setup_debug_entries(काष्ठा qdio_irq *irq_ptr)
अणु
	काष्ठा qdio_q *q;
	पूर्णांक i;

	irq_ptr->debugfs_dev = debugfs_create_dir(dev_name(&irq_ptr->cdev->dev),
						  debugfs_root);
	debugfs_create_file("statistics", S_IFREG | S_IRUGO | S_IWUSR,
			    irq_ptr->debugfs_dev, irq_ptr, &debugfs_perf_fops);
	debugfs_create_file("ssqd", 0444, irq_ptr->debugfs_dev, irq_ptr->cdev,
			    &ssqd_fops);

	क्रम_each_input_queue(irq_ptr, q, i)
		setup_debugfs_entry(irq_ptr->debugfs_dev, q);
	क्रम_each_output_queue(irq_ptr, q, i)
		setup_debugfs_entry(irq_ptr->debugfs_dev, q);
पूर्ण

व्योम qdio_shutकरोwn_debug_entries(काष्ठा qdio_irq *irq_ptr)
अणु
	debugfs_हटाओ_recursive(irq_ptr->debugfs_dev);
पूर्ण

पूर्णांक __init qdio_debug_init(व्योम)
अणु
	debugfs_root = debugfs_create_dir("qdio", शून्य);

	qdio_dbf_setup = debug_रेजिस्टर("qdio_setup", 16, 1, 16);
	debug_रेजिस्टर_view(qdio_dbf_setup, &debug_hex_ascii_view);
	debug_set_level(qdio_dbf_setup, DBF_INFO);
	DBF_EVENT("dbf created\n");

	qdio_dbf_error = debug_रेजिस्टर("qdio_error", 4, 1, 16);
	debug_रेजिस्टर_view(qdio_dbf_error, &debug_hex_ascii_view);
	debug_set_level(qdio_dbf_error, DBF_INFO);
	DBF_ERROR("dbf created\n");
	वापस 0;
पूर्ण

व्योम qdio_debug_निकास(व्योम)
अणु
	qdio_clear_dbf_list();
	debugfs_हटाओ_recursive(debugfs_root);
	debug_unरेजिस्टर(qdio_dbf_setup);
	debug_unरेजिस्टर(qdio_dbf_error);
पूर्ण
