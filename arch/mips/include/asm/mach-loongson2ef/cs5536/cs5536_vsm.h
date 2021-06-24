<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * the पढ़ो/ग_लिखो पूर्णांकerfaces क्रम Virtual Support Module(VSM)
 *
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin <wuzhangjin@gmail.com>
 */

#अगर_अघोषित _CS5536_VSM_H
#घोषणा _CS5536_VSM_H

#समावेश <linux/types.h>

प्रकार व्योम (*cs5536_pci_vsm_ग_लिखो)(पूर्णांक reg, u32 value);
प्रकार u32 (*cs5536_pci_vsm_पढ़ो)(पूर्णांक reg);

#घोषणा DECLARE_CS5536_MODULE(name) \
बाह्य व्योम pci_##name##_ग_लिखो_reg(पूर्णांक reg, u32 value); \
बाह्य u32 pci_##name##_पढ़ो_reg(पूर्णांक reg);

/* ide module */
DECLARE_CS5536_MODULE(ide)
/* acc module */
DECLARE_CS5536_MODULE(acc)
/* ohci module */
DECLARE_CS5536_MODULE(ohci)
/* isa module */
DECLARE_CS5536_MODULE(isa)
/* ehci module */
DECLARE_CS5536_MODULE(ehci)

#पूर्ण_अगर				/* _CS5536_VSM_H */
