<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _R819XU_PHYREG_H
#घोषणा _R819XU_PHYREG_H

#घोषणा   RF_DATA				0x1d4					/* FW will ग_लिखो RF data in the रेजिस्टर.*/

/* page8 */
#घोषणा rFPGA0_RFMOD				0x800  /* RF mode & CCK TxSC */
#घोषणा rFPGA0_TxGainStage			0x80c
#घोषणा rFPGA0_XA_HSSIParameter1	0x820
#घोषणा rFPGA0_XA_HSSIParameter2	0x824
#घोषणा rFPGA0_XB_HSSIParameter1	0x828
#घोषणा rFPGA0_XB_HSSIParameter2	0x82c
#घोषणा rFPGA0_XC_HSSIParameter1	0x830
#घोषणा rFPGA0_XC_HSSIParameter2	0x834
#घोषणा rFPGA0_XD_HSSIParameter1	0x838
#घोषणा rFPGA0_XD_HSSIParameter2	0x83c
#घोषणा rFPGA0_XA_LSSIParameter		0x840
#घोषणा rFPGA0_XB_LSSIParameter		0x844
#घोषणा rFPGA0_XC_LSSIParameter		0x848
#घोषणा rFPGA0_XD_LSSIParameter		0x84c
#घोषणा rFPGA0_XAB_SwitchControl	0x858
#घोषणा rFPGA0_XCD_SwitchControl	0x85c
#घोषणा rFPGA0_XA_RFInterfaceOE		0x860
#घोषणा rFPGA0_XB_RFInterfaceOE		0x864
#घोषणा rFPGA0_XC_RFInterfaceOE		0x868
#घोषणा rFPGA0_XD_RFInterfaceOE		0x86c
#घोषणा rFPGA0_XAB_RFInterfaceSW	0x870
#घोषणा rFPGA0_XCD_RFInterfaceSW	0x874
#घोषणा rFPGA0_XAB_RFParameter		0x878
#घोषणा rFPGA0_XCD_RFParameter		0x87c
#घोषणा rFPGA0_AnalogParameter1		0x880
#घोषणा rFPGA0_AnalogParameter4		0x88c
#घोषणा rFPGA0_XA_LSSIReadBack		0x8a0
#घोषणा rFPGA0_XB_LSSIReadBack		0x8a4
#घोषणा rFPGA0_XC_LSSIReadBack		0x8a8
#घोषणा rFPGA0_XD_LSSIReadBack		0x8ac
#घोषणा rFPGA0_XAB_RFInterfaceRB	0x8e0
#घोषणा rFPGA0_XCD_RFInterfaceRB	0x8e4

/* page 9 */
#घोषणा rFPGA1_RFMOD				0x900  /* RF mode & OFDM TxSC */

/* page a */
#घोषणा rCCK0_System				0xa00
#घोषणा rCCK0_AFESetting			0xa04
#घोषणा rCCK0_CCA					0xa08
#घोषणा rCCK0_TxFilter1				0xa20
#घोषणा rCCK0_TxFilter2				0xa24
#घोषणा rCCK0_DebugPort				0xa28  /* debug port and Tx filter3 */

/* page c */
#घोषणा rOFDM0_TRxPathEnable		0xc04
#घोषणा rOFDM0_XARxAFE				0xc10  /* RxIQ DC offset, Rx digital filter, DC notch filter */
#घोषणा rOFDM0_XARxIQImbalance		0xc14  /* RxIQ imbalance matrix */
#घोषणा rOFDM0_XBRxAFE				0xc18
#घोषणा rOFDM0_XBRxIQImbalance		0xc1c
#घोषणा rOFDM0_XCRxAFE				0xc20
#घोषणा rOFDM0_XCRxIQImbalance		0xc24
#घोषणा rOFDM0_XDRxAFE				0xc28
#घोषणा rOFDM0_XDRxIQImbalance		0xc2c
#घोषणा rOFDM0_RxDetector1			0xc30  /* PD,BW & SBD */
#घोषणा rOFDM0_RxDetector2			0xc34  /* SBD & Fame Sync.*/
#घोषणा rOFDM0_RxDetector3			0xc38  /* Frame Sync.*/
#घोषणा rOFDM0_ECCAThreshold		0xc4c /* energy CCA */
#घोषणा rOFDM0_XAAGCCore1		0xc50
#घोषणा rOFDM0_XAAGCCore2		0xc54
#घोषणा rOFDM0_XBAGCCore1		0xc58
#घोषणा rOFDM0_XBAGCCore2		0xc5c
#घोषणा rOFDM0_XCAGCCore1		0xc60
#घोषणा rOFDM0_XCAGCCore2		0xc64
#घोषणा rOFDM0_XDAGCCore1		0xc68
#घोषणा rOFDM0_XDAGCCore2		0xc6c
#घोषणा rOFDM0_XATxIQImbalance		0xc80
#घोषणा rOFDM0_XATxAFE				0xc84
#घोषणा rOFDM0_XBTxIQImbalance		0xc88
#घोषणा rOFDM0_XBTxAFE				0xc8c
#घोषणा rOFDM0_XCTxIQImbalance		0xc90
#घोषणा rOFDM0_XCTxAFE				0xc94
#घोषणा rOFDM0_XDTxIQImbalance		0xc98
#घोषणा rOFDM0_XDTxAFE				0xc9c

/* page d */
#घोषणा rOFDM1_LSTF				0xd00
#घोषणा rOFDM1_TRxPathEnable		0xd04

/* page e */
#घोषणा rTxAGC_Rate18_06			0xe00
#घोषणा rTxAGC_Rate54_24			0xe04
#घोषणा rTxAGC_CCK_Mcs32			0xe08
#घोषणा rTxAGC_Mcs03_Mcs00			0xe10
#घोषणा rTxAGC_Mcs07_Mcs04			0xe14
#घोषणा rTxAGC_Mcs11_Mcs08			0xe18
#घोषणा rTxAGC_Mcs15_Mcs12			0xe1c

/* RF
 * Zebra1
 */
#घोषणा rZebra1_Channel				0x7

/* Zebra4 */
#घोषणा rGlobalCtrl				0

/* Bit Mask
 * page-8
 */
#घोषणा bRFMOD						0x1
#घोषणा bCCKEn						0x1000000
#घोषणा bOFDMEn						0x2000000
#घोषणा bXBTxAGC					0xf00
#घोषणा bXCTxAGC					0xf000
#घोषणा b3WireDataLength			0x800
#घोषणा b3WireAddressLength			0x400
#घोषणा bRFSI_RFENV				0x10
#घोषणा bLSSIReadAddress			0x3f000000   /* LSSI "Read" Address */
#घोषणा bLSSIReadEdge				0x80000000   /* LSSI "Read" edge संकेत */
#घोषणा bLSSIReadBackData			0xfff
#घोषणा bXtalCap					0x0f000000

/* page-a */
#घोषणा bCCKSideBand				0x10

/* page e */
#घोषणा bTxAGCRateCCK			0x7f00

/* RF
 * Zebra1
 */
#घोषणा bZebra1_ChannelNum        0xf80

/* RTL8258 */
/* क्रम PutRegsetting & GetRegSetting BitMask */
#घोषणा bMaskByte0                0xff
#घोषणा bMaskByte1                0xff00
#घोषणा bMaskByte2                0xff0000
#घोषणा bMaskHWord                0xffff0000
#घोषणा bMaskLWord                0x0000ffff
#घोषणा bMaskDWord                0xffffffff

/* क्रम PutRFRegsetting & GetRFRegSetting BitMask */
#घोषणा bMask12Bits               0xfff

#पूर्ण_अगर	/* __INC_HAL8190PCIPHYREG_H */
