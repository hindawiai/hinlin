<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_DP_H__
#घोषणा __NVBIOS_DP_H__

u16
nvbios_dp_table(काष्ठा nvkm_bios *bios, u8 *ver, u8 *hdr, u8 *cnt, u8 *len);

काष्ठा nvbios_dpout अणु
	u16 type;
	u16 mask;
	u8  flags;
	u32 script[5];
	u32 lnkcmp;
पूर्ण;

u16 nvbios_dpout_parse(काष्ठा nvkm_bios *, u8 idx,
		       u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		       काष्ठा nvbios_dpout *);
u16 nvbios_dpout_match(काष्ठा nvkm_bios *, u16 type, u16 mask,
		       u8 *ver, u8 *hdr, u8 *cnt, u8 *len,
		       काष्ठा nvbios_dpout *);

काष्ठा nvbios_dpcfg अणु
	u8 pc;
	u8 dc;
	u8 pe;
	u8 tx_pu;
पूर्ण;

u16
nvbios_dpcfg_parse(काष्ठा nvkm_bios *, u16 outp, u8 idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_dpcfg *);
u16
nvbios_dpcfg_match(काष्ठा nvkm_bios *, u16 outp, u8 pc, u8 vs, u8 pe,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len, काष्ठा nvbios_dpcfg *);
#पूर्ण_अगर
