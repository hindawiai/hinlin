<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 Atheros Communications, Inc.,  All Rights Reserved.
 * Copyright (C) 2006 FON Technology, SL.
 * Copyright (C) 2006 Imre Kaloz <kaloz@खोलोwrt.org>
 * Copyright (C) 2006-2009 Felix Fietkau <nbd@खोलोwrt.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/समय.स>

#समावेश <ath25_platक्रमm.h>
#समावेश "devices.h"
#समावेश "ar5312.h"
#समावेश "ar2315.h"

व्योम (*ath25_irq_dispatch)(व्योम);

अटल अंतरभूत bool check_radio_magic(स्थिर व्योम __iomem *addr)
अणु
	addr += 0x7a; /* offset क्रम flash magic */
	वापस (__raw_पढ़ोb(addr) == 0x5a) && (__raw_पढ़ोb(addr + 1) == 0xa5);
पूर्ण

अटल अंतरभूत bool check_notempty(स्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोl(addr) != 0xffffffff;
पूर्ण

अटल अंतरभूत bool check_board_data(स्थिर व्योम __iomem *addr, bool broken)
अणु
	/* config magic found */
	अगर (__raw_पढ़ोl(addr) == ATH25_BD_MAGIC)
		वापस true;

	अगर (!broken)
		वापस false;

	/* broken board data detected, use radio data to find the
	 * offset, user will fix this */

	अगर (check_radio_magic(addr + 0x1000))
		वापस true;
	अगर (check_radio_magic(addr + 0xf8))
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर व्योम __iomem * __init find_board_config(स्थिर व्योम __iomem *limit,
						     स्थिर bool broken)
अणु
	स्थिर व्योम __iomem *addr;
	स्थिर व्योम __iomem *begin = limit - 0x1000;
	स्थिर व्योम __iomem *end = limit - 0x30000;

	क्रम (addr = begin; addr >= end; addr -= 0x1000)
		अगर (check_board_data(addr, broken))
			वापस addr;

	वापस शून्य;
पूर्ण

अटल स्थिर व्योम __iomem * __init find_radio_config(स्थिर व्योम __iomem *limit,
						     स्थिर व्योम __iomem *bcfg)
अणु
	स्थिर व्योम __iomem *rcfg, *begin, *end;

	/*
	 * Now find the start of Radio Configuration data, using heuristics:
	 * Search क्रमward from Board Configuration data by 0x1000 bytes
	 * at a समय until we find non-0xffffffff.
	 */
	begin = bcfg + 0x1000;
	end = limit;
	क्रम (rcfg = begin; rcfg < end; rcfg += 0x1000)
		अगर (check_notempty(rcfg) && check_radio_magic(rcfg))
			वापस rcfg;

	/* AR2316 relocates radio config to new location */
	begin = bcfg + 0xf8;
	end = limit - 0x1000 + 0xf8;
	क्रम (rcfg = begin; rcfg < end; rcfg += 0x1000)
		अगर (check_notempty(rcfg) && check_radio_magic(rcfg))
			वापस rcfg;

	वापस शून्य;
पूर्ण

/*
 * NB: Search region size could be larger than the actual flash size,
 * but this shouldn't be a problem here, because the flash
 * will simply be mapped multiple बार.
 */
पूर्णांक __init ath25_find_config(phys_addr_t base, अचिन्हित दीर्घ size)
अणु
	स्थिर व्योम __iomem *flash_base, *flash_limit;
	काष्ठा ath25_boarddata *config;
	अचिन्हित पूर्णांक rcfg_size;
	पूर्णांक broken_boarddata = 0;
	स्थिर व्योम __iomem *bcfg, *rcfg;
	u8 *board_data;
	u8 *radio_data;
	u8 *mac_addr;
	u32 offset;

	flash_base = ioremap(base, size);
	flash_limit = flash_base + size;

	ath25_board.config = शून्य;
	ath25_board.radio = शून्य;

	/* Copy the board and radio data to RAM, because accessing the mapped
	 * memory of the flash directly after booting is not safe */

	/* Try to find valid board and radio data */
	bcfg = find_board_config(flash_limit, false);

	/* If that fails, try to at least find valid radio data */
	अगर (!bcfg) अणु
		bcfg = find_board_config(flash_limit, true);
		broken_boarddata = 1;
	पूर्ण

	अगर (!bcfg) अणु
		pr_warn("WARNING: No board configuration data found!\n");
		जाओ error;
	पूर्ण

	board_data = kzalloc(BOARD_CONFIG_BUFSZ, GFP_KERNEL);
	अगर (!board_data)
		जाओ error;
	ath25_board.config = (काष्ठा ath25_boarddata *)board_data;
	स_नकल_fromio(board_data, bcfg, 0x100);
	अगर (broken_boarddata) अणु
		pr_warn("WARNING: broken board data detected\n");
		config = ath25_board.config;
		अगर (is_zero_ether_addr(config->enet0_mac)) अणु
			pr_info("Fixing up empty mac addresses\n");
			config->reset_config_gpio = 0xffff;
			config->sys_led_gpio = 0xffff;
			eth_अक्रमom_addr(config->wlan0_mac);
			config->wlan0_mac[0] &= ~0x06;
			eth_अक्रमom_addr(config->enet0_mac);
			eth_अक्रमom_addr(config->enet1_mac);
		पूर्ण
	पूर्ण

	/* Radio config starts 0x100 bytes after board config, regardless
	 * of what the physical layout on the flash chip looks like */

	rcfg = find_radio_config(flash_limit, bcfg);
	अगर (!rcfg) अणु
		pr_warn("WARNING: Could not find Radio Configuration data\n");
		जाओ error;
	पूर्ण

	radio_data = board_data + 0x100 + ((rcfg - bcfg) & 0xfff);
	ath25_board.radio = radio_data;
	offset = radio_data - board_data;
	pr_info("Radio config found at offset 0x%x (0x%x)\n", rcfg - bcfg,
		offset);
	rcfg_size = BOARD_CONFIG_BUFSZ - offset;
	स_नकल_fromio(radio_data, rcfg, rcfg_size);

	mac_addr = &radio_data[0x1d * 2];
	अगर (is_broadcast_ether_addr(mac_addr)) अणु
		pr_info("Radio MAC is blank; using board-data\n");
		ether_addr_copy(mac_addr, ath25_board.config->wlan0_mac);
	पूर्ण

	iounmap(flash_base);

	वापस 0;

error:
	iounmap(flash_base);
	वापस -ENODEV;
पूर्ण

अटल व्योम ath25_halt(व्योम)
अणु
	local_irq_disable();
	unreachable();
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	_machine_halt = ath25_halt;
	pm_घातer_off = ath25_halt;

	अगर (is_ar5312())
		ar5312_plat_mem_setup();
	अन्यथा
		ar2315_plat_mem_setup();

	/* Disable data watchpoपूर्णांकs */
	ग_लिखो_c0_watchlo0(0);
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	ath25_irq_dispatch();
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	अगर (is_ar5312())
		ar5312_plat_समय_init();
	अन्यथा
		ar2315_plat_समय_init();
पूर्ण

अचिन्हित पूर्णांक get_c0_compare_पूर्णांक(व्योम)
अणु
	वापस CP0_LEGACY_COMPARE_IRQ;
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	clear_c0_status(ST0_IM);
	mips_cpu_irq_init();

	/* Initialize पूर्णांकerrupt controllers */
	अगर (is_ar5312())
		ar5312_arch_init_irq();
	अन्यथा
		ar2315_arch_init_irq();
पूर्ण
