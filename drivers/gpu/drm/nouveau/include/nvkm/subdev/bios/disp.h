<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_DISP_H__
#घोषणा __NVBIOS_DISP_H__
u16 nvbios_disp_table(काष्ठा nvkm_bios *,
		      u8 *ver, u8 *hdr, u8 *cnt, u8 *len, u8 *sub);

काष्ठा nvbios_disp अणु
	u16 data;
पूर्ण;

u16 nvbios_disp_entry(काष्ठा nvkm_bios *, u8 idx, u8 *ver, u8 *hdr, u8 *sub);
u16 nvbios_disp_parse(काष्ठा nvkm_bios *, u8 idx, u8 *ver, u8 *hdr, u8 *sub,
		      काष्ठा nvbios_disp *);

काष्ठा nvbios_outp अणु
	u16 type;
	u16 mask;
	u16 script[3];
पूर्ण;

u16 nvbios_outp_entry(काष्ठा nvkm_bios *, u8 idx,
		      u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u16 nvbios_outp_parse(काष्ठा nvkm_bios *, u8 idx,
		      u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_outp *);
u16 nvbios_outp_match(काष्ठा nvkm_bios *, u16 type, u16 mask,
		      u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_outp *);

काष्ठा nvbios_ocfg अणु
	u8  proto;
	u8  flags;
	u16 clkcmp[2];
पूर्ण;

u16 nvbios_ocfg_entry(काष्ठा nvkm_bios *, u16 outp, u8 idx,
		      u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u16 nvbios_ocfg_parse(काष्ठा nvkm_bios *, u16 outp, u8 idx,
		      u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_ocfg *);
u16 nvbios_ocfg_match(काष्ठा nvkm_bios *, u16 outp, u8 proto, u8 flags,
		      u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_ocfg *);
u16 nvbios_oclk_match(काष्ठा nvkm_bios *, u16 cmp, u32 khz);
#पूर्ण_अगर
