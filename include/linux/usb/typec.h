<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __LINUX_USB_TYPEC_H
#घोषणा __LINUX_USB_TYPEC_H

#समावेश <linux/types.h>

/* USB Type-C Specअगरication releases */
#घोषणा USB_TYPEC_REV_1_0	0x100 /* 1.0 */
#घोषणा USB_TYPEC_REV_1_1	0x110 /* 1.1 */
#घोषणा USB_TYPEC_REV_1_2	0x120 /* 1.2 */
#घोषणा USB_TYPEC_REV_1_3	0x130 /* 1.3 */
#घोषणा USB_TYPEC_REV_1_4	0x140 /* 1.4 */
#घोषणा USB_TYPEC_REV_2_0	0x200 /* 2.0 */

काष्ठा typec_partner;
काष्ठा typec_cable;
काष्ठा typec_plug;
काष्ठा typec_port;
काष्ठा typec_alपंचांगode_ops;

काष्ठा fwnode_handle;
काष्ठा device;

क्रमागत typec_port_type अणु
	TYPEC_PORT_SRC,
	TYPEC_PORT_SNK,
	TYPEC_PORT_DRP,
पूर्ण;

क्रमागत typec_port_data अणु
	TYPEC_PORT_DFP,
	TYPEC_PORT_UFP,
	TYPEC_PORT_DRD,
पूर्ण;

क्रमागत typec_plug_type अणु
	USB_PLUG_NONE,
	USB_PLUG_TYPE_A,
	USB_PLUG_TYPE_B,
	USB_PLUG_TYPE_C,
	USB_PLUG_CAPTIVE,
पूर्ण;

क्रमागत typec_data_role अणु
	TYPEC_DEVICE,
	TYPEC_HOST,
पूर्ण;

क्रमागत typec_role अणु
	TYPEC_SINK,
	TYPEC_SOURCE,
पूर्ण;

क्रमागत typec_pwr_opmode अणु
	TYPEC_PWR_MODE_USB,
	TYPEC_PWR_MODE_1_5A,
	TYPEC_PWR_MODE_3_0A,
	TYPEC_PWR_MODE_PD,
पूर्ण;

क्रमागत typec_accessory अणु
	TYPEC_ACCESSORY_NONE,
	TYPEC_ACCESSORY_AUDIO,
	TYPEC_ACCESSORY_DEBUG,
पूर्ण;

#घोषणा TYPEC_MAX_ACCESSORY	3

क्रमागत typec_orientation अणु
	TYPEC_ORIENTATION_NONE,
	TYPEC_ORIENTATION_NORMAL,
	TYPEC_ORIENTATION_REVERSE,
पूर्ण;

/*
 * काष्ठा enter_usb_data - Enter_USB Message details
 * @euकरो: Enter_USB Data Object
 * @active_link_training: Active Cable Plug Link Training
 *
 * @active_link_training is a flag that should be set with uni-directional SBRX
 * communication, and left 0 with passive cables and with bi-directional SBRX
 * communication.
 */
काष्ठा enter_usb_data अणु
	u32			euकरो;
	अचिन्हित अक्षर		active_link_training:1;
पूर्ण;

/*
 * काष्ठा usb_pd_identity - USB Power Delivery identity data
 * @id_header: ID Header VDO
 * @cert_stat: Cert Stat VDO
 * @product: Product VDO
 * @vकरो: Product Type Specअगरic VDOs
 *
 * USB घातer delivery Discover Identity command response data.
 *
 * REVISIT: This is USB Power Delivery specअगरic inक्रमmation, so this काष्ठाure
 * probable beदीर्घs to USB Power Delivery header file once we have them.
 */
काष्ठा usb_pd_identity अणु
	u32			id_header;
	u32			cert_stat;
	u32			product;
	u32			vकरो[3];
पूर्ण;

पूर्णांक typec_partner_set_identity(काष्ठा typec_partner *partner);
पूर्णांक typec_cable_set_identity(काष्ठा typec_cable *cable);

/*
 * काष्ठा typec_alपंचांगode_desc - USB Type-C Alternate Mode Descriptor
 * @svid: Standard or Venकरोr ID
 * @mode: Index of the Mode
 * @vकरो: VDO वापसed by Discover Modes USB PD command
 * @roles: Only क्रम ports. DRP अगर the mode is available in both roles
 *
 * Description of an Alternate Mode which a connector, cable plug or partner
 * supports.
 */
काष्ठा typec_alपंचांगode_desc अणु
	u16			svid;
	u8			mode;
	u32			vकरो;
	/* Only used with ports */
	क्रमागत typec_port_data	roles;
पूर्ण;

व्योम typec_partner_set_pd_revision(काष्ठा typec_partner *partner, u16 pd_revision);
पूर्णांक typec_partner_set_num_alपंचांगodes(काष्ठा typec_partner *partner, पूर्णांक num_alपंचांगodes);
काष्ठा typec_alपंचांगode
*typec_partner_रेजिस्टर_alपंचांगode(काष्ठा typec_partner *partner,
				स्थिर काष्ठा typec_alपंचांगode_desc *desc);
पूर्णांक typec_plug_set_num_alपंचांगodes(काष्ठा typec_plug *plug, पूर्णांक num_alपंचांगodes);
काष्ठा typec_alपंचांगode
*typec_plug_रेजिस्टर_alपंचांगode(काष्ठा typec_plug *plug,
			     स्थिर काष्ठा typec_alपंचांगode_desc *desc);
काष्ठा typec_alपंचांगode
*typec_port_रेजिस्टर_alपंचांगode(काष्ठा typec_port *port,
			     स्थिर काष्ठा typec_alपंचांगode_desc *desc);

व्योम typec_port_रेजिस्टर_alपंचांगodes(काष्ठा typec_port *port,
	स्थिर काष्ठा typec_alपंचांगode_ops *ops, व्योम *drvdata,
	काष्ठा typec_alपंचांगode **alपंचांगodes, माप_प्रकार n);

व्योम typec_unरेजिस्टर_alपंचांगode(काष्ठा typec_alपंचांगode *alपंचांगode);

काष्ठा typec_port *typec_alपंचांगode2port(काष्ठा typec_alपंचांगode *alt);

व्योम typec_alपंचांगode_update_active(काष्ठा typec_alपंचांगode *alt, bool active);

क्रमागत typec_plug_index अणु
	TYPEC_PLUG_SOP_P,
	TYPEC_PLUG_SOP_PP,
पूर्ण;

/*
 * काष्ठा typec_plug_desc - USB Type-C Cable Plug Descriptor
 * @index: SOP Prime क्रम the plug connected to DFP and SOP Double Prime क्रम the
 *         plug connected to UFP
 *
 * Represents USB Type-C Cable Plug.
 */
काष्ठा typec_plug_desc अणु
	क्रमागत typec_plug_index	index;
पूर्ण;

/*
 * काष्ठा typec_cable_desc - USB Type-C Cable Descriptor
 * @type: The plug type from USB PD Cable VDO
 * @active: Is the cable active or passive
 * @identity: Result of Discover Identity command
 * @pd_revision: USB Power Delivery Specअगरication revision अगर supported
 *
 * Represents USB Type-C Cable attached to USB Type-C port.
 */
काष्ठा typec_cable_desc अणु
	क्रमागत typec_plug_type	type;
	अचिन्हित पूर्णांक		active:1;
	काष्ठा usb_pd_identity	*identity;
	u16			pd_revision; /* 0300H = "3.0" */

पूर्ण;

/*
 * काष्ठा typec_partner_desc - USB Type-C Partner Descriptor
 * @usb_pd: USB Power Delivery support
 * @accessory: Audio, Debug or none.
 * @identity: Discover Identity command data
 * @pd_revision: USB Power Delivery Specअगरication Revision अगर supported
 *
 * Details about a partner that is attached to USB Type-C port. If @identity
 * member exists when partner is रेजिस्टरed, a directory named "identity" is
 * created to sysfs क्रम the partner device.
 *
 * @pd_revision is based on the setting of the "Specification Revision" field
 * in the message header on the initial "Source Capabilities" message received
 * from the partner, or a "Request" message received from the partner, depending
 * on whether our port is a Sink or a Source.
 */
काष्ठा typec_partner_desc अणु
	अचिन्हित पूर्णांक		usb_pd:1;
	क्रमागत typec_accessory	accessory;
	काष्ठा usb_pd_identity	*identity;
	u16			pd_revision; /* 0300H = "3.0" */
पूर्ण;

/**
 * काष्ठा typec_operations - USB Type-C Port Operations
 * @try_role: Set data role preference क्रम DRP port
 * @dr_set: Set Data Role
 * @pr_set: Set Power Role
 * @vconn_set: Source VCONN
 * @port_type_set: Set port type
 */
काष्ठा typec_operations अणु
	पूर्णांक (*try_role)(काष्ठा typec_port *port, पूर्णांक role);
	पूर्णांक (*dr_set)(काष्ठा typec_port *port, क्रमागत typec_data_role role);
	पूर्णांक (*pr_set)(काष्ठा typec_port *port, क्रमागत typec_role role);
	पूर्णांक (*vconn_set)(काष्ठा typec_port *port, क्रमागत typec_role role);
	पूर्णांक (*port_type_set)(काष्ठा typec_port *port,
			     क्रमागत typec_port_type type);
पूर्ण;

क्रमागत usb_pd_svdm_ver अणु
	SVDM_VER_1_0 = 0,
	SVDM_VER_2_0 = 1,
	SVDM_VER_MAX = SVDM_VER_2_0,
पूर्ण;

/*
 * काष्ठा typec_capability - USB Type-C Port Capabilities
 * @type: Supported घातer role of the port
 * @data: Supported data role of the port
 * @revision: USB Type-C Specअगरication release. Binary coded decimal
 * @pd_revision: USB Power Delivery Specअगरication revision अगर supported
 * @svdm_version: USB PD Structured VDM version अगर supported
 * @prefer_role: Initial role preference (DRP ports).
 * @accessory: Supported Accessory Modes
 * @fwnode: Optional fwnode of the port
 * @driver_data: Private poपूर्णांकer क्रम driver specअगरic info
 * @ops: Port operations vector
 *
 * Static capabilities of a single USB Type-C port.
 */
काष्ठा typec_capability अणु
	क्रमागत typec_port_type	type;
	क्रमागत typec_port_data	data;
	u16			revision; /* 0120H = "1.2" */
	u16			pd_revision; /* 0300H = "3.0" */
	क्रमागत usb_pd_svdm_ver	svdm_version;
	पूर्णांक			prefer_role;
	क्रमागत typec_accessory	accessory[TYPEC_MAX_ACCESSORY];
	अचिन्हित पूर्णांक		orientation_aware:1;

	काष्ठा fwnode_handle	*fwnode;
	व्योम			*driver_data;

	स्थिर काष्ठा typec_operations	*ops;
पूर्ण;

/* Specअगरic to try_role(). Indicates the user want's to clear the preference. */
#घोषणा TYPEC_NO_PREFERRED_ROLE	(-1)

काष्ठा typec_port *typec_रेजिस्टर_port(काष्ठा device *parent,
				       स्थिर काष्ठा typec_capability *cap);
व्योम typec_unरेजिस्टर_port(काष्ठा typec_port *port);

काष्ठा typec_partner *typec_रेजिस्टर_partner(काष्ठा typec_port *port,
					     काष्ठा typec_partner_desc *desc);
व्योम typec_unरेजिस्टर_partner(काष्ठा typec_partner *partner);

काष्ठा typec_cable *typec_रेजिस्टर_cable(काष्ठा typec_port *port,
					 काष्ठा typec_cable_desc *desc);
व्योम typec_unरेजिस्टर_cable(काष्ठा typec_cable *cable);

काष्ठा typec_cable *typec_cable_get(काष्ठा typec_port *port);
व्योम typec_cable_put(काष्ठा typec_cable *cable);
पूर्णांक typec_cable_is_active(काष्ठा typec_cable *cable);

काष्ठा typec_plug *typec_रेजिस्टर_plug(काष्ठा typec_cable *cable,
				       काष्ठा typec_plug_desc *desc);
व्योम typec_unरेजिस्टर_plug(काष्ठा typec_plug *plug);

व्योम typec_set_data_role(काष्ठा typec_port *port, क्रमागत typec_data_role role);
व्योम typec_set_pwr_role(काष्ठा typec_port *port, क्रमागत typec_role role);
व्योम typec_set_vconn_role(काष्ठा typec_port *port, क्रमागत typec_role role);
व्योम typec_set_pwr_opmode(काष्ठा typec_port *port, क्रमागत typec_pwr_opmode mode);

पूर्णांक typec_set_orientation(काष्ठा typec_port *port,
			  क्रमागत typec_orientation orientation);
क्रमागत typec_orientation typec_get_orientation(काष्ठा typec_port *port);
पूर्णांक typec_set_mode(काष्ठा typec_port *port, पूर्णांक mode);

व्योम *typec_get_drvdata(काष्ठा typec_port *port);

पूर्णांक typec_find_pwr_opmode(स्थिर अक्षर *name);
पूर्णांक typec_find_orientation(स्थिर अक्षर *name);
पूर्णांक typec_find_port_घातer_role(स्थिर अक्षर *name);
पूर्णांक typec_find_घातer_role(स्थिर अक्षर *name);
पूर्णांक typec_find_port_data_role(स्थिर अक्षर *name);

व्योम typec_partner_set_svdm_version(काष्ठा typec_partner *partner,
				    क्रमागत usb_pd_svdm_ver svdm_version);
पूर्णांक typec_get_negotiated_svdm_version(काष्ठा typec_port *port);

#अगर IS_REACHABLE(CONFIG_TYPEC)
पूर्णांक typec_link_port(काष्ठा device *port);
व्योम typec_unlink_port(काष्ठा device *port);
#अन्यथा
अटल अंतरभूत पूर्णांक typec_link_port(काष्ठा device *port)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम typec_unlink_port(काष्ठा device *port) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_USB_TYPEC_H */
