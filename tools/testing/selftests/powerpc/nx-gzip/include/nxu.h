<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Hardware पूर्णांकerface of the NX-GZIP compression accelerator
 *
 * Copyright (C) IBM Corporation, 2020
 *
 * Author: Bulent Abali <abali@us.ibm.com>
 *
 */

#अगर_अघोषित _NXU_H
#घोषणा _NXU_H

#समावेश <मानक_निवेशt.h>
#समावेश <endian.h>
#समावेश "nx.h"

/* deflate */
#घोषणा LLSZ   286
#घोषणा DSZ    30

/* nx */
#घोषणा DHTSZ  18
#घोषणा DHT_MAXSZ 288
#घोषणा MAX_DDE_COUNT 256

/* util */
#अगर_घोषित NXDBG
#घोषणा NXPRT(X)	X
#अन्यथा
#घोषणा NXPRT(X)
#पूर्ण_अगर

#अगर_घोषित NXTIMER
#समावेश <sys/platक्रमm/ppc.h>
#घोषणा NX_CLK(X)	X
#घोषणा nx_get_समय()	__ppc_get_समयbase()
#घोषणा nx_get_freq()	__ppc_get_समयbase_freq()
#अन्यथा
#घोषणा NX_CLK(X)
#घोषणा nx_get_समय()  (-1)
#घोषणा nx_get_freq()  (-1)
#पूर्ण_अगर

#घोषणा NX_MAX_FAULTS  500

/*
 * Definitions of acronyms used here. See
 * P9 NX Gzip Accelerator User's Manual क्रम details:
 * https://github.com/libnxz/घातer-gzip/blob/develop/करोc/घातer_nx_gzip_um.pdf
 *
 * adler/crc: 32 bit checksums appended to stream tail
 * ce:       completion extension
 * cpb:      coprocessor parameter block (metadata)
 * crb:      coprocessor request block (command)
 * csb:      coprocessor status block (status)
 * dht:      dynamic huffman table
 * dde:      data descriptor element (address, length)
 * ddl:      list of ddes
 * dh/fh:    dynamic and fixed huffman types
 * fc:       coprocessor function code
 * histlen:  history/dictionary length
 * history:  sliding winकरोw of up to 32KB of data
 * lzcount:  Deflate LZ symbol counts
 * rembytecnt: reमुख्यing byte count
 * sfbt:     source final block type; last block's type during decomp
 * spbc:     source processed byte count
 * subc:     source unprocessed bit count
 * tebc:     target ending bit count; valid bits in the last byte
 * tpbc:     target processed byte count
 * vas:      भव accelerator चयन; the user mode पूर्णांकerface
 */

जोड़ nx_qw_t अणु
	uपूर्णांक32_t word[4];
	uपूर्णांक64_t dword[2];
पूर्ण __aligned(16);

/*
 * Note: NX रेजिस्टरs with fewer than 32 bits are declared by
 * convention as uपूर्णांक32_t variables in जोड़s. If *_offset and *_mask
 * are defined क्रम a variable, then use get_ put_ macros to
 * conveniently access the रेजिस्टर fields क्रम endian conversions.
 */

काष्ठा nx_dde_t अणु
	/* Data Descriptor Element, Section 6.4 */
	जोड़ अणु
		uपूर्णांक32_t dde_count;
		/* When dde_count == 0 ddead is a poपूर्णांकer to a data buffer;
		 * ddebc is the buffer length bytes.
		 * When dde_count > 0 dde is an indirect dde; ddead is a
		 * poपूर्णांकer to a contiguous list of direct ddes; ddebc is the
		 * total length of all data poपूर्णांकed to by the list of direct
		 * ddes. Note that only one level of indirection is permitted.
		 * See Section 6.4 of the user manual क्रम additional details.
		 */
	पूर्ण;
	uपूर्णांक32_t ddebc; /* dde byte count */
	uपूर्णांक64_t ddead; /* dde address */
पूर्ण __aligned(16);

काष्ठा nx_csb_t अणु
	/* Coprocessor Status Block, Section 6.6  */
	जोड़ अणु
		uपूर्णांक32_t csb_v;
		/* Valid bit. v must be set to 0 by the program
		 * beक्रमe submitting the coprocessor command.
		 * Software can poll क्रम the v bit
		 */

		uपूर्णांक32_t csb_f;
		/* 16B CSB size. Written to 0 by DMA when it ग_लिखोs the CPB */

		uपूर्णांक32_t csb_cs;
		/* cs completion sequence; unused */

		uपूर्णांक32_t csb_cc;
		/* cc completion code; cc != 0 exception occurred */

		uपूर्णांक32_t csb_ce;
		/* ce completion extension */

	पूर्ण;
	uपूर्णांक32_t tpbc;
	/* target processed byte count TPBC */

	uपूर्णांक64_t fsaddr;
	/* Section 6.12.1 CSB NonZero error summary.  FSA Failing storage
	 * address.  Address where error occurred. When available, written
	 * to A field of CSB
	 */
पूर्ण __aligned(16);

काष्ठा nx_ccb_t अणु
	/* Coprocessor Completion Block, Section 6.7 */

	uपूर्णांक32_t reserved[3];
	जोड़ अणु
		/* When crb.c==0 (no ccb defined) it is reserved;
		 * When crb.c==1 (ccb defined) it is cm
		 */

		uपूर्णांक32_t ccb_cm;
		/* Signal पूर्णांकerrupt of crb.c==1 and cm==1 */

		uपूर्णांक32_t word;
		/* generic access to the 32bit word */
	पूर्ण;
पूर्ण __aligned(16);

काष्ठा vas_stamped_crb_t अणु
	/*
	 * CRB opeअक्रम of the paste coprocessor inकाष्ठाion is stamped
	 * in quadword 4 with the inक्रमmation shown here as its written
	 * in to the receive FIFO of the coprocessor
	 */

	जोड़ अणु
		uपूर्णांक32_t vas_buf_num;
		/* Verअगरication only vas buffer number which correlates to
		 * the low order bits of the atag in the paste command
		 */

		uपूर्णांक32_t send_wc_id;
		/* Poपूर्णांकer to Send Winकरोw Context that provides क्रम NX address
		 * translation inक्रमmation, such as MSR and LPCR bits, job
		 * completion पूर्णांकerrupt RA, PSWID, and job utilization counter.
		 */

	पूर्ण;
	जोड़ अणु
		uपूर्णांक32_t recv_wc_id;
		/* Poपूर्णांकer to Receive Winकरोw Context. NX uses this to वापस
		 * credits to a Receive FIFO as entries are dequeued.
		 */

	पूर्ण;
	uपूर्णांक32_t reserved2;
	जोड़ अणु
		uपूर्णांक32_t vas_invalid;
		/* Invalid bit. If this bit is 1 the CRB is discarded by
		 * NX upon fetching from the receive FIFO. If this bit is 0
		 * the CRB is processed normally. The bit is stamped to 0
		 * by VAS and may be written to 1 by hypervisor जबतक
		 * the CRB is in the receive FIFO (in memory).
		 */

	पूर्ण;
पूर्ण;

काष्ठा nx_stamped_fault_crb_t अणु
	/*
	 * A CRB that has a translation fault is stamped by NX in quadword 4
	 * and pasted to the Fault Send Winकरोw in VAS.
	 */
	uपूर्णांक64_t fsa;
	जोड़ अणु
		uपूर्णांक32_t nxsf_t;
		uपूर्णांक32_t nxsf_fs;
	पूर्ण;
	uपूर्णांक32_t pswid;
पूर्ण;

जोड़ stamped_crb_t अणु
	काष्ठा vas_stamped_crb_t      vas;
	काष्ठा nx_stamped_fault_crb_t nx;
पूर्ण;

काष्ठा nx_gzip_cpb_t अणु
	/*
	 * Coprocessor Parameter Block In/Out are used to pass metadata
	 * to/from accelerator.  Tables 6.5 and 6.6 of the user manual.
	 */

	/* CPBInput */

	काष्ठा अणु
		जोड़ अणु
		जोड़ nx_qw_t qw0;
			काष्ठा अणु
				uपूर्णांक32_t in_adler;            /* bits 0:31  */
				uपूर्णांक32_t in_crc;              /* bits 32:63 */
				जोड़ अणु
					uपूर्णांक32_t in_histlen;  /* bits 64:75 */
					uपूर्णांक32_t in_subc;     /* bits 93:95 */
				पूर्ण;
				जोड़ अणु
					/* bits 108:111 */
					uपूर्णांक32_t in_sfbt;
					/* bits 112:127 */
					uपूर्णांक32_t in_rembytecnt;
					/* bits 116:127 */
					uपूर्णांक32_t in_dhtlen;
				पूर्ण;
			पूर्ण;
		पूर्ण;
		जोड़ अणु
			जोड़ nx_qw_t  in_dht[DHTSZ];	/* qw[1:18]     */
			अक्षर in_dht_अक्षर[DHT_MAXSZ];	/* byte access  */
		पूर्ण;
		जोड़ nx_qw_t  reserved[5];		/* qw[19:23]    */
	पूर्ण;

	/* CPBOutput */

	अस्थिर काष्ठा अणु
		जोड़ अणु
			जोड़ nx_qw_t qw24;
			काष्ठा अणु
				uपूर्णांक32_t out_adler;    /* bits 0:31  qw[24] */
				uपूर्णांक32_t out_crc;      /* bits 32:63 qw[24] */
				जोड़ अणु
					/* bits 77:79 qw[24] */
					uपूर्णांक32_t out_tebc;
					/* bits 80:95 qw[24] */
					uपूर्णांक32_t out_subc;
				पूर्ण;
				जोड़ अणु
					/* bits 108:111 qw[24] */
					uपूर्णांक32_t out_sfbt;
					/* bits 112:127 qw[24] */
					uपूर्णांक32_t out_rembytecnt;
					/* bits 116:127 qw[24] */
					uपूर्णांक32_t out_dhtlen;
				पूर्ण;
			पूर्ण;
		पूर्ण;
		जोड़ अणु
			जोड़ nx_qw_t  qw25[79];        /* qw[25:103] */
			/* qw[25] compress no lzcounts or wrap */
			uपूर्णांक32_t out_spbc_comp_wrap;
			uपूर्णांक32_t out_spbc_wrap;         /* qw[25] wrap */
			/* qw[25] compress no lzcounts */
			uपूर्णांक32_t out_spbc_comp;
			 /* 286 LL and 30 D symbol counts */
			uपूर्णांक32_t out_lzcount[LLSZ+DSZ];
			काष्ठा अणु
				जोड़ nx_qw_t  out_dht[DHTSZ];  /* qw[25:42] */
				/* qw[43] decompress */
				uपूर्णांक32_t out_spbc_decomp;
			पूर्ण;
		पूर्ण;
		/* qw[104] compress with lzcounts */
		uपूर्णांक32_t out_spbc_comp_with_count;
	पूर्ण;
पूर्ण __aligned(128);

काष्ठा nx_gzip_crb_t अणु
	जोड़ अणु                   /* byte[0:3]   */
		uपूर्णांक32_t gzip_fc;     /* bits[24-31] */
	पूर्ण;
	uपूर्णांक32_t reserved1;       /* byte[4:7]   */
	जोड़ अणु
		uपूर्णांक64_t csb_address; /* byte[8:15]  */
		काष्ठा अणु
			uपूर्णांक32_t reserved2;
			जोड़ अणु
				uपूर्णांक32_t crb_c;
				/* c==0 no ccb defined */

				uपूर्णांक32_t crb_at;
				/* at==0 address type is ignored;
				 * all addrs effective assumed.
				 */

			पूर्ण;
		पूर्ण;
	पूर्ण;
	काष्ठा nx_dde_t source_dde;           /* byte[16:31] */
	काष्ठा nx_dde_t target_dde;           /* byte[32:47] */
	अस्थिर काष्ठा nx_ccb_t ccb;         /* byte[48:63] */
	अस्थिर जोड़ अणु
		/* byte[64:239] shअगरt csb by 128 bytes out of the crb; csb was
		 * in crb earlier; JReilly says csb written with partial inject
		 */
		जोड़ nx_qw_t reserved64[11];
		जोड़ stamped_crb_t stamp;       /* byte[64:79] */
	पूर्ण;
	अस्थिर काष्ठा nx_csb_t csb;
पूर्ण __aligned(128);

काष्ठा nx_gzip_crb_cpb_t अणु
	काष्ठा nx_gzip_crb_t crb;
	काष्ठा nx_gzip_cpb_t cpb;
पूर्ण __aligned(2048);


/*
 * NX hardware convention has the msb bit on the left numbered 0.
 * The defines below has *_offset defined as the right most bit
 * position of a field.  x of size_mask(x) is the field width in bits.
 */

#घोषणा size_mask(x)          ((1U<<(x))-1)

/*
 * Offsets and Widths within the containing 32 bits of the various NX
 * gzip hardware रेजिस्टरs.  Use the getnn/putnn macros to access
 * these regs
 */

#घोषणा dde_count_mask        size_mask(8)
#घोषणा dde_count_offset      23

/* CSB */

#घोषणा csb_v_mask            size_mask(1)
#घोषणा csb_v_offset          0
#घोषणा csb_f_mask            size_mask(1)
#घोषणा csb_f_offset          6
#घोषणा csb_cs_mask           size_mask(8)
#घोषणा csb_cs_offset         15
#घोषणा csb_cc_mask           size_mask(8)
#घोषणा csb_cc_offset         23
#घोषणा csb_ce_mask           size_mask(8)
#घोषणा csb_ce_offset         31

/* CCB */

#घोषणा ccb_cm_mask           size_mask(3)
#घोषणा ccb_cm_offset         31

/* VAS stamped CRB fields */

#घोषणा vas_buf_num_mask      size_mask(6)
#घोषणा vas_buf_num_offset    5
#घोषणा send_wc_id_mask       size_mask(16)
#घोषणा send_wc_id_offset     31
#घोषणा recv_wc_id_mask       size_mask(16)
#घोषणा recv_wc_id_offset     31
#घोषणा vas_invalid_mask      size_mask(1)
#घोषणा vas_invalid_offset    31

/* NX stamped fault CRB fields */

#घोषणा nxsf_t_mask           size_mask(1)
#घोषणा nxsf_t_offset         23
#घोषणा nxsf_fs_mask          size_mask(8)
#घोषणा nxsf_fs_offset        31

/* CPB input */

#घोषणा in_histlen_mask       size_mask(12)
#घोषणा in_histlen_offset     11
#घोषणा in_dhtlen_mask        size_mask(12)
#घोषणा in_dhtlen_offset      31
#घोषणा in_subc_mask          size_mask(3)
#घोषणा in_subc_offset        31
#घोषणा in_sfbt_mask          size_mask(4)
#घोषणा in_sfbt_offset        15
#घोषणा in_rembytecnt_mask    size_mask(16)
#घोषणा in_rembytecnt_offset  31

/* CPB output */

#घोषणा out_tebc_mask         size_mask(3)
#घोषणा out_tebc_offset       15
#घोषणा out_subc_mask         size_mask(16)
#घोषणा out_subc_offset       31
#घोषणा out_sfbt_mask         size_mask(4)
#घोषणा out_sfbt_offset       15
#घोषणा out_rembytecnt_mask   size_mask(16)
#घोषणा out_rembytecnt_offset 31
#घोषणा out_dhtlen_mask       size_mask(12)
#घोषणा out_dhtlen_offset     31

/* CRB */

#घोषणा gzip_fc_mask          size_mask(8)
#घोषणा gzip_fc_offset        31
#घोषणा crb_c_mask            size_mask(1)
#घोषणा crb_c_offset          28
#घोषणा crb_at_mask           size_mask(1)
#घोषणा crb_at_offset         30
#घोषणा csb_address_mask      ~(15UL) /* mask off bottom 4b */

/*
 * Access macros क्रम the रेजिस्टरs.  Do not access रेजिस्टरs directly
 * because of the endian conversion.  P9 processor may run either as
 * Little or Big endian. However the NX coprocessor regs are always
 * big endian.
 * Use the 32 and 64b macros to access respective
 * रेजिस्टर sizes.
 * Use nn क्रमms क्रम the रेजिस्टर fields लघुer than 32 bits.
 */

#घोषणा getnn(ST, REG)      ((be32toh(ST.REG) >> (31-REG##_offset)) \
				 & REG##_mask)
#घोषणा getpnn(ST, REG)     ((be32toh((ST)->REG) >> (31-REG##_offset)) \
				 & REG##_mask)
#घोषणा get32(ST, REG)      (be32toh(ST.REG))
#घोषणा getp32(ST, REG)     (be32toh((ST)->REG))
#घोषणा get64(ST, REG)      (be64toh(ST.REG))
#घोषणा getp64(ST, REG)     (be64toh((ST)->REG))

#घोषणा unget32(ST, REG)    (get32(ST, REG) & ~((REG##_mask) \
				<< (31-REG##_offset)))
/* get 32bits less the REG field */

#घोषणा ungetp32(ST, REG)   (getp32(ST, REG) & ~((REG##_mask) \
				<< (31-REG##_offset)))
/* get 32bits less the REG field */

#घोषणा clear_regs(ST)      स_रखो((व्योम *)(&(ST)), 0, माप(ST))
#घोषणा clear_dde(ST)       करो अणु ST.dde_count = ST.ddebc = 0; ST.ddead = 0; \
				पूर्ण जबतक (0)
#घोषणा clearp_dde(ST)      करो अणु (ST)->dde_count = (ST)->ddebc = 0; \
				 (ST)->ddead = 0; \
				पूर्ण जबतक (0)
#घोषणा clear_काष्ठा(ST)    स_रखो((व्योम *)(&(ST)), 0, माप(ST))
#घोषणा putnn(ST, REG, X)   (ST.REG = htobe32(unget32(ST, REG) | (((X) \
				 & REG##_mask) << (31-REG##_offset))))
#घोषणा putpnn(ST, REG, X)  ((ST)->REG = htobe32(ungetp32(ST, REG) \
				| (((X) & REG##_mask) << (31-REG##_offset))))

#घोषणा put32(ST, REG, X)   (ST.REG = htobe32(X))
#घोषणा putp32(ST, REG, X)  ((ST)->REG = htobe32(X))
#घोषणा put64(ST, REG, X)   (ST.REG = htobe64(X))
#घोषणा putp64(ST, REG, X)  ((ST)->REG = htobe64(X))

/*
 * Completion extension ce(0) ce(1) ce(2).  Bits ce(3-7)
 * unused.  Section 6.6 Figure 6.7.
 */

#घोषणा get_csb_ce(ST) ((uपूर्णांक32_t)getnn(ST, csb_ce))
#घोषणा get_csb_ce_ms3b(ST) (get_csb_ce(ST) >> 5)
#घोषणा put_csb_ce_ms3b(ST, X) putnn(ST, csb_ce, ((uपूर्णांक32_t)(X) << 5))

#घोषणा CSB_CE_PARTIAL         0x4
#घोषणा CSB_CE_TERMINATE       0x2
#घोषणा CSB_CE_TPBC_VALID      0x1

#घोषणा csb_ce_termination(X)         (!!((X) & CSB_CE_TERMINATE))
/* termination, output buffers may be modअगरied, SPBC/TPBC invalid Fig.6-7 */

#घोषणा csb_ce_check_completion(X)    (!csb_ce_termination(X))
/* अगर not terminated then check full or partial completion */

#घोषणा csb_ce_partial_completion(X)  (!!((X) & CSB_CE_PARTIAL))
#घोषणा csb_ce_full_completion(X)     (!csb_ce_partial_completion(X))
#घोषणा csb_ce_tpbc_valid(X)          (!!((X) & CSB_CE_TPBC_VALID))
/* TPBC indicates successfully stored data count */

#घोषणा csb_ce_शेष_err(X)         csb_ce_termination(X)
/* most error CEs have CE(0)=0 and CE(1)=1 */

#घोषणा csb_ce_cc3_partial(X)         csb_ce_partial_completion(X)
/* some CC=3 are partially completed, Table 6-8 */

#घोषणा csb_ce_cc64(X)                ((X)&(CSB_CE_PARTIAL \
					| CSB_CE_TERMINATE) == 0)
/* Compression: when TPBC>SPBC then CC=64 Table 6-8; target didn't
 * compress smaller than source.
 */

/* Decompress SFBT combinations Tables 5-3, 6-4, 6-6 */

#घोषणा SFBT_BFINAL 0x1
#घोषणा SFBT_LIT    0x4
#घोषणा SFBT_FHT    0x5
#घोषणा SFBT_DHT    0x6
#घोषणा SFBT_HDR    0x7

/*
 * NX gzip function codes. Table 6.2.
 * Bits 0:4 are the FC. Bit 5 is used by the DMA controller to
 * select one of the two Byte Count Limits.
 */

#घोषणा GZIP_FC_LIMIT_MASK                               0x01
#घोषणा GZIP_FC_COMPRESS_FHT                             0x00
#घोषणा GZIP_FC_COMPRESS_DHT                             0x02
#घोषणा GZIP_FC_COMPRESS_FHT_COUNT                       0x04
#घोषणा GZIP_FC_COMPRESS_DHT_COUNT                       0x06
#घोषणा GZIP_FC_COMPRESS_RESUME_FHT                      0x08
#घोषणा GZIP_FC_COMPRESS_RESUME_DHT                      0x0a
#घोषणा GZIP_FC_COMPRESS_RESUME_FHT_COUNT                0x0c
#घोषणा GZIP_FC_COMPRESS_RESUME_DHT_COUNT                0x0e
#घोषणा GZIP_FC_DECOMPRESS                               0x10
#घोषणा GZIP_FC_DECOMPRESS_SINGLE_BLK_N_SUSPEND          0x12
#घोषणा GZIP_FC_DECOMPRESS_RESUME                        0x14
#घोषणा GZIP_FC_DECOMPRESS_RESUME_SINGLE_BLK_N_SUSPEND   0x16
#घोषणा GZIP_FC_WRAP                                     0x1e

#घोषणा fc_is_compress(fc)  (((fc) & 0x10) == 0)
#घोषणा fc_has_count(fc)    (fc_is_compress(fc) && (((fc) & 0x4) != 0))

/* CSB.CC Error codes */

#घोषणा ERR_NX_OK             0
#घोषणा ERR_NX_ALIGNMENT      1
#घोषणा ERR_NX_OPOVERLAP      2
#घोषणा ERR_NX_DATA_LENGTH    3
#घोषणा ERR_NX_TRANSLATION    5
#घोषणा ERR_NX_PROTECTION     6
#घोषणा ERR_NX_EXTERNAL_UE7   7
#घोषणा ERR_NX_INVALID_OP     8
#घोषणा ERR_NX_PRIVILEGE      9
#घोषणा ERR_NX_INTERNAL_UE   10
#घोषणा ERR_NX_EXTERN_UE_WR  12
#घोषणा ERR_NX_TARGET_SPACE  13
#घोषणा ERR_NX_EXCESSIVE_DDE 14
#घोषणा ERR_NX_TRANSL_WR     15
#घोषणा ERR_NX_PROTECT_WR    16
#घोषणा ERR_NX_SUBFUNCTION   17
#घोषणा ERR_NX_FUNC_ABORT    18
#घोषणा ERR_NX_BYTE_MAX      19
#घोषणा ERR_NX_CORRUPT_CRB   20
#घोषणा ERR_NX_INVALID_CRB   21
#घोषणा ERR_NX_INVALID_DDE   30
#घोषणा ERR_NX_SEGMENTED_DDL 31
#घोषणा ERR_NX_DDE_OVERFLOW  33
#घोषणा ERR_NX_TPBC_GT_SPBC  64
#घोषणा ERR_NX_MISSING_CODE  66
#घोषणा ERR_NX_INVALID_DIST  67
#घोषणा ERR_NX_INVALID_DHT   68
#घोषणा ERR_NX_EXTERNAL_UE90 90
#घोषणा ERR_NX_WDOG_TIMER   224
#घोषणा ERR_NX_AT_FAULT     250
#घोषणा ERR_NX_INTR_SERVER  252
#घोषणा ERR_NX_UE253        253
#घोषणा ERR_NX_NO_HW        254
#घोषणा ERR_NX_HUNG_OP      255
#घोषणा ERR_NX_END          256

/* initial values क्रम non-resume operations */
#घोषणा INIT_CRC   0  /* crc32(0L, Z_शून्य, 0) */
#घोषणा INIT_ADLER 1  /* adler32(0L, Z_शून्य, 0)  adler is initialized to 1 */

/* prototypes */
पूर्णांक nxu_submit_job(काष्ठा nx_gzip_crb_cpb_t *c, व्योम *handle);

बाह्य व्योम nxu_sigsegv_handler(पूर्णांक sig, siginfo_t *info, व्योम *ctx);
बाह्य पूर्णांक nxu_touch_pages(व्योम *buf, दीर्घ buf_len, दीर्घ page_len, पूर्णांक wr);

/* caller supplies a prपूर्णांक buffer 4*माप(crb) */

अक्षर *nx_crb_str(काष्ठा nx_gzip_crb_t *crb, अक्षर *prbuf);
अक्षर *nx_cpb_str(काष्ठा nx_gzip_cpb_t *cpb, अक्षर *prbuf);
अक्षर *nx_prt_hex(व्योम *cp, पूर्णांक sz, अक्षर *prbuf);
अक्षर *nx_lzcount_str(काष्ठा nx_gzip_cpb_t *cpb, अक्षर *prbuf);
अक्षर *nx_म_त्रुटि(पूर्णांक e);

#अगर_घोषित NX_SIM
#समावेश <मानकपन.स>
पूर्णांक nx_sim_init(व्योम *ctx);
पूर्णांक nx_sim_end(व्योम *ctx);
पूर्णांक nxu_run_sim_job(काष्ठा nx_gzip_crb_cpb_t *c, व्योम *ctx);
#पूर्ण_अगर /* NX_SIM */

/* Deflate stream manipulation */

#घोषणा set_final_bit(x)	(x |= (अचिन्हित अक्षर)1)
#घोषणा clr_final_bit(x)	(x &= ~(अचिन्हित अक्षर)1)

#घोषणा append_empty_fh_blk(p, b) करो अणु *(p) = (2 | (1&(b))); *((p)+1) = 0; \
					पूर्ण जबतक (0)
/* append 10 bits 0000001b 00...... ;
 * assumes appending starts on a byte boundary; b is the final bit.
 */


#अगर_घोषित NX_842

/* 842 Engine */

काष्ठा nx_eft_crb_t अणु
	जोड़ अणु                   /* byte[0:3]   */
		uपूर्णांक32_t eft_fc;      /* bits[29-31] */
	पूर्ण;
	uपूर्णांक32_t reserved1;       /* byte[4:7]   */
	जोड़ अणु
		uपूर्णांक64_t csb_address; /* byte[8:15]  */
		काष्ठा अणु
			uपूर्णांक32_t reserved2;
			जोड़ अणु
				uपूर्णांक32_t crb_c;
				/* c==0 no ccb defined */

				uपूर्णांक32_t crb_at;
				/* at==0 address type is ignored;
				 * all addrs effective assumed.
				 */

			पूर्ण;
		पूर्ण;
	पूर्ण;
	काष्ठा nx_dde_t source_dde;           /* byte[16:31] */
	काष्ठा nx_dde_t target_dde;           /* byte[32:47] */
	काष्ठा nx_ccb_t ccb;                  /* byte[48:63] */
	जोड़ अणु
		जोड़ nx_qw_t reserved64[3];     /* byte[64:96] */
	पूर्ण;
	काष्ठा nx_csb_t csb;
पूर्ण __aligned(128);

/* 842 CRB */

#घोषणा EFT_FC_MASK                 size_mask(3)
#घोषणा EFT_FC_OFFSET               31
#घोषणा EFT_FC_COMPRESS             0x0
#घोषणा EFT_FC_COMPRESS_WITH_CRC    0x1
#घोषणा EFT_FC_DECOMPRESS           0x2
#घोषणा EFT_FC_DECOMPRESS_WITH_CRC  0x3
#घोषणा EFT_FC_BLK_DATA_MOVE        0x4
#पूर्ण_अगर /* NX_842 */

#पूर्ण_अगर /* _NXU_H */
