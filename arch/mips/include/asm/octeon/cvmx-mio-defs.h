<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2012 Cavium Networks
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
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

#अगर_अघोषित __CVMX_MIO_DEFS_H__
#घोषणा __CVMX_MIO_DEFS_H__

#घोषणा CVMX_MIO_BOOT_BIST_STAT (CVMX_ADD_IO_SEG(0x00011800000000F8ull))
#घोषणा CVMX_MIO_BOOT_COMP (CVMX_ADD_IO_SEG(0x00011800000000B8ull))
#घोषणा CVMX_MIO_BOOT_DMA_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001180000000100ull) + ((offset) & 3) * 8)
#घोषणा CVMX_MIO_BOOT_DMA_INTX(offset) (CVMX_ADD_IO_SEG(0x0001180000000138ull) + ((offset) & 3) * 8)
#घोषणा CVMX_MIO_BOOT_DMA_INT_ENX(offset) (CVMX_ADD_IO_SEG(0x0001180000000150ull) + ((offset) & 3) * 8)
#घोषणा CVMX_MIO_BOOT_DMA_TIMX(offset) (CVMX_ADD_IO_SEG(0x0001180000000120ull) + ((offset) & 3) * 8)
#घोषणा CVMX_MIO_BOOT_ERR (CVMX_ADD_IO_SEG(0x00011800000000A0ull))
#घोषणा CVMX_MIO_BOOT_INT (CVMX_ADD_IO_SEG(0x00011800000000A8ull))
#घोषणा CVMX_MIO_BOOT_LOC_ADR (CVMX_ADD_IO_SEG(0x0001180000000090ull))
#घोषणा CVMX_MIO_BOOT_LOC_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001180000000080ull) + ((offset) & 1) * 8)
#घोषणा CVMX_MIO_BOOT_LOC_DAT (CVMX_ADD_IO_SEG(0x0001180000000098ull))
#घोषणा CVMX_MIO_BOOT_PIN_DEFS (CVMX_ADD_IO_SEG(0x00011800000000C0ull))
#घोषणा CVMX_MIO_BOOT_REG_CFGX(offset) (CVMX_ADD_IO_SEG(0x0001180000000000ull) + ((offset) & 7) * 8)
#घोषणा CVMX_MIO_BOOT_REG_TIMX(offset) (CVMX_ADD_IO_SEG(0x0001180000000040ull) + ((offset) & 7) * 8)
#घोषणा CVMX_MIO_BOOT_THR (CVMX_ADD_IO_SEG(0x00011800000000B0ull))
#घोषणा CVMX_MIO_EMM_BUF_DAT (CVMX_ADD_IO_SEG(0x00011800000020E8ull))
#घोषणा CVMX_MIO_EMM_BUF_IDX (CVMX_ADD_IO_SEG(0x00011800000020E0ull))
#घोषणा CVMX_MIO_EMM_CFG (CVMX_ADD_IO_SEG(0x0001180000002000ull))
#घोषणा CVMX_MIO_EMM_CMD (CVMX_ADD_IO_SEG(0x0001180000002058ull))
#घोषणा CVMX_MIO_EMM_DMA (CVMX_ADD_IO_SEG(0x0001180000002050ull))
#घोषणा CVMX_MIO_EMM_INT (CVMX_ADD_IO_SEG(0x0001180000002078ull))
#घोषणा CVMX_MIO_EMM_INT_EN (CVMX_ADD_IO_SEG(0x0001180000002080ull))
#घोषणा CVMX_MIO_EMM_MODEX(offset) (CVMX_ADD_IO_SEG(0x0001180000002008ull) + ((offset) & 3) * 8)
#घोषणा CVMX_MIO_EMM_RCA (CVMX_ADD_IO_SEG(0x00011800000020A0ull))
#घोषणा CVMX_MIO_EMM_RSP_HI (CVMX_ADD_IO_SEG(0x0001180000002070ull))
#घोषणा CVMX_MIO_EMM_RSP_LO (CVMX_ADD_IO_SEG(0x0001180000002068ull))
#घोषणा CVMX_MIO_EMM_RSP_STS (CVMX_ADD_IO_SEG(0x0001180000002060ull))
#घोषणा CVMX_MIO_EMM_SAMPLE (CVMX_ADD_IO_SEG(0x0001180000002090ull))
#घोषणा CVMX_MIO_EMM_STS_MASK (CVMX_ADD_IO_SEG(0x0001180000002098ull))
#घोषणा CVMX_MIO_EMM_SWITCH (CVMX_ADD_IO_SEG(0x0001180000002048ull))
#घोषणा CVMX_MIO_EMM_WDOG (CVMX_ADD_IO_SEG(0x0001180000002088ull))
#घोषणा CVMX_MIO_FUS_BNK_DATX(offset) (CVMX_ADD_IO_SEG(0x0001180000001520ull) + ((offset) & 3) * 8)
#घोषणा CVMX_MIO_FUS_DAT0 (CVMX_ADD_IO_SEG(0x0001180000001400ull))
#घोषणा CVMX_MIO_FUS_DAT1 (CVMX_ADD_IO_SEG(0x0001180000001408ull))
#घोषणा CVMX_MIO_FUS_DAT2 (CVMX_ADD_IO_SEG(0x0001180000001410ull))
#घोषणा CVMX_MIO_FUS_DAT3 (CVMX_ADD_IO_SEG(0x0001180000001418ull))
#घोषणा CVMX_MIO_FUS_EMA (CVMX_ADD_IO_SEG(0x0001180000001550ull))
#घोषणा CVMX_MIO_FUS_PDF (CVMX_ADD_IO_SEG(0x0001180000001420ull))
#घोषणा CVMX_MIO_FUS_PLL (CVMX_ADD_IO_SEG(0x0001180000001580ull))
#घोषणा CVMX_MIO_FUS_PROG (CVMX_ADD_IO_SEG(0x0001180000001510ull))
#घोषणा CVMX_MIO_FUS_PROG_TIMES (CVMX_ADD_IO_SEG(0x0001180000001518ull))
#घोषणा CVMX_MIO_FUS_RCMD (CVMX_ADD_IO_SEG(0x0001180000001500ull))
#घोषणा CVMX_MIO_FUS_READ_TIMES (CVMX_ADD_IO_SEG(0x0001180000001570ull))
#घोषणा CVMX_MIO_FUS_REPAIR_RES0 (CVMX_ADD_IO_SEG(0x0001180000001558ull))
#घोषणा CVMX_MIO_FUS_REPAIR_RES1 (CVMX_ADD_IO_SEG(0x0001180000001560ull))
#घोषणा CVMX_MIO_FUS_REPAIR_RES2 (CVMX_ADD_IO_SEG(0x0001180000001568ull))
#घोषणा CVMX_MIO_FUS_SPR_REPAIR_RES (CVMX_ADD_IO_SEG(0x0001180000001548ull))
#घोषणा CVMX_MIO_FUS_SPR_REPAIR_SUM (CVMX_ADD_IO_SEG(0x0001180000001540ull))
#घोषणा CVMX_MIO_FUS_TGG (CVMX_ADD_IO_SEG(0x0001180000001428ull))
#घोषणा CVMX_MIO_FUS_UNLOCK (CVMX_ADD_IO_SEG(0x0001180000001578ull))
#घोषणा CVMX_MIO_FUS_WADR (CVMX_ADD_IO_SEG(0x0001180000001508ull))
#घोषणा CVMX_MIO_GPIO_COMP (CVMX_ADD_IO_SEG(0x00011800000000C8ull))
#घोषणा CVMX_MIO_NDF_DMA_CFG (CVMX_ADD_IO_SEG(0x0001180000000168ull))
#घोषणा CVMX_MIO_NDF_DMA_INT (CVMX_ADD_IO_SEG(0x0001180000000170ull))
#घोषणा CVMX_MIO_NDF_DMA_INT_EN (CVMX_ADD_IO_SEG(0x0001180000000178ull))
#घोषणा CVMX_MIO_PLL_CTL (CVMX_ADD_IO_SEG(0x0001180000001448ull))
#घोषणा CVMX_MIO_PLL_SETTING (CVMX_ADD_IO_SEG(0x0001180000001440ull))
#घोषणा CVMX_MIO_PTP_CKOUT_HI_INCR (CVMX_ADD_IO_SEG(0x0001070000000F40ull))
#घोषणा CVMX_MIO_PTP_CKOUT_LO_INCR (CVMX_ADD_IO_SEG(0x0001070000000F48ull))
#घोषणा CVMX_MIO_PTP_CKOUT_THRESH_HI (CVMX_ADD_IO_SEG(0x0001070000000F38ull))
#घोषणा CVMX_MIO_PTP_CKOUT_THRESH_LO (CVMX_ADD_IO_SEG(0x0001070000000F30ull))
#घोषणा CVMX_MIO_PTP_CLOCK_CFG (CVMX_ADD_IO_SEG(0x0001070000000F00ull))
#घोषणा CVMX_MIO_PTP_CLOCK_COMP (CVMX_ADD_IO_SEG(0x0001070000000F18ull))
#घोषणा CVMX_MIO_PTP_CLOCK_HI (CVMX_ADD_IO_SEG(0x0001070000000F10ull))
#घोषणा CVMX_MIO_PTP_CLOCK_LO (CVMX_ADD_IO_SEG(0x0001070000000F08ull))
#घोषणा CVMX_MIO_PTP_EVT_CNT (CVMX_ADD_IO_SEG(0x0001070000000F28ull))
#घोषणा CVMX_MIO_PTP_PHY_1PPS_IN (CVMX_ADD_IO_SEG(0x0001070000000F70ull))
#घोषणा CVMX_MIO_PTP_PPS_HI_INCR (CVMX_ADD_IO_SEG(0x0001070000000F60ull))
#घोषणा CVMX_MIO_PTP_PPS_LO_INCR (CVMX_ADD_IO_SEG(0x0001070000000F68ull))
#घोषणा CVMX_MIO_PTP_PPS_THRESH_HI (CVMX_ADD_IO_SEG(0x0001070000000F58ull))
#घोषणा CVMX_MIO_PTP_PPS_THRESH_LO (CVMX_ADD_IO_SEG(0x0001070000000F50ull))
#घोषणा CVMX_MIO_PTP_TIMESTAMP (CVMX_ADD_IO_SEG(0x0001070000000F20ull))
#घोषणा CVMX_MIO_QLMX_CFG(offset) (CVMX_ADD_IO_SEG(0x0001180000001590ull) + ((offset) & 7) * 8)
#घोषणा CVMX_MIO_RST_BOOT (CVMX_ADD_IO_SEG(0x0001180000001600ull))
#घोषणा CVMX_MIO_RST_CFG (CVMX_ADD_IO_SEG(0x0001180000001610ull))
#घोषणा CVMX_MIO_RST_CKILL (CVMX_ADD_IO_SEG(0x0001180000001638ull))
#घोषणा CVMX_MIO_RST_CNTLX(offset) (CVMX_ADD_IO_SEG(0x0001180000001648ull) + ((offset) & 3) * 8)
#घोषणा CVMX_MIO_RST_CTLX(offset) (CVMX_ADD_IO_SEG(0x0001180000001618ull) + ((offset) & 1) * 8)
#घोषणा CVMX_MIO_RST_DELAY (CVMX_ADD_IO_SEG(0x0001180000001608ull))
#घोषणा CVMX_MIO_RST_INT (CVMX_ADD_IO_SEG(0x0001180000001628ull))
#घोषणा CVMX_MIO_RST_INT_EN (CVMX_ADD_IO_SEG(0x0001180000001630ull))
#घोषणा CVMX_MIO_TWSX_INT(offset) (CVMX_ADD_IO_SEG(0x0001180000001010ull) + ((offset) & 1) * 512)
#घोषणा CVMX_MIO_TWSX_SW_TWSI(offset) (CVMX_ADD_IO_SEG(0x0001180000001000ull) + ((offset) & 1) * 512)
#घोषणा CVMX_MIO_TWSX_SW_TWSI_EXT(offset) (CVMX_ADD_IO_SEG(0x0001180000001018ull) + ((offset) & 1) * 512)
#घोषणा CVMX_MIO_TWSX_TWSI_SW(offset) (CVMX_ADD_IO_SEG(0x0001180000001008ull) + ((offset) & 1) * 512)
#घोषणा CVMX_MIO_UART2_DLH (CVMX_ADD_IO_SEG(0x0001180000000488ull))
#घोषणा CVMX_MIO_UART2_DLL (CVMX_ADD_IO_SEG(0x0001180000000480ull))
#घोषणा CVMX_MIO_UART2_FAR (CVMX_ADD_IO_SEG(0x0001180000000520ull))
#घोषणा CVMX_MIO_UART2_FCR (CVMX_ADD_IO_SEG(0x0001180000000450ull))
#घोषणा CVMX_MIO_UART2_HTX (CVMX_ADD_IO_SEG(0x0001180000000708ull))
#घोषणा CVMX_MIO_UART2_IER (CVMX_ADD_IO_SEG(0x0001180000000408ull))
#घोषणा CVMX_MIO_UART2_IIR (CVMX_ADD_IO_SEG(0x0001180000000410ull))
#घोषणा CVMX_MIO_UART2_LCR (CVMX_ADD_IO_SEG(0x0001180000000418ull))
#घोषणा CVMX_MIO_UART2_LSR (CVMX_ADD_IO_SEG(0x0001180000000428ull))
#घोषणा CVMX_MIO_UART2_MCR (CVMX_ADD_IO_SEG(0x0001180000000420ull))
#घोषणा CVMX_MIO_UART2_MSR (CVMX_ADD_IO_SEG(0x0001180000000430ull))
#घोषणा CVMX_MIO_UART2_RBR (CVMX_ADD_IO_SEG(0x0001180000000400ull))
#घोषणा CVMX_MIO_UART2_RFL (CVMX_ADD_IO_SEG(0x0001180000000608ull))
#घोषणा CVMX_MIO_UART2_RFW (CVMX_ADD_IO_SEG(0x0001180000000530ull))
#घोषणा CVMX_MIO_UART2_SBCR (CVMX_ADD_IO_SEG(0x0001180000000620ull))
#घोषणा CVMX_MIO_UART2_SCR (CVMX_ADD_IO_SEG(0x0001180000000438ull))
#घोषणा CVMX_MIO_UART2_SFE (CVMX_ADD_IO_SEG(0x0001180000000630ull))
#घोषणा CVMX_MIO_UART2_SRR (CVMX_ADD_IO_SEG(0x0001180000000610ull))
#घोषणा CVMX_MIO_UART2_SRT (CVMX_ADD_IO_SEG(0x0001180000000638ull))
#घोषणा CVMX_MIO_UART2_SRTS (CVMX_ADD_IO_SEG(0x0001180000000618ull))
#घोषणा CVMX_MIO_UART2_STT (CVMX_ADD_IO_SEG(0x0001180000000700ull))
#घोषणा CVMX_MIO_UART2_TFL (CVMX_ADD_IO_SEG(0x0001180000000600ull))
#घोषणा CVMX_MIO_UART2_TFR (CVMX_ADD_IO_SEG(0x0001180000000528ull))
#घोषणा CVMX_MIO_UART2_THR (CVMX_ADD_IO_SEG(0x0001180000000440ull))
#घोषणा CVMX_MIO_UART2_USR (CVMX_ADD_IO_SEG(0x0001180000000538ull))
#घोषणा CVMX_MIO_UARTX_DLH(offset) (CVMX_ADD_IO_SEG(0x0001180000000888ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_DLL(offset) (CVMX_ADD_IO_SEG(0x0001180000000880ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_FAR(offset) (CVMX_ADD_IO_SEG(0x0001180000000920ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_FCR(offset) (CVMX_ADD_IO_SEG(0x0001180000000850ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_HTX(offset) (CVMX_ADD_IO_SEG(0x0001180000000B08ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_IER(offset) (CVMX_ADD_IO_SEG(0x0001180000000808ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_IIR(offset) (CVMX_ADD_IO_SEG(0x0001180000000810ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_LCR(offset) (CVMX_ADD_IO_SEG(0x0001180000000818ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_LSR(offset) (CVMX_ADD_IO_SEG(0x0001180000000828ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_MCR(offset) (CVMX_ADD_IO_SEG(0x0001180000000820ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_MSR(offset) (CVMX_ADD_IO_SEG(0x0001180000000830ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_RBR(offset) (CVMX_ADD_IO_SEG(0x0001180000000800ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_RFL(offset) (CVMX_ADD_IO_SEG(0x0001180000000A08ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_RFW(offset) (CVMX_ADD_IO_SEG(0x0001180000000930ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_SBCR(offset) (CVMX_ADD_IO_SEG(0x0001180000000A20ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_SCR(offset) (CVMX_ADD_IO_SEG(0x0001180000000838ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_SFE(offset) (CVMX_ADD_IO_SEG(0x0001180000000A30ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_SRR(offset) (CVMX_ADD_IO_SEG(0x0001180000000A10ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_SRT(offset) (CVMX_ADD_IO_SEG(0x0001180000000A38ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_SRTS(offset) (CVMX_ADD_IO_SEG(0x0001180000000A18ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_STT(offset) (CVMX_ADD_IO_SEG(0x0001180000000B00ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_TFL(offset) (CVMX_ADD_IO_SEG(0x0001180000000A00ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_TFR(offset) (CVMX_ADD_IO_SEG(0x0001180000000928ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_THR(offset) (CVMX_ADD_IO_SEG(0x0001180000000840ull) + ((offset) & 1) * 1024)
#घोषणा CVMX_MIO_UARTX_USR(offset) (CVMX_ADD_IO_SEG(0x0001180000000938ull) + ((offset) & 1) * 1024)

जोड़ cvmx_mio_boot_bist_stat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_bist_stat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_boot_bist_stat_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t ncbo_1:1;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t ncbi:1;
#अन्यथा
		uपूर्णांक64_t ncbi:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t ncbo_1:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_mio_boot_bist_stat_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t ncbi:1;
#अन्यथा
		uपूर्णांक64_t ncbi:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_mio_boot_bist_stat_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t pcm_1:1;
		uपूर्णांक64_t pcm_0:1;
		uपूर्णांक64_t ncbo_1:1;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t ncbi:1;
#अन्यथा
		uपूर्णांक64_t ncbi:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t ncbo_1:1;
		uपूर्णांक64_t pcm_0:1;
		uपूर्णांक64_t pcm_1:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_mio_boot_bist_stat_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t ndf:2;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t dma:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t ncbi:1;
#अन्यथा
		uपूर्णांक64_t ncbi:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t dma:1;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t ndf:2;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_mio_boot_bist_stat_cn52xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t dma:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t ncbi:1;
#अन्यथा
		uपूर्णांक64_t ncbi:1;
		uपूर्णांक64_t loc:1;
		uपूर्णांक64_t dma:1;
		uपूर्णांक64_t ncbo_0:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn52xxp1;
	काष्ठा cvmx_mio_boot_bist_stat_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t stat:12;
#अन्यथा
		uपूर्णांक64_t stat:12;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_mio_boot_bist_stat_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t stat:9;
#अन्यथा
		uपूर्णांक64_t stat:9;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_mio_boot_bist_stat_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t stat:10;
#अन्यथा
		uपूर्णांक64_t stat:10;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn66xx;
पूर्ण;

जोड़ cvmx_mio_boot_comp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_comp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_boot_comp_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t nctl:5;
#अन्यथा
		uपूर्णांक64_t nctl:5;
		uपूर्णांक64_t pctl:5;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_mio_boot_comp_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t pctl:6;
		uपूर्णांक64_t nctl:6;
#अन्यथा
		uपूर्णांक64_t nctl:6;
		uपूर्णांक64_t pctl:6;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_mio_boot_dma_cfgx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_dma_cfgx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t rw:1;
		uपूर्णांक64_t clr:1;
		uपूर्णांक64_t reserved_60_60:1;
		uपूर्णांक64_t swap32:1;
		uपूर्णांक64_t swap16:1;
		uपूर्णांक64_t swap8:1;
		uपूर्णांक64_t endian:1;
		uपूर्णांक64_t size:20;
		uपूर्णांक64_t adr:36;
#अन्यथा
		uपूर्णांक64_t adr:36;
		uपूर्णांक64_t size:20;
		uपूर्णांक64_t endian:1;
		uपूर्णांक64_t swap8:1;
		uपूर्णांक64_t swap16:1;
		uपूर्णांक64_t swap32:1;
		uपूर्णांक64_t reserved_60_60:1;
		uपूर्णांक64_t clr:1;
		uपूर्णांक64_t rw:1;
		uपूर्णांक64_t en:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_boot_dma_पूर्णांकx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_dma_पूर्णांकx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t dmarq:1;
		uपूर्णांक64_t करोne:1;
#अन्यथा
		uपूर्णांक64_t करोne:1;
		uपूर्णांक64_t dmarq:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_boot_dma_पूर्णांक_enx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_dma_पूर्णांक_enx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t dmarq:1;
		uपूर्णांक64_t करोne:1;
#अन्यथा
		uपूर्णांक64_t करोne:1;
		uपूर्णांक64_t dmarq:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_boot_dma_timx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_dma_timx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dmack_pi:1;
		uपूर्णांक64_t dmarq_pi:1;
		uपूर्णांक64_t tim_mult:2;
		uपूर्णांक64_t rd_dly:3;
		uपूर्णांक64_t ddr:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t reserved_48_54:7;
		uपूर्णांक64_t छोड़ो:6;
		uपूर्णांक64_t dmack_h:6;
		uपूर्णांक64_t we_n:6;
		uपूर्णांक64_t we_a:6;
		uपूर्णांक64_t oe_n:6;
		uपूर्णांक64_t oe_a:6;
		uपूर्णांक64_t dmack_s:6;
		uपूर्णांक64_t dmarq:6;
#अन्यथा
		uपूर्णांक64_t dmarq:6;
		uपूर्णांक64_t dmack_s:6;
		uपूर्णांक64_t oe_a:6;
		uपूर्णांक64_t oe_n:6;
		uपूर्णांक64_t we_a:6;
		uपूर्णांक64_t we_n:6;
		uपूर्णांक64_t dmack_h:6;
		uपूर्णांक64_t छोड़ो:6;
		uपूर्णांक64_t reserved_48_54:7;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t ddr:1;
		uपूर्णांक64_t rd_dly:3;
		uपूर्णांक64_t tim_mult:2;
		uपूर्णांक64_t dmarq_pi:1;
		uपूर्णांक64_t dmack_pi:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_boot_err अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_err_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t रुको_err:1;
		uपूर्णांक64_t adr_err:1;
#अन्यथा
		uपूर्णांक64_t adr_err:1;
		uपूर्णांक64_t रुको_err:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_boot_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t रुको_पूर्णांक:1;
		uपूर्णांक64_t adr_पूर्णांक:1;
#अन्यथा
		uपूर्णांक64_t adr_पूर्णांक:1;
		uपूर्णांक64_t रुको_पूर्णांक:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_boot_loc_adr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_loc_adr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t adr:5;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t adr:5;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_boot_loc_cfgx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_loc_cfgx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_28_30:3;
		uपूर्णांक64_t base:25;
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t base:25;
		uपूर्णांक64_t reserved_28_30:3;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_boot_loc_dat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_loc_dat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_boot_pin_defs अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_pin_defs_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t user1:16;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t dmack_p2:1;
		uपूर्णांक64_t dmack_p1:1;
		uपूर्णांक64_t dmack_p0:1;
		uपूर्णांक64_t term:2;
		uपूर्णांक64_t nand:1;
		uपूर्णांक64_t user0:8;
#अन्यथा
		uपूर्णांक64_t user0:8;
		uपूर्णांक64_t nand:1;
		uपूर्णांक64_t term:2;
		uपूर्णांक64_t dmack_p0:1;
		uपूर्णांक64_t dmack_p1:1;
		uपूर्णांक64_t dmack_p2:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t user1:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_boot_pin_defs_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t reserved_13_13:1;
		uपूर्णांक64_t dmack_p1:1;
		uपूर्णांक64_t dmack_p0:1;
		uपूर्णांक64_t term:2;
		uपूर्णांक64_t nand:1;
		uपूर्णांक64_t reserved_0_7:8;
#अन्यथा
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t nand:1;
		uपूर्णांक64_t term:2;
		uपूर्णांक64_t dmack_p0:1;
		uपूर्णांक64_t dmack_p1:1;
		uपूर्णांक64_t reserved_13_13:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_mio_boot_pin_defs_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t dmack_p2:1;
		uपूर्णांक64_t dmack_p1:1;
		uपूर्णांक64_t dmack_p0:1;
		uपूर्णांक64_t term:2;
		uपूर्णांक64_t reserved_0_8:9;
#अन्यथा
		uपूर्णांक64_t reserved_0_8:9;
		uपूर्णांक64_t term:2;
		uपूर्णांक64_t dmack_p0:1;
		uपूर्णांक64_t dmack_p1:1;
		uपूर्णांक64_t dmack_p2:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण cn56xx;
	काष्ठा cvmx_mio_boot_pin_defs_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t user1:16;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t reserved_13_13:1;
		uपूर्णांक64_t dmack_p1:1;
		uपूर्णांक64_t dmack_p0:1;
		uपूर्णांक64_t term:2;
		uपूर्णांक64_t nand:1;
		uपूर्णांक64_t user0:8;
#अन्यथा
		uपूर्णांक64_t user0:8;
		uपूर्णांक64_t nand:1;
		uपूर्णांक64_t term:2;
		uपूर्णांक64_t dmack_p0:1;
		uपूर्णांक64_t dmack_p1:1;
		uपूर्णांक64_t reserved_13_13:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t user1:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_mio_boot_reg_cfgx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_reg_cfgx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t dmack:2;
		uपूर्णांक64_t tim_mult:2;
		uपूर्णांक64_t rd_dly:3;
		uपूर्णांक64_t sam:1;
		uपूर्णांक64_t we_ext:2;
		uपूर्णांक64_t oe_ext:2;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t orbit:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t size:12;
		uपूर्णांक64_t base:16;
#अन्यथा
		uपूर्णांक64_t base:16;
		uपूर्णांक64_t size:12;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t orbit:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t oe_ext:2;
		uपूर्णांक64_t we_ext:2;
		uपूर्णांक64_t sam:1;
		uपूर्णांक64_t rd_dly:3;
		uपूर्णांक64_t tim_mult:2;
		uपूर्णांक64_t dmack:2;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_boot_reg_cfgx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t sam:1;
		uपूर्णांक64_t we_ext:2;
		uपूर्णांक64_t oe_ext:2;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t orbit:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t size:12;
		uपूर्णांक64_t base:16;
#अन्यथा
		uपूर्णांक64_t base:16;
		uपूर्णांक64_t size:12;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t orbit:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t oe_ext:2;
		uपूर्णांक64_t we_ext:2;
		uपूर्णांक64_t sam:1;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_mio_boot_reg_cfgx_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t orbit:1;
		uपूर्णांक64_t reserved_28_29:2;
		uपूर्णांक64_t size:12;
		uपूर्णांक64_t base:16;
#अन्यथा
		uपूर्णांक64_t base:16;
		uपूर्णांक64_t size:12;
		uपूर्णांक64_t reserved_28_29:2;
		uपूर्णांक64_t orbit:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_mio_boot_reg_cfgx_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_42_63:22;
		uपूर्णांक64_t tim_mult:2;
		uपूर्णांक64_t rd_dly:3;
		uपूर्णांक64_t sam:1;
		uपूर्णांक64_t we_ext:2;
		uपूर्णांक64_t oe_ext:2;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t orbit:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t size:12;
		uपूर्णांक64_t base:16;
#अन्यथा
		uपूर्णांक64_t base:16;
		uपूर्णांक64_t size:12;
		uपूर्णांक64_t width:1;
		uपूर्णांक64_t ale:1;
		uपूर्णांक64_t orbit:1;
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t oe_ext:2;
		uपूर्णांक64_t we_ext:2;
		uपूर्णांक64_t sam:1;
		uपूर्णांक64_t rd_dly:3;
		uपूर्णांक64_t tim_mult:2;
		uपूर्णांक64_t reserved_42_63:22;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_mio_boot_reg_timx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_reg_timx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pagem:1;
		uपूर्णांक64_t रुकोm:1;
		uपूर्णांक64_t pages:2;
		uपूर्णांक64_t ale:6;
		uपूर्णांक64_t page:6;
		uपूर्णांक64_t रुको:6;
		uपूर्णांक64_t छोड़ो:6;
		uपूर्णांक64_t wr_hld:6;
		uपूर्णांक64_t rd_hld:6;
		uपूर्णांक64_t we:6;
		uपूर्णांक64_t oe:6;
		uपूर्णांक64_t ce:6;
		uपूर्णांक64_t adr:6;
#अन्यथा
		uपूर्णांक64_t adr:6;
		uपूर्णांक64_t ce:6;
		uपूर्णांक64_t oe:6;
		uपूर्णांक64_t we:6;
		uपूर्णांक64_t rd_hld:6;
		uपूर्णांक64_t wr_hld:6;
		uपूर्णांक64_t छोड़ो:6;
		uपूर्णांक64_t रुको:6;
		uपूर्णांक64_t page:6;
		uपूर्णांक64_t ale:6;
		uपूर्णांक64_t pages:2;
		uपूर्णांक64_t रुकोm:1;
		uपूर्णांक64_t pagem:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_boot_reg_timx_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pagem:1;
		uपूर्णांक64_t रुकोm:1;
		uपूर्णांक64_t pages:2;
		uपूर्णांक64_t reserved_54_59:6;
		uपूर्णांक64_t page:6;
		uपूर्णांक64_t रुको:6;
		uपूर्णांक64_t छोड़ो:6;
		uपूर्णांक64_t wr_hld:6;
		uपूर्णांक64_t rd_hld:6;
		uपूर्णांक64_t we:6;
		uपूर्णांक64_t oe:6;
		uपूर्णांक64_t ce:6;
		uपूर्णांक64_t adr:6;
#अन्यथा
		uपूर्णांक64_t adr:6;
		uपूर्णांक64_t ce:6;
		uपूर्णांक64_t oe:6;
		uपूर्णांक64_t we:6;
		uपूर्णांक64_t rd_hld:6;
		uपूर्णांक64_t wr_hld:6;
		uपूर्णांक64_t छोड़ो:6;
		uपूर्णांक64_t रुको:6;
		uपूर्णांक64_t page:6;
		uपूर्णांक64_t reserved_54_59:6;
		uपूर्णांक64_t pages:2;
		uपूर्णांक64_t रुकोm:1;
		uपूर्णांक64_t pagem:1;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

जोड़ cvmx_mio_boot_thr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_boot_thr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t dma_thr:6;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t fअगर_cnt:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t fअगर_thr:6;
#अन्यथा
		uपूर्णांक64_t fअगर_thr:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t fअगर_cnt:6;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t dma_thr:6;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_boot_thr_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t fअगर_cnt:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t fअगर_thr:6;
#अन्यथा
		uपूर्णांक64_t fअगर_thr:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t fअगर_cnt:6;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_mio_emm_buf_dat अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_buf_dat_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dat:64;
#अन्यथा
		uपूर्णांक64_t dat:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_buf_idx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_buf_idx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t inc:1;
		uपूर्णांक64_t reserved_7_15:9;
		uपूर्णांक64_t buf_num:1;
		uपूर्णांक64_t offset:6;
#अन्यथा
		uपूर्णांक64_t offset:6;
		uपूर्णांक64_t buf_num:1;
		uपूर्णांक64_t reserved_7_15:9;
		uपूर्णांक64_t inc:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t boot_fail:1;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t bus_ena:4;
#अन्यथा
		uपूर्णांक64_t bus_ena:4;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t boot_fail:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_cmd अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_cmd_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t bus_id:2;
		uपूर्णांक64_t cmd_val:1;
		uपूर्णांक64_t reserved_56_58:3;
		uपूर्णांक64_t dbuf:1;
		uपूर्णांक64_t offset:6;
		uपूर्णांक64_t reserved_43_48:6;
		uपूर्णांक64_t ctype_xor:2;
		uपूर्णांक64_t rtype_xor:3;
		uपूर्णांक64_t cmd_idx:6;
		uपूर्णांक64_t arg:32;
#अन्यथा
		uपूर्णांक64_t arg:32;
		uपूर्णांक64_t cmd_idx:6;
		uपूर्णांक64_t rtype_xor:3;
		uपूर्णांक64_t ctype_xor:2;
		uपूर्णांक64_t reserved_43_48:6;
		uपूर्णांक64_t offset:6;
		uपूर्णांक64_t dbuf:1;
		uपूर्णांक64_t reserved_56_58:3;
		uपूर्णांक64_t cmd_val:1;
		uपूर्णांक64_t bus_id:2;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_dma अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_dma_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t bus_id:2;
		uपूर्णांक64_t dma_val:1;
		uपूर्णांक64_t sector:1;
		uपूर्णांक64_t dat_null:1;
		uपूर्णांक64_t thres:6;
		uपूर्णांक64_t rel_wr:1;
		uपूर्णांक64_t rw:1;
		uपूर्णांक64_t multi:1;
		uपूर्णांक64_t block_cnt:16;
		uपूर्णांक64_t card_addr:32;
#अन्यथा
		uपूर्णांक64_t card_addr:32;
		uपूर्णांक64_t block_cnt:16;
		uपूर्णांक64_t multi:1;
		uपूर्णांक64_t rw:1;
		uपूर्णांक64_t rel_wr:1;
		uपूर्णांक64_t thres:6;
		uपूर्णांक64_t dat_null:1;
		uपूर्णांक64_t sector:1;
		uपूर्णांक64_t dma_val:1;
		uपूर्णांक64_t bus_id:2;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t चयन_err:1;
		uपूर्णांक64_t चयन_करोne:1;
		uपूर्णांक64_t dma_err:1;
		uपूर्णांक64_t cmd_err:1;
		uपूर्णांक64_t dma_करोne:1;
		uपूर्णांक64_t cmd_करोne:1;
		uपूर्णांक64_t buf_करोne:1;
#अन्यथा
		uपूर्णांक64_t buf_करोne:1;
		uपूर्णांक64_t cmd_करोne:1;
		uपूर्णांक64_t dma_करोne:1;
		uपूर्णांक64_t cmd_err:1;
		uपूर्णांक64_t dma_err:1;
		uपूर्णांक64_t चयन_करोne:1;
		uपूर्णांक64_t चयन_err:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t चयन_err:1;
		uपूर्णांक64_t चयन_करोne:1;
		uपूर्णांक64_t dma_err:1;
		uपूर्णांक64_t cmd_err:1;
		uपूर्णांक64_t dma_करोne:1;
		uपूर्णांक64_t cmd_करोne:1;
		uपूर्णांक64_t buf_करोne:1;
#अन्यथा
		uपूर्णांक64_t buf_करोne:1;
		uपूर्णांक64_t cmd_करोne:1;
		uपूर्णांक64_t dma_करोne:1;
		uपूर्णांक64_t cmd_err:1;
		uपूर्णांक64_t dma_err:1;
		uपूर्णांक64_t चयन_करोne:1;
		uपूर्णांक64_t चयन_err:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_modex अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_modex_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t hs_timing:1;
		uपूर्णांक64_t reserved_43_47:5;
		uपूर्णांक64_t bus_width:3;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t घातer_class:4;
		uपूर्णांक64_t clk_hi:16;
		uपूर्णांक64_t clk_lo:16;
#अन्यथा
		uपूर्णांक64_t clk_lo:16;
		uपूर्णांक64_t clk_hi:16;
		uपूर्णांक64_t घातer_class:4;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t bus_width:3;
		uपूर्णांक64_t reserved_43_47:5;
		uपूर्णांक64_t hs_timing:1;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_rca अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_rca_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t card_rca:16;
#अन्यथा
		uपूर्णांक64_t card_rca:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_rsp_hi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_rsp_hi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dat:64;
#अन्यथा
		uपूर्णांक64_t dat:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_rsp_lo अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_rsp_lo_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dat:64;
#अन्यथा
		uपूर्णांक64_t dat:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_rsp_sts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_rsp_sts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t bus_id:2;
		uपूर्णांक64_t cmd_val:1;
		uपूर्णांक64_t चयन_val:1;
		uपूर्णांक64_t dma_val:1;
		uपूर्णांक64_t dma_pend:1;
		uपूर्णांक64_t reserved_29_55:27;
		uपूर्णांक64_t dbuf_err:1;
		uपूर्णांक64_t reserved_24_27:4;
		uपूर्णांक64_t dbuf:1;
		uपूर्णांक64_t blk_समयout:1;
		uपूर्णांक64_t blk_crc_err:1;
		uपूर्णांक64_t rsp_busybit:1;
		uपूर्णांक64_t stp_समयout:1;
		uपूर्णांक64_t stp_crc_err:1;
		uपूर्णांक64_t stp_bad_sts:1;
		uपूर्णांक64_t stp_val:1;
		uपूर्णांक64_t rsp_समयout:1;
		uपूर्णांक64_t rsp_crc_err:1;
		uपूर्णांक64_t rsp_bad_sts:1;
		uपूर्णांक64_t rsp_val:1;
		uपूर्णांक64_t rsp_type:3;
		uपूर्णांक64_t cmd_type:2;
		uपूर्णांक64_t cmd_idx:6;
		uपूर्णांक64_t cmd_करोne:1;
#अन्यथा
		uपूर्णांक64_t cmd_करोne:1;
		uपूर्णांक64_t cmd_idx:6;
		uपूर्णांक64_t cmd_type:2;
		uपूर्णांक64_t rsp_type:3;
		uपूर्णांक64_t rsp_val:1;
		uपूर्णांक64_t rsp_bad_sts:1;
		uपूर्णांक64_t rsp_crc_err:1;
		uपूर्णांक64_t rsp_समयout:1;
		uपूर्णांक64_t stp_val:1;
		uपूर्णांक64_t stp_bad_sts:1;
		uपूर्णांक64_t stp_crc_err:1;
		uपूर्णांक64_t stp_समयout:1;
		uपूर्णांक64_t rsp_busybit:1;
		uपूर्णांक64_t blk_crc_err:1;
		uपूर्णांक64_t blk_समयout:1;
		uपूर्णांक64_t dbuf:1;
		uपूर्णांक64_t reserved_24_27:4;
		uपूर्णांक64_t dbuf_err:1;
		uपूर्णांक64_t reserved_29_55:27;
		uपूर्णांक64_t dma_pend:1;
		uपूर्णांक64_t dma_val:1;
		uपूर्णांक64_t चयन_val:1;
		uपूर्णांक64_t cmd_val:1;
		uपूर्णांक64_t bus_id:2;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_sample अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_sample_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_26_63:38;
		uपूर्णांक64_t cmd_cnt:10;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t dat_cnt:10;
#अन्यथा
		uपूर्णांक64_t dat_cnt:10;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t cmd_cnt:10;
		uपूर्णांक64_t reserved_26_63:38;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_sts_mask अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_sts_mask_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t sts_msk:32;
#अन्यथा
		uपूर्णांक64_t sts_msk:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_चयन अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_चयन_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t bus_id:2;
		uपूर्णांक64_t चयन_exe:1;
		uपूर्णांक64_t चयन_err0:1;
		uपूर्णांक64_t चयन_err1:1;
		uपूर्णांक64_t चयन_err2:1;
		uपूर्णांक64_t reserved_49_55:7;
		uपूर्णांक64_t hs_timing:1;
		uपूर्णांक64_t reserved_43_47:5;
		uपूर्णांक64_t bus_width:3;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t घातer_class:4;
		uपूर्णांक64_t clk_hi:16;
		uपूर्णांक64_t clk_lo:16;
#अन्यथा
		uपूर्णांक64_t clk_lo:16;
		uपूर्णांक64_t clk_hi:16;
		uपूर्णांक64_t घातer_class:4;
		uपूर्णांक64_t reserved_36_39:4;
		uपूर्णांक64_t bus_width:3;
		uपूर्णांक64_t reserved_43_47:5;
		uपूर्णांक64_t hs_timing:1;
		uपूर्णांक64_t reserved_49_55:7;
		uपूर्णांक64_t चयन_err2:1;
		uपूर्णांक64_t चयन_err1:1;
		uपूर्णांक64_t चयन_err0:1;
		uपूर्णांक64_t चयन_exe:1;
		uपूर्णांक64_t bus_id:2;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_emm_wकरोg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_emm_wकरोg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_26_63:38;
		uपूर्णांक64_t clk_cnt:26;
#अन्यथा
		uपूर्णांक64_t clk_cnt:26;
		uपूर्णांक64_t reserved_26_63:38;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_bnk_datx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_bnk_datx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dat:64;
#अन्यथा
		uपूर्णांक64_t dat:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_dat0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_dat0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t man_info:32;
#अन्यथा
		uपूर्णांक64_t man_info:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_dat1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_dat1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t man_info:32;
#अन्यथा
		uपूर्णांक64_t man_info:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_dat2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_dat2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t run_platक्रमm:3;
		uपूर्णांक64_t gbl_pwr_throttle:8;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_0_15:16;
#अन्यथा
		uपूर्णांक64_t reserved_0_15:16;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t gbl_pwr_throttle:8;
		uपूर्णांक64_t run_platक्रमm:3;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_fus_dat2_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t pll_off:4;
		uपूर्णांक64_t reserved_1_11:11;
		uपूर्णांक64_t pp_dis:1;
#अन्यथा
		uपूर्णांक64_t pp_dis:1;
		uपूर्णांक64_t reserved_1_11:11;
		uपूर्णांक64_t pll_off:4;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_mio_fus_dat2_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t pll_off:4;
		uपूर्णांक64_t reserved_2_11:10;
		uपूर्णांक64_t pp_dis:2;
#अन्यथा
		uपूर्णांक64_t pp_dis:2;
		uपूर्णांक64_t reserved_2_11:10;
		uपूर्णांक64_t pll_off:4;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_mio_fus_dat2_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t pp_dis:16;
#अन्यथा
		uपूर्णांक64_t pp_dis:16;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_mio_fus_dat2_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_2_15:14;
		uपूर्णांक64_t pp_dis:2;
#अन्यथा
		uपूर्णांक64_t pp_dis:2;
		uपूर्णांक64_t reserved_2_15:14;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_mio_fus_dat2_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t pp_dis:4;
#अन्यथा
		uपूर्णांक64_t pp_dis:4;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_mio_fus_dat2_cn56xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_34_63:30;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t pp_dis:12;
#अन्यथा
		uपूर्णांक64_t pp_dis:12;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t reserved_34_63:30;
#पूर्ण_अगर
	पूर्ण cn56xx;
	काष्ठा cvmx_mio_fus_dat2_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_30_63:34;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t pp_dis:16;
#अन्यथा
		uपूर्णांक64_t pp_dis:16;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t bist_dis:1;
		uपूर्णांक64_t rst_sht:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nokasu:1;
		uपूर्णांक64_t reserved_30_63:34;
#पूर्ण_अगर
	पूर्ण cn58xx;
	काष्ठा cvmx_mio_fus_dat2_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t pp_dis:4;
#अन्यथा
		uपूर्णांक64_t pp_dis:4;
		uपूर्णांक64_t reserved_4_15:12;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_mio_fus_dat2_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_35_63:29;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_6_15:10;
		uपूर्णांक64_t pp_dis:6;
#अन्यथा
		uपूर्णांक64_t pp_dis:6;
		uपूर्णांक64_t reserved_6_15:10;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t reserved_35_63:29;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_mio_fus_dat2_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t pp_dis:10;
#अन्यथा
		uपूर्णांक64_t pp_dis:10;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण cn66xx;
	काष्ठा cvmx_mio_fus_dat2_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_0_15:16;
#अन्यथा
		uपूर्णांक64_t reserved_0_15:16;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_24_25:2;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_29_31:3;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण cn68xx;
	काष्ठा cvmx_mio_fus_dat2_cn70xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_31_29:3;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t reserved_25_24:2;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_15_0:16;
#अन्यथा
		uपूर्णांक64_t reserved_15_0:16;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_25_24:2;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_31_29:3;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण cn70xx;
	काष्ठा cvmx_mio_fus_dat2_cn73xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t run_platक्रमm:3;
		uपूर्णांक64_t gbl_pwr_throttle:8;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_31_29:3;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t reserved_25_24:2;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_15_0:16;
#अन्यथा
		uपूर्णांक64_t reserved_15_0:16;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_25_24:2;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_31_29:3;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t gbl_pwr_throttle:8;
		uपूर्णांक64_t run_platक्रमm:3;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण cn73xx;
	काष्ठा cvmx_mio_fus_dat2_cn78xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t run_platक्रमm:3;
		uपूर्णांक64_t reserved_48_55:8;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_31_29:3;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t reserved_25_24:2;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_0_15:16;
#अन्यथा
		uपूर्णांक64_t reserved_0_15:16;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_25_24:2;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_31_29:3;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t reserved_48_55:8;
		uपूर्णांक64_t run_platक्रमm:3;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण cn78xx;
	काष्ठा cvmx_mio_fus_dat2_cn78xxp2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t run_platक्रमm:3;
		uपूर्णांक64_t gbl_pwr_throttle:8;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t reserved_31_29:3;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t reserved_25_24:2;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_0_15:16;
#अन्यथा
		uपूर्णांक64_t reserved_0_15:16;
		uपूर्णांक64_t chip_id:8;
		uपूर्णांक64_t reserved_25_24:2;
		uपूर्णांक64_t nocrypto:1;
		uपूर्णांक64_t nomul:1;
		uपूर्णांक64_t nodfa_cp2:1;
		uपूर्णांक64_t reserved_31_29:3;
		uपूर्णांक64_t raid_en:1;
		uपूर्णांक64_t fus318:1;
		uपूर्णांक64_t करोrm_crypto:1;
		uपूर्णांक64_t घातer_limit:2;
		uपूर्णांक64_t rom_info:10;
		uपूर्णांक64_t fus118:1;
		uपूर्णांक64_t gbl_pwr_throttle:8;
		uपूर्णांक64_t run_platक्रमm:3;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण cn78xxp2;
पूर्ण;

जोड़ cvmx_mio_fus_dat3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_dat3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t ema0:6;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t pll_alt_matrix:1;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t reserved_28_31:4;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t reserved_0_23:24;
#अन्यथा
		uपूर्णांक64_t reserved_0_23:24;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t reserved_28_31:4;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t pll_alt_matrix:1;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t ema0:6;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_fus_dat3_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t pll_भाग4:1;
		uपूर्णांक64_t reserved_29_30:2;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t icache:24;
#अन्यथा
		uपूर्णांक64_t icache:24;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t reserved_29_30:2;
		uपूर्णांक64_t pll_भाग4:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_mio_fus_dat3_cn31xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t pll_भाग4:1;
		uपूर्णांक64_t zip_crip:2;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t icache:24;
#अन्यथा
		uपूर्णांक64_t icache:24;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t zip_crip:2;
		uपूर्णांक64_t pll_भाग4:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn31xx;
	काष्ठा cvmx_mio_fus_dat3_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_31_63:33;
		uपूर्णांक64_t zip_crip:2;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t icache:24;
#अन्यथा
		uपूर्णांक64_t icache:24;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t zip_crip:2;
		uपूर्णांक64_t reserved_31_63:33;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_mio_fus_dat3_cn38xxp2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t icache:24;
#अन्यथा
		uपूर्णांक64_t icache:24;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn38xxp2;
	काष्ठा cvmx_mio_fus_dat3_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_58_63:6;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t reserved_40_40:1;
		uपूर्णांक64_t ema:2;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t reserved_0_23:24;
#अन्यथा
		uपूर्णांक64_t reserved_0_23:24;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_en:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t ema:2;
		uपूर्णांक64_t reserved_40_40:1;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t reserved_58_63:6;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_mio_fus_dat3_cn70xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t ema0:6;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t pll_alt_matrix:1;
		uपूर्णांक64_t pll_bwadj_denom:2;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t use_पूर्णांक_refclk:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t reserved_0_17:18;
#अन्यथा
		uपूर्णांक64_t reserved_0_17:18;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t use_पूर्णांक_refclk:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t pll_bwadj_denom:2;
		uपूर्णांक64_t pll_alt_matrix:1;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t ema0:6;
#पूर्ण_अगर
	पूर्ण cn70xx;
	काष्ठा cvmx_mio_fus_dat3_cn70xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t ema0:6;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t reserved_38_40:3;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t reserved_0_17:18;
#अन्यथा
		uपूर्णांक64_t reserved_0_17:18;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t reserved_38_40:3;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t ema0:6;
#पूर्ण_अगर
	पूर्ण cn70xxp1;
	काष्ठा cvmx_mio_fus_dat3_cn73xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t ema0:6;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t pll_alt_matrix:1;
		uपूर्णांक64_t pll_bwadj_denom:2;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t use_पूर्णांक_refclk:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t nohna_dte:1;
		uपूर्णांक64_t hna_info_dte:3;
		uपूर्णांक64_t hna_info_clm:4;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t core_pll_mul:5;
		uपूर्णांक64_t pnr_pll_mul:4;
#अन्यथा
		uपूर्णांक64_t pnr_pll_mul:4;
		uपूर्णांक64_t core_pll_mul:5;
		uपूर्णांक64_t reserved_9_9:1;
		uपूर्णांक64_t hna_info_clm:4;
		uपूर्णांक64_t hna_info_dte:3;
		uपूर्णांक64_t nohna_dte:1;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t use_पूर्णांक_refclk:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t pll_bwadj_denom:2;
		uपूर्णांक64_t pll_alt_matrix:1;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t ema0:6;
#पूर्ण_अगर
	पूर्ण cn73xx;
	काष्ठा cvmx_mio_fus_dat3_cn78xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t ema0:6;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t reserved_38_40:3;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t nohna_dte:1;
		uपूर्णांक64_t hna_info_dte:3;
		uपूर्णांक64_t hna_info_clm:4;
		uपूर्णांक64_t reserved_0_9:10;
#अन्यथा
		uपूर्णांक64_t reserved_0_9:10;
		uपूर्णांक64_t hna_info_clm:4;
		uपूर्णांक64_t hna_info_dte:3;
		uपूर्णांक64_t nohna_dte:1;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t reserved_38_40:3;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t ema0:6;
#पूर्ण_अगर
	पूर्ण cn78xx;
	काष्ठा cvmx_mio_fus_dat3_cnf75xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t ema0:6;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t pll_alt_matrix:1;
		uपूर्णांक64_t pll_bwadj_denom:2;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t use_पूर्णांक_refclk:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t reserved_9_17:9;
		uपूर्णांक64_t core_pll_mul:5;
		uपूर्णांक64_t pnr_pll_mul:4;
#अन्यथा
		uपूर्णांक64_t pnr_pll_mul:4;
		uपूर्णांक64_t core_pll_mul:5;
		uपूर्णांक64_t reserved_9_17:9;
		uपूर्णांक64_t ema1:6;
		uपूर्णांक64_t nodfa_dte:1;
		uपूर्णांक64_t nozip:1;
		uपूर्णांक64_t efus_ign:1;
		uपूर्णांक64_t efus_lck:1;
		uपूर्णांक64_t bar2_sz_conf:1;
		uपूर्णांक64_t zip_info:2;
		uपूर्णांक64_t use_पूर्णांक_refclk:1;
		uपूर्णांक64_t l2c_crip:3;
		uपूर्णांक64_t pll_half_dis:1;
		uपूर्णांक64_t efus_lck_man:1;
		uपूर्णांक64_t efus_lck_rsv:1;
		uपूर्णांक64_t pll_bwadj_denom:2;
		uपूर्णांक64_t pll_alt_matrix:1;
		uपूर्णांक64_t dfa_info_clm:4;
		uपूर्णांक64_t dfa_info_dte:3;
		uपूर्णांक64_t pll_ctl:10;
		uपूर्णांक64_t ema0:6;
#पूर्ण_अगर
	पूर्ण cnf75xx;
पूर्ण;

जोड़ cvmx_mio_fus_ema अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_ema_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t eff_ema:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t ema:3;
#अन्यथा
		uपूर्णांक64_t ema:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t eff_ema:3;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_fus_ema_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t ema:2;
#अन्यथा
		uपूर्णांक64_t ema:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn58xx;
पूर्ण;

जोड़ cvmx_mio_fus_pdf अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_pdf_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pdf:64;
#अन्यथा
		uपूर्णांक64_t pdf:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_pll अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_pll_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t rclk_align_r:8;
		uपूर्णांक64_t rclk_align_l:8;
		uपूर्णांक64_t reserved_8_31:24;
		uपूर्णांक64_t c_cout_rst:1;
		uपूर्णांक64_t c_cout_sel:2;
		uपूर्णांक64_t pnr_cout_rst:1;
		uपूर्णांक64_t pnr_cout_sel:2;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t fbslip:1;
#अन्यथा
		uपूर्णांक64_t fbslip:1;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t pnr_cout_sel:2;
		uपूर्णांक64_t pnr_cout_rst:1;
		uपूर्णांक64_t c_cout_sel:2;
		uपूर्णांक64_t c_cout_rst:1;
		uपूर्णांक64_t reserved_8_31:24;
		uपूर्णांक64_t rclk_align_l:8;
		uपूर्णांक64_t rclk_align_r:8;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_fus_pll_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t fbslip:1;
#अन्यथा
		uपूर्णांक64_t fbslip:1;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_mio_fus_pll_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t c_cout_rst:1;
		uपूर्णांक64_t c_cout_sel:2;
		uपूर्णांक64_t pnr_cout_rst:1;
		uपूर्णांक64_t pnr_cout_sel:2;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t fbslip:1;
#अन्यथा
		uपूर्णांक64_t fbslip:1;
		uपूर्णांक64_t rfslip:1;
		uपूर्णांक64_t pnr_cout_sel:2;
		uपूर्णांक64_t pnr_cout_rst:1;
		uपूर्णांक64_t c_cout_sel:2;
		uपूर्णांक64_t c_cout_rst:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_mio_fus_prog अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_prog_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t soft:1;
		uपूर्णांक64_t prog:1;
#अन्यथा
		uपूर्णांक64_t prog:1;
		uपूर्णांक64_t soft:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_fus_prog_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t prog:1;
#अन्यथा
		uपूर्णांक64_t prog:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_mio_fus_prog_बार अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_prog_बार_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_35_63:29;
		uपूर्णांक64_t vgate_pin:1;
		uपूर्णांक64_t fsrc_pin:1;
		uपूर्णांक64_t prog_pin:1;
		uपूर्णांक64_t reserved_6_31:26;
		uपूर्णांक64_t setup:6;
#अन्यथा
		uपूर्णांक64_t setup:6;
		uपूर्णांक64_t reserved_6_31:26;
		uपूर्णांक64_t prog_pin:1;
		uपूर्णांक64_t fsrc_pin:1;
		uपूर्णांक64_t vgate_pin:1;
		uपूर्णांक64_t reserved_35_63:29;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_fus_prog_बार_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t prog_pin:1;
		uपूर्णांक64_t out:8;
		uपूर्णांक64_t sclk_lo:4;
		uपूर्णांक64_t sclk_hi:12;
		uपूर्णांक64_t setup:8;
#अन्यथा
		uपूर्णांक64_t setup:8;
		uपूर्णांक64_t sclk_hi:12;
		uपूर्णांक64_t sclk_lo:4;
		uपूर्णांक64_t out:8;
		uपूर्णांक64_t prog_pin:1;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_mio_fus_prog_बार_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_35_63:29;
		uपूर्णांक64_t vgate_pin:1;
		uपूर्णांक64_t fsrc_pin:1;
		uपूर्णांक64_t prog_pin:1;
		uपूर्णांक64_t out:7;
		uपूर्णांक64_t sclk_lo:4;
		uपूर्णांक64_t sclk_hi:15;
		uपूर्णांक64_t setup:6;
#अन्यथा
		uपूर्णांक64_t setup:6;
		uपूर्णांक64_t sclk_hi:15;
		uपूर्णांक64_t sclk_lo:4;
		uपूर्णांक64_t out:7;
		uपूर्णांक64_t prog_pin:1;
		uपूर्णांक64_t fsrc_pin:1;
		uपूर्णांक64_t vgate_pin:1;
		uपूर्णांक64_t reserved_35_63:29;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_mio_fus_rcmd अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_rcmd_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t dat:8;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t efuse:1;
		uपूर्णांक64_t addr:8;
#अन्यथा
		uपूर्णांक64_t addr:8;
		uपूर्णांक64_t efuse:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t dat:8;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_fus_rcmd_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t dat:8;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t efuse:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t addr:7;
#अन्यथा
		uपूर्णांक64_t addr:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t efuse:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t pend:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t dat:8;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_mio_fus_पढ़ो_बार अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_पढ़ो_बार_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_26_63:38;
		uपूर्णांक64_t sch:4;
		uपूर्णांक64_t fsh:4;
		uपूर्णांक64_t prh:4;
		uपूर्णांक64_t sdh:4;
		uपूर्णांक64_t setup:10;
#अन्यथा
		uपूर्णांक64_t setup:10;
		uपूर्णांक64_t sdh:4;
		uपूर्णांक64_t prh:4;
		uपूर्णांक64_t fsh:4;
		uपूर्णांक64_t sch:4;
		uपूर्णांक64_t reserved_26_63:38;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_repair_res0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_repair_res0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_55_63:9;
		uपूर्णांक64_t too_many:1;
		uपूर्णांक64_t repair2:18;
		uपूर्णांक64_t repair1:18;
		uपूर्णांक64_t repair0:18;
#अन्यथा
		uपूर्णांक64_t repair0:18;
		uपूर्णांक64_t repair1:18;
		uपूर्णांक64_t repair2:18;
		uपूर्णांक64_t too_many:1;
		uपूर्णांक64_t reserved_55_63:9;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_repair_res1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_repair_res1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_54_63:10;
		uपूर्णांक64_t repair5:18;
		uपूर्णांक64_t repair4:18;
		uपूर्णांक64_t repair3:18;
#अन्यथा
		uपूर्णांक64_t repair3:18;
		uपूर्णांक64_t repair4:18;
		uपूर्णांक64_t repair5:18;
		uपूर्णांक64_t reserved_54_63:10;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_repair_res2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_repair_res2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t repair6:18;
#अन्यथा
		uपूर्णांक64_t repair6:18;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_spr_repair_res अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_spr_repair_res_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_42_63:22;
		uपूर्णांक64_t repair2:14;
		uपूर्णांक64_t repair1:14;
		uपूर्णांक64_t repair0:14;
#अन्यथा
		uपूर्णांक64_t repair0:14;
		uपूर्णांक64_t repair1:14;
		uपूर्णांक64_t repair2:14;
		uपूर्णांक64_t reserved_42_63:22;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_spr_repair_sum अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_spr_repair_sum_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t too_many:1;
#अन्यथा
		uपूर्णांक64_t too_many:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_tgg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_tgg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t val:1;
		uपूर्णांक64_t dat:63;
#अन्यथा
		uपूर्णांक64_t dat:63;
		uपूर्णांक64_t val:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_unlock अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_unlock_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t key:24;
#अन्यथा
		uपूर्णांक64_t key:24;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_fus_wadr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_fus_wadr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t addr:10;
#अन्यथा
		uपूर्णांक64_t addr:10;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_fus_wadr_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t addr:2;
#अन्यथा
		uपूर्णांक64_t addr:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_mio_fus_wadr_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t addr:3;
#अन्यथा
		uपूर्णांक64_t addr:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_mio_fus_wadr_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t addr:4;
#अन्यथा
		uपूर्णांक64_t addr:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_mio_gpio_comp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_gpio_comp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t pctl:6;
		uपूर्णांक64_t nctl:6;
#अन्यथा
		uपूर्णांक64_t nctl:6;
		uपूर्णांक64_t pctl:6;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ndf_dma_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ndf_dma_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t rw:1;
		uपूर्णांक64_t clr:1;
		uपूर्णांक64_t reserved_60_60:1;
		uपूर्णांक64_t swap32:1;
		uपूर्णांक64_t swap16:1;
		uपूर्णांक64_t swap8:1;
		uपूर्णांक64_t endian:1;
		uपूर्णांक64_t size:20;
		uपूर्णांक64_t adr:36;
#अन्यथा
		uपूर्णांक64_t adr:36;
		uपूर्णांक64_t size:20;
		uपूर्णांक64_t endian:1;
		uपूर्णांक64_t swap8:1;
		uपूर्णांक64_t swap16:1;
		uपूर्णांक64_t swap32:1;
		uपूर्णांक64_t reserved_60_60:1;
		uपूर्णांक64_t clr:1;
		uपूर्णांक64_t rw:1;
		uपूर्णांक64_t en:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ndf_dma_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ndf_dma_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t करोne:1;
#अन्यथा
		uपूर्णांक64_t करोne:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ndf_dma_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ndf_dma_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t करोne:1;
#अन्यथा
		uपूर्णांक64_t करोne:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_pll_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_pll_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t bw_ctl:5;
#अन्यथा
		uपूर्णांक64_t bw_ctl:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_pll_setting अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_pll_setting_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t setting:17;
#अन्यथा
		uपूर्णांक64_t setting:17;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_ckout_hi_incr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_ckout_hi_incr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t nanosec:32;
		uपूर्णांक64_t frnanosec:32;
#अन्यथा
		uपूर्णांक64_t frnanosec:32;
		uपूर्णांक64_t nanosec:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_ckout_lo_incr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_ckout_lo_incr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t nanosec:32;
		uपूर्णांक64_t frnanosec:32;
#अन्यथा
		uपूर्णांक64_t frnanosec:32;
		uपूर्णांक64_t nanosec:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_ckout_thresh_hi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_ckout_thresh_hi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t nanosec:64;
#अन्यथा
		uपूर्णांक64_t nanosec:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_ckout_thresh_lo अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_ckout_thresh_lo_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t frnanosec:32;
#अन्यथा
		uपूर्णांक64_t frnanosec:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_घड़ी_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_घड़ी_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_42_63:22;
		uपूर्णांक64_t pps:1;
		uपूर्णांक64_t ckout:1;
		uपूर्णांक64_t ext_clk_edge:2;
		uपूर्णांक64_t ckout_out4:1;
		uपूर्णांक64_t pps_out:5;
		uपूर्णांक64_t pps_inv:1;
		uपूर्णांक64_t pps_en:1;
		uपूर्णांक64_t ckout_out:4;
		uपूर्णांक64_t ckout_inv:1;
		uपूर्णांक64_t ckout_en:1;
		uपूर्णांक64_t evcnt_in:6;
		uपूर्णांक64_t evcnt_edge:1;
		uपूर्णांक64_t evcnt_en:1;
		uपूर्णांक64_t tsपंचांगp_in:6;
		uपूर्णांक64_t tsपंचांगp_edge:1;
		uपूर्णांक64_t tsपंचांगp_en:1;
		uपूर्णांक64_t ext_clk_in:6;
		uपूर्णांक64_t ext_clk_en:1;
		uपूर्णांक64_t ptp_en:1;
#अन्यथा
		uपूर्णांक64_t ptp_en:1;
		uपूर्णांक64_t ext_clk_en:1;
		uपूर्णांक64_t ext_clk_in:6;
		uपूर्णांक64_t tsपंचांगp_en:1;
		uपूर्णांक64_t tsपंचांगp_edge:1;
		uपूर्णांक64_t tsपंचांगp_in:6;
		uपूर्णांक64_t evcnt_en:1;
		uपूर्णांक64_t evcnt_edge:1;
		uपूर्णांक64_t evcnt_in:6;
		uपूर्णांक64_t ckout_en:1;
		uपूर्णांक64_t ckout_inv:1;
		uपूर्णांक64_t ckout_out:4;
		uपूर्णांक64_t pps_en:1;
		uपूर्णांक64_t pps_inv:1;
		uपूर्णांक64_t pps_out:5;
		uपूर्णांक64_t ckout_out4:1;
		uपूर्णांक64_t ext_clk_edge:2;
		uपूर्णांक64_t ckout:1;
		uपूर्णांक64_t pps:1;
		uपूर्णांक64_t reserved_42_63:22;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_ptp_घड़ी_cfg_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t evcnt_in:6;
		uपूर्णांक64_t evcnt_edge:1;
		uपूर्णांक64_t evcnt_en:1;
		uपूर्णांक64_t tsपंचांगp_in:6;
		uपूर्णांक64_t tsपंचांगp_edge:1;
		uपूर्णांक64_t tsपंचांगp_en:1;
		uपूर्णांक64_t ext_clk_in:6;
		uपूर्णांक64_t ext_clk_en:1;
		uपूर्णांक64_t ptp_en:1;
#अन्यथा
		uपूर्णांक64_t ptp_en:1;
		uपूर्णांक64_t ext_clk_en:1;
		uपूर्णांक64_t ext_clk_in:6;
		uपूर्णांक64_t tsपंचांगp_en:1;
		uपूर्णांक64_t tsपंचांगp_edge:1;
		uपूर्णांक64_t tsपंचांगp_in:6;
		uपूर्णांक64_t evcnt_en:1;
		uपूर्णांक64_t evcnt_edge:1;
		uपूर्णांक64_t evcnt_in:6;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_mio_ptp_घड़ी_cfg_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t ext_clk_edge:2;
		uपूर्णांक64_t ckout_out4:1;
		uपूर्णांक64_t pps_out:5;
		uपूर्णांक64_t pps_inv:1;
		uपूर्णांक64_t pps_en:1;
		uपूर्णांक64_t ckout_out:4;
		uपूर्णांक64_t ckout_inv:1;
		uपूर्णांक64_t ckout_en:1;
		uपूर्णांक64_t evcnt_in:6;
		uपूर्णांक64_t evcnt_edge:1;
		uपूर्णांक64_t evcnt_en:1;
		uपूर्णांक64_t tsपंचांगp_in:6;
		uपूर्णांक64_t tsपंचांगp_edge:1;
		uपूर्णांक64_t tsपंचांगp_en:1;
		uपूर्णांक64_t ext_clk_in:6;
		uपूर्णांक64_t ext_clk_en:1;
		uपूर्णांक64_t ptp_en:1;
#अन्यथा
		uपूर्णांक64_t ptp_en:1;
		uपूर्णांक64_t ext_clk_en:1;
		uपूर्णांक64_t ext_clk_in:6;
		uपूर्णांक64_t tsपंचांगp_en:1;
		uपूर्णांक64_t tsपंचांगp_edge:1;
		uपूर्णांक64_t tsपंचांगp_in:6;
		uपूर्णांक64_t evcnt_en:1;
		uपूर्णांक64_t evcnt_edge:1;
		uपूर्णांक64_t evcnt_in:6;
		uपूर्णांक64_t ckout_en:1;
		uपूर्णांक64_t ckout_inv:1;
		uपूर्णांक64_t ckout_out:4;
		uपूर्णांक64_t pps_en:1;
		uपूर्णांक64_t pps_inv:1;
		uपूर्णांक64_t pps_out:5;
		uपूर्णांक64_t ckout_out4:1;
		uपूर्णांक64_t ext_clk_edge:2;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण cn66xx;
पूर्ण;

जोड़ cvmx_mio_ptp_घड़ी_comp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_घड़ी_comp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t nanosec:32;
		uपूर्णांक64_t frnanosec:32;
#अन्यथा
		uपूर्णांक64_t frnanosec:32;
		uपूर्णांक64_t nanosec:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_घड़ी_hi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_घड़ी_hi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t nanosec:64;
#अन्यथा
		uपूर्णांक64_t nanosec:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_घड़ी_lo अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_घड़ी_lo_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t frnanosec:32;
#अन्यथा
		uपूर्णांक64_t frnanosec:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_evt_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_evt_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t cntr:64;
#अन्यथा
		uपूर्णांक64_t cntr:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_phy_1pps_in अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_phy_1pps_in_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t sel:5;
#अन्यथा
		uपूर्णांक64_t sel:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_pps_hi_incr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_pps_hi_incr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t nanosec:32;
		uपूर्णांक64_t frnanosec:32;
#अन्यथा
		uपूर्णांक64_t frnanosec:32;
		uपूर्णांक64_t nanosec:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_pps_lo_incr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_pps_lo_incr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t nanosec:32;
		uपूर्णांक64_t frnanosec:32;
#अन्यथा
		uपूर्णांक64_t frnanosec:32;
		uपूर्णांक64_t nanosec:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_pps_thresh_hi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_pps_thresh_hi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t nanosec:64;
#अन्यथा
		uपूर्णांक64_t nanosec:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_pps_thresh_lo अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_pps_thresh_lo_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t frnanosec:32;
#अन्यथा
		uपूर्णांक64_t frnanosec:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_ptp_बारtamp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_ptp_बारtamp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t nanosec:64;
#अन्यथा
		uपूर्णांक64_t nanosec:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_qlmx_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_qlmx_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t prपंचांगode:1;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t qlm_spd:4;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t qlm_cfg:4;
#अन्यथा
		uपूर्णांक64_t qlm_cfg:4;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t qlm_spd:4;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t prपंचांगode:1;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_qlmx_cfg_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t prपंचांगode:1;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t qlm_spd:4;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t qlm_cfg:2;
#अन्यथा
		uपूर्णांक64_t qlm_cfg:2;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t qlm_spd:4;
		uपूर्णांक64_t reserved_12_13:2;
		uपूर्णांक64_t prपंचांगode:1;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_mio_qlmx_cfg_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t qlm_spd:4;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t qlm_cfg:4;
#अन्यथा
		uपूर्णांक64_t qlm_cfg:4;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t qlm_spd:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn66xx;
	काष्ठा cvmx_mio_qlmx_cfg_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t qlm_spd:4;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t qlm_cfg:3;
#अन्यथा
		uपूर्णांक64_t qlm_cfg:3;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t qlm_spd:4;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_mio_rst_boot अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_rst_boot_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t chipसमाप्त:1;
		uपूर्णांक64_t jtcsrdis:1;
		uपूर्णांक64_t ejtagdis:1;
		uपूर्णांक64_t romen:1;
		uपूर्णांक64_t cसमाप्त_ppdis:1;
		uपूर्णांक64_t jt_tsपंचांगode:1;
		uपूर्णांक64_t reserved_50_57:8;
		uपूर्णांक64_t lboot_ext:2;
		uपूर्णांक64_t reserved_44_47:4;
		uपूर्णांक64_t qlm4_spd:4;
		uपूर्णांक64_t qlm3_spd:4;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t rboot_pin:1;
#अन्यथा
		uपूर्णांक64_t rboot_pin:1;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t qlm3_spd:4;
		uपूर्णांक64_t qlm4_spd:4;
		uपूर्णांक64_t reserved_44_47:4;
		uपूर्णांक64_t lboot_ext:2;
		uपूर्णांक64_t reserved_50_57:8;
		uपूर्णांक64_t jt_tsपंचांगode:1;
		uपूर्णांक64_t cसमाप्त_ppdis:1;
		uपूर्णांक64_t romen:1;
		uपूर्णांक64_t ejtagdis:1;
		uपूर्णांक64_t jtcsrdis:1;
		uपूर्णांक64_t chipसमाप्त:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_rst_boot_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t chipसमाप्त:1;
		uपूर्णांक64_t jtcsrdis:1;
		uपूर्णांक64_t ejtagdis:1;
		uपूर्णांक64_t romen:1;
		uपूर्णांक64_t cसमाप्त_ppdis:1;
		uपूर्णांक64_t jt_tsपंचांगode:1;
		uपूर्णांक64_t reserved_50_57:8;
		uपूर्णांक64_t lboot_ext:2;
		uपूर्णांक64_t reserved_36_47:12;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t rboot_pin:1;
#अन्यथा
		uपूर्णांक64_t rboot_pin:1;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t reserved_36_47:12;
		uपूर्णांक64_t lboot_ext:2;
		uपूर्णांक64_t reserved_50_57:8;
		uपूर्णांक64_t jt_tsपंचांगode:1;
		uपूर्णांक64_t cसमाप्त_ppdis:1;
		uपूर्णांक64_t romen:1;
		uपूर्णांक64_t ejtagdis:1;
		uपूर्णांक64_t jtcsrdis:1;
		uपूर्णांक64_t chipसमाप्त:1;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_mio_rst_boot_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t rboot_pin:1;
#अन्यथा
		uपूर्णांक64_t rboot_pin:1;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_mio_rst_boot_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t chipसमाप्त:1;
		uपूर्णांक64_t jtcsrdis:1;
		uपूर्णांक64_t ejtagdis:1;
		uपूर्णांक64_t romen:1;
		uपूर्णांक64_t cसमाप्त_ppdis:1;
		uपूर्णांक64_t reserved_50_58:9;
		uपूर्णांक64_t lboot_ext:2;
		uपूर्णांक64_t reserved_36_47:12;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t rboot_pin:1;
#अन्यथा
		uपूर्णांक64_t rboot_pin:1;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t reserved_36_47:12;
		uपूर्णांक64_t lboot_ext:2;
		uपूर्णांक64_t reserved_50_58:9;
		uपूर्णांक64_t cसमाप्त_ppdis:1;
		uपूर्णांक64_t romen:1;
		uपूर्णांक64_t ejtagdis:1;
		uपूर्णांक64_t jtcsrdis:1;
		uपूर्णांक64_t chipसमाप्त:1;
#पूर्ण_अगर
	पूर्ण cn66xx;
	काष्ठा cvmx_mio_rst_boot_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t jt_tsपंचांगode:1;
		uपूर्णांक64_t reserved_44_57:14;
		uपूर्णांक64_t qlm4_spd:4;
		uपूर्णांक64_t qlm3_spd:4;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t rboot_pin:1;
#अन्यथा
		uपूर्णांक64_t rboot_pin:1;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t qlm3_spd:4;
		uपूर्णांक64_t qlm4_spd:4;
		uपूर्णांक64_t reserved_44_57:14;
		uपूर्णांक64_t jt_tsपंचांगode:1;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण cn68xx;
	काष्ठा cvmx_mio_rst_boot_cn68xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t qlm4_spd:4;
		uपूर्णांक64_t qlm3_spd:4;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t rboot_pin:1;
#अन्यथा
		uपूर्णांक64_t rboot_pin:1;
		uपूर्णांक64_t rboot:1;
		uपूर्णांक64_t lboot:10;
		uपूर्णांक64_t qlm0_spd:4;
		uपूर्णांक64_t qlm1_spd:4;
		uपूर्णांक64_t qlm2_spd:4;
		uपूर्णांक64_t pnr_mul:6;
		uपूर्णांक64_t c_mul:6;
		uपूर्णांक64_t qlm3_spd:4;
		uपूर्णांक64_t qlm4_spd:4;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण cn68xxp1;
पूर्ण;

जोड़ cvmx_mio_rst_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_rst_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t cntl_clr_bist:1;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t soft_clr_bist:1;
#अन्यथा
		uपूर्णांक64_t soft_clr_bist:1;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t cntl_clr_bist:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_rst_cfg_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bist_delay:58;
		uपूर्णांक64_t reserved_3_5:3;
		uपूर्णांक64_t cntl_clr_bist:1;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t soft_clr_bist:1;
#अन्यथा
		uपूर्णांक64_t soft_clr_bist:1;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t cntl_clr_bist:1;
		uपूर्णांक64_t reserved_3_5:3;
		uपूर्णांक64_t bist_delay:58;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_mio_rst_cfg_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bist_delay:58;
		uपूर्णांक64_t reserved_2_5:4;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t soft_clr_bist:1;
#अन्यथा
		uपूर्णांक64_t soft_clr_bist:1;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t reserved_2_5:4;
		uपूर्णांक64_t bist_delay:58;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
	काष्ठा cvmx_mio_rst_cfg_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bist_delay:56;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t cntl_clr_bist:1;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t soft_clr_bist:1;
#अन्यथा
		uपूर्णांक64_t soft_clr_bist:1;
		uपूर्णांक64_t warm_clr_bist:1;
		uपूर्णांक64_t cntl_clr_bist:1;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t bist_delay:56;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_mio_rst_cसमाप्त अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_rst_cसमाप्त_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_47_63:17;
		uपूर्णांक64_t समयr:47;
#अन्यथा
		uपूर्णांक64_t समयr:47;
		uपूर्णांक64_t reserved_47_63:17;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_rst_cntlx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_rst_cntlx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t in_rev_ln:1;
		uपूर्णांक64_t rev_lanes:1;
		uपूर्णांक64_t gen1_only:1;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_val:1;
#अन्यथा
		uपूर्णांक64_t rst_val:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t gen1_only:1;
		uपूर्णांक64_t rev_lanes:1;
		uपूर्णांक64_t in_rev_ln:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_rst_cntlx_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_val:1;
#अन्यथा
		uपूर्णांक64_t rst_val:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn66xx;
पूर्ण;

जोड़ cvmx_mio_rst_ctlx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_rst_ctlx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t in_rev_ln:1;
		uपूर्णांक64_t rev_lanes:1;
		uपूर्णांक64_t gen1_only:1;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_val:1;
#अन्यथा
		uपूर्णांक64_t rst_val:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t gen1_only:1;
		uपूर्णांक64_t rev_lanes:1;
		uपूर्णांक64_t in_rev_ln:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_rst_ctlx_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_val:1;
#अन्यथा
		uपूर्णांक64_t rst_val:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t prst_link:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_mio_rst_ctlx_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_val:1;
#अन्यथा
		uपूर्णांक64_t rst_val:1;
		uपूर्णांक64_t rst_chip:1;
		uपूर्णांक64_t rst_rcv:1;
		uपूर्णांक64_t rst_drv:1;
		uपूर्णांक64_t prपंचांगode:2;
		uपूर्णांक64_t host_mode:1;
		uपूर्णांक64_t rst_link:1;
		uपूर्णांक64_t rst_करोne:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_mio_rst_delay अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_rst_delay_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t warm_rst_dly:16;
		uपूर्णांक64_t soft_rst_dly:16;
#अन्यथा
		uपूर्णांक64_t soft_rst_dly:16;
		uपूर्णांक64_t warm_rst_dly:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_rst_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_rst_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t perst1:1;
		uपूर्णांक64_t perst0:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t rst_link3:1;
		uपूर्णांक64_t rst_link2:1;
		uपूर्णांक64_t rst_link1:1;
		uपूर्णांक64_t rst_link0:1;
#अन्यथा
		uपूर्णांक64_t rst_link0:1;
		uपूर्णांक64_t rst_link1:1;
		uपूर्णांक64_t rst_link2:1;
		uपूर्णांक64_t rst_link3:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t perst0:1;
		uपूर्णांक64_t perst1:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_rst_पूर्णांक_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t perst1:1;
		uपूर्णांक64_t perst0:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t rst_link1:1;
		uपूर्णांक64_t rst_link0:1;
#अन्यथा
		uपूर्णांक64_t rst_link0:1;
		uपूर्णांक64_t rst_link1:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t perst0:1;
		uपूर्णांक64_t perst1:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_mio_rst_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_rst_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t perst1:1;
		uपूर्णांक64_t perst0:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t rst_link3:1;
		uपूर्णांक64_t rst_link2:1;
		uपूर्णांक64_t rst_link1:1;
		uपूर्णांक64_t rst_link0:1;
#अन्यथा
		uपूर्णांक64_t rst_link0:1;
		uपूर्णांक64_t rst_link1:1;
		uपूर्णांक64_t rst_link2:1;
		uपूर्णांक64_t rst_link3:1;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t perst0:1;
		uपूर्णांक64_t perst1:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_rst_पूर्णांक_en_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t perst1:1;
		uपूर्णांक64_t perst0:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t rst_link1:1;
		uपूर्णांक64_t rst_link0:1;
#अन्यथा
		uपूर्णांक64_t rst_link0:1;
		uपूर्णांक64_t rst_link1:1;
		uपूर्णांक64_t reserved_2_7:6;
		uपूर्णांक64_t perst0:1;
		uपूर्णांक64_t perst1:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_mio_twsx_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_twsx_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t scl:1;
		uपूर्णांक64_t sda:1;
		uपूर्णांक64_t scl_ovr:1;
		uपूर्णांक64_t sda_ovr:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t core_en:1;
		uपूर्णांक64_t ts_en:1;
		uपूर्णांक64_t st_en:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t core_पूर्णांक:1;
		uपूर्णांक64_t ts_पूर्णांक:1;
		uपूर्णांक64_t st_पूर्णांक:1;
#अन्यथा
		uपूर्णांक64_t st_पूर्णांक:1;
		uपूर्णांक64_t ts_पूर्णांक:1;
		uपूर्णांक64_t core_पूर्णांक:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t st_en:1;
		uपूर्णांक64_t ts_en:1;
		uपूर्णांक64_t core_en:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t sda_ovr:1;
		uपूर्णांक64_t scl_ovr:1;
		uपूर्णांक64_t sda:1;
		uपूर्णांक64_t scl:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_mio_twsx_पूर्णांक_cn38xxp2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t core_en:1;
		uपूर्णांक64_t ts_en:1;
		uपूर्णांक64_t st_en:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t core_पूर्णांक:1;
		uपूर्णांक64_t ts_पूर्णांक:1;
		uपूर्णांक64_t st_पूर्णांक:1;
#अन्यथा
		uपूर्णांक64_t st_पूर्णांक:1;
		uपूर्णांक64_t ts_पूर्णांक:1;
		uपूर्णांक64_t core_पूर्णांक:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t st_en:1;
		uपूर्णांक64_t ts_en:1;
		uपूर्णांक64_t core_en:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण cn38xxp2;
पूर्ण;

जोड़ cvmx_mio_twsx_sw_twsi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_twsx_sw_twsi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t v:1;
		uपूर्णांक64_t slonly:1;
		uपूर्णांक64_t eia:1;
		uपूर्णांक64_t op:4;
		uपूर्णांक64_t r:1;
		uपूर्णांक64_t sovr:1;
		uपूर्णांक64_t size:3;
		uपूर्णांक64_t scr:2;
		uपूर्णांक64_t a:10;
		uपूर्णांक64_t ia:5;
		uपूर्णांक64_t eop_ia:3;
		uपूर्णांक64_t d:32;
#अन्यथा
		uपूर्णांक64_t d:32;
		uपूर्णांक64_t eop_ia:3;
		uपूर्णांक64_t ia:5;
		uपूर्णांक64_t a:10;
		uपूर्णांक64_t scr:2;
		uपूर्णांक64_t size:3;
		uपूर्णांक64_t sovr:1;
		uपूर्णांक64_t r:1;
		uपूर्णांक64_t op:4;
		uपूर्णांक64_t eia:1;
		uपूर्णांक64_t slonly:1;
		uपूर्णांक64_t v:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_twsx_sw_twsi_ext अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_twsx_sw_twsi_ext_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t ia:8;
		uपूर्णांक64_t d:32;
#अन्यथा
		uपूर्णांक64_t d:32;
		uपूर्णांक64_t ia:8;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_twsx_twsi_sw अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_twsx_twsi_sw_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t v:2;
		uपूर्णांक64_t reserved_32_61:30;
		uपूर्णांक64_t d:32;
#अन्यथा
		uपूर्णांक64_t d:32;
		uपूर्णांक64_t reserved_32_61:30;
		uपूर्णांक64_t v:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_dlh अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_dlh_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t dlh:8;
#अन्यथा
		uपूर्णांक64_t dlh:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_dll अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_dll_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t dll:8;
#अन्यथा
		uपूर्णांक64_t dll:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_far अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_far_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t far:1;
#अन्यथा
		uपूर्णांक64_t far:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_fcr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_fcr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t rxtrig:2;
		uपूर्णांक64_t txtrig:2;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t txfr:1;
		uपूर्णांक64_t rxfr:1;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t rxfr:1;
		uपूर्णांक64_t txfr:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t txtrig:2;
		uपूर्णांक64_t rxtrig:2;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_htx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_htx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t htx:1;
#अन्यथा
		uपूर्णांक64_t htx:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_ier अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_ier_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t edssi:1;
		uपूर्णांक64_t elsi:1;
		uपूर्णांक64_t etbei:1;
		uपूर्णांक64_t erbfi:1;
#अन्यथा
		uपूर्णांक64_t erbfi:1;
		uपूर्णांक64_t etbei:1;
		uपूर्णांक64_t elsi:1;
		uपूर्णांक64_t edssi:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_iir अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_iir_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t fen:2;
		uपूर्णांक64_t reserved_4_5:2;
		uपूर्णांक64_t iid:4;
#अन्यथा
		uपूर्णांक64_t iid:4;
		uपूर्णांक64_t reserved_4_5:2;
		uपूर्णांक64_t fen:2;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_lcr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_lcr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t dlab:1;
		uपूर्णांक64_t brk:1;
		uपूर्णांक64_t reserved_5_5:1;
		uपूर्णांक64_t eps:1;
		uपूर्णांक64_t pen:1;
		uपूर्णांक64_t stop:1;
		uपूर्णांक64_t cls:2;
#अन्यथा
		uपूर्णांक64_t cls:2;
		uपूर्णांक64_t stop:1;
		uपूर्णांक64_t pen:1;
		uपूर्णांक64_t eps:1;
		uपूर्णांक64_t reserved_5_5:1;
		uपूर्णांक64_t brk:1;
		uपूर्णांक64_t dlab:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_lsr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_lsr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t ferr:1;
		uपूर्णांक64_t temt:1;
		uपूर्णांक64_t thre:1;
		uपूर्णांक64_t bi:1;
		uपूर्णांक64_t fe:1;
		uपूर्णांक64_t pe:1;
		uपूर्णांक64_t oe:1;
		uपूर्णांक64_t dr:1;
#अन्यथा
		uपूर्णांक64_t dr:1;
		uपूर्णांक64_t oe:1;
		uपूर्णांक64_t pe:1;
		uपूर्णांक64_t fe:1;
		uपूर्णांक64_t bi:1;
		uपूर्णांक64_t thre:1;
		uपूर्णांक64_t temt:1;
		uपूर्णांक64_t ferr:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_mcr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_mcr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t afce:1;
		uपूर्णांक64_t loop:1;
		uपूर्णांक64_t out2:1;
		uपूर्णांक64_t out1:1;
		uपूर्णांक64_t rts:1;
		uपूर्णांक64_t dtr:1;
#अन्यथा
		uपूर्णांक64_t dtr:1;
		uपूर्णांक64_t rts:1;
		uपूर्णांक64_t out1:1;
		uपूर्णांक64_t out2:1;
		uपूर्णांक64_t loop:1;
		uपूर्णांक64_t afce:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_msr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_msr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t dcd:1;
		uपूर्णांक64_t ri:1;
		uपूर्णांक64_t dsr:1;
		uपूर्णांक64_t cts:1;
		uपूर्णांक64_t ddcd:1;
		uपूर्णांक64_t teri:1;
		uपूर्णांक64_t ddsr:1;
		uपूर्णांक64_t dcts:1;
#अन्यथा
		uपूर्णांक64_t dcts:1;
		uपूर्णांक64_t ddsr:1;
		uपूर्णांक64_t teri:1;
		uपूर्णांक64_t ddcd:1;
		uपूर्णांक64_t cts:1;
		uपूर्णांक64_t dsr:1;
		uपूर्णांक64_t ri:1;
		uपूर्णांक64_t dcd:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_rbr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_rbr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t rbr:8;
#अन्यथा
		uपूर्णांक64_t rbr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_rfl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_rfl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t rfl:7;
#अन्यथा
		uपूर्णांक64_t rfl:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_rfw अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_rfw_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t rffe:1;
		uपूर्णांक64_t rfpe:1;
		uपूर्णांक64_t rfwd:8;
#अन्यथा
		uपूर्णांक64_t rfwd:8;
		uपूर्णांक64_t rfpe:1;
		uपूर्णांक64_t rffe:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_sbcr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_sbcr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t sbcr:1;
#अन्यथा
		uपूर्णांक64_t sbcr:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_scr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_scr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t scr:8;
#अन्यथा
		uपूर्णांक64_t scr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_sfe अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_sfe_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t sfe:1;
#अन्यथा
		uपूर्णांक64_t sfe:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_srr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_srr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t stfr:1;
		uपूर्णांक64_t srfr:1;
		uपूर्णांक64_t usr:1;
#अन्यथा
		uपूर्णांक64_t usr:1;
		uपूर्णांक64_t srfr:1;
		uपूर्णांक64_t stfr:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_srt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_srt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t srt:2;
#अन्यथा
		uपूर्णांक64_t srt:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_srts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_srts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t srts:1;
#अन्यथा
		uपूर्णांक64_t srts:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_stt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_stt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t stt:2;
#अन्यथा
		uपूर्णांक64_t stt:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_tfl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_tfl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t tfl:7;
#अन्यथा
		uपूर्णांक64_t tfl:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_tfr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_tfr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t tfr:8;
#अन्यथा
		uपूर्णांक64_t tfr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_thr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_thr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t thr:8;
#अन्यथा
		uपूर्णांक64_t thr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uartx_usr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uartx_usr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t rff:1;
		uपूर्णांक64_t rfne:1;
		uपूर्णांक64_t tfe:1;
		uपूर्णांक64_t tfnf:1;
		uपूर्णांक64_t busy:1;
#अन्यथा
		uपूर्णांक64_t busy:1;
		uपूर्णांक64_t tfnf:1;
		uपूर्णांक64_t tfe:1;
		uपूर्णांक64_t rfne:1;
		uपूर्णांक64_t rff:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_dlh अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_dlh_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t dlh:8;
#अन्यथा
		uपूर्णांक64_t dlh:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_dll अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_dll_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t dll:8;
#अन्यथा
		uपूर्णांक64_t dll:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_far अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_far_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t far:1;
#अन्यथा
		uपूर्णांक64_t far:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_fcr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_fcr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t rxtrig:2;
		uपूर्णांक64_t txtrig:2;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t txfr:1;
		uपूर्णांक64_t rxfr:1;
		uपूर्णांक64_t en:1;
#अन्यथा
		uपूर्णांक64_t en:1;
		uपूर्णांक64_t rxfr:1;
		uपूर्णांक64_t txfr:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t txtrig:2;
		uपूर्णांक64_t rxtrig:2;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_htx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_htx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t htx:1;
#अन्यथा
		uपूर्णांक64_t htx:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_ier अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_ier_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t edssi:1;
		uपूर्णांक64_t elsi:1;
		uपूर्णांक64_t etbei:1;
		uपूर्णांक64_t erbfi:1;
#अन्यथा
		uपूर्णांक64_t erbfi:1;
		uपूर्णांक64_t etbei:1;
		uपूर्णांक64_t elsi:1;
		uपूर्णांक64_t edssi:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t pसमय:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_iir अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_iir_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t fen:2;
		uपूर्णांक64_t reserved_4_5:2;
		uपूर्णांक64_t iid:4;
#अन्यथा
		uपूर्णांक64_t iid:4;
		uपूर्णांक64_t reserved_4_5:2;
		uपूर्णांक64_t fen:2;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_lcr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_lcr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t dlab:1;
		uपूर्णांक64_t brk:1;
		uपूर्णांक64_t reserved_5_5:1;
		uपूर्णांक64_t eps:1;
		uपूर्णांक64_t pen:1;
		uपूर्णांक64_t stop:1;
		uपूर्णांक64_t cls:2;
#अन्यथा
		uपूर्णांक64_t cls:2;
		uपूर्णांक64_t stop:1;
		uपूर्णांक64_t pen:1;
		uपूर्णांक64_t eps:1;
		uपूर्णांक64_t reserved_5_5:1;
		uपूर्णांक64_t brk:1;
		uपूर्णांक64_t dlab:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_lsr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_lsr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t ferr:1;
		uपूर्णांक64_t temt:1;
		uपूर्णांक64_t thre:1;
		uपूर्णांक64_t bi:1;
		uपूर्णांक64_t fe:1;
		uपूर्णांक64_t pe:1;
		uपूर्णांक64_t oe:1;
		uपूर्णांक64_t dr:1;
#अन्यथा
		uपूर्णांक64_t dr:1;
		uपूर्णांक64_t oe:1;
		uपूर्णांक64_t pe:1;
		uपूर्णांक64_t fe:1;
		uपूर्णांक64_t bi:1;
		uपूर्णांक64_t thre:1;
		uपूर्णांक64_t temt:1;
		uपूर्णांक64_t ferr:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_mcr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_mcr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t afce:1;
		uपूर्णांक64_t loop:1;
		uपूर्णांक64_t out2:1;
		uपूर्णांक64_t out1:1;
		uपूर्णांक64_t rts:1;
		uपूर्णांक64_t dtr:1;
#अन्यथा
		uपूर्णांक64_t dtr:1;
		uपूर्णांक64_t rts:1;
		uपूर्णांक64_t out1:1;
		uपूर्णांक64_t out2:1;
		uपूर्णांक64_t loop:1;
		uपूर्णांक64_t afce:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_msr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_msr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t dcd:1;
		uपूर्णांक64_t ri:1;
		uपूर्णांक64_t dsr:1;
		uपूर्णांक64_t cts:1;
		uपूर्णांक64_t ddcd:1;
		uपूर्णांक64_t teri:1;
		uपूर्णांक64_t ddsr:1;
		uपूर्णांक64_t dcts:1;
#अन्यथा
		uपूर्णांक64_t dcts:1;
		uपूर्णांक64_t ddsr:1;
		uपूर्णांक64_t teri:1;
		uपूर्णांक64_t ddcd:1;
		uपूर्णांक64_t cts:1;
		uपूर्णांक64_t dsr:1;
		uपूर्णांक64_t ri:1;
		uपूर्णांक64_t dcd:1;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_rbr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_rbr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t rbr:8;
#अन्यथा
		uपूर्णांक64_t rbr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_rfl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_rfl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t rfl:7;
#अन्यथा
		uपूर्णांक64_t rfl:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_rfw अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_rfw_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t rffe:1;
		uपूर्णांक64_t rfpe:1;
		uपूर्णांक64_t rfwd:8;
#अन्यथा
		uपूर्णांक64_t rfwd:8;
		uपूर्णांक64_t rfpe:1;
		uपूर्णांक64_t rffe:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_sbcr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_sbcr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t sbcr:1;
#अन्यथा
		uपूर्णांक64_t sbcr:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_scr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_scr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t scr:8;
#अन्यथा
		uपूर्णांक64_t scr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_sfe अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_sfe_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t sfe:1;
#अन्यथा
		uपूर्णांक64_t sfe:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_srr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_srr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t stfr:1;
		uपूर्णांक64_t srfr:1;
		uपूर्णांक64_t usr:1;
#अन्यथा
		uपूर्णांक64_t usr:1;
		uपूर्णांक64_t srfr:1;
		uपूर्णांक64_t stfr:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_srt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_srt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t srt:2;
#अन्यथा
		uपूर्णांक64_t srt:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_srts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_srts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t srts:1;
#अन्यथा
		uपूर्णांक64_t srts:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_stt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_stt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t stt:2;
#अन्यथा
		uपूर्णांक64_t stt:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_tfl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_tfl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t tfl:7;
#अन्यथा
		uपूर्णांक64_t tfl:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_tfr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_tfr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t tfr:8;
#अन्यथा
		uपूर्णांक64_t tfr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_thr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_thr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t thr:8;
#अन्यथा
		uपूर्णांक64_t thr:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_mio_uart2_usr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_mio_uart2_usr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t rff:1;
		uपूर्णांक64_t rfne:1;
		uपूर्णांक64_t tfe:1;
		uपूर्णांक64_t tfnf:1;
		uपूर्णांक64_t busy:1;
#अन्यथा
		uपूर्णांक64_t busy:1;
		uपूर्णांक64_t tfnf:1;
		uपूर्णांक64_t tfe:1;
		uपूर्णांक64_t rfne:1;
		uपूर्णांक64_t rff:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
