<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 1999 - 2004 Intel Corporation. All rights reserved.
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_bonding.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/net_namespace.h>
#समावेश <net/bonding.h>
#समावेश <net/bond_3ad.h>
#समावेश <net/netlink.h>

/* General definitions */
#घोषणा AD_SHORT_TIMEOUT           1
#घोषणा AD_LONG_TIMEOUT            0
#घोषणा AD_STANDBY                 0x2
#घोषणा AD_MAX_TX_IN_SECOND        3
#घोषणा AD_COLLECTOR_MAX_DELAY     0

/* Timer definitions (43.4.4 in the 802.3ad standard) */
#घोषणा AD_FAST_PERIODIC_TIME      1
#घोषणा AD_SLOW_PERIODIC_TIME      30
#घोषणा AD_SHORT_TIMEOUT_TIME      (3*AD_FAST_PERIODIC_TIME)
#घोषणा AD_LONG_TIMEOUT_TIME       (3*AD_SLOW_PERIODIC_TIME)
#घोषणा AD_CHURN_DETECTION_TIME    60
#घोषणा AD_AGGREGATE_WAIT_TIME     2

/* Port Variables definitions used by the State Machines (43.4.7 in the
 * 802.3ad standard)
 */
#घोषणा AD_PORT_BEGIN           0x1
#घोषणा AD_PORT_LACP_ENABLED    0x2
#घोषणा AD_PORT_ACTOR_CHURN     0x4
#घोषणा AD_PORT_PARTNER_CHURN   0x8
#घोषणा AD_PORT_READY           0x10
#घोषणा AD_PORT_READY_N         0x20
#घोषणा AD_PORT_MATCHED         0x40
#घोषणा AD_PORT_STANDBY         0x80
#घोषणा AD_PORT_SELECTED        0x100
#घोषणा AD_PORT_MOVED           0x200
#घोषणा AD_PORT_CHURNED         (AD_PORT_ACTOR_CHURN | AD_PORT_PARTNER_CHURN)

/* Port Key definitions
 * key is determined according to the link speed, duplex and
 * user key (which is yet not supported)
 *           --------------------------------------------------------------
 * Port key  | User key (10 bits)           | Speed (5 bits)      | Duplex|
 *           --------------------------------------------------------------
 *           |15                           6|5                   1|0
 */
#घोषणा  AD_DUPLEX_KEY_MASKS    0x1
#घोषणा  AD_SPEED_KEY_MASKS     0x3E
#घोषणा  AD_USER_KEY_MASKS      0xFFC0

क्रमागत ad_link_speed_type अणु
	AD_LINK_SPEED_1MBPS = 1,
	AD_LINK_SPEED_10MBPS,
	AD_LINK_SPEED_100MBPS,
	AD_LINK_SPEED_1000MBPS,
	AD_LINK_SPEED_2500MBPS,
	AD_LINK_SPEED_5000MBPS,
	AD_LINK_SPEED_10000MBPS,
	AD_LINK_SPEED_14000MBPS,
	AD_LINK_SPEED_20000MBPS,
	AD_LINK_SPEED_25000MBPS,
	AD_LINK_SPEED_40000MBPS,
	AD_LINK_SPEED_50000MBPS,
	AD_LINK_SPEED_56000MBPS,
	AD_LINK_SPEED_100000MBPS,
	AD_LINK_SPEED_200000MBPS,
	AD_LINK_SPEED_400000MBPS,
पूर्ण;

/* compare MAC addresses */
#घोषणा MAC_ADDRESS_EQUAL(A, B)	\
	ether_addr_equal_64bits((स्थिर u8 *)A, (स्थिर u8 *)B)

अटल स्थिर u8 null_mac_addr[ETH_ALEN + 2] __दीर्घ_aligned = अणु
	0, 0, 0, 0, 0, 0
पूर्ण;
अटल u16 ad_ticks_per_sec;
अटल स्थिर पूर्णांक ad_delta_in_ticks = (AD_TIMER_INTERVAL * HZ) / 1000;

अटल स्थिर u8 lacpdu_mcast_addr[ETH_ALEN + 2] __दीर्घ_aligned =
	MULTICAST_LACPDU_ADDR;

/* ================= मुख्य 802.3ad protocol functions ================== */
अटल पूर्णांक ad_lacpdu_send(काष्ठा port *port);
अटल पूर्णांक ad_marker_send(काष्ठा port *port, काष्ठा bond_marker *marker);
अटल व्योम ad_mux_machine(काष्ठा port *port, bool *update_slave_arr);
अटल व्योम ad_rx_machine(काष्ठा lacpdu *lacpdu, काष्ठा port *port);
अटल व्योम ad_tx_machine(काष्ठा port *port);
अटल व्योम ad_periodic_machine(काष्ठा port *port);
अटल व्योम ad_port_selection_logic(काष्ठा port *port, bool *update_slave_arr);
अटल व्योम ad_agg_selection_logic(काष्ठा aggregator *aggregator,
				   bool *update_slave_arr);
अटल व्योम ad_clear_agg(काष्ठा aggregator *aggregator);
अटल व्योम ad_initialize_agg(काष्ठा aggregator *aggregator);
अटल व्योम ad_initialize_port(काष्ठा port *port, पूर्णांक lacp_fast);
अटल व्योम ad_enable_collecting_distributing(काष्ठा port *port,
					      bool *update_slave_arr);
अटल व्योम ad_disable_collecting_distributing(काष्ठा port *port,
					       bool *update_slave_arr);
अटल व्योम ad_marker_info_received(काष्ठा bond_marker *marker_info,
				    काष्ठा port *port);
अटल व्योम ad_marker_response_received(काष्ठा bond_marker *marker,
					काष्ठा port *port);
अटल व्योम ad_update_actor_keys(काष्ठा port *port, bool reset);


/* ================= api to bonding and kernel code ================== */

/**
 * __get_bond_by_port - get the port's bonding काष्ठा
 * @port: the port we're looking at
 *
 * Return @port's bonding struct, or %NULL if it can't be found.
 */
अटल अंतरभूत काष्ठा bonding *__get_bond_by_port(काष्ठा port *port)
अणु
	अगर (port->slave == शून्य)
		वापस शून्य;

	वापस bond_get_bond_by_slave(port->slave);
पूर्ण

/**
 * __get_first_agg - get the first aggregator in the bond
 * @port: the port we're looking at
 *
 * Return the aggregator of the first slave in @bond, or %शून्य अगर it can't be
 * found.
 * The caller must hold RCU or RTNL lock.
 */
अटल अंतरभूत काष्ठा aggregator *__get_first_agg(काष्ठा port *port)
अणु
	काष्ठा bonding *bond = __get_bond_by_port(port);
	काष्ठा slave *first_slave;
	काष्ठा aggregator *agg;

	/* If there's no bond क्रम this port, or bond has no slaves */
	अगर (bond == शून्य)
		वापस शून्य;

	rcu_पढ़ो_lock();
	first_slave = bond_first_slave_rcu(bond);
	agg = first_slave ? &(SLAVE_AD_INFO(first_slave)->aggregator) : शून्य;
	rcu_पढ़ो_unlock();

	वापस agg;
पूर्ण

/**
 * __agg_has_partner - see अगर we have a partner
 * @agg: the agregator we're looking at
 *
 * Return nonzero अगर aggregator has a partner (denoted by a non-zero ether
 * address क्रम the partner). Return 0 अगर not.
 */
अटल अंतरभूत पूर्णांक __agg_has_partner(काष्ठा aggregator *agg)
अणु
	वापस !is_zero_ether_addr(agg->partner_प्रणाली.mac_addr_value);
पूर्ण

/**
 * __disable_port - disable the port's slave
 * @port: the port we're looking at
 */
अटल अंतरभूत व्योम __disable_port(काष्ठा port *port)
अणु
	bond_set_slave_inactive_flags(port->slave, BOND_SLAVE_NOTIFY_LATER);
पूर्ण

/**
 * __enable_port - enable the port's slave, if it's up
 * @port: the port we're looking at
 */
अटल अंतरभूत व्योम __enable_port(काष्ठा port *port)
अणु
	काष्ठा slave *slave = port->slave;

	अगर ((slave->link == BOND_LINK_UP) && bond_slave_is_up(slave))
		bond_set_slave_active_flags(slave, BOND_SLAVE_NOTIFY_LATER);
पूर्ण

/**
 * __port_is_enabled - check अगर the port's slave is in active state
 * @port: the port we're looking at
 */
अटल अंतरभूत पूर्णांक __port_is_enabled(काष्ठा port *port)
अणु
	वापस bond_is_active_slave(port->slave);
पूर्ण

/**
 * __get_agg_selection_mode - get the aggregator selection mode
 * @port: the port we're looking at
 *
 * Get the aggregator selection mode. Can be %STABLE, %BANDWIDTH or %COUNT.
 */
अटल अंतरभूत u32 __get_agg_selection_mode(काष्ठा port *port)
अणु
	काष्ठा bonding *bond = __get_bond_by_port(port);

	अगर (bond == शून्य)
		वापस BOND_AD_STABLE;

	वापस bond->params.ad_select;
पूर्ण

/**
 * __check_agg_selection_समयr - check अगर the selection समयr has expired
 * @port: the port we're looking at
 */
अटल अंतरभूत पूर्णांक __check_agg_selection_समयr(काष्ठा port *port)
अणु
	काष्ठा bonding *bond = __get_bond_by_port(port);

	अगर (bond == शून्य)
		वापस 0;

	वापस BOND_AD_INFO(bond).agg_select_समयr ? 1 : 0;
पूर्ण

/**
 * __get_link_speed - get a port's speed
 * @port: the port we're looking at
 *
 * Return @port's speed in 802.3ad क्रमागत क्रमmat. i.e. one of:
 *     0,
 *     %AD_LINK_SPEED_10MBPS,
 *     %AD_LINK_SPEED_100MBPS,
 *     %AD_LINK_SPEED_1000MBPS,
 *     %AD_LINK_SPEED_2500MBPS,
 *     %AD_LINK_SPEED_5000MBPS,
 *     %AD_LINK_SPEED_10000MBPS
 *     %AD_LINK_SPEED_14000MBPS,
 *     %AD_LINK_SPEED_20000MBPS
 *     %AD_LINK_SPEED_25000MBPS
 *     %AD_LINK_SPEED_40000MBPS
 *     %AD_LINK_SPEED_50000MBPS
 *     %AD_LINK_SPEED_56000MBPS
 *     %AD_LINK_SPEED_100000MBPS
 *     %AD_LINK_SPEED_200000MBPS
 *     %AD_LINK_SPEED_400000MBPS
 */
अटल u16 __get_link_speed(काष्ठा port *port)
अणु
	काष्ठा slave *slave = port->slave;
	u16 speed;

	/* this अगर covers only a special हाल: when the configuration starts
	 * with link करोwn, it sets the speed to 0.
	 * This is करोne in spite of the fact that the e100 driver reports 0
	 * to be compatible with MVT in the future.
	 */
	अगर (slave->link != BOND_LINK_UP)
		speed = 0;
	अन्यथा अणु
		चयन (slave->speed) अणु
		हाल SPEED_10:
			speed = AD_LINK_SPEED_10MBPS;
			अवरोध;

		हाल SPEED_100:
			speed = AD_LINK_SPEED_100MBPS;
			अवरोध;

		हाल SPEED_1000:
			speed = AD_LINK_SPEED_1000MBPS;
			अवरोध;

		हाल SPEED_2500:
			speed = AD_LINK_SPEED_2500MBPS;
			अवरोध;

		हाल SPEED_5000:
			speed = AD_LINK_SPEED_5000MBPS;
			अवरोध;

		हाल SPEED_10000:
			speed = AD_LINK_SPEED_10000MBPS;
			अवरोध;

		हाल SPEED_14000:
			speed = AD_LINK_SPEED_14000MBPS;
			अवरोध;

		हाल SPEED_20000:
			speed = AD_LINK_SPEED_20000MBPS;
			अवरोध;

		हाल SPEED_25000:
			speed = AD_LINK_SPEED_25000MBPS;
			अवरोध;

		हाल SPEED_40000:
			speed = AD_LINK_SPEED_40000MBPS;
			अवरोध;

		हाल SPEED_50000:
			speed = AD_LINK_SPEED_50000MBPS;
			अवरोध;

		हाल SPEED_56000:
			speed = AD_LINK_SPEED_56000MBPS;
			अवरोध;

		हाल SPEED_100000:
			speed = AD_LINK_SPEED_100000MBPS;
			अवरोध;

		हाल SPEED_200000:
			speed = AD_LINK_SPEED_200000MBPS;
			अवरोध;

		हाल SPEED_400000:
			speed = AD_LINK_SPEED_400000MBPS;
			अवरोध;

		शेष:
			/* unknown speed value from ethtool. shouldn't happen */
			अगर (slave->speed != SPEED_UNKNOWN)
				pr_err_once("%s: (slave %s): unknown ethtool speed (%d) for port %d (set it to 0)\n",
					    slave->bond->dev->name,
					    slave->dev->name, slave->speed,
					    port->actor_port_number);
			speed = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	slave_dbg(slave->bond->dev, slave->dev, "Port %d Received link speed %d update from adapter\n",
		  port->actor_port_number, speed);
	वापस speed;
पूर्ण

/**
 * __get_duplex - get a port's duplex
 * @port: the port we're looking at
 *
 * Return @port's duplex in 802.3ad biपंचांगask क्रमmat. i.e.:
 *     0x01 अगर in full duplex
 *     0x00 otherwise
 */
अटल u8 __get_duplex(काष्ठा port *port)
अणु
	काष्ठा slave *slave = port->slave;
	u8 retval = 0x0;

	/* handling a special हाल: when the configuration starts with
	 * link करोwn, it sets the duplex to 0.
	 */
	अगर (slave->link == BOND_LINK_UP) अणु
		चयन (slave->duplex) अणु
		हाल DUPLEX_FULL:
			retval = 0x1;
			slave_dbg(slave->bond->dev, slave->dev, "Port %d Received status full duplex update from adapter\n",
				  port->actor_port_number);
			अवरोध;
		हाल DUPLEX_HALF:
		शेष:
			retval = 0x0;
			slave_dbg(slave->bond->dev, slave->dev, "Port %d Received status NOT full duplex update from adapter\n",
				  port->actor_port_number);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम __ad_actor_update_port(काष्ठा port *port)
अणु
	स्थिर काष्ठा bonding *bond = bond_get_bond_by_slave(port->slave);

	port->actor_प्रणाली = BOND_AD_INFO(bond).प्रणाली.sys_mac_addr;
	port->actor_प्रणाली_priority = BOND_AD_INFO(bond).प्रणाली.sys_priority;
पूर्ण

/* Conversions */

/**
 * __ad_समयr_to_ticks - convert a given समयr type to AD module ticks
 * @समयr_type:	which समयr to operate
 * @par: समयr parameter. see below
 *
 * If @समयr_type is %current_जबतक_समयr, @par indicates दीर्घ/लघु समयr.
 * If @समयr_type is %periodic_समयr, @par is one of %FAST_PERIODIC_TIME,
 *						     %SLOW_PERIODIC_TIME.
 */
अटल u16 __ad_समयr_to_ticks(u16 समयr_type, u16 par)
अणु
	u16 retval = 0; /* to silence the compiler */

	चयन (समयr_type) अणु
	हाल AD_CURRENT_WHILE_TIMER:	/* क्रम rx machine usage */
		अगर (par)
			retval = (AD_SHORT_TIMEOUT_TIME*ad_ticks_per_sec);
		अन्यथा
			retval = (AD_LONG_TIMEOUT_TIME*ad_ticks_per_sec);
		अवरोध;
	हाल AD_ACTOR_CHURN_TIMER:	/* क्रम local churn machine */
		retval = (AD_CHURN_DETECTION_TIME*ad_ticks_per_sec);
		अवरोध;
	हाल AD_PERIODIC_TIMER:		/* क्रम periodic machine */
		retval = (par*ad_ticks_per_sec); /* दीर्घ समयout */
		अवरोध;
	हाल AD_PARTNER_CHURN_TIMER:	/* क्रम remote churn machine */
		retval = (AD_CHURN_DETECTION_TIME*ad_ticks_per_sec);
		अवरोध;
	हाल AD_WAIT_WHILE_TIMER:	/* क्रम selection machine */
		retval = (AD_AGGREGATE_WAIT_TIME*ad_ticks_per_sec);
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण


/* ================= ad_rx_machine helper functions ================== */

/**
 * __choose_matched - update a port's matched variable from a received lacpdu
 * @lacpdu: the lacpdu we've received
 * @port: the port we're looking at
 *
 * Update the value of the matched variable, using parameter values from a
 * newly received lacpdu. Parameter values क्रम the partner carried in the
 * received PDU are compared with the corresponding operational parameter
 * values क्रम the actor. Matched is set to TRUE अगर all of these parameters
 * match and the PDU parameter partner_state.aggregation has the same value as
 * actor_oper_port_state.aggregation and lacp will actively मुख्यtain the link
 * in the aggregation. Matched is also set to TRUE अगर the value of
 * actor_state.aggregation in the received PDU is set to FALSE, i.e., indicates
 * an inभागidual link and lacp will actively मुख्यtain the link. Otherwise,
 * matched is set to FALSE. LACP is considered to be actively मुख्यtaining the
 * link अगर either the PDU's actor_state.lacp_activity variable is TRUE or both
 * the actor's actor_oper_port_state.lacp_activity and the PDU's
 * partner_state.lacp_activity variables are TRUE.
 *
 * Note: the AD_PORT_MATCHED "variable" is not specअगरied by 802.3ad; it is
 * used here to implement the language from 802.3ad 43.4.9 that requires
 * recordPDU to "match" the LACPDU parameters to the stored values.
 */
अटल व्योम __choose_matched(काष्ठा lacpdu *lacpdu, काष्ठा port *port)
अणु
	/* check अगर all parameters are alike
	 * or this is inभागidual link(aggregation == FALSE)
	 * then update the state machine Matched variable.
	 */
	अगर (((ntohs(lacpdu->partner_port) == port->actor_port_number) &&
	     (ntohs(lacpdu->partner_port_priority) == port->actor_port_priority) &&
	     MAC_ADDRESS_EQUAL(&(lacpdu->partner_प्रणाली), &(port->actor_प्रणाली)) &&
	     (ntohs(lacpdu->partner_प्रणाली_priority) == port->actor_प्रणाली_priority) &&
	     (ntohs(lacpdu->partner_key) == port->actor_oper_port_key) &&
	     ((lacpdu->partner_state & LACP_STATE_AGGREGATION) == (port->actor_oper_port_state & LACP_STATE_AGGREGATION))) ||
	    ((lacpdu->actor_state & LACP_STATE_AGGREGATION) == 0)
		) अणु
		port->sm_vars |= AD_PORT_MATCHED;
	पूर्ण अन्यथा अणु
		port->sm_vars &= ~AD_PORT_MATCHED;
	पूर्ण
पूर्ण

/**
 * __record_pdu - record parameters from a received lacpdu
 * @lacpdu: the lacpdu we've received
 * @port: the port we're looking at
 *
 * Record the parameter values क्रम the Actor carried in a received lacpdu as
 * the current partner operational parameter values and sets
 * actor_oper_port_state.शेषed to FALSE.
 */
अटल व्योम __record_pdu(काष्ठा lacpdu *lacpdu, काष्ठा port *port)
अणु
	अगर (lacpdu && port) अणु
		काष्ठा port_params *partner = &port->partner_oper;

		__choose_matched(lacpdu, port);
		/* record the new parameter values क्रम the partner
		 * operational
		 */
		partner->port_number = ntohs(lacpdu->actor_port);
		partner->port_priority = ntohs(lacpdu->actor_port_priority);
		partner->प्रणाली = lacpdu->actor_प्रणाली;
		partner->प्रणाली_priority = ntohs(lacpdu->actor_प्रणाली_priority);
		partner->key = ntohs(lacpdu->actor_key);
		partner->port_state = lacpdu->actor_state;

		/* set actor_oper_port_state.शेषed to FALSE */
		port->actor_oper_port_state &= ~LACP_STATE_DEFAULTED;

		/* set the partner sync. to on अगर the partner is sync,
		 * and the port is matched
		 */
		अगर ((port->sm_vars & AD_PORT_MATCHED) &&
		    (lacpdu->actor_state & LACP_STATE_SYNCHRONIZATION)) अणु
			partner->port_state |= LACP_STATE_SYNCHRONIZATION;
			slave_dbg(port->slave->bond->dev, port->slave->dev,
				  "partner sync=1\n");
		पूर्ण अन्यथा अणु
			partner->port_state &= ~LACP_STATE_SYNCHRONIZATION;
			slave_dbg(port->slave->bond->dev, port->slave->dev,
				  "partner sync=0\n");
		पूर्ण
	पूर्ण
पूर्ण

/**
 * __record_शेष - record शेष parameters
 * @port: the port we're looking at
 *
 * This function records the शेष parameter values क्रम the partner carried
 * in the Partner Admin parameters as the current partner operational parameter
 * values and sets actor_oper_port_state.शेषed to TRUE.
 */
अटल व्योम __record_शेष(काष्ठा port *port)
अणु
	अगर (port) अणु
		/* record the partner admin parameters */
		स_नकल(&port->partner_oper, &port->partner_admin,
		       माप(काष्ठा port_params));

		/* set actor_oper_port_state.शेषed to true */
		port->actor_oper_port_state |= LACP_STATE_DEFAULTED;
	पूर्ण
पूर्ण

/**
 * __update_selected - update a port's Selected variable from a received lacpdu
 * @lacpdu: the lacpdu we've received
 * @port: the port we're looking at
 *
 * Update the value of the selected variable, using parameter values from a
 * newly received lacpdu. The parameter values क्रम the Actor carried in the
 * received PDU are compared with the corresponding operational parameter
 * values क्रम the ports partner. If one or more of the comparisons shows that
 * the value(s) received in the PDU dअगरfer from the current operational values,
 * then selected is set to FALSE and actor_oper_port_state.synchronization is
 * set to out_of_sync. Otherwise, selected reमुख्यs unchanged.
 */
अटल व्योम __update_selected(काष्ठा lacpdu *lacpdu, काष्ठा port *port)
अणु
	अगर (lacpdu && port) अणु
		स्थिर काष्ठा port_params *partner = &port->partner_oper;

		/* check अगर any parameter is dअगरferent then
		 * update the state machine selected variable.
		 */
		अगर (ntohs(lacpdu->actor_port) != partner->port_number ||
		    ntohs(lacpdu->actor_port_priority) != partner->port_priority ||
		    !MAC_ADDRESS_EQUAL(&lacpdu->actor_प्रणाली, &partner->प्रणाली) ||
		    ntohs(lacpdu->actor_प्रणाली_priority) != partner->प्रणाली_priority ||
		    ntohs(lacpdu->actor_key) != partner->key ||
		    (lacpdu->actor_state & LACP_STATE_AGGREGATION) != (partner->port_state & LACP_STATE_AGGREGATION)) अणु
			port->sm_vars &= ~AD_PORT_SELECTED;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * __update_शेष_selected - update a port's Selected variable from Partner
 * @port: the port we're looking at
 *
 * This function updates the value of the selected variable, using the partner
 * administrative parameter values. The administrative values are compared with
 * the corresponding operational parameter values क्रम the partner. If one or
 * more of the comparisons shows that the administrative value(s) dअगरfer from
 * the current operational values, then Selected is set to FALSE and
 * actor_oper_port_state.synchronization is set to OUT_OF_SYNC. Otherwise,
 * Selected reमुख्यs unchanged.
 */
अटल व्योम __update_शेष_selected(काष्ठा port *port)
अणु
	अगर (port) अणु
		स्थिर काष्ठा port_params *admin = &port->partner_admin;
		स्थिर काष्ठा port_params *oper = &port->partner_oper;

		/* check अगर any parameter is dअगरferent then
		 * update the state machine selected variable.
		 */
		अगर (admin->port_number != oper->port_number ||
		    admin->port_priority != oper->port_priority ||
		    !MAC_ADDRESS_EQUAL(&admin->प्रणाली, &oper->प्रणाली) ||
		    admin->प्रणाली_priority != oper->प्रणाली_priority ||
		    admin->key != oper->key ||
		    (admin->port_state & LACP_STATE_AGGREGATION)
			!= (oper->port_state & LACP_STATE_AGGREGATION)) अणु
			port->sm_vars &= ~AD_PORT_SELECTED;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * __update_ntt - update a port's ntt variable from a received lacpdu
 * @lacpdu: the lacpdu we've received
 * @port: the port we're looking at
 *
 * Updates the value of the ntt variable, using parameter values from a newly
 * received lacpdu. The parameter values क्रम the partner carried in the
 * received PDU are compared with the corresponding operational parameter
 * values क्रम the Actor. If one or more of the comparisons shows that the
 * value(s) received in the PDU dअगरfer from the current operational values,
 * then ntt is set to TRUE. Otherwise, ntt reमुख्यs unchanged.
 */
अटल व्योम __update_ntt(काष्ठा lacpdu *lacpdu, काष्ठा port *port)
अणु
	/* validate lacpdu and port */
	अगर (lacpdu && port) अणु
		/* check अगर any parameter is dअगरferent then
		 * update the port->ntt.
		 */
		अगर ((ntohs(lacpdu->partner_port) != port->actor_port_number) ||
		    (ntohs(lacpdu->partner_port_priority) != port->actor_port_priority) ||
		    !MAC_ADDRESS_EQUAL(&(lacpdu->partner_प्रणाली), &(port->actor_प्रणाली)) ||
		    (ntohs(lacpdu->partner_प्रणाली_priority) != port->actor_प्रणाली_priority) ||
		    (ntohs(lacpdu->partner_key) != port->actor_oper_port_key) ||
		    ((lacpdu->partner_state & LACP_STATE_LACP_ACTIVITY) != (port->actor_oper_port_state & LACP_STATE_LACP_ACTIVITY)) ||
		    ((lacpdu->partner_state & LACP_STATE_LACP_TIMEOUT) != (port->actor_oper_port_state & LACP_STATE_LACP_TIMEOUT)) ||
		    ((lacpdu->partner_state & LACP_STATE_SYNCHRONIZATION) != (port->actor_oper_port_state & LACP_STATE_SYNCHRONIZATION)) ||
		    ((lacpdu->partner_state & LACP_STATE_AGGREGATION) != (port->actor_oper_port_state & LACP_STATE_AGGREGATION))
		   ) अणु
			port->ntt = true;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * __agg_ports_are_पढ़ोy - check अगर all ports in an aggregator are पढ़ोy
 * @aggregator: the aggregator we're looking at
 *
 */
अटल पूर्णांक __agg_ports_are_पढ़ोy(काष्ठा aggregator *aggregator)
अणु
	काष्ठा port *port;
	पूर्णांक retval = 1;

	अगर (aggregator) अणु
		/* scan all ports in this aggregator to verfy अगर they are
		 * all पढ़ोy.
		 */
		क्रम (port = aggregator->lag_ports;
		     port;
		     port = port->next_port_in_aggregator) अणु
			अगर (!(port->sm_vars & AD_PORT_READY_N)) अणु
				retval = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

/**
 * __set_agg_ports_पढ़ोy - set value of Ready bit in all ports of an aggregator
 * @aggregator: the aggregator we're looking at
 * @val: Should the ports' पढ़ोy bit be set on or off
 *
 */
अटल व्योम __set_agg_ports_पढ़ोy(काष्ठा aggregator *aggregator, पूर्णांक val)
अणु
	काष्ठा port *port;

	क्रम (port = aggregator->lag_ports; port;
	     port = port->next_port_in_aggregator) अणु
		अगर (val)
			port->sm_vars |= AD_PORT_READY;
		अन्यथा
			port->sm_vars &= ~AD_PORT_READY;
	पूर्ण
पूर्ण

अटल पूर्णांक __agg_active_ports(काष्ठा aggregator *agg)
अणु
	काष्ठा port *port;
	पूर्णांक active = 0;

	क्रम (port = agg->lag_ports; port;
	     port = port->next_port_in_aggregator) अणु
		अगर (port->is_enabled)
			active++;
	पूर्ण

	वापस active;
पूर्ण

/**
 * __get_agg_bandwidth - get the total bandwidth of an aggregator
 * @aggregator: the aggregator we're looking at
 *
 */
अटल u32 __get_agg_bandwidth(काष्ठा aggregator *aggregator)
अणु
	पूर्णांक nports = __agg_active_ports(aggregator);
	u32 bandwidth = 0;

	अगर (nports) अणु
		चयन (__get_link_speed(aggregator->lag_ports)) अणु
		हाल AD_LINK_SPEED_1MBPS:
			bandwidth = nports;
			अवरोध;
		हाल AD_LINK_SPEED_10MBPS:
			bandwidth = nports * 10;
			अवरोध;
		हाल AD_LINK_SPEED_100MBPS:
			bandwidth = nports * 100;
			अवरोध;
		हाल AD_LINK_SPEED_1000MBPS:
			bandwidth = nports * 1000;
			अवरोध;
		हाल AD_LINK_SPEED_2500MBPS:
			bandwidth = nports * 2500;
			अवरोध;
		हाल AD_LINK_SPEED_5000MBPS:
			bandwidth = nports * 5000;
			अवरोध;
		हाल AD_LINK_SPEED_10000MBPS:
			bandwidth = nports * 10000;
			अवरोध;
		हाल AD_LINK_SPEED_14000MBPS:
			bandwidth = nports * 14000;
			अवरोध;
		हाल AD_LINK_SPEED_20000MBPS:
			bandwidth = nports * 20000;
			अवरोध;
		हाल AD_LINK_SPEED_25000MBPS:
			bandwidth = nports * 25000;
			अवरोध;
		हाल AD_LINK_SPEED_40000MBPS:
			bandwidth = nports * 40000;
			अवरोध;
		हाल AD_LINK_SPEED_50000MBPS:
			bandwidth = nports * 50000;
			अवरोध;
		हाल AD_LINK_SPEED_56000MBPS:
			bandwidth = nports * 56000;
			अवरोध;
		हाल AD_LINK_SPEED_100000MBPS:
			bandwidth = nports * 100000;
			अवरोध;
		हाल AD_LINK_SPEED_200000MBPS:
			bandwidth = nports * 200000;
			अवरोध;
		हाल AD_LINK_SPEED_400000MBPS:
			bandwidth = nports * 400000;
			अवरोध;
		शेष:
			bandwidth = 0; /* to silence the compiler */
		पूर्ण
	पूर्ण
	वापस bandwidth;
पूर्ण

/**
 * __get_active_agg - get the current active aggregator
 * @aggregator: the aggregator we're looking at
 *
 * Caller must hold RCU lock.
 */
अटल काष्ठा aggregator *__get_active_agg(काष्ठा aggregator *aggregator)
अणु
	काष्ठा bonding *bond = aggregator->slave->bond;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	bond_क्रम_each_slave_rcu(bond, slave, iter)
		अगर (SLAVE_AD_INFO(slave)->aggregator.is_active)
			वापस &(SLAVE_AD_INFO(slave)->aggregator);

	वापस शून्य;
पूर्ण

/**
 * __update_lacpdu_from_port - update a port's lacpdu fields
 * @port: the port we're looking at
 */
अटल अंतरभूत व्योम __update_lacpdu_from_port(काष्ठा port *port)
अणु
	काष्ठा lacpdu *lacpdu = &port->lacpdu;
	स्थिर काष्ठा port_params *partner = &port->partner_oper;

	/* update current actual Actor parameters
	 * lacpdu->subtype                   initialized
	 * lacpdu->version_number            initialized
	 * lacpdu->tlv_type_actor_info       initialized
	 * lacpdu->actor_inक्रमmation_length  initialized
	 */

	lacpdu->actor_प्रणाली_priority = htons(port->actor_प्रणाली_priority);
	lacpdu->actor_प्रणाली = port->actor_प्रणाली;
	lacpdu->actor_key = htons(port->actor_oper_port_key);
	lacpdu->actor_port_priority = htons(port->actor_port_priority);
	lacpdu->actor_port = htons(port->actor_port_number);
	lacpdu->actor_state = port->actor_oper_port_state;
	slave_dbg(port->slave->bond->dev, port->slave->dev,
		  "update lacpdu: actor port state %x\n",
		  port->actor_oper_port_state);

	/* lacpdu->reserved_3_1              initialized
	 * lacpdu->tlv_type_partner_info     initialized
	 * lacpdu->partner_inक्रमmation_length initialized
	 */

	lacpdu->partner_प्रणाली_priority = htons(partner->प्रणाली_priority);
	lacpdu->partner_प्रणाली = partner->प्रणाली;
	lacpdu->partner_key = htons(partner->key);
	lacpdu->partner_port_priority = htons(partner->port_priority);
	lacpdu->partner_port = htons(partner->port_number);
	lacpdu->partner_state = partner->port_state;

	/* lacpdu->reserved_3_2              initialized
	 * lacpdu->tlv_type_collector_info   initialized
	 * lacpdu->collector_inक्रमmation_length initialized
	 * collector_max_delay                initialized
	 * reserved_12[12]                   initialized
	 * tlv_type_terminator               initialized
	 * terminator_length                 initialized
	 * reserved_50[50]                   initialized
	 */
पूर्ण

/* ================= मुख्य 802.3ad protocol code ========================= */

/**
 * ad_lacpdu_send - send out a lacpdu packet on a given port
 * @port: the port we're looking at
 *
 * Returns:   0 on success
 *          < 0 on error
 */
अटल पूर्णांक ad_lacpdu_send(काष्ठा port *port)
अणु
	काष्ठा slave *slave = port->slave;
	काष्ठा sk_buff *skb;
	काष्ठा lacpdu_header *lacpdu_header;
	पूर्णांक length = माप(काष्ठा lacpdu_header);

	skb = dev_alloc_skb(length);
	अगर (!skb)
		वापस -ENOMEM;

	atomic64_inc(&SLAVE_AD_INFO(slave)->stats.lacpdu_tx);
	atomic64_inc(&BOND_AD_INFO(slave->bond).stats.lacpdu_tx);

	skb->dev = slave->dev;
	skb_reset_mac_header(skb);
	skb->network_header = skb->mac_header + ETH_HLEN;
	skb->protocol = PKT_TYPE_LACPDU;
	skb->priority = TC_PRIO_CONTROL;

	lacpdu_header = skb_put(skb, length);

	ether_addr_copy(lacpdu_header->hdr.h_dest, lacpdu_mcast_addr);
	/* Note: source address is set to be the member's PERMANENT address,
	 * because we use it to identअगरy loopback lacpdus in receive.
	 */
	ether_addr_copy(lacpdu_header->hdr.h_source, slave->perm_hwaddr);
	lacpdu_header->hdr.h_proto = PKT_TYPE_LACPDU;

	lacpdu_header->lacpdu = port->lacpdu;

	dev_queue_xmit(skb);

	वापस 0;
पूर्ण

/**
 * ad_marker_send - send marker inक्रमmation/response on a given port
 * @port: the port we're looking at
 * @marker: marker data to send
 *
 * Returns:   0 on success
 *          < 0 on error
 */
अटल पूर्णांक ad_marker_send(काष्ठा port *port, काष्ठा bond_marker *marker)
अणु
	काष्ठा slave *slave = port->slave;
	काष्ठा sk_buff *skb;
	काष्ठा bond_marker_header *marker_header;
	पूर्णांक length = माप(काष्ठा bond_marker_header);

	skb = dev_alloc_skb(length + 16);
	अगर (!skb)
		वापस -ENOMEM;

	चयन (marker->tlv_type) अणु
	हाल AD_MARKER_INFORMATION_SUBTYPE:
		atomic64_inc(&SLAVE_AD_INFO(slave)->stats.marker_tx);
		atomic64_inc(&BOND_AD_INFO(slave->bond).stats.marker_tx);
		अवरोध;
	हाल AD_MARKER_RESPONSE_SUBTYPE:
		atomic64_inc(&SLAVE_AD_INFO(slave)->stats.marker_resp_tx);
		atomic64_inc(&BOND_AD_INFO(slave->bond).stats.marker_resp_tx);
		अवरोध;
	पूर्ण

	skb_reserve(skb, 16);

	skb->dev = slave->dev;
	skb_reset_mac_header(skb);
	skb->network_header = skb->mac_header + ETH_HLEN;
	skb->protocol = PKT_TYPE_LACPDU;

	marker_header = skb_put(skb, length);

	ether_addr_copy(marker_header->hdr.h_dest, lacpdu_mcast_addr);
	/* Note: source address is set to be the member's PERMANENT address,
	 * because we use it to identअगरy loopback MARKERs in receive.
	 */
	ether_addr_copy(marker_header->hdr.h_source, slave->perm_hwaddr);
	marker_header->hdr.h_proto = PKT_TYPE_LACPDU;

	marker_header->marker = *marker;

	dev_queue_xmit(skb);

	वापस 0;
पूर्ण

/**
 * ad_mux_machine - handle a port's mux state machine
 * @port: the port we're looking at
 * @update_slave_arr: Does slave array need update?
 */
अटल व्योम ad_mux_machine(काष्ठा port *port, bool *update_slave_arr)
अणु
	mux_states_t last_state;

	/* keep current State Machine state to compare later अगर it was
	 * changed
	 */
	last_state = port->sm_mux_state;

	अगर (port->sm_vars & AD_PORT_BEGIN) अणु
		port->sm_mux_state = AD_MUX_DETACHED;
	पूर्ण अन्यथा अणु
		चयन (port->sm_mux_state) अणु
		हाल AD_MUX_DETACHED:
			अगर ((port->sm_vars & AD_PORT_SELECTED)
			    || (port->sm_vars & AD_PORT_STANDBY))
				/* अगर SELECTED or STANDBY */
				port->sm_mux_state = AD_MUX_WAITING;
			अवरोध;
		हाल AD_MUX_WAITING:
			/* अगर SELECTED == FALSE वापस to DETACH state */
			अगर (!(port->sm_vars & AD_PORT_SELECTED)) अणु
				port->sm_vars &= ~AD_PORT_READY_N;
				/* in order to withhold the Selection Logic to
				 * check all ports READY_N value every callback
				 * cycle to update पढ़ोy variable, we check
				 * READY_N and update READY here
				 */
				__set_agg_ports_पढ़ोy(port->aggregator, __agg_ports_are_पढ़ोy(port->aggregator));
				port->sm_mux_state = AD_MUX_DETACHED;
				अवरोध;
			पूर्ण

			/* check अगर the रुको_जबतक_समयr expired */
			अगर (port->sm_mux_समयr_counter
			    && !(--port->sm_mux_समयr_counter))
				port->sm_vars |= AD_PORT_READY_N;

			/* in order to withhold the selection logic to check
			 * all ports READY_N value every callback cycle to
			 * update पढ़ोy variable, we check READY_N and update
			 * READY here
			 */
			__set_agg_ports_पढ़ोy(port->aggregator, __agg_ports_are_पढ़ोy(port->aggregator));

			/* अगर the रुको_जबतक_समयr expired, and the port is
			 * in READY state, move to ATTACHED state
			 */
			अगर ((port->sm_vars & AD_PORT_READY)
			    && !port->sm_mux_समयr_counter)
				port->sm_mux_state = AD_MUX_ATTACHED;
			अवरोध;
		हाल AD_MUX_ATTACHED:
			/* check also अगर agg_select_समयr expired (so the
			 * edable port will take place only after this समयr)
			 */
			अगर ((port->sm_vars & AD_PORT_SELECTED) &&
			    (port->partner_oper.port_state & LACP_STATE_SYNCHRONIZATION) &&
			    !__check_agg_selection_समयr(port)) अणु
				अगर (port->aggregator->is_active)
					port->sm_mux_state =
					    AD_MUX_COLLECTING_DISTRIBUTING;
			पूर्ण अन्यथा अगर (!(port->sm_vars & AD_PORT_SELECTED) ||
				   (port->sm_vars & AD_PORT_STANDBY)) अणु
				/* अगर UNSELECTED or STANDBY */
				port->sm_vars &= ~AD_PORT_READY_N;
				/* in order to withhold the selection logic to
				 * check all ports READY_N value every callback
				 * cycle to update पढ़ोy variable, we check
				 * READY_N and update READY here
				 */
				__set_agg_ports_पढ़ोy(port->aggregator, __agg_ports_are_पढ़ोy(port->aggregator));
				port->sm_mux_state = AD_MUX_DETACHED;
			पूर्ण अन्यथा अगर (port->aggregator->is_active) अणु
				port->actor_oper_port_state |=
				    LACP_STATE_SYNCHRONIZATION;
			पूर्ण
			अवरोध;
		हाल AD_MUX_COLLECTING_DISTRIBUTING:
			अगर (!(port->sm_vars & AD_PORT_SELECTED) ||
			    (port->sm_vars & AD_PORT_STANDBY) ||
			    !(port->partner_oper.port_state & LACP_STATE_SYNCHRONIZATION) ||
			    !(port->actor_oper_port_state & LACP_STATE_SYNCHRONIZATION)) अणु
				port->sm_mux_state = AD_MUX_ATTACHED;
			पूर्ण अन्यथा अणु
				/* अगर port state hasn't changed make
				 * sure that a collecting distributing
				 * port in an active aggregator is enabled
				 */
				अगर (port->aggregator &&
				    port->aggregator->is_active &&
				    !__port_is_enabled(port)) अणु

					__enable_port(port);
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* check अगर the state machine was changed */
	अगर (port->sm_mux_state != last_state) अणु
		slave_dbg(port->slave->bond->dev, port->slave->dev,
			  "Mux Machine: Port=%d, Last State=%d, Curr State=%d\n",
			  port->actor_port_number,
			  last_state,
			  port->sm_mux_state);
		चयन (port->sm_mux_state) अणु
		हाल AD_MUX_DETACHED:
			port->actor_oper_port_state &= ~LACP_STATE_SYNCHRONIZATION;
			ad_disable_collecting_distributing(port,
							   update_slave_arr);
			port->actor_oper_port_state &= ~LACP_STATE_COLLECTING;
			port->actor_oper_port_state &= ~LACP_STATE_DISTRIBUTING;
			port->ntt = true;
			अवरोध;
		हाल AD_MUX_WAITING:
			port->sm_mux_समयr_counter = __ad_समयr_to_ticks(AD_WAIT_WHILE_TIMER, 0);
			अवरोध;
		हाल AD_MUX_ATTACHED:
			अगर (port->aggregator->is_active)
				port->actor_oper_port_state |=
				    LACP_STATE_SYNCHRONIZATION;
			अन्यथा
				port->actor_oper_port_state &=
				    ~LACP_STATE_SYNCHRONIZATION;
			port->actor_oper_port_state &= ~LACP_STATE_COLLECTING;
			port->actor_oper_port_state &= ~LACP_STATE_DISTRIBUTING;
			ad_disable_collecting_distributing(port,
							   update_slave_arr);
			port->ntt = true;
			अवरोध;
		हाल AD_MUX_COLLECTING_DISTRIBUTING:
			port->actor_oper_port_state |= LACP_STATE_COLLECTING;
			port->actor_oper_port_state |= LACP_STATE_DISTRIBUTING;
			port->actor_oper_port_state |= LACP_STATE_SYNCHRONIZATION;
			ad_enable_collecting_distributing(port,
							  update_slave_arr);
			port->ntt = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ad_rx_machine - handle a port's rx State Machine
 * @lacpdu: the lacpdu we've received
 * @port: the port we're looking at
 *
 * If lacpdu arrived, stop previous समयr (अगर exists) and set the next state as
 * CURRENT. If समयr expired set the state machine in the proper state.
 * In other हालs, this function checks अगर we need to चयन to other state.
 */
अटल व्योम ad_rx_machine(काष्ठा lacpdu *lacpdu, काष्ठा port *port)
अणु
	rx_states_t last_state;

	/* keep current State Machine state to compare later अगर it was
	 * changed
	 */
	last_state = port->sm_rx_state;

	अगर (lacpdu) अणु
		atomic64_inc(&SLAVE_AD_INFO(port->slave)->stats.lacpdu_rx);
		atomic64_inc(&BOND_AD_INFO(port->slave->bond).stats.lacpdu_rx);
	पूर्ण
	/* check अगर state machine should change state */

	/* first, check अगर port was reinitialized */
	अगर (port->sm_vars & AD_PORT_BEGIN) अणु
		port->sm_rx_state = AD_RX_INITIALIZE;
		port->sm_vars |= AD_PORT_CHURNED;
	/* check अगर port is not enabled */
	पूर्ण अन्यथा अगर (!(port->sm_vars & AD_PORT_BEGIN) && !port->is_enabled)
		port->sm_rx_state = AD_RX_PORT_DISABLED;
	/* check अगर new lacpdu arrived */
	अन्यथा अगर (lacpdu && ((port->sm_rx_state == AD_RX_EXPIRED) ||
		 (port->sm_rx_state == AD_RX_DEFAULTED) ||
		 (port->sm_rx_state == AD_RX_CURRENT))) अणु
		अगर (port->sm_rx_state != AD_RX_CURRENT)
			port->sm_vars |= AD_PORT_CHURNED;
		port->sm_rx_समयr_counter = 0;
		port->sm_rx_state = AD_RX_CURRENT;
	पूर्ण अन्यथा अणु
		/* अगर समयr is on, and अगर it is expired */
		अगर (port->sm_rx_समयr_counter &&
		    !(--port->sm_rx_समयr_counter)) अणु
			चयन (port->sm_rx_state) अणु
			हाल AD_RX_EXPIRED:
				port->sm_rx_state = AD_RX_DEFAULTED;
				अवरोध;
			हाल AD_RX_CURRENT:
				port->sm_rx_state = AD_RX_EXPIRED;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* अगर no lacpdu arrived and no समयr is on */
			चयन (port->sm_rx_state) अणु
			हाल AD_RX_PORT_DISABLED:
				अगर (port->is_enabled &&
				    (port->sm_vars & AD_PORT_LACP_ENABLED))
					port->sm_rx_state = AD_RX_EXPIRED;
				अन्यथा अगर (port->is_enabled
					 && ((port->sm_vars
					      & AD_PORT_LACP_ENABLED) == 0))
					port->sm_rx_state = AD_RX_LACP_DISABLED;
				अवरोध;
			शेष:
				अवरोध;

			पूर्ण
		पूर्ण
	पूर्ण

	/* check अगर the State machine was changed or new lacpdu arrived */
	अगर ((port->sm_rx_state != last_state) || (lacpdu)) अणु
		slave_dbg(port->slave->bond->dev, port->slave->dev,
			  "Rx Machine: Port=%d, Last State=%d, Curr State=%d\n",
			  port->actor_port_number,
			  last_state,
			  port->sm_rx_state);
		चयन (port->sm_rx_state) अणु
		हाल AD_RX_INITIALIZE:
			अगर (!(port->actor_oper_port_key & AD_DUPLEX_KEY_MASKS))
				port->sm_vars &= ~AD_PORT_LACP_ENABLED;
			अन्यथा
				port->sm_vars |= AD_PORT_LACP_ENABLED;
			port->sm_vars &= ~AD_PORT_SELECTED;
			__record_शेष(port);
			port->actor_oper_port_state &= ~LACP_STATE_EXPIRED;
			port->sm_rx_state = AD_RX_PORT_DISABLED;

			fallthrough;
		हाल AD_RX_PORT_DISABLED:
			port->sm_vars &= ~AD_PORT_MATCHED;
			अवरोध;
		हाल AD_RX_LACP_DISABLED:
			port->sm_vars &= ~AD_PORT_SELECTED;
			__record_शेष(port);
			port->partner_oper.port_state &= ~LACP_STATE_AGGREGATION;
			port->sm_vars |= AD_PORT_MATCHED;
			port->actor_oper_port_state &= ~LACP_STATE_EXPIRED;
			अवरोध;
		हाल AD_RX_EXPIRED:
			/* Reset of the Synchronization flag (Standard 43.4.12)
			 * This reset cause to disable this port in the
			 * COLLECTING_DISTRIBUTING state of the mux machine in
			 * हाल of EXPIRED even अगर LINK_DOWN didn't arrive क्रम
			 * the port.
			 */
			port->partner_oper.port_state &= ~LACP_STATE_SYNCHRONIZATION;
			port->sm_vars &= ~AD_PORT_MATCHED;
			port->partner_oper.port_state |= LACP_STATE_LACP_TIMEOUT;
			port->partner_oper.port_state |= LACP_STATE_LACP_ACTIVITY;
			port->sm_rx_समयr_counter = __ad_समयr_to_ticks(AD_CURRENT_WHILE_TIMER, (u16)(AD_SHORT_TIMEOUT));
			port->actor_oper_port_state |= LACP_STATE_EXPIRED;
			port->sm_vars |= AD_PORT_CHURNED;
			अवरोध;
		हाल AD_RX_DEFAULTED:
			__update_शेष_selected(port);
			__record_शेष(port);
			port->sm_vars |= AD_PORT_MATCHED;
			port->actor_oper_port_state &= ~LACP_STATE_EXPIRED;
			अवरोध;
		हाल AD_RX_CURRENT:
			/* detect loopback situation */
			अगर (MAC_ADDRESS_EQUAL(&(lacpdu->actor_प्रणाली),
					      &(port->actor_प्रणाली))) अणु
				slave_err(port->slave->bond->dev, port->slave->dev, "An illegal loopback occurred on slave\n"
					  "Check the configuration to verify that all adapters are connected to 802.3ad compliant switch ports\n");
				वापस;
			पूर्ण
			__update_selected(lacpdu, port);
			__update_ntt(lacpdu, port);
			__record_pdu(lacpdu, port);
			port->sm_rx_समयr_counter = __ad_समयr_to_ticks(AD_CURRENT_WHILE_TIMER, (u16)(port->actor_oper_port_state & LACP_STATE_LACP_TIMEOUT));
			port->actor_oper_port_state &= ~LACP_STATE_EXPIRED;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ad_churn_machine - handle port churn's state machine
 * @port: the port we're looking at
 *
 */
अटल व्योम ad_churn_machine(काष्ठा port *port)
अणु
	अगर (port->sm_vars & AD_PORT_CHURNED) अणु
		port->sm_vars &= ~AD_PORT_CHURNED;
		port->sm_churn_actor_state = AD_CHURN_MONITOR;
		port->sm_churn_partner_state = AD_CHURN_MONITOR;
		port->sm_churn_actor_समयr_counter =
			__ad_समयr_to_ticks(AD_ACTOR_CHURN_TIMER, 0);
		port->sm_churn_partner_समयr_counter =
			 __ad_समयr_to_ticks(AD_PARTNER_CHURN_TIMER, 0);
		वापस;
	पूर्ण
	अगर (port->sm_churn_actor_समयr_counter &&
	    !(--port->sm_churn_actor_समयr_counter) &&
	    port->sm_churn_actor_state == AD_CHURN_MONITOR) अणु
		अगर (port->actor_oper_port_state & LACP_STATE_SYNCHRONIZATION) अणु
			port->sm_churn_actor_state = AD_NO_CHURN;
		पूर्ण अन्यथा अणु
			port->churn_actor_count++;
			port->sm_churn_actor_state = AD_CHURN;
		पूर्ण
	पूर्ण
	अगर (port->sm_churn_partner_समयr_counter &&
	    !(--port->sm_churn_partner_समयr_counter) &&
	    port->sm_churn_partner_state == AD_CHURN_MONITOR) अणु
		अगर (port->partner_oper.port_state & LACP_STATE_SYNCHRONIZATION) अणु
			port->sm_churn_partner_state = AD_NO_CHURN;
		पूर्ण अन्यथा अणु
			port->churn_partner_count++;
			port->sm_churn_partner_state = AD_CHURN;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ad_tx_machine - handle a port's tx state machine
 * @port: the port we're looking at
 */
अटल व्योम ad_tx_machine(काष्ठा port *port)
अणु
	/* check अगर tx समयr expired, to verअगरy that we करो not send more than
	 * 3 packets per second
	 */
	अगर (port->sm_tx_समयr_counter && !(--port->sm_tx_समयr_counter)) अणु
		/* check अगर there is something to send */
		अगर (port->ntt && (port->sm_vars & AD_PORT_LACP_ENABLED)) अणु
			__update_lacpdu_from_port(port);

			अगर (ad_lacpdu_send(port) >= 0) अणु
				slave_dbg(port->slave->bond->dev,
					  port->slave->dev,
					  "Sent LACPDU on port %d\n",
					  port->actor_port_number);

				/* mark ntt as false, so it will not be sent
				 * again until demanded
				 */
				port->ntt = false;
			पूर्ण
		पूर्ण
		/* restart tx समयr(to verअगरy that we will not exceed
		 * AD_MAX_TX_IN_SECOND
		 */
		port->sm_tx_समयr_counter = ad_ticks_per_sec/AD_MAX_TX_IN_SECOND;
	पूर्ण
पूर्ण

/**
 * ad_periodic_machine - handle a port's periodic state machine
 * @port: the port we're looking at
 *
 * Turn ntt flag on priodically to perक्रमm periodic transmission of lacpdu's.
 */
अटल व्योम ad_periodic_machine(काष्ठा port *port)
अणु
	periodic_states_t last_state;

	/* keep current state machine state to compare later अगर it was changed */
	last_state = port->sm_periodic_state;

	/* check अगर port was reinitialized */
	अगर (((port->sm_vars & AD_PORT_BEGIN) || !(port->sm_vars & AD_PORT_LACP_ENABLED) || !port->is_enabled) ||
	    (!(port->actor_oper_port_state & LACP_STATE_LACP_ACTIVITY) && !(port->partner_oper.port_state & LACP_STATE_LACP_ACTIVITY))
	   ) अणु
		port->sm_periodic_state = AD_NO_PERIODIC;
	पूर्ण
	/* check अगर state machine should change state */
	अन्यथा अगर (port->sm_periodic_समयr_counter) अणु
		/* check अगर periodic state machine expired */
		अगर (!(--port->sm_periodic_समयr_counter)) अणु
			/* अगर expired then करो tx */
			port->sm_periodic_state = AD_PERIODIC_TX;
		पूर्ण अन्यथा अणु
			/* If not expired, check अगर there is some new समयout
			 * parameter from the partner state
			 */
			चयन (port->sm_periodic_state) अणु
			हाल AD_FAST_PERIODIC:
				अगर (!(port->partner_oper.port_state
				      & LACP_STATE_LACP_TIMEOUT))
					port->sm_periodic_state = AD_SLOW_PERIODIC;
				अवरोध;
			हाल AD_SLOW_PERIODIC:
				अगर ((port->partner_oper.port_state & LACP_STATE_LACP_TIMEOUT)) अणु
					port->sm_periodic_समयr_counter = 0;
					port->sm_periodic_state = AD_PERIODIC_TX;
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (port->sm_periodic_state) अणु
		हाल AD_NO_PERIODIC:
			port->sm_periodic_state = AD_FAST_PERIODIC;
			अवरोध;
		हाल AD_PERIODIC_TX:
			अगर (!(port->partner_oper.port_state &
			    LACP_STATE_LACP_TIMEOUT))
				port->sm_periodic_state = AD_SLOW_PERIODIC;
			अन्यथा
				port->sm_periodic_state = AD_FAST_PERIODIC;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* check अगर the state machine was changed */
	अगर (port->sm_periodic_state != last_state) अणु
		slave_dbg(port->slave->bond->dev, port->slave->dev,
			  "Periodic Machine: Port=%d, Last State=%d, Curr State=%d\n",
			  port->actor_port_number, last_state,
			  port->sm_periodic_state);
		चयन (port->sm_periodic_state) अणु
		हाल AD_NO_PERIODIC:
			port->sm_periodic_समयr_counter = 0;
			अवरोध;
		हाल AD_FAST_PERIODIC:
			/* decrement 1 tick we lost in the PERIODIC_TX cycle */
			port->sm_periodic_समयr_counter = __ad_समयr_to_ticks(AD_PERIODIC_TIMER, (u16)(AD_FAST_PERIODIC_TIME))-1;
			अवरोध;
		हाल AD_SLOW_PERIODIC:
			/* decrement 1 tick we lost in the PERIODIC_TX cycle */
			port->sm_periodic_समयr_counter = __ad_समयr_to_ticks(AD_PERIODIC_TIMER, (u16)(AD_SLOW_PERIODIC_TIME))-1;
			अवरोध;
		हाल AD_PERIODIC_TX:
			port->ntt = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ad_port_selection_logic - select aggregation groups
 * @port: the port we're looking at
 * @update_slave_arr: Does slave array need update?
 *
 * Select aggregation groups, and assign each port क्रम it's aggregetor. The
 * selection logic is called in the inititalization (after all the handshkes),
 * and after every lacpdu receive (अगर selected is off).
 */
अटल व्योम ad_port_selection_logic(काष्ठा port *port, bool *update_slave_arr)
अणु
	काष्ठा aggregator *aggregator, *मुक्त_aggregator = शून्य, *temp_aggregator;
	काष्ठा port *last_port = शून्य, *curr_port;
	काष्ठा list_head *iter;
	काष्ठा bonding *bond;
	काष्ठा slave *slave;
	पूर्णांक found = 0;

	/* अगर the port is alपढ़ोy Selected, करो nothing */
	अगर (port->sm_vars & AD_PORT_SELECTED)
		वापस;

	bond = __get_bond_by_port(port);

	/* अगर the port is connected to other aggregator, detach it */
	अगर (port->aggregator) अणु
		/* detach the port from its क्रमmer aggregator */
		temp_aggregator = port->aggregator;
		क्रम (curr_port = temp_aggregator->lag_ports; curr_port;
		     last_port = curr_port,
		     curr_port = curr_port->next_port_in_aggregator) अणु
			अगर (curr_port == port) अणु
				temp_aggregator->num_of_ports--;
				/* अगर it is the first port attached to the
				 * aggregator
				 */
				अगर (!last_port) अणु
					temp_aggregator->lag_ports =
						port->next_port_in_aggregator;
				पूर्ण अन्यथा अणु
					/* not the first port attached to the
					 * aggregator
					 */
					last_port->next_port_in_aggregator =
						port->next_port_in_aggregator;
				पूर्ण

				/* clear the port's relations to this
				 * aggregator
				 */
				port->aggregator = शून्य;
				port->next_port_in_aggregator = शून्य;
				port->actor_port_aggregator_identअगरier = 0;

				slave_dbg(bond->dev, port->slave->dev, "Port %d left LAG %d\n",
					  port->actor_port_number,
					  temp_aggregator->aggregator_identअगरier);
				/* अगर the aggregator is empty, clear its
				 * parameters, and set it पढ़ोy to be attached
				 */
				अगर (!temp_aggregator->lag_ports)
					ad_clear_agg(temp_aggregator);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!curr_port) अणु
			/* meaning: the port was related to an aggregator
			 * but was not on the aggregator port list
			 */
			net_warn_ratelimited("%s: (slave %s): Warning: Port %d was related to aggregator %d but was not on its port list\n",
					     port->slave->bond->dev->name,
					     port->slave->dev->name,
					     port->actor_port_number,
					     port->aggregator->aggregator_identअगरier);
		पूर्ण
	पूर्ण
	/* search on all aggregators क्रम a suitable aggregator क्रम this port */
	bond_क्रम_each_slave(bond, slave, iter) अणु
		aggregator = &(SLAVE_AD_INFO(slave)->aggregator);

		/* keep a मुक्त aggregator क्रम later use(अगर needed) */
		अगर (!aggregator->lag_ports) अणु
			अगर (!मुक्त_aggregator)
				मुक्त_aggregator = aggregator;
			जारी;
		पूर्ण
		/* check अगर current aggregator suits us */
		अगर (((aggregator->actor_oper_aggregator_key == port->actor_oper_port_key) && /* अगर all parameters match AND */
		     MAC_ADDRESS_EQUAL(&(aggregator->partner_प्रणाली), &(port->partner_oper.प्रणाली)) &&
		     (aggregator->partner_प्रणाली_priority == port->partner_oper.प्रणाली_priority) &&
		     (aggregator->partner_oper_aggregator_key == port->partner_oper.key)
		    ) &&
		    ((!MAC_ADDRESS_EQUAL(&(port->partner_oper.प्रणाली), &(null_mac_addr)) && /* partner answers */
		      !aggregator->is_inभागidual)  /* but is not inभागidual OR */
		    )
		   ) अणु
			/* attach to the founded aggregator */
			port->aggregator = aggregator;
			port->actor_port_aggregator_identअगरier =
				port->aggregator->aggregator_identअगरier;
			port->next_port_in_aggregator = aggregator->lag_ports;
			port->aggregator->num_of_ports++;
			aggregator->lag_ports = port;
			slave_dbg(bond->dev, slave->dev, "Port %d joined LAG %d (existing LAG)\n",
				  port->actor_port_number,
				  port->aggregator->aggregator_identअगरier);

			/* mark this port as selected */
			port->sm_vars |= AD_PORT_SELECTED;
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* the port couldn't find an aggregator - attach it to a new
	 * aggregator
	 */
	अगर (!found) अणु
		अगर (मुक्त_aggregator) अणु
			/* assign port a new aggregator */
			port->aggregator = मुक्त_aggregator;
			port->actor_port_aggregator_identअगरier =
				port->aggregator->aggregator_identअगरier;

			/* update the new aggregator's parameters
			 * अगर port was responsed from the end-user
			 */
			अगर (port->actor_oper_port_key & AD_DUPLEX_KEY_MASKS)
				/* अगर port is full duplex */
				port->aggregator->is_inभागidual = false;
			अन्यथा
				port->aggregator->is_inभागidual = true;

			port->aggregator->actor_admin_aggregator_key =
				port->actor_admin_port_key;
			port->aggregator->actor_oper_aggregator_key =
				port->actor_oper_port_key;
			port->aggregator->partner_प्रणाली =
				port->partner_oper.प्रणाली;
			port->aggregator->partner_प्रणाली_priority =
				port->partner_oper.प्रणाली_priority;
			port->aggregator->partner_oper_aggregator_key = port->partner_oper.key;
			port->aggregator->receive_state = 1;
			port->aggregator->transmit_state = 1;
			port->aggregator->lag_ports = port;
			port->aggregator->num_of_ports++;

			/* mark this port as selected */
			port->sm_vars |= AD_PORT_SELECTED;

			slave_dbg(bond->dev, port->slave->dev, "Port %d joined LAG %d (new LAG)\n",
				  port->actor_port_number,
				  port->aggregator->aggregator_identअगरier);
		पूर्ण अन्यथा अणु
			slave_err(bond->dev, port->slave->dev,
				  "Port %d did not find a suitable aggregator\n",
				  port->actor_port_number);
		पूर्ण
	पूर्ण
	/* अगर all aggregator's ports are READY_N == TRUE, set पढ़ोy=TRUE
	 * in all aggregator's ports, अन्यथा set पढ़ोy=FALSE in all
	 * aggregator's ports
	 */
	__set_agg_ports_पढ़ोy(port->aggregator,
			      __agg_ports_are_पढ़ोy(port->aggregator));

	aggregator = __get_first_agg(port);
	ad_agg_selection_logic(aggregator, update_slave_arr);

	अगर (!port->aggregator->is_active)
		port->actor_oper_port_state &= ~LACP_STATE_SYNCHRONIZATION;
पूर्ण

/* Decide अगर "agg" is a better choice क्रम the new active aggregator that
 * the current best, according to the ad_select policy.
 */
अटल काष्ठा aggregator *ad_agg_selection_test(काष्ठा aggregator *best,
						काष्ठा aggregator *curr)
अणु
	/* 0. If no best, select current.
	 *
	 * 1. If the current agg is not inभागidual, and the best is
	 *    inभागidual, select current.
	 *
	 * 2. If current agg is inभागidual and the best is not, keep best.
	 *
	 * 3. Thereक्रमe, current and best are both inभागidual or both not
	 *    inभागidual, so:
	 *
	 * 3a. If current agg partner replied, and best agg partner did not,
	 *     select current.
	 *
	 * 3b. If current agg partner did not reply and best agg partner
	 *     did reply, keep best.
	 *
	 * 4.  Thereक्रमe, current and best both have partner replies or
	 *     both करो not, so perक्रमm selection policy:
	 *
	 * BOND_AD_COUNT: Select by count of ports.  If count is equal,
	 *     select by bandwidth.
	 *
	 * BOND_AD_STABLE, BOND_AD_BANDWIDTH: Select by bandwidth.
	 */
	अगर (!best)
		वापस curr;

	अगर (!curr->is_inभागidual && best->is_inभागidual)
		वापस curr;

	अगर (curr->is_inभागidual && !best->is_inभागidual)
		वापस best;

	अगर (__agg_has_partner(curr) && !__agg_has_partner(best))
		वापस curr;

	अगर (!__agg_has_partner(curr) && __agg_has_partner(best))
		वापस best;

	चयन (__get_agg_selection_mode(curr->lag_ports)) अणु
	हाल BOND_AD_COUNT:
		अगर (__agg_active_ports(curr) > __agg_active_ports(best))
			वापस curr;

		अगर (__agg_active_ports(curr) < __agg_active_ports(best))
			वापस best;

		fallthrough;
	हाल BOND_AD_STABLE:
	हाल BOND_AD_BANDWIDTH:
		अगर (__get_agg_bandwidth(curr) > __get_agg_bandwidth(best))
			वापस curr;

		अवरोध;

	शेष:
		net_warn_ratelimited("%s: (slave %s): Impossible agg select mode %d\n",
				     curr->slave->bond->dev->name,
				     curr->slave->dev->name,
				     __get_agg_selection_mode(curr->lag_ports));
		अवरोध;
	पूर्ण

	वापस best;
पूर्ण

अटल पूर्णांक agg_device_up(स्थिर काष्ठा aggregator *agg)
अणु
	काष्ठा port *port = agg->lag_ports;

	अगर (!port)
		वापस 0;

	क्रम (port = agg->lag_ports; port;
	     port = port->next_port_in_aggregator) अणु
		अगर (netअगर_running(port->slave->dev) &&
		    netअगर_carrier_ok(port->slave->dev))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ad_agg_selection_logic - select an aggregation group क्रम a team
 * @agg: the aggregator we're looking at
 * @update_slave_arr: Does slave array need update?
 *
 * It is assumed that only one aggregator may be selected क्रम a team.
 *
 * The logic of this function is to select the aggregator according to
 * the ad_select policy:
 *
 * BOND_AD_STABLE: select the aggregator with the most ports attached to
 * it, and to reselect the active aggregator only अगर the previous
 * aggregator has no more ports related to it.
 *
 * BOND_AD_BANDWIDTH: select the aggregator with the highest total
 * bandwidth, and reselect whenever a link state change takes place or the
 * set of slaves in the bond changes.
 *
 * BOND_AD_COUNT: select the aggregator with largest number of ports
 * (slaves), and reselect whenever a link state change takes place or the
 * set of slaves in the bond changes.
 *
 * FIXME: this function MUST be called with the first agg in the bond, or
 * __get_active_agg() won't work correctly. This function should be better
 * called with the bond itself, and retrieve the first agg from it.
 */
अटल व्योम ad_agg_selection_logic(काष्ठा aggregator *agg,
				   bool *update_slave_arr)
अणु
	काष्ठा aggregator *best, *active, *origin;
	काष्ठा bonding *bond = agg->slave->bond;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	काष्ठा port *port;

	rcu_पढ़ो_lock();
	origin = agg;
	active = __get_active_agg(agg);
	best = (active && agg_device_up(active)) ? active : शून्य;

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		agg = &(SLAVE_AD_INFO(slave)->aggregator);

		agg->is_active = 0;

		अगर (__agg_active_ports(agg) && agg_device_up(agg))
			best = ad_agg_selection_test(best, agg);
	पूर्ण

	अगर (best &&
	    __get_agg_selection_mode(best->lag_ports) == BOND_AD_STABLE) अणु
		/* For the STABLE policy, करोn't replace the old active
		 * aggregator अगर it's still active (it has an answering
		 * partner) or अगर both the best and active करोn't have an
		 * answering partner.
		 */
		अगर (active && active->lag_ports &&
		    __agg_active_ports(active) &&
		    (__agg_has_partner(active) ||
		     (!__agg_has_partner(active) &&
		     !__agg_has_partner(best)))) अणु
			अगर (!(!active->actor_oper_aggregator_key &&
			      best->actor_oper_aggregator_key)) अणु
				best = शून्य;
				active->is_active = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (best && (best == active)) अणु
		best = शून्य;
		active->is_active = 1;
	पूर्ण

	/* अगर there is new best aggregator, activate it */
	अगर (best) अणु
		netdev_dbg(bond->dev, "(slave %s): best Agg=%d; P=%d; a k=%d; p k=%d; Ind=%d; Act=%d\n",
			   best->slave ? best->slave->dev->name : "NULL",
			   best->aggregator_identअगरier, best->num_of_ports,
			   best->actor_oper_aggregator_key,
			   best->partner_oper_aggregator_key,
			   best->is_inभागidual, best->is_active);
		netdev_dbg(bond->dev, "(slave %s): best ports %p slave %p\n",
			   best->slave ? best->slave->dev->name : "NULL",
			   best->lag_ports, best->slave);

		bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
			agg = &(SLAVE_AD_INFO(slave)->aggregator);

			slave_dbg(bond->dev, slave->dev, "Agg=%d; P=%d; a k=%d; p k=%d; Ind=%d; Act=%d\n",
				  agg->aggregator_identअगरier, agg->num_of_ports,
				  agg->actor_oper_aggregator_key,
				  agg->partner_oper_aggregator_key,
				  agg->is_inभागidual, agg->is_active);
		पूर्ण

		/* check अगर any partner replies */
		अगर (best->is_inभागidual)
			net_warn_ratelimited("%s: Warning: No 802.3ad response from the link partner for any adapters in the bond\n",
					     bond->dev->name);

		best->is_active = 1;
		netdev_dbg(bond->dev, "(slave %s): LAG %d chosen as the active LAG\n",
			   best->slave ? best->slave->dev->name : "NULL",
			   best->aggregator_identअगरier);
		netdev_dbg(bond->dev, "(slave %s): Agg=%d; P=%d; a k=%d; p k=%d; Ind=%d; Act=%d\n",
			   best->slave ? best->slave->dev->name : "NULL",
			   best->aggregator_identअगरier, best->num_of_ports,
			   best->actor_oper_aggregator_key,
			   best->partner_oper_aggregator_key,
			   best->is_inभागidual, best->is_active);

		/* disable the ports that were related to the क्रमmer
		 * active_aggregator
		 */
		अगर (active) अणु
			क्रम (port = active->lag_ports; port;
			     port = port->next_port_in_aggregator) अणु
				__disable_port(port);
			पूर्ण
		पूर्ण
		/* Slave array needs update. */
		*update_slave_arr = true;
	पूर्ण

	/* अगर the selected aggregator is of join inभागiduals
	 * (partner_प्रणाली is शून्य), enable their ports
	 */
	active = __get_active_agg(origin);

	अगर (active) अणु
		अगर (!__agg_has_partner(active)) अणु
			क्रम (port = active->lag_ports; port;
			     port = port->next_port_in_aggregator) अणु
				__enable_port(port);
			पूर्ण
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	bond_3ad_set_carrier(bond);
पूर्ण

/**
 * ad_clear_agg - clear a given aggregator's parameters
 * @aggregator: the aggregator we're looking at
 */
अटल व्योम ad_clear_agg(काष्ठा aggregator *aggregator)
अणु
	अगर (aggregator) अणु
		aggregator->is_inभागidual = false;
		aggregator->actor_admin_aggregator_key = 0;
		aggregator->actor_oper_aggregator_key = 0;
		eth_zero_addr(aggregator->partner_प्रणाली.mac_addr_value);
		aggregator->partner_प्रणाली_priority = 0;
		aggregator->partner_oper_aggregator_key = 0;
		aggregator->receive_state = 0;
		aggregator->transmit_state = 0;
		aggregator->lag_ports = शून्य;
		aggregator->is_active = 0;
		aggregator->num_of_ports = 0;
		pr_debug("%s: LAG %d was cleared\n",
			 aggregator->slave ?
			 aggregator->slave->dev->name : "NULL",
			 aggregator->aggregator_identअगरier);
	पूर्ण
पूर्ण

/**
 * ad_initialize_agg - initialize a given aggregator's parameters
 * @aggregator: the aggregator we're looking at
 */
अटल व्योम ad_initialize_agg(काष्ठा aggregator *aggregator)
अणु
	अगर (aggregator) अणु
		ad_clear_agg(aggregator);

		eth_zero_addr(aggregator->aggregator_mac_address.mac_addr_value);
		aggregator->aggregator_identअगरier = 0;
		aggregator->slave = शून्य;
	पूर्ण
पूर्ण

/**
 * ad_initialize_port - initialize a given port's parameters
 * @port: the port we're looking at
 * @lacp_fast: boolean. whether fast periodic should be used
 */
अटल व्योम ad_initialize_port(काष्ठा port *port, पूर्णांक lacp_fast)
अणु
	अटल स्थिर काष्ठा port_params पंचांगpl = अणु
		.प्रणाली_priority = 0xffff,
		.key             = 1,
		.port_number     = 1,
		.port_priority   = 0xff,
		.port_state      = 1,
	पूर्ण;
	अटल स्थिर काष्ठा lacpdu lacpdu = अणु
		.subtype		= 0x01,
		.version_number = 0x01,
		.tlv_type_actor_info = 0x01,
		.actor_inक्रमmation_length = 0x14,
		.tlv_type_partner_info = 0x02,
		.partner_inक्रमmation_length = 0x14,
		.tlv_type_collector_info = 0x03,
		.collector_inक्रमmation_length = 0x10,
		.collector_max_delay = htons(AD_COLLECTOR_MAX_DELAY),
	पूर्ण;

	अगर (port) अणु
		port->actor_port_priority = 0xff;
		port->actor_port_aggregator_identअगरier = 0;
		port->ntt = false;
		port->actor_admin_port_state = LACP_STATE_AGGREGATION |
					       LACP_STATE_LACP_ACTIVITY;
		port->actor_oper_port_state  = LACP_STATE_AGGREGATION |
					       LACP_STATE_LACP_ACTIVITY;

		अगर (lacp_fast)
			port->actor_oper_port_state |= LACP_STATE_LACP_TIMEOUT;

		स_नकल(&port->partner_admin, &पंचांगpl, माप(पंचांगpl));
		स_नकल(&port->partner_oper, &पंचांगpl, माप(पंचांगpl));

		port->is_enabled = true;
		/* निजी parameters */
		port->sm_vars = AD_PORT_BEGIN | AD_PORT_LACP_ENABLED;
		port->sm_rx_state = 0;
		port->sm_rx_समयr_counter = 0;
		port->sm_periodic_state = 0;
		port->sm_periodic_समयr_counter = 0;
		port->sm_mux_state = 0;
		port->sm_mux_समयr_counter = 0;
		port->sm_tx_state = 0;
		port->aggregator = शून्य;
		port->next_port_in_aggregator = शून्य;
		port->transaction_id = 0;

		port->sm_churn_actor_समयr_counter = 0;
		port->sm_churn_actor_state = 0;
		port->churn_actor_count = 0;
		port->sm_churn_partner_समयr_counter = 0;
		port->sm_churn_partner_state = 0;
		port->churn_partner_count = 0;

		स_नकल(&port->lacpdu, &lacpdu, माप(lacpdu));
	पूर्ण
पूर्ण

/**
 * ad_enable_collecting_distributing - enable a port's transmit/receive
 * @port: the port we're looking at
 * @update_slave_arr: Does slave array need update?
 *
 * Enable @port अगर it's in an active aggregator
 */
अटल व्योम ad_enable_collecting_distributing(काष्ठा port *port,
					      bool *update_slave_arr)
अणु
	अगर (port->aggregator->is_active) अणु
		slave_dbg(port->slave->bond->dev, port->slave->dev,
			  "Enabling port %d (LAG %d)\n",
			  port->actor_port_number,
			  port->aggregator->aggregator_identअगरier);
		__enable_port(port);
		/* Slave array needs update */
		*update_slave_arr = true;
	पूर्ण
पूर्ण

/**
 * ad_disable_collecting_distributing - disable a port's transmit/receive
 * @port: the port we're looking at
 * @update_slave_arr: Does slave array need update?
 */
अटल व्योम ad_disable_collecting_distributing(काष्ठा port *port,
					       bool *update_slave_arr)
अणु
	अगर (port->aggregator &&
	    !MAC_ADDRESS_EQUAL(&(port->aggregator->partner_प्रणाली),
			       &(null_mac_addr))) अणु
		slave_dbg(port->slave->bond->dev, port->slave->dev,
			  "Disabling port %d (LAG %d)\n",
			  port->actor_port_number,
			  port->aggregator->aggregator_identअगरier);
		__disable_port(port);
		/* Slave array needs an update */
		*update_slave_arr = true;
	पूर्ण
पूर्ण

/**
 * ad_marker_info_received - handle receive of a Marker inक्रमmation frame
 * @marker_info: Marker info received
 * @port: the port we're looking at
 */
अटल व्योम ad_marker_info_received(काष्ठा bond_marker *marker_info,
				    काष्ठा port *port)
अणु
	काष्ठा bond_marker marker;

	atomic64_inc(&SLAVE_AD_INFO(port->slave)->stats.marker_rx);
	atomic64_inc(&BOND_AD_INFO(port->slave->bond).stats.marker_rx);

	/* copy the received marker data to the response marker */
	स_नकल(&marker, marker_info, माप(काष्ठा bond_marker));
	/* change the marker subtype to marker response */
	marker.tlv_type = AD_MARKER_RESPONSE_SUBTYPE;

	/* send the marker response */
	अगर (ad_marker_send(port, &marker) >= 0)
		slave_dbg(port->slave->bond->dev, port->slave->dev,
			  "Sent Marker Response on port %d\n",
			  port->actor_port_number);
पूर्ण

/**
 * ad_marker_response_received - handle receive of a marker response frame
 * @marker: marker PDU received
 * @port: the port we're looking at
 *
 * This function करोes nothing since we decided not to implement send and handle
 * response क्रम marker PDU's, in this stage, but only to respond to marker
 * inक्रमmation.
 */
अटल व्योम ad_marker_response_received(काष्ठा bond_marker *marker,
					काष्ठा port *port)
अणु
	atomic64_inc(&SLAVE_AD_INFO(port->slave)->stats.marker_resp_rx);
	atomic64_inc(&BOND_AD_INFO(port->slave->bond).stats.marker_resp_rx);

	/* DO NOTHING, SINCE WE DECIDED NOT TO IMPLEMENT THIS FEATURE FOR NOW */
पूर्ण

/* ========= AD exported functions to the मुख्य bonding code ========= */

/* Check aggregators status in team every T seconds */
#घोषणा AD_AGGREGATOR_SELECTION_TIMER  8

/**
 * bond_3ad_initiate_agg_selection - initate aggregator selection
 * @bond: bonding काष्ठा
 * @समयout: समयout value to set
 *
 * Set the aggregation selection समयr, to initiate an agg selection in
 * the very near future.  Called during first initialization, and during
 * any करोwn to up transitions of the bond.
 */
व्योम bond_3ad_initiate_agg_selection(काष्ठा bonding *bond, पूर्णांक समयout)
अणु
	BOND_AD_INFO(bond).agg_select_समयr = समयout;
पूर्ण

/**
 * bond_3ad_initialize - initialize a bond's 802.3ad parameters and काष्ठाures
 * @bond: bonding काष्ठा to work on
 * @tick_resolution: tick duration (millisecond resolution)
 *
 * Can be called only after the mac address of the bond is set.
 */
व्योम bond_3ad_initialize(काष्ठा bonding *bond, u16 tick_resolution)
अणु
	/* check that the bond is not initialized yet */
	अगर (!MAC_ADDRESS_EQUAL(&(BOND_AD_INFO(bond).प्रणाली.sys_mac_addr),
				bond->dev->dev_addr)) अणु

		BOND_AD_INFO(bond).aggregator_identअगरier = 0;

		BOND_AD_INFO(bond).प्रणाली.sys_priority =
			bond->params.ad_actor_sys_prio;
		अगर (is_zero_ether_addr(bond->params.ad_actor_प्रणाली))
			BOND_AD_INFO(bond).प्रणाली.sys_mac_addr =
			    *((काष्ठा mac_addr *)bond->dev->dev_addr);
		अन्यथा
			BOND_AD_INFO(bond).प्रणाली.sys_mac_addr =
			    *((काष्ठा mac_addr *)bond->params.ad_actor_प्रणाली);

		/* initialize how many बार this module is called in one
		 * second (should be about every 100ms)
		 */
		ad_ticks_per_sec = tick_resolution;

		bond_3ad_initiate_agg_selection(bond,
						AD_AGGREGATOR_SELECTION_TIMER *
						ad_ticks_per_sec);
	पूर्ण
पूर्ण

/**
 * bond_3ad_bind_slave - initialize a slave's port
 * @slave: slave काष्ठा to work on
 *
 * Returns:   0 on success
 *          < 0 on error
 */
व्योम bond_3ad_bind_slave(काष्ठा slave *slave)
अणु
	काष्ठा bonding *bond = bond_get_bond_by_slave(slave);
	काष्ठा port *port;
	काष्ठा aggregator *aggregator;

	/* check that the slave has not been initialized yet. */
	अगर (SLAVE_AD_INFO(slave)->port.slave != slave) अणु

		/* port initialization */
		port = &(SLAVE_AD_INFO(slave)->port);

		ad_initialize_port(port, bond->params.lacp_fast);

		port->slave = slave;
		port->actor_port_number = SLAVE_AD_INFO(slave)->id;
		/* key is determined according to the link speed, duplex and
		 * user key
		 */
		port->actor_admin_port_key = bond->params.ad_user_port_key << 6;
		ad_update_actor_keys(port, false);
		/* actor प्रणाली is the bond's प्रणाली */
		__ad_actor_update_port(port);
		/* tx समयr(to verअगरy that no more than MAX_TX_IN_SECOND
		 * lacpdu's are sent in one second)
		 */
		port->sm_tx_समयr_counter = ad_ticks_per_sec/AD_MAX_TX_IN_SECOND;

		__disable_port(port);

		/* aggregator initialization */
		aggregator = &(SLAVE_AD_INFO(slave)->aggregator);

		ad_initialize_agg(aggregator);

		aggregator->aggregator_mac_address = *((काष्ठा mac_addr *)bond->dev->dev_addr);
		aggregator->aggregator_identअगरier = ++BOND_AD_INFO(bond).aggregator_identअगरier;
		aggregator->slave = slave;
		aggregator->is_active = 0;
		aggregator->num_of_ports = 0;
	पूर्ण
पूर्ण

/**
 * bond_3ad_unbind_slave - deinitialize a slave's port
 * @slave: slave काष्ठा to work on
 *
 * Search क्रम the aggregator that is related to this port, हटाओ the
 * aggregator and assign another aggregator क्रम other port related to it
 * (अगर any), and हटाओ the port.
 */
व्योम bond_3ad_unbind_slave(काष्ठा slave *slave)
अणु
	काष्ठा port *port, *prev_port, *temp_port;
	काष्ठा aggregator *aggregator, *new_aggregator, *temp_aggregator;
	पूर्णांक select_new_active_agg = 0;
	काष्ठा bonding *bond = slave->bond;
	काष्ठा slave *slave_iter;
	काष्ठा list_head *iter;
	bool dummy_slave_update; /* Ignore this value as caller updates array */

	/* Sync against bond_3ad_state_machine_handler() */
	spin_lock_bh(&bond->mode_lock);
	aggregator = &(SLAVE_AD_INFO(slave)->aggregator);
	port = &(SLAVE_AD_INFO(slave)->port);

	/* अगर slave is null, the whole port is not initialized */
	अगर (!port->slave) अणु
		slave_warn(bond->dev, slave->dev, "Trying to unbind an uninitialized port\n");
		जाओ out;
	पूर्ण

	slave_dbg(bond->dev, slave->dev, "Unbinding Link Aggregation Group %d\n",
		  aggregator->aggregator_identअगरier);

	/* Tell the partner that this port is not suitable क्रम aggregation */
	port->actor_oper_port_state &= ~LACP_STATE_SYNCHRONIZATION;
	port->actor_oper_port_state &= ~LACP_STATE_COLLECTING;
	port->actor_oper_port_state &= ~LACP_STATE_DISTRIBUTING;
	port->actor_oper_port_state &= ~LACP_STATE_AGGREGATION;
	__update_lacpdu_from_port(port);
	ad_lacpdu_send(port);

	/* check अगर this aggregator is occupied */
	अगर (aggregator->lag_ports) अणु
		/* check अगर there are other ports related to this aggregator
		 * except the port related to this slave(thats ensure us that
		 * there is a reason to search क्रम new aggregator, and that we
		 * will find one
		 */
		अगर ((aggregator->lag_ports != port) ||
		    (aggregator->lag_ports->next_port_in_aggregator)) अणु
			/* find new aggregator क्रम the related port(s) */
			bond_क्रम_each_slave(bond, slave_iter, iter) अणु
				new_aggregator = &(SLAVE_AD_INFO(slave_iter)->aggregator);
				/* अगर the new aggregator is empty, or it is
				 * connected to our port only
				 */
				अगर (!new_aggregator->lag_ports ||
				    ((new_aggregator->lag_ports == port) &&
				     !new_aggregator->lag_ports->next_port_in_aggregator))
					अवरोध;
			पूर्ण
			अगर (!slave_iter)
				new_aggregator = शून्य;

			/* अगर new aggregator found, copy the aggregator's
			 * parameters and connect the related lag_ports to the
			 * new aggregator
			 */
			अगर ((new_aggregator) && ((!new_aggregator->lag_ports) || ((new_aggregator->lag_ports == port) && !new_aggregator->lag_ports->next_port_in_aggregator))) अणु
				slave_dbg(bond->dev, slave->dev, "Some port(s) related to LAG %d - replacing with LAG %d\n",
					  aggregator->aggregator_identअगरier,
					  new_aggregator->aggregator_identअगरier);

				अगर ((new_aggregator->lag_ports == port) &&
				    new_aggregator->is_active) अणु
					slave_info(bond->dev, slave->dev, "Removing an active aggregator\n");
					select_new_active_agg = 1;
				पूर्ण

				new_aggregator->is_inभागidual = aggregator->is_inभागidual;
				new_aggregator->actor_admin_aggregator_key = aggregator->actor_admin_aggregator_key;
				new_aggregator->actor_oper_aggregator_key = aggregator->actor_oper_aggregator_key;
				new_aggregator->partner_प्रणाली = aggregator->partner_प्रणाली;
				new_aggregator->partner_प्रणाली_priority = aggregator->partner_प्रणाली_priority;
				new_aggregator->partner_oper_aggregator_key = aggregator->partner_oper_aggregator_key;
				new_aggregator->receive_state = aggregator->receive_state;
				new_aggregator->transmit_state = aggregator->transmit_state;
				new_aggregator->lag_ports = aggregator->lag_ports;
				new_aggregator->is_active = aggregator->is_active;
				new_aggregator->num_of_ports = aggregator->num_of_ports;

				/* update the inक्रमmation that is written on
				 * the ports about the aggregator
				 */
				क्रम (temp_port = aggregator->lag_ports; temp_port;
				     temp_port = temp_port->next_port_in_aggregator) अणु
					temp_port->aggregator = new_aggregator;
					temp_port->actor_port_aggregator_identअगरier = new_aggregator->aggregator_identअगरier;
				पूर्ण

				ad_clear_agg(aggregator);

				अगर (select_new_active_agg)
					ad_agg_selection_logic(__get_first_agg(port),
							       &dummy_slave_update);
			पूर्ण अन्यथा अणु
				slave_warn(bond->dev, slave->dev, "unbinding aggregator, and could not find a new aggregator for its ports\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			/* in हाल that the only port related to this
			 * aggregator is the one we want to हटाओ
			 */
			select_new_active_agg = aggregator->is_active;
			ad_clear_agg(aggregator);
			अगर (select_new_active_agg) अणु
				slave_info(bond->dev, slave->dev, "Removing an active aggregator\n");
				/* select new active aggregator */
				temp_aggregator = __get_first_agg(port);
				अगर (temp_aggregator)
					ad_agg_selection_logic(temp_aggregator,
							       &dummy_slave_update);
			पूर्ण
		पूर्ण
	पूर्ण

	slave_dbg(bond->dev, slave->dev, "Unbinding port %d\n", port->actor_port_number);

	/* find the aggregator that this port is connected to */
	bond_क्रम_each_slave(bond, slave_iter, iter) अणु
		temp_aggregator = &(SLAVE_AD_INFO(slave_iter)->aggregator);
		prev_port = शून्य;
		/* search the port in the aggregator's related ports */
		क्रम (temp_port = temp_aggregator->lag_ports; temp_port;
		     prev_port = temp_port,
		     temp_port = temp_port->next_port_in_aggregator) अणु
			अगर (temp_port == port) अणु
				/* the aggregator found - detach the port from
				 * this aggregator
				 */
				अगर (prev_port)
					prev_port->next_port_in_aggregator = temp_port->next_port_in_aggregator;
				अन्यथा
					temp_aggregator->lag_ports = temp_port->next_port_in_aggregator;
				temp_aggregator->num_of_ports--;
				अगर (__agg_active_ports(temp_aggregator) == 0) अणु
					select_new_active_agg = temp_aggregator->is_active;
					ad_clear_agg(temp_aggregator);
					अगर (select_new_active_agg) अणु
						slave_info(bond->dev, slave->dev, "Removing an active aggregator\n");
						/* select new active aggregator */
						ad_agg_selection_logic(__get_first_agg(port),
							               &dummy_slave_update);
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	port->slave = शून्य;

out:
	spin_unlock_bh(&bond->mode_lock);
पूर्ण

/**
 * bond_3ad_update_ad_actor_settings - reflect change of actor settings to ports
 * @bond: bonding काष्ठा to work on
 *
 * If an ad_actor setting माला_लो changed we need to update the inभागidual port
 * settings so the bond device will use the new values when it माला_लो upped.
 */
व्योम bond_3ad_update_ad_actor_settings(काष्ठा bonding *bond)
अणु
	काष्ठा list_head *iter;
	काष्ठा slave *slave;

	ASSERT_RTNL();

	BOND_AD_INFO(bond).प्रणाली.sys_priority = bond->params.ad_actor_sys_prio;
	अगर (is_zero_ether_addr(bond->params.ad_actor_प्रणाली))
		BOND_AD_INFO(bond).प्रणाली.sys_mac_addr =
		    *((काष्ठा mac_addr *)bond->dev->dev_addr);
	अन्यथा
		BOND_AD_INFO(bond).प्रणाली.sys_mac_addr =
		    *((काष्ठा mac_addr *)bond->params.ad_actor_प्रणाली);

	spin_lock_bh(&bond->mode_lock);
	bond_क्रम_each_slave(bond, slave, iter) अणु
		काष्ठा port *port = &(SLAVE_AD_INFO(slave))->port;

		__ad_actor_update_port(port);
		port->ntt = true;
	पूर्ण
	spin_unlock_bh(&bond->mode_lock);
पूर्ण

/**
 * bond_3ad_state_machine_handler - handle state machines समयout
 * @work: work context to fetch bonding काष्ठा to work on from
 *
 * The state machine handling concept in this module is to check every tick
 * which state machine should operate any function. The execution order is
 * round robin, so when we have an पूर्णांकeraction between state machines, the
 * reply of one to each other might be delayed until next tick.
 *
 * This function also complete the initialization when the agg_select_समयr
 * बार out, and it selects an aggregator क्रम the ports that are yet not
 * related to any aggregator, and selects the active aggregator क्रम a bond.
 */
व्योम bond_3ad_state_machine_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bonding *bond = container_of(work, काष्ठा bonding,
					    ad_work.work);
	काष्ठा aggregator *aggregator;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	काष्ठा port *port;
	bool should_notअगरy_rtnl = BOND_SLAVE_NOTIFY_LATER;
	bool update_slave_arr = false;

	/* Lock to protect data accessed by all (e.g., port->sm_vars) and
	 * against running with bond_3ad_unbind_slave. ad_rx_machine may run
	 * concurrently due to incoming LACPDU as well.
	 */
	spin_lock_bh(&bond->mode_lock);
	rcu_पढ़ो_lock();

	/* check अगर there are any slaves */
	अगर (!bond_has_slaves(bond))
		जाओ re_arm;

	/* check अगर agg_select_समयr समयr after initialize is समयd out */
	अगर (BOND_AD_INFO(bond).agg_select_समयr &&
	    !(--BOND_AD_INFO(bond).agg_select_समयr)) अणु
		slave = bond_first_slave_rcu(bond);
		port = slave ? &(SLAVE_AD_INFO(slave)->port) : शून्य;

		/* select the active aggregator क्रम the bond */
		अगर (port) अणु
			अगर (!port->slave) अणु
				net_warn_ratelimited("%s: Warning: bond's first port is uninitialized\n",
						     bond->dev->name);
				जाओ re_arm;
			पूर्ण

			aggregator = __get_first_agg(port);
			ad_agg_selection_logic(aggregator, &update_slave_arr);
		पूर्ण
		bond_3ad_set_carrier(bond);
	पूर्ण

	/* क्रम each port run the state machines */
	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		port = &(SLAVE_AD_INFO(slave)->port);
		अगर (!port->slave) अणु
			net_warn_ratelimited("%s: Warning: Found an uninitialized port\n",
					    bond->dev->name);
			जाओ re_arm;
		पूर्ण

		ad_rx_machine(शून्य, port);
		ad_periodic_machine(port);
		ad_port_selection_logic(port, &update_slave_arr);
		ad_mux_machine(port, &update_slave_arr);
		ad_tx_machine(port);
		ad_churn_machine(port);

		/* turn off the BEGIN bit, since we alपढ़ोy handled it */
		अगर (port->sm_vars & AD_PORT_BEGIN)
			port->sm_vars &= ~AD_PORT_BEGIN;
	पूर्ण

re_arm:
	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		अगर (slave->should_notअगरy) अणु
			should_notअगरy_rtnl = BOND_SLAVE_NOTIFY_NOW;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	spin_unlock_bh(&bond->mode_lock);

	अगर (update_slave_arr)
		bond_slave_arr_work_rearm(bond, 0);

	अगर (should_notअगरy_rtnl && rtnl_trylock()) अणु
		bond_slave_state_notअगरy(bond);
		rtnl_unlock();
	पूर्ण
	queue_delayed_work(bond->wq, &bond->ad_work, ad_delta_in_ticks);
पूर्ण

/**
 * bond_3ad_rx_indication - handle a received frame
 * @lacpdu: received lacpdu
 * @slave: slave काष्ठा to work on
 *
 * It is assumed that frames that were sent on this NIC करोn't वापसed as new
 * received frames (loopback). Since only the payload is given to this
 * function, it check क्रम loopback.
 */
अटल पूर्णांक bond_3ad_rx_indication(काष्ठा lacpdu *lacpdu, काष्ठा slave *slave)
अणु
	काष्ठा bonding *bond = slave->bond;
	पूर्णांक ret = RX_HANDLER_ANOTHER;
	काष्ठा bond_marker *marker;
	काष्ठा port *port;
	atomic64_t *stat;

	port = &(SLAVE_AD_INFO(slave)->port);
	अगर (!port->slave) अणु
		net_warn_ratelimited("%s: Warning: port of slave %s is uninitialized\n",
				     slave->dev->name, slave->bond->dev->name);
		वापस ret;
	पूर्ण

	चयन (lacpdu->subtype) अणु
	हाल AD_TYPE_LACPDU:
		ret = RX_HANDLER_CONSUMED;
		slave_dbg(slave->bond->dev, slave->dev,
			  "Received LACPDU on port %d\n",
			  port->actor_port_number);
		/* Protect against concurrent state machines */
		spin_lock(&slave->bond->mode_lock);
		ad_rx_machine(lacpdu, port);
		spin_unlock(&slave->bond->mode_lock);
		अवरोध;
	हाल AD_TYPE_MARKER:
		ret = RX_HANDLER_CONSUMED;
		/* No need to convert fields to Little Endian since we
		 * करोn't use the marker's fields.
		 */
		marker = (काष्ठा bond_marker *)lacpdu;
		चयन (marker->tlv_type) अणु
		हाल AD_MARKER_INFORMATION_SUBTYPE:
			slave_dbg(slave->bond->dev, slave->dev, "Received Marker Information on port %d\n",
				  port->actor_port_number);
			ad_marker_info_received(marker, port);
			अवरोध;
		हाल AD_MARKER_RESPONSE_SUBTYPE:
			slave_dbg(slave->bond->dev, slave->dev, "Received Marker Response on port %d\n",
				  port->actor_port_number);
			ad_marker_response_received(marker, port);
			अवरोध;
		शेष:
			slave_dbg(slave->bond->dev, slave->dev, "Received an unknown Marker subtype on port %d\n",
				  port->actor_port_number);
			stat = &SLAVE_AD_INFO(slave)->stats.marker_unknown_rx;
			atomic64_inc(stat);
			stat = &BOND_AD_INFO(bond).stats.marker_unknown_rx;
			atomic64_inc(stat);
		पूर्ण
		अवरोध;
	शेष:
		atomic64_inc(&SLAVE_AD_INFO(slave)->stats.lacpdu_unknown_rx);
		atomic64_inc(&BOND_AD_INFO(bond).stats.lacpdu_unknown_rx);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ad_update_actor_keys - Update the oper / admin keys क्रम a port based on
 * its current speed and duplex settings.
 *
 * @port: the port we'are looking at
 * @reset: Boolean to just reset the speed and the duplex part of the key
 *
 * The logic to change the oper / admin keys is:
 * (a) A full duplex port can participate in LACP with partner.
 * (b) When the speed is changed, LACP need to be reinitiated.
 */
अटल व्योम ad_update_actor_keys(काष्ठा port *port, bool reset)
अणु
	u8 duplex = 0;
	u16 ospeed = 0, speed = 0;
	u16 old_oper_key = port->actor_oper_port_key;

	port->actor_admin_port_key &= ~(AD_SPEED_KEY_MASKS|AD_DUPLEX_KEY_MASKS);
	अगर (!reset) अणु
		speed = __get_link_speed(port);
		ospeed = (old_oper_key & AD_SPEED_KEY_MASKS) >> 1;
		duplex = __get_duplex(port);
		port->actor_admin_port_key |= (speed << 1) | duplex;
	पूर्ण
	port->actor_oper_port_key = port->actor_admin_port_key;

	अगर (old_oper_key != port->actor_oper_port_key) अणु
		/* Only 'duplex' port participates in LACP */
		अगर (duplex)
			port->sm_vars |= AD_PORT_LACP_ENABLED;
		अन्यथा
			port->sm_vars &= ~AD_PORT_LACP_ENABLED;

		अगर (!reset) अणु
			अगर (!speed) अणु
				slave_err(port->slave->bond->dev,
					  port->slave->dev,
					  "speed changed to 0 on port %d\n",
					  port->actor_port_number);
			पूर्ण अन्यथा अगर (duplex && ospeed != speed) अणु
				/* Speed change restarts LACP state-machine */
				port->sm_vars |= AD_PORT_BEGIN;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * bond_3ad_adapter_speed_duplex_changed - handle a slave's speed / duplex
 * change indication
 *
 * @slave: slave काष्ठा to work on
 *
 * Handle reselection of aggregator (अगर needed) क्रम this port.
 */
व्योम bond_3ad_adapter_speed_duplex_changed(काष्ठा slave *slave)
अणु
	काष्ठा port *port;

	port = &(SLAVE_AD_INFO(slave)->port);

	/* अगर slave is null, the whole port is not initialized */
	अगर (!port->slave) अणु
		slave_warn(slave->bond->dev, slave->dev,
			   "speed/duplex changed for uninitialized port\n");
		वापस;
	पूर्ण

	spin_lock_bh(&slave->bond->mode_lock);
	ad_update_actor_keys(port, false);
	spin_unlock_bh(&slave->bond->mode_lock);
	slave_dbg(slave->bond->dev, slave->dev, "Port %d changed speed/duplex\n",
		  port->actor_port_number);
पूर्ण

/**
 * bond_3ad_handle_link_change - handle a slave's link status change indication
 * @slave: slave काष्ठा to work on
 * @link: whether the link is now up or करोwn
 *
 * Handle reselection of aggregator (अगर needed) क्रम this port.
 */
व्योम bond_3ad_handle_link_change(काष्ठा slave *slave, अक्षर link)
अणु
	काष्ठा aggregator *agg;
	काष्ठा port *port;
	bool dummy;

	port = &(SLAVE_AD_INFO(slave)->port);

	/* अगर slave is null, the whole port is not initialized */
	अगर (!port->slave) अणु
		slave_warn(slave->bond->dev, slave->dev, "link status changed for uninitialized port\n");
		वापस;
	पूर्ण

	spin_lock_bh(&slave->bond->mode_lock);
	/* on link करोwn we are zeroing duplex and speed since
	 * some of the adaptors(ce1000.lan) report full duplex/speed
	 * instead of N/A(duplex) / 0(speed).
	 *
	 * on link up we are क्रमcing recheck on the duplex and speed since
	 * some of he adaptors(ce1000.lan) report.
	 */
	अगर (link == BOND_LINK_UP) अणु
		port->is_enabled = true;
		ad_update_actor_keys(port, false);
	पूर्ण अन्यथा अणु
		/* link has failed */
		port->is_enabled = false;
		ad_update_actor_keys(port, true);
	पूर्ण
	agg = __get_first_agg(port);
	ad_agg_selection_logic(agg, &dummy);

	spin_unlock_bh(&slave->bond->mode_lock);

	slave_dbg(slave->bond->dev, slave->dev, "Port %d changed link status to %s\n",
		  port->actor_port_number,
		  link == BOND_LINK_UP ? "UP" : "DOWN");

	/* RTNL is held and mode_lock is released so it's safe
	 * to update slave_array here.
	 */
	bond_update_slave_arr(slave->bond, शून्य);
पूर्ण

/**
 * bond_3ad_set_carrier - set link state क्रम bonding master
 * @bond: bonding काष्ठाure
 *
 * अगर we have an active aggregator, we're up, if not, we're करोwn.
 * Presumes that we cannot have an active aggregator अगर there are
 * no slaves with link up.
 *
 * This behavior complies with IEEE 802.3 section 43.3.9.
 *
 * Called by bond_set_carrier(). Return zero अगर carrier state करोes not
 * change, nonzero अगर it करोes.
 */
पूर्णांक bond_3ad_set_carrier(काष्ठा bonding *bond)
अणु
	काष्ठा aggregator *active;
	काष्ठा slave *first_slave;
	पूर्णांक ret = 1;

	rcu_पढ़ो_lock();
	first_slave = bond_first_slave_rcu(bond);
	अगर (!first_slave) अणु
		ret = 0;
		जाओ out;
	पूर्ण
	active = __get_active_agg(&(SLAVE_AD_INFO(first_slave)->aggregator));
	अगर (active) अणु
		/* are enough slaves available to consider link up? */
		अगर (__agg_active_ports(active) < bond->params.min_links) अणु
			अगर (netअगर_carrier_ok(bond->dev)) अणु
				netअगर_carrier_off(bond->dev);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!netअगर_carrier_ok(bond->dev)) अणु
			netअगर_carrier_on(bond->dev);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (netअगर_carrier_ok(bond->dev)) अणु
		netअगर_carrier_off(bond->dev);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * __bond_3ad_get_active_agg_info - get inक्रमmation of the active aggregator
 * @bond: bonding काष्ठा to work on
 * @ad_info: ad_info काष्ठा to fill with the bond's info
 *
 * Returns:   0 on success
 *          < 0 on error
 */
पूर्णांक __bond_3ad_get_active_agg_info(काष्ठा bonding *bond,
				   काष्ठा ad_info *ad_info)
अणु
	काष्ठा aggregator *aggregator = शून्य;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	काष्ठा port *port;

	bond_क्रम_each_slave_rcu(bond, slave, iter) अणु
		port = &(SLAVE_AD_INFO(slave)->port);
		अगर (port->aggregator && port->aggregator->is_active) अणु
			aggregator = port->aggregator;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!aggregator)
		वापस -1;

	ad_info->aggregator_id = aggregator->aggregator_identअगरier;
	ad_info->ports = __agg_active_ports(aggregator);
	ad_info->actor_key = aggregator->actor_oper_aggregator_key;
	ad_info->partner_key = aggregator->partner_oper_aggregator_key;
	ether_addr_copy(ad_info->partner_प्रणाली,
			aggregator->partner_प्रणाली.mac_addr_value);
	वापस 0;
पूर्ण

पूर्णांक bond_3ad_get_active_agg_info(काष्ठा bonding *bond, काष्ठा ad_info *ad_info)
अणु
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = __bond_3ad_get_active_agg_info(bond, ad_info);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

पूर्णांक bond_3ad_lacpdu_recv(स्थिर काष्ठा sk_buff *skb, काष्ठा bonding *bond,
			 काष्ठा slave *slave)
अणु
	काष्ठा lacpdu *lacpdu, _lacpdu;

	अगर (skb->protocol != PKT_TYPE_LACPDU)
		वापस RX_HANDLER_ANOTHER;

	अगर (!MAC_ADDRESS_EQUAL(eth_hdr(skb)->h_dest, lacpdu_mcast_addr))
		वापस RX_HANDLER_ANOTHER;

	lacpdu = skb_header_poपूर्णांकer(skb, 0, माप(_lacpdu), &_lacpdu);
	अगर (!lacpdu) अणु
		atomic64_inc(&SLAVE_AD_INFO(slave)->stats.lacpdu_illegal_rx);
		atomic64_inc(&BOND_AD_INFO(bond).stats.lacpdu_illegal_rx);
		वापस RX_HANDLER_ANOTHER;
	पूर्ण

	वापस bond_3ad_rx_indication(lacpdu, slave);
पूर्ण

/**
 * bond_3ad_update_lacp_rate - change the lacp rate
 * @bond: bonding काष्ठा
 *
 * When modअगरy lacp_rate parameter via sysfs,
 * update actor_oper_port_state of each port.
 *
 * Hold bond->mode_lock,
 * so we can modअगरy port->actor_oper_port_state,
 * no matter bond is up or करोwn.
 */
व्योम bond_3ad_update_lacp_rate(काष्ठा bonding *bond)
अणु
	काष्ठा port *port = शून्य;
	काष्ठा list_head *iter;
	काष्ठा slave *slave;
	पूर्णांक lacp_fast;

	lacp_fast = bond->params.lacp_fast;
	spin_lock_bh(&bond->mode_lock);
	bond_क्रम_each_slave(bond, slave, iter) अणु
		port = &(SLAVE_AD_INFO(slave)->port);
		अगर (lacp_fast)
			port->actor_oper_port_state |= LACP_STATE_LACP_TIMEOUT;
		अन्यथा
			port->actor_oper_port_state &= ~LACP_STATE_LACP_TIMEOUT;
	पूर्ण
	spin_unlock_bh(&bond->mode_lock);
पूर्ण

माप_प्रकार bond_3ad_stats_size(व्योम)
अणु
	वापस nla_total_size_64bit(माप(u64)) + /* BOND_3AD_STAT_LACPDU_RX */
	       nla_total_size_64bit(माप(u64)) + /* BOND_3AD_STAT_LACPDU_TX */
	       nla_total_size_64bit(माप(u64)) + /* BOND_3AD_STAT_LACPDU_UNKNOWN_RX */
	       nla_total_size_64bit(माप(u64)) + /* BOND_3AD_STAT_LACPDU_ILLEGAL_RX */
	       nla_total_size_64bit(माप(u64)) + /* BOND_3AD_STAT_MARKER_RX */
	       nla_total_size_64bit(माप(u64)) + /* BOND_3AD_STAT_MARKER_TX */
	       nla_total_size_64bit(माप(u64)) + /* BOND_3AD_STAT_MARKER_RESP_RX */
	       nla_total_size_64bit(माप(u64)) + /* BOND_3AD_STAT_MARKER_RESP_TX */
	       nla_total_size_64bit(माप(u64)); /* BOND_3AD_STAT_MARKER_UNKNOWN_RX */
पूर्ण

पूर्णांक bond_3ad_stats_fill(काष्ठा sk_buff *skb, काष्ठा bond_3ad_stats *stats)
अणु
	u64 val;

	val = atomic64_पढ़ो(&stats->lacpdu_rx);
	अगर (nla_put_u64_64bit(skb, BOND_3AD_STAT_LACPDU_RX, val,
			      BOND_3AD_STAT_PAD))
		वापस -EMSGSIZE;
	val = atomic64_पढ़ो(&stats->lacpdu_tx);
	अगर (nla_put_u64_64bit(skb, BOND_3AD_STAT_LACPDU_TX, val,
			      BOND_3AD_STAT_PAD))
		वापस -EMSGSIZE;
	val = atomic64_पढ़ो(&stats->lacpdu_unknown_rx);
	अगर (nla_put_u64_64bit(skb, BOND_3AD_STAT_LACPDU_UNKNOWN_RX, val,
			      BOND_3AD_STAT_PAD))
		वापस -EMSGSIZE;
	val = atomic64_पढ़ो(&stats->lacpdu_illegal_rx);
	अगर (nla_put_u64_64bit(skb, BOND_3AD_STAT_LACPDU_ILLEGAL_RX, val,
			      BOND_3AD_STAT_PAD))
		वापस -EMSGSIZE;

	val = atomic64_पढ़ो(&stats->marker_rx);
	अगर (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_RX, val,
			      BOND_3AD_STAT_PAD))
		वापस -EMSGSIZE;
	val = atomic64_पढ़ो(&stats->marker_tx);
	अगर (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_TX, val,
			      BOND_3AD_STAT_PAD))
		वापस -EMSGSIZE;
	val = atomic64_पढ़ो(&stats->marker_resp_rx);
	अगर (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_RESP_RX, val,
			      BOND_3AD_STAT_PAD))
		वापस -EMSGSIZE;
	val = atomic64_पढ़ो(&stats->marker_resp_tx);
	अगर (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_RESP_TX, val,
			      BOND_3AD_STAT_PAD))
		वापस -EMSGSIZE;
	val = atomic64_पढ़ो(&stats->marker_unknown_rx);
	अगर (nla_put_u64_64bit(skb, BOND_3AD_STAT_MARKER_UNKNOWN_RX, val,
			      BOND_3AD_STAT_PAD))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण
