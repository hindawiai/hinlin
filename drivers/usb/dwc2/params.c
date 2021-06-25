<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/*
 * Copyright (C) 2004-2016 Synopsys, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The names of the above-listed copyright holders may not be used
 *    to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#समावेश "core.h"

अटल व्योम dwc2_set_bcm_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->host_rx_fअगरo_size = 774;
	p->max_transfer_size = 65535;
	p->max_packet_count = 511;
	p->ahbcfg = 0x10;
पूर्ण

अटल व्योम dwc2_set_his_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->otg_cap = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
	p->speed = DWC2_SPEED_PARAM_HIGH;
	p->host_rx_fअगरo_size = 512;
	p->host_nperio_tx_fअगरo_size = 512;
	p->host_perio_tx_fअगरo_size = 512;
	p->max_transfer_size = 65535;
	p->max_packet_count = 511;
	p->host_channels = 16;
	p->phy_type = DWC2_PHY_TYPE_PARAM_UTMI;
	p->phy_uपंचांगi_width = 8;
	p->i2c_enable = false;
	p->reload_ctl = false;
	p->ahbcfg = GAHBCFG_HBSTLEN_INCR16 <<
		GAHBCFG_HBSTLEN_SHIFT;
	p->change_speed_quirk = true;
	p->घातer_करोwn = DWC2_POWER_DOWN_PARAM_NONE;
पूर्ण

अटल व्योम dwc2_set_s3c6400_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->घातer_करोwn = DWC2_POWER_DOWN_PARAM_NONE;
	p->phy_uपंचांगi_width = 8;
पूर्ण

अटल व्योम dwc2_set_rk_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->otg_cap = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
	p->host_rx_fअगरo_size = 525;
	p->host_nperio_tx_fअगरo_size = 128;
	p->host_perio_tx_fअगरo_size = 256;
	p->ahbcfg = GAHBCFG_HBSTLEN_INCR16 <<
		GAHBCFG_HBSTLEN_SHIFT;
	p->घातer_करोwn = DWC2_POWER_DOWN_PARAM_NONE;
पूर्ण

अटल व्योम dwc2_set_ltq_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->otg_cap = 2;
	p->host_rx_fअगरo_size = 288;
	p->host_nperio_tx_fअगरo_size = 128;
	p->host_perio_tx_fअगरo_size = 96;
	p->max_transfer_size = 65535;
	p->max_packet_count = 511;
	p->ahbcfg = GAHBCFG_HBSTLEN_INCR16 <<
		GAHBCFG_HBSTLEN_SHIFT;
पूर्ण

अटल व्योम dwc2_set_amlogic_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->otg_cap = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
	p->speed = DWC2_SPEED_PARAM_HIGH;
	p->host_rx_fअगरo_size = 512;
	p->host_nperio_tx_fअगरo_size = 500;
	p->host_perio_tx_fअगरo_size = 500;
	p->host_channels = 16;
	p->phy_type = DWC2_PHY_TYPE_PARAM_UTMI;
	p->ahbcfg = GAHBCFG_HBSTLEN_INCR8 <<
		GAHBCFG_HBSTLEN_SHIFT;
	p->घातer_करोwn = DWC2_POWER_DOWN_PARAM_NONE;
पूर्ण

अटल व्योम dwc2_set_amlogic_g12a_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->lpm = false;
	p->lpm_घड़ी_gating = false;
	p->besl = false;
	p->hird_threshold_en = false;
पूर्ण

अटल व्योम dwc2_set_amcc_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->ahbcfg = GAHBCFG_HBSTLEN_INCR16 << GAHBCFG_HBSTLEN_SHIFT;
पूर्ण

अटल व्योम dwc2_set_sपंचांग32f4x9_fsotg_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->otg_cap = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
	p->speed = DWC2_SPEED_PARAM_FULL;
	p->host_rx_fअगरo_size = 128;
	p->host_nperio_tx_fअगरo_size = 96;
	p->host_perio_tx_fअगरo_size = 96;
	p->max_packet_count = 256;
	p->phy_type = DWC2_PHY_TYPE_PARAM_FS;
	p->i2c_enable = false;
	p->activate_sपंचांग_fs_transceiver = true;
पूर्ण

अटल व्योम dwc2_set_sपंचांग32f7_hsotg_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->host_rx_fअगरo_size = 622;
	p->host_nperio_tx_fअगरo_size = 128;
	p->host_perio_tx_fअगरo_size = 256;
पूर्ण

अटल व्योम dwc2_set_sपंचांग32mp15_fsotg_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->otg_cap = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
	p->speed = DWC2_SPEED_PARAM_FULL;
	p->host_rx_fअगरo_size = 128;
	p->host_nperio_tx_fअगरo_size = 96;
	p->host_perio_tx_fअगरo_size = 96;
	p->max_packet_count = 256;
	p->phy_type = DWC2_PHY_TYPE_PARAM_FS;
	p->i2c_enable = false;
	p->activate_sपंचांग_fs_transceiver = true;
	p->activate_sपंचांग_id_vb_detection = true;
	p->ahbcfg = GAHBCFG_HBSTLEN_INCR16 << GAHBCFG_HBSTLEN_SHIFT;
	p->घातer_करोwn = DWC2_POWER_DOWN_PARAM_NONE;
	p->host_support_fs_ls_low_घातer = true;
	p->host_ls_low_घातer_phy_clk = true;
पूर्ण

अटल व्योम dwc2_set_sपंचांग32mp15_hsotg_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->otg_cap = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
	p->activate_sपंचांग_id_vb_detection = !device_property_पढ़ो_bool(hsotg->dev, "usb-role-switch");
	p->host_rx_fअगरo_size = 440;
	p->host_nperio_tx_fअगरo_size = 256;
	p->host_perio_tx_fअगरo_size = 256;
	p->ahbcfg = GAHBCFG_HBSTLEN_INCR16 << GAHBCFG_HBSTLEN_SHIFT;
	p->घातer_करोwn = DWC2_POWER_DOWN_PARAM_NONE;
	p->lpm = false;
	p->lpm_घड़ी_gating = false;
	p->besl = false;
	p->hird_threshold_en = false;
पूर्ण

स्थिर काष्ठा of_device_id dwc2_of_match_table[] = अणु
	अणु .compatible = "brcm,bcm2835-usb", .data = dwc2_set_bcm_params पूर्ण,
	अणु .compatible = "hisilicon,hi6220-usb", .data = dwc2_set_his_params  पूर्ण,
	अणु .compatible = "rockchip,rk3066-usb", .data = dwc2_set_rk_params पूर्ण,
	अणु .compatible = "lantiq,arx100-usb", .data = dwc2_set_ltq_params पूर्ण,
	अणु .compatible = "lantiq,xrx200-usb", .data = dwc2_set_ltq_params पूर्ण,
	अणु .compatible = "snps,dwc2" पूर्ण,
	अणु .compatible = "samsung,s3c6400-hsotg",
	  .data = dwc2_set_s3c6400_params पूर्ण,
	अणु .compatible = "amlogic,meson8-usb",
	  .data = dwc2_set_amlogic_params पूर्ण,
	अणु .compatible = "amlogic,meson8b-usb",
	  .data = dwc2_set_amlogic_params पूर्ण,
	अणु .compatible = "amlogic,meson-gxbb-usb",
	  .data = dwc2_set_amlogic_params पूर्ण,
	अणु .compatible = "amlogic,meson-g12a-usb",
	  .data = dwc2_set_amlogic_g12a_params पूर्ण,
	अणु .compatible = "amcc,dwc-otg", .data = dwc2_set_amcc_params पूर्ण,
	अणु .compatible = "apm,apm82181-dwc-otg", .data = dwc2_set_amcc_params पूर्ण,
	अणु .compatible = "st,stm32f4x9-fsotg",
	  .data = dwc2_set_sपंचांग32f4x9_fsotg_params पूर्ण,
	अणु .compatible = "st,stm32f4x9-hsotg" पूर्ण,
	अणु .compatible = "st,stm32f7-hsotg",
	  .data = dwc2_set_sपंचांग32f7_hsotg_params पूर्ण,
	अणु .compatible = "st,stm32mp15-fsotg",
	  .data = dwc2_set_sपंचांग32mp15_fsotg_params पूर्ण,
	अणु .compatible = "st,stm32mp15-hsotg",
	  .data = dwc2_set_sपंचांग32mp15_hsotg_params पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dwc2_of_match_table);

स्थिर काष्ठा acpi_device_id dwc2_acpi_match[] = अणु
	अणु "BCM2848", (kernel_uदीर्घ_t)dwc2_set_bcm_params पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dwc2_acpi_match);

अटल व्योम dwc2_set_param_otg_cap(काष्ठा dwc2_hsotg *hsotg)
अणु
	u8 val;

	चयन (hsotg->hw_params.op_mode) अणु
	हाल GHWCFG2_OP_MODE_HNP_SRP_CAPABLE:
		val = DWC2_CAP_PARAM_HNP_SRP_CAPABLE;
		अवरोध;
	हाल GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE:
	हाल GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE:
	हाल GHWCFG2_OP_MODE_SRP_CAPABLE_HOST:
		val = DWC2_CAP_PARAM_SRP_ONLY_CAPABLE;
		अवरोध;
	शेष:
		val = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
		अवरोध;
	पूर्ण

	hsotg->params.otg_cap = val;
पूर्ण

अटल व्योम dwc2_set_param_phy_type(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक val;
	u32 hs_phy_type = hsotg->hw_params.hs_phy_type;

	val = DWC2_PHY_TYPE_PARAM_FS;
	अगर (hs_phy_type != GHWCFG2_HS_PHY_TYPE_NOT_SUPPORTED) अणु
		अगर (hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI ||
		    hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI_ULPI)
			val = DWC2_PHY_TYPE_PARAM_UTMI;
		अन्यथा
			val = DWC2_PHY_TYPE_PARAM_ULPI;
	पूर्ण

	अगर (dwc2_is_fs_iot(hsotg))
		hsotg->params.phy_type = DWC2_PHY_TYPE_PARAM_FS;

	hsotg->params.phy_type = val;
पूर्ण

अटल व्योम dwc2_set_param_speed(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक val;

	val = hsotg->params.phy_type == DWC2_PHY_TYPE_PARAM_FS ?
		DWC2_SPEED_PARAM_FULL : DWC2_SPEED_PARAM_HIGH;

	अगर (dwc2_is_fs_iot(hsotg))
		val = DWC2_SPEED_PARAM_FULL;

	अगर (dwc2_is_hs_iot(hsotg))
		val = DWC2_SPEED_PARAM_HIGH;

	hsotg->params.speed = val;
पूर्ण

अटल व्योम dwc2_set_param_phy_uपंचांगi_width(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक val;

	val = (hsotg->hw_params.uपंचांगi_phy_data_width ==
	       GHWCFG4_UTMI_PHY_DATA_WIDTH_8) ? 8 : 16;

	अगर (hsotg->phy) अणु
		/*
		 * If using the generic PHY framework, check अगर the PHY bus
		 * width is 8-bit and set the phyअगर appropriately.
		 */
		अगर (phy_get_bus_width(hsotg->phy) == 8)
			val = 8;
	पूर्ण

	hsotg->params.phy_uपंचांगi_width = val;
पूर्ण

अटल व्योम dwc2_set_param_tx_fअगरo_sizes(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;
	पूर्णांक depth_average;
	पूर्णांक fअगरo_count;
	पूर्णांक i;

	fअगरo_count = dwc2_hsotg_tx_fअगरo_count(hsotg);

	स_रखो(p->g_tx_fअगरo_size, 0, माप(p->g_tx_fअगरo_size));
	depth_average = dwc2_hsotg_tx_fअगरo_average_depth(hsotg);
	क्रम (i = 1; i <= fअगरo_count; i++)
		p->g_tx_fअगरo_size[i] = depth_average;
पूर्ण

अटल व्योम dwc2_set_param_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक val;

	अगर (hsotg->hw_params.hibernation)
		val = DWC2_POWER_DOWN_PARAM_HIBERNATION;
	अन्यथा अगर (hsotg->hw_params.घातer_optimized)
		val = DWC2_POWER_DOWN_PARAM_PARTIAL;
	अन्यथा
		val = DWC2_POWER_DOWN_PARAM_NONE;

	hsotg->params.घातer_करोwn = val;
पूर्ण

अटल व्योम dwc2_set_param_lpm(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;

	p->lpm = hsotg->hw_params.lpm_mode;
	अगर (p->lpm) अणु
		p->lpm_घड़ी_gating = true;
		p->besl = true;
		p->hird_threshold_en = true;
		p->hird_threshold = 4;
	पूर्ण अन्यथा अणु
		p->lpm_घड़ी_gating = false;
		p->besl = false;
		p->hird_threshold_en = false;
	पूर्ण
पूर्ण

/**
 * dwc2_set_शेष_params() - Set all core parameters to their
 * स्वतः-detected शेष values.
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 */
अटल व्योम dwc2_set_शेष_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hw_params *hw = &hsotg->hw_params;
	काष्ठा dwc2_core_params *p = &hsotg->params;
	bool dma_capable = !(hw->arch == GHWCFG2_SLAVE_ONLY_ARCH);

	dwc2_set_param_otg_cap(hsotg);
	dwc2_set_param_phy_type(hsotg);
	dwc2_set_param_speed(hsotg);
	dwc2_set_param_phy_uपंचांगi_width(hsotg);
	dwc2_set_param_घातer_करोwn(hsotg);
	dwc2_set_param_lpm(hsotg);
	p->phy_ulpi_ddr = false;
	p->phy_ulpi_ext_vbus = false;

	p->enable_dynamic_fअगरo = hw->enable_dynamic_fअगरo;
	p->en_multiple_tx_fअगरo = hw->en_multiple_tx_fअगरo;
	p->i2c_enable = hw->i2c_enable;
	p->acg_enable = hw->acg_enable;
	p->ulpi_fs_ls = false;
	p->ts_dline = false;
	p->reload_ctl = (hw->snpsid >= DWC2_CORE_REV_2_92a);
	p->uframe_sched = true;
	p->बाह्यal_id_pin_ctl = false;
	p->ipg_isoc_en = false;
	p->service_पूर्णांकerval = false;
	p->max_packet_count = hw->max_packet_count;
	p->max_transfer_size = hw->max_transfer_size;
	p->ahbcfg = GAHBCFG_HBSTLEN_INCR << GAHBCFG_HBSTLEN_SHIFT;
	p->ref_clk_per = 33333;
	p->sof_cnt_wkup_alert = 100;

	अगर ((hsotg->dr_mode == USB_DR_MODE_HOST) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) अणु
		p->host_dma = dma_capable;
		p->dma_desc_enable = false;
		p->dma_desc_fs_enable = false;
		p->host_support_fs_ls_low_घातer = false;
		p->host_ls_low_घातer_phy_clk = false;
		p->host_channels = hw->host_channels;
		p->host_rx_fअगरo_size = hw->rx_fअगरo_size;
		p->host_nperio_tx_fअगरo_size = hw->host_nperio_tx_fअगरo_size;
		p->host_perio_tx_fअगरo_size = hw->host_perio_tx_fअगरo_size;
	पूर्ण

	अगर ((hsotg->dr_mode == USB_DR_MODE_PERIPHERAL) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) अणु
		p->g_dma = dma_capable;
		p->g_dma_desc = hw->dma_desc_enable;

		/*
		 * The values क्रम g_rx_fअगरo_size (2048) and
		 * g_np_tx_fअगरo_size (1024) come from the legacy s3c
		 * gadget driver. These शेषs have been hard-coded
		 * क्रम some समय so many platक्रमms depend on these
		 * values. Leave them as शेषs क्रम now and only
		 * स्वतः-detect अगर the hardware करोes not support the
		 * शेष.
		 */
		p->g_rx_fअगरo_size = 2048;
		p->g_np_tx_fअगरo_size = 1024;
		dwc2_set_param_tx_fअगरo_sizes(hsotg);
	पूर्ण
पूर्ण

/**
 * dwc2_get_device_properties() - Read in device properties.
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 * Read in the device properties and adjust core parameters अगर needed.
 */
अटल व्योम dwc2_get_device_properties(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_core_params *p = &hsotg->params;
	पूर्णांक num;

	अगर ((hsotg->dr_mode == USB_DR_MODE_PERIPHERAL) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) अणु
		device_property_पढ़ो_u32(hsotg->dev, "g-rx-fifo-size",
					 &p->g_rx_fअगरo_size);

		device_property_पढ़ो_u32(hsotg->dev, "g-np-tx-fifo-size",
					 &p->g_np_tx_fअगरo_size);

		num = device_property_count_u32(hsotg->dev, "g-tx-fifo-size");
		अगर (num > 0) अणु
			num = min(num, 15);
			स_रखो(p->g_tx_fअगरo_size, 0,
			       माप(p->g_tx_fअगरo_size));
			device_property_पढ़ो_u32_array(hsotg->dev,
						       "g-tx-fifo-size",
						       &p->g_tx_fअगरo_size[1],
						       num);
		पूर्ण
	पूर्ण

	अगर (of_find_property(hsotg->dev->of_node, "disable-over-current", शून्य))
		p->oc_disable = true;
पूर्ण

अटल व्योम dwc2_check_param_otg_cap(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक valid = 1;

	चयन (hsotg->params.otg_cap) अणु
	हाल DWC2_CAP_PARAM_HNP_SRP_CAPABLE:
		अगर (hsotg->hw_params.op_mode != GHWCFG2_OP_MODE_HNP_SRP_CAPABLE)
			valid = 0;
		अवरोध;
	हाल DWC2_CAP_PARAM_SRP_ONLY_CAPABLE:
		चयन (hsotg->hw_params.op_mode) अणु
		हाल GHWCFG2_OP_MODE_HNP_SRP_CAPABLE:
		हाल GHWCFG2_OP_MODE_SRP_ONLY_CAPABLE:
		हाल GHWCFG2_OP_MODE_SRP_CAPABLE_DEVICE:
		हाल GHWCFG2_OP_MODE_SRP_CAPABLE_HOST:
			अवरोध;
		शेष:
			valid = 0;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE:
		/* always valid */
		अवरोध;
	शेष:
		valid = 0;
		अवरोध;
	पूर्ण

	अगर (!valid)
		dwc2_set_param_otg_cap(hsotg);
पूर्ण

अटल व्योम dwc2_check_param_phy_type(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक valid = 0;
	u32 hs_phy_type;
	u32 fs_phy_type;

	hs_phy_type = hsotg->hw_params.hs_phy_type;
	fs_phy_type = hsotg->hw_params.fs_phy_type;

	चयन (hsotg->params.phy_type) अणु
	हाल DWC2_PHY_TYPE_PARAM_FS:
		अगर (fs_phy_type == GHWCFG2_FS_PHY_TYPE_DEDICATED)
			valid = 1;
		अवरोध;
	हाल DWC2_PHY_TYPE_PARAM_UTMI:
		अगर ((hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI) ||
		    (hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI_ULPI))
			valid = 1;
		अवरोध;
	हाल DWC2_PHY_TYPE_PARAM_ULPI:
		अगर ((hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI) ||
		    (hs_phy_type == GHWCFG2_HS_PHY_TYPE_UTMI_ULPI))
			valid = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!valid)
		dwc2_set_param_phy_type(hsotg);
पूर्ण

अटल व्योम dwc2_check_param_speed(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक valid = 1;
	पूर्णांक phy_type = hsotg->params.phy_type;
	पूर्णांक speed = hsotg->params.speed;

	चयन (speed) अणु
	हाल DWC2_SPEED_PARAM_HIGH:
		अगर ((hsotg->params.speed == DWC2_SPEED_PARAM_HIGH) &&
		    (phy_type == DWC2_PHY_TYPE_PARAM_FS))
			valid = 0;
		अवरोध;
	हाल DWC2_SPEED_PARAM_FULL:
	हाल DWC2_SPEED_PARAM_LOW:
		अवरोध;
	शेष:
		valid = 0;
		अवरोध;
	पूर्ण

	अगर (!valid)
		dwc2_set_param_speed(hsotg);
पूर्ण

अटल व्योम dwc2_check_param_phy_uपंचांगi_width(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक valid = 0;
	पूर्णांक param = hsotg->params.phy_uपंचांगi_width;
	पूर्णांक width = hsotg->hw_params.uपंचांगi_phy_data_width;

	चयन (width) अणु
	हाल GHWCFG4_UTMI_PHY_DATA_WIDTH_8:
		valid = (param == 8);
		अवरोध;
	हाल GHWCFG4_UTMI_PHY_DATA_WIDTH_16:
		valid = (param == 16);
		अवरोध;
	हाल GHWCFG4_UTMI_PHY_DATA_WIDTH_8_OR_16:
		valid = (param == 8 || param == 16);
		अवरोध;
	पूर्ण

	अगर (!valid)
		dwc2_set_param_phy_uपंचांगi_width(hsotg);
पूर्ण

अटल व्योम dwc2_check_param_घातer_करोwn(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक param = hsotg->params.घातer_करोwn;

	चयन (param) अणु
	हाल DWC2_POWER_DOWN_PARAM_NONE:
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_PARTIAL:
		अगर (hsotg->hw_params.घातer_optimized)
			अवरोध;
		dev_dbg(hsotg->dev,
			"Partial power down isn't supported by HW\n");
		param = DWC2_POWER_DOWN_PARAM_NONE;
		अवरोध;
	हाल DWC2_POWER_DOWN_PARAM_HIBERNATION:
		अगर (hsotg->hw_params.hibernation)
			अवरोध;
		dev_dbg(hsotg->dev,
			"Hibernation isn't supported by HW\n");
		param = DWC2_POWER_DOWN_PARAM_NONE;
		अवरोध;
	शेष:
		dev_err(hsotg->dev,
			"%s: Invalid parameter power_down=%d\n",
			__func__, param);
		param = DWC2_POWER_DOWN_PARAM_NONE;
		अवरोध;
	पूर्ण

	hsotg->params.घातer_करोwn = param;
पूर्ण

अटल व्योम dwc2_check_param_tx_fअगरo_sizes(काष्ठा dwc2_hsotg *hsotg)
अणु
	पूर्णांक fअगरo_count;
	पूर्णांक fअगरo;
	पूर्णांक min;
	u32 total = 0;
	u32 dptxfszn;

	fअगरo_count = dwc2_hsotg_tx_fअगरo_count(hsotg);
	min = hsotg->hw_params.en_multiple_tx_fअगरo ? 16 : 4;

	क्रम (fअगरo = 1; fअगरo <= fअगरo_count; fअगरo++)
		total += hsotg->params.g_tx_fअगरo_size[fअगरo];

	अगर (total > dwc2_hsotg_tx_fअगरo_total_depth(hsotg) || !total) अणु
		dev_warn(hsotg->dev, "%s: Invalid parameter g-tx-fifo-size, setting to default average\n",
			 __func__);
		dwc2_set_param_tx_fअगरo_sizes(hsotg);
	पूर्ण

	क्रम (fअगरo = 1; fअगरo <= fअगरo_count; fअगरo++) अणु
		dptxfszn = hsotg->hw_params.g_tx_fअगरo_size[fअगरo];

		अगर (hsotg->params.g_tx_fअगरo_size[fअगरo] < min ||
		    hsotg->params.g_tx_fअगरo_size[fअगरo] >  dptxfszn) अणु
			dev_warn(hsotg->dev, "%s: Invalid parameter g_tx_fifo_size[%d]=%d\n",
				 __func__, fअगरo,
				 hsotg->params.g_tx_fअगरo_size[fअगरo]);
			hsotg->params.g_tx_fअगरo_size[fअगरo] = dptxfszn;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा CHECK_RANGE(_param, _min, _max, _def) करो अणु			\
		अगर ((पूर्णांक)(hsotg->params._param) < (_min) ||		\
		    (hsotg->params._param) > (_max)) अणु			\
			dev_warn(hsotg->dev, "%s: Invalid parameter %s=%d\n", \
				 __func__, #_param, hsotg->params._param); \
			hsotg->params._param = (_def);			\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा CHECK_BOOL(_param, _check) करो अणु					\
		अगर (hsotg->params._param && !(_check)) अणु		\
			dev_warn(hsotg->dev, "%s: Invalid parameter %s=%d\n", \
				 __func__, #_param, hsotg->params._param); \
			hsotg->params._param = false;			\
		पूर्ण							\
	पूर्ण जबतक (0)

अटल व्योम dwc2_check_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hw_params *hw = &hsotg->hw_params;
	काष्ठा dwc2_core_params *p = &hsotg->params;
	bool dma_capable = !(hw->arch == GHWCFG2_SLAVE_ONLY_ARCH);

	dwc2_check_param_otg_cap(hsotg);
	dwc2_check_param_phy_type(hsotg);
	dwc2_check_param_speed(hsotg);
	dwc2_check_param_phy_uपंचांगi_width(hsotg);
	dwc2_check_param_घातer_करोwn(hsotg);
	CHECK_BOOL(enable_dynamic_fअगरo, hw->enable_dynamic_fअगरo);
	CHECK_BOOL(en_multiple_tx_fअगरo, hw->en_multiple_tx_fअगरo);
	CHECK_BOOL(i2c_enable, hw->i2c_enable);
	CHECK_BOOL(ipg_isoc_en, hw->ipg_isoc_en);
	CHECK_BOOL(acg_enable, hw->acg_enable);
	CHECK_BOOL(reload_ctl, (hsotg->hw_params.snpsid > DWC2_CORE_REV_2_92a));
	CHECK_BOOL(lpm, (hsotg->hw_params.snpsid >= DWC2_CORE_REV_2_80a));
	CHECK_BOOL(lpm, hw->lpm_mode);
	CHECK_BOOL(lpm_घड़ी_gating, hsotg->params.lpm);
	CHECK_BOOL(besl, hsotg->params.lpm);
	CHECK_BOOL(besl, (hsotg->hw_params.snpsid >= DWC2_CORE_REV_3_00a));
	CHECK_BOOL(hird_threshold_en, hsotg->params.lpm);
	CHECK_RANGE(hird_threshold, 0, hsotg->params.besl ? 12 : 7, 0);
	CHECK_BOOL(service_पूर्णांकerval, hw->service_पूर्णांकerval_mode);
	CHECK_RANGE(max_packet_count,
		    15, hw->max_packet_count,
		    hw->max_packet_count);
	CHECK_RANGE(max_transfer_size,
		    2047, hw->max_transfer_size,
		    hw->max_transfer_size);

	अगर ((hsotg->dr_mode == USB_DR_MODE_HOST) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) अणु
		CHECK_BOOL(host_dma, dma_capable);
		CHECK_BOOL(dma_desc_enable, p->host_dma);
		CHECK_BOOL(dma_desc_fs_enable, p->dma_desc_enable);
		CHECK_BOOL(host_ls_low_घातer_phy_clk,
			   p->phy_type == DWC2_PHY_TYPE_PARAM_FS);
		CHECK_RANGE(host_channels,
			    1, hw->host_channels,
			    hw->host_channels);
		CHECK_RANGE(host_rx_fअगरo_size,
			    16, hw->rx_fअगरo_size,
			    hw->rx_fअगरo_size);
		CHECK_RANGE(host_nperio_tx_fअगरo_size,
			    16, hw->host_nperio_tx_fअगरo_size,
			    hw->host_nperio_tx_fअगरo_size);
		CHECK_RANGE(host_perio_tx_fअगरo_size,
			    16, hw->host_perio_tx_fअगरo_size,
			    hw->host_perio_tx_fअगरo_size);
	पूर्ण

	अगर ((hsotg->dr_mode == USB_DR_MODE_PERIPHERAL) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) अणु
		CHECK_BOOL(g_dma, dma_capable);
		CHECK_BOOL(g_dma_desc, (p->g_dma && hw->dma_desc_enable));
		CHECK_RANGE(g_rx_fअगरo_size,
			    16, hw->rx_fअगरo_size,
			    hw->rx_fअगरo_size);
		CHECK_RANGE(g_np_tx_fअगरo_size,
			    16, hw->dev_nperio_tx_fअगरo_size,
			    hw->dev_nperio_tx_fअगरo_size);
		dwc2_check_param_tx_fअगरo_sizes(hsotg);
	पूर्ण
पूर्ण

/*
 * Gets host hardware parameters. Forces host mode अगर not currently in
 * host mode. Should be called immediately after a core soft reset in
 * order to get the reset values.
 */
अटल व्योम dwc2_get_host_hwparams(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hw_params *hw = &hsotg->hw_params;
	u32 gnptxfsiz;
	u32 hptxfsiz;

	अगर (hsotg->dr_mode == USB_DR_MODE_PERIPHERAL)
		वापस;

	dwc2_क्रमce_mode(hsotg, true);

	gnptxfsiz = dwc2_पढ़ोl(hsotg, GNPTXFSIZ);
	hptxfsiz = dwc2_पढ़ोl(hsotg, HPTXFSIZ);

	hw->host_nperio_tx_fअगरo_size = (gnptxfsiz & FIFOSIZE_DEPTH_MASK) >>
				       FIFOSIZE_DEPTH_SHIFT;
	hw->host_perio_tx_fअगरo_size = (hptxfsiz & FIFOSIZE_DEPTH_MASK) >>
				      FIFOSIZE_DEPTH_SHIFT;
पूर्ण

/*
 * Gets device hardware parameters. Forces device mode अगर not
 * currently in device mode. Should be called immediately after a core
 * soft reset in order to get the reset values.
 */
अटल व्योम dwc2_get_dev_hwparams(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hw_params *hw = &hsotg->hw_params;
	u32 gnptxfsiz;
	पूर्णांक fअगरo, fअगरo_count;

	अगर (hsotg->dr_mode == USB_DR_MODE_HOST)
		वापस;

	dwc2_क्रमce_mode(hsotg, false);

	gnptxfsiz = dwc2_पढ़ोl(hsotg, GNPTXFSIZ);

	fअगरo_count = dwc2_hsotg_tx_fअगरo_count(hsotg);

	क्रम (fअगरo = 1; fअगरo <= fअगरo_count; fअगरo++) अणु
		hw->g_tx_fअगरo_size[fअगरo] =
			(dwc2_पढ़ोl(hsotg, DPTXFSIZN(fअगरo)) &
			 FIFOSIZE_DEPTH_MASK) >> FIFOSIZE_DEPTH_SHIFT;
	पूर्ण

	hw->dev_nperio_tx_fअगरo_size = (gnptxfsiz & FIFOSIZE_DEPTH_MASK) >>
				       FIFOSIZE_DEPTH_SHIFT;
पूर्ण

/**
 * During device initialization, पढ़ो various hardware configuration
 * रेजिस्टरs and पूर्णांकerpret the contents.
 *
 * @hsotg: Programming view of the DWC_otg controller
 *
 */
पूर्णांक dwc2_get_hwparams(काष्ठा dwc2_hsotg *hsotg)
अणु
	काष्ठा dwc2_hw_params *hw = &hsotg->hw_params;
	अचिन्हित पूर्णांक width;
	u32 hwcfg1, hwcfg2, hwcfg3, hwcfg4;
	u32 grxfsiz;

	hwcfg1 = dwc2_पढ़ोl(hsotg, GHWCFG1);
	hwcfg2 = dwc2_पढ़ोl(hsotg, GHWCFG2);
	hwcfg3 = dwc2_पढ़ोl(hsotg, GHWCFG3);
	hwcfg4 = dwc2_पढ़ोl(hsotg, GHWCFG4);
	grxfsiz = dwc2_पढ़ोl(hsotg, GRXFSIZ);

	/* hwcfg1 */
	hw->dev_ep_dirs = hwcfg1;

	/* hwcfg2 */
	hw->op_mode = (hwcfg2 & GHWCFG2_OP_MODE_MASK) >>
		      GHWCFG2_OP_MODE_SHIFT;
	hw->arch = (hwcfg2 & GHWCFG2_ARCHITECTURE_MASK) >>
		   GHWCFG2_ARCHITECTURE_SHIFT;
	hw->enable_dynamic_fअगरo = !!(hwcfg2 & GHWCFG2_DYNAMIC_FIFO);
	hw->host_channels = 1 + ((hwcfg2 & GHWCFG2_NUM_HOST_CHAN_MASK) >>
				GHWCFG2_NUM_HOST_CHAN_SHIFT);
	hw->hs_phy_type = (hwcfg2 & GHWCFG2_HS_PHY_TYPE_MASK) >>
			  GHWCFG2_HS_PHY_TYPE_SHIFT;
	hw->fs_phy_type = (hwcfg2 & GHWCFG2_FS_PHY_TYPE_MASK) >>
			  GHWCFG2_FS_PHY_TYPE_SHIFT;
	hw->num_dev_ep = (hwcfg2 & GHWCFG2_NUM_DEV_EP_MASK) >>
			 GHWCFG2_NUM_DEV_EP_SHIFT;
	hw->nperio_tx_q_depth =
		(hwcfg2 & GHWCFG2_NONPERIO_TX_Q_DEPTH_MASK) >>
		GHWCFG2_NONPERIO_TX_Q_DEPTH_SHIFT << 1;
	hw->host_perio_tx_q_depth =
		(hwcfg2 & GHWCFG2_HOST_PERIO_TX_Q_DEPTH_MASK) >>
		GHWCFG2_HOST_PERIO_TX_Q_DEPTH_SHIFT << 1;
	hw->dev_token_q_depth =
		(hwcfg2 & GHWCFG2_DEV_TOKEN_Q_DEPTH_MASK) >>
		GHWCFG2_DEV_TOKEN_Q_DEPTH_SHIFT;

	/* hwcfg3 */
	width = (hwcfg3 & GHWCFG3_XFER_SIZE_CNTR_WIDTH_MASK) >>
		GHWCFG3_XFER_SIZE_CNTR_WIDTH_SHIFT;
	hw->max_transfer_size = (1 << (width + 11)) - 1;
	width = (hwcfg3 & GHWCFG3_PACKET_SIZE_CNTR_WIDTH_MASK) >>
		GHWCFG3_PACKET_SIZE_CNTR_WIDTH_SHIFT;
	hw->max_packet_count = (1 << (width + 4)) - 1;
	hw->i2c_enable = !!(hwcfg3 & GHWCFG3_I2C);
	hw->total_fअगरo_size = (hwcfg3 & GHWCFG3_DFIFO_DEPTH_MASK) >>
			      GHWCFG3_DFIFO_DEPTH_SHIFT;
	hw->lpm_mode = !!(hwcfg3 & GHWCFG3_OTG_LPM_EN);

	/* hwcfg4 */
	hw->en_multiple_tx_fअगरo = !!(hwcfg4 & GHWCFG4_DED_FIFO_EN);
	hw->num_dev_perio_in_ep = (hwcfg4 & GHWCFG4_NUM_DEV_PERIO_IN_EP_MASK) >>
				  GHWCFG4_NUM_DEV_PERIO_IN_EP_SHIFT;
	hw->num_dev_in_eps = (hwcfg4 & GHWCFG4_NUM_IN_EPS_MASK) >>
			     GHWCFG4_NUM_IN_EPS_SHIFT;
	hw->dma_desc_enable = !!(hwcfg4 & GHWCFG4_DESC_DMA);
	hw->घातer_optimized = !!(hwcfg4 & GHWCFG4_POWER_OPTIMIZ);
	hw->hibernation = !!(hwcfg4 & GHWCFG4_HIBER);
	hw->uपंचांगi_phy_data_width = (hwcfg4 & GHWCFG4_UTMI_PHY_DATA_WIDTH_MASK) >>
				  GHWCFG4_UTMI_PHY_DATA_WIDTH_SHIFT;
	hw->acg_enable = !!(hwcfg4 & GHWCFG4_ACG_SUPPORTED);
	hw->ipg_isoc_en = !!(hwcfg4 & GHWCFG4_IPG_ISOC_SUPPORTED);
	hw->service_पूर्णांकerval_mode = !!(hwcfg4 &
				       GHWCFG4_SERVICE_INTERVAL_SUPPORTED);

	/* fअगरo sizes */
	hw->rx_fअगरo_size = (grxfsiz & GRXFSIZ_DEPTH_MASK) >>
				GRXFSIZ_DEPTH_SHIFT;
	/*
	 * Host specअगरic hardware parameters. Reading these parameters
	 * requires the controller to be in host mode. The mode will
	 * be क्रमced, अगर necessary, to पढ़ो these values.
	 */
	dwc2_get_host_hwparams(hsotg);
	dwc2_get_dev_hwparams(hsotg);

	वापस 0;
पूर्ण

प्रकार व्योम (*set_params_cb)(काष्ठा dwc2_hsotg *data);

पूर्णांक dwc2_init_params(काष्ठा dwc2_hsotg *hsotg)
अणु
	स्थिर काष्ठा of_device_id *match;
	set_params_cb set_params;

	dwc2_set_शेष_params(hsotg);
	dwc2_get_device_properties(hsotg);

	match = of_match_device(dwc2_of_match_table, hsotg->dev);
	अगर (match && match->data) अणु
		set_params = match->data;
		set_params(hsotg);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा acpi_device_id *amatch;

		amatch = acpi_match_device(dwc2_acpi_match, hsotg->dev);
		अगर (amatch && amatch->driver_data) अणु
			set_params = (set_params_cb)amatch->driver_data;
			set_params(hsotg);
		पूर्ण
	पूर्ण

	dwc2_check_params(hsotg);

	वापस 0;
पूर्ण
