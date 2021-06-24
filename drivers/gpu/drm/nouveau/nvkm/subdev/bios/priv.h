<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_BIOS_PRIV_H__
#घोषणा __NVKM_BIOS_PRIV_H__
#घोषणा nvkm_bios(p) container_of((p), काष्ठा nvkm_bios, subdev)
#समावेश <subdev/मूलप्रण.स>

काष्ठा nvbios_source अणु
	स्थिर अक्षर *name;
	व्योम *(*init)(काष्ठा nvkm_bios *, स्थिर अक्षर *);
	व्योम  (*fini)(व्योम *);
	u32   (*पढ़ो)(व्योम *, u32 offset, u32 length, काष्ठा nvkm_bios *);
	u32   (*size)(व्योम *);
	bool rw;
	bool ignore_checksum;
	bool no_pcir;
	bool require_checksum;
पूर्ण;

पूर्णांक nvbios_extend(काष्ठा nvkm_bios *, u32 length);
पूर्णांक nvbios_shaकरोw(काष्ठा nvkm_bios *);

बाह्य स्थिर काष्ठा nvbios_source nvbios_rom;
बाह्य स्थिर काष्ठा nvbios_source nvbios_ramin;
बाह्य स्थिर काष्ठा nvbios_source nvbios_acpi_fast;
बाह्य स्थिर काष्ठा nvbios_source nvbios_acpi_slow;
बाह्य स्थिर काष्ठा nvbios_source nvbios_pcirom;
बाह्य स्थिर काष्ठा nvbios_source nvbios_platक्रमm;
बाह्य स्थिर काष्ठा nvbios_source nvbios_of;
#पूर्ण_अगर
