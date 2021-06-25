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

/*
 * This file contains the implementation of the SCIC_SDS_REMOTE_NODE_TABLE
 *    खुला, रक्षित, and निजी methods.
 */
#समावेश "remote_node_table.h"
#समावेश "remote_node_context.h"

/**
 * sci_remote_node_table_get_group_index()
 * @remote_node_table: This is the remote node index table from which the
 *    selection will be made.
 * @group_table_index: This is the index to the group table from which to
 *    search क्रम an available selection.
 *
 * This routine will find the bit position in असलolute bit terms of the next 32
 * + bit position.  If there are available bits in the first u32 then it is
 * just bit position. u32 This is the असलolute bit position क्रम an available
 * group.
 */
अटल u32 sci_remote_node_table_get_group_index(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 group_table_index)
अणु
	u32 dword_index;
	u32 *group_table;
	u32 bit_index;

	group_table = remote_node_table->remote_node_groups[group_table_index];

	क्रम (dword_index = 0; dword_index < remote_node_table->group_array_size; dword_index++) अणु
		अगर (group_table[dword_index] != 0) अणु
			क्रम (bit_index = 0; bit_index < 32; bit_index++) अणु
				अगर ((group_table[dword_index] & (1 << bit_index)) != 0) अणु
					वापस (dword_index * 32) + bit_index;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX;
पूर्ण

/**
 * sci_remote_node_table_clear_group_index()
 * @remote_node_table: This the remote node table in which to clear the
 *    selector.
 * @group_table_index: This is the remote node selector in which the change will be
 *    made.
 * @group_index: This is the bit index in the table to be modअगरied.
 *
 * This method will clear the group index entry in the specअगरied group index
 * table. none
 */
अटल व्योम sci_remote_node_table_clear_group_index(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 group_table_index,
	u32 group_index)
अणु
	u32 dword_index;
	u32 bit_index;
	u32 *group_table;

	BUG_ON(group_table_index >= SCU_STP_REMOTE_NODE_COUNT);
	BUG_ON(group_index >= (u32)(remote_node_table->group_array_size * 32));

	dword_index = group_index / 32;
	bit_index   = group_index % 32;
	group_table = remote_node_table->remote_node_groups[group_table_index];

	group_table[dword_index] = group_table[dword_index] & ~(1 << bit_index);
पूर्ण

/**
 * sci_remote_node_table_set_group_index()
 * @remote_node_table: This the remote node table in which to set the
 *    selector.
 * @group_table_index: This is the remote node selector in which the change
 *    will be made.
 * @group_index: This is the bit position in the table to be modअगरied.
 *
 * This method will set the group index bit entry in the specअगरied gropu index
 * table. none
 */
अटल व्योम sci_remote_node_table_set_group_index(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 group_table_index,
	u32 group_index)
अणु
	u32 dword_index;
	u32 bit_index;
	u32 *group_table;

	BUG_ON(group_table_index >= SCU_STP_REMOTE_NODE_COUNT);
	BUG_ON(group_index >= (u32)(remote_node_table->group_array_size * 32));

	dword_index = group_index / 32;
	bit_index   = group_index % 32;
	group_table = remote_node_table->remote_node_groups[group_table_index];

	group_table[dword_index] = group_table[dword_index] | (1 << bit_index);
पूर्ण

/**
 * sci_remote_node_table_set_node_index()
 * @remote_node_table: This is the remote node table in which to modअगरy
 *    the remote node availability.
 * @remote_node_index: This is the remote node index that is being वापसed to
 *    the table.
 *
 * This method will set the remote to available in the remote node allocation
 * table. none
 */
अटल व्योम sci_remote_node_table_set_node_index(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 remote_node_index)
अणु
	u32 dword_location;
	u32 dword_reमुख्यder;
	u32 slot_normalized;
	u32 slot_position;

	BUG_ON(
		(remote_node_table->available_nodes_array_size * SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD)
		<= (remote_node_index / SCU_STP_REMOTE_NODE_COUNT)
		);

	dword_location  = remote_node_index / SCIC_SDS_REMOTE_NODES_PER_DWORD;
	dword_reमुख्यder = remote_node_index % SCIC_SDS_REMOTE_NODES_PER_DWORD;
	slot_normalized = (dword_reमुख्यder / SCU_STP_REMOTE_NODE_COUNT) * माप(u32);
	slot_position   = remote_node_index % SCU_STP_REMOTE_NODE_COUNT;

	remote_node_table->available_remote_nodes[dword_location] |=
		1 << (slot_normalized + slot_position);
पूर्ण

/**
 * sci_remote_node_table_clear_node_index()
 * @remote_node_table: This is the remote node table from which to clear
 *    the available remote node bit.
 * @remote_node_index: This is the remote node index which is to be cleared
 *    from the table.
 *
 * This method clears the remote node index from the table of available remote
 * nodes. none
 */
अटल व्योम sci_remote_node_table_clear_node_index(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 remote_node_index)
अणु
	u32 dword_location;
	u32 dword_reमुख्यder;
	u32 slot_position;
	u32 slot_normalized;

	BUG_ON(
		(remote_node_table->available_nodes_array_size * SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD)
		<= (remote_node_index / SCU_STP_REMOTE_NODE_COUNT)
		);

	dword_location  = remote_node_index / SCIC_SDS_REMOTE_NODES_PER_DWORD;
	dword_reमुख्यder = remote_node_index % SCIC_SDS_REMOTE_NODES_PER_DWORD;
	slot_normalized = (dword_reमुख्यder / SCU_STP_REMOTE_NODE_COUNT) * माप(u32);
	slot_position   = remote_node_index % SCU_STP_REMOTE_NODE_COUNT;

	remote_node_table->available_remote_nodes[dword_location] &=
		~(1 << (slot_normalized + slot_position));
पूर्ण

/**
 * sci_remote_node_table_clear_group()
 * @remote_node_table: The remote node table from which the slot will be
 *    cleared.
 * @group_index: The index क्रम the slot that is to be cleared.
 *
 * This method clears the entire table slot at the specअगरied slot index. none
 */
अटल व्योम sci_remote_node_table_clear_group(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 group_index)
अणु
	u32 dword_location;
	u32 dword_reमुख्यder;
	u32 dword_value;

	BUG_ON(
		(remote_node_table->available_nodes_array_size * SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD)
		<= (group_index / SCU_STP_REMOTE_NODE_COUNT)
		);

	dword_location  = group_index / SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;
	dword_reमुख्यder = group_index % SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;

	dword_value = remote_node_table->available_remote_nodes[dword_location];
	dword_value &= ~(SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE << (dword_reमुख्यder * 4));
	remote_node_table->available_remote_nodes[dword_location] = dword_value;
पूर्ण

/*
 * sci_remote_node_table_set_group()
 *
 * THis method sets an entire remote node group in the remote node table.
 */
अटल व्योम sci_remote_node_table_set_group(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 group_index)
अणु
	u32 dword_location;
	u32 dword_reमुख्यder;
	u32 dword_value;

	BUG_ON(
		(remote_node_table->available_nodes_array_size * SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD)
		<= (group_index / SCU_STP_REMOTE_NODE_COUNT)
		);

	dword_location  = group_index / SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;
	dword_reमुख्यder = group_index % SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;

	dword_value = remote_node_table->available_remote_nodes[dword_location];
	dword_value |= (SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE << (dword_reमुख्यder * 4));
	remote_node_table->available_remote_nodes[dword_location] = dword_value;
पूर्ण

/**
 * sci_remote_node_table_get_group_value()
 * @remote_node_table: This is the remote node table that क्रम which the group
 *    value is to be वापसed.
 * @group_index: This is the group index to use to find the group value.
 *
 * This method will वापस the group value क्रम the specअगरied group index. The
 * bit values at the specअगरied remote node group index.
 */
अटल u8 sci_remote_node_table_get_group_value(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 group_index)
अणु
	u32 dword_location;
	u32 dword_reमुख्यder;
	u32 dword_value;

	dword_location  = group_index / SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;
	dword_reमुख्यder = group_index % SCIC_SDS_REMOTE_NODE_SETS_PER_DWORD;

	dword_value = remote_node_table->available_remote_nodes[dword_location];
	dword_value &= (SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE << (dword_reमुख्यder * 4));
	dword_value = dword_value >> (dword_reमुख्यder * 4);

	वापस (u8)dword_value;
पूर्ण

/**
 * sci_remote_node_table_initialize()
 * @remote_node_table: The remote that which is to be initialized.
 * @remote_node_entries: The number of entries to put in the table.
 *
 * This method will initialize the remote node table क्रम use. none
 */
व्योम sci_remote_node_table_initialize(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 remote_node_entries)
अणु
	u32 index;

	/*
	 * Initialize the raw data we could improve the speed by only initializing
	 * those entries that we are actually going to be used */
	स_रखो(
		remote_node_table->available_remote_nodes,
		0x00,
		माप(remote_node_table->available_remote_nodes)
		);

	स_रखो(
		remote_node_table->remote_node_groups,
		0x00,
		माप(remote_node_table->remote_node_groups)
		);

	/* Initialize the available remote node sets */
	remote_node_table->available_nodes_array_size = (u16)
							(remote_node_entries / SCIC_SDS_REMOTE_NODES_PER_DWORD)
							+ ((remote_node_entries % SCIC_SDS_REMOTE_NODES_PER_DWORD) != 0);


	/* Initialize each full DWORD to a FULL SET of remote nodes */
	क्रम (index = 0; index < remote_node_entries; index++) अणु
		sci_remote_node_table_set_node_index(remote_node_table, index);
	पूर्ण

	remote_node_table->group_array_size = (u16)
					      (remote_node_entries / (SCU_STP_REMOTE_NODE_COUNT * 32))
					      + ((remote_node_entries % (SCU_STP_REMOTE_NODE_COUNT * 32)) != 0);

	क्रम (index = 0; index < (remote_node_entries / SCU_STP_REMOTE_NODE_COUNT); index++) अणु
		/*
		 * These are all guaranteed to be full slot values so fill them in the
		 * available sets of 3 remote nodes */
		sci_remote_node_table_set_group_index(remote_node_table, 2, index);
	पूर्ण

	/* Now fill in any reमुख्यders that we may find */
	अगर ((remote_node_entries % SCU_STP_REMOTE_NODE_COUNT) == 2) अणु
		sci_remote_node_table_set_group_index(remote_node_table, 1, index);
	पूर्ण अन्यथा अगर ((remote_node_entries % SCU_STP_REMOTE_NODE_COUNT) == 1) अणु
		sci_remote_node_table_set_group_index(remote_node_table, 0, index);
	पूर्ण
पूर्ण

/**
 * sci_remote_node_table_allocate_single_remote_node()
 * @remote_node_table: The remote node table from which to allocate a
 *    remote node.
 * @group_table_index: The group index that is to be used क्रम the search.
 *
 * This method will allocate a single RNi from the remote node table.  The
 * table index will determine from which remote node group table to search.
 * This search may fail and another group node table can be specअगरied.  The
 * function is deचिन्हित to allow a serach of the available single remote node
 * group up to the triple remote node group.  If an entry is found in the
 * specअगरied table the remote node is हटाओd and the remote node groups are
 * updated. The RNi value or an invalid remote node context अगर an RNi can not
 * be found.
 */
अटल u16 sci_remote_node_table_allocate_single_remote_node(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 group_table_index)
अणु
	u8 index;
	u8 group_value;
	u32 group_index;
	u16 remote_node_index = SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX;

	group_index = sci_remote_node_table_get_group_index(
		remote_node_table, group_table_index);

	/* We could not find an available slot in the table selector 0 */
	अगर (group_index != SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX) अणु
		group_value = sci_remote_node_table_get_group_value(
			remote_node_table, group_index);

		क्रम (index = 0; index < SCU_STP_REMOTE_NODE_COUNT; index++) अणु
			अगर (((1 << index) & group_value) != 0) अणु
				/* We have selected a bit now clear it */
				remote_node_index = (u16)(group_index * SCU_STP_REMOTE_NODE_COUNT
							  + index);

				sci_remote_node_table_clear_group_index(
					remote_node_table, group_table_index, group_index
					);

				sci_remote_node_table_clear_node_index(
					remote_node_table, remote_node_index
					);

				अगर (group_table_index > 0) अणु
					sci_remote_node_table_set_group_index(
						remote_node_table, group_table_index - 1, group_index
						);
				पूर्ण

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस remote_node_index;
पूर्ण

/**
 * sci_remote_node_table_allocate_triple_remote_node()
 * @remote_node_table: This is the remote node table from which to allocate the
 *    remote node entries.
 * @group_table_index: This is the group table index which must equal two (2)
 *    क्रम this operation.
 *
 * This method will allocate three consecutive remote node context entries. If
 * there are no reमुख्यing triple entries the function will वापस a failure.
 * The remote node index that represents three consecutive remote node entries
 * or an invalid remote node context अगर none can be found.
 */
अटल u16 sci_remote_node_table_allocate_triple_remote_node(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 group_table_index)
अणु
	u32 group_index;
	u16 remote_node_index = SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX;

	group_index = sci_remote_node_table_get_group_index(
		remote_node_table, group_table_index);

	अगर (group_index != SCIC_SDS_REMOTE_NODE_TABLE_INVALID_INDEX) अणु
		remote_node_index = (u16)group_index * SCU_STP_REMOTE_NODE_COUNT;

		sci_remote_node_table_clear_group_index(
			remote_node_table, group_table_index, group_index
			);

		sci_remote_node_table_clear_group(
			remote_node_table, group_index
			);
	पूर्ण

	वापस remote_node_index;
पूर्ण

/**
 * sci_remote_node_table_allocate_remote_node()
 * @remote_node_table: This is the remote node table from which the remote node
 *    allocation is to take place.
 * @remote_node_count: This is ther remote node count which is one of
 *    SCU_SSP_REMOTE_NODE_COUNT(1) or SCU_STP_REMOTE_NODE_COUNT(3).
 *
 * This method will allocate a remote node that mataches the remote node count
 * specअगरied by the caller.  Valid values क्रम remote node count is
 * SCU_SSP_REMOTE_NODE_COUNT(1) or SCU_STP_REMOTE_NODE_COUNT(3). u16 This is
 * the remote node index that is वापसed or an invalid remote node context.
 */
u16 sci_remote_node_table_allocate_remote_node(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 remote_node_count)
अणु
	u16 remote_node_index = SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX;

	अगर (remote_node_count == SCU_SSP_REMOTE_NODE_COUNT) अणु
		remote_node_index =
			sci_remote_node_table_allocate_single_remote_node(
				remote_node_table, 0);

		अगर (remote_node_index == SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX) अणु
			remote_node_index =
				sci_remote_node_table_allocate_single_remote_node(
					remote_node_table, 1);
		पूर्ण

		अगर (remote_node_index == SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX) अणु
			remote_node_index =
				sci_remote_node_table_allocate_single_remote_node(
					remote_node_table, 2);
		पूर्ण
	पूर्ण अन्यथा अगर (remote_node_count == SCU_STP_REMOTE_NODE_COUNT) अणु
		remote_node_index =
			sci_remote_node_table_allocate_triple_remote_node(
				remote_node_table, 2);
	पूर्ण

	वापस remote_node_index;
पूर्ण

/**
 * sci_remote_node_table_release_single_remote_node()
 * @remote_node_table: This is the remote node table from which the remote node
 *    release is to take place.
 * @remote_node_index: This is the remote node index that is being released.
 * This method will मुक्त a single remote node index back to the remote node
 * table.  This routine will update the remote node groups
 */
अटल व्योम sci_remote_node_table_release_single_remote_node(
	काष्ठा sci_remote_node_table *remote_node_table,
	u16 remote_node_index)
अणु
	u32 group_index;
	u8 group_value;

	group_index = remote_node_index / SCU_STP_REMOTE_NODE_COUNT;

	group_value = sci_remote_node_table_get_group_value(remote_node_table, group_index);

	/*
	 * Assert that we are not trying to add an entry to a slot that is alपढ़ोy
	 * full. */
	BUG_ON(group_value == SCIC_SDS_REMOTE_NODE_TABLE_FULL_SLOT_VALUE);

	अगर (group_value == 0x00) अणु
		/*
		 * There are no entries in this slot so it must be added to the single
		 * slot table. */
		sci_remote_node_table_set_group_index(remote_node_table, 0, group_index);
	पूर्ण अन्यथा अगर ((group_value & (group_value - 1)) == 0) अणु
		/*
		 * There is only one entry in this slot so it must be moved from the
		 * single slot table to the dual slot table */
		sci_remote_node_table_clear_group_index(remote_node_table, 0, group_index);
		sci_remote_node_table_set_group_index(remote_node_table, 1, group_index);
	पूर्ण अन्यथा अणु
		/*
		 * There are two entries in the slot so it must be moved from the dual
		 * slot table to the tripple slot table. */
		sci_remote_node_table_clear_group_index(remote_node_table, 1, group_index);
		sci_remote_node_table_set_group_index(remote_node_table, 2, group_index);
	पूर्ण

	sci_remote_node_table_set_node_index(remote_node_table, remote_node_index);
पूर्ण

/**
 * sci_remote_node_table_release_triple_remote_node()
 * @remote_node_table: This is the remote node table to which the remote node
 *    index is to be मुक्तd.
 * @remote_node_index: This is the remote node index that is being released.
 *
 * This method will release a group of three consecutive remote nodes back to
 * the मुक्त remote nodes.
 */
अटल व्योम sci_remote_node_table_release_triple_remote_node(
	काष्ठा sci_remote_node_table *remote_node_table,
	u16 remote_node_index)
अणु
	u32 group_index;

	group_index = remote_node_index / SCU_STP_REMOTE_NODE_COUNT;

	sci_remote_node_table_set_group_index(
		remote_node_table, 2, group_index
		);

	sci_remote_node_table_set_group(remote_node_table, group_index);
पूर्ण

/**
 * sci_remote_node_table_release_remote_node_index()
 * @remote_node_table: The remote node table to which the remote node index is
 *    to be मुक्तd.
 * @remote_node_count: This is the count of consecutive remote nodes that are
 *    to be मुक्तd.
 * @remote_node_index: This is the remote node index that is being released.
 *
 * This method will release the remote node index back पूर्णांकo the remote node
 * table मुक्त pool.
 */
व्योम sci_remote_node_table_release_remote_node_index(
	काष्ठा sci_remote_node_table *remote_node_table,
	u32 remote_node_count,
	u16 remote_node_index)
अणु
	अगर (remote_node_count == SCU_SSP_REMOTE_NODE_COUNT) अणु
		sci_remote_node_table_release_single_remote_node(
			remote_node_table, remote_node_index);
	पूर्ण अन्यथा अगर (remote_node_count == SCU_STP_REMOTE_NODE_COUNT) अणु
		sci_remote_node_table_release_triple_remote_node(
			remote_node_table, remote_node_index);
	पूर्ण
पूर्ण

