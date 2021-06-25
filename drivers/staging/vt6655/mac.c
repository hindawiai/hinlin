<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: mac.c
 *
 * Purpose:  MAC routines
 *
 * Author: Tevin Chen
 *
 * Date: May 21, 1996
 *
 * Functions:
 *      MACbIsRegBitsOff - Test अगर All test Bits Off
 *      MACbIsIntDisable - Test अगर MAC पूर्णांकerrupt disable
 *      MACvSetShortRetryLimit - Set 802.11 Short Retry limit
 *      MACvSetLongRetryLimit - Set 802.11 Long Retry limit
 *      MACvSetLoopbackMode - Set MAC Loopback Mode
 *      MACvSaveContext - Save Context of MAC Registers
 *      MACvRestoreContext - Restore Context of MAC Registers
 *      MACbSoftwareReset - Software Reset MAC
 *      MACbSafeRxOff - Turn Off MAC Rx
 *      MACbSafeTxOff - Turn Off MAC Tx
 *      MACbSafeStop - Stop MAC function
 *      MACbShutकरोwn - Shut करोwn MAC
 *      MACvInitialize - Initialize MAC
 *      MACvSetCurrRxDescAddr - Set Rx Descriptors Address
 *      MACvSetCurrTx0DescAddr - Set Tx0 Descriptors Address
 *      MACvSetCurrTx1DescAddr - Set Tx1 Descriptors Address
 *      MACvTimer0MicroSDelay - Micro Second Delay Loop by MAC
 *
 * Revision History:
 *      08-22-2003 Kyle Hsu     :  Porting MAC functions from sim53
 *      09-03-2003 Bryan YC Fan :  Add MACvClearBusSusInd()&
 *				   MACvEnableBusSusEn()
 *      09-18-2003 Jerry Chen   :  Add MACvSetKeyEntry & MACvDisableKeyEntry
 *
 */

#समावेश "tmacro.h"
#समावेश "mac.h"

/*
 * Description:
 *      Test अगर all test bits off
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *      byRegOfs    - Offset of MAC Register
 *      byTestBits  - Test bits
 *  Out:
 *      none
 *
 * Return Value: true अगर all test bits Off; otherwise false
 *
 */
bool MACbIsRegBitsOff(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byRegOfs,
		      अचिन्हित अक्षर byTestBits)
अणु
	व्योम __iomem *io_base = priv->PortOffset;

	वापस !(ioपढ़ो8(io_base + byRegOfs) & byTestBits);
पूर्ण

/*
 * Description:
 *      Test अगर MAC पूर्णांकerrupt disable
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *  Out:
 *      none
 *
 * Return Value: true अगर पूर्णांकerrupt is disable; otherwise false
 *
 */
bool MACbIsIntDisable(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *io_base = priv->PortOffset;

	अगर (ioपढ़ो32(io_base + MAC_REG_IMR))
		वापस false;

	वापस true;
पूर्ण

/*
 * Description:
 *      Set 802.11 Short Retry Limit
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *      byRetryLimit- Retry Limit
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvSetShortRetryLimit(काष्ठा vnt_निजी *priv,
			    अचिन्हित अक्षर byRetryLimit)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	/* set SRT */
	ioग_लिखो8(byRetryLimit, io_base + MAC_REG_SRT);
पूर्ण

/*
 * Description:
 *      Set 802.11 Long Retry Limit
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *      byRetryLimit- Retry Limit
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvSetLongRetryLimit(काष्ठा vnt_निजी *priv,
			   अचिन्हित अक्षर byRetryLimit)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	/* set LRT */
	ioग_लिखो8(byRetryLimit, io_base + MAC_REG_LRT);
पूर्ण

/*
 * Description:
 *      Set MAC Loopback mode
 *
 * Parameters:
 *  In:
 *      io_base        - Base Address क्रम MAC
 *      byLoopbackMode  - Loopback Mode
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvSetLoopbackMode(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byLoopbackMode)
अणु
	व्योम __iomem *io_base = priv->PortOffset;

	byLoopbackMode <<= 6;
	/* set TCR */
	ioग_लिखो8((ioपढ़ो8(io_base + MAC_REG_TEST) & 0x3f) | byLoopbackMode,
		 io_base + MAC_REG_TEST);
पूर्ण

/*
 * Description:
 *      Save MAC रेजिस्टरs to context buffer
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *  Out:
 *      cxt_buf   - Context buffer
 *
 * Return Value: none
 *
 */
व्योम MACvSaveContext(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर *cxt_buf)
अणु
	व्योम __iomem *io_base = priv->PortOffset;

	/* पढ़ो page0 रेजिस्टर */
	स_नकल_fromio(cxt_buf, io_base, MAC_MAX_CONTEXT_SIZE_PAGE0);

	MACvSelectPage1(io_base);

	/* पढ़ो page1 रेजिस्टर */
	स_नकल_fromio(cxt_buf + MAC_MAX_CONTEXT_SIZE_PAGE0, io_base,
		      MAC_MAX_CONTEXT_SIZE_PAGE1);

	MACvSelectPage0(io_base);
पूर्ण

/*
 * Description:
 *      Restore MAC रेजिस्टरs from context buffer
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *      cxt_buf   - Context buffer
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvRestoreContext(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर *cxt_buf)
अणु
	व्योम __iomem *io_base = priv->PortOffset;

	MACvSelectPage1(io_base);
	/* restore page1 */
	स_नकल_toio(io_base, cxt_buf + MAC_MAX_CONTEXT_SIZE_PAGE0,
		    MAC_MAX_CONTEXT_SIZE_PAGE1);

	MACvSelectPage0(io_base);

	/* restore RCR,TCR,IMR... */
	स_नकल_toio(io_base + MAC_REG_RCR, cxt_buf + MAC_REG_RCR,
		    MAC_REG_ISR - MAC_REG_RCR);

	/* restore MAC Config. */
	स_नकल_toio(io_base + MAC_REG_LRT, cxt_buf + MAC_REG_LRT,
		    MAC_REG_PAGE1SEL - MAC_REG_LRT);

	ioग_लिखो8(*(cxt_buf + MAC_REG_CFG), io_base + MAC_REG_CFG);

	/* restore PS Config. */
	स_नकल_toio(io_base + MAC_REG_PSCFG, cxt_buf + MAC_REG_PSCFG,
		    MAC_REG_BBREGCTL - MAC_REG_PSCFG);

	/* restore CURR_RX_DESC_ADDR, CURR_TX_DESC_ADDR */
	ioग_लिखो32(*(u32 *)(cxt_buf + MAC_REG_TXDMAPTR0),
		  io_base + MAC_REG_TXDMAPTR0);
	ioग_लिखो32(*(u32 *)(cxt_buf + MAC_REG_AC0DMAPTR),
		  io_base + MAC_REG_AC0DMAPTR);
	ioग_लिखो32(*(u32 *)(cxt_buf + MAC_REG_BCNDMAPTR),
		  io_base + MAC_REG_BCNDMAPTR);
	ioग_लिखो32(*(u32 *)(cxt_buf + MAC_REG_RXDMAPTR0),
		  io_base + MAC_REG_RXDMAPTR0);
	ioग_लिखो32(*(u32 *)(cxt_buf + MAC_REG_RXDMAPTR1),
		  io_base + MAC_REG_RXDMAPTR1);
पूर्ण

/*
 * Description:
 *      Software Reset MAC
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *  Out:
 *      none
 *
 * Return Value: true अगर Reset Success; otherwise false
 *
 */
bool MACbSoftwareReset(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित लघु ww;

	/* turn on HOSTCR_SOFTRST, just ग_लिखो 0x01 to reset */
	ioग_लिखो8(0x01, io_base + MAC_REG_HOSTCR);

	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो8(io_base + MAC_REG_HOSTCR) & HOSTCR_SOFTRST))
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT)
		वापस false;
	वापस true;
पूर्ण

/*
 * Description:
 *      save some important रेजिस्टर's value, then करो reset, then restore
 *	रेजिस्टर's value
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *  Out:
 *      none
 *
 * Return Value: true अगर success; otherwise false
 *
 */
bool MACbSafeSoftwareReset(काष्ठा vnt_निजी *priv)
अणु
	अचिन्हित अक्षर abyTmpRegData[MAC_MAX_CONTEXT_SIZE_PAGE0 + MAC_MAX_CONTEXT_SIZE_PAGE1];
	bool bRetVal;

	/* PATCH....
	 * save some important रेजिस्टर's value, then करो
	 * reset, then restore रेजिस्टर's value
	 */
	/* save MAC context */
	MACvSaveContext(priv, abyTmpRegData);
	/* करो reset */
	bRetVal = MACbSoftwareReset(priv);
	/* restore MAC context, except CR0 */
	MACvRestoreContext(priv, abyTmpRegData);

	वापस bRetVal;
पूर्ण

/*
 * Description:
 *      Turn Off MAC Rx
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *  Out:
 *      none
 *
 * Return Value: true अगर success; otherwise false
 *
 */
bool MACbSafeRxOff(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित लघु ww;

	/* turn off wow temp क्रम turn off Rx safely */

	/* Clear RX DMA0,1 */
	ioग_लिखो32(DMACTL_CLRRUN, io_base + MAC_REG_RXDMACTL0);
	ioग_लिखो32(DMACTL_CLRRUN, io_base + MAC_REG_RXDMACTL1);
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो32(io_base + MAC_REG_RXDMACTL0) & DMACTL_RUN))
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT) अणु
		pr_debug(" DBG_PORT80(0x10)\n");
		वापस false;
	पूर्ण
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो32(io_base + MAC_REG_RXDMACTL1) & DMACTL_RUN))
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT) अणु
		pr_debug(" DBG_PORT80(0x11)\n");
		वापस false;
	पूर्ण

	/* try to safe shutकरोwn RX */
	MACvRegBitsOff(io_base, MAC_REG_HOSTCR, HOSTCR_RXON);
	/* W_MAX_TIMEOUT is the समयout period */
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो8(io_base + MAC_REG_HOSTCR) & HOSTCR_RXONST))
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT) अणु
		pr_debug(" DBG_PORT80(0x12)\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Description:
 *      Turn Off MAC Tx
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *  Out:
 *      none
 *
 * Return Value: true अगर success; otherwise false
 *
 */
bool MACbSafeTxOff(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित लघु ww;

	/* Clear TX DMA */
	/* Tx0 */
	ioग_लिखो32(DMACTL_CLRRUN, io_base + MAC_REG_TXDMACTL0);
	/* AC0 */
	ioग_लिखो32(DMACTL_CLRRUN, io_base + MAC_REG_AC0DMACTL);

	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो32(io_base + MAC_REG_TXDMACTL0) & DMACTL_RUN))
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT) अणु
		pr_debug(" DBG_PORT80(0x20)\n");
		वापस false;
	पूर्ण
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो32(io_base + MAC_REG_AC0DMACTL) & DMACTL_RUN))
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT) अणु
		pr_debug(" DBG_PORT80(0x21)\n");
		वापस false;
	पूर्ण

	/* try to safe shutकरोwn TX */
	MACvRegBitsOff(io_base, MAC_REG_HOSTCR, HOSTCR_TXON);

	/* W_MAX_TIMEOUT is the समयout period */
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो8(io_base + MAC_REG_HOSTCR) & HOSTCR_TXONST))
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT) अणु
		pr_debug(" DBG_PORT80(0x24)\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Description:
 *      Stop MAC function
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *  Out:
 *      none
 *
 * Return Value: true अगर success; otherwise false
 *
 */
bool MACbSafeStop(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *io_base = priv->PortOffset;

	MACvRegBitsOff(io_base, MAC_REG_TCR, TCR_AUTOBCNTX);

	अगर (!MACbSafeRxOff(priv)) अणु
		pr_debug(" MACbSafeRxOff == false)\n");
		MACbSafeSoftwareReset(priv);
		वापस false;
	पूर्ण
	अगर (!MACbSafeTxOff(priv)) अणु
		pr_debug(" MACbSafeTxOff == false)\n");
		MACbSafeSoftwareReset(priv);
		वापस false;
	पूर्ण

	MACvRegBitsOff(io_base, MAC_REG_HOSTCR, HOSTCR_MACEN);

	वापस true;
पूर्ण

/*
 * Description:
 *      Shut Down MAC
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *  Out:
 *      none
 *
 * Return Value: true अगर success; otherwise false
 *
 */
bool MACbShutकरोwn(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	/* disable MAC IMR */
	MACvIntDisable(io_base);
	MACvSetLoopbackMode(priv, MAC_LB_INTERNAL);
	/* stop the adapter */
	अगर (!MACbSafeStop(priv)) अणु
		MACvSetLoopbackMode(priv, MAC_LB_NONE);
		वापस false;
	पूर्ण
	MACvSetLoopbackMode(priv, MAC_LB_NONE);
	वापस true;
पूर्ण

/*
 * Description:
 *      Initialize MAC
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvInitialize(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	/* clear sticky bits */
	MACvClearStckDS(io_base);
	/* disable क्रमce PME-enable */
	ioग_लिखो8(PME_OVR, io_base + MAC_REG_PMC1);
	/* only 3253 A */

	/* करो reset */
	MACbSoftwareReset(priv);

	/* reset TSF counter */
	ioग_लिखो8(TFTCTL_TSFCNTRST, io_base + MAC_REG_TFTCTL);
	/* enable TSF counter */
	ioग_लिखो8(TFTCTL_TSFCNTREN, io_base + MAC_REG_TFTCTL);
पूर्ण

/*
 * Description:
 *      Set the chip with current rx descriptor address
 *
 * Parameters:
 *  In:
 *      io_base        - Base Address क्रम MAC
 *      curr_desc_addr  - Descriptor Address
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvSetCurrRx0DescAddr(काष्ठा vnt_निजी *priv, u32 curr_desc_addr)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित लघु ww;
	अचिन्हित अक्षर org_dma_ctl;

	org_dma_ctl = ioपढ़ो8(io_base + MAC_REG_RXDMACTL0);
	अगर (org_dma_ctl & DMACTL_RUN)
		ioग_लिखो8(DMACTL_RUN, io_base + MAC_REG_RXDMACTL0 + 2);

	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो8(io_base + MAC_REG_RXDMACTL0) & DMACTL_RUN))
			अवरोध;
	पूर्ण

	ioग_लिखो32(curr_desc_addr, io_base + MAC_REG_RXDMAPTR0);
	अगर (org_dma_ctl & DMACTL_RUN)
		ioग_लिखो8(DMACTL_RUN, io_base + MAC_REG_RXDMACTL0);
पूर्ण

/*
 * Description:
 *      Set the chip with current rx descriptor address
 *
 * Parameters:
 *  In:
 *      io_base        - Base Address क्रम MAC
 *      curr_desc_addr  - Descriptor Address
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvSetCurrRx1DescAddr(काष्ठा vnt_निजी *priv, u32 curr_desc_addr)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित लघु ww;
	अचिन्हित अक्षर org_dma_ctl;

	org_dma_ctl = ioपढ़ो8(io_base + MAC_REG_RXDMACTL1);
	अगर (org_dma_ctl & DMACTL_RUN)
		ioग_लिखो8(DMACTL_RUN, io_base + MAC_REG_RXDMACTL1 + 2);

	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो8(io_base + MAC_REG_RXDMACTL1) & DMACTL_RUN))
			अवरोध;
	पूर्ण

	ioग_लिखो32(curr_desc_addr, io_base + MAC_REG_RXDMAPTR1);
	अगर (org_dma_ctl & DMACTL_RUN)
		ioग_लिखो8(DMACTL_RUN, io_base + MAC_REG_RXDMACTL1);
पूर्ण

/*
 * Description:
 *      Set the chip with current tx0 descriptor address
 *
 * Parameters:
 *  In:
 *      io_base        - Base Address क्रम MAC
 *      curr_desc_addr  - Descriptor Address
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvSetCurrTx0DescAddrEx(काष्ठा vnt_निजी *priv,
			      u32 curr_desc_addr)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित लघु ww;
	अचिन्हित अक्षर org_dma_ctl;

	org_dma_ctl = ioपढ़ो8(io_base + MAC_REG_TXDMACTL0);
	अगर (org_dma_ctl & DMACTL_RUN)
		ioग_लिखो8(DMACTL_RUN, io_base + MAC_REG_TXDMACTL0 + 2);

	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो8(io_base + MAC_REG_TXDMACTL0) & DMACTL_RUN))
			अवरोध;
	पूर्ण

	ioग_लिखो32(curr_desc_addr, io_base + MAC_REG_TXDMAPTR0);
	अगर (org_dma_ctl & DMACTL_RUN)
		ioग_लिखो8(DMACTL_RUN, io_base + MAC_REG_TXDMACTL0);
पूर्ण

/*
 * Description:
 *      Set the chip with current AC0 descriptor address
 *
 * Parameters:
 *  In:
 *      io_base        - Base Address क्रम MAC
 *      curr_desc_addr  - Descriptor Address
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
/* TxDMA1 = AC0DMA */
व्योम MACvSetCurrAC0DescAddrEx(काष्ठा vnt_निजी *priv,
			      u32 curr_desc_addr)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित लघु ww;
	अचिन्हित अक्षर org_dma_ctl;

	org_dma_ctl = ioपढ़ो8(io_base + MAC_REG_AC0DMACTL);
	अगर (org_dma_ctl & DMACTL_RUN)
		ioग_लिखो8(DMACTL_RUN, io_base + MAC_REG_AC0DMACTL + 2);

	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (!(ioपढ़ो8(io_base + MAC_REG_AC0DMACTL) & DMACTL_RUN))
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT)
		pr_debug(" DBG_PORT80(0x26)\n");
	ioग_लिखो32(curr_desc_addr, io_base + MAC_REG_AC0DMAPTR);
	अगर (org_dma_ctl & DMACTL_RUN)
		ioग_लिखो8(DMACTL_RUN, io_base + MAC_REG_AC0DMACTL);
पूर्ण

व्योम MACvSetCurrTXDescAddr(पूर्णांक iTxType, काष्ठा vnt_निजी *priv,
			   u32 curr_desc_addr)
अणु
	अगर (iTxType == TYPE_AC0DMA)
		MACvSetCurrAC0DescAddrEx(priv, curr_desc_addr);
	अन्यथा अगर (iTxType == TYPE_TXDMA0)
		MACvSetCurrTx0DescAddrEx(priv, curr_desc_addr);
पूर्ण

/*
 * Description:
 *      Micro Second Delay via MAC
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *      uDelay      - Delay समय (समयr resolution is 4 us)
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvTimer0MicroSDelay(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक uDelay)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित अक्षर byValue;
	अचिन्हित पूर्णांक uu, ii;

	ioग_लिखो8(0, io_base + MAC_REG_TMCTL0);
	ioग_लिखो32(uDelay, io_base + MAC_REG_TMDATA0);
	ioग_लिखो8((TMCTL_TMD | TMCTL_TE), io_base + MAC_REG_TMCTL0);
	क्रम (ii = 0; ii < 66; ii++) अणु  /* assume max PCI घड़ी is 66Mhz */
		क्रम (uu = 0; uu < uDelay; uu++) अणु
			byValue = ioपढ़ो8(io_base + MAC_REG_TMCTL0);
			अगर ((byValue == 0) ||
			    (byValue & TMCTL_TSUSP)) अणु
				ioग_लिखो8(0, io_base + MAC_REG_TMCTL0);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	ioग_लिखो8(0, io_base + MAC_REG_TMCTL0);
पूर्ण

/*
 * Description:
 *      Micro Second One shot समयr via MAC
 *
 * Parameters:
 *  In:
 *      io_base    - Base Address क्रम MAC
 *      uDelay      - Delay समय
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvOneShotTimer1MicroSec(काष्ठा vnt_निजी *priv,
			       अचिन्हित पूर्णांक uDelayTime)
अणु
	व्योम __iomem *io_base = priv->PortOffset;

	ioग_लिखो8(0, io_base + MAC_REG_TMCTL1);
	ioग_लिखो32(uDelayTime, io_base + MAC_REG_TMDATA1);
	ioग_लिखो8((TMCTL_TMD | TMCTL_TE), io_base + MAC_REG_TMCTL1);
पूर्ण

व्योम MACvSetMISCFअगरo(काष्ठा vnt_निजी *priv, अचिन्हित लघु offset,
		     u32 data)
अणु
	व्योम __iomem *io_base = priv->PortOffset;

	अगर (offset > 273)
		वापस;
	ioग_लिखो16(offset, io_base + MAC_REG_MISCFFNDEX);
	ioग_लिखो32(data, io_base + MAC_REG_MISCFFDATA);
	ioग_लिखो16(MISCFFCTL_WRITE, io_base + MAC_REG_MISCFFCTL);
पूर्ण

bool MACbPSWakeup(काष्ठा vnt_निजी *priv)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित पूर्णांक ww;
	/* Read PSCTL */
	अगर (MACbIsRegBitsOff(priv, MAC_REG_PSCTL, PSCTL_PS))
		वापस true;

	/* Disable PS */
	MACvRegBitsOff(io_base, MAC_REG_PSCTL, PSCTL_PSEN);

	/* Check अगर SyncFlushOK */
	क्रम (ww = 0; ww < W_MAX_TIMEOUT; ww++) अणु
		अगर (ioपढ़ो8(io_base + MAC_REG_PSCTL) & PSCTL_WAKEDONE)
			अवरोध;
	पूर्ण
	अगर (ww == W_MAX_TIMEOUT) अणु
		pr_debug(" DBG_PORT80(0x33)\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Description:
 *      Set the Key by MISCFIFO
 *
 * Parameters:
 *  In:
 *      io_base        - Base Address क्रम MAC
 *
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */

व्योम MACvSetKeyEntry(काष्ठा vnt_निजी *priv, अचिन्हित लघु wKeyCtl,
		     अचिन्हित पूर्णांक uEntryIdx, अचिन्हित पूर्णांक uKeyIdx,
		     अचिन्हित अक्षर *pbyAddr, u32 *pdwKey,
		     अचिन्हित अक्षर byLocalID)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित लघु offset;
	u32 data;
	पूर्णांक     ii;

	अगर (byLocalID <= 1)
		वापस;

	pr_debug("%s\n", __func__);
	offset = MISCFIFO_KEYETRY0;
	offset += (uEntryIdx * MISCFIFO_KEYENTRYSIZE);

	data = 0;
	data |= wKeyCtl;
	data <<= 16;
	data |= MAKEWORD(*(pbyAddr + 4), *(pbyAddr + 5));
	pr_debug("1. offset: %d, Data: %X, KeyCtl:%X\n",
		 offset, data, wKeyCtl);

	ioग_लिखो16(offset, io_base + MAC_REG_MISCFFNDEX);
	ioग_लिखो32(data, io_base + MAC_REG_MISCFFDATA);
	ioग_लिखो16(MISCFFCTL_WRITE, io_base + MAC_REG_MISCFFCTL);
	offset++;

	data = 0;
	data |= *(pbyAddr + 3);
	data <<= 8;
	data |= *(pbyAddr + 2);
	data <<= 8;
	data |= *(pbyAddr + 1);
	data <<= 8;
	data |= *pbyAddr;
	pr_debug("2. offset: %d, Data: %X\n", offset, data);

	ioग_लिखो16(offset, io_base + MAC_REG_MISCFFNDEX);
	ioग_लिखो32(data, io_base + MAC_REG_MISCFFDATA);
	ioग_लिखो16(MISCFFCTL_WRITE, io_base + MAC_REG_MISCFFCTL);
	offset++;

	offset += (uKeyIdx * 4);
	क्रम (ii = 0; ii < 4; ii++) अणु
		/* always push 128 bits */
		pr_debug("3.(%d) offset: %d, Data: %X\n",
			 ii, offset + ii, *pdwKey);
		ioग_लिखो16(offset + ii, io_base + MAC_REG_MISCFFNDEX);
		ioग_लिखो32(*pdwKey++, io_base + MAC_REG_MISCFFDATA);
		ioग_लिखो16(MISCFFCTL_WRITE, io_base + MAC_REG_MISCFFCTL);
	पूर्ण
पूर्ण

/*
 * Description:
 *      Disable the Key Entry by MISCFIFO
 *
 * Parameters:
 *  In:
 *      io_base        - Base Address क्रम MAC
 *
 *  Out:
 *      none
 *
 * Return Value: none
 *
 */
व्योम MACvDisableKeyEntry(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक uEntryIdx)
अणु
	व्योम __iomem *io_base = priv->PortOffset;
	अचिन्हित लघु offset;

	offset = MISCFIFO_KEYETRY0;
	offset += (uEntryIdx * MISCFIFO_KEYENTRYSIZE);

	ioग_लिखो16(offset, io_base + MAC_REG_MISCFFNDEX);
	ioग_लिखो32(0, io_base + MAC_REG_MISCFFDATA);
	ioग_लिखो16(MISCFFCTL_WRITE, io_base + MAC_REG_MISCFFCTL);
पूर्ण
