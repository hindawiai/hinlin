<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_BMP_H__
#घोषणा __NVBIOS_BMP_H__
अटल अंतरभूत u16
bmp_version(काष्ठा nvkm_bios *bios)
अणु
	अगर (bios->bmp_offset) अणु
		वापस nvbios_rd08(bios, bios->bmp_offset + 5) << 8 |
		       nvbios_rd08(bios, bios->bmp_offset + 6);
	पूर्ण

	वापस 0x0000;
पूर्ण

अटल अंतरभूत u16
bmp_mem_init_table(काष्ठा nvkm_bios *bios)
अणु
	अगर (bmp_version(bios) >= 0x0300)
		वापस nvbios_rd16(bios, bios->bmp_offset + 24);
	वापस 0x0000;
पूर्ण

अटल अंतरभूत u16
bmp_sdr_seq_table(काष्ठा nvkm_bios *bios)
अणु
	अगर (bmp_version(bios) >= 0x0300)
		वापस nvbios_rd16(bios, bios->bmp_offset + 26);
	वापस 0x0000;
पूर्ण

अटल अंतरभूत u16
bmp_ddr_seq_table(काष्ठा nvkm_bios *bios)
अणु
	अगर (bmp_version(bios) >= 0x0300)
		वापस nvbios_rd16(bios, bios->bmp_offset + 28);
	वापस 0x0000;
पूर्ण
#पूर्ण_अगर
