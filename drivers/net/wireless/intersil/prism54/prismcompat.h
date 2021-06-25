<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  (C) 2004 Margit Schubert-While <margitsw@t-online.de>
 */

/*
 *	Compatibility header file to aid support of dअगरferent kernel versions
 */

#अगर_घोषित PRISM54_COMPAT24
#समावेश "prismcompat24.h"
#अन्यथा	/* PRISM54_COMPAT24 */

#अगर_अघोषित _PRISM_COMPAT_H
#घोषणा _PRISM_COMPAT_H

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/compiler.h>

#अगर_अघोषित __iomem
#घोषणा __iomem
#पूर्ण_अगर

#घोषणा PRISM_FW_PDEV		&priv->pdev->dev

#पूर्ण_अगर				/* _PRISM_COMPAT_H */
#पूर्ण_अगर				/* PRISM54_COMPAT24 */
