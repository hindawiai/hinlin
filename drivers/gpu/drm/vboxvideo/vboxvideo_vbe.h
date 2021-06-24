<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/* Copyright (C) 2006-2016 Oracle Corporation */

#अगर_अघोषित __VBOXVIDEO_VBE_H__
#घोषणा __VBOXVIDEO_VBE_H__

/* GUEST <-> HOST Communication API */

#घोषणा VBE_DISPI_BANK_ADDRESS          0xA0000
#घोषणा VBE_DISPI_BANK_SIZE_KB          64

#घोषणा VBE_DISPI_MAX_XRES              16384
#घोषणा VBE_DISPI_MAX_YRES              16384
#घोषणा VBE_DISPI_MAX_BPP               32

#घोषणा VBE_DISPI_IOPORT_INDEX          0x01CE
#घोषणा VBE_DISPI_IOPORT_DATA           0x01CF

#घोषणा VBE_DISPI_IOPORT_DAC_WRITE_INDEX  0x03C8
#घोषणा VBE_DISPI_IOPORT_DAC_DATA         0x03C9

#घोषणा VBE_DISPI_INDEX_ID              0x0
#घोषणा VBE_DISPI_INDEX_XRES            0x1
#घोषणा VBE_DISPI_INDEX_YRES            0x2
#घोषणा VBE_DISPI_INDEX_BPP             0x3
#घोषणा VBE_DISPI_INDEX_ENABLE          0x4
#घोषणा VBE_DISPI_INDEX_BANK            0x5
#घोषणा VBE_DISPI_INDEX_VIRT_WIDTH      0x6
#घोषणा VBE_DISPI_INDEX_VIRT_HEIGHT     0x7
#घोषणा VBE_DISPI_INDEX_X_OFFSET        0x8
#घोषणा VBE_DISPI_INDEX_Y_OFFSET        0x9
#घोषणा VBE_DISPI_INDEX_VBOX_VIDEO      0xa
#घोषणा VBE_DISPI_INDEX_FB_BASE_HI      0xb

#घोषणा VBE_DISPI_ID0                   0xB0C0
#घोषणा VBE_DISPI_ID1                   0xB0C1
#घोषणा VBE_DISPI_ID2                   0xB0C2
#घोषणा VBE_DISPI_ID3                   0xB0C3
#घोषणा VBE_DISPI_ID4                   0xB0C4

#घोषणा VBE_DISPI_ID_VBOX_VIDEO         0xBE00
/* The VBOX पूर्णांकerface id. Indicates support क्रम VBVA shared memory पूर्णांकerface. */
#घोषणा VBE_DISPI_ID_HGSMI              0xBE01
#घोषणा VBE_DISPI_ID_ANYX               0xBE02

#घोषणा VBE_DISPI_DISABLED              0x00
#घोषणा VBE_DISPI_ENABLED               0x01
#घोषणा VBE_DISPI_GETCAPS               0x02
#घोषणा VBE_DISPI_8BIT_DAC              0x20

#घोषणा VGA_PORT_HGSMI_HOST             0x3b0
#घोषणा VGA_PORT_HGSMI_GUEST            0x3d0

#पूर्ण_अगर
