<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/ibm/emac/tah.h
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller, TAH support.
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Copyright 2004 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 *
 * Copyright (c) 2005 Eugene Surovegin <ebs@ebshome.net>
 */

#अगर_अघोषित __IBM_NEWEMAC_TAH_H
#घोषणा __IBM_NEWEMAC_TAH_H

/* TAH */
काष्ठा tah_regs अणु
	u32 revid;
	u32 pad[3];
	u32 mr;
	u32 ssr0;
	u32 ssr1;
	u32 ssr2;
	u32 ssr3;
	u32 ssr4;
	u32 ssr5;
	u32 tsr;
पूर्ण;


/* TAH device */
काष्ठा tah_instance अणु
	काष्ठा tah_regs __iomem		*base;

	/* Only one EMAC whacks us at a समय */
	काष्ठा mutex			lock;

	/* number of EMACs using this TAH */
	पूर्णांक				users;

	/* OF device instance */
	काष्ठा platक्रमm_device		*ofdev;
पूर्ण;


/* TAH engine */
#घोषणा TAH_MR_CVR		0x80000000
#घोषणा TAH_MR_SR		0x40000000
#घोषणा TAH_MR_ST_256		0x01000000
#घोषणा TAH_MR_ST_512		0x02000000
#घोषणा TAH_MR_ST_768		0x03000000
#घोषणा TAH_MR_ST_1024		0x04000000
#घोषणा TAH_MR_ST_1280		0x05000000
#घोषणा TAH_MR_ST_1536		0x06000000
#घोषणा TAH_MR_TFS_16KB		0x00000000
#घोषणा TAH_MR_TFS_2KB		0x00200000
#घोषणा TAH_MR_TFS_4KB		0x00400000
#घोषणा TAH_MR_TFS_6KB		0x00600000
#घोषणा TAH_MR_TFS_8KB		0x00800000
#घोषणा TAH_MR_TFS_10KB		0x00a00000
#घोषणा TAH_MR_DTFP		0x00100000
#घोषणा TAH_MR_DIG		0x00080000

#अगर_घोषित CONFIG_IBM_EMAC_TAH

पूर्णांक tah_init(व्योम);
व्योम tah_निकास(व्योम);
पूर्णांक tah_attach(काष्ठा platक्रमm_device *ofdev, पूर्णांक channel);
व्योम tah_detach(काष्ठा platक्रमm_device *ofdev, पूर्णांक channel);
व्योम tah_reset(काष्ठा platक्रमm_device *ofdev);
पूर्णांक tah_get_regs_len(काष्ठा platक्रमm_device *ofdev);
व्योम *tah_dump_regs(काष्ठा platक्रमm_device *ofdev, व्योम *buf);

#अन्यथा

# define tah_init()		0
# define tah_निकास()		करो अणु पूर्ण जबतक(0)
# define tah_attach(x,y)	(-ENXIO)
# define tah_detach(x,y)	करो अणु पूर्ण जबतक(0)
# define tah_reset(x)		करो अणु पूर्ण जबतक(0)
# define tah_get_regs_len(x)	0
# define tah_dump_regs(x,buf)	(buf)

#पूर्ण_अगर				/* !CONFIG_IBM_EMAC_TAH */

#पूर्ण_अगर /* __IBM_NEWEMAC_TAH_H */
