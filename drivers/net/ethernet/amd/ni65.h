<शैली गुरु>
/* am7990 (lance) definitions
 *
 * This is an extension to the Linux operating प्रणाली, and is covered by
 * same GNU General Public License that covers that work.
 *
 * Michael Hipp
 * email: mhipp@student.uni-tuebingen.de
 *
 * sources: (mail me or ask archie अगर you need them)
 *    crynwr-packet-driver
 */

/*
 * 	Control and Status Register 0 (CSR0) bit definitions
 * (R=Readable) (W=Writeable) (S=Set on ग_लिखो) (C-Clear on ग_लिखो)
 *
 */

#घोषणा CSR0_ERR	0x8000	/* Error summary (R) */
#घोषणा CSR0_BABL	0x4000	/* Babble transmitter समयout error (RC) */
#घोषणा CSR0_CERR	0x2000	/* Collision Error (RC) */
#घोषणा CSR0_MISS	0x1000	/* Missed packet (RC) */
#घोषणा CSR0_MERR	0x0800	/* Memory Error (RC) */
#घोषणा CSR0_RINT	0x0400	/* Receiver Interrupt (RC) */
#घोषणा CSR0_TINT       0x0200	/* Transmit Interrupt (RC) */
#घोषणा CSR0_IDON	0x0100	/* Initialization Done (RC) */
#घोषणा CSR0_INTR	0x0080	/* Interrupt Flag (R) */
#घोषणा CSR0_INEA	0x0040	/* Interrupt Enable (RW) */
#घोषणा CSR0_RXON	0x0020	/* Receiver on (R) */
#घोषणा CSR0_TXON	0x0010	/* Transmitter on (R) */
#घोषणा CSR0_TDMD	0x0008	/* Transmit Demand (RS) */
#घोषणा CSR0_STOP	0x0004	/* Stop (RS) */
#घोषणा CSR0_STRT	0x0002	/* Start (RS) */
#घोषणा CSR0_INIT	0x0001	/* Initialize (RS) */

#घोषणा CSR0_CLRALL    0x7f00	/* mask क्रम all clearable bits */
/*
 *	Initialization Block  Mode operation Bit Definitions.
 */

#घोषणा M_PROM		0x8000	/* Promiscuous Mode */
#घोषणा M_INTL		0x0040	/* Internal Loopback */
#घोषणा M_DRTY		0x0020	/* Disable Retry */
#घोषणा M_COLL		0x0010	/* Force Collision */
#घोषणा M_DTCR		0x0008	/* Disable Transmit CRC) */
#घोषणा M_LOOP		0x0004	/* Loopback */
#घोषणा M_DTX		0x0002	/* Disable the Transmitter */
#घोषणा M_DRX		0x0001	/* Disable the Receiver */


/*
 * 	Receive message descriptor bit definitions.
 */

#घोषणा RCV_OWN		0x80	/* owner bit 0 = host, 1 = lance */
#घोषणा RCV_ERR		0x40	/* Error Summary */
#घोषणा RCV_FRAM	0x20	/* Framing Error */
#घोषणा RCV_OFLO	0x10	/* Overflow Error */
#घोषणा RCV_CRC		0x08	/* CRC Error */
#घोषणा RCV_BUF_ERR	0x04	/* Buffer Error */
#घोषणा RCV_START	0x02	/* Start of Packet */
#घोषणा RCV_END		0x01	/* End of Packet */


/*
 *	Transmit  message descriptor bit definitions.
 */

#घोषणा XMIT_OWN	0x80	/* owner bit 0 = host, 1 = lance */
#घोषणा XMIT_ERR	0x40	/* Error Summary */
#घोषणा XMIT_RETRY	0x10	/* more the 1 retry needed to Xmit */
#घोषणा XMIT_1_RETRY	0x08	/* one retry needed to Xmit */
#घोषणा XMIT_DEF	0x04	/* Deferred */
#घोषणा XMIT_START	0x02	/* Start of Packet */
#घोषणा XMIT_END	0x01	/* End of Packet */

/*
 * transmit status (2) (valid अगर XMIT_ERR == 1)
 */

#घोषणा XMIT_TDRMASK    0x03ff	/* समय-करोमुख्य-reflectometer-value */
#घोषणा XMIT_RTRY 	0x0400	/* Failed after 16 retransmissions  */
#घोषणा XMIT_LCAR 	0x0800	/* Loss of Carrier */
#घोषणा XMIT_LCOL 	0x1000	/* Late collision */
#घोषणा XMIT_RESERV 	0x2000	/* Reserved */
#घोषणा XMIT_UFLO 	0x4000	/* Underflow (late memory) */
#घोषणा XMIT_BUFF 	0x8000	/* Buffering error (no ENP) */

काष्ठा init_block अणु
	अचिन्हित लघु mode;
	अचिन्हित अक्षर eaddr[6];
	अचिन्हित अक्षर filter[8];
	/* bit 29-31: number of rmd's (घातer of 2) */
	u32 rrp;		/* receive ring poपूर्णांकer (align 8) */
	/* bit 29-31: number of पंचांगd's (घातer of 2) */
	u32 trp;		/* transmit ring poपूर्णांकer (align 8) */
पूर्ण;

काष्ठा rmd अणु			/* Receive Message Descriptor */
	जोड़ अणु
		अस्थिर u32 buffer;
		काष्ठा अणु
			अस्थिर अचिन्हित अक्षर dummy[3];
			अस्थिर अचिन्हित अक्षर status;
		पूर्ण s;
	पूर्ण u;
	अस्थिर लघु blen;
	अस्थिर अचिन्हित लघु mlen;
पूर्ण;

काष्ठा पंचांगd अणु
	जोड़ अणु
		अस्थिर u32 buffer;
		काष्ठा अणु
			अस्थिर अचिन्हित अक्षर dummy[3];
			अस्थिर अचिन्हित अक्षर status;
		पूर्ण s;
	पूर्ण u;
	अस्थिर अचिन्हित लघु blen;
	अस्थिर अचिन्हित लघु status2;
पूर्ण;
