<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel OnChip System Fabric MailBox access support
 */

#अगर_अघोषित IOSF_MBI_SYMS_H
#घोषणा IOSF_MBI_SYMS_H

#समावेश <linux/notअगरier.h>

#घोषणा MBI_MCR_OFFSET		0xD0
#घोषणा MBI_MDR_OFFSET		0xD4
#घोषणा MBI_MCRX_OFFSET		0xD8

#घोषणा MBI_RD_MASK		0xFEFFFFFF
#घोषणा MBI_WR_MASK		0X01000000

#घोषणा MBI_MASK_HI		0xFFFFFF00
#घोषणा MBI_MASK_LO		0x000000FF
#घोषणा MBI_ENABLE		0xF0

/* IOSF SB पढ़ो/ग_लिखो opcodes */
#घोषणा MBI_MMIO_READ		0x00
#घोषणा MBI_MMIO_WRITE		0x01
#घोषणा MBI_CFG_READ		0x04
#घोषणा MBI_CFG_WRITE		0x05
#घोषणा MBI_CR_READ		0x06
#घोषणा MBI_CR_WRITE		0x07
#घोषणा MBI_REG_READ		0x10
#घोषणा MBI_REG_WRITE		0x11
#घोषणा MBI_ESRAM_READ		0x12
#घोषणा MBI_ESRAM_WRITE		0x13

/* Baytrail available units */
#घोषणा BT_MBI_UNIT_AUNIT	0x00
#घोषणा BT_MBI_UNIT_SMC		0x01
#घोषणा BT_MBI_UNIT_CPU		0x02
#घोषणा BT_MBI_UNIT_BUNIT	0x03
#घोषणा BT_MBI_UNIT_PMC		0x04
#घोषणा BT_MBI_UNIT_GFX		0x06
#घोषणा BT_MBI_UNIT_SMI		0x0C
#घोषणा BT_MBI_UNIT_CCK		0x14
#घोषणा BT_MBI_UNIT_USB		0x43
#घोषणा BT_MBI_UNIT_SATA	0xA3
#घोषणा BT_MBI_UNIT_PCIE	0xA6

/* Quark available units */
#घोषणा QRK_MBI_UNIT_HBA	0x00
#घोषणा QRK_MBI_UNIT_HB		0x03
#घोषणा QRK_MBI_UNIT_RMU	0x04
#घोषणा QRK_MBI_UNIT_MM		0x05
#घोषणा QRK_MBI_UNIT_SOC	0x31

/* Action values क्रम the pmic_bus_access_notअगरier functions */
#घोषणा MBI_PMIC_BUS_ACCESS_BEGIN	1
#घोषणा MBI_PMIC_BUS_ACCESS_END		2

#अगर IS_ENABLED(CONFIG_IOSF_MBI)

bool iosf_mbi_available(व्योम);

/**
 * iosf_mbi_पढ़ो() - MailBox Interface पढ़ो command
 * @port:	port indicating subunit being accessed
 * @opcode:	port specअगरic पढ़ो or ग_लिखो opcode
 * @offset:	रेजिस्टर address offset
 * @mdr:	रेजिस्टर data to be पढ़ो
 *
 * Locking is handled by spinlock - cannot sleep.
 * Return: Nonzero on error
 */
पूर्णांक iosf_mbi_पढ़ो(u8 port, u8 opcode, u32 offset, u32 *mdr);

/**
 * iosf_mbi_ग_लिखो() - MailBox unmasked ग_लिखो command
 * @port:	port indicating subunit being accessed
 * @opcode:	port specअगरic पढ़ो or ग_लिखो opcode
 * @offset:	रेजिस्टर address offset
 * @mdr:	रेजिस्टर data to be written
 *
 * Locking is handled by spinlock - cannot sleep.
 * Return: Nonzero on error
 */
पूर्णांक iosf_mbi_ग_लिखो(u8 port, u8 opcode, u32 offset, u32 mdr);

/**
 * iosf_mbi_modअगरy() - MailBox masked ग_लिखो command
 * @port:	port indicating subunit being accessed
 * @opcode:	port specअगरic पढ़ो or ग_लिखो opcode
 * @offset:	रेजिस्टर address offset
 * @mdr:	रेजिस्टर data being modअगरied
 * @mask:	mask indicating bits in mdr to be modअगरied
 *
 * Locking is handled by spinlock - cannot sleep.
 * Return: Nonzero on error
 */
पूर्णांक iosf_mbi_modअगरy(u8 port, u8 opcode, u32 offset, u32 mdr, u32 mask);

/**
 * iosf_mbi_punit_acquire() - Acquire access to the P-Unit
 *
 * One some प्रणालीs the P-Unit accesses the PMIC to change various voltages
 * through the same bus as other kernel drivers use क्रम e.g. battery monitoring.
 *
 * If a driver sends requests to the P-Unit which require the P-Unit to access
 * the PMIC bus जबतक another driver is also accessing the PMIC bus various bad
 * things happen.
 *
 * Call this function beक्रमe sending requests to the P-Unit which may make it
 * access the PMIC, be it through iosf_mbi* functions or through other means.
 * This function will block all kernel access to the PMIC I2C bus, so that the
 * P-Unit can safely access the PMIC over the shared I2C bus.
 *
 * Note on these प्रणालीs the i2c-bus driver will request a sempahore from the
 * P-Unit क्रम exclusive access to the PMIC bus when i2c drivers are accessing
 * it, but this करोes not appear to be sufficient, we still need to aव्योम making
 * certain P-Unit requests during the access winकरोw to aव्योम problems.
 *
 * This function locks a mutex, as such it may sleep.
 */
व्योम iosf_mbi_punit_acquire(व्योम);

/**
 * iosf_mbi_punit_release() - Release access to the P-Unit
 */
व्योम iosf_mbi_punit_release(व्योम);

/**
 * iosf_mbi_block_punit_i2c_access() - Block P-Unit accesses to the PMIC bus
 *
 * Call this function to block P-Unit access to the PMIC I2C bus, so that the
 * kernel can safely access the PMIC over the shared I2C bus.
 *
 * This function acquires the P-Unit bus semaphore and notअगरies
 * pmic_bus_access_notअगरier listeners that they may no दीर्घer access the
 * P-Unit in a way which may cause it to access the shared I2C bus.
 *
 * Note this function may be called multiple बार and the bus will not
 * be released until iosf_mbi_unblock_punit_i2c_access() has been called the
 * same amount of बार.
 *
 * Return: Nonzero on error
 */
पूर्णांक iosf_mbi_block_punit_i2c_access(व्योम);

/*
 * iosf_mbi_unblock_punit_i2c_access() - Release PMIC I2C bus block
 *
 * Release i2c access block gotten through iosf_mbi_block_punit_i2c_access().
 */
व्योम iosf_mbi_unblock_punit_i2c_access(व्योम);

/**
 * iosf_mbi_रेजिस्टर_pmic_bus_access_notअगरier - Register PMIC bus notअगरier
 *
 * This function can be used by drivers which may need to acquire P-Unit
 * managed resources from पूर्णांकerrupt context, where iosf_mbi_punit_acquire()
 * can not be used.
 *
 * This function allows a driver to रेजिस्टर a notअगरier to get notअगरied (in a
 * process context) beक्रमe other drivers start accessing the PMIC bus.
 *
 * This allows the driver to acquire any resources, which it may need during
 * the winकरोw the other driver is accessing the PMIC, beक्रमe hand.
 *
 * @nb: notअगरier_block to रेजिस्टर
 */
पूर्णांक iosf_mbi_रेजिस्टर_pmic_bus_access_notअगरier(काष्ठा notअगरier_block *nb);

/**
 * iosf_mbi_रेजिस्टर_pmic_bus_access_notअगरier - Unरेजिस्टर PMIC bus notअगरier
 *
 * @nb: notअगरier_block to unरेजिस्टर
 */
पूर्णांक iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier(काष्ठा notअगरier_block *nb);

/**
 * iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier_unlocked - Unरेजिस्टर PMIC bus
 *                                                         notअगरier, unlocked
 *
 * Like iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier(), but क्रम use when the
 * caller has alपढ़ोy called iosf_mbi_punit_acquire() itself.
 *
 * @nb: notअगरier_block to unरेजिस्टर
 */
पूर्णांक iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier_unlocked(
	काष्ठा notअगरier_block *nb);

/**
 * iosf_mbi_निश्चित_punit_acquired - Assert that the P-Unit has been acquired.
 */
व्योम iosf_mbi_निश्चित_punit_acquired(व्योम);

#अन्यथा /* CONFIG_IOSF_MBI is not enabled */
अटल अंतरभूत
bool iosf_mbi_available(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत
पूर्णांक iosf_mbi_पढ़ो(u8 port, u8 opcode, u32 offset, u32 *mdr)
अणु
	WARN(1, "IOSF_MBI driver not available");
	वापस -EPERM;
पूर्ण

अटल अंतरभूत
पूर्णांक iosf_mbi_ग_लिखो(u8 port, u8 opcode, u32 offset, u32 mdr)
अणु
	WARN(1, "IOSF_MBI driver not available");
	वापस -EPERM;
पूर्ण

अटल अंतरभूत
पूर्णांक iosf_mbi_modअगरy(u8 port, u8 opcode, u32 offset, u32 mdr, u32 mask)
अणु
	WARN(1, "IOSF_MBI driver not available");
	वापस -EPERM;
पूर्ण

अटल अंतरभूत व्योम iosf_mbi_punit_acquire(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम iosf_mbi_punit_release(व्योम) अणुपूर्ण

अटल अंतरभूत
पूर्णांक iosf_mbi_रेजिस्टर_pmic_bus_access_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
iosf_mbi_unरेजिस्टर_pmic_bus_access_notअगरier_unlocked(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक iosf_mbi_call_pmic_bus_access_notअगरier_chain(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम iosf_mbi_निश्चित_punit_acquired(व्योम) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_IOSF_MBI */

#पूर्ण_अगर /* IOSF_MBI_SYMS_H */
