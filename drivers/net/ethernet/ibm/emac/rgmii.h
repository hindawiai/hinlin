<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/ibm/emac/rgmii.h
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller, RGMII bridge support.
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Based on ocp_zmii.h/ibm_emac_zmii.h
 * Armin Kuster akuster@mvista.com
 *
 * Copyright 2004 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 *
 * Copyright (c) 2004, 2005 Zultys Technologies.
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 */

#अगर_अघोषित __IBM_NEWEMAC_RGMII_H
#घोषणा __IBM_NEWEMAC_RGMII_H

/* RGMII bridge type */
#घोषणा RGMII_STANDARD		0
#घोषणा RGMII_AXON		1

/* RGMII bridge */
काष्ठा rgmii_regs अणु
	u32 fer;		/* Function enable रेजिस्टर */
	u32 ssr;		/* Speed select रेजिस्टर */
पूर्ण;

/* RGMII device */
काष्ठा rgmii_instance अणु
	काष्ठा rgmii_regs __iomem	*base;

	/* RGMII bridge flags */
	पूर्णांक				flags;
#घोषणा EMAC_RGMII_FLAG_HAS_MDIO	0x00000001

	/* Only one EMAC whacks us at a समय */
	काष्ठा mutex			lock;

	/* number of EMACs using this RGMII bridge */
	पूर्णांक				users;

	/* OF device instance */
	काष्ठा platक्रमm_device		*ofdev;
पूर्ण;

#अगर_घोषित CONFIG_IBM_EMAC_RGMII

पूर्णांक rgmii_init(व्योम);
व्योम rgmii_निकास(व्योम);
पूर्णांक rgmii_attach(काष्ठा platक्रमm_device *ofdev, पूर्णांक input, पूर्णांक mode);
व्योम rgmii_detach(काष्ठा platक्रमm_device *ofdev, पूर्णांक input);
व्योम rgmii_get_mdio(काष्ठा platक्रमm_device *ofdev, पूर्णांक input);
व्योम rgmii_put_mdio(काष्ठा platक्रमm_device *ofdev, पूर्णांक input);
व्योम rgmii_set_speed(काष्ठा platक्रमm_device *ofdev, पूर्णांक input, पूर्णांक speed);
पूर्णांक rgmii_get_regs_len(काष्ठा platक्रमm_device *ofdev);
व्योम *rgmii_dump_regs(काष्ठा platक्रमm_device *ofdev, व्योम *buf);

#अन्यथा

# define rgmii_init()		0
# define rgmii_निकास()		करो अणु पूर्ण जबतक(0)
# define rgmii_attach(x,y,z)	(-ENXIO)
# define rgmii_detach(x,y)	करो अणु पूर्ण जबतक(0)
# define rgmii_get_mdio(o,i)	करो अणु पूर्ण जबतक (0)
# define rgmii_put_mdio(o,i)	करो अणु पूर्ण जबतक (0)
# define rgmii_set_speed(x,y,z)	करो अणु पूर्ण जबतक(0)
# define rgmii_get_regs_len(x)	0
# define rgmii_dump_regs(x,buf)	(buf)
#पूर्ण_अगर				/* !CONFIG_IBM_EMAC_RGMII */

#पूर्ण_अगर /* __IBM_NEWEMAC_RGMII_H */
