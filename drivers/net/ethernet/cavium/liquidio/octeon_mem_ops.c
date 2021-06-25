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
#समावेश <linux/netdevice.h>
#समावेश "liquidio_common.h"
#समावेश "octeon_droq.h"
#समावेश "octeon_iq.h"
#समावेश "response_manager.h"
#समावेश "octeon_device.h"
#समावेश "octeon_mem_ops.h"

#घोषणा MEMOPS_IDX   BAR1_INDEX_DYNAMIC_MAP

#अगर_घोषित __BIG_ENDIAN_BITFIELD
अटल अंतरभूत व्योम
octeon_toggle_bar1_swapmode(काष्ठा octeon_device *oct, u32 idx)
अणु
	u32 mask;

	mask = oct->fn_list.bar1_idx_पढ़ो(oct, idx);
	mask = (mask & 0x2) ? (mask & ~2) : (mask | 2);
	oct->fn_list.bar1_idx_ग_लिखो(oct, idx, mask);
पूर्ण
#अन्यथा
#घोषणा octeon_toggle_bar1_swapmode(oct, idx)
#पूर्ण_अगर

अटल व्योम
octeon_pci_fastग_लिखो(काष्ठा octeon_device *oct, u8 __iomem *mapped_addr,
		     u8 *hostbuf, u32 len)
अणु
	जबतक ((len) && ((अचिन्हित दीर्घ)mapped_addr) & 7) अणु
		ग_लिखोb(*(hostbuf++), mapped_addr++);
		len--;
	पूर्ण

	octeon_toggle_bar1_swapmode(oct, MEMOPS_IDX);

	जबतक (len >= 8) अणु
		ग_लिखोq(*((u64 *)hostbuf), mapped_addr);
		mapped_addr += 8;
		hostbuf += 8;
		len -= 8;
	पूर्ण

	octeon_toggle_bar1_swapmode(oct, MEMOPS_IDX);

	जबतक (len--)
		ग_लिखोb(*(hostbuf++), mapped_addr++);
पूर्ण

अटल व्योम
octeon_pci_fastपढ़ो(काष्ठा octeon_device *oct, u8 __iomem *mapped_addr,
		    u8 *hostbuf, u32 len)
अणु
	जबतक ((len) && ((अचिन्हित दीर्घ)mapped_addr) & 7) अणु
		*(hostbuf++) = पढ़ोb(mapped_addr++);
		len--;
	पूर्ण

	octeon_toggle_bar1_swapmode(oct, MEMOPS_IDX);

	जबतक (len >= 8) अणु
		*((u64 *)hostbuf) = पढ़ोq(mapped_addr);
		mapped_addr += 8;
		hostbuf += 8;
		len -= 8;
	पूर्ण

	octeon_toggle_bar1_swapmode(oct, MEMOPS_IDX);

	जबतक (len--)
		*(hostbuf++) = पढ़ोb(mapped_addr++);
पूर्ण

/* Core mem पढ़ो/ग_लिखो with temporary bar1 settings. */
/* op = 1 to पढ़ो, op = 0 to ग_लिखो. */
अटल व्योम
__octeon_pci_rw_core_mem(काष्ठा octeon_device *oct, u64 addr,
			 u8 *hostbuf, u32 len, u32 op)
अणु
	u32 copy_len = 0, index_reg_val = 0;
	अचिन्हित दीर्घ flags;
	u8 __iomem *mapped_addr;
	u64 अटल_mapping_base;

	अटल_mapping_base = oct->console_nb_info.dram_region_base;

	अगर (अटल_mapping_base &&
	    अटल_mapping_base == (addr & ~(OCTEON_BAR1_ENTRY_SIZE - 1ULL))) अणु
		पूर्णांक bar1_index = oct->console_nb_info.bar1_index;

		mapped_addr = oct->mmio[1].hw_addr
			+ (bar1_index << ilog2(OCTEON_BAR1_ENTRY_SIZE))
			+ (addr & (OCTEON_BAR1_ENTRY_SIZE - 1ULL));

		अगर (op)
			octeon_pci_fastपढ़ो(oct, mapped_addr, hostbuf, len);
		अन्यथा
			octeon_pci_fastग_लिखो(oct, mapped_addr, hostbuf, len);

		वापस;
	पूर्ण

	spin_lock_irqsave(&oct->mem_access_lock, flags);

	/* Save the original index reg value. */
	index_reg_val = oct->fn_list.bar1_idx_पढ़ो(oct, MEMOPS_IDX);
	करो अणु
		oct->fn_list.bar1_idx_setup(oct, addr, MEMOPS_IDX, 1);
		mapped_addr = oct->mmio[1].hw_addr
		    + (MEMOPS_IDX << 22) + (addr & 0x3fffff);

		/* If operation crosses a 4MB boundary, split the transfer
		 * at the 4MB
		 * boundary.
		 */
		अगर (((addr + len - 1) & ~(0x3fffff)) != (addr & ~(0x3fffff))) अणु
			copy_len = (u32)(((addr & ~(0x3fffff)) +
				   (MEMOPS_IDX << 22)) - addr);
		पूर्ण अन्यथा अणु
			copy_len = len;
		पूर्ण

		अगर (op) अणु	/* पढ़ो from core */
			octeon_pci_fastपढ़ो(oct, mapped_addr, hostbuf,
					    copy_len);
		पूर्ण अन्यथा अणु
			octeon_pci_fastग_लिखो(oct, mapped_addr, hostbuf,
					     copy_len);
		पूर्ण

		len -= copy_len;
		addr += copy_len;
		hostbuf += copy_len;

	पूर्ण जबतक (len);

	oct->fn_list.bar1_idx_ग_लिखो(oct, MEMOPS_IDX, index_reg_val);

	spin_unlock_irqrestore(&oct->mem_access_lock, flags);
पूर्ण

व्योम
octeon_pci_पढ़ो_core_mem(काष्ठा octeon_device *oct,
			 u64 coपढ़ोdr,
			 u8 *buf,
			 u32 len)
अणु
	__octeon_pci_rw_core_mem(oct, coपढ़ोdr, buf, len, 1);
पूर्ण

व्योम
octeon_pci_ग_लिखो_core_mem(काष्ठा octeon_device *oct,
			  u64 coपढ़ोdr,
			  स्थिर u8 *buf,
			  u32 len)
अणु
	__octeon_pci_rw_core_mem(oct, coपढ़ोdr, (u8 *)buf, len, 0);
पूर्ण

u64 octeon_पढ़ो_device_mem64(काष्ठा octeon_device *oct, u64 coपढ़ोdr)
अणु
	__be64 ret;

	__octeon_pci_rw_core_mem(oct, coपढ़ोdr, (u8 *)&ret, 8, 1);

	वापस be64_to_cpu(ret);
पूर्ण

u32 octeon_पढ़ो_device_mem32(काष्ठा octeon_device *oct, u64 coपढ़ोdr)
अणु
	__be32 ret;

	__octeon_pci_rw_core_mem(oct, coपढ़ोdr, (u8 *)&ret, 4, 1);

	वापस be32_to_cpu(ret);
पूर्ण

व्योम octeon_ग_लिखो_device_mem32(काष्ठा octeon_device *oct, u64 coपढ़ोdr,
			       u32 val)
अणु
	__be32 t = cpu_to_be32(val);

	__octeon_pci_rw_core_mem(oct, coपढ़ोdr, (u8 *)&t, 4, 0);
पूर्ण
