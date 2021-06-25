<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "wl12xx_80211.h"
#समावेश "io.h"
#समावेश "tx.h"

bool wl1271_set_block_size(काष्ठा wl1271 *wl)
अणु
	अगर (wl->अगर_ops->set_block_size) अणु
		wl->अगर_ops->set_block_size(wl->dev, WL12XX_BUS_BLOCK_SIZE);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम wlcore_disable_पूर्णांकerrupts(काष्ठा wl1271 *wl)
अणु
	disable_irq(wl->irq);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_disable_पूर्णांकerrupts);

व्योम wlcore_disable_पूर्णांकerrupts_nosync(काष्ठा wl1271 *wl)
अणु
	disable_irq_nosync(wl->irq);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_disable_पूर्णांकerrupts_nosync);

व्योम wlcore_enable_पूर्णांकerrupts(काष्ठा wl1271 *wl)
अणु
	enable_irq(wl->irq);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_enable_पूर्णांकerrupts);

व्योम wlcore_synchronize_पूर्णांकerrupts(काष्ठा wl1271 *wl)
अणु
	synchronize_irq(wl->irq);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_synchronize_पूर्णांकerrupts);

पूर्णांक wlcore_translate_addr(काष्ठा wl1271 *wl, पूर्णांक addr)
अणु
	काष्ठा wlcore_partition_set *part = &wl->curr_part;

	/*
	 * To translate, first check to which winकरोw of addresses the
	 * particular address beदीर्घs. Then subtract the starting address
	 * of that winकरोw from the address. Then, add offset of the
	 * translated region.
	 *
	 * The translated regions occur next to each other in physical device
	 * memory, so just add the sizes of the preceding address regions to
	 * get the offset to the new region.
	 */
	अगर ((addr >= part->mem.start) &&
	    (addr < part->mem.start + part->mem.size))
		वापस addr - part->mem.start;
	अन्यथा अगर ((addr >= part->reg.start) &&
		 (addr < part->reg.start + part->reg.size))
		वापस addr - part->reg.start + part->mem.size;
	अन्यथा अगर ((addr >= part->mem2.start) &&
		 (addr < part->mem2.start + part->mem2.size))
		वापस addr - part->mem2.start + part->mem.size +
			part->reg.size;
	अन्यथा अगर ((addr >= part->mem3.start) &&
		 (addr < part->mem3.start + part->mem3.size))
		वापस addr - part->mem3.start + part->mem.size +
			part->reg.size + part->mem2.size;

	WARN(1, "HW address 0x%x out of range", addr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_translate_addr);

/* Set the partitions to access the chip addresses
 *
 * To simplअगरy driver code, a fixed (भव) memory map is defined क्रम
 * रेजिस्टर and memory addresses. Because in the chipset, in dअगरferent stages
 * of operation, those addresses will move around, an address translation
 * mechanism is required.
 *
 * There are four partitions (three memory and one रेजिस्टर partition),
 * which are mapped to two dअगरferent areas of the hardware memory.
 *
 *                                Virtual address
 *                                     space
 *
 *                                    |    |
 *                                 ...+----+--> mem.start
 *          Physical address    ...   |    |
 *               space       ...      |    | [PART_0]
 *                        ...         |    |
 *  00000000  <--+----+...         ...+----+--> mem.start + mem.size
 *               |    |         ...   |    |
 *               |MEM |      ...      |    |
 *               |    |   ...         |    |
 *  mem.size  <--+----+...            |    | अणुunused area)
 *               |    |   ...         |    |
 *               |REG |      ...      |    |
 *  mem.size     |    |         ...   |    |
 *      +     <--+----+...         ...+----+--> reg.start
 *  reg.size     |    |   ...         |    |
 *               |MEM2|      ...      |    | [PART_1]
 *               |    |         ...   |    |
 *                                 ...+----+--> reg.start + reg.size
 *                                    |    |
 *
 */
पूर्णांक wlcore_set_partition(काष्ठा wl1271 *wl,
			 स्थिर काष्ठा wlcore_partition_set *p)
अणु
	पूर्णांक ret;

	/* copy partition info */
	स_नकल(&wl->curr_part, p, माप(*p));

	wl1271_debug(DEBUG_IO, "mem_start %08X mem_size %08X",
		     p->mem.start, p->mem.size);
	wl1271_debug(DEBUG_IO, "reg_start %08X reg_size %08X",
		     p->reg.start, p->reg.size);
	wl1271_debug(DEBUG_IO, "mem2_start %08X mem2_size %08X",
		     p->mem2.start, p->mem2.size);
	wl1271_debug(DEBUG_IO, "mem3_start %08X mem3_size %08X",
		     p->mem3.start, p->mem3.size);

	ret = wlcore_raw_ग_लिखो32(wl, HW_PART0_START_ADDR, p->mem.start);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_raw_ग_लिखो32(wl, HW_PART0_SIZE_ADDR, p->mem.size);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_raw_ग_लिखो32(wl, HW_PART1_START_ADDR, p->reg.start);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_raw_ग_लिखो32(wl, HW_PART1_SIZE_ADDR, p->reg.size);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_raw_ग_लिखो32(wl, HW_PART2_START_ADDR, p->mem2.start);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_raw_ग_लिखो32(wl, HW_PART2_SIZE_ADDR, p->mem2.size);
	अगर (ret < 0)
		जाओ out;

	/* wl12xx only: We करोn't need the size of the last partition,
	 * as it is स्वतःmatically calculated based on the total memory
	 * size and the sizes of the previous partitions.
	 *
	 * wl18xx re-defines the HW_PART3 addresses क्रम logger over
	 * SDIO support. wl12xx is expecting the ग_लिखो to
	 * HW_PART3_START_ADDR at offset 24. This creates conflict
	 * between the addresses.
	 * In order to fix this the expected value is written to
	 * HW_PART3_SIZE_ADDR instead which is at offset 24 after changes.
	 */
	ret = wlcore_raw_ग_लिखो32(wl, HW_PART3_START_ADDR, p->mem3.start);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_raw_ग_लिखो32(wl, HW_PART3_SIZE_ADDR, p->mem3.size);
	अगर (ret < 0)
		जाओ out;

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_set_partition);

व्योम wl1271_io_reset(काष्ठा wl1271 *wl)
अणु
	अगर (wl->अगर_ops->reset)
		wl->अगर_ops->reset(wl->dev);
पूर्ण

व्योम wl1271_io_init(काष्ठा wl1271 *wl)
अणु
	अगर (wl->अगर_ops->init)
		wl->अगर_ops->init(wl->dev);
पूर्ण
