<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * dm9000 Ethernet
 */

#अगर_अघोषित _DM9000X_H_
#घोषणा _DM9000X_H_

#घोषणा DM9000_ID		0x90000A46

/* although the रेजिस्टरs are 16 bit, they are 32-bit aligned.
 */

#घोषणा DM9000_NCR             0x00
#घोषणा DM9000_NSR             0x01
#घोषणा DM9000_TCR             0x02
#घोषणा DM9000_TSR1            0x03
#घोषणा DM9000_TSR2            0x04
#घोषणा DM9000_RCR             0x05
#घोषणा DM9000_RSR             0x06
#घोषणा DM9000_ROCR            0x07
#घोषणा DM9000_BPTR            0x08
#घोषणा DM9000_FCTR            0x09
#घोषणा DM9000_FCR             0x0A
#घोषणा DM9000_EPCR            0x0B
#घोषणा DM9000_EPAR            0x0C
#घोषणा DM9000_EPDRL           0x0D
#घोषणा DM9000_EPDRH           0x0E
#घोषणा DM9000_WCR             0x0F

#घोषणा DM9000_PAR             0x10
#घोषणा DM9000_MAR             0x16

#घोषणा DM9000_GPCR	       0x1e
#घोषणा DM9000_GPR             0x1f
#घोषणा DM9000_TRPAL           0x22
#घोषणा DM9000_TRPAH           0x23
#घोषणा DM9000_RWPAL           0x24
#घोषणा DM9000_RWPAH           0x25

#घोषणा DM9000_VIDL            0x28
#घोषणा DM9000_VIDH            0x29
#घोषणा DM9000_PIDL            0x2A
#घोषणा DM9000_PIDH            0x2B

#घोषणा DM9000_CHIPR           0x2C
#घोषणा DM9000_SMCR            0x2F

#घोषणा DM9000_ETXCSR          0x30
#घोषणा DM9000_TCCR	       0x31
#घोषणा DM9000_RCSR	       0x32

#घोषणा CHIPR_DM9000A	       0x19
#घोषणा CHIPR_DM9000B	       0x1A

#घोषणा DM9000_MRCMDX          0xF0
#घोषणा DM9000_MRCMD           0xF2
#घोषणा DM9000_MRRL            0xF4
#घोषणा DM9000_MRRH            0xF5
#घोषणा DM9000_MWCMDX          0xF6
#घोषणा DM9000_MWCMD           0xF8
#घोषणा DM9000_MWRL            0xFA
#घोषणा DM9000_MWRH            0xFB
#घोषणा DM9000_TXPLL           0xFC
#घोषणा DM9000_TXPLH           0xFD
#घोषणा DM9000_ISR             0xFE
#घोषणा DM9000_IMR             0xFF

#घोषणा NCR_EXT_PHY         (1<<7)
#घोषणा NCR_WAKEEN          (1<<6)
#घोषणा NCR_FCOL            (1<<4)
#घोषणा NCR_FDX             (1<<3)

#घोषणा NCR_RESERVED        (3<<1)
#घोषणा NCR_MAC_LBK         (1<<1)
#घोषणा NCR_RST	            (1<<0)

#घोषणा NSR_SPEED           (1<<7)
#घोषणा NSR_LINKST          (1<<6)
#घोषणा NSR_WAKEST          (1<<5)
#घोषणा NSR_TX2END          (1<<3)
#घोषणा NSR_TX1END          (1<<2)
#घोषणा NSR_RXOV            (1<<1)

#घोषणा TCR_TJDIS           (1<<6)
#घोषणा TCR_EXCECM          (1<<5)
#घोषणा TCR_PAD_DIS2        (1<<4)
#घोषणा TCR_CRC_DIS2        (1<<3)
#घोषणा TCR_PAD_DIS1        (1<<2)
#घोषणा TCR_CRC_DIS1        (1<<1)
#घोषणा TCR_TXREQ           (1<<0)

#घोषणा TSR_TJTO            (1<<7)
#घोषणा TSR_LC              (1<<6)
#घोषणा TSR_NC              (1<<5)
#घोषणा TSR_LCOL            (1<<4)
#घोषणा TSR_COL             (1<<3)
#घोषणा TSR_EC              (1<<2)

#घोषणा RCR_WTDIS           (1<<6)
#घोषणा RCR_DIS_LONG        (1<<5)
#घोषणा RCR_DIS_CRC         (1<<4)
#घोषणा RCR_ALL	            (1<<3)
#घोषणा RCR_RUNT            (1<<2)
#घोषणा RCR_PRMSC           (1<<1)
#घोषणा RCR_RXEN            (1<<0)

#घोषणा RSR_RF              (1<<7)
#घोषणा RSR_MF              (1<<6)
#घोषणा RSR_LCS             (1<<5)
#घोषणा RSR_RWTO            (1<<4)
#घोषणा RSR_PLE             (1<<3)
#घोषणा RSR_AE              (1<<2)
#घोषणा RSR_CE              (1<<1)
#घोषणा RSR_FOE             (1<<0)

#घोषणा WCR_LINKEN		(1 << 5)
#घोषणा WCR_SAMPLEEN		(1 << 4)
#घोषणा WCR_MAGICEN		(1 << 3)
#घोषणा WCR_LINKST		(1 << 2)
#घोषणा WCR_SAMPLEST		(1 << 1)
#घोषणा WCR_MAGICST		(1 << 0)

#घोषणा FCTR_HWOT(ot)	(( ot & 0xf ) << 4 )
#घोषणा FCTR_LWOT(ot)	( ot & 0xf )

#घोषणा IMR_PAR             (1<<7)
#घोषणा IMR_ROOM            (1<<3)
#घोषणा IMR_ROM             (1<<2)
#घोषणा IMR_PTM             (1<<1)
#घोषणा IMR_PRM             (1<<0)

#घोषणा ISR_ROOS            (1<<3)
#घोषणा ISR_ROS             (1<<2)
#घोषणा ISR_PTS             (1<<1)
#घोषणा ISR_PRS             (1<<0)
#घोषणा ISR_CLR_STATUS      (ISR_ROOS | ISR_ROS | ISR_PTS | ISR_PRS)

#घोषणा EPCR_REEP           (1<<5)
#घोषणा EPCR_WEP            (1<<4)
#घोषणा EPCR_EPOS           (1<<3)
#घोषणा EPCR_ERPRR          (1<<2)
#घोषणा EPCR_ERPRW          (1<<1)
#घोषणा EPCR_ERRE           (1<<0)

#घोषणा GPCR_GEP_CNTL       (1<<0)

#घोषणा TCCR_IP		    (1<<0)
#घोषणा TCCR_TCP	    (1<<1)
#घोषणा TCCR_UDP	    (1<<2)

#घोषणा RCSR_UDP_BAD	    (1<<7)
#घोषणा RCSR_TCP_BAD	    (1<<6)
#घोषणा RCSR_IP_BAD	    (1<<5)
#घोषणा RCSR_UDP	    (1<<4)
#घोषणा RCSR_TCP	    (1<<3)
#घोषणा RCSR_IP		    (1<<2)
#घोषणा RCSR_CSUM	    (1<<1)
#घोषणा RCSR_DISCARD	    (1<<0)

#घोषणा DM9000_PKT_RDY		0x01	/* Packet पढ़ोy to receive */
#घोषणा DM9000_PKT_ERR		0x02
#घोषणा DM9000_PKT_MAX		1536	/* Received packet max size */

/* DM9000A / DM9000B definitions */

#घोषणा IMR_LNKCHNG		(1<<5)
#घोषणा IMR_UNDERRUN		(1<<4)

#घोषणा ISR_LNKCHNG		(1<<5)
#घोषणा ISR_UNDERRUN		(1<<4)

/* Davicom MII रेजिस्टरs.
 */

#घोषणा MII_DM_DSPCR		0x1b    /* DSP Control Register */

#घोषणा DSPCR_INIT_PARAM	0xE100	/* DSP init parameter */

#पूर्ण_अगर /* _DM9000X_H_ */

