<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

#समावेश <linux/pci.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmi.h>
#समावेश <linux/dma-mapping.h>

#समावेश "xhci.h"
#समावेश "xhci-trace.h"
#समावेश "xhci-debugfs.h"
#समावेश "xhci-dbgcap.h"

#घोषणा DRIVER_AUTHOR "Sarah Sharp"
#घोषणा DRIVER_DESC "'eXtensible' Host Controller (xHC) Driver"

#घोषणा	PORT_WAKE_BITS	(PORT_WKOC_E | PORT_WKDISC_E | PORT_WKCONN_E)

/* Some 0.95 hardware can't handle the chain bit on a Link TRB being cleared */
अटल पूर्णांक link_quirk;
module_param(link_quirk, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(link_quirk, "Don't clear the chain bit on a link TRB");

अटल अचिन्हित दीर्घ दीर्घ quirks;
module_param(quirks, ulदीर्घ, S_IRUGO);
MODULE_PARM_DESC(quirks, "Bit flags for quirks to be enabled as default");

अटल bool td_on_ring(काष्ठा xhci_td *td, काष्ठा xhci_ring *ring)
अणु
	काष्ठा xhci_segment *seg = ring->first_seg;

	अगर (!td || !td->start_seg)
		वापस false;
	करो अणु
		अगर (seg == td->start_seg)
			वापस true;
		seg = seg->next;
	पूर्ण जबतक (seg && seg != ring->first_seg);

	वापस false;
पूर्ण

/*
 * xhci_handshake - spin पढ़ोing hc until handshake completes or fails
 * @ptr: address of hc रेजिस्टर to be पढ़ो
 * @mask: bits to look at in result of पढ़ो
 * @करोne: value of those bits when handshake succeeds
 * @usec: समयout in microseconds
 *
 * Returns negative त्रुटि_सं, or zero on success
 *
 * Success happens when the "mask" bits have the specअगरied value (hardware
 * handshake करोne).  There are two failure modes:  "usec" have passed (major
 * hardware flakeout), or the रेजिस्टर पढ़ोs as all-ones (hardware हटाओd).
 */
पूर्णांक xhci_handshake(व्योम __iomem *ptr, u32 mask, u32 करोne, पूर्णांक usec)
अणु
	u32	result;
	पूर्णांक	ret;

	ret = पढ़ोl_poll_समयout_atomic(ptr, result,
					(result & mask) == करोne ||
					result == U32_MAX,
					1, usec);
	अगर (result == U32_MAX)		/* card हटाओd */
		वापस -ENODEV;

	वापस ret;
पूर्ण

/*
 * Disable पूर्णांकerrupts and begin the xHCI halting process.
 */
व्योम xhci_quiesce(काष्ठा xhci_hcd *xhci)
अणु
	u32 halted;
	u32 cmd;
	u32 mask;

	mask = ~(XHCI_IRQS);
	halted = पढ़ोl(&xhci->op_regs->status) & STS_HALT;
	अगर (!halted)
		mask &= ~CMD_RUN;

	cmd = पढ़ोl(&xhci->op_regs->command);
	cmd &= mask;
	ग_लिखोl(cmd, &xhci->op_regs->command);
पूर्ण

/*
 * Force HC पूर्णांकo halt state.
 *
 * Disable any IRQs and clear the run/stop bit.
 * HC will complete any current and actively pipelined transactions, and
 * should halt within 16 ms of the run/stop bit being cleared.
 * Read HC Halted bit in the status रेजिस्टर to see when the HC is finished.
 */
पूर्णांक xhci_halt(काष्ठा xhci_hcd *xhci)
अणु
	पूर्णांक ret;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "// Halt the HC");
	xhci_quiesce(xhci);

	ret = xhci_handshake(&xhci->op_regs->status,
			STS_HALT, STS_HALT, XHCI_MAX_HALT_USEC);
	अगर (ret) अणु
		xhci_warn(xhci, "Host halt failed, %d\n", ret);
		वापस ret;
	पूर्ण
	xhci->xhc_state |= XHCI_STATE_HALTED;
	xhci->cmd_ring_state = CMD_RING_STATE_STOPPED;
	वापस ret;
पूर्ण

/*
 * Set the run bit and रुको क्रम the host to be running.
 */
पूर्णांक xhci_start(काष्ठा xhci_hcd *xhci)
अणु
	u32 temp;
	पूर्णांक ret;

	temp = पढ़ोl(&xhci->op_regs->command);
	temp |= (CMD_RUN);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "// Turn on HC, cmd = 0x%x.",
			temp);
	ग_लिखोl(temp, &xhci->op_regs->command);

	/*
	 * Wait क्रम the HCHalted Status bit to be 0 to indicate the host is
	 * running.
	 */
	ret = xhci_handshake(&xhci->op_regs->status,
			STS_HALT, 0, XHCI_MAX_HALT_USEC);
	अगर (ret == -ETIMEDOUT)
		xhci_err(xhci, "Host took too long to start, "
				"waited %u microseconds.\n",
				XHCI_MAX_HALT_USEC);
	अगर (!ret)
		/* clear state flags. Including dying, halted or removing */
		xhci->xhc_state = 0;

	वापस ret;
पूर्ण

/*
 * Reset a halted HC.
 *
 * This resets pipelines, समयrs, counters, state machines, etc.
 * Transactions will be terminated immediately, and operational रेजिस्टरs
 * will be set to their शेषs.
 */
पूर्णांक xhci_reset(काष्ठा xhci_hcd *xhci)
अणु
	u32 command;
	u32 state;
	पूर्णांक ret;

	state = पढ़ोl(&xhci->op_regs->status);

	अगर (state == ~(u32)0) अणु
		xhci_warn(xhci, "Host not accessible, reset failed.\n");
		वापस -ENODEV;
	पूर्ण

	अगर ((state & STS_HALT) == 0) अणु
		xhci_warn(xhci, "Host controller not halted, aborting reset.\n");
		वापस 0;
	पूर्ण

	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "// Reset the HC");
	command = पढ़ोl(&xhci->op_regs->command);
	command |= CMD_RESET;
	ग_लिखोl(command, &xhci->op_regs->command);

	/* Existing Intel xHCI controllers require a delay of 1 mS,
	 * after setting the CMD_RESET bit, and beक्रमe accessing any
	 * HC रेजिस्टरs. This allows the HC to complete the
	 * reset operation and be पढ़ोy क्रम HC रेजिस्टर access.
	 * Without this delay, the subsequent HC रेजिस्टर access,
	 * may result in a प्रणाली hang very rarely.
	 */
	अगर (xhci->quirks & XHCI_INTEL_HOST)
		udelay(1000);

	ret = xhci_handshake(&xhci->op_regs->command,
			CMD_RESET, 0, 10 * 1000 * 1000);
	अगर (ret)
		वापस ret;

	अगर (xhci->quirks & XHCI_ASMEDIA_MODIFY_FLOWCONTROL)
		usb_यंत्रedia_modअगरyflowcontrol(to_pci_dev(xhci_to_hcd(xhci)->self.controller));

	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			 "Wait for controller to be ready for doorbell rings");
	/*
	 * xHCI cannot ग_लिखो to any करोorbells or operational रेजिस्टरs other
	 * than status until the "Controller Not Ready" flag is cleared.
	 */
	ret = xhci_handshake(&xhci->op_regs->status,
			STS_CNR, 0, 10 * 1000 * 1000);

	xhci->usb2_rhub.bus_state.port_c_suspend = 0;
	xhci->usb2_rhub.bus_state.suspended_ports = 0;
	xhci->usb2_rhub.bus_state.resuming_ports = 0;
	xhci->usb3_rhub.bus_state.port_c_suspend = 0;
	xhci->usb3_rhub.bus_state.suspended_ports = 0;
	xhci->usb3_rhub.bus_state.resuming_ports = 0;

	वापस ret;
पूर्ण

अटल व्योम xhci_zero_64b_regs(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;
	पूर्णांक err, i;
	u64 val;
	u32 पूर्णांकrs;

	/*
	 * Some Renesas controllers get पूर्णांकo a weird state अगर they are
	 * reset जबतक programmed with 64bit addresses (they will preserve
	 * the top half of the address in पूर्णांकernal, non visible
	 * रेजिस्टरs). You end up with half the address coming from the
	 * kernel, and the other half coming from the firmware. Also,
	 * changing the programming leads to extra accesses even अगर the
	 * controller is supposed to be halted. The controller ends up with
	 * a fatal fault, and is then ripe क्रम being properly reset.
	 *
	 * Special care is taken to only apply this अगर the device is behind
	 * an iommu. Doing anything when there is no iommu is definitely
	 * unsafe...
	 */
	अगर (!(xhci->quirks & XHCI_ZERO_64B_REGS) || !device_iommu_mapped(dev))
		वापस;

	xhci_info(xhci, "Zeroing 64bit base registers, expecting fault\n");

	/* Clear HSEIE so that faults करो not get संकेतed */
	val = पढ़ोl(&xhci->op_regs->command);
	val &= ~CMD_HSEIE;
	ग_लिखोl(val, &xhci->op_regs->command);

	/* Clear HSE (aka FATAL) */
	val = पढ़ोl(&xhci->op_regs->status);
	val |= STS_FATAL;
	ग_लिखोl(val, &xhci->op_regs->status);

	/* Now zero the रेजिस्टरs, and brace क्रम impact */
	val = xhci_पढ़ो_64(xhci, &xhci->op_regs->dcbaa_ptr);
	अगर (upper_32_bits(val))
		xhci_ग_लिखो_64(xhci, 0, &xhci->op_regs->dcbaa_ptr);
	val = xhci_पढ़ो_64(xhci, &xhci->op_regs->cmd_ring);
	अगर (upper_32_bits(val))
		xhci_ग_लिखो_64(xhci, 0, &xhci->op_regs->cmd_ring);

	पूर्णांकrs = min_t(u32, HCS_MAX_INTRS(xhci->hcs_params1),
		      ARRAY_SIZE(xhci->run_regs->ir_set));

	क्रम (i = 0; i < पूर्णांकrs; i++) अणु
		काष्ठा xhci_पूर्णांकr_reg __iomem *ir;

		ir = &xhci->run_regs->ir_set[i];
		val = xhci_पढ़ो_64(xhci, &ir->erst_base);
		अगर (upper_32_bits(val))
			xhci_ग_लिखो_64(xhci, 0, &ir->erst_base);
		val= xhci_पढ़ो_64(xhci, &ir->erst_dequeue);
		अगर (upper_32_bits(val))
			xhci_ग_लिखो_64(xhci, 0, &ir->erst_dequeue);
	पूर्ण

	/* Wait क्रम the fault to appear. It will be cleared on reset */
	err = xhci_handshake(&xhci->op_regs->status,
			     STS_FATAL, STS_FATAL,
			     XHCI_MAX_HALT_USEC);
	अगर (!err)
		xhci_info(xhci, "Fault detected\n");
पूर्ण

#अगर_घोषित CONFIG_USB_PCI
/*
 * Set up MSI
 */
अटल पूर्णांक xhci_setup_msi(काष्ठा xhci_hcd *xhci)
अणु
	पूर्णांक ret;
	/*
	 * TODO:Check with MSI Soc क्रम sysdev
	 */
	काष्ठा pci_dev  *pdev = to_pci_dev(xhci_to_hcd(xhci)->self.controller);

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
	अगर (ret < 0) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_init,
				"failed to allocate MSI entry");
		वापस ret;
	पूर्ण

	ret = request_irq(pdev->irq, xhci_msi_irq,
				0, "xhci_hcd", xhci_to_hcd(xhci));
	अगर (ret) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_init,
				"disable MSI interrupt");
		pci_मुक्त_irq_vectors(pdev);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Set up MSI-X
 */
अटल पूर्णांक xhci_setup_msix(काष्ठा xhci_hcd *xhci)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा usb_hcd *hcd = xhci_to_hcd(xhci);
	काष्ठा pci_dev *pdev = to_pci_dev(hcd->self.controller);

	/*
	 * calculate number of msi-x vectors supported.
	 * - HCS_MAX_INTRS: the max number of पूर्णांकerrupts the host can handle,
	 *   with max number of पूर्णांकerrupters based on the xhci HCSPARAMS1.
	 * - num_online_cpus: maximum msi-x vectors per CPUs core.
	 *   Add additional 1 vector to ensure always available पूर्णांकerrupt.
	 */
	xhci->msix_count = min(num_online_cpus() + 1,
				HCS_MAX_INTRS(xhci->hcs_params1));

	ret = pci_alloc_irq_vectors(pdev, xhci->msix_count, xhci->msix_count,
			PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_init,
				"Failed to enable MSI-X");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < xhci->msix_count; i++) अणु
		ret = request_irq(pci_irq_vector(pdev, i), xhci_msi_irq, 0,
				"xhci_hcd", xhci_to_hcd(xhci));
		अगर (ret)
			जाओ disable_msix;
	पूर्ण

	hcd->msix_enabled = 1;
	वापस ret;

disable_msix:
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "disable MSI-X interrupt");
	जबतक (--i >= 0)
		मुक्त_irq(pci_irq_vector(pdev, i), xhci_to_hcd(xhci));
	pci_मुक्त_irq_vectors(pdev);
	वापस ret;
पूर्ण

/* Free any IRQs and disable MSI-X */
अटल व्योम xhci_cleanup_msix(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा usb_hcd *hcd = xhci_to_hcd(xhci);
	काष्ठा pci_dev *pdev = to_pci_dev(hcd->self.controller);

	अगर (xhci->quirks & XHCI_PLAT)
		वापस;

	/* वापस अगर using legacy पूर्णांकerrupt */
	अगर (hcd->irq > 0)
		वापस;

	अगर (hcd->msix_enabled) अणु
		पूर्णांक i;

		क्रम (i = 0; i < xhci->msix_count; i++)
			मुक्त_irq(pci_irq_vector(pdev, i), xhci_to_hcd(xhci));
	पूर्ण अन्यथा अणु
		मुक्त_irq(pci_irq_vector(pdev, 0), xhci_to_hcd(xhci));
	पूर्ण

	pci_मुक्त_irq_vectors(pdev);
	hcd->msix_enabled = 0;
पूर्ण

अटल व्योम __maybe_unused xhci_msix_sync_irqs(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा usb_hcd *hcd = xhci_to_hcd(xhci);

	अगर (hcd->msix_enabled) अणु
		काष्ठा pci_dev *pdev = to_pci_dev(hcd->self.controller);
		पूर्णांक i;

		क्रम (i = 0; i < xhci->msix_count; i++)
			synchronize_irq(pci_irq_vector(pdev, i));
	पूर्ण
पूर्ण

अटल पूर्णांक xhci_try_enable_msi(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा pci_dev  *pdev;
	पूर्णांक ret;

	/* The xhci platक्रमm device has set up IRQs through usb_add_hcd. */
	अगर (xhci->quirks & XHCI_PLAT)
		वापस 0;

	pdev = to_pci_dev(xhci_to_hcd(xhci)->self.controller);
	/*
	 * Some Fresco Logic host controllers advertise MSI, but fail to
	 * generate पूर्णांकerrupts.  Don't even try to enable MSI.
	 */
	अगर (xhci->quirks & XHCI_BROKEN_MSI)
		जाओ legacy_irq;

	/* unरेजिस्टर the legacy पूर्णांकerrupt */
	अगर (hcd->irq)
		मुक्त_irq(hcd->irq, hcd);
	hcd->irq = 0;

	ret = xhci_setup_msix(xhci);
	अगर (ret)
		/* fall back to msi*/
		ret = xhci_setup_msi(xhci);

	अगर (!ret) अणु
		hcd->msi_enabled = 1;
		वापस 0;
	पूर्ण

	अगर (!pdev->irq) अणु
		xhci_err(xhci, "No msi-x/msi found and no IRQ in BIOS\n");
		वापस -EINVAL;
	पूर्ण

 legacy_irq:
	अगर (!म_माप(hcd->irq_descr))
		snम_लिखो(hcd->irq_descr, माप(hcd->irq_descr), "%s:usb%d",
			 hcd->driver->description, hcd->self.busnum);

	/* fall back to legacy पूर्णांकerrupt*/
	ret = request_irq(pdev->irq, &usb_hcd_irq, IRQF_SHARED,
			hcd->irq_descr, hcd);
	अगर (ret) अणु
		xhci_err(xhci, "request interrupt %d failed\n",
				pdev->irq);
		वापस ret;
	पूर्ण
	hcd->irq = pdev->irq;
	वापस 0;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक xhci_try_enable_msi(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xhci_cleanup_msix(काष्ठा xhci_hcd *xhci)
अणु
पूर्ण

अटल अंतरभूत व्योम xhci_msix_sync_irqs(काष्ठा xhci_hcd *xhci)
अणु
पूर्ण

#पूर्ण_अगर

अटल व्योम compliance_mode_recovery(काष्ठा समयr_list *t)
अणु
	काष्ठा xhci_hcd *xhci;
	काष्ठा usb_hcd *hcd;
	काष्ठा xhci_hub *rhub;
	u32 temp;
	पूर्णांक i;

	xhci = from_समयr(xhci, t, comp_mode_recovery_समयr);
	rhub = &xhci->usb3_rhub;

	क्रम (i = 0; i < rhub->num_ports; i++) अणु
		temp = पढ़ोl(rhub->ports[i]->addr);
		अगर ((temp & PORT_PLS_MASK) == USB_SS_PORT_LS_COMP_MOD) अणु
			/*
			 * Compliance Mode Detected. Letting USB Core
			 * handle the Warm Reset
			 */
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
					"Compliance mode detected->port %d",
					i + 1);
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
					"Attempting compliance mode recovery");
			hcd = xhci->shared_hcd;

			अगर (hcd->state == HC_STATE_SUSPENDED)
				usb_hcd_resume_root_hub(hcd);

			usb_hcd_poll_rh_status(hcd);
		पूर्ण
	पूर्ण

	अगर (xhci->port_status_u0 != ((1 << rhub->num_ports) - 1))
		mod_समयr(&xhci->comp_mode_recovery_समयr,
			jअगरfies + msecs_to_jअगरfies(COMP_MODE_RCVRY_MSECS));
पूर्ण

/*
 * Quirk to work around issue generated by the SN65LVPE502CP USB3.0 re-driver
 * that causes ports behind that hardware to enter compliance mode someबार.
 * The quirk creates a समयr that polls every 2 seconds the link state of
 * each host controller's port and recovers it by issuing a Warm reset
 * अगर Compliance mode is detected, otherwise the port will become "dead" (no
 * device connections or disconnections will be detected anymore). Becasue no
 * status event is generated when entering compliance mode (per xhci spec),
 * this quirk is needed on प्रणालीs that have the failing hardware installed.
 */
अटल व्योम compliance_mode_recovery_समयr_init(काष्ठा xhci_hcd *xhci)
अणु
	xhci->port_status_u0 = 0;
	समयr_setup(&xhci->comp_mode_recovery_समयr, compliance_mode_recovery,
		    0);
	xhci->comp_mode_recovery_समयr.expires = jअगरfies +
			msecs_to_jअगरfies(COMP_MODE_RCVRY_MSECS);

	add_समयr(&xhci->comp_mode_recovery_समयr);
	xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
			"Compliance mode recovery timer initialized");
पूर्ण

/*
 * This function identअगरies the प्रणालीs that have installed the SN65LVPE502CP
 * USB3.0 re-driver and that need the Compliance Mode Quirk.
 * Systems:
 * Venकरोr: Hewlett-Packard -> System Models: Z420, Z620 and Z820
 */
अटल bool xhci_compliance_mode_recovery_समयr_quirk_check(व्योम)
अणु
	स्थिर अक्षर *dmi_product_name, *dmi_sys_venकरोr;

	dmi_product_name = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	dmi_sys_venकरोr = dmi_get_प्रणाली_info(DMI_SYS_VENDOR);
	अगर (!dmi_product_name || !dmi_sys_venकरोr)
		वापस false;

	अगर (!(म_माला(dmi_sys_venकरोr, "Hewlett-Packard")))
		वापस false;

	अगर (म_माला(dmi_product_name, "Z420") ||
			म_माला(dmi_product_name, "Z620") ||
			म_माला(dmi_product_name, "Z820") ||
			म_माला(dmi_product_name, "Z1 Workstation"))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक xhci_all_ports_seen_u0(काष्ठा xhci_hcd *xhci)
अणु
	वापस (xhci->port_status_u0 == ((1 << xhci->usb3_rhub.num_ports) - 1));
पूर्ण


/*
 * Initialize memory क्रम HCD and xHC (one-समय init).
 *
 * Program the PAGESIZE रेजिस्टर, initialize the device context array, create
 * device contexts (?), set up a command ring segment (or two?), create event
 * ring (one क्रम now).
 */
अटल पूर्णांक xhci_init(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	पूर्णांक retval = 0;

	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "xhci_init");
	spin_lock_init(&xhci->lock);
	अगर (xhci->hci_version == 0x95 && link_quirk) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"QUIRK: Not clearing Link TRB chain bits.");
		xhci->quirks |= XHCI_LINK_TRB_QUIRK;
	पूर्ण अन्यथा अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_init,
				"xHCI doesn't need link TRB QUIRK");
	पूर्ण
	retval = xhci_mem_init(xhci, GFP_KERNEL);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "Finished xhci_init");

	/* Initializing Compliance Mode Recovery Data If Needed */
	अगर (xhci_compliance_mode_recovery_समयr_quirk_check()) अणु
		xhci->quirks |= XHCI_COMP_MODE_QUIRK;
		compliance_mode_recovery_समयr_init(xhci);
	पूर्ण

	वापस retval;
पूर्ण

/*-------------------------------------------------------------------------*/


अटल पूर्णांक xhci_run_finished(काष्ठा xhci_hcd *xhci)
अणु
	अगर (xhci_start(xhci)) अणु
		xhci_halt(xhci);
		वापस -ENODEV;
	पूर्ण
	xhci->shared_hcd->state = HC_STATE_RUNNING;
	xhci->cmd_ring_state = CMD_RING_STATE_RUNNING;

	अगर (xhci->quirks & XHCI_NEC_HOST)
		xhci_ring_cmd_db(xhci);

	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Finished xhci_run for USB3 roothub");
	वापस 0;
पूर्ण

/*
 * Start the HC after it was halted.
 *
 * This function is called by the USB core when the HC driver is added.
 * Its opposite is xhci_stop().
 *
 * xhci_init() must be called once beक्रमe this function can be called.
 * Reset the HC, enable device slot contexts, program DCBAAP, and
 * set command ring poपूर्णांकer and event ring poपूर्णांकer.
 *
 * Setup MSI-X vectors and enable पूर्णांकerrupts.
 */
पूर्णांक xhci_run(काष्ठा usb_hcd *hcd)
अणु
	u32 temp;
	u64 temp_64;
	पूर्णांक ret;
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);

	/* Start the xHCI host controller running only after the USB 2.0 roothub
	 * is setup.
	 */

	hcd->uses_new_polling = 1;
	अगर (!usb_hcd_is_primary_hcd(hcd))
		वापस xhci_run_finished(xhci);

	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "xhci_run");

	ret = xhci_try_enable_msi(hcd);
	अगर (ret)
		वापस ret;

	temp_64 = xhci_पढ़ो_64(xhci, &xhci->ir_set->erst_dequeue);
	temp_64 &= ~ERST_PTR_MASK;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"ERST deq = 64'h%0lx", (दीर्घ अचिन्हित पूर्णांक) temp_64);

	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Set the interrupt modulation register");
	temp = पढ़ोl(&xhci->ir_set->irq_control);
	temp &= ~ER_IRQ_INTERVAL_MASK;
	temp |= (xhci->imod_पूर्णांकerval / 250) & ER_IRQ_INTERVAL_MASK;
	ग_लिखोl(temp, &xhci->ir_set->irq_control);

	/* Set the HCD state beक्रमe we enable the irqs */
	temp = पढ़ोl(&xhci->op_regs->command);
	temp |= (CMD_EIE);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Enable interrupts, cmd = 0x%x.", temp);
	ग_लिखोl(temp, &xhci->op_regs->command);

	temp = पढ़ोl(&xhci->ir_set->irq_pending);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Enabling event ring interrupter %p by writing 0x%x to irq_pending",
			xhci->ir_set, (अचिन्हित पूर्णांक) ER_IRQ_ENABLE(temp));
	ग_लिखोl(ER_IRQ_ENABLE(temp), &xhci->ir_set->irq_pending);

	अगर (xhci->quirks & XHCI_NEC_HOST) अणु
		काष्ठा xhci_command *command;

		command = xhci_alloc_command(xhci, false, GFP_KERNEL);
		अगर (!command)
			वापस -ENOMEM;

		ret = xhci_queue_venकरोr_command(xhci, command, 0, 0, 0,
				TRB_TYPE(TRB_NEC_GET_FW));
		अगर (ret)
			xhci_मुक्त_command(xhci, command);
	पूर्ण
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Finished xhci_run for USB2 roothub");

	xhci_dbc_init(xhci);

	xhci_debugfs_init(xhci);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xhci_run);

/*
 * Stop xHCI driver.
 *
 * This function is called by the USB core when the HC driver is हटाओd.
 * Its opposite is xhci_run().
 *
 * Disable device contexts, disable IRQs, and quiesce the HC.
 * Reset the HC, finish any completed transactions, and cleanup memory.
 */
अटल व्योम xhci_stop(काष्ठा usb_hcd *hcd)
अणु
	u32 temp;
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);

	mutex_lock(&xhci->mutex);

	/* Only halt host and मुक्त memory after both hcds are हटाओd */
	अगर (!usb_hcd_is_primary_hcd(hcd)) अणु
		mutex_unlock(&xhci->mutex);
		वापस;
	पूर्ण

	xhci_dbc_निकास(xhci);

	spin_lock_irq(&xhci->lock);
	xhci->xhc_state |= XHCI_STATE_HALTED;
	xhci->cmd_ring_state = CMD_RING_STATE_STOPPED;
	xhci_halt(xhci);
	xhci_reset(xhci);
	spin_unlock_irq(&xhci->lock);

	xhci_cleanup_msix(xhci);

	/* Deleting Compliance Mode Recovery Timer */
	अगर ((xhci->quirks & XHCI_COMP_MODE_QUIRK) &&
			(!(xhci_all_ports_seen_u0(xhci)))) अणु
		del_समयr_sync(&xhci->comp_mode_recovery_समयr);
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"%s: compliance mode recovery timer deleted",
				__func__);
	पूर्ण

	अगर (xhci->quirks & XHCI_AMD_PLL_FIX)
		usb_amd_dev_put();

	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Disabling event ring interrupts");
	temp = पढ़ोl(&xhci->op_regs->status);
	ग_लिखोl((temp & ~0x1fff) | STS_EINT, &xhci->op_regs->status);
	temp = पढ़ोl(&xhci->ir_set->irq_pending);
	ग_लिखोl(ER_IRQ_DISABLE(temp), &xhci->ir_set->irq_pending);

	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "cleaning up memory");
	xhci_mem_cleanup(xhci);
	xhci_debugfs_निकास(xhci);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"xhci_stop completed - status = %x",
			पढ़ोl(&xhci->op_regs->status));
	mutex_unlock(&xhci->mutex);
पूर्ण

/*
 * Shutकरोwn HC (not bus-specअगरic)
 *
 * This is called when the machine is rebooting or halting.  We assume that the
 * machine will be घातered off, and the HC's पूर्णांकernal state will be reset.
 * Don't bother to मुक्त memory.
 *
 * This will only ever be called with the मुख्य usb_hcd (the USB3 roothub).
 */
व्योम xhci_shutकरोwn(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);

	अगर (xhci->quirks & XHCI_SPURIOUS_REBOOT)
		usb_disable_xhci_ports(to_pci_dev(hcd->self.sysdev));

	spin_lock_irq(&xhci->lock);
	xhci_halt(xhci);
	/* Workaround क्रम spurious wakeups at shutकरोwn with HSW */
	अगर (xhci->quirks & XHCI_SPURIOUS_WAKEUP)
		xhci_reset(xhci);
	spin_unlock_irq(&xhci->lock);

	xhci_cleanup_msix(xhci);

	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"xhci_shutdown completed - status = %x",
			पढ़ोl(&xhci->op_regs->status));
पूर्ण
EXPORT_SYMBOL_GPL(xhci_shutकरोwn);

#अगर_घोषित CONFIG_PM
अटल व्योम xhci_save_रेजिस्टरs(काष्ठा xhci_hcd *xhci)
अणु
	xhci->s3.command = पढ़ोl(&xhci->op_regs->command);
	xhci->s3.dev_nt = पढ़ोl(&xhci->op_regs->dev_notअगरication);
	xhci->s3.dcbaa_ptr = xhci_पढ़ो_64(xhci, &xhci->op_regs->dcbaa_ptr);
	xhci->s3.config_reg = पढ़ोl(&xhci->op_regs->config_reg);
	xhci->s3.erst_size = पढ़ोl(&xhci->ir_set->erst_size);
	xhci->s3.erst_base = xhci_पढ़ो_64(xhci, &xhci->ir_set->erst_base);
	xhci->s3.erst_dequeue = xhci_पढ़ो_64(xhci, &xhci->ir_set->erst_dequeue);
	xhci->s3.irq_pending = पढ़ोl(&xhci->ir_set->irq_pending);
	xhci->s3.irq_control = पढ़ोl(&xhci->ir_set->irq_control);
पूर्ण

अटल व्योम xhci_restore_रेजिस्टरs(काष्ठा xhci_hcd *xhci)
अणु
	ग_लिखोl(xhci->s3.command, &xhci->op_regs->command);
	ग_लिखोl(xhci->s3.dev_nt, &xhci->op_regs->dev_notअगरication);
	xhci_ग_लिखो_64(xhci, xhci->s3.dcbaa_ptr, &xhci->op_regs->dcbaa_ptr);
	ग_लिखोl(xhci->s3.config_reg, &xhci->op_regs->config_reg);
	ग_लिखोl(xhci->s3.erst_size, &xhci->ir_set->erst_size);
	xhci_ग_लिखो_64(xhci, xhci->s3.erst_base, &xhci->ir_set->erst_base);
	xhci_ग_लिखो_64(xhci, xhci->s3.erst_dequeue, &xhci->ir_set->erst_dequeue);
	ग_लिखोl(xhci->s3.irq_pending, &xhci->ir_set->irq_pending);
	ग_लिखोl(xhci->s3.irq_control, &xhci->ir_set->irq_control);
पूर्ण

अटल व्योम xhci_set_cmd_ring_deq(काष्ठा xhci_hcd *xhci)
अणु
	u64	val_64;

	/* step 2: initialize command ring buffer */
	val_64 = xhci_पढ़ो_64(xhci, &xhci->op_regs->cmd_ring);
	val_64 = (val_64 & (u64) CMD_RING_RSVD_BITS) |
		(xhci_trb_virt_to_dma(xhci->cmd_ring->deq_seg,
				      xhci->cmd_ring->dequeue) &
		 (u64) ~CMD_RING_RSVD_BITS) |
		xhci->cmd_ring->cycle_state;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Setting command ring address to 0x%llx",
			(दीर्घ अचिन्हित दीर्घ) val_64);
	xhci_ग_लिखो_64(xhci, val_64, &xhci->op_regs->cmd_ring);
पूर्ण

/*
 * The whole command ring must be cleared to zero when we suspend the host.
 *
 * The host करोesn't save the command ring poपूर्णांकer in the suspend well, so we
 * need to re-program it on resume.  Unक्रमtunately, the poपूर्णांकer must be 64-byte
 * aligned, because of the reserved bits in the command ring dequeue poपूर्णांकer
 * रेजिस्टर.  Thereक्रमe, we can't just set the dequeue poपूर्णांकer back in the
 * middle of the ring (TRBs are 16-byte aligned).
 */
अटल व्योम xhci_clear_command_ring(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा xhci_ring *ring;
	काष्ठा xhci_segment *seg;

	ring = xhci->cmd_ring;
	seg = ring->deq_seg;
	करो अणु
		स_रखो(seg->trbs, 0,
			माप(जोड़ xhci_trb) * (TRBS_PER_SEGMENT - 1));
		seg->trbs[TRBS_PER_SEGMENT - 1].link.control &=
			cpu_to_le32(~TRB_CYCLE);
		seg = seg->next;
	पूर्ण जबतक (seg != ring->deq_seg);

	/* Reset the software enqueue and dequeue poपूर्णांकers */
	ring->deq_seg = ring->first_seg;
	ring->dequeue = ring->first_seg->trbs;
	ring->enq_seg = ring->deq_seg;
	ring->enqueue = ring->dequeue;

	ring->num_trbs_मुक्त = ring->num_segs * (TRBS_PER_SEGMENT - 1) - 1;
	/*
	 * Ring is now zeroed, so the HW should look क्रम change of ownership
	 * when the cycle bit is set to 1.
	 */
	ring->cycle_state = 1;

	/*
	 * Reset the hardware dequeue poपूर्णांकer.
	 * Yes, this will need to be re-written after resume, but we're paranoid
	 * and want to make sure the hardware करोesn't access bogus memory
	 * because, say, the BIOS or an SMI started the host without changing
	 * the command ring poपूर्णांकers.
	 */
	xhci_set_cmd_ring_deq(xhci);
पूर्ण

/*
 * Disable port wake bits अगर करो_wakeup is not set.
 *
 * Also clear a possible पूर्णांकernal port wake state left hanging क्रम ports that
 * detected termination but never successfully क्रमागतerated (trained to 0U).
 * Internal wake causes immediate xHCI wake after suspend. PORT_CSC ग_लिखो करोne
 * at क्रमागतeration clears this wake, क्रमce one here as well क्रम unconnected ports
 */

अटल व्योम xhci_disable_hub_port_wake(काष्ठा xhci_hcd *xhci,
				       काष्ठा xhci_hub *rhub,
				       bool करो_wakeup)
अणु
	अचिन्हित दीर्घ flags;
	u32 t1, t2, portsc;
	पूर्णांक i;

	spin_lock_irqsave(&xhci->lock, flags);

	क्रम (i = 0; i < rhub->num_ports; i++) अणु
		portsc = पढ़ोl(rhub->ports[i]->addr);
		t1 = xhci_port_state_to_neutral(portsc);
		t2 = t1;

		/* clear wake bits अगर करो_wake is not set */
		अगर (!करो_wakeup)
			t2 &= ~PORT_WAKE_BITS;

		/* Don't touch csc bit अगर connected or connect change is set */
		अगर (!(portsc & (PORT_CSC | PORT_CONNECT)))
			t2 |= PORT_CSC;

		अगर (t1 != t2) अणु
			ग_लिखोl(t2, rhub->ports[i]->addr);
			xhci_dbg(xhci, "config port %d-%d wake bits, portsc: 0x%x, write: 0x%x\n",
				 rhub->hcd->self.busnum, i + 1, portsc, t2);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&xhci->lock, flags);
पूर्ण

अटल bool xhci_pending_portevent(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा xhci_port	**ports;
	पूर्णांक			port_index;
	u32			status;
	u32			portsc;

	status = पढ़ोl(&xhci->op_regs->status);
	अगर (status & STS_EINT)
		वापस true;
	/*
	 * Checking STS_EINT is not enough as there is a lag between a change
	 * bit being set and the Port Status Change Event that it generated
	 * being written to the Event Ring. See note in xhci 1.1 section 4.19.2.
	 */

	port_index = xhci->usb2_rhub.num_ports;
	ports = xhci->usb2_rhub.ports;
	जबतक (port_index--) अणु
		portsc = पढ़ोl(ports[port_index]->addr);
		अगर (portsc & PORT_CHANGE_MASK ||
		    (portsc & PORT_PLS_MASK) == XDEV_RESUME)
			वापस true;
	पूर्ण
	port_index = xhci->usb3_rhub.num_ports;
	ports = xhci->usb3_rhub.ports;
	जबतक (port_index--) अणु
		portsc = पढ़ोl(ports[port_index]->addr);
		अगर (portsc & PORT_CHANGE_MASK ||
		    (portsc & PORT_PLS_MASK) == XDEV_RESUME)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Stop HC (not bus-specअगरic)
 *
 * This is called when the machine transition पूर्णांकo S3/S4 mode.
 *
 */
पूर्णांक xhci_suspend(काष्ठा xhci_hcd *xhci, bool करो_wakeup)
अणु
	पूर्णांक			rc = 0;
	अचिन्हित पूर्णांक		delay = XHCI_MAX_HALT_USEC * 2;
	काष्ठा usb_hcd		*hcd = xhci_to_hcd(xhci);
	u32			command;
	u32			res;

	अगर (!hcd->state)
		वापस 0;

	अगर (hcd->state != HC_STATE_SUSPENDED ||
			xhci->shared_hcd->state != HC_STATE_SUSPENDED)
		वापस -EINVAL;

	/* Clear root port wake on bits अगर wakeup not allowed. */
	xhci_disable_hub_port_wake(xhci, &xhci->usb3_rhub, करो_wakeup);
	xhci_disable_hub_port_wake(xhci, &xhci->usb2_rhub, करो_wakeup);

	अगर (!HCD_HW_ACCESSIBLE(hcd))
		वापस 0;

	xhci_dbc_suspend(xhci);

	/* Don't poll the roothubs on bus suspend. */
	xhci_dbg(xhci, "%s: stopping port polling.\n", __func__);
	clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	del_समयr_sync(&hcd->rh_समयr);
	clear_bit(HCD_FLAG_POLL_RH, &xhci->shared_hcd->flags);
	del_समयr_sync(&xhci->shared_hcd->rh_समयr);

	अगर (xhci->quirks & XHCI_SUSPEND_DELAY)
		usleep_range(1000, 1500);

	spin_lock_irq(&xhci->lock);
	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &xhci->shared_hcd->flags);
	/* step 1: stop endpoपूर्णांक */
	/* skipped assuming that port suspend has करोne */

	/* step 2: clear Run/Stop bit */
	command = पढ़ोl(&xhci->op_regs->command);
	command &= ~CMD_RUN;
	ग_लिखोl(command, &xhci->op_regs->command);

	/* Some chips from Fresco Logic need an extraordinary delay */
	delay *= (xhci->quirks & XHCI_SLOW_SUSPEND) ? 10 : 1;

	अगर (xhci_handshake(&xhci->op_regs->status,
		      STS_HALT, STS_HALT, delay)) अणु
		xhci_warn(xhci, "WARN: xHC CMD_RUN timeout\n");
		spin_unlock_irq(&xhci->lock);
		वापस -ETIMEDOUT;
	पूर्ण
	xhci_clear_command_ring(xhci);

	/* step 3: save रेजिस्टरs */
	xhci_save_रेजिस्टरs(xhci);

	/* step 4: set CSS flag */
	command = पढ़ोl(&xhci->op_regs->command);
	command |= CMD_CSS;
	ग_लिखोl(command, &xhci->op_regs->command);
	xhci->broken_suspend = 0;
	अगर (xhci_handshake(&xhci->op_regs->status,
				STS_SAVE, 0, 20 * 1000)) अणु
	/*
	 * AMD SNPS xHC 3.0 occasionally करोes not clear the
	 * SSS bit of USBSTS and when driver tries to poll
	 * to see अगर the xHC clears BIT(8) which never happens
	 * and driver assumes that controller is not responding
	 * and बार out. To workaround this, its good to check
	 * अगर SRE and HCE bits are not set (as per xhci
	 * Section 5.4.2) and bypass the समयout.
	 */
		res = पढ़ोl(&xhci->op_regs->status);
		अगर ((xhci->quirks & XHCI_SNPS_BROKEN_SUSPEND) &&
		    (((res & STS_SRE) == 0) &&
				((res & STS_HCE) == 0))) अणु
			xhci->broken_suspend = 1;
		पूर्ण अन्यथा अणु
			xhci_warn(xhci, "WARN: xHC save state timeout\n");
			spin_unlock_irq(&xhci->lock);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&xhci->lock);

	/*
	 * Deleting Compliance Mode Recovery Timer because the xHCI Host
	 * is about to be suspended.
	 */
	अगर ((xhci->quirks & XHCI_COMP_MODE_QUIRK) &&
			(!(xhci_all_ports_seen_u0(xhci)))) अणु
		del_समयr_sync(&xhci->comp_mode_recovery_समयr);
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"%s: compliance mode recovery timer deleted",
				__func__);
	पूर्ण

	/* step 5: हटाओ core well घातer */
	/* synchronize irq when using MSI-X */
	xhci_msix_sync_irqs(xhci);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(xhci_suspend);

/*
 * start xHC (not bus-specअगरic)
 *
 * This is called when the machine transition from S3/S4 mode.
 *
 */
पूर्णांक xhci_resume(काष्ठा xhci_hcd *xhci, bool hibernated)
अणु
	u32			command, temp = 0;
	काष्ठा usb_hcd		*hcd = xhci_to_hcd(xhci);
	काष्ठा usb_hcd		*secondary_hcd;
	पूर्णांक			retval = 0;
	bool			comp_समयr_running = false;
	bool			pending_portevent = false;

	अगर (!hcd->state)
		वापस 0;

	/* Wait a bit अगर either of the roothubs need to settle from the
	 * transition पूर्णांकo bus suspend.
	 */

	अगर (समय_beक्रमe(jअगरfies, xhci->usb2_rhub.bus_state.next_statechange) ||
	    समय_beक्रमe(jअगरfies, xhci->usb3_rhub.bus_state.next_statechange))
		msleep(100);

	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &xhci->shared_hcd->flags);

	spin_lock_irq(&xhci->lock);
	अगर ((xhci->quirks & XHCI_RESET_ON_RESUME) || xhci->broken_suspend)
		hibernated = true;

	अगर (!hibernated) अणु
		/*
		 * Some controllers might lose घातer during suspend, so रुको
		 * क्रम controller not पढ़ोy bit to clear, just as in xHC init.
		 */
		retval = xhci_handshake(&xhci->op_regs->status,
					STS_CNR, 0, 10 * 1000 * 1000);
		अगर (retval) अणु
			xhci_warn(xhci, "Controller not ready at resume %d\n",
				  retval);
			spin_unlock_irq(&xhci->lock);
			वापस retval;
		पूर्ण
		/* step 1: restore रेजिस्टर */
		xhci_restore_रेजिस्टरs(xhci);
		/* step 2: initialize command ring buffer */
		xhci_set_cmd_ring_deq(xhci);
		/* step 3: restore state and start state*/
		/* step 3: set CRS flag */
		command = पढ़ोl(&xhci->op_regs->command);
		command |= CMD_CRS;
		ग_लिखोl(command, &xhci->op_regs->command);
		/*
		 * Some controllers take up to 55+ ms to complete the controller
		 * restore so setting the समयout to 100ms. Xhci specअगरication
		 * करोesn't mention any समयout value.
		 */
		अगर (xhci_handshake(&xhci->op_regs->status,
			      STS_RESTORE, 0, 100 * 1000)) अणु
			xhci_warn(xhci, "WARN: xHC restore state timeout\n");
			spin_unlock_irq(&xhci->lock);
			वापस -ETIMEDOUT;
		पूर्ण
		temp = पढ़ोl(&xhci->op_regs->status);
	पूर्ण

	/* If restore operation fails, re-initialize the HC during resume */
	अगर ((temp & STS_SRE) || hibernated) अणु

		अगर ((xhci->quirks & XHCI_COMP_MODE_QUIRK) &&
				!(xhci_all_ports_seen_u0(xhci))) अणु
			del_समयr_sync(&xhci->comp_mode_recovery_समयr);
			xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Compliance Mode Recovery Timer deleted!");
		पूर्ण

		/* Let the USB core know _both_ roothubs lost घातer. */
		usb_root_hub_lost_घातer(xhci->मुख्य_hcd->self.root_hub);
		usb_root_hub_lost_घातer(xhci->shared_hcd->self.root_hub);

		xhci_dbg(xhci, "Stop HCD\n");
		xhci_halt(xhci);
		xhci_zero_64b_regs(xhci);
		retval = xhci_reset(xhci);
		spin_unlock_irq(&xhci->lock);
		अगर (retval)
			वापस retval;
		xhci_cleanup_msix(xhci);

		xhci_dbg(xhci, "// Disabling event ring interrupts\n");
		temp = पढ़ोl(&xhci->op_regs->status);
		ग_लिखोl((temp & ~0x1fff) | STS_EINT, &xhci->op_regs->status);
		temp = पढ़ोl(&xhci->ir_set->irq_pending);
		ग_लिखोl(ER_IRQ_DISABLE(temp), &xhci->ir_set->irq_pending);

		xhci_dbg(xhci, "cleaning up memory\n");
		xhci_mem_cleanup(xhci);
		xhci_debugfs_निकास(xhci);
		xhci_dbg(xhci, "xhci_stop completed - status = %x\n",
			    पढ़ोl(&xhci->op_regs->status));

		/* USB core calls the PCI reinit and start functions twice:
		 * first with the primary HCD, and then with the secondary HCD.
		 * If we करोn't करो the same, the host will never be started.
		 */
		अगर (!usb_hcd_is_primary_hcd(hcd))
			secondary_hcd = hcd;
		अन्यथा
			secondary_hcd = xhci->shared_hcd;

		xhci_dbg(xhci, "Initialize the xhci_hcd\n");
		retval = xhci_init(hcd->primary_hcd);
		अगर (retval)
			वापस retval;
		comp_समयr_running = true;

		xhci_dbg(xhci, "Start the primary HCD\n");
		retval = xhci_run(hcd->primary_hcd);
		अगर (!retval) अणु
			xhci_dbg(xhci, "Start the secondary HCD\n");
			retval = xhci_run(secondary_hcd);
		पूर्ण
		hcd->state = HC_STATE_SUSPENDED;
		xhci->shared_hcd->state = HC_STATE_SUSPENDED;
		जाओ करोne;
	पूर्ण

	/* step 4: set Run/Stop bit */
	command = पढ़ोl(&xhci->op_regs->command);
	command |= CMD_RUN;
	ग_लिखोl(command, &xhci->op_regs->command);
	xhci_handshake(&xhci->op_regs->status, STS_HALT,
		  0, 250 * 1000);

	/* step 5: walk topology and initialize portsc,
	 * portpmsc and portli
	 */
	/* this is करोne in bus_resume */

	/* step 6: restart each of the previously
	 * Running endpoपूर्णांकs by ringing their करोorbells
	 */

	spin_unlock_irq(&xhci->lock);

	xhci_dbc_resume(xhci);

 करोne:
	अगर (retval == 0) अणु
		/*
		 * Resume roothubs only अगर there are pending events.
		 * USB 3 devices resend U3 LFPS wake after a 100ms delay अगर
		 * the first wake संकेतling failed, give it that chance.
		 */
		pending_portevent = xhci_pending_portevent(xhci);
		अगर (!pending_portevent) अणु
			msleep(120);
			pending_portevent = xhci_pending_portevent(xhci);
		पूर्ण

		अगर (pending_portevent) अणु
			usb_hcd_resume_root_hub(xhci->shared_hcd);
			usb_hcd_resume_root_hub(hcd);
		पूर्ण
	पूर्ण
	/*
	 * If प्रणाली is subject to the Quirk, Compliance Mode Timer needs to
	 * be re-initialized Always after a प्रणाली resume. Ports are subject
	 * to suffer the Compliance Mode issue again. It करोesn't matter अगर
	 * ports have entered previously to U0 beक्रमe प्रणाली's suspension.
	 */
	अगर ((xhci->quirks & XHCI_COMP_MODE_QUIRK) && !comp_समयr_running)
		compliance_mode_recovery_समयr_init(xhci);

	अगर (xhci->quirks & XHCI_ASMEDIA_MODIFY_FLOWCONTROL)
		usb_यंत्रedia_modअगरyflowcontrol(to_pci_dev(hcd->self.controller));

	/* Re-enable port polling. */
	xhci_dbg(xhci, "%s: starting port polling.\n", __func__);
	set_bit(HCD_FLAG_POLL_RH, &xhci->shared_hcd->flags);
	usb_hcd_poll_rh_status(xhci->shared_hcd);
	set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	usb_hcd_poll_rh_status(hcd);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(xhci_resume);
#पूर्ण_अगर	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

अटल पूर्णांक xhci_map_temp_buffer(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	व्योम *temp;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक buf_len;
	क्रमागत dma_data_direction dir;

	dir = usb_urb_dir_in(urb) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	buf_len = urb->transfer_buffer_length;

	temp = kzalloc_node(buf_len, GFP_ATOMIC,
			    dev_to_node(hcd->self.sysdev));

	अगर (usb_urb_dir_out(urb))
		sg_pcopy_to_buffer(urb->sg, urb->num_sgs,
				   temp, buf_len, 0);

	urb->transfer_buffer = temp;
	urb->transfer_dma = dma_map_single(hcd->self.sysdev,
					   urb->transfer_buffer,
					   urb->transfer_buffer_length,
					   dir);

	अगर (dma_mapping_error(hcd->self.sysdev,
			      urb->transfer_dma)) अणु
		ret = -EAGAIN;
		kमुक्त(temp);
	पूर्ण अन्यथा अणु
		urb->transfer_flags |= URB_DMA_MAP_SINGLE;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool xhci_urb_temp_buffer_required(काष्ठा usb_hcd *hcd,
					  काष्ठा urb *urb)
अणु
	bool ret = false;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक len = 0;
	अचिन्हित पूर्णांक trb_size;
	अचिन्हित पूर्णांक max_pkt;
	काष्ठा scatterlist *sg;
	काष्ठा scatterlist *tail_sg;

	tail_sg = urb->sg;
	max_pkt = usb_endpoपूर्णांक_maxp(&urb->ep->desc);

	अगर (!urb->num_sgs)
		वापस ret;

	अगर (urb->dev->speed >= USB_SPEED_SUPER)
		trb_size = TRB_CACHE_SIZE_SS;
	अन्यथा
		trb_size = TRB_CACHE_SIZE_HS;

	अगर (urb->transfer_buffer_length != 0 &&
	    !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)) अणु
		क्रम_each_sg(urb->sg, sg, urb->num_sgs, i) अणु
			len = len + sg->length;
			अगर (i > trb_size - 2) अणु
				len = len - tail_sg->length;
				अगर (len < max_pkt) अणु
					ret = true;
					अवरोध;
				पूर्ण

				tail_sg = sg_next(tail_sg);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम xhci_unmap_temp_buf(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक buf_len;
	क्रमागत dma_data_direction dir;

	dir = usb_urb_dir_in(urb) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	buf_len = urb->transfer_buffer_length;

	अगर (IS_ENABLED(CONFIG_HAS_DMA) &&
	    (urb->transfer_flags & URB_DMA_MAP_SINGLE))
		dma_unmap_single(hcd->self.sysdev,
				 urb->transfer_dma,
				 urb->transfer_buffer_length,
				 dir);

	अगर (usb_urb_dir_in(urb))
		len = sg_pcopy_from_buffer(urb->sg, urb->num_sgs,
					   urb->transfer_buffer,
					   buf_len,
					   0);

	urb->transfer_flags &= ~URB_DMA_MAP_SINGLE;
	kमुक्त(urb->transfer_buffer);
	urb->transfer_buffer = शून्य;
पूर्ण

/*
 * Bypass the DMA mapping अगर URB is suitable क्रम Immediate Transfer (IDT),
 * we'll copy the actual data पूर्णांकo the TRB address रेजिस्टर. This is limited to
 * transfers up to 8 bytes on output endpoपूर्णांकs of any kind with wMaxPacketSize
 * >= 8 bytes. If suitable क्रम IDT only one Transfer TRB per TD is allowed.
 */
अटल पूर्णांक xhci_map_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb,
				gfp_t mem_flags)
अणु
	काष्ठा xhci_hcd *xhci;

	xhci = hcd_to_xhci(hcd);

	अगर (xhci_urb_suitable_क्रम_idt(urb))
		वापस 0;

	अगर (xhci->quirks & XHCI_SG_TRB_CACHE_SIZE_QUIRK) अणु
		अगर (xhci_urb_temp_buffer_required(hcd, urb))
			वापस xhci_map_temp_buffer(hcd, urb);
	पूर्ण
	वापस usb_hcd_map_urb_क्रम_dma(hcd, urb, mem_flags);
पूर्ण

अटल व्योम xhci_unmap_urb_क्रम_dma(काष्ठा usb_hcd *hcd, काष्ठा urb *urb)
अणु
	काष्ठा xhci_hcd *xhci;
	bool unmap_temp_buf = false;

	xhci = hcd_to_xhci(hcd);

	अगर (urb->num_sgs && (urb->transfer_flags & URB_DMA_MAP_SINGLE))
		unmap_temp_buf = true;

	अगर ((xhci->quirks & XHCI_SG_TRB_CACHE_SIZE_QUIRK) && unmap_temp_buf)
		xhci_unmap_temp_buf(hcd, urb);
	अन्यथा
		usb_hcd_unmap_urb_क्रम_dma(hcd, urb);
पूर्ण

/**
 * xhci_get_endpoपूर्णांक_index - Used क्रम passing endpoपूर्णांक biपंचांगasks between the core and
 * HCDs.  Find the index क्रम an endpoपूर्णांक given its descriptor.  Use the वापस
 * value to right shअगरt 1 क्रम the biपंचांगask.
 *
 * Index  = (epnum * 2) + direction - 1,
 * where direction = 0 क्रम OUT, 1 क्रम IN.
 * For control endpoपूर्णांकs, the IN index is used (OUT index is unused), so
 * index = (epnum * 2) + direction - 1 = (epnum * 2) + 1 - 1 = (epnum * 2)
 */
अचिन्हित पूर्णांक xhci_get_endpoपूर्णांक_index(काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित पूर्णांक index;
	अगर (usb_endpoपूर्णांक_xfer_control(desc))
		index = (अचिन्हित पूर्णांक) (usb_endpoपूर्णांक_num(desc)*2);
	अन्यथा
		index = (अचिन्हित पूर्णांक) (usb_endpoपूर्णांक_num(desc)*2) +
			(usb_endpoपूर्णांक_dir_in(desc) ? 1 : 0) - 1;
	वापस index;
पूर्ण
EXPORT_SYMBOL_GPL(xhci_get_endpoपूर्णांक_index);

/* The reverse operation to xhci_get_endpoपूर्णांक_index. Calculate the USB endpoपूर्णांक
 * address from the XHCI endpoपूर्णांक index.
 */
अचिन्हित पूर्णांक xhci_get_endpoपूर्णांक_address(अचिन्हित पूर्णांक ep_index)
अणु
	अचिन्हित पूर्णांक number = DIV_ROUND_UP(ep_index, 2);
	अचिन्हित पूर्णांक direction = ep_index % 2 ? USB_सूची_OUT : USB_सूची_IN;
	वापस direction | number;
पूर्ण

/* Find the flag क्रम this endpoपूर्णांक (क्रम use in the control context).  Use the
 * endpoपूर्णांक index to create a biपंचांगask.  The slot context is bit 0, endpoपूर्णांक 0 is
 * bit 1, etc.
 */
अटल अचिन्हित पूर्णांक xhci_get_endpoपूर्णांक_flag(काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	वापस 1 << (xhci_get_endpoपूर्णांक_index(desc) + 1);
पूर्ण

/* Compute the last valid endpoपूर्णांक context index.  Basically, this is the
 * endpoपूर्णांक index plus one.  For slot contexts with more than valid endpoपूर्णांक,
 * we find the most signअगरicant bit set in the added contexts flags.
 * e.g. ep 1 IN (with epnum 0x81) => added_ctxs = 0b1000
 * fls(0b1000) = 4, but the endpoपूर्णांक context index is 3, so subtract one.
 */
अचिन्हित पूर्णांक xhci_last_valid_endpoपूर्णांक(u32 added_ctxs)
अणु
	वापस fls(added_ctxs) - 1;
पूर्ण

/* Returns 1 अगर the arguments are OK;
 * वापसs 0 this is a root hub; वापसs -EINVAL क्रम शून्य poपूर्णांकers.
 */
अटल पूर्णांक xhci_check_args(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep, पूर्णांक check_ep, bool check_virt_dev,
		स्थिर अक्षर *func) अणु
	काष्ठा xhci_hcd	*xhci;
	काष्ठा xhci_virt_device	*virt_dev;

	अगर (!hcd || (check_ep && !ep) || !udev) अणु
		pr_debug("xHCI %s called with invalid args\n", func);
		वापस -EINVAL;
	पूर्ण
	अगर (!udev->parent) अणु
		pr_debug("xHCI %s called for root hub\n", func);
		वापस 0;
	पूर्ण

	xhci = hcd_to_xhci(hcd);
	अगर (check_virt_dev) अणु
		अगर (!udev->slot_id || !xhci->devs[udev->slot_id]) अणु
			xhci_dbg(xhci, "xHCI %s called with unaddressed device\n",
					func);
			वापस -EINVAL;
		पूर्ण

		virt_dev = xhci->devs[udev->slot_id];
		अगर (virt_dev->udev != udev) अणु
			xhci_dbg(xhci, "xHCI %s called with udev and "
					  "virt_dev does not match\n", func);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (xhci->xhc_state & XHCI_STATE_HALTED)
		वापस -ENODEV;

	वापस 1;
पूर्ण

अटल पूर्णांक xhci_configure_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev, काष्ठा xhci_command *command,
		bool ctx_change, bool must_succeed);

/*
 * Full speed devices may have a max packet size greater than 8 bytes, but the
 * USB core करोesn't know that until it पढ़ोs the first 8 bytes of the
 * descriptor.  If the usb_device's max packet size changes after that poपूर्णांक,
 * we need to issue an evaluate context command and रुको on it.
 */
अटल पूर्णांक xhci_check_maxpacket(काष्ठा xhci_hcd *xhci, अचिन्हित पूर्णांक slot_id,
		अचिन्हित पूर्णांक ep_index, काष्ठा urb *urb, gfp_t mem_flags)
अणु
	काष्ठा xhci_container_ctx *out_ctx;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	काष्ठा xhci_ep_ctx *ep_ctx;
	काष्ठा xhci_command *command;
	पूर्णांक max_packet_size;
	पूर्णांक hw_max_packet_size;
	पूर्णांक ret = 0;

	out_ctx = xhci->devs[slot_id]->out_ctx;
	ep_ctx = xhci_get_ep_ctx(xhci, out_ctx, ep_index);
	hw_max_packet_size = MAX_PACKET_DECODED(le32_to_cpu(ep_ctx->ep_info2));
	max_packet_size = usb_endpoपूर्णांक_maxp(&urb->dev->ep0.desc);
	अगर (hw_max_packet_size != max_packet_size) अणु
		xhci_dbg_trace(xhci,  trace_xhci_dbg_context_change,
				"Max Packet Size for ep 0 changed.");
		xhci_dbg_trace(xhci,  trace_xhci_dbg_context_change,
				"Max packet size in usb_device = %d",
				max_packet_size);
		xhci_dbg_trace(xhci,  trace_xhci_dbg_context_change,
				"Max packet size in xHCI HW = %d",
				hw_max_packet_size);
		xhci_dbg_trace(xhci,  trace_xhci_dbg_context_change,
				"Issuing evaluate context command.");

		/* Set up the input context flags क्रम the command */
		/* FIXME: This won't work अगर a non-शेष control endpoपूर्णांक
		 * changes max packet sizes.
		 */

		command = xhci_alloc_command(xhci, true, mem_flags);
		अगर (!command)
			वापस -ENOMEM;

		command->in_ctx = xhci->devs[slot_id]->in_ctx;
		ctrl_ctx = xhci_get_input_control_ctx(command->in_ctx);
		अगर (!ctrl_ctx) अणु
			xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
					__func__);
			ret = -ENOMEM;
			जाओ command_cleanup;
		पूर्ण
		/* Set up the modअगरied control endpoपूर्णांक 0 */
		xhci_endpoपूर्णांक_copy(xhci, xhci->devs[slot_id]->in_ctx,
				xhci->devs[slot_id]->out_ctx, ep_index);

		ep_ctx = xhci_get_ep_ctx(xhci, command->in_ctx, ep_index);
		ep_ctx->ep_info &= cpu_to_le32(~EP_STATE_MASK);/* must clear */
		ep_ctx->ep_info2 &= cpu_to_le32(~MAX_PACKET_MASK);
		ep_ctx->ep_info2 |= cpu_to_le32(MAX_PACKET(max_packet_size));

		ctrl_ctx->add_flags = cpu_to_le32(EP0_FLAG);
		ctrl_ctx->drop_flags = 0;

		ret = xhci_configure_endpoपूर्णांक(xhci, urb->dev, command,
				true, false);

		/* Clean up the input context क्रम later use by bandwidth
		 * functions.
		 */
		ctrl_ctx->add_flags = cpu_to_le32(SLOT_FLAG);
command_cleanup:
		kमुक्त(command->completion);
		kमुक्त(command);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * non-error वापसs are a promise to giveback() the urb later
 * we drop ownership so next owner (or urb unlink) can get it
 */
अटल पूर्णांक xhci_urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, gfp_t mem_flags)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक slot_id, ep_index;
	अचिन्हित पूर्णांक *ep_state;
	काष्ठा urb_priv	*urb_priv;
	पूर्णांक num_tds;

	अगर (!urb || xhci_check_args(hcd, urb->dev, urb->ep,
					true, true, __func__) <= 0)
		वापस -EINVAL;

	slot_id = urb->dev->slot_id;
	ep_index = xhci_get_endpoपूर्णांक_index(&urb->ep->desc);
	ep_state = &xhci->devs[slot_id]->eps[ep_index].ep_state;

	अगर (!HCD_HW_ACCESSIBLE(hcd))
		वापस -ESHUTDOWN;

	अगर (xhci->devs[slot_id]->flags & VDEV_PORT_ERROR) अणु
		xhci_dbg(xhci, "Can't queue urb, port error, link inactive\n");
		वापस -ENODEV;
	पूर्ण

	अगर (usb_endpoपूर्णांक_xfer_isoc(&urb->ep->desc))
		num_tds = urb->number_of_packets;
	अन्यथा अगर (usb_endpoपूर्णांक_is_bulk_out(&urb->ep->desc) &&
	    urb->transfer_buffer_length > 0 &&
	    urb->transfer_flags & URB_ZERO_PACKET &&
	    !(urb->transfer_buffer_length % usb_endpoपूर्णांक_maxp(&urb->ep->desc)))
		num_tds = 2;
	अन्यथा
		num_tds = 1;

	urb_priv = kzalloc(काष्ठा_size(urb_priv, td, num_tds), mem_flags);
	अगर (!urb_priv)
		वापस -ENOMEM;

	urb_priv->num_tds = num_tds;
	urb_priv->num_tds_करोne = 0;
	urb->hcpriv = urb_priv;

	trace_xhci_urb_enqueue(urb);

	अगर (usb_endpoपूर्णांक_xfer_control(&urb->ep->desc)) अणु
		/* Check to see अगर the max packet size क्रम the शेष control
		 * endpoपूर्णांक changed during FS device क्रमागतeration
		 */
		अगर (urb->dev->speed == USB_SPEED_FULL) अणु
			ret = xhci_check_maxpacket(xhci, slot_id,
					ep_index, urb, mem_flags);
			अगर (ret < 0) अणु
				xhci_urb_मुक्त_priv(urb_priv);
				urb->hcpriv = शून्य;
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&xhci->lock, flags);

	अगर (xhci->xhc_state & XHCI_STATE_DYING) अणु
		xhci_dbg(xhci, "Ep 0x%x: URB %p submitted for non-responsive xHCI host.\n",
			 urb->ep->desc.bEndpoपूर्णांकAddress, urb);
		ret = -ESHUTDOWN;
		जाओ मुक्त_priv;
	पूर्ण
	अगर (*ep_state & (EP_GETTING_STREAMS | EP_GETTING_NO_STREAMS)) अणु
		xhci_warn(xhci, "WARN: Can't enqueue URB, ep in streams transition state %x\n",
			  *ep_state);
		ret = -EINVAL;
		जाओ मुक्त_priv;
	पूर्ण
	अगर (*ep_state & EP_SOFT_CLEAR_TOGGLE) अणु
		xhci_warn(xhci, "Can't enqueue URB while manually clearing toggle\n");
		ret = -EINVAL;
		जाओ मुक्त_priv;
	पूर्ण

	चयन (usb_endpoपूर्णांक_type(&urb->ep->desc)) अणु

	हाल USB_ENDPOINT_XFER_CONTROL:
		ret = xhci_queue_ctrl_tx(xhci, GFP_ATOMIC, urb,
					 slot_id, ep_index);
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		ret = xhci_queue_bulk_tx(xhci, GFP_ATOMIC, urb,
					 slot_id, ep_index);
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		ret = xhci_queue_पूर्णांकr_tx(xhci, GFP_ATOMIC, urb,
				slot_id, ep_index);
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		ret = xhci_queue_isoc_tx_prepare(xhci, GFP_ATOMIC, urb,
				slot_id, ep_index);
	पूर्ण

	अगर (ret) अणु
मुक्त_priv:
		xhci_urb_मुक्त_priv(urb_priv);
		urb->hcpriv = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&xhci->lock, flags);
	वापस ret;
पूर्ण

/*
 * Remove the URB's TD from the endpoपूर्णांक ring.  This may cause the HC to stop
 * USB transfers, potentially stopping in the middle of a TRB buffer.  The HC
 * should pick up where it left off in the TD, unless a Set Transfer Ring
 * Dequeue Poपूर्णांकer is issued.
 *
 * The TRBs that make up the buffers क्रम the canceled URB will be "removed" from
 * the ring.  Since the ring is a contiguous काष्ठाure, they can't be physically
 * हटाओd.  Instead, there are two options:
 *
 *  1) If the HC is in the middle of processing the URB to be canceled, we
 *     simply move the ring's dequeue poपूर्णांकer past those TRBs using the Set
 *     Transfer Ring Dequeue Poपूर्णांकer command.  This will be the common हाल,
 *     when drivers समयout on the last submitted URB and attempt to cancel.
 *
 *  2) If the HC is in the middle of a dअगरferent TD, we turn the TRBs पूर्णांकo a
 *     series of 1-TRB transfer no-op TDs.  (No-ops shouldn't be chained.)  The
 *     HC will need to invalidate the any TRBs it has cached after the stop
 *     endpoपूर्णांक command, as noted in the xHCI 0.95 errata.
 *
 *  3) The TD may have completed by the समय the Stop Endpoपूर्णांक Command
 *     completes, so software needs to handle that हाल too.
 *
 * This function should protect against the TD enqueueing code ringing the
 * करोorbell जबतक this code is रुकोing क्रम a Stop Endpoपूर्णांक command to complete.
 * It also needs to account क्रम multiple cancellations on happening at the same
 * समय क्रम the same endpoपूर्णांक.
 *
 * Note that this function can be called in any context, or so says
 * usb_hcd_unlink_urb()
 */
अटल पूर्णांक xhci_urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, i;
	u32 temp;
	काष्ठा xhci_hcd *xhci;
	काष्ठा urb_priv	*urb_priv;
	काष्ठा xhci_td *td;
	अचिन्हित पूर्णांक ep_index;
	काष्ठा xhci_ring *ep_ring;
	काष्ठा xhci_virt_ep *ep;
	काष्ठा xhci_command *command;
	काष्ठा xhci_virt_device *vdev;

	xhci = hcd_to_xhci(hcd);
	spin_lock_irqsave(&xhci->lock, flags);

	trace_xhci_urb_dequeue(urb);

	/* Make sure the URB hasn't completed or been unlinked alपढ़ोy */
	ret = usb_hcd_check_unlink_urb(hcd, urb, status);
	अगर (ret)
		जाओ करोne;

	/* give back URB now अगर we can't queue it क्रम cancel */
	vdev = xhci->devs[urb->dev->slot_id];
	urb_priv = urb->hcpriv;
	अगर (!vdev || !urb_priv)
		जाओ err_giveback;

	ep_index = xhci_get_endpoपूर्णांक_index(&urb->ep->desc);
	ep = &vdev->eps[ep_index];
	ep_ring = xhci_urb_to_transfer_ring(xhci, urb);
	अगर (!ep || !ep_ring)
		जाओ err_giveback;

	/* If xHC is dead take it करोwn and वापस ALL URBs in xhci_hc_died() */
	temp = पढ़ोl(&xhci->op_regs->status);
	अगर (temp == ~(u32)0 || xhci->xhc_state & XHCI_STATE_DYING) अणु
		xhci_hc_died(xhci);
		जाओ करोne;
	पूर्ण

	/*
	 * check ring is not re-allocated since URB was enqueued. If it is, then
	 * make sure none of the ring related poपूर्णांकers in this URB निजी data
	 * are touched, such as td_list, otherwise we overग_लिखो मुक्तd data
	 */
	अगर (!td_on_ring(&urb_priv->td[0], ep_ring)) अणु
		xhci_err(xhci, "Canceled URB td not found on endpoint ring");
		क्रम (i = urb_priv->num_tds_करोne; i < urb_priv->num_tds; i++) अणु
			td = &urb_priv->td[i];
			अगर (!list_empty(&td->cancelled_td_list))
				list_del_init(&td->cancelled_td_list);
		पूर्ण
		जाओ err_giveback;
	पूर्ण

	अगर (xhci->xhc_state & XHCI_STATE_HALTED) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
				"HC halted, freeing TD manually.");
		क्रम (i = urb_priv->num_tds_करोne;
		     i < urb_priv->num_tds;
		     i++) अणु
			td = &urb_priv->td[i];
			अगर (!list_empty(&td->td_list))
				list_del_init(&td->td_list);
			अगर (!list_empty(&td->cancelled_td_list))
				list_del_init(&td->cancelled_td_list);
		पूर्ण
		जाओ err_giveback;
	पूर्ण

	i = urb_priv->num_tds_करोne;
	अगर (i < urb_priv->num_tds)
		xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
				"Cancel URB %p, dev %s, ep 0x%x, "
				"starting at offset 0x%llx",
				urb, urb->dev->devpath,
				urb->ep->desc.bEndpoपूर्णांकAddress,
				(अचिन्हित दीर्घ दीर्घ) xhci_trb_virt_to_dma(
					urb_priv->td[i].start_seg,
					urb_priv->td[i].first_trb));

	क्रम (; i < urb_priv->num_tds; i++) अणु
		td = &urb_priv->td[i];
		/* TD can alपढ़ोy be on cancelled list अगर ep halted on it */
		अगर (list_empty(&td->cancelled_td_list)) अणु
			td->cancel_status = TD_सूचीTY;
			list_add_tail(&td->cancelled_td_list,
				      &ep->cancelled_td_list);
		पूर्ण
	पूर्ण

	/* Queue a stop endpoपूर्णांक command, but only अगर this is
	 * the first cancellation to be handled.
	 */
	अगर (!(ep->ep_state & EP_STOP_CMD_PENDING)) अणु
		command = xhci_alloc_command(xhci, false, GFP_ATOMIC);
		अगर (!command) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		ep->ep_state |= EP_STOP_CMD_PENDING;
		ep->stop_cmd_समयr.expires = jअगरfies +
			XHCI_STOP_EP_CMD_TIMEOUT * HZ;
		add_समयr(&ep->stop_cmd_समयr);
		xhci_queue_stop_endpoपूर्णांक(xhci, command, urb->dev->slot_id,
					 ep_index, 0);
		xhci_ring_cmd_db(xhci);
	पूर्ण
करोne:
	spin_unlock_irqrestore(&xhci->lock, flags);
	वापस ret;

err_giveback:
	अगर (urb_priv)
		xhci_urb_मुक्त_priv(urb_priv);
	usb_hcd_unlink_urb_from_ep(hcd, urb);
	spin_unlock_irqrestore(&xhci->lock, flags);
	usb_hcd_giveback_urb(hcd, urb, -ESHUTDOWN);
	वापस ret;
पूर्ण

/* Drop an endpoपूर्णांक from a new bandwidth configuration क्रम this device.
 * Only one call to this function is allowed per endpoपूर्णांक beक्रमe
 * check_bandwidth() or reset_bandwidth() must be called.
 * A call to xhci_drop_endpoपूर्णांक() followed by a call to xhci_add_endpoपूर्णांक() will
 * add the endpoपूर्णांक to the schedule with possibly new parameters denoted by a
 * dअगरferent endpoपूर्णांक descriptor in usb_host_endpoपूर्णांक.
 * A call to xhci_add_endpoपूर्णांक() followed by a call to xhci_drop_endpoपूर्णांक() is
 * not allowed.
 *
 * The USB core will not allow URBs to be queued to an endpoपूर्णांक that is being
 * disabled, so there's no need क्रम mutual exclusion to protect
 * the xhci->devs[slot_id] काष्ठाure.
 */
पूर्णांक xhci_drop_endpoपूर्णांक(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		       काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा xhci_hcd *xhci;
	काष्ठा xhci_container_ctx *in_ctx, *out_ctx;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	अचिन्हित पूर्णांक ep_index;
	काष्ठा xhci_ep_ctx *ep_ctx;
	u32 drop_flag;
	u32 new_add_flags, new_drop_flags;
	पूर्णांक ret;

	ret = xhci_check_args(hcd, udev, ep, 1, true, __func__);
	अगर (ret <= 0)
		वापस ret;
	xhci = hcd_to_xhci(hcd);
	अगर (xhci->xhc_state & XHCI_STATE_DYING)
		वापस -ENODEV;

	xhci_dbg(xhci, "%s called for udev %p\n", __func__, udev);
	drop_flag = xhci_get_endpoपूर्णांक_flag(&ep->desc);
	अगर (drop_flag == SLOT_FLAG || drop_flag == EP0_FLAG) अणु
		xhci_dbg(xhci, "xHCI %s - can't drop slot or ep 0 %#x\n",
				__func__, drop_flag);
		वापस 0;
	पूर्ण

	in_ctx = xhci->devs[udev->slot_id]->in_ctx;
	out_ctx = xhci->devs[udev->slot_id]->out_ctx;
	ctrl_ctx = xhci_get_input_control_ctx(in_ctx);
	अगर (!ctrl_ctx) अणु
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		वापस 0;
	पूर्ण

	ep_index = xhci_get_endpoपूर्णांक_index(&ep->desc);
	ep_ctx = xhci_get_ep_ctx(xhci, out_ctx, ep_index);
	/* If the HC alपढ़ोy knows the endpoपूर्णांक is disabled,
	 * or the HCD has noted it is disabled, ignore this request
	 */
	अगर ((GET_EP_CTX_STATE(ep_ctx) == EP_STATE_DISABLED) ||
	    le32_to_cpu(ctrl_ctx->drop_flags) &
	    xhci_get_endpoपूर्णांक_flag(&ep->desc)) अणु
		/* Do not warn when called after a usb_device_reset */
		अगर (xhci->devs[udev->slot_id]->eps[ep_index].ring != शून्य)
			xhci_warn(xhci, "xHCI %s called with disabled ep %p\n",
				  __func__, ep);
		वापस 0;
	पूर्ण

	ctrl_ctx->drop_flags |= cpu_to_le32(drop_flag);
	new_drop_flags = le32_to_cpu(ctrl_ctx->drop_flags);

	ctrl_ctx->add_flags &= cpu_to_le32(~drop_flag);
	new_add_flags = le32_to_cpu(ctrl_ctx->add_flags);

	xhci_debugfs_हटाओ_endpoपूर्णांक(xhci, xhci->devs[udev->slot_id], ep_index);

	xhci_endpoपूर्णांक_zero(xhci, xhci->devs[udev->slot_id], ep);

	xhci_dbg(xhci, "drop ep 0x%x, slot id %d, new drop flags = %#x, new add flags = %#x\n",
			(अचिन्हित पूर्णांक) ep->desc.bEndpoपूर्णांकAddress,
			udev->slot_id,
			(अचिन्हित पूर्णांक) new_drop_flags,
			(अचिन्हित पूर्णांक) new_add_flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xhci_drop_endpoपूर्णांक);

/* Add an endpoपूर्णांक to a new possible bandwidth configuration क्रम this device.
 * Only one call to this function is allowed per endpoपूर्णांक beक्रमe
 * check_bandwidth() or reset_bandwidth() must be called.
 * A call to xhci_drop_endpoपूर्णांक() followed by a call to xhci_add_endpoपूर्णांक() will
 * add the endpoपूर्णांक to the schedule with possibly new parameters denoted by a
 * dअगरferent endpoपूर्णांक descriptor in usb_host_endpoपूर्णांक.
 * A call to xhci_add_endpoपूर्णांक() followed by a call to xhci_drop_endpoपूर्णांक() is
 * not allowed.
 *
 * The USB core will not allow URBs to be queued to an endpoपूर्णांक until the
 * configuration or alt setting is installed in the device, so there's no need
 * क्रम mutual exclusion to protect the xhci->devs[slot_id] काष्ठाure.
 */
पूर्णांक xhci_add_endpoपूर्णांक(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		      काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा xhci_hcd *xhci;
	काष्ठा xhci_container_ctx *in_ctx;
	अचिन्हित पूर्णांक ep_index;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	काष्ठा xhci_ep_ctx *ep_ctx;
	u32 added_ctxs;
	u32 new_add_flags, new_drop_flags;
	काष्ठा xhci_virt_device *virt_dev;
	पूर्णांक ret = 0;

	ret = xhci_check_args(hcd, udev, ep, 1, true, __func__);
	अगर (ret <= 0) अणु
		/* So we won't queue a reset ep command क्रम a root hub */
		ep->hcpriv = शून्य;
		वापस ret;
	पूर्ण
	xhci = hcd_to_xhci(hcd);
	अगर (xhci->xhc_state & XHCI_STATE_DYING)
		वापस -ENODEV;

	added_ctxs = xhci_get_endpoपूर्णांक_flag(&ep->desc);
	अगर (added_ctxs == SLOT_FLAG || added_ctxs == EP0_FLAG) अणु
		/* FIXME when we have to issue an evaluate endpoपूर्णांक command to
		 * deal with ep0 max packet size changing once we get the
		 * descriptors
		 */
		xhci_dbg(xhci, "xHCI %s - can't add slot or ep 0 %#x\n",
				__func__, added_ctxs);
		वापस 0;
	पूर्ण

	virt_dev = xhci->devs[udev->slot_id];
	in_ctx = virt_dev->in_ctx;
	ctrl_ctx = xhci_get_input_control_ctx(in_ctx);
	अगर (!ctrl_ctx) अणु
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		वापस 0;
	पूर्ण

	ep_index = xhci_get_endpoपूर्णांक_index(&ep->desc);
	/* If this endpoपूर्णांक is alपढ़ोy in use, and the upper layers are trying
	 * to add it again without dropping it, reject the addition.
	 */
	अगर (virt_dev->eps[ep_index].ring &&
			!(le32_to_cpu(ctrl_ctx->drop_flags) & added_ctxs)) अणु
		xhci_warn(xhci, "Trying to add endpoint 0x%x "
				"without dropping it.\n",
				(अचिन्हित पूर्णांक) ep->desc.bEndpoपूर्णांकAddress);
		वापस -EINVAL;
	पूर्ण

	/* If the HCD has alपढ़ोy noted the endpoपूर्णांक is enabled,
	 * ignore this request.
	 */
	अगर (le32_to_cpu(ctrl_ctx->add_flags) & added_ctxs) अणु
		xhci_warn(xhci, "xHCI %s called with enabled ep %p\n",
				__func__, ep);
		वापस 0;
	पूर्ण

	/*
	 * Configuration and alternate setting changes must be करोne in
	 * process context, not पूर्णांकerrupt context (or so करोcumenation
	 * क्रम usb_set_पूर्णांकerface() and usb_set_configuration() claim).
	 */
	अगर (xhci_endpoपूर्णांक_init(xhci, virt_dev, udev, ep, GFP_NOIO) < 0) अणु
		dev_dbg(&udev->dev, "%s - could not initialize ep %#x\n",
				__func__, ep->desc.bEndpoपूर्णांकAddress);
		वापस -ENOMEM;
	पूर्ण

	ctrl_ctx->add_flags |= cpu_to_le32(added_ctxs);
	new_add_flags = le32_to_cpu(ctrl_ctx->add_flags);

	/* If xhci_endpoपूर्णांक_disable() was called क्रम this endpoपूर्णांक, but the
	 * xHC hasn't been notअगरied yet through the check_bandwidth() call,
	 * this re-adds a new state क्रम the endpoपूर्णांक from the new endpoपूर्णांक
	 * descriptors.  We must drop and re-add this endpoपूर्णांक, so we leave the
	 * drop flags alone.
	 */
	new_drop_flags = le32_to_cpu(ctrl_ctx->drop_flags);

	/* Store the usb_device poपूर्णांकer क्रम later use */
	ep->hcpriv = udev;

	ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->in_ctx, ep_index);
	trace_xhci_add_endpoपूर्णांक(ep_ctx);

	xhci_dbg(xhci, "add ep 0x%x, slot id %d, new drop flags = %#x, new add flags = %#x\n",
			(अचिन्हित पूर्णांक) ep->desc.bEndpoपूर्णांकAddress,
			udev->slot_id,
			(अचिन्हित पूर्णांक) new_drop_flags,
			(अचिन्हित पूर्णांक) new_add_flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xhci_add_endpoपूर्णांक);

अटल व्योम xhci_zero_in_ctx(काष्ठा xhci_hcd *xhci, काष्ठा xhci_virt_device *virt_dev)
अणु
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	काष्ठा xhci_ep_ctx *ep_ctx;
	काष्ठा xhci_slot_ctx *slot_ctx;
	पूर्णांक i;

	ctrl_ctx = xhci_get_input_control_ctx(virt_dev->in_ctx);
	अगर (!ctrl_ctx) अणु
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		वापस;
	पूर्ण

	/* When a device's add flag and drop flag are zero, any subsequent
	 * configure endpoपूर्णांक command will leave that endpoपूर्णांक's state
	 * untouched.  Make sure we करोn't leave any old state in the input
	 * endpoपूर्णांक contexts.
	 */
	ctrl_ctx->drop_flags = 0;
	ctrl_ctx->add_flags = 0;
	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->in_ctx);
	slot_ctx->dev_info &= cpu_to_le32(~LAST_CTX_MASK);
	/* Endpoपूर्णांक 0 is always valid */
	slot_ctx->dev_info |= cpu_to_le32(LAST_CTX(1));
	क्रम (i = 1; i < 31; i++) अणु
		ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->in_ctx, i);
		ep_ctx->ep_info = 0;
		ep_ctx->ep_info2 = 0;
		ep_ctx->deq = 0;
		ep_ctx->tx_info = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक xhci_configure_endpoपूर्णांक_result(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev, u32 *cmd_status)
अणु
	पूर्णांक ret;

	चयन (*cmd_status) अणु
	हाल COMP_COMMAND_ABORTED:
	हाल COMP_COMMAND_RING_STOPPED:
		xhci_warn(xhci, "Timeout while waiting for configure endpoint command\n");
		ret = -ETIME;
		अवरोध;
	हाल COMP_RESOURCE_ERROR:
		dev_warn(&udev->dev,
			 "Not enough host controller resources for new device state.\n");
		ret = -ENOMEM;
		/* FIXME: can we allocate more resources क्रम the HC? */
		अवरोध;
	हाल COMP_BANDWIDTH_ERROR:
	हाल COMP_SECONDARY_BANDWIDTH_ERROR:
		dev_warn(&udev->dev,
			 "Not enough bandwidth for new device state.\n");
		ret = -ENOSPC;
		/* FIXME: can we go back to the old state? */
		अवरोध;
	हाल COMP_TRB_ERROR:
		/* the HCD set up something wrong */
		dev_warn(&udev->dev, "ERROR: Endpoint drop flag = 0, "
				"add flag = 1, "
				"and endpoint is not disabled.\n");
		ret = -EINVAL;
		अवरोध;
	हाल COMP_INCOMPATIBLE_DEVICE_ERROR:
		dev_warn(&udev->dev,
			 "ERROR: Incompatible device for endpoint configure command.\n");
		ret = -ENODEV;
		अवरोध;
	हाल COMP_SUCCESS:
		xhci_dbg_trace(xhci, trace_xhci_dbg_context_change,
				"Successful Endpoint Configure command");
		ret = 0;
		अवरोध;
	शेष:
		xhci_err(xhci, "ERROR: unexpected command completion code 0x%x.\n",
				*cmd_status);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक xhci_evaluate_context_result(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev, u32 *cmd_status)
अणु
	पूर्णांक ret;

	चयन (*cmd_status) अणु
	हाल COMP_COMMAND_ABORTED:
	हाल COMP_COMMAND_RING_STOPPED:
		xhci_warn(xhci, "Timeout while waiting for evaluate context command\n");
		ret = -ETIME;
		अवरोध;
	हाल COMP_PARAMETER_ERROR:
		dev_warn(&udev->dev,
			 "WARN: xHCI driver setup invalid evaluate context command.\n");
		ret = -EINVAL;
		अवरोध;
	हाल COMP_SLOT_NOT_ENABLED_ERROR:
		dev_warn(&udev->dev,
			"WARN: slot not enabled for evaluate context command.\n");
		ret = -EINVAL;
		अवरोध;
	हाल COMP_CONTEXT_STATE_ERROR:
		dev_warn(&udev->dev,
			"WARN: invalid context state for evaluate context command.\n");
		ret = -EINVAL;
		अवरोध;
	हाल COMP_INCOMPATIBLE_DEVICE_ERROR:
		dev_warn(&udev->dev,
			"ERROR: Incompatible device for evaluate context command.\n");
		ret = -ENODEV;
		अवरोध;
	हाल COMP_MAX_EXIT_LATENCY_TOO_LARGE_ERROR:
		/* Max Exit Latency too large error */
		dev_warn(&udev->dev, "WARN: Max Exit Latency too large\n");
		ret = -EINVAL;
		अवरोध;
	हाल COMP_SUCCESS:
		xhci_dbg_trace(xhci, trace_xhci_dbg_context_change,
				"Successful evaluate context command");
		ret = 0;
		अवरोध;
	शेष:
		xhci_err(xhci, "ERROR: unexpected command completion code 0x%x.\n",
			*cmd_status);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल u32 xhci_count_num_new_endpoपूर्णांकs(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_input_control_ctx *ctrl_ctx)
अणु
	u32 valid_add_flags;
	u32 valid_drop_flags;

	/* Ignore the slot flag (bit 0), and the शेष control endpoपूर्णांक flag
	 * (bit 1).  The शेष control endpoपूर्णांक is added during the Address
	 * Device command and is never हटाओd until the slot is disabled.
	 */
	valid_add_flags = le32_to_cpu(ctrl_ctx->add_flags) >> 2;
	valid_drop_flags = le32_to_cpu(ctrl_ctx->drop_flags) >> 2;

	/* Use hweight32 to count the number of ones in the add flags, or
	 * number of endpoपूर्णांकs added.  Don't count endpoपूर्णांकs that are changed
	 * (both added and dropped).
	 */
	वापस hweight32(valid_add_flags) -
		hweight32(valid_add_flags & valid_drop_flags);
पूर्ण

अटल अचिन्हित पूर्णांक xhci_count_num_dropped_endpoपूर्णांकs(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_input_control_ctx *ctrl_ctx)
अणु
	u32 valid_add_flags;
	u32 valid_drop_flags;

	valid_add_flags = le32_to_cpu(ctrl_ctx->add_flags) >> 2;
	valid_drop_flags = le32_to_cpu(ctrl_ctx->drop_flags) >> 2;

	वापस hweight32(valid_drop_flags) -
		hweight32(valid_add_flags & valid_drop_flags);
पूर्ण

/*
 * We need to reserve the new number of endpoपूर्णांकs beक्रमe the configure endpoपूर्णांक
 * command completes.  We can't subtract the dropped endpoपूर्णांकs from the number
 * of active endpoपूर्णांकs until the command completes because we can oversubscribe
 * the host in this हाल:
 *
 *  - the first configure endpoपूर्णांक command drops more endpoपूर्णांकs than it adds
 *  - a second configure endpoपूर्णांक command that adds more endpoपूर्णांकs is queued
 *  - the first configure endpoपूर्णांक command fails, so the config is unchanged
 *  - the second command may succeed, even though there isn't enough resources
 *
 * Must be called with xhci->lock held.
 */
अटल पूर्णांक xhci_reserve_host_resources(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_input_control_ctx *ctrl_ctx)
अणु
	u32 added_eps;

	added_eps = xhci_count_num_new_endpoपूर्णांकs(xhci, ctrl_ctx);
	अगर (xhci->num_active_eps + added_eps > xhci->limit_active_eps) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Not enough ep ctxs: "
				"%u active, need to add %u, limit is %u.",
				xhci->num_active_eps, added_eps,
				xhci->limit_active_eps);
		वापस -ENOMEM;
	पूर्ण
	xhci->num_active_eps += added_eps;
	xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
			"Adding %u ep ctxs, %u now active.", added_eps,
			xhci->num_active_eps);
	वापस 0;
पूर्ण

/*
 * The configure endpoपूर्णांक was failed by the xHC क्रम some other reason, so we
 * need to revert the resources that failed configuration would have used.
 *
 * Must be called with xhci->lock held.
 */
अटल व्योम xhci_मुक्त_host_resources(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_input_control_ctx *ctrl_ctx)
अणु
	u32 num_failed_eps;

	num_failed_eps = xhci_count_num_new_endpoपूर्णांकs(xhci, ctrl_ctx);
	xhci->num_active_eps -= num_failed_eps;
	xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
			"Removing %u failed ep ctxs, %u now active.",
			num_failed_eps,
			xhci->num_active_eps);
पूर्ण

/*
 * Now that the command has completed, clean up the active endpoपूर्णांक count by
 * subtracting out the endpoपूर्णांकs that were dropped (but not changed).
 *
 * Must be called with xhci->lock held.
 */
अटल व्योम xhci_finish_resource_reservation(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_input_control_ctx *ctrl_ctx)
अणु
	u32 num_dropped_eps;

	num_dropped_eps = xhci_count_num_dropped_endpoपूर्णांकs(xhci, ctrl_ctx);
	xhci->num_active_eps -= num_dropped_eps;
	अगर (num_dropped_eps)
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Removing %u dropped ep ctxs, %u now active.",
				num_dropped_eps,
				xhci->num_active_eps);
पूर्ण

अटल अचिन्हित पूर्णांक xhci_get_block_size(काष्ठा usb_device *udev)
अणु
	चयन (udev->speed) अणु
	हाल USB_SPEED_LOW:
	हाल USB_SPEED_FULL:
		वापस FS_BLOCK;
	हाल USB_SPEED_HIGH:
		वापस HS_BLOCK;
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		वापस SS_BLOCK;
	हाल USB_SPEED_UNKNOWN:
	हाल USB_SPEED_WIRELESS:
	शेष:
		/* Should never happen */
		वापस 1;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
xhci_get_largest_overhead(काष्ठा xhci_पूर्णांकerval_bw *पूर्णांकerval_bw)
अणु
	अगर (पूर्णांकerval_bw->overhead[LS_OVERHEAD_TYPE])
		वापस LS_OVERHEAD;
	अगर (पूर्णांकerval_bw->overhead[FS_OVERHEAD_TYPE])
		वापस FS_OVERHEAD;
	वापस HS_OVERHEAD;
पूर्ण

/* If we are changing a LS/FS device under a HS hub,
 * make sure (अगर we are activating a new TT) that the HS bus has enough
 * bandwidth क्रम this new TT.
 */
अटल पूर्णांक xhci_check_tt_bw_table(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		पूर्णांक old_active_eps)
अणु
	काष्ठा xhci_पूर्णांकerval_bw_table *bw_table;
	काष्ठा xhci_tt_bw_info *tt_info;

	/* Find the bandwidth table क्रम the root port this TT is attached to. */
	bw_table = &xhci->rh_bw[virt_dev->real_port - 1].bw_table;
	tt_info = virt_dev->tt_info;
	/* If this TT alपढ़ोy had active endpoपूर्णांकs, the bandwidth क्रम this TT
	 * has alपढ़ोy been added.  Removing all periodic endpoपूर्णांकs (and thus
	 * making the TT enactive) will only decrease the bandwidth used.
	 */
	अगर (old_active_eps)
		वापस 0;
	अगर (old_active_eps == 0 && tt_info->active_eps != 0) अणु
		अगर (bw_table->bw_used + TT_HS_OVERHEAD > HS_BW_LIMIT)
			वापस -ENOMEM;
		वापस 0;
	पूर्ण
	/* Not sure why we would have no new active endpoपूर्णांकs...
	 *
	 * Maybe because of an Evaluate Context change क्रम a hub update or a
	 * control endpoपूर्णांक 0 max packet size change?
	 * FIXME: skip the bandwidth calculation in that हाल.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक xhci_check_ss_bw(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev)
अणु
	अचिन्हित पूर्णांक bw_reserved;

	bw_reserved = DIV_ROUND_UP(SS_BW_RESERVED*SS_BW_LIMIT_IN, 100);
	अगर (virt_dev->bw_table->ss_bw_in > (SS_BW_LIMIT_IN - bw_reserved))
		वापस -ENOMEM;

	bw_reserved = DIV_ROUND_UP(SS_BW_RESERVED*SS_BW_LIMIT_OUT, 100);
	अगर (virt_dev->bw_table->ss_bw_out > (SS_BW_LIMIT_OUT - bw_reserved))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/*
 * This algorithm is a very conservative estimate of the worst-हाल scheduling
 * scenario क्रम any one पूर्णांकerval.  The hardware dynamically schedules the
 * packets, so we can't tell which microframe could be the limiting factor in
 * the bandwidth scheduling.  This only takes पूर्णांकo account periodic endpoपूर्णांकs.
 *
 * Obviously, we can't solve an NP complete problem to find the minimum worst
 * हाल scenario.  Instead, we come up with an estimate that is no less than
 * the worst हाल bandwidth used क्रम any one microframe, but may be an
 * over-estimate.
 *
 * We walk the requirements क्रम each endpoपूर्णांक by पूर्णांकerval, starting with the
 * smallest पूर्णांकerval, and place packets in the schedule where there is only one
 * possible way to schedule packets क्रम that पूर्णांकerval.  In order to simplअगरy
 * this algorithm, we record the largest max packet size क्रम each पूर्णांकerval, and
 * assume all packets will be that size.
 *
 * For पूर्णांकerval 0, we obviously must schedule all packets क्रम each पूर्णांकerval.
 * The bandwidth क्रम पूर्णांकerval 0 is just the amount of data to be transmitted
 * (the sum of all max ESIT payload sizes, plus any overhead per packet बार
 * the number of packets).
 *
 * For पूर्णांकerval 1, we have two possible microframes to schedule those packets
 * in.  For this algorithm, अगर we can schedule the same number of packets क्रम
 * each possible scheduling opportunity (each microframe), we will करो so.  The
 * reमुख्यing number of packets will be saved to be transmitted in the gaps in
 * the next पूर्णांकerval's scheduling sequence.
 *
 * As we move those reमुख्यing packets to be scheduled with पूर्णांकerval 2 packets,
 * we have to द्विगुन the number of reमुख्यing packets to transmit.  This is
 * because the पूर्णांकervals are actually घातers of 2, and we would be transmitting
 * the previous पूर्णांकerval's packets twice in this पूर्णांकerval.  We also have to be
 * sure that when we look at the largest max packet size क्रम this पूर्णांकerval, we
 * also look at the largest max packet size क्रम the reमुख्यing packets and take
 * the greater of the two.
 *
 * The algorithm जारीs to evenly distribute packets in each scheduling
 * opportunity, and push the reमुख्यing packets out, until we get to the last
 * पूर्णांकerval.  Then those packets and their associated overhead are just added
 * to the bandwidth used.
 */
अटल पूर्णांक xhci_check_bw_table(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		पूर्णांक old_active_eps)
अणु
	अचिन्हित पूर्णांक bw_reserved;
	अचिन्हित पूर्णांक max_bandwidth;
	अचिन्हित पूर्णांक bw_used;
	अचिन्हित पूर्णांक block_size;
	काष्ठा xhci_पूर्णांकerval_bw_table *bw_table;
	अचिन्हित पूर्णांक packet_size = 0;
	अचिन्हित पूर्णांक overhead = 0;
	अचिन्हित पूर्णांक packets_transmitted = 0;
	अचिन्हित पूर्णांक packets_reमुख्यing = 0;
	अचिन्हित पूर्णांक i;

	अगर (virt_dev->udev->speed >= USB_SPEED_SUPER)
		वापस xhci_check_ss_bw(xhci, virt_dev);

	अगर (virt_dev->udev->speed == USB_SPEED_HIGH) अणु
		max_bandwidth = HS_BW_LIMIT;
		/* Convert percent of bus BW reserved to blocks reserved */
		bw_reserved = DIV_ROUND_UP(HS_BW_RESERVED * max_bandwidth, 100);
	पूर्ण अन्यथा अणु
		max_bandwidth = FS_BW_LIMIT;
		bw_reserved = DIV_ROUND_UP(FS_BW_RESERVED * max_bandwidth, 100);
	पूर्ण

	bw_table = virt_dev->bw_table;
	/* We need to translate the max packet size and max ESIT payloads पूर्णांकo
	 * the units the hardware uses.
	 */
	block_size = xhci_get_block_size(virt_dev->udev);

	/* If we are manipulating a LS/FS device under a HS hub, द्विगुन check
	 * that the HS bus has enough bandwidth अगर we are activing a new TT.
	 */
	अगर (virt_dev->tt_info) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Recalculating BW for rootport %u",
				virt_dev->real_port);
		अगर (xhci_check_tt_bw_table(xhci, virt_dev, old_active_eps)) अणु
			xhci_warn(xhci, "Not enough bandwidth on HS bus for "
					"newly activated TT.\n");
			वापस -ENOMEM;
		पूर्ण
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Recalculating BW for TT slot %u port %u",
				virt_dev->tt_info->slot_id,
				virt_dev->tt_info->ttport);
	पूर्ण अन्यथा अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Recalculating BW for rootport %u",
				virt_dev->real_port);
	पूर्ण

	/* Add in how much bandwidth will be used क्रम पूर्णांकerval zero, or the
	 * rounded max ESIT payload + number of packets * largest overhead.
	 */
	bw_used = DIV_ROUND_UP(bw_table->पूर्णांकerval0_esit_payload, block_size) +
		bw_table->पूर्णांकerval_bw[0].num_packets *
		xhci_get_largest_overhead(&bw_table->पूर्णांकerval_bw[0]);

	क्रम (i = 1; i < XHCI_MAX_INTERVAL; i++) अणु
		अचिन्हित पूर्णांक bw_added;
		अचिन्हित पूर्णांक largest_mps;
		अचिन्हित पूर्णांक पूर्णांकerval_overhead;

		/*
		 * How many packets could we transmit in this पूर्णांकerval?
		 * If packets didn't fit in the previous पूर्णांकerval, we will need
		 * to transmit that many packets twice within this पूर्णांकerval.
		 */
		packets_reमुख्यing = 2 * packets_reमुख्यing +
			bw_table->पूर्णांकerval_bw[i].num_packets;

		/* Find the largest max packet size of this or the previous
		 * पूर्णांकerval.
		 */
		अगर (list_empty(&bw_table->पूर्णांकerval_bw[i].endpoपूर्णांकs))
			largest_mps = 0;
		अन्यथा अणु
			काष्ठा xhci_virt_ep *virt_ep;
			काष्ठा list_head *ep_entry;

			ep_entry = bw_table->पूर्णांकerval_bw[i].endpoपूर्णांकs.next;
			virt_ep = list_entry(ep_entry,
					काष्ठा xhci_virt_ep, bw_endpoपूर्णांक_list);
			/* Convert to blocks, rounding up */
			largest_mps = DIV_ROUND_UP(
					virt_ep->bw_info.max_packet_size,
					block_size);
		पूर्ण
		अगर (largest_mps > packet_size)
			packet_size = largest_mps;

		/* Use the larger overhead of this or the previous पूर्णांकerval. */
		पूर्णांकerval_overhead = xhci_get_largest_overhead(
				&bw_table->पूर्णांकerval_bw[i]);
		अगर (पूर्णांकerval_overhead > overhead)
			overhead = पूर्णांकerval_overhead;

		/* How many packets can we evenly distribute across
		 * (1 << (i + 1)) possible scheduling opportunities?
		 */
		packets_transmitted = packets_reमुख्यing >> (i + 1);

		/* Add in the bandwidth used क्रम those scheduled packets */
		bw_added = packets_transmitted * (overhead + packet_size);

		/* How many packets करो we have reमुख्यing to transmit? */
		packets_reमुख्यing = packets_reमुख्यing % (1 << (i + 1));

		/* What largest max packet size should those packets have? */
		/* If we've transmitted all packets, don't carry over the
		 * largest packet size.
		 */
		अगर (packets_reमुख्यing == 0) अणु
			packet_size = 0;
			overhead = 0;
		पूर्ण अन्यथा अगर (packets_transmitted > 0) अणु
			/* Otherwise अगर we करो have reमुख्यing packets, and we've
			 * scheduled some packets in this पूर्णांकerval, take the
			 * largest max packet size from endpoपूर्णांकs with this
			 * पूर्णांकerval.
			 */
			packet_size = largest_mps;
			overhead = पूर्णांकerval_overhead;
		पूर्ण
		/* Otherwise carry over packet_size and overhead from the last
		 * समय we had a reमुख्यder.
		 */
		bw_used += bw_added;
		अगर (bw_used > max_bandwidth) अणु
			xhci_warn(xhci, "Not enough bandwidth. "
					"Proposed: %u, Max: %u\n",
				bw_used, max_bandwidth);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	/*
	 * Ok, we know we have some packets left over after even-handedly
	 * scheduling पूर्णांकerval 15.  We करोn't know which microframes they will
	 * fit पूर्णांकo, so we over-schedule and say they will be scheduled every
	 * microframe.
	 */
	अगर (packets_reमुख्यing > 0)
		bw_used += overhead + packet_size;

	अगर (!virt_dev->tt_info && virt_dev->udev->speed == USB_SPEED_HIGH) अणु
		अचिन्हित पूर्णांक port_index = virt_dev->real_port - 1;

		/* OK, we're manipulating a HS device attached to a
		 * root port bandwidth करोमुख्य.  Include the number of active TTs
		 * in the bandwidth used.
		 */
		bw_used += TT_HS_OVERHEAD *
			xhci->rh_bw[port_index].num_active_tts;
	पूर्ण

	xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
		"Final bandwidth: %u, Limit: %u, Reserved: %u, "
		"Available: %u " "percent",
		bw_used, max_bandwidth, bw_reserved,
		(max_bandwidth - bw_used - bw_reserved) * 100 /
		max_bandwidth);

	bw_used += bw_reserved;
	अगर (bw_used > max_bandwidth) अणु
		xhci_warn(xhci, "Not enough bandwidth. Proposed: %u, Max: %u\n",
				bw_used, max_bandwidth);
		वापस -ENOMEM;
	पूर्ण

	bw_table->bw_used = bw_used;
	वापस 0;
पूर्ण

अटल bool xhci_is_async_ep(अचिन्हित पूर्णांक ep_type)
अणु
	वापस (ep_type != ISOC_OUT_EP && ep_type != INT_OUT_EP &&
					ep_type != ISOC_IN_EP &&
					ep_type != INT_IN_EP);
पूर्ण

अटल bool xhci_is_sync_in_ep(अचिन्हित पूर्णांक ep_type)
अणु
	वापस (ep_type == ISOC_IN_EP || ep_type == INT_IN_EP);
पूर्ण

अटल अचिन्हित पूर्णांक xhci_get_ss_bw_consumed(काष्ठा xhci_bw_info *ep_bw)
अणु
	अचिन्हित पूर्णांक mps = DIV_ROUND_UP(ep_bw->max_packet_size, SS_BLOCK);

	अगर (ep_bw->ep_पूर्णांकerval == 0)
		वापस SS_OVERHEAD_BURST +
			(ep_bw->mult * ep_bw->num_packets *
					(SS_OVERHEAD + mps));
	वापस DIV_ROUND_UP(ep_bw->mult * ep_bw->num_packets *
				(SS_OVERHEAD + mps + SS_OVERHEAD_BURST),
				1 << ep_bw->ep_पूर्णांकerval);

पूर्ण

अटल व्योम xhci_drop_ep_from_पूर्णांकerval_table(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_bw_info *ep_bw,
		काष्ठा xhci_पूर्णांकerval_bw_table *bw_table,
		काष्ठा usb_device *udev,
		काष्ठा xhci_virt_ep *virt_ep,
		काष्ठा xhci_tt_bw_info *tt_info)
अणु
	काष्ठा xhci_पूर्णांकerval_bw	*पूर्णांकerval_bw;
	पूर्णांक normalized_पूर्णांकerval;

	अगर (xhci_is_async_ep(ep_bw->type))
		वापस;

	अगर (udev->speed >= USB_SPEED_SUPER) अणु
		अगर (xhci_is_sync_in_ep(ep_bw->type))
			xhci->devs[udev->slot_id]->bw_table->ss_bw_in -=
				xhci_get_ss_bw_consumed(ep_bw);
		अन्यथा
			xhci->devs[udev->slot_id]->bw_table->ss_bw_out -=
				xhci_get_ss_bw_consumed(ep_bw);
		वापस;
	पूर्ण

	/* SuperSpeed endpoपूर्णांकs never get added to पूर्णांकervals in the table, so
	 * this check is only valid क्रम HS/FS/LS devices.
	 */
	अगर (list_empty(&virt_ep->bw_endpoपूर्णांक_list))
		वापस;
	/* For LS/FS devices, we need to translate the पूर्णांकerval expressed in
	 * microframes to frames.
	 */
	अगर (udev->speed == USB_SPEED_HIGH)
		normalized_पूर्णांकerval = ep_bw->ep_पूर्णांकerval;
	अन्यथा
		normalized_पूर्णांकerval = ep_bw->ep_पूर्णांकerval - 3;

	अगर (normalized_पूर्णांकerval == 0)
		bw_table->पूर्णांकerval0_esit_payload -= ep_bw->max_esit_payload;
	पूर्णांकerval_bw = &bw_table->पूर्णांकerval_bw[normalized_पूर्णांकerval];
	पूर्णांकerval_bw->num_packets -= ep_bw->num_packets;
	चयन (udev->speed) अणु
	हाल USB_SPEED_LOW:
		पूर्णांकerval_bw->overhead[LS_OVERHEAD_TYPE] -= 1;
		अवरोध;
	हाल USB_SPEED_FULL:
		पूर्णांकerval_bw->overhead[FS_OVERHEAD_TYPE] -= 1;
		अवरोध;
	हाल USB_SPEED_HIGH:
		पूर्णांकerval_bw->overhead[HS_OVERHEAD_TYPE] -= 1;
		अवरोध;
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
	हाल USB_SPEED_UNKNOWN:
	हाल USB_SPEED_WIRELESS:
		/* Should never happen because only LS/FS/HS endpoपूर्णांकs will get
		 * added to the endpoपूर्णांक list.
		 */
		वापस;
	पूर्ण
	अगर (tt_info)
		tt_info->active_eps -= 1;
	list_del_init(&virt_ep->bw_endpoपूर्णांक_list);
पूर्ण

अटल व्योम xhci_add_ep_to_पूर्णांकerval_table(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_bw_info *ep_bw,
		काष्ठा xhci_पूर्णांकerval_bw_table *bw_table,
		काष्ठा usb_device *udev,
		काष्ठा xhci_virt_ep *virt_ep,
		काष्ठा xhci_tt_bw_info *tt_info)
अणु
	काष्ठा xhci_पूर्णांकerval_bw	*पूर्णांकerval_bw;
	काष्ठा xhci_virt_ep *smaller_ep;
	पूर्णांक normalized_पूर्णांकerval;

	अगर (xhci_is_async_ep(ep_bw->type))
		वापस;

	अगर (udev->speed == USB_SPEED_SUPER) अणु
		अगर (xhci_is_sync_in_ep(ep_bw->type))
			xhci->devs[udev->slot_id]->bw_table->ss_bw_in +=
				xhci_get_ss_bw_consumed(ep_bw);
		अन्यथा
			xhci->devs[udev->slot_id]->bw_table->ss_bw_out +=
				xhci_get_ss_bw_consumed(ep_bw);
		वापस;
	पूर्ण

	/* For LS/FS devices, we need to translate the पूर्णांकerval expressed in
	 * microframes to frames.
	 */
	अगर (udev->speed == USB_SPEED_HIGH)
		normalized_पूर्णांकerval = ep_bw->ep_पूर्णांकerval;
	अन्यथा
		normalized_पूर्णांकerval = ep_bw->ep_पूर्णांकerval - 3;

	अगर (normalized_पूर्णांकerval == 0)
		bw_table->पूर्णांकerval0_esit_payload += ep_bw->max_esit_payload;
	पूर्णांकerval_bw = &bw_table->पूर्णांकerval_bw[normalized_पूर्णांकerval];
	पूर्णांकerval_bw->num_packets += ep_bw->num_packets;
	चयन (udev->speed) अणु
	हाल USB_SPEED_LOW:
		पूर्णांकerval_bw->overhead[LS_OVERHEAD_TYPE] += 1;
		अवरोध;
	हाल USB_SPEED_FULL:
		पूर्णांकerval_bw->overhead[FS_OVERHEAD_TYPE] += 1;
		अवरोध;
	हाल USB_SPEED_HIGH:
		पूर्णांकerval_bw->overhead[HS_OVERHEAD_TYPE] += 1;
		अवरोध;
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
	हाल USB_SPEED_UNKNOWN:
	हाल USB_SPEED_WIRELESS:
		/* Should never happen because only LS/FS/HS endpoपूर्णांकs will get
		 * added to the endpoपूर्णांक list.
		 */
		वापस;
	पूर्ण

	अगर (tt_info)
		tt_info->active_eps += 1;
	/* Insert the endpoपूर्णांक पूर्णांकo the list, largest max packet size first. */
	list_क्रम_each_entry(smaller_ep, &पूर्णांकerval_bw->endpoपूर्णांकs,
			bw_endpoपूर्णांक_list) अणु
		अगर (ep_bw->max_packet_size >=
				smaller_ep->bw_info.max_packet_size) अणु
			/* Add the new ep beक्रमe the smaller endpoपूर्णांक */
			list_add_tail(&virt_ep->bw_endpoपूर्णांक_list,
					&smaller_ep->bw_endpoपूर्णांक_list);
			वापस;
		पूर्ण
	पूर्ण
	/* Add the new endpoपूर्णांक at the end of the list. */
	list_add_tail(&virt_ep->bw_endpoपूर्णांक_list,
			&पूर्णांकerval_bw->endpoपूर्णांकs);
पूर्ण

व्योम xhci_update_tt_active_eps(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		पूर्णांक old_active_eps)
अणु
	काष्ठा xhci_root_port_bw_info *rh_bw_info;
	अगर (!virt_dev->tt_info)
		वापस;

	rh_bw_info = &xhci->rh_bw[virt_dev->real_port - 1];
	अगर (old_active_eps == 0 &&
				virt_dev->tt_info->active_eps != 0) अणु
		rh_bw_info->num_active_tts += 1;
		rh_bw_info->bw_table.bw_used += TT_HS_OVERHEAD;
	पूर्ण अन्यथा अगर (old_active_eps != 0 &&
				virt_dev->tt_info->active_eps == 0) अणु
		rh_bw_info->num_active_tts -= 1;
		rh_bw_info->bw_table.bw_used -= TT_HS_OVERHEAD;
	पूर्ण
पूर्ण

अटल पूर्णांक xhci_reserve_bandwidth(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		काष्ठा xhci_container_ctx *in_ctx)
अणु
	काष्ठा xhci_bw_info ep_bw_info[31];
	पूर्णांक i;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	पूर्णांक old_active_eps = 0;

	अगर (virt_dev->tt_info)
		old_active_eps = virt_dev->tt_info->active_eps;

	ctrl_ctx = xhci_get_input_control_ctx(in_ctx);
	अगर (!ctrl_ctx) अणु
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < 31; i++) अणु
		अगर (!EP_IS_ADDED(ctrl_ctx, i) && !EP_IS_DROPPED(ctrl_ctx, i))
			जारी;

		/* Make a copy of the BW info in हाल we need to revert this */
		स_नकल(&ep_bw_info[i], &virt_dev->eps[i].bw_info,
				माप(ep_bw_info[i]));
		/* Drop the endpoपूर्णांक from the पूर्णांकerval table अगर the endpoपूर्णांक is
		 * being dropped or changed.
		 */
		अगर (EP_IS_DROPPED(ctrl_ctx, i))
			xhci_drop_ep_from_पूर्णांकerval_table(xhci,
					&virt_dev->eps[i].bw_info,
					virt_dev->bw_table,
					virt_dev->udev,
					&virt_dev->eps[i],
					virt_dev->tt_info);
	पूर्ण
	/* Overग_लिखो the inक्रमmation stored in the endpoपूर्णांकs' bw_info */
	xhci_update_bw_info(xhci, virt_dev->in_ctx, ctrl_ctx, virt_dev);
	क्रम (i = 0; i < 31; i++) अणु
		/* Add any changed or added endpoपूर्णांकs to the पूर्णांकerval table */
		अगर (EP_IS_ADDED(ctrl_ctx, i))
			xhci_add_ep_to_पूर्णांकerval_table(xhci,
					&virt_dev->eps[i].bw_info,
					virt_dev->bw_table,
					virt_dev->udev,
					&virt_dev->eps[i],
					virt_dev->tt_info);
	पूर्ण

	अगर (!xhci_check_bw_table(xhci, virt_dev, old_active_eps)) अणु
		/* Ok, this fits in the bandwidth we have.
		 * Update the number of active TTs.
		 */
		xhci_update_tt_active_eps(xhci, virt_dev, old_active_eps);
		वापस 0;
	पूर्ण

	/* We करोn't have enough bandwidth क्रम this, revert the stored info. */
	क्रम (i = 0; i < 31; i++) अणु
		अगर (!EP_IS_ADDED(ctrl_ctx, i) && !EP_IS_DROPPED(ctrl_ctx, i))
			जारी;

		/* Drop the new copies of any added or changed endpoपूर्णांकs from
		 * the पूर्णांकerval table.
		 */
		अगर (EP_IS_ADDED(ctrl_ctx, i)) अणु
			xhci_drop_ep_from_पूर्णांकerval_table(xhci,
					&virt_dev->eps[i].bw_info,
					virt_dev->bw_table,
					virt_dev->udev,
					&virt_dev->eps[i],
					virt_dev->tt_info);
		पूर्ण
		/* Revert the endpoपूर्णांक back to its old inक्रमmation */
		स_नकल(&virt_dev->eps[i].bw_info, &ep_bw_info[i],
				माप(ep_bw_info[i]));
		/* Add any changed or dropped endpoपूर्णांकs back पूर्णांकo the table */
		अगर (EP_IS_DROPPED(ctrl_ctx, i))
			xhci_add_ep_to_पूर्णांकerval_table(xhci,
					&virt_dev->eps[i].bw_info,
					virt_dev->bw_table,
					virt_dev->udev,
					&virt_dev->eps[i],
					virt_dev->tt_info);
	पूर्ण
	वापस -ENOMEM;
पूर्ण


/* Issue a configure endpoपूर्णांक command or evaluate context command
 * and रुको क्रम it to finish.
 */
अटल पूर्णांक xhci_configure_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev,
		काष्ठा xhci_command *command,
		bool ctx_change, bool must_succeed)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा xhci_slot_ctx *slot_ctx;

	अगर (!command)
		वापस -EINVAL;

	spin_lock_irqsave(&xhci->lock, flags);

	अगर (xhci->xhc_state & XHCI_STATE_DYING) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		वापस -ESHUTDOWN;
	पूर्ण

	virt_dev = xhci->devs[udev->slot_id];

	ctrl_ctx = xhci_get_input_control_ctx(command->in_ctx);
	अगर (!ctrl_ctx) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		वापस -ENOMEM;
	पूर्ण

	अगर ((xhci->quirks & XHCI_EP_LIMIT_QUIRK) &&
			xhci_reserve_host_resources(xhci, ctrl_ctx)) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_warn(xhci, "Not enough host resources, "
				"active endpoint contexts = %u\n",
				xhci->num_active_eps);
		वापस -ENOMEM;
	पूर्ण
	अगर ((xhci->quirks & XHCI_SW_BW_CHECKING) &&
	    xhci_reserve_bandwidth(xhci, virt_dev, command->in_ctx)) अणु
		अगर ((xhci->quirks & XHCI_EP_LIMIT_QUIRK))
			xhci_मुक्त_host_resources(xhci, ctrl_ctx);
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_warn(xhci, "Not enough bandwidth\n");
		वापस -ENOMEM;
	पूर्ण

	slot_ctx = xhci_get_slot_ctx(xhci, command->in_ctx);

	trace_xhci_configure_endpoपूर्णांक_ctrl_ctx(ctrl_ctx);
	trace_xhci_configure_endpoपूर्णांक(slot_ctx);

	अगर (!ctx_change)
		ret = xhci_queue_configure_endpoपूर्णांक(xhci, command,
				command->in_ctx->dma,
				udev->slot_id, must_succeed);
	अन्यथा
		ret = xhci_queue_evaluate_context(xhci, command,
				command->in_ctx->dma,
				udev->slot_id, must_succeed);
	अगर (ret < 0) अणु
		अगर ((xhci->quirks & XHCI_EP_LIMIT_QUIRK))
			xhci_मुक्त_host_resources(xhci, ctrl_ctx);
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_dbg_trace(xhci,  trace_xhci_dbg_context_change,
				"FIXME allocate a new ring segment");
		वापस -ENOMEM;
	पूर्ण
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* Wait क्रम the configure endpoपूर्णांक command to complete */
	रुको_क्रम_completion(command->completion);

	अगर (!ctx_change)
		ret = xhci_configure_endpoपूर्णांक_result(xhci, udev,
						     &command->status);
	अन्यथा
		ret = xhci_evaluate_context_result(xhci, udev,
						   &command->status);

	अगर ((xhci->quirks & XHCI_EP_LIMIT_QUIRK)) अणु
		spin_lock_irqsave(&xhci->lock, flags);
		/* If the command failed, हटाओ the reserved resources.
		 * Otherwise, clean up the estimate to include dropped eps.
		 */
		अगर (ret)
			xhci_मुक्त_host_resources(xhci, ctrl_ctx);
		अन्यथा
			xhci_finish_resource_reservation(xhci, ctrl_ctx);
		spin_unlock_irqrestore(&xhci->lock, flags);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम xhci_check_bw_drop_ep_streams(काष्ठा xhci_hcd *xhci,
	काष्ठा xhci_virt_device *vdev, पूर्णांक i)
अणु
	काष्ठा xhci_virt_ep *ep = &vdev->eps[i];

	अगर (ep->ep_state & EP_HAS_STREAMS) अणु
		xhci_warn(xhci, "WARN: endpoint 0x%02x has streams on set_interface, freeing streams.\n",
				xhci_get_endpoपूर्णांक_address(i));
		xhci_मुक्त_stream_info(xhci, ep->stream_info);
		ep->stream_info = शून्य;
		ep->ep_state &= ~EP_HAS_STREAMS;
	पूर्ण
पूर्ण

/* Called after one or more calls to xhci_add_endpoपूर्णांक() or
 * xhci_drop_endpoपूर्णांक().  If this call fails, the USB core is expected
 * to call xhci_reset_bandwidth().
 *
 * Since we are in the middle of changing either configuration or
 * installing a new alt setting, the USB core won't allow URBs to be
 * enqueued क्रम any endpoपूर्णांक on the old config or पूर्णांकerface.  Nothing
 * अन्यथा should be touching the xhci->devs[slot_id] काष्ठाure, so we
 * करोn't need to take the xhci->lock क्रम manipulating that.
 */
पूर्णांक xhci_check_bandwidth(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा xhci_hcd *xhci;
	काष्ठा xhci_virt_device	*virt_dev;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	काष्ठा xhci_slot_ctx *slot_ctx;
	काष्ठा xhci_command *command;

	ret = xhci_check_args(hcd, udev, शून्य, 0, true, __func__);
	अगर (ret <= 0)
		वापस ret;
	xhci = hcd_to_xhci(hcd);
	अगर ((xhci->xhc_state & XHCI_STATE_DYING) ||
		(xhci->xhc_state & XHCI_STATE_REMOVING))
		वापस -ENODEV;

	xhci_dbg(xhci, "%s called for udev %p\n", __func__, udev);
	virt_dev = xhci->devs[udev->slot_id];

	command = xhci_alloc_command(xhci, true, GFP_KERNEL);
	अगर (!command)
		वापस -ENOMEM;

	command->in_ctx = virt_dev->in_ctx;

	/* See section 4.6.6 - A0 = 1; A1 = D0 = D1 = 0 */
	ctrl_ctx = xhci_get_input_control_ctx(command->in_ctx);
	अगर (!ctrl_ctx) अणु
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		ret = -ENOMEM;
		जाओ command_cleanup;
	पूर्ण
	ctrl_ctx->add_flags |= cpu_to_le32(SLOT_FLAG);
	ctrl_ctx->add_flags &= cpu_to_le32(~EP0_FLAG);
	ctrl_ctx->drop_flags &= cpu_to_le32(~(SLOT_FLAG | EP0_FLAG));

	/* Don't issue the command if there's no endpoपूर्णांकs to update. */
	अगर (ctrl_ctx->add_flags == cpu_to_le32(SLOT_FLAG) &&
	    ctrl_ctx->drop_flags == 0) अणु
		ret = 0;
		जाओ command_cleanup;
	पूर्ण
	/* Fix up Context Entries field. Minimum value is EP0 == BIT(1). */
	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->in_ctx);
	क्रम (i = 31; i >= 1; i--) अणु
		__le32 le32 = cpu_to_le32(BIT(i));

		अगर ((virt_dev->eps[i-1].ring && !(ctrl_ctx->drop_flags & le32))
		    || (ctrl_ctx->add_flags & le32) || i == 1) अणु
			slot_ctx->dev_info &= cpu_to_le32(~LAST_CTX_MASK);
			slot_ctx->dev_info |= cpu_to_le32(LAST_CTX(i));
			अवरोध;
		पूर्ण
	पूर्ण

	ret = xhci_configure_endpoपूर्णांक(xhci, udev, command,
			false, false);
	अगर (ret)
		/* Callee should call reset_bandwidth() */
		जाओ command_cleanup;

	/* Free any rings that were dropped, but not changed. */
	क्रम (i = 1; i < 31; i++) अणु
		अगर ((le32_to_cpu(ctrl_ctx->drop_flags) & (1 << (i + 1))) &&
		    !(le32_to_cpu(ctrl_ctx->add_flags) & (1 << (i + 1)))) अणु
			xhci_मुक्त_endpoपूर्णांक_ring(xhci, virt_dev, i);
			xhci_check_bw_drop_ep_streams(xhci, virt_dev, i);
		पूर्ण
	पूर्ण
	xhci_zero_in_ctx(xhci, virt_dev);
	/*
	 * Install any rings क्रम completely new endpoपूर्णांकs or changed endpoपूर्णांकs,
	 * and मुक्त any old rings from changed endpoपूर्णांकs.
	 */
	क्रम (i = 1; i < 31; i++) अणु
		अगर (!virt_dev->eps[i].new_ring)
			जारी;
		/* Only मुक्त the old ring अगर it exists.
		 * It may not अगर this is the first add of an endpoपूर्णांक.
		 */
		अगर (virt_dev->eps[i].ring) अणु
			xhci_मुक्त_endpoपूर्णांक_ring(xhci, virt_dev, i);
		पूर्ण
		xhci_check_bw_drop_ep_streams(xhci, virt_dev, i);
		virt_dev->eps[i].ring = virt_dev->eps[i].new_ring;
		virt_dev->eps[i].new_ring = शून्य;
		xhci_debugfs_create_endpoपूर्णांक(xhci, virt_dev, i);
	पूर्ण
command_cleanup:
	kमुक्त(command->completion);
	kमुक्त(command);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xhci_check_bandwidth);

व्योम xhci_reset_bandwidth(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	काष्ठा xhci_hcd *xhci;
	काष्ठा xhci_virt_device	*virt_dev;
	पूर्णांक i, ret;

	ret = xhci_check_args(hcd, udev, शून्य, 0, true, __func__);
	अगर (ret <= 0)
		वापस;
	xhci = hcd_to_xhci(hcd);

	xhci_dbg(xhci, "%s called for udev %p\n", __func__, udev);
	virt_dev = xhci->devs[udev->slot_id];
	/* Free any rings allocated क्रम added endpoपूर्णांकs */
	क्रम (i = 0; i < 31; i++) अणु
		अगर (virt_dev->eps[i].new_ring) अणु
			xhci_debugfs_हटाओ_endpoपूर्णांक(xhci, virt_dev, i);
			xhci_ring_मुक्त(xhci, virt_dev->eps[i].new_ring);
			virt_dev->eps[i].new_ring = शून्य;
		पूर्ण
	पूर्ण
	xhci_zero_in_ctx(xhci, virt_dev);
पूर्ण
EXPORT_SYMBOL_GPL(xhci_reset_bandwidth);

अटल व्योम xhci_setup_input_ctx_क्रम_config_ep(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *in_ctx,
		काष्ठा xhci_container_ctx *out_ctx,
		काष्ठा xhci_input_control_ctx *ctrl_ctx,
		u32 add_flags, u32 drop_flags)
अणु
	ctrl_ctx->add_flags = cpu_to_le32(add_flags);
	ctrl_ctx->drop_flags = cpu_to_le32(drop_flags);
	xhci_slot_copy(xhci, in_ctx, out_ctx);
	ctrl_ctx->add_flags |= cpu_to_le32(SLOT_FLAG);
पूर्ण

अटल व्योम xhci_endpoपूर्णांक_disable(काष्ठा usb_hcd *hcd,
				  काष्ठा usb_host_endpoपूर्णांक *host_ep)
अणु
	काष्ठा xhci_hcd		*xhci;
	काष्ठा xhci_virt_device	*vdev;
	काष्ठा xhci_virt_ep	*ep;
	काष्ठा usb_device	*udev;
	अचिन्हित दीर्घ		flags;
	अचिन्हित पूर्णांक		ep_index;

	xhci = hcd_to_xhci(hcd);
rescan:
	spin_lock_irqsave(&xhci->lock, flags);

	udev = (काष्ठा usb_device *)host_ep->hcpriv;
	अगर (!udev || !udev->slot_id)
		जाओ करोne;

	vdev = xhci->devs[udev->slot_id];
	अगर (!vdev)
		जाओ करोne;

	ep_index = xhci_get_endpoपूर्णांक_index(&host_ep->desc);
	ep = &vdev->eps[ep_index];
	अगर (!ep)
		जाओ करोne;

	/* रुको क्रम hub_tt_work to finish clearing hub TT */
	अगर (ep->ep_state & EP_CLEARING_TT) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		schedule_समयout_unपूर्णांकerruptible(1);
		जाओ rescan;
	पूर्ण

	अगर (ep->ep_state)
		xhci_dbg(xhci, "endpoint disable with ep_state 0x%x\n",
			 ep->ep_state);
करोne:
	host_ep->hcpriv = शून्य;
	spin_unlock_irqrestore(&xhci->lock, flags);
पूर्ण

/*
 * Called after usb core issues a clear halt control message.
 * The host side of the halt should alपढ़ोy be cleared by a reset endpoपूर्णांक
 * command issued when the STALL event was received.
 *
 * The reset endpoपूर्णांक command may only be issued to endpoपूर्णांकs in the halted
 * state. For software that wishes to reset the data toggle or sequence number
 * of an endpoपूर्णांक that isn't in the halted state this function will issue a
 * configure endpoपूर्णांक command with the Drop and Add bits set क्रम the target
 * endpoपूर्णांक. Refer to the additional note in xhci spcअगरication section 4.6.8.
 */

अटल व्योम xhci_endpoपूर्णांक_reset(काष्ठा usb_hcd *hcd,
		काष्ठा usb_host_endpoपूर्णांक *host_ep)
अणु
	काष्ठा xhci_hcd *xhci;
	काष्ठा usb_device *udev;
	काष्ठा xhci_virt_device *vdev;
	काष्ठा xhci_virt_ep *ep;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	काष्ठा xhci_command *stop_cmd, *cfg_cmd;
	अचिन्हित पूर्णांक ep_index;
	अचिन्हित दीर्घ flags;
	u32 ep_flag;
	पूर्णांक err;

	xhci = hcd_to_xhci(hcd);
	अगर (!host_ep->hcpriv)
		वापस;
	udev = (काष्ठा usb_device *) host_ep->hcpriv;
	vdev = xhci->devs[udev->slot_id];

	/*
	 * vdev may be lost due to xHC restore error and re-initialization
	 * during S3/S4 resume. A new vdev will be allocated later by
	 * xhci_discover_or_reset_device()
	 */
	अगर (!udev->slot_id || !vdev)
		वापस;
	ep_index = xhci_get_endpoपूर्णांक_index(&host_ep->desc);
	ep = &vdev->eps[ep_index];
	अगर (!ep)
		वापस;

	/* Bail out अगर toggle is alपढ़ोy being cleared by a endpoपूर्णांक reset */
	अगर (ep->ep_state & EP_HARD_CLEAR_TOGGLE) अणु
		ep->ep_state &= ~EP_HARD_CLEAR_TOGGLE;
		वापस;
	पूर्ण
	/* Only पूर्णांकerrupt and bulk ep's use data toggle, USB2 spec 5.5.4-> */
	अगर (usb_endpoपूर्णांक_xfer_control(&host_ep->desc) ||
	    usb_endpoपूर्णांक_xfer_isoc(&host_ep->desc))
		वापस;

	ep_flag = xhci_get_endpoपूर्णांक_flag(&host_ep->desc);

	अगर (ep_flag == SLOT_FLAG || ep_flag == EP0_FLAG)
		वापस;

	stop_cmd = xhci_alloc_command(xhci, true, GFP_NOWAIT);
	अगर (!stop_cmd)
		वापस;

	cfg_cmd = xhci_alloc_command_with_ctx(xhci, true, GFP_NOWAIT);
	अगर (!cfg_cmd)
		जाओ cleanup;

	spin_lock_irqsave(&xhci->lock, flags);

	/* block queuing new trbs and ringing ep करोorbell */
	ep->ep_state |= EP_SOFT_CLEAR_TOGGLE;

	/*
	 * Make sure endpoपूर्णांक ring is empty beक्रमe resetting the toggle/seq.
	 * Driver is required to synchronously cancel all transfer request.
	 * Stop the endpoपूर्णांक to क्रमce xHC to update the output context
	 */

	अगर (!list_empty(&ep->ring->td_list)) अणु
		dev_err(&udev->dev, "EP not empty, refuse reset\n");
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_मुक्त_command(xhci, cfg_cmd);
		जाओ cleanup;
	पूर्ण

	err = xhci_queue_stop_endpoपूर्णांक(xhci, stop_cmd, udev->slot_id,
					ep_index, 0);
	अगर (err < 0) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_मुक्त_command(xhci, cfg_cmd);
		xhci_dbg(xhci, "%s: Failed to queue stop ep command, %d ",
				__func__, err);
		जाओ cleanup;
	पूर्ण

	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	रुको_क्रम_completion(stop_cmd->completion);

	spin_lock_irqsave(&xhci->lock, flags);

	/* config ep command clears toggle अगर add and drop ep flags are set */
	ctrl_ctx = xhci_get_input_control_ctx(cfg_cmd->in_ctx);
	अगर (!ctrl_ctx) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_मुक्त_command(xhci, cfg_cmd);
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		जाओ cleanup;
	पूर्ण

	xhci_setup_input_ctx_क्रम_config_ep(xhci, cfg_cmd->in_ctx, vdev->out_ctx,
					   ctrl_ctx, ep_flag, ep_flag);
	xhci_endpoपूर्णांक_copy(xhci, cfg_cmd->in_ctx, vdev->out_ctx, ep_index);

	err = xhci_queue_configure_endpoपूर्णांक(xhci, cfg_cmd, cfg_cmd->in_ctx->dma,
				      udev->slot_id, false);
	अगर (err < 0) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_मुक्त_command(xhci, cfg_cmd);
		xhci_dbg(xhci, "%s: Failed to queue config ep command, %d ",
				__func__, err);
		जाओ cleanup;
	पूर्ण

	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	रुको_क्रम_completion(cfg_cmd->completion);

	xhci_मुक्त_command(xhci, cfg_cmd);
cleanup:
	xhci_मुक्त_command(xhci, stop_cmd);
	अगर (ep->ep_state & EP_SOFT_CLEAR_TOGGLE)
		ep->ep_state &= ~EP_SOFT_CLEAR_TOGGLE;
पूर्ण

अटल पूर्णांक xhci_check_streams_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev, काष्ठा usb_host_endpoपूर्णांक *ep,
		अचिन्हित पूर्णांक slot_id)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक ep_index;
	अचिन्हित पूर्णांक ep_state;

	अगर (!ep)
		वापस -EINVAL;
	ret = xhci_check_args(xhci_to_hcd(xhci), udev, ep, 1, true, __func__);
	अगर (ret <= 0)
		वापस -EINVAL;
	अगर (usb_ss_max_streams(&ep->ss_ep_comp) == 0) अणु
		xhci_warn(xhci, "WARN: SuperSpeed Endpoint Companion"
				" descriptor for ep 0x%x does not support streams\n",
				ep->desc.bEndpoपूर्णांकAddress);
		वापस -EINVAL;
	पूर्ण

	ep_index = xhci_get_endpoपूर्णांक_index(&ep->desc);
	ep_state = xhci->devs[slot_id]->eps[ep_index].ep_state;
	अगर (ep_state & EP_HAS_STREAMS ||
			ep_state & EP_GETTING_STREAMS) अणु
		xhci_warn(xhci, "WARN: SuperSpeed bulk endpoint 0x%x "
				"already has streams set up.\n",
				ep->desc.bEndpoपूर्णांकAddress);
		xhci_warn(xhci, "Send email to xHCI maintainer and ask for "
				"dynamic stream context array reallocation.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!list_empty(&xhci->devs[slot_id]->eps[ep_index].ring->td_list)) अणु
		xhci_warn(xhci, "Cannot setup streams for SuperSpeed bulk "
				"endpoint 0x%x; URBs are pending.\n",
				ep->desc.bEndpoपूर्णांकAddress);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम xhci_calculate_streams_entries(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक *num_streams, अचिन्हित पूर्णांक *num_stream_ctxs)
अणु
	अचिन्हित पूर्णांक max_streams;

	/* The stream context array size must be a घातer of two */
	*num_stream_ctxs = roundup_घात_of_two(*num_streams);
	/*
	 * Find out how many primary stream array entries the host controller
	 * supports.  Later we may use secondary stream arrays (similar to 2nd
	 * level page entries), but that's an optional feature क्रम xHCI host
	 * controllers. xHCs must support at least 4 stream IDs.
	 */
	max_streams = HCC_MAX_PSA(xhci->hcc_params);
	अगर (*num_stream_ctxs > max_streams) अणु
		xhci_dbg(xhci, "xHCI HW only supports %u stream ctx entries.\n",
				max_streams);
		*num_stream_ctxs = max_streams;
		*num_streams = max_streams;
	पूर्ण
पूर्ण

/* Returns an error code अगर one of the endpoपूर्णांक alपढ़ोy has streams.
 * This करोes not change any data काष्ठाures, it only checks and gathers
 * inक्रमmation.
 */
अटल पूर्णांक xhci_calculate_streams_and_biपंचांगask(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
		अचिन्हित पूर्णांक *num_streams, u32 *changed_ep_biपंचांगask)
अणु
	अचिन्हित पूर्णांक max_streams;
	अचिन्हित पूर्णांक endpoपूर्णांक_flag;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_eps; i++) अणु
		ret = xhci_check_streams_endpoपूर्णांक(xhci, udev,
				eps[i], udev->slot_id);
		अगर (ret < 0)
			वापस ret;

		max_streams = usb_ss_max_streams(&eps[i]->ss_ep_comp);
		अगर (max_streams < (*num_streams - 1)) अणु
			xhci_dbg(xhci, "Ep 0x%x only supports %u stream IDs.\n",
					eps[i]->desc.bEndpoपूर्णांकAddress,
					max_streams);
			*num_streams = max_streams+1;
		पूर्ण

		endpoपूर्णांक_flag = xhci_get_endpoपूर्णांक_flag(&eps[i]->desc);
		अगर (*changed_ep_biपंचांगask & endpoपूर्णांक_flag)
			वापस -EINVAL;
		*changed_ep_biपंचांगask |= endpoपूर्णांक_flag;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 xhci_calculate_no_streams_biपंचांगask(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps)
अणु
	u32 changed_ep_biपंचांगask = 0;
	अचिन्हित पूर्णांक slot_id;
	अचिन्हित पूर्णांक ep_index;
	अचिन्हित पूर्णांक ep_state;
	पूर्णांक i;

	slot_id = udev->slot_id;
	अगर (!xhci->devs[slot_id])
		वापस 0;

	क्रम (i = 0; i < num_eps; i++) अणु
		ep_index = xhci_get_endpoपूर्णांक_index(&eps[i]->desc);
		ep_state = xhci->devs[slot_id]->eps[ep_index].ep_state;
		/* Are streams alपढ़ोy being मुक्तd क्रम the endpoपूर्णांक? */
		अगर (ep_state & EP_GETTING_NO_STREAMS) अणु
			xhci_warn(xhci, "WARN Can't disable streams for "
					"endpoint 0x%x, "
					"streams are being disabled already\n",
					eps[i]->desc.bEndpoपूर्णांकAddress);
			वापस 0;
		पूर्ण
		/* Are there actually any streams to मुक्त? */
		अगर (!(ep_state & EP_HAS_STREAMS) &&
				!(ep_state & EP_GETTING_STREAMS)) अणु
			xhci_warn(xhci, "WARN Can't disable streams for "
					"endpoint 0x%x, "
					"streams are already disabled!\n",
					eps[i]->desc.bEndpoपूर्णांकAddress);
			xhci_warn(xhci, "WARN xhci_free_streams() called "
					"with non-streams endpoint\n");
			वापस 0;
		पूर्ण
		changed_ep_biपंचांगask |= xhci_get_endpoपूर्णांक_flag(&eps[i]->desc);
	पूर्ण
	वापस changed_ep_biपंचांगask;
पूर्ण

/*
 * The USB device drivers use this function (through the HCD पूर्णांकerface in USB
 * core) to prepare a set of bulk endpoपूर्णांकs to use streams.  Streams are used to
 * coordinate mass storage command queueing across multiple endpoपूर्णांकs (basically
 * a stream ID == a task ID).
 *
 * Setting up streams involves allocating the same size stream context array
 * क्रम each endpoपूर्णांक and issuing a configure endpoपूर्णांक command क्रम all endpoपूर्णांकs.
 *
 * Don't allow the call to succeed अगर one endpoपूर्णांक only supports one stream
 * (which means it करोesn't support streams at all).
 *
 * Drivers may get less stream IDs than they asked क्रम, अगर the host controller
 * hardware or endpoपूर्णांकs claim they can't support the number of requested
 * stream IDs.
 */
अटल पूर्णांक xhci_alloc_streams(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
		अचिन्हित पूर्णांक num_streams, gfp_t mem_flags)
अणु
	पूर्णांक i, ret;
	काष्ठा xhci_hcd *xhci;
	काष्ठा xhci_virt_device *vdev;
	काष्ठा xhci_command *config_cmd;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	अचिन्हित पूर्णांक ep_index;
	अचिन्हित पूर्णांक num_stream_ctxs;
	अचिन्हित पूर्णांक max_packet;
	अचिन्हित दीर्घ flags;
	u32 changed_ep_biपंचांगask = 0;

	अगर (!eps)
		वापस -EINVAL;

	/* Add one to the number of streams requested to account क्रम
	 * stream 0 that is reserved क्रम xHCI usage.
	 */
	num_streams += 1;
	xhci = hcd_to_xhci(hcd);
	xhci_dbg(xhci, "Driver wants %u stream IDs (including stream 0).\n",
			num_streams);

	/* MaxPSASize value 0 (2 streams) means streams are not supported */
	अगर ((xhci->quirks & XHCI_BROKEN_STREAMS) ||
			HCC_MAX_PSA(xhci->hcc_params) < 4) अणु
		xhci_dbg(xhci, "xHCI controller does not support streams.\n");
		वापस -ENOSYS;
	पूर्ण

	config_cmd = xhci_alloc_command_with_ctx(xhci, true, mem_flags);
	अगर (!config_cmd)
		वापस -ENOMEM;

	ctrl_ctx = xhci_get_input_control_ctx(config_cmd->in_ctx);
	अगर (!ctrl_ctx) अणु
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		xhci_मुक्त_command(xhci, config_cmd);
		वापस -ENOMEM;
	पूर्ण

	/* Check to make sure all endpoपूर्णांकs are not alपढ़ोy configured क्रम
	 * streams.  While we're at it, find the maximum number of streams that
	 * all the endpoपूर्णांकs will support and check क्रम duplicate endpoपूर्णांकs.
	 */
	spin_lock_irqsave(&xhci->lock, flags);
	ret = xhci_calculate_streams_and_biपंचांगask(xhci, udev, eps,
			num_eps, &num_streams, &changed_ep_biपंचांगask);
	अगर (ret < 0) अणु
		xhci_मुक्त_command(xhci, config_cmd);
		spin_unlock_irqrestore(&xhci->lock, flags);
		वापस ret;
	पूर्ण
	अगर (num_streams <= 1) अणु
		xhci_warn(xhci, "WARN: endpoints can't handle "
				"more than one stream.\n");
		xhci_मुक्त_command(xhci, config_cmd);
		spin_unlock_irqrestore(&xhci->lock, flags);
		वापस -EINVAL;
	पूर्ण
	vdev = xhci->devs[udev->slot_id];
	/* Mark each endpoपूर्णांक as being in transition, so
	 * xhci_urb_enqueue() will reject all URBs.
	 */
	क्रम (i = 0; i < num_eps; i++) अणु
		ep_index = xhci_get_endpoपूर्णांक_index(&eps[i]->desc);
		vdev->eps[ep_index].ep_state |= EP_GETTING_STREAMS;
	पूर्ण
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* Setup पूर्णांकernal data काष्ठाures and allocate HW data काष्ठाures क्रम
	 * streams (but करोn't install the HW काष्ठाures in the input context
	 * until we're sure all memory allocation succeeded).
	 */
	xhci_calculate_streams_entries(xhci, &num_streams, &num_stream_ctxs);
	xhci_dbg(xhci, "Need %u stream ctx entries for %u stream IDs.\n",
			num_stream_ctxs, num_streams);

	क्रम (i = 0; i < num_eps; i++) अणु
		ep_index = xhci_get_endpoपूर्णांक_index(&eps[i]->desc);
		max_packet = usb_endpoपूर्णांक_maxp(&eps[i]->desc);
		vdev->eps[ep_index].stream_info = xhci_alloc_stream_info(xhci,
				num_stream_ctxs,
				num_streams,
				max_packet, mem_flags);
		अगर (!vdev->eps[ep_index].stream_info)
			जाओ cleanup;
		/* Set maxPstreams in endpoपूर्णांक context and update deq ptr to
		 * poपूर्णांक to stream context array. FIXME
		 */
	पूर्ण

	/* Set up the input context क्रम a configure endpoपूर्णांक command. */
	क्रम (i = 0; i < num_eps; i++) अणु
		काष्ठा xhci_ep_ctx *ep_ctx;

		ep_index = xhci_get_endpoपूर्णांक_index(&eps[i]->desc);
		ep_ctx = xhci_get_ep_ctx(xhci, config_cmd->in_ctx, ep_index);

		xhci_endpoपूर्णांक_copy(xhci, config_cmd->in_ctx,
				vdev->out_ctx, ep_index);
		xhci_setup_streams_ep_input_ctx(xhci, ep_ctx,
				vdev->eps[ep_index].stream_info);
	पूर्ण
	/* Tell the HW to drop its old copy of the endpoपूर्णांक context info
	 * and add the updated copy from the input context.
	 */
	xhci_setup_input_ctx_क्रम_config_ep(xhci, config_cmd->in_ctx,
			vdev->out_ctx, ctrl_ctx,
			changed_ep_biपंचांगask, changed_ep_biपंचांगask);

	/* Issue and रुको क्रम the configure endpoपूर्णांक command */
	ret = xhci_configure_endpoपूर्णांक(xhci, udev, config_cmd,
			false, false);

	/* xHC rejected the configure endpoपूर्णांक command क्रम some reason, so we
	 * leave the old ring पूर्णांकact and मुक्त our पूर्णांकernal streams data
	 * काष्ठाure.
	 */
	अगर (ret < 0)
		जाओ cleanup;

	spin_lock_irqsave(&xhci->lock, flags);
	क्रम (i = 0; i < num_eps; i++) अणु
		ep_index = xhci_get_endpoपूर्णांक_index(&eps[i]->desc);
		vdev->eps[ep_index].ep_state &= ~EP_GETTING_STREAMS;
		xhci_dbg(xhci, "Slot %u ep ctx %u now has streams.\n",
			 udev->slot_id, ep_index);
		vdev->eps[ep_index].ep_state |= EP_HAS_STREAMS;
	पूर्ण
	xhci_मुक्त_command(xhci, config_cmd);
	spin_unlock_irqrestore(&xhci->lock, flags);

	क्रम (i = 0; i < num_eps; i++) अणु
		ep_index = xhci_get_endpoपूर्णांक_index(&eps[i]->desc);
		xhci_debugfs_create_stream_files(xhci, vdev, ep_index);
	पूर्ण
	/* Subtract 1 क्रम stream 0, which drivers can't use */
	वापस num_streams - 1;

cleanup:
	/* If it didn't work, मुक्त the streams! */
	क्रम (i = 0; i < num_eps; i++) अणु
		ep_index = xhci_get_endpoपूर्णांक_index(&eps[i]->desc);
		xhci_मुक्त_stream_info(xhci, vdev->eps[ep_index].stream_info);
		vdev->eps[ep_index].stream_info = शून्य;
		/* FIXME Unset maxPstreams in endpoपूर्णांक context and
		 * update deq ptr to poपूर्णांक to normal string ring.
		 */
		vdev->eps[ep_index].ep_state &= ~EP_GETTING_STREAMS;
		vdev->eps[ep_index].ep_state &= ~EP_HAS_STREAMS;
		xhci_endpoपूर्णांक_zero(xhci, vdev, eps[i]);
	पूर्ण
	xhci_मुक्त_command(xhci, config_cmd);
	वापस -ENOMEM;
पूर्ण

/* Transition the endpoपूर्णांक from using streams to being a "normal" endpoपूर्णांक
 * without streams.
 *
 * Modअगरy the endpoपूर्णांक context state, submit a configure endpoपूर्णांक command,
 * and मुक्त all endpoपूर्णांक rings क्रम streams अगर that completes successfully.
 */
अटल पूर्णांक xhci_मुक्त_streams(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक **eps, अचिन्हित पूर्णांक num_eps,
		gfp_t mem_flags)
अणु
	पूर्णांक i, ret;
	काष्ठा xhci_hcd *xhci;
	काष्ठा xhci_virt_device *vdev;
	काष्ठा xhci_command *command;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	अचिन्हित पूर्णांक ep_index;
	अचिन्हित दीर्घ flags;
	u32 changed_ep_biपंचांगask;

	xhci = hcd_to_xhci(hcd);
	vdev = xhci->devs[udev->slot_id];

	/* Set up a configure endpoपूर्णांक command to हटाओ the streams rings */
	spin_lock_irqsave(&xhci->lock, flags);
	changed_ep_biपंचांगask = xhci_calculate_no_streams_biपंचांगask(xhci,
			udev, eps, num_eps);
	अगर (changed_ep_biपंचांगask == 0) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		वापस -EINVAL;
	पूर्ण

	/* Use the xhci_command काष्ठाure from the first endpoपूर्णांक.  We may have
	 * allocated too many, but the driver may call xhci_मुक्त_streams() क्रम
	 * each endpoपूर्णांक it grouped पूर्णांकo one call to xhci_alloc_streams().
	 */
	ep_index = xhci_get_endpoपूर्णांक_index(&eps[0]->desc);
	command = vdev->eps[ep_index].stream_info->मुक्त_streams_command;
	ctrl_ctx = xhci_get_input_control_ctx(command->in_ctx);
	अगर (!ctrl_ctx) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_eps; i++) अणु
		काष्ठा xhci_ep_ctx *ep_ctx;

		ep_index = xhci_get_endpoपूर्णांक_index(&eps[i]->desc);
		ep_ctx = xhci_get_ep_ctx(xhci, command->in_ctx, ep_index);
		xhci->devs[udev->slot_id]->eps[ep_index].ep_state |=
			EP_GETTING_NO_STREAMS;

		xhci_endpoपूर्णांक_copy(xhci, command->in_ctx,
				vdev->out_ctx, ep_index);
		xhci_setup_no_streams_ep_input_ctx(ep_ctx,
				&vdev->eps[ep_index]);
	पूर्ण
	xhci_setup_input_ctx_क्रम_config_ep(xhci, command->in_ctx,
			vdev->out_ctx, ctrl_ctx,
			changed_ep_biपंचांगask, changed_ep_biपंचांगask);
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* Issue and रुको क्रम the configure endpoपूर्णांक command,
	 * which must succeed.
	 */
	ret = xhci_configure_endpoपूर्णांक(xhci, udev, command,
			false, true);

	/* xHC rejected the configure endpoपूर्णांक command क्रम some reason, so we
	 * leave the streams rings पूर्णांकact.
	 */
	अगर (ret < 0)
		वापस ret;

	spin_lock_irqsave(&xhci->lock, flags);
	क्रम (i = 0; i < num_eps; i++) अणु
		ep_index = xhci_get_endpoपूर्णांक_index(&eps[i]->desc);
		xhci_मुक्त_stream_info(xhci, vdev->eps[ep_index].stream_info);
		vdev->eps[ep_index].stream_info = शून्य;
		/* FIXME Unset maxPstreams in endpoपूर्णांक context and
		 * update deq ptr to poपूर्णांक to normal string ring.
		 */
		vdev->eps[ep_index].ep_state &= ~EP_GETTING_NO_STREAMS;
		vdev->eps[ep_index].ep_state &= ~EP_HAS_STREAMS;
	पूर्ण
	spin_unlock_irqrestore(&xhci->lock, flags);

	वापस 0;
पूर्ण

/*
 * Deletes endpoपूर्णांक resources क्रम endpoपूर्णांकs that were active beक्रमe a Reset
 * Device command, or a Disable Slot command.  The Reset Device command leaves
 * the control endpoपूर्णांक पूर्णांकact, whereas the Disable Slot command deletes it.
 *
 * Must be called with xhci->lock held.
 */
व्योम xhci_मुक्त_device_endpoपूर्णांक_resources(काष्ठा xhci_hcd *xhci,
	काष्ठा xhci_virt_device *virt_dev, bool drop_control_ep)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक num_dropped_eps = 0;
	अचिन्हित पूर्णांक drop_flags = 0;

	क्रम (i = (drop_control_ep ? 0 : 1); i < 31; i++) अणु
		अगर (virt_dev->eps[i].ring) अणु
			drop_flags |= 1 << i;
			num_dropped_eps++;
		पूर्ण
	पूर्ण
	xhci->num_active_eps -= num_dropped_eps;
	अगर (num_dropped_eps)
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Dropped %u ep ctxs, flags = 0x%x, "
				"%u now active.",
				num_dropped_eps, drop_flags,
				xhci->num_active_eps);
पूर्ण

/*
 * This submits a Reset Device Command, which will set the device state to 0,
 * set the device address to 0, and disable all the endpoपूर्णांकs except the शेष
 * control endpoपूर्णांक.  The USB core should come back and call
 * xhci_address_device(), and then re-set up the configuration.  If this is
 * called because of a usb_reset_and_verअगरy_device(), then the old alternate
 * settings will be re-installed through the normal bandwidth allocation
 * functions.
 *
 * Wait क्रम the Reset Device command to finish.  Remove all काष्ठाures
 * associated with the endpoपूर्णांकs that were disabled.  Clear the input device
 * काष्ठाure? Reset the control endpoपूर्णांक 0 max packet size?
 *
 * If the virt_dev to be reset करोes not exist or करोes not match the udev,
 * it means the device is lost, possibly due to the xHC restore error and
 * re-initialization during S3/S4. In this हाल, call xhci_alloc_dev() to
 * re-allocate the device.
 */
अटल पूर्णांक xhci_discover_or_reset_device(काष्ठा usb_hcd *hcd,
		काष्ठा usb_device *udev)
अणु
	पूर्णांक ret, i;
	अचिन्हित दीर्घ flags;
	काष्ठा xhci_hcd *xhci;
	अचिन्हित पूर्णांक slot_id;
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा xhci_command *reset_device_cmd;
	काष्ठा xhci_slot_ctx *slot_ctx;
	पूर्णांक old_active_eps = 0;

	ret = xhci_check_args(hcd, udev, शून्य, 0, false, __func__);
	अगर (ret <= 0)
		वापस ret;
	xhci = hcd_to_xhci(hcd);
	slot_id = udev->slot_id;
	virt_dev = xhci->devs[slot_id];
	अगर (!virt_dev) अणु
		xhci_dbg(xhci, "The device to be reset with slot ID %u does "
				"not exist. Re-allocate the device\n", slot_id);
		ret = xhci_alloc_dev(hcd, udev);
		अगर (ret == 1)
			वापस 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (virt_dev->tt_info)
		old_active_eps = virt_dev->tt_info->active_eps;

	अगर (virt_dev->udev != udev) अणु
		/* If the virt_dev and the udev करोes not match, this virt_dev
		 * may beदीर्घ to another udev.
		 * Re-allocate the device.
		 */
		xhci_dbg(xhci, "The device to be reset with slot ID %u does "
				"not match the udev. Re-allocate the device\n",
				slot_id);
		ret = xhci_alloc_dev(hcd, udev);
		अगर (ret == 1)
			वापस 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	/* If device is not setup, there is no poपूर्णांक in resetting it */
	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->out_ctx);
	अगर (GET_SLOT_STATE(le32_to_cpu(slot_ctx->dev_state)) ==
						SLOT_STATE_DISABLED)
		वापस 0;

	trace_xhci_discover_or_reset_device(slot_ctx);

	xhci_dbg(xhci, "Resetting device with slot ID %u\n", slot_id);
	/* Allocate the command काष्ठाure that holds the काष्ठा completion.
	 * Assume we're in process context, since the normal device reset
	 * process has to रुको क्रम the device anyway.  Storage devices are
	 * reset as part of error handling, so use GFP_NOIO instead of
	 * GFP_KERNEL.
	 */
	reset_device_cmd = xhci_alloc_command(xhci, true, GFP_NOIO);
	अगर (!reset_device_cmd) अणु
		xhci_dbg(xhci, "Couldn't allocate command structure.\n");
		वापस -ENOMEM;
	पूर्ण

	/* Attempt to submit the Reset Device command to the command ring */
	spin_lock_irqsave(&xhci->lock, flags);

	ret = xhci_queue_reset_device(xhci, reset_device_cmd, slot_id);
	अगर (ret) अणु
		xhci_dbg(xhci, "FIXME: allocate a command ring segment\n");
		spin_unlock_irqrestore(&xhci->lock, flags);
		जाओ command_cleanup;
	पूर्ण
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* Wait क्रम the Reset Device command to finish */
	रुको_क्रम_completion(reset_device_cmd->completion);

	/* The Reset Device command can't fail, according to the 0.95/0.96 spec,
	 * unless we tried to reset a slot ID that wasn't enabled,
	 * or the device wasn't in the addressed or configured state.
	 */
	ret = reset_device_cmd->status;
	चयन (ret) अणु
	हाल COMP_COMMAND_ABORTED:
	हाल COMP_COMMAND_RING_STOPPED:
		xhci_warn(xhci, "Timeout waiting for reset device command\n");
		ret = -ETIME;
		जाओ command_cleanup;
	हाल COMP_SLOT_NOT_ENABLED_ERROR: /* 0.95 completion क्रम bad slot ID */
	हाल COMP_CONTEXT_STATE_ERROR: /* 0.96 completion code क्रम same thing */
		xhci_dbg(xhci, "Can't reset device (slot ID %u) in %s state\n",
				slot_id,
				xhci_get_slot_state(xhci, virt_dev->out_ctx));
		xhci_dbg(xhci, "Not freeing device rings.\n");
		/* Don't treat this as an error.  May change my mind later. */
		ret = 0;
		जाओ command_cleanup;
	हाल COMP_SUCCESS:
		xhci_dbg(xhci, "Successful reset device command.\n");
		अवरोध;
	शेष:
		अगर (xhci_is_venकरोr_info_code(xhci, ret))
			अवरोध;
		xhci_warn(xhci, "Unknown completion code %u for "
				"reset device command.\n", ret);
		ret = -EINVAL;
		जाओ command_cleanup;
	पूर्ण

	/* Free up host controller endpoपूर्णांक resources */
	अगर ((xhci->quirks & XHCI_EP_LIMIT_QUIRK)) अणु
		spin_lock_irqsave(&xhci->lock, flags);
		/* Don't delete the शेष control endpoपूर्णांक resources */
		xhci_मुक्त_device_endpoपूर्णांक_resources(xhci, virt_dev, false);
		spin_unlock_irqrestore(&xhci->lock, flags);
	पूर्ण

	/* Everything but endpoपूर्णांक 0 is disabled, so मुक्त the rings. */
	क्रम (i = 1; i < 31; i++) अणु
		काष्ठा xhci_virt_ep *ep = &virt_dev->eps[i];

		अगर (ep->ep_state & EP_HAS_STREAMS) अणु
			xhci_warn(xhci, "WARN: endpoint 0x%02x has streams on device reset, freeing streams.\n",
					xhci_get_endpoपूर्णांक_address(i));
			xhci_मुक्त_stream_info(xhci, ep->stream_info);
			ep->stream_info = शून्य;
			ep->ep_state &= ~EP_HAS_STREAMS;
		पूर्ण

		अगर (ep->ring) अणु
			xhci_debugfs_हटाओ_endpoपूर्णांक(xhci, virt_dev, i);
			xhci_मुक्त_endpoपूर्णांक_ring(xhci, virt_dev, i);
		पूर्ण
		अगर (!list_empty(&virt_dev->eps[i].bw_endpoपूर्णांक_list))
			xhci_drop_ep_from_पूर्णांकerval_table(xhci,
					&virt_dev->eps[i].bw_info,
					virt_dev->bw_table,
					udev,
					&virt_dev->eps[i],
					virt_dev->tt_info);
		xhci_clear_endpoपूर्णांक_bw_info(&virt_dev->eps[i].bw_info);
	पूर्ण
	/* If necessary, update the number of active TTs on this root port */
	xhci_update_tt_active_eps(xhci, virt_dev, old_active_eps);
	virt_dev->flags = 0;
	ret = 0;

command_cleanup:
	xhci_मुक्त_command(xhci, reset_device_cmd);
	वापस ret;
पूर्ण

/*
 * At this poपूर्णांक, the काष्ठा usb_device is about to go away, the device has
 * disconnected, and all traffic has been stopped and the endpoपूर्णांकs have been
 * disabled.  Free any HC data काष्ठाures associated with that device.
 */
अटल व्योम xhci_मुक्त_dev(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा xhci_slot_ctx *slot_ctx;
	पूर्णांक i, ret;

#अगर_अघोषित CONFIG_USB_DEFAULT_PERSIST
	/*
	 * We called pm_runसमय_get_noresume when the device was attached.
	 * Decrement the counter here to allow controller to runसमय suspend
	 * अगर no devices reमुख्य.
	 */
	अगर (xhci->quirks & XHCI_RESET_ON_RESUME)
		pm_runसमय_put_noidle(hcd->self.controller);
#पूर्ण_अगर

	ret = xhci_check_args(hcd, udev, शून्य, 0, true, __func__);
	/* If the host is halted due to driver unload, we still need to मुक्त the
	 * device.
	 */
	अगर (ret <= 0 && ret != -ENODEV)
		वापस;

	virt_dev = xhci->devs[udev->slot_id];
	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->out_ctx);
	trace_xhci_मुक्त_dev(slot_ctx);

	/* Stop any wayward समयr functions (which may grab the lock) */
	क्रम (i = 0; i < 31; i++) अणु
		virt_dev->eps[i].ep_state &= ~EP_STOP_CMD_PENDING;
		del_समयr_sync(&virt_dev->eps[i].stop_cmd_समयr);
	पूर्ण
	virt_dev->udev = शून्य;
	ret = xhci_disable_slot(xhci, udev->slot_id);
	अगर (ret)
		xhci_मुक्त_virt_device(xhci, udev->slot_id);
पूर्ण

पूर्णांक xhci_disable_slot(काष्ठा xhci_hcd *xhci, u32 slot_id)
अणु
	काष्ठा xhci_command *command;
	अचिन्हित दीर्घ flags;
	u32 state;
	पूर्णांक ret = 0;

	command = xhci_alloc_command(xhci, false, GFP_KERNEL);
	अगर (!command)
		वापस -ENOMEM;

	xhci_debugfs_हटाओ_slot(xhci, slot_id);

	spin_lock_irqsave(&xhci->lock, flags);
	/* Don't disable the slot अगर the host controller is dead. */
	state = पढ़ोl(&xhci->op_regs->status);
	अगर (state == 0xffffffff || (xhci->xhc_state & XHCI_STATE_DYING) ||
			(xhci->xhc_state & XHCI_STATE_HALTED)) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		kमुक्त(command);
		वापस -ENODEV;
	पूर्ण

	ret = xhci_queue_slot_control(xhci, command, TRB_DISABLE_SLOT,
				slot_id);
	अगर (ret) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		kमुक्त(command);
		वापस ret;
	पूर्ण
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);
	वापस ret;
पूर्ण

/*
 * Checks अगर we have enough host controller resources क्रम the शेष control
 * endpoपूर्णांक.
 *
 * Must be called with xhci->lock held.
 */
अटल पूर्णांक xhci_reserve_host_control_ep_resources(काष्ठा xhci_hcd *xhci)
अणु
	अगर (xhci->num_active_eps + 1 > xhci->limit_active_eps) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Not enough ep ctxs: "
				"%u active, need to add 1, limit is %u.",
				xhci->num_active_eps, xhci->limit_active_eps);
		वापस -ENOMEM;
	पूर्ण
	xhci->num_active_eps += 1;
	xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
			"Adding 1 ep ctx, %u now active.",
			xhci->num_active_eps);
	वापस 0;
पूर्ण


/*
 * Returns 0 अगर the xHC ran out of device slots, the Enable Slot command
 * समयd out, or allocating memory failed.  Returns 1 on success.
 */
पूर्णांक xhci_alloc_dev(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा xhci_virt_device *vdev;
	काष्ठा xhci_slot_ctx *slot_ctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, slot_id;
	काष्ठा xhci_command *command;

	command = xhci_alloc_command(xhci, true, GFP_KERNEL);
	अगर (!command)
		वापस 0;

	spin_lock_irqsave(&xhci->lock, flags);
	ret = xhci_queue_slot_control(xhci, command, TRB_ENABLE_SLOT, 0);
	अगर (ret) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_dbg(xhci, "FIXME: allocate a command ring segment\n");
		xhci_मुक्त_command(xhci, command);
		वापस 0;
	पूर्ण
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	रुको_क्रम_completion(command->completion);
	slot_id = command->slot_id;

	अगर (!slot_id || command->status != COMP_SUCCESS) अणु
		xhci_err(xhci, "Error while assigning device slot ID\n");
		xhci_err(xhci, "Max number of devices this xHCI host supports is %u.\n",
				HCS_MAX_SLOTS(
					पढ़ोl(&xhci->cap_regs->hcs_params1)));
		xhci_मुक्त_command(xhci, command);
		वापस 0;
	पूर्ण

	xhci_मुक्त_command(xhci, command);

	अगर ((xhci->quirks & XHCI_EP_LIMIT_QUIRK)) अणु
		spin_lock_irqsave(&xhci->lock, flags);
		ret = xhci_reserve_host_control_ep_resources(xhci);
		अगर (ret) अणु
			spin_unlock_irqrestore(&xhci->lock, flags);
			xhci_warn(xhci, "Not enough host resources, "
					"active endpoint contexts = %u\n",
					xhci->num_active_eps);
			जाओ disable_slot;
		पूर्ण
		spin_unlock_irqrestore(&xhci->lock, flags);
	पूर्ण
	/* Use GFP_NOIO, since this function can be called from
	 * xhci_discover_or_reset_device(), which may be called as part of
	 * mass storage driver error handling.
	 */
	अगर (!xhci_alloc_virt_device(xhci, slot_id, udev, GFP_NOIO)) अणु
		xhci_warn(xhci, "Could not allocate xHCI USB device data structures\n");
		जाओ disable_slot;
	पूर्ण
	vdev = xhci->devs[slot_id];
	slot_ctx = xhci_get_slot_ctx(xhci, vdev->out_ctx);
	trace_xhci_alloc_dev(slot_ctx);

	udev->slot_id = slot_id;

	xhci_debugfs_create_slot(xhci, slot_id);

#अगर_अघोषित CONFIG_USB_DEFAULT_PERSIST
	/*
	 * If resetting upon resume, we can't put the controller पूर्णांकo runसमय
	 * suspend अगर there is a device attached.
	 */
	अगर (xhci->quirks & XHCI_RESET_ON_RESUME)
		pm_runसमय_get_noresume(hcd->self.controller);
#पूर्ण_अगर

	/* Is this a LS or FS device under a HS hub? */
	/* Hub or peripherial? */
	वापस 1;

disable_slot:
	ret = xhci_disable_slot(xhci, udev->slot_id);
	अगर (ret)
		xhci_मुक्त_virt_device(xhci, udev->slot_id);

	वापस 0;
पूर्ण

/*
 * Issue an Address Device command and optionally send a corresponding
 * SetAddress request to the device.
 */
अटल पूर्णांक xhci_setup_device(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev,
			     क्रमागत xhci_setup_dev setup)
अणु
	स्थिर अक्षर *act = setup == SETUP_CONTEXT_ONLY ? "context" : "address";
	अचिन्हित दीर्घ flags;
	काष्ठा xhci_virt_device *virt_dev;
	पूर्णांक ret = 0;
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा xhci_slot_ctx *slot_ctx;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	u64 temp_64;
	काष्ठा xhci_command *command = शून्य;

	mutex_lock(&xhci->mutex);

	अगर (xhci->xhc_state) अणु	/* dying, removing or halted */
		ret = -ESHUTDOWN;
		जाओ out;
	पूर्ण

	अगर (!udev->slot_id) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_address,
				"Bad Slot ID %d", udev->slot_id);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	virt_dev = xhci->devs[udev->slot_id];

	अगर (WARN_ON(!virt_dev)) अणु
		/*
		 * In plug/unplug torture test with an NEC controller,
		 * a zero-dereference was observed once due to virt_dev = 0.
		 * Prपूर्णांक useful debug rather than crash अगर it is observed again!
		 */
		xhci_warn(xhci, "Virt dev invalid for slot_id 0x%x!\n",
			udev->slot_id);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->out_ctx);
	trace_xhci_setup_device_slot(slot_ctx);

	अगर (setup == SETUP_CONTEXT_ONLY) अणु
		अगर (GET_SLOT_STATE(le32_to_cpu(slot_ctx->dev_state)) ==
		    SLOT_STATE_DEFAULT) अणु
			xhci_dbg(xhci, "Slot already in default state\n");
			जाओ out;
		पूर्ण
	पूर्ण

	command = xhci_alloc_command(xhci, true, GFP_KERNEL);
	अगर (!command) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	command->in_ctx = virt_dev->in_ctx;

	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->in_ctx);
	ctrl_ctx = xhci_get_input_control_ctx(virt_dev->in_ctx);
	अगर (!ctrl_ctx) अणु
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	/*
	 * If this is the first Set Address since device plug-in or
	 * virt_device realloaction after a resume with an xHCI घातer loss,
	 * then set up the slot context.
	 */
	अगर (!slot_ctx->dev_info)
		xhci_setup_addressable_virt_dev(xhci, udev);
	/* Otherwise, update the control endpoपूर्णांक ring enqueue poपूर्णांकer. */
	अन्यथा
		xhci_copy_ep0_dequeue_पूर्णांकo_input_ctx(xhci, udev);
	ctrl_ctx->add_flags = cpu_to_le32(SLOT_FLAG | EP0_FLAG);
	ctrl_ctx->drop_flags = 0;

	trace_xhci_address_ctx(xhci, virt_dev->in_ctx,
				le32_to_cpu(slot_ctx->dev_info) >> 27);

	trace_xhci_address_ctrl_ctx(ctrl_ctx);
	spin_lock_irqsave(&xhci->lock, flags);
	trace_xhci_setup_device(virt_dev);
	ret = xhci_queue_address_device(xhci, command, virt_dev->in_ctx->dma,
					udev->slot_id, setup);
	अगर (ret) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_dbg_trace(xhci, trace_xhci_dbg_address,
				"FIXME: allocate a command ring segment");
		जाओ out;
	पूर्ण
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* ctrl tx can take up to 5 sec; XXX: need more समय क्रम xHC? */
	रुको_क्रम_completion(command->completion);

	/* FIXME: From section 4.3.4: "Software shall be responsible क्रम timing
	 * the SetAddress() "recovery interval" required by USB and पातing the
	 * command on a समयout.
	 */
	चयन (command->status) अणु
	हाल COMP_COMMAND_ABORTED:
	हाल COMP_COMMAND_RING_STOPPED:
		xhci_warn(xhci, "Timeout while waiting for setup device command\n");
		ret = -ETIME;
		अवरोध;
	हाल COMP_CONTEXT_STATE_ERROR:
	हाल COMP_SLOT_NOT_ENABLED_ERROR:
		xhci_err(xhci, "Setup ERROR: setup %s command for slot %d.\n",
			 act, udev->slot_id);
		ret = -EINVAL;
		अवरोध;
	हाल COMP_USB_TRANSACTION_ERROR:
		dev_warn(&udev->dev, "Device not responding to setup %s.\n", act);

		mutex_unlock(&xhci->mutex);
		ret = xhci_disable_slot(xhci, udev->slot_id);
		अगर (!ret)
			xhci_alloc_dev(hcd, udev);
		kमुक्त(command->completion);
		kमुक्त(command);
		वापस -EPROTO;
	हाल COMP_INCOMPATIBLE_DEVICE_ERROR:
		dev_warn(&udev->dev,
			 "ERROR: Incompatible device for setup %s command\n", act);
		ret = -ENODEV;
		अवरोध;
	हाल COMP_SUCCESS:
		xhci_dbg_trace(xhci, trace_xhci_dbg_address,
			       "Successful setup %s command", act);
		अवरोध;
	शेष:
		xhci_err(xhci,
			 "ERROR: unexpected setup %s command completion code 0x%x.\n",
			 act, command->status);
		trace_xhci_address_ctx(xhci, virt_dev->out_ctx, 1);
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	अगर (ret)
		जाओ out;
	temp_64 = xhci_पढ़ो_64(xhci, &xhci->op_regs->dcbaa_ptr);
	xhci_dbg_trace(xhci, trace_xhci_dbg_address,
			"Op regs DCBAA ptr = %#016llx", temp_64);
	xhci_dbg_trace(xhci, trace_xhci_dbg_address,
		"Slot ID %d dcbaa entry @%p = %#016llx",
		udev->slot_id,
		&xhci->dcbaa->dev_context_ptrs[udev->slot_id],
		(अचिन्हित दीर्घ दीर्घ)
		le64_to_cpu(xhci->dcbaa->dev_context_ptrs[udev->slot_id]));
	xhci_dbg_trace(xhci, trace_xhci_dbg_address,
			"Output Context DMA address = %#08llx",
			(अचिन्हित दीर्घ दीर्घ)virt_dev->out_ctx->dma);
	trace_xhci_address_ctx(xhci, virt_dev->in_ctx,
				le32_to_cpu(slot_ctx->dev_info) >> 27);
	/*
	 * USB core uses address 1 क्रम the roothubs, so we add one to the
	 * address given back to us by the HC.
	 */
	trace_xhci_address_ctx(xhci, virt_dev->out_ctx,
				le32_to_cpu(slot_ctx->dev_info) >> 27);
	/* Zero the input context control क्रम later use */
	ctrl_ctx->add_flags = 0;
	ctrl_ctx->drop_flags = 0;
	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->out_ctx);
	udev->devaddr = (u8)(le32_to_cpu(slot_ctx->dev_state) & DEV_ADDR_MASK);

	xhci_dbg_trace(xhci, trace_xhci_dbg_address,
		       "Internal device address = %d",
		       le32_to_cpu(slot_ctx->dev_state) & DEV_ADDR_MASK);
out:
	mutex_unlock(&xhci->mutex);
	अगर (command) अणु
		kमुक्त(command->completion);
		kमुक्त(command);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक xhci_address_device(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	वापस xhci_setup_device(hcd, udev, SETUP_CONTEXT_ADDRESS);
पूर्ण

अटल पूर्णांक xhci_enable_device(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	वापस xhci_setup_device(hcd, udev, SETUP_CONTEXT_ONLY);
पूर्ण

/*
 * Transfer the port index पूर्णांकo real index in the HW port status
 * रेजिस्टरs. Caculate offset between the port's PORTSC रेजिस्टर
 * and port status base. Divide the number of per port रेजिस्टर
 * to get the real index. The raw port number bases 1.
 */
पूर्णांक xhci_find_raw_port_number(काष्ठा usb_hcd *hcd, पूर्णांक port1)
अणु
	काष्ठा xhci_hub *rhub;

	rhub = xhci_get_rhub(hcd);
	वापस rhub->ports[port1 - 1]->hw_portnum + 1;
पूर्ण

/*
 * Issue an Evaluate Context command to change the Maximum Exit Latency in the
 * slot context.  If that succeeds, store the new MEL in the xhci_virt_device.
 */
अटल पूर्णांक __maybe_unused xhci_change_max_निकास_latency(काष्ठा xhci_hcd *xhci,
			काष्ठा usb_device *udev, u16 max_निकास_latency)
अणु
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा xhci_command *command;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	काष्ठा xhci_slot_ctx *slot_ctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&xhci->lock, flags);

	virt_dev = xhci->devs[udev->slot_id];

	/*
	 * virt_dev might not exists yet अगर xHC resumed from hibernate (S4) and
	 * xHC was re-initialized. Exit latency will be set later after
	 * hub_port_finish_reset() is करोne and xhci->devs[] are re-allocated
	 */

	अगर (!virt_dev || max_निकास_latency == virt_dev->current_mel) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		वापस 0;
	पूर्ण

	/* Attempt to issue an Evaluate Context command to change the MEL. */
	command = xhci->lpm_command;
	ctrl_ctx = xhci_get_input_control_ctx(command->in_ctx);
	अगर (!ctrl_ctx) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		वापस -ENOMEM;
	पूर्ण

	xhci_slot_copy(xhci, command->in_ctx, virt_dev->out_ctx);
	spin_unlock_irqrestore(&xhci->lock, flags);

	ctrl_ctx->add_flags |= cpu_to_le32(SLOT_FLAG);
	slot_ctx = xhci_get_slot_ctx(xhci, command->in_ctx);
	slot_ctx->dev_info2 &= cpu_to_le32(~((u32) MAX_EXIT));
	slot_ctx->dev_info2 |= cpu_to_le32(max_निकास_latency);
	slot_ctx->dev_state = 0;

	xhci_dbg_trace(xhci, trace_xhci_dbg_context_change,
			"Set up evaluate context for LPM MEL change.");

	/* Issue and रुको क्रम the evaluate context command. */
	ret = xhci_configure_endpoपूर्णांक(xhci, udev, command,
			true, true);

	अगर (!ret) अणु
		spin_lock_irqsave(&xhci->lock, flags);
		virt_dev->current_mel = max_निकास_latency;
		spin_unlock_irqrestore(&xhci->lock, flags);
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM

/* BESL to HIRD Encoding array क्रम USB2 LPM */
अटल पूर्णांक xhci_besl_encoding[16] = अणु125, 150, 200, 300, 400, 500, 1000, 2000,
	3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000पूर्ण;

/* Calculate HIRD/BESL क्रम USB2 PORTPMSC*/
अटल पूर्णांक xhci_calculate_hird_besl(काष्ठा xhci_hcd *xhci,
					काष्ठा usb_device *udev)
अणु
	पूर्णांक u2del, besl, besl_host;
	पूर्णांक besl_device = 0;
	u32 field;

	u2del = HCS_U2_LATENCY(xhci->hcs_params3);
	field = le32_to_cpu(udev->bos->ext_cap->bmAttributes);

	अगर (field & USB_BESL_SUPPORT) अणु
		क्रम (besl_host = 0; besl_host < 16; besl_host++) अणु
			अगर (xhci_besl_encoding[besl_host] >= u2del)
				अवरोध;
		पूर्ण
		/* Use baseline BESL value as शेष */
		अगर (field & USB_BESL_BASELINE_VALID)
			besl_device = USB_GET_BESL_BASELINE(field);
		अन्यथा अगर (field & USB_BESL_DEEP_VALID)
			besl_device = USB_GET_BESL_DEEP(field);
	पूर्ण अन्यथा अणु
		अगर (u2del <= 50)
			besl_host = 0;
		अन्यथा
			besl_host = (u2del - 51) / 75 + 1;
	पूर्ण

	besl = besl_host + besl_device;
	अगर (besl > 15)
		besl = 15;

	वापस besl;
पूर्ण

/* Calculate BESLD, L1 समयout and HIRDM क्रम USB2 PORTHLPMC */
अटल पूर्णांक xhci_calculate_usb2_hw_lpm_params(काष्ठा usb_device *udev)
अणु
	u32 field;
	पूर्णांक l1;
	पूर्णांक besld = 0;
	पूर्णांक hirdm = 0;

	field = le32_to_cpu(udev->bos->ext_cap->bmAttributes);

	/* xHCI l1 is set in steps of 256us, xHCI 1.0 section 5.4.11.2 */
	l1 = udev->l1_params.समयout / 256;

	/* device has preferred BESLD */
	अगर (field & USB_BESL_DEEP_VALID) अणु
		besld = USB_GET_BESL_DEEP(field);
		hirdm = 1;
	पूर्ण

	वापस PORT_BESLD(besld) | PORT_L1_TIMEOUT(l1) | PORT_HIRDM(hirdm);
पूर्ण

अटल पूर्णांक xhci_set_usb2_hardware_lpm(काष्ठा usb_hcd *hcd,
			काष्ठा usb_device *udev, पूर्णांक enable)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	काष्ठा xhci_port **ports;
	__le32 __iomem	*pm_addr, *hlpm_addr;
	u32		pm_val, hlpm_val, field;
	अचिन्हित पूर्णांक	port_num;
	अचिन्हित दीर्घ	flags;
	पूर्णांक		hird, निकास_latency;
	पूर्णांक		ret;

	अगर (xhci->quirks & XHCI_HW_LPM_DISABLE)
		वापस -EPERM;

	अगर (hcd->speed >= HCD_USB3 || !xhci->hw_lpm_support ||
			!udev->lpm_capable)
		वापस -EPERM;

	अगर (!udev->parent || udev->parent->parent ||
			udev->descriptor.bDeviceClass == USB_CLASS_HUB)
		वापस -EPERM;

	अगर (udev->usb2_hw_lpm_capable != 1)
		वापस -EPERM;

	spin_lock_irqsave(&xhci->lock, flags);

	ports = xhci->usb2_rhub.ports;
	port_num = udev->portnum - 1;
	pm_addr = ports[port_num]->addr + PORTPMSC;
	pm_val = पढ़ोl(pm_addr);
	hlpm_addr = ports[port_num]->addr + PORTHLPMC;

	xhci_dbg(xhci, "%s port %d USB2 hardware LPM\n",
			enable ? "enable" : "disable", port_num + 1);

	अगर (enable) अणु
		/* Host supports BESL समयout instead of HIRD */
		अगर (udev->usb2_hw_lpm_besl_capable) अणु
			/* अगर device करोesn't have a preferred BESL value use a
			 * शेष one which works with mixed HIRD and BESL
			 * प्रणालीs. See XHCI_DEFAULT_BESL definition in xhci.h
			 */
			field = le32_to_cpu(udev->bos->ext_cap->bmAttributes);
			अगर ((field & USB_BESL_SUPPORT) &&
			    (field & USB_BESL_BASELINE_VALID))
				hird = USB_GET_BESL_BASELINE(field);
			अन्यथा
				hird = udev->l1_params.besl;

			निकास_latency = xhci_besl_encoding[hird];
			spin_unlock_irqrestore(&xhci->lock, flags);

			/* USB 3.0 code dedicate one xhci->lpm_command->in_ctx
			 * input context क्रम link घातermanagement evaluate
			 * context commands. It is रक्षित by hcd->bandwidth
			 * mutex and is shared by all devices. We need to set
			 * the max ext latency in USB 2 BESL LPM as well, so
			 * use the same mutex and xhci_change_max_निकास_latency()
			 */
			mutex_lock(hcd->bandwidth_mutex);
			ret = xhci_change_max_निकास_latency(xhci, udev,
							   निकास_latency);
			mutex_unlock(hcd->bandwidth_mutex);

			अगर (ret < 0)
				वापस ret;
			spin_lock_irqsave(&xhci->lock, flags);

			hlpm_val = xhci_calculate_usb2_hw_lpm_params(udev);
			ग_लिखोl(hlpm_val, hlpm_addr);
			/* flush ग_लिखो */
			पढ़ोl(hlpm_addr);
		पूर्ण अन्यथा अणु
			hird = xhci_calculate_hird_besl(xhci, udev);
		पूर्ण

		pm_val &= ~PORT_HIRD_MASK;
		pm_val |= PORT_HIRD(hird) | PORT_RWE | PORT_L1DS(udev->slot_id);
		ग_लिखोl(pm_val, pm_addr);
		pm_val = पढ़ोl(pm_addr);
		pm_val |= PORT_HLE;
		ग_लिखोl(pm_val, pm_addr);
		/* flush ग_लिखो */
		पढ़ोl(pm_addr);
	पूर्ण अन्यथा अणु
		pm_val &= ~(PORT_HLE | PORT_RWE | PORT_HIRD_MASK | PORT_L1DS_MASK);
		ग_लिखोl(pm_val, pm_addr);
		/* flush ग_लिखो */
		पढ़ोl(pm_addr);
		अगर (udev->usb2_hw_lpm_besl_capable) अणु
			spin_unlock_irqrestore(&xhci->lock, flags);
			mutex_lock(hcd->bandwidth_mutex);
			xhci_change_max_निकास_latency(xhci, udev, 0);
			mutex_unlock(hcd->bandwidth_mutex);
			पढ़ोl_poll_समयout(ports[port_num]->addr, pm_val,
					   (pm_val & PORT_PLS_MASK) == XDEV_U0,
					   100, 10000);
			वापस 0;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&xhci->lock, flags);
	वापस 0;
पूर्ण

/* check अगर a usb2 port supports a given extened capability protocol
 * only USB2 ports extended protocol capability values are cached.
 * Return 1 अगर capability is supported
 */
अटल पूर्णांक xhci_check_usb2_port_capability(काष्ठा xhci_hcd *xhci, पूर्णांक port,
					   अचिन्हित capability)
अणु
	u32 port_offset, port_count;
	पूर्णांक i;

	क्रम (i = 0; i < xhci->num_ext_caps; i++) अणु
		अगर (xhci->ext_caps[i] & capability) अणु
			/* port offsets starts at 1 */
			port_offset = XHCI_EXT_PORT_OFF(xhci->ext_caps[i]) - 1;
			port_count = XHCI_EXT_PORT_COUNT(xhci->ext_caps[i]);
			अगर (port >= port_offset &&
			    port < port_offset + port_count)
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xhci_update_device(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	पूर्णांक		portnum = udev->portnum - 1;

	अगर (hcd->speed >= HCD_USB3 || !udev->lpm_capable)
		वापस 0;

	/* we only support lpm क्रम non-hub device connected to root hub yet */
	अगर (!udev->parent || udev->parent->parent ||
			udev->descriptor.bDeviceClass == USB_CLASS_HUB)
		वापस 0;

	अगर (xhci->hw_lpm_support == 1 &&
			xhci_check_usb2_port_capability(
				xhci, portnum, XHCI_HLC)) अणु
		udev->usb2_hw_lpm_capable = 1;
		udev->l1_params.समयout = XHCI_L1_TIMEOUT;
		udev->l1_params.besl = XHCI_DEFAULT_BESL;
		अगर (xhci_check_usb2_port_capability(xhci, portnum,
					XHCI_BLC))
			udev->usb2_hw_lpm_besl_capable = 1;
	पूर्ण

	वापस 0;
पूर्ण

/*---------------------- USB 3.0 Link PM functions ------------------------*/

/* Service पूर्णांकerval in nanoseconds = 2^(bInterval - 1) * 125us * 1000ns / 1us */
अटल अचिन्हित दीर्घ दीर्घ xhci_service_पूर्णांकerval_to_ns(
		काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	वापस (1ULL << (desc->bInterval - 1)) * 125 * 1000;
पूर्ण

अटल u16 xhci_get_समयout_no_hub_lpm(काष्ठा usb_device *udev,
		क्रमागत usb3_link_state state)
अणु
	अचिन्हित दीर्घ दीर्घ sel;
	अचिन्हित दीर्घ दीर्घ pel;
	अचिन्हित पूर्णांक max_sel_pel;
	अक्षर *state_name;

	चयन (state) अणु
	हाल USB3_LPM_U1:
		/* Convert SEL and PEL stored in nanoseconds to microseconds */
		sel = DIV_ROUND_UP(udev->u1_params.sel, 1000);
		pel = DIV_ROUND_UP(udev->u1_params.pel, 1000);
		max_sel_pel = USB3_LPM_MAX_U1_SEL_PEL;
		state_name = "U1";
		अवरोध;
	हाल USB3_LPM_U2:
		sel = DIV_ROUND_UP(udev->u2_params.sel, 1000);
		pel = DIV_ROUND_UP(udev->u2_params.pel, 1000);
		max_sel_pel = USB3_LPM_MAX_U2_SEL_PEL;
		state_name = "U2";
		अवरोध;
	शेष:
		dev_warn(&udev->dev, "%s: Can't get timeout for non-U1 or U2 state.\n",
				__func__);
		वापस USB3_LPM_DISABLED;
	पूर्ण

	अगर (sel <= max_sel_pel && pel <= max_sel_pel)
		वापस USB3_LPM_DEVICE_INITIATED;

	अगर (sel > max_sel_pel)
		dev_dbg(&udev->dev, "Device-initiated %s disabled "
				"due to long SEL %llu ms\n",
				state_name, sel);
	अन्यथा
		dev_dbg(&udev->dev, "Device-initiated %s disabled "
				"due to long PEL %llu ms\n",
				state_name, pel);
	वापस USB3_LPM_DISABLED;
पूर्ण

/* The U1 समयout should be the maximum of the following values:
 *  - For control endpoपूर्णांकs, U1 प्रणाली निकास latency (SEL) * 3
 *  - For bulk endpoपूर्णांकs, U1 SEL * 5
 *  - For पूर्णांकerrupt endpoपूर्णांकs:
 *    - Notअगरication EPs, U1 SEL * 3
 *    - Periodic EPs, max(105% of bInterval, U1 SEL * 2)
 *  - For isochronous endpoपूर्णांकs, max(105% of bInterval, U1 SEL * 2)
 */
अटल अचिन्हित दीर्घ दीर्घ xhci_calculate_पूर्णांकel_u1_समयout(
		काष्ठा usb_device *udev,
		काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित दीर्घ दीर्घ समयout_ns;
	पूर्णांक ep_type;
	पूर्णांक पूर्णांकr_type;

	ep_type = usb_endpoपूर्णांक_type(desc);
	चयन (ep_type) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		समयout_ns = udev->u1_params.sel * 3;
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		समयout_ns = udev->u1_params.sel * 5;
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		पूर्णांकr_type = usb_endpoपूर्णांक_पूर्णांकerrupt_type(desc);
		अगर (पूर्णांकr_type == USB_ENDPOINT_INTR_NOTIFICATION) अणु
			समयout_ns = udev->u1_params.sel * 3;
			अवरोध;
		पूर्ण
		/* Otherwise the calculation is the same as isoc eps */
		fallthrough;
	हाल USB_ENDPOINT_XFER_ISOC:
		समयout_ns = xhci_service_पूर्णांकerval_to_ns(desc);
		समयout_ns = DIV_ROUND_UP_ULL(समयout_ns * 105, 100);
		अगर (समयout_ns < udev->u1_params.sel * 2)
			समयout_ns = udev->u1_params.sel * 2;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस समयout_ns;
पूर्ण

/* Returns the hub-encoded U1 समयout value. */
अटल u16 xhci_calculate_u1_समयout(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev,
		काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित दीर्घ दीर्घ समयout_ns;

	अगर (xhci->quirks & XHCI_INTEL_HOST)
		समयout_ns = xhci_calculate_पूर्णांकel_u1_समयout(udev, desc);
	अन्यथा
		समयout_ns = udev->u1_params.sel;

	/* Prevent U1 अगर service पूर्णांकerval is लघुer than U1 निकास latency */
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(desc) || usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
		अगर (xhci_service_पूर्णांकerval_to_ns(desc) <= समयout_ns) अणु
			dev_dbg(&udev->dev, "Disable U1, ESIT shorter than exit latency\n");
			वापस USB3_LPM_DISABLED;
		पूर्ण
	पूर्ण

	/* The U1 समयout is encoded in 1us पूर्णांकervals.
	 * Don't return a timeout of zero, because that's USB3_LPM_DISABLED.
	 */
	अगर (समयout_ns == USB3_LPM_DISABLED)
		समयout_ns = 1;
	अन्यथा
		समयout_ns = DIV_ROUND_UP_ULL(समयout_ns, 1000);

	/* If the necessary समयout value is bigger than what we can set in the
	 * USB 3.0 hub, we have to disable hub-initiated U1.
	 */
	अगर (समयout_ns <= USB3_LPM_U1_MAX_TIMEOUT)
		वापस समयout_ns;
	dev_dbg(&udev->dev, "Hub-initiated U1 disabled "
			"due to long timeout %llu ms\n", समयout_ns);
	वापस xhci_get_समयout_no_hub_lpm(udev, USB3_LPM_U1);
पूर्ण

/* The U2 समयout should be the maximum of:
 *  - 10 ms (to aव्योम the bandwidth impact on the scheduler)
 *  - largest bInterval of any active periodic endpoपूर्णांक (to aव्योम going
 *    पूर्णांकo lower घातer link states between पूर्णांकervals).
 *  - the U2 Exit Latency of the device
 */
अटल अचिन्हित दीर्घ दीर्घ xhci_calculate_पूर्णांकel_u2_समयout(
		काष्ठा usb_device *udev,
		काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित दीर्घ दीर्घ समयout_ns;
	अचिन्हित दीर्घ दीर्घ u2_del_ns;

	समयout_ns = 10 * 1000 * 1000;

	अगर ((usb_endpoपूर्णांक_xfer_पूर्णांक(desc) || usb_endpoपूर्णांक_xfer_isoc(desc)) &&
			(xhci_service_पूर्णांकerval_to_ns(desc) > समयout_ns))
		समयout_ns = xhci_service_पूर्णांकerval_to_ns(desc);

	u2_del_ns = le16_to_cpu(udev->bos->ss_cap->bU2DevExitLat) * 1000ULL;
	अगर (u2_del_ns > समयout_ns)
		समयout_ns = u2_del_ns;

	वापस समयout_ns;
पूर्ण

/* Returns the hub-encoded U2 समयout value. */
अटल u16 xhci_calculate_u2_समयout(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev,
		काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	अचिन्हित दीर्घ दीर्घ समयout_ns;

	अगर (xhci->quirks & XHCI_INTEL_HOST)
		समयout_ns = xhci_calculate_पूर्णांकel_u2_समयout(udev, desc);
	अन्यथा
		समयout_ns = udev->u2_params.sel;

	/* Prevent U2 अगर service पूर्णांकerval is लघुer than U2 निकास latency */
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(desc) || usb_endpoपूर्णांक_xfer_isoc(desc)) अणु
		अगर (xhci_service_पूर्णांकerval_to_ns(desc) <= समयout_ns) अणु
			dev_dbg(&udev->dev, "Disable U2, ESIT shorter than exit latency\n");
			वापस USB3_LPM_DISABLED;
		पूर्ण
	पूर्ण

	/* The U2 समयout is encoded in 256us पूर्णांकervals */
	समयout_ns = DIV_ROUND_UP_ULL(समयout_ns, 256 * 1000);
	/* If the necessary समयout value is bigger than what we can set in the
	 * USB 3.0 hub, we have to disable hub-initiated U2.
	 */
	अगर (समयout_ns <= USB3_LPM_U2_MAX_TIMEOUT)
		वापस समयout_ns;
	dev_dbg(&udev->dev, "Hub-initiated U2 disabled "
			"due to long timeout %llu ms\n", समयout_ns);
	वापस xhci_get_समयout_no_hub_lpm(udev, USB3_LPM_U2);
पूर्ण

अटल u16 xhci_call_host_update_समयout_क्रम_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev,
		काष्ठा usb_endpoपूर्णांक_descriptor *desc,
		क्रमागत usb3_link_state state,
		u16 *समयout)
अणु
	अगर (state == USB3_LPM_U1)
		वापस xhci_calculate_u1_समयout(xhci, udev, desc);
	अन्यथा अगर (state == USB3_LPM_U2)
		वापस xhci_calculate_u2_समयout(xhci, udev, desc);

	वापस USB3_LPM_DISABLED;
पूर्ण

अटल पूर्णांक xhci_update_समयout_क्रम_endpoपूर्णांक(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev,
		काष्ठा usb_endpoपूर्णांक_descriptor *desc,
		क्रमागत usb3_link_state state,
		u16 *समयout)
अणु
	u16 alt_समयout;

	alt_समयout = xhci_call_host_update_समयout_क्रम_endpoपूर्णांक(xhci, udev,
		desc, state, समयout);

	/* If we found we can't enable hub-initiated LPM, and
	 * the U1 or U2 निकास latency was too high to allow
	 * device-initiated LPM as well, then we will disable LPM
	 * क्रम this device, so stop searching any further.
	 */
	अगर (alt_समयout == USB3_LPM_DISABLED) अणु
		*समयout = alt_समयout;
		वापस -E2BIG;
	पूर्ण
	अगर (alt_समयout > *समयout)
		*समयout = alt_समयout;
	वापस 0;
पूर्ण

अटल पूर्णांक xhci_update_समयout_क्रम_पूर्णांकerface(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev,
		काष्ठा usb_host_पूर्णांकerface *alt,
		क्रमागत usb3_link_state state,
		u16 *समयout)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < alt->desc.bNumEndpoपूर्णांकs; j++) अणु
		अगर (xhci_update_समयout_क्रम_endpoपूर्णांक(xhci, udev,
					&alt->endpoपूर्णांक[j].desc, state, समयout))
			वापस -E2BIG;
		जारी;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xhci_check_पूर्णांकel_tier_policy(काष्ठा usb_device *udev,
		क्रमागत usb3_link_state state)
अणु
	काष्ठा usb_device *parent;
	अचिन्हित पूर्णांक num_hubs;

	अगर (state == USB3_LPM_U2)
		वापस 0;

	/* Don't enable U1 अगर the device is on a 2nd tier hub or lower. */
	क्रम (parent = udev->parent, num_hubs = 0; parent->parent;
			parent = parent->parent)
		num_hubs++;

	अगर (num_hubs < 2)
		वापस 0;

	dev_dbg(&udev->dev, "Disabling U1 link state for device"
			" below second-tier hub.\n");
	dev_dbg(&udev->dev, "Plug device into first-tier hub "
			"to decrease power consumption.\n");
	वापस -E2BIG;
पूर्ण

अटल पूर्णांक xhci_check_tier_policy(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev,
		क्रमागत usb3_link_state state)
अणु
	अगर (xhci->quirks & XHCI_INTEL_HOST)
		वापस xhci_check_पूर्णांकel_tier_policy(udev, state);
	अन्यथा
		वापस 0;
पूर्ण

/* Returns the U1 or U2 समयout that should be enabled.
 * If the tier check or समयout setting functions वापस with a non-zero निकास
 * code, that means the समयout value has been finalized and we shouldn't look
 * at any more endpoपूर्णांकs.
 */
अटल u16 xhci_calculate_lpm_समयout(काष्ठा usb_hcd *hcd,
			काष्ठा usb_device *udev, क्रमागत usb3_link_state state)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा usb_host_config *config;
	अक्षर *state_name;
	पूर्णांक i;
	u16 समयout = USB3_LPM_DISABLED;

	अगर (state == USB3_LPM_U1)
		state_name = "U1";
	अन्यथा अगर (state == USB3_LPM_U2)
		state_name = "U2";
	अन्यथा अणु
		dev_warn(&udev->dev, "Can't enable unknown link state %i\n",
				state);
		वापस समयout;
	पूर्ण

	अगर (xhci_check_tier_policy(xhci, udev, state) < 0)
		वापस समयout;

	/* Gather some inक्रमmation about the currently installed configuration
	 * and alternate पूर्णांकerface settings.
	 */
	अगर (xhci_update_समयout_क्रम_endpoपूर्णांक(xhci, udev, &udev->ep0.desc,
			state, &समयout))
		वापस समयout;

	config = udev->actconfig;
	अगर (!config)
		वापस समयout;

	क्रम (i = 0; i < config->desc.bNumInterfaces; i++) अणु
		काष्ठा usb_driver *driver;
		काष्ठा usb_पूर्णांकerface *पूर्णांकf = config->पूर्णांकerface[i];

		अगर (!पूर्णांकf)
			जारी;

		/* Check अगर any currently bound drivers want hub-initiated LPM
		 * disabled.
		 */
		अगर (पूर्णांकf->dev.driver) अणु
			driver = to_usb_driver(पूर्णांकf->dev.driver);
			अगर (driver && driver->disable_hub_initiated_lpm) अणु
				dev_dbg(&udev->dev, "Hub-initiated %s disabled at request of driver %s\n",
					state_name, driver->name);
				समयout = xhci_get_समयout_no_hub_lpm(udev,
								      state);
				अगर (समयout == USB3_LPM_DISABLED)
					वापस समयout;
			पूर्ण
		पूर्ण

		/* Not sure how this could happen... */
		अगर (!पूर्णांकf->cur_altsetting)
			जारी;

		अगर (xhci_update_समयout_क्रम_पूर्णांकerface(xhci, udev,
					पूर्णांकf->cur_altsetting,
					state, &समयout))
			वापस समयout;
	पूर्ण
	वापस समयout;
पूर्ण

अटल पूर्णांक calculate_max_निकास_latency(काष्ठा usb_device *udev,
		क्रमागत usb3_link_state state_changed,
		u16 hub_encoded_समयout)
अणु
	अचिन्हित दीर्घ दीर्घ u1_mel_us = 0;
	अचिन्हित दीर्घ दीर्घ u2_mel_us = 0;
	अचिन्हित दीर्घ दीर्घ mel_us = 0;
	bool disabling_u1;
	bool disabling_u2;
	bool enabling_u1;
	bool enabling_u2;

	disabling_u1 = (state_changed == USB3_LPM_U1 &&
			hub_encoded_समयout == USB3_LPM_DISABLED);
	disabling_u2 = (state_changed == USB3_LPM_U2 &&
			hub_encoded_समयout == USB3_LPM_DISABLED);

	enabling_u1 = (state_changed == USB3_LPM_U1 &&
			hub_encoded_समयout != USB3_LPM_DISABLED);
	enabling_u2 = (state_changed == USB3_LPM_U2 &&
			hub_encoded_समयout != USB3_LPM_DISABLED);

	/* If U1 was alपढ़ोy enabled and we're not disabling it,
	 * or we're going to enable U1, account क्रम the U1 max निकास latency.
	 */
	अगर ((udev->u1_params.समयout != USB3_LPM_DISABLED && !disabling_u1) ||
			enabling_u1)
		u1_mel_us = DIV_ROUND_UP(udev->u1_params.mel, 1000);
	अगर ((udev->u2_params.समयout != USB3_LPM_DISABLED && !disabling_u2) ||
			enabling_u2)
		u2_mel_us = DIV_ROUND_UP(udev->u2_params.mel, 1000);

	अगर (u1_mel_us > u2_mel_us)
		mel_us = u1_mel_us;
	अन्यथा
		mel_us = u2_mel_us;
	/* xHCI host controller max निकास latency field is only 16 bits wide. */
	अगर (mel_us > MAX_EXIT) अणु
		dev_warn(&udev->dev, "Link PM max exit latency of %lluus "
				"is too big.\n", mel_us);
		वापस -E2BIG;
	पूर्ण
	वापस mel_us;
पूर्ण

/* Returns the USB3 hub-encoded value क्रम the U1/U2 समयout. */
अटल पूर्णांक xhci_enable_usb3_lpm_समयout(काष्ठा usb_hcd *hcd,
			काष्ठा usb_device *udev, क्रमागत usb3_link_state state)
अणु
	काष्ठा xhci_hcd	*xhci;
	u16 hub_encoded_समयout;
	पूर्णांक mel;
	पूर्णांक ret;

	xhci = hcd_to_xhci(hcd);
	/* The LPM समयout values are pretty host-controller specअगरic, so करोn't
	 * enable hub-initiated समयouts unless the venकरोr has provided
	 * inक्रमmation about their समयout algorithm.
	 */
	अगर (!xhci || !(xhci->quirks & XHCI_LPM_SUPPORT) ||
			!xhci->devs[udev->slot_id])
		वापस USB3_LPM_DISABLED;

	hub_encoded_समयout = xhci_calculate_lpm_समयout(hcd, udev, state);
	mel = calculate_max_निकास_latency(udev, state, hub_encoded_समयout);
	अगर (mel < 0) अणु
		/* Max Exit Latency is too big, disable LPM. */
		hub_encoded_समयout = USB3_LPM_DISABLED;
		mel = 0;
	पूर्ण

	ret = xhci_change_max_निकास_latency(xhci, udev, mel);
	अगर (ret)
		वापस ret;
	वापस hub_encoded_समयout;
पूर्ण

अटल पूर्णांक xhci_disable_usb3_lpm_समयout(काष्ठा usb_hcd *hcd,
			काष्ठा usb_device *udev, क्रमागत usb3_link_state state)
अणु
	काष्ठा xhci_hcd	*xhci;
	u16 mel;

	xhci = hcd_to_xhci(hcd);
	अगर (!xhci || !(xhci->quirks & XHCI_LPM_SUPPORT) ||
			!xhci->devs[udev->slot_id])
		वापस 0;

	mel = calculate_max_निकास_latency(udev, state, USB3_LPM_DISABLED);
	वापस xhci_change_max_निकास_latency(xhci, udev, mel);
पूर्ण
#अन्यथा /* CONFIG_PM */

अटल पूर्णांक xhci_set_usb2_hardware_lpm(काष्ठा usb_hcd *hcd,
				काष्ठा usb_device *udev, पूर्णांक enable)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक xhci_update_device(काष्ठा usb_hcd *hcd, काष्ठा usb_device *udev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक xhci_enable_usb3_lpm_समयout(काष्ठा usb_hcd *hcd,
			काष्ठा usb_device *udev, क्रमागत usb3_link_state state)
अणु
	वापस USB3_LPM_DISABLED;
पूर्ण

अटल पूर्णांक xhci_disable_usb3_lpm_समयout(काष्ठा usb_hcd *hcd,
			काष्ठा usb_device *udev, क्रमागत usb3_link_state state)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

/* Once a hub descriptor is fetched क्रम a device, we need to update the xHC's
 * पूर्णांकernal data काष्ठाures क्रम the device.
 */
अटल पूर्णांक xhci_update_hub_device(काष्ठा usb_hcd *hcd, काष्ठा usb_device *hdev,
			काष्ठा usb_tt *tt, gfp_t mem_flags)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	काष्ठा xhci_virt_device *vdev;
	काष्ठा xhci_command *config_cmd;
	काष्ठा xhci_input_control_ctx *ctrl_ctx;
	काष्ठा xhci_slot_ctx *slot_ctx;
	अचिन्हित दीर्घ flags;
	अचिन्हित think_समय;
	पूर्णांक ret;

	/* Ignore root hubs */
	अगर (!hdev->parent)
		वापस 0;

	vdev = xhci->devs[hdev->slot_id];
	अगर (!vdev) अणु
		xhci_warn(xhci, "Cannot update hub desc for unknown device.\n");
		वापस -EINVAL;
	पूर्ण

	config_cmd = xhci_alloc_command_with_ctx(xhci, true, mem_flags);
	अगर (!config_cmd)
		वापस -ENOMEM;

	ctrl_ctx = xhci_get_input_control_ctx(config_cmd->in_ctx);
	अगर (!ctrl_ctx) अणु
		xhci_warn(xhci, "%s: Could not get input context, bad type.\n",
				__func__);
		xhci_मुक्त_command(xhci, config_cmd);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&xhci->lock, flags);
	अगर (hdev->speed == USB_SPEED_HIGH &&
			xhci_alloc_tt_info(xhci, vdev, hdev, tt, GFP_ATOMIC)) अणु
		xhci_dbg(xhci, "Could not allocate xHCI TT structure.\n");
		xhci_मुक्त_command(xhci, config_cmd);
		spin_unlock_irqrestore(&xhci->lock, flags);
		वापस -ENOMEM;
	पूर्ण

	xhci_slot_copy(xhci, config_cmd->in_ctx, vdev->out_ctx);
	ctrl_ctx->add_flags |= cpu_to_le32(SLOT_FLAG);
	slot_ctx = xhci_get_slot_ctx(xhci, config_cmd->in_ctx);
	slot_ctx->dev_info |= cpu_to_le32(DEV_HUB);
	/*
	 * refer to section 6.2.2: MTT should be 0 क्रम full speed hub,
	 * but it may be alपढ़ोy set to 1 when setup an xHCI भव
	 * device, so clear it anyway.
	 */
	अगर (tt->multi)
		slot_ctx->dev_info |= cpu_to_le32(DEV_MTT);
	अन्यथा अगर (hdev->speed == USB_SPEED_FULL)
		slot_ctx->dev_info &= cpu_to_le32(~DEV_MTT);

	अगर (xhci->hci_version > 0x95) अणु
		xhci_dbg(xhci, "xHCI version %x needs hub "
				"TT think time and number of ports\n",
				(अचिन्हित पूर्णांक) xhci->hci_version);
		slot_ctx->dev_info2 |= cpu_to_le32(XHCI_MAX_PORTS(hdev->maxchild));
		/* Set TT think समय - convert from ns to FS bit बार.
		 * 0 = 8 FS bit बार, 1 = 16 FS bit बार,
		 * 2 = 24 FS bit बार, 3 = 32 FS bit बार.
		 *
		 * xHCI 1.0: this field shall be 0 अगर the device is not a
		 * High-spped hub.
		 */
		think_समय = tt->think_समय;
		अगर (think_समय != 0)
			think_समय = (think_समय / 666) - 1;
		अगर (xhci->hci_version < 0x100 || hdev->speed == USB_SPEED_HIGH)
			slot_ctx->tt_info |=
				cpu_to_le32(TT_THINK_TIME(think_समय));
	पूर्ण अन्यथा अणु
		xhci_dbg(xhci, "xHCI version %x doesn't need hub "
				"TT think time or number of ports\n",
				(अचिन्हित पूर्णांक) xhci->hci_version);
	पूर्ण
	slot_ctx->dev_state = 0;
	spin_unlock_irqrestore(&xhci->lock, flags);

	xhci_dbg(xhci, "Set up %s for hub device.\n",
			(xhci->hci_version > 0x95) ?
			"configure endpoint" : "evaluate context");

	/* Issue and रुको क्रम the configure endpoपूर्णांक or
	 * evaluate context command.
	 */
	अगर (xhci->hci_version > 0x95)
		ret = xhci_configure_endpoपूर्णांक(xhci, hdev, config_cmd,
				false, false);
	अन्यथा
		ret = xhci_configure_endpoपूर्णांक(xhci, hdev, config_cmd,
				true, false);

	xhci_मुक्त_command(xhci, config_cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक xhci_get_frame(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	/* EHCI mods by the periodic size.  Why? */
	वापस पढ़ोl(&xhci->run_regs->microframe_index) >> 3;
पूर्ण

पूर्णांक xhci_gen_setup(काष्ठा usb_hcd *hcd, xhci_get_quirks_t get_quirks)
अणु
	काष्ठा xhci_hcd		*xhci;
	/*
	 * TODO: Check with DWC3 clients क्रम sysdev according to
	 * quirks
	 */
	काष्ठा device		*dev = hcd->self.sysdev;
	अचिन्हित पूर्णांक		minor_rev;
	पूर्णांक			retval;

	/* Accept arbitrarily दीर्घ scatter-gather lists */
	hcd->self.sg_tablesize = ~0;

	/* support to build packet from discontinuous buffers */
	hcd->self.no_sg_स्थिरraपूर्णांक = 1;

	/* XHCI controllers करोn't stop the ep queue on लघु packets :| */
	hcd->self.no_stop_on_लघु = 1;

	xhci = hcd_to_xhci(hcd);

	अगर (usb_hcd_is_primary_hcd(hcd)) अणु
		xhci->मुख्य_hcd = hcd;
		xhci->usb2_rhub.hcd = hcd;
		/* Mark the first roothub as being USB 2.0.
		 * The xHCI driver will रेजिस्टर the USB 3.0 roothub.
		 */
		hcd->speed = HCD_USB2;
		hcd->self.root_hub->speed = USB_SPEED_HIGH;
		/*
		 * USB 2.0 roothub under xHCI has an पूर्णांकegrated TT,
		 * (rate matching hub) as opposed to having an OHCI/UHCI
		 * companion controller.
		 */
		hcd->has_tt = 1;
	पूर्ण अन्यथा अणु
		/*
		 * Early xHCI 1.1 spec did not mention USB 3.1 capable hosts
		 * should वापस 0x31 क्रम sbrn, or that the minor revision
		 * is a two digit BCD containig minor and sub-minor numbers.
		 * This was later clarअगरied in xHCI 1.2.
		 *
		 * Some USB 3.1 capable hosts thereक्रमe have sbrn 0x30, and
		 * minor revision set to 0x1 instead of 0x10.
		 */
		अगर (xhci->usb3_rhub.min_rev == 0x1)
			minor_rev = 1;
		अन्यथा
			minor_rev = xhci->usb3_rhub.min_rev / 0x10;

		चयन (minor_rev) अणु
		हाल 2:
			hcd->speed = HCD_USB32;
			hcd->self.root_hub->speed = USB_SPEED_SUPER_PLUS;
			hcd->self.root_hub->rx_lanes = 2;
			hcd->self.root_hub->tx_lanes = 2;
			hcd->self.root_hub->ssp_rate = USB_SSP_GEN_2x2;
			अवरोध;
		हाल 1:
			hcd->speed = HCD_USB31;
			hcd->self.root_hub->speed = USB_SPEED_SUPER_PLUS;
			hcd->self.root_hub->ssp_rate = USB_SSP_GEN_2x1;
			अवरोध;
		पूर्ण
		xhci_info(xhci, "Host supports USB 3.%x %sSuperSpeed\n",
			  minor_rev,
			  minor_rev ? "Enhanced " : "");

		xhci->usb3_rhub.hcd = hcd;
		/* xHCI निजी poपूर्णांकer was set in xhci_pci_probe क्रम the second
		 * रेजिस्टरed roothub.
		 */
		वापस 0;
	पूर्ण

	mutex_init(&xhci->mutex);
	xhci->cap_regs = hcd->regs;
	xhci->op_regs = hcd->regs +
		HC_LENGTH(पढ़ोl(&xhci->cap_regs->hc_capbase));
	xhci->run_regs = hcd->regs +
		(पढ़ोl(&xhci->cap_regs->run_regs_off) & RTSOFF_MASK);
	/* Cache पढ़ो-only capability रेजिस्टरs */
	xhci->hcs_params1 = पढ़ोl(&xhci->cap_regs->hcs_params1);
	xhci->hcs_params2 = पढ़ोl(&xhci->cap_regs->hcs_params2);
	xhci->hcs_params3 = पढ़ोl(&xhci->cap_regs->hcs_params3);
	xhci->hcc_params = पढ़ोl(&xhci->cap_regs->hc_capbase);
	xhci->hci_version = HC_VERSION(xhci->hcc_params);
	xhci->hcc_params = पढ़ोl(&xhci->cap_regs->hcc_params);
	अगर (xhci->hci_version > 0x100)
		xhci->hcc_params2 = पढ़ोl(&xhci->cap_regs->hcc_params2);

	xhci->quirks |= quirks;

	get_quirks(dev, xhci);

	/* In xhci controllers which follow xhci 1.0 spec gives a spurious
	 * success event after a लघु transfer. This quirk will ignore such
	 * spurious event.
	 */
	अगर (xhci->hci_version > 0x96)
		xhci->quirks |= XHCI_SPURIOUS_SUCCESS;

	/* Make sure the HC is halted. */
	retval = xhci_halt(xhci);
	अगर (retval)
		वापस retval;

	xhci_zero_64b_regs(xhci);

	xhci_dbg(xhci, "Resetting HCD\n");
	/* Reset the पूर्णांकernal HC memory state and रेजिस्टरs. */
	retval = xhci_reset(xhci);
	अगर (retval)
		वापस retval;
	xhci_dbg(xhci, "Reset complete\n");

	/*
	 * On some xHCI controllers (e.g. R-Car SoCs), the AC64 bit (bit 0)
	 * of HCCPARAMS1 is set to 1. However, the xHCs करोn't support 64-bit
	 * address memory poपूर्णांकers actually. So, this driver clears the AC64
	 * bit of xhci->hcc_params to call dma_set_coherent_mask(dev,
	 * DMA_BIT_MASK(32)) in this xhci_gen_setup().
	 */
	अगर (xhci->quirks & XHCI_NO_64BIT_SUPPORT)
		xhci->hcc_params &= ~BIT(0);

	/* Set dma_mask and coherent_dma_mask to 64-bits,
	 * अगर xHC supports 64-bit addressing */
	अगर (HCC_64BIT_ADDR(xhci->hcc_params) &&
			!dma_set_mask(dev, DMA_BIT_MASK(64))) अणु
		xhci_dbg(xhci, "Enabling 64-bit DMA addresses.\n");
		dma_set_coherent_mask(dev, DMA_BIT_MASK(64));
	पूर्ण अन्यथा अणु
		/*
		 * This is to aव्योम error in हालs where a 32-bit USB
		 * controller is used on a 64-bit capable प्रणाली.
		 */
		retval = dma_set_mask(dev, DMA_BIT_MASK(32));
		अगर (retval)
			वापस retval;
		xhci_dbg(xhci, "Enabling 32-bit DMA addresses.\n");
		dma_set_coherent_mask(dev, DMA_BIT_MASK(32));
	पूर्ण

	xhci_dbg(xhci, "Calling HCD init\n");
	/* Initialize HCD and host controller data काष्ठाures. */
	retval = xhci_init(hcd);
	अगर (retval)
		वापस retval;
	xhci_dbg(xhci, "Called HCD init\n");

	xhci_info(xhci, "hcc params 0x%08x hci version 0x%x quirks 0x%016llx\n",
		  xhci->hcc_params, xhci->hci_version, xhci->quirks);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xhci_gen_setup);

अटल व्योम xhci_clear_tt_buffer_complete(काष्ठा usb_hcd *hcd,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	काष्ठा xhci_hcd *xhci;
	काष्ठा usb_device *udev;
	अचिन्हित पूर्णांक slot_id;
	अचिन्हित पूर्णांक ep_index;
	अचिन्हित दीर्घ flags;

	xhci = hcd_to_xhci(hcd);

	spin_lock_irqsave(&xhci->lock, flags);
	udev = (काष्ठा usb_device *)ep->hcpriv;
	slot_id = udev->slot_id;
	ep_index = xhci_get_endpoपूर्णांक_index(&ep->desc);

	xhci->devs[slot_id]->eps[ep_index].ep_state &= ~EP_CLEARING_TT;
	xhci_ring_करोorbell_क्रम_active_rings(xhci, slot_id, ep_index);
	spin_unlock_irqrestore(&xhci->lock, flags);
पूर्ण

अटल स्थिर काष्ठा hc_driver xhci_hc_driver = अणु
	.description =		"xhci-hcd",
	.product_desc =		"xHCI Host Controller",
	.hcd_priv_size =	माप(काष्ठा xhci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			xhci_irq,
	.flags =		HCD_MEMORY | HCD_DMA | HCD_USB3 | HCD_SHARED |
				HCD_BH,

	/*
	 * basic lअगरecycle operations
	 */
	.reset =		शून्य, /* set in xhci_init_driver() */
	.start =		xhci_run,
	.stop =			xhci_stop,
	.shutकरोwn =		xhci_shutकरोwn,

	/*
	 * managing i/o requests and associated device resources
	 */
	.map_urb_क्रम_dma =      xhci_map_urb_क्रम_dma,
	.unmap_urb_क्रम_dma =    xhci_unmap_urb_क्रम_dma,
	.urb_enqueue =		xhci_urb_enqueue,
	.urb_dequeue =		xhci_urb_dequeue,
	.alloc_dev =		xhci_alloc_dev,
	.मुक्त_dev =		xhci_मुक्त_dev,
	.alloc_streams =	xhci_alloc_streams,
	.मुक्त_streams =		xhci_मुक्त_streams,
	.add_endpoपूर्णांक =		xhci_add_endpoपूर्णांक,
	.drop_endpoपूर्णांक =	xhci_drop_endpoपूर्णांक,
	.endpoपूर्णांक_disable =	xhci_endpoपूर्णांक_disable,
	.endpoपूर्णांक_reset =	xhci_endpoपूर्णांक_reset,
	.check_bandwidth =	xhci_check_bandwidth,
	.reset_bandwidth =	xhci_reset_bandwidth,
	.address_device =	xhci_address_device,
	.enable_device =	xhci_enable_device,
	.update_hub_device =	xhci_update_hub_device,
	.reset_device =		xhci_discover_or_reset_device,

	/*
	 * scheduling support
	 */
	.get_frame_number =	xhci_get_frame,

	/*
	 * root hub support
	 */
	.hub_control =		xhci_hub_control,
	.hub_status_data =	xhci_hub_status_data,
	.bus_suspend =		xhci_bus_suspend,
	.bus_resume =		xhci_bus_resume,
	.get_resuming_ports =	xhci_get_resuming_ports,

	/*
	 * call back when device connected and addressed
	 */
	.update_device =        xhci_update_device,
	.set_usb2_hw_lpm =	xhci_set_usb2_hardware_lpm,
	.enable_usb3_lpm_समयout =	xhci_enable_usb3_lpm_समयout,
	.disable_usb3_lpm_समयout =	xhci_disable_usb3_lpm_समयout,
	.find_raw_port_number =	xhci_find_raw_port_number,
	.clear_tt_buffer_complete = xhci_clear_tt_buffer_complete,
पूर्ण;

व्योम xhci_init_driver(काष्ठा hc_driver *drv,
		      स्थिर काष्ठा xhci_driver_overrides *over)
अणु
	BUG_ON(!over);

	/* Copy the generic table to drv then apply the overrides */
	*drv = xhci_hc_driver;

	अगर (over) अणु
		drv->hcd_priv_size += over->extra_priv_size;
		अगर (over->reset)
			drv->reset = over->reset;
		अगर (over->start)
			drv->start = over->start;
		अगर (over->add_endpoपूर्णांक)
			drv->add_endpoपूर्णांक = over->add_endpoपूर्णांक;
		अगर (over->drop_endpoपूर्णांक)
			drv->drop_endpoपूर्णांक = over->drop_endpoपूर्णांक;
		अगर (over->check_bandwidth)
			drv->check_bandwidth = over->check_bandwidth;
		अगर (over->reset_bandwidth)
			drv->reset_bandwidth = over->reset_bandwidth;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xhci_init_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");

अटल पूर्णांक __init xhci_hcd_init(व्योम)
अणु
	/*
	 * Check the compiler generated sizes of काष्ठाures that must be laid
	 * out in specअगरic ways क्रम hardware access.
	 */
	BUILD_BUG_ON(माप(काष्ठा xhci_करोorbell_array) != 256*32/8);
	BUILD_BUG_ON(माप(काष्ठा xhci_slot_ctx) != 8*32/8);
	BUILD_BUG_ON(माप(काष्ठा xhci_ep_ctx) != 8*32/8);
	/* xhci_device_control has eight fields, and also
	 * embeds one xhci_slot_ctx and 31 xhci_ep_ctx
	 */
	BUILD_BUG_ON(माप(काष्ठा xhci_stream_ctx) != 4*32/8);
	BUILD_BUG_ON(माप(जोड़ xhci_trb) != 4*32/8);
	BUILD_BUG_ON(माप(काष्ठा xhci_erst_entry) != 4*32/8);
	BUILD_BUG_ON(माप(काष्ठा xhci_cap_regs) != 8*32/8);
	BUILD_BUG_ON(माप(काष्ठा xhci_पूर्णांकr_reg) != 8*32/8);
	/* xhci_run_regs has eight fields and embeds 128 xhci_पूर्णांकr_regs */
	BUILD_BUG_ON(माप(काष्ठा xhci_run_regs) != (8+8*128)*32/8);

	अगर (usb_disabled())
		वापस -ENODEV;

	xhci_debugfs_create_root();

	वापस 0;
पूर्ण

/*
 * If an init function is provided, an निकास function must also be provided
 * to allow module unload.
 */
अटल व्योम __निकास xhci_hcd_fini(व्योम)
अणु
	xhci_debugfs_हटाओ_root();
पूर्ण

module_init(xhci_hcd_init);
module_निकास(xhci_hcd_fini);
