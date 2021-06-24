<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DSA_MV88E6XXX_H
#घोषणा __DSA_MV88E6XXX_H

#समावेश <linux/platक्रमm_data/dsa.h>

काष्ठा dsa_mv88e6xxx_pdata अणु
	/* Must be first, such that dsa_रेजिस्टर_चयन() can access this
	 * without gory poपूर्णांकer manipulations
	 */
	काष्ठा dsa_chip_data cd;
	स्थिर अक्षर *compatible;
	अचिन्हित पूर्णांक enabled_ports;
	काष्ठा net_device *netdev;
	u32 eeprom_len;
	पूर्णांक irq;
पूर्ण;

#पूर्ण_अगर
