<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Character device driver क्रम writing z/VM *MONITOR service records.
 *
 * Copyright IBM Corp. 2006, 2009
 *
 * Author(s): Melissa Howland <Melissa.Howland@us.ibm.com>
 */

#घोषणा KMSG_COMPONENT "monwriter"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/appldata.h>
#समावेश <यंत्र/monग_लिखोr.h>

#घोषणा MONWRITE_MAX_DATALEN	4010

अटल पूर्णांक mon_max_bufs = 255;
अटल पूर्णांक mon_buf_count;

काष्ठा mon_buf अणु
	काष्ठा list_head list;
	काष्ठा monग_लिखो_hdr hdr;
	पूर्णांक diag_करोne;
	अक्षर *data;
पूर्ण;

अटल LIST_HEAD(mon_priv_list);

काष्ठा mon_निजी अणु
	काष्ठा list_head priv_list;
	काष्ठा list_head list;
	काष्ठा monग_लिखो_hdr hdr;
	माप_प्रकार hdr_to_पढ़ो;
	माप_प्रकार data_to_पढ़ो;
	काष्ठा mon_buf *current_buf;
	काष्ठा mutex thपढ़ो_mutex;
पूर्ण;

/*
 * helper functions
 */

अटल पूर्णांक monग_लिखो_diag(काष्ठा monग_लिखो_hdr *myhdr, अक्षर *buffer, पूर्णांक fcn)
अणु
	काष्ठा appldata_parameter_list *parm_list;
	काष्ठा appldata_product_id *id;
	पूर्णांक rc;

	id = kदो_स्मृति(माप(*id), GFP_KERNEL);
	parm_list = kदो_स्मृति(माप(*parm_list), GFP_KERNEL);
	rc = -ENOMEM;
	अगर (!id || !parm_list)
		जाओ out;
	स_नकल(id->prod_nr, "LNXAPPL", 7);
	id->prod_fn = myhdr->applid;
	id->record_nr = myhdr->record_num;
	id->version_nr = myhdr->version;
	id->release_nr = myhdr->release;
	id->mod_lvl = myhdr->mod_level;
	rc = appldata_यंत्र(parm_list, id, fcn,
			  (व्योम *) buffer, myhdr->datalen);
	अगर (rc <= 0)
		जाओ out;
	pr_err("Writing monitor data failed with rc=%i\n", rc);
	rc = (rc == 5) ? -EPERM : -EINVAL;
out:
	kमुक्त(id);
	kमुक्त(parm_list);
	वापस rc;
पूर्ण

अटल काष्ठा mon_buf *monग_लिखो_find_hdr(काष्ठा mon_निजी *monpriv,
					 काष्ठा monग_लिखो_hdr *monhdr)
अणु
	काष्ठा mon_buf *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &monpriv->list, list)
		अगर ((entry->hdr.mon_function == monhdr->mon_function ||
		     monhdr->mon_function == MONWRITE_STOP_INTERVAL) &&
		    entry->hdr.applid == monhdr->applid &&
		    entry->hdr.record_num == monhdr->record_num &&
		    entry->hdr.version == monhdr->version &&
		    entry->hdr.release == monhdr->release &&
		    entry->hdr.mod_level == monhdr->mod_level)
			वापस entry;

	वापस शून्य;
पूर्ण

अटल पूर्णांक monग_लिखो_new_hdr(काष्ठा mon_निजी *monpriv)
अणु
	काष्ठा monग_लिखो_hdr *monhdr = &monpriv->hdr;
	काष्ठा mon_buf *monbuf;
	पूर्णांक rc = 0;

	अगर (monhdr->datalen > MONWRITE_MAX_DATALEN ||
	    monhdr->mon_function > MONWRITE_START_CONFIG ||
	    monhdr->hdrlen != माप(काष्ठा monग_लिखो_hdr))
		वापस -EINVAL;
	monbuf = शून्य;
	अगर (monhdr->mon_function != MONWRITE_GEN_EVENT)
		monbuf = monग_लिखो_find_hdr(monpriv, monhdr);
	अगर (monbuf) अणु
		अगर (monhdr->mon_function == MONWRITE_STOP_INTERVAL) अणु
			monhdr->datalen = monbuf->hdr.datalen;
			rc = monग_लिखो_diag(monhdr, monbuf->data,
					   APPLDATA_STOP_REC);
			list_del(&monbuf->list);
			mon_buf_count--;
			kमुक्त(monbuf->data);
			kमुक्त(monbuf);
			monbuf = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (monhdr->mon_function != MONWRITE_STOP_INTERVAL) अणु
		अगर (mon_buf_count >= mon_max_bufs)
			वापस -ENOSPC;
		monbuf = kzalloc(माप(काष्ठा mon_buf), GFP_KERNEL);
		अगर (!monbuf)
			वापस -ENOMEM;
		monbuf->data = kzalloc(monhdr->datalen,
				       GFP_KERNEL | GFP_DMA);
		अगर (!monbuf->data) अणु
			kमुक्त(monbuf);
			वापस -ENOMEM;
		पूर्ण
		monbuf->hdr = *monhdr;
		list_add_tail(&monbuf->list, &monpriv->list);
		अगर (monhdr->mon_function != MONWRITE_GEN_EVENT)
			mon_buf_count++;
	पूर्ण
	monpriv->current_buf = monbuf;
	वापस rc;
पूर्ण

अटल पूर्णांक monग_लिखो_new_data(काष्ठा mon_निजी *monpriv)
अणु
	काष्ठा monग_लिखो_hdr *monhdr = &monpriv->hdr;
	काष्ठा mon_buf *monbuf = monpriv->current_buf;
	पूर्णांक rc = 0;

	चयन (monhdr->mon_function) अणु
	हाल MONWRITE_START_INTERVAL:
		अगर (!monbuf->diag_करोne) अणु
			rc = monग_लिखो_diag(monhdr, monbuf->data,
					   APPLDATA_START_INTERVAL_REC);
			monbuf->diag_करोne = 1;
		पूर्ण
		अवरोध;
	हाल MONWRITE_START_CONFIG:
		अगर (!monbuf->diag_करोne) अणु
			rc = monग_लिखो_diag(monhdr, monbuf->data,
					   APPLDATA_START_CONFIG_REC);
			monbuf->diag_करोne = 1;
		पूर्ण
		अवरोध;
	हाल MONWRITE_GEN_EVENT:
		rc = monग_लिखो_diag(monhdr, monbuf->data,
				   APPLDATA_GEN_EVENT_REC);
		list_del(&monpriv->current_buf->list);
		kमुक्त(monpriv->current_buf->data);
		kमुक्त(monpriv->current_buf);
		monpriv->current_buf = शून्य;
		अवरोध;
	शेष:
		/* monhdr->mon_function is checked in monग_लिखो_new_hdr */
		BUG();
	पूर्ण
	वापस rc;
पूर्ण

/*
 * file operations
 */

अटल पूर्णांक monग_लिखो_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा mon_निजी *monpriv;

	monpriv = kzalloc(माप(काष्ठा mon_निजी), GFP_KERNEL);
	अगर (!monpriv)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&monpriv->list);
	monpriv->hdr_to_पढ़ो = माप(monpriv->hdr);
	mutex_init(&monpriv->thपढ़ो_mutex);
	filp->निजी_data = monpriv;
	list_add_tail(&monpriv->priv_list, &mon_priv_list);
	वापस nonseekable_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक monग_लिखो_बंद(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा mon_निजी *monpriv = filp->निजी_data;
	काष्ठा mon_buf *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &monpriv->list, list) अणु
		अगर (entry->hdr.mon_function != MONWRITE_GEN_EVENT)
			monग_लिखो_diag(&entry->hdr, entry->data,
				      APPLDATA_STOP_REC);
		mon_buf_count--;
		list_del(&entry->list);
		kमुक्त(entry->data);
		kमुक्त(entry);
	पूर्ण
	list_del(&monpriv->priv_list);
	kमुक्त(monpriv);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार monग_लिखो_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *data,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mon_निजी *monpriv = filp->निजी_data;
	माप_प्रकार len, written;
	व्योम *to;
	पूर्णांक rc;

	mutex_lock(&monpriv->thपढ़ो_mutex);
	क्रम (written = 0; written < count; ) अणु
		अगर (monpriv->hdr_to_पढ़ो) अणु
			len = min(count - written, monpriv->hdr_to_पढ़ो);
			to = (अक्षर *) &monpriv->hdr +
				माप(monpriv->hdr) - monpriv->hdr_to_पढ़ो;
			अगर (copy_from_user(to, data + written, len)) अणु
				rc = -EFAULT;
				जाओ out_error;
			पूर्ण
			monpriv->hdr_to_पढ़ो -= len;
			written += len;
			अगर (monpriv->hdr_to_पढ़ो > 0)
				जारी;
			rc = monग_लिखो_new_hdr(monpriv);
			अगर (rc)
				जाओ out_error;
			monpriv->data_to_पढ़ो = monpriv->current_buf ?
				monpriv->current_buf->hdr.datalen : 0;
		पूर्ण

		अगर (monpriv->data_to_पढ़ो) अणु
			len = min(count - written, monpriv->data_to_पढ़ो);
			to = monpriv->current_buf->data +
				monpriv->hdr.datalen - monpriv->data_to_पढ़ो;
			अगर (copy_from_user(to, data + written, len)) अणु
				rc = -EFAULT;
				जाओ out_error;
			पूर्ण
			monpriv->data_to_पढ़ो -= len;
			written += len;
			अगर (monpriv->data_to_पढ़ो > 0)
				जारी;
			rc = monग_लिखो_new_data(monpriv);
			अगर (rc)
				जाओ out_error;
		पूर्ण
		monpriv->hdr_to_पढ़ो = माप(monpriv->hdr);
	पूर्ण
	mutex_unlock(&monpriv->thपढ़ो_mutex);
	वापस written;

out_error:
	monpriv->data_to_पढ़ो = 0;
	monpriv->hdr_to_पढ़ो = माप(काष्ठा monग_लिखो_hdr);
	mutex_unlock(&monpriv->thपढ़ो_mutex);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations monग_लिखो_fops = अणु
	.owner	 = THIS_MODULE,
	.खोलो	 = &monग_लिखो_खोलो,
	.release = &monग_लिखो_बंद,
	.ग_लिखो	 = &monग_लिखो_ग_लिखो,
	.llseek  = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice mon_dev = अणु
	.name	= "monwriter",
	.fops	= &monग_लिखो_fops,
	.minor	= MISC_DYNAMIC_MINOR,
पूर्ण;

/*
 * suspend/resume
 */

अटल पूर्णांक monग_लिखोr_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा mon_निजी *monpriv;
	काष्ठा mon_buf *monbuf;

	list_क्रम_each_entry(monpriv, &mon_priv_list, priv_list) अणु
		list_क्रम_each_entry(monbuf, &monpriv->list, list) अणु
			अगर (monbuf->hdr.mon_function != MONWRITE_GEN_EVENT)
				monग_लिखो_diag(&monbuf->hdr, monbuf->data,
					      APPLDATA_STOP_REC);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक monग_लिखोr_restore(काष्ठा device *dev)
अणु
	काष्ठा mon_निजी *monpriv;
	काष्ठा mon_buf *monbuf;

	list_क्रम_each_entry(monpriv, &mon_priv_list, priv_list) अणु
		list_क्रम_each_entry(monbuf, &monpriv->list, list) अणु
			अगर (monbuf->hdr.mon_function == MONWRITE_START_INTERVAL)
				monग_लिखो_diag(&monbuf->hdr, monbuf->data,
					      APPLDATA_START_INTERVAL_REC);
			अगर (monbuf->hdr.mon_function == MONWRITE_START_CONFIG)
				monग_लिखो_diag(&monbuf->hdr, monbuf->data,
					      APPLDATA_START_CONFIG_REC);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक monग_लिखोr_thaw(काष्ठा device *dev)
अणु
	वापस monग_लिखोr_restore(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops monग_लिखोr_pm_ops = अणु
	.मुक्तze		= monग_लिखोr_मुक्तze,
	.thaw		= monग_लिखोr_thaw,
	.restore	= monग_लिखोr_restore,
पूर्ण;

अटल काष्ठा platक्रमm_driver monग_लिखोr_pdrv = अणु
	.driver = अणु
		.name	= "monwriter",
		.pm	= &monग_लिखोr_pm_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *monग_लिखोr_pdev;

/*
 * module init/निकास
 */

अटल पूर्णांक __init mon_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!MACHINE_IS_VM)
		वापस -ENODEV;

	rc = platक्रमm_driver_रेजिस्टर(&monग_लिखोr_pdrv);
	अगर (rc)
		वापस rc;

	monग_लिखोr_pdev = platक्रमm_device_रेजिस्टर_simple("monwriter", -1, शून्य,
							0);
	अगर (IS_ERR(monग_लिखोr_pdev)) अणु
		rc = PTR_ERR(monग_लिखोr_pdev);
		जाओ out_driver;
	पूर्ण

	/*
	 * misc_रेजिस्टर() has to be the last action in module_init(), because
	 * file operations will be available right after this.
	 */
	rc = misc_रेजिस्टर(&mon_dev);
	अगर (rc)
		जाओ out_device;
	वापस 0;

out_device:
	platक्रमm_device_unरेजिस्टर(monग_लिखोr_pdev);
out_driver:
	platक्रमm_driver_unरेजिस्टर(&monग_लिखोr_pdrv);
	वापस rc;
पूर्ण

अटल व्योम __निकास mon_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&mon_dev);
	platक्रमm_device_unरेजिस्टर(monग_लिखोr_pdev);
	platक्रमm_driver_unरेजिस्टर(&monग_लिखोr_pdrv);
पूर्ण

module_init(mon_init);
module_निकास(mon_निकास);

module_param_named(max_bufs, mon_max_bufs, पूर्णांक, 0644);
MODULE_PARM_DESC(max_bufs, "Maximum number of sample monitor data buffers "
		 "that can be active at one time");

MODULE_AUTHOR("Melissa Howland <Melissa.Howland@us.ibm.com>");
MODULE_DESCRIPTION("Character device driver for writing z/VM "
		   "APPLDATA monitor records.");
MODULE_LICENSE("GPL");
