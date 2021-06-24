<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains code to reset and initialize USB host controllers.
 * Some of it includes work-arounds क्रम PCI hardware and BIOS quirks.
 * It may need to run early during booting -- beक्रमe USB would normally
 * initialize -- to ensure that Linux करोesn't use any legacy modes.
 *
 *  Copyright (c) 1999 Martin Mares <mj@ucw.cz>
 *  (and others)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/of.h>
#समावेश <linux/iopoll.h>

#समावेश "pci-quirks.h"
#समावेश "xhci-ext-caps.h"


#घोषणा UHCI_USBLEGSUP		0xc0		/* legacy support */
#घोषणा UHCI_USBCMD		0		/* command रेजिस्टर */
#घोषणा UHCI_USBINTR		4		/* पूर्णांकerrupt रेजिस्टर */
#घोषणा UHCI_USBLEGSUP_RWC	0x8f00		/* the R/WC bits */
#घोषणा UHCI_USBLEGSUP_RO	0x5040		/* R/O and reserved bits */
#घोषणा UHCI_USBCMD_RUN		0x0001		/* RUN/STOP bit */
#घोषणा UHCI_USBCMD_HCRESET	0x0002		/* Host Controller reset */
#घोषणा UHCI_USBCMD_EGSM	0x0008		/* Global Suspend Mode */
#घोषणा UHCI_USBCMD_CONFIGURE	0x0040		/* Config Flag */
#घोषणा UHCI_USBINTR_RESUME	0x0002		/* Resume पूर्णांकerrupt enable */

#घोषणा OHCI_CONTROL		0x04
#घोषणा OHCI_CMDSTATUS		0x08
#घोषणा OHCI_INTRSTATUS		0x0c
#घोषणा OHCI_INTRENABLE		0x10
#घोषणा OHCI_INTRDISABLE	0x14
#घोषणा OHCI_FMINTERVAL		0x34
#घोषणा OHCI_HCFS		(3 << 6)	/* hc functional state */
#घोषणा OHCI_HCR		(1 << 0)	/* host controller reset */
#घोषणा OHCI_OCR		(1 << 3)	/* ownership change request */
#घोषणा OHCI_CTRL_RWC		(1 << 9)	/* remote wakeup connected */
#घोषणा OHCI_CTRL_IR		(1 << 8)	/* पूर्णांकerrupt routing */
#घोषणा OHCI_INTR_OC		(1 << 30)	/* ownership change */

#घोषणा EHCI_HCC_PARAMS		0x08		/* extended capabilities */
#घोषणा EHCI_USBCMD		0		/* command रेजिस्टर */
#घोषणा EHCI_USBCMD_RUN		(1 << 0)	/* RUN/STOP bit */
#घोषणा EHCI_USBSTS		4		/* status रेजिस्टर */
#घोषणा EHCI_USBSTS_HALTED	(1 << 12)	/* HCHalted bit */
#घोषणा EHCI_USBINTR		8		/* पूर्णांकerrupt रेजिस्टर */
#घोषणा EHCI_CONFIGFLAG		0x40		/* configured flag रेजिस्टर */
#घोषणा EHCI_USBLEGSUP		0		/* legacy support रेजिस्टर */
#घोषणा EHCI_USBLEGSUP_BIOS	(1 << 16)	/* BIOS semaphore */
#घोषणा EHCI_USBLEGSUP_OS	(1 << 24)	/* OS semaphore */
#घोषणा EHCI_USBLEGCTLSTS	4		/* legacy control/status */
#घोषणा EHCI_USBLEGCTLSTS_SOOE	(1 << 13)	/* SMI on ownership change */

/* AMD quirk use */
#घोषणा	AB_REG_BAR_LOW		0xe0
#घोषणा	AB_REG_BAR_HIGH		0xe1
#घोषणा	AB_REG_BAR_SB700	0xf0
#घोषणा	AB_INDX(addr)		((addr) + 0x00)
#घोषणा	AB_DATA(addr)		((addr) + 0x04)
#घोषणा	AX_INDXC		0x30
#घोषणा	AX_DATAC		0x34

#घोषणा PT_ADDR_INDX		0xE8
#घोषणा PT_READ_INDX		0xE4
#घोषणा PT_SIG_1_ADDR		0xA520
#घोषणा PT_SIG_2_ADDR		0xA521
#घोषणा PT_SIG_3_ADDR		0xA522
#घोषणा PT_SIG_4_ADDR		0xA523
#घोषणा PT_SIG_1_DATA		0x78
#घोषणा PT_SIG_2_DATA		0x56
#घोषणा PT_SIG_3_DATA		0x34
#घोषणा PT_SIG_4_DATA		0x12
#घोषणा PT4_P1_REG		0xB521
#घोषणा PT4_P2_REG		0xB522
#घोषणा PT2_P1_REG		0xD520
#घोषणा PT2_P2_REG		0xD521
#घोषणा PT1_P1_REG		0xD522
#घोषणा PT1_P2_REG		0xD523

#घोषणा	NB_PCIE_INDX_ADDR	0xe0
#घोषणा	NB_PCIE_INDX_DATA	0xe4
#घोषणा	PCIE_P_CNTL		0x10040
#घोषणा	BIF_NB			0x10002
#घोषणा	NB_PIF0_PWRDOWN_0	0x01100012
#घोषणा	NB_PIF0_PWRDOWN_1	0x01100013

#घोषणा USB_INTEL_XUSB2PR      0xD0
#घोषणा USB_INTEL_USB2PRM      0xD4
#घोषणा USB_INTEL_USB3_PSSEN   0xD8
#घोषणा USB_INTEL_USB3PRM      0xDC

/* ASMEDIA quirk use */
#घोषणा ASMT_DATA_WRITE0_REG	0xF8
#घोषणा ASMT_DATA_WRITE1_REG	0xFC
#घोषणा ASMT_CONTROL_REG	0xE0
#घोषणा ASMT_CONTROL_WRITE_BIT	0x02
#घोषणा ASMT_WRITEREG_CMD	0x10423
#घोषणा ASMT_FLOWCTL_ADDR	0xFA30
#घोषणा ASMT_FLOWCTL_DATA	0xBA
#घोषणा ASMT_PSEUDO_DATA	0

/*
 * amd_chipset_gen values represent AMD dअगरferent chipset generations
 */
क्रमागत amd_chipset_gen अणु
	NOT_AMD_CHIPSET = 0,
	AMD_CHIPSET_SB600,
	AMD_CHIPSET_SB700,
	AMD_CHIPSET_SB800,
	AMD_CHIPSET_HUDSON2,
	AMD_CHIPSET_BOLTON,
	AMD_CHIPSET_YANGTZE,
	AMD_CHIPSET_TAISHAN,
	AMD_CHIPSET_UNKNOWN,
पूर्ण;

काष्ठा amd_chipset_type अणु
	क्रमागत amd_chipset_gen gen;
	u8 rev;
पूर्ण;

अटल काष्ठा amd_chipset_info अणु
	काष्ठा pci_dev	*nb_dev;
	काष्ठा pci_dev	*smbus_dev;
	पूर्णांक nb_type;
	काष्ठा amd_chipset_type sb_type;
	पूर्णांक isoc_reqs;
	पूर्णांक probe_count;
	bool need_pll_quirk;
पूर्ण amd_chipset;

अटल DEFINE_SPINLOCK(amd_lock);

/*
 * amd_chipset_sb_type_init - initialize amd chipset southbridge type
 *
 * AMD FCH/SB generation and revision is identअगरied by SMBus controller
 * venकरोr, device and revision IDs.
 *
 * Returns: 1 अगर it is an AMD chipset, 0 otherwise.
 */
अटल पूर्णांक amd_chipset_sb_type_init(काष्ठा amd_chipset_info *pinfo)
अणु
	u8 rev = 0;
	pinfo->sb_type.gen = AMD_CHIPSET_UNKNOWN;

	pinfo->smbus_dev = pci_get_device(PCI_VENDOR_ID_ATI,
			PCI_DEVICE_ID_ATI_SBX00_SMBUS, शून्य);
	अगर (pinfo->smbus_dev) अणु
		rev = pinfo->smbus_dev->revision;
		अगर (rev >= 0x10 && rev <= 0x1f)
			pinfo->sb_type.gen = AMD_CHIPSET_SB600;
		अन्यथा अगर (rev >= 0x30 && rev <= 0x3f)
			pinfo->sb_type.gen = AMD_CHIPSET_SB700;
		अन्यथा अगर (rev >= 0x40 && rev <= 0x4f)
			pinfo->sb_type.gen = AMD_CHIPSET_SB800;
	पूर्ण अन्यथा अणु
		pinfo->smbus_dev = pci_get_device(PCI_VENDOR_ID_AMD,
				PCI_DEVICE_ID_AMD_HUDSON2_SMBUS, शून्य);

		अगर (pinfo->smbus_dev) अणु
			rev = pinfo->smbus_dev->revision;
			अगर (rev >= 0x11 && rev <= 0x14)
				pinfo->sb_type.gen = AMD_CHIPSET_HUDSON2;
			अन्यथा अगर (rev >= 0x15 && rev <= 0x18)
				pinfo->sb_type.gen = AMD_CHIPSET_BOLTON;
			अन्यथा अगर (rev >= 0x39 && rev <= 0x3a)
				pinfo->sb_type.gen = AMD_CHIPSET_YANGTZE;
		पूर्ण अन्यथा अणु
			pinfo->smbus_dev = pci_get_device(PCI_VENDOR_ID_AMD,
							  0x145c, शून्य);
			अगर (pinfo->smbus_dev) अणु
				rev = pinfo->smbus_dev->revision;
				pinfo->sb_type.gen = AMD_CHIPSET_TAISHAN;
			पूर्ण अन्यथा अणु
				pinfo->sb_type.gen = NOT_AMD_CHIPSET;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	pinfo->sb_type.rev = rev;
	वापस 1;
पूर्ण

व्योम sb800_prefetch(काष्ठा device *dev, पूर्णांक on)
अणु
	u16 misc;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	pci_पढ़ो_config_word(pdev, 0x50, &misc);
	अगर (on == 0)
		pci_ग_लिखो_config_word(pdev, 0x50, misc & 0xfcff);
	अन्यथा
		pci_ग_लिखो_config_word(pdev, 0x50, misc | 0x0300);
पूर्ण
EXPORT_SYMBOL_GPL(sb800_prefetch);

अटल व्योम usb_amd_find_chipset_info(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा amd_chipset_info info;
	info.need_pll_quirk = false;

	spin_lock_irqsave(&amd_lock, flags);

	/* probe only once */
	अगर (amd_chipset.probe_count > 0) अणु
		amd_chipset.probe_count++;
		spin_unlock_irqrestore(&amd_lock, flags);
		वापस;
	पूर्ण
	स_रखो(&info, 0, माप(info));
	spin_unlock_irqrestore(&amd_lock, flags);

	अगर (!amd_chipset_sb_type_init(&info)) अणु
		जाओ commit;
	पूर्ण

	चयन (info.sb_type.gen) अणु
	हाल AMD_CHIPSET_SB700:
		info.need_pll_quirk = info.sb_type.rev <= 0x3B;
		अवरोध;
	हाल AMD_CHIPSET_SB800:
	हाल AMD_CHIPSET_HUDSON2:
	हाल AMD_CHIPSET_BOLTON:
		info.need_pll_quirk = true;
		अवरोध;
	शेष:
		info.need_pll_quirk = false;
		अवरोध;
	पूर्ण

	अगर (!info.need_pll_quirk) अणु
		अगर (info.smbus_dev) अणु
			pci_dev_put(info.smbus_dev);
			info.smbus_dev = शून्य;
		पूर्ण
		जाओ commit;
	पूर्ण

	info.nb_dev = pci_get_device(PCI_VENDOR_ID_AMD, 0x9601, शून्य);
	अगर (info.nb_dev) अणु
		info.nb_type = 1;
	पूर्ण अन्यथा अणु
		info.nb_dev = pci_get_device(PCI_VENDOR_ID_AMD, 0x1510, शून्य);
		अगर (info.nb_dev) अणु
			info.nb_type = 2;
		पूर्ण अन्यथा अणु
			info.nb_dev = pci_get_device(PCI_VENDOR_ID_AMD,
						     0x9600, शून्य);
			अगर (info.nb_dev)
				info.nb_type = 3;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "QUIRK: Enable AMD PLL fix\n");

commit:

	spin_lock_irqsave(&amd_lock, flags);
	अगर (amd_chipset.probe_count > 0) अणु
		/* race - someone अन्यथा was faster - drop devices */

		/* Mark that we where here */
		amd_chipset.probe_count++;

		spin_unlock_irqrestore(&amd_lock, flags);

		pci_dev_put(info.nb_dev);
		pci_dev_put(info.smbus_dev);

	पूर्ण अन्यथा अणु
		/* no race - commit the result */
		info.probe_count++;
		amd_chipset = info;
		spin_unlock_irqrestore(&amd_lock, flags);
	पूर्ण
पूर्ण

पूर्णांक usb_hcd_amd_remote_wakeup_quirk(काष्ठा pci_dev *pdev)
अणु
	/* Make sure amd chipset type has alपढ़ोy been initialized */
	usb_amd_find_chipset_info();
	अगर (amd_chipset.sb_type.gen == AMD_CHIPSET_YANGTZE ||
	    amd_chipset.sb_type.gen == AMD_CHIPSET_TAISHAN) अणु
		dev_dbg(&pdev->dev, "QUIRK: Enable AMD remote wakeup fix\n");
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(usb_hcd_amd_remote_wakeup_quirk);

bool usb_amd_hang_symptom_quirk(व्योम)
अणु
	u8 rev;

	usb_amd_find_chipset_info();
	rev = amd_chipset.sb_type.rev;
	/* SB600 and old version of SB700 have hang symptom bug */
	वापस amd_chipset.sb_type.gen == AMD_CHIPSET_SB600 ||
			(amd_chipset.sb_type.gen == AMD_CHIPSET_SB700 &&
			 rev >= 0x3a && rev <= 0x3b);
पूर्ण
EXPORT_SYMBOL_GPL(usb_amd_hang_symptom_quirk);

bool usb_amd_prefetch_quirk(व्योम)
अणु
	usb_amd_find_chipset_info();
	/* SB800 needs pre-fetch fix */
	वापस amd_chipset.sb_type.gen == AMD_CHIPSET_SB800;
पूर्ण
EXPORT_SYMBOL_GPL(usb_amd_prefetch_quirk);

bool usb_amd_quirk_pll_check(व्योम)
अणु
	usb_amd_find_chipset_info();
	वापस amd_chipset.need_pll_quirk;
पूर्ण
EXPORT_SYMBOL_GPL(usb_amd_quirk_pll_check);

/*
 * The hardware normally enables the A-link घातer management feature, which
 * lets the प्रणाली lower the घातer consumption in idle states.
 *
 * This USB quirk prevents the link going पूर्णांकo that lower घातer state
 * during isochronous transfers.
 *
 * Without this quirk, isochronous stream on OHCI/EHCI/xHCI controllers of
 * some AMD platक्रमms may stutter or have अवरोधs occasionally.
 */
अटल व्योम usb_amd_quirk_pll(पूर्णांक disable)
अणु
	u32 addr, addr_low, addr_high, val;
	u32 bit = disable ? 0 : 1;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&amd_lock, flags);

	अगर (disable) अणु
		amd_chipset.isoc_reqs++;
		अगर (amd_chipset.isoc_reqs > 1) अणु
			spin_unlock_irqrestore(&amd_lock, flags);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		amd_chipset.isoc_reqs--;
		अगर (amd_chipset.isoc_reqs > 0) अणु
			spin_unlock_irqrestore(&amd_lock, flags);
			वापस;
		पूर्ण
	पूर्ण

	अगर (amd_chipset.sb_type.gen == AMD_CHIPSET_SB800 ||
			amd_chipset.sb_type.gen == AMD_CHIPSET_HUDSON2 ||
			amd_chipset.sb_type.gen == AMD_CHIPSET_BOLTON) अणु
		outb_p(AB_REG_BAR_LOW, 0xcd6);
		addr_low = inb_p(0xcd7);
		outb_p(AB_REG_BAR_HIGH, 0xcd6);
		addr_high = inb_p(0xcd7);
		addr = addr_high << 8 | addr_low;

		outl_p(0x30, AB_INDX(addr));
		outl_p(0x40, AB_DATA(addr));
		outl_p(0x34, AB_INDX(addr));
		val = inl_p(AB_DATA(addr));
	पूर्ण अन्यथा अगर (amd_chipset.sb_type.gen == AMD_CHIPSET_SB700 &&
			amd_chipset.sb_type.rev <= 0x3b) अणु
		pci_पढ़ो_config_dword(amd_chipset.smbus_dev,
					AB_REG_BAR_SB700, &addr);
		outl(AX_INDXC, AB_INDX(addr));
		outl(0x40, AB_DATA(addr));
		outl(AX_DATAC, AB_INDX(addr));
		val = inl(AB_DATA(addr));
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&amd_lock, flags);
		वापस;
	पूर्ण

	अगर (disable) अणु
		val &= ~0x08;
		val |= (1 << 4) | (1 << 9);
	पूर्ण अन्यथा अणु
		val |= 0x08;
		val &= ~((1 << 4) | (1 << 9));
	पूर्ण
	outl_p(val, AB_DATA(addr));

	अगर (!amd_chipset.nb_dev) अणु
		spin_unlock_irqrestore(&amd_lock, flags);
		वापस;
	पूर्ण

	अगर (amd_chipset.nb_type == 1 || amd_chipset.nb_type == 3) अणु
		addr = PCIE_P_CNTL;
		pci_ग_लिखो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_ADDR, addr);
		pci_पढ़ो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, &val);

		val &= ~(1 | (1 << 3) | (1 << 4) | (1 << 9) | (1 << 12));
		val |= bit | (bit << 3) | (bit << 12);
		val |= ((!bit) << 4) | ((!bit) << 9);
		pci_ग_लिखो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, val);

		addr = BIF_NB;
		pci_ग_लिखो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_ADDR, addr);
		pci_पढ़ो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, &val);
		val &= ~(1 << 8);
		val |= bit << 8;

		pci_ग_लिखो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, val);
	पूर्ण अन्यथा अगर (amd_chipset.nb_type == 2) अणु
		addr = NB_PIF0_PWRDOWN_0;
		pci_ग_लिखो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_ADDR, addr);
		pci_पढ़ो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, &val);
		अगर (disable)
			val &= ~(0x3f << 7);
		अन्यथा
			val |= 0x3f << 7;

		pci_ग_लिखो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, val);

		addr = NB_PIF0_PWRDOWN_1;
		pci_ग_लिखो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_ADDR, addr);
		pci_पढ़ो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, &val);
		अगर (disable)
			val &= ~(0x3f << 7);
		अन्यथा
			val |= 0x3f << 7;

		pci_ग_लिखो_config_dword(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, val);
	पूर्ण

	spin_unlock_irqrestore(&amd_lock, flags);
	वापस;
पूर्ण

व्योम usb_amd_quirk_pll_disable(व्योम)
अणु
	usb_amd_quirk_pll(1);
पूर्ण
EXPORT_SYMBOL_GPL(usb_amd_quirk_pll_disable);

अटल पूर्णांक usb_यंत्रedia_रुको_ग_लिखो(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ retry_count;
	अचिन्हित अक्षर value;

	क्रम (retry_count = 1000; retry_count > 0; --retry_count) अणु

		pci_पढ़ो_config_byte(pdev, ASMT_CONTROL_REG, &value);

		अगर (value == 0xff) अणु
			dev_err(&pdev->dev, "%s: check_ready ERROR", __func__);
			वापस -EIO;
		पूर्ण

		अगर ((value & ASMT_CONTROL_WRITE_BIT) == 0)
			वापस 0;

		udelay(50);
	पूर्ण

	dev_warn(&pdev->dev, "%s: check_write_ready timeout", __func__);
	वापस -ETIMEDOUT;
पूर्ण

व्योम usb_यंत्रedia_modअगरyflowcontrol(काष्ठा pci_dev *pdev)
अणु
	अगर (usb_यंत्रedia_रुको_ग_लिखो(pdev) != 0)
		वापस;

	/* send command and address to device */
	pci_ग_लिखो_config_dword(pdev, ASMT_DATA_WRITE0_REG, ASMT_WRITEREG_CMD);
	pci_ग_लिखो_config_dword(pdev, ASMT_DATA_WRITE1_REG, ASMT_FLOWCTL_ADDR);
	pci_ग_लिखो_config_byte(pdev, ASMT_CONTROL_REG, ASMT_CONTROL_WRITE_BIT);

	अगर (usb_यंत्रedia_रुको_ग_लिखो(pdev) != 0)
		वापस;

	/* send data to device */
	pci_ग_लिखो_config_dword(pdev, ASMT_DATA_WRITE0_REG, ASMT_FLOWCTL_DATA);
	pci_ग_लिखो_config_dword(pdev, ASMT_DATA_WRITE1_REG, ASMT_PSEUDO_DATA);
	pci_ग_लिखो_config_byte(pdev, ASMT_CONTROL_REG, ASMT_CONTROL_WRITE_BIT);
पूर्ण
EXPORT_SYMBOL_GPL(usb_यंत्रedia_modअगरyflowcontrol);

व्योम usb_amd_quirk_pll_enable(व्योम)
अणु
	usb_amd_quirk_pll(0);
पूर्ण
EXPORT_SYMBOL_GPL(usb_amd_quirk_pll_enable);

व्योम usb_amd_dev_put(व्योम)
अणु
	काष्ठा pci_dev *nb, *smbus;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&amd_lock, flags);

	amd_chipset.probe_count--;
	अगर (amd_chipset.probe_count > 0) अणु
		spin_unlock_irqrestore(&amd_lock, flags);
		वापस;
	पूर्ण

	/* save them to pci_dev_put outside of spinlock */
	nb    = amd_chipset.nb_dev;
	smbus = amd_chipset.smbus_dev;

	amd_chipset.nb_dev = शून्य;
	amd_chipset.smbus_dev = शून्य;
	amd_chipset.nb_type = 0;
	स_रखो(&amd_chipset.sb_type, 0, माप(amd_chipset.sb_type));
	amd_chipset.isoc_reqs = 0;
	amd_chipset.need_pll_quirk = false;

	spin_unlock_irqrestore(&amd_lock, flags);

	pci_dev_put(nb);
	pci_dev_put(smbus);
पूर्ण
EXPORT_SYMBOL_GPL(usb_amd_dev_put);

/*
 * Check अगर port is disabled in BIOS on AMD Promontory host.
 * BIOS Disabled ports may wake on connect/disconnect and need
 * driver workaround to keep them disabled.
 * Returns true अगर port is marked disabled.
 */
bool usb_amd_pt_check_port(काष्ठा device *device, पूर्णांक port)
अणु
	अचिन्हित अक्षर value, port_shअगरt;
	काष्ठा pci_dev *pdev;
	u16 reg;

	pdev = to_pci_dev(device);
	pci_ग_लिखो_config_word(pdev, PT_ADDR_INDX, PT_SIG_1_ADDR);

	pci_पढ़ो_config_byte(pdev, PT_READ_INDX, &value);
	अगर (value != PT_SIG_1_DATA)
		वापस false;

	pci_ग_लिखो_config_word(pdev, PT_ADDR_INDX, PT_SIG_2_ADDR);

	pci_पढ़ो_config_byte(pdev, PT_READ_INDX, &value);
	अगर (value != PT_SIG_2_DATA)
		वापस false;

	pci_ग_लिखो_config_word(pdev, PT_ADDR_INDX, PT_SIG_3_ADDR);

	pci_पढ़ो_config_byte(pdev, PT_READ_INDX, &value);
	अगर (value != PT_SIG_3_DATA)
		वापस false;

	pci_ग_लिखो_config_word(pdev, PT_ADDR_INDX, PT_SIG_4_ADDR);

	pci_पढ़ो_config_byte(pdev, PT_READ_INDX, &value);
	अगर (value != PT_SIG_4_DATA)
		वापस false;

	/* Check disabled port setting, अगर bit is set port is enabled */
	चयन (pdev->device) अणु
	हाल 0x43b9:
	हाल 0x43ba:
	/*
	 * device is AMD_PROMONTORYA_4(0x43b9) or PROMONTORYA_3(0x43ba)
	 * PT4_P1_REG bits[7..1] represents USB2.0 ports 6 to 0
	 * PT4_P2_REG bits[6..0] represents ports 13 to 7
	 */
		अगर (port > 6) अणु
			reg = PT4_P2_REG;
			port_shअगरt = port - 7;
		पूर्ण अन्यथा अणु
			reg = PT4_P1_REG;
			port_shअगरt = port + 1;
		पूर्ण
		अवरोध;
	हाल 0x43bb:
	/*
	 * device is AMD_PROMONTORYA_2(0x43bb)
	 * PT2_P1_REG bits[7..5] represents USB2.0 ports 2 to 0
	 * PT2_P2_REG bits[5..0] represents ports 9 to 3
	 */
		अगर (port > 2) अणु
			reg = PT2_P2_REG;
			port_shअगरt = port - 3;
		पूर्ण अन्यथा अणु
			reg = PT2_P1_REG;
			port_shअगरt = port + 5;
		पूर्ण
		अवरोध;
	हाल 0x43bc:
	/*
	 * device is AMD_PROMONTORYA_1(0x43bc)
	 * PT1_P1_REG[7..4] represents USB2.0 ports 3 to 0
	 * PT1_P2_REG[5..0] represents ports 9 to 4
	 */
		अगर (port > 3) अणु
			reg = PT1_P2_REG;
			port_shअगरt = port - 4;
		पूर्ण अन्यथा अणु
			reg = PT1_P1_REG;
			port_shअगरt = port + 4;
		पूर्ण
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	pci_ग_लिखो_config_word(pdev, PT_ADDR_INDX, reg);
	pci_पढ़ो_config_byte(pdev, PT_READ_INDX, &value);

	वापस !(value & BIT(port_shअगरt));
पूर्ण
EXPORT_SYMBOL_GPL(usb_amd_pt_check_port);

/*
 * Make sure the controller is completely inactive, unable to
 * generate पूर्णांकerrupts or करो DMA.
 */
व्योम uhci_reset_hc(काष्ठा pci_dev *pdev, अचिन्हित दीर्घ base)
अणु
	/* Turn off PIRQ enable and SMI enable.  (This also turns off the
	 * BIOS's USB Legacy Support.)  Turn off all the R/WC bits too.
	 */
	pci_ग_लिखो_config_word(pdev, UHCI_USBLEGSUP, UHCI_USBLEGSUP_RWC);

	/* Reset the HC - this will क्रमce us to get a
	 * new notअगरication of any alपढ़ोy connected
	 * ports due to the भव disconnect that it
	 * implies.
	 */
	outw(UHCI_USBCMD_HCRESET, base + UHCI_USBCMD);
	mb();
	udelay(5);
	अगर (inw(base + UHCI_USBCMD) & UHCI_USBCMD_HCRESET)
		dev_warn(&pdev->dev, "HCRESET not completed yet!\n");

	/* Just to be safe, disable पूर्णांकerrupt requests and
	 * make sure the controller is stopped.
	 */
	outw(0, base + UHCI_USBINTR);
	outw(0, base + UHCI_USBCMD);
पूर्ण
EXPORT_SYMBOL_GPL(uhci_reset_hc);

/*
 * Initialize a controller that was newly discovered or has just been
 * resumed.  In either हाल we can't be sure of its previous state.
 *
 * Returns: 1 अगर the controller was reset, 0 otherwise.
 */
पूर्णांक uhci_check_and_reset_hc(काष्ठा pci_dev *pdev, अचिन्हित दीर्घ base)
अणु
	u16 legsup;
	अचिन्हित पूर्णांक cmd, पूर्णांकr;

	/*
	 * When restarting a suspended controller, we expect all the
	 * settings to be the same as we left them:
	 *
	 *	PIRQ and SMI disabled, no R/W bits set in USBLEGSUP;
	 *	Controller is stopped and configured with EGSM set;
	 *	No पूर्णांकerrupts enabled except possibly Resume Detect.
	 *
	 * If any of these conditions are violated we करो a complete reset.
	 */
	pci_पढ़ो_config_word(pdev, UHCI_USBLEGSUP, &legsup);
	अगर (legsup & ~(UHCI_USBLEGSUP_RO | UHCI_USBLEGSUP_RWC)) अणु
		dev_dbg(&pdev->dev, "%s: legsup = 0x%04x\n",
				__func__, legsup);
		जाओ reset_needed;
	पूर्ण

	cmd = inw(base + UHCI_USBCMD);
	अगर ((cmd & UHCI_USBCMD_RUN) || !(cmd & UHCI_USBCMD_CONFIGURE) ||
			!(cmd & UHCI_USBCMD_EGSM)) अणु
		dev_dbg(&pdev->dev, "%s: cmd = 0x%04x\n",
				__func__, cmd);
		जाओ reset_needed;
	पूर्ण

	पूर्णांकr = inw(base + UHCI_USBINTR);
	अगर (पूर्णांकr & (~UHCI_USBINTR_RESUME)) अणु
		dev_dbg(&pdev->dev, "%s: intr = 0x%04x\n",
				__func__, पूर्णांकr);
		जाओ reset_needed;
	पूर्ण
	वापस 0;

reset_needed:
	dev_dbg(&pdev->dev, "Performing full reset\n");
	uhci_reset_hc(pdev, base);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(uhci_check_and_reset_hc);

अटल अंतरभूत पूर्णांक io_type_enabled(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक mask)
अणु
	u16 cmd;
	वापस !pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd) && (cmd & mask);
पूर्ण

#घोषणा pio_enabled(dev) io_type_enabled(dev, PCI_COMMAND_IO)
#घोषणा mmio_enabled(dev) io_type_enabled(dev, PCI_COMMAND_MEMORY)

अटल व्योम quirk_usb_hanकरोff_uhci(काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ base = 0;
	पूर्णांक i;

	अगर (!pio_enabled(pdev))
		वापस;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++)
		अगर ((pci_resource_flags(pdev, i) & IORESOURCE_IO)) अणु
			base = pci_resource_start(pdev, i);
			अवरोध;
		पूर्ण

	अगर (base)
		uhci_check_and_reset_hc(pdev, base);
पूर्ण

अटल पूर्णांक mmio_resource_enabled(काष्ठा pci_dev *pdev, पूर्णांक idx)
अणु
	वापस pci_resource_start(pdev, idx) && mmio_enabled(pdev);
पूर्ण

अटल व्योम quirk_usb_hanकरोff_ohci(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *base;
	u32 control;
	u32 fmपूर्णांकerval = 0;
	bool no_fmपूर्णांकerval = false;
	पूर्णांक cnt;

	अगर (!mmio_resource_enabled(pdev, 0))
		वापस;

	base = pci_ioremap_bar(pdev, 0);
	अगर (base == शून्य)
		वापस;

	/*
	 * ULi M5237 OHCI controller locks the whole प्रणाली when accessing
	 * the OHCI_FMINTERVAL offset.
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_AL && pdev->device == 0x5237)
		no_fmपूर्णांकerval = true;

	control = पढ़ोl(base + OHCI_CONTROL);

/* On PA-RISC, PDC can leave IR set incorrectly; ignore it there. */
#अगर_घोषित __hppa__
#घोषणा	OHCI_CTRL_MASK		(OHCI_CTRL_RWC | OHCI_CTRL_IR)
#अन्यथा
#घोषणा	OHCI_CTRL_MASK		OHCI_CTRL_RWC

	अगर (control & OHCI_CTRL_IR) अणु
		पूर्णांक रुको_समय = 500; /* arbitrary; 5 seconds */
		ग_लिखोl(OHCI_INTR_OC, base + OHCI_INTRENABLE);
		ग_लिखोl(OHCI_OCR, base + OHCI_CMDSTATUS);
		जबतक (रुको_समय > 0 &&
				पढ़ोl(base + OHCI_CONTROL) & OHCI_CTRL_IR) अणु
			रुको_समय -= 10;
			msleep(10);
		पूर्ण
		अगर (रुको_समय <= 0)
			dev_warn(&pdev->dev,
				 "OHCI: BIOS handoff failed (BIOS bug?) %08x\n",
				 पढ़ोl(base + OHCI_CONTROL));
	पूर्ण
#पूर्ण_अगर

	/* disable पूर्णांकerrupts */
	ग_लिखोl((u32) ~0, base + OHCI_INTRDISABLE);

	/* Go पूर्णांकo the USB_RESET state, preserving RWC (and possibly IR) */
	ग_लिखोl(control & OHCI_CTRL_MASK, base + OHCI_CONTROL);
	पढ़ोl(base + OHCI_CONTROL);

	/* software reset of the controller, preserving HcFmInterval */
	अगर (!no_fmपूर्णांकerval)
		fmपूर्णांकerval = पढ़ोl(base + OHCI_FMINTERVAL);

	ग_लिखोl(OHCI_HCR, base + OHCI_CMDSTATUS);

	/* reset requires max 10 us delay */
	क्रम (cnt = 30; cnt > 0; --cnt) अणु	/* ... allow extra समय */
		अगर ((पढ़ोl(base + OHCI_CMDSTATUS) & OHCI_HCR) == 0)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (!no_fmपूर्णांकerval)
		ग_लिखोl(fmपूर्णांकerval, base + OHCI_FMINTERVAL);

	/* Now the controller is safely in SUSPEND and nothing can wake it up */
	iounmap(base);
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id ehci_dmi_nohanकरोff_table[] = अणु
	अणु
		/*  Pegatron Lucid (ExoPC) */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "EXOPG06411"),
			DMI_MATCH(DMI_BIOS_VERSION, "Lucid-CE-133"),
		पूर्ण,
	पूर्ण,
	अणु
		/*  Pegatron Lucid (Ordissimo AIRIS) */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "M11JB"),
			DMI_MATCH(DMI_BIOS_VERSION, "Lucid-"),
		पूर्ण,
	पूर्ण,
	अणु
		/*  Pegatron Lucid (Ordissimo) */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_NAME, "Ordissimo"),
			DMI_MATCH(DMI_BIOS_VERSION, "Lucid-"),
		पूर्ण,
	पूर्ण,
	अणु
		/* HASEE E200 */
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "HASEE"),
			DMI_MATCH(DMI_BOARD_NAME, "E210"),
			DMI_MATCH(DMI_BIOS_VERSION, "6.00"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम ehci_bios_hanकरोff(काष्ठा pci_dev *pdev,
					व्योम __iomem *op_reg_base,
					u32 cap, u8 offset)
अणु
	पूर्णांक try_hanकरोff = 1, tried_hanकरोff = 0;

	/*
	 * The Pegatron Lucid tablet sporadically रुकोs क्रम 98 seconds trying
	 * the hanकरोff on its unused controller.  Skip it.
	 *
	 * The HASEE E200 hangs when the semaphore is set (bugzilla #77021).
	 */
	अगर (pdev->venकरोr == 0x8086 && (pdev->device == 0x283a ||
			pdev->device == 0x27cc)) अणु
		अगर (dmi_check_प्रणाली(ehci_dmi_nohanकरोff_table))
			try_hanकरोff = 0;
	पूर्ण

	अगर (try_hanकरोff && (cap & EHCI_USBLEGSUP_BIOS)) अणु
		dev_dbg(&pdev->dev, "EHCI: BIOS handoff\n");

#अगर 0
/* aleksey_gorelov@phoenix.com reports that some प्रणालीs need SMI क्रमced on,
 * but that seems dubious in general (the BIOS left it off पूर्णांकentionally)
 * and is known to prevent some प्रणालीs from booting.  so we won't करो this
 * unless maybe we can determine when we're on a प्रणाली that needs SMI क्रमced.
 */
		/* BIOS workaround (?): be sure the pre-Linux code
		 * receives the SMI
		 */
		pci_पढ़ो_config_dword(pdev, offset + EHCI_USBLEGCTLSTS, &val);
		pci_ग_लिखो_config_dword(pdev, offset + EHCI_USBLEGCTLSTS,
				       val | EHCI_USBLEGCTLSTS_SOOE);
#पूर्ण_अगर

		/* some प्रणालीs get upset अगर this semaphore is
		 * set क्रम any other reason than क्रमcing a BIOS
		 * hanकरोff..
		 */
		pci_ग_लिखो_config_byte(pdev, offset + 3, 1);
	पूर्ण

	/* अगर boot firmware now owns EHCI, spin till it hands it over. */
	अगर (try_hanकरोff) अणु
		पूर्णांक msec = 1000;
		जबतक ((cap & EHCI_USBLEGSUP_BIOS) && (msec > 0)) अणु
			tried_hanकरोff = 1;
			msleep(10);
			msec -= 10;
			pci_पढ़ो_config_dword(pdev, offset, &cap);
		पूर्ण
	पूर्ण

	अगर (cap & EHCI_USBLEGSUP_BIOS) अणु
		/* well, possibly buggy BIOS... try to shut it करोwn,
		 * and hope nothing goes too wrong
		 */
		अगर (try_hanकरोff)
			dev_warn(&pdev->dev,
				 "EHCI: BIOS handoff failed (BIOS bug?) %08x\n",
				 cap);
		pci_ग_लिखो_config_byte(pdev, offset + 2, 0);
	पूर्ण

	/* just in हाल, always disable EHCI SMIs */
	pci_ग_लिखो_config_dword(pdev, offset + EHCI_USBLEGCTLSTS, 0);

	/* If the BIOS ever owned the controller then we can't expect
	 * any घातer sessions to reमुख्य पूर्णांकact.
	 */
	अगर (tried_hanकरोff)
		ग_लिखोl(0, op_reg_base + EHCI_CONFIGFLAG);
पूर्ण

अटल व्योम quirk_usb_disable_ehci(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *base, *op_reg_base;
	u32	hcc_params, cap, val;
	u8	offset, cap_length;
	पूर्णांक	रुको_समय, count = 256/4;

	अगर (!mmio_resource_enabled(pdev, 0))
		वापस;

	base = pci_ioremap_bar(pdev, 0);
	अगर (base == शून्य)
		वापस;

	cap_length = पढ़ोb(base);
	op_reg_base = base + cap_length;

	/* EHCI 0.96 and later may have "extended capabilities"
	 * spec section 5.1 explains the bios hanकरोff, e.g. क्रम
	 * booting from USB disk or using a usb keyboard
	 */
	hcc_params = पढ़ोl(base + EHCI_HCC_PARAMS);
	offset = (hcc_params >> 8) & 0xff;
	जबतक (offset && --count) अणु
		pci_पढ़ो_config_dword(pdev, offset, &cap);

		चयन (cap & 0xff) अणु
		हाल 1:
			ehci_bios_hanकरोff(pdev, op_reg_base, cap, offset);
			अवरोध;
		हाल 0: /* Illegal reserved cap, set cap=0 so we निकास */
			cap = 0;
			fallthrough;
		शेष:
			dev_warn(&pdev->dev,
				 "EHCI: unrecognized capability %02x\n",
				 cap & 0xff);
		पूर्ण
		offset = (cap >> 8) & 0xff;
	पूर्ण
	अगर (!count)
		dev_prपूर्णांकk(KERN_DEBUG, &pdev->dev, "EHCI: capability loop?\n");

	/*
	 * halt EHCI & disable its पूर्णांकerrupts in any हाल
	 */
	val = पढ़ोl(op_reg_base + EHCI_USBSTS);
	अगर ((val & EHCI_USBSTS_HALTED) == 0) अणु
		val = पढ़ोl(op_reg_base + EHCI_USBCMD);
		val &= ~EHCI_USBCMD_RUN;
		ग_लिखोl(val, op_reg_base + EHCI_USBCMD);

		रुको_समय = 2000;
		करो अणु
			ग_लिखोl(0x3f, op_reg_base + EHCI_USBSTS);
			udelay(100);
			रुको_समय -= 100;
			val = पढ़ोl(op_reg_base + EHCI_USBSTS);
			अगर ((val == ~(u32)0) || (val & EHCI_USBSTS_HALTED)) अणु
				अवरोध;
			पूर्ण
		पूर्ण जबतक (रुको_समय > 0);
	पूर्ण
	ग_लिखोl(0, op_reg_base + EHCI_USBINTR);
	ग_लिखोl(0x3f, op_reg_base + EHCI_USBSTS);

	iounmap(base);
पूर्ण

/*
 * handshake - spin पढ़ोing a रेजिस्टर until handshake completes
 * @ptr: address of hc रेजिस्टर to be पढ़ो
 * @mask: bits to look at in result of पढ़ो
 * @करोne: value of those bits when handshake succeeds
 * @रुको_usec: समयout in microseconds
 * @delay_usec: delay in microseconds to रुको between polling
 *
 * Polls a रेजिस्टर every delay_usec microseconds.
 * Returns 0 when the mask bits have the value करोne.
 * Returns -ETIMEDOUT अगर this condition is not true after
 * रुको_usec microseconds have passed.
 */
अटल पूर्णांक handshake(व्योम __iomem *ptr, u32 mask, u32 करोne,
		पूर्णांक रुको_usec, पूर्णांक delay_usec)
अणु
	u32	result;

	वापस पढ़ोl_poll_समयout_atomic(ptr, result,
					 ((result & mask) == करोne),
					 delay_usec, रुको_usec);
पूर्ण

/*
 * Intel's Panther Poपूर्णांक chipset has two host controllers (EHCI and xHCI) that
 * share some number of ports.  These ports can be चयनed between either
 * controller.  Not all of the ports under the EHCI host controller may be
 * चयनable.
 *
 * The ports should be चयनed over to xHCI beक्रमe PCI probes क्रम any device
 * start.  This aव्योमs active devices under EHCI being disconnected during the
 * port चयनover, which could cause loss of data on USB storage devices, or
 * failed boot when the root file प्रणाली is on a USB mass storage device and is
 * क्रमागतerated under EHCI first.
 *
 * We ग_लिखो पूर्णांकo the xHC's PCI configuration space in some Intel-specअगरic
 * रेजिस्टरs to चयन the ports over.  The USB 3.0 terminations and the USB
 * 2.0 data wires are चयनed separately.  We want to enable the SuperSpeed
 * terminations beक्रमe चयनing the USB 2.0 wires over, so that USB 3.0
 * devices connect at SuperSpeed, rather than at USB 2.0 speeds.
 */
व्योम usb_enable_पूर्णांकel_xhci_ports(काष्ठा pci_dev *xhci_pdev)
अणु
	u32		ports_available;
	bool		ehci_found = false;
	काष्ठा pci_dev	*companion = शून्य;

	/* Sony VAIO t-series with subप्रणाली device ID 90a8 is not capable of
	 * चयनing ports from EHCI to xHCI
	 */
	अगर (xhci_pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_SONY &&
	    xhci_pdev->subप्रणाली_device == 0x90a8)
		वापस;

	/* make sure an पूर्णांकel EHCI controller exists */
	क्रम_each_pci_dev(companion) अणु
		अगर (companion->class == PCI_CLASS_SERIAL_USB_EHCI &&
		    companion->venकरोr == PCI_VENDOR_ID_INTEL) अणु
			ehci_found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ehci_found)
		वापस;

	/* Don't switchover the ports if the user hasn't compiled the xHCI
	 * driver.  Otherwise they will see "dead" USB ports that करोn't घातer
	 * the devices.
	 */
	अगर (!IS_ENABLED(CONFIG_USB_XHCI_HCD)) अणु
		dev_warn(&xhci_pdev->dev,
			 "CONFIG_USB_XHCI_HCD is turned off, defaulting to EHCI.\n");
		dev_warn(&xhci_pdev->dev,
				"USB 3.0 devices will work at USB 2.0 speeds.\n");
		usb_disable_xhci_ports(xhci_pdev);
		वापस;
	पूर्ण

	/* Read USB3PRM, the USB 3.0 Port Routing Mask Register
	 * Indicate the ports that can be changed from OS.
	 */
	pci_पढ़ो_config_dword(xhci_pdev, USB_INTEL_USB3PRM,
			&ports_available);

	dev_dbg(&xhci_pdev->dev, "Configurable ports to enable SuperSpeed: 0x%x\n",
			ports_available);

	/* Write USB3_PSSEN, the USB 3.0 Port SuperSpeed Enable
	 * Register, to turn on SuperSpeed terminations क्रम the
	 * चयनable ports.
	 */
	pci_ग_लिखो_config_dword(xhci_pdev, USB_INTEL_USB3_PSSEN,
			ports_available);

	pci_पढ़ो_config_dword(xhci_pdev, USB_INTEL_USB3_PSSEN,
			&ports_available);
	dev_dbg(&xhci_pdev->dev,
		"USB 3.0 ports that are now enabled under xHCI: 0x%x\n",
		ports_available);

	/* Read XUSB2PRM, xHCI USB 2.0 Port Routing Mask Register
	 * Indicate the USB 2.0 ports to be controlled by the xHCI host.
	 */

	pci_पढ़ो_config_dword(xhci_pdev, USB_INTEL_USB2PRM,
			&ports_available);

	dev_dbg(&xhci_pdev->dev, "Configurable USB 2.0 ports to hand over to xCHI: 0x%x\n",
			ports_available);

	/* Write XUSB2PR, the xHC USB 2.0 Port Routing Register, to
	 * चयन the USB 2.0 घातer and data lines over to the xHCI
	 * host.
	 */
	pci_ग_लिखो_config_dword(xhci_pdev, USB_INTEL_XUSB2PR,
			ports_available);

	pci_पढ़ो_config_dword(xhci_pdev, USB_INTEL_XUSB2PR,
			&ports_available);
	dev_dbg(&xhci_pdev->dev,
		"USB 2.0 ports that are now switched over to xHCI: 0x%x\n",
		ports_available);
पूर्ण
EXPORT_SYMBOL_GPL(usb_enable_पूर्णांकel_xhci_ports);

व्योम usb_disable_xhci_ports(काष्ठा pci_dev *xhci_pdev)
अणु
	pci_ग_लिखो_config_dword(xhci_pdev, USB_INTEL_USB3_PSSEN, 0x0);
	pci_ग_लिखो_config_dword(xhci_pdev, USB_INTEL_XUSB2PR, 0x0);
पूर्ण
EXPORT_SYMBOL_GPL(usb_disable_xhci_ports);

/*
 * PCI Quirks क्रम xHCI.
 *
 * Takes care of the hanकरोff between the Pre-OS (i.e. BIOS) and the OS.
 * It संकेतs to the BIOS that the OS wants control of the host controller,
 * and then रुकोs 1 second क्रम the BIOS to hand over control.
 * If we समयout, assume the BIOS is broken and take control anyway.
 */
अटल व्योम quirk_usb_hanकरोff_xhci(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *base;
	पूर्णांक ext_cap_offset;
	व्योम __iomem *op_reg_base;
	u32 val;
	पूर्णांक समयout;
	पूर्णांक len = pci_resource_len(pdev, 0);

	अगर (!mmio_resource_enabled(pdev, 0))
		वापस;

	base = ioremap(pci_resource_start(pdev, 0), len);
	अगर (base == शून्य)
		वापस;

	/*
	 * Find the Legacy Support Capability रेजिस्टर -
	 * this is optional क्रम xHCI host controllers.
	 */
	ext_cap_offset = xhci_find_next_ext_cap(base, 0, XHCI_EXT_CAPS_LEGACY);

	अगर (!ext_cap_offset)
		जाओ hc_init;

	अगर ((ext_cap_offset + माप(val)) > len) अणु
		/* We're पढ़ोing garbage from the controller */
		dev_warn(&pdev->dev, "xHCI controller failing to respond");
		जाओ iounmap;
	पूर्ण
	val = पढ़ोl(base + ext_cap_offset);

	/* Auto hanकरोff never worked क्रम these devices. Force it and जारी */
	अगर ((pdev->venकरोr == PCI_VENDOR_ID_TI && pdev->device == 0x8241) ||
			(pdev->venकरोr == PCI_VENDOR_ID_RENESAS
			 && pdev->device == 0x0014)) अणु
		val = (val | XHCI_HC_OS_OWNED) & ~XHCI_HC_BIOS_OWNED;
		ग_लिखोl(val, base + ext_cap_offset);
	पूर्ण

	/* If the BIOS owns the HC, संकेत that the OS wants it, and रुको */
	अगर (val & XHCI_HC_BIOS_OWNED) अणु
		ग_लिखोl(val | XHCI_HC_OS_OWNED, base + ext_cap_offset);

		/* Wait क्रम 1 second with 10 microsecond polling पूर्णांकerval */
		समयout = handshake(base + ext_cap_offset, XHCI_HC_BIOS_OWNED,
				0, 1000000, 10);

		/* Assume a buggy BIOS and take HC ownership anyway */
		अगर (समयout) अणु
			dev_warn(&pdev->dev,
				 "xHCI BIOS handoff failed (BIOS bug ?) %08x\n",
				 val);
			ग_लिखोl(val & ~XHCI_HC_BIOS_OWNED, base + ext_cap_offset);
		पूर्ण
	पूर्ण

	val = पढ़ोl(base + ext_cap_offset + XHCI_LEGACY_CONTROL_OFFSET);
	/* Mask off (turn off) any enabled SMIs */
	val &= XHCI_LEGACY_DISABLE_SMI;
	/* Mask all SMI events bits, RW1C */
	val |= XHCI_LEGACY_SMI_EVENTS;
	/* Disable any BIOS SMIs and clear all SMI events*/
	ग_लिखोl(val, base + ext_cap_offset + XHCI_LEGACY_CONTROL_OFFSET);

hc_init:
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL)
		usb_enable_पूर्णांकel_xhci_ports(pdev);

	op_reg_base = base + XHCI_HC_LENGTH(पढ़ोl(base));

	/* Wait क्रम the host controller to be पढ़ोy beक्रमe writing any
	 * operational or runसमय रेजिस्टरs.  Wait 5 seconds and no more.
	 */
	समयout = handshake(op_reg_base + XHCI_STS_OFFSET, XHCI_STS_CNR, 0,
			5000000, 10);
	/* Assume a buggy HC and start HC initialization anyway */
	अगर (समयout) अणु
		val = पढ़ोl(op_reg_base + XHCI_STS_OFFSET);
		dev_warn(&pdev->dev,
			 "xHCI HW not ready after 5 sec (HC bug?) status = 0x%x\n",
			 val);
	पूर्ण

	/* Send the halt and disable पूर्णांकerrupts command */
	val = पढ़ोl(op_reg_base + XHCI_CMD_OFFSET);
	val &= ~(XHCI_CMD_RUN | XHCI_IRQS);
	ग_लिखोl(val, op_reg_base + XHCI_CMD_OFFSET);

	/* Wait क्रम the HC to halt - poll every 125 usec (one microframe). */
	समयout = handshake(op_reg_base + XHCI_STS_OFFSET, XHCI_STS_HALT, 1,
			XHCI_MAX_HALT_USEC, 125);
	अगर (समयout) अणु
		val = पढ़ोl(op_reg_base + XHCI_STS_OFFSET);
		dev_warn(&pdev->dev,
			 "xHCI HW did not halt within %d usec status = 0x%x\n",
			 XHCI_MAX_HALT_USEC, val);
	पूर्ण

iounmap:
	iounmap(base);
पूर्ण

अटल व्योम quirk_usb_early_hanकरोff(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device_node *parent;
	bool is_rpi;

	/* Skip Netlogic mips SoC's पूर्णांकernal PCI USB controller.
	 * This device करोes not need/support EHCI/OHCI hanकरोff
	 */
	अगर (pdev->venकरोr == 0x184e)	/* venकरोr Netlogic */
		वापस;

	/*
	 * Bypass the Raspberry Pi 4 controller xHCI controller, things are
	 * taken care of by the board's co-processor.
	 */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_VIA && pdev->device == 0x3483) अणु
		parent = of_get_parent(pdev->bus->dev.of_node);
		is_rpi = of_device_is_compatible(parent, "brcm,bcm2711-pcie");
		of_node_put(parent);
		अगर (is_rpi)
			वापस;
	पूर्ण

	अगर (pdev->class != PCI_CLASS_SERIAL_USB_UHCI &&
			pdev->class != PCI_CLASS_SERIAL_USB_OHCI &&
			pdev->class != PCI_CLASS_SERIAL_USB_EHCI &&
			pdev->class != PCI_CLASS_SERIAL_USB_XHCI)
		वापस;

	अगर (pci_enable_device(pdev) < 0) अणु
		dev_warn(&pdev->dev,
			 "Can't enable PCI device, BIOS handoff failed.\n");
		वापस;
	पूर्ण
	अगर (pdev->class == PCI_CLASS_SERIAL_USB_UHCI)
		quirk_usb_hanकरोff_uhci(pdev);
	अन्यथा अगर (pdev->class == PCI_CLASS_SERIAL_USB_OHCI)
		quirk_usb_hanकरोff_ohci(pdev);
	अन्यथा अगर (pdev->class == PCI_CLASS_SERIAL_USB_EHCI)
		quirk_usb_disable_ehci(pdev);
	अन्यथा अगर (pdev->class == PCI_CLASS_SERIAL_USB_XHCI)
		quirk_usb_hanकरोff_xhci(pdev);
	pci_disable_device(pdev);
पूर्ण
DECLARE_PCI_FIXUP_CLASS_FINAL(PCI_ANY_ID, PCI_ANY_ID,
			PCI_CLASS_SERIAL_USB, 8, quirk_usb_early_hanकरोff);
