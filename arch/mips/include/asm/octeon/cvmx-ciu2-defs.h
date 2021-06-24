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

#अगर_अघोषित __CVMX_CIU2_DEFS_H__
#घोषणा __CVMX_CIU2_DEFS_H__

#घोषणा CVMX_CIU2_ACK_PPX_IP2(block_id) (CVMX_ADD_IO_SEG(0x00010701000C0000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_ACK_PPX_IP3(block_id) (CVMX_ADD_IO_SEG(0x00010701000C0200ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_EN_PPX_IP2_RML(block_id) (CVMX_ADD_IO_SEG(0x0001070100092000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_EN_PPX_IP2_WDOG(block_id) (CVMX_ADD_IO_SEG(0x0001070100091000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_EN_PPX_IP2_WRKQ(block_id) (CVMX_ADD_IO_SEG(0x0001070100090000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_EN_PPX_IP2_WRKQ_W1C(block_id) (CVMX_ADD_IO_SEG(0x00010701000B0000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_EN_PPX_IP2_WRKQ_W1S(block_id) (CVMX_ADD_IO_SEG(0x00010701000A0000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_EN_PPX_IP3_MBOX_W1C(block_id) (CVMX_ADD_IO_SEG(0x00010701000B8200ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_EN_PPX_IP3_MBOX_W1S(block_id) (CVMX_ADD_IO_SEG(0x00010701000A8200ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_INTR_CIU_READY (CVMX_ADD_IO_SEG(0x0001070100102008ull))
#घोषणा CVMX_CIU2_RAW_PPX_IP2_WRKQ(block_id) (CVMX_ADD_IO_SEG(0x0001070100040000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_SRC_PPX_IP2_RML(block_id) (CVMX_ADD_IO_SEG(0x0001070100082000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_SRC_PPX_IP2_WDOG(block_id) (CVMX_ADD_IO_SEG(0x0001070100081000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_SRC_PPX_IP2_WRKQ(block_id) (CVMX_ADD_IO_SEG(0x0001070100080000ull) + ((block_id) & 31) * 0x200000ull)
#घोषणा CVMX_CIU2_SUM_PPX_IP2(offset) (CVMX_ADD_IO_SEG(0x0001070100000000ull) + ((offset) & 31) * 8)
#घोषणा CVMX_CIU2_SUM_PPX_IP3(offset) (CVMX_ADD_IO_SEG(0x0001070100000200ull) + ((offset) & 31) * 8)

#पूर्ण_अगर
