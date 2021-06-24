<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#समावेश "nitrox_dev.h"
#समावेश "nitrox_hal.h"
#समावेश "nitrox_common.h"
#समावेश "nitrox_isr.h"
#समावेश "nitrox_mbx.h"

/**
 * num_vfs_valid - validate VF count
 * @num_vfs: number of VF(s)
 */
अटल अंतरभूत bool num_vfs_valid(पूर्णांक num_vfs)
अणु
	bool valid = false;

	चयन (num_vfs) अणु
	हाल 16:
	हाल 32:
	हाल 64:
	हाल 128:
		valid = true;
		अवरोध;
	पूर्ण

	वापस valid;
पूर्ण

अटल अंतरभूत क्रमागत vf_mode num_vfs_to_mode(पूर्णांक num_vfs)
अणु
	क्रमागत vf_mode mode = 0;

	चयन (num_vfs) अणु
	हाल 0:
		mode = __NDEV_MODE_PF;
		अवरोध;
	हाल 16:
		mode = __NDEV_MODE_VF16;
		अवरोध;
	हाल 32:
		mode = __NDEV_MODE_VF32;
		अवरोध;
	हाल 64:
		mode = __NDEV_MODE_VF64;
		अवरोध;
	हाल 128:
		mode = __NDEV_MODE_VF128;
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण

अटल अंतरभूत पूर्णांक vf_mode_to_nr_queues(क्रमागत vf_mode mode)
अणु
	पूर्णांक nr_queues = 0;

	चयन (mode) अणु
	हाल __NDEV_MODE_PF:
		nr_queues = MAX_PF_QUEUES;
		अवरोध;
	हाल __NDEV_MODE_VF16:
		nr_queues = 8;
		अवरोध;
	हाल __NDEV_MODE_VF32:
		nr_queues = 4;
		अवरोध;
	हाल __NDEV_MODE_VF64:
		nr_queues = 2;
		अवरोध;
	हाल __NDEV_MODE_VF128:
		nr_queues = 1;
		अवरोध;
	पूर्ण

	वापस nr_queues;
पूर्ण

अटल व्योम nitrox_pf_cleanup(काष्ठा nitrox_device *ndev)
अणु
	 /* PF has no queues in SR-IOV mode */
	atomic_set(&ndev->state, __NDEV_NOT_READY);
	/* unरेजिस्टर crypto algorithms */
	nitrox_crypto_unरेजिस्टर();

	/* cleanup PF resources */
	nitrox_unरेजिस्टर_पूर्णांकerrupts(ndev);
	nitrox_common_sw_cleanup(ndev);
पूर्ण

/**
 * nitrox_pf_reinit - re-initialize PF resources once SR-IOV is disabled
 * @ndev: NITROX device
 */
अटल पूर्णांक nitrox_pf_reinit(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक err;

	/* allocate resources क्रम PF */
	err = nitrox_common_sw_init(ndev);
	अगर (err)
		वापस err;

	err = nitrox_रेजिस्टर_पूर्णांकerrupts(ndev);
	अगर (err) अणु
		nitrox_common_sw_cleanup(ndev);
		वापस err;
	पूर्ण

	/* configure the AQM queues */
	nitrox_config_aqm_rings(ndev);

	/* configure the packet queues */
	nitrox_config_pkt_input_rings(ndev);
	nitrox_config_pkt_solicit_ports(ndev);

	/* set device to पढ़ोy state */
	atomic_set(&ndev->state, __NDEV_READY);

	/* रेजिस्टर crypto algorithms */
	वापस nitrox_crypto_रेजिस्टर();
पूर्ण

अटल व्योम nitrox_sriov_cleanup(काष्ठा nitrox_device *ndev)
अणु
	/* unरेजिस्टर पूर्णांकerrupts क्रम PF in SR-IOV */
	nitrox_sriov_unरेजिस्टर_पूर्णांकerrupts(ndev);
	nitrox_mbox_cleanup(ndev);
पूर्ण

अटल पूर्णांक nitrox_sriov_init(काष्ठा nitrox_device *ndev)
अणु
	पूर्णांक ret;

	/* रेजिस्टर पूर्णांकerrupts क्रम PF in SR-IOV */
	ret = nitrox_sriov_रेजिस्टर_पूर्णांकerupts(ndev);
	अगर (ret)
		वापस ret;

	ret = nitrox_mbox_init(ndev);
	अगर (ret)
		जाओ sriov_init_fail;

	वापस 0;

sriov_init_fail:
	nitrox_sriov_cleanup(ndev);
	वापस ret;
पूर्ण

अटल पूर्णांक nitrox_sriov_enable(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा nitrox_device *ndev = pci_get_drvdata(pdev);
	पूर्णांक err;

	अगर (!num_vfs_valid(num_vfs)) अणु
		dev_err(DEV(ndev), "Invalid num_vfs %d\n", num_vfs);
		वापस -EINVAL;
	पूर्ण

	अगर (pci_num_vf(pdev) == num_vfs)
		वापस num_vfs;

	err = pci_enable_sriov(pdev, num_vfs);
	अगर (err) अणु
		dev_err(DEV(ndev), "failed to enable PCI sriov %d\n", err);
		वापस err;
	पूर्ण
	dev_info(DEV(ndev), "Enabled VF(s) %d\n", num_vfs);

	ndev->mode = num_vfs_to_mode(num_vfs);
	ndev->iov.num_vfs = num_vfs;
	ndev->iov.max_vf_queues = vf_mode_to_nr_queues(ndev->mode);
	/* set bit in flags */
	set_bit(__NDEV_SRIOV_BIT, &ndev->flags);

	/* cleanup PF resources */
	nitrox_pf_cleanup(ndev);

	/* PF SR-IOV mode initialization */
	err = nitrox_sriov_init(ndev);
	अगर (err)
		जाओ iov_fail;

	config_nps_core_vfcfg_mode(ndev, ndev->mode);
	वापस num_vfs;

iov_fail:
	pci_disable_sriov(pdev);
	/* clear bit in flags */
	clear_bit(__NDEV_SRIOV_BIT, &ndev->flags);
	ndev->iov.num_vfs = 0;
	ndev->mode = __NDEV_MODE_PF;
	/* reset back to working mode in PF */
	nitrox_pf_reinit(ndev);
	वापस err;
पूर्ण

अटल पूर्णांक nitrox_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nitrox_device *ndev = pci_get_drvdata(pdev);

	अगर (!test_bit(__NDEV_SRIOV_BIT, &ndev->flags))
		वापस 0;

	अगर (pci_vfs_asचिन्हित(pdev)) अणु
		dev_warn(DEV(ndev), "VFs are attached to VM. Can't disable SR-IOV\n");
		वापस -EPERM;
	पूर्ण
	pci_disable_sriov(pdev);
	/* clear bit in flags */
	clear_bit(__NDEV_SRIOV_BIT, &ndev->flags);

	ndev->iov.num_vfs = 0;
	ndev->iov.max_vf_queues = 0;
	ndev->mode = __NDEV_MODE_PF;

	/* cleanup PF SR-IOV resources */
	nitrox_sriov_cleanup(ndev);

	config_nps_core_vfcfg_mode(ndev, ndev->mode);

	वापस nitrox_pf_reinit(ndev);
पूर्ण

पूर्णांक nitrox_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	अगर (!num_vfs)
		वापस nitrox_sriov_disable(pdev);

	वापस nitrox_sriov_enable(pdev, num_vfs);
पूर्ण
