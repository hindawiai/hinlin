<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

/*
 *  bfad.c Linux driver PCI पूर्णांकerface module.
 */
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/fcntl.h>

#समावेश "bfad_drv.h"
#समावेश "bfad_im.h"
#समावेश "bfa_fcs.h"
#समावेश "bfa_defs.h"
#समावेश "bfa.h"

BFA_TRC_खाता(LDRV, BFAD);
DEFINE_MUTEX(bfad_mutex);
LIST_HEAD(bfad_list);

अटल पूर्णांक	bfad_inst;
अटल पूर्णांक      num_sgpgs_parm;
पूर्णांक		supported_fc4s;
अक्षर		*host_name, *os_name, *os_patch;
पूर्णांक		num_rports, num_ios, num_पंचांगs;
पूर्णांक		num_fcxps, num_ufbufs;
पूर्णांक		reqq_size, rspq_size, num_sgpgs;
पूर्णांक		rport_del_समयout = BFA_FCS_RPORT_DEF_DEL_TIMEOUT;
पूर्णांक		bfa_lun_queue_depth = BFAD_LUN_QUEUE_DEPTH;
पूर्णांक		bfa_io_max_sge = BFAD_IO_MAX_SGE;
पूर्णांक		bfa_log_level = 3; /* WARNING log level */
पूर्णांक		ioc_स्वतः_recover = BFA_TRUE;
पूर्णांक		bfa_linkup_delay = -1;
पूर्णांक		fdmi_enable = BFA_TRUE;
पूर्णांक		pcie_max_पढ़ो_reqsz;
पूर्णांक		bfa_debugfs_enable = 1;
पूर्णांक		msix_disable_cb = 0, msix_disable_ct = 0;
पूर्णांक		max_xfer_size = BFAD_MAX_SECTORS >> 1;
अटल पूर्णांक	max_rport_logins = BFA_FCS_MAX_RPORT_LOGINS;

/* Firmware releated */
u32	bfi_image_cb_size, bfi_image_ct_size, bfi_image_ct2_size;
u32	*bfi_image_cb, *bfi_image_ct, *bfi_image_ct2;

#घोषणा BFAD_FW_खाता_CB		"cbfw-3.2.5.1.bin"
#घोषणा BFAD_FW_खाता_CT		"ctfw-3.2.5.1.bin"
#घोषणा BFAD_FW_खाता_CT2	"ct2fw-3.2.5.1.bin"

अटल u32 *bfad_load_fwimg(काष्ठा pci_dev *pdev);
अटल व्योम bfad_मुक्त_fwimg(व्योम);
अटल व्योम bfad_पढ़ो_firmware(काष्ठा pci_dev *pdev, u32 **bfi_image,
		u32 *bfi_image_size, अक्षर *fw_name);

अटल स्थिर अक्षर *msix_name_ct[] = अणु
	"ctrl",
	"cpe0", "cpe1", "cpe2", "cpe3",
	"rme0", "rme1", "rme2", "rme3" पूर्ण;

अटल स्थिर अक्षर *msix_name_cb[] = अणु
	"cpe0", "cpe1", "cpe2", "cpe3",
	"rme0", "rme1", "rme2", "rme3",
	"eemc", "elpu0", "elpu1", "epss", "mlpu" पूर्ण;

MODULE_FIRMWARE(BFAD_FW_खाता_CB);
MODULE_FIRMWARE(BFAD_FW_खाता_CT);
MODULE_FIRMWARE(BFAD_FW_खाता_CT2);

module_param(os_name, अक्षरp, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(os_name, "OS name of the hba host machine");
module_param(os_patch, अक्षरp, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(os_patch, "OS patch level of the hba host machine");
module_param(host_name, अक्षरp, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(host_name, "Hostname of the hba host machine");
module_param(num_rports, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(num_rports, "Max number of rports supported per port "
				"(physical/logical), default=1024");
module_param(num_ios, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(num_ios, "Max number of ioim requests, default=2000");
module_param(num_पंचांगs, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(num_पंचांगs, "Max number of task im requests, default=128");
module_param(num_fcxps, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(num_fcxps, "Max number of fcxp requests, default=64");
module_param(num_ufbufs, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(num_ufbufs, "Max number of unsolicited frame "
				"buffers, default=64");
module_param(reqq_size, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(reqq_size, "Max number of request queue elements, "
				"default=256");
module_param(rspq_size, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(rspq_size, "Max number of response queue elements, "
				"default=64");
module_param(num_sgpgs, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(num_sgpgs, "Number of scatter/gather pages, default=2048");
module_param(rport_del_समयout, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(rport_del_समयout, "Rport delete timeout, default=90 secs, "
					"Range[>0]");
module_param(bfa_lun_queue_depth, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(bfa_lun_queue_depth, "Lun queue depth, default=32, Range[>0]");
module_param(bfa_io_max_sge, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(bfa_io_max_sge, "Max io scatter/gather elements, default=255");
module_param(bfa_log_level, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(bfa_log_level, "Driver log level, default=3, "
				"Range[Critical:1|Error:2|Warning:3|Info:4]");
module_param(ioc_स्वतः_recover, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(ioc_स्वतः_recover, "IOC auto recovery, default=1, "
				"Range[off:0|on:1]");
module_param(bfa_linkup_delay, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(bfa_linkup_delay, "Link up delay, default=30 secs for "
			"boot port. Otherwise 10 secs in RHEL4 & 0 for "
			"[RHEL5, SLES10, ESX40] Range[>0]");
module_param(msix_disable_cb, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(msix_disable_cb, "Disable Message Signaled Interrupts for QLogic-415/425/815/825 cards, default=0 Range[false:0|true:1]");
module_param(msix_disable_ct, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(msix_disable_ct, "Disable Message Signaled Interrupts if possible for QLogic-1010/1020/804/1007/902/1741 cards, default=0, Range[false:0|true:1]");
module_param(fdmi_enable, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(fdmi_enable, "Enables fdmi registration, default=1, "
				"Range[false:0|true:1]");
module_param(pcie_max_पढ़ो_reqsz, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(pcie_max_पढ़ो_reqsz, "PCIe max read request size, default=0 "
		"(use system setting), Range[128|256|512|1024|2048|4096]");
module_param(bfa_debugfs_enable, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(bfa_debugfs_enable, "Enables debugfs feature, default=1,"
		" Range[false:0|true:1]");
module_param(max_xfer_size, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(max_xfer_size, "default=32MB,"
		" Range[64k|128k|256k|512k|1024k|2048k]");
module_param(max_rport_logins, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(max_rport_logins, "Max number of logins to initiator and target rports on a port (physical/logical), default=1024");

अटल व्योम
bfad_sm_uninit(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event);
अटल व्योम
bfad_sm_created(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event);
अटल व्योम
bfad_sm_initializing(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event);
अटल व्योम
bfad_sm_operational(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event);
अटल व्योम
bfad_sm_stopping(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event);
अटल व्योम
bfad_sm_failed(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event);
अटल व्योम
bfad_sm_fcs_निकास(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event);

/*
 * Beginning state क्रम the driver instance, aरुकोing the pci_probe event
 */
अटल व्योम
bfad_sm_uninit(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event)
अणु
	bfa_trc(bfad, event);

	चयन (event) अणु
	हाल BFAD_E_CREATE:
		bfa_sm_set_state(bfad, bfad_sm_created);
		bfad->bfad_tsk = kthपढ़ो_create(bfad_worker, (व्योम *) bfad,
						"%s", "bfad_worker");
		अगर (IS_ERR(bfad->bfad_tsk)) अणु
			prपूर्णांकk(KERN_INFO "bfad[%d]: Kernel thread "
				"creation failed!\n", bfad->inst_no);
			bfa_sm_send_event(bfad, BFAD_E_KTHREAD_CREATE_FAILED);
		पूर्ण
		bfa_sm_send_event(bfad, BFAD_E_INIT);
		अवरोध;

	हाल BFAD_E_STOP:
		/* Ignore stop; alपढ़ोy in uninit */
		अवरोध;

	शेष:
		bfa_sm_fault(bfad, event);
	पूर्ण
पूर्ण

/*
 * Driver Instance is created, aरुकोing event INIT to initialize the bfad
 */
अटल व्योम
bfad_sm_created(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event)
अणु
	अचिन्हित दीर्घ flags;
	bfa_status_t ret;

	bfa_trc(bfad, event);

	चयन (event) अणु
	हाल BFAD_E_INIT:
		bfa_sm_set_state(bfad, bfad_sm_initializing);

		init_completion(&bfad->comp);

		/* Enable Interrupt and रुको bfa_init completion */
		अगर (bfad_setup_पूर्णांकr(bfad)) अणु
			prपूर्णांकk(KERN_WARNING "bfad%d: bfad_setup_intr failed\n",
					bfad->inst_no);
			bfa_sm_send_event(bfad, BFAD_E_INIT_FAILED);
			अवरोध;
		पूर्ण

		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfa_iocfc_init(&bfad->bfa);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);

		/* Set up पूर्णांकerrupt handler क्रम each vectors */
		अगर ((bfad->bfad_flags & BFAD_MSIX_ON) &&
			bfad_install_msix_handler(bfad)) अणु
			prपूर्णांकk(KERN_WARNING "%s: install_msix failed, bfad%d\n",
				__func__, bfad->inst_no);
		पूर्ण

		bfad_init_समयr(bfad);

		रुको_क्रम_completion(&bfad->comp);

		अगर ((bfad->bfad_flags & BFAD_HAL_INIT_DONE)) अणु
			bfa_sm_send_event(bfad, BFAD_E_INIT_SUCCESS);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING
				"bfa %s: bfa init failed\n",
				bfad->pci_name);
			spin_lock_irqsave(&bfad->bfad_lock, flags);
			bfa_fcs_init(&bfad->bfa_fcs);
			spin_unlock_irqrestore(&bfad->bfad_lock, flags);

			ret = bfad_cfg_pport(bfad, BFA_LPORT_ROLE_FCP_IM);
			अगर (ret != BFA_STATUS_OK) अणु
				init_completion(&bfad->comp);

				spin_lock_irqsave(&bfad->bfad_lock, flags);
				bfad->pport.flags |= BFAD_PORT_DELETE;
				bfa_fcs_निकास(&bfad->bfa_fcs);
				spin_unlock_irqrestore(&bfad->bfad_lock, flags);

				रुको_क्रम_completion(&bfad->comp);

				bfa_sm_send_event(bfad, BFAD_E_INIT_FAILED);
				अवरोध;
			पूर्ण
			bfad->bfad_flags |= BFAD_HAL_INIT_FAIL;
			bfa_sm_send_event(bfad, BFAD_E_HAL_INIT_FAILED);
		पूर्ण

		अवरोध;

	हाल BFAD_E_KTHREAD_CREATE_FAILED:
		bfa_sm_set_state(bfad, bfad_sm_uninit);
		अवरोध;

	शेष:
		bfa_sm_fault(bfad, event);
	पूर्ण
पूर्ण

अटल व्योम
bfad_sm_initializing(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event)
अणु
	पूर्णांक	retval;
	अचिन्हित दीर्घ	flags;

	bfa_trc(bfad, event);

	चयन (event) अणु
	हाल BFAD_E_INIT_SUCCESS:
		kthपढ़ो_stop(bfad->bfad_tsk);
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_tsk = शून्य;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);

		retval = bfad_start_ops(bfad);
		अगर (retval != BFA_STATUS_OK) अणु
			bfa_sm_set_state(bfad, bfad_sm_failed);
			अवरोध;
		पूर्ण
		bfa_sm_set_state(bfad, bfad_sm_operational);
		अवरोध;

	हाल BFAD_E_INIT_FAILED:
		bfa_sm_set_state(bfad, bfad_sm_uninit);
		kthपढ़ो_stop(bfad->bfad_tsk);
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_tsk = शून्य;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		अवरोध;

	हाल BFAD_E_HAL_INIT_FAILED:
		bfa_sm_set_state(bfad, bfad_sm_failed);
		अवरोध;
	शेष:
		bfa_sm_fault(bfad, event);
	पूर्ण
पूर्ण

अटल व्योम
bfad_sm_failed(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event)
अणु
	पूर्णांक	retval;

	bfa_trc(bfad, event);

	चयन (event) अणु
	हाल BFAD_E_INIT_SUCCESS:
		retval = bfad_start_ops(bfad);
		अगर (retval != BFA_STATUS_OK)
			अवरोध;
		bfa_sm_set_state(bfad, bfad_sm_operational);
		अवरोध;

	हाल BFAD_E_STOP:
		bfa_sm_set_state(bfad, bfad_sm_fcs_निकास);
		bfa_sm_send_event(bfad, BFAD_E_FCS_EXIT_COMP);
		अवरोध;

	हाल BFAD_E_EXIT_COMP:
		bfa_sm_set_state(bfad, bfad_sm_uninit);
		bfad_हटाओ_पूर्णांकr(bfad);
		del_समयr_sync(&bfad->hal_पंचांगo);
		अवरोध;

	शेष:
		bfa_sm_fault(bfad, event);
	पूर्ण
पूर्ण

अटल व्योम
bfad_sm_operational(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event)
अणु
	bfa_trc(bfad, event);

	चयन (event) अणु
	हाल BFAD_E_STOP:
		bfa_sm_set_state(bfad, bfad_sm_fcs_निकास);
		bfad_fcs_stop(bfad);
		अवरोध;

	शेष:
		bfa_sm_fault(bfad, event);
	पूर्ण
पूर्ण

अटल व्योम
bfad_sm_fcs_निकास(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event)
अणु
	bfa_trc(bfad, event);

	चयन (event) अणु
	हाल BFAD_E_FCS_EXIT_COMP:
		bfa_sm_set_state(bfad, bfad_sm_stopping);
		bfad_stop(bfad);
		अवरोध;

	शेष:
		bfa_sm_fault(bfad, event);
	पूर्ण
पूर्ण

अटल व्योम
bfad_sm_stopping(काष्ठा bfad_s *bfad, क्रमागत bfad_sm_event event)
अणु
	bfa_trc(bfad, event);

	चयन (event) अणु
	हाल BFAD_E_EXIT_COMP:
		bfa_sm_set_state(bfad, bfad_sm_uninit);
		bfad_हटाओ_पूर्णांकr(bfad);
		del_समयr_sync(&bfad->hal_पंचांगo);
		bfad_im_probe_unकरो(bfad);
		bfad->bfad_flags &= ~BFAD_FC4_PROBE_DONE;
		bfad_uncfg_pport(bfad);
		अवरोध;

	शेष:
		bfa_sm_fault(bfad, event);
		अवरोध;
	पूर्ण
पूर्ण

/*
 *  BFA callbacks
 */
व्योम
bfad_hcb_comp(व्योम *arg, bfa_status_t status)
अणु
	काष्ठा bfad_hal_comp *fcomp = (काष्ठा bfad_hal_comp *)arg;

	fcomp->status = status;
	complete(&fcomp->comp);
पूर्ण

/*
 * bfa_init callback
 */
व्योम
bfa_cb_init(व्योम *drv, bfa_status_t init_status)
अणु
	काष्ठा bfad_s	      *bfad = drv;

	अगर (init_status == BFA_STATUS_OK) अणु
		bfad->bfad_flags |= BFAD_HAL_INIT_DONE;

		/*
		 * If BFAD_HAL_INIT_FAIL flag is set:
		 * Wake up the kernel thपढ़ो to start
		 * the bfad operations after HAL init करोne
		 */
		अगर ((bfad->bfad_flags & BFAD_HAL_INIT_FAIL)) अणु
			bfad->bfad_flags &= ~BFAD_HAL_INIT_FAIL;
			wake_up_process(bfad->bfad_tsk);
		पूर्ण
	पूर्ण

	complete(&bfad->comp);
पूर्ण

/*
 *  BFA_FCS callbacks
 */
काष्ठा bfad_port_s *
bfa_fcb_lport_new(काष्ठा bfad_s *bfad, काष्ठा bfa_fcs_lport_s *port,
		 क्रमागत bfa_lport_role roles, काष्ठा bfad_vf_s *vf_drv,
		 काष्ठा bfad_vport_s *vp_drv)
अणु
	bfa_status_t	rc;
	काष्ठा bfad_port_s    *port_drv;

	अगर (!vp_drv && !vf_drv) अणु
		port_drv = &bfad->pport;
		port_drv->pvb_type = BFAD_PORT_PHYS_BASE;
	पूर्ण अन्यथा अगर (!vp_drv && vf_drv) अणु
		port_drv = &vf_drv->base_port;
		port_drv->pvb_type = BFAD_PORT_VF_BASE;
	पूर्ण अन्यथा अगर (vp_drv && !vf_drv) अणु
		port_drv = &vp_drv->drv_port;
		port_drv->pvb_type = BFAD_PORT_PHYS_VPORT;
	पूर्ण अन्यथा अणु
		port_drv = &vp_drv->drv_port;
		port_drv->pvb_type = BFAD_PORT_VF_VPORT;
	पूर्ण

	port_drv->fcs_port = port;
	port_drv->roles = roles;

	अगर (roles & BFA_LPORT_ROLE_FCP_IM) अणु
		rc = bfad_im_port_new(bfad, port_drv);
		अगर (rc != BFA_STATUS_OK) अणु
			bfad_im_port_delete(bfad, port_drv);
			port_drv = शून्य;
		पूर्ण
	पूर्ण

	वापस port_drv;
पूर्ण

/*
 * FCS RPORT alloc callback, after successful PLOGI by FCS
 */
bfa_status_t
bfa_fcb_rport_alloc(काष्ठा bfad_s *bfad, काष्ठा bfa_fcs_rport_s **rport,
		    काष्ठा bfad_rport_s **rport_drv)
अणु
	bfa_status_t	rc = BFA_STATUS_OK;

	*rport_drv = kzalloc(माप(काष्ठा bfad_rport_s), GFP_ATOMIC);
	अगर (*rport_drv == शून्य) अणु
		rc = BFA_STATUS_ENOMEM;
		जाओ ext;
	पूर्ण

	*rport = &(*rport_drv)->fcs_rport;

ext:
	वापस rc;
पूर्ण

/*
 * FCS PBC VPORT Create
 */
व्योम
bfa_fcb_pbc_vport_create(काष्ठा bfad_s *bfad, काष्ठा bfi_pbc_vport_s pbc_vport)
अणु

	काष्ठा bfa_lport_cfg_s port_cfg = अणु0पूर्ण;
	काष्ठा bfad_vport_s   *vport;
	पूर्णांक rc;

	vport = kzalloc(माप(काष्ठा bfad_vport_s), GFP_ATOMIC);
	अगर (!vport) अणु
		bfa_trc(bfad, 0);
		वापस;
	पूर्ण

	vport->drv_port.bfad = bfad;
	port_cfg.roles = BFA_LPORT_ROLE_FCP_IM;
	port_cfg.pwwn = pbc_vport.vp_pwwn;
	port_cfg.nwwn = pbc_vport.vp_nwwn;
	port_cfg.preboot_vp  = BFA_TRUE;

	rc = bfa_fcs_pbc_vport_create(&vport->fcs_vport, &bfad->bfa_fcs, 0,
				  &port_cfg, vport);

	अगर (rc != BFA_STATUS_OK) अणु
		bfa_trc(bfad, 0);
		वापस;
	पूर्ण

	list_add_tail(&vport->list_entry, &bfad->pbc_vport_list);
पूर्ण

व्योम
bfad_hal_mem_release(काष्ठा bfad_s *bfad)
अणु
	काष्ठा bfa_meminfo_s *hal_meminfo = &bfad->meminfo;
	काष्ठा bfa_mem_dma_s *dma_info, *dma_elem;
	काष्ठा bfa_mem_kva_s *kva_info, *kva_elem;
	काष्ठा list_head *dm_qe, *km_qe;

	dma_info = &hal_meminfo->dma_info;
	kva_info = &hal_meminfo->kva_info;

	/* Iterate through the KVA meminfo queue */
	list_क्रम_each(km_qe, &kva_info->qe) अणु
		kva_elem = (काष्ठा bfa_mem_kva_s *) km_qe;
		vमुक्त(kva_elem->kva);
	पूर्ण

	/* Iterate through the DMA meminfo queue */
	list_क्रम_each(dm_qe, &dma_info->qe) अणु
		dma_elem = (काष्ठा bfa_mem_dma_s *) dm_qe;
		dma_मुक्त_coherent(&bfad->pcidev->dev,
				dma_elem->mem_len, dma_elem->kva,
				(dma_addr_t) dma_elem->dma);
	पूर्ण

	स_रखो(hal_meminfo, 0, माप(काष्ठा bfa_meminfo_s));
पूर्ण

व्योम
bfad_update_hal_cfg(काष्ठा bfa_iocfc_cfg_s *bfa_cfg)
अणु
	अगर (num_rports > 0)
		bfa_cfg->fwcfg.num_rports = num_rports;
	अगर (num_ios > 0)
		bfa_cfg->fwcfg.num_ioim_reqs = num_ios;
	अगर (num_पंचांगs > 0)
		bfa_cfg->fwcfg.num_tskim_reqs = num_पंचांगs;
	अगर (num_fcxps > 0 && num_fcxps <= BFA_FCXP_MAX)
		bfa_cfg->fwcfg.num_fcxp_reqs = num_fcxps;
	अगर (num_ufbufs > 0 && num_ufbufs <= BFA_UF_MAX)
		bfa_cfg->fwcfg.num_uf_bufs = num_ufbufs;
	अगर (reqq_size > 0)
		bfa_cfg->drvcfg.num_reqq_elems = reqq_size;
	अगर (rspq_size > 0)
		bfa_cfg->drvcfg.num_rspq_elems = rspq_size;
	अगर (num_sgpgs > 0 && num_sgpgs <= BFA_SGPG_MAX)
		bfa_cfg->drvcfg.num_sgpgs = num_sgpgs;

	/*
	 * populate the hal values back to the driver क्रम sysfs use.
	 * otherwise, the शेष values will be shown as 0 in sysfs
	 */
	num_rports = bfa_cfg->fwcfg.num_rports;
	num_ios = bfa_cfg->fwcfg.num_ioim_reqs;
	num_पंचांगs = bfa_cfg->fwcfg.num_tskim_reqs;
	num_fcxps = bfa_cfg->fwcfg.num_fcxp_reqs;
	num_ufbufs = bfa_cfg->fwcfg.num_uf_bufs;
	reqq_size = bfa_cfg->drvcfg.num_reqq_elems;
	rspq_size = bfa_cfg->drvcfg.num_rspq_elems;
	num_sgpgs = bfa_cfg->drvcfg.num_sgpgs;
पूर्ण

bfa_status_t
bfad_hal_mem_alloc(काष्ठा bfad_s *bfad)
अणु
	काष्ठा bfa_meminfo_s *hal_meminfo = &bfad->meminfo;
	काष्ठा bfa_mem_dma_s *dma_info, *dma_elem;
	काष्ठा bfa_mem_kva_s *kva_info, *kva_elem;
	काष्ठा list_head *dm_qe, *km_qe;
	bfa_status_t	rc = BFA_STATUS_OK;
	dma_addr_t	phys_addr;

	bfa_cfg_get_शेष(&bfad->ioc_cfg);
	bfad_update_hal_cfg(&bfad->ioc_cfg);
	bfad->cfg_data.ioc_queue_depth = bfad->ioc_cfg.fwcfg.num_ioim_reqs;
	bfa_cfg_get_meminfo(&bfad->ioc_cfg, hal_meminfo, &bfad->bfa);

	dma_info = &hal_meminfo->dma_info;
	kva_info = &hal_meminfo->kva_info;

	/* Iterate through the KVA meminfo queue */
	list_क्रम_each(km_qe, &kva_info->qe) अणु
		kva_elem = (काष्ठा bfa_mem_kva_s *) km_qe;
		kva_elem->kva = vzalloc(kva_elem->mem_len);
		अगर (kva_elem->kva == शून्य) अणु
			bfad_hal_mem_release(bfad);
			rc = BFA_STATUS_ENOMEM;
			जाओ ext;
		पूर्ण
	पूर्ण

	/* Iterate through the DMA meminfo queue */
	list_क्रम_each(dm_qe, &dma_info->qe) अणु
		dma_elem = (काष्ठा bfa_mem_dma_s *) dm_qe;
		dma_elem->kva = dma_alloc_coherent(&bfad->pcidev->dev,
						dma_elem->mem_len,
						&phys_addr, GFP_KERNEL);
		अगर (dma_elem->kva == शून्य) अणु
			bfad_hal_mem_release(bfad);
			rc = BFA_STATUS_ENOMEM;
			जाओ ext;
		पूर्ण
		dma_elem->dma = phys_addr;
		स_रखो(dma_elem->kva, 0, dma_elem->mem_len);
	पूर्ण
ext:
	वापस rc;
पूर्ण

/*
 * Create a vport under a vf.
 */
bfa_status_t
bfad_vport_create(काष्ठा bfad_s *bfad, u16 vf_id,
		  काष्ठा bfa_lport_cfg_s *port_cfg, काष्ठा device *dev)
अणु
	काष्ठा bfad_vport_s   *vport;
	पूर्णांक		rc = BFA_STATUS_OK;
	अचिन्हित दीर्घ	flags;
	काष्ठा completion fcomp;

	vport = kzalloc(माप(काष्ठा bfad_vport_s), GFP_KERNEL);
	अगर (!vport) अणु
		rc = BFA_STATUS_ENOMEM;
		जाओ ext;
	पूर्ण

	vport->drv_port.bfad = bfad;
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	rc = bfa_fcs_vport_create(&vport->fcs_vport, &bfad->bfa_fcs, vf_id,
				  port_cfg, vport);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (rc != BFA_STATUS_OK)
		जाओ ext_मुक्त_vport;

	अगर (port_cfg->roles & BFA_LPORT_ROLE_FCP_IM) अणु
		rc = bfad_im_scsi_host_alloc(bfad, vport->drv_port.im_port,
							dev);
		अगर (rc != BFA_STATUS_OK)
			जाओ ext_मुक्त_fcs_vport;
	पूर्ण

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcs_vport_start(&vport->fcs_vport);
	list_add_tail(&vport->list_entry, &bfad->vport_list);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस BFA_STATUS_OK;

ext_मुक्त_fcs_vport:
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	vport->comp_del = &fcomp;
	init_completion(vport->comp_del);
	bfa_fcs_vport_delete(&vport->fcs_vport);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	रुको_क्रम_completion(vport->comp_del);
ext_मुक्त_vport:
	kमुक्त(vport);
ext:
	वापस rc;
पूर्ण

व्योम
bfad_bfa_पंचांगo(काष्ठा समयr_list *t)
अणु
	काष्ठा bfad_s	      *bfad = from_समयr(bfad, t, hal_पंचांगo);
	अचिन्हित दीर्घ	flags;
	काष्ठा list_head	       करोneq;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	bfa_समयr_beat(&bfad->bfa.समयr_mod);

	bfa_comp_deq(&bfad->bfa, &करोneq);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (!list_empty(&करोneq)) अणु
		bfa_comp_process(&bfad->bfa, &करोneq);
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfa_comp_मुक्त(&bfad->bfa, &करोneq);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	पूर्ण

	mod_समयr(&bfad->hal_पंचांगo,
		  jअगरfies + msecs_to_jअगरfies(BFA_TIMER_FREQ));
पूर्ण

व्योम
bfad_init_समयr(काष्ठा bfad_s *bfad)
अणु
	समयr_setup(&bfad->hal_पंचांगo, bfad_bfa_पंचांगo, 0);

	mod_समयr(&bfad->hal_पंचांगo,
		  jअगरfies + msecs_to_jअगरfies(BFA_TIMER_FREQ));
पूर्ण

पूर्णांक
bfad_pci_init(काष्ठा pci_dev *pdev, काष्ठा bfad_s *bfad)
अणु
	पूर्णांक rc = -ENODEV;

	अगर (pci_enable_device(pdev)) अणु
		prपूर्णांकk(KERN_ERR "pci_enable_device fail %p\n", pdev);
		जाओ out;
	पूर्ण

	अगर (pci_request_regions(pdev, BFAD_DRIVER_NAME))
		जाओ out_disable_device;

	pci_set_master(pdev);

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rc)
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));

	अगर (rc) अणु
		rc = -ENODEV;
		prपूर्णांकk(KERN_ERR "dma_set_mask_and_coherent fail %p\n", pdev);
		जाओ out_release_region;
	पूर्ण

	/* Enable PCIE Advanced Error Recovery (AER) अगर kernel supports */
	pci_enable_pcie_error_reporting(pdev);

	bfad->pci_bar0_kva = pci_iomap(pdev, 0, pci_resource_len(pdev, 0));
	bfad->pci_bar2_kva = pci_iomap(pdev, 2, pci_resource_len(pdev, 2));

	अगर (bfad->pci_bar0_kva == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Fail to map bar0\n");
		rc = -ENODEV;
		जाओ out_release_region;
	पूर्ण

	bfad->hal_pcidev.pci_slot = PCI_SLOT(pdev->devfn);
	bfad->hal_pcidev.pci_func = PCI_FUNC(pdev->devfn);
	bfad->hal_pcidev.pci_bar_kva = bfad->pci_bar0_kva;
	bfad->hal_pcidev.device_id = pdev->device;
	bfad->hal_pcidev.ssid = pdev->subप्रणाली_device;
	bfad->pci_name = pci_name(pdev);

	bfad->pci_attr.venकरोr_id = pdev->venकरोr;
	bfad->pci_attr.device_id = pdev->device;
	bfad->pci_attr.ssid = pdev->subप्रणाली_device;
	bfad->pci_attr.ssvid = pdev->subप्रणाली_venकरोr;
	bfad->pci_attr.pcअगरn = PCI_FUNC(pdev->devfn);

	bfad->pcidev = pdev;

	/* Adjust PCIe Maximum Read Request Size */
	अगर (pci_is_pcie(pdev) && pcie_max_पढ़ो_reqsz) अणु
		अगर (pcie_max_पढ़ो_reqsz >= 128 &&
		    pcie_max_पढ़ो_reqsz <= 4096 &&
		    is_घातer_of_2(pcie_max_पढ़ो_reqsz)) अणु
			पूर्णांक max_rq = pcie_get_पढ़ोrq(pdev);
			prपूर्णांकk(KERN_WARNING "BFA[%s]: "
				"pcie_max_read_request_size is %d, "
				"reset to %d\n", bfad->pci_name, max_rq,
				pcie_max_पढ़ो_reqsz);
			pcie_set_पढ़ोrq(pdev, pcie_max_पढ़ो_reqsz);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "BFA[%s]: invalid "
			       "pcie_max_read_request_size %d ignored\n",
			       bfad->pci_name, pcie_max_पढ़ो_reqsz);
		पूर्ण
	पूर्ण

	pci_save_state(pdev);

	वापस 0;

out_release_region:
	pci_release_regions(pdev);
out_disable_device:
	pci_disable_device(pdev);
out:
	वापस rc;
पूर्ण

व्योम
bfad_pci_uninit(काष्ठा pci_dev *pdev, काष्ठा bfad_s *bfad)
अणु
	pci_iounmap(pdev, bfad->pci_bar0_kva);
	pci_iounmap(pdev, bfad->pci_bar2_kva);
	pci_release_regions(pdev);
	/* Disable PCIE Advanced Error Recovery (AER) */
	pci_disable_pcie_error_reporting(pdev);
	pci_disable_device(pdev);
पूर्ण

bfa_status_t
bfad_drv_init(काष्ठा bfad_s *bfad)
अणु
	bfa_status_t	rc;
	अचिन्हित दीर्घ	flags;

	bfad->cfg_data.rport_del_समयout = rport_del_समयout;
	bfad->cfg_data.lun_queue_depth = bfa_lun_queue_depth;
	bfad->cfg_data.io_max_sge = bfa_io_max_sge;
	bfad->cfg_data.binding_method = FCP_PWWN_BINDING;

	rc = bfad_hal_mem_alloc(bfad);
	अगर (rc != BFA_STATUS_OK) अणु
		prपूर्णांकk(KERN_WARNING "bfad%d bfad_hal_mem_alloc failure\n",
		       bfad->inst_no);
		prपूर्णांकk(KERN_WARNING
			"Not enough memory to attach all QLogic BR-series HBA ports. System may need more memory.\n");
		वापस BFA_STATUS_FAILED;
	पूर्ण

	bfad->bfa.trcmod = bfad->trcmod;
	bfad->bfa.plog = &bfad->plog_buf;
	bfa_plog_init(&bfad->plog_buf);
	bfa_plog_str(&bfad->plog_buf, BFA_PL_MID_DRVR, BFA_PL_EID_DRIVER_START,
		     0, "Driver Attach");

	bfa_attach(&bfad->bfa, bfad, &bfad->ioc_cfg, &bfad->meminfo,
		   &bfad->hal_pcidev);

	/* FCS INIT */
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfad->bfa_fcs.trcmod = bfad->trcmod;
	bfa_fcs_attach(&bfad->bfa_fcs, &bfad->bfa, bfad, BFA_FALSE);
	bfad->bfa_fcs.fdmi_enabled = fdmi_enable;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	bfad->bfad_flags |= BFAD_DRV_INIT_DONE;

	वापस BFA_STATUS_OK;
पूर्ण

व्योम
bfad_drv_uninit(काष्ठा bfad_s *bfad)
अणु
	अचिन्हित दीर्घ   flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	init_completion(&bfad->comp);
	bfa_iocfc_stop(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	रुको_क्रम_completion(&bfad->comp);

	del_समयr_sync(&bfad->hal_पंचांगo);
	bfa_isr_disable(&bfad->bfa);
	bfa_detach(&bfad->bfa);
	bfad_हटाओ_पूर्णांकr(bfad);
	bfad_hal_mem_release(bfad);

	bfad->bfad_flags &= ~BFAD_DRV_INIT_DONE;
पूर्ण

व्योम
bfad_drv_start(काष्ठा bfad_s *bfad)
अणु
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_iocfc_start(&bfad->bfa);
	bfa_fcs_pbc_vport_init(&bfad->bfa_fcs);
	bfa_fcs_fabric_modstart(&bfad->bfa_fcs);
	bfad->bfad_flags |= BFAD_HAL_START_DONE;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (bfad->im)
		flush_workqueue(bfad->im->drv_workq);
पूर्ण

व्योम
bfad_fcs_stop(काष्ठा bfad_s *bfad)
अणु
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	init_completion(&bfad->comp);
	bfad->pport.flags |= BFAD_PORT_DELETE;
	bfa_fcs_निकास(&bfad->bfa_fcs);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	रुको_क्रम_completion(&bfad->comp);

	bfa_sm_send_event(bfad, BFAD_E_FCS_EXIT_COMP);
पूर्ण

व्योम
bfad_stop(काष्ठा bfad_s *bfad)
अणु
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	init_completion(&bfad->comp);
	bfa_iocfc_stop(&bfad->bfa);
	bfad->bfad_flags &= ~BFAD_HAL_START_DONE;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	रुको_क्रम_completion(&bfad->comp);

	bfa_sm_send_event(bfad, BFAD_E_EXIT_COMP);
पूर्ण

bfa_status_t
bfad_cfg_pport(काष्ठा bfad_s *bfad, क्रमागत bfa_lport_role role)
अणु
	पूर्णांक		rc = BFA_STATUS_OK;

	/* Allocate scsi_host क्रम the physical port */
	अगर ((supported_fc4s & BFA_LPORT_ROLE_FCP_IM) &&
	    (role & BFA_LPORT_ROLE_FCP_IM)) अणु
		अगर (bfad->pport.im_port == शून्य) अणु
			rc = BFA_STATUS_FAILED;
			जाओ out;
		पूर्ण

		rc = bfad_im_scsi_host_alloc(bfad, bfad->pport.im_port,
						&bfad->pcidev->dev);
		अगर (rc != BFA_STATUS_OK)
			जाओ out;

		bfad->pport.roles |= BFA_LPORT_ROLE_FCP_IM;
	पूर्ण

	bfad->bfad_flags |= BFAD_CFG_PPORT_DONE;

out:
	वापस rc;
पूर्ण

व्योम
bfad_uncfg_pport(काष्ठा bfad_s *bfad)
अणु
	अगर ((supported_fc4s & BFA_LPORT_ROLE_FCP_IM) &&
	    (bfad->pport.roles & BFA_LPORT_ROLE_FCP_IM)) अणु
		bfad_im_scsi_host_मुक्त(bfad, bfad->pport.im_port);
		bfad_im_port_clean(bfad->pport.im_port);
		kमुक्त(bfad->pport.im_port);
		bfad->pport.roles &= ~BFA_LPORT_ROLE_FCP_IM;
	पूर्ण

	bfad->bfad_flags &= ~BFAD_CFG_PPORT_DONE;
पूर्ण

bfa_status_t
bfad_start_ops(काष्ठा bfad_s *bfad) अणु

	पूर्णांक	retval;
	अचिन्हित दीर्घ	flags;
	काष्ठा bfad_vport_s *vport, *vport_new;
	काष्ठा bfa_fcs_driver_info_s driver_info;

	/* Limit min/max. xfer size to [64k-32MB] */
	अगर (max_xfer_size < BFAD_MIN_SECTORS >> 1)
		max_xfer_size = BFAD_MIN_SECTORS >> 1;
	अगर (max_xfer_size > BFAD_MAX_SECTORS >> 1)
		max_xfer_size = BFAD_MAX_SECTORS >> 1;

	/* Fill the driver_info info to fcs*/
	स_रखो(&driver_info, 0, माप(driver_info));
	strlcpy(driver_info.version, BFAD_DRIVER_VERSION,
		माप(driver_info.version));
	अगर (host_name)
		strlcpy(driver_info.host_machine_name, host_name,
			माप(driver_info.host_machine_name));
	अगर (os_name)
		strlcpy(driver_info.host_os_name, os_name,
			माप(driver_info.host_os_name));
	अगर (os_patch)
		strlcpy(driver_info.host_os_patch, os_patch,
			माप(driver_info.host_os_patch));

	strlcpy(driver_info.os_device_name, bfad->pci_name,
		माप(driver_info.os_device_name));

	/* FCS driver info init */
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcs_driver_info_init(&bfad->bfa_fcs, &driver_info);

	अगर (bfad->bfad_flags & BFAD_CFG_PPORT_DONE)
		bfa_fcs_update_cfg(&bfad->bfa_fcs);
	अन्यथा
		bfa_fcs_init(&bfad->bfa_fcs);

	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (!(bfad->bfad_flags & BFAD_CFG_PPORT_DONE)) अणु
		retval = bfad_cfg_pport(bfad, BFA_LPORT_ROLE_FCP_IM);
		अगर (retval != BFA_STATUS_OK)
			वापस BFA_STATUS_FAILED;
	पूर्ण

	/* Setup fc host fixed attribute अगर the lk supports */
	bfad_fc_host_init(bfad->pport.im_port);

	/* BFAD level FC4 IM specअगरic resource allocation */
	retval = bfad_im_probe(bfad);
	अगर (retval != BFA_STATUS_OK) अणु
		prपूर्णांकk(KERN_WARNING "bfad_im_probe failed\n");
		अगर (bfa_sm_cmp_state(bfad, bfad_sm_initializing))
			bfa_sm_set_state(bfad, bfad_sm_failed);
		वापस BFA_STATUS_FAILED;
	पूर्ण अन्यथा
		bfad->bfad_flags |= BFAD_FC4_PROBE_DONE;

	bfad_drv_start(bfad);

	/* Complete pbc vport create */
	list_क्रम_each_entry_safe(vport, vport_new, &bfad->pbc_vport_list,
				list_entry) अणु
		काष्ठा fc_vport_identअगरiers vid;
		काष्ठा fc_vport *fc_vport;
		अक्षर pwwn_buf[BFA_STRING_32];

		स_रखो(&vid, 0, माप(vid));
		vid.roles = FC_PORT_ROLE_FCP_INITIATOR;
		vid.vport_type = FC_PORTTYPE_NPIV;
		vid.disable = false;
		vid.node_name = wwn_to_u64((u8 *)
				(&((vport->fcs_vport).lport.port_cfg.nwwn)));
		vid.port_name = wwn_to_u64((u8 *)
				(&((vport->fcs_vport).lport.port_cfg.pwwn)));
		fc_vport = fc_vport_create(bfad->pport.im_port->shost, 0, &vid);
		अगर (!fc_vport) अणु
			wwn2str(pwwn_buf, vid.port_name);
			prपूर्णांकk(KERN_WARNING "bfad%d: failed to create pbc vport"
				" %s\n", bfad->inst_no, pwwn_buf);
		पूर्ण
		list_del(&vport->list_entry);
		kमुक्त(vport);
	पूर्ण

	/*
	 * If bfa_linkup_delay is set to -1 शेष; try to retrive the
	 * value using the bfad_get_linkup_delay(); अन्यथा use the
	 * passed in module param value as the bfa_linkup_delay.
	 */
	अगर (bfa_linkup_delay < 0) अणु
		bfa_linkup_delay = bfad_get_linkup_delay(bfad);
		bfad_rport_online_रुको(bfad);
		bfa_linkup_delay = -1;
	पूर्ण अन्यथा
		bfad_rport_online_रुको(bfad);

	BFA_LOG(KERN_INFO, bfad, bfa_log_level, "bfa device claimed\n");

	वापस BFA_STATUS_OK;
पूर्ण

पूर्णांक
bfad_worker(व्योम *ptr)
अणु
	काष्ठा bfad_s *bfad = ptr;
	अचिन्हित दीर्घ flags;

	अगर (kthपढ़ो_should_stop())
		वापस 0;

	/* Send event BFAD_E_INIT_SUCCESS */
	bfa_sm_send_event(bfad, BFAD_E_INIT_SUCCESS);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfad->bfad_tsk = शून्य;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	वापस 0;
पूर्ण

/*
 *  BFA driver पूर्णांकerrupt functions
 */
irqवापस_t
bfad_पूर्णांकx(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bfad_s	*bfad = dev_id;
	काष्ठा list_head	करोneq;
	अचिन्हित दीर्घ	flags;
	bfa_boolean_t rc;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	rc = bfa_पूर्णांकx(&bfad->bfa);
	अगर (!rc) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	bfa_comp_deq(&bfad->bfa, &करोneq);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (!list_empty(&करोneq)) अणु
		bfa_comp_process(&bfad->bfa, &करोneq);

		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfa_comp_मुक्त(&bfad->bfa, &करोneq);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	पूर्ण

	वापस IRQ_HANDLED;

पूर्ण

अटल irqवापस_t
bfad_msix(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bfad_msix_s *vec = dev_id;
	काष्ठा bfad_s *bfad = vec->bfad;
	काष्ठा list_head करोneq;
	अचिन्हित दीर्घ   flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);

	bfa_msix(&bfad->bfa, vec->msix.entry);
	bfa_comp_deq(&bfad->bfa, &करोneq);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	अगर (!list_empty(&करोneq)) अणु
		bfa_comp_process(&bfad->bfa, &करोneq);

		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfa_comp_मुक्त(&bfad->bfa, &करोneq);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Initialize the MSIX entry table.
 */
अटल व्योम
bfad_init_msix_entry(काष्ठा bfad_s *bfad, काष्ठा msix_entry *msix_entries,
			 पूर्णांक mask, पूर्णांक max_bit)
अणु
	पूर्णांक	i;
	पूर्णांक	match = 0x00000001;

	क्रम (i = 0, bfad->nvec = 0; i < MAX_MSIX_ENTRY; i++) अणु
		अगर (mask & match) अणु
			bfad->msix_tab[bfad->nvec].msix.entry = i;
			bfad->msix_tab[bfad->nvec].bfad = bfad;
			msix_entries[bfad->nvec].entry = i;
			bfad->nvec++;
		पूर्ण

		match <<= 1;
	पूर्ण

पूर्ण

पूर्णांक
bfad_install_msix_handler(काष्ठा bfad_s *bfad)
अणु
	पूर्णांक i, error = 0;

	क्रम (i = 0; i < bfad->nvec; i++) अणु
		प्र_लिखो(bfad->msix_tab[i].name, "bfa-%s-%s",
				bfad->pci_name,
				((bfa_asic_id_cb(bfad->hal_pcidev.device_id)) ?
				msix_name_cb[i] : msix_name_ct[i]));

		error = request_irq(bfad->msix_tab[i].msix.vector,
				    (irq_handler_t) bfad_msix, 0,
				    bfad->msix_tab[i].name, &bfad->msix_tab[i]);
		bfa_trc(bfad, i);
		bfa_trc(bfad, bfad->msix_tab[i].msix.vector);
		अगर (error) अणु
			पूर्णांक	j;

			क्रम (j = 0; j < i; j++)
				मुक्त_irq(bfad->msix_tab[j].msix.vector,
						&bfad->msix_tab[j]);

			bfad->bfad_flags &= ~BFAD_MSIX_ON;
			pci_disable_msix(bfad->pcidev);

			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Setup MSIX based पूर्णांकerrupt.
 */
पूर्णांक
bfad_setup_पूर्णांकr(काष्ठा bfad_s *bfad)
अणु
	पूर्णांक error;
	u32 mask = 0, i, num_bit = 0, max_bit = 0;
	काष्ठा msix_entry msix_entries[MAX_MSIX_ENTRY];
	काष्ठा pci_dev *pdev = bfad->pcidev;
	u16	reg;

	/* Call BFA to get the msix map क्रम this PCI function.  */
	bfa_msix_getvecs(&bfad->bfa, &mask, &num_bit, &max_bit);

	/* Set up the msix entry table */
	bfad_init_msix_entry(bfad, msix_entries, mask, max_bit);

	अगर ((bfa_asic_id_ctc(pdev->device) && !msix_disable_ct) ||
	   (bfa_asic_id_cb(pdev->device) && !msix_disable_cb)) अणु

		error = pci_enable_msix_exact(bfad->pcidev,
					      msix_entries, bfad->nvec);
		/* In CT1 & CT2, try to allocate just one vector */
		अगर (error == -ENOSPC && bfa_asic_id_ctc(pdev->device)) अणु
			prपूर्णांकk(KERN_WARNING "bfa %s: trying one msix "
			       "vector failed to allocate %d[%d]\n",
			       bfad->pci_name, bfad->nvec, error);
			bfad->nvec = 1;
			error = pci_enable_msix_exact(bfad->pcidev,
						      msix_entries, 1);
		पूर्ण

		अगर (error) अणु
			prपूर्णांकk(KERN_WARNING "bfad%d: "
			       "pci_enable_msix_exact failed (%d), "
			       "use line based.\n",
				bfad->inst_no, error);
			जाओ line_based;
		पूर्ण

		/* Disable INTX in MSI-X mode */
		pci_पढ़ो_config_word(pdev, PCI_COMMAND, &reg);

		अगर (!(reg & PCI_COMMAND_INTX_DISABLE))
			pci_ग_लिखो_config_word(pdev, PCI_COMMAND,
				reg | PCI_COMMAND_INTX_DISABLE);

		/* Save the vectors */
		क्रम (i = 0; i < bfad->nvec; i++) अणु
			bfa_trc(bfad, msix_entries[i].vector);
			bfad->msix_tab[i].msix.vector = msix_entries[i].vector;
		पूर्ण

		bfa_msix_init(&bfad->bfa, bfad->nvec);

		bfad->bfad_flags |= BFAD_MSIX_ON;

		वापस 0;
	पूर्ण

line_based:
	error = request_irq(bfad->pcidev->irq, (irq_handler_t)bfad_पूर्णांकx,
			    BFAD_IRQ_FLAGS, BFAD_DRIVER_NAME, bfad);
	अगर (error)
		वापस error;

	bfad->bfad_flags |= BFAD_INTX_ON;

	वापस 0;
पूर्ण

व्योम
bfad_हटाओ_पूर्णांकr(काष्ठा bfad_s *bfad)
अणु
	पूर्णांक	i;

	अगर (bfad->bfad_flags & BFAD_MSIX_ON) अणु
		क्रम (i = 0; i < bfad->nvec; i++)
			मुक्त_irq(bfad->msix_tab[i].msix.vector,
					&bfad->msix_tab[i]);

		pci_disable_msix(bfad->pcidev);
		bfad->bfad_flags &= ~BFAD_MSIX_ON;
	पूर्ण अन्यथा अगर (bfad->bfad_flags & BFAD_INTX_ON) अणु
		मुक्त_irq(bfad->pcidev->irq, bfad);
	पूर्ण
पूर्ण

/*
 * PCI probe entry.
 */
पूर्णांक
bfad_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *pid)
अणु
	काष्ठा bfad_s	*bfad;
	पूर्णांक		error = -ENODEV, retval, i;

	/* For single port cards - only claim function 0 */
	अगर ((pdev->device == BFA_PCI_DEVICE_ID_FC_8G1P) &&
		(PCI_FUNC(pdev->devfn) != 0))
		वापस -ENODEV;

	bfad = kzalloc(माप(काष्ठा bfad_s), GFP_KERNEL);
	अगर (!bfad) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	bfad->trcmod = kzalloc(माप(काष्ठा bfa_trc_mod_s), GFP_KERNEL);
	अगर (!bfad->trcmod) अणु
		prपूर्णांकk(KERN_WARNING "Error alloc trace buffer!\n");
		error = -ENOMEM;
		जाओ out_alloc_trace_failure;
	पूर्ण

	/* TRACE INIT */
	bfa_trc_init(bfad->trcmod);
	bfa_trc(bfad, bfad_inst);

	/* AEN INIT */
	INIT_LIST_HEAD(&bfad->मुक्त_aen_q);
	INIT_LIST_HEAD(&bfad->active_aen_q);
	क्रम (i = 0; i < BFA_AEN_MAX_ENTRY; i++)
		list_add_tail(&bfad->aen_list[i].qe, &bfad->मुक्त_aen_q);

	अगर (!(bfad_load_fwimg(pdev))) अणु
		kमुक्त(bfad->trcmod);
		जाओ out_alloc_trace_failure;
	पूर्ण

	retval = bfad_pci_init(pdev, bfad);
	अगर (retval) अणु
		prपूर्णांकk(KERN_WARNING "bfad_pci_init failure!\n");
		error = retval;
		जाओ out_pci_init_failure;
	पूर्ण

	mutex_lock(&bfad_mutex);
	bfad->inst_no = bfad_inst++;
	list_add_tail(&bfad->list_entry, &bfad_list);
	mutex_unlock(&bfad_mutex);

	/* Initializing the state machine: State set to uninit */
	bfa_sm_set_state(bfad, bfad_sm_uninit);

	spin_lock_init(&bfad->bfad_lock);
	spin_lock_init(&bfad->bfad_aen_spinlock);

	pci_set_drvdata(pdev, bfad);

	bfad->ref_count = 0;
	bfad->pport.bfad = bfad;
	INIT_LIST_HEAD(&bfad->pbc_vport_list);
	INIT_LIST_HEAD(&bfad->vport_list);

	/* Setup the debugfs node क्रम this bfad */
	अगर (bfa_debugfs_enable)
		bfad_debugfs_init(&bfad->pport);

	retval = bfad_drv_init(bfad);
	अगर (retval != BFA_STATUS_OK)
		जाओ out_drv_init_failure;

	bfa_sm_send_event(bfad, BFAD_E_CREATE);

	अगर (bfa_sm_cmp_state(bfad, bfad_sm_uninit))
		जाओ out_bfad_sm_failure;

	वापस 0;

out_bfad_sm_failure:
	bfad_hal_mem_release(bfad);
out_drv_init_failure:
	/* Remove the debugfs node क्रम this bfad */
	kमुक्त(bfad->regdata);
	bfad_debugfs_निकास(&bfad->pport);
	mutex_lock(&bfad_mutex);
	bfad_inst--;
	list_del(&bfad->list_entry);
	mutex_unlock(&bfad_mutex);
	bfad_pci_uninit(pdev, bfad);
out_pci_init_failure:
	kमुक्त(bfad->trcmod);
out_alloc_trace_failure:
	kमुक्त(bfad);
out:
	वापस error;
पूर्ण

/*
 * PCI हटाओ entry.
 */
व्योम
bfad_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा bfad_s	      *bfad = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ	flags;

	bfa_trc(bfad, bfad->inst_no);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	अगर (bfad->bfad_tsk != शून्य) अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		kthपढ़ो_stop(bfad->bfad_tsk);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	पूर्ण

	/* Send Event BFAD_E_STOP */
	bfa_sm_send_event(bfad, BFAD_E_STOP);

	/* Driver detach and dealloc mem */
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_detach(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	bfad_hal_mem_release(bfad);

	/* Remove the debugfs node क्रम this bfad */
	kमुक्त(bfad->regdata);
	bfad_debugfs_निकास(&bfad->pport);

	/* Cleaning the BFAD instance */
	mutex_lock(&bfad_mutex);
	bfad_inst--;
	list_del(&bfad->list_entry);
	mutex_unlock(&bfad_mutex);
	bfad_pci_uninit(pdev, bfad);

	kमुक्त(bfad->trcmod);
	kमुक्त(bfad);
पूर्ण

/*
 * PCI Error Recovery entry, error detected.
 */
अटल pci_ers_result_t
bfad_pci_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा bfad_s *bfad = pci_get_drvdata(pdev);
	अचिन्हित दीर्घ	flags;
	pci_ers_result_t ret = PCI_ERS_RESULT_NONE;

	dev_prपूर्णांकk(KERN_ERR, &pdev->dev,
		   "error detected state: %d - flags: 0x%x\n",
		   state, bfad->bfad_flags);

	चयन (state) अणु
	हाल pci_channel_io_normal: /* non-fatal error */
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_flags &= ~BFAD_EEH_BUSY;
		/* Suspend/fail all bfa operations */
		bfa_ioc_suspend(&bfad->bfa.ioc);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		del_समयr_sync(&bfad->hal_पंचांगo);
		ret = PCI_ERS_RESULT_CAN_RECOVER;
		अवरोध;
	हाल pci_channel_io_frozen: /* fatal error */
		init_completion(&bfad->comp);
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_flags |= BFAD_EEH_BUSY;
		/* Suspend/fail all bfa operations */
		bfa_ioc_suspend(&bfad->bfa.ioc);
		bfa_fcs_stop(&bfad->bfa_fcs);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		रुको_क्रम_completion(&bfad->comp);

		bfad_हटाओ_पूर्णांकr(bfad);
		del_समयr_sync(&bfad->hal_पंचांगo);
		pci_disable_device(pdev);
		ret = PCI_ERS_RESULT_NEED_RESET;
		अवरोध;
	हाल pci_channel_io_perm_failure: /* PCI Card is DEAD */
		spin_lock_irqsave(&bfad->bfad_lock, flags);
		bfad->bfad_flags |= BFAD_EEH_BUSY |
				    BFAD_EEH_PCI_CHANNEL_IO_PERM_FAILURE;
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);

		/* If the error_detected handler is called with the reason
		 * pci_channel_io_perm_failure - it will subsequently call
		 * pci_हटाओ() entry poपूर्णांक to हटाओ the pci device from the
		 * प्रणाली - So defer the cleanup to pci_हटाओ(); cleaning up
		 * here causes inconsistent state during pci_हटाओ().
		 */
		ret = PCI_ERS_RESULT_DISCONNECT;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक restart_bfa(काष्ठा bfad_s *bfad)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pci_dev *pdev = bfad->pcidev;

	bfa_attach(&bfad->bfa, bfad, &bfad->ioc_cfg,
		   &bfad->meminfo, &bfad->hal_pcidev);

	/* Enable Interrupt and रुको bfa_init completion */
	अगर (bfad_setup_पूर्णांकr(bfad)) अणु
		dev_prपूर्णांकk(KERN_WARNING, &pdev->dev,
			   "%s: bfad_setup_intr failed\n", bfad->pci_name);
		bfa_sm_send_event(bfad, BFAD_E_INIT_FAILED);
		वापस -1;
	पूर्ण

	init_completion(&bfad->comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_iocfc_init(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	/* Set up पूर्णांकerrupt handler क्रम each vectors */
	अगर ((bfad->bfad_flags & BFAD_MSIX_ON) &&
	    bfad_install_msix_handler(bfad))
		dev_prपूर्णांकk(KERN_WARNING, &pdev->dev,
			   "%s: install_msix failed.\n", bfad->pci_name);

	bfad_init_समयr(bfad);
	रुको_क्रम_completion(&bfad->comp);
	bfad_drv_start(bfad);

	वापस 0;
पूर्ण

/*
 * PCI Error Recovery entry, re-initialize the chip.
 */
अटल pci_ers_result_t
bfad_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा bfad_s *bfad = pci_get_drvdata(pdev);
	u8 byte;
	पूर्णांक rc;

	dev_prपूर्णांकk(KERN_ERR, &pdev->dev,
		   "bfad_pci_slot_reset flags: 0x%x\n", bfad->bfad_flags);

	अगर (pci_enable_device(pdev)) अणु
		dev_prपूर्णांकk(KERN_ERR, &pdev->dev, "Cannot re-enable "
			   "PCI device after reset.\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	pci_restore_state(pdev);

	/*
	 * Read some byte (e.g. DMA max. payload size which can't
	 * be 0xff any समय) to make sure - we did not hit another PCI error
	 * in the middle of recovery. If we did, then declare permanent failure.
	 */
	pci_पढ़ो_config_byte(pdev, 0x68, &byte);
	अगर (byte == 0xff) अणु
		dev_prपूर्णांकk(KERN_ERR, &pdev->dev,
			   "slot_reset failed ... got another PCI error !\n");
		जाओ out_disable_device;
	पूर्ण

	pci_save_state(pdev);
	pci_set_master(pdev);

	rc = dma_set_mask_and_coherent(&bfad->pcidev->dev, DMA_BIT_MASK(64));
	अगर (rc)
		rc = dma_set_mask_and_coherent(&bfad->pcidev->dev,
					       DMA_BIT_MASK(32));
	अगर (rc)
		जाओ out_disable_device;

	अगर (restart_bfa(bfad) == -1)
		जाओ out_disable_device;

	pci_enable_pcie_error_reporting(pdev);
	dev_prपूर्णांकk(KERN_WARNING, &pdev->dev,
		   "slot_reset completed  flags: 0x%x!\n", bfad->bfad_flags);

	वापस PCI_ERS_RESULT_RECOVERED;

out_disable_device:
	pci_disable_device(pdev);
	वापस PCI_ERS_RESULT_DISCONNECT;
पूर्ण

अटल pci_ers_result_t
bfad_pci_mmio_enabled(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ	flags;
	काष्ठा bfad_s *bfad = pci_get_drvdata(pdev);

	dev_prपूर्णांकk(KERN_INFO, &pdev->dev, "mmio_enabled\n");

	/* Fetch FW diagnostic inक्रमmation */
	bfa_ioc_debug_save_ftrc(&bfad->bfa.ioc);

	/* Cancel all pending IOs */
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	init_completion(&bfad->comp);
	bfa_fcs_stop(&bfad->bfa_fcs);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	रुको_क्रम_completion(&bfad->comp);

	bfad_हटाओ_पूर्णांकr(bfad);
	del_समयr_sync(&bfad->hal_पंचांगo);
	pci_disable_device(pdev);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल व्योम
bfad_pci_resume(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ	flags;
	काष्ठा bfad_s *bfad = pci_get_drvdata(pdev);

	dev_prपूर्णांकk(KERN_WARNING, &pdev->dev, "resume\n");

	/* रुको until the link is online */
	bfad_rport_online_रुको(bfad);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfad->bfad_flags &= ~BFAD_EEH_BUSY;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
पूर्ण

काष्ठा pci_device_id bfad_id_table[] = अणु
	अणु
		.venकरोr = BFA_PCI_VENDOR_ID_BROCADE,
		.device = BFA_PCI_DEVICE_ID_FC_8G2P,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण,
	अणु
		.venकरोr = BFA_PCI_VENDOR_ID_BROCADE,
		.device = BFA_PCI_DEVICE_ID_FC_8G1P,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण,
	अणु
		.venकरोr = BFA_PCI_VENDOR_ID_BROCADE,
		.device = BFA_PCI_DEVICE_ID_CT,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
		.class = (PCI_CLASS_SERIAL_FIBER << 8),
		.class_mask = ~0,
	पूर्ण,
	अणु
		.venकरोr = BFA_PCI_VENDOR_ID_BROCADE,
		.device = BFA_PCI_DEVICE_ID_CT_FC,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
		.class = (PCI_CLASS_SERIAL_FIBER << 8),
		.class_mask = ~0,
	पूर्ण,
	अणु
		.venकरोr = BFA_PCI_VENDOR_ID_BROCADE,
		.device = BFA_PCI_DEVICE_ID_CT2,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
		.class = (PCI_CLASS_SERIAL_FIBER << 8),
		.class_mask = ~0,
	पूर्ण,

	अणु
		.venकरोr = BFA_PCI_VENDOR_ID_BROCADE,
		.device = BFA_PCI_DEVICE_ID_CT2_QUAD,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
		.class = (PCI_CLASS_SERIAL_FIBER << 8),
		.class_mask = ~0,
	पूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, bfad_id_table);

/*
 * PCI error recovery handlers.
 */
अटल काष्ठा pci_error_handlers bfad_err_handler = अणु
	.error_detected = bfad_pci_error_detected,
	.slot_reset = bfad_pci_slot_reset,
	.mmio_enabled = bfad_pci_mmio_enabled,
	.resume = bfad_pci_resume,
पूर्ण;

अटल काष्ठा pci_driver bfad_pci_driver = अणु
	.name = BFAD_DRIVER_NAME,
	.id_table = bfad_id_table,
	.probe = bfad_pci_probe,
	.हटाओ = bfad_pci_हटाओ,
	.err_handler = &bfad_err_handler,
पूर्ण;

/*
 * Driver module init.
 */
अटल पूर्णांक __init
bfad_init(व्योम)
अणु
	पूर्णांक		error = 0;

	pr_info("QLogic BR-series BFA FC/FCOE SCSI driver - version: %s\n",
			BFAD_DRIVER_VERSION);

	अगर (num_sgpgs > 0)
		num_sgpgs_parm = num_sgpgs;

	error = bfad_im_module_init();
	अगर (error) अणु
		error = -ENOMEM;
		prपूर्णांकk(KERN_WARNING "bfad_im_module_init failure\n");
		जाओ ext;
	पूर्ण

	अगर (म_भेद(FCPI_NAME, " fcpim") == 0)
		supported_fc4s |= BFA_LPORT_ROLE_FCP_IM;

	bfa_स्वतः_recover = ioc_स्वतः_recover;
	bfa_fcs_rport_set_del_समयout(rport_del_समयout);
	bfa_fcs_rport_set_max_logins(max_rport_logins);

	error = pci_रेजिस्टर_driver(&bfad_pci_driver);
	अगर (error) अणु
		prपूर्णांकk(KERN_WARNING "pci_register_driver failure\n");
		जाओ ext;
	पूर्ण

	वापस 0;

ext:
	bfad_im_module_निकास();
	वापस error;
पूर्ण

/*
 * Driver module निकास.
 */
अटल व्योम __निकास
bfad_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&bfad_pci_driver);
	bfad_im_module_निकास();
	bfad_मुक्त_fwimg();
पूर्ण

/* Firmware handling */
अटल व्योम
bfad_पढ़ो_firmware(काष्ठा pci_dev *pdev, u32 **bfi_image,
		u32 *bfi_image_size, अक्षर *fw_name)
अणु
	स्थिर काष्ठा firmware *fw;

	अगर (request_firmware(&fw, fw_name, &pdev->dev)) अणु
		prपूर्णांकk(KERN_ALERT "Can't locate firmware %s\n", fw_name);
		*bfi_image = शून्य;
		जाओ out;
	पूर्ण

	*bfi_image = vदो_स्मृति(fw->size);
	अगर (शून्य == *bfi_image) अणु
		prपूर्णांकk(KERN_ALERT "Fail to allocate buffer for fw image "
			"size=%x!\n", (u32) fw->size);
		जाओ out;
	पूर्ण

	स_नकल(*bfi_image, fw->data, fw->size);
	*bfi_image_size = fw->size/माप(u32);
out:
	release_firmware(fw);
पूर्ण

अटल u32 *
bfad_load_fwimg(काष्ठा pci_dev *pdev)
अणु
	अगर (bfa_asic_id_ct2(pdev->device)) अणु
		अगर (bfi_image_ct2_size == 0)
			bfad_पढ़ो_firmware(pdev, &bfi_image_ct2,
				&bfi_image_ct2_size, BFAD_FW_खाता_CT2);
		वापस bfi_image_ct2;
	पूर्ण अन्यथा अगर (bfa_asic_id_ct(pdev->device)) अणु
		अगर (bfi_image_ct_size == 0)
			bfad_पढ़ो_firmware(pdev, &bfi_image_ct,
				&bfi_image_ct_size, BFAD_FW_खाता_CT);
		वापस bfi_image_ct;
	पूर्ण अन्यथा अगर (bfa_asic_id_cb(pdev->device)) अणु
		अगर (bfi_image_cb_size == 0)
			bfad_पढ़ो_firmware(pdev, &bfi_image_cb,
				&bfi_image_cb_size, BFAD_FW_खाता_CB);
		वापस bfi_image_cb;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
bfad_मुक्त_fwimg(व्योम)
अणु
	अगर (bfi_image_ct2_size && bfi_image_ct2)
		vमुक्त(bfi_image_ct2);
	अगर (bfi_image_ct_size && bfi_image_ct)
		vमुक्त(bfi_image_ct);
	अगर (bfi_image_cb_size && bfi_image_cb)
		vमुक्त(bfi_image_cb);
पूर्ण

module_init(bfad_init);
module_निकास(bfad_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("QLogic BR-series Fibre Channel HBA Driver" BFAD_PROTO_NAME);
MODULE_AUTHOR("QLogic Corporation");
MODULE_VERSION(BFAD_DRIVER_VERSION);
