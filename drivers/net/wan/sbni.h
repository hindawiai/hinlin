<शैली गुरु>
/* sbni.h:  definitions क्रम a Granch SBNI12 driver, version 5.0.0
 * Written 2001 Denis I.Timofeev (timofeev@granch.ru)
 * This file is distributed under the GNU GPL
 */

#अगर_अघोषित SBNI_H
#घोषणा SBNI_H

#अगर_घोषित SBNI_DEBUG
#घोषणा DP( A ) A
#अन्यथा
#घोषणा DP( A )
#पूर्ण_अगर


/* We करोn't have official venकरोr id yet... */
#घोषणा SBNI_PCI_VENDOR 	0x55 
#घोषणा SBNI_PCI_DEVICE 	0x9f

#घोषणा ISA_MODE 0x00
#घोषणा PCI_MODE 0x01

#घोषणा	SBNI_IO_EXTENT	4

क्रमागत sbni_reg अणु
	CSR0 = 0,
	CSR1 = 1,
	DAT  = 2
पूर्ण;

/* CSR0 mapping */
क्रमागत अणु
	BU_EMP = 0x02,
	RC_CHK = 0x04,
	CT_ZER = 0x08,
	TR_REQ = 0x10,
	TR_RDY = 0x20,
	EN_INT = 0x40,
	RC_RDY = 0x80
पूर्ण;


/* CSR1 mapping */
#घोषणा PR_RES 0x80

काष्ठा sbni_csr1 अणु
#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
	u8 rxl	: 5;
	u8 rate	: 2;
	u8 	: 1;
#अन्यथा
	u8 	: 1;
	u8 rate	: 2;
	u8 rxl	: 5;
#पूर्ण_अगर
पूर्ण;

/* fields in frame header */
#घोषणा FRAME_ACK_MASK  (अचिन्हित लघु)0x7000
#घोषणा FRAME_LEN_MASK  (अचिन्हित लघु)0x03FF
#घोषणा FRAME_FIRST     (अचिन्हित लघु)0x8000
#घोषणा FRAME_RETRY     (अचिन्हित लघु)0x0800

#घोषणा FRAME_SENT_BAD  (अचिन्हित लघु)0x4000
#घोषणा FRAME_SENT_OK   (अचिन्हित लघु)0x3000


/* state flags */
क्रमागत अणु
	FL_WAIT_ACK    = 0x01,
	FL_NEED_RESEND = 0x02,
	FL_PREV_OK     = 0x04,
	FL_SLOW_MODE   = 0x08,
	FL_SECONDARY   = 0x10,
#अगर_घोषित CONFIG_SBNI_MULTILINE
	FL_SLAVE       = 0x20,
#पूर्ण_अगर
	FL_LINE_DOWN   = 0x40
पूर्ण;


क्रमागत अणु
	DEFAULT_IOBASEADDR = 0x210,
	DEFAULT_INTERRUPTNUMBER = 5,
	DEFAULT_RATE = 0,
	DEFAULT_FRAME_LEN = 1012
पूर्ण;

#घोषणा DEF_RXL_DELTA	-1
#घोषणा DEF_RXL		0xf

#घोषणा SBNI_SIG 0x5a

#घोषणा	SBNI_MIN_LEN	60	/* Shortest Ethernet frame without FCS */
#घोषणा SBNI_MAX_FRAME	1023
#घोषणा ETHER_MAX_LEN	1518

#घोषणा SBNI_TIMEOUT	(HZ/10)

#घोषणा TR_ERROR_COUNT	32
#घोषणा CHANGE_LEVEL_START_TICKS 4

#घोषणा SBNI_MAX_NUM_CARDS	16

/* पूर्णांकernal SBNI-specअगरic statistics */
काष्ठा sbni_in_stats अणु
	u32	all_rx_number;
	u32	bad_rx_number;
	u32	समयout_number;
	u32	all_tx_number;
	u32	resend_tx_number;
पूर्ण;

/* SBNI ioctl params */
#घोषणा SIOCDEVGETINSTATS 	SIOCDEVPRIVATE
#घोषणा SIOCDEVRESINSTATS 	SIOCDEVPRIVATE+1
#घोषणा SIOCDEVGHWSTATE   	SIOCDEVPRIVATE+2
#घोषणा SIOCDEVSHWSTATE   	SIOCDEVPRIVATE+3
#घोषणा SIOCDEVENSLAVE  	SIOCDEVPRIVATE+4
#घोषणा SIOCDEVEMANSIPATE  	SIOCDEVPRIVATE+5


/* data packet क्रम SIOCDEVGHWSTATE/SIOCDEVSHWSTATE ioctl requests */
काष्ठा sbni_flags अणु
	u32	rxl		: 4;
	u32	rate		: 2;
	u32	fixed_rxl	: 1;
	u32	slow_mode	: 1;
	u32	mac_addr	: 24;
पूर्ण;

/*
 * CRC-32 stuff
 */
#घोषणा CRC32(c,crc) (crc32tab[((माप_प्रकार)(crc) ^ (c)) & 0xff] ^ (((crc) >> 8) & 0x00FFFFFF))
      /* CRC generator 0xEDB88320 */
      /* CRC reमुख्यder 0x2144DF1C */
      /* CRC initial value 0x00000000 */
#घोषणा CRC32_REMAINDER 0x2144DF1C
#घोषणा CRC32_INITIAL 0x00000000

#अगर_अघोषित __initdata
#घोषणा __initdata
#पूर्ण_अगर

#पूर्ण_अगर

