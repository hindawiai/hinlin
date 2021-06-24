<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2006 Intel Corporation. */

#समावेश "e1000.h"

/* This is the only thing that needs to be changed to adjust the
 * maximum number of ports that the driver can manage.
 */

#घोषणा E1000_MAX_NIC 32

#घोषणा OPTION_UNSET   -1
#घोषणा OPTION_DISABLED 0
#घोषणा OPTION_ENABLED  1

/* All parameters are treated the same, as an पूर्णांकeger array of values.
 * This macro just reduces the need to repeat the same declaration code
 * over and over (plus this helps to aव्योम typo bugs).
 */

#घोषणा E1000_PARAM_INIT अणु [0 ... E1000_MAX_NIC] = OPTION_UNSET पूर्ण
#घोषणा E1000_PARAM(X, desc) \
	अटल पूर्णांक X[E1000_MAX_NIC+1] = E1000_PARAM_INIT; \
	अटल अचिन्हित पूर्णांक num_##X; \
	module_param_array_named(X, X, पूर्णांक, &num_##X, 0); \
	MODULE_PARM_DESC(X, desc);

/* Transmit Descriptor Count
 *
 * Valid Range: 80-256 क्रम 82542 and 82543 gigabit ethernet controllers
 * Valid Range: 80-4096 क्रम 82544 and newer
 *
 * Default Value: 256
 */
E1000_PARAM(TxDescriptors, "Number of transmit descriptors");

/* Receive Descriptor Count
 *
 * Valid Range: 80-256 क्रम 82542 and 82543 gigabit ethernet controllers
 * Valid Range: 80-4096 क्रम 82544 and newer
 *
 * Default Value: 256
 */
E1000_PARAM(RxDescriptors, "Number of receive descriptors");

/* User Specअगरied Speed Override
 *
 * Valid Range: 0, 10, 100, 1000
 *  - 0    - स्वतः-negotiate at all supported speeds
 *  - 10   - only link at 10 Mbps
 *  - 100  - only link at 100 Mbps
 *  - 1000 - only link at 1000 Mbps
 *
 * Default Value: 0
 */
E1000_PARAM(Speed, "Speed setting");

/* User Specअगरied Duplex Override
 *
 * Valid Range: 0-2
 *  - 0 - स्वतः-negotiate क्रम duplex
 *  - 1 - only link at half duplex
 *  - 2 - only link at full duplex
 *
 * Default Value: 0
 */
E1000_PARAM(Duplex, "Duplex setting");

/* Auto-negotiation Advertisement Override
 *
 * Valid Range: 0x01-0x0F, 0x20-0x2F (copper); 0x20 (fiber)
 *
 * The AutoNeg value is a bit mask describing which speed and duplex
 * combinations should be advertised during स्वतः-negotiation.
 * The supported speed and duplex modes are listed below
 *
 * Bit           7     6     5      4      3     2     1      0
 * Speed (Mbps)  N/A   N/A   1000   N/A    100   100   10     10
 * Duplex                    Full          Full  Half  Full   Half
 *
 * Default Value: 0x2F (copper); 0x20 (fiber)
 */
E1000_PARAM(AutoNeg, "Advertised auto-negotiation setting");
#घोषणा AUTONEG_ADV_DEFAULT  0x2F
#घोषणा AUTONEG_ADV_MASK     0x2F

/* User Specअगरied Flow Control Override
 *
 * Valid Range: 0-3
 *  - 0 - No Flow Control
 *  - 1 - Rx only, respond to PAUSE frames but करो not generate them
 *  - 2 - Tx only, generate PAUSE frames but ignore them on receive
 *  - 3 - Full Flow Control Support
 *
 * Default Value: Read flow control settings from the EEPROM
 */
E1000_PARAM(FlowControl, "Flow Control setting");
#घोषणा FLOW_CONTROL_DEFAULT FLOW_CONTROL_FULL

/* XsumRX - Receive Checksum Offload Enable/Disable
 *
 * Valid Range: 0, 1
 *  - 0 - disables all checksum offload
 *  - 1 - enables receive IP/TCP/UDP checksum offload
 *        on 82543 and newer -based NICs
 *
 * Default Value: 1
 */
E1000_PARAM(XsumRX, "Disable or enable Receive Checksum offload");

/* Transmit Interrupt Delay in units of 1.024 microseconds
 *  Tx पूर्णांकerrupt delay needs to typically be set to something non zero
 *
 * Valid Range: 0-65535
 */
E1000_PARAM(TxIntDelay, "Transmit Interrupt Delay");
#घोषणा DEFAULT_TIDV                   8
#घोषणा MAX_TXDELAY               0xFFFF
#घोषणा MIN_TXDELAY                    0

/* Transmit Absolute Interrupt Delay in units of 1.024 microseconds
 *
 * Valid Range: 0-65535
 */
E1000_PARAM(TxAbsIntDelay, "Transmit Absolute Interrupt Delay");
#घोषणा DEFAULT_TADV                  32
#घोषणा MAX_TXABSDELAY            0xFFFF
#घोषणा MIN_TXABSDELAY                 0

/* Receive Interrupt Delay in units of 1.024 microseconds
 *   hardware will likely hang अगर you set this to anything but zero.
 *
 * Valid Range: 0-65535
 */
E1000_PARAM(RxIntDelay, "Receive Interrupt Delay");
#घोषणा DEFAULT_RDTR                   0
#घोषणा MAX_RXDELAY               0xFFFF
#घोषणा MIN_RXDELAY                    0

/* Receive Absolute Interrupt Delay in units of 1.024 microseconds
 *
 * Valid Range: 0-65535
 */
E1000_PARAM(RxAbsIntDelay, "Receive Absolute Interrupt Delay");
#घोषणा DEFAULT_RADV                   8
#घोषणा MAX_RXABSDELAY            0xFFFF
#घोषणा MIN_RXABSDELAY                 0

/* Interrupt Throttle Rate (पूर्णांकerrupts/sec)
 *
 * Valid Range: 100-100000 (0=off, 1=dynamic, 3=dynamic conservative)
 */
E1000_PARAM(InterruptThrottleRate, "Interrupt Throttling Rate");
#घोषणा DEFAULT_ITR                    3
#घोषणा MAX_ITR                   100000
#घोषणा MIN_ITR                      100

/* Enable Smart Power Down of the PHY
 *
 * Valid Range: 0, 1
 *
 * Default Value: 0 (disabled)
 */
E1000_PARAM(SmartPowerDownEnable, "Enable PHY smart power down");

काष्ठा e1000_option अणु
	क्रमागत अणु enable_option, range_option, list_option पूर्ण type;
	स्थिर अक्षर *name;
	स्थिर अक्षर *err;
	पूर्णांक def;
	जोड़ अणु
		काष्ठा अणु /* range_option info */
			पूर्णांक min;
			पूर्णांक max;
		पूर्ण r;
		काष्ठा अणु /* list_option info */
			पूर्णांक nr;
			स्थिर काष्ठा e1000_opt_list अणु पूर्णांक i; अक्षर *str; पूर्ण *p;
		पूर्ण l;
	पूर्ण arg;
पूर्ण;

अटल पूर्णांक e1000_validate_option(अचिन्हित पूर्णांक *value,
				 स्थिर काष्ठा e1000_option *opt,
				 काष्ठा e1000_adapter *adapter)
अणु
	अगर (*value == OPTION_UNSET) अणु
		*value = opt->def;
		वापस 0;
	पूर्ण

	चयन (opt->type) अणु
	हाल enable_option:
		चयन (*value) अणु
		हाल OPTION_ENABLED:
			e_dev_info("%s Enabled\n", opt->name);
			वापस 0;
		हाल OPTION_DISABLED:
			e_dev_info("%s Disabled\n", opt->name);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल range_option:
		अगर (*value >= opt->arg.r.min && *value <= opt->arg.r.max) अणु
			e_dev_info("%s set to %i\n", opt->name, *value);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल list_option: अणु
		पूर्णांक i;
		स्थिर काष्ठा e1000_opt_list *ent;

		क्रम (i = 0; i < opt->arg.l.nr; i++) अणु
			ent = &opt->arg.l.p[i];
			अगर (*value == ent->i) अणु
				अगर (ent->str[0] != '\0')
					e_dev_info("%s\n", ent->str);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	e_dev_info("Invalid %s value specified (%i) %s\n",
	       opt->name, *value, opt->err);
	*value = opt->def;
	वापस -1;
पूर्ण

अटल व्योम e1000_check_fiber_options(काष्ठा e1000_adapter *adapter);
अटल व्योम e1000_check_copper_options(काष्ठा e1000_adapter *adapter);

/**
 * e1000_check_options - Range Checking क्रम Command Line Parameters
 * @adapter: board निजी काष्ठाure
 *
 * This routine checks all command line parameters क्रम valid user
 * input.  If an invalid value is given, or अगर no user specअगरied
 * value exists, a शेष value is used.  The final value is stored
 * in a variable in the adapter काष्ठाure.
 **/
व्योम e1000_check_options(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_option opt;
	पूर्णांक bd = adapter->bd_number;

	अगर (bd >= E1000_MAX_NIC) अणु
		e_dev_warn("Warning: no configuration for board #%i "
			   "using defaults for all values\n", bd);
	पूर्ण

	अणु /* Transmit Descriptor Count */
		काष्ठा e1000_tx_ring *tx_ring = adapter->tx_ring;
		पूर्णांक i;
		e1000_mac_type mac_type = adapter->hw.mac_type;

		opt = (काष्ठा e1000_option) अणु
			.type = range_option,
			.name = "Transmit Descriptors",
			.err  = "using default of "
				__MODULE_STRING(E1000_DEFAULT_TXD),
			.def  = E1000_DEFAULT_TXD,
			.arg  = अणु .r = अणु
				.min = E1000_MIN_TXD,
				.max = mac_type < e1000_82544 ? E1000_MAX_TXD : E1000_MAX_82544_TXD
				पूर्णपूर्ण
		पूर्ण;

		अगर (num_TxDescriptors > bd) अणु
			tx_ring->count = TxDescriptors[bd];
			e1000_validate_option(&tx_ring->count, &opt, adapter);
			tx_ring->count = ALIGN(tx_ring->count,
						REQ_TX_DESCRIPTOR_MULTIPLE);
		पूर्ण अन्यथा अणु
			tx_ring->count = opt.def;
		पूर्ण
		क्रम (i = 0; i < adapter->num_tx_queues; i++)
			tx_ring[i].count = tx_ring->count;
	पूर्ण
	अणु /* Receive Descriptor Count */
		काष्ठा e1000_rx_ring *rx_ring = adapter->rx_ring;
		पूर्णांक i;
		e1000_mac_type mac_type = adapter->hw.mac_type;

		opt = (काष्ठा e1000_option) अणु
			.type = range_option,
			.name = "Receive Descriptors",
			.err  = "using default of "
				__MODULE_STRING(E1000_DEFAULT_RXD),
			.def  = E1000_DEFAULT_RXD,
			.arg  = अणु .r = अणु
				.min = E1000_MIN_RXD,
				.max = mac_type < e1000_82544 ? E1000_MAX_RXD :
				       E1000_MAX_82544_RXD
			पूर्णपूर्ण
		पूर्ण;

		अगर (num_RxDescriptors > bd) अणु
			rx_ring->count = RxDescriptors[bd];
			e1000_validate_option(&rx_ring->count, &opt, adapter);
			rx_ring->count = ALIGN(rx_ring->count,
						REQ_RX_DESCRIPTOR_MULTIPLE);
		पूर्ण अन्यथा अणु
			rx_ring->count = opt.def;
		पूर्ण
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			rx_ring[i].count = rx_ring->count;
	पूर्ण
	अणु /* Checksum Offload Enable/Disable */
		opt = (काष्ठा e1000_option) अणु
			.type = enable_option,
			.name = "Checksum Offload",
			.err  = "defaulting to Enabled",
			.def  = OPTION_ENABLED
		पूर्ण;

		अगर (num_XsumRX > bd) अणु
			अचिन्हित पूर्णांक rx_csum = XsumRX[bd];
			e1000_validate_option(&rx_csum, &opt, adapter);
			adapter->rx_csum = rx_csum;
		पूर्ण अन्यथा अणु
			adapter->rx_csum = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Flow Control */

		अटल स्थिर काष्ठा e1000_opt_list fc_list[] = अणु
		       अणु E1000_FC_NONE, "Flow Control Disabled" पूर्ण,
		       अणु E1000_FC_RX_PAUSE, "Flow Control Receive Only" पूर्ण,
		       अणु E1000_FC_TX_PAUSE, "Flow Control Transmit Only" पूर्ण,
		       अणु E1000_FC_FULL, "Flow Control Enabled" पूर्ण,
		       अणु E1000_FC_DEFAULT, "Flow Control Hardware Default" पूर्ण
		पूर्ण;

		opt = (काष्ठा e1000_option) अणु
			.type = list_option,
			.name = "Flow Control",
			.err  = "reading default settings from EEPROM",
			.def  = E1000_FC_DEFAULT,
			.arg  = अणु .l = अणु .nr = ARRAY_SIZE(fc_list),
					 .p = fc_list पूर्णपूर्ण
		पूर्ण;

		अगर (num_FlowControl > bd) अणु
			अचिन्हित पूर्णांक fc = FlowControl[bd];
			e1000_validate_option(&fc, &opt, adapter);
			adapter->hw.fc = adapter->hw.original_fc = fc;
		पूर्ण अन्यथा अणु
			adapter->hw.fc = adapter->hw.original_fc = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Transmit Interrupt Delay */
		opt = (काष्ठा e1000_option) अणु
			.type = range_option,
			.name = "Transmit Interrupt Delay",
			.err  = "using default of " __MODULE_STRING(DEFAULT_TIDV),
			.def  = DEFAULT_TIDV,
			.arg  = अणु .r = अणु .min = MIN_TXDELAY,
					 .max = MAX_TXDELAY पूर्णपूर्ण
		पूर्ण;

		अगर (num_TxIntDelay > bd) अणु
			adapter->tx_पूर्णांक_delay = TxIntDelay[bd];
			e1000_validate_option(&adapter->tx_पूर्णांक_delay, &opt,
			                      adapter);
		पूर्ण अन्यथा अणु
			adapter->tx_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Transmit Absolute Interrupt Delay */
		opt = (काष्ठा e1000_option) अणु
			.type = range_option,
			.name = "Transmit Absolute Interrupt Delay",
			.err  = "using default of " __MODULE_STRING(DEFAULT_TADV),
			.def  = DEFAULT_TADV,
			.arg  = अणु .r = अणु .min = MIN_TXABSDELAY,
					 .max = MAX_TXABSDELAY पूर्णपूर्ण
		पूर्ण;

		अगर (num_TxAbsIntDelay > bd) अणु
			adapter->tx_असल_पूर्णांक_delay = TxAbsIntDelay[bd];
			e1000_validate_option(&adapter->tx_असल_पूर्णांक_delay, &opt,
					      adapter);
		पूर्ण अन्यथा अणु
			adapter->tx_असल_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Receive Interrupt Delay */
		opt = (काष्ठा e1000_option) अणु
			.type = range_option,
			.name = "Receive Interrupt Delay",
			.err  = "using default of " __MODULE_STRING(DEFAULT_RDTR),
			.def  = DEFAULT_RDTR,
			.arg  = अणु .r = अणु .min = MIN_RXDELAY,
					 .max = MAX_RXDELAY पूर्णपूर्ण
		पूर्ण;

		अगर (num_RxIntDelay > bd) अणु
			adapter->rx_पूर्णांक_delay = RxIntDelay[bd];
			e1000_validate_option(&adapter->rx_पूर्णांक_delay, &opt,
					      adapter);
		पूर्ण अन्यथा अणु
			adapter->rx_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Receive Absolute Interrupt Delay */
		opt = (काष्ठा e1000_option) अणु
			.type = range_option,
			.name = "Receive Absolute Interrupt Delay",
			.err  = "using default of " __MODULE_STRING(DEFAULT_RADV),
			.def  = DEFAULT_RADV,
			.arg  = अणु .r = अणु .min = MIN_RXABSDELAY,
					 .max = MAX_RXABSDELAY पूर्णपूर्ण
		पूर्ण;

		अगर (num_RxAbsIntDelay > bd) अणु
			adapter->rx_असल_पूर्णांक_delay = RxAbsIntDelay[bd];
			e1000_validate_option(&adapter->rx_असल_पूर्णांक_delay, &opt,
					      adapter);
		पूर्ण अन्यथा अणु
			adapter->rx_असल_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Interrupt Throttling Rate */
		opt = (काष्ठा e1000_option) अणु
			.type = range_option,
			.name = "Interrupt Throttling Rate (ints/sec)",
			.err  = "using default of " __MODULE_STRING(DEFAULT_ITR),
			.def  = DEFAULT_ITR,
			.arg  = अणु .r = अणु .min = MIN_ITR,
					 .max = MAX_ITR पूर्णपूर्ण
		पूर्ण;

		अगर (num_InterruptThrottleRate > bd) अणु
			adapter->itr = InterruptThrottleRate[bd];
			चयन (adapter->itr) अणु
			हाल 0:
				e_dev_info("%s turned off\n", opt.name);
				अवरोध;
			हाल 1:
				e_dev_info("%s set to dynamic mode\n",
					   opt.name);
				adapter->itr_setting = adapter->itr;
				adapter->itr = 20000;
				अवरोध;
			हाल 3:
				e_dev_info("%s set to dynamic conservative "
					   "mode\n", opt.name);
				adapter->itr_setting = adapter->itr;
				adapter->itr = 20000;
				अवरोध;
			हाल 4:
				e_dev_info("%s set to simplified "
					   "(2000-8000) ints mode\n", opt.name);
				adapter->itr_setting = adapter->itr;
				अवरोध;
			शेष:
				e1000_validate_option(&adapter->itr, &opt,
						      adapter);
				/* save the setting, because the dynamic bits
				 * change itr.
				 * clear the lower two bits because they are
				 * used as control
				 */
				adapter->itr_setting = adapter->itr & ~3;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			adapter->itr_setting = opt.def;
			adapter->itr = 20000;
		पूर्ण
	पूर्ण
	अणु /* Smart Power Down */
		opt = (काष्ठा e1000_option) अणु
			.type = enable_option,
			.name = "PHY Smart Power Down",
			.err  = "defaulting to Disabled",
			.def  = OPTION_DISABLED
		पूर्ण;

		अगर (num_SmartPowerDownEnable > bd) अणु
			अचिन्हित पूर्णांक spd = SmartPowerDownEnable[bd];
			e1000_validate_option(&spd, &opt, adapter);
			adapter->smart_घातer_करोwn = spd;
		पूर्ण अन्यथा अणु
			adapter->smart_घातer_करोwn = opt.def;
		पूर्ण
	पूर्ण

	चयन (adapter->hw.media_type) अणु
	हाल e1000_media_type_fiber:
	हाल e1000_media_type_पूर्णांकernal_serdes:
		e1000_check_fiber_options(adapter);
		अवरोध;
	हाल e1000_media_type_copper:
		e1000_check_copper_options(adapter);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/**
 * e1000_check_fiber_options - Range Checking क्रम Link Options, Fiber Version
 * @adapter: board निजी काष्ठाure
 *
 * Handles speed and duplex options on fiber adapters
 **/
अटल व्योम e1000_check_fiber_options(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक bd = adapter->bd_number;
	अगर (num_Speed > bd) अणु
		e_dev_info("Speed not valid for fiber adapters, parameter "
			   "ignored\n");
	पूर्ण

	अगर (num_Duplex > bd) अणु
		e_dev_info("Duplex not valid for fiber adapters, parameter "
			   "ignored\n");
	पूर्ण

	अगर ((num_AutoNeg > bd) && (AutoNeg[bd] != 0x20)) अणु
		e_dev_info("AutoNeg other than 1000/Full is not valid for fiber"
			   "adapters, parameter ignored\n");
	पूर्ण
पूर्ण

/**
 * e1000_check_copper_options - Range Checking क्रम Link Options, Copper Version
 * @adapter: board निजी काष्ठाure
 *
 * Handles speed and duplex options on copper adapters
 **/
अटल व्योम e1000_check_copper_options(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_option opt;
	अचिन्हित पूर्णांक speed, dplx, an;
	पूर्णांक bd = adapter->bd_number;

	अणु /* Speed */
		अटल स्थिर काष्ठा e1000_opt_list speed_list[] = अणु
			अणु          0, "" पूर्ण,
			अणु   SPEED_10, "" पूर्ण,
			अणु  SPEED_100, "" पूर्ण,
			अणु SPEED_1000, "" पूर्णपूर्ण;

		opt = (काष्ठा e1000_option) अणु
			.type = list_option,
			.name = "Speed",
			.err  = "parameter ignored",
			.def  = 0,
			.arg  = अणु .l = अणु .nr = ARRAY_SIZE(speed_list),
					 .p = speed_list पूर्णपूर्ण
		पूर्ण;

		अगर (num_Speed > bd) अणु
			speed = Speed[bd];
			e1000_validate_option(&speed, &opt, adapter);
		पूर्ण अन्यथा अणु
			speed = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Duplex */
		अटल स्थिर काष्ठा e1000_opt_list dplx_list[] = अणु
			अणु           0, "" पूर्ण,
			अणु HALF_DUPLEX, "" पूर्ण,
			अणु FULL_DUPLEX, "" पूर्णपूर्ण;

		opt = (काष्ठा e1000_option) अणु
			.type = list_option,
			.name = "Duplex",
			.err  = "parameter ignored",
			.def  = 0,
			.arg  = अणु .l = अणु .nr = ARRAY_SIZE(dplx_list),
					 .p = dplx_list पूर्णपूर्ण
		पूर्ण;

		अगर (num_Duplex > bd) अणु
			dplx = Duplex[bd];
			e1000_validate_option(&dplx, &opt, adapter);
		पूर्ण अन्यथा अणु
			dplx = opt.def;
		पूर्ण
	पूर्ण

	अगर ((num_AutoNeg > bd) && (speed != 0 || dplx != 0)) अणु
		e_dev_info("AutoNeg specified along with Speed or Duplex, "
			   "parameter ignored\n");
		adapter->hw.स्वतःneg_advertised = AUTONEG_ADV_DEFAULT;
	पूर्ण अन्यथा अणु /* Autoneg */
		अटल स्थिर काष्ठा e1000_opt_list an_list[] =
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
			 अणु 0x2f, AA "1000/FD, 100/FD, 100/HD, 10/FD, 10/HD" पूर्णपूर्ण;

		opt = (काष्ठा e1000_option) अणु
			.type = list_option,
			.name = "AutoNeg",
			.err  = "parameter ignored",
			.def  = AUTONEG_ADV_DEFAULT,
			.arg  = अणु .l = अणु .nr = ARRAY_SIZE(an_list),
					 .p = an_list पूर्णपूर्ण
		पूर्ण;

		अगर (num_AutoNeg > bd) अणु
			an = AutoNeg[bd];
			e1000_validate_option(&an, &opt, adapter);
		पूर्ण अन्यथा अणु
			an = opt.def;
		पूर्ण
		adapter->hw.स्वतःneg_advertised = an;
	पूर्ण

	चयन (speed + dplx) अणु
	हाल 0:
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 1;
		अगर ((num_Speed > bd) && (speed != 0 || dplx != 0))
			e_dev_info("Speed and duplex autonegotiation "
				   "enabled\n");
		अवरोध;
	हाल HALF_DUPLEX:
		e_dev_info("Half Duplex specified without Speed\n");
		e_dev_info("Using Autonegotiation at Half Duplex only\n");
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 1;
		adapter->hw.स्वतःneg_advertised = ADVERTISE_10_HALF |
						 ADVERTISE_100_HALF;
		अवरोध;
	हाल FULL_DUPLEX:
		e_dev_info("Full Duplex specified without Speed\n");
		e_dev_info("Using Autonegotiation at Full Duplex only\n");
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 1;
		adapter->hw.स्वतःneg_advertised = ADVERTISE_10_FULL |
						 ADVERTISE_100_FULL |
						 ADVERTISE_1000_FULL;
		अवरोध;
	हाल SPEED_10:
		e_dev_info("10 Mbps Speed specified without Duplex\n");
		e_dev_info("Using Autonegotiation at 10 Mbps only\n");
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 1;
		adapter->hw.स्वतःneg_advertised = ADVERTISE_10_HALF |
						 ADVERTISE_10_FULL;
		अवरोध;
	हाल SPEED_10 + HALF_DUPLEX:
		e_dev_info("Forcing to 10 Mbps Half Duplex\n");
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 0;
		adapter->hw.क्रमced_speed_duplex = e1000_10_half;
		adapter->hw.स्वतःneg_advertised = 0;
		अवरोध;
	हाल SPEED_10 + FULL_DUPLEX:
		e_dev_info("Forcing to 10 Mbps Full Duplex\n");
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 0;
		adapter->hw.क्रमced_speed_duplex = e1000_10_full;
		adapter->hw.स्वतःneg_advertised = 0;
		अवरोध;
	हाल SPEED_100:
		e_dev_info("100 Mbps Speed specified without Duplex\n");
		e_dev_info("Using Autonegotiation at 100 Mbps only\n");
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 1;
		adapter->hw.स्वतःneg_advertised = ADVERTISE_100_HALF |
						 ADVERTISE_100_FULL;
		अवरोध;
	हाल SPEED_100 + HALF_DUPLEX:
		e_dev_info("Forcing to 100 Mbps Half Duplex\n");
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 0;
		adapter->hw.क्रमced_speed_duplex = e1000_100_half;
		adapter->hw.स्वतःneg_advertised = 0;
		अवरोध;
	हाल SPEED_100 + FULL_DUPLEX:
		e_dev_info("Forcing to 100 Mbps Full Duplex\n");
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 0;
		adapter->hw.क्रमced_speed_duplex = e1000_100_full;
		adapter->hw.स्वतःneg_advertised = 0;
		अवरोध;
	हाल SPEED_1000:
		e_dev_info("1000 Mbps Speed specified without Duplex\n");
		जाओ full_duplex_only;
	हाल SPEED_1000 + HALF_DUPLEX:
		e_dev_info("Half Duplex is not supported at 1000 Mbps\n");
		fallthrough;
	हाल SPEED_1000 + FULL_DUPLEX:
full_duplex_only:
		e_dev_info("Using Autonegotiation at 1000 Mbps Full Duplex "
			   "only\n");
		adapter->hw.स्वतःneg = adapter->fc_स्वतःneg = 1;
		adapter->hw.स्वतःneg_advertised = ADVERTISE_1000_FULL;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	/* Speed, AutoNeg and MDI/MDI-X must all play nice */
	अगर (e1000_validate_mdi_setting(&(adapter->hw)) < 0) अणु
		e_dev_info("Speed, AutoNeg and MDI-X specs are incompatible. "
			   "Setting MDI-X to a compatible value.\n");
	पूर्ण
पूर्ण

