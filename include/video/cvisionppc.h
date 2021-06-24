<शैली गुरु>
/*
 * Phase5 CybervisionPPC (TVP4020) definitions क्रम the Permedia2 framebuffer
 * driver.
 *
 * Copyright (c) 1998-1999 Ilario Nardinocchi (nardinoc@CS.UniBO.IT)
 * --------------------------------------------------------------------------
 * $Id: cvisionppc.h,v 1.8 1999/01/28 13:18:07 illo Exp $
 * --------------------------------------------------------------------------
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित CVISIONPPC_H
#घोषणा CVISIONPPC_H

#अगर_अघोषित PM2FB_H
#समावेश "pm2fb.h"
#पूर्ण_अगर

काष्ठा cvppc_par अणु
	अचिन्हित अक्षर* pci_config;
	अचिन्हित अक्षर* pci_bridge;
	u32 user_flags;
पूर्ण;

#घोषणा CSPPC_PCI_BRIDGE		0xfffe0000
#घोषणा CSPPC_BRIDGE_ENDIAN		0x0000
#घोषणा CSPPC_BRIDGE_INT		0x0010

#घोषणा	CVPPC_PCI_CONFIG		0xfffc0000
#घोषणा CVPPC_ROM_ADDRESS		0xe2000001
#घोषणा CVPPC_REGS_REGION		0xef000000
#घोषणा CVPPC_FB_APERTURE_ONE		0xe0000000
#घोषणा CVPPC_FB_APERTURE_TWO		0xe1000000
#घोषणा CVPPC_FB_SIZE			0x00800000
#घोषणा CVPPC_MEM_CONFIG_OLD		0xed61fcaa	/* FIXME Fujitsu?? */
#घोषणा CVPPC_MEM_CONFIG_NEW		0xed41c532	/* FIXME USA?? */
#घोषणा CVPPC_MEMCLOCK			83000		/* in KHz */

/* CVPPC_BRIDGE_ENDIAN */
#घोषणा CSPPCF_BRIDGE_BIG_ENDIAN	0x02

/* CVPPC_BRIDGE_INT */
#घोषणा CSPPCF_BRIDGE_ACTIVE_INT2	0x01

#पूर्ण_अगर	/* CVISIONPPC_H */

/*****************************************************************************
 * That's all folks!
 *****************************************************************************/
