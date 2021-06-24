<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>

#समावेश "kfd_priv.h"
#समावेश "cik_regs.h"
#समावेश "kfd_pm4_headers.h"
#समावेश "kfd_pm4_headers_diq.h"
#समावेश "kfd_dbgmgr.h"
#समावेश "kfd_dbgdev.h"
#समावेश "kfd_device_queue_manager.h"

अटल DEFINE_MUTEX(kfd_dbgmgr_mutex);

काष्ठा mutex *kfd_get_dbgmgr_mutex(व्योम)
अणु
	वापस &kfd_dbgmgr_mutex;
पूर्ण


अटल व्योम kfd_dbgmgr_uninitialize(काष्ठा kfd_dbgmgr *pmgr)
अणु
	kमुक्त(pmgr->dbgdev);

	pmgr->dbgdev = शून्य;
	pmgr->pasid = 0;
	pmgr->dev = शून्य;
पूर्ण

व्योम kfd_dbgmgr_destroy(काष्ठा kfd_dbgmgr *pmgr)
अणु
	अगर (pmgr) अणु
		kfd_dbgmgr_uninitialize(pmgr);
		kमुक्त(pmgr);
	पूर्ण
पूर्ण

bool kfd_dbgmgr_create(काष्ठा kfd_dbgmgr **ppmgr, काष्ठा kfd_dev *pdev)
अणु
	क्रमागत DBGDEV_TYPE type = DBGDEV_TYPE_DIQ;
	काष्ठा kfd_dbgmgr *new_buff;

	अगर (WARN_ON(!pdev->init_complete))
		वापस false;

	new_buff = kfd_alloc_काष्ठा(new_buff);
	अगर (!new_buff) अणु
		pr_err("Failed to allocate dbgmgr instance\n");
		वापस false;
	पूर्ण

	new_buff->pasid = 0;
	new_buff->dev = pdev;
	new_buff->dbgdev = kfd_alloc_काष्ठा(new_buff->dbgdev);
	अगर (!new_buff->dbgdev) अणु
		pr_err("Failed to allocate dbgdev instance\n");
		kमुक्त(new_buff);
		वापस false;
	पूर्ण

	/* get actual type of DBGDevice cpsch or not */
	अगर (pdev->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS)
		type = DBGDEV_TYPE_NODIQ;

	kfd_dbgdev_init(new_buff->dbgdev, pdev, type);
	*ppmgr = new_buff;

	वापस true;
पूर्ण

दीर्घ kfd_dbgmgr_रेजिस्टर(काष्ठा kfd_dbgmgr *pmgr, काष्ठा kfd_process *p)
अणु
	अगर (pmgr->pasid != 0) अणु
		pr_debug("H/W debugger is already active using pasid 0x%x\n",
				pmgr->pasid);
		वापस -EBUSY;
	पूर्ण

	/* remember pasid */
	pmgr->pasid = p->pasid;

	/* provide the pqm क्रम diq generation */
	pmgr->dbgdev->pqm = &p->pqm;

	/* activate the actual रेजिस्टरing */
	pmgr->dbgdev->dbgdev_रेजिस्टर(pmgr->dbgdev);

	वापस 0;
पूर्ण

दीर्घ kfd_dbgmgr_unरेजिस्टर(काष्ठा kfd_dbgmgr *pmgr, काष्ठा kfd_process *p)
अणु
	/* Is the requests coming from the alपढ़ोy रेजिस्टरed process? */
	अगर (pmgr->pasid != p->pasid) अणु
		pr_debug("H/W debugger is not registered by calling pasid 0x%x\n",
				p->pasid);
		वापस -EINVAL;
	पूर्ण

	pmgr->dbgdev->dbgdev_unरेजिस्टर(pmgr->dbgdev);

	pmgr->pasid = 0;

	वापस 0;
पूर्ण

दीर्घ kfd_dbgmgr_wave_control(काष्ठा kfd_dbgmgr *pmgr,
				काष्ठा dbg_wave_control_info *wac_info)
अणु
	/* Is the requests coming from the alपढ़ोy रेजिस्टरed process? */
	अगर (pmgr->pasid != wac_info->process->pasid) अणु
		pr_debug("H/W debugger support was not registered for requester pasid 0x%x\n",
				wac_info->process->pasid);
		वापस -EINVAL;
	पूर्ण

	वापस (दीर्घ) pmgr->dbgdev->dbgdev_wave_control(pmgr->dbgdev, wac_info);
पूर्ण

दीर्घ kfd_dbgmgr_address_watch(काष्ठा kfd_dbgmgr *pmgr,
				काष्ठा dbg_address_watch_info *adw_info)
अणु
	/* Is the requests coming from the alपढ़ोy रेजिस्टरed process? */
	अगर (pmgr->pasid != adw_info->process->pasid) अणु
		pr_debug("H/W debugger support was not registered for requester pasid 0x%x\n",
				adw_info->process->pasid);
		वापस -EINVAL;
	पूर्ण

	वापस (दीर्घ) pmgr->dbgdev->dbgdev_address_watch(pmgr->dbgdev,
							adw_info);
पूर्ण

