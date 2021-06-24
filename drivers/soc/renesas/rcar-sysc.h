<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Renesas R-Car System Controller
 *
 * Copyright (C) 2016 Glider bvba
 */
#अगर_अघोषित __SOC_RENESAS_RCAR_SYSC_H__
#घोषणा __SOC_RENESAS_RCAR_SYSC_H__

#समावेश <linux/types.h>


/*
 * Power Doमुख्य flags
 */
#घोषणा PD_CPU		BIT(0)	/* Area contains मुख्य CPU core */
#घोषणा PD_SCU		BIT(1)	/* Area contains SCU and L2 cache */
#घोषणा PD_NO_CR	BIT(2)	/* Area lacks PWRअणुON,OFFपूर्णCR रेजिस्टरs */

#घोषणा PD_CPU_CR	PD_CPU		  /* CPU area has CR (R-Car H1) */
#घोषणा PD_CPU_NOCR	PD_CPU | PD_NO_CR /* CPU area lacks CR (R-Car Gen2/3) */
#घोषणा PD_ALWAYS_ON	PD_NO_CR	  /* Always-on area */


/*
 * Description of a Power Area
 */

काष्ठा rcar_sysc_area अणु
	स्थिर अक्षर *name;
	u16 chan_offs;		/* Offset of PWRSR रेजिस्टर क्रम this area */
	u8 chan_bit;		/* Bit in PWR* (except क्रम PWRUP in PWRSR) */
	u8 isr_bit;		/* Bit in SYSCI*R */
	पूर्णांक parent;		/* -1 अगर none */
	अचिन्हित पूर्णांक flags;	/* See PD_* */
पूर्ण;


/*
 * SoC-specअगरic Power Area Description
 */

काष्ठा rcar_sysc_info अणु
	पूर्णांक (*init)(व्योम);	/* Optional */
	स्थिर काष्ठा rcar_sysc_area *areas;
	अचिन्हित पूर्णांक num_areas;
	/* Optional External Request Mask Register */
	u32 exपंचांगask_offs;	/* SYSCEXTMASK रेजिस्टर offset */
	u32 exपंचांगask_val;	/* SYSCEXTMASK रेजिस्टर mask value */
पूर्ण;

बाह्य स्थिर काष्ठा rcar_sysc_info r8a7742_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a7743_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a7745_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a77470_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a774a1_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a774b1_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a774c0_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a774e1_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a7779_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a7790_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a7791_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a7792_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a7794_sysc_info;
बाह्य काष्ठा rcar_sysc_info r8a7795_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a77960_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a77961_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a77965_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a77970_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a77980_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a77990_sysc_info;
बाह्य स्थिर काष्ठा rcar_sysc_info r8a77995_sysc_info;


    /*
     * Helpers क्रम fixing up घातer area tables depending on SoC revision
     */

बाह्य व्योम rcar_sysc_nullअगरy(काष्ठा rcar_sysc_area *areas,
			      अचिन्हित पूर्णांक num_areas, u8 id);

#पूर्ण_अगर /* __SOC_RENESAS_RCAR_SYSC_H__ */
