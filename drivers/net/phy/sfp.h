<शैली गुरु>
#अगर_अघोषित SFP_H
#घोषणा SFP_H

#समावेश <linux/ethtool.h>
#समावेश <linux/sfp.h>

काष्ठा sfp;

काष्ठा sfp_socket_ops अणु
	व्योम (*attach)(काष्ठा sfp *sfp);
	व्योम (*detach)(काष्ठा sfp *sfp);
	व्योम (*start)(काष्ठा sfp *sfp);
	व्योम (*stop)(काष्ठा sfp *sfp);
	पूर्णांक (*module_info)(काष्ठा sfp *sfp, काष्ठा ethtool_modinfo *modinfo);
	पूर्णांक (*module_eeprom)(काष्ठा sfp *sfp, काष्ठा ethtool_eeprom *ee,
			     u8 *data);
	पूर्णांक (*module_eeprom_by_page)(काष्ठा sfp *sfp,
				     स्थिर काष्ठा ethtool_module_eeprom *page,
				     काष्ठा netlink_ext_ack *extack);
पूर्ण;

पूर्णांक sfp_add_phy(काष्ठा sfp_bus *bus, काष्ठा phy_device *phydev);
व्योम sfp_हटाओ_phy(काष्ठा sfp_bus *bus);
व्योम sfp_link_up(काष्ठा sfp_bus *bus);
व्योम sfp_link_करोwn(काष्ठा sfp_bus *bus);
पूर्णांक sfp_module_insert(काष्ठा sfp_bus *bus, स्थिर काष्ठा sfp_eeprom_id *id);
व्योम sfp_module_हटाओ(काष्ठा sfp_bus *bus);
पूर्णांक sfp_module_start(काष्ठा sfp_bus *bus);
व्योम sfp_module_stop(काष्ठा sfp_bus *bus);
पूर्णांक sfp_link_configure(काष्ठा sfp_bus *bus, स्थिर काष्ठा sfp_eeprom_id *id);
काष्ठा sfp_bus *sfp_रेजिस्टर_socket(काष्ठा device *dev, काष्ठा sfp *sfp,
				    स्थिर काष्ठा sfp_socket_ops *ops);
व्योम sfp_unरेजिस्टर_socket(काष्ठा sfp_bus *bus);

#पूर्ण_अगर
