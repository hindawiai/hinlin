<शैली गुरु>
/*
 * Copyright 2017 NXP
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of NXP nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NXP BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>

#समावेश "fman_keygen.h"

/* Maximum number of HW Ports */
#घोषणा FMAN_MAX_NUM_OF_HW_PORTS		64

/* Maximum number of KeyGen Schemes */
#घोषणा FM_KG_MAX_NUM_OF_SCHEMES		32

/* Number of generic KeyGen Generic Extract Command Registers */
#घोषणा FM_KG_NUM_OF_GENERIC_REGS		8

/* Dummy port ID */
#घोषणा DUMMY_PORT_ID				0

/* Select Scheme Value Register */
#घोषणा KG_SCH_DEF_USE_KGSE_DV_0		2
#घोषणा KG_SCH_DEF_USE_KGSE_DV_1		3

/* Registers Shअगरting values */
#घोषणा FM_KG_KGAR_NUM_SHIFT			16
#घोषणा KG_SCH_DEF_L4_PORT_SHIFT		8
#घोषणा KG_SCH_DEF_IP_ADDR_SHIFT		18
#घोषणा KG_SCH_HASH_CONFIG_SHIFT_SHIFT		24

/* KeyGen Registers bit field masks: */

/* Enable bit field mask क्रम KeyGen General Configuration Register */
#घोषणा FM_KG_KGGCR_EN				0x80000000

/* KeyGen Global Registers bit field masks */
#घोषणा FM_KG_KGAR_GO				0x80000000
#घोषणा FM_KG_KGAR_READ				0x40000000
#घोषणा FM_KG_KGAR_WRITE			0x00000000
#घोषणा FM_KG_KGAR_SEL_SCHEME_ENTRY		0x00000000
#घोषणा FM_KG_KGAR_SCM_WSEL_UPDATE_CNT		0x00008000

#घोषणा FM_KG_KGAR_ERR				0x20000000
#घोषणा FM_KG_KGAR_SEL_CLS_PLAN_ENTRY		0x01000000
#घोषणा FM_KG_KGAR_SEL_PORT_ENTRY		0x02000000
#घोषणा FM_KG_KGAR_SEL_PORT_WSEL_SP		0x00008000
#घोषणा FM_KG_KGAR_SEL_PORT_WSEL_CPP		0x00004000

/* Error events exceptions */
#घोषणा FM_EX_KG_DOUBLE_ECC			0x80000000
#घोषणा FM_EX_KG_KEYSIZE_OVERFLOW		0x40000000

/* Scheme Registers bit field masks */
#घोषणा KG_SCH_MODE_EN				0x80000000
#घोषणा KG_SCH_VSP_NO_KSP_EN			0x80000000
#घोषणा KG_SCH_HASH_CONFIG_SYM			0x40000000

/* Known Protocol field codes */
#घोषणा KG_SCH_KN_PORT_ID		0x80000000
#घोषणा KG_SCH_KN_MACDST		0x40000000
#घोषणा KG_SCH_KN_MACSRC		0x20000000
#घोषणा KG_SCH_KN_TCI1			0x10000000
#घोषणा KG_SCH_KN_TCI2			0x08000000
#घोषणा KG_SCH_KN_ETYPE			0x04000000
#घोषणा KG_SCH_KN_PPPSID		0x02000000
#घोषणा KG_SCH_KN_PPPID			0x01000000
#घोषणा KG_SCH_KN_MPLS1			0x00800000
#घोषणा KG_SCH_KN_MPLS2			0x00400000
#घोषणा KG_SCH_KN_MPLS_LAST		0x00200000
#घोषणा KG_SCH_KN_IPSRC1		0x00100000
#घोषणा KG_SCH_KN_IPDST1		0x00080000
#घोषणा KG_SCH_KN_PTYPE1		0x00040000
#घोषणा KG_SCH_KN_IPTOS_TC1		0x00020000
#घोषणा KG_SCH_KN_IPV6FL1		0x00010000
#घोषणा KG_SCH_KN_IPSRC2		0x00008000
#घोषणा KG_SCH_KN_IPDST2		0x00004000
#घोषणा KG_SCH_KN_PTYPE2		0x00002000
#घोषणा KG_SCH_KN_IPTOS_TC2		0x00001000
#घोषणा KG_SCH_KN_IPV6FL2		0x00000800
#घोषणा KG_SCH_KN_GREPTYPE		0x00000400
#घोषणा KG_SCH_KN_IPSEC_SPI		0x00000200
#घोषणा KG_SCH_KN_IPSEC_NH		0x00000100
#घोषणा KG_SCH_KN_IPPID			0x00000080
#घोषणा KG_SCH_KN_L4PSRC		0x00000004
#घोषणा KG_SCH_KN_L4PDST		0x00000002
#घोषणा KG_SCH_KN_TFLG			0x00000001

/* NIA values */
#घोषणा NIA_ENG_BMI			0x00500000
#घोषणा NIA_BMI_AC_ENQ_FRAME		0x00000002
#घोषणा ENQUEUE_KG_DFLT_NIA		(NIA_ENG_BMI | NIA_BMI_AC_ENQ_FRAME)

/* Hard-coded configuration:
 * These values are used as hard-coded values क्रम KeyGen configuration
 * and they replace user selections क्रम this hard-coded version
 */

/* Hash distribution shअगरt */
#घोषणा DEFAULT_HASH_DIST_FQID_SHIFT		0

/* Hash shअगरt */
#घोषणा DEFAULT_HASH_SHIFT			0

/* Symmetric hash usage:
 * Warning:
 * - the value क्रम symmetric hash usage must be in accordance with hash
 *	key defined below
 * - according to tests perक्रमmed, spपढ़ोing is not working अगर symmetric
 *	hash is set on true
 * So ultimately symmetric hash functionality should be always disabled:
 */
#घोषणा DEFAULT_SYMMETRIC_HASH			false

/* Hash Key extraction fields: */
#घोषणा DEFAULT_HASH_KEY_EXTRACT_FIELDS		\
	(KG_SCH_KN_IPSRC1 | KG_SCH_KN_IPDST1 | \
	 KG_SCH_KN_L4PSRC | KG_SCH_KN_L4PDST | \
	 KG_SCH_KN_IPSEC_SPI)

/* Default values to be used as hash key in हाल IPv4 or L4 (TCP, UDP)
 * करोn't exist in the frame
 */
/* Default IPv4 address */
#घोषणा DEFAULT_HASH_KEY_IPv4_ADDR		0x0A0A0A0A
/* Default L4 port */
#घोषणा DEFAULT_HASH_KEY_L4_PORT		0x0B0B0B0B

/* KeyGen Memory Mapped Registers: */

/* Scheme Configuration RAM Registers */
काष्ठा fman_kg_scheme_regs अणु
	u32 kgse_mode;		/* 0x100: MODE */
	u32 kgse_ekfc;		/* 0x104: Extract Known Fields Command */
	u32 kgse_ekdv;		/* 0x108: Extract Known Default Value */
	u32 kgse_bmch;		/* 0x10C: Bit Mask Command High */
	u32 kgse_bmcl;		/* 0x110: Bit Mask Command Low */
	u32 kgse_fqb;		/* 0x114: Frame Queue Base */
	u32 kgse_hc;		/* 0x118: Hash Command */
	u32 kgse_ppc;		/* 0x11C: Policer Profile Command */
	u32 kgse_gec[FM_KG_NUM_OF_GENERIC_REGS];
			/* 0x120: Generic Extract Command */
	u32 kgse_spc;
		/* 0x140: KeyGen Scheme Entry Statistic Packet Counter */
	u32 kgse_dv0;	/* 0x144: KeyGen Scheme Entry Default Value 0 */
	u32 kgse_dv1;	/* 0x148: KeyGen Scheme Entry Default Value 1 */
	u32 kgse_ccbs;
		/* 0x14C: KeyGen Scheme Entry Coarse Classअगरication Bit*/
	u32 kgse_mv;	/* 0x150: KeyGen Scheme Entry Match vector */
	u32 kgse_om;	/* 0x154: KeyGen Scheme Entry Operation Mode bits */
	u32 kgse_vsp;
		/* 0x158: KeyGen Scheme Entry Virtual Storage Profile */
पूर्ण;

/* Port Partition Configuration Registers */
काष्ठा fman_kg_pe_regs अणु
	u32 fmkg_pe_sp;		/* 0x100: KeyGen Port entry Scheme Partition */
	u32 fmkg_pe_cpp;
		/* 0x104: KeyGen Port Entry Classअगरication Plan Partition */
पूर्ण;

/* General Configuration and Status Registers
 * Global Statistic Counters
 * KeyGen Global Registers
 */
काष्ठा fman_kg_regs अणु
	u32 fmkg_gcr;	/* 0x000: KeyGen General Configuration Register */
	u32 res004;	/* 0x004: Reserved */
	u32 res008;	/* 0x008: Reserved */
	u32 fmkg_eer;	/* 0x00C: KeyGen Error Event Register */
	u32 fmkg_eeer;	/* 0x010: KeyGen Error Event Enable Register */
	u32 res014;	/* 0x014: Reserved */
	u32 res018;	/* 0x018: Reserved */
	u32 fmkg_seer;	/* 0x01C: KeyGen Scheme Error Event Register */
	u32 fmkg_seeer;	/* 0x020: KeyGen Scheme Error Event Enable Register */
	u32 fmkg_gsr;	/* 0x024: KeyGen Global Status Register */
	u32 fmkg_tpc;	/* 0x028: Total Packet Counter Register */
	u32 fmkg_serc;	/* 0x02C: Soft Error Capture Register */
	u32 res030[4];	/* 0x030: Reserved */
	u32 fmkg_fकरोr;	/* 0x034: Frame Data Offset Register */
	u32 fmkg_gdv0r;	/* 0x038: Global Default Value Register 0 */
	u32 fmkg_gdv1r;	/* 0x03C: Global Default Value Register 1 */
	u32 res04c[6];	/* 0x040: Reserved */
	u32 fmkg_feer;	/* 0x044: Force Error Event Register */
	u32 res068[38];	/* 0x048: Reserved */
	जोड़ अणु
		u32 fmkg_indirect[63];	/* 0x100: Indirect Access Registers */
		काष्ठा fman_kg_scheme_regs fmkg_sch; /* Scheme Registers */
		काष्ठा fman_kg_pe_regs fmkg_pe; /* Port Partition Registers */
	पूर्ण;
	u32 fmkg_ar;	/* 0x1FC: KeyGen Action Register */
पूर्ण;

/* KeyGen Scheme data */
काष्ठा keygen_scheme अणु
	bool used;	/* Specअगरies अगर this scheme is used */
	u8 hw_port_id;
		/* Hardware port ID
		 * schemes sharing between multiple ports is not
		 * currently supported
		 * so we have only one port id bound to a scheme
		 */
	u32 base_fqid;
		/* Base FQID:
		 * Must be between 1 and 2^24-1
		 * If hash is used and an even distribution is
		 * expected according to hash_fqid_count,
		 * base_fqid must be aligned to hash_fqid_count
		 */
	u32 hash_fqid_count;
		/* FQ range क्रम hash distribution:
		 * Must be a घातer of 2
		 * Represents the range of queues क्रम spपढ़ोing
		 */
	bool use_hashing;	/* Usage of Hashing and spपढ़ोing over FQ */
	bool symmetric_hash;	/* Symmetric Hash option usage */
	u8 hashShअगरt;
		/* Hash result right shअगरt.
		 * Select the 24 bits out of the 64 hash result.
		 * 0 means using the 24 LSB's, otherwise
		 * use the 24 LSB's after shअगरting right
		 */
	u32 match_vector;	/* Match Vector */
पूर्ण;

/* KeyGen driver data */
काष्ठा fman_keygen अणु
	काष्ठा keygen_scheme schemes[FM_KG_MAX_NUM_OF_SCHEMES];
				/* Array of schemes */
	काष्ठा fman_kg_regs __iomem *keygen_regs;	/* KeyGen रेजिस्टरs */
पूर्ण;

/* keygen_ग_लिखो_ar_रुको
 *
 * Write Action Register with specअगरied value, रुको क्रम GO bit field to be
 * idle and then पढ़ो the error
 *
 * regs: KeyGen रेजिस्टरs
 * fmkg_ar: Action Register value
 *
 * Return: Zero क्रम success or error code in हाल of failure
 */
अटल पूर्णांक keygen_ग_लिखो_ar_रुको(काष्ठा fman_kg_regs __iomem *regs, u32 fmkg_ar)
अणु
	ioग_लिखो32be(fmkg_ar, &regs->fmkg_ar);

	/* Wait क्रम GO bit field to be idle */
	जबतक (fmkg_ar & FM_KG_KGAR_GO)
		fmkg_ar = ioपढ़ो32be(&regs->fmkg_ar);

	अगर (fmkg_ar & FM_KG_KGAR_ERR)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* build_ar_scheme
 *
 * Build Action Register value क्रम scheme settings
 *
 * scheme_id: Scheme ID
 * update_counter: update scheme counter
 * ग_लिखो: true क्रम action to ग_लिखो the scheme or false क्रम पढ़ो action
 *
 * Return: AR value
 */
अटल u32 build_ar_scheme(u8 scheme_id, bool update_counter, bool ग_लिखो)
अणु
	u32 rw = (u32)(ग_लिखो ? FM_KG_KGAR_WRITE : FM_KG_KGAR_READ);

	वापस (u32)(FM_KG_KGAR_GO |
			rw |
			FM_KG_KGAR_SEL_SCHEME_ENTRY |
			DUMMY_PORT_ID |
			((u32)scheme_id << FM_KG_KGAR_NUM_SHIFT) |
			(update_counter ? FM_KG_KGAR_SCM_WSEL_UPDATE_CNT : 0));
पूर्ण

/* build_ar_bind_scheme
 *
 * Build Action Register value क्रम port binding to schemes
 *
 * hwport_id: HW Port ID
 * ग_लिखो: true क्रम action to ग_लिखो the bind or false क्रम पढ़ो action
 *
 * Return: AR value
 */
अटल u32 build_ar_bind_scheme(u8 hwport_id, bool ग_लिखो)
अणु
	u32 rw = ग_लिखो ? (u32)FM_KG_KGAR_WRITE : (u32)FM_KG_KGAR_READ;

	वापस (u32)(FM_KG_KGAR_GO |
			rw |
			FM_KG_KGAR_SEL_PORT_ENTRY |
			hwport_id |
			FM_KG_KGAR_SEL_PORT_WSEL_SP);
पूर्ण

/* keygen_ग_लिखो_sp
 *
 * Write Scheme Partition Register with specअगरied value
 *
 * regs: KeyGen Registers
 * sp: Scheme Partition रेजिस्टर value
 * add: true to add a scheme partition or false to clear
 *
 * Return: none
 */
अटल व्योम keygen_ग_लिखो_sp(काष्ठा fman_kg_regs __iomem *regs, u32 sp, bool add)
अणु
	u32 पंचांगp;

	पंचांगp = ioपढ़ो32be(&regs->fmkg_pe.fmkg_pe_sp);

	अगर (add)
		पंचांगp |= sp;
	अन्यथा
		पंचांगp &= ~sp;

	ioग_लिखो32be(पंचांगp, &regs->fmkg_pe.fmkg_pe_sp);
पूर्ण

/* build_ar_bind_cls_plan
 *
 * Build Action Register value क्रम Classअगरication Plan
 *
 * hwport_id: HW Port ID
 * ग_लिखो: true क्रम action to ग_लिखो the CP or false क्रम पढ़ो action
 *
 * Return: AR value
 */
अटल u32 build_ar_bind_cls_plan(u8 hwport_id, bool ग_लिखो)
अणु
	u32 rw = ग_लिखो ? (u32)FM_KG_KGAR_WRITE : (u32)FM_KG_KGAR_READ;

	वापस (u32)(FM_KG_KGAR_GO |
			rw |
			FM_KG_KGAR_SEL_PORT_ENTRY |
			hwport_id |
			FM_KG_KGAR_SEL_PORT_WSEL_CPP);
पूर्ण

/* keygen_ग_लिखो_cpp
 *
 * Write Classअगरication Plan Partition Register with specअगरied value
 *
 * regs: KeyGen Registers
 * cpp: CPP रेजिस्टर value
 *
 * Return: none
 */
अटल व्योम keygen_ग_लिखो_cpp(काष्ठा fman_kg_regs __iomem *regs, u32 cpp)
अणु
	ioग_लिखो32be(cpp, &regs->fmkg_pe.fmkg_pe_cpp);
पूर्ण

/* keygen_ग_लिखो_scheme
 *
 * Write all Schemes Registers with specअगरied values
 *
 * regs: KeyGen Registers
 * scheme_id: Scheme ID
 * scheme_regs: Scheme रेजिस्टरs values desired to be written
 * update_counter: update scheme counter
 *
 * Return: Zero क्रम success or error code in हाल of failure
 */
अटल पूर्णांक keygen_ग_लिखो_scheme(काष्ठा fman_kg_regs __iomem *regs, u8 scheme_id,
			       काष्ठा fman_kg_scheme_regs *scheme_regs,
				bool update_counter)
अणु
	u32 ar_reg;
	पूर्णांक err, i;

	/* Write indirect scheme रेजिस्टरs */
	ioग_लिखो32be(scheme_regs->kgse_mode, &regs->fmkg_sch.kgse_mode);
	ioग_लिखो32be(scheme_regs->kgse_ekfc, &regs->fmkg_sch.kgse_ekfc);
	ioग_लिखो32be(scheme_regs->kgse_ekdv, &regs->fmkg_sch.kgse_ekdv);
	ioग_लिखो32be(scheme_regs->kgse_bmch, &regs->fmkg_sch.kgse_bmch);
	ioग_लिखो32be(scheme_regs->kgse_bmcl, &regs->fmkg_sch.kgse_bmcl);
	ioग_लिखो32be(scheme_regs->kgse_fqb, &regs->fmkg_sch.kgse_fqb);
	ioग_लिखो32be(scheme_regs->kgse_hc, &regs->fmkg_sch.kgse_hc);
	ioग_लिखो32be(scheme_regs->kgse_ppc, &regs->fmkg_sch.kgse_ppc);
	ioग_लिखो32be(scheme_regs->kgse_spc, &regs->fmkg_sch.kgse_spc);
	ioग_लिखो32be(scheme_regs->kgse_dv0, &regs->fmkg_sch.kgse_dv0);
	ioग_लिखो32be(scheme_regs->kgse_dv1, &regs->fmkg_sch.kgse_dv1);
	ioग_लिखो32be(scheme_regs->kgse_ccbs, &regs->fmkg_sch.kgse_ccbs);
	ioग_लिखो32be(scheme_regs->kgse_mv, &regs->fmkg_sch.kgse_mv);
	ioग_लिखो32be(scheme_regs->kgse_om, &regs->fmkg_sch.kgse_om);
	ioग_लिखो32be(scheme_regs->kgse_vsp, &regs->fmkg_sch.kgse_vsp);

	क्रम (i = 0 ; i < FM_KG_NUM_OF_GENERIC_REGS ; i++)
		ioग_लिखो32be(scheme_regs->kgse_gec[i],
			    &regs->fmkg_sch.kgse_gec[i]);

	/* Write AR (Action रेजिस्टर) */
	ar_reg = build_ar_scheme(scheme_id, update_counter, true);
	err = keygen_ग_लिखो_ar_रुको(regs, ar_reg);
	अगर (err != 0) अणु
		pr_err("Writing Action Register failed\n");
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

/* get_मुक्त_scheme_id
 *
 * Find the first मुक्त scheme available to be used
 *
 * keygen: KeyGen handle
 * scheme_id: poपूर्णांकer to scheme id
 *
 * Return: 0 on success, -EINVAL when the are no available मुक्त schemes
 */
अटल पूर्णांक get_मुक्त_scheme_id(काष्ठा fman_keygen *keygen, u8 *scheme_id)
अणु
	u8 i;

	क्रम (i = 0; i < FM_KG_MAX_NUM_OF_SCHEMES; i++)
		अगर (!keygen->schemes[i].used) अणु
			*scheme_id = i;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

/* get_scheme
 *
 * Provides the scheme क्रम specअगरied ID
 *
 * keygen: KeyGen handle
 * scheme_id: Scheme ID
 *
 * Return: handle to required scheme
 */
अटल काष्ठा keygen_scheme *get_scheme(काष्ठा fman_keygen *keygen,
					u8 scheme_id)
अणु
	अगर (scheme_id >= FM_KG_MAX_NUM_OF_SCHEMES)
		वापस शून्य;
	वापस &keygen->schemes[scheme_id];
पूर्ण

/* keygen_bind_port_to_schemes
 *
 * Bind the port to schemes
 *
 * keygen: KeyGen handle
 * scheme_id: id of the scheme to bind to
 * bind: true to bind the port or false to unbind it
 *
 * Return: Zero क्रम success or error code in हाल of failure
 */
अटल पूर्णांक keygen_bind_port_to_schemes(काष्ठा fman_keygen *keygen,
				       u8 scheme_id,
					bool bind)
अणु
	काष्ठा fman_kg_regs __iomem *keygen_regs = keygen->keygen_regs;
	काष्ठा keygen_scheme *scheme;
	u32 ar_reg;
	u32 schemes_vector = 0;
	पूर्णांक err;

	scheme = get_scheme(keygen, scheme_id);
	अगर (!scheme) अणु
		pr_err("Requested Scheme does not exist\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!scheme->used) अणु
		pr_err("Cannot bind port to an invalid scheme\n");
		वापस -EINVAL;
	पूर्ण

	schemes_vector |= 1 << (31 - scheme_id);

	ar_reg = build_ar_bind_scheme(scheme->hw_port_id, false);
	err = keygen_ग_लिखो_ar_रुको(keygen_regs, ar_reg);
	अगर (err != 0) अणु
		pr_err("Reading Action Register failed\n");
		वापस err;
	पूर्ण

	keygen_ग_लिखो_sp(keygen_regs, schemes_vector, bind);

	ar_reg = build_ar_bind_scheme(scheme->hw_port_id, true);
	err = keygen_ग_लिखो_ar_रुको(keygen_regs, ar_reg);
	अगर (err != 0) अणु
		pr_err("Writing Action Register failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* keygen_scheme_setup
 *
 * Setup the scheme according to required configuration
 *
 * keygen: KeyGen handle
 * scheme_id: scheme ID
 * enable: true to enable scheme or false to disable it
 *
 * Return: Zero क्रम success or error code in हाल of failure
 */
अटल पूर्णांक keygen_scheme_setup(काष्ठा fman_keygen *keygen, u8 scheme_id,
			       bool enable)
अणु
	काष्ठा fman_kg_regs __iomem *keygen_regs = keygen->keygen_regs;
	काष्ठा fman_kg_scheme_regs scheme_regs;
	काष्ठा keygen_scheme *scheme;
	u32 पंचांगp_reg;
	पूर्णांक err;

	scheme = get_scheme(keygen, scheme_id);
	अगर (!scheme) अणु
		pr_err("Requested Scheme does not exist\n");
		वापस -EINVAL;
	पूर्ण
	अगर (enable && scheme->used) अणु
		pr_err("The requested Scheme is already used\n");
		वापस -EINVAL;
	पूर्ण

	/* Clear scheme रेजिस्टरs */
	स_रखो(&scheme_regs, 0, माप(काष्ठा fman_kg_scheme_regs));

	/* Setup all scheme रेजिस्टरs: */
	पंचांगp_reg = 0;

	अगर (enable) अणु
		/* Enable Scheme */
		पंचांगp_reg |= KG_SCH_MODE_EN;
		/* Enqueue frame NIA */
		पंचांगp_reg |= ENQUEUE_KG_DFLT_NIA;
	पूर्ण

	scheme_regs.kgse_mode = पंचांगp_reg;

	scheme_regs.kgse_mv = scheme->match_vector;

	/* Scheme करोn't override StorageProfile:
	 * valid only क्रम DPAA_VERSION >= 11
	 */
	scheme_regs.kgse_vsp = KG_SCH_VSP_NO_KSP_EN;

	/* Configure Hard-Coded Rx Hashing: */

	अगर (scheme->use_hashing) अणु
		/* configure kgse_ekfc */
		scheme_regs.kgse_ekfc = DEFAULT_HASH_KEY_EXTRACT_FIELDS;

		/* configure kgse_ekdv */
		पंचांगp_reg = 0;
		पंचांगp_reg |= (KG_SCH_DEF_USE_KGSE_DV_0 <<
				KG_SCH_DEF_IP_ADDR_SHIFT);
		पंचांगp_reg |= (KG_SCH_DEF_USE_KGSE_DV_1 <<
				KG_SCH_DEF_L4_PORT_SHIFT);
		scheme_regs.kgse_ekdv = पंचांगp_reg;

		/* configure kgse_dv0 */
		scheme_regs.kgse_dv0 = DEFAULT_HASH_KEY_IPv4_ADDR;
		/* configure kgse_dv1 */
		scheme_regs.kgse_dv1 = DEFAULT_HASH_KEY_L4_PORT;

		/* configure kgse_hc  */
		पंचांगp_reg = 0;
		पंचांगp_reg |= ((scheme->hash_fqid_count - 1) <<
				DEFAULT_HASH_DIST_FQID_SHIFT);
		पंचांगp_reg |= scheme->hashShअगरt << KG_SCH_HASH_CONFIG_SHIFT_SHIFT;

		अगर (scheme->symmetric_hash) अणु
			/* Normally extraction key should be verअगरied अगर
			 * complies with symmetric hash
			 * But because extraction is hard-coded, we are sure
			 * the key is symmetric
			 */
			पंचांगp_reg |= KG_SCH_HASH_CONFIG_SYM;
		पूर्ण
		scheme_regs.kgse_hc = पंचांगp_reg;
	पूर्ण अन्यथा अणु
		scheme_regs.kgse_ekfc = 0;
		scheme_regs.kgse_hc = 0;
		scheme_regs.kgse_ekdv = 0;
		scheme_regs.kgse_dv0 = 0;
		scheme_regs.kgse_dv1 = 0;
	पूर्ण

	/* configure kgse_fqb: Scheme FQID base */
	पंचांगp_reg = 0;
	पंचांगp_reg |= scheme->base_fqid;
	scheme_regs.kgse_fqb = पंचांगp_reg;

	/* features not used by hard-coded configuration */
	scheme_regs.kgse_bmch = 0;
	scheme_regs.kgse_bmcl = 0;
	scheme_regs.kgse_spc = 0;

	/* Write scheme रेजिस्टरs */
	err = keygen_ग_लिखो_scheme(keygen_regs, scheme_id, &scheme_regs, true);
	अगर (err != 0) अणु
		pr_err("Writing scheme registers failed\n");
		वापस err;
	पूर्ण

	/* Update used field क्रम Scheme */
	scheme->used = enable;

	वापस 0;
पूर्ण

/* keygen_init
 *
 * KeyGen initialization:
 * Initializes and enables KeyGen, allocate driver memory, setup रेजिस्टरs,
 * clear port bindings, invalidate all schemes
 *
 * keygen_regs: KeyGen रेजिस्टरs base address
 *
 * Return: Handle to KeyGen driver
 */
काष्ठा fman_keygen *keygen_init(काष्ठा fman_kg_regs __iomem *keygen_regs)
अणु
	काष्ठा fman_keygen *keygen;
	u32 ar;
	पूर्णांक i;

	/* Allocate memory क्रम KeyGen driver */
	keygen = kzalloc(माप(*keygen), GFP_KERNEL);
	अगर (!keygen)
		वापस शून्य;

	keygen->keygen_regs = keygen_regs;

	/* KeyGen initialization (क्रम Master partition):
	 * Setup KeyGen रेजिस्टरs
	 */
	ioग_लिखो32be(ENQUEUE_KG_DFLT_NIA, &keygen_regs->fmkg_gcr);

	ioग_लिखो32be(FM_EX_KG_DOUBLE_ECC | FM_EX_KG_KEYSIZE_OVERFLOW,
		    &keygen_regs->fmkg_eer);

	ioग_लिखो32be(0, &keygen_regs->fmkg_fकरोr);
	ioग_लिखो32be(0, &keygen_regs->fmkg_gdv0r);
	ioग_लिखो32be(0, &keygen_regs->fmkg_gdv1r);

	/* Clear binding between ports to schemes and classअगरication plans
	 * so that all ports are not bound to any scheme/classअगरication plan
	 */
	क्रम (i = 0; i < FMAN_MAX_NUM_OF_HW_PORTS; i++) अणु
		/* Clear all pe sp schemes रेजिस्टरs */
		keygen_ग_लिखो_sp(keygen_regs, 0xffffffff, false);
		ar = build_ar_bind_scheme(i, true);
		keygen_ग_लिखो_ar_रुको(keygen_regs, ar);

		/* Clear all pe cpp classअगरication plans रेजिस्टरs */
		keygen_ग_लिखो_cpp(keygen_regs, 0);
		ar = build_ar_bind_cls_plan(i, true);
		keygen_ग_लिखो_ar_रुको(keygen_regs, ar);
	पूर्ण

	/* Enable all scheme पूर्णांकerrupts */
	ioग_लिखो32be(0xFFFFFFFF, &keygen_regs->fmkg_seer);
	ioग_लिखो32be(0xFFFFFFFF, &keygen_regs->fmkg_seeer);

	/* Enable KyeGen */
	ioग_लिखो32be(ioपढ़ो32be(&keygen_regs->fmkg_gcr) | FM_KG_KGGCR_EN,
		    &keygen_regs->fmkg_gcr);

	वापस keygen;
पूर्ण
EXPORT_SYMBOL(keygen_init);

/* keygen_port_hashing_init
 *
 * Initializes a port क्रम Rx Hashing with specअगरied configuration parameters
 *
 * keygen: KeyGen handle
 * hw_port_id: HW Port ID
 * hash_base_fqid: Hashing Base FQID used क्रम spपढ़ोing
 * hash_size: Hashing size
 *
 * Return: Zero क्रम success or error code in हाल of failure
 */
पूर्णांक keygen_port_hashing_init(काष्ठा fman_keygen *keygen, u8 hw_port_id,
			     u32 hash_base_fqid, u32 hash_size)
अणु
	काष्ठा keygen_scheme *scheme;
	u8 scheme_id;
	पूर्णांक err;

	/* Validate Scheme configuration parameters */
	अगर (hash_base_fqid == 0 || (hash_base_fqid & ~0x00FFFFFF)) अणु
		pr_err("Base FQID must be between 1 and 2^24-1\न");
		वापस -EINVAL;
	पूर्ण
	अगर (hash_size == 0 || (hash_size & (hash_size - 1)) != 0) अणु
		pr_err("Hash size must be power of two\n");
		वापस -EINVAL;
	पूर्ण

	/* Find a मुक्त scheme */
	err = get_मुक्त_scheme_id(keygen, &scheme_id);
	अगर (err) अणु
		pr_err("The maximum number of available Schemes has been exceeded\n");
		वापस -EINVAL;
	पूर्ण

	/* Create and configure Hard-Coded Scheme: */

	scheme = get_scheme(keygen, scheme_id);
	अगर (!scheme) अणु
		pr_err("Requested Scheme does not exist\n");
		वापस -EINVAL;
	पूर्ण
	अगर (scheme->used) अणु
		pr_err("The requested Scheme is already used\n");
		वापस -EINVAL;
	पूर्ण

	/* Clear all scheme fields because the scheme may have been
	 * previously used
	 */
	स_रखो(scheme, 0, माप(काष्ठा keygen_scheme));

	/* Setup scheme: */
	scheme->hw_port_id = hw_port_id;
	scheme->use_hashing = true;
	scheme->base_fqid = hash_base_fqid;
	scheme->hash_fqid_count = hash_size;
	scheme->symmetric_hash = DEFAULT_SYMMETRIC_HASH;
	scheme->hashShअगरt = DEFAULT_HASH_SHIFT;

	/* All Schemes in hard-coded configuration
	 * are Indirect Schemes
	 */
	scheme->match_vector = 0;

	err = keygen_scheme_setup(keygen, scheme_id, true);
	अगर (err != 0) अणु
		pr_err("Scheme setup failed\n");
		वापस err;
	पूर्ण

	/* Bind Rx port to Scheme */
	err = keygen_bind_port_to_schemes(keygen, scheme_id, true);
	अगर (err != 0) अणु
		pr_err("Binding port to schemes failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(keygen_port_hashing_init);
