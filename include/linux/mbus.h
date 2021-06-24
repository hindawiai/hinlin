<शैली गुरु>
/*
 * Marvell MBUS common definitions.
 *
 * Copyright (C) 2008 Marvell Semiconductor
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __LINUX_MBUS_H
#घोषणा __LINUX_MBUS_H

#समावेश <linux/त्रुटिसं.स>

काष्ठा resource;

काष्ठा mbus_dram_target_info
अणु
	/*
	 * The 4-bit MBUS target ID of the DRAM controller.
	 */
	u8		mbus_dram_target_id;

	/*
	 * The base address, size, and MBUS attribute ID क्रम each
	 * of the possible DRAM chip selects.  Peripherals are
	 * required to support at least 4 decode winकरोws.
	 */
	पूर्णांक		num_cs;
	काष्ठा mbus_dram_winकरोw अणु
		u8	cs_index;
		u8	mbus_attr;
		u64	base;
		u64	size;
	पूर्ण cs[4];
पूर्ण;

/* Flags क्रम PCI/PCIe address decoding regions */
#घोषणा MVEBU_MBUS_PCI_IO  0x1
#घोषणा MVEBU_MBUS_PCI_MEM 0x2
#घोषणा MVEBU_MBUS_PCI_WA  0x3

/*
 * Magic value that explicits that we करोn't need a remapping-capable
 * address decoding winकरोw.
 */
#घोषणा MVEBU_MBUS_NO_REMAP (0xffffffff)

/* Maximum size of a mbus winकरोw name */
#घोषणा MVEBU_MBUS_MAX_WINNAME_SZ 32

/*
 * The Marvell mbus is to be found only on SOCs from the Orion family
 * at the moment.  Provide a dummy stub क्रम other architectures.
 */
#अगर_घोषित CONFIG_PLAT_ORION
बाह्य स्थिर काष्ठा mbus_dram_target_info *mv_mbus_dram_info(व्योम);
बाह्य स्थिर काष्ठा mbus_dram_target_info *mv_mbus_dram_info_nooverlap(व्योम);
पूर्णांक mvebu_mbus_get_io_win_info(phys_addr_t phyaddr, u32 *size, u8 *target,
			       u8 *attr);
#अन्यथा
अटल अंतरभूत स्थिर काष्ठा mbus_dram_target_info *mv_mbus_dram_info(व्योम)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत स्थिर काष्ठा mbus_dram_target_info *mv_mbus_dram_info_nooverlap(व्योम)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक mvebu_mbus_get_io_win_info(phys_addr_t phyaddr, u32 *size,
					     u8 *target, u8 *attr)
अणु
	/*
	 * On all ARM32 MVEBU platक्रमms with MBus support, this stub
	 * function will not get called. The real function from the
	 * MBus driver is called instead. ARM64 MVEBU platक्रमms like
	 * the Armada 3700 could use the mv_xor device driver which calls
	 * पूर्णांकo this function
	 */
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MVEBU_MBUS
पूर्णांक mvebu_mbus_save_cpu_target(u32 __iomem *store_addr);
व्योम mvebu_mbus_get_pcie_mem_aperture(काष्ठा resource *res);
व्योम mvebu_mbus_get_pcie_io_aperture(काष्ठा resource *res);
पूर्णांक mvebu_mbus_get_dram_win_info(phys_addr_t phyaddr, u8 *target, u8 *attr);
पूर्णांक mvebu_mbus_add_winकरोw_remap_by_id(अचिन्हित पूर्णांक target,
				      अचिन्हित पूर्णांक attribute,
				      phys_addr_t base, माप_प्रकार size,
				      phys_addr_t remap);
पूर्णांक mvebu_mbus_add_winकरोw_by_id(अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक attribute,
				phys_addr_t base, माप_प्रकार size);
पूर्णांक mvebu_mbus_del_winकरोw(phys_addr_t base, माप_प्रकार size);
पूर्णांक mvebu_mbus_init(स्थिर अक्षर *soc, phys_addr_t mbus_phys_base,
		    माप_प्रकार mbus_size, phys_addr_t sdram_phys_base,
		    माप_प्रकार sdram_size);
पूर्णांक mvebu_mbus_dt_init(bool is_coherent);
#अन्यथा
अटल अंतरभूत पूर्णांक mvebu_mbus_get_dram_win_info(phys_addr_t phyaddr, u8 *target,
					       u8 *attr)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_MVEBU_MBUS */

#पूर्ण_अगर /* __LINUX_MBUS_H */
