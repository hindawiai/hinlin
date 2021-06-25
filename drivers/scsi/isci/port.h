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

#अगर_अघोषित _ISCI_PORT_H_
#घोषणा _ISCI_PORT_H_

#समावेश <scsi/libsas.h>
#समावेश "isci.h"
#समावेश "sas.h"
#समावेश "phy.h"

#घोषणा SCIC_SDS_DUMMY_PORT   0xFF

#घोषणा PF_NOTIFY (1 << 0)
#घोषणा PF_RESUME (1 << 1)

काष्ठा isci_phy;
काष्ठा isci_host;

क्रमागत isci_status अणु
	isci_मुक्तd        = 0x00,
	isci_starting     = 0x01,
	isci_पढ़ोy        = 0x02,
	isci_पढ़ोy_क्रम_io = 0x03,
	isci_stopping     = 0x04,
	isci_stopped      = 0x05,
पूर्ण;

/**
 * काष्ठा isci_port - isci direct attached sas port object
 * @पढ़ोy_निकास: several states स्थिरitute 'ready'. When निकासing पढ़ोy we
 *              need to take extra port-tearकरोwn actions that are
 *              skipped when निकासing to another 'ready' state.
 * @logical_port_index: software port index
 * @physical_port_index: hardware port index
 * @active_phy_mask: identअगरies phy members
 * @enabled_phy_mask: phy mask क्रम the port
 *                    that are alपढ़ोy part of the port
 * @reserved_tag:
 * @reserved_rni: reserver क्रम port task scheduler workaround
 * @started_request_count: reference count क्रम outstanding commands
 * @not_पढ़ोy_reason: set during state transitions and notअगरied
 * @समयr: समयout start/stop operations
 */
काष्ठा isci_port अणु
	काष्ठा isci_host *isci_host;
	काष्ठा list_head remote_dev_list;
	#घोषणा IPORT_RESET_PENDING 0
	अचिन्हित दीर्घ state;
	क्रमागत sci_status hard_reset_status;
	काष्ठा sci_base_state_machine sm;
	bool पढ़ोy_निकास;
	u8 logical_port_index;
	u8 physical_port_index;
	u8 active_phy_mask;
	u8 enabled_phy_mask;
	u8 last_active_phy;
	u16 reserved_rni;
	u16 reserved_tag;
	u32 started_request_count;
	u32 asचिन्हित_device_count;
	u32 hang_detect_users;
	u32 not_पढ़ोy_reason;
	काष्ठा isci_phy *phy_table[SCI_MAX_PHYS];
	काष्ठा isci_host *owning_controller;
	काष्ठा sci_समयr समयr;
	काष्ठा scu_port_task_scheduler_रेजिस्टरs __iomem *port_task_scheduler_रेजिस्टरs;
	/* XXX rework: only one रेजिस्टर, no need to replicate per-port */
	u32 __iomem *port_pe_configuration_रेजिस्टर;
	काष्ठा scu_viit_entry __iomem *viit_रेजिस्टरs;
पूर्ण;

क्रमागत sci_port_not_पढ़ोy_reason_code अणु
	SCIC_PORT_NOT_READY_NO_ACTIVE_PHYS,
	SCIC_PORT_NOT_READY_HARD_RESET_REQUESTED,
	SCIC_PORT_NOT_READY_INVALID_PORT_CONFIGURATION,
	SCIC_PORT_NOT_READY_RECONFIGURING,

	SCIC_PORT_NOT_READY_REASON_CODE_MAX
पूर्ण;

काष्ठा sci_port_end_poपूर्णांक_properties अणु
	काष्ठा sci_sas_address sas_address;
	काष्ठा sci_phy_proto protocols;
पूर्ण;

काष्ठा sci_port_properties अणु
	u32 index;
	काष्ठा sci_port_end_poपूर्णांक_properties local;
	काष्ठा sci_port_end_poपूर्णांक_properties remote;
	u32 phy_mask;
पूर्ण;

/**
 * क्रमागत sci_port_states - port state machine states
 * @SCI_PORT_STOPPED: port has successfully been stopped.  In this state
 *		      no new IO operations are permitted.  This state is
 *		      entered from the STOPPING state.
 * @SCI_PORT_STOPPING: port is in the process of stopping.  In this
 *		       state no new IO operations are permitted, but
 *		       existing IO operations are allowed to complete.
 *		       This state is entered from the READY state.
 * @SCI_PORT_READY: port is now पढ़ोy.  Thus, the user is able to
 *		    perक्रमm IO operations on this port. This state is
 *		    entered from the STARTING state.
 * @SCI_PORT_SUB_WAITING: port is started and पढ़ोy but has no active
 *			  phys.
 * @SCI_PORT_SUB_OPERATIONAL: port is started and पढ़ोy and there is at
 *			      least one phy operational.
 * @SCI_PORT_SUB_CONFIGURING: port is started and there was an
 *			      add/हटाओ phy event.  This state is only
 *			      used in Automatic Port Configuration Mode
 *			      (APC)
 * @SCI_PORT_RESETTING: port is in the process of perक्रमming a hard
 *			reset.  Thus, the user is unable to perक्रमm IO
 *			operations on this port.  This state is entered
 *			from the READY state.
 * @SCI_PORT_FAILED: port has failed a reset request.  This state is
 *		     entered when a port reset request बार out. This
 *		     state is entered from the RESETTING state.
 */
#घोषणा PORT_STATES अणु\
	C(PORT_STOPPED),\
	C(PORT_STOPPING),\
	C(PORT_READY),\
	C(PORT_SUB_WAITING),\
	C(PORT_SUB_OPERATIONAL),\
	C(PORT_SUB_CONFIGURING),\
	C(PORT_RESETTING),\
	C(PORT_FAILED),\
	पूर्ण
#अघोषित C
#घोषणा C(a) SCI_##a
क्रमागत sci_port_states PORT_STATES;
#अघोषित C

अटल अंतरभूत व्योम sci_port_decrement_request_count(काष्ठा isci_port *iport)
अणु
	अगर (WARN_ONCE(iport->started_request_count == 0,
		       "%s: tried to decrement started_request_count past 0!?",
			__func__))
		/* pass */;
	अन्यथा
		iport->started_request_count--;
पूर्ण

#घोषणा sci_port_active_phy(port, phy) \
	(((port)->active_phy_mask & (1 << (phy)->phy_index)) != 0)

व्योम sci_port_स्थिरruct(
	काष्ठा isci_port *iport,
	u8 port_index,
	काष्ठा isci_host *ihost);

क्रमागत sci_status sci_port_start(काष्ठा isci_port *iport);
क्रमागत sci_status sci_port_stop(काष्ठा isci_port *iport);

क्रमागत sci_status sci_port_add_phy(
	काष्ठा isci_port *iport,
	काष्ठा isci_phy *iphy);

क्रमागत sci_status sci_port_हटाओ_phy(
	काष्ठा isci_port *iport,
	काष्ठा isci_phy *iphy);

व्योम sci_port_setup_transports(
	काष्ठा isci_port *iport,
	u32 device_id);

व्योम isci_port_bcn_enable(काष्ठा isci_host *, काष्ठा isci_port *);

व्योम sci_port_deactivate_phy(
	काष्ठा isci_port *iport,
	काष्ठा isci_phy *iphy,
	bool करो_notअगरy_user);

bool sci_port_link_detected(
	काष्ठा isci_port *iport,
	काष्ठा isci_phy *iphy);

क्रमागत sci_status sci_port_get_properties(
	काष्ठा isci_port *iport,
	काष्ठा sci_port_properties *prop);

क्रमागत sci_status sci_port_link_up(काष्ठा isci_port *iport,
				      काष्ठा isci_phy *iphy);
क्रमागत sci_status sci_port_link_करोwn(काष्ठा isci_port *iport,
					काष्ठा isci_phy *iphy);

काष्ठा isci_request;
काष्ठा isci_remote_device;
क्रमागत sci_status sci_port_start_io(
	काष्ठा isci_port *iport,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

क्रमागत sci_status sci_port_complete_io(
	काष्ठा isci_port *iport,
	काष्ठा isci_remote_device *idev,
	काष्ठा isci_request *ireq);

क्रमागत sas_linkrate sci_port_get_max_allowed_speed(
	काष्ठा isci_port *iport);

व्योम sci_port_broadcast_change_received(
	काष्ठा isci_port *iport,
	काष्ठा isci_phy *iphy);

bool sci_port_is_valid_phy_assignment(
	काष्ठा isci_port *iport,
	u32 phy_index);

व्योम sci_port_get_sas_address(
	काष्ठा isci_port *iport,
	काष्ठा sci_sas_address *sas_address);

व्योम sci_port_get_attached_sas_address(
	काष्ठा isci_port *iport,
	काष्ठा sci_sas_address *sas_address);

व्योम sci_port_set_hang_detection_समयout(
	काष्ठा isci_port *isci_port,
	u32 समयout);

व्योम isci_port_क्रमmed(काष्ठा asd_sas_phy *);
व्योम isci_port_deक्रमmed(काष्ठा asd_sas_phy *);

पूर्णांक isci_port_perक्रमm_hard_reset(काष्ठा isci_host *ihost, काष्ठा isci_port *iport,
				 काष्ठा isci_phy *iphy);
पूर्णांक isci_ata_check_पढ़ोy(काष्ठा करोमुख्य_device *dev);
#पूर्ण_अगर /* !defined(_ISCI_PORT_H_) */
