<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MUSB OTG driver रेजिस्टर I/O
 *
 * Copyright 2005 Mentor Graphics Corporation
 * Copyright (C) 2005-2006 by Texas Instruments
 * Copyright (C) 2006-2007 Nokia Corporation
 */

#अगर_अघोषित __MUSB_LINUX_PLATFORM_ARCH_H__
#घोषणा __MUSB_LINUX_PLATFORM_ARCH_H__

#समावेश <linux/पन.स>

#घोषणा musb_ep_select(_mbase, _epnum)	musb->io.ep_select((_mbase), (_epnum))

/**
 * काष्ठा musb_io - IO functions क्रम MUSB
 * @ep_offset:	platक्रमm specअगरic function to get end poपूर्णांक offset
 * @ep_select:	platक्रमm specअगरic function to select end poपूर्णांक
 * @fअगरo_offset: platक्रमm specअगरic function to get fअगरo offset
 * @पढ़ो_fअगरo:	platक्रमm specअगरic function to पढ़ो fअगरo
 * @ग_लिखो_fअगरo:	platक्रमm specअगरic function to ग_लिखो fअगरo
 * @busctl_offset: platक्रमm specअगरic function to get busctl offset
 * @get_toggle: platक्रमm specअगरic function to get toggle
 * @set_toggle: platक्रमm specअगरic function to set toggle
 */
काष्ठा musb_io अणु
	u32	(*ep_offset)(u8 epnum, u16 offset);
	व्योम	(*ep_select)(व्योम __iomem *mbase, u8 epnum);
	u32	(*fअगरo_offset)(u8 epnum);
	व्योम	(*पढ़ो_fअगरo)(काष्ठा musb_hw_ep *hw_ep, u16 len, u8 *buf);
	व्योम	(*ग_लिखो_fअगरo)(काष्ठा musb_hw_ep *hw_ep, u16 len, स्थिर u8 *buf);
	u32	(*busctl_offset)(u8 epnum, u16 offset);
	u16	(*get_toggle)(काष्ठा musb_qh *qh, पूर्णांक is_out);
	u16	(*set_toggle)(काष्ठा musb_qh *qh, पूर्णांक is_out, काष्ठा urb *urb);
पूर्ण;

/* Do not add new entries here, add them the काष्ठा musb_io instead */
बाह्य u8 (*musb_पढ़ोb)(व्योम __iomem *addr, u32 offset);
बाह्य व्योम (*musb_ग_लिखोb)(व्योम __iomem *addr, u32 offset, u8 data);
बाह्य u8 (*musb_clearb)(व्योम __iomem *addr, u32 offset);
बाह्य u16 (*musb_पढ़ोw)(व्योम __iomem *addr, u32 offset);
बाह्य व्योम (*musb_ग_लिखोw)(व्योम __iomem *addr, u32 offset, u16 data);
बाह्य u16 (*musb_clearw)(व्योम __iomem *addr, u32 offset);
बाह्य u32 musb_पढ़ोl(व्योम __iomem *addr, u32 offset);
बाह्य व्योम musb_ग_लिखोl(व्योम __iomem *addr, u32 offset, u32 data);

#पूर्ण_अगर
