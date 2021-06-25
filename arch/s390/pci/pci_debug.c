<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright IBM Corp. 2012,2015
 *
 *  Author(s):
 *    Jan Glauber <jang@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "zpci"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/debug.h>

#समावेश <यंत्र/pci_dma.h>

अटल काष्ठा dentry *debugfs_root;
debug_info_t *pci_debug_msg_id;
EXPORT_SYMBOL_GPL(pci_debug_msg_id);
debug_info_t *pci_debug_err_id;
EXPORT_SYMBOL_GPL(pci_debug_err_id);

अटल अक्षर *pci_common_names[] = अणु
	"Load operations",
	"Store operations",
	"Store block operations",
	"Refresh operations",
पूर्ण;

अटल अक्षर *pci_fmt0_names[] = अणु
	"DMA read bytes",
	"DMA write bytes",
पूर्ण;

अटल अक्षर *pci_fmt1_names[] = अणु
	"Received bytes",
	"Received packets",
	"Transmitted bytes",
	"Transmitted packets",
पूर्ण;

अटल अक्षर *pci_fmt2_names[] = अणु
	"Consumed work units",
	"Maximum work units",
पूर्ण;

अटल अक्षर *pci_fmt3_names[] = अणु
	"Transmitted bytes",
पूर्ण;

अटल अक्षर *pci_sw_names[] = अणु
	"Allocated pages",
	"Mapped pages",
	"Unmapped pages",
पूर्ण;

अटल व्योम pci_fmb_show(काष्ठा seq_file *m, अक्षर *name[], पूर्णांक length,
			 u64 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < length; i++, data++)
		seq_म_लिखो(m, "%26s:\t%llu\n", name[i], *data);
पूर्ण

अटल व्योम pci_sw_counter_show(काष्ठा seq_file *m)
अणु
	काष्ठा zpci_dev *zdev = m->निजी;
	atomic64_t *counter = &zdev->allocated_pages;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pci_sw_names); i++, counter++)
		seq_म_लिखो(m, "%26s:\t%llu\n", pci_sw_names[i],
			   atomic64_पढ़ो(counter));
पूर्ण

अटल पूर्णांक pci_perf_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा zpci_dev *zdev = m->निजी;

	अगर (!zdev)
		वापस 0;

	mutex_lock(&zdev->lock);
	अगर (!zdev->fmb) अणु
		mutex_unlock(&zdev->lock);
		seq_माला_दो(m, "FMB statistics disabled\n");
		वापस 0;
	पूर्ण

	/* header */
	seq_म_लिखो(m, "Update interval: %u ms\n", zdev->fmb_update);
	seq_म_लिखो(m, "Samples: %u\n", zdev->fmb->samples);
	seq_म_लिखो(m, "Last update TOD: %Lx\n", zdev->fmb->last_update);

	pci_fmb_show(m, pci_common_names, ARRAY_SIZE(pci_common_names),
		     &zdev->fmb->ld_ops);

	चयन (zdev->fmb->क्रमmat) अणु
	हाल 0:
		अगर (!(zdev->fmb->fmt_ind & ZPCI_FMB_DMA_COUNTER_VALID))
			अवरोध;
		pci_fmb_show(m, pci_fmt0_names, ARRAY_SIZE(pci_fmt0_names),
			     &zdev->fmb->fmt0.dma_rbytes);
		अवरोध;
	हाल 1:
		pci_fmb_show(m, pci_fmt1_names, ARRAY_SIZE(pci_fmt1_names),
			     &zdev->fmb->fmt1.rx_bytes);
		अवरोध;
	हाल 2:
		pci_fmb_show(m, pci_fmt2_names, ARRAY_SIZE(pci_fmt2_names),
			     &zdev->fmb->fmt2.consumed_work_units);
		अवरोध;
	हाल 3:
		pci_fmb_show(m, pci_fmt3_names, ARRAY_SIZE(pci_fmt3_names),
			     &zdev->fmb->fmt3.tx_bytes);
		अवरोध;
	शेष:
		seq_माला_दो(m, "Unknown format\n");
	पूर्ण

	pci_sw_counter_show(m);
	mutex_unlock(&zdev->lock);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार pci_perf_seq_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				  माप_प्रकार count, loff_t *off)
अणु
	काष्ठा zpci_dev *zdev = ((काष्ठा seq_file *) file->निजी_data)->निजी;
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	अगर (!zdev)
		वापस 0;

	rc = kम_से_अदीर्घ_from_user(ubuf, count, 10, &val);
	अगर (rc)
		वापस rc;

	mutex_lock(&zdev->lock);
	चयन (val) अणु
	हाल 0:
		rc = zpci_fmb_disable_device(zdev);
		अवरोध;
	हाल 1:
		rc = zpci_fmb_enable_device(zdev);
		अवरोध;
	पूर्ण
	mutex_unlock(&zdev->lock);
	वापस rc ? rc : count;
पूर्ण

अटल पूर्णांक pci_perf_seq_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, pci_perf_show,
			   file_inode(filp)->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_pci_perf_fops = अणु
	.खोलो	 = pci_perf_seq_खोलो,
	.पढ़ो	 = seq_पढ़ो,
	.ग_लिखो	 = pci_perf_seq_ग_लिखो,
	.llseek  = seq_lseek,
	.release = single_release,
पूर्ण;

व्योम zpci_debug_init_device(काष्ठा zpci_dev *zdev, स्थिर अक्षर *name)
अणु
	zdev->debugfs_dev = debugfs_create_dir(name, debugfs_root);

	debugfs_create_file("statistics", S_IFREG | S_IRUGO | S_IWUSR,
			    zdev->debugfs_dev, zdev, &debugfs_pci_perf_fops);
पूर्ण

व्योम zpci_debug_निकास_device(काष्ठा zpci_dev *zdev)
अणु
	debugfs_हटाओ_recursive(zdev->debugfs_dev);
पूर्ण

पूर्णांक __init zpci_debug_init(व्योम)
अणु
	/* event trace buffer */
	pci_debug_msg_id = debug_रेजिस्टर("pci_msg", 8, 1, 8 * माप(दीर्घ));
	अगर (!pci_debug_msg_id)
		वापस -EINVAL;
	debug_रेजिस्टर_view(pci_debug_msg_id, &debug_प्र_लिखो_view);
	debug_set_level(pci_debug_msg_id, 3);

	/* error log */
	pci_debug_err_id = debug_रेजिस्टर("pci_error", 2, 1, 16);
	अगर (!pci_debug_err_id)
		वापस -EINVAL;
	debug_रेजिस्टर_view(pci_debug_err_id, &debug_hex_ascii_view);
	debug_set_level(pci_debug_err_id, 6);

	debugfs_root = debugfs_create_dir("pci", शून्य);
	वापस 0;
पूर्ण

व्योम zpci_debug_निकास(व्योम)
अणु
	debug_unरेजिस्टर(pci_debug_msg_id);
	debug_unरेजिस्टर(pci_debug_err_id);
	debugfs_हटाओ(debugfs_root);
पूर्ण
