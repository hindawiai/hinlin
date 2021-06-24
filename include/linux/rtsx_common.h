<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Driver क्रम Realtek driver-based card पढ़ोer
 *
 * Copyright(c) 2009-2013 Realtek Semiconductor Corp. All rights reserved.
 *
 * Author:
 *   Wei WANG <wei_wang@realsil.com.cn>
 */

#अगर_अघोषित __RTSX_COMMON_H
#घोषणा __RTSX_COMMON_H

#घोषणा DRV_NAME_RTSX_PCI		"rtsx_pci"
#घोषणा DRV_NAME_RTSX_PCI_SDMMC		"rtsx_pci_sdmmc"
#घोषणा DRV_NAME_RTSX_PCI_MS		"rtsx_pci_ms"

#घोषणा RTSX_REG_PAIR(addr, val)	(((u32)(addr) << 16) | (u8)(val))

#घोषणा RTSX_SSC_DEPTH_4M		0x01
#घोषणा RTSX_SSC_DEPTH_2M		0x02
#घोषणा RTSX_SSC_DEPTH_1M		0x03
#घोषणा RTSX_SSC_DEPTH_500K		0x04
#घोषणा RTSX_SSC_DEPTH_250K		0x05

#घोषणा RTSX_SD_CARD			0
#घोषणा RTSX_MS_CARD			1

#घोषणा CLK_TO_DIV_N			0
#घोषणा DIV_N_TO_CLK			1

काष्ठा platक्रमm_device;

काष्ठा rtsx_slot अणु
	काष्ठा platक्रमm_device	*p_dev;
	व्योम			(*card_event)(काष्ठा platक्रमm_device *p_dev);
पूर्ण;

#पूर्ण_अगर
