<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */
#अगर_अघोषित _FC_ENCAPS_H_
#घोषणा _FC_ENCAPS_H_

/*
 * Protocol definitions from RFC 3643 - Fibre Channel Frame Encapsulation.
 *
 * Note:  The frame length field is the number of 32-bit words in
 * the encapsulation including the fcip_encaps_header, CRC and खातापूर्ण words.
 * The minimum frame length value in bytes is (32 + 24 + 4 + 4) * 4 = 64.
 * The maximum frame length value in bytes is (32 + 24 + 2112 + 4 + 4) = 2172.
 */
#घोषणा FC_ENCAPS_MIN_FRAME_LEN 64	/* min frame len (bytes) (see above) */
#घोषणा FC_ENCAPS_MAX_FRAME_LEN (FC_ENCAPS_MIN_FRAME_LEN + FC_MAX_PAYLOAD)

#घोषणा FC_ENCAPS_VER       1           /* current version number */

काष्ठा fc_encaps_hdr अणु
	__u8	fc_proto;	/* protocol number */
	__u8	fc_ver;		/* version of encapsulation */
	__u8	fc_proto_n;	/* ones complement of protocol */
	__u8	fc_ver_n;	/* ones complement of version */

	अचिन्हित अक्षर fc_proto_data[8]; /* protocol specअगरic data */

	__be16	fc_len_flags;	/* 10-bit length/4 w/ 6 flag bits */
	__be16	fc_len_flags_n;	/* ones complement of length / flags */

	/*
	 * Offset 0x10
	 */
	__be32	fc_समय[2];	/* समय stamp: seconds and fraction */
	__be32	fc_crc;		/* CRC */
	__be32	fc_sof;		/* start of frame (see FC_SOF below) */

	/* 0x20 - FC frame content followed by खातापूर्ण word */
पूर्ण;

#घोषणा FCIP_ENCAPS_HDR_LEN 0x20	/* expected length क्रम निश्चितs */

/*
 * Macro's क्रम making redundant copies of खातापूर्ण and SOF.
 */
#घोषणा FC_XY(x, y)		((((x) & 0xff) << 8) | ((y) & 0xff))
#घोषणा FC_XYXY(x, y)		((FCIP_XY(x, y) << 16) | FCIP_XY(x, y))
#घोषणा FC_XYNN(x, y)		(FCIP_XYXY(x, y) ^ 0xffff)

#घोषणा FC_SOF_ENCODE(n)	FC_XYNN(n, n)
#घोषणा FC_खातापूर्ण_ENCODE(n)	FC_XYNN(n, n)

/*
 * SOF / खातापूर्ण bytes.
 */
क्रमागत fc_sof अणु
	FC_SOF_F =	0x28,	/* fabric */
	FC_SOF_I4 =	0x29,	/* initiate class 4 */
	FC_SOF_I2 =	0x2d,	/* initiate class 2 */
	FC_SOF_I3 =	0x2e,	/* initiate class 3 */
	FC_SOF_N4 =	0x31,	/* normal class 4 */
	FC_SOF_N2 =	0x35,	/* normal class 2 */
	FC_SOF_N3 =	0x36,	/* normal class 3 */
	FC_SOF_C4 =	0x39,	/* activate class 4 */
पूर्ण __attribute__((packed));

क्रमागत fc_eof अणु
	FC_खातापूर्ण_N =	0x41,	/* normal (not last frame of seq) */
	FC_खातापूर्ण_T =	0x42,	/* terminate (last frame of sequence) */
	FC_खातापूर्ण_RT =	0x44,
	FC_खातापूर्ण_DT =	0x46,	/* disconnect-terminate class-1 */
	FC_खातापूर्ण_NI =	0x49,	/* normal-invalid */
	FC_खातापूर्ण_DTI =	0x4e,	/* disconnect-terminate-invalid */
	FC_खातापूर्ण_RTI =	0x4f,
	FC_खातापूर्ण_A =	0x50,	/* पात */
पूर्ण __attribute__((packed));

#घोषणा FC_SOF_CLASS_MASK 0x06	/* mask क्रम class of service in SOF */

/*
 * Define classes in terms of the SOF code (initial).
 */
क्रमागत fc_class अणु
	FC_CLASS_NONE = 0,	/* software value indicating no class */
	FC_CLASS_2 =	FC_SOF_I2,
	FC_CLASS_3 =	FC_SOF_I3,
	FC_CLASS_4 =	FC_SOF_I4,
	FC_CLASS_F =	FC_SOF_F,
पूर्ण;

/*
 * Determine whether SOF code indicates the need क्रम a BLS ACK.
 */
अटल अंतरभूत पूर्णांक fc_sof_needs_ack(क्रमागत fc_sof sof)
अणु
	वापस (~sof) & 0x02;	/* true क्रम class 1, 2, 4, 6, or F */
पूर्ण

/*
 * Given an fc_class, वापस the normal (non-initial) SOF value.
 */
अटल अंतरभूत क्रमागत fc_sof fc_sof_normal(क्रमागत fc_class class)
अणु
	वापस class + FC_SOF_N3 - FC_SOF_I3;	/* dअगरf is always 8 */
पूर्ण

/*
 * Compute class from SOF value.
 */
अटल अंतरभूत क्रमागत fc_class fc_sof_class(क्रमागत fc_sof sof)
अणु
	वापस (sof & 0x7) | FC_SOF_F;
पूर्ण

/*
 * Determine whether SOF is क्रम the initial frame of a sequence.
 */
अटल अंतरभूत पूर्णांक fc_sof_is_init(क्रमागत fc_sof sof)
अणु
	वापस sof < 0x30;
पूर्ण

#पूर्ण_अगर /* _FC_ENCAPS_H_ */
