<शैली गुरु>
/*
 * Copyright (c) 2003-2012 Broadcom Corporation
 * All Rights Reserved
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the Broadcom
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
 * THIS SOFTWARE IS PROVIDED BY BROADCOM ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BROADCOM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#अगर_अघोषित _ASM_NLM_FLASH_H_
#घोषणा _ASM_NLM_FLASH_H_

#घोषणा FLASH_CSBASE_ADDR(cs)		(cs)
#घोषणा FLASH_CSADDR_MASK(cs)		(0x10 + (cs))
#घोषणा FLASH_CSDEV_PARM(cs)		(0x20 + (cs))
#घोषणा FLASH_CSTIME_PARMA(cs)		(0x30 + (cs))
#घोषणा FLASH_CSTIME_PARMB(cs)		(0x40 + (cs))

#घोषणा FLASH_INT_MASK			0x50
#घोषणा FLASH_INT_STATUS		0x60
#घोषणा FLASH_ERROR_STATUS		0x70
#घोषणा FLASH_ERROR_ADDR		0x80

#घोषणा FLASH_न_अंकD_CLE(cs)		(0x90 + (cs))
#घोषणा FLASH_न_अंकD_ALE(cs)		(0xa0 + (cs))

#घोषणा FLASH_न_अंकD_CSDEV_PARAM		0x000041e6
#घोषणा FLASH_न_अंकD_CSTIME_PARAMA	0x4f400e22
#घोषणा FLASH_न_अंकD_CSTIME_PARAMB	0x000083cf

#पूर्ण_अगर
