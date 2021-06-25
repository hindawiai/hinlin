<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	पूर्णांकel TCO Watchकरोg Driver
 *
 *	(c) Copyright 2006-2011 Wim Van Sebroeck <wim@iguana.be>.
 *
 *	Neither Wim Van Sebroeck nor Iguana vzw. admit liability nor
 *	provide warranty क्रम any of this software. This material is
 *	provided "AS-IS" and at no अक्षरge.
 *
 *	The TCO watchकरोg is implemented in the following I/O controller hubs:
 *	(See the पूर्णांकel करोcumentation on http://developer.पूर्णांकel.com.)
 *	करोcument number 290655-003, 290677-014: 82801AA (ICH), 82801AB (ICHO)
 *	करोcument number 290687-002, 298242-027: 82801BA (ICH2)
 *	करोcument number 290733-003, 290739-013: 82801CA (ICH3-S)
 *	करोcument number 290716-001, 290718-007: 82801CAM (ICH3-M)
 *	करोcument number 290744-001, 290745-025: 82801DB (ICH4)
 *	करोcument number 252337-001, 252663-008: 82801DBM (ICH4-M)
 *	करोcument number 273599-001, 273645-002: 82801E (C-ICH)
 *	करोcument number 252516-001, 252517-028: 82801EB (ICH5), 82801ER (ICH5R)
 *	करोcument number 300641-004, 300884-013: 6300ESB
 *	करोcument number 301473-002, 301474-026: 82801F (ICH6)
 *	करोcument number 313082-001, 313075-006: 631xESB, 632xESB
 *	करोcument number 307013-003, 307014-024: 82801G (ICH7)
 *	करोcument number 322896-001, 322897-001: NM10
 *	करोcument number 313056-003, 313057-017: 82801H (ICH8)
 *	करोcument number 316972-004, 316973-012: 82801I (ICH9)
 *	करोcument number 319973-002, 319974-002: 82801J (ICH10)
 *	करोcument number 322169-001, 322170-003: 5 Series, 3400 Series (PCH)
 *	करोcument number 320066-003, 320257-008: EP80597 (IICH)
 *	करोcument number 324645-001, 324646-001: Cougar Poपूर्णांक (CPT)
 *	करोcument number TBD                   : Patsburg (PBG)
 *	करोcument number TBD                   : DH89xxCC
 *	करोcument number TBD                   : Panther Poपूर्णांक
 *	करोcument number TBD                   : Lynx Poपूर्णांक
 *	करोcument number TBD                   : Lynx Poपूर्णांक-LP
 */

/*
 *	Includes, defines, variables, module parameters, ...
 */

/* Module and version inक्रमmation */
#घोषणा DRV_NAME	"iTCO_wdt"
#घोषणा DRV_VERSION	"1.11"

/* Includes */
#समावेश <linux/acpi.h>			/* For ACPI support */
#समावेश <linux/bits.h>			/* For BIT() */
#समावेश <linux/module.h>		/* For module specअगरic items */
#समावेश <linux/moduleparam.h>		/* For new moduleparam's */
#समावेश <linux/types.h>		/* For standard types (like माप_प्रकार) */
#समावेश <linux/त्रुटिसं.स>		/* For the -ENODEV/... values */
#समावेश <linux/kernel.h>		/* For prपूर्णांकk/panic/... */
#समावेश <linux/watchकरोg.h>		/* For the watchकरोg specअगरic items */
#समावेश <linux/init.h>			/* For __init/__निकास/... */
#समावेश <linux/fs.h>			/* For file operations */
#समावेश <linux/platक्रमm_device.h>	/* For platक्रमm_driver framework */
#समावेश <linux/pci.h>			/* For pci functions */
#समावेश <linux/ioport.h>		/* For io-port access */
#समावेश <linux/spinlock.h>		/* For spin_lock/spin_unlock/... */
#समावेश <linux/uaccess.h>		/* For copy_to_user/put_user/... */
#समावेश <linux/पन.स>			/* For inb/outb/... */
#समावेश <linux/platक्रमm_data/itco_wdt.h>
#समावेश <linux/mfd/पूर्णांकel_pmc_bxt.h>

#समावेश "iTCO_vendor.h"

/* Address definitions क्रम the TCO */
/* TCO base address */
#घोषणा TCOBASE(p)	((p)->tco_res->start)
/* SMI Control and Enable Register */
#घोषणा SMI_EN(p)	((p)->smi_res->start)

#घोषणा TCO_RLD(p)	(TCOBASE(p) + 0x00) /* TCO Timer Reload/Curr. Value */
#घोषणा TCOv1_TMR(p)	(TCOBASE(p) + 0x01) /* TCOv1 Timer Initial Value*/
#घोषणा TCO_DAT_IN(p)	(TCOBASE(p) + 0x02) /* TCO Data In Register	*/
#घोषणा TCO_DAT_OUT(p)	(TCOBASE(p) + 0x03) /* TCO Data Out Register	*/
#घोषणा TCO1_STS(p)	(TCOBASE(p) + 0x04) /* TCO1 Status Register	*/
#घोषणा TCO2_STS(p)	(TCOBASE(p) + 0x06) /* TCO2 Status Register	*/
#घोषणा TCO1_CNT(p)	(TCOBASE(p) + 0x08) /* TCO1 Control Register	*/
#घोषणा TCO2_CNT(p)	(TCOBASE(p) + 0x0a) /* TCO2 Control Register	*/
#घोषणा TCOv2_TMR(p)	(TCOBASE(p) + 0x12) /* TCOv2 Timer Initial Value*/

/* पूर्णांकernal variables */
काष्ठा iTCO_wdt_निजी अणु
	काष्ठा watchकरोg_device wddev;

	/* TCO version/generation */
	अचिन्हित पूर्णांक iTCO_version;
	काष्ठा resource *tco_res;
	काष्ठा resource *smi_res;
	/*
	 * NO_REBOOT flag is Memory-Mapped GCS रेजिस्टर bit 5 (TCO version 2),
	 * or memory-mapped PMC रेजिस्टर bit 4 (TCO version 3).
	 */
	काष्ठा resource *gcs_pmc_res;
	अचिन्हित दीर्घ __iomem *gcs_pmc;
	/* the lock क्रम io operations */
	spinlock_t io_lock;
	/* the PCI-device */
	काष्ठा pci_dev *pci_dev;
	/* whether or not the watchकरोg has been suspended */
	bool suspended;
	/* no reboot API निजी data */
	व्योम *no_reboot_priv;
	/* no reboot update function poपूर्णांकer */
	पूर्णांक (*update_no_reboot_bit)(व्योम *p, bool set);
पूर्ण;

/* module parameters */
#घोषणा WATCHDOG_TIMEOUT 30	/* 30 sec शेष heartbeat */
अटल पूर्णांक heartbeat = WATCHDOG_TIMEOUT;  /* in seconds */
module_param(heartbeat, पूर्णांक, 0);
MODULE_PARM_DESC(heartbeat, "Watchdog timeout in seconds. "
	"5..76 (TCO v1) or 3..614 (TCO v2), default="
				__MODULE_STRING(WATCHDOG_TIMEOUT) ")");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout,
	"Watchdog cannot be stopped once started (default="
				__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल पूर्णांक turn_SMI_watchकरोg_clear_off = 1;
module_param(turn_SMI_watchकरोg_clear_off, पूर्णांक, 0);
MODULE_PARM_DESC(turn_SMI_watchकरोg_clear_off,
	"Turn off SMI clearing watchdog (depends on TCO-version)(default=1)");

/*
 * Some TCO specअगरic functions
 */

/*
 * The iTCO v1 and v2's पूर्णांकernal समयr is stored as ticks which decrement
 * every 0.6 seconds.  v3's पूर्णांकernal समयr is stored as seconds (some
 * datasheets incorrectly state 0.6 seconds).
 */
अटल अंतरभूत अचिन्हित पूर्णांक seconds_to_ticks(काष्ठा iTCO_wdt_निजी *p,
					    पूर्णांक secs)
अणु
	वापस p->iTCO_version == 3 ? secs : (secs * 10) / 6;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ticks_to_seconds(काष्ठा iTCO_wdt_निजी *p,
					    पूर्णांक ticks)
अणु
	वापस p->iTCO_version == 3 ? ticks : (ticks * 6) / 10;
पूर्ण

अटल अंतरभूत u32 no_reboot_bit(काष्ठा iTCO_wdt_निजी *p)
अणु
	u32 enable_bit;

	चयन (p->iTCO_version) अणु
	हाल 5:
	हाल 3:
		enable_bit = 0x00000010;
		अवरोध;
	हाल 2:
		enable_bit = 0x00000020;
		अवरोध;
	हाल 4:
	हाल 1:
	शेष:
		enable_bit = 0x00000002;
		अवरोध;
	पूर्ण

	वापस enable_bit;
पूर्ण

अटल पूर्णांक update_no_reboot_bit_def(व्योम *priv, bool set)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक update_no_reboot_bit_pci(व्योम *priv, bool set)
अणु
	काष्ठा iTCO_wdt_निजी *p = priv;
	u32 val32 = 0, newval32 = 0;

	pci_पढ़ो_config_dword(p->pci_dev, 0xd4, &val32);
	अगर (set)
		val32 |= no_reboot_bit(p);
	अन्यथा
		val32 &= ~no_reboot_bit(p);
	pci_ग_लिखो_config_dword(p->pci_dev, 0xd4, val32);
	pci_पढ़ो_config_dword(p->pci_dev, 0xd4, &newval32);

	/* make sure the update is successful */
	अगर (val32 != newval32)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक update_no_reboot_bit_mem(व्योम *priv, bool set)
अणु
	काष्ठा iTCO_wdt_निजी *p = priv;
	u32 val32 = 0, newval32 = 0;

	val32 = पढ़ोl(p->gcs_pmc);
	अगर (set)
		val32 |= no_reboot_bit(p);
	अन्यथा
		val32 &= ~no_reboot_bit(p);
	ग_लिखोl(val32, p->gcs_pmc);
	newval32 = पढ़ोl(p->gcs_pmc);

	/* make sure the update is successful */
	अगर (val32 != newval32)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक update_no_reboot_bit_cnt(व्योम *priv, bool set)
अणु
	काष्ठा iTCO_wdt_निजी *p = priv;
	u16 val, newval;

	val = inw(TCO1_CNT(p));
	अगर (set)
		val |= BIT(0);
	अन्यथा
		val &= ~BIT(0);
	outw(val, TCO1_CNT(p));
	newval = inw(TCO1_CNT(p));

	/* make sure the update is successful */
	वापस val != newval ? -EIO : 0;
पूर्ण

अटल पूर्णांक update_no_reboot_bit_pmc(व्योम *priv, bool set)
अणु
	काष्ठा पूर्णांकel_pmc_dev *pmc = priv;
	u32 bits = PMC_CFG_NO_REBOOT_EN;
	u32 value = set ? bits : 0;

	वापस पूर्णांकel_pmc_gcr_update(pmc, PMC_GCR_PMC_CFG_REG, bits, value);
पूर्ण

अटल व्योम iTCO_wdt_no_reboot_bit_setup(काष्ठा iTCO_wdt_निजी *p,
					 काष्ठा platक्रमm_device *pdev,
					 काष्ठा itco_wdt_platक्रमm_data *pdata)
अणु
	अगर (pdata->no_reboot_use_pmc) अणु
		काष्ठा पूर्णांकel_pmc_dev *pmc = dev_get_drvdata(pdev->dev.parent);

		p->update_no_reboot_bit = update_no_reboot_bit_pmc;
		p->no_reboot_priv = pmc;
		वापस;
	पूर्ण

	अगर (p->iTCO_version >= 6)
		p->update_no_reboot_bit = update_no_reboot_bit_cnt;
	अन्यथा अगर (p->iTCO_version >= 2)
		p->update_no_reboot_bit = update_no_reboot_bit_mem;
	अन्यथा अगर (p->iTCO_version == 1)
		p->update_no_reboot_bit = update_no_reboot_bit_pci;
	अन्यथा
		p->update_no_reboot_bit = update_no_reboot_bit_def;

	p->no_reboot_priv = p;
पूर्ण

अटल पूर्णांक iTCO_wdt_start(काष्ठा watchकरोg_device *wd_dev)
अणु
	काष्ठा iTCO_wdt_निजी *p = watchकरोg_get_drvdata(wd_dev);
	अचिन्हित पूर्णांक val;

	spin_lock(&p->io_lock);

	iTCO_venकरोr_pre_start(p->smi_res, wd_dev->समयout);

	/* disable chipset's NO_REBOOT bit */
	अगर (p->update_no_reboot_bit(p->no_reboot_priv, false)) अणु
		spin_unlock(&p->io_lock);
		dev_err(wd_dev->parent, "failed to reset NO_REBOOT flag, reboot disabled by hardware/BIOS\n");
		वापस -EIO;
	पूर्ण

	/* Force the समयr to its reload value by writing to the TCO_RLD
	   रेजिस्टर */
	अगर (p->iTCO_version >= 2)
		outw(0x01, TCO_RLD(p));
	अन्यथा अगर (p->iTCO_version == 1)
		outb(0x01, TCO_RLD(p));

	/* Bit 11: TCO Timer Halt -> 0 = The TCO समयr is enabled to count */
	val = inw(TCO1_CNT(p));
	val &= 0xf7ff;
	outw(val, TCO1_CNT(p));
	val = inw(TCO1_CNT(p));
	spin_unlock(&p->io_lock);

	अगर (val & 0x0800)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक iTCO_wdt_stop(काष्ठा watchकरोg_device *wd_dev)
अणु
	काष्ठा iTCO_wdt_निजी *p = watchकरोg_get_drvdata(wd_dev);
	अचिन्हित पूर्णांक val;

	spin_lock(&p->io_lock);

	iTCO_venकरोr_pre_stop(p->smi_res);

	/* Bit 11: TCO Timer Halt -> 1 = The TCO समयr is disabled */
	val = inw(TCO1_CNT(p));
	val |= 0x0800;
	outw(val, TCO1_CNT(p));
	val = inw(TCO1_CNT(p));

	/* Set the NO_REBOOT bit to prevent later reboots, just क्रम sure */
	p->update_no_reboot_bit(p->no_reboot_priv, true);

	spin_unlock(&p->io_lock);

	अगर ((val & 0x0800) == 0)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक iTCO_wdt_ping(काष्ठा watchकरोg_device *wd_dev)
अणु
	काष्ठा iTCO_wdt_निजी *p = watchकरोg_get_drvdata(wd_dev);

	spin_lock(&p->io_lock);

	/* Reload the समयr by writing to the TCO Timer Counter रेजिस्टर */
	अगर (p->iTCO_version >= 2) अणु
		outw(0x01, TCO_RLD(p));
	पूर्ण अन्यथा अगर (p->iTCO_version == 1) अणु
		/* Reset the समयout status bit so that the समयr
		 * needs to count करोwn twice again beक्रमe rebooting */
		outw(0x0008, TCO1_STS(p));	/* ग_लिखो 1 to clear bit */

		outb(0x01, TCO_RLD(p));
	पूर्ण

	spin_unlock(&p->io_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक iTCO_wdt_set_समयout(काष्ठा watchकरोg_device *wd_dev, अचिन्हित पूर्णांक t)
अणु
	काष्ठा iTCO_wdt_निजी *p = watchकरोg_get_drvdata(wd_dev);
	अचिन्हित पूर्णांक val16;
	अचिन्हित अक्षर val8;
	अचिन्हित पूर्णांक पंचांगrval;

	पंचांगrval = seconds_to_ticks(p, t);

	/* For TCO v1 the समयr counts करोwn twice beक्रमe rebooting */
	अगर (p->iTCO_version == 1)
		पंचांगrval /= 2;

	/* from the specs: */
	/* "Values of 0h-3h are ignored and should not be attempted" */
	अगर (पंचांगrval < 0x04)
		वापस -EINVAL;
	अगर ((p->iTCO_version >= 2 && पंचांगrval > 0x3ff) ||
	    (p->iTCO_version == 1 && पंचांगrval > 0x03f))
		वापस -EINVAL;

	/* Write new heartbeat to watchकरोg */
	अगर (p->iTCO_version >= 2) अणु
		spin_lock(&p->io_lock);
		val16 = inw(TCOv2_TMR(p));
		val16 &= 0xfc00;
		val16 |= पंचांगrval;
		outw(val16, TCOv2_TMR(p));
		val16 = inw(TCOv2_TMR(p));
		spin_unlock(&p->io_lock);

		अगर ((val16 & 0x3ff) != पंचांगrval)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (p->iTCO_version == 1) अणु
		spin_lock(&p->io_lock);
		val8 = inb(TCOv1_TMR(p));
		val8 &= 0xc0;
		val8 |= (पंचांगrval & 0xff);
		outb(val8, TCOv1_TMR(p));
		val8 = inb(TCOv1_TMR(p));
		spin_unlock(&p->io_lock);

		अगर ((val8 & 0x3f) != पंचांगrval)
			वापस -EINVAL;
	पूर्ण

	wd_dev->समयout = t;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक iTCO_wdt_get_समयleft(काष्ठा watchकरोg_device *wd_dev)
अणु
	काष्ठा iTCO_wdt_निजी *p = watchकरोg_get_drvdata(wd_dev);
	अचिन्हित पूर्णांक val16;
	अचिन्हित अक्षर val8;
	अचिन्हित पूर्णांक समय_left = 0;

	/* पढ़ो the TCO Timer */
	अगर (p->iTCO_version >= 2) अणु
		spin_lock(&p->io_lock);
		val16 = inw(TCO_RLD(p));
		val16 &= 0x3ff;
		spin_unlock(&p->io_lock);

		समय_left = ticks_to_seconds(p, val16);
	पूर्ण अन्यथा अगर (p->iTCO_version == 1) अणु
		spin_lock(&p->io_lock);
		val8 = inb(TCO_RLD(p));
		val8 &= 0x3f;
		अगर (!(inw(TCO1_STS(p)) & 0x0008))
			val8 += (inb(TCOv1_TMR(p)) & 0x3f);
		spin_unlock(&p->io_lock);

		समय_left = ticks_to_seconds(p, val8);
	पूर्ण
	वापस समय_left;
पूर्ण

/*
 *	Kernel Interfaces
 */

अटल स्थिर काष्ठा watchकरोg_info ident = अणु
	.options =		WDIOF_SETTIMEOUT |
				WDIOF_KEEPALIVEPING |
				WDIOF_MAGICCLOSE,
	.firmware_version =	0,
	.identity =		DRV_NAME,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops iTCO_wdt_ops = अणु
	.owner =		THIS_MODULE,
	.start =		iTCO_wdt_start,
	.stop =			iTCO_wdt_stop,
	.ping =			iTCO_wdt_ping,
	.set_समयout =		iTCO_wdt_set_समयout,
	.get_समयleft =		iTCO_wdt_get_समयleft,
पूर्ण;

/*
 *	Init & निकास routines
 */

अटल पूर्णांक iTCO_wdt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा itco_wdt_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा iTCO_wdt_निजी *p;
	अचिन्हित दीर्घ val32;
	पूर्णांक ret;

	अगर (!pdata)
		वापस -ENODEV;

	p = devm_kzalloc(dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	spin_lock_init(&p->io_lock);

	p->tco_res = platक्रमm_get_resource(pdev, IORESOURCE_IO, ICH_RES_IO_TCO);
	अगर (!p->tco_res)
		वापस -ENODEV;

	p->iTCO_version = pdata->version;
	p->pci_dev = to_pci_dev(dev->parent);

	p->smi_res = platक्रमm_get_resource(pdev, IORESOURCE_IO, ICH_RES_IO_SMI);
	अगर (p->smi_res) अणु
		/* The TCO logic uses the TCO_EN bit in the SMI_EN रेजिस्टर */
		अगर (!devm_request_region(dev, p->smi_res->start,
					 resource_size(p->smi_res),
					 pdev->name)) अणु
			pr_err("I/O address 0x%04llx already in use, device disabled\n",
			       (u64)SMI_EN(p));
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अगर (iTCO_venकरोrsupport ||
		   turn_SMI_watchकरोg_clear_off >= p->iTCO_version) अणु
		pr_err("SMI I/O resource is missing\n");
		वापस -ENODEV;
	पूर्ण

	iTCO_wdt_no_reboot_bit_setup(p, pdev, pdata);

	/*
	 * Get the Memory-Mapped GCS or PMC रेजिस्टर, we need it क्रम the
	 * NO_REBOOT flag (TCO v2 and v3).
	 */
	अगर (p->iTCO_version >= 2 && p->iTCO_version < 6 &&
	    !pdata->no_reboot_use_pmc) अणु
		p->gcs_pmc_res = platक्रमm_get_resource(pdev,
						       IORESOURCE_MEM,
						       ICH_RES_MEM_GCS_PMC);
		p->gcs_pmc = devm_ioremap_resource(dev, p->gcs_pmc_res);
		अगर (IS_ERR(p->gcs_pmc))
			वापस PTR_ERR(p->gcs_pmc);
	पूर्ण

	/* Check chipset's NO_REBOOT bit */
	अगर (p->update_no_reboot_bit(p->no_reboot_priv, false) &&
	    iTCO_venकरोr_check_noreboot_on()) अणु
		dev_info(dev, "unable to reset NO_REBOOT flag, device disabled by hardware/BIOS\n");
		वापस -ENODEV;	/* Cannot reset NO_REBOOT bit */
	पूर्ण

	/* Set the NO_REBOOT bit to prevent later reboots, just क्रम sure */
	p->update_no_reboot_bit(p->no_reboot_priv, true);

	अगर (turn_SMI_watchकरोg_clear_off >= p->iTCO_version) अणु
		/*
		 * Bit 13: TCO_EN -> 0
		 * Disables TCO logic generating an SMI#
		 */
		val32 = inl(SMI_EN(p));
		val32 &= 0xffffdfff;	/* Turn off SMI clearing watchकरोg */
		outl(val32, SMI_EN(p));
	पूर्ण

	अगर (!devm_request_region(dev, p->tco_res->start,
				 resource_size(p->tco_res),
				 pdev->name)) अणु
		dev_err(dev, "I/O address 0x%04llx already in use, device disabled\n",
		       (u64)TCOBASE(p));
		वापस -EBUSY;
	पूर्ण

	dev_info(dev, "Found a %s TCO device (Version=%d, TCOBASE=0x%04llx)\n",
		pdata->name, pdata->version, (u64)TCOBASE(p));

	/* Clear out the (probably old) status */
	चयन (p->iTCO_version) अणु
	हाल 6:
	हाल 5:
	हाल 4:
		outw(0x0008, TCO1_STS(p)); /* Clear the Time Out Status bit */
		outw(0x0002, TCO2_STS(p)); /* Clear SECOND_TO_STS bit */
		अवरोध;
	हाल 3:
		outl(0x20008, TCO1_STS(p));
		अवरोध;
	हाल 2:
	हाल 1:
	शेष:
		outw(0x0008, TCO1_STS(p)); /* Clear the Time Out Status bit */
		outw(0x0002, TCO2_STS(p)); /* Clear SECOND_TO_STS bit */
		outw(0x0004, TCO2_STS(p)); /* Clear BOOT_STS bit */
		अवरोध;
	पूर्ण

	p->wddev.info = &ident,
	p->wddev.ops = &iTCO_wdt_ops,
	p->wddev.bootstatus = 0;
	p->wddev.समयout = WATCHDOG_TIMEOUT;
	watchकरोg_set_nowayout(&p->wddev, nowayout);
	p->wddev.parent = dev;

	watchकरोg_set_drvdata(&p->wddev, p);
	platक्रमm_set_drvdata(pdev, p);

	/* Make sure the watchकरोg is not running */
	iTCO_wdt_stop(&p->wddev);

	/* Check that the heartbeat value is within it's range;
	   अगर not reset to the शेष */
	अगर (iTCO_wdt_set_समयout(&p->wddev, heartbeat)) अणु
		iTCO_wdt_set_समयout(&p->wddev, WATCHDOG_TIMEOUT);
		dev_info(dev, "timeout value out of range, using %d\n",
			WATCHDOG_TIMEOUT);
	पूर्ण

	watchकरोg_stop_on_reboot(&p->wddev);
	watchकरोg_stop_on_unरेजिस्टर(&p->wddev);
	ret = devm_watchकरोg_रेजिस्टर_device(dev, &p->wddev);
	अगर (ret != 0) अणु
		dev_err(dev, "cannot register watchdog device (err=%d)\n", ret);
		वापस ret;
	पूर्ण

	dev_info(dev, "initialized. heartbeat=%d sec (nowayout=%d)\n",
		heartbeat, nowayout);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/*
 * Suspend-to-idle requires this, because it stops the ticks and समयkeeping, so
 * the watchकरोg cannot be pinged जबतक in that state.  In ACPI sleep states the
 * watchकरोg is stopped by the platक्रमm firmware.
 */

#अगर_घोषित CONFIG_ACPI
अटल अंतरभूत bool need_suspend(व्योम)
अणु
	वापस acpi_target_प्रणाली_state() == ACPI_STATE_S0;
पूर्ण
#अन्यथा
अटल अंतरभूत bool need_suspend(व्योम) अणु वापस true; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक iTCO_wdt_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा iTCO_wdt_निजी *p = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	p->suspended = false;
	अगर (watchकरोg_active(&p->wddev) && need_suspend()) अणु
		ret = iTCO_wdt_stop(&p->wddev);
		अगर (!ret)
			p->suspended = true;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक iTCO_wdt_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा iTCO_wdt_निजी *p = dev_get_drvdata(dev);

	अगर (p->suspended)
		iTCO_wdt_start(&p->wddev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops iTCO_wdt_pm = अणु
	.suspend_noirq = iTCO_wdt_suspend_noirq,
	.resume_noirq = iTCO_wdt_resume_noirq,
पूर्ण;

#घोषणा ITCO_WDT_PM_OPS	(&iTCO_wdt_pm)
#अन्यथा
#घोषणा ITCO_WDT_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा platक्रमm_driver iTCO_wdt_driver = अणु
	.probe          = iTCO_wdt_probe,
	.driver         = अणु
		.name   = DRV_NAME,
		.pm     = ITCO_WDT_PM_OPS,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(iTCO_wdt_driver);

MODULE_AUTHOR("Wim Van Sebroeck <wim@iguana.be>");
MODULE_DESCRIPTION("Intel TCO WatchDog Timer Driver");
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
