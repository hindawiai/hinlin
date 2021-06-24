<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __USB_TYPEC_CLASS__
#घोषणा __USB_TYPEC_CLASS__

#समावेश <linux/device.h>
#समावेश <linux/usb/typec.h>

काष्ठा typec_mux;
काष्ठा typec_चयन;

काष्ठा typec_plug अणु
	काष्ठा device			dev;
	क्रमागत typec_plug_index		index;
	काष्ठा ida			mode_ids;
	पूर्णांक				num_alपंचांगodes;
पूर्ण;

काष्ठा typec_cable अणु
	काष्ठा device			dev;
	क्रमागत typec_plug_type		type;
	काष्ठा usb_pd_identity		*identity;
	अचिन्हित पूर्णांक			active:1;
	u16				pd_revision; /* 0300H = "3.0" */
पूर्ण;

काष्ठा typec_partner अणु
	काष्ठा device			dev;
	अचिन्हित पूर्णांक			usb_pd:1;
	काष्ठा usb_pd_identity		*identity;
	क्रमागत typec_accessory		accessory;
	काष्ठा ida			mode_ids;
	पूर्णांक				num_alपंचांगodes;
	u16				pd_revision; /* 0300H = "3.0" */
	क्रमागत usb_pd_svdm_ver		svdm_version;
पूर्ण;

काष्ठा typec_port अणु
	अचिन्हित पूर्णांक			id;
	काष्ठा device			dev;
	काष्ठा ida			mode_ids;

	पूर्णांक				prefer_role;
	क्रमागत typec_data_role		data_role;
	क्रमागत typec_role			pwr_role;
	क्रमागत typec_role			vconn_role;
	क्रमागत typec_pwr_opmode		pwr_opmode;
	क्रमागत typec_port_type		port_type;
	काष्ठा mutex			port_type_lock;

	क्रमागत typec_orientation		orientation;
	काष्ठा typec_चयन		*sw;
	काष्ठा typec_mux		*mux;

	स्थिर काष्ठा typec_capability	*cap;
	स्थिर काष्ठा typec_operations   *ops;

	काष्ठा list_head		port_list;
	काष्ठा mutex			port_list_lock; /* Port list lock */

	व्योम				*pld;
पूर्ण;

#घोषणा to_typec_port(_dev_) container_of(_dev_, काष्ठा typec_port, dev)
#घोषणा to_typec_plug(_dev_) container_of(_dev_, काष्ठा typec_plug, dev)
#घोषणा to_typec_cable(_dev_) container_of(_dev_, काष्ठा typec_cable, dev)
#घोषणा to_typec_partner(_dev_) container_of(_dev_, काष्ठा typec_partner, dev)

बाह्य स्थिर काष्ठा device_type typec_partner_dev_type;
बाह्य स्थिर काष्ठा device_type typec_cable_dev_type;
बाह्य स्थिर काष्ठा device_type typec_plug_dev_type;
बाह्य स्थिर काष्ठा device_type typec_port_dev_type;

#घोषणा is_typec_partner(dev) ((dev)->type == &typec_partner_dev_type)
#घोषणा is_typec_cable(dev) ((dev)->type == &typec_cable_dev_type)
#घोषणा is_typec_plug(dev) ((dev)->type == &typec_plug_dev_type)
#घोषणा is_typec_port(dev) ((dev)->type == &typec_port_dev_type)

बाह्य काष्ठा class typec_mux_class;
बाह्य काष्ठा class typec_class;

पूर्णांक typec_link_ports(काष्ठा typec_port *connector);
व्योम typec_unlink_ports(काष्ठा typec_port *connector);

#पूर्ण_अगर /* __USB_TYPEC_CLASS__ */
