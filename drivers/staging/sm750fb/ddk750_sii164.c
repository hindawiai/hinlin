<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा USE_DVICHIP
#अगर_घोषित USE_DVICHIP

#समावेश "ddk750_sii164.h"
#समावेश "ddk750_hwi2c.h"

/* I2C Address of each SII164 chip */
#घोषणा SII164_I2C_ADDRESS                  0x70

/* Define this definition to use hardware i2c. */
#घोषणा USE_HW_I2C

#अगर_घोषित USE_HW_I2C
    #घोषणा i2cWriteReg sm750_hw_i2c_ग_लिखो_reg
    #घोषणा i2cReadReg  sm750_hw_i2c_पढ़ो_reg
#अन्यथा
    #घोषणा i2cWriteReg sm750_sw_i2c_ग_लिखो_reg
    #घोषणा i2cReadReg  sm750_sw_i2c_पढ़ो_reg
#पूर्ण_अगर

/* SII164 Venकरोr and Device ID */
#घोषणा SII164_VENDOR_ID                    0x0001
#घोषणा SII164_DEVICE_ID                    0x0006

#अगर_घोषित SII164_FULL_FUNCTIONS
/* Name of the DVI Controller chip */
अटल अक्षर *gDviCtrlChipName = "Silicon Image SiI 164";
#पूर्ण_अगर

/*
 *  sii164GetVenकरोrID
 *      This function माला_लो the venकरोr ID of the DVI controller chip.
 *
 *  Output:
 *      Venकरोr ID
 */
अचिन्हित लघु sii164GetVenकरोrID(व्योम)
अणु
	अचिन्हित लघु venकरोrID;

	venकरोrID = ((अचिन्हित लघु)i2cReadReg(SII164_I2C_ADDRESS,
					       SII164_VENDOR_ID_HIGH) << 8) |
		   (अचिन्हित लघु)i2cReadReg(SII164_I2C_ADDRESS,
					      SII164_VENDOR_ID_LOW);

	वापस venकरोrID;
पूर्ण

/*
 *  sii164GetDeviceID
 *      This function माला_लो the device ID of the DVI controller chip.
 *
 *  Output:
 *      Device ID
 */
अचिन्हित लघु sii164GetDeviceID(व्योम)
अणु
	अचिन्हित लघु deviceID;

	deviceID = ((अचिन्हित लघु)i2cReadReg(SII164_I2C_ADDRESS,
					       SII164_DEVICE_ID_HIGH) << 8) |
		   (अचिन्हित लघु)i2cReadReg(SII164_I2C_ADDRESS,
					      SII164_DEVICE_ID_LOW);

	वापस deviceID;
पूर्ण

/*
 *  DVI.C will handle all SiI164 chip stuffs and try its best to make code
 *  minimal and useful
 */

/*
 *  sii164InitChip
 *      This function initialize and detect the DVI controller chip.
 *
 *  Input:
 *      edge_select           - Edge Select:
 *                               0 = Input data is falling edge latched (falling
 *                                   edge latched first in dual edge mode)
 *                               1 = Input data is rising edge latched (rising
 *                                   edge latched first in dual edge mode)
 *      bus_select            - Input Bus Select:
 *                               0 = Input data bus is 12-bits wide
 *                               1 = Input data bus is 24-bits wide
 *      dual_edge_clk_select  - Dual Edge Clock Select
 *                               0 = Input data is single edge latched
 *                               1 = Input data is dual edge latched
 *      hsync_enable          - Horizontal Sync Enable:
 *                               0 = HSYNC input is transmitted as fixed LOW
 *                               1 = HSYNC input is transmitted as is
 *      vsync_enable          - Vertical Sync Enable:
 *                               0 = VSYNC input is transmitted as fixed LOW
 *                               1 = VSYNC input is transmitted as is
 *      deskew_enable         - De-skewing Enable:
 *                               0 = De-skew disabled
 *                               1 = De-skew enabled
 *      deskew_setting        - De-skewing Setting (increment of 260psec)
 *                               0 = 1 step --> minimum setup / maximum hold
 *                               1 = 2 step
 *                               2 = 3 step
 *                               3 = 4 step
 *                               4 = 5 step
 *                               5 = 6 step
 *                               6 = 7 step
 *                               7 = 8 step --> maximum setup / minimum hold
 *      continuous_sync_enable- SYNC Continuous:
 *                               0 = Disable
 *                               1 = Enable
 *      pll_filter_enable     - PLL Filter Enable
 *                               0 = Disable PLL Filter
 *                               1 = Enable PLL Filter
 *      pll_filter_value      - PLL Filter अक्षरacteristics:
 *                               0~7 (recommended value is 4)
 *
 *  Output:
 *      0   - Success
 *     -1   - Fail.
 */
दीर्घ sii164InitChip(अचिन्हित अक्षर edge_select,
		    अचिन्हित अक्षर bus_select,
		    अचिन्हित अक्षर dual_edge_clk_select,
		    अचिन्हित अक्षर hsync_enable,
		    अचिन्हित अक्षर vsync_enable,
		    अचिन्हित अक्षर deskew_enable,
		    अचिन्हित अक्षर deskew_setting,
		    अचिन्हित अक्षर continuous_sync_enable,
		    अचिन्हित अक्षर pll_filter_enable,
		    अचिन्हित अक्षर pll_filter_value)
अणु
	अचिन्हित अक्षर config;

	/* Initialize the i2c bus */
#अगर_घोषित USE_HW_I2C
	/* Use fast mode. */
	sm750_hw_i2c_init(1);
#अन्यथा
	sm750_sw_i2c_init(DEFAULT_I2C_SCL, DEFAULT_I2C_SDA);
#पूर्ण_अगर

	/* Check अगर SII164 Chip exists */
	अगर ((sii164GetVenकरोrID() == SII164_VENDOR_ID) &&
	    (sii164GetDeviceID() == SII164_DEVICE_ID)) अणु
		/*
		 *  Initialize SII164 controller chip.
		 */

		/* Select the edge */
		अगर (edge_select == 0)
			config = SII164_CONFIGURATION_LATCH_FALLING;
		अन्यथा
			config = SII164_CONFIGURATION_LATCH_RISING;

		/* Select bus wide */
		अगर (bus_select == 0)
			config |= SII164_CONFIGURATION_BUS_12BITS;
		अन्यथा
			config |= SII164_CONFIGURATION_BUS_24BITS;

		/* Select Dual/Single Edge Clock */
		अगर (dual_edge_clk_select == 0)
			config |= SII164_CONFIGURATION_CLOCK_SINGLE;
		अन्यथा
			config |= SII164_CONFIGURATION_CLOCK_DUAL;

		/* Select HSync Enable */
		अगर (hsync_enable == 0)
			config |= SII164_CONFIGURATION_HSYNC_FORCE_LOW;
		अन्यथा
			config |= SII164_CONFIGURATION_HSYNC_AS_IS;

		/* Select VSync Enable */
		अगर (vsync_enable == 0)
			config |= SII164_CONFIGURATION_VSYNC_FORCE_LOW;
		अन्यथा
			config |= SII164_CONFIGURATION_VSYNC_AS_IS;

		i2cWriteReg(SII164_I2C_ADDRESS, SII164_CONFIGURATION, config);

		/*
		 * De-skew enabled with शेष 111b value.
		 * This fixes some artअगरacts problem in some mode on board 2.2.
		 * Somehow this fix करोes not affect board 2.1.
		 */
		अगर (deskew_enable == 0)
			config = SII164_DESKEW_DISABLE;
		अन्यथा
			config = SII164_DESKEW_ENABLE;

		चयन (deskew_setting) अणु
		हाल 0:
			config |= SII164_DESKEW_1_STEP;
			अवरोध;
		हाल 1:
			config |= SII164_DESKEW_2_STEP;
			अवरोध;
		हाल 2:
			config |= SII164_DESKEW_3_STEP;
			अवरोध;
		हाल 3:
			config |= SII164_DESKEW_4_STEP;
			अवरोध;
		हाल 4:
			config |= SII164_DESKEW_5_STEP;
			अवरोध;
		हाल 5:
			config |= SII164_DESKEW_6_STEP;
			अवरोध;
		हाल 6:
			config |= SII164_DESKEW_7_STEP;
			अवरोध;
		हाल 7:
			config |= SII164_DESKEW_8_STEP;
			अवरोध;
		पूर्ण
		i2cWriteReg(SII164_I2C_ADDRESS, SII164_DESKEW, config);

		/* Enable/Disable Continuous Sync. */
		अगर (continuous_sync_enable == 0)
			config = SII164_PLL_FILTER_SYNC_CONTINUOUS_DISABLE;
		अन्यथा
			config = SII164_PLL_FILTER_SYNC_CONTINUOUS_ENABLE;

		/* Enable/Disable PLL Filter */
		अगर (pll_filter_enable == 0)
			config |= SII164_PLL_FILTER_DISABLE;
		अन्यथा
			config |= SII164_PLL_FILTER_ENABLE;

		/* Set the PLL Filter value */
		config |= ((pll_filter_value & 0x07) << 1);

		i2cWriteReg(SII164_I2C_ADDRESS, SII164_PLL, config);

		/* Recover from Power Down and enable output. */
		config = i2cReadReg(SII164_I2C_ADDRESS, SII164_CONFIGURATION);
		config |= SII164_CONFIGURATION_POWER_NORMAL;
		i2cWriteReg(SII164_I2C_ADDRESS, SII164_CONFIGURATION, config);

		वापस 0;
	पूर्ण

	/* Return -1 अगर initialization fails. */
	वापस -1;
पूर्ण

/* below sii164 function is not necessary */

#अगर_घोषित SII164_FULL_FUNCTIONS

/*
 *  sii164ResetChip
 *      This function resets the DVI Controller Chip.
 */
व्योम sii164ResetChip(व्योम)
अणु
	/* Power करोwn */
	sii164SetPower(0);
	sii164SetPower(1);
पूर्ण

/*
 * sii164GetChipString
 *      This function वापसs a अक्षर string name of the current DVI Controller
 *      chip.
 *
 *      It's convenient क्रम application need to display the chip name.
 */
अक्षर *sii164GetChipString(व्योम)
अणु
	वापस gDviCtrlChipName;
पूर्ण

/*
 *  sii164SetPower
 *      This function sets the घातer configuration of the DVI Controller Chip.
 *
 *  Input:
 *      घातerUp - Flag to set the घातer करोwn or up
 */
व्योम sii164SetPower(अचिन्हित अक्षर घातerUp)
अणु
	अचिन्हित अक्षर config;

	config = i2cReadReg(SII164_I2C_ADDRESS, SII164_CONFIGURATION);
	अगर (घातerUp == 1) अणु
		/* Power up the chip */
		config &= ~SII164_CONFIGURATION_POWER_MASK;
		config |= SII164_CONFIGURATION_POWER_NORMAL;
		i2cWriteReg(SII164_I2C_ADDRESS, SII164_CONFIGURATION, config);
	पूर्ण अन्यथा अणु
		/* Power करोwn the chip */
		config &= ~SII164_CONFIGURATION_POWER_MASK;
		config |= SII164_CONFIGURATION_POWER_DOWN;
		i2cWriteReg(SII164_I2C_ADDRESS, SII164_CONFIGURATION, config);
	पूर्ण
पूर्ण

/*
 *  sii164SelectHotPlugDetectionMode
 *      This function selects the mode of the hot plug detection.
 */
अटल
व्योम sii164SelectHotPlugDetectionMode(क्रमागत sii164_hot_plug_mode hotPlugMode)
अणु
	अचिन्हित अक्षर detectReg;

	detectReg = i2cReadReg(SII164_I2C_ADDRESS, SII164_DETECT) &
		    ~SII164_DETECT_MONITOR_SENSE_OUTPUT_FLAG;
	चयन (hotPlugMode) अणु
	हाल SII164_HOTPLUG_DISABLE:
		detectReg |= SII164_DETECT_MONITOR_SENSE_OUTPUT_HIGH;
		अवरोध;
	हाल SII164_HOTPLUG_USE_MDI:
		detectReg &= ~SII164_DETECT_INTERRUPT_MASK;
		detectReg |= SII164_DETECT_INTERRUPT_BY_HTPLG_PIN;
		detectReg |= SII164_DETECT_MONITOR_SENSE_OUTPUT_MDI;
		अवरोध;
	हाल SII164_HOTPLUG_USE_RSEN:
		detectReg |= SII164_DETECT_MONITOR_SENSE_OUTPUT_RSEN;
		अवरोध;
	हाल SII164_HOTPLUG_USE_HTPLG:
		detectReg |= SII164_DETECT_MONITOR_SENSE_OUTPUT_HTPLG;
		अवरोध;
	पूर्ण

	i2cWriteReg(SII164_I2C_ADDRESS, SII164_DETECT, detectReg);
पूर्ण

/*
 *  sii164EnableHotPlugDetection
 *      This function enables the Hot Plug detection.
 *
 *  enableHotPlug   - Enable (=1) / disable (=0) Hot Plug detection
 */
व्योम sii164EnableHotPlugDetection(अचिन्हित अक्षर enableHotPlug)
अणु
	अचिन्हित अक्षर detectReg;

	detectReg = i2cReadReg(SII164_I2C_ADDRESS, SII164_DETECT);

	/* Depending on each DVI controller, need to enable the hot plug based
	 * on each inभागidual chip design.
	 */
	अगर (enableHotPlug != 0)
		sii164SelectHotPlugDetectionMode(SII164_HOTPLUG_USE_MDI);
	अन्यथा
		sii164SelectHotPlugDetectionMode(SII164_HOTPLUG_DISABLE);
पूर्ण

/*
 *  sii164IsConnected
 *      Check अगर the DVI Monitor is connected.
 *
 *  Output:
 *      0   - Not Connected
 *      1   - Connected
 */
अचिन्हित अक्षर sii164IsConnected(व्योम)
अणु
	अचिन्हित अक्षर hotPlugValue;

	hotPlugValue = i2cReadReg(SII164_I2C_ADDRESS, SII164_DETECT) &
		       SII164_DETECT_HOT_PLUG_STATUS_MASK;
	अगर (hotPlugValue == SII164_DETECT_HOT_PLUG_STATUS_ON)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/*
 *  sii164CheckInterrupt
 *      Checks अगर पूर्णांकerrupt has occurred.
 *
 *  Output:
 *      0   - No पूर्णांकerrupt
 *      1   - Interrupt occurs
 */
अचिन्हित अक्षर sii164CheckInterrupt(व्योम)
अणु
	अचिन्हित अक्षर detectReg;

	detectReg = i2cReadReg(SII164_I2C_ADDRESS, SII164_DETECT) &
		    SII164_DETECT_MONITOR_STATE_MASK;
	अगर (detectReg == SII164_DETECT_MONITOR_STATE_CHANGE)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/*
 *  sii164ClearInterrupt
 *      Clear the hot plug पूर्णांकerrupt.
 */
व्योम sii164ClearInterrupt(व्योम)
अणु
	अचिन्हित अक्षर detectReg;

	/* Clear the MDI पूर्णांकerrupt */
	detectReg = i2cReadReg(SII164_I2C_ADDRESS, SII164_DETECT);
	i2cWriteReg(SII164_I2C_ADDRESS, SII164_DETECT,
		    detectReg | SII164_DETECT_MONITOR_STATE_CLEAR);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
