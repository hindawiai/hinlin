<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_POWER_BUDGET_H__
#घोषणा __NVBIOS_POWER_BUDGET_H__

#समावेश <nvkm/subdev/मूलप्रण.स>

काष्ठा nvbios_घातer_budget_entry अणु
	u32 min_w;
	u32 avg_w;
	u32 max_w;
पूर्ण;

काष्ठा nvbios_घातer_budget अणु
	u32 offset;
	u8  ver;
	u8  hlen;
	u8  elen;
	u8  ecount;
	u8  cap_entry;
पूर्ण;

पूर्णांक nvbios_घातer_budget_header(काष्ठा nvkm_bios *,
                               काष्ठा nvbios_घातer_budget *);
पूर्णांक nvbios_घातer_budget_entry(काष्ठा nvkm_bios *, काष्ठा nvbios_घातer_budget *,
                              u8 idx, काष्ठा nvbios_घातer_budget_entry *);

#पूर्ण_अगर
