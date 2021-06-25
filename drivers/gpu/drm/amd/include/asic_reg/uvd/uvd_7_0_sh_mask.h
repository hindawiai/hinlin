<शैली गुरु>
/*
 * Copyright (C) 2017  Advanced Micro Devices, Inc.
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
#अगर_अघोषित _uvd_7_0_SH_MASK_HEADER
#घोषणा _uvd_7_0_SH_MASK_HEADER


// addressBlock: uvd0_uvd_pg_dec
//UVD_POWER_STATUS
#घोषणा UVD_POWER_STATUS__UVD_POWER_STATUS__SHIFT                                                             0x0
#घोषणा UVD_POWER_STATUS__UVD_PG_MODE__SHIFT                                                                  0x2
#घोषणा UVD_POWER_STATUS__UVD_STATUS_CHECK_TIMEOUT__SHIFT                                                     0x3
#घोषणा UVD_POWER_STATUS__PWR_ON_CHECK_TIMEOUT__SHIFT                                                         0x4
#घोषणा UVD_POWER_STATUS__PWR_OFF_CHECK_TIMEOUT__SHIFT                                                        0x5
#घोषणा UVD_POWER_STATUS__UVD_PGFSM_TIMEOUT_MODE__SHIFT                                                       0x6
#घोषणा UVD_POWER_STATUS__UVD_PG_EN__SHIFT                                                                    0x8
#घोषणा UVD_POWER_STATUS__PAUSE_DPG_REQ__SHIFT                                                                0x9
#घोषणा UVD_POWER_STATUS__PAUSE_DPG_ACK__SHIFT                                                                0xa
#घोषणा UVD_POWER_STATUS__UVD_POWER_STATUS_MASK                                                               0x00000003L
#घोषणा UVD_POWER_STATUS__UVD_PG_MODE_MASK                                                                    0x00000004L
#घोषणा UVD_POWER_STATUS__UVD_STATUS_CHECK_TIMEOUT_MASK                                                       0x00000008L
#घोषणा UVD_POWER_STATUS__PWR_ON_CHECK_TIMEOUT_MASK                                                           0x00000010L
#घोषणा UVD_POWER_STATUS__PWR_OFF_CHECK_TIMEOUT_MASK                                                          0x00000020L
#घोषणा UVD_POWER_STATUS__UVD_PGFSM_TIMEOUT_MODE_MASK                                                         0x000000C0L
#घोषणा UVD_POWER_STATUS__UVD_PG_EN_MASK                                                                      0x00000100L
#घोषणा UVD_POWER_STATUS__PAUSE_DPG_REQ_MASK                                                                  0x00000200L
#घोषणा UVD_POWER_STATUS__PAUSE_DPG_ACK_MASK                                                                  0x00000400L
//UVD_DPG_RBC_RB_CNTL
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_BUFSZ__SHIFT                                                                  0x0
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_BLKSZ__SHIFT                                                                  0x8
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_NO_FETCH__SHIFT                                                               0x10
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_WPTR_POLL_EN__SHIFT                                                           0x14
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_NO_UPDATE__SHIFT                                                              0x18
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_RPTR_WR_EN__SHIFT                                                             0x1c
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_BUFSZ_MASK                                                                    0x0000001FL
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_BLKSZ_MASK                                                                    0x00001F00L
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_NO_FETCH_MASK                                                                 0x00010000L
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_WPTR_POLL_EN_MASK                                                             0x00100000L
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_NO_UPDATE_MASK                                                                0x01000000L
#घोषणा UVD_DPG_RBC_RB_CNTL__RB_RPTR_WR_EN_MASK                                                               0x10000000L
//UVD_DPG_RBC_RB_BASE_LOW
#घोषणा UVD_DPG_RBC_RB_BASE_LOW__RB_BASE_LOW__SHIFT                                                           0x0
#घोषणा UVD_DPG_RBC_RB_BASE_LOW__RB_BASE_LOW_MASK                                                             0xFFFFFFFFL
//UVD_DPG_RBC_RB_BASE_HIGH
#घोषणा UVD_DPG_RBC_RB_BASE_HIGH__RB_BASE_HIGH__SHIFT                                                         0x0
#घोषणा UVD_DPG_RBC_RB_BASE_HIGH__RB_BASE_HIGH_MASK                                                           0xFFFFFFFFL
//UVD_DPG_RBC_RB_WPTR_CNTL
#घोषणा UVD_DPG_RBC_RB_WPTR_CNTL__RB_PRE_WRITE_TIMER__SHIFT                                                   0x0
#घोषणा UVD_DPG_RBC_RB_WPTR_CNTL__RB_PRE_WRITE_TIMER_MASK                                                     0x00007FFFL
//UVD_DPG_RBC_RB_RPTR
#घोषणा UVD_DPG_RBC_RB_RPTR__RB_RPTR__SHIFT                                                                   0x4
#घोषणा UVD_DPG_RBC_RB_RPTR__RB_RPTR_MASK                                                                     0x007FFFF0L
//UVD_DPG_RBC_RB_WPTR
#घोषणा UVD_DPG_RBC_RB_WPTR__RB_WPTR__SHIFT                                                                   0x4
#घोषणा UVD_DPG_RBC_RB_WPTR__RB_WPTR_MASK                                                                     0x007FFFF0L
//UVD_DPG_LMI_VCPU_CACHE_64BIT_BAR_LOW
#घोषणा UVD_DPG_LMI_VCPU_CACHE_64BIT_BAR_LOW__BITS_31_0__SHIFT                                                0x0
#घोषणा UVD_DPG_LMI_VCPU_CACHE_64BIT_BAR_LOW__BITS_31_0_MASK                                                  0xFFFFFFFFL
//UVD_DPG_LMI_VCPU_CACHE_64BIT_BAR_HIGH
#घोषणा UVD_DPG_LMI_VCPU_CACHE_64BIT_BAR_HIGH__BITS_63_32__SHIFT                                              0x0
#घोषणा UVD_DPG_LMI_VCPU_CACHE_64BIT_BAR_HIGH__BITS_63_32_MASK                                                0xFFFFFFFFL
//UVD_DPG_VCPU_CACHE_OFFSET0
#घोषणा UVD_DPG_VCPU_CACHE_OFFSET0__CACHE_OFFSET0__SHIFT                                                      0x0
#घोषणा UVD_DPG_VCPU_CACHE_OFFSET0__CACHE_OFFSET0_MASK                                                        0x01FFFFFFL


// addressBlock: uvd0_uvdnpdec
//UVD_JPEG_ADDR_CONFIG
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_PIPES__SHIFT                                                                0x0
#घोषणा UVD_JPEG_ADDR_CONFIG__PIPE_INTERLEAVE_SIZE__SHIFT                                                     0x3
#घोषणा UVD_JPEG_ADDR_CONFIG__MAX_COMPRESSED_FRAGS__SHIFT                                                     0x6
#घोषणा UVD_JPEG_ADDR_CONFIG__BANK_INTERLEAVE_SIZE__SHIFT                                                     0x8
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_BANKS__SHIFT                                                                0xc
#घोषणा UVD_JPEG_ADDR_CONFIG__SHADER_ENGINE_TILE_SIZE__SHIFT                                                  0x10
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_SHADER_ENGINES__SHIFT                                                       0x13
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_GPUS__SHIFT                                                                 0x15
#घोषणा UVD_JPEG_ADDR_CONFIG__MULTI_GPU_TILE_SIZE__SHIFT                                                      0x18
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_RB_PER_SE__SHIFT                                                            0x1a
#घोषणा UVD_JPEG_ADDR_CONFIG__ROW_SIZE__SHIFT                                                                 0x1c
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_LOWER_PIPES__SHIFT                                                          0x1e
#घोषणा UVD_JPEG_ADDR_CONFIG__SE_ENABLE__SHIFT                                                                0x1f
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_PIPES_MASK                                                                  0x00000007L
#घोषणा UVD_JPEG_ADDR_CONFIG__PIPE_INTERLEAVE_SIZE_MASK                                                       0x00000038L
#घोषणा UVD_JPEG_ADDR_CONFIG__MAX_COMPRESSED_FRAGS_MASK                                                       0x000000C0L
#घोषणा UVD_JPEG_ADDR_CONFIG__BANK_INTERLEAVE_SIZE_MASK                                                       0x00000700L
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_BANKS_MASK                                                                  0x00007000L
#घोषणा UVD_JPEG_ADDR_CONFIG__SHADER_ENGINE_TILE_SIZE_MASK                                                    0x00070000L
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_SHADER_ENGINES_MASK                                                         0x00180000L
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_GPUS_MASK                                                                   0x00E00000L
#घोषणा UVD_JPEG_ADDR_CONFIG__MULTI_GPU_TILE_SIZE_MASK                                                        0x03000000L
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_RB_PER_SE_MASK                                                              0x0C000000L
#घोषणा UVD_JPEG_ADDR_CONFIG__ROW_SIZE_MASK                                                                   0x30000000L
#घोषणा UVD_JPEG_ADDR_CONFIG__NUM_LOWER_PIPES_MASK                                                            0x40000000L
#घोषणा UVD_JPEG_ADDR_CONFIG__SE_ENABLE_MASK                                                                  0x80000000L
//UVD_GPCOM_VCPU_CMD
#घोषणा UVD_GPCOM_VCPU_CMD__CMD_SEND__SHIFT                                                                   0x0
#घोषणा UVD_GPCOM_VCPU_CMD__CMD__SHIFT                                                                        0x1
#घोषणा UVD_GPCOM_VCPU_CMD__CMD_SOURCE__SHIFT                                                                 0x1f
#घोषणा UVD_GPCOM_VCPU_CMD__CMD_SEND_MASK                                                                     0x00000001L
#घोषणा UVD_GPCOM_VCPU_CMD__CMD_MASK                                                                          0x7FFFFFFEL
#घोषणा UVD_GPCOM_VCPU_CMD__CMD_SOURCE_MASK                                                                   0x80000000L
//UVD_GPCOM_VCPU_DATA0
#घोषणा UVD_GPCOM_VCPU_DATA0__DATA0__SHIFT                                                                    0x0
#घोषणा UVD_GPCOM_VCPU_DATA0__DATA0_MASK                                                                      0xFFFFFFFFL
//UVD_GPCOM_VCPU_DATA1
#घोषणा UVD_GPCOM_VCPU_DATA1__DATA1__SHIFT                                                                    0x0
#घोषणा UVD_GPCOM_VCPU_DATA1__DATA1_MASK                                                                      0xFFFFFFFFL
//UVD_UDEC_ADDR_CONFIG
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_PIPES__SHIFT                                                                0x0
#घोषणा UVD_UDEC_ADDR_CONFIG__PIPE_INTERLEAVE_SIZE__SHIFT                                                     0x3
#घोषणा UVD_UDEC_ADDR_CONFIG__MAX_COMPRESSED_FRAGS__SHIFT                                                     0x6
#घोषणा UVD_UDEC_ADDR_CONFIG__BANK_INTERLEAVE_SIZE__SHIFT                                                     0x8
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_BANKS__SHIFT                                                                0xc
#घोषणा UVD_UDEC_ADDR_CONFIG__SHADER_ENGINE_TILE_SIZE__SHIFT                                                  0x10
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_SHADER_ENGINES__SHIFT                                                       0x13
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_GPUS__SHIFT                                                                 0x15
#घोषणा UVD_UDEC_ADDR_CONFIG__MULTI_GPU_TILE_SIZE__SHIFT                                                      0x18
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_RB_PER_SE__SHIFT                                                            0x1a
#घोषणा UVD_UDEC_ADDR_CONFIG__ROW_SIZE__SHIFT                                                                 0x1c
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_LOWER_PIPES__SHIFT                                                          0x1e
#घोषणा UVD_UDEC_ADDR_CONFIG__SE_ENABLE__SHIFT                                                                0x1f
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_PIPES_MASK                                                                  0x00000007L
#घोषणा UVD_UDEC_ADDR_CONFIG__PIPE_INTERLEAVE_SIZE_MASK                                                       0x00000038L
#घोषणा UVD_UDEC_ADDR_CONFIG__MAX_COMPRESSED_FRAGS_MASK                                                       0x000000C0L
#घोषणा UVD_UDEC_ADDR_CONFIG__BANK_INTERLEAVE_SIZE_MASK                                                       0x00000700L
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_BANKS_MASK                                                                  0x00007000L
#घोषणा UVD_UDEC_ADDR_CONFIG__SHADER_ENGINE_TILE_SIZE_MASK                                                    0x00070000L
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_SHADER_ENGINES_MASK                                                         0x00180000L
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_GPUS_MASK                                                                   0x00E00000L
#घोषणा UVD_UDEC_ADDR_CONFIG__MULTI_GPU_TILE_SIZE_MASK                                                        0x03000000L
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_RB_PER_SE_MASK                                                              0x0C000000L
#घोषणा UVD_UDEC_ADDR_CONFIG__ROW_SIZE_MASK                                                                   0x30000000L
#घोषणा UVD_UDEC_ADDR_CONFIG__NUM_LOWER_PIPES_MASK                                                            0x40000000L
#घोषणा UVD_UDEC_ADDR_CONFIG__SE_ENABLE_MASK                                                                  0x80000000L
//UVD_UDEC_DB_ADDR_CONFIG
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_PIPES__SHIFT                                                             0x0
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__PIPE_INTERLEAVE_SIZE__SHIFT                                                  0x3
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__MAX_COMPRESSED_FRAGS__SHIFT                                                  0x6
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__BANK_INTERLEAVE_SIZE__SHIFT                                                  0x8
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_BANKS__SHIFT                                                             0xc
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__SHADER_ENGINE_TILE_SIZE__SHIFT                                               0x10
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_SHADER_ENGINES__SHIFT                                                    0x13
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_GPUS__SHIFT                                                              0x15
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__MULTI_GPU_TILE_SIZE__SHIFT                                                   0x18
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_RB_PER_SE__SHIFT                                                         0x1a
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__ROW_SIZE__SHIFT                                                              0x1c
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_LOWER_PIPES__SHIFT                                                       0x1e
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__SE_ENABLE__SHIFT                                                             0x1f
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_PIPES_MASK                                                               0x00000007L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__PIPE_INTERLEAVE_SIZE_MASK                                                    0x00000038L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__MAX_COMPRESSED_FRAGS_MASK                                                    0x000000C0L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__BANK_INTERLEAVE_SIZE_MASK                                                    0x00000700L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_BANKS_MASK                                                               0x00007000L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__SHADER_ENGINE_TILE_SIZE_MASK                                                 0x00070000L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_SHADER_ENGINES_MASK                                                      0x00180000L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_GPUS_MASK                                                                0x00E00000L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__MULTI_GPU_TILE_SIZE_MASK                                                     0x03000000L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_RB_PER_SE_MASK                                                           0x0C000000L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__ROW_SIZE_MASK                                                                0x30000000L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__NUM_LOWER_PIPES_MASK                                                         0x40000000L
#घोषणा UVD_UDEC_DB_ADDR_CONFIG__SE_ENABLE_MASK                                                               0x80000000L
//UVD_UDEC_DBW_ADDR_CONFIG
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_PIPES__SHIFT                                                            0x0
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__PIPE_INTERLEAVE_SIZE__SHIFT                                                 0x3
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__MAX_COMPRESSED_FRAGS__SHIFT                                                 0x6
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__BANK_INTERLEAVE_SIZE__SHIFT                                                 0x8
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_BANKS__SHIFT                                                            0xc
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__SHADER_ENGINE_TILE_SIZE__SHIFT                                              0x10
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_SHADER_ENGINES__SHIFT                                                   0x13
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_GPUS__SHIFT                                                             0x15
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__MULTI_GPU_TILE_SIZE__SHIFT                                                  0x18
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_RB_PER_SE__SHIFT                                                        0x1a
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__ROW_SIZE__SHIFT                                                             0x1c
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_LOWER_PIPES__SHIFT                                                      0x1e
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__SE_ENABLE__SHIFT                                                            0x1f
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_PIPES_MASK                                                              0x00000007L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__PIPE_INTERLEAVE_SIZE_MASK                                                   0x00000038L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__MAX_COMPRESSED_FRAGS_MASK                                                   0x000000C0L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__BANK_INTERLEAVE_SIZE_MASK                                                   0x00000700L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_BANKS_MASK                                                              0x00007000L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__SHADER_ENGINE_TILE_SIZE_MASK                                                0x00070000L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_SHADER_ENGINES_MASK                                                     0x00180000L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_GPUS_MASK                                                               0x00E00000L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__MULTI_GPU_TILE_SIZE_MASK                                                    0x03000000L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_RB_PER_SE_MASK                                                          0x0C000000L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__ROW_SIZE_MASK                                                               0x30000000L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__NUM_LOWER_PIPES_MASK                                                        0x40000000L
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG__SE_ENABLE_MASK                                                              0x80000000L
//UVD_SUVD_CGC_GATE
#घोषणा UVD_SUVD_CGC_GATE__SRE__SHIFT                                                                         0x0
#घोषणा UVD_SUVD_CGC_GATE__SIT__SHIFT                                                                         0x1
#घोषणा UVD_SUVD_CGC_GATE__SMP__SHIFT                                                                         0x2
#घोषणा UVD_SUVD_CGC_GATE__SCM__SHIFT                                                                         0x3
#घोषणा UVD_SUVD_CGC_GATE__SDB__SHIFT                                                                         0x4
#घोषणा UVD_SUVD_CGC_GATE__SRE_H264__SHIFT                                                                    0x5
#घोषणा UVD_SUVD_CGC_GATE__SRE_HEVC__SHIFT                                                                    0x6
#घोषणा UVD_SUVD_CGC_GATE__SIT_H264__SHIFT                                                                    0x7
#घोषणा UVD_SUVD_CGC_GATE__SIT_HEVC__SHIFT                                                                    0x8
#घोषणा UVD_SUVD_CGC_GATE__SCM_H264__SHIFT                                                                    0x9
#घोषणा UVD_SUVD_CGC_GATE__SCM_HEVC__SHIFT                                                                    0xa
#घोषणा UVD_SUVD_CGC_GATE__SDB_H264__SHIFT                                                                    0xb
#घोषणा UVD_SUVD_CGC_GATE__SDB_HEVC__SHIFT                                                                    0xc
#घोषणा UVD_SUVD_CGC_GATE__SCLR__SHIFT                                                                        0xd
#घोषणा UVD_SUVD_CGC_GATE__UVD_SC__SHIFT                                                                      0xe
#घोषणा UVD_SUVD_CGC_GATE__ENT__SHIFT                                                                         0xf
#घोषणा UVD_SUVD_CGC_GATE__IME__SHIFT                                                                         0x10
#घोषणा UVD_SUVD_CGC_GATE__SIT_HEVC_DEC__SHIFT                                                                0x11
#घोषणा UVD_SUVD_CGC_GATE__SIT_HEVC_ENC__SHIFT                                                                0x12
#घोषणा UVD_SUVD_CGC_GATE__SRE_MASK                                                                           0x00000001L
#घोषणा UVD_SUVD_CGC_GATE__SIT_MASK                                                                           0x00000002L
#घोषणा UVD_SUVD_CGC_GATE__SMP_MASK                                                                           0x00000004L
#घोषणा UVD_SUVD_CGC_GATE__SCM_MASK                                                                           0x00000008L
#घोषणा UVD_SUVD_CGC_GATE__SDB_MASK                                                                           0x00000010L
#घोषणा UVD_SUVD_CGC_GATE__SRE_H264_MASK                                                                      0x00000020L
#घोषणा UVD_SUVD_CGC_GATE__SRE_HEVC_MASK                                                                      0x00000040L
#घोषणा UVD_SUVD_CGC_GATE__SIT_H264_MASK                                                                      0x00000080L
#घोषणा UVD_SUVD_CGC_GATE__SIT_HEVC_MASK                                                                      0x00000100L
#घोषणा UVD_SUVD_CGC_GATE__SCM_H264_MASK                                                                      0x00000200L
#घोषणा UVD_SUVD_CGC_GATE__SCM_HEVC_MASK                                                                      0x00000400L
#घोषणा UVD_SUVD_CGC_GATE__SDB_H264_MASK                                                                      0x00000800L
#घोषणा UVD_SUVD_CGC_GATE__SDB_HEVC_MASK                                                                      0x00001000L
#घोषणा UVD_SUVD_CGC_GATE__SCLR_MASK                                                                          0x00002000L
#घोषणा UVD_SUVD_CGC_GATE__UVD_SC_MASK                                                                        0x00004000L
#घोषणा UVD_SUVD_CGC_GATE__ENT_MASK                                                                           0x00008000L
#घोषणा UVD_SUVD_CGC_GATE__IME_MASK                                                                           0x00010000L
#घोषणा UVD_SUVD_CGC_GATE__SIT_HEVC_DEC_MASK                                                                  0x00020000L
#घोषणा UVD_SUVD_CGC_GATE__SIT_HEVC_ENC_MASK                                                                  0x00040000L
//UVD_SUVD_CGC_CTRL
#घोषणा UVD_SUVD_CGC_CTRL__SRE_MODE__SHIFT                                                                    0x0
#घोषणा UVD_SUVD_CGC_CTRL__SIT_MODE__SHIFT                                                                    0x1
#घोषणा UVD_SUVD_CGC_CTRL__SMP_MODE__SHIFT                                                                    0x2
#घोषणा UVD_SUVD_CGC_CTRL__SCM_MODE__SHIFT                                                                    0x3
#घोषणा UVD_SUVD_CGC_CTRL__SDB_MODE__SHIFT                                                                    0x4
#घोषणा UVD_SUVD_CGC_CTRL__SCLR_MODE__SHIFT                                                                   0x5
#घोषणा UVD_SUVD_CGC_CTRL__UVD_SC_MODE__SHIFT                                                                 0x6
#घोषणा UVD_SUVD_CGC_CTRL__ENT_MODE__SHIFT                                                                    0x7
#घोषणा UVD_SUVD_CGC_CTRL__IME_MODE__SHIFT                                                                    0x8
#घोषणा UVD_SUVD_CGC_CTRL__SRE_MODE_MASK                                                                      0x00000001L
#घोषणा UVD_SUVD_CGC_CTRL__SIT_MODE_MASK                                                                      0x00000002L
#घोषणा UVD_SUVD_CGC_CTRL__SMP_MODE_MASK                                                                      0x00000004L
#घोषणा UVD_SUVD_CGC_CTRL__SCM_MODE_MASK                                                                      0x00000008L
#घोषणा UVD_SUVD_CGC_CTRL__SDB_MODE_MASK                                                                      0x00000010L
#घोषणा UVD_SUVD_CGC_CTRL__SCLR_MODE_MASK                                                                     0x00000020L
#घोषणा UVD_SUVD_CGC_CTRL__UVD_SC_MODE_MASK                                                                   0x00000040L
#घोषणा UVD_SUVD_CGC_CTRL__ENT_MODE_MASK                                                                      0x00000080L
#घोषणा UVD_SUVD_CGC_CTRL__IME_MODE_MASK                                                                      0x00000100L
//UVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW
#घोषणा UVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW__BITS_31_0__SHIFT                                                   0x0
#घोषणा UVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW__BITS_31_0_MASK                                                     0xFFFFFFFFL
//UVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH
#घोषणा UVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH__BITS_63_32__SHIFT                                                 0x0
#घोषणा UVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH__BITS_63_32_MASK                                                   0xFFFFFFFFL
//UVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW
#घोषणा UVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW__BITS_31_0__SHIFT                                                   0x0
#घोषणा UVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW__BITS_31_0_MASK                                                     0xFFFFFFFFL
//UVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH
#घोषणा UVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH__BITS_63_32__SHIFT                                                 0x0
#घोषणा UVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH__BITS_63_32_MASK                                                   0xFFFFFFFFL
//UVD_POWER_STATUS_U
#घोषणा UVD_POWER_STATUS_U__UVD_POWER_STATUS__SHIFT                                                           0x0
#घोषणा UVD_POWER_STATUS_U__UVD_POWER_STATUS_MASK                                                             0x00000003L
//UVD_NO_OP
#घोषणा UVD_NO_OP__NO_OP__SHIFT                                                                               0x0
#घोषणा UVD_NO_OP__NO_OP_MASK                                                                                 0xFFFFFFFFL
//UVD_GP_SCRATCH8
#घोषणा UVD_GP_SCRATCH8__DATA__SHIFT                                                                          0x0
#घोषणा UVD_GP_SCRATCH8__DATA_MASK                                                                            0xFFFFFFFFL
//UVD_RB_BASE_LO2
#घोषणा UVD_RB_BASE_LO2__RB_BASE_LO__SHIFT                                                                    0x6
#घोषणा UVD_RB_BASE_LO2__RB_BASE_LO_MASK                                                                      0xFFFFFFC0L
//UVD_RB_BASE_HI2
#घोषणा UVD_RB_BASE_HI2__RB_BASE_HI__SHIFT                                                                    0x0
#घोषणा UVD_RB_BASE_HI2__RB_BASE_HI_MASK                                                                      0xFFFFFFFFL
//UVD_RB_SIZE2
#घोषणा UVD_RB_SIZE2__RB_SIZE__SHIFT                                                                          0x4
#घोषणा UVD_RB_SIZE2__RB_SIZE_MASK                                                                            0x007FFFF0L
//UVD_RB_RPTR2
#घोषणा UVD_RB_RPTR2__RB_RPTR__SHIFT                                                                          0x4
#घोषणा UVD_RB_RPTR2__RB_RPTR_MASK                                                                            0x007FFFF0L
//UVD_RB_WPTR2
#घोषणा UVD_RB_WPTR2__RB_WPTR__SHIFT                                                                          0x4
#घोषणा UVD_RB_WPTR2__RB_WPTR_MASK                                                                            0x007FFFF0L
//UVD_RB_BASE_LO
#घोषणा UVD_RB_BASE_LO__RB_BASE_LO__SHIFT                                                                     0x6
#घोषणा UVD_RB_BASE_LO__RB_BASE_LO_MASK                                                                       0xFFFFFFC0L
//UVD_RB_BASE_HI
#घोषणा UVD_RB_BASE_HI__RB_BASE_HI__SHIFT                                                                     0x0
#घोषणा UVD_RB_BASE_HI__RB_BASE_HI_MASK                                                                       0xFFFFFFFFL
//UVD_RB_SIZE
#घोषणा UVD_RB_SIZE__RB_SIZE__SHIFT                                                                           0x4
#घोषणा UVD_RB_SIZE__RB_SIZE_MASK                                                                             0x007FFFF0L
//UVD_RB_RPTR
#घोषणा UVD_RB_RPTR__RB_RPTR__SHIFT                                                                           0x4
#घोषणा UVD_RB_RPTR__RB_RPTR_MASK                                                                             0x007FFFF0L
//UVD_RB_WPTR
#घोषणा UVD_RB_WPTR__RB_WPTR__SHIFT                                                                           0x4
#घोषणा UVD_RB_WPTR__RB_WPTR_MASK                                                                             0x007FFFF0L
//UVD_JRBC_RB_RPTR
#घोषणा UVD_JRBC_RB_RPTR__RB_RPTR__SHIFT                                                                      0x4
#घोषणा UVD_JRBC_RB_RPTR__RB_RPTR_MASK                                                                        0x007FFFF0L
//UVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH
#घोषणा UVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH__BITS_63_32__SHIFT                                                  0x0
#घोषणा UVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH__BITS_63_32_MASK                                                    0xFFFFFFFFL
//UVD_LMI_VCPU_CACHE_64BIT_BAR_LOW
#घोषणा UVD_LMI_VCPU_CACHE_64BIT_BAR_LOW__BITS_31_0__SHIFT                                                    0x0
#घोषणा UVD_LMI_VCPU_CACHE_64BIT_BAR_LOW__BITS_31_0_MASK                                                      0xFFFFFFFFL
//UVD_LMI_RBC_IB_64BIT_BAR_HIGH
#घोषणा UVD_LMI_RBC_IB_64BIT_BAR_HIGH__BITS_63_32__SHIFT                                                      0x0
#घोषणा UVD_LMI_RBC_IB_64BIT_BAR_HIGH__BITS_63_32_MASK                                                        0xFFFFFFFFL
//UVD_LMI_RBC_IB_64BIT_BAR_LOW
#घोषणा UVD_LMI_RBC_IB_64BIT_BAR_LOW__BITS_31_0__SHIFT                                                        0x0
#घोषणा UVD_LMI_RBC_IB_64BIT_BAR_LOW__BITS_31_0_MASK                                                          0xFFFFFFFFL
//UVD_LMI_RBC_RB_64BIT_BAR_HIGH
#घोषणा UVD_LMI_RBC_RB_64BIT_BAR_HIGH__BITS_63_32__SHIFT                                                      0x0
#घोषणा UVD_LMI_RBC_RB_64BIT_BAR_HIGH__BITS_63_32_MASK                                                        0xFFFFFFFFL
//UVD_LMI_RBC_RB_64BIT_BAR_LOW
#घोषणा UVD_LMI_RBC_RB_64BIT_BAR_LOW__BITS_31_0__SHIFT                                                        0x0
#घोषणा UVD_LMI_RBC_RB_64BIT_BAR_LOW__BITS_31_0_MASK                                                          0xFFFFFFFFL


// addressBlock: uvd0_uvddec
//UVD_SEMA_CNTL
#घोषणा UVD_SEMA_CNTL__SEMAPHORE_EN__SHIFT                                                                    0x0
#घोषणा UVD_SEMA_CNTL__ADVANCED_MODE_DIS__SHIFT                                                               0x1
#घोषणा UVD_SEMA_CNTL__SEMAPHORE_EN_MASK                                                                      0x00000001L
#घोषणा UVD_SEMA_CNTL__ADVANCED_MODE_DIS_MASK                                                                 0x00000002L
//UVD_LMI_JRBC_RB_64BIT_BAR_LOW
#घोषणा UVD_LMI_JRBC_RB_64BIT_BAR_LOW__BITS_31_0__SHIFT                                                       0x0
#घोषणा UVD_LMI_JRBC_RB_64BIT_BAR_LOW__BITS_31_0_MASK                                                         0xFFFFFFFFL
//UVD_JRBC_RB_WPTR
#घोषणा UVD_JRBC_RB_WPTR__RB_WPTR__SHIFT                                                                      0x4
#घोषणा UVD_JRBC_RB_WPTR__RB_WPTR_MASK                                                                        0x007FFFF0L
//UVD_RB_RPTR3
#घोषणा UVD_RB_RPTR3__RB_RPTR__SHIFT                                                                          0x4
#घोषणा UVD_RB_RPTR3__RB_RPTR_MASK                                                                            0x007FFFF0L
//UVD_RB_WPTR3
#घोषणा UVD_RB_WPTR3__RB_WPTR__SHIFT                                                                          0x4
#घोषणा UVD_RB_WPTR3__RB_WPTR_MASK                                                                            0x007FFFF0L
//UVD_RB_BASE_LO3
#घोषणा UVD_RB_BASE_LO3__RB_BASE_LO__SHIFT                                                                    0x6
#घोषणा UVD_RB_BASE_LO3__RB_BASE_LO_MASK                                                                      0xFFFFFFC0L
//UVD_RB_BASE_HI3
#घोषणा UVD_RB_BASE_HI3__RB_BASE_HI__SHIFT                                                                    0x0
#घोषणा UVD_RB_BASE_HI3__RB_BASE_HI_MASK                                                                      0xFFFFFFFFL
//UVD_RB_SIZE3
#घोषणा UVD_RB_SIZE3__RB_SIZE__SHIFT                                                                          0x4
#घोषणा UVD_RB_SIZE3__RB_SIZE_MASK                                                                            0x007FFFF0L
//JPEG_CGC_GATE
#घोषणा JPEG_CGC_GATE__JPEG__SHIFT                                                                            0x14
#घोषणा JPEG_CGC_GATE__JPEG2__SHIFT                                                                           0x15
#घोषणा JPEG_CGC_GATE__JPEG_MASK                                                                              0x00100000L
#घोषणा JPEG_CGC_GATE__JPEG2_MASK                                                                             0x00200000L
//UVD_CTX_INDEX
#घोषणा UVD_CTX_INDEX__INDEX__SHIFT                                                                           0x0
#घोषणा UVD_CTX_INDEX__INDEX_MASK                                                                             0x000001FFL
//UVD_CTX_DATA
#घोषणा UVD_CTX_DATA__DATA__SHIFT                                                                             0x0
#घोषणा UVD_CTX_DATA__DATA_MASK                                                                               0xFFFFFFFFL
//UVD_CGC_GATE
#घोषणा UVD_CGC_GATE__SYS__SHIFT                                                                              0x0
#घोषणा UVD_CGC_GATE__UDEC__SHIFT                                                                             0x1
#घोषणा UVD_CGC_GATE__MPEG2__SHIFT                                                                            0x2
#घोषणा UVD_CGC_GATE__REGS__SHIFT                                                                             0x3
#घोषणा UVD_CGC_GATE__RBC__SHIFT                                                                              0x4
#घोषणा UVD_CGC_GATE__LMI_MC__SHIFT                                                                           0x5
#घोषणा UVD_CGC_GATE__LMI_UMC__SHIFT                                                                          0x6
#घोषणा UVD_CGC_GATE__IDCT__SHIFT                                                                             0x7
#घोषणा UVD_CGC_GATE__MPRD__SHIFT                                                                             0x8
#घोषणा UVD_CGC_GATE__MPC__SHIFT                                                                              0x9
#घोषणा UVD_CGC_GATE__LBSI__SHIFT                                                                             0xa
#घोषणा UVD_CGC_GATE__LRBBM__SHIFT                                                                            0xb
#घोषणा UVD_CGC_GATE__UDEC_RE__SHIFT                                                                          0xc
#घोषणा UVD_CGC_GATE__UDEC_CM__SHIFT                                                                          0xd
#घोषणा UVD_CGC_GATE__UDEC_IT__SHIFT                                                                          0xe
#घोषणा UVD_CGC_GATE__UDEC_DB__SHIFT                                                                          0xf
#घोषणा UVD_CGC_GATE__UDEC_MP__SHIFT                                                                          0x10
#घोषणा UVD_CGC_GATE__WCB__SHIFT                                                                              0x11
#घोषणा UVD_CGC_GATE__VCPU__SHIFT                                                                             0x12
#घोषणा UVD_CGC_GATE__SCPU__SHIFT                                                                             0x13
#घोषणा UVD_CGC_GATE__SYS_MASK                                                                                0x00000001L
#घोषणा UVD_CGC_GATE__UDEC_MASK                                                                               0x00000002L
#घोषणा UVD_CGC_GATE__MPEG2_MASK                                                                              0x00000004L
#घोषणा UVD_CGC_GATE__REGS_MASK                                                                               0x00000008L
#घोषणा UVD_CGC_GATE__RBC_MASK                                                                                0x00000010L
#घोषणा UVD_CGC_GATE__LMI_MC_MASK                                                                             0x00000020L
#घोषणा UVD_CGC_GATE__LMI_UMC_MASK                                                                            0x00000040L
#घोषणा UVD_CGC_GATE__IDCT_MASK                                                                               0x00000080L
#घोषणा UVD_CGC_GATE__MPRD_MASK                                                                               0x00000100L
#घोषणा UVD_CGC_GATE__MPC_MASK                                                                                0x00000200L
#घोषणा UVD_CGC_GATE__LBSI_MASK                                                                               0x00000400L
#घोषणा UVD_CGC_GATE__LRBBM_MASK                                                                              0x00000800L
#घोषणा UVD_CGC_GATE__UDEC_RE_MASK                                                                            0x00001000L
#घोषणा UVD_CGC_GATE__UDEC_CM_MASK                                                                            0x00002000L
#घोषणा UVD_CGC_GATE__UDEC_IT_MASK                                                                            0x00004000L
#घोषणा UVD_CGC_GATE__UDEC_DB_MASK                                                                            0x00008000L
#घोषणा UVD_CGC_GATE__UDEC_MP_MASK                                                                            0x00010000L
#घोषणा UVD_CGC_GATE__WCB_MASK                                                                                0x00020000L
#घोषणा UVD_CGC_GATE__VCPU_MASK                                                                               0x00040000L
#घोषणा UVD_CGC_GATE__SCPU_MASK                                                                               0x00080000L
//UVD_CGC_CTRL
#घोषणा UVD_CGC_CTRL__DYN_CLOCK_MODE__SHIFT                                                                   0x0
#घोषणा UVD_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT                                                               0x2
#घोषणा UVD_CGC_CTRL__CLK_OFF_DELAY__SHIFT                                                                    0x6
#घोषणा UVD_CGC_CTRL__UDEC_RE_MODE__SHIFT                                                                     0xb
#घोषणा UVD_CGC_CTRL__UDEC_CM_MODE__SHIFT                                                                     0xc
#घोषणा UVD_CGC_CTRL__UDEC_IT_MODE__SHIFT                                                                     0xd
#घोषणा UVD_CGC_CTRL__UDEC_DB_MODE__SHIFT                                                                     0xe
#घोषणा UVD_CGC_CTRL__UDEC_MP_MODE__SHIFT                                                                     0xf
#घोषणा UVD_CGC_CTRL__SYS_MODE__SHIFT                                                                         0x10
#घोषणा UVD_CGC_CTRL__UDEC_MODE__SHIFT                                                                        0x11
#घोषणा UVD_CGC_CTRL__MPEG2_MODE__SHIFT                                                                       0x12
#घोषणा UVD_CGC_CTRL__REGS_MODE__SHIFT                                                                        0x13
#घोषणा UVD_CGC_CTRL__RBC_MODE__SHIFT                                                                         0x14
#घोषणा UVD_CGC_CTRL__LMI_MC_MODE__SHIFT                                                                      0x15
#घोषणा UVD_CGC_CTRL__LMI_UMC_MODE__SHIFT                                                                     0x16
#घोषणा UVD_CGC_CTRL__IDCT_MODE__SHIFT                                                                        0x17
#घोषणा UVD_CGC_CTRL__MPRD_MODE__SHIFT                                                                        0x18
#घोषणा UVD_CGC_CTRL__MPC_MODE__SHIFT                                                                         0x19
#घोषणा UVD_CGC_CTRL__LBSI_MODE__SHIFT                                                                        0x1a
#घोषणा UVD_CGC_CTRL__LRBBM_MODE__SHIFT                                                                       0x1b
#घोषणा UVD_CGC_CTRL__WCB_MODE__SHIFT                                                                         0x1c
#घोषणा UVD_CGC_CTRL__VCPU_MODE__SHIFT                                                                        0x1d
#घोषणा UVD_CGC_CTRL__SCPU_MODE__SHIFT                                                                        0x1e
#घोषणा UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK                                                                     0x00000001L
#घोषणा UVD_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK                                                                 0x0000003CL
#घोषणा UVD_CGC_CTRL__CLK_OFF_DELAY_MASK                                                                      0x000007C0L
#घोषणा UVD_CGC_CTRL__UDEC_RE_MODE_MASK                                                                       0x00000800L
#घोषणा UVD_CGC_CTRL__UDEC_CM_MODE_MASK                                                                       0x00001000L
#घोषणा UVD_CGC_CTRL__UDEC_IT_MODE_MASK                                                                       0x00002000L
#घोषणा UVD_CGC_CTRL__UDEC_DB_MODE_MASK                                                                       0x00004000L
#घोषणा UVD_CGC_CTRL__UDEC_MP_MODE_MASK                                                                       0x00008000L
#घोषणा UVD_CGC_CTRL__SYS_MODE_MASK                                                                           0x00010000L
#घोषणा UVD_CGC_CTRL__UDEC_MODE_MASK                                                                          0x00020000L
#घोषणा UVD_CGC_CTRL__MPEG2_MODE_MASK                                                                         0x00040000L
#घोषणा UVD_CGC_CTRL__REGS_MODE_MASK                                                                          0x00080000L
#घोषणा UVD_CGC_CTRL__RBC_MODE_MASK                                                                           0x00100000L
#घोषणा UVD_CGC_CTRL__LMI_MC_MODE_MASK                                                                        0x00200000L
#घोषणा UVD_CGC_CTRL__LMI_UMC_MODE_MASK                                                                       0x00400000L
#घोषणा UVD_CGC_CTRL__IDCT_MODE_MASK                                                                          0x00800000L
#घोषणा UVD_CGC_CTRL__MPRD_MODE_MASK                                                                          0x01000000L
#घोषणा UVD_CGC_CTRL__MPC_MODE_MASK                                                                           0x02000000L
#घोषणा UVD_CGC_CTRL__LBSI_MODE_MASK                                                                          0x04000000L
#घोषणा UVD_CGC_CTRL__LRBBM_MODE_MASK                                                                         0x08000000L
#घोषणा UVD_CGC_CTRL__WCB_MODE_MASK                                                                           0x10000000L
#घोषणा UVD_CGC_CTRL__VCPU_MODE_MASK                                                                          0x20000000L
#घोषणा UVD_CGC_CTRL__SCPU_MODE_MASK                                                                          0x40000000L
//UVD_GP_SCRATCH4
#घोषणा UVD_GP_SCRATCH4__DATA__SHIFT                                                                          0x0
#घोषणा UVD_GP_SCRATCH4__DATA_MASK                                                                            0xFFFFFFFFL
//UVD_LMI_CTRL2
#घोषणा UVD_LMI_CTRL2__SPH_DIS__SHIFT                                                                         0x0
#घोषणा UVD_LMI_CTRL2__STALL_ARB__SHIFT                                                                       0x1
#घोषणा UVD_LMI_CTRL2__ASSERT_UMC_URGENT__SHIFT                                                               0x2
#घोषणा UVD_LMI_CTRL2__MASK_UMC_URGENT__SHIFT                                                                 0x3
#घोषणा UVD_LMI_CTRL2__DRCITF_BUBBLE_FIX_DIS__SHIFT                                                           0x7
#घोषणा UVD_LMI_CTRL2__STALL_ARB_UMC__SHIFT                                                                   0x8
#घोषणा UVD_LMI_CTRL2__MC_READ_ID_SEL__SHIFT                                                                  0x9
#घोषणा UVD_LMI_CTRL2__MC_WRITE_ID_SEL__SHIFT                                                                 0xb
#घोषणा UVD_LMI_CTRL2__SPH_DIS_MASK                                                                           0x00000001L
#घोषणा UVD_LMI_CTRL2__STALL_ARB_MASK                                                                         0x00000002L
#घोषणा UVD_LMI_CTRL2__ASSERT_UMC_URGENT_MASK                                                                 0x00000004L
#घोषणा UVD_LMI_CTRL2__MASK_UMC_URGENT_MASK                                                                   0x00000008L
#घोषणा UVD_LMI_CTRL2__DRCITF_BUBBLE_FIX_DIS_MASK                                                             0x00000080L
#घोषणा UVD_LMI_CTRL2__STALL_ARB_UMC_MASK                                                                     0x00000100L
#घोषणा UVD_LMI_CTRL2__MC_READ_ID_SEL_MASK                                                                    0x00000600L
#घोषणा UVD_LMI_CTRL2__MC_WRITE_ID_SEL_MASK                                                                   0x00001800L
//UVD_MASTINT_EN
#घोषणा UVD_MASTINT_EN__OVERRUN_RST__SHIFT                                                                    0x0
#घोषणा UVD_MASTINT_EN__VCPU_EN__SHIFT                                                                        0x1
#घोषणा UVD_MASTINT_EN__SYS_EN__SHIFT                                                                         0x2
#घोषणा UVD_MASTINT_EN__INT_OVERRUN__SHIFT                                                                    0x4
#घोषणा UVD_MASTINT_EN__OVERRUN_RST_MASK                                                                      0x00000001L
#घोषणा UVD_MASTINT_EN__VCPU_EN_MASK                                                                          0x00000002L
#घोषणा UVD_MASTINT_EN__SYS_EN_MASK                                                                           0x00000004L
#घोषणा UVD_MASTINT_EN__INT_OVERRUN_MASK                                                                      0x007FFFF0L
//JPEG_CGC_CTRL
#घोषणा JPEG_CGC_CTRL__DYN_CLOCK_MODE__SHIFT                                                                  0x0
#घोषणा JPEG_CGC_CTRL__JPEG2_MODE__SHIFT                                                                      0x1
#घोषणा JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER__SHIFT                                                              0x2
#घोषणा JPEG_CGC_CTRL__CLK_OFF_DELAY__SHIFT                                                                   0x6
#घोषणा JPEG_CGC_CTRL__JPEG_MODE__SHIFT                                                                       0x1f
#घोषणा JPEG_CGC_CTRL__DYN_CLOCK_MODE_MASK                                                                    0x00000001L
#घोषणा JPEG_CGC_CTRL__JPEG2_MODE_MASK                                                                        0x00000002L
#घोषणा JPEG_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK                                                                0x0000003CL
#घोषणा JPEG_CGC_CTRL__CLK_OFF_DELAY_MASK                                                                     0x000007C0L
#घोषणा JPEG_CGC_CTRL__JPEG_MODE_MASK                                                                         0x80000000L
//UVD_LMI_CTRL
#घोषणा UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT                                                                0x0
#घोषणा UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN__SHIFT                                                             0x8
#घोषणा UVD_LMI_CTRL__REQ_MODE__SHIFT                                                                         0x9
#घोषणा UVD_LMI_CTRL__ASSERT_MC_URGENT__SHIFT                                                                 0xb
#घोषणा UVD_LMI_CTRL__MASK_MC_URGENT__SHIFT                                                                   0xc
#घोषणा UVD_LMI_CTRL__DATA_COHERENCY_EN__SHIFT                                                                0xd
#घोषणा UVD_LMI_CTRL__CRC_RESET__SHIFT                                                                        0xe
#घोषणा UVD_LMI_CTRL__CRC_SEL__SHIFT                                                                          0xf
#घोषणा UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN__SHIFT                                                           0x15
#घोषणा UVD_LMI_CTRL__CM_DATA_COHERENCY_EN__SHIFT                                                             0x16
#घोषणा UVD_LMI_CTRL__DB_DB_DATA_COHERENCY_EN__SHIFT                                                          0x17
#घोषणा UVD_LMI_CTRL__DB_IT_DATA_COHERENCY_EN__SHIFT                                                          0x18
#घोषणा UVD_LMI_CTRL__IT_IT_DATA_COHERENCY_EN__SHIFT                                                          0x19
#घोषणा UVD_LMI_CTRL__RFU__SHIFT                                                                              0x1b
#घोषणा UVD_LMI_CTRL__WRITE_CLEAN_TIMER_MASK                                                                  0x000000FFL
#घोषणा UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK                                                               0x00000100L
#घोषणा UVD_LMI_CTRL__REQ_MODE_MASK                                                                           0x00000200L
#घोषणा UVD_LMI_CTRL__ASSERT_MC_URGENT_MASK                                                                   0x00000800L
#घोषणा UVD_LMI_CTRL__MASK_MC_URGENT_MASK                                                                     0x00001000L
#घोषणा UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK                                                                  0x00002000L
#घोषणा UVD_LMI_CTRL__CRC_RESET_MASK                                                                          0x00004000L
#घोषणा UVD_LMI_CTRL__CRC_SEL_MASK                                                                            0x000F8000L
#घोषणा UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK                                                             0x00200000L
#घोषणा UVD_LMI_CTRL__CM_DATA_COHERENCY_EN_MASK                                                               0x00400000L
#घोषणा UVD_LMI_CTRL__DB_DB_DATA_COHERENCY_EN_MASK                                                            0x00800000L
#घोषणा UVD_LMI_CTRL__DB_IT_DATA_COHERENCY_EN_MASK                                                            0x01000000L
#घोषणा UVD_LMI_CTRL__IT_IT_DATA_COHERENCY_EN_MASK                                                            0x02000000L
#घोषणा UVD_LMI_CTRL__RFU_MASK                                                                                0xF8000000L
//UVD_LMI_SWAP_CNTL
#घोषणा UVD_LMI_SWAP_CNTL__RB_MC_SWAP__SHIFT                                                                  0x0
#घोषणा UVD_LMI_SWAP_CNTL__IB_MC_SWAP__SHIFT                                                                  0x2
#घोषणा UVD_LMI_SWAP_CNTL__RB_RPTR_MC_SWAP__SHIFT                                                             0x4
#घोषणा UVD_LMI_SWAP_CNTL__VCPU_R_MC_SWAP__SHIFT                                                              0x6
#घोषणा UVD_LMI_SWAP_CNTL__VCPU_W_MC_SWAP__SHIFT                                                              0x8
#घोषणा UVD_LMI_SWAP_CNTL__CM_MC_SWAP__SHIFT                                                                  0xa
#घोषणा UVD_LMI_SWAP_CNTL__IT_MC_SWAP__SHIFT                                                                  0xc
#घोषणा UVD_LMI_SWAP_CNTL__DB_R_MC_SWAP__SHIFT                                                                0xe
#घोषणा UVD_LMI_SWAP_CNTL__DB_W_MC_SWAP__SHIFT                                                                0x10
#घोषणा UVD_LMI_SWAP_CNTL__CSM_MC_SWAP__SHIFT                                                                 0x12
#घोषणा UVD_LMI_SWAP_CNTL__MP_REF16_MC_SWAP__SHIFT                                                            0x16
#घोषणा UVD_LMI_SWAP_CNTL__DBW_MC_SWAP__SHIFT                                                                 0x18
#घोषणा UVD_LMI_SWAP_CNTL__RB_WR_MC_SWAP__SHIFT                                                               0x1a
#घोषणा UVD_LMI_SWAP_CNTL__RE_MC_SWAP__SHIFT                                                                  0x1c
#घोषणा UVD_LMI_SWAP_CNTL__MP_MC_SWAP__SHIFT                                                                  0x1e
#घोषणा UVD_LMI_SWAP_CNTL__RB_MC_SWAP_MASK                                                                    0x00000003L
#घोषणा UVD_LMI_SWAP_CNTL__IB_MC_SWAP_MASK                                                                    0x0000000CL
#घोषणा UVD_LMI_SWAP_CNTL__RB_RPTR_MC_SWAP_MASK                                                               0x00000030L
#घोषणा UVD_LMI_SWAP_CNTL__VCPU_R_MC_SWAP_MASK                                                                0x000000C0L
#घोषणा UVD_LMI_SWAP_CNTL__VCPU_W_MC_SWAP_MASK                                                                0x00000300L
#घोषणा UVD_LMI_SWAP_CNTL__CM_MC_SWAP_MASK                                                                    0x00000C00L
#घोषणा UVD_LMI_SWAP_CNTL__IT_MC_SWAP_MASK                                                                    0x00003000L
#घोषणा UVD_LMI_SWAP_CNTL__DB_R_MC_SWAP_MASK                                                                  0x0000C000L
#घोषणा UVD_LMI_SWAP_CNTL__DB_W_MC_SWAP_MASK                                                                  0x00030000L
#घोषणा UVD_LMI_SWAP_CNTL__CSM_MC_SWAP_MASK                                                                   0x000C0000L
#घोषणा UVD_LMI_SWAP_CNTL__MP_REF16_MC_SWAP_MASK                                                              0x00C00000L
#घोषणा UVD_LMI_SWAP_CNTL__DBW_MC_SWAP_MASK                                                                   0x03000000L
#घोषणा UVD_LMI_SWAP_CNTL__RB_WR_MC_SWAP_MASK                                                                 0x0C000000L
#घोषणा UVD_LMI_SWAP_CNTL__RE_MC_SWAP_MASK                                                                    0x30000000L
#घोषणा UVD_LMI_SWAP_CNTL__MP_MC_SWAP_MASK                                                                    0xC0000000L
//UVD_MP_SWAP_CNTL
#घोषणा UVD_MP_SWAP_CNTL__MP_REF0_MC_SWAP__SHIFT                                                              0x0
#घोषणा UVD_MP_SWAP_CNTL__MP_REF1_MC_SWAP__SHIFT                                                              0x2
#घोषणा UVD_MP_SWAP_CNTL__MP_REF2_MC_SWAP__SHIFT                                                              0x4
#घोषणा UVD_MP_SWAP_CNTL__MP_REF3_MC_SWAP__SHIFT                                                              0x6
#घोषणा UVD_MP_SWAP_CNTL__MP_REF4_MC_SWAP__SHIFT                                                              0x8
#घोषणा UVD_MP_SWAP_CNTL__MP_REF5_MC_SWAP__SHIFT                                                              0xa
#घोषणा UVD_MP_SWAP_CNTL__MP_REF6_MC_SWAP__SHIFT                                                              0xc
#घोषणा UVD_MP_SWAP_CNTL__MP_REF7_MC_SWAP__SHIFT                                                              0xe
#घोषणा UVD_MP_SWAP_CNTL__MP_REF8_MC_SWAP__SHIFT                                                              0x10
#घोषणा UVD_MP_SWAP_CNTL__MP_REF9_MC_SWAP__SHIFT                                                              0x12
#घोषणा UVD_MP_SWAP_CNTL__MP_REF10_MC_SWAP__SHIFT                                                             0x14
#घोषणा UVD_MP_SWAP_CNTL__MP_REF11_MC_SWAP__SHIFT                                                             0x16
#घोषणा UVD_MP_SWAP_CNTL__MP_REF12_MC_SWAP__SHIFT                                                             0x18
#घोषणा UVD_MP_SWAP_CNTL__MP_REF13_MC_SWAP__SHIFT                                                             0x1a
#घोषणा UVD_MP_SWAP_CNTL__MP_REF14_MC_SWAP__SHIFT                                                             0x1c
#घोषणा UVD_MP_SWAP_CNTL__MP_REF15_MC_SWAP__SHIFT                                                             0x1e
#घोषणा UVD_MP_SWAP_CNTL__MP_REF0_MC_SWAP_MASK                                                                0x00000003L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF1_MC_SWAP_MASK                                                                0x0000000CL
#घोषणा UVD_MP_SWAP_CNTL__MP_REF2_MC_SWAP_MASK                                                                0x00000030L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF3_MC_SWAP_MASK                                                                0x000000C0L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF4_MC_SWAP_MASK                                                                0x00000300L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF5_MC_SWAP_MASK                                                                0x00000C00L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF6_MC_SWAP_MASK                                                                0x00003000L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF7_MC_SWAP_MASK                                                                0x0000C000L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF8_MC_SWAP_MASK                                                                0x00030000L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF9_MC_SWAP_MASK                                                                0x000C0000L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF10_MC_SWAP_MASK                                                               0x00300000L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF11_MC_SWAP_MASK                                                               0x00C00000L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF12_MC_SWAP_MASK                                                               0x03000000L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF13_MC_SWAP_MASK                                                               0x0C000000L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF14_MC_SWAP_MASK                                                               0x30000000L
#घोषणा UVD_MP_SWAP_CNTL__MP_REF15_MC_SWAP_MASK                                                               0xC0000000L
//UVD_MPC_SET_MUXA0
#घोषणा UVD_MPC_SET_MUXA0__VARA_0__SHIFT                                                                      0x0
#घोषणा UVD_MPC_SET_MUXA0__VARA_1__SHIFT                                                                      0x6
#घोषणा UVD_MPC_SET_MUXA0__VARA_2__SHIFT                                                                      0xc
#घोषणा UVD_MPC_SET_MUXA0__VARA_3__SHIFT                                                                      0x12
#घोषणा UVD_MPC_SET_MUXA0__VARA_4__SHIFT                                                                      0x18
#घोषणा UVD_MPC_SET_MUXA0__VARA_0_MASK                                                                        0x0000003FL
#घोषणा UVD_MPC_SET_MUXA0__VARA_1_MASK                                                                        0x00000FC0L
#घोषणा UVD_MPC_SET_MUXA0__VARA_2_MASK                                                                        0x0003F000L
#घोषणा UVD_MPC_SET_MUXA0__VARA_3_MASK                                                                        0x00FC0000L
#घोषणा UVD_MPC_SET_MUXA0__VARA_4_MASK                                                                        0x3F000000L
//UVD_MPC_SET_MUXA1
#घोषणा UVD_MPC_SET_MUXA1__VARA_5__SHIFT                                                                      0x0
#घोषणा UVD_MPC_SET_MUXA1__VARA_6__SHIFT                                                                      0x6
#घोषणा UVD_MPC_SET_MUXA1__VARA_7__SHIFT                                                                      0xc
#घोषणा UVD_MPC_SET_MUXA1__VARA_5_MASK                                                                        0x0000003FL
#घोषणा UVD_MPC_SET_MUXA1__VARA_6_MASK                                                                        0x00000FC0L
#घोषणा UVD_MPC_SET_MUXA1__VARA_7_MASK                                                                        0x0003F000L
//UVD_MPC_SET_MUXB0
#घोषणा UVD_MPC_SET_MUXB0__VARB_0__SHIFT                                                                      0x0
#घोषणा UVD_MPC_SET_MUXB0__VARB_1__SHIFT                                                                      0x6
#घोषणा UVD_MPC_SET_MUXB0__VARB_2__SHIFT                                                                      0xc
#घोषणा UVD_MPC_SET_MUXB0__VARB_3__SHIFT                                                                      0x12
#घोषणा UVD_MPC_SET_MUXB0__VARB_4__SHIFT                                                                      0x18
#घोषणा UVD_MPC_SET_MUXB0__VARB_0_MASK                                                                        0x0000003FL
#घोषणा UVD_MPC_SET_MUXB0__VARB_1_MASK                                                                        0x00000FC0L
#घोषणा UVD_MPC_SET_MUXB0__VARB_2_MASK                                                                        0x0003F000L
#घोषणा UVD_MPC_SET_MUXB0__VARB_3_MASK                                                                        0x00FC0000L
#घोषणा UVD_MPC_SET_MUXB0__VARB_4_MASK                                                                        0x3F000000L
//UVD_MPC_SET_MUXB1
#घोषणा UVD_MPC_SET_MUXB1__VARB_5__SHIFT                                                                      0x0
#घोषणा UVD_MPC_SET_MUXB1__VARB_6__SHIFT                                                                      0x6
#घोषणा UVD_MPC_SET_MUXB1__VARB_7__SHIFT                                                                      0xc
#घोषणा UVD_MPC_SET_MUXB1__VARB_5_MASK                                                                        0x0000003FL
#घोषणा UVD_MPC_SET_MUXB1__VARB_6_MASK                                                                        0x00000FC0L
#घोषणा UVD_MPC_SET_MUXB1__VARB_7_MASK                                                                        0x0003F000L
//UVD_MPC_SET_MUX
#घोषणा UVD_MPC_SET_MUX__SET_0__SHIFT                                                                         0x0
#घोषणा UVD_MPC_SET_MUX__SET_1__SHIFT                                                                         0x3
#घोषणा UVD_MPC_SET_MUX__SET_2__SHIFT                                                                         0x6
#घोषणा UVD_MPC_SET_MUX__SET_0_MASK                                                                           0x00000007L
#घोषणा UVD_MPC_SET_MUX__SET_1_MASK                                                                           0x00000038L
#घोषणा UVD_MPC_SET_MUX__SET_2_MASK                                                                           0x000001C0L
//UVD_MPC_SET_ALU
#घोषणा UVD_MPC_SET_ALU__FUNCT__SHIFT                                                                         0x0
#घोषणा UVD_MPC_SET_ALU__OPERAND__SHIFT                                                                       0x4
#घोषणा UVD_MPC_SET_ALU__FUNCT_MASK                                                                           0x00000007L
#घोषणा UVD_MPC_SET_ALU__OPERAND_MASK                                                                         0x00000FF0L
//UVD_VCPU_CACHE_OFFSET0
#घोषणा UVD_VCPU_CACHE_OFFSET0__CACHE_OFFSET0__SHIFT                                                          0x0
#घोषणा UVD_VCPU_CACHE_OFFSET0__CACHE_OFFSET0_MASK                                                            0x01FFFFFFL
//UVD_VCPU_CACHE_SIZE0
#घोषणा UVD_VCPU_CACHE_SIZE0__CACHE_SIZE0__SHIFT                                                              0x0
#घोषणा UVD_VCPU_CACHE_SIZE0__CACHE_SIZE0_MASK                                                                0x001FFFFFL
//UVD_VCPU_CACHE_OFFSET1
#घोषणा UVD_VCPU_CACHE_OFFSET1__CACHE_OFFSET1__SHIFT                                                          0x0
#घोषणा UVD_VCPU_CACHE_OFFSET1__CACHE_OFFSET1_MASK                                                            0x01FFFFFFL
//UVD_VCPU_CACHE_SIZE1
#घोषणा UVD_VCPU_CACHE_SIZE1__CACHE_SIZE1__SHIFT                                                              0x0
#घोषणा UVD_VCPU_CACHE_SIZE1__CACHE_SIZE1_MASK                                                                0x001FFFFFL
//UVD_VCPU_CACHE_OFFSET2
#घोषणा UVD_VCPU_CACHE_OFFSET2__CACHE_OFFSET2__SHIFT                                                          0x0
#घोषणा UVD_VCPU_CACHE_OFFSET2__CACHE_OFFSET2_MASK                                                            0x01FFFFFFL
//UVD_VCPU_CACHE_SIZE2
#घोषणा UVD_VCPU_CACHE_SIZE2__CACHE_SIZE2__SHIFT                                                              0x0
#घोषणा UVD_VCPU_CACHE_SIZE2__CACHE_SIZE2_MASK                                                                0x001FFFFFL
//UVD_VCPU_CNTL
#घोषणा UVD_VCPU_CNTL__CLK_EN__SHIFT                                                                          0x9
#घोषणा UVD_VCPU_CNTL__CLK_EN_MASK                                                                            0x00000200L
//UVD_SOFT_RESET
#घोषणा UVD_SOFT_RESET__RBC_SOFT_RESET__SHIFT                                                                 0x0
#घोषणा UVD_SOFT_RESET__LBSI_SOFT_RESET__SHIFT                                                                0x1
#घोषणा UVD_SOFT_RESET__LMI_SOFT_RESET__SHIFT                                                                 0x2
#घोषणा UVD_SOFT_RESET__VCPU_SOFT_RESET__SHIFT                                                                0x3
#घोषणा UVD_SOFT_RESET__UDEC_SOFT_RESET__SHIFT                                                                0x4
#घोषणा UVD_SOFT_RESET__CSM_SOFT_RESET__SHIFT                                                                 0x5
#घोषणा UVD_SOFT_RESET__CXW_SOFT_RESET__SHIFT                                                                 0x6
#घोषणा UVD_SOFT_RESET__TAP_SOFT_RESET__SHIFT                                                                 0x7
#घोषणा UVD_SOFT_RESET__MPC_SOFT_RESET__SHIFT                                                                 0x8
#घोषणा UVD_SOFT_RESET__IH_SOFT_RESET__SHIFT                                                                  0xa
#घोषणा UVD_SOFT_RESET__LMI_UMC_SOFT_RESET__SHIFT                                                             0xd
#घोषणा UVD_SOFT_RESET__SPH_SOFT_RESET__SHIFT                                                                 0xe
#घोषणा UVD_SOFT_RESET__MIF_SOFT_RESET__SHIFT                                                                 0xf
#घोषणा UVD_SOFT_RESET__LCM_SOFT_RESET__SHIFT                                                                 0x10
#घोषणा UVD_SOFT_RESET__SUVD_SOFT_RESET__SHIFT                                                                0x11
#घोषणा UVD_SOFT_RESET__LBSI_VCLK_RESET_STATUS__SHIFT                                                         0x12
#घोषणा UVD_SOFT_RESET__VCPU_VCLK_RESET_STATUS__SHIFT                                                         0x13
#घोषणा UVD_SOFT_RESET__UDEC_VCLK_RESET_STATUS__SHIFT                                                         0x14
#घोषणा UVD_SOFT_RESET__UDEC_DCLK_RESET_STATUS__SHIFT                                                         0x15
#घोषणा UVD_SOFT_RESET__MPC_DCLK_RESET_STATUS__SHIFT                                                          0x16
#घोषणा UVD_SOFT_RESET__MIF_DCLK_RESET_STATUS__SHIFT                                                          0x1a
#घोषणा UVD_SOFT_RESET__LCM_DCLK_RESET_STATUS__SHIFT                                                          0x1b
#घोषणा UVD_SOFT_RESET__SUVD_VCLK_RESET_STATUS__SHIFT                                                         0x1c
#घोषणा UVD_SOFT_RESET__SUVD_DCLK_RESET_STATUS__SHIFT                                                         0x1d
#घोषणा UVD_SOFT_RESET__RE_DCLK_RESET_STATUS__SHIFT                                                           0x1e
#घोषणा UVD_SOFT_RESET__SRE_DCLK_RESET_STATUS__SHIFT                                                          0x1f
#घोषणा UVD_SOFT_RESET__RBC_SOFT_RESET_MASK                                                                   0x00000001L
#घोषणा UVD_SOFT_RESET__LBSI_SOFT_RESET_MASK                                                                  0x00000002L
#घोषणा UVD_SOFT_RESET__LMI_SOFT_RESET_MASK                                                                   0x00000004L
#घोषणा UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK                                                                  0x00000008L
#घोषणा UVD_SOFT_RESET__UDEC_SOFT_RESET_MASK                                                                  0x00000010L
#घोषणा UVD_SOFT_RESET__CSM_SOFT_RESET_MASK                                                                   0x00000020L
#घोषणा UVD_SOFT_RESET__CXW_SOFT_RESET_MASK                                                                   0x00000040L
#घोषणा UVD_SOFT_RESET__TAP_SOFT_RESET_MASK                                                                   0x00000080L
#घोषणा UVD_SOFT_RESET__MPC_SOFT_RESET_MASK                                                                   0x00000100L
#घोषणा UVD_SOFT_RESET__IH_SOFT_RESET_MASK                                                                    0x00000400L
#घोषणा UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK                                                               0x00002000L
#घोषणा UVD_SOFT_RESET__SPH_SOFT_RESET_MASK                                                                   0x00004000L
#घोषणा UVD_SOFT_RESET__MIF_SOFT_RESET_MASK                                                                   0x00008000L
#घोषणा UVD_SOFT_RESET__LCM_SOFT_RESET_MASK                                                                   0x00010000L
#घोषणा UVD_SOFT_RESET__SUVD_SOFT_RESET_MASK                                                                  0x00020000L
#घोषणा UVD_SOFT_RESET__LBSI_VCLK_RESET_STATUS_MASK                                                           0x00040000L
#घोषणा UVD_SOFT_RESET__VCPU_VCLK_RESET_STATUS_MASK                                                           0x00080000L
#घोषणा UVD_SOFT_RESET__UDEC_VCLK_RESET_STATUS_MASK                                                           0x00100000L
#घोषणा UVD_SOFT_RESET__UDEC_DCLK_RESET_STATUS_MASK                                                           0x00200000L
#घोषणा UVD_SOFT_RESET__MPC_DCLK_RESET_STATUS_MASK                                                            0x00400000L
#घोषणा UVD_SOFT_RESET__MIF_DCLK_RESET_STATUS_MASK                                                            0x04000000L
#घोषणा UVD_SOFT_RESET__LCM_DCLK_RESET_STATUS_MASK                                                            0x08000000L
#घोषणा UVD_SOFT_RESET__SUVD_VCLK_RESET_STATUS_MASK                                                           0x10000000L
#घोषणा UVD_SOFT_RESET__SUVD_DCLK_RESET_STATUS_MASK                                                           0x20000000L
#घोषणा UVD_SOFT_RESET__RE_DCLK_RESET_STATUS_MASK                                                             0x40000000L
#घोषणा UVD_SOFT_RESET__SRE_DCLK_RESET_STATUS_MASK                                                            0x80000000L
//UVD_LMI_RBC_IB_VMID
#घोषणा UVD_LMI_RBC_IB_VMID__IB_VMID__SHIFT                                                                   0x0
#घोषणा UVD_LMI_RBC_IB_VMID__IB_VMID_MASK                                                                     0x0000000FL
//UVD_RBC_IB_SIZE
#घोषणा UVD_RBC_IB_SIZE__IB_SIZE__SHIFT                                                                       0x4
#घोषणा UVD_RBC_IB_SIZE__IB_SIZE_MASK                                                                         0x007FFFF0L
//UVD_RBC_RB_RPTR
#घोषणा UVD_RBC_RB_RPTR__RB_RPTR__SHIFT                                                                       0x4
#घोषणा UVD_RBC_RB_RPTR__RB_RPTR_MASK                                                                         0x007FFFF0L
//UVD_RBC_RB_WPTR
#घोषणा UVD_RBC_RB_WPTR__RB_WPTR__SHIFT                                                                       0x4
#घोषणा UVD_RBC_RB_WPTR__RB_WPTR_MASK                                                                         0x007FFFF0L
//UVD_RBC_RB_WPTR_CNTL
#घोषणा UVD_RBC_RB_WPTR_CNTL__RB_PRE_WRITE_TIMER__SHIFT                                                       0x0
#घोषणा UVD_RBC_RB_WPTR_CNTL__RB_PRE_WRITE_TIMER_MASK                                                         0x00007FFFL
//UVD_RBC_RB_CNTL
#घोषणा UVD_RBC_RB_CNTL__RB_BUFSZ__SHIFT                                                                      0x0
#घोषणा UVD_RBC_RB_CNTL__RB_BLKSZ__SHIFT                                                                      0x8
#घोषणा UVD_RBC_RB_CNTL__RB_NO_FETCH__SHIFT                                                                   0x10
#घोषणा UVD_RBC_RB_CNTL__RB_WPTR_POLL_EN__SHIFT                                                               0x14
#घोषणा UVD_RBC_RB_CNTL__RB_NO_UPDATE__SHIFT                                                                  0x18
#घोषणा UVD_RBC_RB_CNTL__RB_RPTR_WR_EN__SHIFT                                                                 0x1c
#घोषणा UVD_RBC_RB_CNTL__RB_BUFSZ_MASK                                                                        0x0000001FL
#घोषणा UVD_RBC_RB_CNTL__RB_BLKSZ_MASK                                                                        0x00001F00L
#घोषणा UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK                                                                     0x00010000L
#घोषणा UVD_RBC_RB_CNTL__RB_WPTR_POLL_EN_MASK                                                                 0x00100000L
#घोषणा UVD_RBC_RB_CNTL__RB_NO_UPDATE_MASK                                                                    0x01000000L
#घोषणा UVD_RBC_RB_CNTL__RB_RPTR_WR_EN_MASK                                                                   0x10000000L
//UVD_RBC_RB_RPTR_ADDR
#घोषणा UVD_RBC_RB_RPTR_ADDR__RB_RPTR_ADDR__SHIFT                                                             0x0
#घोषणा UVD_RBC_RB_RPTR_ADDR__RB_RPTR_ADDR_MASK                                                               0xFFFFFFFFL
//UVD_STATUS
#घोषणा UVD_STATUS__RBC_BUSY__SHIFT                                                                           0x0
#घोषणा UVD_STATUS__VCPU_REPORT__SHIFT                                                                        0x1
#घोषणा UVD_STATUS__AVP_BUSY__SHIFT                                                                           0x8
#घोषणा UVD_STATUS__IDCT_BUSY__SHIFT                                                                          0x9
#घोषणा UVD_STATUS__IDCT_CTL_ACK__SHIFT                                                                       0xb
#घोषणा UVD_STATUS__UVD_CTL_ACK__SHIFT                                                                        0xc
#घोषणा UVD_STATUS__AVP_BLOCK_ACK__SHIFT                                                                      0xd
#घोषणा UVD_STATUS__IDCT_BLOCK_ACK__SHIFT                                                                     0xe
#घोषणा UVD_STATUS__UVD_BLOCK_ACK__SHIFT                                                                      0xf
#घोषणा UVD_STATUS__RBC_ACCESS_GPCOM__SHIFT                                                                   0x10
#घोषणा UVD_STATUS__SYS_GPCOM_REQ__SHIFT                                                                      0x1f
#घोषणा UVD_STATUS__RBC_BUSY_MASK                                                                             0x00000001L
#घोषणा UVD_STATUS__VCPU_REPORT_MASK                                                                          0x000000FEL
#घोषणा UVD_STATUS__AVP_BUSY_MASK                                                                             0x00000100L
#घोषणा UVD_STATUS__IDCT_BUSY_MASK                                                                            0x00000200L
#घोषणा UVD_STATUS__IDCT_CTL_ACK_MASK                                                                         0x00000800L
#घोषणा UVD_STATUS__UVD_CTL_ACK_MASK                                                                          0x00001000L
#घोषणा UVD_STATUS__AVP_BLOCK_ACK_MASK                                                                        0x00002000L
#घोषणा UVD_STATUS__IDCT_BLOCK_ACK_MASK                                                                       0x00004000L
#घोषणा UVD_STATUS__UVD_BLOCK_ACK_MASK                                                                        0x00008000L
#घोषणा UVD_STATUS__RBC_ACCESS_GPCOM_MASK                                                                     0x00010000L
#घोषणा UVD_STATUS__SYS_GPCOM_REQ_MASK                                                                        0x80000000L
//UVD_SEMA_TIMEOUT_STATUS
#घोषणा UVD_SEMA_TIMEOUT_STATUS__SEMAPHORE_WAIT_INCOMPLETE_TIMEOUT_STAT__SHIFT                                0x0
#घोषणा UVD_SEMA_TIMEOUT_STATUS__SEMAPHORE_WAIT_FAULT_TIMEOUT_STAT__SHIFT                                     0x1
#घोषणा UVD_SEMA_TIMEOUT_STATUS__SEMAPHORE_SIGNAL_INCOMPLETE_TIMEOUT_STAT__SHIFT                              0x2
#घोषणा UVD_SEMA_TIMEOUT_STATUS__SEMAPHORE_TIMEOUT_CLEAR__SHIFT                                               0x3
#घोषणा UVD_SEMA_TIMEOUT_STATUS__SEMAPHORE_WAIT_INCOMPLETE_TIMEOUT_STAT_MASK                                  0x00000001L
#घोषणा UVD_SEMA_TIMEOUT_STATUS__SEMAPHORE_WAIT_FAULT_TIMEOUT_STAT_MASK                                       0x00000002L
#घोषणा UVD_SEMA_TIMEOUT_STATUS__SEMAPHORE_SIGNAL_INCOMPLETE_TIMEOUT_STAT_MASK                                0x00000004L
#घोषणा UVD_SEMA_TIMEOUT_STATUS__SEMAPHORE_TIMEOUT_CLEAR_MASK                                                 0x00000008L
//UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL
#घोषणा UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL__WAIT_INCOMPLETE_EN__SHIFT                                      0x0
#घोषणा UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL__WAIT_INCOMPLETE_COUNT__SHIFT                                   0x1
#घोषणा UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL__RESEND_TIMER__SHIFT                                            0x18
#घोषणा UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL__WAIT_INCOMPLETE_EN_MASK                                        0x00000001L
#घोषणा UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL__WAIT_INCOMPLETE_COUNT_MASK                                     0x001FFFFEL
#घोषणा UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL__RESEND_TIMER_MASK                                              0x07000000L
//UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL
#घोषणा UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL__WAIT_FAULT_EN__SHIFT                                                0x0
#घोषणा UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL__WAIT_FAULT_COUNT__SHIFT                                             0x1
#घोषणा UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL__RESEND_TIMER__SHIFT                                                 0x18
#घोषणा UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL__WAIT_FAULT_EN_MASK                                                  0x00000001L
#घोषणा UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL__WAIT_FAULT_COUNT_MASK                                               0x001FFFFEL
#घोषणा UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL__RESEND_TIMER_MASK                                                   0x07000000L
//UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL
#घोषणा UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL__SIGNAL_INCOMPLETE_EN__SHIFT                                  0x0
#घोषणा UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL__SIGNAL_INCOMPLETE_COUNT__SHIFT                               0x1
#घोषणा UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL__RESEND_TIMER__SHIFT                                          0x18
#घोषणा UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL__SIGNAL_INCOMPLETE_EN_MASK                                    0x00000001L
#घोषणा UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL__SIGNAL_INCOMPLETE_COUNT_MASK                                 0x001FFFFEL
#घोषणा UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL__RESEND_TIMER_MASK                                            0x07000000L
//UVD_CONTEXT_ID
#घोषणा UVD_CONTEXT_ID__CONTEXT_ID__SHIFT                                                                     0x0
#घोषणा UVD_CONTEXT_ID__CONTEXT_ID_MASK                                                                       0xFFFFFFFFL
//UVD_CONTEXT_ID2
#घोषणा UVD_CONTEXT_ID2__CONTEXT_ID2__SHIFT                                                                   0x0
#घोषणा UVD_CONTEXT_ID2__CONTEXT_ID2_MASK                                                                     0xFFFFFFFFL

//UVD_FW_STATUS
#घोषणा UVD_FW_STATUS__BUSY__SHIFT                                                                            0x0
#घोषणा UVD_FW_STATUS__ACTIVE__SHIFT                                                                          0x1
#घोषणा UVD_FW_STATUS__SEND_EFUSE_REQ__SHIFT                                                                  0x2
#घोषणा UVD_FW_STATUS__DONE__SHIFT                                                                            0x8
#घोषणा UVD_FW_STATUS__PASS__SHIFT                                                                            0x10
#घोषणा UVD_FW_STATUS__FAIL__SHIFT                                                                            0x11
#घोषणा UVD_FW_STATUS__INVALID_LEN__SHIFT                                                                     0x12
#घोषणा UVD_FW_STATUS__INVALID_0_PADDING__SHIFT                                                               0x13
#घोषणा UVD_FW_STATUS__INVALID_NONCE__SHIFT                                                                   0x14
#घोषणा UVD_FW_STATUS__BUSY_MASK                                                                              0x00000001L
#घोषणा UVD_FW_STATUS__ACTIVE_MASK                                                                            0x00000002L
#घोषणा UVD_FW_STATUS__SEND_EFUSE_REQ_MASK                                                                    0x00000004L
#घोषणा UVD_FW_STATUS__DONE_MASK                                                                              0x00000100L
#घोषणा UVD_FW_STATUS__PASS_MASK                                                                              0x00010000L
#घोषणा UVD_FW_STATUS__FAIL_MASK                                                                              0x00020000L
#घोषणा UVD_FW_STATUS__INVALID_LEN_MASK                                                                       0x00040000L
#घोषणा UVD_FW_STATUS__INVALID_0_PADDING_MASK                                                                 0x00080000L
#घोषणा UVD_FW_STATUS__INVALID_NONCE_MASK                                                                     0x00100000L


#पूर्ण_अगर
