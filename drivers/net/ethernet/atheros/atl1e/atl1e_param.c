<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2007 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#समावेश <linux/netdevice.h>

#समावेश "atl1e.h"

/* This is the only thing that needs to be changed to adjust the
 * maximum number of ports that the driver can manage.
 */

#घोषणा ATL1E_MAX_NIC 32

#घोषणा OPTION_UNSET    -1
#घोषणा OPTION_DISABLED 0
#घोषणा OPTION_ENABLED  1

/* All parameters are treated the same, as an पूर्णांकeger array of values.
 * This macro just reduces the need to repeat the same declaration code
 * over and over (plus this helps to aव्योम typo bugs).
 */
#घोषणा ATL1E_PARAM_INIT अणु [0 ... ATL1E_MAX_NIC] = OPTION_UNSET पूर्ण

#घोषणा ATL1E_PARAM(x, desc) \
	अटल पूर्णांक x[ATL1E_MAX_NIC + 1] = ATL1E_PARAM_INIT; \
	अटल अचिन्हित पूर्णांक num_##x; \
	module_param_array_named(x, x, पूर्णांक, &num_##x, 0); \
	MODULE_PARM_DESC(x, desc);

/* Transmit Memory count
 *
 * Valid Range: 64-2048
 *
 * Default Value: 128
 */
#घोषणा ATL1E_MIN_TX_DESC_CNT		32
#घोषणा ATL1E_MAX_TX_DESC_CNT		1020
#घोषणा ATL1E_DEFAULT_TX_DESC_CNT	128
ATL1E_PARAM(tx_desc_cnt, "Transmit description count");

/* Receive Memory Block Count
 *
 * Valid Range: 16-512
 *
 * Default Value: 128
 */
#घोषणा ATL1E_MIN_RX_MEM_SIZE		8    /* 8KB   */
#घोषणा ATL1E_MAX_RX_MEM_SIZE		1024 /* 1MB   */
#घोषणा ATL1E_DEFAULT_RX_MEM_SIZE	256  /* 128KB */
ATL1E_PARAM(rx_mem_size, "memory size of rx buffer(KB)");

/* User Specअगरied MediaType Override
 *
 * Valid Range: 0-5
 *  - 0    - स्वतः-negotiate at all supported speeds
 *  - 1    - only link at 100Mbps Full Duplex
 *  - 2    - only link at 100Mbps Half Duplex
 *  - 3    - only link at 10Mbps Full Duplex
 *  - 4    - only link at 10Mbps Half Duplex
 * Default Value: 0
 */

ATL1E_PARAM(media_type, "MediaType Select");

/* Interrupt Moderate Timer in units of 2 us
 *
 * Valid Range: 10-65535
 *
 * Default Value: 45000(90ms)
 */
#घोषणा INT_MOD_DEFAULT_CNT             100 /* 200us */
#घोषणा INT_MOD_MAX_CNT                 65000
#घोषणा INT_MOD_MIN_CNT                 50
ATL1E_PARAM(पूर्णांक_mod_समयr, "Interrupt Moderator Timer");

#घोषणा AUTONEG_ADV_DEFAULT  0x2F
#घोषणा AUTONEG_ADV_MASK     0x2F
#घोषणा FLOW_CONTROL_DEFAULT FLOW_CONTROL_FULL

#घोषणा FLASH_VENDOR_DEFAULT    0
#घोषणा FLASH_VENDOR_MIN        0
#घोषणा FLASH_VENDOR_MAX        2

काष्ठा atl1e_option अणु
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
			काष्ठा atl1e_opt_list अणु पूर्णांक i; अक्षर *str; पूर्ण *p;
		पूर्ण l;
	पूर्ण arg;
पूर्ण;

अटल पूर्णांक atl1e_validate_option(पूर्णांक *value, काष्ठा atl1e_option *opt,
				 काष्ठा atl1e_adapter *adapter)
अणु
	अगर (*value == OPTION_UNSET) अणु
		*value = opt->def;
		वापस 0;
	पूर्ण

	चयन (opt->type) अणु
	हाल enable_option:
		चयन (*value) अणु
		हाल OPTION_ENABLED:
			netdev_info(adapter->netdev,
				    "%s Enabled\n", opt->name);
			वापस 0;
		हाल OPTION_DISABLED:
			netdev_info(adapter->netdev,
				    "%s Disabled\n", opt->name);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल range_option:
		अगर (*value >= opt->arg.r.min && *value <= opt->arg.r.max) अणु
			netdev_info(adapter->netdev, "%s set to %i\n",
				    opt->name, *value);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल list_option:अणु
			पूर्णांक i;
			काष्ठा atl1e_opt_list *ent;

			क्रम (i = 0; i < opt->arg.l.nr; i++) अणु
				ent = &opt->arg.l.p[i];
				अगर (*value == ent->i) अणु
					अगर (ent->str[0] != '\0')
						netdev_info(adapter->netdev,
							    "%s\n", ent->str);
					वापस 0;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	शेष:
		BUG();
	पूर्ण

	netdev_info(adapter->netdev, "Invalid %s specified (%i) %s\n",
		    opt->name, *value, opt->err);
	*value = opt->def;
	वापस -1;
पूर्ण

/**
 * atl1e_check_options - Range Checking क्रम Command Line Parameters
 * @adapter: board निजी काष्ठाure
 *
 * This routine checks all command line parameters क्रम valid user
 * input.  If an invalid value is given, or अगर no user specअगरied
 * value exists, a शेष value is used.  The final value is stored
 * in a variable in the adapter काष्ठाure.
 */
व्योम atl1e_check_options(काष्ठा atl1e_adapter *adapter)
अणु
	पूर्णांक bd = adapter->bd_number;

	अगर (bd >= ATL1E_MAX_NIC) अणु
		netdev_notice(adapter->netdev,
			      "no configuration for board #%i\n", bd);
		netdev_notice(adapter->netdev,
			      "Using defaults for all values\n");
	पूर्ण

	अणु 		/* Transmit Ring Size */
		काष्ठा atl1e_option opt = अणु
			.type = range_option,
			.name = "Transmit Ddescription Count",
			.err  = "using default of "
				__MODULE_STRING(ATL1E_DEFAULT_TX_DESC_CNT),
			.def  = ATL1E_DEFAULT_TX_DESC_CNT,
			.arg  = अणु .r = अणु .min = ATL1E_MIN_TX_DESC_CNT,
					 .max = ATL1E_MAX_TX_DESC_CNTपूर्ण पूर्ण
		पूर्ण;
		पूर्णांक val;
		अगर (num_tx_desc_cnt > bd) अणु
			val = tx_desc_cnt[bd];
			atl1e_validate_option(&val, &opt, adapter);
			adapter->tx_ring.count = (u16) val & 0xFFFC;
		पूर्ण अन्यथा
			adapter->tx_ring.count = (u16)opt.def;
	पूर्ण

	अणु 		/* Receive Memory Block Count */
		काष्ठा atl1e_option opt = अणु
			.type = range_option,
			.name = "Memory size of rx buffer(KB)",
			.err  = "using default of "
				__MODULE_STRING(ATL1E_DEFAULT_RX_MEM_SIZE),
			.def  = ATL1E_DEFAULT_RX_MEM_SIZE,
			.arg  = अणु .r = अणु .min = ATL1E_MIN_RX_MEM_SIZE,
					 .max = ATL1E_MAX_RX_MEM_SIZEपूर्ण पूर्ण
		पूर्ण;
		पूर्णांक val;
		अगर (num_rx_mem_size > bd) अणु
			val = rx_mem_size[bd];
			atl1e_validate_option(&val, &opt, adapter);
			adapter->rx_ring.page_size = (u32)val * 1024;
		पूर्ण अन्यथा अणु
			adapter->rx_ring.page_size = (u32)opt.def * 1024;
		पूर्ण
	पूर्ण

	अणु 		/* Interrupt Moderate Timer */
		काष्ठा atl1e_option opt = अणु
			.type = range_option,
			.name = "Interrupt Moderate Timer",
			.err  = "using default of "
				__MODULE_STRING(INT_MOD_DEFAULT_CNT),
			.def  = INT_MOD_DEFAULT_CNT,
			.arg  = अणु .r = अणु .min = INT_MOD_MIN_CNT,
					 .max = INT_MOD_MAX_CNTपूर्ण पूर्ण
		पूर्ण ;
		पूर्णांक val;
		अगर (num_पूर्णांक_mod_समयr > bd) अणु
			val = पूर्णांक_mod_समयr[bd];
			atl1e_validate_option(&val, &opt, adapter);
			adapter->hw.imt = (u16) val;
		पूर्ण अन्यथा
			adapter->hw.imt = (u16)(opt.def);
	पूर्ण

	अणु 		/* MediaType */
		काष्ठा atl1e_option opt = अणु
			.type = range_option,
			.name = "Speed/Duplex Selection",
			.err  = "using default of "
				__MODULE_STRING(MEDIA_TYPE_AUTO_SENSOR),
			.def  = MEDIA_TYPE_AUTO_SENSOR,
			.arg  = अणु .r = अणु .min = MEDIA_TYPE_AUTO_SENSOR,
					 .max = MEDIA_TYPE_10M_HALFपूर्ण पूर्ण
		पूर्ण ;
		पूर्णांक val;
		अगर (num_media_type > bd) अणु
			val = media_type[bd];
			atl1e_validate_option(&val, &opt, adapter);
			adapter->hw.media_type = (u16) val;
		पूर्ण अन्यथा
			adapter->hw.media_type = (u16)(opt.def);

	पूर्ण
पूर्ण
