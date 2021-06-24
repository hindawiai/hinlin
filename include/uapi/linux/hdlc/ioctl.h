<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __HDLC_IOCTL_H__
#घोषणा __HDLC_IOCTL_H__


#घोषणा GENERIC_HDLC_VERSION 4	/* For synchronization with sethdlc utility */

#घोषणा CLOCK_DEFAULT   0	/* Default setting */
#घोषणा CLOCK_EXT	1	/* External TX and RX घड़ी - DTE */
#घोषणा CLOCK_INT	2	/* Internal TX and RX घड़ी - DCE */
#घोषणा CLOCK_TXINT	3	/* Internal TX and बाह्यal RX घड़ी */
#घोषणा CLOCK_TXFROMRX	4	/* TX घड़ी derived from बाह्यal RX घड़ी */


#घोषणा ENCODING_DEFAULT	0 /* Default setting */
#घोषणा ENCODING_NRZ		1
#घोषणा ENCODING_NRZI		2
#घोषणा ENCODING_FM_MARK	3
#घोषणा ENCODING_FM_SPACE	4
#घोषणा ENCODING_MANCHESTER	5


#घोषणा PARITY_DEFAULT		0 /* Default setting */
#घोषणा PARITY_NONE		1 /* No parity */
#घोषणा PARITY_CRC16_PR0	2 /* CRC16, initial value 0x0000 */
#घोषणा PARITY_CRC16_PR1	3 /* CRC16, initial value 0xFFFF */
#घोषणा PARITY_CRC16_PR0_CCITT	4 /* CRC16, initial 0x0000, ITU-T version */
#घोषणा PARITY_CRC16_PR1_CCITT	5 /* CRC16, initial 0xFFFF, ITU-T version */
#घोषणा PARITY_CRC32_PR0_CCITT	6 /* CRC32, initial value 0x00000000 */
#घोषणा PARITY_CRC32_PR1_CCITT	7 /* CRC32, initial value 0xFFFFFFFF */

#घोषणा LMI_DEFAULT		0 /* Default setting */
#घोषणा LMI_NONE		1 /* No LMI, all PVCs are अटल */
#घोषणा LMI_ANSI		2 /* ANSI Annex D */
#घोषणा LMI_CCITT		3 /* ITU-T Annex A */
#घोषणा LMI_CISCO		4 /* The "original" LMI, aka Gang of Four */

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक घड़ी_rate; /* bits per second */
	अचिन्हित पूर्णांक घड़ी_प्रकारype; /* पूर्णांकernal, बाह्यal, TX-पूर्णांकernal etc. */
	अचिन्हित लघु loopback;
पूर्ण sync_serial_settings;          /* V.35, V.24, X.21 */

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक घड़ी_rate; /* bits per second */
	अचिन्हित पूर्णांक घड़ी_प्रकारype; /* पूर्णांकernal, बाह्यal, TX-पूर्णांकernal etc. */
	अचिन्हित लघु loopback;
	अचिन्हित पूर्णांक slot_map;
पूर्ण te1_settings;                  /* T1, E1 */

प्रकार काष्ठा अणु
	अचिन्हित लघु encoding;
	अचिन्हित लघु parity;
पूर्ण raw_hdlc_proto;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक t391;
	अचिन्हित पूर्णांक t392;
	अचिन्हित पूर्णांक n391;
	अचिन्हित पूर्णांक n392;
	अचिन्हित पूर्णांक n393;
	अचिन्हित लघु lmi;
	अचिन्हित लघु dce; /* 1 क्रम DCE (network side) operation */
पूर्ण fr_proto;

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक dlci;
पूर्ण fr_proto_pvc;          /* क्रम creating/deleting FR PVCs */

प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक dlci;
	अक्षर master[IFNAMSIZ];	/* Name of master FRAD device */
पूर्णfr_proto_pvc_info;		/* क्रम वापसing PVC inक्रमmation only */

प्रकार काष्ठा अणु
    अचिन्हित पूर्णांक पूर्णांकerval;
    अचिन्हित पूर्णांक समयout;
पूर्ण cisco_proto;

प्रकार काष्ठा अणु
	अचिन्हित लघु dce; /* 1 क्रम DCE (network side) operation */
	अचिन्हित पूर्णांक modulo; /* modulo (8 = basic / 128 = extended) */
	अचिन्हित पूर्णांक winकरोw; /* frame winकरोw size */
	अचिन्हित पूर्णांक t1; /* समयout t1 */
	अचिन्हित पूर्णांक t2; /* समयout t2 */
	अचिन्हित पूर्णांक n2; /* frame retry counter */
पूर्ण x25_hdlc_proto;

/* PPP करोesn't need any info now - supply length = 0 to ioctl */

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __HDLC_IOCTL_H__ */
