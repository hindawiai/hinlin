<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IOSF-SB MailBox Interface Driver
 * Copyright (c) 2013, Intel Corporation.
 *
 * The IOSF-SB is a fabric bus available on Atom based SOC's that uses a
 * mailbox पूर्णांकerface (MBI) to communicate with multiple devices. This
 * driver implements access to this पूर्णांकerface क्रम those platक्रमms that can
 * क्रमागतerate the device using PCI.
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/capability.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/रुको.h>

#समावेश <यंत्र/iosf_mbi.h>

#घोषणा PCI_DEVICE_ID_INTEL_BAYTRAIL		0x0F00
#घोषणा PCI_DEVICE_ID_INTEL_BRASWELL		0x2280
#घोषणा PCI_DEVICE_ID_INTEL_QUARK_X1000		0x0958
#घोषणा PCI_DEVICE_ID_INTEL_TANGIER		0x1170

अटल काष्ठा pci_dev *mbi_pdev;
अटल DEFINE_SPINLOCK(iosf_mbi_lock);

/**************** Generic iosf_mbi access helpers ****************/

अटल अंतरभूत u32 iosf_mbi_क्रमm_mcr(u8 op, u8 port, u8 offset)
अणु
	वापस (op << 24) | (port << 16) | (offset << 8) | MBI_ENABLE;
पूर्ण

अटल पूर्णांक iosf_mbi_pci_पढ़ो_mdr(u32 mcrx, u32 mcr, u32 *mdr)
अणु
	पूर्णांक result;

	अगर (!mbi_pdev)
		वापस -ENODEV;

	अगर (mcrx) अणु
		result = pci_ग_लिखो_config_dword(mbi_pdev, MBI_MCRX_OFFSET,
						mcrx);
		अगर (result < 0)
			जाओ fail_पढ़ो;
	पूर्ण

	result = pci_ग_लिखो_config_dword(mbi_pdev, MBI_MCR_OFFSET, mcr);
	अगर (result < 0)
		जाओ fail_पढ़ो;

	result = pci_पढ़ो_config_dword(mbi_pdev, MBI_MDR_OFFSET, mdr);
	अगर (result < 0)
		जाओ fail_पढ़ो;

	वापस 0;

fail_पढ़ो:
	dev_err(&mbi_pdev->dev, "PCI config access failed with %d\n", result);
	वापस result;
पूर्ण

अटल पूर्णांक iosf_mbi_pci_ग_लिखो_mdr(u32 mcrx, u32 mcr, u32 mdr)
अणु
	पूर्णांक result;

	अगर (!mbi_pdev)
		वापस -ENODEV;

	result = pci_ग_लिखो_config_dword(mbi_pdev, MBI_MDR_OFFSET, mdr);
	अगर (result < 0)
		जाओ fail_ग_लिखो;

	अगर (mcrx) अणु
		result = pci_ग_लिखो_config_dword(mbi_pdev, MBI_MCRX_OFFSET,
						mcrx);
		अगर (result < 0)
			जाओ fail_ग_लिखो;
	पूर्ण

	result = pci_ग_लिखो_config_dword(mbi_pdev, MBI_MCR_OFFSET, mcr);
	अगर (result < 0)
		जाओ fail_ग_लिखो;

	वापस 0;

fail_ग_लिखो:
	dev_err(&mbi_pdev->dev, "PCI config access failed with %d\n", result);
	वापस result;
पूर्ण

पूर्णांक iosf_mbi_पढ़ो(u8 port, u8 opcode, u32 offset, u32 *mdr)
अणु
	u32 mcr, mcrx;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Access to the GFX unit is handled by GPU code */
	अगर (port == BT_MBI_UNIT_GFX) अणु
		WARN_ON(1);
		वापस -EPERM;
	पूर्ण

	mcr = iosf_mbi_क्रमm_mcr(opcode, port, offset & MBI_MASK_LO);
	mcrx = offset & MBI_MASK_HI;

	spin_lock_irqsave(&iosf_mbi_lock, flags);
	ret = iosf_mbi_pci_पढ़ो_mdr(mcrx, mcr, mdr);
	spin_unlock_irqrestore(&iosf_mbi_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iosf_mbi_पढ़ो);

पूर्णांक iosf_mbi_ग_लिखो(u8 port, u8 opcode, u32 offset, u32 mdr)
अणु
	u32 mcr, mcrx;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Access to the GFX unit is handled by GPU code */
	अगर (port == BT_MBI_UNIT_GFX) अणु
		WARN_ON(1);
		वापस -EPERM;
	पूर्ण

	mcr = iosf_mbi_क्रमm_mcr(opcode, port, offset & MBI_MASK_LO);
	mcrx = offset & MBI_MASK_HI;

	spin_lock_irqsave(&iosf_mbi_lock, flags);
	ret = iosf_mbi_pci_ग_लिखो_mdr(mcrx, mcr, mdr);
	spin_unlock_irqrestore(&iosf_mbi_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iosf_mbi_ग_लिखो);

पूर्णांक iosf_mbi_modअगरy(u8 port, u8 opcode, u32 offset, u32 mdr, u32 mask)
अणु
	u32 mcr, mcrx;
	u32 value;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* Access to the GFX unit is handled by GPU code */
	अगर (port == BT_MBI_UNIT_GFX) अणु
		WARN_ON(1);
		वापस -EPERM;
	पूर्ण

	mcr = iosf_mbi_क्रमm_mcr(opcode, port, offset & MBI_MASK_LO);
	mcrx = offset & MBI_MASK_HI;

	spin_lock_irqsave(&iosf_mbi_lock, flags);

	/* Read current mdr value */
	ret = iosf_mbi_pci_पढ़ो_mdr(mcrx, mcr & MBI_RD_MASK, &value);
	अगर (ret < 0) अणु
		spin_unlock_irqrestore(&iosf_mbi_lock, flags);
		वापस ret;
	पूर्ण

	/* Apply mask */
	value &= ~mask;
	mdr &= mask;
	value |= mdr;

	/* Write back */
	ret = iosf_mbi_pci_ग_लिखो_mdr(mcrx, mcr | MBI_WR_MASK, value);

	spin_unlock_irqrestore(&iosf_mbi_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iosf_mbi_modअगरy);

bool iosf_mbi_available(व्योम)
अणु
	/* Mbi isn't hot-pluggable. No हटाओ routine is provided */
	वापस mbi_pdev;
पूर्ण
EXPORT_SYMBOL(iosf_mbi_available);

/*
 **************** P-Unit/kernel shared I2C bus arbitration ****************
 *
 * Some Bay Trail and Cherry Trail devices have the P-Unit and us (the kernel)
 * share a single I2C bus to the PMIC. Below are helpers to arbitrate the
 * accesses between the kernel and the P-Unit.
 *
 * See arch/x86/include/यंत्र/iosf_mbi.h क्रम kernel-करोc text क्रम each function.
 */

#घोषणा SEMAPHORE_TIMEOUT		500
#घोषणा PUNIT_SEMAPHORE_BYT		0x7
#घोषणा PUNIT_SEMAPHORE_CHT		0x10e
#घोषणा PUNIT_SEMAPHORE_BIT		BIT(0)
#घोषणा PUNIT_SEMAPHORE_ACQUIRE		BIT(1)

अटल DEFINE_MUTEX(iosf_mbi_pmic_access_mutex);
अटल BLOCKING_NOTIFIER_HEAD(iosf_mbi_pmic_bus_access_notअगरier);
अटल DECLARE_WAIT_QUEUE_HEAD(iosf_mbi_pmic_access_रुकोq);
अटल u32 iosf_mbi_pmic_punit_access_count;
अटल u32 iosf_mbi_pmic_i2c_access_count;
अटल u32 iosf_mbi_sem_address;
अटल अचिन्हित दीर्घ iosf_mbi_sem_acquired;
अटल काष्ठा pm_qos_request iosf_mbi_pm_qos;

व्योम iosf_mbi_punit_acquire(व्योम)
अणु
	/* Wait क्रम any I2C PMIC accesses from in kernel drivers to finish. */
	mutex_lock(&iosf_mbi_pmic_access_mutex);
	जबतक (iosf_mbi_pmic_i2c_access_count != 0) अणु
		mutex_unlock(&iosf_mbi_pmic_access_mutex);
		रुको_event(iosf_mbi_pmic_access_रुकोq,
			   iosf_mbi_pmic_i2c_access_count == 0);
		mutex_lock(&iosf_mbi_pmic_access_mutex);
	पूर्ण
	/*
	 * We करो not need to करो anything to allow the PUNIT to safely access
	 * the PMIC, other then block in kernel accesses to the PMIC.
	 */
	iosf_mbi_pmic_punit_access_count++;
	mutex_unlock(&iosf_mbi_pmic_access_mutex);
पूर्ण
EXPORT_SYMBOL(iosf_mbi_punit_acquire);

व्योम iosf_mbi_punit_release(व्योम)
अणु
	bool करो_wakeup;

	mutex_lock(&iosf_mbi_pmic_access_mutex);
	iosf_mbi_pmic_punit_access_count--;
	करो_wakeup = iosf_mbi_pmic_punit_access_count == 0;
	mutex_unlock(&iosf_mbi_pmic_access_mutex);

	अगर (करो_wakeup)
		wake_up(&iosf_mbi_pmic_access_रुकोq);
पूर्ण
EXPORT_SYMBOL(iosf_mbi_punit_release);

अटल पूर्णांक iosf_mbi_get_sem(u32 *sem)
अणु
	पूर्णांक ret;

	ret = iosf_mbi_पढ़ो(BT_MBI_UNIT_PMC, MBI_REG_READ,
			    iosf_mbi_sem_address, sem);
	अगर (ret) अणु
		dev_err(&mbi_pdev->dev, "Error P-Unit semaphore read failed\n");
		वापस ret;
	पूर्ण

	*sem &= PUNIT_SEMAPHORE_BIT;
	वापस 0;
पूर्ण

अटल व्योम iosf_mbi_reset_semaphore(व्योम)
अणु
	अगर (iosf_mbi_modअगरy(BT_MBI_UNIT_PMC, MBI_REG_READ,
			    iosf_mbi_sem_address, 0, PUNIT_SEMAPHORE_BIT))
		dev_err(&mbi_pdev->dev, "Error P-Unit semaphore reset failed\n");

	cpu_latency_qos_update_request(&iosf_mbi_pm_qos, PM_QOS_DEFAULT_VALUE);

	blocking_notअगरier_call_chain(&iosf_mbi_pmic_bus_access_notअगरier,
				     MBI_PMIC_BUS_ACCESS_END, शून्य);
पूर्ण

/*
 * This function blocks P-Unit accesses to the PMIC I2C bus, so that kernel
 * I2C code, such as e.g. a fuel-gauge driver, can access it safely.
 *
 * This function may be called by I2C controller code जबतक an I2C driver has
 * alपढ़ोy blocked P-Unit accesses because it wants them blocked over multiple
 * i2c-transfers, क्रम e.g. पढ़ो-modअगरy-ग_लिखो of an I2C client रेजिस्टर.
 *
 * To allow safe PMIC i2c bus accesses this function takes the following steps:
 *
 * 1) Some code sends request to the P-Unit which make it access the PMIC
 *    I2C bus. Testing has shown that the P-Unit करोes not check its पूर्णांकernal
 *    PMIC bus semaphore क्रम these requests. Callers of these requests call
 *    iosf_mbi_punit_acquire()/_release() around their P-Unit accesses, these
 *    functions increase/decrease iosf_mbi_pmic_punit_access_count, so first
 *    we रुको क्रम iosf_mbi_pmic_punit_access_count to become 0.
 *
 * 2) Check iosf_mbi_pmic_i2c_access_count, अगर access has alपढ़ोy
 *    been blocked by another caller, we only need to increment
 *    iosf_mbi_pmic_i2c_access_count and we can skip the other steps.
 *
 * 3) Some code makes such P-Unit requests from atomic contexts where it
 *    cannot call iosf_mbi_punit_acquire() as that may sleep.
 *    As the second step we call a notअगरier chain which allows any code
 *    needing P-Unit resources from atomic context to acquire them beक्रमe
 *    we take control over the PMIC I2C bus.
 *
 * 4) When CPU cores enter C6 or C7 the P-Unit needs to talk to the PMIC
 *    अगर this happens जबतक the kernel itself is accessing the PMIC I2C bus
 *    the SoC hangs.
 *    As the third step we call cpu_latency_qos_update_request() to disallow the
 *    CPU to enter C6 or C7.
 *
 * 5) The P-Unit has a PMIC bus semaphore which we can request to stop
 *    स्वतःnomous P-Unit tasks from accessing the PMIC I2C bus जबतक we hold it.
 *    As the fourth and final step we request this semaphore and रुको क्रम our
 *    request to be acknowledged.
 */
पूर्णांक iosf_mbi_block_punit_i2c_access(व्योम)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक ret = 0;
	u32 sem;

	अगर (WARN_ON(!mbi_pdev || !iosf_mbi_sem_address))
		वापस -ENXIO;

	mutex_lock(&iosf_mbi_pmic_access_mutex);

	जबतक (iosf_mbi_pmic_punit_access_count != 0) अणु
		mutex_unlock(&iosf_mbi_pmic_access_mutex);
		रुको_event(iosf_mbi_pmic_access_रुकोq,
			   iosf_mbi_pmic_punit_access_count == 0);
		mutex_lock(&iosf_mbi_pmic_access_mutex);
	पूर्ण

	अगर (iosf_mbi_pmic_i2c_access_count > 0)
		जाओ success;

	blocking_notअगरier_call_chain(&iosf_mbi_pmic_bus_access_notअगरier,
				     MBI_PMIC_BUS_ACCESS_BEGIN, शून्य);

	/*
	 * Disallow the CPU to enter C6 or C7 state, entering these states
	 * requires the P-Unit to talk to the PMIC and अगर this happens जबतक
	 * we're holding the semaphore, the SoC hangs.
	 */
	cpu_latency_qos_update_request(&iosf_mbi_pm_qos, 0);

	/* host driver ग_लिखोs to side band semaphore रेजिस्टर */
	ret = iosf_mbi_ग_लिखो(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
			     iosf_mbi_sem_address, PUNIT_SEMAPHORE_ACQUIRE);
	अगर (ret) अणु
		dev_err(&mbi_pdev->dev, "Error P-Unit semaphore request failed\n");
		जाओ error;
	पूर्ण

	/* host driver रुकोs क्रम bit 0 to be set in semaphore रेजिस्टर */
	start = jअगरfies;
	end = start + msecs_to_jअगरfies(SEMAPHORE_TIMEOUT);
	करो अणु
		ret = iosf_mbi_get_sem(&sem);
		अगर (!ret && sem) अणु
			iosf_mbi_sem_acquired = jअगरfies;
			dev_dbg(&mbi_pdev->dev, "P-Unit semaphore acquired after %ums\n",
				jअगरfies_to_msecs(jअगरfies - start));
			जाओ success;
		पूर्ण

		usleep_range(1000, 2000);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	ret = -ETIMEDOUT;
	dev_err(&mbi_pdev->dev, "Error P-Unit semaphore timed out, resetting\n");
error:
	iosf_mbi_reset_semaphore();
	अगर (!iosf_mbi_get_sem(&sem))
		dev_err(&mbi_pdev->dev, "P-Unit semaphore: %d\n", sem);
success:
	अगर (!WARN_ON(ret))
		iosf_mbi_pmic_i2c_access_count++;

	mutex_unlock(&iosf_mbi_pmic_access_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iosf_mbi_block_punit_i2c_access);

व्योम iosf_mbi_unblock_punit_i2c_access(व्योम)
अणु
	bool करो_wakeup = false;

	mutex_lock(&iosf_mbi_pmic_access_mutex);
	iosf_mbi_pmic_i2c_access_count--;
	अगर (iosf_mbi_pmic_i2c_access_count == 0) अणु
		iosf_mbi_reset_semaphore();
		dev_dbg(&mbi_pdev->dev, "punit semaphore held for %ums\n",
			jअगरfies_to_msecs(jअगरfies - iosf_mbi_sem_acquired));
		करो_wakeup = true;
	पूर्ण
	mutex_unlock(&iosf_mbi_pmic_access_mutex);

	अगर (करो_wakeup)
		wake_up(&iosf_mbi_pmic_access_रुकोq);
पूर्ण
EXPORT_SYMBOL(iosf_mbi_unblock_punit_i2c_access);

पूर्णांक iosf_mbi_रेजिस्टर_pmic_bus_access_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret;

	/* Wait क्रम the bus to go inactive beक्रमe रेजिस्टरing */
	iosf_mbi_punit_acquire();
	ret = blocking_notअगरier_chain_रेजिस्टर(
				&iosf_mbi_pmic_bus_access_notअगरier, nb);
	iosf_mbi_punit_release();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iosf_mbi_रेजिस्टर_pmic_bus_access_notअगरier);

पूर्णांक iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier_unlocked(
	काष्ठा notअगरier_block *nb)
अणु
	iosf_mbi_निश्चित_punit_acquired();

	वापस blocking_notअगरier_chain_unरेजिस्टर(
				&iosf_mbi_pmic_bus_access_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL(iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier_unlocked);

पूर्णांक iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret;

	/* Wait क्रम the bus to go inactive beक्रमe unरेजिस्टरing */
	iosf_mbi_punit_acquire();
	ret = iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier_unlocked(nb);
	iosf_mbi_punit_release();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier);

व्योम iosf_mbi_निश्चित_punit_acquired(व्योम)
अणु
	WARN_ON(iosf_mbi_pmic_punit_access_count == 0);
पूर्ण
EXPORT_SYMBOL(iosf_mbi_निश्चित_punit_acquired);

/**************** iosf_mbi debug code ****************/

#अगर_घोषित CONFIG_IOSF_MBI_DEBUG
अटल u32	dbg_mdr;
अटल u32	dbg_mcr;
अटल u32	dbg_mcrx;

अटल पूर्णांक mcr_get(व्योम *data, u64 *val)
अणु
	*val = *(u32 *)data;
	वापस 0;
पूर्ण

अटल पूर्णांक mcr_set(व्योम *data, u64 val)
अणु
	u8 command = ((u32)val & 0xFF000000) >> 24,
	   port	   = ((u32)val & 0x00FF0000) >> 16,
	   offset  = ((u32)val & 0x0000FF00) >> 8;
	पूर्णांक err;

	*(u32 *)data = val;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EACCES;

	अगर (command & 1u)
		err = iosf_mbi_ग_लिखो(port,
			       command,
			       dbg_mcrx | offset,
			       dbg_mdr);
	अन्यथा
		err = iosf_mbi_पढ़ो(port,
			      command,
			      dbg_mcrx | offset,
			      &dbg_mdr);

	वापस err;
पूर्ण
DEFINE_SIMPLE_ATTRIBUTE(iosf_mcr_fops, mcr_get, mcr_set , "%llx\n");

अटल काष्ठा dentry *iosf_dbg;

अटल व्योम iosf_sideband_debug_init(व्योम)
अणु
	iosf_dbg = debugfs_create_dir("iosf_sb", शून्य);

	/* mdr */
	debugfs_create_x32("mdr", 0660, iosf_dbg, &dbg_mdr);

	/* mcrx */
	debugfs_create_x32("mcrx", 0660, iosf_dbg, &dbg_mcrx);

	/* mcr - initiates mailbox transaction */
	debugfs_create_file("mcr", 0660, iosf_dbg, &dbg_mcr, &iosf_mcr_fops);
पूर्ण

अटल व्योम iosf_debugfs_init(व्योम)
अणु
	iosf_sideband_debug_init();
पूर्ण

अटल व्योम iosf_debugfs_हटाओ(व्योम)
अणु
	debugfs_हटाओ_recursive(iosf_dbg);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम iosf_debugfs_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम iosf_debugfs_हटाओ(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_IOSF_MBI_DEBUG */

अटल पूर्णांक iosf_mbi_probe(काष्ठा pci_dev *pdev,
			  स्थिर काष्ठा pci_device_id *dev_id)
अणु
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "error: could not enable device\n");
		वापस ret;
	पूर्ण

	mbi_pdev = pci_dev_get(pdev);
	iosf_mbi_sem_address = dev_id->driver_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id iosf_mbi_pci_ids[] = अणु
	अणु PCI_DEVICE_DATA(INTEL, BAYTRAIL, PUNIT_SEMAPHORE_BYT) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, BRASWELL, PUNIT_SEMAPHORE_CHT) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, QUARK_X1000, 0) पूर्ण,
	अणु PCI_DEVICE_DATA(INTEL, TANGIER, 0) पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, iosf_mbi_pci_ids);

अटल काष्ठा pci_driver iosf_mbi_pci_driver = अणु
	.name		= "iosf_mbi_pci",
	.probe		= iosf_mbi_probe,
	.id_table	= iosf_mbi_pci_ids,
पूर्ण;

अटल पूर्णांक __init iosf_mbi_init(व्योम)
अणु
	iosf_debugfs_init();

	cpu_latency_qos_add_request(&iosf_mbi_pm_qos, PM_QOS_DEFAULT_VALUE);

	वापस pci_रेजिस्टर_driver(&iosf_mbi_pci_driver);
पूर्ण

अटल व्योम __निकास iosf_mbi_निकास(व्योम)
अणु
	iosf_debugfs_हटाओ();

	pci_unरेजिस्टर_driver(&iosf_mbi_pci_driver);
	pci_dev_put(mbi_pdev);
	mbi_pdev = शून्य;

	cpu_latency_qos_हटाओ_request(&iosf_mbi_pm_qos);
पूर्ण

module_init(iosf_mbi_init);
module_निकास(iosf_mbi_निकास);

MODULE_AUTHOR("David E. Box <david.e.box@linux.intel.com>");
MODULE_DESCRIPTION("IOSF Mailbox Interface accessor");
MODULE_LICENSE("GPL v2");
