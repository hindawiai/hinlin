<शैली गुरु>
/*
 * UVD_4_2 Register करोcumentation
 *
 * Copyright (C) 2014  Advanced Micro Devices, Inc.
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

#अगर_अघोषित UVD_4_2_D_H
#घोषणा UVD_4_2_D_H

#घोषणा mmUVD_SEMA_ADDR_LOW                                                     0x3bc0
#घोषणा mmUVD_SEMA_ADDR_HIGH                                                    0x3bc1
#घोषणा mmUVD_SEMA_CMD                                                          0x3bc2
#घोषणा mmUVD_GPCOM_VCPU_CMD                                                    0x3bc3
#घोषणा mmUVD_GPCOM_VCPU_DATA0                                                  0x3bc4
#घोषणा mmUVD_GPCOM_VCPU_DATA1                                                  0x3bc5
#घोषणा mmUVD_ENGINE_CNTL                                                       0x3bc6
#घोषणा mmUVD_UDEC_ADDR_CONFIG                                                  0x3bd3
#घोषणा mmUVD_UDEC_DB_ADDR_CONFIG                                               0x3bd4
#घोषणा mmUVD_UDEC_DBW_ADDR_CONFIG                                              0x3bd5
#घोषणा mmUVD_NO_OP                                                             0x3bff
#घोषणा mmUVD_SEMA_CNTL                                                         0x3d00
#घोषणा mmUVD_LMI_EXT40_ADDR                                                    0x3d26
#घोषणा mmUVD_CTX_INDEX                                                         0x3d28
#घोषणा mmUVD_CTX_DATA                                                          0x3d29
#घोषणा mmUVD_CGC_GATE                                                          0x3d2a
#घोषणा mmUVD_CGC_STATUS                                                        0x3d2b
#घोषणा mmUVD_CGC_CTRL                                                          0x3d2c
#घोषणा mmUVD_CGC_UDEC_STATUS                                                   0x3d2d
#घोषणा mmUVD_LMI_CTRL2                                                         0x3d3d
#घोषणा mmUVD_MASTINT_EN                                                        0x3d40
#घोषणा mmUVD_LMI_ADDR_EXT                                                      0x3d65
#घोषणा mmUVD_LMI_CTRL                                                          0x3d66
#घोषणा mmUVD_LMI_STATUS                                                        0x3d67
#घोषणा mmUVD_LMI_SWAP_CNTL                                                     0x3d6d
#घोषणा mmUVD_MP_SWAP_CNTL                                                      0x3d6f
#घोषणा mmUVD_MPC_CNTL                                                          0x3d77
#घोषणा mmUVD_MPC_SET_MUXA0                                                     0x3d79
#घोषणा mmUVD_MPC_SET_MUXA1                                                     0x3d7a
#घोषणा mmUVD_MPC_SET_MUXB0                                                     0x3d7b
#घोषणा mmUVD_MPC_SET_MUXB1                                                     0x3d7c
#घोषणा mmUVD_MPC_SET_MUX                                                       0x3d7d
#घोषणा mmUVD_MPC_SET_ALU                                                       0x3d7e
#घोषणा mmUVD_VCPU_CACHE_OFFSET0                                                0x3d82
#घोषणा mmUVD_VCPU_CACHE_SIZE0                                                  0x3d83
#घोषणा mmUVD_VCPU_CACHE_OFFSET1                                                0x3d84
#घोषणा mmUVD_VCPU_CACHE_SIZE1                                                  0x3d85
#घोषणा mmUVD_VCPU_CACHE_OFFSET2                                                0x3d86
#घोषणा mmUVD_VCPU_CACHE_SIZE2                                                  0x3d87
#घोषणा mmUVD_VCPU_CNTL                                                         0x3d98
#घोषणा mmUVD_SOFT_RESET                                                        0x3da0
#घोषणा mmUVD_RBC_IB_BASE                                                       0x3da1
#घोषणा mmUVD_RBC_IB_SIZE                                                       0x3da2
#घोषणा mmUVD_RBC_RB_BASE                                                       0x3da3
#घोषणा mmUVD_RBC_RB_RPTR                                                       0x3da4
#घोषणा mmUVD_RBC_RB_WPTR                                                       0x3da5
#घोषणा mmUVD_RBC_RB_WPTR_CNTL                                                  0x3da6
#घोषणा mmUVD_RBC_RB_CNTL                                                       0x3da9
#घोषणा mmUVD_RBC_RB_RPTR_ADDR                                                  0x3daa
#घोषणा mmUVD_STATUS                                                            0x3daf
#घोषणा mmUVD_SEMA_TIMEOUT_STATUS                                               0x3db0
#घोषणा mmUVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL                                 0x3db1
#घोषणा mmUVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL                                      0x3db2
#घोषणा mmUVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL                               0x3db3
#घोषणा mmUVD_CONTEXT_ID                                                        0x3dbd
#घोषणा mmUVD_RBC_IB_SIZE_UPDATE                                                0x3df1
#घोषणा ixUVD_LMI_CACHE_CTRL                                                    0x9b
#घोषणा ixUVD_LMI_SWAP_CNTL2                                                    0xaa
#घोषणा ixUVD_LMI_ADDR_EXT2                                                     0xab
#घोषणा ixUVD_CGC_MEM_CTRL                                                      0xc0
#घोषणा ixUVD_CGC_CTRL2                                                         0xc1
#घोषणा mmUVD_PGFSM_CONFIG                                                      0x38f8
#घोषणा mmUVD_PGFSM_READ_TILE1                                                  0x38fa
#घोषणा mmUVD_PGFSM_READ_TILE2                                                  0x38fb
#घोषणा mmUVD_POWER_STATUS                                                      0x38fc
#घोषणा ixUVD_MIF_CURR_ADDR_CONFIG                                              0x48
#घोषणा ixUVD_MIF_REF_ADDR_CONFIG                                               0x4c
#घोषणा ixUVD_MIF_RECON1_ADDR_CONFIG                                            0x114

#पूर्ण_अगर /* UVD_4_2_D_H */
