<शैली गुरु>
/*
 * Copyright (C) 2016  Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __VEGA10_SDMA_PKT_OPEN_H_
#घोषणा __VEGA10_SDMA_PKT_OPEN_H_

#घोषणा SDMA_OP_NOP  0
#घोषणा SDMA_OP_COPY  1
#घोषणा SDMA_OP_WRITE  2
#घोषणा SDMA_OP_INसूचीECT  4
#घोषणा SDMA_OP_FENCE  5
#घोषणा SDMA_OP_TRAP  6
#घोषणा SDMA_OP_SEM  7
#घोषणा SDMA_OP_POLL_REGMEM  8
#घोषणा SDMA_OP_COND_EXE  9
#घोषणा SDMA_OP_ATOMIC  10
#घोषणा SDMA_OP_CONST_FILL  11
#घोषणा SDMA_OP_PTEPDE  12
#घोषणा SDMA_OP_TIMESTAMP  13
#घोषणा SDMA_OP_SRBM_WRITE  14
#घोषणा SDMA_OP_PRE_EXE  15
#घोषणा SDMA_OP_DUMMY_TRAP  16
#घोषणा SDMA_SUBOP_TIMESTAMP_SET  0
#घोषणा SDMA_SUBOP_TIMESTAMP_GET  1
#घोषणा SDMA_SUBOP_TIMESTAMP_GET_GLOBAL  2
#घोषणा SDMA_SUBOP_COPY_LINEAR  0
#घोषणा SDMA_SUBOP_COPY_LINEAR_SUB_WIND  4
#घोषणा SDMA_SUBOP_COPY_TILED  1
#घोषणा SDMA_SUBOP_COPY_TILED_SUB_WIND  5
#घोषणा SDMA_SUBOP_COPY_T2T_SUB_WIND  6
#घोषणा SDMA_SUBOP_COPY_SOA  3
#घोषणा SDMA_SUBOP_COPY_सूचीTY_PAGE  7
#घोषणा SDMA_SUBOP_COPY_LINEAR_PHY  8
#घोषणा SDMA_SUBOP_WRITE_LINEAR  0
#घोषणा SDMA_SUBOP_WRITE_TILED  1
#घोषणा SDMA_SUBOP_PTEPDE_GEN  0
#घोषणा SDMA_SUBOP_PTEPDE_COPY  1
#घोषणा SDMA_SUBOP_PTEPDE_RMW  2
#घोषणा SDMA_SUBOP_PTEPDE_COPY_BACKWARDS  3
#घोषणा SDMA_SUBOP_DATA_FILL_MULTI  1
#घोषणा SDMA_SUBOP_POLL_REG_WRITE_MEM  1
#घोषणा SDMA_SUBOP_POLL_DBIT_WRITE_MEM  2
#घोषणा SDMA_SUBOP_POLL_MEM_VERIFY  3
#घोषणा HEADER_AGENT_DISPATCH  4
#घोषणा HEADER_BARRIER  5
#घोषणा SDMA_OP_AQL_COPY  0
#घोषणा SDMA_OP_AQL_BARRIER_OR  0

/*define क्रम op field*/
#घोषणा SDMA_PKT_HEADER_op_offset 0
#घोषणा SDMA_PKT_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_HEADER_OP(x) (((x) & SDMA_PKT_HEADER_op_mask) << SDMA_PKT_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_HEADER_SUB_OP(x) (((x) & SDMA_PKT_HEADER_sub_op_mask) << SDMA_PKT_HEADER_sub_op_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_LINEAR packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_OP(x) (((x) & SDMA_PKT_COPY_LINEAR_HEADER_op_mask) << SDMA_PKT_COPY_LINEAR_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_LINEAR_HEADER_sub_op_mask) << SDMA_PKT_COPY_LINEAR_HEADER_sub_op_shअगरt)

/*define क्रम encrypt field*/
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_encrypt_offset 0
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_encrypt_mask   0x00000001
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_encrypt_shअगरt  16
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_ENCRYPT(x) (((x) & SDMA_PKT_COPY_LINEAR_HEADER_encrypt_mask) << SDMA_PKT_COPY_LINEAR_HEADER_encrypt_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_LINEAR_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_LINEAR_HEADER_पंचांगz_shअगरt)

/*define क्रम broadcast field*/
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_broadcast_offset 0
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_broadcast_mask   0x00000001
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_broadcast_shअगरt  27
#घोषणा SDMA_PKT_COPY_LINEAR_HEADER_BROADCAST(x) (((x) & SDMA_PKT_COPY_LINEAR_HEADER_broadcast_mask) << SDMA_PKT_COPY_LINEAR_HEADER_broadcast_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_COPY_LINEAR_COUNT_count_offset 1
#घोषणा SDMA_PKT_COPY_LINEAR_COUNT_count_mask   0x003FFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_LINEAR_COUNT_count_mask) << SDMA_PKT_COPY_LINEAR_COUNT_count_shअगरt)

/*define क्रम PARAMETER word*/
/*define क्रम dst_sw field*/
#घोषणा SDMA_PKT_COPY_LINEAR_PARAMETER_dst_sw_offset 2
#घोषणा SDMA_PKT_COPY_LINEAR_PARAMETER_dst_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_LINEAR_PARAMETER_dst_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_LINEAR_PARAMETER_DST_SW(x) (((x) & SDMA_PKT_COPY_LINEAR_PARAMETER_dst_sw_mask) << SDMA_PKT_COPY_LINEAR_PARAMETER_dst_sw_shअगरt)

/*define क्रम src_sw field*/
#घोषणा SDMA_PKT_COPY_LINEAR_PARAMETER_src_sw_offset 2
#घोषणा SDMA_PKT_COPY_LINEAR_PARAMETER_src_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_LINEAR_PARAMETER_src_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_LINEAR_PARAMETER_SRC_SW(x) (((x) & SDMA_PKT_COPY_LINEAR_PARAMETER_src_sw_mask) << SDMA_PKT_COPY_LINEAR_PARAMETER_src_sw_shअगरt)

/*define क्रम SRC_ADDR_LO word*/
/*define क्रम src_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_offset 3
#घोषणा SDMA_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SRC_ADDR_LO_SRC_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_mask) << SDMA_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_shअगरt)

/*define क्रम SRC_ADDR_HI word*/
/*define क्रम src_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_offset 4
#घोषणा SDMA_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SRC_ADDR_HI_SRC_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_mask) << SDMA_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_offset 5
#घोषणा SDMA_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_offset 6
#घोषणा SDMA_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_सूचीTY_PAGE packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_OP(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_op_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_sub_op_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_sub_op_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_पंचांगz_shअगरt)

/*define क्रम all field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_all_offset 0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_all_mask   0x00000001
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_all_shअगरt  31
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_ALL(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_all_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_HEADER_all_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_COUNT_count_offset 1
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_COUNT_count_mask   0x003FFFFF
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_COUNT_count_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_COUNT_count_shअगरt)

/*define क्रम PARAMETER word*/
/*define क्रम dst_sw field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sw_offset 2
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_DST_SW(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sw_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sw_shअगरt)

/*define क्रम dst_gcc field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gcc_offset 2
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gcc_mask   0x00000001
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gcc_shअगरt  19
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_DST_GCC(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gcc_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gcc_shअगरt)

/*define क्रम dst_sys field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sys_offset 2
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sys_mask   0x00000001
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sys_shअगरt  20
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_DST_SYS(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sys_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_sys_shअगरt)

/*define क्रम dst_snoop field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_snoop_offset 2
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_snoop_mask   0x00000001
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_snoop_shअगरt  22
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_DST_SNOOP(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_snoop_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_snoop_shअगरt)

/*define क्रम dst_gpa field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gpa_offset 2
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gpa_mask   0x00000001
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gpa_shअगरt  23
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_DST_GPA(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gpa_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_dst_gpa_shअगरt)

/*define क्रम src_sw field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sw_offset 2
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_SRC_SW(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sw_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sw_shअगरt)

/*define क्रम src_sys field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sys_offset 2
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sys_mask   0x00000001
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sys_shअगरt  28
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_SRC_SYS(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sys_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_sys_shअगरt)

/*define क्रम src_snoop field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_snoop_offset 2
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_snoop_mask   0x00000001
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_snoop_shअगरt  30
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_SRC_SNOOP(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_snoop_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_snoop_shअगरt)

/*define क्रम src_gpa field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_gpa_offset 2
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_gpa_mask   0x00000001
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_gpa_shअगरt  31
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_SRC_GPA(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_gpa_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_PARAMETER_src_gpa_shअगरt)

/*define क्रम SRC_ADDR_LO word*/
/*define क्रम src_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_LO_src_addr_31_0_offset 3
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_LO_src_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_LO_src_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_LO_SRC_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_LO_src_addr_31_0_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_LO_src_addr_31_0_shअगरt)

/*define क्रम SRC_ADDR_HI word*/
/*define क्रम src_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_HI_src_addr_63_32_offset 4
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_HI_src_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_HI_src_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_HI_SRC_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_HI_src_addr_63_32_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_SRC_ADDR_HI_src_addr_63_32_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_LO_dst_addr_31_0_offset 5
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_HI_dst_addr_63_32_offset 6
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_COPY_सूचीTY_PAGE_DST_ADDR_HI_dst_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_PHYSICAL_LINEAR packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_OP(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_op_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_sub_op_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_sub_op_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_HEADER_पंचांगz_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_COUNT_count_offset 1
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_COUNT_count_mask   0x003FFFFF
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_COUNT_count_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_COUNT_count_shअगरt)

/*define क्रम PARAMETER word*/
/*define क्रम dst_sw field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sw_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_DST_SW(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sw_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sw_shअगरt)

/*define क्रम dst_gcc field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gcc_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gcc_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gcc_shअगरt  19
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_DST_GCC(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gcc_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gcc_shअगरt)

/*define क्रम dst_sys field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sys_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sys_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sys_shअगरt  20
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_DST_SYS(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sys_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_sys_shअगरt)

/*define क्रम dst_log field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_log_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_log_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_log_shअगरt  21
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_DST_LOG(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_log_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_log_shअगरt)

/*define क्रम dst_snoop field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_snoop_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_snoop_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_snoop_shअगरt  22
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_DST_SNOOP(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_snoop_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_snoop_shअगरt)

/*define क्रम dst_gpa field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gpa_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gpa_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gpa_shअगरt  23
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_DST_GPA(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gpa_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_dst_gpa_shअगरt)

/*define क्रम src_sw field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sw_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_SRC_SW(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sw_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sw_shअगरt)

/*define क्रम src_gcc field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gcc_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gcc_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gcc_shअगरt  27
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_SRC_GCC(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gcc_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gcc_shअगरt)

/*define क्रम src_sys field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sys_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sys_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sys_shअगरt  28
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_SRC_SYS(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sys_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_sys_shअगरt)

/*define क्रम src_snoop field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_snoop_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_snoop_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_snoop_shअगरt  30
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_SRC_SNOOP(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_snoop_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_snoop_shअगरt)

/*define क्रम src_gpa field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gpa_offset 2
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gpa_mask   0x00000001
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gpa_shअगरt  31
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_SRC_GPA(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gpa_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_PARAMETER_src_gpa_shअगरt)

/*define क्रम SRC_ADDR_LO word*/
/*define क्रम src_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_LO_src_addr_31_0_offset 3
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_LO_src_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_LO_src_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_LO_SRC_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_LO_src_addr_31_0_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_LO_src_addr_31_0_shअगरt)

/*define क्रम SRC_ADDR_HI word*/
/*define क्रम src_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_HI_src_addr_63_32_offset 4
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_HI_src_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_HI_src_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_HI_SRC_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_HI_src_addr_63_32_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_SRC_ADDR_HI_src_addr_63_32_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_LO_dst_addr_31_0_offset 5
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_HI_dst_addr_63_32_offset 6
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_COPY_PHYSICAL_LINEAR_DST_ADDR_HI_dst_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_BROADCAST_LINEAR packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_OP(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_op_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_sub_op_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_sub_op_shअगरt)

/*define क्रम encrypt field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_encrypt_offset 0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_encrypt_mask   0x00000001
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_encrypt_shअगरt  16
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_ENCRYPT(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_encrypt_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_encrypt_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_पंचांगz_shअगरt)

/*define क्रम broadcast field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_broadcast_offset 0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_broadcast_mask   0x00000001
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_broadcast_shअगरt  27
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_BROADCAST(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_broadcast_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_HEADER_broadcast_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_COUNT_count_offset 1
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_COUNT_count_mask   0x003FFFFF
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_COUNT_count_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_COUNT_count_shअगरt)

/*define क्रम PARAMETER word*/
/*define क्रम dst2_sw field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst2_sw_offset 2
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst2_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst2_sw_shअगरt  8
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_DST2_SW(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst2_sw_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst2_sw_shअगरt)

/*define क्रम dst1_sw field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst1_sw_offset 2
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst1_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst1_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_DST1_SW(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst1_sw_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_dst1_sw_shअगरt)

/*define क्रम src_sw field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_src_sw_offset 2
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_src_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_src_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_SRC_SW(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_src_sw_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_PARAMETER_src_sw_shअगरt)

/*define क्रम SRC_ADDR_LO word*/
/*define क्रम src_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_LO_src_addr_31_0_offset 3
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_LO_src_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_LO_src_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_LO_SRC_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_LO_src_addr_31_0_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_LO_src_addr_31_0_shअगरt)

/*define क्रम SRC_ADDR_HI word*/
/*define क्रम src_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_HI_src_addr_63_32_offset 4
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_HI_src_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_HI_src_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_HI_SRC_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_HI_src_addr_63_32_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_SRC_ADDR_HI_src_addr_63_32_shअगरt)

/*define क्रम DST1_ADDR_LO word*/
/*define क्रम dst1_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_LO_dst1_addr_31_0_offset 5
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_LO_dst1_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_LO_dst1_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_LO_DST1_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_LO_dst1_addr_31_0_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_LO_dst1_addr_31_0_shअगरt)

/*define क्रम DST1_ADDR_HI word*/
/*define क्रम dst1_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_HI_dst1_addr_63_32_offset 6
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_HI_dst1_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_HI_dst1_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_HI_DST1_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_HI_dst1_addr_63_32_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_DST1_ADDR_HI_dst1_addr_63_32_shअगरt)

/*define क्रम DST2_ADDR_LO word*/
/*define क्रम dst2_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_LO_dst2_addr_31_0_offset 7
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_LO_dst2_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_LO_dst2_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_LO_DST2_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_LO_dst2_addr_31_0_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_LO_dst2_addr_31_0_shअगरt)

/*define क्रम DST2_ADDR_HI word*/
/*define क्रम dst2_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_HI_dst2_addr_63_32_offset 8
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_HI_dst2_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_HI_dst2_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_HI_DST2_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_HI_dst2_addr_63_32_mask) << SDMA_PKT_COPY_BROADCAST_LINEAR_DST2_ADDR_HI_dst2_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_LINEAR_SUBWIN packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_OP(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_op_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_sub_op_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_sub_op_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_पंचांगz_shअगरt)

/*define क्रम elementsize field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_elementsize_offset 0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_elementsize_mask   0x00000007
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_elementsize_shअगरt  29
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_ELEMENTSIZE(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_elementsize_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_HEADER_elementsize_shअगरt)

/*define क्रम SRC_ADDR_LO word*/
/*define क्रम src_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_LO_src_addr_31_0_offset 1
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_LO_src_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_LO_src_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_LO_SRC_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_LO_src_addr_31_0_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_LO_src_addr_31_0_shअगरt)

/*define क्रम SRC_ADDR_HI word*/
/*define क्रम src_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_HI_src_addr_63_32_offset 2
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_HI_src_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_HI_src_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_HI_SRC_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_HI_src_addr_63_32_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_SRC_ADDR_HI_src_addr_63_32_shअगरt)

/*define क्रम DW_3 word*/
/*define क्रम src_x field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_x_offset 3
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_SRC_X(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_x_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_x_shअगरt)

/*define क्रम src_y field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_y_offset 3
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_SRC_Y(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_y_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_3_src_y_shअगरt)

/*define क्रम DW_4 word*/
/*define क्रम src_z field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_z_offset 4
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_SRC_Z(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_z_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_z_shअगरt)

/*define क्रम src_pitch field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_pitch_offset 4
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_pitch_mask   0x0007FFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_pitch_shअगरt  13
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_SRC_PITCH(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_pitch_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_4_src_pitch_shअगरt)

/*define क्रम DW_5 word*/
/*define क्रम src_slice_pitch field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_5_src_slice_pitch_offset 5
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_5_src_slice_pitch_mask   0x0FFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_5_src_slice_pitch_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_5_SRC_SLICE_PITCH(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_5_src_slice_pitch_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_5_src_slice_pitch_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_LO_dst_addr_31_0_offset 6
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_HI_dst_addr_63_32_offset 7
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम DW_8 word*/
/*define क्रम dst_x field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_x_offset 8
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_DST_X(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_x_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_x_shअगरt)

/*define क्रम dst_y field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_y_offset 8
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_DST_Y(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_y_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_8_dst_y_shअगरt)

/*define क्रम DW_9 word*/
/*define क्रम dst_z field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_z_offset 9
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_DST_Z(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_z_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_z_shअगरt)

/*define क्रम dst_pitch field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_pitch_offset 9
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_pitch_mask   0x0007FFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_pitch_shअगरt  13
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_DST_PITCH(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_pitch_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_9_dst_pitch_shअगरt)

/*define क्रम DW_10 word*/
/*define क्रम dst_slice_pitch field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_10_dst_slice_pitch_offset 10
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_10_dst_slice_pitch_mask   0x0FFFFFFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_10_dst_slice_pitch_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_10_DST_SLICE_PITCH(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_10_dst_slice_pitch_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_10_dst_slice_pitch_shअगरt)

/*define क्रम DW_11 word*/
/*define क्रम rect_x field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_x_offset 11
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_RECT_X(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_x_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_x_shअगरt)

/*define क्रम rect_y field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_y_offset 11
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_RECT_Y(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_y_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_11_rect_y_shअगरt)

/*define क्रम DW_12 word*/
/*define क्रम rect_z field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_rect_z_offset 12
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_rect_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_rect_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_RECT_Z(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_rect_z_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_rect_z_shअगरt)

/*define क्रम dst_sw field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_dst_sw_offset 12
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_dst_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_dst_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_DST_SW(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_dst_sw_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_dst_sw_shअगरt)

/*define क्रम src_sw field*/
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_src_sw_offset 12
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_src_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_src_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_SRC_SW(x) (((x) & SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_src_sw_mask) << SDMA_PKT_COPY_LINEAR_SUBWIN_DW_12_src_sw_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_TILED packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_TILED_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_TILED_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_TILED_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_HEADER_OP(x) (((x) & SDMA_PKT_COPY_TILED_HEADER_op_mask) << SDMA_PKT_COPY_TILED_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_TILED_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_TILED_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_TILED_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_TILED_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_TILED_HEADER_sub_op_mask) << SDMA_PKT_COPY_TILED_HEADER_sub_op_shअगरt)

/*define क्रम encrypt field*/
#घोषणा SDMA_PKT_COPY_TILED_HEADER_encrypt_offset 0
#घोषणा SDMA_PKT_COPY_TILED_HEADER_encrypt_mask   0x00000001
#घोषणा SDMA_PKT_COPY_TILED_HEADER_encrypt_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_HEADER_ENCRYPT(x) (((x) & SDMA_PKT_COPY_TILED_HEADER_encrypt_mask) << SDMA_PKT_COPY_TILED_HEADER_encrypt_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_TILED_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_TILED_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_TILED_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_TILED_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_TILED_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_TILED_HEADER_पंचांगz_shअगरt)

/*define क्रम mip_max field*/
#घोषणा SDMA_PKT_COPY_TILED_HEADER_mip_max_offset 0
#घोषणा SDMA_PKT_COPY_TILED_HEADER_mip_max_mask   0x0000000F
#घोषणा SDMA_PKT_COPY_TILED_HEADER_mip_max_shअगरt  20
#घोषणा SDMA_PKT_COPY_TILED_HEADER_MIP_MAX(x) (((x) & SDMA_PKT_COPY_TILED_HEADER_mip_max_mask) << SDMA_PKT_COPY_TILED_HEADER_mip_max_shअगरt)

/*define क्रम detile field*/
#घोषणा SDMA_PKT_COPY_TILED_HEADER_detile_offset 0
#घोषणा SDMA_PKT_COPY_TILED_HEADER_detile_mask   0x00000001
#घोषणा SDMA_PKT_COPY_TILED_HEADER_detile_shअगरt  31
#घोषणा SDMA_PKT_COPY_TILED_HEADER_DETILE(x) (((x) & SDMA_PKT_COPY_TILED_HEADER_detile_mask) << SDMA_PKT_COPY_TILED_HEADER_detile_shअगरt)

/*define क्रम TILED_ADDR_LO word*/
/*define क्रम tiled_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_TILED_TILED_ADDR_LO_tiled_addr_31_0_offset 1
#घोषणा SDMA_PKT_COPY_TILED_TILED_ADDR_LO_tiled_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_TILED_ADDR_LO_tiled_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_TILED_ADDR_LO_TILED_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_TILED_TILED_ADDR_LO_tiled_addr_31_0_mask) << SDMA_PKT_COPY_TILED_TILED_ADDR_LO_tiled_addr_31_0_shअगरt)

/*define क्रम TILED_ADDR_HI word*/
/*define क्रम tiled_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_TILED_TILED_ADDR_HI_tiled_addr_63_32_offset 2
#घोषणा SDMA_PKT_COPY_TILED_TILED_ADDR_HI_tiled_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_TILED_ADDR_HI_tiled_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_TILED_ADDR_HI_TILED_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_TILED_TILED_ADDR_HI_tiled_addr_63_32_mask) << SDMA_PKT_COPY_TILED_TILED_ADDR_HI_tiled_addr_63_32_shअगरt)

/*define क्रम DW_3 word*/
/*define क्रम width field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_3_width_offset 3
#घोषणा SDMA_PKT_COPY_TILED_DW_3_width_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_DW_3_width_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_DW_3_WIDTH(x) (((x) & SDMA_PKT_COPY_TILED_DW_3_width_mask) << SDMA_PKT_COPY_TILED_DW_3_width_shअगरt)

/*define क्रम DW_4 word*/
/*define क्रम height field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_4_height_offset 4
#घोषणा SDMA_PKT_COPY_TILED_DW_4_height_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_DW_4_height_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_DW_4_HEIGHT(x) (((x) & SDMA_PKT_COPY_TILED_DW_4_height_mask) << SDMA_PKT_COPY_TILED_DW_4_height_shअगरt)

/*define क्रम depth field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_4_depth_offset 4
#घोषणा SDMA_PKT_COPY_TILED_DW_4_depth_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_TILED_DW_4_depth_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_DW_4_DEPTH(x) (((x) & SDMA_PKT_COPY_TILED_DW_4_depth_mask) << SDMA_PKT_COPY_TILED_DW_4_depth_shअगरt)

/*define क्रम DW_5 word*/
/*define क्रम element_size field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_5_element_size_offset 5
#घोषणा SDMA_PKT_COPY_TILED_DW_5_element_size_mask   0x00000007
#घोषणा SDMA_PKT_COPY_TILED_DW_5_element_size_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_DW_5_ELEMENT_SIZE(x) (((x) & SDMA_PKT_COPY_TILED_DW_5_element_size_mask) << SDMA_PKT_COPY_TILED_DW_5_element_size_shअगरt)

/*define क्रम swizzle_mode field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_5_swizzle_mode_offset 5
#घोषणा SDMA_PKT_COPY_TILED_DW_5_swizzle_mode_mask   0x0000001F
#घोषणा SDMA_PKT_COPY_TILED_DW_5_swizzle_mode_shअगरt  3
#घोषणा SDMA_PKT_COPY_TILED_DW_5_SWIZZLE_MODE(x) (((x) & SDMA_PKT_COPY_TILED_DW_5_swizzle_mode_mask) << SDMA_PKT_COPY_TILED_DW_5_swizzle_mode_shअगरt)

/*define क्रम dimension field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_5_dimension_offset 5
#घोषणा SDMA_PKT_COPY_TILED_DW_5_dimension_mask   0x00000003
#घोषणा SDMA_PKT_COPY_TILED_DW_5_dimension_shअगरt  9
#घोषणा SDMA_PKT_COPY_TILED_DW_5_DIMENSION(x) (((x) & SDMA_PKT_COPY_TILED_DW_5_dimension_mask) << SDMA_PKT_COPY_TILED_DW_5_dimension_shअगरt)

/*define क्रम epitch field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_5_epitch_offset 5
#घोषणा SDMA_PKT_COPY_TILED_DW_5_epitch_mask   0x0000FFFF
#घोषणा SDMA_PKT_COPY_TILED_DW_5_epitch_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_DW_5_EPITCH(x) (((x) & SDMA_PKT_COPY_TILED_DW_5_epitch_mask) << SDMA_PKT_COPY_TILED_DW_5_epitch_shअगरt)

/*define क्रम DW_6 word*/
/*define क्रम x field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_6_x_offset 6
#घोषणा SDMA_PKT_COPY_TILED_DW_6_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_DW_6_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_DW_6_X(x) (((x) & SDMA_PKT_COPY_TILED_DW_6_x_mask) << SDMA_PKT_COPY_TILED_DW_6_x_shअगरt)

/*define क्रम y field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_6_y_offset 6
#घोषणा SDMA_PKT_COPY_TILED_DW_6_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_DW_6_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_DW_6_Y(x) (((x) & SDMA_PKT_COPY_TILED_DW_6_y_mask) << SDMA_PKT_COPY_TILED_DW_6_y_shअगरt)

/*define क्रम DW_7 word*/
/*define क्रम z field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_7_z_offset 7
#घोषणा SDMA_PKT_COPY_TILED_DW_7_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_TILED_DW_7_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_DW_7_Z(x) (((x) & SDMA_PKT_COPY_TILED_DW_7_z_mask) << SDMA_PKT_COPY_TILED_DW_7_z_shअगरt)

/*define क्रम linear_sw field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_7_linear_sw_offset 7
#घोषणा SDMA_PKT_COPY_TILED_DW_7_linear_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_TILED_DW_7_linear_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_DW_7_LINEAR_SW(x) (((x) & SDMA_PKT_COPY_TILED_DW_7_linear_sw_mask) << SDMA_PKT_COPY_TILED_DW_7_linear_sw_shअगरt)

/*define क्रम tile_sw field*/
#घोषणा SDMA_PKT_COPY_TILED_DW_7_tile_sw_offset 7
#घोषणा SDMA_PKT_COPY_TILED_DW_7_tile_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_TILED_DW_7_tile_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_TILED_DW_7_TILE_SW(x) (((x) & SDMA_PKT_COPY_TILED_DW_7_tile_sw_mask) << SDMA_PKT_COPY_TILED_DW_7_tile_sw_shअगरt)

/*define क्रम LINEAR_ADDR_LO word*/
/*define क्रम linear_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_ADDR_LO_linear_addr_31_0_offset 8
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_ADDR_LO_linear_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_ADDR_LO_linear_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_ADDR_LO_LINEAR_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_TILED_LINEAR_ADDR_LO_linear_addr_31_0_mask) << SDMA_PKT_COPY_TILED_LINEAR_ADDR_LO_linear_addr_31_0_shअगरt)

/*define क्रम LINEAR_ADDR_HI word*/
/*define क्रम linear_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_ADDR_HI_linear_addr_63_32_offset 9
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_ADDR_HI_linear_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_ADDR_HI_linear_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_ADDR_HI_LINEAR_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_TILED_LINEAR_ADDR_HI_linear_addr_63_32_mask) << SDMA_PKT_COPY_TILED_LINEAR_ADDR_HI_linear_addr_63_32_shअगरt)

/*define क्रम LINEAR_PITCH word*/
/*define क्रम linear_pitch field*/
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_PITCH_linear_pitch_offset 10
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_PITCH_linear_pitch_mask   0x0007FFFF
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_PITCH_linear_pitch_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_PITCH_LINEAR_PITCH(x) (((x) & SDMA_PKT_COPY_TILED_LINEAR_PITCH_linear_pitch_mask) << SDMA_PKT_COPY_TILED_LINEAR_PITCH_linear_pitch_shअगरt)

/*define क्रम LINEAR_SLICE_PITCH word*/
/*define क्रम linear_slice_pitch field*/
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_SLICE_PITCH_linear_slice_pitch_offset 11
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_SLICE_PITCH_linear_slice_pitch_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_SLICE_PITCH_linear_slice_pitch_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_LINEAR_SLICE_PITCH_LINEAR_SLICE_PITCH(x) (((x) & SDMA_PKT_COPY_TILED_LINEAR_SLICE_PITCH_linear_slice_pitch_mask) << SDMA_PKT_COPY_TILED_LINEAR_SLICE_PITCH_linear_slice_pitch_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_COPY_TILED_COUNT_count_offset 12
#घोषणा SDMA_PKT_COPY_TILED_COUNT_count_mask   0x000FFFFF
#घोषणा SDMA_PKT_COPY_TILED_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_TILED_COUNT_count_mask) << SDMA_PKT_COPY_TILED_COUNT_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_L2T_BROADCAST packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_OP(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_HEADER_op_mask) << SDMA_PKT_COPY_L2T_BROADCAST_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_HEADER_sub_op_mask) << SDMA_PKT_COPY_L2T_BROADCAST_HEADER_sub_op_shअगरt)

/*define क्रम encrypt field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_encrypt_offset 0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_encrypt_mask   0x00000001
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_encrypt_shअगरt  16
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_ENCRYPT(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_HEADER_encrypt_mask) << SDMA_PKT_COPY_L2T_BROADCAST_HEADER_encrypt_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_L2T_BROADCAST_HEADER_पंचांगz_shअगरt)

/*define क्रम mip_max field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_mip_max_offset 0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_mip_max_mask   0x0000000F
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_mip_max_shअगरt  20
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_MIP_MAX(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_HEADER_mip_max_mask) << SDMA_PKT_COPY_L2T_BROADCAST_HEADER_mip_max_shअगरt)

/*define क्रम videocopy field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_videocopy_offset 0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_videocopy_mask   0x00000001
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_videocopy_shअगरt  26
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_VIDEOCOPY(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_HEADER_videocopy_mask) << SDMA_PKT_COPY_L2T_BROADCAST_HEADER_videocopy_shअगरt)

/*define क्रम broadcast field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_broadcast_offset 0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_broadcast_mask   0x00000001
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_broadcast_shअगरt  27
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_HEADER_BROADCAST(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_HEADER_broadcast_mask) << SDMA_PKT_COPY_L2T_BROADCAST_HEADER_broadcast_shअगरt)

/*define क्रम TILED_ADDR_LO_0 word*/
/*define क्रम tiled_addr0_31_0 field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_0_tiled_addr0_31_0_offset 1
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_0_tiled_addr0_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_0_tiled_addr0_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_0_TILED_ADDR0_31_0(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_0_tiled_addr0_31_0_mask) << SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_0_tiled_addr0_31_0_shअगरt)

/*define क्रम TILED_ADDR_HI_0 word*/
/*define क्रम tiled_addr0_63_32 field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_0_tiled_addr0_63_32_offset 2
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_0_tiled_addr0_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_0_tiled_addr0_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_0_TILED_ADDR0_63_32(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_0_tiled_addr0_63_32_mask) << SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_0_tiled_addr0_63_32_shअगरt)

/*define क्रम TILED_ADDR_LO_1 word*/
/*define क्रम tiled_addr1_31_0 field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_1_tiled_addr1_31_0_offset 3
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_1_tiled_addr1_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_1_tiled_addr1_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_1_TILED_ADDR1_31_0(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_1_tiled_addr1_31_0_mask) << SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_LO_1_tiled_addr1_31_0_shअगरt)

/*define क्रम TILED_ADDR_HI_1 word*/
/*define क्रम tiled_addr1_63_32 field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_1_tiled_addr1_63_32_offset 4
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_1_tiled_addr1_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_1_tiled_addr1_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_1_TILED_ADDR1_63_32(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_1_tiled_addr1_63_32_mask) << SDMA_PKT_COPY_L2T_BROADCAST_TILED_ADDR_HI_1_tiled_addr1_63_32_shअगरt)

/*define क्रम DW_5 word*/
/*define क्रम width field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_5_width_offset 5
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_5_width_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_5_width_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_5_WIDTH(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_5_width_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_5_width_shअगरt)

/*define क्रम DW_6 word*/
/*define क्रम height field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_6_height_offset 6
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_6_height_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_6_height_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_6_HEIGHT(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_6_height_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_6_height_shअगरt)

/*define क्रम depth field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_6_depth_offset 6
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_6_depth_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_6_depth_shअगरt  16
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_6_DEPTH(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_6_depth_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_6_depth_shअगरt)

/*define क्रम DW_7 word*/
/*define क्रम element_size field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_element_size_offset 7
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_element_size_mask   0x00000007
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_element_size_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_ELEMENT_SIZE(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_7_element_size_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_7_element_size_shअगरt)

/*define क्रम swizzle_mode field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_swizzle_mode_offset 7
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_swizzle_mode_mask   0x0000001F
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_swizzle_mode_shअगरt  3
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_SWIZZLE_MODE(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_7_swizzle_mode_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_7_swizzle_mode_shअगरt)

/*define क्रम dimension field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_dimension_offset 7
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_dimension_mask   0x00000003
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_dimension_shअगरt  9
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_DIMENSION(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_7_dimension_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_7_dimension_shअगरt)

/*define क्रम epitch field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_epitch_offset 7
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_epitch_mask   0x0000FFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_epitch_shअगरt  16
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_7_EPITCH(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_7_epitch_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_7_epitch_shअगरt)

/*define क्रम DW_8 word*/
/*define क्रम x field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_8_x_offset 8
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_8_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_8_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_8_X(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_8_x_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_8_x_shअगरt)

/*define क्रम y field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_8_y_offset 8
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_8_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_8_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_8_Y(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_8_y_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_8_y_shअगरt)

/*define क्रम DW_9 word*/
/*define क्रम z field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_9_z_offset 9
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_9_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_9_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_9_Z(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_9_z_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_9_z_shअगरt)

/*define क्रम DW_10 word*/
/*define क्रम dst2_sw field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_dst2_sw_offset 10
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_dst2_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_dst2_sw_shअगरt  8
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_DST2_SW(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_10_dst2_sw_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_10_dst2_sw_shअगरt)

/*define क्रम linear_sw field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_linear_sw_offset 10
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_linear_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_linear_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_LINEAR_SW(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_10_linear_sw_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_10_linear_sw_shअगरt)

/*define क्रम tile_sw field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_tile_sw_offset 10
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_tile_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_tile_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_DW_10_TILE_SW(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_DW_10_tile_sw_mask) << SDMA_PKT_COPY_L2T_BROADCAST_DW_10_tile_sw_shअगरt)

/*define क्रम LINEAR_ADDR_LO word*/
/*define क्रम linear_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_LO_linear_addr_31_0_offset 11
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_LO_linear_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_LO_linear_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_LO_LINEAR_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_LO_linear_addr_31_0_mask) << SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_LO_linear_addr_31_0_shअगरt)

/*define क्रम LINEAR_ADDR_HI word*/
/*define क्रम linear_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_HI_linear_addr_63_32_offset 12
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_HI_linear_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_HI_linear_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_HI_LINEAR_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_HI_linear_addr_63_32_mask) << SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_ADDR_HI_linear_addr_63_32_shअगरt)

/*define क्रम LINEAR_PITCH word*/
/*define क्रम linear_pitch field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_PITCH_linear_pitch_offset 13
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_PITCH_linear_pitch_mask   0x0007FFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_PITCH_linear_pitch_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_PITCH_LINEAR_PITCH(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_PITCH_linear_pitch_mask) << SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_PITCH_linear_pitch_shअगरt)

/*define क्रम LINEAR_SLICE_PITCH word*/
/*define क्रम linear_slice_pitch field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_SLICE_PITCH_linear_slice_pitch_offset 14
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_SLICE_PITCH_linear_slice_pitch_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_SLICE_PITCH_linear_slice_pitch_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_SLICE_PITCH_LINEAR_SLICE_PITCH(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_SLICE_PITCH_linear_slice_pitch_mask) << SDMA_PKT_COPY_L2T_BROADCAST_LINEAR_SLICE_PITCH_linear_slice_pitch_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_COUNT_count_offset 15
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_COUNT_count_mask   0x000FFFFF
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_COPY_L2T_BROADCAST_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_L2T_BROADCAST_COUNT_count_mask) << SDMA_PKT_COPY_L2T_BROADCAST_COUNT_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_T2T packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_T2T_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_T2T_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_T2T_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_HEADER_OP(x) (((x) & SDMA_PKT_COPY_T2T_HEADER_op_mask) << SDMA_PKT_COPY_T2T_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_T2T_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_T2T_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_T2T_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_T2T_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_T2T_HEADER_sub_op_mask) << SDMA_PKT_COPY_T2T_HEADER_sub_op_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_T2T_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_T2T_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_T2T_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_T2T_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_T2T_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_T2T_HEADER_पंचांगz_shअगरt)

/*define क्रम mip_max field*/
#घोषणा SDMA_PKT_COPY_T2T_HEADER_mip_max_offset 0
#घोषणा SDMA_PKT_COPY_T2T_HEADER_mip_max_mask   0x0000000F
#घोषणा SDMA_PKT_COPY_T2T_HEADER_mip_max_shअगरt  20
#घोषणा SDMA_PKT_COPY_T2T_HEADER_MIP_MAX(x) (((x) & SDMA_PKT_COPY_T2T_HEADER_mip_max_mask) << SDMA_PKT_COPY_T2T_HEADER_mip_max_shअगरt)

/*define क्रम SRC_ADDR_LO word*/
/*define क्रम src_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_T2T_SRC_ADDR_LO_src_addr_31_0_offset 1
#घोषणा SDMA_PKT_COPY_T2T_SRC_ADDR_LO_src_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_T2T_SRC_ADDR_LO_src_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_SRC_ADDR_LO_SRC_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_T2T_SRC_ADDR_LO_src_addr_31_0_mask) << SDMA_PKT_COPY_T2T_SRC_ADDR_LO_src_addr_31_0_shअगरt)

/*define क्रम SRC_ADDR_HI word*/
/*define क्रम src_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_T2T_SRC_ADDR_HI_src_addr_63_32_offset 2
#घोषणा SDMA_PKT_COPY_T2T_SRC_ADDR_HI_src_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_T2T_SRC_ADDR_HI_src_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_SRC_ADDR_HI_SRC_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_T2T_SRC_ADDR_HI_src_addr_63_32_mask) << SDMA_PKT_COPY_T2T_SRC_ADDR_HI_src_addr_63_32_shअगरt)

/*define क्रम DW_3 word*/
/*define क्रम src_x field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_3_src_x_offset 3
#घोषणा SDMA_PKT_COPY_T2T_DW_3_src_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_3_src_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_3_SRC_X(x) (((x) & SDMA_PKT_COPY_T2T_DW_3_src_x_mask) << SDMA_PKT_COPY_T2T_DW_3_src_x_shअगरt)

/*define क्रम src_y field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_3_src_y_offset 3
#घोषणा SDMA_PKT_COPY_T2T_DW_3_src_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_3_src_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_3_SRC_Y(x) (((x) & SDMA_PKT_COPY_T2T_DW_3_src_y_mask) << SDMA_PKT_COPY_T2T_DW_3_src_y_shअगरt)

/*define क्रम DW_4 word*/
/*define क्रम src_z field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_4_src_z_offset 4
#घोषणा SDMA_PKT_COPY_T2T_DW_4_src_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_T2T_DW_4_src_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_4_SRC_Z(x) (((x) & SDMA_PKT_COPY_T2T_DW_4_src_z_mask) << SDMA_PKT_COPY_T2T_DW_4_src_z_shअगरt)

/*define क्रम src_width field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_4_src_width_offset 4
#घोषणा SDMA_PKT_COPY_T2T_DW_4_src_width_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_4_src_width_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_4_SRC_WIDTH(x) (((x) & SDMA_PKT_COPY_T2T_DW_4_src_width_mask) << SDMA_PKT_COPY_T2T_DW_4_src_width_shअगरt)

/*define क्रम DW_5 word*/
/*define क्रम src_height field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_5_src_height_offset 5
#घोषणा SDMA_PKT_COPY_T2T_DW_5_src_height_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_5_src_height_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_5_SRC_HEIGHT(x) (((x) & SDMA_PKT_COPY_T2T_DW_5_src_height_mask) << SDMA_PKT_COPY_T2T_DW_5_src_height_shअगरt)

/*define क्रम src_depth field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_5_src_depth_offset 5
#घोषणा SDMA_PKT_COPY_T2T_DW_5_src_depth_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_T2T_DW_5_src_depth_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_5_SRC_DEPTH(x) (((x) & SDMA_PKT_COPY_T2T_DW_5_src_depth_mask) << SDMA_PKT_COPY_T2T_DW_5_src_depth_shअगरt)

/*define क्रम DW_6 word*/
/*define क्रम src_element_size field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_element_size_offset 6
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_element_size_mask   0x00000007
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_element_size_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_6_SRC_ELEMENT_SIZE(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_src_element_size_mask) << SDMA_PKT_COPY_T2T_DW_6_src_element_size_shअगरt)

/*define क्रम src_swizzle_mode field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_swizzle_mode_offset 6
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_swizzle_mode_mask   0x0000001F
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_swizzle_mode_shअगरt  3
#घोषणा SDMA_PKT_COPY_T2T_DW_6_SRC_SWIZZLE_MODE(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_src_swizzle_mode_mask) << SDMA_PKT_COPY_T2T_DW_6_src_swizzle_mode_shअगरt)

/*define क्रम src_dimension field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_dimension_offset 6
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_dimension_mask   0x00000003
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_dimension_shअगरt  9
#घोषणा SDMA_PKT_COPY_T2T_DW_6_SRC_DIMENSION(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_src_dimension_mask) << SDMA_PKT_COPY_T2T_DW_6_src_dimension_shअगरt)

/*define क्रम src_epitch field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_epitch_offset 6
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_epitch_mask   0x0000FFFF
#घोषणा SDMA_PKT_COPY_T2T_DW_6_src_epitch_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_6_SRC_EPITCH(x) (((x) & SDMA_PKT_COPY_T2T_DW_6_src_epitch_mask) << SDMA_PKT_COPY_T2T_DW_6_src_epitch_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_T2T_DST_ADDR_LO_dst_addr_31_0_offset 7
#घोषणा SDMA_PKT_COPY_T2T_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_T2T_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_T2T_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_COPY_T2T_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_T2T_DST_ADDR_HI_dst_addr_63_32_offset 8
#घोषणा SDMA_PKT_COPY_T2T_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_T2T_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_T2T_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_COPY_T2T_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम DW_9 word*/
/*define क्रम dst_x field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_9_dst_x_offset 9
#घोषणा SDMA_PKT_COPY_T2T_DW_9_dst_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_9_dst_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_9_DST_X(x) (((x) & SDMA_PKT_COPY_T2T_DW_9_dst_x_mask) << SDMA_PKT_COPY_T2T_DW_9_dst_x_shअगरt)

/*define क्रम dst_y field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_9_dst_y_offset 9
#घोषणा SDMA_PKT_COPY_T2T_DW_9_dst_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_9_dst_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_9_DST_Y(x) (((x) & SDMA_PKT_COPY_T2T_DW_9_dst_y_mask) << SDMA_PKT_COPY_T2T_DW_9_dst_y_shअगरt)

/*define क्रम DW_10 word*/
/*define क्रम dst_z field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_10_dst_z_offset 10
#घोषणा SDMA_PKT_COPY_T2T_DW_10_dst_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_T2T_DW_10_dst_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_10_DST_Z(x) (((x) & SDMA_PKT_COPY_T2T_DW_10_dst_z_mask) << SDMA_PKT_COPY_T2T_DW_10_dst_z_shअगरt)

/*define क्रम dst_width field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_10_dst_width_offset 10
#घोषणा SDMA_PKT_COPY_T2T_DW_10_dst_width_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_10_dst_width_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_10_DST_WIDTH(x) (((x) & SDMA_PKT_COPY_T2T_DW_10_dst_width_mask) << SDMA_PKT_COPY_T2T_DW_10_dst_width_shअगरt)

/*define क्रम DW_11 word*/
/*define क्रम dst_height field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_11_dst_height_offset 11
#घोषणा SDMA_PKT_COPY_T2T_DW_11_dst_height_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_11_dst_height_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_11_DST_HEIGHT(x) (((x) & SDMA_PKT_COPY_T2T_DW_11_dst_height_mask) << SDMA_PKT_COPY_T2T_DW_11_dst_height_shअगरt)

/*define क्रम dst_depth field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_11_dst_depth_offset 11
#घोषणा SDMA_PKT_COPY_T2T_DW_11_dst_depth_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_T2T_DW_11_dst_depth_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_11_DST_DEPTH(x) (((x) & SDMA_PKT_COPY_T2T_DW_11_dst_depth_mask) << SDMA_PKT_COPY_T2T_DW_11_dst_depth_shअगरt)

/*define क्रम DW_12 word*/
/*define क्रम dst_element_size field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_element_size_offset 12
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_element_size_mask   0x00000007
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_element_size_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_12_DST_ELEMENT_SIZE(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_element_size_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_element_size_shअगरt)

/*define क्रम dst_swizzle_mode field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_swizzle_mode_offset 12
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_swizzle_mode_mask   0x0000001F
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_swizzle_mode_shअगरt  3
#घोषणा SDMA_PKT_COPY_T2T_DW_12_DST_SWIZZLE_MODE(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_swizzle_mode_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_swizzle_mode_shअगरt)

/*define क्रम dst_dimension field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_dimension_offset 12
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_dimension_mask   0x00000003
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_dimension_shअगरt  9
#घोषणा SDMA_PKT_COPY_T2T_DW_12_DST_DIMENSION(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_dimension_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_dimension_shअगरt)

/*define क्रम dst_epitch field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_epitch_offset 12
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_epitch_mask   0x0000FFFF
#घोषणा SDMA_PKT_COPY_T2T_DW_12_dst_epitch_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_12_DST_EPITCH(x) (((x) & SDMA_PKT_COPY_T2T_DW_12_dst_epitch_mask) << SDMA_PKT_COPY_T2T_DW_12_dst_epitch_shअगरt)

/*define क्रम DW_13 word*/
/*define क्रम rect_x field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_13_rect_x_offset 13
#घोषणा SDMA_PKT_COPY_T2T_DW_13_rect_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_13_rect_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_13_RECT_X(x) (((x) & SDMA_PKT_COPY_T2T_DW_13_rect_x_mask) << SDMA_PKT_COPY_T2T_DW_13_rect_x_shअगरt)

/*define क्रम rect_y field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_13_rect_y_offset 13
#घोषणा SDMA_PKT_COPY_T2T_DW_13_rect_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_T2T_DW_13_rect_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_13_RECT_Y(x) (((x) & SDMA_PKT_COPY_T2T_DW_13_rect_y_mask) << SDMA_PKT_COPY_T2T_DW_13_rect_y_shअगरt)

/*define क्रम DW_14 word*/
/*define क्रम rect_z field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_14_rect_z_offset 14
#घोषणा SDMA_PKT_COPY_T2T_DW_14_rect_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_T2T_DW_14_rect_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_T2T_DW_14_RECT_Z(x) (((x) & SDMA_PKT_COPY_T2T_DW_14_rect_z_mask) << SDMA_PKT_COPY_T2T_DW_14_rect_z_shअगरt)

/*define क्रम dst_sw field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_14_dst_sw_offset 14
#घोषणा SDMA_PKT_COPY_T2T_DW_14_dst_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_T2T_DW_14_dst_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_T2T_DW_14_DST_SW(x) (((x) & SDMA_PKT_COPY_T2T_DW_14_dst_sw_mask) << SDMA_PKT_COPY_T2T_DW_14_dst_sw_shअगरt)

/*define क्रम src_sw field*/
#घोषणा SDMA_PKT_COPY_T2T_DW_14_src_sw_offset 14
#घोषणा SDMA_PKT_COPY_T2T_DW_14_src_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_T2T_DW_14_src_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_T2T_DW_14_SRC_SW(x) (((x) & SDMA_PKT_COPY_T2T_DW_14_src_sw_mask) << SDMA_PKT_COPY_T2T_DW_14_src_sw_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_TILED_SUBWIN packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_OP(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_HEADER_op_mask) << SDMA_PKT_COPY_TILED_SUBWIN_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_HEADER_sub_op_mask) << SDMA_PKT_COPY_TILED_SUBWIN_HEADER_sub_op_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_TILED_SUBWIN_HEADER_पंचांगz_shअगरt)

/*define क्रम mip_max field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_max_offset 0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_max_mask   0x0000000F
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_max_shअगरt  20
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_MIP_MAX(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_max_mask) << SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_max_shअगरt)

/*define क्रम mip_id field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_id_offset 0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_id_mask   0x0000000F
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_id_shअगरt  24
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_MIP_ID(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_id_mask) << SDMA_PKT_COPY_TILED_SUBWIN_HEADER_mip_id_shअगरt)

/*define क्रम detile field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_detile_offset 0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_detile_mask   0x00000001
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_detile_shअगरt  31
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_HEADER_DETILE(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_HEADER_detile_mask) << SDMA_PKT_COPY_TILED_SUBWIN_HEADER_detile_shअगरt)

/*define क्रम TILED_ADDR_LO word*/
/*define क्रम tiled_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_LO_tiled_addr_31_0_offset 1
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_LO_tiled_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_LO_tiled_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_LO_TILED_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_LO_tiled_addr_31_0_mask) << SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_LO_tiled_addr_31_0_shअगरt)

/*define क्रम TILED_ADDR_HI word*/
/*define क्रम tiled_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_HI_tiled_addr_63_32_offset 2
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_HI_tiled_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_HI_tiled_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_HI_TILED_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_HI_tiled_addr_63_32_mask) << SDMA_PKT_COPY_TILED_SUBWIN_TILED_ADDR_HI_tiled_addr_63_32_shअगरt)

/*define क्रम DW_3 word*/
/*define क्रम tiled_x field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_x_offset 3
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_3_TILED_X(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_x_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_x_shअगरt)

/*define क्रम tiled_y field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_y_offset 3
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_3_TILED_Y(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_y_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_3_tiled_y_shअगरt)

/*define क्रम DW_4 word*/
/*define क्रम tiled_z field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_4_tiled_z_offset 4
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_4_tiled_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_4_tiled_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_4_TILED_Z(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_4_tiled_z_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_4_tiled_z_shअगरt)

/*define क्रम width field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_4_width_offset 4
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_4_width_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_4_width_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_4_WIDTH(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_4_width_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_4_width_shअगरt)

/*define क्रम DW_5 word*/
/*define क्रम height field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_5_height_offset 5
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_5_height_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_5_height_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_5_HEIGHT(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_5_height_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_5_height_shअगरt)

/*define क्रम depth field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_5_depth_offset 5
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_5_depth_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_5_depth_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_5_DEPTH(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_5_depth_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_5_depth_shअगरt)

/*define क्रम DW_6 word*/
/*define क्रम element_size field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_element_size_offset 6
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_element_size_mask   0x00000007
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_element_size_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_ELEMENT_SIZE(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_6_element_size_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_6_element_size_shअगरt)

/*define क्रम swizzle_mode field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_swizzle_mode_offset 6
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_swizzle_mode_mask   0x0000001F
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_swizzle_mode_shअगरt  3
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_SWIZZLE_MODE(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_6_swizzle_mode_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_6_swizzle_mode_shअगरt)

/*define क्रम dimension field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_dimension_offset 6
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_dimension_mask   0x00000003
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_dimension_shअगरt  9
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_DIMENSION(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_6_dimension_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_6_dimension_shअगरt)

/*define क्रम epitch field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_epitch_offset 6
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_epitch_mask   0x0000FFFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_epitch_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_6_EPITCH(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_6_epitch_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_6_epitch_shअगरt)

/*define क्रम LINEAR_ADDR_LO word*/
/*define क्रम linear_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_LO_linear_addr_31_0_offset 7
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_LO_linear_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_LO_linear_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_LO_LINEAR_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_LO_linear_addr_31_0_mask) << SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_LO_linear_addr_31_0_shअगरt)

/*define क्रम LINEAR_ADDR_HI word*/
/*define क्रम linear_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_HI_linear_addr_63_32_offset 8
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_HI_linear_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_HI_linear_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_HI_LINEAR_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_HI_linear_addr_63_32_mask) << SDMA_PKT_COPY_TILED_SUBWIN_LINEAR_ADDR_HI_linear_addr_63_32_shअगरt)

/*define क्रम DW_9 word*/
/*define क्रम linear_x field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_x_offset 9
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_9_LINEAR_X(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_x_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_x_shअगरt)

/*define क्रम linear_y field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_y_offset 9
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_9_LINEAR_Y(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_y_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_9_linear_y_shअगरt)

/*define क्रम DW_10 word*/
/*define क्रम linear_z field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_z_offset 10
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_10_LINEAR_Z(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_z_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_z_shअगरt)

/*define क्रम linear_pitch field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_pitch_offset 10
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_pitch_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_pitch_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_10_LINEAR_PITCH(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_pitch_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_10_linear_pitch_shअगरt)

/*define क्रम DW_11 word*/
/*define क्रम linear_slice_pitch field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_11_linear_slice_pitch_offset 11
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_11_linear_slice_pitch_mask   0x0FFFFFFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_11_linear_slice_pitch_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_11_LINEAR_SLICE_PITCH(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_11_linear_slice_pitch_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_11_linear_slice_pitch_shअगरt)

/*define क्रम DW_12 word*/
/*define क्रम rect_x field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_x_offset 12
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_x_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_x_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_12_RECT_X(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_x_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_x_shअगरt)

/*define क्रम rect_y field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_y_offset 12
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_y_mask   0x00003FFF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_y_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_12_RECT_Y(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_y_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_12_rect_y_shअगरt)

/*define क्रम DW_13 word*/
/*define क्रम rect_z field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_rect_z_offset 13
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_rect_z_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_rect_z_shअगरt  0
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_RECT_Z(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_13_rect_z_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_13_rect_z_shअगरt)

/*define क्रम linear_sw field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_linear_sw_offset 13
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_linear_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_linear_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_LINEAR_SW(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_13_linear_sw_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_13_linear_sw_shअगरt)

/*define क्रम tile_sw field*/
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_tile_sw_offset 13
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_tile_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_tile_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_TILED_SUBWIN_DW_13_TILE_SW(x) (((x) & SDMA_PKT_COPY_TILED_SUBWIN_DW_13_tile_sw_mask) << SDMA_PKT_COPY_TILED_SUBWIN_DW_13_tile_sw_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COPY_STRUCT packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_op_offset 0
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_OP(x) (((x) & SDMA_PKT_COPY_STRUCT_HEADER_op_mask) << SDMA_PKT_COPY_STRUCT_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COPY_STRUCT_HEADER_sub_op_mask) << SDMA_PKT_COPY_STRUCT_HEADER_sub_op_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_TMZ(x) (((x) & SDMA_PKT_COPY_STRUCT_HEADER_पंचांगz_mask) << SDMA_PKT_COPY_STRUCT_HEADER_पंचांगz_shअगरt)

/*define क्रम detile field*/
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_detile_offset 0
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_detile_mask   0x00000001
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_detile_shअगरt  31
#घोषणा SDMA_PKT_COPY_STRUCT_HEADER_DETILE(x) (((x) & SDMA_PKT_COPY_STRUCT_HEADER_detile_mask) << SDMA_PKT_COPY_STRUCT_HEADER_detile_shअगरt)

/*define क्रम SB_ADDR_LO word*/
/*define क्रम sb_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_STRUCT_SB_ADDR_LO_sb_addr_31_0_offset 1
#घोषणा SDMA_PKT_COPY_STRUCT_SB_ADDR_LO_sb_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_STRUCT_SB_ADDR_LO_sb_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_STRUCT_SB_ADDR_LO_SB_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_STRUCT_SB_ADDR_LO_sb_addr_31_0_mask) << SDMA_PKT_COPY_STRUCT_SB_ADDR_LO_sb_addr_31_0_shअगरt)

/*define क्रम SB_ADDR_HI word*/
/*define क्रम sb_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_STRUCT_SB_ADDR_HI_sb_addr_63_32_offset 2
#घोषणा SDMA_PKT_COPY_STRUCT_SB_ADDR_HI_sb_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_STRUCT_SB_ADDR_HI_sb_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_STRUCT_SB_ADDR_HI_SB_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_STRUCT_SB_ADDR_HI_sb_addr_63_32_mask) << SDMA_PKT_COPY_STRUCT_SB_ADDR_HI_sb_addr_63_32_shअगरt)

/*define क्रम START_INDEX word*/
/*define क्रम start_index field*/
#घोषणा SDMA_PKT_COPY_STRUCT_START_INDEX_start_index_offset 3
#घोषणा SDMA_PKT_COPY_STRUCT_START_INDEX_start_index_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_STRUCT_START_INDEX_start_index_shअगरt  0
#घोषणा SDMA_PKT_COPY_STRUCT_START_INDEX_START_INDEX(x) (((x) & SDMA_PKT_COPY_STRUCT_START_INDEX_start_index_mask) << SDMA_PKT_COPY_STRUCT_START_INDEX_start_index_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_COPY_STRUCT_COUNT_count_offset 4
#घोषणा SDMA_PKT_COPY_STRUCT_COUNT_count_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_STRUCT_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_COPY_STRUCT_COUNT_COUNT(x) (((x) & SDMA_PKT_COPY_STRUCT_COUNT_count_mask) << SDMA_PKT_COPY_STRUCT_COUNT_count_shअगरt)

/*define क्रम DW_5 word*/
/*define क्रम stride field*/
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_stride_offset 5
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_stride_mask   0x000007FF
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_stride_shअगरt  0
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_STRIDE(x) (((x) & SDMA_PKT_COPY_STRUCT_DW_5_stride_mask) << SDMA_PKT_COPY_STRUCT_DW_5_stride_shअगरt)

/*define क्रम linear_sw field*/
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_linear_sw_offset 5
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_linear_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_linear_sw_shअगरt  16
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_LINEAR_SW(x) (((x) & SDMA_PKT_COPY_STRUCT_DW_5_linear_sw_mask) << SDMA_PKT_COPY_STRUCT_DW_5_linear_sw_shअगरt)

/*define क्रम काष्ठा_sw field*/
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_काष्ठा_sw_offset 5
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_काष्ठा_sw_mask   0x00000003
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_काष्ठा_sw_shअगरt  24
#घोषणा SDMA_PKT_COPY_STRUCT_DW_5_STRUCT_SW(x) (((x) & SDMA_PKT_COPY_STRUCT_DW_5_काष्ठा_sw_mask) << SDMA_PKT_COPY_STRUCT_DW_5_काष्ठा_sw_shअगरt)

/*define क्रम LINEAR_ADDR_LO word*/
/*define क्रम linear_addr_31_0 field*/
#घोषणा SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_LO_linear_addr_31_0_offset 6
#घोषणा SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_LO_linear_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_LO_linear_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_LO_LINEAR_ADDR_31_0(x) (((x) & SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_LO_linear_addr_31_0_mask) << SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_LO_linear_addr_31_0_shअगरt)

/*define क्रम LINEAR_ADDR_HI word*/
/*define क्रम linear_addr_63_32 field*/
#घोषणा SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_HI_linear_addr_63_32_offset 7
#घोषणा SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_HI_linear_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_HI_linear_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_HI_LINEAR_ADDR_63_32(x) (((x) & SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_HI_linear_addr_63_32_mask) << SDMA_PKT_COPY_STRUCT_LINEAR_ADDR_HI_linear_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_WRITE_UNTILED packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_op_offset 0
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_OP(x) (((x) & SDMA_PKT_WRITE_UNTILED_HEADER_op_mask) << SDMA_PKT_WRITE_UNTILED_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_SUB_OP(x) (((x) & SDMA_PKT_WRITE_UNTILED_HEADER_sub_op_mask) << SDMA_PKT_WRITE_UNTILED_HEADER_sub_op_shअगरt)

/*define क्रम encrypt field*/
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_encrypt_offset 0
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_encrypt_mask   0x00000001
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_encrypt_shअगरt  16
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_ENCRYPT(x) (((x) & SDMA_PKT_WRITE_UNTILED_HEADER_encrypt_mask) << SDMA_PKT_WRITE_UNTILED_HEADER_encrypt_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_WRITE_UNTILED_HEADER_TMZ(x) (((x) & SDMA_PKT_WRITE_UNTILED_HEADER_पंचांगz_mask) << SDMA_PKT_WRITE_UNTILED_HEADER_पंचांगz_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_WRITE_UNTILED_DST_ADDR_LO_dst_addr_31_0_offset 1
#घोषणा SDMA_PKT_WRITE_UNTILED_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_UNTILED_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_WRITE_UNTILED_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_WRITE_UNTILED_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_WRITE_UNTILED_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_WRITE_UNTILED_DST_ADDR_HI_dst_addr_63_32_offset 2
#घोषणा SDMA_PKT_WRITE_UNTILED_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_UNTILED_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_WRITE_UNTILED_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_WRITE_UNTILED_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_WRITE_UNTILED_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम DW_3 word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_WRITE_UNTILED_DW_3_count_offset 3
#घोषणा SDMA_PKT_WRITE_UNTILED_DW_3_count_mask   0x000FFFFF
#घोषणा SDMA_PKT_WRITE_UNTILED_DW_3_count_shअगरt  0
#घोषणा SDMA_PKT_WRITE_UNTILED_DW_3_COUNT(x) (((x) & SDMA_PKT_WRITE_UNTILED_DW_3_count_mask) << SDMA_PKT_WRITE_UNTILED_DW_3_count_shअगरt)

/*define क्रम sw field*/
#घोषणा SDMA_PKT_WRITE_UNTILED_DW_3_sw_offset 3
#घोषणा SDMA_PKT_WRITE_UNTILED_DW_3_sw_mask   0x00000003
#घोषणा SDMA_PKT_WRITE_UNTILED_DW_3_sw_shअगरt  24
#घोषणा SDMA_PKT_WRITE_UNTILED_DW_3_SW(x) (((x) & SDMA_PKT_WRITE_UNTILED_DW_3_sw_mask) << SDMA_PKT_WRITE_UNTILED_DW_3_sw_shअगरt)

/*define क्रम DATA0 word*/
/*define क्रम data0 field*/
#घोषणा SDMA_PKT_WRITE_UNTILED_DATA0_data0_offset 4
#घोषणा SDMA_PKT_WRITE_UNTILED_DATA0_data0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_UNTILED_DATA0_data0_shअगरt  0
#घोषणा SDMA_PKT_WRITE_UNTILED_DATA0_DATA0(x) (((x) & SDMA_PKT_WRITE_UNTILED_DATA0_data0_mask) << SDMA_PKT_WRITE_UNTILED_DATA0_data0_shअगरt)


/*
** Definitions क्रम SDMA_PKT_WRITE_TILED packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_op_offset 0
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_OP(x) (((x) & SDMA_PKT_WRITE_TILED_HEADER_op_mask) << SDMA_PKT_WRITE_TILED_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_SUB_OP(x) (((x) & SDMA_PKT_WRITE_TILED_HEADER_sub_op_mask) << SDMA_PKT_WRITE_TILED_HEADER_sub_op_shअगरt)

/*define क्रम encrypt field*/
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_encrypt_offset 0
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_encrypt_mask   0x00000001
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_encrypt_shअगरt  16
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_ENCRYPT(x) (((x) & SDMA_PKT_WRITE_TILED_HEADER_encrypt_mask) << SDMA_PKT_WRITE_TILED_HEADER_encrypt_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_TMZ(x) (((x) & SDMA_PKT_WRITE_TILED_HEADER_पंचांगz_mask) << SDMA_PKT_WRITE_TILED_HEADER_पंचांगz_shअगरt)

/*define क्रम mip_max field*/
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_mip_max_offset 0
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_mip_max_mask   0x0000000F
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_mip_max_shअगरt  20
#घोषणा SDMA_PKT_WRITE_TILED_HEADER_MIP_MAX(x) (((x) & SDMA_PKT_WRITE_TILED_HEADER_mip_max_mask) << SDMA_PKT_WRITE_TILED_HEADER_mip_max_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_WRITE_TILED_DST_ADDR_LO_dst_addr_31_0_offset 1
#घोषणा SDMA_PKT_WRITE_TILED_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_TILED_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_WRITE_TILED_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_WRITE_TILED_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_WRITE_TILED_DST_ADDR_HI_dst_addr_63_32_offset 2
#घोषणा SDMA_PKT_WRITE_TILED_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_TILED_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_WRITE_TILED_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_WRITE_TILED_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम DW_3 word*/
/*define क्रम width field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_3_width_offset 3
#घोषणा SDMA_PKT_WRITE_TILED_DW_3_width_mask   0x00003FFF
#घोषणा SDMA_PKT_WRITE_TILED_DW_3_width_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_DW_3_WIDTH(x) (((x) & SDMA_PKT_WRITE_TILED_DW_3_width_mask) << SDMA_PKT_WRITE_TILED_DW_3_width_shअगरt)

/*define क्रम DW_4 word*/
/*define क्रम height field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_4_height_offset 4
#घोषणा SDMA_PKT_WRITE_TILED_DW_4_height_mask   0x00003FFF
#घोषणा SDMA_PKT_WRITE_TILED_DW_4_height_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_DW_4_HEIGHT(x) (((x) & SDMA_PKT_WRITE_TILED_DW_4_height_mask) << SDMA_PKT_WRITE_TILED_DW_4_height_shअगरt)

/*define क्रम depth field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_4_depth_offset 4
#घोषणा SDMA_PKT_WRITE_TILED_DW_4_depth_mask   0x000007FF
#घोषणा SDMA_PKT_WRITE_TILED_DW_4_depth_shअगरt  16
#घोषणा SDMA_PKT_WRITE_TILED_DW_4_DEPTH(x) (((x) & SDMA_PKT_WRITE_TILED_DW_4_depth_mask) << SDMA_PKT_WRITE_TILED_DW_4_depth_shअगरt)

/*define क्रम DW_5 word*/
/*define क्रम element_size field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_element_size_offset 5
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_element_size_mask   0x00000007
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_element_size_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_ELEMENT_SIZE(x) (((x) & SDMA_PKT_WRITE_TILED_DW_5_element_size_mask) << SDMA_PKT_WRITE_TILED_DW_5_element_size_shअगरt)

/*define क्रम swizzle_mode field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_swizzle_mode_offset 5
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_swizzle_mode_mask   0x0000001F
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_swizzle_mode_shअगरt  3
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_SWIZZLE_MODE(x) (((x) & SDMA_PKT_WRITE_TILED_DW_5_swizzle_mode_mask) << SDMA_PKT_WRITE_TILED_DW_5_swizzle_mode_shअगरt)

/*define क्रम dimension field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_dimension_offset 5
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_dimension_mask   0x00000003
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_dimension_shअगरt  9
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_DIMENSION(x) (((x) & SDMA_PKT_WRITE_TILED_DW_5_dimension_mask) << SDMA_PKT_WRITE_TILED_DW_5_dimension_shअगरt)

/*define क्रम epitch field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_epitch_offset 5
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_epitch_mask   0x0000FFFF
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_epitch_shअगरt  16
#घोषणा SDMA_PKT_WRITE_TILED_DW_5_EPITCH(x) (((x) & SDMA_PKT_WRITE_TILED_DW_5_epitch_mask) << SDMA_PKT_WRITE_TILED_DW_5_epitch_shअगरt)

/*define क्रम DW_6 word*/
/*define क्रम x field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_6_x_offset 6
#घोषणा SDMA_PKT_WRITE_TILED_DW_6_x_mask   0x00003FFF
#घोषणा SDMA_PKT_WRITE_TILED_DW_6_x_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_DW_6_X(x) (((x) & SDMA_PKT_WRITE_TILED_DW_6_x_mask) << SDMA_PKT_WRITE_TILED_DW_6_x_shअगरt)

/*define क्रम y field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_6_y_offset 6
#घोषणा SDMA_PKT_WRITE_TILED_DW_6_y_mask   0x00003FFF
#घोषणा SDMA_PKT_WRITE_TILED_DW_6_y_shअगरt  16
#घोषणा SDMA_PKT_WRITE_TILED_DW_6_Y(x) (((x) & SDMA_PKT_WRITE_TILED_DW_6_y_mask) << SDMA_PKT_WRITE_TILED_DW_6_y_shअगरt)

/*define क्रम DW_7 word*/
/*define क्रम z field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_7_z_offset 7
#घोषणा SDMA_PKT_WRITE_TILED_DW_7_z_mask   0x000007FF
#घोषणा SDMA_PKT_WRITE_TILED_DW_7_z_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_DW_7_Z(x) (((x) & SDMA_PKT_WRITE_TILED_DW_7_z_mask) << SDMA_PKT_WRITE_TILED_DW_7_z_shअगरt)

/*define क्रम sw field*/
#घोषणा SDMA_PKT_WRITE_TILED_DW_7_sw_offset 7
#घोषणा SDMA_PKT_WRITE_TILED_DW_7_sw_mask   0x00000003
#घोषणा SDMA_PKT_WRITE_TILED_DW_7_sw_shअगरt  24
#घोषणा SDMA_PKT_WRITE_TILED_DW_7_SW(x) (((x) & SDMA_PKT_WRITE_TILED_DW_7_sw_mask) << SDMA_PKT_WRITE_TILED_DW_7_sw_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_WRITE_TILED_COUNT_count_offset 8
#घोषणा SDMA_PKT_WRITE_TILED_COUNT_count_mask   0x000FFFFF
#घोषणा SDMA_PKT_WRITE_TILED_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_COUNT_COUNT(x) (((x) & SDMA_PKT_WRITE_TILED_COUNT_count_mask) << SDMA_PKT_WRITE_TILED_COUNT_count_shअगरt)

/*define क्रम DATA0 word*/
/*define क्रम data0 field*/
#घोषणा SDMA_PKT_WRITE_TILED_DATA0_data0_offset 9
#घोषणा SDMA_PKT_WRITE_TILED_DATA0_data0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_TILED_DATA0_data0_shअगरt  0
#घोषणा SDMA_PKT_WRITE_TILED_DATA0_DATA0(x) (((x) & SDMA_PKT_WRITE_TILED_DATA0_data0_mask) << SDMA_PKT_WRITE_TILED_DATA0_data0_shअगरt)


/*
** Definitions क्रम SDMA_PKT_PTEPDE_COPY packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_op_offset 0
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_OP(x) (((x) & SDMA_PKT_PTEPDE_COPY_HEADER_op_mask) << SDMA_PKT_PTEPDE_COPY_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_SUB_OP(x) (((x) & SDMA_PKT_PTEPDE_COPY_HEADER_sub_op_mask) << SDMA_PKT_PTEPDE_COPY_HEADER_sub_op_shअगरt)

/*define क्रम ptepde_op field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_ptepde_op_offset 0
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_ptepde_op_mask   0x00000001
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_ptepde_op_shअगरt  31
#घोषणा SDMA_PKT_PTEPDE_COPY_HEADER_PTEPDE_OP(x) (((x) & SDMA_PKT_PTEPDE_COPY_HEADER_ptepde_op_mask) << SDMA_PKT_PTEPDE_COPY_HEADER_ptepde_op_shअगरt)

/*define क्रम SRC_ADDR_LO word*/
/*define क्रम src_addr_31_0 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_SRC_ADDR_LO_src_addr_31_0_offset 1
#घोषणा SDMA_PKT_PTEPDE_COPY_SRC_ADDR_LO_src_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_SRC_ADDR_LO_src_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_SRC_ADDR_LO_SRC_ADDR_31_0(x) (((x) & SDMA_PKT_PTEPDE_COPY_SRC_ADDR_LO_src_addr_31_0_mask) << SDMA_PKT_PTEPDE_COPY_SRC_ADDR_LO_src_addr_31_0_shअगरt)

/*define क्रम SRC_ADDR_HI word*/
/*define क्रम src_addr_63_32 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_SRC_ADDR_HI_src_addr_63_32_offset 2
#घोषणा SDMA_PKT_PTEPDE_COPY_SRC_ADDR_HI_src_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_SRC_ADDR_HI_src_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_SRC_ADDR_HI_SRC_ADDR_63_32(x) (((x) & SDMA_PKT_PTEPDE_COPY_SRC_ADDR_HI_src_addr_63_32_mask) << SDMA_PKT_PTEPDE_COPY_SRC_ADDR_HI_src_addr_63_32_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_DST_ADDR_LO_dst_addr_31_0_offset 3
#घोषणा SDMA_PKT_PTEPDE_COPY_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_PTEPDE_COPY_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_PTEPDE_COPY_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_DST_ADDR_HI_dst_addr_63_32_offset 4
#घोषणा SDMA_PKT_PTEPDE_COPY_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_PTEPDE_COPY_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_PTEPDE_COPY_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम MASK_DW0 word*/
/*define क्रम mask_dw0 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_MASK_DW0_mask_dw0_offset 5
#घोषणा SDMA_PKT_PTEPDE_COPY_MASK_DW0_mask_dw0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_MASK_DW0_mask_dw0_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_MASK_DW0_MASK_DW0(x) (((x) & SDMA_PKT_PTEPDE_COPY_MASK_DW0_mask_dw0_mask) << SDMA_PKT_PTEPDE_COPY_MASK_DW0_mask_dw0_shअगरt)

/*define क्रम MASK_DW1 word*/
/*define क्रम mask_dw1 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_MASK_DW1_mask_dw1_offset 6
#घोषणा SDMA_PKT_PTEPDE_COPY_MASK_DW1_mask_dw1_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_MASK_DW1_mask_dw1_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_MASK_DW1_MASK_DW1(x) (((x) & SDMA_PKT_PTEPDE_COPY_MASK_DW1_mask_dw1_mask) << SDMA_PKT_PTEPDE_COPY_MASK_DW1_mask_dw1_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_COUNT_count_offset 7
#घोषणा SDMA_PKT_PTEPDE_COPY_COUNT_count_mask   0x0007FFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_COUNT_COUNT(x) (((x) & SDMA_PKT_PTEPDE_COPY_COUNT_count_mask) << SDMA_PKT_PTEPDE_COPY_COUNT_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_PTEPDE_COPY_BACKWARDS packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_op_offset 0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_OP(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_op_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_SUB_OP(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_sub_op_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_sub_op_shअगरt)

/*define क्रम pte_size field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_pte_size_offset 0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_pte_size_mask   0x00000003
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_pte_size_shअगरt  28
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_PTE_SIZE(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_pte_size_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_pte_size_shअगरt)

/*define क्रम direction field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_direction_offset 0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_direction_mask   0x00000001
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_direction_shअगरt  30
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_सूचीECTION(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_direction_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_direction_shअगरt)

/*define क्रम ptepde_op field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_ptepde_op_offset 0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_ptepde_op_mask   0x00000001
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_ptepde_op_shअगरt  31
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_PTEPDE_OP(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_ptepde_op_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_HEADER_ptepde_op_shअगरt)

/*define क्रम SRC_ADDR_LO word*/
/*define क्रम src_addr_31_0 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_LO_src_addr_31_0_offset 1
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_LO_src_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_LO_src_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_LO_SRC_ADDR_31_0(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_LO_src_addr_31_0_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_LO_src_addr_31_0_shअगरt)

/*define क्रम SRC_ADDR_HI word*/
/*define क्रम src_addr_63_32 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_HI_src_addr_63_32_offset 2
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_HI_src_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_HI_src_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_HI_SRC_ADDR_63_32(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_HI_src_addr_63_32_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_SRC_ADDR_HI_src_addr_63_32_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_LO_dst_addr_31_0_offset 3
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_HI_dst_addr_63_32_offset 4
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम MASK_BIT_FOR_DW word*/
/*define क्रम mask_first_xfer field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_first_xfer_offset 5
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_first_xfer_mask   0x000000FF
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_first_xfer_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_MASK_FIRST_XFER(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_first_xfer_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_first_xfer_shअगरt)

/*define क्रम mask_last_xfer field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_last_xfer_offset 5
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_last_xfer_mask   0x000000FF
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_last_xfer_shअगरt  8
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_MASK_LAST_XFER(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_last_xfer_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_MASK_BIT_FOR_DW_mask_last_xfer_shअगरt)

/*define क्रम COUNT_IN_32B_XFER word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_COUNT_IN_32B_XFER_count_offset 6
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_COUNT_IN_32B_XFER_count_mask   0x0001FFFF
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_COUNT_IN_32B_XFER_count_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_COPY_BACKWARDS_COUNT_IN_32B_XFER_COUNT(x) (((x) & SDMA_PKT_PTEPDE_COPY_BACKWARDS_COUNT_IN_32B_XFER_count_mask) << SDMA_PKT_PTEPDE_COPY_BACKWARDS_COUNT_IN_32B_XFER_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_PTEPDE_RMW packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_op_offset 0
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_OP(x) (((x) & SDMA_PKT_PTEPDE_RMW_HEADER_op_mask) << SDMA_PKT_PTEPDE_RMW_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_SUB_OP(x) (((x) & SDMA_PKT_PTEPDE_RMW_HEADER_sub_op_mask) << SDMA_PKT_PTEPDE_RMW_HEADER_sub_op_shअगरt)

/*define क्रम gcc field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_gcc_offset 0
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_gcc_mask   0x00000001
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_gcc_shअगरt  19
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_GCC(x) (((x) & SDMA_PKT_PTEPDE_RMW_HEADER_gcc_mask) << SDMA_PKT_PTEPDE_RMW_HEADER_gcc_shअगरt)

/*define क्रम sys field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_sys_offset 0
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_sys_mask   0x00000001
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_sys_shअगरt  20
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_SYS(x) (((x) & SDMA_PKT_PTEPDE_RMW_HEADER_sys_mask) << SDMA_PKT_PTEPDE_RMW_HEADER_sys_shअगरt)

/*define क्रम snp field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_snp_offset 0
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_snp_mask   0x00000001
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_snp_shअगरt  22
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_SNP(x) (((x) & SDMA_PKT_PTEPDE_RMW_HEADER_snp_mask) << SDMA_PKT_PTEPDE_RMW_HEADER_snp_shअगरt)

/*define क्रम gpa field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_gpa_offset 0
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_gpa_mask   0x00000001
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_gpa_shअगरt  23
#घोषणा SDMA_PKT_PTEPDE_RMW_HEADER_GPA(x) (((x) & SDMA_PKT_PTEPDE_RMW_HEADER_gpa_mask) << SDMA_PKT_PTEPDE_RMW_HEADER_gpa_shअगरt)

/*define क्रम ADDR_LO word*/
/*define क्रम addr_31_0 field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_ADDR_LO_addr_31_0_offset 1
#घोषणा SDMA_PKT_PTEPDE_RMW_ADDR_LO_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_RMW_ADDR_LO_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_RMW_ADDR_LO_ADDR_31_0(x) (((x) & SDMA_PKT_PTEPDE_RMW_ADDR_LO_addr_31_0_mask) << SDMA_PKT_PTEPDE_RMW_ADDR_LO_addr_31_0_shअगरt)

/*define क्रम ADDR_HI word*/
/*define क्रम addr_63_32 field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_ADDR_HI_addr_63_32_offset 2
#घोषणा SDMA_PKT_PTEPDE_RMW_ADDR_HI_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_RMW_ADDR_HI_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_RMW_ADDR_HI_ADDR_63_32(x) (((x) & SDMA_PKT_PTEPDE_RMW_ADDR_HI_addr_63_32_mask) << SDMA_PKT_PTEPDE_RMW_ADDR_HI_addr_63_32_shअगरt)

/*define क्रम MASK_LO word*/
/*define क्रम mask_31_0 field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_MASK_LO_mask_31_0_offset 3
#घोषणा SDMA_PKT_PTEPDE_RMW_MASK_LO_mask_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_RMW_MASK_LO_mask_31_0_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_RMW_MASK_LO_MASK_31_0(x) (((x) & SDMA_PKT_PTEPDE_RMW_MASK_LO_mask_31_0_mask) << SDMA_PKT_PTEPDE_RMW_MASK_LO_mask_31_0_shअगरt)

/*define क्रम MASK_HI word*/
/*define क्रम mask_63_32 field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_MASK_HI_mask_63_32_offset 4
#घोषणा SDMA_PKT_PTEPDE_RMW_MASK_HI_mask_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_RMW_MASK_HI_mask_63_32_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_RMW_MASK_HI_MASK_63_32(x) (((x) & SDMA_PKT_PTEPDE_RMW_MASK_HI_mask_63_32_mask) << SDMA_PKT_PTEPDE_RMW_MASK_HI_mask_63_32_shअगरt)

/*define क्रम VALUE_LO word*/
/*define क्रम value_31_0 field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_VALUE_LO_value_31_0_offset 5
#घोषणा SDMA_PKT_PTEPDE_RMW_VALUE_LO_value_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_RMW_VALUE_LO_value_31_0_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_RMW_VALUE_LO_VALUE_31_0(x) (((x) & SDMA_PKT_PTEPDE_RMW_VALUE_LO_value_31_0_mask) << SDMA_PKT_PTEPDE_RMW_VALUE_LO_value_31_0_shअगरt)

/*define क्रम VALUE_HI word*/
/*define क्रम value_63_32 field*/
#घोषणा SDMA_PKT_PTEPDE_RMW_VALUE_HI_value_63_32_offset 6
#घोषणा SDMA_PKT_PTEPDE_RMW_VALUE_HI_value_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_PTEPDE_RMW_VALUE_HI_value_63_32_shअगरt  0
#घोषणा SDMA_PKT_PTEPDE_RMW_VALUE_HI_VALUE_63_32(x) (((x) & SDMA_PKT_PTEPDE_RMW_VALUE_HI_value_63_32_mask) << SDMA_PKT_PTEPDE_RMW_VALUE_HI_value_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_WRITE_INCR packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_WRITE_INCR_HEADER_op_offset 0
#घोषणा SDMA_PKT_WRITE_INCR_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_WRITE_INCR_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_HEADER_OP(x) (((x) & SDMA_PKT_WRITE_INCR_HEADER_op_mask) << SDMA_PKT_WRITE_INCR_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_WRITE_INCR_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_WRITE_INCR_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_WRITE_INCR_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_WRITE_INCR_HEADER_SUB_OP(x) (((x) & SDMA_PKT_WRITE_INCR_HEADER_sub_op_mask) << SDMA_PKT_WRITE_INCR_HEADER_sub_op_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_WRITE_INCR_DST_ADDR_LO_dst_addr_31_0_offset 1
#घोषणा SDMA_PKT_WRITE_INCR_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_INCR_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_WRITE_INCR_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_WRITE_INCR_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_WRITE_INCR_DST_ADDR_HI_dst_addr_63_32_offset 2
#घोषणा SDMA_PKT_WRITE_INCR_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_INCR_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_WRITE_INCR_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_WRITE_INCR_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम MASK_DW0 word*/
/*define क्रम mask_dw0 field*/
#घोषणा SDMA_PKT_WRITE_INCR_MASK_DW0_mask_dw0_offset 3
#घोषणा SDMA_PKT_WRITE_INCR_MASK_DW0_mask_dw0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_INCR_MASK_DW0_mask_dw0_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_MASK_DW0_MASK_DW0(x) (((x) & SDMA_PKT_WRITE_INCR_MASK_DW0_mask_dw0_mask) << SDMA_PKT_WRITE_INCR_MASK_DW0_mask_dw0_shअगरt)

/*define क्रम MASK_DW1 word*/
/*define क्रम mask_dw1 field*/
#घोषणा SDMA_PKT_WRITE_INCR_MASK_DW1_mask_dw1_offset 4
#घोषणा SDMA_PKT_WRITE_INCR_MASK_DW1_mask_dw1_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_INCR_MASK_DW1_mask_dw1_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_MASK_DW1_MASK_DW1(x) (((x) & SDMA_PKT_WRITE_INCR_MASK_DW1_mask_dw1_mask) << SDMA_PKT_WRITE_INCR_MASK_DW1_mask_dw1_shअगरt)

/*define क्रम INIT_DW0 word*/
/*define क्रम init_dw0 field*/
#घोषणा SDMA_PKT_WRITE_INCR_INIT_DW0_init_dw0_offset 5
#घोषणा SDMA_PKT_WRITE_INCR_INIT_DW0_init_dw0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_INCR_INIT_DW0_init_dw0_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_INIT_DW0_INIT_DW0(x) (((x) & SDMA_PKT_WRITE_INCR_INIT_DW0_init_dw0_mask) << SDMA_PKT_WRITE_INCR_INIT_DW0_init_dw0_shअगरt)

/*define क्रम INIT_DW1 word*/
/*define क्रम init_dw1 field*/
#घोषणा SDMA_PKT_WRITE_INCR_INIT_DW1_init_dw1_offset 6
#घोषणा SDMA_PKT_WRITE_INCR_INIT_DW1_init_dw1_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_INCR_INIT_DW1_init_dw1_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_INIT_DW1_INIT_DW1(x) (((x) & SDMA_PKT_WRITE_INCR_INIT_DW1_init_dw1_mask) << SDMA_PKT_WRITE_INCR_INIT_DW1_init_dw1_shअगरt)

/*define क्रम INCR_DW0 word*/
/*define क्रम incr_dw0 field*/
#घोषणा SDMA_PKT_WRITE_INCR_INCR_DW0_incr_dw0_offset 7
#घोषणा SDMA_PKT_WRITE_INCR_INCR_DW0_incr_dw0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_INCR_INCR_DW0_incr_dw0_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_INCR_DW0_INCR_DW0(x) (((x) & SDMA_PKT_WRITE_INCR_INCR_DW0_incr_dw0_mask) << SDMA_PKT_WRITE_INCR_INCR_DW0_incr_dw0_shअगरt)

/*define क्रम INCR_DW1 word*/
/*define क्रम incr_dw1 field*/
#घोषणा SDMA_PKT_WRITE_INCR_INCR_DW1_incr_dw1_offset 8
#घोषणा SDMA_PKT_WRITE_INCR_INCR_DW1_incr_dw1_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_WRITE_INCR_INCR_DW1_incr_dw1_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_INCR_DW1_INCR_DW1(x) (((x) & SDMA_PKT_WRITE_INCR_INCR_DW1_incr_dw1_mask) << SDMA_PKT_WRITE_INCR_INCR_DW1_incr_dw1_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_WRITE_INCR_COUNT_count_offset 9
#घोषणा SDMA_PKT_WRITE_INCR_COUNT_count_mask   0x0007FFFF
#घोषणा SDMA_PKT_WRITE_INCR_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_WRITE_INCR_COUNT_COUNT(x) (((x) & SDMA_PKT_WRITE_INCR_COUNT_count_mask) << SDMA_PKT_WRITE_INCR_COUNT_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_INसूचीECT packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_INसूचीECT_HEADER_op_offset 0
#घोषणा SDMA_PKT_INसूचीECT_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_INसूचीECT_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_INसूचीECT_HEADER_OP(x) (((x) & SDMA_PKT_INसूचीECT_HEADER_op_mask) << SDMA_PKT_INसूचीECT_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_INसूचीECT_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_INसूचीECT_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_INसूचीECT_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_INसूचीECT_HEADER_SUB_OP(x) (((x) & SDMA_PKT_INसूचीECT_HEADER_sub_op_mask) << SDMA_PKT_INसूचीECT_HEADER_sub_op_shअगरt)

/*define क्रम vmid field*/
#घोषणा SDMA_PKT_INसूचीECT_HEADER_vmid_offset 0
#घोषणा SDMA_PKT_INसूचीECT_HEADER_vmid_mask   0x0000000F
#घोषणा SDMA_PKT_INसूचीECT_HEADER_vmid_shअगरt  16
#घोषणा SDMA_PKT_INसूचीECT_HEADER_VMID(x) (((x) & SDMA_PKT_INसूचीECT_HEADER_vmid_mask) << SDMA_PKT_INसूचीECT_HEADER_vmid_shअगरt)

/*define क्रम BASE_LO word*/
/*define क्रम ib_base_31_0 field*/
#घोषणा SDMA_PKT_INसूचीECT_BASE_LO_ib_base_31_0_offset 1
#घोषणा SDMA_PKT_INसूचीECT_BASE_LO_ib_base_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_INसूचीECT_BASE_LO_ib_base_31_0_shअगरt  0
#घोषणा SDMA_PKT_INसूचीECT_BASE_LO_IB_BASE_31_0(x) (((x) & SDMA_PKT_INसूचीECT_BASE_LO_ib_base_31_0_mask) << SDMA_PKT_INसूचीECT_BASE_LO_ib_base_31_0_shअगरt)

/*define क्रम BASE_HI word*/
/*define क्रम ib_base_63_32 field*/
#घोषणा SDMA_PKT_INसूचीECT_BASE_HI_ib_base_63_32_offset 2
#घोषणा SDMA_PKT_INसूचीECT_BASE_HI_ib_base_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_INसूचीECT_BASE_HI_ib_base_63_32_shअगरt  0
#घोषणा SDMA_PKT_INसूचीECT_BASE_HI_IB_BASE_63_32(x) (((x) & SDMA_PKT_INसूचीECT_BASE_HI_ib_base_63_32_mask) << SDMA_PKT_INसूचीECT_BASE_HI_ib_base_63_32_shअगरt)

/*define क्रम IB_SIZE word*/
/*define क्रम ib_size field*/
#घोषणा SDMA_PKT_INसूचीECT_IB_SIZE_ib_size_offset 3
#घोषणा SDMA_PKT_INसूचीECT_IB_SIZE_ib_size_mask   0x000FFFFF
#घोषणा SDMA_PKT_INसूचीECT_IB_SIZE_ib_size_shअगरt  0
#घोषणा SDMA_PKT_INसूचीECT_IB_SIZE_IB_SIZE(x) (((x) & SDMA_PKT_INसूचीECT_IB_SIZE_ib_size_mask) << SDMA_PKT_INसूचीECT_IB_SIZE_ib_size_shअगरt)

/*define क्रम CSA_ADDR_LO word*/
/*define क्रम csa_addr_31_0 field*/
#घोषणा SDMA_PKT_INसूचीECT_CSA_ADDR_LO_csa_addr_31_0_offset 4
#घोषणा SDMA_PKT_INसूचीECT_CSA_ADDR_LO_csa_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_INसूचीECT_CSA_ADDR_LO_csa_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_INसूचीECT_CSA_ADDR_LO_CSA_ADDR_31_0(x) (((x) & SDMA_PKT_INसूचीECT_CSA_ADDR_LO_csa_addr_31_0_mask) << SDMA_PKT_INसूचीECT_CSA_ADDR_LO_csa_addr_31_0_shअगरt)

/*define क्रम CSA_ADDR_HI word*/
/*define क्रम csa_addr_63_32 field*/
#घोषणा SDMA_PKT_INसूचीECT_CSA_ADDR_HI_csa_addr_63_32_offset 5
#घोषणा SDMA_PKT_INसूचीECT_CSA_ADDR_HI_csa_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_INसूचीECT_CSA_ADDR_HI_csa_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_INसूचीECT_CSA_ADDR_HI_CSA_ADDR_63_32(x) (((x) & SDMA_PKT_INसूचीECT_CSA_ADDR_HI_csa_addr_63_32_mask) << SDMA_PKT_INसूचीECT_CSA_ADDR_HI_csa_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_SEMAPHORE packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_op_offset 0
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_OP(x) (((x) & SDMA_PKT_SEMAPHORE_HEADER_op_mask) << SDMA_PKT_SEMAPHORE_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_SUB_OP(x) (((x) & SDMA_PKT_SEMAPHORE_HEADER_sub_op_mask) << SDMA_PKT_SEMAPHORE_HEADER_sub_op_shअगरt)

/*define क्रम ग_लिखो_one field*/
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_ग_लिखो_one_offset 0
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_ग_लिखो_one_mask   0x00000001
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_ग_लिखो_one_shअगरt  29
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_WRITE_ONE(x) (((x) & SDMA_PKT_SEMAPHORE_HEADER_ग_लिखो_one_mask) << SDMA_PKT_SEMAPHORE_HEADER_ग_लिखो_one_shअगरt)

/*define क्रम संकेत field*/
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_संकेत_offset 0
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_संकेत_mask   0x00000001
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_संकेत_shअगरt  30
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_SIGNAL(x) (((x) & SDMA_PKT_SEMAPHORE_HEADER_संकेत_mask) << SDMA_PKT_SEMAPHORE_HEADER_संकेत_shअगरt)

/*define क्रम mailbox field*/
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_mailbox_offset 0
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_mailbox_mask   0x00000001
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_mailbox_shअगरt  31
#घोषणा SDMA_PKT_SEMAPHORE_HEADER_MAILBOX(x) (((x) & SDMA_PKT_SEMAPHORE_HEADER_mailbox_mask) << SDMA_PKT_SEMAPHORE_HEADER_mailbox_shअगरt)

/*define क्रम ADDR_LO word*/
/*define क्रम addr_31_0 field*/
#घोषणा SDMA_PKT_SEMAPHORE_ADDR_LO_addr_31_0_offset 1
#घोषणा SDMA_PKT_SEMAPHORE_ADDR_LO_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_SEMAPHORE_ADDR_LO_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_SEMAPHORE_ADDR_LO_ADDR_31_0(x) (((x) & SDMA_PKT_SEMAPHORE_ADDR_LO_addr_31_0_mask) << SDMA_PKT_SEMAPHORE_ADDR_LO_addr_31_0_shअगरt)

/*define क्रम ADDR_HI word*/
/*define क्रम addr_63_32 field*/
#घोषणा SDMA_PKT_SEMAPHORE_ADDR_HI_addr_63_32_offset 2
#घोषणा SDMA_PKT_SEMAPHORE_ADDR_HI_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_SEMAPHORE_ADDR_HI_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_SEMAPHORE_ADDR_HI_ADDR_63_32(x) (((x) & SDMA_PKT_SEMAPHORE_ADDR_HI_addr_63_32_mask) << SDMA_PKT_SEMAPHORE_ADDR_HI_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_FENCE packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_FENCE_HEADER_op_offset 0
#घोषणा SDMA_PKT_FENCE_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_FENCE_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_FENCE_HEADER_OP(x) (((x) & SDMA_PKT_FENCE_HEADER_op_mask) << SDMA_PKT_FENCE_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_FENCE_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_FENCE_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_FENCE_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_FENCE_HEADER_SUB_OP(x) (((x) & SDMA_PKT_FENCE_HEADER_sub_op_mask) << SDMA_PKT_FENCE_HEADER_sub_op_shअगरt)

/*define क्रम ADDR_LO word*/
/*define क्रम addr_31_0 field*/
#घोषणा SDMA_PKT_FENCE_ADDR_LO_addr_31_0_offset 1
#घोषणा SDMA_PKT_FENCE_ADDR_LO_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_FENCE_ADDR_LO_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_FENCE_ADDR_LO_ADDR_31_0(x) (((x) & SDMA_PKT_FENCE_ADDR_LO_addr_31_0_mask) << SDMA_PKT_FENCE_ADDR_LO_addr_31_0_shअगरt)

/*define क्रम ADDR_HI word*/
/*define क्रम addr_63_32 field*/
#घोषणा SDMA_PKT_FENCE_ADDR_HI_addr_63_32_offset 2
#घोषणा SDMA_PKT_FENCE_ADDR_HI_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_FENCE_ADDR_HI_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_FENCE_ADDR_HI_ADDR_63_32(x) (((x) & SDMA_PKT_FENCE_ADDR_HI_addr_63_32_mask) << SDMA_PKT_FENCE_ADDR_HI_addr_63_32_shअगरt)

/*define क्रम DATA word*/
/*define क्रम data field*/
#घोषणा SDMA_PKT_FENCE_DATA_data_offset 3
#घोषणा SDMA_PKT_FENCE_DATA_data_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_FENCE_DATA_data_shअगरt  0
#घोषणा SDMA_PKT_FENCE_DATA_DATA(x) (((x) & SDMA_PKT_FENCE_DATA_data_mask) << SDMA_PKT_FENCE_DATA_data_shअगरt)


/*
** Definitions क्रम SDMA_PKT_SRBM_WRITE packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_op_offset 0
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_OP(x) (((x) & SDMA_PKT_SRBM_WRITE_HEADER_op_mask) << SDMA_PKT_SRBM_WRITE_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_SUB_OP(x) (((x) & SDMA_PKT_SRBM_WRITE_HEADER_sub_op_mask) << SDMA_PKT_SRBM_WRITE_HEADER_sub_op_shअगरt)

/*define क्रम byte_en field*/
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_byte_en_offset 0
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_byte_en_mask   0x0000000F
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_byte_en_shअगरt  28
#घोषणा SDMA_PKT_SRBM_WRITE_HEADER_BYTE_EN(x) (((x) & SDMA_PKT_SRBM_WRITE_HEADER_byte_en_mask) << SDMA_PKT_SRBM_WRITE_HEADER_byte_en_shअगरt)

/*define क्रम ADDR word*/
/*define क्रम addr field*/
#घोषणा SDMA_PKT_SRBM_WRITE_ADDR_addr_offset 1
#घोषणा SDMA_PKT_SRBM_WRITE_ADDR_addr_mask   0x0003FFFF
#घोषणा SDMA_PKT_SRBM_WRITE_ADDR_addr_shअगरt  0
#घोषणा SDMA_PKT_SRBM_WRITE_ADDR_ADDR(x) (((x) & SDMA_PKT_SRBM_WRITE_ADDR_addr_mask) << SDMA_PKT_SRBM_WRITE_ADDR_addr_shअगरt)

/*define क्रम DATA word*/
/*define क्रम data field*/
#घोषणा SDMA_PKT_SRBM_WRITE_DATA_data_offset 2
#घोषणा SDMA_PKT_SRBM_WRITE_DATA_data_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_SRBM_WRITE_DATA_data_shअगरt  0
#घोषणा SDMA_PKT_SRBM_WRITE_DATA_DATA(x) (((x) & SDMA_PKT_SRBM_WRITE_DATA_data_mask) << SDMA_PKT_SRBM_WRITE_DATA_data_shअगरt)


/*
** Definitions क्रम SDMA_PKT_PRE_EXE packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_PRE_EXE_HEADER_op_offset 0
#घोषणा SDMA_PKT_PRE_EXE_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_PRE_EXE_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_PRE_EXE_HEADER_OP(x) (((x) & SDMA_PKT_PRE_EXE_HEADER_op_mask) << SDMA_PKT_PRE_EXE_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_PRE_EXE_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_PRE_EXE_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_PRE_EXE_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_PRE_EXE_HEADER_SUB_OP(x) (((x) & SDMA_PKT_PRE_EXE_HEADER_sub_op_mask) << SDMA_PKT_PRE_EXE_HEADER_sub_op_shअगरt)

/*define क्रम dev_sel field*/
#घोषणा SDMA_PKT_PRE_EXE_HEADER_dev_sel_offset 0
#घोषणा SDMA_PKT_PRE_EXE_HEADER_dev_sel_mask   0x000000FF
#घोषणा SDMA_PKT_PRE_EXE_HEADER_dev_sel_shअगरt  16
#घोषणा SDMA_PKT_PRE_EXE_HEADER_DEV_SEL(x) (((x) & SDMA_PKT_PRE_EXE_HEADER_dev_sel_mask) << SDMA_PKT_PRE_EXE_HEADER_dev_sel_shअगरt)

/*define क्रम EXEC_COUNT word*/
/*define क्रम exec_count field*/
#घोषणा SDMA_PKT_PRE_EXE_EXEC_COUNT_exec_count_offset 1
#घोषणा SDMA_PKT_PRE_EXE_EXEC_COUNT_exec_count_mask   0x00003FFF
#घोषणा SDMA_PKT_PRE_EXE_EXEC_COUNT_exec_count_shअगरt  0
#घोषणा SDMA_PKT_PRE_EXE_EXEC_COUNT_EXEC_COUNT(x) (((x) & SDMA_PKT_PRE_EXE_EXEC_COUNT_exec_count_mask) << SDMA_PKT_PRE_EXE_EXEC_COUNT_exec_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_COND_EXE packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_COND_EXE_HEADER_op_offset 0
#घोषणा SDMA_PKT_COND_EXE_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_COND_EXE_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_COND_EXE_HEADER_OP(x) (((x) & SDMA_PKT_COND_EXE_HEADER_op_mask) << SDMA_PKT_COND_EXE_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_COND_EXE_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_COND_EXE_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_COND_EXE_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_COND_EXE_HEADER_SUB_OP(x) (((x) & SDMA_PKT_COND_EXE_HEADER_sub_op_mask) << SDMA_PKT_COND_EXE_HEADER_sub_op_shअगरt)

/*define क्रम ADDR_LO word*/
/*define क्रम addr_31_0 field*/
#घोषणा SDMA_PKT_COND_EXE_ADDR_LO_addr_31_0_offset 1
#घोषणा SDMA_PKT_COND_EXE_ADDR_LO_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COND_EXE_ADDR_LO_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_COND_EXE_ADDR_LO_ADDR_31_0(x) (((x) & SDMA_PKT_COND_EXE_ADDR_LO_addr_31_0_mask) << SDMA_PKT_COND_EXE_ADDR_LO_addr_31_0_shअगरt)

/*define क्रम ADDR_HI word*/
/*define क्रम addr_63_32 field*/
#घोषणा SDMA_PKT_COND_EXE_ADDR_HI_addr_63_32_offset 2
#घोषणा SDMA_PKT_COND_EXE_ADDR_HI_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COND_EXE_ADDR_HI_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_COND_EXE_ADDR_HI_ADDR_63_32(x) (((x) & SDMA_PKT_COND_EXE_ADDR_HI_addr_63_32_mask) << SDMA_PKT_COND_EXE_ADDR_HI_addr_63_32_shअगरt)

/*define क्रम REFERENCE word*/
/*define क्रम reference field*/
#घोषणा SDMA_PKT_COND_EXE_REFERENCE_reference_offset 3
#घोषणा SDMA_PKT_COND_EXE_REFERENCE_reference_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_COND_EXE_REFERENCE_reference_shअगरt  0
#घोषणा SDMA_PKT_COND_EXE_REFERENCE_REFERENCE(x) (((x) & SDMA_PKT_COND_EXE_REFERENCE_reference_mask) << SDMA_PKT_COND_EXE_REFERENCE_reference_shअगरt)

/*define क्रम EXEC_COUNT word*/
/*define क्रम exec_count field*/
#घोषणा SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_offset 4
#घोषणा SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_mask   0x00003FFF
#घोषणा SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_shअगरt  0
#घोषणा SDMA_PKT_COND_EXE_EXEC_COUNT_EXEC_COUNT(x) (((x) & SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_mask) << SDMA_PKT_COND_EXE_EXEC_COUNT_exec_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_CONSTANT_FILL packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_op_offset 0
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_OP(x) (((x) & SDMA_PKT_CONSTANT_FILL_HEADER_op_mask) << SDMA_PKT_CONSTANT_FILL_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_SUB_OP(x) (((x) & SDMA_PKT_CONSTANT_FILL_HEADER_sub_op_mask) << SDMA_PKT_CONSTANT_FILL_HEADER_sub_op_shअगरt)

/*define क्रम sw field*/
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_sw_offset 0
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_sw_mask   0x00000003
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_sw_shअगरt  16
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_SW(x) (((x) & SDMA_PKT_CONSTANT_FILL_HEADER_sw_mask) << SDMA_PKT_CONSTANT_FILL_HEADER_sw_shअगरt)

/*define क्रम fillsize field*/
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_fillsize_offset 0
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_fillsize_mask   0x00000003
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_fillsize_shअगरt  30
#घोषणा SDMA_PKT_CONSTANT_FILL_HEADER_FILLSIZE(x) (((x) & SDMA_PKT_CONSTANT_FILL_HEADER_fillsize_mask) << SDMA_PKT_CONSTANT_FILL_HEADER_fillsize_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_CONSTANT_FILL_DST_ADDR_LO_dst_addr_31_0_offset 1
#घोषणा SDMA_PKT_CONSTANT_FILL_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_CONSTANT_FILL_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_CONSTANT_FILL_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_CONSTANT_FILL_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_CONSTANT_FILL_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_CONSTANT_FILL_DST_ADDR_HI_dst_addr_63_32_offset 2
#घोषणा SDMA_PKT_CONSTANT_FILL_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_CONSTANT_FILL_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_CONSTANT_FILL_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_CONSTANT_FILL_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_CONSTANT_FILL_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम DATA word*/
/*define क्रम src_data_31_0 field*/
#घोषणा SDMA_PKT_CONSTANT_FILL_DATA_src_data_31_0_offset 3
#घोषणा SDMA_PKT_CONSTANT_FILL_DATA_src_data_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_CONSTANT_FILL_DATA_src_data_31_0_shअगरt  0
#घोषणा SDMA_PKT_CONSTANT_FILL_DATA_SRC_DATA_31_0(x) (((x) & SDMA_PKT_CONSTANT_FILL_DATA_src_data_31_0_mask) << SDMA_PKT_CONSTANT_FILL_DATA_src_data_31_0_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_CONSTANT_FILL_COUNT_count_offset 4
#घोषणा SDMA_PKT_CONSTANT_FILL_COUNT_count_mask   0x003FFFFF
#घोषणा SDMA_PKT_CONSTANT_FILL_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_CONSTANT_FILL_COUNT_COUNT(x) (((x) & SDMA_PKT_CONSTANT_FILL_COUNT_count_mask) << SDMA_PKT_CONSTANT_FILL_COUNT_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_DATA_FILL_MULTI packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_op_offset 0
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_OP(x) (((x) & SDMA_PKT_DATA_FILL_MULTI_HEADER_op_mask) << SDMA_PKT_DATA_FILL_MULTI_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_SUB_OP(x) (((x) & SDMA_PKT_DATA_FILL_MULTI_HEADER_sub_op_mask) << SDMA_PKT_DATA_FILL_MULTI_HEADER_sub_op_shअगरt)

/*define क्रम memlog_clr field*/
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_memlog_clr_offset 0
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_memlog_clr_mask   0x00000001
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_memlog_clr_shअगरt  31
#घोषणा SDMA_PKT_DATA_FILL_MULTI_HEADER_MEMLOG_CLR(x) (((x) & SDMA_PKT_DATA_FILL_MULTI_HEADER_memlog_clr_mask) << SDMA_PKT_DATA_FILL_MULTI_HEADER_memlog_clr_shअगरt)

/*define क्रम BYTE_STRIDE word*/
/*define क्रम byte_stride field*/
#घोषणा SDMA_PKT_DATA_FILL_MULTI_BYTE_STRIDE_byte_stride_offset 1
#घोषणा SDMA_PKT_DATA_FILL_MULTI_BYTE_STRIDE_byte_stride_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_DATA_FILL_MULTI_BYTE_STRIDE_byte_stride_shअगरt  0
#घोषणा SDMA_PKT_DATA_FILL_MULTI_BYTE_STRIDE_BYTE_STRIDE(x) (((x) & SDMA_PKT_DATA_FILL_MULTI_BYTE_STRIDE_byte_stride_mask) << SDMA_PKT_DATA_FILL_MULTI_BYTE_STRIDE_byte_stride_shअगरt)

/*define क्रम DMA_COUNT word*/
/*define क्रम dma_count field*/
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DMA_COUNT_dma_count_offset 2
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DMA_COUNT_dma_count_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DMA_COUNT_dma_count_shअगरt  0
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DMA_COUNT_DMA_COUNT(x) (((x) & SDMA_PKT_DATA_FILL_MULTI_DMA_COUNT_dma_count_mask) << SDMA_PKT_DATA_FILL_MULTI_DMA_COUNT_dma_count_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_LO_dst_addr_31_0_offset 3
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_HI_dst_addr_63_32_offset 4
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_PKT_DATA_FILL_MULTI_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम BYTE_COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_PKT_DATA_FILL_MULTI_BYTE_COUNT_count_offset 5
#घोषणा SDMA_PKT_DATA_FILL_MULTI_BYTE_COUNT_count_mask   0x03FFFFFF
#घोषणा SDMA_PKT_DATA_FILL_MULTI_BYTE_COUNT_count_shअगरt  0
#घोषणा SDMA_PKT_DATA_FILL_MULTI_BYTE_COUNT_COUNT(x) (((x) & SDMA_PKT_DATA_FILL_MULTI_BYTE_COUNT_count_mask) << SDMA_PKT_DATA_FILL_MULTI_BYTE_COUNT_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_POLL_REGMEM packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_op_offset 0
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_OP(x) (((x) & SDMA_PKT_POLL_REGMEM_HEADER_op_mask) << SDMA_PKT_POLL_REGMEM_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_SUB_OP(x) (((x) & SDMA_PKT_POLL_REGMEM_HEADER_sub_op_mask) << SDMA_PKT_POLL_REGMEM_HEADER_sub_op_shअगरt)

/*define क्रम hdp_flush field*/
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_hdp_flush_offset 0
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_hdp_flush_mask   0x00000001
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_hdp_flush_shअगरt  26
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_HDP_FLUSH(x) (((x) & SDMA_PKT_POLL_REGMEM_HEADER_hdp_flush_mask) << SDMA_PKT_POLL_REGMEM_HEADER_hdp_flush_shअगरt)

/*define क्रम func field*/
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_func_offset 0
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_func_mask   0x00000007
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_func_shअगरt  28
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_FUNC(x) (((x) & SDMA_PKT_POLL_REGMEM_HEADER_func_mask) << SDMA_PKT_POLL_REGMEM_HEADER_func_shअगरt)

/*define क्रम mem_poll field*/
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_mem_poll_offset 0
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_mem_poll_mask   0x00000001
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_mem_poll_shअगरt  31
#घोषणा SDMA_PKT_POLL_REGMEM_HEADER_MEM_POLL(x) (((x) & SDMA_PKT_POLL_REGMEM_HEADER_mem_poll_mask) << SDMA_PKT_POLL_REGMEM_HEADER_mem_poll_shअगरt)

/*define क्रम ADDR_LO word*/
/*define क्रम addr_31_0 field*/
#घोषणा SDMA_PKT_POLL_REGMEM_ADDR_LO_addr_31_0_offset 1
#घोषणा SDMA_PKT_POLL_REGMEM_ADDR_LO_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_REGMEM_ADDR_LO_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_POLL_REGMEM_ADDR_LO_ADDR_31_0(x) (((x) & SDMA_PKT_POLL_REGMEM_ADDR_LO_addr_31_0_mask) << SDMA_PKT_POLL_REGMEM_ADDR_LO_addr_31_0_shअगरt)

/*define क्रम ADDR_HI word*/
/*define क्रम addr_63_32 field*/
#घोषणा SDMA_PKT_POLL_REGMEM_ADDR_HI_addr_63_32_offset 2
#घोषणा SDMA_PKT_POLL_REGMEM_ADDR_HI_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_REGMEM_ADDR_HI_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_POLL_REGMEM_ADDR_HI_ADDR_63_32(x) (((x) & SDMA_PKT_POLL_REGMEM_ADDR_HI_addr_63_32_mask) << SDMA_PKT_POLL_REGMEM_ADDR_HI_addr_63_32_shअगरt)

/*define क्रम VALUE word*/
/*define क्रम value field*/
#घोषणा SDMA_PKT_POLL_REGMEM_VALUE_value_offset 3
#घोषणा SDMA_PKT_POLL_REGMEM_VALUE_value_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_REGMEM_VALUE_value_shअगरt  0
#घोषणा SDMA_PKT_POLL_REGMEM_VALUE_VALUE(x) (((x) & SDMA_PKT_POLL_REGMEM_VALUE_value_mask) << SDMA_PKT_POLL_REGMEM_VALUE_value_shअगरt)

/*define क्रम MASK word*/
/*define क्रम mask field*/
#घोषणा SDMA_PKT_POLL_REGMEM_MASK_mask_offset 4
#घोषणा SDMA_PKT_POLL_REGMEM_MASK_mask_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_REGMEM_MASK_mask_shअगरt  0
#घोषणा SDMA_PKT_POLL_REGMEM_MASK_MASK(x) (((x) & SDMA_PKT_POLL_REGMEM_MASK_mask_mask) << SDMA_PKT_POLL_REGMEM_MASK_mask_shअगरt)

/*define क्रम DW5 word*/
/*define क्रम पूर्णांकerval field*/
#घोषणा SDMA_PKT_POLL_REGMEM_DW5_पूर्णांकerval_offset 5
#घोषणा SDMA_PKT_POLL_REGMEM_DW5_पूर्णांकerval_mask   0x0000FFFF
#घोषणा SDMA_PKT_POLL_REGMEM_DW5_पूर्णांकerval_shअगरt  0
#घोषणा SDMA_PKT_POLL_REGMEM_DW5_INTERVAL(x) (((x) & SDMA_PKT_POLL_REGMEM_DW5_पूर्णांकerval_mask) << SDMA_PKT_POLL_REGMEM_DW5_पूर्णांकerval_shअगरt)

/*define क्रम retry_count field*/
#घोषणा SDMA_PKT_POLL_REGMEM_DW5_retry_count_offset 5
#घोषणा SDMA_PKT_POLL_REGMEM_DW5_retry_count_mask   0x00000FFF
#घोषणा SDMA_PKT_POLL_REGMEM_DW5_retry_count_shअगरt  16
#घोषणा SDMA_PKT_POLL_REGMEM_DW5_RETRY_COUNT(x) (((x) & SDMA_PKT_POLL_REGMEM_DW5_retry_count_mask) << SDMA_PKT_POLL_REGMEM_DW5_retry_count_shअगरt)


/*
** Definitions क्रम SDMA_PKT_POLL_REG_WRITE_MEM packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_op_offset 0
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_OP(x) (((x) & SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_op_mask) << SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_SUB_OP(x) (((x) & SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_sub_op_mask) << SDMA_PKT_POLL_REG_WRITE_MEM_HEADER_sub_op_shअगरt)

/*define क्रम SRC_ADDR word*/
/*define क्रम addr_31_2 field*/
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_SRC_ADDR_addr_31_2_offset 1
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_SRC_ADDR_addr_31_2_mask   0x3FFFFFFF
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_SRC_ADDR_addr_31_2_shअगरt  2
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_SRC_ADDR_ADDR_31_2(x) (((x) & SDMA_PKT_POLL_REG_WRITE_MEM_SRC_ADDR_addr_31_2_mask) << SDMA_PKT_POLL_REG_WRITE_MEM_SRC_ADDR_addr_31_2_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम addr_31_0 field*/
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_LO_addr_31_0_offset 2
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_LO_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_LO_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_LO_ADDR_31_0(x) (((x) & SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_LO_addr_31_0_mask) << SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_LO_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम addr_63_32 field*/
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_HI_addr_63_32_offset 3
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_HI_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_HI_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_HI_ADDR_63_32(x) (((x) & SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_HI_addr_63_32_mask) << SDMA_PKT_POLL_REG_WRITE_MEM_DST_ADDR_HI_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_POLL_DBIT_WRITE_MEM packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_op_offset 0
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_OP(x) (((x) & SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_op_mask) << SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_SUB_OP(x) (((x) & SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_sub_op_mask) << SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_sub_op_shअगरt)

/*define क्रम ea field*/
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_ea_offset 0
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_ea_mask   0x00000003
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_ea_shअगरt  16
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_EA(x) (((x) & SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_ea_mask) << SDMA_PKT_POLL_DBIT_WRITE_MEM_HEADER_ea_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम addr_31_0 field*/
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_LO_addr_31_0_offset 1
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_LO_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_LO_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_LO_ADDR_31_0(x) (((x) & SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_LO_addr_31_0_mask) << SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_LO_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम addr_63_32 field*/
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_HI_addr_63_32_offset 2
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_HI_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_HI_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_HI_ADDR_63_32(x) (((x) & SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_HI_addr_63_32_mask) << SDMA_PKT_POLL_DBIT_WRITE_MEM_DST_ADDR_HI_addr_63_32_shअगरt)

/*define क्रम START_PAGE word*/
/*define क्रम addr_31_4 field*/
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_START_PAGE_addr_31_4_offset 3
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_START_PAGE_addr_31_4_mask   0x0FFFFFFF
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_START_PAGE_addr_31_4_shअगरt  4
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_START_PAGE_ADDR_31_4(x) (((x) & SDMA_PKT_POLL_DBIT_WRITE_MEM_START_PAGE_addr_31_4_mask) << SDMA_PKT_POLL_DBIT_WRITE_MEM_START_PAGE_addr_31_4_shअगरt)

/*define क्रम PAGE_NUM word*/
/*define क्रम page_num_31_0 field*/
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_PAGE_NUM_page_num_31_0_offset 4
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_PAGE_NUM_page_num_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_PAGE_NUM_page_num_31_0_shअगरt  0
#घोषणा SDMA_PKT_POLL_DBIT_WRITE_MEM_PAGE_NUM_PAGE_NUM_31_0(x) (((x) & SDMA_PKT_POLL_DBIT_WRITE_MEM_PAGE_NUM_page_num_31_0_mask) << SDMA_PKT_POLL_DBIT_WRITE_MEM_PAGE_NUM_page_num_31_0_shअगरt)


/*
** Definitions क्रम SDMA_PKT_POLL_MEM_VERIFY packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_op_offset 0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_OP(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_HEADER_op_mask) << SDMA_PKT_POLL_MEM_VERIFY_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_SUB_OP(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_HEADER_sub_op_mask) << SDMA_PKT_POLL_MEM_VERIFY_HEADER_sub_op_shअगरt)

/*define क्रम mode field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_mode_offset 0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_mode_mask   0x00000001
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_mode_shअगरt  31
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_HEADER_MODE(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_HEADER_mode_mask) << SDMA_PKT_POLL_MEM_VERIFY_HEADER_mode_shअगरt)

/*define क्रम PATTERN word*/
/*define क्रम pattern field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_PATTERN_pattern_offset 1
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_PATTERN_pattern_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_PATTERN_pattern_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_PATTERN_PATTERN(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_PATTERN_pattern_mask) << SDMA_PKT_POLL_MEM_VERIFY_PATTERN_pattern_shअगरt)

/*define क्रम CMP0_ADDR_START_LO word*/
/*define क्रम cmp0_start_31_0 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_LO_cmp0_start_31_0_offset 2
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_LO_cmp0_start_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_LO_cmp0_start_31_0_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_LO_CMP0_START_31_0(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_LO_cmp0_start_31_0_mask) << SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_LO_cmp0_start_31_0_shअगरt)

/*define क्रम CMP0_ADDR_START_HI word*/
/*define क्रम cmp0_start_63_32 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_HI_cmp0_start_63_32_offset 3
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_HI_cmp0_start_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_HI_cmp0_start_63_32_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_HI_CMP0_START_63_32(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_HI_cmp0_start_63_32_mask) << SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_START_HI_cmp0_start_63_32_shअगरt)

/*define क्रम CMP0_ADDR_END_LO word*/
/*define क्रम cmp1_end_31_0 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_LO_cmp1_end_31_0_offset 4
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_LO_cmp1_end_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_LO_cmp1_end_31_0_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_LO_CMP1_END_31_0(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_LO_cmp1_end_31_0_mask) << SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_LO_cmp1_end_31_0_shअगरt)

/*define क्रम CMP0_ADDR_END_HI word*/
/*define क्रम cmp1_end_63_32 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_HI_cmp1_end_63_32_offset 5
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_HI_cmp1_end_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_HI_cmp1_end_63_32_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_HI_CMP1_END_63_32(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_HI_cmp1_end_63_32_mask) << SDMA_PKT_POLL_MEM_VERIFY_CMP0_ADDR_END_HI_cmp1_end_63_32_shअगरt)

/*define क्रम CMP1_ADDR_START_LO word*/
/*define क्रम cmp1_start_31_0 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_LO_cmp1_start_31_0_offset 6
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_LO_cmp1_start_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_LO_cmp1_start_31_0_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_LO_CMP1_START_31_0(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_LO_cmp1_start_31_0_mask) << SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_LO_cmp1_start_31_0_shअगरt)

/*define क्रम CMP1_ADDR_START_HI word*/
/*define क्रम cmp1_start_63_32 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_HI_cmp1_start_63_32_offset 7
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_HI_cmp1_start_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_HI_cmp1_start_63_32_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_HI_CMP1_START_63_32(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_HI_cmp1_start_63_32_mask) << SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_START_HI_cmp1_start_63_32_shअगरt)

/*define क्रम CMP1_ADDR_END_LO word*/
/*define क्रम cmp1_end_31_0 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_LO_cmp1_end_31_0_offset 8
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_LO_cmp1_end_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_LO_cmp1_end_31_0_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_LO_CMP1_END_31_0(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_LO_cmp1_end_31_0_mask) << SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_LO_cmp1_end_31_0_shअगरt)

/*define क्रम CMP1_ADDR_END_HI word*/
/*define क्रम cmp1_end_63_32 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_HI_cmp1_end_63_32_offset 9
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_HI_cmp1_end_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_HI_cmp1_end_63_32_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_HI_CMP1_END_63_32(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_HI_cmp1_end_63_32_mask) << SDMA_PKT_POLL_MEM_VERIFY_CMP1_ADDR_END_HI_cmp1_end_63_32_shअगरt)

/*define क्रम REC_ADDR_LO word*/
/*define क्रम rec_31_0 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_LO_rec_31_0_offset 10
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_LO_rec_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_LO_rec_31_0_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_LO_REC_31_0(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_LO_rec_31_0_mask) << SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_LO_rec_31_0_shअगरt)

/*define क्रम REC_ADDR_HI word*/
/*define क्रम rec_63_32 field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_HI_rec_63_32_offset 11
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_HI_rec_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_HI_rec_63_32_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_HI_REC_63_32(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_HI_rec_63_32_mask) << SDMA_PKT_POLL_MEM_VERIFY_REC_ADDR_HI_rec_63_32_shअगरt)

/*define क्रम RESERVED word*/
/*define क्रम reserved field*/
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_RESERVED_reserved_offset 12
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_RESERVED_reserved_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_RESERVED_reserved_shअगरt  0
#घोषणा SDMA_PKT_POLL_MEM_VERIFY_RESERVED_RESERVED(x) (((x) & SDMA_PKT_POLL_MEM_VERIFY_RESERVED_reserved_mask) << SDMA_PKT_POLL_MEM_VERIFY_RESERVED_reserved_shअगरt)


/*
** Definitions क्रम SDMA_PKT_ATOMIC packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_ATOMIC_HEADER_op_offset 0
#घोषणा SDMA_PKT_ATOMIC_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_ATOMIC_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_ATOMIC_HEADER_OP(x) (((x) & SDMA_PKT_ATOMIC_HEADER_op_mask) << SDMA_PKT_ATOMIC_HEADER_op_shअगरt)

/*define क्रम loop field*/
#घोषणा SDMA_PKT_ATOMIC_HEADER_loop_offset 0
#घोषणा SDMA_PKT_ATOMIC_HEADER_loop_mask   0x00000001
#घोषणा SDMA_PKT_ATOMIC_HEADER_loop_shअगरt  16
#घोषणा SDMA_PKT_ATOMIC_HEADER_LOOP(x) (((x) & SDMA_PKT_ATOMIC_HEADER_loop_mask) << SDMA_PKT_ATOMIC_HEADER_loop_shअगरt)

/*define क्रम पंचांगz field*/
#घोषणा SDMA_PKT_ATOMIC_HEADER_पंचांगz_offset 0
#घोषणा SDMA_PKT_ATOMIC_HEADER_पंचांगz_mask   0x00000001
#घोषणा SDMA_PKT_ATOMIC_HEADER_पंचांगz_shअगरt  18
#घोषणा SDMA_PKT_ATOMIC_HEADER_TMZ(x) (((x) & SDMA_PKT_ATOMIC_HEADER_पंचांगz_mask) << SDMA_PKT_ATOMIC_HEADER_पंचांगz_shअगरt)

/*define क्रम atomic_op field*/
#घोषणा SDMA_PKT_ATOMIC_HEADER_atomic_op_offset 0
#घोषणा SDMA_PKT_ATOMIC_HEADER_atomic_op_mask   0x0000007F
#घोषणा SDMA_PKT_ATOMIC_HEADER_atomic_op_shअगरt  25
#घोषणा SDMA_PKT_ATOMIC_HEADER_ATOMIC_OP(x) (((x) & SDMA_PKT_ATOMIC_HEADER_atomic_op_mask) << SDMA_PKT_ATOMIC_HEADER_atomic_op_shअगरt)

/*define क्रम ADDR_LO word*/
/*define क्रम addr_31_0 field*/
#घोषणा SDMA_PKT_ATOMIC_ADDR_LO_addr_31_0_offset 1
#घोषणा SDMA_PKT_ATOMIC_ADDR_LO_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_ATOMIC_ADDR_LO_addr_31_0_shअगरt  0
#घोषणा SDMA_PKT_ATOMIC_ADDR_LO_ADDR_31_0(x) (((x) & SDMA_PKT_ATOMIC_ADDR_LO_addr_31_0_mask) << SDMA_PKT_ATOMIC_ADDR_LO_addr_31_0_shअगरt)

/*define क्रम ADDR_HI word*/
/*define क्रम addr_63_32 field*/
#घोषणा SDMA_PKT_ATOMIC_ADDR_HI_addr_63_32_offset 2
#घोषणा SDMA_PKT_ATOMIC_ADDR_HI_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_ATOMIC_ADDR_HI_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_ATOMIC_ADDR_HI_ADDR_63_32(x) (((x) & SDMA_PKT_ATOMIC_ADDR_HI_addr_63_32_mask) << SDMA_PKT_ATOMIC_ADDR_HI_addr_63_32_shअगरt)

/*define क्रम SRC_DATA_LO word*/
/*define क्रम src_data_31_0 field*/
#घोषणा SDMA_PKT_ATOMIC_SRC_DATA_LO_src_data_31_0_offset 3
#घोषणा SDMA_PKT_ATOMIC_SRC_DATA_LO_src_data_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_ATOMIC_SRC_DATA_LO_src_data_31_0_shअगरt  0
#घोषणा SDMA_PKT_ATOMIC_SRC_DATA_LO_SRC_DATA_31_0(x) (((x) & SDMA_PKT_ATOMIC_SRC_DATA_LO_src_data_31_0_mask) << SDMA_PKT_ATOMIC_SRC_DATA_LO_src_data_31_0_shअगरt)

/*define क्रम SRC_DATA_HI word*/
/*define क्रम src_data_63_32 field*/
#घोषणा SDMA_PKT_ATOMIC_SRC_DATA_HI_src_data_63_32_offset 4
#घोषणा SDMA_PKT_ATOMIC_SRC_DATA_HI_src_data_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_ATOMIC_SRC_DATA_HI_src_data_63_32_shअगरt  0
#घोषणा SDMA_PKT_ATOMIC_SRC_DATA_HI_SRC_DATA_63_32(x) (((x) & SDMA_PKT_ATOMIC_SRC_DATA_HI_src_data_63_32_mask) << SDMA_PKT_ATOMIC_SRC_DATA_HI_src_data_63_32_shअगरt)

/*define क्रम CMP_DATA_LO word*/
/*define क्रम cmp_data_31_0 field*/
#घोषणा SDMA_PKT_ATOMIC_CMP_DATA_LO_cmp_data_31_0_offset 5
#घोषणा SDMA_PKT_ATOMIC_CMP_DATA_LO_cmp_data_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_ATOMIC_CMP_DATA_LO_cmp_data_31_0_shअगरt  0
#घोषणा SDMA_PKT_ATOMIC_CMP_DATA_LO_CMP_DATA_31_0(x) (((x) & SDMA_PKT_ATOMIC_CMP_DATA_LO_cmp_data_31_0_mask) << SDMA_PKT_ATOMIC_CMP_DATA_LO_cmp_data_31_0_shअगरt)

/*define क्रम CMP_DATA_HI word*/
/*define क्रम cmp_data_63_32 field*/
#घोषणा SDMA_PKT_ATOMIC_CMP_DATA_HI_cmp_data_63_32_offset 6
#घोषणा SDMA_PKT_ATOMIC_CMP_DATA_HI_cmp_data_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_ATOMIC_CMP_DATA_HI_cmp_data_63_32_shअगरt  0
#घोषणा SDMA_PKT_ATOMIC_CMP_DATA_HI_CMP_DATA_63_32(x) (((x) & SDMA_PKT_ATOMIC_CMP_DATA_HI_cmp_data_63_32_mask) << SDMA_PKT_ATOMIC_CMP_DATA_HI_cmp_data_63_32_shअगरt)

/*define क्रम LOOP_INTERVAL word*/
/*define क्रम loop_पूर्णांकerval field*/
#घोषणा SDMA_PKT_ATOMIC_LOOP_INTERVAL_loop_पूर्णांकerval_offset 7
#घोषणा SDMA_PKT_ATOMIC_LOOP_INTERVAL_loop_पूर्णांकerval_mask   0x00001FFF
#घोषणा SDMA_PKT_ATOMIC_LOOP_INTERVAL_loop_पूर्णांकerval_shअगरt  0
#घोषणा SDMA_PKT_ATOMIC_LOOP_INTERVAL_LOOP_INTERVAL(x) (((x) & SDMA_PKT_ATOMIC_LOOP_INTERVAL_loop_पूर्णांकerval_mask) << SDMA_PKT_ATOMIC_LOOP_INTERVAL_loop_पूर्णांकerval_shअगरt)


/*
** Definitions क्रम SDMA_PKT_TIMESTAMP_SET packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_TIMESTAMP_SET_HEADER_op_offset 0
#घोषणा SDMA_PKT_TIMESTAMP_SET_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_TIMESTAMP_SET_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_TIMESTAMP_SET_HEADER_OP(x) (((x) & SDMA_PKT_TIMESTAMP_SET_HEADER_op_mask) << SDMA_PKT_TIMESTAMP_SET_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_TIMESTAMP_SET_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_TIMESTAMP_SET_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_TIMESTAMP_SET_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_TIMESTAMP_SET_HEADER_SUB_OP(x) (((x) & SDMA_PKT_TIMESTAMP_SET_HEADER_sub_op_mask) << SDMA_PKT_TIMESTAMP_SET_HEADER_sub_op_shअगरt)

/*define क्रम INIT_DATA_LO word*/
/*define क्रम init_data_31_0 field*/
#घोषणा SDMA_PKT_TIMESTAMP_SET_INIT_DATA_LO_init_data_31_0_offset 1
#घोषणा SDMA_PKT_TIMESTAMP_SET_INIT_DATA_LO_init_data_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_TIMESTAMP_SET_INIT_DATA_LO_init_data_31_0_shअगरt  0
#घोषणा SDMA_PKT_TIMESTAMP_SET_INIT_DATA_LO_INIT_DATA_31_0(x) (((x) & SDMA_PKT_TIMESTAMP_SET_INIT_DATA_LO_init_data_31_0_mask) << SDMA_PKT_TIMESTAMP_SET_INIT_DATA_LO_init_data_31_0_shअगरt)

/*define क्रम INIT_DATA_HI word*/
/*define क्रम init_data_63_32 field*/
#घोषणा SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_offset 2
#घोषणा SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_shअगरt  0
#घोषणा SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_INIT_DATA_63_32(x) (((x) & SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_mask) << SDMA_PKT_TIMESTAMP_SET_INIT_DATA_HI_init_data_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_TIMESTAMP_GET packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_TIMESTAMP_GET_HEADER_op_offset 0
#घोषणा SDMA_PKT_TIMESTAMP_GET_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_TIMESTAMP_GET_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_TIMESTAMP_GET_HEADER_OP(x) (((x) & SDMA_PKT_TIMESTAMP_GET_HEADER_op_mask) << SDMA_PKT_TIMESTAMP_GET_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_TIMESTAMP_GET_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_TIMESTAMP_GET_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_TIMESTAMP_GET_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_TIMESTAMP_GET_HEADER_SUB_OP(x) (((x) & SDMA_PKT_TIMESTAMP_GET_HEADER_sub_op_mask) << SDMA_PKT_TIMESTAMP_GET_HEADER_sub_op_shअगरt)

/*define क्रम WRITE_ADDR_LO word*/
/*define क्रम ग_लिखो_addr_31_3 field*/
#घोषणा SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_LO_ग_लिखो_addr_31_3_offset 1
#घोषणा SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_LO_ग_लिखो_addr_31_3_mask   0x1FFFFFFF
#घोषणा SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_LO_ग_लिखो_addr_31_3_shअगरt  3
#घोषणा SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_LO_WRITE_ADDR_31_3(x) (((x) & SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_LO_ग_लिखो_addr_31_3_mask) << SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_LO_ग_लिखो_addr_31_3_shअगरt)

/*define क्रम WRITE_ADDR_HI word*/
/*define क्रम ग_लिखो_addr_63_32 field*/
#घोषणा SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_HI_ग_लिखो_addr_63_32_offset 2
#घोषणा SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_HI_ग_लिखो_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_HI_ग_लिखो_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_HI_WRITE_ADDR_63_32(x) (((x) & SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_HI_ग_लिखो_addr_63_32_mask) << SDMA_PKT_TIMESTAMP_GET_WRITE_ADDR_HI_ग_लिखो_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_TIMESTAMP_GET_GLOBAL packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_op_offset 0
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_OP(x) (((x) & SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_op_mask) << SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_SUB_OP(x) (((x) & SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_sub_op_mask) << SDMA_PKT_TIMESTAMP_GET_GLOBAL_HEADER_sub_op_shअगरt)

/*define क्रम WRITE_ADDR_LO word*/
/*define क्रम ग_लिखो_addr_31_3 field*/
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_LO_ग_लिखो_addr_31_3_offset 1
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_LO_ग_लिखो_addr_31_3_mask   0x1FFFFFFF
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_LO_ग_लिखो_addr_31_3_shअगरt  3
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_LO_WRITE_ADDR_31_3(x) (((x) & SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_LO_ग_लिखो_addr_31_3_mask) << SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_LO_ग_लिखो_addr_31_3_shअगरt)

/*define क्रम WRITE_ADDR_HI word*/
/*define क्रम ग_लिखो_addr_63_32 field*/
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_HI_ग_लिखो_addr_63_32_offset 2
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_HI_ग_लिखो_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_HI_ग_लिखो_addr_63_32_shअगरt  0
#घोषणा SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_HI_WRITE_ADDR_63_32(x) (((x) & SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_HI_ग_लिखो_addr_63_32_mask) << SDMA_PKT_TIMESTAMP_GET_GLOBAL_WRITE_ADDR_HI_ग_लिखो_addr_63_32_shअगरt)


/*
** Definitions क्रम SDMA_PKT_TRAP packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_TRAP_HEADER_op_offset 0
#घोषणा SDMA_PKT_TRAP_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_TRAP_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_TRAP_HEADER_OP(x) (((x) & SDMA_PKT_TRAP_HEADER_op_mask) << SDMA_PKT_TRAP_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_TRAP_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_TRAP_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_TRAP_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_TRAP_HEADER_SUB_OP(x) (((x) & SDMA_PKT_TRAP_HEADER_sub_op_mask) << SDMA_PKT_TRAP_HEADER_sub_op_shअगरt)

/*define क्रम INT_CONTEXT word*/
/*define क्रम पूर्णांक_context field*/
#घोषणा SDMA_PKT_TRAP_INT_CONTEXT_पूर्णांक_context_offset 1
#घोषणा SDMA_PKT_TRAP_INT_CONTEXT_पूर्णांक_context_mask   0x0FFFFFFF
#घोषणा SDMA_PKT_TRAP_INT_CONTEXT_पूर्णांक_context_shअगरt  0
#घोषणा SDMA_PKT_TRAP_INT_CONTEXT_INT_CONTEXT(x) (((x) & SDMA_PKT_TRAP_INT_CONTEXT_पूर्णांक_context_mask) << SDMA_PKT_TRAP_INT_CONTEXT_पूर्णांक_context_shअगरt)


/*
** Definitions क्रम SDMA_PKT_DUMMY_TRAP packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_DUMMY_TRAP_HEADER_op_offset 0
#घोषणा SDMA_PKT_DUMMY_TRAP_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_DUMMY_TRAP_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_DUMMY_TRAP_HEADER_OP(x) (((x) & SDMA_PKT_DUMMY_TRAP_HEADER_op_mask) << SDMA_PKT_DUMMY_TRAP_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_DUMMY_TRAP_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_DUMMY_TRAP_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_DUMMY_TRAP_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_DUMMY_TRAP_HEADER_SUB_OP(x) (((x) & SDMA_PKT_DUMMY_TRAP_HEADER_sub_op_mask) << SDMA_PKT_DUMMY_TRAP_HEADER_sub_op_shअगरt)

/*define क्रम INT_CONTEXT word*/
/*define क्रम पूर्णांक_context field*/
#घोषणा SDMA_PKT_DUMMY_TRAP_INT_CONTEXT_पूर्णांक_context_offset 1
#घोषणा SDMA_PKT_DUMMY_TRAP_INT_CONTEXT_पूर्णांक_context_mask   0x0FFFFFFF
#घोषणा SDMA_PKT_DUMMY_TRAP_INT_CONTEXT_पूर्णांक_context_shअगरt  0
#घोषणा SDMA_PKT_DUMMY_TRAP_INT_CONTEXT_INT_CONTEXT(x) (((x) & SDMA_PKT_DUMMY_TRAP_INT_CONTEXT_पूर्णांक_context_mask) << SDMA_PKT_DUMMY_TRAP_INT_CONTEXT_पूर्णांक_context_shअगरt)


/*
** Definitions क्रम SDMA_PKT_NOP packet
*/

/*define क्रम HEADER word*/
/*define क्रम op field*/
#घोषणा SDMA_PKT_NOP_HEADER_op_offset 0
#घोषणा SDMA_PKT_NOP_HEADER_op_mask   0x000000FF
#घोषणा SDMA_PKT_NOP_HEADER_op_shअगरt  0
#घोषणा SDMA_PKT_NOP_HEADER_OP(x) (((x) & SDMA_PKT_NOP_HEADER_op_mask) << SDMA_PKT_NOP_HEADER_op_shअगरt)

/*define क्रम sub_op field*/
#घोषणा SDMA_PKT_NOP_HEADER_sub_op_offset 0
#घोषणा SDMA_PKT_NOP_HEADER_sub_op_mask   0x000000FF
#घोषणा SDMA_PKT_NOP_HEADER_sub_op_shअगरt  8
#घोषणा SDMA_PKT_NOP_HEADER_SUB_OP(x) (((x) & SDMA_PKT_NOP_HEADER_sub_op_mask) << SDMA_PKT_NOP_HEADER_sub_op_shअगरt)

/*define क्रम count field*/
#घोषणा SDMA_PKT_NOP_HEADER_count_offset 0
#घोषणा SDMA_PKT_NOP_HEADER_count_mask   0x00003FFF
#घोषणा SDMA_PKT_NOP_HEADER_count_shअगरt  16
#घोषणा SDMA_PKT_NOP_HEADER_COUNT(x) (((x) & SDMA_PKT_NOP_HEADER_count_mask) << SDMA_PKT_NOP_HEADER_count_shअगरt)

/*define क्रम DATA0 word*/
/*define क्रम data0 field*/
#घोषणा SDMA_PKT_NOP_DATA0_data0_offset 1
#घोषणा SDMA_PKT_NOP_DATA0_data0_mask   0xFFFFFFFF
#घोषणा SDMA_PKT_NOP_DATA0_data0_shअगरt  0
#घोषणा SDMA_PKT_NOP_DATA0_DATA0(x) (((x) & SDMA_PKT_NOP_DATA0_data0_mask) << SDMA_PKT_NOP_DATA0_data0_shअगरt)


/*
** Definitions क्रम SDMA_AQL_PKT_HEADER packet
*/

/*define क्रम HEADER word*/
/*define क्रम क्रमmat field*/
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_क्रमmat_offset 0
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_क्रमmat_mask   0x000000FF
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_क्रमmat_shअगरt  0
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_FORMAT(x) (((x) & SDMA_AQL_PKT_HEADER_HEADER_क्रमmat_mask) << SDMA_AQL_PKT_HEADER_HEADER_क्रमmat_shअगरt)

/*define क्रम barrier field*/
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_barrier_offset 0
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_barrier_mask   0x00000001
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_barrier_shअगरt  8
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_BARRIER(x) (((x) & SDMA_AQL_PKT_HEADER_HEADER_barrier_mask) << SDMA_AQL_PKT_HEADER_HEADER_barrier_shअगरt)

/*define क्रम acquire_fence_scope field*/
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_acquire_fence_scope_offset 0
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_acquire_fence_scope_mask   0x00000003
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_acquire_fence_scope_shअगरt  9
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_ACQUIRE_FENCE_SCOPE(x) (((x) & SDMA_AQL_PKT_HEADER_HEADER_acquire_fence_scope_mask) << SDMA_AQL_PKT_HEADER_HEADER_acquire_fence_scope_shअगरt)

/*define क्रम release_fence_scope field*/
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_release_fence_scope_offset 0
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_release_fence_scope_mask   0x00000003
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_release_fence_scope_shअगरt  11
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_RELEASE_FENCE_SCOPE(x) (((x) & SDMA_AQL_PKT_HEADER_HEADER_release_fence_scope_mask) << SDMA_AQL_PKT_HEADER_HEADER_release_fence_scope_shअगरt)

/*define क्रम reserved field*/
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_reserved_offset 0
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_reserved_mask   0x00000007
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_reserved_shअगरt  13
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_RESERVED(x) (((x) & SDMA_AQL_PKT_HEADER_HEADER_reserved_mask) << SDMA_AQL_PKT_HEADER_HEADER_reserved_shअगरt)

/*define क्रम op field*/
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_op_offset 0
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_op_mask   0x0000000F
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_op_shअगरt  16
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_OP(x) (((x) & SDMA_AQL_PKT_HEADER_HEADER_op_mask) << SDMA_AQL_PKT_HEADER_HEADER_op_shअगरt)

/*define क्रम subop field*/
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_subop_offset 0
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_subop_mask   0x00000007
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_subop_shअगरt  20
#घोषणा SDMA_AQL_PKT_HEADER_HEADER_SUBOP(x) (((x) & SDMA_AQL_PKT_HEADER_HEADER_subop_mask) << SDMA_AQL_PKT_HEADER_HEADER_subop_shअगरt)


/*
** Definitions क्रम SDMA_AQL_PKT_COPY_LINEAR packet
*/

/*define क्रम HEADER word*/
/*define क्रम क्रमmat field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_क्रमmat_offset 0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_क्रमmat_mask   0x000000FF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_क्रमmat_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_FORMAT(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_HEADER_क्रमmat_mask) << SDMA_AQL_PKT_COPY_LINEAR_HEADER_क्रमmat_shअगरt)

/*define क्रम barrier field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_barrier_offset 0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_barrier_mask   0x00000001
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_barrier_shअगरt  8
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_BARRIER(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_HEADER_barrier_mask) << SDMA_AQL_PKT_COPY_LINEAR_HEADER_barrier_shअगरt)

/*define क्रम acquire_fence_scope field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_acquire_fence_scope_offset 0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_acquire_fence_scope_mask   0x00000003
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_acquire_fence_scope_shअगरt  9
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_ACQUIRE_FENCE_SCOPE(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_HEADER_acquire_fence_scope_mask) << SDMA_AQL_PKT_COPY_LINEAR_HEADER_acquire_fence_scope_shअगरt)

/*define क्रम release_fence_scope field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_release_fence_scope_offset 0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_release_fence_scope_mask   0x00000003
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_release_fence_scope_shअगरt  11
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_RELEASE_FENCE_SCOPE(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_HEADER_release_fence_scope_mask) << SDMA_AQL_PKT_COPY_LINEAR_HEADER_release_fence_scope_shअगरt)

/*define क्रम reserved field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_reserved_offset 0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_reserved_mask   0x00000007
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_reserved_shअगरt  13
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_RESERVED(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_HEADER_reserved_mask) << SDMA_AQL_PKT_COPY_LINEAR_HEADER_reserved_shअगरt)

/*define क्रम op field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_op_offset 0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_op_mask   0x0000000F
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_op_shअगरt  16
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_OP(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_HEADER_op_mask) << SDMA_AQL_PKT_COPY_LINEAR_HEADER_op_shअगरt)

/*define क्रम subop field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_subop_offset 0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_subop_mask   0x00000007
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_subop_shअगरt  20
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_HEADER_SUBOP(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_HEADER_subop_mask) << SDMA_AQL_PKT_COPY_LINEAR_HEADER_subop_shअगरt)

/*define क्रम RESERVED_DW1 word*/
/*define क्रम reserved_dw1 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW1_reserved_dw1_offset 1
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW1_reserved_dw1_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW1_reserved_dw1_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW1_RESERVED_DW1(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW1_reserved_dw1_mask) << SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW1_reserved_dw1_shअगरt)

/*define क्रम RETURN_ADDR_LO word*/
/*define क्रम वापस_addr_31_0 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_LO_वापस_addr_31_0_offset 2
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_LO_वापस_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_LO_वापस_addr_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_LO_RETURN_ADDR_31_0(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_LO_वापस_addr_31_0_mask) << SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_LO_वापस_addr_31_0_shअगरt)

/*define क्रम RETURN_ADDR_HI word*/
/*define क्रम वापस_addr_63_32 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_HI_वापस_addr_63_32_offset 3
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_HI_वापस_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_HI_वापस_addr_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_HI_RETURN_ADDR_63_32(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_HI_वापस_addr_63_32_mask) << SDMA_AQL_PKT_COPY_LINEAR_RETURN_ADDR_HI_वापस_addr_63_32_shअगरt)

/*define क्रम COUNT word*/
/*define क्रम count field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COUNT_count_offset 4
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COUNT_count_mask   0x003FFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COUNT_count_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COUNT_COUNT(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_COUNT_count_mask) << SDMA_AQL_PKT_COPY_LINEAR_COUNT_count_shअगरt)

/*define क्रम PARAMETER word*/
/*define क्रम dst_sw field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_dst_sw_offset 5
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_dst_sw_mask   0x00000003
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_dst_sw_shअगरt  16
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_DST_SW(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_dst_sw_mask) << SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_dst_sw_shअगरt)

/*define क्रम src_sw field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_src_sw_offset 5
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_src_sw_mask   0x00000003
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_src_sw_shअगरt  24
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_SRC_SW(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_src_sw_mask) << SDMA_AQL_PKT_COPY_LINEAR_PARAMETER_src_sw_shअगरt)

/*define क्रम SRC_ADDR_LO word*/
/*define क्रम src_addr_31_0 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_offset 6
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_LO_SRC_ADDR_31_0(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_mask) << SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_LO_src_addr_31_0_shअगरt)

/*define क्रम SRC_ADDR_HI word*/
/*define क्रम src_addr_63_32 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_offset 7
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_HI_SRC_ADDR_63_32(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_mask) << SDMA_AQL_PKT_COPY_LINEAR_SRC_ADDR_HI_src_addr_63_32_shअगरt)

/*define क्रम DST_ADDR_LO word*/
/*define क्रम dst_addr_31_0 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_offset 8
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_LO_DST_ADDR_31_0(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_mask) << SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_LO_dst_addr_31_0_shअगरt)

/*define क्रम DST_ADDR_HI word*/
/*define क्रम dst_addr_63_32 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_offset 9
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_HI_DST_ADDR_63_32(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_mask) << SDMA_AQL_PKT_COPY_LINEAR_DST_ADDR_HI_dst_addr_63_32_shअगरt)

/*define क्रम RESERVED_DW10 word*/
/*define क्रम reserved_dw10 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW10_reserved_dw10_offset 10
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW10_reserved_dw10_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW10_reserved_dw10_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW10_RESERVED_DW10(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW10_reserved_dw10_mask) << SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW10_reserved_dw10_shअगरt)

/*define क्रम RESERVED_DW11 word*/
/*define क्रम reserved_dw11 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW11_reserved_dw11_offset 11
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW11_reserved_dw11_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW11_reserved_dw11_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW11_RESERVED_DW11(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW11_reserved_dw11_mask) << SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW11_reserved_dw11_shअगरt)

/*define क्रम RESERVED_DW12 word*/
/*define क्रम reserved_dw12 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW12_reserved_dw12_offset 12
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW12_reserved_dw12_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW12_reserved_dw12_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW12_RESERVED_DW12(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW12_reserved_dw12_mask) << SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW12_reserved_dw12_shअगरt)

/*define क्रम RESERVED_DW13 word*/
/*define क्रम reserved_dw13 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW13_reserved_dw13_offset 13
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW13_reserved_dw13_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW13_reserved_dw13_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW13_RESERVED_DW13(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW13_reserved_dw13_mask) << SDMA_AQL_PKT_COPY_LINEAR_RESERVED_DW13_reserved_dw13_shअगरt)

/*define क्रम COMPLETION_SIGNAL_LO word*/
/*define क्रम completion_संकेत_31_0 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_offset 14
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_LO_COMPLETION_SIGNAL_31_0(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_mask) << SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_shअगरt)

/*define क्रम COMPLETION_SIGNAL_HI word*/
/*define क्रम completion_संकेत_63_32 field*/
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_offset 15
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_HI_COMPLETION_SIGNAL_63_32(x) (((x) & SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_mask) << SDMA_AQL_PKT_COPY_LINEAR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_shअगरt)


/*
** Definitions क्रम SDMA_AQL_PKT_BARRIER_OR packet
*/

/*define क्रम HEADER word*/
/*define क्रम क्रमmat field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_क्रमmat_offset 0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_क्रमmat_mask   0x000000FF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_क्रमmat_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_FORMAT(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_HEADER_क्रमmat_mask) << SDMA_AQL_PKT_BARRIER_OR_HEADER_क्रमmat_shअगरt)

/*define क्रम barrier field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_barrier_offset 0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_barrier_mask   0x00000001
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_barrier_shअगरt  8
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_BARRIER(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_HEADER_barrier_mask) << SDMA_AQL_PKT_BARRIER_OR_HEADER_barrier_shअगरt)

/*define क्रम acquire_fence_scope field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_acquire_fence_scope_offset 0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_acquire_fence_scope_mask   0x00000003
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_acquire_fence_scope_shअगरt  9
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_ACQUIRE_FENCE_SCOPE(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_HEADER_acquire_fence_scope_mask) << SDMA_AQL_PKT_BARRIER_OR_HEADER_acquire_fence_scope_shअगरt)

/*define क्रम release_fence_scope field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_release_fence_scope_offset 0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_release_fence_scope_mask   0x00000003
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_release_fence_scope_shअगरt  11
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_RELEASE_FENCE_SCOPE(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_HEADER_release_fence_scope_mask) << SDMA_AQL_PKT_BARRIER_OR_HEADER_release_fence_scope_shअगरt)

/*define क्रम reserved field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_reserved_offset 0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_reserved_mask   0x00000007
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_reserved_shअगरt  13
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_RESERVED(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_HEADER_reserved_mask) << SDMA_AQL_PKT_BARRIER_OR_HEADER_reserved_shअगरt)

/*define क्रम op field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_op_offset 0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_op_mask   0x0000000F
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_op_shअगरt  16
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_OP(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_HEADER_op_mask) << SDMA_AQL_PKT_BARRIER_OR_HEADER_op_shअगरt)

/*define क्रम subop field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_subop_offset 0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_subop_mask   0x00000007
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_subop_shअगरt  20
#घोषणा SDMA_AQL_PKT_BARRIER_OR_HEADER_SUBOP(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_HEADER_subop_mask) << SDMA_AQL_PKT_BARRIER_OR_HEADER_subop_shअगरt)

/*define क्रम RESERVED_DW1 word*/
/*define क्रम reserved_dw1 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW1_reserved_dw1_offset 1
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW1_reserved_dw1_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW1_reserved_dw1_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW1_RESERVED_DW1(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW1_reserved_dw1_mask) << SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW1_reserved_dw1_shअगरt)

/*define क्रम DEPENDENT_ADDR_0_LO word*/
/*define क्रम dependent_addr_0_31_0 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_LO_dependent_addr_0_31_0_offset 2
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_LO_dependent_addr_0_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_LO_dependent_addr_0_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_LO_DEPENDENT_ADDR_0_31_0(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_LO_dependent_addr_0_31_0_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_LO_dependent_addr_0_31_0_shअगरt)

/*define क्रम DEPENDENT_ADDR_0_HI word*/
/*define क्रम dependent_addr_0_63_32 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_HI_dependent_addr_0_63_32_offset 3
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_HI_dependent_addr_0_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_HI_dependent_addr_0_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_HI_DEPENDENT_ADDR_0_63_32(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_HI_dependent_addr_0_63_32_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_0_HI_dependent_addr_0_63_32_shअगरt)

/*define क्रम DEPENDENT_ADDR_1_LO word*/
/*define क्रम dependent_addr_1_31_0 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_LO_dependent_addr_1_31_0_offset 4
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_LO_dependent_addr_1_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_LO_dependent_addr_1_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_LO_DEPENDENT_ADDR_1_31_0(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_LO_dependent_addr_1_31_0_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_LO_dependent_addr_1_31_0_shअगरt)

/*define क्रम DEPENDENT_ADDR_1_HI word*/
/*define क्रम dependent_addr_1_63_32 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_HI_dependent_addr_1_63_32_offset 5
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_HI_dependent_addr_1_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_HI_dependent_addr_1_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_HI_DEPENDENT_ADDR_1_63_32(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_HI_dependent_addr_1_63_32_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_1_HI_dependent_addr_1_63_32_shअगरt)

/*define क्रम DEPENDENT_ADDR_2_LO word*/
/*define क्रम dependent_addr_2_31_0 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_LO_dependent_addr_2_31_0_offset 6
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_LO_dependent_addr_2_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_LO_dependent_addr_2_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_LO_DEPENDENT_ADDR_2_31_0(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_LO_dependent_addr_2_31_0_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_LO_dependent_addr_2_31_0_shअगरt)

/*define क्रम DEPENDENT_ADDR_2_HI word*/
/*define क्रम dependent_addr_2_63_32 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_HI_dependent_addr_2_63_32_offset 7
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_HI_dependent_addr_2_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_HI_dependent_addr_2_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_HI_DEPENDENT_ADDR_2_63_32(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_HI_dependent_addr_2_63_32_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_2_HI_dependent_addr_2_63_32_shअगरt)

/*define क्रम DEPENDENT_ADDR_3_LO word*/
/*define क्रम dependent_addr_3_31_0 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_LO_dependent_addr_3_31_0_offset 8
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_LO_dependent_addr_3_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_LO_dependent_addr_3_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_LO_DEPENDENT_ADDR_3_31_0(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_LO_dependent_addr_3_31_0_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_LO_dependent_addr_3_31_0_shअगरt)

/*define क्रम DEPENDENT_ADDR_3_HI word*/
/*define क्रम dependent_addr_3_63_32 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_HI_dependent_addr_3_63_32_offset 9
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_HI_dependent_addr_3_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_HI_dependent_addr_3_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_HI_DEPENDENT_ADDR_3_63_32(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_HI_dependent_addr_3_63_32_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_3_HI_dependent_addr_3_63_32_shअगरt)

/*define क्रम DEPENDENT_ADDR_4_LO word*/
/*define क्रम dependent_addr_4_31_0 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_LO_dependent_addr_4_31_0_offset 10
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_LO_dependent_addr_4_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_LO_dependent_addr_4_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_LO_DEPENDENT_ADDR_4_31_0(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_LO_dependent_addr_4_31_0_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_LO_dependent_addr_4_31_0_shअगरt)

/*define क्रम DEPENDENT_ADDR_4_HI word*/
/*define क्रम dependent_addr_4_63_32 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_HI_dependent_addr_4_63_32_offset 11
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_HI_dependent_addr_4_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_HI_dependent_addr_4_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_HI_DEPENDENT_ADDR_4_63_32(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_HI_dependent_addr_4_63_32_mask) << SDMA_AQL_PKT_BARRIER_OR_DEPENDENT_ADDR_4_HI_dependent_addr_4_63_32_shअगरt)

/*define क्रम RESERVED_DW12 word*/
/*define क्रम reserved_dw12 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW12_reserved_dw12_offset 12
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW12_reserved_dw12_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW12_reserved_dw12_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW12_RESERVED_DW12(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW12_reserved_dw12_mask) << SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW12_reserved_dw12_shअगरt)

/*define क्रम RESERVED_DW13 word*/
/*define क्रम reserved_dw13 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW13_reserved_dw13_offset 13
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW13_reserved_dw13_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW13_reserved_dw13_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW13_RESERVED_DW13(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW13_reserved_dw13_mask) << SDMA_AQL_PKT_BARRIER_OR_RESERVED_DW13_reserved_dw13_shअगरt)

/*define क्रम COMPLETION_SIGNAL_LO word*/
/*define क्रम completion_संकेत_31_0 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_offset 14
#घोषणा SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_LO_COMPLETION_SIGNAL_31_0(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_mask) << SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_LO_completion_संकेत_31_0_shअगरt)

/*define क्रम COMPLETION_SIGNAL_HI word*/
/*define क्रम completion_संकेत_63_32 field*/
#घोषणा SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_offset 15
#घोषणा SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_mask   0xFFFFFFFF
#घोषणा SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_shअगरt  0
#घोषणा SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_HI_COMPLETION_SIGNAL_63_32(x) (((x) & SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_mask) << SDMA_AQL_PKT_BARRIER_OR_COMPLETION_SIGNAL_HI_completion_संकेत_63_32_shअगरt)


#पूर्ण_अगर /* __SDMA_PKT_OPEN_H_ */
