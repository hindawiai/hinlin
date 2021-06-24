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

#समावेश "isci.h"
#समावेश "port.h"
#समावेश "request.h"

#घोषणा SCIC_SDS_PORT_HARD_RESET_TIMEOUT  (1000)
#घोषणा SCU_DUMMY_INDEX    (0xFFFF)

#अघोषित C
#घोषणा C(a) (#a)
अटल स्थिर अक्षर *port_state_name(क्रमागत sci_port_states state)
अणु
	अटल स्थिर अक्षर * स्थिर strings[] = PORT_STATES;

	वापस strings[state];
पूर्ण
#अघोषित C

अटल काष्ठा device *sciport_to_dev(काष्ठा isci_port *iport)
अणु
	पूर्णांक i = iport->physical_port_index;
	काष्ठा isci_port *table;
	काष्ठा isci_host *ihost;

	अगर (i == SCIC_SDS_DUMMY_PORT)
		i = SCI_MAX_PORTS+1;

	table = iport - i;
	ihost = container_of(table, typeof(*ihost), ports[0]);

	वापस &ihost->pdev->dev;
पूर्ण

अटल व्योम sci_port_get_protocols(काष्ठा isci_port *iport, काष्ठा sci_phy_proto *proto)
अणु
	u8 index;

	proto->all = 0;
	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		काष्ठा isci_phy *iphy = iport->phy_table[index];

		अगर (!iphy)
			जारी;
		sci_phy_get_protocols(iphy, proto);
	पूर्ण
पूर्ण

अटल u32 sci_port_get_phys(काष्ठा isci_port *iport)
अणु
	u32 index;
	u32 mask;

	mask = 0;
	क्रम (index = 0; index < SCI_MAX_PHYS; index++)
		अगर (iport->phy_table[index])
			mask |= (1 << index);

	वापस mask;
पूर्ण

/**
 * sci_port_get_properties() - This method simply वापसs the properties
 *    regarding the port, such as: physical index, protocols, sas address, etc.
 * @iport: this parameter specअगरies the port क्रम which to retrieve the physical
 *    index.
 * @prop: This parameter specअगरies the properties काष्ठाure पूर्णांकo which to
 *    copy the requested inक्रमmation.
 *
 * Indicate अगर the user specअगरied a valid port. SCI_SUCCESS This value is
 * वापसed अगर the specअगरied port was valid. SCI_FAILURE_INVALID_PORT This
 * value is वापसed अगर the specअगरied port is not valid.  When this value is
 * वापसed, no data is copied to the properties output parameter.
 */
क्रमागत sci_status sci_port_get_properties(काष्ठा isci_port *iport,
						काष्ठा sci_port_properties *prop)
अणु
	अगर (!iport || iport->logical_port_index == SCIC_SDS_DUMMY_PORT)
		वापस SCI_FAILURE_INVALID_PORT;

	prop->index = iport->logical_port_index;
	prop->phy_mask = sci_port_get_phys(iport);
	sci_port_get_sas_address(iport, &prop->local.sas_address);
	sci_port_get_protocols(iport, &prop->local.protocols);
	sci_port_get_attached_sas_address(iport, &prop->remote.sas_address);

	वापस SCI_SUCCESS;
पूर्ण

अटल व्योम sci_port_bcn_enable(काष्ठा isci_port *iport)
अणु
	काष्ठा isci_phy *iphy;
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(iport->phy_table); i++) अणु
		iphy = iport->phy_table[i];
		अगर (!iphy)
			जारी;
		val = पढ़ोl(&iphy->link_layer_रेजिस्टरs->link_layer_control);
		/* clear the bit by writing 1. */
		ग_लिखोl(val, &iphy->link_layer_रेजिस्टरs->link_layer_control);
	पूर्ण
पूर्ण

अटल व्योम isci_port_bc_change_received(काष्ठा isci_host *ihost,
					 काष्ठा isci_port *iport,
					 काष्ठा isci_phy *iphy)
अणु
	dev_dbg(&ihost->pdev->dev,
		"%s: isci_phy = %p, sas_phy = %p\n",
		__func__, iphy, &iphy->sas_phy);

	sas_notअगरy_port_event(&iphy->sas_phy,
			      PORTE_BROADCAST_RCVD, GFP_ATOMIC);
	sci_port_bcn_enable(iport);
पूर्ण

अटल व्योम isci_port_link_up(काष्ठा isci_host *isci_host,
			      काष्ठा isci_port *iport,
			      काष्ठा isci_phy *iphy)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sci_port_properties properties;
	अचिन्हित दीर्घ success = true;

	dev_dbg(&isci_host->pdev->dev,
		"%s: isci_port = %p\n",
		__func__, iport);

	spin_lock_irqsave(&iphy->sas_phy.frame_rcvd_lock, flags);

	sci_port_get_properties(iport, &properties);

	अगर (iphy->protocol == SAS_PROTOCOL_SATA) अणु
		u64 attached_sas_address;

		iphy->sas_phy.oob_mode = SATA_OOB_MODE;
		iphy->sas_phy.frame_rcvd_size = माप(काष्ठा dev_to_host_fis);

		/*
		 * For direct-attached SATA devices, the SCI core will
		 * स्वतःmagically assign a SAS address to the end device
		 * क्रम the purpose of creating a port. This SAS address
		 * will not be the same as asचिन्हित to the PHY and needs
		 * to be obtained from काष्ठा sci_port_properties properties.
		 */
		attached_sas_address = properties.remote.sas_address.high;
		attached_sas_address <<= 32;
		attached_sas_address |= properties.remote.sas_address.low;
		swab64s(&attached_sas_address);

		स_नकल(&iphy->sas_phy.attached_sas_addr,
		       &attached_sas_address, माप(attached_sas_address));
	पूर्ण अन्यथा अगर (iphy->protocol == SAS_PROTOCOL_SSP) अणु
		iphy->sas_phy.oob_mode = SAS_OOB_MODE;
		iphy->sas_phy.frame_rcvd_size = माप(काष्ठा sas_identअगरy_frame);

		/* Copy the attached SAS address from the IAF */
		स_नकल(iphy->sas_phy.attached_sas_addr,
		       iphy->frame_rcvd.iaf.sas_addr, SAS_ADDR_SIZE);
	पूर्ण अन्यथा अणु
		dev_err(&isci_host->pdev->dev, "%s: unknown target\n", __func__);
		success = false;
	पूर्ण

	iphy->sas_phy.phy->negotiated_linkrate = sci_phy_linkrate(iphy);

	spin_unlock_irqrestore(&iphy->sas_phy.frame_rcvd_lock, flags);

	/* Notअगरy libsas that we have an address frame, अगर indeed
	 * we've found an SSP, SMP, or STP target */
	अगर (success)
		sas_notअगरy_port_event(&iphy->sas_phy,
				      PORTE_BYTES_DMAED, GFP_ATOMIC);
पूर्ण


/**
 * isci_port_link_करोwn() - This function is called by the sci core when a link
 *    becomes inactive.
 * @isci_host: This parameter specअगरies the isci host object.
 * @isci_phy: This parameter specअगरies the isci phy with the active link.
 * @isci_port: This parameter specअगरies the isci port with the active link.
 *
 */
अटल व्योम isci_port_link_करोwn(काष्ठा isci_host *isci_host,
				काष्ठा isci_phy *isci_phy,
				काष्ठा isci_port *isci_port)
अणु
	काष्ठा isci_remote_device *isci_device;

	dev_dbg(&isci_host->pdev->dev,
		"%s: isci_port = %p\n", __func__, isci_port);

	अगर (isci_port) अणु

		/* check to see अगर this is the last phy on this port. */
		अगर (isci_phy->sas_phy.port &&
		    isci_phy->sas_phy.port->num_phys == 1) अणु
			/* change the state क्रम all devices on this port.  The
			* next task sent to this device will be वापसed as
			* SAS_TASK_UNDELIVERED, and the scsi mid layer will
			* हटाओ the target
			*/
			list_क्रम_each_entry(isci_device,
					    &isci_port->remote_dev_list,
					    node) अणु
				dev_dbg(&isci_host->pdev->dev,
					"%s: isci_device = %p\n",
					__func__, isci_device);
				set_bit(IDEV_GONE, &isci_device->flags);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Notअगरy libsas of the borken link, this will trigger calls to our
	 * isci_port_deक्रमmed and isci_dev_gone functions.
	 */
	sas_phy_disconnected(&isci_phy->sas_phy);
	sas_notअगरy_phy_event(&isci_phy->sas_phy,
			     PHYE_LOSS_OF_SIGNAL, GFP_ATOMIC);

	dev_dbg(&isci_host->pdev->dev,
		"%s: isci_port = %p - Done\n", __func__, isci_port);
पूर्ण

अटल bool is_port_पढ़ोy_state(क्रमागत sci_port_states state)
अणु
	चयन (state) अणु
	हाल SCI_PORT_READY:
	हाल SCI_PORT_SUB_WAITING:
	हाल SCI_PORT_SUB_OPERATIONAL:
	हाल SCI_PORT_SUB_CONFIGURING:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* flag dummy rnc hanling when निकासing a पढ़ोy state */
अटल व्योम port_state_machine_change(काष्ठा isci_port *iport,
				      क्रमागत sci_port_states state)
अणु
	काष्ठा sci_base_state_machine *sm = &iport->sm;
	क्रमागत sci_port_states old_state = sm->current_state_id;

	अगर (is_port_पढ़ोy_state(old_state) && !is_port_पढ़ोy_state(state))
		iport->पढ़ोy_निकास = true;

	sci_change_state(sm, state);
	iport->पढ़ोy_निकास = false;
पूर्ण

/**
 * isci_port_hard_reset_complete() - This function is called by the sci core
 *    when the hard reset complete notअगरication has been received.
 * @isci_port: This parameter specअगरies the sci port with the active link.
 * @completion_status: This parameter specअगरies the core status क्रम the reset
 *    process.
 *
 */
अटल व्योम isci_port_hard_reset_complete(काष्ठा isci_port *isci_port,
					  क्रमागत sci_status completion_status)
अणु
	काष्ठा isci_host *ihost = isci_port->owning_controller;

	dev_dbg(&ihost->pdev->dev,
		"%s: isci_port = %p, completion_status=%x\n",
		     __func__, isci_port, completion_status);

	/* Save the status of the hard reset from the port. */
	isci_port->hard_reset_status = completion_status;

	अगर (completion_status != SCI_SUCCESS) अणु

		/* The reset failed.  The port state is now SCI_PORT_FAILED. */
		अगर (isci_port->active_phy_mask == 0) अणु
			पूर्णांक phy_idx = isci_port->last_active_phy;
			काष्ठा isci_phy *iphy = &ihost->phys[phy_idx];

			/* Generate the link करोwn now to the host, since it
			 * was पूर्णांकercepted by the hard reset state machine when
			 * it really happened.
			 */
			isci_port_link_करोwn(ihost, iphy, isci_port);
		पूर्ण
		/* Advance the port state so that link state changes will be
		 * noticed.
		 */
		port_state_machine_change(isci_port, SCI_PORT_SUB_WAITING);

	पूर्ण
	clear_bit(IPORT_RESET_PENDING, &isci_port->state);
	wake_up(&ihost->eventq);

पूर्ण

/* This method will वापस a true value अगर the specअगरied phy can be asचिन्हित to
 * this port The following is a list of phys क्रम each port that are allowed: -
 * Port 0 - 3 2 1 0 - Port 1 -     1 - Port 2 - 3 2 - Port 3 - 3 This method
 * करोesn't preclude all configurations.  It merely ensures that a phy is part
 * of the allowable set of phy identअगरiers क्रम that port.  For example, one
 * could assign phy 3 to port 0 and no other phys.  Please refer to
 * sci_port_is_phy_mask_valid() क्रम inक्रमmation regarding whether the
 * phy_mask क्रम a port can be supported. bool true अगर this is a valid phy
 * assignment क्रम the port false अगर this is not a valid phy assignment क्रम the
 * port
 */
bool sci_port_is_valid_phy_assignment(काष्ठा isci_port *iport, u32 phy_index)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;
	काष्ठा sci_user_parameters *user = &ihost->user_parameters;

	/* Initialize to invalid value. */
	u32 existing_phy_index = SCI_MAX_PHYS;
	u32 index;

	अगर ((iport->physical_port_index == 1) && (phy_index != 1))
		वापस false;

	अगर (iport->physical_port_index == 3 && phy_index != 3)
		वापस false;

	अगर (iport->physical_port_index == 2 &&
	    (phy_index == 0 || phy_index == 1))
		वापस false;

	क्रम (index = 0; index < SCI_MAX_PHYS; index++)
		अगर (iport->phy_table[index] && index != phy_index)
			existing_phy_index = index;

	/* Ensure that all of the phys in the port are capable of
	 * operating at the same maximum link rate.
	 */
	अगर (existing_phy_index < SCI_MAX_PHYS &&
	    user->phys[phy_index].max_speed_generation !=
	    user->phys[existing_phy_index].max_speed_generation)
		वापस false;

	वापस true;
पूर्ण

/**
 * sci_port_is_phy_mask_valid()
 * @iport: This is the port object क्रम which to determine अगर the phy mask
 *    can be supported.
 * @phy_mask: Phy mask beदीर्घing to this port
 *
 * This method will वापस a true value अगर the port's phy mask can be supported
 * by the SCU. The following is a list of valid PHY mask configurations क्रम
 * each port: - Port 0 - [[3  2] 1] 0 - Port 1 -        [1] - Port 2 - [[3] 2]
 * - Port 3 -  [3] This method वापसs a boolean indication specअगरying अगर the
 * phy mask can be supported. true अगर this is a valid phy assignment क्रम the
 * port false अगर this is not a valid phy assignment क्रम the port
 */
अटल bool sci_port_is_phy_mask_valid(
	काष्ठा isci_port *iport,
	u32 phy_mask)
अणु
	अगर (iport->physical_port_index == 0) अणु
		अगर (((phy_mask & 0x0F) == 0x0F)
		    || ((phy_mask & 0x03) == 0x03)
		    || ((phy_mask & 0x01) == 0x01)
		    || (phy_mask == 0))
			वापस true;
	पूर्ण अन्यथा अगर (iport->physical_port_index == 1) अणु
		अगर (((phy_mask & 0x02) == 0x02)
		    || (phy_mask == 0))
			वापस true;
	पूर्ण अन्यथा अगर (iport->physical_port_index == 2) अणु
		अगर (((phy_mask & 0x0C) == 0x0C)
		    || ((phy_mask & 0x04) == 0x04)
		    || (phy_mask == 0))
			वापस true;
	पूर्ण अन्यथा अगर (iport->physical_port_index == 3) अणु
		अगर (((phy_mask & 0x08) == 0x08)
		    || (phy_mask == 0))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * This method retrieves a currently active (i.e. connected) phy contained in
 * the port.  Currently, the lowest order phy that is connected is वापसed.
 * This method वापसs a poपूर्णांकer to a SCIS_SDS_PHY object. शून्य This value is
 * वापसed अगर there are no currently active (i.e. connected to a remote end
 * poपूर्णांक) phys contained in the port. All other values specअगरy a काष्ठा sci_phy
 * object that is active in the port.
 */
अटल काष्ठा isci_phy *sci_port_get_a_connected_phy(काष्ठा isci_port *iport)
अणु
	u32 index;
	काष्ठा isci_phy *iphy;

	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		/* Ensure that the phy is both part of the port and currently
		 * connected to the remote end-poपूर्णांक.
		 */
		iphy = iport->phy_table[index];
		अगर (iphy && sci_port_active_phy(iport, iphy))
			वापस iphy;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत sci_status sci_port_set_phy(काष्ठा isci_port *iport, काष्ठा isci_phy *iphy)
अणु
	/* Check to see अगर we can add this phy to a port
	 * that means that the phy is not part of a port and that the port करोes
	 * not alपढ़ोy have a phy assinged to the phy index.
	 */
	अगर (!iport->phy_table[iphy->phy_index] &&
	    !phy_get_non_dummy_port(iphy) &&
	    sci_port_is_valid_phy_assignment(iport, iphy->phy_index)) अणु
		/* Phy is being added in the stopped state so we are in MPC mode
		 * make logical port index = physical port index
		 */
		iport->logical_port_index = iport->physical_port_index;
		iport->phy_table[iphy->phy_index] = iphy;
		sci_phy_set_port(iphy, iport);

		वापस SCI_SUCCESS;
	पूर्ण

	वापस SCI_FAILURE;
पूर्ण

अटल क्रमागत sci_status sci_port_clear_phy(काष्ठा isci_port *iport, काष्ठा isci_phy *iphy)
अणु
	/* Make sure that this phy is part of this port */
	अगर (iport->phy_table[iphy->phy_index] == iphy &&
	    phy_get_non_dummy_port(iphy) == iport) अणु
		काष्ठा isci_host *ihost = iport->owning_controller;

		/* Yep it is asचिन्हित to this port so हटाओ it */
		sci_phy_set_port(iphy, &ihost->ports[SCI_MAX_PORTS]);
		iport->phy_table[iphy->phy_index] = शून्य;
		वापस SCI_SUCCESS;
	पूर्ण

	वापस SCI_FAILURE;
पूर्ण

व्योम sci_port_get_sas_address(काष्ठा isci_port *iport, काष्ठा sci_sas_address *sas)
अणु
	u32 index;

	sas->high = 0;
	sas->low  = 0;
	क्रम (index = 0; index < SCI_MAX_PHYS; index++)
		अगर (iport->phy_table[index])
			sci_phy_get_sas_address(iport->phy_table[index], sas);
पूर्ण

व्योम sci_port_get_attached_sas_address(काष्ठा isci_port *iport, काष्ठा sci_sas_address *sas)
अणु
	काष्ठा isci_phy *iphy;

	/*
	 * Ensure that the phy is both part of the port and currently
	 * connected to the remote end-poपूर्णांक.
	 */
	iphy = sci_port_get_a_connected_phy(iport);
	अगर (iphy) अणु
		अगर (iphy->protocol != SAS_PROTOCOL_SATA) अणु
			sci_phy_get_attached_sas_address(iphy, sas);
		पूर्ण अन्यथा अणु
			sci_phy_get_sas_address(iphy, sas);
			sas->low += iphy->phy_index;
		पूर्ण
	पूर्ण अन्यथा अणु
		sas->high = 0;
		sas->low  = 0;
	पूर्ण
पूर्ण

/**
 * sci_port_स्थिरruct_dummy_rnc() - create dummy rnc क्रम si workaround
 *
 * @iport: logical port on which we need to create the remote node context
 * @rni: remote node index क्रम this remote node context.
 *
 * This routine will स्थिरruct a dummy remote node context data काष्ठाure
 * This काष्ठाure will be posted to the hardware to work around a scheduler
 * error in the hardware.
 */
अटल व्योम sci_port_स्थिरruct_dummy_rnc(काष्ठा isci_port *iport, u16 rni)
अणु
	जोड़ scu_remote_node_context *rnc;

	rnc = &iport->owning_controller->remote_node_context_table[rni];

	स_रखो(rnc, 0, माप(जोड़ scu_remote_node_context));

	rnc->ssp.remote_sas_address_hi = 0;
	rnc->ssp.remote_sas_address_lo = 0;

	rnc->ssp.remote_node_index = rni;
	rnc->ssp.remote_node_port_width = 1;
	rnc->ssp.logical_port_index = iport->physical_port_index;

	rnc->ssp.nexus_loss_समयr_enable = false;
	rnc->ssp.check_bit = false;
	rnc->ssp.is_valid = true;
	rnc->ssp.is_remote_node_context = true;
	rnc->ssp.function_number = 0;
	rnc->ssp.arbitration_रुको_समय = 0;
पूर्ण

/*
 * स्थिरruct a dummy task context data काष्ठाure.  This
 * काष्ठाure will be posted to the hardwre to work around a scheduler error
 * in the hardware.
 */
अटल व्योम sci_port_स्थिरruct_dummy_task(काष्ठा isci_port *iport, u16 tag)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;
	काष्ठा scu_task_context *task_context;

	task_context = &ihost->task_context_table[ISCI_TAG_TCI(tag)];
	स_रखो(task_context, 0, माप(काष्ठा scu_task_context));

	task_context->initiator_request = 1;
	task_context->connection_rate = 1;
	task_context->logical_port_index = iport->physical_port_index;
	task_context->protocol_type = SCU_TASK_CONTEXT_PROTOCOL_SSP;
	task_context->task_index = ISCI_TAG_TCI(tag);
	task_context->valid = SCU_TASK_CONTEXT_VALID;
	task_context->context_type = SCU_TASK_CONTEXT_TYPE;
	task_context->remote_node_index = iport->reserved_rni;
	task_context->करो_not_dma_ssp_good_response = 1;
	task_context->task_phase = 0x01;
पूर्ण

अटल व्योम sci_port_destroy_dummy_resources(काष्ठा isci_port *iport)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;

	अगर (iport->reserved_tag != SCI_CONTROLLER_INVALID_IO_TAG)
		isci_मुक्त_tag(ihost, iport->reserved_tag);

	अगर (iport->reserved_rni != SCU_DUMMY_INDEX)
		sci_remote_node_table_release_remote_node_index(&ihost->available_remote_nodes,
								     1, iport->reserved_rni);

	iport->reserved_rni = SCU_DUMMY_INDEX;
	iport->reserved_tag = SCI_CONTROLLER_INVALID_IO_TAG;
पूर्ण

व्योम sci_port_setup_transports(काष्ठा isci_port *iport, u32 device_id)
अणु
	u8 index;

	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		अगर (iport->active_phy_mask & (1 << index))
			sci_phy_setup_transport(iport->phy_table[index], device_id);
	पूर्ण
पूर्ण

अटल व्योम sci_port_resume_phy(काष्ठा isci_port *iport, काष्ठा isci_phy *iphy)
अणु
	sci_phy_resume(iphy);
	iport->enabled_phy_mask |= 1 << iphy->phy_index;
पूर्ण

अटल व्योम sci_port_activate_phy(काष्ठा isci_port *iport,
				  काष्ठा isci_phy *iphy,
				  u8 flags)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;

	अगर (iphy->protocol != SAS_PROTOCOL_SATA && (flags & PF_RESUME))
		sci_phy_resume(iphy);

	iport->active_phy_mask |= 1 << iphy->phy_index;

	sci_controller_clear_invalid_phy(ihost, iphy);

	अगर (flags & PF_NOTIFY)
		isci_port_link_up(ihost, iport, iphy);
पूर्ण

व्योम sci_port_deactivate_phy(काष्ठा isci_port *iport, काष्ठा isci_phy *iphy,
			     bool करो_notअगरy_user)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;

	iport->active_phy_mask &= ~(1 << iphy->phy_index);
	iport->enabled_phy_mask &= ~(1 << iphy->phy_index);
	अगर (!iport->active_phy_mask)
		iport->last_active_phy = iphy->phy_index;

	iphy->max_negotiated_speed = SAS_LINK_RATE_UNKNOWN;

	/* Re-assign the phy back to the LP as अगर it were a narrow port क्रम APC
	 * mode. For MPC mode, the phy will reमुख्य in the port.
	 */
	अगर (iport->owning_controller->oem_parameters.controller.mode_type ==
		SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE)
		ग_लिखोl(iphy->phy_index,
			&iport->port_pe_configuration_रेजिस्टर[iphy->phy_index]);

	अगर (करो_notअगरy_user == true)
		isci_port_link_करोwn(ihost, iphy, iport);
पूर्ण

अटल व्योम sci_port_invalid_link_up(काष्ठा isci_port *iport, काष्ठा isci_phy *iphy)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;

	/*
	 * Check to see अगर we have alreay reported this link as bad and अगर
	 * not go ahead and tell the SCI_USER that we have discovered an
	 * invalid link.
	 */
	अगर ((ihost->invalid_phy_mask & (1 << iphy->phy_index)) == 0) अणु
		ihost->invalid_phy_mask |= 1 << iphy->phy_index;
		dev_warn(&ihost->pdev->dev, "Invalid link up!\n");
	पूर्ण
पूर्ण

/**
 * sci_port_general_link_up_handler - phy can be asचिन्हित to port?
 * @iport: sci_port object क्रम which has a phy that has gone link up.
 * @iphy: This is the काष्ठा isci_phy object that has gone link up.
 * @flags: PF_RESUME, PF_NOTIFY to sci_port_activate_phy
 *
 * Determine अगर this phy can be asचिन्हित to this port . If the phy is
 * not a valid PHY क्रम this port then the function will notअगरy the user.
 * A PHY can only be part of a port अगर it's attached SAS ADDRESS is the
 * same as all other PHYs in the same port.
 */
अटल व्योम sci_port_general_link_up_handler(काष्ठा isci_port *iport,
					     काष्ठा isci_phy *iphy,
					     u8 flags)
अणु
	काष्ठा sci_sas_address port_sas_address;
	काष्ठा sci_sas_address phy_sas_address;

	sci_port_get_attached_sas_address(iport, &port_sas_address);
	sci_phy_get_attached_sas_address(iphy, &phy_sas_address);

	/* If the SAS address of the new phy matches the SAS address of
	 * other phys in the port OR this is the first phy in the port,
	 * then activate the phy and allow it to be used क्रम operations
	 * in this port.
	 */
	अगर ((phy_sas_address.high == port_sas_address.high &&
	     phy_sas_address.low  == port_sas_address.low) ||
	    iport->active_phy_mask == 0) अणु
		काष्ठा sci_base_state_machine *sm = &iport->sm;

		sci_port_activate_phy(iport, iphy, flags);
		अगर (sm->current_state_id == SCI_PORT_RESETTING)
			port_state_machine_change(iport, SCI_PORT_READY);
	पूर्ण अन्यथा
		sci_port_invalid_link_up(iport, iphy);
पूर्ण



/**
 * sci_port_is_wide()
 * This method वापसs false अगर the port only has a single phy object asचिन्हित.
 *     If there are no phys or more than one phy then the method will वापस
 *    true.
 * @iport: The port क्रम which the wide port condition is to be checked.
 *
 * bool true Is वापसed अगर this is a wide ported port. false Is वापसed अगर
 * this is a narrow port.
 */
अटल bool sci_port_is_wide(काष्ठा isci_port *iport)
अणु
	u32 index;
	u32 phy_count = 0;

	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		अगर (iport->phy_table[index] != शून्य) अणु
			phy_count++;
		पूर्ण
	पूर्ण

	वापस phy_count != 1;
पूर्ण

/**
 * sci_port_link_detected()
 * This method is called by the PHY object when the link is detected. अगर the
 *    port wants the PHY to जारी on to the link up state then the port
 *    layer must वापस true.  If the port object वापसs false the phy object
 *    must halt its attempt to go link up.
 * @iport: The port associated with the phy object.
 * @iphy: The phy object that is trying to go link up.
 *
 * true अगर the phy object can जारी to the link up condition. true Is
 * वापसed अगर this phy can जारी to the पढ़ोy state. false Is वापसed अगर
 * can not जारी on to the पढ़ोy state. This notअगरication is in place क्रम
 * wide ports and direct attached phys.  Since there are no wide ported SATA
 * devices this could become an invalid port configuration.
 */
bool sci_port_link_detected(काष्ठा isci_port *iport, काष्ठा isci_phy *iphy)
अणु
	अगर ((iport->logical_port_index != SCIC_SDS_DUMMY_PORT) &&
	    (iphy->protocol == SAS_PROTOCOL_SATA)) अणु
		अगर (sci_port_is_wide(iport)) अणु
			sci_port_invalid_link_up(iport, iphy);
			वापस false;
		पूर्ण अन्यथा अणु
			काष्ठा isci_host *ihost = iport->owning_controller;
			काष्ठा isci_port *dst_port = &(ihost->ports[iphy->phy_index]);
			ग_लिखोl(iphy->phy_index,
			       &dst_port->port_pe_configuration_रेजिस्टर[iphy->phy_index]);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम port_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा sci_समयr *पंचांगr = from_समयr(पंचांगr, t, समयr);
	काष्ठा isci_port *iport = container_of(पंचांगr, typeof(*iport), समयr);
	काष्ठा isci_host *ihost = iport->owning_controller;
	अचिन्हित दीर्घ flags;
	u32 current_state;

	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (पंचांगr->cancel)
		जाओ करोne;

	current_state = iport->sm.current_state_id;

	अगर (current_state == SCI_PORT_RESETTING) अणु
		/* अगर the port is still in the resetting state then the समयout
		 * fired beक्रमe the reset completed.
		 */
		port_state_machine_change(iport, SCI_PORT_FAILED);
	पूर्ण अन्यथा अगर (current_state == SCI_PORT_STOPPED) अणु
		/* अगर the port is stopped then the start request failed In this
		 * हाल stay in the stopped state.
		 */
		dev_err(sciport_to_dev(iport),
			"%s: SCIC Port 0x%p failed to stop before timeout.\n",
			__func__,
			iport);
	पूर्ण अन्यथा अगर (current_state == SCI_PORT_STOPPING) अणु
		dev_dbg(sciport_to_dev(iport),
			"%s: port%d: stop complete timeout\n",
			__func__, iport->physical_port_index);
	पूर्ण अन्यथा अणु
		/* The port is in the पढ़ोy state and we have a समयr
		 * reporting a समयout this should not happen.
		 */
		dev_err(sciport_to_dev(iport),
			"%s: SCIC Port 0x%p is processing a timeout operation "
			"in state %d.\n", __func__, iport, current_state);
	पूर्ण

करोne:
	spin_unlock_irqrestore(&ihost->scic_lock, flags);
पूर्ण

/* --------------------------------------------------------------------------- */

/*
 * This function updates the hardwares VIIT entry क्रम this port.
 */
अटल व्योम sci_port_update_viit_entry(काष्ठा isci_port *iport)
अणु
	काष्ठा sci_sas_address sas_address;

	sci_port_get_sas_address(iport, &sas_address);

	ग_लिखोl(sas_address.high,
		&iport->viit_रेजिस्टरs->initiator_sas_address_hi);
	ग_लिखोl(sas_address.low,
		&iport->viit_रेजिस्टरs->initiator_sas_address_lo);

	/* This value get cleared just in हाल its not alपढ़ोy cleared */
	ग_लिखोl(0, &iport->viit_रेजिस्टरs->reserved);

	/* We are required to update the status रेजिस्टर last */
	ग_लिखोl(SCU_VIIT_ENTRY_ID_VIIT |
	       SCU_VIIT_IPPT_INITIATOR |
	       ((1 << iport->physical_port_index) << SCU_VIIT_ENTRY_LPVIE_SHIFT) |
	       SCU_VIIT_STATUS_ALL_VALID,
	       &iport->viit_रेजिस्टरs->status);
पूर्ण

क्रमागत sas_linkrate sci_port_get_max_allowed_speed(काष्ठा isci_port *iport)
अणु
	u16 index;
	काष्ठा isci_phy *iphy;
	क्रमागत sas_linkrate max_allowed_speed = SAS_LINK_RATE_6_0_GBPS;

	/*
	 * Loop through all of the phys in this port and find the phy with the
	 * lowest maximum link rate. */
	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		iphy = iport->phy_table[index];
		अगर (iphy && sci_port_active_phy(iport, iphy) &&
		    iphy->max_negotiated_speed < max_allowed_speed)
			max_allowed_speed = iphy->max_negotiated_speed;
	पूर्ण

	वापस max_allowed_speed;
पूर्ण

अटल व्योम sci_port_suspend_port_task_scheduler(काष्ठा isci_port *iport)
अणु
	u32 pts_control_value;

	pts_control_value = पढ़ोl(&iport->port_task_scheduler_रेजिस्टरs->control);
	pts_control_value |= SCU_PTSxCR_GEN_BIT(SUSPEND);
	ग_लिखोl(pts_control_value, &iport->port_task_scheduler_रेजिस्टरs->control);
पूर्ण

/**
 * sci_port_post_dummy_request() - post dummy/workaround request
 * @iport: port to post task
 *
 * Prevent the hardware scheduler from posting new requests to the front
 * of the scheduler queue causing a starvation problem क्रम currently
 * ongoing requests.
 *
 */
अटल व्योम sci_port_post_dummy_request(काष्ठा isci_port *iport)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;
	u16 tag = iport->reserved_tag;
	काष्ठा scu_task_context *tc;
	u32 command;

	tc = &ihost->task_context_table[ISCI_TAG_TCI(tag)];
	tc->पात = 0;

	command = SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC |
		  iport->physical_port_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT |
		  ISCI_TAG_TCI(tag);

	sci_controller_post_request(ihost, command);
पूर्ण

/**
 * sci_port_पात_dummy_request()
 * This routine will पात the dummy request.  This will allow the hardware to
 * घातer करोwn parts of the silicon to save घातer.
 *
 * @iport: The port on which the task must be पातed.
 *
 */
अटल व्योम sci_port_पात_dummy_request(काष्ठा isci_port *iport)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;
	u16 tag = iport->reserved_tag;
	काष्ठा scu_task_context *tc;
	u32 command;

	tc = &ihost->task_context_table[ISCI_TAG_TCI(tag)];
	tc->पात = 1;

	command = SCU_CONTEXT_COMMAND_REQUEST_POST_TC_ABORT |
		  iport->physical_port_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT |
		  ISCI_TAG_TCI(tag);

	sci_controller_post_request(ihost, command);
पूर्ण

/**
 * sci_port_resume_port_task_scheduler()
 * @iport: This is the काष्ठा isci_port object to resume.
 *
 * This method will resume the port task scheduler क्रम this port object. none
 */
अटल व्योम
sci_port_resume_port_task_scheduler(काष्ठा isci_port *iport)
अणु
	u32 pts_control_value;

	pts_control_value = पढ़ोl(&iport->port_task_scheduler_रेजिस्टरs->control);
	pts_control_value &= ~SCU_PTSxCR_GEN_BIT(SUSPEND);
	ग_लिखोl(pts_control_value, &iport->port_task_scheduler_रेजिस्टरs->control);
पूर्ण

अटल व्योम sci_port_पढ़ोy_substate_रुकोing_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);

	sci_port_suspend_port_task_scheduler(iport);

	iport->not_पढ़ोy_reason = SCIC_PORT_NOT_READY_NO_ACTIVE_PHYS;

	अगर (iport->active_phy_mask != 0) अणु
		/* At least one of the phys on the port is पढ़ोy */
		port_state_machine_change(iport,
					  SCI_PORT_SUB_OPERATIONAL);
	पूर्ण
पूर्ण

अटल व्योम scic_sds_port_पढ़ोy_substate_रुकोing_निकास(
					काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);
	sci_port_resume_port_task_scheduler(iport);
पूर्ण

अटल व्योम sci_port_पढ़ोy_substate_operational_enter(काष्ठा sci_base_state_machine *sm)
अणु
	u32 index;
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);
	काष्ठा isci_host *ihost = iport->owning_controller;

	dev_dbg(&ihost->pdev->dev, "%s: port%d ready\n",
		__func__, iport->physical_port_index);

	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		अगर (iport->phy_table[index]) अणु
			ग_लिखोl(iport->physical_port_index,
				&iport->port_pe_configuration_रेजिस्टर[
					iport->phy_table[index]->phy_index]);
			अगर (((iport->active_phy_mask^iport->enabled_phy_mask) & (1 << index)) != 0)
				sci_port_resume_phy(iport, iport->phy_table[index]);
		पूर्ण
	पूर्ण

	sci_port_update_viit_entry(iport);

	/*
	 * Post the dummy task क्रम the port so the hardware can schedule
	 * io correctly
	 */
	sci_port_post_dummy_request(iport);
पूर्ण

अटल व्योम sci_port_invalidate_dummy_remote_node(काष्ठा isci_port *iport)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;
	u8 phys_index = iport->physical_port_index;
	जोड़ scu_remote_node_context *rnc;
	u16 rni = iport->reserved_rni;
	u32 command;

	rnc = &ihost->remote_node_context_table[rni];

	rnc->ssp.is_valid = false;

	/* ensure the preceding tc पात request has reached the
	 * controller and give it ample समय to act beक्रमe posting the rnc
	 * invalidate
	 */
	पढ़ोl(&ihost->smu_रेजिस्टरs->पूर्णांकerrupt_status); /* flush */
	udelay(10);

	command = SCU_CONTEXT_COMMAND_POST_RNC_INVALIDATE |
		  phys_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT | rni;

	sci_controller_post_request(ihost, command);
पूर्ण

/**
 * sci_port_पढ़ोy_substate_operational_निकास()
 * @sm: This is the object which is cast to a काष्ठा isci_port object.
 *
 * This method will perक्रमm the actions required by the काष्ठा isci_port on
 * निकासing the SCI_PORT_SUB_OPERATIONAL. This function reports
 * the port not पढ़ोy and suspends the port task scheduler. none
 */
अटल व्योम sci_port_पढ़ोy_substate_operational_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);
	काष्ठा isci_host *ihost = iport->owning_controller;

	/*
	 * Kill the dummy task क्रम this port अगर it has not yet posted
	 * the hardware will treat this as a NOP and just वापस पात
	 * complete.
	 */
	sci_port_पात_dummy_request(iport);

	dev_dbg(&ihost->pdev->dev, "%s: port%d !ready\n",
		__func__, iport->physical_port_index);

	अगर (iport->पढ़ोy_निकास)
		sci_port_invalidate_dummy_remote_node(iport);
पूर्ण

अटल व्योम sci_port_पढ़ोy_substate_configuring_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);
	काष्ठा isci_host *ihost = iport->owning_controller;

	अगर (iport->active_phy_mask == 0) अणु
		dev_dbg(&ihost->pdev->dev, "%s: port%d !ready\n",
			__func__, iport->physical_port_index);

		port_state_machine_change(iport, SCI_PORT_SUB_WAITING);
	पूर्ण अन्यथा
		port_state_machine_change(iport, SCI_PORT_SUB_OPERATIONAL);
पूर्ण

क्रमागत sci_status sci_port_start(काष्ठा isci_port *iport)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;
	क्रमागत sci_status status = SCI_SUCCESS;
	क्रमागत sci_port_states state;
	u32 phy_mask;

	state = iport->sm.current_state_id;
	अगर (state != SCI_PORT_STOPPED) अणु
		dev_warn(sciport_to_dev(iport), "%s: in wrong state: %s\n",
			 __func__, port_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	अगर (iport->asचिन्हित_device_count > 0) अणु
		/* TODO This is a start failure operation because
		 * there are still devices asचिन्हित to this port.
		 * There must be no devices asचिन्हित to a port on a
		 * start operation.
		 */
		वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
	पूर्ण

	अगर (iport->reserved_rni == SCU_DUMMY_INDEX) अणु
		u16 rni = sci_remote_node_table_allocate_remote_node(
				&ihost->available_remote_nodes, 1);

		अगर (rni != SCU_DUMMY_INDEX)
			sci_port_स्थिरruct_dummy_rnc(iport, rni);
		अन्यथा
			status = SCI_FAILURE_INSUFFICIENT_RESOURCES;
		iport->reserved_rni = rni;
	पूर्ण

	अगर (iport->reserved_tag == SCI_CONTROLLER_INVALID_IO_TAG) अणु
		u16 tag;

		tag = isci_alloc_tag(ihost);
		अगर (tag == SCI_CONTROLLER_INVALID_IO_TAG)
			status = SCI_FAILURE_INSUFFICIENT_RESOURCES;
		अन्यथा
			sci_port_स्थिरruct_dummy_task(iport, tag);
		iport->reserved_tag = tag;
	पूर्ण

	अगर (status == SCI_SUCCESS) अणु
		phy_mask = sci_port_get_phys(iport);

		/*
		 * There are one or more phys asचिन्हित to this port.  Make sure
		 * the port's phy mask is in fact legal and supported by the
		 * silicon.
		 */
		अगर (sci_port_is_phy_mask_valid(iport, phy_mask) == true) अणु
			port_state_machine_change(iport,
						  SCI_PORT_READY);

			वापस SCI_SUCCESS;
		पूर्ण
		status = SCI_FAILURE;
	पूर्ण

	अगर (status != SCI_SUCCESS)
		sci_port_destroy_dummy_resources(iport);

	वापस status;
पूर्ण

क्रमागत sci_status sci_port_stop(काष्ठा isci_port *iport)
अणु
	क्रमागत sci_port_states state;

	state = iport->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_PORT_STOPPED:
		वापस SCI_SUCCESS;
	हाल SCI_PORT_SUB_WAITING:
	हाल SCI_PORT_SUB_OPERATIONAL:
	हाल SCI_PORT_SUB_CONFIGURING:
	हाल SCI_PORT_RESETTING:
		port_state_machine_change(iport,
					  SCI_PORT_STOPPING);
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(sciport_to_dev(iport), "%s: in wrong state: %s\n",
			 __func__, port_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

अटल क्रमागत sci_status sci_port_hard_reset(काष्ठा isci_port *iport, u32 समयout)
अणु
	क्रमागत sci_status status = SCI_FAILURE_INVALID_PHY;
	काष्ठा isci_phy *iphy = शून्य;
	क्रमागत sci_port_states state;
	u32 phy_index;

	state = iport->sm.current_state_id;
	अगर (state != SCI_PORT_SUB_OPERATIONAL) अणु
		dev_warn(sciport_to_dev(iport), "%s: in wrong state: %s\n",
			 __func__, port_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण

	/* Select a phy on which we can send the hard reset request. */
	क्रम (phy_index = 0; phy_index < SCI_MAX_PHYS && !iphy; phy_index++) अणु
		iphy = iport->phy_table[phy_index];
		अगर (iphy && !sci_port_active_phy(iport, iphy)) अणु
			/*
			 * We found a phy but it is not पढ़ोy select
			 * dअगरferent phy
			 */
			iphy = शून्य;
		पूर्ण
	पूर्ण

	/* If we have a phy then go ahead and start the reset procedure */
	अगर (!iphy)
		वापस status;
	status = sci_phy_reset(iphy);

	अगर (status != SCI_SUCCESS)
		वापस status;

	sci_mod_समयr(&iport->समयr, समयout);
	iport->not_पढ़ोy_reason = SCIC_PORT_NOT_READY_HARD_RESET_REQUESTED;

	port_state_machine_change(iport, SCI_PORT_RESETTING);
	वापस SCI_SUCCESS;
पूर्ण

/**
 * sci_port_add_phy()
 * @iport: This parameter specअगरies the port in which the phy will be added.
 * @iphy: This parameter is the phy which is to be added to the port.
 *
 * This method will add a PHY to the selected port. This method वापसs an
 * क्रमागत sci_status. SCI_SUCCESS the phy has been added to the port. Any other
 * status is a failure to add the phy to the port.
 */
क्रमागत sci_status sci_port_add_phy(काष्ठा isci_port *iport,
				      काष्ठा isci_phy *iphy)
अणु
	क्रमागत sci_status status;
	क्रमागत sci_port_states state;

	sci_port_bcn_enable(iport);

	state = iport->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_PORT_STOPPED: अणु
		काष्ठा sci_sas_address port_sas_address;

		/* Read the port asचिन्हित SAS Address अगर there is one */
		sci_port_get_sas_address(iport, &port_sas_address);

		अगर (port_sas_address.high != 0 && port_sas_address.low != 0) अणु
			काष्ठा sci_sas_address phy_sas_address;

			/* Make sure that the PHY SAS Address matches the SAS Address
			 * क्रम this port
			 */
			sci_phy_get_sas_address(iphy, &phy_sas_address);

			अगर (port_sas_address.high != phy_sas_address.high ||
			    port_sas_address.low  != phy_sas_address.low)
				वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
		पूर्ण
		वापस sci_port_set_phy(iport, iphy);
	पूर्ण
	हाल SCI_PORT_SUB_WAITING:
	हाल SCI_PORT_SUB_OPERATIONAL:
		status = sci_port_set_phy(iport, iphy);

		अगर (status != SCI_SUCCESS)
			वापस status;

		sci_port_general_link_up_handler(iport, iphy, PF_NOTIFY|PF_RESUME);
		iport->not_पढ़ोy_reason = SCIC_PORT_NOT_READY_RECONFIGURING;
		port_state_machine_change(iport, SCI_PORT_SUB_CONFIGURING);

		वापस status;
	हाल SCI_PORT_SUB_CONFIGURING:
		status = sci_port_set_phy(iport, iphy);

		अगर (status != SCI_SUCCESS)
			वापस status;
		sci_port_general_link_up_handler(iport, iphy, PF_NOTIFY);

		/* Re-enter the configuring state since this may be the last phy in
		 * the port.
		 */
		port_state_machine_change(iport,
					  SCI_PORT_SUB_CONFIGURING);
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(sciport_to_dev(iport), "%s: in wrong state: %s\n",
			 __func__, port_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

/**
 * sci_port_हटाओ_phy()
 * @iport: This parameter specअगरies the port in which the phy will be added.
 * @iphy: This parameter is the phy which is to be added to the port.
 *
 * This method will हटाओ the PHY from the selected PORT. This method वापसs
 * an क्रमागत sci_status. SCI_SUCCESS the phy has been हटाओd from the port. Any
 * other status is a failure to add the phy to the port.
 */
क्रमागत sci_status sci_port_हटाओ_phy(काष्ठा isci_port *iport,
					 काष्ठा isci_phy *iphy)
अणु
	क्रमागत sci_status status;
	क्रमागत sci_port_states state;

	state = iport->sm.current_state_id;

	चयन (state) अणु
	हाल SCI_PORT_STOPPED:
		वापस sci_port_clear_phy(iport, iphy);
	हाल SCI_PORT_SUB_OPERATIONAL:
		status = sci_port_clear_phy(iport, iphy);
		अगर (status != SCI_SUCCESS)
			वापस status;

		sci_port_deactivate_phy(iport, iphy, true);
		iport->not_पढ़ोy_reason = SCIC_PORT_NOT_READY_RECONFIGURING;
		port_state_machine_change(iport,
					  SCI_PORT_SUB_CONFIGURING);
		वापस SCI_SUCCESS;
	हाल SCI_PORT_SUB_CONFIGURING:
		status = sci_port_clear_phy(iport, iphy);

		अगर (status != SCI_SUCCESS)
			वापस status;
		sci_port_deactivate_phy(iport, iphy, true);

		/* Re-enter the configuring state since this may be the last phy in
		 * the port
		 */
		port_state_machine_change(iport,
					  SCI_PORT_SUB_CONFIGURING);
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(sciport_to_dev(iport), "%s: in wrong state: %s\n",
			 __func__, port_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_port_link_up(काष्ठा isci_port *iport,
				      काष्ठा isci_phy *iphy)
अणु
	क्रमागत sci_port_states state;

	state = iport->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_PORT_SUB_WAITING:
		/* Since this is the first phy going link up क्रम the port we
		 * can just enable it and जारी
		 */
		sci_port_activate_phy(iport, iphy, PF_NOTIFY|PF_RESUME);

		port_state_machine_change(iport,
					  SCI_PORT_SUB_OPERATIONAL);
		वापस SCI_SUCCESS;
	हाल SCI_PORT_SUB_OPERATIONAL:
		sci_port_general_link_up_handler(iport, iphy, PF_NOTIFY|PF_RESUME);
		वापस SCI_SUCCESS;
	हाल SCI_PORT_RESETTING:
		/* TODO We should  make  sure  that  the phy  that  has gone
		 * link up is the same one on which we sent the reset.  It is
		 * possible that the phy on which we sent  the reset is not the
		 * one that has  gone  link up  and we  want to make sure that
		 * phy being reset  comes  back.  Consider the हाल where a
		 * reset is sent but beक्रमe the hardware processes the reset it
		 * get a link up on  the  port because of a hot plug event.
		 * because  of  the reset request this phy will go link करोwn
		 * almost immediately.
		 */

		/* In the resetting state we करोn't notअगरy the user regarding
		 * link up and link करोwn notअगरications.
		 */
		sci_port_general_link_up_handler(iport, iphy, PF_RESUME);
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(sciport_to_dev(iport), "%s: in wrong state: %s\n",
			 __func__, port_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_port_link_करोwn(काष्ठा isci_port *iport,
					काष्ठा isci_phy *iphy)
अणु
	क्रमागत sci_port_states state;

	state = iport->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_PORT_SUB_OPERATIONAL:
		sci_port_deactivate_phy(iport, iphy, true);

		/* If there are no active phys left in the port, then
		 * transition the port to the WAITING state until such समय
		 * as a phy goes link up
		 */
		अगर (iport->active_phy_mask == 0)
			port_state_machine_change(iport,
						  SCI_PORT_SUB_WAITING);
		वापस SCI_SUCCESS;
	हाल SCI_PORT_RESETTING:
		/* In the resetting state we करोn't notअगरy the user regarding
		 * link up and link करोwn notअगरications. */
		sci_port_deactivate_phy(iport, iphy, false);
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(sciport_to_dev(iport), "%s: in wrong state: %s\n",
			 __func__, port_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_port_start_io(काष्ठा isci_port *iport,
				  काष्ठा isci_remote_device *idev,
				  काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_port_states state;

	state = iport->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_PORT_SUB_WAITING:
		वापस SCI_FAILURE_INVALID_STATE;
	हाल SCI_PORT_SUB_OPERATIONAL:
		iport->started_request_count++;
		वापस SCI_SUCCESS;
	शेष:
		dev_warn(sciport_to_dev(iport), "%s: in wrong state: %s\n",
			 __func__, port_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	पूर्ण
पूर्ण

क्रमागत sci_status sci_port_complete_io(काष्ठा isci_port *iport,
				     काष्ठा isci_remote_device *idev,
				     काष्ठा isci_request *ireq)
अणु
	क्रमागत sci_port_states state;

	state = iport->sm.current_state_id;
	चयन (state) अणु
	हाल SCI_PORT_STOPPED:
		dev_warn(sciport_to_dev(iport), "%s: in wrong state: %s\n",
			 __func__, port_state_name(state));
		वापस SCI_FAILURE_INVALID_STATE;
	हाल SCI_PORT_STOPPING:
		sci_port_decrement_request_count(iport);

		अगर (iport->started_request_count == 0)
			port_state_machine_change(iport,
						  SCI_PORT_STOPPED);
		अवरोध;
	हाल SCI_PORT_READY:
	हाल SCI_PORT_RESETTING:
	हाल SCI_PORT_FAILED:
	हाल SCI_PORT_SUB_WAITING:
	हाल SCI_PORT_SUB_OPERATIONAL:
		sci_port_decrement_request_count(iport);
		अवरोध;
	हाल SCI_PORT_SUB_CONFIGURING:
		sci_port_decrement_request_count(iport);
		अगर (iport->started_request_count == 0) अणु
			port_state_machine_change(iport,
						  SCI_PORT_SUB_OPERATIONAL);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस SCI_SUCCESS;
पूर्ण

अटल व्योम sci_port_enable_port_task_scheduler(काष्ठा isci_port *iport)
अणु
	u32 pts_control_value;

	 /* enable the port task scheduler in a suspended state */
	pts_control_value = पढ़ोl(&iport->port_task_scheduler_रेजिस्टरs->control);
	pts_control_value |= SCU_PTSxCR_GEN_BIT(ENABLE) | SCU_PTSxCR_GEN_BIT(SUSPEND);
	ग_लिखोl(pts_control_value, &iport->port_task_scheduler_रेजिस्टरs->control);
पूर्ण

अटल व्योम sci_port_disable_port_task_scheduler(काष्ठा isci_port *iport)
अणु
	u32 pts_control_value;

	pts_control_value = पढ़ोl(&iport->port_task_scheduler_रेजिस्टरs->control);
	pts_control_value &=
		~(SCU_PTSxCR_GEN_BIT(ENABLE) | SCU_PTSxCR_GEN_BIT(SUSPEND));
	ग_लिखोl(pts_control_value, &iport->port_task_scheduler_रेजिस्टरs->control);
पूर्ण

अटल व्योम sci_port_post_dummy_remote_node(काष्ठा isci_port *iport)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;
	u8 phys_index = iport->physical_port_index;
	जोड़ scu_remote_node_context *rnc;
	u16 rni = iport->reserved_rni;
	u32 command;

	rnc = &ihost->remote_node_context_table[rni];
	rnc->ssp.is_valid = true;

	command = SCU_CONTEXT_COMMAND_POST_RNC_32 |
		  phys_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT | rni;

	sci_controller_post_request(ihost, command);

	/* ensure hardware has seen the post rnc command and give it
	 * ample समय to act beक्रमe sending the suspend
	 */
	पढ़ोl(&ihost->smu_रेजिस्टरs->पूर्णांकerrupt_status); /* flush */
	udelay(10);

	command = SCU_CONTEXT_COMMAND_POST_RNC_SUSPEND_TX_RX |
		  phys_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT | rni;

	sci_controller_post_request(ihost, command);
पूर्ण

अटल व्योम sci_port_stopped_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);

	अगर (iport->sm.previous_state_id == SCI_PORT_STOPPING) अणु
		/*
		 * If we enter this state becasuse of a request to stop
		 * the port then we want to disable the hardwares port
		 * task scheduler. */
		sci_port_disable_port_task_scheduler(iport);
	पूर्ण
पूर्ण

अटल व्योम sci_port_stopped_state_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);

	/* Enable and suspend the port task scheduler */
	sci_port_enable_port_task_scheduler(iport);
पूर्ण

अटल व्योम sci_port_पढ़ोy_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);
	काष्ठा isci_host *ihost = iport->owning_controller;
	u32 prev_state;

	prev_state = iport->sm.previous_state_id;
	अगर (prev_state  == SCI_PORT_RESETTING)
		isci_port_hard_reset_complete(iport, SCI_SUCCESS);
	अन्यथा
		dev_dbg(&ihost->pdev->dev, "%s: port%d !ready\n",
			__func__, iport->physical_port_index);

	/* Post and suspend the dummy remote node context क्रम this port. */
	sci_port_post_dummy_remote_node(iport);

	/* Start the पढ़ोy substate machine */
	port_state_machine_change(iport,
				  SCI_PORT_SUB_WAITING);
पूर्ण

अटल व्योम sci_port_resetting_state_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);

	sci_del_समयr(&iport->समयr);
पूर्ण

अटल व्योम sci_port_stopping_state_निकास(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);

	sci_del_समयr(&iport->समयr);

	sci_port_destroy_dummy_resources(iport);
पूर्ण

अटल व्योम sci_port_failed_state_enter(काष्ठा sci_base_state_machine *sm)
अणु
	काष्ठा isci_port *iport = container_of(sm, typeof(*iport), sm);

	isci_port_hard_reset_complete(iport, SCI_FAILURE_TIMEOUT);
पूर्ण

व्योम sci_port_set_hang_detection_समयout(काष्ठा isci_port *iport, u32 समयout)
अणु
	पूर्णांक phy_index;
	u32 phy_mask = iport->active_phy_mask;

	अगर (समयout)
		++iport->hang_detect_users;
	अन्यथा अगर (iport->hang_detect_users > 1)
		--iport->hang_detect_users;
	अन्यथा
		iport->hang_detect_users = 0;

	अगर (समयout || (iport->hang_detect_users == 0)) अणु
		क्रम (phy_index = 0; phy_index < SCI_MAX_PHYS; phy_index++) अणु
			अगर ((phy_mask >> phy_index) & 1) अणु
				ग_लिखोl(समयout,
				       &iport->phy_table[phy_index]
					  ->link_layer_रेजिस्टरs
					  ->link_layer_hang_detection_समयout);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
/* --------------------------------------------------------------------------- */

अटल स्थिर काष्ठा sci_base_state sci_port_state_table[] = अणु
	[SCI_PORT_STOPPED] = अणु
		.enter_state = sci_port_stopped_state_enter,
		.निकास_state  = sci_port_stopped_state_निकास
	पूर्ण,
	[SCI_PORT_STOPPING] = अणु
		.निकास_state  = sci_port_stopping_state_निकास
	पूर्ण,
	[SCI_PORT_READY] = अणु
		.enter_state = sci_port_पढ़ोy_state_enter,
	पूर्ण,
	[SCI_PORT_SUB_WAITING] = अणु
		.enter_state = sci_port_पढ़ोy_substate_रुकोing_enter,
		.निकास_state  = scic_sds_port_पढ़ोy_substate_रुकोing_निकास,
	पूर्ण,
	[SCI_PORT_SUB_OPERATIONAL] = अणु
		.enter_state = sci_port_पढ़ोy_substate_operational_enter,
		.निकास_state  = sci_port_पढ़ोy_substate_operational_निकास
	पूर्ण,
	[SCI_PORT_SUB_CONFIGURING] = अणु
		.enter_state = sci_port_पढ़ोy_substate_configuring_enter
	पूर्ण,
	[SCI_PORT_RESETTING] = अणु
		.निकास_state  = sci_port_resetting_state_निकास
	पूर्ण,
	[SCI_PORT_FAILED] = अणु
		.enter_state = sci_port_failed_state_enter,
	पूर्ण
पूर्ण;

व्योम sci_port_स्थिरruct(काष्ठा isci_port *iport, u8 index,
			     काष्ठा isci_host *ihost)
अणु
	sci_init_sm(&iport->sm, sci_port_state_table, SCI_PORT_STOPPED);

	iport->logical_port_index  = SCIC_SDS_DUMMY_PORT;
	iport->physical_port_index = index;
	iport->active_phy_mask     = 0;
	iport->enabled_phy_mask    = 0;
	iport->last_active_phy     = 0;
	iport->पढ़ोy_निकास	   = false;

	iport->owning_controller = ihost;

	iport->started_request_count = 0;
	iport->asचिन्हित_device_count = 0;
	iport->hang_detect_users = 0;

	iport->reserved_rni = SCU_DUMMY_INDEX;
	iport->reserved_tag = SCI_CONTROLLER_INVALID_IO_TAG;

	sci_init_समयr(&iport->समयr, port_समयout);

	iport->port_task_scheduler_रेजिस्टरs = शून्य;

	क्रम (index = 0; index < SCI_MAX_PHYS; index++)
		iport->phy_table[index] = शून्य;
पूर्ण

व्योम sci_port_broadcast_change_received(काष्ठा isci_port *iport, काष्ठा isci_phy *iphy)
अणु
	काष्ठा isci_host *ihost = iport->owning_controller;

	/* notअगरy the user. */
	isci_port_bc_change_received(ihost, iport, iphy);
पूर्ण

अटल व्योम रुको_port_reset(काष्ठा isci_host *ihost, काष्ठा isci_port *iport)
अणु
	रुको_event(ihost->eventq, !test_bit(IPORT_RESET_PENDING, &iport->state));
पूर्ण

पूर्णांक isci_port_perक्रमm_hard_reset(काष्ठा isci_host *ihost, काष्ठा isci_port *iport,
				 काष्ठा isci_phy *iphy)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत sci_status status;
	पूर्णांक ret = TMF_RESP_FUNC_COMPLETE;

	dev_dbg(&ihost->pdev->dev, "%s: iport = %p\n",
		__func__, iport);

	spin_lock_irqsave(&ihost->scic_lock, flags);
	set_bit(IPORT_RESET_PENDING, &iport->state);

	#घोषणा ISCI_PORT_RESET_TIMEOUT SCIC_SDS_SIGNATURE_FIS_TIMEOUT
	status = sci_port_hard_reset(iport, ISCI_PORT_RESET_TIMEOUT);

	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	अगर (status == SCI_SUCCESS) अणु
		रुको_port_reset(ihost, iport);

		dev_dbg(&ihost->pdev->dev,
			"%s: iport = %p; hard reset completion\n",
			__func__, iport);

		अगर (iport->hard_reset_status != SCI_SUCCESS) अणु
			ret = TMF_RESP_FUNC_FAILED;

			dev_err(&ihost->pdev->dev,
				"%s: iport = %p; hard reset failed (0x%x)\n",
				__func__, iport, iport->hard_reset_status);
		पूर्ण
	पूर्ण अन्यथा अणु
		clear_bit(IPORT_RESET_PENDING, &iport->state);
		wake_up(&ihost->eventq);
		ret = TMF_RESP_FUNC_FAILED;

		dev_err(&ihost->pdev->dev,
			"%s: iport = %p; sci_port_hard_reset call"
			" failed 0x%x\n",
			__func__, iport, status);

	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक isci_ata_check_पढ़ोy(काष्ठा करोमुख्य_device *dev)
अणु
	काष्ठा isci_port *iport = dev->port->lldd_port;
	काष्ठा isci_host *ihost = dev_to_ihost(dev);
	काष्ठा isci_remote_device *idev;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	idev = isci_lookup_device(dev);
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	अगर (!idev)
		जाओ out;

	अगर (test_bit(IPORT_RESET_PENDING, &iport->state))
		जाओ out;

	rc = !!iport->active_phy_mask;
 out:
	isci_put_device(idev);

	वापस rc;
पूर्ण

व्योम isci_port_deक्रमmed(काष्ठा asd_sas_phy *phy)
अणु
	काष्ठा isci_host *ihost = phy->ha->lldd_ha;
	काष्ठा isci_port *iport = phy->port->lldd_port;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* we got a port notअगरication on a port that was subsequently
	 * torn करोwn and libsas is just now catching up
	 */
	अगर (!iport)
		वापस;

	spin_lock_irqsave(&ihost->scic_lock, flags);
	क्रम (i = 0; i < SCI_MAX_PHYS; i++) अणु
		अगर (iport->active_phy_mask & 1 << i)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	अगर (i >= SCI_MAX_PHYS)
		dev_dbg(&ihost->pdev->dev, "%s: port: %ld\n",
			__func__, (दीर्घ) (iport - &ihost->ports[0]));
पूर्ण

व्योम isci_port_क्रमmed(काष्ठा asd_sas_phy *phy)
अणु
	काष्ठा isci_host *ihost = phy->ha->lldd_ha;
	काष्ठा isci_phy *iphy = to_iphy(phy);
	काष्ठा asd_sas_port *port = phy->port;
	काष्ठा isci_port *iport = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* initial ports are क्रमmed as the driver is still initializing,
	 * रुको क्रम that process to complete
	 */
	रुको_क्रम_start(ihost);

	spin_lock_irqsave(&ihost->scic_lock, flags);
	क्रम (i = 0; i < SCI_MAX_PORTS; i++) अणु
		iport = &ihost->ports[i];
		अगर (iport->active_phy_mask & 1 << iphy->phy_index)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	अगर (i >= SCI_MAX_PORTS)
		iport = शून्य;

	port->lldd_port = iport;
पूर्ण
