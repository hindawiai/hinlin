<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2008 Intel Corporation. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "ixgb.h"

/* This is the only thing that needs to be changed to adjust the
 * maximum number of ports that the driver can manage.
 */

#घोषणा IXGB_MAX_NIC 8

#घोषणा OPTION_UNSET	-1
#घोषणा OPTION_DISABLED 0
#घोषणा OPTION_ENABLED  1

/* All parameters are treated the same, as an पूर्णांकeger array of values.
 * This macro just reduces the need to repeat the same declaration code
 * over and over (plus this helps to aव्योम typo bugs).
 */

#घोषणा IXGB_PARAM_INIT अणु [0 ... IXGB_MAX_NIC] = OPTION_UNSET पूर्ण
#घोषणा IXGB_PARAM(X, desc)					\
	अटल पूर्णांक X[IXGB_MAX_NIC+1]		\
		= IXGB_PARAM_INIT;				\
	अटल अचिन्हित पूर्णांक num_##X = 0;			\
	module_param_array_named(X, X, पूर्णांक, &num_##X, 0);	\
	MODULE_PARM_DESC(X, desc);

/* Transmit Descriptor Count
 *
 * Valid Range: 64-4096
 *
 * Default Value: 256
 */

IXGB_PARAM(TxDescriptors, "Number of transmit descriptors");

/* Receive Descriptor Count
 *
 * Valid Range: 64-4096
 *
 * Default Value: 1024
 */

IXGB_PARAM(RxDescriptors, "Number of receive descriptors");

/* User Specअगरied Flow Control Override
 *
 * Valid Range: 0-3
 *  - 0 - No Flow Control
 *  - 1 - Rx only, respond to PAUSE frames but करो not generate them
 *  - 2 - Tx only, generate PAUSE frames but ignore them on receive
 *  - 3 - Full Flow Control Support
 *
 * Default Value: 2 - Tx only (silicon bug aव्योमance)
 */

IXGB_PARAM(FlowControl, "Flow Control setting");

/* XsumRX - Receive Checksum Offload Enable/Disable
 *
 * Valid Range: 0, 1
 *  - 0 - disables all checksum offload
 *  - 1 - enables receive IP/TCP/UDP checksum offload
 *        on 82597 based NICs
 *
 * Default Value: 1
 */

IXGB_PARAM(XsumRX, "Disable or enable Receive Checksum offload");

/* Transmit Interrupt Delay in units of 0.8192 microseconds
 *
 * Valid Range: 0-65535
 *
 * Default Value: 32
 */

IXGB_PARAM(TxIntDelay, "Transmit Interrupt Delay");

/* Receive Interrupt Delay in units of 0.8192 microseconds
 *
 * Valid Range: 0-65535
 *
 * Default Value: 72
 */

IXGB_PARAM(RxIntDelay, "Receive Interrupt Delay");

/* Receive Flow control high threshold (when we send a छोड़ो frame)
 * (FCRTH)
 *
 * Valid Range: 1,536 - 262,136 (0x600 - 0x3FFF8, 8 byte granularity)
 *
 * Default Value: 196,608 (0x30000)
 */

IXGB_PARAM(RxFCHighThresh, "Receive Flow Control High Threshold");

/* Receive Flow control low threshold (when we send a resume frame)
 * (FCRTL)
 *
 * Valid Range: 64 - 262,136 (0x40 - 0x3FFF8, 8 byte granularity)
 *              must be less than high threshold by at least 8 bytes
 *
 * Default Value:  163,840 (0x28000)
 */

IXGB_PARAM(RxFCLowThresh, "Receive Flow Control Low Threshold");

/* Flow control request समयout (how दीर्घ to छोड़ो the link partner's tx)
 * (PAP 15:0)
 *
 * Valid Range: 1 - 65535
 *
 * Default Value:  65535 (0xffff) (we'll send an xon अगर we recover)
 */

IXGB_PARAM(FCReqTimeout, "Flow Control Request Timeout");

/* Interrupt Delay Enable
 *
 * Valid Range: 0, 1
 *
 *  - 0 - disables transmit पूर्णांकerrupt delay
 *  - 1 - enables transmmit पूर्णांकerrupt delay
 *
 * Default Value: 1
 */

IXGB_PARAM(IntDelayEnable, "Transmit Interrupt Delay Enable");


#घोषणा DEFAULT_TIDV	   		     32
#घोषणा MAX_TIDV			 0xFFFF
#घोषणा MIN_TIDV			      0

#घोषणा DEFAULT_RDTR		   	     72
#घोषणा MAX_RDTR			 0xFFFF
#घोषणा MIN_RDTR			      0

#घोषणा XSUMRX_DEFAULT		 OPTION_ENABLED

#घोषणा DEFAULT_FCRTL	  		0x28000
#घोषणा DEFAULT_FCRTH			0x30000
#घोषणा MIN_FCRTL			      0
#घोषणा MAX_FCRTL			0x3FFE8
#घोषणा MIN_FCRTH			      8
#घोषणा MAX_FCRTH			0x3FFF0

#घोषणा MIN_FCPAUSE			      1
#घोषणा MAX_FCPAUSE			 0xffff
#घोषणा DEFAULT_FCPAUSE		  	 0xFFFF /* this may be too दीर्घ */

काष्ठा ixgb_option अणु
	क्रमागत अणु enable_option, range_option, list_option पूर्ण type;
	स्थिर अक्षर *name;
	स्थिर अक्षर *err;
	पूर्णांक def;
	जोड़ अणु
		काष्ठा अणु	/* range_option info */
			पूर्णांक min;
			पूर्णांक max;
		पूर्ण r;
		काष्ठा अणु	/* list_option info */
			पूर्णांक nr;
			स्थिर काष्ठा ixgb_opt_list अणु
				पूर्णांक i;
				स्थिर अक्षर *str;
			पूर्ण *p;
		पूर्ण l;
	पूर्ण arg;
पूर्ण;

अटल पूर्णांक
ixgb_validate_option(अचिन्हित पूर्णांक *value, स्थिर काष्ठा ixgb_option *opt)
अणु
	अगर (*value == OPTION_UNSET) अणु
		*value = opt->def;
		वापस 0;
	पूर्ण

	चयन (opt->type) अणु
	हाल enable_option:
		चयन (*value) अणु
		हाल OPTION_ENABLED:
			pr_info("%s Enabled\n", opt->name);
			वापस 0;
		हाल OPTION_DISABLED:
			pr_info("%s Disabled\n", opt->name);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल range_option:
		अगर (*value >= opt->arg.r.min && *value <= opt->arg.r.max) अणु
			pr_info("%s set to %i\n", opt->name, *value);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल list_option: अणु
		पूर्णांक i;
		स्थिर काष्ठा ixgb_opt_list *ent;

		क्रम (i = 0; i < opt->arg.l.nr; i++) अणु
			ent = &opt->arg.l.p[i];
			अगर (*value == ent->i) अणु
				अगर (ent->str[0] != '\0')
					pr_info("%s\n", ent->str);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	pr_info("Invalid %s specified (%i) %s\n", opt->name, *value, opt->err);
	*value = opt->def;
	वापस -1;
पूर्ण

/**
 * ixgb_check_options - Range Checking क्रम Command Line Parameters
 * @adapter: board निजी काष्ठाure
 *
 * This routine checks all command line parameters क्रम valid user
 * input.  If an invalid value is given, or अगर no user specअगरied
 * value exists, a शेष value is used.  The final value is stored
 * in a variable in the adapter काष्ठाure.
 **/

व्योम
ixgb_check_options(काष्ठा ixgb_adapter *adapter)
अणु
	पूर्णांक bd = adapter->bd_number;
	अगर (bd >= IXGB_MAX_NIC) अणु
		pr_notice("Warning: no configuration for board #%i\n", bd);
		pr_notice("Using defaults for all values\n");
	पूर्ण

	अणु /* Transmit Descriptor Count */
		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = range_option,
			.name = "Transmit Descriptors",
			.err  = "using default of " __MODULE_STRING(DEFAULT_TXD),
			.def  = DEFAULT_TXD,
			.arg  = अणु .r = अणु .min = MIN_TXD,
					 .max = MAX_TXDपूर्णपूर्ण
		पूर्ण;
		काष्ठा ixgb_desc_ring *tx_ring = &adapter->tx_ring;

		अगर (num_TxDescriptors > bd) अणु
			tx_ring->count = TxDescriptors[bd];
			ixgb_validate_option(&tx_ring->count, &opt);
		पूर्ण अन्यथा अणु
			tx_ring->count = opt.def;
		पूर्ण
		tx_ring->count = ALIGN(tx_ring->count, IXGB_REQ_TX_DESCRIPTOR_MULTIPLE);
	पूर्ण
	अणु /* Receive Descriptor Count */
		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = range_option,
			.name = "Receive Descriptors",
			.err  = "using default of " __MODULE_STRING(DEFAULT_RXD),
			.def  = DEFAULT_RXD,
			.arg  = अणु .r = अणु .min = MIN_RXD,
					 .max = MAX_RXDपूर्णपूर्ण
		पूर्ण;
		काष्ठा ixgb_desc_ring *rx_ring = &adapter->rx_ring;

		अगर (num_RxDescriptors > bd) अणु
			rx_ring->count = RxDescriptors[bd];
			ixgb_validate_option(&rx_ring->count, &opt);
		पूर्ण अन्यथा अणु
			rx_ring->count = opt.def;
		पूर्ण
		rx_ring->count = ALIGN(rx_ring->count, IXGB_REQ_RX_DESCRIPTOR_MULTIPLE);
	पूर्ण
	अणु /* Receive Checksum Offload Enable */
		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = enable_option,
			.name = "Receive Checksum Offload",
			.err  = "defaulting to Enabled",
			.def  = OPTION_ENABLED
		पूर्ण;

		अगर (num_XsumRX > bd) अणु
			अचिन्हित पूर्णांक rx_csum = XsumRX[bd];
			ixgb_validate_option(&rx_csum, &opt);
			adapter->rx_csum = rx_csum;
		पूर्ण अन्यथा अणु
			adapter->rx_csum = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Flow Control */

		अटल स्थिर काष्ठा ixgb_opt_list fc_list[] = अणु
		       अणु ixgb_fc_none, "Flow Control Disabled" पूर्ण,
		       अणु ixgb_fc_rx_छोड़ो, "Flow Control Receive Only" पूर्ण,
		       अणु ixgb_fc_tx_छोड़ो, "Flow Control Transmit Only" पूर्ण,
		       अणु ixgb_fc_full, "Flow Control Enabled" पूर्ण,
		       अणु ixgb_fc_शेष, "Flow Control Hardware Default" पूर्ण
		पूर्ण;

		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = list_option,
			.name = "Flow Control",
			.err  = "reading default settings from EEPROM",
			.def  = ixgb_fc_tx_छोड़ो,
			.arg  = अणु .l = अणु .nr = ARRAY_SIZE(fc_list),
					 .p = fc_list पूर्णपूर्ण
		पूर्ण;

		अगर (num_FlowControl > bd) अणु
			अचिन्हित पूर्णांक fc = FlowControl[bd];
			ixgb_validate_option(&fc, &opt);
			adapter->hw.fc.type = fc;
		पूर्ण अन्यथा अणु
			adapter->hw.fc.type = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Receive Flow Control High Threshold */
		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = range_option,
			.name = "Rx Flow Control High Threshold",
			.err  = "using default of " __MODULE_STRING(DEFAULT_FCRTH),
			.def  = DEFAULT_FCRTH,
			.arg  = अणु .r = अणु .min = MIN_FCRTH,
					 .max = MAX_FCRTHपूर्णपूर्ण
		पूर्ण;

		अगर (num_RxFCHighThresh > bd) अणु
			adapter->hw.fc.high_water = RxFCHighThresh[bd];
			ixgb_validate_option(&adapter->hw.fc.high_water, &opt);
		पूर्ण अन्यथा अणु
			adapter->hw.fc.high_water = opt.def;
		पूर्ण
		अगर (!(adapter->hw.fc.type & ixgb_fc_tx_छोड़ो) )
			pr_info("Ignoring RxFCHighThresh when no RxFC\n");
	पूर्ण
	अणु /* Receive Flow Control Low Threshold */
		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = range_option,
			.name = "Rx Flow Control Low Threshold",
			.err  = "using default of " __MODULE_STRING(DEFAULT_FCRTL),
			.def  = DEFAULT_FCRTL,
			.arg  = अणु .r = अणु .min = MIN_FCRTL,
					 .max = MAX_FCRTLपूर्णपूर्ण
		पूर्ण;

		अगर (num_RxFCLowThresh > bd) अणु
			adapter->hw.fc.low_water = RxFCLowThresh[bd];
			ixgb_validate_option(&adapter->hw.fc.low_water, &opt);
		पूर्ण अन्यथा अणु
			adapter->hw.fc.low_water = opt.def;
		पूर्ण
		अगर (!(adapter->hw.fc.type & ixgb_fc_tx_छोड़ो) )
			pr_info("Ignoring RxFCLowThresh when no RxFC\n");
	पूर्ण
	अणु /* Flow Control Pause Time Request*/
		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = range_option,
			.name = "Flow Control Pause Time Request",
			.err  = "using default of "__MODULE_STRING(DEFAULT_FCPAUSE),
			.def  = DEFAULT_FCPAUSE,
			.arg = अणु .r = अणु .min = MIN_FCPAUSE,
					.max = MAX_FCPAUSEपूर्णपूर्ण
		पूर्ण;

		अगर (num_FCReqTimeout > bd) अणु
			अचिन्हित पूर्णांक छोड़ो_समय = FCReqTimeout[bd];
			ixgb_validate_option(&छोड़ो_समय, &opt);
			adapter->hw.fc.छोड़ो_समय = छोड़ो_समय;
		पूर्ण अन्यथा अणु
			adapter->hw.fc.छोड़ो_समय = opt.def;
		पूर्ण
		अगर (!(adapter->hw.fc.type & ixgb_fc_tx_छोड़ो) )
			pr_info("Ignoring FCReqTimeout when no RxFC\n");
	पूर्ण
	/* high low and spacing check क्रम rx flow control thresholds */
	अगर (adapter->hw.fc.type & ixgb_fc_tx_छोड़ो) अणु
		/* high must be greater than low */
		अगर (adapter->hw.fc.high_water < (adapter->hw.fc.low_water + 8)) अणु
			/* set शेषs */
			pr_info("RxFCHighThresh must be >= (RxFCLowThresh + 8), Using Defaults\n");
			adapter->hw.fc.high_water = DEFAULT_FCRTH;
			adapter->hw.fc.low_water  = DEFAULT_FCRTL;
		पूर्ण
	पूर्ण
	अणु /* Receive Interrupt Delay */
		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = range_option,
			.name = "Receive Interrupt Delay",
			.err  = "using default of " __MODULE_STRING(DEFAULT_RDTR),
			.def  = DEFAULT_RDTR,
			.arg  = अणु .r = अणु .min = MIN_RDTR,
					 .max = MAX_RDTRपूर्णपूर्ण
		पूर्ण;

		अगर (num_RxIntDelay > bd) अणु
			adapter->rx_पूर्णांक_delay = RxIntDelay[bd];
			ixgb_validate_option(&adapter->rx_पूर्णांक_delay, &opt);
		पूर्ण अन्यथा अणु
			adapter->rx_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण
	अणु /* Transmit Interrupt Delay */
		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = range_option,
			.name = "Transmit Interrupt Delay",
			.err  = "using default of " __MODULE_STRING(DEFAULT_TIDV),
			.def  = DEFAULT_TIDV,
			.arg  = अणु .r = अणु .min = MIN_TIDV,
					 .max = MAX_TIDVपूर्णपूर्ण
		पूर्ण;

		अगर (num_TxIntDelay > bd) अणु
			adapter->tx_पूर्णांक_delay = TxIntDelay[bd];
			ixgb_validate_option(&adapter->tx_पूर्णांक_delay, &opt);
		पूर्ण अन्यथा अणु
			adapter->tx_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण

	अणु /* Transmit Interrupt Delay Enable */
		अटल स्थिर काष्ठा ixgb_option opt = अणु
			.type = enable_option,
			.name = "Tx Interrupt Delay Enable",
			.err  = "defaulting to Enabled",
			.def  = OPTION_ENABLED
		पूर्ण;

		अगर (num_IntDelayEnable > bd) अणु
			अचिन्हित पूर्णांक ide = IntDelayEnable[bd];
			ixgb_validate_option(&ide, &opt);
			adapter->tx_पूर्णांक_delay_enable = ide;
		पूर्ण अन्यथा अणु
			adapter->tx_पूर्णांक_delay_enable = opt.def;
		पूर्ण
	पूर्ण
पूर्ण
