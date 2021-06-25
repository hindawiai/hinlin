<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 **********************************************************************/

/*!  \पile octeon_mem_ops.h
 *   \मrief Host Driver: Routines used to पढ़ो/ग_लिखो Octeon memory.
 */

#अगर_अघोषित __OCTEON_MEM_OPS_H__
#घोषणा __OCTEON_MEM_OPS_H__

/**  Read a 64-bit value from a BAR1 mapped core memory address.
 *   @param  oct        -  poपूर्णांकer to the octeon device.
 *   @param  core_addr  -  the address to पढ़ो from.
 *
 *   The range_idx gives the BAR1 index रेजिस्टर क्रम the range of address
 *   in which core_addr is mapped.
 *
 *   @वापस  64-bit value पढ़ो from Core memory
 */
u64 octeon_पढ़ो_device_mem64(काष्ठा octeon_device *oct, u64 core_addr);

/**  Read a 32-bit value from a BAR1 mapped core memory address.
 *   @param  oct        -  poपूर्णांकer to the octeon device.
 *   @param  core_addr  -  the address to पढ़ो from.
 *
 *   @वापस  32-bit value पढ़ो from Core memory
 */
u32 octeon_पढ़ो_device_mem32(काष्ठा octeon_device *oct, u64 core_addr);

/**  Write a 32-bit value to a BAR1 mapped core memory address.
 *   @param  oct        -  poपूर्णांकer to the octeon device.
 *   @param  core_addr  -  the address to ग_लिखो to.
 *   @param  val        -  32-bit value to ग_लिखो.
 */
व्योम
octeon_ग_लिखो_device_mem32(काष्ठा octeon_device *oct,
			  u64 core_addr,
			  u32 val);

/** Read multiple bytes from Octeon memory.
 */
व्योम
octeon_pci_पढ़ो_core_mem(काष्ठा octeon_device *oct,
			 u64 coपढ़ोdr,
			 u8 *buf,
			 u32 len);

/** Write multiple bytes पूर्णांकo Octeon memory.
 */
व्योम
octeon_pci_ग_लिखो_core_mem(काष्ठा octeon_device *oct,
			  u64 coपढ़ोdr,
			  स्थिर u8 *buf,
			  u32 len);

#पूर्ण_अगर
