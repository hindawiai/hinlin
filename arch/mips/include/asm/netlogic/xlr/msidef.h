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

#अगर_अघोषित ASM_RMI_MSIDEF_H
#घोषणा ASM_RMI_MSIDEF_H

/*
 * Constants क्रम Intel APIC based MSI messages.
 * Adapted क्रम the RMI XLR using identical defines
 */

/*
 * Shअगरts क्रम MSI data
 */

#घोषणा MSI_DATA_VECTOR_SHIFT		0
#घोषणा	 MSI_DATA_VECTOR_MASK		0x000000ff
#घोषणा	 MSI_DATA_VECTOR(v)		(((v) << MSI_DATA_VECTOR_SHIFT) & \
						MSI_DATA_VECTOR_MASK)

#घोषणा MSI_DATA_DELIVERY_MODE_SHIFT	8
#घोषणा	 MSI_DATA_DELIVERY_FIXED	(0 << MSI_DATA_DELIVERY_MODE_SHIFT)
#घोषणा	 MSI_DATA_DELIVERY_LOWPRI	(1 << MSI_DATA_DELIVERY_MODE_SHIFT)

#घोषणा MSI_DATA_LEVEL_SHIFT		14
#घोषणा	 MSI_DATA_LEVEL_DEASSERT	(0 << MSI_DATA_LEVEL_SHIFT)
#घोषणा	 MSI_DATA_LEVEL_ASSERT		(1 << MSI_DATA_LEVEL_SHIFT)

#घोषणा MSI_DATA_TRIGGER_SHIFT		15
#घोषणा	 MSI_DATA_TRIGGER_EDGE		(0 << MSI_DATA_TRIGGER_SHIFT)
#घोषणा	 MSI_DATA_TRIGGER_LEVEL		(1 << MSI_DATA_TRIGGER_SHIFT)

/*
 * Shअगरt/mask fields क्रम msi address
 */

#घोषणा MSI_ADDR_BASE_HI		0
#घोषणा MSI_ADDR_BASE_LO		0xfee00000

#घोषणा MSI_ADDR_DEST_MODE_SHIFT	2
#घोषणा	 MSI_ADDR_DEST_MODE_PHYSICAL	(0 << MSI_ADDR_DEST_MODE_SHIFT)
#घोषणा	 MSI_ADDR_DEST_MODE_LOGICAL	(1 << MSI_ADDR_DEST_MODE_SHIFT)

#घोषणा MSI_ADDR_REसूचीECTION_SHIFT	3
#घोषणा	 MSI_ADDR_REसूचीECTION_CPU	(0 << MSI_ADDR_REसूचीECTION_SHIFT)
#घोषणा	 MSI_ADDR_REसूचीECTION_LOWPRI	(1 << MSI_ADDR_REसूचीECTION_SHIFT)

#घोषणा MSI_ADDR_DEST_ID_SHIFT		12
#घोषणा	 MSI_ADDR_DEST_ID_MASK		0x00ffff0
#घोषणा	 MSI_ADDR_DEST_ID(dest)		(((dest) << MSI_ADDR_DEST_ID_SHIFT) & \
						 MSI_ADDR_DEST_ID_MASK)

#पूर्ण_अगर /* ASM_RMI_MSIDEF_H */
