<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Express Downstream Port Containment services driver
 * Author: Keith Busch <keith.busch@पूर्णांकel.com>
 *
 * Copyright (C) 2016 Intel Corp.
 */

#घोषणा dev_fmt(fmt) "DPC: " fmt

#समावेश <linux/aer.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश "portdrv.h"
#समावेश "../pci.h"

अटल स्थिर अक्षर * स्थिर rp_pio_error_string[] = अणु
	"Configuration Request received UR Completion",	 /* Bit Position 0  */
	"Configuration Request received CA Completion",	 /* Bit Position 1  */
	"Configuration Request Completion Timeout",	 /* Bit Position 2  */
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	"I/O Request received UR Completion",		 /* Bit Position 8  */
	"I/O Request received CA Completion",		 /* Bit Position 9  */
	"I/O Request Completion Timeout",		 /* Bit Position 10 */
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	शून्य,
	"Memory Request received UR Completion",	 /* Bit Position 16 */
	"Memory Request received CA Completion",	 /* Bit Position 17 */
	"Memory Request Completion Timeout",		 /* Bit Position 18 */
पूर्ण;

व्योम pci_save_dpc_state(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_cap_saved_state *save_state;
	u16 *cap;

	अगर (!pci_is_pcie(dev))
		वापस;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_DPC);
	अगर (!save_state)
		वापस;

	cap = (u16 *)&save_state->cap.data[0];
	pci_पढ़ो_config_word(dev, dev->dpc_cap + PCI_EXP_DPC_CTL, cap);
पूर्ण

व्योम pci_restore_dpc_state(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_cap_saved_state *save_state;
	u16 *cap;

	अगर (!pci_is_pcie(dev))
		वापस;

	save_state = pci_find_saved_ext_cap(dev, PCI_EXT_CAP_ID_DPC);
	अगर (!save_state)
		वापस;

	cap = (u16 *)&save_state->cap.data[0];
	pci_ग_लिखो_config_word(dev, dev->dpc_cap + PCI_EXP_DPC_CTL, *cap);
पूर्ण

अटल पूर्णांक dpc_रुको_rp_inactive(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;
	u16 cap = pdev->dpc_cap, status;

	pci_पढ़ो_config_word(pdev, cap + PCI_EXP_DPC_STATUS, &status);
	जबतक (status & PCI_EXP_DPC_RP_BUSY &&
					!समय_after(jअगरfies, समयout)) अणु
		msleep(10);
		pci_पढ़ो_config_word(pdev, cap + PCI_EXP_DPC_STATUS, &status);
	पूर्ण
	अगर (status & PCI_EXP_DPC_RP_BUSY) अणु
		pci_warn(pdev, "root port still busy\n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

pci_ers_result_t dpc_reset_link(काष्ठा pci_dev *pdev)
अणु
	u16 cap;

	/*
	 * DPC disables the Link स्वतःmatically in hardware, so it has
	 * alपढ़ोy been reset by the समय we get here.
	 */
	cap = pdev->dpc_cap;

	/*
	 * Wait until the Link is inactive, then clear DPC Trigger Status
	 * to allow the Port to leave DPC.
	 */
	अगर (!pcie_रुको_क्रम_link(pdev, false))
		pci_info(pdev, "Data Link Layer Link Active not cleared in 1000 msec\n");

	अगर (pdev->dpc_rp_extensions && dpc_रुको_rp_inactive(pdev))
		वापस PCI_ERS_RESULT_DISCONNECT;

	pci_ग_लिखो_config_word(pdev, cap + PCI_EXP_DPC_STATUS,
			      PCI_EXP_DPC_STATUS_TRIGGER);

	अगर (!pcie_रुको_क्रम_link(pdev, true)) अणु
		pci_info(pdev, "Data Link Layer Link Active not set in 1000 msec\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

अटल व्योम dpc_process_rp_pio_error(काष्ठा pci_dev *pdev)
अणु
	u16 cap = pdev->dpc_cap, dpc_status, first_error;
	u32 status, mask, sev, syserr, exc, dw0, dw1, dw2, dw3, log, prefix;
	पूर्णांक i;

	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_STATUS, &status);
	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_MASK, &mask);
	pci_err(pdev, "rp_pio_status: %#010x, rp_pio_mask: %#010x\n",
		status, mask);

	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_SEVERITY, &sev);
	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_SYSERROR, &syserr);
	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_EXCEPTION, &exc);
	pci_err(pdev, "RP PIO severity=%#010x, syserror=%#010x, exception=%#010x\n",
		sev, syserr, exc);

	/* Get First Error Poपूर्णांकer */
	pci_पढ़ो_config_word(pdev, cap + PCI_EXP_DPC_STATUS, &dpc_status);
	first_error = (dpc_status & 0x1f00) >> 8;

	क्रम (i = 0; i < ARRAY_SIZE(rp_pio_error_string); i++) अणु
		अगर ((status & ~mask) & (1 << i))
			pci_err(pdev, "[%2d] %s%s\n", i, rp_pio_error_string[i],
				first_error == i ? " (First)" : "");
	पूर्ण

	अगर (pdev->dpc_rp_log_size < 4)
		जाओ clear_status;
	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_HEADER_LOG,
			      &dw0);
	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_HEADER_LOG + 4,
			      &dw1);
	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_HEADER_LOG + 8,
			      &dw2);
	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_HEADER_LOG + 12,
			      &dw3);
	pci_err(pdev, "TLP Header: %#010x %#010x %#010x %#010x\n",
		dw0, dw1, dw2, dw3);

	अगर (pdev->dpc_rp_log_size < 5)
		जाओ clear_status;
	pci_पढ़ो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_IMPSPEC_LOG, &log);
	pci_err(pdev, "RP PIO ImpSpec Log %#010x\n", log);

	क्रम (i = 0; i < pdev->dpc_rp_log_size - 5; i++) अणु
		pci_पढ़ो_config_dword(pdev,
			cap + PCI_EXP_DPC_RP_PIO_TLPPREFIX_LOG, &prefix);
		pci_err(pdev, "TLP Prefix Header: dw%d, %#010x\n", i, prefix);
	पूर्ण
 clear_status:
	pci_ग_लिखो_config_dword(pdev, cap + PCI_EXP_DPC_RP_PIO_STATUS, status);
पूर्ण

अटल पूर्णांक dpc_get_aer_uncorrect_severity(काष्ठा pci_dev *dev,
					  काष्ठा aer_err_info *info)
अणु
	पूर्णांक pos = dev->aer_cap;
	u32 status, mask, sev;

	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS, &status);
	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_UNCOR_MASK, &mask);
	status &= ~mask;
	अगर (!status)
		वापस 0;

	pci_पढ़ो_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, &sev);
	status &= sev;
	अगर (status)
		info->severity = AER_FATAL;
	अन्यथा
		info->severity = AER_NONFATAL;

	वापस 1;
पूर्ण

व्योम dpc_process_error(काष्ठा pci_dev *pdev)
अणु
	u16 cap = pdev->dpc_cap, status, source, reason, ext_reason;
	काष्ठा aer_err_info info;

	pci_पढ़ो_config_word(pdev, cap + PCI_EXP_DPC_STATUS, &status);
	pci_पढ़ो_config_word(pdev, cap + PCI_EXP_DPC_SOURCE_ID, &source);

	pci_info(pdev, "containment event, status:%#06x source:%#06x\n",
		 status, source);

	reason = (status & PCI_EXP_DPC_STATUS_TRIGGER_RSN) >> 1;
	ext_reason = (status & PCI_EXP_DPC_STATUS_TRIGGER_RSN_EXT) >> 5;
	pci_warn(pdev, "%s detected\n",
		 (reason == 0) ? "unmasked uncorrectable error" :
		 (reason == 1) ? "ERR_NONFATAL" :
		 (reason == 2) ? "ERR_FATAL" :
		 (ext_reason == 0) ? "RP PIO error" :
		 (ext_reason == 1) ? "software trigger" :
				     "reserved error");

	/* show RP PIO error detail inक्रमmation */
	अगर (pdev->dpc_rp_extensions && reason == 3 && ext_reason == 0)
		dpc_process_rp_pio_error(pdev);
	अन्यथा अगर (reason == 0 &&
		 dpc_get_aer_uncorrect_severity(pdev, &info) &&
		 aer_get_device_error_info(pdev, &info)) अणु
		aer_prपूर्णांक_error(pdev, &info);
		pci_aer_clear_nonfatal_status(pdev);
		pci_aer_clear_fatal_status(pdev);
	पूर्ण
पूर्ण

अटल irqवापस_t dpc_handler(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा pci_dev *pdev = context;

	dpc_process_error(pdev);

	/* We configure DPC so it only triggers on ERR_FATAL */
	pcie_करो_recovery(pdev, pci_channel_io_frozen, dpc_reset_link);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dpc_irq(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा pci_dev *pdev = context;
	u16 cap = pdev->dpc_cap, status;

	pci_पढ़ो_config_word(pdev, cap + PCI_EXP_DPC_STATUS, &status);

	अगर (!(status & PCI_EXP_DPC_STATUS_INTERRUPT) || status == (u16)(~0))
		वापस IRQ_NONE;

	pci_ग_लिखो_config_word(pdev, cap + PCI_EXP_DPC_STATUS,
			      PCI_EXP_DPC_STATUS_INTERRUPT);
	अगर (status & PCI_EXP_DPC_STATUS_TRIGGER)
		वापस IRQ_WAKE_THREAD;
	वापस IRQ_HANDLED;
पूर्ण

व्योम pci_dpc_init(काष्ठा pci_dev *pdev)
अणु
	u16 cap;

	pdev->dpc_cap = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_DPC);
	अगर (!pdev->dpc_cap)
		वापस;

	pci_पढ़ो_config_word(pdev, pdev->dpc_cap + PCI_EXP_DPC_CAP, &cap);
	अगर (!(cap & PCI_EXP_DPC_CAP_RP_EXT))
		वापस;

	pdev->dpc_rp_extensions = true;
	pdev->dpc_rp_log_size = (cap & PCI_EXP_DPC_RP_PIO_LOG_SIZE) >> 8;
	अगर (pdev->dpc_rp_log_size < 4 || pdev->dpc_rp_log_size > 9) अणु
		pci_err(pdev, "RP PIO log size %u is invalid\n",
			pdev->dpc_rp_log_size);
		pdev->dpc_rp_log_size = 0;
	पूर्ण
पूर्ण

#घोषणा FLAG(x, y) (((x) & (y)) ? '+' : '-')
अटल पूर्णांक dpc_probe(काष्ठा pcie_device *dev)
अणु
	काष्ठा pci_dev *pdev = dev->port;
	काष्ठा device *device = &dev->device;
	पूर्णांक status;
	u16 ctl, cap;

	अगर (!pcie_aer_is_native(pdev) && !pcie_ports_dpc_native)
		वापस -ENOTSUPP;

	status = devm_request_thपढ़ोed_irq(device, dev->irq, dpc_irq,
					   dpc_handler, IRQF_SHARED,
					   "pcie-dpc", pdev);
	अगर (status) अणु
		pci_warn(pdev, "request IRQ%d failed: %d\n", dev->irq,
			 status);
		वापस status;
	पूर्ण

	pci_पढ़ो_config_word(pdev, pdev->dpc_cap + PCI_EXP_DPC_CAP, &cap);
	pci_पढ़ो_config_word(pdev, pdev->dpc_cap + PCI_EXP_DPC_CTL, &ctl);

	ctl = (ctl & 0xfff4) | PCI_EXP_DPC_CTL_EN_FATAL | PCI_EXP_DPC_CTL_INT_EN;
	pci_ग_लिखो_config_word(pdev, pdev->dpc_cap + PCI_EXP_DPC_CTL, ctl);
	pci_info(pdev, "enabled with IRQ %d\n", dev->irq);

	pci_info(pdev, "error containment capabilities: Int Msg #%d, RPExt%c PoisonedTLP%c SwTrigger%c RP PIO Log %d, DL_ActiveErr%c\n",
		 cap & PCI_EXP_DPC_IRQ, FLAG(cap, PCI_EXP_DPC_CAP_RP_EXT),
		 FLAG(cap, PCI_EXP_DPC_CAP_POISONED_TLP),
		 FLAG(cap, PCI_EXP_DPC_CAP_SW_TRIGGER), pdev->dpc_rp_log_size,
		 FLAG(cap, PCI_EXP_DPC_CAP_DL_ACTIVE));

	pci_add_ext_cap_save_buffer(pdev, PCI_EXT_CAP_ID_DPC, माप(u16));
	वापस status;
पूर्ण

अटल व्योम dpc_हटाओ(काष्ठा pcie_device *dev)
अणु
	काष्ठा pci_dev *pdev = dev->port;
	u16 ctl;

	pci_पढ़ो_config_word(pdev, pdev->dpc_cap + PCI_EXP_DPC_CTL, &ctl);
	ctl &= ~(PCI_EXP_DPC_CTL_EN_FATAL | PCI_EXP_DPC_CTL_INT_EN);
	pci_ग_लिखो_config_word(pdev, pdev->dpc_cap + PCI_EXP_DPC_CTL, ctl);
पूर्ण

अटल काष्ठा pcie_port_service_driver dpcdriver = अणु
	.name		= "dpc",
	.port_type	= PCIE_ANY_PORT,
	.service	= PCIE_PORT_SERVICE_DPC,
	.probe		= dpc_probe,
	.हटाओ		= dpc_हटाओ,
पूर्ण;

पूर्णांक __init pcie_dpc_init(व्योम)
अणु
	वापस pcie_port_service_रेजिस्टर(&dpcdriver);
पूर्ण
