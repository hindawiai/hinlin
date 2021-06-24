<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _xgmi_4_0_0_SH_MASK_HEADER
#घोषणा _xgmi_4_0_0_SH_MASK_HEADER

//PCS_GOPX16_PCS_ERROR_STATUS
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__DataLossErr__SHIFT								0x0
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__TrainingErr__SHIFT								0x1
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__CRCErr__SHIFT								0x5
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__BERExceededErr__SHIFT							0x6
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__TxMetaDataErr__SHIFT								0x7
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReplayBufParityErr__SHIFT							0x8
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__DataParityErr__SHIFT								0x9
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReplayFअगरoOverflowErr__SHIFT							0xa
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReplayFअगरoUnderflowErr__SHIFT						0xb
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ElasticFअगरoOverflowErr__SHIFT						0xc
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__DeskewErr__SHIFT								0xd
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__DataStartupLimitErr__SHIFT							0xf
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__FCInitTimeoutErr__SHIFT							0x10
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__RecoveryTimeoutErr__SHIFT							0x11
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReadySerialTimeoutErr__SHIFT							0x12
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReadySerialAttemptErr__SHIFT							0x13
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__RecoveryAttemptErr__SHIFT							0x14
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__RecoveryRelockAttemptErr__SHIFT						0x15
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ClearBERAccum__SHIFT								0x17
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__BERAccumulator__SHIFT							0x18
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__DataLossErr_MASK								0x00000001L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__TrainingErr_MASK								0x00000002L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__CRCErr_MASK									0x00000020L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__BERExceededErr_MASK								0x00000040L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__TxMetaDataErr_MASK								0x00000080L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReplayBufParityErr_MASK							0x00000100L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__DataParityErr_MASK								0x00000200L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReplayFअगरoOverflowErr_MASK							0x00000400L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReplayFअगरoUnderflowErr_MASK							0x00000800L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ElasticFअगरoOverflowErr_MASK							0x00001000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__DeskewErr_MASK								0x00002000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__DataStartupLimitErr_MASK							0x00008000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__FCInitTimeoutErr_MASK							0x00010000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__RecoveryTimeoutErr_MASK							0x00020000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReadySerialTimeoutErr_MASK							0x00040000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ReadySerialAttemptErr_MASK							0x00080000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__RecoveryAttemptErr_MASK							0x00100000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__RecoveryRelockAttemptErr_MASK						0x00200000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__ClearBERAccum_MASK								0x00800000L
#घोषणा	XGMI0_PCS_GOPX16_PCS_ERROR_STATUS__BERAccumulator_MASK								0xFF000000L

#पूर्ण_अगर
