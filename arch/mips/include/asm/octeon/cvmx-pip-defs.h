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

#अगर_अघोषित __CVMX_PIP_DEFS_H__
#घोषणा __CVMX_PIP_DEFS_H__

/*
 * Enumeration representing the amount of packet processing
 * and validation perक्रमmed by the input hardware.
 */
क्रमागत cvmx_pip_port_parse_mode अणु
	/*
	 * Packet input करोesn't perक्रमm any processing of the input
	 * packet.
	 */
	CVMX_PIP_PORT_CFG_MODE_NONE = 0ull,
	/*
	 * Full packet processing is perक्रमmed with poपूर्णांकer starting
	 * at the L2 (ethernet MAC) header.
	 */
	CVMX_PIP_PORT_CFG_MODE_SKIPL2 = 1ull,
	/*
	 * Input packets are assumed to be IP.	Results from non IP
	 * packets is undefined. Poपूर्णांकers reference the beginning of
	 * the IP header.
	 */
	CVMX_PIP_PORT_CFG_MODE_SKIPIP = 2ull
पूर्ण;

#घोषणा CVMX_PIP_ALT_SKIP_CFGX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002A00ull) + ((offset) & 3) * 8)
#घोषणा CVMX_PIP_BCK_PRS (CVMX_ADD_IO_SEG(0x00011800A0000038ull))
#घोषणा CVMX_PIP_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011800A0000000ull))
#घोषणा CVMX_PIP_BSEL_EXT_CFGX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002800ull) + ((offset) & 3) * 16)
#घोषणा CVMX_PIP_BSEL_EXT_POSX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002808ull) + ((offset) & 3) * 16)
#घोषणा CVMX_PIP_BSEL_TBL_ENTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0003000ull) + ((offset) & 511) * 8)
#घोषणा CVMX_PIP_CLKEN (CVMX_ADD_IO_SEG(0x00011800A0000040ull))
#घोषणा CVMX_PIP_CRC_CTLX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000040ull) + ((offset) & 1) * 8)
#घोषणा CVMX_PIP_CRC_IVX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000050ull) + ((offset) & 1) * 8)
#घोषणा CVMX_PIP_DEC_IPSECX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000080ull) + ((offset) & 3) * 8)
#घोषणा CVMX_PIP_DSA_SRC_GRP (CVMX_ADD_IO_SEG(0x00011800A0000190ull))
#घोषणा CVMX_PIP_DSA_VID_GRP (CVMX_ADD_IO_SEG(0x00011800A0000198ull))
#घोषणा CVMX_PIP_FRM_LEN_CHKX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000180ull) + ((offset) & 1) * 8)
#घोषणा CVMX_PIP_GBL_CFG (CVMX_ADD_IO_SEG(0x00011800A0000028ull))
#घोषणा CVMX_PIP_GBL_CTL (CVMX_ADD_IO_SEG(0x00011800A0000020ull))
#घोषणा CVMX_PIP_HG_PRI_QOS (CVMX_ADD_IO_SEG(0x00011800A00001A0ull))
#घोषणा CVMX_PIP_INT_EN (CVMX_ADD_IO_SEG(0x00011800A0000010ull))
#घोषणा CVMX_PIP_INT_REG (CVMX_ADD_IO_SEG(0x00011800A0000008ull))
#घोषणा CVMX_PIP_IP_OFFSET (CVMX_ADD_IO_SEG(0x00011800A0000060ull))
#घोषणा CVMX_PIP_PRI_TBLX(offset) (CVMX_ADD_IO_SEG(0x00011800A0004000ull) + ((offset) & 255) * 8)
#घोषणा CVMX_PIP_PRT_CFGBX(offset) (CVMX_ADD_IO_SEG(0x00011800A0008000ull) + ((offset) & 63) * 8)
#घोषणा CVMX_PIP_PRT_CFGX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000200ull) + ((offset) & 63) * 8)
#घोषणा CVMX_PIP_PRT_TAGX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000400ull) + ((offset) & 63) * 8)
#घोषणा CVMX_PIP_QOS_DIFFX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000600ull) + ((offset) & 63) * 8)
#घोषणा CVMX_PIP_QOS_VLANX(offset) (CVMX_ADD_IO_SEG(0x00011800A00000C0ull) + ((offset) & 7) * 8)
#घोषणा CVMX_PIP_QOS_WATCHX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000100ull) + ((offset) & 7) * 8)
#घोषणा CVMX_PIP_RAW_WORD (CVMX_ADD_IO_SEG(0x00011800A00000B0ull))
#घोषणा CVMX_PIP_SFT_RST (CVMX_ADD_IO_SEG(0x00011800A0000030ull))
#घोषणा CVMX_PIP_STAT0_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000800ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT0_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040000ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT10_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001480ull) + ((offset) & 63) * 16)
#घोषणा CVMX_PIP_STAT10_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040050ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT11_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001488ull) + ((offset) & 63) * 16)
#घोषणा CVMX_PIP_STAT11_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040058ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT1_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000808ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT1_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040008ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT2_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000810ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT2_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040010ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT3_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000818ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT3_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040018ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT4_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000820ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT4_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040020ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT5_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000828ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT5_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040028ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT6_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000830ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT6_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040030ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT7_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000838ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT7_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040038ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT8_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000840ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT8_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040040ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT9_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0000848ull) + ((offset) & 63) * 80)
#घोषणा CVMX_PIP_STAT9_X(offset) (CVMX_ADD_IO_SEG(0x00011800A0040048ull) + ((offset) & 63) * 128)
#घोषणा CVMX_PIP_STAT_CTL (CVMX_ADD_IO_SEG(0x00011800A0000018ull))
#घोषणा CVMX_PIP_STAT_INB_ERRSX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001A10ull) + ((offset) & 63) * 32)
#घोषणा CVMX_PIP_STAT_INB_ERRS_PKNDX(offset) (CVMX_ADD_IO_SEG(0x00011800A0020010ull) + ((offset) & 63) * 32)
#घोषणा CVMX_PIP_STAT_INB_OCTSX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001A08ull) + ((offset) & 63) * 32)
#घोषणा CVMX_PIP_STAT_INB_OCTS_PKNDX(offset) (CVMX_ADD_IO_SEG(0x00011800A0020008ull) + ((offset) & 63) * 32)
#घोषणा CVMX_PIP_STAT_INB_PKTSX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001A00ull) + ((offset) & 63) * 32)
#घोषणा CVMX_PIP_STAT_INB_PKTS_PKNDX(offset) (CVMX_ADD_IO_SEG(0x00011800A0020000ull) + ((offset) & 63) * 32)
#घोषणा CVMX_PIP_SUB_PKIND_FCSX(block_id) (CVMX_ADD_IO_SEG(0x00011800A0080000ull))
#घोषणा CVMX_PIP_TAG_INCX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001800ull) + ((offset) & 63) * 8)
#घोषणा CVMX_PIP_TAG_MASK (CVMX_ADD_IO_SEG(0x00011800A0000070ull))
#घोषणा CVMX_PIP_TAG_SECRET (CVMX_ADD_IO_SEG(0x00011800A0000068ull))
#घोषणा CVMX_PIP_TODO_ENTRY (CVMX_ADD_IO_SEG(0x00011800A0000078ull))
#घोषणा CVMX_PIP_VLAN_ETYPESX(offset) (CVMX_ADD_IO_SEG(0x00011800A00001C0ull) + ((offset) & 1) * 8)
#घोषणा CVMX_PIP_XSTAT0_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002000ull) + ((offset) & 63) * 80 - 80*40)
#घोषणा CVMX_PIP_XSTAT10_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001700ull) + ((offset) & 63) * 16 - 16*40)
#घोषणा CVMX_PIP_XSTAT11_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0001708ull) + ((offset) & 63) * 16 - 16*40)
#घोषणा CVMX_PIP_XSTAT1_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002008ull) + ((offset) & 63) * 80 - 80*40)
#घोषणा CVMX_PIP_XSTAT2_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002010ull) + ((offset) & 63) * 80 - 80*40)
#घोषणा CVMX_PIP_XSTAT3_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002018ull) + ((offset) & 63) * 80 - 80*40)
#घोषणा CVMX_PIP_XSTAT4_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002020ull) + ((offset) & 63) * 80 - 80*40)
#घोषणा CVMX_PIP_XSTAT5_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002028ull) + ((offset) & 63) * 80 - 80*40)
#घोषणा CVMX_PIP_XSTAT6_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002030ull) + ((offset) & 63) * 80 - 80*40)
#घोषणा CVMX_PIP_XSTAT7_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002038ull) + ((offset) & 63) * 80 - 80*40)
#घोषणा CVMX_PIP_XSTAT8_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002040ull) + ((offset) & 63) * 80 - 80*40)
#घोषणा CVMX_PIP_XSTAT9_PRTX(offset) (CVMX_ADD_IO_SEG(0x00011800A0002048ull) + ((offset) & 63) * 80 - 80*40)

जोड़ cvmx_pip_alt_skip_cfgx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_alt_skip_cfgx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_57_63:7;
		uपूर्णांक64_t len:1;
		uपूर्णांक64_t reserved_46_55:10;
		uपूर्णांक64_t bit1:6;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t bit0:6;
		uपूर्णांक64_t reserved_23_31:9;
		uपूर्णांक64_t skip3:7;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t skip2:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t skip1:7;
#अन्यथा
		uपूर्णांक64_t skip1:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t skip2:7;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t skip3:7;
		uपूर्णांक64_t reserved_23_31:9;
		uपूर्णांक64_t bit0:6;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t bit1:6;
		uपूर्णांक64_t reserved_46_55:10;
		uपूर्णांक64_t len:1;
		uपूर्णांक64_t reserved_57_63:7;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_bck_prs अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_bck_prs_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t reserved_13_62:50;
		uपूर्णांक64_t hiwater:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t lowater:5;
#अन्यथा
		uपूर्णांक64_t lowater:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t hiwater:5;
		uपूर्णांक64_t reserved_13_62:50;
		uपूर्णांक64_t bckprs:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_bist_status अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_bist_status_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_22_63:42;
		uपूर्णांक64_t bist:22;
#अन्यथा
		uपूर्णांक64_t bist:22;
		uपूर्णांक64_t reserved_22_63:42;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_bist_status_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t bist:18;
#अन्यथा
		uपूर्णांक64_t bist:18;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pip_bist_status_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t bist:17;
#अन्यथा
		uपूर्णांक64_t bist:17;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pip_bist_status_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t bist:20;
#अन्यथा
		uपूर्णांक64_t bist:20;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_pip_bsel_ext_cfgx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_bsel_ext_cfgx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_56_63:8;
		uपूर्णांक64_t upper_tag:16;
		uपूर्णांक64_t tag:8;
		uपूर्णांक64_t reserved_25_31:7;
		uपूर्णांक64_t offset:9;
		uपूर्णांक64_t reserved_7_15:9;
		uपूर्णांक64_t skip:7;
#अन्यथा
		uपूर्णांक64_t skip:7;
		uपूर्णांक64_t reserved_7_15:9;
		uपूर्णांक64_t offset:9;
		uपूर्णांक64_t reserved_25_31:7;
		uपूर्णांक64_t tag:8;
		uपूर्णांक64_t upper_tag:16;
		uपूर्णांक64_t reserved_56_63:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_bsel_ext_posx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_bsel_ext_posx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pos7_val:1;
		uपूर्णांक64_t pos7:7;
		uपूर्णांक64_t pos6_val:1;
		uपूर्णांक64_t pos6:7;
		uपूर्णांक64_t pos5_val:1;
		uपूर्णांक64_t pos5:7;
		uपूर्णांक64_t pos4_val:1;
		uपूर्णांक64_t pos4:7;
		uपूर्णांक64_t pos3_val:1;
		uपूर्णांक64_t pos3:7;
		uपूर्णांक64_t pos2_val:1;
		uपूर्णांक64_t pos2:7;
		uपूर्णांक64_t pos1_val:1;
		uपूर्णांक64_t pos1:7;
		uपूर्णांक64_t pos0_val:1;
		uपूर्णांक64_t pos0:7;
#अन्यथा
		uपूर्णांक64_t pos0:7;
		uपूर्णांक64_t pos0_val:1;
		uपूर्णांक64_t pos1:7;
		uपूर्णांक64_t pos1_val:1;
		uपूर्णांक64_t pos2:7;
		uपूर्णांक64_t pos2_val:1;
		uपूर्णांक64_t pos3:7;
		uपूर्णांक64_t pos3_val:1;
		uपूर्णांक64_t pos4:7;
		uपूर्णांक64_t pos4_val:1;
		uपूर्णांक64_t pos5:7;
		uपूर्णांक64_t pos5_val:1;
		uपूर्णांक64_t pos6:7;
		uपूर्णांक64_t pos6_val:1;
		uपूर्णांक64_t pos7:7;
		uपूर्णांक64_t pos7_val:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_bsel_tbl_entx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_bsel_tbl_entx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t tag_en:1;
		uपूर्णांक64_t grp_en:1;
		uपूर्णांक64_t tt_en:1;
		uपूर्णांक64_t qos_en:1;
		uपूर्णांक64_t reserved_40_59:20;
		uपूर्णांक64_t tag:8;
		uपूर्णांक64_t reserved_22_31:10;
		uपूर्णांक64_t grp:6;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t tt:2;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t tt:2;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t grp:6;
		uपूर्णांक64_t reserved_22_31:10;
		uपूर्णांक64_t tag:8;
		uपूर्णांक64_t reserved_40_59:20;
		uपूर्णांक64_t qos_en:1;
		uपूर्णांक64_t tt_en:1;
		uपूर्णांक64_t grp_en:1;
		uपूर्णांक64_t tag_en:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_bsel_tbl_entx_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t tag_en:1;
		uपूर्णांक64_t grp_en:1;
		uपूर्णांक64_t tt_en:1;
		uपूर्णांक64_t qos_en:1;
		uपूर्णांक64_t reserved_40_59:20;
		uपूर्णांक64_t tag:8;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t tt:2;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t tt:2;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t reserved_20_31:12;
		uपूर्णांक64_t tag:8;
		uपूर्णांक64_t reserved_40_59:20;
		uपूर्णांक64_t qos_en:1;
		uपूर्णांक64_t tt_en:1;
		uपूर्णांक64_t grp_en:1;
		uपूर्णांक64_t tag_en:1;
#पूर्ण_अगर
	पूर्ण cn61xx;
पूर्ण;

जोड़ cvmx_pip_clken अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_clken_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t clken:1;
#अन्यथा
		uपूर्णांक64_t clken:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_crc_ctlx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_crc_ctlx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t invres:1;
		uपूर्णांक64_t reflect:1;
#अन्यथा
		uपूर्णांक64_t reflect:1;
		uपूर्णांक64_t invres:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_crc_ivx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_crc_ivx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t iv:32;
#अन्यथा
		uपूर्णांक64_t iv:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_dec_ipsecx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_dec_ipsecx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_18_63:46;
		uपूर्णांक64_t tcp:1;
		uपूर्णांक64_t udp:1;
		uपूर्णांक64_t dprt:16;
#अन्यथा
		uपूर्णांक64_t dprt:16;
		uपूर्णांक64_t udp:1;
		uपूर्णांक64_t tcp:1;
		uपूर्णांक64_t reserved_18_63:46;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_dsa_src_grp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_dsa_src_grp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t map15:4;
		uपूर्णांक64_t map14:4;
		uपूर्णांक64_t map13:4;
		uपूर्णांक64_t map12:4;
		uपूर्णांक64_t map11:4;
		uपूर्णांक64_t map10:4;
		uपूर्णांक64_t map9:4;
		uपूर्णांक64_t map8:4;
		uपूर्णांक64_t map7:4;
		uपूर्णांक64_t map6:4;
		uपूर्णांक64_t map5:4;
		uपूर्णांक64_t map4:4;
		uपूर्णांक64_t map3:4;
		uपूर्णांक64_t map2:4;
		uपूर्णांक64_t map1:4;
		uपूर्णांक64_t map0:4;
#अन्यथा
		uपूर्णांक64_t map0:4;
		uपूर्णांक64_t map1:4;
		uपूर्णांक64_t map2:4;
		uपूर्णांक64_t map3:4;
		uपूर्णांक64_t map4:4;
		uपूर्णांक64_t map5:4;
		uपूर्णांक64_t map6:4;
		uपूर्णांक64_t map7:4;
		uपूर्णांक64_t map8:4;
		uपूर्णांक64_t map9:4;
		uपूर्णांक64_t map10:4;
		uपूर्णांक64_t map11:4;
		uपूर्णांक64_t map12:4;
		uपूर्णांक64_t map13:4;
		uपूर्णांक64_t map14:4;
		uपूर्णांक64_t map15:4;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_dsa_vid_grp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_dsa_vid_grp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t map15:4;
		uपूर्णांक64_t map14:4;
		uपूर्णांक64_t map13:4;
		uपूर्णांक64_t map12:4;
		uपूर्णांक64_t map11:4;
		uपूर्णांक64_t map10:4;
		uपूर्णांक64_t map9:4;
		uपूर्णांक64_t map8:4;
		uपूर्णांक64_t map7:4;
		uपूर्णांक64_t map6:4;
		uपूर्णांक64_t map5:4;
		uपूर्णांक64_t map4:4;
		uपूर्णांक64_t map3:4;
		uपूर्णांक64_t map2:4;
		uपूर्णांक64_t map1:4;
		uपूर्णांक64_t map0:4;
#अन्यथा
		uपूर्णांक64_t map0:4;
		uपूर्णांक64_t map1:4;
		uपूर्णांक64_t map2:4;
		uपूर्णांक64_t map3:4;
		uपूर्णांक64_t map4:4;
		uपूर्णांक64_t map5:4;
		uपूर्णांक64_t map6:4;
		uपूर्णांक64_t map7:4;
		uपूर्णांक64_t map8:4;
		uपूर्णांक64_t map9:4;
		uपूर्णांक64_t map10:4;
		uपूर्णांक64_t map11:4;
		uपूर्णांक64_t map12:4;
		uपूर्णांक64_t map13:4;
		uपूर्णांक64_t map14:4;
		uपूर्णांक64_t map15:4;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_frm_len_chkx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_frm_len_chkx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t maxlen:16;
		uपूर्णांक64_t minlen:16;
#अन्यथा
		uपूर्णांक64_t minlen:16;
		uपूर्णांक64_t maxlen:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_gbl_cfg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_gbl_cfg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_19_63:45;
		uपूर्णांक64_t tag_syn:1;
		uपूर्णांक64_t ip6_udp:1;
		uपूर्णांक64_t max_l2:1;
		uपूर्णांक64_t reserved_11_15:5;
		uपूर्णांक64_t raw_shf:3;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t nip_shf:3;
#अन्यथा
		uपूर्णांक64_t nip_shf:3;
		uपूर्णांक64_t reserved_3_7:5;
		uपूर्णांक64_t raw_shf:3;
		uपूर्णांक64_t reserved_11_15:5;
		uपूर्णांक64_t max_l2:1;
		uपूर्णांक64_t ip6_udp:1;
		uपूर्णांक64_t tag_syn:1;
		uपूर्णांक64_t reserved_19_63:45;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_gbl_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_gbl_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t egrp_dis:1;
		uपूर्णांक64_t ihmsk_dis:1;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_chk:1;
#अन्यथा
		uपूर्णांक64_t ip_chk:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t ihmsk_dis:1;
		uपूर्णांक64_t egrp_dis:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_gbl_ctl_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_chk:1;
#अन्यथा
		uपूर्णांक64_t ip_chk:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pip_gbl_ctl_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_27_63:37;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_chk:1;
#अन्यथा
		uपूर्णांक64_t ip_chk:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t reserved_27_63:37;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pip_gbl_ctl_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_21_63:43;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_chk:1;
#अन्यथा
		uपूर्णांक64_t ip_chk:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t reserved_21_63:43;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
	काष्ठा cvmx_pip_gbl_ctl_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t ihmsk_dis:1;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_chk:1;
#अन्यथा
		uपूर्णांक64_t ip_chk:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t reserved_17_19:3;
		uपूर्णांक64_t ring_en:1;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t ihmsk_dis:1;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_pip_gbl_ctl_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t egrp_dis:1;
		uपूर्णांक64_t ihmsk_dis:1;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t reserved_17_23:7;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_chk:1;
#अन्यथा
		uपूर्णांक64_t ip_chk:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t reserved_17_23:7;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t ihmsk_dis:1;
		uपूर्णांक64_t egrp_dis:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn68xx;
	काष्ठा cvmx_pip_gbl_ctl_cn68xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t ihmsk_dis:1;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t reserved_17_23:7;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_chk:1;
#अन्यथा
		uपूर्णांक64_t ip_chk:1;
		uपूर्णांक64_t ip_mal:1;
		uपूर्णांक64_t ip_hop:1;
		uपूर्णांक64_t ip4_opts:1;
		uपूर्णांक64_t ip6_eext:2;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t l4_mal:1;
		uपूर्णांक64_t l4_prt:1;
		uपूर्णांक64_t l4_chk:1;
		uपूर्णांक64_t l4_len:1;
		uपूर्णांक64_t tcp_flag:1;
		uपूर्णांक64_t l2_mal:1;
		uपूर्णांक64_t vs_qos:1;
		uपूर्णांक64_t vs_wqe:1;
		uपूर्णांक64_t ignrs:1;
		uपूर्णांक64_t reserved_17_23:7;
		uपूर्णांक64_t dsa_grp_sid:1;
		uपूर्णांक64_t dsa_grp_scmd:1;
		uपूर्णांक64_t dsa_grp_tvid:1;
		uपूर्णांक64_t ihmsk_dis:1;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn68xxp1;
पूर्ण;

जोड़ cvmx_pip_hg_pri_qos अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_hg_pri_qos_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t up_qos:1;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t pri:6;
#अन्यथा
		uपूर्णांक64_t pri:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_11_11:1;
		uपूर्णांक64_t up_qos:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_पूर्णांक_en अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_पूर्णांक_en_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_पूर्णांक_en_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pip_पूर्णांक_en_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pip_पूर्णांक_en_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pip_पूर्णांक_en_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
	काष्ठा cvmx_pip_पूर्णांक_en_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण cn58xx;
पूर्ण;

जोड़ cvmx_pip_पूर्णांक_reg अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_पूर्णांक_reg_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_पूर्णांक_reg_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pip_पूर्णांक_reg_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pip_पूर्णांक_reg_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t reserved_1_1:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pip_पूर्णांक_reg_cn56xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t minerr:1;
		uपूर्णांक64_t maxerr:1;
		uपूर्णांक64_t lenerr:1;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn56xxp1;
	काष्ठा cvmx_pip_पूर्णांक_reg_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_13_63:51;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t pktdrp:1;
#अन्यथा
		uपूर्णांक64_t pktdrp:1;
		uपूर्णांक64_t crcerr:1;
		uपूर्णांक64_t bckprs:1;
		uपूर्णांक64_t prtnxa:1;
		uपूर्णांक64_t badtag:1;
		uपूर्णांक64_t skprunt:1;
		uपूर्णांक64_t toकरोovr:1;
		uपूर्णांक64_t feperr:1;
		uपूर्णांक64_t beperr:1;
		uपूर्णांक64_t reserved_9_11:3;
		uपूर्णांक64_t punyerr:1;
		uपूर्णांक64_t reserved_13_63:51;
#पूर्ण_अगर
	पूर्ण cn58xx;
पूर्ण;

जोड़ cvmx_pip_ip_offset अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_ip_offset_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t offset:3;
#अन्यथा
		uपूर्णांक64_t offset:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_pri_tblx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_pri_tblx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dअगरf2_padd:8;
		uपूर्णांक64_t hg2_padd:8;
		uपूर्णांक64_t vlan2_padd:8;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t dअगरf2_bpid:6;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t hg2_bpid:6;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t vlan2_bpid:6;
		uपूर्णांक64_t reserved_11_15:5;
		uपूर्णांक64_t dअगरf2_qos:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t hg2_qos:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t vlan2_qos:3;
#अन्यथा
		uपूर्णांक64_t vlan2_qos:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t hg2_qos:3;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t dअगरf2_qos:3;
		uपूर्णांक64_t reserved_11_15:5;
		uपूर्णांक64_t vlan2_bpid:6;
		uपूर्णांक64_t reserved_22_23:2;
		uपूर्णांक64_t hg2_bpid:6;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t dअगरf2_bpid:6;
		uपूर्णांक64_t reserved_38_39:2;
		uपूर्णांक64_t vlan2_padd:8;
		uपूर्णांक64_t hg2_padd:8;
		uपूर्णांक64_t dअगरf2_padd:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_prt_cfgx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_prt_cfgx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_55_63:9;
		uपूर्णांक64_t ih_pri:1;
		uपूर्णांक64_t len_chk_sel:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t lenerr_en:1;
		uपूर्णांक64_t maxerr_en:1;
		uपूर्णांक64_t minerr_en:1;
		uपूर्णांक64_t grp_wat_47:4;
		uपूर्णांक64_t qos_wat_47:4;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t hg_qos:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t qos_vsel:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t higig_en:1;
		uपूर्णांक64_t dsa_en:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t skip:7;
#अन्यथा
		uपूर्णांक64_t skip:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t dsa_en:1;
		uपूर्णांक64_t higig_en:1;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t qos_vsel:1;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t hg_qos:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t qos_wat_47:4;
		uपूर्णांक64_t grp_wat_47:4;
		uपूर्णांक64_t minerr_en:1;
		uपूर्णांक64_t maxerr_en:1;
		uपूर्णांक64_t lenerr_en:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t len_chk_sel:1;
		uपूर्णांक64_t ih_pri:1;
		uपूर्णांक64_t reserved_55_63:9;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_prt_cfgx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t skip:7;
#अन्यथा
		uपूर्णांक64_t skip:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_10_15:6;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pip_prt_cfgx_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t skip:7;
#अन्यथा
		uपूर्णांक64_t skip:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_pip_prt_cfgx_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_53_63:11;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t lenerr_en:1;
		uपूर्णांक64_t maxerr_en:1;
		uपूर्णांक64_t minerr_en:1;
		uपूर्णांक64_t grp_wat_47:4;
		uपूर्णांक64_t qos_wat_47:4;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t skip:7;
#अन्यथा
		uपूर्णांक64_t skip:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t qos_wat_47:4;
		uपूर्णांक64_t grp_wat_47:4;
		uपूर्णांक64_t minerr_en:1;
		uपूर्णांक64_t maxerr_en:1;
		uपूर्णांक64_t lenerr_en:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t reserved_53_63:11;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pip_prt_cfgx_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_53_63:11;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t lenerr_en:1;
		uपूर्णांक64_t maxerr_en:1;
		uपूर्णांक64_t minerr_en:1;
		uपूर्णांक64_t grp_wat_47:4;
		uपूर्णांक64_t qos_wat_47:4;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t hg_qos:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t qos_vsel:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t higig_en:1;
		uपूर्णांक64_t dsa_en:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t skip:7;
#अन्यथा
		uपूर्णांक64_t skip:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t dsa_en:1;
		uपूर्णांक64_t higig_en:1;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t qos_vsel:1;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t hg_qos:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t qos_wat_47:4;
		uपूर्णांक64_t grp_wat_47:4;
		uपूर्णांक64_t minerr_en:1;
		uपूर्णांक64_t maxerr_en:1;
		uपूर्णांक64_t lenerr_en:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t reserved_53_63:11;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pip_prt_cfgx_cn58xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t skip:7;
#अन्यथा
		uपूर्णांक64_t skip:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_10_11:2;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण cn58xx;
	काष्ठा cvmx_pip_prt_cfgx_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_55_63:9;
		uपूर्णांक64_t ih_pri:1;
		uपूर्णांक64_t len_chk_sel:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t lenerr_en:1;
		uपूर्णांक64_t maxerr_en:1;
		uपूर्णांक64_t minerr_en:1;
		uपूर्णांक64_t grp_wat_47:4;
		uपूर्णांक64_t qos_wat_47:4;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t hg_qos:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t higig_en:1;
		uपूर्णांक64_t dsa_en:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t skip:7;
#अन्यथा
		uपूर्णांक64_t skip:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t dsa_en:1;
		uपूर्णांक64_t higig_en:1;
		uपूर्णांक64_t crc_en:1;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t qos_vlan:1;
		uपूर्णांक64_t qos_dअगरf:1;
		uपूर्णांक64_t qos_vod:1;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t qos_wat:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t hg_qos:1;
		uपूर्णांक64_t grp_wat:4;
		uपूर्णांक64_t inst_hdr:1;
		uपूर्णांक64_t dyn_rs:1;
		uपूर्णांक64_t tag_inc:2;
		uपूर्णांक64_t rawdrp:1;
		uपूर्णांक64_t reserved_37_39:3;
		uपूर्णांक64_t qos_wat_47:4;
		uपूर्णांक64_t grp_wat_47:4;
		uपूर्णांक64_t minerr_en:1;
		uपूर्णांक64_t maxerr_en:1;
		uपूर्णांक64_t lenerr_en:1;
		uपूर्णांक64_t vlan_len:1;
		uपूर्णांक64_t pad_len:1;
		uपूर्णांक64_t len_chk_sel:1;
		uपूर्णांक64_t ih_pri:1;
		uपूर्णांक64_t reserved_55_63:9;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_pip_prt_cfgbx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_prt_cfgbx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_39_63:25;
		uपूर्णांक64_t alt_skp_sel:2;
		uपूर्णांक64_t alt_skp_en:1;
		uपूर्णांक64_t reserved_35_35:1;
		uपूर्णांक64_t bsel_num:2;
		uपूर्णांक64_t bsel_en:1;
		uपूर्णांक64_t reserved_24_31:8;
		uपूर्णांक64_t base:8;
		uपूर्णांक64_t reserved_6_15:10;
		uपूर्णांक64_t bpid:6;
#अन्यथा
		uपूर्णांक64_t bpid:6;
		uपूर्णांक64_t reserved_6_15:10;
		uपूर्णांक64_t base:8;
		uपूर्णांक64_t reserved_24_31:8;
		uपूर्णांक64_t bsel_en:1;
		uपूर्णांक64_t bsel_num:2;
		uपूर्णांक64_t reserved_35_35:1;
		uपूर्णांक64_t alt_skp_en:1;
		uपूर्णांक64_t alt_skp_sel:2;
		uपूर्णांक64_t reserved_39_63:25;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_prt_cfgbx_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_39_63:25;
		uपूर्णांक64_t alt_skp_sel:2;
		uपूर्णांक64_t alt_skp_en:1;
		uपूर्णांक64_t reserved_35_35:1;
		uपूर्णांक64_t bsel_num:2;
		uपूर्णांक64_t bsel_en:1;
		uपूर्णांक64_t reserved_0_31:32;
#अन्यथा
		uपूर्णांक64_t reserved_0_31:32;
		uपूर्णांक64_t bsel_en:1;
		uपूर्णांक64_t bsel_num:2;
		uपूर्णांक64_t reserved_35_35:1;
		uपूर्णांक64_t alt_skp_en:1;
		uपूर्णांक64_t alt_skp_sel:2;
		uपूर्णांक64_t reserved_39_63:25;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_pip_prt_cfgbx_cn66xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_39_63:25;
		uपूर्णांक64_t alt_skp_sel:2;
		uपूर्णांक64_t alt_skp_en:1;
		uपूर्णांक64_t reserved_0_35:36;
#अन्यथा
		uपूर्णांक64_t reserved_0_35:36;
		uपूर्णांक64_t alt_skp_en:1;
		uपूर्णांक64_t alt_skp_sel:2;
		uपूर्णांक64_t reserved_39_63:25;
#पूर्ण_अगर
	पूर्ण cn66xx;
	काष्ठा cvmx_pip_prt_cfgbx_cn68xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_24_63:40;
		uपूर्णांक64_t base:8;
		uपूर्णांक64_t reserved_6_15:10;
		uपूर्णांक64_t bpid:6;
#अन्यथा
		uपूर्णांक64_t bpid:6;
		uपूर्णांक64_t reserved_6_15:10;
		uपूर्णांक64_t base:8;
		uपूर्णांक64_t reserved_24_63:40;
#पूर्ण_अगर
	पूर्ण cn68xxp1;
पूर्ण;

जोड़ cvmx_pip_prt_tagx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_prt_tagx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_54_63:10;
		uपूर्णांक64_t portadd_en:1;
		uपूर्णांक64_t inc_hwchk:1;
		uपूर्णांक64_t reserved_50_51:2;
		uपूर्णांक64_t grptagbase_msb:2;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t grptagmask_msb:2;
		uपूर्णांक64_t reserved_42_43:2;
		uपूर्णांक64_t grp_msb:2;
		uपूर्णांक64_t grptagbase:4;
		uपूर्णांक64_t grptagmask:4;
		uपूर्णांक64_t grptag:1;
		uपूर्णांक64_t grptag_mskip:1;
		uपूर्णांक64_t tag_mode:2;
		uपूर्णांक64_t inc_vs:2;
		uपूर्णांक64_t inc_vlan:1;
		uपूर्णांक64_t inc_prt_flag:1;
		uपूर्णांक64_t ip6_dprt_flag:1;
		uपूर्णांक64_t ip4_dprt_flag:1;
		uपूर्णांक64_t ip6_sprt_flag:1;
		uपूर्णांक64_t ip4_sprt_flag:1;
		uपूर्णांक64_t ip6_nxth_flag:1;
		uपूर्णांक64_t ip4_pctl_flag:1;
		uपूर्णांक64_t ip6_dst_flag:1;
		uपूर्णांक64_t ip4_dst_flag:1;
		uपूर्णांक64_t ip6_src_flag:1;
		uपूर्णांक64_t ip4_src_flag:1;
		uपूर्णांक64_t tcp6_tag_type:2;
		uपूर्णांक64_t tcp4_tag_type:2;
		uपूर्णांक64_t ip6_tag_type:2;
		uपूर्णांक64_t ip4_tag_type:2;
		uपूर्णांक64_t non_tag_type:2;
		uपूर्णांक64_t grp:4;
#अन्यथा
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t non_tag_type:2;
		uपूर्णांक64_t ip4_tag_type:2;
		uपूर्णांक64_t ip6_tag_type:2;
		uपूर्णांक64_t tcp4_tag_type:2;
		uपूर्णांक64_t tcp6_tag_type:2;
		uपूर्णांक64_t ip4_src_flag:1;
		uपूर्णांक64_t ip6_src_flag:1;
		uपूर्णांक64_t ip4_dst_flag:1;
		uपूर्णांक64_t ip6_dst_flag:1;
		uपूर्णांक64_t ip4_pctl_flag:1;
		uपूर्णांक64_t ip6_nxth_flag:1;
		uपूर्णांक64_t ip4_sprt_flag:1;
		uपूर्णांक64_t ip6_sprt_flag:1;
		uपूर्णांक64_t ip4_dprt_flag:1;
		uपूर्णांक64_t ip6_dprt_flag:1;
		uपूर्णांक64_t inc_prt_flag:1;
		uपूर्णांक64_t inc_vlan:1;
		uपूर्णांक64_t inc_vs:2;
		uपूर्णांक64_t tag_mode:2;
		uपूर्णांक64_t grptag_mskip:1;
		uपूर्णांक64_t grptag:1;
		uपूर्णांक64_t grptagmask:4;
		uपूर्णांक64_t grptagbase:4;
		uपूर्णांक64_t grp_msb:2;
		uपूर्णांक64_t reserved_42_43:2;
		uपूर्णांक64_t grptagmask_msb:2;
		uपूर्णांक64_t reserved_46_47:2;
		uपूर्णांक64_t grptagbase_msb:2;
		uपूर्णांक64_t reserved_50_51:2;
		uपूर्णांक64_t inc_hwchk:1;
		uपूर्णांक64_t portadd_en:1;
		uपूर्णांक64_t reserved_54_63:10;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_prt_tagx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t grptagbase:4;
		uपूर्णांक64_t grptagmask:4;
		uपूर्णांक64_t grptag:1;
		uपूर्णांक64_t reserved_30_30:1;
		uपूर्णांक64_t tag_mode:2;
		uपूर्णांक64_t inc_vs:2;
		uपूर्णांक64_t inc_vlan:1;
		uपूर्णांक64_t inc_prt_flag:1;
		uपूर्णांक64_t ip6_dprt_flag:1;
		uपूर्णांक64_t ip4_dprt_flag:1;
		uपूर्णांक64_t ip6_sprt_flag:1;
		uपूर्णांक64_t ip4_sprt_flag:1;
		uपूर्णांक64_t ip6_nxth_flag:1;
		uपूर्णांक64_t ip4_pctl_flag:1;
		uपूर्णांक64_t ip6_dst_flag:1;
		uपूर्णांक64_t ip4_dst_flag:1;
		uपूर्णांक64_t ip6_src_flag:1;
		uपूर्णांक64_t ip4_src_flag:1;
		uपूर्णांक64_t tcp6_tag_type:2;
		uपूर्णांक64_t tcp4_tag_type:2;
		uपूर्णांक64_t ip6_tag_type:2;
		uपूर्णांक64_t ip4_tag_type:2;
		uपूर्णांक64_t non_tag_type:2;
		uपूर्णांक64_t grp:4;
#अन्यथा
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t non_tag_type:2;
		uपूर्णांक64_t ip4_tag_type:2;
		uपूर्णांक64_t ip6_tag_type:2;
		uपूर्णांक64_t tcp4_tag_type:2;
		uपूर्णांक64_t tcp6_tag_type:2;
		uपूर्णांक64_t ip4_src_flag:1;
		uपूर्णांक64_t ip6_src_flag:1;
		uपूर्णांक64_t ip4_dst_flag:1;
		uपूर्णांक64_t ip6_dst_flag:1;
		uपूर्णांक64_t ip4_pctl_flag:1;
		uपूर्णांक64_t ip6_nxth_flag:1;
		uपूर्णांक64_t ip4_sprt_flag:1;
		uपूर्णांक64_t ip6_sprt_flag:1;
		uपूर्णांक64_t ip4_dprt_flag:1;
		uपूर्णांक64_t ip6_dprt_flag:1;
		uपूर्णांक64_t inc_prt_flag:1;
		uपूर्णांक64_t inc_vlan:1;
		uपूर्णांक64_t inc_vs:2;
		uपूर्णांक64_t tag_mode:2;
		uपूर्णांक64_t reserved_30_30:1;
		uपूर्णांक64_t grptag:1;
		uपूर्णांक64_t grptagmask:4;
		uपूर्णांक64_t grptagbase:4;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pip_prt_tagx_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t grptagbase:4;
		uपूर्णांक64_t grptagmask:4;
		uपूर्णांक64_t grptag:1;
		uपूर्णांक64_t grptag_mskip:1;
		uपूर्णांक64_t tag_mode:2;
		uपूर्णांक64_t inc_vs:2;
		uपूर्णांक64_t inc_vlan:1;
		uपूर्णांक64_t inc_prt_flag:1;
		uपूर्णांक64_t ip6_dprt_flag:1;
		uपूर्णांक64_t ip4_dprt_flag:1;
		uपूर्णांक64_t ip6_sprt_flag:1;
		uपूर्णांक64_t ip4_sprt_flag:1;
		uपूर्णांक64_t ip6_nxth_flag:1;
		uपूर्णांक64_t ip4_pctl_flag:1;
		uपूर्णांक64_t ip6_dst_flag:1;
		uपूर्णांक64_t ip4_dst_flag:1;
		uपूर्णांक64_t ip6_src_flag:1;
		uपूर्णांक64_t ip4_src_flag:1;
		uपूर्णांक64_t tcp6_tag_type:2;
		uपूर्णांक64_t tcp4_tag_type:2;
		uपूर्णांक64_t ip6_tag_type:2;
		uपूर्णांक64_t ip4_tag_type:2;
		uपूर्णांक64_t non_tag_type:2;
		uपूर्णांक64_t grp:4;
#अन्यथा
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t non_tag_type:2;
		uपूर्णांक64_t ip4_tag_type:2;
		uपूर्णांक64_t ip6_tag_type:2;
		uपूर्णांक64_t tcp4_tag_type:2;
		uपूर्णांक64_t tcp6_tag_type:2;
		uपूर्णांक64_t ip4_src_flag:1;
		uपूर्णांक64_t ip6_src_flag:1;
		uपूर्णांक64_t ip4_dst_flag:1;
		uपूर्णांक64_t ip6_dst_flag:1;
		uपूर्णांक64_t ip4_pctl_flag:1;
		uपूर्णांक64_t ip6_nxth_flag:1;
		uपूर्णांक64_t ip4_sprt_flag:1;
		uपूर्णांक64_t ip6_sprt_flag:1;
		uपूर्णांक64_t ip4_dprt_flag:1;
		uपूर्णांक64_t ip6_dprt_flag:1;
		uपूर्णांक64_t inc_prt_flag:1;
		uपूर्णांक64_t inc_vlan:1;
		uपूर्णांक64_t inc_vs:2;
		uपूर्णांक64_t tag_mode:2;
		uपूर्णांक64_t grptag_mskip:1;
		uपूर्णांक64_t grptag:1;
		uपूर्णांक64_t grptagmask:4;
		uपूर्णांक64_t grptagbase:4;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_pip_qos_dअगरfx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_qos_dअगरfx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_qos_vlanx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_qos_vlanx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t qos1:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_3_3:1;
		uपूर्णांक64_t qos1:3;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_qos_vlanx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_pip_qos_watchx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_qos_watchx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t mask:16;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t grp:6;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t match_type:3;
		uपूर्णांक64_t match_value:16;
#अन्यथा
		uपूर्णांक64_t match_value:16;
		uपूर्णांक64_t match_type:3;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t grp:6;
		uपूर्णांक64_t reserved_30_31:2;
		uपूर्णांक64_t mask:16;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_qos_watchx_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t mask:16;
		uपूर्णांक64_t reserved_28_31:4;
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t match_type:2;
		uपूर्णांक64_t match_value:16;
#अन्यथा
		uपूर्णांक64_t match_value:16;
		uपूर्णांक64_t match_type:2;
		uपूर्णांक64_t reserved_18_19:2;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t reserved_28_31:4;
		uपूर्णांक64_t mask:16;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pip_qos_watchx_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t mask:16;
		uपूर्णांक64_t reserved_28_31:4;
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t match_type:3;
		uपूर्णांक64_t match_value:16;
#अन्यथा
		uपूर्णांक64_t match_value:16;
		uपूर्णांक64_t match_type:3;
		uपूर्णांक64_t reserved_19_19:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t reserved_23_23:1;
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t reserved_28_31:4;
		uपूर्णांक64_t mask:16;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_pip_raw_word अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_raw_word_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_56_63:8;
		uपूर्णांक64_t word:56;
#अन्यथा
		uपूर्णांक64_t word:56;
		uपूर्णांक64_t reserved_56_63:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_sft_rst अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_sft_rst_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t rst:1;
#अन्यथा
		uपूर्णांक64_t rst:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat0_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat0_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t drp_pkts:32;
		uपूर्णांक64_t drp_octs:32;
#अन्यथा
		uपूर्णांक64_t drp_octs:32;
		uपूर्णांक64_t drp_pkts:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat0_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat0_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t drp_pkts:32;
		uपूर्णांक64_t drp_octs:32;
#अन्यथा
		uपूर्णांक64_t drp_octs:32;
		uपूर्णांक64_t drp_pkts:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat10_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat10_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bcast:32;
		uपूर्णांक64_t mcast:32;
#अन्यथा
		uपूर्णांक64_t mcast:32;
		uपूर्णांक64_t bcast:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat10_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat10_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bcast:32;
		uपूर्णांक64_t mcast:32;
#अन्यथा
		uपूर्णांक64_t mcast:32;
		uपूर्णांक64_t bcast:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat11_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat11_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bcast:32;
		uपूर्णांक64_t mcast:32;
#अन्यथा
		uपूर्णांक64_t mcast:32;
		uपूर्णांक64_t bcast:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat11_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat11_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bcast:32;
		uपूर्णांक64_t mcast:32;
#अन्यथा
		uपूर्णांक64_t mcast:32;
		uपूर्णांक64_t bcast:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat1_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat1_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t octs:48;
#अन्यथा
		uपूर्णांक64_t octs:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat1_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat1_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t octs:48;
#अन्यथा
		uपूर्णांक64_t octs:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat2_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat2_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pkts:32;
		uपूर्णांक64_t raw:32;
#अन्यथा
		uपूर्णांक64_t raw:32;
		uपूर्णांक64_t pkts:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat2_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat2_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pkts:32;
		uपूर्णांक64_t raw:32;
#अन्यथा
		uपूर्णांक64_t raw:32;
		uपूर्णांक64_t pkts:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat3_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat3_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bcst:32;
		uपूर्णांक64_t mcst:32;
#अन्यथा
		uपूर्णांक64_t mcst:32;
		uपूर्णांक64_t bcst:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat3_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat3_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bcst:32;
		uपूर्णांक64_t mcst:32;
#अन्यथा
		uपूर्णांक64_t mcst:32;
		uपूर्णांक64_t bcst:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat4_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat4_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t h65to127:32;
		uपूर्णांक64_t h64:32;
#अन्यथा
		uपूर्णांक64_t h64:32;
		uपूर्णांक64_t h65to127:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat4_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat4_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t h65to127:32;
		uपूर्णांक64_t h64:32;
#अन्यथा
		uपूर्णांक64_t h64:32;
		uपूर्णांक64_t h65to127:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat5_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat5_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t h256to511:32;
		uपूर्णांक64_t h128to255:32;
#अन्यथा
		uपूर्णांक64_t h128to255:32;
		uपूर्णांक64_t h256to511:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat5_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat5_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t h256to511:32;
		uपूर्णांक64_t h128to255:32;
#अन्यथा
		uपूर्णांक64_t h128to255:32;
		uपूर्णांक64_t h256to511:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat6_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat6_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t h1024to1518:32;
		uपूर्णांक64_t h512to1023:32;
#अन्यथा
		uपूर्णांक64_t h512to1023:32;
		uपूर्णांक64_t h1024to1518:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat6_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat6_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t h1024to1518:32;
		uपूर्णांक64_t h512to1023:32;
#अन्यथा
		uपूर्णांक64_t h512to1023:32;
		uपूर्णांक64_t h1024to1518:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat7_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat7_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t fcs:32;
		uपूर्णांक64_t h1519:32;
#अन्यथा
		uपूर्णांक64_t h1519:32;
		uपूर्णांक64_t fcs:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat7_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat7_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t fcs:32;
		uपूर्णांक64_t h1519:32;
#अन्यथा
		uपूर्णांक64_t h1519:32;
		uपूर्णांक64_t fcs:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat8_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat8_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t frag:32;
		uपूर्णांक64_t undersz:32;
#अन्यथा
		uपूर्णांक64_t undersz:32;
		uपूर्णांक64_t frag:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat8_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat8_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t frag:32;
		uपूर्णांक64_t undersz:32;
#अन्यथा
		uपूर्णांक64_t undersz:32;
		uपूर्णांक64_t frag:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat9_x अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat9_x_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t jabber:32;
		uपूर्णांक64_t oversz:32;
#अन्यथा
		uपूर्णांक64_t oversz:32;
		uपूर्णांक64_t jabber:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat9_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat9_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t jabber:32;
		uपूर्णांक64_t oversz:32;
#अन्यथा
		uपूर्णांक64_t oversz:32;
		uपूर्णांक64_t jabber:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t reserved_1_7:7;
		uपूर्णांक64_t rdclr:1;
#अन्यथा
		uपूर्णांक64_t rdclr:1;
		uपूर्णांक64_t reserved_1_7:7;
		uपूर्णांक64_t mode:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pip_stat_ctl_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_1_63:63;
		uपूर्णांक64_t rdclr:1;
#अन्यथा
		uपूर्णांक64_t rdclr:1;
		uपूर्णांक64_t reserved_1_63:63;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_pip_stat_inb_errsx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat_inb_errsx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t errs:16;
#अन्यथा
		uपूर्णांक64_t errs:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat_inb_errs_pkndx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat_inb_errs_pkndx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t errs:16;
#अन्यथा
		uपूर्णांक64_t errs:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat_inb_octsx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat_inb_octsx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t octs:48;
#अन्यथा
		uपूर्णांक64_t octs:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat_inb_octs_pkndx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat_inb_octs_pkndx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t octs:48;
#अन्यथा
		uपूर्णांक64_t octs:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat_inb_pktsx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat_inb_pktsx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t pkts:32;
#अन्यथा
		uपूर्णांक64_t pkts:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_stat_inb_pkts_pkndx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_stat_inb_pkts_pkndx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t pkts:32;
#अन्यथा
		uपूर्णांक64_t pkts:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_sub_pkind_fcsx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_sub_pkind_fcsx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t port_bit:64;
#अन्यथा
		uपूर्णांक64_t port_bit:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_tag_incx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_tag_incx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_8_63:56;
		uपूर्णांक64_t en:8;
#अन्यथा
		uपूर्णांक64_t en:8;
		uपूर्णांक64_t reserved_8_63:56;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_tag_mask अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_tag_mask_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t mask:16;
#अन्यथा
		uपूर्णांक64_t mask:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_tag_secret अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_tag_secret_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t dst:16;
		uपूर्णांक64_t src:16;
#अन्यथा
		uपूर्णांक64_t src:16;
		uपूर्णांक64_t dst:16;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_toकरो_entry अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_toकरो_entry_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t val:1;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t entry:62;
#अन्यथा
		uपूर्णांक64_t entry:62;
		uपूर्णांक64_t reserved_62_62:1;
		uपूर्णांक64_t val:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_vlan_etypesx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_vlan_etypesx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t type3:16;
		uपूर्णांक64_t type2:16;
		uपूर्णांक64_t type1:16;
		uपूर्णांक64_t type0:16;
#अन्यथा
		uपूर्णांक64_t type0:16;
		uपूर्णांक64_t type1:16;
		uपूर्णांक64_t type2:16;
		uपूर्णांक64_t type3:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat0_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat0_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t drp_pkts:32;
		uपूर्णांक64_t drp_octs:32;
#अन्यथा
		uपूर्णांक64_t drp_octs:32;
		uपूर्णांक64_t drp_pkts:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat10_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat10_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bcast:32;
		uपूर्णांक64_t mcast:32;
#अन्यथा
		uपूर्णांक64_t mcast:32;
		uपूर्णांक64_t bcast:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat11_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat11_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bcast:32;
		uपूर्णांक64_t mcast:32;
#अन्यथा
		uपूर्णांक64_t mcast:32;
		uपूर्णांक64_t bcast:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat1_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat1_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t octs:48;
#अन्यथा
		uपूर्णांक64_t octs:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat2_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat2_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t pkts:32;
		uपूर्णांक64_t raw:32;
#अन्यथा
		uपूर्णांक64_t raw:32;
		uपूर्णांक64_t pkts:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat3_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat3_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bcst:32;
		uपूर्णांक64_t mcst:32;
#अन्यथा
		uपूर्णांक64_t mcst:32;
		uपूर्णांक64_t bcst:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat4_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat4_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t h65to127:32;
		uपूर्णांक64_t h64:32;
#अन्यथा
		uपूर्णांक64_t h64:32;
		uपूर्णांक64_t h65to127:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat5_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat5_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t h256to511:32;
		uपूर्णांक64_t h128to255:32;
#अन्यथा
		uपूर्णांक64_t h128to255:32;
		uपूर्णांक64_t h256to511:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat6_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat6_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t h1024to1518:32;
		uपूर्णांक64_t h512to1023:32;
#अन्यथा
		uपूर्णांक64_t h512to1023:32;
		uपूर्णांक64_t h1024to1518:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat7_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat7_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t fcs:32;
		uपूर्णांक64_t h1519:32;
#अन्यथा
		uपूर्णांक64_t h1519:32;
		uपूर्णांक64_t fcs:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat8_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat8_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t frag:32;
		uपूर्णांक64_t undersz:32;
#अन्यथा
		uपूर्णांक64_t undersz:32;
		uपूर्णांक64_t frag:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pip_xstat9_prtx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pip_xstat9_prtx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t jabber:32;
		uपूर्णांक64_t oversz:32;
#अन्यथा
		uपूर्णांक64_t oversz:32;
		uपूर्णांक64_t jabber:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
