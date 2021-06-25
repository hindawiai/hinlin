<शैली गुरु>
/*
 *
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित UVD_4_0_D_H
#घोषणा UVD_4_0_D_H

#घोषणा ixUVD_CGC_CTRL2 0x00C1
#घोषणा ixUVD_CGC_MEM_CTRL 0x00C0
#घोषणा ixUVD_LMI_ADDR_EXT2 0x00AB
#घोषणा ixUVD_LMI_CACHE_CTRL 0x009B
#घोषणा ixUVD_LMI_SWAP_CNTL2 0x00AA
#घोषणा ixUVD_MIF_CURR_ADDR_CONFIG 0x0048
#घोषणा ixUVD_MIF_RECON1_ADDR_CONFIG 0x0114
#घोषणा ixUVD_MIF_REF_ADDR_CONFIG 0x004C
#घोषणा mmUVD_CGC_CTRL 0x3D2C
#घोषणा mmUVD_CGC_GATE 0x3D2A
#घोषणा mmUVD_CGC_STATUS 0x3D2B
#घोषणा mmUVD_CGC_UDEC_STATUS 0x3D2D
#घोषणा mmUVD_CONTEXT_ID 0x3DBD
#घोषणा mmUVD_CTX_DATA 0x3D29
#घोषणा mmUVD_CTX_INDEX 0x3D28
#घोषणा mmUVD_ENGINE_CNTL 0x3BC6
#घोषणा mmUVD_GPCOM_VCPU_CMD 0x3BC3
#घोषणा mmUVD_GPCOM_VCPU_DATA0 0x3BC4
#घोषणा mmUVD_GPCOM_VCPU_DATA1 0x3BC5
#घोषणा mmUVD_GP_SCRATCH4 0x3D38
#घोषणा mmUVD_LMI_ADDR_EXT 0x3D65
#घोषणा mmUVD_LMI_CTRL 0x3D66
#घोषणा mmUVD_LMI_CTRL2 0x3D3D
#घोषणा mmUVD_LMI_EXT40_ADDR 0x3D26
#घोषणा mmUVD_LMI_STATUS 0x3D67
#घोषणा mmUVD_LMI_SWAP_CNTL 0x3D6D
#घोषणा mmUVD_MASTINT_EN 0x3D40
#घोषणा mmUVD_MPC_CNTL 0x3D77
#घोषणा mmUVD_MPC_SET_ALU 0x3D7E
#घोषणा mmUVD_MPC_SET_MUX 0x3D7D
#घोषणा mmUVD_MPC_SET_MUXA0 0x3D79
#घोषणा mmUVD_MPC_SET_MUXA1 0x3D7A
#घोषणा mmUVD_MPC_SET_MUXB0 0x3D7B
#घोषणा mmUVD_MPC_SET_MUXB1 0x3D7C
#घोषणा mmUVD_MP_SWAP_CNTL 0x3D6F
#घोषणा mmUVD_NO_OP 0x3BFF
#घोषणा mmUVD_PGFSM_CONFIG 0x38F8
#घोषणा mmUVD_PGFSM_READ_TILE1 0x38FA
#घोषणा mmUVD_PGFSM_READ_TILE2 0x38FB
#घोषणा mmUVD_POWER_STATUS 0x38FC
#घोषणा mmUVD_RBC_IB_BASE 0x3DA1
#घोषणा mmUVD_RBC_IB_SIZE 0x3DA2
#घोषणा mmUVD_RBC_IB_SIZE_UPDATE 0x3DF1
#घोषणा mmUVD_RBC_RB_BASE 0x3DA3
#घोषणा mmUVD_RBC_RB_CNTL 0x3DA9
#घोषणा mmUVD_RBC_RB_RPTR 0x3DA4
#घोषणा mmUVD_RBC_RB_RPTR_ADDR 0x3DAA
#घोषणा mmUVD_RBC_RB_WPTR 0x3DA5
#घोषणा mmUVD_RBC_RB_WPTR_CNTL 0x3DA6
#घोषणा mmUVD_SEMA_ADDR_HIGH 0x3BC1
#घोषणा mmUVD_SEMA_ADDR_LOW 0x3BC0
#घोषणा mmUVD_SEMA_CMD 0x3BC2
#घोषणा mmUVD_SEMA_CNTL 0x3D00
#घोषणा mmUVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL 0x3DB3
#घोषणा mmUVD_SEMA_TIMEOUT_STATUS 0x3DB0
#घोषणा mmUVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL 0x3DB2
#घोषणा mmUVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL 0x3DB1
#घोषणा mmUVD_SOFT_RESET 0x3DA0
#घोषणा mmUVD_STATUS 0x3DAF
#घोषणा mmUVD_UDEC_ADDR_CONFIG 0x3BD3
#घोषणा mmUVD_UDEC_DB_ADDR_CONFIG 0x3BD4
#घोषणा mmUVD_UDEC_DBW_ADDR_CONFIG 0x3BD5
#घोषणा mmUVD_VCPU_CACHE_OFFSET0 0x3D36
#घोषणा mmUVD_VCPU_CACHE_OFFSET1 0x3D38
#घोषणा mmUVD_VCPU_CACHE_OFFSET2 0x3D3A
#घोषणा mmUVD_VCPU_CACHE_SIZE0 0x3D37
#घोषणा mmUVD_VCPU_CACHE_SIZE1 0x3D39
#घोषणा mmUVD_VCPU_CACHE_SIZE2 0x3D3B
#घोषणा mmUVD_VCPU_CNTL 0x3D98

#पूर्ण_अगर
