<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश "bnx2x.h"

#घोषणा NA 0xCD

#घोषणा IDLE_CHK_E1			0x01
#घोषणा IDLE_CHK_E1H			0x02
#घोषणा IDLE_CHK_E2			0x04
#घोषणा IDLE_CHK_E3A0			0x08
#घोषणा IDLE_CHK_E3B0			0x10

#घोषणा IDLE_CHK_ERROR			1
#घोषणा IDLE_CHK_ERROR_NO_TRAFFIC	2
#घोषणा IDLE_CHK_WARNING		3

#घोषणा MAX_FAIL_MSG 256

/* statistics and error reporting */
अटल पूर्णांक idle_chk_errors, idle_chk_warnings;

/* masks क्रम all chip types */
अटल पूर्णांक is_e1, is_e1h, is_e2, is_e3a0, is_e3b0;

/* काष्ठा क्रम the argument list क्रम a predicate in the self test databasei */
काष्ठा st_pred_args अणु
	u32 val1; /* value पढ़ो from first रेजिस्टर */
	u32 val2; /* value पढ़ो from second रेजिस्टर, अगर applicable */
	u32 imm1; /* 1st value in predicate condition, left-to-right */
	u32 imm2; /* 2nd value in predicate condition, left-to-right */
	u32 imm3; /* 3rd value in predicate condition, left-to-right */
	u32 imm4; /* 4th value in predicate condition, left-to-right */
पूर्ण;

/* काष्ठा representing self test record - a single test */
काष्ठा st_record अणु
	u8 chip_mask;
	u8 macro;
	u32 reg1;
	u32 reg2;
	u16 loop;
	u16 incr;
	पूर्णांक (*bnx2x_predicate)(काष्ठा st_pred_args *pred_args);
	u32 reg3;
	u8 severity;
	अक्षर *fail_msg;
	काष्ठा st_pred_args pred_args;
पूर्ण;

/* predicates क्रम self test */
अटल पूर्णांक peq(काष्ठा st_pred_args *args)
अणु
	वापस (args->val1 == args->imm1);
पूर्ण

अटल पूर्णांक pneq(काष्ठा st_pred_args *args)
अणु
	वापस (args->val1 != args->imm1);
पूर्ण

अटल पूर्णांक pand_neq(काष्ठा st_pred_args *args)
अणु
	वापस ((args->val1 & args->imm1) != args->imm2);
पूर्ण

अटल पूर्णांक pand_neq_x2(काष्ठा st_pred_args *args)
अणु
	वापस (((args->val1 & args->imm1) != args->imm2) &&
		((args->val1 & args->imm3) != args->imm4));
पूर्ण

अटल पूर्णांक pneq_err(काष्ठा st_pred_args *args)
अणु
	वापस ((args->val1 != args->imm1) && (idle_chk_errors > args->imm2));
पूर्ण

अटल पूर्णांक pgt(काष्ठा st_pred_args *args)
अणु
	वापस (args->val1 > args->imm1);
पूर्ण

अटल पूर्णांक pneq_r2(काष्ठा st_pred_args *args)
अणु
	वापस (args->val1 != args->val2);
पूर्ण

अटल पूर्णांक plt_sub_r2(काष्ठा st_pred_args *args)
अणु
	वापस (args->val1 < (args->val2 - args->imm1));
पूर्ण

अटल पूर्णांक pne_sub_r2(काष्ठा st_pred_args *args)
अणु
	वापस (args->val1 != (args->val2 - args->imm1));
पूर्ण

अटल पूर्णांक prsh_and_neq(काष्ठा st_pred_args *args)
अणु
	वापस (((args->val1 >> args->imm1) & args->imm2) != args->imm3);
पूर्ण

अटल पूर्णांक peq_neq_r2(काष्ठा st_pred_args *args)
अणु
	वापस ((args->val1 == args->imm1) && (args->val2 != args->imm2));
पूर्ण

अटल पूर्णांक peq_neq_neq_r2(काष्ठा st_pred_args *args)
अणु
	वापस ((args->val1 == args->imm1) && (args->val2 != args->imm2) &&
		(args->val2 != args->imm3));
पूर्ण

/* काष्ठा holding the database of self test checks (रेजिस्टरs and predicates) */
/* lines start from 2 since line 1 is heading in csv */
#घोषणा ST_DB_LINES 468
अटल काष्ठा st_record st_database[ST_DB_LINES] = अणु
/*line 2*/अणु(0x3), 1, 0x2114,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"PCIE: ucorr_err_status is not 0",
	अणुNA, NA, 0x0FF010, 0, NA, NAपूर्ण पूर्ण,

/*line 3*/अणु(0x3), 1, 0x2114,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"PCIE: ucorr_err_status - Unsupported request error",
	अणुNA, NA, 0x100000, 0, NA, NAपूर्ण पूर्ण,

/*line 4*/अणु(0x3), 1, 0x2120,
	NA, 1, 0, pand_neq_x2,
	NA, IDLE_CHK_WARNING,
	"PCIE: corr_err_status is not 0x2000",
	अणुNA, NA, 0x31C1, 0x2000, 0x31C1, 0पूर्ण पूर्ण,

/*line 5*/अणु(0x3), 1, 0x2814,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"PCIE: attentions register is not 0x40100",
	अणुNA, NA, ~0x40100, 0, NA, NAपूर्ण पूर्ण,

/*line 6*/अणु(0x2), 1, 0x281c,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"PCIE: attentions register is not 0x40040100",
	अणुNA, NA, ~0x40040100, 0, NA, NAपूर्ण पूर्ण,

/*line 7*/अणु(0x2), 1, 0x2820,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"PCIE: attentions register is not 0x40040100",
	अणुNA, NA, ~0x40040100, 0, NA, NAपूर्ण पूर्ण,

/*line 8*/अणु(0x3), 1, PXP2_REG_PGL_EXP_ROM2,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: There are outstanding read requests. Not all completios have arrived for read requests on tags that are marked with 0",
	अणुNA, NA, 0xffffffff, NA, NA, NAपूर्ण पूर्ण,

/*line 9*/अणु(0x3), 2, 0x212c,
	NA, 4, 4, pneq_err,
	NA, IDLE_CHK_WARNING,
	"PCIE: error packet header is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 10*/अणु(0x1C), 1, 0x2104,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"PCIE: ucorr_err_status is not 0",
	अणुNA, NA, 0x0FD010, 0, NA, NAपूर्ण पूर्ण,

/*line 11*/अणु(0x1C), 1, 0x2104,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"PCIE: ucorr_err_status - Unsupported request error",
	अणुNA, NA, 0x100000, 0, NA, NAपूर्ण पूर्ण,

/*line 12*/अणु(0x1C), 1, 0x2104,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"PCIE: ucorr_err_status - Flow Control Protocol Error",
	अणुNA, NA, 0x2000, 0, NA, NAपूर्ण पूर्ण,

/*line 13*/अणु(0x1C), 1, 0x2110,
	NA, 1, 0, pand_neq_x2,
	NA, IDLE_CHK_WARNING,
	"PCIE: corr_err_status is not 0x2000",
	अणुNA, NA, 0x31C1, 0x2000, 0x31C1, 0पूर्ण पूर्ण,

/*line 14*/अणु(0x1C), 1, 0x2814,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"PCIE: TTX_BRIDGE_FORWARD_ERR - Received master request while BME was 0",
	अणुNA, NA, 0x2000000, 0, NA, NAपूर्ण पूर्ण,

/*line 15*/अणु(0x1C), 1, 0x2814,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"PCIE: Func 0 1: attentions register is not 0x2040902",
	अणुNA, NA, ~0x2040902, 0, NA, NAपूर्ण पूर्ण,

/*line 16*/अणु(0x1C), 1, 0x2854,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"PCIE: Func 2 3 4: attentions register is not 0x10240902",
	अणुNA, NA, ~0x10240902, 0, NA, NAपूर्ण पूर्ण,

/*line 17*/अणु(0x1C), 1, 0x285c,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"PCIE: Func 5 6 7: attentions register is not 0x10240902",
	अणुNA, NA, ~0x10240902, 0, NA, NAपूर्ण पूर्ण,

/*line 18*/अणु(0x18), 1, 0x3040,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"PCIE: Overflow in DLP2TLP buffer",
	अणुNA, NA, 0x2, 0, NA, NAपूर्ण पूर्ण,

/*line 19*/अणु(0x1C), 1, PXP2_REG_PGL_EXP_ROM2,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: There are outstanding read requests for tags 0-31. Not all completios have arrived for read requests on tags that are marked with 0",
	अणुNA, NA, 0xffffffff, NA, NA, NAपूर्ण पूर्ण,

/*line 20*/अणु(0x1C), 2, 0x211c,
	NA, 4, 4, pneq_err,
	NA, IDLE_CHK_WARNING,
	"PCIE: error packet header is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 21*/अणु(0x1C), 1, PGLUE_B_REG_INCORRECT_RCV_DETAILS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PGLUE_B: Packet received from PCIe not according to the rules",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 22*/अणु(0x1C), 1, PGLUE_B_REG_WAS_ERROR_VF_31_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: was_error for VFs 0-31 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 23*/अणु(0x1C), 1, PGLUE_B_REG_WAS_ERROR_VF_63_32,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: was_error for VFs 32-63 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 24*/अणु(0x1C), 1, PGLUE_B_REG_WAS_ERROR_VF_95_64,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: was_error for VFs 64-95 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 25*/अणु(0x1C), 1, PGLUE_B_REG_WAS_ERROR_VF_127_96,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: was_error for VFs 96-127 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 26*/अणु(0x1C), 1, PGLUE_B_REG_WAS_ERROR_PF_7_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: was_error for PFs 0-7 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 27*/अणु(0x1C), 1, PGLUE_B_REG_RX_ERR_DETAILS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Completion received with error. (2:0) - PFID. (3) - VF_VALID. (9:4) - VFID. (11:10) - Error code : 0 - Completion Timeout; 1 - Unsupported Request; 2 - Completer Abort. (12) - valid bit",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 28*/अणु(0x1C), 1, PGLUE_B_REG_RX_TCPL_ERR_DETAILS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: ATS TCPL received with error. (2:0) - PFID. (3) - VF_VALID. (9:4) - VFID. (11:10) - Error code : 0 - Completion Timeout ; 1 - Unsupported Request; 2 - Completer Abort. (16:12) - OTB Entry ID. (17) - valid bit",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 29*/अणु(0x1C), 1, PGLUE_B_REG_TX_ERR_WR_ADD_31_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Error in master write. Address(31:0) is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 30*/अणु(0x1C), 1, PGLUE_B_REG_TX_ERR_WR_ADD_63_32,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Error in master write. Address(63:32) is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 31*/अणु(0x1C), 1, PGLUE_B_REG_TX_ERR_WR_DETAILS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Error in master write. Error details register is not 0. (4:0) VQID. (23:21) - PFID. (24) - VF_VALID. (30:25) - VFID",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 32*/अणु(0x1C), 1, PGLUE_B_REG_TX_ERR_WR_DETAILS2,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Error in master write. Error details 2nd register is not 0. (21) - was_error set; (22) - BME cleared; (23) - FID_enable cleared; (24) - VF with parent PF FLR_request or IOV_disable_request",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 33*/अणु(0x1C), 1, PGLUE_B_REG_TX_ERR_RD_ADD_31_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE: Error in master read address(31:0) is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 34*/अणु(0x1C), 1, PGLUE_B_REG_TX_ERR_RD_ADD_63_32,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Error in master read address(63:32) is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 35*/अणु(0x1C), 1, PGLUE_B_REG_TX_ERR_RD_DETAILS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Error in master read Error details register is not 0. (4:0) VQID. (23:21) - PFID. (24) - VF_VALID. (30:25) - VFID",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 36*/अणु(0x1C), 1, PGLUE_B_REG_TX_ERR_RD_DETAILS2,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Error in master read Error details 2nd register is not 0. (21) - was_error set; (22) - BME cleared; (23) - FID_enable cleared; (24) - VF with parent PF FLR_request or IOV_disable_request",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 37*/अणु(0x1C), 1, PGLUE_B_REG_VF_LENGTH_VIOLATION_DETAILS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Target VF length violation access",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 38*/अणु(0x1C), 1, PGLUE_B_REG_VF_GRC_SPACE_VIOLATION_DETAILS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Target VF GRC space access failed permission check",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 39*/अणु(0x1C), 1, PGLUE_B_REG_TAGS_63_32,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: There are outstanding read requests for tags 32-63. Not all completios have arrived for read requests on tags that are marked with 0",
	अणुNA, NA, 0xffffffff, NA, NA, NAपूर्ण पूर्ण,

/*line 40*/अणु(0x1C), 3, PXP_REG_HST_VF_DISABLED_ERROR_VALID,
	PXP_REG_HST_VF_DISABLED_ERROR_DATA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: Access to disabled VF took place",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 41*/अणु(0x1C), 1, PXP_REG_HST_PER_VIOLATION_VALID,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: Zone A permission violation occurred",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 42*/अणु(0x1C), 1, PXP_REG_HST_INCORRECT_ACCESS_VALID,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: Incorrect transaction took place",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 43*/अणु(0x1C), 1, PXP2_REG_RD_CPL_ERR_DETAILS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: Completion received with error. Error details register is not 0. (15:0) - ECHO. (28:16) - Sub Request length plus start_offset_2_0 minus 1",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 44*/अणु(0x1C), 1, PXP2_REG_RD_CPL_ERR_DETAILS2,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: Completion received with error. Error details 2nd register is not 0. (4:0) - VQ ID. (8:5) - client ID. (9) - valid bit",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 45*/अणु(0x1F), 1, PXP2_REG_RQ_VQ0_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ0 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 46*/अणु(0x1F), 1, PXP2_REG_RQ_VQ1_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ1 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 47*/अणु(0x1F), 1, PXP2_REG_RQ_VQ2_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ2 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 48*/अणु(0x1F), 1, PXP2_REG_RQ_VQ3_ENTRY_CNT,
	NA, 1, 0, pgt,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ3 is not empty",
	अणुNA, NA, 2, NA, NA, NAपूर्ण पूर्ण,

/*line 49*/अणु(0x1F), 1, PXP2_REG_RQ_VQ4_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ4 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 50*/अणु(0x1F), 1, PXP2_REG_RQ_VQ5_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ5 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 51*/अणु(0x1F), 1, PXP2_REG_RQ_VQ6_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ6 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 52*/अणु(0x1F), 1, PXP2_REG_RQ_VQ7_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ7 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 53*/अणु(0x1F), 1, PXP2_REG_RQ_VQ8_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ8 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 54*/अणु(0x1F), 1, PXP2_REG_RQ_VQ9_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ9 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 55*/अणु(0x1F), 1, PXP2_REG_RQ_VQ10_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ10 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 56*/अणु(0x1F), 1, PXP2_REG_RQ_VQ11_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ11 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 57*/अणु(0x1F), 1, PXP2_REG_RQ_VQ12_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ12 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 58*/अणु(0x1F), 1, PXP2_REG_RQ_VQ13_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ13 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 59*/अणु(0x1F), 1, PXP2_REG_RQ_VQ14_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ14 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 60*/अणु(0x1F), 1, PXP2_REG_RQ_VQ15_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ15 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 61*/अणु(0x1F), 1, PXP2_REG_RQ_VQ16_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ16 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 62*/अणु(0x1F), 1, PXP2_REG_RQ_VQ17_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ17 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 63*/अणु(0x1F), 1, PXP2_REG_RQ_VQ18_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ18 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 64*/अणु(0x1F), 1, PXP2_REG_RQ_VQ19_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ19 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 65*/अणु(0x1F), 1, PXP2_REG_RQ_VQ20_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ20 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 66*/अणु(0x1F), 1, PXP2_REG_RQ_VQ21_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ21 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 67*/अणु(0x1F), 1, PXP2_REG_RQ_VQ22_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ22 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 68*/अणु(0x1F), 1, PXP2_REG_RQ_VQ23_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ23 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 69*/अणु(0x1F), 1, PXP2_REG_RQ_VQ24_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ24 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 70*/अणु(0x1F), 1, PXP2_REG_RQ_VQ25_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ25 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 71*/अणु(0x1F), 1, PXP2_REG_RQ_VQ26_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ26 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 72*/अणु(0x1F), 1, PXP2_REG_RQ_VQ27_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ27 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 73*/अणु(0x1F), 1, PXP2_REG_RQ_VQ28_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ28 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 74*/अणु(0x1F), 1, PXP2_REG_RQ_VQ29_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ29 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 75*/अणु(0x1F), 1, PXP2_REG_RQ_VQ30_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ30 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 76*/अणु(0x1F), 1, PXP2_REG_RQ_VQ31_ENTRY_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: VQ31 is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 77*/अणु(0x1F), 1, PXP2_REG_RQ_UFIFO_NUM_OF_ENTRY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: rq_ufifo_num_of_entry is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 78*/अणु(0x1F), 1, PXP2_REG_RQ_RBC_DONE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PXP2: rq_rbc_done is not 1",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 79*/अणु(0x1F), 1, PXP2_REG_RQ_CFG_DONE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PXP2: rq_cfg_done is not 1",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 80*/अणु(0x3), 1, PXP2_REG_PSWRQ_BW_CREDIT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: rq_read_credit and rq_write_credit are not 3",
	अणुNA, NA, 0x1B, NA, NA, NAपूर्ण पूर्ण,

/*line 81*/अणु(0x1F), 1, PXP2_REG_RD_START_INIT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PXP2: rd_start_init is not 1",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 82*/अणु(0x1F), 1, PXP2_REG_RD_INIT_DONE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PXP2: rd_init_done is not 1",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 83*/अणु(0x1F), 3, PXP2_REG_RD_SR_CNT,
	PXP2_REG_RD_SR_NUM_CFG, 1, 0, pne_sub_r2,
	NA, IDLE_CHK_WARNING,
	"PXP2: rd_sr_cnt is not equal to rd_sr_num_cfg",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 84*/अणु(0x1F), 3, PXP2_REG_RD_BLK_CNT,
	PXP2_REG_RD_BLK_NUM_CFG, 1, 0, pneq_r2,
	NA, IDLE_CHK_WARNING,
	"PXP2: rd_blk_cnt is not equal to rd_blk_num_cfg",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 85*/अणु(0x1F), 3, PXP2_REG_RD_SR_CNT,
	PXP2_REG_RD_SR_NUM_CFG, 1, 0, plt_sub_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: There are more than two unused SRs",
	अणुNA, NA, 3, NA, NA, NAपूर्ण पूर्ण,

/*line 86*/अणु(0x1F), 3, PXP2_REG_RD_BLK_CNT,
	PXP2_REG_RD_BLK_NUM_CFG, 1, 0, plt_sub_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: There are more than two unused blocks",
	अणुNA, NA, 2, NA, NA, NAपूर्ण पूर्ण,

/*line 87*/अणु(0x1F), 1, PXP2_REG_RD_PORT_IS_IDLE_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: P0 All delivery ports are not idle",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 88*/अणु(0x1F), 1, PXP2_REG_RD_PORT_IS_IDLE_1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: P1 All delivery ports are not idle",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 89*/अणु(0x1F), 2, PXP2_REG_RD_ALMOST_FULL_0,
	NA, 11, 4, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: rd_almost_full is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 90*/अणु(0x1F), 1, PXP2_REG_RD_DISABLE_INPUTS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PXP2: PSWRD inputs are disabled",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 91*/अणु(0x1F), 1, PXP2_REG_HST_HEADER_FIFO_STATUS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: HST header FIFO status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 92*/अणु(0x1F), 1, PXP2_REG_HST_DATA_FIFO_STATUS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: HST data FIFO status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 93*/अणु(0x3), 1, PXP2_REG_PGL_WRITE_BLOCKED,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PXP2: pgl_write_blocked is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 94*/अणु(0x3), 1, PXP2_REG_PGL_READ_BLOCKED,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PXP2: pgl_read_blocked is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 95*/अणु(0x1C), 1, PXP2_REG_PGL_WRITE_BLOCKED,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: pgl_write_blocked is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 96*/अणु(0x1C), 1, PXP2_REG_PGL_READ_BLOCKED,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: pgl_read_blocked is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 97*/अणु(0x1F), 1, PXP2_REG_PGL_TXW_CDTS,
	NA, 1, 0, prsh_and_neq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PXP2: There is data which is ready",
	अणुNA, NA, 17, 1, 0, NAपूर्ण पूर्ण,

/*line 98*/अणु(0x1F), 1, PXP_REG_HST_ARB_IS_IDLE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: HST arbiter is not idle",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 99*/अणु(0x1F), 1, PXP_REG_HST_CLIENTS_WAITING_TO_ARB,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: HST one of the clients is waiting for delivery",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 100*/अणु(0x1E), 1, PXP_REG_HST_DISCARD_INTERNAL_WRITES_STATUS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: HST Close the gates: Discarding internal writes",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 101*/अणु(0x1E), 1, PXP_REG_HST_DISCARD_DOORBELLS_STATUS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: HST Close the gates: Discarding doorbells",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 102*/अणु(0x1C), 1, PXP2_REG_RQ_GARB,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"PXP2: PSWRQ Close the gates is asserted. Check AEU AFTER_INVERT registers for parity errors",
	अणुNA, NA, 0x1000, 0, NA, NAपूर्ण पूर्ण,

/*line 103*/अणु(0x1F), 1, DMAE_REG_GO_C0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 0 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 104*/अणु(0x1F), 1, DMAE_REG_GO_C1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 1 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 105*/अणु(0x1F), 1, DMAE_REG_GO_C2,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 2 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 106*/अणु(0x1F), 1, DMAE_REG_GO_C3,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 3 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 107*/अणु(0x1F), 1, DMAE_REG_GO_C4,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 4 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 108*/अणु(0x1F), 1, DMAE_REG_GO_C5,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 5 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 109*/अणु(0x1F), 1, DMAE_REG_GO_C6,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 6 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 110*/अणु(0x1F), 1, DMAE_REG_GO_C7,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 7 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 111*/अणु(0x1F), 1, DMAE_REG_GO_C8,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 8 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 112*/अणु(0x1F), 1, DMAE_REG_GO_C9,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 9 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 113*/अणु(0x1F), 1, DMAE_REG_GO_C10,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 10 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 114*/अणु(0x1F), 1, DMAE_REG_GO_C11,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 11 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 115*/अणु(0x1F), 1, DMAE_REG_GO_C12,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 12 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 116*/अणु(0x1F), 1, DMAE_REG_GO_C13,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 13 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 117*/अणु(0x1F), 1, DMAE_REG_GO_C14,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 14 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 118*/अणु(0x1F), 1, DMAE_REG_GO_C15,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DMAE: command 15 go is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 119*/अणु(0x1F), 1, CFC_REG_ERROR_VECTOR,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CFC: error vector is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 120*/अणु(0x1F), 1, CFC_REG_NUM_LCIDS_ARRIVING,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CFC: number of arriving LCIDs is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 121*/अणु(0x1F), 1, CFC_REG_NUM_LCIDS_ALLOC,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CFC: number of alloc LCIDs is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 122*/अणु(0x1F), 1, CFC_REG_NUM_LCIDS_LEAVING,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CFC: number of leaving LCIDs is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 123*/अणु(0x1F), 7, CFC_REG_INFO_RAM,
	CFC_REG_CID_CAM, (CFC_REG_INFO_RAM_SIZE >> 4), 16, peq_neq_neq_r2,
	CFC_REG_ACTIVITY_COUNTER, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CFC: AC is neither 0 nor 2 on connType 0 (ETH)",
	अणुNA, NA, 0, 0, 2, NAपूर्ण पूर्ण,

/*line 124*/अणु(0x1F), 7, CFC_REG_INFO_RAM,
	CFC_REG_CID_CAM, (CFC_REG_INFO_RAM_SIZE >> 4), 16, peq_neq_r2,
	CFC_REG_ACTIVITY_COUNTER, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CFC: AC is not 0 on connType 1 (TOE)",
	अणुNA, NA, 1, 0, NA, NAपूर्ण पूर्ण,

/*line 125*/अणु(0x1F), 7, CFC_REG_INFO_RAM,
	CFC_REG_CID_CAM, (CFC_REG_INFO_RAM_SIZE >> 4), 16, peq_neq_r2,
	CFC_REG_ACTIVITY_COUNTER, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CFC: AC is not 0 on connType 3 (iSCSI)",
	अणुNA, NA, 3, 0, NA, NAपूर्ण पूर्ण,

/*line 126*/अणु(0x1F), 7, CFC_REG_INFO_RAM,
	CFC_REG_CID_CAM, (CFC_REG_INFO_RAM_SIZE >> 4), 16, peq_neq_r2,
	CFC_REG_ACTIVITY_COUNTER, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CFC: AC is not 0 on connType 4 (FCoE)",
	अणुNA, NA, 4, 0, NA, NAपूर्ण पूर्ण,

/*line 127*/अणु(0x1F), 2, QM_REG_QTASKCTR_0,
	NA, 64, 4, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Queue is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 128*/अणु(0xF), 3, QM_REG_VOQCREDIT_0,
	QM_REG_VOQINITCREDIT_0, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_0, VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 129*/अणु(0xF), 3, QM_REG_VOQCREDIT_1,
	QM_REG_VOQINITCREDIT_1, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_1, VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 130*/अणु(0xF), 3, QM_REG_VOQCREDIT_4,
	QM_REG_VOQINITCREDIT_4, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_4, VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 131*/अणु(0x3), 3, QM_REG_PORT0BYTECRD,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: P0 Byte credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 132*/अणु(0x3), 3, QM_REG_PORT1BYTECRD,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: P1 Byte credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 133*/अणु(0x1F), 1, CCM_REG_CAM_OCCUP,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CCM: XX protection CAM is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 134*/अणु(0x1F), 1, TCM_REG_CAM_OCCUP,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TCM: XX protection CAM is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 135*/अणु(0x1F), 1, UCM_REG_CAM_OCCUP,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"UCM: XX protection CAM is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 136*/अणु(0x1F), 1, XCM_REG_CAM_OCCUP,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XCM: XX protection CAM is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 137*/अणु(0x1F), 1, BRB1_REG_NUM_OF_FULL_BLOCKS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"BRB1: BRB is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 138*/अणु(0x1F), 1, CSEM_REG_SLEEP_THREADS_VALID,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CSEM: There are sleeping threads",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 139*/अणु(0x1F), 1, TSEM_REG_SLEEP_THREADS_VALID,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TSEM: There are sleeping threads",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 140*/अणु(0x1F), 1, USEM_REG_SLEEP_THREADS_VALID,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"USEM: There are sleeping threads",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 141*/अणु(0x1F), 1, XSEM_REG_SLEEP_THREADS_VALID,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XSEM: There are sleeping threads",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 142*/अणु(0x1F), 1, CSEM_REG_SLOW_EXT_STORE_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CSEM: External store FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 143*/अणु(0x1F), 1, TSEM_REG_SLOW_EXT_STORE_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TSEM: External store FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 144*/अणु(0x1F), 1, USEM_REG_SLOW_EXT_STORE_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"USEM: External store FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 145*/अणु(0x1F), 1, XSEM_REG_SLOW_EXT_STORE_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XSEM: External store FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 146*/अणु(0x1F), 1, CSDM_REG_SYNC_PARSER_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CSDM: Parser serial FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 147*/अणु(0x1F), 1, TSDM_REG_SYNC_PARSER_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TSDM: Parser serial FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 148*/अणु(0x1F), 1, USDM_REG_SYNC_PARSER_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"USDM: Parser serial FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 149*/अणु(0x1F), 1, XSDM_REG_SYNC_PARSER_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XSDM: Parser serial FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 150*/अणु(0x1F), 1, CSDM_REG_SYNC_SYNC_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CSDM: Parser SYNC serial FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 151*/अणु(0x1F), 1, TSDM_REG_SYNC_SYNC_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TSDM: Parser SYNC serial FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 152*/अणु(0x1F), 1, USDM_REG_SYNC_SYNC_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"USDM: Parser SYNC serial FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 153*/अणु(0x1F), 1, XSDM_REG_SYNC_SYNC_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XSDM: Parser SYNC serial FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 154*/अणु(0x1F), 1, CSDM_REG_RSP_PXP_CTRL_RDATA_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CSDM: pxp_ctrl rd_data fifo is not empty in sdm_dma_rsp block",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 155*/अणु(0x1F), 1, TSDM_REG_RSP_PXP_CTRL_RDATA_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TSDM: pxp_ctrl rd_data fifo is not empty in sdm_dma_rsp block",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 156*/अणु(0x1F), 1, USDM_REG_RSP_PXP_CTRL_RDATA_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"USDM: pxp_ctrl rd_data fifo is not empty in sdm_dma_rsp block",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 157*/अणु(0x1F), 1, XSDM_REG_RSP_PXP_CTRL_RDATA_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XSDM: pxp_ctrl rd_data fifo is not empty in sdm_dma_rsp block",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 158*/अणु(0x1F), 1, DORQ_REG_DQ_FILL_LVLF,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DORQ: DORQ queue is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 159*/अणु(0x1F), 1, CFC_REG_CFC_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CFC: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 160*/अणु(0x1F), 1, CDU_REG_CDU_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CDU: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 161*/अणु(0x1F), 1, CCM_REG_CCM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CCM: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 162*/अणु(0x1F), 1, TCM_REG_TCM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"TCM: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 163*/अणु(0x1F), 1, UCM_REG_UCM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"UCM: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 164*/अणु(0x1F), 1, XCM_REG_XCM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 165*/अणु(0xF), 1, PBF_REG_PBF_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PBF: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 166*/अणु(0x1F), 1, TM_REG_TM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"TIMERS: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 167*/अणु(0x1F), 1, DORQ_REG_DORQ_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"DORQ: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 168*/अणु(0x1F), 1, SRC_REG_SRC_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"SRCH: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 169*/अणु(0x1F), 1, PRS_REG_PRS_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PRS: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 170*/अणु(0x1F), 1, BRB1_REG_BRB1_INT_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"BRB1: Interrupt status is not 0",
	अणुNA, NA, ~0xFC00, 0, NA, NAपूर्ण पूर्ण,

/*line 171*/अणु(0x1F), 1, GRCBASE_XPB + PB_REG_PB_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XPB: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 172*/अणु(0x1F), 1, GRCBASE_UPB + PB_REG_PB_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"UPB: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 173*/अणु(0x1), 1, PXP2_REG_PXP2_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: Interrupt status 0 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 174*/अणु(0x1E), 1, PXP2_REG_PXP2_INT_STS_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: Interrupt status 0 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 175*/अणु(0x1E), 1, PXP2_REG_PXP2_INT_STS_1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: Interrupt status 1 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 176*/अणु(0x1F), 1, QM_REG_QM_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 177*/अणु(0x1F), 1, PXP_REG_PXP_INT_STS_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: P0 Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 178*/अणु(0x1F), 1, PXP_REG_PXP_INT_STS_1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: P1 Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 179*/अणु(0x1C), 1, PGLUE_B_REG_PGLUE_B_INT_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: Interrupt status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 180*/अणु(0x1F), 1, DORQ_REG_RSPA_CRD_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DORQ: Credit to XCM is not full",
	अणुNA, NA, 2, NA, NA, NAपूर्ण पूर्ण,

/*line 181*/अणु(0x1F), 1, DORQ_REG_RSPB_CRD_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"DORQ: Credit to UCM is not full",
	अणुNA, NA, 2, NA, NA, NAपूर्ण पूर्ण,

/*line 182*/अणु(0x3), 1, QM_REG_VOQCRDERRREG,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: Credit error register is not 0 (byte or credit overflow/underflow)",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 183*/अणु(0x1F), 1, DORQ_REG_DQ_FULL_ST,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"DORQ: DORQ queue is full",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 184*/अणु(0x1F), 1, MISC_REG_AEU_AFTER_INVERT_1_FUNC_0,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"AEU: P0 AFTER_INVERT_1 is not 0",
	अणुNA, NA, ~0xCFFC, 0, NA, NAपूर्ण पूर्ण,

/*line 185*/अणु(0x1F), 1, MISC_REG_AEU_AFTER_INVERT_2_FUNC_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"AEU: P0 AFTER_INVERT_2 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 186*/अणु(0x1F), 1, MISC_REG_AEU_AFTER_INVERT_3_FUNC_0,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"AEU: P0 AFTER_INVERT_3 is not 0",
	अणुNA, NA, ~0xFFFF0000, 0, NA, NAपूर्ण पूर्ण,

/*line 187*/अणु(0x1F), 1, MISC_REG_AEU_AFTER_INVERT_4_FUNC_0,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"AEU: P0 AFTER_INVERT_4 is not 0",
	अणुNA, NA, ~0x801FFFFF, 0, NA, NAपूर्ण पूर्ण,

/*line 188*/अणु(0x3), 1, MISC_REG_AEU_AFTER_INVERT_1_FUNC_1,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"AEU: P1 AFTER_INVERT_1 is not 0",
	अणुNA, NA, ~0xCFFC, 0, NA, NAपूर्ण पूर्ण,

/*line 189*/अणु(0x3), 1, MISC_REG_AEU_AFTER_INVERT_2_FUNC_1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"AEU: P1 AFTER_INVERT_2 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 190*/अणु(0x3), 1, MISC_REG_AEU_AFTER_INVERT_3_FUNC_1,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"AEU: P1 AFTER_INVERT_3 is not 0",
	अणुNA, NA, ~0xFFFF0000, 0, NA, NAपूर्ण पूर्ण,

/*line 191*/अणु(0x3), 1, MISC_REG_AEU_AFTER_INVERT_4_FUNC_1,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"AEU: P1 AFTER_INVERT_4 is not 0",
	अणुNA, NA, ~0x801FFFFF, 0, NA, NAपूर्ण पूर्ण,

/*line 192*/अणु(0x1F), 1, MISC_REG_AEU_AFTER_INVERT_1_MCP,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"AEU: MCP AFTER_INVERT_1 is not 0",
	अणुNA, NA, ~0xCFFC, 0, NA, NAपूर्ण पूर्ण,

/*line 193*/अणु(0x1F), 1, MISC_REG_AEU_AFTER_INVERT_2_MCP,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"AEU: MCP AFTER_INVERT_2 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 194*/अणु(0x1F), 1, MISC_REG_AEU_AFTER_INVERT_3_MCP,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"AEU: MCP AFTER_INVERT_3 is not 0",
	अणुNA, NA, ~0xFFFF0000, 0, NA, NAपूर्ण पूर्ण,

/*line 195*/अणु(0x1F), 1, MISC_REG_AEU_AFTER_INVERT_4_MCP,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"AEU: MCP AFTER_INVERT_4 is not 0",
	अणुNA, NA, ~0x801FFFFF, 0, NA, NAपूर्ण पूर्ण,

/*line 196*/अणु(0xF), 5, PBF_REG_P0_CREDIT,
	PBF_REG_P0_INIT_CRD, 1, 0, pneq_r2,
	PBF_REG_DISABLE_NEW_TASK_PROC_P0, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: P0 credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 197*/अणु(0xF), 5, PBF_REG_P1_CREDIT,
	PBF_REG_P1_INIT_CRD, 1, 0, pneq_r2,
	PBF_REG_DISABLE_NEW_TASK_PROC_P1, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: P1 credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 198*/अणु(0xF), 3, PBF_REG_P4_CREDIT,
	PBF_REG_P4_INIT_CRD, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: P4 credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 199*/अणु(0x10), 5, PBF_REG_CREDIT_Q0,
	PBF_REG_INIT_CRD_Q0, 1, 0, pneq_r2,
	PBF_REG_DISABLE_NEW_TASK_PROC_Q0, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q0 credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 200*/अणु(0x10), 5, PBF_REG_CREDIT_Q1,
	PBF_REG_INIT_CRD_Q1, 1, 0, pneq_r2,
	PBF_REG_DISABLE_NEW_TASK_PROC_Q1, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q1 credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 201*/अणु(0x10), 5, PBF_REG_CREDIT_Q2,
	PBF_REG_INIT_CRD_Q2, 1, 0, pneq_r2,
	PBF_REG_DISABLE_NEW_TASK_PROC_Q2, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q2 credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 202*/अणु(0x10), 5, PBF_REG_CREDIT_Q3,
	PBF_REG_INIT_CRD_Q3, 1, 0, pneq_r2,
	PBF_REG_DISABLE_NEW_TASK_PROC_Q3, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q3 credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 203*/अणु(0x10), 5, PBF_REG_CREDIT_Q4,
	PBF_REG_INIT_CRD_Q4, 1, 0, pneq_r2,
	PBF_REG_DISABLE_NEW_TASK_PROC_Q4, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q4 credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 204*/अणु(0x10), 5, PBF_REG_CREDIT_Q5,
	PBF_REG_INIT_CRD_Q5, 1, 0, pneq_r2,
	PBF_REG_DISABLE_NEW_TASK_PROC_Q5, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q5 credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 205*/अणु(0x10), 3, PBF_REG_CREDIT_LB_Q,
	PBF_REG_INIT_CRD_LB_Q, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: LB Q credit is not equal to init_crd",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 206*/अणु(0xF), 1, PBF_REG_P0_TASK_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: P0 task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 207*/अणु(0xF), 1, PBF_REG_P1_TASK_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: P1 task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 208*/अणु(0xF), 1, PBF_REG_P4_TASK_CNT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: P4 task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 209*/अणु(0x10), 1, PBF_REG_TASK_CNT_Q0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q0 task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 210*/अणु(0x10), 1, PBF_REG_TASK_CNT_Q1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q1 task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 211*/अणु(0x10), 1, PBF_REG_TASK_CNT_Q2,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q2 task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 212*/अणु(0x10), 1, PBF_REG_TASK_CNT_Q3,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q3 task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 213*/अणु(0x10), 1, PBF_REG_TASK_CNT_Q4,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q4 task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 214*/अणु(0x10), 1, PBF_REG_TASK_CNT_Q5,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: Q5 task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 215*/अणु(0x10), 1, PBF_REG_TASK_CNT_LB_Q,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PBF: LB Q task_cnt is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 216*/अणु(0x1F), 1, XCM_REG_CFC_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XCM: CFC_INIT_CRD is not 1",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 217*/अणु(0x1F), 1, UCM_REG_CFC_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"UCM: CFC_INIT_CRD is not 1",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 218*/अणु(0x1F), 1, TCM_REG_CFC_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TCM: CFC_INIT_CRD is not 1",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 219*/अणु(0x1F), 1, CCM_REG_CFC_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CCM: CFC_INIT_CRD is not 1",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 220*/अणु(0x1F), 1, XCM_REG_XQM_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XCM: XQM_INIT_CRD is not 32",
	अणुNA, NA, 32, NA, NA, NAपूर्ण पूर्ण,

/*line 221*/अणु(0x1F), 1, UCM_REG_UQM_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"UCM: UQM_INIT_CRD is not 32",
	अणुNA, NA, 32, NA, NA, NAपूर्ण पूर्ण,

/*line 222*/अणु(0x1F), 1, TCM_REG_TQM_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TCM: TQM_INIT_CRD is not 32",
	अणुNA, NA, 32, NA, NA, NAपूर्ण पूर्ण,

/*line 223*/अणु(0x1F), 1, CCM_REG_CQM_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CCM: CQM_INIT_CRD is not 32",
	अणुNA, NA, 32, NA, NA, NAपूर्ण पूर्ण,

/*line 224*/अणु(0x1F), 1, XCM_REG_TM_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XCM: TM_INIT_CRD is not 4",
	अणुNA, NA, 4, NA, NA, NAपूर्ण पूर्ण,

/*line 225*/अणु(0x1F), 1, UCM_REG_TM_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"UCM: TM_INIT_CRD is not 4",
	अणुNA, NA, 4, NA, NA, NAपूर्ण पूर्ण,

/*line 226*/अणु(0x1F), 1, XCM_REG_FIC0_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"XCM: FIC0_INIT_CRD is not 64",
	अणुNA, NA, 64, NA, NA, NAपूर्ण पूर्ण,

/*line 227*/अणु(0x1F), 1, UCM_REG_FIC0_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"UCM: FIC0_INIT_CRD is not 64",
	अणुNA, NA, 64, NA, NA, NAपूर्ण पूर्ण,

/*line 228*/अणु(0x1F), 1, TCM_REG_FIC0_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TCM: FIC0_INIT_CRD is not 64",
	अणुNA, NA, 64, NA, NA, NAपूर्ण पूर्ण,

/*line 229*/अणु(0x1F), 1, CCM_REG_FIC0_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CCM: FIC0_INIT_CRD is not 64",
	अणुNA, NA, 64, NA, NA, NAपूर्ण पूर्ण,

/*line 230*/अणु(0x1F), 1, XCM_REG_FIC1_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XCM: FIC1_INIT_CRD is not 64",
	अणुNA, NA, 64, NA, NA, NAपूर्ण पूर्ण,

/*line 231*/अणु(0x1F), 1, UCM_REG_FIC1_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"UCM: FIC1_INIT_CRD is not 64",
	अणुNA, NA, 64, NA, NA, NAपूर्ण पूर्ण,

/*line 232*/अणु(0x1F), 1, TCM_REG_FIC1_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TCM: FIC1_INIT_CRD is not 64",
	अणुNA, NA, 64, NA, NA, NAपूर्ण पूर्ण,

/*line 233*/अणु(0x1F), 1, CCM_REG_FIC1_INIT_CRD,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CCM: FIC1_INIT_CRD is not 64",
	अणुNA, NA, 64, NA, NA, NAपूर्ण पूर्ण,

/*line 234*/अणु(0x1), 1, XCM_REG_XX_FREE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XCM: XX_FREE differs from expected 31",
	अणुNA, NA, 31, NA, NA, NAपूर्ण पूर्ण,

/*line 235*/अणु(0x1E), 1, XCM_REG_XX_FREE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XCM: XX_FREE differs from expected 32",
	अणुNA, NA, 32, NA, NA, NAपूर्ण पूर्ण,

/*line 236*/अणु(0x1F), 1, UCM_REG_XX_FREE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"UCM: XX_FREE differs from expected 27",
	अणुNA, NA, 27, NA, NA, NAपूर्ण पूर्ण,

/*line 237*/अणु(0x7), 1, TCM_REG_XX_FREE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TCM: XX_FREE differs from expected 32",
	अणुNA, NA, 32, NA, NA, NAपूर्ण पूर्ण,

/*line 238*/अणु(0x18), 1, TCM_REG_XX_FREE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TCM: XX_FREE differs from expected 29",
	अणुNA, NA, 29, NA, NA, NAपूर्ण पूर्ण,

/*line 239*/अणु(0x1F), 1, CCM_REG_XX_FREE,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CCM: XX_FREE differs from expected 24",
	अणुNA, NA, 24, NA, NA, NAपूर्ण पूर्ण,

/*line 240*/अणु(0x1F), 1, XSEM_REG_FAST_MEMORY + 0x18000,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XSEM: FOC0 credit less than initial credit",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 241*/अणु(0x1F), 1, XSEM_REG_FAST_MEMORY + 0x18040,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XSEM: FOC1 credit less than initial credit",
	अणुNA, NA, 24, NA, NA, NAपूर्ण पूर्ण,

/*line 242*/अणु(0x1F), 1, XSEM_REG_FAST_MEMORY + 0x18080,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"XSEM: FOC2 credit less than initial credit",
	अणुNA, NA, 12, NA, NA, NAपूर्ण पूर्ण,

/*line 243*/अणु(0x1F), 1, USEM_REG_FAST_MEMORY + 0x18000,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"USEM: FOC0 credit less than initial credit",
	अणुNA, NA, 26, NA, NA, NAपूर्ण पूर्ण,

/*line 244*/अणु(0x1F), 1, USEM_REG_FAST_MEMORY + 0x18040,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"USEM: FOC1 credit less than initial credit",
	अणुNA, NA, 78, NA, NA, NAपूर्ण पूर्ण,

/*line 245*/अणु(0x1F), 1, USEM_REG_FAST_MEMORY + 0x18080,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"USEM: FOC2 credit less than initial credit",
	अणुNA, NA, 16, NA, NA, NAपूर्ण पूर्ण,

/*line 246*/अणु(0x1F), 1, USEM_REG_FAST_MEMORY + 0x180C0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"USEM: FOC3 credit less than initial credit",
	अणुNA, NA, 32, NA, NA, NAपूर्ण पूर्ण,

/*line 247*/अणु(0x1F), 1, TSEM_REG_FAST_MEMORY + 0x18000,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TSEM: FOC0 credit less than initial credit",
	अणुNA, NA, 52, NA, NA, NAपूर्ण पूर्ण,

/*line 248*/अणु(0x1F), 1, TSEM_REG_FAST_MEMORY + 0x18040,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TSEM: FOC1 credit less than initial credit",
	अणुNA, NA, 24, NA, NA, NAपूर्ण पूर्ण,

/*line 249*/अणु(0x1F), 1, TSEM_REG_FAST_MEMORY + 0x18080,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TSEM: FOC2 credit less than initial credit",
	अणुNA, NA, 12, NA, NA, NAपूर्ण पूर्ण,

/*line 250*/अणु(0x1F), 1, TSEM_REG_FAST_MEMORY + 0x180C0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"TSEM: FOC3 credit less than initial credit",
	अणुNA, NA, 32, NA, NA, NAपूर्ण पूर्ण,

/*line 251*/अणु(0x1F), 1, CSEM_REG_FAST_MEMORY + 0x18000,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CSEM: FOC0 credit less than initial credit",
	अणुNA, NA, 16, NA, NA, NAपूर्ण पूर्ण,

/*line 252*/अणु(0x1F), 1, CSEM_REG_FAST_MEMORY + 0x18040,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CSEM: FOC1 credit less than initial credit",
	अणुNA, NA, 18, NA, NA, NAपूर्ण पूर्ण,

/*line 253*/अणु(0x1F), 1, CSEM_REG_FAST_MEMORY + 0x18080,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CSEM: FOC2 credit less than initial credit",
	अणुNA, NA, 48, NA, NA, NAपूर्ण पूर्ण,

/*line 254*/अणु(0x1F), 1, CSEM_REG_FAST_MEMORY + 0x180C0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"CSEM: FOC3 credit less than initial credit",
	अणुNA, NA, 14, NA, NA, NAपूर्ण पूर्ण,

/*line 255*/अणु(0x1F), 1, PRS_REG_TSDM_CURRENT_CREDIT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PRS: TSDM current credit is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 256*/अणु(0x1F), 1, PRS_REG_TCM_CURRENT_CREDIT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PRS: TCM current credit is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 257*/अणु(0x1F), 1, PRS_REG_CFC_LD_CURRENT_CREDIT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PRS: CFC_LD current credit is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 258*/अणु(0x1F), 1, PRS_REG_CFC_SEARCH_CURRENT_CREDIT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PRS: CFC_SEARCH current credit is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 259*/अणु(0x1F), 1, PRS_REG_SRC_CURRENT_CREDIT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PRS: SRCH current credit is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 260*/अणु(0x1F), 1, PRS_REG_PENDING_BRB_PRS_RQ,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PRS: PENDING_BRB_PRS_RQ is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 261*/अणु(0x1F), 2, PRS_REG_PENDING_BRB_CAC0_RQ,
	NA, 5, 4, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PRS: PENDING_BRB_CAC_RQ is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 262*/अणु(0x1F), 1, PRS_REG_SERIAL_NUM_STATUS_LSB,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PRS: SERIAL_NUM_STATUS_LSB is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 263*/अणु(0x1F), 1, PRS_REG_SERIAL_NUM_STATUS_MSB,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"PRS: SERIAL_NUM_STATUS_MSB is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 264*/अणु(0x1F), 1, CDU_REG_ERROR_DATA,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CDU: ERROR_DATA is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 265*/अणु(0x1F), 1, CCM_REG_STORM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CCM: STORM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 266*/अणु(0x1F), 1, CCM_REG_CSDM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CCM: CSDM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 267*/अणु(0x1F), 1, CCM_REG_TSEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CCM: TSEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 268*/अणु(0x1F), 1, CCM_REG_XSEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CCM: XSEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 269*/अणु(0x1F), 1, CCM_REG_USEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CCM: USEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 270*/अणु(0x1F), 1, CCM_REG_PBF_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"CCM: PBF declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 271*/अणु(0x1F), 1, TCM_REG_STORM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"TCM: STORM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 272*/अणु(0x1F), 1, TCM_REG_TSDM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"TCM: TSDM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 273*/अणु(0x1F), 1, TCM_REG_PRS_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"TCM: PRS declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 274*/अणु(0x1F), 1, TCM_REG_PBF_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"TCM: PBF declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 275*/अणु(0x1F), 1, TCM_REG_USEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"TCM: USEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 276*/अणु(0x1F), 1, TCM_REG_CSEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"TCM: CSEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 277*/अणु(0x1F), 1, UCM_REG_STORM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"UCM: STORM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 278*/अणु(0x1F), 1, UCM_REG_USDM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"UCM: USDM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 279*/अणु(0x1F), 1, UCM_REG_TSEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"UCM: TSEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 280*/अणु(0x1F), 1, UCM_REG_CSEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"UCM: CSEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 281*/अणु(0x1F), 1, UCM_REG_XSEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"UCM: XSEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 282*/अणु(0x1F), 1, UCM_REG_DORQ_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"UCM: DORQ declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 283*/अणु(0x1F), 1, XCM_REG_STORM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: STORM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 284*/अणु(0x1F), 1, XCM_REG_XSDM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: XSDM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 285*/अणु(0x1F), 1, XCM_REG_TSEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: TSEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 286*/अणु(0x1F), 1, XCM_REG_CSEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: CSEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 287*/अणु(0x1F), 1, XCM_REG_USEM_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: USEM declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 288*/अणु(0x1F), 1, XCM_REG_DORQ_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: DORQ declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 289*/अणु(0x1F), 1, XCM_REG_PBF_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: PBF declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 290*/अणु(0x1F), 1, XCM_REG_NIG0_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: NIG0 declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 291*/अणु(0x1F), 1, XCM_REG_NIG1_LENGTH_MIS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"XCM: NIG1 declared message length unequal to actual",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 292*/अणु(0x1F), 1, QM_REG_XQM_WRC_FIFOLVL,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: XQM wrc_fifolvl is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 293*/अणु(0x1F), 1, QM_REG_UQM_WRC_FIFOLVL,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: UQM wrc_fifolvl is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 294*/अणु(0x1F), 1, QM_REG_TQM_WRC_FIFOLVL,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: TQM wrc_fifolvl is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 295*/अणु(0x1F), 1, QM_REG_CQM_WRC_FIFOLVL,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: CQM wrc_fifolvl is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 296*/अणु(0x1F), 1, QM_REG_QSTATUS_LOW,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: QSTATUS_LOW is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 297*/अणु(0x1F), 1, QM_REG_QSTATUS_HIGH,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: QSTATUS_HIGH is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 298*/अणु(0x1F), 1, QM_REG_PAUSESTATE0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: PAUSESTATE0 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 299*/अणु(0x1F), 1, QM_REG_PAUSESTATE1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: PAUSESTATE1 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 300*/अणु(0x1F), 1, QM_REG_OVFQNUM,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: OVFQNUM is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 301*/अणु(0x1F), 1, QM_REG_OVFERROR,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: OVFERROR is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 302*/अणु(0x1F), 6, QM_REG_PTRTBL,
	NA, 64, 8, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: read and write variables not equal",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 303*/अणु(0x1F), 1, BRB1_REG_BRB1_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"BRB1: parity status is not 0",
	अणुNA, NA, ~0x8, 0, NA, NAपूर्ण पूर्ण,

/*line 304*/अणु(0x1F), 1, CDU_REG_CDU_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"CDU: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 305*/अणु(0x1F), 1, CFC_REG_CFC_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"CFC: parity status is not 0",
	अणुNA, NA, ~0x2, 0, NA, NAपूर्ण पूर्ण,

/*line 306*/अणु(0x1F), 1, CSDM_REG_CSDM_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"CSDM: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 307*/अणु(0x3), 1, DBG_REG_DBG_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"DBG: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 308*/अणु(0x1F), 1, DMAE_REG_DMAE_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"DMAE: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 309*/अणु(0x1F), 1, DORQ_REG_DORQ_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"DORQ: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 310*/अणु(0x1), 1, TCM_REG_TCM_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"TCM: parity status is not 0",
	अणुNA, NA, ~0x3ffc0, 0, NA, NAपूर्ण पूर्ण,

/*line 311*/अणु(0x1E), 1, TCM_REG_TCM_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"TCM: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 312*/अणु(0x1), 1, CCM_REG_CCM_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"CCM: parity status is not 0",
	अणुNA, NA, ~0x3ffc0, 0, NA, NAपूर्ण पूर्ण,

/*line 313*/अणु(0x1E), 1, CCM_REG_CCM_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"CCM: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 314*/अणु(0x1), 1, UCM_REG_UCM_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"UCM: parity status is not 0",
	अणुNA, NA, ~0x3ffc0, 0, NA, NAपूर्ण पूर्ण,

/*line 315*/अणु(0x1E), 1, UCM_REG_UCM_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"UCM: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 316*/अणु(0x1), 1, XCM_REG_XCM_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"XCM: parity status is not 0",
	अणुNA, NA, ~0x3ffc0, 0, NA, NAपूर्ण पूर्ण,

/*line 317*/अणु(0x1E), 1, XCM_REG_XCM_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"XCM: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 318*/अणु(0x1), 1, HC_REG_HC_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"HC: parity status is not 0",
	अणुNA, NA, ~0x1, 0, NA, NAपूर्ण पूर्ण,

/*line 319*/अणु(0x1), 1, MISC_REG_MISC_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"MISC: parity status is not 0",
	अणुNA, NA, ~0x1, 0, NA, NAपूर्ण पूर्ण,

/*line 320*/अणु(0x1F), 1, PRS_REG_PRS_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PRS: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 321*/अणु(0x1F), 1, PXP_REG_PXP_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 322*/अणु(0x1F), 1, QM_REG_QM_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"QM: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 323*/अणु(0x1), 1, SRC_REG_SRC_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"SRCH: parity status is not 0",
	अणुNA, NA, ~0x4, 0, NA, NAपूर्ण पूर्ण,

/*line 324*/अणु(0x1F), 1, TSDM_REG_TSDM_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"TSDM: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 325*/अणु(0x1F), 1, USDM_REG_USDM_PRTY_STS,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"USDM: parity status is not 0",
	अणुNA, NA, ~0x20, 0, NA, NAपूर्ण पूर्ण,

/*line 326*/अणु(0x1F), 1, XSDM_REG_XSDM_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"XSDM: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 327*/अणु(0x1F), 1, GRCBASE_XPB + PB_REG_PB_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"XPB: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 328*/अणु(0x1F), 1, GRCBASE_UPB + PB_REG_PB_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"UPB: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 329*/अणु(0x1F), 1, CSEM_REG_CSEM_PRTY_STS_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"CSEM: parity status 0 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 330*/अणु(0x1), 1, PXP2_REG_PXP2_PRTY_STS_0,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"PXP2: parity status 0 is not 0",
	अणुNA, NA, ~0xfff40020, 0, NA, NAपूर्ण पूर्ण,

/*line 331*/अणु(0x1E), 1, PXP2_REG_PXP2_PRTY_STS_0,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"PXP2: parity status 0 is not 0",
	अणुNA, NA, ~0x20, 0, NA, NAपूर्ण पूर्ण,

/*line 332*/अणु(0x1F), 1, TSEM_REG_TSEM_PRTY_STS_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"TSEM: parity status 0 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 333*/अणु(0x1F), 1, USEM_REG_USEM_PRTY_STS_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"USEM: parity status 0 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 334*/अणु(0x1F), 1, XSEM_REG_XSEM_PRTY_STS_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"XSEM: parity status 0 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 335*/अणु(0x1F), 1, CSEM_REG_CSEM_PRTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"CSEM: parity status 1 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 336*/अणु(0x1), 1, PXP2_REG_PXP2_PRTY_STS_1,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"PXP2: parity status 1 is not 0",
	अणुNA, NA, ~0x20, 0, NA, NAपूर्ण पूर्ण,

/*line 337*/अणु(0x1E), 1, PXP2_REG_PXP2_PRTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PXP2: parity status 1 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 338*/अणु(0x1F), 1, TSEM_REG_TSEM_PRTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"TSEM: parity status 1 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 339*/अणु(0x1F), 1, USEM_REG_USEM_PRTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"USEM: parity status 1 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 340*/अणु(0x1F), 1, XSEM_REG_XSEM_PRTY_STS_1,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"XSEM: parity status 1 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 341*/अणु(0x1C), 1, PGLUE_B_REG_PGLUE_B_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGLUE_B: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 342*/अणु(0x2), 2, QM_REG_QTASKCTR_EXT_A_0,
	NA, 64, 4, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Q_EXT_A (upper 64 queues), Queue is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 343*/अणु(0x2), 1, QM_REG_QSTATUS_LOW_EXT_A,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: QSTATUS_LOW_EXT_A is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 344*/अणु(0x2), 1, QM_REG_QSTATUS_HIGH_EXT_A,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: QSTATUS_HIGH_EXT_A is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 345*/अणु(0x1E), 1, QM_REG_PAUSESTATE2,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: PAUSESTATE2 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 346*/अणु(0x1E), 1, QM_REG_PAUSESTATE3,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: PAUSESTATE3 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 347*/अणु(0x2), 1, QM_REG_PAUSESTATE4,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: PAUSESTATE4 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 348*/अणु(0x2), 1, QM_REG_PAUSESTATE5,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: PAUSESTATE5 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 349*/अणु(0x2), 1, QM_REG_PAUSESTATE6,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: PAUSESTATE6 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 350*/अणु(0x2), 1, QM_REG_PAUSESTATE7,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"QM: PAUSESTATE7 is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 351*/अणु(0x2), 6, QM_REG_PTRTBL_EXT_A,
	NA, 64, 8, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: read and write variables not equal in ext table",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 352*/अणु(0x1E), 1, MISC_REG_AEU_SYS_KILL_OCCURRED,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"MISC: system kill occurred;",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 353*/अणु(0x1E), 1, MISC_REG_AEU_SYS_KILL_STATUS_0,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"MISC: system kill occurred; status_0 register",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 354*/अणु(0x1E), 1, MISC_REG_AEU_SYS_KILL_STATUS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"MISC: system kill occurred; status_1 register",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 355*/अणु(0x1E), 1, MISC_REG_AEU_SYS_KILL_STATUS_2,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"MISC: system kill occurred; status_2 register",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 356*/अणु(0x1E), 1, MISC_REG_AEU_SYS_KILL_STATUS_3,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"MISC: system kill occurred; status_3 register",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 357*/अणु(0x1E), 1, MISC_REG_PCIE_HOT_RESET,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_WARNING,
	"MISC: pcie_rst_b was asserted without perst assertion",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 358*/अणु(0x1F), 1, NIG_REG_NIG_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_ERROR,
	"NIG: interrupt 0 is active",
	अणुNA, NA, ~0x300, 0, NA, NAपूर्ण पूर्ण,

/*line 359*/अणु(0x1F), 1, NIG_REG_NIG_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDLE_CHK_WARNING,
	"NIG: Access to BMAC while not active. If tested on FPGA, ignore this warning",
	अणुNA, NA, 0x300, NA, NA, NAपूर्ण पूर्ण,

/*line 360*/अणु(0x1F), 1, NIG_REG_NIG_INT_STS_1,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_ERROR,
	"NIG: interrupt 1 is active",
	अणुNA, NA, 0x783FF03, 0, NA, NAपूर्ण पूर्ण,

/*line 361*/अणु(0x1F), 1, NIG_REG_NIG_INT_STS_1,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_WARNING,
	"NIG: port cos was paused too long",
	अणुNA, NA, ~0x783FF0F, 0, NA, NAपूर्ण पूर्ण,

/*line 362*/अणु(0x1F), 1, NIG_REG_NIG_INT_STS_1,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_WARNING,
	"NIG: Got packets w/o Outer-VLAN in MF mode",
	अणुNA, NA, 0xC, 0, NA, NAपूर्ण पूर्ण,

/*line 363*/अणु(0x2), 1, NIG_REG_NIG_PRTY_STS,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_ERROR,
	"NIG: parity interrupt is active",
	अणुNA, NA, ~0xFFC00000, 0, NA, NAपूर्ण पूर्ण,

/*line 364*/अणु(0x1C), 1, NIG_REG_NIG_PRTY_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_ERROR,
	"NIG: parity 0 interrupt is active",
	अणुNA, NA, ~0xFFC00000, 0, NA, NAपूर्ण पूर्ण,

/*line 365*/अणु(0x4), 1, NIG_REG_NIG_PRTY_STS_1,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_ERROR,
	"NIG: parity 1 interrupt is active",
	अणुNA, NA, 0xff, 0, NA, NAपूर्ण पूर्ण,

/*line 366*/अणु(0x18), 1, NIG_REG_NIG_PRTY_STS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"NIG: parity 1 interrupt is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 367*/अणु(0x1F), 1, TSEM_REG_TSEM_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_WARNING,
	"TSEM: interrupt 0 is active",
	अणुNA, NA, ~0x10000000, 0, NA, NAपूर्ण पूर्ण,

/*line 368*/अणु(0x1F), 1, TSEM_REG_TSEM_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDLE_CHK_WARNING,
	"TSEM: interrupt 0 is active",
	अणुNA, NA, 0x10000000, NA, NA, NAपूर्ण पूर्ण,

/*line 369*/अणु(0x1F), 1, TSEM_REG_TSEM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"TSEM: interrupt 1 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 370*/अणु(0x1F), 1, CSEM_REG_CSEM_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_WARNING,
	"CSEM: interrupt 0 is active",
	अणुNA, NA, ~0x10000000, 0, NA, NAपूर्ण पूर्ण,

/*line 371*/अणु(0x1F), 1, CSEM_REG_CSEM_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDLE_CHK_WARNING,
	"CSEM: interrupt 0 is active",
	अणुNA, NA, 0x10000000, NA, NA, NAपूर्ण पूर्ण,

/*line 372*/अणु(0x1F), 1, CSEM_REG_CSEM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"CSEM: interrupt 1 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 373*/अणु(0x1F), 1, USEM_REG_USEM_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_WARNING,
	"USEM: interrupt 0 is active",
	अणुNA, NA, ~0x10000000, 0, NA, NAपूर्ण पूर्ण,

/*line 374*/अणु(0x1F), 1, USEM_REG_USEM_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDLE_CHK_WARNING,
	"USEM: interrupt 0 is active",
	अणुNA, NA, 0x10000000, NA, NA, NAपूर्ण पूर्ण,

/*line 375*/अणु(0x1F), 1, USEM_REG_USEM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"USEM: interrupt 1 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 376*/अणु(0x1F), 1, XSEM_REG_XSEM_INT_STS_0,
	NA, NA, NA, pand_neq,
	NA, IDLE_CHK_WARNING,
	"XSEM: interrupt 0 is active",
	अणुNA, NA, ~0x10000000, 0, NA, NAपूर्ण पूर्ण,

/*line 377*/अणु(0x1F), 1, XSEM_REG_XSEM_INT_STS_0,
	NA, NA, NA, peq,
	NA, IDLE_CHK_WARNING,
	"XSEM: interrupt 0 is active",
	अणुNA, NA, 0x10000000, NA, NA, NAपूर्ण पूर्ण,

/*line 378*/अणु(0x1F), 1, XSEM_REG_XSEM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"XSEM: interrupt 1 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 379*/अणु(0x1F), 1, TSDM_REG_TSDM_INT_STS_0,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"TSDM: interrupt 0 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 380*/अणु(0x1F), 1, TSDM_REG_TSDM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"TSDM: interrupt 0 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 381*/अणु(0x1F), 1, CSDM_REG_CSDM_INT_STS_0,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"CSDM: interrupt 0 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 382*/अणु(0x1F), 1, CSDM_REG_CSDM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"CSDM: interrupt 0 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 383*/अणु(0x1F), 1, USDM_REG_USDM_INT_STS_0,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"USDM: interrupt 0 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 384*/अणु(0x1F), 1, USDM_REG_USDM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"USDM: interrupt 0 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 385*/अणु(0x1F), 1, XSDM_REG_XSDM_INT_STS_0,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"XSDM: interrupt 0 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 386*/अणु(0x1F), 1, XSDM_REG_XSDM_INT_STS_1,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_ERROR,
	"XSDM: interrupt 0 is active",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 387*/अणु(0x2), 1, HC_REG_HC_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"HC: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 388*/अणु(0x1E), 1, MISC_REG_MISC_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"MISC: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 389*/अणु(0x1E), 1, SRC_REG_SRC_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"SRCH: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 390*/अणु(0xC), 3, QM_REG_BYTECRD0,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 0 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 391*/अणु(0xC), 3, QM_REG_BYTECRD1,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 1 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 392*/अणु(0xC), 3, QM_REG_BYTECRD2,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 2 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 393*/अणु(0x1C), 1, QM_REG_VOQCRDERRREG,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"QM: VOQ credit error register is not 0 (VOQ credit overflow/underflow)",
	अणुNA, NA, 0xFFFF, 0, NA, NAपूर्ण पूर्ण,

/*line 394*/अणु(0x1C), 1, QM_REG_BYTECRDERRREG,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"QM: Byte credit error register is not 0 (Byte credit overflow/underflow)",
	अणुNA, NA, 0xFFF, 0, NA, NAपूर्ण पूर्ण,

/*line 395*/अणु(0x1C), 1, PGLUE_B_REG_FLR_REQUEST_VF_31_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGL: FLR request is set for VF addresses 31-0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 396*/अणु(0x1C), 1, PGLUE_B_REG_FLR_REQUEST_VF_63_32,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGL: FLR request is set for VF addresses 63-32",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 397*/अणु(0x1C), 1, PGLUE_B_REG_FLR_REQUEST_VF_95_64,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGL: FLR request is set for VF addresses 95-64",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 398*/अणु(0x1C), 1, PGLUE_B_REG_FLR_REQUEST_VF_127_96,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGL: FLR request is set for VF addresses 127-96",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 399*/अणु(0x1C), 1, PGLUE_B_REG_FLR_REQUEST_PF_7_0,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGL: FLR request is set for PF addresses 7-0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 400*/अणु(0x1C), 1, PGLUE_B_REG_SR_IOV_DISABLED_REQUEST,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGL: SR-IOV disable request is set",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 401*/अणु(0x1C), 1, PGLUE_B_REG_CFG_SPACE_A_REQUEST,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGL: Cfg-Space A request is set",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 402*/अणु(0x1C), 1, PGLUE_B_REG_CFG_SPACE_B_REQUEST,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"PGL: Cfg-Space B request is set",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 403*/अणु(0x1C), 1, IGU_REG_ERROR_HANDLING_DATA_VALID,
	NA, NA, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"IGU: some unauthorized commands arrived to the IGU. Use igu_dump_fifo utility for more details",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 404*/अणु(0x1C), 1, IGU_REG_ATTN_WRITE_DONE_PENDING,
	NA, NA, NA, pneq,
	NA, IDLE_CHK_WARNING,
	"IGU attention message write done pending is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 405*/अणु(0x1C), 1, IGU_REG_WRITE_DONE_PENDING,
	NA, 5, 4, pneq,
	NA, IDLE_CHK_WARNING,
	"IGU MSI/MSIX message write done pending is not empty",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 406*/अणु(0x1C), 1, IGU_REG_IGU_PRTY_STS,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"IGU: parity status is not 0",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 407*/अणु(0x1E), 3, MISC_REG_GRC_TIMEOUT_ATTN,
	MISC_REG_AEU_AFTER_INVERT_4_FUNC_0, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"MISC_REG_GRC_TIMEOUT_ATTN: GRC timeout attention parameters (FUNC_0)",
	अणुNA, NA, 0x4000000, 0, NA, NAपूर्ण पूर्ण,

/*line 408*/अणु(0x1C), 3, MISC_REG_GRC_TIMEOUT_ATTN_FULL_FID,
	MISC_REG_AEU_AFTER_INVERT_4_FUNC_0, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"MISC_REG_GRC_TIMEOUT_ATTN_FULL_FID: GRC timeout attention FID (FUNC_0)",
	अणुNA, NA, 0x4000000, 0, NA, NAपूर्ण पूर्ण,

/*line 409*/अणु(0x1E), 3, MISC_REG_GRC_TIMEOUT_ATTN,
	MISC_REG_AEU_AFTER_INVERT_4_FUNC_1, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"MISC_REG_GRC_TIMEOUT_ATTN: GRC timeout attention parameters (FUNC_1)",
	अणुNA, NA, 0x4000000, 0, NA, NAपूर्ण पूर्ण,

/*line 410*/अणु(0x1C), 3, MISC_REG_GRC_TIMEOUT_ATTN_FULL_FID,
	MISC_REG_AEU_AFTER_INVERT_4_FUNC_1, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"MISC_REG_GRC_TIMEOUT_ATTN_FULL_FID: GRC timeout attention FID (FUNC_1)",
	अणुNA, NA, 0x4000000, 0, NA, NAपूर्ण पूर्ण,

/*line 411*/अणु(0x1E), 3, MISC_REG_GRC_TIMEOUT_ATTN,
	MISC_REG_AEU_AFTER_INVERT_4_MCP, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"MISC_REG_GRC_TIMEOUT_ATTN: GRC timeout attention parameters (MCP)",
	अणुNA, NA, 0x4000000, 0, NA, NAपूर्ण पूर्ण,

/*line 412*/अणु(0x1C), 3, MISC_REG_GRC_TIMEOUT_ATTN_FULL_FID,
	MISC_REG_AEU_AFTER_INVERT_4_MCP, 1, 0, pand_neq,
	NA, IDLE_CHK_ERROR,
	"MISC_REG_GRC_TIMEOUT_ATTN_FULL_FID: GRC timeout attention FID (MCP)",
	अणुNA, NA, 0x4000000, 0, NA, NAपूर्ण पूर्ण,

/*line 413*/अणु(0x1C), 1, IGU_REG_SILENT_DROP,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"Some messages were not executed in the IGU",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 414*/अणु(0x1C), 1, PXP2_REG_PSWRQ_BW_CREDIT,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR,
	"PXP2: rq_read_credit and rq_write_credit are not 5",
	अणुNA, NA, 0x2D, NA, NA, NAपूर्ण पूर्ण,

/*line 415*/अणु(0x1C), 1, IGU_REG_SB_CTRL_FSM,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"IGU: block is not in idle. SB_CTRL_FSM should be zero in idle state",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 416*/अणु(0x1C), 1, IGU_REG_INT_HANDLE_FSM,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"IGU: block is not in idle. INT_HANDLE_FSM should be zero in idle state",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 417*/अणु(0x1C), 1, IGU_REG_ATTN_FSM,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"IGU: block is not in idle. SB_ATTN_FSMshould be zeroor two in idle state",
	अणुNA, NA, ~0x2, 0, NA, NAपूर्ण पूर्ण,

/*line 418*/अणु(0x1C), 1, IGU_REG_CTRL_FSM,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"IGU: block is not in idle. SB_CTRL_FSM should be zero in idle state",
	अणुNA, NA, ~0x1, 0, NA, NAपूर्ण पूर्ण,

/*line 419*/अणु(0x1C), 1, IGU_REG_PXP_ARB_FSM,
	NA, 1, 0, pand_neq,
	NA, IDLE_CHK_WARNING,
	"IGU: block is not in idle. SB_ARB_FSM should be zero in idle state",
	अणुNA, NA, ~0x1, 0, NA, NAपूर्ण पूर्ण,

/*line 420*/अणु(0x1C), 1, IGU_REG_PENDING_BITS_STATUS,
	NA, 5, 4, pneq,
	NA, IDLE_CHK_WARNING,
	"IGU: block is not in idle. There are pending write done",
	अणुNA, NA, 0, NA, NA, NAपूर्ण पूर्ण,

/*line 421*/अणु(0x10), 3, QM_REG_VOQCREDIT_0,
	QM_REG_VOQINITCREDIT_0, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_0, VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 422*/अणु(0x10), 3, QM_REG_VOQCREDIT_1,
	QM_REG_VOQINITCREDIT_1, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_1, VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 423*/अणु(0x10), 3, QM_REG_VOQCREDIT_2,
	QM_REG_VOQINITCREDIT_2, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_2, VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 424*/अणु(0x10), 3, QM_REG_VOQCREDIT_3,
	QM_REG_VOQINITCREDIT_3, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_3, VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 425*/अणु(0x10), 3, QM_REG_VOQCREDIT_4,
	QM_REG_VOQINITCREDIT_4, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_4, VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 426*/अणु(0x10), 3, QM_REG_VOQCREDIT_5,
	QM_REG_VOQINITCREDIT_5, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_5, VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 427*/अणु(0x10), 3, QM_REG_VOQCREDIT_6,
	QM_REG_VOQINITCREDIT_6, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: VOQ_6 (LB VOQ), VOQ credit is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 428*/अणु(0x10), 3, QM_REG_BYTECRD0,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 0 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 429*/अणु(0x10), 3, QM_REG_BYTECRD1,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 1 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 430*/अणु(0x10), 3, QM_REG_BYTECRD2,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 2 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 431*/अणु(0x10), 3, QM_REG_BYTECRD3,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 3 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 432*/अणु(0x10), 3, QM_REG_BYTECRD4,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 4 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 433*/अणु(0x10), 3, QM_REG_BYTECRD5,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 5 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 434*/अणु(0x10), 3, QM_REG_BYTECRD6,
	QM_REG_BYTECRDINITVAL, 1, 0, pneq_r2,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"QM: Byte credit 6 is not equal to initial credit",
	अणुNA, NA, NA, NA, NA, NAपूर्ण पूर्ण,

/*line 435*/अणु(0x10), 1, QM_REG_FWVOQ0TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDLE_CHK_ERROR,
	"QM: FwVoq0 is mapped to HwVoq7 (non-TX HwVoq)",
	अणुNA, NA, 0x7, NA, NA, NAपूर्ण पूर्ण,

/*line 436*/अणु(0x10), 1, QM_REG_FWVOQ1TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDLE_CHK_ERROR,
	"QM: FwVoq1 is mapped to HwVoq7 (non-TX HwVoq)",
	अणुNA, NA, 0x7, NA, NA, NAपूर्ण पूर्ण,

/*line 437*/अणु(0x10), 1, QM_REG_FWVOQ2TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDLE_CHK_ERROR,
	"QM: FwVoq2 is mapped to HwVoq7 (non-TX HwVoq)",
	अणुNA, NA, 0x7, NA, NA, NAपूर्ण पूर्ण,

/*line 438*/अणु(0x10), 1, QM_REG_FWVOQ3TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDLE_CHK_ERROR,
	"QM: FwVoq3 is mapped to HwVoq7 (non-TX HwVoq)",
	अणुNA, NA, 0x7, NA, NA, NAपूर्ण पूर्ण,

/*line 439*/अणु(0x10), 1, QM_REG_FWVOQ4TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDLE_CHK_ERROR,
	"QM: FwVoq4 is mapped to HwVoq7 (non-TX HwVoq)",
	अणुNA, NA, 0x7, NA, NA, NAपूर्ण पूर्ण,

/*line 440*/अणु(0x10), 1, QM_REG_FWVOQ5TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDLE_CHK_ERROR,
	"QM: FwVoq5 is mapped to HwVoq7 (non-TX HwVoq)",
	अणुNA, NA, 0x7, NA, NA, NAपूर्ण पूर्ण,

/*line 441*/अणु(0x10), 1, QM_REG_FWVOQ6TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDLE_CHK_ERROR,
	"QM: FwVoq6 is mapped to HwVoq7 (non-TX HwVoq)",
	अणुNA, NA, 0x7, NA, NA, NAपूर्ण पूर्ण,

/*line 442*/अणु(0x10), 1, QM_REG_FWVOQ7TOHWVOQ,
	NA, 1, 0, peq,
	NA, IDLE_CHK_ERROR,
	"QM: FwVoq7 is mapped to HwVoq7 (non-TX HwVoq)",
	अणुNA, NA, 0x7, NA, NA, NAपूर्ण पूर्ण,

/*line 443*/अणु(0x1F), 1, NIG_REG_INGRESS_EOP_PORT0_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 0 EOP FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 444*/अणु(0x1F), 1, NIG_REG_INGRESS_EOP_PORT1_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 1 EOP FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 445*/अणु(0x1F), 1, NIG_REG_INGRESS_EOP_LB_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: LB EOP FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 446*/अणु(0x1F), 1, NIG_REG_INGRESS_RMP0_DSCR_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"NIG: Port 0 RX MCP descriptor FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 447*/अणु(0x1F), 1, NIG_REG_INGRESS_RMP1_DSCR_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"NIG: Port 1 RX MCP descriptor FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 448*/अणु(0x1F), 1, NIG_REG_INGRESS_LB_PBF_DELAY_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: PBF LB FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 449*/अणु(0x1F), 1, NIG_REG_EGRESS_MNG0_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"NIG: Port 0 TX MCP FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 450*/अणु(0x1F), 1, NIG_REG_EGRESS_MNG1_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"NIG: Port 1 TX MCP FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 451*/अणु(0x1F), 1, NIG_REG_EGRESS_DEBUG_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Debug FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 452*/अणु(0x1F), 1, NIG_REG_EGRESS_DELAY0_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: PBF IF0 FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 453*/अणु(0x1F), 1, NIG_REG_EGRESS_DELAY1_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: PBF IF1 FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 454*/अणु(0x1F), 1, NIG_REG_LLH0_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 0 RX LLH FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 455*/अणु(0x1F), 1, NIG_REG_LLH1_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 1 RX LLH FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 456*/अणु(0x1C), 1, NIG_REG_P0_TX_MNG_HOST_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"NIG: Port 0 TX MCP FIFO for traffic going to the host is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 457*/अणु(0x1C), 1, NIG_REG_P1_TX_MNG_HOST_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"NIG: Port 1 TX MCP FIFO for traffic going to the host is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 458*/अणु(0x1C), 1, NIG_REG_P0_TLLH_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 0 TX LLH FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 459*/अणु(0x1C), 1, NIG_REG_P1_TLLH_FIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 1 TX LLH FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 460*/अणु(0x1C), 1, NIG_REG_P0_HBUF_DSCR_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"NIG: Port 0 RX MCP descriptor FIFO for traffic from the host is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 461*/अणु(0x1C), 1, NIG_REG_P1_HBUF_DSCR_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_WARNING,
	"NIG: Port 1 RX MCP descriptor FIFO for traffic from the host is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 462*/अणु(0x18), 1, NIG_REG_P0_RX_MACFIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 0 RX MAC interface FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 463*/अणु(0x18), 1, NIG_REG_P1_RX_MACFIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 1 RX MAC interface FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 464*/अणु(0x18), 1, NIG_REG_P0_TX_MACFIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 0 TX MAC interface FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 465*/अणु(0x18), 1, NIG_REG_P1_TX_MACFIFO_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: Port 1 TX MAC interface FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 466*/अणु(0x10), 1, NIG_REG_EGRESS_DELAY2_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: PBF IF2 FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 467*/अणु(0x10), 1, NIG_REG_EGRESS_DELAY3_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: PBF IF3 FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 468*/अणु(0x10), 1, NIG_REG_EGRESS_DELAY4_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: PBF IF4 FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,

/*line 469*/अणु(0x10), 1, NIG_REG_EGRESS_DELAY5_EMPTY,
	NA, 1, 0, pneq,
	NA, IDLE_CHK_ERROR_NO_TRAFFIC,
	"NIG: PBF IF5 FIFO is not empty",
	अणुNA, NA, 1, NA, NA, NAपूर्ण पूर्ण,
पूर्ण;

/* handle self test fails according to severity and type */
अटल व्योम bnx2x_self_test_log(काष्ठा bnx2x *bp, u8 severity, अक्षर *message)
अणु
	चयन (severity) अणु
	हाल IDLE_CHK_ERROR:
		BNX2X_ERR("ERROR %s", message);
		idle_chk_errors++;
		अवरोध;
	हाल IDLE_CHK_ERROR_NO_TRAFFIC:
		DP(NETIF_MSG_HW, "INFO %s", message);
		अवरोध;
	हाल IDLE_CHK_WARNING:
		DP(NETIF_MSG_HW, "WARNING %s", message);
		idle_chk_warnings++;
		अवरोध;
	पूर्ण
पूर्ण

/* specअगरic test क्रम QM rd/wr poपूर्णांकers and rd/wr banks */
अटल व्योम bnx2x_idle_chk6(काष्ठा bnx2x *bp,
			    काष्ठा st_record *rec, अक्षर *message)
अणु
	u32 rd_ptr, wr_ptr, rd_bank, wr_bank;
	पूर्णांक i;

	क्रम (i = 0; i < rec->loop; i++) अणु
		/* पढ़ो regs */
		rec->pred_args.val1 =
			REG_RD(bp, rec->reg1 + i * rec->incr);
		rec->pred_args.val2 =
			REG_RD(bp, rec->reg1 + i * rec->incr + 4);

		/* calc पढ़ो and ग_लिखो poपूर्णांकers */
		rd_ptr = ((rec->pred_args.val1 & 0x3FFFFFC0) >> 6);
		wr_ptr = ((((rec->pred_args.val1 & 0xC0000000) >> 30) & 0x3) |
			((rec->pred_args.val2 & 0x3FFFFF) << 2));

		/* perfrom poपूर्णांकer test */
		अगर (rd_ptr != wr_ptr) अणु
			snम_लिखो(message, MAX_FAIL_MSG,
				 "QM: PTRTBL entry %d- rd_ptr is not equal to wr_ptr. Values are 0x%x and 0x%x\n",
				 i, rd_ptr, wr_ptr);
			bnx2x_self_test_log(bp, rec->severity, message);
		पूर्ण

		/* calculate पढ़ो and ग_लिखो banks */
		rd_bank = ((rec->pred_args.val1 & 0x30) >> 4);
		wr_bank = (rec->pred_args.val1 & 0x03);

		/* perक्रमm bank test */
		अगर (rd_bank != wr_bank) अणु
			snम_लिखो(message, MAX_FAIL_MSG,
				 "QM: PTRTBL entry %d - rd_bank is not equal to wr_bank. Values are 0x%x 0x%x\n",
				 i, rd_bank, wr_bank);
			bnx2x_self_test_log(bp, rec->severity, message);
		पूर्ण
	पूर्ण
पूर्ण

/* specअगरic test क्रम cfc info ram and cid cam */
अटल व्योम bnx2x_idle_chk7(काष्ठा bnx2x *bp,
			    काष्ठा st_record *rec, अक्षर *message)
अणु
	पूर्णांक i;

	/* iterate through lcids */
	क्रम (i = 0; i < rec->loop; i++) अणु
		/* make sure cam entry is valid (bit 0) */
		अगर ((REG_RD(bp, (rec->reg2 + i * 4)) & 0x1) != 0x1)
			जारी;

		/* get connection type (multiple पढ़ोs due to widebus) */
		REG_RD(bp, (rec->reg1 + i * rec->incr));
		REG_RD(bp, (rec->reg1 + i * rec->incr + 4));
		rec->pred_args.val1 =
			REG_RD(bp, (rec->reg1 + i * rec->incr + 8));
		REG_RD(bp, (rec->reg1 + i * rec->incr + 12));

		/* obtain connection type */
		अगर (is_e1 || is_e1h) अणु
			/* E1 E1H (bits 4..7) */
			rec->pred_args.val1 &= 0x78;
			rec->pred_args.val1 >>= 3;
		पूर्ण अन्यथा अणु
			/* E2 E3A0 E3B0 (bits 26..29) */
			rec->pred_args.val1 &= 0x1E000000;
			rec->pred_args.val1 >>= 25;
		पूर्ण

		/* get activity counter value */
		rec->pred_args.val2 = REG_RD(bp, rec->reg3 + i * 4);

		/* validate ac value is legal क्रम con_type at idle state */
		अगर (rec->bnx2x_predicate(&rec->pred_args)) अणु
			snम_लिखो(message, MAX_FAIL_MSG,
				 "%s. Values are 0x%x 0x%x\n", rec->fail_msg,
				 rec->pred_args.val1, rec->pred_args.val2);
			bnx2x_self_test_log(bp, rec->severity, message);
		पूर्ण
	पूर्ण
पूर्ण

/* self test procedure
 * scan स्वतः-generated database
 * क्रम each line:
 * 1.	compare chip mask
 * 2.	determine type (according to maro number)
 * 3.	पढ़ो रेजिस्टरs
 * 4.	call predicate
 * 5.	collate results and statistics
 */
पूर्णांक bnx2x_idle_chk(काष्ठा bnx2x *bp)
अणु
	u16 i;				/* loop counter */
	u16 st_ind;			/* self test database access index */
	काष्ठा st_record rec;		/* current record variable */
	अक्षर message[MAX_FAIL_MSG];	/* message to log */

	/*init stats*/
	idle_chk_errors = 0;
	idle_chk_warnings = 0;

	/*create masks क्रम all chip types*/
	is_e1	= CHIP_IS_E1(bp);
	is_e1h	= CHIP_IS_E1H(bp);
	is_e2	= CHIP_IS_E2(bp);
	is_e3a0	= CHIP_IS_E3A0(bp);
	is_e3b0	= CHIP_IS_E3B0(bp);

	/*database मुख्य loop*/
	क्रम (st_ind = 0; st_ind < ST_DB_LINES; st_ind++) अणु
		rec = st_database[st_ind];

		/*check अगर test applies to chip*/
		अगर (!((rec.chip_mask & IDLE_CHK_E1) && is_e1) &&
		    !((rec.chip_mask & IDLE_CHK_E1H) && is_e1h) &&
		    !((rec.chip_mask & IDLE_CHK_E2) && is_e2) &&
		    !((rec.chip_mask & IDLE_CHK_E3A0) && is_e3a0) &&
		    !((rec.chip_mask & IDLE_CHK_E3B0) && is_e3b0))
			जारी;

		/* identअगरy macro */
		चयन (rec.macro) अणु
		हाल 1:
			/* पढ़ो single reg and call predicate */
			rec.pred_args.val1 = REG_RD(bp, rec.reg1);
			DP(BNX2X_MSG_IDLE, "mac1 add %x\n", rec.reg1);
			अगर (rec.bnx2x_predicate(&rec.pred_args)) अणु
				snम_लिखो(message, माप(message),
					 "%s.Value is 0x%x\n", rec.fail_msg,
					 rec.pred_args.val1);
				bnx2x_self_test_log(bp, rec.severity, message);
			पूर्ण
			अवरोध;
		हाल 2:
			/* पढ़ो repeatedly starting from reg1 and call
			 * predicate after each पढ़ो
			 */
			क्रम (i = 0; i < rec.loop; i++) अणु
				rec.pred_args.val1 =
					REG_RD(bp, rec.reg1 + i * rec.incr);
				DP(BNX2X_MSG_IDLE, "mac2 add %x\n", rec.reg1);
				अगर (rec.bnx2x_predicate(&rec.pred_args)) अणु
					snम_लिखो(message, माप(message),
						 "%s. Value is 0x%x in loop %d\n",
						 rec.fail_msg,
						 rec.pred_args.val1, i);
					bnx2x_self_test_log(bp, rec.severity,
							    message);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 3:
			/* पढ़ो two regs and call predicate */
			rec.pred_args.val1 = REG_RD(bp, rec.reg1);
			rec.pred_args.val2 = REG_RD(bp, rec.reg2);
			DP(BNX2X_MSG_IDLE, "mac3 add1 %x add2 %x\n",
			   rec.reg1, rec.reg2);
			अगर (rec.bnx2x_predicate(&rec.pred_args)) अणु
				snम_लिखो(message, माप(message),
					 "%s. Values are 0x%x 0x%x\n",
					 rec.fail_msg, rec.pred_args.val1,
					 rec.pred_args.val2);
				bnx2x_self_test_log(bp, rec.severity, message);
			पूर्ण
			अवरोध;
		हाल 4:
			/*unused to-date*/
			क्रम (i = 0; i < rec.loop; i++) अणु
				rec.pred_args.val1 =
					REG_RD(bp, rec.reg1 + i * rec.incr);
				rec.pred_args.val2 =
					(REG_RD(bp,
						rec.reg2 + i * rec.incr)) >> 1;
				अगर (rec.bnx2x_predicate(&rec.pred_args)) अणु
					snम_लिखो(message, माप(message),
						 "%s. Values are 0x%x 0x%x in loop %d\n",
						 rec.fail_msg,
						 rec.pred_args.val1,
						 rec.pred_args.val2, i);
					bnx2x_self_test_log(bp, rec.severity,
							    message);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 5:
			/* compare two regs, pending
			 * the value of a condition reg
			 */
			rec.pred_args.val1 = REG_RD(bp, rec.reg1);
			rec.pred_args.val2 = REG_RD(bp, rec.reg2);
			DP(BNX2X_MSG_IDLE, "mac3 add1 %x add2 %x add3 %x\n",
			   rec.reg1, rec.reg2, rec.reg3);
			अगर (REG_RD(bp, rec.reg3) != 0) अणु
				अगर (rec.bnx2x_predicate(&rec.pred_args)) अणु
					snम_लिखो(message, माप(message),
						 "%s. Values are 0x%x 0x%x\n",
						 rec.fail_msg,
						 rec.pred_args.val1,
						 rec.pred_args.val2);
					bnx2x_self_test_log(bp, rec.severity,
							    message);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल 6:
			/* compare पढ़ो and ग_लिखो poपूर्णांकers
			 * and पढ़ो and ग_लिखो banks in QM
			 */
			bnx2x_idle_chk6(bp, &rec, message);
			अवरोध;
		हाल 7:
			/* compare cfc info cam with cid cam */
			bnx2x_idle_chk7(bp, &rec, message);
			अवरोध;
		शेष:
			DP(BNX2X_MSG_IDLE,
			   "unknown macro in self test data base. macro %d line %d",
			   rec.macro, st_ind);
		पूर्ण
	पूर्ण

	/* पात अगर पूर्णांकerface is not running */
	अगर (!netअगर_running(bp->dev))
		वापस idle_chk_errors;

	/* वापस value accorindg to statistics */
	अगर (idle_chk_errors == 0) अणु
		DP(BNX2X_MSG_IDLE,
		   "completed successfully (logged %d warnings)\n",
		   idle_chk_warnings);
	पूर्ण अन्यथा अणु
		BNX2X_ERR("failed (with %d errors, %d warnings)\n",
			  idle_chk_errors, idle_chk_warnings);
	पूर्ण
	वापस idle_chk_errors;
पूर्ण
