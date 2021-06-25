<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/रुको.h>

#समावेश "pci.h"

/*
 * This पूर्णांकerrupt-safe spinlock protects all accesses to PCI
 * configuration space.
 */

DEFINE_RAW_SPINLOCK(pci_lock);

/*
 * Wrappers क्रम all PCI configuration access functions.  They just check
 * alignment, करो locking and call the low-level functions poपूर्णांकed to
 * by pci_dev->ops.
 */

#घोषणा PCI_byte_BAD 0
#घोषणा PCI_word_BAD (pos & 1)
#घोषणा PCI_dword_BAD (pos & 3)

#अगर_घोषित CONFIG_PCI_LOCKLESS_CONFIG
# define pci_lock_config(f)	करो अणु (व्योम)(f); पूर्ण जबतक (0)
# define pci_unlock_config(f)	करो अणु (व्योम)(f); पूर्ण जबतक (0)
#अन्यथा
# define pci_lock_config(f)	raw_spin_lock_irqsave(&pci_lock, f)
# define pci_unlock_config(f)	raw_spin_unlock_irqrestore(&pci_lock, f)
#पूर्ण_अगर

#घोषणा PCI_OP_READ(size, type, len) \
पूर्णांक noअंतरभूत pci_bus_पढ़ो_config_##size \
	(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक pos, type *value)	\
अणु									\
	पूर्णांक res;							\
	अचिन्हित दीर्घ flags;						\
	u32 data = 0;							\
	अगर (PCI_##size##_BAD) वापस PCIBIOS_BAD_REGISTER_NUMBER;	\
	pci_lock_config(flags);						\
	res = bus->ops->पढ़ो(bus, devfn, pos, len, &data);		\
	*value = (type)data;						\
	pci_unlock_config(flags);					\
	वापस res;							\
पूर्ण

#घोषणा PCI_OP_WRITE(size, type, len) \
पूर्णांक noअंतरभूत pci_bus_ग_लिखो_config_##size \
	(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक pos, type value)	\
अणु									\
	पूर्णांक res;							\
	अचिन्हित दीर्घ flags;						\
	अगर (PCI_##size##_BAD) वापस PCIBIOS_BAD_REGISTER_NUMBER;	\
	pci_lock_config(flags);						\
	res = bus->ops->ग_लिखो(bus, devfn, pos, len, value);		\
	pci_unlock_config(flags);					\
	वापस res;							\
पूर्ण

PCI_OP_READ(byte, u8, 1)
PCI_OP_READ(word, u16, 2)
PCI_OP_READ(dword, u32, 4)
PCI_OP_WRITE(byte, u8, 1)
PCI_OP_WRITE(word, u16, 2)
PCI_OP_WRITE(dword, u32, 4)

EXPORT_SYMBOL(pci_bus_पढ़ो_config_byte);
EXPORT_SYMBOL(pci_bus_पढ़ो_config_word);
EXPORT_SYMBOL(pci_bus_पढ़ो_config_dword);
EXPORT_SYMBOL(pci_bus_ग_लिखो_config_byte);
EXPORT_SYMBOL(pci_bus_ग_लिखो_config_word);
EXPORT_SYMBOL(pci_bus_ग_लिखो_config_dword);

पूर्णांक pci_generic_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	व्योम __iomem *addr;

	addr = bus->ops->map_bus(bus, devfn, where);
	अगर (!addr) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	अगर (size == 1)
		*val = पढ़ोb(addr);
	अन्यथा अगर (size == 2)
		*val = पढ़ोw(addr);
	अन्यथा
		*val = पढ़ोl(addr);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
EXPORT_SYMBOL_GPL(pci_generic_config_पढ़ो);

पूर्णांक pci_generic_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, पूर्णांक size, u32 val)
अणु
	व्योम __iomem *addr;

	addr = bus->ops->map_bus(bus, devfn, where);
	अगर (!addr)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (size == 1)
		ग_लिखोb(val, addr);
	अन्यथा अगर (size == 2)
		ग_लिखोw(val, addr);
	अन्यथा
		ग_लिखोl(val, addr);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
EXPORT_SYMBOL_GPL(pci_generic_config_ग_लिखो);

पूर्णांक pci_generic_config_पढ़ो32(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	व्योम __iomem *addr;

	addr = bus->ops->map_bus(bus, devfn, where & ~0x3);
	अगर (!addr) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	*val = पढ़ोl(addr);

	अगर (size <= 2)
		*val = (*val >> (8 * (where & 3))) & ((1 << (size * 8)) - 1);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
EXPORT_SYMBOL_GPL(pci_generic_config_पढ़ो32);

पूर्णांक pci_generic_config_ग_लिखो32(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, पूर्णांक size, u32 val)
अणु
	व्योम __iomem *addr;
	u32 mask, पंचांगp;

	addr = bus->ops->map_bus(bus, devfn, where & ~0x3);
	अगर (!addr)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (size == 4) अणु
		ग_लिखोl(val, addr);
		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	/*
	 * In general, hardware that supports only 32-bit ग_लिखोs on PCI is
	 * not spec-compliant.  For example, software may perक्रमm a 16-bit
	 * ग_लिखो.  If the hardware only supports 32-bit accesses, we must
	 * करो a 32-bit पढ़ो, merge in the 16 bits we पूर्णांकend to ग_लिखो,
	 * followed by a 32-bit ग_लिखो.  If the 16 bits we *करोn't* पूर्णांकend to
	 * ग_लिखो happen to have any RW1C (ग_लिखो-one-to-clear) bits set, we
	 * just inadvertently cleared something we shouldn't have.
	 */
	dev_warn_ratelimited(&bus->dev, "%d-byte config write to %04x:%02x:%02x.%d offset %#x may corrupt adjacent RW1C bits\n",
			     size, pci_करोमुख्य_nr(bus), bus->number,
			     PCI_SLOT(devfn), PCI_FUNC(devfn), where);

	mask = ~(((1 << (size * 8)) - 1) << ((where & 0x3) * 8));
	पंचांगp = पढ़ोl(addr) & mask;
	पंचांगp |= val << ((where & 0x3) * 8);
	ग_लिखोl(पंचांगp, addr);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण
EXPORT_SYMBOL_GPL(pci_generic_config_ग_लिखो32);

/**
 * pci_bus_set_ops - Set raw operations of pci bus
 * @bus:	pci bus काष्ठा
 * @ops:	new raw operations
 *
 * Return previous raw operations
 */
काष्ठा pci_ops *pci_bus_set_ops(काष्ठा pci_bus *bus, काष्ठा pci_ops *ops)
अणु
	काष्ठा pci_ops *old_ops;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pci_lock, flags);
	old_ops = bus->ops;
	bus->ops = ops;
	raw_spin_unlock_irqrestore(&pci_lock, flags);
	वापस old_ops;
पूर्ण
EXPORT_SYMBOL(pci_bus_set_ops);

/*
 * The following routines are to prevent the user from accessing PCI config
 * space when it's unsafe to करो so.  Some devices require this during BIST and
 * we're required to prevent it during D-state transitions.
 *
 * We have a bit per device to indicate it's blocked and a global रुको queue
 * क्रम callers to sleep on until devices are unblocked.
 */
अटल DECLARE_WAIT_QUEUE_HEAD(pci_cfg_रुको);

अटल noअंतरभूत व्योम pci_रुको_cfg(काष्ठा pci_dev *dev)
	__must_hold(&pci_lock)
अणु
	करो अणु
		raw_spin_unlock_irq(&pci_lock);
		रुको_event(pci_cfg_रुको, !dev->block_cfg_access);
		raw_spin_lock_irq(&pci_lock);
	पूर्ण जबतक (dev->block_cfg_access);
पूर्ण

/* Returns 0 on success, negative values indicate error. */
#घोषणा PCI_USER_READ_CONFIG(size, type)					\
पूर्णांक pci_user_पढ़ो_config_##size						\
	(काष्ठा pci_dev *dev, पूर्णांक pos, type *val)			\
अणु									\
	पूर्णांक ret = PCIBIOS_SUCCESSFUL;					\
	u32 data = -1;							\
	अगर (PCI_##size##_BAD)						\
		वापस -EINVAL;						\
	raw_spin_lock_irq(&pci_lock);				\
	अगर (unlikely(dev->block_cfg_access))				\
		pci_रुको_cfg(dev);					\
	ret = dev->bus->ops->पढ़ो(dev->bus, dev->devfn,			\
					pos, माप(type), &data);	\
	raw_spin_unlock_irq(&pci_lock);				\
	*val = (type)data;						\
	वापस pcibios_err_to_त्रुटि_सं(ret);				\
पूर्ण									\
EXPORT_SYMBOL_GPL(pci_user_पढ़ो_config_##size);

/* Returns 0 on success, negative values indicate error. */
#घोषणा PCI_USER_WRITE_CONFIG(size, type)				\
पूर्णांक pci_user_ग_लिखो_config_##size					\
	(काष्ठा pci_dev *dev, पूर्णांक pos, type val)			\
अणु									\
	पूर्णांक ret = PCIBIOS_SUCCESSFUL;					\
	अगर (PCI_##size##_BAD)						\
		वापस -EINVAL;						\
	raw_spin_lock_irq(&pci_lock);				\
	अगर (unlikely(dev->block_cfg_access))				\
		pci_रुको_cfg(dev);					\
	ret = dev->bus->ops->ग_लिखो(dev->bus, dev->devfn,		\
					pos, माप(type), val);	\
	raw_spin_unlock_irq(&pci_lock);				\
	वापस pcibios_err_to_त्रुटि_सं(ret);				\
पूर्ण									\
EXPORT_SYMBOL_GPL(pci_user_ग_लिखो_config_##size);

PCI_USER_READ_CONFIG(byte, u8)
PCI_USER_READ_CONFIG(word, u16)
PCI_USER_READ_CONFIG(dword, u32)
PCI_USER_WRITE_CONFIG(byte, u8)
PCI_USER_WRITE_CONFIG(word, u16)
PCI_USER_WRITE_CONFIG(dword, u32)

/**
 * pci_cfg_access_lock - Lock PCI config पढ़ोs/ग_लिखोs
 * @dev:	pci device काष्ठा
 *
 * When access is locked, any userspace पढ़ोs or ग_लिखोs to config
 * space and concurrent lock requests will sleep until access is
 * allowed via pci_cfg_access_unlock() again.
 */
व्योम pci_cfg_access_lock(काष्ठा pci_dev *dev)
अणु
	might_sleep();

	raw_spin_lock_irq(&pci_lock);
	अगर (dev->block_cfg_access)
		pci_रुको_cfg(dev);
	dev->block_cfg_access = 1;
	raw_spin_unlock_irq(&pci_lock);
पूर्ण
EXPORT_SYMBOL_GPL(pci_cfg_access_lock);

/**
 * pci_cfg_access_trylock - try to lock PCI config पढ़ोs/ग_लिखोs
 * @dev:	pci device काष्ठा
 *
 * Same as pci_cfg_access_lock, but will वापस 0 अगर access is
 * alपढ़ोy locked, 1 otherwise. This function can be used from
 * atomic contexts.
 */
bool pci_cfg_access_trylock(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	bool locked = true;

	raw_spin_lock_irqsave(&pci_lock, flags);
	अगर (dev->block_cfg_access)
		locked = false;
	अन्यथा
		dev->block_cfg_access = 1;
	raw_spin_unlock_irqrestore(&pci_lock, flags);

	वापस locked;
पूर्ण
EXPORT_SYMBOL_GPL(pci_cfg_access_trylock);

/**
 * pci_cfg_access_unlock - Unlock PCI config पढ़ोs/ग_लिखोs
 * @dev:	pci device काष्ठा
 *
 * This function allows PCI config accesses to resume.
 */
व्योम pci_cfg_access_unlock(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&pci_lock, flags);

	/*
	 * This indicates a problem in the caller, but we करोn't need
	 * to समाप्त them, unlike a द्विगुन-block above.
	 */
	WARN_ON(!dev->block_cfg_access);

	dev->block_cfg_access = 0;
	raw_spin_unlock_irqrestore(&pci_lock, flags);

	wake_up_all(&pci_cfg_रुको);
पूर्ण
EXPORT_SYMBOL_GPL(pci_cfg_access_unlock);

अटल अंतरभूत पूर्णांक pcie_cap_version(स्थिर काष्ठा pci_dev *dev)
अणु
	वापस pcie_caps_reg(dev) & PCI_EXP_FLAGS_VERS;
पूर्ण

bool pcie_cap_has_lnkctl(स्थिर काष्ठा pci_dev *dev)
अणु
	पूर्णांक type = pci_pcie_type(dev);

	वापस type == PCI_EXP_TYPE_ENDPOINT ||
	       type == PCI_EXP_TYPE_LEG_END ||
	       type == PCI_EXP_TYPE_ROOT_PORT ||
	       type == PCI_EXP_TYPE_UPSTREAM ||
	       type == PCI_EXP_TYPE_DOWNSTREAM ||
	       type == PCI_EXP_TYPE_PCI_BRIDGE ||
	       type == PCI_EXP_TYPE_PCIE_BRIDGE;
पूर्ण

अटल अंतरभूत bool pcie_cap_has_sltctl(स्थिर काष्ठा pci_dev *dev)
अणु
	वापस pcie_करोwnstream_port(dev) &&
	       pcie_caps_reg(dev) & PCI_EXP_FLAGS_SLOT;
पूर्ण

bool pcie_cap_has_rtctl(स्थिर काष्ठा pci_dev *dev)
अणु
	पूर्णांक type = pci_pcie_type(dev);

	वापस type == PCI_EXP_TYPE_ROOT_PORT ||
	       type == PCI_EXP_TYPE_RC_EC;
पूर्ण

अटल bool pcie_capability_reg_implemented(काष्ठा pci_dev *dev, पूर्णांक pos)
अणु
	अगर (!pci_is_pcie(dev))
		वापस false;

	चयन (pos) अणु
	हाल PCI_EXP_FLAGS:
		वापस true;
	हाल PCI_EXP_DEVCAP:
	हाल PCI_EXP_DEVCTL:
	हाल PCI_EXP_DEVSTA:
		वापस true;
	हाल PCI_EXP_LNKCAP:
	हाल PCI_EXP_LNKCTL:
	हाल PCI_EXP_LNKSTA:
		वापस pcie_cap_has_lnkctl(dev);
	हाल PCI_EXP_SLTCAP:
	हाल PCI_EXP_SLTCTL:
	हाल PCI_EXP_SLTSTA:
		वापस pcie_cap_has_sltctl(dev);
	हाल PCI_EXP_RTCTL:
	हाल PCI_EXP_RTCAP:
	हाल PCI_EXP_RTSTA:
		वापस pcie_cap_has_rtctl(dev);
	हाल PCI_EXP_DEVCAP2:
	हाल PCI_EXP_DEVCTL2:
	हाल PCI_EXP_LNKCAP2:
	हाल PCI_EXP_LNKCTL2:
	हाल PCI_EXP_LNKSTA2:
		वापस pcie_cap_version(dev) > 1;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * Note that these accessor functions are only क्रम the "PCI Express
 * Capability" (see PCIe spec r3.0, sec 7.8).  They करो not apply to the
 * other "PCI Express Extended Capabilities" (AER, VC, ACS, MFVC, etc.)
 */
पूर्णांक pcie_capability_पढ़ो_word(काष्ठा pci_dev *dev, पूर्णांक pos, u16 *val)
अणु
	पूर्णांक ret;

	*val = 0;
	अगर (pos & 1)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (pcie_capability_reg_implemented(dev, pos)) अणु
		ret = pci_पढ़ो_config_word(dev, pci_pcie_cap(dev) + pos, val);
		/*
		 * Reset *val to 0 अगर pci_पढ़ो_config_word() fails, it may
		 * have been written as 0xFFFF अगर hardware error happens
		 * during pci_पढ़ो_config_word().
		 */
		अगर (ret)
			*val = 0;
		वापस ret;
	पूर्ण

	/*
	 * For Functions that करो not implement the Slot Capabilities,
	 * Slot Status, and Slot Control रेजिस्टरs, these spaces must
	 * be hardwired to 0b, with the exception of the Presence Detect
	 * State bit in the Slot Status रेजिस्टर of Downstream Ports,
	 * which must be hardwired to 1b.  (PCIe Base Spec 3.0, sec 7.8)
	 */
	अगर (pci_is_pcie(dev) && pcie_करोwnstream_port(dev) &&
	    pos == PCI_EXP_SLTSTA)
		*val = PCI_EXP_SLTSTA_PDS;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pcie_capability_पढ़ो_word);

पूर्णांक pcie_capability_पढ़ो_dword(काष्ठा pci_dev *dev, पूर्णांक pos, u32 *val)
अणु
	पूर्णांक ret;

	*val = 0;
	अगर (pos & 3)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (pcie_capability_reg_implemented(dev, pos)) अणु
		ret = pci_पढ़ो_config_dword(dev, pci_pcie_cap(dev) + pos, val);
		/*
		 * Reset *val to 0 अगर pci_पढ़ो_config_dword() fails, it may
		 * have been written as 0xFFFFFFFF अगर hardware error happens
		 * during pci_पढ़ो_config_dword().
		 */
		अगर (ret)
			*val = 0;
		वापस ret;
	पूर्ण

	अगर (pci_is_pcie(dev) && pcie_करोwnstream_port(dev) &&
	    pos == PCI_EXP_SLTSTA)
		*val = PCI_EXP_SLTSTA_PDS;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pcie_capability_पढ़ो_dword);

पूर्णांक pcie_capability_ग_लिखो_word(काष्ठा pci_dev *dev, पूर्णांक pos, u16 val)
अणु
	अगर (pos & 1)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (!pcie_capability_reg_implemented(dev, pos))
		वापस 0;

	वापस pci_ग_लिखो_config_word(dev, pci_pcie_cap(dev) + pos, val);
पूर्ण
EXPORT_SYMBOL(pcie_capability_ग_लिखो_word);

पूर्णांक pcie_capability_ग_लिखो_dword(काष्ठा pci_dev *dev, पूर्णांक pos, u32 val)
अणु
	अगर (pos & 3)
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (!pcie_capability_reg_implemented(dev, pos))
		वापस 0;

	वापस pci_ग_लिखो_config_dword(dev, pci_pcie_cap(dev) + pos, val);
पूर्ण
EXPORT_SYMBOL(pcie_capability_ग_लिखो_dword);

पूर्णांक pcie_capability_clear_and_set_word(काष्ठा pci_dev *dev, पूर्णांक pos,
				       u16 clear, u16 set)
अणु
	पूर्णांक ret;
	u16 val;

	ret = pcie_capability_पढ़ो_word(dev, pos, &val);
	अगर (!ret) अणु
		val &= ~clear;
		val |= set;
		ret = pcie_capability_ग_लिखो_word(dev, pos, val);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(pcie_capability_clear_and_set_word);

पूर्णांक pcie_capability_clear_and_set_dword(काष्ठा pci_dev *dev, पूर्णांक pos,
					u32 clear, u32 set)
अणु
	पूर्णांक ret;
	u32 val;

	ret = pcie_capability_पढ़ो_dword(dev, pos, &val);
	अगर (!ret) अणु
		val &= ~clear;
		val |= set;
		ret = pcie_capability_ग_लिखो_dword(dev, pos, val);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(pcie_capability_clear_and_set_dword);

पूर्णांक pci_पढ़ो_config_byte(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u8 *val)
अणु
	अगर (pci_dev_is_disconnected(dev)) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण
	वापस pci_bus_पढ़ो_config_byte(dev->bus, dev->devfn, where, val);
पूर्ण
EXPORT_SYMBOL(pci_पढ़ो_config_byte);

पूर्णांक pci_पढ़ो_config_word(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u16 *val)
अणु
	अगर (pci_dev_is_disconnected(dev)) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण
	वापस pci_bus_पढ़ो_config_word(dev->bus, dev->devfn, where, val);
पूर्ण
EXPORT_SYMBOL(pci_पढ़ो_config_word);

पूर्णांक pci_पढ़ो_config_dword(स्थिर काष्ठा pci_dev *dev, पूर्णांक where,
					u32 *val)
अणु
	अगर (pci_dev_is_disconnected(dev)) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण
	वापस pci_bus_पढ़ो_config_dword(dev->bus, dev->devfn, where, val);
पूर्ण
EXPORT_SYMBOL(pci_पढ़ो_config_dword);

पूर्णांक pci_ग_लिखो_config_byte(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u8 val)
अणु
	अगर (pci_dev_is_disconnected(dev))
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	वापस pci_bus_ग_लिखो_config_byte(dev->bus, dev->devfn, where, val);
पूर्ण
EXPORT_SYMBOL(pci_ग_लिखो_config_byte);

पूर्णांक pci_ग_लिखो_config_word(स्थिर काष्ठा pci_dev *dev, पूर्णांक where, u16 val)
अणु
	अगर (pci_dev_is_disconnected(dev))
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	वापस pci_bus_ग_लिखो_config_word(dev->bus, dev->devfn, where, val);
पूर्ण
EXPORT_SYMBOL(pci_ग_लिखो_config_word);

पूर्णांक pci_ग_लिखो_config_dword(स्थिर काष्ठा pci_dev *dev, पूर्णांक where,
					 u32 val)
अणु
	अगर (pci_dev_is_disconnected(dev))
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	वापस pci_bus_ग_लिखो_config_dword(dev->bus, dev->devfn, where, val);
पूर्ण
EXPORT_SYMBOL(pci_ग_लिखो_config_dword);
