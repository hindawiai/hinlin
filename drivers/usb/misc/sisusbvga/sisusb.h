<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * sisusb - usb kernel driver क्रम Net2280/SiS315 based USB2VGA करोngles
 *
 * Copyright (C) 2005 by Thomas Winischhofer, Vienna, Austria
 *
 * If distributed as part of the Linux kernel, this code is licensed under the
 * terms of the GPL v2.
 *
 * Otherwise, the following license terms apply:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1) Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2) Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3) The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author:	Thomas Winischhofer <thomas@winischhofer.net>
 *
 */

#अगर_अघोषित _SISUSB_H_
#घोषणा _SISUSB_H_

#समावेश <linux/mutex.h>

/* Version Inक्रमmation */

#घोषणा SISUSB_VERSION		0
#घोषणा SISUSB_REVISION		0
#घोषणा SISUSB_PATCHLEVEL	8

/* Include console and mode चयनing code? */

#समावेश <linux/console.h>
#समावेश <linux/vt_kern.h>
#समावेश "sisusb_struct.h"

/* USB related */

#घोषणा SISUSB_MINOR		133	/* official */

/* Size of the sisusb input/output buffers */
#घोषणा SISUSB_IBUF_SIZE  0x01000
#घोषणा SISUSB_OBUF_SIZE  0x10000	/* fixed */

#घोषणा NUMOBUFS 8		/* max number of output buffers/output URBs */

/* About endianness:
 *
 * 1) I/O ports, PCI config रेजिस्टरs. The पढ़ो/ग_लिखो()
 *    calls emulate inX/outX. Hence, the data is
 *    expected/delivered in machine endiannes by this
 *    driver.
 * 2) Video memory. The data is copied 1:1. There is
 *    no swapping. Ever. This means क्रम userland that
 *    the data has to be prepared properly. (Hपूर्णांक:
 *    think graphics data क्रमmat, command queue,
 *    hardware cursor.)
 * 3) MMIO. Data is copied 1:1. MMIO must be swapped
 *    properly by userland.
 *
 */

#अगर_घोषित __BIG_ENDIAN
#घोषणा SISUSB_CORRECT_ENDIANNESS_PACKET(p)		\
	करो अणु						\
		p->header  = cpu_to_le16(p->header);	\
		p->address = cpu_to_le32(p->address);	\
		p->data    = cpu_to_le32(p->data);	\
	पूर्ण जबतक(0)
#अन्यथा
#घोषणा SISUSB_CORRECT_ENDIANNESS_PACKET(p)
#पूर्ण_अगर

काष्ठा sisusb_usb_data;

काष्ठा sisusb_urb_context अणु	/* urb->context क्रम outbound bulk URBs */
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक urbindex;
	पूर्णांक *actual_length;
पूर्ण;

काष्ठा sisusb_usb_data अणु
	काष्ठा usb_device *sisusb_dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	काष्ठा kref kref;
	रुको_queue_head_t रुको_q;	/* क्रम syncind and समयouts */
	काष्ठा mutex lock;	/* general race aव्योमance */
	अचिन्हित पूर्णांक अगरnum;	/* पूर्णांकerface number of the USB device */
	पूर्णांक minor;		/* minor (क्रम logging clarity) */
	पूर्णांक isखोलो;		/* !=0 अगर खोलो */
	पूर्णांक present;		/* !=0 अगर device is present on the bus */
	पूर्णांक पढ़ोy;		/* !=0 अगर device is पढ़ोy क्रम userland */
	पूर्णांक numobufs;		/* number of obufs = number of out urbs */
	अक्षर *obuf[NUMOBUFS], *ibuf;	/* transfer buffers */
	पूर्णांक obufsize, ibufsize;
	काष्ठा urb *sisurbout[NUMOBUFS];
	काष्ठा urb *sisurbin;
	अचिन्हित अक्षर urbstatus[NUMOBUFS];
	अचिन्हित अक्षर completein;
	काष्ठा sisusb_urb_context urbout_context[NUMOBUFS];
	अचिन्हित दीर्घ flagb0;
	अचिन्हित दीर्घ vrambase;	/* framebuffer base */
	अचिन्हित पूर्णांक vramsize;	/* framebuffer size (bytes) */
	अचिन्हित दीर्घ mmiobase;
	अचिन्हित पूर्णांक mmiosize;
	अचिन्हित दीर्घ ioportbase;
	अचिन्हित अक्षर devinit;	/* device initialized? */
	अचिन्हित अक्षर gfxinit;	/* graphics core initialized? */
	अचिन्हित लघु chipid, chipvenकरोr;
	अचिन्हित लघु chiprevision;
#अगर_घोषित CONFIG_USB_SISUSBVGA_CON
	काष्ठा SiS_Private *SiS_Pr;
	अचिन्हित दीर्घ scrbuf;
	अचिन्हित पूर्णांक scrbuf_size;
	पूर्णांक haveconsole, con_first, con_last;
	पूर्णांक havethisconsole[MAX_NR_CONSOLES];
	पूर्णांक texपंचांगodedestroyed;
	अचिन्हित पूर्णांक sisusb_num_columns;	/* real number, not vt's idea */
	पूर्णांक cur_start_addr, con_rolled_over;
	पूर्णांक sisusb_cursor_loc, bad_cursor_pos;
	पूर्णांक sisusb_cursor_size_from;
	पूर्णांक sisusb_cursor_माप_प्रकारo;
	पूर्णांक current_font_height, current_font_512;
	पूर्णांक font_backup_size, font_backup_height, font_backup_512;
	अक्षर *font_backup;
	पूर्णांक font_slot;
	काष्ठा vc_data *sisusb_display_fg;
	पूर्णांक is_gfx;
	पूर्णांक con_blanked;
#पूर्ण_अगर
पूर्ण;

#घोषणा to_sisusb_dev(d) container_of(d, काष्ठा sisusb_usb_data, kref)

/* USB transport related */

/* urbstatus */
#घोषणा SU_URB_BUSY   1
#घोषणा SU_URB_ALLOC  2

/* Endpoपूर्णांकs */

#घोषणा SISUSB_EP_GFX_IN	0x0e	/* gfx std packet out(0e)/in(8e) */
#घोषणा SISUSB_EP_GFX_OUT	0x0e

#घोषणा SISUSB_EP_GFX_BULK_OUT	0x01	/* gfx mem bulk out/in */
#घोषणा SISUSB_EP_GFX_BULK_IN	0x02	/* ? 2 is "OUT" ? */

#घोषणा SISUSB_EP_GFX_LBULK_OUT	0x03	/* gfx large mem bulk out */

#घोषणा SISUSB_EP_UNKNOWN_04	0x04	/* ? 4 is "OUT" ? - unused */

#घोषणा SISUSB_EP_BRIDGE_IN	0x0d	/* Net2280 out(0d)/in(8d) */
#घोषणा SISUSB_EP_BRIDGE_OUT	0x0d

#घोषणा SISUSB_TYPE_MEM		0
#घोषणा SISUSB_TYPE_IO		1

काष्ठा sisusb_packet अणु
	अचिन्हित लघु header;
	u32 address;
	u32 data;
पूर्ण __attribute__ ((__packed__));

#घोषणा CLEARPACKET(packet) स_रखो(packet, 0, 10)

/* PCI bridge related */

#घोषणा SISUSB_PCI_MEMBASE	0xd0000000
#घोषणा SISUSB_PCI_MMIOBASE	0xe4000000
#घोषणा SISUSB_PCI_IOPORTBASE	0x0000d000

#घोषणा SISUSB_PCI_PSEUDO_MEMBASE	0x10000000
#घोषणा SISUSB_PCI_PSEUDO_MMIOBASE	0x20000000
#घोषणा SISUSB_PCI_PSEUDO_IOPORTBASE	0x0000d000
#घोषणा SISUSB_PCI_PSEUDO_PCIBASE	0x00010000

#घोषणा SISUSB_PCI_MMIOSIZE	(128*1024)
#घोषणा SISUSB_PCI_PCONFSIZE	0x5c

/* graphics core related */

#घोषणा AROFFSET	0x40
#घोषणा ARROFFSET	0x41
#घोषणा GROFFSET	0x4e
#घोषणा SROFFSET	0x44
#घोषणा CROFFSET	0x54
#घोषणा MISCROFFSET	0x4c
#घोषणा MISCWOFFSET	0x42
#घोषणा INPUTSTATOFFSET 0x5A
#घोषणा PART1OFFSET	0x04
#घोषणा PART2OFFSET	0x10
#घोषणा PART3OFFSET	0x12
#घोषणा PART4OFFSET	0x14
#घोषणा PART5OFFSET	0x16
#घोषणा CAPTURखातापूर्णFSET	0x00
#घोषणा VIDEOOFFSET	0x02
#घोषणा COLREGOFFSET	0x48
#घोषणा PELMASKOFFSET	0x46
#घोषणा VGAENABLE	0x43

#घोषणा SISAR		SISUSB_PCI_IOPORTBASE + AROFFSET
#घोषणा SISARR		SISUSB_PCI_IOPORTBASE + ARROFFSET
#घोषणा SISGR		SISUSB_PCI_IOPORTBASE + GROFFSET
#घोषणा SISSR		SISUSB_PCI_IOPORTBASE + SROFFSET
#घोषणा SISCR		SISUSB_PCI_IOPORTBASE + CROFFSET
#घोषणा SISMISCR	SISUSB_PCI_IOPORTBASE + MISCROFFSET
#घोषणा SISMISCW	SISUSB_PCI_IOPORTBASE + MISCWOFFSET
#घोषणा SISINPSTAT	SISUSB_PCI_IOPORTBASE + INPUTSTATOFFSET
#घोषणा SISPART1	SISUSB_PCI_IOPORTBASE + PART1OFFSET
#घोषणा SISPART2	SISUSB_PCI_IOPORTBASE + PART2OFFSET
#घोषणा SISPART3	SISUSB_PCI_IOPORTBASE + PART3OFFSET
#घोषणा SISPART4	SISUSB_PCI_IOPORTBASE + PART4OFFSET
#घोषणा SISPART5	SISUSB_PCI_IOPORTBASE + PART5OFFSET
#घोषणा SISCAP		SISUSB_PCI_IOPORTBASE + CAPTURखातापूर्णFSET
#घोषणा SISVID		SISUSB_PCI_IOPORTBASE + VIDEOOFFSET
#घोषणा SISCOLIDXR	SISUSB_PCI_IOPORTBASE + COLREGOFFSET - 1
#घोषणा SISCOLIDX	SISUSB_PCI_IOPORTBASE + COLREGOFFSET
#घोषणा SISCOLDATA	SISUSB_PCI_IOPORTBASE + COLREGOFFSET + 1
#घोषणा SISCOL2IDX	SISPART5
#घोषणा SISCOL2DATA	SISPART5 + 1
#घोषणा SISPEL		SISUSB_PCI_IOPORTBASE + PELMASKOFFSET
#घोषणा SISVGAEN	SISUSB_PCI_IOPORTBASE + VGAENABLE
#घोषणा SISDACA		SISCOLIDX
#घोषणा SISDACD		SISCOLDATA

/* ioctl related */

/* Structure argument क्रम SISUSB_GET_INFO ioctl  */
काष्ठा sisusb_info अणु
	__u32 sisusb_id;	/* क्रम identअगरying sisusb */
#घोषणा SISUSB_ID  0x53495355	/* Identअगरy myself with 'SISU' */
	__u8 sisusb_version;
	__u8 sisusb_revision;
	__u8 sisusb_patchlevel;
	__u8 sisusb_gfxinit;	/* graphics core initialized? */

	__u32 sisusb_vrambase;
	__u32 sisusb_mmiobase;
	__u32 sisusb_iobase;
	__u32 sisusb_pcibase;

	__u32 sisusb_vramsize;	/* framebuffer size in bytes */

	__u32 sisusb_minor;

	__u32 sisusb_fbdevactive;	/* != 0 अगर framebuffer device active */

	__u32 sisusb_conactive;	/* != 0 अगर console driver active */

	__u8 sisusb_reserved[28];	/* क्रम future use */
पूर्ण;

काष्ठा sisusb_command अणु
	__u8 operation;		/* see below */
	__u8 data0;		/* operation dependent */
	__u8 data1;		/* operation dependent */
	__u8 data2;		/* operation dependent */
	__u32 data3;		/* operation dependent */
	__u32 data4;		/* क्रम future use */
पूर्ण;

#घोषणा SUCMD_GET	0x01	/* क्रम all: data0 = index, data3 = port */
#घोषणा SUCMD_SET	0x02	/* data1 = value */
#घोषणा SUCMD_SETOR	0x03	/* data1 = or */
#घोषणा SUCMD_SETAND	0x04	/* data1 = and */
#घोषणा SUCMD_SETANDOR	0x05	/* data1 = and, data2 = or */
#घोषणा SUCMD_SETMASK	0x06	/* data1 = data, data2 = mask */

#घोषणा SUCMD_CLRSCR	0x07	/* data0:1:2 = length, data3 = address */

#घोषणा SUCMD_HANDLETEXTMODE 0x08	/* Reset/destroy text mode */

#घोषणा SUCMD_SETMODE	0x09	/* Set a display mode (data3 = SiS mode) */
#घोषणा SUCMD_SETVESAMODE 0x0a	/* Set a display mode (data3 = VESA mode) */

#घोषणा SISUSB_COMMAND		_IOWR(0xF3,0x3D,काष्ठा sisusb_command)
#घोषणा SISUSB_GET_CONFIG_SIZE	_IOR(0xF3,0x3E,__u32)
#घोषणा SISUSB_GET_CONFIG	_IOR(0xF3,0x3F,काष्ठा sisusb_info)

#पूर्ण_अगर /* SISUSB_H */
