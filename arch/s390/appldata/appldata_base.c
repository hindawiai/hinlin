<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Base infraकाष्ठाure क्रम Linux-z/VM Monitor Stream, Stage 1.
 * Exports appldata_रेजिस्टर_ops() and appldata_unरेजिस्टर_ops() क्रम the
 * data gathering modules.
 *
 * Copyright IBM Corp. 2003, 2009
 *
 * Author: Gerald Schaefer <gerald.schaefer@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT	"appldata"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/suspend.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/appldata.h>
#समावेश <यंत्र/vसमयr.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>

#समावेश "appldata.h"


#घोषणा APPLDATA_CPU_INTERVAL	10000		/* शेष (CPU) समय क्रम
						   sampling पूर्णांकerval in
						   milliseconds */

#घोषणा TOD_MICRO	0x01000			/* nr. of TOD घड़ी units
						   क्रम 1 microsecond */

अटल काष्ठा platक्रमm_device *appldata_pdev;

/*
 * /proc entries (sysctl)
 */
अटल स्थिर अक्षर appldata_proc_name[APPLDATA_PROC_NAME_LENGTH] = "appldata";
अटल पूर्णांक appldata_समयr_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
अटल पूर्णांक appldata_पूर्णांकerval_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);

अटल काष्ठा ctl_table_header *appldata_sysctl_header;
अटल काष्ठा ctl_table appldata_table[] = अणु
	अणु
		.procname	= "timer",
		.mode		= S_IRUGO | S_IWUSR,
		.proc_handler	= appldata_समयr_handler,
	पूर्ण,
	अणु
		.procname	= "interval",
		.mode		= S_IRUGO | S_IWUSR,
		.proc_handler	= appldata_पूर्णांकerval_handler,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table appldata_dir_table[] = अणु
	अणु
		.procname	= appldata_proc_name,
		.maxlen		= 0,
		.mode		= S_IRUGO | S_IXUGO,
		.child		= appldata_table,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

/*
 * Timer
 */
अटल काष्ठा vसमयr_list appldata_समयr;

अटल DEFINE_SPINLOCK(appldata_समयr_lock);
अटल पूर्णांक appldata_पूर्णांकerval = APPLDATA_CPU_INTERVAL;
अटल पूर्णांक appldata_समयr_active;
अटल पूर्णांक appldata_समयr_suspended = 0;

/*
 * Work queue
 */
अटल काष्ठा workqueue_काष्ठा *appldata_wq;
अटल व्योम appldata_work_fn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(appldata_work, appldata_work_fn);


/*
 * Ops list
 */
अटल DEFINE_MUTEX(appldata_ops_mutex);
अटल LIST_HEAD(appldata_ops_list);


/*************************** समयr, work, DIAG *******************************/
/*
 * appldata_समयr_function()
 *
 * schedule work and reschedule समयr
 */
अटल व्योम appldata_समयr_function(अचिन्हित दीर्घ data)
अणु
	queue_work(appldata_wq, (काष्ठा work_काष्ठा *) data);
पूर्ण

/*
 * appldata_work_fn()
 *
 * call data gathering function क्रम each (active) module
 */
अटल व्योम appldata_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा list_head *lh;
	काष्ठा appldata_ops *ops;

	mutex_lock(&appldata_ops_mutex);
	list_क्रम_each(lh, &appldata_ops_list) अणु
		ops = list_entry(lh, काष्ठा appldata_ops, list);
		अगर (ops->active == 1) अणु
			ops->callback(ops->data);
		पूर्ण
	पूर्ण
	mutex_unlock(&appldata_ops_mutex);
पूर्ण

अटल काष्ठा appldata_product_id appldata_id = अणु
	.prod_nr    = अणु0xD3, 0xC9, 0xD5, 0xE4,
		       0xE7, 0xD2, 0xD9पूर्ण,	/* "LINUXKR" */
	.prod_fn    = 0xD5D3,			/* "NL" */
	.version_nr = 0xF2F6,			/* "26" */
	.release_nr = 0xF0F1,			/* "01" */
पूर्ण;

/*
 * appldata_diag()
 *
 * prepare parameter list, issue DIAG 0xDC
 */
पूर्णांक appldata_diag(अक्षर record_nr, u16 function, अचिन्हित दीर्घ buffer,
			u16 length, अक्षर *mod_lvl)
अणु
	काष्ठा appldata_parameter_list *parm_list;
	काष्ठा appldata_product_id *id;
	पूर्णांक rc;

	parm_list = kदो_स्मृति(माप(*parm_list), GFP_KERNEL);
	id = kmemdup(&appldata_id, माप(appldata_id), GFP_KERNEL);
	rc = -ENOMEM;
	अगर (parm_list && id) अणु
		id->record_nr = record_nr;
		id->mod_lvl = (mod_lvl[0]) << 8 | mod_lvl[1];
		rc = appldata_यंत्र(parm_list, id, function,
				  (व्योम *) buffer, length);
	पूर्ण
	kमुक्त(id);
	kमुक्त(parm_list);
	वापस rc;
पूर्ण
/************************ समयr, work, DIAG <END> ****************************/


/****************************** /proc stuff **********************************/

#घोषणा APPLDATA_ADD_TIMER	0
#घोषणा APPLDATA_DEL_TIMER	1
#घोषणा APPLDATA_MOD_TIMER	2

/*
 * __appldata_vसमयr_setup()
 *
 * Add, delete or modअगरy भव समयrs on all online cpus.
 * The caller needs to get the appldata_समयr_lock spinlock.
 */
अटल व्योम __appldata_vसमयr_setup(पूर्णांक cmd)
अणु
	u64 समयr_पूर्णांकerval = (u64) appldata_पूर्णांकerval * 1000 * TOD_MICRO;

	चयन (cmd) अणु
	हाल APPLDATA_ADD_TIMER:
		अगर (appldata_समयr_active)
			अवरोध;
		appldata_समयr.expires = समयr_पूर्णांकerval;
		add_virt_समयr_periodic(&appldata_समयr);
		appldata_समयr_active = 1;
		अवरोध;
	हाल APPLDATA_DEL_TIMER:
		del_virt_समयr(&appldata_समयr);
		अगर (!appldata_समयr_active)
			अवरोध;
		appldata_समयr_active = 0;
		अवरोध;
	हाल APPLDATA_MOD_TIMER:
		अगर (!appldata_समयr_active)
			अवरोध;
		mod_virt_समयr_periodic(&appldata_समयr, समयr_पूर्णांकerval);
	पूर्ण
पूर्ण

/*
 * appldata_समयr_handler()
 *
 * Start/Stop समयr, show status of समयr (0 = not active, 1 = active)
 */
अटल पूर्णांक
appldata_समयr_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक समयr_active = appldata_समयr_active;
	पूर्णांक rc;
	काष्ठा ctl_table ctl_entry = अणु
		.procname	= ctl->procname,
		.data		= &समयr_active,
		.maxlen		= माप(पूर्णांक),
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण;

	rc = proc_करोuपूर्णांकvec_minmax(&ctl_entry, ग_लिखो, buffer, lenp, ppos);
	अगर (rc < 0 || !ग_लिखो)
		वापस rc;

	spin_lock(&appldata_समयr_lock);
	अगर (समयr_active)
		__appldata_vसमयr_setup(APPLDATA_ADD_TIMER);
	अन्यथा
		__appldata_vसमयr_setup(APPLDATA_DEL_TIMER);
	spin_unlock(&appldata_समयr_lock);
	वापस 0;
पूर्ण

/*
 * appldata_पूर्णांकerval_handler()
 *
 * Set (CPU) समयr पूर्णांकerval क्रम collection of data (in milliseconds), show
 * current समयr पूर्णांकerval.
 */
अटल पूर्णांक
appldata_पूर्णांकerval_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक पूर्णांकerval = appldata_पूर्णांकerval;
	पूर्णांक rc;
	काष्ठा ctl_table ctl_entry = अणु
		.procname	= ctl->procname,
		.data		= &पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.extra1		= SYSCTL_ONE,
	पूर्ण;

	rc = proc_करोपूर्णांकvec_minmax(&ctl_entry, ग_लिखो, buffer, lenp, ppos);
	अगर (rc < 0 || !ग_लिखो)
		वापस rc;

	spin_lock(&appldata_समयr_lock);
	appldata_पूर्णांकerval = पूर्णांकerval;
	__appldata_vसमयr_setup(APPLDATA_MOD_TIMER);
	spin_unlock(&appldata_समयr_lock);
	वापस 0;
पूर्ण

/*
 * appldata_generic_handler()
 *
 * Generic start/stop monitoring and DIAG, show status of
 * monitoring (0 = not in process, 1 = in process)
 */
अटल पूर्णांक
appldata_generic_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा appldata_ops *ops = शून्य, *पंचांगp_ops;
	काष्ठा list_head *lh;
	पूर्णांक rc, found;
	पूर्णांक active;
	काष्ठा ctl_table ctl_entry = अणु
		.data		= &active,
		.maxlen		= माप(पूर्णांक),
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण;

	found = 0;
	mutex_lock(&appldata_ops_mutex);
	list_क्रम_each(lh, &appldata_ops_list) अणु
		पंचांगp_ops = list_entry(lh, काष्ठा appldata_ops, list);
		अगर (&पंचांगp_ops->ctl_table[2] == ctl) अणु
			found = 1;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		mutex_unlock(&appldata_ops_mutex);
		वापस -ENODEV;
	पूर्ण
	ops = ctl->data;
	अगर (!try_module_get(ops->owner)) अणु	// protect this function
		mutex_unlock(&appldata_ops_mutex);
		वापस -ENODEV;
	पूर्ण
	mutex_unlock(&appldata_ops_mutex);

	active = ops->active;
	rc = proc_करोuपूर्णांकvec_minmax(&ctl_entry, ग_लिखो, buffer, lenp, ppos);
	अगर (rc < 0 || !ग_लिखो) अणु
		module_put(ops->owner);
		वापस rc;
	पूर्ण

	mutex_lock(&appldata_ops_mutex);
	अगर (active && (ops->active == 0)) अणु
		// protect work queue callback
		अगर (!try_module_get(ops->owner)) अणु
			mutex_unlock(&appldata_ops_mutex);
			module_put(ops->owner);
			वापस -ENODEV;
		पूर्ण
		ops->callback(ops->data);	// init record
		rc = appldata_diag(ops->record_nr,
					APPLDATA_START_INTERVAL_REC,
					(अचिन्हित दीर्घ) ops->data, ops->size,
					ops->mod_lvl);
		अगर (rc != 0) अणु
			pr_err("Starting the data collection for %s "
			       "failed with rc=%d\n", ops->name, rc);
			module_put(ops->owner);
		पूर्ण अन्यथा
			ops->active = 1;
	पूर्ण अन्यथा अगर (!active && (ops->active == 1)) अणु
		ops->active = 0;
		rc = appldata_diag(ops->record_nr, APPLDATA_STOP_REC,
				(अचिन्हित दीर्घ) ops->data, ops->size,
				ops->mod_lvl);
		अगर (rc != 0)
			pr_err("Stopping the data collection for %s "
			       "failed with rc=%d\n", ops->name, rc);
		module_put(ops->owner);
	पूर्ण
	mutex_unlock(&appldata_ops_mutex);
	module_put(ops->owner);
	वापस 0;
पूर्ण

/*************************** /proc stuff <END> *******************************/


/************************* module-ops management *****************************/
/*
 * appldata_रेजिस्टर_ops()
 *
 * update ops list, रेजिस्टर /proc/sys entries
 */
पूर्णांक appldata_रेजिस्टर_ops(काष्ठा appldata_ops *ops)
अणु
	अगर (ops->size > APPLDATA_MAX_REC_SIZE)
		वापस -EINVAL;

	ops->ctl_table = kसुस्मृति(4, माप(काष्ठा ctl_table), GFP_KERNEL);
	अगर (!ops->ctl_table)
		वापस -ENOMEM;

	mutex_lock(&appldata_ops_mutex);
	list_add(&ops->list, &appldata_ops_list);
	mutex_unlock(&appldata_ops_mutex);

	ops->ctl_table[0].procname = appldata_proc_name;
	ops->ctl_table[0].maxlen   = 0;
	ops->ctl_table[0].mode     = S_IRUGO | S_IXUGO;
	ops->ctl_table[0].child    = &ops->ctl_table[2];

	ops->ctl_table[2].procname = ops->name;
	ops->ctl_table[2].mode     = S_IRUGO | S_IWUSR;
	ops->ctl_table[2].proc_handler = appldata_generic_handler;
	ops->ctl_table[2].data = ops;

	ops->sysctl_header = रेजिस्टर_sysctl_table(ops->ctl_table);
	अगर (!ops->sysctl_header)
		जाओ out;
	वापस 0;
out:
	mutex_lock(&appldata_ops_mutex);
	list_del(&ops->list);
	mutex_unlock(&appldata_ops_mutex);
	kमुक्त(ops->ctl_table);
	वापस -ENOMEM;
पूर्ण

/*
 * appldata_unरेजिस्टर_ops()
 *
 * update ops list, unरेजिस्टर /proc entries, stop DIAG अगर necessary
 */
व्योम appldata_unरेजिस्टर_ops(काष्ठा appldata_ops *ops)
अणु
	mutex_lock(&appldata_ops_mutex);
	list_del(&ops->list);
	mutex_unlock(&appldata_ops_mutex);
	unरेजिस्टर_sysctl_table(ops->sysctl_header);
	kमुक्त(ops->ctl_table);
पूर्ण
/********************** module-ops management <END> **************************/


/**************************** suspend / resume *******************************/
अटल पूर्णांक appldata_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा appldata_ops *ops;
	पूर्णांक rc;
	काष्ठा list_head *lh;

	spin_lock(&appldata_समयr_lock);
	अगर (appldata_समयr_active) अणु
		__appldata_vसमयr_setup(APPLDATA_DEL_TIMER);
		appldata_समयr_suspended = 1;
	पूर्ण
	spin_unlock(&appldata_समयr_lock);

	mutex_lock(&appldata_ops_mutex);
	list_क्रम_each(lh, &appldata_ops_list) अणु
		ops = list_entry(lh, काष्ठा appldata_ops, list);
		अगर (ops->active == 1) अणु
			rc = appldata_diag(ops->record_nr, APPLDATA_STOP_REC,
					(अचिन्हित दीर्घ) ops->data, ops->size,
					ops->mod_lvl);
			अगर (rc != 0)
				pr_err("Stopping the data collection for %s "
				       "failed with rc=%d\n", ops->name, rc);
		पूर्ण
	पूर्ण
	mutex_unlock(&appldata_ops_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक appldata_restore(काष्ठा device *dev)
अणु
	काष्ठा appldata_ops *ops;
	पूर्णांक rc;
	काष्ठा list_head *lh;

	spin_lock(&appldata_समयr_lock);
	अगर (appldata_समयr_suspended) अणु
		__appldata_vसमयr_setup(APPLDATA_ADD_TIMER);
		appldata_समयr_suspended = 0;
	पूर्ण
	spin_unlock(&appldata_समयr_lock);

	mutex_lock(&appldata_ops_mutex);
	list_क्रम_each(lh, &appldata_ops_list) अणु
		ops = list_entry(lh, काष्ठा appldata_ops, list);
		अगर (ops->active == 1) अणु
			ops->callback(ops->data);	// init record
			rc = appldata_diag(ops->record_nr,
					APPLDATA_START_INTERVAL_REC,
					(अचिन्हित दीर्घ) ops->data, ops->size,
					ops->mod_lvl);
			अगर (rc != 0) अणु
				pr_err("Starting the data collection for %s "
				       "failed with rc=%d\n", ops->name, rc);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&appldata_ops_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक appldata_thaw(काष्ठा device *dev)
अणु
	वापस appldata_restore(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops appldata_pm_ops = अणु
	.मुक्तze		= appldata_मुक्तze,
	.thaw		= appldata_thaw,
	.restore	= appldata_restore,
पूर्ण;

अटल काष्ठा platक्रमm_driver appldata_pdrv = अणु
	.driver = अणु
		.name	= "appldata",
		.pm	= &appldata_pm_ops,
	पूर्ण,
पूर्ण;
/************************* suspend / resume <END> ****************************/


/******************************* init / निकास *********************************/

/*
 * appldata_init()
 *
 * init समयr, रेजिस्टर /proc entries
 */
अटल पूर्णांक __init appldata_init(व्योम)
अणु
	पूर्णांक rc;

	init_virt_समयr(&appldata_समयr);
	appldata_समयr.function = appldata_समयr_function;
	appldata_समयr.data = (अचिन्हित दीर्घ) &appldata_work;

	rc = platक्रमm_driver_रेजिस्टर(&appldata_pdrv);
	अगर (rc)
		वापस rc;

	appldata_pdev = platक्रमm_device_रेजिस्टर_simple("appldata", -1, शून्य,
							0);
	अगर (IS_ERR(appldata_pdev)) अणु
		rc = PTR_ERR(appldata_pdev);
		जाओ out_driver;
	पूर्ण
	appldata_wq = alloc_ordered_workqueue("appldata", 0);
	अगर (!appldata_wq) अणु
		rc = -ENOMEM;
		जाओ out_device;
	पूर्ण

	appldata_sysctl_header = रेजिस्टर_sysctl_table(appldata_dir_table);
	वापस 0;

out_device:
	platक्रमm_device_unरेजिस्टर(appldata_pdev);
out_driver:
	platक्रमm_driver_unरेजिस्टर(&appldata_pdrv);
	वापस rc;
पूर्ण

__initcall(appldata_init);

/**************************** init / निकास <END> ******************************/

EXPORT_SYMBOL_GPL(appldata_रेजिस्टर_ops);
EXPORT_SYMBOL_GPL(appldata_unरेजिस्टर_ops);
EXPORT_SYMBOL_GPL(appldata_diag);

#अगर_घोषित CONFIG_SWAP
EXPORT_SYMBOL_GPL(si_swapinfo);
#पूर्ण_अगर
EXPORT_SYMBOL_GPL(nr_thपढ़ोs);
EXPORT_SYMBOL_GPL(nr_running);
EXPORT_SYMBOL_GPL(nr_ioरुको);
