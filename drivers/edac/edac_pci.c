<शैली गुरु>
/*
 * EDAC PCI component
 *
 * Author: Dave Jiang <djiang@mvista.com>
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 */
#समावेश <यंत्र/page.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/समयr.h>

#समावेश "edac_pci.h"
#समावेश "edac_module.h"

अटल DEFINE_MUTEX(edac_pci_ctls_mutex);
अटल LIST_HEAD(edac_pci_list);
अटल atomic_t pci_indexes = ATOMIC_INIT(0);

काष्ठा edac_pci_ctl_info *edac_pci_alloc_ctl_info(अचिन्हित पूर्णांक sz_pvt,
						स्थिर अक्षर *edac_pci_name)
अणु
	काष्ठा edac_pci_ctl_info *pci;
	व्योम *p = शून्य, *pvt;
	अचिन्हित पूर्णांक size;

	edac_dbg(1, "\n");

	pci = edac_align_ptr(&p, माप(*pci), 1);
	pvt = edac_align_ptr(&p, 1, sz_pvt);
	size = ((अचिन्हित दीर्घ)pvt) + sz_pvt;

	/* Alloc the needed control काष्ठा memory */
	pci = kzalloc(size, GFP_KERNEL);
	अगर (pci  == शून्य)
		वापस शून्य;

	/* Now much निजी space */
	pvt = sz_pvt ? ((अक्षर *)pci) + ((अचिन्हित दीर्घ)pvt) : शून्य;

	pci->pvt_info = pvt;
	pci->op_state = OP_ALLOC;

	snम_लिखो(pci->name, म_माप(edac_pci_name) + 1, "%s", edac_pci_name);

	वापस pci;
पूर्ण
EXPORT_SYMBOL_GPL(edac_pci_alloc_ctl_info);

व्योम edac_pci_मुक्त_ctl_info(काष्ठा edac_pci_ctl_info *pci)
अणु
	edac_dbg(1, "\n");

	edac_pci_हटाओ_sysfs(pci);
पूर्ण
EXPORT_SYMBOL_GPL(edac_pci_मुक्त_ctl_info);

/*
 * find_edac_pci_by_dev()
 * 	scans the edac_pci list क्रम a specअगरic 'struct device *'
 *
 *	वापस शून्य अगर not found, or वापस control काष्ठा poपूर्णांकer
 */
अटल काष्ठा edac_pci_ctl_info *find_edac_pci_by_dev(काष्ठा device *dev)
अणु
	काष्ठा edac_pci_ctl_info *pci;
	काष्ठा list_head *item;

	edac_dbg(1, "\n");

	list_क्रम_each(item, &edac_pci_list) अणु
		pci = list_entry(item, काष्ठा edac_pci_ctl_info, link);

		अगर (pci->dev == dev)
			वापस pci;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * add_edac_pci_to_global_list
 * 	Beक्रमe calling this function, caller must assign a unique value to
 * 	edac_dev->pci_idx.
 * 	Return:
 * 		0 on success
 * 		1 on failure
 */
अटल पूर्णांक add_edac_pci_to_global_list(काष्ठा edac_pci_ctl_info *pci)
अणु
	काष्ठा list_head *item, *insert_beक्रमe;
	काष्ठा edac_pci_ctl_info *rover;

	edac_dbg(1, "\n");

	insert_beक्रमe = &edac_pci_list;

	/* Determine अगर alपढ़ोy on the list */
	rover = find_edac_pci_by_dev(pci->dev);
	अगर (unlikely(rover != शून्य))
		जाओ fail0;

	/* Insert in ascending order by 'pci_idx', so find position */
	list_क्रम_each(item, &edac_pci_list) अणु
		rover = list_entry(item, काष्ठा edac_pci_ctl_info, link);

		अगर (rover->pci_idx >= pci->pci_idx) अणु
			अगर (unlikely(rover->pci_idx == pci->pci_idx))
				जाओ fail1;

			insert_beक्रमe = item;
			अवरोध;
		पूर्ण
	पूर्ण

	list_add_tail_rcu(&pci->link, insert_beक्रमe);
	वापस 0;

fail0:
	edac_prपूर्णांकk(KERN_WARNING, EDAC_PCI,
		"%s (%s) %s %s already assigned %d\n",
		dev_name(rover->dev), edac_dev_name(rover),
		rover->mod_name, rover->ctl_name, rover->pci_idx);
	वापस 1;

fail1:
	edac_prपूर्णांकk(KERN_WARNING, EDAC_PCI,
		"but in low-level driver: attempt to assign\n"
		"\tduplicate pci_idx %d in %s()\n", rover->pci_idx,
		__func__);
	वापस 1;
पूर्ण

/*
 * del_edac_pci_from_global_list
 *
 *	हटाओ the PCI control काष्ठा from the global list
 */
अटल व्योम del_edac_pci_from_global_list(काष्ठा edac_pci_ctl_info *pci)
अणु
	list_del_rcu(&pci->link);

	/* these are क्रम safe removal of devices from global list जबतक
	 * NMI handlers may be traversing list
	 */
	synchronize_rcu();
	INIT_LIST_HEAD(&pci->link);
पूर्ण

/*
 * edac_pci_workq_function()
 *
 * 	periodic function that perक्रमms the operation
 *	scheduled by a workq request, क्रम a given PCI control काष्ठा
 */
अटल व्योम edac_pci_workq_function(काष्ठा work_काष्ठा *work_req)
अणु
	काष्ठा delayed_work *d_work = to_delayed_work(work_req);
	काष्ठा edac_pci_ctl_info *pci = to_edac_pci_ctl_work(d_work);
	पूर्णांक msec;
	अचिन्हित दीर्घ delay;

	edac_dbg(3, "checking\n");

	mutex_lock(&edac_pci_ctls_mutex);

	अगर (pci->op_state != OP_RUNNING_POLL) अणु
		mutex_unlock(&edac_pci_ctls_mutex);
		वापस;
	पूर्ण

	अगर (edac_pci_get_check_errors())
		pci->edac_check(pci);

	/* अगर we are on a one second period, then use round */
	msec = edac_pci_get_poll_msec();
	अगर (msec == 1000)
		delay = round_jअगरfies_relative(msecs_to_jअगरfies(msec));
	अन्यथा
		delay = msecs_to_jअगरfies(msec);

	edac_queue_work(&pci->work, delay);

	mutex_unlock(&edac_pci_ctls_mutex);
पूर्ण

पूर्णांक edac_pci_alloc_index(व्योम)
अणु
	वापस atomic_inc_वापस(&pci_indexes) - 1;
पूर्ण
EXPORT_SYMBOL_GPL(edac_pci_alloc_index);

पूर्णांक edac_pci_add_device(काष्ठा edac_pci_ctl_info *pci, पूर्णांक edac_idx)
अणु
	edac_dbg(0, "\n");

	pci->pci_idx = edac_idx;
	pci->start_समय = jअगरfies;

	mutex_lock(&edac_pci_ctls_mutex);

	अगर (add_edac_pci_to_global_list(pci))
		जाओ fail0;

	अगर (edac_pci_create_sysfs(pci)) अणु
		edac_pci_prपूर्णांकk(pci, KERN_WARNING,
				"failed to create sysfs pci\n");
		जाओ fail1;
	पूर्ण

	अगर (pci->edac_check) अणु
		pci->op_state = OP_RUNNING_POLL;

		INIT_DELAYED_WORK(&pci->work, edac_pci_workq_function);
		edac_queue_work(&pci->work, msecs_to_jअगरfies(edac_pci_get_poll_msec()));

	पूर्ण अन्यथा अणु
		pci->op_state = OP_RUNNING_INTERRUPT;
	पूर्ण

	edac_pci_prपूर्णांकk(pci, KERN_INFO,
		"Giving out device to module %s controller %s: DEV %s (%s)\n",
		pci->mod_name, pci->ctl_name, pci->dev_name,
		edac_op_state_to_string(pci->op_state));

	mutex_unlock(&edac_pci_ctls_mutex);
	वापस 0;

	/* error unwind stack */
fail1:
	del_edac_pci_from_global_list(pci);
fail0:
	mutex_unlock(&edac_pci_ctls_mutex);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(edac_pci_add_device);

काष्ठा edac_pci_ctl_info *edac_pci_del_device(काष्ठा device *dev)
अणु
	काष्ठा edac_pci_ctl_info *pci;

	edac_dbg(0, "\n");

	mutex_lock(&edac_pci_ctls_mutex);

	/* ensure the control काष्ठा is on the global list
	 * अगर not, then leave
	 */
	pci = find_edac_pci_by_dev(dev);
	अगर (pci  == शून्य) अणु
		mutex_unlock(&edac_pci_ctls_mutex);
		वापस शून्य;
	पूर्ण

	pci->op_state = OP_OFFLINE;

	del_edac_pci_from_global_list(pci);

	mutex_unlock(&edac_pci_ctls_mutex);

	अगर (pci->edac_check)
		edac_stop_work(&pci->work);

	edac_prपूर्णांकk(KERN_INFO, EDAC_PCI,
		"Removed device %d for %s %s: DEV %s\n",
		pci->pci_idx, pci->mod_name, pci->ctl_name, edac_dev_name(pci));

	वापस pci;
पूर्ण
EXPORT_SYMBOL_GPL(edac_pci_del_device);

/*
 * edac_pci_generic_check
 *
 *	a Generic parity check API
 */
अटल व्योम edac_pci_generic_check(काष्ठा edac_pci_ctl_info *pci)
अणु
	edac_dbg(4, "\n");
	edac_pci_करो_parity_check();
पूर्ण

/* मुक्त running instance index counter */
अटल पूर्णांक edac_pci_idx;
#घोषणा EDAC_PCI_GENCTL_NAME	"EDAC PCI controller"

काष्ठा edac_pci_gen_data अणु
	पूर्णांक edac_idx;
पूर्ण;

काष्ठा edac_pci_ctl_info *edac_pci_create_generic_ctl(काष्ठा device *dev,
						स्थिर अक्षर *mod_name)
अणु
	काष्ठा edac_pci_ctl_info *pci;
	काष्ठा edac_pci_gen_data *pdata;

	pci = edac_pci_alloc_ctl_info(माप(*pdata), EDAC_PCI_GENCTL_NAME);
	अगर (!pci)
		वापस शून्य;

	pdata = pci->pvt_info;
	pci->dev = dev;
	dev_set_drvdata(pci->dev, pci);
	pci->dev_name = pci_name(to_pci_dev(dev));

	pci->mod_name = mod_name;
	pci->ctl_name = EDAC_PCI_GENCTL_NAME;
	अगर (edac_op_state == EDAC_OPSTATE_POLL)
		pci->edac_check = edac_pci_generic_check;

	pdata->edac_idx = edac_pci_idx++;

	अगर (edac_pci_add_device(pci, pdata->edac_idx) > 0) अणु
		edac_dbg(3, "failed edac_pci_add_device()\n");
		edac_pci_मुक्त_ctl_info(pci);
		वापस शून्य;
	पूर्ण

	वापस pci;
पूर्ण
EXPORT_SYMBOL_GPL(edac_pci_create_generic_ctl);

व्योम edac_pci_release_generic_ctl(काष्ठा edac_pci_ctl_info *pci)
अणु
	edac_dbg(0, "pci mod=%s\n", pci->mod_name);

	edac_pci_del_device(pci->dev);
	edac_pci_मुक्त_ctl_info(pci);
पूर्ण
EXPORT_SYMBOL_GPL(edac_pci_release_generic_ctl);
