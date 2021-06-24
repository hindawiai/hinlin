<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2015-2017 Google, Inc
 */

#अगर_अघोषित __LINUX_USB_TCPM_H
#घोषणा __LINUX_USB_TCPM_H

#समावेश <linux/bitops.h>
#समावेश <linux/usb/typec.h>
#समावेश "pd.h"

क्रमागत typec_cc_status अणु
	TYPEC_CC_OPEN,
	TYPEC_CC_RA,
	TYPEC_CC_RD,
	TYPEC_CC_RP_DEF,
	TYPEC_CC_RP_1_5,
	TYPEC_CC_RP_3_0,
पूर्ण;

/* Collision Aव्योमance */
#घोषणा SINK_TX_NG	TYPEC_CC_RP_1_5
#घोषणा SINK_TX_OK	TYPEC_CC_RP_3_0

क्रमागत typec_cc_polarity अणु
	TYPEC_POLARITY_CC1,
	TYPEC_POLARITY_CC2,
पूर्ण;

/* Time to रुको क्रम TCPC to complete transmit */
#घोषणा PD_T_TCPC_TX_TIMEOUT	100		/* in ms	*/
#घोषणा PD_ROLE_SWAP_TIMEOUT	(MSEC_PER_SEC * 10)
#घोषणा PD_PPS_CTRL_TIMEOUT	(MSEC_PER_SEC * 10)

क्रमागत tcpm_transmit_status अणु
	TCPC_TX_SUCCESS = 0,
	TCPC_TX_DISCARDED = 1,
	TCPC_TX_FAILED = 2,
पूर्ण;

क्रमागत tcpm_transmit_type अणु
	TCPC_TX_SOP = 0,
	TCPC_TX_SOP_PRIME = 1,
	TCPC_TX_SOP_PRIME_PRIME = 2,
	TCPC_TX_SOP_DEBUG_PRIME = 3,
	TCPC_TX_SOP_DEBUG_PRIME_PRIME = 4,
	TCPC_TX_HARD_RESET = 5,
	TCPC_TX_CABLE_RESET = 6,
	TCPC_TX_BIST_MODE_2 = 7
पूर्ण;

/* Mux state attributes */
#घोषणा TCPC_MUX_USB_ENABLED		BIT(0)	/* USB enabled */
#घोषणा TCPC_MUX_DP_ENABLED		BIT(1)	/* DP enabled */
#घोषणा TCPC_MUX_POLARITY_INVERTED	BIT(2)	/* Polarity inverted */

/**
 * काष्ठा tcpc_dev - Port configuration and callback functions
 * @fwnode:	Poपूर्णांकer to port fwnode
 * @get_vbus:	Called to पढ़ो current VBUS state
 * @get_current_limit:
 *		Optional; called by the tcpm core when configured as a snk
 *		and cc=Rp-def. This allows the tcpm to provide a fallback
 *		current-limit detection method क्रम the cc=Rp-def हाल.
 *		For example, some tcpcs may include BC1.2 अक्षरger detection
 *		and use that in this हाल.
 * @set_cc:	Called to set value of CC pins
 * @get_cc:	Called to पढ़ो current CC pin values
 * @set_polarity:
 *		Called to set polarity
 * @set_vconn:	Called to enable or disable VCONN
 * @set_vbus:	Called to enable or disable VBUS
 * @set_current_limit:
 *		Optional; called to set current limit as negotiated
 *		with partner.
 * @set_pd_rx:	Called to enable or disable reception of PD messages
 * @set_roles:	Called to set घातer and data roles
 * @start_toggling:
 *		Optional; अगर supported by hardware, called to start dual-role
 *		toggling or single-role connection detection. Toggling stops
 *		स्वतःmatically अगर a connection is established.
 * @try_role:	Optional; called to set a preferred role
 * @pd_transmit:Called to transmit PD message
 * @set_bist_data: Turn on/off bist data mode क्रम compliance testing
 * @enable_frs:
 *		Optional; Called to enable/disable PD 3.0 fast role swap.
 *		Enabling frs is accessory dependent as not all PD3.0
 *		accessories support fast role swap.
 * @frs_sourcing_vbus:
 *		Optional; Called to notअगरy that vbus is now being sourced.
 *		Low level drivers can perक्रमm chip specअगरic operations, अगर any.
 * @enable_स्वतः_vbus_disअक्षरge:
 *		Optional; TCPCI spec based TCPC implementations can optionally
 *		support hardware to स्वतःnomously dischrge vbus upon disconnecting
 *		as sink or source. TCPM संकेतs TCPC to enable the mechanism upon
 *		entering connected state and संकेतs disabling upon disconnect.
 * @set_स्वतः_vbus_disअक्षरge_threshold:
 *		Mandatory when enable_स्वतः_vbus_disअक्षरge is implemented. TCPM
 *		calls this function to allow lower levels drivers to program the
 *		vbus threshold voltage below which the vbus disअक्षरge circuit
 *		will be turned on. requested_vbus_voltage is set to 0 when vbus
 *		is going to disappear knowingly i.e. during PR_SWAP and
 *		HARD_RESET etc.
 * @is_vbus_vsafe0v:
 *		Optional; TCPCI spec based TCPC implementations are expected to
 *		detect VSAFE0V voltage level at vbus. When detection of VSAFE0V
 *		is supported by TCPC, set this callback क्रम TCPM to query
 *		whether vbus is at VSAFE0V when needed.
 *		Returns true when vbus is at VSAFE0V, false otherwise.
 * @set_partner_usb_comm_capable:
 *              Optional; The USB Communications Capable bit indicates अगर port
 *              partner is capable of communication over the USB data lines
 *              (e.g. D+/- or SS Tx/Rx). Called to notअगरy the status of the bit.
 */
काष्ठा tcpc_dev अणु
	काष्ठा fwnode_handle *fwnode;

	पूर्णांक (*init)(काष्ठा tcpc_dev *dev);
	पूर्णांक (*get_vbus)(काष्ठा tcpc_dev *dev);
	पूर्णांक (*get_current_limit)(काष्ठा tcpc_dev *dev);
	पूर्णांक (*set_cc)(काष्ठा tcpc_dev *dev, क्रमागत typec_cc_status cc);
	पूर्णांक (*get_cc)(काष्ठा tcpc_dev *dev, क्रमागत typec_cc_status *cc1,
		      क्रमागत typec_cc_status *cc2);
	पूर्णांक (*set_polarity)(काष्ठा tcpc_dev *dev,
			    क्रमागत typec_cc_polarity polarity);
	पूर्णांक (*set_vconn)(काष्ठा tcpc_dev *dev, bool on);
	पूर्णांक (*set_vbus)(काष्ठा tcpc_dev *dev, bool on, bool अक्षरge);
	पूर्णांक (*set_current_limit)(काष्ठा tcpc_dev *dev, u32 max_ma, u32 mv);
	पूर्णांक (*set_pd_rx)(काष्ठा tcpc_dev *dev, bool on);
	पूर्णांक (*set_roles)(काष्ठा tcpc_dev *dev, bool attached,
			 क्रमागत typec_role role, क्रमागत typec_data_role data);
	पूर्णांक (*start_toggling)(काष्ठा tcpc_dev *dev,
			      क्रमागत typec_port_type port_type,
			      क्रमागत typec_cc_status cc);
	पूर्णांक (*try_role)(काष्ठा tcpc_dev *dev, पूर्णांक role);
	पूर्णांक (*pd_transmit)(काष्ठा tcpc_dev *dev, क्रमागत tcpm_transmit_type type,
			   स्थिर काष्ठा pd_message *msg, अचिन्हित पूर्णांक negotiated_rev);
	पूर्णांक (*set_bist_data)(काष्ठा tcpc_dev *dev, bool on);
	पूर्णांक (*enable_frs)(काष्ठा tcpc_dev *dev, bool enable);
	व्योम (*frs_sourcing_vbus)(काष्ठा tcpc_dev *dev);
	पूर्णांक (*enable_स्वतः_vbus_disअक्षरge)(काष्ठा tcpc_dev *dev, bool enable);
	पूर्णांक (*set_स्वतः_vbus_disअक्षरge_threshold)(काष्ठा tcpc_dev *dev, क्रमागत typec_pwr_opmode mode,
						 bool pps_active, u32 requested_vbus_voltage);
	bool (*is_vbus_vsafe0v)(काष्ठा tcpc_dev *dev);
	व्योम (*set_partner_usb_comm_capable)(काष्ठा tcpc_dev *dev, bool enable);
पूर्ण;

काष्ठा tcpm_port;

काष्ठा tcpm_port *tcpm_रेजिस्टर_port(काष्ठा device *dev, काष्ठा tcpc_dev *tcpc);
व्योम tcpm_unरेजिस्टर_port(काष्ठा tcpm_port *port);

व्योम tcpm_vbus_change(काष्ठा tcpm_port *port);
व्योम tcpm_cc_change(काष्ठा tcpm_port *port);
व्योम tcpm_sink_frs(काष्ठा tcpm_port *port);
व्योम tcpm_sourcing_vbus(काष्ठा tcpm_port *port);
व्योम tcpm_pd_receive(काष्ठा tcpm_port *port,
		     स्थिर काष्ठा pd_message *msg);
व्योम tcpm_pd_transmit_complete(काष्ठा tcpm_port *port,
			       क्रमागत tcpm_transmit_status status);
व्योम tcpm_pd_hard_reset(काष्ठा tcpm_port *port);
व्योम tcpm_tcpc_reset(काष्ठा tcpm_port *port);

#पूर्ण_अगर /* __LINUX_USB_TCPM_H */
