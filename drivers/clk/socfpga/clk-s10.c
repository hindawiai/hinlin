<शैली गुरु>
// SPDX-License-Identअगरier:	GPL-2.0
/*
 * Copyright (C) 2017, Intel Corporation
 */
#समावेश <linux/slab.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <dt-bindings/घड़ी/stratix10-घड़ी.h>

#समावेश "stratix10-clk.h"

अटल स्थिर काष्ठा clk_parent_data pll_mux[] = अणु
	अणु .fw_name = "osc1",
	  .name = "osc1" पूर्ण,
	अणु .fw_name = "cb-intosc-hs-div2-clk",
	  .name = "cb-intosc-hs-div2-clk" पूर्ण,
	अणु .fw_name = "f2s-free-clk",
	  .name = "f2s-free-clk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data cntr_mux[] = अणु
	अणु .fw_name =  "main_pll",
	  .name = "main_pll", पूर्ण,
	अणु .fw_name = "periph_pll",
	  .name = "periph_pll", पूर्ण,
	अणु .fw_name = "osc1",
	  .name = "osc1", पूर्ण,
	अणु .fw_name = "cb-intosc-hs-div2-clk",
	  .name = "cb-intosc-hs-div2-clk", पूर्ण,
	अणु .fw_name = "f2s-free-clk",
	  .name = "f2s-free-clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data boot_mux[] = अणु
	अणु .fw_name = "osc1",
	  .name = "osc1" पूर्ण,
	अणु .fw_name = "cb-intosc-hs-div2-clk",
	  .name = "cb-intosc-hs-div2-clk" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data noc_मुक्त_mux[] = अणु
	अणु .fw_name = "main_noc_base_clk",
	  .name = "main_noc_base_clk", पूर्ण,
	अणु .fw_name = "peri_noc_base_clk",
	  .name = "peri_noc_base_clk", पूर्ण,
	अणु .fw_name = "osc1",
	  .name = "osc1", पूर्ण,
	अणु .fw_name = "cb-intosc-hs-div2-clk",
	  .name = "cb-intosc-hs-div2-clk", पूर्ण,
	अणु .fw_name = "f2s-free-clk",
	  .name = "f2s-free-clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data emaca_मुक्त_mux[] = अणु
	अणु .fw_name = "peri_emaca_clk",
	  .name = "peri_emaca_clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data emacb_मुक्त_mux[] = अणु
	अणु .fw_name = "peri_emacb_clk",
	  .name = "peri_emacb_clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data emac_ptp_मुक्त_mux[] = अणु
	अणु .fw_name = "peri_emac_ptp_clk",
	  .name = "peri_emac_ptp_clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data gpio_db_मुक्त_mux[] = अणु
	अणु .fw_name = "peri_gpio_db_clk",
	  .name = "peri_gpio_db_clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data sdmmc_मुक्त_mux[] = अणु
	अणु .fw_name = "main_sdmmc_clk",
	  .name = "main_sdmmc_clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data s2f_usr1_मुक्त_mux[] = अणु
	अणु .fw_name = "peri_s2f_usr1_clk",
	  .name = "peri_s2f_usr1_clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data psi_ref_मुक्त_mux[] = अणु
	अणु .fw_name = "peri_psi_ref_clk",
	  .name = "peri_psi_ref_clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mpu_mux[] = अणु
	अणु .fw_name = "mpu_free_clk",
	  .name = "mpu_free_clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data s2f_usr0_mux[] = अणु
	अणु .fw_name = "f2s-free-clk",
	  .name = "f2s-free-clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data emac_mux[] = अणु
	अणु .fw_name = "emaca_free_clk",
	  .name = "emaca_free_clk", पूर्ण,
	अणु .fw_name = "emacb_free_clk",
	  .name = "emacb_free_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data noc_mux[] = अणु
	अणु .fw_name = "noc_free_clk",
	  .name = "noc_free_clk", पूर्ण,
	अणु .fw_name = "boot_clk",
	  .name = "boot_clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mpu_मुक्त_mux[] = अणु
	अणु .fw_name = "main_mpu_base_clk",
	  .name = "main_mpu_base_clk", पूर्ण,
	अणु .fw_name = "peri_mpu_base_clk",
	  .name = "peri_mpu_base_clk", पूर्ण,
	अणु .fw_name = "osc1",
	  .name = "osc1", पूर्ण,
	अणु .fw_name = "cb-intosc-hs-div2-clk",
	  .name = "cb-intosc-hs-div2-clk", पूर्ण,
	अणु .fw_name = "f2s-free-clk",
	  .name = "f2s-free-clk", पूर्ण,
पूर्ण;

/* घड़ीs in AO (always on) controller */
अटल स्थिर काष्ठा stratix10_pll_घड़ी s10_pll_clks[] = अणु
	अणु STRATIX10_BOOT_CLK, "boot_clk", boot_mux, ARRAY_SIZE(boot_mux), 0,
	  0x0पूर्ण,
	अणु STRATIX10_MAIN_PLL_CLK, "main_pll", pll_mux, ARRAY_SIZE(pll_mux),
	  0, 0x74पूर्ण,
	अणु STRATIX10_PERIPH_PLL_CLK, "periph_pll", pll_mux, ARRAY_SIZE(pll_mux),
	  0, 0xe4पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा stratix10_perip_c_घड़ी s10_मुख्य_perip_c_clks[] = अणु
	अणु STRATIX10_MAIN_MPU_BASE_CLK, "main_mpu_base_clk", "main_pll", शून्य, 1, 0, 0x84पूर्ण,
	अणु STRATIX10_MAIN_NOC_BASE_CLK, "main_noc_base_clk", "main_pll", शून्य, 1, 0, 0x88पूर्ण,
	अणु STRATIX10_PERI_MPU_BASE_CLK, "peri_mpu_base_clk", "periph_pll", शून्य, 1, 0,
	  0xF4पूर्ण,
	अणु STRATIX10_PERI_NOC_BASE_CLK, "peri_noc_base_clk", "periph_pll", शून्य, 1, 0,
	  0xF8पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा stratix10_perip_cnt_घड़ी s10_मुख्य_perip_cnt_clks[] = अणु
	अणु STRATIX10_MPU_FREE_CLK, "mpu_free_clk", शून्य, mpu_मुक्त_mux, ARRAY_SIZE(mpu_मुक्त_mux),
	   0, 0x48, 0, 0, 0पूर्ण,
	अणु STRATIX10_NOC_FREE_CLK, "noc_free_clk", शून्य, noc_मुक्त_mux, ARRAY_SIZE(noc_मुक्त_mux),
	  0, 0x4C, 0, 0, 0पूर्ण,
	अणु STRATIX10_MAIN_EMACA_CLK, "main_emaca_clk", "main_noc_base_clk", शून्य, 1, 0,
	  0x50, 0, 0, 0पूर्ण,
	अणु STRATIX10_MAIN_EMACB_CLK, "main_emacb_clk", "main_noc_base_clk", शून्य, 1, 0,
	  0x54, 0, 0, 0पूर्ण,
	अणु STRATIX10_MAIN_EMAC_PTP_CLK, "main_emac_ptp_clk", "main_noc_base_clk", शून्य, 1, 0,
	  0x58, 0, 0, 0पूर्ण,
	अणु STRATIX10_MAIN_GPIO_DB_CLK, "main_gpio_db_clk", "main_noc_base_clk", शून्य, 1, 0,
	  0x5C, 0, 0, 0पूर्ण,
	अणु STRATIX10_MAIN_SDMMC_CLK, "main_sdmmc_clk", "main_noc_base_clk", शून्य, 1, 0,
	  0x60, 0, 0, 0पूर्ण,
	अणु STRATIX10_MAIN_S2F_USR0_CLK, "main_s2f_usr0_clk", शून्य, cntr_mux, ARRAY_SIZE(cntr_mux),
	  0, 0x64, 0, 0, 0पूर्ण,
	अणु STRATIX10_MAIN_S2F_USR1_CLK, "main_s2f_usr1_clk", "main_noc_base_clk", शून्य, 1, 0,
	  0x68, 0, 0, 0पूर्ण,
	अणु STRATIX10_MAIN_PSI_REF_CLK, "main_psi_ref_clk", "main_noc_base_clk", शून्य, 1, 0,
	  0x6C, 0, 0, 0पूर्ण,
	अणु STRATIX10_PERI_EMACA_CLK, "peri_emaca_clk", शून्य, cntr_mux, ARRAY_SIZE(cntr_mux),
	  0, 0xBC, 0, 0, 0पूर्ण,
	अणु STRATIX10_PERI_EMACB_CLK, "peri_emacb_clk", शून्य, cntr_mux, ARRAY_SIZE(cntr_mux),
	  0, 0xC0, 0, 0, 0पूर्ण,
	अणु STRATIX10_PERI_EMAC_PTP_CLK, "peri_emac_ptp_clk", शून्य, cntr_mux, ARRAY_SIZE(cntr_mux),
	  0, 0xC4, 0, 0, 0पूर्ण,
	अणु STRATIX10_PERI_GPIO_DB_CLK, "peri_gpio_db_clk", शून्य, cntr_mux, ARRAY_SIZE(cntr_mux),
	  0, 0xC8, 0, 0, 0पूर्ण,
	अणु STRATIX10_PERI_SDMMC_CLK, "peri_sdmmc_clk", शून्य, cntr_mux, ARRAY_SIZE(cntr_mux),
	  0, 0xCC, 0, 0, 0पूर्ण,
	अणु STRATIX10_PERI_S2F_USR0_CLK, "peri_s2f_usr0_clk", "peri_noc_base_clk", शून्य, 1, 0,
	  0xD0, 0, 0, 0पूर्ण,
	अणु STRATIX10_PERI_S2F_USR1_CLK, "peri_s2f_usr1_clk", शून्य, cntr_mux, ARRAY_SIZE(cntr_mux),
	  0, 0xD4, 0, 0, 0पूर्ण,
	अणु STRATIX10_PERI_PSI_REF_CLK, "peri_psi_ref_clk", "peri_noc_base_clk", शून्य, 1, 0,
	  0xD8, 0, 0, 0पूर्ण,
	अणु STRATIX10_L4_SYS_FREE_CLK, "l4_sys_free_clk", "noc_free_clk", शून्य, 1, 0,
	  0, 4, 0, 0पूर्ण,
	अणु STRATIX10_NOC_CLK, "noc_clk", शून्य, noc_mux, ARRAY_SIZE(noc_mux),
	  0, 0, 0, 0x3C, 1पूर्ण,
	अणु STRATIX10_EMAC_A_FREE_CLK, "emaca_free_clk", शून्य, emaca_मुक्त_mux, ARRAY_SIZE(emaca_मुक्त_mux),
	  0, 0, 2, 0xB0, 0पूर्ण,
	अणु STRATIX10_EMAC_B_FREE_CLK, "emacb_free_clk", शून्य, emacb_मुक्त_mux, ARRAY_SIZE(emacb_मुक्त_mux),
	  0, 0, 2, 0xB0, 1पूर्ण,
	अणु STRATIX10_EMAC_PTP_FREE_CLK, "emac_ptp_free_clk", शून्य, emac_ptp_मुक्त_mux,
	  ARRAY_SIZE(emac_ptp_मुक्त_mux), 0, 0, 2, 0xB0, 2पूर्ण,
	अणु STRATIX10_GPIO_DB_FREE_CLK, "gpio_db_free_clk", शून्य, gpio_db_मुक्त_mux,
	  ARRAY_SIZE(gpio_db_मुक्त_mux), 0, 0, 0, 0xB0, 3पूर्ण,
	अणु STRATIX10_SDMMC_FREE_CLK, "sdmmc_free_clk", शून्य, sdmmc_मुक्त_mux,
	  ARRAY_SIZE(sdmmc_मुक्त_mux), 0, 0, 0, 0xB0, 4पूर्ण,
	अणु STRATIX10_S2F_USER1_FREE_CLK, "s2f_user1_free_clk", शून्य, s2f_usr1_मुक्त_mux,
	  ARRAY_SIZE(s2f_usr1_मुक्त_mux), 0, 0, 0, 0xB0, 5पूर्ण,
	अणु STRATIX10_PSI_REF_FREE_CLK, "psi_ref_free_clk", शून्य, psi_ref_मुक्त_mux,
	  ARRAY_SIZE(psi_ref_मुक्त_mux), 0, 0, 0, 0xB0, 6पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा stratix10_gate_घड़ी s10_gate_clks[] = अणु
	अणु STRATIX10_MPU_CLK, "mpu_clk", शून्य, mpu_mux, ARRAY_SIZE(mpu_mux), 0, 0x30,
	  0, 0, 0, 0, 0x3C, 0, 0पूर्ण,
	अणु STRATIX10_MPU_PERIPH_CLK, "mpu_periph_clk", "mpu_clk", शून्य, 1, 0, 0x30,
	  0, 0, 0, 0, 0, 0, 4पूर्ण,
	अणु STRATIX10_MPU_L2RAM_CLK, "mpu_l2ram_clk", "mpu_clk", शून्य, 1, 0, 0x30,
	  0, 0, 0, 0, 0, 0, 2पूर्ण,
	अणु STRATIX10_L4_MAIN_CLK, "l4_main_clk", "noc_clk", शून्य, 1, 0, 0x30,
	  1, 0x70, 0, 2, 0, 0, 0पूर्ण,
	अणु STRATIX10_L4_MP_CLK, "l4_mp_clk", "noc_clk", शून्य, 1, 0, 0x30,
	  2, 0x70, 8, 2, 0, 0, 0पूर्ण,
	अणु STRATIX10_L4_SP_CLK, "l4_sp_clk", "noc_clk", शून्य, 1, CLK_IS_CRITICAL, 0x30,
	  3, 0x70, 16, 2, 0, 0, 0पूर्ण,
	अणु STRATIX10_CS_AT_CLK, "cs_at_clk", "noc_clk", शून्य, 1, 0, 0x30,
	  4, 0x70, 24, 2, 0, 0, 0पूर्ण,
	अणु STRATIX10_CS_TRACE_CLK, "cs_trace_clk", "noc_clk", शून्य, 1, 0, 0x30,
	  4, 0x70, 26, 2, 0, 0, 0पूर्ण,
	अणु STRATIX10_CS_PDBG_CLK, "cs_pdbg_clk", "cs_at_clk", शून्य, 1, 0, 0x30,
	  4, 0x70, 28, 1, 0, 0, 0पूर्ण,
	अणु STRATIX10_CS_TIMER_CLK, "cs_timer_clk", "noc_clk", शून्य, 1, 0, 0x30,
	  5, 0, 0, 0, 0, 0, 0पूर्ण,
	अणु STRATIX10_S2F_USER0_CLK, "s2f_user0_clk", शून्य, s2f_usr0_mux, ARRAY_SIZE(s2f_usr0_mux), 0, 0x30,
	  6, 0, 0, 0, 0, 0, 0पूर्ण,
	अणु STRATIX10_EMAC0_CLK, "emac0_clk", शून्य, emac_mux, ARRAY_SIZE(emac_mux), 0, 0xA4,
	  0, 0, 0, 0, 0xDC, 26, 0पूर्ण,
	अणु STRATIX10_EMAC1_CLK, "emac1_clk", शून्य, emac_mux, ARRAY_SIZE(emac_mux), 0, 0xA4,
	  1, 0, 0, 0, 0xDC, 27, 0पूर्ण,
	अणु STRATIX10_EMAC2_CLK, "emac2_clk", शून्य, emac_mux, ARRAY_SIZE(emac_mux), 0, 0xA4,
	  2, 0, 0, 0, 0xDC, 28, 0पूर्ण,
	अणु STRATIX10_EMAC_PTP_CLK, "emac_ptp_clk", "emac_ptp_free_clk", शून्य, 1, 0, 0xA4,
	  3, 0, 0, 0, 0, 0, 0पूर्ण,
	अणु STRATIX10_GPIO_DB_CLK, "gpio_db_clk", "gpio_db_free_clk", शून्य, 1, 0, 0xA4,
	  4, 0xE0, 0, 16, 0, 0, 0पूर्ण,
	अणु STRATIX10_SDMMC_CLK, "sdmmc_clk", "sdmmc_free_clk", शून्य, 1, 0, 0xA4,
	  5, 0, 0, 0, 0, 0, 4पूर्ण,
	अणु STRATIX10_S2F_USER1_CLK, "s2f_user1_clk", "s2f_user1_free_clk", शून्य, 1, 0, 0xA4,
	  6, 0, 0, 0, 0, 0, 0पूर्ण,
	अणु STRATIX10_PSI_REF_CLK, "psi_ref_clk", "psi_ref_free_clk", शून्य, 1, 0, 0xA4,
	  7, 0, 0, 0, 0, 0, 0पूर्ण,
	अणु STRATIX10_USB_CLK, "usb_clk", "l4_mp_clk", शून्य, 1, 0, 0xA4,
	  8, 0, 0, 0, 0, 0, 0पूर्ण,
	अणु STRATIX10_SPI_M_CLK, "spi_m_clk", "l4_mp_clk", शून्य, 1, 0, 0xA4,
	  9, 0, 0, 0, 0, 0, 0पूर्ण,
	अणु STRATIX10_न_अंकD_X_CLK, "nand_x_clk", "l4_mp_clk", शून्य, 1, 0, 0xA4,
	  10, 0, 0, 0, 0, 0, 0पूर्ण,
	अणु STRATIX10_न_अंकD_CLK, "nand_clk", "nand_x_clk", शून्य, 1, 0, 0xA4,
	  10, 0, 0, 0, 0, 0, 4पूर्ण,
	अणु STRATIX10_न_अंकD_ECC_CLK, "nand_ecc_clk", "nand_x_clk", शून्य, 1, 0, 0xA4,
	  10, 0, 0, 0, 0, 0, 4पूर्ण,
पूर्ण;

अटल पूर्णांक s10_clk_रेजिस्टर_c_perip(स्थिर काष्ठा stratix10_perip_c_घड़ी *clks,
				    पूर्णांक nums, काष्ठा stratix10_घड़ी_data *data)
अणु
	काष्ठा clk_hw *hw_clk;
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		hw_clk = s10_रेजिस्टर_periph(&clks[i], base);
		अगर (IS_ERR(hw_clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		data->clk_data.hws[clks[i].id] = hw_clk;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s10_clk_रेजिस्टर_cnt_perip(स्थिर काष्ठा stratix10_perip_cnt_घड़ी *clks,
				      पूर्णांक nums, काष्ठा stratix10_घड़ी_data *data)
अणु
	काष्ठा clk_hw *hw_clk;
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		hw_clk = s10_रेजिस्टर_cnt_periph(&clks[i], base);
		अगर (IS_ERR(hw_clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		data->clk_data.hws[clks[i].id] = hw_clk;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s10_clk_रेजिस्टर_gate(स्थिर काष्ठा stratix10_gate_घड़ी *clks,
				 पूर्णांक nums, काष्ठा stratix10_घड़ी_data *data)
अणु
	काष्ठा clk_hw *hw_clk;
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		hw_clk = s10_रेजिस्टर_gate(&clks[i], base);
		अगर (IS_ERR(hw_clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		data->clk_data.hws[clks[i].id] = hw_clk;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s10_clk_रेजिस्टर_pll(स्थिर काष्ठा stratix10_pll_घड़ी *clks,
				 पूर्णांक nums, काष्ठा stratix10_घड़ी_data *data)
अणु
	काष्ठा clk_hw *hw_clk;
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		hw_clk = s10_रेजिस्टर_pll(&clks[i], base);
		अगर (IS_ERR(hw_clk)) अणु
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण
		data->clk_data.hws[clks[i].id] = hw_clk;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s10_clkmgr_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा stratix10_घड़ी_data *clk_data;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक i, num_clks;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base)) अणु
		pr_err("%s: failed to map clock registers\n", __func__);
		वापस PTR_ERR(base);
	पूर्ण

	num_clks = STRATIX10_NUM_CLKS;
	clk_data = devm_kzalloc(dev, काष्ठा_size(clk_data, clk_data.hws,
						 num_clks), GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_clks; i++)
		clk_data->clk_data.hws[i] = ERR_PTR(-ENOENT);

	clk_data->base = base;
	clk_data->clk_data.num = num_clks;

	s10_clk_रेजिस्टर_pll(s10_pll_clks, ARRAY_SIZE(s10_pll_clks), clk_data);

	s10_clk_रेजिस्टर_c_perip(s10_मुख्य_perip_c_clks,
				 ARRAY_SIZE(s10_मुख्य_perip_c_clks), clk_data);

	s10_clk_रेजिस्टर_cnt_perip(s10_मुख्य_perip_cnt_clks,
				   ARRAY_SIZE(s10_मुख्य_perip_cnt_clks),
				   clk_data);

	s10_clk_रेजिस्टर_gate(s10_gate_clks, ARRAY_SIZE(s10_gate_clks),
			      clk_data);

	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, &clk_data->clk_data);
	वापस 0;
पूर्ण

अटल पूर्णांक s10_clkmgr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस	s10_clkmgr_init(pdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id stratix10_clkmgr_match_table[] = अणु
	अणु .compatible = "intel,stratix10-clkmgr",
	  .data = s10_clkmgr_init पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver stratix10_clkmgr_driver = अणु
	.probe		= s10_clkmgr_probe,
	.driver		= अणु
		.name	= "stratix10-clkmgr",
		.suppress_bind_attrs = true,
		.of_match_table = stratix10_clkmgr_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init s10_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&stratix10_clkmgr_driver);
पूर्ण
core_initcall(s10_clk_init);
