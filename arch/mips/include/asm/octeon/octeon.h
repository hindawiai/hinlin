<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004-2008 Cavium Networks
 */
#अगर_अघोषित __ASM_OCTEON_OCTEON_H
#घोषणा __ASM_OCTEON_OCTEON_H

#समावेश <यंत्र/octeon/cvmx.h>
#समावेश <यंत्र/bitfield.h>

बाह्य uपूर्णांक64_t octeon_booपंचांगem_alloc_range_phys(uपूर्णांक64_t size,
						uपूर्णांक64_t alignment,
						uपूर्णांक64_t min_addr,
						uपूर्णांक64_t max_addr,
						पूर्णांक करो_locking);
बाह्य व्योम *octeon_booपंचांगem_alloc(uपूर्णांक64_t size, uपूर्णांक64_t alignment,
				  पूर्णांक करो_locking);
बाह्य व्योम *octeon_booपंचांगem_alloc_range(uपूर्णांक64_t size, uपूर्णांक64_t alignment,
					uपूर्णांक64_t min_addr, uपूर्णांक64_t max_addr,
					पूर्णांक करो_locking);
बाह्य व्योम *octeon_booपंचांगem_alloc_named(uपूर्णांक64_t size, uपूर्णांक64_t alignment,
					अक्षर *name);
बाह्य व्योम *octeon_booपंचांगem_alloc_named_range(uपूर्णांक64_t size, uपूर्णांक64_t min_addr,
					      uपूर्णांक64_t max_addr, uपूर्णांक64_t align,
					      अक्षर *name);
बाह्य व्योम *octeon_booपंचांगem_alloc_named_address(uपूर्णांक64_t size, uपूर्णांक64_t address,
						अक्षर *name);
बाह्य पूर्णांक octeon_booपंचांगem_मुक्त_named(अक्षर *name);
बाह्य व्योम octeon_booपंचांगem_lock(व्योम);
बाह्य व्योम octeon_booपंचांगem_unlock(व्योम);

बाह्य पूर्णांक octeon_is_simulation(व्योम);
बाह्य पूर्णांक octeon_is_pci_host(व्योम);
बाह्य पूर्णांक octeon_usb_is_ref_clk(व्योम);
बाह्य uपूर्णांक64_t octeon_get_घड़ी_rate(व्योम);
बाह्य u64 octeon_get_io_घड़ी_rate(व्योम);
बाह्य स्थिर अक्षर *octeon_board_type_string(व्योम);
बाह्य स्थिर अक्षर *octeon_get_pci_पूर्णांकerrupts(व्योम);
बाह्य पूर्णांक octeon_get_southbridge_पूर्णांकerrupt(व्योम);
बाह्य पूर्णांक octeon_get_boot_coremask(व्योम);
बाह्य पूर्णांक octeon_get_boot_num_arguments(व्योम);
बाह्य स्थिर अक्षर *octeon_get_boot_argument(पूर्णांक arg);
बाह्य व्योम octeon_hal_setup_reserved32(व्योम);
बाह्य व्योम octeon_user_io_init(व्योम);

बाह्य व्योम octeon_init_cvmcount(व्योम);
बाह्य व्योम octeon_setup_delays(व्योम);
बाह्य व्योम octeon_io_clk_delay(अचिन्हित दीर्घ);

#घोषणा OCTEON_ARGV_MAX_ARGS	64
#घोषणा OCTEON_SERIAL_LEN	20

काष्ठा octeon_boot_descriptor अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	/* Start of block referenced by assembly code - करो not change! */
	uपूर्णांक32_t desc_version;
	uपूर्णांक32_t desc_size;
	uपूर्णांक64_t stack_top;
	uपूर्णांक64_t heap_base;
	uपूर्णांक64_t heap_end;
	/* Only used by bootloader */
	uपूर्णांक64_t entry_poपूर्णांक;
	uपूर्णांक64_t desc_vaddr;
	/* End of This block referenced by assembly code - करो not change! */
	uपूर्णांक32_t exception_base_addr;
	uपूर्णांक32_t stack_size;
	uपूर्णांक32_t heap_size;
	/* Argc count क्रम application. */
	uपूर्णांक32_t argc;
	uपूर्णांक32_t argv[OCTEON_ARGV_MAX_ARGS];

#घोषणा	 BOOT_FLAG_INIT_CORE		(1 << 0)
#घोषणा	 OCTEON_BL_FLAG_DEBUG		(1 << 1)
#घोषणा	 OCTEON_BL_FLAG_NO_MAGIC	(1 << 2)
	/* If set, use uart1 क्रम console */
#घोषणा	 OCTEON_BL_FLAG_CONSOLE_UART1	(1 << 3)
	/* If set, use PCI console */
#घोषणा	 OCTEON_BL_FLAG_CONSOLE_PCI	(1 << 4)
	/* Call निकास on अवरोध on serial port */
#घोषणा	 OCTEON_BL_FLAG_BREAK		(1 << 5)

	uपूर्णांक32_t flags;
	uपूर्णांक32_t core_mask;
	/* DRAM size in megabyes. */
	uपूर्णांक32_t dram_size;
	/* physical address of मुक्त memory descriptor block. */
	uपूर्णांक32_t phy_mem_desc_addr;
	/* used to pass flags from app to debugger. */
	uपूर्णांक32_t debugger_flags_base_addr;
	/* CPU घड़ी speed, in hz. */
	uपूर्णांक32_t eघड़ी_hz;
	/* DRAM घड़ी speed, in hz. */
	uपूर्णांक32_t dघड़ी_hz;
	/* SPI4 घड़ी in hz. */
	uपूर्णांक32_t spi_घड़ी_hz;
	uपूर्णांक16_t board_type;
	uपूर्णांक8_t board_rev_major;
	uपूर्णांक8_t board_rev_minor;
	uपूर्णांक16_t chip_type;
	uपूर्णांक8_t chip_rev_major;
	uपूर्णांक8_t chip_rev_minor;
	अक्षर board_serial_number[OCTEON_SERIAL_LEN];
	uपूर्णांक8_t mac_addr_base[6];
	uपूर्णांक8_t mac_addr_count;
	uपूर्णांक64_t cvmx_desc_vaddr;
#अन्यथा
	uपूर्णांक32_t desc_size;
	uपूर्णांक32_t desc_version;
	uपूर्णांक64_t stack_top;
	uपूर्णांक64_t heap_base;
	uपूर्णांक64_t heap_end;
	/* Only used by bootloader */
	uपूर्णांक64_t entry_poपूर्णांक;
	uपूर्णांक64_t desc_vaddr;
	/* End of This block referenced by assembly code - करो not change! */
	uपूर्णांक32_t stack_size;
	uपूर्णांक32_t exception_base_addr;
	uपूर्णांक32_t argc;
	uपूर्णांक32_t heap_size;
	/*
	 * Argc count क्रम application.
	 * Warning low bit scrambled in little-endian.
	 */
	uपूर्णांक32_t argv[OCTEON_ARGV_MAX_ARGS];

#घोषणा  BOOT_FLAG_INIT_CORE		(1 << 0)
#घोषणा  OCTEON_BL_FLAG_DEBUG		(1 << 1)
#घोषणा  OCTEON_BL_FLAG_NO_MAGIC	(1 << 2)
	/* If set, use uart1 क्रम console */
#घोषणा  OCTEON_BL_FLAG_CONSOLE_UART1	(1 << 3)
	/* If set, use PCI console */
#घोषणा  OCTEON_BL_FLAG_CONSOLE_PCI	(1 << 4)
	/* Call निकास on अवरोध on serial port */
#घोषणा  OCTEON_BL_FLAG_BREAK		(1 << 5)

	uपूर्णांक32_t core_mask;
	uपूर्णांक32_t flags;
	/* physical address of मुक्त memory descriptor block. */
	uपूर्णांक32_t phy_mem_desc_addr;
	/* DRAM size in megabyes. */
	uपूर्णांक32_t dram_size;
	/* CPU घड़ी speed, in hz. */
	uपूर्णांक32_t eघड़ी_hz;
	/* used to pass flags from app to debugger. */
	uपूर्णांक32_t debugger_flags_base_addr;
	/* SPI4 घड़ी in hz. */
	uपूर्णांक32_t spi_घड़ी_hz;
	/* DRAM घड़ी speed, in hz. */
	uपूर्णांक32_t dघड़ी_hz;
	uपूर्णांक8_t chip_rev_minor;
	uपूर्णांक8_t chip_rev_major;
	uपूर्णांक16_t chip_type;
	uपूर्णांक8_t board_rev_minor;
	uपूर्णांक8_t board_rev_major;
	uपूर्णांक16_t board_type;

	uपूर्णांक64_t unused1[4]; /* Not even filled in by bootloader. */

	uपूर्णांक64_t cvmx_desc_vaddr;
#पूर्ण_अगर
पूर्ण;

जोड़ octeon_cvmemctl अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
		/* RO 1 = BIST fail, 0 = BIST pass */
		__BITFIELD_FIELD(uपूर्णांक64_t tlbbist:1,
		/* RO 1 = BIST fail, 0 = BIST pass */
		__BITFIELD_FIELD(uपूर्णांक64_t l1cbist:1,
		/* RO 1 = BIST fail, 0 = BIST pass */
		__BITFIELD_FIELD(uपूर्णांक64_t l1dbist:1,
		/* RO 1 = BIST fail, 0 = BIST pass */
		__BITFIELD_FIELD(uपूर्णांक64_t dcmbist:1,
		/* RO 1 = BIST fail, 0 = BIST pass */
		__BITFIELD_FIELD(uपूर्णांक64_t ptgbist:1,
		/* RO 1 = BIST fail, 0 = BIST pass */
		__BITFIELD_FIELD(uपूर्णांक64_t wbfbist:1,
		/* Reserved */
		__BITFIELD_FIELD(uपूर्णांक64_t reserved:17,
		/* OCTEON II - TLB replacement policy: 0 = biपंचांगask LRU; 1 = NLU.
		 * This field selects between the TLB replacement policies:
		 * biपंचांगask LRU or NLU. Biपंचांगask LRU मुख्यtains a mask of
		 * recently used TLB entries and aव्योमs them as new entries
		 * are allocated. NLU simply guarantees that the next
		 * allocation is not the last used TLB entry. */
		__BITFIELD_FIELD(uपूर्णांक64_t tlbnlu:1,
		/* OCTEON II - Selects the bit in the counter used क्रम
		 * releasing a PAUSE. This counter trips every 2(8+PAUSETIME)
		 * cycles. If not alपढ़ोy released, the cnMIPS II core will
		 * always release a given PAUSE inकाष्ठाion within
		 * 2(8+PAUSETIME). If the counter trip happens to line up,
		 * the cnMIPS II core may release the PAUSE instantly. */
		__BITFIELD_FIELD(uपूर्णांक64_t छोड़ोसमय:3,
		/* OCTEON II - This field is an extension of
		 * CvmMemCtl[DIDTTO] */
		__BITFIELD_FIELD(uपूर्णांक64_t didtto2:1,
		/* R/W If set, marked ग_लिखो-buffer entries समय out
		 * the same as other entries; अगर clear, marked
		 * ग_लिखो-buffer entries use the maximum समयout. */
		__BITFIELD_FIELD(uपूर्णांक64_t dismarkwbदीर्घto:1,
		/* R/W If set, a merged store करोes not clear the
		 * ग_लिखो-buffer entry समयout state. */
		__BITFIELD_FIELD(uपूर्णांक64_t dismrgclrwbto:1,
		/* R/W Two bits that are the MSBs of the resultant
		 * CVMSEG LM word location क्रम an IOBDMA. The other 8
		 * bits come from the SCRADDR field of the IOBDMA. */
		__BITFIELD_FIELD(uपूर्णांक64_t iobdmascrmsb:2,
		/* R/W If set, SYNCWS and SYNCS only order marked
		 * stores; अगर clear, SYNCWS and SYNCS only order
		 * unmarked stores. SYNCWSMARKED has no effect when
		 * DISSYNCWS is set. */
		__BITFIELD_FIELD(uपूर्णांक64_t syncwsmarked:1,
		/* R/W If set, SYNCWS acts as SYNCW and SYNCS acts as
		 * SYNC. */
		__BITFIELD_FIELD(uपूर्णांक64_t dissyncws:1,
		/* R/W If set, no stall happens on ग_लिखो buffer
		 * full. */
		__BITFIELD_FIELD(uपूर्णांक64_t diswbfst:1,
		/* R/W If set (and SX set), supervisor-level
		 * loads/stores can use XKPHYS addresses with
		 * VA<48>==0 */
		__BITFIELD_FIELD(uपूर्णांक64_t xkmemenas:1,
		/* R/W If set (and UX set), user-level loads/stores
		 * can use XKPHYS addresses with VA<48>==0 */
		__BITFIELD_FIELD(uपूर्णांक64_t xkmemenau:1,
		/* R/W If set (and SX set), supervisor-level
		 * loads/stores can use XKPHYS addresses with
		 * VA<48>==1 */
		__BITFIELD_FIELD(uपूर्णांक64_t xkioenas:1,
		/* R/W If set (and UX set), user-level loads/stores
		 * can use XKPHYS addresses with VA<48>==1 */
		__BITFIELD_FIELD(uपूर्णांक64_t xkioenau:1,
		/* R/W If set, all stores act as SYNCW (NOMERGE must
		 * be set when this is set) RW, reset to 0. */
		__BITFIELD_FIELD(uपूर्णांक64_t allsyncw:1,
		/* R/W If set, no stores merge, and all stores reach
		 * the coherent bus in order. */
		__BITFIELD_FIELD(uपूर्णांक64_t nomerge:1,
		/* R/W Selects the bit in the counter used क्रम DID
		 * समय-outs 0 = 231, 1 = 230, 2 = 229, 3 =
		 * 214. Actual समय-out is between 1x and 2x this
		 * पूर्णांकerval. For example, with DIDTTO=3, expiration
		 * पूर्णांकerval is between 16K and 32K. */
		__BITFIELD_FIELD(uपूर्णांक64_t didtto:2,
		/* R/W If set, the (mem) CSR घड़ी never turns off. */
		__BITFIELD_FIELD(uपूर्णांक64_t csrckalwys:1,
		/* R/W If set, mclk never turns off. */
		__BITFIELD_FIELD(uपूर्णांक64_t mclkalwys:1,
		/* R/W Selects the bit in the counter used क्रम ग_लिखो
		 * buffer flush समय-outs (WBFLT+11) is the bit
		 * position in an पूर्णांकernal counter used to determine
		 * expiration. The ग_लिखो buffer expires between 1x and
		 * 2x this पूर्णांकerval. For example, with WBFLT = 0, a
		 * ग_लिखो buffer expires between 2K and 4K cycles after
		 * the ग_लिखो buffer entry is allocated. */
		__BITFIELD_FIELD(uपूर्णांक64_t wbflसमय:3,
		/* R/W If set, करो not put Istream in the L2 cache. */
		__BITFIELD_FIELD(uपूर्णांक64_t istrnol2:1,
		/* R/W The ग_लिखो buffer threshold. */
		__BITFIELD_FIELD(uपूर्णांक64_t wbthresh:4,
		/* Reserved */
		__BITFIELD_FIELD(uपूर्णांक64_t reserved2:2,
		/* R/W If set, CVMSEG is available क्रम loads/stores in
		 * kernel/debug mode. */
		__BITFIELD_FIELD(uपूर्णांक64_t cvmsegenak:1,
		/* R/W If set, CVMSEG is available क्रम loads/stores in
		 * supervisor mode. */
		__BITFIELD_FIELD(uपूर्णांक64_t cvmsegenas:1,
		/* R/W If set, CVMSEG is available क्रम loads/stores in
		 * user mode. */
		__BITFIELD_FIELD(uपूर्णांक64_t cvmsegenau:1,
		/* R/W Size of local memory in cache blocks, 54 (6912
		 * bytes) is max legal value. */
		__BITFIELD_FIELD(uपूर्णांक64_t lmemsz:6,
		;)))))))))))))))))))))))))))))))))
	पूर्ण s;
पूर्ण;

बाह्य व्योम octeon_check_cpu_bist(व्योम);

पूर्णांक octeon_prune_device_tree(व्योम);
बाह्य स्थिर अक्षर __dtb_octeon_3xxx_begin;
बाह्य स्थिर अक्षर __dtb_octeon_68xx_begin;

/**
 * Write a 32bit value to the Octeon NPI रेजिस्टर space
 *
 * @address: Address to ग_लिखो to
 * @val:     Value to ग_लिखो
 */
अटल अंतरभूत व्योम octeon_npi_ग_लिखो32(uपूर्णांक64_t address, uपूर्णांक32_t val)
अणु
	cvmx_ग_लिखो64_uपूर्णांक32(address ^ 4, val);
	cvmx_पढ़ो64_uपूर्णांक32(address ^ 4);
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम octeon_setup_smp(व्योम);
#अन्यथा
अटल अंतरभूत व्योम octeon_setup_smp(व्योम) अणुपूर्ण
#पूर्ण_अगर

काष्ठा irq_करोमुख्य;
काष्ठा device_node;
काष्ठा irq_data;
काष्ठा irq_chip;
व्योम octeon_ciu3_mbox_send(पूर्णांक cpu, अचिन्हित पूर्णांक mbox);
पूर्णांक octeon_irq_ciu3_xlat(काष्ठा irq_करोमुख्य *d,
			 काष्ठा device_node *node,
			 स्थिर u32 *पूर्णांकspec,
			 अचिन्हित पूर्णांक पूर्णांकsize,
			 अचिन्हित दीर्घ *out_hwirq,
			 अचिन्हित पूर्णांक *out_type);
व्योम octeon_irq_ciu3_enable(काष्ठा irq_data *data);
व्योम octeon_irq_ciu3_disable(काष्ठा irq_data *data);
व्योम octeon_irq_ciu3_ack(काष्ठा irq_data *data);
व्योम octeon_irq_ciu3_mask(काष्ठा irq_data *data);
व्योम octeon_irq_ciu3_mask_ack(काष्ठा irq_data *data);
पूर्णांक octeon_irq_ciu3_mapx(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw, काष्ठा irq_chip *chip);

/* Octeon multiplier save/restore routines from octeon_चयन.S */
व्योम octeon_mult_save(व्योम);
व्योम octeon_mult_restore(व्योम);
व्योम octeon_mult_save_end(व्योम);
व्योम octeon_mult_restore_end(व्योम);
व्योम octeon_mult_save3(व्योम);
व्योम octeon_mult_save3_end(व्योम);
व्योम octeon_mult_save2(व्योम);
व्योम octeon_mult_save2_end(व्योम);
व्योम octeon_mult_restore3(व्योम);
व्योम octeon_mult_restore3_end(व्योम);
व्योम octeon_mult_restore2(व्योम);
व्योम octeon_mult_restore2_end(व्योम);

/**
 * Read a 32bit value from the Octeon NPI रेजिस्टर space
 *
 * @address: Address to पढ़ो
 * Returns The result
 */
अटल अंतरभूत uपूर्णांक32_t octeon_npi_पढ़ो32(uपूर्णांक64_t address)
अणु
	वापस cvmx_पढ़ो64_uपूर्णांक32(address ^ 4);
पूर्ण

बाह्य काष्ठा cvmx_bootinfo *octeon_bootinfo;

बाह्य uपूर्णांक64_t octeon_bootloader_entry_addr;

बाह्य व्योम (*octeon_irq_setup_secondary)(व्योम);

प्रकार व्योम (*octeon_irq_ip4_handler_t)(व्योम);
व्योम octeon_irq_set_ip4_handler(octeon_irq_ip4_handler_t);

बाह्य व्योम octeon_fixup_irqs(व्योम);

बाह्य काष्ठा semaphore octeon_bootbus_sem;

काष्ठा irq_करोमुख्य *octeon_irq_get_block_करोमुख्य(पूर्णांक node, uपूर्णांक8_t block);

#पूर्ण_अगर /* __ASM_OCTEON_OCTEON_H */
