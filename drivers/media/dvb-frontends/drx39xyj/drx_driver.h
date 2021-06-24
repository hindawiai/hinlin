<शैली गुरु>
/*
  Copyright (c), 2004-2005,2007-2010 Trident Microप्रणालीs, Inc.
  All rights reserved.

  Redistribution and use in source and binary क्रमms, with or without
  modअगरication, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  * Redistributions in binary क्रमm must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the करोcumentation
	and/or other materials provided with the distribution.
  * Neither the name of Trident Microप्रणालीs nor Hauppauge Computer Works
    nor the names of its contributors may be used to enकरोrse or promote
	products derived from this software without specअगरic prior written
	permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#अगर_अघोषित __DRXDRIVER_H__
#घोषणा __DRXDRIVER_H__

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>

/*
 * This काष्ठाure contains the I2C address, the device ID and a user_data poपूर्णांकer.
 * The user_data poपूर्णांकer can be used क्रम application specअगरic purposes.
 */
काष्ठा i2c_device_addr अणु
	u16 i2c_addr;		/* The I2C address of the device. */
	u16 i2c_dev_id;		/* The device identअगरier. */
	व्योम *user_data;		/* User data poपूर्णांकer */
पूर्ण;

/*
* \def IS_I2C_10BIT( addr )
* \मrief Determine अगर I2C address 'addr' is a 10 bits address or not.
* \param addr The I2C address.
* \लeturn पूर्णांक.
* \लetval 0 अगर address is not a 10 bits I2C address.
* \लetval 1 अगर address is a 10 bits I2C address.
*/
#घोषणा IS_I2C_10BIT(addr) \
	 (((addr) & 0xF8) == 0xF0)

/*------------------------------------------------------------------------------
Exported FUNCTIONS
------------------------------------------------------------------------------*/

/*
* \पn drxbsp_i2c_init()
* \मrief Initialize I2C communication module.
* \लeturn पूर्णांक Return status.
* \लetval 0 Initialization successful.
* \लetval -EIO Initialization failed.
*/
पूर्णांक drxbsp_i2c_init(व्योम);

/*
* \पn drxbsp_i2c_term()
* \मrief Terminate I2C communication module.
* \लeturn पूर्णांक Return status.
* \लetval 0 Termination successful.
* \लetval -EIO Termination failed.
*/
पूर्णांक drxbsp_i2c_term(व्योम);

/*
* \पn पूर्णांक drxbsp_i2c_ग_लिखो_पढ़ो( काष्ठा i2c_device_addr *w_dev_addr,
*                                       u16 w_count,
*                                       u8 * wData,
*                                       काष्ठा i2c_device_addr *r_dev_addr,
*                                       u16 r_count,
*                                       u8 * r_data)
* \मrief Read and/or ग_लिखो count bytes from I2C bus, store them in data[].
* \param w_dev_addr The device i2c address and the device ID to ग_लिखो to
* \param w_count   The number of bytes to ग_लिखो
* \param wData    The array to ग_लिखो the data to
* \param r_dev_addr The device i2c address and the device ID to पढ़ो from
* \param r_count   The number of bytes to पढ़ो
* \param r_data    The array to पढ़ो the data from
* \लeturn पूर्णांक Return status.
* \लetval 0 Success.
* \लetval -EIO Failure.
* \लetval -EINVAL Parameter 'wcount' is not zero but parameter
*                                       'wdata' contains शून्य.
*                                       Idem क्रम 'rcount' and 'rdata'.
*                                       Both w_dev_addr and r_dev_addr are शून्य.
*
* This function must implement an atomic ग_लिखो and/or पढ़ो action on the I2C bus
* No other process may use the I2C bus when this function is executing.
* The critical section of this function runs from and including the I2C
* ग_लिखो, up to and including the I2C पढ़ो action.
*
* The device ID can be useful अगर several devices share an I2C address.
* It can be used to control a "switch" on the I2C bus to the correct device.
*/
पूर्णांक drxbsp_i2c_ग_लिखो_पढ़ो(काष्ठा i2c_device_addr *w_dev_addr,
					u16 w_count,
					u8 *wData,
					काष्ठा i2c_device_addr *r_dev_addr,
					u16 r_count, u8 *r_data);

/*
* \पn drxbsp_i2c_error_text()
* \मrief Returns a human पढ़ोable error.
* Counter part of numerical drx_i2c_error_g.
*
* \लeturn अक्षर* Poपूर्णांकer to human पढ़ोable error text.
*/
अक्षर *drxbsp_i2c_error_text(व्योम);

/*
* \खar drx_i2c_error_g;
* \मrief I2C specअगरic error codes, platक्रमm dependent.
*/
बाह्य पूर्णांक drx_i2c_error_g;

#घोषणा TUNER_MODE_SUB0    0x0001	/* क्रम sub-mode (e.g. RF-AGC setting) */
#घोषणा TUNER_MODE_SUB1    0x0002	/* क्रम sub-mode (e.g. RF-AGC setting) */
#घोषणा TUNER_MODE_SUB2    0x0004	/* क्रम sub-mode (e.g. RF-AGC setting) */
#घोषणा TUNER_MODE_SUB3    0x0008	/* क्रम sub-mode (e.g. RF-AGC setting) */
#घोषणा TUNER_MODE_SUB4    0x0010	/* क्रम sub-mode (e.g. RF-AGC setting) */
#घोषणा TUNER_MODE_SUB5    0x0020	/* क्रम sub-mode (e.g. RF-AGC setting) */
#घोषणा TUNER_MODE_SUB6    0x0040	/* क्रम sub-mode (e.g. RF-AGC setting) */
#घोषणा TUNER_MODE_SUB7    0x0080	/* क्रम sub-mode (e.g. RF-AGC setting) */

#घोषणा TUNER_MODE_DIGITAL 0x0100	/* क्रम digital channel (e.g. DVB-T)   */
#घोषणा TUNER_MODE_ANALOG  0x0200	/* क्रम analog channel  (e.g. PAL)     */
#घोषणा TUNER_MODE_SWITCH  0x0400	/* during channel चयन & scanning   */
#घोषणा TUNER_MODE_LOCK    0x0800	/* after tuner has locked             */
#घोषणा TUNER_MODE_6MHZ    0x1000	/* क्रम 6MHz bandwidth channels        */
#घोषणा TUNER_MODE_7MHZ    0x2000	/* क्रम 7MHz bandwidth channels        */
#घोषणा TUNER_MODE_8MHZ    0x4000	/* क्रम 8MHz bandwidth channels        */

#घोषणा TUNER_MODE_SUB_MAX 8
#घोषणा TUNER_MODE_SUBALL  (TUNER_MODE_SUB0 | TUNER_MODE_SUB1 | \
			      TUNER_MODE_SUB2 | TUNER_MODE_SUB3 | \
			      TUNER_MODE_SUB4 | TUNER_MODE_SUB5 | \
			      TUNER_MODE_SUB6 | TUNER_MODE_SUB7)


क्रमागत tuner_lock_status अणु
	TUNER_LOCKED,
	TUNER_NOT_LOCKED
पूर्ण;

काष्ठा tuner_common अणु
	अक्षर *name;	/* Tuner bअक्रम & type name */
	s32 min_freq_rf;	/* Lowest  RF input frequency, in kHz */
	s32 max_freq_rf;	/* Highest RF input frequency, in kHz */

	u8 sub_mode;	/* Index to sub-mode in use */
	अक्षर ***sub_mode_descriptions;	/* Poपूर्णांकer to description of sub-modes */
	u8 sub_modes;	/* Number of available sub-modes      */

	/* The following fields will be either 0, शून्य or false and करो not need
		initialisation */
	व्योम *self_check;	/* gives proof of initialization  */
	bool programmed;	/* only valid अगर self_check is OK  */
	s32 r_ffrequency;	/* only valid अगर programmed       */
	s32 i_ffrequency;	/* only valid अगर programmed       */

	व्योम *my_user_data;	/* poपूर्णांकer to associated demod instance */
	u16 my_capabilities;	/* value क्रम storing application flags  */
पूर्ण;

काष्ठा tuner_instance;

प्रकार पूर्णांक(*tuner_खोलो_func_t) (काष्ठा tuner_instance *tuner);
प्रकार पूर्णांक(*tuner_बंद_func_t) (काष्ठा tuner_instance *tuner);

प्रकार पूर्णांक(*tuner_set_frequency_func_t) (काष्ठा tuner_instance *tuner,
						u32 mode,
						s32
						frequency);

प्रकार पूर्णांक(*tuner_get_frequency_func_t) (काष्ठा tuner_instance *tuner,
						u32 mode,
						s32 *
						r_ffrequency,
						s32 *
						i_ffrequency);

प्रकार पूर्णांक(*tuner_lock_status_func_t) (काष्ठा tuner_instance *tuner,
						क्रमागत tuner_lock_status *
						lock_stat);

प्रकार पूर्णांक(*tune_ri2c_ग_लिखो_पढ़ो_func_t) (काष्ठा tuner_instance *tuner,
						काष्ठा i2c_device_addr *
						w_dev_addr, u16 w_count,
						u8 *wData,
						काष्ठा i2c_device_addr *
						r_dev_addr, u16 r_count,
						u8 *r_data);

काष्ठा tuner_ops अणु
	tuner_खोलो_func_t खोलो_func;
	tuner_बंद_func_t बंद_func;
	tuner_set_frequency_func_t set_frequency_func;
	tuner_get_frequency_func_t get_frequency_func;
	tuner_lock_status_func_t lock_status_func;
	tune_ri2c_ग_लिखो_पढ़ो_func_t i2c_ग_लिखो_पढ़ो_func;

पूर्ण;

काष्ठा tuner_instance अणु
	काष्ठा i2c_device_addr my_i2c_dev_addr;
	काष्ठा tuner_common *my_common_attr;
	व्योम *my_ext_attr;
	काष्ठा tuner_ops *my_funct;
पूर्ण;

पूर्णांक drxbsp_tuner_set_frequency(काष्ठा tuner_instance *tuner,
					u32 mode,
					s32 frequency);

पूर्णांक drxbsp_tuner_get_frequency(काष्ठा tuner_instance *tuner,
					u32 mode,
					s32 *r_ffrequency,
					s32 *i_ffrequency);

पूर्णांक drxbsp_tuner_शेष_i2c_ग_लिखो_पढ़ो(काष्ठा tuner_instance *tuner,
						काष्ठा i2c_device_addr *w_dev_addr,
						u16 w_count,
						u8 *wData,
						काष्ठा i2c_device_addr *r_dev_addr,
						u16 r_count, u8 *r_data);

/*************
*
* This section configures the DRX Data Access Protocols (DAPs).
*
**************/

/*
* \def DRXDAP_SINGLE_MASTER
* \मrief Enable I2C single or I2C multimaster mode on host.
*
* Set to 1 to enable single master mode
* Set to 0 to enable multi master mode
*
* The actual DAP implementation may be restricted to only one of the modes.
* A compiler warning or error will be generated अगर the DAP implementation
* overrides or cannot handle the mode defined below.
*/
#अगर_अघोषित DRXDAP_SINGLE_MASTER
#घोषणा DRXDAP_SINGLE_MASTER 1
#पूर्ण_अगर

/*
* \def DRXDAP_MAX_WCHUNKSIZE
* \मrief Defines maximum chunksize of an i2c ग_लिखो action by host.
*
* This indicates the maximum size of data the I2C device driver is able to
* ग_लिखो at a समय. This includes I2C device address and रेजिस्टर addressing.
*
* This maximum size may be restricted by the actual DAP implementation.
* A compiler warning or error will be generated अगर the DAP implementation
* overrides or cannot handle the chunksize defined below.
*
* Beware that the DAP uses  DRXDAP_MAX_WCHUNKSIZE to create a temporary data
* buffer. Do not undefine or choose too large, unless your प्रणाली is able to
* handle a stack buffer of that size.
*
*/
#अगर_अघोषित DRXDAP_MAX_WCHUNKSIZE
#घोषणा  DRXDAP_MAX_WCHUNKSIZE 60
#पूर्ण_अगर

/*
* \def DRXDAP_MAX_RCHUNKSIZE
* \मrief Defines maximum chunksize of an i2c पढ़ो action by host.
*
* This indicates the maximum size of data the I2C device driver is able to पढ़ो
* at a समय. Minimum value is 2. Also, the पढ़ो chunk size must be even.
*
* This maximum size may be restricted by the actual DAP implementation.
* A compiler warning or error will be generated अगर the DAP implementation
* overrides or cannot handle the chunksize defined below.
*/
#अगर_अघोषित DRXDAP_MAX_RCHUNKSIZE
#घोषणा  DRXDAP_MAX_RCHUNKSIZE 60
#पूर्ण_अगर

/*************
*
* This section describes drxdriver defines.
*
**************/

/*
* \def DRX_UNKNOWN
* \मrief Generic UNKNOWN value क्रम DRX क्रमागतerated types.
*
* Used to indicate that the parameter value is unknown or not yet initialized.
*/
#अगर_अघोषित DRX_UNKNOWN
#घोषणा DRX_UNKNOWN (254)
#पूर्ण_अगर

/*
* \def DRX_AUTO
* \मrief Generic AUTO value क्रम DRX क्रमागतerated types.
*
* Used to inकाष्ठा the driver to स्वतःmatically determine the value of the
* parameter.
*/
#अगर_अघोषित DRX_AUTO
#घोषणा DRX_AUTO    (255)
#पूर्ण_अगर

/*************
*
* This section describes flag definitions क्रम the device capbilities.
*
**************/

/*
* \मrief LNA capability flag
*
* Device has a Low Noise Amplअगरier
*
*/
#घोषणा DRX_CAPABILITY_HAS_LNA           (1UL <<  0)
/*
* \मrief OOB-RX capability flag
*
* Device has OOB-RX
*
*/
#घोषणा DRX_CAPABILITY_HAS_OOBRX         (1UL <<  1)
/*
* \मrief ATV capability flag
*
* Device has ATV
*
*/
#घोषणा DRX_CAPABILITY_HAS_ATV           (1UL <<  2)
/*
* \मrief DVB-T capability flag
*
* Device has DVB-T
*
*/
#घोषणा DRX_CAPABILITY_HAS_DVBT          (1UL <<  3)
/*
* \मrief  ITU-B capability flag
*
* Device has ITU-B
*
*/
#घोषणा DRX_CAPABILITY_HAS_ITUB          (1UL <<  4)
/*
* \मrief  Audio capability flag
*
* Device has Audio
*
*/
#घोषणा DRX_CAPABILITY_HAS_AUD           (1UL <<  5)
/*
* \मrief  SAW चयन capability flag
*
* Device has SAW चयन
*
*/
#घोषणा DRX_CAPABILITY_HAS_SAWSW         (1UL <<  6)
/*
* \मrief  GPIO1 capability flag
*
* Device has GPIO1
*
*/
#घोषणा DRX_CAPABILITY_HAS_GPIO1         (1UL <<  7)
/*
* \मrief  GPIO2 capability flag
*
* Device has GPIO2
*
*/
#घोषणा DRX_CAPABILITY_HAS_GPIO2         (1UL <<  8)
/*
* \मrief  IRQN capability flag
*
* Device has IRQN
*
*/
#घोषणा DRX_CAPABILITY_HAS_IRQN          (1UL <<  9)
/*
* \मrief  8VSB capability flag
*
* Device has 8VSB
*
*/
#घोषणा DRX_CAPABILITY_HAS_8VSB          (1UL << 10)
/*
* \मrief  SMA-TX capability flag
*
* Device has SMATX
*
*/
#घोषणा DRX_CAPABILITY_HAS_SMATX         (1UL << 11)
/*
* \मrief  SMA-RX capability flag
*
* Device has SMARX
*
*/
#घोषणा DRX_CAPABILITY_HAS_SMARX         (1UL << 12)
/*
* \मrief  ITU-A/C capability flag
*
* Device has ITU-A/C
*
*/
#घोषणा DRX_CAPABILITY_HAS_ITUAC         (1UL << 13)

/*-------------------------------------------------------------------------
MACROS
-------------------------------------------------------------------------*/
/* Macros to stringअगरy the version number */
#घोषणा DRX_VERSIONSTRING(MAJOR, MINOR, PATCH) \
	 DRX_VERSIONSTRING_HELP(MAJOR)"." \
	 DRX_VERSIONSTRING_HELP(MINOR)"." \
	 DRX_VERSIONSTRING_HELP(PATCH)
#घोषणा DRX_VERSIONSTRING_HELP(NUM) #NUM

/*
* \मrief Macro to create byte array elements from 16 bit पूर्णांकegers.
* This macro is used to create byte arrays क्रम block ग_लिखोs.
* Block ग_लिखोs speed up I2C traffic between host and demod.
* The macro takes care of the required byte order in a 16 bits word.
* x->lowbyte(x), highbyte(x)
*/
#घोषणा DRX_16TO8(x) ((u8) (((u16)x) & 0xFF)), \
			((u8)((((u16)x)>>8)&0xFF))

/*
* \मrief Macro to convert 16 bit रेजिस्टर value to a s32
*/
#घोषणा DRX_U16TODRXFREQ(x)   ((x & 0x8000) ? \
				 ((s32) \
				    (((u32) x) | 0xFFFF0000)) : \
				 ((s32) x))

/*-------------------------------------------------------------------------
ENUM
-------------------------------------------------------------------------*/

/*
* \क्रमागत क्रमागत drx_standard
* \मrief Modulation standards.
*/
क्रमागत drx_standard अणु
	DRX_STANDARD_DVBT = 0, /*< Terrestrial DVB-T.               */
	DRX_STANDARD_8VSB,     /*< Terrestrial 8VSB.                */
	DRX_STANDARD_NTSC,     /*< Terrestrial\Cable analog NTSC.   */
	DRX_STANDARD_PAL_SECAM_BG,
				/*< Terrestrial analog PAL/SECAM B/G */
	DRX_STANDARD_PAL_SECAM_DK,
				/*< Terrestrial analog PAL/SECAM D/K */
	DRX_STANDARD_PAL_SECAM_I,
				/*< Terrestrial analog PAL/SECAM I   */
	DRX_STANDARD_PAL_SECAM_L,
				/*< Terrestrial analog PAL/SECAM L
					with negative modulation        */
	DRX_STANDARD_PAL_SECAM_LP,
				/*< Terrestrial analog PAL/SECAM L
					with positive modulation        */
	DRX_STANDARD_ITU_A,    /*< Cable ITU ANNEX A.               */
	DRX_STANDARD_ITU_B,    /*< Cable ITU ANNEX B.               */
	DRX_STANDARD_ITU_C,    /*< Cable ITU ANNEX C.               */
	DRX_STANDARD_ITU_D,    /*< Cable ITU ANNEX D.               */
	DRX_STANDARD_FM,       /*< Terrestrial\Cable FM radio       */
	DRX_STANDARD_DTMB,     /*< Terrestrial DTMB standard (China)*/
	DRX_STANDARD_UNKNOWN = DRX_UNKNOWN,
				/*< Standard unknown.                */
	DRX_STANDARD_AUTO = DRX_AUTO
				/*< Autodetect standard.             */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_standard
* \मrief Modulation sub-standards.
*/
क्रमागत drx_substandard अणु
	DRX_SUBSTANDARD_MAIN = 0, /*< Main subvariant of standard   */
	DRX_SUBSTANDARD_ATV_BG_SCANDINAVIA,
	DRX_SUBSTANDARD_ATV_DK_POLAND,
	DRX_SUBSTANDARD_ATV_DK_CHINA,
	DRX_SUBSTANDARD_UNKNOWN = DRX_UNKNOWN,
					/*< Sub-standard unknown.         */
	DRX_SUBSTANDARD_AUTO = DRX_AUTO
					/*< Auto (शेष) sub-standard   */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_bandwidth
* \मrief Channel bandwidth or channel spacing.
*/
क्रमागत drx_bandwidth अणु
	DRX_BANDWIDTH_8MHZ = 0,	 /*< Bandwidth 8 MHz.   */
	DRX_BANDWIDTH_7MHZ,	 /*< Bandwidth 7 MHz.   */
	DRX_BANDWIDTH_6MHZ,	 /*< Bandwidth 6 MHz.   */
	DRX_BANDWIDTH_UNKNOWN = DRX_UNKNOWN,
					/*< Bandwidth unknown. */
	DRX_BANDWIDTH_AUTO = DRX_AUTO
					/*< Auto Set Bandwidth */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_mirror
* \मrief Indicate अगर channel spectrum is mirrored or not.
*/
क्रमागत drx_mirror अणु
	DRX_MIRROR_NO = 0,   /*< Spectrum is not mirrored.           */
	DRX_MIRROR_YES,	     /*< Spectrum is mirrored.               */
	DRX_MIRROR_UNKNOWN = DRX_UNKNOWN,
				/*< Unknown अगर spectrum is mirrored.    */
	DRX_MIRROR_AUTO = DRX_AUTO
				/*< Autodetect अगर spectrum is mirrored. */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_modulation
* \मrief Constellation type of the channel.
*/
क्रमागत drx_modulation अणु
	DRX_CONSTELLATION_BPSK = 0,  /*< Modulation is BPSK.       */
	DRX_CONSTELLATION_QPSK,	     /*< Constellation is QPSK.    */
	DRX_CONSTELLATION_PSK8,	     /*< Constellation is PSK8.    */
	DRX_CONSTELLATION_QAM16,     /*< Constellation is QAM16.   */
	DRX_CONSTELLATION_QAM32,     /*< Constellation is QAM32.   */
	DRX_CONSTELLATION_QAM64,     /*< Constellation is QAM64.   */
	DRX_CONSTELLATION_QAM128,    /*< Constellation is QAM128.  */
	DRX_CONSTELLATION_QAM256,    /*< Constellation is QAM256.  */
	DRX_CONSTELLATION_QAM512,    /*< Constellation is QAM512.  */
	DRX_CONSTELLATION_QAM1024,   /*< Constellation is QAM1024. */
	DRX_CONSTELLATION_QPSK_NR,   /*< Constellation is QPSK_NR  */
	DRX_CONSTELLATION_UNKNOWN = DRX_UNKNOWN,
					/*< Constellation unknown.    */
	DRX_CONSTELLATION_AUTO = DRX_AUTO
					/*< Autodetect स्थिरellation. */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_hierarchy
* \मrief Hierarchy of the channel.
*/
क्रमागत drx_hierarchy अणु
	DRX_HIERARCHY_NONE = 0,	/*< None hierarchical channel.     */
	DRX_HIERARCHY_ALPHA1,	/*< Hierarchical channel, alpha=1. */
	DRX_HIERARCHY_ALPHA2,	/*< Hierarchical channel, alpha=2. */
	DRX_HIERARCHY_ALPHA4,	/*< Hierarchical channel, alpha=4. */
	DRX_HIERARCHY_UNKNOWN = DRX_UNKNOWN,
				/*< Hierarchy unknown.             */
	DRX_HIERARCHY_AUTO = DRX_AUTO
				/*< Autodetect hierarchy.          */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_priority
* \मrief Channel priority in हाल of hierarchical transmission.
*/
क्रमागत drx_priority अणु
	DRX_PRIORITY_LOW = 0,  /*< Low priority channel.  */
	DRX_PRIORITY_HIGH,     /*< High priority channel. */
	DRX_PRIORITY_UNKNOWN = DRX_UNKNOWN
				/*< Priority unknown.      */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_coderate
* \मrief Channel priority in हाल of hierarchical transmission.
*/
क्रमागत drx_coderate अणु
		DRX_CODERATE_1DIV2 = 0,	/*< Code rate 1/2nd.      */
		DRX_CODERATE_2DIV3,	/*< Code rate 2/3nd.      */
		DRX_CODERATE_3DIV4,	/*< Code rate 3/4nd.      */
		DRX_CODERATE_5DIV6,	/*< Code rate 5/6nd.      */
		DRX_CODERATE_7DIV8,	/*< Code rate 7/8nd.      */
		DRX_CODERATE_UNKNOWN = DRX_UNKNOWN,
					/*< Code rate unknown.    */
		DRX_CODERATE_AUTO = DRX_AUTO
					/*< Autodetect code rate. */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_guard
* \मrief Guard पूर्णांकerval of a channel.
*/
क्रमागत drx_guard अणु
	DRX_GUARD_1DIV32 = 0, /*< Guard पूर्णांकerval 1/32nd.     */
	DRX_GUARD_1DIV16,     /*< Guard पूर्णांकerval 1/16th.     */
	DRX_GUARD_1DIV8,      /*< Guard पूर्णांकerval 1/8th.      */
	DRX_GUARD_1DIV4,      /*< Guard पूर्णांकerval 1/4th.      */
	DRX_GUARD_UNKNOWN = DRX_UNKNOWN,
				/*< Guard पूर्णांकerval unknown.    */
	DRX_GUARD_AUTO = DRX_AUTO
				/*< Autodetect guard पूर्णांकerval. */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_fft_mode
* \मrief FFT mode.
*/
क्रमागत drx_fft_mode अणु
	DRX_FFTMODE_2K = 0,    /*< 2K FFT mode.         */
	DRX_FFTMODE_4K,	       /*< 4K FFT mode.         */
	DRX_FFTMODE_8K,	       /*< 8K FFT mode.         */
	DRX_FFTMODE_UNKNOWN = DRX_UNKNOWN,
				/*< FFT mode unknown.    */
	DRX_FFTMODE_AUTO = DRX_AUTO
				/*< Autodetect FFT mode. */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_classअगरication
* \मrief Channel classअगरication.
*/
क्रमागत drx_classअगरication अणु
	DRX_CLASSIFICATION_GAUSS = 0, /*< Gaussion noise.            */
	DRX_CLASSIFICATION_HVY_GAUSS, /*< Heavy Gaussion noise.      */
	DRX_CLASSIFICATION_COCHANNEL, /*< Co-channel.                */
	DRX_CLASSIFICATION_STATIC,    /*< Static echo.               */
	DRX_CLASSIFICATION_MOVING,    /*< Moving echo.               */
	DRX_CLASSIFICATION_ZERODB,    /*< Zero dB echo.              */
	DRX_CLASSIFICATION_UNKNOWN = DRX_UNKNOWN,
					/*< Unknown classअगरication     */
	DRX_CLASSIFICATION_AUTO = DRX_AUTO
					/*< Autodetect classअगरication. */
पूर्ण;

/*
* /क्रमागत क्रमागत drx_पूर्णांकerleave_mode
* /brief Interleave modes
*/
क्रमागत drx_पूर्णांकerleave_mode अणु
	DRX_INTERLEAVEMODE_I128_J1 = 0,
	DRX_INTERLEAVEMODE_I128_J1_V2,
	DRX_INTERLEAVEMODE_I128_J2,
	DRX_INTERLEAVEMODE_I64_J2,
	DRX_INTERLEAVEMODE_I128_J3,
	DRX_INTERLEAVEMODE_I32_J4,
	DRX_INTERLEAVEMODE_I128_J4,
	DRX_INTERLEAVEMODE_I16_J8,
	DRX_INTERLEAVEMODE_I128_J5,
	DRX_INTERLEAVEMODE_I8_J16,
	DRX_INTERLEAVEMODE_I128_J6,
	DRX_INTERLEAVEMODE_RESERVED_11,
	DRX_INTERLEAVEMODE_I128_J7,
	DRX_INTERLEAVEMODE_RESERVED_13,
	DRX_INTERLEAVEMODE_I128_J8,
	DRX_INTERLEAVEMODE_RESERVED_15,
	DRX_INTERLEAVEMODE_I12_J17,
	DRX_INTERLEAVEMODE_I5_J4,
	DRX_INTERLEAVEMODE_B52_M240,
	DRX_INTERLEAVEMODE_B52_M720,
	DRX_INTERLEAVEMODE_B52_M48,
	DRX_INTERLEAVEMODE_B52_M0,
	DRX_INTERLEAVEMODE_UNKNOWN = DRX_UNKNOWN,
					/*< Unknown पूर्णांकerleave mode    */
	DRX_INTERLEAVEMODE_AUTO = DRX_AUTO
					/*< Autodetect पूर्णांकerleave mode */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_carrier_mode
* \मrief Channel Carrier Mode.
*/
क्रमागत drx_carrier_mode अणु
	DRX_CARRIER_MULTI = 0,		/*< Multi carrier mode       */
	DRX_CARRIER_SINGLE,		/*< Single carrier mode      */
	DRX_CARRIER_UNKNOWN = DRX_UNKNOWN,
					/*< Carrier mode unknown.    */
	DRX_CARRIER_AUTO = DRX_AUTO	/*< Autodetect carrier mode  */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_frame_mode
* \मrief Channel Frame Mode.
*/
क्रमागत drx_frame_mode अणु
	DRX_FRAMEMODE_420 = 0,	 /*< 420 with variable PN  */
	DRX_FRAMEMODE_595,	 /*< 595                   */
	DRX_FRAMEMODE_945,	 /*< 945 with variable PN  */
	DRX_FRAMEMODE_420_FIXED_PN,
					/*< 420 with fixed PN     */
	DRX_FRAMEMODE_945_FIXED_PN,
					/*< 945 with fixed PN     */
	DRX_FRAMEMODE_UNKNOWN = DRX_UNKNOWN,
					/*< Frame mode unknown.   */
	DRX_FRAMEMODE_AUTO = DRX_AUTO
					/*< Autodetect frame mode */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_tps_frame
* \मrief Frame number in current super-frame.
*/
क्रमागत drx_tps_frame अणु
	DRX_TPS_FRAME1 = 0,	  /*< TPS frame 1.       */
	DRX_TPS_FRAME2,		  /*< TPS frame 2.       */
	DRX_TPS_FRAME3,		  /*< TPS frame 3.       */
	DRX_TPS_FRAME4,		  /*< TPS frame 4.       */
	DRX_TPS_FRAME_UNKNOWN = DRX_UNKNOWN
					/*< TPS frame unknown. */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_ldpc
* \मrief TPS LDPC .
*/
क्रमागत drx_ldpc अणु
	DRX_LDPC_0_4 = 0,	  /*< LDPC 0.4           */
	DRX_LDPC_0_6,		  /*< LDPC 0.6           */
	DRX_LDPC_0_8,		  /*< LDPC 0.8           */
	DRX_LDPC_UNKNOWN = DRX_UNKNOWN,
					/*< LDPC unknown.      */
	DRX_LDPC_AUTO = DRX_AUTO  /*< Autodetect LDPC    */
पूर्ण;

/*
* \क्रमागत क्रमागत drx_pilot_mode
* \मrief Pilot modes in DTMB.
*/
क्रमागत drx_pilot_mode अणु
	DRX_PILOT_ON = 0,	  /*< Pilot On             */
	DRX_PILOT_OFF,		  /*< Pilot Off            */
	DRX_PILOT_UNKNOWN = DRX_UNKNOWN,
					/*< Pilot unknown.       */
	DRX_PILOT_AUTO = DRX_AUTO /*< Autodetect Pilot     */
पूर्ण;

/*
 * क्रमागत drxu_code_action - indicate अगर firmware has to be uploaded or verअगरied.
 * @UCODE_UPLOAD:	Upload the microcode image to device
 * @UCODE_VERIFY:	Compare microcode image with code on device
 */
क्रमागत drxu_code_action अणु
	UCODE_UPLOAD,
	UCODE_VERIFY
पूर्ण;

/*
* \क्रमागत क्रमागत drx_lock_status * \मrief Used to reflect current lock status of demodulator.
*
* The generic lock states have device dependent semantics.

		DRX_NEVER_LOCK = 0,
			      **< Device will never lock on this संकेत *
		DRX_NOT_LOCKED,
			      **< Device has no lock at all             *
		DRX_LOCK_STATE_1,
			      **< Generic lock state                    *
		DRX_LOCK_STATE_2,
			      **< Generic lock state                    *
		DRX_LOCK_STATE_3,
			      **< Generic lock state                    *
		DRX_LOCK_STATE_4,
			      **< Generic lock state                    *
		DRX_LOCK_STATE_5,
			      **< Generic lock state                    *
		DRX_LOCK_STATE_6,
			      **< Generic lock state                    *
		DRX_LOCK_STATE_7,
			      **< Generic lock state                    *
		DRX_LOCK_STATE_8,
			      **< Generic lock state                    *
		DRX_LOCK_STATE_9,
			      **< Generic lock state                    *
		DRX_LOCKED    **< Device is in lock                     *
*/

क्रमागत drx_lock_status अणु
	DRX_NEVER_LOCK = 0,
	DRX_NOT_LOCKED,
	DRX_LOCK_STATE_1,
	DRX_LOCK_STATE_2,
	DRX_LOCK_STATE_3,
	DRX_LOCK_STATE_4,
	DRX_LOCK_STATE_5,
	DRX_LOCK_STATE_6,
	DRX_LOCK_STATE_7,
	DRX_LOCK_STATE_8,
	DRX_LOCK_STATE_9,
	DRX_LOCKED
पूर्ण;

/*
* \क्रमागत क्रमागत drx_uio* \मrief Used to address a User IO (UIO).
*/
क्रमागत drx_uio अणु
	DRX_UIO1,
	DRX_UIO2,
	DRX_UIO3,
	DRX_UIO4,
	DRX_UIO5,
	DRX_UIO6,
	DRX_UIO7,
	DRX_UIO8,
	DRX_UIO9,
	DRX_UIO10,
	DRX_UIO11,
	DRX_UIO12,
	DRX_UIO13,
	DRX_UIO14,
	DRX_UIO15,
	DRX_UIO16,
	DRX_UIO17,
	DRX_UIO18,
	DRX_UIO19,
	DRX_UIO20,
	DRX_UIO21,
	DRX_UIO22,
	DRX_UIO23,
	DRX_UIO24,
	DRX_UIO25,
	DRX_UIO26,
	DRX_UIO27,
	DRX_UIO28,
	DRX_UIO29,
	DRX_UIO30,
	DRX_UIO31,
	DRX_UIO32,
	DRX_UIO_MAX = DRX_UIO32
पूर्ण;

/*
* \क्रमागत क्रमागत drxuio_mode * \मrief Used to configure the modus opअक्रमi of a UIO.
*
* DRX_UIO_MODE_FIRMWARE is an old uio mode.
* It is replaced by the modes DRX_UIO_MODE_FIRMWARE0 .. DRX_UIO_MODE_FIRMWARE9.
* To be backward compatible DRX_UIO_MODE_FIRMWARE is equivalent to
* DRX_UIO_MODE_FIRMWARE0.
*/
क्रमागत drxuio_mode अणु
	DRX_UIO_MODE_DISABLE = 0x01,
			    /*< not used, pin is configured as input */
	DRX_UIO_MODE_READWRITE = 0x02,
			    /*< used क्रम पढ़ो/ग_लिखो by application   */
	DRX_UIO_MODE_FIRMWARE = 0x04,
			    /*< controlled by firmware, function 0   */
	DRX_UIO_MODE_FIRMWARE0 = DRX_UIO_MODE_FIRMWARE,
					    /*< same as above        */
	DRX_UIO_MODE_FIRMWARE1 = 0x08,
			    /*< controlled by firmware, function 1   */
	DRX_UIO_MODE_FIRMWARE2 = 0x10,
			    /*< controlled by firmware, function 2   */
	DRX_UIO_MODE_FIRMWARE3 = 0x20,
			    /*< controlled by firmware, function 3   */
	DRX_UIO_MODE_FIRMWARE4 = 0x40,
			    /*< controlled by firmware, function 4   */
	DRX_UIO_MODE_FIRMWARE5 = 0x80
			    /*< controlled by firmware, function 5   */
पूर्ण;

/*
* \क्रमागत क्रमागत drxoob_करोwnstream_standard * \मrief Used to select OOB standard.
*
* Based on ANSI 55-1 and 55-2
*/
क्रमागत drxoob_करोwnstream_standard अणु
	DRX_OOB_MODE_A = 0,
		       /*< ANSI 55-1   */
	DRX_OOB_MODE_B_GRADE_A,
		       /*< ANSI 55-2 A */
	DRX_OOB_MODE_B_GRADE_B
		       /*< ANSI 55-2 B */
पूर्ण;

/*-------------------------------------------------------------------------
STRUCTS
-------------------------------------------------------------------------*/

/*============================================================================*/
/*============================================================================*/
/*== CTRL CFG related data काष्ठाures ========================================*/
/*============================================================================*/
/*============================================================================*/

#अगर_अघोषित DRX_CFG_BASE
#घोषणा DRX_CFG_BASE          0
#पूर्ण_अगर

#घोषणा DRX_CFG_MPEG_OUTPUT         (DRX_CFG_BASE +  0)	/* MPEG TS output    */
#घोषणा DRX_CFG_PKTERR              (DRX_CFG_BASE +  1)	/* Packet Error      */
#घोषणा DRX_CFG_SYMCLK_OFFS         (DRX_CFG_BASE +  2)	/* Symbol Clk Offset */
#घोषणा DRX_CFG_SMA                 (DRX_CFG_BASE +  3)	/* Smart Antenna     */
#घोषणा DRX_CFG_PINSAFE             (DRX_CFG_BASE +  4)	/* Pin safe mode     */
#घोषणा DRX_CFG_SUBSTANDARD         (DRX_CFG_BASE +  5)	/* substandard       */
#घोषणा DRX_CFG_AUD_VOLUME          (DRX_CFG_BASE +  6)	/* volume            */
#घोषणा DRX_CFG_AUD_RDS             (DRX_CFG_BASE +  7)	/* rds               */
#घोषणा DRX_CFG_AUD_AUTOSOUND       (DRX_CFG_BASE +  8)	/* ASS & ASC         */
#घोषणा DRX_CFG_AUD_ASS_THRES       (DRX_CFG_BASE +  9)	/* ASS Thresholds    */
#घोषणा DRX_CFG_AUD_DEVIATION       (DRX_CFG_BASE + 10)	/* Deviation         */
#घोषणा DRX_CFG_AUD_PRESCALE        (DRX_CFG_BASE + 11)	/* Prescale          */
#घोषणा DRX_CFG_AUD_MIXER           (DRX_CFG_BASE + 12)	/* Mixer             */
#घोषणा DRX_CFG_AUD_AVSYNC          (DRX_CFG_BASE + 13)	/* AVSync            */
#घोषणा DRX_CFG_AUD_CARRIER         (DRX_CFG_BASE + 14)	/* Audio carriers    */
#घोषणा DRX_CFG_I2S_OUTPUT          (DRX_CFG_BASE + 15)	/* I2S output        */
#घोषणा DRX_CFG_ATV_STANDARD        (DRX_CFG_BASE + 16)	/* ATV standard      */
#घोषणा DRX_CFG_SQI_SPEED           (DRX_CFG_BASE + 17)	/* SQI speed         */
#घोषणा DRX_CTRL_CFG_MAX            (DRX_CFG_BASE + 18)	/* never to be used  */

#घोषणा DRX_CFG_PINS_SAFE_MODE      DRX_CFG_PINSAFE
/*============================================================================*/
/*============================================================================*/
/*== CTRL related data काष्ठाures ============================================*/
/*============================================================================*/
/*============================================================================*/

/*
 * काष्ठा drxu_code_info	Parameters क्रम microcode upload and verfiy.
 *
 * @mc_file:	microcode file name
 *
 * Used by DRX_CTRL_LOAD_UCODE and DRX_CTRL_VERIFY_UCODE
 */
काष्ठा drxu_code_info अणु
	अक्षर			*mc_file;
पूर्ण;

/*
* \काष्ठा drx_mc_version_rec_t
* \मrief Microcode version record
* Version numbers are stored in BCD क्रमmat, as usual:
*   o major number = bits 31-20 (first three nibbles of MSW)
*   o minor number = bits 19-16 (fourth nibble of MSW)
*   o patch number = bits 15-0  (reमुख्यing nibbles in LSW)
*
* The device type indicates क्रम which the device is meant. It is based on the
* JTAG ID, using everything except the bond ID and the metal fix.
*
* Special values:
* - mc_dev_type == 0         => any device allowed
* - mc_base_version == 0.0.0 => full microcode (mc_version is the version)
* - mc_base_version != 0.0.0 => patch microcode, the base microcode version
*                             (mc_version is the version)
*/
#घोषणा AUX_VER_RECORD 0x8000

काष्ठा drx_mc_version_rec अणु
	u16 aux_type;	/* type of aux data - 0x8000 क्रम version record     */
	u32 mc_dev_type;	/* device type, based on JTAG ID                    */
	u32 mc_version;	/* version of microcode                             */
	u32 mc_base_version;	/* in हाल of patch: the original microcode version */
पूर्ण;

/*========================================*/

/*
* \काष्ठा drx_filter_info_t
* \मrief Parameters क्रम loading filter coefficients
*
* Used by DRX_CTRL_LOAD_FILTER
*/
काष्ठा drx_filter_info अणु
	u8 *data_re;
	      /*< poपूर्णांकer to coefficients क्रम RE */
	u8 *data_im;
	      /*< poपूर्णांकer to coefficients क्रम IM */
	u16 size_re;
	      /*< size of coefficients क्रम RE    */
	u16 size_im;
	      /*< size of coefficients क्रम IM    */
पूर्ण;

/*========================================*/

/*
* \काष्ठा काष्ठा drx_channel * \मrief The set of parameters describing a single channel.
*
* Used by DRX_CTRL_SET_CHANNEL and DRX_CTRL_GET_CHANNEL.
* Only certain fields need to be used क्रम a specअगरic standard.
*
*/
काष्ठा drx_channel अणु
	s32 frequency;
				/*< frequency in kHz                 */
	क्रमागत drx_bandwidth bandwidth;
				/*< bandwidth                        */
	क्रमागत drx_mirror mirror;	/*< mirrored or not on RF            */
	क्रमागत drx_modulation स्थिरellation;
				/*< स्थिरellation                    */
	क्रमागत drx_hierarchy hierarchy;
				/*< hierarchy                        */
	क्रमागत drx_priority priority;	/*< priority                         */
	क्रमागत drx_coderate coderate;	/*< coderate                         */
	क्रमागत drx_guard guard;	/*< guard पूर्णांकerval                   */
	क्रमागत drx_fft_mode ffपंचांगode;	/*< ffपंचांगode                          */
	क्रमागत drx_classअगरication classअगरication;
				/*< classअगरication                   */
	u32 symbolrate;
				/*< symbolrate in symbols/sec        */
	क्रमागत drx_पूर्णांकerleave_mode पूर्णांकerleavemode;
				/*< पूर्णांकerleaveMode QAM               */
	क्रमागत drx_ldpc ldpc;		/*< ldpc                             */
	क्रमागत drx_carrier_mode carrier;	/*< carrier                          */
	क्रमागत drx_frame_mode framemode;
				/*< frame mode                       */
	क्रमागत drx_pilot_mode pilot;	/*< pilot mode                       */
पूर्ण;

/*========================================*/

क्रमागत drx_cfg_sqi_speed अणु
	DRX_SQI_SPEED_FAST = 0,
	DRX_SQI_SPEED_MEDIUM,
	DRX_SQI_SPEED_SLOW,
	DRX_SQI_SPEED_UNKNOWN = DRX_UNKNOWN
पूर्ण;

/*========================================*/

/*
* \काष्ठा काष्ठा drx_complex * A complex number.
*
* Used by DRX_CTRL_CONSTEL.
*/
काष्ठा drx_complex अणु
	s16 im;
     /*< Imaginary part. */
	s16 re;
     /*< Real part.      */
पूर्ण;

/*========================================*/

/*
* \काष्ठा काष्ठा drx_frequency_plan * Array element of a frequency plan.
*
* Used by DRX_CTRL_SCAN_INIT.
*/
काष्ठा drx_frequency_plan अणु
	s32 first;
		     /*< First centre frequency in this band        */
	s32 last;
		     /*< Last centre frequency in this band         */
	s32 step;
		     /*< Stepping frequency in this band            */
	क्रमागत drx_bandwidth bandwidth;
		     /*< Bandwidth within this frequency band       */
	u16 ch_number;
		     /*< First channel number in this band, or first
			    index in ch_names                         */
	अक्षर **ch_names;
		     /*< Optional list of channel names in this
			    band                                     */
पूर्ण;

/*========================================*/

/*
* \काष्ठा काष्ठा drx_scan_param * Parameters क्रम channel scan.
*
* Used by DRX_CTRL_SCAN_INIT.
*/
काष्ठा drx_scan_param अणु
	काष्ठा drx_frequency_plan *frequency_plan;
				  /*< Frequency plan (array)*/
	u16 frequency_plan_size;  /*< Number of bands       */
	u32 num_tries;		  /*< Max channels tried    */
	s32 skip;	  /*< Minimum frequency step to take
					after a channel is found */
	व्योम *ext_params;	  /*< Standard specअगरic params */
पूर्ण;

/*========================================*/

/*
* \मrief Scan commands.
* Used by scanning algorithms.
*/
क्रमागत drx_scan_command अणु
		DRX_SCAN_COMMAND_INIT = 0,/*< Initialize scanning */
		DRX_SCAN_COMMAND_NEXT,	  /*< Next scan           */
		DRX_SCAN_COMMAND_STOP	  /*< Stop scanning       */
पूर्ण;

/*========================================*/

/*
* \मrief Inner scan function prototype.
*/
प्रकार पूर्णांक(*drx_scan_func_t) (व्योम *scan_context,
				     क्रमागत drx_scan_command scan_command,
				     काष्ठा drx_channel *scan_channel,
				     bool *get_next_channel);

/*========================================*/

/*
* \काष्ठा काष्ठा drxtps_info * TPS inक्रमmation, DVB-T specअगरic.
*
* Used by DRX_CTRL_TPS_INFO.
*/
	काष्ठा drxtps_info अणु
		क्रमागत drx_fft_mode ffपंचांगode;	/*< Fft mode       */
		क्रमागत drx_guard guard;	/*< Guard पूर्णांकerval */
		क्रमागत drx_modulation स्थिरellation;
					/*< Constellation  */
		क्रमागत drx_hierarchy hierarchy;
					/*< Hierarchy      */
		क्रमागत drx_coderate high_coderate;
					/*< High code rate */
		क्रमागत drx_coderate low_coderate;
					/*< Low cod rate   */
		क्रमागत drx_tps_frame frame;	/*< Tps frame      */
		u8 length;		/*< Length         */
		u16 cell_id;		/*< Cell id        */
	पूर्ण;

/*========================================*/

/*
* \मrief Power mode of device.
*
* Used by DRX_CTRL_SET_POWER_MODE.
*/
	क्रमागत drx_घातer_mode अणु
		DRX_POWER_UP = 0,
			 /*< Generic         , Power Up Mode   */
		DRX_POWER_MODE_1,
			 /*< Device specअगरic , Power Up Mode   */
		DRX_POWER_MODE_2,
			 /*< Device specअगरic , Power Up Mode   */
		DRX_POWER_MODE_3,
			 /*< Device specअगरic , Power Up Mode   */
		DRX_POWER_MODE_4,
			 /*< Device specअगरic , Power Up Mode   */
		DRX_POWER_MODE_5,
			 /*< Device specअगरic , Power Up Mode   */
		DRX_POWER_MODE_6,
			 /*< Device specअगरic , Power Up Mode   */
		DRX_POWER_MODE_7,
			 /*< Device specअगरic , Power Up Mode   */
		DRX_POWER_MODE_8,
			 /*< Device specअगरic , Power Up Mode   */

		DRX_POWER_MODE_9,
			 /*< Device specअगरic , Power Down Mode */
		DRX_POWER_MODE_10,
			 /*< Device specअगरic , Power Down Mode */
		DRX_POWER_MODE_11,
			 /*< Device specअगरic , Power Down Mode */
		DRX_POWER_MODE_12,
			 /*< Device specअगरic , Power Down Mode */
		DRX_POWER_MODE_13,
			 /*< Device specअगरic , Power Down Mode */
		DRX_POWER_MODE_14,
			 /*< Device specअगरic , Power Down Mode */
		DRX_POWER_MODE_15,
			 /*< Device specअगरic , Power Down Mode */
		DRX_POWER_MODE_16,
			 /*< Device specअगरic , Power Down Mode */
		DRX_POWER_DOWN = 255
			 /*< Generic         , Power Down Mode */
	पूर्ण;

/*========================================*/

/*
* \क्रमागत क्रमागत drx_module * \मrief Software module identअगरication.
*
* Used by DRX_CTRL_VERSION.
*/
	क्रमागत drx_module अणु
		DRX_MODULE_DEVICE,
		DRX_MODULE_MICROCODE,
		DRX_MODULE_DRIVERCORE,
		DRX_MODULE_DEVICEDRIVER,
		DRX_MODULE_DAP,
		DRX_MODULE_BSP_I2C,
		DRX_MODULE_BSP_TUNER,
		DRX_MODULE_BSP_HOST,
		DRX_MODULE_UNKNOWN
	पूर्ण;

/*
* \क्रमागत काष्ठा drx_version * \मrief Version inक्रमmation of one software module.
*
* Used by DRX_CTRL_VERSION.
*/
	काष्ठा drx_version अणु
		क्रमागत drx_module module_type;
			       /*< Type identअगरier of the module */
		अक्षर *module_name;
			       /*< Name or description of module */
		u16 v_major;  /*< Major version number          */
		u16 v_minor;  /*< Minor version number          */
		u16 v_patch;  /*< Patch version number          */
		अक्षर *v_string; /*< Version as text string        */
	पूर्ण;

/*
* \क्रमागत काष्ठा drx_version_list * \मrief List element of शून्य terminated, linked list क्रम version inक्रमmation.
*
* Used by DRX_CTRL_VERSION.
*/
काष्ठा drx_version_list अणु
	काष्ठा drx_version *version;/*< Version inक्रमmation */
	काष्ठा drx_version_list *next;
			      /*< Next list element   */
पूर्ण;

/*========================================*/

/*
* \मrief Parameters needed to confiugure a UIO.
*
* Used by DRX_CTRL_UIO_CFG.
*/
	काष्ठा drxuio_cfg अणु
		क्रमागत drx_uio uio;
		       /*< UIO identअगरier       */
		क्रमागत drxuio_mode mode;
		       /*< UIO operational mode */
	पूर्ण;

/*========================================*/

/*
* \मrief Parameters needed to पढ़ो from or ग_लिखो to a UIO.
*
* Used by DRX_CTRL_UIO_READ and DRX_CTRL_UIO_WRITE.
*/
	काष्ठा drxuio_data अणु
		क्रमागत drx_uio uio;
		   /*< UIO identअगरier              */
		bool value;
		   /*< UIO value (true=1, false=0) */
	पूर्ण;

/*========================================*/

/*
* \मrief Parameters needed to configure OOB.
*
* Used by DRX_CTRL_SET_OOB.
*/
	काष्ठा drxoob अणु
		s32 frequency;	   /*< Frequency in kHz      */
		क्रमागत drxoob_करोwnstream_standard standard;
						   /*< OOB standard          */
		bool spectrum_inverted;	   /*< If true, then spectrum
							 is inverted          */
	पूर्ण;

/*========================================*/

/*
* \मrief Metrics from OOB.
*
* Used by DRX_CTRL_GET_OOB.
*/
	काष्ठा drxoob_status अणु
		s32 frequency; /*< Frequency in Khz         */
		क्रमागत drx_lock_status lock;	  /*< Lock status              */
		u32 mer;		  /*< MER                      */
		s32 symbol_rate_offset;	  /*< Symbolrate offset in ppm */
	पूर्ण;

/*========================================*/

/*
* \मrief Device dependent configuration data.
*
* Used by DRX_CTRL_SET_CFG and DRX_CTRL_GET_CFG.
* A sort of nested drx_ctrl() functionality क्रम device specअगरic controls.
*/
	काष्ठा drx_cfg अणु
		u32 cfg_type;
			  /*< Function identअगरier */
		व्योम *cfg_data;
			  /*< Function data */
	पूर्ण;

/*========================================*/

/*
* /काष्ठा DRXMpegStartWidth_t
* MStart width [nr MCLK cycles] क्रम serial MPEG output.
*/

	क्रमागत drxmpeg_str_width अणु
		DRX_MPEG_STR_WIDTH_1,
		DRX_MPEG_STR_WIDTH_8
	पूर्ण;

/* CTRL CFG MPEG output */
/*
* \काष्ठा काष्ठा drx_cfg_mpeg_output * \मrief Configuration parameters क्रम MPEG output control.
*
* Used by DRX_CFG_MPEG_OUTPUT, in combination with DRX_CTRL_SET_CFG and
* DRX_CTRL_GET_CFG.
*/

	काष्ठा drx_cfg_mpeg_output अणु
		bool enable_mpeg_output;/*< If true, enable MPEG output      */
		bool insert_rs_byte;	/*< If true, insert RS byte          */
		bool enable_parallel;	/*< If true, parallel out otherwise
								     serial   */
		bool invert_data;	/*< If true, invert DATA संकेतs     */
		bool invert_err;	/*< If true, invert ERR संकेत       */
		bool invert_str;	/*< If true, invert STR संकेतs      */
		bool invert_val;	/*< If true, invert VAL संकेतs      */
		bool invert_clk;	/*< If true, invert CLK संकेतs      */
		bool अटल_clk;	/*< If true, अटल MPEG घड़ीrate
					     will be used, otherwise घड़ीrate
					     will adapt to the bitrate of the
					     TS                               */
		u32 bitrate;		/*< Maximum bitrate in b/s in हाल
					     अटल घड़ीrate is selected     */
		क्रमागत drxmpeg_str_width width_str;
					/*< MPEG start width                 */
	पूर्ण;


/*========================================*/

/*
* \काष्ठा काष्ठा drxi2c_data * \मrief Data क्रम I2C via 2nd or 3rd or etc I2C port.
*
* Used by DRX_CTRL_I2C_READWRITE.
* If port_nr is equal to primairy port_nr BSPI2C will be used.
*
*/
	काष्ठा drxi2c_data अणु
		u16 port_nr;	/*< I2C port number               */
		काष्ठा i2c_device_addr *w_dev_addr;
				/*< Write device address          */
		u16 w_count;	/*< Size of ग_लिखो data in bytes   */
		u8 *wData;	/*< Poपूर्णांकer to ग_लिखो data         */
		काष्ठा i2c_device_addr *r_dev_addr;
				/*< Read device address           */
		u16 r_count;	/*< Size of data to पढ़ो in bytes */
		u8 *r_data;	/*< Poपूर्णांकer to पढ़ो buffer        */
	पूर्ण;

/*========================================*/

/*
* \क्रमागत क्रमागत drx_aud_standard * \मrief Audio standard identअगरier.
*
* Used by DRX_CTRL_SET_AUD.
*/
	क्रमागत drx_aud_standard अणु
		DRX_AUD_STANDARD_BTSC,	   /*< set BTSC standard (USA)       */
		DRX_AUD_STANDARD_A2,	   /*< set A2-Korea FM Stereo        */
		DRX_AUD_STANDARD_EIAJ,	   /*< set to Japanese FM Stereo     */
		DRX_AUD_STANDARD_FM_STEREO,/*< set to FM-Stereo Radio        */
		DRX_AUD_STANDARD_M_MONO,   /*< क्रम 4.5 MHz mono detected     */
		DRX_AUD_STANDARD_D_K_MONO, /*< क्रम 6.5 MHz mono detected     */
		DRX_AUD_STANDARD_BG_FM,	   /*< set BG_FM standard            */
		DRX_AUD_STANDARD_D_K1,	   /*< set D_K1 standard             */
		DRX_AUD_STANDARD_D_K2,	   /*< set D_K2 standard             */
		DRX_AUD_STANDARD_D_K3,	   /*< set D_K3 standard             */
		DRX_AUD_STANDARD_BG_NICAM_FM,
					   /*< set BG_NICAM_FM standard      */
		DRX_AUD_STANDARD_L_NICAM_AM,
					   /*< set L_NICAM_AM standard       */
		DRX_AUD_STANDARD_I_NICAM_FM,
					   /*< set I_NICAM_FM standard       */
		DRX_AUD_STANDARD_D_K_NICAM_FM,
					   /*< set D_K_NICAM_FM standard     */
		DRX_AUD_STANDARD_NOT_READY,/*< used to detect audio standard */
		DRX_AUD_STANDARD_AUTO = DRX_AUTO,
					   /*< Automatic Standard Detection  */
		DRX_AUD_STANDARD_UNKNOWN = DRX_UNKNOWN
					   /*< used as स्वतः and क्रम पढ़ोback */
	पूर्ण;

/* CTRL_AUD_GET_STATUS    - काष्ठा drx_aud_status */
/*
* \क्रमागत क्रमागत drx_aud_nicam_status * \मrief Status of NICAM carrier.
*/
	क्रमागत drx_aud_nicam_status अणु
		DRX_AUD_NICAM_DETECTED = 0,
					  /*< NICAM carrier detected         */
		DRX_AUD_NICAM_NOT_DETECTED,
					  /*< NICAM carrier not detected     */
		DRX_AUD_NICAM_BAD	  /*< NICAM carrier bad quality      */
	पूर्ण;

/*
* \काष्ठा काष्ठा drx_aud_status * \मrief Audio status अक्षरacteristics.
*/
	काष्ठा drx_aud_status अणु
		bool stereo;		  /*< stereo detection               */
		bool carrier_a;	  /*< carrier A detected             */
		bool carrier_b;	  /*< carrier B detected             */
		bool sap;		  /*< sap / bilingual detection      */
		bool rds;		  /*< RDS data array present         */
		क्रमागत drx_aud_nicam_status nicam_status;
					  /*< status of NICAM carrier        */
		s8 fm_ident;		  /*< FM Identअगरication value        */
	पूर्ण;

/* CTRL_AUD_READ_RDS       - DRXRDSdata_t */

/*
* \काष्ठा DRXRDSdata_t
* \मrief Raw RDS data array.
*/
	काष्ठा drx_cfg_aud_rds अणु
		bool valid;		  /*< RDS data validation            */
		u16 data[18];		  /*< data from one RDS data array   */
	पूर्ण;

/* DRX_CFG_AUD_VOLUME      - काष्ठा drx_cfg_aud_volume - set/get */
/*
* \क्रमागत DRXAudAVCDecayTime_t
* \मrief Automatic volume control configuration.
*/
	क्रमागत drx_aud_avc_mode अणु
		DRX_AUD_AVC_OFF,	  /*< Automatic volume control off   */
		DRX_AUD_AVC_DECAYTIME_8S, /*< level volume in  8 seconds     */
		DRX_AUD_AVC_DECAYTIME_4S, /*< level volume in  4 seconds     */
		DRX_AUD_AVC_DECAYTIME_2S, /*< level volume in  2 seconds     */
		DRX_AUD_AVC_DECAYTIME_20MS/*< level volume in 20 millisec    */
	पूर्ण;

/*
* /क्रमागत DRXAudMaxAVCGain_t
* /brief Automatic volume control max gain in audio baseband.
*/
	क्रमागत drx_aud_avc_max_gain अणु
		DRX_AUD_AVC_MAX_GAIN_0DB, /*< maximum AVC gain  0 dB         */
		DRX_AUD_AVC_MAX_GAIN_6DB, /*< maximum AVC gain  6 dB         */
		DRX_AUD_AVC_MAX_GAIN_12DB /*< maximum AVC gain 12 dB         */
	पूर्ण;

/*
* /क्रमागत DRXAudMaxAVCAtten_t
* /brief Automatic volume control max attenuation in audio baseband.
*/
	क्रमागत drx_aud_avc_max_atten अणु
		DRX_AUD_AVC_MAX_ATTEN_12DB,
					  /*< maximum AVC attenuation 12 dB  */
		DRX_AUD_AVC_MAX_ATTEN_18DB,
					  /*< maximum AVC attenuation 18 dB  */
		DRX_AUD_AVC_MAX_ATTEN_24DB/*< maximum AVC attenuation 24 dB  */
	पूर्ण;
/*
* \काष्ठा काष्ठा drx_cfg_aud_volume * \मrief Audio volume configuration.
*/
	काष्ठा drx_cfg_aud_volume अणु
		bool mute;		  /*< mute overrides volume setting  */
		s16 volume;		  /*< volume, range -114 to 12 dB    */
		क्रमागत drx_aud_avc_mode avc_mode;  /*< AVC स्वतः volume control mode   */
		u16 avc_ref_level;	  /*< AVC reference level            */
		क्रमागत drx_aud_avc_max_gain avc_max_gain;
					  /*< AVC max gain selection         */
		क्रमागत drx_aud_avc_max_atten avc_max_atten;
					  /*< AVC max attenuation selection  */
		s16 strength_left;	  /*< quasi-peak, left speaker       */
		s16 strength_right;	  /*< quasi-peak, right speaker      */
	पूर्ण;

/* DRX_CFG_I2S_OUTPUT      - काष्ठा drx_cfg_i2s_output - set/get */
/*
* \क्रमागत क्रमागत drxi2s_mode * \मrief I2S output mode.
*/
	क्रमागत drxi2s_mode अणु
		DRX_I2S_MODE_MASTER,	  /*< I2S is in master mode          */
		DRX_I2S_MODE_SLAVE	  /*< I2S is in slave mode           */
	पूर्ण;

/*
* \क्रमागत क्रमागत drxi2s_word_length * \मrief Width of I2S data.
*/
	क्रमागत drxi2s_word_length अणु
		DRX_I2S_WORDLENGTH_32 = 0,/*< I2S data is 32 bit wide        */
		DRX_I2S_WORDLENGTH_16 = 1 /*< I2S data is 16 bit wide        */
	पूर्ण;

/*
* \क्रमागत क्रमागत drxi2s_क्रमmat * \मrief Data wordstrobe alignment क्रम I2S.
*/
	क्रमागत drxi2s_क्रमmat अणु
		DRX_I2S_FORMAT_WS_WITH_DATA,
				    /*< I2S data and wordstrobe are aligned  */
		DRX_I2S_FORMAT_WS_ADVANCED
				    /*< I2S data one cycle after wordstrobe  */
	पूर्ण;

/*
* \क्रमागत क्रमागत drxi2s_polarity * \मrief Polarity of I2S data.
*/
	क्रमागत drxi2s_polarity अणु
		DRX_I2S_POLARITY_RIGHT,/*< wordstrobe - right high, left low */
		DRX_I2S_POLARITY_LEFT  /*< wordstrobe - right low, left high */
	पूर्ण;

/*
* \काष्ठा काष्ठा drx_cfg_i2s_output * \मrief I2S output configuration.
*/
	काष्ठा drx_cfg_i2s_output अणु
		bool output_enable;	  /*< I2S output enable              */
		u32 frequency;	  /*< range from 8000-48000 Hz       */
		क्रमागत drxi2s_mode mode;	  /*< I2S mode, master or slave      */
		क्रमागत drxi2s_word_length word_length;
					  /*< I2S wordlength, 16 or 32 bits  */
		क्रमागत drxi2s_polarity polarity;/*< I2S wordstrobe polarity        */
		क्रमागत drxi2s_क्रमmat क्रमmat;	  /*< I2S wordstrobe delay to data   */
	पूर्ण;

/* ------------------------------expert पूर्णांकerface-----------------------------*/
/*
* /क्रमागत क्रमागत drx_aud_fm_deemphasis * setting क्रम FM-Deemphasis in audio demodulator.
*
*/
	क्रमागत drx_aud_fm_deemphasis अणु
		DRX_AUD_FM_DEEMPH_50US,
		DRX_AUD_FM_DEEMPH_75US,
		DRX_AUD_FM_DEEMPH_OFF
	पूर्ण;

/*
* /क्रमागत DRXAudDeviation_t
* setting क्रम deviation mode in audio demodulator.
*
*/
	क्रमागत drx_cfg_aud_deviation अणु
		DRX_AUD_DEVIATION_NORMAL,
		DRX_AUD_DEVIATION_HIGH
	पूर्ण;

/*
* /क्रमागत क्रमागत drx_no_carrier_option * setting क्रम carrier, mute/noise.
*
*/
	क्रमागत drx_no_carrier_option अणु
		DRX_NO_CARRIER_MUTE,
		DRX_NO_CARRIER_NOISE
	पूर्ण;

/*
* \क्रमागत DRXAudAutoSound_t
* \मrief Automatic Sound
*/
	क्रमागत drx_cfg_aud_स्वतः_sound अणु
		DRX_AUD_AUTO_SOUND_OFF = 0,
		DRX_AUD_AUTO_SOUND_SELECT_ON_CHANGE_ON,
		DRX_AUD_AUTO_SOUND_SELECT_ON_CHANGE_OFF
	पूर्ण;

/*
* \क्रमागत DRXAudASSThres_t
* \मrief Automatic Sound Select Thresholds
*/
	काष्ठा drx_cfg_aud_ass_thres अणु
		u16 a2;	/* A2 Threshold क्रम ASS configuration */
		u16 btsc;	/* BTSC Threshold क्रम ASS configuration */
		u16 nicam;	/* Nicam Threshold क्रम ASS configuration */
	पूर्ण;

/*
* \काष्ठा काष्ठा drx_aud_carrier * \मrief Carrier detection related parameters
*/
	काष्ठा drx_aud_carrier अणु
		u16 thres;	/* carrier detetcion threshold क्रम primary carrier (A) */
		क्रमागत drx_no_carrier_option opt;	/* Mute or noise at no carrier detection (A) */
		s32 shअगरt;	/* DC level of incoming संकेत (A) */
		s32 dco;	/* frequency adjusपंचांगent (A) */
	पूर्ण;

/*
* \काष्ठा काष्ठा drx_cfg_aud_carriers * \मrief combining carrier A & B to one काष्ठा
*/
	काष्ठा drx_cfg_aud_carriers अणु
		काष्ठा drx_aud_carrier a;
		काष्ठा drx_aud_carrier b;
	पूर्ण;

/*
* /क्रमागत क्रमागत drx_aud_i2s_src * Selection of audio source
*/
	क्रमागत drx_aud_i2s_src अणु
		DRX_AUD_SRC_MONO,
		DRX_AUD_SRC_STEREO_OR_AB,
		DRX_AUD_SRC_STEREO_OR_A,
		DRX_AUD_SRC_STEREO_OR_Bपूर्ण;

/*
* \क्रमागत क्रमागत drx_aud_i2s_matrix * \मrief Used क्रम selecting I2S output.
*/
	क्रमागत drx_aud_i2s_matrix अणु
		DRX_AUD_I2S_MATRIX_A_MONO,
					/*< A sound only, stereo or mono     */
		DRX_AUD_I2S_MATRIX_B_MONO,
					/*< B sound only, stereo or mono     */
		DRX_AUD_I2S_MATRIX_STEREO,
					/*< A+B sound, transparent           */
		DRX_AUD_I2S_MATRIX_MONO	/*< A+B mixed to mono sum, (L+R)/2   */पूर्ण;

/*
* /क्रमागत क्रमागत drx_aud_fm_matrix * setting क्रम FM-Matrix in audio demodulator.
*
*/
	क्रमागत drx_aud_fm_matrix अणु
		DRX_AUD_FM_MATRIX_NO_MATRIX,
		DRX_AUD_FM_MATRIX_GERMAN,
		DRX_AUD_FM_MATRIX_KOREAN,
		DRX_AUD_FM_MATRIX_SOUND_A,
		DRX_AUD_FM_MATRIX_SOUND_Bपूर्ण;

/*
* \काष्ठा DRXAudMatrices_t
* \मrief Mixer settings
*/
काष्ठा drx_cfg_aud_mixer अणु
	क्रमागत drx_aud_i2s_src source_i2s;
	क्रमागत drx_aud_i2s_matrix matrix_i2s;
	क्रमागत drx_aud_fm_matrix matrix_fm;
पूर्ण;

/*
* \क्रमागत DRXI2SVidSync_t
* \मrief Audio/video synchronization, पूर्णांकeracts with I2S mode.
* AUTO_1 and AUTO_2 are क्रम स्वतःmatic video standard detection with preference
* क्रम NTSC or Monochrome, because the frequencies are too बंद (59.94 & 60 Hz)
*/
	क्रमागत drx_cfg_aud_av_sync अणु
		DRX_AUD_AVSYNC_OFF,/*< audio/video synchronization is off   */
		DRX_AUD_AVSYNC_NTSC,
				   /*< it is an NTSC प्रणाली                 */
		DRX_AUD_AVSYNC_MONOCHROME,
				   /*< it is a MONOCHROME प्रणाली            */
		DRX_AUD_AVSYNC_PAL_SECAM
				   /*< it is a PAL/SECAM प्रणाली             */पूर्ण;

/*
* \काष्ठा काष्ठा drx_cfg_aud_prescale * \मrief Prescalers
*/
काष्ठा drx_cfg_aud_prescale अणु
	u16 fm_deviation;
	s16 nicam_gain;
पूर्ण;

/*
* \काष्ठा काष्ठा drx_aud_beep * \मrief Beep
*/
काष्ठा drx_aud_beep अणु
	s16 volume;	/* dB */
	u16 frequency;	/* Hz */
	bool mute;
पूर्ण;

/*
* \क्रमागत क्रमागत drx_aud_btsc_detect * \मrief BTSC detetcion mode
*/
	क्रमागत drx_aud_btsc_detect अणु
		DRX_BTSC_STEREO,
		DRX_BTSC_MONO_AND_SAPपूर्ण;

/*
* \काष्ठा काष्ठा drx_aud_data * \मrief Audio data काष्ठाure
*/
काष्ठा drx_aud_data अणु
	/* audio storage */
	bool audio_is_active;
	क्रमागत drx_aud_standard audio_standard;
	काष्ठा drx_cfg_i2s_output i2sdata;
	काष्ठा drx_cfg_aud_volume volume;
	क्रमागत drx_cfg_aud_स्वतः_sound स्वतः_sound;
	काष्ठा drx_cfg_aud_ass_thres ass_thresholds;
	काष्ठा drx_cfg_aud_carriers carriers;
	काष्ठा drx_cfg_aud_mixer mixer;
	क्रमागत drx_cfg_aud_deviation deviation;
	क्रमागत drx_cfg_aud_av_sync av_sync;
	काष्ठा drx_cfg_aud_prescale prescale;
	क्रमागत drx_aud_fm_deemphasis deemph;
	क्रमागत drx_aud_btsc_detect btsc_detect;
	/* rds */
	u16 rds_data_counter;
	bool rds_data_present;
पूर्ण;

/*
* \क्रमागत क्रमागत drx_qam_lock_range * \मrief QAM lock range mode
*/
	क्रमागत drx_qam_lock_range अणु
		DRX_QAM_LOCKRANGE_NORMAL,
		DRX_QAM_LOCKRANGE_EXTENDEDपूर्ण;

/*============================================================================*/
/*============================================================================*/
/*== Data access काष्ठाures ==================================================*/
/*============================================================================*/
/*============================================================================*/

/* Address on device */
	प्रकार u32 dr_xaddr_t, *pdr_xaddr_t;

/* Protocol specअगरic flags */
	प्रकार u32 dr_xflags_t, *pdr_xflags_t;

/* Write block of data to device */
	प्रकार पूर्णांक(*drx_ग_लिखो_block_func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device        */
						   u32 addr,	/* address of रेजिस्टर/memory   */
						   u16 datasize,	/* size of data in bytes        */
						   u8 *data,	/* data to send                 */
						   u32 flags);

/* Read block of data from device */
	प्रकार पूर्णांक(*drx_पढ़ो_block_func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device        */
						  u32 addr,	/* address of रेजिस्टर/memory   */
						  u16 datasize,	/* size of data in bytes        */
						  u8 *data,	/* receive buffer               */
						  u32 flags);

/* Write 8-bits value to device */
	प्रकार पूर्णांक(*drx_ग_लिखो_reg8func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device        */
						  u32 addr,	/* address of रेजिस्टर/memory   */
						  u8 data,	/* data to send                 */
						  u32 flags);

/* Read 8-bits value to device */
	प्रकार पूर्णांक(*drx_पढ़ो_reg8func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device        */
						 u32 addr,	/* address of रेजिस्टर/memory   */
						 u8 *data,	/* receive buffer               */
						 u32 flags);

/* Read modअगरy ग_लिखो 8-bits value to device */
	प्रकार पूर्णांक(*drx_पढ़ो_modअगरy_ग_लिखो_reg8func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device       */
							    u32 waddr,	/* ग_लिखो address of रेजिस्टर   */
							    u32 raddr,	/* पढ़ो  address of रेजिस्टर   */
							    u8 wdata,	/* data to ग_लिखो               */
							    u8 *rdata);	/* data to पढ़ो                */

/* Write 16-bits value to device */
	प्रकार पूर्णांक(*drx_ग_लिखो_reg16func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device        */
						   u32 addr,	/* address of रेजिस्टर/memory   */
						   u16 data,	/* data to send                 */
						   u32 flags);

/* Read 16-bits value to device */
	प्रकार पूर्णांक(*drx_पढ़ो_reg16func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device        */
						  u32 addr,	/* address of रेजिस्टर/memory   */
						  u16 *data,	/* receive buffer               */
						  u32 flags);

/* Read modअगरy ग_लिखो 16-bits value to device */
	प्रकार पूर्णांक(*drx_पढ़ो_modअगरy_ग_लिखो_reg16func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device       */
							     u32 waddr,	/* ग_लिखो address of रेजिस्टर   */
							     u32 raddr,	/* पढ़ो  address of रेजिस्टर   */
							     u16 wdata,	/* data to ग_लिखो               */
							     u16 *rdata);	/* data to पढ़ो                */

/* Write 32-bits value to device */
	प्रकार पूर्णांक(*drx_ग_लिखो_reg32func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device        */
						   u32 addr,	/* address of रेजिस्टर/memory   */
						   u32 data,	/* data to send                 */
						   u32 flags);

/* Read 32-bits value to device */
	प्रकार पूर्णांक(*drx_पढ़ो_reg32func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device        */
						  u32 addr,	/* address of रेजिस्टर/memory   */
						  u32 *data,	/* receive buffer               */
						  u32 flags);

/* Read modअगरy ग_लिखो 32-bits value to device */
	प्रकार पूर्णांक(*drx_पढ़ो_modअगरy_ग_लिखो_reg32func_t) (काष्ठा i2c_device_addr *dev_addr,	/* address of I2C device       */
							     u32 waddr,	/* ग_लिखो address of रेजिस्टर   */
							     u32 raddr,	/* पढ़ो  address of रेजिस्टर   */
							     u32 wdata,	/* data to ग_लिखो               */
							     u32 *rdata);	/* data to पढ़ो                */

/*
* \काष्ठा काष्ठा drx_access_func * \मrief Interface to an access protocol.
*/
काष्ठा drx_access_func अणु
	drx_ग_लिखो_block_func_t ग_लिखो_block_func;
	drx_पढ़ो_block_func_t पढ़ो_block_func;
	drx_ग_लिखो_reg8func_t ग_लिखो_reg8func;
	drx_पढ़ो_reg8func_t पढ़ो_reg8func;
	drx_पढ़ो_modअगरy_ग_लिखो_reg8func_t पढ़ो_modअगरy_ग_लिखो_reg8func;
	drx_ग_लिखो_reg16func_t ग_लिखो_reg16func;
	drx_पढ़ो_reg16func_t पढ़ो_reg16func;
	drx_पढ़ो_modअगरy_ग_लिखो_reg16func_t पढ़ो_modअगरy_ग_लिखो_reg16func;
	drx_ग_लिखो_reg32func_t ग_लिखो_reg32func;
	drx_पढ़ो_reg32func_t पढ़ो_reg32func;
	drx_पढ़ो_modअगरy_ग_लिखो_reg32func_t पढ़ो_modअगरy_ग_लिखो_reg32func;
पूर्ण;

/* Register address and data क्रम रेजिस्टर dump function */
काष्ठा drx_reg_dump अणु
	u32 address;
	u32 data;
पूर्ण;

/*============================================================================*/
/*============================================================================*/
/*== Demod instance data काष्ठाures ==========================================*/
/*============================================================================*/
/*============================================================================*/

/*
* \काष्ठा काष्ठा drx_common_attr * \मrief Set of common attributes, shared by all DRX devices.
*/
	काष्ठा drx_common_attr अणु
		/* Microcode (firmware) attributes */
		अक्षर *microcode_file;   /*<  microcode filename           */
		bool verअगरy_microcode;
				   /*< Use microcode verअगरy or not.          */
		काष्ठा drx_mc_version_rec mcversion;
				   /*< Version record of microcode from file */

		/* Clocks and tuner attributes */
		s32 पूर्णांकermediate_freq;
				     /*< IF,अगर tuner instance not used. (kHz)*/
		s32 sys_घड़ी_freq;
				     /*< Systemघड़ी frequency.  (kHz)       */
		s32 osc_घड़ी_freq;
				     /*< Oscillator घड़ी frequency.  (kHz)  */
		s16 osc_घड़ी_deviation;
				     /*< Oscillator घड़ी deviation.  (ppm)  */
		bool mirror_freq_spect;
				     /*< Mirror IF frequency spectrum or not.*/

		/* Initial MPEG output attributes */
		काष्ठा drx_cfg_mpeg_output mpeg_cfg;
				     /*< MPEG configuration                  */

		bool is_खोलोed;     /*< अगर true instance is alपढ़ोy खोलोed. */

		/* Channel scan */
		काष्ठा drx_scan_param *scan_param;
				      /*< scan parameters                    */
		u16 scan_freq_plan_index;
				      /*< next index in freq plan            */
		s32 scan_next_frequency;
				      /*< next freq to scan                  */
		bool scan_पढ़ोy;     /*< scan पढ़ोy flag                    */
		u32 scan_max_channels;/*< number of channels in freqplan     */
		u32 scan_channels_scanned;
					/*< number of channels scanned       */
		/* Channel scan - inner loop: demod related */
		drx_scan_func_t scan_function;
				      /*< function to check channel          */
		/* Channel scan - inner loop: SYSObj related */
		व्योम *scan_context;    /*< Context Poपूर्णांकer of SYSObj          */
		/* Channel scan - parameters क्रम शेष DTV scan function in core driver  */
		u16 scan_demod_lock_समयout;
					 /*< millisecs to रुको क्रम lock      */
		क्रमागत drx_lock_status scan_desired_lock;
				      /*< lock requirement क्रम channel found */
		/* scan_active can be used by SetChannel to decide how to program the tuner,
		   fast or slow (but stable). Usually fast during scan. */
		bool scan_active;    /*< true when scan routines are active */

		/* Power management */
		क्रमागत drx_घातer_mode current_घातer_mode;
				      /*< current घातer management mode      */

		/* Tuner */
		u8 tuner_port_nr;     /*< nr of I2C port to which tuner is    */
		s32 tuner_min_freq_rf;
				      /*< minimum RF input frequency, in kHz */
		s32 tuner_max_freq_rf;
				      /*< maximum RF input frequency, in kHz */
		bool tuner_rf_agc_pol; /*< अगर true invert RF AGC polarity     */
		bool tuner_अगर_agc_pol; /*< अगर true invert IF AGC polarity     */
		bool tuner_slow_mode; /*< अगर true invert IF AGC polarity     */

		काष्ठा drx_channel current_channel;
				      /*< current channel parameters         */
		क्रमागत drx_standard current_standard;
				      /*< current standard selection         */
		क्रमागत drx_standard prev_standard;
				      /*< previous standard selection        */
		क्रमागत drx_standard di_cache_standard;
				      /*< standard in DI cache अगर available  */
		bool use_bootloader; /*< use bootloader in खोलो             */
		u32 capabilities;   /*< capabilities flags                 */
		u32 product_id;      /*< product ID inc. metal fix number   */पूर्ण;

/*
* Generic functions क्रम DRX devices.
*/

काष्ठा drx_demod_instance;

/*
* \काष्ठा काष्ठा drx_demod_instance * \मrief Top काष्ठाure of demodulator instance.
*/
काष्ठा drx_demod_instance अणु
				/*< data access protocol functions       */
	काष्ठा i2c_device_addr *my_i2c_dev_addr;
				/*< i2c address and device identअगरier    */
	काष्ठा drx_common_attr *my_common_attr;
				/*< common DRX attributes                */
	व्योम *my_ext_attr;    /*< device specअगरic attributes           */
	/* generic demodulator data */

	काष्ठा i2c_adapter	*i2c;
	स्थिर काष्ठा firmware	*firmware;
पूर्ण;

/*-------------------------------------------------------------------------
MACROS
Conversion from क्रमागत values to human पढ़ोable क्रमm.
-------------------------------------------------------------------------*/

/* standard */

#घोषणा DRX_STR_STANDARD(x) ( \
	(x == DRX_STANDARD_DVBT)  ? "DVB-T"            : \
	(x == DRX_STANDARD_8VSB)  ? "8VSB"             : \
	(x == DRX_STANDARD_NTSC)  ? "NTSC"             : \
	(x == DRX_STANDARD_PAL_SECAM_BG)  ? "PAL/SECAM B/G"    : \
	(x == DRX_STANDARD_PAL_SECAM_DK)  ? "PAL/SECAM D/K"    : \
	(x == DRX_STANDARD_PAL_SECAM_I)  ? "PAL/SECAM I"      : \
	(x == DRX_STANDARD_PAL_SECAM_L)  ? "PAL/SECAM L"      : \
	(x == DRX_STANDARD_PAL_SECAM_LP)  ? "PAL/SECAM LP"     : \
	(x == DRX_STANDARD_ITU_A)  ? "ITU-A"            : \
	(x == DRX_STANDARD_ITU_B)  ? "ITU-B"            : \
	(x == DRX_STANDARD_ITU_C)  ? "ITU-C"            : \
	(x == DRX_STANDARD_ITU_D)  ? "ITU-D"            : \
	(x == DRX_STANDARD_FM)  ? "FM"               : \
	(x == DRX_STANDARD_DTMB)  ? "DTMB"             : \
	(x == DRX_STANDARD_AUTO)  ? "Auto"             : \
	(x == DRX_STANDARD_UNKNOWN)  ? "Unknown"          : \
	"(Invalid)")

/* channel */

#घोषणा DRX_STR_BANDWIDTH(x) ( \
	(x == DRX_BANDWIDTH_8MHZ)  ?  "8 MHz"            : \
	(x == DRX_BANDWIDTH_7MHZ)  ?  "7 MHz"            : \
	(x == DRX_BANDWIDTH_6MHZ)  ?  "6 MHz"            : \
	(x == DRX_BANDWIDTH_AUTO)  ?  "Auto"             : \
	(x == DRX_BANDWIDTH_UNKNOWN)  ?  "Unknown"          : \
	"(Invalid)")
#घोषणा DRX_STR_FFTMODE(x) ( \
	(x == DRX_FFTMODE_2K)  ?  "2k"               : \
	(x == DRX_FFTMODE_4K)  ?  "4k"               : \
	(x == DRX_FFTMODE_8K)  ?  "8k"               : \
	(x == DRX_FFTMODE_AUTO)  ?  "Auto"             : \
	(x == DRX_FFTMODE_UNKNOWN)  ?  "Unknown"          : \
	"(Invalid)")
#घोषणा DRX_STR_GUARD(x) ( \
	(x == DRX_GUARD_1DIV32)  ?  "1/32nd"           : \
	(x == DRX_GUARD_1DIV16)  ?  "1/16th"           : \
	(x == DRX_GUARD_1DIV8)  ?  "1/8th"            : \
	(x == DRX_GUARD_1DIV4)  ?  "1/4th"            : \
	(x == DRX_GUARD_AUTO)  ?  "Auto"             : \
	(x == DRX_GUARD_UNKNOWN)  ?  "Unknown"          : \
	"(Invalid)")
#घोषणा DRX_STR_CONSTELLATION(x) ( \
	(x == DRX_CONSTELLATION_BPSK)  ?  "BPSK"            : \
	(x == DRX_CONSTELLATION_QPSK)  ?  "QPSK"            : \
	(x == DRX_CONSTELLATION_PSK8)  ?  "PSK8"            : \
	(x == DRX_CONSTELLATION_QAM16)  ?  "QAM16"           : \
	(x == DRX_CONSTELLATION_QAM32)  ?  "QAM32"           : \
	(x == DRX_CONSTELLATION_QAM64)  ?  "QAM64"           : \
	(x == DRX_CONSTELLATION_QAM128)  ?  "QAM128"          : \
	(x == DRX_CONSTELLATION_QAM256)  ?  "QAM256"          : \
	(x == DRX_CONSTELLATION_QAM512)  ?  "QAM512"          : \
	(x == DRX_CONSTELLATION_QAM1024)  ?  "QAM1024"         : \
	(x == DRX_CONSTELLATION_QPSK_NR)  ?  "QPSK_NR"            : \
	(x == DRX_CONSTELLATION_AUTO)  ?  "Auto"            : \
	(x == DRX_CONSTELLATION_UNKNOWN)  ?  "Unknown"         : \
	"(Invalid)")
#घोषणा DRX_STR_CODERATE(x) ( \
	(x == DRX_CODERATE_1DIV2)  ?  "1/2nd"           : \
	(x == DRX_CODERATE_2DIV3)  ?  "2/3rd"           : \
	(x == DRX_CODERATE_3DIV4)  ?  "3/4th"           : \
	(x == DRX_CODERATE_5DIV6)  ?  "5/6th"           : \
	(x == DRX_CODERATE_7DIV8)  ?  "7/8th"           : \
	(x == DRX_CODERATE_AUTO)  ?  "Auto"            : \
	(x == DRX_CODERATE_UNKNOWN)  ?  "Unknown"         : \
	"(Invalid)")
#घोषणा DRX_STR_HIERARCHY(x) ( \
	(x == DRX_HIERARCHY_NONE)  ?  "None"            : \
	(x == DRX_HIERARCHY_ALPHA1)  ?  "Alpha=1"         : \
	(x == DRX_HIERARCHY_ALPHA2)  ?  "Alpha=2"         : \
	(x == DRX_HIERARCHY_ALPHA4)  ?  "Alpha=4"         : \
	(x == DRX_HIERARCHY_AUTO)  ?  "Auto"            : \
	(x == DRX_HIERARCHY_UNKNOWN)  ?  "Unknown"         : \
	"(Invalid)")
#घोषणा DRX_STR_PRIORITY(x) ( \
	(x == DRX_PRIORITY_LOW)  ?  "Low"             : \
	(x == DRX_PRIORITY_HIGH)  ?  "High"            : \
	(x == DRX_PRIORITY_UNKNOWN)  ?  "Unknown"         : \
	"(Invalid)")
#घोषणा DRX_STR_MIRROR(x) ( \
	(x == DRX_MIRROR_NO)  ?  "Normal"          : \
	(x == DRX_MIRROR_YES)  ?  "Mirrored"        : \
	(x == DRX_MIRROR_AUTO)  ?  "Auto"            : \
	(x == DRX_MIRROR_UNKNOWN)  ?  "Unknown"         : \
	"(Invalid)")
#घोषणा DRX_STR_CLASSIFICATION(x) ( \
	(x == DRX_CLASSIFICATION_GAUSS)  ?  "Gaussion"        : \
	(x == DRX_CLASSIFICATION_HVY_GAUSS)  ?  "Heavy Gaussion"  : \
	(x == DRX_CLASSIFICATION_COCHANNEL)  ?  "Co-channel"      : \
	(x == DRX_CLASSIFICATION_STATIC)  ?  "Static echo"     : \
	(x == DRX_CLASSIFICATION_MOVING)  ?  "Moving echo"     : \
	(x == DRX_CLASSIFICATION_ZERODB)  ?  "Zero dB echo"    : \
	(x == DRX_CLASSIFICATION_UNKNOWN)  ?  "Unknown"         : \
	(x == DRX_CLASSIFICATION_AUTO)  ?  "Auto"            : \
	"(Invalid)")

#घोषणा DRX_STR_INTERLEAVEMODE(x) ( \
	(x == DRX_INTERLEAVEMODE_I128_J1) ? "I128_J1"         : \
	(x == DRX_INTERLEAVEMODE_I128_J1_V2) ? "I128_J1_V2"      : \
	(x == DRX_INTERLEAVEMODE_I128_J2) ? "I128_J2"         : \
	(x == DRX_INTERLEAVEMODE_I64_J2) ? "I64_J2"          : \
	(x == DRX_INTERLEAVEMODE_I128_J3) ? "I128_J3"         : \
	(x == DRX_INTERLEAVEMODE_I32_J4) ? "I32_J4"          : \
	(x == DRX_INTERLEAVEMODE_I128_J4) ? "I128_J4"         : \
	(x == DRX_INTERLEAVEMODE_I16_J8) ? "I16_J8"          : \
	(x == DRX_INTERLEAVEMODE_I128_J5) ? "I128_J5"         : \
	(x == DRX_INTERLEAVEMODE_I8_J16) ? "I8_J16"          : \
	(x == DRX_INTERLEAVEMODE_I128_J6) ? "I128_J6"         : \
	(x == DRX_INTERLEAVEMODE_RESERVED_11) ? "Reserved 11"     : \
	(x == DRX_INTERLEAVEMODE_I128_J7) ? "I128_J7"         : \
	(x == DRX_INTERLEAVEMODE_RESERVED_13) ? "Reserved 13"     : \
	(x == DRX_INTERLEAVEMODE_I128_J8) ? "I128_J8"         : \
	(x == DRX_INTERLEAVEMODE_RESERVED_15) ? "Reserved 15"     : \
	(x == DRX_INTERLEAVEMODE_I12_J17) ? "I12_J17"         : \
	(x == DRX_INTERLEAVEMODE_I5_J4) ? "I5_J4"           : \
	(x == DRX_INTERLEAVEMODE_B52_M240) ? "B52_M240"        : \
	(x == DRX_INTERLEAVEMODE_B52_M720) ? "B52_M720"        : \
	(x == DRX_INTERLEAVEMODE_B52_M48) ? "B52_M48"         : \
	(x == DRX_INTERLEAVEMODE_B52_M0) ? "B52_M0"          : \
	(x == DRX_INTERLEAVEMODE_UNKNOWN) ? "Unknown"         : \
	(x == DRX_INTERLEAVEMODE_AUTO) ? "Auto"            : \
	"(Invalid)")

#घोषणा DRX_STR_LDPC(x) ( \
	(x == DRX_LDPC_0_4) ? "0.4"             : \
	(x == DRX_LDPC_0_6) ? "0.6"             : \
	(x == DRX_LDPC_0_8) ? "0.8"             : \
	(x == DRX_LDPC_AUTO) ? "Auto"            : \
	(x == DRX_LDPC_UNKNOWN) ? "Unknown"         : \
	"(Invalid)")

#घोषणा DRX_STR_CARRIER(x) ( \
	(x == DRX_CARRIER_MULTI) ? "Multi"           : \
	(x == DRX_CARRIER_SINGLE) ? "Single"          : \
	(x == DRX_CARRIER_AUTO) ? "Auto"            : \
	(x == DRX_CARRIER_UNKNOWN) ? "Unknown"         : \
	"(Invalid)")

#घोषणा DRX_STR_FRAMEMODE(x) ( \
	(x == DRX_FRAMEMODE_420)  ? "420"                : \
	(x == DRX_FRAMEMODE_595)  ? "595"                : \
	(x == DRX_FRAMEMODE_945)  ? "945"                : \
	(x == DRX_FRAMEMODE_420_FIXED_PN)  ? "420 with fixed PN"  : \
	(x == DRX_FRAMEMODE_945_FIXED_PN)  ? "945 with fixed PN"  : \
	(x == DRX_FRAMEMODE_AUTO)  ? "Auto"               : \
	(x == DRX_FRAMEMODE_UNKNOWN)  ? "Unknown"            : \
	"(Invalid)")

#घोषणा DRX_STR_PILOT(x) ( \
	(x == DRX_PILOT_ON) ?   "On"              : \
	(x == DRX_PILOT_OFF) ?   "Off"             : \
	(x == DRX_PILOT_AUTO) ?   "Auto"            : \
	(x == DRX_PILOT_UNKNOWN) ?   "Unknown"         : \
	"(Invalid)")
/* TPS */

#घोषणा DRX_STR_TPS_FRAME(x)  ( \
	(x == DRX_TPS_FRAME1)  ?  "Frame1"          : \
	(x == DRX_TPS_FRAME2)  ?  "Frame2"          : \
	(x == DRX_TPS_FRAME3)  ?  "Frame3"          : \
	(x == DRX_TPS_FRAME4)  ?  "Frame4"          : \
	(x == DRX_TPS_FRAME_UNKNOWN)  ?  "Unknown"         : \
	"(Invalid)")

/* lock status */

#घोषणा DRX_STR_LOCKSTATUS(x) ( \
	(x == DRX_NEVER_LOCK)  ?  "Never"           : \
	(x == DRX_NOT_LOCKED)  ?  "No"              : \
	(x == DRX_LOCKED)  ?  "Locked"          : \
	(x == DRX_LOCK_STATE_1)  ?  "Lock state 1"    : \
	(x == DRX_LOCK_STATE_2)  ?  "Lock state 2"    : \
	(x == DRX_LOCK_STATE_3)  ?  "Lock state 3"    : \
	(x == DRX_LOCK_STATE_4)  ?  "Lock state 4"    : \
	(x == DRX_LOCK_STATE_5)  ?  "Lock state 5"    : \
	(x == DRX_LOCK_STATE_6)  ?  "Lock state 6"    : \
	(x == DRX_LOCK_STATE_7)  ?  "Lock state 7"    : \
	(x == DRX_LOCK_STATE_8)  ?  "Lock state 8"    : \
	(x == DRX_LOCK_STATE_9)  ?  "Lock state 9"    : \
	"(Invalid)")

/* version inक्रमmation , modules */
#घोषणा DRX_STR_MODULE(x) ( \
	(x == DRX_MODULE_DEVICE)  ?  "Device"                : \
	(x == DRX_MODULE_MICROCODE)  ?  "Microcode"             : \
	(x == DRX_MODULE_DRIVERCORE)  ?  "CoreDriver"            : \
	(x == DRX_MODULE_DEVICEDRIVER)  ?  "DeviceDriver"          : \
	(x == DRX_MODULE_BSP_I2C)  ?  "BSP I2C"               : \
	(x == DRX_MODULE_BSP_TUNER)  ?  "BSP Tuner"             : \
	(x == DRX_MODULE_BSP_HOST)  ?  "BSP Host"              : \
	(x == DRX_MODULE_DAP)  ?  "Data Access Protocol"  : \
	(x == DRX_MODULE_UNKNOWN)  ?  "Unknown"               : \
	"(Invalid)")

#घोषणा DRX_STR_POWER_MODE(x) ( \
	(x == DRX_POWER_UP)  ?  "DRX_POWER_UP    "  : \
	(x == DRX_POWER_MODE_1)  ?  "DRX_POWER_MODE_1"  : \
	(x == DRX_POWER_MODE_2)  ?  "DRX_POWER_MODE_2"  : \
	(x == DRX_POWER_MODE_3)  ?  "DRX_POWER_MODE_3"  : \
	(x == DRX_POWER_MODE_4)  ?  "DRX_POWER_MODE_4"  : \
	(x == DRX_POWER_MODE_5)  ?  "DRX_POWER_MODE_5"  : \
	(x == DRX_POWER_MODE_6)  ?  "DRX_POWER_MODE_6"  : \
	(x == DRX_POWER_MODE_7)  ?  "DRX_POWER_MODE_7"  : \
	(x == DRX_POWER_MODE_8)  ?  "DRX_POWER_MODE_8"  : \
	(x == DRX_POWER_MODE_9)  ?  "DRX_POWER_MODE_9"  : \
	(x == DRX_POWER_MODE_10)  ?  "DRX_POWER_MODE_10" : \
	(x == DRX_POWER_MODE_11)  ?  "DRX_POWER_MODE_11" : \
	(x == DRX_POWER_MODE_12)  ?  "DRX_POWER_MODE_12" : \
	(x == DRX_POWER_MODE_13)  ?  "DRX_POWER_MODE_13" : \
	(x == DRX_POWER_MODE_14)  ?  "DRX_POWER_MODE_14" : \
	(x == DRX_POWER_MODE_15)  ?  "DRX_POWER_MODE_15" : \
	(x == DRX_POWER_MODE_16)  ?  "DRX_POWER_MODE_16" : \
	(x == DRX_POWER_DOWN)  ?  "DRX_POWER_DOWN  " : \
	"(Invalid)")

#घोषणा DRX_STR_OOB_STANDARD(x) ( \
	(x == DRX_OOB_MODE_A)  ?  "ANSI 55-1  " : \
	(x == DRX_OOB_MODE_B_GRADE_A)  ?  "ANSI 55-2 A" : \
	(x == DRX_OOB_MODE_B_GRADE_B)  ?  "ANSI 55-2 B" : \
	"(Invalid)")

#घोषणा DRX_STR_AUD_STANDARD(x) ( \
	(x == DRX_AUD_STANDARD_BTSC)  ? "BTSC"                     : \
	(x == DRX_AUD_STANDARD_A2)  ? "A2"                       : \
	(x == DRX_AUD_STANDARD_EIAJ)  ? "EIAJ"                     : \
	(x == DRX_AUD_STANDARD_FM_STEREO)  ? "FM Stereo"                : \
	(x == DRX_AUD_STANDARD_AUTO)  ? "Auto"                     : \
	(x == DRX_AUD_STANDARD_M_MONO)  ? "M-Standard Mono"          : \
	(x == DRX_AUD_STANDARD_D_K_MONO)  ? "D/K Mono FM"              : \
	(x == DRX_AUD_STANDARD_BG_FM)  ? "B/G-Dual Carrier FM (A2)" : \
	(x == DRX_AUD_STANDARD_D_K1)  ? "D/K1-Dual Carrier FM"     : \
	(x == DRX_AUD_STANDARD_D_K2)  ? "D/K2-Dual Carrier FM"     : \
	(x == DRX_AUD_STANDARD_D_K3)  ? "D/K3-Dual Carrier FM"     : \
	(x == DRX_AUD_STANDARD_BG_NICAM_FM)  ? "B/G-NICAM-FM"             : \
	(x == DRX_AUD_STANDARD_L_NICAM_AM)  ? "L-NICAM-AM"               : \
	(x == DRX_AUD_STANDARD_I_NICAM_FM)  ? "I-NICAM-FM"               : \
	(x == DRX_AUD_STANDARD_D_K_NICAM_FM)  ? "D/K-NICAM-FM"             : \
	(x == DRX_AUD_STANDARD_UNKNOWN)  ? "Unknown"                  : \
	"(Invalid)")
#घोषणा DRX_STR_AUD_STEREO(x) ( \
	(x == true)  ? "Stereo"           : \
	(x == false)  ? "Mono"             : \
	"(Invalid)")

#घोषणा DRX_STR_AUD_SAP(x) ( \
	(x == true)  ? "Present"          : \
	(x == false)  ? "Not present"      : \
	"(Invalid)")

#घोषणा DRX_STR_AUD_CARRIER(x) ( \
	(x == true)  ? "Present"          : \
	(x == false)  ? "Not present"      : \
	"(Invalid)")

#घोषणा DRX_STR_AUD_RDS(x) ( \
	(x == true)  ? "Available"        : \
	(x == false)  ? "Not Available"    : \
	"(Invalid)")

#घोषणा DRX_STR_AUD_NICAM_STATUS(x) ( \
	(x == DRX_AUD_NICAM_DETECTED)  ? "Detected"         : \
	(x == DRX_AUD_NICAM_NOT_DETECTED)  ? "Not detected"     : \
	(x == DRX_AUD_NICAM_BAD)  ? "Bad"              : \
	"(Invalid)")

#घोषणा DRX_STR_RDS_VALID(x) ( \
	(x == true)  ? "Valid"            : \
	(x == false)  ? "Not Valid"        : \
	"(Invalid)")

/*-------------------------------------------------------------------------
Access macros
-------------------------------------------------------------------------*/

/*
* \मrief Create a compilable reference to the microcode attribute
* \param d poपूर्णांकer to demod instance
*
* Used as मुख्य reference to an attribute field.
* Used by both macro implementation and function implementation.
* These macros are defined to aव्योम duplication of code in macro and function
* definitions that handle access of demod common or extended attributes.
*
*/

#घोषणा DRX_ATTR_MCRECORD(d)        ((d)->my_common_attr->mcversion)
#घोषणा DRX_ATTR_MIRRORFREQSPECT(d) ((d)->my_common_attr->mirror_freq_spect)
#घोषणा DRX_ATTR_CURRENTPOWERMODE(d)((d)->my_common_attr->current_घातer_mode)
#घोषणा DRX_ATTR_ISOPENED(d)        ((d)->my_common_attr->is_खोलोed)
#घोषणा DRX_ATTR_USEBOOTLOADER(d)   ((d)->my_common_attr->use_bootloader)
#घोषणा DRX_ATTR_CURRENTSTANDARD(d) ((d)->my_common_attr->current_standard)
#घोषणा DRX_ATTR_PREVSTANDARD(d)    ((d)->my_common_attr->prev_standard)
#घोषणा DRX_ATTR_CACHESTANDARD(d)   ((d)->my_common_attr->di_cache_standard)
#घोषणा DRX_ATTR_CURRENTCHANNEL(d)  ((d)->my_common_attr->current_channel)
#घोषणा DRX_ATTR_MICROCODE(d)       ((d)->my_common_attr->microcode)
#घोषणा DRX_ATTR_VERIFYMICROCODE(d) ((d)->my_common_attr->verअगरy_microcode)
#घोषणा DRX_ATTR_CAPABILITIES(d)    ((d)->my_common_attr->capabilities)
#घोषणा DRX_ATTR_PRODUCTID(d)       ((d)->my_common_attr->product_id)
#घोषणा DRX_ATTR_INTERMEDIATEFREQ(d) ((d)->my_common_attr->पूर्णांकermediate_freq)
#घोषणा DRX_ATTR_SYSCLOCKFREQ(d)     ((d)->my_common_attr->sys_घड़ी_freq)
#घोषणा DRX_ATTR_TUNERRFAGCPOL(d)   ((d)->my_common_attr->tuner_rf_agc_pol)
#घोषणा DRX_ATTR_TUNERIFAGCPOL(d)    ((d)->my_common_attr->tuner_अगर_agc_pol)
#घोषणा DRX_ATTR_TUNERSLOWMODE(d)    ((d)->my_common_attr->tuner_slow_mode)
#घोषणा DRX_ATTR_TUNERSPORTNR(d)     ((d)->my_common_attr->tuner_port_nr)
#घोषणा DRX_ATTR_I2CADDR(d)         ((d)->my_i2c_dev_addr->i2c_addr)
#घोषणा DRX_ATTR_I2CDEVID(d)        ((d)->my_i2c_dev_addr->i2c_dev_id)
#घोषणा DRX_ISMCVERTYPE(x) ((x) == AUX_VER_RECORD)

/*************************/

/* Macros with device-specअगरic handling are converted to CFG functions */

#घोषणा DRX_ACCESSMACRO_SET(demod, value, cfg_name, data_type)             \
	करो अणु                                                               \
		काष्ठा drx_cfg config;                                     \
		data_type cfg_data;                                        \
		config.cfg_type = cfg_name;                                \
		config.cfg_data = &cfg_data;                               \
		cfg_data = value;                                          \
		drx_ctrl(demod, DRX_CTRL_SET_CFG, &config);                \
	पूर्ण जबतक (0)

#घोषणा DRX_ACCESSMACRO_GET(demod, value, cfg_name, data_type, error_value) \
	करो अणु                                                                \
		पूर्णांक cfg_status;                                             \
		काष्ठा drx_cfg config;                                      \
		data_type    cfg_data;                                      \
		config.cfg_type = cfg_name;                                 \
		config.cfg_data = &cfg_data;                                \
		cfg_status = drx_ctrl(demod, DRX_CTRL_GET_CFG, &config);    \
		अगर (cfg_status == 0) अणु                                      \
			value = cfg_data;                                   \
		पूर्ण अन्यथा अणु                                                    \
			value = (data_type)error_value;                     \
		पूर्ण                                                           \
	पूर्ण जबतक (0)

/* Configuration functions क्रम usage by Access (XS) Macros */

#अगर_अघोषित DRX_XS_CFG_BASE
#घोषणा DRX_XS_CFG_BASE (500)
#पूर्ण_अगर

#घोषणा DRX_XS_CFG_PRESET          (DRX_XS_CFG_BASE + 0)
#घोषणा DRX_XS_CFG_AUD_BTSC_DETECT (DRX_XS_CFG_BASE + 1)
#घोषणा DRX_XS_CFG_QAM_LOCKRANGE   (DRX_XS_CFG_BASE + 2)

/* Access Macros with device-specअगरic handling */

#घोषणा DRX_SET_PRESET(d, x) \
	DRX_ACCESSMACRO_SET((d), (x), DRX_XS_CFG_PRESET, अक्षर*)
#घोषणा DRX_GET_PRESET(d, x) \
	DRX_ACCESSMACRO_GET((d), (x), DRX_XS_CFG_PRESET, अक्षर*, "ERROR")

#घोषणा DRX_SET_AUD_BTSC_DETECT(d, x) DRX_ACCESSMACRO_SET((d), (x), \
	 DRX_XS_CFG_AUD_BTSC_DETECT, क्रमागत drx_aud_btsc_detect)
#घोषणा DRX_GET_AUD_BTSC_DETECT(d, x) DRX_ACCESSMACRO_GET((d), (x), \
	 DRX_XS_CFG_AUD_BTSC_DETECT, क्रमागत drx_aud_btsc_detect, DRX_UNKNOWN)

#घोषणा DRX_SET_QAM_LOCKRANGE(d, x) DRX_ACCESSMACRO_SET((d), (x), \
	 DRX_XS_CFG_QAM_LOCKRANGE, क्रमागत drx_qam_lock_range)
#घोषणा DRX_GET_QAM_LOCKRANGE(d, x) DRX_ACCESSMACRO_GET((d), (x), \
	 DRX_XS_CFG_QAM_LOCKRANGE, क्रमागत drx_qam_lock_range, DRX_UNKNOWN)

/*
* \मrief Macro to check अगर std is an ATV standard
* \लetval true std is an ATV standard
* \लetval false std is an ATV standard
*/
#घोषणा DRX_ISATVSTD(std) (((std) == DRX_STANDARD_PAL_SECAM_BG) || \
			      ((std) == DRX_STANDARD_PAL_SECAM_DK) || \
			      ((std) == DRX_STANDARD_PAL_SECAM_I) || \
			      ((std) == DRX_STANDARD_PAL_SECAM_L) || \
			      ((std) == DRX_STANDARD_PAL_SECAM_LP) || \
			      ((std) == DRX_STANDARD_NTSC) || \
			      ((std) == DRX_STANDARD_FM))

/*
* \मrief Macro to check अगर std is an QAM standard
* \लetval true std is an QAM standards
* \लetval false std is an QAM standards
*/
#घोषणा DRX_ISQAMSTD(std) (((std) == DRX_STANDARD_ITU_A) || \
			      ((std) == DRX_STANDARD_ITU_B) || \
			      ((std) == DRX_STANDARD_ITU_C) || \
			      ((std) == DRX_STANDARD_ITU_D))

/*
* \मrief Macro to check अगर std is VSB standard
* \लetval true std is VSB standard
* \लetval false std is not VSB standard
*/
#घोषणा DRX_ISVSBSTD(std) ((std) == DRX_STANDARD_8VSB)

/*
* \मrief Macro to check अगर std is DVBT standard
* \लetval true std is DVBT standard
* \लetval false std is not DVBT standard
*/
#घोषणा DRX_ISDVBTSTD(std) ((std) == DRX_STANDARD_DVBT)

/*-------------------------------------------------------------------------
THE END
-------------------------------------------------------------------------*/
#पूर्ण_अगर				/* __DRXDRIVER_H__ */
