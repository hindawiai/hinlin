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

#अगर_अघोषित __CVMX_IOB_DEFS_H__
#घोषणा __CVMX_IOB_DEFS_H__

#घोषणा CVMX_IOB_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011800F00007F8ull))
#घोषणा CVMX_IOB_CTL_STATUS (CVMX_ADD_IO_SEG(0x00011800F0000050ull))
#घोषणा CVMX_IOB_DWB_PRI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000028ull))
#घोषणा CVMX_IOB_FAU_TIMEOUT (CVMX_ADD_IO_SEG(0x00011800F0000000ull))
#घोषणा CVMX_IOB_I2C_PRI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000010ull))
#घोषणा CVMX_IOB_INB_CONTROL_MATCH (CVMX_ADD_IO_SEG(0x00011800F0000078ull))
#घोषणा CVMX_IOB_INB_CONTROL_MATCH_ENB (CVMX_ADD_IO_SEG(0x00011800F0000088ull))
#घोषणा CVMX_IOB_INB_DATA_MATCH (CVMX_ADD_IO_SEG(0x00011800F0000070ull))
#घोषणा CVMX_IOB_INB_DATA_MATCH_ENB (CVMX_ADD_IO_SEG(0x00011800F0000080ull))
#घोषणा CVMX_IOB_INT_ENB (CVMX_ADD_IO_SEG(0x00011800F0000060ull))
#घोषणा CVMX_IOB_INT_SUM (CVMX_ADD_IO_SEG(0x00011800F0000058ull))
#घोषणा CVMX_IOB_N2C_L2C_PRI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000020ull))
#घोषणा CVMX_IOB_N2C_RSP_PRI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000008ull))
#घोषणा CVMX_IOB_OUTB_COM_PRI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000040ull))
#घोषणा CVMX_IOB_OUTB_CONTROL_MATCH (CVMX_ADD_IO_SEG(0x00011800F0000098ull))
#घोषणा CVMX_IOB_OUTB_CONTROL_MATCH_ENB (CVMX_ADD_IO_SEG(0x00011800F00000A8ull))
#घोषणा CVMX_IOB_OUTB_DATA_MATCH (CVMX_ADD_IO_SEG(0x00011800F0000090ull))
#घोषणा CVMX_IOB_OUTB_DATA_MATCH_ENB (CVMX_ADD_IO_SEG(0x00011800F00000A0ull))
#घोषणा CVMX_IOB_OUTB_FPA_PRI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000048ull))
#घोषणा CVMX_IOB_OUTB_REQ_PRI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000038ull))
#घोषणा CVMX_IOB_P2C_REQ_PRI_CNT (CVMX_ADD_IO_SEG(0x00011800F0000018ull))
#घोषणा CVMX_IOB_PKT_ERR (CVMX_ADD_IO_SEG(0x00011800F0000068ull))
#घोषणा CVMX_IOB_TO_CMB_CREDITS (CVMX_ADD_IO_SEG(0x00011800F00000B0ull))
#घोषणा CVMX_IOB_TO_NCB_DID_00_CREDITS (CVMX_ADD_IO_SEG(0x00011800F0000800ull))
#घोषणा CVMX_IOB_TO_NCB_DID_111_CREDITS (CVMX_ADD_IO_SEG(0x00011800F0000B78ull))
#घोषणा CVMX_IOB_TO_NCB_DID_223_CREDITS (CVMX_ADD_IO_SEG(0x00011800F0000EF8ull))
#घोषणा CVMX_IOB_TO_NCB_DID_24_CREDITS (CVMX_ADD_IO_SEG(0x00011800F00008C0ull))
#घोषणा CVMX_IOB_TO_NCB_DID_32_CREDITS (CVMX_ADD_IO_SEG(0x00011800F0000900ull))
#घोषणा CVMX_IOB_TO_NCB_DID_40_CREDITS (CVMX_ADD_IO_SEG(0x00011800F0000940ull))
#घोषणा CVMX_IOB_TO_NCB_DID_55_CREDITS (CVMX_ADD_IO_SEG(0x00011800F00009B8ull))
#घोषणा CVMX_IOB_TO_NCB_DID_64_CREDITS (CVMX_ADD_IO_SEG(0x00011800F0000A00ull))
#घोषणा CVMX_IOB_TO_NCB_DID_79_CREDITS (CVMX_ADD_IO_SEG(0x00011800F0000A78ull))
#घोषणा CVMX_IOB_TO_NCB_DID_96_CREDITS (CVMX_ADD_IO_SEG(0x00011800F0000B00ull))
#घोषणा CVMX_IOB_TO_NCB_DID_98_CREDITS (CVMX_ADD_IO_SEG(0x00011800F0000B10ull))

जोड़ cvmx_iob_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t ibd:1;
		uपूर्णांक64_t icd:1;
#अन्यथा
		uपूर्णांक64_t icd:1;
		uपूर्णांक64_t ibd:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_iob_bist_status_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t icnrcb:1;
		uपूर्णांक64_t icr0:1;
		uपूर्णांक64_t icr1:1;
		uपूर्णांक64_t icnr1:1;
		uपूर्णांक64_t icnr0:1;
		uपूर्णांक64_t ibdr0:1;
		uपूर्णांक64_t ibdr1:1;
		uपूर्णांक64_t ibr0:1;
		uपूर्णांक64_t ibr1:1;
		uपूर्णांक64_t icnrt:1;
		uपूर्णांक64_t ibrq0:1;
		uपूर्णांक64_t ibrq1:1;
		uपूर्णांक64_t icrn0:1;
		uपूर्णांक64_t icrn1:1;
		uपूर्णांक64_t icrp0:1;
		uपूर्णांक64_t icrp1:1;
		uपूर्णांक64_t ibd:1;
		uपूर्णांक64_t icd:1;
#अन्यथा
		uपूर्णांक64_t icd:1;
		uपूर्णांक64_t ibd:1;
		uपूर्णांक64_t icrp1:1;
		uपूर्णांक64_t icrp0:1;
		uपूर्णांक64_t icrn1:1;
		uपूर्णांक64_t icrn0:1;
		uपूर्णांक64_t ibrq1:1;
		uपूर्णांक64_t ibrq0:1;
		uपूर्णांक64_t icnrt:1;
		uपूर्णांक64_t ibr1:1;
		uपूर्णांक64_t ibr0:1;
		uपूर्णांक64_t ibdr1:1;
		uपूर्णांक64_t ibdr0:1;
		uपूर्णांक64_t icnr0:1;
		uपूर्णांक64_t icnr1:1;
		uपूर्णांक64_t icr1:1;
		uपूर्णांक64_t icr0:1;
		uपूर्णांक64_t icnrcb:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_iob_bist_status_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t xmdfअगर:1;
		uपूर्णांक64_t xmcfअगर:1;
		uपूर्णांक64_t iorfअगर:1;
		uपूर्णांक64_t rsdfअगर:1;
		uपूर्णांक64_t iocfअगर:1;
		uपूर्णांक64_t icnrcb:1;
		uपूर्णांक64_t icr0:1;
		uपूर्णांक64_t icr1:1;
		uपूर्णांक64_t icnr1:1;
		uपूर्णांक64_t icnr0:1;
		uपूर्णांक64_t ibdr0:1;
		uपूर्णांक64_t ibdr1:1;
		uपूर्णांक64_t ibr0:1;
		uपूर्णांक64_t ibr1:1;
		uपूर्णांक64_t icnrt:1;
		uपूर्णांक64_t ibrq0:1;
		uपूर्णांक64_t ibrq1:1;
		uपूर्णांक64_t icrn0:1;
		uपूर्णांक64_t icrn1:1;
		uपूर्णांक64_t icrp0:1;
		uपूर्णांक64_t icrp1:1;
		uपूर्णांक64_t ibd:1;
		uपूर्णांक64_t icd:1;
#अन्यथा
		uपूर्णांक64_t icd:1;
		uपूर्णांक64_t ibd:1;
		uपूर्णांक64_t icrp1:1;
		uपूर्णांक64_t icrp0:1;
		uपूर्णांक64_t icrn1:1;
		uपूर्णांक64_t icrn0:1;
		uपूर्णांक64_t ibrq1:1;
		uपूर्णांक64_t ibrq0:1;
		uपूर्णांक64_t icnrt:1;
		uपूर्णांक64_t ibr1:1;
		uपूर्णांक64_t ibr0:1;
		uपूर्णांक64_t ibdr1:1;
		uपूर्णांक64_t ibdr0:1;
		uपूर्णांक64_t icnr0:1;
		uपूर्णांक64_t icnr1:1;
		uपूर्णांक64_t icr1:1;
		uपूर्णांक64_t icr0:1;
		uपूर्णांक64_t icnrcb:1;
		uपूर्णांक64_t iocfअगर:1;
		uपूर्णांक64_t rsdfअगर:1;
		uपूर्णांक64_t iorfअगर:1;
		uपूर्णांक64_t xmcfअगर:1;
		uपूर्णांक64_t xmdfअगर:1;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_iob_bist_status_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t xmdfअगर:1;
		uपूर्णांक64_t xmcfअगर:1;
		uपूर्णांक64_t iorfअगर:1;
		uपूर्णांक64_t rsdfअगर:1;
		uपूर्णांक64_t iocfअगर:1;
		uपूर्णांक64_t icnrcb:1;
		uपूर्णांक64_t icr0:1;
		uपूर्णांक64_t icr1:1;
		uपूर्णांक64_t icnr0:1;
		uपूर्णांक64_t ibr0:1;
		uपूर्णांक64_t ibr1:1;
		uपूर्णांक64_t icnrt:1;
		uपूर्णांक64_t ibrq0:1;
		uपूर्णांक64_t ibrq1:1;
		uपूर्णांक64_t icrn0:1;
		uपूर्णांक64_t icrn1:1;
		uपूर्णांक64_t ibd:1;
		uपूर्णांक64_t icd:1;
#अन्यथा
		uपूर्णांक64_t icd:1;
		uपूर्णांक64_t ibd:1;
		uपूर्णांक64_t icrn1:1;
		uपूर्णांक64_t icrn0:1;
		uपूर्णांक64_t ibrq1:1;
		uपूर्णांक64_t ibrq0:1;
		uपूर्णांक64_t icnrt:1;
		uपूर्णांक64_t ibr1:1;
		uपूर्णांक64_t ibr0:1;
		uपूर्णांक64_t icnr0:1;
		uपूर्णांक64_t icr1:1;
		uपूर्णांक64_t icr0:1;
		uपूर्णांक64_t icnrcb:1;
		uपूर्णांक64_t iocfअगर:1;
		uपूर्णांक64_t rsdfअगर:1;
		uपूर्णांक64_t iorfअगर:1;
		uपूर्णांक64_t xmcfअगर:1;
		uपूर्णांक64_t xmdfअगर:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_iob_ctl_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_ctl_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t fअगर_dly:1;
		uपूर्णांक64_t xmc_per:4;
		uपूर्णांक64_t reserved_5_5:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t fau_end:1;
#अन्यथा
		uपूर्णांक64_t fau_end:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t reserved_5_5:1;
		uपूर्णांक64_t xmc_per:4;
		uपूर्णांक64_t fअगर_dly:1;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_iob_ctl_status_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t fau_end:1;
#अन्यथा
		uपूर्णांक64_t fau_end:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_iob_ctl_status_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t rr_mode:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t fau_end:1;
#अन्यथा
		uपूर्णांक64_t fau_end:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t rr_mode:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_iob_ctl_status_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t fअगर_dly:1;
		uपूर्णांक64_t xmc_per:4;
		uपूर्णांक64_t rr_mode:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t fau_end:1;
#अन्यथा
		uपूर्णांक64_t fau_end:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t rr_mode:1;
		uपूर्णांक64_t xmc_per:4;
		uपूर्णांक64_t fअगर_dly:1;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_iob_ctl_status_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t xmc_per:4;
		uपूर्णांक64_t rr_mode:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t fau_end:1;
#अन्यथा
		uपूर्णांक64_t fau_end:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t rr_mode:1;
		uपूर्णांक64_t xmc_per:4;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_iob_ctl_status_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t fअगर_dly:1;
		uपूर्णांक64_t xmc_per:4;
		uपूर्णांक64_t rsvr5:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t fau_end:1;
#अन्यथा
		uपूर्णांक64_t fau_end:1;
		uपूर्णांक64_t dwb_enb:1;
		uपूर्णांक64_t pko_enb:1;
		uपूर्णांक64_t inb_mat:1;
		uपूर्णांक64_t outb_mat:1;
		uपूर्णांक64_t rsvr5:1;
		uपूर्णांक64_t xmc_per:4;
		uपूर्णांक64_t fअगर_dly:1;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_iob_dwb_pri_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_dwb_pri_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t cnt_val:15;
#अन्यथा
		uपूर्णांक64_t cnt_val:15;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_fau_समयout अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_fau_समयout_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t tout_enb:1;
		uपूर्णांक64_t tout_val:12;
#अन्यथा
		uपूर्णांक64_t tout_val:12;
		uपूर्णांक64_t tout_enb:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_i2c_pri_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_i2c_pri_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t cnt_val:15;
#अन्यथा
		uपूर्णांक64_t cnt_val:15;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_inb_control_match अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_inb_control_match_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t opc:4;
		uपूर्णांक64_t dst:9;
		uपूर्णांक64_t src:8;
#अन्यथा
		uपूर्णांक64_t src:8;
		uपूर्णांक64_t dst:9;
		uपूर्णांक64_t opc:4;
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_inb_control_match_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_inb_control_match_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t opc:4;
		uपूर्णांक64_t dst:9;
		uपूर्णांक64_t src:8;
#अन्यथा
		uपूर्णांक64_t src:8;
		uपूर्णांक64_t dst:9;
		uपूर्णांक64_t opc:4;
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_inb_data_match अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_inb_data_match_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_inb_data_match_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_inb_data_match_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_पूर्णांक_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_पूर्णांक_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t p_dat:1;
		uपूर्णांक64_t np_dat:1;
		uपूर्णांक64_t p_eop:1;
		uपूर्णांक64_t p_sop:1;
		uपूर्णांक64_t np_eop:1;
		uपूर्णांक64_t np_sop:1;
#अन्यथा
		uपूर्णांक64_t np_sop:1;
		uपूर्णांक64_t np_eop:1;
		uपूर्णांक64_t p_sop:1;
		uपूर्णांक64_t p_eop:1;
		uपूर्णांक64_t np_dat:1;
		uपूर्णांक64_t p_dat:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_iob_पूर्णांक_enb_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t p_eop:1;
		uपूर्णांक64_t p_sop:1;
		uपूर्णांक64_t np_eop:1;
		uपूर्णांक64_t np_sop:1;
#अन्यथा
		uपूर्णांक64_t np_sop:1;
		uपूर्णांक64_t np_eop:1;
		uपूर्णांक64_t p_sop:1;
		uपूर्णांक64_t p_eop:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_iob_पूर्णांक_enb_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_iob_पूर्णांक_sum अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_पूर्णांक_sum_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t p_dat:1;
		uपूर्णांक64_t np_dat:1;
		uपूर्णांक64_t p_eop:1;
		uपूर्णांक64_t p_sop:1;
		uपूर्णांक64_t np_eop:1;
		uपूर्णांक64_t np_sop:1;
#अन्यथा
		uपूर्णांक64_t np_sop:1;
		uपूर्णांक64_t np_eop:1;
		uपूर्णांक64_t p_sop:1;
		uपूर्णांक64_t p_eop:1;
		uपूर्णांक64_t np_dat:1;
		uपूर्णांक64_t p_dat:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_iob_पूर्णांक_sum_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t p_eop:1;
		uपूर्णांक64_t p_sop:1;
		uपूर्णांक64_t np_eop:1;
		uपूर्णांक64_t np_sop:1;
#अन्यथा
		uपूर्णांक64_t np_sop:1;
		uपूर्णांक64_t np_eop:1;
		uपूर्णांक64_t p_sop:1;
		uपूर्णांक64_t p_eop:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_iob_पूर्णांक_sum_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_iob_n2c_l2c_pri_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_n2c_l2c_pri_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t cnt_val:15;
#अन्यथा
		uपूर्णांक64_t cnt_val:15;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_n2c_rsp_pri_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_n2c_rsp_pri_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t cnt_val:15;
#अन्यथा
		uपूर्णांक64_t cnt_val:15;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_outb_com_pri_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_outb_com_pri_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t cnt_val:15;
#अन्यथा
		uपूर्णांक64_t cnt_val:15;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_outb_control_match अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_outb_control_match_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_26_63:38;
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t eot:1;
		uपूर्णांक64_t dst:8;
		uपूर्णांक64_t src:9;
#अन्यथा
		uपूर्णांक64_t src:9;
		uपूर्णांक64_t dst:8;
		uपूर्णांक64_t eot:1;
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t reserved_26_63:38;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_outb_control_match_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_outb_control_match_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_26_63:38;
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t eot:1;
		uपूर्णांक64_t dst:8;
		uपूर्णांक64_t src:9;
#अन्यथा
		uपूर्णांक64_t src:9;
		uपूर्णांक64_t dst:8;
		uपूर्णांक64_t eot:1;
		uपूर्णांक64_t mask:8;
		uपूर्णांक64_t reserved_26_63:38;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_outb_data_match अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_outb_data_match_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_outb_data_match_enb अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_outb_data_match_enb_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_outb_fpa_pri_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_outb_fpa_pri_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t cnt_val:15;
#अन्यथा
		uपूर्णांक64_t cnt_val:15;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_outb_req_pri_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_outb_req_pri_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t cnt_val:15;
#अन्यथा
		uपूर्णांक64_t cnt_val:15;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_p2c_req_pri_cnt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_p2c_req_pri_cnt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t cnt_val:15;
#अन्यथा
		uपूर्णांक64_t cnt_val:15;
		uपूर्णांक64_t cnt_enb:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_pkt_err अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_pkt_err_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t vport:6;
		uपूर्णांक64_t port:6;
#अन्यथा
		uपूर्णांक64_t port:6;
		uपूर्णांक64_t vport:6;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_iob_pkt_err_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t port:6;
#अन्यथा
		uपूर्णांक64_t port:6;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_iob_to_cmb_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_cmb_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t ncb_rd:3;
		uपूर्णांक64_t ncb_wr:3;
#अन्यथा
		uपूर्णांक64_t ncb_wr:3;
		uपूर्णांक64_t ncb_rd:3;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_iob_to_cmb_credits_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t pko_rd:3;
		uपूर्णांक64_t ncb_rd:3;
		uपूर्णांक64_t ncb_wr:3;
#अन्यथा
		uपूर्णांक64_t ncb_wr:3;
		uपूर्णांक64_t ncb_rd:3;
		uपूर्णांक64_t pko_rd:3;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_iob_to_cmb_credits_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t dwb:3;
		uपूर्णांक64_t ncb_rd:3;
		uपूर्णांक64_t ncb_wr:3;
#अन्यथा
		uपूर्णांक64_t ncb_wr:3;
		uपूर्णांक64_t ncb_rd:3;
		uपूर्णांक64_t dwb:3;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_00_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_00_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_111_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_111_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_223_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_223_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_24_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_24_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_32_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_32_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_40_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_40_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_55_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_55_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_64_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_64_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_79_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_79_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_96_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_96_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_iob_to_ncb_did_98_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_iob_to_ncb_did_98_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t crd:7;
#अन्यथा
		uपूर्णांक64_t crd:7;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
