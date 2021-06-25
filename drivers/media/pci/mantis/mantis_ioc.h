<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MANTIS_IOC_H
#घोषणा __MANTIS_IOC_H

#घोषणा GPIF_A00		0x00
#घोषणा GPIF_A01		0x01
#घोषणा GPIF_A02		0x02
#घोषणा GPIF_A03		0x03
#घोषणा GPIF_A04		0x04
#घोषणा GPIF_A05		0x05
#घोषणा GPIF_A06		0x06
#घोषणा GPIF_A07		0x07
#घोषणा GPIF_A08		0x08
#घोषणा GPIF_A09		0x09
#घोषणा GPIF_A10		0x0a
#घोषणा GPIF_A11		0x0b

#घोषणा GPIF_A12		0x0c
#घोषणा GPIF_A13		0x0d
#घोषणा GPIF_A14		0x0e

क्रमागत mantis_stream_control अणु
	STREAM_TO_HIF = 0,
	STREAM_TO_CAM
पूर्ण;

बाह्य पूर्णांक mantis_get_mac(काष्ठा mantis_pci *mantis);
बाह्य व्योम mantis_gpio_set_bits(काष्ठा mantis_pci *mantis, u32 bitpos, u8 value);

बाह्य पूर्णांक mantis_stream_control(काष्ठा mantis_pci *mantis, क्रमागत mantis_stream_control stream_ctl);

#पूर्ण_अगर /* __MANTIS_IOC_H */
