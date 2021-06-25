<शैली गुरु>
/* Copyright 2008 - 2016 Freescale Semiconductor, Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __FSL_QMAN_H
#घोषणा __FSL_QMAN_H

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>

/* Hardware स्थिरants */
#घोषणा QM_CHANNEL_SWPORTAL0 0
#घोषणा QMAN_CHANNEL_POOL1 0x21
#घोषणा QMAN_CHANNEL_CAAM 0x80
#घोषणा QMAN_CHANNEL_POOL1_REV3 0x401
#घोषणा QMAN_CHANNEL_CAAM_REV3 0x840
बाह्य u16 qm_channel_pool1;
बाह्य u16 qm_channel_caam;

/* Portal processing (पूर्णांकerrupt) sources */
#घोषणा QM_PIRQ_CSCI	0x00100000	/* Congestion State Change */
#घोषणा QM_PIRQ_EQCI	0x00080000	/* Enqueue Command Committed */
#घोषणा QM_PIRQ_EQRI	0x00040000	/* EQCR Ring (below threshold) */
#घोषणा QM_PIRQ_DQRI	0x00020000	/* DQRR Ring (non-empty) */
#घोषणा QM_PIRQ_MRI	0x00010000	/* MR Ring (non-empty) */
/*
 * This mask contains all the पूर्णांकerrupt sources that need handling except DQRI,
 * ie. that अगर present should trigger slow-path processing.
 */
#घोषणा QM_PIRQ_SLOW	(QM_PIRQ_CSCI | QM_PIRQ_EQCI | QM_PIRQ_EQRI | \
			 QM_PIRQ_MRI)

/* For qman_अटल_dequeue_*** APIs */
#घोषणा QM_SDQCR_CHANNELS_POOL_MASK	0x00007fff
/* क्रम n in [1,15] */
#घोषणा QM_SDQCR_CHANNELS_POOL(n)	(0x00008000 >> (n))
/* क्रम conversion from n of qm_channel */
अटल अंतरभूत u32 QM_SDQCR_CHANNELS_POOL_CONV(u16 channel)
अणु
	वापस QM_SDQCR_CHANNELS_POOL(channel + 1 - qm_channel_pool1);
पूर्ण

/* --- QMan data काष्ठाures (and associated स्थिरants) --- */

/* "Frame Descriptor (FD)" */
काष्ठा qm_fd अणु
	जोड़ अणु
		काष्ठा अणु
			u8 cfg8b_w1;
			u8 bpid;	/* Buffer Pool ID */
			u8 cfg8b_w3;
			u8 addr_hi;	/* high 8-bits of 40-bit address */
			__be32 addr_lo;	/* low 32-bits of 40-bit address */
		पूर्ण __packed;
		__be64 data;
	पूर्ण;
	__be32 cfg;	/* क्रमmat, offset, length / congestion */
	जोड़ अणु
		__be32 cmd;
		__be32 status;
	पूर्ण;
पूर्ण __aligned(8);

#घोषणा QM_FD_FORMAT_SG		BIT(31)
#घोषणा QM_FD_FORMAT_LONG	BIT(30)
#घोषणा QM_FD_FORMAT_COMPOUND	BIT(29)
#घोषणा QM_FD_FORMAT_MASK	GENMASK(31, 29)
#घोषणा QM_FD_OFF_SHIFT		20
#घोषणा QM_FD_OFF_MASK		GENMASK(28, 20)
#घोषणा QM_FD_LEN_MASK		GENMASK(19, 0)
#घोषणा QM_FD_LEN_BIG_MASK	GENMASK(28, 0)

क्रमागत qm_fd_क्रमmat अणु
	/*
	 * 'contig' implies a contiguous buffer, whereas 'sg' implies a
	 * scatter-gather table. 'big' implies a 29-bit length with no offset
	 * field, otherwise length is 20-bit and offset is 9-bit. 'compound'
	 * implies a s/g-like table, where each entry itself represents a frame
	 * (contiguous or scatter-gather) and the 29-bit "length" is
	 * पूर्णांकerpreted purely क्रम congestion calculations, ie. a "congestion
	 * weight".
	 */
	qm_fd_contig = 0,
	qm_fd_contig_big = QM_FD_FORMAT_LONG,
	qm_fd_sg = QM_FD_FORMAT_SG,
	qm_fd_sg_big = QM_FD_FORMAT_SG | QM_FD_FORMAT_LONG,
	qm_fd_compound = QM_FD_FORMAT_COMPOUND
पूर्ण;

अटल अंतरभूत dma_addr_t qm_fd_addr(स्थिर काष्ठा qm_fd *fd)
अणु
	वापस be64_to_cpu(fd->data) & 0xffffffffffLLU;
पूर्ण

अटल अंतरभूत u64 qm_fd_addr_get64(स्थिर काष्ठा qm_fd *fd)
अणु
	वापस be64_to_cpu(fd->data) & 0xffffffffffLLU;
पूर्ण

अटल अंतरभूत व्योम qm_fd_addr_set64(काष्ठा qm_fd *fd, u64 addr)
अणु
	fd->addr_hi = upper_32_bits(addr);
	fd->addr_lo = cpu_to_be32(lower_32_bits(addr));
पूर्ण

/*
 * The 'format' field indicates the पूर्णांकerpretation of the reमुख्यing
 * 29 bits of the 32-bit word.
 * If 'format' is _contig or _sg, 20b length and 9b offset.
 * If 'format' is _contig_big or _sg_big, 29b length.
 * If 'format' is _compound, 29b "congestion weight".
 */
अटल अंतरभूत क्रमागत qm_fd_क्रमmat qm_fd_get_क्रमmat(स्थिर काष्ठा qm_fd *fd)
अणु
	वापस be32_to_cpu(fd->cfg) & QM_FD_FORMAT_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक qm_fd_get_offset(स्थिर काष्ठा qm_fd *fd)
अणु
	वापस (be32_to_cpu(fd->cfg) & QM_FD_OFF_MASK) >> QM_FD_OFF_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक qm_fd_get_length(स्थिर काष्ठा qm_fd *fd)
अणु
	वापस be32_to_cpu(fd->cfg) & QM_FD_LEN_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक qm_fd_get_len_big(स्थिर काष्ठा qm_fd *fd)
अणु
	वापस be32_to_cpu(fd->cfg) & QM_FD_LEN_BIG_MASK;
पूर्ण

अटल अंतरभूत व्योम qm_fd_set_param(काष्ठा qm_fd *fd, क्रमागत qm_fd_क्रमmat fmt,
				   पूर्णांक off, पूर्णांक len)
अणु
	fd->cfg = cpu_to_be32(fmt | (len & QM_FD_LEN_BIG_MASK) |
			      ((off << QM_FD_OFF_SHIFT) & QM_FD_OFF_MASK));
पूर्ण

#घोषणा qm_fd_set_contig(fd, off, len) \
	qm_fd_set_param(fd, qm_fd_contig, off, len)
#घोषणा qm_fd_set_sg(fd, off, len) qm_fd_set_param(fd, qm_fd_sg, off, len)
#घोषणा qm_fd_set_contig_big(fd, len) \
	qm_fd_set_param(fd, qm_fd_contig_big, 0, len)
#घोषणा qm_fd_set_sg_big(fd, len) qm_fd_set_param(fd, qm_fd_sg_big, 0, len)
#घोषणा qm_fd_set_compound(fd, len) qm_fd_set_param(fd, qm_fd_compound, 0, len)

अटल अंतरभूत व्योम qm_fd_clear_fd(काष्ठा qm_fd *fd)
अणु
	fd->data = 0;
	fd->cfg = 0;
	fd->cmd = 0;
पूर्ण

/* Scatter/Gather table entry */
काष्ठा qm_sg_entry अणु
	जोड़ अणु
		काष्ठा अणु
			u8 __reserved1[3];
			u8 addr_hi;	/* high 8-bits of 40-bit address */
			__be32 addr_lo;	/* low 32-bits of 40-bit address */
		पूर्ण;
		__be64 data;
	पूर्ण;
	__be32 cfg;	/* E bit, F bit, length */
	u8 __reserved2;
	u8 bpid;
	__be16 offset; /* 13-bit, _res[13-15]*/
पूर्ण __packed;

#घोषणा QM_SG_LEN_MASK	GENMASK(29, 0)
#घोषणा QM_SG_OFF_MASK	GENMASK(12, 0)
#घोषणा QM_SG_FIN	BIT(30)
#घोषणा QM_SG_EXT	BIT(31)

अटल अंतरभूत dma_addr_t qm_sg_addr(स्थिर काष्ठा qm_sg_entry *sg)
अणु
	वापस be64_to_cpu(sg->data) & 0xffffffffffLLU;
पूर्ण

अटल अंतरभूत u64 qm_sg_entry_get64(स्थिर काष्ठा qm_sg_entry *sg)
अणु
	वापस be64_to_cpu(sg->data) & 0xffffffffffLLU;
पूर्ण

अटल अंतरभूत व्योम qm_sg_entry_set64(काष्ठा qm_sg_entry *sg, u64 addr)
अणु
	sg->addr_hi = upper_32_bits(addr);
	sg->addr_lo = cpu_to_be32(lower_32_bits(addr));
पूर्ण

अटल अंतरभूत bool qm_sg_entry_is_final(स्थिर काष्ठा qm_sg_entry *sg)
अणु
	वापस be32_to_cpu(sg->cfg) & QM_SG_FIN;
पूर्ण

अटल अंतरभूत bool qm_sg_entry_is_ext(स्थिर काष्ठा qm_sg_entry *sg)
अणु
	वापस be32_to_cpu(sg->cfg) & QM_SG_EXT;
पूर्ण

अटल अंतरभूत पूर्णांक qm_sg_entry_get_len(स्थिर काष्ठा qm_sg_entry *sg)
अणु
	वापस be32_to_cpu(sg->cfg) & QM_SG_LEN_MASK;
पूर्ण

अटल अंतरभूत व्योम qm_sg_entry_set_len(काष्ठा qm_sg_entry *sg, पूर्णांक len)
अणु
	sg->cfg = cpu_to_be32(len & QM_SG_LEN_MASK);
पूर्ण

अटल अंतरभूत व्योम qm_sg_entry_set_f(काष्ठा qm_sg_entry *sg, पूर्णांक len)
अणु
	sg->cfg = cpu_to_be32(QM_SG_FIN | (len & QM_SG_LEN_MASK));
पूर्ण

अटल अंतरभूत पूर्णांक qm_sg_entry_get_off(स्थिर काष्ठा qm_sg_entry *sg)
अणु
	वापस be32_to_cpu(sg->offset) & QM_SG_OFF_MASK;
पूर्ण

/* "Frame Dequeue Response" */
काष्ठा qm_dqrr_entry अणु
	u8 verb;
	u8 stat;
	__be16 seqnum;	/* 15-bit */
	u8 tok;
	u8 __reserved2[3];
	__be32 fqid;	/* 24-bit */
	__be32 context_b;
	काष्ठा qm_fd fd;
	u8 __reserved4[32];
पूर्ण __packed __aligned(64);
#घोषणा QM_DQRR_VERB_VBIT		0x80
#घोषणा QM_DQRR_VERB_MASK		0x7f	/* where the verb contains; */
#घोषणा QM_DQRR_VERB_FRAME_DEQUEUE	0x60	/* "this format" */
#घोषणा QM_DQRR_STAT_FQ_EMPTY		0x80	/* FQ empty */
#घोषणा QM_DQRR_STAT_FQ_HELDACTIVE	0x40	/* FQ held active */
#घोषणा QM_DQRR_STAT_FQ_FORCEELIGIBLE	0x20	/* FQ was क्रमce-eligible'd */
#घोषणा QM_DQRR_STAT_FD_VALID		0x10	/* has a non-शून्य FD */
#घोषणा QM_DQRR_STAT_UNSCHEDULED	0x02	/* Unscheduled dequeue */
#घोषणा QM_DQRR_STAT_DQCR_EXPIRED	0x01	/* VDQCR or PDQCR expired*/

/* 'fqid' is a 24-bit field in every h/w descriptor */
#घोषणा QM_FQID_MASK	GENMASK(23, 0)
#घोषणा qm_fqid_set(p, v) ((p)->fqid = cpu_to_be32((v) & QM_FQID_MASK))
#घोषणा qm_fqid_get(p)    (be32_to_cpu((p)->fqid) & QM_FQID_MASK)

/* "ERN Message Response" */
/* "FQ State Change Notification" */
जोड़ qm_mr_entry अणु
	काष्ठा अणु
		u8 verb;
		u8 __reserved[63];
	पूर्ण;
	काष्ठा अणु
		u8 verb;
		u8 dca;
		__be16 seqnum;
		u8 rc;		/* Rej Code: 8-bit */
		u8 __reserved[3];
		__be32 fqid;	/* 24-bit */
		__be32 tag;
		काष्ठा qm_fd fd;
		u8 __reserved1[32];
	पूर्ण __packed __aligned(64) ern;
	काष्ठा अणु
		u8 verb;
		u8 fqs;		/* Frame Queue Status */
		u8 __reserved1[6];
		__be32 fqid;	/* 24-bit */
		__be32 context_b;
		u8 __reserved2[48];
	पूर्ण __packed fq;		/* FQRN/FQRNI/FQRL/FQPN */
पूर्ण;
#घोषणा QM_MR_VERB_VBIT			0x80
/*
 * ERNs originating from direct-connect portals ("dcern") use 0x20 as a verb
 * which would be invalid as a s/w enqueue verb. A s/w ERN can be distinguished
 * from the other MR types by noting अगर the 0x20 bit is unset.
 */
#घोषणा QM_MR_VERB_TYPE_MASK		0x27
#घोषणा QM_MR_VERB_DC_ERN		0x20
#घोषणा QM_MR_VERB_FQRN			0x21
#घोषणा QM_MR_VERB_FQRNI		0x22
#घोषणा QM_MR_VERB_FQRL			0x23
#घोषणा QM_MR_VERB_FQPN			0x24
#घोषणा QM_MR_RC_MASK			0xf0	/* contains one of; */
#घोषणा QM_MR_RC_CGR_TAILDROP		0x00
#घोषणा QM_MR_RC_WRED			0x10
#घोषणा QM_MR_RC_ERROR			0x20
#घोषणा QM_MR_RC_ORPWINDOW_EARLY	0x30
#घोषणा QM_MR_RC_ORPWINDOW_LATE		0x40
#घोषणा QM_MR_RC_FQ_TAILDROP		0x50
#घोषणा QM_MR_RC_ORPWINDOW_RETIRED	0x60
#घोषणा QM_MR_RC_ORP_ZERO		0x70
#घोषणा QM_MR_FQS_ORLPRESENT		0x02	/* ORL fragments to come */
#घोषणा QM_MR_FQS_NOTEMPTY		0x01	/* FQ has enqueued frames */

/*
 * An identical काष्ठाure of FQD fields is present in the "Init FQ" command and
 * the "Query FQ" result, it's suctioned out पूर्णांकo the "struct qm_fqd" type.
 * Within that, the 'stashing' and 'taildrop' pieces are also factored out, the
 * latter has two अंतरभूतs to assist with converting to/from the mant+exp
 * representation.
 */
काष्ठा qm_fqd_stashing अणु
	/* See QM_STASHING_EXCL_<...> */
	u8 exclusive;
	/* Numbers of cachelines */
	u8 cl; /* _res[6-7], as[4-5], ds[2-3], cs[0-1] */
पूर्ण;

काष्ठा qm_fqd_oac अणु
	/* "Overhead Accounting Control", see QM_OAC_<...> */
	u8 oac; /* oac[6-7], _res[0-5] */
	/* Two's-complement value (-128 to +127) */
	s8 oal; /* "Overhead Accounting Length" */
पूर्ण;

काष्ठा qm_fqd अणु
	/* _res[6-7], orprws[3-5], oa[2], olws[0-1] */
	u8 orpc;
	u8 cgid;
	__be16 fq_ctrl;	/* See QM_FQCTRL_<...> */
	__be16 dest_wq;	/* channel[3-15], wq[0-2] */
	__be16 ics_cred; /* 15-bit */
	/*
	 * For "Initialize Frame Queue" commands, the ग_लिखो-enable mask
	 * determines whether 'td' or 'oac_init' is observed. For query
	 * commands, this field is always 'td', and 'oac_query' (below) reflects
	 * the Overhead ACcounting values.
	 */
	जोड़ अणु
		__be16 td; /* "Taildrop": _res[13-15], mant[5-12], exp[0-4] */
		काष्ठा qm_fqd_oac oac_init;
	पूर्ण;
	__be32 context_b;
	जोड़ अणु
		/* Treat it as 64-bit opaque */
		__be64 opaque;
		काष्ठा अणु
			__be32 hi;
			__be32 lo;
		पूर्ण;
		/* Treat it as s/w portal stashing config */
		/* see "FQD Context_A field used for [...]" */
		काष्ठा अणु
			काष्ठा qm_fqd_stashing stashing;
			/*
			 * 48-bit address of FQ context to
			 * stash, must be cacheline-aligned
			 */
			__be16 context_hi;
			__be32 context_lo;
		पूर्ण __packed;
	पूर्ण context_a;
	काष्ठा qm_fqd_oac oac_query;
पूर्ण __packed;

#घोषणा QM_FQD_CHAN_OFF		3
#घोषणा QM_FQD_WQ_MASK		GENMASK(2, 0)
#घोषणा QM_FQD_TD_EXP_MASK	GENMASK(4, 0)
#घोषणा QM_FQD_TD_MANT_OFF	5
#घोषणा QM_FQD_TD_MANT_MASK	GENMASK(12, 5)
#घोषणा QM_FQD_TD_MAX		0xe0000000
#घोषणा QM_FQD_TD_MANT_MAX	0xff
#घोषणा QM_FQD_OAC_OFF		6
#घोषणा QM_FQD_AS_OFF		4
#घोषणा QM_FQD_DS_OFF		2
#घोषणा QM_FQD_XS_MASK		0x3

/* 64-bit converters क्रम context_hi/lo */
अटल अंतरभूत u64 qm_fqd_stashing_get64(स्थिर काष्ठा qm_fqd *fqd)
अणु
	वापस be64_to_cpu(fqd->context_a.opaque) & 0xffffffffffffULL;
पूर्ण

अटल अंतरभूत dma_addr_t qm_fqd_stashing_addr(स्थिर काष्ठा qm_fqd *fqd)
अणु
	वापस be64_to_cpu(fqd->context_a.opaque) & 0xffffffffffffULL;
पूर्ण

अटल अंतरभूत u64 qm_fqd_context_a_get64(स्थिर काष्ठा qm_fqd *fqd)
अणु
	वापस qm_fqd_stashing_get64(fqd);
पूर्ण

अटल अंतरभूत व्योम qm_fqd_stashing_set64(काष्ठा qm_fqd *fqd, u64 addr)
अणु
	fqd->context_a.context_hi = cpu_to_be16(upper_32_bits(addr));
	fqd->context_a.context_lo = cpu_to_be32(lower_32_bits(addr));
पूर्ण

अटल अंतरभूत व्योम qm_fqd_context_a_set64(काष्ठा qm_fqd *fqd, u64 addr)
अणु
	fqd->context_a.hi = cpu_to_be32(upper_32_bits(addr));
	fqd->context_a.lo = cpu_to_be32(lower_32_bits(addr));
पूर्ण

/* convert a threshold value पूर्णांकo mant+exp representation */
अटल अंतरभूत पूर्णांक qm_fqd_set_taildrop(काष्ठा qm_fqd *fqd, u32 val,
				      पूर्णांक roundup)
अणु
	u32 e = 0;
	पूर्णांक td, oddbit = 0;

	अगर (val > QM_FQD_TD_MAX)
		वापस -दुस्फल;

	जबतक (val > QM_FQD_TD_MANT_MAX) अणु
		oddbit = val & 1;
		val >>= 1;
		e++;
		अगर (roundup && oddbit)
			val++;
	पूर्ण

	td = (val << QM_FQD_TD_MANT_OFF) & QM_FQD_TD_MANT_MASK;
	td |= (e & QM_FQD_TD_EXP_MASK);
	fqd->td = cpu_to_be16(td);
	वापस 0;
पूर्ण
/* and the other direction */
अटल अंतरभूत पूर्णांक qm_fqd_get_taildrop(स्थिर काष्ठा qm_fqd *fqd)
अणु
	पूर्णांक td = be16_to_cpu(fqd->td);

	वापस ((td & QM_FQD_TD_MANT_MASK) >> QM_FQD_TD_MANT_OFF)
		<< (td & QM_FQD_TD_EXP_MASK);
पूर्ण

अटल अंतरभूत व्योम qm_fqd_set_stashing(काष्ठा qm_fqd *fqd, u8 as, u8 ds, u8 cs)
अणु
	काष्ठा qm_fqd_stashing *st = &fqd->context_a.stashing;

	st->cl = ((as & QM_FQD_XS_MASK) << QM_FQD_AS_OFF) |
		 ((ds & QM_FQD_XS_MASK) << QM_FQD_DS_OFF) |
		 (cs & QM_FQD_XS_MASK);
पूर्ण

अटल अंतरभूत u8 qm_fqd_get_stashing(स्थिर काष्ठा qm_fqd *fqd)
अणु
	वापस fqd->context_a.stashing.cl;
पूर्ण

अटल अंतरभूत व्योम qm_fqd_set_oac(काष्ठा qm_fqd *fqd, u8 val)
अणु
	fqd->oac_init.oac = val << QM_FQD_OAC_OFF;
पूर्ण

अटल अंतरभूत व्योम qm_fqd_set_oal(काष्ठा qm_fqd *fqd, s8 val)
अणु
	fqd->oac_init.oal = val;
पूर्ण

अटल अंतरभूत व्योम qm_fqd_set_destwq(काष्ठा qm_fqd *fqd, पूर्णांक ch, पूर्णांक wq)
अणु
	fqd->dest_wq = cpu_to_be16((ch << QM_FQD_CHAN_OFF) |
				   (wq & QM_FQD_WQ_MASK));
पूर्ण

अटल अंतरभूत पूर्णांक qm_fqd_get_chan(स्थिर काष्ठा qm_fqd *fqd)
अणु
	वापस be16_to_cpu(fqd->dest_wq) >> QM_FQD_CHAN_OFF;
पूर्ण

अटल अंतरभूत पूर्णांक qm_fqd_get_wq(स्थिर काष्ठा qm_fqd *fqd)
अणु
	वापस be16_to_cpu(fqd->dest_wq) & QM_FQD_WQ_MASK;
पूर्ण

/* See "Frame Queue Descriptor (FQD)" */
/* Frame Queue Descriptor (FQD) field 'fq_ctrl' uses these स्थिरants */
#घोषणा QM_FQCTRL_MASK		0x07ff	/* 'fq_ctrl' flags; */
#घोषणा QM_FQCTRL_CGE		0x0400	/* Congestion Group Enable */
#घोषणा QM_FQCTRL_TDE		0x0200	/* Tail-Drop Enable */
#घोषणा QM_FQCTRL_CTXASTASHING	0x0080	/* Context-A stashing */
#घोषणा QM_FQCTRL_CPCSTASH	0x0040	/* CPC Stash Enable */
#घोषणा QM_FQCTRL_FORCESFDR	0x0008	/* High-priority SFDRs */
#घोषणा QM_FQCTRL_AVOIDBLOCK	0x0004	/* Don't block active */
#घोषणा QM_FQCTRL_HOLDACTIVE	0x0002	/* Hold active in portal */
#घोषणा QM_FQCTRL_PREFERINCACHE	0x0001	/* Aggressively cache FQD */
#घोषणा QM_FQCTRL_LOCKINCACHE	QM_FQCTRL_PREFERINCACHE /* older naming */

/* See "FQD Context_A field used क्रम [...] */
/* Frame Queue Descriptor (FQD) field 'CONTEXT_A' uses these स्थिरants */
#घोषणा QM_STASHING_EXCL_ANNOTATION	0x04
#घोषणा QM_STASHING_EXCL_DATA		0x02
#घोषणा QM_STASHING_EXCL_CTX		0x01

/* See "Intra Class Scheduling" */
/* FQD field 'OAC' (Overhead ACcounting) uses these स्थिरants */
#घोषणा QM_OAC_ICS		0x2 /* Accounting क्रम Intra-Class Scheduling */
#घोषणा QM_OAC_CG		0x1 /* Accounting क्रम Congestion Groups */

/*
 * This काष्ठा represents the 32-bit "WR_PARM_[GYR]" parameters in CGR fields
 * and associated commands/responses. The WRED parameters are calculated from
 * these fields as follows;
 *   MaxTH = MA * (2 ^ Mn)
 *   Slope = SA / (2 ^ Sn)
 *    MaxP = 4 * (Pn + 1)
 */
काष्ठा qm_cgr_wr_parm अणु
	/* MA[24-31], Mn[19-23], SA[12-18], Sn[6-11], Pn[0-5] */
	__be32 word;
पूर्ण;
/*
 * This काष्ठा represents the 13-bit "CS_THRES" CGR field. In the corresponding
 * management commands, this is padded to a 16-bit काष्ठाure field, so that's
 * how we represent it here. The congestion state threshold is calculated from
 * these fields as follows;
 *   CS threshold = TA * (2 ^ Tn)
 */
काष्ठा qm_cgr_cs_thres अणु
	/* _res[13-15], TA[5-12], Tn[0-4] */
	__be16 word;
पूर्ण;
/*
 * This identical काष्ठाure of CGR fields is present in the "Init/Modify CGR"
 * commands and the "Query CGR" result. It's suctioned out here पूर्णांकo its own
 * काष्ठा.
 */
काष्ठा __qm_mc_cgr अणु
	काष्ठा qm_cgr_wr_parm wr_parm_g;
	काष्ठा qm_cgr_wr_parm wr_parm_y;
	काष्ठा qm_cgr_wr_parm wr_parm_r;
	u8 wr_en_g;	/* boolean, use QM_CGR_EN */
	u8 wr_en_y;	/* boolean, use QM_CGR_EN */
	u8 wr_en_r;	/* boolean, use QM_CGR_EN */
	u8 cscn_en;	/* boolean, use QM_CGR_EN */
	जोड़ अणु
		काष्ठा अणु
			__be16 cscn_targ_upd_ctrl; /* use QM_CGR_TARG_UDP_* */
			__be16 cscn_targ_dcp_low;
		पूर्ण;
		__be32 cscn_targ;	/* use QM_CGR_TARG_* */
	पूर्ण;
	u8 cstd_en;	/* boolean, use QM_CGR_EN */
	u8 cs;		/* boolean, only used in query response */
	काष्ठा qm_cgr_cs_thres cs_thres; /* use qm_cgr_cs_thres_set64() */
	u8 mode;	/* QMAN_CGR_MODE_FRAME not supported in rev1.0 */
पूर्ण __packed;
#घोषणा QM_CGR_EN		0x01 /* For wr_en_*, cscn_en, cstd_en */
#घोषणा QM_CGR_TARG_UDP_CTRL_WRITE_BIT	0x8000 /* value written to portal bit*/
#घोषणा QM_CGR_TARG_UDP_CTRL_DCP	0x4000 /* 0: SWP, 1: DCP */
#घोषणा QM_CGR_TARG_PORTAL(n)	(0x80000000 >> (n)) /* s/w portal, 0-9 */
#घोषणा QM_CGR_TARG_FMAN0	0x00200000 /* direct-connect portal: fman0 */
#घोषणा QM_CGR_TARG_FMAN1	0x00100000 /*			   : fman1 */
/* Convert CGR thresholds to/from "cs_thres" क्रमmat */
अटल अंतरभूत u64 qm_cgr_cs_thres_get64(स्थिर काष्ठा qm_cgr_cs_thres *th)
अणु
	पूर्णांक thres = be16_to_cpu(th->word);

	वापस ((thres >> 5) & 0xff) << (thres & 0x1f);
पूर्ण

अटल अंतरभूत पूर्णांक qm_cgr_cs_thres_set64(काष्ठा qm_cgr_cs_thres *th, u64 val,
					पूर्णांक roundup)
अणु
	u32 e = 0;
	पूर्णांक oddbit = 0;

	जबतक (val > 0xff) अणु
		oddbit = val & 1;
		val >>= 1;
		e++;
		अगर (roundup && oddbit)
			val++;
	पूर्ण
	th->word = cpu_to_be16(((val & 0xff) << 5) | (e & 0x1f));
	वापस 0;
पूर्ण

/* "Initialize FQ" */
काष्ठा qm_mcc_initfq अणु
	u8 __reserved1[2];
	__be16 we_mask;	/* Write Enable Mask */
	__be32 fqid;	/* 24-bit */
	__be16 count;	/* Initialises 'count+1' FQDs */
	काष्ठा qm_fqd fqd; /* the FQD fields go here */
	u8 __reserved2[30];
पूर्ण __packed;
/* "Initialize/Modify CGR" */
काष्ठा qm_mcc_initcgr अणु
	u8 __reserve1[2];
	__be16 we_mask;	/* Write Enable Mask */
	काष्ठा __qm_mc_cgr cgr;	/* CGR fields */
	u8 __reserved2[2];
	u8 cgid;
	u8 __reserved3[32];
पूर्ण __packed;

/* INITFQ-specअगरic flags */
#घोषणा QM_INITFQ_WE_MASK		0x01ff	/* 'Write Enable' flags; */
#घोषणा QM_INITFQ_WE_OAC		0x0100
#घोषणा QM_INITFQ_WE_ORPC		0x0080
#घोषणा QM_INITFQ_WE_CGID		0x0040
#घोषणा QM_INITFQ_WE_FQCTRL		0x0020
#घोषणा QM_INITFQ_WE_DESTWQ		0x0010
#घोषणा QM_INITFQ_WE_ICSCRED		0x0008
#घोषणा QM_INITFQ_WE_TDTHRESH		0x0004
#घोषणा QM_INITFQ_WE_CONTEXTB		0x0002
#घोषणा QM_INITFQ_WE_CONTEXTA		0x0001
/* INITCGR/MODIFYCGR-specअगरic flags */
#घोषणा QM_CGR_WE_MASK			0x07ff	/* 'Write Enable Mask'; */
#घोषणा QM_CGR_WE_WR_PARM_G		0x0400
#घोषणा QM_CGR_WE_WR_PARM_Y		0x0200
#घोषणा QM_CGR_WE_WR_PARM_R		0x0100
#घोषणा QM_CGR_WE_WR_EN_G		0x0080
#घोषणा QM_CGR_WE_WR_EN_Y		0x0040
#घोषणा QM_CGR_WE_WR_EN_R		0x0020
#घोषणा QM_CGR_WE_CSCN_EN		0x0010
#घोषणा QM_CGR_WE_CSCN_TARG		0x0008
#घोषणा QM_CGR_WE_CSTD_EN		0x0004
#घोषणा QM_CGR_WE_CS_THRES		0x0002
#घोषणा QM_CGR_WE_MODE			0x0001

#घोषणा QMAN_CGR_FLAG_USE_INIT	     0x00000001
#घोषणा QMAN_CGR_MODE_FRAME          0x00000001

	/* Portal and Frame Queues */
/* Represents a managed portal */
काष्ठा qman_portal;

/*
 * This object type represents QMan frame queue descriptors (FQD), it is
 * cacheline-aligned, and initialised by qman_create_fq(). The काष्ठाure is
 * defined further करोwn.
 */
काष्ठा qman_fq;

/*
 * This object type represents a QMan congestion group, it is defined further
 * करोwn.
 */
काष्ठा qman_cgr;

/*
 * This क्रमागत, and the callback type that वापसs it, are used when handling
 * dequeued frames via DQRR. Note that क्रम "null" callbacks रेजिस्टरed with the
 * portal object (क्रम handling dequeues that करो not demux because context_b is
 * शून्य), the वापस value *MUST* be qman_cb_dqrr_consume.
 */
क्रमागत qman_cb_dqrr_result अणु
	/* DQRR entry can be consumed */
	qman_cb_dqrr_consume,
	/* Like _consume, but requests parking - FQ must be held-active */
	qman_cb_dqrr_park,
	/* Does not consume, क्रम DCA mode only. */
	qman_cb_dqrr_defer,
	/*
	 * Stop processing without consuming this ring entry. Exits the current
	 * qman_p_poll_dqrr() or पूर्णांकerrupt-handling, as appropriate. If within
	 * an पूर्णांकerrupt handler, the callback would typically call
	 * qman_irqsource_हटाओ(QM_PIRQ_DQRI) beक्रमe वापसing this value,
	 * otherwise the पूर्णांकerrupt will reनिश्चित immediately.
	 */
	qman_cb_dqrr_stop,
	/* Like qman_cb_dqrr_stop, but consumes the current entry. */
	qman_cb_dqrr_consume_stop
पूर्ण;
प्रकार क्रमागत qman_cb_dqrr_result (*qman_cb_dqrr)(काष्ठा qman_portal *qm,
					काष्ठा qman_fq *fq,
					स्थिर काष्ठा qm_dqrr_entry *dqrr,
					bool sched_napi);

/*
 * This callback type is used when handling ERNs, FQRNs and FQRLs via MR. They
 * are always consumed after the callback वापसs.
 */
प्रकार व्योम (*qman_cb_mr)(काष्ठा qman_portal *qm, काष्ठा qman_fq *fq,
			   स्थिर जोड़ qm_mr_entry *msg);

/*
 * s/w-visible states. Ie. tentatively scheduled + truly scheduled + active +
 * held-active + held-suspended are just "sched". Things like "retired" will not
 * be assumed until it is complete (ie. QMAN_FQ_STATE_CHANGING is set until
 * then, to indicate it's completing and to gate attempts to retry the retire
 * command). Note, park commands करो not set QMAN_FQ_STATE_CHANGING because it's
 * technically impossible in the हाल of enqueue DCAs (which refer to DQRR ring
 * index rather than the FQ that ring entry corresponds to), so repeated park
 * commands are allowed (अगर you're silly enough to try) but won't change FQ
 * state, and the resulting park notअगरications move FQs from "sched" to
 * "parked".
 */
क्रमागत qman_fq_state अणु
	qman_fq_state_oos,
	qman_fq_state_parked,
	qman_fq_state_sched,
	qman_fq_state_retired
पूर्ण;

#घोषणा QMAN_FQ_STATE_CHANGING	     0x80000000 /* 'state' is changing */
#घोषणा QMAN_FQ_STATE_NE	     0x40000000 /* retired FQ isn't empty */
#घोषणा QMAN_FQ_STATE_ORL	     0x20000000 /* retired FQ has ORL */
#घोषणा QMAN_FQ_STATE_BLOCKOOS	     0xe0000000 /* अगर any are set, no OOS */
#घोषणा QMAN_FQ_STATE_CGR_EN	     0x10000000 /* CGR enabled */
#घोषणा QMAN_FQ_STATE_VDQCR	     0x08000000 /* being अस्थिर dequeued */

/*
 * Frame queue objects (काष्ठा qman_fq) are stored within memory passed to
 * qman_create_fq(), as this allows stashing of caller-provided demux callback
 * poपूर्णांकers at no extra cost to stashing of (driver-पूर्णांकernal) FQ state. If the
 * caller wishes to add per-FQ state and have it benefit from dequeue-stashing,
 * they should;
 *
 * (a) extend the qman_fq काष्ठाure with their state; eg.
 *
 *     // myfq is allocated and driver_fq callbacks filled in;
 *     काष्ठा my_fq अणु
 *	   काष्ठा qman_fq base;
 *	   पूर्णांक an_extra_field;
 *	   [ ... add other fields to be associated with each FQ ...]
 *     पूर्ण *myfq = some_my_fq_allocator();
 *     काष्ठा qman_fq *fq = qman_create_fq(fqid, flags, &myfq->base);
 *
 *     // in a dequeue callback, access extra fields from 'fq' via a cast;
 *     काष्ठा my_fq *myfq = (काष्ठा my_fq *)fq;
 *     करो_something_with(myfq->an_extra_field);
 *     [...]
 *
 * (b) when and अगर configuring the FQ क्रम context stashing, specअगरy how ever
 *     many cachelines are required to stash 'struct my_fq', to accelerate not
 *     only the QMan driver but the callback as well.
 */

काष्ठा qman_fq_cb अणु
	qman_cb_dqrr dqrr;	/* क्रम dequeued frames */
	qman_cb_mr ern;		/* क्रम s/w ERNs */
	qman_cb_mr fqs;		/* frame-queue state changes*/
पूर्ण;

काष्ठा qman_fq अणु
	/* Caller of qman_create_fq() provides these demux callbacks */
	काष्ठा qman_fq_cb cb;
	/*
	 * These are पूर्णांकernal to the driver, करोn't touch. In particular, they
	 * may change, be हटाओd, or extended (so you shouldn't rely on
	 * माप(qman_fq) being a स्थिरant).
	 */
	u32 fqid, idx;
	अचिन्हित दीर्घ flags;
	क्रमागत qman_fq_state state;
	पूर्णांक cgr_groupid;
पूर्ण;

/*
 * This callback type is used when handling congestion group entry/निकास.
 * 'congested' is non-zero on congestion-entry, and zero on congestion-निकास.
 */
प्रकार व्योम (*qman_cb_cgr)(काष्ठा qman_portal *qm,
			    काष्ठा qman_cgr *cgr, पूर्णांक congested);

काष्ठा qman_cgr अणु
	/* Set these prior to qman_create_cgr() */
	u32 cgrid; /* 0..255, but u32 to allow specials like -1, 256, etc.*/
	qman_cb_cgr cb;
	/* These are निजी to the driver */
	u16 chan; /* portal channel this object is created on */
	काष्ठा list_head node;
पूर्ण;

/* Flags to qman_create_fq() */
#घोषणा QMAN_FQ_FLAG_NO_ENQUEUE	     0x00000001 /* can't enqueue */
#घोषणा QMAN_FQ_FLAG_NO_MODIFY	     0x00000002 /* can only enqueue */
#घोषणा QMAN_FQ_FLAG_TO_DCPORTAL     0x00000004 /* consumed by CAAM/PME/Fman */
#घोषणा QMAN_FQ_FLAG_DYNAMIC_FQID    0x00000020 /* (de)allocate fqid */

/* Flags to qman_init_fq() */
#घोषणा QMAN_INITFQ_FLAG_SCHED	     0x00000001 /* schedule rather than park */
#घोषणा QMAN_INITFQ_FLAG_LOCAL	     0x00000004 /* set dest portal */

/*
 * For qman_अस्थिर_dequeue(); Choose one PRECEDENCE. EXACT is optional. Use
 * NUMFRAMES(n) (6-bit) or NUMFRAMES_TILLEMPTY to fill in the frame-count. Use
 * FQID(n) to fill in the frame queue ID.
 */
#घोषणा QM_VDQCR_PRECEDENCE_VDQCR	0x0
#घोषणा QM_VDQCR_PRECEDENCE_SDQCR	0x80000000
#घोषणा QM_VDQCR_EXACT			0x40000000
#घोषणा QM_VDQCR_NUMFRAMES_MASK		0x3f000000
#घोषणा QM_VDQCR_NUMFRAMES_SET(n)	(((n) & 0x3f) << 24)
#घोषणा QM_VDQCR_NUMFRAMES_GET(n)	(((n) >> 24) & 0x3f)
#घोषणा QM_VDQCR_NUMFRAMES_TILLEMPTY	QM_VDQCR_NUMFRAMES_SET(0)

#घोषणा QMAN_VOLATILE_FLAG_WAIT	     0x00000001 /* रुको अगर VDQCR is in use */
#घोषणा QMAN_VOLATILE_FLAG_WAIT_INT  0x00000002 /* अगर रुको, पूर्णांकerruptible? */
#घोषणा QMAN_VOLATILE_FLAG_FINISH    0x00000004 /* रुको till VDQCR completes */

/* "Query FQ Non-Programmable Fields" */
काष्ठा qm_mcr_queryfq_np अणु
	u8 verb;
	u8 result;
	u8 __reserved1;
	u8 state;		/* QM_MCR_NP_STATE_*** */
	u32 fqd_link;		/* 24-bit, _res2[24-31] */
	u16 odp_seq;		/* 14-bit, _res3[14-15] */
	u16 orp_nesn;		/* 14-bit, _res4[14-15] */
	u16 orp_ea_hseq;	/* 15-bit, _res5[15] */
	u16 orp_ea_tseq;	/* 15-bit, _res6[15] */
	u32 orp_ea_hptr;	/* 24-bit, _res7[24-31] */
	u32 orp_ea_tptr;	/* 24-bit, _res8[24-31] */
	u32 pfdr_hptr;		/* 24-bit, _res9[24-31] */
	u32 pfdr_tptr;		/* 24-bit, _res10[24-31] */
	u8 __reserved2[5];
	u8 is;			/* 1-bit, _res12[1-7] */
	u16 ics_surp;
	u32 byte_cnt;
	u32 frm_cnt;		/* 24-bit, _res13[24-31] */
	u32 __reserved3;
	u16 ra1_sfdr;		/* QM_MCR_NP_RA1_*** */
	u16 ra2_sfdr;		/* QM_MCR_NP_RA2_*** */
	u16 __reserved4;
	u16 od1_sfdr;		/* QM_MCR_NP_OD1_*** */
	u16 od2_sfdr;		/* QM_MCR_NP_OD2_*** */
	u16 od3_sfdr;		/* QM_MCR_NP_OD3_*** */
पूर्ण __packed;

#घोषणा QM_MCR_NP_STATE_FE		0x10
#घोषणा QM_MCR_NP_STATE_R		0x08
#घोषणा QM_MCR_NP_STATE_MASK		0x07	/* Reads FQD::STATE; */
#घोषणा QM_MCR_NP_STATE_OOS		0x00
#घोषणा QM_MCR_NP_STATE_RETIRED		0x01
#घोषणा QM_MCR_NP_STATE_TEN_SCHED	0x02
#घोषणा QM_MCR_NP_STATE_TRU_SCHED	0x03
#घोषणा QM_MCR_NP_STATE_PARKED		0x04
#घोषणा QM_MCR_NP_STATE_ACTIVE		0x05
#घोषणा QM_MCR_NP_PTR_MASK		0x07ff	/* क्रम RA[12] & OD[123] */
#घोषणा QM_MCR_NP_RA1_NRA(v)		(((v) >> 14) & 0x3)	/* FQD::NRA */
#घोषणा QM_MCR_NP_RA2_IT(v)		(((v) >> 14) & 0x1)	/* FQD::IT */
#घोषणा QM_MCR_NP_OD1_NOD(v)		(((v) >> 14) & 0x3)	/* FQD::NOD */
#घोषणा QM_MCR_NP_OD3_NPC(v)		(((v) >> 14) & 0x3)	/* FQD::NPC */

क्रमागत qm_mcr_queryfq_np_masks अणु
	qm_mcr_fqd_link_mask = BIT(24) - 1,
	qm_mcr_odp_seq_mask = BIT(14) - 1,
	qm_mcr_orp_nesn_mask = BIT(14) - 1,
	qm_mcr_orp_ea_hseq_mask = BIT(15) - 1,
	qm_mcr_orp_ea_tseq_mask = BIT(15) - 1,
	qm_mcr_orp_ea_hptr_mask = BIT(24) - 1,
	qm_mcr_orp_ea_tptr_mask = BIT(24) - 1,
	qm_mcr_pfdr_hptr_mask = BIT(24) - 1,
	qm_mcr_pfdr_tptr_mask = BIT(24) - 1,
	qm_mcr_is_mask = BIT(1) - 1,
	qm_mcr_frm_cnt_mask = BIT(24) - 1,
पूर्ण;

#घोषणा qm_mcr_np_get(np, field) \
	((np)->field & (qm_mcr_##field##_mask))

	/* Portal Management */
/**
 * qman_p_irqsource_add - add processing sources to be पूर्णांकerrupt-driven
 * @bits: biपंचांगask of QM_PIRQ_**I processing sources
 *
 * Adds processing sources that should be पूर्णांकerrupt-driven (rather than
 * processed via qman_poll_***() functions).
 */
व्योम qman_p_irqsource_add(काष्ठा qman_portal *p, u32 bits);

/**
 * qman_p_irqsource_हटाओ - हटाओ processing sources from being पूर्णांक-driven
 * @bits: biपंचांगask of QM_PIRQ_**I processing sources
 *
 * Removes processing sources from being पूर्णांकerrupt-driven, so that they will
 * instead be processed via qman_poll_***() functions.
 */
व्योम qman_p_irqsource_हटाओ(काष्ठा qman_portal *p, u32 bits);

/**
 * qman_affine_cpus - वापस a mask of cpus that have affine portals
 */
स्थिर cpumask_t *qman_affine_cpus(व्योम);

/**
 * qman_affine_channel - वापस the channel ID of an portal
 * @cpu: the cpu whose affine portal is the subject of the query
 *
 * If @cpu is -1, the affine portal क्रम the current CPU will be used. It is a
 * bug to call this function क्रम any value of @cpu (other than -1) that is not a
 * member of the mask वापसed from qman_affine_cpus().
 */
u16 qman_affine_channel(पूर्णांक cpu);

/**
 * qman_get_affine_portal - वापस the portal poपूर्णांकer affine to cpu
 * @cpu: the cpu whose affine portal is the subject of the query
 */
काष्ठा qman_portal *qman_get_affine_portal(पूर्णांक cpu);

/**
 * qman_start_using_portal - रेजिस्टर a device link क्रम the portal user
 * @p: the portal that will be in use
 * @dev: the device that will use the portal
 *
 * Makes sure that the devices that use the portal are unbound when the
 * portal is unbound
 */
पूर्णांक qman_start_using_portal(काष्ठा qman_portal *p, काष्ठा device *dev);

/**
 * qman_p_poll_dqrr - process DQRR (fast-path) entries
 * @limit: the maximum number of DQRR entries to process
 *
 * Use of this function requires that DQRR processing not be पूर्णांकerrupt-driven.
 * The वापस value represents the number of DQRR entries processed.
 */
पूर्णांक qman_p_poll_dqrr(काष्ठा qman_portal *p, अचिन्हित पूर्णांक limit);

/**
 * qman_p_अटल_dequeue_add - Add pool channels to the portal SDQCR
 * @pools: bit-mask of pool channels, using QM_SDQCR_CHANNELS_POOL(n)
 *
 * Adds a set of pool channels to the portal's अटल dequeue command रेजिस्टर
 * (SDQCR). The requested pools are limited to those the portal has dequeue
 * access to.
 */
व्योम qman_p_अटल_dequeue_add(काष्ठा qman_portal *p, u32 pools);

	/* FQ management */
/**
 * qman_create_fq - Allocates a FQ
 * @fqid: the index of the FQD to encapsulate, must be "Out of Service"
 * @flags: bit-mask of QMAN_FQ_FLAG_*** options
 * @fq: memory क्रम storing the 'fq', with callbacks filled in
 *
 * Creates a frame queue object क्रम the given @fqid, unless the
 * QMAN_FQ_FLAG_DYNAMIC_FQID flag is set in @flags, in which हाल a FQID is
 * dynamically allocated (or the function fails अगर none are available). Once
 * created, the caller should not touch the memory at 'fq' except as extended to
 * adjacent memory क्रम user-defined fields (see the definition of "काष्ठा
 * qman_fq" क्रम more info). NO_MODIFY is only पूर्णांकended क्रम enqueuing to
 * pre-existing frame-queues that aren't to be otherwise पूर्णांकerfered with, it
 * prevents all other modअगरications to the frame queue. The TO_DCPORTAL flag
 * causes the driver to honour any context_b modअगरications requested in the
 * qm_init_fq() API, as this indicates the frame queue will be consumed by a
 * direct-connect portal (PME, CAAM, or Fman). When frame queues are consumed by
 * software portals, the context_b field is controlled by the driver and can't
 * be modअगरied by the caller.
 */
पूर्णांक qman_create_fq(u32 fqid, u32 flags, काष्ठा qman_fq *fq);

/**
 * qman_destroy_fq - Deallocates a FQ
 * @fq: the frame queue object to release
 *
 * The memory क्रम this frame queue object ('fq' provided in qman_create_fq()) is
 * not deallocated but the caller regains ownership, to करो with as desired. The
 * FQ must be in the 'out-of-service' or in the 'parked' state.
 */
व्योम qman_destroy_fq(काष्ठा qman_fq *fq);

/**
 * qman_fq_fqid - Queries the frame queue ID of a FQ object
 * @fq: the frame queue object to query
 */
u32 qman_fq_fqid(काष्ठा qman_fq *fq);

/**
 * qman_init_fq - Initialises FQ fields, leaves the FQ "parked" or "scheduled"
 * @fq: the frame queue object to modअगरy, must be 'parked' or new.
 * @flags: bit-mask of QMAN_INITFQ_FLAG_*** options
 * @opts: the FQ-modअगरication settings, as defined in the low-level API
 *
 * The @opts parameter comes from the low-level portal API. Select
 * QMAN_INITFQ_FLAG_SCHED in @flags to cause the frame queue to be scheduled
 * rather than parked. NB, @opts can be शून्य.
 *
 * Note that some fields and options within @opts may be ignored or overwritten
 * by the driver;
 * 1. the 'count' and 'fqid' fields are always ignored (this operation only
 * affects one frame queue: @fq).
 * 2. the QM_INITFQ_WE_CONTEXTB option of the 'we_mask' field and the associated
 * 'fqd' structure's 'context_b' field are someबार overwritten;
 *   - अगर @fq was not created with QMAN_FQ_FLAG_TO_DCPORTAL, then context_b is
 *     initialised to a value used by the driver क्रम demux.
 *   - अगर context_b is initialised क्रम demux, so is context_a in हाल stashing
 *     is requested (see item 4).
 * (So caller control of context_b is only possible क्रम TO_DCPORTAL frame queue
 * objects.)
 * 3. अगर @flags contains QMAN_INITFQ_FLAG_LOCAL, the 'fqd' structure's
 * 'dest::channel' field will be overwritten to match the portal used to issue
 * the command. If the WE_DESTWQ ग_लिखो-enable bit had alपढ़ोy been set by the
 * caller, the channel workqueue will be left as-is, otherwise the ग_लिखो-enable
 * bit is set and the workqueue is set to a शेष of 4. If the "LOCAL" flag
 * isn't set, the destination channel/workqueue fields and the ग_लिखो-enable bit
 * are left as-is.
 * 4. अगर the driver overग_लिखोs context_a/b क्रम demux, then अगर
 * QM_INITFQ_WE_CONTEXTA is set, the driver will only overग_लिखो
 * context_a.address fields and will leave the stashing fields provided by the
 * user alone, otherwise it will zero out the context_a.stashing fields.
 */
पूर्णांक qman_init_fq(काष्ठा qman_fq *fq, u32 flags, काष्ठा qm_mcc_initfq *opts);

/**
 * qman_schedule_fq - Schedules a FQ
 * @fq: the frame queue object to schedule, must be 'parked'
 *
 * Schedules the frame queue, which must be Parked, which takes it to
 * Tentatively-Scheduled or Truly-Scheduled depending on its fill-level.
 */
पूर्णांक qman_schedule_fq(काष्ठा qman_fq *fq);

/**
 * qman_retire_fq - Retires a FQ
 * @fq: the frame queue object to retire
 * @flags: FQ flags (QMAN_FQ_STATE*) अगर retirement completes immediately
 *
 * Retires the frame queue. This वापसs zero अगर it succeeds immediately, +1 अगर
 * the retirement was started asynchronously, otherwise it वापसs negative क्रम
 * failure. When this function वापसs zero, @flags is set to indicate whether
 * the retired FQ is empty and/or whether it has any ORL fragments (to show up
 * as ERNs). Otherwise the corresponding flags will be known when a subsequent
 * FQRN message shows up on the portal's message ring.
 *
 * NB, अगर the retirement is asynchronous (the FQ was in the Truly Scheduled or
 * Active state), the completion will be via the message ring as a FQRN - but
 * the corresponding callback may occur beक्रमe this function वापसs!! Ie. the
 * caller should be prepared to accept the callback as the function is called,
 * not only once it has वापसed.
 */
पूर्णांक qman_retire_fq(काष्ठा qman_fq *fq, u32 *flags);

/**
 * qman_oos_fq - Puts a FQ "out of service"
 * @fq: the frame queue object to be put out-of-service, must be 'retired'
 *
 * The frame queue must be retired and empty, and अगर any order restoration list
 * was released as ERNs at the समय of retirement, they must all be consumed.
 */
पूर्णांक qman_oos_fq(काष्ठा qman_fq *fq);

/*
 * qman_अस्थिर_dequeue - Issue a अस्थिर dequeue command
 * @fq: the frame queue object to dequeue from
 * @flags: a bit-mask of QMAN_VOLATILE_FLAG_*** options
 * @vdqcr: bit mask of QM_VDQCR_*** options, as per qm_dqrr_vdqcr_set()
 *
 * Attempts to lock access to the portal's VDQCR अस्थिर dequeue functionality.
 * The function will block and sleep अगर QMAN_VOLATILE_FLAG_WAIT is specअगरied and
 * the VDQCR is alपढ़ोy in use, otherwise वापसs non-zero क्रम failure. If
 * QMAN_VOLATILE_FLAG_FINISH is specअगरied, the function will only वापस once
 * the VDQCR command has finished executing (ie. once the callback क्रम the last
 * DQRR entry resulting from the VDQCR command has been called). If not using
 * the FINISH flag, completion can be determined either by detecting the
 * presence of the QM_DQRR_STAT_UNSCHEDULED and QM_DQRR_STAT_DQCR_EXPIRED bits
 * in the "stat" parameter passed to the FQ's dequeue callback, or by रुकोing
 * क्रम the QMAN_FQ_STATE_VDQCR bit to disappear.
 */
पूर्णांक qman_अस्थिर_dequeue(काष्ठा qman_fq *fq, u32 flags, u32 vdqcr);

/**
 * qman_enqueue - Enqueue a frame to a frame queue
 * @fq: the frame queue object to enqueue to
 * @fd: a descriptor of the frame to be enqueued
 *
 * Fills an entry in the EQCR of portal @qm to enqueue the frame described by
 * @fd. The descriptor details are copied from @fd to the EQCR entry, the 'pid'
 * field is ignored. The वापस value is non-zero on error, such as ring full.
 */
पूर्णांक qman_enqueue(काष्ठा qman_fq *fq, स्थिर काष्ठा qm_fd *fd);

/**
 * qman_alloc_fqid_range - Allocate a contiguous range of FQIDs
 * @result: is set by the API to the base FQID of the allocated range
 * @count: the number of FQIDs required
 *
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक qman_alloc_fqid_range(u32 *result, u32 count);
#घोषणा qman_alloc_fqid(result) qman_alloc_fqid_range(result, 1)

/**
 * qman_release_fqid - Release the specअगरied frame queue ID
 * @fqid: the FQID to be released back to the resource pool
 *
 * This function can also be used to seed the allocator with
 * FQID ranges that it can subsequently allocate from.
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक qman_release_fqid(u32 fqid);

/**
 * qman_query_fq_np - Queries non-programmable FQD fields
 * @fq: the frame queue object to be queried
 * @np: storage क्रम the queried FQD fields
 */
पूर्णांक qman_query_fq_np(काष्ठा qman_fq *fq, काष्ठा qm_mcr_queryfq_np *np);

	/* Pool-channel management */
/**
 * qman_alloc_pool_range - Allocate a contiguous range of pool-channel IDs
 * @result: is set by the API to the base pool-channel ID of the allocated range
 * @count: the number of pool-channel IDs required
 *
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक qman_alloc_pool_range(u32 *result, u32 count);
#घोषणा qman_alloc_pool(result) qman_alloc_pool_range(result, 1)

/**
 * qman_release_pool - Release the specअगरied pool-channel ID
 * @id: the pool-chan ID to be released back to the resource pool
 *
 * This function can also be used to seed the allocator with
 * pool-channel ID ranges that it can subsequently allocate from.
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक qman_release_pool(u32 id);

	/* CGR management */
/**
 * qman_create_cgr - Register a congestion group object
 * @cgr: the 'cgr' object, with fields filled in
 * @flags: QMAN_CGR_FLAG_* values
 * @opts: optional state of CGR settings
 *
 * Registers this object to receiving congestion entry/निकास callbacks on the
 * portal affine to the cpu portal on which this API is executed. If opts is
 * शून्य then only the callback (cgr->cb) function is रेजिस्टरed. If @flags
 * contains QMAN_CGR_FLAG_USE_INIT, then an init hw command (which will reset
 * any unspecअगरied parameters) will be used rather than a modअगरy hw hardware
 * (which only modअगरies the specअगरied parameters).
 */
पूर्णांक qman_create_cgr(काष्ठा qman_cgr *cgr, u32 flags,
		    काष्ठा qm_mcc_initcgr *opts);

/**
 * qman_delete_cgr - Deरेजिस्टरs a congestion group object
 * @cgr: the 'cgr' object to deरेजिस्टर
 *
 * "Unplugs" this CGR object from the portal affine to the cpu on which this API
 * is executed. This must be excuted on the same affine portal on which it was
 * created.
 */
पूर्णांक qman_delete_cgr(काष्ठा qman_cgr *cgr);

/**
 * qman_delete_cgr_safe - Deरेजिस्टरs a congestion group object from any CPU
 * @cgr: the 'cgr' object to deरेजिस्टर
 *
 * This will select the proper CPU and run there qman_delete_cgr().
 */
व्योम qman_delete_cgr_safe(काष्ठा qman_cgr *cgr);

/**
 * qman_query_cgr_congested - Queries CGR's congestion status
 * @cgr: the 'cgr' object to query
 * @result: वापसs 'cgr's congestion status, 1 (true) अगर congested
 */
पूर्णांक qman_query_cgr_congested(काष्ठा qman_cgr *cgr, bool *result);

/**
 * qman_alloc_cgrid_range - Allocate a contiguous range of CGR IDs
 * @result: is set by the API to the base CGR ID of the allocated range
 * @count: the number of CGR IDs required
 *
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक qman_alloc_cgrid_range(u32 *result, u32 count);
#घोषणा qman_alloc_cgrid(result) qman_alloc_cgrid_range(result, 1)

/**
 * qman_release_cgrid - Release the specअगरied CGR ID
 * @id: the CGR ID to be released back to the resource pool
 *
 * This function can also be used to seed the allocator with
 * CGR ID ranges that it can subsequently allocate from.
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक qman_release_cgrid(u32 id);

/**
 * qman_is_probed - Check अगर qman is probed
 *
 * Returns 1 अगर the qman driver successfully probed, -1 अगर the qman driver
 * failed to probe or 0 अगर the qman driver did not probed yet.
 */
पूर्णांक qman_is_probed(व्योम);

/**
 * qman_portals_probed - Check अगर all cpu bound qman portals are probed
 *
 * Returns 1 अगर all the required cpu bound qman portals successfully probed,
 * -1 अगर probe errors appeared or 0 अगर the qman portals did not yet finished
 * probing.
 */
पूर्णांक qman_portals_probed(व्योम);

/**
 * qman_dqrr_get_ithresh - Get coalesce पूर्णांकerrupt threshold
 * @portal: portal to get the value क्रम
 * @ithresh: threshold poपूर्णांकer
 */
व्योम qman_dqrr_get_ithresh(काष्ठा qman_portal *portal, u8 *ithresh);

/**
 * qman_dqrr_set_ithresh - Set coalesce पूर्णांकerrupt threshold
 * @portal: portal to set the new value on
 * @ithresh: new threshold value
 *
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक qman_dqrr_set_ithresh(काष्ठा qman_portal *portal, u8 ithresh);

/**
 * qman_dqrr_get_iperiod - Get coalesce पूर्णांकerrupt period
 * @portal: portal to get the value क्रम
 * @iperiod: period poपूर्णांकer
 */
व्योम qman_portal_get_iperiod(काष्ठा qman_portal *portal, u32 *iperiod);

/**
 * qman_dqrr_set_iperiod - Set coalesce पूर्णांकerrupt period
 * @portal: portal to set the new value on
 * @ithresh: new period value
 *
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक qman_portal_set_iperiod(काष्ठा qman_portal *portal, u32 iperiod);

#पूर्ण_अगर	/* __FSL_QMAN_H */
