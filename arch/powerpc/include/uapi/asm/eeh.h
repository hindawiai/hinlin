<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301, USA.
 *
 * Copyright IBM Corp. 2015
 *
 * Authors: Gavin Shan <gwshan@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ASM_POWERPC_EEH_H
#घोषणा _ASM_POWERPC_EEH_H

/* PE states */
#घोषणा EEH_PE_STATE_NORMAL		0	/* Normal state		*/
#घोषणा EEH_PE_STATE_RESET		1	/* PE reset निश्चितed	*/
#घोषणा EEH_PE_STATE_STOPPED_IO_DMA	2	/* Frozen PE		*/
#घोषणा EEH_PE_STATE_STOPPED_DMA	4	/* Stopped DMA only	*/
#घोषणा EEH_PE_STATE_UNAVAIL		5	/* Unavailable		*/

/* EEH error types and functions */
#घोषणा EEH_ERR_TYPE_32			0       /* 32-bits error	*/
#घोषणा EEH_ERR_TYPE_64			1       /* 64-bits error	*/
#घोषणा EEH_ERR_FUNC_MIN		0
#घोषणा EEH_ERR_FUNC_LD_MEM_ADDR	0	/* Memory load	*/
#घोषणा EEH_ERR_FUNC_LD_MEM_DATA	1
#घोषणा EEH_ERR_FUNC_LD_IO_ADDR		2	/* IO load	*/
#घोषणा EEH_ERR_FUNC_LD_IO_DATA		3
#घोषणा EEH_ERR_FUNC_LD_CFG_ADDR	4	/* Config load	*/
#घोषणा EEH_ERR_FUNC_LD_CFG_DATA	5
#घोषणा EEH_ERR_FUNC_ST_MEM_ADDR	6	/* Memory store	*/
#घोषणा EEH_ERR_FUNC_ST_MEM_DATA	7
#घोषणा EEH_ERR_FUNC_ST_IO_ADDR		8	/* IO store	*/
#घोषणा EEH_ERR_FUNC_ST_IO_DATA		9
#घोषणा EEH_ERR_FUNC_ST_CFG_ADDR	10	/* Config store	*/
#घोषणा EEH_ERR_FUNC_ST_CFG_DATA	11
#घोषणा EEH_ERR_FUNC_DMA_RD_ADDR	12	/* DMA पढ़ो	*/
#घोषणा EEH_ERR_FUNC_DMA_RD_DATA	13
#घोषणा EEH_ERR_FUNC_DMA_RD_MASTER	14
#घोषणा EEH_ERR_FUNC_DMA_RD_TARGET	15
#घोषणा EEH_ERR_FUNC_DMA_WR_ADDR	16	/* DMA ग_लिखो	*/
#घोषणा EEH_ERR_FUNC_DMA_WR_DATA	17
#घोषणा EEH_ERR_FUNC_DMA_WR_MASTER	18
#घोषणा EEH_ERR_FUNC_DMA_WR_TARGET	19
#घोषणा EEH_ERR_FUNC_MAX		19

#पूर्ण_अगर /* _ASM_POWERPC_EEH_H */
