<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gpio/driver.h>

/**
 * काष्ठा vsc73xx - VSC73xx state container
 */
काष्ठा vsc73xx अणु
	काष्ठा device			*dev;
	काष्ठा gpio_desc		*reset;
	काष्ठा dsa_चयन		*ds;
	काष्ठा gpio_chip		gc;
	u16				chipid;
	u8				addr[ETH_ALEN];
	स्थिर काष्ठा vsc73xx_ops	*ops;
	व्योम				*priv;
पूर्ण;

काष्ठा vsc73xx_ops अणु
	पूर्णांक (*पढ़ो)(काष्ठा vsc73xx *vsc, u8 block, u8 subblock, u8 reg,
		    u32 *val);
	पूर्णांक (*ग_लिखो)(काष्ठा vsc73xx *vsc, u8 block, u8 subblock, u8 reg,
		     u32 val);
पूर्ण;

पूर्णांक vsc73xx_is_addr_valid(u8 block, u8 subblock);
पूर्णांक vsc73xx_probe(काष्ठा vsc73xx *vsc);
पूर्णांक vsc73xx_हटाओ(काष्ठा vsc73xx *vsc);
