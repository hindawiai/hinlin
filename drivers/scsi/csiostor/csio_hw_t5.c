<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2013 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "csio_hw.h"
#समावेश "csio_init.h"

अटल पूर्णांक
csio_t5_set_mem_win(काष्ठा csio_hw *hw, uपूर्णांक32_t win)
अणु
	u32 mem_win_base;
	/*
	 * Truncation पूर्णांकentional: we only पढ़ो the bottom 32-bits of the
	 * 64-bit BAR0/BAR1 ...  We use the hardware backकरोor mechanism to
	 * पढ़ो BAR0 instead of using pci_resource_start() because we could be
	 * operating from within a Virtual Machine which is trapping our
	 * accesses to our Configuration Space and we need to set up the PCI-E
	 * Memory Winकरोw decoders with the actual addresses which will be
	 * coming across the PCI-E link.
	 */

	/* For T5, only relative offset inside the PCIe BAR is passed */
	mem_win_base = MEMWIN_BASE;

	/*
	 * Set up memory winकरोw क्रम accessing adapter memory ranges.  (Read
	 * back MA रेजिस्टर to ensure that changes propagate beक्रमe we attempt
	 * to use the new values.)
	 */
	csio_wr_reg32(hw, mem_win_base | BIR_V(0) |
			  WINDOW_V(ilog2(MEMWIN_APERTURE) - 10),
			  PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, win));
	csio_rd_reg32(hw,
		      PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, win));

	वापस 0;
पूर्ण

/*
 * Interrupt handler क्रम the PCIE module.
 */
अटल व्योम
csio_t5_pcie_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info pcie_पूर्णांकr_info[] = अणु
		अणु MSTGRPPERR_F, "Master Response Read Queue parity error",
		-1, 1 पूर्ण,
		अणु MSTTIMEOUTPERR_F, "Master Timeout FIFO parity error", -1, 1 पूर्ण,
		अणु MSIXSTIPERR_F, "MSI-X STI SRAM parity error", -1, 1 पूर्ण,
		अणु MSIXADDRLPERR_F, "MSI-X AddrL parity error", -1, 1 पूर्ण,
		अणु MSIXADDRHPERR_F, "MSI-X AddrH parity error", -1, 1 पूर्ण,
		अणु MSIXDATAPERR_F, "MSI-X data parity error", -1, 1 पूर्ण,
		अणु MSIXDIPERR_F, "MSI-X DI parity error", -1, 1 पूर्ण,
		अणु PIOCPLGRPPERR_F, "PCI PIO completion Group FIFO parity error",
		-1, 1 पूर्ण,
		अणु PIOREQGRPPERR_F, "PCI PIO request Group FIFO parity error",
		-1, 1 पूर्ण,
		अणु TARTAGPERR_F, "PCI PCI target tag FIFO parity error", -1, 1 पूर्ण,
		अणु MSTTAGQPERR_F, "PCI master tag queue parity error", -1, 1 पूर्ण,
		अणु CREQPERR_F, "PCI CMD channel request parity error", -1, 1 पूर्ण,
		अणु CRSPPERR_F, "PCI CMD channel response parity error", -1, 1 पूर्ण,
		अणु DREQWRPERR_F, "PCI DMA channel write request parity error",
		-1, 1 पूर्ण,
		अणु DREQPERR_F, "PCI DMA channel request parity error", -1, 1 पूर्ण,
		अणु DRSPPERR_F, "PCI DMA channel response parity error", -1, 1 पूर्ण,
		अणु HREQWRPERR_F, "PCI HMA channel count parity error", -1, 1 पूर्ण,
		अणु HREQPERR_F, "PCI HMA channel request parity error", -1, 1 पूर्ण,
		अणु HRSPPERR_F, "PCI HMA channel response parity error", -1, 1 पूर्ण,
		अणु CFGSNPPERR_F, "PCI config snoop FIFO parity error", -1, 1 पूर्ण,
		अणु FIDPERR_F, "PCI FID parity error", -1, 1 पूर्ण,
		अणु VFIDPERR_F, "PCI INTx clear parity error", -1, 1 पूर्ण,
		अणु MAGRPPERR_F, "PCI MA group FIFO parity error", -1, 1 पूर्ण,
		अणु PIOTAGPERR_F, "PCI PIO tag parity error", -1, 1 पूर्ण,
		अणु IPRXHDRGRPPERR_F, "PCI IP Rx header group parity error",
		-1, 1 पूर्ण,
		अणु IPRXDATAGRPPERR_F, "PCI IP Rx data group parity error",
		-1, 1 पूर्ण,
		अणु RPLPERR_F, "PCI IP replay buffer parity error", -1, 1 पूर्ण,
		अणु IPSOTPERR_F, "PCI IP SOT buffer parity error", -1, 1 पूर्ण,
		अणु TRGT1GRPPERR_F, "PCI TRGT1 group FIFOs parity error", -1, 1 पूर्ण,
		अणु READRSPERR_F, "Outbound read error", -1, 0 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	पूर्णांक fat;
	fat = csio_handle_पूर्णांकr_status(hw, PCIE_INT_CAUSE_A, pcie_पूर्णांकr_info);
	अगर (fat)
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * csio_t5_flash_cfg_addr - वापस the address of the flash configuration file
 * @hw: the HW module
 *
 * Return the address within the flash where the Firmware Configuration
 * File is stored.
 */
अटल अचिन्हित पूर्णांक
csio_t5_flash_cfg_addr(काष्ठा csio_hw *hw)
अणु
	वापस FLASH_CFG_START;
पूर्ण

/*
 *      csio_t5_mc_पढ़ो - पढ़ो from MC through backकरोor accesses
 *      @hw: the hw module
 *      @idx: index to the रेजिस्टर
 *      @addr: address of first byte requested
 *      @data: 64 bytes of data containing the requested address
 *      @ecc: where to store the corresponding 64-bit ECC word
 *
 *      Read 64 bytes of data from MC starting at a 64-byte-aligned address
 *      that covers the requested address @addr.  If @parity is not %शून्य it
 *      is asचिन्हित the 64-bit ECC word क्रम the पढ़ो data.
 */
अटल पूर्णांक
csio_t5_mc_पढ़ो(काष्ठा csio_hw *hw, पूर्णांक idx, uपूर्णांक32_t addr, __be32 *data,
		uपूर्णांक64_t *ecc)
अणु
	पूर्णांक i;
	uपूर्णांक32_t mc_bist_cmd_reg, mc_bist_cmd_addr_reg, mc_bist_cmd_len_reg;
	uपूर्णांक32_t mc_bist_data_pattern_reg;

	mc_bist_cmd_reg = MC_REG(MC_P_BIST_CMD_A, idx);
	mc_bist_cmd_addr_reg = MC_REG(MC_P_BIST_CMD_ADDR_A, idx);
	mc_bist_cmd_len_reg = MC_REG(MC_P_BIST_CMD_LEN_A, idx);
	mc_bist_data_pattern_reg = MC_REG(MC_P_BIST_DATA_PATTERN_A, idx);

	अगर (csio_rd_reg32(hw, mc_bist_cmd_reg) & START_BIST_F)
		वापस -EBUSY;
	csio_wr_reg32(hw, addr & ~0x3fU, mc_bist_cmd_addr_reg);
	csio_wr_reg32(hw, 64, mc_bist_cmd_len_reg);
	csio_wr_reg32(hw, 0xc, mc_bist_data_pattern_reg);
	csio_wr_reg32(hw, BIST_OPCODE_V(1) | START_BIST_F |  BIST_CMD_GAP_V(1),
		      mc_bist_cmd_reg);
	i = csio_hw_रुको_op_करोne_val(hw, mc_bist_cmd_reg, START_BIST_F,
				     0, 10, 1, शून्य);
	अगर (i)
		वापस i;

#घोषणा MC_DATA(i) MC_BIST_STATUS_REG(MC_BIST_STATUS_RDATA_A, i)

	क्रम (i = 15; i >= 0; i--)
		*data++ = htonl(csio_rd_reg32(hw, MC_DATA(i)));
	अगर (ecc)
		*ecc = csio_rd_reg64(hw, MC_DATA(16));
#अघोषित MC_DATA
	वापस 0;
पूर्ण

/*
 *      csio_t5_edc_पढ़ो - पढ़ो from EDC through backकरोor accesses
 *      @hw: the hw module
 *      @idx: which EDC to access
 *      @addr: address of first byte requested
 *      @data: 64 bytes of data containing the requested address
 *      @ecc: where to store the corresponding 64-bit ECC word
 *
 *      Read 64 bytes of data from EDC starting at a 64-byte-aligned address
 *      that covers the requested address @addr.  If @parity is not %शून्य it
 *      is asचिन्हित the 64-bit ECC word क्रम the पढ़ो data.
 */
अटल पूर्णांक
csio_t5_edc_पढ़ो(काष्ठा csio_hw *hw, पूर्णांक idx, uपूर्णांक32_t addr, __be32 *data,
		uपूर्णांक64_t *ecc)
अणु
	पूर्णांक i;
	uपूर्णांक32_t edc_bist_cmd_reg, edc_bist_cmd_addr_reg, edc_bist_cmd_len_reg;
	uपूर्णांक32_t edc_bist_cmd_data_pattern;

/*
 * These macro are missing in t4_regs.h file.
 */
#घोषणा EDC_STRIDE_T5 (EDC_T51_BASE_ADDR - EDC_T50_BASE_ADDR)
#घोषणा EDC_REG_T5(reg, idx) (reg + EDC_STRIDE_T5 * idx)

	edc_bist_cmd_reg = EDC_REG_T5(EDC_H_BIST_CMD_A, idx);
	edc_bist_cmd_addr_reg = EDC_REG_T5(EDC_H_BIST_CMD_ADDR_A, idx);
	edc_bist_cmd_len_reg = EDC_REG_T5(EDC_H_BIST_CMD_LEN_A, idx);
	edc_bist_cmd_data_pattern = EDC_REG_T5(EDC_H_BIST_DATA_PATTERN_A, idx);
#अघोषित EDC_REG_T5
#अघोषित EDC_STRIDE_T5

	अगर (csio_rd_reg32(hw, edc_bist_cmd_reg) & START_BIST_F)
		वापस -EBUSY;
	csio_wr_reg32(hw, addr & ~0x3fU, edc_bist_cmd_addr_reg);
	csio_wr_reg32(hw, 64, edc_bist_cmd_len_reg);
	csio_wr_reg32(hw, 0xc, edc_bist_cmd_data_pattern);
	csio_wr_reg32(hw, BIST_OPCODE_V(1) | START_BIST_F |  BIST_CMD_GAP_V(1),
		      edc_bist_cmd_reg);
	i = csio_hw_रुको_op_करोne_val(hw, edc_bist_cmd_reg, START_BIST_F,
				     0, 10, 1, शून्य);
	अगर (i)
		वापस i;

#घोषणा EDC_DATA(i) (EDC_BIST_STATUS_REG(EDC_BIST_STATUS_RDATA_A, i) + idx)

	क्रम (i = 15; i >= 0; i--)
		*data++ = htonl(csio_rd_reg32(hw, EDC_DATA(i)));
	अगर (ecc)
		*ecc = csio_rd_reg64(hw, EDC_DATA(16));
#अघोषित EDC_DATA
	वापस 0;
पूर्ण

/*
 * csio_t5_memory_rw - पढ़ो/ग_लिखो EDC 0, EDC 1 or MC via PCIE memory winकरोw
 * @hw: the csio_hw
 * @win: PCI-E memory Winकरोw to use
 * @mtype: memory type: MEM_EDC0, MEM_EDC1, MEM_MC0 (or MEM_MC) or MEM_MC1
 * @addr: address within indicated memory type
 * @len: amount of memory to transfer
 * @buf: host memory buffer
 * @dir: direction of transfer 1 => पढ़ो, 0 => ग_लिखो
 *
 * Reads/ग_लिखोs an [almost] arbitrary memory region in the firmware: the
 * firmware memory address, length and host buffer must be aligned on
 * 32-bit boundaries.  The memory is transferred as a raw byte sequence
 * from/to the firmware's memory.  If this memory contains data
 * काष्ठाures which contain multi-byte पूर्णांकegers, it's the callers
 * responsibility to perक्रमm appropriate byte order conversions.
 */
अटल पूर्णांक
csio_t5_memory_rw(काष्ठा csio_hw *hw, u32 win, पूर्णांक mtype, u32 addr,
		u32 len, uपूर्णांक32_t *buf, पूर्णांक dir)
अणु
	u32 pos, start, offset, memoffset;
	u32 edc_size, mc_size, win_pf, mem_reg, mem_aperture, mem_base;

	/*
	 * Argument sanity checks ...
	 */
	अगर ((addr & 0x3) || (len & 0x3))
		वापस -EINVAL;

	/* Offset पूर्णांकo the region of memory which is being accessed
	 * MEM_EDC0 = 0
	 * MEM_EDC1 = 1
	 * MEM_MC   = 2 -- T4
	 * MEM_MC0  = 2 -- For T5
	 * MEM_MC1  = 3 -- For T5
	 */
	edc_size  = EDRAM0_SIZE_G(csio_rd_reg32(hw, MA_EDRAM0_BAR_A));
	अगर (mtype != MEM_MC1)
		memoffset = (mtype * (edc_size * 1024 * 1024));
	अन्यथा अणु
		mc_size = EXT_MEM_SIZE_G(csio_rd_reg32(hw,
						       MA_EXT_MEMORY_BAR_A));
		memoffset = (MEM_MC0 * edc_size + mc_size) * 1024 * 1024;
	पूर्ण

	/* Determine the PCIE_MEM_ACCESS_OFFSET */
	addr = addr + memoffset;

	/*
	 * Each PCI-E Memory Winकरोw is programmed with a winकरोw size -- or
	 * "aperture" -- which controls the granularity of its mapping onto
	 * adapter memory.  We need to grab that aperture in order to know
	 * how to use the specअगरied winकरोw.  The winकरोw is also programmed
	 * with the base address of the Memory Winकरोw in BAR0's address
	 * space.  For T4 this is an असलolute PCI-E Bus Address.  For T5
	 * the address is relative to BAR0.
	 */
	mem_reg = csio_rd_reg32(hw,
			PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, win));
	mem_aperture = 1 << (WINDOW_V(mem_reg) + 10);
	mem_base = PCIखातापूर्णST_G(mem_reg) << 10;

	start = addr & ~(mem_aperture-1);
	offset = addr - start;
	win_pf = PFNUM_V(hw->pfn);

	csio_dbg(hw, "csio_t5_memory_rw: mem_reg: 0x%x, mem_aperture: 0x%x\n",
		 mem_reg, mem_aperture);
	csio_dbg(hw, "csio_t5_memory_rw: mem_base: 0x%x, mem_offset: 0x%x\n",
		 mem_base, memoffset);
	csio_dbg(hw, "csio_t5_memory_rw: start:0x%x, offset:0x%x, win_pf:%d\n",
		 start, offset, win_pf);
	csio_dbg(hw, "csio_t5_memory_rw: mtype: %d, addr: 0x%x, len: %d\n",
		 mtype, addr, len);

	क्रम (pos = start; len > 0; pos += mem_aperture, offset = 0) अणु
		/*
		 * Move PCI-E Memory Winकरोw to our current transfer
		 * position.  Read it back to ensure that changes propagate
		 * beक्रमe we attempt to use the new value.
		 */
		csio_wr_reg32(hw, pos | win_pf,
			PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, win));
		csio_rd_reg32(hw,
			PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, win));

		जबतक (offset < mem_aperture && len > 0) अणु
			अगर (dir)
				*buf++ = csio_rd_reg32(hw, mem_base + offset);
			अन्यथा
				csio_wr_reg32(hw, *buf++, mem_base + offset);

			offset += माप(__be32);
			len -= माप(__be32);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * csio_t5_dfs_create_ext_mem - setup debugfs क्रम MC0 or MC1 to पढ़ो the values
 * @hw: the csio_hw
 *
 * This function creates files in the debugfs with बाह्यal memory region
 * MC0 & MC1.
 */
अटल व्योम
csio_t5_dfs_create_ext_mem(काष्ठा csio_hw *hw)
अणु
	u32 size;
	पूर्णांक i = csio_rd_reg32(hw, MA_TARGET_MEM_ENABLE_A);

	अगर (i & EXT_MEM_ENABLE_F) अणु
		size = csio_rd_reg32(hw, MA_EXT_MEMORY_BAR_A);
		csio_add_debugfs_mem(hw, "mc0", MEM_MC0,
				     EXT_MEM_SIZE_G(size));
	पूर्ण
	अगर (i & EXT_MEM1_ENABLE_F) अणु
		size = csio_rd_reg32(hw, MA_EXT_MEMORY1_BAR_A);
		csio_add_debugfs_mem(hw, "mc1", MEM_MC1,
				     EXT_MEM_SIZE_G(size));
	पूर्ण
पूर्ण

/* T5 adapter specअगरic function */
काष्ठा csio_hw_chip_ops t5_ops = अणु
	.chip_set_mem_win		= csio_t5_set_mem_win,
	.chip_pcie_पूर्णांकr_handler		= csio_t5_pcie_पूर्णांकr_handler,
	.chip_flash_cfg_addr		= csio_t5_flash_cfg_addr,
	.chip_mc_पढ़ो			= csio_t5_mc_पढ़ो,
	.chip_edc_पढ़ो			= csio_t5_edc_पढ़ो,
	.chip_memory_rw			= csio_t5_memory_rw,
	.chip_dfs_create_ext_mem	= csio_t5_dfs_create_ext_mem,
पूर्ण;
