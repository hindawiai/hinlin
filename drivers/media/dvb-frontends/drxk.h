<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _DRXK_H_
#घोषणा _DRXK_H_

#समावेश <linux/types.h>
#समावेश <linux/i2c.h>

/**
 * काष्ठा drxk_config - Configure the initial parameters क्रम DRX-K
 *
 * @adr:		I2C address of the DRX-K
 * @parallel_ts:	True means that the device uses parallel TS,
 *			Serial otherwise.
 * @dynamic_clk:	True means that the घड़ी will be dynamically
 *			adjusted. Static घड़ी otherwise.
 * @enable_merr_cfg:	Enable SIO_PDR_PERR_CFG/SIO_PDR_MVAL_CFG.
 * @single_master:	Device is on the single master mode
 * @no_i2c_bridge:	Don't चयन the I2C bridge to talk with tuner
 * @antenna_gpio:	GPIO bit used to control the antenna
 * @antenna_dvbt:	GPIO bit क्रम changing antenna to DVB-C. A value of 1
 *			means that 1=DVBC, 0 = DVBT. Zero means the opposite.
 * @mpeg_out_clk_strength: DRXK Mpeg output घड़ी drive strength.
 * @chunk_size:		maximum size क्रम I2C messages
 * @microcode_name:	Name of the firmware file with the microcode
 * @qam_demod_parameter_count:	The number of parameters used क्रम the command
 *				to set the demodulator parameters. All
 *				firmwares are using the 2-parameter command.
 *				An exception is the ``drxk_a3.mc`` firmware,
 *				which uses the 4-parameter command.
 *				A value of 0 (शेष) or lower indicates that
 *				the correct number of parameters will be
 *				स्वतःmatically detected.
 *
 * On the ``*_gpio`` vars, bit 0 is UIO-1, bit 1 is UIO-2 and bit 2 is
 * UIO-3.
 */
काष्ठा drxk_config अणु
	u8	adr;
	bool	single_master;
	bool	no_i2c_bridge;
	bool	parallel_ts;
	bool	dynamic_clk;
	bool	enable_merr_cfg;

	bool	antenna_dvbt;
	u16	antenna_gpio;

	u8	mpeg_out_clk_strength;
	पूर्णांक	chunk_size;

	स्थिर अक्षर	*microcode_name;
	पूर्णांक		 qam_demod_parameter_count;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_DRXK)
/**
 * drxk_attach - Attach a drxk demod
 *
 * @config: poपूर्णांकer to &काष्ठा drxk_config with demod configuration.
 * @i2c: i2c adapter to use.
 *
 * वापस: FE poपूर्णांकer on success, शून्य on failure.
 */
बाह्य काष्ठा dvb_frontend *drxk_attach(स्थिर काष्ठा drxk_config *config,
					काष्ठा i2c_adapter *i2c);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *drxk_attach(स्थिर काष्ठा drxk_config *config,
					काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
