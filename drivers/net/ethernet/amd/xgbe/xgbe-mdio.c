<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 *
 * This file is मुक्त software; you may copy, redistribute and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or (at
 * your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * License 2: Modअगरied BSD
 *
 * Copyright (c) 2014-2016 Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *     The Synopsys DWC ETHER XGMAC Software Driver and करोcumentation
 *     (hereinafter "Software") is an unsupported proprietary work of Synopsys,
 *     Inc. unless otherwise expressly agreed to in writing between Synopsys
 *     and you.
 *
 *     The Software IS NOT an item of Licensed Software or Licensed Product
 *     under any End User Software License Agreement or Agreement क्रम Licensed
 *     Product with Synopsys or any supplement thereto.  Permission is hereby
 *     granted, मुक्त of अक्षरge, to any person obtaining a copy of this software
 *     annotated with this license and the Software, to deal in the Software
 *     without restriction, including without limitation the rights to use,
 *     copy, modअगरy, merge, publish, distribute, sublicense, and/or sell copies
 *     of the Software, and to permit persons to whom the Software is furnished
 *     to करो so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included
 *     in all copies or substantial portions of the Software.
 *
 *     THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS"
 *     BASIS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *     TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *     PARTICULAR PURPOSE ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS
 *     BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *     INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *     CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *     ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *     THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>
#समावेश <linux/bitops.h>
#समावेश <linux/jअगरfies.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

अटल पूर्णांक xgbe_phy_module_eeprom(काष्ठा xgbe_prv_data *pdata,
				  काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	अगर (!pdata->phy_अगर.phy_impl.module_eeprom)
		वापस -ENXIO;

	वापस pdata->phy_अगर.phy_impl.module_eeprom(pdata, eeprom, data);
पूर्ण

अटल पूर्णांक xgbe_phy_module_info(काष्ठा xgbe_prv_data *pdata,
				काष्ठा ethtool_modinfo *modinfo)
अणु
	अगर (!pdata->phy_अगर.phy_impl.module_info)
		वापस -ENXIO;

	वापस pdata->phy_अगर.phy_impl.module_info(pdata, modinfo);
पूर्ण

अटल व्योम xgbe_an37_clear_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT);
	reg &= ~XGBE_AN_CL37_INT_MASK;
	XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, reg);
पूर्ण

अटल व्योम xgbe_an37_disable_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL);
	reg &= ~XGBE_AN_CL37_INT_MASK;
	XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL, reg);

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL);
	reg &= ~XGBE_PCS_CL37_BP;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL, reg);
पूर्ण

अटल व्योम xgbe_an37_enable_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL);
	reg |= XGBE_PCS_CL37_BP;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_PCS_DIG_CTRL, reg);

	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL);
	reg |= XGBE_AN_CL37_INT_MASK;
	XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL, reg);
पूर्ण

अटल व्योम xgbe_an73_clear_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, 0);
पूर्ण

अटल व्योम xgbe_an73_disable_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, 0);
पूर्ण

अटल व्योम xgbe_an73_enable_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, XGBE_AN_CL73_INT_MASK);
पूर्ण

अटल व्योम xgbe_an_enable_पूर्णांकerrupts(काष्ठा xgbe_prv_data *pdata)
अणु
	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL73:
	हाल XGBE_AN_MODE_CL73_REDRV:
		xgbe_an73_enable_पूर्णांकerrupts(pdata);
		अवरोध;
	हाल XGBE_AN_MODE_CL37:
	हाल XGBE_AN_MODE_CL37_SGMII:
		xgbe_an37_enable_पूर्णांकerrupts(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xgbe_an_clear_पूर्णांकerrupts_all(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_an73_clear_पूर्णांकerrupts(pdata);
	xgbe_an37_clear_पूर्णांकerrupts(pdata);
पूर्ण

अटल व्योम xgbe_kr_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Set MAC to 10G speed */
	pdata->hw_अगर.set_speed(pdata, SPEED_10000);

	/* Call PHY implementation support to complete rate change */
	pdata->phy_अगर.phy_impl.set_mode(pdata, XGBE_MODE_KR);
पूर्ण

अटल व्योम xgbe_kx_2500_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Set MAC to 2.5G speed */
	pdata->hw_अगर.set_speed(pdata, SPEED_2500);

	/* Call PHY implementation support to complete rate change */
	pdata->phy_अगर.phy_impl.set_mode(pdata, XGBE_MODE_KX_2500);
पूर्ण

अटल व्योम xgbe_kx_1000_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Set MAC to 1G speed */
	pdata->hw_अगर.set_speed(pdata, SPEED_1000);

	/* Call PHY implementation support to complete rate change */
	pdata->phy_अगर.phy_impl.set_mode(pdata, XGBE_MODE_KX_1000);
पूर्ण

अटल व्योम xgbe_sfi_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	/* If a KR re-driver is present, change to KR mode instead */
	अगर (pdata->kr_redrv)
		वापस xgbe_kr_mode(pdata);

	/* Set MAC to 10G speed */
	pdata->hw_अगर.set_speed(pdata, SPEED_10000);

	/* Call PHY implementation support to complete rate change */
	pdata->phy_अगर.phy_impl.set_mode(pdata, XGBE_MODE_SFI);
पूर्ण

अटल व्योम xgbe_x_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Set MAC to 1G speed */
	pdata->hw_अगर.set_speed(pdata, SPEED_1000);

	/* Call PHY implementation support to complete rate change */
	pdata->phy_अगर.phy_impl.set_mode(pdata, XGBE_MODE_X);
पूर्ण

अटल व्योम xgbe_sgmii_1000_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Set MAC to 1G speed */
	pdata->hw_अगर.set_speed(pdata, SPEED_1000);

	/* Call PHY implementation support to complete rate change */
	pdata->phy_अगर.phy_impl.set_mode(pdata, XGBE_MODE_SGMII_1000);
पूर्ण

अटल व्योम xgbe_sgmii_100_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Set MAC to 1G speed */
	pdata->hw_अगर.set_speed(pdata, SPEED_1000);

	/* Call PHY implementation support to complete rate change */
	pdata->phy_अगर.phy_impl.set_mode(pdata, XGBE_MODE_SGMII_100);
पूर्ण

अटल क्रमागत xgbe_mode xgbe_cur_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस pdata->phy_अगर.phy_impl.cur_mode(pdata);
पूर्ण

अटल bool xgbe_in_kr_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस (xgbe_cur_mode(pdata) == XGBE_MODE_KR);
पूर्ण

अटल व्योम xgbe_change_mode(काष्ठा xgbe_prv_data *pdata,
			     क्रमागत xgbe_mode mode)
अणु
	चयन (mode) अणु
	हाल XGBE_MODE_KX_1000:
		xgbe_kx_1000_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_KX_2500:
		xgbe_kx_2500_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_KR:
		xgbe_kr_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_SGMII_100:
		xgbe_sgmii_100_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_SGMII_1000:
		xgbe_sgmii_1000_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_X:
		xgbe_x_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_SFI:
		xgbe_sfi_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_UNKNOWN:
		अवरोध;
	शेष:
		netअगर_dbg(pdata, link, pdata->netdev,
			  "invalid operation mode requested (%u)\n", mode);
	पूर्ण
पूर्ण

अटल व्योम xgbe_चयन_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_change_mode(pdata, pdata->phy_अगर.phy_impl.चयन_mode(pdata));
पूर्ण

अटल bool xgbe_set_mode(काष्ठा xgbe_prv_data *pdata,
			  क्रमागत xgbe_mode mode)
अणु
	अगर (mode == xgbe_cur_mode(pdata))
		वापस false;

	xgbe_change_mode(pdata, mode);

	वापस true;
पूर्ण

अटल bool xgbe_use_mode(काष्ठा xgbe_prv_data *pdata,
			  क्रमागत xgbe_mode mode)
अणु
	वापस pdata->phy_अगर.phy_impl.use_mode(pdata, mode);
पूर्ण

अटल व्योम xgbe_an37_set(काष्ठा xgbe_prv_data *pdata, bool enable,
			  bool restart)
अणु
	अचिन्हित पूर्णांक reg;

	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_CTRL1);
	reg &= ~MDIO_VEND2_CTRL1_AN_ENABLE;

	अगर (enable)
		reg |= MDIO_VEND2_CTRL1_AN_ENABLE;

	अगर (restart)
		reg |= MDIO_VEND2_CTRL1_AN_RESTART;

	XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_CTRL1, reg);
पूर्ण

अटल व्योम xgbe_an37_restart(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_an37_enable_पूर्णांकerrupts(pdata);
	xgbe_an37_set(pdata, true, true);

	netअगर_dbg(pdata, link, pdata->netdev, "CL37 AN enabled/restarted\n");
पूर्ण

अटल व्योम xgbe_an37_disable(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_an37_set(pdata, false, false);
	xgbe_an37_disable_पूर्णांकerrupts(pdata);

	netअगर_dbg(pdata, link, pdata->netdev, "CL37 AN disabled\n");
पूर्ण

अटल व्योम xgbe_an73_set(काष्ठा xgbe_prv_data *pdata, bool enable,
			  bool restart)
अणु
	अचिन्हित पूर्णांक reg;

	/* Disable KR training क्रम now */
	reg = XMDIO_READ(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL);
	reg &= ~XGBE_KR_TRAINING_ENABLE;
	XMDIO_WRITE(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL, reg);

	/* Update AN settings */
	reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_CTRL1);
	reg &= ~MDIO_AN_CTRL1_ENABLE;

	अगर (enable)
		reg |= MDIO_AN_CTRL1_ENABLE;

	अगर (restart)
		reg |= MDIO_AN_CTRL1_RESTART;

	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_CTRL1, reg);
पूर्ण

अटल व्योम xgbe_an73_restart(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_an73_enable_पूर्णांकerrupts(pdata);
	xgbe_an73_set(pdata, true, true);

	netअगर_dbg(pdata, link, pdata->netdev, "CL73 AN enabled/restarted\n");
पूर्ण

अटल व्योम xgbe_an73_disable(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_an73_set(pdata, false, false);
	xgbe_an73_disable_पूर्णांकerrupts(pdata);

	pdata->an_start = 0;

	netअगर_dbg(pdata, link, pdata->netdev, "CL73 AN disabled\n");
पूर्ण

अटल व्योम xgbe_an_restart(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (pdata->phy_अगर.phy_impl.an_pre)
		pdata->phy_अगर.phy_impl.an_pre(pdata);

	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL73:
	हाल XGBE_AN_MODE_CL73_REDRV:
		xgbe_an73_restart(pdata);
		अवरोध;
	हाल XGBE_AN_MODE_CL37:
	हाल XGBE_AN_MODE_CL37_SGMII:
		xgbe_an37_restart(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xgbe_an_disable(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (pdata->phy_अगर.phy_impl.an_post)
		pdata->phy_अगर.phy_impl.an_post(pdata);

	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL73:
	हाल XGBE_AN_MODE_CL73_REDRV:
		xgbe_an73_disable(pdata);
		अवरोध;
	हाल XGBE_AN_MODE_CL37:
	हाल XGBE_AN_MODE_CL37_SGMII:
		xgbe_an37_disable(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xgbe_an_disable_all(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_an73_disable(pdata);
	xgbe_an37_disable(pdata);
पूर्ण

अटल क्रमागत xgbe_an xgbe_an73_tx_training(काष्ठा xgbe_prv_data *pdata,
					  क्रमागत xgbe_rx *state)
अणु
	अचिन्हित पूर्णांक ad_reg, lp_reg, reg;

	*state = XGBE_RX_COMPLETE;

	/* If we're not in KR mode then we're करोne */
	अगर (!xgbe_in_kr_mode(pdata))
		वापस XGBE_AN_PAGE_RECEIVED;

	/* Enable/Disable FEC */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 2);

	reg = XMDIO_READ(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_FECCTRL);
	reg &= ~(MDIO_PMA_10GBR_FECABLE_ABLE | MDIO_PMA_10GBR_FECABLE_ERRABLE);
	अगर ((ad_reg & 0xc000) && (lp_reg & 0xc000))
		reg |= pdata->fec_ability;

	XMDIO_WRITE(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_FECCTRL, reg);

	/* Start KR training */
	अगर (pdata->phy_अगर.phy_impl.kr_training_pre)
		pdata->phy_अगर.phy_impl.kr_training_pre(pdata);

	reg = XMDIO_READ(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL);
	reg |= XGBE_KR_TRAINING_ENABLE;
	reg |= XGBE_KR_TRAINING_START;
	XMDIO_WRITE(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL, reg);

	netअगर_dbg(pdata, link, pdata->netdev,
		  "KR training initiated\n");

	अगर (pdata->phy_अगर.phy_impl.kr_training_post)
		pdata->phy_अगर.phy_impl.kr_training_post(pdata);

	वापस XGBE_AN_PAGE_RECEIVED;
पूर्ण

अटल क्रमागत xgbe_an xgbe_an73_tx_xnp(काष्ठा xgbe_prv_data *pdata,
				     क्रमागत xgbe_rx *state)
अणु
	u16 msg;

	*state = XGBE_RX_XNP;

	msg = XGBE_XNP_MCF_शून्य_MESSAGE;
	msg |= XGBE_XNP_MP_FORMATTED;

	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_XNP + 2, 0);
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_XNP + 1, 0);
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_XNP, msg);

	वापस XGBE_AN_PAGE_RECEIVED;
पूर्ण

अटल क्रमागत xgbe_an xgbe_an73_rx_bpa(काष्ठा xgbe_prv_data *pdata,
				     क्रमागत xgbe_rx *state)
अणु
	अचिन्हित पूर्णांक link_support;
	अचिन्हित पूर्णांक reg, ad_reg, lp_reg;

	/* Read Base Ability रेजिस्टर 2 first */
	reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 1);

	/* Check क्रम a supported mode, otherwise restart in a dअगरferent one */
	link_support = xgbe_in_kr_mode(pdata) ? 0x80 : 0x20;
	अगर (!(reg & link_support))
		वापस XGBE_AN_INCOMPAT_LINK;

	/* Check Extended Next Page support */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA);

	वापस ((ad_reg & XGBE_XNP_NP_EXCHANGE) ||
		(lp_reg & XGBE_XNP_NP_EXCHANGE))
	       ? xgbe_an73_tx_xnp(pdata, state)
	       : xgbe_an73_tx_training(pdata, state);
पूर्ण

अटल क्रमागत xgbe_an xgbe_an73_rx_xnp(काष्ठा xgbe_prv_data *pdata,
				     क्रमागत xgbe_rx *state)
अणु
	अचिन्हित पूर्णांक ad_reg, lp_reg;

	/* Check Extended Next Page support */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_XNP);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPX);

	वापस ((ad_reg & XGBE_XNP_NP_EXCHANGE) ||
		(lp_reg & XGBE_XNP_NP_EXCHANGE))
	       ? xgbe_an73_tx_xnp(pdata, state)
	       : xgbe_an73_tx_training(pdata, state);
पूर्ण

अटल क्रमागत xgbe_an xgbe_an73_page_received(काष्ठा xgbe_prv_data *pdata)
अणु
	क्रमागत xgbe_rx *state;
	अचिन्हित दीर्घ an_समयout;
	क्रमागत xgbe_an ret;

	अगर (!pdata->an_start) अणु
		pdata->an_start = jअगरfies;
	पूर्ण अन्यथा अणु
		an_समयout = pdata->an_start +
			     msecs_to_jअगरfies(XGBE_AN_MS_TIMEOUT);
		अगर (समय_after(jअगरfies, an_समयout)) अणु
			/* Auto-negotiation समयd out, reset state */
			pdata->kr_state = XGBE_RX_BPA;
			pdata->kx_state = XGBE_RX_BPA;

			pdata->an_start = jअगरfies;

			netअगर_dbg(pdata, link, pdata->netdev,
				  "CL73 AN timed out, resetting state\n");
		पूर्ण
	पूर्ण

	state = xgbe_in_kr_mode(pdata) ? &pdata->kr_state
				       : &pdata->kx_state;

	चयन (*state) अणु
	हाल XGBE_RX_BPA:
		ret = xgbe_an73_rx_bpa(pdata, state);
		अवरोध;

	हाल XGBE_RX_XNP:
		ret = xgbe_an73_rx_xnp(pdata, state);
		अवरोध;

	शेष:
		ret = XGBE_AN_ERROR;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत xgbe_an xgbe_an73_incompat_link(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;

	/* Be sure we aren't looping trying to negotiate */
	अगर (xgbe_in_kr_mode(pdata)) अणु
		pdata->kr_state = XGBE_RX_ERROR;

		अगर (!XGBE_ADV(lks, 1000baseKX_Full) &&
		    !XGBE_ADV(lks, 2500baseX_Full))
			वापस XGBE_AN_NO_LINK;

		अगर (pdata->kx_state != XGBE_RX_BPA)
			वापस XGBE_AN_NO_LINK;
	पूर्ण अन्यथा अणु
		pdata->kx_state = XGBE_RX_ERROR;

		अगर (!XGBE_ADV(lks, 10000baseKR_Full))
			वापस XGBE_AN_NO_LINK;

		अगर (pdata->kr_state != XGBE_RX_BPA)
			वापस XGBE_AN_NO_LINK;
	पूर्ण

	xgbe_an_disable(pdata);

	xgbe_चयन_mode(pdata);

	xgbe_an_restart(pdata);

	वापस XGBE_AN_INCOMPAT_LINK;
पूर्ण

अटल व्योम xgbe_an37_isr(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक reg;

	/* Disable AN पूर्णांकerrupts */
	xgbe_an37_disable_पूर्णांकerrupts(pdata);

	/* Save the पूर्णांकerrupt(s) that fired */
	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT);
	pdata->an_पूर्णांक = reg & XGBE_AN_CL37_INT_MASK;
	pdata->an_status = reg & ~XGBE_AN_CL37_INT_MASK;

	अगर (pdata->an_पूर्णांक) अणु
		/* Clear the पूर्णांकerrupt(s) that fired and process them */
		reg &= ~XGBE_AN_CL37_INT_MASK;
		XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_STAT, reg);

		queue_work(pdata->an_workqueue, &pdata->an_irq_work);
	पूर्ण अन्यथा अणु
		/* Enable AN पूर्णांकerrupts */
		xgbe_an37_enable_पूर्णांकerrupts(pdata);

		/* Reissue पूर्णांकerrupt अगर status is not clear */
		अगर (pdata->vdata->irq_reissue_support)
			XP_IOWRITE(pdata, XP_INT_REISSUE_EN, 1 << 3);
	पूर्ण
पूर्ण

अटल व्योम xgbe_an73_isr(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Disable AN पूर्णांकerrupts */
	xgbe_an73_disable_पूर्णांकerrupts(pdata);

	/* Save the पूर्णांकerrupt(s) that fired */
	pdata->an_पूर्णांक = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_INT);

	अगर (pdata->an_पूर्णांक) अणु
		/* Clear the पूर्णांकerrupt(s) that fired and process them */
		XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, ~pdata->an_पूर्णांक);

		queue_work(pdata->an_workqueue, &pdata->an_irq_work);
	पूर्ण अन्यथा अणु
		/* Enable AN पूर्णांकerrupts */
		xgbe_an73_enable_पूर्णांकerrupts(pdata);

		/* Reissue पूर्णांकerrupt अगर status is not clear */
		अगर (pdata->vdata->irq_reissue_support)
			XP_IOWRITE(pdata, XP_INT_REISSUE_EN, 1 << 3);
	पूर्ण
पूर्ण

अटल व्योम xgbe_an_isr_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा xgbe_prv_data *pdata = from_tasklet(pdata, t, tasklet_an);

	netअगर_dbg(pdata, पूर्णांकr, pdata->netdev, "AN interrupt received\n");

	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL73:
	हाल XGBE_AN_MODE_CL73_REDRV:
		xgbe_an73_isr(pdata);
		अवरोध;
	हाल XGBE_AN_MODE_CL37:
	हाल XGBE_AN_MODE_CL37_SGMII:
		xgbe_an37_isr(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t xgbe_an_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xgbe_prv_data *pdata = (काष्ठा xgbe_prv_data *)data;

	अगर (pdata->isr_as_tasklet)
		tasklet_schedule(&pdata->tasklet_an);
	अन्यथा
		xgbe_an_isr_task(&pdata->tasklet_an);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t xgbe_an_combined_isr(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_an_isr_task(&pdata->tasklet_an);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xgbe_an_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(work,
						   काष्ठा xgbe_prv_data,
						   an_irq_work);

	/* Aव्योम a race between enabling the IRQ and निकासing the work by
	 * रुकोing क्रम the work to finish and then queueing it
	 */
	flush_work(&pdata->an_work);
	queue_work(pdata->an_workqueue, &pdata->an_work);
पूर्ण

अटल स्थिर अक्षर *xgbe_state_as_string(क्रमागत xgbe_an state)
अणु
	चयन (state) अणु
	हाल XGBE_AN_READY:
		वापस "Ready";
	हाल XGBE_AN_PAGE_RECEIVED:
		वापस "Page-Received";
	हाल XGBE_AN_INCOMPAT_LINK:
		वापस "Incompatible-Link";
	हाल XGBE_AN_COMPLETE:
		वापस "Complete";
	हाल XGBE_AN_NO_LINK:
		वापस "No-Link";
	हाल XGBE_AN_ERROR:
		वापस "Error";
	शेष:
		वापस "Undefined";
	पूर्ण
पूर्ण

अटल व्योम xgbe_an37_state_machine(काष्ठा xgbe_prv_data *pdata)
अणु
	क्रमागत xgbe_an cur_state = pdata->an_state;

	अगर (!pdata->an_पूर्णांक)
		वापस;

	अगर (pdata->an_पूर्णांक & XGBE_AN_CL37_INT_CMPLT) अणु
		pdata->an_state = XGBE_AN_COMPLETE;
		pdata->an_पूर्णांक &= ~XGBE_AN_CL37_INT_CMPLT;

		/* If SGMII is enabled, check the link status */
		अगर ((pdata->an_mode == XGBE_AN_MODE_CL37_SGMII) &&
		    !(pdata->an_status & XGBE_SGMII_AN_LINK_STATUS))
			pdata->an_state = XGBE_AN_NO_LINK;
	पूर्ण

	netअगर_dbg(pdata, link, pdata->netdev, "CL37 AN %s\n",
		  xgbe_state_as_string(pdata->an_state));

	cur_state = pdata->an_state;

	चयन (pdata->an_state) अणु
	हाल XGBE_AN_READY:
		अवरोध;

	हाल XGBE_AN_COMPLETE:
		netअगर_dbg(pdata, link, pdata->netdev,
			  "Auto negotiation successful\n");
		अवरोध;

	हाल XGBE_AN_NO_LINK:
		अवरोध;

	शेष:
		pdata->an_state = XGBE_AN_ERROR;
	पूर्ण

	अगर (pdata->an_state == XGBE_AN_ERROR) अणु
		netdev_err(pdata->netdev,
			   "error during auto-negotiation, state=%u\n",
			   cur_state);

		pdata->an_पूर्णांक = 0;
		xgbe_an37_clear_पूर्णांकerrupts(pdata);
	पूर्ण

	अगर (pdata->an_state >= XGBE_AN_COMPLETE) अणु
		pdata->an_result = pdata->an_state;
		pdata->an_state = XGBE_AN_READY;

		अगर (pdata->phy_अगर.phy_impl.an_post)
			pdata->phy_अगर.phy_impl.an_post(pdata);

		netअगर_dbg(pdata, link, pdata->netdev, "CL37 AN result: %s\n",
			  xgbe_state_as_string(pdata->an_result));
	पूर्ण

	xgbe_an37_enable_पूर्णांकerrupts(pdata);
पूर्ण

अटल व्योम xgbe_an73_state_machine(काष्ठा xgbe_prv_data *pdata)
अणु
	क्रमागत xgbe_an cur_state = pdata->an_state;

	अगर (!pdata->an_पूर्णांक)
		वापस;

next_पूर्णांक:
	अगर (pdata->an_पूर्णांक & XGBE_AN_CL73_PG_RCV) अणु
		pdata->an_state = XGBE_AN_PAGE_RECEIVED;
		pdata->an_पूर्णांक &= ~XGBE_AN_CL73_PG_RCV;
	पूर्ण अन्यथा अगर (pdata->an_पूर्णांक & XGBE_AN_CL73_INC_LINK) अणु
		pdata->an_state = XGBE_AN_INCOMPAT_LINK;
		pdata->an_पूर्णांक &= ~XGBE_AN_CL73_INC_LINK;
	पूर्ण अन्यथा अगर (pdata->an_पूर्णांक & XGBE_AN_CL73_INT_CMPLT) अणु
		pdata->an_state = XGBE_AN_COMPLETE;
		pdata->an_पूर्णांक &= ~XGBE_AN_CL73_INT_CMPLT;
	पूर्ण अन्यथा अणु
		pdata->an_state = XGBE_AN_ERROR;
	पूर्ण

again:
	netअगर_dbg(pdata, link, pdata->netdev, "CL73 AN %s\n",
		  xgbe_state_as_string(pdata->an_state));

	cur_state = pdata->an_state;

	चयन (pdata->an_state) अणु
	हाल XGBE_AN_READY:
		pdata->an_supported = 0;
		अवरोध;

	हाल XGBE_AN_PAGE_RECEIVED:
		pdata->an_state = xgbe_an73_page_received(pdata);
		pdata->an_supported++;
		अवरोध;

	हाल XGBE_AN_INCOMPAT_LINK:
		pdata->an_supported = 0;
		pdata->parallel_detect = 0;
		pdata->an_state = xgbe_an73_incompat_link(pdata);
		अवरोध;

	हाल XGBE_AN_COMPLETE:
		pdata->parallel_detect = pdata->an_supported ? 0 : 1;
		netअगर_dbg(pdata, link, pdata->netdev, "%s successful\n",
			  pdata->an_supported ? "Auto negotiation"
					      : "Parallel detection");
		अवरोध;

	हाल XGBE_AN_NO_LINK:
		अवरोध;

	शेष:
		pdata->an_state = XGBE_AN_ERROR;
	पूर्ण

	अगर (pdata->an_state == XGBE_AN_NO_LINK) अणु
		pdata->an_पूर्णांक = 0;
		xgbe_an73_clear_पूर्णांकerrupts(pdata);
	पूर्ण अन्यथा अगर (pdata->an_state == XGBE_AN_ERROR) अणु
		netdev_err(pdata->netdev,
			   "error during auto-negotiation, state=%u\n",
			   cur_state);

		pdata->an_पूर्णांक = 0;
		xgbe_an73_clear_पूर्णांकerrupts(pdata);
	पूर्ण

	अगर (pdata->an_state >= XGBE_AN_COMPLETE) अणु
		pdata->an_result = pdata->an_state;
		pdata->an_state = XGBE_AN_READY;
		pdata->kr_state = XGBE_RX_BPA;
		pdata->kx_state = XGBE_RX_BPA;
		pdata->an_start = 0;

		अगर (pdata->phy_अगर.phy_impl.an_post)
			pdata->phy_अगर.phy_impl.an_post(pdata);

		netअगर_dbg(pdata, link, pdata->netdev, "CL73 AN result: %s\n",
			  xgbe_state_as_string(pdata->an_result));
	पूर्ण

	अगर (cur_state != pdata->an_state)
		जाओ again;

	अगर (pdata->an_पूर्णांक)
		जाओ next_पूर्णांक;

	xgbe_an73_enable_पूर्णांकerrupts(pdata);
पूर्ण

अटल व्योम xgbe_an_state_machine(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xgbe_prv_data *pdata = container_of(work,
						   काष्ठा xgbe_prv_data,
						   an_work);

	mutex_lock(&pdata->an_mutex);

	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL73:
	हाल XGBE_AN_MODE_CL73_REDRV:
		xgbe_an73_state_machine(pdata);
		अवरोध;
	हाल XGBE_AN_MODE_CL37:
	हाल XGBE_AN_MODE_CL37_SGMII:
		xgbe_an37_state_machine(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Reissue पूर्णांकerrupt अगर status is not clear */
	अगर (pdata->vdata->irq_reissue_support)
		XP_IOWRITE(pdata, XP_INT_REISSUE_EN, 1 << 3);

	mutex_unlock(&pdata->an_mutex);
पूर्ण

अटल व्योम xgbe_an37_init(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings lks;
	अचिन्हित पूर्णांक reg;

	pdata->phy_अगर.phy_impl.an_advertising(pdata, &lks);

	/* Set up Advertisement रेजिस्टर */
	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_ADVERTISE);
	अगर (XGBE_ADV(&lks, Pause))
		reg |= 0x100;
	अन्यथा
		reg &= ~0x100;

	अगर (XGBE_ADV(&lks, Asym_Pause))
		reg |= 0x80;
	अन्यथा
		reg &= ~0x80;

	/* Full duplex, but not half */
	reg |= XGBE_AN_CL37_FD_MASK;
	reg &= ~XGBE_AN_CL37_HD_MASK;

	XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_ADVERTISE, reg);

	/* Set up the Control रेजिस्टर */
	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL);
	reg &= ~XGBE_AN_CL37_TX_CONFIG_MASK;
	reg &= ~XGBE_AN_CL37_PCS_MODE_MASK;

	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL37:
		reg |= XGBE_AN_CL37_PCS_MODE_BASEX;
		अवरोध;
	हाल XGBE_AN_MODE_CL37_SGMII:
		reg |= XGBE_AN_CL37_PCS_MODE_SGMII;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	reg |= XGBE_AN_CL37_MII_CTRL_8BIT;

	XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL, reg);

	netअगर_dbg(pdata, link, pdata->netdev, "CL37 AN (%s) initialized\n",
		  (pdata->an_mode == XGBE_AN_MODE_CL37) ? "BaseX" : "SGMII");
पूर्ण

अटल व्योम xgbe_an73_init(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings lks;
	अचिन्हित पूर्णांक reg;

	pdata->phy_अगर.phy_impl.an_advertising(pdata, &lks);

	/* Set up Advertisement रेजिस्टर 3 first */
	reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
	अगर (XGBE_ADV(&lks, 10000baseR_FEC))
		reg |= 0xc000;
	अन्यथा
		reg &= ~0xc000;

	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2, reg);

	/* Set up Advertisement रेजिस्टर 2 next */
	reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1);
	अगर (XGBE_ADV(&lks, 10000baseKR_Full))
		reg |= 0x80;
	अन्यथा
		reg &= ~0x80;

	अगर (XGBE_ADV(&lks, 1000baseKX_Full) ||
	    XGBE_ADV(&lks, 2500baseX_Full))
		reg |= 0x20;
	अन्यथा
		reg &= ~0x20;

	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1, reg);

	/* Set up Advertisement रेजिस्टर 1 last */
	reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
	अगर (XGBE_ADV(&lks, Pause))
		reg |= 0x400;
	अन्यथा
		reg &= ~0x400;

	अगर (XGBE_ADV(&lks, Asym_Pause))
		reg |= 0x800;
	अन्यथा
		reg &= ~0x800;

	/* We करोn't पूर्णांकend to perक्रमm XNP */
	reg &= ~XGBE_XNP_NP_EXCHANGE;

	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE, reg);

	netअगर_dbg(pdata, link, pdata->netdev, "CL73 AN initialized\n");
पूर्ण

अटल व्योम xgbe_an_init(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Set up advertisement रेजिस्टरs based on current settings */
	pdata->an_mode = pdata->phy_अगर.phy_impl.an_mode(pdata);
	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL73:
	हाल XGBE_AN_MODE_CL73_REDRV:
		xgbe_an73_init(pdata);
		अवरोध;
	हाल XGBE_AN_MODE_CL37:
	हाल XGBE_AN_MODE_CL37_SGMII:
		xgbe_an37_init(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *xgbe_phy_fc_string(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (pdata->tx_छोड़ो && pdata->rx_छोड़ो)
		वापस "rx/tx";
	अन्यथा अगर (pdata->rx_छोड़ो)
		वापस "rx";
	अन्यथा अगर (pdata->tx_छोड़ो)
		वापस "tx";
	अन्यथा
		वापस "off";
पूर्ण

अटल स्थिर अक्षर *xgbe_phy_speed_string(पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_100:
		वापस "100Mbps";
	हाल SPEED_1000:
		वापस "1Gbps";
	हाल SPEED_2500:
		वापस "2.5Gbps";
	हाल SPEED_10000:
		वापस "10Gbps";
	हाल SPEED_UNKNOWN:
		वापस "Unknown";
	शेष:
		वापस "Unsupported";
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_prपूर्णांक_status(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (pdata->phy.link)
		netdev_info(pdata->netdev,
			    "Link is Up - %s/%s - flow control %s\n",
			    xgbe_phy_speed_string(pdata->phy.speed),
			    pdata->phy.duplex == DUPLEX_FULL ? "Full" : "Half",
			    xgbe_phy_fc_string(pdata));
	अन्यथा
		netdev_info(pdata->netdev, "Link is Down\n");
पूर्ण

अटल व्योम xgbe_phy_adjust_link(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक new_state = 0;

	अगर (pdata->phy.link) अणु
		/* Flow control support */
		pdata->छोड़ो_स्वतःneg = pdata->phy.छोड़ो_स्वतःneg;

		अगर (pdata->tx_छोड़ो != pdata->phy.tx_छोड़ो) अणु
			new_state = 1;
			pdata->tx_छोड़ो = pdata->phy.tx_छोड़ो;
			pdata->hw_अगर.config_tx_flow_control(pdata);
		पूर्ण

		अगर (pdata->rx_छोड़ो != pdata->phy.rx_छोड़ो) अणु
			new_state = 1;
			pdata->rx_छोड़ो = pdata->phy.rx_छोड़ो;
			pdata->hw_अगर.config_rx_flow_control(pdata);
		पूर्ण

		/* Speed support */
		अगर (pdata->phy_speed != pdata->phy.speed) अणु
			new_state = 1;
			pdata->phy_speed = pdata->phy.speed;
		पूर्ण

		अगर (pdata->phy_link != pdata->phy.link) अणु
			new_state = 1;
			pdata->phy_link = pdata->phy.link;
		पूर्ण
	पूर्ण अन्यथा अगर (pdata->phy_link) अणु
		new_state = 1;
		pdata->phy_link = 0;
		pdata->phy_speed = SPEED_UNKNOWN;
	पूर्ण

	अगर (new_state && netअगर_msg_link(pdata))
		xgbe_phy_prपूर्णांक_status(pdata);
पूर्ण

अटल bool xgbe_phy_valid_speed(काष्ठा xgbe_prv_data *pdata, पूर्णांक speed)
अणु
	वापस pdata->phy_अगर.phy_impl.valid_speed(pdata, speed);
पूर्ण

अटल पूर्णांक xgbe_phy_config_fixed(काष्ठा xgbe_prv_data *pdata)
अणु
	क्रमागत xgbe_mode mode;

	netअगर_dbg(pdata, link, pdata->netdev, "fixed PHY configuration\n");

	/* Disable स्वतः-negotiation */
	xgbe_an_disable(pdata);

	/* Set specअगरied mode क्रम specअगरied speed */
	mode = pdata->phy_अगर.phy_impl.get_mode(pdata, pdata->phy.speed);
	चयन (mode) अणु
	हाल XGBE_MODE_KX_1000:
	हाल XGBE_MODE_KX_2500:
	हाल XGBE_MODE_KR:
	हाल XGBE_MODE_SGMII_100:
	हाल XGBE_MODE_SGMII_1000:
	हाल XGBE_MODE_X:
	हाल XGBE_MODE_SFI:
		अवरोध;
	हाल XGBE_MODE_UNKNOWN:
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Validate duplex mode */
	अगर (pdata->phy.duplex != DUPLEX_FULL)
		वापस -EINVAL;

	xgbe_set_mode(pdata, mode);

	वापस 0;
पूर्ण

अटल पूर्णांक __xgbe_phy_config_aneg(काष्ठा xgbe_prv_data *pdata, bool set_mode)
अणु
	पूर्णांक ret;

	mutex_lock(&pdata->an_mutex);

	set_bit(XGBE_LINK_INIT, &pdata->dev_state);
	pdata->link_check = jअगरfies;

	ret = pdata->phy_अगर.phy_impl.an_config(pdata);
	अगर (ret)
		जाओ out;

	अगर (pdata->phy.स्वतःneg != AUTONEG_ENABLE) अणु
		ret = xgbe_phy_config_fixed(pdata);
		अगर (ret || !pdata->kr_redrv)
			जाओ out;

		netअगर_dbg(pdata, link, pdata->netdev, "AN redriver support\n");
	पूर्ण अन्यथा अणु
		netअगर_dbg(pdata, link, pdata->netdev, "AN PHY configuration\n");
	पूर्ण

	/* Disable स्वतः-negotiation पूर्णांकerrupt */
	disable_irq(pdata->an_irq);

	अगर (set_mode) अणु
		/* Start स्वतः-negotiation in a supported mode */
		अगर (xgbe_use_mode(pdata, XGBE_MODE_KR)) अणु
			xgbe_set_mode(pdata, XGBE_MODE_KR);
		पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_KX_2500)) अणु
			xgbe_set_mode(pdata, XGBE_MODE_KX_2500);
		पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_KX_1000)) अणु
			xgbe_set_mode(pdata, XGBE_MODE_KX_1000);
		पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_SFI)) अणु
			xgbe_set_mode(pdata, XGBE_MODE_SFI);
		पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_X)) अणु
			xgbe_set_mode(pdata, XGBE_MODE_X);
		पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_SGMII_1000)) अणु
			xgbe_set_mode(pdata, XGBE_MODE_SGMII_1000);
		पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_SGMII_100)) अणु
			xgbe_set_mode(pdata, XGBE_MODE_SGMII_100);
		पूर्ण अन्यथा अणु
			enable_irq(pdata->an_irq);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Disable and stop any in progress स्वतः-negotiation */
	xgbe_an_disable_all(pdata);

	/* Clear any स्वतः-negotitation पूर्णांकerrupts */
	xgbe_an_clear_पूर्णांकerrupts_all(pdata);

	pdata->an_result = XGBE_AN_READY;
	pdata->an_state = XGBE_AN_READY;
	pdata->kr_state = XGBE_RX_BPA;
	pdata->kx_state = XGBE_RX_BPA;

	/* Re-enable स्वतः-negotiation पूर्णांकerrupt */
	enable_irq(pdata->an_irq);

	xgbe_an_init(pdata);
	xgbe_an_restart(pdata);

out:
	अगर (ret)
		set_bit(XGBE_LINK_ERR, &pdata->dev_state);
	अन्यथा
		clear_bit(XGBE_LINK_ERR, &pdata->dev_state);

	mutex_unlock(&pdata->an_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_config_aneg(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस __xgbe_phy_config_aneg(pdata, true);
पूर्ण

अटल पूर्णांक xgbe_phy_reconfig_aneg(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस __xgbe_phy_config_aneg(pdata, false);
पूर्ण

अटल bool xgbe_phy_aneg_करोne(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस (pdata->an_result == XGBE_AN_COMPLETE);
पूर्ण

अटल व्योम xgbe_check_link_समयout(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित दीर्घ link_समयout;

	link_समयout = pdata->link_check + (XGBE_LINK_TIMEOUT * HZ);
	अगर (समय_after(jअगरfies, link_समयout)) अणु
		netअगर_dbg(pdata, link, pdata->netdev, "AN link timeout\n");
		xgbe_phy_config_aneg(pdata);
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_status_aneg(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस pdata->phy_अगर.phy_impl.an_outcome(pdata);
पूर्ण

अटल व्योम xgbe_phy_status_result(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	क्रमागत xgbe_mode mode;

	XGBE_ZERO_LP_ADV(lks);

	अगर ((pdata->phy.स्वतःneg != AUTONEG_ENABLE) || pdata->parallel_detect)
		mode = xgbe_cur_mode(pdata);
	अन्यथा
		mode = xgbe_phy_status_aneg(pdata);

	चयन (mode) अणु
	हाल XGBE_MODE_SGMII_100:
		pdata->phy.speed = SPEED_100;
		अवरोध;
	हाल XGBE_MODE_X:
	हाल XGBE_MODE_KX_1000:
	हाल XGBE_MODE_SGMII_1000:
		pdata->phy.speed = SPEED_1000;
		अवरोध;
	हाल XGBE_MODE_KX_2500:
		pdata->phy.speed = SPEED_2500;
		अवरोध;
	हाल XGBE_MODE_KR:
	हाल XGBE_MODE_SFI:
		pdata->phy.speed = SPEED_10000;
		अवरोध;
	हाल XGBE_MODE_UNKNOWN:
	शेष:
		pdata->phy.speed = SPEED_UNKNOWN;
	पूर्ण

	pdata->phy.duplex = DUPLEX_FULL;

	अगर (xgbe_set_mode(pdata, mode) && pdata->an_again)
		xgbe_phy_reconfig_aneg(pdata);
पूर्ण

अटल व्योम xgbe_phy_status(काष्ठा xgbe_prv_data *pdata)
अणु
	अचिन्हित पूर्णांक link_aneg;
	पूर्णांक an_restart;

	अगर (test_bit(XGBE_LINK_ERR, &pdata->dev_state)) अणु
		netअगर_carrier_off(pdata->netdev);

		pdata->phy.link = 0;
		जाओ adjust_link;
	पूर्ण

	link_aneg = (pdata->phy.स्वतःneg == AUTONEG_ENABLE);

	pdata->phy.link = pdata->phy_अगर.phy_impl.link_status(pdata,
							     &an_restart);
	अगर (an_restart) अणु
		xgbe_phy_config_aneg(pdata);
		जाओ adjust_link;
	पूर्ण

	अगर (pdata->phy.link) अणु
		अगर (link_aneg && !xgbe_phy_aneg_करोne(pdata)) अणु
			xgbe_check_link_समयout(pdata);
			वापस;
		पूर्ण

		xgbe_phy_status_result(pdata);

		अगर (test_bit(XGBE_LINK_INIT, &pdata->dev_state))
			clear_bit(XGBE_LINK_INIT, &pdata->dev_state);

		netअगर_carrier_on(pdata->netdev);
	पूर्ण अन्यथा अणु
		अगर (test_bit(XGBE_LINK_INIT, &pdata->dev_state)) अणु
			xgbe_check_link_समयout(pdata);

			अगर (link_aneg)
				वापस;
		पूर्ण

		xgbe_phy_status_result(pdata);

		netअगर_carrier_off(pdata->netdev);
	पूर्ण

adjust_link:
	xgbe_phy_adjust_link(pdata);
पूर्ण

अटल व्योम xgbe_phy_stop(काष्ठा xgbe_prv_data *pdata)
अणु
	netअगर_dbg(pdata, link, pdata->netdev, "stopping PHY\n");

	अगर (!pdata->phy_started)
		वापस;

	/* Indicate the PHY is करोwn */
	pdata->phy_started = 0;

	/* Disable स्वतः-negotiation */
	xgbe_an_disable_all(pdata);

	अगर (pdata->dev_irq != pdata->an_irq)
		devm_मुक्त_irq(pdata->dev, pdata->an_irq, pdata);

	pdata->phy_अगर.phy_impl.stop(pdata);

	pdata->phy.link = 0;

	xgbe_phy_adjust_link(pdata);
पूर्ण

अटल पूर्णांक xgbe_phy_start(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;
	पूर्णांक ret;

	netअगर_dbg(pdata, link, pdata->netdev, "starting PHY\n");

	ret = pdata->phy_अगर.phy_impl.start(pdata);
	अगर (ret)
		वापस ret;

	/* If we have a separate AN irq, enable it */
	अगर (pdata->dev_irq != pdata->an_irq) अणु
		tasklet_setup(&pdata->tasklet_an, xgbe_an_isr_task);

		ret = devm_request_irq(pdata->dev, pdata->an_irq,
				       xgbe_an_isr, 0, pdata->an_name,
				       pdata);
		अगर (ret) अणु
			netdev_err(netdev, "phy irq request failed\n");
			जाओ err_stop;
		पूर्ण
	पूर्ण

	/* Set initial mode - call the mode setting routines
	 * directly to insure we are properly configured
	 */
	अगर (xgbe_use_mode(pdata, XGBE_MODE_KR)) अणु
		xgbe_kr_mode(pdata);
	पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_KX_2500)) अणु
		xgbe_kx_2500_mode(pdata);
	पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_KX_1000)) अणु
		xgbe_kx_1000_mode(pdata);
	पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_SFI)) अणु
		xgbe_sfi_mode(pdata);
	पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_X)) अणु
		xgbe_x_mode(pdata);
	पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_SGMII_1000)) अणु
		xgbe_sgmii_1000_mode(pdata);
	पूर्ण अन्यथा अगर (xgbe_use_mode(pdata, XGBE_MODE_SGMII_100)) अणु
		xgbe_sgmii_100_mode(pdata);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err_irq;
	पूर्ण

	/* Indicate the PHY is up and running */
	pdata->phy_started = 1;

	xgbe_an_init(pdata);
	xgbe_an_enable_पूर्णांकerrupts(pdata);

	वापस xgbe_phy_config_aneg(pdata);

err_irq:
	अगर (pdata->dev_irq != pdata->an_irq)
		devm_मुक्त_irq(pdata->dev, pdata->an_irq, pdata);

err_stop:
	pdata->phy_अगर.phy_impl.stop(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_reset(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक ret;

	ret = pdata->phy_अगर.phy_impl.reset(pdata);
	अगर (ret)
		वापस ret;

	/* Disable स्वतः-negotiation क्रम now */
	xgbe_an_disable_all(pdata);

	/* Clear स्वतः-negotiation पूर्णांकerrupts */
	xgbe_an_clear_पूर्णांकerrupts_all(pdata);

	वापस 0;
पूर्ण

अटल व्योम xgbe_dump_phy_रेजिस्टरs(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा device *dev = pdata->dev;

	dev_dbg(dev, "\n************* PHY Reg dump **********************\n");

	dev_dbg(dev, "PCS Control Reg (%#06x) = %#06x\n", MDIO_CTRL1,
		XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1));
	dev_dbg(dev, "PCS Status Reg (%#06x) = %#06x\n", MDIO_STAT1,
		XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1));
	dev_dbg(dev, "Phy Id (PHYS ID 1 %#06x)= %#06x\n", MDIO_DEVID1,
		XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_DEVID1));
	dev_dbg(dev, "Phy Id (PHYS ID 2 %#06x)= %#06x\n", MDIO_DEVID2,
		XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_DEVID2));
	dev_dbg(dev, "Devices in Package (%#06x)= %#06x\n", MDIO_DEVS1,
		XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_DEVS1));
	dev_dbg(dev, "Devices in Package (%#06x)= %#06x\n", MDIO_DEVS2,
		XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_DEVS2));

	dev_dbg(dev, "Auto-Neg Control Reg (%#06x) = %#06x\n", MDIO_CTRL1,
		XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_CTRL1));
	dev_dbg(dev, "Auto-Neg Status Reg (%#06x) = %#06x\n", MDIO_STAT1,
		XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_STAT1));
	dev_dbg(dev, "Auto-Neg Ad Reg 1 (%#06x) = %#06x\n",
		MDIO_AN_ADVERTISE,
		XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE));
	dev_dbg(dev, "Auto-Neg Ad Reg 2 (%#06x) = %#06x\n",
		MDIO_AN_ADVERTISE + 1,
		XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1));
	dev_dbg(dev, "Auto-Neg Ad Reg 3 (%#06x) = %#06x\n",
		MDIO_AN_ADVERTISE + 2,
		XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2));
	dev_dbg(dev, "Auto-Neg Completion Reg (%#06x) = %#06x\n",
		MDIO_AN_COMP_STAT,
		XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_COMP_STAT));

	dev_dbg(dev, "\n*************************************************\n");
पूर्ण

अटल पूर्णांक xgbe_phy_best_advertised_speed(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;

	अगर (XGBE_ADV(lks, 10000baseKR_Full))
		वापस SPEED_10000;
	अन्यथा अगर (XGBE_ADV(lks, 10000baseT_Full))
		वापस SPEED_10000;
	अन्यथा अगर (XGBE_ADV(lks, 2500baseX_Full))
		वापस SPEED_2500;
	अन्यथा अगर (XGBE_ADV(lks, 2500baseT_Full))
		वापस SPEED_2500;
	अन्यथा अगर (XGBE_ADV(lks, 1000baseKX_Full))
		वापस SPEED_1000;
	अन्यथा अगर (XGBE_ADV(lks, 1000baseT_Full))
		वापस SPEED_1000;
	अन्यथा अगर (XGBE_ADV(lks, 100baseT_Full))
		वापस SPEED_100;

	वापस SPEED_UNKNOWN;
पूर्ण

अटल व्योम xgbe_phy_निकास(काष्ठा xgbe_prv_data *pdata)
अणु
	pdata->phy_अगर.phy_impl.निकास(pdata);
पूर्ण

अटल पूर्णांक xgbe_phy_init(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	पूर्णांक ret;

	mutex_init(&pdata->an_mutex);
	INIT_WORK(&pdata->an_irq_work, xgbe_an_irq_work);
	INIT_WORK(&pdata->an_work, xgbe_an_state_machine);
	pdata->mdio_mmd = MDIO_MMD_PCS;

	/* Check क्रम FEC support */
	pdata->fec_ability = XMDIO_READ(pdata, MDIO_MMD_PMAPMD,
					MDIO_PMA_10GBR_FECABLE);
	pdata->fec_ability &= (MDIO_PMA_10GBR_FECABLE_ABLE |
			       MDIO_PMA_10GBR_FECABLE_ERRABLE);

	/* Setup the phy (including supported features) */
	ret = pdata->phy_अगर.phy_impl.init(pdata);
	अगर (ret)
		वापस ret;

	/* Copy supported link modes to advertising link modes */
	XGBE_LM_COPY(lks, advertising, lks, supported);

	pdata->phy.address = 0;

	अगर (XGBE_ADV(lks, Autoneg)) अणु
		pdata->phy.स्वतःneg = AUTONEG_ENABLE;
		pdata->phy.speed = SPEED_UNKNOWN;
		pdata->phy.duplex = DUPLEX_UNKNOWN;
	पूर्ण अन्यथा अणु
		pdata->phy.स्वतःneg = AUTONEG_DISABLE;
		pdata->phy.speed = xgbe_phy_best_advertised_speed(pdata);
		pdata->phy.duplex = DUPLEX_FULL;
	पूर्ण

	pdata->phy.link = 0;

	pdata->phy.छोड़ो_स्वतःneg = pdata->छोड़ो_स्वतःneg;
	pdata->phy.tx_छोड़ो = pdata->tx_छोड़ो;
	pdata->phy.rx_छोड़ो = pdata->rx_छोड़ो;

	/* Fix up Flow Control advertising */
	XGBE_CLR_ADV(lks, Pause);
	XGBE_CLR_ADV(lks, Asym_Pause);

	अगर (pdata->rx_छोड़ो) अणु
		XGBE_SET_ADV(lks, Pause);
		XGBE_SET_ADV(lks, Asym_Pause);
	पूर्ण

	अगर (pdata->tx_छोड़ो) अणु
		/* Equivalent to XOR of Asym_Pause */
		अगर (XGBE_ADV(lks, Asym_Pause))
			XGBE_CLR_ADV(lks, Asym_Pause);
		अन्यथा
			XGBE_SET_ADV(lks, Asym_Pause);
	पूर्ण

	अगर (netअगर_msg_drv(pdata))
		xgbe_dump_phy_रेजिस्टरs(pdata);

	वापस 0;
पूर्ण

व्योम xgbe_init_function_ptrs_phy(काष्ठा xgbe_phy_अगर *phy_अगर)
अणु
	phy_अगर->phy_init        = xgbe_phy_init;
	phy_अगर->phy_निकास        = xgbe_phy_निकास;

	phy_अगर->phy_reset       = xgbe_phy_reset;
	phy_अगर->phy_start       = xgbe_phy_start;
	phy_अगर->phy_stop        = xgbe_phy_stop;

	phy_अगर->phy_status      = xgbe_phy_status;
	phy_अगर->phy_config_aneg = xgbe_phy_config_aneg;

	phy_अगर->phy_valid_speed = xgbe_phy_valid_speed;

	phy_अगर->an_isr          = xgbe_an_combined_isr;

	phy_अगर->module_info     = xgbe_phy_module_info;
	phy_अगर->module_eeprom   = xgbe_phy_module_eeprom;
पूर्ण
