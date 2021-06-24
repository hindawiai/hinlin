<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2008 Nokia Corporation
 */

#समावेश "wl1251.h"
#समावेश "reg.h"
#समावेश "io.h"

/* FIXME: this is अटल data nowadays and the table can be हटाओd */
अटल क्रमागत wl12xx_acx_पूर्णांक_reg wl1251_io_reg_table[ACX_REG_TABLE_LEN] = अणु
	[ACX_REG_INTERRUPT_TRIG]     = (REGISTERS_BASE + 0x0474),
	[ACX_REG_INTERRUPT_TRIG_H]   = (REGISTERS_BASE + 0x0478),
	[ACX_REG_INTERRUPT_MASK]     = (REGISTERS_BASE + 0x0494),
	[ACX_REG_HINT_MASK_SET]      = (REGISTERS_BASE + 0x0498),
	[ACX_REG_HINT_MASK_CLR]      = (REGISTERS_BASE + 0x049C),
	[ACX_REG_INTERRUPT_NO_CLEAR] = (REGISTERS_BASE + 0x04B0),
	[ACX_REG_INTERRUPT_CLEAR]    = (REGISTERS_BASE + 0x04A4),
	[ACX_REG_INTERRUPT_ACK]      = (REGISTERS_BASE + 0x04A8),
	[ACX_REG_SLV_SOFT_RESET]     = (REGISTERS_BASE + 0x0000),
	[ACX_REG_EE_START]           = (REGISTERS_BASE + 0x080C),
	[ACX_REG_ECPU_CONTROL]       = (REGISTERS_BASE + 0x0804)
पूर्ण;

अटल पूर्णांक wl1251_translate_reg_addr(काष्ठा wl1251 *wl, पूर्णांक addr)
अणु
	/* If the address is lower than REGISTERS_BASE, it means that this is
	 * a chip-specअगरic रेजिस्टर address, so look it up in the रेजिस्टरs
	 * table */
	अगर (addr < REGISTERS_BASE) अणु
		/* Make sure we करोn't go over the table */
		अगर (addr >= ACX_REG_TABLE_LEN) अणु
			wl1251_error("address out of range (%d)", addr);
			वापस -EINVAL;
		पूर्ण
		addr = wl1251_io_reg_table[addr];
	पूर्ण

	वापस addr - wl->physical_reg_addr + wl->भव_reg_addr;
पूर्ण

अटल पूर्णांक wl1251_translate_mem_addr(काष्ठा wl1251 *wl, पूर्णांक addr)
अणु
	वापस addr - wl->physical_mem_addr + wl->भव_mem_addr;
पूर्ण

व्योम wl1251_mem_पढ़ो(काष्ठा wl1251 *wl, पूर्णांक addr, व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक physical;

	physical = wl1251_translate_mem_addr(wl, addr);

	wl->अगर_ops->पढ़ो(wl, physical, buf, len);
पूर्ण

व्योम wl1251_mem_ग_लिखो(काष्ठा wl1251 *wl, पूर्णांक addr, व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक physical;

	physical = wl1251_translate_mem_addr(wl, addr);

	wl->अगर_ops->ग_लिखो(wl, physical, buf, len);
पूर्ण

u32 wl1251_mem_पढ़ो32(काष्ठा wl1251 *wl, पूर्णांक addr)
अणु
	वापस wl1251_पढ़ो32(wl, wl1251_translate_mem_addr(wl, addr));
पूर्ण

व्योम wl1251_mem_ग_लिखो32(काष्ठा wl1251 *wl, पूर्णांक addr, u32 val)
अणु
	wl1251_ग_लिखो32(wl, wl1251_translate_mem_addr(wl, addr), val);
पूर्ण

u32 wl1251_reg_पढ़ो32(काष्ठा wl1251 *wl, पूर्णांक addr)
अणु
	वापस wl1251_पढ़ो32(wl, wl1251_translate_reg_addr(wl, addr));
पूर्ण

व्योम wl1251_reg_ग_लिखो32(काष्ठा wl1251 *wl, पूर्णांक addr, u32 val)
अणु
	wl1251_ग_लिखो32(wl, wl1251_translate_reg_addr(wl, addr), val);
पूर्ण

/* Set the partitions to access the chip addresses.
 *
 * There are two VIRTUAL partitions (the memory partition and the
 * रेजिस्टरs partition), which are mapped to two dअगरferent areas of the
 * PHYSICAL (hardware) memory.  This function also makes other checks to
 * ensure that the partitions are not overlapping.  In the diagram below, the
 * memory partition comes beक्रमe the रेजिस्टर partition, but the opposite is
 * also supported.
 *
 *                               PHYSICAL address
 *                                     space
 *
 *                                    |    |
 *                                 ...+----+--> mem_start
 *          VIRTUAL address     ...   |    |
 *               space       ...      |    | [PART_0]
 *                        ...         |    |
 * 0x00000000 <--+----+...         ...+----+--> mem_start + mem_size
 *               |    |         ...   |    |
 *               |MEM |      ...      |    |
 *               |    |   ...         |    |
 *  part_size <--+----+...            |    | अणुunused area)
 *               |    |   ...         |    |
 *               |REG |      ...      |    |
 *  part_size    |    |         ...   |    |
 *      +     <--+----+...         ...+----+--> reg_start
 *  reg_size              ...         |    |
 *                           ...      |    | [PART_1]
 *                              ...   |    |
 *                                 ...+----+--> reg_start + reg_size
 *                                    |    |
 *
 */
व्योम wl1251_set_partition(काष्ठा wl1251 *wl,
			  u32 mem_start, u32 mem_size,
			  u32 reg_start, u32 reg_size)
अणु
	काष्ठा wl1251_partition partition[2];

	wl1251_debug(DEBUG_SPI, "mem_start %08X mem_size %08X",
		     mem_start, mem_size);
	wl1251_debug(DEBUG_SPI, "reg_start %08X reg_size %08X",
		     reg_start, reg_size);

	/* Make sure that the two partitions together करोn't exceed the
	 * address range */
	अगर ((mem_size + reg_size) > HW_ACCESS_MEMORY_MAX_RANGE) अणु
		wl1251_debug(DEBUG_SPI, "Total size exceeds maximum virtual"
			     " address range.  Truncating partition[0].");
		mem_size = HW_ACCESS_MEMORY_MAX_RANGE - reg_size;
		wl1251_debug(DEBUG_SPI, "mem_start %08X mem_size %08X",
			     mem_start, mem_size);
		wl1251_debug(DEBUG_SPI, "reg_start %08X reg_size %08X",
			     reg_start, reg_size);
	पूर्ण

	अगर ((mem_start < reg_start) &&
	    ((mem_start + mem_size) > reg_start)) अणु
		/* Guarantee that the memory partition करोesn't overlap the
		 * रेजिस्टरs partition */
		wl1251_debug(DEBUG_SPI, "End of partition[0] is "
			     "overlapping partition[1].  Adjusted.");
		mem_size = reg_start - mem_start;
		wl1251_debug(DEBUG_SPI, "mem_start %08X mem_size %08X",
			     mem_start, mem_size);
		wl1251_debug(DEBUG_SPI, "reg_start %08X reg_size %08X",
			     reg_start, reg_size);
	पूर्ण अन्यथा अगर ((reg_start < mem_start) &&
		   ((reg_start + reg_size) > mem_start)) अणु
		/* Guarantee that the रेजिस्टर partition करोesn't overlap the
		 * memory partition */
		wl1251_debug(DEBUG_SPI, "End of partition[1] is"
			     " overlapping partition[0].  Adjusted.");
		reg_size = mem_start - reg_start;
		wl1251_debug(DEBUG_SPI, "mem_start %08X mem_size %08X",
			     mem_start, mem_size);
		wl1251_debug(DEBUG_SPI, "reg_start %08X reg_size %08X",
			     reg_start, reg_size);
	पूर्ण

	partition[0].start = mem_start;
	partition[0].size  = mem_size;
	partition[1].start = reg_start;
	partition[1].size  = reg_size;

	wl->physical_mem_addr = mem_start;
	wl->physical_reg_addr = reg_start;

	wl->भव_mem_addr = 0;
	wl->भव_reg_addr = mem_size;

	wl->अगर_ops->ग_लिखो(wl, HW_ACCESS_PART0_SIZE_ADDR, partition,
		माप(partition));
पूर्ण
