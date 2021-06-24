<शैली गुरु>
#अगर_अघोषित NETDEV_PCS_H
#घोषणा NETDEV_PCS_H

#समावेश <linux/phy.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

काष्ठा device_node;
काष्ठा ethtool_cmd;
काष्ठा fwnode_handle;
काष्ठा net_device;

क्रमागत अणु
	MLO_PAUSE_NONE,
	MLO_PAUSE_RX = BIT(0),
	MLO_PAUSE_TX = BIT(1),
	MLO_PAUSE_TXRX_MASK = MLO_PAUSE_TX | MLO_PAUSE_RX,
	MLO_PAUSE_AN = BIT(2),

	MLO_AN_PHY = 0,	/* Conventional PHY */
	MLO_AN_FIXED,	/* Fixed-link mode */
	MLO_AN_INBAND,	/* In-band protocol */
पूर्ण;

अटल अंतरभूत bool phylink_स्वतःneg_inband(अचिन्हित पूर्णांक mode)
अणु
	वापस mode == MLO_AN_INBAND;
पूर्ण

/**
 * काष्ठा phylink_link_state - link state काष्ठाure
 * @advertising: ethtool biपंचांगask containing advertised link modes
 * @lp_advertising: ethtool biपंचांगask containing link partner advertised link
 *   modes
 * @पूर्णांकerface: link &प्रकार phy_पूर्णांकerface_t mode
 * @speed: link speed, one of the SPEED_* स्थिरants.
 * @duplex: link duplex mode, one of DUPLEX_* स्थिरants.
 * @छोड़ो: link छोड़ो state, described by MLO_PAUSE_* स्थिरants.
 * @link: true अगर the link is up.
 * @an_enabled: true अगर स्वतःnegotiation is enabled/desired.
 * @an_complete: true अगर स्वतःnegotiation has completed.
 */
काष्ठा phylink_link_state अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(advertising);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(lp_advertising);
	phy_पूर्णांकerface_t पूर्णांकerface;
	पूर्णांक speed;
	पूर्णांक duplex;
	पूर्णांक छोड़ो;
	अचिन्हित पूर्णांक link:1;
	अचिन्हित पूर्णांक an_enabled:1;
	अचिन्हित पूर्णांक an_complete:1;
पूर्ण;

क्रमागत phylink_op_type अणु
	PHYLINK_NETDEV = 0,
	PHYLINK_DEV,
पूर्ण;

/**
 * काष्ठा phylink_config - PHYLINK configuration काष्ठाure
 * @dev: a poपूर्णांकer to a काष्ठा device associated with the MAC
 * @type: operation type of PHYLINK instance
 * @pcs_poll: MAC PCS cannot provide link change पूर्णांकerrupt
 * @poll_fixed_state: अगर true, starts link_poll,
 *		      अगर MAC link is at %MLO_AN_FIXED mode.
 * @ovr_an_inband: अगर true, override PCS to MLO_AN_INBAND
 * @get_fixed_state: callback to execute to determine the fixed link state,
 *		     अगर MAC link is at %MLO_AN_FIXED mode.
 */
काष्ठा phylink_config अणु
	काष्ठा device *dev;
	क्रमागत phylink_op_type type;
	bool pcs_poll;
	bool poll_fixed_state;
	bool ovr_an_inband;
	व्योम (*get_fixed_state)(काष्ठा phylink_config *config,
				काष्ठा phylink_link_state *state);
पूर्ण;

/**
 * काष्ठा phylink_mac_ops - MAC operations काष्ठाure.
 * @validate: Validate and update the link configuration.
 * @mac_pcs_get_state: Read the current link state from the hardware.
 * @mac_prepare: prepare क्रम a major reconfiguration of the पूर्णांकerface.
 * @mac_config: configure the MAC क्रम the selected mode and state.
 * @mac_finish: finish a major reconfiguration of the पूर्णांकerface.
 * @mac_an_restart: restart 802.3z BaseX स्वतःnegotiation.
 * @mac_link_करोwn: take the link करोwn.
 * @mac_link_up: allow the link to come up.
 *
 * The inभागidual methods are described more fully below.
 */
काष्ठा phylink_mac_ops अणु
	व्योम (*validate)(काष्ठा phylink_config *config,
			 अचिन्हित दीर्घ *supported,
			 काष्ठा phylink_link_state *state);
	व्योम (*mac_pcs_get_state)(काष्ठा phylink_config *config,
				  काष्ठा phylink_link_state *state);
	पूर्णांक (*mac_prepare)(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			   phy_पूर्णांकerface_t अगरace);
	व्योम (*mac_config)(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			   स्थिर काष्ठा phylink_link_state *state);
	पूर्णांक (*mac_finish)(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			  phy_पूर्णांकerface_t अगरace);
	व्योम (*mac_an_restart)(काष्ठा phylink_config *config);
	व्योम (*mac_link_करोwn)(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			      phy_पूर्णांकerface_t पूर्णांकerface);
	व्योम (*mac_link_up)(काष्ठा phylink_config *config,
			    काष्ठा phy_device *phy, अचिन्हित पूर्णांक mode,
			    phy_पूर्णांकerface_t पूर्णांकerface, पूर्णांक speed, पूर्णांक duplex,
			    bool tx_छोड़ो, bool rx_छोड़ो);
पूर्ण;

#अगर 0 /* For kernel-करोc purposes only. */
/**
 * validate - Validate and update the link configuration
 * @config: a poपूर्णांकer to a &काष्ठा phylink_config.
 * @supported: ethtool biपंचांगask क्रम supported link modes.
 * @state: a poपूर्णांकer to a &काष्ठा phylink_link_state.
 *
 * Clear bits in the @supported and @state->advertising masks that
 * are not supportable by the MAC.
 *
 * Note that the PHY may be able to transक्रमm from one connection
 * technology to another, so, eg, करोn't clear 1000BaseX just
 * because the MAC is unable to BaseX mode. This is more about
 * clearing unsupported speeds and duplex settings. The port modes
 * should not be cleared; phylink_set_port_modes() will help with this.
 *
 * If the @state->पूर्णांकerface mode is %PHY_INTERFACE_MODE_1000BASEX
 * or %PHY_INTERFACE_MODE_2500BASEX, select the appropriate mode
 * based on @state->advertising and/or @state->speed and update
 * @state->पूर्णांकerface accordingly. See phylink_helper_basex_speed().
 *
 * When @state->पूर्णांकerface is %PHY_INTERFACE_MODE_NA, phylink expects the
 * MAC driver to वापस all supported link modes.
 *
 * If the @state->पूर्णांकerface mode is not supported, then the @supported
 * mask must be cleared.
 */
व्योम validate(काष्ठा phylink_config *config, अचिन्हित दीर्घ *supported,
	      काष्ठा phylink_link_state *state);

/**
 * mac_pcs_get_state() - Read the current inband link state from the hardware
 * @config: a poपूर्णांकer to a &काष्ठा phylink_config.
 * @state: a poपूर्णांकer to a &काष्ठा phylink_link_state.
 *
 * Read the current inband link state from the MAC PCS, reporting the
 * current speed in @state->speed, duplex mode in @state->duplex, छोड़ो
 * mode in @state->छोड़ो using the %MLO_PAUSE_RX and %MLO_PAUSE_TX bits,
 * negotiation completion state in @state->an_complete, and link up state
 * in @state->link. If possible, @state->lp_advertising should also be
 * populated.
 */
व्योम mac_pcs_get_state(काष्ठा phylink_config *config,
		       काष्ठा phylink_link_state *state);

/**
 * mac_prepare() - prepare to change the PHY पूर्णांकerface mode
 * @config: a poपूर्णांकer to a &काष्ठा phylink_config.
 * @mode: one of %MLO_AN_FIXED, %MLO_AN_PHY, %MLO_AN_INBAND.
 * @अगरace: पूर्णांकerface mode to चयन to
 *
 * phylink will call this method at the beginning of a full initialisation
 * of the link, which includes changing the पूर्णांकerface mode or at initial
 * startup समय. It may be called क्रम the current mode. The MAC driver
 * should perक्रमm whatever actions are required, e.g. disabling the
 * Serdes PHY.
 *
 * This will be the first call in the sequence:
 * - mac_prepare()
 * - mac_config()
 * - pcs_config()
 * - possible pcs_an_restart()
 * - mac_finish()
 *
 * Returns zero on success, or negative त्रुटि_सं on failure which will be
 * reported to the kernel log.
 */
पूर्णांक mac_prepare(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
		phy_पूर्णांकerface_t अगरace);

/**
 * mac_config() - configure the MAC क्रम the selected mode and state
 * @config: a poपूर्णांकer to a &काष्ठा phylink_config.
 * @mode: one of %MLO_AN_FIXED, %MLO_AN_PHY, %MLO_AN_INBAND.
 * @state: a poपूर्णांकer to a &काष्ठा phylink_link_state.
 *
 * Note - not all members of @state are valid.  In particular,
 * @state->lp_advertising, @state->link, @state->an_complete are never
 * guaranteed to be correct, and so any mac_config() implementation must
 * never reference these fields.
 *
 * (this requires a reग_लिखो - please refer to mac_link_up() क्रम situations
 *  where the PCS and MAC are not tightly पूर्णांकegrated.)
 *
 * In all negotiation modes, as defined by @mode, @state->छोड़ो indicates the
 * छोड़ो settings which should be applied as follows. If %MLO_PAUSE_AN is not
 * set, %MLO_PAUSE_TX and %MLO_PAUSE_RX indicate whether the MAC should send
 * छोड़ो frames and/or act on received छोड़ो frames respectively. Otherwise,
 * the results of in-band negotiation/status from the MAC PCS should be used
 * to control the MAC छोड़ो mode settings.
 *
 * The action perक्रमmed depends on the currently selected mode:
 *
 * %MLO_AN_FIXED, %MLO_AN_PHY:
 *   Configure क्रम non-inband negotiation mode, where the link settings
 *   are completely communicated via mac_link_up().  The physical link
 *   protocol from the MAC is specअगरied by @state->पूर्णांकerface.
 *
 *   @state->advertising may be used, but is not required.
 *
 *   Older drivers (prior to the mac_link_up() change) may use @state->speed,
 *   @state->duplex and @state->छोड़ो to configure the MAC, but this is
 *   deprecated; such drivers should be converted to use mac_link_up().
 *
 *   Other members of @state must be ignored.
 *
 *   Valid state members: पूर्णांकerface, advertising.
 *   Deprecated state members: speed, duplex, छोड़ो.
 *
 * %MLO_AN_INBAND:
 *   place the link in an inband negotiation mode (such as 802.3z
 *   1000base-X or Cisco SGMII mode depending on the @state->पूर्णांकerface
 *   mode). In both हालs, link state management (whether the link
 *   is up or not) is perक्रमmed by the MAC, and reported via the
 *   mac_pcs_get_state() callback. Changes in link state must be made
 *   by calling phylink_mac_change().
 *
 *   Interface mode specअगरic details are mentioned below.
 *
 *   If in 802.3z mode, the link speed is fixed, dependent on the
 *   @state->पूर्णांकerface. Duplex and छोड़ो modes are negotiated via
 *   the in-band configuration word. Advertised छोड़ो modes are set
 *   according to the @state->an_enabled and @state->advertising
 *   flags. Beware of MACs which only support full duplex at gigabit
 *   and higher speeds.
 *
 *   If in Cisco SGMII mode, the link speed and duplex mode are passed
 *   in the serial bitstream 16-bit configuration word, and the MAC
 *   should be configured to पढ़ो these bits and acknowledge the
 *   configuration word. Nothing is advertised by the MAC. The MAC is
 *   responsible क्रम पढ़ोing the configuration word and configuring
 *   itself accordingly.
 *
 *   Valid state members: पूर्णांकerface, an_enabled, छोड़ो, advertising.
 *
 * Implementations are expected to update the MAC to reflect the
 * requested settings - i.o.w., अगर nothing has changed between two
 * calls, no action is expected.  If only flow control settings have
 * changed, flow control should be updated *without* taking the link
 * करोwn.  This "update" behaviour is critical to aव्योम bouncing the
 * link up status.
 */
व्योम mac_config(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
		स्थिर काष्ठा phylink_link_state *state);

/**
 * mac_finish() - finish a to change the PHY पूर्णांकerface mode
 * @config: a poपूर्णांकer to a &काष्ठा phylink_config.
 * @mode: one of %MLO_AN_FIXED, %MLO_AN_PHY, %MLO_AN_INBAND.
 * @अगरace: पूर्णांकerface mode to चयन to
 *
 * phylink will call this अगर it called mac_prepare() to allow the MAC to
 * complete any necessary steps after the MAC and PCS have been configured
 * क्रम the @mode and @अगरace. E.g. a MAC driver may wish to re-enable the
 * Serdes PHY here अगर it was previously disabled by mac_prepare().
 *
 * Returns zero on success, or negative त्रुटि_सं on failure which will be
 * reported to the kernel log.
 */
पूर्णांक mac_finish(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
		phy_पूर्णांकerface_t अगरace);

/**
 * mac_an_restart() - restart 802.3z BaseX स्वतःnegotiation
 * @config: a poपूर्णांकer to a &काष्ठा phylink_config.
 */
व्योम mac_an_restart(काष्ठा phylink_config *config);

/**
 * mac_link_करोwn() - take the link करोwn
 * @config: a poपूर्णांकer to a &काष्ठा phylink_config.
 * @mode: link स्वतःnegotiation mode
 * @पूर्णांकerface: link &प्रकार phy_पूर्णांकerface_t mode
 *
 * If @mode is not an in-band negotiation mode (as defined by
 * phylink_स्वतःneg_inband()), क्रमce the link करोwn and disable any
 * Energy Efficient Ethernet MAC configuration. Interface type
 * selection must be करोne in mac_config().
 */
व्योम mac_link_करोwn(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
		   phy_पूर्णांकerface_t पूर्णांकerface);

/**
 * mac_link_up() - allow the link to come up
 * @config: a poपूर्णांकer to a &काष्ठा phylink_config.
 * @phy: any attached phy
 * @mode: link स्वतःnegotiation mode
 * @पूर्णांकerface: link &प्रकार phy_पूर्णांकerface_t mode
 * @speed: link speed
 * @duplex: link duplex
 * @tx_छोड़ो: link transmit छोड़ो enablement status
 * @rx_छोड़ो: link receive छोड़ो enablement status
 *
 * Configure the MAC क्रम an established link.
 *
 * @speed, @duplex, @tx_छोड़ो and @rx_छोड़ो indicate the finalised link
 * settings, and should be used to configure the MAC block appropriately
 * where these settings are not स्वतःmatically conveyed from the PCS block,
 * or अगर in-band negotiation (as defined by phylink_स्वतःneg_inband(@mode))
 * is disabled.
 *
 * Note that when 802.3z in-band negotiation is in use, it is possible
 * that the user wishes to override the छोड़ो settings, and this should
 * be allowed when considering the implementation of this method.
 *
 * If in-band negotiation mode is disabled, allow the link to come up. If
 * @phy is non-%शून्य, configure Energy Efficient Ethernet by calling
 * phy_init_eee() and perक्रमm appropriate MAC configuration क्रम EEE.
 * Interface type selection must be करोne in mac_config().
 */
व्योम mac_link_up(काष्ठा phylink_config *config, काष्ठा phy_device *phy,
		 अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
		 पूर्णांक speed, पूर्णांक duplex, bool tx_छोड़ो, bool rx_छोड़ो);
#पूर्ण_अगर

काष्ठा phylink_pcs_ops;

/**
 * काष्ठा phylink_pcs - PHYLINK PCS instance
 * @ops: a poपूर्णांकer to the &काष्ठा phylink_pcs_ops काष्ठाure
 * @poll: poll the PCS क्रम link changes
 *
 * This काष्ठाure is deचिन्हित to be embedded within the PCS निजी data,
 * and will be passed between phylink and the PCS.
 */
काष्ठा phylink_pcs अणु
	स्थिर काष्ठा phylink_pcs_ops *ops;
	bool poll;
पूर्ण;

/**
 * काष्ठा phylink_pcs_ops - MAC PCS operations काष्ठाure.
 * @pcs_get_state: पढ़ो the current MAC PCS link state from the hardware.
 * @pcs_config: configure the MAC PCS क्रम the selected mode and state.
 * @pcs_an_restart: restart 802.3z BaseX स्वतःnegotiation.
 * @pcs_link_up: program the PCS क्रम the resolved link configuration
 *               (where necessary).
 */
काष्ठा phylink_pcs_ops अणु
	व्योम (*pcs_get_state)(काष्ठा phylink_pcs *pcs,
			      काष्ठा phylink_link_state *state);
	पूर्णांक (*pcs_config)(काष्ठा phylink_pcs *pcs, अचिन्हित पूर्णांक mode,
			  phy_पूर्णांकerface_t पूर्णांकerface,
			  स्थिर अचिन्हित दीर्घ *advertising,
			  bool permit_छोड़ो_to_mac);
	व्योम (*pcs_an_restart)(काष्ठा phylink_pcs *pcs);
	व्योम (*pcs_link_up)(काष्ठा phylink_pcs *pcs, अचिन्हित पूर्णांक mode,
			    phy_पूर्णांकerface_t पूर्णांकerface, पूर्णांक speed, पूर्णांक duplex);
पूर्ण;

#अगर 0 /* For kernel-करोc purposes only. */
/**
 * pcs_get_state() - Read the current inband link state from the hardware
 * @pcs: a poपूर्णांकer to a &काष्ठा phylink_pcs.
 * @state: a poपूर्णांकer to a &काष्ठा phylink_link_state.
 *
 * Read the current inband link state from the MAC PCS, reporting the
 * current speed in @state->speed, duplex mode in @state->duplex, छोड़ो
 * mode in @state->छोड़ो using the %MLO_PAUSE_RX and %MLO_PAUSE_TX bits,
 * negotiation completion state in @state->an_complete, and link up state
 * in @state->link. If possible, @state->lp_advertising should also be
 * populated.
 *
 * When present, this overrides mac_pcs_get_state() in &काष्ठा
 * phylink_mac_ops.
 */
व्योम pcs_get_state(काष्ठा phylink_pcs *pcs,
		   काष्ठा phylink_link_state *state);

/**
 * pcs_config() - Configure the PCS mode and advertisement
 * @pcs: a poपूर्णांकer to a &काष्ठा phylink_pcs.
 * @mode: one of %MLO_AN_FIXED, %MLO_AN_PHY, %MLO_AN_INBAND.
 * @पूर्णांकerface: पूर्णांकerface mode to be used
 * @advertising: adertisement ethtool link mode mask
 * @permit_छोड़ो_to_mac: permit क्रमwarding छोड़ो resolution to MAC
 *
 * Configure the PCS क्रम the operating mode, the पूर्णांकerface mode, and set
 * the advertisement mask. @permit_छोड़ो_to_mac indicates whether the
 * hardware may क्रमward the छोड़ो mode resolution to the MAC.
 *
 * When operating in %MLO_AN_INBAND, inband should always be enabled,
 * otherwise inband should be disabled.
 *
 * For SGMII, there is no advertisement from the MAC side, the PCS should
 * be programmed to acknowledge the inband word from the PHY.
 *
 * For 1000BASE-X, the advertisement should be programmed पूर्णांकo the PCS.
 *
 * For most 10GBASE-R, there is no advertisement.
 */
पूर्णांक pcs_config(काष्ठा phylink_pcs *pcs, अचिन्हित पूर्णांक mode,
	       phy_पूर्णांकerface_t पूर्णांकerface, स्थिर अचिन्हित दीर्घ *advertising,
	       bool permit_छोड़ो_to_mac);

/**
 * pcs_an_restart() - restart 802.3z BaseX स्वतःnegotiation
 * @pcs: a poपूर्णांकer to a &काष्ठा phylink_pcs.
 *
 * When PCS ops are present, this overrides mac_an_restart() in &काष्ठा
 * phylink_mac_ops.
 */
व्योम pcs_an_restart(काष्ठा phylink_pcs *pcs);

/**
 * pcs_link_up() - program the PCS क्रम the resolved link configuration
 * @pcs: a poपूर्णांकer to a &काष्ठा phylink_pcs.
 * @mode: link स्वतःnegotiation mode
 * @पूर्णांकerface: link &प्रकार phy_पूर्णांकerface_t mode
 * @speed: link speed
 * @duplex: link duplex
 *
 * This call will be made just beक्रमe mac_link_up() to inक्रमm the PCS of
 * the resolved link parameters. For example, a PCS operating in SGMII
 * mode without in-band AN needs to be manually configured क्रम the link
 * and duplex setting. Otherwise, this should be a no-op.
 */
व्योम pcs_link_up(काष्ठा phylink_pcs *pcs, अचिन्हित पूर्णांक mode,
		 phy_पूर्णांकerface_t पूर्णांकerface, पूर्णांक speed, पूर्णांक duplex);
#पूर्ण_अगर

काष्ठा phylink *phylink_create(काष्ठा phylink_config *, काष्ठा fwnode_handle *,
			       phy_पूर्णांकerface_t अगरace,
			       स्थिर काष्ठा phylink_mac_ops *mac_ops);
व्योम phylink_set_pcs(काष्ठा phylink *, काष्ठा phylink_pcs *pcs);
व्योम phylink_destroy(काष्ठा phylink *);

पूर्णांक phylink_connect_phy(काष्ठा phylink *, काष्ठा phy_device *);
पूर्णांक phylink_of_phy_connect(काष्ठा phylink *, काष्ठा device_node *, u32 flags);
व्योम phylink_disconnect_phy(काष्ठा phylink *);

व्योम phylink_mac_change(काष्ठा phylink *, bool up);

व्योम phylink_start(काष्ठा phylink *);
व्योम phylink_stop(काष्ठा phylink *);

व्योम phylink_ethtool_get_wol(काष्ठा phylink *, काष्ठा ethtool_wolinfo *);
पूर्णांक phylink_ethtool_set_wol(काष्ठा phylink *, काष्ठा ethtool_wolinfo *);

पूर्णांक phylink_ethtool_ksettings_get(काष्ठा phylink *,
				  काष्ठा ethtool_link_ksettings *);
पूर्णांक phylink_ethtool_ksettings_set(काष्ठा phylink *,
				  स्थिर काष्ठा ethtool_link_ksettings *);
पूर्णांक phylink_ethtool_nway_reset(काष्ठा phylink *);
व्योम phylink_ethtool_get_छोड़ोparam(काष्ठा phylink *,
				    काष्ठा ethtool_छोड़ोparam *);
पूर्णांक phylink_ethtool_set_छोड़ोparam(काष्ठा phylink *,
				   काष्ठा ethtool_छोड़ोparam *);
पूर्णांक phylink_get_eee_err(काष्ठा phylink *);
पूर्णांक phylink_init_eee(काष्ठा phylink *, bool);
पूर्णांक phylink_ethtool_get_eee(काष्ठा phylink *, काष्ठा ethtool_eee *);
पूर्णांक phylink_ethtool_set_eee(काष्ठा phylink *, काष्ठा ethtool_eee *);
पूर्णांक phylink_mii_ioctl(काष्ठा phylink *, काष्ठा अगरreq *, पूर्णांक);
पूर्णांक phylink_speed_करोwn(काष्ठा phylink *pl, bool sync);
पूर्णांक phylink_speed_up(काष्ठा phylink *pl);

#घोषणा phylink_zero(bm) \
	biपंचांगap_zero(bm, __ETHTOOL_LINK_MODE_MASK_NBITS)
#घोषणा __phylink_करो_bit(op, bm, mode) \
	op(ETHTOOL_LINK_MODE_ ## mode ## _BIT, bm)

#घोषणा phylink_set(bm, mode)	__phylink_करो_bit(__set_bit, bm, mode)
#घोषणा phylink_clear(bm, mode)	__phylink_करो_bit(__clear_bit, bm, mode)
#घोषणा phylink_test(bm, mode)	__phylink_करो_bit(test_bit, bm, mode)

व्योम phylink_set_port_modes(अचिन्हित दीर्घ *bits);
व्योम phylink_helper_basex_speed(काष्ठा phylink_link_state *state);

व्योम phylink_mii_c22_pcs_get_state(काष्ठा mdio_device *pcs,
				   काष्ठा phylink_link_state *state);
पूर्णांक phylink_mii_c22_pcs_set_advertisement(काष्ठा mdio_device *pcs,
					  phy_पूर्णांकerface_t पूर्णांकerface,
					  स्थिर अचिन्हित दीर्घ *advertising);
पूर्णांक phylink_mii_c22_pcs_config(काष्ठा mdio_device *pcs, अचिन्हित पूर्णांक mode,
			       phy_पूर्णांकerface_t पूर्णांकerface,
			       स्थिर अचिन्हित दीर्घ *advertising);
व्योम phylink_mii_c22_pcs_an_restart(काष्ठा mdio_device *pcs);

व्योम phylink_mii_c45_pcs_get_state(काष्ठा mdio_device *pcs,
				   काष्ठा phylink_link_state *state);

व्योम phylink_decode_usxgmii_word(काष्ठा phylink_link_state *state,
				 uपूर्णांक16_t lpa);
#पूर्ण_अगर
