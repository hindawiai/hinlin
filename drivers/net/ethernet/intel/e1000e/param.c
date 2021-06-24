<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "e1000.h"

/* This is the only thing that needs to be changed to adjust the
 * maximum number of ports that the driver can manage.
 */
#घोषणा E1000_MAX_NIC 32

#घोषणा OPTION_UNSET   -1
#घोषणा OPTION_DISABLED 0
#घोषणा OPTION_ENABLED  1

#घोषणा COPYBREAK_DEFAULT 256
अचिन्हित पूर्णांक copyअवरोध = COPYBREAK_DEFAULT;
module_param(copyअवरोध, uपूर्णांक, 0644);
MODULE_PARM_DESC(copyअवरोध,
		 "Maximum size of packet that is copied to a new buffer on receive");

/* All parameters are treated the same, as an पूर्णांकeger array of values.
 * This macro just reduces the need to repeat the same declaration code
 * over and over (plus this helps to aव्योम typo bugs).
 */
#घोषणा E1000_PARAM_INIT अणु [0 ... E1000_MAX_NIC] = OPTION_UNSET पूर्ण
#घोषणा E1000_PARAM(X, desc)					\
	अटल पूर्णांक X[E1000_MAX_NIC+1] = E1000_PARAM_INIT;	\
	अटल अचिन्हित पूर्णांक num_##X;				\
	module_param_array_named(X, X, पूर्णांक, &num_##X, 0);	\
	MODULE_PARM_DESC(X, desc);

/* Transmit Interrupt Delay in units of 1.024 microseconds
 * Tx पूर्णांकerrupt delay needs to typically be set to something non-zero
 *
 * Valid Range: 0-65535
 */
E1000_PARAM(TxIntDelay, "Transmit Interrupt Delay");
#घोषणा DEFAULT_TIDV 8
#घोषणा MAX_TXDELAY 0xFFFF
#घोषणा MIN_TXDELAY 0

/* Transmit Absolute Interrupt Delay in units of 1.024 microseconds
 *
 * Valid Range: 0-65535
 */
E1000_PARAM(TxAbsIntDelay, "Transmit Absolute Interrupt Delay");
#घोषणा DEFAULT_TADV 32
#घोषणा MAX_TXABSDELAY 0xFFFF
#घोषणा MIN_TXABSDELAY 0

/* Receive Interrupt Delay in units of 1.024 microseconds
 * hardware will likely hang अगर you set this to anything but zero.
 *
 * Burst variant is used as शेष अगर device has FLAG2_DMA_BURST.
 *
 * Valid Range: 0-65535
 */
E1000_PARAM(RxIntDelay, "Receive Interrupt Delay");
#घोषणा DEFAULT_RDTR	0
#घोषणा BURST_RDTR	0x20
#घोषणा MAX_RXDELAY 0xFFFF
#घोषणा MIN_RXDELAY 0

/* Receive Absolute Interrupt Delay in units of 1.024 microseconds
 *
 * Burst variant is used as शेष अगर device has FLAG2_DMA_BURST.
 *
 * Valid Range: 0-65535
 */
E1000_PARAM(RxAbsIntDelay, "Receive Absolute Interrupt Delay");
#घोषणा DEFAULT_RADV	8
#घोषणा BURST_RADV	0x20
#घोषणा MAX_RXABSDELAY 0xFFFF
#घोषणा MIN_RXABSDELAY 0

/* Interrupt Throttle Rate (पूर्णांकerrupts/sec)
 *
 * Valid Range: 100-100000 or one of: 0=off, 1=dynamic, 3=dynamic conservative
 */
E1000_PARAM(InterruptThrottleRate, "Interrupt Throttling Rate");
#घोषणा DEFAULT_ITR 3
#घोषणा MAX_ITR 100000
#घोषणा MIN_ITR 100

/* IntMode (Interrupt Mode)
 *
 * Valid Range: varies depending on kernel configuration & hardware support
 *
 * legacy=0, MSI=1, MSI-X=2
 *
 * When MSI/MSI-X support is enabled in kernel-
 *   Default Value: 2 (MSI-X) when supported by hardware, 1 (MSI) otherwise
 * When MSI/MSI-X support is not enabled in kernel-
 *   Default Value: 0 (legacy)
 *
 * When a mode is specअगरied that is not allowed/supported, it will be
 * demoted to the most advanced पूर्णांकerrupt mode available.
 */
E1000_PARAM(IntMode, "Interrupt Mode");
#घोषणा MAX_INTMODE	2
#घोषणा MIN_INTMODE	0

/* Enable Smart Power Down of the PHY
 *
 * Valid Range: 0, 1
 *
 * Default Value: 0 (disabled)
 */
E1000_PARAM(SmartPowerDownEnable, "Enable PHY smart power down");

/* Enable Kumeran Lock Loss workaround
 *
 * Valid Range: 0, 1
 *
 * Default Value: 1 (enabled)
 */
E1000_PARAM(KumeranLockLoss, "Enable Kumeran lock loss workaround");

/* Write Protect NVM
 *
 * Valid Range: 0, 1
 *
 * Default Value: 1 (enabled)
 */
E1000_PARAM(WriteProtectNVM,
	    "Write-protect NVM [WARNING: disabling this can lead to corrupted NVM]");

/* Enable CRC Stripping
 *
 * Valid Range: 0, 1
 *
 * Default Value: 1 (enabled)
 */
E1000_PARAM(CrcStripping,
	    "Enable CRC Stripping, disable if your BMC needs the CRC");

काष्ठा e1000_option अणु
	क्रमागत अणु enable_option, range_option, list_option पूर्ण type;
	स्थिर अक्षर *name;
	स्थिर अक्षर *err;
	पूर्णांक def;
	जोड़ अणु
		/* range_option info */
		काष्ठा अणु
			पूर्णांक min;
			पूर्णांक max;
		पूर्ण r;
		/* list_option info */
		काष्ठा अणु
			पूर्णांक nr;
			काष्ठा e1000_opt_list अणु
				पूर्णांक i;
				अक्षर *str;
			पूर्ण *p;
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
			dev_info(&adapter->pdev->dev, "%s Enabled\n",
				 opt->name);
			वापस 0;
		हाल OPTION_DISABLED:
			dev_info(&adapter->pdev->dev, "%s Disabled\n",
				 opt->name);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल range_option:
		अगर (*value >= opt->arg.r.min && *value <= opt->arg.r.max) अणु
			dev_info(&adapter->pdev->dev, "%s set to %i\n",
				 opt->name, *value);
			वापस 0;
		पूर्ण
		अवरोध;
	हाल list_option: अणु
		पूर्णांक i;
		काष्ठा e1000_opt_list *ent;

		क्रम (i = 0; i < opt->arg.l.nr; i++) अणु
			ent = &opt->arg.l.p[i];
			अगर (*value == ent->i) अणु
				अगर (ent->str[0] != '\0')
					dev_info(&adapter->pdev->dev, "%s\n",
						 ent->str);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	dev_info(&adapter->pdev->dev, "Invalid %s value specified (%i) %s\n",
		 opt->name, *value, opt->err);
	*value = opt->def;
	वापस -1;
पूर्ण

/**
 * e1000e_check_options - Range Checking क्रम Command Line Parameters
 * @adapter: board निजी काष्ठाure
 *
 * This routine checks all command line parameters क्रम valid user
 * input.  If an invalid value is given, or अगर no user specअगरied
 * value exists, a शेष value is used.  The final value is stored
 * in a variable in the adapter काष्ठाure.
 **/
व्योम e1000e_check_options(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक bd = adapter->bd_number;

	अगर (bd >= E1000_MAX_NIC) अणु
		dev_notice(&adapter->pdev->dev,
			   "Warning: no configuration for board #%i\n", bd);
		dev_notice(&adapter->pdev->dev,
			   "Using defaults for all values\n");
	पूर्ण

	/* Transmit Interrupt Delay */
	अणु
		अटल स्थिर काष्ठा e1000_option opt = अणु
			.type = range_option,
			.name = "Transmit Interrupt Delay",
			.err  = "using default of "
				__MODULE_STRING(DEFAULT_TIDV),
			.def  = DEFAULT_TIDV,
			.arg  = अणु .r = अणु .min = MIN_TXDELAY,
					 .max = MAX_TXDELAY पूर्ण पूर्ण
		पूर्ण;

		अगर (num_TxIntDelay > bd) अणु
			adapter->tx_पूर्णांक_delay = TxIntDelay[bd];
			e1000_validate_option(&adapter->tx_पूर्णांक_delay, &opt,
					      adapter);
		पूर्ण अन्यथा अणु
			adapter->tx_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण
	/* Transmit Absolute Interrupt Delay */
	अणु
		अटल स्थिर काष्ठा e1000_option opt = अणु
			.type = range_option,
			.name = "Transmit Absolute Interrupt Delay",
			.err  = "using default of "
				__MODULE_STRING(DEFAULT_TADV),
			.def  = DEFAULT_TADV,
			.arg  = अणु .r = अणु .min = MIN_TXABSDELAY,
					 .max = MAX_TXABSDELAY पूर्ण पूर्ण
		पूर्ण;

		अगर (num_TxAbsIntDelay > bd) अणु
			adapter->tx_असल_पूर्णांक_delay = TxAbsIntDelay[bd];
			e1000_validate_option(&adapter->tx_असल_पूर्णांक_delay, &opt,
					      adapter);
		पूर्ण अन्यथा अणु
			adapter->tx_असल_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण
	/* Receive Interrupt Delay */
	अणु
		अटल काष्ठा e1000_option opt = अणु
			.type = range_option,
			.name = "Receive Interrupt Delay",
			.err  = "using default of "
				__MODULE_STRING(DEFAULT_RDTR),
			.def  = DEFAULT_RDTR,
			.arg  = अणु .r = अणु .min = MIN_RXDELAY,
					 .max = MAX_RXDELAY पूर्ण पूर्ण
		पूर्ण;

		अगर (adapter->flags2 & FLAG2_DMA_BURST)
			opt.def = BURST_RDTR;

		अगर (num_RxIntDelay > bd) अणु
			adapter->rx_पूर्णांक_delay = RxIntDelay[bd];
			e1000_validate_option(&adapter->rx_पूर्णांक_delay, &opt,
					      adapter);
		पूर्ण अन्यथा अणु
			adapter->rx_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण
	/* Receive Absolute Interrupt Delay */
	अणु
		अटल काष्ठा e1000_option opt = अणु
			.type = range_option,
			.name = "Receive Absolute Interrupt Delay",
			.err  = "using default of "
				__MODULE_STRING(DEFAULT_RADV),
			.def  = DEFAULT_RADV,
			.arg  = अणु .r = अणु .min = MIN_RXABSDELAY,
					 .max = MAX_RXABSDELAY पूर्ण पूर्ण
		पूर्ण;

		अगर (adapter->flags2 & FLAG2_DMA_BURST)
			opt.def = BURST_RADV;

		अगर (num_RxAbsIntDelay > bd) अणु
			adapter->rx_असल_पूर्णांक_delay = RxAbsIntDelay[bd];
			e1000_validate_option(&adapter->rx_असल_पूर्णांक_delay, &opt,
					      adapter);
		पूर्ण अन्यथा अणु
			adapter->rx_असल_पूर्णांक_delay = opt.def;
		पूर्ण
	पूर्ण
	/* Interrupt Throttling Rate */
	अणु
		अटल स्थिर काष्ठा e1000_option opt = अणु
			.type = range_option,
			.name = "Interrupt Throttling Rate (ints/sec)",
			.err  = "using default of "
				__MODULE_STRING(DEFAULT_ITR),
			.def  = DEFAULT_ITR,
			.arg  = अणु .r = अणु .min = MIN_ITR,
					 .max = MAX_ITR पूर्ण पूर्ण
		पूर्ण;

		अगर (num_InterruptThrottleRate > bd) अणु
			adapter->itr = InterruptThrottleRate[bd];

			/* Make sure a message is prपूर्णांकed क्रम non-special
			 * values. And in हाल of an invalid option, display
			 * warning, use शेष and go through itr/itr_setting
			 * adjusपंचांगent logic below
			 */
			अगर ((adapter->itr > 4) &&
			    e1000_validate_option(&adapter->itr, &opt, adapter))
				adapter->itr = opt.def;
		पूर्ण अन्यथा अणु
			/* If no option specअगरied, use शेष value and go
			 * through the logic below to adjust itr/itr_setting
			 */
			adapter->itr = opt.def;

			/* Make sure a message is prपूर्णांकed क्रम non-special
			 * शेष values
			 */
			अगर (adapter->itr > 4)
				dev_info(&adapter->pdev->dev,
					 "%s set to default %d\n", opt.name,
					 adapter->itr);
		पूर्ण

		adapter->itr_setting = adapter->itr;
		चयन (adapter->itr) अणु
		हाल 0:
			dev_info(&adapter->pdev->dev, "%s turned off\n",
				 opt.name);
			अवरोध;
		हाल 1:
			dev_info(&adapter->pdev->dev,
				 "%s set to dynamic mode\n", opt.name);
			adapter->itr = 20000;
			अवरोध;
		हाल 2:
			dev_info(&adapter->pdev->dev,
				 "%s Invalid mode - setting default\n",
				 opt.name);
			adapter->itr_setting = opt.def;
			fallthrough;
		हाल 3:
			dev_info(&adapter->pdev->dev,
				 "%s set to dynamic conservative mode\n",
				 opt.name);
			adapter->itr = 20000;
			अवरोध;
		हाल 4:
			dev_info(&adapter->pdev->dev,
				 "%s set to simplified (2000-8000 ints) mode\n",
				 opt.name);
			अवरोध;
		शेष:
			/* Save the setting, because the dynamic bits
			 * change itr.
			 *
			 * Clear the lower two bits because
			 * they are used as control.
			 */
			adapter->itr_setting &= ~3;
			अवरोध;
		पूर्ण
	पूर्ण
	/* Interrupt Mode */
	अणु
		अटल काष्ठा e1000_option opt = अणु
			.type = range_option,
			.name = "Interrupt Mode",
#अगर_अघोषित CONFIG_PCI_MSI
			.err  = "defaulting to 0 (legacy)",
			.def  = E1000E_INT_MODE_LEGACY,
			.arg  = अणु .r = अणु .min = 0,
					 .max = 0 पूर्ण पूर्ण
#पूर्ण_अगर
		पूर्ण;

#अगर_घोषित CONFIG_PCI_MSI
		अगर (adapter->flags & FLAG_HAS_MSIX) अणु
			opt.err = kstrdup("defaulting to 2 (MSI-X)",
					  GFP_KERNEL);
			opt.def = E1000E_INT_MODE_MSIX;
			opt.arg.r.max = E1000E_INT_MODE_MSIX;
		पूर्ण अन्यथा अणु
			opt.err = kstrdup("defaulting to 1 (MSI)", GFP_KERNEL);
			opt.def = E1000E_INT_MODE_MSI;
			opt.arg.r.max = E1000E_INT_MODE_MSI;
		पूर्ण

		अगर (!opt.err) अणु
			dev_err(&adapter->pdev->dev,
				"Failed to allocate memory\n");
			वापस;
		पूर्ण
#पूर्ण_अगर

		अगर (num_IntMode > bd) अणु
			अचिन्हित पूर्णांक पूर्णांक_mode = IntMode[bd];

			e1000_validate_option(&पूर्णांक_mode, &opt, adapter);
			adapter->पूर्णांक_mode = पूर्णांक_mode;
		पूर्ण अन्यथा अणु
			adapter->पूर्णांक_mode = opt.def;
		पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
		kमुक्त(opt.err);
#पूर्ण_अगर
	पूर्ण
	/* Smart Power Down */
	अणु
		अटल स्थिर काष्ठा e1000_option opt = अणु
			.type = enable_option,
			.name = "PHY Smart Power Down",
			.err  = "defaulting to Disabled",
			.def  = OPTION_DISABLED
		पूर्ण;

		अगर (num_SmartPowerDownEnable > bd) अणु
			अचिन्हित पूर्णांक spd = SmartPowerDownEnable[bd];

			e1000_validate_option(&spd, &opt, adapter);
			अगर ((adapter->flags & FLAG_HAS_SMART_POWER_DOWN) && spd)
				adapter->flags |= FLAG_SMART_POWER_DOWN;
		पूर्ण
	पूर्ण
	/* CRC Stripping */
	अणु
		अटल स्थिर काष्ठा e1000_option opt = अणु
			.type = enable_option,
			.name = "CRC Stripping",
			.err  = "defaulting to Enabled",
			.def  = OPTION_ENABLED
		पूर्ण;

		अगर (num_CrcStripping > bd) अणु
			अचिन्हित पूर्णांक crc_stripping = CrcStripping[bd];

			e1000_validate_option(&crc_stripping, &opt, adapter);
			अगर (crc_stripping == OPTION_ENABLED) अणु
				adapter->flags2 |= FLAG2_CRC_STRIPPING;
				adapter->flags2 |= FLAG2_DFLT_CRC_STRIPPING;
			पूर्ण
		पूर्ण अन्यथा अणु
			adapter->flags2 |= FLAG2_CRC_STRIPPING;
			adapter->flags2 |= FLAG2_DFLT_CRC_STRIPPING;
		पूर्ण
	पूर्ण
	/* Kumeran Lock Loss Workaround */
	अणु
		अटल स्थिर काष्ठा e1000_option opt = अणु
			.type = enable_option,
			.name = "Kumeran Lock Loss Workaround",
			.err  = "defaulting to Enabled",
			.def  = OPTION_ENABLED
		पूर्ण;
		bool enabled = opt.def;

		अगर (num_KumeranLockLoss > bd) अणु
			अचिन्हित पूर्णांक kmrn_lock_loss = KumeranLockLoss[bd];

			e1000_validate_option(&kmrn_lock_loss, &opt, adapter);
			enabled = kmrn_lock_loss;
		पूर्ण

		अगर (hw->mac.type == e1000_ich8lan)
			e1000e_set_kmrn_lock_loss_workaround_ich8lan(hw,
								     enabled);
	पूर्ण
	/* Write-protect NVM */
	अणु
		अटल स्थिर काष्ठा e1000_option opt = अणु
			.type = enable_option,
			.name = "Write-protect NVM",
			.err  = "defaulting to Enabled",
			.def  = OPTION_ENABLED
		पूर्ण;

		अगर (adapter->flags & FLAG_IS_ICH) अणु
			अगर (num_WriteProtectNVM > bd) अणु
				अचिन्हित पूर्णांक ग_लिखो_protect_nvm =
				    WriteProtectNVM[bd];
				e1000_validate_option(&ग_लिखो_protect_nvm, &opt,
						      adapter);
				अगर (ग_लिखो_protect_nvm)
					adapter->flags |= FLAG_READ_ONLY_NVM;
			पूर्ण अन्यथा अणु
				अगर (opt.def)
					adapter->flags |= FLAG_READ_ONLY_NVM;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
