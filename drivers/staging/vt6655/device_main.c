<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: device_मुख्य.c
 *
 * Purpose: driver entry क्रम initial, खोलो, बंद, tx and rx.
 *
 * Author: Lynकरोn Chen
 *
 * Date: Jan 8, 2003
 *
 * Functions:
 *
 *   vt6655_probe - module initial (insmod) driver entry
 *   vt6655_हटाओ - module हटाओ entry
 *   device_मुक्त_info - device काष्ठाure resource मुक्त function
 *   device_prपूर्णांक_info - prपूर्णांक out resource
 *   device_rx_srv - rx service function
 *   device_alloc_rx_buf - rx buffer pre-allocated function
 *   device_मुक्त_rx_buf - मुक्त rx buffer function
 *   device_मुक्त_tx_buf - मुक्त tx buffer function
 *   device_init_rd0_ring - initial rd dma0 ring
 *   device_init_rd1_ring - initial rd dma1 ring
 *   device_init_td0_ring - initial tx dma0 ring buffer
 *   device_init_td1_ring - initial tx dma1 ring buffer
 *   device_init_रेजिस्टरs - initial MAC & BBP & RF पूर्णांकernal रेजिस्टरs.
 *   device_init_rings - initial tx/rx ring buffer
 *   device_मुक्त_rings - मुक्त all allocated ring buffer
 *   device_tx_srv - tx पूर्णांकerrupt service function
 *
 * Revision History:
 */

#समावेश <linux/file.h>
#समावेश "device.h"
#समावेश "card.h"
#समावेश "channel.h"
#समावेश "baseband.h"
#समावेश "mac.h"
#समावेश "power.h"
#समावेश "rxtx.h"
#समावेश "dpc.h"
#समावेश "rf.h"
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>

/*---------------------  Static Definitions -------------------------*/
/*
 * Define module options
 */
MODULE_AUTHOR("VIA Networking Technologies, Inc., <lyndonchen@vntek.com.tw>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("VIA Networking Solomon-A/B/G Wireless LAN Adapter Driver");

#घोषणा DEVICE_PARAM(N, D)

#घोषणा RX_DESC_MIN0     16
#घोषणा RX_DESC_MAX0     128
#घोषणा RX_DESC_DEF0     32
DEVICE_PARAM(RxDescriptors0, "Number of receive descriptors0");

#घोषणा RX_DESC_MIN1     16
#घोषणा RX_DESC_MAX1     128
#घोषणा RX_DESC_DEF1     32
DEVICE_PARAM(RxDescriptors1, "Number of receive descriptors1");

#घोषणा TX_DESC_MIN0     16
#घोषणा TX_DESC_MAX0     128
#घोषणा TX_DESC_DEF0     32
DEVICE_PARAM(TxDescriptors0, "Number of transmit descriptors0");

#घोषणा TX_DESC_MIN1     16
#घोषणा TX_DESC_MAX1     128
#घोषणा TX_DESC_DEF1     64
DEVICE_PARAM(TxDescriptors1, "Number of transmit descriptors1");

#घोषणा INT_WORKS_DEF   20
#घोषणा INT_WORKS_MIN   10
#घोषणा INT_WORKS_MAX   64

DEVICE_PARAM(पूर्णांक_works, "Number of packets per interrupt services");

#घोषणा RTS_THRESH_DEF     2347

#घोषणा FRAG_THRESH_DEF     2346

#घोषणा SHORT_RETRY_MIN     0
#घोषणा SHORT_RETRY_MAX     31
#घोषणा SHORT_RETRY_DEF     8

DEVICE_PARAM(ShortRetryLimit, "Short frame retry limits");

#घोषणा LONG_RETRY_MIN     0
#घोषणा LONG_RETRY_MAX     15
#घोषणा LONG_RETRY_DEF     4

DEVICE_PARAM(LongRetryLimit, "long frame retry limits");

/* BasebandType[] baseband type selected
 * 0: indicate 802.11a type
 * 1: indicate 802.11b type
 * 2: indicate 802.11g type
 */
#घोषणा BBP_TYPE_MIN     0
#घोषणा BBP_TYPE_MAX     2
#घोषणा BBP_TYPE_DEF     2

DEVICE_PARAM(BasebandType, "baseband type");

/*
 * Static vars definitions
 */
अटल स्थिर काष्ठा pci_device_id vt6655_pci_id_table[] = अणु
	अणु PCI_VDEVICE(VIA, 0x3253) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

/*---------------------  Static Functions  --------------------------*/

अटल पूर्णांक  vt6655_probe(काष्ठा pci_dev *pcid, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम device_मुक्त_info(काष्ठा vnt_निजी *priv);
अटल व्योम device_prपूर्णांक_info(काष्ठा vnt_निजी *priv);

अटल पूर्णांक device_init_rd0_ring(काष्ठा vnt_निजी *priv);
अटल पूर्णांक device_init_rd1_ring(काष्ठा vnt_निजी *priv);
अटल पूर्णांक device_init_td0_ring(काष्ठा vnt_निजी *priv);
अटल पूर्णांक device_init_td1_ring(काष्ठा vnt_निजी *priv);

अटल पूर्णांक  device_rx_srv(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक idx);
अटल पूर्णांक  device_tx_srv(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक idx);
अटल bool device_alloc_rx_buf(काष्ठा vnt_निजी *, काष्ठा vnt_rx_desc *);
अटल व्योम device_मुक्त_rx_buf(काष्ठा vnt_निजी *priv,
			       काष्ठा vnt_rx_desc *rd);
अटल व्योम device_init_रेजिस्टरs(काष्ठा vnt_निजी *priv);
अटल व्योम device_मुक्त_tx_buf(काष्ठा vnt_निजी *, काष्ठा vnt_tx_desc *);
अटल व्योम device_मुक्त_td0_ring(काष्ठा vnt_निजी *priv);
अटल व्योम device_मुक्त_td1_ring(काष्ठा vnt_निजी *priv);
अटल व्योम device_मुक्त_rd0_ring(काष्ठा vnt_निजी *priv);
अटल व्योम device_मुक्त_rd1_ring(काष्ठा vnt_निजी *priv);
अटल व्योम device_मुक्त_rings(काष्ठा vnt_निजी *priv);

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

अटल व्योम vt6655_हटाओ(काष्ठा pci_dev *pcid)
अणु
	काष्ठा vnt_निजी *priv = pci_get_drvdata(pcid);

	अगर (!priv)
		वापस;
	device_मुक्त_info(priv);
पूर्ण

अटल व्योम device_get_options(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा vnt_options *opts = &priv->opts;

	opts->rx_descs0 = RX_DESC_DEF0;
	opts->rx_descs1 = RX_DESC_DEF1;
	opts->tx_descs[0] = TX_DESC_DEF0;
	opts->tx_descs[1] = TX_DESC_DEF1;
	opts->पूर्णांक_works = INT_WORKS_DEF;

	opts->लघु_retry = SHORT_RETRY_DEF;
	opts->दीर्घ_retry = LONG_RETRY_DEF;
	opts->bbp_type = BBP_TYPE_DEF;
पूर्ण

अटल व्योम
device_set_options(काष्ठा vnt_निजी *priv)
अणु
	priv->byShortRetryLimit = priv->opts.लघु_retry;
	priv->byLongRetryLimit = priv->opts.दीर्घ_retry;
	priv->byBBType = priv->opts.bbp_type;
	priv->byPacketType = priv->byBBType;
	priv->byAutoFBCtrl = AUTO_FB_0;
	priv->bUpdateBBVGA = true;
	priv->byPreambleType = 0;

	pr_debug(" byShortRetryLimit= %d\n", (पूर्णांक)priv->byShortRetryLimit);
	pr_debug(" byLongRetryLimit= %d\n", (पूर्णांक)priv->byLongRetryLimit);
	pr_debug(" byPreambleType= %d\n", (पूर्णांक)priv->byPreambleType);
	pr_debug(" byShortPreamble= %d\n", (पूर्णांक)priv->byShortPreamble);
	pr_debug(" byBBType= %d\n", (पूर्णांक)priv->byBBType);
पूर्ण

/*
 * Initialisation of MAC & BBP रेजिस्टरs
 */

अटल व्योम device_init_रेजिस्टरs(काष्ठा vnt_निजी *priv)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ii;
	अचिन्हित अक्षर byValue;
	अचिन्हित अक्षर byCCKPwrdBm = 0;
	अचिन्हित अक्षर byOFDMPwrdBm = 0;

	MACbShutकरोwn(priv);
	bb_software_reset(priv);

	/* Do MACbSoftwareReset in MACvInitialize */
	MACbSoftwareReset(priv);

	priv->bAES = false;

	/* Only used in 11g type, sync with ERP IE */
	priv->bProtectMode = false;

	priv->bNonERPPresent = false;
	priv->bBarkerPreambleMd = false;
	priv->wCurrentRate = RATE_1M;
	priv->byTopOFDMBasicRate = RATE_24M;
	priv->byTopCCKBasicRate = RATE_1M;

	/* init MAC */
	MACvInitialize(priv);

	/* Get Local ID */
	VNSvInPortB(priv->PortOffset + MAC_REG_LOCALID, &priv->byLocalID);

	spin_lock_irqsave(&priv->lock, flags);

	SROMvReadAllContents(priv->PortOffset, priv->abyEEPROM);

	spin_unlock_irqrestore(&priv->lock, flags);

	/* Get Channel range */
	priv->byMinChannel = 1;
	priv->byMaxChannel = CB_MAX_CHANNEL;

	/* Get Antena */
	byValue = SROMbyReadEmbedded(priv->PortOffset, EEP_OFS_ANTENNA);
	अगर (byValue & EEP_ANTINV)
		priv->bTxRxAntInv = true;
	अन्यथा
		priv->bTxRxAntInv = false;

	byValue &= (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);
	/* अगर not set शेष is All */
	अगर (byValue == 0)
		byValue = (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN);

	अगर (byValue == (EEP_ANTENNA_AUX | EEP_ANTENNA_MAIN)) अणु
		priv->byAntennaCount = 2;
		priv->byTxAntennaMode = ANT_B;
		priv->dwTxAntennaSel = 1;
		priv->dwRxAntennaSel = 1;

		अगर (priv->bTxRxAntInv)
			priv->byRxAntennaMode = ANT_A;
		अन्यथा
			priv->byRxAntennaMode = ANT_B;
	पूर्ण अन्यथा  अणु
		priv->byAntennaCount = 1;
		priv->dwTxAntennaSel = 0;
		priv->dwRxAntennaSel = 0;

		अगर (byValue & EEP_ANTENNA_AUX) अणु
			priv->byTxAntennaMode = ANT_A;

			अगर (priv->bTxRxAntInv)
				priv->byRxAntennaMode = ANT_B;
			अन्यथा
				priv->byRxAntennaMode = ANT_A;
		पूर्ण अन्यथा अणु
			priv->byTxAntennaMode = ANT_B;

			अगर (priv->bTxRxAntInv)
				priv->byRxAntennaMode = ANT_A;
			अन्यथा
				priv->byRxAntennaMode = ANT_B;
		पूर्ण
	पूर्ण

	/* Set initial antenna mode */
	bb_set_tx_antenna_mode(priv, priv->byTxAntennaMode);
	bb_set_rx_antenna_mode(priv, priv->byRxAntennaMode);

	/* zonetype initial */
	priv->byOriginalZonetype = priv->abyEEPROM[EEP_OFS_ZONETYPE];

	अगर (!priv->bZoneRegExist)
		priv->byZoneType = priv->abyEEPROM[EEP_OFS_ZONETYPE];

	pr_debug("priv->byZoneType = %x\n", priv->byZoneType);

	/* Init RF module */
	RFbInit(priv);

	/* Get Desire Power Value */
	priv->byCurPwr = 0xFF;
	priv->byCCKPwr = SROMbyReadEmbedded(priv->PortOffset, EEP_OFS_PWR_CCK);
	priv->byOFDMPwrG = SROMbyReadEmbedded(priv->PortOffset,
					      EEP_OFS_PWR_OFDMG);

	/* Load घातer Table */
	क्रम (ii = 0; ii < CB_MAX_CHANNEL_24G; ii++) अणु
		priv->abyCCKPwrTbl[ii + 1] =
			SROMbyReadEmbedded(priv->PortOffset,
					   (अचिन्हित अक्षर)(ii + EEP_OFS_CCK_PWR_TBL));
		अगर (priv->abyCCKPwrTbl[ii + 1] == 0)
			priv->abyCCKPwrTbl[ii + 1] = priv->byCCKPwr;

		priv->abyOFDMPwrTbl[ii + 1] =
			SROMbyReadEmbedded(priv->PortOffset,
					   (अचिन्हित अक्षर)(ii + EEP_OFS_OFDM_PWR_TBL));
		अगर (priv->abyOFDMPwrTbl[ii + 1] == 0)
			priv->abyOFDMPwrTbl[ii + 1] = priv->byOFDMPwrG;

		priv->abyCCKDefaultPwr[ii + 1] = byCCKPwrdBm;
		priv->abyOFDMDefaultPwr[ii + 1] = byOFDMPwrdBm;
	पूर्ण

	/* recover 12,13 ,14channel क्रम EUROPE by 11 channel */
	क्रम (ii = 11; ii < 14; ii++) अणु
		priv->abyCCKPwrTbl[ii] = priv->abyCCKPwrTbl[10];
		priv->abyOFDMPwrTbl[ii] = priv->abyOFDMPwrTbl[10];
	पूर्ण

	/* Load OFDM A Power Table */
	क्रम (ii = 0; ii < CB_MAX_CHANNEL_5G; ii++) अणु
		priv->abyOFDMPwrTbl[ii + CB_MAX_CHANNEL_24G + 1] =
			SROMbyReadEmbedded(priv->PortOffset,
					   (अचिन्हित अक्षर)(ii + EEP_OFS_OFDMA_PWR_TBL));

		priv->abyOFDMDefaultPwr[ii + CB_MAX_CHANNEL_24G + 1] =
			SROMbyReadEmbedded(priv->PortOffset,
					   (अचिन्हित अक्षर)(ii + EEP_OFS_OFDMA_PWR_dBm));
	पूर्ण

	अगर (priv->byLocalID > REV_ID_VT3253_B1) अणु
		MACvSelectPage1(priv->PortOffset);

		VNSvOutPortB(priv->PortOffset + MAC_REG_MSRCTL + 1,
			     (MSRCTL1_TXPWR | MSRCTL1_CSAPAREN));

		MACvSelectPage0(priv->PortOffset);
	पूर्ण

	/* use relative tx समयout and 802.11i D4 */
	MACvWordRegBitsOn(priv->PortOffset,
			  MAC_REG_CFG, (CFG_TKIPOPT | CFG_NOTXTIMEOUT));

	/* set perक्रमmance parameter by registry */
	MACvSetShortRetryLimit(priv, priv->byShortRetryLimit);
	MACvSetLongRetryLimit(priv, priv->byLongRetryLimit);

	/* reset TSF counter */
	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTRST);
	/* enable TSF counter */
	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);

	/* initialize BBP रेजिस्टरs */
	bb_vt3253_init(priv);

	अगर (priv->bUpdateBBVGA) अणु
		priv->byBBVGACurrent = priv->abyBBVGA[0];
		priv->byBBVGANew = priv->byBBVGACurrent;
		bb_set_vga_gain_offset(priv, priv->abyBBVGA[0]);
	पूर्ण

	bb_set_rx_antenna_mode(priv, priv->byRxAntennaMode);
	bb_set_tx_antenna_mode(priv, priv->byTxAntennaMode);

	/* Set BB and packet type at the same समय. */
	/* Set Short Slot Time, xIFS, and RSPINF. */
	priv->wCurrentRate = RATE_54M;

	priv->bRadioOff = false;

	priv->byRadioCtl = SROMbyReadEmbedded(priv->PortOffset,
					      EEP_OFS_RADIOCTL);
	priv->bHWRadioOff = false;

	अगर (priv->byRadioCtl & EEP_RADIOCTL_ENABLE) अणु
		/* Get GPIO */
		MACvGPIOIn(priv->PortOffset, &priv->byGPIO);

		अगर (((priv->byGPIO & GPIO0_DATA) &&
		     !(priv->byRadioCtl & EEP_RADIOCTL_INV)) ||
		     (!(priv->byGPIO & GPIO0_DATA) &&
		     (priv->byRadioCtl & EEP_RADIOCTL_INV)))
			priv->bHWRadioOff = true;
	पूर्ण

	अगर (priv->bHWRadioOff || priv->bRadioControlOff)
		CARDbRadioPowerOff(priv);

	/* get Permanent network address */
	SROMvReadEtherAddress(priv->PortOffset, priv->abyCurrentNetAddr);
	pr_debug("Network address = %pM\n", priv->abyCurrentNetAddr);

	/* reset Tx poपूर्णांकer */
	CARDvSafeResetRx(priv);
	/* reset Rx poपूर्णांकer */
	CARDvSafeResetTx(priv);

	अगर (priv->byLocalID <= REV_ID_VT3253_A1)
		MACvRegBitsOn(priv->PortOffset, MAC_REG_RCR, RCR_WPAERR);

	/* Turn On Rx DMA */
	MACvReceive0(priv->PortOffset);
	MACvReceive1(priv->PortOffset);

	/* start the adapter */
	MACvStart(priv->PortOffset);
पूर्ण

अटल व्योम device_prपूर्णांक_info(काष्ठा vnt_निजी *priv)
अणु
	dev_info(&priv->pcid->dev, "MAC=%pM IO=0x%lx Mem=0x%lx IRQ=%d\n",
		 priv->abyCurrentNetAddr, (अचिन्हित दीर्घ)priv->ioaddr,
		 (अचिन्हित दीर्घ)priv->PortOffset, priv->pcid->irq);
पूर्ण

अटल व्योम device_मुक्त_info(काष्ठा vnt_निजी *priv)
अणु
	अगर (!priv)
		वापस;

	अगर (priv->mac_hw)
		ieee80211_unरेजिस्टर_hw(priv->hw);

	अगर (priv->PortOffset)
		iounmap(priv->PortOffset);

	अगर (priv->pcid)
		pci_release_regions(priv->pcid);

	अगर (priv->hw)
		ieee80211_मुक्त_hw(priv->hw);
पूर्ण

अटल bool device_init_rings(काष्ठा vnt_निजी *priv)
अणु
	व्योम *vir_pool;

	/*allocate all RD/TD rings a single pool*/
	vir_pool = dma_alloc_coherent(&priv->pcid->dev,
				      priv->opts.rx_descs0 * माप(काष्ठा vnt_rx_desc) +
				      priv->opts.rx_descs1 * माप(काष्ठा vnt_rx_desc) +
				      priv->opts.tx_descs[0] * माप(काष्ठा vnt_tx_desc) +
				      priv->opts.tx_descs[1] * माप(काष्ठा vnt_tx_desc),
				      &priv->pool_dma, GFP_ATOMIC);
	अगर (!vir_pool) अणु
		dev_err(&priv->pcid->dev, "allocate desc dma memory failed\n");
		वापस false;
	पूर्ण

	priv->aRD0Ring = vir_pool;
	priv->aRD1Ring = vir_pool +
		priv->opts.rx_descs0 * माप(काष्ठा vnt_rx_desc);

	priv->rd0_pool_dma = priv->pool_dma;
	priv->rd1_pool_dma = priv->rd0_pool_dma +
		priv->opts.rx_descs0 * माप(काष्ठा vnt_rx_desc);

	priv->tx0_bufs = dma_alloc_coherent(&priv->pcid->dev,
					    priv->opts.tx_descs[0] * PKT_BUF_SZ +
					    priv->opts.tx_descs[1] * PKT_BUF_SZ +
					    CB_BEACON_BUF_SIZE +
					    CB_MAX_BUF_SIZE,
					    &priv->tx_bufs_dma0, GFP_ATOMIC);
	अगर (!priv->tx0_bufs) अणु
		dev_err(&priv->pcid->dev, "allocate buf dma memory failed\n");

		dma_मुक्त_coherent(&priv->pcid->dev,
				  priv->opts.rx_descs0 * माप(काष्ठा vnt_rx_desc) +
				  priv->opts.rx_descs1 * माप(काष्ठा vnt_rx_desc) +
				  priv->opts.tx_descs[0] * माप(काष्ठा vnt_tx_desc) +
				  priv->opts.tx_descs[1] * माप(काष्ठा vnt_tx_desc),
				  vir_pool, priv->pool_dma);
		वापस false;
	पूर्ण

	priv->td0_pool_dma = priv->rd1_pool_dma +
		priv->opts.rx_descs1 * माप(काष्ठा vnt_rx_desc);

	priv->td1_pool_dma = priv->td0_pool_dma +
		priv->opts.tx_descs[0] * माप(काष्ठा vnt_tx_desc);

	/* vir_pool: pव्योम type */
	priv->apTD0Rings = vir_pool
		+ priv->opts.rx_descs0 * माप(काष्ठा vnt_rx_desc)
		+ priv->opts.rx_descs1 * माप(काष्ठा vnt_rx_desc);

	priv->apTD1Rings = vir_pool
		+ priv->opts.rx_descs0 * माप(काष्ठा vnt_rx_desc)
		+ priv->opts.rx_descs1 * माप(काष्ठा vnt_rx_desc)
		+ priv->opts.tx_descs[0] * माप(काष्ठा vnt_tx_desc);

	priv->tx1_bufs = priv->tx0_bufs +
		priv->opts.tx_descs[0] * PKT_BUF_SZ;

	priv->tx_beacon_bufs = priv->tx1_bufs +
		priv->opts.tx_descs[1] * PKT_BUF_SZ;

	priv->pbyTmpBuff = priv->tx_beacon_bufs +
		CB_BEACON_BUF_SIZE;

	priv->tx_bufs_dma1 = priv->tx_bufs_dma0 +
		priv->opts.tx_descs[0] * PKT_BUF_SZ;

	priv->tx_beacon_dma = priv->tx_bufs_dma1 +
		priv->opts.tx_descs[1] * PKT_BUF_SZ;

	वापस true;
पूर्ण

अटल व्योम device_मुक्त_rings(काष्ठा vnt_निजी *priv)
अणु
	dma_मुक्त_coherent(&priv->pcid->dev,
			  priv->opts.rx_descs0 * माप(काष्ठा vnt_rx_desc) +
			  priv->opts.rx_descs1 * माप(काष्ठा vnt_rx_desc) +
			  priv->opts.tx_descs[0] * माप(काष्ठा vnt_tx_desc) +
			  priv->opts.tx_descs[1] * माप(काष्ठा vnt_tx_desc),
			  priv->aRD0Ring, priv->pool_dma);

	अगर (priv->tx0_bufs)
		dma_मुक्त_coherent(&priv->pcid->dev,
				  priv->opts.tx_descs[0] * PKT_BUF_SZ +
				  priv->opts.tx_descs[1] * PKT_BUF_SZ +
				  CB_BEACON_BUF_SIZE +
				  CB_MAX_BUF_SIZE,
				  priv->tx0_bufs, priv->tx_bufs_dma0);
पूर्ण

अटल पूर्णांक device_init_rd0_ring(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक i;
	dma_addr_t      curr = priv->rd0_pool_dma;
	काष्ठा vnt_rx_desc *desc;
	पूर्णांक ret;

	/* Init the RD0 ring entries */
	क्रम (i = 0; i < priv->opts.rx_descs0;
	     i ++, curr += माप(काष्ठा vnt_rx_desc)) अणु
		desc = &priv->aRD0Ring[i];
		desc->rd_info = kzalloc(माप(*desc->rd_info), GFP_KERNEL);
		अगर (!desc->rd_info) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_desc;
		पूर्ण

		अगर (!device_alloc_rx_buf(priv, desc)) अणु
			dev_err(&priv->pcid->dev, "can not alloc rx bufs\n");
			ret = -ENOMEM;
			जाओ err_मुक्त_rd;
		पूर्ण

		desc->next = &priv->aRD0Ring[(i + 1) % priv->opts.rx_descs0];
		desc->next_desc = cpu_to_le32(curr + माप(काष्ठा vnt_rx_desc));
	पूर्ण

	अगर (i > 0)
		priv->aRD0Ring[i - 1].next_desc = cpu_to_le32(priv->rd0_pool_dma);
	priv->pCurrRD[0] = &priv->aRD0Ring[0];

	वापस 0;

err_मुक्त_rd:
	kमुक्त(desc->rd_info);

err_मुक्त_desc:
	जबतक (--i) अणु
		desc = &priv->aRD0Ring[i];
		device_मुक्त_rx_buf(priv, desc);
		kमुक्त(desc->rd_info);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक device_init_rd1_ring(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक i;
	dma_addr_t      curr = priv->rd1_pool_dma;
	काष्ठा vnt_rx_desc *desc;
	पूर्णांक ret;

	/* Init the RD1 ring entries */
	क्रम (i = 0; i < priv->opts.rx_descs1;
	     i ++, curr += माप(काष्ठा vnt_rx_desc)) अणु
		desc = &priv->aRD1Ring[i];
		desc->rd_info = kzalloc(माप(*desc->rd_info), GFP_KERNEL);
		अगर (!desc->rd_info) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_desc;
		पूर्ण

		अगर (!device_alloc_rx_buf(priv, desc)) अणु
			dev_err(&priv->pcid->dev, "can not alloc rx bufs\n");
			ret = -ENOMEM;
			जाओ err_मुक्त_rd;
		पूर्ण

		desc->next = &priv->aRD1Ring[(i + 1) % priv->opts.rx_descs1];
		desc->next_desc = cpu_to_le32(curr + माप(काष्ठा vnt_rx_desc));
	पूर्ण

	अगर (i > 0)
		priv->aRD1Ring[i - 1].next_desc = cpu_to_le32(priv->rd1_pool_dma);
	priv->pCurrRD[1] = &priv->aRD1Ring[0];

	वापस 0;

err_मुक्त_rd:
	kमुक्त(desc->rd_info);

err_मुक्त_desc:
	जबतक (--i) अणु
		desc = &priv->aRD1Ring[i];
		device_मुक्त_rx_buf(priv, desc);
		kमुक्त(desc->rd_info);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम device_मुक्त_rd0_ring(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->opts.rx_descs0; i++) अणु
		काष्ठा vnt_rx_desc *desc = &priv->aRD0Ring[i];

		device_मुक्त_rx_buf(priv, desc);
		kमुक्त(desc->rd_info);
	पूर्ण
पूर्ण

अटल व्योम device_मुक्त_rd1_ring(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->opts.rx_descs1; i++) अणु
		काष्ठा vnt_rx_desc *desc = &priv->aRD1Ring[i];

		device_मुक्त_rx_buf(priv, desc);
		kमुक्त(desc->rd_info);
	पूर्ण
पूर्ण

अटल पूर्णांक device_init_td0_ring(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक i;
	dma_addr_t  curr;
	काष्ठा vnt_tx_desc *desc;
	पूर्णांक ret;

	curr = priv->td0_pool_dma;
	क्रम (i = 0; i < priv->opts.tx_descs[0];
	     i++, curr += माप(काष्ठा vnt_tx_desc)) अणु
		desc = &priv->apTD0Rings[i];
		desc->td_info = kzalloc(माप(*desc->td_info), GFP_KERNEL);
		अगर (!desc->td_info) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_desc;
		पूर्ण

		desc->td_info->buf = priv->tx0_bufs + i * PKT_BUF_SZ;
		desc->td_info->buf_dma = priv->tx_bufs_dma0 + i * PKT_BUF_SZ;

		desc->next = &(priv->apTD0Rings[(i + 1) % priv->opts.tx_descs[0]]);
		desc->next_desc = cpu_to_le32(curr +
					      माप(काष्ठा vnt_tx_desc));
	पूर्ण

	अगर (i > 0)
		priv->apTD0Rings[i - 1].next_desc = cpu_to_le32(priv->td0_pool_dma);
	priv->apTailTD[0] = priv->apCurrTD[0] = &priv->apTD0Rings[0];

	वापस 0;

err_मुक्त_desc:
	जबतक (--i) अणु
		desc = &priv->apTD0Rings[i];
		kमुक्त(desc->td_info);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक device_init_td1_ring(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक i;
	dma_addr_t  curr;
	काष्ठा vnt_tx_desc *desc;
	पूर्णांक ret;

	/* Init the TD ring entries */
	curr = priv->td1_pool_dma;
	क्रम (i = 0; i < priv->opts.tx_descs[1];
	     i++, curr += माप(काष्ठा vnt_tx_desc)) अणु
		desc = &priv->apTD1Rings[i];
		desc->td_info = kzalloc(माप(*desc->td_info), GFP_KERNEL);
		अगर (!desc->td_info) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_desc;
		पूर्ण

		desc->td_info->buf = priv->tx1_bufs + i * PKT_BUF_SZ;
		desc->td_info->buf_dma = priv->tx_bufs_dma1 + i * PKT_BUF_SZ;

		desc->next = &(priv->apTD1Rings[(i + 1) % priv->opts.tx_descs[1]]);
		desc->next_desc = cpu_to_le32(curr + माप(काष्ठा vnt_tx_desc));
	पूर्ण

	अगर (i > 0)
		priv->apTD1Rings[i - 1].next_desc = cpu_to_le32(priv->td1_pool_dma);
	priv->apTailTD[1] = priv->apCurrTD[1] = &priv->apTD1Rings[0];

	वापस 0;

err_मुक्त_desc:
	जबतक (--i) अणु
		desc = &priv->apTD1Rings[i];
		kमुक्त(desc->td_info);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम device_मुक्त_td0_ring(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->opts.tx_descs[0]; i++) अणु
		काष्ठा vnt_tx_desc *desc = &priv->apTD0Rings[i];
		काष्ठा vnt_td_info *td_info = desc->td_info;

		dev_kमुक्त_skb(td_info->skb);
		kमुक्त(desc->td_info);
	पूर्ण
पूर्ण

अटल व्योम device_मुक्त_td1_ring(काष्ठा vnt_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->opts.tx_descs[1]; i++) अणु
		काष्ठा vnt_tx_desc *desc = &priv->apTD1Rings[i];
		काष्ठा vnt_td_info *td_info = desc->td_info;

		dev_kमुक्त_skb(td_info->skb);
		kमुक्त(desc->td_info);
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------*/

अटल पूर्णांक device_rx_srv(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा vnt_rx_desc *rd;
	पूर्णांक works = 0;

	क्रम (rd = priv->pCurrRD[idx];
	     rd->rd0.owner == OWNED_BY_HOST;
	     rd = rd->next) अणु
		अगर (works++ > 15)
			अवरोध;

		अगर (!rd->rd_info->skb)
			अवरोध;

		अगर (vnt_receive_frame(priv, rd)) अणु
			अगर (!device_alloc_rx_buf(priv, rd)) अणु
				dev_err(&priv->pcid->dev,
					"can not allocate rx buf\n");
				अवरोध;
			पूर्ण
		पूर्ण
		rd->rd0.owner = OWNED_BY_NIC;
	पूर्ण

	priv->pCurrRD[idx] = rd;

	वापस works;
पूर्ण

अटल bool device_alloc_rx_buf(काष्ठा vnt_निजी *priv,
				काष्ठा vnt_rx_desc *rd)
अणु
	काष्ठा vnt_rd_info *rd_info = rd->rd_info;

	rd_info->skb = dev_alloc_skb((पूर्णांक)priv->rx_buf_sz);
	अगर (!rd_info->skb)
		वापस false;

	rd_info->skb_dma =
		dma_map_single(&priv->pcid->dev,
			       skb_put(rd_info->skb, skb_tailroom(rd_info->skb)),
			       priv->rx_buf_sz, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&priv->pcid->dev, rd_info->skb_dma)) अणु
		dev_kमुक्त_skb(rd_info->skb);
		rd_info->skb = शून्य;
		वापस false;
	पूर्ण

	*((अचिन्हित पूर्णांक *)&rd->rd0) = 0; /* FIX cast */

	rd->rd0.res_count = cpu_to_le16(priv->rx_buf_sz);
	rd->rd0.owner = OWNED_BY_NIC;
	rd->rd1.req_count = cpu_to_le16(priv->rx_buf_sz);
	rd->buff_addr = cpu_to_le32(rd_info->skb_dma);

	वापस true;
पूर्ण

अटल व्योम device_मुक्त_rx_buf(काष्ठा vnt_निजी *priv,
			       काष्ठा vnt_rx_desc *rd)
अणु
	काष्ठा vnt_rd_info *rd_info = rd->rd_info;

	dma_unmap_single(&priv->pcid->dev, rd_info->skb_dma,
			 priv->rx_buf_sz, DMA_FROM_DEVICE);
	dev_kमुक्त_skb(rd_info->skb);
पूर्ण

अटल स्थिर u8 fallback_rate0[5][5] = अणु
	अणुRATE_18M, RATE_18M, RATE_12M, RATE_12M, RATE_12Mपूर्ण,
	अणुRATE_24M, RATE_24M, RATE_18M, RATE_12M, RATE_12Mपूर्ण,
	अणुRATE_36M, RATE_36M, RATE_24M, RATE_18M, RATE_18Mपूर्ण,
	अणुRATE_48M, RATE_48M, RATE_36M, RATE_24M, RATE_24Mपूर्ण,
	अणुRATE_54M, RATE_54M, RATE_48M, RATE_36M, RATE_36Mपूर्ण
पूर्ण;

अटल स्थिर u8 fallback_rate1[5][5] = अणु
	अणुRATE_18M, RATE_18M, RATE_12M, RATE_6M, RATE_6Mपूर्ण,
	अणुRATE_24M, RATE_24M, RATE_18M, RATE_6M, RATE_6Mपूर्ण,
	अणुRATE_36M, RATE_36M, RATE_24M, RATE_12M, RATE_12Mपूर्ण,
	अणुRATE_48M, RATE_48M, RATE_24M, RATE_12M, RATE_12Mपूर्ण,
	अणुRATE_54M, RATE_54M, RATE_36M, RATE_18M, RATE_18Mपूर्ण
पूर्ण;

अटल पूर्णांक vnt_पूर्णांक_report_rate(काष्ठा vnt_निजी *priv,
			       काष्ठा vnt_td_info *context, u8 tsr0, u8 tsr1)
अणु
	काष्ठा vnt_tx_fअगरo_head *fअगरo_head;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_rate *rate;
	u16 fb_option;
	u8 tx_retry = (tsr0 & TSR0_NCR);
	s8 idx;

	अगर (!context)
		वापस -ENOMEM;

	अगर (!context->skb)
		वापस -EINVAL;

	fअगरo_head = (काष्ठा vnt_tx_fअगरo_head *)context->buf;
	fb_option = (le16_to_cpu(fअगरo_head->fअगरo_ctl) &
			(FIFOCTL_AUTO_FB_0 | FIFOCTL_AUTO_FB_1));

	info = IEEE80211_SKB_CB(context->skb);
	idx = info->control.rates[0].idx;

	अगर (fb_option && !(tsr1 & TSR1_TERR)) अणु
		u8 tx_rate;
		u8 retry = tx_retry;

		rate = ieee80211_get_tx_rate(priv->hw, info);
		tx_rate = rate->hw_value - RATE_18M;

		अगर (retry > 4)
			retry = 4;

		अगर (fb_option & FIFOCTL_AUTO_FB_0)
			tx_rate = fallback_rate0[tx_rate][retry];
		अन्यथा अगर (fb_option & FIFOCTL_AUTO_FB_1)
			tx_rate = fallback_rate1[tx_rate][retry];

		अगर (info->band == NL80211_BAND_5GHZ)
			idx = tx_rate - RATE_6M;
		अन्यथा
			idx = tx_rate;
	पूर्ण

	ieee80211_tx_info_clear_status(info);

	info->status.rates[0].count = tx_retry;

	अगर (!(tsr1 & TSR1_TERR)) अणु
		info->status.rates[0].idx = idx;

		अगर (info->flags & IEEE80211_TX_CTL_NO_ACK)
			info->flags |= IEEE80211_TX_STAT_NOACK_TRANSMITTED;
		अन्यथा
			info->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक device_tx_srv(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा vnt_tx_desc *desc;
	पूर्णांक                      works = 0;
	अचिन्हित अक्षर byTsr0;
	अचिन्हित अक्षर byTsr1;

	क्रम (desc = priv->apTailTD[idx]; priv->iTDUsed[idx] > 0; desc = desc->next) अणु
		अगर (desc->td0.owner == OWNED_BY_NIC)
			अवरोध;
		अगर (works++ > 15)
			अवरोध;

		byTsr0 = desc->td0.tsr0;
		byTsr1 = desc->td0.tsr1;

		/* Only the status of first TD in the chain is correct */
		अगर (desc->td1.tcr & TCR_STP) अणु
			अगर ((desc->td_info->flags & TD_FLAGS_NETIF_SKB) != 0) अणु
				अगर (!(byTsr1 & TSR1_TERR)) अणु
					अगर (byTsr0 != 0) अणु
						pr_debug(" Tx[%d] OK but has error. tsr1[%02X] tsr0[%02X]\n",
							 (पूर्णांक)idx, byTsr1,
							 byTsr0);
					पूर्ण
				पूर्ण अन्यथा अणु
					pr_debug(" Tx[%d] dropped & tsr1[%02X] tsr0[%02X]\n",
						 (पूर्णांक)idx, byTsr1, byTsr0);
				पूर्ण
			पूर्ण

			अगर (byTsr1 & TSR1_TERR) अणु
				अगर ((desc->td_info->flags & TD_FLAGS_PRIV_SKB) != 0) अणु
					pr_debug(" Tx[%d] fail has error. tsr1[%02X] tsr0[%02X]\n",
						 (पूर्णांक)idx, byTsr1, byTsr0);
				पूर्ण
			पूर्ण

			vnt_पूर्णांक_report_rate(priv, desc->td_info, byTsr0, byTsr1);

			device_मुक्त_tx_buf(priv, desc);
			priv->iTDUsed[idx]--;
		पूर्ण
	पूर्ण

	priv->apTailTD[idx] = desc;

	वापस works;
पूर्ण

अटल व्योम device_error(काष्ठा vnt_निजी *priv, अचिन्हित लघु status)
अणु
	अगर (status & ISR_FETALERR) अणु
		dev_err(&priv->pcid->dev, "Hardware fatal error\n");

		MACbShutकरोwn(priv);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम device_मुक्त_tx_buf(काष्ठा vnt_निजी *priv,
			       काष्ठा vnt_tx_desc *desc)
अणु
	काष्ठा vnt_td_info *td_info = desc->td_info;
	काष्ठा sk_buff *skb = td_info->skb;

	अगर (skb)
		ieee80211_tx_status_irqsafe(priv->hw, skb);

	td_info->skb = शून्य;
	td_info->flags = 0;
पूर्ण

अटल व्योम vnt_check_bb_vga(काष्ठा vnt_निजी *priv)
अणु
	दीर्घ dbm;
	पूर्णांक i;

	अगर (!priv->bUpdateBBVGA)
		वापस;

	अगर (priv->hw->conf.flags & IEEE80211_CONF_OFFCHANNEL)
		वापस;

	अगर (!(priv->vअगर->bss_conf.assoc && priv->uCurrRSSI))
		वापस;

	RFvRSSITodBm(priv, (u8)priv->uCurrRSSI, &dbm);

	क्रम (i = 0; i < BB_VGA_LEVEL; i++) अणु
		अगर (dbm < priv->ldBmThreshold[i]) अणु
			priv->byBBVGANew = priv->abyBBVGA[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (priv->byBBVGANew == priv->byBBVGACurrent) अणु
		priv->uBBVGADअगरfCount = 1;
		वापस;
	पूर्ण

	priv->uBBVGADअगरfCount++;

	अगर (priv->uBBVGADअगरfCount == 1) अणु
		/* first VGA dअगरf gain */
		bb_set_vga_gain_offset(priv, priv->byBBVGANew);

		dev_dbg(&priv->pcid->dev,
			"First RSSI[%d] NewGain[%d] OldGain[%d] Count[%d]\n",
			(पूर्णांक)dbm, priv->byBBVGANew,
			priv->byBBVGACurrent,
			(पूर्णांक)priv->uBBVGADअगरfCount);
	पूर्ण

	अगर (priv->uBBVGADअगरfCount >= BB_VGA_CHANGE_THRESHOLD) अणु
		dev_dbg(&priv->pcid->dev,
			"RSSI[%d] NewGain[%d] OldGain[%d] Count[%d]\n",
			(पूर्णांक)dbm, priv->byBBVGANew,
			priv->byBBVGACurrent,
			(पूर्णांक)priv->uBBVGADअगरfCount);

		bb_set_vga_gain_offset(priv, priv->byBBVGANew);
	पूर्ण
पूर्ण

अटल व्योम vnt_पूर्णांकerrupt_process(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा ieee80211_low_level_stats *low_stats = &priv->low_stats;
	पूर्णांक             max_count = 0;
	u32 mib_counter;
	u32 isr;
	अचिन्हित दीर्घ flags;

	MACvReadISR(priv->PortOffset, &isr);

	अगर (isr == 0)
		वापस;

	अगर (isr == 0xffffffff) अणु
		pr_debug("isr = 0xffff\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	/* Read low level stats */
	MACvReadMIBCounter(priv->PortOffset, &mib_counter);

	low_stats->करोt11RTSSuccessCount += mib_counter & 0xff;
	low_stats->करोt11RTSFailureCount += (mib_counter >> 8) & 0xff;
	low_stats->करोt11ACKFailureCount += (mib_counter >> 16) & 0xff;
	low_stats->करोt11FCSErrorCount += (mib_counter >> 24) & 0xff;

	/*
	 * TBD....
	 * Must करो this after करोing rx/tx, cause ISR bit is slow
	 * than RD/TD ग_लिखो back
	 * update ISR counter
	 */
	जबतक (isr && priv->vअगर) अणु
		MACvWriteISR(priv->PortOffset, isr);

		अगर (isr & ISR_FETALERR) अणु
			pr_debug(" ISR_FETALERR\n");
			VNSvOutPortB(priv->PortOffset + MAC_REG_SOFTPWRCTL, 0);
			VNSvOutPortW(priv->PortOffset +
				     MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPECTI);
			device_error(priv, isr);
		पूर्ण

		अगर (isr & ISR_TBTT) अणु
			अगर (priv->op_mode != NL80211_IFTYPE_ADHOC)
				vnt_check_bb_vga(priv);

			priv->bBeaconSent = false;
			अगर (priv->bEnablePSMode)
				PSbIsNextTBTTWakeUp((व्योम *)priv);

			अगर ((priv->op_mode == NL80211_IFTYPE_AP ||
			    priv->op_mode == NL80211_IFTYPE_ADHOC) &&
			    priv->vअगर->bss_conf.enable_beacon)
				MACvOneShotTimer1MicroSec(priv,
							  (priv->vअगर->bss_conf.beacon_पूर्णांक -
							   MAKE_BEACON_RESERVED) << 10);

			/* TODO: adhoc PS mode */
		पूर्ण

		अगर (isr & ISR_BNTX) अणु
			अगर (priv->op_mode == NL80211_IFTYPE_ADHOC) अणु
				priv->bIsBeaconBufReadySet = false;
				priv->cbBeaconBufReadySetCnt = 0;
			पूर्ण

			priv->bBeaconSent = true;
		पूर्ण

		अगर (isr & ISR_RXDMA0)
			max_count += device_rx_srv(priv, TYPE_RXDMA0);

		अगर (isr & ISR_RXDMA1)
			max_count += device_rx_srv(priv, TYPE_RXDMA1);

		अगर (isr & ISR_TXDMA0)
			max_count += device_tx_srv(priv, TYPE_TXDMA0);

		अगर (isr & ISR_AC0DMA)
			max_count += device_tx_srv(priv, TYPE_AC0DMA);

		अगर (isr & ISR_SOFTTIMER1) अणु
			अगर (priv->vअगर->bss_conf.enable_beacon)
				vnt_beacon_make(priv, priv->vअगर);
		पूर्ण

		/* If both buffers available wake the queue */
		अगर (AVAIL_TD(priv, TYPE_TXDMA0) &&
		    AVAIL_TD(priv, TYPE_AC0DMA) &&
		    ieee80211_queue_stopped(priv->hw, 0))
			ieee80211_wake_queues(priv->hw);

		MACvReadISR(priv->PortOffset, &isr);

		MACvReceive0(priv->PortOffset);
		MACvReceive1(priv->PortOffset);

		अगर (max_count > priv->opts.पूर्णांक_works)
			अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल व्योम vnt_पूर्णांकerrupt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vnt_निजी *priv =
		container_of(work, काष्ठा vnt_निजी, पूर्णांकerrupt_work);

	अगर (priv->vअगर)
		vnt_पूर्णांकerrupt_process(priv);

	MACvIntEnable(priv->PortOffset, IMR_MASK_VALUE);
पूर्ण

अटल irqवापस_t vnt_पूर्णांकerrupt(पूर्णांक irq,  व्योम *arg)
अणु
	काष्ठा vnt_निजी *priv = arg;

	schedule_work(&priv->पूर्णांकerrupt_work);

	MACvIntDisable(priv->PortOffset);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vnt_tx_packet(काष्ठा vnt_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा vnt_tx_desc *head_td;
	u32 dma_idx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (ieee80211_is_data(hdr->frame_control))
		dma_idx = TYPE_AC0DMA;
	अन्यथा
		dma_idx = TYPE_TXDMA0;

	अगर (AVAIL_TD(priv, dma_idx) < 1) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		ieee80211_stop_queues(priv->hw);
		वापस -ENOMEM;
	पूर्ण

	head_td = priv->apCurrTD[dma_idx];

	head_td->td1.tcr = 0;

	head_td->td_info->skb = skb;

	अगर (dma_idx == TYPE_AC0DMA)
		head_td->td_info->flags = TD_FLAGS_NETIF_SKB;

	priv->apCurrTD[dma_idx] = head_td->next;

	spin_unlock_irqrestore(&priv->lock, flags);

	vnt_generate_fअगरo_header(priv, dma_idx, head_td, skb);

	spin_lock_irqsave(&priv->lock, flags);

	priv->bPWBitOn = false;

	/* Set TSR1 & ReqCount in TxDescHead */
	head_td->td1.tcr |= (TCR_STP | TCR_EDP | EDMSDU);
	head_td->td1.req_count = cpu_to_le16(head_td->td_info->req_count);

	head_td->buff_addr = cpu_to_le32(head_td->td_info->buf_dma);

	/* Poll Transmit the adapter */
	wmb();
	head_td->td0.owner = OWNED_BY_NIC;
	wmb(); /* second memory barrier */

	अगर (head_td->td_info->flags & TD_FLAGS_NETIF_SKB)
		MACvTransmitAC0(priv->PortOffset);
	अन्यथा
		MACvTransmit0(priv->PortOffset);

	priv->iTDUsed[dma_idx]++;

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम vnt_tx_80211(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_tx_control *control,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	अगर (vnt_tx_packet(priv, skb))
		ieee80211_मुक्त_txskb(hw, skb);
पूर्ण

अटल पूर्णांक vnt_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	पूर्णांक ret;

	priv->rx_buf_sz = PKT_BUF_SZ;
	अगर (!device_init_rings(priv))
		वापस -ENOMEM;

	ret = request_irq(priv->pcid->irq, vnt_पूर्णांकerrupt,
			  IRQF_SHARED, "vt6655", priv);
	अगर (ret) अणु
		dev_dbg(&priv->pcid->dev, "failed to start irq\n");
		जाओ err_मुक्त_rings;
	पूर्ण

	dev_dbg(&priv->pcid->dev, "call device init rd0 ring\n");
	ret = device_init_rd0_ring(priv);
	अगर (ret)
		जाओ err_मुक्त_irq;
	ret = device_init_rd1_ring(priv);
	अगर (ret)
		जाओ err_मुक्त_rd0_ring;
	ret = device_init_td0_ring(priv);
	अगर (ret)
		जाओ err_मुक्त_rd1_ring;
	ret = device_init_td1_ring(priv);
	अगर (ret)
		जाओ err_मुक्त_td0_ring;

	device_init_रेजिस्टरs(priv);

	dev_dbg(&priv->pcid->dev, "call MACvIntEnable\n");
	MACvIntEnable(priv->PortOffset, IMR_MASK_VALUE);

	ieee80211_wake_queues(hw);

	वापस 0;

err_मुक्त_td0_ring:
	device_मुक्त_td0_ring(priv);
err_मुक्त_rd1_ring:
	device_मुक्त_rd1_ring(priv);
err_मुक्त_rd0_ring:
	device_मुक्त_rd0_ring(priv);
err_मुक्त_irq:
	मुक्त_irq(priv->pcid->irq, priv);
err_मुक्त_rings:
	device_मुक्त_rings(priv);
	वापस ret;
पूर्ण

अटल व्योम vnt_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	ieee80211_stop_queues(hw);

	cancel_work_sync(&priv->पूर्णांकerrupt_work);

	MACbShutकरोwn(priv);
	MACbSoftwareReset(priv);
	CARDbRadioPowerOff(priv);

	device_मुक्त_td0_ring(priv);
	device_मुक्त_td1_ring(priv);
	device_मुक्त_rd0_ring(priv);
	device_मुक्त_rd1_ring(priv);
	device_मुक्त_rings(priv);

	मुक्त_irq(priv->pcid->irq, priv);
पूर्ण

अटल पूर्णांक vnt_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	priv->vअगर = vअगर;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		MACvRegBitsOff(priv->PortOffset, MAC_REG_RCR, RCR_UNICAST);

		MACvRegBitsOn(priv->PortOffset, MAC_REG_HOSTCR, HOSTCR_ADHOC);

		अवरोध;
	हाल NL80211_IFTYPE_AP:
		MACvRegBitsOff(priv->PortOffset, MAC_REG_RCR, RCR_UNICAST);

		MACvRegBitsOn(priv->PortOffset, MAC_REG_HOSTCR, HOSTCR_AP);

		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	priv->op_mode = vअगर->type;

	वापस 0;
पूर्ण

अटल व्योम vnt_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		MACvRegBitsOff(priv->PortOffset, MAC_REG_TCR, TCR_AUTOBCNTX);
		MACvRegBitsOff(priv->PortOffset,
			       MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);
		MACvRegBitsOff(priv->PortOffset, MAC_REG_HOSTCR, HOSTCR_ADHOC);
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		MACvRegBitsOff(priv->PortOffset, MAC_REG_TCR, TCR_AUTOBCNTX);
		MACvRegBitsOff(priv->PortOffset,
			       MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);
		MACvRegBitsOff(priv->PortOffset, MAC_REG_HOSTCR, HOSTCR_AP);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	priv->op_mode = NL80211_IFTYPE_UNSPECIFIED;
पूर्ण

अटल पूर्णांक vnt_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	u8 bb_type;

	अगर (changed & IEEE80211_CONF_CHANGE_PS) अणु
		अगर (conf->flags & IEEE80211_CONF_PS)
			PSvEnablePowerSaving(priv, conf->listen_पूर्णांकerval);
		अन्यथा
			PSvDisablePowerSaving(priv);
	पूर्ण

	अगर ((changed & IEEE80211_CONF_CHANGE_CHANNEL) ||
	    (conf->flags & IEEE80211_CONF_OFFCHANNEL)) अणु
		set_channel(priv, conf->chandef.chan);

		अगर (conf->chandef.chan->band == NL80211_BAND_5GHZ)
			bb_type = BB_TYPE_11A;
		अन्यथा
			bb_type = BB_TYPE_11G;

		अगर (priv->byBBType != bb_type) अणु
			priv->byBBType = bb_type;

			CARDbSetPhyParameter(priv, priv->byBBType);
		पूर्ण
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		अगर (priv->byBBType == BB_TYPE_11B)
			priv->wCurrentRate = RATE_1M;
		अन्यथा
			priv->wCurrentRate = RATE_54M;

		RFbSetPower(priv, priv->wCurrentRate,
			    conf->chandef.chan->hw_value);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vnt_bss_info_changed(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_bss_conf *conf, u32 changed)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	priv->current_aid = conf->aid;

	अगर (changed & BSS_CHANGED_BSSID && conf->bssid) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&priv->lock, flags);

		MACvWriteBSSIDAddress(priv->PortOffset, (u8 *)conf->bssid);

		spin_unlock_irqrestore(&priv->lock, flags);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		priv->basic_rates = conf->basic_rates;

		CARDvUpdateBasicTopRate(priv);

		dev_dbg(&priv->pcid->dev,
			"basic rates %x\n", conf->basic_rates);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		अगर (conf->use_लघु_preamble) अणु
			MACvEnableBarkerPreambleMd(priv->PortOffset);
			priv->byPreambleType = true;
		पूर्ण अन्यथा अणु
			MACvDisableBarkerPreambleMd(priv->PortOffset);
			priv->byPreambleType = false;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT) अणु
		अगर (conf->use_cts_prot)
			MACvEnableProtectMD(priv->PortOffset);
		अन्यथा
			MACvDisableProtectMD(priv->PortOffset);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		अगर (conf->use_लघु_slot)
			priv->bShortSlotTime = true;
		अन्यथा
			priv->bShortSlotTime = false;

		CARDbSetPhyParameter(priv, priv->byBBType);
		bb_set_vga_gain_offset(priv, priv->abyBBVGA[0]);
	पूर्ण

	अगर (changed & BSS_CHANGED_TXPOWER)
		RFbSetPower(priv, priv->wCurrentRate,
			    conf->chandef.chan->hw_value);

	अगर (changed & BSS_CHANGED_BEACON_ENABLED) अणु
		dev_dbg(&priv->pcid->dev,
			"Beacon enable %d\n", conf->enable_beacon);

		अगर (conf->enable_beacon) अणु
			vnt_beacon_enable(priv, vअगर, conf);

			MACvRegBitsOn(priv->PortOffset, MAC_REG_TCR,
				      TCR_AUTOBCNTX);
		पूर्ण अन्यथा अणु
			MACvRegBitsOff(priv->PortOffset, MAC_REG_TCR,
				       TCR_AUTOBCNTX);
		पूर्ण
	पूर्ण

	अगर (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_BEACON_INFO) &&
	    priv->op_mode != NL80211_IFTYPE_AP) अणु
		अगर (conf->assoc && conf->beacon_rate) अणु
			CARDbUpdateTSF(priv, conf->beacon_rate->hw_value,
				       conf->sync_tsf);

			CARDbSetBeaconPeriod(priv, conf->beacon_पूर्णांक);

			CARDvSetFirstNextTBTT(priv, conf->beacon_पूर्णांक);
		पूर्ण अन्यथा अणु
			VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL,
				     TFTCTL_TSFCNTRST);
			VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL,
				     TFTCTL_TSFCNTREN);
		पूर्ण
	पूर्ण
पूर्ण

अटल u64 vnt_prepare_multicast(काष्ठा ieee80211_hw *hw,
				 काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	काष्ठा netdev_hw_addr *ha;
	u64 mc_filter = 0;
	u32 bit_nr = 0;

	netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
		bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;

		mc_filter |= 1ULL << (bit_nr & 0x3f);
	पूर्ण

	priv->mc_list_count = mc_list->count;

	वापस mc_filter;
पूर्ण

अटल व्योम vnt_configure(काष्ठा ieee80211_hw *hw,
			  अचिन्हित पूर्णांक changed_flags,
			  अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	u8 rx_mode = 0;

	*total_flags &= FIF_ALLMULTI | FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC;

	VNSvInPortB(priv->PortOffset + MAC_REG_RCR, &rx_mode);

	dev_dbg(&priv->pcid->dev, "rx mode in = %x\n", rx_mode);

	अगर (changed_flags & FIF_ALLMULTI) अणु
		अगर (*total_flags & FIF_ALLMULTI) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&priv->lock, flags);

			अगर (priv->mc_list_count > 2) अणु
				MACvSelectPage1(priv->PortOffset);

				VNSvOutPortD(priv->PortOffset +
					     MAC_REG_MAR0, 0xffffffff);
				VNSvOutPortD(priv->PortOffset +
					    MAC_REG_MAR0 + 4, 0xffffffff);

				MACvSelectPage0(priv->PortOffset);
			पूर्ण अन्यथा अणु
				MACvSelectPage1(priv->PortOffset);

				VNSvOutPortD(priv->PortOffset +
					     MAC_REG_MAR0, (u32)multicast);
				VNSvOutPortD(priv->PortOffset +
					     MAC_REG_MAR0 + 4,
					     (u32)(multicast >> 32));

				MACvSelectPage0(priv->PortOffset);
			पूर्ण

			spin_unlock_irqrestore(&priv->lock, flags);

			rx_mode |= RCR_MULTICAST | RCR_BROADCAST;
		पूर्ण अन्यथा अणु
			rx_mode &= ~(RCR_MULTICAST | RCR_BROADCAST);
		पूर्ण
	पूर्ण

	अगर (changed_flags & (FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC)) अणु
		rx_mode |= RCR_MULTICAST | RCR_BROADCAST;

		अगर (*total_flags & (FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC))
			rx_mode &= ~RCR_BSSID;
		अन्यथा
			rx_mode |= RCR_BSSID;
	पूर्ण

	VNSvOutPortB(priv->PortOffset + MAC_REG_RCR, rx_mode);

	dev_dbg(&priv->pcid->dev, "rx mode out= %x\n", rx_mode);
पूर्ण

अटल पूर्णांक vnt_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		       काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (vnt_set_keys(hw, sta, vअगर, key))
			वापस -EOPNOTSUPP;
		अवरोध;
	हाल DISABLE_KEY:
		अगर (test_bit(key->hw_key_idx, &priv->key_entry_inuse))
			clear_bit(key->hw_key_idx, &priv->key_entry_inuse);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vnt_get_stats(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	स_नकल(stats, &priv->low_stats, माप(*stats));

	वापस 0;
पूर्ण

अटल u64 vnt_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;
	u64 tsf;

	CARDbGetCurrentTSF(priv, &tsf);

	वापस tsf;
पूर्ण

अटल व्योम vnt_set_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			u64 tsf)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	CARDvUpdateNextTBTT(priv, tsf, vअगर->bss_conf.beacon_पूर्णांक);
पूर्ण

अटल व्योम vnt_reset_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा vnt_निजी *priv = hw->priv;

	/* reset TSF counter */
	VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL, TFTCTL_TSFCNTRST);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops vnt_mac_ops = अणु
	.tx			= vnt_tx_80211,
	.start			= vnt_start,
	.stop			= vnt_stop,
	.add_पूर्णांकerface		= vnt_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= vnt_हटाओ_पूर्णांकerface,
	.config			= vnt_config,
	.bss_info_changed	= vnt_bss_info_changed,
	.prepare_multicast	= vnt_prepare_multicast,
	.configure_filter	= vnt_configure,
	.set_key		= vnt_set_key,
	.get_stats		= vnt_get_stats,
	.get_tsf		= vnt_get_tsf,
	.set_tsf		= vnt_set_tsf,
	.reset_tsf		= vnt_reset_tsf,
पूर्ण;

अटल पूर्णांक vnt_init(काष्ठा vnt_निजी *priv)
अणु
	SET_IEEE80211_PERM_ADDR(priv->hw, priv->abyCurrentNetAddr);

	vnt_init_bands(priv);

	अगर (ieee80211_रेजिस्टर_hw(priv->hw))
		वापस -ENODEV;

	priv->mac_hw = true;

	CARDbRadioPowerOff(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक
vt6655_probe(काष्ठा pci_dev *pcid, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा vnt_निजी *priv;
	काष्ठा ieee80211_hw *hw;
	काष्ठा wiphy *wiphy;
	पूर्णांक         rc;

	dev_notice(&pcid->dev,
		   "%s Ver. %s\n", DEVICE_FULL_DRV_NAM, DEVICE_VERSION);

	dev_notice(&pcid->dev,
		   "Copyright (c) 2003 VIA Networking Technologies, Inc.\n");

	hw = ieee80211_alloc_hw(माप(*priv), &vnt_mac_ops);
	अगर (!hw) अणु
		dev_err(&pcid->dev, "could not register ieee80211_hw\n");
		वापस -ENOMEM;
	पूर्ण

	priv = hw->priv;
	priv->pcid = pcid;

	spin_lock_init(&priv->lock);

	priv->hw = hw;

	SET_IEEE80211_DEV(priv->hw, &pcid->dev);

	अगर (pci_enable_device(pcid)) अणु
		device_मुक्त_info(priv);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(&pcid->dev,
		"Before get pci_info memaddr is %x\n", priv->memaddr);

	pci_set_master(pcid);

	priv->memaddr = pci_resource_start(pcid, 0);
	priv->ioaddr = pci_resource_start(pcid, 1);
	priv->PortOffset = ioremap(priv->memaddr & PCI_BASE_ADDRESS_MEM_MASK,
				   256);
	अगर (!priv->PortOffset) अणु
		dev_err(&pcid->dev, ": Failed to IO remapping ..\n");
		device_मुक्त_info(priv);
		वापस -ENODEV;
	पूर्ण

	rc = pci_request_regions(pcid, DEVICE_NAME);
	अगर (rc) अणु
		dev_err(&pcid->dev, ": Failed to find PCI device\n");
		device_मुक्त_info(priv);
		वापस -ENODEV;
	पूर्ण

	अगर (dma_set_mask(&pcid->dev, DMA_BIT_MASK(32))) अणु
		dev_err(&pcid->dev, ": Failed to set dma 32 bit mask\n");
		device_मुक्त_info(priv);
		वापस -ENODEV;
	पूर्ण

	INIT_WORK(&priv->पूर्णांकerrupt_work, vnt_पूर्णांकerrupt_work);

	/* करो reset */
	अगर (!MACbSoftwareReset(priv)) अणु
		dev_err(&pcid->dev, ": Failed to access MAC hardware..\n");
		device_मुक्त_info(priv);
		वापस -ENODEV;
	पूर्ण
	/* initial to reload eeprom */
	MACvInitialize(priv);
	MACvReadEtherAddress(priv->PortOffset, priv->abyCurrentNetAddr);

	/* Get RFType */
	priv->byRFType = SROMbyReadEmbedded(priv->PortOffset, EEP_OFS_RFTYPE);
	priv->byRFType &= RF_MASK;

	dev_dbg(&pcid->dev, "RF Type = %x\n", priv->byRFType);

	device_get_options(priv);
	device_set_options(priv);

	wiphy = priv->hw->wiphy;

	wiphy->frag_threshold = FRAG_THRESH_DEF;
	wiphy->rts_threshold = RTS_THRESH_DEF;
	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC) | BIT(NL80211_IFTYPE_AP);

	ieee80211_hw_set(priv->hw, TIMING_BEACON_ONLY);
	ieee80211_hw_set(priv->hw, SIGNAL_DBM);
	ieee80211_hw_set(priv->hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(priv->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(priv->hw, SUPPORTS_PS);

	priv->hw->max_संकेत = 100;

	अगर (vnt_init(priv)) अणु
		device_मुक्त_info(priv);
		वापस -ENODEV;
	पूर्ण

	device_prपूर्णांक_info(priv);
	pci_set_drvdata(pcid, priv);

	वापस 0;
पूर्ण

/*------------------------------------------------------------------*/

अटल पूर्णांक __maybe_unused vt6655_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा vnt_निजी *priv = dev_get_drvdata(dev_d);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	MACbShutकरोwn(priv);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused vt6655_resume(काष्ठा device *dev_d)
अणु
	device_wakeup_disable(dev_d);

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(pci, vt6655_pci_id_table);

अटल SIMPLE_DEV_PM_OPS(vt6655_pm_ops, vt6655_suspend, vt6655_resume);

अटल काष्ठा pci_driver device_driver = अणु
	.name = DEVICE_NAME,
	.id_table = vt6655_pci_id_table,
	.probe = vt6655_probe,
	.हटाओ = vt6655_हटाओ,
	.driver.pm = &vt6655_pm_ops,
पूर्ण;

module_pci_driver(device_driver);
