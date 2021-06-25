<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_XPIO_H__
#घोषणा __NVBIOS_XPIO_H__

#घोषणा NVBIOS_XPIO_FLAG_AUX  0x10
#घोषणा NVBIOS_XPIO_FLAG_AUX0 0x00
#घोषणा NVBIOS_XPIO_FLAG_AUX1 0x10

काष्ठा nvbios_xpio अणु
	u8 type;
	u8 addr;
	u8 flags;
पूर्ण;

u16 dcb_xpio_table(काष्ठा nvkm_bios *, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u16 dcb_xpio_parse(काष्ठा nvkm_bios *, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_xpio *);
#पूर्ण_अगर
