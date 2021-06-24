<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_B43_PHY_COMMON_H_
#घोषणा LINUX_B43_PHY_COMMON_H_

#समावेश <linux/types.h>
#समावेश <linux/nl80211.h>

काष्ठा b43_wldev;

/* PHY रेजिस्टर routing bits */
#घोषणा B43_PHYROUTE			0x0C00 /* PHY रेजिस्टर routing bits mask */
#घोषणा  B43_PHYROUTE_BASE		0x0000 /* Base रेजिस्टरs */
#घोषणा  B43_PHYROUTE_OFDM_GPHY		0x0400 /* OFDM रेजिस्टर routing क्रम G-PHYs */
#घोषणा  B43_PHYROUTE_EXT_GPHY		0x0800 /* Extended G-PHY रेजिस्टरs */
#घोषणा  B43_PHYROUTE_N_BMODE		0x0C00 /* N-PHY BMODE रेजिस्टरs */

/* CCK (B-PHY) रेजिस्टरs. */
#घोषणा B43_PHY_CCK(reg)		((reg) | B43_PHYROUTE_BASE)
/* N-PHY रेजिस्टरs. */
#घोषणा B43_PHY_N(reg)			((reg) | B43_PHYROUTE_BASE)
/* N-PHY BMODE रेजिस्टरs. */
#घोषणा B43_PHY_N_BMODE(reg)		((reg) | B43_PHYROUTE_N_BMODE)
/* OFDM (A-PHY) रेजिस्टरs. */
#घोषणा B43_PHY_OFDM(reg)		((reg) | B43_PHYROUTE_OFDM_GPHY)
/* Extended G-PHY रेजिस्टरs. */
#घोषणा B43_PHY_EXTG(reg)		((reg) | B43_PHYROUTE_EXT_GPHY)


/* Masks क्रम the PHY versioning रेजिस्टरs. */
#घोषणा B43_PHYVER_ANALOG		0xF000
#घोषणा B43_PHYVER_ANALOG_SHIFT		12
#घोषणा B43_PHYVER_TYPE			0x0F00
#घोषणा B43_PHYVER_TYPE_SHIFT		8
#घोषणा B43_PHYVER_VERSION		0x00FF

/* PHY ग_लिखोs need to be flushed अगर we reach limit */
#घोषणा B43_MAX_WRITES_IN_ROW		24

/**
 * क्रमागत b43_पूर्णांकerference_mitigation - Interference Mitigation mode
 *
 * @B43_INTERFMODE_NONE:	Disabled
 * @B43_INTERFMODE_NONWLAN:	Non-WLAN Interference Mitigation
 * @B43_INTERFMODE_MANUALWLAN:	WLAN Interference Mitigation
 * @B43_INTERFMODE_AUTOWLAN:	Automatic WLAN Interference Mitigation
 */
क्रमागत b43_पूर्णांकerference_mitigation अणु
	B43_INTERFMODE_NONE,
	B43_INTERFMODE_NONWLAN,
	B43_INTERFMODE_MANUALWLAN,
	B43_INTERFMODE_AUTOWLAN,
पूर्ण;

/* Antenna identअगरiers */
क्रमागत अणु
	B43_ANTENNA0 = 0,	/* Antenna 0 */
	B43_ANTENNA1 = 1,	/* Antenna 1 */
	B43_ANTENNA_AUTO0 = 2,	/* Automatic, starting with antenna 0 */
	B43_ANTENNA_AUTO1 = 3,	/* Automatic, starting with antenna 1 */
	B43_ANTENNA2 = 4,
	B43_ANTENNA3 = 8,

	B43_ANTENNA_AUTO = B43_ANTENNA_AUTO0,
	B43_ANTENNA_DEFAULT = B43_ANTENNA_AUTO,
पूर्ण;

/**
 * क्रमागत b43_txpwr_result - Return value क्रम the recalc_txघातer PHY op.
 *
 * @B43_TXPWR_RES_NEED_ADJUST:	Values changed. Hardware adjusपंचांगent is needed.
 * @B43_TXPWR_RES_DONE:		No more work to करो. Everything is करोne.
 */
क्रमागत b43_txpwr_result अणु
	B43_TXPWR_RES_NEED_ADJUST,
	B43_TXPWR_RES_DONE,
पूर्ण;

/**
 * काष्ठा b43_phy_operations - Function poपूर्णांकers क्रम PHY ops.
 *
 * @allocate:		Allocate and initialise the PHY data काष्ठाures.
 * 			Must not be शून्य.
 * @मुक्त:		Destroy and मुक्त the PHY data काष्ठाures.
 * 			Must not be शून्य.
 *
 * @prepare_काष्ठाs:	Prepare the PHY data काष्ठाures.
 * 			The data काष्ठाures allocated in @allocate are
 * 			initialized here.
 * 			Must not be शून्य.
 * @prepare_hardware:	Prepare the PHY. This is called beक्रमe b43_chip_init to
 * 			करो some early early PHY hardware init.
 * 			Can be शून्य, अगर not required.
 * @init:		Initialize the PHY.
 * 			Must not be शून्य.
 * @निकास:		Shutकरोwn the PHY.
 * 			Can be शून्य, अगर not required.
 *
 * @phy_पढ़ो:		Read from a PHY रेजिस्टर.
 * 			Must not be शून्य.
 * @phy_ग_लिखो:		Write to a PHY रेजिस्टर.
 * 			Must not be शून्य.
 * @phy_maskset:	Maskset a PHY रेजिस्टर, taking लघुcuts.
 *			If it is शून्य, a generic algorithm is used.
 * @radio_पढ़ो:		Read from a Radio रेजिस्टर.
 * 			Must not be शून्य.
 * @radio_ग_लिखो:	Write to a Radio रेजिस्टर.
 * 			Must not be शून्य.
 *
 * @supports_hwpctl:	Returns a boolean whether Hardware Power Control
 * 			is supported or not.
 * 			If शून्य, hwpctl is assumed to be never supported.
 * @software_rfसमाप्त:	Turn the radio ON or OFF.
 * 			Possible state values are
 * 			RFKILL_STATE_SOFT_BLOCKED or
 * 			RFKILL_STATE_UNBLOCKED
 * 			Must not be शून्य.
 * @चयन_analog:	Turn the Analog on/off.
 * 			Must not be शून्य.
 * @चयन_channel:	Switch the radio to another channel.
 * 			Must not be शून्य.
 * @get_शेष_chan:	Just वापसs the शेष channel number.
 * 			Must not be शून्य.
 * @set_rx_antenna:	Set the antenna used क्रम RX.
 * 			Can be शून्य, अगर not supported.
 * @पूर्णांकerf_mitigation:	Switch the Interference Mitigation mode.
 * 			Can be शून्य, अगर not supported.
 *
 * @recalc_txघातer:	Recalculate the transmission घातer parameters.
 * 			This callback has to recalculate the TX घातer settings,
 * 			but करोes not need to ग_लिखो them to the hardware, yet.
 * 			Returns क्रमागत b43_txpwr_result to indicate whether the hardware
 * 			needs to be adjusted.
 * 			If B43_TXPWR_NEED_ADJUST is वापसed, @adjust_txघातer
 * 			will be called later.
 * 			If the parameter "ignore_tssi" is true, the TSSI values should
 * 			be ignored and a recalculation of the घातer settings should be
 * 			करोne even अगर the TSSI values did not change.
 * 			This function may sleep, but should not.
 * 			Must not be शून्य.
 * @adjust_txघातer:	Write the previously calculated TX घातer settings
 * 			(from @recalc_txघातer) to the hardware.
 * 			This function may sleep.
 * 			Can be शून्य, अगर (and ONLY अगर) @recalc_txघातer _always_
 * 			वापसs B43_TXPWR_RES_DONE.
 *
 * @pwork_15sec:	Periodic work. Called every 15 seconds.
 * 			Can be शून्य, अगर not required.
 * @pwork_60sec:	Periodic work. Called every 60 seconds.
 * 			Can be शून्य, अगर not required.
 */
काष्ठा b43_phy_operations अणु
	/* Initialisation */
	पूर्णांक (*allocate)(काष्ठा b43_wldev *dev);
	व्योम (*मुक्त)(काष्ठा b43_wldev *dev);
	व्योम (*prepare_काष्ठाs)(काष्ठा b43_wldev *dev);
	पूर्णांक (*prepare_hardware)(काष्ठा b43_wldev *dev);
	पूर्णांक (*init)(काष्ठा b43_wldev *dev);
	व्योम (*निकास)(काष्ठा b43_wldev *dev);

	/* Register access */
	u16 (*phy_पढ़ो)(काष्ठा b43_wldev *dev, u16 reg);
	व्योम (*phy_ग_लिखो)(काष्ठा b43_wldev *dev, u16 reg, u16 value);
	व्योम (*phy_maskset)(काष्ठा b43_wldev *dev, u16 reg, u16 mask, u16 set);
	u16 (*radio_पढ़ो)(काष्ठा b43_wldev *dev, u16 reg);
	व्योम (*radio_ग_लिखो)(काष्ठा b43_wldev *dev, u16 reg, u16 value);

	/* Radio */
	bool (*supports_hwpctl)(काष्ठा b43_wldev *dev);
	व्योम (*software_rfसमाप्त)(काष्ठा b43_wldev *dev, bool blocked);
	व्योम (*चयन_analog)(काष्ठा b43_wldev *dev, bool on);
	पूर्णांक (*चयन_channel)(काष्ठा b43_wldev *dev, अचिन्हित पूर्णांक new_channel);
	अचिन्हित पूर्णांक (*get_शेष_chan)(काष्ठा b43_wldev *dev);
	व्योम (*set_rx_antenna)(काष्ठा b43_wldev *dev, पूर्णांक antenna);
	पूर्णांक (*पूर्णांकerf_mitigation)(काष्ठा b43_wldev *dev,
				 क्रमागत b43_पूर्णांकerference_mitigation new_mode);

	/* Transmission घातer adjusपंचांगent */
	क्रमागत b43_txpwr_result (*recalc_txघातer)(काष्ठा b43_wldev *dev,
						bool ignore_tssi);
	व्योम (*adjust_txघातer)(काष्ठा b43_wldev *dev);

	/* Misc */
	व्योम (*pwork_15sec)(काष्ठा b43_wldev *dev);
	व्योम (*pwork_60sec)(काष्ठा b43_wldev *dev);
पूर्ण;

काष्ठा b43_phy_g;
काष्ठा b43_phy_n;
काष्ठा b43_phy_lp;
काष्ठा b43_phy_ht;
काष्ठा b43_phy_lcn;

काष्ठा b43_phy अणु
	/* Hardware operation callbacks. */
	स्थिर काष्ठा b43_phy_operations *ops;

	/* Most hardware context inक्रमmation is stored in the standard-
	 * specअगरic data काष्ठाures poपूर्णांकed to by the poपूर्णांकers below.
	 * Only one of them is valid (the currently enabled PHY). */
#अगर_घोषित CONFIG_B43_DEBUG
	/* No जोड़ क्रम debug build to क्रमce शून्य derefs in buggy code. */
	काष्ठा अणु
#अन्यथा
	जोड़ अणु
#पूर्ण_अगर
		/* G-PHY specअगरic inक्रमmation */
		काष्ठा b43_phy_g *g;
		/* N-PHY specअगरic inक्रमmation */
		काष्ठा b43_phy_n *n;
		/* LP-PHY specअगरic inक्रमmation */
		काष्ठा b43_phy_lp *lp;
		/* HT-PHY specअगरic inक्रमmation */
		काष्ठा b43_phy_ht *ht;
		/* LCN-PHY specअगरic inक्रमmation */
		काष्ठा b43_phy_lcn *lcn;
		/* AC-PHY specअगरic inक्रमmation */
		काष्ठा b43_phy_ac *ac;
	पूर्ण;

	/* Band support flags. */
	bool supports_2ghz;
	bool supports_5ghz;

	/* Is GMODE (2 GHz mode) bit enabled? */
	bool gmode;

	/* After घातer reset full init has to be perक्रमmed */
	bool करो_full_init;

	/* Analog Type */
	u8 analog;
	/* B43_PHYTYPE_ */
	u8 type;
	/* PHY revision number. */
	u8 rev;

	/* Count ग_लिखोs since last पढ़ो */
	u8 ग_लिखोs_counter;

	/* Radio versioning */
	u16 radio_manuf;	/* Radio manufacturer */
	u16 radio_ver;		/* Radio version */
	u8 radio_rev;		/* Radio revision */

	/* Software state of the radio */
	bool radio_on;

	/* Desired TX घातer level (in dBm).
	 * This is set by the user and adjusted in b43_phy_xmitघातer(). */
	पूर्णांक desired_txघातer;

	/* Hardware Power Control enabled? */
	bool hardware_घातer_control;

	/* The समय (in असलolute jअगरfies) when the next TX घातer output
	 * check is needed. */
	अचिन्हित दीर्घ next_txpwr_check_समय;

	/* Current channel */
	काष्ठा cfg80211_chan_def *chandef;
	अचिन्हित पूर्णांक channel;

	/* PHY TX errors counter. */
	atomic_t txerr_cnt;

#अगर_घोषित CONFIG_B43_DEBUG
	/* PHY रेजिस्टरs locked (w.r.t. firmware) */
	bool phy_locked;
	/* Radio रेजिस्टरs locked (w.r.t. firmware) */
	bool radio_locked;
#पूर्ण_अगर /* B43_DEBUG */
पूर्ण;


/**
 * b43_phy_allocate - Allocate PHY काष्ठाs
 * Allocate the PHY data काष्ठाures, based on the current dev->phy.type
 */
पूर्णांक b43_phy_allocate(काष्ठा b43_wldev *dev);

/**
 * b43_phy_मुक्त - Free PHY काष्ठाs
 */
व्योम b43_phy_मुक्त(काष्ठा b43_wldev *dev);

/**
 * b43_phy_init - Initialise the PHY
 */
पूर्णांक b43_phy_init(काष्ठा b43_wldev *dev);

/**
 * b43_phy_निकास - Cleanup PHY
 */
व्योम b43_phy_निकास(काष्ठा b43_wldev *dev);

/**
 * b43_has_hardware_pctl - Hardware Power Control supported?
 * Returns a boolean, whether hardware घातer control is supported.
 */
bool b43_has_hardware_pctl(काष्ठा b43_wldev *dev);

/**
 * b43_phy_पढ़ो - 16bit PHY रेजिस्टर पढ़ो access
 */
u16 b43_phy_पढ़ो(काष्ठा b43_wldev *dev, u16 reg);

/**
 * b43_phy_ग_लिखो - 16bit PHY रेजिस्टर ग_लिखो access
 */
व्योम b43_phy_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg, u16 value);

/**
 * b43_phy_copy - copy contents of 16bit PHY रेजिस्टर to another
 */
व्योम b43_phy_copy(काष्ठा b43_wldev *dev, u16 destreg, u16 srcreg);

/**
 * b43_phy_mask - Mask a PHY रेजिस्टर with a mask
 */
व्योम b43_phy_mask(काष्ठा b43_wldev *dev, u16 offset, u16 mask);

/**
 * b43_phy_set - OR a PHY रेजिस्टर with a biपंचांगap
 */
व्योम b43_phy_set(काष्ठा b43_wldev *dev, u16 offset, u16 set);

/**
 * b43_phy_maskset - Mask and OR a PHY रेजिस्टर with a mask and biपंचांगap
 */
व्योम b43_phy_maskset(काष्ठा b43_wldev *dev, u16 offset, u16 mask, u16 set);

/**
 * b43_radio_पढ़ो - 16bit Radio रेजिस्टर पढ़ो access
 */
u16 b43_radio_पढ़ो(काष्ठा b43_wldev *dev, u16 reg);
#घोषणा b43_radio_पढ़ो16	b43_radio_पढ़ो /* DEPRECATED */

/**
 * b43_radio_ग_लिखो - 16bit Radio रेजिस्टर ग_लिखो access
 */
व्योम b43_radio_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg, u16 value);
#घोषणा b43_radio_ग_लिखो16	b43_radio_ग_लिखो /* DEPRECATED */

/**
 * b43_radio_mask - Mask a 16bit radio रेजिस्टर with a mask
 */
व्योम b43_radio_mask(काष्ठा b43_wldev *dev, u16 offset, u16 mask);

/**
 * b43_radio_set - OR a 16bit radio रेजिस्टर with a biपंचांगap
 */
व्योम b43_radio_set(काष्ठा b43_wldev *dev, u16 offset, u16 set);

/**
 * b43_radio_maskset - Mask and OR a radio रेजिस्टर with a mask and biपंचांगap
 */
व्योम b43_radio_maskset(काष्ठा b43_wldev *dev, u16 offset, u16 mask, u16 set);

/**
 * b43_radio_रुको_value - Waits क्रम a given value in masked रेजिस्टर पढ़ो
 */
bool b43_radio_रुको_value(काष्ठा b43_wldev *dev, u16 offset, u16 mask,
			  u16 value, पूर्णांक delay, पूर्णांक समयout);

/**
 * b43_radio_lock - Lock firmware radio रेजिस्टर access
 */
व्योम b43_radio_lock(काष्ठा b43_wldev *dev);

/**
 * b43_radio_unlock - Unlock firmware radio रेजिस्टर access
 */
व्योम b43_radio_unlock(काष्ठा b43_wldev *dev);

/**
 * b43_phy_lock - Lock firmware PHY रेजिस्टर access
 */
व्योम b43_phy_lock(काष्ठा b43_wldev *dev);

/**
 * b43_phy_unlock - Unlock firmware PHY रेजिस्टर access
 */
व्योम b43_phy_unlock(काष्ठा b43_wldev *dev);

व्योम b43_phy_put_पूर्णांकo_reset(काष्ठा b43_wldev *dev);
व्योम b43_phy_take_out_of_reset(काष्ठा b43_wldev *dev);

/**
 * b43_चयन_channel - Switch to another channel
 */
पूर्णांक b43_चयन_channel(काष्ठा b43_wldev *dev, अचिन्हित पूर्णांक new_channel);

/**
 * b43_software_rfसमाप्त - Turn the radio ON or OFF in software.
 */
व्योम b43_software_rfसमाप्त(काष्ठा b43_wldev *dev, bool blocked);

/**
 * b43_phy_txघातer_check - Check TX घातer output.
 *
 * Compare the current TX घातer output to the desired घातer emission
 * and schedule an adjusपंचांगent in हाल it mismatches.
 *
 * @flags:	OR'ed क्रमागत b43_phy_txघातer_check_flags flags.
 * 		See the करोcs below.
 */
व्योम b43_phy_txघातer_check(काष्ठा b43_wldev *dev, अचिन्हित पूर्णांक flags);
/**
 * क्रमागत b43_phy_txघातer_check_flags - Flags क्रम b43_phy_txघातer_check()
 *
 * @B43_TXPWR_IGNORE_TIME: Ignore the schedule समय and क्रमce-reकरो
 *                         the check now.
 * @B43_TXPWR_IGNORE_TSSI: Reकरो the recalculation, even अगर the average
 *                         TSSI did not change.
 */
क्रमागत b43_phy_txघातer_check_flags अणु
	B43_TXPWR_IGNORE_TIME		= (1 << 0),
	B43_TXPWR_IGNORE_TSSI		= (1 << 1),
पूर्ण;

काष्ठा work_काष्ठा;
व्योम b43_phy_txघातer_adjust_work(काष्ठा work_काष्ठा *work);

/**
 * b43_phy_shm_tssi_पढ़ो - Read the average of the last 4 TSSI from SHM.
 *
 * @shm_offset:		The SHM address to पढ़ो the values from.
 *
 * Returns the average of the 4 TSSI values, or a negative error code.
 */
पूर्णांक b43_phy_shm_tssi_पढ़ो(काष्ठा b43_wldev *dev, u16 shm_offset);

/**
 * b43_phy_चयन_analog_generic - Generic PHY operation क्रम चयनing the Analog.
 *
 * It करोes the चयनing based on the PHY0 core रेजिस्टर.
 * Do _not_ call this directly. Only use it as a चयन_analog callback
 * क्रम काष्ठा b43_phy_operations.
 */
व्योम b43_phyop_चयन_analog_generic(काष्ठा b43_wldev *dev, bool on);

bool b43_is_40mhz(काष्ठा b43_wldev *dev);

व्योम b43_phy_क्रमce_घड़ी(काष्ठा b43_wldev *dev, bool क्रमce);

#पूर्ण_अगर /* LINUX_B43_PHY_COMMON_H_ */
