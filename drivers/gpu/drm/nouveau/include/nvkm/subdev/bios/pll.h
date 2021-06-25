<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_PLL_H__
#घोषणा __NVBIOS_PLL_H__
/*XXX: समाप्त me */
काष्ठा nvkm_pll_vals अणु
	जोड़ अणु
		काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
			uपूर्णांक8_t N1, M1, N2, M2;
#अन्यथा
			uपूर्णांक8_t M1, N1, M2, N2;
#पूर्ण_अगर
		पूर्ण;
		काष्ठा अणु
			uपूर्णांक16_t NM1, NM2;
		पूर्ण __attribute__((packed));
	पूर्ण;
	पूर्णांक log2P;

	पूर्णांक refclk;
पूर्ण;

/* these match types in pll limits table version 0x40,
 * nvkm uses them on all chipsets पूर्णांकernally where a
 * specअगरic pll needs to be referenced, but the exact
 * रेजिस्टर isn't known.
 */
क्रमागत nvbios_pll_type अणु
	PLL_CORE   = 0x01,
	PLL_SHADER = 0x02,
	PLL_UNK03  = 0x03,
	PLL_MEMORY = 0x04,
	PLL_VDEC   = 0x05,
	PLL_UNK40  = 0x40,
	PLL_UNK41  = 0x41,
	PLL_UNK42  = 0x42,
	PLL_VPLL0  = 0x80,
	PLL_VPLL1  = 0x81,
	PLL_VPLL2  = 0x82,
	PLL_VPLL3  = 0x83,
	PLL_MAX    = 0xff
पूर्ण;

काष्ठा nvbios_pll अणु
	क्रमागत nvbios_pll_type type;
	u32 reg;
	u32 refclk;

	u8 min_p;
	u8 max_p;
	u8 bias_p;

	/*
	 * क्रम most pre nv50 cards setting a log2P of 7 (the common max_log2p
	 * value) is no dअगरferent to 6 (at least क्रम vplls) so allowing the MNP
	 * calc to use 7 causes the generated घड़ी to be out by a factor of 2.
	 * however, max_log2p cannot be fixed-up during parsing as the
	 * unmodअगरied max_log2p value is still needed क्रम setting mplls, hence
	 * an additional max_usable_log2p member
	 */
	u8 max_p_usable;

	काष्ठा अणु
		u32 min_freq;
		u32 max_freq;
		u32 min_inputfreq;
		u32 max_inputfreq;
		u8  min_m;
		u8  max_m;
		u8  min_n;
		u8  max_n;
	पूर्ण vco1, vco2;
पूर्ण;

पूर्णांक nvbios_pll_parse(काष्ठा nvkm_bios *, u32 type, काष्ठा nvbios_pll *);
#पूर्ण_अगर
