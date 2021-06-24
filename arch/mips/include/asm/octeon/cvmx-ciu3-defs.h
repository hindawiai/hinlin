<शैली गुरु>
/*
 * Copyright (c) 2003-2016 Cavium Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 */

#अगर_अघोषित __CVMX_CIU3_DEFS_H__
#घोषणा __CVMX_CIU3_DEFS_H__

#घोषणा CVMX_CIU3_FUSE CVMX_ADD_IO_SEG(0x00010100000001A0ull)
#घोषणा CVMX_CIU3_BIST CVMX_ADD_IO_SEG(0x00010100000001C0ull)
#घोषणा CVMX_CIU3_CONST CVMX_ADD_IO_SEG(0x0001010000000220ull)
#घोषणा CVMX_CIU3_CTL CVMX_ADD_IO_SEG(0x00010100000000E0ull)
#घोषणा CVMX_CIU3_DESTX_IO_INT(offset) (CVMX_ADD_IO_SEG(0x0001010000210000ull) + ((offset) & 7) * 8)
#घोषणा CVMX_CIU3_DESTX_PP_INT(offset) (CVMX_ADD_IO_SEG(0x0001010000200000ull) + ((offset) & 255) * 8)
#घोषणा CVMX_CIU3_GSTOP CVMX_ADD_IO_SEG(0x0001010000000140ull)
#घोषणा CVMX_CIU3_IDTX_CTL(offset) (CVMX_ADD_IO_SEG(0x0001010000110000ull) + ((offset) & 255) * 8)
#घोषणा CVMX_CIU3_IDTX_IO(offset) (CVMX_ADD_IO_SEG(0x0001010000130000ull) + ((offset) & 255) * 8)
#घोषणा CVMX_CIU3_IDTX_PPX(offset, block_id) (CVMX_ADD_IO_SEG(0x0001010000120000ull) + ((block_id) & 255) * 0x20ull)
#घोषणा CVMX_CIU3_INTR_RAM_ECC_CTL CVMX_ADD_IO_SEG(0x0001010000000260ull)
#घोषणा CVMX_CIU3_INTR_RAM_ECC_ST CVMX_ADD_IO_SEG(0x0001010000000280ull)
#घोषणा CVMX_CIU3_INTR_READY CVMX_ADD_IO_SEG(0x00010100000002A0ull)
#घोषणा CVMX_CIU3_INTR_SLOWDOWN CVMX_ADD_IO_SEG(0x0001010000000240ull)
#घोषणा CVMX_CIU3_ISCX_CTL(offset) (CVMX_ADD_IO_SEG(0x0001010080000000ull) + ((offset) & 1048575) * 8)
#घोषणा CVMX_CIU3_ISCX_W1C(offset) (CVMX_ADD_IO_SEG(0x0001010090000000ull) + ((offset) & 1048575) * 8)
#घोषणा CVMX_CIU3_ISCX_W1S(offset) (CVMX_ADD_IO_SEG(0x00010100A0000000ull) + ((offset) & 1048575) * 8)
#घोषणा CVMX_CIU3_NMI CVMX_ADD_IO_SEG(0x0001010000000160ull)
#घोषणा CVMX_CIU3_SISCX(offset) (CVMX_ADD_IO_SEG(0x0001010000220000ull) + ((offset) & 255) * 8)
#घोषणा CVMX_CIU3_TIMX(offset) (CVMX_ADD_IO_SEG(0x0001010000010000ull) + ((offset) & 15) * 8)

जोड़ cvmx_ciu3_bist अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_bist_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_9_63                : 55;
	uपूर्णांक64_t bist                         : 9;
#अन्यथा
	uपूर्णांक64_t bist                         : 9;
	uपूर्णांक64_t reserved_9_63                : 55;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_स्थिर अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_स्थिर_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t dests_io                     : 16;
	uपूर्णांक64_t pपूर्णांकsn                       : 16;
	uपूर्णांक64_t dests_pp                     : 16;
	uपूर्णांक64_t idt                          : 16;
#अन्यथा
	uपूर्णांक64_t idt                          : 16;
	uपूर्णांक64_t dests_pp                     : 16;
	uपूर्णांक64_t pपूर्णांकsn                       : 16;
	uपूर्णांक64_t dests_io                     : 16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_5_63                : 59;
	uपूर्णांक64_t mcd_sel                      : 2;
	uपूर्णांक64_t iscmem_le                    : 1;
	uपूर्णांक64_t seq_dis                      : 1;
	uपूर्णांक64_t cclk_dis                     : 1;
#अन्यथा
	uपूर्णांक64_t cclk_dis                     : 1;
	uपूर्णांक64_t seq_dis                      : 1;
	uपूर्णांक64_t iscmem_le                    : 1;
	uपूर्णांक64_t mcd_sel                      : 2;
	uपूर्णांक64_t reserved_5_63                : 59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_destx_io_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_destx_io_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_52_63               : 12;
	uपूर्णांक64_t पूर्णांकsn                        : 20;
	uपूर्णांक64_t reserved_10_31               : 22;
	uपूर्णांक64_t पूर्णांकidt                       : 8;
	uपूर्णांक64_t newपूर्णांक                       : 1;
	uपूर्णांक64_t पूर्णांकr                         : 1;
#अन्यथा
	uपूर्णांक64_t पूर्णांकr                         : 1;
	uपूर्णांक64_t newपूर्णांक                       : 1;
	uपूर्णांक64_t पूर्णांकidt                       : 8;
	uपूर्णांक64_t reserved_10_31               : 22;
	uपूर्णांक64_t पूर्णांकsn                        : 20;
	uपूर्णांक64_t reserved_52_63               : 12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_destx_pp_पूर्णांक अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_destx_pp_पूर्णांक_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_52_63               : 12;
	uपूर्णांक64_t पूर्णांकsn                        : 20;
	uपूर्णांक64_t reserved_10_31               : 22;
	uपूर्णांक64_t पूर्णांकidt                       : 8;
	uपूर्णांक64_t newपूर्णांक                       : 1;
	uपूर्णांक64_t पूर्णांकr                         : 1;
#अन्यथा
	uपूर्णांक64_t पूर्णांकr                         : 1;
	uपूर्णांक64_t newपूर्णांक                       : 1;
	uपूर्णांक64_t पूर्णांकidt                       : 8;
	uपूर्णांक64_t reserved_10_31               : 22;
	uपूर्णांक64_t पूर्णांकsn                        : 20;
	uपूर्णांक64_t reserved_52_63               : 12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_gstop अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_gstop_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_1_63                : 63;
	uपूर्णांक64_t gstop                        : 1;
#अन्यथा
	uपूर्णांक64_t gstop                        : 1;
	uपूर्णांक64_t reserved_1_63                : 63;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_idtx_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_idtx_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_52_63               : 12;
	uपूर्णांक64_t पूर्णांकsn                        : 20;
	uपूर्णांक64_t reserved_4_31                : 28;
	uपूर्णांक64_t पूर्णांकr                         : 1;
	uपूर्णांक64_t newपूर्णांक                       : 1;
	uपूर्णांक64_t ip_num                       : 2;
#अन्यथा
	uपूर्णांक64_t ip_num                       : 2;
	uपूर्णांक64_t newपूर्णांक                       : 1;
	uपूर्णांक64_t पूर्णांकr                         : 1;
	uपूर्णांक64_t reserved_4_31                : 28;
	uपूर्णांक64_t पूर्णांकsn                        : 20;
	uपूर्णांक64_t reserved_52_63               : 12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_idtx_io अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_idtx_io_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_5_63                : 59;
	uपूर्णांक64_t io                           : 5;
#अन्यथा
	uपूर्णांक64_t io                           : 5;
	uपूर्णांक64_t reserved_5_63                : 59;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_idtx_ppx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_idtx_ppx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_48_63               : 16;
	uपूर्णांक64_t pp                           : 48;
#अन्यथा
	uपूर्णांक64_t pp                           : 48;
	uपूर्णांक64_t reserved_48_63               : 16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_पूर्णांकr_ram_ecc_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_पूर्णांकr_ram_ecc_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_3_63                : 61;
	uपूर्णांक64_t flip_synd                    : 2;
	uपूर्णांक64_t ecc_ena                      : 1;
#अन्यथा
	uपूर्णांक64_t ecc_ena                      : 1;
	uपूर्णांक64_t flip_synd                    : 2;
	uपूर्णांक64_t reserved_3_63                : 61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_पूर्णांकr_ram_ecc_st अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_पूर्णांकr_ram_ecc_st_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_52_63               : 12;
	uपूर्णांक64_t addr                         : 20;
	uपूर्णांक64_t reserved_6_31                : 26;
	uपूर्णांक64_t sisc_dbe                     : 1;
	uपूर्णांक64_t sisc_sbe                     : 1;
	uपूर्णांक64_t idt_dbe                      : 1;
	uपूर्णांक64_t idt_sbe                      : 1;
	uपूर्णांक64_t isc_dbe                      : 1;
	uपूर्णांक64_t isc_sbe                      : 1;
#अन्यथा
	uपूर्णांक64_t isc_sbe                      : 1;
	uपूर्णांक64_t isc_dbe                      : 1;
	uपूर्णांक64_t idt_sbe                      : 1;
	uपूर्णांक64_t idt_dbe                      : 1;
	uपूर्णांक64_t sisc_sbe                     : 1;
	uपूर्णांक64_t sisc_dbe                     : 1;
	uपूर्णांक64_t reserved_6_31                : 26;
	uपूर्णांक64_t addr                         : 20;
	uपूर्णांक64_t reserved_52_63               : 12;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_पूर्णांकr_पढ़ोy अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_पूर्णांकr_पढ़ोy_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_46_63               : 18;
	uपूर्णांक64_t index                        : 14;
	uपूर्णांक64_t reserved_1_31                : 31;
	uपूर्णांक64_t पढ़ोy                        : 1;
#अन्यथा
	uपूर्णांक64_t पढ़ोy                        : 1;
	uपूर्णांक64_t reserved_1_31                : 31;
	uपूर्णांक64_t index                        : 14;
	uपूर्णांक64_t reserved_46_63               : 18;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_पूर्णांकr_slowकरोwn अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_पूर्णांकr_slowकरोwn_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_3_63                : 61;
	uपूर्णांक64_t ctl                          : 3;
#अन्यथा
	uपूर्णांक64_t ctl                          : 3;
	uपूर्णांक64_t reserved_3_63                : 61;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_iscx_ctl अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_iscx_ctl_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_24_63               : 40;
	uपूर्णांक64_t idt                          : 8;
	uपूर्णांक64_t imp                          : 1;
	uपूर्णांक64_t reserved_2_14                : 13;
	uपूर्णांक64_t en                           : 1;
	uपूर्णांक64_t raw                          : 1;
#अन्यथा
	uपूर्णांक64_t raw                          : 1;
	uपूर्णांक64_t en                           : 1;
	uपूर्णांक64_t reserved_2_14                : 13;
	uपूर्णांक64_t imp                          : 1;
	uपूर्णांक64_t idt                          : 8;
	uपूर्णांक64_t reserved_24_63               : 40;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_iscx_w1c अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_iscx_w1c_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_2_63                : 62;
	uपूर्णांक64_t en                           : 1;
	uपूर्णांक64_t raw                          : 1;
#अन्यथा
	uपूर्णांक64_t raw                          : 1;
	uपूर्णांक64_t en                           : 1;
	uपूर्णांक64_t reserved_2_63                : 62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_iscx_w1s अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_iscx_w1s_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_2_63                : 62;
	uपूर्णांक64_t en                           : 1;
	uपूर्णांक64_t raw                          : 1;
#अन्यथा
	uपूर्णांक64_t raw                          : 1;
	uपूर्णांक64_t en                           : 1;
	uपूर्णांक64_t reserved_2_63                : 62;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_nmi अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_nmi_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_48_63               : 16;
	uपूर्णांक64_t nmi                          : 48;
#अन्यथा
	uपूर्णांक64_t nmi                          : 48;
	uपूर्णांक64_t reserved_48_63               : 16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_siscx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_siscx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t en                           : 64;
#अन्यथा
	uपूर्णांक64_t en                           : 64;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

जोड़ cvmx_ciu3_timx अणु
	uपूर्णांक64_t u64;
	काष्ठा cvmx_ciu3_timx_s अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक64_t reserved_37_63               : 27;
	uपूर्णांक64_t one_shot                     : 1;
	uपूर्णांक64_t len                          : 36;
#अन्यथा
	uपूर्णांक64_t len                          : 36;
	uपूर्णांक64_t one_shot                     : 1;
	uपूर्णांक64_t reserved_37_63               : 27;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

#पूर्ण_अगर
