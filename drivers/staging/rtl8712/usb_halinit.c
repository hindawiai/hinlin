<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * usb_halinit.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _HCI_HAL_INIT_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "usb_ops.h"
#समावेश "usb_osintf.h"

u8 r8712_usb_hal_bus_init(काष्ठा _adapter *adapter)
अणु
	u8 val8 = 0;
	u8 ret = _SUCCESS;
	पूर्णांक PollingCnt = 20;
	काष्ठा registry_priv *registrypriv = &adapter->registrypriv;

	अगर (registrypriv->chip_version == RTL8712_FPGA) अणु
		val8 = 0x01;
		/* चयन to 80M घड़ी */
		r8712_ग_लिखो8(adapter, SYS_CLKR, val8);
		val8 = r8712_पढ़ो8(adapter, SPS1_CTRL);
		val8 = val8 | 0x01;
		/* enable VSPS12 LDO Macro block */
		r8712_ग_लिखो8(adapter, SPS1_CTRL, val8);
		val8 = r8712_पढ़ो8(adapter, AFE_MISC);
		val8 = val8 | 0x01;
		/* Enable AFE Macro Block's Bandgap */
		r8712_ग_लिखो8(adapter, AFE_MISC, val8);
		val8 = r8712_पढ़ो8(adapter, LDOA15_CTRL);
		val8 = val8 | 0x01;
		/* enable LDOA15 block */
		r8712_ग_लिखो8(adapter, LDOA15_CTRL, val8);
		val8 = r8712_पढ़ो8(adapter, SPS1_CTRL);
		val8 = val8 | 0x02;
		/* Enable VSPS12_SW Macro Block */
		r8712_ग_लिखो8(adapter, SPS1_CTRL, val8);
		val8 = r8712_पढ़ो8(adapter, AFE_MISC);
		val8 = val8 | 0x02;
		/* Enable AFE Macro Block's Mbias */
		r8712_ग_लिखो8(adapter, AFE_MISC, val8);
		val8 = r8712_पढ़ो8(adapter, SYS_ISO_CTRL + 1);
		val8 = val8 | 0x08;
		/* isolate PCIe Analog 1.2V to PCIe 3.3V and PCIE Digital */
		r8712_ग_लिखो8(adapter, SYS_ISO_CTRL + 1, val8);
		val8 = r8712_पढ़ो8(adapter, SYS_ISO_CTRL + 1);
		val8 = val8 & 0xEF;
		/* attach AFE PLL to MACTOP/BB/PCIe Digital */
		r8712_ग_लिखो8(adapter, SYS_ISO_CTRL + 1, val8);
		val8 = r8712_पढ़ो8(adapter, AFE_XTAL_CTRL + 1);
		val8 = val8 & 0xFB;
		/* enable AFE घड़ी */
		r8712_ग_लिखो8(adapter, AFE_XTAL_CTRL + 1, val8);
		val8 = r8712_पढ़ो8(adapter, AFE_PLL_CTRL);
		val8 = val8 | 0x01;
		/* Enable AFE PLL Macro Block */
		r8712_ग_लिखो8(adapter, AFE_PLL_CTRL, val8);
		val8 = 0xEE;
		/* release isolation AFE PLL & MD */
		r8712_ग_लिखो8(adapter, SYS_ISO_CTRL, val8);
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR + 1);
		val8 = val8 | 0x08;
		/* enable MAC घड़ी */
		r8712_ग_लिखो8(adapter, SYS_CLKR + 1, val8);
		val8 = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		val8 = val8 | 0x08;
		/* enable Core digital and enable IOREG R/W */
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, val8);
		val8 = val8 | 0x80;
		/* enable REG_EN */
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, val8);
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR + 1);
		val8 = (val8 | 0x80) & 0xBF;
		/* चयन the control path */
		r8712_ग_लिखो8(adapter, SYS_CLKR + 1, val8);
		val8 = 0xFC;
		r8712_ग_लिखो8(adapter, CR, val8);
		val8 = 0x37;
		r8712_ग_लिखो8(adapter, CR + 1, val8);
		/* reduce EndPoपूर्णांक & init it */
		r8712_ग_लिखो8(adapter, 0x102500ab, r8712_पढ़ो8(adapter,
			     0x102500ab) | BIT(6) | BIT(7));
		/* consideration of घातer consumption - init */
		r8712_ग_लिखो8(adapter, 0x10250008, r8712_पढ़ो8(adapter,
			     0x10250008) & 0xfffffffb);
	पूर्ण अन्यथा अगर (registrypriv->chip_version == RTL8712_1stCUT) अणु
		/* Initialization क्रम घातer on sequence, */
		r8712_ग_लिखो8(adapter, SPS0_CTRL + 1, 0x53);
		r8712_ग_लिखो8(adapter, SPS0_CTRL, 0x57);
		/* Enable AFE Macro Block's Bandgap and Enable AFE Macro
		 * Block's Mbias
		 */
		val8 = r8712_पढ़ो8(adapter, AFE_MISC);
		r8712_ग_लिखो8(adapter, AFE_MISC, (val8 | AFE_MISC_BGEN |
			     AFE_MISC_MBEN));
		/* Enable LDOA15 block */
		val8 = r8712_पढ़ो8(adapter, LDOA15_CTRL);
		r8712_ग_लिखो8(adapter, LDOA15_CTRL, (val8 | LDA15_EN));
		val8 = r8712_पढ़ो8(adapter, SPS1_CTRL);
		r8712_ग_लिखो8(adapter, SPS1_CTRL, (val8 | SPS1_LDEN));
		msleep(20);
		/* Enable Switch Regulator Block */
		val8 = r8712_पढ़ो8(adapter, SPS1_CTRL);
		r8712_ग_लिखो8(adapter, SPS1_CTRL, (val8 | SPS1_SWEN));
		r8712_ग_लिखो32(adapter, SPS1_CTRL, 0x00a7b267);
		val8 = r8712_पढ़ो8(adapter, SYS_ISO_CTRL + 1);
		r8712_ग_लिखो8(adapter, SYS_ISO_CTRL + 1, (val8 | 0x08));
		/* Engineer Packet CP test Enable */
		val8 = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, (val8 | 0x20));
		val8 = r8712_पढ़ो8(adapter, SYS_ISO_CTRL + 1);
		r8712_ग_लिखो8(adapter, SYS_ISO_CTRL + 1, (val8 & 0x6F));
		/* Enable AFE घड़ी */
		val8 = r8712_पढ़ो8(adapter, AFE_XTAL_CTRL + 1);
		r8712_ग_लिखो8(adapter, AFE_XTAL_CTRL + 1, (val8 & 0xfb));
		/* Enable AFE PLL Macro Block */
		val8 = r8712_पढ़ो8(adapter, AFE_PLL_CTRL);
		r8712_ग_लिखो8(adapter, AFE_PLL_CTRL, (val8 | 0x11));
		/* Attach AFE PLL to MACTOP/BB/PCIe Digital */
		val8 = r8712_पढ़ो8(adapter, SYS_ISO_CTRL);
		r8712_ग_लिखो8(adapter, SYS_ISO_CTRL, (val8 & 0xEE));
		/* Switch to 40M घड़ी */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR);
		r8712_ग_लिखो8(adapter, SYS_CLKR, val8 & (~SYS_CLKSEL));
		/* SSC Disable */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR);
		/* Enable MAC घड़ी */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR + 1);
		r8712_ग_लिखो8(adapter, SYS_CLKR + 1, (val8 | 0x18));
		/* Revised POS, */
		r8712_ग_लिखो8(adapter, PMC_FSM, 0x02);
		/* Enable Core digital and enable IOREG R/W */
		val8 = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, (val8 | 0x08));
		/* Enable REG_EN */
		val8 = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, (val8 | 0x80));
		/* Switch the control path to FW */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR + 1);
		r8712_ग_लिखो8(adapter, SYS_CLKR + 1, (val8 | 0x80) & 0xBF);
		r8712_ग_लिखो8(adapter, CR, 0xFC);
		r8712_ग_लिखो8(adapter, CR + 1, 0x37);
		/* Fix the RX FIFO issue(usb error), */
		val8 = r8712_पढ़ो8(adapter, 0x1025FE5c);
		r8712_ग_लिखो8(adapter, 0x1025FE5c, (val8 | BIT(7)));
		val8 = r8712_पढ़ो8(adapter, 0x102500ab);
		r8712_ग_लिखो8(adapter, 0x102500ab, (val8 | BIT(6) | BIT(7)));
		/* For घातer save, used this in the bit file after 970621 */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR);
		r8712_ग_लिखो8(adapter, SYS_CLKR, val8 & (~CPU_CLKSEL));
	पूर्ण अन्यथा अगर (registrypriv->chip_version == RTL8712_2ndCUT ||
		   registrypriv->chip_version == RTL8712_3rdCUT) अणु
		/* Initialization क्रम घातer on sequence,
		 * E-Fuse leakage prevention sequence
		 */
		r8712_ग_लिखो8(adapter, 0x37, 0xb0);
		msleep(20);
		r8712_ग_लिखो8(adapter, 0x37, 0x30);
		/* Set control path चयन to HW control and reset Digital Core,
		 * CPU Core and MAC I/O to solve FW करोwnload fail when प्रणाली
		 * from resume sate.
		 */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR + 1);
		अगर (val8 & 0x80) अणु
			val8 &= 0x3f;
			r8712_ग_लिखो8(adapter, SYS_CLKR + 1, val8);
		पूर्ण
		val8 = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		val8 &= 0x73;
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, val8);
		msleep(20);
		/* Revised POS, */
		/* Enable AFE Macro Block's Bandgap and Enable AFE Macro
		 * Block's Mbias
		 */
		r8712_ग_लिखो8(adapter, SPS0_CTRL + 1, 0x53);
		r8712_ग_लिखो8(adapter, SPS0_CTRL, 0x57);
		val8 = r8712_पढ़ो8(adapter, AFE_MISC);
		/*Bandgap*/
		r8712_ग_लिखो8(adapter, AFE_MISC, (val8 | AFE_MISC_BGEN));
		r8712_ग_लिखो8(adapter, AFE_MISC, (val8 | AFE_MISC_BGEN |
			     AFE_MISC_MBEN | AFE_MISC_I32_EN));
		/* Enable PLL Power (LDOA15V) */
		val8 = r8712_पढ़ो8(adapter, LDOA15_CTRL);
		r8712_ग_लिखो8(adapter, LDOA15_CTRL, (val8 | LDA15_EN));
		/* Enable LDOV12D block */
		val8 = r8712_पढ़ो8(adapter, LDOV12D_CTRL);
		r8712_ग_लिखो8(adapter, LDOV12D_CTRL, (val8 | LDV12_EN));
		val8 = r8712_पढ़ो8(adapter, SYS_ISO_CTRL + 1);
		r8712_ग_लिखो8(adapter, SYS_ISO_CTRL + 1, (val8 | 0x08));
		/* Engineer Packet CP test Enable */
		val8 = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, (val8 | 0x20));
		/* Support 64k IMEM */
		val8 = r8712_पढ़ो8(adapter, SYS_ISO_CTRL + 1);
		r8712_ग_लिखो8(adapter, SYS_ISO_CTRL + 1, (val8 & 0x68));
		/* Enable AFE घड़ी */
		val8 = r8712_पढ़ो8(adapter, AFE_XTAL_CTRL + 1);
		r8712_ग_लिखो8(adapter, AFE_XTAL_CTRL + 1, (val8 & 0xfb));
		/* Enable AFE PLL Macro Block */
		val8 = r8712_पढ़ो8(adapter, AFE_PLL_CTRL);
		r8712_ग_लिखो8(adapter, AFE_PLL_CTRL, (val8 | 0x11));
		/* Some sample will करोwnload fw failure. The घड़ी will be
		 * stable with 500 us delay after reset the PLL
		 * TODO: When usleep is added to kernel, change next 3
		 * udelay(500) to usleep(500)
		 */
		udelay(500);
		r8712_ग_लिखो8(adapter, AFE_PLL_CTRL, (val8 | 0x51));
		udelay(500);
		r8712_ग_लिखो8(adapter, AFE_PLL_CTRL, (val8 | 0x11));
		udelay(500);
		/* Attach AFE PLL to MACTOP/BB/PCIe Digital */
		val8 = r8712_पढ़ो8(adapter, SYS_ISO_CTRL);
		r8712_ग_लिखो8(adapter, SYS_ISO_CTRL, (val8 & 0xEE));
		/* Switch to 40M घड़ी */
		r8712_ग_लिखो8(adapter, SYS_CLKR, 0x00);
		/* CPU Clock and 80M Clock SSC Disable to overcome FW करोwnload
		 * fail timing issue.
		 */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR);
		r8712_ग_लिखो8(adapter, SYS_CLKR, (val8 | 0xa0));
		/* Enable MAC घड़ी */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR + 1);
		r8712_ग_लिखो8(adapter, SYS_CLKR + 1, (val8 | 0x18));
		/* Revised POS, */
		r8712_ग_लिखो8(adapter, PMC_FSM, 0x02);
		/* Enable Core digital and enable IOREG R/W */
		val8 = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, (val8 | 0x08));
		/* Enable REG_EN */
		val8 = r8712_पढ़ो8(adapter, SYS_FUNC_EN + 1);
		r8712_ग_लिखो8(adapter, SYS_FUNC_EN + 1, (val8 | 0x80));
		/* Switch the control path to FW */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR + 1);
		r8712_ग_लिखो8(adapter, SYS_CLKR + 1, (val8 | 0x80) & 0xBF);
		r8712_ग_लिखो8(adapter, CR, 0xFC);
		r8712_ग_लिखो8(adapter, CR + 1, 0x37);
		/* Fix the RX FIFO issue(usb error), 970410 */
		val8 = r8712_पढ़ो8(adapter, 0x1025FE5c);
		r8712_ग_लिखो8(adapter, 0x1025FE5c, (val8 | BIT(7)));
		/* For घातer save, used this in the bit file after 970621 */
		val8 = r8712_पढ़ो8(adapter, SYS_CLKR);
		r8712_ग_लिखो8(adapter, SYS_CLKR, val8 & (~CPU_CLKSEL));
		/* Revised क्रम 8051 ROM code wrong operation. */
		r8712_ग_लिखो8(adapter, 0x1025fe1c, 0x80);
		/* To make sure that TxDMA can पढ़ोy to करोwnload FW.
		 * We should reset TxDMA अगर IMEM RPT was not पढ़ोy.
		 */
		करो अणु
			val8 = r8712_पढ़ो8(adapter, TCR);
			अगर ((val8 & _TXDMA_INIT_VALUE) == _TXDMA_INIT_VALUE)
				अवरोध;
			udelay(5); /* Platक्रमmStallExecution(5); */
		पूर्ण जबतक (PollingCnt--);	/* Delay 1ms */

		अगर (PollingCnt <= 0) अणु
			val8 = r8712_पढ़ो8(adapter, CR);
			r8712_ग_लिखो8(adapter, CR, val8 & (~_TXDMA_EN));
			udelay(2); /* Platक्रमmStallExecution(2); */
			/* Reset TxDMA */
			r8712_ग_लिखो8(adapter, CR, val8 | _TXDMA_EN);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = _FAIL;
	पूर्ण
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक r8712_usb_inirp_init(काष्ठा _adapter *adapter)
अणु
	u8 i;
	काष्ठा recv_buf *recvbuf;
	काष्ठा पूर्णांकf_hdl *पूर्णांकfhdl = &adapter->pio_queue->पूर्णांकf;
	काष्ठा recv_priv *recvpriv = &(adapter->recvpriv);

	recvpriv->ff_hwaddr = RTL8712_DMA_RX0FF; /* mapping rx fअगरo address */
	/* issue Rx irp to receive data */
	recvbuf = (काष्ठा recv_buf *)recvpriv->precv_buf;
	क्रम (i = 0; i < NR_RECVBUFF; i++) अणु
		अगर (r8712_usb_पढ़ो_port(पूर्णांकfhdl, recvpriv->ff_hwaddr, 0,
					(अचिन्हित अक्षर *)recvbuf) == false)
			वापस _FAIL;
		recvbuf++;
		recvpriv->मुक्त_recv_buf_queue_cnt--;
	पूर्ण
	वापस _SUCCESS;
पूर्ण

अचिन्हित पूर्णांक r8712_usb_inirp_deinit(काष्ठा _adapter *adapter)
अणु
	r8712_usb_पढ़ो_port_cancel(adapter);
	वापस _SUCCESS;
पूर्ण
