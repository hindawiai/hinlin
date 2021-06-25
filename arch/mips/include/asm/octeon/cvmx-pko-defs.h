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

#अगर_अघोषित __CVMX_PKO_DEFS_H__
#घोषणा __CVMX_PKO_DEFS_H__

#घोषणा CVMX_PKO_MEM_COUNT0 (CVMX_ADD_IO_SEG(0x0001180050001080ull))
#घोषणा CVMX_PKO_MEM_COUNT1 (CVMX_ADD_IO_SEG(0x0001180050001088ull))
#घोषणा CVMX_PKO_MEM_DEBUG0 (CVMX_ADD_IO_SEG(0x0001180050001100ull))
#घोषणा CVMX_PKO_MEM_DEBUG1 (CVMX_ADD_IO_SEG(0x0001180050001108ull))
#घोषणा CVMX_PKO_MEM_DEBUG10 (CVMX_ADD_IO_SEG(0x0001180050001150ull))
#घोषणा CVMX_PKO_MEM_DEBUG11 (CVMX_ADD_IO_SEG(0x0001180050001158ull))
#घोषणा CVMX_PKO_MEM_DEBUG12 (CVMX_ADD_IO_SEG(0x0001180050001160ull))
#घोषणा CVMX_PKO_MEM_DEBUG13 (CVMX_ADD_IO_SEG(0x0001180050001168ull))
#घोषणा CVMX_PKO_MEM_DEBUG14 (CVMX_ADD_IO_SEG(0x0001180050001170ull))
#घोषणा CVMX_PKO_MEM_DEBUG2 (CVMX_ADD_IO_SEG(0x0001180050001110ull))
#घोषणा CVMX_PKO_MEM_DEBUG3 (CVMX_ADD_IO_SEG(0x0001180050001118ull))
#घोषणा CVMX_PKO_MEM_DEBUG4 (CVMX_ADD_IO_SEG(0x0001180050001120ull))
#घोषणा CVMX_PKO_MEM_DEBUG5 (CVMX_ADD_IO_SEG(0x0001180050001128ull))
#घोषणा CVMX_PKO_MEM_DEBUG6 (CVMX_ADD_IO_SEG(0x0001180050001130ull))
#घोषणा CVMX_PKO_MEM_DEBUG7 (CVMX_ADD_IO_SEG(0x0001180050001138ull))
#घोषणा CVMX_PKO_MEM_DEBUG8 (CVMX_ADD_IO_SEG(0x0001180050001140ull))
#घोषणा CVMX_PKO_MEM_DEBUG9 (CVMX_ADD_IO_SEG(0x0001180050001148ull))
#घोषणा CVMX_PKO_MEM_IPORT_PTRS (CVMX_ADD_IO_SEG(0x0001180050001030ull))
#घोषणा CVMX_PKO_MEM_IPORT_QOS (CVMX_ADD_IO_SEG(0x0001180050001038ull))
#घोषणा CVMX_PKO_MEM_IQUEUE_PTRS (CVMX_ADD_IO_SEG(0x0001180050001040ull))
#घोषणा CVMX_PKO_MEM_IQUEUE_QOS (CVMX_ADD_IO_SEG(0x0001180050001048ull))
#घोषणा CVMX_PKO_MEM_PORT_PTRS (CVMX_ADD_IO_SEG(0x0001180050001010ull))
#घोषणा CVMX_PKO_MEM_PORT_QOS (CVMX_ADD_IO_SEG(0x0001180050001018ull))
#घोषणा CVMX_PKO_MEM_PORT_RATE0 (CVMX_ADD_IO_SEG(0x0001180050001020ull))
#घोषणा CVMX_PKO_MEM_PORT_RATE1 (CVMX_ADD_IO_SEG(0x0001180050001028ull))
#घोषणा CVMX_PKO_MEM_QUEUE_PTRS (CVMX_ADD_IO_SEG(0x0001180050001000ull))
#घोषणा CVMX_PKO_MEM_QUEUE_QOS (CVMX_ADD_IO_SEG(0x0001180050001008ull))
#घोषणा CVMX_PKO_MEM_THROTTLE_INT (CVMX_ADD_IO_SEG(0x0001180050001058ull))
#घोषणा CVMX_PKO_MEM_THROTTLE_PIPE (CVMX_ADD_IO_SEG(0x0001180050001050ull))
#घोषणा CVMX_PKO_REG_BIST_RESULT (CVMX_ADD_IO_SEG(0x0001180050000080ull))
#घोषणा CVMX_PKO_REG_CMD_BUF (CVMX_ADD_IO_SEG(0x0001180050000010ull))
#घोषणा CVMX_PKO_REG_CRC_CTLX(offset) (CVMX_ADD_IO_SEG(0x0001180050000028ull) + ((offset) & 1) * 8)
#घोषणा CVMX_PKO_REG_CRC_ENABLE (CVMX_ADD_IO_SEG(0x0001180050000020ull))
#घोषणा CVMX_PKO_REG_CRC_IVX(offset) (CVMX_ADD_IO_SEG(0x0001180050000038ull) + ((offset) & 1) * 8)
#घोषणा CVMX_PKO_REG_DEBUG0 (CVMX_ADD_IO_SEG(0x0001180050000098ull))
#घोषणा CVMX_PKO_REG_DEBUG1 (CVMX_ADD_IO_SEG(0x00011800500000A0ull))
#घोषणा CVMX_PKO_REG_DEBUG2 (CVMX_ADD_IO_SEG(0x00011800500000A8ull))
#घोषणा CVMX_PKO_REG_DEBUG3 (CVMX_ADD_IO_SEG(0x00011800500000B0ull))
#घोषणा CVMX_PKO_REG_DEBUG4 (CVMX_ADD_IO_SEG(0x00011800500000B8ull))
#घोषणा CVMX_PKO_REG_ENGINE_INFLIGHT (CVMX_ADD_IO_SEG(0x0001180050000050ull))
#घोषणा CVMX_PKO_REG_ENGINE_INFLIGHT1 (CVMX_ADD_IO_SEG(0x0001180050000318ull))
#घोषणा CVMX_PKO_REG_ENGINE_STORAGEX(offset) (CVMX_ADD_IO_SEG(0x0001180050000300ull) + ((offset) & 1) * 8)
#घोषणा CVMX_PKO_REG_ENGINE_THRESH (CVMX_ADD_IO_SEG(0x0001180050000058ull))
#घोषणा CVMX_PKO_REG_ERROR (CVMX_ADD_IO_SEG(0x0001180050000088ull))
#घोषणा CVMX_PKO_REG_FLAGS (CVMX_ADD_IO_SEG(0x0001180050000000ull))
#घोषणा CVMX_PKO_REG_GMX_PORT_MODE (CVMX_ADD_IO_SEG(0x0001180050000018ull))
#घोषणा CVMX_PKO_REG_INT_MASK (CVMX_ADD_IO_SEG(0x0001180050000090ull))
#घोषणा CVMX_PKO_REG_LOOPBACK_BPID (CVMX_ADD_IO_SEG(0x0001180050000118ull))
#घोषणा CVMX_PKO_REG_LOOPBACK_PKIND (CVMX_ADD_IO_SEG(0x0001180050000068ull))
#घोषणा CVMX_PKO_REG_MIN_PKT (CVMX_ADD_IO_SEG(0x0001180050000070ull))
#घोषणा CVMX_PKO_REG_PREEMPT (CVMX_ADD_IO_SEG(0x0001180050000110ull))
#घोषणा CVMX_PKO_REG_QUEUE_MODE (CVMX_ADD_IO_SEG(0x0001180050000048ull))
#घोषणा CVMX_PKO_REG_QUEUE_PREEMPT (CVMX_ADD_IO_SEG(0x0001180050000108ull))
#घोषणा CVMX_PKO_REG_QUEUE_PTRS1 (CVMX_ADD_IO_SEG(0x0001180050000100ull))
#घोषणा CVMX_PKO_REG_READ_IDX (CVMX_ADD_IO_SEG(0x0001180050000008ull))
#घोषणा CVMX_PKO_REG_THROTTLE (CVMX_ADD_IO_SEG(0x0001180050000078ull))
#घोषणा CVMX_PKO_REG_TIMESTAMP (CVMX_ADD_IO_SEG(0x0001180050000060ull))

जोड़ cvmx_pko_mem_count0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_count0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t count:32;
#अन्यथा
		uपूर्णांक64_t count:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_count1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_count1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t count:48;
#अन्यथा
		uपूर्णांक64_t count:48;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_debug0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t fau:28;
		uपूर्णांक64_t cmd:14;
		uपूर्णांक64_t segs:6;
		uपूर्णांक64_t size:16;
#अन्यथा
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t segs:6;
		uपूर्णांक64_t cmd:14;
		uपूर्णांक64_t fau:28;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_debug1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t i:1;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t ptr:40;
#अन्यथा
		uपूर्णांक64_t ptr:40;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t i:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_debug10 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug10_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug10_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t fau:28;
		uपूर्णांक64_t cmd:14;
		uपूर्णांक64_t segs:6;
		uपूर्णांक64_t size:16;
#अन्यथा
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t segs:6;
		uपूर्णांक64_t cmd:14;
		uपूर्णांक64_t fau:28;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug10_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t ptrs1:17;
		uपूर्णांक64_t reserved_17_31:15;
		uपूर्णांक64_t ptrs2:17;
#अन्यथा
		uपूर्णांक64_t ptrs2:17;
		uपूर्णांक64_t reserved_17_31:15;
		uपूर्णांक64_t ptrs1:17;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug11 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug11_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t i:1;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t reserved_0_39:40;
#अन्यथा
		uपूर्णांक64_t reserved_0_39:40;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t i:1;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug11_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t i:1;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t ptr:40;
#अन्यथा
		uपूर्णांक64_t ptr:40;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t i:1;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug11_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t maj:1;
		uपूर्णांक64_t uid:3;
		uपूर्णांक64_t sop:1;
		uपूर्णांक64_t len:1;
		uपूर्णांक64_t chk:1;
		uपूर्णांक64_t cnt:13;
		uपूर्णांक64_t mod:3;
#अन्यथा
		uपूर्णांक64_t mod:3;
		uपूर्णांक64_t cnt:13;
		uपूर्णांक64_t chk:1;
		uपूर्णांक64_t len:1;
		uपूर्णांक64_t sop:1;
		uपूर्णांक64_t uid:3;
		uपूर्णांक64_t maj:1;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug12 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug12_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug12_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug12_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t fau:28;
		uपूर्णांक64_t cmd:14;
		uपूर्णांक64_t segs:6;
		uपूर्णांक64_t size:16;
#अन्यथा
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t segs:6;
		uपूर्णांक64_t cmd:14;
		uपूर्णांक64_t fau:28;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pko_mem_debug12_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t state:64;
#अन्यथा
		uपूर्णांक64_t state:64;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug13 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug13_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug13_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_51_63:13;
		uपूर्णांक64_t widx:17;
		uपूर्णांक64_t ridx2:17;
		uपूर्णांक64_t widx2:17;
#अन्यथा
		uपूर्णांक64_t widx2:17;
		uपूर्णांक64_t ridx2:17;
		uपूर्णांक64_t widx:17;
		uपूर्णांक64_t reserved_51_63:13;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug13_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t i:1;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t ptr:40;
#अन्यथा
		uपूर्णांक64_t ptr:40;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t i:1;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pko_mem_debug13_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t state:64;
#अन्यथा
		uपूर्णांक64_t state:64;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug14 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug14_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug14_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t ridx:17;
#अन्यथा
		uपूर्णांक64_t ridx:17;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug14_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t i:1;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t ptr:40;
#अन्यथा
		uपूर्णांक64_t ptr:40;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t i:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_debug3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug3_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t i:1;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t ptr:40;
#अन्यथा
		uपूर्णांक64_t ptr:40;
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t back:4;
		uपूर्णांक64_t i:1;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug3_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug4 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug4_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug4_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t data:64;
#अन्यथा
		uपूर्णांक64_t data:64;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug4_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t cmnd_segs:3;
		uपूर्णांक64_t cmnd_siz:16;
		uपूर्णांक64_t cmnd_off:6;
		uपूर्णांक64_t uid:3;
		uपूर्णांक64_t dपढ़ो_sop:1;
		uपूर्णांक64_t init_dग_लिखो:1;
		uपूर्णांक64_t chk_once:1;
		uपूर्णांक64_t chk_mode:1;
		uपूर्णांक64_t active:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qcb_ridx:5;
		uपूर्णांक64_t qid_off_max:4;
		uपूर्णांक64_t qid_off:4;
		uपूर्णांक64_t qid_base:8;
		uपूर्णांक64_t रुको:1;
		uपूर्णांक64_t minor:2;
		uपूर्णांक64_t major:3;
#अन्यथा
		uपूर्णांक64_t major:3;
		uपूर्णांक64_t minor:2;
		uपूर्णांक64_t रुको:1;
		uपूर्णांक64_t qid_base:8;
		uपूर्णांक64_t qid_off:4;
		uपूर्णांक64_t qid_off_max:4;
		uपूर्णांक64_t qcb_ridx:5;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t active:1;
		uपूर्णांक64_t chk_mode:1;
		uपूर्णांक64_t chk_once:1;
		uपूर्णांक64_t init_dग_लिखो:1;
		uपूर्णांक64_t dपढ़ो_sop:1;
		uपूर्णांक64_t uid:3;
		uपूर्णांक64_t cmnd_off:6;
		uपूर्णांक64_t cmnd_siz:16;
		uपूर्णांक64_t cmnd_segs:3;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pko_mem_debug4_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t curr_siz:8;
		uपूर्णांक64_t curr_off:16;
		uपूर्णांक64_t cmnd_segs:6;
		uपूर्णांक64_t cmnd_siz:16;
		uपूर्णांक64_t cmnd_off:6;
		uपूर्णांक64_t uid:2;
		uपूर्णांक64_t dपढ़ो_sop:1;
		uपूर्णांक64_t init_dग_लिखो:1;
		uपूर्णांक64_t chk_once:1;
		uपूर्णांक64_t chk_mode:1;
		uपूर्णांक64_t रुको:1;
		uपूर्णांक64_t minor:2;
		uपूर्णांक64_t major:3;
#अन्यथा
		uपूर्णांक64_t major:3;
		uपूर्णांक64_t minor:2;
		uपूर्णांक64_t रुको:1;
		uपूर्णांक64_t chk_mode:1;
		uपूर्णांक64_t chk_once:1;
		uपूर्णांक64_t init_dग_लिखो:1;
		uपूर्णांक64_t dपढ़ो_sop:1;
		uपूर्णांक64_t uid:2;
		uपूर्णांक64_t cmnd_off:6;
		uपूर्णांक64_t cmnd_siz:16;
		uपूर्णांक64_t cmnd_segs:6;
		uपूर्णांक64_t curr_off:16;
		uपूर्णांक64_t curr_siz:8;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug5 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug5_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug5_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t dwri_mod:1;
		uपूर्णांक64_t dwri_sop:1;
		uपूर्णांक64_t dwri_len:1;
		uपूर्णांक64_t dwri_cnt:13;
		uपूर्णांक64_t cmnd_siz:16;
		uपूर्णांक64_t uid:1;
		uपूर्णांक64_t xfer_wor:1;
		uपूर्णांक64_t xfer_dwr:1;
		uपूर्णांक64_t cbuf_fre:1;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t chk_mode:1;
		uपूर्णांक64_t active:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qcb_ridx:5;
		uपूर्णांक64_t qid_off:3;
		uपूर्णांक64_t qid_base:7;
		uपूर्णांक64_t रुको:1;
		uपूर्णांक64_t minor:2;
		uपूर्णांक64_t major:4;
#अन्यथा
		uपूर्णांक64_t major:4;
		uपूर्णांक64_t minor:2;
		uपूर्णांक64_t रुको:1;
		uपूर्णांक64_t qid_base:7;
		uपूर्णांक64_t qid_off:3;
		uपूर्णांक64_t qcb_ridx:5;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t active:1;
		uपूर्णांक64_t chk_mode:1;
		uपूर्णांक64_t reserved_27_27:1;
		uपूर्णांक64_t cbuf_fre:1;
		uपूर्णांक64_t xfer_dwr:1;
		uपूर्णांक64_t xfer_wor:1;
		uपूर्णांक64_t uid:1;
		uपूर्णांक64_t cmnd_siz:16;
		uपूर्णांक64_t dwri_cnt:13;
		uपूर्णांक64_t dwri_len:1;
		uपूर्णांक64_t dwri_sop:1;
		uपूर्णांक64_t dwri_mod:1;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug5_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t curr_ptr:29;
		uपूर्णांक64_t curr_siz:16;
		uपूर्णांक64_t curr_off:16;
		uपूर्णांक64_t cmnd_segs:3;
#अन्यथा
		uपूर्णांक64_t cmnd_segs:3;
		uपूर्णांक64_t curr_off:16;
		uपूर्णांक64_t curr_siz:16;
		uपूर्णांक64_t curr_ptr:29;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pko_mem_debug5_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_54_63:10;
		uपूर्णांक64_t nxt_inflt:6;
		uपूर्णांक64_t curr_ptr:40;
		uपूर्णांक64_t curr_siz:8;
#अन्यथा
		uपूर्णांक64_t curr_siz:8;
		uपूर्णांक64_t curr_ptr:40;
		uपूर्णांक64_t nxt_inflt:6;
		uपूर्णांक64_t reserved_54_63:10;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pko_mem_debug5_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_56_63:8;
		uपूर्णांक64_t ptp:1;
		uपूर्णांक64_t major_3:1;
		uपूर्णांक64_t nxt_inflt:6;
		uपूर्णांक64_t curr_ptr:40;
		uपूर्णांक64_t curr_siz:8;
#अन्यथा
		uपूर्णांक64_t curr_siz:8;
		uपूर्णांक64_t curr_ptr:40;
		uपूर्णांक64_t nxt_inflt:6;
		uपूर्णांक64_t major_3:1;
		uपूर्णांक64_t ptp:1;
		uपूर्णांक64_t reserved_56_63:8;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_pko_mem_debug5_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_57_63:7;
		uपूर्णांक64_t uid_2:1;
		uपूर्णांक64_t ptp:1;
		uपूर्णांक64_t major_3:1;
		uपूर्णांक64_t nxt_inflt:6;
		uपूर्णांक64_t curr_ptr:40;
		uपूर्णांक64_t curr_siz:8;
#अन्यथा
		uपूर्णांक64_t curr_siz:8;
		uपूर्णांक64_t curr_ptr:40;
		uपूर्णांक64_t nxt_inflt:6;
		uपूर्णांक64_t major_3:1;
		uपूर्णांक64_t ptp:1;
		uपूर्णांक64_t uid_2:1;
		uपूर्णांक64_t reserved_57_63:7;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug6 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug6_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t qid_offres:4;
		uपूर्णांक64_t qid_offths:4;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t preempted:1;
		uपूर्णांक64_t active:1;
		uपूर्णांक64_t statc:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qcb_ridx:5;
		uपूर्णांक64_t qid_offmax:4;
		uपूर्णांक64_t reserved_0_11:12;
#अन्यथा
		uपूर्णांक64_t reserved_0_11:12;
		uपूर्णांक64_t qid_offmax:4;
		uपूर्णांक64_t qcb_ridx:5;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t statc:1;
		uपूर्णांक64_t active:1;
		uपूर्णांक64_t preempted:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t qid_offths:4;
		uपूर्णांक64_t qid_offres:4;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug6_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t qid_offm:3;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t work_min:3;
		uपूर्णांक64_t dwri_chk:1;
		uपूर्णांक64_t dwri_uid:1;
		uपूर्णांक64_t dwri_mod:2;
#अन्यथा
		uपूर्णांक64_t dwri_mod:2;
		uपूर्णांक64_t dwri_uid:1;
		uपूर्णांक64_t dwri_chk:1;
		uपूर्णांक64_t work_min:3;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t qid_offm:3;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug6_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_11_63:53;
		uपूर्णांक64_t curr_ptr:11;
#अन्यथा
		uपूर्णांक64_t curr_ptr:11;
		uपूर्णांक64_t reserved_11_63:53;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pko_mem_debug6_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t qid_offres:4;
		uपूर्णांक64_t qid_offths:4;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t preempted:1;
		uपूर्णांक64_t active:1;
		uपूर्णांक64_t statc:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t qcb_ridx:5;
		uपूर्णांक64_t qid_offmax:4;
		uपूर्णांक64_t qid_off:4;
		uपूर्णांक64_t qid_base:8;
#अन्यथा
		uपूर्णांक64_t qid_base:8;
		uपूर्णांक64_t qid_off:4;
		uपूर्णांक64_t qid_offmax:4;
		uपूर्णांक64_t qcb_ridx:5;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t statc:1;
		uपूर्णांक64_t active:1;
		uपूर्णांक64_t preempted:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t qid_offths:4;
		uपूर्णांक64_t qid_offres:4;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug7 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug7_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug7_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_58_63:6;
		uपूर्णांक64_t dwb:9;
		uपूर्णांक64_t start:33;
		uपूर्णांक64_t size:16;
#अन्यथा
		uपूर्णांक64_t size:16;
		uपूर्णांक64_t start:33;
		uपूर्णांक64_t dwb:9;
		uपूर्णांक64_t reserved_58_63:6;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug7_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t qos:5;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t buf_siz:13;
		uपूर्णांक64_t buf_ptr:33;
		uपूर्णांक64_t qcb_widx:6;
		uपूर्णांक64_t qcb_ridx:6;
#अन्यथा
		uपूर्णांक64_t qcb_ridx:6;
		uपूर्णांक64_t qcb_widx:6;
		uपूर्णांक64_t buf_ptr:33;
		uपूर्णांक64_t buf_siz:13;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t qos:5;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pko_mem_debug7_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t buf_siz:13;
		uपूर्णांक64_t buf_ptr:33;
		uपूर्णांक64_t qcb_widx:7;
		uपूर्णांक64_t qcb_ridx:7;
#अन्यथा
		uपूर्णांक64_t qcb_ridx:7;
		uपूर्णांक64_t qcb_widx:7;
		uपूर्णांक64_t buf_ptr:33;
		uपूर्णांक64_t buf_siz:13;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t qos:3;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug8 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug8_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t buf_siz:13;
		uपूर्णांक64_t reserved_0_44:45;
#अन्यथा
		uपूर्णांक64_t reserved_0_44:45;
		uपूर्णांक64_t buf_siz:13;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug8_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t qos:5;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t buf_siz:13;
		uपूर्णांक64_t buf_ptr:33;
		uपूर्णांक64_t qcb_widx:6;
		uपूर्णांक64_t qcb_ridx:6;
#अन्यथा
		uपूर्णांक64_t qcb_ridx:6;
		uपूर्णांक64_t qcb_widx:6;
		uपूर्णांक64_t buf_ptr:33;
		uपूर्णांक64_t buf_siz:13;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t qos:5;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug8_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pko_mem_debug8_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_29_63:35;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t reserved_29_63:35;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pko_mem_debug8_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_42_63:22;
		uपूर्णांक64_t qid_qqos:8;
		uपूर्णांक64_t reserved_33_33:1;
		uपूर्णांक64_t qid_idx:4;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t qid_idx:4;
		uपूर्णांक64_t reserved_33_33:1;
		uपूर्णांक64_t qid_qqos:8;
		uपूर्णांक64_t reserved_42_63:22;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_pko_mem_debug8_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_37_63:27;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t qos:5;
#अन्यथा
		uपूर्णांक64_t qos:5;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t reserved_9_15:7;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t reserved_37_63:27;
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_pko_mem_debug9 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_debug9_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t ptrs0:17;
		uपूर्णांक64_t reserved_0_31:32;
#अन्यथा
		uपूर्णांक64_t reserved_0_31:32;
		uपूर्णांक64_t ptrs0:17;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_debug9_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_mem_debug9_cn38xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_28_63:36;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t qos:3;
#अन्यथा
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t करोorbell:20;
		uपूर्णांक64_t reserved_28_63:36;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा cvmx_pko_mem_debug9_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_49_63:15;
		uपूर्णांक64_t ptrs0:17;
		uपूर्णांक64_t reserved_17_31:15;
		uपूर्णांक64_t ptrs3:17;
#अन्यथा
		uपूर्णांक64_t ptrs3:17;
		uपूर्णांक64_t reserved_17_31:15;
		uपूर्णांक64_t ptrs0:17;
		uपूर्णांक64_t reserved_49_63:15;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_pko_mem_iport_ptrs अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_iport_ptrs_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_63_63:1;
		uपूर्णांक64_t crc:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t min_pkt:3;
		uपूर्णांक64_t reserved_31_49:19;
		uपूर्णांक64_t pipe:7;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t पूर्णांकr:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t eid:5;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t ipid:7;
#अन्यथा
		uपूर्णांक64_t ipid:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t eid:5;
		uपूर्णांक64_t reserved_13_15:3;
		uपूर्णांक64_t पूर्णांकr:5;
		uपूर्णांक64_t reserved_21_23:3;
		uपूर्णांक64_t pipe:7;
		uपूर्णांक64_t reserved_31_49:19;
		uपूर्णांक64_t min_pkt:3;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t crc:1;
		uपूर्णांक64_t reserved_63_63:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_iport_qos अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_iport_qos_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_61_63:3;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t reserved_13_52:40;
		uपूर्णांक64_t eid:5;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t ipid:7;
#अन्यथा
		uपूर्णांक64_t ipid:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t eid:5;
		uपूर्णांक64_t reserved_13_52:40;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t reserved_61_63:3;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_iqueue_ptrs अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_iqueue_ptrs_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t buf_ptr:31;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t index:5;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t ipid:7;
		uपूर्णांक64_t qid:8;
#अन्यथा
		uपूर्णांक64_t qid:8;
		uपूर्णांक64_t ipid:7;
		uपूर्णांक64_t reserved_15_15:1;
		uपूर्णांक64_t index:5;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t buf_ptr:31;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t s_tail:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_iqueue_qos अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_iqueue_qos_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_61_63:3;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t reserved_15_52:38;
		uपूर्णांक64_t ipid:7;
		uपूर्णांक64_t qid:8;
#अन्यथा
		uपूर्णांक64_t qid:8;
		uपूर्णांक64_t ipid:7;
		uपूर्णांक64_t reserved_15_52:38;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t reserved_61_63:3;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_port_ptrs अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_port_ptrs_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t reserved_16_52:37;
		uपूर्णांक64_t bp_port:6;
		uपूर्णांक64_t eid:4;
		uपूर्णांक64_t pid:6;
#अन्यथा
		uपूर्णांक64_t pid:6;
		uपूर्णांक64_t eid:4;
		uपूर्णांक64_t bp_port:6;
		uपूर्णांक64_t reserved_16_52:37;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_port_qos अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_port_qos_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_61_63:3;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t reserved_10_52:43;
		uपूर्णांक64_t eid:4;
		uपूर्णांक64_t pid:6;
#अन्यथा
		uपूर्णांक64_t pid:6;
		uपूर्णांक64_t eid:4;
		uपूर्णांक64_t reserved_10_52:43;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t reserved_61_63:3;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_port_rate0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_port_rate0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_51_63:13;
		uपूर्णांक64_t rate_word:19;
		uपूर्णांक64_t rate_pkt:24;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t pid:7;
#अन्यथा
		uपूर्णांक64_t pid:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t rate_pkt:24;
		uपूर्णांक64_t rate_word:19;
		uपूर्णांक64_t reserved_51_63:13;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_port_rate0_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_51_63:13;
		uपूर्णांक64_t rate_word:19;
		uपूर्णांक64_t rate_pkt:24;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t pid:6;
#अन्यथा
		uपूर्णांक64_t pid:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t rate_pkt:24;
		uपूर्णांक64_t rate_word:19;
		uपूर्णांक64_t reserved_51_63:13;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_pko_mem_port_rate1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_port_rate1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rate_lim:24;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t pid:7;
#अन्यथा
		uपूर्णांक64_t pid:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t rate_lim:24;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_mem_port_rate1_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t rate_lim:24;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t pid:6;
#अन्यथा
		uपूर्णांक64_t pid:6;
		uपूर्णांक64_t reserved_6_7:2;
		uपूर्णांक64_t rate_lim:24;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण cn52xx;
पूर्ण;

जोड़ cvmx_pko_mem_queue_ptrs अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_queue_ptrs_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t s_tail:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t buf_ptr:36;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t index:3;
		uपूर्णांक64_t port:6;
		uपूर्णांक64_t queue:7;
#अन्यथा
		uपूर्णांक64_t queue:7;
		uपूर्णांक64_t port:6;
		uपूर्णांक64_t index:3;
		uपूर्णांक64_t tail:1;
		uपूर्णांक64_t buf_ptr:36;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t अटल_q:1;
		uपूर्णांक64_t अटल_p:1;
		uपूर्णांक64_t s_tail:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_queue_qos अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_queue_qos_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_61_63:3;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t reserved_13_52:40;
		uपूर्णांक64_t pid:6;
		uपूर्णांक64_t qid:7;
#अन्यथा
		uपूर्णांक64_t qid:7;
		uपूर्णांक64_t pid:6;
		uपूर्णांक64_t reserved_13_52:40;
		uपूर्णांक64_t qos_mask:8;
		uपूर्णांक64_t reserved_61_63:3;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_throttle_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_throttle_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_47_63:17;
		uपूर्णांक64_t word:15;
		uपूर्णांक64_t reserved_14_31:18;
		uपूर्णांक64_t packet:6;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t पूर्णांकr:5;
#अन्यथा
		uपूर्णांक64_t पूर्णांकr:5;
		uपूर्णांक64_t reserved_5_7:3;
		uपूर्णांक64_t packet:6;
		uपूर्णांक64_t reserved_14_31:18;
		uपूर्णांक64_t word:15;
		uपूर्णांक64_t reserved_47_63:17;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_mem_throttle_pipe अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_mem_throttle_pipe_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_47_63:17;
		uपूर्णांक64_t word:15;
		uपूर्णांक64_t reserved_14_31:18;
		uपूर्णांक64_t packet:6;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t pipe:7;
#अन्यथा
		uपूर्णांक64_t pipe:7;
		uपूर्णांक64_t reserved_7_7:1;
		uपूर्णांक64_t packet:6;
		uपूर्णांक64_t reserved_14_31:18;
		uपूर्णांक64_t word:15;
		uपूर्णांक64_t reserved_47_63:17;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_bist_result अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_bist_result_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_0_63:64;
#अन्यथा
		uपूर्णांक64_t reserved_0_63:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_reg_bist_result_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_27_63:37;
		uपूर्णांक64_t psb2:5;
		uपूर्णांक64_t count:1;
		uपूर्णांक64_t rअगर:1;
		uपूर्णांक64_t wअगर:1;
		uपूर्णांक64_t ncb:1;
		uपूर्णांक64_t out:1;
		uपूर्णांक64_t crc:1;
		uपूर्णांक64_t chk:1;
		uपूर्णांक64_t qsb:2;
		uपूर्णांक64_t qcb:2;
		uपूर्णांक64_t pdb:4;
		uपूर्णांक64_t psb:7;
#अन्यथा
		uपूर्णांक64_t psb:7;
		uपूर्णांक64_t pdb:4;
		uपूर्णांक64_t qcb:2;
		uपूर्णांक64_t qsb:2;
		uपूर्णांक64_t chk:1;
		uपूर्णांक64_t crc:1;
		uपूर्णांक64_t out:1;
		uपूर्णांक64_t ncb:1;
		uपूर्णांक64_t wअगर:1;
		uपूर्णांक64_t rअगर:1;
		uपूर्णांक64_t count:1;
		uपूर्णांक64_t psb2:5;
		uपूर्णांक64_t reserved_27_63:37;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_reg_bist_result_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_33_63:31;
		uपूर्णांक64_t csr:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t out_crc:1;
		uपूर्णांक64_t out_ctl:3;
		uपूर्णांक64_t out_sta:1;
		uपूर्णांक64_t out_wअगर:1;
		uपूर्णांक64_t prt_chk:3;
		uपूर्णांक64_t prt_nxt:1;
		uपूर्णांक64_t prt_psb:6;
		uपूर्णांक64_t ncb_inb:2;
		uपूर्णांक64_t prt_qcb:2;
		uपूर्णांक64_t prt_qsb:3;
		uपूर्णांक64_t dat_dat:4;
		uपूर्णांक64_t dat_ptr:4;
#अन्यथा
		uपूर्णांक64_t dat_ptr:4;
		uपूर्णांक64_t dat_dat:4;
		uपूर्णांक64_t prt_qsb:3;
		uपूर्णांक64_t prt_qcb:2;
		uपूर्णांक64_t ncb_inb:2;
		uपूर्णांक64_t prt_psb:6;
		uपूर्णांक64_t prt_nxt:1;
		uपूर्णांक64_t prt_chk:3;
		uपूर्णांक64_t out_wअगर:1;
		uपूर्णांक64_t out_sta:1;
		uपूर्णांक64_t out_ctl:3;
		uपूर्णांक64_t out_crc:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t csr:1;
		uपूर्णांक64_t reserved_33_63:31;
#पूर्ण_अगर
	पूर्ण cn50xx;
	काष्ठा cvmx_pko_reg_bist_result_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_35_63:29;
		uपूर्णांक64_t csr:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t out_dat:1;
		uपूर्णांक64_t out_ctl:3;
		uपूर्णांक64_t out_sta:1;
		uपूर्णांक64_t out_wअगर:1;
		uपूर्णांक64_t prt_chk:3;
		uपूर्णांक64_t prt_nxt:1;
		uपूर्णांक64_t prt_psb:8;
		uपूर्णांक64_t ncb_inb:2;
		uपूर्णांक64_t prt_qcb:2;
		uपूर्णांक64_t prt_qsb:3;
		uपूर्णांक64_t prt_ctl:2;
		uपूर्णांक64_t dat_dat:2;
		uपूर्णांक64_t dat_ptr:4;
#अन्यथा
		uपूर्णांक64_t dat_ptr:4;
		uपूर्णांक64_t dat_dat:2;
		uपूर्णांक64_t prt_ctl:2;
		uपूर्णांक64_t prt_qsb:3;
		uपूर्णांक64_t prt_qcb:2;
		uपूर्णांक64_t ncb_inb:2;
		uपूर्णांक64_t prt_psb:8;
		uपूर्णांक64_t prt_nxt:1;
		uपूर्णांक64_t prt_chk:3;
		uपूर्णांक64_t out_wअगर:1;
		uपूर्णांक64_t out_sta:1;
		uपूर्णांक64_t out_ctl:3;
		uपूर्णांक64_t out_dat:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t csr:1;
		uपूर्णांक64_t reserved_35_63:29;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pko_reg_bist_result_cn68xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_36_63:28;
		uपूर्णांक64_t crc:1;
		uपूर्णांक64_t csr:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t out_dat:1;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t out_ctl:2;
		uपूर्णांक64_t out_sta:1;
		uपूर्णांक64_t out_wअगर:1;
		uपूर्णांक64_t prt_chk:3;
		uपूर्णांक64_t prt_nxt:1;
		uपूर्णांक64_t prt_psb7:1;
		uपूर्णांक64_t reserved_21_21:1;
		uपूर्णांक64_t prt_psb:6;
		uपूर्णांक64_t ncb_inb:2;
		uपूर्णांक64_t prt_qcb:2;
		uपूर्णांक64_t prt_qsb:3;
		uपूर्णांक64_t prt_ctl:2;
		uपूर्णांक64_t dat_dat:2;
		uपूर्णांक64_t dat_ptr:4;
#अन्यथा
		uपूर्णांक64_t dat_ptr:4;
		uपूर्णांक64_t dat_dat:2;
		uपूर्णांक64_t prt_ctl:2;
		uपूर्णांक64_t prt_qsb:3;
		uपूर्णांक64_t prt_qcb:2;
		uपूर्णांक64_t ncb_inb:2;
		uपूर्णांक64_t prt_psb:6;
		uपूर्णांक64_t reserved_21_21:1;
		uपूर्णांक64_t prt_psb7:1;
		uपूर्णांक64_t prt_nxt:1;
		uपूर्णांक64_t prt_chk:3;
		uपूर्णांक64_t out_wअगर:1;
		uपूर्णांक64_t out_sta:1;
		uपूर्णांक64_t out_ctl:2;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t out_dat:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t csr:1;
		uपूर्णांक64_t crc:1;
		uपूर्णांक64_t reserved_36_63:28;
#पूर्ण_अगर
	पूर्ण cn68xx;
	काष्ठा cvmx_pko_reg_bist_result_cn68xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_35_63:29;
		uपूर्णांक64_t csr:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t out_dat:1;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t out_ctl:2;
		uपूर्णांक64_t out_sta:1;
		uपूर्णांक64_t out_wअगर:1;
		uपूर्णांक64_t prt_chk:3;
		uपूर्णांक64_t prt_nxt:1;
		uपूर्णांक64_t prt_psb7:1;
		uपूर्णांक64_t reserved_21_21:1;
		uपूर्णांक64_t prt_psb:6;
		uपूर्णांक64_t ncb_inb:2;
		uपूर्णांक64_t prt_qcb:2;
		uपूर्णांक64_t prt_qsb:3;
		uपूर्णांक64_t prt_ctl:2;
		uपूर्णांक64_t dat_dat:2;
		uपूर्णांक64_t dat_ptr:4;
#अन्यथा
		uपूर्णांक64_t dat_ptr:4;
		uपूर्णांक64_t dat_dat:2;
		uपूर्णांक64_t prt_ctl:2;
		uपूर्णांक64_t prt_qsb:3;
		uपूर्णांक64_t prt_qcb:2;
		uपूर्णांक64_t ncb_inb:2;
		uपूर्णांक64_t prt_psb:6;
		uपूर्णांक64_t reserved_21_21:1;
		uपूर्णांक64_t prt_psb7:1;
		uपूर्णांक64_t prt_nxt:1;
		uपूर्णांक64_t prt_chk:3;
		uपूर्णांक64_t out_wअगर:1;
		uपूर्णांक64_t out_sta:1;
		uपूर्णांक64_t out_ctl:2;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t out_dat:1;
		uपूर्णांक64_t iob:1;
		uपूर्णांक64_t csr:1;
		uपूर्णांक64_t reserved_35_63:29;
#पूर्ण_अगर
	पूर्ण cn68xxp1;
पूर्ण;

जोड़ cvmx_pko_reg_cmd_buf अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_cmd_buf_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_23_63:41;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t reserved_13_19:7;
		uपूर्णांक64_t size:13;
#अन्यथा
		uपूर्णांक64_t size:13;
		uपूर्णांक64_t reserved_13_19:7;
		uपूर्णांक64_t pool:3;
		uपूर्णांक64_t reserved_23_63:41;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_crc_ctlx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_crc_ctlx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t invres:1;
		uपूर्णांक64_t refin:1;
#अन्यथा
		uपूर्णांक64_t refin:1;
		uपूर्णांक64_t invres:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_crc_enable अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_crc_enable_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t enable:32;
#अन्यथा
		uपूर्णांक64_t enable:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_crc_ivx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_crc_ivx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t iv:32;
#अन्यथा
		uपूर्णांक64_t iv:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_debug0 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_debug0_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t निश्चितs:64;
#अन्यथा
		uपूर्णांक64_t निश्चितs:64;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_reg_debug0_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_17_63:47;
		uपूर्णांक64_t निश्चितs:17;
#अन्यथा
		uपूर्णांक64_t निश्चितs:17;
		uपूर्णांक64_t reserved_17_63:47;
#पूर्ण_अगर
	पूर्ण cn30xx;
पूर्ण;

जोड़ cvmx_pko_reg_debug1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_debug1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t निश्चितs:64;
#अन्यथा
		uपूर्णांक64_t निश्चितs:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_debug2 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_debug2_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t निश्चितs:64;
#अन्यथा
		uपूर्णांक64_t निश्चितs:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_debug3 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_debug3_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t निश्चितs:64;
#अन्यथा
		uपूर्णांक64_t निश्चितs:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_debug4 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_debug4_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t निश्चितs:64;
#अन्यथा
		uपूर्णांक64_t निश्चितs:64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_engine_inflight अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_engine_inflight_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t engine15:4;
		uपूर्णांक64_t engine14:4;
		uपूर्णांक64_t engine13:4;
		uपूर्णांक64_t engine12:4;
		uपूर्णांक64_t engine11:4;
		uपूर्णांक64_t engine10:4;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine0:4;
#अन्यथा
		uपूर्णांक64_t engine0:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t engine10:4;
		uपूर्णांक64_t engine11:4;
		uपूर्णांक64_t engine12:4;
		uपूर्णांक64_t engine13:4;
		uपूर्णांक64_t engine14:4;
		uपूर्णांक64_t engine15:4;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_reg_engine_inflight_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_40_63:24;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine0:4;
#अन्यथा
		uपूर्णांक64_t engine0:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t reserved_40_63:24;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pko_reg_engine_inflight_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_56_63:8;
		uपूर्णांक64_t engine13:4;
		uपूर्णांक64_t engine12:4;
		uपूर्णांक64_t engine11:4;
		uपूर्णांक64_t engine10:4;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine0:4;
#अन्यथा
		uपूर्णांक64_t engine0:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t engine10:4;
		uपूर्णांक64_t engine11:4;
		uपूर्णांक64_t engine12:4;
		uपूर्णांक64_t engine13:4;
		uपूर्णांक64_t reserved_56_63:8;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_pko_reg_engine_inflight_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_48_63:16;
		uपूर्णांक64_t engine11:4;
		uपूर्णांक64_t engine10:4;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine0:4;
#अन्यथा
		uपूर्णांक64_t engine0:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t engine10:4;
		uपूर्णांक64_t engine11:4;
		uपूर्णांक64_t reserved_48_63:16;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_pko_reg_engine_inflight1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_engine_inflight1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t engine19:4;
		uपूर्णांक64_t engine18:4;
		uपूर्णांक64_t engine17:4;
		uपूर्णांक64_t engine16:4;
#अन्यथा
		uपूर्णांक64_t engine16:4;
		uपूर्णांक64_t engine17:4;
		uपूर्णांक64_t engine18:4;
		uपूर्णांक64_t engine19:4;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_engine_storagex अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_engine_storagex_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t engine15:4;
		uपूर्णांक64_t engine14:4;
		uपूर्णांक64_t engine13:4;
		uपूर्णांक64_t engine12:4;
		uपूर्णांक64_t engine11:4;
		uपूर्णांक64_t engine10:4;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine0:4;
#अन्यथा
		uपूर्णांक64_t engine0:4;
		uपूर्णांक64_t engine1:4;
		uपूर्णांक64_t engine2:4;
		uपूर्णांक64_t engine3:4;
		uपूर्णांक64_t engine4:4;
		uपूर्णांक64_t engine5:4;
		uपूर्णांक64_t engine6:4;
		uपूर्णांक64_t engine7:4;
		uपूर्णांक64_t engine8:4;
		uपूर्णांक64_t engine9:4;
		uपूर्णांक64_t engine10:4;
		uपूर्णांक64_t engine11:4;
		uपूर्णांक64_t engine12:4;
		uपूर्णांक64_t engine13:4;
		uपूर्णांक64_t engine14:4;
		uपूर्णांक64_t engine15:4;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_engine_thresh अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_engine_thresh_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_20_63:44;
		uपूर्णांक64_t mask:20;
#अन्यथा
		uपूर्णांक64_t mask:20;
		uपूर्णांक64_t reserved_20_63:44;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_reg_engine_thresh_cn52xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_10_63:54;
		uपूर्णांक64_t mask:10;
#अन्यथा
		uपूर्णांक64_t mask:10;
		uपूर्णांक64_t reserved_10_63:54;
#पूर्ण_अगर
	पूर्ण cn52xx;
	काष्ठा cvmx_pko_reg_engine_thresh_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_14_63:50;
		uपूर्णांक64_t mask:14;
#अन्यथा
		uपूर्णांक64_t mask:14;
		uपूर्णांक64_t reserved_14_63:50;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_pko_reg_engine_thresh_cn63xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_12_63:52;
		uपूर्णांक64_t mask:12;
#अन्यथा
		uपूर्णांक64_t mask:12;
		uपूर्णांक64_t reserved_12_63:52;
#पूर्ण_अगर
	पूर्ण cn63xx;
पूर्ण;

जोड़ cvmx_pko_reg_error अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_error_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t loopback:1;
		uपूर्णांक64_t currzero:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t parity:1;
#अन्यथा
		uपूर्णांक64_t parity:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t currzero:1;
		uपूर्णांक64_t loopback:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_reg_error_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t parity:1;
#अन्यथा
		uपूर्णांक64_t parity:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_reg_error_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t currzero:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t parity:1;
#अन्यथा
		uपूर्णांक64_t parity:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t currzero:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_pko_reg_flags अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_flags_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t dis_perf3:1;
		uपूर्णांक64_t dis_perf2:1;
		uपूर्णांक64_t dis_perf1:1;
		uपूर्णांक64_t dis_perf0:1;
		uपूर्णांक64_t ena_throttle:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t store_be:1;
		uपूर्णांक64_t ena_dwb:1;
		uपूर्णांक64_t ena_pko:1;
#अन्यथा
		uपूर्णांक64_t ena_pko:1;
		uपूर्णांक64_t ena_dwb:1;
		uपूर्णांक64_t store_be:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ena_throttle:1;
		uपूर्णांक64_t dis_perf0:1;
		uपूर्णांक64_t dis_perf1:1;
		uपूर्णांक64_t dis_perf2:1;
		uपूर्णांक64_t dis_perf3:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_reg_flags_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t store_be:1;
		uपूर्णांक64_t ena_dwb:1;
		uपूर्णांक64_t ena_pko:1;
#अन्यथा
		uपूर्णांक64_t ena_pko:1;
		uपूर्णांक64_t ena_dwb:1;
		uपूर्णांक64_t store_be:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_reg_flags_cn61xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_9_63:55;
		uपूर्णांक64_t dis_perf3:1;
		uपूर्णांक64_t dis_perf2:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t store_be:1;
		uपूर्णांक64_t ena_dwb:1;
		uपूर्णांक64_t ena_pko:1;
#अन्यथा
		uपूर्णांक64_t ena_pko:1;
		uपूर्णांक64_t ena_dwb:1;
		uपूर्णांक64_t store_be:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t reserved_4_6:3;
		uपूर्णांक64_t dis_perf2:1;
		uपूर्णांक64_t dis_perf3:1;
		uपूर्णांक64_t reserved_9_63:55;
#पूर्ण_अगर
	पूर्ण cn61xx;
	काष्ठा cvmx_pko_reg_flags_cn68xxp1 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_7_63:57;
		uपूर्णांक64_t dis_perf1:1;
		uपूर्णांक64_t dis_perf0:1;
		uपूर्णांक64_t ena_throttle:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t store_be:1;
		uपूर्णांक64_t ena_dwb:1;
		uपूर्णांक64_t ena_pko:1;
#अन्यथा
		uपूर्णांक64_t ena_pko:1;
		uपूर्णांक64_t ena_dwb:1;
		uपूर्णांक64_t store_be:1;
		uपूर्णांक64_t reset:1;
		uपूर्णांक64_t ena_throttle:1;
		uपूर्णांक64_t dis_perf0:1;
		uपूर्णांक64_t dis_perf1:1;
		uपूर्णांक64_t reserved_7_63:57;
#पूर्ण_अगर
	पूर्ण cn68xxp1;
पूर्ण;

जोड़ cvmx_pko_reg_gmx_port_mode अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_gmx_port_mode_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_6_63:58;
		uपूर्णांक64_t mode1:3;
		uपूर्णांक64_t mode0:3;
#अन्यथा
		uपूर्णांक64_t mode0:3;
		uपूर्णांक64_t mode1:3;
		uपूर्णांक64_t reserved_6_63:58;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_पूर्णांक_mask अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_पूर्णांक_mask_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t loopback:1;
		uपूर्णांक64_t currzero:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t parity:1;
#अन्यथा
		uपूर्णांक64_t parity:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t currzero:1;
		uपूर्णांक64_t loopback:1;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा cvmx_pko_reg_पूर्णांक_mask_cn30xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t parity:1;
#अन्यथा
		uपूर्णांक64_t parity:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण cn30xx;
	काष्ठा cvmx_pko_reg_पूर्णांक_mask_cn50xx अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_3_63:61;
		uपूर्णांक64_t currzero:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t parity:1;
#अन्यथा
		uपूर्णांक64_t parity:1;
		uपूर्णांक64_t करोorbell:1;
		uपूर्णांक64_t currzero:1;
		uपूर्णांक64_t reserved_3_63:61;
#पूर्ण_अगर
	पूर्ण cn50xx;
पूर्ण;

जोड़ cvmx_pko_reg_loopback_bpid अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_loopback_bpid_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t bpid7:6;
		uपूर्णांक64_t reserved_52_52:1;
		uपूर्णांक64_t bpid6:6;
		uपूर्णांक64_t reserved_45_45:1;
		uपूर्णांक64_t bpid5:6;
		uपूर्णांक64_t reserved_38_38:1;
		uपूर्णांक64_t bpid4:6;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t bpid3:6;
		uपूर्णांक64_t reserved_24_24:1;
		uपूर्णांक64_t bpid2:6;
		uपूर्णांक64_t reserved_17_17:1;
		uपूर्णांक64_t bpid1:6;
		uपूर्णांक64_t reserved_10_10:1;
		uपूर्णांक64_t bpid0:6;
		uपूर्णांक64_t reserved_0_3:4;
#अन्यथा
		uपूर्णांक64_t reserved_0_3:4;
		uपूर्णांक64_t bpid0:6;
		uपूर्णांक64_t reserved_10_10:1;
		uपूर्णांक64_t bpid1:6;
		uपूर्णांक64_t reserved_17_17:1;
		uपूर्णांक64_t bpid2:6;
		uपूर्णांक64_t reserved_24_24:1;
		uपूर्णांक64_t bpid3:6;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t bpid4:6;
		uपूर्णांक64_t reserved_38_38:1;
		uपूर्णांक64_t bpid5:6;
		uपूर्णांक64_t reserved_45_45:1;
		uपूर्णांक64_t bpid6:6;
		uपूर्णांक64_t reserved_52_52:1;
		uपूर्णांक64_t bpid7:6;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_loopback_pkind अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_loopback_pkind_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_59_63:5;
		uपूर्णांक64_t pkind7:6;
		uपूर्णांक64_t reserved_52_52:1;
		uपूर्णांक64_t pkind6:6;
		uपूर्णांक64_t reserved_45_45:1;
		uपूर्णांक64_t pkind5:6;
		uपूर्णांक64_t reserved_38_38:1;
		uपूर्णांक64_t pkind4:6;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t pkind3:6;
		uपूर्णांक64_t reserved_24_24:1;
		uपूर्णांक64_t pkind2:6;
		uपूर्णांक64_t reserved_17_17:1;
		uपूर्णांक64_t pkind1:6;
		uपूर्णांक64_t reserved_10_10:1;
		uपूर्णांक64_t pkind0:6;
		uपूर्णांक64_t num_ports:4;
#अन्यथा
		uपूर्णांक64_t num_ports:4;
		uपूर्णांक64_t pkind0:6;
		uपूर्णांक64_t reserved_10_10:1;
		uपूर्णांक64_t pkind1:6;
		uपूर्णांक64_t reserved_17_17:1;
		uपूर्णांक64_t pkind2:6;
		uपूर्णांक64_t reserved_24_24:1;
		uपूर्णांक64_t pkind3:6;
		uपूर्णांक64_t reserved_31_31:1;
		uपूर्णांक64_t pkind4:6;
		uपूर्णांक64_t reserved_38_38:1;
		uपूर्णांक64_t pkind5:6;
		uपूर्णांक64_t reserved_45_45:1;
		uपूर्णांक64_t pkind6:6;
		uपूर्णांक64_t reserved_52_52:1;
		uपूर्णांक64_t pkind7:6;
		uपूर्णांक64_t reserved_59_63:5;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_min_pkt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_min_pkt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t size7:8;
		uपूर्णांक64_t size6:8;
		uपूर्णांक64_t size5:8;
		uपूर्णांक64_t size4:8;
		uपूर्णांक64_t size3:8;
		uपूर्णांक64_t size2:8;
		uपूर्णांक64_t size1:8;
		uपूर्णांक64_t size0:8;
#अन्यथा
		uपूर्णांक64_t size0:8;
		uपूर्णांक64_t size1:8;
		uपूर्णांक64_t size2:8;
		uपूर्णांक64_t size3:8;
		uपूर्णांक64_t size4:8;
		uपूर्णांक64_t size5:8;
		uपूर्णांक64_t size6:8;
		uपूर्णांक64_t size7:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_preempt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_preempt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t min_size:16;
#अन्यथा
		uपूर्णांक64_t min_size:16;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_queue_mode अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_queue_mode_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t mode:2;
#अन्यथा
		uपूर्णांक64_t mode:2;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_queue_preempt अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_queue_preempt_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t preempter:1;
#अन्यथा
		uपूर्णांक64_t preempter:1;
		uपूर्णांक64_t preemptee:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_queue_ptrs1 अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_queue_ptrs1_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_2_63:62;
		uपूर्णांक64_t idx3:1;
		uपूर्णांक64_t qid7:1;
#अन्यथा
		uपूर्णांक64_t qid7:1;
		uपूर्णांक64_t idx3:1;
		uपूर्णांक64_t reserved_2_63:62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_पढ़ो_idx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_पढ़ो_idx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_16_63:48;
		uपूर्णांक64_t inc:8;
		uपूर्णांक64_t index:8;
#अन्यथा
		uपूर्णांक64_t index:8;
		uपूर्णांक64_t inc:8;
		uपूर्णांक64_t reserved_16_63:48;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_throttle अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_throttle_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_32_63:32;
		uपूर्णांक64_t पूर्णांक_mask:32;
#अन्यथा
		uपूर्णांक64_t पूर्णांक_mask:32;
		uपूर्णांक64_t reserved_32_63:32;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_pko_reg_बारtamp अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_pko_reg_बारtamp_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_4_63:60;
		uपूर्णांक64_t wqe_word:4;
#अन्यथा
		uपूर्णांक64_t wqe_word:4;
		uपूर्णांक64_t reserved_4_63:60;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
