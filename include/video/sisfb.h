<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * sisfb.h - definitions क्रम the SiS framebuffer driver
 *
 * Copyright (C) 2001-2005 by Thomas Winischhofer, Vienna, Austria.
 */
#अगर_अघोषित _LINUX_SISFB_H_
#घोषणा _LINUX_SISFB_H_


#समावेश <linux/pci.h>
#समावेश <uapi/video/sisfb.h>

#घोषणा	UNKNOWN_VGA  0
#घोषणा	SIS_300_VGA  1
#घोषणा	SIS_315_VGA  2

#घोषणा SISFB_HAVE_MALLOC_NEW
बाह्य व्योम sis_दो_स्मृति(काष्ठा sis_memreq *req);
बाह्य व्योम sis_दो_स्मृति_new(काष्ठा pci_dev *pdev, काष्ठा sis_memreq *req);

बाह्य व्योम sis_मुक्त(u32 base);
बाह्य व्योम sis_मुक्त_new(काष्ठा pci_dev *pdev, u32 base);
#पूर्ण_अगर
