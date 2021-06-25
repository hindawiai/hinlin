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

#समावेश "host.h"

#घोषणा SCIC_SDS_MPC_RECONFIGURATION_TIMEOUT    (10)
#घोषणा SCIC_SDS_APC_RECONFIGURATION_TIMEOUT    (10)
#घोषणा SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION  (1000)

क्रमागत SCIC_SDS_APC_ACTIVITY अणु
	SCIC_SDS_APC_SKIP_PHY,
	SCIC_SDS_APC_ADD_PHY,
	SCIC_SDS_APC_START_TIMER,

	SCIC_SDS_APC_ACTIVITY_MAX
पूर्ण;

/*
 * ******************************************************************************
 * General port configuration agent routines
 * ****************************************************************************** */

/**
 * sci_sas_address_compare()
 * @address_one: A SAS Address to be compared.
 * @address_two: A SAS Address to be compared.
 *
 * Compare the two SAS Address and अगर SAS Address One is greater than SAS
 * Address Two then वापस > 0 अन्यथा अगर SAS Address One is less than SAS Address
 * Two वापस < 0 Otherwise they are the same वापस 0 A चिन्हित value of x > 0
 * > y where x is वापसed क्रम Address One > Address Two y is वापसed क्रम
 * Address One < Address Two 0 is वापसed ofr Address One = Address Two
 */
अटल s32 sci_sas_address_compare(
	काष्ठा sci_sas_address address_one,
	काष्ठा sci_sas_address address_two)
अणु
	अगर (address_one.high > address_two.high) अणु
		वापस 1;
	पूर्ण अन्यथा अगर (address_one.high < address_two.high) अणु
		वापस -1;
	पूर्ण अन्यथा अगर (address_one.low > address_two.low) अणु
		वापस 1;
	पूर्ण अन्यथा अगर (address_one.low < address_two.low) अणु
		वापस -1;
	पूर्ण

	/* The two SAS Address must be identical */
	वापस 0;
पूर्ण

/**
 * sci_port_configuration_agent_find_port()
 * @ihost: The controller object used क्रम the port search.
 * @iphy: The phy object to match.
 *
 * This routine will find a matching port क्रम the phy.  This means that the
 * port and phy both have the same broadcast sas address and same received sas
 * address. The port address or the शून्य अगर there is no matching
 * port. port address अगर the port can be found to match the phy.
 * शून्य अगर there is no matching port क्रम the phy.
 */
अटल काष्ठा isci_port *sci_port_configuration_agent_find_port(
	काष्ठा isci_host *ihost,
	काष्ठा isci_phy *iphy)
अणु
	u8 i;
	काष्ठा sci_sas_address port_sas_address;
	काष्ठा sci_sas_address port_attached_device_address;
	काष्ठा sci_sas_address phy_sas_address;
	काष्ठा sci_sas_address phy_attached_device_address;

	/*
	 * Since this phy can be a member of a wide port check to see अगर one or
	 * more phys match the sent and received SAS address as this phy in which
	 * हाल it should participate in the same port.
	 */
	sci_phy_get_sas_address(iphy, &phy_sas_address);
	sci_phy_get_attached_sas_address(iphy, &phy_attached_device_address);

	क्रम (i = 0; i < ihost->logical_port_entries; i++) अणु
		काष्ठा isci_port *iport = &ihost->ports[i];

		sci_port_get_sas_address(iport, &port_sas_address);
		sci_port_get_attached_sas_address(iport, &port_attached_device_address);

		अगर (sci_sas_address_compare(port_sas_address, phy_sas_address) == 0 &&
		    sci_sas_address_compare(port_attached_device_address, phy_attached_device_address) == 0)
			वापस iport;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * sci_port_configuration_agent_validate_ports()
 * @ihost: This is the controller object that contains the port agent
 * @port_agent: This is the port configuration agent क्रम the controller.
 *
 * This routine will validate the port configuration is correct क्रम the SCU
 * hardware.  The SCU hardware allows क्रम port configurations as follows. LP0
 * -> (PE0), (PE0, PE1), (PE0, PE1, PE2, PE3) LP1 -> (PE1) LP2 -> (PE2), (PE2,
 * PE3) LP3 -> (PE3) क्रमागत sci_status SCI_SUCCESS the port configuration is valid क्रम
 * this port configuration agent. SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION
 * the port configuration is not valid क्रम this port configuration agent.
 */
अटल क्रमागत sci_status sci_port_configuration_agent_validate_ports(
	काष्ठा isci_host *ihost,
	काष्ठा sci_port_configuration_agent *port_agent)
अणु
	काष्ठा sci_sas_address first_address;
	काष्ठा sci_sas_address second_address;

	/*
	 * Sanity check the max ranges क्रम all the phys the max index
	 * is always equal to the port range index */
	अगर (port_agent->phy_valid_port_range[0].max_index != 0 ||
	    port_agent->phy_valid_port_range[1].max_index != 1 ||
	    port_agent->phy_valid_port_range[2].max_index != 2 ||
	    port_agent->phy_valid_port_range[3].max_index != 3)
		वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;

	/*
	 * This is a request to configure a single x4 port or at least attempt
	 * to make all the phys पूर्णांकo a single port */
	अगर (port_agent->phy_valid_port_range[0].min_index == 0 &&
	    port_agent->phy_valid_port_range[1].min_index == 0 &&
	    port_agent->phy_valid_port_range[2].min_index == 0 &&
	    port_agent->phy_valid_port_range[3].min_index == 0)
		वापस SCI_SUCCESS;

	/*
	 * This is a degenerate हाल where phy 1 and phy 2 are asचिन्हित
	 * to the same port this is explicitly disallowed by the hardware
	 * unless they are part of the same x4 port and this condition was
	 * alपढ़ोy checked above. */
	अगर (port_agent->phy_valid_port_range[2].min_index == 1) अणु
		वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
	पूर्ण

	/*
	 * PE0 and PE3 can never have the same SAS Address unless they
	 * are part of the same x4 wide port and we have alपढ़ोy checked
	 * क्रम this condition. */
	sci_phy_get_sas_address(&ihost->phys[0], &first_address);
	sci_phy_get_sas_address(&ihost->phys[3], &second_address);

	अगर (sci_sas_address_compare(first_address, second_address) == 0) अणु
		वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
	पूर्ण

	/*
	 * PE0 and PE1 are configured पूर्णांकo a 2x1 ports make sure that the
	 * SAS Address क्रम PE0 and PE2 are dअगरferent since they can not be
	 * part of the same port. */
	अगर (port_agent->phy_valid_port_range[0].min_index == 0 &&
	    port_agent->phy_valid_port_range[1].min_index == 1) अणु
		sci_phy_get_sas_address(&ihost->phys[0], &first_address);
		sci_phy_get_sas_address(&ihost->phys[2], &second_address);

		अगर (sci_sas_address_compare(first_address, second_address) == 0) अणु
			वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
		पूर्ण
	पूर्ण

	/*
	 * PE2 and PE3 are configured पूर्णांकo a 2x1 ports make sure that the
	 * SAS Address क्रम PE1 and PE3 are dअगरferent since they can not be
	 * part of the same port. */
	अगर (port_agent->phy_valid_port_range[2].min_index == 2 &&
	    port_agent->phy_valid_port_range[3].min_index == 3) अणु
		sci_phy_get_sas_address(&ihost->phys[1], &first_address);
		sci_phy_get_sas_address(&ihost->phys[3], &second_address);

		अगर (sci_sas_address_compare(first_address, second_address) == 0) अणु
			वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
		पूर्ण
	पूर्ण

	वापस SCI_SUCCESS;
पूर्ण

/*
 * ******************************************************************************
 * Manual port configuration agent routines
 * ****************************************************************************** */

/* verअगरy all of the phys in the same port are using the same SAS address */
अटल क्रमागत sci_status
sci_mpc_agent_validate_phy_configuration(काष्ठा isci_host *ihost,
					      काष्ठा sci_port_configuration_agent *port_agent)
अणु
	u32 phy_mask;
	u32 asचिन्हित_phy_mask;
	काष्ठा sci_sas_address sas_address;
	काष्ठा sci_sas_address phy_asचिन्हित_address;
	u8 port_index;
	u8 phy_index;

	asचिन्हित_phy_mask = 0;
	sas_address.high = 0;
	sas_address.low = 0;

	क्रम (port_index = 0; port_index < SCI_MAX_PORTS; port_index++) अणु
		phy_mask = ihost->oem_parameters.ports[port_index].phy_mask;

		अगर (!phy_mask)
			जारी;
		/*
		 * Make sure that one or more of the phys were not alपढ़ोy assinged to
		 * a dअगरferent port. */
		अगर ((phy_mask & ~asचिन्हित_phy_mask) == 0) अणु
			वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
		पूर्ण

		/* Find the starting phy index क्रम this round through the loop */
		क्रम (phy_index = 0; phy_index < SCI_MAX_PHYS; phy_index++) अणु
			अगर ((phy_mask & (1 << phy_index)) == 0)
				जारी;
			sci_phy_get_sas_address(&ihost->phys[phy_index],
						     &sas_address);

			/*
			 * The phy_index can be used as the starting poपूर्णांक क्रम the
			 * port range since the hardware starts all logical ports
			 * the same as the PE index. */
			port_agent->phy_valid_port_range[phy_index].min_index = port_index;
			port_agent->phy_valid_port_range[phy_index].max_index = phy_index;

			अगर (phy_index != port_index) अणु
				वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
			पूर्ण

			अवरोध;
		पूर्ण

		/*
		 * See how many additional phys are being added to this logical port.
		 * Note: We have not moved the current phy_index so we will actually
		 *       compare the startting phy with itself.
		 *       This is expected and required to add the phy to the port. */
		क्रम (; phy_index < SCI_MAX_PHYS; phy_index++) अणु
			अगर ((phy_mask & (1 << phy_index)) == 0)
				जारी;
			sci_phy_get_sas_address(&ihost->phys[phy_index],
						     &phy_asचिन्हित_address);

			अगर (sci_sas_address_compare(sas_address, phy_asचिन्हित_address) != 0) अणु
				/*
				 * The phy mask specअगरied that this phy is part of the same port
				 * as the starting phy and it is not so fail this configuration */
				वापस SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
			पूर्ण

			port_agent->phy_valid_port_range[phy_index].min_index = port_index;
			port_agent->phy_valid_port_range[phy_index].max_index = phy_index;

			sci_port_add_phy(&ihost->ports[port_index],
					      &ihost->phys[phy_index]);

			asचिन्हित_phy_mask |= (1 << phy_index);
		पूर्ण

	पूर्ण

	वापस sci_port_configuration_agent_validate_ports(ihost, port_agent);
पूर्ण

अटल व्योम mpc_agent_समयout(काष्ठा समयr_list *t)
अणु
	u8 index;
	काष्ठा sci_समयr *पंचांगr = from_समयr(पंचांगr, t, समयr);
	काष्ठा sci_port_configuration_agent *port_agent;
	काष्ठा isci_host *ihost;
	अचिन्हित दीर्घ flags;
	u16 configure_phy_mask;

	port_agent = container_of(पंचांगr, typeof(*port_agent), समयr);
	ihost = container_of(port_agent, typeof(*ihost), port_agent);

	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (पंचांगr->cancel)
		जाओ करोne;

	port_agent->समयr_pending = false;

	/* Find the mask of phys that are reported पढ़ो but as yet unconfigured पूर्णांकo a port */
	configure_phy_mask = ~port_agent->phy_configured_mask & port_agent->phy_पढ़ोy_mask;

	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		काष्ठा isci_phy *iphy = &ihost->phys[index];

		अगर (configure_phy_mask & (1 << index)) अणु
			port_agent->link_up_handler(ihost, port_agent,
						    phy_get_non_dummy_port(iphy),
						    iphy);
		पूर्ण
	पूर्ण

करोne:
	spin_unlock_irqrestore(&ihost->scic_lock, flags);
पूर्ण

अटल व्योम sci_mpc_agent_link_up(काष्ठा isci_host *ihost,
				       काष्ठा sci_port_configuration_agent *port_agent,
				       काष्ठा isci_port *iport,
				       काष्ठा isci_phy *iphy)
अणु
	/* If the port is शून्य then the phy was not asचिन्हित to a port.
	 * This is because the phy was not given the same SAS Address as
	 * the other PHYs in the port.
	 */
	अगर (!iport)
		वापस;

	port_agent->phy_पढ़ोy_mask |= (1 << iphy->phy_index);
	sci_port_link_up(iport, iphy);
	अगर ((iport->active_phy_mask & (1 << iphy->phy_index)))
		port_agent->phy_configured_mask |= (1 << iphy->phy_index);
पूर्ण

/**
 * sci_mpc_agent_link_करोwn()
 * @ihost: This is the controller object that receives the link करोwn
 *    notअगरication.
 * @port_agent: This is the port configuration agent क्रम the controller.
 * @iport: This is the port object associated with the phy.  If the is no
 *    associated port this is an शून्य.  The port is an invalid
 *    handle only अगर the phy was never port of this port.  This happens when
 *    the phy is not broadcasting the same SAS address as the other phys in the
 *    asचिन्हित port.
 * @iphy: This is the phy object which has gone link करोwn.
 *
 * This function handles the manual port configuration link करोwn notअगरications.
 * Since all ports and phys are associated at initialization समय we just turn
 * around and notअगरiy the port object of the link करोwn event.  If this PHY is
 * not associated with a port there is no action taken. Is it possible to get a
 * link करोwn notअगरication from a phy that has no assocoated port?
 */
अटल व्योम sci_mpc_agent_link_करोwn(
	काष्ठा isci_host *ihost,
	काष्ठा sci_port_configuration_agent *port_agent,
	काष्ठा isci_port *iport,
	काष्ठा isci_phy *iphy)
अणु
	अगर (iport != शून्य) अणु
		/*
		 * If we can क्रमm a new port from the reमुख्यder of the phys
		 * then we want to start the समयr to allow the SCI User to
		 * cleanup old devices and rediscover the port beक्रमe
		 * rebuilding the port with the phys that reमुख्य in the पढ़ोy
		 * state.
		 */
		port_agent->phy_पढ़ोy_mask &= ~(1 << iphy->phy_index);
		port_agent->phy_configured_mask &= ~(1 << iphy->phy_index);

		/*
		 * Check to see अगर there are more phys रुकोing to be
		 * configured पूर्णांकo a port. If there are allow the SCI User
		 * to tear करोwn this port, अगर necessary, and then reस्थिरruct
		 * the port after the समयout.
		 */
		अगर ((port_agent->phy_configured_mask == 0x0000) &&
		    (port_agent->phy_पढ़ोy_mask != 0x0000) &&
		    !port_agent->समयr_pending) अणु
			port_agent->समयr_pending = true;

			sci_mod_समयr(&port_agent->समयr,
				      SCIC_SDS_MPC_RECONFIGURATION_TIMEOUT);
		पूर्ण

		sci_port_link_करोwn(iport, iphy);
	पूर्ण
पूर्ण

/* verअगरy phys are asचिन्हित a valid SAS address क्रम स्वतःmatic port
 * configuration mode.
 */
अटल क्रमागत sci_status
sci_apc_agent_validate_phy_configuration(काष्ठा isci_host *ihost,
					      काष्ठा sci_port_configuration_agent *port_agent)
अणु
	u8 phy_index;
	u8 port_index;
	काष्ठा sci_sas_address sas_address;
	काष्ठा sci_sas_address phy_asचिन्हित_address;

	phy_index = 0;

	जबतक (phy_index < SCI_MAX_PHYS) अणु
		port_index = phy_index;

		/* Get the asचिन्हित SAS Address क्रम the first PHY on the controller. */
		sci_phy_get_sas_address(&ihost->phys[phy_index],
					    &sas_address);

		जबतक (++phy_index < SCI_MAX_PHYS) अणु
			sci_phy_get_sas_address(&ihost->phys[phy_index],
						     &phy_asचिन्हित_address);

			/* Verअगरy each of the SAS address are all the same क्रम every PHY */
			अगर (sci_sas_address_compare(sas_address, phy_asचिन्हित_address) == 0) अणु
				port_agent->phy_valid_port_range[phy_index].min_index = port_index;
				port_agent->phy_valid_port_range[phy_index].max_index = phy_index;
			पूर्ण अन्यथा अणु
				port_agent->phy_valid_port_range[phy_index].min_index = phy_index;
				port_agent->phy_valid_port_range[phy_index].max_index = phy_index;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस sci_port_configuration_agent_validate_ports(ihost, port_agent);
पूर्ण

/*
 * This routine will restart the स्वतःmatic port configuration समयout
 * समयr क्रम the next समय period. This could be caused by either a link
 * करोwn event or a link up event where we can not yet tell to which a phy
 * beदीर्घs.
 */
अटल व्योम sci_apc_agent_start_समयr(काष्ठा sci_port_configuration_agent *port_agent,
				      u32 समयout)
अणु
	port_agent->समयr_pending = true;
	sci_mod_समयr(&port_agent->समयr, समयout);
पूर्ण

अटल व्योम sci_apc_agent_configure_ports(काष्ठा isci_host *ihost,
					       काष्ठा sci_port_configuration_agent *port_agent,
					       काष्ठा isci_phy *iphy,
					       bool start_समयr)
अणु
	u8 port_index;
	क्रमागत sci_status status;
	काष्ठा isci_port *iport;
	क्रमागत SCIC_SDS_APC_ACTIVITY apc_activity = SCIC_SDS_APC_SKIP_PHY;

	iport = sci_port_configuration_agent_find_port(ihost, iphy);

	अगर (iport) अणु
		अगर (sci_port_is_valid_phy_assignment(iport, iphy->phy_index))
			apc_activity = SCIC_SDS_APC_ADD_PHY;
		अन्यथा
			apc_activity = SCIC_SDS_APC_SKIP_PHY;
	पूर्ण अन्यथा अणु
		/*
		 * There is no matching Port क्रम this PHY so lets search through the
		 * Ports and see अगर we can add the PHY to its own port or maybe start
		 * the समयr and रुको to see अगर a wider port can be made.
		 *
		 * Note the अवरोध when we reach the condition of the port id == phy id */
		क्रम (port_index = port_agent->phy_valid_port_range[iphy->phy_index].min_index;
		     port_index <= port_agent->phy_valid_port_range[iphy->phy_index].max_index;
		     port_index++) अणु

			iport = &ihost->ports[port_index];

			/* First we must make sure that this PHY can be added to this Port. */
			अगर (sci_port_is_valid_phy_assignment(iport, iphy->phy_index)) अणु
				/*
				 * Port contains a PHY with a greater PHY ID than the current
				 * PHY that has gone link up.  This phy can not be part of any
				 * port so skip it and move on. */
				अगर (iport->active_phy_mask > (1 << iphy->phy_index)) अणु
					apc_activity = SCIC_SDS_APC_SKIP_PHY;
					अवरोध;
				पूर्ण

				/*
				 * We have reached the end of our Port list and have not found
				 * any reason why we should not either add the PHY to the port
				 * or रुको क्रम more phys to become active. */
				अगर (iport->physical_port_index == iphy->phy_index) अणु
					/*
					 * The Port either has no active PHYs.
					 * Consider that अगर the port had any active PHYs we would have
					 * or active PHYs with
					 * a lower PHY Id than this PHY. */
					अगर (apc_activity != SCIC_SDS_APC_START_TIMER) अणु
						apc_activity = SCIC_SDS_APC_ADD_PHY;
					पूर्ण

					अवरोध;
				पूर्ण

				/*
				 * The current Port has no active PHYs and this PHY could be part
				 * of this Port.  Since we करोnt know as yet setup to start the
				 * समयr and see अगर there is a better configuration. */
				अगर (iport->active_phy_mask == 0) अणु
					apc_activity = SCIC_SDS_APC_START_TIMER;
				पूर्ण
			पूर्ण अन्यथा अगर (iport->active_phy_mask != 0) अणु
				/*
				 * The Port has an active phy and the current Phy can not
				 * participate in this port so skip the PHY and see अगर
				 * there is a better configuration. */
				apc_activity = SCIC_SDS_APC_SKIP_PHY;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Check to see अगर the start समयr operations should instead map to an
	 * add phy operation.  This is caused because we have been रुकोing to
	 * add a phy to a port but could not becuase the स्वतःmatic port
	 * configuration engine had a choice of possible ports क्रम the phy.
	 * Since we have gone through a समयout we are going to restrict the
	 * choice to the smallest possible port. */
	अगर (
		(start_समयr == false)
		&& (apc_activity == SCIC_SDS_APC_START_TIMER)
		) अणु
		apc_activity = SCIC_SDS_APC_ADD_PHY;
	पूर्ण

	चयन (apc_activity) अणु
	हाल SCIC_SDS_APC_ADD_PHY:
		status = sci_port_add_phy(iport, iphy);

		अगर (status == SCI_SUCCESS) अणु
			port_agent->phy_configured_mask |= (1 << iphy->phy_index);
		पूर्ण
		अवरोध;

	हाल SCIC_SDS_APC_START_TIMER:
		sci_apc_agent_start_समयr(port_agent,
					  SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION);
		अवरोध;

	हाल SCIC_SDS_APC_SKIP_PHY:
	शेष:
		/* करो nothing the PHY can not be made part of a port at this समय. */
		अवरोध;
	पूर्ण
पूर्ण

/**
 * sci_apc_agent_link_up - handle apc link up events
 * @ihost: This is the controller object that receives the link up
 *    notअगरication.
 * @port_agent: This is the port configuration agent क्रम the controller.
 * @iport: This is the port object associated with the phy.  If the is no
 *    associated port this is an शून्य.
 * @iphy: This is the phy object which has gone link up.
 *
 * This method handles the स्वतःmatic port configuration क्रम link up
 * notअगरications. Is it possible to get a link करोwn notअगरication from a phy
 * that has no assocoated port?
 */
अटल व्योम sci_apc_agent_link_up(काष्ठा isci_host *ihost,
				       काष्ठा sci_port_configuration_agent *port_agent,
				       काष्ठा isci_port *iport,
				       काष्ठा isci_phy *iphy)
अणु
	u8 phy_index  = iphy->phy_index;

	अगर (!iport) अणु
		/* the phy is not the part of this port */
		port_agent->phy_पढ़ोy_mask |= 1 << phy_index;
		sci_apc_agent_start_समयr(port_agent,
					  SCIC_SDS_APC_WAIT_LINK_UP_NOTIFICATION);
	पूर्ण अन्यथा अणु
		/* the phy is alपढ़ोy the part of the port */
		port_agent->phy_पढ़ोy_mask |= 1 << phy_index;
		sci_port_link_up(iport, iphy);
	पूर्ण
पूर्ण

/**
 * sci_apc_agent_link_करोwn()
 * @ihost: This is the controller object that receives the link करोwn
 *    notअगरication.
 * @port_agent: This is the port configuration agent क्रम the controller.
 * @iport: This is the port object associated with the phy.  If the is no
 *    associated port this is an शून्य.
 * @iphy: This is the phy object which has gone link करोwn.
 *
 * This method handles the स्वतःmatic port configuration link करोwn
 * notअगरications. not associated with a port there is no action taken. Is it
 * possible to get a link करोwn notअगरication from a phy that has no assocoated
 * port?
 */
अटल व्योम sci_apc_agent_link_करोwn(
	काष्ठा isci_host *ihost,
	काष्ठा sci_port_configuration_agent *port_agent,
	काष्ठा isci_port *iport,
	काष्ठा isci_phy *iphy)
अणु
	port_agent->phy_पढ़ोy_mask &= ~(1 << iphy->phy_index);

	अगर (!iport)
		वापस;
	अगर (port_agent->phy_configured_mask & (1 << iphy->phy_index)) अणु
		क्रमागत sci_status status;

		status = sci_port_हटाओ_phy(iport, iphy);

		अगर (status == SCI_SUCCESS)
			port_agent->phy_configured_mask &= ~(1 << iphy->phy_index);
	पूर्ण
पूर्ण

/* configure the phys पूर्णांकo ports when the समयr fires */
अटल व्योम apc_agent_समयout(काष्ठा समयr_list *t)
अणु
	u32 index;
	काष्ठा sci_समयr *पंचांगr = from_समयr(पंचांगr, t, समयr);
	काष्ठा sci_port_configuration_agent *port_agent;
	काष्ठा isci_host *ihost;
	अचिन्हित दीर्घ flags;
	u16 configure_phy_mask;

	port_agent = container_of(पंचांगr, typeof(*port_agent), समयr);
	ihost = container_of(port_agent, typeof(*ihost), port_agent);

	spin_lock_irqsave(&ihost->scic_lock, flags);

	अगर (पंचांगr->cancel)
		जाओ करोne;

	port_agent->समयr_pending = false;

	configure_phy_mask = ~port_agent->phy_configured_mask & port_agent->phy_पढ़ोy_mask;

	अगर (!configure_phy_mask)
		जाओ करोne;

	क्रम (index = 0; index < SCI_MAX_PHYS; index++) अणु
		अगर ((configure_phy_mask & (1 << index)) == 0)
			जारी;

		sci_apc_agent_configure_ports(ihost, port_agent,
						   &ihost->phys[index], false);
	पूर्ण

	अगर (is_controller_start_complete(ihost))
		sci_controller_transition_to_पढ़ोy(ihost, SCI_SUCCESS);

करोne:
	spin_unlock_irqrestore(&ihost->scic_lock, flags);
पूर्ण

/*
 * ******************************************************************************
 * Public port configuration agent routines
 * ****************************************************************************** */

/*
 * This method will स्थिरruct the port configuration agent क्रम operation. This
 * call is universal क्रम both manual port configuration and स्वतःmatic port
 * configuration modes.
 */
व्योम sci_port_configuration_agent_स्थिरruct(
	काष्ठा sci_port_configuration_agent *port_agent)
अणु
	u32 index;

	port_agent->phy_configured_mask = 0x00;
	port_agent->phy_पढ़ोy_mask = 0x00;

	port_agent->link_up_handler = शून्य;
	port_agent->link_करोwn_handler = शून्य;

	port_agent->समयr_pending = false;

	क्रम (index = 0; index < SCI_MAX_PORTS; index++) अणु
		port_agent->phy_valid_port_range[index].min_index = 0;
		port_agent->phy_valid_port_range[index].max_index = 0;
	पूर्ण
पूर्ण

bool is_port_config_apc(काष्ठा isci_host *ihost)
अणु
	वापस ihost->port_agent.link_up_handler == sci_apc_agent_link_up;
पूर्ण

क्रमागत sci_status sci_port_configuration_agent_initialize(
	काष्ठा isci_host *ihost,
	काष्ठा sci_port_configuration_agent *port_agent)
अणु
	क्रमागत sci_status status;
	क्रमागत sci_port_configuration_mode mode;

	mode = ihost->oem_parameters.controller.mode_type;

	अगर (mode == SCIC_PORT_MANUAL_CONFIGURATION_MODE) अणु
		status = sci_mpc_agent_validate_phy_configuration(
				ihost, port_agent);

		port_agent->link_up_handler = sci_mpc_agent_link_up;
		port_agent->link_करोwn_handler = sci_mpc_agent_link_करोwn;

		sci_init_समयr(&port_agent->समयr, mpc_agent_समयout);
	पूर्ण अन्यथा अणु
		status = sci_apc_agent_validate_phy_configuration(
				ihost, port_agent);

		port_agent->link_up_handler = sci_apc_agent_link_up;
		port_agent->link_करोwn_handler = sci_apc_agent_link_करोwn;

		sci_init_समयr(&port_agent->समयr, apc_agent_समयout);
	पूर्ण

	वापस status;
पूर्ण
