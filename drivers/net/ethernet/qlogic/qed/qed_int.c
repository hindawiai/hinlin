<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "qed.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_init_ops.h"
#समावेश "qed_int.h"
#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sp.h"
#समावेश "qed_sriov.h"
#समावेश "qed_vf.h"

काष्ठा qed_pi_info अणु
	qed_पूर्णांक_comp_cb_t	comp_cb;
	व्योम			*cookie;
पूर्ण;

काष्ठा qed_sb_sp_info अणु
	काष्ठा qed_sb_info sb_info;

	/* per protocol index data */
	काष्ठा qed_pi_info pi_info_arr[PIS_PER_SB_E4];
पूर्ण;

क्रमागत qed_attention_type अणु
	QED_ATTN_TYPE_ATTN,
	QED_ATTN_TYPE_PARITY,
पूर्ण;

#घोषणा SB_ATTN_ALIGNED_SIZE(p_hwfn) \
	ALIGNED_TYPE_SIZE(काष्ठा atten_status_block, p_hwfn)

काष्ठा aeu_invert_reg_bit अणु
	अक्षर bit_name[30];

#घोषणा ATTENTION_PARITY                (1 << 0)

#घोषणा ATTENTION_LENGTH_MASK           (0x00000ff0)
#घोषणा ATTENTION_LENGTH_SHIFT          (4)
#घोषणा ATTENTION_LENGTH(flags)         (((flags) & ATTENTION_LENGTH_MASK) >> \
					 ATTENTION_LENGTH_SHIFT)
#घोषणा ATTENTION_SINGLE                BIT(ATTENTION_LENGTH_SHIFT)
#घोषणा ATTENTION_PAR                   (ATTENTION_SINGLE | ATTENTION_PARITY)
#घोषणा ATTENTION_PAR_INT               ((2 << ATTENTION_LENGTH_SHIFT) | \
					 ATTENTION_PARITY)

/* Multiple bits start with this offset */
#घोषणा ATTENTION_OFFSET_MASK           (0x000ff000)
#घोषणा ATTENTION_OFFSET_SHIFT          (12)

#घोषणा ATTENTION_BB_MASK               (0x00700000)
#घोषणा ATTENTION_BB_SHIFT              (20)
#घोषणा ATTENTION_BB(value)             (value << ATTENTION_BB_SHIFT)
#घोषणा ATTENTION_BB_DIFFERENT          BIT(23)

#घोषणा ATTENTION_CLEAR_ENABLE          BIT(28)
	अचिन्हित पूर्णांक flags;

	/* Callback to call अगर attention will be triggered */
	पूर्णांक (*cb)(काष्ठा qed_hwfn *p_hwfn);

	क्रमागत block_id block_index;
पूर्ण;

काष्ठा aeu_invert_reg अणु
	काष्ठा aeu_invert_reg_bit bits[32];
पूर्ण;

#घोषणा MAX_ATTN_GRPS           (8)
#घोषणा NUM_ATTN_REGS           (9)

/* Specअगरic HW attention callbacks */
अटल पूर्णांक qed_mcp_attn_cb(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 पंचांगp = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt, MCP_REG_CPU_STATE);

	/* This might occur on certain instances; Log it once then mask it */
	DP_INFO(p_hwfn->cdev, "MCP_REG_CPU_STATE: %08x - Masking...\n",
		पंचांगp);
	qed_wr(p_hwfn, p_hwfn->p_dpc_ptt, MCP_REG_CPU_EVENT_MASK,
	       0xffffffff);

	वापस 0;
पूर्ण

#घोषणा QED_PSWHST_ATTENTION_INCORRECT_ACCESS		(0x1)
#घोषणा ATTENTION_INCORRECT_ACCESS_WR_MASK		(0x1)
#घोषणा ATTENTION_INCORRECT_ACCESS_WR_SHIFT		(0)
#घोषणा ATTENTION_INCORRECT_ACCESS_CLIENT_MASK		(0xf)
#घोषणा ATTENTION_INCORRECT_ACCESS_CLIENT_SHIFT		(1)
#घोषणा ATTENTION_INCORRECT_ACCESS_VF_VALID_MASK	(0x1)
#घोषणा ATTENTION_INCORRECT_ACCESS_VF_VALID_SHIFT	(5)
#घोषणा ATTENTION_INCORRECT_ACCESS_VF_ID_MASK		(0xff)
#घोषणा ATTENTION_INCORRECT_ACCESS_VF_ID_SHIFT		(6)
#घोषणा ATTENTION_INCORRECT_ACCESS_PF_ID_MASK		(0xf)
#घोषणा ATTENTION_INCORRECT_ACCESS_PF_ID_SHIFT		(14)
#घोषणा ATTENTION_INCORRECT_ACCESS_BYTE_EN_MASK		(0xff)
#घोषणा ATTENTION_INCORRECT_ACCESS_BYTE_EN_SHIFT	(18)
अटल पूर्णांक qed_pswhst_attn_cb(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 पंचांगp = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
			 PSWHST_REG_INCORRECT_ACCESS_VALID);

	अगर (पंचांगp & QED_PSWHST_ATTENTION_INCORRECT_ACCESS) अणु
		u32 addr, data, length;

		addr = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
			      PSWHST_REG_INCORRECT_ACCESS_ADDRESS);
		data = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
			      PSWHST_REG_INCORRECT_ACCESS_DATA);
		length = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
				PSWHST_REG_INCORRECT_ACCESS_LENGTH);

		DP_INFO(p_hwfn->cdev,
			"Incorrect access to %08x of length %08x - PF [%02x] VF [%04x] [valid %02x] client [%02x] write [%02x] Byte-Enable [%04x] [%08x]\n",
			addr, length,
			(u8) GET_FIELD(data, ATTENTION_INCORRECT_ACCESS_PF_ID),
			(u8) GET_FIELD(data, ATTENTION_INCORRECT_ACCESS_VF_ID),
			(u8) GET_FIELD(data,
				       ATTENTION_INCORRECT_ACCESS_VF_VALID),
			(u8) GET_FIELD(data,
				       ATTENTION_INCORRECT_ACCESS_CLIENT),
			(u8) GET_FIELD(data, ATTENTION_INCORRECT_ACCESS_WR),
			(u8) GET_FIELD(data,
				       ATTENTION_INCORRECT_ACCESS_BYTE_EN),
			data);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा QED_GRC_ATTENTION_VALID_BIT	(1 << 0)
#घोषणा QED_GRC_ATTENTION_ADDRESS_MASK	(0x7fffff)
#घोषणा QED_GRC_ATTENTION_ADDRESS_SHIFT	(0)
#घोषणा QED_GRC_ATTENTION_RDWR_BIT	(1 << 23)
#घोषणा QED_GRC_ATTENTION_MASTER_MASK	(0xf)
#घोषणा QED_GRC_ATTENTION_MASTER_SHIFT	(24)
#घोषणा QED_GRC_ATTENTION_PF_MASK	(0xf)
#घोषणा QED_GRC_ATTENTION_PF_SHIFT	(0)
#घोषणा QED_GRC_ATTENTION_VF_MASK	(0xff)
#घोषणा QED_GRC_ATTENTION_VF_SHIFT	(4)
#घोषणा QED_GRC_ATTENTION_PRIV_MASK	(0x3)
#घोषणा QED_GRC_ATTENTION_PRIV_SHIFT	(14)
#घोषणा QED_GRC_ATTENTION_PRIV_VF	(0)
अटल स्थिर अक्षर *attn_master_to_str(u8 master)
अणु
	चयन (master) अणु
	हाल 1: वापस "PXP";
	हाल 2: वापस "MCP";
	हाल 3: वापस "MSDM";
	हाल 4: वापस "PSDM";
	हाल 5: वापस "YSDM";
	हाल 6: वापस "USDM";
	हाल 7: वापस "TSDM";
	हाल 8: वापस "XSDM";
	हाल 9: वापस "DBU";
	हाल 10: वापस "DMAE";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक qed_grc_attn_cb(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 पंचांगp, पंचांगp2;

	/* We've alपढ़ोy cleared the समयout पूर्णांकerrupt रेजिस्टर, so we learn
	 * of पूर्णांकerrupts via the validity रेजिस्टर
	 */
	पंचांगp = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
		     GRC_REG_TIMEOUT_ATTN_ACCESS_VALID);
	अगर (!(पंचांगp & QED_GRC_ATTENTION_VALID_BIT))
		जाओ out;

	/* Read the GRC समयout inक्रमmation */
	पंचांगp = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
		     GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_0);
	पंचांगp2 = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
		      GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_1);

	DP_INFO(p_hwfn->cdev,
		"GRC timeout [%08x:%08x] - %s Address [%08x] [Master %s] [PF: %02x %s %02x]\n",
		पंचांगp2, पंचांगp,
		(पंचांगp & QED_GRC_ATTENTION_RDWR_BIT) ? "Write to" : "Read from",
		GET_FIELD(पंचांगp, QED_GRC_ATTENTION_ADDRESS) << 2,
		attn_master_to_str(GET_FIELD(पंचांगp, QED_GRC_ATTENTION_MASTER)),
		GET_FIELD(पंचांगp2, QED_GRC_ATTENTION_PF),
		(GET_FIELD(पंचांगp2, QED_GRC_ATTENTION_PRIV) ==
		 QED_GRC_ATTENTION_PRIV_VF) ? "VF" : "(Irrelevant)",
		GET_FIELD(पंचांगp2, QED_GRC_ATTENTION_VF));

out:
	/* Regardles of anything अन्यथा, clean the validity bit */
	qed_wr(p_hwfn, p_hwfn->p_dpc_ptt,
	       GRC_REG_TIMEOUT_ATTN_ACCESS_VALID, 0);
	वापस 0;
पूर्ण

#घोषणा PGLUE_ATTENTION_VALID			(1 << 29)
#घोषणा PGLUE_ATTENTION_RD_VALID		(1 << 26)
#घोषणा PGLUE_ATTENTION_DETAILS_PFID_MASK	(0xf)
#घोषणा PGLUE_ATTENTION_DETAILS_PFID_SHIFT	(20)
#घोषणा PGLUE_ATTENTION_DETAILS_VF_VALID_MASK	(0x1)
#घोषणा PGLUE_ATTENTION_DETAILS_VF_VALID_SHIFT	(19)
#घोषणा PGLUE_ATTENTION_DETAILS_VFID_MASK	(0xff)
#घोषणा PGLUE_ATTENTION_DETAILS_VFID_SHIFT	(24)
#घोषणा PGLUE_ATTENTION_DETAILS2_WAS_ERR_MASK	(0x1)
#घोषणा PGLUE_ATTENTION_DETAILS2_WAS_ERR_SHIFT	(21)
#घोषणा PGLUE_ATTENTION_DETAILS2_BME_MASK	(0x1)
#घोषणा PGLUE_ATTENTION_DETAILS2_BME_SHIFT	(22)
#घोषणा PGLUE_ATTENTION_DETAILS2_FID_EN_MASK	(0x1)
#घोषणा PGLUE_ATTENTION_DETAILS2_FID_EN_SHIFT	(23)
#घोषणा PGLUE_ATTENTION_ICPL_VALID		(1 << 23)
#घोषणा PGLUE_ATTENTION_ZLR_VALID		(1 << 25)
#घोषणा PGLUE_ATTENTION_ILT_VALID		(1 << 23)

पूर्णांक qed_pglueb_rbc_attn_handler(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
				bool hw_init)
अणु
	अक्षर msg[256];
	u32 पंचांगp;

	पंचांगp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_TX_ERR_WR_DETAILS2);
	अगर (पंचांगp & PGLUE_ATTENTION_VALID) अणु
		u32 addr_lo, addr_hi, details;

		addr_lo = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_WR_ADD_31_0);
		addr_hi = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_WR_ADD_63_32);
		details = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_WR_DETAILS);

		snम_लिखो(msg, माप(msg),
			 "Illegal write by chip to [%08x:%08x] blocked.\n"
			 "Details: %08x [PFID %02x, VFID %02x, VF_VALID %02x]\n"
			 "Details2 %08x [Was_error %02x BME deassert %02x FID_enable deassert %02x]",
			 addr_hi, addr_lo, details,
			 (u8)GET_FIELD(details, PGLUE_ATTENTION_DETAILS_PFID),
			 (u8)GET_FIELD(details, PGLUE_ATTENTION_DETAILS_VFID),
			 !!GET_FIELD(details, PGLUE_ATTENTION_DETAILS_VF_VALID),
			 पंचांगp,
			 !!GET_FIELD(पंचांगp, PGLUE_ATTENTION_DETAILS2_WAS_ERR),
			 !!GET_FIELD(पंचांगp, PGLUE_ATTENTION_DETAILS2_BME),
			 !!GET_FIELD(पंचांगp, PGLUE_ATTENTION_DETAILS2_FID_EN));

		अगर (hw_init)
			DP_VERBOSE(p_hwfn, NETIF_MSG_INTR, "%s\n", msg);
		अन्यथा
			DP_NOTICE(p_hwfn, "%s\n", msg);
	पूर्ण

	पंचांगp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_TX_ERR_RD_DETAILS2);
	अगर (पंचांगp & PGLUE_ATTENTION_RD_VALID) अणु
		u32 addr_lo, addr_hi, details;

		addr_lo = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_RD_ADD_31_0);
		addr_hi = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_RD_ADD_63_32);
		details = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_RD_DETAILS);

		DP_NOTICE(p_hwfn,
			  "Illegal read by chip from [%08x:%08x] blocked.\n"
			  "Details: %08x [PFID %02x, VFID %02x, VF_VALID %02x]\n"
			  "Details2 %08x [Was_error %02x BME deassert %02x FID_enable deassert %02x]\n",
			  addr_hi, addr_lo, details,
			  (u8)GET_FIELD(details, PGLUE_ATTENTION_DETAILS_PFID),
			  (u8)GET_FIELD(details, PGLUE_ATTENTION_DETAILS_VFID),
			  GET_FIELD(details,
				    PGLUE_ATTENTION_DETAILS_VF_VALID) ? 1 : 0,
			  पंचांगp,
			  GET_FIELD(पंचांगp,
				    PGLUE_ATTENTION_DETAILS2_WAS_ERR) ? 1 : 0,
			  GET_FIELD(पंचांगp,
				    PGLUE_ATTENTION_DETAILS2_BME) ? 1 : 0,
			  GET_FIELD(पंचांगp,
				    PGLUE_ATTENTION_DETAILS2_FID_EN) ? 1 : 0);
	पूर्ण

	पंचांगp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_TX_ERR_WR_DETAILS_ICPL);
	अगर (पंचांगp & PGLUE_ATTENTION_ICPL_VALID) अणु
		snम_लिखो(msg, माप(msg), "ICPL error - %08x", पंचांगp);

		अगर (hw_init)
			DP_VERBOSE(p_hwfn, NETIF_MSG_INTR, "%s\n", msg);
		अन्यथा
			DP_NOTICE(p_hwfn, "%s\n", msg);
	पूर्ण

	पंचांगp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_MASTER_ZLR_ERR_DETAILS);
	अगर (पंचांगp & PGLUE_ATTENTION_ZLR_VALID) अणु
		u32 addr_hi, addr_lo;

		addr_lo = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_MASTER_ZLR_ERR_ADD_31_0);
		addr_hi = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_MASTER_ZLR_ERR_ADD_63_32);

		DP_NOTICE(p_hwfn, "ZLR error - %08x [Address %08x:%08x]\n",
			  पंचांगp, addr_hi, addr_lo);
	पूर्ण

	पंचांगp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_VF_ILT_ERR_DETAILS2);
	अगर (पंचांगp & PGLUE_ATTENTION_ILT_VALID) अणु
		u32 addr_hi, addr_lo, details;

		addr_lo = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_VF_ILT_ERR_ADD_31_0);
		addr_hi = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_VF_ILT_ERR_ADD_63_32);
		details = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_VF_ILT_ERR_DETAILS);

		DP_NOTICE(p_hwfn,
			  "ILT error - Details %08x Details2 %08x [Address %08x:%08x]\n",
			  details, पंचांगp, addr_hi, addr_lo);
	पूर्ण

	/* Clear the indications */
	qed_wr(p_hwfn, p_ptt, PGLUE_B_REG_LATCHED_ERRORS_CLR, BIT(2));

	वापस 0;
पूर्ण

अटल पूर्णांक qed_pglueb_rbc_attn_cb(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस qed_pglueb_rbc_attn_handler(p_hwfn, p_hwfn->p_dpc_ptt, false);
पूर्ण

अटल पूर्णांक qed_fw_निश्चितion(काष्ठा qed_hwfn *p_hwfn)
अणु
	qed_hw_err_notअगरy(p_hwfn, p_hwfn->p_dpc_ptt, QED_HW_ERR_FW_ASSERT,
			  "FW assertion!\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qed_general_attention_35(काष्ठा qed_hwfn *p_hwfn)
अणु
	DP_INFO(p_hwfn, "General attention 35!\n");

	वापस 0;
पूर्ण

#घोषणा QED_DORQ_ATTENTION_REASON_MASK  (0xfffff)
#घोषणा QED_DORQ_ATTENTION_OPAQUE_MASK  (0xffff)
#घोषणा QED_DORQ_ATTENTION_OPAQUE_SHIFT (0x0)
#घोषणा QED_DORQ_ATTENTION_SIZE_MASK            (0x7f)
#घोषणा QED_DORQ_ATTENTION_SIZE_SHIFT           (16)

#घोषणा QED_DB_REC_COUNT                        1000
#घोषणा QED_DB_REC_INTERVAL                     100

अटल पूर्णांक qed_db_rec_flush_queue(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt)
अणु
	u32 count = QED_DB_REC_COUNT;
	u32 usage = 1;

	/* Flush any pending (e)dpms as they may never arrive */
	qed_wr(p_hwfn, p_ptt, DORQ_REG_DPM_FORCE_ABORT, 0x1);

	/* रुको क्रम usage to zero or count to run out. This is necessary since
	 * EDPM करोorbell transactions can take multiple 64b cycles, and as such
	 * can "split" over the pci. Possibly, the करोorbell drop can happen with
	 * half an EDPM in the queue and other half dropped. Another EDPM
	 * करोorbell to the same address (from करोorbell recovery mechanism or
	 * from the करोorbelling entity) could have first half dropped and second
	 * half पूर्णांकerpreted as continuation of the first. To prevent such
	 * malक्रमmed करोorbells from reaching the device, flush the queue beक्रमe
	 * releasing the overflow sticky indication.
	 */
	जबतक (count-- && usage) अणु
		usage = qed_rd(p_hwfn, p_ptt, DORQ_REG_PF_USAGE_CNT);
		udelay(QED_DB_REC_INTERVAL);
	पूर्ण

	/* should have been depleted by now */
	अगर (usage) अणु
		DP_NOTICE(p_hwfn->cdev,
			  "DB recovery: doorbell usage failed to zero after %d usec. usage was %x\n",
			  QED_DB_REC_INTERVAL * QED_DB_REC_COUNT, usage);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qed_db_rec_handler(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	u32 attn_ovfl, cur_ovfl;
	पूर्णांक rc;

	attn_ovfl = test_and_clear_bit(QED_OVERFLOW_BIT,
				       &p_hwfn->db_recovery_info.overflow);
	cur_ovfl = qed_rd(p_hwfn, p_ptt, DORQ_REG_PF_OVFL_STICKY);
	अगर (!cur_ovfl && !attn_ovfl)
		वापस 0;

	DP_NOTICE(p_hwfn, "PF Overflow sticky: attn %u current %u\n",
		  attn_ovfl, cur_ovfl);

	अगर (cur_ovfl && !p_hwfn->db_bar_no_edpm) अणु
		rc = qed_db_rec_flush_queue(p_hwfn, p_ptt);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* Release overflow sticky indication (stop silently dropping everything) */
	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_OVFL_STICKY, 0x0);

	/* Repeat all last करोorbells (करोorbell drop recovery) */
	qed_db_recovery_execute(p_hwfn);

	वापस 0;
पूर्ण

अटल व्योम qed_करोrq_attn_overflow(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_ptt *p_ptt = p_hwfn->p_dpc_ptt;
	u32 overflow;
	पूर्णांक rc;

	overflow = qed_rd(p_hwfn, p_ptt, DORQ_REG_PF_OVFL_STICKY);
	अगर (!overflow)
		जाओ out;

	/* Run PF करोorbell recovery in next periodic handler */
	set_bit(QED_OVERFLOW_BIT, &p_hwfn->db_recovery_info.overflow);

	अगर (!p_hwfn->db_bar_no_edpm) अणु
		rc = qed_db_rec_flush_queue(p_hwfn, p_ptt);
		अगर (rc)
			जाओ out;
	पूर्ण

	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_OVFL_STICKY, 0x0);
out:
	/* Schedule the handler even अगर overflow was not detected */
	qed_periodic_db_rec_start(p_hwfn);
पूर्ण

अटल पूर्णांक qed_करोrq_attn_पूर्णांक_sts(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 पूर्णांक_sts, first_drop_reason, details, address, all_drops_reason;
	काष्ठा qed_ptt *p_ptt = p_hwfn->p_dpc_ptt;

	/* पूर्णांक_sts may be zero since all PFs were पूर्णांकerrupted क्रम करोorbell
	 * overflow but another one alपढ़ोy handled it. Can पात here. If
	 * This PF also requires overflow recovery we will be पूर्णांकerrupted again.
	 * The masked almost full indication may also be set. Ignoring.
	 */
	पूर्णांक_sts = qed_rd(p_hwfn, p_ptt, DORQ_REG_INT_STS);
	अगर (!(पूर्णांक_sts & ~DORQ_REG_INT_STS_DORQ_FIFO_AFULL))
		वापस 0;

	DP_NOTICE(p_hwfn->cdev, "DORQ attention. int_sts was %x\n", पूर्णांक_sts);

	/* check अगर db_drop or overflow happened */
	अगर (पूर्णांक_sts & (DORQ_REG_INT_STS_DB_DROP |
		       DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR)) अणु
		/* Obtain data about db drop/overflow */
		first_drop_reason = qed_rd(p_hwfn, p_ptt,
					   DORQ_REG_DB_DROP_REASON) &
		    QED_DORQ_ATTENTION_REASON_MASK;
		details = qed_rd(p_hwfn, p_ptt, DORQ_REG_DB_DROP_DETAILS);
		address = qed_rd(p_hwfn, p_ptt,
				 DORQ_REG_DB_DROP_DETAILS_ADDRESS);
		all_drops_reason = qed_rd(p_hwfn, p_ptt,
					  DORQ_REG_DB_DROP_DETAILS_REASON);

		/* Log info */
		DP_NOTICE(p_hwfn->cdev,
			  "Doorbell drop occurred\n"
			  "Address\t\t0x%08x\t(second BAR address)\n"
			  "FID\t\t0x%04x\t\t(Opaque FID)\n"
			  "Size\t\t0x%04x\t\t(in bytes)\n"
			  "1st drop reason\t0x%08x\t(details on first drop since last handling)\n"
			  "Sticky reasons\t0x%08x\t(all drop reasons since last handling)\n",
			  address,
			  GET_FIELD(details, QED_DORQ_ATTENTION_OPAQUE),
			  GET_FIELD(details, QED_DORQ_ATTENTION_SIZE) * 4,
			  first_drop_reason, all_drops_reason);

		/* Clear the करोorbell drop details and prepare क्रम next drop */
		qed_wr(p_hwfn, p_ptt, DORQ_REG_DB_DROP_DETAILS_REL, 0);

		/* Mark पूर्णांकerrupt as handled (note: even अगर drop was due to a dअगरferent
		 * reason than overflow we mark as handled)
		 */
		qed_wr(p_hwfn,
		       p_ptt,
		       DORQ_REG_INT_STS_WR,
		       DORQ_REG_INT_STS_DB_DROP |
		       DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR);

		/* If there are no indications other than drop indications, success */
		अगर ((पूर्णांक_sts & ~(DORQ_REG_INT_STS_DB_DROP |
				 DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR |
				 DORQ_REG_INT_STS_DORQ_FIFO_AFULL)) == 0)
			वापस 0;
	पूर्ण

	/* Some other indication was present - non recoverable */
	DP_INFO(p_hwfn, "DORQ fatal attention\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक qed_करोrq_attn_cb(काष्ठा qed_hwfn *p_hwfn)
अणु
	p_hwfn->db_recovery_info.करोrq_attn = true;
	qed_करोrq_attn_overflow(p_hwfn);

	वापस qed_करोrq_attn_पूर्णांक_sts(p_hwfn);
पूर्ण

अटल व्योम qed_करोrq_attn_handler(काष्ठा qed_hwfn *p_hwfn)
अणु
	अगर (p_hwfn->db_recovery_info.करोrq_attn)
		जाओ out;

	/* Call DORQ callback अगर the attention was missed */
	qed_करोrq_attn_cb(p_hwfn);
out:
	p_hwfn->db_recovery_info.करोrq_attn = false;
पूर्ण

/* Instead of major changes to the data-काष्ठाure, we have a some 'special'
 * identअगरiers क्रम sources that changed meaning between adapters.
 */
क्रमागत aeu_invert_reg_special_type अणु
	AEU_INVERT_REG_SPECIAL_CNIG_0,
	AEU_INVERT_REG_SPECIAL_CNIG_1,
	AEU_INVERT_REG_SPECIAL_CNIG_2,
	AEU_INVERT_REG_SPECIAL_CNIG_3,
	AEU_INVERT_REG_SPECIAL_MAX,
पूर्ण;

अटल काष्ठा aeu_invert_reg_bit
aeu_descs_special[AEU_INVERT_REG_SPECIAL_MAX] = अणु
	अणु"CNIG port 0", ATTENTION_SINGLE, शून्य, BLOCK_CNIGपूर्ण,
	अणु"CNIG port 1", ATTENTION_SINGLE, शून्य, BLOCK_CNIGपूर्ण,
	अणु"CNIG port 2", ATTENTION_SINGLE, शून्य, BLOCK_CNIGपूर्ण,
	अणु"CNIG port 3", ATTENTION_SINGLE, शून्य, BLOCK_CNIGपूर्ण,
पूर्ण;

/* Notice aeu_invert_reg must be defined in the same order of bits as HW;  */
अटल काष्ठा aeu_invert_reg aeu_descs[NUM_ATTN_REGS] = अणु
	अणु
		अणु       /* After Invert 1 */
			अणु"GPIO0 function%d",
			 (32 << ATTENTION_LENGTH_SHIFT), शून्य, MAX_BLOCK_IDपूर्ण,
		पूर्ण
	पूर्ण,

	अणु
		अणु       /* After Invert 2 */
			अणु"PGLUE config_space", ATTENTION_SINGLE,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"PGLUE misc_flr", ATTENTION_SINGLE,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"PGLUE B RBC", ATTENTION_PAR_INT,
			 qed_pglueb_rbc_attn_cb, BLOCK_PGLUE_Bपूर्ण,
			अणु"PGLUE misc_mctp", ATTENTION_SINGLE,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"Flash event", ATTENTION_SINGLE, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"SMB event", ATTENTION_SINGLE,	शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"Main Power", ATTENTION_SINGLE, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"SW timers #%d", (8 << ATTENTION_LENGTH_SHIFT) |
					  (1 << ATTENTION_OFFSET_SHIFT),
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"PCIE glue/PXP VPD %d",
			 (16 << ATTENTION_LENGTH_SHIFT), शून्य, BLOCK_PGLCSपूर्ण,
		पूर्ण
	पूर्ण,

	अणु
		अणु       /* After Invert 3 */
			अणु"General Attention %d",
			 (32 << ATTENTION_LENGTH_SHIFT), शून्य, MAX_BLOCK_IDपूर्ण,
		पूर्ण
	पूर्ण,

	अणु
		अणु       /* After Invert 4 */
			अणु"General Attention 32", ATTENTION_SINGLE |
			 ATTENTION_CLEAR_ENABLE, qed_fw_निश्चितion,
			 MAX_BLOCK_IDपूर्ण,
			अणु"General Attention %d",
			 (2 << ATTENTION_LENGTH_SHIFT) |
			 (33 << ATTENTION_OFFSET_SHIFT), शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"General Attention 35", ATTENTION_SINGLE |
			 ATTENTION_CLEAR_ENABLE, qed_general_attention_35,
			 MAX_BLOCK_IDपूर्ण,
			अणु"NWS Parity",
			 ATTENTION_PAR | ATTENTION_BB_DIFFERENT |
			 ATTENTION_BB(AEU_INVERT_REG_SPECIAL_CNIG_0),
			 शून्य, BLOCK_NWSपूर्ण,
			अणु"NWS Interrupt",
			 ATTENTION_SINGLE | ATTENTION_BB_DIFFERENT |
			 ATTENTION_BB(AEU_INVERT_REG_SPECIAL_CNIG_1),
			 शून्य, BLOCK_NWSपूर्ण,
			अणु"NWM Parity",
			 ATTENTION_PAR | ATTENTION_BB_DIFFERENT |
			 ATTENTION_BB(AEU_INVERT_REG_SPECIAL_CNIG_2),
			 शून्य, BLOCK_NWMपूर्ण,
			अणु"NWM Interrupt",
			 ATTENTION_SINGLE | ATTENTION_BB_DIFFERENT |
			 ATTENTION_BB(AEU_INVERT_REG_SPECIAL_CNIG_3),
			 शून्य, BLOCK_NWMपूर्ण,
			अणु"MCP CPU", ATTENTION_SINGLE,
			 qed_mcp_attn_cb, MAX_BLOCK_IDपूर्ण,
			अणु"MCP Watchdog timer", ATTENTION_SINGLE,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"MCP M2P", ATTENTION_SINGLE, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"AVS stop status ready", ATTENTION_SINGLE,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"MSTAT", ATTENTION_PAR_INT, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"MSTAT per-path", ATTENTION_PAR_INT,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"Reserved %d", (6 << ATTENTION_LENGTH_SHIFT),
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"NIG", ATTENTION_PAR_INT, शून्य, BLOCK_NIGपूर्ण,
			अणु"BMB/OPTE/MCP", ATTENTION_PAR_INT, शून्य, BLOCK_BMBपूर्ण,
			अणु"BTB",	ATTENTION_PAR_INT, शून्य, BLOCK_BTBपूर्ण,
			अणु"BRB",	ATTENTION_PAR_INT, शून्य, BLOCK_BRBपूर्ण,
			अणु"PRS",	ATTENTION_PAR_INT, शून्य, BLOCK_PRSपूर्ण,
		पूर्ण
	पूर्ण,

	अणु
		अणु       /* After Invert 5 */
			अणु"SRC", ATTENTION_PAR_INT, शून्य, BLOCK_SRCपूर्ण,
			अणु"PB Client1", ATTENTION_PAR_INT, शून्य, BLOCK_PBF_PB1पूर्ण,
			अणु"PB Client2", ATTENTION_PAR_INT, शून्य, BLOCK_PBF_PB2पूर्ण,
			अणु"RPB", ATTENTION_PAR_INT, शून्य, BLOCK_RPBपूर्ण,
			अणु"PBF", ATTENTION_PAR_INT, शून्य, BLOCK_PBFपूर्ण,
			अणु"QM", ATTENTION_PAR_INT, शून्य, BLOCK_QMपूर्ण,
			अणु"TM", ATTENTION_PAR_INT, शून्य, BLOCK_TMपूर्ण,
			अणु"MCM",  ATTENTION_PAR_INT, शून्य, BLOCK_MCMपूर्ण,
			अणु"MSDM", ATTENTION_PAR_INT, शून्य, BLOCK_MSDMपूर्ण,
			अणु"MSEM", ATTENTION_PAR_INT, शून्य, BLOCK_MSEMपूर्ण,
			अणु"PCM", ATTENTION_PAR_INT, शून्य, BLOCK_PCMपूर्ण,
			अणु"PSDM", ATTENTION_PAR_INT, शून्य, BLOCK_PSDMपूर्ण,
			अणु"PSEM", ATTENTION_PAR_INT, शून्य, BLOCK_PSEMपूर्ण,
			अणु"TCM", ATTENTION_PAR_INT, शून्य, BLOCK_TCMपूर्ण,
			अणु"TSDM", ATTENTION_PAR_INT, शून्य, BLOCK_TSDMपूर्ण,
			अणु"TSEM", ATTENTION_PAR_INT, शून्य, BLOCK_TSEMपूर्ण,
		पूर्ण
	पूर्ण,

	अणु
		अणु       /* After Invert 6 */
			अणु"UCM", ATTENTION_PAR_INT, शून्य, BLOCK_UCMपूर्ण,
			अणु"USDM", ATTENTION_PAR_INT, शून्य, BLOCK_USDMपूर्ण,
			अणु"USEM", ATTENTION_PAR_INT, शून्य, BLOCK_USEMपूर्ण,
			अणु"XCM",	ATTENTION_PAR_INT, शून्य, BLOCK_XCMपूर्ण,
			अणु"XSDM", ATTENTION_PAR_INT, शून्य, BLOCK_XSDMपूर्ण,
			अणु"XSEM", ATTENTION_PAR_INT, शून्य, BLOCK_XSEMपूर्ण,
			अणु"YCM",	ATTENTION_PAR_INT, शून्य, BLOCK_YCMपूर्ण,
			अणु"YSDM", ATTENTION_PAR_INT, शून्य, BLOCK_YSDMपूर्ण,
			अणु"YSEM", ATTENTION_PAR_INT, शून्य, BLOCK_YSEMपूर्ण,
			अणु"XYLD", ATTENTION_PAR_INT, शून्य, BLOCK_XYLDपूर्ण,
			अणु"TMLD", ATTENTION_PAR_INT, शून्य, BLOCK_TMLDपूर्ण,
			अणु"MYLD", ATTENTION_PAR_INT, शून्य, BLOCK_MULDपूर्ण,
			अणु"YULD", ATTENTION_PAR_INT, शून्य, BLOCK_YULDपूर्ण,
			अणु"DORQ", ATTENTION_PAR_INT,
			 qed_करोrq_attn_cb, BLOCK_DORQपूर्ण,
			अणु"DBG", ATTENTION_PAR_INT, शून्य, BLOCK_DBGपूर्ण,
			अणु"IPC",	ATTENTION_PAR_INT, शून्य, BLOCK_IPCपूर्ण,
		पूर्ण
	पूर्ण,

	अणु
		अणु       /* After Invert 7 */
			अणु"CCFC", ATTENTION_PAR_INT, शून्य, BLOCK_CCFCपूर्ण,
			अणु"CDU", ATTENTION_PAR_INT, शून्य, BLOCK_CDUपूर्ण,
			अणु"DMAE", ATTENTION_PAR_INT, शून्य, BLOCK_DMAEपूर्ण,
			अणु"IGU", ATTENTION_PAR_INT, शून्य, BLOCK_IGUपूर्ण,
			अणु"ATC", ATTENTION_PAR_INT, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"CAU", ATTENTION_PAR_INT, शून्य, BLOCK_CAUपूर्ण,
			अणु"PTU", ATTENTION_PAR_INT, शून्य, BLOCK_PTUपूर्ण,
			अणु"PRM", ATTENTION_PAR_INT, शून्य, BLOCK_PRMपूर्ण,
			अणु"TCFC", ATTENTION_PAR_INT, शून्य, BLOCK_TCFCपूर्ण,
			अणु"RDIF", ATTENTION_PAR_INT, शून्य, BLOCK_RDIFपूर्ण,
			अणु"TDIF", ATTENTION_PAR_INT, शून्य, BLOCK_TDIFपूर्ण,
			अणु"RSS", ATTENTION_PAR_INT, शून्य, BLOCK_RSSपूर्ण,
			अणु"MISC", ATTENTION_PAR_INT, शून्य, BLOCK_MISCपूर्ण,
			अणु"MISCS", ATTENTION_PAR_INT, शून्य, BLOCK_MISCSपूर्ण,
			अणु"PCIE", ATTENTION_PAR, शून्य, BLOCK_PCIEपूर्ण,
			अणु"Vaux PCI core", ATTENTION_SINGLE, शून्य, BLOCK_PGLCSपूर्ण,
			अणु"PSWRQ", ATTENTION_PAR_INT, शून्य, BLOCK_PSWRQपूर्ण,
		पूर्ण
	पूर्ण,

	अणु
		अणु       /* After Invert 8 */
			अणु"PSWRQ (pci_clk)", ATTENTION_PAR_INT,
			 शून्य, BLOCK_PSWRQ2पूर्ण,
			अणु"PSWWR", ATTENTION_PAR_INT, शून्य, BLOCK_PSWWRपूर्ण,
			अणु"PSWWR (pci_clk)", ATTENTION_PAR_INT,
			 शून्य, BLOCK_PSWWR2पूर्ण,
			अणु"PSWRD", ATTENTION_PAR_INT, शून्य, BLOCK_PSWRDपूर्ण,
			अणु"PSWRD (pci_clk)", ATTENTION_PAR_INT,
			 शून्य, BLOCK_PSWRD2पूर्ण,
			अणु"PSWHST", ATTENTION_PAR_INT,
			 qed_pswhst_attn_cb, BLOCK_PSWHSTपूर्ण,
			अणु"PSWHST (pci_clk)", ATTENTION_PAR_INT,
			 शून्य, BLOCK_PSWHST2पूर्ण,
			अणु"GRC",	ATTENTION_PAR_INT,
			 qed_grc_attn_cb, BLOCK_GRCपूर्ण,
			अणु"CPMU", ATTENTION_PAR_INT, शून्य, BLOCK_CPMUपूर्ण,
			अणु"NCSI", ATTENTION_PAR_INT, शून्य, BLOCK_NCSIपूर्ण,
			अणु"MSEM PRAM", ATTENTION_PAR, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"PSEM PRAM", ATTENTION_PAR, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"TSEM PRAM", ATTENTION_PAR, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"USEM PRAM", ATTENTION_PAR, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"XSEM PRAM", ATTENTION_PAR, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"YSEM PRAM", ATTENTION_PAR, शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"pxp_misc_mps", ATTENTION_PAR, शून्य, BLOCK_PGLCSपूर्ण,
			अणु"PCIE glue/PXP Exp. ROM", ATTENTION_SINGLE,
			 शून्य, BLOCK_PGLCSपूर्ण,
			अणु"PERST_B assertion", ATTENTION_SINGLE,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"PERST_B deassertion", ATTENTION_SINGLE,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"Reserved %d", (2 << ATTENTION_LENGTH_SHIFT),
			 शून्य, MAX_BLOCK_IDपूर्ण,
		पूर्ण
	पूर्ण,

	अणु
		अणु       /* After Invert 9 */
			अणु"MCP Latched memory", ATTENTION_PAR,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"MCP Latched scratchpad cache", ATTENTION_SINGLE,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"MCP Latched ump_tx", ATTENTION_PAR,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"MCP Latched scratchpad", ATTENTION_PAR,
			 शून्य, MAX_BLOCK_IDपूर्ण,
			अणु"Reserved %d", (28 << ATTENTION_LENGTH_SHIFT),
			 शून्य, MAX_BLOCK_IDपूर्ण,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल काष्ठा aeu_invert_reg_bit *
qed_पूर्णांक_aeu_translate(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा aeu_invert_reg_bit *p_bit)
अणु
	अगर (!QED_IS_BB(p_hwfn->cdev))
		वापस p_bit;

	अगर (!(p_bit->flags & ATTENTION_BB_DIFFERENT))
		वापस p_bit;

	वापस &aeu_descs_special[(p_bit->flags & ATTENTION_BB_MASK) >>
				  ATTENTION_BB_SHIFT];
पूर्ण

अटल bool qed_पूर्णांक_is_parity_flag(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा aeu_invert_reg_bit *p_bit)
अणु
	वापस !!(qed_पूर्णांक_aeu_translate(p_hwfn, p_bit)->flags &
		   ATTENTION_PARITY);
पूर्ण

#घोषणा ATTN_STATE_BITS         (0xfff)
#घोषणा ATTN_BITS_MASKABLE      (0x3ff)
काष्ठा qed_sb_attn_info अणु
	/* Virtual & Physical address of the SB */
	काष्ठा atten_status_block       *sb_attn;
	dma_addr_t			sb_phys;

	/* Last seen running index */
	u16				index;

	/* A mask of the AEU bits resulting in a parity error */
	u32				parity_mask[NUM_ATTN_REGS];

	/* A poपूर्णांकer to the attention description काष्ठाure */
	काष्ठा aeu_invert_reg		*p_aeu_desc;

	/* Previously निश्चितed attentions, which are still unनिश्चितed */
	u16				known_attn;

	/* Cleanup address क्रम the link's general hw attention */
	u32				mfw_attn_addr;
पूर्ण;

अटल अंतरभूत u16 qed_attn_update_idx(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_sb_attn_info *p_sb_desc)
अणु
	u16 rc = 0, index;

	index = le16_to_cpu(p_sb_desc->sb_attn->sb_index);
	अगर (p_sb_desc->index != index) अणु
		p_sb_desc->index	= index;
		rc		      = QED_SB_ATT_IDX;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * qed_पूर्णांक_निश्चितion() - Handle निश्चितed attention bits.
 *
 * @p_hwfn: HW device data.
 * @निश्चितed_bits: Newly निश्चितed bits.
 *
 * Return: Zero value.
 */
अटल पूर्णांक qed_पूर्णांक_निश्चितion(काष्ठा qed_hwfn *p_hwfn, u16 निश्चितed_bits)
अणु
	काष्ठा qed_sb_attn_info *sb_attn_sw = p_hwfn->p_sb_attn;
	u32 igu_mask;

	/* Mask the source of the attention in the IGU */
	igu_mask = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt, IGU_REG_ATTENTION_ENABLE);
	DP_VERBOSE(p_hwfn, NETIF_MSG_INTR, "IGU mask: 0x%08x --> 0x%08x\n",
		   igu_mask, igu_mask & ~(निश्चितed_bits & ATTN_BITS_MASKABLE));
	igu_mask &= ~(निश्चितed_bits & ATTN_BITS_MASKABLE);
	qed_wr(p_hwfn, p_hwfn->p_dpc_ptt, IGU_REG_ATTENTION_ENABLE, igu_mask);

	DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
		   "inner known ATTN state: 0x%04x --> 0x%04x\n",
		   sb_attn_sw->known_attn,
		   sb_attn_sw->known_attn | निश्चितed_bits);
	sb_attn_sw->known_attn |= निश्चितed_bits;

	/* Handle MCP events */
	अगर (निश्चितed_bits & 0x100) अणु
		qed_mcp_handle_events(p_hwfn, p_hwfn->p_dpc_ptt);
		/* Clean the MCP attention */
		qed_wr(p_hwfn, p_hwfn->p_dpc_ptt,
		       sb_attn_sw->mfw_attn_addr, 0);
	पूर्ण

	सूचीECT_REG_WR((u8 __iomem *)p_hwfn->regview +
		      GTT_BAR0_MAP_REG_IGU_CMD +
		      ((IGU_CMD_ATTN_BIT_SET_UPPER -
			IGU_CMD_INT_ACK_BASE) << 3),
		      (u32)निश्चितed_bits);

	DP_VERBOSE(p_hwfn, NETIF_MSG_INTR, "set cmd IGU: 0x%04x\n",
		   निश्चितed_bits);

	वापस 0;
पूर्ण

अटल व्योम qed_पूर्णांक_attn_prपूर्णांक(काष्ठा qed_hwfn *p_hwfn,
			       क्रमागत block_id id,
			       क्रमागत dbg_attn_type type, bool b_clear)
अणु
	काष्ठा dbg_attn_block_result attn_results;
	क्रमागत dbg_status status;

	स_रखो(&attn_results, 0, माप(attn_results));

	status = qed_dbg_पढ़ो_attn(p_hwfn, p_hwfn->p_dpc_ptt, id, type,
				   b_clear, &attn_results);
	अगर (status != DBG_STATUS_OK)
		DP_NOTICE(p_hwfn,
			  "Failed to parse attention information [status: %s]\n",
			  qed_dbg_get_status_str(status));
	अन्यथा
		qed_dbg_parse_attn(p_hwfn, &attn_results);
पूर्ण

/**
 * qed_पूर्णांक_deनिश्चितion_aeu_bit() - Handles the effects of a single
 * cause of the attention.
 *
 * @p_hwfn: HW device data.
 * @p_aeu: Descriptor of an AEU bit which caused the attention.
 * @aeu_en_reg: Register offset of the AEU enable reg. which configured
 *              this bit to this group.
 * @p_bit_name: AEU bit description क्रम logging purposes.
 * @biपंचांगask: Index of this bit in the aeu_en_reg.
 *
 * Return: Zero on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक
qed_पूर्णांक_deनिश्चितion_aeu_bit(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा aeu_invert_reg_bit *p_aeu,
			    u32 aeu_en_reg,
			    स्थिर अक्षर *p_bit_name, u32 biपंचांगask)
अणु
	bool b_fatal = false;
	पूर्णांक rc = -EINVAL;
	u32 val;

	DP_INFO(p_hwfn, "Deasserted attention `%s'[%08x]\n",
		p_bit_name, biपंचांगask);

	/* Call callback beक्रमe clearing the पूर्णांकerrupt status */
	अगर (p_aeu->cb) अणु
		DP_INFO(p_hwfn, "`%s (attention)': Calling Callback function\n",
			p_bit_name);
		rc = p_aeu->cb(p_hwfn);
	पूर्ण

	अगर (rc)
		b_fatal = true;

	/* Prपूर्णांक HW block पूर्णांकerrupt रेजिस्टरs */
	अगर (p_aeu->block_index != MAX_BLOCK_ID)
		qed_पूर्णांक_attn_prपूर्णांक(p_hwfn, p_aeu->block_index,
				   ATTN_TYPE_INTERRUPT, !b_fatal);

	/* Reach निश्चितion अगर attention is fatal */
	अगर (b_fatal)
		qed_hw_err_notअगरy(p_hwfn, p_hwfn->p_dpc_ptt, QED_HW_ERR_HW_ATTN,
				  "`%s': Fatal attention\n",
				  p_bit_name);
	अन्यथा /* If the attention is benign, no need to prevent it */
		जाओ out;

	/* Prevent this Attention from being निश्चितed in the future */
	val = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt, aeu_en_reg);
	qed_wr(p_hwfn, p_hwfn->p_dpc_ptt, aeu_en_reg, (val & ~biपंचांगask));
	DP_INFO(p_hwfn, "`%s' - Disabled future attentions\n",
		p_bit_name);

out:
	वापस rc;
पूर्ण

/**
 * qed_पूर्णांक_deनिश्चितion_parity() - Handle a single parity AEU source.
 *
 * @p_hwfn: HW device data.
 * @p_aeu: Descriptor of an AEU bit which caused the parity.
 * @aeu_en_reg: Address of the AEU enable रेजिस्टर.
 * @bit_index: Index (0-31) of an AEU bit.
 */
अटल व्योम qed_पूर्णांक_deनिश्चितion_parity(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा aeu_invert_reg_bit *p_aeu,
				       u32 aeu_en_reg, u8 bit_index)
अणु
	u32 block_id = p_aeu->block_index, mask, val;

	DP_NOTICE(p_hwfn->cdev,
		  "%s parity attention is set [address 0x%08x, bit %d]\n",
		  p_aeu->bit_name, aeu_en_reg, bit_index);

	अगर (block_id != MAX_BLOCK_ID) अणु
		qed_पूर्णांक_attn_prपूर्णांक(p_hwfn, block_id, ATTN_TYPE_PARITY, false);

		/* In BB, there's a single parity bit क्रम several blocks */
		अगर (block_id == BLOCK_BTB) अणु
			qed_पूर्णांक_attn_prपूर्णांक(p_hwfn, BLOCK_OPTE,
					   ATTN_TYPE_PARITY, false);
			qed_पूर्णांक_attn_prपूर्णांक(p_hwfn, BLOCK_MCP,
					   ATTN_TYPE_PARITY, false);
		पूर्ण
	पूर्ण

	/* Prevent this parity error from being re-निश्चितed */
	mask = ~BIT(bit_index);
	val = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt, aeu_en_reg);
	qed_wr(p_hwfn, p_hwfn->p_dpc_ptt, aeu_en_reg, val & mask);
	DP_INFO(p_hwfn, "`%s' - Disabled future parity errors\n",
		p_aeu->bit_name);
पूर्ण

/**
 * qed_पूर्णांक_deनिश्चितion() - Handle deनिश्चितion of previously निश्चितed
 * attentions.
 *
 * @p_hwfn: HW device data.
 * @deनिश्चितed_bits: newly deनिश्चितed bits.
 *
 * Return: Zero value.
 */
अटल पूर्णांक qed_पूर्णांक_deनिश्चितion(काष्ठा qed_hwfn  *p_hwfn,
			       u16 deनिश्चितed_bits)
अणु
	काष्ठा qed_sb_attn_info *sb_attn_sw = p_hwfn->p_sb_attn;
	u32 aeu_inv_arr[NUM_ATTN_REGS], aeu_mask, aeu_en, en;
	u8 i, j, k, bit_idx;
	पूर्णांक rc = 0;

	/* Read the attention रेजिस्टरs in the AEU */
	क्रम (i = 0; i < NUM_ATTN_REGS; i++) अणु
		aeu_inv_arr[i] = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
					MISC_REG_AEU_AFTER_INVERT_1_IGU +
					i * 0x4);
		DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
			   "Deasserted bits [%d]: %08x\n",
			   i, aeu_inv_arr[i]);
	पूर्ण

	/* Find parity attentions first */
	क्रम (i = 0; i < NUM_ATTN_REGS; i++) अणु
		काष्ठा aeu_invert_reg *p_aeu = &sb_attn_sw->p_aeu_desc[i];
		u32 parities;

		aeu_en = MISC_REG_AEU_ENABLE1_IGU_OUT_0 + i * माप(u32);
		en = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt, aeu_en);

		/* Skip रेजिस्टर in which no parity bit is currently set */
		parities = sb_attn_sw->parity_mask[i] & aeu_inv_arr[i] & en;
		अगर (!parities)
			जारी;

		क्रम (j = 0, bit_idx = 0; bit_idx < 32; j++) अणु
			काष्ठा aeu_invert_reg_bit *p_bit = &p_aeu->bits[j];

			अगर (qed_पूर्णांक_is_parity_flag(p_hwfn, p_bit) &&
			    !!(parities & BIT(bit_idx)))
				qed_पूर्णांक_deनिश्चितion_parity(p_hwfn, p_bit,
							   aeu_en, bit_idx);

			bit_idx += ATTENTION_LENGTH(p_bit->flags);
		पूर्ण
	पूर्ण

	/* Find non-parity cause क्रम attention and act */
	क्रम (k = 0; k < MAX_ATTN_GRPS; k++) अणु
		काष्ठा aeu_invert_reg_bit *p_aeu;

		/* Handle only groups whose attention is currently deनिश्चितed */
		अगर (!(deनिश्चितed_bits & (1 << k)))
			जारी;

		क्रम (i = 0; i < NUM_ATTN_REGS; i++) अणु
			u32 bits;

			aeu_en = MISC_REG_AEU_ENABLE1_IGU_OUT_0 +
				 i * माप(u32) +
				 k * माप(u32) * NUM_ATTN_REGS;

			en = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt, aeu_en);
			bits = aeu_inv_arr[i] & en;

			/* Skip अगर no bit from this group is currently set */
			अगर (!bits)
				जारी;

			/* Find all set bits from current रेजिस्टर which beदीर्घ
			 * to current group, making them responsible क्रम the
			 * previous निश्चितion.
			 */
			क्रम (j = 0, bit_idx = 0; bit_idx < 32; j++) अणु
				दीर्घ अचिन्हित पूर्णांक biपंचांगask;
				u8 bit, bit_len;

				p_aeu = &sb_attn_sw->p_aeu_desc[i].bits[j];
				p_aeu = qed_पूर्णांक_aeu_translate(p_hwfn, p_aeu);

				bit = bit_idx;
				bit_len = ATTENTION_LENGTH(p_aeu->flags);
				अगर (qed_पूर्णांक_is_parity_flag(p_hwfn, p_aeu)) अणु
					/* Skip Parity */
					bit++;
					bit_len--;
				पूर्ण

				biपंचांगask = bits & (((1 << bit_len) - 1) << bit);
				biपंचांगask >>= bit;

				अगर (biपंचांगask) अणु
					u32 flags = p_aeu->flags;
					अक्षर bit_name[30];
					u8 num;

					num = (u8)find_first_bit(&biपंचांगask,
								 bit_len);

					/* Some bits represent more than a
					 * a single पूर्णांकerrupt. Correctly prपूर्णांक
					 * their name.
					 */
					अगर (ATTENTION_LENGTH(flags) > 2 ||
					    ((flags & ATTENTION_PAR_INT) &&
					     ATTENTION_LENGTH(flags) > 1))
						snम_लिखो(bit_name, 30,
							 p_aeu->bit_name, num);
					अन्यथा
						strlcpy(bit_name,
							p_aeu->bit_name, 30);

					/* We now need to pass biपंचांगask in its
					 * correct position.
					 */
					biपंचांगask <<= bit;

					/* Handle source of the attention */
					qed_पूर्णांक_deनिश्चितion_aeu_bit(p_hwfn,
								    p_aeu,
								    aeu_en,
								    bit_name,
								    biपंचांगask);
				पूर्ण

				bit_idx += ATTENTION_LENGTH(p_aeu->flags);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Handle missed DORQ attention */
	qed_करोrq_attn_handler(p_hwfn);

	/* Clear IGU indication क्रम the deनिश्चितed bits */
	सूचीECT_REG_WR((u8 __iomem *)p_hwfn->regview +
				    GTT_BAR0_MAP_REG_IGU_CMD +
				    ((IGU_CMD_ATTN_BIT_CLR_UPPER -
				      IGU_CMD_INT_ACK_BASE) << 3),
				    ~((u32)deनिश्चितed_bits));

	/* Unmask deनिश्चितed attentions in IGU */
	aeu_mask = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt, IGU_REG_ATTENTION_ENABLE);
	aeu_mask |= (deनिश्चितed_bits & ATTN_BITS_MASKABLE);
	qed_wr(p_hwfn, p_hwfn->p_dpc_ptt, IGU_REG_ATTENTION_ENABLE, aeu_mask);

	/* Clear deनिश्चितion from inner state */
	sb_attn_sw->known_attn &= ~deनिश्चितed_bits;

	वापस rc;
पूर्ण

अटल पूर्णांक qed_पूर्णांक_attentions(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_sb_attn_info *p_sb_attn_sw = p_hwfn->p_sb_attn;
	काष्ठा atten_status_block *p_sb_attn = p_sb_attn_sw->sb_attn;
	u32 attn_bits = 0, attn_acks = 0;
	u16 निश्चितed_bits, deनिश्चितed_bits;
	__le16 index;
	पूर्णांक rc = 0;

	/* Read current attention bits/acks - safeguard against attentions
	 * by guaranting work on a synchronized समयframe
	 */
	करो अणु
		index = p_sb_attn->sb_index;
		/* finish पढ़ोing index beक्रमe the loop condition */
		dma_rmb();
		attn_bits = le32_to_cpu(p_sb_attn->atten_bits);
		attn_acks = le32_to_cpu(p_sb_attn->atten_ack);
	पूर्ण जबतक (index != p_sb_attn->sb_index);
	p_sb_attn->sb_index = index;

	/* Attention / Deनिश्चितion are meaningful (and in correct state)
	 * only when they dअगरfer and consistent with known state - deनिश्चितion
	 * when previous attention & current ack, and निश्चितion when current
	 * attention with no previous attention
	 */
	निश्चितed_bits = (attn_bits & ~attn_acks & ATTN_STATE_BITS) &
		~p_sb_attn_sw->known_attn;
	deनिश्चितed_bits = (~attn_bits & attn_acks & ATTN_STATE_BITS) &
		p_sb_attn_sw->known_attn;

	अगर ((निश्चितed_bits & ~0x100) || (deनिश्चितed_bits & ~0x100)) अणु
		DP_INFO(p_hwfn,
			"Attention: Index: 0x%04x, Bits: 0x%08x, Acks: 0x%08x, asserted: 0x%04x, De-asserted 0x%04x [Prev. known: 0x%04x]\n",
			index, attn_bits, attn_acks, निश्चितed_bits,
			deनिश्चितed_bits, p_sb_attn_sw->known_attn);
	पूर्ण अन्यथा अगर (निश्चितed_bits == 0x100) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
			   "MFW indication via attention\n");
	पूर्ण अन्यथा अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
			   "MFW indication [deassertion]\n");
	पूर्ण

	अगर (निश्चितed_bits) अणु
		rc = qed_पूर्णांक_निश्चितion(p_hwfn, निश्चितed_bits);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (deनिश्चितed_bits)
		rc = qed_पूर्णांक_deनिश्चितion(p_hwfn, deनिश्चितed_bits);

	वापस rc;
पूर्ण

अटल व्योम qed_sb_ack_attn(काष्ठा qed_hwfn *p_hwfn,
			    व्योम __iomem *igu_addr, u32 ack_cons)
अणु
	u32 igu_ack;

	igu_ack = ((ack_cons << IGU_PROD_CONS_UPDATE_SB_INDEX_SHIFT) |
		   (1 << IGU_PROD_CONS_UPDATE_UPDATE_FLAG_SHIFT) |
		   (IGU_INT_NOP << IGU_PROD_CONS_UPDATE_ENABLE_INT_SHIFT) |
		   (IGU_SEG_ACCESS_ATTN <<
		    IGU_PROD_CONS_UPDATE_SEGMENT_ACCESS_SHIFT));

	सूचीECT_REG_WR(igu_addr, igu_ack);

	/* Both segments (पूर्णांकerrupts & acks) are written to same place address;
	 * Need to guarantee all commands will be received (in-order) by HW.
	 */
	barrier();
पूर्ण

व्योम qed_पूर्णांक_sp_dpc(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा qed_hwfn *p_hwfn = from_tasklet(p_hwfn, t, sp_dpc);
	काष्ठा qed_pi_info *pi_info = शून्य;
	काष्ठा qed_sb_attn_info *sb_attn;
	काष्ठा qed_sb_info *sb_info;
	पूर्णांक arr_size;
	u16 rc = 0;

	अगर (!p_hwfn->p_sp_sb) अणु
		DP_ERR(p_hwfn->cdev, "DPC called - no p_sp_sb\n");
		वापस;
	पूर्ण

	sb_info = &p_hwfn->p_sp_sb->sb_info;
	arr_size = ARRAY_SIZE(p_hwfn->p_sp_sb->pi_info_arr);
	अगर (!sb_info) अणु
		DP_ERR(p_hwfn->cdev,
		       "Status block is NULL - cannot ack interrupts\n");
		वापस;
	पूर्ण

	अगर (!p_hwfn->p_sb_attn) अणु
		DP_ERR(p_hwfn->cdev, "DPC called - no p_sb_attn");
		वापस;
	पूर्ण
	sb_attn = p_hwfn->p_sb_attn;

	DP_VERBOSE(p_hwfn, NETIF_MSG_INTR, "DPC Called! (hwfn %p %d)\n",
		   p_hwfn, p_hwfn->my_id);

	/* Disable ack क्रम def status block. Required both क्रम msix +
	 * पूर्णांकa in non-mask mode, in पूर्णांकa करोes no harm.
	 */
	qed_sb_ack(sb_info, IGU_INT_DISABLE, 0);

	/* Gather Interrupts/Attentions inक्रमmation */
	अगर (!sb_info->sb_virt) अणु
		DP_ERR(p_hwfn->cdev,
		       "Interrupt Status block is NULL - cannot check for new interrupts!\n");
	पूर्ण अन्यथा अणु
		u32 पंचांगp_index = sb_info->sb_ack;

		rc = qed_sb_update_sb_idx(sb_info);
		DP_VERBOSE(p_hwfn->cdev, NETIF_MSG_INTR,
			   "Interrupt indices: 0x%08x --> 0x%08x\n",
			   पंचांगp_index, sb_info->sb_ack);
	पूर्ण

	अगर (!sb_attn || !sb_attn->sb_attn) अणु
		DP_ERR(p_hwfn->cdev,
		       "Attentions Status block is NULL - cannot check for new attentions!\n");
	पूर्ण अन्यथा अणु
		u16 पंचांगp_index = sb_attn->index;

		rc |= qed_attn_update_idx(p_hwfn, sb_attn);
		DP_VERBOSE(p_hwfn->cdev, NETIF_MSG_INTR,
			   "Attention indices: 0x%08x --> 0x%08x\n",
			   पंचांगp_index, sb_attn->index);
	पूर्ण

	/* Check अगर we expect पूर्णांकerrupts at this समय. अगर not just ack them */
	अगर (!(rc & QED_SB_EVENT_MASK)) अणु
		qed_sb_ack(sb_info, IGU_INT_ENABLE, 1);
		वापस;
	पूर्ण

	/* Check the validity of the DPC ptt. If not ack पूर्णांकerrupts and fail */
	अगर (!p_hwfn->p_dpc_ptt) अणु
		DP_NOTICE(p_hwfn->cdev, "Failed to allocate PTT\n");
		qed_sb_ack(sb_info, IGU_INT_ENABLE, 1);
		वापस;
	पूर्ण

	अगर (rc & QED_SB_ATT_IDX)
		qed_पूर्णांक_attentions(p_hwfn);

	अगर (rc & QED_SB_IDX) अणु
		पूर्णांक pi;

		/* Look क्रम a मुक्त index */
		क्रम (pi = 0; pi < arr_size; pi++) अणु
			pi_info = &p_hwfn->p_sp_sb->pi_info_arr[pi];
			अगर (pi_info->comp_cb)
				pi_info->comp_cb(p_hwfn, pi_info->cookie);
		पूर्ण
	पूर्ण

	अगर (sb_attn && (rc & QED_SB_ATT_IDX))
		/* This should be करोne beक्रमe the पूर्णांकerrupts are enabled,
		 * since otherwise a new attention will be generated.
		 */
		qed_sb_ack_attn(p_hwfn, sb_info->igu_addr, sb_attn->index);

	qed_sb_ack(sb_info, IGU_INT_ENABLE, 1);
पूर्ण

अटल व्योम qed_पूर्णांक_sb_attn_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_sb_attn_info *p_sb = p_hwfn->p_sb_attn;

	अगर (!p_sb)
		वापस;

	अगर (p_sb->sb_attn)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  SB_ATTN_ALIGNED_SIZE(p_hwfn),
				  p_sb->sb_attn, p_sb->sb_phys);
	kमुक्त(p_sb);
	p_hwfn->p_sb_attn = शून्य;
पूर्ण

अटल व्योम qed_पूर्णांक_sb_attn_setup(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_sb_attn_info *sb_info = p_hwfn->p_sb_attn;

	स_रखो(sb_info->sb_attn, 0, माप(*sb_info->sb_attn));

	sb_info->index = 0;
	sb_info->known_attn = 0;

	/* Configure Attention Status Block in IGU */
	qed_wr(p_hwfn, p_ptt, IGU_REG_ATTN_MSG_ADDR_L,
	       lower_32_bits(p_hwfn->p_sb_attn->sb_phys));
	qed_wr(p_hwfn, p_ptt, IGU_REG_ATTN_MSG_ADDR_H,
	       upper_32_bits(p_hwfn->p_sb_attn->sb_phys));
पूर्ण

अटल व्योम qed_पूर्णांक_sb_attn_init(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 व्योम *sb_virt_addr, dma_addr_t sb_phy_addr)
अणु
	काष्ठा qed_sb_attn_info *sb_info = p_hwfn->p_sb_attn;
	पूर्णांक i, j, k;

	sb_info->sb_attn = sb_virt_addr;
	sb_info->sb_phys = sb_phy_addr;

	/* Set the poपूर्णांकer to the AEU descriptors */
	sb_info->p_aeu_desc = aeu_descs;

	/* Calculate Parity Masks */
	स_रखो(sb_info->parity_mask, 0, माप(u32) * NUM_ATTN_REGS);
	क्रम (i = 0; i < NUM_ATTN_REGS; i++) अणु
		/* j is array index, k is bit index */
		क्रम (j = 0, k = 0; k < 32; j++) अणु
			काष्ठा aeu_invert_reg_bit *p_aeu;

			p_aeu = &aeu_descs[i].bits[j];
			अगर (qed_पूर्णांक_is_parity_flag(p_hwfn, p_aeu))
				sb_info->parity_mask[i] |= 1 << k;

			k += ATTENTION_LENGTH(p_aeu->flags);
		पूर्ण
		DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
			   "Attn Mask [Reg %d]: 0x%08x\n",
			   i, sb_info->parity_mask[i]);
	पूर्ण

	/* Set the address of cleanup क्रम the mcp attention */
	sb_info->mfw_attn_addr = (p_hwfn->rel_pf_id << 3) +
				 MISC_REG_AEU_GENERAL_ATTN_0;

	qed_पूर्णांक_sb_attn_setup(p_hwfn, p_ptt);
पूर्ण

अटल पूर्णांक qed_पूर्णांक_sb_attn_alloc(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	काष्ठा qed_sb_attn_info *p_sb;
	dma_addr_t p_phys = 0;
	व्योम *p_virt;

	/* SB काष्ठा */
	p_sb = kदो_स्मृति(माप(*p_sb), GFP_KERNEL);
	अगर (!p_sb)
		वापस -ENOMEM;

	/* SB ring  */
	p_virt = dma_alloc_coherent(&cdev->pdev->dev,
				    SB_ATTN_ALIGNED_SIZE(p_hwfn),
				    &p_phys, GFP_KERNEL);

	अगर (!p_virt) अणु
		kमुक्त(p_sb);
		वापस -ENOMEM;
	पूर्ण

	/* Attention setup */
	p_hwfn->p_sb_attn = p_sb;
	qed_पूर्णांक_sb_attn_init(p_hwfn, p_ptt, p_virt, p_phys);

	वापस 0;
पूर्ण

/* coalescing समयout = बारet << (समयr_res + 1) */
#घोषणा QED_CAU_DEF_RX_USECS 24
#घोषणा QED_CAU_DEF_TX_USECS 48

व्योम qed_init_cau_sb_entry(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा cau_sb_entry *p_sb_entry,
			   u8 pf_id, u16 vf_number, u8 vf_valid)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u32 cau_state, params = 0, data = 0;
	u8 समयr_res;

	स_रखो(p_sb_entry, 0, माप(*p_sb_entry));

	SET_FIELD(params, CAU_SB_ENTRY_PF_NUMBER, pf_id);
	SET_FIELD(params, CAU_SB_ENTRY_VF_NUMBER, vf_number);
	SET_FIELD(params, CAU_SB_ENTRY_VF_VALID, vf_valid);
	SET_FIELD(params, CAU_SB_ENTRY_SB_TIMESET0, 0x7F);
	SET_FIELD(params, CAU_SB_ENTRY_SB_TIMESET1, 0x7F);

	cau_state = CAU_HC_DISABLE_STATE;

	अगर (cdev->पूर्णांक_coalescing_mode == QED_COAL_MODE_ENABLE) अणु
		cau_state = CAU_HC_ENABLE_STATE;
		अगर (!cdev->rx_coalesce_usecs)
			cdev->rx_coalesce_usecs = QED_CAU_DEF_RX_USECS;
		अगर (!cdev->tx_coalesce_usecs)
			cdev->tx_coalesce_usecs = QED_CAU_DEF_TX_USECS;
	पूर्ण

	/* Coalesce = (बारet << समयr-res), बारet is 7bit wide */
	अगर (cdev->rx_coalesce_usecs <= 0x7F)
		समयr_res = 0;
	अन्यथा अगर (cdev->rx_coalesce_usecs <= 0xFF)
		समयr_res = 1;
	अन्यथा
		समयr_res = 2;

	SET_FIELD(params, CAU_SB_ENTRY_TIMER_RES0, समयr_res);

	अगर (cdev->tx_coalesce_usecs <= 0x7F)
		समयr_res = 0;
	अन्यथा अगर (cdev->tx_coalesce_usecs <= 0xFF)
		समयr_res = 1;
	अन्यथा
		समयr_res = 2;

	SET_FIELD(params, CAU_SB_ENTRY_TIMER_RES1, समयr_res);
	p_sb_entry->params = cpu_to_le32(params);

	SET_FIELD(data, CAU_SB_ENTRY_STATE0, cau_state);
	SET_FIELD(data, CAU_SB_ENTRY_STATE1, cau_state);
	p_sb_entry->data = cpu_to_le32(data);
पूर्ण

अटल व्योम qed_पूर्णांक_cau_conf_pi(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt,
				u16 igu_sb_id,
				u32 pi_index,
				क्रमागत qed_coalescing_fsm coalescing_fsm,
				u8 बारet)
अणु
	u32 sb_offset, pi_offset;
	u32 prod = 0;

	अगर (IS_VF(p_hwfn->cdev))
		वापस;

	SET_FIELD(prod, CAU_PI_ENTRY_PI_TIMESET, बारet);
	अगर (coalescing_fsm == QED_COAL_RX_STATE_MACHINE)
		SET_FIELD(prod, CAU_PI_ENTRY_FSM_SEL, 0);
	अन्यथा
		SET_FIELD(prod, CAU_PI_ENTRY_FSM_SEL, 1);

	sb_offset = igu_sb_id * PIS_PER_SB_E4;
	pi_offset = sb_offset + pi_index;

	अगर (p_hwfn->hw_init_करोne)
		qed_wr(p_hwfn, p_ptt,
		       CAU_REG_PI_MEMORY + pi_offset * माप(u32), prod);
	अन्यथा
		STORE_RT_REG(p_hwfn, CAU_REG_PI_MEMORY_RT_OFFSET + pi_offset,
			     prod);
पूर्ण

व्योम qed_पूर्णांक_cau_conf_sb(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt,
			 dma_addr_t sb_phys,
			 u16 igu_sb_id, u16 vf_number, u8 vf_valid)
अणु
	काष्ठा cau_sb_entry sb_entry;

	qed_init_cau_sb_entry(p_hwfn, &sb_entry, p_hwfn->rel_pf_id,
			      vf_number, vf_valid);

	अगर (p_hwfn->hw_init_करोne) अणु
		/* Wide-bus, initialize via DMAE */
		u64 phys_addr = (u64)sb_phys;

		qed_dmae_host2grc(p_hwfn, p_ptt, (u64)(uपूर्णांकptr_t)&phys_addr,
				  CAU_REG_SB_ADDR_MEMORY +
				  igu_sb_id * माप(u64), 2, शून्य);
		qed_dmae_host2grc(p_hwfn, p_ptt, (u64)(uपूर्णांकptr_t)&sb_entry,
				  CAU_REG_SB_VAR_MEMORY +
				  igu_sb_id * माप(u64), 2, शून्य);
	पूर्ण अन्यथा अणु
		/* Initialize Status Block Address */
		STORE_RT_REG_AGG(p_hwfn,
				 CAU_REG_SB_ADDR_MEMORY_RT_OFFSET +
				 igu_sb_id * 2,
				 sb_phys);

		STORE_RT_REG_AGG(p_hwfn,
				 CAU_REG_SB_VAR_MEMORY_RT_OFFSET +
				 igu_sb_id * 2,
				 sb_entry);
	पूर्ण

	/* Configure pi coalescing अगर set */
	अगर (p_hwfn->cdev->पूर्णांक_coalescing_mode == QED_COAL_MODE_ENABLE) अणु
		u8 num_tc = p_hwfn->hw_info.num_hw_tc;
		u8 बारet, समयr_res;
		u8 i;

		/* बारet = (coalesce >> समयr-res), बारet is 7bit wide */
		अगर (p_hwfn->cdev->rx_coalesce_usecs <= 0x7F)
			समयr_res = 0;
		अन्यथा अगर (p_hwfn->cdev->rx_coalesce_usecs <= 0xFF)
			समयr_res = 1;
		अन्यथा
			समयr_res = 2;
		बारet = (u8)(p_hwfn->cdev->rx_coalesce_usecs >> समयr_res);
		qed_पूर्णांक_cau_conf_pi(p_hwfn, p_ptt, igu_sb_id, RX_PI,
				    QED_COAL_RX_STATE_MACHINE, बारet);

		अगर (p_hwfn->cdev->tx_coalesce_usecs <= 0x7F)
			समयr_res = 0;
		अन्यथा अगर (p_hwfn->cdev->tx_coalesce_usecs <= 0xFF)
			समयr_res = 1;
		अन्यथा
			समयr_res = 2;
		बारet = (u8)(p_hwfn->cdev->tx_coalesce_usecs >> समयr_res);
		क्रम (i = 0; i < num_tc; i++) अणु
			qed_पूर्णांक_cau_conf_pi(p_hwfn, p_ptt,
					    igu_sb_id, TX_PI(i),
					    QED_COAL_TX_STATE_MACHINE,
					    बारet);
		पूर्ण
	पूर्ण
पूर्ण

व्योम qed_पूर्णांक_sb_setup(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt, काष्ठा qed_sb_info *sb_info)
अणु
	/* zero status block and ack counter */
	sb_info->sb_ack = 0;
	स_रखो(sb_info->sb_virt, 0, माप(*sb_info->sb_virt));

	अगर (IS_PF(p_hwfn->cdev))
		qed_पूर्णांक_cau_conf_sb(p_hwfn, p_ptt, sb_info->sb_phys,
				    sb_info->igu_sb_id, 0, 0);
पूर्ण

काष्ठा qed_igu_block *qed_get_igu_मुक्त_sb(काष्ठा qed_hwfn *p_hwfn, bool b_is_pf)
अणु
	काष्ठा qed_igu_block *p_block;
	u16 igu_id;

	क्रम (igu_id = 0; igu_id < QED_MAPPING_MEMORY_SIZE(p_hwfn->cdev);
	     igu_id++) अणु
		p_block = &p_hwfn->hw_info.p_igu_info->entry[igu_id];

		अगर (!(p_block->status & QED_IGU_STATUS_VALID) ||
		    !(p_block->status & QED_IGU_STATUS_FREE))
			जारी;

		अगर (!!(p_block->status & QED_IGU_STATUS_PF) == b_is_pf)
			वापस p_block;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल u16 qed_get_pf_igu_sb_id(काष्ठा qed_hwfn *p_hwfn, u16 vector_id)
अणु
	काष्ठा qed_igu_block *p_block;
	u16 igu_id;

	क्रम (igu_id = 0; igu_id < QED_MAPPING_MEMORY_SIZE(p_hwfn->cdev);
	     igu_id++) अणु
		p_block = &p_hwfn->hw_info.p_igu_info->entry[igu_id];

		अगर (!(p_block->status & QED_IGU_STATUS_VALID) ||
		    !p_block->is_pf ||
		    p_block->vector_number != vector_id)
			जारी;

		वापस igu_id;
	पूर्ण

	वापस QED_SB_INVALID_IDX;
पूर्ण

u16 qed_get_igu_sb_id(काष्ठा qed_hwfn *p_hwfn, u16 sb_id)
अणु
	u16 igu_sb_id;

	/* Assuming continuous set of IGU SBs dedicated क्रम given PF */
	अगर (sb_id == QED_SP_SB_ID)
		igu_sb_id = p_hwfn->hw_info.p_igu_info->igu_dsb_id;
	अन्यथा अगर (IS_PF(p_hwfn->cdev))
		igu_sb_id = qed_get_pf_igu_sb_id(p_hwfn, sb_id + 1);
	अन्यथा
		igu_sb_id = qed_vf_get_igu_sb_id(p_hwfn, sb_id);

	अगर (sb_id == QED_SP_SB_ID)
		DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
			   "Slowpath SB index in IGU is 0x%04x\n", igu_sb_id);
	अन्यथा
		DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
			   "SB [%04x] <--> IGU SB [%04x]\n", sb_id, igu_sb_id);

	वापस igu_sb_id;
पूर्ण

पूर्णांक qed_पूर्णांक_sb_init(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt,
		    काष्ठा qed_sb_info *sb_info,
		    व्योम *sb_virt_addr, dma_addr_t sb_phy_addr, u16 sb_id)
अणु
	sb_info->sb_virt = sb_virt_addr;
	sb_info->sb_phys = sb_phy_addr;

	sb_info->igu_sb_id = qed_get_igu_sb_id(p_hwfn, sb_id);

	अगर (sb_id != QED_SP_SB_ID) अणु
		अगर (IS_PF(p_hwfn->cdev)) अणु
			काष्ठा qed_igu_info *p_info;
			काष्ठा qed_igu_block *p_block;

			p_info = p_hwfn->hw_info.p_igu_info;
			p_block = &p_info->entry[sb_info->igu_sb_id];

			p_block->sb_info = sb_info;
			p_block->status &= ~QED_IGU_STATUS_FREE;
			p_info->usage.मुक्त_cnt--;
		पूर्ण अन्यथा अणु
			qed_vf_set_sb_info(p_hwfn, sb_id, sb_info);
		पूर्ण
	पूर्ण

	sb_info->cdev = p_hwfn->cdev;

	/* The igu address will hold the असलolute address that needs to be
	 * written to क्रम a specअगरic status block
	 */
	अगर (IS_PF(p_hwfn->cdev)) अणु
		sb_info->igu_addr = (u8 __iomem *)p_hwfn->regview +
						  GTT_BAR0_MAP_REG_IGU_CMD +
						  (sb_info->igu_sb_id << 3);
	पूर्ण अन्यथा अणु
		sb_info->igu_addr = (u8 __iomem *)p_hwfn->regview +
						  PXP_VF_BAR0_START_IGU +
						  ((IGU_CMD_INT_ACK_BASE +
						    sb_info->igu_sb_id) << 3);
	पूर्ण

	sb_info->flags |= QED_SB_INFO_INIT;

	qed_पूर्णांक_sb_setup(p_hwfn, p_ptt, sb_info);

	वापस 0;
पूर्ण

पूर्णांक qed_पूर्णांक_sb_release(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_sb_info *sb_info, u16 sb_id)
अणु
	काष्ठा qed_igu_block *p_block;
	काष्ठा qed_igu_info *p_info;

	अगर (!sb_info)
		वापस 0;

	/* zero status block and ack counter */
	sb_info->sb_ack = 0;
	स_रखो(sb_info->sb_virt, 0, माप(*sb_info->sb_virt));

	अगर (IS_VF(p_hwfn->cdev)) अणु
		qed_vf_set_sb_info(p_hwfn, sb_id, शून्य);
		वापस 0;
	पूर्ण

	p_info = p_hwfn->hw_info.p_igu_info;
	p_block = &p_info->entry[sb_info->igu_sb_id];

	/* Vector 0 is reserved to Default SB */
	अगर (!p_block->vector_number) अणु
		DP_ERR(p_hwfn, "Do Not free sp sb using this function");
		वापस -EINVAL;
	पूर्ण

	/* Lose reference to client's SB info, and fix counters */
	p_block->sb_info = शून्य;
	p_block->status |= QED_IGU_STATUS_FREE;
	p_info->usage.मुक्त_cnt++;

	वापस 0;
पूर्ण

अटल व्योम qed_पूर्णांक_sp_sb_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_sb_sp_info *p_sb = p_hwfn->p_sp_sb;

	अगर (!p_sb)
		वापस;

	अगर (p_sb->sb_info.sb_virt)
		dma_मुक्त_coherent(&p_hwfn->cdev->pdev->dev,
				  SB_ALIGNED_SIZE(p_hwfn),
				  p_sb->sb_info.sb_virt,
				  p_sb->sb_info.sb_phys);
	kमुक्त(p_sb);
	p_hwfn->p_sp_sb = शून्य;
पूर्ण

अटल पूर्णांक qed_पूर्णांक_sp_sb_alloc(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_sb_sp_info *p_sb;
	dma_addr_t p_phys = 0;
	व्योम *p_virt;

	/* SB काष्ठा */
	p_sb = kदो_स्मृति(माप(*p_sb), GFP_KERNEL);
	अगर (!p_sb)
		वापस -ENOMEM;

	/* SB ring  */
	p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				    SB_ALIGNED_SIZE(p_hwfn),
				    &p_phys, GFP_KERNEL);
	अगर (!p_virt) अणु
		kमुक्त(p_sb);
		वापस -ENOMEM;
	पूर्ण

	/* Status Block setup */
	p_hwfn->p_sp_sb = p_sb;
	qed_पूर्णांक_sb_init(p_hwfn, p_ptt, &p_sb->sb_info, p_virt,
			p_phys, QED_SP_SB_ID);

	स_रखो(p_sb->pi_info_arr, 0, माप(p_sb->pi_info_arr));

	वापस 0;
पूर्ण

पूर्णांक qed_पूर्णांक_रेजिस्टर_cb(काष्ठा qed_hwfn *p_hwfn,
			qed_पूर्णांक_comp_cb_t comp_cb,
			व्योम *cookie, u8 *sb_idx, __le16 **p_fw_cons)
अणु
	काष्ठा qed_sb_sp_info *p_sp_sb = p_hwfn->p_sp_sb;
	पूर्णांक rc = -ENOMEM;
	u8 pi;

	/* Look क्रम a मुक्त index */
	क्रम (pi = 0; pi < ARRAY_SIZE(p_sp_sb->pi_info_arr); pi++) अणु
		अगर (p_sp_sb->pi_info_arr[pi].comp_cb)
			जारी;

		p_sp_sb->pi_info_arr[pi].comp_cb = comp_cb;
		p_sp_sb->pi_info_arr[pi].cookie = cookie;
		*sb_idx = pi;
		*p_fw_cons = &p_sp_sb->sb_info.sb_virt->pi_array[pi];
		rc = 0;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_पूर्णांक_unरेजिस्टर_cb(काष्ठा qed_hwfn *p_hwfn, u8 pi)
अणु
	काष्ठा qed_sb_sp_info *p_sp_sb = p_hwfn->p_sp_sb;

	अगर (p_sp_sb->pi_info_arr[pi].comp_cb == शून्य)
		वापस -ENOMEM;

	p_sp_sb->pi_info_arr[pi].comp_cb = शून्य;
	p_sp_sb->pi_info_arr[pi].cookie = शून्य;

	वापस 0;
पूर्ण

u16 qed_पूर्णांक_get_sp_sb_id(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस p_hwfn->p_sp_sb->sb_info.igu_sb_id;
पूर्ण

व्योम qed_पूर्णांक_igu_enable_पूर्णांक(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, क्रमागत qed_पूर्णांक_mode पूर्णांक_mode)
अणु
	u32 igu_pf_conf = IGU_PF_CONF_FUNC_EN | IGU_PF_CONF_ATTN_BIT_EN;

	p_hwfn->cdev->पूर्णांक_mode = पूर्णांक_mode;
	चयन (p_hwfn->cdev->पूर्णांक_mode) अणु
	हाल QED_INT_MODE_INTA:
		igu_pf_conf |= IGU_PF_CONF_INT_LINE_EN;
		igu_pf_conf |= IGU_PF_CONF_SINGLE_ISR_EN;
		अवरोध;

	हाल QED_INT_MODE_MSI:
		igu_pf_conf |= IGU_PF_CONF_MSI_MSIX_EN;
		igu_pf_conf |= IGU_PF_CONF_SINGLE_ISR_EN;
		अवरोध;

	हाल QED_INT_MODE_MSIX:
		igu_pf_conf |= IGU_PF_CONF_MSI_MSIX_EN;
		अवरोध;
	हाल QED_INT_MODE_POLL:
		अवरोध;
	पूर्ण

	qed_wr(p_hwfn, p_ptt, IGU_REG_PF_CONFIGURATION, igu_pf_conf);
पूर्ण

अटल व्योम qed_पूर्णांक_igu_enable_attn(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt)
अणु

	/* Configure AEU संकेत change to produce attentions */
	qed_wr(p_hwfn, p_ptt, IGU_REG_ATTENTION_ENABLE, 0);
	qed_wr(p_hwfn, p_ptt, IGU_REG_LEADING_EDGE_LATCH, 0xfff);
	qed_wr(p_hwfn, p_ptt, IGU_REG_TRAILING_EDGE_LATCH, 0xfff);
	qed_wr(p_hwfn, p_ptt, IGU_REG_ATTENTION_ENABLE, 0xfff);

	/* Unmask AEU संकेतs toward IGU */
	qed_wr(p_hwfn, p_ptt, MISC_REG_AEU_MASK_ATTN_IGU, 0xff);
पूर्ण

पूर्णांक
qed_पूर्णांक_igu_enable(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt, क्रमागत qed_पूर्णांक_mode पूर्णांक_mode)
अणु
	पूर्णांक rc = 0;

	qed_पूर्णांक_igu_enable_attn(p_hwfn, p_ptt);

	अगर ((पूर्णांक_mode != QED_INT_MODE_INTA) || IS_LEAD_HWFN(p_hwfn)) अणु
		rc = qed_slowpath_irq_req(p_hwfn);
		अगर (rc) अणु
			DP_NOTICE(p_hwfn, "Slowpath IRQ request failed\n");
			वापस -EINVAL;
		पूर्ण
		p_hwfn->b_पूर्णांक_requested = true;
	पूर्ण
	/* Enable पूर्णांकerrupt Generation */
	qed_पूर्णांक_igu_enable_पूर्णांक(p_hwfn, p_ptt, पूर्णांक_mode);
	p_hwfn->b_पूर्णांक_enabled = 1;

	वापस rc;
पूर्ण

व्योम qed_पूर्णांक_igu_disable_पूर्णांक(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	p_hwfn->b_पूर्णांक_enabled = 0;

	अगर (IS_VF(p_hwfn->cdev))
		वापस;

	qed_wr(p_hwfn, p_ptt, IGU_REG_PF_CONFIGURATION, 0);
पूर्ण

#घोषणा IGU_CLEANUP_SLEEP_LENGTH                (1000)
अटल व्योम qed_पूर्णांक_igu_cleanup_sb(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   u16 igu_sb_id,
				   bool cleanup_set, u16 opaque_fid)
अणु
	u32 cmd_ctrl = 0, val = 0, sb_bit = 0, sb_bit_addr = 0, data = 0;
	u32 pxp_addr = IGU_CMD_INT_ACK_BASE + igu_sb_id;
	u32 sleep_cnt = IGU_CLEANUP_SLEEP_LENGTH;

	/* Set the data field */
	SET_FIELD(data, IGU_CLEANUP_CLEANUP_SET, cleanup_set ? 1 : 0);
	SET_FIELD(data, IGU_CLEANUP_CLEANUP_TYPE, 0);
	SET_FIELD(data, IGU_CLEANUP_COMMAND_TYPE, IGU_COMMAND_TYPE_SET);

	/* Set the control रेजिस्टर */
	SET_FIELD(cmd_ctrl, IGU_CTRL_REG_PXP_ADDR, pxp_addr);
	SET_FIELD(cmd_ctrl, IGU_CTRL_REG_FID, opaque_fid);
	SET_FIELD(cmd_ctrl, IGU_CTRL_REG_TYPE, IGU_CTRL_CMD_TYPE_WR);

	qed_wr(p_hwfn, p_ptt, IGU_REG_COMMAND_REG_32LSB_DATA, data);

	barrier();

	qed_wr(p_hwfn, p_ptt, IGU_REG_COMMAND_REG_CTRL, cmd_ctrl);

	/* calculate where to पढ़ो the status bit from */
	sb_bit = 1 << (igu_sb_id % 32);
	sb_bit_addr = igu_sb_id / 32 * माप(u32);

	sb_bit_addr += IGU_REG_CLEANUP_STATUS_0;

	/* Now रुको क्रम the command to complete */
	करो अणु
		val = qed_rd(p_hwfn, p_ptt, sb_bit_addr);

		अगर ((val & sb_bit) == (cleanup_set ? sb_bit : 0))
			अवरोध;

		usleep_range(5000, 10000);
	पूर्ण जबतक (--sleep_cnt);

	अगर (!sleep_cnt)
		DP_NOTICE(p_hwfn,
			  "Timeout waiting for clear status 0x%08x [for sb %d]\n",
			  val, igu_sb_id);
पूर्ण

व्योम qed_पूर्णांक_igu_init_pure_rt_single(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     u16 igu_sb_id, u16 opaque, bool b_set)
अणु
	काष्ठा qed_igu_block *p_block;
	पूर्णांक pi, i;

	p_block = &p_hwfn->hw_info.p_igu_info->entry[igu_sb_id];
	DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
		   "Cleaning SB [%04x]: func_id= %d is_pf = %d vector_num = 0x%0x\n",
		   igu_sb_id,
		   p_block->function_id,
		   p_block->is_pf, p_block->vector_number);

	/* Set */
	अगर (b_set)
		qed_पूर्णांक_igu_cleanup_sb(p_hwfn, p_ptt, igu_sb_id, 1, opaque);

	/* Clear */
	qed_पूर्णांक_igu_cleanup_sb(p_hwfn, p_ptt, igu_sb_id, 0, opaque);

	/* Wait क्रम the IGU SB to cleanup */
	क्रम (i = 0; i < IGU_CLEANUP_SLEEP_LENGTH; i++) अणु
		u32 val;

		val = qed_rd(p_hwfn, p_ptt,
			     IGU_REG_WRITE_DONE_PENDING +
			     ((igu_sb_id / 32) * 4));
		अगर (val & BIT((igu_sb_id % 32)))
			usleep_range(10, 20);
		अन्यथा
			अवरोध;
	पूर्ण
	अगर (i == IGU_CLEANUP_SLEEP_LENGTH)
		DP_NOTICE(p_hwfn,
			  "Failed SB[0x%08x] still appearing in WRITE_DONE_PENDING\n",
			  igu_sb_id);

	/* Clear the CAU क्रम the SB */
	क्रम (pi = 0; pi < 12; pi++)
		qed_wr(p_hwfn, p_ptt,
		       CAU_REG_PI_MEMORY + (igu_sb_id * 12 + pi) * 4, 0);
पूर्ण

व्योम qed_पूर्णांक_igu_init_pure_rt(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      bool b_set, bool b_slowpath)
अणु
	काष्ठा qed_igu_info *p_info = p_hwfn->hw_info.p_igu_info;
	काष्ठा qed_igu_block *p_block;
	u16 igu_sb_id = 0;
	u32 val = 0;

	val = qed_rd(p_hwfn, p_ptt, IGU_REG_BLOCK_CONFIGURATION);
	val |= IGU_REG_BLOCK_CONFIGURATION_VF_CLEANUP_EN;
	val &= ~IGU_REG_BLOCK_CONFIGURATION_PXP_TPH_INTERFACE_EN;
	qed_wr(p_hwfn, p_ptt, IGU_REG_BLOCK_CONFIGURATION, val);

	क्रम (igu_sb_id = 0;
	     igu_sb_id < QED_MAPPING_MEMORY_SIZE(p_hwfn->cdev); igu_sb_id++) अणु
		p_block = &p_info->entry[igu_sb_id];

		अगर (!(p_block->status & QED_IGU_STATUS_VALID) ||
		    !p_block->is_pf ||
		    (p_block->status & QED_IGU_STATUS_DSB))
			जारी;

		qed_पूर्णांक_igu_init_pure_rt_single(p_hwfn, p_ptt, igu_sb_id,
						p_hwfn->hw_info.opaque_fid,
						b_set);
	पूर्ण

	अगर (b_slowpath)
		qed_पूर्णांक_igu_init_pure_rt_single(p_hwfn, p_ptt,
						p_info->igu_dsb_id,
						p_hwfn->hw_info.opaque_fid,
						b_set);
पूर्ण

पूर्णांक qed_पूर्णांक_igu_reset_cam(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_igu_info *p_info = p_hwfn->hw_info.p_igu_info;
	काष्ठा qed_igu_block *p_block;
	पूर्णांक pf_sbs, vf_sbs;
	u16 igu_sb_id;
	u32 val, rval;

	अगर (!RESC_NUM(p_hwfn, QED_SB)) अणु
		p_info->b_allow_pf_vf_change = false;
	पूर्ण अन्यथा अणु
		/* Use the numbers the MFW have provided -
		 * करोn't क्रमget MFW accounts क्रम the शेष SB as well.
		 */
		p_info->b_allow_pf_vf_change = true;

		अगर (p_info->usage.cnt != RESC_NUM(p_hwfn, QED_SB) - 1) अणु
			DP_INFO(p_hwfn,
				"MFW notifies of 0x%04x PF SBs; IGU indicates of only 0x%04x\n",
				RESC_NUM(p_hwfn, QED_SB) - 1,
				p_info->usage.cnt);
			p_info->usage.cnt = RESC_NUM(p_hwfn, QED_SB) - 1;
		पूर्ण

		अगर (IS_PF_SRIOV(p_hwfn)) अणु
			u16 vfs = p_hwfn->cdev->p_iov_info->total_vfs;

			अगर (vfs != p_info->usage.iov_cnt)
				DP_VERBOSE(p_hwfn,
					   NETIF_MSG_INTR,
					   "0x%04x VF SBs in IGU CAM != PCI configuration 0x%04x\n",
					   p_info->usage.iov_cnt, vfs);

			/* At this poपूर्णांक we know how many SBs we have totally
			 * in IGU + number of PF SBs. So we can validate that
			 * we'd have sufficient क्रम VF.
			 */
			अगर (vfs > p_info->usage.मुक्त_cnt +
			    p_info->usage.मुक्त_cnt_iov - p_info->usage.cnt) अणु
				DP_NOTICE(p_hwfn,
					  "Not enough SBs for VFs - 0x%04x SBs, from which %04x PFs and %04x are required\n",
					  p_info->usage.मुक्त_cnt +
					  p_info->usage.मुक्त_cnt_iov,
					  p_info->usage.cnt, vfs);
				वापस -EINVAL;
			पूर्ण

			/* Currently cap the number of VFs SBs by the
			 * number of VFs.
			 */
			p_info->usage.iov_cnt = vfs;
		पूर्ण
	पूर्ण

	/* Mark all SBs as मुक्त, now in the right PF/VFs भागision */
	p_info->usage.मुक्त_cnt = p_info->usage.cnt;
	p_info->usage.मुक्त_cnt_iov = p_info->usage.iov_cnt;
	p_info->usage.orig = p_info->usage.cnt;
	p_info->usage.iov_orig = p_info->usage.iov_cnt;

	/* We now proceed to re-configure the IGU cam to reflect the initial
	 * configuration. We can start with the Default SB.
	 */
	pf_sbs = p_info->usage.cnt;
	vf_sbs = p_info->usage.iov_cnt;

	क्रम (igu_sb_id = p_info->igu_dsb_id;
	     igu_sb_id < QED_MAPPING_MEMORY_SIZE(p_hwfn->cdev); igu_sb_id++) अणु
		p_block = &p_info->entry[igu_sb_id];
		val = 0;

		अगर (!(p_block->status & QED_IGU_STATUS_VALID))
			जारी;

		अगर (p_block->status & QED_IGU_STATUS_DSB) अणु
			p_block->function_id = p_hwfn->rel_pf_id;
			p_block->is_pf = 1;
			p_block->vector_number = 0;
			p_block->status = QED_IGU_STATUS_VALID |
					  QED_IGU_STATUS_PF |
					  QED_IGU_STATUS_DSB;
		पूर्ण अन्यथा अगर (pf_sbs) अणु
			pf_sbs--;
			p_block->function_id = p_hwfn->rel_pf_id;
			p_block->is_pf = 1;
			p_block->vector_number = p_info->usage.cnt - pf_sbs;
			p_block->status = QED_IGU_STATUS_VALID |
					  QED_IGU_STATUS_PF |
					  QED_IGU_STATUS_FREE;
		पूर्ण अन्यथा अगर (vf_sbs) अणु
			p_block->function_id =
			    p_hwfn->cdev->p_iov_info->first_vf_in_pf +
			    p_info->usage.iov_cnt - vf_sbs;
			p_block->is_pf = 0;
			p_block->vector_number = 0;
			p_block->status = QED_IGU_STATUS_VALID |
					  QED_IGU_STATUS_FREE;
			vf_sbs--;
		पूर्ण अन्यथा अणु
			p_block->function_id = 0;
			p_block->is_pf = 0;
			p_block->vector_number = 0;
		पूर्ण

		SET_FIELD(val, IGU_MAPPING_LINE_FUNCTION_NUMBER,
			  p_block->function_id);
		SET_FIELD(val, IGU_MAPPING_LINE_PF_VALID, p_block->is_pf);
		SET_FIELD(val, IGU_MAPPING_LINE_VECTOR_NUMBER,
			  p_block->vector_number);

		/* VF entries would be enabled when VF is initializaed */
		SET_FIELD(val, IGU_MAPPING_LINE_VALID, p_block->is_pf);

		rval = qed_rd(p_hwfn, p_ptt,
			      IGU_REG_MAPPING_MEMORY + माप(u32) * igu_sb_id);

		अगर (rval != val) अणु
			qed_wr(p_hwfn, p_ptt,
			       IGU_REG_MAPPING_MEMORY +
			       माप(u32) * igu_sb_id, val);

			DP_VERBOSE(p_hwfn,
				   NETIF_MSG_INTR,
				   "IGU reset: [SB 0x%04x] func_id = %d is_pf = %d vector_num = 0x%x [%08x -> %08x]\n",
				   igu_sb_id,
				   p_block->function_id,
				   p_block->is_pf,
				   p_block->vector_number, rval, val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_पूर्णांक_igu_पढ़ो_cam_block(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt, u16 igu_sb_id)
अणु
	u32 val = qed_rd(p_hwfn, p_ptt,
			 IGU_REG_MAPPING_MEMORY + माप(u32) * igu_sb_id);
	काष्ठा qed_igu_block *p_block;

	p_block = &p_hwfn->hw_info.p_igu_info->entry[igu_sb_id];

	/* Fill the block inक्रमmation */
	p_block->function_id = GET_FIELD(val, IGU_MAPPING_LINE_FUNCTION_NUMBER);
	p_block->is_pf = GET_FIELD(val, IGU_MAPPING_LINE_PF_VALID);
	p_block->vector_number = GET_FIELD(val, IGU_MAPPING_LINE_VECTOR_NUMBER);
	p_block->igu_sb_id = igu_sb_id;
पूर्ण

पूर्णांक qed_पूर्णांक_igu_पढ़ो_cam(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_igu_info *p_igu_info;
	काष्ठा qed_igu_block *p_block;
	u32 min_vf = 0, max_vf = 0;
	u16 igu_sb_id;

	p_hwfn->hw_info.p_igu_info = kzalloc(माप(*p_igu_info), GFP_KERNEL);
	अगर (!p_hwfn->hw_info.p_igu_info)
		वापस -ENOMEM;

	p_igu_info = p_hwfn->hw_info.p_igu_info;

	/* Distinguish between existent and non-existent शेष SB */
	p_igu_info->igu_dsb_id = QED_SB_INVALID_IDX;

	/* Find the range of VF ids whose SB beदीर्घ to this PF */
	अगर (p_hwfn->cdev->p_iov_info) अणु
		काष्ठा qed_hw_sriov_info *p_iov = p_hwfn->cdev->p_iov_info;

		min_vf	= p_iov->first_vf_in_pf;
		max_vf	= p_iov->first_vf_in_pf + p_iov->total_vfs;
	पूर्ण

	क्रम (igu_sb_id = 0;
	     igu_sb_id < QED_MAPPING_MEMORY_SIZE(p_hwfn->cdev); igu_sb_id++) अणु
		/* Read current entry; Notice it might not beदीर्घ to this PF */
		qed_पूर्णांक_igu_पढ़ो_cam_block(p_hwfn, p_ptt, igu_sb_id);
		p_block = &p_igu_info->entry[igu_sb_id];

		अगर ((p_block->is_pf) &&
		    (p_block->function_id == p_hwfn->rel_pf_id)) अणु
			p_block->status = QED_IGU_STATUS_PF |
					  QED_IGU_STATUS_VALID |
					  QED_IGU_STATUS_FREE;

			अगर (p_igu_info->igu_dsb_id != QED_SB_INVALID_IDX)
				p_igu_info->usage.cnt++;
		पूर्ण अन्यथा अगर (!(p_block->is_pf) &&
			   (p_block->function_id >= min_vf) &&
			   (p_block->function_id < max_vf)) अणु
			/* Available क्रम VFs of this PF */
			p_block->status = QED_IGU_STATUS_VALID |
					  QED_IGU_STATUS_FREE;

			अगर (p_igu_info->igu_dsb_id != QED_SB_INVALID_IDX)
				p_igu_info->usage.iov_cnt++;
		पूर्ण

		/* Mark the First entry beदीर्घing to the PF or its VFs
		 * as the शेष SB [we'll reset IGU prior to first usage].
		 */
		अगर ((p_block->status & QED_IGU_STATUS_VALID) &&
		    (p_igu_info->igu_dsb_id == QED_SB_INVALID_IDX)) अणु
			p_igu_info->igu_dsb_id = igu_sb_id;
			p_block->status |= QED_IGU_STATUS_DSB;
		पूर्ण

		/* limit number of prपूर्णांकs by having each PF prपूर्णांक only its
		 * entries with the exception of PF0 which would prपूर्णांक
		 * everything.
		 */
		अगर ((p_block->status & QED_IGU_STATUS_VALID) ||
		    (p_hwfn->असल_pf_id == 0)) अणु
			DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
				   "IGU_BLOCK: [SB 0x%04x] func_id = %d is_pf = %d vector_num = 0x%x\n",
				   igu_sb_id, p_block->function_id,
				   p_block->is_pf, p_block->vector_number);
		पूर्ण
	पूर्ण

	अगर (p_igu_info->igu_dsb_id == QED_SB_INVALID_IDX) अणु
		DP_NOTICE(p_hwfn,
			  "IGU CAM returned invalid values igu_dsb_id=0x%x\n",
			  p_igu_info->igu_dsb_id);
		वापस -EINVAL;
	पूर्ण

	/* All non शेष SB are considered मुक्त at this poपूर्णांक */
	p_igu_info->usage.मुक्त_cnt = p_igu_info->usage.cnt;
	p_igu_info->usage.मुक्त_cnt_iov = p_igu_info->usage.iov_cnt;

	DP_VERBOSE(p_hwfn, NETIF_MSG_INTR,
		   "igu_dsb_id=0x%x, num Free SBs - PF: %04x VF: %04x [might change after resource allocation]\n",
		   p_igu_info->igu_dsb_id,
		   p_igu_info->usage.cnt, p_igu_info->usage.iov_cnt);

	वापस 0;
पूर्ण

/**
 * qed_पूर्णांक_igu_init_rt() - Initialize IGU runसमय रेजिस्टरs.
 *
 * @p_hwfn: HW device data.
 */
व्योम qed_पूर्णांक_igu_init_rt(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 igu_pf_conf = IGU_PF_CONF_FUNC_EN;

	STORE_RT_REG(p_hwfn, IGU_REG_PF_CONFIGURATION_RT_OFFSET, igu_pf_conf);
पूर्ण

u64 qed_पूर्णांक_igu_पढ़ो_sisr_reg(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 lsb_igu_cmd_addr = IGU_REG_SISR_MDPC_WMASK_LSB_UPPER -
			       IGU_CMD_INT_ACK_BASE;
	u32 msb_igu_cmd_addr = IGU_REG_SISR_MDPC_WMASK_MSB_UPPER -
			       IGU_CMD_INT_ACK_BASE;
	u32 पूर्णांकr_status_hi = 0, पूर्णांकr_status_lo = 0;
	u64 पूर्णांकr_status = 0;

	पूर्णांकr_status_lo = REG_RD(p_hwfn,
				GTT_BAR0_MAP_REG_IGU_CMD +
				lsb_igu_cmd_addr * 8);
	पूर्णांकr_status_hi = REG_RD(p_hwfn,
				GTT_BAR0_MAP_REG_IGU_CMD +
				msb_igu_cmd_addr * 8);
	पूर्णांकr_status = ((u64)पूर्णांकr_status_hi << 32) + (u64)पूर्णांकr_status_lo;

	वापस पूर्णांकr_status;
पूर्ण

अटल व्योम qed_पूर्णांक_sp_dpc_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
	tasklet_setup(&p_hwfn->sp_dpc, qed_पूर्णांक_sp_dpc);
	p_hwfn->b_sp_dpc_enabled = true;
पूर्ण

पूर्णांक qed_पूर्णांक_alloc(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	पूर्णांक rc = 0;

	rc = qed_पूर्णांक_sp_sb_alloc(p_hwfn, p_ptt);
	अगर (rc)
		वापस rc;

	rc = qed_पूर्णांक_sb_attn_alloc(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

व्योम qed_पूर्णांक_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	qed_पूर्णांक_sp_sb_मुक्त(p_hwfn);
	qed_पूर्णांक_sb_attn_मुक्त(p_hwfn);
पूर्ण

व्योम qed_पूर्णांक_setup(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	qed_पूर्णांक_sb_setup(p_hwfn, p_ptt, &p_hwfn->p_sp_sb->sb_info);
	qed_पूर्णांक_sb_attn_setup(p_hwfn, p_ptt);
	qed_पूर्णांक_sp_dpc_setup(p_hwfn);
पूर्ण

व्योम qed_पूर्णांक_get_num_sbs(काष्ठा qed_hwfn	*p_hwfn,
			 काष्ठा qed_sb_cnt_info *p_sb_cnt_info)
अणु
	काष्ठा qed_igu_info *info = p_hwfn->hw_info.p_igu_info;

	अगर (!info || !p_sb_cnt_info)
		वापस;

	स_नकल(p_sb_cnt_info, &info->usage, माप(*p_sb_cnt_info));
पूर्ण

व्योम qed_पूर्णांक_disable_post_isr_release(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i)
		cdev->hwfns[i].b_पूर्णांक_requested = false;
पूर्ण

व्योम qed_पूर्णांक_attn_clr_enable(काष्ठा qed_dev *cdev, bool clr_enable)
अणु
	cdev->attn_clr_en = clr_enable;
पूर्ण

पूर्णांक qed_पूर्णांक_set_समयr_res(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			  u8 समयr_res, u16 sb_id, bool tx)
अणु
	काष्ठा cau_sb_entry sb_entry;
	u32 params;
	पूर्णांक rc;

	अगर (!p_hwfn->hw_init_करोne) अणु
		DP_ERR(p_hwfn, "hardware not initialized yet\n");
		वापस -EINVAL;
	पूर्ण

	rc = qed_dmae_grc2host(p_hwfn, p_ptt, CAU_REG_SB_VAR_MEMORY +
			       sb_id * माप(u64),
			       (u64)(uपूर्णांकptr_t)&sb_entry, 2, शून्य);
	अगर (rc) अणु
		DP_ERR(p_hwfn, "dmae_grc2host failed %d\n", rc);
		वापस rc;
	पूर्ण

	params = le32_to_cpu(sb_entry.params);

	अगर (tx)
		SET_FIELD(params, CAU_SB_ENTRY_TIMER_RES1, समयr_res);
	अन्यथा
		SET_FIELD(params, CAU_SB_ENTRY_TIMER_RES0, समयr_res);

	sb_entry.params = cpu_to_le32(params);

	rc = qed_dmae_host2grc(p_hwfn, p_ptt,
			       (u64)(uपूर्णांकptr_t)&sb_entry,
			       CAU_REG_SB_VAR_MEMORY +
			       sb_id * माप(u64), 2, शून्य);
	अगर (rc) अणु
		DP_ERR(p_hwfn, "dmae_host2grc failed %d\n", rc);
		वापस rc;
	पूर्ण

	वापस rc;
पूर्ण
