<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_VPSTATE_H__
#घोषणा __NVBIOS_VPSTATE_H__
काष्ठा nvbios_vpstate_header अणु
	u32 offset;

	u8 version;
	u8 hlen;
	u8 ecount;
	u8 elen;
	u8 scount;
	u8 slen;

	u8 base_id;
	u8 boost_id;
	u8 tdp_id;
पूर्ण;
काष्ठा nvbios_vpstate_entry अणु
	u8  pstate;
	u16 घड़ी_mhz;
पूर्ण;
पूर्णांक nvbios_vpstate_parse(काष्ठा nvkm_bios *, काष्ठा nvbios_vpstate_header *);
पूर्णांक nvbios_vpstate_entry(काष्ठा nvkm_bios *, काष्ठा nvbios_vpstate_header *,
			 u8 idx, काष्ठा nvbios_vpstate_entry *);
#पूर्ण_अगर
