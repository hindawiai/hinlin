<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/ibm/emac/zmii.h
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller, ZMII bridge support.
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Copyright (c) 2004, 2005 Zultys Technologies.
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *
 * Based on original work by
 *      Armin Kuster <akuster@mvista.com>
 * 	Copyright 2001 MontaVista Softare Inc.
 */
#अगर_अघोषित __IBM_NEWEMAC_ZMII_H
#घोषणा __IBM_NEWEMAC_ZMII_H

/* ZMII bridge रेजिस्टरs */
काष्ठा zmii_regs अणु
	u32 fer;		/* Function enable reg */
	u32 ssr;		/* Speed select reg */
	u32 smiirs;		/* SMII status reg */
पूर्ण;

/* ZMII device */
काष्ठा zmii_instance अणु
	काष्ठा zmii_regs __iomem	*base;

	/* Only one EMAC whacks us at a समय */
	काष्ठा mutex			lock;

	/* subset of PHY_MODE_XXXX */
	पूर्णांक				mode;

	/* number of EMACs using this ZMII bridge */
	पूर्णांक				users;

	/* FER value left by firmware */
	u32				fer_save;

	/* OF device instance */
	काष्ठा platक्रमm_device		*ofdev;
पूर्ण;

#अगर_घोषित CONFIG_IBM_EMAC_ZMII

पूर्णांक zmii_init(व्योम);
व्योम zmii_निकास(व्योम);
पूर्णांक zmii_attach(काष्ठा platक्रमm_device *ofdev, पूर्णांक input,
		phy_पूर्णांकerface_t *mode);
व्योम zmii_detach(काष्ठा platक्रमm_device *ofdev, पूर्णांक input);
व्योम zmii_get_mdio(काष्ठा platक्रमm_device *ofdev, पूर्णांक input);
व्योम zmii_put_mdio(काष्ठा platक्रमm_device *ofdev, पूर्णांक input);
व्योम zmii_set_speed(काष्ठा platक्रमm_device *ofdev, पूर्णांक input, पूर्णांक speed);
पूर्णांक zmii_get_regs_len(काष्ठा platक्रमm_device *ocpdev);
व्योम *zmii_dump_regs(काष्ठा platक्रमm_device *ofdev, व्योम *buf);

#अन्यथा
# define zmii_init()		0
# define zmii_निकास()		करो अणु पूर्ण जबतक(0)
# define zmii_attach(x,y,z)	(-ENXIO)
# define zmii_detach(x,y)	करो अणु पूर्ण जबतक(0)
# define zmii_get_mdio(x,y)	करो अणु पूर्ण जबतक(0)
# define zmii_put_mdio(x,y)	करो अणु पूर्ण जबतक(0)
# define zmii_set_speed(x,y,z)	करो अणु पूर्ण जबतक(0)
# define zmii_get_regs_len(x)	0
# define zmii_dump_regs(x,buf)	(buf)
#पूर्ण_अगर				/* !CONFIG_IBM_EMAC_ZMII */

#पूर्ण_अगर /* __IBM_NEWEMAC_ZMII_H */
