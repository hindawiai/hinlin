<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DDK750_CHIP_H__
#घोषणा DDK750_CHIP_H__
#घोषणा DEFAULT_INPUT_CLOCK 14318181 /* Default reference घड़ी */
#अगर_अघोषित SM750LE_REVISION_ID
#घोषणा SM750LE_REVISION_ID ((अचिन्हित अक्षर)0xfe)
#पूर्ण_अगर

#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/uaccess.h>

बाह्य व्योम __iomem *mmio750;

/* software control endianness */
अटल अंतरभूत u32 peek32(u32 addr)
अणु
	वापस पढ़ोl(addr + mmio750);
पूर्ण

अटल अंतरभूत व्योम poke32(u32 addr, u32 data)
अणु
	ग_लिखोl(data, addr + mmio750);
पूर्ण

/* This is all the chips recognized by this library */
क्रमागत logical_chip_type अणु
	SM_UNKNOWN,
	SM718,
	SM750,
	SM750LE,
पूर्ण;

क्रमागत घड़ी_प्रकारype अणु
	MXCLK_PLL,
	PRIMARY_PLL,
	SECONDARY_PLL,
	VGA0_PLL,
	VGA1_PLL,
पूर्ण;

काष्ठा pll_value अणु
	क्रमागत घड़ी_प्रकारype घड़ी_प्रकारype;
	अचिन्हित दीर्घ input_freq; /* Input घड़ी frequency to the PLL */

	/* Use this when घड़ीType = PANEL_PLL */
	अचिन्हित दीर्घ M;
	अचिन्हित दीर्घ N;
	अचिन्हित दीर्घ OD;
	अचिन्हित दीर्घ POD;
पूर्ण;

/* input काष्ठा to initChipParam() function */
काष्ठा initchip_param अणु
	/* Use घातer mode 0 or 1 */
	अचिन्हित लघु घातer_mode;

	/*
	 * Speed of मुख्य chip घड़ी in MHz unit
	 * 0 = keep the current घड़ी setting
	 * Others = the new मुख्य chip घड़ी
	 */
	अचिन्हित लघु chip_घड़ी;

	/*
	 * Speed of memory घड़ी in MHz unit
	 * 0 = keep the current घड़ी setting
	 * Others = the new memory घड़ी
	 */
	अचिन्हित लघु mem_घड़ी;

	/*
	 * Speed of master घड़ी in MHz unit
	 * 0 = keep the current घड़ी setting
	 * Others = the new master घड़ी
	 */
	अचिन्हित लघु master_घड़ी;

	/*
	 * 0 = leave all engine state untouched.
	 * 1 = make sure they are off: 2D, Overlay,
	 * video alpha, alpha, hardware cursors
	 */
	अचिन्हित लघु set_all_eng_off;

	/*
	 * 0 = Do not reset the memory controller
	 * 1 = Reset the memory controller
	 */
	अचिन्हित अक्षर reset_memory;

	/* More initialization parameter can be added अगर needed */
पूर्ण;

क्रमागत logical_chip_type sm750_get_chip_type(व्योम);
व्योम sm750_set_chip_type(अचिन्हित लघु dev_id, u8 rev_id);
अचिन्हित पूर्णांक sm750_calc_pll_value(अचिन्हित पूर्णांक request, काष्ठा  pll_value *pll);
अचिन्हित पूर्णांक sm750_क्रमmat_pll_reg(काष्ठा pll_value *p_PLL);
अचिन्हित पूर्णांक ddk750_get_vm_size(व्योम);
पूर्णांक ddk750_init_hw(काष्ठा initchip_param *pinit_param);

#पूर्ण_अगर
