<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright IBM Corp. 2012
 *
 *  Author(s):
 *    Jan Glauber <jang@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "zpci"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/pci_debug.h>
#समावेश <यंत्र/pci_dma.h>
#समावेश <यंत्र/sclp.h>

#समावेश "pci_bus.h"

/* Content Code Description क्रम PCI Function Error */
काष्ठा zpci_ccdf_err अणु
	u32 reserved1;
	u32 fh;				/* function handle */
	u32 fid;			/* function id */
	u32 ett		:  4;		/* expected table type */
	u32 mvn		: 12;		/* MSI vector number */
	u32 dmaas	:  8;		/* DMA address space */
	u32		:  6;
	u32 q		:  1;		/* event qualअगरier */
	u32 rw		:  1;		/* पढ़ो/ग_लिखो */
	u64 faddr;			/* failing address */
	u32 reserved3;
	u16 reserved4;
	u16 pec;			/* PCI event code */
पूर्ण __packed;

/* Content Code Description क्रम PCI Function Availability */
काष्ठा zpci_ccdf_avail अणु
	u32 reserved1;
	u32 fh;				/* function handle */
	u32 fid;			/* function id */
	u32 reserved2;
	u32 reserved3;
	u32 reserved4;
	u32 reserved5;
	u16 reserved6;
	u16 pec;			/* PCI event code */
पूर्ण __packed;

अटल व्योम __zpci_event_error(काष्ठा zpci_ccdf_err *ccdf)
अणु
	काष्ठा zpci_dev *zdev = get_zdev_by_fid(ccdf->fid);
	काष्ठा pci_dev *pdev = शून्य;

	zpci_err("error CCDF:\n");
	zpci_err_hex(ccdf, माप(*ccdf));

	अगर (zdev)
		pdev = pci_get_slot(zdev->zbus->bus, zdev->devfn);

	pr_err("%s: Event 0x%x reports an error for PCI function 0x%x\n",
	       pdev ? pci_name(pdev) : "n/a", ccdf->pec, ccdf->fid);

	अगर (!pdev)
		वापस;

	pdev->error_state = pci_channel_io_perm_failure;
	pci_dev_put(pdev);
पूर्ण

व्योम zpci_event_error(व्योम *data)
अणु
	अगर (zpci_is_enabled())
		__zpci_event_error(data);
पूर्ण

अटल व्योम zpci_event_hard_deconfigured(काष्ठा zpci_dev *zdev, u32 fh)
अणु
	zdev->fh = fh;
	/* Give the driver a hपूर्णांक that the function is
	 * alपढ़ोy unusable.
	 */
	zpci_bus_हटाओ_device(zdev, true);
	/* Even though the device is alपढ़ोy gone we still
	 * need to मुक्त zPCI resources as part of the disable.
	 */
	zpci_disable_device(zdev);
	zdev->state = ZPCI_FN_STATE_STANDBY;
पूर्ण

अटल व्योम __zpci_event_availability(काष्ठा zpci_ccdf_avail *ccdf)
अणु
	काष्ठा zpci_dev *zdev = get_zdev_by_fid(ccdf->fid);
	क्रमागत zpci_state state;

	zpci_err("avail CCDF:\n");
	zpci_err_hex(ccdf, माप(*ccdf));

	चयन (ccdf->pec) अणु
	हाल 0x0301: /* Reserved|Standby -> Configured */
		अगर (!zdev) अणु
			zdev = zpci_create_device(ccdf->fid, ccdf->fh, ZPCI_FN_STATE_CONFIGURED);
			अगर (IS_ERR(zdev))
				अवरोध;
		पूर्ण अन्यथा अणु
			/* the configuration request may be stale */
			अगर (zdev->state != ZPCI_FN_STATE_STANDBY)
				अवरोध;
			zdev->state = ZPCI_FN_STATE_CONFIGURED;
		पूर्ण
		zpci_scan_configured_device(zdev, ccdf->fh);
		अवरोध;
	हाल 0x0302: /* Reserved -> Standby */
		अगर (!zdev)
			zpci_create_device(ccdf->fid, ccdf->fh, ZPCI_FN_STATE_STANDBY);
		अन्यथा
			zdev->fh = ccdf->fh;
		अवरोध;
	हाल 0x0303: /* Deconfiguration requested */
		अगर (zdev) अणु
			/* The event may have been queued beक्रमe we confirgured
			 * the device.
			 */
			अगर (zdev->state != ZPCI_FN_STATE_CONFIGURED)
				अवरोध;
			zdev->fh = ccdf->fh;
			zpci_deconfigure_device(zdev);
		पूर्ण
		अवरोध;
	हाल 0x0304: /* Configured -> Standby|Reserved */
		अगर (zdev) अणु
			/* The event may have been queued beक्रमe we confirgured
			 * the device.:
			 */
			अगर (zdev->state == ZPCI_FN_STATE_CONFIGURED)
				zpci_event_hard_deconfigured(zdev, ccdf->fh);
			/* The 0x0304 event may immediately reserve the device */
			अगर (!clp_get_state(zdev->fid, &state) &&
			    state == ZPCI_FN_STATE_RESERVED) अणु
				zpci_zdev_put(zdev);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 0x0306: /* 0x308 or 0x302 क्रम multiple devices */
		zpci_हटाओ_reserved_devices();
		clp_scan_pci_devices();
		अवरोध;
	हाल 0x0308: /* Standby -> Reserved */
		अगर (!zdev)
			अवरोध;
		zpci_zdev_put(zdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम zpci_event_availability(व्योम *data)
अणु
	अगर (zpci_is_enabled())
		__zpci_event_availability(data);
पूर्ण
