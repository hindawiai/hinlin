<शैली गुरु>
/*
 * AMD 10Gb Ethernet driver
 *
 * This file is available to you under your choice of the following two
 * licenses:
 *
 * License 1: GPLv2
 *
 * Copyright (c) 2016 Advanced Micro Devices, Inc.
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
 * Copyright (c) 2016 Advanced Micro Devices, Inc.
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

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kmod.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/ethtool.h>

#समावेश "xgbe.h"
#समावेश "xgbe-common.h"

#घोषणा XGBE_PHY_PORT_SPEED_100		BIT(0)
#घोषणा XGBE_PHY_PORT_SPEED_1000	BIT(1)
#घोषणा XGBE_PHY_PORT_SPEED_2500	BIT(2)
#घोषणा XGBE_PHY_PORT_SPEED_10000	BIT(3)

#घोषणा XGBE_MUTEX_RELEASE		0x80000000

#घोषणा XGBE_SFP_सूचीECT			7

/* I2C target addresses */
#घोषणा XGBE_SFP_SERIAL_ID_ADDRESS	0x50
#घोषणा XGBE_SFP_DIAG_INFO_ADDRESS	0x51
#घोषणा XGBE_SFP_PHY_ADDRESS		0x56
#घोषणा XGBE_GPIO_ADDRESS_PCA9555	0x20

/* SFP sideband संकेत indicators */
#घोषणा XGBE_GPIO_NO_TX_FAULT		BIT(0)
#घोषणा XGBE_GPIO_NO_RATE_SELECT	BIT(1)
#घोषणा XGBE_GPIO_NO_MOD_ABSENT		BIT(2)
#घोषणा XGBE_GPIO_NO_RX_LOS		BIT(3)

/* Rate-change complete रुको/retry count */
#घोषणा XGBE_RATECHANGE_COUNT		500

/* CDR delay values क्रम KR support (in usec) */
#घोषणा XGBE_CDR_DELAY_INIT		10000
#घोषणा XGBE_CDR_DELAY_INC		10000
#घोषणा XGBE_CDR_DELAY_MAX		100000

/* RRC frequency during link status check */
#घोषणा XGBE_RRC_FREQUENCY		10

क्रमागत xgbe_port_mode अणु
	XGBE_PORT_MODE_RSVD = 0,
	XGBE_PORT_MODE_BACKPLANE,
	XGBE_PORT_MODE_BACKPLANE_2500,
	XGBE_PORT_MODE_1000BASE_T,
	XGBE_PORT_MODE_1000BASE_X,
	XGBE_PORT_MODE_NBASE_T,
	XGBE_PORT_MODE_10GBASE_T,
	XGBE_PORT_MODE_10GBASE_R,
	XGBE_PORT_MODE_SFP,
	XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG,
	XGBE_PORT_MODE_MAX,
पूर्ण;

क्रमागत xgbe_conn_type अणु
	XGBE_CONN_TYPE_NONE = 0,
	XGBE_CONN_TYPE_SFP,
	XGBE_CONN_TYPE_MDIO,
	XGBE_CONN_TYPE_RSVD1,
	XGBE_CONN_TYPE_BACKPLANE,
	XGBE_CONN_TYPE_MAX,
पूर्ण;

/* SFP/SFP+ related definitions */
क्रमागत xgbe_sfp_comm अणु
	XGBE_SFP_COMM_सूचीECT = 0,
	XGBE_SFP_COMM_PCA9545,
पूर्ण;

क्रमागत xgbe_sfp_cable अणु
	XGBE_SFP_CABLE_UNKNOWN = 0,
	XGBE_SFP_CABLE_ACTIVE,
	XGBE_SFP_CABLE_PASSIVE,
पूर्ण;

क्रमागत xgbe_sfp_base अणु
	XGBE_SFP_BASE_UNKNOWN = 0,
	XGBE_SFP_BASE_1000_T,
	XGBE_SFP_BASE_1000_SX,
	XGBE_SFP_BASE_1000_LX,
	XGBE_SFP_BASE_1000_CX,
	XGBE_SFP_BASE_10000_SR,
	XGBE_SFP_BASE_10000_LR,
	XGBE_SFP_BASE_10000_LRM,
	XGBE_SFP_BASE_10000_ER,
	XGBE_SFP_BASE_10000_CR,
पूर्ण;

क्रमागत xgbe_sfp_speed अणु
	XGBE_SFP_SPEED_UNKNOWN = 0,
	XGBE_SFP_SPEED_100_1000,
	XGBE_SFP_SPEED_1000,
	XGBE_SFP_SPEED_10000,
पूर्ण;

/* SFP Serial ID Base ID values relative to an offset of 0 */
#घोषणा XGBE_SFP_BASE_ID			0
#घोषणा XGBE_SFP_ID_SFP				0x03

#घोषणा XGBE_SFP_BASE_EXT_ID			1
#घोषणा XGBE_SFP_EXT_ID_SFP			0x04

#घोषणा XGBE_SFP_BASE_10GBE_CC			3
#घोषणा XGBE_SFP_BASE_10GBE_CC_SR		BIT(4)
#घोषणा XGBE_SFP_BASE_10GBE_CC_LR		BIT(5)
#घोषणा XGBE_SFP_BASE_10GBE_CC_LRM		BIT(6)
#घोषणा XGBE_SFP_BASE_10GBE_CC_ER		BIT(7)

#घोषणा XGBE_SFP_BASE_1GBE_CC			6
#घोषणा XGBE_SFP_BASE_1GBE_CC_SX		BIT(0)
#घोषणा XGBE_SFP_BASE_1GBE_CC_LX		BIT(1)
#घोषणा XGBE_SFP_BASE_1GBE_CC_CX		BIT(2)
#घोषणा XGBE_SFP_BASE_1GBE_CC_T			BIT(3)

#घोषणा XGBE_SFP_BASE_CABLE			8
#घोषणा XGBE_SFP_BASE_CABLE_PASSIVE		BIT(2)
#घोषणा XGBE_SFP_BASE_CABLE_ACTIVE		BIT(3)

#घोषणा XGBE_SFP_BASE_BR			12
#घोषणा XGBE_SFP_BASE_BR_1GBE_MIN		0x0a
#घोषणा XGBE_SFP_BASE_BR_1GBE_MAX		0x0d
#घोषणा XGBE_SFP_BASE_BR_10GBE_MIN		0x64
#घोषणा XGBE_SFP_BASE_BR_10GBE_MAX		0x68

#घोषणा XGBE_SFP_BASE_CU_CABLE_LEN		18

#घोषणा XGBE_SFP_BASE_VENDOR_NAME		20
#घोषणा XGBE_SFP_BASE_VENDOR_NAME_LEN		16
#घोषणा XGBE_SFP_BASE_VENDOR_PN			40
#घोषणा XGBE_SFP_BASE_VENDOR_PN_LEN		16
#घोषणा XGBE_SFP_BASE_VENDOR_REV		56
#घोषणा XGBE_SFP_BASE_VENDOR_REV_LEN		4

#घोषणा XGBE_SFP_BASE_CC			63

/* SFP Serial ID Extended ID values relative to an offset of 64 */
#घोषणा XGBE_SFP_BASE_VENDOR_SN			4
#घोषणा XGBE_SFP_BASE_VENDOR_SN_LEN		16

#घोषणा XGBE_SFP_EXTD_OPT1			1
#घोषणा XGBE_SFP_EXTD_OPT1_RX_LOS		BIT(1)
#घोषणा XGBE_SFP_EXTD_OPT1_TX_FAULT		BIT(3)

#घोषणा XGBE_SFP_EXTD_DIAG			28
#घोषणा XGBE_SFP_EXTD_DIAG_ADDR_CHANGE		BIT(2)

#घोषणा XGBE_SFP_EXTD_SFF_8472			30

#घोषणा XGBE_SFP_EXTD_CC			31

काष्ठा xgbe_sfp_eeprom अणु
	u8 base[64];
	u8 extd[32];
	u8 venकरोr[32];
पूर्ण;

#घोषणा XGBE_SFP_DIAGS_SUPPORTED(_x)			\
	((_x)->extd[XGBE_SFP_EXTD_SFF_8472] &&		\
	 !((_x)->extd[XGBE_SFP_EXTD_DIAG] & XGBE_SFP_EXTD_DIAG_ADDR_CHANGE))

#घोषणा XGBE_SFP_EEPROM_BASE_LEN	256
#घोषणा XGBE_SFP_EEPROM_DIAG_LEN	256
#घोषणा XGBE_SFP_EEPROM_MAX		(XGBE_SFP_EEPROM_BASE_LEN +	\
					 XGBE_SFP_EEPROM_DIAG_LEN)

#घोषणा XGBE_BEL_FUSE_VENDOR	"BEL-FUSE        "
#घोषणा XGBE_BEL_FUSE_PARTNO	"1GBT-SFP06      "

काष्ठा xgbe_sfp_ascii अणु
	जोड़ अणु
		अक्षर venकरोr[XGBE_SFP_BASE_VENDOR_NAME_LEN + 1];
		अक्षर partno[XGBE_SFP_BASE_VENDOR_PN_LEN + 1];
		अक्षर rev[XGBE_SFP_BASE_VENDOR_REV_LEN + 1];
		अक्षर serno[XGBE_SFP_BASE_VENDOR_SN_LEN + 1];
	पूर्ण u;
पूर्ण;

/* MDIO PHY reset types */
क्रमागत xgbe_mdio_reset अणु
	XGBE_MDIO_RESET_NONE = 0,
	XGBE_MDIO_RESET_I2C_GPIO,
	XGBE_MDIO_RESET_INT_GPIO,
	XGBE_MDIO_RESET_MAX,
पूर्ण;

/* Re-driver related definitions */
क्रमागत xgbe_phy_redrv_अगर अणु
	XGBE_PHY_REDRV_IF_MDIO = 0,
	XGBE_PHY_REDRV_IF_I2C,
	XGBE_PHY_REDRV_IF_MAX,
पूर्ण;

क्रमागत xgbe_phy_redrv_model अणु
	XGBE_PHY_REDRV_MODEL_4223 = 0,
	XGBE_PHY_REDRV_MODEL_4227,
	XGBE_PHY_REDRV_MODEL_MAX,
पूर्ण;

क्रमागत xgbe_phy_redrv_mode अणु
	XGBE_PHY_REDRV_MODE_CX = 5,
	XGBE_PHY_REDRV_MODE_SR = 9,
पूर्ण;

#घोषणा XGBE_PHY_REDRV_MODE_REG	0x12b0

/* PHY related configuration inक्रमmation */
काष्ठा xgbe_phy_data अणु
	क्रमागत xgbe_port_mode port_mode;

	अचिन्हित पूर्णांक port_id;

	अचिन्हित पूर्णांक port_speeds;

	क्रमागत xgbe_conn_type conn_type;

	क्रमागत xgbe_mode cur_mode;
	क्रमागत xgbe_mode start_mode;

	अचिन्हित पूर्णांक rrc_count;

	अचिन्हित पूर्णांक mdio_addr;

	/* SFP Support */
	क्रमागत xgbe_sfp_comm sfp_comm;
	अचिन्हित पूर्णांक sfp_mux_address;
	अचिन्हित पूर्णांक sfp_mux_channel;

	अचिन्हित पूर्णांक sfp_gpio_address;
	अचिन्हित पूर्णांक sfp_gpio_mask;
	अचिन्हित पूर्णांक sfp_gpio_inमाला_दो;
	अचिन्हित पूर्णांक sfp_gpio_rx_los;
	अचिन्हित पूर्णांक sfp_gpio_tx_fault;
	अचिन्हित पूर्णांक sfp_gpio_mod_असलent;
	अचिन्हित पूर्णांक sfp_gpio_rate_select;

	अचिन्हित पूर्णांक sfp_rx_los;
	अचिन्हित पूर्णांक sfp_tx_fault;
	अचिन्हित पूर्णांक sfp_mod_असलent;
	अचिन्हित पूर्णांक sfp_changed;
	अचिन्हित पूर्णांक sfp_phy_avail;
	अचिन्हित पूर्णांक sfp_cable_len;
	क्रमागत xgbe_sfp_base sfp_base;
	क्रमागत xgbe_sfp_cable sfp_cable;
	क्रमागत xgbe_sfp_speed sfp_speed;
	काष्ठा xgbe_sfp_eeprom sfp_eeprom;

	/* External PHY support */
	क्रमागत xgbe_mdio_mode phydev_mode;
	काष्ठा mii_bus *mii;
	काष्ठा phy_device *phydev;
	क्रमागत xgbe_mdio_reset mdio_reset;
	अचिन्हित पूर्णांक mdio_reset_addr;
	अचिन्हित पूर्णांक mdio_reset_gpio;

	/* Re-driver support */
	अचिन्हित पूर्णांक redrv;
	अचिन्हित पूर्णांक redrv_अगर;
	अचिन्हित पूर्णांक redrv_addr;
	अचिन्हित पूर्णांक redrv_lane;
	अचिन्हित पूर्णांक redrv_model;

	/* KR AN support */
	अचिन्हित पूर्णांक phy_cdr_notrack;
	अचिन्हित पूर्णांक phy_cdr_delay;
पूर्ण;

/* I2C, MDIO and GPIO lines are muxed, so only one device at a समय */
अटल DEFINE_MUTEX(xgbe_phy_comm_lock);

अटल क्रमागत xgbe_an_mode xgbe_phy_an_mode(काष्ठा xgbe_prv_data *pdata);

अटल पूर्णांक xgbe_phy_i2c_xfer(काष्ठा xgbe_prv_data *pdata,
			     काष्ठा xgbe_i2c_op *i2c_op)
अणु
	वापस pdata->i2c_अगर.i2c_xfer(pdata, i2c_op);
पूर्ण

अटल पूर्णांक xgbe_phy_redrv_ग_लिखो(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक val)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	काष्ठा xgbe_i2c_op i2c_op;
	__be16 *redrv_val;
	u8 redrv_data[5], csum;
	अचिन्हित पूर्णांक i, retry;
	पूर्णांक ret;

	/* High byte of रेजिस्टर contains पढ़ो/ग_लिखो indicator */
	redrv_data[0] = ((reg >> 8) & 0xff) << 1;
	redrv_data[1] = reg & 0xff;
	redrv_val = (__be16 *)&redrv_data[2];
	*redrv_val = cpu_to_be16(val);

	/* Calculate 1 byte checksum */
	csum = 0;
	क्रम (i = 0; i < 4; i++) अणु
		csum += redrv_data[i];
		अगर (redrv_data[i] > csum)
			csum++;
	पूर्ण
	redrv_data[4] = ~csum;

	retry = 1;
again1:
	i2c_op.cmd = XGBE_I2C_CMD_WRITE;
	i2c_op.target = phy_data->redrv_addr;
	i2c_op.len = माप(redrv_data);
	i2c_op.buf = redrv_data;
	ret = xgbe_phy_i2c_xfer(pdata, &i2c_op);
	अगर (ret) अणु
		अगर ((ret == -EAGAIN) && retry--)
			जाओ again1;

		वापस ret;
	पूर्ण

	retry = 1;
again2:
	i2c_op.cmd = XGBE_I2C_CMD_READ;
	i2c_op.target = phy_data->redrv_addr;
	i2c_op.len = 1;
	i2c_op.buf = redrv_data;
	ret = xgbe_phy_i2c_xfer(pdata, &i2c_op);
	अगर (ret) अणु
		अगर ((ret == -EAGAIN) && retry--)
			जाओ again2;

		वापस ret;
	पूर्ण

	अगर (redrv_data[0] != 0xff) अणु
		netअगर_dbg(pdata, drv, pdata->netdev,
			  "Redriver write checksum error\n");
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_i2c_ग_लिखो(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक target,
			      व्योम *val, अचिन्हित पूर्णांक val_len)
अणु
	काष्ठा xgbe_i2c_op i2c_op;
	पूर्णांक retry, ret;

	retry = 1;
again:
	/* Write the specfied रेजिस्टर */
	i2c_op.cmd = XGBE_I2C_CMD_WRITE;
	i2c_op.target = target;
	i2c_op.len = val_len;
	i2c_op.buf = val;
	ret = xgbe_phy_i2c_xfer(pdata, &i2c_op);
	अगर ((ret == -EAGAIN) && retry--)
		जाओ again;

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_i2c_पढ़ो(काष्ठा xgbe_prv_data *pdata, अचिन्हित पूर्णांक target,
			     व्योम *reg, अचिन्हित पूर्णांक reg_len,
			     व्योम *val, अचिन्हित पूर्णांक val_len)
अणु
	काष्ठा xgbe_i2c_op i2c_op;
	पूर्णांक retry, ret;

	retry = 1;
again1:
	/* Set the specअगरied रेजिस्टर to पढ़ो */
	i2c_op.cmd = XGBE_I2C_CMD_WRITE;
	i2c_op.target = target;
	i2c_op.len = reg_len;
	i2c_op.buf = reg;
	ret = xgbe_phy_i2c_xfer(pdata, &i2c_op);
	अगर (ret) अणु
		अगर ((ret == -EAGAIN) && retry--)
			जाओ again1;

		वापस ret;
	पूर्ण

	retry = 1;
again2:
	/* Read the specfied रेजिस्टर */
	i2c_op.cmd = XGBE_I2C_CMD_READ;
	i2c_op.target = target;
	i2c_op.len = val_len;
	i2c_op.buf = val;
	ret = xgbe_phy_i2c_xfer(pdata, &i2c_op);
	अगर ((ret == -EAGAIN) && retry--)
		जाओ again2;

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_sfp_put_mux(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	काष्ठा xgbe_i2c_op i2c_op;
	u8 mux_channel;

	अगर (phy_data->sfp_comm == XGBE_SFP_COMM_सूचीECT)
		वापस 0;

	/* Select no mux channels */
	mux_channel = 0;
	i2c_op.cmd = XGBE_I2C_CMD_WRITE;
	i2c_op.target = phy_data->sfp_mux_address;
	i2c_op.len = माप(mux_channel);
	i2c_op.buf = &mux_channel;

	वापस xgbe_phy_i2c_xfer(pdata, &i2c_op);
पूर्ण

अटल पूर्णांक xgbe_phy_sfp_get_mux(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	काष्ठा xgbe_i2c_op i2c_op;
	u8 mux_channel;

	अगर (phy_data->sfp_comm == XGBE_SFP_COMM_सूचीECT)
		वापस 0;

	/* Select desired mux channel */
	mux_channel = 1 << phy_data->sfp_mux_channel;
	i2c_op.cmd = XGBE_I2C_CMD_WRITE;
	i2c_op.target = phy_data->sfp_mux_address;
	i2c_op.len = माप(mux_channel);
	i2c_op.buf = &mux_channel;

	वापस xgbe_phy_i2c_xfer(pdata, &i2c_op);
पूर्ण

अटल व्योम xgbe_phy_put_comm_ownership(काष्ठा xgbe_prv_data *pdata)
अणु
	mutex_unlock(&xgbe_phy_comm_lock);
पूर्ण

अटल पूर्णांक xgbe_phy_get_comm_ownership(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक mutex_id;

	/* The I2C and MDIO/GPIO bus is multiplexed between multiple devices,
	 * the driver needs to take the software mutex and then the hardware
	 * mutexes beक्रमe being able to use the busses.
	 */
	mutex_lock(&xgbe_phy_comm_lock);

	/* Clear the mutexes */
	XP_IOWRITE(pdata, XP_I2C_MUTEX, XGBE_MUTEX_RELEASE);
	XP_IOWRITE(pdata, XP_MDIO_MUTEX, XGBE_MUTEX_RELEASE);

	/* Mutex क्रमmats are the same क्रम I2C and MDIO/GPIO */
	mutex_id = 0;
	XP_SET_BITS(mutex_id, XP_I2C_MUTEX, ID, phy_data->port_id);
	XP_SET_BITS(mutex_id, XP_I2C_MUTEX, ACTIVE, 1);

	समयout = jअगरfies + (5 * HZ);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		/* Must be all zeroes in order to obtain the mutex */
		अगर (XP_IOREAD(pdata, XP_I2C_MUTEX) ||
		    XP_IOREAD(pdata, XP_MDIO_MUTEX)) अणु
			usleep_range(100, 200);
			जारी;
		पूर्ण

		/* Obtain the mutex */
		XP_IOWRITE(pdata, XP_I2C_MUTEX, mutex_id);
		XP_IOWRITE(pdata, XP_MDIO_MUTEX, mutex_id);

		वापस 0;
	पूर्ण

	mutex_unlock(&xgbe_phy_comm_lock);

	netdev_err(pdata->netdev, "unable to obtain hardware mutexes\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक xgbe_phy_mdio_mii_ग_लिखो(काष्ठा xgbe_prv_data *pdata, पूर्णांक addr,
				   पूर्णांक reg, u16 val)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	अगर (reg & MII_ADDR_C45) अणु
		अगर (phy_data->phydev_mode != XGBE_MDIO_MODE_CL45)
			वापस -ENOTSUPP;
	पूर्ण अन्यथा अणु
		अगर (phy_data->phydev_mode != XGBE_MDIO_MODE_CL22)
			वापस -ENOTSUPP;
	पूर्ण

	वापस pdata->hw_अगर.ग_लिखो_ext_mii_regs(pdata, addr, reg, val);
पूर्ण

अटल पूर्णांक xgbe_phy_i2c_mii_ग_लिखो(काष्ठा xgbe_prv_data *pdata, पूर्णांक reg, u16 val)
अणु
	__be16 *mii_val;
	u8 mii_data[3];
	पूर्णांक ret;

	ret = xgbe_phy_sfp_get_mux(pdata);
	अगर (ret)
		वापस ret;

	mii_data[0] = reg & 0xff;
	mii_val = (__be16 *)&mii_data[1];
	*mii_val = cpu_to_be16(val);

	ret = xgbe_phy_i2c_ग_लिखो(pdata, XGBE_SFP_PHY_ADDRESS,
				 mii_data, माप(mii_data));

	xgbe_phy_sfp_put_mux(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_mii_ग_लिखो(काष्ठा mii_bus *mii, पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	काष्ठा xgbe_prv_data *pdata = mii->priv;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	पूर्णांक ret;

	ret = xgbe_phy_get_comm_ownership(pdata);
	अगर (ret)
		वापस ret;

	अगर (phy_data->conn_type == XGBE_CONN_TYPE_SFP)
		ret = xgbe_phy_i2c_mii_ग_लिखो(pdata, reg, val);
	अन्यथा अगर (phy_data->conn_type & XGBE_CONN_TYPE_MDIO)
		ret = xgbe_phy_mdio_mii_ग_लिखो(pdata, addr, reg, val);
	अन्यथा
		ret = -ENOTSUPP;

	xgbe_phy_put_comm_ownership(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_mdio_mii_पढ़ो(काष्ठा xgbe_prv_data *pdata, पूर्णांक addr,
				  पूर्णांक reg)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	अगर (reg & MII_ADDR_C45) अणु
		अगर (phy_data->phydev_mode != XGBE_MDIO_MODE_CL45)
			वापस -ENOTSUPP;
	पूर्ण अन्यथा अणु
		अगर (phy_data->phydev_mode != XGBE_MDIO_MODE_CL22)
			वापस -ENOTSUPP;
	पूर्ण

	वापस pdata->hw_अगर.पढ़ो_ext_mii_regs(pdata, addr, reg);
पूर्ण

अटल पूर्णांक xgbe_phy_i2c_mii_पढ़ो(काष्ठा xgbe_prv_data *pdata, पूर्णांक reg)
अणु
	__be16 mii_val;
	u8 mii_reg;
	पूर्णांक ret;

	ret = xgbe_phy_sfp_get_mux(pdata);
	अगर (ret)
		वापस ret;

	mii_reg = reg;
	ret = xgbe_phy_i2c_पढ़ो(pdata, XGBE_SFP_PHY_ADDRESS,
				&mii_reg, माप(mii_reg),
				&mii_val, माप(mii_val));
	अगर (!ret)
		ret = be16_to_cpu(mii_val);

	xgbe_phy_sfp_put_mux(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_mii_पढ़ो(काष्ठा mii_bus *mii, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा xgbe_prv_data *pdata = mii->priv;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	पूर्णांक ret;

	ret = xgbe_phy_get_comm_ownership(pdata);
	अगर (ret)
		वापस ret;

	अगर (phy_data->conn_type == XGBE_CONN_TYPE_SFP)
		ret = xgbe_phy_i2c_mii_पढ़ो(pdata, reg);
	अन्यथा अगर (phy_data->conn_type & XGBE_CONN_TYPE_MDIO)
		ret = xgbe_phy_mdio_mii_पढ़ो(pdata, addr, reg);
	अन्यथा
		ret = -ENOTSUPP;

	xgbe_phy_put_comm_ownership(pdata);

	वापस ret;
पूर्ण

अटल व्योम xgbe_phy_sfp_phy_settings(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	अगर (!phy_data->sfp_mod_असलent && !phy_data->sfp_changed)
		वापस;

	XGBE_ZERO_SUP(lks);

	अगर (phy_data->sfp_mod_असलent) अणु
		pdata->phy.speed = SPEED_UNKNOWN;
		pdata->phy.duplex = DUPLEX_UNKNOWN;
		pdata->phy.स्वतःneg = AUTONEG_ENABLE;
		pdata->phy.छोड़ो_स्वतःneg = AUTONEG_ENABLE;

		XGBE_SET_SUP(lks, Autoneg);
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		XGBE_SET_SUP(lks, TP);
		XGBE_SET_SUP(lks, FIBRE);

		XGBE_LM_COPY(lks, advertising, lks, supported);

		वापस;
	पूर्ण

	चयन (phy_data->sfp_base) अणु
	हाल XGBE_SFP_BASE_1000_T:
	हाल XGBE_SFP_BASE_1000_SX:
	हाल XGBE_SFP_BASE_1000_LX:
	हाल XGBE_SFP_BASE_1000_CX:
		pdata->phy.speed = SPEED_UNKNOWN;
		pdata->phy.duplex = DUPLEX_UNKNOWN;
		pdata->phy.स्वतःneg = AUTONEG_ENABLE;
		pdata->phy.छोड़ो_स्वतःneg = AUTONEG_ENABLE;
		XGBE_SET_SUP(lks, Autoneg);
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		अगर (phy_data->sfp_base == XGBE_SFP_BASE_1000_T) अणु
			अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100)
				XGBE_SET_SUP(lks, 100baseT_Full);
			अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000)
				XGBE_SET_SUP(lks, 1000baseT_Full);
		पूर्ण अन्यथा अणु
			अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000)
				XGBE_SET_SUP(lks, 1000baseX_Full);
		पूर्ण
		अवरोध;
	हाल XGBE_SFP_BASE_10000_SR:
	हाल XGBE_SFP_BASE_10000_LR:
	हाल XGBE_SFP_BASE_10000_LRM:
	हाल XGBE_SFP_BASE_10000_ER:
	हाल XGBE_SFP_BASE_10000_CR:
		pdata->phy.speed = SPEED_10000;
		pdata->phy.duplex = DUPLEX_FULL;
		pdata->phy.स्वतःneg = AUTONEG_DISABLE;
		pdata->phy.छोड़ो_स्वतःneg = AUTONEG_DISABLE;
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000) अणु
			चयन (phy_data->sfp_base) अणु
			हाल XGBE_SFP_BASE_10000_SR:
				XGBE_SET_SUP(lks, 10000baseSR_Full);
				अवरोध;
			हाल XGBE_SFP_BASE_10000_LR:
				XGBE_SET_SUP(lks, 10000baseLR_Full);
				अवरोध;
			हाल XGBE_SFP_BASE_10000_LRM:
				XGBE_SET_SUP(lks, 10000baseLRM_Full);
				अवरोध;
			हाल XGBE_SFP_BASE_10000_ER:
				XGBE_SET_SUP(lks, 10000baseER_Full);
				अवरोध;
			हाल XGBE_SFP_BASE_10000_CR:
				XGBE_SET_SUP(lks, 10000baseCR_Full);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		pdata->phy.speed = SPEED_UNKNOWN;
		pdata->phy.duplex = DUPLEX_UNKNOWN;
		pdata->phy.स्वतःneg = AUTONEG_DISABLE;
		pdata->phy.छोड़ो_स्वतःneg = AUTONEG_DISABLE;
		अवरोध;
	पूर्ण

	चयन (phy_data->sfp_base) अणु
	हाल XGBE_SFP_BASE_1000_T:
	हाल XGBE_SFP_BASE_1000_CX:
	हाल XGBE_SFP_BASE_10000_CR:
		XGBE_SET_SUP(lks, TP);
		अवरोध;
	शेष:
		XGBE_SET_SUP(lks, FIBRE);
		अवरोध;
	पूर्ण

	XGBE_LM_COPY(lks, advertising, lks, supported);
पूर्ण

अटल bool xgbe_phy_sfp_bit_rate(काष्ठा xgbe_sfp_eeprom *sfp_eeprom,
				  क्रमागत xgbe_sfp_speed sfp_speed)
अणु
	u8 *sfp_base, min, max;

	sfp_base = sfp_eeprom->base;

	चयन (sfp_speed) अणु
	हाल XGBE_SFP_SPEED_1000:
		min = XGBE_SFP_BASE_BR_1GBE_MIN;
		max = XGBE_SFP_BASE_BR_1GBE_MAX;
		अवरोध;
	हाल XGBE_SFP_SPEED_10000:
		min = XGBE_SFP_BASE_BR_10GBE_MIN;
		max = XGBE_SFP_BASE_BR_10GBE_MAX;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस ((sfp_base[XGBE_SFP_BASE_BR] >= min) &&
		(sfp_base[XGBE_SFP_BASE_BR] <= max));
पूर्ण

अटल व्योम xgbe_phy_मुक्त_phy_device(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	अगर (phy_data->phydev) अणु
		phy_detach(phy_data->phydev);
		phy_device_हटाओ(phy_data->phydev);
		phy_device_मुक्त(phy_data->phydev);
		phy_data->phydev = शून्य;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_finisar_phy_quirks(काष्ठा xgbe_prv_data *pdata)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported) = अणु 0, पूर्ण;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	अचिन्हित पूर्णांक phy_id = phy_data->phydev->phy_id;

	अगर (phy_data->port_mode != XGBE_PORT_MODE_SFP)
		वापस false;

	अगर ((phy_id & 0xfffffff0) != 0x01ff0cc0)
		वापस false;

	/* Enable Base-T AN */
	phy_ग_लिखो(phy_data->phydev, 0x16, 0x0001);
	phy_ग_लिखो(phy_data->phydev, 0x00, 0x9140);
	phy_ग_लिखो(phy_data->phydev, 0x16, 0x0000);

	/* Enable SGMII at 100Base-T/1000Base-T Full Duplex */
	phy_ग_लिखो(phy_data->phydev, 0x1b, 0x9084);
	phy_ग_लिखो(phy_data->phydev, 0x09, 0x0e00);
	phy_ग_लिखो(phy_data->phydev, 0x00, 0x8140);
	phy_ग_लिखो(phy_data->phydev, 0x04, 0x0d01);
	phy_ग_लिखो(phy_data->phydev, 0x00, 0x9140);

	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       supported);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       supported);

	linkmode_copy(phy_data->phydev->supported, supported);

	phy_support_asym_छोड़ो(phy_data->phydev);

	netअगर_dbg(pdata, drv, pdata->netdev,
		  "Finisar PHY quirk in place\n");

	वापस true;
पूर्ण

अटल bool xgbe_phy_belfuse_phy_quirks(काष्ठा xgbe_prv_data *pdata)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported) = अणु 0, पूर्ण;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	काष्ठा xgbe_sfp_eeprom *sfp_eeprom = &phy_data->sfp_eeprom;
	अचिन्हित पूर्णांक phy_id = phy_data->phydev->phy_id;
	पूर्णांक reg;

	अगर (phy_data->port_mode != XGBE_PORT_MODE_SFP)
		वापस false;

	अगर (स_भेद(&sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_NAME],
		   XGBE_BEL_FUSE_VENDOR, XGBE_SFP_BASE_VENDOR_NAME_LEN))
		वापस false;

	/* For Bel-Fuse, use the extra AN flag */
	pdata->an_again = 1;

	अगर (स_भेद(&sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_PN],
		   XGBE_BEL_FUSE_PARTNO, XGBE_SFP_BASE_VENDOR_PN_LEN))
		वापस false;

	अगर ((phy_id & 0xfffffff0) != 0x03625d10)
		वापस false;

	/* Reset PHY - रुको क्रम self-clearing reset bit to clear */
	genphy_soft_reset(phy_data->phydev);

	/* Disable RGMII mode */
	phy_ग_लिखो(phy_data->phydev, 0x18, 0x7007);
	reg = phy_पढ़ो(phy_data->phydev, 0x18);
	phy_ग_लिखो(phy_data->phydev, 0x18, reg & ~0x0080);

	/* Enable fiber रेजिस्टर bank */
	phy_ग_लिखो(phy_data->phydev, 0x1c, 0x7c00);
	reg = phy_पढ़ो(phy_data->phydev, 0x1c);
	reg &= 0x03ff;
	reg &= ~0x0001;
	phy_ग_लिखो(phy_data->phydev, 0x1c, 0x8000 | 0x7c00 | reg | 0x0001);

	/* Power करोwn SerDes */
	reg = phy_पढ़ो(phy_data->phydev, 0x00);
	phy_ग_लिखो(phy_data->phydev, 0x00, reg | 0x00800);

	/* Configure SGMII-to-Copper mode */
	phy_ग_लिखो(phy_data->phydev, 0x1c, 0x7c00);
	reg = phy_पढ़ो(phy_data->phydev, 0x1c);
	reg &= 0x03ff;
	reg &= ~0x0006;
	phy_ग_लिखो(phy_data->phydev, 0x1c, 0x8000 | 0x7c00 | reg | 0x0004);

	/* Power up SerDes */
	reg = phy_पढ़ो(phy_data->phydev, 0x00);
	phy_ग_लिखो(phy_data->phydev, 0x00, reg & ~0x00800);

	/* Enable copper रेजिस्टर bank */
	phy_ग_लिखो(phy_data->phydev, 0x1c, 0x7c00);
	reg = phy_पढ़ो(phy_data->phydev, 0x1c);
	reg &= 0x03ff;
	reg &= ~0x0001;
	phy_ग_लिखो(phy_data->phydev, 0x1c, 0x8000 | 0x7c00 | reg);

	/* Power up SerDes */
	reg = phy_पढ़ो(phy_data->phydev, 0x00);
	phy_ग_लिखो(phy_data->phydev, 0x00, reg & ~0x00800);

	linkmode_set_bit_array(phy_10_100_features_array,
			       ARRAY_SIZE(phy_10_100_features_array),
			       supported);
	linkmode_set_bit_array(phy_gbit_features_array,
			       ARRAY_SIZE(phy_gbit_features_array),
			       supported);
	linkmode_copy(phy_data->phydev->supported, supported);
	phy_support_asym_छोड़ो(phy_data->phydev);

	netअगर_dbg(pdata, drv, pdata->netdev,
		  "BelFuse PHY quirk in place\n");

	वापस true;
पूर्ण

अटल व्योम xgbe_phy_बाह्यal_phy_quirks(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (xgbe_phy_belfuse_phy_quirks(pdata))
		वापस;

	अगर (xgbe_phy_finisar_phy_quirks(pdata))
		वापस;
पूर्ण

अटल पूर्णांक xgbe_phy_find_phy_device(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	काष्ठा phy_device *phydev;
	पूर्णांक ret;

	/* If we alपढ़ोy have a PHY, just वापस */
	अगर (phy_data->phydev)
		वापस 0;

	/* Clear the extra AN flag */
	pdata->an_again = 0;

	/* Check क्रम the use of an बाह्यal PHY */
	अगर (phy_data->phydev_mode == XGBE_MDIO_MODE_NONE)
		वापस 0;

	/* For SFP, only use an बाह्यal PHY अगर available */
	अगर ((phy_data->port_mode == XGBE_PORT_MODE_SFP) &&
	    !phy_data->sfp_phy_avail)
		वापस 0;

	/* Set the proper MDIO mode क्रम the PHY */
	ret = pdata->hw_अगर.set_ext_mii_mode(pdata, phy_data->mdio_addr,
					    phy_data->phydev_mode);
	अगर (ret) अणु
		netdev_err(pdata->netdev,
			   "mdio port/clause not compatible (%u/%u)\n",
			   phy_data->mdio_addr, phy_data->phydev_mode);
		वापस ret;
	पूर्ण

	/* Create and connect to the PHY device */
	phydev = get_phy_device(phy_data->mii, phy_data->mdio_addr,
				(phy_data->phydev_mode == XGBE_MDIO_MODE_CL45));
	अगर (IS_ERR(phydev)) अणु
		netdev_err(pdata->netdev, "get_phy_device failed\n");
		वापस -ENODEV;
	पूर्ण
	netअगर_dbg(pdata, drv, pdata->netdev, "external PHY id is %#010x\n",
		  phydev->phy_id);

	/*TODO: If c45, add request_module based on one of the MMD ids? */

	ret = phy_device_रेजिस्टर(phydev);
	अगर (ret) अणु
		netdev_err(pdata->netdev, "phy_device_register failed\n");
		phy_device_मुक्त(phydev);
		वापस ret;
	पूर्ण

	ret = phy_attach_direct(pdata->netdev, phydev, phydev->dev_flags,
				PHY_INTERFACE_MODE_SGMII);
	अगर (ret) अणु
		netdev_err(pdata->netdev, "phy_attach_direct failed\n");
		phy_device_हटाओ(phydev);
		phy_device_मुक्त(phydev);
		वापस ret;
	पूर्ण
	phy_data->phydev = phydev;

	xgbe_phy_बाह्यal_phy_quirks(pdata);

	linkmode_and(phydev->advertising, phydev->advertising,
		     lks->link_modes.advertising);

	phy_start_aneg(phy_data->phydev);

	वापस 0;
पूर्ण

अटल व्योम xgbe_phy_sfp_बाह्यal_phy(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	पूर्णांक ret;

	अगर (!phy_data->sfp_changed)
		वापस;

	phy_data->sfp_phy_avail = 0;

	अगर (phy_data->sfp_base != XGBE_SFP_BASE_1000_T)
		वापस;

	/* Check access to the PHY by पढ़ोing CTRL1 */
	ret = xgbe_phy_i2c_mii_पढ़ो(pdata, MII_BMCR);
	अगर (ret < 0)
		वापस;

	/* Successfully accessed the PHY */
	phy_data->sfp_phy_avail = 1;
पूर्ण

अटल bool xgbe_phy_check_sfp_rx_los(काष्ठा xgbe_phy_data *phy_data)
अणु
	u8 *sfp_extd = phy_data->sfp_eeprom.extd;

	अगर (!(sfp_extd[XGBE_SFP_EXTD_OPT1] & XGBE_SFP_EXTD_OPT1_RX_LOS))
		वापस false;

	अगर (phy_data->sfp_gpio_mask & XGBE_GPIO_NO_RX_LOS)
		वापस false;

	अगर (phy_data->sfp_gpio_inमाला_दो & (1 << phy_data->sfp_gpio_rx_los))
		वापस true;

	वापस false;
पूर्ण

अटल bool xgbe_phy_check_sfp_tx_fault(काष्ठा xgbe_phy_data *phy_data)
अणु
	u8 *sfp_extd = phy_data->sfp_eeprom.extd;

	अगर (!(sfp_extd[XGBE_SFP_EXTD_OPT1] & XGBE_SFP_EXTD_OPT1_TX_FAULT))
		वापस false;

	अगर (phy_data->sfp_gpio_mask & XGBE_GPIO_NO_TX_FAULT)
		वापस false;

	अगर (phy_data->sfp_gpio_inमाला_दो & (1 << phy_data->sfp_gpio_tx_fault))
		वापस true;

	वापस false;
पूर्ण

अटल bool xgbe_phy_check_sfp_mod_असलent(काष्ठा xgbe_phy_data *phy_data)
अणु
	अगर (phy_data->sfp_gpio_mask & XGBE_GPIO_NO_MOD_ABSENT)
		वापस false;

	अगर (phy_data->sfp_gpio_inमाला_दो & (1 << phy_data->sfp_gpio_mod_असलent))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम xgbe_phy_sfp_parse_eeprom(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	काष्ठा xgbe_sfp_eeprom *sfp_eeprom = &phy_data->sfp_eeprom;
	u8 *sfp_base;

	sfp_base = sfp_eeprom->base;

	अगर (sfp_base[XGBE_SFP_BASE_ID] != XGBE_SFP_ID_SFP)
		वापस;

	अगर (sfp_base[XGBE_SFP_BASE_EXT_ID] != XGBE_SFP_EXT_ID_SFP)
		वापस;

	/* Update transceiver संकेतs (eeprom extd/options) */
	phy_data->sfp_tx_fault = xgbe_phy_check_sfp_tx_fault(phy_data);
	phy_data->sfp_rx_los = xgbe_phy_check_sfp_rx_los(phy_data);

	/* Assume ACTIVE cable unless told it is PASSIVE */
	अगर (sfp_base[XGBE_SFP_BASE_CABLE] & XGBE_SFP_BASE_CABLE_PASSIVE) अणु
		phy_data->sfp_cable = XGBE_SFP_CABLE_PASSIVE;
		phy_data->sfp_cable_len = sfp_base[XGBE_SFP_BASE_CU_CABLE_LEN];
	पूर्ण अन्यथा अणु
		phy_data->sfp_cable = XGBE_SFP_CABLE_ACTIVE;
	पूर्ण

	/* Determine the type of SFP */
	अगर (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_SR)
		phy_data->sfp_base = XGBE_SFP_BASE_10000_SR;
	अन्यथा अगर (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_LR)
		phy_data->sfp_base = XGBE_SFP_BASE_10000_LR;
	अन्यथा अगर (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_LRM)
		phy_data->sfp_base = XGBE_SFP_BASE_10000_LRM;
	अन्यथा अगर (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_ER)
		phy_data->sfp_base = XGBE_SFP_BASE_10000_ER;
	अन्यथा अगर (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_SX)
		phy_data->sfp_base = XGBE_SFP_BASE_1000_SX;
	अन्यथा अगर (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_LX)
		phy_data->sfp_base = XGBE_SFP_BASE_1000_LX;
	अन्यथा अगर (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_CX)
		phy_data->sfp_base = XGBE_SFP_BASE_1000_CX;
	अन्यथा अगर (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_T)
		phy_data->sfp_base = XGBE_SFP_BASE_1000_T;
	अन्यथा अगर ((phy_data->sfp_cable == XGBE_SFP_CABLE_PASSIVE) &&
		 xgbe_phy_sfp_bit_rate(sfp_eeprom, XGBE_SFP_SPEED_10000))
		phy_data->sfp_base = XGBE_SFP_BASE_10000_CR;

	चयन (phy_data->sfp_base) अणु
	हाल XGBE_SFP_BASE_1000_T:
		phy_data->sfp_speed = XGBE_SFP_SPEED_100_1000;
		अवरोध;
	हाल XGBE_SFP_BASE_1000_SX:
	हाल XGBE_SFP_BASE_1000_LX:
	हाल XGBE_SFP_BASE_1000_CX:
		phy_data->sfp_speed = XGBE_SFP_SPEED_1000;
		अवरोध;
	हाल XGBE_SFP_BASE_10000_SR:
	हाल XGBE_SFP_BASE_10000_LR:
	हाल XGBE_SFP_BASE_10000_LRM:
	हाल XGBE_SFP_BASE_10000_ER:
	हाल XGBE_SFP_BASE_10000_CR:
		phy_data->sfp_speed = XGBE_SFP_SPEED_10000;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_sfp_eeprom_info(काष्ठा xgbe_prv_data *pdata,
				     काष्ठा xgbe_sfp_eeprom *sfp_eeprom)
अणु
	काष्ठा xgbe_sfp_ascii sfp_ascii;
	अक्षर *sfp_data = (अक्षर *)&sfp_ascii;

	netअगर_dbg(pdata, drv, pdata->netdev, "SFP detected:\n");
	स_नकल(sfp_data, &sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_NAME],
	       XGBE_SFP_BASE_VENDOR_NAME_LEN);
	sfp_data[XGBE_SFP_BASE_VENDOR_NAME_LEN] = '\0';
	netअगर_dbg(pdata, drv, pdata->netdev, "  vendor:         %s\n",
		  sfp_data);

	स_नकल(sfp_data, &sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_PN],
	       XGBE_SFP_BASE_VENDOR_PN_LEN);
	sfp_data[XGBE_SFP_BASE_VENDOR_PN_LEN] = '\0';
	netअगर_dbg(pdata, drv, pdata->netdev, "  part number:    %s\n",
		  sfp_data);

	स_नकल(sfp_data, &sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_REV],
	       XGBE_SFP_BASE_VENDOR_REV_LEN);
	sfp_data[XGBE_SFP_BASE_VENDOR_REV_LEN] = '\0';
	netअगर_dbg(pdata, drv, pdata->netdev, "  revision level: %s\n",
		  sfp_data);

	स_नकल(sfp_data, &sfp_eeprom->extd[XGBE_SFP_BASE_VENDOR_SN],
	       XGBE_SFP_BASE_VENDOR_SN_LEN);
	sfp_data[XGBE_SFP_BASE_VENDOR_SN_LEN] = '\0';
	netअगर_dbg(pdata, drv, pdata->netdev, "  serial number:  %s\n",
		  sfp_data);
पूर्ण

अटल bool xgbe_phy_sfp_verअगरy_eeprom(u8 cc_in, u8 *buf, अचिन्हित पूर्णांक len)
अणु
	u8 cc;

	क्रम (cc = 0; len; buf++, len--)
		cc += *buf;

	वापस cc == cc_in;
पूर्ण

अटल पूर्णांक xgbe_phy_sfp_पढ़ो_eeprom(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	काष्ठा xgbe_sfp_eeprom sfp_eeprom;
	u8 eeprom_addr;
	पूर्णांक ret;

	ret = xgbe_phy_sfp_get_mux(pdata);
	अगर (ret) अणु
		dev_err_once(pdata->dev, "%s: I2C error setting SFP MUX\n",
			     netdev_name(pdata->netdev));
		वापस ret;
	पूर्ण

	/* Read the SFP serial ID eeprom */
	eeprom_addr = 0;
	ret = xgbe_phy_i2c_पढ़ो(pdata, XGBE_SFP_SERIAL_ID_ADDRESS,
				&eeprom_addr, माप(eeprom_addr),
				&sfp_eeprom, माप(sfp_eeprom));
	अगर (ret) अणु
		dev_err_once(pdata->dev, "%s: I2C error reading SFP EEPROM\n",
			     netdev_name(pdata->netdev));
		जाओ put;
	पूर्ण

	/* Validate the contents पढ़ो */
	अगर (!xgbe_phy_sfp_verअगरy_eeprom(sfp_eeprom.base[XGBE_SFP_BASE_CC],
					sfp_eeprom.base,
					माप(sfp_eeprom.base) - 1)) अणु
		ret = -EINVAL;
		जाओ put;
	पूर्ण

	अगर (!xgbe_phy_sfp_verअगरy_eeprom(sfp_eeprom.extd[XGBE_SFP_EXTD_CC],
					sfp_eeprom.extd,
					माप(sfp_eeprom.extd) - 1)) अणु
		ret = -EINVAL;
		जाओ put;
	पूर्ण

	/* Check क्रम an added or changed SFP */
	अगर (स_भेद(&phy_data->sfp_eeprom, &sfp_eeprom, माप(sfp_eeprom))) अणु
		phy_data->sfp_changed = 1;

		अगर (netअगर_msg_drv(pdata))
			xgbe_phy_sfp_eeprom_info(pdata, &sfp_eeprom);

		स_नकल(&phy_data->sfp_eeprom, &sfp_eeprom, माप(sfp_eeprom));

		xgbe_phy_मुक्त_phy_device(pdata);
	पूर्ण अन्यथा अणु
		phy_data->sfp_changed = 0;
	पूर्ण

put:
	xgbe_phy_sfp_put_mux(pdata);

	वापस ret;
पूर्ण

अटल व्योम xgbe_phy_sfp_संकेतs(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	u8 gpio_reg, gpio_ports[2];
	पूर्णांक ret;

	/* Read the input port रेजिस्टरs */
	gpio_reg = 0;
	ret = xgbe_phy_i2c_पढ़ो(pdata, phy_data->sfp_gpio_address,
				&gpio_reg, माप(gpio_reg),
				gpio_ports, माप(gpio_ports));
	अगर (ret) अणु
		dev_err_once(pdata->dev, "%s: I2C error reading SFP GPIOs\n",
			     netdev_name(pdata->netdev));
		वापस;
	पूर्ण

	phy_data->sfp_gpio_inमाला_दो = (gpio_ports[1] << 8) | gpio_ports[0];

	phy_data->sfp_mod_असलent = xgbe_phy_check_sfp_mod_असलent(phy_data);
पूर्ण

अटल व्योम xgbe_phy_sfp_mod_असलent(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_मुक्त_phy_device(pdata);

	phy_data->sfp_mod_असलent = 1;
	phy_data->sfp_phy_avail = 0;
	स_रखो(&phy_data->sfp_eeprom, 0, माप(phy_data->sfp_eeprom));
पूर्ण

अटल व्योम xgbe_phy_sfp_reset(काष्ठा xgbe_phy_data *phy_data)
अणु
	phy_data->sfp_rx_los = 0;
	phy_data->sfp_tx_fault = 0;
	phy_data->sfp_mod_असलent = 1;
	phy_data->sfp_base = XGBE_SFP_BASE_UNKNOWN;
	phy_data->sfp_cable = XGBE_SFP_CABLE_UNKNOWN;
	phy_data->sfp_speed = XGBE_SFP_SPEED_UNKNOWN;
पूर्ण

अटल व्योम xgbe_phy_sfp_detect(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	पूर्णांक ret;

	/* Reset the SFP संकेतs and info */
	xgbe_phy_sfp_reset(phy_data);

	ret = xgbe_phy_get_comm_ownership(pdata);
	अगर (ret)
		वापस;

	/* Read the SFP संकेतs and check क्रम module presence */
	xgbe_phy_sfp_संकेतs(pdata);
	अगर (phy_data->sfp_mod_असलent) अणु
		xgbe_phy_sfp_mod_असलent(pdata);
		जाओ put;
	पूर्ण

	ret = xgbe_phy_sfp_पढ़ो_eeprom(pdata);
	अगर (ret) अणु
		/* Treat any error as अगर there isn't an SFP plugged in */
		xgbe_phy_sfp_reset(phy_data);
		xgbe_phy_sfp_mod_असलent(pdata);
		जाओ put;
	पूर्ण

	xgbe_phy_sfp_parse_eeprom(pdata);

	xgbe_phy_sfp_बाह्यal_phy(pdata);

put:
	xgbe_phy_sfp_phy_settings(pdata);

	xgbe_phy_put_comm_ownership(pdata);
पूर्ण

अटल पूर्णांक xgbe_phy_module_eeprom(काष्ठा xgbe_prv_data *pdata,
				  काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	u8 eeprom_addr, eeprom_data[XGBE_SFP_EEPROM_MAX];
	काष्ठा xgbe_sfp_eeprom *sfp_eeprom;
	अचिन्हित पूर्णांक i, j, rem;
	पूर्णांक ret;

	rem = eeprom->len;

	अगर (!eeprom->len) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर ((eeprom->offset + eeprom->len) > XGBE_SFP_EEPROM_MAX) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (phy_data->port_mode != XGBE_PORT_MODE_SFP) अणु
		ret = -ENXIO;
		जाओ करोne;
	पूर्ण

	अगर (!netअगर_running(pdata->netdev)) अणु
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (phy_data->sfp_mod_असलent) अणु
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	ret = xgbe_phy_get_comm_ownership(pdata);
	अगर (ret) अणु
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	ret = xgbe_phy_sfp_get_mux(pdata);
	अगर (ret) अणु
		netdev_err(pdata->netdev, "I2C error setting SFP MUX\n");
		ret = -EIO;
		जाओ put_own;
	पूर्ण

	/* Read the SFP serial ID eeprom */
	eeprom_addr = 0;
	ret = xgbe_phy_i2c_पढ़ो(pdata, XGBE_SFP_SERIAL_ID_ADDRESS,
				&eeprom_addr, माप(eeprom_addr),
				eeprom_data, XGBE_SFP_EEPROM_BASE_LEN);
	अगर (ret) अणु
		netdev_err(pdata->netdev,
			   "I2C error reading SFP EEPROM\n");
		ret = -EIO;
		जाओ put_mux;
	पूर्ण

	sfp_eeprom = (काष्ठा xgbe_sfp_eeprom *)eeprom_data;

	अगर (XGBE_SFP_DIAGS_SUPPORTED(sfp_eeprom)) अणु
		/* Read the SFP diagnostic eeprom */
		eeprom_addr = 0;
		ret = xgbe_phy_i2c_पढ़ो(pdata, XGBE_SFP_DIAG_INFO_ADDRESS,
					&eeprom_addr, माप(eeprom_addr),
					eeprom_data + XGBE_SFP_EEPROM_BASE_LEN,
					XGBE_SFP_EEPROM_DIAG_LEN);
		अगर (ret) अणु
			netdev_err(pdata->netdev,
				   "I2C error reading SFP DIAGS\n");
			ret = -EIO;
			जाओ put_mux;
		पूर्ण
	पूर्ण

	क्रम (i = 0, j = eeprom->offset; i < eeprom->len; i++, j++) अणु
		अगर ((j >= XGBE_SFP_EEPROM_BASE_LEN) &&
		    !XGBE_SFP_DIAGS_SUPPORTED(sfp_eeprom))
			अवरोध;

		data[i] = eeprom_data[j];
		rem--;
	पूर्ण

put_mux:
	xgbe_phy_sfp_put_mux(pdata);

put_own:
	xgbe_phy_put_comm_ownership(pdata);

करोne:
	eeprom->len -= rem;

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_module_info(काष्ठा xgbe_prv_data *pdata,
				काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	अगर (phy_data->port_mode != XGBE_PORT_MODE_SFP)
		वापस -ENXIO;

	अगर (!netअगर_running(pdata->netdev))
		वापस -EIO;

	अगर (phy_data->sfp_mod_असलent)
		वापस -EIO;

	अगर (XGBE_SFP_DIAGS_SUPPORTED(&phy_data->sfp_eeprom)) अणु
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
	पूर्ण अन्यथा अणु
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgbe_phy_phydev_flowctrl(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	u16 lcl_adv = 0, rmt_adv = 0;
	u8 fc;

	pdata->phy.tx_छोड़ो = 0;
	pdata->phy.rx_छोड़ो = 0;

	अगर (!phy_data->phydev)
		वापस;

	lcl_adv = linkmode_adv_to_lcl_adv_t(phy_data->phydev->advertising);

	अगर (phy_data->phydev->छोड़ो) अणु
		XGBE_SET_LP_ADV(lks, Pause);
		rmt_adv |= LPA_PAUSE_CAP;
	पूर्ण
	अगर (phy_data->phydev->asym_छोड़ो) अणु
		XGBE_SET_LP_ADV(lks, Asym_Pause);
		rmt_adv |= LPA_PAUSE_ASYM;
	पूर्ण

	fc = mii_resolve_flowctrl_fdx(lcl_adv, rmt_adv);
	अगर (fc & FLOW_CTRL_TX)
		pdata->phy.tx_छोड़ो = 1;
	अगर (fc & FLOW_CTRL_RX)
		pdata->phy.rx_छोड़ो = 1;
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_an37_sgmii_outcome(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	क्रमागत xgbe_mode mode;

	XGBE_SET_LP_ADV(lks, Autoneg);
	XGBE_SET_LP_ADV(lks, TP);

	/* Use बाह्यal PHY to determine flow control */
	अगर (pdata->phy.छोड़ो_स्वतःneg)
		xgbe_phy_phydev_flowctrl(pdata);

	चयन (pdata->an_status & XGBE_SGMII_AN_LINK_SPEED) अणु
	हाल XGBE_SGMII_AN_LINK_SPEED_100:
		अगर (pdata->an_status & XGBE_SGMII_AN_LINK_DUPLEX) अणु
			XGBE_SET_LP_ADV(lks, 100baseT_Full);
			mode = XGBE_MODE_SGMII_100;
		पूर्ण अन्यथा अणु
			/* Half-duplex not supported */
			XGBE_SET_LP_ADV(lks, 100baseT_Half);
			mode = XGBE_MODE_UNKNOWN;
		पूर्ण
		अवरोध;
	हाल XGBE_SGMII_AN_LINK_SPEED_1000:
		अगर (pdata->an_status & XGBE_SGMII_AN_LINK_DUPLEX) अणु
			XGBE_SET_LP_ADV(lks, 1000baseT_Full);
			mode = XGBE_MODE_SGMII_1000;
		पूर्ण अन्यथा अणु
			/* Half-duplex not supported */
			XGBE_SET_LP_ADV(lks, 1000baseT_Half);
			mode = XGBE_MODE_UNKNOWN;
		पूर्ण
		अवरोध;
	शेष:
		mode = XGBE_MODE_UNKNOWN;
	पूर्ण

	वापस mode;
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_an37_outcome(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	क्रमागत xgbe_mode mode;
	अचिन्हित पूर्णांक ad_reg, lp_reg;

	XGBE_SET_LP_ADV(lks, Autoneg);
	XGBE_SET_LP_ADV(lks, FIBRE);

	/* Compare Advertisement and Link Partner रेजिस्टर */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_ADVERTISE);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_LP_ABILITY);
	अगर (lp_reg & 0x100)
		XGBE_SET_LP_ADV(lks, Pause);
	अगर (lp_reg & 0x80)
		XGBE_SET_LP_ADV(lks, Asym_Pause);

	अगर (pdata->phy.छोड़ो_स्वतःneg) अणु
		/* Set flow control based on स्वतः-negotiation result */
		pdata->phy.tx_छोड़ो = 0;
		pdata->phy.rx_छोड़ो = 0;

		अगर (ad_reg & lp_reg & 0x100) अणु
			pdata->phy.tx_छोड़ो = 1;
			pdata->phy.rx_छोड़ो = 1;
		पूर्ण अन्यथा अगर (ad_reg & lp_reg & 0x80) अणु
			अगर (ad_reg & 0x100)
				pdata->phy.rx_छोड़ो = 1;
			अन्यथा अगर (lp_reg & 0x100)
				pdata->phy.tx_छोड़ो = 1;
		पूर्ण
	पूर्ण

	अगर (lp_reg & 0x20)
		XGBE_SET_LP_ADV(lks, 1000baseX_Full);

	/* Half duplex is not supported */
	ad_reg &= lp_reg;
	mode = (ad_reg & 0x20) ? XGBE_MODE_X : XGBE_MODE_UNKNOWN;

	वापस mode;
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_an73_redrv_outcome(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	क्रमागत xgbe_mode mode;
	अचिन्हित पूर्णांक ad_reg, lp_reg;

	XGBE_SET_LP_ADV(lks, Autoneg);
	XGBE_SET_LP_ADV(lks, Backplane);

	/* Use बाह्यal PHY to determine flow control */
	अगर (pdata->phy.छोड़ो_स्वतःneg)
		xgbe_phy_phydev_flowctrl(pdata);

	/* Compare Advertisement and Link Partner रेजिस्टर 2 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 1);
	अगर (lp_reg & 0x80)
		XGBE_SET_LP_ADV(lks, 10000baseKR_Full);
	अगर (lp_reg & 0x20)
		XGBE_SET_LP_ADV(lks, 1000baseKX_Full);

	ad_reg &= lp_reg;
	अगर (ad_reg & 0x80) अणु
		चयन (phy_data->port_mode) अणु
		हाल XGBE_PORT_MODE_BACKPLANE:
		हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
			mode = XGBE_MODE_KR;
			अवरोध;
		शेष:
			mode = XGBE_MODE_SFI;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (ad_reg & 0x20) अणु
		चयन (phy_data->port_mode) अणु
		हाल XGBE_PORT_MODE_BACKPLANE:
		हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
			mode = XGBE_MODE_KX_1000;
			अवरोध;
		हाल XGBE_PORT_MODE_1000BASE_X:
			mode = XGBE_MODE_X;
			अवरोध;
		हाल XGBE_PORT_MODE_SFP:
			चयन (phy_data->sfp_base) अणु
			हाल XGBE_SFP_BASE_1000_T:
				अगर (phy_data->phydev &&
				    (phy_data->phydev->speed == SPEED_100))
					mode = XGBE_MODE_SGMII_100;
				अन्यथा
					mode = XGBE_MODE_SGMII_1000;
				अवरोध;
			हाल XGBE_SFP_BASE_1000_SX:
			हाल XGBE_SFP_BASE_1000_LX:
			हाल XGBE_SFP_BASE_1000_CX:
			शेष:
				mode = XGBE_MODE_X;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अगर (phy_data->phydev &&
			    (phy_data->phydev->speed == SPEED_100))
				mode = XGBE_MODE_SGMII_100;
			अन्यथा
				mode = XGBE_MODE_SGMII_1000;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		mode = XGBE_MODE_UNKNOWN;
	पूर्ण

	/* Compare Advertisement and Link Partner रेजिस्टर 3 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 2);
	अगर (lp_reg & 0xc000)
		XGBE_SET_LP_ADV(lks, 10000baseR_FEC);

	वापस mode;
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_an73_outcome(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	क्रमागत xgbe_mode mode;
	अचिन्हित पूर्णांक ad_reg, lp_reg;

	XGBE_SET_LP_ADV(lks, Autoneg);
	XGBE_SET_LP_ADV(lks, Backplane);

	/* Compare Advertisement and Link Partner रेजिस्टर 1 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA);
	अगर (lp_reg & 0x400)
		XGBE_SET_LP_ADV(lks, Pause);
	अगर (lp_reg & 0x800)
		XGBE_SET_LP_ADV(lks, Asym_Pause);

	अगर (pdata->phy.छोड़ो_स्वतःneg) अणु
		/* Set flow control based on स्वतः-negotiation result */
		pdata->phy.tx_छोड़ो = 0;
		pdata->phy.rx_छोड़ो = 0;

		अगर (ad_reg & lp_reg & 0x400) अणु
			pdata->phy.tx_छोड़ो = 1;
			pdata->phy.rx_छोड़ो = 1;
		पूर्ण अन्यथा अगर (ad_reg & lp_reg & 0x800) अणु
			अगर (ad_reg & 0x400)
				pdata->phy.rx_छोड़ो = 1;
			अन्यथा अगर (lp_reg & 0x400)
				pdata->phy.tx_छोड़ो = 1;
		पूर्ण
	पूर्ण

	/* Compare Advertisement and Link Partner रेजिस्टर 2 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 1);
	अगर (lp_reg & 0x80)
		XGBE_SET_LP_ADV(lks, 10000baseKR_Full);
	अगर (lp_reg & 0x20)
		XGBE_SET_LP_ADV(lks, 1000baseKX_Full);

	ad_reg &= lp_reg;
	अगर (ad_reg & 0x80)
		mode = XGBE_MODE_KR;
	अन्यथा अगर (ad_reg & 0x20)
		mode = XGBE_MODE_KX_1000;
	अन्यथा
		mode = XGBE_MODE_UNKNOWN;

	/* Compare Advertisement and Link Partner रेजिस्टर 3 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 2);
	अगर (lp_reg & 0xc000)
		XGBE_SET_LP_ADV(lks, 10000baseR_FEC);

	वापस mode;
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_an_outcome(काष्ठा xgbe_prv_data *pdata)
अणु
	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL73:
		वापस xgbe_phy_an73_outcome(pdata);
	हाल XGBE_AN_MODE_CL73_REDRV:
		वापस xgbe_phy_an73_redrv_outcome(pdata);
	हाल XGBE_AN_MODE_CL37:
		वापस xgbe_phy_an37_outcome(pdata);
	हाल XGBE_AN_MODE_CL37_SGMII:
		वापस xgbe_phy_an37_sgmii_outcome(pdata);
	शेष:
		वापस XGBE_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_an_advertising(काष्ठा xgbe_prv_data *pdata,
				    काष्ठा ethtool_link_ksettings *dlks)
अणु
	काष्ठा ethtool_link_ksettings *slks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	XGBE_LM_COPY(dlks, advertising, slks, advertising);

	/* Without a re-driver, just वापस current advertising */
	अगर (!phy_data->redrv)
		वापस;

	/* With the KR re-driver we need to advertise a single speed */
	XGBE_CLR_ADV(dlks, 1000baseKX_Full);
	XGBE_CLR_ADV(dlks, 10000baseKR_Full);

	/* Advertise FEC support is present */
	अगर (pdata->fec_ability & MDIO_PMA_10GBR_FECABLE_ABLE)
		XGBE_SET_ADV(dlks, 10000baseR_FEC);

	चयन (phy_data->port_mode) अणु
	हाल XGBE_PORT_MODE_BACKPLANE:
	हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
		XGBE_SET_ADV(dlks, 10000baseKR_Full);
		अवरोध;
	हाल XGBE_PORT_MODE_BACKPLANE_2500:
		XGBE_SET_ADV(dlks, 1000baseKX_Full);
		अवरोध;
	हाल XGBE_PORT_MODE_1000BASE_T:
	हाल XGBE_PORT_MODE_1000BASE_X:
	हाल XGBE_PORT_MODE_NBASE_T:
		XGBE_SET_ADV(dlks, 1000baseKX_Full);
		अवरोध;
	हाल XGBE_PORT_MODE_10GBASE_T:
		अगर (phy_data->phydev &&
		    (phy_data->phydev->speed == SPEED_10000))
			XGBE_SET_ADV(dlks, 10000baseKR_Full);
		अन्यथा
			XGBE_SET_ADV(dlks, 1000baseKX_Full);
		अवरोध;
	हाल XGBE_PORT_MODE_10GBASE_R:
		XGBE_SET_ADV(dlks, 10000baseKR_Full);
		अवरोध;
	हाल XGBE_PORT_MODE_SFP:
		चयन (phy_data->sfp_base) अणु
		हाल XGBE_SFP_BASE_1000_T:
		हाल XGBE_SFP_BASE_1000_SX:
		हाल XGBE_SFP_BASE_1000_LX:
		हाल XGBE_SFP_BASE_1000_CX:
			XGBE_SET_ADV(dlks, 1000baseKX_Full);
			अवरोध;
		शेष:
			XGBE_SET_ADV(dlks, 10000baseKR_Full);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		XGBE_SET_ADV(dlks, 10000baseKR_Full);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_phy_an_config(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	पूर्णांक ret;

	ret = xgbe_phy_find_phy_device(pdata);
	अगर (ret)
		वापस ret;

	अगर (!phy_data->phydev)
		वापस 0;

	phy_data->phydev->स्वतःneg = pdata->phy.स्वतःneg;
	linkmode_and(phy_data->phydev->advertising,
		     phy_data->phydev->supported,
		     lks->link_modes.advertising);

	अगर (pdata->phy.स्वतःneg != AUTONEG_ENABLE) अणु
		phy_data->phydev->speed = pdata->phy.speed;
		phy_data->phydev->duplex = pdata->phy.duplex;
	पूर्ण

	ret = phy_start_aneg(phy_data->phydev);

	वापस ret;
पूर्ण

अटल क्रमागत xgbe_an_mode xgbe_phy_an_sfp_mode(काष्ठा xgbe_phy_data *phy_data)
अणु
	चयन (phy_data->sfp_base) अणु
	हाल XGBE_SFP_BASE_1000_T:
		वापस XGBE_AN_MODE_CL37_SGMII;
	हाल XGBE_SFP_BASE_1000_SX:
	हाल XGBE_SFP_BASE_1000_LX:
	हाल XGBE_SFP_BASE_1000_CX:
		वापस XGBE_AN_MODE_CL37;
	शेष:
		वापस XGBE_AN_MODE_NONE;
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_an_mode xgbe_phy_an_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	/* A KR re-driver will always require CL73 AN */
	अगर (phy_data->redrv)
		वापस XGBE_AN_MODE_CL73_REDRV;

	चयन (phy_data->port_mode) अणु
	हाल XGBE_PORT_MODE_BACKPLANE:
		वापस XGBE_AN_MODE_CL73;
	हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
	हाल XGBE_PORT_MODE_BACKPLANE_2500:
		वापस XGBE_AN_MODE_NONE;
	हाल XGBE_PORT_MODE_1000BASE_T:
		वापस XGBE_AN_MODE_CL37_SGMII;
	हाल XGBE_PORT_MODE_1000BASE_X:
		वापस XGBE_AN_MODE_CL37;
	हाल XGBE_PORT_MODE_NBASE_T:
		वापस XGBE_AN_MODE_CL37_SGMII;
	हाल XGBE_PORT_MODE_10GBASE_T:
		वापस XGBE_AN_MODE_CL73;
	हाल XGBE_PORT_MODE_10GBASE_R:
		वापस XGBE_AN_MODE_NONE;
	हाल XGBE_PORT_MODE_SFP:
		वापस xgbe_phy_an_sfp_mode(phy_data);
	शेष:
		वापस XGBE_AN_MODE_NONE;
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_phy_set_redrv_mode_mdio(काष्ठा xgbe_prv_data *pdata,
					क्रमागत xgbe_phy_redrv_mode mode)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	u16 redrv_reg, redrv_val;

	redrv_reg = XGBE_PHY_REDRV_MODE_REG + (phy_data->redrv_lane * 0x1000);
	redrv_val = (u16)mode;

	वापस pdata->hw_अगर.ग_लिखो_ext_mii_regs(pdata, phy_data->redrv_addr,
					       redrv_reg, redrv_val);
पूर्ण

अटल पूर्णांक xgbe_phy_set_redrv_mode_i2c(काष्ठा xgbe_prv_data *pdata,
				       क्रमागत xgbe_phy_redrv_mode mode)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	अचिन्हित पूर्णांक redrv_reg;
	पूर्णांक ret;

	/* Calculate the रेजिस्टर to ग_लिखो */
	redrv_reg = XGBE_PHY_REDRV_MODE_REG + (phy_data->redrv_lane * 0x1000);

	ret = xgbe_phy_redrv_ग_लिखो(pdata, redrv_reg, mode);

	वापस ret;
पूर्ण

अटल व्योम xgbe_phy_set_redrv_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	क्रमागत xgbe_phy_redrv_mode mode;
	पूर्णांक ret;

	अगर (!phy_data->redrv)
		वापस;

	mode = XGBE_PHY_REDRV_MODE_CX;
	अगर ((phy_data->port_mode == XGBE_PORT_MODE_SFP) &&
	    (phy_data->sfp_base != XGBE_SFP_BASE_1000_CX) &&
	    (phy_data->sfp_base != XGBE_SFP_BASE_10000_CR))
		mode = XGBE_PHY_REDRV_MODE_SR;

	ret = xgbe_phy_get_comm_ownership(pdata);
	अगर (ret)
		वापस;

	अगर (phy_data->redrv_अगर)
		xgbe_phy_set_redrv_mode_i2c(pdata, mode);
	अन्यथा
		xgbe_phy_set_redrv_mode_mdio(pdata, mode);

	xgbe_phy_put_comm_ownership(pdata);
पूर्ण

अटल व्योम xgbe_phy_rx_reset(काष्ठा xgbe_prv_data *pdata)
अणु
	पूर्णांक reg;

	reg = XMDIO_READ_BITS(pdata, MDIO_MMD_PCS, MDIO_PCS_DIGITAL_STAT,
			      XGBE_PCS_PSEQ_STATE_MASK);
	अगर (reg == XGBE_PCS_PSEQ_STATE_POWER_GOOD) अणु
		/* Mailbox command समयd out, reset of RX block is required.
		 * This can be करोne by asseting the reset bit and रुको क्रम
		 * its compeletion.
		 */
		XMDIO_WRITE_BITS(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_RX_CTRL1,
				 XGBE_PMA_RX_RST_0_MASK, XGBE_PMA_RX_RST_0_RESET_ON);
		ndelay(20);
		XMDIO_WRITE_BITS(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_RX_CTRL1,
				 XGBE_PMA_RX_RST_0_MASK, XGBE_PMA_RX_RST_0_RESET_OFF);
		usleep_range(40, 50);
		netअगर_err(pdata, link, pdata->netdev, "firmware mailbox reset performed\n");
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_perक्रमm_ratechange(काष्ठा xgbe_prv_data *pdata,
					अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक sub_cmd)
अणु
	अचिन्हित पूर्णांक s0 = 0;
	अचिन्हित पूर्णांक रुको;

	/* Log अगर a previous command did not complete */
	अगर (XP_IOREAD_BITS(pdata, XP_DRIVER_INT_RO, STATUS)) अणु
		netअगर_dbg(pdata, link, pdata->netdev,
			  "firmware mailbox not ready for command\n");
		xgbe_phy_rx_reset(pdata);
	पूर्ण

	/* Conकाष्ठा the command */
	XP_SET_BITS(s0, XP_DRIVER_SCRATCH_0, COMMAND, cmd);
	XP_SET_BITS(s0, XP_DRIVER_SCRATCH_0, SUB_COMMAND, sub_cmd);

	/* Issue the command */
	XP_IOWRITE(pdata, XP_DRIVER_SCRATCH_0, s0);
	XP_IOWRITE(pdata, XP_DRIVER_SCRATCH_1, 0);
	XP_IOWRITE_BITS(pdata, XP_DRIVER_INT_REQ, REQUEST, 1);

	/* Wait क्रम command to complete */
	रुको = XGBE_RATECHANGE_COUNT;
	जबतक (रुको--) अणु
		अगर (!XP_IOREAD_BITS(pdata, XP_DRIVER_INT_RO, STATUS))
			वापस;

		usleep_range(1000, 2000);
	पूर्ण

	netअगर_dbg(pdata, link, pdata->netdev,
		  "firmware mailbox command did not complete\n");

	/* Reset on error */
	xgbe_phy_rx_reset(pdata);
पूर्ण

अटल व्योम xgbe_phy_rrc(काष्ठा xgbe_prv_data *pdata)
अणु
	/* Receiver Reset Cycle */
	xgbe_phy_perक्रमm_ratechange(pdata, 5, 0);

	netअगर_dbg(pdata, link, pdata->netdev, "receiver reset complete\n");
पूर्ण

अटल व्योम xgbe_phy_घातer_off(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	/* Power off */
	xgbe_phy_perक्रमm_ratechange(pdata, 0, 0);

	phy_data->cur_mode = XGBE_MODE_UNKNOWN;

	netअगर_dbg(pdata, link, pdata->netdev, "phy powered off\n");
पूर्ण

अटल व्योम xgbe_phy_sfi_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_set_redrv_mode(pdata);

	/* 10G/SFI */
	अगर (phy_data->sfp_cable != XGBE_SFP_CABLE_PASSIVE) अणु
		xgbe_phy_perक्रमm_ratechange(pdata, 3, 0);
	पूर्ण अन्यथा अणु
		अगर (phy_data->sfp_cable_len <= 1)
			xgbe_phy_perक्रमm_ratechange(pdata, 3, 1);
		अन्यथा अगर (phy_data->sfp_cable_len <= 3)
			xgbe_phy_perक्रमm_ratechange(pdata, 3, 2);
		अन्यथा
			xgbe_phy_perक्रमm_ratechange(pdata, 3, 3);
	पूर्ण

	phy_data->cur_mode = XGBE_MODE_SFI;

	netअगर_dbg(pdata, link, pdata->netdev, "10GbE SFI mode set\n");
पूर्ण

अटल व्योम xgbe_phy_x_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_set_redrv_mode(pdata);

	/* 1G/X */
	xgbe_phy_perक्रमm_ratechange(pdata, 1, 3);

	phy_data->cur_mode = XGBE_MODE_X;

	netअगर_dbg(pdata, link, pdata->netdev, "1GbE X mode set\n");
पूर्ण

अटल व्योम xgbe_phy_sgmii_1000_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_set_redrv_mode(pdata);

	/* 1G/SGMII */
	xgbe_phy_perक्रमm_ratechange(pdata, 1, 2);

	phy_data->cur_mode = XGBE_MODE_SGMII_1000;

	netअगर_dbg(pdata, link, pdata->netdev, "1GbE SGMII mode set\n");
पूर्ण

अटल व्योम xgbe_phy_sgmii_100_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_set_redrv_mode(pdata);

	/* 100M/SGMII */
	xgbe_phy_perक्रमm_ratechange(pdata, 1, 1);

	phy_data->cur_mode = XGBE_MODE_SGMII_100;

	netअगर_dbg(pdata, link, pdata->netdev, "100MbE SGMII mode set\n");
पूर्ण

अटल व्योम xgbe_phy_kr_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_set_redrv_mode(pdata);

	/* 10G/KR */
	xgbe_phy_perक्रमm_ratechange(pdata, 4, 0);

	phy_data->cur_mode = XGBE_MODE_KR;

	netअगर_dbg(pdata, link, pdata->netdev, "10GbE KR mode set\n");
पूर्ण

अटल व्योम xgbe_phy_kx_2500_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_set_redrv_mode(pdata);

	/* 2.5G/KX */
	xgbe_phy_perक्रमm_ratechange(pdata, 2, 0);

	phy_data->cur_mode = XGBE_MODE_KX_2500;

	netअगर_dbg(pdata, link, pdata->netdev, "2.5GbE KX mode set\n");
पूर्ण

अटल व्योम xgbe_phy_kx_1000_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	xgbe_phy_set_redrv_mode(pdata);

	/* 1G/KX */
	xgbe_phy_perक्रमm_ratechange(pdata, 1, 3);

	phy_data->cur_mode = XGBE_MODE_KX_1000;

	netअगर_dbg(pdata, link, pdata->netdev, "1GbE KX mode set\n");
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_cur_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	वापस phy_data->cur_mode;
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_चयन_baset_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	/* No चयनing अगर not 10GBase-T */
	अगर (phy_data->port_mode != XGBE_PORT_MODE_10GBASE_T)
		वापस xgbe_phy_cur_mode(pdata);

	चयन (xgbe_phy_cur_mode(pdata)) अणु
	हाल XGBE_MODE_SGMII_100:
	हाल XGBE_MODE_SGMII_1000:
		वापस XGBE_MODE_KR;
	हाल XGBE_MODE_KR:
	शेष:
		वापस XGBE_MODE_SGMII_1000;
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_चयन_bp_2500_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	वापस XGBE_MODE_KX_2500;
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_चयन_bp_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	/* If we are in KR चयन to KX, and vice-versa */
	चयन (xgbe_phy_cur_mode(pdata)) अणु
	हाल XGBE_MODE_KX_1000:
		वापस XGBE_MODE_KR;
	हाल XGBE_MODE_KR:
	शेष:
		वापस XGBE_MODE_KX_1000;
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_चयन_mode(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (phy_data->port_mode) अणु
	हाल XGBE_PORT_MODE_BACKPLANE:
	हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
		वापस xgbe_phy_चयन_bp_mode(pdata);
	हाल XGBE_PORT_MODE_BACKPLANE_2500:
		वापस xgbe_phy_चयन_bp_2500_mode(pdata);
	हाल XGBE_PORT_MODE_1000BASE_T:
	हाल XGBE_PORT_MODE_NBASE_T:
	हाल XGBE_PORT_MODE_10GBASE_T:
		वापस xgbe_phy_चयन_baset_mode(pdata);
	हाल XGBE_PORT_MODE_1000BASE_X:
	हाल XGBE_PORT_MODE_10GBASE_R:
	हाल XGBE_PORT_MODE_SFP:
		/* No चयनing, so just वापस current mode */
		वापस xgbe_phy_cur_mode(pdata);
	शेष:
		वापस XGBE_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_get_basex_mode(काष्ठा xgbe_phy_data *phy_data,
					      पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_1000:
		वापस XGBE_MODE_X;
	हाल SPEED_10000:
		वापस XGBE_MODE_KR;
	शेष:
		वापस XGBE_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_get_baset_mode(काष्ठा xgbe_phy_data *phy_data,
					      पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_100:
		वापस XGBE_MODE_SGMII_100;
	हाल SPEED_1000:
		वापस XGBE_MODE_SGMII_1000;
	हाल SPEED_2500:
		वापस XGBE_MODE_KX_2500;
	हाल SPEED_10000:
		वापस XGBE_MODE_KR;
	शेष:
		वापस XGBE_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_get_sfp_mode(काष्ठा xgbe_phy_data *phy_data,
					    पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_100:
		वापस XGBE_MODE_SGMII_100;
	हाल SPEED_1000:
		अगर (phy_data->sfp_base == XGBE_SFP_BASE_1000_T)
			वापस XGBE_MODE_SGMII_1000;
		अन्यथा
			वापस XGBE_MODE_X;
	हाल SPEED_10000:
	हाल SPEED_UNKNOWN:
		वापस XGBE_MODE_SFI;
	शेष:
		वापस XGBE_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_get_bp_2500_mode(पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_2500:
		वापस XGBE_MODE_KX_2500;
	शेष:
		वापस XGBE_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_get_bp_mode(पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_1000:
		वापस XGBE_MODE_KX_1000;
	हाल SPEED_10000:
		वापस XGBE_MODE_KR;
	शेष:
		वापस XGBE_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल क्रमागत xgbe_mode xgbe_phy_get_mode(काष्ठा xgbe_prv_data *pdata,
					पूर्णांक speed)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (phy_data->port_mode) अणु
	हाल XGBE_PORT_MODE_BACKPLANE:
	हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
		वापस xgbe_phy_get_bp_mode(speed);
	हाल XGBE_PORT_MODE_BACKPLANE_2500:
		वापस xgbe_phy_get_bp_2500_mode(speed);
	हाल XGBE_PORT_MODE_1000BASE_T:
	हाल XGBE_PORT_MODE_NBASE_T:
	हाल XGBE_PORT_MODE_10GBASE_T:
		वापस xgbe_phy_get_baset_mode(phy_data, speed);
	हाल XGBE_PORT_MODE_1000BASE_X:
	हाल XGBE_PORT_MODE_10GBASE_R:
		वापस xgbe_phy_get_basex_mode(phy_data, speed);
	हाल XGBE_PORT_MODE_SFP:
		वापस xgbe_phy_get_sfp_mode(phy_data, speed);
	शेष:
		वापस XGBE_MODE_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_set_mode(काष्ठा xgbe_prv_data *pdata, क्रमागत xgbe_mode mode)
अणु
	चयन (mode) अणु
	हाल XGBE_MODE_KX_1000:
		xgbe_phy_kx_1000_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_KX_2500:
		xgbe_phy_kx_2500_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_KR:
		xgbe_phy_kr_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_SGMII_100:
		xgbe_phy_sgmii_100_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_SGMII_1000:
		xgbe_phy_sgmii_1000_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_X:
		xgbe_phy_x_mode(pdata);
		अवरोध;
	हाल XGBE_MODE_SFI:
		xgbe_phy_sfi_mode(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_check_mode(काष्ठा xgbe_prv_data *pdata,
				क्रमागत xgbe_mode mode, bool advert)
अणु
	अगर (pdata->phy.स्वतःneg == AUTONEG_ENABLE) अणु
		वापस advert;
	पूर्ण अन्यथा अणु
		क्रमागत xgbe_mode cur_mode;

		cur_mode = xgbe_phy_get_mode(pdata, pdata->phy.speed);
		अगर (cur_mode == mode)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool xgbe_phy_use_basex_mode(काष्ठा xgbe_prv_data *pdata,
				    क्रमागत xgbe_mode mode)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;

	चयन (mode) अणु
	हाल XGBE_MODE_X:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 1000baseX_Full));
	हाल XGBE_MODE_KR:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 10000baseKR_Full));
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_use_baset_mode(काष्ठा xgbe_prv_data *pdata,
				    क्रमागत xgbe_mode mode)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;

	चयन (mode) अणु
	हाल XGBE_MODE_SGMII_100:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 100baseT_Full));
	हाल XGBE_MODE_SGMII_1000:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 1000baseT_Full));
	हाल XGBE_MODE_KX_2500:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 2500baseT_Full));
	हाल XGBE_MODE_KR:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 10000baseT_Full));
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_use_sfp_mode(काष्ठा xgbe_prv_data *pdata,
				  क्रमागत xgbe_mode mode)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (mode) अणु
	हाल XGBE_MODE_X:
		अगर (phy_data->sfp_base == XGBE_SFP_BASE_1000_T)
			वापस false;
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 1000baseX_Full));
	हाल XGBE_MODE_SGMII_100:
		अगर (phy_data->sfp_base != XGBE_SFP_BASE_1000_T)
			वापस false;
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 100baseT_Full));
	हाल XGBE_MODE_SGMII_1000:
		अगर (phy_data->sfp_base != XGBE_SFP_BASE_1000_T)
			वापस false;
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 1000baseT_Full));
	हाल XGBE_MODE_SFI:
		अगर (phy_data->sfp_mod_असलent)
			वापस true;
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 10000baseSR_Full)  ||
					   XGBE_ADV(lks, 10000baseLR_Full)  ||
					   XGBE_ADV(lks, 10000baseLRM_Full) ||
					   XGBE_ADV(lks, 10000baseER_Full)  ||
					   XGBE_ADV(lks, 10000baseCR_Full));
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_use_bp_2500_mode(काष्ठा xgbe_prv_data *pdata,
				      क्रमागत xgbe_mode mode)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;

	चयन (mode) अणु
	हाल XGBE_MODE_KX_2500:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 2500baseX_Full));
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_use_bp_mode(काष्ठा xgbe_prv_data *pdata,
				 क्रमागत xgbe_mode mode)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;

	चयन (mode) अणु
	हाल XGBE_MODE_KX_1000:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 1000baseKX_Full));
	हाल XGBE_MODE_KR:
		वापस xgbe_phy_check_mode(pdata, mode,
					   XGBE_ADV(lks, 10000baseKR_Full));
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_use_mode(काष्ठा xgbe_prv_data *pdata, क्रमागत xgbe_mode mode)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (phy_data->port_mode) अणु
	हाल XGBE_PORT_MODE_BACKPLANE:
	हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
		वापस xgbe_phy_use_bp_mode(pdata, mode);
	हाल XGBE_PORT_MODE_BACKPLANE_2500:
		वापस xgbe_phy_use_bp_2500_mode(pdata, mode);
	हाल XGBE_PORT_MODE_1000BASE_T:
	हाल XGBE_PORT_MODE_NBASE_T:
	हाल XGBE_PORT_MODE_10GBASE_T:
		वापस xgbe_phy_use_baset_mode(pdata, mode);
	हाल XGBE_PORT_MODE_1000BASE_X:
	हाल XGBE_PORT_MODE_10GBASE_R:
		वापस xgbe_phy_use_basex_mode(pdata, mode);
	हाल XGBE_PORT_MODE_SFP:
		वापस xgbe_phy_use_sfp_mode(pdata, mode);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_valid_speed_basex_mode(काष्ठा xgbe_phy_data *phy_data,
					    पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_1000:
		वापस (phy_data->port_mode == XGBE_PORT_MODE_1000BASE_X);
	हाल SPEED_10000:
		वापस (phy_data->port_mode == XGBE_PORT_MODE_10GBASE_R);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_valid_speed_baset_mode(काष्ठा xgbe_phy_data *phy_data,
					    पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_100:
	हाल SPEED_1000:
		वापस true;
	हाल SPEED_2500:
		वापस (phy_data->port_mode == XGBE_PORT_MODE_NBASE_T);
	हाल SPEED_10000:
		वापस (phy_data->port_mode == XGBE_PORT_MODE_10GBASE_T);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_valid_speed_sfp_mode(काष्ठा xgbe_phy_data *phy_data,
					  पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_100:
		वापस (phy_data->sfp_speed == XGBE_SFP_SPEED_100_1000);
	हाल SPEED_1000:
		वापस ((phy_data->sfp_speed == XGBE_SFP_SPEED_100_1000) ||
			(phy_data->sfp_speed == XGBE_SFP_SPEED_1000));
	हाल SPEED_10000:
		वापस (phy_data->sfp_speed == XGBE_SFP_SPEED_10000);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_valid_speed_bp_2500_mode(पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_2500:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_valid_speed_bp_mode(पूर्णांक speed)
अणु
	चयन (speed) अणु
	हाल SPEED_1000:
	हाल SPEED_10000:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool xgbe_phy_valid_speed(काष्ठा xgbe_prv_data *pdata, पूर्णांक speed)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (phy_data->port_mode) अणु
	हाल XGBE_PORT_MODE_BACKPLANE:
	हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
		वापस xgbe_phy_valid_speed_bp_mode(speed);
	हाल XGBE_PORT_MODE_BACKPLANE_2500:
		वापस xgbe_phy_valid_speed_bp_2500_mode(speed);
	हाल XGBE_PORT_MODE_1000BASE_T:
	हाल XGBE_PORT_MODE_NBASE_T:
	हाल XGBE_PORT_MODE_10GBASE_T:
		वापस xgbe_phy_valid_speed_baset_mode(phy_data, speed);
	हाल XGBE_PORT_MODE_1000BASE_X:
	हाल XGBE_PORT_MODE_10GBASE_R:
		वापस xgbe_phy_valid_speed_basex_mode(phy_data, speed);
	हाल XGBE_PORT_MODE_SFP:
		वापस xgbe_phy_valid_speed_sfp_mode(phy_data, speed);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक xgbe_phy_link_status(काष्ठा xgbe_prv_data *pdata, पूर्णांक *an_restart)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	*an_restart = 0;

	अगर (phy_data->port_mode == XGBE_PORT_MODE_SFP) अणु
		/* Check SFP संकेतs */
		xgbe_phy_sfp_detect(pdata);

		अगर (phy_data->sfp_changed) अणु
			*an_restart = 1;
			वापस 0;
		पूर्ण

		अगर (phy_data->sfp_mod_असलent || phy_data->sfp_rx_los)
			वापस 0;
	पूर्ण

	अगर (phy_data->phydev) अणु
		/* Check बाह्यal PHY */
		ret = phy_पढ़ो_status(phy_data->phydev);
		अगर (ret < 0)
			वापस 0;

		अगर ((pdata->phy.स्वतःneg == AUTONEG_ENABLE) &&
		    !phy_aneg_करोne(phy_data->phydev))
			वापस 0;

		अगर (!phy_data->phydev->link)
			वापस 0;
	पूर्ण

	/* Link status is latched low, so पढ़ो once to clear
	 * and then पढ़ो again to get current state
	 */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);
	अगर (reg & MDIO_STAT1_LSTATUS)
		वापस 1;

	अगर (pdata->phy.स्वतःneg == AUTONEG_ENABLE &&
	    phy_data->port_mode == XGBE_PORT_MODE_BACKPLANE) अणु
		अगर (!test_bit(XGBE_LINK_INIT, &pdata->dev_state)) अणु
			netअगर_carrier_off(pdata->netdev);
			*an_restart = 1;
		पूर्ण
	पूर्ण

	/* No link, attempt a receiver reset cycle */
	अगर (phy_data->rrc_count++ > XGBE_RRC_FREQUENCY) अणु
		phy_data->rrc_count = 0;
		xgbe_phy_rrc(pdata);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgbe_phy_sfp_gpio_setup(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	phy_data->sfp_gpio_address = XGBE_GPIO_ADDRESS_PCA9555 +
				     XP_GET_BITS(pdata->pp3, XP_PROP_3,
						 GPIO_ADDR);

	phy_data->sfp_gpio_mask = XP_GET_BITS(pdata->pp3, XP_PROP_3,
					      GPIO_MASK);

	phy_data->sfp_gpio_rx_los = XP_GET_BITS(pdata->pp3, XP_PROP_3,
						GPIO_RX_LOS);
	phy_data->sfp_gpio_tx_fault = XP_GET_BITS(pdata->pp3, XP_PROP_3,
						  GPIO_TX_FAULT);
	phy_data->sfp_gpio_mod_असलent = XP_GET_BITS(pdata->pp3, XP_PROP_3,
						    GPIO_MOD_ABS);
	phy_data->sfp_gpio_rate_select = XP_GET_BITS(pdata->pp3, XP_PROP_3,
						     GPIO_RATE_SELECT);

	अगर (netअगर_msg_probe(pdata)) अणु
		dev_dbg(pdata->dev, "SFP: gpio_address=%#x\n",
			phy_data->sfp_gpio_address);
		dev_dbg(pdata->dev, "SFP: gpio_mask=%#x\n",
			phy_data->sfp_gpio_mask);
		dev_dbg(pdata->dev, "SFP: gpio_rx_los=%u\n",
			phy_data->sfp_gpio_rx_los);
		dev_dbg(pdata->dev, "SFP: gpio_tx_fault=%u\n",
			phy_data->sfp_gpio_tx_fault);
		dev_dbg(pdata->dev, "SFP: gpio_mod_absent=%u\n",
			phy_data->sfp_gpio_mod_असलent);
		dev_dbg(pdata->dev, "SFP: gpio_rate_select=%u\n",
			phy_data->sfp_gpio_rate_select);
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_sfp_comm_setup(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	अचिन्हित पूर्णांक mux_addr_hi, mux_addr_lo;

	mux_addr_hi = XP_GET_BITS(pdata->pp4, XP_PROP_4, MUX_ADDR_HI);
	mux_addr_lo = XP_GET_BITS(pdata->pp4, XP_PROP_4, MUX_ADDR_LO);
	अगर (mux_addr_lo == XGBE_SFP_सूचीECT)
		वापस;

	phy_data->sfp_comm = XGBE_SFP_COMM_PCA9545;
	phy_data->sfp_mux_address = (mux_addr_hi << 2) + mux_addr_lo;
	phy_data->sfp_mux_channel = XP_GET_BITS(pdata->pp4, XP_PROP_4,
						MUX_CHAN);

	अगर (netअगर_msg_probe(pdata)) अणु
		dev_dbg(pdata->dev, "SFP: mux_address=%#x\n",
			phy_data->sfp_mux_address);
		dev_dbg(pdata->dev, "SFP: mux_channel=%u\n",
			phy_data->sfp_mux_channel);
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_sfp_setup(काष्ठा xgbe_prv_data *pdata)
अणु
	xgbe_phy_sfp_comm_setup(pdata);
	xgbe_phy_sfp_gpio_setup(pdata);
पूर्ण

अटल पूर्णांक xgbe_phy_पूर्णांक_mdio_reset(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	अचिन्हित पूर्णांक ret;

	ret = pdata->hw_अगर.set_gpio(pdata, phy_data->mdio_reset_gpio);
	अगर (ret)
		वापस ret;

	ret = pdata->hw_अगर.clr_gpio(pdata, phy_data->mdio_reset_gpio);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_i2c_mdio_reset(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	u8 gpio_reg, gpio_ports[2], gpio_data[3];
	पूर्णांक ret;

	/* Read the output port रेजिस्टरs */
	gpio_reg = 2;
	ret = xgbe_phy_i2c_पढ़ो(pdata, phy_data->mdio_reset_addr,
				&gpio_reg, माप(gpio_reg),
				gpio_ports, माप(gpio_ports));
	अगर (ret)
		वापस ret;

	/* Prepare to ग_लिखो the GPIO data */
	gpio_data[0] = 2;
	gpio_data[1] = gpio_ports[0];
	gpio_data[2] = gpio_ports[1];

	/* Set the GPIO pin */
	अगर (phy_data->mdio_reset_gpio < 8)
		gpio_data[1] |= (1 << (phy_data->mdio_reset_gpio % 8));
	अन्यथा
		gpio_data[2] |= (1 << (phy_data->mdio_reset_gpio % 8));

	/* Write the output port रेजिस्टरs */
	ret = xgbe_phy_i2c_ग_लिखो(pdata, phy_data->mdio_reset_addr,
				 gpio_data, माप(gpio_data));
	अगर (ret)
		वापस ret;

	/* Clear the GPIO pin */
	अगर (phy_data->mdio_reset_gpio < 8)
		gpio_data[1] &= ~(1 << (phy_data->mdio_reset_gpio % 8));
	अन्यथा
		gpio_data[2] &= ~(1 << (phy_data->mdio_reset_gpio % 8));

	/* Write the output port रेजिस्टरs */
	ret = xgbe_phy_i2c_ग_लिखो(pdata, phy_data->mdio_reset_addr,
				 gpio_data, माप(gpio_data));

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_mdio_reset(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	पूर्णांक ret;

	अगर (phy_data->conn_type != XGBE_CONN_TYPE_MDIO)
		वापस 0;

	ret = xgbe_phy_get_comm_ownership(pdata);
	अगर (ret)
		वापस ret;

	अगर (phy_data->mdio_reset == XGBE_MDIO_RESET_I2C_GPIO)
		ret = xgbe_phy_i2c_mdio_reset(pdata);
	अन्यथा अगर (phy_data->mdio_reset == XGBE_MDIO_RESET_INT_GPIO)
		ret = xgbe_phy_पूर्णांक_mdio_reset(pdata);

	xgbe_phy_put_comm_ownership(pdata);

	वापस ret;
पूर्ण

अटल bool xgbe_phy_redrv_error(काष्ठा xgbe_phy_data *phy_data)
अणु
	अगर (!phy_data->redrv)
		वापस false;

	अगर (phy_data->redrv_अगर >= XGBE_PHY_REDRV_IF_MAX)
		वापस true;

	चयन (phy_data->redrv_model) अणु
	हाल XGBE_PHY_REDRV_MODEL_4223:
		अगर (phy_data->redrv_lane > 3)
			वापस true;
		अवरोध;
	हाल XGBE_PHY_REDRV_MODEL_4227:
		अगर (phy_data->redrv_lane > 1)
			वापस true;
		अवरोध;
	शेष:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक xgbe_phy_mdio_reset_setup(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	अगर (phy_data->conn_type != XGBE_CONN_TYPE_MDIO)
		वापस 0;

	phy_data->mdio_reset = XP_GET_BITS(pdata->pp3, XP_PROP_3, MDIO_RESET);
	चयन (phy_data->mdio_reset) अणु
	हाल XGBE_MDIO_RESET_NONE:
	हाल XGBE_MDIO_RESET_I2C_GPIO:
	हाल XGBE_MDIO_RESET_INT_GPIO:
		अवरोध;
	शेष:
		dev_err(pdata->dev, "unsupported MDIO reset (%#x)\n",
			phy_data->mdio_reset);
		वापस -EINVAL;
	पूर्ण

	अगर (phy_data->mdio_reset == XGBE_MDIO_RESET_I2C_GPIO) अणु
		phy_data->mdio_reset_addr = XGBE_GPIO_ADDRESS_PCA9555 +
					    XP_GET_BITS(pdata->pp3, XP_PROP_3,
							MDIO_RESET_I2C_ADDR);
		phy_data->mdio_reset_gpio = XP_GET_BITS(pdata->pp3, XP_PROP_3,
							MDIO_RESET_I2C_GPIO);
	पूर्ण अन्यथा अगर (phy_data->mdio_reset == XGBE_MDIO_RESET_INT_GPIO) अणु
		phy_data->mdio_reset_gpio = XP_GET_BITS(pdata->pp3, XP_PROP_3,
							MDIO_RESET_INT_GPIO);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool xgbe_phy_port_mode_mismatch(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (phy_data->port_mode) अणु
	हाल XGBE_PORT_MODE_BACKPLANE:
	हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
		अगर ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000))
			वापस false;
		अवरोध;
	हाल XGBE_PORT_MODE_BACKPLANE_2500:
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_2500)
			वापस false;
		अवरोध;
	हाल XGBE_PORT_MODE_1000BASE_T:
		अगर ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000))
			वापस false;
		अवरोध;
	हाल XGBE_PORT_MODE_1000BASE_X:
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000)
			वापस false;
		अवरोध;
	हाल XGBE_PORT_MODE_NBASE_T:
		अगर ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_2500))
			वापस false;
		अवरोध;
	हाल XGBE_PORT_MODE_10GBASE_T:
		अगर ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000))
			वापस false;
		अवरोध;
	हाल XGBE_PORT_MODE_10GBASE_R:
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000)
			वापस false;
		अवरोध;
	हाल XGBE_PORT_MODE_SFP:
		अगर ((phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) ||
		    (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000))
			वापस false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल bool xgbe_phy_conn_type_mismatch(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (phy_data->port_mode) अणु
	हाल XGBE_PORT_MODE_BACKPLANE:
	हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
	हाल XGBE_PORT_MODE_BACKPLANE_2500:
		अगर (phy_data->conn_type == XGBE_CONN_TYPE_BACKPLANE)
			वापस false;
		अवरोध;
	हाल XGBE_PORT_MODE_1000BASE_T:
	हाल XGBE_PORT_MODE_1000BASE_X:
	हाल XGBE_PORT_MODE_NBASE_T:
	हाल XGBE_PORT_MODE_10GBASE_T:
	हाल XGBE_PORT_MODE_10GBASE_R:
		अगर (phy_data->conn_type == XGBE_CONN_TYPE_MDIO)
			वापस false;
		अवरोध;
	हाल XGBE_PORT_MODE_SFP:
		अगर (phy_data->conn_type == XGBE_CONN_TYPE_SFP)
			वापस false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल bool xgbe_phy_port_enabled(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (!XP_GET_BITS(pdata->pp0, XP_PROP_0, PORT_SPEEDS))
		वापस false;
	अगर (!XP_GET_BITS(pdata->pp0, XP_PROP_0, CONN_TYPE))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम xgbe_phy_cdr_track(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	अगर (!pdata->debugfs_an_cdr_workaround)
		वापस;

	अगर (!phy_data->phy_cdr_notrack)
		वापस;

	usleep_range(phy_data->phy_cdr_delay,
		     phy_data->phy_cdr_delay + 500);

	XMDIO_WRITE_BITS(pdata, MDIO_MMD_PMAPMD, MDIO_VEND2_PMA_CDR_CONTROL,
			 XGBE_PMA_CDR_TRACK_EN_MASK,
			 XGBE_PMA_CDR_TRACK_EN_ON);

	phy_data->phy_cdr_notrack = 0;
पूर्ण

अटल व्योम xgbe_phy_cdr_notrack(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	अगर (!pdata->debugfs_an_cdr_workaround)
		वापस;

	अगर (phy_data->phy_cdr_notrack)
		वापस;

	XMDIO_WRITE_BITS(pdata, MDIO_MMD_PMAPMD, MDIO_VEND2_PMA_CDR_CONTROL,
			 XGBE_PMA_CDR_TRACK_EN_MASK,
			 XGBE_PMA_CDR_TRACK_EN_OFF);

	xgbe_phy_rrc(pdata);

	phy_data->phy_cdr_notrack = 1;
पूर्ण

अटल व्योम xgbe_phy_kr_training_post(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (!pdata->debugfs_an_cdr_track_early)
		xgbe_phy_cdr_track(pdata);
पूर्ण

अटल व्योम xgbe_phy_kr_training_pre(काष्ठा xgbe_prv_data *pdata)
अणु
	अगर (pdata->debugfs_an_cdr_track_early)
		xgbe_phy_cdr_track(pdata);
पूर्ण

अटल व्योम xgbe_phy_an_post(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL73:
	हाल XGBE_AN_MODE_CL73_REDRV:
		अगर (phy_data->cur_mode != XGBE_MODE_KR)
			अवरोध;

		xgbe_phy_cdr_track(pdata);

		चयन (pdata->an_result) अणु
		हाल XGBE_AN_READY:
		हाल XGBE_AN_COMPLETE:
			अवरोध;
		शेष:
			अगर (phy_data->phy_cdr_delay < XGBE_CDR_DELAY_MAX)
				phy_data->phy_cdr_delay += XGBE_CDR_DELAY_INC;
			अन्यथा
				phy_data->phy_cdr_delay = XGBE_CDR_DELAY_INIT;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_an_pre(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	चयन (pdata->an_mode) अणु
	हाल XGBE_AN_MODE_CL73:
	हाल XGBE_AN_MODE_CL73_REDRV:
		अगर (phy_data->cur_mode != XGBE_MODE_KR)
			अवरोध;

		xgbe_phy_cdr_notrack(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xgbe_phy_stop(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	/* If we have an बाह्यal PHY, मुक्त it */
	xgbe_phy_मुक्त_phy_device(pdata);

	/* Reset SFP data */
	xgbe_phy_sfp_reset(phy_data);
	xgbe_phy_sfp_mod_असलent(pdata);

	/* Reset CDR support */
	xgbe_phy_cdr_track(pdata);

	/* Power off the PHY */
	xgbe_phy_घातer_off(pdata);

	/* Stop the I2C controller */
	pdata->i2c_अगर.i2c_stop(pdata);
पूर्ण

अटल पूर्णांक xgbe_phy_start(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	पूर्णांक ret;

	/* Start the I2C controller */
	ret = pdata->i2c_अगर.i2c_start(pdata);
	अगर (ret)
		वापस ret;

	/* Set the proper MDIO mode क्रम the re-driver */
	अगर (phy_data->redrv && !phy_data->redrv_अगर) अणु
		ret = pdata->hw_अगर.set_ext_mii_mode(pdata, phy_data->redrv_addr,
						    XGBE_MDIO_MODE_CL22);
		अगर (ret) अणु
			netdev_err(pdata->netdev,
				   "redriver mdio port not compatible (%u)\n",
				   phy_data->redrv_addr);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Start in highest supported mode */
	xgbe_phy_set_mode(pdata, phy_data->start_mode);

	/* Reset CDR support */
	xgbe_phy_cdr_track(pdata);

	/* After starting the I2C controller, we can check क्रम an SFP */
	चयन (phy_data->port_mode) अणु
	हाल XGBE_PORT_MODE_SFP:
		xgbe_phy_sfp_detect(pdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* If we have an बाह्यal PHY, start it */
	ret = xgbe_phy_find_phy_device(pdata);
	अगर (ret)
		जाओ err_i2c;

	वापस 0;

err_i2c:
	pdata->i2c_अगर.i2c_stop(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xgbe_phy_reset(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;
	क्रमागत xgbe_mode cur_mode;
	पूर्णांक ret;

	/* Reset by घातer cycling the PHY */
	cur_mode = phy_data->cur_mode;
	xgbe_phy_घातer_off(pdata);
	xgbe_phy_set_mode(pdata, cur_mode);

	अगर (!phy_data->phydev)
		वापस 0;

	/* Reset the बाह्यal PHY */
	ret = xgbe_phy_mdio_reset(pdata);
	अगर (ret)
		वापस ret;

	वापस phy_init_hw(phy_data->phydev);
पूर्ण

अटल व्योम xgbe_phy_निकास(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा xgbe_phy_data *phy_data = pdata->phy_data;

	/* Unरेजिस्टर क्रम driving बाह्यal PHYs */
	mdiobus_unरेजिस्टर(phy_data->mii);
पूर्ण

अटल पूर्णांक xgbe_phy_init(काष्ठा xgbe_prv_data *pdata)
अणु
	काष्ठा ethtool_link_ksettings *lks = &pdata->phy.lks;
	काष्ठा xgbe_phy_data *phy_data;
	काष्ठा mii_bus *mii;
	पूर्णांक ret;

	/* Check अगर enabled */
	अगर (!xgbe_phy_port_enabled(pdata)) अणु
		dev_info(pdata->dev, "device is not enabled\n");
		वापस -ENODEV;
	पूर्ण

	/* Initialize the I2C controller */
	ret = pdata->i2c_अगर.i2c_init(pdata);
	अगर (ret)
		वापस ret;

	phy_data = devm_kzalloc(pdata->dev, माप(*phy_data), GFP_KERNEL);
	अगर (!phy_data)
		वापस -ENOMEM;
	pdata->phy_data = phy_data;

	phy_data->port_mode = XP_GET_BITS(pdata->pp0, XP_PROP_0, PORT_MODE);
	phy_data->port_id = XP_GET_BITS(pdata->pp0, XP_PROP_0, PORT_ID);
	phy_data->port_speeds = XP_GET_BITS(pdata->pp0, XP_PROP_0, PORT_SPEEDS);
	phy_data->conn_type = XP_GET_BITS(pdata->pp0, XP_PROP_0, CONN_TYPE);
	phy_data->mdio_addr = XP_GET_BITS(pdata->pp0, XP_PROP_0, MDIO_ADDR);
	अगर (netअगर_msg_probe(pdata)) अणु
		dev_dbg(pdata->dev, "port mode=%u\n", phy_data->port_mode);
		dev_dbg(pdata->dev, "port id=%u\n", phy_data->port_id);
		dev_dbg(pdata->dev, "port speeds=%#x\n", phy_data->port_speeds);
		dev_dbg(pdata->dev, "conn type=%u\n", phy_data->conn_type);
		dev_dbg(pdata->dev, "mdio addr=%u\n", phy_data->mdio_addr);
	पूर्ण

	phy_data->redrv = XP_GET_BITS(pdata->pp4, XP_PROP_4, REDRV_PRESENT);
	phy_data->redrv_अगर = XP_GET_BITS(pdata->pp4, XP_PROP_4, REDRV_IF);
	phy_data->redrv_addr = XP_GET_BITS(pdata->pp4, XP_PROP_4, REDRV_ADDR);
	phy_data->redrv_lane = XP_GET_BITS(pdata->pp4, XP_PROP_4, REDRV_LANE);
	phy_data->redrv_model = XP_GET_BITS(pdata->pp4, XP_PROP_4, REDRV_MODEL);
	अगर (phy_data->redrv && netअगर_msg_probe(pdata)) अणु
		dev_dbg(pdata->dev, "redrv present\n");
		dev_dbg(pdata->dev, "redrv i/f=%u\n", phy_data->redrv_अगर);
		dev_dbg(pdata->dev, "redrv addr=%#x\n", phy_data->redrv_addr);
		dev_dbg(pdata->dev, "redrv lane=%u\n", phy_data->redrv_lane);
		dev_dbg(pdata->dev, "redrv model=%u\n", phy_data->redrv_model);
	पूर्ण

	/* Validate the connection requested */
	अगर (xgbe_phy_conn_type_mismatch(pdata)) अणु
		dev_err(pdata->dev, "phy mode/connection mismatch (%#x/%#x)\n",
			phy_data->port_mode, phy_data->conn_type);
		वापस -EINVAL;
	पूर्ण

	/* Validate the mode requested */
	अगर (xgbe_phy_port_mode_mismatch(pdata)) अणु
		dev_err(pdata->dev, "phy mode/speed mismatch (%#x/%#x)\n",
			phy_data->port_mode, phy_data->port_speeds);
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम and validate MDIO reset support */
	ret = xgbe_phy_mdio_reset_setup(pdata);
	अगर (ret)
		वापस ret;

	/* Validate the re-driver inक्रमmation */
	अगर (xgbe_phy_redrv_error(phy_data)) अणु
		dev_err(pdata->dev, "phy re-driver settings error\n");
		वापस -EINVAL;
	पूर्ण
	pdata->kr_redrv = phy_data->redrv;

	/* Indicate current mode is unknown */
	phy_data->cur_mode = XGBE_MODE_UNKNOWN;

	/* Initialize supported features */
	XGBE_ZERO_SUP(lks);

	चयन (phy_data->port_mode) अणु
	/* Backplane support */
	हाल XGBE_PORT_MODE_BACKPLANE:
		XGBE_SET_SUP(lks, Autoneg);
		fallthrough;
	हाल XGBE_PORT_MODE_BACKPLANE_NO_AUTONEG:
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		XGBE_SET_SUP(lks, Backplane);
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) अणु
			XGBE_SET_SUP(lks, 1000baseKX_Full);
			phy_data->start_mode = XGBE_MODE_KX_1000;
		पूर्ण
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000) अणु
			XGBE_SET_SUP(lks, 10000baseKR_Full);
			अगर (pdata->fec_ability & MDIO_PMA_10GBR_FECABLE_ABLE)
				XGBE_SET_SUP(lks, 10000baseR_FEC);
			phy_data->start_mode = XGBE_MODE_KR;
		पूर्ण

		phy_data->phydev_mode = XGBE_MDIO_MODE_NONE;
		अवरोध;
	हाल XGBE_PORT_MODE_BACKPLANE_2500:
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		XGBE_SET_SUP(lks, Backplane);
		XGBE_SET_SUP(lks, 2500baseX_Full);
		phy_data->start_mode = XGBE_MODE_KX_2500;

		phy_data->phydev_mode = XGBE_MDIO_MODE_NONE;
		अवरोध;

	/* MDIO 1GBase-T support */
	हाल XGBE_PORT_MODE_1000BASE_T:
		XGBE_SET_SUP(lks, Autoneg);
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		XGBE_SET_SUP(lks, TP);
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) अणु
			XGBE_SET_SUP(lks, 100baseT_Full);
			phy_data->start_mode = XGBE_MODE_SGMII_100;
		पूर्ण
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) अणु
			XGBE_SET_SUP(lks, 1000baseT_Full);
			phy_data->start_mode = XGBE_MODE_SGMII_1000;
		पूर्ण

		phy_data->phydev_mode = XGBE_MDIO_MODE_CL22;
		अवरोध;

	/* MDIO Base-X support */
	हाल XGBE_PORT_MODE_1000BASE_X:
		XGBE_SET_SUP(lks, Autoneg);
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		XGBE_SET_SUP(lks, FIBRE);
		XGBE_SET_SUP(lks, 1000baseX_Full);
		phy_data->start_mode = XGBE_MODE_X;

		phy_data->phydev_mode = XGBE_MDIO_MODE_CL22;
		अवरोध;

	/* MDIO NBase-T support */
	हाल XGBE_PORT_MODE_NBASE_T:
		XGBE_SET_SUP(lks, Autoneg);
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		XGBE_SET_SUP(lks, TP);
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) अणु
			XGBE_SET_SUP(lks, 100baseT_Full);
			phy_data->start_mode = XGBE_MODE_SGMII_100;
		पूर्ण
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) अणु
			XGBE_SET_SUP(lks, 1000baseT_Full);
			phy_data->start_mode = XGBE_MODE_SGMII_1000;
		पूर्ण
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_2500) अणु
			XGBE_SET_SUP(lks, 2500baseT_Full);
			phy_data->start_mode = XGBE_MODE_KX_2500;
		पूर्ण

		phy_data->phydev_mode = XGBE_MDIO_MODE_CL45;
		अवरोध;

	/* 10GBase-T support */
	हाल XGBE_PORT_MODE_10GBASE_T:
		XGBE_SET_SUP(lks, Autoneg);
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		XGBE_SET_SUP(lks, TP);
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100) अणु
			XGBE_SET_SUP(lks, 100baseT_Full);
			phy_data->start_mode = XGBE_MODE_SGMII_100;
		पूर्ण
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000) अणु
			XGBE_SET_SUP(lks, 1000baseT_Full);
			phy_data->start_mode = XGBE_MODE_SGMII_1000;
		पूर्ण
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000) अणु
			XGBE_SET_SUP(lks, 10000baseT_Full);
			phy_data->start_mode = XGBE_MODE_KR;
		पूर्ण

		phy_data->phydev_mode = XGBE_MDIO_MODE_CL45;
		अवरोध;

	/* 10GBase-R support */
	हाल XGBE_PORT_MODE_10GBASE_R:
		XGBE_SET_SUP(lks, Autoneg);
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		XGBE_SET_SUP(lks, FIBRE);
		XGBE_SET_SUP(lks, 10000baseSR_Full);
		XGBE_SET_SUP(lks, 10000baseLR_Full);
		XGBE_SET_SUP(lks, 10000baseLRM_Full);
		XGBE_SET_SUP(lks, 10000baseER_Full);
		अगर (pdata->fec_ability & MDIO_PMA_10GBR_FECABLE_ABLE)
			XGBE_SET_SUP(lks, 10000baseR_FEC);
		phy_data->start_mode = XGBE_MODE_SFI;

		phy_data->phydev_mode = XGBE_MDIO_MODE_NONE;
		अवरोध;

	/* SFP support */
	हाल XGBE_PORT_MODE_SFP:
		XGBE_SET_SUP(lks, Autoneg);
		XGBE_SET_SUP(lks, Pause);
		XGBE_SET_SUP(lks, Asym_Pause);
		XGBE_SET_SUP(lks, TP);
		XGBE_SET_SUP(lks, FIBRE);
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_100)
			phy_data->start_mode = XGBE_MODE_SGMII_100;
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_1000)
			phy_data->start_mode = XGBE_MODE_SGMII_1000;
		अगर (phy_data->port_speeds & XGBE_PHY_PORT_SPEED_10000)
			phy_data->start_mode = XGBE_MODE_SFI;

		phy_data->phydev_mode = XGBE_MDIO_MODE_CL22;

		xgbe_phy_sfp_setup(pdata);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (netअगर_msg_probe(pdata))
		dev_dbg(pdata->dev, "phy supported=0x%*pb\n",
			__ETHTOOL_LINK_MODE_MASK_NBITS,
			lks->link_modes.supported);

	अगर ((phy_data->conn_type & XGBE_CONN_TYPE_MDIO) &&
	    (phy_data->phydev_mode != XGBE_MDIO_MODE_NONE)) अणु
		ret = pdata->hw_अगर.set_ext_mii_mode(pdata, phy_data->mdio_addr,
						    phy_data->phydev_mode);
		अगर (ret) अणु
			dev_err(pdata->dev,
				"mdio port/clause not compatible (%d/%u)\n",
				phy_data->mdio_addr, phy_data->phydev_mode);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (phy_data->redrv && !phy_data->redrv_अगर) अणु
		ret = pdata->hw_अगर.set_ext_mii_mode(pdata, phy_data->redrv_addr,
						    XGBE_MDIO_MODE_CL22);
		अगर (ret) अणु
			dev_err(pdata->dev,
				"redriver mdio port not compatible (%u)\n",
				phy_data->redrv_addr);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	phy_data->phy_cdr_delay = XGBE_CDR_DELAY_INIT;

	/* Register क्रम driving बाह्यal PHYs */
	mii = devm_mdiobus_alloc(pdata->dev);
	अगर (!mii) अणु
		dev_err(pdata->dev, "mdiobus_alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	mii->priv = pdata;
	mii->name = "amd-xgbe-mii";
	mii->पढ़ो = xgbe_phy_mii_पढ़ो;
	mii->ग_लिखो = xgbe_phy_mii_ग_लिखो;
	mii->parent = pdata->dev;
	mii->phy_mask = ~0;
	snम_लिखो(mii->id, माप(mii->id), "%s", dev_name(pdata->dev));
	ret = mdiobus_रेजिस्टर(mii);
	अगर (ret) अणु
		dev_err(pdata->dev, "mdiobus_register failed\n");
		वापस ret;
	पूर्ण
	phy_data->mii = mii;

	वापस 0;
पूर्ण

व्योम xgbe_init_function_ptrs_phy_v2(काष्ठा xgbe_phy_अगर *phy_अगर)
अणु
	काष्ठा xgbe_phy_impl_अगर *phy_impl = &phy_अगर->phy_impl;

	phy_impl->init			= xgbe_phy_init;
	phy_impl->निकास			= xgbe_phy_निकास;

	phy_impl->reset			= xgbe_phy_reset;
	phy_impl->start			= xgbe_phy_start;
	phy_impl->stop			= xgbe_phy_stop;

	phy_impl->link_status		= xgbe_phy_link_status;

	phy_impl->valid_speed		= xgbe_phy_valid_speed;

	phy_impl->use_mode		= xgbe_phy_use_mode;
	phy_impl->set_mode		= xgbe_phy_set_mode;
	phy_impl->get_mode		= xgbe_phy_get_mode;
	phy_impl->चयन_mode		= xgbe_phy_चयन_mode;
	phy_impl->cur_mode		= xgbe_phy_cur_mode;

	phy_impl->an_mode		= xgbe_phy_an_mode;

	phy_impl->an_config		= xgbe_phy_an_config;

	phy_impl->an_advertising	= xgbe_phy_an_advertising;

	phy_impl->an_outcome		= xgbe_phy_an_outcome;

	phy_impl->an_pre		= xgbe_phy_an_pre;
	phy_impl->an_post		= xgbe_phy_an_post;

	phy_impl->kr_training_pre	= xgbe_phy_kr_training_pre;
	phy_impl->kr_training_post	= xgbe_phy_kr_training_post;

	phy_impl->module_info		= xgbe_phy_module_info;
	phy_impl->module_eeprom		= xgbe_phy_module_eeprom;
पूर्ण
