<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999 - 2010 Intel Corporation.
 * Copyright (C) 2010 OKI SEMICONDUCTOR Co., LTD.
 *
 * This code was derived from the Intel e1000e Linux driver.
 */

#समावेश "pch_gbe.h"
#समावेश <linux/module.h>	/* क्रम __MODULE_STRING */

#घोषणा OPTION_UNSET   -1
#घोषणा OPTION_DISABLED 0
#घोषणा OPTION_ENABLED  1

/*
 * TxDescriptors - Transmit Descriptor Count
 * @Valid Range:   PCH_GBE_MIN_TXD - PCH_GBE_MAX_TXD
 * @Default Value: PCH_GBE_DEFAULT_TXD
 */
अटल पूर्णांक TxDescriptors = OPTION_UNSET;
module_param(TxDescriptors, पूर्णांक, 0);
MODULE_PARM_DESC(TxDescriptors, "Number of transmit descriptors");

/*
 * RxDescriptors -Receive Descriptor Count
 * @Valid Range:   PCH_GBE_MIN_RXD - PCH_GBE_MAX_RXD
 * @Default Value: PCH_GBE_DEFAULT_RXD
 */
अटल पूर्णांक RxDescriptors = OPTION_UNSET;
module_param(RxDescriptors, पूर्णांक, 0);
MODULE_PARM_DESC(RxDescriptors, "Number of receive descriptors");

/*
 * Speed - User Specअगरied Speed Override
 * @Valid Range: 0, 10, 100, 1000
 *   - 0:    स्वतः-negotiate at all supported speeds
 *   - 10:   only link at 10 Mbps
 *   - 100:  only link at 100 Mbps
 *   - 1000: only link at 1000 Mbps
 * @Default Value: 0
 */
अटल पूर्णांक Speed = OPTION_UNSET;
module_param(Speed, पूर्णांक, 0);
MODULE_PARM_DESC(Speed, "Speed setting");

/*
 * Duplex - User Specअगरied Duplex Override
 * @Valid Range: 0-2
 *   - 0:  स्वतः-negotiate क्रम duplex
 *   - 1:  only link at half duplex
 *   - 2:  only link at full duplex
 * @Default Value: 0
 */
अटल पूर्णांक Duplex = OPTION_UNSET;
module_param(Duplex, पूर्णांक, 0);
MODULE_PARM_DESC(Duplex, "Duplex setting");

#घोषणा HALF_DUPLEX 1
#घोषणा FULL_DUPLEX 2

/*
 * AutoNeg - Auto-negotiation Advertisement Override
 * @Valid Range: 0x01-0x0F, 0x20-0x2F
 *
 *       The AutoNeg value is a bit mask describing which speed and duplex
 *       combinations should be advertised during स्वतः-negotiation.
 *       The supported speed and duplex modes are listed below
 *
 *       Bit           7     6     5      4      3     2     1      0
 *       Speed (Mbps)  N/A   N/A   1000   N/A    100   100   10     10
 *       Duplex                    Full          Full  Half  Full   Half
 *
 * @Default Value: 0x2F (copper)
 */
अटल पूर्णांक AutoNeg = OPTION_UNSET;
module_param(AutoNeg, पूर्णांक, 0);
MODULE_PARM_DESC(AutoNeg, "Advertised auto-negotiation setting");

#घोषणा PHY_ADVERTISE_10_HALF      0x0001
#घोषणा PHY_ADVERTISE_10_FULL      0x0002
#घोषणा PHY_ADVERTISE_100_HALF     0x0004
#घोषणा PHY_ADVERTISE_100_FULL     0x0008
#घोषणा PHY_ADVERTISE_1000_HALF    0x0010 /* Not used, just FYI */
#घोषणा PHY_ADVERTISE_1000_FULL    0x0020
#घोषणा PCH_AUTONEG_ADVERTISE_DEFAULT   0x2F

/*
 * FlowControl - User Specअगरied Flow Control Override
 * @Valid Range: 0-3
 *    - 0:  No Flow Control
 *    - 1:  Rx only, respond to PAUSE frames but करो not generate them
 *    - 2:  Tx only, generate PAUSE frames but ignore them on receive
 *    - 3:  Full Flow Control Support
 * @Default Value: Read flow control settings from the EEPROM
 */
अटल पूर्णांक FlowControl = OPTION_UNSET;
module_param(FlowControl, पूर्णांक, 0);
MODULE_PARM_DESC(FlowControl, "Flow Control setting");

/*
 * XsumRX - Receive Checksum Offload Enable/Disable
 * @Valid Range: 0, 1
 *    - 0:  disables all checksum offload
 *    - 1:  enables receive IP/TCP/UDP checksum offload
 * @Default Value: PCH_GBE_DEFAULT_RX_CSUM
 */
अटल पूर्णांक XsumRX = OPTION_UNSET;
module_param(XsumRX, पूर्णांक, 0);
MODULE_PARM_DESC(XsumRX, "Disable or enable Receive Checksum offload");

#घोषणा PCH_GBE_DEFAULT_RX_CSUM             true	/* trueorfalse */

/*
 * XsumTX - Transmit Checksum Offload Enable/Disable
 * @Valid Range: 0, 1
 *    - 0:  disables all checksum offload
 *    - 1:  enables transmit IP/TCP/UDP checksum offload
 * @Default Value: PCH_GBE_DEFAULT_TX_CSUM
 */
अटल पूर्णांक XsumTX = OPTION_UNSET;
module_param(XsumTX, पूर्णांक, 0);
MODULE_PARM_DESC(XsumTX, "Disable or enable Transmit Checksum offload");

#घोषणा PCH_GBE_DEFAULT_TX_CSUM             true	/* trueorfalse */

/*
 * pch_gbe_option - Force the MAC's flow control settings
 * @hw:	            Poपूर्णांकer to the HW काष्ठाure
 * Returns:
 *	0:			Successful.
 *	Negative value:		Failed.
 */
काष्ठा pch_gbe_option अणु
	क्रमागत अणु enable_option, range_option, list_option पूर्ण type;
	अक्षर *name;
	अक्षर *err;
	पूर्णांक  def;
	जोड़ अणु
		काष्ठा अणु /* range_option info */
			पूर्णांक min;
			पूर्णांक max;
		पूर्ण r;
		काष्ठा अणु /* list_option info */
			पूर्णांक nr;
			स्थिर काष्ठा pch_gbe_opt_list अणु पूर्णांक i; अक्षर *str; पूर्ण *p;
		पूर्ण l;
	पूर्ण arg;
पूर्ण;

अटल स्थिर काष्ठा pch_gbe_opt_list speed_list[] = अणु
	अणु 0, "" पूर्ण,
	अणु SPEED_10, "" पूर्ण,
	अणु SPEED_100, "" पूर्ण,
	अणु SPEED_1000, "" पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pch_gbe_opt_list dplx_list[] = अणु
	अणु 0, "" पूर्ण,
	अणु HALF_DUPLEX, "" पूर्ण,
	अणु FULL_DUPLEX, "" पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pch_gbe_opt_list an_list[] =
	#घोषणा AA "AutoNeg advertising "
	अणुअणु 0x01, AA "10/HD" पूर्ण,
	 अणु 0x02, AA "10/FD" पूर्ण,
	 अणु 0x03, AA "10/FD, 10/HD" पूर्ण,
	 अणु 0x04, AA "100/HD" पूर्ण,
	 अणु 0x05, AA "100/HD, 10/HD" पूर्ण,
	 अणु 0x06, AA "100/HD, 10/FD" पूर्ण,
	 अणु 0x07, AA "100/HD, 10/FD, 10/HD" पूर्ण,
	 अणु 0x08, AA "100/FD" पूर्ण,
	 अणु 0x09, AA "100/FD, 10/HD" पूर्ण,
	 अणु 0x0a, AA "100/FD, 10/FD" पूर्ण,
	 अणु 0x0b, AA "100/FD, 10/FD, 10/HD" पूर्ण,
	 अणु 0x0c, AA "100/FD, 100/HD" पूर्ण,
	 अणु 0x0d, AA "100/FD, 100/HD, 10/HD" पूर्ण,
	 अणु 0x0e, AA "100/FD, 100/HD, 10/FD" पूर्ण,
	 अणु 0x0f, AA "100/FD, 100/HD, 10/FD, 10/HD" पूर्ण,
	 अणु 0x20, AA "1000/FD" पूर्ण,
	 अणु 0x21, AA "1000/FD, 10/HD" पूर्ण,
	 अणु 0x22, AA "1000/FD, 10/FD" पूर्ण,
	 अणु 0x23, AA "1000/FD, 10/FD, 10/HD" पूर्ण,
	 अणु 0x24, AA "1000/FD, 100/HD" पूर्ण,
	 अणु 0x25, AA "1000/FD, 100/HD, 10/HD" पूर्ण,
	 अणु 0x26, AA "1000/FD, 100/HD, 10/FD" पूर्ण,
	 अणु 0x27, AA "1000/FD, 100/HD, 10/FD, 10/HD" पूर्ण,
	 अणु 0x28, AA "1000/FD, 100/FD" पूर्ण,
	 अणु 0x29, AA "1000/FD, 100/FD, 10/HD" पूर्ण,
	 अणु 0x2a, AA "1000/FD, 100/FD, 10/FD" पूर्ण,
	 अणु 0x2b, AA "1000/FD, 100/FD, 10/FD, 10/HD" पूर्ण,
	 अणु 0x2c, AA "1000/FD, 100/FD, 100/HD" पूर्ण,
	 अणु 0x2d, AA "1000/FD, 100/FD, 100/HD, 10/HD" पूर्ण,
	 अणु 0x2e, AA "1000/FD, 100/FD, 100/HD, 10/FD" पूर्ण,
	 अणु 0x2f, AA "1000/FD, 100/FD, 100/HD, 10/FD, 10/HD" पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pch_gbe_opt_list fc_list[] = अणु
	अणु PCH_GBE_FC_NONE, "Flow Control Disabled" पूर्ण,
	अणु PCH_GBE_FC_RX_PAUSE, "Flow Control Receive Only" पूर्ण,
	अणु PCH_GBE_FC_TX_PAUSE, "Flow Control Transmit Only" पूर्ण,
	अणु PCH_GBE_FC_FULL, "Flow Control Enabled" पूर्ण
पूर्ण;

/**
 * pch_gbe_validate_option - Validate option
 * @value:    value
 * @opt:      option
 * @adapter:  Board निजी काष्ठाure
 * Returns:
 *	0:			Successful.
 *	Negative value:		Failed.
 */
अटल पूर्णांक pch_gbe_validate_option(पूर्णांक *value,
				    स्थिर काष्ठा pch_gbe_option *opt,
				    काष्ठा pch_gbe_adapter *adapter)
अणु
	अगर (*value == OPTION_UNSET) अणु
		*value = opt->def;
		वापस 0;
	पूर्ण

	चयन (opt->type) अणु
	हाल enable_option:
		चयन (*value) अणु
		हाल OPTION_ENABLED:
			netdev_dbg(adapter->netdev, "%s Enabled\n", opt->name);
			वापस 0;
		हाल OPTION_DISABLED:
			netdev_dbg(adapter->netdev, "%s Disabled\n", opt->name);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल range_option:
		अगर (*value >= opt->arg.r.min && *value <= opt->arg.r.max) अणु
			netdev_dbg(adapter->netdev, "%s set to %i\n",
				   opt->name, *value);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल list_option: अणु
		पूर्णांक i;
		स्थिर काष्ठा pch_gbe_opt_list *ent;

		क्रम (i = 0; i < opt->arg.l.nr; i++) अणु
			ent = &opt->arg.l.p[i];
			अगर (*value == ent->i) अणु
				अगर (ent->str[0] != '\0')
					netdev_dbg(adapter->netdev, "%s\n",
						   ent->str);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	netdev_dbg(adapter->netdev, "Invalid %s value specified (%i) %s\n",
		   opt->name, *value, opt->err);
	*value = opt->def;
	वापस -1;
पूर्ण

/**
 * pch_gbe_check_copper_options - Range Checking क्रम Link Options, Copper Version
 * @adapter:  Board निजी काष्ठाure
 */
अटल व्योम pch_gbe_check_copper_options(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	पूर्णांक speed, dplx;

	अणु /* Speed */
		अटल स्थिर काष्ठा pch_gbe_option opt = अणु
			.type = list_option,
			.name = "Speed",
			.err  = "parameter ignored",
			.def  = 0,
			.arg  = अणु .l = अणु .nr = (पूर्णांक)ARRAY_SIZE(speed_list),
					 .p = speed_list पूर्ण पूर्ण
		पूर्ण;
		speed = Speed;
		pch_gbe_validate_option(&speed, &opt, adapter);
	पूर्ण
	अणु /* Duplex */
		अटल स्थिर काष्ठा pch_gbe_option opt = अणु
			.type = list_option,
			.name = "Duplex",
			.err  = "parameter ignored",
			.def  = 0,
			.arg  = अणु .l = अणु .nr = (पूर्णांक)ARRAY_SIZE(dplx_list),
					 .p = dplx_list पूर्ण पूर्ण
		पूर्ण;
		dplx = Duplex;
		pch_gbe_validate_option(&dplx, &opt, adapter);
	पूर्ण

	अणु /* Autoneg */
		अटल स्थिर काष्ठा pch_gbe_option opt = अणु
			.type = list_option,
			.name = "AutoNeg",
			.err  = "parameter ignored",
			.def  = PCH_AUTONEG_ADVERTISE_DEFAULT,
			.arg  = अणु .l = अणु .nr = (पूर्णांक)ARRAY_SIZE(an_list),
					 .p = an_listपूर्ण पूर्ण
		पूर्ण;
		अगर (speed || dplx) अणु
			netdev_dbg(adapter->netdev,
				   "AutoNeg specified along with Speed or Duplex, AutoNeg parameter ignored\n");
			hw->phy.स्वतःneg_advertised = opt.def;
		पूर्ण अन्यथा अणु
			पूर्णांक पंचांगp = AutoNeg;

			pch_gbe_validate_option(&पंचांगp, &opt, adapter);
			hw->phy.स्वतःneg_advertised = पंचांगp;
		पूर्ण
	पूर्ण

	चयन (speed + dplx) अणु
	हाल 0:
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 1;
		अगर ((speed || dplx))
			netdev_dbg(adapter->netdev,
				   "Speed and duplex autonegotiation enabled\n");
		hw->mac.link_speed = SPEED_10;
		hw->mac.link_duplex = DUPLEX_HALF;
		अवरोध;
	हाल HALF_DUPLEX:
		netdev_dbg(adapter->netdev,
			   "Half Duplex specified without Speed\n");
		netdev_dbg(adapter->netdev,
			   "Using Autonegotiation at Half Duplex only\n");
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 1;
		hw->phy.स्वतःneg_advertised = PHY_ADVERTISE_10_HALF |
						PHY_ADVERTISE_100_HALF;
		hw->mac.link_speed = SPEED_10;
		hw->mac.link_duplex = DUPLEX_HALF;
		अवरोध;
	हाल FULL_DUPLEX:
		netdev_dbg(adapter->netdev,
			   "Full Duplex specified without Speed\n");
		netdev_dbg(adapter->netdev,
			   "Using Autonegotiation at Full Duplex only\n");
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 1;
		hw->phy.स्वतःneg_advertised = PHY_ADVERTISE_10_FULL |
						PHY_ADVERTISE_100_FULL |
						PHY_ADVERTISE_1000_FULL;
		hw->mac.link_speed = SPEED_10;
		hw->mac.link_duplex = DUPLEX_FULL;
		अवरोध;
	हाल SPEED_10:
		netdev_dbg(adapter->netdev,
			   "10 Mbps Speed specified without Duplex\n");
		netdev_dbg(adapter->netdev,
			   "Using Autonegotiation at 10 Mbps only\n");
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 1;
		hw->phy.स्वतःneg_advertised = PHY_ADVERTISE_10_HALF |
						PHY_ADVERTISE_10_FULL;
		hw->mac.link_speed = SPEED_10;
		hw->mac.link_duplex = DUPLEX_HALF;
		अवरोध;
	हाल SPEED_10 + HALF_DUPLEX:
		netdev_dbg(adapter->netdev, "Forcing to 10 Mbps Half Duplex\n");
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 0;
		hw->phy.स्वतःneg_advertised = 0;
		hw->mac.link_speed = SPEED_10;
		hw->mac.link_duplex = DUPLEX_HALF;
		अवरोध;
	हाल SPEED_10 + FULL_DUPLEX:
		netdev_dbg(adapter->netdev, "Forcing to 10 Mbps Full Duplex\n");
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 0;
		hw->phy.स्वतःneg_advertised = 0;
		hw->mac.link_speed = SPEED_10;
		hw->mac.link_duplex = DUPLEX_FULL;
		अवरोध;
	हाल SPEED_100:
		netdev_dbg(adapter->netdev,
			   "100 Mbps Speed specified without Duplex\n");
		netdev_dbg(adapter->netdev,
			   "Using Autonegotiation at 100 Mbps only\n");
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 1;
		hw->phy.स्वतःneg_advertised = PHY_ADVERTISE_100_HALF |
						PHY_ADVERTISE_100_FULL;
		hw->mac.link_speed = SPEED_100;
		hw->mac.link_duplex = DUPLEX_HALF;
		अवरोध;
	हाल SPEED_100 + HALF_DUPLEX:
		netdev_dbg(adapter->netdev,
			   "Forcing to 100 Mbps Half Duplex\n");
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 0;
		hw->phy.स्वतःneg_advertised = 0;
		hw->mac.link_speed = SPEED_100;
		hw->mac.link_duplex = DUPLEX_HALF;
		अवरोध;
	हाल SPEED_100 + FULL_DUPLEX:
		netdev_dbg(adapter->netdev,
			   "Forcing to 100 Mbps Full Duplex\n");
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 0;
		hw->phy.स्वतःneg_advertised = 0;
		hw->mac.link_speed = SPEED_100;
		hw->mac.link_duplex = DUPLEX_FULL;
		अवरोध;
	हाल SPEED_1000:
		netdev_dbg(adapter->netdev,
			   "1000 Mbps Speed specified without Duplex\n");
		जाओ full_duplex_only;
	हाल SPEED_1000 + HALF_DUPLEX:
		netdev_dbg(adapter->netdev,
			   "Half Duplex is not supported at 1000 Mbps\n");
		fallthrough;
	हाल SPEED_1000 + FULL_DUPLEX:
full_duplex_only:
		netdev_dbg(adapter->netdev,
			   "Using Autonegotiation at 1000 Mbps Full Duplex only\n");
		hw->mac.स्वतःneg = hw->mac.fc_स्वतःneg = 1;
		hw->phy.स्वतःneg_advertised = PHY_ADVERTISE_1000_FULL;
		hw->mac.link_speed = SPEED_1000;
		hw->mac.link_duplex = DUPLEX_FULL;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/**
 * pch_gbe_check_options - Range Checking क्रम Command Line Parameters
 * @adapter:  Board निजी काष्ठाure
 */
व्योम pch_gbe_check_options(काष्ठा pch_gbe_adapter *adapter)
अणु
	काष्ठा pch_gbe_hw *hw = &adapter->hw;
	काष्ठा net_device *dev = adapter->netdev;
	पूर्णांक val;

	अणु /* Transmit Descriptor Count */
		अटल स्थिर काष्ठा pch_gbe_option opt = अणु
			.type = range_option,
			.name = "Transmit Descriptors",
			.err  = "using default of "
				__MODULE_STRING(PCH_GBE_DEFAULT_TXD),
			.def  = PCH_GBE_DEFAULT_TXD,
			.arg  = अणु .r = अणु .min = PCH_GBE_MIN_TXD,
					 .max = PCH_GBE_MAX_TXD पूर्ण पूर्ण
		पूर्ण;
		काष्ठा pch_gbe_tx_ring *tx_ring = adapter->tx_ring;
		tx_ring->count = TxDescriptors;
		pch_gbe_validate_option(&tx_ring->count, &opt, adapter);
		tx_ring->count = roundup(tx_ring->count,
					PCH_GBE_TX_DESC_MULTIPLE);
	पूर्ण
	अणु /* Receive Descriptor Count */
		अटल स्थिर काष्ठा pch_gbe_option opt = अणु
			.type = range_option,
			.name = "Receive Descriptors",
			.err  = "using default of "
				__MODULE_STRING(PCH_GBE_DEFAULT_RXD),
			.def  = PCH_GBE_DEFAULT_RXD,
			.arg  = अणु .r = अणु .min = PCH_GBE_MIN_RXD,
					 .max = PCH_GBE_MAX_RXD पूर्ण पूर्ण
		पूर्ण;
		काष्ठा pch_gbe_rx_ring *rx_ring = adapter->rx_ring;
		rx_ring->count = RxDescriptors;
		pch_gbe_validate_option(&rx_ring->count, &opt, adapter);
		rx_ring->count = roundup(rx_ring->count,
				PCH_GBE_RX_DESC_MULTIPLE);
	पूर्ण
	अणु /* Checksum Offload Enable/Disable */
		अटल स्थिर काष्ठा pch_gbe_option opt = अणु
			.type = enable_option,
			.name = "Checksum Offload",
			.err  = "defaulting to Enabled",
			.def  = PCH_GBE_DEFAULT_RX_CSUM
		पूर्ण;
		val = XsumRX;
		pch_gbe_validate_option(&val, &opt, adapter);
		अगर (!val)
			dev->features &= ~NETIF_F_RXCSUM;
	पूर्ण
	अणु /* Checksum Offload Enable/Disable */
		अटल स्थिर काष्ठा pch_gbe_option opt = अणु
			.type = enable_option,
			.name = "Checksum Offload",
			.err  = "defaulting to Enabled",
			.def  = PCH_GBE_DEFAULT_TX_CSUM
		पूर्ण;
		val = XsumTX;
		pch_gbe_validate_option(&val, &opt, adapter);
		अगर (!val)
			dev->features &= ~NETIF_F_CSUM_MASK;
	पूर्ण
	अणु /* Flow Control */
		अटल स्थिर काष्ठा pch_gbe_option opt = अणु
			.type = list_option,
			.name = "Flow Control",
			.err  = "reading default settings from EEPROM",
			.def  = PCH_GBE_FC_DEFAULT,
			.arg  = अणु .l = अणु .nr = (पूर्णांक)ARRAY_SIZE(fc_list),
					 .p = fc_list पूर्ण पूर्ण
		पूर्ण;
		पूर्णांक पंचांगp = FlowControl;

		pch_gbe_validate_option(&पंचांगp, &opt, adapter);
		hw->mac.fc = पंचांगp;
	पूर्ण

	pch_gbe_check_copper_options(adapter);
पूर्ण
