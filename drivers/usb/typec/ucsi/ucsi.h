<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __DRIVER_USB_TYPEC_UCSI_H
#घोषणा __DRIVER_USB_TYPEC_UCSI_H

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/types.h>
#समावेश <linux/usb/typec.h>
#समावेश <linux/usb/pd.h>
#समावेश <linux/usb/role.h>

/* -------------------------------------------------------------------------- */

काष्ठा ucsi;
काष्ठा ucsi_alपंचांगode;

/* UCSI offsets (Bytes) */
#घोषणा UCSI_VERSION			0
#घोषणा UCSI_CCI			4
#घोषणा UCSI_CONTROL			8
#घोषणा UCSI_MESSAGE_IN			16
#घोषणा UCSI_MESSAGE_OUT		32

/* Command Status and Connector Change Indication (CCI) bits */
#घोषणा UCSI_CCI_CONNECTOR(_c_)		(((_c_) & GENMASK(7, 1)) >> 1)
#घोषणा UCSI_CCI_LENGTH(_c_)		(((_c_) & GENMASK(15, 8)) >> 8)
#घोषणा UCSI_CCI_NOT_SUPPORTED		BIT(25)
#घोषणा UCSI_CCI_CANCEL_COMPLETE	BIT(26)
#घोषणा UCSI_CCI_RESET_COMPLETE		BIT(27)
#घोषणा UCSI_CCI_BUSY			BIT(28)
#घोषणा UCSI_CCI_ACK_COMPLETE		BIT(29)
#घोषणा UCSI_CCI_ERROR			BIT(30)
#घोषणा UCSI_CCI_COMMAND_COMPLETE	BIT(31)

/**
 * काष्ठा ucsi_operations - UCSI I/O operations
 * @पढ़ो: Read operation
 * @sync_ग_लिखो: Blocking ग_लिखो operation
 * @async_ग_लिखो: Non-blocking ग_लिखो operation
 * @update_alपंचांगodes: Squashes duplicate DP alपंचांगodes
 *
 * Read and ग_लिखो routines क्रम UCSI पूर्णांकerface. @sync_ग_लिखो must रुको क्रम the
 * Command Completion Event from the PPM beक्रमe वापसing, and @async_ग_लिखो must
 * वापस immediately after sending the data to the PPM.
 */
काष्ठा ucsi_operations अणु
	पूर्णांक (*पढ़ो)(काष्ठा ucsi *ucsi, अचिन्हित पूर्णांक offset,
		    व्योम *val, माप_प्रकार val_len);
	पूर्णांक (*sync_ग_लिखो)(काष्ठा ucsi *ucsi, अचिन्हित पूर्णांक offset,
			  स्थिर व्योम *val, माप_प्रकार val_len);
	पूर्णांक (*async_ग_लिखो)(काष्ठा ucsi *ucsi, अचिन्हित पूर्णांक offset,
			   स्थिर व्योम *val, माप_प्रकार val_len);
	bool (*update_alपंचांगodes)(काष्ठा ucsi *ucsi, काष्ठा ucsi_alपंचांगode *orig,
				काष्ठा ucsi_alपंचांगode *updated);
पूर्ण;

काष्ठा ucsi *ucsi_create(काष्ठा device *dev, स्थिर काष्ठा ucsi_operations *ops);
व्योम ucsi_destroy(काष्ठा ucsi *ucsi);
पूर्णांक ucsi_रेजिस्टर(काष्ठा ucsi *ucsi);
व्योम ucsi_unरेजिस्टर(काष्ठा ucsi *ucsi);
व्योम *ucsi_get_drvdata(काष्ठा ucsi *ucsi);
व्योम ucsi_set_drvdata(काष्ठा ucsi *ucsi, व्योम *data);

व्योम ucsi_connector_change(काष्ठा ucsi *ucsi, u8 num);

/* -------------------------------------------------------------------------- */

/* Commands */
#घोषणा UCSI_PPM_RESET			0x01
#घोषणा UCSI_CANCEL			0x02
#घोषणा UCSI_CONNECTOR_RESET		0x03
#घोषणा UCSI_ACK_CC_CI			0x04
#घोषणा UCSI_SET_NOTIFICATION_ENABLE	0x05
#घोषणा UCSI_GET_CAPABILITY		0x06
#घोषणा UCSI_GET_CONNECTOR_CAPABILITY	0x07
#घोषणा UCSI_SET_UOM			0x08
#घोषणा UCSI_SET_UOR			0x09
#घोषणा UCSI_SET_PDM			0x0a
#घोषणा UCSI_SET_PDR			0x0b
#घोषणा UCSI_GET_ALTERNATE_MODES	0x0c
#घोषणा UCSI_GET_CAM_SUPPORTED		0x0d
#घोषणा UCSI_GET_CURRENT_CAM		0x0e
#घोषणा UCSI_SET_NEW_CAM		0x0f
#घोषणा UCSI_GET_PDOS			0x10
#घोषणा UCSI_GET_CABLE_PROPERTY		0x11
#घोषणा UCSI_GET_CONNECTOR_STATUS	0x12
#घोषणा UCSI_GET_ERROR_STATUS		0x13

#घोषणा UCSI_CONNECTOR_NUMBER(_num_)		((u64)(_num_) << 16)
#घोषणा UCSI_COMMAND(_cmd_)			((_cmd_) & 0xff)

/* CONNECTOR_RESET command bits */
#घोषणा UCSI_CONNECTOR_RESET_HARD		BIT(23) /* Deprecated in v1.1 */

/* ACK_CC_CI bits */
#घोषणा UCSI_ACK_CONNECTOR_CHANGE		BIT(16)
#घोषणा UCSI_ACK_COMMAND_COMPLETE		BIT(17)

/* SET_NOTIFICATION_ENABLE command bits */
#घोषणा UCSI_ENABLE_NTFY_CMD_COMPLETE		BIT(16)
#घोषणा UCSI_ENABLE_NTFY_EXT_PWR_SRC_CHANGE	BIT(17)
#घोषणा UCSI_ENABLE_NTFY_PWR_OPMODE_CHANGE	BIT(18)
#घोषणा UCSI_ENABLE_NTFY_CAP_CHANGE		BIT(21)
#घोषणा UCSI_ENABLE_NTFY_PWR_LEVEL_CHANGE	BIT(22)
#घोषणा UCSI_ENABLE_NTFY_PD_RESET_COMPLETE	BIT(23)
#घोषणा UCSI_ENABLE_NTFY_CAM_CHANGE		BIT(24)
#घोषणा UCSI_ENABLE_NTFY_BAT_STATUS_CHANGE	BIT(25)
#घोषणा UCSI_ENABLE_NTFY_PARTNER_CHANGE		BIT(27)
#घोषणा UCSI_ENABLE_NTFY_PWR_सूची_CHANGE		BIT(28)
#घोषणा UCSI_ENABLE_NTFY_CONNECTOR_CHANGE	BIT(30)
#घोषणा UCSI_ENABLE_NTFY_ERROR			BIT(31)
#घोषणा UCSI_ENABLE_NTFY_ALL			0xdbe70000

/* SET_UOR command bits */
#घोषणा UCSI_SET_UOR_ROLE(_r_)		(((_r_) == TYPEC_HOST ? 1 : 2) << 23)
#घोषणा UCSI_SET_UOR_ACCEPT_ROLE_SWAPS		BIT(25)

/* SET_PDF command bits */
#घोषणा UCSI_SET_PDR_ROLE(_r_)		(((_r_) == TYPEC_SOURCE ? 1 : 2) << 23)
#घोषणा UCSI_SET_PDR_ACCEPT_ROLE_SWAPS		BIT(25)

/* GET_ALTERNATE_MODES command bits */
#घोषणा UCSI_ALTMODE_RECIPIENT(_r_)		(((_r_) >> 16) & 0x7)
#घोषणा UCSI_GET_ALTMODE_RECIPIENT(_r_)		((u64)(_r_) << 16)
#घोषणा   UCSI_RECIPIENT_CON			0
#घोषणा   UCSI_RECIPIENT_SOP			1
#घोषणा   UCSI_RECIPIENT_SOP_P			2
#घोषणा   UCSI_RECIPIENT_SOP_PP			3
#घोषणा UCSI_GET_ALTMODE_CONNECTOR_NUMBER(_r_)	((u64)(_r_) << 24)
#घोषणा UCSI_ALTMODE_OFFSET(_r_)		(((_r_) >> 32) & 0xff)
#घोषणा UCSI_GET_ALTMODE_OFFSET(_r_)		((u64)(_r_) << 32)
#घोषणा UCSI_GET_ALTMODE_NUM_ALTMODES(_r_)	((u64)(_r_) << 40)

/* GET_PDOS command bits */
#घोषणा UCSI_GET_PDOS_PARTNER_PDO(_r_)		((u64)(_r_) << 23)
#घोषणा UCSI_GET_PDOS_PDO_OFFSET(_r_)		((u64)(_r_) << 24)
#घोषणा UCSI_GET_PDOS_NUM_PDOS(_r_)		((u64)(_r_) << 32)
#घोषणा UCSI_MAX_PDOS				(4)
#घोषणा UCSI_GET_PDOS_SRC_PDOS			((u64)1 << 34)

/* -------------------------------------------------------------------------- */

/* Error inक्रमmation वापसed by PPM in response to GET_ERROR_STATUS command. */
#घोषणा UCSI_ERROR_UNREGONIZED_CMD		BIT(0)
#घोषणा UCSI_ERROR_INVALID_CON_NUM		BIT(1)
#घोषणा UCSI_ERROR_INVALID_CMD_ARGUMENT		BIT(2)
#घोषणा UCSI_ERROR_INCOMPATIBLE_PARTNER		BIT(3)
#घोषणा UCSI_ERROR_CC_COMMUNICATION_ERR		BIT(4)
#घोषणा UCSI_ERROR_DEAD_BATTERY			BIT(5)
#घोषणा UCSI_ERROR_CONTRACT_NEGOTIATION_FAIL	BIT(6)
#घोषणा UCSI_ERROR_OVERCURRENT			BIT(7)
#घोषणा UCSI_ERROR_UNDEFINED			BIT(8)
#घोषणा UCSI_ERROR_PARTNER_REJECTED_SWAP	BIT(9)
#घोषणा UCSI_ERROR_HARD_RESET			BIT(10)
#घोषणा UCSI_ERROR_PPM_POLICY_CONFLICT		BIT(11)
#घोषणा UCSI_ERROR_SWAP_REJECTED		BIT(12)

#घोषणा UCSI_SET_NEW_CAM_ENTER(x)		(((x) >> 23) & 0x1)
#घोषणा UCSI_SET_NEW_CAM_GET_AM(x)		(((x) >> 24) & 0xff)
#घोषणा UCSI_SET_NEW_CAM_AM_MASK		(0xff << 24)
#घोषणा UCSI_SET_NEW_CAM_SET_AM(x)		(((x) & 0xff) << 24)
#घोषणा UCSI_CMD_CONNECTOR_MASK			(0x7)

/* Data काष्ठाure filled by PPM in response to GET_CAPABILITY command. */
काष्ठा ucsi_capability अणु
	u32 attributes;
#घोषणा UCSI_CAP_ATTR_DISABLE_STATE		BIT(0)
#घोषणा UCSI_CAP_ATTR_BATTERY_CHARGING		BIT(1)
#घोषणा UCSI_CAP_ATTR_USB_PD			BIT(2)
#घोषणा UCSI_CAP_ATTR_TYPEC_CURRENT		BIT(6)
#घोषणा UCSI_CAP_ATTR_POWER_AC_SUPPLY		BIT(8)
#घोषणा UCSI_CAP_ATTR_POWER_OTHER		BIT(10)
#घोषणा UCSI_CAP_ATTR_POWER_VBUS		BIT(14)
	u8 num_connectors;
	u8 features;
#घोषणा UCSI_CAP_SET_UOM			BIT(0)
#घोषणा UCSI_CAP_SET_PDM			BIT(1)
#घोषणा UCSI_CAP_ALT_MODE_DETAILS		BIT(2)
#घोषणा UCSI_CAP_ALT_MODE_OVERRIDE		BIT(3)
#घोषणा UCSI_CAP_PDO_DETAILS			BIT(4)
#घोषणा UCSI_CAP_CABLE_DETAILS			BIT(5)
#घोषणा UCSI_CAP_EXT_SUPPLY_NOTIFICATIONS	BIT(6)
#घोषणा UCSI_CAP_PD_RESET			BIT(7)
	u16 reserved_1;
	u8 num_alt_modes;
	u8 reserved_2;
	u16 bc_version;
	u16 pd_version;
	u16 typec_version;
पूर्ण __packed;

/* Data काष्ठाure filled by PPM in response to GET_CONNECTOR_CAPABILITY cmd. */
काष्ठा ucsi_connector_capability अणु
	u8 op_mode;
#घोषणा UCSI_CONCAP_OPMODE_DFP			BIT(0)
#घोषणा UCSI_CONCAP_OPMODE_UFP			BIT(1)
#घोषणा UCSI_CONCAP_OPMODE_DRP			BIT(2)
#घोषणा UCSI_CONCAP_OPMODE_AUDIO_ACCESSORY	BIT(3)
#घोषणा UCSI_CONCAP_OPMODE_DEBUG_ACCESSORY	BIT(4)
#घोषणा UCSI_CONCAP_OPMODE_USB2			BIT(5)
#घोषणा UCSI_CONCAP_OPMODE_USB3			BIT(6)
#घोषणा UCSI_CONCAP_OPMODE_ALT_MODE		BIT(7)
	u8 flags;
#घोषणा UCSI_CONCAP_FLAG_PROVIDER		BIT(0)
#घोषणा UCSI_CONCAP_FLAG_CONSUMER		BIT(1)
पूर्ण __packed;

काष्ठा ucsi_alपंचांगode अणु
	u16 svid;
	u32 mid;
पूर्ण __packed;

/* Data काष्ठाure filled by PPM in response to GET_CABLE_PROPERTY command. */
काष्ठा ucsi_cable_property अणु
	u16 speed_supported;
	u8 current_capability;
	u8 flags;
#घोषणा UCSI_CABLE_PROP_FLAG_VBUS_IN_CABLE	BIT(0)
#घोषणा UCSI_CABLE_PROP_FLAG_ACTIVE_CABLE	BIT(1)
#घोषणा UCSI_CABLE_PROP_FLAG_सूचीECTIONALITY	BIT(2)
#घोषणा UCSI_CABLE_PROP_FLAG_PLUG_TYPE(_f_)	((_f_) & GENMASK(3, 0))
#घोषणा   UCSI_CABLE_PROPERTY_PLUG_TYPE_A	0
#घोषणा   UCSI_CABLE_PROPERTY_PLUG_TYPE_B	1
#घोषणा   UCSI_CABLE_PROPERTY_PLUG_TYPE_C	2
#घोषणा   UCSI_CABLE_PROPERTY_PLUG_OTHER	3
#घोषणा UCSI_CABLE_PROP_MODE_SUPPORT		BIT(5)
	u8 latency;
पूर्ण __packed;

/* Data काष्ठाure filled by PPM in response to GET_CONNECTOR_STATUS command. */
काष्ठा ucsi_connector_status अणु
	u16 change;
#घोषणा UCSI_CONSTAT_EXT_SUPPLY_CHANGE		BIT(1)
#घोषणा UCSI_CONSTAT_POWER_OPMODE_CHANGE	BIT(2)
#घोषणा UCSI_CONSTAT_PDOS_CHANGE		BIT(5)
#घोषणा UCSI_CONSTAT_POWER_LEVEL_CHANGE		BIT(6)
#घोषणा UCSI_CONSTAT_PD_RESET_COMPLETE		BIT(7)
#घोषणा UCSI_CONSTAT_CAM_CHANGE			BIT(8)
#घोषणा UCSI_CONSTAT_BC_CHANGE			BIT(9)
#घोषणा UCSI_CONSTAT_PARTNER_CHANGE		BIT(11)
#घोषणा UCSI_CONSTAT_POWER_सूची_CHANGE		BIT(12)
#घोषणा UCSI_CONSTAT_CONNECT_CHANGE		BIT(14)
#घोषणा UCSI_CONSTAT_ERROR			BIT(15)
	u16 flags;
#घोषणा UCSI_CONSTAT_PWR_OPMODE(_f_)		((_f_) & GENMASK(2, 0))
#घोषणा   UCSI_CONSTAT_PWR_OPMODE_NONE		0
#घोषणा   UCSI_CONSTAT_PWR_OPMODE_DEFAULT	1
#घोषणा   UCSI_CONSTAT_PWR_OPMODE_BC		2
#घोषणा   UCSI_CONSTAT_PWR_OPMODE_PD		3
#घोषणा   UCSI_CONSTAT_PWR_OPMODE_TYPEC1_5	4
#घोषणा   UCSI_CONSTAT_PWR_OPMODE_TYPEC3_0	5
#घोषणा UCSI_CONSTAT_CONNECTED			BIT(3)
#घोषणा UCSI_CONSTAT_PWR_सूची			BIT(4)
#घोषणा UCSI_CONSTAT_PARTNER_FLAGS(_f_)		(((_f_) & GENMASK(12, 5)) >> 5)
#घोषणा   UCSI_CONSTAT_PARTNER_FLAG_USB		1
#घोषणा   UCSI_CONSTAT_PARTNER_FLAG_ALT_MODE	2
#घोषणा UCSI_CONSTAT_PARTNER_TYPE(_f_)		(((_f_) & GENMASK(15, 13)) >> 13)
#घोषणा   UCSI_CONSTAT_PARTNER_TYPE_DFP		1
#घोषणा   UCSI_CONSTAT_PARTNER_TYPE_UFP		2
#घोषणा   UCSI_CONSTAT_PARTNER_TYPE_CABLE	3 /* Powered Cable */
#घोषणा   UCSI_CONSTAT_PARTNER_TYPE_CABLE_AND_UFP	4 /* Powered Cable */
#घोषणा   UCSI_CONSTAT_PARTNER_TYPE_DEBUG	5
#घोषणा   UCSI_CONSTAT_PARTNER_TYPE_AUDIO	6
	u32 request_data_obj;
	u8 pwr_status;
#घोषणा UCSI_CONSTAT_BC_STATUS(_p_)		((_p_) & GENMASK(2, 0))
#घोषणा   UCSI_CONSTAT_BC_NOT_CHARGING		0
#घोषणा   UCSI_CONSTAT_BC_NOMINAL_CHARGING	1
#घोषणा   UCSI_CONSTAT_BC_SLOW_CHARGING		2
#घोषणा   UCSI_CONSTAT_BC_TRICKLE_CHARGING	3
#घोषणा UCSI_CONSTAT_PROVIDER_CAP_LIMIT(_p_)	(((_p_) & GENMASK(6, 3)) >> 3)
#घोषणा   UCSI_CONSTAT_CAP_PWR_LOWERED		0
#घोषणा   UCSI_CONSTAT_CAP_PWR_BUDGET_LIMIT	1
पूर्ण __packed;

/* -------------------------------------------------------------------------- */

काष्ठा ucsi अणु
	u16 version;
	काष्ठा device *dev;
	काष्ठा driver_data *driver_data;

	स्थिर काष्ठा ucsi_operations *ops;

	काष्ठा ucsi_capability cap;
	काष्ठा ucsi_connector *connector;

	काष्ठा work_काष्ठा work;

	/* PPM Communication lock */
	काष्ठा mutex ppm_lock;

	/* The latest "Notification Enable" bits (SET_NOTIFICATION_ENABLE) */
	u64 ntfy;

	/* PPM communication flags */
	अचिन्हित दीर्घ flags;
#घोषणा EVENT_PENDING	0
#घोषणा COMMAND_PENDING	1
#घोषणा ACK_PENDING	2
#घोषणा EVENT_PROCESSING	3
पूर्ण;

#घोषणा UCSI_MAX_SVID		5
#घोषणा UCSI_MAX_ALTMODES	(UCSI_MAX_SVID * 6)

#घोषणा UCSI_TYPEC_VSAFE5V	5000
#घोषणा UCSI_TYPEC_1_5_CURRENT	1500
#घोषणा UCSI_TYPEC_3_0_CURRENT	3000

काष्ठा ucsi_connector अणु
	पूर्णांक num;

	काष्ठा ucsi *ucsi;
	काष्ठा mutex lock; /* port lock */
	काष्ठा work_काष्ठा work;
	काष्ठा completion complete;

	काष्ठा typec_port *port;
	काष्ठा typec_partner *partner;

	काष्ठा typec_alपंचांगode *port_alपंचांगode[UCSI_MAX_ALTMODES];
	काष्ठा typec_alपंचांगode *partner_alपंचांगode[UCSI_MAX_ALTMODES];

	काष्ठा typec_capability typec_cap;

	u16 unprocessed_changes;
	काष्ठा ucsi_connector_status status;
	काष्ठा ucsi_connector_capability cap;
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_desc psy_desc;
	u32 rकरो;
	u32 src_pकरोs[PDO_MAX_OBJECTS];
	पूर्णांक num_pकरोs;

	काष्ठा usb_role_चयन *usb_role_sw;
पूर्ण;

पूर्णांक ucsi_send_command(काष्ठा ucsi *ucsi, u64 command,
		      व्योम *retval, माप_प्रकार size);

व्योम ucsi_alपंचांगode_update_active(काष्ठा ucsi_connector *con);
पूर्णांक ucsi_resume(काष्ठा ucsi *ucsi);

#अगर IS_ENABLED(CONFIG_POWER_SUPPLY)
पूर्णांक ucsi_रेजिस्टर_port_psy(काष्ठा ucsi_connector *con);
व्योम ucsi_unरेजिस्टर_port_psy(काष्ठा ucsi_connector *con);
व्योम ucsi_port_psy_changed(काष्ठा ucsi_connector *con);
#अन्यथा
अटल अंतरभूत पूर्णांक ucsi_रेजिस्टर_port_psy(काष्ठा ucsi_connector *con) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ucsi_unरेजिस्टर_port_psy(काष्ठा ucsi_connector *con) अणु पूर्ण
अटल अंतरभूत व्योम ucsi_port_psy_changed(काष्ठा ucsi_connector *con) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_POWER_SUPPLY */

#अगर IS_ENABLED(CONFIG_TYPEC_DP_ALTMODE)
काष्ठा typec_alपंचांगode *
ucsi_रेजिस्टर_displayport(काष्ठा ucsi_connector *con,
			  bool override, पूर्णांक offset,
			  काष्ठा typec_alपंचांगode_desc *desc);

व्योम ucsi_displayport_हटाओ_partner(काष्ठा typec_alपंचांगode *adev);

#अन्यथा
अटल अंतरभूत काष्ठा typec_alपंचांगode *
ucsi_रेजिस्टर_displayport(काष्ठा ucsi_connector *con,
			  bool override, पूर्णांक offset,
			  काष्ठा typec_alपंचांगode_desc *desc)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
ucsi_displayport_हटाओ_partner(काष्ठा typec_alपंचांगode *adev) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_TYPEC_DP_ALTMODE */

/*
 * NVIDIA VirtualLink (svid 0x955) has two alपंचांगode. VirtualLink
 * DP mode with vकरो=0x1 and NVIDIA test mode with vकरो=0x3
 */
#घोषणा USB_TYPEC_NVIDIA_VLINK_DP_VDO	0x1
#घोषणा USB_TYPEC_NVIDIA_VLINK_DBG_VDO	0x3

#पूर्ण_अगर /* __DRIVER_USB_TYPEC_UCSI_H */
