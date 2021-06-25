<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright IBM Corporation 2001, 2005, 2006
 * Copyright Dave Engebretsen & Todd Inglett 2001
 * Copyright Linas Vepstas 2005, 2006
 * Copyright 2001-2012 IBM Corporation.
 *
 * Please address comments and feedback to Linas Vepstas <linas@austin.ibm.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/iommu.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/reboot.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/of.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/eeh.h>
#समावेश <यंत्र/eeh_event.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/pte-walk.h>


/** Overview:
 *  EEH, or "Enhanced Error Handling" is a PCI bridge technology क्रम
 *  dealing with PCI bus errors that can't be dealt with within the
 *  usual PCI framework, except by check-stopping the CPU.  Systems
 *  that are deचिन्हित क्रम high-availability/reliability cannot afक्रमd
 *  to crash due to a "mere" PCI error, thus the need क्रम EEH.
 *  An EEH-capable bridge operates by converting a detected error
 *  पूर्णांकo a "slot freeze", taking the PCI adapter off-line, making
 *  the slot behave, from the OS'es poपूर्णांक of view, as अगर the slot
 *  were "empty": all पढ़ोs वापस 0xff's and all ग_लिखोs are silently
 *  ignored.  EEH slot isolation events can be triggered by parity
 *  errors on the address or data busses (e.g. during posted ग_लिखोs),
 *  which in turn might be caused by low voltage on the bus, dust,
 *  vibration, humidity, radioactivity or plain-old failed hardware.
 *
 *  Note, however, that one of the leading causes of EEH slot
 *  मुक्तze events are buggy device drivers, buggy device microcode,
 *  or buggy device hardware.  This is because any attempt by the
 *  device to bus-master data to a memory address that is not
 *  asचिन्हित to the device will trigger a slot मुक्तze.   (The idea
 *  is to prevent devices-gone-wild from corrupting प्रणाली memory).
 *  Buggy hardware/drivers will have a miserable समय co-existing
 *  with EEH.
 *
 *  Ideally, a PCI device driver, when suspecting that an isolation
 *  event has occurred (e.g. by पढ़ोing 0xff's), will then ask EEH
 *  whether this is the हाल, and then take appropriate steps to
 *  reset the PCI slot, the PCI device, and then resume operations.
 *  However, until that day,  the checking is करोne here, with the
 *  eeh_check_failure() routine embedded in the MMIO macros.  If
 *  the slot is found to be isolated, an "EEH Event" is synthesized
 *  and sent out क्रम processing.
 */

/* If a device driver keeps पढ़ोing an MMIO रेजिस्टर in an पूर्णांकerrupt
 * handler after a slot isolation event, it might be broken.
 * This sets the threshold क्रम how many पढ़ो attempts we allow
 * beक्रमe prपूर्णांकing an error message.
 */
#घोषणा EEH_MAX_FAILS	2100000

/* Time to रुको क्रम a PCI slot to report status, in milliseconds */
#घोषणा PCI_BUS_RESET_WAIT_MSEC (5*60*1000)

/*
 * EEH probe mode support, which is part of the flags,
 * is to support multiple platक्रमms क्रम EEH. Some platक्रमms
 * like pSeries करो PCI emunation based on device tree.
 * However, other platक्रमms like घातernv probe PCI devices
 * from hardware. The flag is used to distinguish that.
 * In addition, काष्ठा eeh_ops::probe would be invoked क्रम
 * particular OF node or PCI device so that the corresponding
 * PE would be created there.
 */
पूर्णांक eeh_subप्रणाली_flags;
EXPORT_SYMBOL(eeh_subप्रणाली_flags);

/*
 * EEH allowed maximal frozen बार. If one particular PE's
 * frozen count in last hour exceeds this limit, the PE will
 * be क्रमced to be offline permanently.
 */
u32 eeh_max_मुक्तzes = 5;

/*
 * Controls whether a recovery event should be scheduled when an
 * isolated device is discovered. This is only really useful क्रम
 * debugging problems with the EEH core.
 */
bool eeh_debugfs_no_recover;

/* Platक्रमm dependent EEH operations */
काष्ठा eeh_ops *eeh_ops = शून्य;

/* Lock to aव्योम races due to multiple reports of an error */
DEFINE_RAW_SPINLOCK(confirm_error_lock);
EXPORT_SYMBOL_GPL(confirm_error_lock);

/* Lock to protect passed flags */
अटल DEFINE_MUTEX(eeh_dev_mutex);

/* Buffer क्रम reporting pci रेजिस्टर dumps. Its here in BSS, and
 * not dynamically alloced, so that it ends up in RMO where RTAS
 * can access it.
 */
#घोषणा EEH_PCI_REGS_LOG_LEN 8192
अटल अचिन्हित अक्षर pci_regs_buf[EEH_PCI_REGS_LOG_LEN];

/*
 * The काष्ठा is used to मुख्यtain the EEH global statistic
 * inक्रमmation. Besides, the EEH global statistics will be
 * exported to user space through procfs
 */
काष्ठा eeh_stats अणु
	u64 no_device;		/* PCI device not found		*/
	u64 no_dn;		/* OF node not found		*/
	u64 no_cfg_addr;	/* Config address not found	*/
	u64 ignored_check;	/* EEH check skipped		*/
	u64 total_mmio_ffs;	/* Total EEH checks		*/
	u64 false_positives;	/* Unnecessary EEH checks	*/
	u64 slot_resets;	/* PE reset			*/
पूर्ण;

अटल काष्ठा eeh_stats eeh_stats;

अटल पूर्णांक __init eeh_setup(अक्षर *str)
अणु
	अगर (!म_भेद(str, "off"))
		eeh_add_flag(EEH_FORCE_DISABLED);
	अन्यथा अगर (!म_भेद(str, "early_log"))
		eeh_add_flag(EEH_EARLY_DUMP_LOG);

	वापस 1;
पूर्ण
__setup("eeh=", eeh_setup);

व्योम eeh_show_enabled(व्योम)
अणु
	अगर (eeh_has_flag(EEH_FORCE_DISABLED))
		pr_info("EEH: Recovery disabled by kernel parameter.\n");
	अन्यथा अगर (eeh_has_flag(EEH_ENABLED))
		pr_info("EEH: Capable adapter found: recovery enabled.\n");
	अन्यथा
		pr_info("EEH: No capable adapters found: recovery disabled.\n");
पूर्ण

/*
 * This routine captures assorted PCI configuration space data
 * क्रम the indicated PCI device, and माला_दो them पूर्णांकo a buffer
 * क्रम RTAS error logging.
 */
अटल माप_प्रकार eeh_dump_dev_log(काष्ठा eeh_dev *edev, अक्षर *buf, माप_प्रकार len)
अणु
	u32 cfg;
	पूर्णांक cap, i;
	पूर्णांक n = 0, l = 0;
	अक्षर buffer[128];

	n += scnम_लिखो(buf+n, len-n, "%04x:%02x:%02x.%01x\n",
			edev->pe->phb->global_number, edev->bdfn >> 8,
			PCI_SLOT(edev->bdfn), PCI_FUNC(edev->bdfn));
	pr_warn("EEH: of node=%04x:%02x:%02x.%01x\n",
		edev->pe->phb->global_number, edev->bdfn >> 8,
		PCI_SLOT(edev->bdfn), PCI_FUNC(edev->bdfn));

	eeh_ops->पढ़ो_config(edev, PCI_VENDOR_ID, 4, &cfg);
	n += scnम_लिखो(buf+n, len-n, "dev/vend:%08x\n", cfg);
	pr_warn("EEH: PCI device/vendor: %08x\n", cfg);

	eeh_ops->पढ़ो_config(edev, PCI_COMMAND, 4, &cfg);
	n += scnम_लिखो(buf+n, len-n, "cmd/stat:%x\n", cfg);
	pr_warn("EEH: PCI cmd/status register: %08x\n", cfg);

	/* Gather bridge-specअगरic रेजिस्टरs */
	अगर (edev->mode & EEH_DEV_BRIDGE) अणु
		eeh_ops->पढ़ो_config(edev, PCI_SEC_STATUS, 2, &cfg);
		n += scnम_लिखो(buf+n, len-n, "sec stat:%x\n", cfg);
		pr_warn("EEH: Bridge secondary status: %04x\n", cfg);

		eeh_ops->पढ़ो_config(edev, PCI_BRIDGE_CONTROL, 2, &cfg);
		n += scnम_लिखो(buf+n, len-n, "brdg ctl:%x\n", cfg);
		pr_warn("EEH: Bridge control: %04x\n", cfg);
	पूर्ण

	/* Dump out the PCI-X command and status regs */
	cap = edev->pcix_cap;
	अगर (cap) अणु
		eeh_ops->पढ़ो_config(edev, cap, 4, &cfg);
		n += scnम_लिखो(buf+n, len-n, "pcix-cmd:%x\n", cfg);
		pr_warn("EEH: PCI-X cmd: %08x\n", cfg);

		eeh_ops->पढ़ो_config(edev, cap+4, 4, &cfg);
		n += scnम_लिखो(buf+n, len-n, "pcix-stat:%x\n", cfg);
		pr_warn("EEH: PCI-X status: %08x\n", cfg);
	पूर्ण

	/* If PCI-E capable, dump PCI-E cap 10 */
	cap = edev->pcie_cap;
	अगर (cap) अणु
		n += scnम_लिखो(buf+n, len-n, "pci-e cap10:\n");
		pr_warn("EEH: PCI-E capabilities and status follow:\n");

		क्रम (i=0; i<=8; i++) अणु
			eeh_ops->पढ़ो_config(edev, cap+4*i, 4, &cfg);
			n += scnम_लिखो(buf+n, len-n, "%02x:%x\n", 4*i, cfg);

			अगर ((i % 4) == 0) अणु
				अगर (i != 0)
					pr_warn("%s\n", buffer);

				l = scnम_लिखो(buffer, माप(buffer),
					      "EEH: PCI-E %02x: %08x ",
					      4*i, cfg);
			पूर्ण अन्यथा अणु
				l += scnम_लिखो(buffer+l, माप(buffer)-l,
					       "%08x ", cfg);
			पूर्ण

		पूर्ण

		pr_warn("%s\n", buffer);
	पूर्ण

	/* If AER capable, dump it */
	cap = edev->aer_cap;
	अगर (cap) अणु
		n += scnम_लिखो(buf+n, len-n, "pci-e AER:\n");
		pr_warn("EEH: PCI-E AER capability register set follows:\n");

		क्रम (i=0; i<=13; i++) अणु
			eeh_ops->पढ़ो_config(edev, cap+4*i, 4, &cfg);
			n += scnम_लिखो(buf+n, len-n, "%02x:%x\n", 4*i, cfg);

			अगर ((i % 4) == 0) अणु
				अगर (i != 0)
					pr_warn("%s\n", buffer);

				l = scnम_लिखो(buffer, माप(buffer),
					      "EEH: PCI-E AER %02x: %08x ",
					      4*i, cfg);
			पूर्ण अन्यथा अणु
				l += scnम_लिखो(buffer+l, माप(buffer)-l,
					       "%08x ", cfg);
			पूर्ण
		पूर्ण

		pr_warn("%s\n", buffer);
	पूर्ण

	वापस n;
पूर्ण

अटल व्योम *eeh_dump_pe_log(काष्ठा eeh_pe *pe, व्योम *flag)
अणु
	काष्ठा eeh_dev *edev, *पंचांगp;
	माप_प्रकार *plen = flag;

	eeh_pe_क्रम_each_dev(pe, edev, पंचांगp)
		*plen += eeh_dump_dev_log(edev, pci_regs_buf + *plen,
					  EEH_PCI_REGS_LOG_LEN - *plen);

	वापस शून्य;
पूर्ण

/**
 * eeh_slot_error_detail - Generate combined log including driver log and error log
 * @pe: EEH PE
 * @severity: temporary or permanent error log
 *
 * This routine should be called to generate the combined log, which
 * is comprised of driver log and error log. The driver log is figured
 * out from the config space of the corresponding PCI device, जबतक
 * the error log is fetched through platक्रमm dependent function call.
 */
व्योम eeh_slot_error_detail(काष्ठा eeh_pe *pe, पूर्णांक severity)
अणु
	माप_प्रकार loglen = 0;

	/*
	 * When the PHB is fenced or dead, it's poपूर्णांकless to collect
	 * the data from PCI config space because it should वापस
	 * 0xFF's. For ER, we still retrieve the data from the PCI
	 * config space.
	 *
	 * For pHyp, we have to enable IO क्रम log retrieval. Otherwise,
	 * 0xFF's is always वापसed from PCI config space.
	 *
	 * When the @severity is EEH_LOG_PERM, the PE is going to be
	 * हटाओd. Prior to that, the drivers क्रम devices included in
	 * the PE will be बंदd. The drivers rely on working IO path
	 * to bring the devices to quiet state. Otherwise, PCI traffic
	 * from those devices after they are हटाओd is like to cause
	 * another unexpected EEH error.
	 */
	अगर (!(pe->type & EEH_PE_PHB)) अणु
		अगर (eeh_has_flag(EEH_ENABLE_IO_FOR_LOG) ||
		    severity == EEH_LOG_PERM)
			eeh_pci_enable(pe, EEH_OPT_THAW_MMIO);

		/*
		 * The config space of some PCI devices can't be accessed
		 * when their PEs are in frozen state. Otherwise, fenced
		 * PHB might be seen. Those PEs are identअगरied with flag
		 * EEH_PE_CFG_RESTRICTED, indicating EEH_PE_CFG_BLOCKED
		 * is set स्वतःmatically when the PE is put to EEH_PE_ISOLATED.
		 *
		 * Restoring BARs possibly triggers PCI config access in
		 * (OPAL) firmware and then causes fenced PHB. If the
		 * PCI config is blocked with flag EEH_PE_CFG_BLOCKED, it's
		 * poपूर्णांकless to restore BARs and dump config space.
		 */
		eeh_ops->configure_bridge(pe);
		अगर (!(pe->state & EEH_PE_CFG_BLOCKED)) अणु
			eeh_pe_restore_bars(pe);

			pci_regs_buf[0] = 0;
			eeh_pe_traverse(pe, eeh_dump_pe_log, &loglen);
		पूर्ण
	पूर्ण

	eeh_ops->get_log(pe, severity, pci_regs_buf, loglen);
पूर्ण

/**
 * eeh_token_to_phys - Convert EEH address token to phys address
 * @token: I/O token, should be address in the क्रमm 0xA....
 *
 * This routine should be called to convert भव I/O address
 * to physical one.
 */
अटल अंतरभूत अचिन्हित दीर्घ eeh_token_to_phys(अचिन्हित दीर्घ token)
अणु
	वापस ppc_find_vmap_phys(token);
पूर्ण

/*
 * On PowerNV platक्रमm, we might alपढ़ोy have fenced PHB there.
 * For that हाल, it's meaningless to recover frozen PE. Intead,
 * We have to handle fenced PHB firstly.
 */
अटल पूर्णांक eeh_phb_check_failure(काष्ठा eeh_pe *pe)
अणु
	काष्ठा eeh_pe *phb_pe;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!eeh_has_flag(EEH_PROBE_MODE_DEV))
		वापस -EPERM;

	/* Find the PHB PE */
	phb_pe = eeh_phb_pe_get(pe->phb);
	अगर (!phb_pe) अणु
		pr_warn("%s Can't find PE for PHB#%x\n",
			__func__, pe->phb->global_number);
		वापस -EEXIST;
	पूर्ण

	/* If the PHB has been in problematic state */
	eeh_serialize_lock(&flags);
	अगर (phb_pe->state & EEH_PE_ISOLATED) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/* Check PHB state */
	ret = eeh_ops->get_state(phb_pe, शून्य);
	अगर ((ret < 0) ||
	    (ret == EEH_STATE_NOT_SUPPORT) || eeh_state_active(ret)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/* Isolate the PHB and send event */
	eeh_pe_mark_isolated(phb_pe);
	eeh_serialize_unlock(flags);

	pr_debug("EEH: PHB#%x failure detected, location: %s\n",
		phb_pe->phb->global_number, eeh_pe_loc_get(phb_pe));
	eeh_send_failure_event(phb_pe);
	वापस 1;
out:
	eeh_serialize_unlock(flags);
	वापस ret;
पूर्ण

/**
 * eeh_dev_check_failure - Check अगर all 1's data is due to EEH slot मुक्तze
 * @edev: eeh device
 *
 * Check क्रम an EEH failure क्रम the given device node.  Call this
 * routine अगर the result of a पढ़ो was all 0xff's and you want to
 * find out अगर this is due to an EEH slot मुक्तze.  This routine
 * will query firmware क्रम the EEH status.
 *
 * Returns 0 अगर there has not been an EEH error; otherwise वापसs
 * a non-zero value and queues up a slot isolation event notअगरication.
 *
 * It is safe to call this routine in an पूर्णांकerrupt context.
 */
पूर्णांक eeh_dev_check_failure(काष्ठा eeh_dev *edev)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा device_node *dn;
	काष्ठा pci_dev *dev;
	काष्ठा eeh_pe *pe, *parent_pe;
	पूर्णांक rc = 0;
	स्थिर अक्षर *location = शून्य;

	eeh_stats.total_mmio_ffs++;

	अगर (!eeh_enabled())
		वापस 0;

	अगर (!edev) अणु
		eeh_stats.no_dn++;
		वापस 0;
	पूर्ण
	dev = eeh_dev_to_pci_dev(edev);
	pe = eeh_dev_to_pe(edev);

	/* Access to IO BARs might get this far and still not want checking. */
	अगर (!pe) अणु
		eeh_stats.ignored_check++;
		eeh_edev_dbg(edev, "Ignored check\n");
		वापस 0;
	पूर्ण

	/*
	 * On PowerNV platक्रमm, we might alपढ़ोy have fenced PHB
	 * there and we need take care of that firstly.
	 */
	ret = eeh_phb_check_failure(pe);
	अगर (ret > 0)
		वापस ret;

	/*
	 * If the PE isn't owned by us, we shouldn't check the
	 * state. Instead, let the owner handle it अगर the PE has
	 * been frozen.
	 */
	अगर (eeh_pe_passed(pe))
		वापस 0;

	/* If we alपढ़ोy have a pending isolation event क्रम this
	 * slot, we know it's bad already, we don't need to check.
	 * Do this checking under a lock; as multiple PCI devices
	 * in one slot might report errors simultaneously, and we
	 * only want one error recovery routine running.
	 */
	eeh_serialize_lock(&flags);
	rc = 1;
	अगर (pe->state & EEH_PE_ISOLATED) अणु
		pe->check_count++;
		अगर (pe->check_count == EEH_MAX_FAILS) अणु
			dn = pci_device_to_OF_node(dev);
			अगर (dn)
				location = of_get_property(dn, "ibm,loc-code",
						शून्य);
			eeh_edev_err(edev, "%d reads ignored for recovering device at location=%s driver=%s\n",
				pe->check_count,
				location ? location : "unknown",
				eeh_driver_name(dev));
			eeh_edev_err(edev, "Might be infinite loop in %s driver\n",
				eeh_driver_name(dev));
			dump_stack();
		पूर्ण
		जाओ dn_unlock;
	पूर्ण

	/*
	 * Now test क्रम an EEH failure.  This is VERY expensive.
	 * Note that the eeh_config_addr may be a parent device
	 * in the हाल of a device behind a bridge, or it may be
	 * function zero of a multi-function device.
	 * In any हाल they must share a common PHB.
	 */
	ret = eeh_ops->get_state(pe, शून्य);

	/* Note that config-io to empty slots may fail;
	 * they are empty when they करोn't have children.
	 * We will punt with the following conditions: Failure to get
	 * PE's state, EEH not support and Permanently unavailable
	 * state, PE is in good state.
	 */
	अगर ((ret < 0) ||
	    (ret == EEH_STATE_NOT_SUPPORT) || eeh_state_active(ret)) अणु
		eeh_stats.false_positives++;
		pe->false_positives++;
		rc = 0;
		जाओ dn_unlock;
	पूर्ण

	/*
	 * It should be corner हाल that the parent PE has been
	 * put पूर्णांकo frozen state as well. We should take care
	 * that at first.
	 */
	parent_pe = pe->parent;
	जबतक (parent_pe) अणु
		/* Hit the उच्चमानing ? */
		अगर (parent_pe->type & EEH_PE_PHB)
			अवरोध;

		/* Frozen parent PE ? */
		ret = eeh_ops->get_state(parent_pe, शून्य);
		अगर (ret > 0 && !eeh_state_active(ret)) अणु
			pe = parent_pe;
			pr_err("EEH: Failure of PHB#%x-PE#%x will be handled at parent PHB#%x-PE#%x.\n",
			       pe->phb->global_number, pe->addr,
			       pe->phb->global_number, parent_pe->addr);
		पूर्ण

		/* Next parent level */
		parent_pe = parent_pe->parent;
	पूर्ण

	eeh_stats.slot_resets++;

	/* Aव्योम repeated reports of this failure, including problems
	 * with other functions on this device, and functions under
	 * bridges.
	 */
	eeh_pe_mark_isolated(pe);
	eeh_serialize_unlock(flags);

	/* Most EEH events are due to device driver bugs.  Having
	 * a stack trace will help the device-driver authors figure
	 * out what happened.  So prपूर्णांक that out.
	 */
	pr_debug("EEH: %s: Frozen PHB#%x-PE#%x detected\n",
		__func__, pe->phb->global_number, pe->addr);
	eeh_send_failure_event(pe);

	वापस 1;

dn_unlock:
	eeh_serialize_unlock(flags);
	वापस rc;
पूर्ण

EXPORT_SYMBOL_GPL(eeh_dev_check_failure);

/**
 * eeh_check_failure - Check अगर all 1's data is due to EEH slot मुक्तze
 * @token: I/O address
 *
 * Check क्रम an EEH failure at the given I/O address. Call this
 * routine अगर the result of a पढ़ो was all 0xff's and you want to
 * find out अगर this is due to an EEH slot मुक्तze event. This routine
 * will query firmware क्रम the EEH status.
 *
 * Note this routine is safe to call in an पूर्णांकerrupt context.
 */
पूर्णांक eeh_check_failure(स्थिर अस्थिर व्योम __iomem *token)
अणु
	अचिन्हित दीर्घ addr;
	काष्ठा eeh_dev *edev;

	/* Finding the phys addr + pci device; this is pretty quick. */
	addr = eeh_token_to_phys((अचिन्हित दीर्घ __क्रमce) token);
	edev = eeh_addr_cache_get_dev(addr);
	अगर (!edev) अणु
		eeh_stats.no_device++;
		वापस 0;
	पूर्ण

	वापस eeh_dev_check_failure(edev);
पूर्ण
EXPORT_SYMBOL(eeh_check_failure);


/**
 * eeh_pci_enable - Enable MMIO or DMA transfers क्रम this slot
 * @pe: EEH PE
 *
 * This routine should be called to reenable frozen MMIO or DMA
 * so that it would work correctly again. It's useful जबतक करोing
 * recovery or log collection on the indicated device.
 */
पूर्णांक eeh_pci_enable(काष्ठा eeh_pe *pe, पूर्णांक function)
अणु
	पूर्णांक active_flag, rc;

	/*
	 * pHyp करोesn't allow to enable IO or DMA on unfrozen PE.
	 * Also, it's poपूर्णांकless to enable them on unfrozen PE. So
	 * we have to check beक्रमe enabling IO or DMA.
	 */
	चयन (function) अणु
	हाल EEH_OPT_THAW_MMIO:
		active_flag = EEH_STATE_MMIO_ACTIVE | EEH_STATE_MMIO_ENABLED;
		अवरोध;
	हाल EEH_OPT_THAW_DMA:
		active_flag = EEH_STATE_DMA_ACTIVE;
		अवरोध;
	हाल EEH_OPT_DISABLE:
	हाल EEH_OPT_ENABLE:
	हाल EEH_OPT_FREEZE_PE:
		active_flag = 0;
		अवरोध;
	शेष:
		pr_warn("%s: Invalid function %d\n",
			__func__, function);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check अगर IO or DMA has been enabled beक्रमe
	 * enabling them.
	 */
	अगर (active_flag) अणु
		rc = eeh_ops->get_state(pe, शून्य);
		अगर (rc < 0)
			वापस rc;

		/* Needn't enable it at all */
		अगर (rc == EEH_STATE_NOT_SUPPORT)
			वापस 0;

		/* It's alपढ़ोy enabled */
		अगर (rc & active_flag)
			वापस 0;
	पूर्ण


	/* Issue the request */
	rc = eeh_ops->set_option(pe, function);
	अगर (rc)
		pr_warn("%s: Unexpected state change %d on "
			"PHB#%x-PE#%x, err=%d\n",
			__func__, function, pe->phb->global_number,
			pe->addr, rc);

	/* Check अगर the request is finished successfully */
	अगर (active_flag) अणु
		rc = eeh_रुको_state(pe, PCI_BUS_RESET_WAIT_MSEC);
		अगर (rc < 0)
			वापस rc;

		अगर (rc & active_flag)
			वापस 0;

		वापस -EIO;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम eeh_disable_and_save_dev_state(काष्ठा eeh_dev *edev,
					    व्योम *userdata)
अणु
	काष्ठा pci_dev *pdev = eeh_dev_to_pci_dev(edev);
	काष्ठा pci_dev *dev = userdata;

	/*
	 * The caller should have disabled and saved the
	 * state क्रम the specअगरied device
	 */
	अगर (!pdev || pdev == dev)
		वापस;

	/* Ensure we have D0 घातer state */
	pci_set_घातer_state(pdev, PCI_D0);

	/* Save device state */
	pci_save_state(pdev);

	/*
	 * Disable device to aव्योम any DMA traffic and
	 * पूर्णांकerrupt from the device
	 */
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, PCI_COMMAND_INTX_DISABLE);
पूर्ण

अटल व्योम eeh_restore_dev_state(काष्ठा eeh_dev *edev, व्योम *userdata)
अणु
	काष्ठा pci_dev *pdev = eeh_dev_to_pci_dev(edev);
	काष्ठा pci_dev *dev = userdata;

	अगर (!pdev)
		वापस;

	/* Apply customization from firmware */
	अगर (eeh_ops->restore_config)
		eeh_ops->restore_config(edev);

	/* The caller should restore state क्रम the specअगरied device */
	अगर (pdev != dev)
		pci_restore_state(pdev);
पूर्ण

/**
 * pcibios_set_pcie_reset_state - Set PCI-E reset state
 * @dev: pci device काष्ठा
 * @state: reset state to enter
 *
 * Return value:
 * 	0 अगर success
 */
पूर्णांक pcibios_set_pcie_reset_state(काष्ठा pci_dev *dev, क्रमागत pcie_reset_state state)
अणु
	काष्ठा eeh_dev *edev = pci_dev_to_eeh_dev(dev);
	काष्ठा eeh_pe *pe = eeh_dev_to_pe(edev);

	अगर (!pe) अणु
		pr_err("%s: No PE found on PCI device %s\n",
			__func__, pci_name(dev));
		वापस -EINVAL;
	पूर्ण

	चयन (state) अणु
	हाल pcie_deनिश्चित_reset:
		eeh_ops->reset(pe, EEH_RESET_DEACTIVATE);
		eeh_unमुक्तze_pe(pe);
		अगर (!(pe->type & EEH_PE_VF))
			eeh_pe_state_clear(pe, EEH_PE_CFG_BLOCKED, true);
		eeh_pe_dev_traverse(pe, eeh_restore_dev_state, dev);
		eeh_pe_state_clear(pe, EEH_PE_ISOLATED, true);
		अवरोध;
	हाल pcie_hot_reset:
		eeh_pe_mark_isolated(pe);
		eeh_pe_state_clear(pe, EEH_PE_CFG_BLOCKED, true);
		eeh_ops->set_option(pe, EEH_OPT_FREEZE_PE);
		eeh_pe_dev_traverse(pe, eeh_disable_and_save_dev_state, dev);
		अगर (!(pe->type & EEH_PE_VF))
			eeh_pe_state_mark(pe, EEH_PE_CFG_BLOCKED);
		eeh_ops->reset(pe, EEH_RESET_HOT);
		अवरोध;
	हाल pcie_warm_reset:
		eeh_pe_mark_isolated(pe);
		eeh_pe_state_clear(pe, EEH_PE_CFG_BLOCKED, true);
		eeh_ops->set_option(pe, EEH_OPT_FREEZE_PE);
		eeh_pe_dev_traverse(pe, eeh_disable_and_save_dev_state, dev);
		अगर (!(pe->type & EEH_PE_VF))
			eeh_pe_state_mark(pe, EEH_PE_CFG_BLOCKED);
		eeh_ops->reset(pe, EEH_RESET_FUNDAMENTAL);
		अवरोध;
	शेष:
		eeh_pe_state_clear(pe, EEH_PE_ISOLATED | EEH_PE_CFG_BLOCKED, true);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * eeh_set_pe_freset - Check the required reset क्रम the indicated device
 * @data: EEH device
 * @flag: वापस value
 *
 * Each device might have its preferred reset type: fundamental or
 * hot reset. The routine is used to collected the inक्रमmation क्रम
 * the indicated device and its children so that the bunch of the
 * devices could be reset properly.
 */
अटल व्योम eeh_set_dev_freset(काष्ठा eeh_dev *edev, व्योम *flag)
अणु
	काष्ठा pci_dev *dev;
	अचिन्हित पूर्णांक *freset = (अचिन्हित पूर्णांक *)flag;

	dev = eeh_dev_to_pci_dev(edev);
	अगर (dev)
		*freset |= dev->needs_freset;
पूर्ण

अटल व्योम eeh_pe_reमुक्तze_passed(काष्ठा eeh_pe *root)
अणु
	काष्ठा eeh_pe *pe;
	पूर्णांक state;

	eeh_क्रम_each_pe(root, pe) अणु
		अगर (eeh_pe_passed(pe)) अणु
			state = eeh_ops->get_state(pe, शून्य);
			अगर (state &
			   (EEH_STATE_MMIO_ACTIVE | EEH_STATE_MMIO_ENABLED)) अणु
				pr_info("EEH: Passed-through PE PHB#%x-PE#%x was thawed by reset, re-freezing for safety.\n",
					pe->phb->global_number, pe->addr);
				eeh_pe_set_option(pe, EEH_OPT_FREEZE_PE);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * eeh_pe_reset_full - Complete a full reset process on the indicated PE
 * @pe: EEH PE
 *
 * This function executes a full reset procedure on a PE, including setting
 * the appropriate flags, perक्रमming a fundamental or hot reset, and then
 * deactivating the reset status.  It is deचिन्हित to be used within the EEH
 * subप्रणाली, as opposed to eeh_pe_reset which is exported to drivers and
 * only perक्रमms a single operation at a समय.
 *
 * This function will attempt to reset a PE three बार beक्रमe failing.
 */
पूर्णांक eeh_pe_reset_full(काष्ठा eeh_pe *pe, bool include_passed)
अणु
	पूर्णांक reset_state = (EEH_PE_RESET | EEH_PE_CFG_BLOCKED);
	पूर्णांक type = EEH_RESET_HOT;
	अचिन्हित पूर्णांक freset = 0;
	पूर्णांक i, state = 0, ret;

	/*
	 * Determine the type of reset to perक्रमm - hot or fundamental.
	 * Hot reset is the शेष operation, unless any device under the
	 * PE requires a fundamental reset.
	 */
	eeh_pe_dev_traverse(pe, eeh_set_dev_freset, &freset);

	अगर (freset)
		type = EEH_RESET_FUNDAMENTAL;

	/* Mark the PE as in reset state and block config space accesses */
	eeh_pe_state_mark(pe, reset_state);

	/* Make three attempts at resetting the bus */
	क्रम (i = 0; i < 3; i++) अणु
		ret = eeh_pe_reset(pe, type, include_passed);
		अगर (!ret)
			ret = eeh_pe_reset(pe, EEH_RESET_DEACTIVATE,
					   include_passed);
		अगर (ret) अणु
			ret = -EIO;
			pr_warn("EEH: Failure %d resetting PHB#%x-PE#%x (attempt %d)\n\n",
				state, pe->phb->global_number, pe->addr, i + 1);
			जारी;
		पूर्ण
		अगर (i)
			pr_warn("EEH: PHB#%x-PE#%x: Successful reset (attempt %d)\n",
				pe->phb->global_number, pe->addr, i + 1);

		/* Wait until the PE is in a functioning state */
		state = eeh_रुको_state(pe, PCI_BUS_RESET_WAIT_MSEC);
		अगर (state < 0) अणु
			pr_warn("EEH: Unrecoverable slot failure on PHB#%x-PE#%x",
				pe->phb->global_number, pe->addr);
			ret = -ENOTRECOVERABLE;
			अवरोध;
		पूर्ण
		अगर (eeh_state_active(state))
			अवरोध;
		अन्यथा
			pr_warn("EEH: PHB#%x-PE#%x: Slot inactive after reset: 0x%x (attempt %d)\n",
				pe->phb->global_number, pe->addr, state, i + 1);
	पूर्ण

	/* Resetting the PE may have unfrozen child PEs. If those PEs have been
	 * (potentially) passed through to a guest, re-मुक्तze them:
	 */
	अगर (!include_passed)
		eeh_pe_reमुक्तze_passed(pe);

	eeh_pe_state_clear(pe, reset_state, true);
	वापस ret;
पूर्ण

/**
 * eeh_save_bars - Save device bars
 * @edev: PCI device associated EEH device
 *
 * Save the values of the device bars. Unlike the restore
 * routine, this routine is *not* recursive. This is because
 * PCI devices are added inभागidually; but, क्रम the restore,
 * an entire slot is reset at a समय.
 */
व्योम eeh_save_bars(काष्ठा eeh_dev *edev)
अणु
	पूर्णांक i;

	अगर (!edev)
		वापस;

	क्रम (i = 0; i < 16; i++)
		eeh_ops->पढ़ो_config(edev, i * 4, 4, &edev->config_space[i]);

	/*
	 * For PCI bridges including root port, we need enable bus
	 * master explicitly. Otherwise, it can't fetch IODA table
	 * entries correctly. So we cache the bit in advance so that
	 * we can restore it after reset, either PHB range or PE range.
	 */
	अगर (edev->mode & EEH_DEV_BRIDGE)
		edev->config_space[1] |= PCI_COMMAND_MASTER;
पूर्ण

अटल पूर्णांक eeh_reboot_notअगरier(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ action, व्योम *unused)
अणु
	eeh_clear_flag(EEH_ENABLED);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block eeh_reboot_nb = अणु
	.notअगरier_call = eeh_reboot_notअगरier,
पूर्ण;

अटल पूर्णांक eeh_device_notअगरier(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;

	चयन (action) अणु
	/*
	 * Note: It's not possible to perक्रमm EEH device addition (i.e.
	 * अणुpseries,pnvपूर्ण_pcibios_bus_add_device()) here because it depends on
	 * the device's resources, which have not yet been set up.
	 */
	हाल BUS_NOTIFY_DEL_DEVICE:
		eeh_हटाओ_device(to_pci_dev(dev));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block eeh_device_nb = अणु
	.notअगरier_call = eeh_device_notअगरier,
पूर्ण;

/**
 * eeh_init - System wide EEH initialization
 *
 * It's the platform's job to call this from an arch_initcall().
 */
पूर्णांक eeh_init(काष्ठा eeh_ops *ops)
अणु
	काष्ठा pci_controller *hose, *पंचांगp;
	पूर्णांक ret = 0;

	/* the platक्रमm should only initialise EEH once */
	अगर (WARN_ON(eeh_ops))
		वापस -EEXIST;
	अगर (WARN_ON(!ops))
		वापस -ENOENT;
	eeh_ops = ops;

	/* Register reboot notअगरier */
	ret = रेजिस्टर_reboot_notअगरier(&eeh_reboot_nb);
	अगर (ret) अणु
		pr_warn("%s: Failed to register reboot notifier (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = bus_रेजिस्टर_notअगरier(&pci_bus_type, &eeh_device_nb);
	अगर (ret) अणु
		pr_warn("%s: Failed to register bus notifier (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* Initialize PHB PEs */
	list_क्रम_each_entry_safe(hose, पंचांगp, &hose_list, list_node)
		eeh_phb_pe_create(hose);

	eeh_addr_cache_init();

	/* Initialize EEH event */
	वापस eeh_event_init();
पूर्ण

/**
 * eeh_probe_device() - Perक्रमm EEH initialization क्रम the indicated pci device
 * @dev: pci device क्रम which to set up EEH
 *
 * This routine must be used to complete EEH initialization क्रम PCI
 * devices that were added after प्रणाली boot (e.g. hotplug, dlpar).
 */
व्योम eeh_probe_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा eeh_dev *edev;

	pr_debug("EEH: Adding device %s\n", pci_name(dev));

	/*
	 * pci_dev_to_eeh_dev() can only work अगर eeh_probe_dev() was
	 * alपढ़ोy called क्रम this device.
	 */
	अगर (WARN_ON_ONCE(pci_dev_to_eeh_dev(dev))) अणु
		pci_dbg(dev, "Already bound to an eeh_dev!\n");
		वापस;
	पूर्ण

	edev = eeh_ops->probe(dev);
	अगर (!edev) अणु
		pr_debug("EEH: Adding device failed\n");
		वापस;
	पूर्ण

	/*
	 * FIXME: We rely on pcibios_release_device() to हटाओ the
	 * existing EEH state. The release function is only called अगर
	 * the pci_dev's refcount drops to zero so अगर something is
	 * keeping a ref to a device (e.g. a fileप्रणाली) we need to
	 * हटाओ the old EEH state.
	 *
	 * FIXME: HEY MA, LOOK AT ME, NO LOCKING!
	 */
	अगर (edev->pdev && edev->pdev != dev) अणु
		eeh_pe_tree_हटाओ(edev);
		eeh_addr_cache_rmv_dev(edev->pdev);
		eeh_sysfs_हटाओ_device(edev->pdev);

		/*
		 * We definitely should have the PCI device हटाओd
		 * though it wasn't correctly. So we needn't call
		 * पूर्णांकo error handler afterwards.
		 */
		edev->mode |= EEH_DEV_NO_HANDLER;
	पूर्ण

	/* bind the pdev and the edev together */
	edev->pdev = dev;
	dev->dev.archdata.edev = edev;
	eeh_addr_cache_insert_dev(dev);
	eeh_sysfs_add_device(dev);
पूर्ण

/**
 * eeh_हटाओ_device - Unकरो EEH setup क्रम the indicated pci device
 * @dev: pci device to be हटाओd
 *
 * This routine should be called when a device is हटाओd from
 * a running प्रणाली (e.g. by hotplug or dlpar).  It unरेजिस्टरs
 * the PCI device from the EEH subप्रणाली.  I/O errors affecting
 * this device will no दीर्घer be detected after this call; thus,
 * i/o errors affecting this slot may leave this device unusable.
 */
व्योम eeh_हटाओ_device(काष्ठा pci_dev *dev)
अणु
	काष्ठा eeh_dev *edev;

	अगर (!dev || !eeh_enabled())
		वापस;
	edev = pci_dev_to_eeh_dev(dev);

	/* Unरेजिस्टर the device with the EEH/PCI address search प्रणाली */
	dev_dbg(&dev->dev, "EEH: Removing device\n");

	अगर (!edev || !edev->pdev || !edev->pe) अणु
		dev_dbg(&dev->dev, "EEH: Device not referenced!\n");
		वापस;
	पूर्ण

	/*
	 * During the hotplug क्रम EEH error recovery, we need the EEH
	 * device attached to the parent PE in order क्रम BAR restore
	 * a bit later. So we keep it क्रम BAR restore and हटाओ it
	 * from the parent PE during the BAR resotre.
	 */
	edev->pdev = शून्य;

	/*
	 * eeh_sysfs_हटाओ_device() uses pci_dev_to_eeh_dev() so we need to
	 * हटाओ the sysfs files beक्रमe clearing dev.archdata.edev
	 */
	अगर (edev->mode & EEH_DEV_SYSFS)
		eeh_sysfs_हटाओ_device(dev);

	/*
	 * We're removing from the PCI subप्रणाली, that means
	 * the PCI device driver can't support EEH or not
	 * well. So we rely on hotplug completely to करो recovery
	 * क्रम the specअगरic PCI device.
	 */
	edev->mode |= EEH_DEV_NO_HANDLER;

	eeh_addr_cache_rmv_dev(dev);

	/*
	 * The flag "in_error" is used to trace EEH devices क्रम VFs
	 * in error state or not. It's set in eeh_report_error(). If
	 * it's not set, eeh_report_{reset,resume}() won't be called
	 * क्रम the VF EEH device.
	 */
	edev->in_error = false;
	dev->dev.archdata.edev = शून्य;
	अगर (!(edev->pe->state & EEH_PE_KEEP))
		eeh_pe_tree_हटाओ(edev);
	अन्यथा
		edev->mode |= EEH_DEV_DISCONNECTED;
पूर्ण

पूर्णांक eeh_unमुक्तze_pe(काष्ठा eeh_pe *pe)
अणु
	पूर्णांक ret;

	ret = eeh_pci_enable(pe, EEH_OPT_THAW_MMIO);
	अगर (ret) अणु
		pr_warn("%s: Failure %d enabling IO on PHB#%x-PE#%x\n",
			__func__, ret, pe->phb->global_number, pe->addr);
		वापस ret;
	पूर्ण

	ret = eeh_pci_enable(pe, EEH_OPT_THAW_DMA);
	अगर (ret) अणु
		pr_warn("%s: Failure %d enabling DMA on PHB#%x-PE#%x\n",
			__func__, ret, pe->phb->global_number, pe->addr);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण


अटल काष्ठा pci_device_id eeh_reset_ids[] = अणु
	अणु PCI_DEVICE(0x19a2, 0x0710) पूर्ण,	/* Emulex, BE     */
	अणु PCI_DEVICE(0x10df, 0xe220) पूर्ण,	/* Emulex, Lancer */
	अणु PCI_DEVICE(0x14e4, 0x1657) पूर्ण, /* Broadcom BCM5719 */
	अणु 0 पूर्ण
पूर्ण;

अटल पूर्णांक eeh_pe_change_owner(काष्ठा eeh_pe *pe)
अणु
	काष्ठा eeh_dev *edev, *पंचांगp;
	काष्ठा pci_dev *pdev;
	काष्ठा pci_device_id *id;
	पूर्णांक ret;

	/* Check PE state */
	ret = eeh_ops->get_state(pe, शून्य);
	अगर (ret < 0 || ret == EEH_STATE_NOT_SUPPORT)
		वापस 0;

	/* Unfrozen PE, nothing to करो */
	अगर (eeh_state_active(ret))
		वापस 0;

	/* Frozen PE, check अगर it needs PE level reset */
	eeh_pe_क्रम_each_dev(pe, edev, पंचांगp) अणु
		pdev = eeh_dev_to_pci_dev(edev);
		अगर (!pdev)
			जारी;

		क्रम (id = &eeh_reset_ids[0]; id->venकरोr != 0; id++) अणु
			अगर (id->venकरोr != PCI_ANY_ID &&
			    id->venकरोr != pdev->venकरोr)
				जारी;
			अगर (id->device != PCI_ANY_ID &&
			    id->device != pdev->device)
				जारी;
			अगर (id->subvenकरोr != PCI_ANY_ID &&
			    id->subvenकरोr != pdev->subप्रणाली_venकरोr)
				जारी;
			अगर (id->subdevice != PCI_ANY_ID &&
			    id->subdevice != pdev->subप्रणाली_device)
				जारी;

			वापस eeh_pe_reset_and_recover(pe);
		पूर्ण
	पूर्ण

	ret = eeh_unमुक्तze_pe(pe);
	अगर (!ret)
		eeh_pe_state_clear(pe, EEH_PE_ISOLATED, true);
	वापस ret;
पूर्ण

/**
 * eeh_dev_खोलो - Increase count of pass through devices क्रम PE
 * @pdev: PCI device
 *
 * Increase count of passed through devices क्रम the indicated
 * PE. In the result, the EEH errors detected on the PE won't be
 * reported. The PE owner will be responsible क्रम detection
 * and recovery.
 */
पूर्णांक eeh_dev_खोलो(काष्ठा pci_dev *pdev)
अणु
	काष्ठा eeh_dev *edev;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&eeh_dev_mutex);

	/* No PCI device ? */
	अगर (!pdev)
		जाओ out;

	/* No EEH device or PE ? */
	edev = pci_dev_to_eeh_dev(pdev);
	अगर (!edev || !edev->pe)
		जाओ out;

	/*
	 * The PE might have been put पूर्णांकo frozen state, but we
	 * didn't detect that yet. The passed through PCI devices
	 * in frozen PE won't work properly. Clear the frozen state
	 * in advance.
	 */
	ret = eeh_pe_change_owner(edev->pe);
	अगर (ret)
		जाओ out;

	/* Increase PE's pass through count */
	atomic_inc(&edev->pe->pass_dev_cnt);
	mutex_unlock(&eeh_dev_mutex);

	वापस 0;
out:
	mutex_unlock(&eeh_dev_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(eeh_dev_खोलो);

/**
 * eeh_dev_release - Decrease count of pass through devices क्रम PE
 * @pdev: PCI device
 *
 * Decrease count of pass through devices क्रम the indicated PE. If
 * there is no passed through device in PE, the EEH errors detected
 * on the PE will be reported and handled as usual.
 */
व्योम eeh_dev_release(काष्ठा pci_dev *pdev)
अणु
	काष्ठा eeh_dev *edev;

	mutex_lock(&eeh_dev_mutex);

	/* No PCI device ? */
	अगर (!pdev)
		जाओ out;

	/* No EEH device ? */
	edev = pci_dev_to_eeh_dev(pdev);
	अगर (!edev || !edev->pe || !eeh_pe_passed(edev->pe))
		जाओ out;

	/* Decrease PE's pass through count */
	WARN_ON(atomic_dec_अगर_positive(&edev->pe->pass_dev_cnt) < 0);
	eeh_pe_change_owner(edev->pe);
out:
	mutex_unlock(&eeh_dev_mutex);
पूर्ण
EXPORT_SYMBOL(eeh_dev_release);

#अगर_घोषित CONFIG_IOMMU_API

अटल पूर्णांक dev_has_iommu_table(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pci_dev **ppdev = data;

	अगर (!dev)
		वापस 0;

	अगर (device_iommu_mapped(dev)) अणु
		*ppdev = pdev;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * eeh_iommu_group_to_pe - Convert IOMMU group to EEH PE
 * @group: IOMMU group
 *
 * The routine is called to convert IOMMU group to EEH PE.
 */
काष्ठा eeh_pe *eeh_iommu_group_to_pe(काष्ठा iommu_group *group)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	काष्ठा eeh_dev *edev;
	पूर्णांक ret;

	/* No IOMMU group ? */
	अगर (!group)
		वापस शून्य;

	ret = iommu_group_क्रम_each_dev(group, &pdev, dev_has_iommu_table);
	अगर (!ret || !pdev)
		वापस शून्य;

	/* No EEH device or PE ? */
	edev = pci_dev_to_eeh_dev(pdev);
	अगर (!edev || !edev->pe)
		वापस शून्य;

	वापस edev->pe;
पूर्ण
EXPORT_SYMBOL_GPL(eeh_iommu_group_to_pe);

#पूर्ण_अगर /* CONFIG_IOMMU_API */

/**
 * eeh_pe_set_option - Set options क्रम the indicated PE
 * @pe: EEH PE
 * @option: requested option
 *
 * The routine is called to enable or disable EEH functionality
 * on the indicated PE, to enable IO or DMA क्रम the frozen PE.
 */
पूर्णांक eeh_pe_set_option(काष्ठा eeh_pe *pe, पूर्णांक option)
अणु
	पूर्णांक ret = 0;

	/* Invalid PE ? */
	अगर (!pe)
		वापस -ENODEV;

	/*
	 * EEH functionality could possibly be disabled, just
	 * वापस error क्रम the हाल. And the EEH functinality
	 * isn't expected to be disabled on one specअगरic PE.
	 */
	चयन (option) अणु
	हाल EEH_OPT_ENABLE:
		अगर (eeh_enabled()) अणु
			ret = eeh_pe_change_owner(pe);
			अवरोध;
		पूर्ण
		ret = -EIO;
		अवरोध;
	हाल EEH_OPT_DISABLE:
		अवरोध;
	हाल EEH_OPT_THAW_MMIO:
	हाल EEH_OPT_THAW_DMA:
	हाल EEH_OPT_FREEZE_PE:
		अगर (!eeh_ops || !eeh_ops->set_option) अणु
			ret = -ENOENT;
			अवरोध;
		पूर्ण

		ret = eeh_pci_enable(pe, option);
		अवरोध;
	शेष:
		pr_debug("%s: Option %d out of range (%d, %d)\n",
			__func__, option, EEH_OPT_DISABLE, EEH_OPT_THAW_DMA);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(eeh_pe_set_option);

/**
 * eeh_pe_get_state - Retrieve PE's state
 * @pe: EEH PE
 *
 * Retrieve the PE's state, which includes 3 aspects: enabled
 * DMA, enabled IO and निश्चितed reset.
 */
पूर्णांक eeh_pe_get_state(काष्ठा eeh_pe *pe)
अणु
	पूर्णांक result, ret = 0;
	bool rst_active, dma_en, mmio_en;

	/* Existing PE ? */
	अगर (!pe)
		वापस -ENODEV;

	अगर (!eeh_ops || !eeh_ops->get_state)
		वापस -ENOENT;

	/*
	 * If the parent PE is owned by the host kernel and is undergoing
	 * error recovery, we should वापस the PE state as temporarily
	 * unavailable so that the error recovery on the guest is suspended
	 * until the recovery completes on the host.
	 */
	अगर (pe->parent &&
	    !(pe->state & EEH_PE_REMOVED) &&
	    (pe->parent->state & (EEH_PE_ISOLATED | EEH_PE_RECOVERING)))
		वापस EEH_PE_STATE_UNAVAIL;

	result = eeh_ops->get_state(pe, शून्य);
	rst_active = !!(result & EEH_STATE_RESET_ACTIVE);
	dma_en = !!(result & EEH_STATE_DMA_ENABLED);
	mmio_en = !!(result & EEH_STATE_MMIO_ENABLED);

	अगर (rst_active)
		ret = EEH_PE_STATE_RESET;
	अन्यथा अगर (dma_en && mmio_en)
		ret = EEH_PE_STATE_NORMAL;
	अन्यथा अगर (!dma_en && !mmio_en)
		ret = EEH_PE_STATE_STOPPED_IO_DMA;
	अन्यथा अगर (!dma_en && mmio_en)
		ret = EEH_PE_STATE_STOPPED_DMA;
	अन्यथा
		ret = EEH_PE_STATE_UNAVAIL;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(eeh_pe_get_state);

अटल पूर्णांक eeh_pe_reenable_devices(काष्ठा eeh_pe *pe, bool include_passed)
अणु
	काष्ठा eeh_dev *edev, *पंचांगp;
	काष्ठा pci_dev *pdev;
	पूर्णांक ret = 0;

	eeh_pe_restore_bars(pe);

	/*
	 * Reenable PCI devices as the devices passed
	 * through are always enabled beक्रमe the reset.
	 */
	eeh_pe_क्रम_each_dev(pe, edev, पंचांगp) अणु
		pdev = eeh_dev_to_pci_dev(edev);
		अगर (!pdev)
			जारी;

		ret = pci_reenable_device(pdev);
		अगर (ret) अणु
			pr_warn("%s: Failure %d reenabling %s\n",
				__func__, ret, pci_name(pdev));
			वापस ret;
		पूर्ण
	पूर्ण

	/* The PE is still in frozen state */
	अगर (include_passed || !eeh_pe_passed(pe)) अणु
		ret = eeh_unमुक्तze_pe(pe);
	पूर्ण अन्यथा
		pr_info("EEH: Note: Leaving passthrough PHB#%x-PE#%x frozen.\n",
			pe->phb->global_number, pe->addr);
	अगर (!ret)
		eeh_pe_state_clear(pe, EEH_PE_ISOLATED, include_passed);
	वापस ret;
पूर्ण


/**
 * eeh_pe_reset - Issue PE reset according to specअगरied type
 * @pe: EEH PE
 * @option: reset type
 *
 * The routine is called to reset the specअगरied PE with the
 * indicated type, either fundamental reset or hot reset.
 * PE reset is the most important part क्रम error recovery.
 */
पूर्णांक eeh_pe_reset(काष्ठा eeh_pe *pe, पूर्णांक option, bool include_passed)
अणु
	पूर्णांक ret = 0;

	/* Invalid PE ? */
	अगर (!pe)
		वापस -ENODEV;

	अगर (!eeh_ops || !eeh_ops->set_option || !eeh_ops->reset)
		वापस -ENOENT;

	चयन (option) अणु
	हाल EEH_RESET_DEACTIVATE:
		ret = eeh_ops->reset(pe, option);
		eeh_pe_state_clear(pe, EEH_PE_CFG_BLOCKED, include_passed);
		अगर (ret)
			अवरोध;

		ret = eeh_pe_reenable_devices(pe, include_passed);
		अवरोध;
	हाल EEH_RESET_HOT:
	हाल EEH_RESET_FUNDAMENTAL:
		/*
		 * Proactively मुक्तze the PE to drop all MMIO access
		 * during reset, which should be banned as it's always
		 * cause recursive EEH error.
		 */
		eeh_ops->set_option(pe, EEH_OPT_FREEZE_PE);

		eeh_pe_state_mark(pe, EEH_PE_CFG_BLOCKED);
		ret = eeh_ops->reset(pe, option);
		अवरोध;
	शेष:
		pr_debug("%s: Unsupported option %d\n",
			__func__, option);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(eeh_pe_reset);

/**
 * eeh_pe_configure - Configure PCI bridges after PE reset
 * @pe: EEH PE
 *
 * The routine is called to restore the PCI config space क्रम
 * those PCI devices, especially PCI bridges affected by PE
 * reset issued previously.
 */
पूर्णांक eeh_pe_configure(काष्ठा eeh_pe *pe)
अणु
	पूर्णांक ret = 0;

	/* Invalid PE ? */
	अगर (!pe)
		वापस -ENODEV;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(eeh_pe_configure);

/**
 * eeh_pe_inject_err - Injecting the specअगरied PCI error to the indicated PE
 * @pe: the indicated PE
 * @type: error type
 * @function: error function
 * @addr: address
 * @mask: address mask
 *
 * The routine is called to inject the specअगरied PCI error, which
 * is determined by @type and @function, to the indicated PE क्रम
 * testing purpose.
 */
पूर्णांक eeh_pe_inject_err(काष्ठा eeh_pe *pe, पूर्णांक type, पूर्णांक func,
		      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ mask)
अणु
	/* Invalid PE ? */
	अगर (!pe)
		वापस -ENODEV;

	/* Unsupported operation ? */
	अगर (!eeh_ops || !eeh_ops->err_inject)
		वापस -ENOENT;

	/* Check on PCI error type */
	अगर (type != EEH_ERR_TYPE_32 && type != EEH_ERR_TYPE_64)
		वापस -EINVAL;

	/* Check on PCI error function */
	अगर (func < EEH_ERR_FUNC_MIN || func > EEH_ERR_FUNC_MAX)
		वापस -EINVAL;

	वापस eeh_ops->err_inject(pe, type, func, addr, mask);
पूर्ण
EXPORT_SYMBOL_GPL(eeh_pe_inject_err);

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक proc_eeh_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (!eeh_enabled()) अणु
		seq_म_लिखो(m, "EEH Subsystem is globally disabled\n");
		seq_म_लिखो(m, "eeh_total_mmio_ffs=%llu\n", eeh_stats.total_mmio_ffs);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "EEH Subsystem is enabled\n");
		seq_म_लिखो(m,
				"no device=%llu\n"
				"no device node=%llu\n"
				"no config address=%llu\n"
				"check not wanted=%llu\n"
				"eeh_total_mmio_ffs=%llu\n"
				"eeh_false_positives=%llu\n"
				"eeh_slot_resets=%llu\n",
				eeh_stats.no_device,
				eeh_stats.no_dn,
				eeh_stats.no_cfg_addr,
				eeh_stats.ignored_check,
				eeh_stats.total_mmio_ffs,
				eeh_stats.false_positives,
				eeh_stats.slot_resets);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

#अगर_घोषित CONFIG_DEBUG_FS


अटल काष्ठा pci_dev *eeh_debug_lookup_pdev(काष्ठा file *filp,
					     स्थिर अक्षर __user *user_buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	uपूर्णांक32_t करोमुख्य, bus, dev, fn;
	काष्ठा pci_dev *pdev;
	अक्षर buf[20];
	पूर्णांक ret;

	स_रखो(buf, 0, माप(buf));
	ret = simple_ग_लिखो_to_buffer(buf, माप(buf)-1, ppos, user_buf, count);
	अगर (!ret)
		वापस ERR_PTR(-EFAULT);

	ret = माला_पूछो(buf, "%x:%x:%x.%x", &करोमुख्य, &bus, &dev, &fn);
	अगर (ret != 4) अणु
		pr_err("%s: expected 4 args, got %d\n", __func__, ret);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, bus, (dev << 3) | fn);
	अगर (!pdev)
		वापस ERR_PTR(-ENODEV);

	वापस pdev;
पूर्ण

अटल पूर्णांक eeh_enable_dbgfs_set(व्योम *data, u64 val)
अणु
	अगर (val)
		eeh_clear_flag(EEH_FORCE_DISABLED);
	अन्यथा
		eeh_add_flag(EEH_FORCE_DISABLED);

	वापस 0;
पूर्ण

अटल पूर्णांक eeh_enable_dbgfs_get(व्योम *data, u64 *val)
अणु
	अगर (eeh_enabled())
		*val = 0x1ul;
	अन्यथा
		*val = 0x0ul;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(eeh_enable_dbgfs_ops, eeh_enable_dbgfs_get,
			 eeh_enable_dbgfs_set, "0x%llx\n");

अटल sमाप_प्रकार eeh_क्रमce_recover_ग_लिखो(काष्ठा file *filp,
				स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pci_controller *hose;
	uपूर्णांक32_t phbid, pe_no;
	काष्ठा eeh_pe *pe;
	अक्षर buf[20];
	पूर्णांक ret;

	ret = simple_ग_लिखो_to_buffer(buf, माप(buf), ppos, user_buf, count);
	अगर (!ret)
		वापस -EFAULT;

	/*
	 * When PE is शून्य the event is a "special" event. Rather than
	 * recovering a specअगरic PE it क्रमces the EEH core to scan क्रम failed
	 * PHBs and recovers each. This needs to be करोne beक्रमe any device
	 * recoveries can occur.
	 */
	अगर (!म_भेदन(buf, "hwcheck", 7)) अणु
		__eeh_send_failure_event(शून्य);
		वापस count;
	पूर्ण

	ret = माला_पूछो(buf, "%x:%x", &phbid, &pe_no);
	अगर (ret != 2)
		वापस -EINVAL;

	hose = pci_find_controller_क्रम_करोमुख्य(phbid);
	अगर (!hose)
		वापस -ENODEV;

	/* Retrieve PE */
	pe = eeh_pe_get(hose, pe_no);
	अगर (!pe)
		वापस -ENODEV;

	/*
	 * We करोn't करो any state checking here since the detection
	 * process is async to the recovery process. The recovery
	 * thपढ़ो *should* not अवरोध even अगर we schedule a recovery
	 * from an odd state (e.g. PE हटाओd, or recovery of a
	 * non-isolated PE)
	 */
	__eeh_send_failure_event(pe);

	वापस ret < 0 ? ret : count;
पूर्ण

अटल स्थिर काष्ठा file_operations eeh_क्रमce_recover_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek	= no_llseek,
	.ग_लिखो	= eeh_क्रमce_recover_ग_लिखो,
पूर्ण;

अटल sमाप_प्रकार eeh_debugfs_dev_usage(काष्ठा file *filp,
				अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	अटल स्थिर अक्षर usage[] = "input format: <domain>:<bus>:<dev>.<fn>\n";

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,
				       usage, माप(usage) - 1);
पूर्ण

अटल sमाप_प्रकार eeh_dev_check_ग_लिखो(काष्ठा file *filp,
				स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा eeh_dev *edev;
	पूर्णांक ret;

	pdev = eeh_debug_lookup_pdev(filp, user_buf, count, ppos);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	edev = pci_dev_to_eeh_dev(pdev);
	अगर (!edev) अणु
		pci_err(pdev, "No eeh_dev for this device!\n");
		pci_dev_put(pdev);
		वापस -ENODEV;
	पूर्ण

	ret = eeh_dev_check_failure(edev);
	pci_info(pdev, "eeh_dev_check_failure(%s) = %d\n",
			pci_name(pdev), ret);

	pci_dev_put(pdev);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations eeh_dev_check_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek	= no_llseek,
	.ग_लिखो	= eeh_dev_check_ग_लिखो,
	.पढ़ो   = eeh_debugfs_dev_usage,
पूर्ण;

अटल पूर्णांक eeh_debugfs_अवरोध_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा resource *bar = शून्य;
	व्योम __iomem *mapped;
	u16 old, bit;
	पूर्णांक i, pos;

	/* Do we have an MMIO BAR to disable? */
	क्रम (i = 0; i <= PCI_STD_RESOURCE_END; i++) अणु
		काष्ठा resource *r = &pdev->resource[i];

		अगर (!r->flags || !r->start)
			जारी;
		अगर (r->flags & IORESOURCE_IO)
			जारी;
		अगर (r->flags & IORESOURCE_UNSET)
			जारी;

		bar = r;
		अवरोध;
	पूर्ण

	अगर (!bar) अणु
		pci_err(pdev, "Unable to find Memory BAR to cause EEH with\n");
		वापस -ENXIO;
	पूर्ण

	pci_err(pdev, "Going to break: %pR\n", bar);

	अगर (pdev->is_virtfn) अणु
#अगर_अघोषित CONFIG_PCI_IOV
		वापस -ENXIO;
#अन्यथा
		/*
		 * VFs करोn't have a per-function COMMAND रेजिस्टर, so the best
		 * we can करो is clear the Memory Space Enable bit in the PF's
		 * SRIOV control reg.
		 *
		 * Unक्रमtunately, this requires that we have a PF (i.e करोesn't
		 * work क्रम a passed-through VF) and it has the potential side
		 * effect of also causing an EEH on every other VF under the
		 * PF. Oh well.
		 */
		pdev = pdev->physfn;
		अगर (!pdev)
			वापस -ENXIO; /* passed through VFs have no PF */

		pos  = pci_find_ext_capability(pdev, PCI_EXT_CAP_ID_SRIOV);
		pos += PCI_SRIOV_CTRL;
		bit  = PCI_SRIOV_CTRL_MSE;
#पूर्ण_अगर /* !CONFIG_PCI_IOV */
	पूर्ण अन्यथा अणु
		bit = PCI_COMMAND_MEMORY;
		pos = PCI_COMMAND;
	पूर्ण

	/*
	 * Process here is:
	 *
	 * 1. Disable Memory space.
	 *
	 * 2. Perक्रमm an MMIO to the device. This should result in an error
	 *    (CA  / UR) being उठाओd by the device which results in an EEH
	 *    PE मुक्तze. Using the in_8() accessor skips the eeh detection hook
	 *    so the मुक्तze hook so the EEH Detection machinery won't be
	 *    triggered here. This is to match the usual behaviour of EEH
	 *    where the HW will asyncronously मुक्तze a PE and it's up to
	 *    the kernel to notice and deal with it.
	 *
	 * 3. Turn Memory space back on. This is more important क्रम VFs
	 *    since recovery will probably fail अगर we करोn't. For normal
	 *    the COMMAND रेजिस्टर is reset as a part of re-initialising
	 *    the device.
	 *
	 * Breaking stuff is the poपूर्णांक so who cares अगर it's racy ;)
	 */
	pci_पढ़ो_config_word(pdev, pos, &old);

	mapped = ioremap(bar->start, PAGE_SIZE);
	अगर (!mapped) अणु
		pci_err(pdev, "Unable to map MMIO BAR %pR\n", bar);
		वापस -ENXIO;
	पूर्ण

	pci_ग_लिखो_config_word(pdev, pos, old & ~bit);
	in_8(mapped);
	pci_ग_लिखो_config_word(pdev, pos, old);

	iounmap(mapped);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार eeh_dev_अवरोध_ग_लिखो(काष्ठा file *filp,
				स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pci_dev *pdev;
	पूर्णांक ret;

	pdev = eeh_debug_lookup_pdev(filp, user_buf, count, ppos);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	ret = eeh_debugfs_अवरोध_device(pdev);
	pci_dev_put(pdev);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations eeh_dev_अवरोध_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek	= no_llseek,
	.ग_लिखो	= eeh_dev_अवरोध_ग_लिखो,
	.पढ़ो   = eeh_debugfs_dev_usage,
पूर्ण;

अटल sमाप_प्रकार eeh_dev_can_recover(काष्ठा file *filp,
				   स्थिर अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pci_driver *drv;
	काष्ठा pci_dev *pdev;
	माप_प्रकार ret;

	pdev = eeh_debug_lookup_pdev(filp, user_buf, count, ppos);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	/*
	 * In order क्रम error recovery to work the driver needs to implement
	 * .error_detected(), so it can quiesce IO to the device, and
	 * .slot_reset() so it can re-initialise the device after a reset.
	 *
	 * Ideally they'd implement .resume() too, but some drivers which
	 * we need to support (notably IPR) करोn't so I guess we can tolerate
	 * that.
	 *
	 * .mmio_enabled() is mostly there as a work-around क्रम devices which
	 * take क्रमever to re-init after a hot reset. Implementing that is
	 * strictly optional.
	 */
	drv = pci_dev_driver(pdev);
	अगर (drv &&
	    drv->err_handler &&
	    drv->err_handler->error_detected &&
	    drv->err_handler->slot_reset) अणु
		ret = count;
	पूर्ण अन्यथा अणु
		ret = -EOPNOTSUPP;
	पूर्ण

	pci_dev_put(pdev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations eeh_dev_can_recover_fops = अणु
	.खोलो	= simple_खोलो,
	.llseek	= no_llseek,
	.ग_लिखो	= eeh_dev_can_recover,
	.पढ़ो   = eeh_debugfs_dev_usage,
पूर्ण;

#पूर्ण_अगर

अटल पूर्णांक __init eeh_init_proc(व्योम)
अणु
	अगर (machine_is(pseries) || machine_is(घातernv)) अणु
		proc_create_single("powerpc/eeh", 0, शून्य, proc_eeh_show);
#अगर_घोषित CONFIG_DEBUG_FS
		debugfs_create_file_unsafe("eeh_enable", 0600,
					   घातerpc_debugfs_root, शून्य,
					   &eeh_enable_dbgfs_ops);
		debugfs_create_u32("eeh_max_freezes", 0600,
				घातerpc_debugfs_root, &eeh_max_मुक्तzes);
		debugfs_create_bool("eeh_disable_recovery", 0600,
				घातerpc_debugfs_root,
				&eeh_debugfs_no_recover);
		debugfs_create_file_unsafe("eeh_dev_check", 0600,
				घातerpc_debugfs_root, शून्य,
				&eeh_dev_check_fops);
		debugfs_create_file_unsafe("eeh_dev_break", 0600,
				घातerpc_debugfs_root, शून्य,
				&eeh_dev_अवरोध_fops);
		debugfs_create_file_unsafe("eeh_force_recover", 0600,
				घातerpc_debugfs_root, शून्य,
				&eeh_क्रमce_recover_fops);
		debugfs_create_file_unsafe("eeh_dev_can_recover", 0600,
				घातerpc_debugfs_root, शून्य,
				&eeh_dev_can_recover_fops);
		eeh_cache_debugfs_init();
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण
__initcall(eeh_init_proc);
