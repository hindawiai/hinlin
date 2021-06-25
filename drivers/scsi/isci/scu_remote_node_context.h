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

#अगर_अघोषित __SCU_REMOTE_NODE_CONTEXT_HEADER__
#घोषणा __SCU_REMOTE_NODE_CONTEXT_HEADER__

/**
 * This file contains the काष्ठाures and स्थिरatns used by the SCU hardware to
 *    describe a remote node context.
 *
 *
 */

/**
 * काष्ठा ssp_remote_node_context - This काष्ठाure contains the SCU hardware
 *    definition क्रम an SSP remote node.
 *
 *
 */
काष्ठा ssp_remote_node_context अणु
	/* WORD 0 */

	/**
	 * This field is the remote node index asचिन्हित क्रम this remote node. All
	 * remote nodes must have a unique remote node index. The value of the remote
	 * node index can not exceed the maximum number of remote nodes reported in
	 * the SCU device context capacity रेजिस्टर.
	 */
	u32 remote_node_index:12;
	u32 reserved0_1:4;

	/**
	 * This field tells the SCU hardware how many simultaneous connections that
	 * this remote node will support.
	 */
	u32 remote_node_port_width:4;

	/**
	 * This field tells the SCU hardware which logical port to associate with this
	 * remote node.
	 */
	u32 logical_port_index:3;
	u32 reserved0_2:5;

	/**
	 * This field will enable the I_T nexus loss समयr क्रम this remote node.
	 */
	u32 nexus_loss_समयr_enable:1;

	/**
	 * This field is the क्रम driver debug only and is not used.
	 */
	u32 check_bit:1;

	/**
	 * This field must be set to true when the hardware DMAs the remote node
	 * context to the hardware SRAM.  When the remote node is being invalidated
	 * this field must be set to false.
	 */
	u32 is_valid:1;

	/**
	 * This field must be set to true.
	 */
	u32 is_remote_node_context:1;

	/* WORD 1 - 2 */

	/**
	 * This is the low word of the remote device SAS Address
	 */
	u32 remote_sas_address_lo;

	/**
	 * This field is the high word of the remote device SAS Address
	 */
	u32 remote_sas_address_hi;

	/* WORD 3 */
	/**
	 * This field reprensets the function number asचिन्हित to this remote device.
	 * This value must match the भव function number that is being used to
	 * communicate to the device.
	 */
	u32 function_number:8;
	u32 reserved3_1:8;

	/**
	 * This field provides the driver a way to cheat on the arbitration रुको समय
	 * क्रम this remote node.
	 */
	u32 arbitration_रुको_समय:16;

	/* WORD 4 */
	/**
	 * This field tells the SCU hardware how दीर्घ this device may occupy the
	 * connection beक्रमe it must be बंदd.
	 */
	u32 connection_occupancy_समयout:16;

	/**
	 * This field tells the SCU hardware how दीर्घ to मुख्यtain a connection when
	 * there are no frames being transmitted on the link.
	 */
	u32 connection_inactivity_समयout:16;

	/* WORD  5 */
	/**
	 * This field allows the driver to cheat on the arbitration रुको समय क्रम this
	 * remote node.
	 */
	u32 initial_arbitration_रुको_समय:16;

	/**
	 * This field is tells the hardware what to program क्रम the connection rate in
	 * the खोलो address frame.  See the SAS spec क्रम valid values.
	 */
	u32 oaf_connection_rate:4;

	/**
	 * This field tells the SCU hardware what to program क्रम the features in the
	 * खोलो address frame.  See the SAS spec क्रम valid values.
	 */
	u32 oaf_features:4;

	/**
	 * This field tells the SCU hardware what to use क्रम the source zone group in
	 * the खोलो address frame.  See the SAS spec क्रम more details on zoning.
	 */
	u32 oaf_source_zone_group:8;

	/* WORD 6 */
	/**
	 * This field tells the SCU hardware what to use as the more capibilities in
	 * the खोलो address frame. See the SAS Spec क्रम details.
	 */
	u32 oaf_more_compatibility_features;

	/* WORD 7 */
	u32 reserved7;

पूर्ण;

/**
 * काष्ठा stp_remote_node_context - This काष्ठाure contains the SCU hardware
 *    definition क्रम a STP remote node.
 *
 * STP Tarमाला_लो are not yet supported so this definition is a placeholder until
 * we करो support them.
 */
काष्ठा stp_remote_node_context अणु
	/**
	 * Placeholder data क्रम the STP remote node.
	 */
	u32 data[8];

पूर्ण;

/**
 * This जोड़ combines the SAS and SATA remote node definitions.
 *
 * जोड़ scu_remote_node_context
 */
जोड़ scu_remote_node_context अणु
	/**
	 * SSP Remote Node
	 */
	काष्ठा ssp_remote_node_context ssp;

	/**
	 * STP Remote Node
	 */
	काष्ठा stp_remote_node_context stp;

पूर्ण;

#पूर्ण_अगर /* __SCU_REMOTE_NODE_CONTEXT_HEADER__ */
