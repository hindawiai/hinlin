<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __GENWQE_DRIVER_H__
#घोषणा __GENWQE_DRIVER_H__

/**
 * IBM Accelerator Family 'GenWQE'
 *
 * (C) Copyright IBM Corp. 2013
 *
 * Author: Frank Haverkamp <haver@linux.vnet.ibm.com>
 * Author: Joerg-Stephan Vogt <jsvogt@de.ibm.com>
 * Author: Michael Jung <mijung@gmx.net>
 * Author: Michael Ruettger <michael@ibmra.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/cdev.h>
#समावेश <linux/list.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/iommu.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/genwqe/genwqe_card.h>

#घोषणा DRV_VERSION		"2.0.25"

/*
 * Static minor number assignement, until we decide/implement
 * something dynamic.
 */
#घोषणा GENWQE_MAX_MINOR	128 /* up to 128 possible genwqe devices */

/**
 * genwqe_requ_alloc() - Allocate a new DDCB execution request
 *
 * This data काष्ठाure contains the user visiable fields of the DDCB
 * to be executed.
 *
 * Return: ptr to genwqe_ddcb_cmd data काष्ठाure
 */
काष्ठा genwqe_ddcb_cmd *ddcb_requ_alloc(व्योम);

/**
 * ddcb_requ_मुक्त() - Free DDCB execution request.
 * @req:       ptr to genwqe_ddcb_cmd data काष्ठाure.
 */
व्योम ddcb_requ_मुक्त(काष्ठा genwqe_ddcb_cmd *req);

u32  genwqe_crc32(u8 *buff, माप_प्रकार len, u32 init);

अटल अंतरभूत व्योम genwqe_hexdump(काष्ठा pci_dev *pci_dev,
				  स्थिर व्योम *buff, अचिन्हित पूर्णांक size)
अणु
	अक्षर prefix[32];

	scnम_लिखो(prefix, माप(prefix), "%s %s: ",
		  GENWQE_DEVNAME, pci_name(pci_dev));

	prपूर्णांक_hex_dump_debug(prefix, DUMP_PREFIX_OFFSET, 16, 1, buff,
			     size, true);
पूर्ण

#पूर्ण_अगर	/* __GENWQE_DRIVER_H__ */
