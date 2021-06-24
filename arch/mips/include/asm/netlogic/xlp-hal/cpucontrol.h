<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __NLM_HAL_CPUCONTROL_H__
#घोषणा __NLM_HAL_CPUCONTROL_H__

#घोषणा CPU_BLOCKID_IFU		0
#घोषणा CPU_BLOCKID_ICU		1
#घोषणा CPU_BLOCKID_IEU		2
#घोषणा CPU_BLOCKID_LSU		3
#घोषणा CPU_BLOCKID_MMU		4
#घोषणा CPU_BLOCKID_PRF		5
#घोषणा CPU_BLOCKID_SCH		7
#घोषणा CPU_BLOCKID_SCU		8
#घोषणा CPU_BLOCKID_FPU		9
#घोषणा CPU_BLOCKID_MAP		10

#घोषणा IFU_BRUB_RESERVE	0x007

#घोषणा ICU_DEFEATURE		0x100

#घोषणा LSU_DEFEATURE		0x304
#घोषणा LSU_DEBUG_ADDR		0x305
#घोषणा LSU_DEBUG_DATA0		0x306
#घोषणा LSU_CERRLOG_REGID	0x309
#घोषणा SCHED_DEFEATURE		0x700

/* Offsets of पूर्णांकerest from the 'MAP' Block */
#घोषणा MAP_THREADMODE			0x00
#घोषणा MAP_EXT_EBASE_ENABLE		0x04
#घोषणा MAP_CCDI_CONFIG			0x08
#घोषणा MAP_THRD0_CCDI_STATUS		0x0c
#घोषणा MAP_THRD1_CCDI_STATUS		0x10
#घोषणा MAP_THRD2_CCDI_STATUS		0x14
#घोषणा MAP_THRD3_CCDI_STATUS		0x18
#घोषणा MAP_THRD0_DEBUG_MODE		0x1c
#घोषणा MAP_THRD1_DEBUG_MODE		0x20
#घोषणा MAP_THRD2_DEBUG_MODE		0x24
#घोषणा MAP_THRD3_DEBUG_MODE		0x28
#घोषणा MAP_MISC_STATE			0x60
#घोषणा MAP_DEBUG_READ_CTL		0x64
#घोषणा MAP_DEBUG_READ_REG0		0x68
#घोषणा MAP_DEBUG_READ_REG1		0x6c

#घोषणा MMU_SETUP		0x400
#घोषणा MMU_LFSRSEED		0x401
#घोषणा MMU_HPW_NUM_PAGE_LVL	0x410
#घोषणा MMU_PGWKR_PGDBASE	0x411
#घोषणा MMU_PGWKR_PGDSHFT	0x412
#घोषणा MMU_PGWKR_PGDMASK	0x413
#घोषणा MMU_PGWKR_PUDSHFT	0x414
#घोषणा MMU_PGWKR_PUDMASK	0x415
#घोषणा MMU_PGWKR_PMDSHFT	0x416
#घोषणा MMU_PGWKR_PMDMASK	0x417
#घोषणा MMU_PGWKR_PTESHFT	0x418
#घोषणा MMU_PGWKR_PTEMASK	0x419

#पूर्ण_अगर /* __NLM_CPUCONTROL_H__ */
