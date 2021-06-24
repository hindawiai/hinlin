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

#अगर_अघोषित __CVMX_SRIOX_DEFS_H__
#घोषणा __CVMX_SRIOX_DEFS_H__

#घोषणा CVMX_SRIOX_ACC_CTRL(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000148ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_ASMBLY_ID(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000200ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_ASMBLY_INFO(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000208ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_BELL_RESP_CTRL(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000310ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_BIST_STATUS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000108ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_IMSG_CTRL(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000508ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_IMSG_INST_HDRX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000510ull) + (((offset) & 1) + ((block_id) & 3) * 0x200000ull) * 8)
#घोषणा CVMX_SRIOX_IMSG_QOS_GRPX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000600ull) + (((offset) & 31) + ((block_id) & 3) * 0x200000ull) * 8)
#घोषणा CVMX_SRIOX_IMSG_STATUSX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000700ull) + (((offset) & 31) + ((block_id) & 3) * 0x200000ull) * 8)
#घोषणा CVMX_SRIOX_IMSG_VPORT_THR(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000500ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_IMSG_VPORT_THR2(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000528ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_INT2_ENABLE(block_id) (CVMX_ADD_IO_SEG(0x00011800C80003E0ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_INT2_REG(block_id) (CVMX_ADD_IO_SEG(0x00011800C80003E8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_INT_ENABLE(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000110ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_INT_INFO0(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000120ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_INT_INFO1(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000128ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_INT_INFO2(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000130ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_INT_INFO3(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000138ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_INT_REG(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000118ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_IP_FEATURE(block_id) (CVMX_ADD_IO_SEG(0x00011800C80003F8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_MAC_BUFFERS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000390ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_MAINT_OP(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000158ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_MAINT_RD_DATA(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000160ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_MCE_TX_CTL(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000240ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_MEM_OP_CTRL(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000168ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_OMSG_CTRLX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000488ull) + (((offset) & 1) + ((block_id) & 3) * 0x40000ull) * 64)
#घोषणा CVMX_SRIOX_OMSG_DONE_COUNTSX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C80004B0ull) + (((offset) & 1) + ((block_id) & 3) * 0x40000ull) * 64)
#घोषणा CVMX_SRIOX_OMSG_FMP_MRX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000498ull) + (((offset) & 1) + ((block_id) & 3) * 0x40000ull) * 64)
#घोषणा CVMX_SRIOX_OMSG_NMP_MRX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C80004A0ull) + (((offset) & 1) + ((block_id) & 3) * 0x40000ull) * 64)
#घोषणा CVMX_SRIOX_OMSG_PORTX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000480ull) + (((offset) & 1) + ((block_id) & 3) * 0x40000ull) * 64)
#घोषणा CVMX_SRIOX_OMSG_SILO_THR(block_id) (CVMX_ADD_IO_SEG(0x00011800C80004F8ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_OMSG_SP_MRX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000490ull) + (((offset) & 1) + ((block_id) & 3) * 0x40000ull) * 64)
#घोषणा CVMX_SRIOX_PRIOX_IN_USE(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C80003C0ull) + (((offset) & 3) + ((block_id) & 3) * 0x200000ull) * 8)
#घोषणा CVMX_SRIOX_RX_BELL(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000308ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_RX_BELL_SEQ(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000300ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_RX_STATUS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000380ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_S2M_TYPEX(offset, block_id) (CVMX_ADD_IO_SEG(0x00011800C8000180ull) + (((offset) & 15) + ((block_id) & 3) * 0x200000ull) * 8)
#घोषणा CVMX_SRIOX_SEQ(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000278ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_STATUS_REG(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000100ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_TAG_CTRL(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000178ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_TLP_CREDITS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000150ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_TX_BELL(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000280ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_TX_BELL_INFO(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000288ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_TX_CTRL(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000170ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_TX_EMPHASIS(block_id) (CVMX_ADD_IO_SEG(0x00011800C80003F0ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_TX_STATUS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000388ull) + ((block_id) & 3) * 0x1000000ull)
#घोषणा CVMX_SRIOX_WR_DONE_COUNTS(block_id) (CVMX_ADD_IO_SEG(0x00011800C8000340ull) + ((block_id) & 3) * 0x1000000ull)

जोड़ cvmx_sriox_acc_ctrl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_acc_ctrl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t deny_adr2:1;
		uपूर्णांक64_t deny_adr1:1;
		uपूर्णांक64_t deny_adr0:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t deny_bar2:1;
		uपूर्णांक64_t deny_bar1:1;
		uपूर्णांक64_t deny_bar0:1;
#अन्यथा
		uपूर्णांक64_t deny_bar0:1;
		uपूर्णांक64_t deny_bar1:1;
		uपूर्णांक64_t deny_bar2:1;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t deny_adr0:1;
		uपूर्णांक64_t deny_adr1:1;
		uपूर्णांक64_t deny_adr2:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_sriox_acc_ctrl_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t deny_bar2:1;
		uपूर्णांक64_t deny_bar1:1;
		uपूर्णांक64_t deny_bar0:1;
#अन्यथा
		uपूर्णांक64_t deny_bar0:1;
		uपूर्णांक64_t deny_bar1:1;
		uपूर्णांक64_t deny_bar2:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_sriox_यंत्रbly_id अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_यंत्रbly_id_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t assy_id:16;
		uपूर्णांक64_t assy_ven:16;
#अन्यथा
		uपूर्णांक64_t assy_ven:16;
		uपूर्णांक64_t assy_id:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_यंत्रbly_info अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_यंत्रbly_info_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t assy_rev:16;
		uपूर्णांक64_t reserved_0_15:16;
#अन्यथा
		uपूर्णांक64_t reserved_0_15:16;
		uपूर्णांक64_t assy_rev:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_bell_resp_ctrl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_bell_resp_ctrl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t rp1_sid:1;
		uपूर्णांक64_t rp0_sid:2;
		uपूर्णांक64_t rp1_pid:1;
		uपूर्णांक64_t rp0_pid:2;
#अन्यथा
		uपूर्णांक64_t rp0_pid:2;
		uपूर्णांक64_t rp1_pid:1;
		uपूर्णांक64_t rp0_sid:2;
		uपूर्णांक64_t rp1_sid:1;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_45_63:19;
		uपूर्णांक64_t lram:1;
		uपूर्णांक64_t mram:2;
		uपूर्णांक64_t cram:2;
		uपूर्णांक64_t bell:2;
		uपूर्णांक64_t otag:2;
		uपूर्णांक64_t itag:1;
		uपूर्णांक64_t oमुक्त:1;
		uपूर्णांक64_t rtn:2;
		uपूर्णांक64_t obulk:4;
		uपूर्णांक64_t optrs:4;
		uपूर्णांक64_t oarb2:2;
		uपूर्णांक64_t rxbuf2:2;
		uपूर्णांक64_t oarb:2;
		uपूर्णांक64_t ispf:1;
		uपूर्णांक64_t ospf:1;
		uपूर्णांक64_t txbuf:2;
		uपूर्णांक64_t rxbuf:2;
		uपूर्णांक64_t imsg:5;
		uपूर्णांक64_t omsg:7;
#अन्यथा
		uपूर्णांक64_t omsg:7;
		uपूर्णांक64_t imsg:5;
		uपूर्णांक64_t rxbuf:2;
		uपूर्णांक64_t txbuf:2;
		uपूर्णांक64_t ospf:1;
		uपूर्णांक64_t ispf:1;
		uपूर्णांक64_t oarb:2;
		uपूर्णांक64_t rxbuf2:2;
		uपूर्णांक64_t oarb2:2;
		uपूर्णांक64_t optrs:4;
		uपूर्णांक64_t obulk:4;
		uपूर्णांक64_t rtn:2;
		uपूर्णांक64_t oमुक्त:1;
		uपूर्णांक64_t itag:1;
		uपूर्णांक64_t otag:2;
		uपूर्णांक64_t bell:2;
		uपूर्णांक64_t cram:2;
		uपूर्णांक64_t mram:2;
		uपूर्णांक64_t lram:1;
		uपूर्णांक64_t reserved_45_63:19;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_sriox_bist_status_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t mram:2;
		uपूर्णांक64_t cram:2;
		uपूर्णांक64_t bell:2;
		uपूर्णांक64_t otag:2;
		uपूर्णांक64_t itag:1;
		uपूर्णांक64_t oमुक्त:1;
		uपूर्णांक64_t rtn:2;
		uपूर्णांक64_t obulk:4;
		uपूर्णांक64_t optrs:4;
		uपूर्णांक64_t oarb2:2;
		uपूर्णांक64_t rxbuf2:2;
		uपूर्णांक64_t oarb:2;
		uपूर्णांक64_t ispf:1;
		uपूर्णांक64_t ospf:1;
		uपूर्णांक64_t txbuf:2;
		uपूर्णांक64_t rxbuf:2;
		uपूर्णांक64_t imsg:5;
		uपूर्णांक64_t omsg:7;
#अन्यथा
		uपूर्णांक64_t omsg:7;
		uपूर्णांक64_t imsg:5;
		uपूर्णांक64_t rxbuf:2;
		uपूर्णांक64_t txbuf:2;
		uपूर्णांक64_t ospf:1;
		uपूर्णांक64_t ispf:1;
		uपूर्णांक64_t oarb:2;
		uपूर्णांक64_t rxbuf2:2;
		uपूर्णांक64_t oarb2:2;
		uपूर्णांक64_t optrs:4;
		uपूर्णांक64_t obulk:4;
		uपूर्णांक64_t rtn:2;
		uपूर्णांक64_t oमुक्त:1;
		uपूर्णांक64_t itag:1;
		uपूर्णांक64_t otag:2;
		uपूर्णांक64_t bell:2;
		uपूर्णांक64_t cram:2;
		uपूर्णांक64_t mram:2;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण cn63xx;
	काष्ठा cvmx_sriox_bist_status_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_44_63:20;
		uपूर्णांक64_t mram:2;
		uपूर्णांक64_t cram:2;
		uपूर्णांक64_t bell:2;
		uपूर्णांक64_t otag:2;
		uपूर्णांक64_t itag:1;
		uपूर्णांक64_t oमुक्त:1;
		uपूर्णांक64_t rtn:2;
		uपूर्णांक64_t obulk:4;
		uपूर्णांक64_t optrs:4;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t oarb:2;
		uपूर्णांक64_t ispf:1;
		uपूर्णांक64_t ospf:1;
		uपूर्णांक64_t txbuf:2;
		uपूर्णांक64_t rxbuf:2;
		uपूर्णांक64_t imsg:5;
		uपूर्णांक64_t omsg:7;
#अन्यथा
		uपूर्णांक64_t omsg:7;
		uपूर्णांक64_t imsg:5;
		uपूर्णांक64_t rxbuf:2;
		uपूर्णांक64_t txbuf:2;
		uपूर्णांक64_t ospf:1;
		uपूर्णांक64_t ispf:1;
		uपूर्णांक64_t oarb:2;
		uपूर्णांक64_t reserved_20_23:4;
		uपूर्णांक64_t optrs:4;
		uपूर्णांक64_t obulk:4;
		uपूर्णांक64_t rtn:2;
		uपूर्णांक64_t oमुक्त:1;
		uपूर्णांक64_t itag:1;
		uपूर्णांक64_t otag:2;
		uपूर्णांक64_t bell:2;
		uपूर्णांक64_t cram:2;
		uपूर्णांक64_t mram:2;
		uपूर्णांक64_t reserved_44_63:20;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_sriox_imsg_ctrl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_imsg_ctrl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t to_mode:1;
		uपूर्णांक64_t reserved_30_30:1;
		uपूर्णांक64_t rsp_thr:6;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t rp1_sid:1;
		uपूर्णांक64_t rp0_sid:2;
		uपूर्णांक64_t rp1_pid:1;
		uपूर्णांक64_t rp0_pid:2;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t prt_sel:3;
		uपूर्णांक64_t lttr:4;
		uपूर्णांक64_t prio:4;
		uपूर्णांक64_t mbox:4;
#अन्यथा
		uपूर्णांक64_t mbox:4;
		uपूर्णांक64_t prio:4;
		uपूर्णांक64_t lttr:4;
		uपूर्णांक64_t prt_sel:3;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t rp0_pid:2;
		uपूर्णांक64_t rp1_pid:1;
		uपूर्णांक64_t rp0_sid:2;
		uपूर्णांक64_t rp1_sid:1;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t rsp_thr:6;
		uपूर्णांक64_t reserved_30_30:1;
		uपूर्णांक64_t to_mode:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_imsg_inst_hdrx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_imsg_inst_hdrx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t r:1;
		uपूर्णांक64_t reserved_58_62:5;
		uपूर्णांक64_t pm:2;
		uपूर्णांक64_t reserved_55_55:1;
		uपूर्णांक64_t sl:7;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t nqos:1;
		uपूर्णांक64_t ngrp:1;
		uपूर्णांक64_t ntt:1;
		uपूर्णांक64_t ntag:1;
		uपूर्णांक64_t reserved_35_41:7;
		uपूर्णांक64_t rs:1;
		uपूर्णांक64_t tt:2;
		uपूर्णांक64_t tag:32;
#अन्यथा
		uपूर्णांक64_t tag:32;
		uपूर्णांक64_t tt:2;
		uपूर्णांक64_t rs:1;
		uपूर्णांक64_t reserved_35_41:7;
		uपूर्णांक64_t ntag:1;
		uपूर्णांक64_t ntt:1;
		uपूर्णांक64_t ngrp:1;
		uपूर्णांक64_t nqos:1;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t sl:7;
		uपूर्णांक64_t reserved_55_55:1;
		uपूर्णांक64_t pm:2;
		uपूर्णांक64_t reserved_58_62:5;
		uपूर्णांक64_t r:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_imsg_qos_grpx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_imsg_qos_grpx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_63_63:1;
		uपूर्णांक64_t qos7:3;
		uपूर्णांक64_t grp7:4;
		uपूर्णांक64_t reserved_55_55:1;
		uपूर्णांक64_t qos6:3;
		uपूर्णांक64_t grp6:4;
		uपूर्णांक64_t reserved_47_47:1;
		uपूर्णांक64_t qos5:3;
		uपूर्णांक64_t grp5:4;
		uपूर्णांक64_t reserved_39_39:1;
		uपूर्णांक64_t qos4:3;
		uपूर्णांक64_t grp4:4;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t qos3:3;
		uपूर्णांक64_t grp3:4;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t qos2:3;
		uपूर्णांक64_t grp2:4;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t qos1:3;
		uपूर्णांक64_t grp1:4;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t qos0:3;
		uपूर्णांक64_t grp0:4;
#अन्यथा
		uपूर्णांक64_t grp0:4;
		uपूर्णांक64_t qos0:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t grp1:4;
		uपूर्णांक64_t qos1:3;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t grp2:4;
		uपूर्णांक64_t qos2:3;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t grp3:4;
		uपूर्णांक64_t qos3:3;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t grp4:4;
		uपूर्णांक64_t qos4:3;
		uपूर्णांक64_t reserved_39_39:1;
		uपूर्णांक64_t grp5:4;
		uपूर्णांक64_t qos5:3;
		uपूर्णांक64_t reserved_47_47:1;
		uपूर्णांक64_t grp6:4;
		uपूर्णांक64_t qos6:3;
		uपूर्णांक64_t reserved_55_55:1;
		uपूर्णांक64_t grp7:4;
		uपूर्णांक64_t qos7:3;
		uपूर्णांक64_t reserved_63_63:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_imsg_statusx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_imsg_statusx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t val1:1;
		uपूर्णांक64_t err1:1;
		uपूर्णांक64_t toe1:1;
		uपूर्णांक64_t toc1:1;
		uपूर्णांक64_t prt1:1;
		uपूर्णांक64_t reserved_58_58:1;
		uपूर्णांक64_t tt1:1;
		uपूर्णांक64_t dis1:1;
		uपूर्णांक64_t seg1:4;
		uपूर्णांक64_t mbox1:2;
		uपूर्णांक64_t lttr1:2;
		uपूर्णांक64_t sid1:16;
		uपूर्णांक64_t val0:1;
		uपूर्णांक64_t err0:1;
		uपूर्णांक64_t toe0:1;
		uपूर्णांक64_t toc0:1;
		uपूर्णांक64_t prt0:1;
		uपूर्णांक64_t reserved_26_26:1;
		uपूर्णांक64_t tt0:1;
		uपूर्णांक64_t dis0:1;
		uपूर्णांक64_t seg0:4;
		uपूर्णांक64_t mbox0:2;
		uपूर्णांक64_t lttr0:2;
		uपूर्णांक64_t sid0:16;
#अन्यथा
		uपूर्णांक64_t sid0:16;
		uपूर्णांक64_t lttr0:2;
		uपूर्णांक64_t mbox0:2;
		uपूर्णांक64_t seg0:4;
		uपूर्णांक64_t dis0:1;
		uपूर्णांक64_t tt0:1;
		uपूर्णांक64_t reserved_26_26:1;
		uपूर्णांक64_t prt0:1;
		uपूर्णांक64_t toc0:1;
		uपूर्णांक64_t toe0:1;
		uपूर्णांक64_t err0:1;
		uपूर्णांक64_t val0:1;
		uपूर्णांक64_t sid1:16;
		uपूर्णांक64_t lttr1:2;
		uपूर्णांक64_t mbox1:2;
		uपूर्णांक64_t seg1:4;
		uपूर्णांक64_t dis1:1;
		uपूर्णांक64_t tt1:1;
		uपूर्णांक64_t reserved_58_58:1;
		uपूर्णांक64_t prt1:1;
		uपूर्णांक64_t toc1:1;
		uपूर्णांक64_t toe1:1;
		uपूर्णांक64_t err1:1;
		uपूर्णांक64_t val1:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_imsg_vport_thr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_imsg_vport_thr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_54_63:10;
		uपूर्णांक64_t max_tot:6;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t max_s1:6;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t max_s0:6;
		uपूर्णांक64_t sp_vport:1;
		uपूर्णांक64_t reserved_20_30:11;
		uपूर्णांक64_t buf_thr:4;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t max_p1:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t max_p0:6;
#अन्यथा
		uपूर्णांक64_t max_p0:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t max_p1:6;
		uपूर्णांक64_t reserved_14_15:2;
		uपूर्णांक64_t buf_thr:4;
		uपूर्णांक64_t reserved_20_30:11;
		uपूर्णांक64_t sp_vport:1;
		uपूर्णांक64_t max_s0:6;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t max_s1:6;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t max_tot:6;
		uपूर्णांक64_t reserved_54_63:10;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_imsg_vport_thr2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_imsg_vport_thr2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_46_63:18;
		uपूर्णांक64_t max_s3:6;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t max_s2:6;
		uपूर्णांक64_t reserved_0_31:32;
#अन्यथा
		uपूर्णांक64_t reserved_0_31:32;
		uपूर्णांक64_t max_s2:6;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t max_s3:6;
		uपूर्णांक64_t reserved_46_63:18;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_पूर्णांक2_enable अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_पूर्णांक2_enable_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t pko_rst:1;
#अन्यथा
		uपूर्णांक64_t pko_rst:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_पूर्णांक2_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_पूर्णांक2_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t पूर्णांक_sum:1;
		uपूर्णांक64_t reserved_1_30:30;
		uपूर्णांक64_t pko_rst:1;
#अन्यथा
		uपूर्णांक64_t pko_rst:1;
		uपूर्णांक64_t reserved_1_30:30;
		uपूर्णांक64_t पूर्णांक_sum:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_पूर्णांक_enable अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_पूर्णांक_enable_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_27_63:37;
		uपूर्णांक64_t zero_pkt:1;
		uपूर्णांक64_t ttl_tout:1;
		uपूर्णांक64_t fail:1;
		uपूर्णांक64_t degrade:1;
		uपूर्णांक64_t mac_buf:1;
		uपूर्णांक64_t f_error:1;
		uपूर्णांक64_t rtry_err:1;
		uपूर्णांक64_t pko_err:1;
		uपूर्णांक64_t omsg_err:1;
		uपूर्णांक64_t omsg1:1;
		uपूर्णांक64_t omsg0:1;
		uपूर्णांक64_t link_up:1;
		uपूर्णांक64_t link_dwn:1;
		uपूर्णांक64_t phy_erb:1;
		uपूर्णांक64_t log_erb:1;
		uपूर्णांक64_t soft_rx:1;
		uपूर्णांक64_t soft_tx:1;
		uपूर्णांक64_t mce_rx:1;
		uपूर्णांक64_t mce_tx:1;
		uपूर्णांक64_t wr_करोne:1;
		uपूर्णांक64_t sli_err:1;
		uपूर्णांक64_t deny_wr:1;
		uपूर्णांक64_t bar_err:1;
		uपूर्णांक64_t मुख्यt_op:1;
		uपूर्णांक64_t rxbell:1;
		uपूर्णांक64_t bell_err:1;
		uपूर्णांक64_t txbell:1;
#अन्यथा
		uपूर्णांक64_t txbell:1;
		uपूर्णांक64_t bell_err:1;
		uपूर्णांक64_t rxbell:1;
		uपूर्णांक64_t मुख्यt_op:1;
		uपूर्णांक64_t bar_err:1;
		uपूर्णांक64_t deny_wr:1;
		uपूर्णांक64_t sli_err:1;
		uपूर्णांक64_t wr_करोne:1;
		uपूर्णांक64_t mce_tx:1;
		uपूर्णांक64_t mce_rx:1;
		uपूर्णांक64_t soft_tx:1;
		uपूर्णांक64_t soft_rx:1;
		uपूर्णांक64_t log_erb:1;
		uपूर्णांक64_t phy_erb:1;
		uपूर्णांक64_t link_dwn:1;
		uपूर्णांक64_t link_up:1;
		uपूर्णांक64_t omsg0:1;
		uपूर्णांक64_t omsg1:1;
		uपूर्णांक64_t omsg_err:1;
		uपूर्णांक64_t pko_err:1;
		uपूर्णांक64_t rtry_err:1;
		uपूर्णांक64_t f_error:1;
		uपूर्णांक64_t mac_buf:1;
		uपूर्णांक64_t degrade:1;
		uपूर्णांक64_t fail:1;
		uपूर्णांक64_t ttl_tout:1;
		uपूर्णांक64_t zero_pkt:1;
		uपूर्णांक64_t reserved_27_63:37;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_sriox_पूर्णांक_enable_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t f_error:1;
		uपूर्णांक64_t rtry_err:1;
		uपूर्णांक64_t pko_err:1;
		uपूर्णांक64_t omsg_err:1;
		uपूर्णांक64_t omsg1:1;
		uपूर्णांक64_t omsg0:1;
		uपूर्णांक64_t link_up:1;
		uपूर्णांक64_t link_dwn:1;
		uपूर्णांक64_t phy_erb:1;
		uपूर्णांक64_t log_erb:1;
		uपूर्णांक64_t soft_rx:1;
		uपूर्णांक64_t soft_tx:1;
		uपूर्णांक64_t mce_rx:1;
		uपूर्णांक64_t mce_tx:1;
		uपूर्णांक64_t wr_करोne:1;
		uपूर्णांक64_t sli_err:1;
		uपूर्णांक64_t deny_wr:1;
		uपूर्णांक64_t bar_err:1;
		uपूर्णांक64_t मुख्यt_op:1;
		uपूर्णांक64_t rxbell:1;
		uपूर्णांक64_t bell_err:1;
		uपूर्णांक64_t txbell:1;
#अन्यथा
		uपूर्णांक64_t txbell:1;
		uपूर्णांक64_t bell_err:1;
		uपूर्णांक64_t rxbell:1;
		uपूर्णांक64_t मुख्यt_op:1;
		uपूर्णांक64_t bar_err:1;
		uपूर्णांक64_t deny_wr:1;
		uपूर्णांक64_t sli_err:1;
		uपूर्णांक64_t wr_करोne:1;
		uपूर्णांक64_t mce_tx:1;
		uपूर्णांक64_t mce_rx:1;
		uपूर्णांक64_t soft_tx:1;
		uपूर्णांक64_t soft_rx:1;
		uपूर्णांक64_t log_erb:1;
		uपूर्णांक64_t phy_erb:1;
		uपूर्णांक64_t link_dwn:1;
		uपूर्णांक64_t link_up:1;
		uपूर्णांक64_t omsg0:1;
		uपूर्णांक64_t omsg1:1;
		uपूर्णांक64_t omsg_err:1;
		uपूर्णांक64_t pko_err:1;
		uपूर्णांक64_t rtry_err:1;
		uपूर्णांक64_t f_error:1;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_sriox_पूर्णांक_info0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_पूर्णांक_info0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t cmd:4;
		uपूर्णांक64_t type:4;
		uपूर्णांक64_t tag:8;
		uपूर्णांक64_t reserved_42_47:6;
		uपूर्णांक64_t length:10;
		uपूर्णांक64_t status:3;
		uपूर्णांक64_t reserved_16_28:13;
		uपूर्णांक64_t be0:8;
		uपूर्णांक64_t be1:8;
#अन्यथा
		uपूर्णांक64_t be1:8;
		uपूर्णांक64_t be0:8;
		uपूर्णांक64_t reserved_16_28:13;
		uपूर्णांक64_t status:3;
		uपूर्णांक64_t length:10;
		uपूर्णांक64_t reserved_42_47:6;
		uपूर्णांक64_t tag:8;
		uपूर्णांक64_t type:4;
		uपूर्णांक64_t cmd:4;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_पूर्णांक_info1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_पूर्णांक_info1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t info1:64;
#अन्यथा
		uपूर्णांक64_t info1:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_पूर्णांक_info2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_पूर्णांक_info2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t prio:2;
		uपूर्णांक64_t tt:1;
		uपूर्णांक64_t sis:1;
		uपूर्णांक64_t ssize:4;
		uपूर्णांक64_t did:16;
		uपूर्णांक64_t xmbox:4;
		uपूर्णांक64_t mbox:2;
		uपूर्णांक64_t letter:2;
		uपूर्णांक64_t rsrvd:30;
		uपूर्णांक64_t lns:1;
		uपूर्णांक64_t पूर्णांकr:1;
#अन्यथा
		uपूर्णांक64_t पूर्णांकr:1;
		uपूर्णांक64_t lns:1;
		uपूर्णांक64_t rsrvd:30;
		uपूर्णांक64_t letter:2;
		uपूर्णांक64_t mbox:2;
		uपूर्णांक64_t xmbox:4;
		uपूर्णांक64_t did:16;
		uपूर्णांक64_t ssize:4;
		uपूर्णांक64_t sis:1;
		uपूर्णांक64_t tt:1;
		uपूर्णांक64_t prio:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_पूर्णांक_info3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_पूर्णांक_info3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t prio:2;
		uपूर्णांक64_t tt:2;
		uपूर्णांक64_t type:4;
		uपूर्णांक64_t other:48;
		uपूर्णांक64_t reserved_0_7:8;
#अन्यथा
		uपूर्णांक64_t reserved_0_7:8;
		uपूर्णांक64_t other:48;
		uपूर्णांक64_t type:4;
		uपूर्णांक64_t tt:2;
		uपूर्णांक64_t prio:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t पूर्णांक2_sum:1;
		uपूर्णांक64_t reserved_27_30:4;
		uपूर्णांक64_t zero_pkt:1;
		uपूर्णांक64_t ttl_tout:1;
		uपूर्णांक64_t fail:1;
		uपूर्णांक64_t degrad:1;
		uपूर्णांक64_t mac_buf:1;
		uपूर्णांक64_t f_error:1;
		uपूर्णांक64_t rtry_err:1;
		uपूर्णांक64_t pko_err:1;
		uपूर्णांक64_t omsg_err:1;
		uपूर्णांक64_t omsg1:1;
		uपूर्णांक64_t omsg0:1;
		uपूर्णांक64_t link_up:1;
		uपूर्णांक64_t link_dwn:1;
		uपूर्णांक64_t phy_erb:1;
		uपूर्णांक64_t log_erb:1;
		uपूर्णांक64_t soft_rx:1;
		uपूर्णांक64_t soft_tx:1;
		uपूर्णांक64_t mce_rx:1;
		uपूर्णांक64_t mce_tx:1;
		uपूर्णांक64_t wr_करोne:1;
		uपूर्णांक64_t sli_err:1;
		uपूर्णांक64_t deny_wr:1;
		uपूर्णांक64_t bar_err:1;
		uपूर्णांक64_t मुख्यt_op:1;
		uपूर्णांक64_t rxbell:1;
		uपूर्णांक64_t bell_err:1;
		uपूर्णांक64_t txbell:1;
#अन्यथा
		uपूर्णांक64_t txbell:1;
		uपूर्णांक64_t bell_err:1;
		uपूर्णांक64_t rxbell:1;
		uपूर्णांक64_t मुख्यt_op:1;
		uपूर्णांक64_t bar_err:1;
		uपूर्णांक64_t deny_wr:1;
		uपूर्णांक64_t sli_err:1;
		uपूर्णांक64_t wr_करोne:1;
		uपूर्णांक64_t mce_tx:1;
		uपूर्णांक64_t mce_rx:1;
		uपूर्णांक64_t soft_tx:1;
		uपूर्णांक64_t soft_rx:1;
		uपूर्णांक64_t log_erb:1;
		uपूर्णांक64_t phy_erb:1;
		uपूर्णांक64_t link_dwn:1;
		uपूर्णांक64_t link_up:1;
		uपूर्णांक64_t omsg0:1;
		uपूर्णांक64_t omsg1:1;
		uपूर्णांक64_t omsg_err:1;
		uपूर्णांक64_t pko_err:1;
		uपूर्णांक64_t rtry_err:1;
		uपूर्णांक64_t f_error:1;
		uपूर्णांक64_t mac_buf:1;
		uपूर्णांक64_t degrad:1;
		uपूर्णांक64_t fail:1;
		uपूर्णांक64_t ttl_tout:1;
		uपूर्णांक64_t zero_pkt:1;
		uपूर्णांक64_t reserved_27_30:4;
		uपूर्णांक64_t पूर्णांक2_sum:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_sriox_पूर्णांक_reg_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t f_error:1;
		uपूर्णांक64_t rtry_err:1;
		uपूर्णांक64_t pko_err:1;
		uपूर्णांक64_t omsg_err:1;
		uपूर्णांक64_t omsg1:1;
		uपूर्णांक64_t omsg0:1;
		uपूर्णांक64_t link_up:1;
		uपूर्णांक64_t link_dwn:1;
		uपूर्णांक64_t phy_erb:1;
		uपूर्णांक64_t log_erb:1;
		uपूर्णांक64_t soft_rx:1;
		uपूर्णांक64_t soft_tx:1;
		uपूर्णांक64_t mce_rx:1;
		uपूर्णांक64_t mce_tx:1;
		uपूर्णांक64_t wr_करोne:1;
		uपूर्णांक64_t sli_err:1;
		uपूर्णांक64_t deny_wr:1;
		uपूर्णांक64_t bar_err:1;
		uपूर्णांक64_t मुख्यt_op:1;
		uपूर्णांक64_t rxbell:1;
		uपूर्णांक64_t bell_err:1;
		uपूर्णांक64_t txbell:1;
#अन्यथा
		uपूर्णांक64_t txbell:1;
		uपूर्णांक64_t bell_err:1;
		uपूर्णांक64_t rxbell:1;
		uपूर्णांक64_t मुख्यt_op:1;
		uपूर्णांक64_t bar_err:1;
		uपूर्णांक64_t deny_wr:1;
		uपूर्णांक64_t sli_err:1;
		uपूर्णांक64_t wr_करोne:1;
		uपूर्णांक64_t mce_tx:1;
		uपूर्णांक64_t mce_rx:1;
		uपूर्णांक64_t soft_tx:1;
		uपूर्णांक64_t soft_rx:1;
		uपूर्णांक64_t log_erb:1;
		uपूर्णांक64_t phy_erb:1;
		uपूर्णांक64_t link_dwn:1;
		uपूर्णांक64_t link_up:1;
		uपूर्णांक64_t omsg0:1;
		uपूर्णांक64_t omsg1:1;
		uपूर्णांक64_t omsg_err:1;
		uपूर्णांक64_t pko_err:1;
		uपूर्णांक64_t rtry_err:1;
		uपूर्णांक64_t f_error:1;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_sriox_ip_feature अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_ip_feature_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t ops:32;
		uपूर्णांक64_t reserved_15_31:17;
		uपूर्णांक64_t no_vmin:1;
		uपूर्णांक64_t a66:1;
		uपूर्णांक64_t a50:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t tx_flow:1;
		uपूर्णांक64_t pt_width:2;
		uपूर्णांक64_t tx_pol:4;
		uपूर्णांक64_t rx_pol:4;
#अन्यथा
		uपूर्णांक64_t rx_pol:4;
		uपूर्णांक64_t tx_pol:4;
		uपूर्णांक64_t pt_width:2;
		uपूर्णांक64_t tx_flow:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t a50:1;
		uपूर्णांक64_t a66:1;
		uपूर्णांक64_t no_vmin:1;
		uपूर्णांक64_t reserved_15_31:17;
		uपूर्णांक64_t ops:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_sriox_ip_feature_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t ops:32;
		uपूर्णांक64_t reserved_14_31:18;
		uपूर्णांक64_t a66:1;
		uपूर्णांक64_t a50:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t tx_flow:1;
		uपूर्णांक64_t pt_width:2;
		uपूर्णांक64_t tx_pol:4;
		uपूर्णांक64_t rx_pol:4;
#अन्यथा
		uपूर्णांक64_t rx_pol:4;
		uपूर्णांक64_t tx_pol:4;
		uपूर्णांक64_t pt_width:2;
		uपूर्णांक64_t tx_flow:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t a50:1;
		uपूर्णांक64_t a66:1;
		uपूर्णांक64_t reserved_14_31:18;
		uपूर्णांक64_t ops:32;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_sriox_mac_buffers अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_mac_buffers_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_56_63:8;
		uपूर्णांक64_t tx_enb:8;
		uपूर्णांक64_t reserved_44_47:4;
		uपूर्णांक64_t tx_inuse:4;
		uपूर्णांक64_t tx_stat:8;
		uपूर्णांक64_t reserved_24_31:8;
		uपूर्णांक64_t rx_enb:8;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t rx_inuse:4;
		uपूर्णांक64_t rx_stat:8;
#अन्यथा
		uपूर्णांक64_t rx_stat:8;
		uपूर्णांक64_t rx_inuse:4;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t rx_enb:8;
		uपूर्णांक64_t reserved_24_31:8;
		uपूर्णांक64_t tx_stat:8;
		uपूर्णांक64_t tx_inuse:4;
		uपूर्णांक64_t reserved_44_47:4;
		uपूर्णांक64_t tx_enb:8;
		uपूर्णांक64_t reserved_56_63:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_मुख्यt_op अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_मुख्यt_op_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t wr_data:32;
		uपूर्णांक64_t reserved_27_31:5;
		uपूर्णांक64_t fail:1;
		uपूर्णांक64_t pending:1;
		uपूर्णांक64_t op:1;
		uपूर्णांक64_t addr:24;
#अन्यथा
		uपूर्णांक64_t addr:24;
		uपूर्णांक64_t op:1;
		uपूर्णांक64_t pending:1;
		uपूर्णांक64_t fail:1;
		uपूर्णांक64_t reserved_27_31:5;
		uपूर्णांक64_t wr_data:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_मुख्यt_rd_data अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_मुख्यt_rd_data_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t valid:1;
		uपूर्णांक64_t rd_data:32;
#अन्यथा
		uपूर्णांक64_t rd_data:32;
		uपूर्णांक64_t valid:1;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_mce_tx_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_mce_tx_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t mce:1;
#अन्यथा
		uपूर्णांक64_t mce:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_mem_op_ctrl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_mem_op_ctrl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t rr_ro:1;
		uपूर्णांक64_t w_ro:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t rp1_sid:1;
		uपूर्णांक64_t rp0_sid:2;
		uपूर्णांक64_t rp1_pid:1;
		uपूर्णांक64_t rp0_pid:2;
#अन्यथा
		uपूर्णांक64_t rp0_pid:2;
		uपूर्णांक64_t rp1_pid:1;
		uपूर्णांक64_t rp0_sid:2;
		uपूर्णांक64_t rp1_sid:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t w_ro:1;
		uपूर्णांक64_t rr_ro:1;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_omsg_ctrlx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_omsg_ctrlx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t tesपंचांगode:1;
		uपूर्णांक64_t reserved_37_62:26;
		uपूर्णांक64_t silo_max:5;
		uपूर्णांक64_t rtry_thr:16;
		uपूर्णांक64_t rtry_en:1;
		uपूर्णांक64_t reserved_11_14:4;
		uपूर्णांक64_t idm_tt:1;
		uपूर्णांक64_t idm_sis:1;
		uपूर्णांक64_t idm_did:1;
		uपूर्णांक64_t lttr_sp:4;
		uपूर्णांक64_t lttr_mp:4;
#अन्यथा
		uपूर्णांक64_t lttr_mp:4;
		uपूर्णांक64_t lttr_sp:4;
		uपूर्णांक64_t idm_did:1;
		uपूर्णांक64_t idm_sis:1;
		uपूर्णांक64_t idm_tt:1;
		uपूर्णांक64_t reserved_11_14:4;
		uपूर्णांक64_t rtry_en:1;
		uपूर्णांक64_t rtry_thr:16;
		uपूर्णांक64_t silo_max:5;
		uपूर्णांक64_t reserved_37_62:26;
		uपूर्णांक64_t tesपंचांगode:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_sriox_omsg_ctrlx_cn63xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t tesपंचांगode:1;
		uपूर्णांक64_t reserved_32_62:31;
		uपूर्णांक64_t rtry_thr:16;
		uपूर्णांक64_t rtry_en:1;
		uपूर्णांक64_t reserved_11_14:4;
		uपूर्णांक64_t idm_tt:1;
		uपूर्णांक64_t idm_sis:1;
		uपूर्णांक64_t idm_did:1;
		uपूर्णांक64_t lttr_sp:4;
		uपूर्णांक64_t lttr_mp:4;
#अन्यथा
		uपूर्णांक64_t lttr_mp:4;
		uपूर्णांक64_t lttr_sp:4;
		uपूर्णांक64_t idm_did:1;
		uपूर्णांक64_t idm_sis:1;
		uपूर्णांक64_t idm_tt:1;
		uपूर्णांक64_t reserved_11_14:4;
		uपूर्णांक64_t rtry_en:1;
		uपूर्णांक64_t rtry_thr:16;
		uपूर्णांक64_t reserved_32_62:31;
		uपूर्णांक64_t tesपंचांगode:1;
#पूर्ण_अगर
	पूर्ण cn63xxp1;
पूर्ण;

जोड़ cvmx_sriox_omsg_करोne_countsx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_omsg_करोne_countsx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t bad:16;
		uपूर्णांक64_t good:16;
#अन्यथा
		uपूर्णांक64_t good:16;
		uपूर्णांक64_t bad:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_omsg_fmp_mrx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_omsg_fmp_mrx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t ctlr_sp:1;
		uपूर्णांक64_t ctlr_fmp:1;
		uपूर्णांक64_t ctlr_nmp:1;
		uपूर्णांक64_t id_sp:1;
		uपूर्णांक64_t id_fmp:1;
		uपूर्णांक64_t id_nmp:1;
		uपूर्णांक64_t id_psd:1;
		uपूर्णांक64_t mbox_sp:1;
		uपूर्णांक64_t mbox_fmp:1;
		uपूर्णांक64_t mbox_nmp:1;
		uपूर्णांक64_t mbox_psd:1;
		uपूर्णांक64_t all_sp:1;
		uपूर्णांक64_t all_fmp:1;
		uपूर्णांक64_t all_nmp:1;
		uपूर्णांक64_t all_psd:1;
#अन्यथा
		uपूर्णांक64_t all_psd:1;
		uपूर्णांक64_t all_nmp:1;
		uपूर्णांक64_t all_fmp:1;
		uपूर्णांक64_t all_sp:1;
		uपूर्णांक64_t mbox_psd:1;
		uपूर्णांक64_t mbox_nmp:1;
		uपूर्णांक64_t mbox_fmp:1;
		uपूर्णांक64_t mbox_sp:1;
		uपूर्णांक64_t id_psd:1;
		uपूर्णांक64_t id_nmp:1;
		uपूर्णांक64_t id_fmp:1;
		uपूर्णांक64_t id_sp:1;
		uपूर्णांक64_t ctlr_nmp:1;
		uपूर्णांक64_t ctlr_fmp:1;
		uपूर्णांक64_t ctlr_sp:1;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_omsg_nmp_mrx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_omsg_nmp_mrx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_15_63:49;
		uपूर्णांक64_t ctlr_sp:1;
		uपूर्णांक64_t ctlr_fmp:1;
		uपूर्णांक64_t ctlr_nmp:1;
		uपूर्णांक64_t id_sp:1;
		uपूर्णांक64_t id_fmp:1;
		uपूर्णांक64_t id_nmp:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t mbox_sp:1;
		uपूर्णांक64_t mbox_fmp:1;
		uपूर्णांक64_t mbox_nmp:1;
		uपूर्णांक64_t reserved_4_4:1;
		uपूर्णांक64_t all_sp:1;
		uपूर्णांक64_t all_fmp:1;
		uपूर्णांक64_t all_nmp:1;
		uपूर्णांक64_t reserved_0_0:1;
#अन्यथा
		uपूर्णांक64_t reserved_0_0:1;
		uपूर्णांक64_t all_nmp:1;
		uपूर्णांक64_t all_fmp:1;
		uपूर्णांक64_t all_sp:1;
		uपूर्णांक64_t reserved_4_4:1;
		uपूर्णांक64_t mbox_nmp:1;
		uपूर्णांक64_t mbox_fmp:1;
		uपूर्णांक64_t mbox_sp:1;
		uपूर्णांक64_t reserved_8_8:1;
		uपूर्णांक64_t id_nmp:1;
		uपूर्णांक64_t id_fmp:1;
		uपूर्णांक64_t id_sp:1;
		uपूर्णांक64_t ctlr_nmp:1;
		uपूर्णांक64_t ctlr_fmp:1;
		uपूर्णांक64_t ctlr_sp:1;
		uपूर्णांक64_t reserved_15_63:49;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_omsg_portx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_omsg_portx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t reserved_3_30:28;
		uपूर्णांक64_t port:3;
#अन्यथा
		uपूर्णांक64_t port:3;
		uपूर्णांक64_t reserved_3_30:28;
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_sriox_omsg_portx_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t reserved_2_30:29;
		uपूर्णांक64_t port:2;
#अन्यथा
		uपूर्णांक64_t port:2;
		uपूर्णांक64_t reserved_2_30:29;
		uपूर्णांक64_t enable:1;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_sriox_omsg_silo_thr अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_omsg_silo_thr_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_5_63:59;
		uपूर्णांक64_t tot_silo:5;
#अन्यथा
		uपूर्णांक64_t tot_silo:5;
		uपूर्णांक64_t reserved_5_63:59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_omsg_sp_mrx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_omsg_sp_mrx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t xmbox_sp:1;
		uपूर्णांक64_t ctlr_sp:1;
		uपूर्णांक64_t ctlr_fmp:1;
		uपूर्णांक64_t ctlr_nmp:1;
		uपूर्णांक64_t id_sp:1;
		uपूर्णांक64_t id_fmp:1;
		uपूर्णांक64_t id_nmp:1;
		uपूर्णांक64_t id_psd:1;
		uपूर्णांक64_t mbox_sp:1;
		uपूर्णांक64_t mbox_fmp:1;
		uपूर्णांक64_t mbox_nmp:1;
		uपूर्णांक64_t mbox_psd:1;
		uपूर्णांक64_t all_sp:1;
		uपूर्णांक64_t all_fmp:1;
		uपूर्णांक64_t all_nmp:1;
		uपूर्णांक64_t all_psd:1;
#अन्यथा
		uपूर्णांक64_t all_psd:1;
		uपूर्णांक64_t all_nmp:1;
		uपूर्णांक64_t all_fmp:1;
		uपूर्णांक64_t all_sp:1;
		uपूर्णांक64_t mbox_psd:1;
		uपूर्णांक64_t mbox_nmp:1;
		uपूर्णांक64_t mbox_fmp:1;
		uपूर्णांक64_t mbox_sp:1;
		uपूर्णांक64_t id_psd:1;
		uपूर्णांक64_t id_nmp:1;
		uपूर्णांक64_t id_fmp:1;
		uपूर्णांक64_t id_sp:1;
		uपूर्णांक64_t ctlr_nmp:1;
		uपूर्णांक64_t ctlr_fmp:1;
		uपूर्णांक64_t ctlr_sp:1;
		uपूर्णांक64_t xmbox_sp:1;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_priox_in_use अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_priox_in_use_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t end_cnt:16;
		uपूर्णांक64_t start_cnt:16;
#अन्यथा
		uपूर्णांक64_t start_cnt:16;
		uपूर्णांक64_t end_cnt:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_rx_bell अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_rx_bell_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t data:16;
		uपूर्णांक64_t src_id:16;
		uपूर्णांक64_t count:8;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t dest_id:1;
		uपूर्णांक64_t id16:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t priority:2;
#अन्यथा
		uपूर्णांक64_t priority:2;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t id16:1;
		uपूर्णांक64_t dest_id:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t count:8;
		uपूर्णांक64_t src_id:16;
		uपूर्णांक64_t data:16;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_rx_bell_seq अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_rx_bell_seq_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t count:8;
		uपूर्णांक64_t seq:32;
#अन्यथा
		uपूर्णांक64_t seq:32;
		uपूर्णांक64_t count:8;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_rx_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_rx_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t rtn_pr3:8;
		uपूर्णांक64_t rtn_pr2:8;
		uपूर्णांक64_t rtn_pr1:8;
		uपूर्णांक64_t reserved_28_39:12;
		uपूर्णांक64_t mbox:4;
		uपूर्णांक64_t comp:8;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t n_post:5;
		uपूर्णांक64_t post:8;
#अन्यथा
		uपूर्णांक64_t post:8;
		uपूर्णांक64_t n_post:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t comp:8;
		uपूर्णांक64_t mbox:4;
		uपूर्णांक64_t reserved_28_39:12;
		uपूर्णांक64_t rtn_pr1:8;
		uपूर्णांक64_t rtn_pr2:8;
		uपूर्णांक64_t rtn_pr3:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_s2m_typex अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_s2m_typex_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t wr_op:3;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t rd_op:3;
		uपूर्णांक64_t wr_prior:2;
		uपूर्णांक64_t rd_prior:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t src_id:1;
		uपूर्णांक64_t id16:1;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t iaow_sel:2;
#अन्यथा
		uपूर्णांक64_t iaow_sel:2;
		uपूर्णांक64_t reserved_2_3:2;
		uपूर्णांक64_t id16:1;
		uपूर्णांक64_t src_id:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t rd_prior:2;
		uपूर्णांक64_t wr_prior:2;
		uपूर्णांक64_t rd_op:3;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t wr_op:3;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_seq अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_seq_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t seq:32;
#अन्यथा
		uपूर्णांक64_t seq:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_status_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_status_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t access:1;
		uपूर्णांक64_t srio:1;
#अन्यथा
		uपूर्णांक64_t srio:1;
		uपूर्णांक64_t access:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_tag_ctrl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_tag_ctrl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t o_clr:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t otag:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t itag:5;
#अन्यथा
		uपूर्णांक64_t itag:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t otag:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t o_clr:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_tlp_credits अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_tlp_credits_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t mbox:4;
		uपूर्णांक64_t comp:8;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t n_post:5;
		uपूर्णांक64_t post:8;
#अन्यथा
		uपूर्णांक64_t post:8;
		uपूर्णांक64_t n_post:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t comp:8;
		uपूर्णांक64_t mbox:4;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_tx_bell अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_tx_bell_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t data:16;
		uपूर्णांक64_t dest_id:16;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t pending:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t src_id:1;
		uपूर्णांक64_t id16:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t priority:2;
#अन्यथा
		uपूर्णांक64_t priority:2;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t id16:1;
		uपूर्णांक64_t src_id:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t pending:1;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t dest_id:16;
		uपूर्णांक64_t data:16;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_tx_bell_info अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_tx_bell_info_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t data:16;
		uपूर्णांक64_t dest_id:16;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t समयout:1;
		uपूर्णांक64_t error:1;
		uपूर्णांक64_t retry:1;
		uपूर्णांक64_t src_id:1;
		uपूर्णांक64_t id16:1;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t priority:2;
#अन्यथा
		uपूर्णांक64_t priority:2;
		uपूर्णांक64_t reserved_2_2:1;
		uपूर्णांक64_t id16:1;
		uपूर्णांक64_t src_id:1;
		uपूर्णांक64_t retry:1;
		uपूर्णांक64_t error:1;
		uपूर्णांक64_t समयout:1;
		uपूर्णांक64_t reserved_8_15:8;
		uपूर्णांक64_t dest_id:16;
		uपूर्णांक64_t data:16;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_tx_ctrl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_tx_ctrl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_53_63:11;
		uपूर्णांक64_t tag_th2:5;
		uपूर्णांक64_t reserved_45_47:3;
		uपूर्णांक64_t tag_th1:5;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t tag_th0:5;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t tx_th2:4;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t tx_th1:4;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t tx_th0:4;
#अन्यथा
		uपूर्णांक64_t tx_th0:4;
		uपूर्णांक64_t reserved_4_7:4;
		uपूर्णांक64_t tx_th1:4;
		uपूर्णांक64_t reserved_12_15:4;
		uपूर्णांक64_t tx_th2:4;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t tag_th0:5;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t tag_th1:5;
		uपूर्णांक64_t reserved_45_47:3;
		uपूर्णांक64_t tag_th2:5;
		uपूर्णांक64_t reserved_53_63:11;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_tx_emphasis अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_tx_emphasis_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t emph:4;
#अन्यथा
		uपूर्णांक64_t emph:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_tx_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_tx_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t s2m_pr3:8;
		uपूर्णांक64_t s2m_pr2:8;
		uपूर्णांक64_t s2m_pr1:8;
		uपूर्णांक64_t s2m_pr0:8;
#अन्यथा
		uपूर्णांक64_t s2m_pr0:8;
		uपूर्णांक64_t s2m_pr1:8;
		uपूर्णांक64_t s2m_pr2:8;
		uपूर्णांक64_t s2m_pr3:8;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_sriox_wr_करोne_counts अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_sriox_wr_करोne_counts_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t bad:16;
		uपूर्णांक64_t good:16;
#अन्यथा
		uपूर्णांक64_t good:16;
		uपूर्णांक64_t bad:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
