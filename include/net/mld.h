<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_MLD_H
#घोषणा LINUX_MLD_H

#समावेश <linux/in6.h>
#समावेश <linux/icmpv6.h>

/* MLDv1 Query/Report/Done */
काष्ठा mld_msg अणु
	काष्ठा icmp6hdr		mld_hdr;
	काष्ठा in6_addr		mld_mca;
पूर्ण;

#घोषणा mld_type		mld_hdr.icmp6_type
#घोषणा mld_code		mld_hdr.icmp6_code
#घोषणा mld_cksum		mld_hdr.icmp6_cksum
#घोषणा mld_maxdelay		mld_hdr.icmp6_maxdelay
#घोषणा mld_reserved		mld_hdr.icmp6_dataun.un_data16[1]

/* Multicast Listener Discovery version 2 headers */
/* MLDv2 Report */
काष्ठा mld2_grec अणु
	__u8		grec_type;
	__u8		grec_auxwords;
	__be16		grec_nsrcs;
	काष्ठा in6_addr	grec_mca;
	काष्ठा in6_addr	grec_src[];
पूर्ण;

काष्ठा mld2_report अणु
	काष्ठा icmp6hdr		mld2r_hdr;
	काष्ठा mld2_grec	mld2r_grec[];
पूर्ण;

#घोषणा mld2r_type		mld2r_hdr.icmp6_type
#घोषणा mld2r_resv1		mld2r_hdr.icmp6_code
#घोषणा mld2r_cksum		mld2r_hdr.icmp6_cksum
#घोषणा mld2r_resv2		mld2r_hdr.icmp6_dataun.un_data16[0]
#घोषणा mld2r_ngrec		mld2r_hdr.icmp6_dataun.un_data16[1]

/* MLDv2 Query */
काष्ठा mld2_query अणु
	काष्ठा icmp6hdr		mld2q_hdr;
	काष्ठा in6_addr		mld2q_mca;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8			mld2q_qrv:3,
				mld2q_suppress:1,
				mld2q_resv2:4;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8			mld2q_resv2:4,
				mld2q_suppress:1,
				mld2q_qrv:3;
#अन्यथा
#त्रुटि "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__u8			mld2q_qqic;
	__be16			mld2q_nsrcs;
	काष्ठा in6_addr		mld2q_srcs[];
पूर्ण;

#घोषणा mld2q_type		mld2q_hdr.icmp6_type
#घोषणा mld2q_code		mld2q_hdr.icmp6_code
#घोषणा mld2q_cksum		mld2q_hdr.icmp6_cksum
#घोषणा mld2q_mrc		mld2q_hdr.icmp6_maxdelay
#घोषणा mld2q_resv1		mld2q_hdr.icmp6_dataun.un_data16[1]

/* RFC3810, 5.1.3. Maximum Response Code:
 *
 * If Maximum Response Code >= 32768, Maximum Response Code represents a
 * भग्नing-poपूर्णांक value as follows:
 *
 *  0 1 2 3 4 5 6 7 8 9 A B C D E F
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1| exp |          mant         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#घोषणा MLDV2_MRC_EXP(value)	(((value) >> 12) & 0x0007)
#घोषणा MLDV2_MRC_MAN(value)	((value) & 0x0fff)

/* RFC3810, 5.1.9. QQIC (Querier's Query Interval Code):
 *
 * If QQIC >= 128, QQIC represents a भग्नing-poपूर्णांक value as follows:
 *
 *  0 1 2 3 4 5 6 7
 * +-+-+-+-+-+-+-+-+
 * |1| exp | mant  |
 * +-+-+-+-+-+-+-+-+
 */
#घोषणा MLDV2_QQIC_EXP(value)	(((value) >> 4) & 0x07)
#घोषणा MLDV2_QQIC_MAN(value)	((value) & 0x0f)

#घोषणा MLD_EXP_MIN_LIMIT	32768UL
#घोषणा MLDV1_MRD_MAX_COMPAT	(MLD_EXP_MIN_LIMIT - 1)

#घोषणा MLD_MAX_QUEUE		8
#घोषणा MLD_MAX_SKBS		32

अटल अंतरभूत अचिन्हित दीर्घ mldv2_mrc(स्थिर काष्ठा mld2_query *mlh2)
अणु
	/* RFC3810, 5.1.3. Maximum Response Code */
	अचिन्हित दीर्घ ret, mc_mrc = ntohs(mlh2->mld2q_mrc);

	अगर (mc_mrc < MLD_EXP_MIN_LIMIT) अणु
		ret = mc_mrc;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ mc_man, mc_exp;

		mc_exp = MLDV2_MRC_EXP(mc_mrc);
		mc_man = MLDV2_MRC_MAN(mc_mrc);

		ret = (mc_man | 0x1000) << (mc_exp + 3);
	पूर्ण

	वापस ret;
पूर्ण

#पूर्ण_अगर
