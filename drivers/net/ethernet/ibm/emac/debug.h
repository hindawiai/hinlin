<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/ethernet/ibm/emac/debug.h
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller, debug prपूर्णांक routines.
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * Copyright (c) 2004, 2005 Zultys Technologies
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 */
#अगर_अघोषित __IBM_NEWEMAC_DEBUG_H
#घोषणा __IBM_NEWEMAC_DEBUG_H

#समावेश <linux/init.h>

#समावेश "core.h"

#अगर defined(CONFIG_IBM_EMAC_DEBUG)
# define DBG_LEVEL		1
#अन्यथा
# define DBG_LEVEL		0
#पूर्ण_अगर

#घोषणा EMAC_DBG(d, name, fmt, arg...) \
	prपूर्णांकk(KERN_DEBUG #name "%pOF: " fmt, d->ofdev->dev.of_node, ## arg)

#अगर DBG_LEVEL > 0
#  define DBG(d,f,x...)		EMAC_DBG(d, emac, f, ##x)
#  define MAL_DBG(d,f,x...)	EMAC_DBG(d, mal, f, ##x)
#  define ZMII_DBG(d,f,x...)	EMAC_DBG(d, zmii, f, ##x)
#  define RGMII_DBG(d,f,x...)	EMAC_DBG(d, rgmii, f, ##x)
#  define NL			"\n"
#अन्यथा
#  define DBG(f,x...)		((व्योम)0)
#  define MAL_DBG(d,f,x...)	((व्योम)0)
#  define ZMII_DBG(d,f,x...)	((व्योम)0)
#  define RGMII_DBG(d,f,x...)	((व्योम)0)
#पूर्ण_अगर
#अगर DBG_LEVEL > 1
#  define DBG2(d,f,x...) 	DBG(d,f, ##x)
#  define MAL_DBG2(d,f,x...) 	MAL_DBG(d,f, ##x)
#  define ZMII_DBG2(d,f,x...) 	ZMII_DBG(d,f, ##x)
#  define RGMII_DBG2(d,f,x...) 	RGMII_DBG(d,f, ##x)
#अन्यथा
#  define DBG2(f,x...) 		((व्योम)0)
#  define MAL_DBG2(d,f,x...) 	((व्योम)0)
#  define ZMII_DBG2(d,f,x...) 	((व्योम)0)
#  define RGMII_DBG2(d,f,x...) 	((व्योम)0)
#पूर्ण_अगर

#पूर्ण_अगर /* __IBM_NEWEMAC_DEBUG_H */
