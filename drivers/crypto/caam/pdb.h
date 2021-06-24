<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CAAM Protocol Data Block (PDB) definition header file
 *
 * Copyright 2008-2016 Freescale Semiconductor, Inc.
 *
 */

#अगर_अघोषित CAAM_PDB_H
#घोषणा CAAM_PDB_H
#समावेश "compat.h"

/*
 * PDB- IPSec ESP Header Modअगरication Options
 */
#घोषणा PDBHMO_ESP_DECAP_SHIFT	28
#घोषणा PDBHMO_ESP_ENCAP_SHIFT	28
/*
 * Encap and Decap - Decrement TTL (Hop Limit) - Based on the value of the
 * Options Byte IP version (IPvsn) field:
 * अगर IPv4, decrement the inner IP header TTL field (byte 8);
 * अगर IPv6 decrement the inner IP header Hop Limit field (byte 7).
*/
#घोषणा PDBHMO_ESP_DECAP_DEC_TTL	(0x02 << PDBHMO_ESP_DECAP_SHIFT)
#घोषणा PDBHMO_ESP_ENCAP_DEC_TTL	(0x02 << PDBHMO_ESP_ENCAP_SHIFT)
/*
 * Decap - DअगरfServ Copy - Copy the IPv4 TOS or IPv6 Traffic Class byte
 * from the outer IP header to the inner IP header.
 */
#घोषणा PDBHMO_ESP_DIFFSERV		(0x01 << PDBHMO_ESP_DECAP_SHIFT)
/*
 * Encap- Copy DF bit -अगर an IPv4 tunnel mode outer IP header is coming from
 * the PDB, copy the DF bit from the inner IP header to the outer IP header.
 */
#घोषणा PDBHMO_ESP_DFBIT		(0x04 << PDBHMO_ESP_ENCAP_SHIFT)

#घोषणा PDBNH_ESP_ENCAP_SHIFT		16
#घोषणा PDBNH_ESP_ENCAP_MASK		(0xff << PDBNH_ESP_ENCAP_SHIFT)

#घोषणा PDBHDRLEN_ESP_DECAP_SHIFT	16
#घोषणा PDBHDRLEN_MASK			(0x0fff << PDBHDRLEN_ESP_DECAP_SHIFT)

#घोषणा PDB_NH_OFFSET_SHIFT		8
#घोषणा PDB_NH_OFFSET_MASK		(0xff << PDB_NH_OFFSET_SHIFT)

/*
 * PDB - IPSec ESP Encap/Decap Options
 */
#घोषणा PDBOPTS_ESP_ARSNONE	0x00 /* no antireplay winकरोw */
#घोषणा PDBOPTS_ESP_ARS32	0x40 /* 32-entry antireplay winकरोw */
#घोषणा PDBOPTS_ESP_ARS128	0x80 /* 128-entry antireplay winकरोw */
#घोषणा PDBOPTS_ESP_ARS64	0xc0 /* 64-entry antireplay winकरोw */
#घोषणा PDBOPTS_ESP_ARS_MASK	0xc0 /* antireplay winकरोw mask */
#घोषणा PDBOPTS_ESP_IVSRC	0x20 /* IV comes from पूर्णांकernal अक्रमom gen */
#घोषणा PDBOPTS_ESP_ESN		0x10 /* extended sequence included */
#घोषणा PDBOPTS_ESP_OUTFMT	0x08 /* output only decapsulation (decap) */
#घोषणा PDBOPTS_ESP_IPHDRSRC	0x08 /* IP header comes from PDB (encap) */
#घोषणा PDBOPTS_ESP_INCIPHDR	0x04 /* Prepend IP header to output frame */
#घोषणा PDBOPTS_ESP_IPVSN	0x02 /* process IPv6 header */
#घोषणा PDBOPTS_ESP_AOFL	0x04 /* adjust out frame len (decap, SEC>=5.3)*/
#घोषणा PDBOPTS_ESP_TUNNEL	0x01 /* tunnel mode next-header byte */
#घोषणा PDBOPTS_ESP_IPV6	0x02 /* ip header version is V6 */
#घोषणा PDBOPTS_ESP_DIFFSERV	0x40 /* copy TOS/TC from inner iphdr */
#घोषणा PDBOPTS_ESP_UPDATE_CSUM 0x80 /* encap-update ip header checksum */
#घोषणा PDBOPTS_ESP_VERIFY_CSUM 0x20 /* decap-validate ip header checksum */

/*
 * General IPSec encap/decap PDB definitions
 */

/**
 * ipsec_encap_cbc - PDB part क्रम IPsec CBC encapsulation
 * @iv: 16-byte array initialization vector
 */
काष्ठा ipsec_encap_cbc अणु
	u8 iv[16];
पूर्ण;

/**
 * ipsec_encap_ctr - PDB part क्रम IPsec CTR encapsulation
 * @ctr_nonce: 4-byte array nonce
 * @ctr_initial: initial count स्थिरant
 * @iv: initialization vector
 */
काष्ठा ipsec_encap_ctr अणु
	u8 ctr_nonce[4];
	u32 ctr_initial;
	u64 iv;
पूर्ण;

/**
 * ipsec_encap_ccm - PDB part क्रम IPsec CCM encapsulation
 * @salt: 3-byte array salt (lower 24 bits)
 * @ccm_opt: CCM algorithm options - MSB-LSB description:
 *  b0_flags (8b) - CCM B0; use 0x5B क्रम 8-byte ICV, 0x6B क्रम 12-byte ICV,
 *    0x7B क्रम 16-byte ICV (cf. RFC4309, RFC3610)
 *  ctr_flags (8b) - counter flags; स्थिरant equal to 0x3
 *  ctr_initial (16b) - initial count स्थिरant
 * @iv: initialization vector
 */
काष्ठा ipsec_encap_ccm अणु
	u8 salt[4];
	u32 ccm_opt;
	u64 iv;
पूर्ण;

/**
 * ipsec_encap_gcm - PDB part क्रम IPsec GCM encapsulation
 * @salt: 3-byte array salt (lower 24 bits)
 * @rsvd: reserved, करो not use
 * @iv: initialization vector
 */
काष्ठा ipsec_encap_gcm अणु
	u8 salt[4];
	u32 rsvd1;
	u64 iv;
पूर्ण;

/**
 * ipsec_encap_pdb - PDB क्रम IPsec encapsulation
 * @options: MSB-LSB description
 *  hmo (header manipulation options) - 4b
 *  reserved - 4b
 *  next header - 8b
 *  next header offset - 8b
 *  option flags (depend on selected algorithm) - 8b
 * @seq_num_ext_hi: (optional) IPsec Extended Sequence Number (ESN)
 * @seq_num: IPsec sequence number
 * @spi: IPsec SPI (Security Parameters Index)
 * @ip_hdr_len: optional IP Header length (in bytes)
 *  reserved - 16b
 *  Opt. IP Hdr Len - 16b
 * @ip_hdr: optional IP Header content
 */
काष्ठा ipsec_encap_pdb अणु
	u32 options;
	u32 seq_num_ext_hi;
	u32 seq_num;
	जोड़ अणु
		काष्ठा ipsec_encap_cbc cbc;
		काष्ठा ipsec_encap_ctr ctr;
		काष्ठा ipsec_encap_ccm ccm;
		काष्ठा ipsec_encap_gcm gcm;
	पूर्ण;
	u32 spi;
	u32 ip_hdr_len;
	u32 ip_hdr[0];
पूर्ण;

/**
 * ipsec_decap_cbc - PDB part क्रम IPsec CBC decapsulation
 * @rsvd: reserved, करो not use
 */
काष्ठा ipsec_decap_cbc अणु
	u32 rsvd[2];
पूर्ण;

/**
 * ipsec_decap_ctr - PDB part क्रम IPsec CTR decapsulation
 * @ctr_nonce: 4-byte array nonce
 * @ctr_initial: initial count स्थिरant
 */
काष्ठा ipsec_decap_ctr अणु
	u8 ctr_nonce[4];
	u32 ctr_initial;
पूर्ण;

/**
 * ipsec_decap_ccm - PDB part क्रम IPsec CCM decapsulation
 * @salt: 3-byte salt (lower 24 bits)
 * @ccm_opt: CCM algorithm options - MSB-LSB description:
 *  b0_flags (8b) - CCM B0; use 0x5B क्रम 8-byte ICV, 0x6B क्रम 12-byte ICV,
 *    0x7B क्रम 16-byte ICV (cf. RFC4309, RFC3610)
 *  ctr_flags (8b) - counter flags; स्थिरant equal to 0x3
 *  ctr_initial (16b) - initial count स्थिरant
 */
काष्ठा ipsec_decap_ccm अणु
	u8 salt[4];
	u32 ccm_opt;
पूर्ण;

/**
 * ipsec_decap_gcm - PDB part क्रम IPsec GCN decapsulation
 * @salt: 4-byte salt
 * @rsvd: reserved, करो not use
 */
काष्ठा ipsec_decap_gcm अणु
	u8 salt[4];
	u32 resvd;
पूर्ण;

/**
 * ipsec_decap_pdb - PDB क्रम IPsec decapsulation
 * @options: MSB-LSB description
 *  hmo (header manipulation options) - 4b
 *  IP header length - 12b
 *  next header offset - 8b
 *  option flags (depend on selected algorithm) - 8b
 * @seq_num_ext_hi: (optional) IPsec Extended Sequence Number (ESN)
 * @seq_num: IPsec sequence number
 * @anti_replay: Anti-replay winकरोw; size depends on ARS (option flags)
 */
काष्ठा ipsec_decap_pdb अणु
	u32 options;
	जोड़ अणु
		काष्ठा ipsec_decap_cbc cbc;
		काष्ठा ipsec_decap_ctr ctr;
		काष्ठा ipsec_decap_ccm ccm;
		काष्ठा ipsec_decap_gcm gcm;
	पूर्ण;
	u32 seq_num_ext_hi;
	u32 seq_num;
	__be32 anti_replay[4];
पूर्ण;

/*
 * IPSec ESP Datapath Protocol Override Register (DPOVRD)
 */
काष्ठा ipsec_deco_dpovrd अणु
#घोषणा IPSEC_ENCAP_DECO_DPOVRD_USE 0x80
	u8 ovrd_ecn;
	u8 ip_hdr_len;
	u8 nh_offset;
	u8 next_header; /* reserved अगर decap */
पूर्ण;

/*
 * IEEE 802.11i WiFi Protocol Data Block
 */
#घोषणा WIFI_PDBOPTS_FCS	0x01
#घोषणा WIFI_PDBOPTS_AR		0x40

काष्ठा wअगरi_encap_pdb अणु
	u16 mac_hdr_len;
	u8 rsvd;
	u8 options;
	u8 iv_flags;
	u8 pri;
	u16 pn1;
	u32 pn2;
	u16 frm_ctrl_mask;
	u16 seq_ctrl_mask;
	u8 rsvd1[2];
	u8 cnst;
	u8 key_id;
	u8 ctr_flags;
	u8 rsvd2;
	u16 ctr_init;
पूर्ण;

काष्ठा wअगरi_decap_pdb अणु
	u16 mac_hdr_len;
	u8 rsvd;
	u8 options;
	u8 iv_flags;
	u8 pri;
	u16 pn1;
	u32 pn2;
	u16 frm_ctrl_mask;
	u16 seq_ctrl_mask;
	u8 rsvd1[4];
	u8 ctr_flags;
	u8 rsvd2;
	u16 ctr_init;
पूर्ण;

/*
 * IEEE 802.16 WiMAX Protocol Data Block
 */
#घोषणा WIMAX_PDBOPTS_FCS	0x01
#घोषणा WIMAX_PDBOPTS_AR	0x40 /* decap only */

काष्ठा wimax_encap_pdb अणु
	u8 rsvd[3];
	u8 options;
	u32 nonce;
	u8 b0_flags;
	u8 ctr_flags;
	u16 ctr_init;
	/* begin DECO ग_लिखोback region */
	u32 pn;
	/* end DECO ग_लिखोback region */
पूर्ण;

काष्ठा wimax_decap_pdb अणु
	u8 rsvd[3];
	u8 options;
	u32 nonce;
	u8 iv_flags;
	u8 ctr_flags;
	u16 ctr_init;
	/* begin DECO ग_लिखोback region */
	u32 pn;
	u8 rsvd1[2];
	u16 antireplay_len;
	u64 antireplay_scorecard;
	/* end DECO ग_लिखोback region */
पूर्ण;

/*
 * IEEE 801.AE MacSEC Protocol Data Block
 */
#घोषणा MACSEC_PDBOPTS_FCS	0x01
#घोषणा MACSEC_PDBOPTS_AR	0x40 /* used in decap only */

काष्ठा macsec_encap_pdb अणु
	u16 aad_len;
	u8 rsvd;
	u8 options;
	u64 sci;
	u16 ethertype;
	u8 tci_an;
	u8 rsvd1;
	/* begin DECO ग_लिखोback region */
	u32 pn;
	/* end DECO ग_लिखोback region */
पूर्ण;

काष्ठा macsec_decap_pdb अणु
	u16 aad_len;
	u8 rsvd;
	u8 options;
	u64 sci;
	u8 rsvd1[3];
	/* begin DECO ग_लिखोback region */
	u8 antireplay_len;
	u32 pn;
	u64 antireplay_scorecard;
	/* end DECO ग_लिखोback region */
पूर्ण;

/*
 * SSL/TLS/DTLS Protocol Data Blocks
 */

#घोषणा TLS_PDBOPTS_ARS32	0x40
#घोषणा TLS_PDBOPTS_ARS64	0xc0
#घोषणा TLS_PDBOPTS_OUTFMT	0x08
#घोषणा TLS_PDBOPTS_IV_WRTBK	0x02 /* 1.1/1.2/DTLS only */
#घोषणा TLS_PDBOPTS_EXP_RND_IV	0x01 /* 1.1/1.2/DTLS only */

काष्ठा tls_block_encap_pdb अणु
	u8 type;
	u8 version[2];
	u8 options;
	u64 seq_num;
	u32 iv[4];
पूर्ण;

काष्ठा tls_stream_encap_pdb अणु
	u8 type;
	u8 version[2];
	u8 options;
	u64 seq_num;
	u8 i;
	u8 j;
	u8 rsvd1[2];
पूर्ण;

काष्ठा dtls_block_encap_pdb अणु
	u8 type;
	u8 version[2];
	u8 options;
	u16 epoch;
	u16 seq_num[3];
	u32 iv[4];
पूर्ण;

काष्ठा tls_block_decap_pdb अणु
	u8 rsvd[3];
	u8 options;
	u64 seq_num;
	u32 iv[4];
पूर्ण;

काष्ठा tls_stream_decap_pdb अणु
	u8 rsvd[3];
	u8 options;
	u64 seq_num;
	u8 i;
	u8 j;
	u8 rsvd1[2];
पूर्ण;

काष्ठा dtls_block_decap_pdb अणु
	u8 rsvd[3];
	u8 options;
	u16 epoch;
	u16 seq_num[3];
	u32 iv[4];
	u64 antireplay_scorecard;
पूर्ण;

/*
 * SRTP Protocol Data Blocks
 */
#घोषणा SRTP_PDBOPTS_MKI	0x08
#घोषणा SRTP_PDBOPTS_AR		0x40

काष्ठा srtp_encap_pdb अणु
	u8 x_len;
	u8 mki_len;
	u8 n_tag;
	u8 options;
	u32 cnst0;
	u8 rsvd[2];
	u16 cnst1;
	u16 salt[7];
	u16 cnst2;
	u32 rsvd1;
	u32 roc;
	u32 opt_mki;
पूर्ण;

काष्ठा srtp_decap_pdb अणु
	u8 x_len;
	u8 mki_len;
	u8 n_tag;
	u8 options;
	u32 cnst0;
	u8 rsvd[2];
	u16 cnst1;
	u16 salt[7];
	u16 cnst2;
	u16 rsvd1;
	u16 seq_num;
	u32 roc;
	u64 antireplay_scorecard;
पूर्ण;

/*
 * DSA/ECDSA Protocol Data Blocks
 * Two of these exist: DSA-SIGN, and DSA-VERIFY. They are similar
 * except क्रम the treaपंचांगent of "w" क्रम verअगरy, "s" क्रम sign,
 * and the placement of "a,b".
 */
#घोषणा DSA_PDB_SGF_SHIFT	24
#घोषणा DSA_PDB_SGF_MASK	(0xff << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_Q		(0x80 << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_R		(0x40 << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_G		(0x20 << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_W		(0x10 << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_S		(0x10 << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_F		(0x08 << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_C		(0x04 << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_D		(0x02 << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_AB_SIGN	(0x02 << DSA_PDB_SGF_SHIFT)
#घोषणा DSA_PDB_SGF_AB_VERIFY	(0x01 << DSA_PDB_SGF_SHIFT)

#घोषणा DSA_PDB_L_SHIFT		7
#घोषणा DSA_PDB_L_MASK		(0x3ff << DSA_PDB_L_SHIFT)

#घोषणा DSA_PDB_N_MASK		0x7f

काष्ठा dsa_sign_pdb अणु
	u32 sgf_ln; /* Use DSA_PDB_ definitions per above */
	u8 *q;
	u8 *r;
	u8 *g;	/* or Gx,y */
	u8 *s;
	u8 *f;
	u8 *c;
	u8 *d;
	u8 *ab; /* ECC only */
	u8 *u;
पूर्ण;

काष्ठा dsa_verअगरy_pdb अणु
	u32 sgf_ln;
	u8 *q;
	u8 *r;
	u8 *g;	/* or Gx,y */
	u8 *w; /* or Wx,y */
	u8 *f;
	u8 *c;
	u8 *d;
	u8 *पंचांगp; /* temporary data block */
	u8 *ab; /* only used अगर ECC processing */
पूर्ण;

/* RSA Protocol Data Block */
#घोषणा RSA_PDB_SGF_SHIFT       28
#घोषणा RSA_PDB_E_SHIFT         12
#घोषणा RSA_PDB_E_MASK          (0xFFF << RSA_PDB_E_SHIFT)
#घोषणा RSA_PDB_D_SHIFT         12
#घोषणा RSA_PDB_D_MASK          (0xFFF << RSA_PDB_D_SHIFT)
#घोषणा RSA_PDB_Q_SHIFT         12
#घोषणा RSA_PDB_Q_MASK          (0xFFF << RSA_PDB_Q_SHIFT)

#घोषणा RSA_PDB_SGF_F           (0x8 << RSA_PDB_SGF_SHIFT)
#घोषणा RSA_PDB_SGF_G           (0x4 << RSA_PDB_SGF_SHIFT)
#घोषणा RSA_PRIV_PDB_SGF_F      (0x4 << RSA_PDB_SGF_SHIFT)
#घोषणा RSA_PRIV_PDB_SGF_G      (0x8 << RSA_PDB_SGF_SHIFT)

#घोषणा RSA_PRIV_KEY_FRM_1      0
#घोषणा RSA_PRIV_KEY_FRM_2      1
#घोषणा RSA_PRIV_KEY_FRM_3      2

/**
 * RSA Encrypt Protocol Data Block
 * @sgf: scatter-gather field
 * @f_dma: dma address of input data
 * @g_dma: dma address of encrypted output data
 * @n_dma: dma address of RSA modulus
 * @e_dma: dma address of RSA खुला exponent
 * @f_len: length in octets of the input data
 */
काष्ठा rsa_pub_pdb अणु
	u32		sgf;
	dma_addr_t	f_dma;
	dma_addr_t	g_dma;
	dma_addr_t	n_dma;
	dma_addr_t	e_dma;
	u32		f_len;
पूर्ण;

#घोषणा SIZखातापूर्ण_RSA_PUB_PDB	(2 * माप(u32) + 4 * caam_ptr_sz)

/**
 * RSA Decrypt PDB - Private Key Form #1
 * @sgf: scatter-gather field
 * @g_dma: dma address of encrypted input data
 * @f_dma: dma address of output data
 * @n_dma: dma address of RSA modulus
 * @d_dma: dma address of RSA निजी exponent
 */
काष्ठा rsa_priv_f1_pdb अणु
	u32		sgf;
	dma_addr_t	g_dma;
	dma_addr_t	f_dma;
	dma_addr_t	n_dma;
	dma_addr_t	d_dma;
पूर्ण;

#घोषणा SIZखातापूर्ण_RSA_PRIV_F1_PDB	(माप(u32) + 4 * caam_ptr_sz)

/**
 * RSA Decrypt PDB - Private Key Form #2
 * @sgf     : scatter-gather field
 * @g_dma   : dma address of encrypted input data
 * @f_dma   : dma address of output data
 * @d_dma   : dma address of RSA निजी exponent
 * @p_dma   : dma address of RSA prime factor p of RSA modulus n
 * @q_dma   : dma address of RSA prime factor q of RSA modulus n
 * @पंचांगp1_dma: dma address of temporary buffer. CAAM uses this temporary buffer
 *            as पूर्णांकernal state buffer. It is assumed to be as दीर्घ as p.
 * @पंचांगp2_dma: dma address of temporary buffer. CAAM uses this temporary buffer
 *            as पूर्णांकernal state buffer. It is assumed to be as दीर्घ as q.
 * @p_q_len : length in bytes of first two prime factors of the RSA modulus n
 */
काष्ठा rsa_priv_f2_pdb अणु
	u32		sgf;
	dma_addr_t	g_dma;
	dma_addr_t	f_dma;
	dma_addr_t	d_dma;
	dma_addr_t	p_dma;
	dma_addr_t	q_dma;
	dma_addr_t	पंचांगp1_dma;
	dma_addr_t	पंचांगp2_dma;
	u32		p_q_len;
पूर्ण;

#घोषणा SIZखातापूर्ण_RSA_PRIV_F2_PDB	(2 * माप(u32) + 7 * caam_ptr_sz)

/**
 * RSA Decrypt PDB - Private Key Form #3
 * This is the RSA Chinese Reminder Theorem (CRT) क्रमm क्रम two prime factors of
 * the RSA modulus.
 * @sgf     : scatter-gather field
 * @g_dma   : dma address of encrypted input data
 * @f_dma   : dma address of output data
 * @c_dma   : dma address of RSA CRT coefficient
 * @p_dma   : dma address of RSA prime factor p of RSA modulus n
 * @q_dma   : dma address of RSA prime factor q of RSA modulus n
 * @dp_dma  : dma address of RSA CRT exponent of RSA prime factor p
 * @dp_dma  : dma address of RSA CRT exponent of RSA prime factor q
 * @पंचांगp1_dma: dma address of temporary buffer. CAAM uses this temporary buffer
 *            as पूर्णांकernal state buffer. It is assumed to be as दीर्घ as p.
 * @पंचांगp2_dma: dma address of temporary buffer. CAAM uses this temporary buffer
 *            as पूर्णांकernal state buffer. It is assumed to be as दीर्घ as q.
 * @p_q_len : length in bytes of first two prime factors of the RSA modulus n
 */
काष्ठा rsa_priv_f3_pdb अणु
	u32		sgf;
	dma_addr_t	g_dma;
	dma_addr_t	f_dma;
	dma_addr_t	c_dma;
	dma_addr_t	p_dma;
	dma_addr_t	q_dma;
	dma_addr_t	dp_dma;
	dma_addr_t	dq_dma;
	dma_addr_t	पंचांगp1_dma;
	dma_addr_t	पंचांगp2_dma;
	u32		p_q_len;
पूर्ण;

#घोषणा SIZखातापूर्ण_RSA_PRIV_F3_PDB	(2 * माप(u32) + 9 * caam_ptr_sz)

#पूर्ण_अगर
