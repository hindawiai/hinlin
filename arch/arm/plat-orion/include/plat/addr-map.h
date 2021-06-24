<शैली गुरु>
/*
 * arch/arm/plat-orion/include/plat/addr-map.h
 *
 * Marvell Orion SoC address map handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __PLAT_ADDR_MAP_H
#घोषणा __PLAT_ADDR_MAP_H

बाह्य काष्ठा mbus_dram_target_info orion_mbus_dram_info;

काष्ठा orion_addr_map_cfg अणु
	स्थिर पूर्णांक num_wins;	/* Total number of winकरोws */
	स्थिर पूर्णांक remappable_wins;
	व्योम __iomem *bridge_virt_base;
	पूर्णांक hw_io_coherency;

	/* If शून्य, the शेष cpu_win_can_remap will be used, using
	   the value in remappable_wins */
	पूर्णांक (*cpu_win_can_remap) (स्थिर काष्ठा orion_addr_map_cfg *cfg,
				  स्थिर पूर्णांक win);
	/* If शून्य, the शेष win_cfg_base will be used, using the
	   value in bridge_virt_base */
	व्योम __iomem *(*win_cfg_base) (स्थिर काष्ठा orion_addr_map_cfg *cfg,
				 स्थिर पूर्णांक win);
पूर्ण;

/*
 * Inक्रमmation needed to setup one address mapping.
 */
काष्ठा orion_addr_map_info अणु
	स्थिर पूर्णांक win;
	स्थिर u32 base;
	स्थिर u32 size;
	स्थिर u8 target;
	स्थिर u8 attr;
	स्थिर पूर्णांक remap;
पूर्ण;

व्योम __init orion_config_wins(काष्ठा orion_addr_map_cfg *cfg,
			      स्थिर काष्ठा orion_addr_map_info *info);

व्योम __init orion_setup_cpu_win(स्थिर काष्ठा orion_addr_map_cfg *cfg,
				स्थिर पूर्णांक win, स्थिर u32 base,
				स्थिर u32 size, स्थिर u8 target,
				स्थिर u8 attr, स्थिर पूर्णांक remap);

व्योम __init orion_setup_cpu_mbus_target(स्थिर काष्ठा orion_addr_map_cfg *cfg,
					स्थिर व्योम __iomem *ddr_winकरोw_cpu_base);
#पूर्ण_अगर
