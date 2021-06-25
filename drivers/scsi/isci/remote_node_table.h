<शैली गुरु>
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _SCIC_SDS_REMOTE_NODE_TABLE_H_
#घोषणा _SCIC_SDS_REMOTE_NODE_TABLE_H_

#समावेश "isci.h"

/**
 *
 *
 * Remote node sets are sets of remote node index in the remote node table. The
 * SCU hardware requires that STP remote node entries take three consecutive
 * remote node index so the table is arranged in sets of three. The bits are
 * used as 0111 0111 to make a byte and the bits define the set of three remote
 * nodes to use as a sequence.
 */
#घोषणा SCIC_SDS_REMOTE_NODE_SETS_PER_BYTE 2

/**
 *
 *
 * Since the remote node table is organized as DWORDS take the remote node sets
 * in bytes and represent them in DWORDs. The lowest ordered bits are the ones
 * used in हाल full DWORD is not being used. i.e. 0000 0000 0000 0000 0111
 * 0111 0111 0111 // अगर only a single WORD is in use in the DWORD.
 */
#घोषणा SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD \
	(माप(u32) * SCIC_SDS_REMOTE_NODE_SETS_PER_BYTE)
/**
 *
 *
 * This is a count of the numeber of remote nodes that can be represented in a
 * byte
 */
#घोषणा SCIC_SDS_REMOTE_NODES_PER_BYTE	\
	(SCU_STP_REMOTE_NODE_COUNT * SCIC_SDS_REMOTE_NODE_SETS_PER_BYTE)

/**
 *
 *
 * This is a count of the number of remote nodes that can be represented in a
 * DWROD
 */
#घोषणा SCIC_SDS_REMOTE_NODES_PER_DWORD	\
	(माप(u32) * SCIC_SDS_REMOTE_NODES_PER_BYTE)

/**
 *
 *
 * This is the number of bits in a remote node group
 */
#घोषणा SCIC_SDS_REMOTE_NODES_BITS_PER_GROUP   4

#घोषणा SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX      (0xFFFFFFFF)
#घोषणा SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE    (0x07)
#घोषणा SCIC_SDS_REMOTE_NODE_TABLE_EMPTY_SLOT_VALUE   (0x00)

/**
 *
 *
 * Expander attached sata remote node count
 */
#घोषणा SCU_STP_REMOTE_NODE_COUNT        3

/**
 *
 *
 * Expander or direct attached ssp remote node count
 */
#घोषणा SCU_SSP_REMOTE_NODE_COUNT        1

/**
 *
 *
 * Direct attached STP remote node count
 */
#घोषणा SCU_SATA_REMOTE_NODE_COUNT       1

/**
 * काष्ठा sci_remote_node_table -
 *
 *
 */
काष्ठा sci_remote_node_table अणु
	/**
	 * This field contains the array size in dwords
	 */
	u16 available_nodes_array_size;

	/**
	 * This field contains the array size of the
	 */
	u16 group_array_size;

	/**
	 * This field is the array of available remote node entries in bits.
	 * Because of the way STP remote node data is allocated on the SCU hardware
	 * the remote nodes must occupy three consecutive remote node context
	 * entries.  For ease of allocation and de-allocation we have broken the
	 * sets of three पूर्णांकo a single nibble.  When the STP RNi is allocated all
	 * of the bits in the nibble are cleared.  This math results in a table size
	 * of MAX_REMOTE_NODES / CONSECUTIVE RNi ENTRIES क्रम STP / 2 entries per byte.
	 */
	u32 available_remote_nodes[
		(SCI_MAX_REMOTE_DEVICES / SCIC_SDS_REMOTE_NODES_PER_DWORD)
		+ ((SCI_MAX_REMOTE_DEVICES % SCIC_SDS_REMOTE_NODES_PER_DWORD) != 0)];

	/**
	 * This field is the nibble selector क्रम the above table.  There are three
	 * possible selectors each क्रम fast lookup when trying to find one, two or
	 * three remote node entries.
	 */
	u32 remote_node_groups[
		SCU_STP_REMOTE_NODE_COUNT][
		(SCI_MAX_REMOTE_DEVICES / (32 * SCU_STP_REMOTE_NODE_COUNT))
		+ ((SCI_MAX_REMOTE_DEVICES % (32 * SCU_STP_REMOTE_NODE_COUNT)) != 0)];

पूर्ण;

/* --------------------------------------------------------------------------- */

व्योम sci_remote_node_table_initialize(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 remote_node_entries);

u16 sci_remote_node_table_allocate_remote_node(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 remote_node_count);

व्योम sci_remote_node_table_release_remote_node_index(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 remote_node_count,
	u16 remote_node_index);

#पूर्ण_अगर /* _SCIC_SDS_REMOTE_NODE_TABLE_H_ */
