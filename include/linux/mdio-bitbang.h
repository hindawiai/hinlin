<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_MDIO_BITBANG_H
#घोषणा __LINUX_MDIO_BITBANG_H

#समावेश <linux/phy.h>

काष्ठा module;

काष्ठा mdiobb_ctrl;

काष्ठा mdiobb_ops अणु
	काष्ठा module *owner;

	/* Set the Management Data Clock high अगर level is one,
	 * low अगर level is zero.
	 */
	व्योम (*set_mdc)(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक level);

	/* Configure the Management Data I/O pin as an input अगर
	 * "output" is zero, or an output अगर "output" is one.
	 */
	व्योम (*set_mdio_dir)(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक output);

	/* Set the Management Data I/O pin high अगर value is one,
	 * low अगर "value" is zero.  This may only be called
	 * when the MDIO pin is configured as an output.
	 */
	व्योम (*set_mdio_data)(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक value);

	/* Retrieve the state Management Data I/O pin. */
	पूर्णांक (*get_mdio_data)(काष्ठा mdiobb_ctrl *ctrl);
पूर्ण;

काष्ठा mdiobb_ctrl अणु
	स्थिर काष्ठा mdiobb_ops *ops;
	अचिन्हित पूर्णांक override_op_c22;
	u8 op_c22_पढ़ो;
	u8 op_c22_ग_लिखो;
पूर्ण;

पूर्णांक mdiobb_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg);
पूर्णांक mdiobb_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg, u16 val);

/* The वापसed bus is not yet रेजिस्टरed with the phy layer. */
काष्ठा mii_bus *alloc_mdio_bitbang(काष्ठा mdiobb_ctrl *ctrl);

/* The bus must alपढ़ोy have been unरेजिस्टरed. */
व्योम मुक्त_mdio_bitbang(काष्ठा mii_bus *bus);

#पूर्ण_अगर
