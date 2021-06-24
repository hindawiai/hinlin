<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FIREWIRE_OHCI_H
#घोषणा _FIREWIRE_OHCI_H

/* OHCI रेजिस्टर map */

#घोषणा OHCI1394_Version                      0x000
#घोषणा OHCI1394_GUID_ROM                     0x004
#घोषणा OHCI1394_ATRetries                    0x008
#घोषणा OHCI1394_CSRData                      0x00C
#घोषणा OHCI1394_CSRCompareData               0x010
#घोषणा OHCI1394_CSRControl                   0x014
#घोषणा OHCI1394_ConfigROMhdr                 0x018
#घोषणा OHCI1394_BusID                        0x01C
#घोषणा OHCI1394_BusOptions                   0x020
#घोषणा OHCI1394_GUIDHi                       0x024
#घोषणा OHCI1394_GUIDLo                       0x028
#घोषणा OHCI1394_ConfigROMmap                 0x034
#घोषणा OHCI1394_PostedWriteAddressLo         0x038
#घोषणा OHCI1394_PostedWriteAddressHi         0x03C
#घोषणा OHCI1394_VenकरोrID                     0x040
#घोषणा OHCI1394_HCControlSet                 0x050
#घोषणा OHCI1394_HCControlClear               0x054
#घोषणा  OHCI1394_HCControl_BIBimageValid	0x80000000
#घोषणा  OHCI1394_HCControl_noByteSwapData	0x40000000
#घोषणा  OHCI1394_HCControl_programPhyEnable	0x00800000
#घोषणा  OHCI1394_HCControl_aPhyEnhanceEnable	0x00400000
#घोषणा  OHCI1394_HCControl_LPS			0x00080000
#घोषणा  OHCI1394_HCControl_postedWriteEnable	0x00040000
#घोषणा  OHCI1394_HCControl_linkEnable		0x00020000
#घोषणा  OHCI1394_HCControl_softReset		0x00010000
#घोषणा OHCI1394_SelfIDBuffer                 0x064
#घोषणा OHCI1394_SelfIDCount                  0x068
#घोषणा  OHCI1394_SelfIDCount_selfIDError	0x80000000
#घोषणा OHCI1394_IRMultiChanMaskHiSet         0x070
#घोषणा OHCI1394_IRMultiChanMaskHiClear       0x074
#घोषणा OHCI1394_IRMultiChanMaskLoSet         0x078
#घोषणा OHCI1394_IRMultiChanMaskLoClear       0x07C
#घोषणा OHCI1394_IntEventSet                  0x080
#घोषणा OHCI1394_IntEventClear                0x084
#घोषणा OHCI1394_IntMaskSet                   0x088
#घोषणा OHCI1394_IntMaskClear                 0x08C
#घोषणा OHCI1394_IsoXmitIntEventSet           0x090
#घोषणा OHCI1394_IsoXmitIntEventClear         0x094
#घोषणा OHCI1394_IsoXmitIntMaskSet            0x098
#घोषणा OHCI1394_IsoXmitIntMaskClear          0x09C
#घोषणा OHCI1394_IsoRecvIntEventSet           0x0A0
#घोषणा OHCI1394_IsoRecvIntEventClear         0x0A4
#घोषणा OHCI1394_IsoRecvIntMaskSet            0x0A8
#घोषणा OHCI1394_IsoRecvIntMaskClear          0x0AC
#घोषणा OHCI1394_InitialBandwidthAvailable    0x0B0
#घोषणा OHCI1394_InitialChannelsAvailableHi   0x0B4
#घोषणा OHCI1394_InitialChannelsAvailableLo   0x0B8
#घोषणा OHCI1394_FairnessControl              0x0DC
#घोषणा OHCI1394_LinkControlSet               0x0E0
#घोषणा OHCI1394_LinkControlClear             0x0E4
#घोषणा   OHCI1394_LinkControl_rcvSelfID	(1 << 9)
#घोषणा   OHCI1394_LinkControl_rcvPhyPkt	(1 << 10)
#घोषणा   OHCI1394_LinkControl_cycleTimerEnable	(1 << 20)
#घोषणा   OHCI1394_LinkControl_cycleMaster	(1 << 21)
#घोषणा   OHCI1394_LinkControl_cycleSource	(1 << 22)
#घोषणा OHCI1394_NodeID                       0x0E8
#घोषणा   OHCI1394_NodeID_idValid             0x80000000
#घोषणा   OHCI1394_NodeID_root                0x40000000
#घोषणा   OHCI1394_NodeID_nodeNumber          0x0000003f
#घोषणा   OHCI1394_NodeID_busNumber           0x0000ffc0
#घोषणा OHCI1394_PhyControl                   0x0EC
#घोषणा   OHCI1394_PhyControl_Read(addr)	(((addr) << 8) | 0x00008000)
#घोषणा   OHCI1394_PhyControl_ReadDone		0x80000000
#घोषणा   OHCI1394_PhyControl_ReadData(r)	(((r) & 0x00ff0000) >> 16)
#घोषणा   OHCI1394_PhyControl_Write(addr, data)	(((addr) << 8) | (data) | 0x00004000)
#घोषणा   OHCI1394_PhyControl_WritePending	0x00004000
#घोषणा OHCI1394_IsochronousCycleTimer        0x0F0
#घोषणा OHCI1394_AsReqFilterHiSet             0x100
#घोषणा OHCI1394_AsReqFilterHiClear           0x104
#घोषणा OHCI1394_AsReqFilterLoSet             0x108
#घोषणा OHCI1394_AsReqFilterLoClear           0x10C
#घोषणा OHCI1394_PhyReqFilterHiSet            0x110
#घोषणा OHCI1394_PhyReqFilterHiClear          0x114
#घोषणा OHCI1394_PhyReqFilterLoSet            0x118
#घोषणा OHCI1394_PhyReqFilterLoClear          0x11C
#घोषणा OHCI1394_PhyUpperBound                0x120

#घोषणा OHCI1394_AsReqTrContextBase           0x180
#घोषणा OHCI1394_AsReqTrContextControlSet     0x180
#घोषणा OHCI1394_AsReqTrContextControlClear   0x184
#घोषणा OHCI1394_AsReqTrCommandPtr            0x18C

#घोषणा OHCI1394_AsRspTrContextBase           0x1A0
#घोषणा OHCI1394_AsRspTrContextControlSet     0x1A0
#घोषणा OHCI1394_AsRspTrContextControlClear   0x1A4
#घोषणा OHCI1394_AsRspTrCommandPtr            0x1AC

#घोषणा OHCI1394_AsReqRcvContextBase          0x1C0
#घोषणा OHCI1394_AsReqRcvContextControlSet    0x1C0
#घोषणा OHCI1394_AsReqRcvContextControlClear  0x1C4
#घोषणा OHCI1394_AsReqRcvCommandPtr           0x1CC

#घोषणा OHCI1394_AsRspRcvContextBase          0x1E0
#घोषणा OHCI1394_AsRspRcvContextControlSet    0x1E0
#घोषणा OHCI1394_AsRspRcvContextControlClear  0x1E4
#घोषणा OHCI1394_AsRspRcvCommandPtr           0x1EC

/* Isochronous transmit रेजिस्टरs */
#घोषणा OHCI1394_IsoXmitContextBase(n)           (0x200 + 16 * (n))
#घोषणा OHCI1394_IsoXmitContextControlSet(n)     (0x200 + 16 * (n))
#घोषणा OHCI1394_IsoXmitContextControlClear(n)   (0x204 + 16 * (n))
#घोषणा OHCI1394_IsoXmitCommandPtr(n)            (0x20C + 16 * (n))

/* Isochronous receive रेजिस्टरs */
#घोषणा OHCI1394_IsoRcvContextBase(n)         (0x400 + 32 * (n))
#घोषणा OHCI1394_IsoRcvContextControlSet(n)   (0x400 + 32 * (n))
#घोषणा OHCI1394_IsoRcvContextControlClear(n) (0x404 + 32 * (n))
#घोषणा OHCI1394_IsoRcvCommandPtr(n)          (0x40C + 32 * (n))
#घोषणा OHCI1394_IsoRcvContextMatch(n)        (0x410 + 32 * (n))

/* Interrupts Mask/Events */
#घोषणा OHCI1394_reqTxComplete		0x00000001
#घोषणा OHCI1394_respTxComplete		0x00000002
#घोषणा OHCI1394_ARRQ			0x00000004
#घोषणा OHCI1394_ARRS			0x00000008
#घोषणा OHCI1394_RQPkt			0x00000010
#घोषणा OHCI1394_RSPkt			0x00000020
#घोषणा OHCI1394_isochTx		0x00000040
#घोषणा OHCI1394_isochRx		0x00000080
#घोषणा OHCI1394_postedWriteErr		0x00000100
#घोषणा OHCI1394_lockRespErr		0x00000200
#घोषणा OHCI1394_selfIDComplete		0x00010000
#घोषणा OHCI1394_busReset		0x00020000
#घोषणा OHCI1394_regAccessFail		0x00040000
#घोषणा OHCI1394_phy			0x00080000
#घोषणा OHCI1394_cycleSynch		0x00100000
#घोषणा OHCI1394_cycle64Seconds		0x00200000
#घोषणा OHCI1394_cycleLost		0x00400000
#घोषणा OHCI1394_cycleInconsistent	0x00800000
#घोषणा OHCI1394_unrecoverableError	0x01000000
#घोषणा OHCI1394_cycleTooLong		0x02000000
#घोषणा OHCI1394_phyRegRcvd		0x04000000
#घोषणा OHCI1394_masterIntEnable	0x80000000

#घोषणा OHCI1394_evt_no_status		0x0
#घोषणा OHCI1394_evt_दीर्घ_packet	0x2
#घोषणा OHCI1394_evt_missing_ack	0x3
#घोषणा OHCI1394_evt_underrun		0x4
#घोषणा OHCI1394_evt_overrun		0x5
#घोषणा OHCI1394_evt_descriptor_पढ़ो	0x6
#घोषणा OHCI1394_evt_data_पढ़ो		0x7
#घोषणा OHCI1394_evt_data_ग_लिखो		0x8
#घोषणा OHCI1394_evt_bus_reset		0x9
#घोषणा OHCI1394_evt_समयout		0xa
#घोषणा OHCI1394_evt_tcode_err		0xb
#घोषणा OHCI1394_evt_reserved_b		0xc
#घोषणा OHCI1394_evt_reserved_c		0xd
#घोषणा OHCI1394_evt_unknown		0xe
#घोषणा OHCI1394_evt_flushed		0xf

#घोषणा OHCI1394_phy_tcode		0xe

#पूर्ण_अगर /* _FIREWIRE_OHCI_H */
