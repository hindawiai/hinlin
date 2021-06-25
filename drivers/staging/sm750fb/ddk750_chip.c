<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/sizes.h>

#समावेश "ddk750_reg.h"
#समावेश "ddk750_chip.h"
#समावेश "ddk750_power.h"

#घोषणा MHz(x) ((x) * 1000000)

अटल क्रमागत logical_chip_type chip;

क्रमागत logical_chip_type sm750_get_chip_type(व्योम)
अणु
	वापस chip;
पूर्ण

व्योम sm750_set_chip_type(अचिन्हित लघु dev_id, u8 rev_id)
अणु
	अगर (dev_id == 0x718) अणु
		chip = SM718;
	पूर्ण अन्यथा अगर (dev_id == 0x750) अणु
		chip = SM750;
		/* SM750 and SM750LE are dअगरferent in their revision ID only. */
		अगर (rev_id == SM750LE_REVISION_ID) अणु
			chip = SM750LE;
			pr_info("found sm750le\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		chip = SM_UNKNOWN;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक get_mxclk_freq(व्योम)
अणु
	अचिन्हित पूर्णांक pll_reg;
	अचिन्हित पूर्णांक M, N, OD, POD;

	अगर (sm750_get_chip_type() == SM750LE)
		वापस MHz(130);

	pll_reg = peek32(MXCLK_PLL_CTRL);
	M = (pll_reg & PLL_CTRL_M_MASK) >> PLL_CTRL_M_SHIFT;
	N = (pll_reg & PLL_CTRL_N_MASK) >> PLL_CTRL_N_SHIFT;
	OD = (pll_reg & PLL_CTRL_OD_MASK) >> PLL_CTRL_OD_SHIFT;
	POD = (pll_reg & PLL_CTRL_POD_MASK) >> PLL_CTRL_POD_SHIFT;

	वापस DEFAULT_INPUT_CLOCK * M / N / BIT(OD) / BIT(POD);
पूर्ण

/*
 * This function set up the मुख्य chip घड़ी.
 *
 * Input: Frequency to be set.
 */
अटल व्योम set_chip_घड़ी(अचिन्हित पूर्णांक frequency)
अणु
	काष्ठा pll_value pll;

	/* Cheok_0509: For SM750LE, the chip घड़ी is fixed. Nothing to set. */
	अगर (sm750_get_chip_type() == SM750LE)
		वापस;

	अगर (frequency) अणु
		/*
		 * Set up PLL काष्ठाure to hold the value to be set in घड़ीs.
		 */
		pll.input_freq = DEFAULT_INPUT_CLOCK; /* Defined in CLOCK.H */
		pll.घड़ी_प्रकारype = MXCLK_PLL;

		/*
		 * Call sm750_calc_pll_value() to fill the other fields
		 * of the PLL काष्ठाure. Someबार, the chip cannot set
		 * up the exact घड़ी required by the User.
		 * Return value of sm750_calc_pll_value gives the actual
		 * possible घड़ी.
		 */
		sm750_calc_pll_value(frequency, &pll);

		/* Master Clock Control: MXCLK_PLL */
		poke32(MXCLK_PLL_CTRL, sm750_क्रमmat_pll_reg(&pll));
	पूर्ण
पूर्ण

अटल व्योम set_memory_घड़ी(अचिन्हित पूर्णांक frequency)
अणु
	अचिन्हित पूर्णांक reg, भागisor;

	/*
	 * Cheok_0509: For SM750LE, the memory घड़ी is fixed.
	 * Nothing to set.
	 */
	अगर (sm750_get_chip_type() == SM750LE)
		वापस;

	अगर (frequency) अणु
		/*
		 * Set the frequency to the maximum frequency
		 * that the DDR Memory can take which is 336MHz.
		 */
		अगर (frequency > MHz(336))
			frequency = MHz(336);

		/* Calculate the भागisor */
		भागisor = DIV_ROUND_CLOSEST(get_mxclk_freq(), frequency);

		/* Set the corresponding भागisor in the रेजिस्टर. */
		reg = peek32(CURRENT_GATE) & ~CURRENT_GATE_M2XCLK_MASK;
		चयन (भागisor) अणु
		शेष:
		हाल 1:
			reg |= CURRENT_GATE_M2XCLK_DIV_1;
			अवरोध;
		हाल 2:
			reg |= CURRENT_GATE_M2XCLK_DIV_2;
			अवरोध;
		हाल 3:
			reg |= CURRENT_GATE_M2XCLK_DIV_3;
			अवरोध;
		हाल 4:
			reg |= CURRENT_GATE_M2XCLK_DIV_4;
			अवरोध;
		पूर्ण

		sm750_set_current_gate(reg);
	पूर्ण
पूर्ण

/*
 * This function set up the master घड़ी (MCLK).
 *
 * Input: Frequency to be set.
 *
 * NOTE:
 *      The maximum frequency the engine can run is 168MHz.
 */
अटल व्योम set_master_घड़ी(अचिन्हित पूर्णांक frequency)
अणु
	अचिन्हित पूर्णांक reg, भागisor;

	/*
	 * Cheok_0509: For SM750LE, the memory घड़ी is fixed.
	 * Nothing to set.
	 */
	अगर (sm750_get_chip_type() == SM750LE)
		वापस;

	अगर (frequency) अणु
		/*
		 * Set the frequency to the maximum frequency
		 * that the SM750 engine can run, which is about 190 MHz.
		 */
		अगर (frequency > MHz(190))
			frequency = MHz(190);

		/* Calculate the भागisor */
		भागisor = DIV_ROUND_CLOSEST(get_mxclk_freq(), frequency);

		/* Set the corresponding भागisor in the रेजिस्टर. */
		reg = peek32(CURRENT_GATE) & ~CURRENT_GATE_MCLK_MASK;
		चयन (भागisor) अणु
		शेष:
		हाल 3:
			reg |= CURRENT_GATE_MCLK_DIV_3;
			अवरोध;
		हाल 4:
			reg |= CURRENT_GATE_MCLK_DIV_4;
			अवरोध;
		हाल 6:
			reg |= CURRENT_GATE_MCLK_DIV_6;
			अवरोध;
		हाल 8:
			reg |= CURRENT_GATE_MCLK_DIV_8;
			अवरोध;
		पूर्ण

		sm750_set_current_gate(reg);
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक ddk750_get_vm_size(व्योम)
अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक data;

	/* sm750le only use 64 mb memory*/
	अगर (sm750_get_chip_type() == SM750LE)
		वापस SZ_64M;

	/* क्रम 750,always use घातer mode0*/
	reg = peek32(MODE0_GATE);
	reg |= MODE0_GATE_GPIO;
	poke32(MODE0_GATE, reg);

	/* get frame buffer size from GPIO */
	reg = peek32(MISC_CTRL) & MISC_CTRL_LOCALMEM_SIZE_MASK;
	चयन (reg) अणु
	हाल MISC_CTRL_LOCALMEM_SIZE_8M:
		data = SZ_8M;  अवरोध; /* 8  Mega byte */
	हाल MISC_CTRL_LOCALMEM_SIZE_16M:
		data = SZ_16M; अवरोध; /* 16 Mega byte */
	हाल MISC_CTRL_LOCALMEM_SIZE_32M:
		data = SZ_32M; अवरोध; /* 32 Mega byte */
	हाल MISC_CTRL_LOCALMEM_SIZE_64M:
		data = SZ_64M; अवरोध; /* 64 Mega byte */
	शेष:
		data = 0;
		अवरोध;
	पूर्ण
	वापस data;
पूर्ण

पूर्णांक ddk750_init_hw(काष्ठा initchip_param *p_init_param)
अणु
	अचिन्हित पूर्णांक reg;

	अगर (p_init_param->घातer_mode != 0)
		p_init_param->घातer_mode = 0;
	sm750_set_घातer_mode(p_init_param->घातer_mode);

	/* Enable display घातer gate & LOCALMEM घातer gate*/
	reg = peek32(CURRENT_GATE);
	reg |= (CURRENT_GATE_DISPLAY | CURRENT_GATE_LOCALMEM);
	sm750_set_current_gate(reg);

	अगर (sm750_get_chip_type() != SM750LE) अणु
		/* set panel pll and graphic mode via mmio_88 */
		reg = peek32(VGA_CONFIGURATION);
		reg |= (VGA_CONFIGURATION_PLL | VGA_CONFIGURATION_MODE);
		poke32(VGA_CONFIGURATION, reg);
	पूर्ण अन्यथा अणु
#अगर defined(__i386__) || defined(__x86_64__)
		/* set graphic mode via IO method */
		outb_p(0x88, 0x3d4);
		outb_p(0x06, 0x3d5);
#पूर्ण_अगर
	पूर्ण

	/* Set the Main Chip Clock */
	set_chip_घड़ी(MHz((अचिन्हित पूर्णांक)p_init_param->chip_घड़ी));

	/* Set up memory घड़ी. */
	set_memory_घड़ी(MHz(p_init_param->mem_घड़ी));

	/* Set up master घड़ी */
	set_master_घड़ी(MHz(p_init_param->master_घड़ी));

	/*
	 * Reset the memory controller.
	 * If the memory controller is not reset in SM750,
	 * the प्रणाली might hang when sw accesses the memory.
	 * The memory should be resetted after changing the MXCLK.
	 */
	अगर (p_init_param->reset_memory == 1) अणु
		reg = peek32(MISC_CTRL);
		reg &= ~MISC_CTRL_LOCALMEM_RESET;
		poke32(MISC_CTRL, reg);

		reg |= MISC_CTRL_LOCALMEM_RESET;
		poke32(MISC_CTRL, reg);
	पूर्ण

	अगर (p_init_param->set_all_eng_off == 1) अणु
		sm750_enable_2d_engine(0);

		/* Disable Overlay, अगर a क्रमmer application left it on */
		reg = peek32(VIDEO_DISPLAY_CTRL);
		reg &= ~DISPLAY_CTRL_PLANE;
		poke32(VIDEO_DISPLAY_CTRL, reg);

		/* Disable video alpha, अगर a क्रमmer application left it on */
		reg = peek32(VIDEO_ALPHA_DISPLAY_CTRL);
		reg &= ~DISPLAY_CTRL_PLANE;
		poke32(VIDEO_ALPHA_DISPLAY_CTRL, reg);

		/* Disable alpha plane, अगर a क्रमmer application left it on */
		reg = peek32(ALPHA_DISPLAY_CTRL);
		reg &= ~DISPLAY_CTRL_PLANE;
		poke32(ALPHA_DISPLAY_CTRL, reg);

		/* Disable DMA Channel, अगर a क्रमmer application left it on */
		reg = peek32(DMA_ABORT_INTERRUPT);
		reg |= DMA_ABORT_INTERRUPT_ABORT_1;
		poke32(DMA_ABORT_INTERRUPT, reg);

		/* Disable DMA Power, अगर a क्रमmer application left it on */
		sm750_enable_dma(0);
	पूर्ण

	/* We can add more initialization as needed. */

	वापस 0;
पूर्ण

/*
 * monk liu @ 4/6/2011:
 *	re-ग_लिखो the calculatePLL function of ddk750.
 *	the original version function करोes not use
 *	some mathematics tricks and लघुcut
 *	when it करोing the calculation of the best N,M,D combination
 *	I think this version gives a little upgrade in speed
 *
 * 750 pll घड़ी क्रमmular:
 * Request Clock = (Input Clock * M )/(N * X)
 *
 * Input Clock = 14318181 hz
 * X = 2 घातer D
 * D =अणु0,1,2,3,4,5,6पूर्ण
 * M = अणु1,...,255पूर्ण
 * N = अणु2,...,15पूर्ण
 */
अचिन्हित पूर्णांक sm750_calc_pll_value(अचिन्हित पूर्णांक request_orig,
				  काष्ठा pll_value *pll)
अणु
	/*
	 * as sm750 रेजिस्टर definition,
	 * N located in 2,15 and M located in 1,255
	 */
	पूर्णांक N, M, X, d;
	पूर्णांक mini_dअगरf;
	अचिन्हित पूर्णांक RN, quo, rem, fl_quo;
	अचिन्हित पूर्णांक input, request;
	अचिन्हित पूर्णांक पंचांगp_घड़ी, ret;
	स्थिर पूर्णांक max_OD = 3;
	पूर्णांक max_d = 6;

	अगर (sm750_get_chip_type() == SM750LE) अणु
		/*
		 * SM750LE करोn't have
		 * programmable PLL and M/N values to work on.
		 * Just वापस the requested घड़ी.
		 */
		वापस request_orig;
	पूर्ण

	ret = 0;
	mini_dअगरf = ~0;
	request = request_orig / 1000;
	input = pll->input_freq / 1000;

	/*
	 * क्रम MXCLK रेजिस्टर,
	 * no POD provided, so need be treated dअगरferently
	 */
	अगर (pll->घड़ी_प्रकारype == MXCLK_PLL)
		max_d = 3;

	क्रम (N = 15; N > 1; N--) अणु
		/*
		 * RN will not exceed maximum दीर्घ
		 * अगर @request <= 285 MHZ (क्रम 32bit cpu)
		 */
		RN = N * request;
		quo = RN / input;
		rem = RN % input;/* rem always small than 14318181 */
		fl_quo = rem * 10000 / input;

		क्रम (d = max_d; d >= 0; d--) अणु
			X = BIT(d);
			M = quo * X;
			M += fl_quo * X / 10000;
			/* round step */
			M += (fl_quo * X % 10000) > 5000 ? 1 : 0;
			अगर (M < 256 && M > 0) अणु
				अचिन्हित पूर्णांक dअगरf;

				पंचांगp_घड़ी = pll->input_freq * M / N / X;
				dअगरf = असल(पंचांगp_घड़ी - request_orig);
				अगर (dअगरf < mini_dअगरf) अणु
					pll->M = M;
					pll->N = N;
					pll->POD = 0;
					अगर (d > max_OD)
						pll->POD = d - max_OD;
					pll->OD = d - pll->POD;
					mini_dअगरf = dअगरf;
					ret = पंचांगp_घड़ी;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक sm750_क्रमmat_pll_reg(काष्ठा pll_value *p_PLL)
अणु
#अगर_अघोषित VALIDATION_CHIP
	अचिन्हित पूर्णांक POD = p_PLL->POD;
#पूर्ण_अगर
	अचिन्हित पूर्णांक OD = p_PLL->OD;
	अचिन्हित पूर्णांक M = p_PLL->M;
	अचिन्हित पूर्णांक N = p_PLL->N;

	/*
	 * Note that all PLL's have the same क्रमmat. Here, we just use
	 * Panel PLL parameter to work out the bit fields in the
	 * रेजिस्टर. On वापसing a 32 bit number, the value can be
	 * applied to any PLL in the calling function.
	 */
	वापस PLL_CTRL_POWER |
#अगर_अघोषित VALIDATION_CHIP
		((POD << PLL_CTRL_POD_SHIFT) & PLL_CTRL_POD_MASK) |
#पूर्ण_अगर
		((OD << PLL_CTRL_OD_SHIFT) & PLL_CTRL_OD_MASK) |
		((N << PLL_CTRL_N_SHIFT) & PLL_CTRL_N_MASK) |
		((M << PLL_CTRL_M_SHIFT) & PLL_CTRL_M_MASK);
पूर्ण
