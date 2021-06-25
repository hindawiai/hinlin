<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2006 Intel Corporation. */

/* glue क्रम the OS independent part of e1000
 * includes रेजिस्टर access macros
 */

#अगर_अघोषित _E1000_OSDEP_H_
#घोषणा _E1000_OSDEP_H_

#समावेश <यंत्र/पन.स>

#घोषणा CONFIG_RAM_BASE         0x60000
#घोषणा GBE_CONFIG_OFFSET       0x0

#घोषणा GBE_CONFIG_RAM_BASE \
	((अचिन्हित पूर्णांक)(CONFIG_RAM_BASE + GBE_CONFIG_OFFSET))

#घोषणा GBE_CONFIG_BASE_VIRT \
	((व्योम __iomem *)phys_to_virt(GBE_CONFIG_RAM_BASE))

#घोषणा GBE_CONFIG_FLASH_WRITE(base, offset, count, data) \
	(ioग_लिखो16_rep(base + offset, data, count))

#घोषणा GBE_CONFIG_FLASH_READ(base, offset, count, data) \
	(ioपढ़ो16_rep(base + (offset << 1), data, count))

#घोषणा er32(reg)							\
	(पढ़ोl(hw->hw_addr + ((hw->mac_type >= e1000_82543)		\
			       ? E1000_##reg : E1000_82542_##reg)))

#घोषणा ew32(reg, value)						\
	(ग_लिखोl((value), (hw->hw_addr + ((hw->mac_type >= e1000_82543)	\
					 ? E1000_##reg : E1000_82542_##reg))))

#घोषणा E1000_WRITE_REG_ARRAY(a, reg, offset, value) ( \
    ग_लिखोl((value), ((a)->hw_addr + \
        (((a)->mac_type >= e1000_82543) ? E1000_##reg : E1000_82542_##reg) + \
        ((offset) << 2))))

#घोषणा E1000_READ_REG_ARRAY(a, reg, offset) ( \
    पढ़ोl((a)->hw_addr + \
        (((a)->mac_type >= e1000_82543) ? E1000_##reg : E1000_82542_##reg) + \
        ((offset) << 2)))

#घोषणा E1000_READ_REG_ARRAY_DWORD E1000_READ_REG_ARRAY
#घोषणा E1000_WRITE_REG_ARRAY_DWORD E1000_WRITE_REG_ARRAY

#घोषणा E1000_WRITE_REG_ARRAY_WORD(a, reg, offset, value) ( \
    ग_लिखोw((value), ((a)->hw_addr + \
        (((a)->mac_type >= e1000_82543) ? E1000_##reg : E1000_82542_##reg) + \
        ((offset) << 1))))

#घोषणा E1000_READ_REG_ARRAY_WORD(a, reg, offset) ( \
    पढ़ोw((a)->hw_addr + \
        (((a)->mac_type >= e1000_82543) ? E1000_##reg : E1000_82542_##reg) + \
        ((offset) << 1)))

#घोषणा E1000_WRITE_REG_ARRAY_BYTE(a, reg, offset, value) ( \
    ग_लिखोb((value), ((a)->hw_addr + \
        (((a)->mac_type >= e1000_82543) ? E1000_##reg : E1000_82542_##reg) + \
        (offset))))

#घोषणा E1000_READ_REG_ARRAY_BYTE(a, reg, offset) ( \
    पढ़ोb((a)->hw_addr + \
        (((a)->mac_type >= e1000_82543) ? E1000_##reg : E1000_82542_##reg) + \
        (offset)))

#घोषणा E1000_WRITE_FLUSH() er32(STATUS)

#घोषणा E1000_WRITE_ICH_FLASH_REG(a, reg, value) ( \
    ग_लिखोl((value), ((a)->flash_address + reg)))

#घोषणा E1000_READ_ICH_FLASH_REG(a, reg) ( \
    पढ़ोl((a)->flash_address + reg))

#घोषणा E1000_WRITE_ICH_FLASH_REG16(a, reg, value) ( \
    ग_लिखोw((value), ((a)->flash_address + reg)))

#घोषणा E1000_READ_ICH_FLASH_REG16(a, reg) ( \
    पढ़ोw((a)->flash_address + reg))

#पूर्ण_अगर /* _E1000_OSDEP_H_ */
