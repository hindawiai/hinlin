<शैली गुरु>
/* bnx2x_reg.h: Qlogic Everest network driver.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * The रेजिस्टरs description starts with the रेजिस्टर Access type followed
 * by size in bits. For example [RW 32]. The access types are:
 * R  - Read only
 * RC - Clear on पढ़ो
 * RW - Read/Write
 * ST - Statistics रेजिस्टर (clear on पढ़ो)
 * W  - Write only
 * WB - Wide bus रेजिस्टर - the size is over 32 bits and it should be
 *      पढ़ो/ग_लिखो in consecutive 32 bits accesses
 * WR - Write Clear (ग_लिखो 1 to clear the bit)
 *
 */
#अगर_अघोषित BNX2X_REG_H
#घोषणा BNX2X_REG_H

#घोषणा ATC_ATC_INT_STS_REG_ADDRESS_ERROR			 (0x1<<0)
#घोषणा ATC_ATC_INT_STS_REG_ATC_GPA_MULTIPLE_HITS		 (0x1<<2)
#घोषणा ATC_ATC_INT_STS_REG_ATC_IREQ_LESS_THAN_STU		 (0x1<<5)
#घोषणा ATC_ATC_INT_STS_REG_ATC_RCPL_TO_EMPTY_CNT		 (0x1<<3)
#घोषणा ATC_ATC_INT_STS_REG_ATC_TCPL_ERROR			 (0x1<<4)
#घोषणा ATC_ATC_INT_STS_REG_ATC_TCPL_TO_NOT_PEND		 (0x1<<1)
/* [RW 1] Initiate the ATC array - reset all the valid bits */
#घोषणा ATC_REG_ATC_INIT_ARRAY					 0x1100b8
/* [R 1] ATC initialization करोne */
#घोषणा ATC_REG_ATC_INIT_DONE					 0x1100bc
/* [RC 6] Interrupt रेजिस्टर #0 पढ़ो clear */
#घोषणा ATC_REG_ATC_INT_STS_CLR					 0x1101c0
/* [RW 5] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा ATC_REG_ATC_PRTY_MASK					 0x1101d8
/* [R 5] Parity रेजिस्टर #0 पढ़ो */
#घोषणा ATC_REG_ATC_PRTY_STS					 0x1101cc
/* [RC 5] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा ATC_REG_ATC_PRTY_STS_CLR				 0x1101d0
/* [RW 19] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा BRB1_REG_BRB1_INT_MASK					 0x60128
/* [R 19] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा BRB1_REG_BRB1_INT_STS					 0x6011c
/* [RW 4] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा BRB1_REG_BRB1_PRTY_MASK 				 0x60138
/* [R 4] Parity रेजिस्टर #0 पढ़ो */
#घोषणा BRB1_REG_BRB1_PRTY_STS					 0x6012c
/* [RC 4] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा BRB1_REG_BRB1_PRTY_STS_CLR				 0x60130
/* [RW 10] At address BRB1_IND_FREE_LIST_PRS_CRDT initialize मुक्त head. At
 * address BRB1_IND_FREE_LIST_PRS_CRDT+1 initialize मुक्त tail. At address
 * BRB1_IND_FREE_LIST_PRS_CRDT+2 initialize parser initial credit. Warning -
 * following reset the first rbc access to this reg must be ग_लिखो; there can
 * be no more rbc ग_लिखोs after the first one; there can be any number of rbc
 * पढ़ो following the first ग_लिखो; rbc access not following these rules will
 * result in hang condition. */
#घोषणा BRB1_REG_FREE_LIST_PRS_CRDT				 0x60200
/* [RW 10] The number of मुक्त blocks below which the full संकेत to class 0
 * is निश्चितed */
#घोषणा BRB1_REG_FULL_0_XOFF_THRESHOLD_0			 0x601d0
#घोषणा BRB1_REG_FULL_0_XOFF_THRESHOLD_1			 0x60230
/* [RW 11] The number of मुक्त blocks above which the full संकेत to class 0
 * is de-निश्चितed */
#घोषणा BRB1_REG_FULL_0_XON_THRESHOLD_0				 0x601d4
#घोषणा BRB1_REG_FULL_0_XON_THRESHOLD_1				 0x60234
/* [RW 11] The number of मुक्त blocks below which the full संकेत to class 1
 * is निश्चितed */
#घोषणा BRB1_REG_FULL_1_XOFF_THRESHOLD_0			 0x601d8
#घोषणा BRB1_REG_FULL_1_XOFF_THRESHOLD_1			 0x60238
/* [RW 11] The number of मुक्त blocks above which the full संकेत to class 1
 * is de-निश्चितed */
#घोषणा BRB1_REG_FULL_1_XON_THRESHOLD_0				 0x601dc
#घोषणा BRB1_REG_FULL_1_XON_THRESHOLD_1				 0x6023c
/* [RW 11] The number of मुक्त blocks below which the full संकेत to the LB
 * port is निश्चितed */
#घोषणा BRB1_REG_FULL_LB_XOFF_THRESHOLD				 0x601e0
/* [RW 10] The number of मुक्त blocks above which the full संकेत to the LB
 * port is de-निश्चितed */
#घोषणा BRB1_REG_FULL_LB_XON_THRESHOLD				 0x601e4
/* [RW 10] The number of मुक्त blocks above which the High_llfc संकेत to
   पूर्णांकerface #n is de-निश्चितed. */
#घोषणा BRB1_REG_HIGH_LLFC_HIGH_THRESHOLD_0			 0x6014c
/* [RW 10] The number of मुक्त blocks below which the High_llfc संकेत to
   पूर्णांकerface #n is निश्चितed. */
#घोषणा BRB1_REG_HIGH_LLFC_LOW_THRESHOLD_0			 0x6013c
/* [RW 11] The number of blocks guarantied क्रम the LB port */
#घोषणा BRB1_REG_LB_GUARANTIED					 0x601ec
/* [RW 11] The hysteresis on the guarantied buffer space क्रम the Lb port
 * beक्रमe संकेतing XON. */
#घोषणा BRB1_REG_LB_GUARANTIED_HYST				 0x60264
/* [RW 24] LL RAM data. */
#घोषणा BRB1_REG_LL_RAM						 0x61000
/* [RW 10] The number of मुक्त blocks above which the Low_llfc संकेत to
   पूर्णांकerface #n is de-निश्चितed. */
#घोषणा BRB1_REG_LOW_LLFC_HIGH_THRESHOLD_0			 0x6016c
/* [RW 10] The number of मुक्त blocks below which the Low_llfc संकेत to
   पूर्णांकerface #n is निश्चितed. */
#घोषणा BRB1_REG_LOW_LLFC_LOW_THRESHOLD_0			 0x6015c
/* [RW 11] The number of blocks guarantied क्रम class 0 in MAC 0. The
 * रेजिस्टर is applicable only when per_class_guaranty_mode is set. */
#घोषणा BRB1_REG_MAC_0_CLASS_0_GUARANTIED			 0x60244
/* [RW 11] The hysteresis on the guarantied buffer space क्रम class 0 in MAC
 * 1 beक्रमe संकेतing XON. The रेजिस्टर is applicable only when
 * per_class_guaranty_mode is set. */
#घोषणा BRB1_REG_MAC_0_CLASS_0_GUARANTIED_HYST			 0x60254
/* [RW 11] The number of blocks guarantied क्रम class 1 in MAC 0. The
 * रेजिस्टर is applicable only when per_class_guaranty_mode is set. */
#घोषणा BRB1_REG_MAC_0_CLASS_1_GUARANTIED			 0x60248
/* [RW 11] The hysteresis on the guarantied buffer space क्रम class 1in MAC 0
 * beक्रमe संकेतing XON. The रेजिस्टर is applicable only when
 * per_class_guaranty_mode is set. */
#घोषणा BRB1_REG_MAC_0_CLASS_1_GUARANTIED_HYST			 0x60258
/* [RW 11] The number of blocks guarantied क्रम class 0in MAC1.The रेजिस्टर
 * is applicable only when per_class_guaranty_mode is set. */
#घोषणा BRB1_REG_MAC_1_CLASS_0_GUARANTIED			 0x6024c
/* [RW 11] The hysteresis on the guarantied buffer space क्रम class 0 in MAC
 * 1 beक्रमe संकेतing XON. The रेजिस्टर is applicable only when
 * per_class_guaranty_mode is set. */
#घोषणा BRB1_REG_MAC_1_CLASS_0_GUARANTIED_HYST			 0x6025c
/* [RW 11] The number of blocks guarantied क्रम class 1 in MAC 1. The
 * रेजिस्टर is applicable only when per_class_guaranty_mode is set. */
#घोषणा BRB1_REG_MAC_1_CLASS_1_GUARANTIED			 0x60250
/* [RW 11] The hysteresis on the guarantied buffer space क्रम class 1 in MAC
 * 1 beक्रमe संकेतing XON. The रेजिस्टर is applicable only when
 * per_class_guaranty_mode is set. */
#घोषणा BRB1_REG_MAC_1_CLASS_1_GUARANTIED_HYST			 0x60260
/* [RW 11] The number of blocks guarantied क्रम the MAC port. The रेजिस्टर is
 * applicable only when per_class_guaranty_mode is reset. */
#घोषणा BRB1_REG_MAC_GUARANTIED_0				 0x601e8
#घोषणा BRB1_REG_MAC_GUARANTIED_1				 0x60240
/* [R 24] The number of full blocks. */
#घोषणा BRB1_REG_NUM_OF_FULL_BLOCKS				 0x60090
/* [ST 32] The number of cycles that the ग_लिखो_full संकेत towards MAC #0
   was निश्चितed. */
#घोषणा BRB1_REG_NUM_OF_FULL_CYCLES_0				 0x600c8
#घोषणा BRB1_REG_NUM_OF_FULL_CYCLES_1				 0x600cc
#घोषणा BRB1_REG_NUM_OF_FULL_CYCLES_4				 0x600d8
/* [ST 32] The number of cycles that the छोड़ो संकेत towards MAC #0 was
   निश्चितed. */
#घोषणा BRB1_REG_NUM_OF_PAUSE_CYCLES_0				 0x600b8
#घोषणा BRB1_REG_NUM_OF_PAUSE_CYCLES_1				 0x600bc
/* [RW 10] The number of मुक्त blocks below which the छोड़ो संकेत to class 0
 * is निश्चितed */
#घोषणा BRB1_REG_PAUSE_0_XOFF_THRESHOLD_0			 0x601c0
#घोषणा BRB1_REG_PAUSE_0_XOFF_THRESHOLD_1			 0x60220
/* [RW 11] The number of मुक्त blocks above which the छोड़ो संकेत to class 0
 * is de-निश्चितed */
#घोषणा BRB1_REG_PAUSE_0_XON_THRESHOLD_0			 0x601c4
#घोषणा BRB1_REG_PAUSE_0_XON_THRESHOLD_1			 0x60224
/* [RW 11] The number of मुक्त blocks below which the छोड़ो संकेत to class 1
 * is निश्चितed */
#घोषणा BRB1_REG_PAUSE_1_XOFF_THRESHOLD_0			 0x601c8
#घोषणा BRB1_REG_PAUSE_1_XOFF_THRESHOLD_1			 0x60228
/* [RW 11] The number of मुक्त blocks above which the छोड़ो संकेत to class 1
 * is de-निश्चितed */
#घोषणा BRB1_REG_PAUSE_1_XON_THRESHOLD_0			 0x601cc
#घोषणा BRB1_REG_PAUSE_1_XON_THRESHOLD_1			 0x6022c
/* [RW 10] Write client 0: De-निश्चित छोड़ो threshold. Not Functional */
#घोषणा BRB1_REG_PAUSE_HIGH_THRESHOLD_0 			 0x60078
#घोषणा BRB1_REG_PAUSE_HIGH_THRESHOLD_1 			 0x6007c
/* [RW 10] Write client 0: Assert छोड़ो threshold. */
#घोषणा BRB1_REG_PAUSE_LOW_THRESHOLD_0				 0x60068
/* [RW 1] Indicates अगर to use per-class guaranty mode (new mode) or per-MAC
 * guaranty mode (backwards-compatible mode). 0=per-MAC guaranty mode (BC
 * mode). 1=per-class guaranty mode (new mode). */
#घोषणा BRB1_REG_PER_CLASS_GUARANTY_MODE			 0x60268
/* [R 24] The number of full blocks occpied by port. */
#घोषणा BRB1_REG_PORT_NUM_OCC_BLOCKS_0				 0x60094
/* [RW 1] Reset the design by software. */
#घोषणा BRB1_REG_SOFT_RESET					 0x600dc
/* [R 5] Used to पढ़ो the value of the XX protection CAM occupancy counter. */
#घोषणा CCM_REG_CAM_OCCUP					 0xd0188
/* [RW 1] CM - CFC Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा CCM_REG_CCM_CFC_IFEN					 0xd003c
/* [RW 1] CM - QM Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा CCM_REG_CCM_CQM_IFEN					 0xd000c
/* [RW 1] If set the Q index; received from the QM is inserted to event ID.
   Otherwise 0 is inserted. */
#घोषणा CCM_REG_CCM_CQM_USE_Q					 0xd00c0
/* [RW 11] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CCM_REG_CCM_INT_MASK					 0xd01e4
/* [R 11] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा CCM_REG_CCM_INT_STS					 0xd01d8
/* [RW 27] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CCM_REG_CCM_PRTY_MASK					 0xd01f4
/* [R 27] Parity रेजिस्टर #0 पढ़ो */
#घोषणा CCM_REG_CCM_PRTY_STS					 0xd01e8
/* [RC 27] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा CCM_REG_CCM_PRTY_STS_CLR				 0xd01ec
/* [RW 3] The size of AG context region 0 in REG-pairs. Designates the MS
   REG-pair number (e.g. अगर region 0 is 6 REG-pairs; the value should be 5).
   Is used to determine the number of the AG context REG-pairs written back;
   when the input message Reg1WbFlg isn't set. */
#घोषणा CCM_REG_CCM_REG0_SZ					 0xd00c4
/* [RW 1] CM - STORM 0 Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा CCM_REG_CCM_STORM0_IFEN 				 0xd0004
/* [RW 1] CM - STORM 1 Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा CCM_REG_CCM_STORM1_IFEN 				 0xd0008
/* [RW 1] CDU AG पढ़ो Interface enable. If 0 - the request input is
   disregarded; valid output is deनिश्चितed; all other संकेतs are treated as
   usual; अगर 1 - normal activity. */
#घोषणा CCM_REG_CDU_AG_RD_IFEN					 0xd0030
/* [RW 1] CDU AG ग_लिखो Interface enable. If 0 - the request and valid input
   are disregarded; all other संकेतs are treated as usual; अगर 1 - normal
   activity. */
#घोषणा CCM_REG_CDU_AG_WR_IFEN					 0xd002c
/* [RW 1] CDU STORM पढ़ो Interface enable. If 0 - the request input is
   disregarded; valid output is deनिश्चितed; all other संकेतs are treated as
   usual; अगर 1 - normal activity. */
#घोषणा CCM_REG_CDU_SM_RD_IFEN					 0xd0038
/* [RW 1] CDU STORM ग_लिखो Interface enable. If 0 - the request and valid
   input is disregarded; all other संकेतs are treated as usual; अगर 1 -
   normal activity. */
#घोषणा CCM_REG_CDU_SM_WR_IFEN					 0xd0034
/* [RW 4] CFC output initial credit. Max credit available - 15.Write ग_लिखोs
   the initial credit value; पढ़ो वापसs the current value of the credit
   counter. Must be initialized to 1 at start-up. */
#घोषणा CCM_REG_CFC_INIT_CRD					 0xd0204
/* [RW 2] Auxiliary counter flag Q number 1. */
#घोषणा CCM_REG_CNT_AUX1_Q					 0xd00c8
/* [RW 2] Auxiliary counter flag Q number 2. */
#घोषणा CCM_REG_CNT_AUX2_Q					 0xd00cc
/* [RW 28] The CM header value क्रम QM request (primary). */
#घोषणा CCM_REG_CQM_CCM_HDR_P					 0xd008c
/* [RW 28] The CM header value क्रम QM request (secondary). */
#घोषणा CCM_REG_CQM_CCM_HDR_S					 0xd0090
/* [RW 1] QM - CM Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा CCM_REG_CQM_CCM_IFEN					 0xd0014
/* [RW 6] QM output initial credit. Max credit available - 32. Write ग_लिखोs
   the initial credit value; पढ़ो वापसs the current value of the credit
   counter. Must be initialized to 32 at start-up. */
#घोषणा CCM_REG_CQM_INIT_CRD					 0xd020c
/* [RW 3] The weight of the QM (primary) input in the WRR mechanism. 0
   stands क्रम weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा CCM_REG_CQM_P_WEIGHT					 0xd00b8
/* [RW 3] The weight of the QM (secondary) input in the WRR mechanism. 0
   stands क्रम weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा CCM_REG_CQM_S_WEIGHT					 0xd00bc
/* [RW 1] Input SDM Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा CCM_REG_CSDM_IFEN					 0xd0018
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the SDM पूर्णांकerface is detected. */
#घोषणा CCM_REG_CSDM_LENGTH_MIS 				 0xd0170
/* [RW 3] The weight of the SDM input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा CCM_REG_CSDM_WEIGHT					 0xd00b4
/* [RW 28] The CM header क्रम QM क्रमmatting in हाल of an error in the QM
   inमाला_दो. */
#घोषणा CCM_REG_ERR_CCM_HDR					 0xd0094
/* [RW 8] The Event ID in हाल the input message ErrorFlg is set. */
#घोषणा CCM_REG_ERR_EVNT_ID					 0xd0098
/* [RW 8] FIC0 output initial credit. Max credit available - 255. Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 64 at start-up. */
#घोषणा CCM_REG_FIC0_INIT_CRD					 0xd0210
/* [RW 8] FIC1 output initial credit. Max credit available - 255.Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 64 at start-up. */
#घोषणा CCM_REG_FIC1_INIT_CRD					 0xd0214
/* [RW 1] Arbitration between Input Arbiter groups: 0 - fair Round-Robin; 1
   - strict priority defined by ~ccm_रेजिस्टरs_gr_ag_pr.gr_ag_pr;
   ~ccm_रेजिस्टरs_gr_ld0_pr.gr_ld0_pr and
   ~ccm_रेजिस्टरs_gr_ld1_pr.gr_ld1_pr. Groups are according to channels and
   outमाला_दो to STORM: aggregation; load FIC0; load FIC1 and store. */
#घोषणा CCM_REG_GR_ARB_TYPE					 0xd015c
/* [RW 2] Load (FIC0) channel group priority. The lowest priority is 0; the
   highest priority is 3. It is supposed; that the Store channel priority is
   the complement to 4 of the rest priorities - Aggregation channel; Load
   (FIC0) channel and Load (FIC1). */
#घोषणा CCM_REG_GR_LD0_PR					 0xd0164
/* [RW 2] Load (FIC1) channel group priority. The lowest priority is 0; the
   highest priority is 3. It is supposed; that the Store channel priority is
   the complement to 4 of the rest priorities - Aggregation channel; Load
   (FIC0) channel and Load (FIC1). */
#घोषणा CCM_REG_GR_LD1_PR					 0xd0168
/* [RW 2] General flags index. */
#घोषणा CCM_REG_INV_DONE_Q					 0xd0108
/* [RW 4] The number of द्विगुन REG-pairs(128 bits); loaded from the STORM
   context and sent to STORM; क्रम a specअगरic connection type. The द्विगुन
   REG-pairs are used in order to align to STORM context row size of 128
   bits. The offset of these data in the STORM context is always 0. Index
   _(0..15) stands क्रम the connection type (one of 16). */
#घोषणा CCM_REG_N_SM_CTX_LD_0					 0xd004c
#घोषणा CCM_REG_N_SM_CTX_LD_1					 0xd0050
#घोषणा CCM_REG_N_SM_CTX_LD_2					 0xd0054
#घोषणा CCM_REG_N_SM_CTX_LD_3					 0xd0058
#घोषणा CCM_REG_N_SM_CTX_LD_4					 0xd005c
/* [RW 1] Input pbf Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा CCM_REG_PBF_IFEN					 0xd0028
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the pbf पूर्णांकerface is detected. */
#घोषणा CCM_REG_PBF_LENGTH_MIS					 0xd0180
/* [RW 3] The weight of the input pbf in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा CCM_REG_PBF_WEIGHT					 0xd00ac
#घोषणा CCM_REG_PHYS_QNUM1_0					 0xd0134
#घोषणा CCM_REG_PHYS_QNUM1_1					 0xd0138
#घोषणा CCM_REG_PHYS_QNUM2_0					 0xd013c
#घोषणा CCM_REG_PHYS_QNUM2_1					 0xd0140
#घोषणा CCM_REG_PHYS_QNUM3_0					 0xd0144
#घोषणा CCM_REG_PHYS_QNUM3_1					 0xd0148
#घोषणा CCM_REG_QOS_PHYS_QNUM0_0				 0xd0114
#घोषणा CCM_REG_QOS_PHYS_QNUM0_1				 0xd0118
#घोषणा CCM_REG_QOS_PHYS_QNUM1_0				 0xd011c
#घोषणा CCM_REG_QOS_PHYS_QNUM1_1				 0xd0120
#घोषणा CCM_REG_QOS_PHYS_QNUM2_0				 0xd0124
#घोषणा CCM_REG_QOS_PHYS_QNUM2_1				 0xd0128
#घोषणा CCM_REG_QOS_PHYS_QNUM3_0				 0xd012c
#घोषणा CCM_REG_QOS_PHYS_QNUM3_1				 0xd0130
/* [RW 1] STORM - CM Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा CCM_REG_STORM_CCM_IFEN					 0xd0010
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the STORM पूर्णांकerface is detected. */
#घोषणा CCM_REG_STORM_LENGTH_MIS				 0xd016c
/* [RW 3] The weight of the STORM input in the WRR (Weighted Round robin)
   mechanism. 0 stands क्रम weight 8 (the most prioritised); 1 stands क्रम
   weight 1(least prioritised); 2 stands क्रम weight 2 (more prioritised);
   tc. */
#घोषणा CCM_REG_STORM_WEIGHT					 0xd009c
/* [RW 1] Input tsem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा CCM_REG_TSEM_IFEN					 0xd001c
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the tsem पूर्णांकerface is detected. */
#घोषणा CCM_REG_TSEM_LENGTH_MIS 				 0xd0174
/* [RW 3] The weight of the input tsem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा CCM_REG_TSEM_WEIGHT					 0xd00a0
/* [RW 1] Input usem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा CCM_REG_USEM_IFEN					 0xd0024
/* [RC 1] Set when message length mismatch (relative to last indication) at
   the usem पूर्णांकerface is detected. */
#घोषणा CCM_REG_USEM_LENGTH_MIS 				 0xd017c
/* [RW 3] The weight of the input usem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा CCM_REG_USEM_WEIGHT					 0xd00a8
/* [RW 1] Input xsem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा CCM_REG_XSEM_IFEN					 0xd0020
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the xsem पूर्णांकerface is detected. */
#घोषणा CCM_REG_XSEM_LENGTH_MIS 				 0xd0178
/* [RW 3] The weight of the input xsem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा CCM_REG_XSEM_WEIGHT					 0xd00a4
/* [RW 19] Indirect access to the descriptor table of the XX protection
   mechanism. The fields are: [5:0] - message length; [12:6] - message
   poपूर्णांकer; 18:13] - next poपूर्णांकer. */
#घोषणा CCM_REG_XX_DESCR_TABLE					 0xd0300
#घोषणा CCM_REG_XX_DESCR_TABLE_SIZE				 24
/* [R 7] Used to पढ़ो the value of XX protection Free counter. */
#घोषणा CCM_REG_XX_FREE 					 0xd0184
/* [RW 6] Initial value क्रम the credit counter; responsible क्रम fulfilling
   of the Input Stage XX protection buffer by the XX protection pending
   messages. Max credit available - 127. Write ग_लिखोs the initial credit
   value; पढ़ो वापसs the current value of the credit counter. Must be
   initialized to maximum XX रक्षित message size - 2 at start-up. */
#घोषणा CCM_REG_XX_INIT_CRD					 0xd0220
/* [RW 7] The maximum number of pending messages; which may be stored in XX
   protection. At पढ़ो the ~ccm_रेजिस्टरs_xx_मुक्त.xx_मुक्त counter is पढ़ो.
   At ग_लिखो comprises the start value of the ~ccm_रेजिस्टरs_xx_मुक्त.xx_मुक्त
   counter. */
#घोषणा CCM_REG_XX_MSG_NUM					 0xd0224
/* [RW 8] The Event ID; sent to the STORM in हाल of XX overflow. */
#घोषणा CCM_REG_XX_OVFL_EVNT_ID 				 0xd0044
/* [RW 18] Indirect access to the XX table of the XX protection mechanism.
   The fields are: [5:0] - tail poपूर्णांकer; 11:6] - Link List size; 17:12] -
   header poपूर्णांकer. */
#घोषणा CCM_REG_XX_TABLE					 0xd0280
#घोषणा CDU_REG_CDU_CHK_MASK0					 0x101000
#घोषणा CDU_REG_CDU_CHK_MASK1					 0x101004
#घोषणा CDU_REG_CDU_CONTROL0					 0x101008
#घोषणा CDU_REG_CDU_DEBUG					 0x101010
#घोषणा CDU_REG_CDU_GLOBAL_PARAMS				 0x101020
/* [RW 7] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CDU_REG_CDU_INT_MASK					 0x10103c
/* [R 7] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा CDU_REG_CDU_INT_STS					 0x101030
/* [RW 5] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CDU_REG_CDU_PRTY_MASK					 0x10104c
/* [R 5] Parity रेजिस्टर #0 पढ़ो */
#घोषणा CDU_REG_CDU_PRTY_STS					 0x101040
/* [RC 5] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा CDU_REG_CDU_PRTY_STS_CLR				 0x101044
/* [RC 32] logging of error data in हाल of a CDU load error:
   अणुexpected_cid[15:0]; xpected_type[2:0]; xpected_region[2:0]; ctive_error;
   ype_error; ctual_active; ctual_compressed_contextपूर्ण; */
#घोषणा CDU_REG_ERROR_DATA					 0x101014
/* [WB 216] L1TT ram access. each entry has the following क्रमmat :
   अणुmrege_regions[7:0]; ffset12[5:0]...offset0[5:0];
   ength12[5:0]...length0[5:0]; d12[3:0]...id0[3:0]पूर्ण */
#घोषणा CDU_REG_L1TT						 0x101800
/* [WB 24] MATT ram access. each entry has the following
   क्रमmat:अणुRegionLength[11:0]; egionOffset[11:0]पूर्ण */
#घोषणा CDU_REG_MATT						 0x101100
/* [RW 1] when this bit is set the CDU operates in e1hmf mode */
#घोषणा CDU_REG_MF_MODE 					 0x101050
/* [R 1] indication the initializing the activity counter by the hardware
   was करोne. */
#घोषणा CFC_REG_AC_INIT_DONE					 0x104078
/* [RW 13] activity counter ram access */
#घोषणा CFC_REG_ACTIVITY_COUNTER				 0x104400
#घोषणा CFC_REG_ACTIVITY_COUNTER_SIZE				 256
/* [R 1] indication the initializing the cams by the hardware was करोne. */
#घोषणा CFC_REG_CAM_INIT_DONE					 0x10407c
/* [RW 2] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CFC_REG_CFC_INT_MASK					 0x104108
/* [R 2] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा CFC_REG_CFC_INT_STS					 0x1040fc
/* [RC 2] Interrupt रेजिस्टर #0 पढ़ो clear */
#घोषणा CFC_REG_CFC_INT_STS_CLR 				 0x104100
/* [RW 4] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CFC_REG_CFC_PRTY_MASK					 0x104118
/* [R 4] Parity रेजिस्टर #0 पढ़ो */
#घोषणा CFC_REG_CFC_PRTY_STS					 0x10410c
/* [RC 4] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा CFC_REG_CFC_PRTY_STS_CLR				 0x104110
/* [RW 21] CID cam access (21:1 - Data; alid - 0) */
#घोषणा CFC_REG_CID_CAM 					 0x104800
#घोषणा CFC_REG_CONTROL0					 0x104028
#घोषणा CFC_REG_DEBUG0						 0x104050
/* [RW 14] indicates per error (in #cfc_रेजिस्टरs_cfc_error_vector.cfc_error
   vector) whether the cfc should be disabled upon it */
#घोषणा CFC_REG_DISABLE_ON_ERROR				 0x104044
/* [RC 14] CFC error vector. when the CFC detects an पूर्णांकernal error it will
   set one of these bits. the bit description can be found in CFC
   specअगरications */
#घोषणा CFC_REG_ERROR_VECTOR					 0x10403c
/* [WB 93] LCID info ram access */
#घोषणा CFC_REG_INFO_RAM					 0x105000
#घोषणा CFC_REG_INFO_RAM_SIZE					 1024
#घोषणा CFC_REG_INIT_REG					 0x10404c
#घोषणा CFC_REG_INTERFACES					 0x104058
/* [RW 24] अणुweight_load_client7[2:0] to weight_load_client0[2:0]पूर्ण. this
   field allows changing the priorities of the weighted-round-robin arbiter
   which selects which CFC load client should be served next */
#घोषणा CFC_REG_LCREQ_WEIGHTS					 0x104084
/* [RW 16] Link List ram access; data = अणुprev_lcid; ext_lcidपूर्ण */
#घोषणा CFC_REG_LINK_LIST					 0x104c00
#घोषणा CFC_REG_LINK_LIST_SIZE					 256
/* [R 1] indication the initializing the link list by the hardware was करोne. */
#घोषणा CFC_REG_LL_INIT_DONE					 0x104074
/* [R 9] Number of allocated LCIDs which are at empty state */
#घोषणा CFC_REG_NUM_LCIDS_ALLOC 				 0x104020
/* [R 9] Number of Arriving LCIDs in Link List Block */
#घोषणा CFC_REG_NUM_LCIDS_ARRIVING				 0x104004
#घोषणा CFC_REG_NUM_LCIDS_INSIDE_PF				 0x104120
/* [R 9] Number of Leaving LCIDs in Link List Block */
#घोषणा CFC_REG_NUM_LCIDS_LEAVING				 0x104018
#घोषणा CFC_REG_WEAK_ENABLE_PF					 0x104124
/* [RW 8] The event id क्रम aggregated पूर्णांकerrupt 0 */
#घोषणा CSDM_REG_AGG_INT_EVENT_0				 0xc2038
#घोषणा CSDM_REG_AGG_INT_EVENT_10				 0xc2060
#घोषणा CSDM_REG_AGG_INT_EVENT_11				 0xc2064
#घोषणा CSDM_REG_AGG_INT_EVENT_12				 0xc2068
#घोषणा CSDM_REG_AGG_INT_EVENT_13				 0xc206c
#घोषणा CSDM_REG_AGG_INT_EVENT_14				 0xc2070
#घोषणा CSDM_REG_AGG_INT_EVENT_15				 0xc2074
#घोषणा CSDM_REG_AGG_INT_EVENT_16				 0xc2078
#घोषणा CSDM_REG_AGG_INT_EVENT_2				 0xc2040
#घोषणा CSDM_REG_AGG_INT_EVENT_3				 0xc2044
#घोषणा CSDM_REG_AGG_INT_EVENT_4				 0xc2048
#घोषणा CSDM_REG_AGG_INT_EVENT_5				 0xc204c
#घोषणा CSDM_REG_AGG_INT_EVENT_6				 0xc2050
#घोषणा CSDM_REG_AGG_INT_EVENT_7				 0xc2054
#घोषणा CSDM_REG_AGG_INT_EVENT_8				 0xc2058
#घोषणा CSDM_REG_AGG_INT_EVENT_9				 0xc205c
/* [RW 1] For each aggregated पूर्णांकerrupt index whether the mode is normal (0)
   or स्वतः-mask-mode (1) */
#घोषणा CSDM_REG_AGG_INT_MODE_10				 0xc21e0
#घोषणा CSDM_REG_AGG_INT_MODE_11				 0xc21e4
#घोषणा CSDM_REG_AGG_INT_MODE_12				 0xc21e8
#घोषणा CSDM_REG_AGG_INT_MODE_13				 0xc21ec
#घोषणा CSDM_REG_AGG_INT_MODE_14				 0xc21f0
#घोषणा CSDM_REG_AGG_INT_MODE_15				 0xc21f4
#घोषणा CSDM_REG_AGG_INT_MODE_16				 0xc21f8
#घोषणा CSDM_REG_AGG_INT_MODE_6 				 0xc21d0
#घोषणा CSDM_REG_AGG_INT_MODE_7 				 0xc21d4
#घोषणा CSDM_REG_AGG_INT_MODE_8 				 0xc21d8
#घोषणा CSDM_REG_AGG_INT_MODE_9 				 0xc21dc
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the cfc_rsp lcid */
#घोषणा CSDM_REG_CFC_RSP_START_ADDR				 0xc2008
/* [RW 16] The maximum value of the completion counter #0 */
#घोषणा CSDM_REG_CMP_COUNTER_MAX0				 0xc201c
/* [RW 16] The maximum value of the completion counter #1 */
#घोषणा CSDM_REG_CMP_COUNTER_MAX1				 0xc2020
/* [RW 16] The maximum value of the completion counter #2 */
#घोषणा CSDM_REG_CMP_COUNTER_MAX2				 0xc2024
/* [RW 16] The maximum value of the completion counter #3 */
#घोषणा CSDM_REG_CMP_COUNTER_MAX3				 0xc2028
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the completion
   counters. */
#घोषणा CSDM_REG_CMP_COUNTER_START_ADDR 			 0xc200c
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CSDM_REG_CSDM_INT_MASK_0				 0xc229c
#घोषणा CSDM_REG_CSDM_INT_MASK_1				 0xc22ac
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा CSDM_REG_CSDM_INT_STS_0 				 0xc2290
#घोषणा CSDM_REG_CSDM_INT_STS_1 				 0xc22a0
/* [RW 11] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CSDM_REG_CSDM_PRTY_MASK 				 0xc22bc
/* [R 11] Parity रेजिस्टर #0 पढ़ो */
#घोषणा CSDM_REG_CSDM_PRTY_STS					 0xc22b0
/* [RC 11] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा CSDM_REG_CSDM_PRTY_STS_CLR				 0xc22b4
#घोषणा CSDM_REG_ENABLE_IN1					 0xc2238
#घोषणा CSDM_REG_ENABLE_IN2					 0xc223c
#घोषणा CSDM_REG_ENABLE_OUT1					 0xc2240
#घोषणा CSDM_REG_ENABLE_OUT2					 0xc2244
/* [RW 4] The initial number of messages that can be sent to the pxp control
   पूर्णांकerface without receiving any ACK. */
#घोषणा CSDM_REG_INIT_CREDIT_PXP_CTRL				 0xc24bc
/* [ST 32] The number of ACK after placement messages received */
#घोषणा CSDM_REG_NUM_OF_ACK_AFTER_PLACE 			 0xc227c
/* [ST 32] The number of packet end messages received from the parser */
#घोषणा CSDM_REG_NUM_OF_PKT_END_MSG				 0xc2274
/* [ST 32] The number of requests received from the pxp async अगर */
#घोषणा CSDM_REG_NUM_OF_PXP_ASYNC_REQ				 0xc2278
/* [ST 32] The number of commands received in queue 0 */
#घोषणा CSDM_REG_NUM_OF_Q0_CMD					 0xc2248
/* [ST 32] The number of commands received in queue 10 */
#घोषणा CSDM_REG_NUM_OF_Q10_CMD 				 0xc226c
/* [ST 32] The number of commands received in queue 11 */
#घोषणा CSDM_REG_NUM_OF_Q11_CMD 				 0xc2270
/* [ST 32] The number of commands received in queue 1 */
#घोषणा CSDM_REG_NUM_OF_Q1_CMD					 0xc224c
/* [ST 32] The number of commands received in queue 3 */
#घोषणा CSDM_REG_NUM_OF_Q3_CMD					 0xc2250
/* [ST 32] The number of commands received in queue 4 */
#घोषणा CSDM_REG_NUM_OF_Q4_CMD					 0xc2254
/* [ST 32] The number of commands received in queue 5 */
#घोषणा CSDM_REG_NUM_OF_Q5_CMD					 0xc2258
/* [ST 32] The number of commands received in queue 6 */
#घोषणा CSDM_REG_NUM_OF_Q6_CMD					 0xc225c
/* [ST 32] The number of commands received in queue 7 */
#घोषणा CSDM_REG_NUM_OF_Q7_CMD					 0xc2260
/* [ST 32] The number of commands received in queue 8 */
#घोषणा CSDM_REG_NUM_OF_Q8_CMD					 0xc2264
/* [ST 32] The number of commands received in queue 9 */
#घोषणा CSDM_REG_NUM_OF_Q9_CMD					 0xc2268
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम queue counters */
#घोषणा CSDM_REG_Q_COUNTER_START_ADDR				 0xc2010
/* [R 1] pxp_ctrl rd_data fअगरo empty in sdm_dma_rsp block */
#घोषणा CSDM_REG_RSP_PXP_CTRL_RDATA_EMPTY			 0xc2548
/* [R 1] parser fअगरo empty in sdm_sync block */
#घोषणा CSDM_REG_SYNC_PARSER_EMPTY				 0xc2550
/* [R 1] parser serial fअगरo empty in sdm_sync block */
#घोषणा CSDM_REG_SYNC_SYNC_EMPTY				 0xc2558
/* [RW 32] Tick क्रम समयr counter. Applicable only when
   ~csdm_रेजिस्टरs_समयr_tick_enable.समयr_tick_enable =1 */
#घोषणा CSDM_REG_TIMER_TICK					 0xc2000
/* [RW 5] The number of समय_slots in the arbitration cycle */
#घोषणा CSEM_REG_ARB_CYCLE_SIZE 				 0x200034
/* [RW 3] The source that is associated with arbitration element 0. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2 */
#घोषणा CSEM_REG_ARB_ELEMENT0					 0x200020
/* [RW 3] The source that is associated with arbitration element 1. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~csem_रेजिस्टरs_arb_element0.arb_element0 */
#घोषणा CSEM_REG_ARB_ELEMENT1					 0x200024
/* [RW 3] The source that is associated with arbitration element 2. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~csem_रेजिस्टरs_arb_element0.arb_element0
   and ~csem_रेजिस्टरs_arb_element1.arb_element1 */
#घोषणा CSEM_REG_ARB_ELEMENT2					 0x200028
/* [RW 3] The source that is associated with arbitration element 3. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.Could
   not be equal to रेजिस्टर ~csem_रेजिस्टरs_arb_element0.arb_element0 and
   ~csem_रेजिस्टरs_arb_element1.arb_element1 and
   ~csem_रेजिस्टरs_arb_element2.arb_element2 */
#घोषणा CSEM_REG_ARB_ELEMENT3					 0x20002c
/* [RW 3] The source that is associated with arbitration element 4. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~csem_रेजिस्टरs_arb_element0.arb_element0
   and ~csem_रेजिस्टरs_arb_element1.arb_element1 and
   ~csem_रेजिस्टरs_arb_element2.arb_element2 and
   ~csem_रेजिस्टरs_arb_element3.arb_element3 */
#घोषणा CSEM_REG_ARB_ELEMENT4					 0x200030
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CSEM_REG_CSEM_INT_MASK_0				 0x200110
#घोषणा CSEM_REG_CSEM_INT_MASK_1				 0x200120
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा CSEM_REG_CSEM_INT_STS_0 				 0x200104
#घोषणा CSEM_REG_CSEM_INT_STS_1 				 0x200114
/* [RW 32] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा CSEM_REG_CSEM_PRTY_MASK_0				 0x200130
#घोषणा CSEM_REG_CSEM_PRTY_MASK_1				 0x200140
/* [R 32] Parity रेजिस्टर #0 पढ़ो */
#घोषणा CSEM_REG_CSEM_PRTY_STS_0				 0x200124
#घोषणा CSEM_REG_CSEM_PRTY_STS_1				 0x200134
/* [RC 32] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा CSEM_REG_CSEM_PRTY_STS_CLR_0				 0x200128
#घोषणा CSEM_REG_CSEM_PRTY_STS_CLR_1				 0x200138
#घोषणा CSEM_REG_ENABLE_IN					 0x2000a4
#घोषणा CSEM_REG_ENABLE_OUT					 0x2000a8
/* [RW 32] This address space contains all रेजिस्टरs and memories that are
   placed in SEM_FAST block. The SEM_FAST रेजिस्टरs are described in
   appendix B. In order to access the sem_fast रेजिस्टरs the base address
   ~fast_memory.fast_memory should be added to eachsem_fast रेजिस्टर offset. */
#घोषणा CSEM_REG_FAST_MEMORY					 0x220000
/* [RW 1] Disables input messages from FIC0 May be updated during run_समय
   by the microcode */
#घोषणा CSEM_REG_FIC0_DISABLE					 0x200224
/* [RW 1] Disables input messages from FIC1 May be updated during run_समय
   by the microcode */
#घोषणा CSEM_REG_FIC1_DISABLE					 0x200234
/* [RW 15] Interrupt table Read and ग_लिखो access to it is not possible in
   the middle of the work */
#घोषणा CSEM_REG_INT_TABLE					 0x200400
/* [ST 24] Statistics रेजिस्टर. The number of messages that entered through
   FIC0 */
#घोषणा CSEM_REG_MSG_NUM_FIC0					 0x200000
/* [ST 24] Statistics रेजिस्टर. The number of messages that entered through
   FIC1 */
#घोषणा CSEM_REG_MSG_NUM_FIC1					 0x200004
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC0 */
#घोषणा CSEM_REG_MSG_NUM_FOC0					 0x200008
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC1 */
#घोषणा CSEM_REG_MSG_NUM_FOC1					 0x20000c
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC2 */
#घोषणा CSEM_REG_MSG_NUM_FOC2					 0x200010
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC3 */
#घोषणा CSEM_REG_MSG_NUM_FOC3					 0x200014
/* [RW 1] Disables input messages from the passive buffer May be updated
   during run_समय by the microcode */
#घोषणा CSEM_REG_PAS_DISABLE					 0x20024c
/* [WB 128] Debug only. Passive buffer memory */
#घोषणा CSEM_REG_PASSIVE_BUFFER 				 0x202000
/* [WB 46] pram memory. B45 is parity; b[44:0] - data. */
#घोषणा CSEM_REG_PRAM						 0x240000
/* [R 16] Valid sleeping thपढ़ोs indication have bit per thपढ़ो */
#घोषणा CSEM_REG_SLEEP_THREADS_VALID				 0x20026c
/* [R 1] EXT_STORE FIFO is empty in sem_slow_ls_ext */
#घोषणा CSEM_REG_SLOW_EXT_STORE_EMPTY				 0x2002a0
/* [RW 16] List of मुक्त thपढ़ोs . There is a bit per thपढ़ो. */
#घोषणा CSEM_REG_THREADS_LIST					 0x2002e4
/* [RW 3] The arbitration scheme of समय_slot 0 */
#घोषणा CSEM_REG_TS_0_AS					 0x200038
/* [RW 3] The arbitration scheme of समय_slot 10 */
#घोषणा CSEM_REG_TS_10_AS					 0x200060
/* [RW 3] The arbitration scheme of समय_slot 11 */
#घोषणा CSEM_REG_TS_11_AS					 0x200064
/* [RW 3] The arbitration scheme of समय_slot 12 */
#घोषणा CSEM_REG_TS_12_AS					 0x200068
/* [RW 3] The arbitration scheme of समय_slot 13 */
#घोषणा CSEM_REG_TS_13_AS					 0x20006c
/* [RW 3] The arbitration scheme of समय_slot 14 */
#घोषणा CSEM_REG_TS_14_AS					 0x200070
/* [RW 3] The arbitration scheme of समय_slot 15 */
#घोषणा CSEM_REG_TS_15_AS					 0x200074
/* [RW 3] The arbitration scheme of समय_slot 16 */
#घोषणा CSEM_REG_TS_16_AS					 0x200078
/* [RW 3] The arbitration scheme of समय_slot 17 */
#घोषणा CSEM_REG_TS_17_AS					 0x20007c
/* [RW 3] The arbitration scheme of समय_slot 18 */
#घोषणा CSEM_REG_TS_18_AS					 0x200080
/* [RW 3] The arbitration scheme of समय_slot 1 */
#घोषणा CSEM_REG_TS_1_AS					 0x20003c
/* [RW 3] The arbitration scheme of समय_slot 2 */
#घोषणा CSEM_REG_TS_2_AS					 0x200040
/* [RW 3] The arbitration scheme of समय_slot 3 */
#घोषणा CSEM_REG_TS_3_AS					 0x200044
/* [RW 3] The arbitration scheme of समय_slot 4 */
#घोषणा CSEM_REG_TS_4_AS					 0x200048
/* [RW 3] The arbitration scheme of समय_slot 5 */
#घोषणा CSEM_REG_TS_5_AS					 0x20004c
/* [RW 3] The arbitration scheme of समय_slot 6 */
#घोषणा CSEM_REG_TS_6_AS					 0x200050
/* [RW 3] The arbitration scheme of समय_slot 7 */
#घोषणा CSEM_REG_TS_7_AS					 0x200054
/* [RW 3] The arbitration scheme of समय_slot 8 */
#घोषणा CSEM_REG_TS_8_AS					 0x200058
/* [RW 3] The arbitration scheme of समय_slot 9 */
#घोषणा CSEM_REG_TS_9_AS					 0x20005c
/* [W 7] VF or PF ID क्रम reset error bit. Values 0-63 reset error bit क्रम 64
 * VF; values 64-67 reset error क्रम 4 PF; values 68-127 are not valid. */
#घोषणा CSEM_REG_VFPF_ERR_NUM					 0x200380
/* [RW 1] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा DBG_REG_DBG_PRTY_MASK					 0xc0a8
/* [R 1] Parity रेजिस्टर #0 पढ़ो */
#घोषणा DBG_REG_DBG_PRTY_STS					 0xc09c
/* [RC 1] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा DBG_REG_DBG_PRTY_STS_CLR				 0xc0a0
/* [RW 1] When set the DMAE will process the commands as in E1.5. 1.The
 * function that is used is always SRC-PCI; 2.VF_Valid = 0; 3.VFID=0;
 * 4.Completion function=0; 5.Error handling=0 */
#घोषणा DMAE_REG_BACKWARD_COMP_EN				 0x10207c
/* [RW 32] Commands memory. The address to command X; row Y is to calculated
   as 14*X+Y. */
#घोषणा DMAE_REG_CMD_MEM					 0x102400
#घोषणा DMAE_REG_CMD_MEM_SIZE					 224
/* [RW 1] If 0 - the CRC-16c initial value is all zeroes; अगर 1 - the CRC-16c
   initial value is all ones. */
#घोषणा DMAE_REG_CRC16C_INIT					 0x10201c
/* [RW 1] If 0 - the CRC-16 T10 initial value is all zeroes; अगर 1 - the
   CRC-16 T10 initial value is all ones. */
#घोषणा DMAE_REG_CRC16T10_INIT					 0x102020
/* [RW 2] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा DMAE_REG_DMAE_INT_MASK					 0x102054
/* [RW 4] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा DMAE_REG_DMAE_PRTY_MASK 				 0x102064
/* [R 4] Parity रेजिस्टर #0 पढ़ो */
#घोषणा DMAE_REG_DMAE_PRTY_STS					 0x102058
/* [RC 4] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा DMAE_REG_DMAE_PRTY_STS_CLR				 0x10205c
/* [RW 1] Command 0 go. */
#घोषणा DMAE_REG_GO_C0						 0x102080
/* [RW 1] Command 1 go. */
#घोषणा DMAE_REG_GO_C1						 0x102084
/* [RW 1] Command 10 go. */
#घोषणा DMAE_REG_GO_C10 					 0x102088
/* [RW 1] Command 11 go. */
#घोषणा DMAE_REG_GO_C11 					 0x10208c
/* [RW 1] Command 12 go. */
#घोषणा DMAE_REG_GO_C12 					 0x102090
/* [RW 1] Command 13 go. */
#घोषणा DMAE_REG_GO_C13 					 0x102094
/* [RW 1] Command 14 go. */
#घोषणा DMAE_REG_GO_C14 					 0x102098
/* [RW 1] Command 15 go. */
#घोषणा DMAE_REG_GO_C15 					 0x10209c
/* [RW 1] Command 2 go. */
#घोषणा DMAE_REG_GO_C2						 0x1020a0
/* [RW 1] Command 3 go. */
#घोषणा DMAE_REG_GO_C3						 0x1020a4
/* [RW 1] Command 4 go. */
#घोषणा DMAE_REG_GO_C4						 0x1020a8
/* [RW 1] Command 5 go. */
#घोषणा DMAE_REG_GO_C5						 0x1020ac
/* [RW 1] Command 6 go. */
#घोषणा DMAE_REG_GO_C6						 0x1020b0
/* [RW 1] Command 7 go. */
#घोषणा DMAE_REG_GO_C7						 0x1020b4
/* [RW 1] Command 8 go. */
#घोषणा DMAE_REG_GO_C8						 0x1020b8
/* [RW 1] Command 9 go. */
#घोषणा DMAE_REG_GO_C9						 0x1020bc
/* [RW 1] DMAE GRC Interface (Target; aster) enable. If 0 - the acknowledge
   input is disregarded; valid is deनिश्चितed; all other संकेतs are treated
   as usual; अगर 1 - normal activity. */
#घोषणा DMAE_REG_GRC_IFEN					 0x102008
/* [RW 1] DMAE PCI Interface (Request; ead; rite) enable. If 0 - the
   acknowledge input is disregarded; valid is deनिश्चितed; full is निश्चितed;
   all other संकेतs are treated as usual; अगर 1 - normal activity. */
#घोषणा DMAE_REG_PCI_IFEN					 0x102004
/* [RW 4] DMAE- PCI Request Interface initial credit. Write ग_लिखोs the
   initial value to the credit counter; related to the address. Read वापसs
   the current value of the counter. */
#घोषणा DMAE_REG_PXP_REQ_INIT_CRD				 0x1020c0
/* [RW 8] Aggregation command. */
#घोषणा DORQ_REG_AGG_CMD0					 0x170060
/* [RW 8] Aggregation command. */
#घोषणा DORQ_REG_AGG_CMD1					 0x170064
/* [RW 8] Aggregation command. */
#घोषणा DORQ_REG_AGG_CMD2					 0x170068
/* [RW 8] Aggregation command. */
#घोषणा DORQ_REG_AGG_CMD3					 0x17006c
/* [RW 28] UCM Header. */
#घोषणा DORQ_REG_CMHEAD_RX					 0x170050
/* [RW 32] Doorbell address क्रम RBC करोorbells (function 0). */
#घोषणा DORQ_REG_DB_ADDR0					 0x17008c
/* [RW 5] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा DORQ_REG_DORQ_INT_MASK					 0x170180
/* [R 5] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा DORQ_REG_DORQ_INT_STS					 0x170174
/* [RC 5] Interrupt रेजिस्टर #0 पढ़ो clear */
#घोषणा DORQ_REG_DORQ_INT_STS_CLR				 0x170178
/* [RW 2] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा DORQ_REG_DORQ_PRTY_MASK 				 0x170190
/* [R 2] Parity रेजिस्टर #0 पढ़ो */
#घोषणा DORQ_REG_DORQ_PRTY_STS					 0x170184
/* [RC 2] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा DORQ_REG_DORQ_PRTY_STS_CLR				 0x170188
/* [RW 8] The address to ग_लिखो the DPM CID to STORM. */
#घोषणा DORQ_REG_DPM_CID_ADDR					 0x170044
/* [RW 5] The DPM mode CID extraction offset. */
#घोषणा DORQ_REG_DPM_CID_OFST					 0x170030
/* [RW 12] The threshold of the DQ FIFO to send the almost full पूर्णांकerrupt. */
#घोषणा DORQ_REG_DQ_FIFO_AFULL_TH				 0x17007c
/* [RW 12] The threshold of the DQ FIFO to send the full पूर्णांकerrupt. */
#घोषणा DORQ_REG_DQ_FIFO_FULL_TH				 0x170078
/* [R 13] Current value of the DQ FIFO fill level according to following
   poपूर्णांकer. The range is 0 - 256 FIFO rows; where each row stands क्रम the
   करोorbell. */
#घोषणा DORQ_REG_DQ_FILL_LVLF					 0x1700a4
/* [R 1] DQ FIFO full status. Is set; when FIFO filling level is more or
   equal to full threshold; reset on full clear. */
#घोषणा DORQ_REG_DQ_FULL_ST					 0x1700c0
/* [RW 28] The value sent to CM header in the हाल of CFC load error. */
#घोषणा DORQ_REG_ERR_CMHEAD					 0x170058
#घोषणा DORQ_REG_IF_EN						 0x170004
#घोषणा DORQ_REG_MAX_RVFID_SIZE				 0x1701ec
#घोषणा DORQ_REG_MODE_ACT					 0x170008
/* [RW 5] The normal mode CID extraction offset. */
#घोषणा DORQ_REG_NORM_CID_OFST					 0x17002c
/* [RW 28] TCM Header when only TCP context is loaded. */
#घोषणा DORQ_REG_NORM_CMHEAD_TX 				 0x17004c
/* [RW 3] The number of simultaneous outstanding requests to Context Fetch
   Interface. */
#घोषणा DORQ_REG_OUTST_REQ					 0x17003c
#घोषणा DORQ_REG_PF_USAGE_CNT					 0x1701d0
#घोषणा DORQ_REG_REGN						 0x170038
/* [R 4] Current value of response A counter credit. Initial credit is
   configured through ग_लिखो to ~करोrq_रेजिस्टरs_rsp_init_crd.rsp_init_crd
   रेजिस्टर. */
#घोषणा DORQ_REG_RSPA_CRD_CNT					 0x1700ac
/* [R 4] Current value of response B counter credit. Initial credit is
   configured through ग_लिखो to ~करोrq_रेजिस्टरs_rsp_init_crd.rsp_init_crd
   रेजिस्टर. */
#घोषणा DORQ_REG_RSPB_CRD_CNT					 0x1700b0
/* [RW 4] The initial credit at the Doorbell Response Interface. The ग_लिखो
   ग_लिखोs the same initial credit to the rspa_crd_cnt and rspb_crd_cnt. The
   पढ़ो पढ़ोs this written value. */
#घोषणा DORQ_REG_RSP_INIT_CRD					 0x170048
#घोषणा DORQ_REG_RSPB_CRD_CNT					 0x1700b0
#घोषणा DORQ_REG_VF_NORM_CID_BASE				 0x1701a0
#घोषणा DORQ_REG_VF_NORM_CID_OFST				 0x1701f4
#घोषणा DORQ_REG_VF_NORM_CID_WND_SIZE				 0x1701a4
#घोषणा DORQ_REG_VF_NORM_MAX_CID_COUNT				 0x1701e4
#घोषणा DORQ_REG_VF_NORM_VF_BASE				 0x1701a8
/* [RW 10] VF type validation mask value */
#घोषणा DORQ_REG_VF_TYPE_MASK_0					 0x170218
/* [RW 17] VF type validation Min MCID value */
#घोषणा DORQ_REG_VF_TYPE_MAX_MCID_0				 0x1702d8
/* [RW 17] VF type validation Max MCID value */
#घोषणा DORQ_REG_VF_TYPE_MIN_MCID_0				 0x170298
/* [RW 10] VF type validation comp value */
#घोषणा DORQ_REG_VF_TYPE_VALUE_0				 0x170258
#घोषणा DORQ_REG_VF_USAGE_CT_LIMIT				 0x170340

/* [RW 4] Initial activity counter value on the load request; when the
   लघुcut is करोne. */
#घोषणा DORQ_REG_SHRT_ACT_CNT					 0x170070
/* [RW 28] TCM Header when both ULP and TCP context is loaded. */
#घोषणा DORQ_REG_SHRT_CMHEAD					 0x170054
#घोषणा HC_CONFIG_0_REG_ATTN_BIT_EN_0				 (0x1<<4)
#घोषणा HC_CONFIG_0_REG_BLOCK_DISABLE_0				 (0x1<<0)
#घोषणा HC_CONFIG_0_REG_INT_LINE_EN_0				 (0x1<<3)
#घोषणा HC_CONFIG_0_REG_MSI_ATTN_EN_0				 (0x1<<7)
#घोषणा HC_CONFIG_0_REG_MSI_MSIX_INT_EN_0			 (0x1<<2)
#घोषणा HC_CONFIG_0_REG_SINGLE_ISR_EN_0				 (0x1<<1)
#घोषणा HC_CONFIG_1_REG_BLOCK_DISABLE_1				 (0x1<<0)
#घोषणा DORQ_REG_VF_USAGE_CNT					 0x170320
#घोषणा HC_REG_AGG_INT_0					 0x108050
#घोषणा HC_REG_AGG_INT_1					 0x108054
#घोषणा HC_REG_ATTN_BIT 					 0x108120
#घोषणा HC_REG_ATTN_IDX 					 0x108100
#घोषणा HC_REG_ATTN_MSG0_ADDR_L 				 0x108018
#घोषणा HC_REG_ATTN_MSG1_ADDR_L 				 0x108020
#घोषणा HC_REG_ATTN_NUM_P0					 0x108038
#घोषणा HC_REG_ATTN_NUM_P1					 0x10803c
#घोषणा HC_REG_COMMAND_REG					 0x108180
#घोषणा HC_REG_CONFIG_0 					 0x108000
#घोषणा HC_REG_CONFIG_1 					 0x108004
#घोषणा HC_REG_FUNC_NUM_P0					 0x1080ac
#घोषणा HC_REG_FUNC_NUM_P1					 0x1080b0
/* [RW 3] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा HC_REG_HC_PRTY_MASK					 0x1080a0
/* [R 3] Parity रेजिस्टर #0 पढ़ो */
#घोषणा HC_REG_HC_PRTY_STS					 0x108094
/* [RC 3] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा HC_REG_HC_PRTY_STS_CLR					 0x108098
#घोषणा HC_REG_INT_MASK						 0x108108
#घोषणा HC_REG_LEADING_EDGE_0					 0x108040
#घोषणा HC_REG_LEADING_EDGE_1					 0x108048
#घोषणा HC_REG_MAIN_MEMORY					 0x108800
#घोषणा HC_REG_MAIN_MEMORY_SIZE					 152
#घोषणा HC_REG_P0_PROD_CONS					 0x108200
#घोषणा HC_REG_P1_PROD_CONS					 0x108400
#घोषणा HC_REG_PBA_COMMAND					 0x108140
#घोषणा HC_REG_PCI_CONFIG_0					 0x108010
#घोषणा HC_REG_PCI_CONFIG_1					 0x108014
#घोषणा HC_REG_STATISTIC_COUNTERS				 0x109000
#घोषणा HC_REG_TRAILING_EDGE_0					 0x108044
#घोषणा HC_REG_TRAILING_EDGE_1					 0x10804c
#घोषणा HC_REG_UC_RAM_ADDR_0					 0x108028
#घोषणा HC_REG_UC_RAM_ADDR_1					 0x108030
#घोषणा HC_REG_USTORM_ADDR_FOR_COALESCE 			 0x108068
#घोषणा HC_REG_VQID_0						 0x108008
#घोषणा HC_REG_VQID_1						 0x10800c
#घोषणा IGU_BLOCK_CONFIGURATION_REG_BACKWARD_COMP_EN		 (0x1<<1)
#घोषणा IGU_BLOCK_CONFIGURATION_REG_BLOCK_ENABLE		 (0x1<<0)
#घोषणा IGU_REG_ATTENTION_ACK_BITS				 0x130108
/* [R 4] Debug: attn_fsm */
#घोषणा IGU_REG_ATTN_FSM					 0x130054
#घोषणा IGU_REG_ATTN_MSG_ADDR_H				 0x13011c
#घोषणा IGU_REG_ATTN_MSG_ADDR_L				 0x130120
/* [R 4] Debug: [3] - attention ग_लिखो करोne message is pending (0-no pending;
 * 1-pending). [2:0] = PFID. Pending means attention message was sent; but
 * ग_लिखो करोne didn't receive. */
#घोषणा IGU_REG_ATTN_WRITE_DONE_PENDING			 0x130030
#घोषणा IGU_REG_BLOCK_CONFIGURATION				 0x130000
#घोषणा IGU_REG_COMMAND_REG_32LSB_DATA				 0x130124
#घोषणा IGU_REG_COMMAND_REG_CTRL				 0x13012c
/* [WB_R 32] Cleanup bit status per SB. 1 = cleanup is set. 0 = cleanup bit
 * is clear. The bits in this रेजिस्टरs are set and clear via the producer
 * command. Data valid only in addresses 0-4. all the rest are zero. */
#घोषणा IGU_REG_CSTORM_TYPE_0_SB_CLEANUP			 0x130200
/* [R 5] Debug: ctrl_fsm */
#घोषणा IGU_REG_CTRL_FSM					 0x130064
/* [R 1] data available क्रम error memory. If this bit is clear करो not red
 * from error_handling_memory. */
#घोषणा IGU_REG_ERROR_HANDLING_DATA_VALID			 0x130130
/* [RW 11] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा IGU_REG_IGU_PRTY_MASK					 0x1300a8
/* [R 11] Parity रेजिस्टर #0 पढ़ो */
#घोषणा IGU_REG_IGU_PRTY_STS					 0x13009c
/* [RC 11] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा IGU_REG_IGU_PRTY_STS_CLR				 0x1300a0
/* [R 4] Debug: पूर्णांक_handle_fsm */
#घोषणा IGU_REG_INT_HANDLE_FSM					 0x130050
#घोषणा IGU_REG_LEADING_EDGE_LATCH				 0x130134
/* [RW 14] mapping CAM; relevant क्रम E2 operating mode only. [0] - valid.
 * [6:1] - vector number; [13:7] - FID (अगर VF - [13] = 0; [12:7] = VF
 * number; अगर PF - [13] = 1; [12:10] = 0; [9:7] = PF number); */
#घोषणा IGU_REG_MAPPING_MEMORY					 0x131000
#घोषणा IGU_REG_MAPPING_MEMORY_SIZE				 136
#घोषणा IGU_REG_PBA_STATUS_LSB					 0x130138
#घोषणा IGU_REG_PBA_STATUS_MSB					 0x13013c
#घोषणा IGU_REG_PCI_PF_MSI_EN					 0x130140
#घोषणा IGU_REG_PCI_PF_MSIX_EN					 0x130144
#घोषणा IGU_REG_PCI_PF_MSIX_FUNC_MASK				 0x130148
/* [WB_R 32] Each bit represent the pending bits status क्रम that SB. 0 = no
 * pending; 1 = pending. Pendings means पूर्णांकerrupt was निश्चितed; and ग_लिखो
 * करोne was not received. Data valid only in addresses 0-4. all the rest are
 * zero. */
#घोषणा IGU_REG_PENDING_BITS_STATUS				 0x130300
#घोषणा IGU_REG_PF_CONFIGURATION				 0x130154
/* [RW 20] producers only. E2 mode: address 0-135 match to the mapping
 * memory; 136 - PF0 शेष prod; 137 PF1 शेष prod; 138 - PF2 शेष
 * prod; 139 PF3 शेष prod; 140 - PF0 - ATTN prod; 141 - PF1 - ATTN prod;
 * 142 - PF2 - ATTN prod; 143 - PF3 - ATTN prod; 144-147 reserved. E1.5 mode
 * - In backward compatible mode; क्रम non शेष SB; each even line in the
 * memory holds the U producer and each odd line hold the C producer. The
 * first 128 producer are क्रम NDSB (PF0 - 0-31; PF1 - 32-63 and so on). The
 * last 20 producers are क्रम the DSB क्रम each PF. each PF has five segments
 * (the order inside each segment is PF0; PF1; PF2; PF3) - 128-131 U prods;
 * 132-135 C prods; 136-139 X prods; 140-143 T prods; 144-147 ATTN prods; */
#घोषणा IGU_REG_PROD_CONS_MEMORY				 0x132000
/* [R 3] Debug: pxp_arb_fsm */
#घोषणा IGU_REG_PXP_ARB_FSM					 0x130068
/* [RW 6] Write one क्रम each bit will reset the appropriate memory. When the
 * memory reset finished the appropriate bit will be clear. Bit 0 - mapping
 * memory; Bit 1 - SB memory; Bit 2 - SB पूर्णांकerrupt and mask रेजिस्टर; Bit 3
 * - MSIX memory; Bit 4 - PBA memory; Bit 5 - statistics; */
#घोषणा IGU_REG_RESET_MEMORIES					 0x130158
/* [R 4] Debug: sb_ctrl_fsm */
#घोषणा IGU_REG_SB_CTRL_FSM					 0x13004c
#घोषणा IGU_REG_SB_INT_BEFORE_MASK_LSB				 0x13015c
#घोषणा IGU_REG_SB_INT_BEFORE_MASK_MSB				 0x130160
#घोषणा IGU_REG_SB_MASK_LSB					 0x130164
#घोषणा IGU_REG_SB_MASK_MSB					 0x130168
/* [RW 16] Number of command that were dropped without causing an पूर्णांकerrupt
 * due to: पढ़ो access क्रम WO BAR address; or ग_लिखो access क्रम RO BAR
 * address or any access क्रम reserved address or PCI function error is set
 * and address is not MSIX; PBA or cleanup */
#घोषणा IGU_REG_SILENT_DROP					 0x13016c
/* [RW 10] Number of MSI/MSIX/ATTN messages sent क्रम the function: 0-63 -
 * number of MSIX messages per VF; 64-67 - number of MSI/MSIX messages per
 * PF; 68-71 number of ATTN messages per PF */
#घोषणा IGU_REG_STATISTIC_NUM_MESSAGE_SENT			 0x130800
/* [RW 32] Number of cycles the समयr mask masking the IGU पूर्णांकerrupt when a
 * समयr mask command arrives. Value must be bigger than 100. */
#घोषणा IGU_REG_TIMER_MASKING_VALUE				 0x13003c
#घोषणा IGU_REG_TRAILING_EDGE_LATCH				 0x130104
#घोषणा IGU_REG_VF_CONFIGURATION				 0x130170
/* [WB_R 32] Each bit represent ग_लिखो करोne pending bits status क्रम that SB
 * (MSI/MSIX message was sent and ग_लिखो करोne was not received yet). 0 =
 * clear; 1 = set. Data valid only in addresses 0-4. all the rest are zero. */
#घोषणा IGU_REG_WRITE_DONE_PENDING				 0x130480
#घोषणा MCP_A_REG_MCPR_SCRATCH					 0x3a0000
#घोषणा MCP_REG_MCPR_ACCESS_LOCK				 0x8009c
#घोषणा MCP_REG_MCPR_CPU_PROGRAM_COUNTER			 0x8501c
#घोषणा MCP_REG_MCPR_GP_INPUTS					 0x800c0
#घोषणा MCP_REG_MCPR_GP_OENABLE					 0x800c8
#घोषणा MCP_REG_MCPR_GP_OUTPUTS					 0x800c4
#घोषणा MCP_REG_MCPR_IMC_COMMAND				 0x85900
#घोषणा MCP_REG_MCPR_IMC_DATAREG0				 0x85920
#घोषणा MCP_REG_MCPR_IMC_SLAVE_CONTROL				 0x85904
#घोषणा MCP_REG_MCPR_CPU_PROGRAM_COUNTER			 0x8501c
#घोषणा MCP_REG_MCPR_NVM_ACCESS_ENABLE				 0x86424
#घोषणा MCP_REG_MCPR_NVM_ADDR					 0x8640c
#घोषणा MCP_REG_MCPR_NVM_CFG4					 0x8642c
#घोषणा MCP_REG_MCPR_NVM_COMMAND				 0x86400
#घोषणा MCP_REG_MCPR_NVM_READ					 0x86410
#घोषणा MCP_REG_MCPR_NVM_SW_ARB 				 0x86420
#घोषणा MCP_REG_MCPR_NVM_WRITE					 0x86408
#घोषणा MCP_REG_MCPR_SCRATCH					 0xa0000
#घोषणा MISC_AEU_GENERAL_MASK_REG_AEU_NIG_CLOSE_MASK		 (0x1<<1)
#घोषणा MISC_AEU_GENERAL_MASK_REG_AEU_PXP_CLOSE_MASK		 (0x1<<0)
/* [R 32] पढ़ो first 32 bit after inversion of function 0. mapped as
   follows: [0] NIG attention क्रम function0; [1] NIG attention क्रम
   function1; [2] GPIO1 mcp; [3] GPIO2 mcp; [4] GPIO3 mcp; [5] GPIO4 mcp;
   [6] GPIO1 function 1; [7] GPIO2 function 1; [8] GPIO3 function 1; [9]
   GPIO4 function 1; [10] PCIE glue/PXP VPD event function0; [11] PCIE
   glue/PXP VPD event function1; [12] PCIE glue/PXP Expansion ROM event0;
   [13] PCIE glue/PXP Expansion ROM event1; [14] SPIO4; [15] SPIO5; [16]
   MSI/X indication क्रम mcp; [17] MSI/X indication क्रम function 1; [18] BRB
   Parity error; [19] BRB Hw पूर्णांकerrupt; [20] PRS Parity error; [21] PRS Hw
   पूर्णांकerrupt; [22] SRC Parity error; [23] SRC Hw पूर्णांकerrupt; [24] TSDM Parity
   error; [25] TSDM Hw पूर्णांकerrupt; [26] TCM Parity error; [27] TCM Hw
   पूर्णांकerrupt; [28] TSEMI Parity error; [29] TSEMI Hw पूर्णांकerrupt; [30] PBF
   Parity error; [31] PBF Hw पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_AFTER_INVERT_1_FUNC_0			 0xa42c
#घोषणा MISC_REG_AEU_AFTER_INVERT_1_FUNC_1			 0xa430
/* [R 32] पढ़ो first 32 bit after inversion of mcp. mapped as follows: [0]
   NIG attention क्रम function0; [1] NIG attention क्रम function1; [2] GPIO1
   mcp; [3] GPIO2 mcp; [4] GPIO3 mcp; [5] GPIO4 mcp; [6] GPIO1 function 1;
   [7] GPIO2 function 1; [8] GPIO3 function 1; [9] GPIO4 function 1; [10]
   PCIE glue/PXP VPD event function0; [11] PCIE glue/PXP VPD event
   function1; [12] PCIE glue/PXP Expansion ROM event0; [13] PCIE glue/PXP
   Expansion ROM event1; [14] SPIO4; [15] SPIO5; [16] MSI/X indication क्रम
   mcp; [17] MSI/X indication क्रम function 1; [18] BRB Parity error; [19]
   BRB Hw पूर्णांकerrupt; [20] PRS Parity error; [21] PRS Hw पूर्णांकerrupt; [22] SRC
   Parity error; [23] SRC Hw पूर्णांकerrupt; [24] TSDM Parity error; [25] TSDM Hw
   पूर्णांकerrupt; [26] TCM Parity error; [27] TCM Hw पूर्णांकerrupt; [28] TSEMI
   Parity error; [29] TSEMI Hw पूर्णांकerrupt; [30] PBF Parity error; [31] PBF Hw
   पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_AFTER_INVERT_1_MCP 			 0xa434
/* [R 32] पढ़ो second 32 bit after inversion of function 0. mapped as
   follows: [0] PBClient Parity error; [1] PBClient Hw पूर्णांकerrupt; [2] QM
   Parity error; [3] QM Hw पूर्णांकerrupt; [4] Timers Parity error; [5] Timers Hw
   पूर्णांकerrupt; [6] XSDM Parity error; [7] XSDM Hw पूर्णांकerrupt; [8] XCM Parity
   error; [9] XCM Hw पूर्णांकerrupt; [10] XSEMI Parity error; [11] XSEMI Hw
   पूर्णांकerrupt; [12] DoorbellQ Parity error; [13] DoorbellQ Hw पूर्णांकerrupt; [14]
   NIG Parity error; [15] NIG Hw पूर्णांकerrupt; [16] Vaux PCI core Parity error;
   [17] Vaux PCI core Hw पूर्णांकerrupt; [18] Debug Parity error; [19] Debug Hw
   पूर्णांकerrupt; [20] USDM Parity error; [21] USDM Hw पूर्णांकerrupt; [22] UCM
   Parity error; [23] UCM Hw पूर्णांकerrupt; [24] USEMI Parity error; [25] USEMI
   Hw पूर्णांकerrupt; [26] UPB Parity error; [27] UPB Hw पूर्णांकerrupt; [28] CSDM
   Parity error; [29] CSDM Hw पूर्णांकerrupt; [30] CCM Parity error; [31] CCM Hw
   पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_AFTER_INVERT_2_FUNC_0			 0xa438
#घोषणा MISC_REG_AEU_AFTER_INVERT_2_FUNC_1			 0xa43c
/* [R 32] पढ़ो second 32 bit after inversion of mcp. mapped as follows: [0]
   PBClient Parity error; [1] PBClient Hw पूर्णांकerrupt; [2] QM Parity error;
   [3] QM Hw पूर्णांकerrupt; [4] Timers Parity error; [5] Timers Hw पूर्णांकerrupt;
   [6] XSDM Parity error; [7] XSDM Hw पूर्णांकerrupt; [8] XCM Parity error; [9]
   XCM Hw पूर्णांकerrupt; [10] XSEMI Parity error; [11] XSEMI Hw पूर्णांकerrupt; [12]
   DoorbellQ Parity error; [13] DoorbellQ Hw पूर्णांकerrupt; [14] NIG Parity
   error; [15] NIG Hw पूर्णांकerrupt; [16] Vaux PCI core Parity error; [17] Vaux
   PCI core Hw पूर्णांकerrupt; [18] Debug Parity error; [19] Debug Hw पूर्णांकerrupt;
   [20] USDM Parity error; [21] USDM Hw पूर्णांकerrupt; [22] UCM Parity error;
   [23] UCM Hw पूर्णांकerrupt; [24] USEMI Parity error; [25] USEMI Hw पूर्णांकerrupt;
   [26] UPB Parity error; [27] UPB Hw पूर्णांकerrupt; [28] CSDM Parity error;
   [29] CSDM Hw पूर्णांकerrupt; [30] CCM Parity error; [31] CCM Hw पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_AFTER_INVERT_2_MCP 			 0xa440
/* [R 32] पढ़ो third 32 bit after inversion of function 0. mapped as
   follows: [0] CSEMI Parity error; [1] CSEMI Hw पूर्णांकerrupt; [2] PXP Parity
   error; [3] PXP Hw पूर्णांकerrupt; [4] PXPpciClockClient Parity error; [5]
   PXPpciClockClient Hw पूर्णांकerrupt; [6] CFC Parity error; [7] CFC Hw
   पूर्णांकerrupt; [8] CDU Parity error; [9] CDU Hw पूर्णांकerrupt; [10] DMAE Parity
   error; [11] DMAE Hw पूर्णांकerrupt; [12] IGU (HC) Parity error; [13] IGU (HC)
   Hw पूर्णांकerrupt; [14] MISC Parity error; [15] MISC Hw पूर्णांकerrupt; [16]
   pxp_misc_mps_attn; [17] Flash event; [18] SMB event; [19] MCP attn0; [20]
   MCP attn1; [21] SW समयrs attn_1 func0; [22] SW समयrs attn_2 func0; [23]
   SW समयrs attn_3 func0; [24] SW समयrs attn_4 func0; [25] PERST; [26] SW
   समयrs attn_1 func1; [27] SW समयrs attn_2 func1; [28] SW समयrs attn_3
   func1; [29] SW समयrs attn_4 func1; [30] General attn0; [31] General
   attn1; */
#घोषणा MISC_REG_AEU_AFTER_INVERT_3_FUNC_0			 0xa444
#घोषणा MISC_REG_AEU_AFTER_INVERT_3_FUNC_1			 0xa448
/* [R 32] पढ़ो third 32 bit after inversion of mcp. mapped as follows: [0]
   CSEMI Parity error; [1] CSEMI Hw पूर्णांकerrupt; [2] PXP Parity error; [3] PXP
   Hw पूर्णांकerrupt; [4] PXPpciClockClient Parity error; [5] PXPpciClockClient
   Hw पूर्णांकerrupt; [6] CFC Parity error; [7] CFC Hw पूर्णांकerrupt; [8] CDU Parity
   error; [9] CDU Hw पूर्णांकerrupt; [10] DMAE Parity error; [11] DMAE Hw
   पूर्णांकerrupt; [12] IGU (HC) Parity error; [13] IGU (HC) Hw पूर्णांकerrupt; [14]
   MISC Parity error; [15] MISC Hw पूर्णांकerrupt; [16] pxp_misc_mps_attn; [17]
   Flash event; [18] SMB event; [19] MCP attn0; [20] MCP attn1; [21] SW
   समयrs attn_1 func0; [22] SW समयrs attn_2 func0; [23] SW समयrs attn_3
   func0; [24] SW समयrs attn_4 func0; [25] PERST; [26] SW समयrs attn_1
   func1; [27] SW समयrs attn_2 func1; [28] SW समयrs attn_3 func1; [29] SW
   समयrs attn_4 func1; [30] General attn0; [31] General attn1; */
#घोषणा MISC_REG_AEU_AFTER_INVERT_3_MCP 			 0xa44c
/* [R 32] पढ़ो fourth 32 bit after inversion of function 0. mapped as
   follows: [0] General attn2; [1] General attn3; [2] General attn4; [3]
   General attn5; [4] General attn6; [5] General attn7; [6] General attn8;
   [7] General attn9; [8] General attn10; [9] General attn11; [10] General
   attn12; [11] General attn13; [12] General attn14; [13] General attn15;
   [14] General attn16; [15] General attn17; [16] General attn18; [17]
   General attn19; [18] General attn20; [19] General attn21; [20] Main घातer
   पूर्णांकerrupt; [21] RBCR Latched attn; [22] RBCT Latched attn; [23] RBCN
   Latched attn; [24] RBCU Latched attn; [25] RBCP Latched attn; [26] GRC
   Latched समयout attention; [27] GRC Latched reserved access attention;
   [28] MCP Latched rom_parity; [29] MCP Latched ump_rx_parity; [30] MCP
   Latched ump_tx_parity; [31] MCP Latched scpad_parity; */
#घोषणा MISC_REG_AEU_AFTER_INVERT_4_FUNC_0			 0xa450
#घोषणा MISC_REG_AEU_AFTER_INVERT_4_FUNC_1			 0xa454
/* [R 32] पढ़ो fourth 32 bit after inversion of mcp. mapped as follows: [0]
   General attn2; [1] General attn3; [2] General attn4; [3] General attn5;
   [4] General attn6; [5] General attn7; [6] General attn8; [7] General
   attn9; [8] General attn10; [9] General attn11; [10] General attn12; [11]
   General attn13; [12] General attn14; [13] General attn15; [14] General
   attn16; [15] General attn17; [16] General attn18; [17] General attn19;
   [18] General attn20; [19] General attn21; [20] Main घातer पूर्णांकerrupt; [21]
   RBCR Latched attn; [22] RBCT Latched attn; [23] RBCN Latched attn; [24]
   RBCU Latched attn; [25] RBCP Latched attn; [26] GRC Latched समयout
   attention; [27] GRC Latched reserved access attention; [28] MCP Latched
   rom_parity; [29] MCP Latched ump_rx_parity; [30] MCP Latched
   ump_tx_parity; [31] MCP Latched scpad_parity; */
#घोषणा MISC_REG_AEU_AFTER_INVERT_4_MCP 			 0xa458
/* [R 32] Read fअगरth 32 bit after inversion of function 0. Mapped as
 * follows: [0] PGLUE config_space; [1] PGLUE misc_flr; [2] PGLUE B RBC
 * attention [3] PGLUE B RBC parity; [4] ATC attention; [5] ATC parity; [6]
 * CNIG attention (reserved); [7] CNIG parity (reserved); [31-8] Reserved; */
#घोषणा MISC_REG_AEU_AFTER_INVERT_5_FUNC_0			 0xa700
/* [W 14] ग_लिखो to this रेजिस्टर results with the clear of the latched
   संकेतs; one in d0 clears RBCR latch; one in d1 clears RBCT latch; one in
   d2 clears RBCN latch; one in d3 clears RBCU latch; one in d4 clears RBCP
   latch; one in d5 clears GRC Latched समयout attention; one in d6 clears
   GRC Latched reserved access attention; one in d7 clears Latched
   rom_parity; one in d8 clears Latched ump_rx_parity; one in d9 clears
   Latched ump_tx_parity; one in d10 clears Latched scpad_parity (both
   ports); one in d11 clears pxpv_misc_mps_attn; one in d12 clears
   pxp_misc_exp_rom_attn0; one in d13 clears pxp_misc_exp_rom_attn1; पढ़ो
   from this रेजिस्टर वापस zero */
#घोषणा MISC_REG_AEU_CLR_LATCH_SIGNAL				 0xa45c
/* [RW 32] first 32b क्रम enabling the output क्रम function 0 output0. mapped
   as follows: [0] NIG attention क्रम function0; [1] NIG attention क्रम
   function1; [2] GPIO1 function 0; [3] GPIO2 function 0; [4] GPIO3 function
   0; [5] GPIO4 function 0; [6] GPIO1 function 1; [7] GPIO2 function 1; [8]
   GPIO3 function 1; [9] GPIO4 function 1; [10] PCIE glue/PXP VPD event
   function0; [11] PCIE glue/PXP VPD event function1; [12] PCIE glue/PXP
   Expansion ROM event0; [13] PCIE glue/PXP Expansion ROM event1; [14]
   SPIO4; [15] SPIO5; [16] MSI/X indication क्रम function 0; [17] MSI/X
   indication क्रम function 1; [18] BRB Parity error; [19] BRB Hw पूर्णांकerrupt;
   [20] PRS Parity error; [21] PRS Hw पूर्णांकerrupt; [22] SRC Parity error; [23]
   SRC Hw पूर्णांकerrupt; [24] TSDM Parity error; [25] TSDM Hw पूर्णांकerrupt; [26]
   TCM Parity error; [27] TCM Hw पूर्णांकerrupt; [28] TSEMI Parity error; [29]
   TSEMI Hw पूर्णांकerrupt; [30] PBF Parity error; [31] PBF Hw पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_0_OUT_0			 0xa06c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_0_OUT_1			 0xa07c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_0_OUT_2			 0xa08c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_0_OUT_3			 0xa09c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_0_OUT_5			 0xa0bc
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_0_OUT_6			 0xa0cc
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_0_OUT_7			 0xa0dc
/* [RW 32] first 32b क्रम enabling the output क्रम function 1 output0. mapped
   as follows: [0] NIG attention क्रम function0; [1] NIG attention क्रम
   function1; [2] GPIO1 function 1; [3] GPIO2 function 1; [4] GPIO3 function
   1; [5] GPIO4 function 1; [6] GPIO1 function 1; [7] GPIO2 function 1; [8]
   GPIO3 function 1; [9] GPIO4 function 1; [10] PCIE glue/PXP VPD event
   function0; [11] PCIE glue/PXP VPD event function1; [12] PCIE glue/PXP
   Expansion ROM event0; [13] PCIE glue/PXP Expansion ROM event1; [14]
   SPIO4; [15] SPIO5; [16] MSI/X indication क्रम function 1; [17] MSI/X
   indication क्रम function 1; [18] BRB Parity error; [19] BRB Hw पूर्णांकerrupt;
   [20] PRS Parity error; [21] PRS Hw पूर्णांकerrupt; [22] SRC Parity error; [23]
   SRC Hw पूर्णांकerrupt; [24] TSDM Parity error; [25] TSDM Hw पूर्णांकerrupt; [26]
   TCM Parity error; [27] TCM Hw पूर्णांकerrupt; [28] TSEMI Parity error; [29]
   TSEMI Hw पूर्णांकerrupt; [30] PBF Parity error; [31] PBF Hw पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_1_OUT_0			 0xa10c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_1_OUT_1			 0xa11c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_1_OUT_2			 0xa12c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_1_OUT_3			 0xa13c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_1_OUT_5			 0xa15c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_1_OUT_6			 0xa16c
#घोषणा MISC_REG_AEU_ENABLE1_FUNC_1_OUT_7			 0xa17c
/* [RW 32] first 32b क्रम enabling the output क्रम बंद the gate nig. mapped
   as follows: [0] NIG attention क्रम function0; [1] NIG attention क्रम
   function1; [2] GPIO1 function 0; [3] GPIO2 function 0; [4] GPIO3 function
   0; [5] GPIO4 function 0; [6] GPIO1 function 1; [7] GPIO2 function 1; [8]
   GPIO3 function 1; [9] GPIO4 function 1; [10] PCIE glue/PXP VPD event
   function0; [11] PCIE glue/PXP VPD event function1; [12] PCIE glue/PXP
   Expansion ROM event0; [13] PCIE glue/PXP Expansion ROM event1; [14]
   SPIO4; [15] SPIO5; [16] MSI/X indication क्रम function 0; [17] MSI/X
   indication क्रम function 1; [18] BRB Parity error; [19] BRB Hw पूर्णांकerrupt;
   [20] PRS Parity error; [21] PRS Hw पूर्णांकerrupt; [22] SRC Parity error; [23]
   SRC Hw पूर्णांकerrupt; [24] TSDM Parity error; [25] TSDM Hw पूर्णांकerrupt; [26]
   TCM Parity error; [27] TCM Hw पूर्णांकerrupt; [28] TSEMI Parity error; [29]
   TSEMI Hw पूर्णांकerrupt; [30] PBF Parity error; [31] PBF Hw पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_ENABLE1_NIG_0				 0xa0ec
#घोषणा MISC_REG_AEU_ENABLE1_NIG_1				 0xa18c
/* [RW 32] first 32b क्रम enabling the output क्रम बंद the gate pxp. mapped
   as follows: [0] NIG attention क्रम function0; [1] NIG attention क्रम
   function1; [2] GPIO1 function 0; [3] GPIO2 function 0; [4] GPIO3 function
   0; [5] GPIO4 function 0; [6] GPIO1 function 1; [7] GPIO2 function 1; [8]
   GPIO3 function 1; [9] GPIO4 function 1; [10] PCIE glue/PXP VPD event
   function0; [11] PCIE glue/PXP VPD event function1; [12] PCIE glue/PXP
   Expansion ROM event0; [13] PCIE glue/PXP Expansion ROM event1; [14]
   SPIO4; [15] SPIO5; [16] MSI/X indication क्रम function 0; [17] MSI/X
   indication क्रम function 1; [18] BRB Parity error; [19] BRB Hw पूर्णांकerrupt;
   [20] PRS Parity error; [21] PRS Hw पूर्णांकerrupt; [22] SRC Parity error; [23]
   SRC Hw पूर्णांकerrupt; [24] TSDM Parity error; [25] TSDM Hw पूर्णांकerrupt; [26]
   TCM Parity error; [27] TCM Hw पूर्णांकerrupt; [28] TSEMI Parity error; [29]
   TSEMI Hw पूर्णांकerrupt; [30] PBF Parity error; [31] PBF Hw पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_ENABLE1_PXP_0				 0xa0fc
#घोषणा MISC_REG_AEU_ENABLE1_PXP_1				 0xa19c
/* [RW 32] second 32b क्रम enabling the output क्रम function 0 output0. mapped
   as follows: [0] PBClient Parity error; [1] PBClient Hw पूर्णांकerrupt; [2] QM
   Parity error; [3] QM Hw पूर्णांकerrupt; [4] Timers Parity error; [5] Timers Hw
   पूर्णांकerrupt; [6] XSDM Parity error; [7] XSDM Hw पूर्णांकerrupt; [8] XCM Parity
   error; [9] XCM Hw पूर्णांकerrupt; [10] XSEMI Parity error; [11] XSEMI Hw
   पूर्णांकerrupt; [12] DoorbellQ Parity error; [13] DoorbellQ Hw पूर्णांकerrupt; [14]
   NIG Parity error; [15] NIG Hw पूर्णांकerrupt; [16] Vaux PCI core Parity error;
   [17] Vaux PCI core Hw पूर्णांकerrupt; [18] Debug Parity error; [19] Debug Hw
   पूर्णांकerrupt; [20] USDM Parity error; [21] USDM Hw पूर्णांकerrupt; [22] UCM
   Parity error; [23] UCM Hw पूर्णांकerrupt; [24] USEMI Parity error; [25] USEMI
   Hw पूर्णांकerrupt; [26] UPB Parity error; [27] UPB Hw पूर्णांकerrupt; [28] CSDM
   Parity error; [29] CSDM Hw पूर्णांकerrupt; [30] CCM Parity error; [31] CCM Hw
   पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_ENABLE2_FUNC_0_OUT_0			 0xa070
#घोषणा MISC_REG_AEU_ENABLE2_FUNC_0_OUT_1			 0xa080
/* [RW 32] second 32b क्रम enabling the output क्रम function 1 output0. mapped
   as follows: [0] PBClient Parity error; [1] PBClient Hw पूर्णांकerrupt; [2] QM
   Parity error; [3] QM Hw पूर्णांकerrupt; [4] Timers Parity error; [5] Timers Hw
   पूर्णांकerrupt; [6] XSDM Parity error; [7] XSDM Hw पूर्णांकerrupt; [8] XCM Parity
   error; [9] XCM Hw पूर्णांकerrupt; [10] XSEMI Parity error; [11] XSEMI Hw
   पूर्णांकerrupt; [12] DoorbellQ Parity error; [13] DoorbellQ Hw पूर्णांकerrupt; [14]
   NIG Parity error; [15] NIG Hw पूर्णांकerrupt; [16] Vaux PCI core Parity error;
   [17] Vaux PCI core Hw पूर्णांकerrupt; [18] Debug Parity error; [19] Debug Hw
   पूर्णांकerrupt; [20] USDM Parity error; [21] USDM Hw पूर्णांकerrupt; [22] UCM
   Parity error; [23] UCM Hw पूर्णांकerrupt; [24] USEMI Parity error; [25] USEMI
   Hw पूर्णांकerrupt; [26] UPB Parity error; [27] UPB Hw पूर्णांकerrupt; [28] CSDM
   Parity error; [29] CSDM Hw पूर्णांकerrupt; [30] CCM Parity error; [31] CCM Hw
   पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_ENABLE2_FUNC_1_OUT_0			 0xa110
#घोषणा MISC_REG_AEU_ENABLE2_FUNC_1_OUT_1			 0xa120
/* [RW 32] second 32b क्रम enabling the output क्रम बंद the gate nig. mapped
   as follows: [0] PBClient Parity error; [1] PBClient Hw पूर्णांकerrupt; [2] QM
   Parity error; [3] QM Hw पूर्णांकerrupt; [4] Timers Parity error; [5] Timers Hw
   पूर्णांकerrupt; [6] XSDM Parity error; [7] XSDM Hw पूर्णांकerrupt; [8] XCM Parity
   error; [9] XCM Hw पूर्णांकerrupt; [10] XSEMI Parity error; [11] XSEMI Hw
   पूर्णांकerrupt; [12] DoorbellQ Parity error; [13] DoorbellQ Hw पूर्णांकerrupt; [14]
   NIG Parity error; [15] NIG Hw पूर्णांकerrupt; [16] Vaux PCI core Parity error;
   [17] Vaux PCI core Hw पूर्णांकerrupt; [18] Debug Parity error; [19] Debug Hw
   पूर्णांकerrupt; [20] USDM Parity error; [21] USDM Hw पूर्णांकerrupt; [22] UCM
   Parity error; [23] UCM Hw पूर्णांकerrupt; [24] USEMI Parity error; [25] USEMI
   Hw पूर्णांकerrupt; [26] UPB Parity error; [27] UPB Hw पूर्णांकerrupt; [28] CSDM
   Parity error; [29] CSDM Hw पूर्णांकerrupt; [30] CCM Parity error; [31] CCM Hw
   पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_ENABLE2_NIG_0				 0xa0f0
#घोषणा MISC_REG_AEU_ENABLE2_NIG_1				 0xa190
/* [RW 32] second 32b क्रम enabling the output क्रम बंद the gate pxp. mapped
   as follows: [0] PBClient Parity error; [1] PBClient Hw पूर्णांकerrupt; [2] QM
   Parity error; [3] QM Hw पूर्णांकerrupt; [4] Timers Parity error; [5] Timers Hw
   पूर्णांकerrupt; [6] XSDM Parity error; [7] XSDM Hw पूर्णांकerrupt; [8] XCM Parity
   error; [9] XCM Hw पूर्णांकerrupt; [10] XSEMI Parity error; [11] XSEMI Hw
   पूर्णांकerrupt; [12] DoorbellQ Parity error; [13] DoorbellQ Hw पूर्णांकerrupt; [14]
   NIG Parity error; [15] NIG Hw पूर्णांकerrupt; [16] Vaux PCI core Parity error;
   [17] Vaux PCI core Hw पूर्णांकerrupt; [18] Debug Parity error; [19] Debug Hw
   पूर्णांकerrupt; [20] USDM Parity error; [21] USDM Hw पूर्णांकerrupt; [22] UCM
   Parity error; [23] UCM Hw पूर्णांकerrupt; [24] USEMI Parity error; [25] USEMI
   Hw पूर्णांकerrupt; [26] UPB Parity error; [27] UPB Hw पूर्णांकerrupt; [28] CSDM
   Parity error; [29] CSDM Hw पूर्णांकerrupt; [30] CCM Parity error; [31] CCM Hw
   पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_ENABLE2_PXP_0				 0xa100
#घोषणा MISC_REG_AEU_ENABLE2_PXP_1				 0xa1a0
/* [RW 32] third 32b क्रम enabling the output क्रम function 0 output0. mapped
   as follows: [0] CSEMI Parity error; [1] CSEMI Hw पूर्णांकerrupt; [2] PXP
   Parity error; [3] PXP Hw पूर्णांकerrupt; [4] PXPpciClockClient Parity error;
   [5] PXPpciClockClient Hw पूर्णांकerrupt; [6] CFC Parity error; [7] CFC Hw
   पूर्णांकerrupt; [8] CDU Parity error; [9] CDU Hw पूर्णांकerrupt; [10] DMAE Parity
   error; [11] DMAE Hw पूर्णांकerrupt; [12] IGU (HC) Parity error; [13] IGU (HC)
   Hw पूर्णांकerrupt; [14] MISC Parity error; [15] MISC Hw पूर्णांकerrupt; [16]
   pxp_misc_mps_attn; [17] Flash event; [18] SMB event; [19] MCP attn0; [20]
   MCP attn1; [21] SW समयrs attn_1 func0; [22] SW समयrs attn_2 func0; [23]
   SW समयrs attn_3 func0; [24] SW समयrs attn_4 func0; [25] PERST; [26] SW
   समयrs attn_1 func1; [27] SW समयrs attn_2 func1; [28] SW समयrs attn_3
   func1; [29] SW समयrs attn_4 func1; [30] General attn0; [31] General
   attn1; */
#घोषणा MISC_REG_AEU_ENABLE3_FUNC_0_OUT_0			 0xa074
#घोषणा MISC_REG_AEU_ENABLE3_FUNC_0_OUT_1			 0xa084
/* [RW 32] third 32b क्रम enabling the output क्रम function 1 output0. mapped
   as follows: [0] CSEMI Parity error; [1] CSEMI Hw पूर्णांकerrupt; [2] PXP
   Parity error; [3] PXP Hw पूर्णांकerrupt; [4] PXPpciClockClient Parity error;
   [5] PXPpciClockClient Hw पूर्णांकerrupt; [6] CFC Parity error; [7] CFC Hw
   पूर्णांकerrupt; [8] CDU Parity error; [9] CDU Hw पूर्णांकerrupt; [10] DMAE Parity
   error; [11] DMAE Hw पूर्णांकerrupt; [12] IGU (HC) Parity error; [13] IGU (HC)
   Hw पूर्णांकerrupt; [14] MISC Parity error; [15] MISC Hw पूर्णांकerrupt; [16]
   pxp_misc_mps_attn; [17] Flash event; [18] SMB event; [19] MCP attn0; [20]
   MCP attn1; [21] SW समयrs attn_1 func0; [22] SW समयrs attn_2 func0; [23]
   SW समयrs attn_3 func0; [24] SW समयrs attn_4 func0; [25] PERST; [26] SW
   समयrs attn_1 func1; [27] SW समयrs attn_2 func1; [28] SW समयrs attn_3
   func1; [29] SW समयrs attn_4 func1; [30] General attn0; [31] General
   attn1; */
#घोषणा MISC_REG_AEU_ENABLE3_FUNC_1_OUT_0			 0xa114
#घोषणा MISC_REG_AEU_ENABLE3_FUNC_1_OUT_1			 0xa124
/* [RW 32] third 32b क्रम enabling the output क्रम बंद the gate nig. mapped
   as follows: [0] CSEMI Parity error; [1] CSEMI Hw पूर्णांकerrupt; [2] PXP
   Parity error; [3] PXP Hw पूर्णांकerrupt; [4] PXPpciClockClient Parity error;
   [5] PXPpciClockClient Hw पूर्णांकerrupt; [6] CFC Parity error; [7] CFC Hw
   पूर्णांकerrupt; [8] CDU Parity error; [9] CDU Hw पूर्णांकerrupt; [10] DMAE Parity
   error; [11] DMAE Hw पूर्णांकerrupt; [12] IGU (HC) Parity error; [13] IGU (HC)
   Hw पूर्णांकerrupt; [14] MISC Parity error; [15] MISC Hw पूर्णांकerrupt; [16]
   pxp_misc_mps_attn; [17] Flash event; [18] SMB event; [19] MCP attn0; [20]
   MCP attn1; [21] SW समयrs attn_1 func0; [22] SW समयrs attn_2 func0; [23]
   SW समयrs attn_3 func0; [24] SW समयrs attn_4 func0; [25] PERST; [26] SW
   समयrs attn_1 func1; [27] SW समयrs attn_2 func1; [28] SW समयrs attn_3
   func1; [29] SW समयrs attn_4 func1; [30] General attn0; [31] General
   attn1; */
#घोषणा MISC_REG_AEU_ENABLE3_NIG_0				 0xa0f4
#घोषणा MISC_REG_AEU_ENABLE3_NIG_1				 0xa194
/* [RW 32] third 32b क्रम enabling the output क्रम बंद the gate pxp. mapped
   as follows: [0] CSEMI Parity error; [1] CSEMI Hw पूर्णांकerrupt; [2] PXP
   Parity error; [3] PXP Hw पूर्णांकerrupt; [4] PXPpciClockClient Parity error;
   [5] PXPpciClockClient Hw पूर्णांकerrupt; [6] CFC Parity error; [7] CFC Hw
   पूर्णांकerrupt; [8] CDU Parity error; [9] CDU Hw पूर्णांकerrupt; [10] DMAE Parity
   error; [11] DMAE Hw पूर्णांकerrupt; [12] IGU (HC) Parity error; [13] IGU (HC)
   Hw पूर्णांकerrupt; [14] MISC Parity error; [15] MISC Hw पूर्णांकerrupt; [16]
   pxp_misc_mps_attn; [17] Flash event; [18] SMB event; [19] MCP attn0; [20]
   MCP attn1; [21] SW समयrs attn_1 func0; [22] SW समयrs attn_2 func0; [23]
   SW समयrs attn_3 func0; [24] SW समयrs attn_4 func0; [25] PERST; [26] SW
   समयrs attn_1 func1; [27] SW समयrs attn_2 func1; [28] SW समयrs attn_3
   func1; [29] SW समयrs attn_4 func1; [30] General attn0; [31] General
   attn1; */
#घोषणा MISC_REG_AEU_ENABLE3_PXP_0				 0xa104
#घोषणा MISC_REG_AEU_ENABLE3_PXP_1				 0xa1a4
/* [RW 32] fourth 32b क्रम enabling the output क्रम function 0 output0.mapped
   as follows: [0] General attn2; [1] General attn3; [2] General attn4; [3]
   General attn5; [4] General attn6; [5] General attn7; [6] General attn8;
   [7] General attn9; [8] General attn10; [9] General attn11; [10] General
   attn12; [11] General attn13; [12] General attn14; [13] General attn15;
   [14] General attn16; [15] General attn17; [16] General attn18; [17]
   General attn19; [18] General attn20; [19] General attn21; [20] Main घातer
   पूर्णांकerrupt; [21] RBCR Latched attn; [22] RBCT Latched attn; [23] RBCN
   Latched attn; [24] RBCU Latched attn; [25] RBCP Latched attn; [26] GRC
   Latched समयout attention; [27] GRC Latched reserved access attention;
   [28] MCP Latched rom_parity; [29] MCP Latched ump_rx_parity; [30] MCP
   Latched ump_tx_parity; [31] MCP Latched scpad_parity; */
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_0_OUT_0			 0xa078
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_0_OUT_2			 0xa098
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_0_OUT_4			 0xa0b8
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_0_OUT_5			 0xa0c8
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_0_OUT_6			 0xa0d8
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_0_OUT_7			 0xa0e8
/* [RW 32] fourth 32b क्रम enabling the output क्रम function 1 output0.mapped
   as follows: [0] General attn2; [1] General attn3; [2] General attn4; [3]
   General attn5; [4] General attn6; [5] General attn7; [6] General attn8;
   [7] General attn9; [8] General attn10; [9] General attn11; [10] General
   attn12; [11] General attn13; [12] General attn14; [13] General attn15;
   [14] General attn16; [15] General attn17; [16] General attn18; [17]
   General attn19; [18] General attn20; [19] General attn21; [20] Main घातer
   पूर्णांकerrupt; [21] RBCR Latched attn; [22] RBCT Latched attn; [23] RBCN
   Latched attn; [24] RBCU Latched attn; [25] RBCP Latched attn; [26] GRC
   Latched समयout attention; [27] GRC Latched reserved access attention;
   [28] MCP Latched rom_parity; [29] MCP Latched ump_rx_parity; [30] MCP
   Latched ump_tx_parity; [31] MCP Latched scpad_parity; */
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_1_OUT_0			 0xa118
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_1_OUT_2			 0xa138
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_1_OUT_4			 0xa158
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_1_OUT_5			 0xa168
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_1_OUT_6			 0xa178
#घोषणा MISC_REG_AEU_ENABLE4_FUNC_1_OUT_7			 0xa188
/* [RW 32] fourth 32b क्रम enabling the output क्रम बंद the gate nig.mapped
   as follows: [0] General attn2; [1] General attn3; [2] General attn4; [3]
   General attn5; [4] General attn6; [5] General attn7; [6] General attn8;
   [7] General attn9; [8] General attn10; [9] General attn11; [10] General
   attn12; [11] General attn13; [12] General attn14; [13] General attn15;
   [14] General attn16; [15] General attn17; [16] General attn18; [17]
   General attn19; [18] General attn20; [19] General attn21; [20] Main घातer
   पूर्णांकerrupt; [21] RBCR Latched attn; [22] RBCT Latched attn; [23] RBCN
   Latched attn; [24] RBCU Latched attn; [25] RBCP Latched attn; [26] GRC
   Latched समयout attention; [27] GRC Latched reserved access attention;
   [28] MCP Latched rom_parity; [29] MCP Latched ump_rx_parity; [30] MCP
   Latched ump_tx_parity; [31] MCP Latched scpad_parity; */
#घोषणा MISC_REG_AEU_ENABLE4_NIG_0				 0xa0f8
#घोषणा MISC_REG_AEU_ENABLE4_NIG_1				 0xa198
/* [RW 32] fourth 32b क्रम enabling the output क्रम बंद the gate pxp.mapped
   as follows: [0] General attn2; [1] General attn3; [2] General attn4; [3]
   General attn5; [4] General attn6; [5] General attn7; [6] General attn8;
   [7] General attn9; [8] General attn10; [9] General attn11; [10] General
   attn12; [11] General attn13; [12] General attn14; [13] General attn15;
   [14] General attn16; [15] General attn17; [16] General attn18; [17]
   General attn19; [18] General attn20; [19] General attn21; [20] Main घातer
   पूर्णांकerrupt; [21] RBCR Latched attn; [22] RBCT Latched attn; [23] RBCN
   Latched attn; [24] RBCU Latched attn; [25] RBCP Latched attn; [26] GRC
   Latched समयout attention; [27] GRC Latched reserved access attention;
   [28] MCP Latched rom_parity; [29] MCP Latched ump_rx_parity; [30] MCP
   Latched ump_tx_parity; [31] MCP Latched scpad_parity; */
#घोषणा MISC_REG_AEU_ENABLE4_PXP_0				 0xa108
#घोषणा MISC_REG_AEU_ENABLE4_PXP_1				 0xa1a8
/* [RW 32] fअगरth 32b क्रम enabling the output क्रम function 0 output0. Mapped
 * as follows: [0] PGLUE config_space; [1] PGLUE misc_flr; [2] PGLUE B RBC
 * attention [3] PGLUE B RBC parity; [4] ATC attention; [5] ATC parity; [6]
 * mstat0 attention; [7] mstat0 parity; [8] mstat1 attention; [9] mstat1
 * parity; [31-10] Reserved; */
#घोषणा MISC_REG_AEU_ENABLE5_FUNC_0_OUT_0			 0xa688
/* [RW 32] Fअगरth 32b क्रम enabling the output क्रम function 1 output0. Mapped
 * as follows: [0] PGLUE config_space; [1] PGLUE misc_flr; [2] PGLUE B RBC
 * attention [3] PGLUE B RBC parity; [4] ATC attention; [5] ATC parity; [6]
 * mstat0 attention; [7] mstat0 parity; [8] mstat1 attention; [9] mstat1
 * parity; [31-10] Reserved; */
#घोषणा MISC_REG_AEU_ENABLE5_FUNC_1_OUT_0			 0xa6b0
/* [RW 1] set/clr general attention 0; this will set/clr bit 94 in the aeu
   128 bit vector */
#घोषणा MISC_REG_AEU_GENERAL_ATTN_0				 0xa000
#घोषणा MISC_REG_AEU_GENERAL_ATTN_1				 0xa004
#घोषणा MISC_REG_AEU_GENERAL_ATTN_10				 0xa028
#घोषणा MISC_REG_AEU_GENERAL_ATTN_11				 0xa02c
#घोषणा MISC_REG_AEU_GENERAL_ATTN_12				 0xa030
#घोषणा MISC_REG_AEU_GENERAL_ATTN_2				 0xa008
#घोषणा MISC_REG_AEU_GENERAL_ATTN_3				 0xa00c
#घोषणा MISC_REG_AEU_GENERAL_ATTN_4				 0xa010
#घोषणा MISC_REG_AEU_GENERAL_ATTN_5				 0xa014
#घोषणा MISC_REG_AEU_GENERAL_ATTN_6				 0xa018
#घोषणा MISC_REG_AEU_GENERAL_ATTN_7				 0xa01c
#घोषणा MISC_REG_AEU_GENERAL_ATTN_8				 0xa020
#घोषणा MISC_REG_AEU_GENERAL_ATTN_9				 0xa024
#घोषणा MISC_REG_AEU_GENERAL_MASK				 0xa61c
/* [RW 32] first 32b क्रम inverting the input क्रम function 0; क्रम each bit:
   0= करो not invert; 1= invert; mapped as follows: [0] NIG attention क्रम
   function0; [1] NIG attention क्रम function1; [2] GPIO1 mcp; [3] GPIO2 mcp;
   [4] GPIO3 mcp; [5] GPIO4 mcp; [6] GPIO1 function 1; [7] GPIO2 function 1;
   [8] GPIO3 function 1; [9] GPIO4 function 1; [10] PCIE glue/PXP VPD event
   function0; [11] PCIE glue/PXP VPD event function1; [12] PCIE glue/PXP
   Expansion ROM event0; [13] PCIE glue/PXP Expansion ROM event1; [14]
   SPIO4; [15] SPIO5; [16] MSI/X indication क्रम mcp; [17] MSI/X indication
   क्रम function 1; [18] BRB Parity error; [19] BRB Hw पूर्णांकerrupt; [20] PRS
   Parity error; [21] PRS Hw पूर्णांकerrupt; [22] SRC Parity error; [23] SRC Hw
   पूर्णांकerrupt; [24] TSDM Parity error; [25] TSDM Hw पूर्णांकerrupt; [26] TCM
   Parity error; [27] TCM Hw पूर्णांकerrupt; [28] TSEMI Parity error; [29] TSEMI
   Hw पूर्णांकerrupt; [30] PBF Parity error; [31] PBF Hw पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_INVERTER_1_FUNC_0				 0xa22c
#घोषणा MISC_REG_AEU_INVERTER_1_FUNC_1				 0xa23c
/* [RW 32] second 32b क्रम inverting the input क्रम function 0; क्रम each bit:
   0= करो not invert; 1= invert. mapped as follows: [0] PBClient Parity
   error; [1] PBClient Hw पूर्णांकerrupt; [2] QM Parity error; [3] QM Hw
   पूर्णांकerrupt; [4] Timers Parity error; [5] Timers Hw पूर्णांकerrupt; [6] XSDM
   Parity error; [7] XSDM Hw पूर्णांकerrupt; [8] XCM Parity error; [9] XCM Hw
   पूर्णांकerrupt; [10] XSEMI Parity error; [11] XSEMI Hw पूर्णांकerrupt; [12]
   DoorbellQ Parity error; [13] DoorbellQ Hw पूर्णांकerrupt; [14] NIG Parity
   error; [15] NIG Hw पूर्णांकerrupt; [16] Vaux PCI core Parity error; [17] Vaux
   PCI core Hw पूर्णांकerrupt; [18] Debug Parity error; [19] Debug Hw पूर्णांकerrupt;
   [20] USDM Parity error; [21] USDM Hw पूर्णांकerrupt; [22] UCM Parity error;
   [23] UCM Hw पूर्णांकerrupt; [24] USEMI Parity error; [25] USEMI Hw पूर्णांकerrupt;
   [26] UPB Parity error; [27] UPB Hw पूर्णांकerrupt; [28] CSDM Parity error;
   [29] CSDM Hw पूर्णांकerrupt; [30] CCM Parity error; [31] CCM Hw पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_INVERTER_2_FUNC_0				 0xa230
#घोषणा MISC_REG_AEU_INVERTER_2_FUNC_1				 0xa240
/* [RW 10] [7:0] = mask 8 attention output संकेतs toward IGU function0;
   [9:8] = raserved. Zero = mask; one = unmask */
#घोषणा MISC_REG_AEU_MASK_ATTN_FUNC_0				 0xa060
#घोषणा MISC_REG_AEU_MASK_ATTN_FUNC_1				 0xa064
/* [RW 1] If set a प्रणाली समाप्त occurred */
#घोषणा MISC_REG_AEU_SYS_KILL_OCCURRED				 0xa610
/* [RW 32] Represent the status of the input vector to the AEU when a प्रणाली
   समाप्त occurred. The रेजिस्टर is reset in por reset. Mapped as follows: [0]
   NIG attention क्रम function0; [1] NIG attention क्रम function1; [2] GPIO1
   mcp; [3] GPIO2 mcp; [4] GPIO3 mcp; [5] GPIO4 mcp; [6] GPIO1 function 1;
   [7] GPIO2 function 1; [8] GPIO3 function 1; [9] GPIO4 function 1; [10]
   PCIE glue/PXP VPD event function0; [11] PCIE glue/PXP VPD event
   function1; [12] PCIE glue/PXP Expansion ROM event0; [13] PCIE glue/PXP
   Expansion ROM event1; [14] SPIO4; [15] SPIO5; [16] MSI/X indication क्रम
   mcp; [17] MSI/X indication क्रम function 1; [18] BRB Parity error; [19]
   BRB Hw पूर्णांकerrupt; [20] PRS Parity error; [21] PRS Hw पूर्णांकerrupt; [22] SRC
   Parity error; [23] SRC Hw पूर्णांकerrupt; [24] TSDM Parity error; [25] TSDM Hw
   पूर्णांकerrupt; [26] TCM Parity error; [27] TCM Hw पूर्णांकerrupt; [28] TSEMI
   Parity error; [29] TSEMI Hw पूर्णांकerrupt; [30] PBF Parity error; [31] PBF Hw
   पूर्णांकerrupt; */
#घोषणा MISC_REG_AEU_SYS_KILL_STATUS_0				 0xa600
#घोषणा MISC_REG_AEU_SYS_KILL_STATUS_1				 0xa604
#घोषणा MISC_REG_AEU_SYS_KILL_STATUS_2				 0xa608
#घोषणा MISC_REG_AEU_SYS_KILL_STATUS_3				 0xa60c
/* [R 4] This field indicates the type of the device. '0' - 2 Ports; '1' - 1
   Port. */
#घोषणा MISC_REG_BOND_ID					 0xa400
/* [R 16] These bits indicate the part number क्रम the chip. */
#घोषणा MISC_REG_CHIP_NUM					 0xa408
/* [R 4] These bits indicate the base revision of the chip. This value
   starts at 0x0 क्रम the A0 tape-out and increments by one क्रम each
   all-layer tape-out. */
#घोषणा MISC_REG_CHIP_REV					 0xa40c
/* [R 14] otp_misc_करो[100:0] spare bits collection: 13:11-
 * otp_misc_करो[100:98]; 10:7 - otp_misc_करो[87:84]; 6:3 - otp_misc_करो[75:72];
 * 2:1 - otp_misc_करो[51:50]; 0 - otp_misc_करो[1]. */
#घोषणा MISC_REG_CHIP_TYPE					 0xac60
#घोषणा MISC_REG_CHIP_TYPE_57811_MASK				 (1<<1)
#घोषणा MISC_REG_CPMU_LP_DR_ENABLE				 0xa858
/* [RW 1] FW EEE LPI Enable. When 1 indicates that EEE LPI mode is enabled
 * by FW. When 0 indicates that the EEE LPI mode is disabled by FW. Clk
 * 25MHz. Reset on hard reset. */
#घोषणा MISC_REG_CPMU_LP_FW_ENABLE_P0				 0xa84c
/* [RW 32] EEE LPI Idle Threshold. The threshold value क्रम the idle EEE LPI
 * counter. Timer tick is 1 us. Clock 25MHz. Reset on hard reset. */
#घोषणा MISC_REG_CPMU_LP_IDLE_THR_P0				 0xa8a0
/* [RW 18] LPI entry events mask. [0] - Vमुख्य SM Mask. When 1 indicates that
 * the Vमुख्य SM end state is disabled. When 0 indicates that the Vमुख्य SM
 * end state is enabled. [1] - FW Queues Empty Mask. When 1 indicates that
 * the FW command that all Queues are empty is disabled. When 0 indicates
 * that the FW command that all Queues are empty is enabled. [2] - FW Early
 * Exit Mask / Reserved (Entry mask). When 1 indicates that the FW Early
 * Exit command is disabled. When 0 indicates that the FW Early Exit command
 * is enabled. This bit applicable only in the EXIT Events Mask रेजिस्टरs.
 * [3] - PBF Request Mask. When 1 indicates that the PBF Request indication
 * is disabled. When 0 indicates that the PBF Request indication is enabled.
 * [4] - Tx Request Mask. When =1 indicates that the Tx other Than PBF
 * Request indication is disabled. When 0 indicates that the Tx Other Than
 * PBF Request indication is enabled. [5] - Rx EEE LPI Status Mask. When 1
 * indicates that the RX EEE LPI Status indication is disabled. When 0
 * indicates that the RX EEE LPI Status indication is enabled. In the EXIT
 * Events Masks रेजिस्टरs; this bit masks the falling edge detect of the LPI
 * Status (Rx LPI is on - off). [6] - Tx Pause Mask. When 1 indicates that
 * the Tx Pause indication is disabled. When 0 indicates that the Tx Pause
 * indication is enabled. [7] - BRB1 Empty Mask. When 1 indicates that the
 * BRB1 EMPTY indication is disabled. When 0 indicates that the BRB1 EMPTY
 * indication is enabled. [8] - QM Idle Mask. When 1 indicates that the QM
 * IDLE indication is disabled. When 0 indicates that the QM IDLE indication
 * is enabled. (One bit क्रम both VOQ0 and VOQ1). [9] - QM LB Idle Mask. When
 * 1 indicates that the QM IDLE indication क्रम LOOPBACK is disabled. When 0
 * indicates that the QM IDLE indication क्रम LOOPBACK is enabled. [10] - L1
 * Status Mask. When 1 indicates that the L1 Status indication from the PCIE
 * CORE is disabled. When 0 indicates that the RX EEE LPI Status indication
 * from the PCIE CORE is enabled. In the EXIT Events Masks रेजिस्टरs; this
 * bit masks the falling edge detect of the L1 status (L1 is on - off). [11]
 * - P0 E0 EEE EEE LPI REQ Mask. When =1 indicates that the P0 E0 EEE EEE
 * LPI REQ indication is disabled. When =0 indicates that the P0 E0 EEE LPI
 * REQ indication is enabled. [12] - P1 E0 EEE LPI REQ Mask. When =1
 * indicates that the P0 EEE LPI REQ indication is disabled. When =0
 * indicates that the P0 EEE LPI REQ indication is enabled. [13] - P0 E1 EEE
 * LPI REQ Mask. When =1 indicates that the P0 EEE LPI REQ indication is
 * disabled. When =0 indicates that the P0 EEE LPI REQ indication is
 * enabled. [14] - P1 E1 EEE LPI REQ Mask. When =1 indicates that the P0 EEE
 * LPI REQ indication is disabled. When =0 indicates that the P0 EEE LPI REQ
 * indication is enabled. [15] - L1 REQ Mask. When =1 indicates that the L1
 * REQ indication is disabled. When =0 indicates that the L1 indication is
 * enabled. [16] - Rx EEE LPI Status Edge Detect Mask. When =1 indicates
 * that the RX EEE LPI Status Falling Edge Detect indication is disabled (Rx
 * EEE LPI is on - off). When =0 indicates that the RX EEE LPI Status
 * Falling Edge Detec indication is enabled (Rx EEE LPI is on - off). This
 * bit is applicable only in the EXIT Events Masks रेजिस्टरs. [17] - L1
 * Status Edge Detect Mask. When =1 indicates that the L1 Status Falling
 * Edge Detect indication from the PCIE CORE is disabled (L1 is on - off).
 * When =0 indicates that the L1 Status Falling Edge Detect indication from
 * the PCIE CORE is enabled (L1 is on - off). This bit is applicable only in
 * the EXIT Events Masks रेजिस्टरs. Clock 25MHz. Reset on hard reset. */
#घोषणा MISC_REG_CPMU_LP_MASK_ENT_P0				 0xa880
/* [RW 18] EEE LPI निकास events mask. [0] - Vमुख्य SM Mask. When 1 indicates
 * that the Vमुख्य SM end state is disabled. When 0 indicates that the Vमुख्य
 * SM end state is enabled. [1] - FW Queues Empty Mask. When 1 indicates
 * that the FW command that all Queues are empty is disabled. When 0
 * indicates that the FW command that all Queues are empty is enabled. [2] -
 * FW Early Exit Mask / Reserved (Entry mask). When 1 indicates that the FW
 * Early Exit command is disabled. When 0 indicates that the FW Early Exit
 * command is enabled. This bit applicable only in the EXIT Events Mask
 * रेजिस्टरs. [3] - PBF Request Mask. When 1 indicates that the PBF Request
 * indication is disabled. When 0 indicates that the PBF Request indication
 * is enabled. [4] - Tx Request Mask. When =1 indicates that the Tx other
 * Than PBF Request indication is disabled. When 0 indicates that the Tx
 * Other Than PBF Request indication is enabled. [5] - Rx EEE LPI Status
 * Mask. When 1 indicates that the RX EEE LPI Status indication is disabled.
 * When 0 indicates that the RX LPI Status indication is enabled. In the
 * EXIT Events Masks रेजिस्टरs; this bit masks the falling edge detect of
 * the EEE LPI Status (Rx EEE LPI is on - off). [6] - Tx Pause Mask. When 1
 * indicates that the Tx Pause indication is disabled. When 0 indicates that
 * the Tx Pause indication is enabled. [7] - BRB1 Empty Mask. When 1
 * indicates that the BRB1 EMPTY indication is disabled. When 0 indicates
 * that the BRB1 EMPTY indication is enabled. [8] - QM Idle Mask. When 1
 * indicates that the QM IDLE indication is disabled. When 0 indicates that
 * the QM IDLE indication is enabled. (One bit क्रम both VOQ0 and VOQ1). [9]
 * - QM LB Idle Mask. When 1 indicates that the QM IDLE indication क्रम
 * LOOPBACK is disabled. When 0 indicates that the QM IDLE indication क्रम
 * LOOPBACK is enabled. [10] - L1 Status Mask. When 1 indicates that the L1
 * Status indication from the PCIE CORE is disabled. When 0 indicates that
 * the RX EEE LPI Status indication from the PCIE CORE is enabled. In the
 * EXIT Events Masks रेजिस्टरs; this bit masks the falling edge detect of
 * the L1 status (L1 is on - off). [11] - P0 E0 EEE EEE LPI REQ Mask. When
 * =1 indicates that the P0 E0 EEE EEE LPI REQ indication is disabled. When
 * =0 indicates that the P0 E0 EEE LPI REQ indication is enabled. [12] - P1
 * E0 EEE LPI REQ Mask. When =1 indicates that the P0 EEE LPI REQ indication
 * is disabled. When =0 indicates that the P0 EEE LPI REQ indication is
 * enabled. [13] - P0 E1 EEE LPI REQ Mask. When =1 indicates that the P0 EEE
 * LPI REQ indication is disabled. When =0 indicates that the P0 EEE LPI REQ
 * indication is enabled. [14] - P1 E1 EEE LPI REQ Mask. When =1 indicates
 * that the P0 EEE LPI REQ indication is disabled. When =0 indicates that
 * the P0 EEE LPI REQ indication is enabled. [15] - L1 REQ Mask. When =1
 * indicates that the L1 REQ indication is disabled. When =0 indicates that
 * the L1 indication is enabled. [16] - Rx EEE LPI Status Edge Detect Mask.
 * When =1 indicates that the RX EEE LPI Status Falling Edge Detect
 * indication is disabled (Rx EEE LPI is on - off). When =0 indicates that
 * the RX EEE LPI Status Falling Edge Detec indication is enabled (Rx EEE
 * LPI is on - off). This bit is applicable only in the EXIT Events Masks
 * रेजिस्टरs. [17] - L1 Status Edge Detect Mask. When =1 indicates that the
 * L1 Status Falling Edge Detect indication from the PCIE CORE is disabled
 * (L1 is on - off). When =0 indicates that the L1 Status Falling Edge
 * Detect indication from the PCIE CORE is enabled (L1 is on - off). This
 * bit is applicable only in the EXIT Events Masks रेजिस्टरs.Clock 25MHz.
 * Reset on hard reset. */
#घोषणा MISC_REG_CPMU_LP_MASK_EXT_P0				 0xa888
/* [RW 16] EEE LPI Entry Events Counter. A statistic counter with the number
 * of counts that the SM entered the EEE LPI state. Clock 25MHz. Read only
 * रेजिस्टर. Reset on hard reset. */
#घोषणा MISC_REG_CPMU_LP_SM_ENT_CNT_P0				 0xa8b8
/* [RW 16] EEE LPI Entry Events Counter. A statistic counter with the number
 * of counts that the SM entered the EEE LPI state. Clock 25MHz. Read only
 * रेजिस्टर. Reset on hard reset. */
#घोषणा MISC_REG_CPMU_LP_SM_ENT_CNT_P1				 0xa8bc
/* [RW 32] The following driver रेजिस्टरs(1...16) represent 16 drivers and
   32 clients. Each client can be controlled by one driver only. One in each
   bit represent that this driver control the appropriate client (Ex: bit 5
   is set means this driver control client number 5). addr1 = set; addr0 =
   clear; पढ़ो from both addresses will give the same result = status. ग_लिखो
   to address 1 will set a request to control all the clients that their
   appropriate bit (in the ग_लिखो command) is set. अगर the client is मुक्त (the
   appropriate bit in all the other drivers is clear) one will be written to
   that driver रेजिस्टर; अगर the client isn't मुक्त the bit will reमुख्य zero.
   अगर the appropriate bit is set (the driver request to gain control on a
   client it alपढ़ोy controls the ~MISC_REGISTERS_INT_STS.GENERIC_SW
   पूर्णांकerrupt will be निश्चितed). ग_लिखो to address 0 will set a request to
   मुक्त all the clients that their appropriate bit (in the ग_लिखो command) is
   set. अगर the appropriate bit is clear (the driver request to मुक्त a client
   it करोesn't controls the ~MISC_REGISTERS_INT_STS.GENERIC_SW पूर्णांकerrupt will
   be निश्चितed). */
#घोषणा MISC_REG_DRIVER_CONTROL_1				 0xa510
#घोषणा MISC_REG_DRIVER_CONTROL_7				 0xa3c8
/* [RW 1] e1hmf क्रम WOL. If clr WOL संकेत o the PXP will be send on bit 0
   only. */
#घोषणा MISC_REG_E1HMF_MODE					 0xa5f8
/* [R 1] Status of four port mode path swap input pin. */
#घोषणा MISC_REG_FOUR_PORT_PATH_SWAP				 0xa75c
/* [RW 2] 4 port path swap overग_लिखो.[0] - Overग_लिखो control; अगर it is 0 -
   the path_swap output is equal to 4 port mode path swap input pin; अगर it
   is 1 - the path_swap output is equal to bit[1] of this रेजिस्टर; [1] -
   Overग_लिखो value. If bit[0] of this रेजिस्टर is 1 this is the value that
   receives the path_swap output. Reset on Hard reset. */
#घोषणा MISC_REG_FOUR_PORT_PATH_SWAP_OVWR			 0xa738
/* [R 1] Status of 4 port mode port swap input pin. */
#घोषणा MISC_REG_FOUR_PORT_PORT_SWAP				 0xa754
/* [RW 2] 4 port port swap overग_लिखो.[0] - Overग_लिखो control; अगर it is 0 -
   the port_swap output is equal to 4 port mode port swap input pin; अगर it
   is 1 - the port_swap output is equal to bit[1] of this रेजिस्टर; [1] -
   Overग_लिखो value. If bit[0] of this रेजिस्टर is 1 this is the value that
   receives the port_swap output. Reset on Hard reset. */
#घोषणा MISC_REG_FOUR_PORT_PORT_SWAP_OVWR			 0xa734
/* [RW 32] Debug only: spare RW रेजिस्टर reset by core reset */
#घोषणा MISC_REG_GENERIC_CR_0					 0xa460
#घोषणा MISC_REG_GENERIC_CR_1					 0xa464
/* [RW 32] Debug only: spare RW रेजिस्टर reset by por reset */
#घोषणा MISC_REG_GENERIC_POR_1					 0xa474
/* [RW 32] Bit[0]: EPIO MODE SEL: Setting this bit to 1 will allow SW/FW to
   use all of the 32 Extended GPIO pins. Without setting this bit; an EPIO
   can not be configured as an output. Each output has its output enable in
   the MCP रेजिस्टर space; but this bit needs to be set to make use of that.
   Bit[3:1] spare. Bit[4]: WCVTMON_PWRDN: Powerकरोwn क्रम Warpcore VTMON. When
   set to 1 - Powerकरोwn. Bit[5]: WCVTMON_RESETB: Reset क्रम Warpcore VTMON.
   When set to 0 - vTMON is in reset. Bit[6]: setting this bit will change
   the i/o to an output and will drive the TimeSync output. Bit[31:7]:
   spare. Global रेजिस्टर. Reset by hard reset. */
#घोषणा MISC_REG_GEN_PURP_HWG					 0xa9a0
/* [RW 32] GPIO. [31-28] FLOAT port 0; [27-24] FLOAT port 0; When any of
   these bits is written as a '1'; the corresponding SPIO bit will turn off
   it's drivers and become an input. This is the reset state of all GPIO
   pins. The पढ़ो value of these bits will be a '1' अगर that last command
   (#SET; #CLR; or #FLOAT) क्रम this bit was a #FLOAT. (reset value 0xff).
   [23-20] CLR port 1; 19-16] CLR port 0; When any of these bits is written
   as a '1'; the corresponding GPIO bit will drive low. The पढ़ो value of
   these bits will be a '1' अगर that last command (#SET; #CLR; or #FLOAT) क्रम
   this bit was a #CLR. (reset value 0). [15-12] SET port 1; 11-8] port 0;
   SET When any of these bits is written as a '1'; the corresponding GPIO
   bit will drive high (अगर it has that capability). The पढ़ो value of these
   bits will be a '1' अगर that last command (#SET; #CLR; or #FLOAT) क्रम this
   bit was a #SET. (reset value 0). [7-4] VALUE port 1; [3-0] VALUE port 0;
   RO; These bits indicate the पढ़ो value of each of the eight GPIO pins.
   This is the result value of the pin; not the drive value. Writing these
   bits will have not effect. */
#घोषणा MISC_REG_GPIO						 0xa490
/* [RW 8] These bits enable the GPIO_INTs to संकेतs event to the
   IGU/MCP.according to the following map: [0] p0_gpio_0; [1] p0_gpio_1; [2]
   p0_gpio_2; [3] p0_gpio_3; [4] p1_gpio_0; [5] p1_gpio_1; [6] p1_gpio_2;
   [7] p1_gpio_3; */
#घोषणा MISC_REG_GPIO_EVENT_EN					 0xa2bc
/* [RW 32] GPIO INT. [31-28] OLD_CLR port1; [27-24] OLD_CLR port0; Writing a
   '1' to these bit clears the corresponding bit in the #OLD_VALUE रेजिस्टर.
   This will acknowledge an पूर्णांकerrupt on the falling edge of corresponding
   GPIO input (reset value 0). [23-16] OLD_SET [23-16] port1; OLD_SET port0;
   Writing a '1' to these bit sets the corresponding bit in the #OLD_VALUE
   रेजिस्टर. This will acknowledge an पूर्णांकerrupt on the rising edge of
   corresponding SPIO input (reset value 0). [15-12] OLD_VALUE [11-8] port1;
   OLD_VALUE port0; RO; These bits indicate the old value of the GPIO input
   value. When the ~INT_STATE bit is set; this bit indicates the OLD value
   of the pin such that अगर ~INT_STATE is set and this bit is '0'; then the
   पूर्णांकerrupt is due to a low to high edge. If ~INT_STATE is set and this bit
   is '1'; then the पूर्णांकerrupt is due to a high to low edge (reset value 0).
   [7-4] INT_STATE port1; [3-0] INT_STATE RO port0; These bits indicate the
   current GPIO पूर्णांकerrupt state क्रम each GPIO pin. This bit is cleared when
   the appropriate #OLD_SET or #OLD_CLR command bit is written. This bit is
   set when the GPIO input करोes not match the current value in #OLD_VALUE
   (reset value 0). */
#घोषणा MISC_REG_GPIO_INT					 0xa494
/* [R 28] this field hold the last inक्रमmation that caused reserved
   attention. bits [19:0] - address; [22:20] function; [23] reserved;
   [27:24] the master that caused the attention - according to the following
   encodeing:1 = pxp; 2 = mcp; 3 = usdm; 4 = tsdm; 5 = xsdm; 6 = csdm; 7 =
   dbu; 8 = dmae */
#घोषणा MISC_REG_GRC_RSV_ATTN					 0xa3c0
/* [R 28] this field hold the last inक्रमmation that caused समयout
   attention. bits [19:0] - address; [22:20] function; [23] reserved;
   [27:24] the master that caused the attention - according to the following
   encodeing:1 = pxp; 2 = mcp; 3 = usdm; 4 = tsdm; 5 = xsdm; 6 = csdm; 7 =
   dbu; 8 = dmae */
#घोषणा MISC_REG_GRC_TIMEOUT_ATTN				 0xa3c4
/* [RW 1] Setting this bit enables a समयr in the GRC block to समयout any
   access that करोes not finish within
   ~misc_रेजिस्टरs_grc_timout_val.grc_समयout_val cycles. When this bit is
   cleared; this समयout is disabled. If this समयout occurs; the GRC shall
   निश्चित it attention output. */
#घोषणा MISC_REG_GRC_TIMEOUT_EN 				 0xa280
/* [RW 28] 28 LSB of LCPLL first रेजिस्टर; reset val = 521. inside order of
   the bits is: [2:0] OAC reset value 001) CML output buffer bias control;
   111 क्रम +40%; 011 क्रम +20%; 001 क्रम 0%; 000 क्रम -20%. [5:3] Icp_ctrl
   (reset value 001) Charge pump current control; 111 क्रम 720u; 011 क्रम
   600u; 001 क्रम 480u and 000 क्रम 360u. [7:6] Bias_ctrl (reset value 00)
   Global bias control; When bit 7 is high bias current will be 10 0gh; When
   bit 6 is high bias will be 100w; Valid values are 00; 10; 01. [10:8]
   Pll_observe (reset value 010) Bits to control observability. bit 10 is
   क्रम test bias; bit 9 is क्रम test CK; bit 8 is test Vc. [12:11] Vth_ctrl
   (reset value 00) Comparator threshold control. 00 क्रम 0.6V; 01 क्रम 0.54V
   and 10 क्रम 0.66V. [13] pllSeqStart (reset value 0) Enables VCO tuning
   sequencer: 1= sequencer disabled; 0= sequencer enabled (inverted
   पूर्णांकernally). [14] reserved (reset value 0) Reset क्रम VCO sequencer is
   connected to RESET input directly. [15] capRetry_en (reset value 0)
   enable retry on cap search failure (inverted). [16] freqMonitor_e (reset
   value 0) bit to continuously monitor vco freq (inverted). [17]
   freqDetRestart_en (reset value 0) bit to enable restart when not freq
   locked (inverted). [18] freqDetRetry_en (reset value 0) bit to enable
   retry on freq det failure(inverted). [19] pllForceFकरोne_en (reset value
   0) bit to enable pllForceFकरोne & pllForceFpass पूर्णांकo pllSeq. [20]
   pllForceFकरोne (reset value 0) bit to क्रमce freqDone. [21] pllForceFpass
   (reset value 0) bit to क्रमce freqPass. [22] pllForceDone_en (reset value
   0) bit to enable pllForceCapDone. [23] pllForceCapDone (reset value 0)
   bit to क्रमce capDone. [24] pllForceCapPass_en (reset value 0) bit to
   enable pllForceCapPass. [25] pllForceCapPass (reset value 0) bit to क्रमce
   capPass. [26] capRestart (reset value 0) bit to क्रमce cap sequencer to
   restart. [27] capSelectM_en (reset value 0) bit to enable cap select
   रेजिस्टर bits. */
#घोषणा MISC_REG_LCPLL_CTRL_1					 0xa2a4
#घोषणा MISC_REG_LCPLL_CTRL_REG_2				 0xa2a8
/* [RW 1] LCPLL घातer करोwn. Global रेजिस्टर. Active High. Reset on POR
 * reset. */
#घोषणा MISC_REG_LCPLL_E40_PWRDWN				 0xaa74
/* [RW 1] LCPLL VCO reset. Global रेजिस्टर. Active Low Reset on POR reset. */
#घोषणा MISC_REG_LCPLL_E40_RESETB_ANA				 0xaa78
/* [RW 1] LCPLL post-भागider reset. Global रेजिस्टर. Active Low Reset on POR
 * reset. */
#घोषणा MISC_REG_LCPLL_E40_RESETB_DIG				 0xaa7c
/* [RW 4] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा MISC_REG_MISC_INT_MASK					 0xa388
/* [RW 1] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा MISC_REG_MISC_PRTY_MASK 				 0xa398
/* [R 1] Parity रेजिस्टर #0 पढ़ो */
#घोषणा MISC_REG_MISC_PRTY_STS					 0xa38c
/* [RC 1] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा MISC_REG_MISC_PRTY_STS_CLR				 0xa390
#घोषणा MISC_REG_NIG_WOL_P0					 0xa270
#घोषणा MISC_REG_NIG_WOL_P1					 0xa274
/* [R 1] If set indicate that the pcie_rst_b was निश्चितed without perst
   निश्चितion */
#घोषणा MISC_REG_PCIE_HOT_RESET 				 0xa618
/* [RW 32] 32 LSB of storm PLL first रेजिस्टर; reset val = 0x 071d2911.
   inside order of the bits is: [0] P1 भागider[0] (reset value 1); [1] P1
   भागider[1] (reset value 0); [2] P1 भागider[2] (reset value 0); [3] P1
   भागider[3] (reset value 0); [4] P2 भागider[0] (reset value 1); [5] P2
   भागider[1] (reset value 0); [6] P2 भागider[2] (reset value 0); [7] P2
   भागider[3] (reset value 0); [8] ph_det_dis (reset value 1); [9]
   freq_det_dis (reset value 0); [10] Icpx[0] (reset value 0); [11] Icpx[1]
   (reset value 1); [12] Icpx[2] (reset value 0); [13] Icpx[3] (reset value
   1); [14] Icpx[4] (reset value 0); [15] Icpx[5] (reset value 0); [16]
   Rx[0] (reset value 1); [17] Rx[1] (reset value 0); [18] vc_en (reset
   value 1); [19] vco_rng[0] (reset value 1); [20] vco_rng[1] (reset value
   1); [21] Kvco_xf[0] (reset value 0); [22] Kvco_xf[1] (reset value 0);
   [23] Kvco_xf[2] (reset value 0); [24] Kvco_xs[0] (reset value 1); [25]
   Kvco_xs[1] (reset value 1); [26] Kvco_xs[2] (reset value 1); [27]
   testd_en (reset value 0); [28] testd_sel[0] (reset value 0); [29]
   testd_sel[1] (reset value 0); [30] testd_sel[2] (reset value 0); [31]
   testa_en (reset value 0); */
#घोषणा MISC_REG_PLL_STORM_CTRL_1				 0xa294
#घोषणा MISC_REG_PLL_STORM_CTRL_2				 0xa298
#घोषणा MISC_REG_PLL_STORM_CTRL_3				 0xa29c
#घोषणा MISC_REG_PLL_STORM_CTRL_4				 0xa2a0
/* [R 1] Status of 4 port mode enable input pin. */
#घोषणा MISC_REG_PORT4MODE_EN					 0xa750
/* [RW 2] 4 port mode enable overग_लिखो.[0] - Overग_लिखो control; अगर it is 0 -
 * the port4mode_en output is equal to 4 port mode input pin; अगर it is 1 -
 * the port4mode_en output is equal to bit[1] of this रेजिस्टर; [1] -
 * Overग_लिखो value. If bit[0] of this रेजिस्टर is 1 this is the value that
 * receives the port4mode_en output . */
#घोषणा MISC_REG_PORT4MODE_EN_OVWR				 0xa720
/* [RW 32] reset reg#2; rite/पढ़ो one = the specअगरic block is out of reset;
   ग_लिखो/पढ़ो zero = the specअगरic block is in reset; addr 0-wr- the ग_लिखो
   value will be written to the रेजिस्टर; addr 1-set - one will be written
   to all the bits that have the value of one in the data written (bits that
   have the value of zero will not be change) ; addr 2-clear - zero will be
   written to all the bits that have the value of one in the data written
   (bits that have the value of zero will not be change); addr 3-ignore;
   पढ़ो ignore from all addr except addr 00; inside order of the bits is:
   [0] rst_bmac0; [1] rst_bmac1; [2] rst_emac0; [3] rst_emac1; [4] rst_grc;
   [5] rst_mcp_n_reset_reg_hard_core; [6] rst_ mcp_n_hard_core_rst_b; [7]
   rst_ mcp_n_reset_cmn_cpu; [8] rst_ mcp_n_reset_cmn_core; [9] rst_rbcn;
   [10] rst_dbg; [11] rst_misc_core; [12] rst_dbue (UART); [13]
   Pci_reseपंचांगdio_n; [14] rst_emac0_hard_core; [15] rst_emac1_hard_core; 16]
   rst_pxp_rq_rd_wr; 31:17] reserved */
#घोषणा MISC_REG_RESET_REG_1					 0xa580
#घोषणा MISC_REG_RESET_REG_2					 0xa590
/* [RW 20] 20 bit GRC address where the scratch-pad of the MCP that is
   shared with the driver resides */
#घोषणा MISC_REG_SHARED_MEM_ADDR				 0xa2b4
/* [RW 32] SPIO. [31-24] FLOAT When any of these bits is written as a '1';
   the corresponding SPIO bit will turn off it's drivers and become an
   input. This is the reset state of all SPIO pins. The पढ़ो value of these
   bits will be a '1' अगर that last command (#SET; #CL; or #FLOAT) क्रम this
   bit was a #FLOAT. (reset value 0xff). [23-16] CLR When any of these bits
   is written as a '1'; the corresponding SPIO bit will drive low. The पढ़ो
   value of these bits will be a '1' अगर that last command (#SET; #CLR; or
#FLOAT) क्रम this bit was a #CLR. (reset value 0). [15-8] SET When any of
   these bits is written as a '1'; the corresponding SPIO bit will drive
   high (अगर it has that capability). The पढ़ो value of these bits will be a
   '1' अगर that last command (#SET; #CLR; or #FLOAT) क्रम this bit was a #SET.
   (reset value 0). [7-0] VALUE RO; These bits indicate the पढ़ो value of
   each of the eight SPIO pins. This is the result value of the pin; not the
   drive value. Writing these bits will have not effect. Each 8 bits field
   is भागided as follows: [0] VAUX Enable; when pulsed low; enables supply
   from VAUX. (This is an output pin only; the FLOAT field is not applicable
   क्रम this pin); [1] VAUX Disable; when pulsed low; disables supply क्रमm
   VAUX. (This is an output pin only; FLOAT field is not applicable क्रम this
   pin); [2] SEL_VAUX_B - Control to घातer चयनing logic. Drive low to
   select VAUX supply. (This is an output pin only; it is not controlled by
   the SET and CLR fields; it is controlled by the Main Power SM; the FLOAT
   field is not applicable क्रम this pin; only the VALUE fields is relevant -
   it reflects the output value); [3] port swap [4] spio_4; [5] spio_5; [6]
   Bit 0 of UMP device ID select; पढ़ो by UMP firmware; [7] Bit 1 of UMP
   device ID select; पढ़ो by UMP firmware. */
#घोषणा MISC_REG_SPIO						 0xa4fc
/* [RW 8] These bits enable the SPIO_INTs to संकेतs event to the IGU/MC.
   according to the following map: [3:0] reserved; [4] spio_4 [5] spio_5;
   [7:0] reserved */
#घोषणा MISC_REG_SPIO_EVENT_EN					 0xa2b8
/* [RW 32] SPIO INT. [31-24] OLD_CLR Writing a '1' to these bit clears the
   corresponding bit in the #OLD_VALUE रेजिस्टर. This will acknowledge an
   पूर्णांकerrupt on the falling edge of corresponding SPIO input (reset value
   0). [23-16] OLD_SET Writing a '1' to these bit sets the corresponding bit
   in the #OLD_VALUE रेजिस्टर. This will acknowledge an पूर्णांकerrupt on the
   rising edge of corresponding SPIO input (reset value 0). [15-8] OLD_VALUE
   RO; These bits indicate the old value of the SPIO input value. When the
   ~INT_STATE bit is set; this bit indicates the OLD value of the pin such
   that अगर ~INT_STATE is set and this bit is '0'; then the पूर्णांकerrupt is due
   to a low to high edge. If ~INT_STATE is set and this bit is '1'; then the
   पूर्णांकerrupt is due to a high to low edge (reset value 0). [7-0] INT_STATE
   RO; These bits indicate the current SPIO पूर्णांकerrupt state क्रम each SPIO
   pin. This bit is cleared when the appropriate #OLD_SET or #OLD_CLR
   command bit is written. This bit is set when the SPIO input करोes not
   match the current value in #OLD_VALUE (reset value 0). */
#घोषणा MISC_REG_SPIO_INT					 0xa500
/* [RW 32] reload value क्रम counter 4 अगर reload; the value will be reload अगर
   the counter reached zero and the reload bit
   (~misc_रेजिस्टरs_sw_समयr_cfg_4.sw_समयr_cfg_4[1] ) is set */
#घोषणा MISC_REG_SW_TIMER_RELOAD_VAL_4				 0xa2fc
/* [RW 32] the value of the counter क्रम sw समयrs1-8. there are 8 addresses
   in this रेजिस्टर. address 0 - समयr 1; address 1 - समयr 2, ...  address 7 -
   समयr 8 */
#घोषणा MISC_REG_SW_TIMER_VAL					 0xa5c0
/* [R 1] Status of two port mode path swap input pin. */
#घोषणा MISC_REG_TWO_PORT_PATH_SWAP				 0xa758
/* [RW 2] 2 port swap overग_लिखो.[0] - Overग_लिखो control; अगर it is 0 - the
   path_swap output is equal to 2 port mode path swap input pin; अगर it is 1
   - the path_swap output is equal to bit[1] of this रेजिस्टर; [1] -
   Overग_लिखो value. If bit[0] of this रेजिस्टर is 1 this is the value that
   receives the path_swap output. Reset on Hard reset. */
#घोषणा MISC_REG_TWO_PORT_PATH_SWAP_OVWR			 0xa72c
/* [RW 1] Set by the MCP to remember अगर one or more of the drivers is/are
   loaded; 0-prepare; -unprepare */
#घोषणा MISC_REG_UNPREPARED					 0xa424
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_BRCST	 (0x1<<0)
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_MLCST	 (0x1<<1)
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_NO_VLAN	 (0x1<<4)
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_UNCST	 (0x1<<2)
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_VLAN	 (0x1<<3)
/* [RW 5] MDIO PHY Address. The WC uses this address to determine whether or
 * not it is the recipient of the message on the MDIO पूर्णांकerface. The value
 * is compared to the value on ctrl_md_devad. Drives output
 * misc_xgxs0_phy_addr. Global रेजिस्टर. */
#घोषणा MISC_REG_WC0_CTRL_PHY_ADDR				 0xa9cc
#घोषणा MISC_REG_WC0_RESET					 0xac30
/* [RW 2] XMAC Core port mode. Indicates the number of ports on the प्रणाली
   side. This should be less than or equal to phy_port_mode; अगर some of the
   ports are not used. This enables reduction of frequency on the core side.
   This is a strap input क्रम the XMAC_MP core. 00 - Single Port Mode; 01 -
   Dual Port Mode; 10 - Tri Port Mode; 11 - Quad Port Mode. This is a strap
   input क्रम the XMAC_MP core; and should be changed only जबतक reset is
   held low. Reset on Hard reset. */
#घोषणा MISC_REG_XMAC_CORE_PORT_MODE				 0xa964
/* [RW 2] XMAC PHY port mode. Indicates the number of ports on the Warp
   Core. This is a strap input क्रम the XMAC_MP core. 00 - Single Port Mode;
   01 - Dual Port Mode; 1x - Quad Port Mode; This is a strap input क्रम the
   XMAC_MP core; and should be changed only जबतक reset is held low. Reset
   on Hard reset. */
#घोषणा MISC_REG_XMAC_PHY_PORT_MODE				 0xa960
/* [RW 32] 1 [47] Packet Size = 64 Write to this रेजिस्टर ग_लिखो bits 31:0.
 * Reads from this रेजिस्टर will clear bits 31:0. */
#घोषणा MSTAT_REG_RX_STAT_GR64_LO				 0x200
/* [RW 32] 1 [00] Tx Good Packet Count Write to this रेजिस्टर ग_लिखो bits
 * 31:0. Reads from this रेजिस्टर will clear bits 31:0. */
#घोषणा MSTAT_REG_TX_STAT_GTXPOK_LO				 0
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_BRCST	 (0x1<<0)
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_MLCST	 (0x1<<1)
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_NO_VLAN	 (0x1<<4)
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_UNCST	 (0x1<<2)
#घोषणा NIG_LLH0_BRB1_DRV_MASK_REG_LLH0_BRB1_DRV_MASK_VLAN	 (0x1<<3)
#घोषणा NIG_LLH0_XCM_MASK_REG_LLH0_XCM_MASK_BCN			 (0x1<<0)
#घोषणा NIG_LLH1_XCM_MASK_REG_LLH1_XCM_MASK_BCN			 (0x1<<0)
#घोषणा NIG_MASK_INTERRUPT_PORT0_REG_MASK_EMAC0_MISC_MI_INT	 (0x1<<0)
#घोषणा NIG_MASK_INTERRUPT_PORT0_REG_MASK_SERDES0_LINK_STATUS	 (0x1<<9)
#घोषणा NIG_MASK_INTERRUPT_PORT0_REG_MASK_XGXS0_LINK10G 	 (0x1<<15)
#घोषणा NIG_MASK_INTERRUPT_PORT0_REG_MASK_XGXS0_LINK_STATUS	 (0xf<<18)
/* [RW 1] Input enable क्रम RX_BMAC0 IF */
#घोषणा NIG_REG_BMAC0_IN_EN					 0x100ac
/* [RW 1] output enable क्रम TX_BMAC0 IF */
#घोषणा NIG_REG_BMAC0_OUT_EN					 0x100e0
/* [RW 1] output enable क्रम TX BMAC छोड़ो port 0 IF */
#घोषणा NIG_REG_BMAC0_PAUSE_OUT_EN				 0x10110
/* [RW 1] output enable क्रम RX_BMAC0_REGS IF */
#घोषणा NIG_REG_BMAC0_REGS_OUT_EN				 0x100e8
/* [RW 1] output enable क्रम RX BRB1 port0 IF */
#घोषणा NIG_REG_BRB0_OUT_EN					 0x100f8
/* [RW 1] Input enable क्रम TX BRB1 छोड़ो port 0 IF */
#घोषणा NIG_REG_BRB0_PAUSE_IN_EN				 0x100c4
/* [RW 1] output enable क्रम RX BRB1 port1 IF */
#घोषणा NIG_REG_BRB1_OUT_EN					 0x100fc
/* [RW 1] Input enable क्रम TX BRB1 छोड़ो port 1 IF */
#घोषणा NIG_REG_BRB1_PAUSE_IN_EN				 0x100c8
/* [RW 1] output enable क्रम RX BRB1 LP IF */
#घोषणा NIG_REG_BRB_LB_OUT_EN					 0x10100
/* [WB_W 82] Debug packet to LP from RBC; Data spelling:[63:0] data; 64]
   error; [67:65]eop_bvalid; [68]eop; [69]sop; [70]port_id; 71]flush;
   72:73]-vnic_num; 81:74]-sideband_info */
#घोषणा NIG_REG_DEBUG_PACKET_LB 				 0x10800
/* [RW 1] Input enable क्रम TX Debug packet */
#घोषणा NIG_REG_EGRESS_DEBUG_IN_EN				 0x100dc
/* [RW 1] If 1 - egress drain mode क्रम port0 is active. In this mode all
   packets from PBFare not क्रमwarded to the MAC and just deleted from FIFO.
   First packet may be deleted from the middle. And last packet will be
   always deleted till the end. */
#घोषणा NIG_REG_EGRESS_DRAIN0_MODE				 0x10060
/* [RW 1] Output enable to EMAC0 */
#घोषणा NIG_REG_EGRESS_EMAC0_OUT_EN				 0x10120
/* [RW 1] MAC configuration क्रम packets of port0. If 1 - all packet outमाला_दो
   to emac क्रम port0; other way to bmac क्रम port0 */
#घोषणा NIG_REG_EGRESS_EMAC0_PORT				 0x10058
/* [RW 1] Input enable क्रम TX PBF user packet port0 IF */
#घोषणा NIG_REG_EGRESS_PBF0_IN_EN				 0x100cc
/* [RW 1] Input enable क्रम TX PBF user packet port1 IF */
#घोषणा NIG_REG_EGRESS_PBF1_IN_EN				 0x100d0
/* [RW 1] Input enable क्रम TX UMP management packet port0 IF */
#घोषणा NIG_REG_EGRESS_UMP0_IN_EN				 0x100d4
/* [RW 1] Input enable क्रम RX_EMAC0 IF */
#घोषणा NIG_REG_EMAC0_IN_EN					 0x100a4
/* [RW 1] output enable क्रम TX EMAC छोड़ो port 0 IF */
#घोषणा NIG_REG_EMAC0_PAUSE_OUT_EN				 0x10118
/* [R 1] status from emac0. This bit is set when MDINT from either the
   EXT_MDINT pin or from the Copper PHY is driven low. This condition must
   be cleared in the attached PHY device that is driving the MINT pin. */
#घोषणा NIG_REG_EMAC0_STATUS_MISC_MI_INT			 0x10494
/* [WB 48] This address space contains BMAC0 रेजिस्टरs. The BMAC रेजिस्टरs
   are described in appendix A. In order to access the BMAC0 रेजिस्टरs; the
   base address; NIG_REGISTERS_INGRESS_BMAC0_MEM; Offset: 0x10c00; should be
   added to each BMAC रेजिस्टर offset */
#घोषणा NIG_REG_INGRESS_BMAC0_MEM				 0x10c00
/* [WB 48] This address space contains BMAC1 रेजिस्टरs. The BMAC रेजिस्टरs
   are described in appendix A. In order to access the BMAC0 रेजिस्टरs; the
   base address; NIG_REGISTERS_INGRESS_BMAC1_MEM; Offset: 0x11000; should be
   added to each BMAC रेजिस्टर offset */
#घोषणा NIG_REG_INGRESS_BMAC1_MEM				 0x11000
/* [R 1] FIFO empty in EOP descriptor FIFO of LP in NIG_RX_EOP */
#घोषणा NIG_REG_INGRESS_EOP_LB_EMPTY				 0x104e0
/* [RW 17] Debug only. RX_EOP_DSCR_lb_FIFO in NIG_RX_EOP. Data
   packet_length[13:0]; mac_error[14]; trunc_error[15]; parity[16] */
#घोषणा NIG_REG_INGRESS_EOP_LB_FIFO				 0x104e4
/* [RW 27] 0 - must be active क्रम Everest A0; 1- क्रम Everest B0 when latch
   logic क्रम पूर्णांकerrupts must be used. Enable per bit of पूर्णांकerrupt of
   ~latch_status.latch_status */
#घोषणा NIG_REG_LATCH_BC_0					 0x16210
/* [RW 27] Latch क्रम each पूर्णांकerrupt from Unicore.b[0]
   status_emac0_misc_mi_पूर्णांक; b[1] status_emac0_misc_mi_complete;
   b[2]status_emac0_misc_cfg_change; b[3]status_emac0_misc_link_status;
   b[4]status_emac0_misc_link_change; b[5]status_emac0_misc_attn;
   b[6]status_serdes0_mac_crs; b[7]status_serdes0_स्वतःneg_complete;
   b[8]status_serdes0_fiber_rxact; b[9]status_serdes0_link_status;
   b[10]status_serdes0_mr_page_rx; b[11]status_serdes0_cl73_an_complete;
   b[12]status_serdes0_cl73_mr_page_rx; b[13]status_serdes0_rx_sigdet;
   b[14]status_xgxs0_remotemdioreq; b[15]status_xgxs0_link10g;
   b[16]status_xgxs0_स्वतःneg_complete; b[17]status_xgxs0_fiber_rxact;
   b[21:18]status_xgxs0_link_status; b[22]status_xgxs0_mr_page_rx;
   b[23]status_xgxs0_cl73_an_complete; b[24]status_xgxs0_cl73_mr_page_rx;
   b[25]status_xgxs0_rx_sigdet; b[26]status_xgxs0_mac_crs */
#घोषणा NIG_REG_LATCH_STATUS_0					 0x18000
/* [RW 1] led 10g क्रम port 0 */
#घोषणा NIG_REG_LED_10G_P0					 0x10320
/* [RW 1] led 10g क्रम port 1 */
#घोषणा NIG_REG_LED_10G_P1					 0x10324
/* [RW 1] Port0: This bit is set to enable the use of the
   ~nig_रेजिस्टरs_led_control_blink_rate_p0.led_control_blink_rate_p0 field
   defined below. If this bit is cleared; then the blink rate will be about
   8Hz. */
#घोषणा NIG_REG_LED_CONTROL_BLINK_RATE_ENA_P0			 0x10318
/* [RW 12] Port0: Specअगरies the period of each blink cycle (on + off) क्रम
   Traffic LED in milliseconds. Must be a non-zero value. This 12-bit field
   is reset to 0x080; giving a शेष blink period of approximately 8Hz. */
#घोषणा NIG_REG_LED_CONTROL_BLINK_RATE_P0			 0x10310
/* [RW 1] Port0: If set aदीर्घ with the
 ~nig_रेजिस्टरs_led_control_override_traffic_p0.led_control_override_traffic_p0
   bit and ~nig_रेजिस्टरs_led_control_traffic_p0.led_control_traffic_p0 LED
   bit; the Traffic LED will blink with the blink rate specअगरied in
   ~nig_रेजिस्टरs_led_control_blink_rate_p0.led_control_blink_rate_p0 and
   ~nig_रेजिस्टरs_led_control_blink_rate_ena_p0.led_control_blink_rate_ena_p0
   fields. */
#घोषणा NIG_REG_LED_CONTROL_BLINK_TRAFFIC_P0			 0x10308
/* [RW 1] Port0: If set overrides hardware control of the Traffic LED. The
   Traffic LED will then be controlled via bit ~nig_रेजिस्टरs_
   led_control_traffic_p0.led_control_traffic_p0 and bit
   ~nig_रेजिस्टरs_led_control_blink_traffic_p0.led_control_blink_traffic_p0 */
#घोषणा NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0 		 0x102f8
/* [RW 1] Port0: If set aदीर्घ with the led_control_override_trafic_p0 bit;
   turns on the Traffic LED. If the led_control_blink_traffic_p0 bit is also
   set; the LED will blink with blink rate specअगरied in
   ~nig_रेजिस्टरs_led_control_blink_rate_p0.led_control_blink_rate_p0 and
   ~nig_regsters_led_control_blink_rate_ena_p0.led_control_blink_rate_ena_p0
   fields. */
#घोषणा NIG_REG_LED_CONTROL_TRAFFIC_P0				 0x10300
/* [RW 4] led mode क्रम port0: 0 MAC; 1-3 PHY1; 4 MAC2; 5-7 PHY4; 8-MAC3;
   9-11PHY7; 12 MAC4; 13-15 PHY10; */
#घोषणा NIG_REG_LED_MODE_P0					 0x102f0
/* [RW 3] क्रम port0 enable क्रम llfc ppp and छोड़ो. b0 - brb1 enable; b1-
   tsdm enable; b2- usdm enable */
#घोषणा NIG_REG_LLFC_EGRESS_SRC_ENABLE_0			 0x16070
#घोषणा NIG_REG_LLFC_EGRESS_SRC_ENABLE_1			 0x16074
/* [RW 1] SAFC enable क्रम port0. This रेजिस्टर may get 1 only when
   ~ppp_enable.ppp_enable = 0 and छोड़ो_enable.छोड़ो_enable =0 क्रम the same
   port */
#घोषणा NIG_REG_LLFC_ENABLE_0					 0x16208
#घोषणा NIG_REG_LLFC_ENABLE_1					 0x1620c
/* [RW 16] classes are high-priority क्रम port0 */
#घोषणा NIG_REG_LLFC_HIGH_PRIORITY_CLASSES_0			 0x16058
#घोषणा NIG_REG_LLFC_HIGH_PRIORITY_CLASSES_1			 0x1605c
/* [RW 16] classes are low-priority क्रम port0 */
#घोषणा NIG_REG_LLFC_LOW_PRIORITY_CLASSES_0			 0x16060
#घोषणा NIG_REG_LLFC_LOW_PRIORITY_CLASSES_1			 0x16064
/* [RW 1] Output enable of message to LLFC BMAC IF क्रम port0 */
#घोषणा NIG_REG_LLFC_OUT_EN_0					 0x160c8
#घोषणा NIG_REG_LLFC_OUT_EN_1					 0x160cc
#घोषणा NIG_REG_LLH0_ACPI_PAT_0_CRC				 0x1015c
#घोषणा NIG_REG_LLH0_ACPI_PAT_6_LEN				 0x10154
#घोषणा NIG_REG_LLH0_BRB1_DRV_MASK				 0x10244
#घोषणा NIG_REG_LLH0_BRB1_DRV_MASK_MF				 0x16048
/* [RW 1] send to BRB1 अगर no match on any of RMP rules. */
#घोषणा NIG_REG_LLH0_BRB1_NOT_MCP				 0x1025c
/* [RW 2] Determine the classअगरication participants. 0: no classअगरication.1:
   classअगरication upon VLAN id. 2: classअगरication upon MAC address. 3:
   classअगरication upon both VLAN id & MAC addr. */
#घोषणा NIG_REG_LLH0_CLS_TYPE					 0x16080
/* [RW 32] cm header क्रम llh0 */
#घोषणा NIG_REG_LLH0_CM_HEADER					 0x1007c
#घोषणा NIG_REG_LLH0_DEST_IP_0_1				 0x101dc
#घोषणा NIG_REG_LLH0_DEST_MAC_0_0				 0x101c0
/* [RW 16] destination TCP address 1. The LLH will look क्रम this address in
   all incoming packets. */
#घोषणा NIG_REG_LLH0_DEST_TCP_0 				 0x10220
/* [RW 16] destination UDP address 1 The LLH will look क्रम this address in
   all incoming packets. */
#घोषणा NIG_REG_LLH0_DEST_UDP_0 				 0x10214
#घोषणा NIG_REG_LLH0_ERROR_MASK 				 0x1008c
/* [RW 8] event id क्रम llh0 */
#घोषणा NIG_REG_LLH0_EVENT_ID					 0x10084
#घोषणा NIG_REG_LLH0_FUNC_EN					 0x160fc
#घोषणा NIG_REG_LLH0_FUNC_MEM					 0x16180
#घोषणा NIG_REG_LLH0_FUNC_MEM_ENABLE				 0x16140
#घोषणा NIG_REG_LLH0_FUNC_VLAN_ID				 0x16100
/* [RW 1] Determine the IP version to look क्रम in
   ~nig_रेजिस्टरs_llh0_dest_ip_0.llh0_dest_ip_0. 0 - IPv6; 1-IPv4 */
#घोषणा NIG_REG_LLH0_IPV4_IPV6_0				 0x10208
/* [RW 1] t bit क्रम llh0 */
#घोषणा NIG_REG_LLH0_T_BIT					 0x10074
/* [RW 12] VLAN ID 1. In हाल of VLAN packet the LLH will look क्रम this ID. */
#घोषणा NIG_REG_LLH0_VLAN_ID_0					 0x1022c
/* [RW 8] init credit counter क्रम port0 in LLH */
#घोषणा NIG_REG_LLH0_XCM_INIT_CREDIT				 0x10554
#घोषणा NIG_REG_LLH0_XCM_MASK					 0x10130
#घोषणा NIG_REG_LLH1_BRB1_DRV_MASK				 0x10248
/* [RW 1] send to BRB1 अगर no match on any of RMP rules. */
#घोषणा NIG_REG_LLH1_BRB1_NOT_MCP				 0x102dc
/* [RW 2] Determine the classअगरication participants. 0: no classअगरication.1:
   classअगरication upon VLAN id. 2: classअगरication upon MAC address. 3:
   classअगरication upon both VLAN id & MAC addr. */
#घोषणा NIG_REG_LLH1_CLS_TYPE					 0x16084
/* [RW 32] cm header क्रम llh1 */
#घोषणा NIG_REG_LLH1_CM_HEADER					 0x10080
#घोषणा NIG_REG_LLH1_ERROR_MASK 				 0x10090
/* [RW 8] event id क्रम llh1 */
#घोषणा NIG_REG_LLH1_EVENT_ID					 0x10088
#घोषणा NIG_REG_LLH1_FUNC_EN					 0x16104
#घोषणा NIG_REG_LLH1_FUNC_MEM					 0x161c0
#घोषणा NIG_REG_LLH1_FUNC_MEM_ENABLE				 0x16160
#घोषणा NIG_REG_LLH1_FUNC_MEM_SIZE				 16
/* [RW 1] When this bit is set; the LLH will classअगरy the packet beक्रमe
 * sending it to the BRB or calculating WoL on it. This bit controls port 1
 * only. The legacy llh_multi_function_mode bit controls port 0. */
#घोषणा NIG_REG_LLH1_MF_MODE					 0x18614
/* [RW 8] init credit counter क्रम port1 in LLH */
#घोषणा NIG_REG_LLH1_XCM_INIT_CREDIT				 0x10564
#घोषणा NIG_REG_LLH1_XCM_MASK					 0x10134
/* [RW 1] When this bit is set; the LLH will expect all packets to be with
   e1hov */
#घोषणा NIG_REG_LLH_E1HOV_MODE					 0x160d8
/* [RW 16] Outer VLAN type identअगरier क्रम multi-function mode. In non
 * multi-function mode; it will hold the inner VLAN type. Typically 0x8100.
 */
#घोषणा NIG_REG_LLH_E1HOV_TYPE_1				 0x16028
/* [RW 1] When this bit is set; the LLH will classअगरy the packet beक्रमe
   sending it to the BRB or calculating WoL on it. */
#घोषणा NIG_REG_LLH_MF_MODE					 0x16024
#घोषणा NIG_REG_MASK_INTERRUPT_PORT0				 0x10330
#घोषणा NIG_REG_MASK_INTERRUPT_PORT1				 0x10334
/* [RW 1] Output संकेत from NIG to EMAC0. When set enables the EMAC0 block. */
#घोषणा NIG_REG_NIG_EMAC0_EN					 0x1003c
/* [RW 1] Output संकेत from NIG to EMAC1. When set enables the EMAC1 block. */
#घोषणा NIG_REG_NIG_EMAC1_EN					 0x10040
/* [RW 1] Output संकेत from NIG to TX_EMAC0. When set indicates to the
   EMAC0 to strip the CRC from the ingress packets. */
#घोषणा NIG_REG_NIG_INGRESS_EMAC0_NO_CRC			 0x10044
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा NIG_REG_NIG_INT_STS_0					 0x103b0
#घोषणा NIG_REG_NIG_INT_STS_1					 0x103c0
/* [RC 32] Interrupt रेजिस्टर #0 पढ़ो clear */
#घोषणा NIG_REG_NIG_INT_STS_CLR_0				 0x103b4
/* [R 32] Legacy E1 and E1H location क्रम parity error mask रेजिस्टर. */
#घोषणा NIG_REG_NIG_PRTY_MASK					 0x103dc
/* [RW 32] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा NIG_REG_NIG_PRTY_MASK_0					 0x183c8
#घोषणा NIG_REG_NIG_PRTY_MASK_1					 0x183d8
/* [R 32] Legacy E1 and E1H location क्रम parity error status रेजिस्टर. */
#घोषणा NIG_REG_NIG_PRTY_STS					 0x103d0
/* [R 32] Parity रेजिस्टर #0 पढ़ो */
#घोषणा NIG_REG_NIG_PRTY_STS_0					 0x183bc
#घोषणा NIG_REG_NIG_PRTY_STS_1					 0x183cc
/* [R 32] Legacy E1 and E1H location क्रम parity error status clear रेजिस्टर. */
#घोषणा NIG_REG_NIG_PRTY_STS_CLR				 0x103d4
/* [RC 32] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा NIG_REG_NIG_PRTY_STS_CLR_0				 0x183c0
#घोषणा NIG_REG_NIG_PRTY_STS_CLR_1				 0x183d0
#घोषणा MCPR_IMC_COMMAND_ENABLE					 (1L<<31)
#घोषणा MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT			 16
#घोषणा MCPR_IMC_COMMAND_OPERATION_BITSHIFT			 28
#घोषणा MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT		 8
/* [RW 6] Bit-map indicating which L2 hdrs may appear after the basic
 * Ethernet header. */
#घोषणा NIG_REG_P0_HDRS_AFTER_BASIC				 0x18038
/* [RW 1] HW PFC enable bit. Set this bit to enable the PFC functionality in
 * the NIG. Other flow control modes such as PAUSE and SAFC/LLFC should be
 * disabled when this bit is set. */
#घोषणा NIG_REG_P0_HWPFC_ENABLE				 0x18078
#घोषणा NIG_REG_P0_LLH_FUNC_MEM2				 0x18480
#घोषणा NIG_REG_P0_LLH_FUNC_MEM2_ENABLE			 0x18440
/* [RW 17] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * the host. Bits [15:0] वापस the sequence ID of the packet. Bit 16
 * indicates the validity of the data in the buffer. Writing a 1 to bit 16
 * will clear the buffer.
 */
#घोषणा NIG_REG_P0_LLH_PTP_HOST_BUF_SEQID			 0x1875c
/* [R 32] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * the host. This location वापसs the lower 32 bits of बारtamp value.
 */
#घोषणा NIG_REG_P0_LLH_PTP_HOST_BUF_TS_LSB			 0x18754
/* [R 32] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * the host. This location वापसs the upper 32 bits of बारtamp value.
 */
#घोषणा NIG_REG_P0_LLH_PTP_HOST_BUF_TS_MSB			 0x18758
/* [RW 11] Mask रेजिस्टर क्रम the various parameters used in determining PTP
 * packet presence. Set each bit to 1 to mask out the particular parameter.
 * 0-IPv4 DA 0 of 224.0.1.129. 1-IPv4 DA 1 of 224.0.0.107. 2-IPv6 DA 0 of
 * 0xFF0*:0:0:0:0:0:0:181. 3-IPv6 DA 1 of 0xFF02:0:0:0:0:0:0:6B. 4-UDP
 * destination port 0 of 319. 5-UDP destination port 1 of 320. 6-MAC
 * Ethertype 0 of 0x88F7. 7-configurable MAC Ethertype 1. 8-MAC DA 0 of
 * 0x01-1B-19-00-00-00. 9-MAC DA 1 of 0x01-80-C2-00-00-0E. 10-configurable
 * MAC DA 2. The reset शेष is set to mask out all parameters.
 */
#घोषणा NIG_REG_P0_LLH_PTP_PARAM_MASK				 0x187a0
/* [RW 14] Mask regiser क्रम the rules used in detecting PTP packets. Set
 * each bit to 1 to mask out that particular rule. 0-अणुIPv4 DA 0; UDP DP 0पूर्ण .
 * 1-अणुIPv4 DA 0; UDP DP 1पूर्ण . 2-अणुIPv4 DA 1; UDP DP 0पूर्ण . 3-अणुIPv4 DA 1; UDP DP
 * 1पूर्ण . 4-अणुIPv6 DA 0; UDP DP 0पूर्ण . 5-अणुIPv6 DA 0; UDP DP 1पूर्ण . 6-अणुIPv6 DA 1;
 * UDP DP 0पूर्ण . 7-अणुIPv6 DA 1; UDP DP 1पूर्ण . 8-अणुMAC DA 0; Ethertype 0पूर्ण . 9-अणुMAC
 * DA 1; Ethertype 0पूर्ण . 10-अणुMAC DA 0; Ethertype 1पूर्ण . 11-अणुMAC DA 1; Ethertype
 * 1पूर्ण . 12-अणुMAC DA 2; Ethertype 0पूर्ण . 13-अणुMAC DA 2; Ethertype 1पूर्ण . The reset
 * शेष is to mask out all of the rules. Note that rules 0-3 are क्रम IPv4
 * packets only and require that the packet is IPv4 क्रम the rules to match.
 * Note that rules 4-7 are क्रम IPv6 packets only and require that the packet
 * is IPv6 क्रम the rules to match.
 */
#घोषणा NIG_REG_P0_LLH_PTP_RULE_MASK				 0x187a4
/* [RW 1] Set to 1 to enable PTP packets to be क्रमwarded to the host. */
#घोषणा NIG_REG_P0_LLH_PTP_TO_HOST				 0x187ac
/* [RW 1] Input enable क्रम RX MAC पूर्णांकerface. */
#घोषणा NIG_REG_P0_MAC_IN_EN					 0x185ac
/* [RW 1] Output enable क्रम TX MAC पूर्णांकerface */
#घोषणा NIG_REG_P0_MAC_OUT_EN					 0x185b0
/* [RW 1] Output enable क्रम TX PAUSE संकेत to the MAC. */
#घोषणा NIG_REG_P0_MAC_PAUSE_OUT_EN				 0x185b4
/* [RW 32] Eight 4-bit configurations क्रम specअगरying which COS (0-15 क्रम
 * future expansion) each priorty is to be mapped to. Bits 3:0 specअगरy the
 * COS क्रम priority 0. Bits 31:28 specअगरy the COS क्रम priority 7. The 3-bit
 * priority field is extracted from the outer-most VLAN in receive packet.
 * Only COS 0 and COS 1 are supported in E2. */
#घोषणा NIG_REG_P0_PKT_PRIORITY_TO_COS				 0x18054
/* [RW 6] Enable क्रम TimeSync feature. Bits [2:0] are क्रम RX side. Bits
 * [5:3] are क्रम TX side. Bit 0 enables TimeSync on RX side. Bit 1 enables
 * V1 frame क्रमmat in बारync event detection on RX side. Bit 2 enables V2
 * frame क्रमmat in बारync event detection on RX side. Bit 3 enables
 * TimeSync on TX side. Bit 4 enables V1 frame क्रमmat in बारync event
 * detection on TX side. Bit 5 enables V2 frame क्रमmat in बारync event
 * detection on TX side. Note that क्रम HW to detect PTP packet and extract
 * data from the packet, at least one of the version bits of that traffic
 * direction has to be enabled.
 */
#घोषणा NIG_REG_P0_PTP_EN					 0x18788
/* [RW 16] Bit-map indicating which SAFC/PFC priorities to map to COS 0. A
 * priority is mapped to COS 0 when the corresponding mask bit is 1. More
 * than one bit may be set; allowing multiple priorities to be mapped to one
 * COS. */
#घोषणा NIG_REG_P0_RX_COS0_PRIORITY_MASK			 0x18058
/* [RW 16] Bit-map indicating which SAFC/PFC priorities to map to COS 1. A
 * priority is mapped to COS 1 when the corresponding mask bit is 1. More
 * than one bit may be set; allowing multiple priorities to be mapped to one
 * COS. */
#घोषणा NIG_REG_P0_RX_COS1_PRIORITY_MASK			 0x1805c
/* [RW 16] Bit-map indicating which SAFC/PFC priorities to map to COS 2. A
 * priority is mapped to COS 2 when the corresponding mask bit is 1. More
 * than one bit may be set; allowing multiple priorities to be mapped to one
 * COS. */
#घोषणा NIG_REG_P0_RX_COS2_PRIORITY_MASK			 0x186b0
/* [RW 16] Bit-map indicating which SAFC/PFC priorities to map to COS 3. A
 * priority is mapped to COS 3 when the corresponding mask bit is 1. More
 * than one bit may be set; allowing multiple priorities to be mapped to one
 * COS. */
#घोषणा NIG_REG_P0_RX_COS3_PRIORITY_MASK			 0x186b4
/* [RW 16] Bit-map indicating which SAFC/PFC priorities to map to COS 4. A
 * priority is mapped to COS 4 when the corresponding mask bit is 1. More
 * than one bit may be set; allowing multiple priorities to be mapped to one
 * COS. */
#घोषणा NIG_REG_P0_RX_COS4_PRIORITY_MASK			 0x186b8
/* [RW 16] Bit-map indicating which SAFC/PFC priorities to map to COS 5. A
 * priority is mapped to COS 5 when the corresponding mask bit is 1. More
 * than one bit may be set; allowing multiple priorities to be mapped to one
 * COS. */
#घोषणा NIG_REG_P0_RX_COS5_PRIORITY_MASK			 0x186bc
/* [R 1] RX FIFO क्रम receiving data from MAC is empty. */
/* [RW 15] Specअगरy which of the credit रेजिस्टरs the client is to be mapped
 * to. Bits[2:0] are क्रम client 0; bits [14:12] are क्रम client 4. For
 * clients that are not subject to WFQ credit blocking - their
 * specअगरications here are not used. */
#घोषणा NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP			 0x180f0
/* [RW 32] Specअगरy which of the credit रेजिस्टरs the client is to be mapped
 * to. This रेजिस्टर specअगरies bits 31:0 of the 36-bit value. Bits[3:0] are
 * क्रम client 0; bits [35:32] are क्रम client 8. For clients that are not
 * subject to WFQ credit blocking - their specअगरications here are not used.
 * This is a new रेजिस्टर (with 2_) added in E3 B0 to accommodate the 9
 * input clients to ETS arbiter. The reset शेष is set क्रम management and
 * debug to use credit रेजिस्टरs 6, 7, and 8, respectively, and COSes 0-5 to
 * use credit रेजिस्टरs 0-5 respectively (0x543210876). Note that credit
 * रेजिस्टरs can not be shared between clients. */
#घोषणा NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP2_LSB		 0x18688
/* [RW 4] Specअगरy which of the credit रेजिस्टरs the client is to be mapped
 * to. This रेजिस्टर specअगरies bits 35:32 of the 36-bit value. Bits[3:0] are
 * क्रम client 0; bits [35:32] are क्रम client 8. For clients that are not
 * subject to WFQ credit blocking - their specअगरications here are not used.
 * This is a new रेजिस्टर (with 2_) added in E3 B0 to accommodate the 9
 * input clients to ETS arbiter. The reset शेष is set क्रम management and
 * debug to use credit रेजिस्टरs 6, 7, and 8, respectively, and COSes 0-5 to
 * use credit रेजिस्टरs 0-5 respectively (0x543210876). Note that credit
 * रेजिस्टरs can not be shared between clients. */
#घोषणा NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP2_MSB		 0x1868c
/* [RW 5] Specअगरy whether the client competes directly in the strict
 * priority arbiter. The bits are mapped according to client ID (client IDs
 * are defined in tx_arb_priority_client). Default value is set to enable
 * strict priorities क्रम clients 0-2 -- management and debug traffic. */
#घोषणा NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT			 0x180e8
/* [RW 5] Specअगरy whether the client is subject to WFQ credit blocking. The
 * bits are mapped according to client ID (client IDs are defined in
 * tx_arb_priority_client). Default value is 0 क्रम not using WFQ credit
 * blocking. */
#घोषणा NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ		 0x180ec
/* [RW 32] Specअगरy the upper bound that credit रेजिस्टर 0 is allowed to
 * reach. */
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_0			 0x1810c
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_1			 0x18110
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_2			 0x18114
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_3			 0x18118
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_4			 0x1811c
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_5			 0x186a0
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_6			 0x186a4
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_7			 0x186a8
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_8			 0x186ac
/* [RW 32] Specअगरy the weight (in bytes) to be added to credit रेजिस्टर 0
 * when it is समय to increment. */
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0			 0x180f8
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1			 0x180fc
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_2			 0x18100
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_3			 0x18104
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_4			 0x18108
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_5			 0x18690
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_6			 0x18694
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_7			 0x18698
#घोषणा NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_8			 0x1869c
/* [RW 12] Specअगरy the number of strict priority arbitration slots between
 * two round-robin arbitration slots to aव्योम starvation. A value of 0 means
 * no strict priority cycles - the strict priority with anti-starvation
 * arbiter becomes a round-robin arbiter. */
#घोषणा NIG_REG_P0_TX_ARB_NUM_STRICT_ARB_SLOTS			 0x180f4
/* [RW 15] Specअगरy the client number to be asचिन्हित to each priority of the
 * strict priority arbiter. Priority 0 is the highest priority. Bits [2:0]
 * are क्रम priority 0 client; bits [14:12] are क्रम priority 4 client. The
 * clients are asचिन्हित the following IDs: 0-management; 1-debug traffic
 * from this port; 2-debug traffic from other port; 3-COS0 traffic; 4-COS1
 * traffic. The reset value[14:0] is set to 0x4688 (15'b100_011_010_001_000)
 * क्रम management at priority 0; debug traffic at priorities 1 and 2; COS0
 * traffic at priority 3; and COS1 traffic at priority 4. */
#घोषणा NIG_REG_P0_TX_ARB_PRIORITY_CLIENT			 0x180e4
/* [RW 6] Bit-map indicating which L2 hdrs may appear after the basic
 * Ethernet header. */
#घोषणा NIG_REG_P1_HDRS_AFTER_BASIC				 0x1818c
#घोषणा NIG_REG_P1_LLH_FUNC_MEM2				 0x184c0
#घोषणा NIG_REG_P1_LLH_FUNC_MEM2_ENABLE			 0x18460a
/* [RW 17] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * the host. Bits [15:0] वापस the sequence ID of the packet. Bit 16
 * indicates the validity of the data in the buffer. Writing a 1 to bit 16
 * will clear the buffer.
 */
#घोषणा NIG_REG_P1_LLH_PTP_HOST_BUF_SEQID			 0x18774
/* [R 32] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * the host. This location वापसs the lower 32 bits of बारtamp value.
 */
#घोषणा NIG_REG_P1_LLH_PTP_HOST_BUF_TS_LSB			 0x1876c
/* [R 32] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * the host. This location वापसs the upper 32 bits of बारtamp value.
 */
#घोषणा NIG_REG_P1_LLH_PTP_HOST_BUF_TS_MSB			 0x18770
/* [RW 11] Mask रेजिस्टर क्रम the various parameters used in determining PTP
 * packet presence. Set each bit to 1 to mask out the particular parameter.
 * 0-IPv4 DA 0 of 224.0.1.129. 1-IPv4 DA 1 of 224.0.0.107. 2-IPv6 DA 0 of
 * 0xFF0*:0:0:0:0:0:0:181. 3-IPv6 DA 1 of 0xFF02:0:0:0:0:0:0:6B. 4-UDP
 * destination port 0 of 319. 5-UDP destination port 1 of 320. 6-MAC
 * Ethertype 0 of 0x88F7. 7-configurable MAC Ethertype 1. 8-MAC DA 0 of
 * 0x01-1B-19-00-00-00. 9-MAC DA 1 of 0x01-80-C2-00-00-0E. 10-configurable
 * MAC DA 2. The reset शेष is set to mask out all parameters.
 */
#घोषणा NIG_REG_P1_LLH_PTP_PARAM_MASK				 0x187c8
/* [RW 14] Mask regiser क्रम the rules used in detecting PTP packets. Set
 * each bit to 1 to mask out that particular rule. 0-अणुIPv4 DA 0; UDP DP 0पूर्ण .
 * 1-अणुIPv4 DA 0; UDP DP 1पूर्ण . 2-अणुIPv4 DA 1; UDP DP 0पूर्ण . 3-अणुIPv4 DA 1; UDP DP
 * 1पूर्ण . 4-अणुIPv6 DA 0; UDP DP 0पूर्ण . 5-अणुIPv6 DA 0; UDP DP 1पूर्ण . 6-अणुIPv6 DA 1;
 * UDP DP 0पूर्ण . 7-अणुIPv6 DA 1; UDP DP 1पूर्ण . 8-अणुMAC DA 0; Ethertype 0पूर्ण . 9-अणुMAC
 * DA 1; Ethertype 0पूर्ण . 10-अणुMAC DA 0; Ethertype 1पूर्ण . 11-अणुMAC DA 1; Ethertype
 * 1पूर्ण . 12-अणुMAC DA 2; Ethertype 0पूर्ण . 13-अणुMAC DA 2; Ethertype 1पूर्ण . The reset
 * शेष is to mask out all of the rules. Note that rules 0-3 are क्रम IPv4
 * packets only and require that the packet is IPv4 क्रम the rules to match.
 * Note that rules 4-7 are क्रम IPv6 packets only and require that the packet
 * is IPv6 क्रम the rules to match.
 */
#घोषणा NIG_REG_P1_LLH_PTP_RULE_MASK				 0x187cc
/* [RW 1] Set to 1 to enable PTP packets to be क्रमwarded to the host. */
#घोषणा NIG_REG_P1_LLH_PTP_TO_HOST				 0x187d4
/* [RW 32] Specअगरy the client number to be asचिन्हित to each priority of the
 * strict priority arbiter. This रेजिस्टर specअगरies bits 31:0 of the 36-bit
 * value. Priority 0 is the highest priority. Bits [3:0] are क्रम priority 0
 * client; bits [35-32] are क्रम priority 8 client. The clients are asचिन्हित
 * the following IDs: 0-management; 1-debug traffic from this port; 2-debug
 * traffic from other port; 3-COS0 traffic; 4-COS1 traffic; 5-COS2 traffic;
 * 6-COS3 traffic; 7-COS4 traffic; 8-COS5 traffic. The reset value[35:0] is
 * set to 0x345678021. This is a new रेजिस्टर (with 2_) added in E3 B0 to
 * accommodate the 9 input clients to ETS arbiter. */
#घोषणा NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_LSB			 0x18680
/* [RW 4] Specअगरy the client number to be asचिन्हित to each priority of the
 * strict priority arbiter. This रेजिस्टर specअगरies bits 35:32 of the 36-bit
 * value. Priority 0 is the highest priority. Bits [3:0] are क्रम priority 0
 * client; bits [35-32] are क्रम priority 8 client. The clients are asचिन्हित
 * the following IDs: 0-management; 1-debug traffic from this port; 2-debug
 * traffic from other port; 3-COS0 traffic; 4-COS1 traffic; 5-COS2 traffic;
 * 6-COS3 traffic; 7-COS4 traffic; 8-COS5 traffic. The reset value[35:0] is
 * set to 0x345678021. This is a new रेजिस्टर (with 2_) added in E3 B0 to
 * accommodate the 9 input clients to ETS arbiter. */
#घोषणा NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_MSB			 0x18684
/* [RW 1] MCP-to-host path enable. Set this bit to enable the routing of MCP
 * packets to BRB LB पूर्णांकerface to क्रमward the packet to the host. All
 * packets from MCP are क्रमwarded to the network when this bit is cleared -
 * regardless of the configured destination in tx_mng_destination रेजिस्टर.
 * When MCP-to-host paths क्रम both ports 0 and 1 are disabled - the arbiter
 * क्रम BRB LB पूर्णांकerface is bypassed and PBF LB traffic is always selected to
 * send to BRB LB.
 */
#घोषणा NIG_REG_P0_TX_MNG_HOST_ENABLE				 0x182f4
#घोषणा NIG_REG_P1_HWPFC_ENABLE					 0x181d0
#घोषणा NIG_REG_P1_MAC_IN_EN					 0x185c0
/* [RW 1] Output enable क्रम TX MAC पूर्णांकerface */
#घोषणा NIG_REG_P1_MAC_OUT_EN					 0x185c4
/* [RW 1] Output enable क्रम TX PAUSE संकेत to the MAC. */
#घोषणा NIG_REG_P1_MAC_PAUSE_OUT_EN				 0x185c8
/* [RW 32] Eight 4-bit configurations क्रम specअगरying which COS (0-15 क्रम
 * future expansion) each priorty is to be mapped to. Bits 3:0 specअगरy the
 * COS क्रम priority 0. Bits 31:28 specअगरy the COS क्रम priority 7. The 3-bit
 * priority field is extracted from the outer-most VLAN in receive packet.
 * Only COS 0 and COS 1 are supported in E2. */
#घोषणा NIG_REG_P1_PKT_PRIORITY_TO_COS				 0x181a8
/* [RW 6] Enable क्रम TimeSync feature. Bits [2:0] are क्रम RX side. Bits
 * [5:3] are क्रम TX side. Bit 0 enables TimeSync on RX side. Bit 1 enables
 * V1 frame क्रमmat in बारync event detection on RX side. Bit 2 enables V2
 * frame क्रमmat in बारync event detection on RX side. Bit 3 enables
 * TimeSync on TX side. Bit 4 enables V1 frame क्रमmat in बारync event
 * detection on TX side. Bit 5 enables V2 frame क्रमmat in बारync event
 * detection on TX side. Note that क्रम HW to detect PTP packet and extract
 * data from the packet, at least one of the version bits of that traffic
 * direction has to be enabled.
 */
#घोषणा NIG_REG_P1_PTP_EN					 0x187b0
/* [RW 16] Bit-map indicating which SAFC/PFC priorities to map to COS 0. A
 * priority is mapped to COS 0 when the corresponding mask bit is 1. More
 * than one bit may be set; allowing multiple priorities to be mapped to one
 * COS. */
#घोषणा NIG_REG_P1_RX_COS0_PRIORITY_MASK			 0x181ac
/* [RW 16] Bit-map indicating which SAFC/PFC priorities to map to COS 1. A
 * priority is mapped to COS 1 when the corresponding mask bit is 1. More
 * than one bit may be set; allowing multiple priorities to be mapped to one
 * COS. */
#घोषणा NIG_REG_P1_RX_COS1_PRIORITY_MASK			 0x181b0
/* [RW 16] Bit-map indicating which SAFC/PFC priorities to map to COS 2. A
 * priority is mapped to COS 2 when the corresponding mask bit is 1. More
 * than one bit may be set; allowing multiple priorities to be mapped to one
 * COS. */
#घोषणा NIG_REG_P1_RX_COS2_PRIORITY_MASK			 0x186f8
/* [R 1] RX FIFO क्रम receiving data from MAC is empty. */
#घोषणा NIG_REG_P1_RX_MACFIFO_EMPTY				 0x1858c
/* [R 1] TLLH FIFO is empty. */
#घोषणा NIG_REG_P1_TLLH_FIFO_EMPTY				 0x18338
/* [RW 19] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * TX side. Bits [15:0] reflect the sequence ID of the packet. Bit 16
 * indicates the validity of the data in the buffer. Bit 17 indicates that
 * the sequence ID is valid and it is रुकोing क्रम the TX बारtamp value.
 * Bit 18 indicates whether the बारtamp is from a SW request (value of 1)
 * or HW request (value of 0). Writing a 1 to bit 16 will clear the buffer.
 */
#घोषणा NIG_REG_P0_TLLH_PTP_BUF_SEQID				 0x187e0
/* [R 32] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * MCP. This location वापसs the lower 32 bits of बारtamp value.
 */
#घोषणा NIG_REG_P0_TLLH_PTP_BUF_TS_LSB				 0x187d8
/* [R 32] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * MCP. This location वापसs the upper 32 bits of बारtamp value.
 */
#घोषणा NIG_REG_P0_TLLH_PTP_BUF_TS_MSB				 0x187dc
/* [RW 11] Mask रेजिस्टर क्रम the various parameters used in determining PTP
 * packet presence. Set each bit to 1 to mask out the particular parameter.
 * 0-IPv4 DA 0 of 224.0.1.129. 1-IPv4 DA 1 of 224.0.0.107. 2-IPv6 DA 0 of
 * 0xFF0*:0:0:0:0:0:0:181. 3-IPv6 DA 1 of 0xFF02:0:0:0:0:0:0:6B. 4-UDP
 * destination port 0 of 319. 5-UDP destination port 1 of 320. 6-MAC
 * Ethertype 0 of 0x88F7. 7-configurable MAC Ethertype 1. 8-MAC DA 0 of
 * 0x01-1B-19-00-00-00. 9-MAC DA 1 of 0x01-80-C2-00-00-0E. 10-configurable
 * MAC DA 2. The reset शेष is set to mask out all parameters.
 */
#घोषणा NIG_REG_P0_TLLH_PTP_PARAM_MASK				 0x187f0
/* [RW 14] Mask regiser क्रम the rules used in detecting PTP packets. Set
 * each bit to 1 to mask out that particular rule. 0-अणुIPv4 DA 0; UDP DP 0पूर्ण .
 * 1-अणुIPv4 DA 0; UDP DP 1पूर्ण . 2-अणुIPv4 DA 1; UDP DP 0पूर्ण . 3-अणुIPv4 DA 1; UDP DP
 * 1पूर्ण . 4-अणुIPv6 DA 0; UDP DP 0पूर्ण . 5-अणुIPv6 DA 0; UDP DP 1पूर्ण . 6-अणुIPv6 DA 1;
 * UDP DP 0पूर्ण . 7-अणुIPv6 DA 1; UDP DP 1पूर्ण . 8-अणुMAC DA 0; Ethertype 0पूर्ण . 9-अणुMAC
 * DA 1; Ethertype 0पूर्ण . 10-अणुMAC DA 0; Ethertype 1पूर्ण . 11-अणुMAC DA 1; Ethertype
 * 1पूर्ण . 12-अणुMAC DA 2; Ethertype 0पूर्ण . 13-अणुMAC DA 2; Ethertype 1पूर्ण . The reset
 * शेष is to mask out all of the rules.
 */
#घोषणा NIG_REG_P0_TLLH_PTP_RULE_MASK				 0x187f4
/* [RW 19] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * TX side. Bits [15:0] reflect the sequence ID of the packet. Bit 16
 * indicates the validity of the data in the buffer. Bit 17 indicates that
 * the sequence ID is valid and it is रुकोing क्रम the TX बारtamp value.
 * Bit 18 indicates whether the बारtamp is from a SW request (value of 1)
 * or HW request (value of 0). Writing a 1 to bit 16 will clear the buffer.
 */
#घोषणा NIG_REG_P1_TLLH_PTP_BUF_SEQID				 0x187ec
/* [R 32] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * MCP. This location वापसs the lower 32 bits of बारtamp value.
 */
#घोषणा NIG_REG_P1_TLLH_PTP_BUF_TS_LSB				 0x187e4
/* [R 32] Packet TimeSync inक्रमmation that is buffered in 1-deep FIFOs क्रम
 * MCP. This location वापसs the upper 32 bits of बारtamp value.
 */
#घोषणा NIG_REG_P1_TLLH_PTP_BUF_TS_MSB				 0x187e8
/* [RW 11] Mask रेजिस्टर क्रम the various parameters used in determining PTP
 * packet presence. Set each bit to 1 to mask out the particular parameter.
 * 0-IPv4 DA 0 of 224.0.1.129. 1-IPv4 DA 1 of 224.0.0.107. 2-IPv6 DA 0 of
 * 0xFF0*:0:0:0:0:0:0:181. 3-IPv6 DA 1 of 0xFF02:0:0:0:0:0:0:6B. 4-UDP
 * destination port 0 of 319. 5-UDP destination port 1 of 320. 6-MAC
 * Ethertype 0 of 0x88F7. 7-configurable MAC Ethertype 1. 8-MAC DA 0 of
 * 0x01-1B-19-00-00-00. 9-MAC DA 1 of 0x01-80-C2-00-00-0E. 10-configurable
 * MAC DA 2. The reset शेष is set to mask out all parameters.
 */
#घोषणा NIG_REG_P1_TLLH_PTP_PARAM_MASK				 0x187f8
/* [RW 14] Mask regiser क्रम the rules used in detecting PTP packets. Set
 * each bit to 1 to mask out that particular rule. 0-अणुIPv4 DA 0; UDP DP 0पूर्ण .
 * 1-अणुIPv4 DA 0; UDP DP 1पूर्ण . 2-अणुIPv4 DA 1; UDP DP 0पूर्ण . 3-अणुIPv4 DA 1; UDP DP
 * 1पूर्ण . 4-अणुIPv6 DA 0; UDP DP 0पूर्ण . 5-अणुIPv6 DA 0; UDP DP 1पूर्ण . 6-अणुIPv6 DA 1;
 * UDP DP 0पूर्ण . 7-अणुIPv6 DA 1; UDP DP 1पूर्ण . 8-अणुMAC DA 0; Ethertype 0पूर्ण . 9-अणुMAC
 * DA 1; Ethertype 0पूर्ण . 10-अणुMAC DA 0; Ethertype 1पूर्ण . 11-अणुMAC DA 1; Ethertype
 * 1पूर्ण . 12-अणुMAC DA 2; Ethertype 0पूर्ण . 13-अणुMAC DA 2; Ethertype 1पूर्ण . The reset
 * शेष is to mask out all of the rules.
 */
#घोषणा NIG_REG_P1_TLLH_PTP_RULE_MASK				 0x187fc
/* [RW 32] Specअगरy which of the credit रेजिस्टरs the client is to be mapped
 * to. This रेजिस्टर specअगरies bits 31:0 of the 36-bit value. Bits[3:0] are
 * क्रम client 0; bits [35:32] are क्रम client 8. For clients that are not
 * subject to WFQ credit blocking - their specअगरications here are not used.
 * This is a new रेजिस्टर (with 2_) added in E3 B0 to accommodate the 9
 * input clients to ETS arbiter. The reset शेष is set क्रम management and
 * debug to use credit रेजिस्टरs 6, 7, and 8, respectively, and COSes 0-5 to
 * use credit रेजिस्टरs 0-5 respectively (0x543210876). Note that credit
 * रेजिस्टरs can not be shared between clients. Note also that there are
 * only COS0-2 in port 1- there is a total of 6 clients in port 1. Only
 * credit रेजिस्टरs 0-5 are valid. This रेजिस्टर should be configured
 * appropriately beक्रमe enabling WFQ. */
#घोषणा NIG_REG_P1_TX_ARB_CLIENT_CREDIT_MAP2_LSB		 0x186e8
/* [RW 4] Specअगरy which of the credit रेजिस्टरs the client is to be mapped
 * to. This रेजिस्टर specअगरies bits 35:32 of the 36-bit value. Bits[3:0] are
 * क्रम client 0; bits [35:32] are क्रम client 8. For clients that are not
 * subject to WFQ credit blocking - their specअगरications here are not used.
 * This is a new रेजिस्टर (with 2_) added in E3 B0 to accommodate the 9
 * input clients to ETS arbiter. The reset शेष is set क्रम management and
 * debug to use credit रेजिस्टरs 6, 7, and 8, respectively, and COSes 0-5 to
 * use credit रेजिस्टरs 0-5 respectively (0x543210876). Note that credit
 * रेजिस्टरs can not be shared between clients. Note also that there are
 * only COS0-2 in port 1- there is a total of 6 clients in port 1. Only
 * credit रेजिस्टरs 0-5 are valid. This रेजिस्टर should be configured
 * appropriately beक्रमe enabling WFQ. */
#घोषणा NIG_REG_P1_TX_ARB_CLIENT_CREDIT_MAP2_MSB		 0x186ec
/* [RW 9] Specअगरy whether the client competes directly in the strict
 * priority arbiter. The bits are mapped according to client ID (client IDs
 * are defined in tx_arb_priority_client2): 0-management; 1-debug traffic
 * from this port; 2-debug traffic from other port; 3-COS0 traffic; 4-COS1
 * traffic; 5-COS2 traffic; 6-COS3 traffic; 7-COS4 traffic; 8-COS5 traffic.
 * Default value is set to enable strict priorities क्रम all clients. */
#घोषणा NIG_REG_P1_TX_ARB_CLIENT_IS_STRICT			 0x18234
/* [RW 9] Specअगरy whether the client is subject to WFQ credit blocking. The
 * bits are mapped according to client ID (client IDs are defined in
 * tx_arb_priority_client2): 0-management; 1-debug traffic from this port;
 * 2-debug traffic from other port; 3-COS0 traffic; 4-COS1 traffic; 5-COS2
 * traffic; 6-COS3 traffic; 7-COS4 traffic; 8-COS5 traffic. Default value is
 * 0 क्रम not using WFQ credit blocking. */
#घोषणा NIG_REG_P1_TX_ARB_CLIENT_IS_SUBJECT2WFQ			 0x18238
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_0			 0x18258
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_1			 0x1825c
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_2			 0x18260
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_3			 0x18264
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_4			 0x18268
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_5			 0x186f4
/* [RW 32] Specअगरy the weight (in bytes) to be added to credit रेजिस्टर 0
 * when it is समय to increment. */
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_0			 0x18244
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_1			 0x18248
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_2			 0x1824c
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_3			 0x18250
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_4			 0x18254
#घोषणा NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_5			 0x186f0
/* [RW 12] Specअगरy the number of strict priority arbitration slots between
   two round-robin arbitration slots to aव्योम starvation. A value of 0 means
   no strict priority cycles - the strict priority with anti-starvation
   arbiter becomes a round-robin arbiter. */
#घोषणा NIG_REG_P1_TX_ARB_NUM_STRICT_ARB_SLOTS			 0x18240
/* [RW 32] Specअगरy the client number to be asचिन्हित to each priority of the
   strict priority arbiter. This रेजिस्टर specअगरies bits 31:0 of the 36-bit
   value. Priority 0 is the highest priority. Bits [3:0] are क्रम priority 0
   client; bits [35-32] are क्रम priority 8 client. The clients are asचिन्हित
   the following IDs: 0-management; 1-debug traffic from this port; 2-debug
   traffic from other port; 3-COS0 traffic; 4-COS1 traffic; 5-COS2 traffic;
   6-COS3 traffic; 7-COS4 traffic; 8-COS5 traffic. The reset value[35:0] is
   set to 0x345678021. This is a new रेजिस्टर (with 2_) added in E3 B0 to
   accommodate the 9 input clients to ETS arbiter. Note that this रेजिस्टर
   is the same as the one क्रम port 0, except that port 1 only has COS 0-2
   traffic. There is no traffic क्रम COS 3-5 of port 1. */
#घोषणा NIG_REG_P1_TX_ARB_PRIORITY_CLIENT2_LSB			 0x186e0
/* [RW 4] Specअगरy the client number to be asचिन्हित to each priority of the
   strict priority arbiter. This रेजिस्टर specअगरies bits 35:32 of the 36-bit
   value. Priority 0 is the highest priority. Bits [3:0] are क्रम priority 0
   client; bits [35-32] are क्रम priority 8 client. The clients are asचिन्हित
   the following IDs: 0-management; 1-debug traffic from this port; 2-debug
   traffic from other port; 3-COS0 traffic; 4-COS1 traffic; 5-COS2 traffic;
   6-COS3 traffic; 7-COS4 traffic; 8-COS5 traffic. The reset value[35:0] is
   set to 0x345678021. This is a new रेजिस्टर (with 2_) added in E3 B0 to
   accommodate the 9 input clients to ETS arbiter. Note that this रेजिस्टर
   is the same as the one क्रम port 0, except that port 1 only has COS 0-2
   traffic. There is no traffic क्रम COS 3-5 of port 1. */
#घोषणा NIG_REG_P1_TX_ARB_PRIORITY_CLIENT2_MSB			 0x186e4
/* [R 1] TX FIFO क्रम transmitting data to MAC is empty. */
#घोषणा NIG_REG_P1_TX_MACFIFO_EMPTY				 0x18594
/* [RW 1] MCP-to-host path enable. Set this bit to enable the routing of MCP
 * packets to BRB LB पूर्णांकerface to क्रमward the packet to the host. All
 * packets from MCP are क्रमwarded to the network when this bit is cleared -
 * regardless of the configured destination in tx_mng_destination रेजिस्टर.
 */
#घोषणा NIG_REG_P1_TX_MNG_HOST_ENABLE				 0x182f8
/* [R 1] FIFO empty status of the MCP TX FIFO used क्रम storing MCP packets
   क्रमwarded to the host. */
#घोषणा NIG_REG_P1_TX_MNG_HOST_FIFO_EMPTY			 0x182b8
/* [RW 32] Specअगरy the upper bound that credit रेजिस्टर 0 is allowed to
 * reach. */
/* [RW 1] Pause enable क्रम port0. This रेजिस्टर may get 1 only when
   ~safc_enable.safc_enable = 0 and ppp_enable.ppp_enable =0 क्रम the same
   port */
#घोषणा NIG_REG_PAUSE_ENABLE_0					 0x160c0
#घोषणा NIG_REG_PAUSE_ENABLE_1					 0x160c4
/* [RW 1] Input enable क्रम RX PBF LP IF */
#घोषणा NIG_REG_PBF_LB_IN_EN					 0x100b4
/* [RW 1] Value of this रेजिस्टर will be transmitted to port swap when
   ~nig_रेजिस्टरs_strap_override.strap_override =1 */
#घोषणा NIG_REG_PORT_SWAP					 0x10394
/* [RW 1] PPP enable क्रम port0. This रेजिस्टर may get 1 only when
 * ~safc_enable.safc_enable = 0 and छोड़ो_enable.छोड़ो_enable =0 क्रम the
 * same port */
#घोषणा NIG_REG_PPP_ENABLE_0					 0x160b0
#घोषणा NIG_REG_PPP_ENABLE_1					 0x160b4
/* [RW 1] output enable क्रम RX parser descriptor IF */
#घोषणा NIG_REG_PRS_EOP_OUT_EN					 0x10104
/* [RW 1] Input enable क्रम RX parser request IF */
#घोषणा NIG_REG_PRS_REQ_IN_EN					 0x100b8
/* [RW 5] control to serdes - CL45 DEVAD */
#घोषणा NIG_REG_SERDES0_CTRL_MD_DEVAD				 0x10370
/* [RW 1] control to serdes; 0 - clause 45; 1 - clause 22 */
#घोषणा NIG_REG_SERDES0_CTRL_MD_ST				 0x1036c
/* [RW 5] control to serdes - CL22 PHY_ADD and CL45 PRTAD */
#घोषणा NIG_REG_SERDES0_CTRL_PHY_ADDR				 0x10374
/* [R 1] status from serdes0 that inमाला_दो to पूर्णांकerrupt logic of link status */
#घोषणा NIG_REG_SERDES0_STATUS_LINK_STATUS			 0x10578
/* [R 32] Rx statistics : In user packets discarded due to BRB backpressure
   क्रम port0 */
#घोषणा NIG_REG_STAT0_BRB_DISCARD				 0x105f0
/* [R 32] Rx statistics : In user packets truncated due to BRB backpressure
   क्रम port0 */
#घोषणा NIG_REG_STAT0_BRB_TRUNCATE				 0x105f8
/* [WB_R 36] Tx statistics : Number of packets from emac0 or bmac0 that
   between 1024 and 1522 bytes क्रम port0 */
#घोषणा NIG_REG_STAT0_EGRESS_MAC_PKT0				 0x10750
/* [WB_R 36] Tx statistics : Number of packets from emac0 or bmac0 that
   between 1523 bytes and above क्रम port0 */
#घोषणा NIG_REG_STAT0_EGRESS_MAC_PKT1				 0x10760
/* [R 32] Rx statistics : In user packets discarded due to BRB backpressure
   क्रम port1 */
#घोषणा NIG_REG_STAT1_BRB_DISCARD				 0x10628
/* [WB_R 36] Tx statistics : Number of packets from emac1 or bmac1 that
   between 1024 and 1522 bytes क्रम port1 */
#घोषणा NIG_REG_STAT1_EGRESS_MAC_PKT0				 0x107a0
/* [WB_R 36] Tx statistics : Number of packets from emac1 or bmac1 that
   between 1523 bytes and above क्रम port1 */
#घोषणा NIG_REG_STAT1_EGRESS_MAC_PKT1				 0x107b0
/* [WB_R 64] Rx statistics : User octets received क्रम LP */
#घोषणा NIG_REG_STAT2_BRB_OCTET 				 0x107e0
#घोषणा NIG_REG_STATUS_INTERRUPT_PORT0				 0x10328
#घोषणा NIG_REG_STATUS_INTERRUPT_PORT1				 0x1032c
/* [RW 1] port swap mux selection. If this रेजिस्टर equal to 0 then port
   swap is equal to SPIO pin that inमाला_दो from अगरmux_serdes_swap. If 1 then
   ort swap is equal to ~nig_रेजिस्टरs_port_swap.port_swap */
#घोषणा NIG_REG_STRAP_OVERRIDE					 0x10398
/* [WB 64] Addresses क्रम TimeSync related रेजिस्टरs in the बारync
 * generator sub-module.
 */
#घोषणा NIG_REG_TIMESYNC_GEN_REG				 0x18800
/* [RW 1] output enable क्रम RX_XCM0 IF */
#घोषणा NIG_REG_XCM0_OUT_EN					 0x100f0
/* [RW 1] output enable क्रम RX_XCM1 IF */
#घोषणा NIG_REG_XCM1_OUT_EN					 0x100f4
/* [RW 1] control to xgxs - remote PHY in-band MDIO */
#घोषणा NIG_REG_XGXS0_CTRL_EXTREMOTEMDIOST			 0x10348
/* [RW 5] control to xgxs - CL45 DEVAD */
#घोषणा NIG_REG_XGXS0_CTRL_MD_DEVAD				 0x1033c
/* [RW 1] control to xgxs; 0 - clause 45; 1 - clause 22 */
#घोषणा NIG_REG_XGXS0_CTRL_MD_ST				 0x10338
/* [RW 5] control to xgxs - CL22 PHY_ADD and CL45 PRTAD */
#घोषणा NIG_REG_XGXS0_CTRL_PHY_ADDR				 0x10340
/* [R 1] status from xgxs0 that inमाला_दो to पूर्णांकerrupt logic of link10g. */
#घोषणा NIG_REG_XGXS0_STATUS_LINK10G				 0x10680
/* [R 4] status from xgxs0 that inमाला_दो to पूर्णांकerrupt logic of link status */
#घोषणा NIG_REG_XGXS0_STATUS_LINK_STATUS			 0x10684
/* [RW 2] selection क्रम XGXS lane of port 0 in NIG_MUX block */
#घोषणा NIG_REG_XGXS_LANE_SEL_P0				 0x102e8
/* [RW 1] selection क्रम port0 क्रम NIG_MUX block : 0 = SerDes; 1 = XGXS */
#घोषणा NIG_REG_XGXS_SERDES0_MODE_SEL				 0x102e0
#घोषणा NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_EMAC0_MISC_MI_INT  (0x1<<0)
#घोषणा NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_SERDES0_LINK_STATUS (0x1<<9)
#घोषणा NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_XGXS0_LINK10G	 (0x1<<15)
#घोषणा NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_XGXS0_LINK_STATUS  (0xf<<18)
#घोषणा NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_XGXS0_LINK_STATUS_SIZE 18
/* [RW 31] The upper bound of the weight of COS0 in the ETS command arbiter. */
#घोषणा PBF_REG_COS0_UPPER_BOUND				 0x15c05c
/* [RW 31] The upper bound of the weight of COS0 in the ETS command arbiter
 * of port 0. */
#घोषणा PBF_REG_COS0_UPPER_BOUND_P0				 0x15c2cc
/* [RW 31] The upper bound of the weight of COS0 in the ETS command arbiter
 * of port 1. */
#घोषणा PBF_REG_COS0_UPPER_BOUND_P1				 0x15c2e4
/* [RW 31] The weight of COS0 in the ETS command arbiter. */
#घोषणा PBF_REG_COS0_WEIGHT					 0x15c054
/* [RW 31] The weight of COS0 in port 0 ETS command arbiter. */
#घोषणा PBF_REG_COS0_WEIGHT_P0					 0x15c2a8
/* [RW 31] The weight of COS0 in port 1 ETS command arbiter. */
#घोषणा PBF_REG_COS0_WEIGHT_P1					 0x15c2c0
/* [RW 31] The upper bound of the weight of COS1 in the ETS command arbiter. */
#घोषणा PBF_REG_COS1_UPPER_BOUND				 0x15c060
/* [RW 31] The weight of COS1 in the ETS command arbiter. */
#घोषणा PBF_REG_COS1_WEIGHT					 0x15c058
/* [RW 31] The weight of COS1 in port 0 ETS command arbiter. */
#घोषणा PBF_REG_COS1_WEIGHT_P0					 0x15c2ac
/* [RW 31] The weight of COS1 in port 1 ETS command arbiter. */
#घोषणा PBF_REG_COS1_WEIGHT_P1					 0x15c2c4
/* [RW 31] The weight of COS2 in port 0 ETS command arbiter. */
#घोषणा PBF_REG_COS2_WEIGHT_P0					 0x15c2b0
/* [RW 31] The weight of COS2 in port 1 ETS command arbiter. */
#घोषणा PBF_REG_COS2_WEIGHT_P1					 0x15c2c8
/* [RW 31] The weight of COS3 in port 0 ETS command arbiter. */
#घोषणा PBF_REG_COS3_WEIGHT_P0					 0x15c2b4
/* [RW 31] The weight of COS4 in port 0 ETS command arbiter. */
#घोषणा PBF_REG_COS4_WEIGHT_P0					 0x15c2b8
/* [RW 31] The weight of COS5 in port 0 ETS command arbiter. */
#घोषणा PBF_REG_COS5_WEIGHT_P0					 0x15c2bc
/* [R 11] Current credit क्रम the LB queue in the tx port buffers in 16 byte
 * lines. */
#घोषणा PBF_REG_CREDIT_LB_Q					 0x140338
/* [R 11] Current credit क्रम queue 0 in the tx port buffers in 16 byte
 * lines. */
#घोषणा PBF_REG_CREDIT_Q0					 0x14033c
/* [R 11] Current credit क्रम queue 1 in the tx port buffers in 16 byte
 * lines. */
#घोषणा PBF_REG_CREDIT_Q1					 0x140340
/* [RW 1] Disable processing further tasks from port 0 (after ending the
   current task in process). */
#घोषणा PBF_REG_DISABLE_NEW_TASK_PROC_P0			 0x14005c
/* [RW 1] Disable processing further tasks from port 1 (after ending the
   current task in process). */
#घोषणा PBF_REG_DISABLE_NEW_TASK_PROC_P1			 0x140060
/* [RW 1] Disable processing further tasks from port 4 (after ending the
   current task in process). */
#घोषणा PBF_REG_DISABLE_NEW_TASK_PROC_P4			 0x14006c
#घोषणा PBF_REG_DISABLE_PF					 0x1402e8
#घोषणा PBF_REG_DISABLE_VF					 0x1402ec
/* [RW 18] For port 0: For each client that is subject to WFQ (the
 * corresponding bit is 1); indicates to which of the credit रेजिस्टरs this
 * client is mapped. For clients which are not credit blocked; their mapping
 * is करोnt care. */
#घोषणा PBF_REG_ETS_ARB_CLIENT_CREDIT_MAP_P0			 0x15c288
/* [RW 9] For port 1: For each client that is subject to WFQ (the
 * corresponding bit is 1); indicates to which of the credit रेजिस्टरs this
 * client is mapped. For clients which are not credit blocked; their mapping
 * is करोnt care. */
#घोषणा PBF_REG_ETS_ARB_CLIENT_CREDIT_MAP_P1			 0x15c28c
/* [RW 6] For port 0: Bit per client to indicate अगर the client competes in
 * the strict priority arbiter directly (corresponding bit = 1); or first
 * goes to the RR arbiter (corresponding bit = 0); and then competes in the
 * lowest priority in the strict-priority arbiter. */
#घोषणा PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P0			 0x15c278
/* [RW 3] For port 1: Bit per client to indicate अगर the client competes in
 * the strict priority arbiter directly (corresponding bit = 1); or first
 * goes to the RR arbiter (corresponding bit = 0); and then competes in the
 * lowest priority in the strict-priority arbiter. */
#घोषणा PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P1			 0x15c27c
/* [RW 6] For port 0: Bit per client to indicate अगर the client is subject to
 * WFQ credit blocking (corresponding bit = 1). */
#घोषणा PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P0		 0x15c280
/* [RW 3] For port 0: Bit per client to indicate अगर the client is subject to
 * WFQ credit blocking (corresponding bit = 1). */
#घोषणा PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P1		 0x15c284
/* [RW 16] For port 0: The number of strict priority arbitration slots
 * between 2 RR arbitration slots. A value of 0 means no strict priority
 * cycles; i.e. the strict-priority w/ anti-starvation arbiter is a RR
 * arbiter. */
#घोषणा PBF_REG_ETS_ARB_NUM_STRICT_ARB_SLOTS_P0			 0x15c2a0
/* [RW 16] For port 1: The number of strict priority arbitration slots
 * between 2 RR arbitration slots. A value of 0 means no strict priority
 * cycles; i.e. the strict-priority w/ anti-starvation arbiter is a RR
 * arbiter. */
#घोषणा PBF_REG_ETS_ARB_NUM_STRICT_ARB_SLOTS_P1			 0x15c2a4
/* [RW 18] For port 0: Indicates which client is connected to each priority
 * in the strict-priority arbiter. Priority 0 is the highest priority, and
 * priority 5 is the lowest; to which the RR output is connected to (this is
 * not configurable). */
#घोषणा PBF_REG_ETS_ARB_PRIORITY_CLIENT_P0			 0x15c270
/* [RW 9] For port 1: Indicates which client is connected to each priority
 * in the strict-priority arbiter. Priority 0 is the highest priority, and
 * priority 5 is the lowest; to which the RR output is connected to (this is
 * not configurable). */
#घोषणा PBF_REG_ETS_ARB_PRIORITY_CLIENT_P1			 0x15c274
/* [RW 1] Indicates that ETS is perक्रमmed between the COSes in the command
 * arbiter. If reset strict priority w/ anti-starvation will be perक्रमmed
 * w/o WFQ. */
#घोषणा PBF_REG_ETS_ENABLED					 0x15c050
/* [RW 6] Bit-map indicating which L2 hdrs may appear after the basic
 * Ethernet header. */
#घोषणा PBF_REG_HDRS_AFTER_BASIC				 0x15c0a8
/* [RW 6] Bit-map indicating which L2 hdrs may appear after L2 tag 0 */
#घोषणा PBF_REG_HDRS_AFTER_TAG_0				 0x15c0b8
/* [R 1] Removed क्रम E3 B0 - Indicates which COS is conncted to the highest
 * priority in the command arbiter. */
#घोषणा PBF_REG_HIGH_PRIORITY_COS_NUM				 0x15c04c
#घोषणा PBF_REG_IF_ENABLE_REG					 0x140044
/* [RW 1] Init bit. When set the initial credits are copied to the credit
   रेजिस्टरs (except the port credits). Should be set and then reset after
   the configuration of the block has ended. */
#घोषणा PBF_REG_INIT						 0x140000
/* [RW 11] Initial credit क्रम the LB queue in the tx port buffers in 16 byte
 * lines. */
#घोषणा PBF_REG_INIT_CRD_LB_Q					 0x15c248
/* [RW 11] Initial credit क्रम queue 0 in the tx port buffers in 16 byte
 * lines. */
#घोषणा PBF_REG_INIT_CRD_Q0					 0x15c230
/* [RW 11] Initial credit क्रम queue 1 in the tx port buffers in 16 byte
 * lines. */
#घोषणा PBF_REG_INIT_CRD_Q1					 0x15c234
/* [RW 1] Init bit क्रम port 0. When set the initial credit of port 0 is
   copied to the credit रेजिस्टर. Should be set and then reset after the
   configuration of the port has ended. */
#घोषणा PBF_REG_INIT_P0 					 0x140004
/* [RW 1] Init bit क्रम port 1. When set the initial credit of port 1 is
   copied to the credit रेजिस्टर. Should be set and then reset after the
   configuration of the port has ended. */
#घोषणा PBF_REG_INIT_P1 					 0x140008
/* [RW 1] Init bit क्रम port 4. When set the initial credit of port 4 is
   copied to the credit रेजिस्टर. Should be set and then reset after the
   configuration of the port has ended. */
#घोषणा PBF_REG_INIT_P4 					 0x14000c
/* [R 32] Cyclic counter क्रम the amount credits in 16 bytes lines added क्रम
 * the LB queue. Reset upon init. */
#घोषणा PBF_REG_INTERNAL_CRD_FREED_CNT_LB_Q			 0x140354
/* [R 32] Cyclic counter क्रम the amount credits in 16 bytes lines added क्रम
 * queue 0. Reset upon init. */
#घोषणा PBF_REG_INTERNAL_CRD_FREED_CNT_Q0			 0x140358
/* [R 32] Cyclic counter क्रम the amount credits in 16 bytes lines added क्रम
 * queue 1. Reset upon init. */
#घोषणा PBF_REG_INTERNAL_CRD_FREED_CNT_Q1			 0x14035c
/* [RW 1] Enable क्रम mac पूर्णांकerface 0. */
#घोषणा PBF_REG_MAC_IF0_ENABLE					 0x140030
/* [RW 1] Enable क्रम mac पूर्णांकerface 1. */
#घोषणा PBF_REG_MAC_IF1_ENABLE					 0x140034
/* [RW 1] Enable क्रम the loopback पूर्णांकerface. */
#घोषणा PBF_REG_MAC_LB_ENABLE					 0x140040
/* [RW 6] Bit-map indicating which headers must appear in the packet */
#घोषणा PBF_REG_MUST_HAVE_HDRS					 0x15c0c4
/* [RW 16] The number of strict priority arbitration slots between 2 RR
 * arbitration slots. A value of 0 means no strict priority cycles; i.e. the
 * strict-priority w/ anti-starvation arbiter is a RR arbiter. */
#घोषणा PBF_REG_NUM_STRICT_ARB_SLOTS				 0x15c064
/* [RW 10] Port 0 threshold used by arbiter in 16 byte lines used when छोड़ो
   not suppoterd. */
#घोषणा PBF_REG_P0_ARB_THRSH					 0x1400e4
/* [R 11] Current credit क्रम port 0 in the tx port buffers in 16 byte lines. */
#घोषणा PBF_REG_P0_CREDIT					 0x140200
/* [RW 11] Initial credit क्रम port 0 in the tx port buffers in 16 byte
   lines. */
#घोषणा PBF_REG_P0_INIT_CRD					 0x1400d0
/* [R 32] Cyclic counter क्रम the amount credits in 16 bytes lines added क्रम
 * port 0. Reset upon init. */
#घोषणा PBF_REG_P0_INTERNAL_CRD_FREED_CNT			 0x140308
/* [R 1] Removed क्रम E3 B0 - Indication that छोड़ो is enabled क्रम port 0. */
#घोषणा PBF_REG_P0_PAUSE_ENABLE					 0x140014
/* [R 8] Removed क्रम E3 B0 - Number of tasks in port 0 task queue. */
#घोषणा PBF_REG_P0_TASK_CNT					 0x140204
/* [R 32] Removed क्रम E3 B0 - Cyclic counter क्रम number of 8 byte lines
 * मुक्तd from the task queue of port 0. Reset upon init. */
#घोषणा PBF_REG_P0_TQ_LINES_FREED_CNT				 0x1402f0
/* [R 12] Number of 8 bytes lines occupied in the task queue of port 0. */
#घोषणा PBF_REG_P0_TQ_OCCUPANCY					 0x1402fc
/* [R 11] Removed क्रम E3 B0 - Current credit क्रम port 1 in the tx port
 * buffers in 16 byte lines. */
#घोषणा PBF_REG_P1_CREDIT					 0x140208
/* [R 11] Removed क्रम E3 B0 - Initial credit क्रम port 0 in the tx port
 * buffers in 16 byte lines. */
#घोषणा PBF_REG_P1_INIT_CRD					 0x1400d4
/* [R 32] Cyclic counter क्रम the amount credits in 16 bytes lines added क्रम
 * port 1. Reset upon init. */
#घोषणा PBF_REG_P1_INTERNAL_CRD_FREED_CNT			 0x14030c
/* [R 8] Removed क्रम E3 B0 - Number of tasks in port 1 task queue. */
#घोषणा PBF_REG_P1_TASK_CNT					 0x14020c
/* [R 32] Removed क्रम E3 B0 - Cyclic counter क्रम number of 8 byte lines
 * मुक्तd from the task queue of port 1. Reset upon init. */
#घोषणा PBF_REG_P1_TQ_LINES_FREED_CNT				 0x1402f4
/* [R 12] Number of 8 bytes lines occupied in the task queue of port 1. */
#घोषणा PBF_REG_P1_TQ_OCCUPANCY					 0x140300
/* [R 11] Current credit क्रम port 4 in the tx port buffers in 16 byte lines. */
#घोषणा PBF_REG_P4_CREDIT					 0x140210
/* [RW 11] Initial credit क्रम port 4 in the tx port buffers in 16 byte
   lines. */
#घोषणा PBF_REG_P4_INIT_CRD					 0x1400e0
/* [R 32] Cyclic counter क्रम the amount credits in 16 bytes lines added क्रम
 * port 4. Reset upon init. */
#घोषणा PBF_REG_P4_INTERNAL_CRD_FREED_CNT			 0x140310
/* [R 8] Removed क्रम E3 B0 - Number of tasks in port 4 task queue. */
#घोषणा PBF_REG_P4_TASK_CNT					 0x140214
/* [R 32] Removed क्रम E3 B0 - Cyclic counter क्रम number of 8 byte lines
 * मुक्तd from the task queue of port 4. Reset upon init. */
#घोषणा PBF_REG_P4_TQ_LINES_FREED_CNT				 0x1402f8
/* [R 12] Number of 8 bytes lines occupied in the task queue of port 4. */
#घोषणा PBF_REG_P4_TQ_OCCUPANCY					 0x140304
/* [RW 5] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PBF_REG_PBF_INT_MASK					 0x1401d4
/* [R 5] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा PBF_REG_PBF_INT_STS					 0x1401c8
/* [RW 20] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PBF_REG_PBF_PRTY_MASK					 0x1401e4
/* [R 28] Parity रेजिस्टर #0 पढ़ो */
#घोषणा PBF_REG_PBF_PRTY_STS					 0x1401d8
/* [RC 20] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा PBF_REG_PBF_PRTY_STS_CLR				 0x1401dc
/* [RW 16] The Ethernet type value क्रम L2 tag 0 */
#घोषणा PBF_REG_TAG_ETHERTYPE_0					 0x15c090
/* [RW 4] The length of the info field क्रम L2 tag 0. The length is between
 * 2B and 14B; in 2B granularity */
#घोषणा PBF_REG_TAG_LEN_0					 0x15c09c
/* [R 32] Cyclic counter क्रम number of 8 byte lines मुक्तd from the LB task
 * queue. Reset upon init. */
#घोषणा PBF_REG_TQ_LINES_FREED_CNT_LB_Q				 0x14038c
/* [R 32] Cyclic counter क्रम number of 8 byte lines मुक्तd from the task
 * queue 0. Reset upon init. */
#घोषणा PBF_REG_TQ_LINES_FREED_CNT_Q0				 0x140390
/* [R 32] Cyclic counter क्रम number of 8 byte lines मुक्तd from task queue 1.
 * Reset upon init. */
#घोषणा PBF_REG_TQ_LINES_FREED_CNT_Q1				 0x140394
/* [R 13] Number of 8 bytes lines occupied in the task queue of the LB
 * queue. */
#घोषणा PBF_REG_TQ_OCCUPANCY_LB_Q				 0x1403a8
/* [R 13] Number of 8 bytes lines occupied in the task queue of queue 0. */
#घोषणा PBF_REG_TQ_OCCUPANCY_Q0					 0x1403ac
/* [R 13] Number of 8 bytes lines occupied in the task queue of queue 1. */
#घोषणा PBF_REG_TQ_OCCUPANCY_Q1					 0x1403b0
/* [RW 16] One of 8 values that should be compared to type in Ethernet
 * parsing. If there is a match; the field after Ethernet is the first VLAN.
 * Reset value is 0x8100 which is the standard VLAN type. Note that when
 * checking second VLAN; type is compared only to 0x8100.
 */
#घोषणा PBF_REG_VLAN_TYPE_0					 0x15c06c
/* [RW 2] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PB_REG_PB_INT_MASK					 0x28
/* [R 2] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा PB_REG_PB_INT_STS					 0x1c
/* [RW 4] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PB_REG_PB_PRTY_MASK					 0x38
/* [R 4] Parity रेजिस्टर #0 पढ़ो */
#घोषणा PB_REG_PB_PRTY_STS					 0x2c
/* [RC 4] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा PB_REG_PB_PRTY_STS_CLR					 0x30
#घोषणा PGLUE_B_PGLUE_B_INT_STS_REG_ADDRESS_ERROR		 (0x1<<0)
#घोषणा PGLUE_B_PGLUE_B_INT_STS_REG_CSSNOOP_FIFO_OVERFLOW	 (0x1<<8)
#घोषणा PGLUE_B_PGLUE_B_INT_STS_REG_INCORRECT_RCV_BEHAVIOR	 (0x1<<1)
#घोषणा PGLUE_B_PGLUE_B_INT_STS_REG_TCPL_ERROR_ATTN		 (0x1<<6)
#घोषणा PGLUE_B_PGLUE_B_INT_STS_REG_TCPL_IN_TWO_RCBS_ATTN	 (0x1<<7)
#घोषणा PGLUE_B_PGLUE_B_INT_STS_REG_VF_GRC_SPACE_VIOLATION_ATTN  (0x1<<4)
#घोषणा PGLUE_B_PGLUE_B_INT_STS_REG_VF_LENGTH_VIOLATION_ATTN	 (0x1<<3)
#घोषणा PGLUE_B_PGLUE_B_INT_STS_REG_VF_MSIX_BAR_VIOLATION_ATTN	 (0x1<<5)
#घोषणा PGLUE_B_PGLUE_B_INT_STS_REG_WAS_ERROR_ATTN		 (0x1<<2)
/* [R 8] Config space A attention dirty bits. Each bit indicates that the
 * corresponding PF generates config space A attention. Set by PXP. Reset by
 * MCP writing 1 to icfg_space_a_request_clr. Note: रेजिस्टर contains bits
 * from both paths. */
#घोषणा PGLUE_B_REG_CFG_SPACE_A_REQUEST			 0x9010
/* [R 8] Config space B attention dirty bits. Each bit indicates that the
 * corresponding PF generates config space B attention. Set by PXP. Reset by
 * MCP writing 1 to icfg_space_b_request_clr. Note: रेजिस्टर contains bits
 * from both paths. */
#घोषणा PGLUE_B_REG_CFG_SPACE_B_REQUEST			 0x9014
/* [RW 1] Type A PF enable inbound पूर्णांकerrupt table क्रम CSDM. 0 - disable; 1
 * - enable. */
#घोषणा PGLUE_B_REG_CSDM_INB_INT_A_PF_ENABLE			 0x9194
/* [RW 18] Type B VF inbound पूर्णांकerrupt table क्रम CSDM: bits[17:9]-mask;
 * its[8:0]-address. Bits [1:0] must be zero (DW resolution address). */
#घोषणा PGLUE_B_REG_CSDM_INB_INT_B_VF				 0x916c
/* [RW 1] Type B VF enable inbound पूर्णांकerrupt table क्रम CSDM. 0 - disable; 1
 * - enable. */
#घोषणा PGLUE_B_REG_CSDM_INB_INT_B_VF_ENABLE			 0x919c
/* [RW 16] Start offset of CSDM zone A (queue zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_CSDM_START_OFFSET_A			 0x9100
/* [RW 16] Start offset of CSDM zone B (legacy zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_CSDM_START_OFFSET_B			 0x9108
/* [RW 5] VF Shअगरt of CSDM zone B (legacy zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_CSDM_VF_SHIFT_B				 0x9110
/* [RW 1] 0 - Zone A size is 136x32B; 1 - Zone A size is 152x32B. */
#घोषणा PGLUE_B_REG_CSDM_ZONE_A_SIZE_PF			 0x91ac
/* [R 8] FLR request attention dirty bits क्रम PFs 0 to 7. Each bit indicates
 * that the FLR रेजिस्टर of the corresponding PF was set. Set by PXP. Reset
 * by MCP writing 1 to flr_request_pf_7_0_clr. Note: रेजिस्टर contains bits
 * from both paths. */
#घोषणा PGLUE_B_REG_FLR_REQUEST_PF_7_0				 0x9028
/* [W 8] FLR request attention dirty bits clear क्रम PFs 0 to 7. MCP ग_लिखोs 1
 * to a bit in this रेजिस्टर in order to clear the corresponding bit in
 * flr_request_pf_7_0 रेजिस्टर. Note: रेजिस्टर contains bits from both
 * paths. */
#घोषणा PGLUE_B_REG_FLR_REQUEST_PF_7_0_CLR			 0x9418
/* [R 32] FLR request attention dirty bits क्रम VFs 96 to 127. Each bit
 * indicates that the FLR रेजिस्टर of the corresponding VF was set. Set by
 * PXP. Reset by MCP writing 1 to flr_request_vf_127_96_clr. */
#घोषणा PGLUE_B_REG_FLR_REQUEST_VF_127_96			 0x9024
/* [R 32] FLR request attention dirty bits क्रम VFs 0 to 31. Each bit
 * indicates that the FLR रेजिस्टर of the corresponding VF was set. Set by
 * PXP. Reset by MCP writing 1 to flr_request_vf_31_0_clr. */
#घोषणा PGLUE_B_REG_FLR_REQUEST_VF_31_0			 0x9018
/* [R 32] FLR request attention dirty bits क्रम VFs 32 to 63. Each bit
 * indicates that the FLR रेजिस्टर of the corresponding VF was set. Set by
 * PXP. Reset by MCP writing 1 to flr_request_vf_63_32_clr. */
#घोषणा PGLUE_B_REG_FLR_REQUEST_VF_63_32			 0x901c
/* [R 32] FLR request attention dirty bits क्रम VFs 64 to 95. Each bit
 * indicates that the FLR रेजिस्टर of the corresponding VF was set. Set by
 * PXP. Reset by MCP writing 1 to flr_request_vf_95_64_clr. */
#घोषणा PGLUE_B_REG_FLR_REQUEST_VF_95_64			 0x9020
/* [R 8] Each bit indicates an incorrect behavior in user RX पूर्णांकerface. Bit
 * 0 - Target memory पढ़ो arrived with a correctable error. Bit 1 - Target
 * memory पढ़ो arrived with an uncorrectable error. Bit 2 - Configuration RW
 * arrived with a correctable error. Bit 3 - Configuration RW arrived with
 * an uncorrectable error. Bit 4 - Completion with Configuration Request
 * Retry Status. Bit 5 - Expansion ROM access received with a ग_लिखो request.
 * Bit 6 - Completion with pcie_rx_err of 0000; CMPL_STATUS of non-zero; and
 * pcie_rx_last not निश्चितed. Bit 7 - Completion with pcie_rx_err of 1010;
 * and pcie_rx_last not निश्चितed. */
#घोषणा PGLUE_B_REG_INCORRECT_RCV_DETAILS			 0x9068
#घोषणा PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER		 0x942c
#घोषणा PGLUE_B_REG_INTERNAL_PFID_ENABLE_TARGET_READ		 0x9430
#घोषणा PGLUE_B_REG_INTERNAL_PFID_ENABLE_TARGET_WRITE		 0x9434
#घोषणा PGLUE_B_REG_INTERNAL_VFID_ENABLE			 0x9438
/* [W 7] Writing 1 to each bit in this रेजिस्टर clears a corresponding error
 * details रेजिस्टर and enables logging new error details. Bit 0 - clears
 * INCORRECT_RCV_DETAILS; Bit 1 - clears RX_ERR_DETAILS; Bit 2 - clears
 * TX_ERR_WR_ADD_31_0 TX_ERR_WR_ADD_63_32 TX_ERR_WR_DETAILS
 * TX_ERR_WR_DETAILS2 TX_ERR_RD_ADD_31_0 TX_ERR_RD_ADD_63_32
 * TX_ERR_RD_DETAILS TX_ERR_RD_DETAILS2 TX_ERR_WR_DETAILS_ICPL; Bit 3 -
 * clears VF_LENGTH_VIOLATION_DETAILS. Bit 4 - clears
 * VF_GRC_SPACE_VIOLATION_DETAILS. Bit 5 - clears RX_TCPL_ERR_DETAILS. Bit 6
 * - clears TCPL_IN_TWO_RCBS_DETAILS. */
#घोषणा PGLUE_B_REG_LATCHED_ERRORS_CLR				 0x943c

/* [R 9] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा PGLUE_B_REG_PGLUE_B_INT_STS				 0x9298
/* [RC 9] Interrupt रेजिस्टर #0 पढ़ो clear */
#घोषणा PGLUE_B_REG_PGLUE_B_INT_STS_CLR			 0x929c
/* [RW 2] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PGLUE_B_REG_PGLUE_B_PRTY_MASK				 0x92b4
/* [R 2] Parity रेजिस्टर #0 पढ़ो */
#घोषणा PGLUE_B_REG_PGLUE_B_PRTY_STS				 0x92a8
/* [RC 2] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा PGLUE_B_REG_PGLUE_B_PRTY_STS_CLR			 0x92ac
/* [R 13] Details of first request received with error. [2:0] - PFID. [3] -
 * VF_VALID. [9:4] - VFID. [11:10] - Error Code - 0 - Indicates Completion
 * Timeout of a User Tx non-posted request. 1 - unsupported request. 2 -
 * completer पात. 3 - Illegal value क्रम this field. [12] valid - indicates
 * अगर there was a completion error since the last समय this रेजिस्टर was
 * cleared. */
#घोषणा PGLUE_B_REG_RX_ERR_DETAILS				 0x9080
/* [R 18] Details of first ATS Translation Completion request received with
 * error. [2:0] - PFID. [3] - VF_VALID. [9:4] - VFID. [11:10] - Error Code -
 * 0 - Indicates Completion Timeout of a User Tx non-posted request. 1 -
 * unsupported request. 2 - completer पात. 3 - Illegal value क्रम this
 * field. [16:12] - ATC OTB EntryID. [17] valid - indicates अगर there was a
 * completion error since the last समय this रेजिस्टर was cleared. */
#घोषणा PGLUE_B_REG_RX_TCPL_ERR_DETAILS			 0x9084
/* [W 8] Debug only - Shaकरोw BME bits clear क्रम PFs 0 to 7. MCP ग_लिखोs 1 to
 * a bit in this रेजिस्टर in order to clear the corresponding bit in
 * shaकरोw_bme_pf_7_0 रेजिस्टर. MCP should never use this unless a
 * work-around is needed. Note: रेजिस्टर contains bits from both paths. */
#घोषणा PGLUE_B_REG_SHADOW_BME_PF_7_0_CLR			 0x9458
/* [R 8] SR IOV disabled attention dirty bits. Each bit indicates that the
 * VF enable रेजिस्टर of the corresponding PF is written to 0 and was
 * previously 1. Set by PXP. Reset by MCP writing 1 to
 * sr_iov_disabled_request_clr. Note: रेजिस्टर contains bits from both
 * paths. */
#घोषणा PGLUE_B_REG_SR_IOV_DISABLED_REQUEST			 0x9030
/* [R 32] Indicates the status of tags 32-63. 0 - tags is used - पढ़ो
 * completion did not वापस yet. 1 - tag is unused. Same functionality as
 * pxp2_रेजिस्टरs_pgl_exp_rom_data2 क्रम tags 0-31. */
#घोषणा PGLUE_B_REG_TAGS_63_32					 0x9244
/* [RW 1] Type A PF enable inbound पूर्णांकerrupt table क्रम TSDM. 0 - disable; 1
 * - enable. */
#घोषणा PGLUE_B_REG_TSDM_INB_INT_A_PF_ENABLE			 0x9170
/* [RW 16] Start offset of TSDM zone A (queue zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_TSDM_START_OFFSET_A			 0x90c4
/* [RW 16] Start offset of TSDM zone B (legacy zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_TSDM_START_OFFSET_B			 0x90cc
/* [RW 5] VF Shअगरt of TSDM zone B (legacy zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_TSDM_VF_SHIFT_B				 0x90d4
/* [RW 1] 0 - Zone A size is 136x32B; 1 - Zone A size is 152x32B. */
#घोषणा PGLUE_B_REG_TSDM_ZONE_A_SIZE_PF			 0x91a0
/* [R 32] Address [31:0] of first पढ़ो request not submitted due to error */
#घोषणा PGLUE_B_REG_TX_ERR_RD_ADD_31_0				 0x9098
/* [R 32] Address [63:32] of first पढ़ो request not submitted due to error */
#घोषणा PGLUE_B_REG_TX_ERR_RD_ADD_63_32			 0x909c
/* [R 31] Details of first पढ़ो request not submitted due to error. [4:0]
 * VQID. [5] TREQ. 1 - Indicates the request is a Translation Request.
 * [20:8] - Length in bytes. [23:21] - PFID. [24] - VF_VALID. [30:25] -
 * VFID. */
#घोषणा PGLUE_B_REG_TX_ERR_RD_DETAILS				 0x90a0
/* [R 26] Details of first पढ़ो request not submitted due to error. [15:0]
 * Request ID. [19:16] client ID. [20] - last SR. [24:21] - Error type -
 * [21] - Indicates was_error was set; [22] - Indicates BME was cleared;
 * [23] - Indicates FID_enable was cleared; [24] - Indicates VF with parent
 * PF FLR_request or IOV_disable_request dirty bit is set. [25] valid -
 * indicates अगर there was a request not submitted due to error since the
 * last समय this रेजिस्टर was cleared. */
#घोषणा PGLUE_B_REG_TX_ERR_RD_DETAILS2				 0x90a4
/* [R 32] Address [31:0] of first ग_लिखो request not submitted due to error */
#घोषणा PGLUE_B_REG_TX_ERR_WR_ADD_31_0				 0x9088
/* [R 32] Address [63:32] of first ग_लिखो request not submitted due to error */
#घोषणा PGLUE_B_REG_TX_ERR_WR_ADD_63_32			 0x908c
/* [R 31] Details of first ग_लिखो request not submitted due to error. [4:0]
 * VQID. [20:8] - Length in bytes. [23:21] - PFID. [24] - VF_VALID. [30:25]
 * - VFID. */
#घोषणा PGLUE_B_REG_TX_ERR_WR_DETAILS				 0x9090
/* [R 26] Details of first ग_लिखो request not submitted due to error. [15:0]
 * Request ID. [19:16] client ID. [20] - last SR. [24:21] - Error type -
 * [21] - Indicates was_error was set; [22] - Indicates BME was cleared;
 * [23] - Indicates FID_enable was cleared; [24] - Indicates VF with parent
 * PF FLR_request or IOV_disable_request dirty bit is set. [25] valid -
 * indicates अगर there was a request not submitted due to error since the
 * last समय this रेजिस्टर was cleared. */
#घोषणा PGLUE_B_REG_TX_ERR_WR_DETAILS2				 0x9094
/* [RW 10] Type A PF/VF inbound पूर्णांकerrupt table क्रम USDM: bits[9:5]-mask;
 * its[4:0]-address relative to start_offset_a. Bits [1:0] can have any
 * value (Byte resolution address). */
#घोषणा PGLUE_B_REG_USDM_INB_INT_A_0				 0x9128
#घोषणा PGLUE_B_REG_USDM_INB_INT_A_1				 0x912c
#घोषणा PGLUE_B_REG_USDM_INB_INT_A_2				 0x9130
#घोषणा PGLUE_B_REG_USDM_INB_INT_A_3				 0x9134
#घोषणा PGLUE_B_REG_USDM_INB_INT_A_4				 0x9138
#घोषणा PGLUE_B_REG_USDM_INB_INT_A_5				 0x913c
#घोषणा PGLUE_B_REG_USDM_INB_INT_A_6				 0x9140
/* [RW 1] Type A PF enable inbound पूर्णांकerrupt table क्रम USDM. 0 - disable; 1
 * - enable. */
#घोषणा PGLUE_B_REG_USDM_INB_INT_A_PF_ENABLE			 0x917c
/* [RW 1] Type A VF enable inbound पूर्णांकerrupt table क्रम USDM. 0 - disable; 1
 * - enable. */
#घोषणा PGLUE_B_REG_USDM_INB_INT_A_VF_ENABLE			 0x9180
/* [RW 1] Type B VF enable inbound पूर्णांकerrupt table क्रम USDM. 0 - disable; 1
 * - enable. */
#घोषणा PGLUE_B_REG_USDM_INB_INT_B_VF_ENABLE			 0x9184
/* [RW 16] Start offset of USDM zone A (queue zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_USDM_START_OFFSET_A			 0x90d8
/* [RW 16] Start offset of USDM zone B (legacy zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_USDM_START_OFFSET_B			 0x90e0
/* [RW 5] VF Shअगरt of USDM zone B (legacy zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_USDM_VF_SHIFT_B				 0x90e8
/* [RW 1] 0 - Zone A size is 136x32B; 1 - Zone A size is 152x32B. */
#घोषणा PGLUE_B_REG_USDM_ZONE_A_SIZE_PF			 0x91a4
/* [R 26] Details of first target VF request accessing VF GRC space that
 * failed permission check. [14:0] Address. [15] w_nr: 0 - Read; 1 - Write.
 * [21:16] VFID. [24:22] - PFID. [25] valid - indicates अगर there was a
 * request accessing VF GRC space that failed permission check since the
 * last समय this रेजिस्टर was cleared. Permission checks are: function
 * permission; R/W permission; address range permission. */
#घोषणा PGLUE_B_REG_VF_GRC_SPACE_VIOLATION_DETAILS		 0x9234
/* [R 31] Details of first target VF request with length violation (too many
 * DWs) accessing BAR0. [12:0] Address in DWs (bits [14:2] of byte address).
 * [14:13] BAR. [20:15] VFID. [23:21] - PFID. [29:24] - Length in DWs. [30]
 * valid - indicates अगर there was a request with length violation since the
 * last समय this रेजिस्टर was cleared. Length violations: length of more
 * than 2DWs; length of 2DWs and address not QW aligned; winकरोw is GRC and
 * length is more than 1 DW. */
#घोषणा PGLUE_B_REG_VF_LENGTH_VIOLATION_DETAILS		 0x9230
/* [R 8] Was_error indication dirty bits क्रम PFs 0 to 7. Each bit indicates
 * that there was a completion with uncorrectable error क्रम the
 * corresponding PF. Set by PXP. Reset by MCP writing 1 to
 * was_error_pf_7_0_clr. */
#घोषणा PGLUE_B_REG_WAS_ERROR_PF_7_0				 0x907c
/* [W 8] Was_error indication dirty bits clear क्रम PFs 0 to 7. MCP ग_लिखोs 1
 * to a bit in this रेजिस्टर in order to clear the corresponding bit in
 * flr_request_pf_7_0 रेजिस्टर. */
#घोषणा PGLUE_B_REG_WAS_ERROR_PF_7_0_CLR			 0x9470
/* [R 32] Was_error indication dirty bits क्रम VFs 96 to 127. Each bit
 * indicates that there was a completion with uncorrectable error क्रम the
 * corresponding VF. Set by PXP. Reset by MCP writing 1 to
 * was_error_vf_127_96_clr. */
#घोषणा PGLUE_B_REG_WAS_ERROR_VF_127_96			 0x9078
/* [W 32] Was_error indication dirty bits clear क्रम VFs 96 to 127. MCP
 * ग_लिखोs 1 to a bit in this रेजिस्टर in order to clear the corresponding
 * bit in was_error_vf_127_96 रेजिस्टर. */
#घोषणा PGLUE_B_REG_WAS_ERROR_VF_127_96_CLR			 0x9474
/* [R 32] Was_error indication dirty bits क्रम VFs 0 to 31. Each bit
 * indicates that there was a completion with uncorrectable error क्रम the
 * corresponding VF. Set by PXP. Reset by MCP writing 1 to
 * was_error_vf_31_0_clr. */
#घोषणा PGLUE_B_REG_WAS_ERROR_VF_31_0				 0x906c
/* [W 32] Was_error indication dirty bits clear क्रम VFs 0 to 31. MCP ग_लिखोs
 * 1 to a bit in this रेजिस्टर in order to clear the corresponding bit in
 * was_error_vf_31_0 रेजिस्टर. */
#घोषणा PGLUE_B_REG_WAS_ERROR_VF_31_0_CLR			 0x9478
/* [R 32] Was_error indication dirty bits क्रम VFs 32 to 63. Each bit
 * indicates that there was a completion with uncorrectable error क्रम the
 * corresponding VF. Set by PXP. Reset by MCP writing 1 to
 * was_error_vf_63_32_clr. */
#घोषणा PGLUE_B_REG_WAS_ERROR_VF_63_32				 0x9070
/* [W 32] Was_error indication dirty bits clear क्रम VFs 32 to 63. MCP ग_लिखोs
 * 1 to a bit in this रेजिस्टर in order to clear the corresponding bit in
 * was_error_vf_63_32 रेजिस्टर. */
#घोषणा PGLUE_B_REG_WAS_ERROR_VF_63_32_CLR			 0x947c
/* [R 32] Was_error indication dirty bits क्रम VFs 64 to 95. Each bit
 * indicates that there was a completion with uncorrectable error क्रम the
 * corresponding VF. Set by PXP. Reset by MCP writing 1 to
 * was_error_vf_95_64_clr. */
#घोषणा PGLUE_B_REG_WAS_ERROR_VF_95_64				 0x9074
/* [W 32] Was_error indication dirty bits clear क्रम VFs 64 to 95. MCP ग_लिखोs
 * 1 to a bit in this रेजिस्टर in order to clear the corresponding bit in
 * was_error_vf_95_64 रेजिस्टर. */
#घोषणा PGLUE_B_REG_WAS_ERROR_VF_95_64_CLR			 0x9480
/* [RW 1] Type A PF enable inbound पूर्णांकerrupt table क्रम XSDM. 0 - disable; 1
 * - enable. */
#घोषणा PGLUE_B_REG_XSDM_INB_INT_A_PF_ENABLE			 0x9188
/* [RW 16] Start offset of XSDM zone A (queue zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_XSDM_START_OFFSET_A			 0x90ec
/* [RW 16] Start offset of XSDM zone B (legacy zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_XSDM_START_OFFSET_B			 0x90f4
/* [RW 5] VF Shअगरt of XSDM zone B (legacy zone) in the पूर्णांकernal RAM */
#घोषणा PGLUE_B_REG_XSDM_VF_SHIFT_B				 0x90fc
/* [RW 1] 0 - Zone A size is 136x32B; 1 - Zone A size is 152x32B. */
#घोषणा PGLUE_B_REG_XSDM_ZONE_A_SIZE_PF			 0x91a8
#घोषणा PRS_REG_A_PRSU_20					 0x40134
/* [R 8] debug only: CFC load request current credit. Transaction based. */
#घोषणा PRS_REG_CFC_LD_CURRENT_CREDIT				 0x40164
/* [R 8] debug only: CFC search request current credit. Transaction based. */
#घोषणा PRS_REG_CFC_SEARCH_CURRENT_CREDIT			 0x40168
/* [RW 6] The initial credit क्रम the search message to the CFC पूर्णांकerface.
   Credit is transaction based. */
#घोषणा PRS_REG_CFC_SEARCH_INITIAL_CREDIT			 0x4011c
/* [RW 24] CID क्रम port 0 अगर no match */
#घोषणा PRS_REG_CID_PORT_0					 0x400fc
/* [RW 32] The CM header क्रम flush message where 'load existed' bit in CFC
   load response is reset and packet type is 0. Used in packet start message
   to TCM. */
#घोषणा PRS_REG_CM_HDR_FLUSH_LOAD_TYPE_0			 0x400dc
#घोषणा PRS_REG_CM_HDR_FLUSH_LOAD_TYPE_1			 0x400e0
#घोषणा PRS_REG_CM_HDR_FLUSH_LOAD_TYPE_2			 0x400e4
#घोषणा PRS_REG_CM_HDR_FLUSH_LOAD_TYPE_3			 0x400e8
#घोषणा PRS_REG_CM_HDR_FLUSH_LOAD_TYPE_4			 0x400ec
#घोषणा PRS_REG_CM_HDR_FLUSH_LOAD_TYPE_5			 0x400f0
/* [RW 32] The CM header क्रम flush message where 'load existed' bit in CFC
   load response is set and packet type is 0. Used in packet start message
   to TCM. */
#घोषणा PRS_REG_CM_HDR_FLUSH_NO_LOAD_TYPE_0			 0x400bc
#घोषणा PRS_REG_CM_HDR_FLUSH_NO_LOAD_TYPE_1			 0x400c0
#घोषणा PRS_REG_CM_HDR_FLUSH_NO_LOAD_TYPE_2			 0x400c4
#घोषणा PRS_REG_CM_HDR_FLUSH_NO_LOAD_TYPE_3			 0x400c8
#घोषणा PRS_REG_CM_HDR_FLUSH_NO_LOAD_TYPE_4			 0x400cc
#घोषणा PRS_REG_CM_HDR_FLUSH_NO_LOAD_TYPE_5			 0x400d0
/* [RW 32] The CM header क्रम a match and packet type 1 क्रम loopback port.
   Used in packet start message to TCM. */
#घोषणा PRS_REG_CM_HDR_LOOPBACK_TYPE_1				 0x4009c
#घोषणा PRS_REG_CM_HDR_LOOPBACK_TYPE_2				 0x400a0
#घोषणा PRS_REG_CM_HDR_LOOPBACK_TYPE_3				 0x400a4
#घोषणा PRS_REG_CM_HDR_LOOPBACK_TYPE_4				 0x400a8
/* [RW 32] The CM header क्रम a match and packet type 0. Used in packet start
   message to TCM. */
#घोषणा PRS_REG_CM_HDR_TYPE_0					 0x40078
#घोषणा PRS_REG_CM_HDR_TYPE_1					 0x4007c
#घोषणा PRS_REG_CM_HDR_TYPE_2					 0x40080
#घोषणा PRS_REG_CM_HDR_TYPE_3					 0x40084
#घोषणा PRS_REG_CM_HDR_TYPE_4					 0x40088
/* [RW 32] The CM header in हाल there was not a match on the connection */
#घोषणा PRS_REG_CM_NO_MATCH_HDR 				 0x400b8
/* [RW 1] Indicates अगर in e1hov mode. 0=non-e1hov mode; 1=e1hov mode. */
#घोषणा PRS_REG_E1HOV_MODE					 0x401c8
/* [RW 8] The 8-bit event ID क्रम a match and packet type 1. Used in packet
   start message to TCM. */
#घोषणा PRS_REG_EVENT_ID_1					 0x40054
#घोषणा PRS_REG_EVENT_ID_2					 0x40058
#घोषणा PRS_REG_EVENT_ID_3					 0x4005c
/* [RW 16] The Ethernet type value क्रम FCoE */
#घोषणा PRS_REG_FCOE_TYPE					 0x401d0
/* [RW 8] Context region क्रम flush packet with packet type 0. Used in CFC
   load request message. */
#घोषणा PRS_REG_FLUSH_REGIONS_TYPE_0				 0x40004
#घोषणा PRS_REG_FLUSH_REGIONS_TYPE_1				 0x40008
#घोषणा PRS_REG_FLUSH_REGIONS_TYPE_2				 0x4000c
#घोषणा PRS_REG_FLUSH_REGIONS_TYPE_3				 0x40010
#घोषणा PRS_REG_FLUSH_REGIONS_TYPE_4				 0x40014
#घोषणा PRS_REG_FLUSH_REGIONS_TYPE_5				 0x40018
#घोषणा PRS_REG_FLUSH_REGIONS_TYPE_6				 0x4001c
#घोषणा PRS_REG_FLUSH_REGIONS_TYPE_7				 0x40020
/* [RW 6] Bit-map indicating which L2 hdrs may appear after the basic
 * Ethernet header. */
#घोषणा PRS_REG_HDRS_AFTER_BASIC				 0x40238
/* [RW 6] Bit-map indicating which L2 hdrs may appear after the basic
 * Ethernet header क्रम port 0 packets. */
#घोषणा PRS_REG_HDRS_AFTER_BASIC_PORT_0				 0x40270
#घोषणा PRS_REG_HDRS_AFTER_BASIC_PORT_1				 0x40290
/* [R 6] Bit-map indicating which L2 hdrs may appear after L2 tag 0 */
#घोषणा PRS_REG_HDRS_AFTER_TAG_0				 0x40248
/* [RW 6] Bit-map indicating which L2 hdrs may appear after L2 tag 0 क्रम
 * port 0 packets */
#घोषणा PRS_REG_HDRS_AFTER_TAG_0_PORT_0				 0x40280
#घोषणा PRS_REG_HDRS_AFTER_TAG_0_PORT_1				 0x402a0
/* [RW 4] The increment value to send in the CFC load request message */
#घोषणा PRS_REG_INC_VALUE					 0x40048
/* [RW 6] Bit-map indicating which headers must appear in the packet */
#घोषणा PRS_REG_MUST_HAVE_HDRS					 0x40254
/* [RW 6] Bit-map indicating which headers must appear in the packet क्रम
 * port 0 packets */
#घोषणा PRS_REG_MUST_HAVE_HDRS_PORT_0				 0x4028c
#घोषणा PRS_REG_MUST_HAVE_HDRS_PORT_1				 0x402ac
#घोषणा PRS_REG_NIC_MODE					 0x40138
/* [RW 8] The 8-bit event ID क्रम हालs where there is no match on the
   connection. Used in packet start message to TCM. */
#घोषणा PRS_REG_NO_MATCH_EVENT_ID				 0x40070
/* [ST 24] The number of input CFC flush packets */
#घोषणा PRS_REG_NUM_OF_CFC_FLUSH_MESSAGES			 0x40128
/* [ST 32] The number of cycles the Parser halted its operation since it
   could not allocate the next serial number */
#घोषणा PRS_REG_NUM_OF_DEAD_CYCLES				 0x40130
/* [ST 24] The number of input packets */
#घोषणा PRS_REG_NUM_OF_PACKETS					 0x40124
/* [ST 24] The number of input transparent flush packets */
#घोषणा PRS_REG_NUM_OF_TRANSPARENT_FLUSH_MESSAGES		 0x4012c
/* [RW 8] Context region क्रम received Ethernet packet with a match and
   packet type 0. Used in CFC load request message */
#घोषणा PRS_REG_PACKET_REGIONS_TYPE_0				 0x40028
#घोषणा PRS_REG_PACKET_REGIONS_TYPE_1				 0x4002c
#घोषणा PRS_REG_PACKET_REGIONS_TYPE_2				 0x40030
#घोषणा PRS_REG_PACKET_REGIONS_TYPE_3				 0x40034
#घोषणा PRS_REG_PACKET_REGIONS_TYPE_4				 0x40038
#घोषणा PRS_REG_PACKET_REGIONS_TYPE_5				 0x4003c
#घोषणा PRS_REG_PACKET_REGIONS_TYPE_6				 0x40040
#घोषणा PRS_REG_PACKET_REGIONS_TYPE_7				 0x40044
/* [R 2] debug only: Number of pending requests क्रम CAC on port 0. */
#घोषणा PRS_REG_PENDING_BRB_CAC0_RQ				 0x40174
/* [R 2] debug only: Number of pending requests क्रम header parsing. */
#घोषणा PRS_REG_PENDING_BRB_PRS_RQ				 0x40170
/* [R 1] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा PRS_REG_PRS_INT_STS					 0x40188
/* [RW 8] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PRS_REG_PRS_PRTY_MASK					 0x401a4
/* [R 8] Parity रेजिस्टर #0 पढ़ो */
#घोषणा PRS_REG_PRS_PRTY_STS					 0x40198
/* [RC 8] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा PRS_REG_PRS_PRTY_STS_CLR				 0x4019c
/* [RW 8] Context region क्रम pure acknowledge packets. Used in CFC load
   request message */
#घोषणा PRS_REG_PURE_REGIONS					 0x40024
/* [R 32] debug only: Serial number status lsb 32 bits. '1' indicates this
   serail number was released by SDM but cannot be used because a previous
   serial number was not released. */
#घोषणा PRS_REG_SERIAL_NUM_STATUS_LSB				 0x40154
/* [R 32] debug only: Serial number status msb 32 bits. '1' indicates this
   serail number was released by SDM but cannot be used because a previous
   serial number was not released. */
#घोषणा PRS_REG_SERIAL_NUM_STATUS_MSB				 0x40158
/* [R 4] debug only: SRC current credit. Transaction based. */
#घोषणा PRS_REG_SRC_CURRENT_CREDIT				 0x4016c
/* [RW 16] The Ethernet type value क्रम L2 tag 0 */
#घोषणा PRS_REG_TAG_ETHERTYPE_0					 0x401d4
/* [RW 4] The length of the info field क्रम L2 tag 0. The length is between
 * 2B and 14B; in 2B granularity */
#घोषणा PRS_REG_TAG_LEN_0					 0x4022c
/* [R 8] debug only: TCM current credit. Cycle based. */
#घोषणा PRS_REG_TCM_CURRENT_CREDIT				 0x40160
/* [R 8] debug only: TSDM current credit. Transaction based. */
#घोषणा PRS_REG_TSDM_CURRENT_CREDIT				 0x4015c
/* [RW 16] One of 8 values that should be compared to type in Ethernet
 * parsing. If there is a match; the field after Ethernet is the first VLAN.
 * Reset value is 0x8100 which is the standard VLAN type. Note that when
 * checking second VLAN; type is compared only to 0x8100.
 */
#घोषणा PRS_REG_VLAN_TYPE_0					 0x401a8
#घोषणा PXP2_PXP2_INT_MASK_0_REG_PGL_CPL_AFT			 (0x1<<19)
#घोषणा PXP2_PXP2_INT_MASK_0_REG_PGL_CPL_OF			 (0x1<<20)
#घोषणा PXP2_PXP2_INT_MASK_0_REG_PGL_PCIE_ATTN			 (0x1<<22)
#घोषणा PXP2_PXP2_INT_MASK_0_REG_PGL_READ_BLOCKED		 (0x1<<23)
#घोषणा PXP2_PXP2_INT_MASK_0_REG_PGL_WRITE_BLOCKED		 (0x1<<24)
#घोषणा PXP2_PXP2_INT_STS_0_REG_WR_PGLUE_EOP_ERROR		 (0x1<<7)
#घोषणा PXP2_PXP2_INT_STS_CLR_0_REG_WR_PGLUE_EOP_ERROR		 (0x1<<7)
/* [R 6] Debug only: Number of used entries in the data FIFO */
#घोषणा PXP2_REG_HST_DATA_FIFO_STATUS				 0x12047c
/* [R 7] Debug only: Number of used entries in the header FIFO */
#घोषणा PXP2_REG_HST_HEADER_FIFO_STATUS				 0x120478
#घोषणा PXP2_REG_PGL_ADDR_88_F0					 0x120534
/* [R 32] GRC address क्रम configuration access to PCIE config address 0x88.
 * any ग_लिखो to this PCIE address will cause a GRC ग_लिखो access to the
 * address that's in t this रेजिस्टर */
#घोषणा PXP2_REG_PGL_ADDR_88_F1					 0x120544
#घोषणा PXP2_REG_PGL_ADDR_8C_F0					 0x120538
/* [R 32] GRC address क्रम configuration access to PCIE config address 0x8c.
 * any ग_लिखो to this PCIE address will cause a GRC ग_लिखो access to the
 * address that's in t this रेजिस्टर */
#घोषणा PXP2_REG_PGL_ADDR_8C_F1					 0x120548
#घोषणा PXP2_REG_PGL_ADDR_90_F0					 0x12053c
/* [R 32] GRC address क्रम configuration access to PCIE config address 0x90.
 * any ग_लिखो to this PCIE address will cause a GRC ग_लिखो access to the
 * address that's in t this रेजिस्टर */
#घोषणा PXP2_REG_PGL_ADDR_90_F1					 0x12054c
#घोषणा PXP2_REG_PGL_ADDR_94_F0					 0x120540
/* [R 32] GRC address क्रम configuration access to PCIE config address 0x94.
 * any ग_लिखो to this PCIE address will cause a GRC ग_लिखो access to the
 * address that's in t this रेजिस्टर */
#घोषणा PXP2_REG_PGL_ADDR_94_F1					 0x120550
#घोषणा PXP2_REG_PGL_CONTROL0					 0x120490
#घोषणा PXP2_REG_PGL_CONTROL1					 0x120514
#घोषणा PXP2_REG_PGL_DEBUG					 0x120520
/* [RW 32] third dword data of expansion rom request. this रेजिस्टर is
   special. पढ़ोing from it provides a vector outstanding पढ़ो requests. अगर
   a bit is zero it means that a पढ़ो request on the corresponding tag did
   not finish yet (not all completions have arrived क्रम it) */
#घोषणा PXP2_REG_PGL_EXP_ROM2					 0x120808
/* [RW 32] Inbound पूर्णांकerrupt table क्रम CSDM: bits[31:16]-mask;
   its[15:0]-address */
#घोषणा PXP2_REG_PGL_INT_CSDM_0 				 0x1204f4
#घोषणा PXP2_REG_PGL_INT_CSDM_1 				 0x1204f8
#घोषणा PXP2_REG_PGL_INT_CSDM_2 				 0x1204fc
#घोषणा PXP2_REG_PGL_INT_CSDM_3 				 0x120500
#घोषणा PXP2_REG_PGL_INT_CSDM_4 				 0x120504
#घोषणा PXP2_REG_PGL_INT_CSDM_5 				 0x120508
#घोषणा PXP2_REG_PGL_INT_CSDM_6 				 0x12050c
#घोषणा PXP2_REG_PGL_INT_CSDM_7 				 0x120510
/* [RW 32] Inbound पूर्णांकerrupt table क्रम TSDM: bits[31:16]-mask;
   its[15:0]-address */
#घोषणा PXP2_REG_PGL_INT_TSDM_0 				 0x120494
#घोषणा PXP2_REG_PGL_INT_TSDM_1 				 0x120498
#घोषणा PXP2_REG_PGL_INT_TSDM_2 				 0x12049c
#घोषणा PXP2_REG_PGL_INT_TSDM_3 				 0x1204a0
#घोषणा PXP2_REG_PGL_INT_TSDM_4 				 0x1204a4
#घोषणा PXP2_REG_PGL_INT_TSDM_5 				 0x1204a8
#घोषणा PXP2_REG_PGL_INT_TSDM_6 				 0x1204ac
#घोषणा PXP2_REG_PGL_INT_TSDM_7 				 0x1204b0
/* [RW 32] Inbound पूर्णांकerrupt table क्रम USDM: bits[31:16]-mask;
   its[15:0]-address */
#घोषणा PXP2_REG_PGL_INT_USDM_0 				 0x1204b4
#घोषणा PXP2_REG_PGL_INT_USDM_1 				 0x1204b8
#घोषणा PXP2_REG_PGL_INT_USDM_2 				 0x1204bc
#घोषणा PXP2_REG_PGL_INT_USDM_3 				 0x1204c0
#घोषणा PXP2_REG_PGL_INT_USDM_4 				 0x1204c4
#घोषणा PXP2_REG_PGL_INT_USDM_5 				 0x1204c8
#घोषणा PXP2_REG_PGL_INT_USDM_6 				 0x1204cc
#घोषणा PXP2_REG_PGL_INT_USDM_7 				 0x1204d0
/* [RW 32] Inbound पूर्णांकerrupt table क्रम XSDM: bits[31:16]-mask;
   its[15:0]-address */
#घोषणा PXP2_REG_PGL_INT_XSDM_0 				 0x1204d4
#घोषणा PXP2_REG_PGL_INT_XSDM_1 				 0x1204d8
#घोषणा PXP2_REG_PGL_INT_XSDM_2 				 0x1204dc
#घोषणा PXP2_REG_PGL_INT_XSDM_3 				 0x1204e0
#घोषणा PXP2_REG_PGL_INT_XSDM_4 				 0x1204e4
#घोषणा PXP2_REG_PGL_INT_XSDM_5 				 0x1204e8
#घोषणा PXP2_REG_PGL_INT_XSDM_6 				 0x1204ec
#घोषणा PXP2_REG_PGL_INT_XSDM_7 				 0x1204f0
/* [RW 3] this field allows one function to pretend being another function
   when accessing any BAR mapped resource within the device. the value of
   the field is the number of the function that will be accessed
   effectively. after software ग_लिखो to this bit it must पढ़ो it in order to
   know that the new value is updated */
#घोषणा PXP2_REG_PGL_PRETEND_FUNC_F0				 0x120674
#घोषणा PXP2_REG_PGL_PRETEND_FUNC_F1				 0x120678
#घोषणा PXP2_REG_PGL_PRETEND_FUNC_F2				 0x12067c
#घोषणा PXP2_REG_PGL_PRETEND_FUNC_F3				 0x120680
#घोषणा PXP2_REG_PGL_PRETEND_FUNC_F4				 0x120684
#घोषणा PXP2_REG_PGL_PRETEND_FUNC_F5				 0x120688
#घोषणा PXP2_REG_PGL_PRETEND_FUNC_F6				 0x12068c
#घोषणा PXP2_REG_PGL_PRETEND_FUNC_F7				 0x120690
/* [R 1] this bit indicates that a पढ़ो request was blocked because of
   bus_master_en was deनिश्चितed */
#घोषणा PXP2_REG_PGL_READ_BLOCKED				 0x120568
#घोषणा PXP2_REG_PGL_TAGS_LIMIT 				 0x1205a8
/* [R 18] debug only */
#घोषणा PXP2_REG_PGL_TXW_CDTS					 0x12052c
/* [R 1] this bit indicates that a ग_लिखो request was blocked because of
   bus_master_en was deनिश्चितed */
#घोषणा PXP2_REG_PGL_WRITE_BLOCKED				 0x120564
#घोषणा PXP2_REG_PSWRQ_BW_ADD1					 0x1201c0
#घोषणा PXP2_REG_PSWRQ_BW_ADD10 				 0x1201e4
#घोषणा PXP2_REG_PSWRQ_BW_ADD11 				 0x1201e8
#घोषणा PXP2_REG_PSWRQ_BW_ADD2					 0x1201c4
#घोषणा PXP2_REG_PSWRQ_BW_ADD28 				 0x120228
#घोषणा PXP2_REG_PSWRQ_BW_ADD3					 0x1201c8
#घोषणा PXP2_REG_PSWRQ_BW_ADD6					 0x1201d4
#घोषणा PXP2_REG_PSWRQ_BW_ADD7					 0x1201d8
#घोषणा PXP2_REG_PSWRQ_BW_ADD8					 0x1201dc
#घोषणा PXP2_REG_PSWRQ_BW_ADD9					 0x1201e0
#घोषणा PXP2_REG_PSWRQ_BW_CREDIT				 0x12032c
#घोषणा PXP2_REG_PSWRQ_BW_L1					 0x1202b0
#घोषणा PXP2_REG_PSWRQ_BW_L10					 0x1202d4
#घोषणा PXP2_REG_PSWRQ_BW_L11					 0x1202d8
#घोषणा PXP2_REG_PSWRQ_BW_L2					 0x1202b4
#घोषणा PXP2_REG_PSWRQ_BW_L28					 0x120318
#घोषणा PXP2_REG_PSWRQ_BW_L3					 0x1202b8
#घोषणा PXP2_REG_PSWRQ_BW_L6					 0x1202c4
#घोषणा PXP2_REG_PSWRQ_BW_L7					 0x1202c8
#घोषणा PXP2_REG_PSWRQ_BW_L8					 0x1202cc
#घोषणा PXP2_REG_PSWRQ_BW_L9					 0x1202d0
#घोषणा PXP2_REG_PSWRQ_BW_RD					 0x120324
#घोषणा PXP2_REG_PSWRQ_BW_UB1					 0x120238
#घोषणा PXP2_REG_PSWRQ_BW_UB10					 0x12025c
#घोषणा PXP2_REG_PSWRQ_BW_UB11					 0x120260
#घोषणा PXP2_REG_PSWRQ_BW_UB2					 0x12023c
#घोषणा PXP2_REG_PSWRQ_BW_UB28					 0x1202a0
#घोषणा PXP2_REG_PSWRQ_BW_UB3					 0x120240
#घोषणा PXP2_REG_PSWRQ_BW_UB6					 0x12024c
#घोषणा PXP2_REG_PSWRQ_BW_UB7					 0x120250
#घोषणा PXP2_REG_PSWRQ_BW_UB8					 0x120254
#घोषणा PXP2_REG_PSWRQ_BW_UB9					 0x120258
#घोषणा PXP2_REG_PSWRQ_BW_WR					 0x120328
#घोषणा PXP2_REG_PSWRQ_CDU0_L2P 				 0x120000
#घोषणा PXP2_REG_PSWRQ_QM0_L2P					 0x120038
#घोषणा PXP2_REG_PSWRQ_SRC0_L2P 				 0x120054
#घोषणा PXP2_REG_PSWRQ_TM0_L2P					 0x12001c
#घोषणा PXP2_REG_PSWRQ_TSDM0_L2P				 0x1200e0
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PXP2_REG_PXP2_INT_MASK_0				 0x120578
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा PXP2_REG_PXP2_INT_STS_0 				 0x12056c
#घोषणा PXP2_REG_PXP2_INT_STS_1 				 0x120608
/* [RC 32] Interrupt रेजिस्टर #0 पढ़ो clear */
#घोषणा PXP2_REG_PXP2_INT_STS_CLR_0				 0x120570
/* [RW 32] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PXP2_REG_PXP2_PRTY_MASK_0				 0x120588
#घोषणा PXP2_REG_PXP2_PRTY_MASK_1				 0x120598
/* [R 32] Parity रेजिस्टर #0 पढ़ो */
#घोषणा PXP2_REG_PXP2_PRTY_STS_0				 0x12057c
#घोषणा PXP2_REG_PXP2_PRTY_STS_1				 0x12058c
/* [RC 32] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा PXP2_REG_PXP2_PRTY_STS_CLR_0				 0x120580
#घोषणा PXP2_REG_PXP2_PRTY_STS_CLR_1				 0x120590
/* [R 1] Debug only: The 'almost full' indication from each fअगरo (gives
   indication about backpressure) */
#घोषणा PXP2_REG_RD_ALMOST_FULL_0				 0x120424
/* [R 8] Debug only: The blocks counter - number of unused block ids */
#घोषणा PXP2_REG_RD_BLK_CNT					 0x120418
/* [RW 8] Debug only: Total number of available blocks in Tetris Buffer.
   Must be bigger than 6. Normally should not be changed. */
#घोषणा PXP2_REG_RD_BLK_NUM_CFG 				 0x12040c
/* [RW 2] CDU byte swapping mode configuration क्रम master पढ़ो requests */
#घोषणा PXP2_REG_RD_CDURD_SWAP_MODE				 0x120404
/* [RW 1] When '1'; inमाला_दो to the PSWRD block are ignored */
#घोषणा PXP2_REG_RD_DISABLE_INPUTS				 0x120374
/* [R 1] PSWRD पूर्णांकernal memories initialization is करोne */
#घोषणा PXP2_REG_RD_INIT_DONE					 0x120370
/* [RW 8] The maximum number of blocks in Tetris Buffer that can be
   allocated क्रम vq10 */
#घोषणा PXP2_REG_RD_MAX_BLKS_VQ10				 0x1203a0
/* [RW 8] The maximum number of blocks in Tetris Buffer that can be
   allocated क्रम vq11 */
#घोषणा PXP2_REG_RD_MAX_BLKS_VQ11				 0x1203a4
/* [RW 8] The maximum number of blocks in Tetris Buffer that can be
   allocated क्रम vq17 */
#घोषणा PXP2_REG_RD_MAX_BLKS_VQ17				 0x1203bc
/* [RW 8] The maximum number of blocks in Tetris Buffer that can be
   allocated क्रम vq18 */
#घोषणा PXP2_REG_RD_MAX_BLKS_VQ18				 0x1203c0
/* [RW 8] The maximum number of blocks in Tetris Buffer that can be
   allocated क्रम vq19 */
#घोषणा PXP2_REG_RD_MAX_BLKS_VQ19				 0x1203c4
/* [RW 8] The maximum number of blocks in Tetris Buffer that can be
   allocated क्रम vq22 */
#घोषणा PXP2_REG_RD_MAX_BLKS_VQ22				 0x1203d0
/* [RW 8] The maximum number of blocks in Tetris Buffer that can be
   allocated क्रम vq25 */
#घोषणा PXP2_REG_RD_MAX_BLKS_VQ25				 0x1203dc
/* [RW 8] The maximum number of blocks in Tetris Buffer that can be
   allocated क्रम vq6 */
#घोषणा PXP2_REG_RD_MAX_BLKS_VQ6				 0x120390
/* [RW 8] The maximum number of blocks in Tetris Buffer that can be
   allocated क्रम vq9 */
#घोषणा PXP2_REG_RD_MAX_BLKS_VQ9				 0x12039c
/* [RW 2] PBF byte swapping mode configuration क्रम master पढ़ो requests */
#घोषणा PXP2_REG_RD_PBF_SWAP_MODE				 0x1203f4
/* [R 1] Debug only: Indication अगर delivery ports are idle */
#घोषणा PXP2_REG_RD_PORT_IS_IDLE_0				 0x12041c
#घोषणा PXP2_REG_RD_PORT_IS_IDLE_1				 0x120420
/* [RW 2] QM byte swapping mode configuration क्रम master पढ़ो requests */
#घोषणा PXP2_REG_RD_QM_SWAP_MODE				 0x1203f8
/* [R 7] Debug only: The SR counter - number of unused sub request ids */
#घोषणा PXP2_REG_RD_SR_CNT					 0x120414
/* [RW 2] SRC byte swapping mode configuration क्रम master पढ़ो requests */
#घोषणा PXP2_REG_RD_SRC_SWAP_MODE				 0x120400
/* [RW 7] Debug only: Total number of available PCI पढ़ो sub-requests. Must
   be bigger than 1. Normally should not be changed. */
#घोषणा PXP2_REG_RD_SR_NUM_CFG					 0x120408
/* [RW 1] Signals the PSWRD block to start initializing पूर्णांकernal memories */
#घोषणा PXP2_REG_RD_START_INIT					 0x12036c
/* [RW 2] TM byte swapping mode configuration क्रम master पढ़ो requests */
#घोषणा PXP2_REG_RD_TM_SWAP_MODE				 0x1203fc
/* [RW 10] Bandwidth addition to VQ0 ग_लिखो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD0					 0x1201bc
/* [RW 10] Bandwidth addition to VQ12 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD12 				 0x1201ec
/* [RW 10] Bandwidth addition to VQ13 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD13 				 0x1201f0
/* [RW 10] Bandwidth addition to VQ14 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD14 				 0x1201f4
/* [RW 10] Bandwidth addition to VQ15 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD15 				 0x1201f8
/* [RW 10] Bandwidth addition to VQ16 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD16 				 0x1201fc
/* [RW 10] Bandwidth addition to VQ17 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD17 				 0x120200
/* [RW 10] Bandwidth addition to VQ18 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD18 				 0x120204
/* [RW 10] Bandwidth addition to VQ19 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD19 				 0x120208
/* [RW 10] Bandwidth addition to VQ20 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD20 				 0x12020c
/* [RW 10] Bandwidth addition to VQ22 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD22 				 0x120210
/* [RW 10] Bandwidth addition to VQ23 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD23 				 0x120214
/* [RW 10] Bandwidth addition to VQ24 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD24 				 0x120218
/* [RW 10] Bandwidth addition to VQ25 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD25 				 0x12021c
/* [RW 10] Bandwidth addition to VQ26 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD26 				 0x120220
/* [RW 10] Bandwidth addition to VQ27 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD27 				 0x120224
/* [RW 10] Bandwidth addition to VQ4 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD4					 0x1201cc
/* [RW 10] Bandwidth addition to VQ5 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_ADD5					 0x1201d0
/* [RW 10] Bandwidth Typical L क्रम VQ0 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L0					 0x1202ac
/* [RW 10] Bandwidth Typical L क्रम VQ12 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L12					 0x1202dc
/* [RW 10] Bandwidth Typical L क्रम VQ13 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L13					 0x1202e0
/* [RW 10] Bandwidth Typical L क्रम VQ14 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L14					 0x1202e4
/* [RW 10] Bandwidth Typical L क्रम VQ15 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L15					 0x1202e8
/* [RW 10] Bandwidth Typical L क्रम VQ16 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L16					 0x1202ec
/* [RW 10] Bandwidth Typical L क्रम VQ17 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L17					 0x1202f0
/* [RW 10] Bandwidth Typical L क्रम VQ18 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L18					 0x1202f4
/* [RW 10] Bandwidth Typical L क्रम VQ19 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L19					 0x1202f8
/* [RW 10] Bandwidth Typical L क्रम VQ20 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L20					 0x1202fc
/* [RW 10] Bandwidth Typical L क्रम VQ22 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L22					 0x120300
/* [RW 10] Bandwidth Typical L क्रम VQ23 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L23					 0x120304
/* [RW 10] Bandwidth Typical L क्रम VQ24 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L24					 0x120308
/* [RW 10] Bandwidth Typical L क्रम VQ25 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L25					 0x12030c
/* [RW 10] Bandwidth Typical L क्रम VQ26 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L26					 0x120310
/* [RW 10] Bandwidth Typical L क्रम VQ27 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L27					 0x120314
/* [RW 10] Bandwidth Typical L क्रम VQ4 Read requests */
#घोषणा PXP2_REG_RQ_BW_RD_L4					 0x1202bc
/* [RW 10] Bandwidth Typical L क्रम VQ5 Read- currently not used */
#घोषणा PXP2_REG_RQ_BW_RD_L5					 0x1202c0
/* [RW 7] Bandwidth upper bound क्रम VQ0 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND0				 0x120234
/* [RW 7] Bandwidth upper bound क्रम VQ12 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND12				 0x120264
/* [RW 7] Bandwidth upper bound क्रम VQ13 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND13				 0x120268
/* [RW 7] Bandwidth upper bound क्रम VQ14 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND14				 0x12026c
/* [RW 7] Bandwidth upper bound क्रम VQ15 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND15				 0x120270
/* [RW 7] Bandwidth upper bound क्रम VQ16 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND16				 0x120274
/* [RW 7] Bandwidth upper bound क्रम VQ17 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND17				 0x120278
/* [RW 7] Bandwidth upper bound क्रम VQ18 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND18				 0x12027c
/* [RW 7] Bandwidth upper bound क्रम VQ19 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND19				 0x120280
/* [RW 7] Bandwidth upper bound क्रम VQ20 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND20				 0x120284
/* [RW 7] Bandwidth upper bound क्रम VQ22 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND22				 0x120288
/* [RW 7] Bandwidth upper bound क्रम VQ23 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND23				 0x12028c
/* [RW 7] Bandwidth upper bound क्रम VQ24 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND24				 0x120290
/* [RW 7] Bandwidth upper bound क्रम VQ25 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND25				 0x120294
/* [RW 7] Bandwidth upper bound क्रम VQ26 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND26				 0x120298
/* [RW 7] Bandwidth upper bound क्रम VQ27 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND27				 0x12029c
/* [RW 7] Bandwidth upper bound क्रम VQ4 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND4				 0x120244
/* [RW 7] Bandwidth upper bound क्रम VQ5 पढ़ो requests */
#घोषणा PXP2_REG_RQ_BW_RD_UBOUND5				 0x120248
/* [RW 10] Bandwidth addition to VQ29 ग_लिखो requests */
#घोषणा PXP2_REG_RQ_BW_WR_ADD29 				 0x12022c
/* [RW 10] Bandwidth addition to VQ30 ग_लिखो requests */
#घोषणा PXP2_REG_RQ_BW_WR_ADD30 				 0x120230
/* [RW 10] Bandwidth Typical L क्रम VQ29 Write requests */
#घोषणा PXP2_REG_RQ_BW_WR_L29					 0x12031c
/* [RW 10] Bandwidth Typical L क्रम VQ30 Write requests */
#घोषणा PXP2_REG_RQ_BW_WR_L30					 0x120320
/* [RW 7] Bandwidth upper bound क्रम VQ29 */
#घोषणा PXP2_REG_RQ_BW_WR_UBOUND29				 0x1202a4
/* [RW 7] Bandwidth upper bound क्रम VQ30 */
#घोषणा PXP2_REG_RQ_BW_WR_UBOUND30				 0x1202a8
/* [RW 18] बाह्यal first_mem_addr field in L2P table क्रम CDU module port 0 */
#घोषणा PXP2_REG_RQ_CDU0_EFIRST_MEM_ADDR			 0x120008
/* [RW 2] Endian mode क्रम cdu */
#घोषणा PXP2_REG_RQ_CDU_ENDIAN_M				 0x1201a0
#घोषणा PXP2_REG_RQ_CDU_FIRST_ILT				 0x12061c
#घोषणा PXP2_REG_RQ_CDU_LAST_ILT				 0x120620
/* [RW 3] page size in L2P table क्रम CDU module; -4k; -8k; -16k; -32k; -64k;
   -128k */
#घोषणा PXP2_REG_RQ_CDU_P_SIZE					 0x120018
/* [R 1] 1' indicates that the requester has finished its पूर्णांकernal
   configuration */
#घोषणा PXP2_REG_RQ_CFG_DONE					 0x1201b4
/* [RW 2] Endian mode क्रम debug */
#घोषणा PXP2_REG_RQ_DBG_ENDIAN_M				 0x1201a4
/* [RW 1] When '1'; requests will enter input buffers but wont get out
   towards the glue */
#घोषणा PXP2_REG_RQ_DISABLE_INPUTS				 0x120330
/* [RW 4] Determines alignment of ग_लिखो SRs when a request is split पूर्णांकo
 * several SRs. 0 - 8B aligned. 1 - 64B aligned. 2 - 128B aligned. 3 - 256B
 * aligned. 4 - 512B aligned. */
#घोषणा PXP2_REG_RQ_DRAM_ALIGN					 0x1205b0
/* [RW 4] Determines alignment of पढ़ो SRs when a request is split पूर्णांकo
 * several SRs. 0 - 8B aligned. 1 - 64B aligned. 2 - 128B aligned. 3 - 256B
 * aligned. 4 - 512B aligned. */
#घोषणा PXP2_REG_RQ_DRAM_ALIGN_RD				 0x12092c
/* [RW 1] when set the new alignment method (E2) will be applied; when reset
 * the original alignment method (E1 E1H) will be applied */
#घोषणा PXP2_REG_RQ_DRAM_ALIGN_SEL				 0x120930
/* [RW 1] If 1 ILT failiue will not result in ELT access; An पूर्णांकerrupt will
   be निश्चितed */
#घोषणा PXP2_REG_RQ_ELT_DISABLE 				 0x12066c
/* [RW 2] Endian mode क्रम hc */
#घोषणा PXP2_REG_RQ_HC_ENDIAN_M 				 0x1201a8
/* [RW 1] when '0' ILT logic will work as in A0; otherwise B0; क्रम back
   compatibility needs; Note that dअगरferent रेजिस्टरs are used per mode */
#घोषणा PXP2_REG_RQ_ILT_MODE					 0x1205b4
/* [WB 53] Onchip address table */
#घोषणा PXP2_REG_RQ_ONCHIP_AT					 0x122000
/* [WB 53] Onchip address table - B0 */
#घोषणा PXP2_REG_RQ_ONCHIP_AT_B0				 0x128000
/* [RW 13] Pending पढ़ो limiter threshold; in Dwords */
#घोषणा PXP2_REG_RQ_PDR_LIMIT					 0x12033c
/* [RW 2] Endian mode क्रम qm */
#घोषणा PXP2_REG_RQ_QM_ENDIAN_M 				 0x120194
#घोषणा PXP2_REG_RQ_QM_FIRST_ILT				 0x120634
#घोषणा PXP2_REG_RQ_QM_LAST_ILT 				 0x120638
/* [RW 3] page size in L2P table क्रम QM module; -4k; -8k; -16k; -32k; -64k;
   -128k */
#घोषणा PXP2_REG_RQ_QM_P_SIZE					 0x120050
/* [RW 1] 1' indicates that the RBC has finished configuring the PSWRQ */
#घोषणा PXP2_REG_RQ_RBC_DONE					 0x1201b0
/* [RW 3] Max burst size filed क्रम पढ़ो requests port 0; 000 - 128B;
   001:256B; 010: 512B; 11:1K:100:2K; 01:4K */
#घोषणा PXP2_REG_RQ_RD_MBS0					 0x120160
/* [RW 3] Max burst size filed क्रम पढ़ो requests port 1; 000 - 128B;
   001:256B; 010: 512B; 11:1K:100:2K; 01:4K */
#घोषणा PXP2_REG_RQ_RD_MBS1					 0x120168
/* [RW 2] Endian mode क्रम src */
#घोषणा PXP2_REG_RQ_SRC_ENDIAN_M				 0x12019c
#घोषणा PXP2_REG_RQ_SRC_FIRST_ILT				 0x12063c
#घोषणा PXP2_REG_RQ_SRC_LAST_ILT				 0x120640
/* [RW 3] page size in L2P table क्रम SRC module; -4k; -8k; -16k; -32k; -64k;
   -128k */
#घोषणा PXP2_REG_RQ_SRC_P_SIZE					 0x12006c
/* [RW 2] Endian mode क्रम पंचांग */
#घोषणा PXP2_REG_RQ_TM_ENDIAN_M 				 0x120198
#घोषणा PXP2_REG_RQ_TM_FIRST_ILT				 0x120644
#घोषणा PXP2_REG_RQ_TM_LAST_ILT 				 0x120648
/* [RW 3] page size in L2P table क्रम TM module; -4k; -8k; -16k; -32k; -64k;
   -128k */
#घोषणा PXP2_REG_RQ_TM_P_SIZE					 0x120034
/* [R 5] Number of entries in the ufअगरo; his fअगरo has l2p completions */
#घोषणा PXP2_REG_RQ_UFIFO_NUM_OF_ENTRY				 0x12080c
/* [RW 18] बाह्यal first_mem_addr field in L2P table क्रम USDM module port 0 */
#घोषणा PXP2_REG_RQ_USDM0_EFIRST_MEM_ADDR			 0x120094
/* [R 8] Number of entries occupied by vq 0 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ0_ENTRY_CNT				 0x120810
/* [R 8] Number of entries occupied by vq 10 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ10_ENTRY_CNT				 0x120818
/* [R 8] Number of entries occupied by vq 11 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ11_ENTRY_CNT				 0x120820
/* [R 8] Number of entries occupied by vq 12 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ12_ENTRY_CNT				 0x120828
/* [R 8] Number of entries occupied by vq 13 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ13_ENTRY_CNT				 0x120830
/* [R 8] Number of entries occupied by vq 14 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ14_ENTRY_CNT				 0x120838
/* [R 8] Number of entries occupied by vq 15 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ15_ENTRY_CNT				 0x120840
/* [R 8] Number of entries occupied by vq 16 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ16_ENTRY_CNT				 0x120848
/* [R 8] Number of entries occupied by vq 17 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ17_ENTRY_CNT				 0x120850
/* [R 8] Number of entries occupied by vq 18 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ18_ENTRY_CNT				 0x120858
/* [R 8] Number of entries occupied by vq 19 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ19_ENTRY_CNT				 0x120860
/* [R 8] Number of entries occupied by vq 1 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ1_ENTRY_CNT				 0x120868
/* [R 8] Number of entries occupied by vq 20 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ20_ENTRY_CNT				 0x120870
/* [R 8] Number of entries occupied by vq 21 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ21_ENTRY_CNT				 0x120878
/* [R 8] Number of entries occupied by vq 22 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ22_ENTRY_CNT				 0x120880
/* [R 8] Number of entries occupied by vq 23 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ23_ENTRY_CNT				 0x120888
/* [R 8] Number of entries occupied by vq 24 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ24_ENTRY_CNT				 0x120890
/* [R 8] Number of entries occupied by vq 25 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ25_ENTRY_CNT				 0x120898
/* [R 8] Number of entries occupied by vq 26 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ26_ENTRY_CNT				 0x1208a0
/* [R 8] Number of entries occupied by vq 27 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ27_ENTRY_CNT				 0x1208a8
/* [R 8] Number of entries occupied by vq 28 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ28_ENTRY_CNT				 0x1208b0
/* [R 8] Number of entries occupied by vq 29 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ29_ENTRY_CNT				 0x1208b8
/* [R 8] Number of entries occupied by vq 2 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ2_ENTRY_CNT				 0x1208c0
/* [R 8] Number of entries occupied by vq 30 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ30_ENTRY_CNT				 0x1208c8
/* [R 8] Number of entries occupied by vq 31 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ31_ENTRY_CNT				 0x1208d0
/* [R 8] Number of entries occupied by vq 3 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ3_ENTRY_CNT				 0x1208d8
/* [R 8] Number of entries occupied by vq 4 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ4_ENTRY_CNT				 0x1208e0
/* [R 8] Number of entries occupied by vq 5 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ5_ENTRY_CNT				 0x1208e8
/* [R 8] Number of entries occupied by vq 6 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ6_ENTRY_CNT				 0x1208f0
/* [R 8] Number of entries occupied by vq 7 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ7_ENTRY_CNT				 0x1208f8
/* [R 8] Number of entries occupied by vq 8 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ8_ENTRY_CNT				 0x120900
/* [R 8] Number of entries occupied by vq 9 in pswrq memory */
#घोषणा PXP2_REG_RQ_VQ9_ENTRY_CNT				 0x120908
/* [RW 3] Max burst size filed क्रम ग_लिखो requests port 0; 000 - 128B;
   001:256B; 010: 512B; */
#घोषणा PXP2_REG_RQ_WR_MBS0					 0x12015c
/* [RW 3] Max burst size filed क्रम ग_लिखो requests port 1; 000 - 128B;
   001:256B; 010: 512B; */
#घोषणा PXP2_REG_RQ_WR_MBS1					 0x120164
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_CDU_MPS					 0x1205f0
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_CSDM_MPS					 0x1205d0
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_DBG_MPS					 0x1205e8
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_DMAE_MPS					 0x1205ec
/* [RW 10] अगर Number of entries in dmae fअगरo will be higher than this
   threshold then has_payload indication will be निश्चितed; the शेष value
   should be equal to &gt;  ग_लिखो MBS size! */
#घोषणा PXP2_REG_WR_DMAE_TH					 0x120368
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_HC_MPS					 0x1205c8
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_QM_MPS					 0x1205dc
/* [RW 1] 0 - working in A0 mode;  - working in B0 mode */
#घोषणा PXP2_REG_WR_REV_MODE					 0x120670
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_SRC_MPS					 0x1205e4
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_TM_MPS					 0x1205e0
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_TSDM_MPS					 0x1205d4
/* [RW 10] अगर Number of entries in usdmdp fअगरo will be higher than this
   threshold then has_payload indication will be निश्चितed; the शेष value
   should be equal to &gt;  ग_लिखो MBS size! */
#घोषणा PXP2_REG_WR_USDMDP_TH					 0x120348
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_USDM_MPS					 0x1205cc
/* [RW 2] 0 - 128B;  - 256B;  - 512B;  - 1024B; when the payload in the
   buffer reaches this number has_payload will be निश्चितed */
#घोषणा PXP2_REG_WR_XSDM_MPS					 0x1205d8
/* [R 1] debug only: Indication अगर PSWHST arbiter is idle */
#घोषणा PXP_REG_HST_ARB_IS_IDLE 				 0x103004
/* [R 8] debug only: A bit mask क्रम all PSWHST arbiter clients. '1' means
   this client is रुकोing क्रम the arbiter. */
#घोषणा PXP_REG_HST_CLIENTS_WAITING_TO_ARB			 0x103008
/* [RW 1] When 1; करोorbells are discarded and not passed to करोorbell queue
   block. Should be used क्रम बंद the gates. */
#घोषणा PXP_REG_HST_DISCARD_DOORBELLS				 0x1030a4
/* [R 1] debug only: '1' means this PSWHST is discarding करोorbells. This bit
   should update according to 'hst_discard_doorbells' रेजिस्टर when the state
   machine is idle */
#घोषणा PXP_REG_HST_DISCARD_DOORBELLS_STATUS			 0x1030a0
/* [RW 1] When 1; new पूर्णांकernal ग_लिखोs arriving to the block are discarded.
   Should be used क्रम बंद the gates. */
#घोषणा PXP_REG_HST_DISCARD_INTERNAL_WRITES			 0x1030a8
/* [R 6] debug only: A bit mask क्रम all PSWHST पूर्णांकernal ग_लिखो clients. '1'
   means this PSWHST is discarding inमाला_दो from this client. Each bit should
   update according to 'hst_discard_internal_writes' रेजिस्टर when the state
   machine is idle. */
#घोषणा PXP_REG_HST_DISCARD_INTERNAL_WRITES_STATUS		 0x10309c
/* [WB 160] Used क्रम initialization of the inbound पूर्णांकerrupts memory */
#घोषणा PXP_REG_HST_INBOUND_INT 				 0x103800
/* [RW 7] Indirect access to the permission table. The fields are : अणुValid;
 * VFID[5:0]पूर्ण
 */
#घोषणा PXP_REG_HST_ZONE_PERMISSION_TABLE			 0x103400
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PXP_REG_PXP_INT_MASK_0					 0x103074
#घोषणा PXP_REG_PXP_INT_MASK_1					 0x103084
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा PXP_REG_PXP_INT_STS_0					 0x103068
#घोषणा PXP_REG_PXP_INT_STS_1					 0x103078
/* [RC 32] Interrupt रेजिस्टर #0 पढ़ो clear */
#घोषणा PXP_REG_PXP_INT_STS_CLR_0				 0x10306c
#घोषणा PXP_REG_PXP_INT_STS_CLR_1				 0x10307c
/* [RW 27] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा PXP_REG_PXP_PRTY_MASK					 0x103094
/* [R 26] Parity रेजिस्टर #0 पढ़ो */
#घोषणा PXP_REG_PXP_PRTY_STS					 0x103088
/* [RC 27] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा PXP_REG_PXP_PRTY_STS_CLR				 0x10308c
/* [RW 4] The activity counter initial increment value sent in the load
   request */
#घोषणा QM_REG_ACTCTRINITVAL_0					 0x168040
#घोषणा QM_REG_ACTCTRINITVAL_1					 0x168044
#घोषणा QM_REG_ACTCTRINITVAL_2					 0x168048
#घोषणा QM_REG_ACTCTRINITVAL_3					 0x16804c
/* [RW 32] The base logical address (in bytes) of each physical queue. The
   index I represents the physical queue number. The 12 lsbs are ignore and
   considered zero so practically there are only 20 bits in this रेजिस्टर;
   queues 63-0 */
#घोषणा QM_REG_BASEADDR 					 0x168900
/* [RW 32] The base logical address (in bytes) of each physical queue. The
   index I represents the physical queue number. The 12 lsbs are ignore and
   considered zero so practically there are only 20 bits in this रेजिस्टर;
   queues 127-64 */
#घोषणा QM_REG_BASEADDR_EXT_A					 0x16e100
/* [RW 16] The byte credit cost क्रम each task. This value is क्रम both ports */
#घोषणा QM_REG_BYTECRDCOST					 0x168234
/* [RW 16] The initial byte credit value क्रम both ports. */
#घोषणा QM_REG_BYTECRDINITVAL					 0x168238
/* [RW 32] A bit per physical queue. If the bit is cleared then the physical
   queue uses port 0 अन्यथा it uses port 1; queues 31-0 */
#घोषणा QM_REG_BYTECRDPORT_LSB					 0x168228
/* [RW 32] A bit per physical queue. If the bit is cleared then the physical
   queue uses port 0 अन्यथा it uses port 1; queues 95-64 */
#घोषणा QM_REG_BYTECRDPORT_LSB_EXT_A				 0x16e520
/* [RW 32] A bit per physical queue. If the bit is cleared then the physical
   queue uses port 0 अन्यथा it uses port 1; queues 63-32 */
#घोषणा QM_REG_BYTECRDPORT_MSB					 0x168224
/* [RW 32] A bit per physical queue. If the bit is cleared then the physical
   queue uses port 0 अन्यथा it uses port 1; queues 127-96 */
#घोषणा QM_REG_BYTECRDPORT_MSB_EXT_A				 0x16e51c
/* [RW 16] The byte credit value that अगर above the QM is considered almost
   full */
#घोषणा QM_REG_BYTECREDITAFULLTHR				 0x168094
/* [RW 4] The initial credit क्रम पूर्णांकerface */
#घोषणा QM_REG_CMINITCRD_0					 0x1680cc
#घोषणा QM_REG_BYTECRDCMDQ_0					 0x16e6e8
#घोषणा QM_REG_CMINITCRD_1					 0x1680d0
#घोषणा QM_REG_CMINITCRD_2					 0x1680d4
#घोषणा QM_REG_CMINITCRD_3					 0x1680d8
#घोषणा QM_REG_CMINITCRD_4					 0x1680dc
#घोषणा QM_REG_CMINITCRD_5					 0x1680e0
#घोषणा QM_REG_CMINITCRD_6					 0x1680e4
#घोषणा QM_REG_CMINITCRD_7					 0x1680e8
/* [RW 8] A mask bit per CM पूर्णांकerface. If this bit is 0 then this पूर्णांकerface
   is masked */
#घोषणा QM_REG_CMINTEN						 0x1680ec
/* [RW 12] A bit vector which indicates which one of the queues are tied to
   पूर्णांकerface 0 */
#घोषणा QM_REG_CMINTVOQMASK_0					 0x1681f4
#घोषणा QM_REG_CMINTVOQMASK_1					 0x1681f8
#घोषणा QM_REG_CMINTVOQMASK_2					 0x1681fc
#घोषणा QM_REG_CMINTVOQMASK_3					 0x168200
#घोषणा QM_REG_CMINTVOQMASK_4					 0x168204
#घोषणा QM_REG_CMINTVOQMASK_5					 0x168208
#घोषणा QM_REG_CMINTVOQMASK_6					 0x16820c
#घोषणा QM_REG_CMINTVOQMASK_7					 0x168210
/* [RW 20] The number of connections भागided by 16 which dictates the size
   of each queue which beदीर्घs to even function number. */
#घोषणा QM_REG_CONNNUM_0					 0x168020
/* [R 6] Keep the fill level of the fअगरo from ग_लिखो client 4 */
#घोषणा QM_REG_CQM_WRC_FIFOLVL					 0x168018
/* [RW 8] The context regions sent in the CFC load request */
#घोषणा QM_REG_CTXREG_0 					 0x168030
#घोषणा QM_REG_CTXREG_1 					 0x168034
#घोषणा QM_REG_CTXREG_2 					 0x168038
#घोषणा QM_REG_CTXREG_3 					 0x16803c
/* [RW 12] The VOQ mask used to select the VOQs which needs to be full क्रम
   bypass enable */
#घोषणा QM_REG_ENBYPVOQMASK					 0x16823c
/* [RW 32] A bit mask per each physical queue. If a bit is set then the
   physical queue uses the byte credit; queues 31-0 */
#घोषणा QM_REG_ENBYTECRD_LSB					 0x168220
/* [RW 32] A bit mask per each physical queue. If a bit is set then the
   physical queue uses the byte credit; queues 95-64 */
#घोषणा QM_REG_ENBYTECRD_LSB_EXT_A				 0x16e518
/* [RW 32] A bit mask per each physical queue. If a bit is set then the
   physical queue uses the byte credit; queues 63-32 */
#घोषणा QM_REG_ENBYTECRD_MSB					 0x16821c
/* [RW 32] A bit mask per each physical queue. If a bit is set then the
   physical queue uses the byte credit; queues 127-96 */
#घोषणा QM_REG_ENBYTECRD_MSB_EXT_A				 0x16e514
/* [RW 4] If cleared then the secondary पूर्णांकerface will not be served by the
   RR arbiter */
#घोषणा QM_REG_ENSEC						 0x1680f0
/* [RW 32] NA */
#घोषणा QM_REG_FUNCNUMSEL_LSB					 0x168230
/* [RW 32] NA */
#घोषणा QM_REG_FUNCNUMSEL_MSB					 0x16822c
/* [RW 32] A mask रेजिस्टर to mask the Almost empty संकेतs which will not
   be use क्रम the almost empty indication to the HW block; queues 31:0 */
#घोषणा QM_REG_HWAEMPTYMASK_LSB 				 0x168218
/* [RW 32] A mask रेजिस्टर to mask the Almost empty संकेतs which will not
   be use क्रम the almost empty indication to the HW block; queues 95-64 */
#घोषणा QM_REG_HWAEMPTYMASK_LSB_EXT_A				 0x16e510
/* [RW 32] A mask रेजिस्टर to mask the Almost empty संकेतs which will not
   be use क्रम the almost empty indication to the HW block; queues 63:32 */
#घोषणा QM_REG_HWAEMPTYMASK_MSB 				 0x168214
/* [RW 32] A mask रेजिस्टर to mask the Almost empty संकेतs which will not
   be use क्रम the almost empty indication to the HW block; queues 127-96 */
#घोषणा QM_REG_HWAEMPTYMASK_MSB_EXT_A				 0x16e50c
/* [RW 4] The number of outstanding request to CFC */
#घोषणा QM_REG_OUTLDREQ 					 0x168804
/* [RC 1] A flag to indicate that overflow error occurred in one of the
   queues. */
#घोषणा QM_REG_OVFERROR 					 0x16805c
/* [RC 7] the Q where the overflow occurs */
#घोषणा QM_REG_OVFQNUM						 0x168058
/* [R 16] Pause state क्रम physical queues 15-0 */
#घोषणा QM_REG_PAUSESTATE0					 0x168410
/* [R 16] Pause state क्रम physical queues 31-16 */
#घोषणा QM_REG_PAUSESTATE1					 0x168414
/* [R 16] Pause state क्रम physical queues 47-32 */
#घोषणा QM_REG_PAUSESTATE2					 0x16e684
/* [R 16] Pause state क्रम physical queues 63-48 */
#घोषणा QM_REG_PAUSESTATE3					 0x16e688
/* [R 16] Pause state क्रम physical queues 79-64 */
#घोषणा QM_REG_PAUSESTATE4					 0x16e68c
/* [R 16] Pause state क्रम physical queues 95-80 */
#घोषणा QM_REG_PAUSESTATE5					 0x16e690
/* [R 16] Pause state क्रम physical queues 111-96 */
#घोषणा QM_REG_PAUSESTATE6					 0x16e694
/* [R 16] Pause state क्रम physical queues 127-112 */
#घोषणा QM_REG_PAUSESTATE7					 0x16e698
/* [RW 2] The PCI attributes field used in the PCI request. */
#घोषणा QM_REG_PCIREQAT 					 0x168054
#घोषणा QM_REG_PF_EN						 0x16e70c
/* [R 24] The number of tasks stored in the QM क्रम the PF. only even
 * functions are valid in E2 (odd I रेजिस्टरs will be hard wired to 0) */
#घोषणा QM_REG_PF_USG_CNT_0					 0x16e040
/* [R 16] NOT USED */
#घोषणा QM_REG_PORT0BYTECRD					 0x168300
/* [R 16] The byte credit of port 1 */
#घोषणा QM_REG_PORT1BYTECRD					 0x168304
/* [RW 3] pci function number of queues 15-0 */
#घोषणा QM_REG_PQ2PCIFUNC_0					 0x16e6bc
#घोषणा QM_REG_PQ2PCIFUNC_1					 0x16e6c0
#घोषणा QM_REG_PQ2PCIFUNC_2					 0x16e6c4
#घोषणा QM_REG_PQ2PCIFUNC_3					 0x16e6c8
#घोषणा QM_REG_PQ2PCIFUNC_4					 0x16e6cc
#घोषणा QM_REG_PQ2PCIFUNC_5					 0x16e6d0
#घोषणा QM_REG_PQ2PCIFUNC_6					 0x16e6d4
#घोषणा QM_REG_PQ2PCIFUNC_7					 0x16e6d8
/* [WB 54] Poपूर्णांकer Table Memory क्रम queues 63-0; The mapping is as follow:
   ptrtbl[53:30] पढ़ो poपूर्णांकer; ptrtbl[29:6] ग_लिखो poपूर्णांकer; ptrtbl[5:4] पढ़ो
   bank0; ptrtbl[3:2] पढ़ो bank 1; ptrtbl[1:0] ग_लिखो bank; */
#घोषणा QM_REG_PTRTBL						 0x168a00
/* [WB 54] Poपूर्णांकer Table Memory क्रम queues 127-64; The mapping is as follow:
   ptrtbl[53:30] पढ़ो poपूर्णांकer; ptrtbl[29:6] ग_लिखो poपूर्णांकer; ptrtbl[5:4] पढ़ो
   bank0; ptrtbl[3:2] पढ़ो bank 1; ptrtbl[1:0] ग_लिखो bank; */
#घोषणा QM_REG_PTRTBL_EXT_A					 0x16e200
/* [RW 2] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा QM_REG_QM_INT_MASK					 0x168444
/* [R 2] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा QM_REG_QM_INT_STS					 0x168438
/* [RW 12] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा QM_REG_QM_PRTY_MASK					 0x168454
/* [R 12] Parity रेजिस्टर #0 पढ़ो */
#घोषणा QM_REG_QM_PRTY_STS					 0x168448
/* [RC 12] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा QM_REG_QM_PRTY_STS_CLR					 0x16844c
/* [R 32] Current queues in pipeline: Queues from 32 to 63 */
#घोषणा QM_REG_QSTATUS_HIGH					 0x16802c
/* [R 32] Current queues in pipeline: Queues from 96 to 127 */
#घोषणा QM_REG_QSTATUS_HIGH_EXT_A				 0x16e408
/* [R 32] Current queues in pipeline: Queues from 0 to 31 */
#घोषणा QM_REG_QSTATUS_LOW					 0x168028
/* [R 32] Current queues in pipeline: Queues from 64 to 95 */
#घोषणा QM_REG_QSTATUS_LOW_EXT_A				 0x16e404
/* [R 24] The number of tasks queued क्रम each queue; queues 63-0 */
#घोषणा QM_REG_QTASKCTR_0					 0x168308
/* [R 24] The number of tasks queued क्रम each queue; queues 127-64 */
#घोषणा QM_REG_QTASKCTR_EXT_A_0 				 0x16e584
/* [RW 4] Queue tied to VOQ */
#घोषणा QM_REG_QVOQIDX_0					 0x1680f4
#घोषणा QM_REG_QVOQIDX_10					 0x16811c
#घोषणा QM_REG_QVOQIDX_100					 0x16e49c
#घोषणा QM_REG_QVOQIDX_101					 0x16e4a0
#घोषणा QM_REG_QVOQIDX_102					 0x16e4a4
#घोषणा QM_REG_QVOQIDX_103					 0x16e4a8
#घोषणा QM_REG_QVOQIDX_104					 0x16e4ac
#घोषणा QM_REG_QVOQIDX_105					 0x16e4b0
#घोषणा QM_REG_QVOQIDX_106					 0x16e4b4
#घोषणा QM_REG_QVOQIDX_107					 0x16e4b8
#घोषणा QM_REG_QVOQIDX_108					 0x16e4bc
#घोषणा QM_REG_QVOQIDX_109					 0x16e4c0
#घोषणा QM_REG_QVOQIDX_11					 0x168120
#घोषणा QM_REG_QVOQIDX_110					 0x16e4c4
#घोषणा QM_REG_QVOQIDX_111					 0x16e4c8
#घोषणा QM_REG_QVOQIDX_112					 0x16e4cc
#घोषणा QM_REG_QVOQIDX_113					 0x16e4d0
#घोषणा QM_REG_QVOQIDX_114					 0x16e4d4
#घोषणा QM_REG_QVOQIDX_115					 0x16e4d8
#घोषणा QM_REG_QVOQIDX_116					 0x16e4dc
#घोषणा QM_REG_QVOQIDX_117					 0x16e4e0
#घोषणा QM_REG_QVOQIDX_118					 0x16e4e4
#घोषणा QM_REG_QVOQIDX_119					 0x16e4e8
#घोषणा QM_REG_QVOQIDX_12					 0x168124
#घोषणा QM_REG_QVOQIDX_120					 0x16e4ec
#घोषणा QM_REG_QVOQIDX_121					 0x16e4f0
#घोषणा QM_REG_QVOQIDX_122					 0x16e4f4
#घोषणा QM_REG_QVOQIDX_123					 0x16e4f8
#घोषणा QM_REG_QVOQIDX_124					 0x16e4fc
#घोषणा QM_REG_QVOQIDX_125					 0x16e500
#घोषणा QM_REG_QVOQIDX_126					 0x16e504
#घोषणा QM_REG_QVOQIDX_127					 0x16e508
#घोषणा QM_REG_QVOQIDX_13					 0x168128
#घोषणा QM_REG_QVOQIDX_14					 0x16812c
#घोषणा QM_REG_QVOQIDX_15					 0x168130
#घोषणा QM_REG_QVOQIDX_16					 0x168134
#घोषणा QM_REG_QVOQIDX_17					 0x168138
#घोषणा QM_REG_QVOQIDX_21					 0x168148
#घोषणा QM_REG_QVOQIDX_22					 0x16814c
#घोषणा QM_REG_QVOQIDX_23					 0x168150
#घोषणा QM_REG_QVOQIDX_24					 0x168154
#घोषणा QM_REG_QVOQIDX_25					 0x168158
#घोषणा QM_REG_QVOQIDX_26					 0x16815c
#घोषणा QM_REG_QVOQIDX_27					 0x168160
#घोषणा QM_REG_QVOQIDX_28					 0x168164
#घोषणा QM_REG_QVOQIDX_29					 0x168168
#घोषणा QM_REG_QVOQIDX_30					 0x16816c
#घोषणा QM_REG_QVOQIDX_31					 0x168170
#घोषणा QM_REG_QVOQIDX_32					 0x168174
#घोषणा QM_REG_QVOQIDX_33					 0x168178
#घोषणा QM_REG_QVOQIDX_34					 0x16817c
#घोषणा QM_REG_QVOQIDX_35					 0x168180
#घोषणा QM_REG_QVOQIDX_36					 0x168184
#घोषणा QM_REG_QVOQIDX_37					 0x168188
#घोषणा QM_REG_QVOQIDX_38					 0x16818c
#घोषणा QM_REG_QVOQIDX_39					 0x168190
#घोषणा QM_REG_QVOQIDX_40					 0x168194
#घोषणा QM_REG_QVOQIDX_41					 0x168198
#घोषणा QM_REG_QVOQIDX_42					 0x16819c
#घोषणा QM_REG_QVOQIDX_43					 0x1681a0
#घोषणा QM_REG_QVOQIDX_44					 0x1681a4
#घोषणा QM_REG_QVOQIDX_45					 0x1681a8
#घोषणा QM_REG_QVOQIDX_46					 0x1681ac
#घोषणा QM_REG_QVOQIDX_47					 0x1681b0
#घोषणा QM_REG_QVOQIDX_48					 0x1681b4
#घोषणा QM_REG_QVOQIDX_49					 0x1681b8
#घोषणा QM_REG_QVOQIDX_5					 0x168108
#घोषणा QM_REG_QVOQIDX_50					 0x1681bc
#घोषणा QM_REG_QVOQIDX_51					 0x1681c0
#घोषणा QM_REG_QVOQIDX_52					 0x1681c4
#घोषणा QM_REG_QVOQIDX_53					 0x1681c8
#घोषणा QM_REG_QVOQIDX_54					 0x1681cc
#घोषणा QM_REG_QVOQIDX_55					 0x1681d0
#घोषणा QM_REG_QVOQIDX_56					 0x1681d4
#घोषणा QM_REG_QVOQIDX_57					 0x1681d8
#घोषणा QM_REG_QVOQIDX_58					 0x1681dc
#घोषणा QM_REG_QVOQIDX_59					 0x1681e0
#घोषणा QM_REG_QVOQIDX_6					 0x16810c
#घोषणा QM_REG_QVOQIDX_60					 0x1681e4
#घोषणा QM_REG_QVOQIDX_61					 0x1681e8
#घोषणा QM_REG_QVOQIDX_62					 0x1681ec
#घोषणा QM_REG_QVOQIDX_63					 0x1681f0
#घोषणा QM_REG_QVOQIDX_64					 0x16e40c
#घोषणा QM_REG_QVOQIDX_65					 0x16e410
#घोषणा QM_REG_QVOQIDX_69					 0x16e420
#घोषणा QM_REG_QVOQIDX_7					 0x168110
#घोषणा QM_REG_QVOQIDX_70					 0x16e424
#घोषणा QM_REG_QVOQIDX_71					 0x16e428
#घोषणा QM_REG_QVOQIDX_72					 0x16e42c
#घोषणा QM_REG_QVOQIDX_73					 0x16e430
#घोषणा QM_REG_QVOQIDX_74					 0x16e434
#घोषणा QM_REG_QVOQIDX_75					 0x16e438
#घोषणा QM_REG_QVOQIDX_76					 0x16e43c
#घोषणा QM_REG_QVOQIDX_77					 0x16e440
#घोषणा QM_REG_QVOQIDX_78					 0x16e444
#घोषणा QM_REG_QVOQIDX_79					 0x16e448
#घोषणा QM_REG_QVOQIDX_8					 0x168114
#घोषणा QM_REG_QVOQIDX_80					 0x16e44c
#घोषणा QM_REG_QVOQIDX_81					 0x16e450
#घोषणा QM_REG_QVOQIDX_85					 0x16e460
#घोषणा QM_REG_QVOQIDX_86					 0x16e464
#घोषणा QM_REG_QVOQIDX_87					 0x16e468
#घोषणा QM_REG_QVOQIDX_88					 0x16e46c
#घोषणा QM_REG_QVOQIDX_89					 0x16e470
#घोषणा QM_REG_QVOQIDX_9					 0x168118
#घोषणा QM_REG_QVOQIDX_90					 0x16e474
#घोषणा QM_REG_QVOQIDX_91					 0x16e478
#घोषणा QM_REG_QVOQIDX_92					 0x16e47c
#घोषणा QM_REG_QVOQIDX_93					 0x16e480
#घोषणा QM_REG_QVOQIDX_94					 0x16e484
#घोषणा QM_REG_QVOQIDX_95					 0x16e488
#घोषणा QM_REG_QVOQIDX_96					 0x16e48c
#घोषणा QM_REG_QVOQIDX_97					 0x16e490
#घोषणा QM_REG_QVOQIDX_98					 0x16e494
#घोषणा QM_REG_QVOQIDX_99					 0x16e498
/* [RW 1] Initialization bit command */
#घोषणा QM_REG_SOFT_RESET					 0x168428
/* [RW 8] The credit cost per every task in the QM. A value per each VOQ */
#घोषणा QM_REG_TASKCRDCOST_0					 0x16809c
#घोषणा QM_REG_TASKCRDCOST_1					 0x1680a0
#घोषणा QM_REG_TASKCRDCOST_2					 0x1680a4
#घोषणा QM_REG_TASKCRDCOST_4					 0x1680ac
#घोषणा QM_REG_TASKCRDCOST_5					 0x1680b0
/* [R 6] Keep the fill level of the fअगरo from ग_लिखो client 3 */
#घोषणा QM_REG_TQM_WRC_FIFOLVL					 0x168010
/* [R 6] Keep the fill level of the fअगरo from ग_लिखो client 2 */
#घोषणा QM_REG_UQM_WRC_FIFOLVL					 0x168008
/* [RC 32] Credit update error रेजिस्टर */
#घोषणा QM_REG_VOQCRDERRREG					 0x168408
/* [R 16] The credit value क्रम each VOQ */
#घोषणा QM_REG_VOQCREDIT_0					 0x1682d0
#घोषणा QM_REG_VOQCREDIT_1					 0x1682d4
#घोषणा QM_REG_VOQCREDIT_4					 0x1682e0
/* [RW 16] The credit value that अगर above the QM is considered almost full */
#घोषणा QM_REG_VOQCREDITAFULLTHR				 0x168090
/* [RW 16] The init and maximum credit क्रम each VoQ */
#घोषणा QM_REG_VOQINITCREDIT_0					 0x168060
#घोषणा QM_REG_VOQINITCREDIT_1					 0x168064
#घोषणा QM_REG_VOQINITCREDIT_2					 0x168068
#घोषणा QM_REG_VOQINITCREDIT_4					 0x168070
#घोषणा QM_REG_VOQINITCREDIT_5					 0x168074
/* [RW 1] The port of which VOQ beदीर्घs */
#घोषणा QM_REG_VOQPORT_0					 0x1682a0
#घोषणा QM_REG_VOQPORT_1					 0x1682a4
#घोषणा QM_REG_VOQPORT_2					 0x1682a8
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_0_LSB					 0x168240
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_0_LSB_EXT_A				 0x16e524
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_0_MSB					 0x168244
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_0_MSB_EXT_A				 0x16e528
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_10_LSB					 0x168290
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_10_LSB_EXT_A				 0x16e574
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_10_MSB					 0x168294
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_10_MSB_EXT_A				 0x16e578
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_11_LSB					 0x168298
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_11_LSB_EXT_A				 0x16e57c
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_11_MSB					 0x16829c
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_11_MSB_EXT_A				 0x16e580
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_1_LSB					 0x168248
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_1_LSB_EXT_A				 0x16e52c
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_1_MSB					 0x16824c
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_1_MSB_EXT_A				 0x16e530
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_2_LSB					 0x168250
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_2_LSB_EXT_A				 0x16e534
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_2_MSB					 0x168254
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_2_MSB_EXT_A				 0x16e538
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_3_LSB					 0x168258
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_3_LSB_EXT_A				 0x16e53c
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_3_MSB_EXT_A				 0x16e540
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_4_LSB					 0x168260
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_4_LSB_EXT_A				 0x16e544
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_4_MSB					 0x168264
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_4_MSB_EXT_A				 0x16e548
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_5_LSB					 0x168268
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_5_LSB_EXT_A				 0x16e54c
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_5_MSB					 0x16826c
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_5_MSB_EXT_A				 0x16e550
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_6_LSB					 0x168270
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_6_LSB_EXT_A				 0x16e554
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_6_MSB					 0x168274
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_6_MSB_EXT_A				 0x16e558
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_7_LSB					 0x168278
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_7_LSB_EXT_A				 0x16e55c
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_7_MSB					 0x16827c
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_7_MSB_EXT_A				 0x16e560
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_8_LSB					 0x168280
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_8_LSB_EXT_A				 0x16e564
/* [RW 32] The physical queue number associated with each VOQ; queues 63-32 */
#घोषणा QM_REG_VOQQMASK_8_MSB					 0x168284
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_8_MSB_EXT_A				 0x16e568
/* [RW 32] The physical queue number associated with each VOQ; queues 31-0 */
#घोषणा QM_REG_VOQQMASK_9_LSB					 0x168288
/* [RW 32] The physical queue number associated with each VOQ; queues 95-64 */
#घोषणा QM_REG_VOQQMASK_9_LSB_EXT_A				 0x16e56c
/* [RW 32] The physical queue number associated with each VOQ; queues 127-96 */
#घोषणा QM_REG_VOQQMASK_9_MSB_EXT_A				 0x16e570
/* [RW 32] Wrr weights */
#घोषणा QM_REG_WRRWEIGHTS_0					 0x16880c
#घोषणा QM_REG_WRRWEIGHTS_1					 0x168810
#घोषणा QM_REG_WRRWEIGHTS_10					 0x168814
#घोषणा QM_REG_WRRWEIGHTS_11					 0x168818
#घोषणा QM_REG_WRRWEIGHTS_12					 0x16881c
#घोषणा QM_REG_WRRWEIGHTS_13					 0x168820
#घोषणा QM_REG_WRRWEIGHTS_14					 0x168824
#घोषणा QM_REG_WRRWEIGHTS_15					 0x168828
#घोषणा QM_REG_WRRWEIGHTS_16					 0x16e000
#घोषणा QM_REG_WRRWEIGHTS_17					 0x16e004
#घोषणा QM_REG_WRRWEIGHTS_18					 0x16e008
#घोषणा QM_REG_WRRWEIGHTS_19					 0x16e00c
#घोषणा QM_REG_WRRWEIGHTS_2					 0x16882c
#घोषणा QM_REG_WRRWEIGHTS_20					 0x16e010
#घोषणा QM_REG_WRRWEIGHTS_21					 0x16e014
#घोषणा QM_REG_WRRWEIGHTS_22					 0x16e018
#घोषणा QM_REG_WRRWEIGHTS_23					 0x16e01c
#घोषणा QM_REG_WRRWEIGHTS_24					 0x16e020
#घोषणा QM_REG_WRRWEIGHTS_25					 0x16e024
#घोषणा QM_REG_WRRWEIGHTS_26					 0x16e028
#घोषणा QM_REG_WRRWEIGHTS_27					 0x16e02c
#घोषणा QM_REG_WRRWEIGHTS_28					 0x16e030
#घोषणा QM_REG_WRRWEIGHTS_29					 0x16e034
#घोषणा QM_REG_WRRWEIGHTS_3					 0x168830
#घोषणा QM_REG_WRRWEIGHTS_30					 0x16e038
#घोषणा QM_REG_WRRWEIGHTS_31					 0x16e03c
#घोषणा QM_REG_WRRWEIGHTS_4					 0x168834
#घोषणा QM_REG_WRRWEIGHTS_5					 0x168838
#घोषणा QM_REG_WRRWEIGHTS_6					 0x16883c
#घोषणा QM_REG_WRRWEIGHTS_7					 0x168840
#घोषणा QM_REG_WRRWEIGHTS_8					 0x168844
#घोषणा QM_REG_WRRWEIGHTS_9					 0x168848
/* [R 6] Keep the fill level of the fअगरo from ग_लिखो client 1 */
#घोषणा QM_REG_XQM_WRC_FIFOLVL					 0x168000
/* [W 1] reset to parity पूर्णांकerrupt */
#घोषणा SEM_FAST_REG_PARITY_RST					 0x18840
#घोषणा SRC_REG_COUNTFREE0					 0x40500
/* [RW 1] If clr the searcher is compatible to E1 A0 - support only two
   ports. If set the searcher support 8 functions. */
#घोषणा SRC_REG_E1HMF_ENABLE					 0x404cc
#घोषणा SRC_REG_FIRSTFREE0					 0x40510
#घोषणा SRC_REG_KEYRSS0_0					 0x40408
#घोषणा SRC_REG_KEYRSS0_7					 0x40424
#घोषणा SRC_REG_KEYRSS1_9					 0x40454
#घोषणा SRC_REG_KEYSEARCH_0					 0x40458
#घोषणा SRC_REG_KEYSEARCH_1					 0x4045c
#घोषणा SRC_REG_KEYSEARCH_2					 0x40460
#घोषणा SRC_REG_KEYSEARCH_3					 0x40464
#घोषणा SRC_REG_KEYSEARCH_4					 0x40468
#घोषणा SRC_REG_KEYSEARCH_5					 0x4046c
#घोषणा SRC_REG_KEYSEARCH_6					 0x40470
#घोषणा SRC_REG_KEYSEARCH_7					 0x40474
#घोषणा SRC_REG_KEYSEARCH_8					 0x40478
#घोषणा SRC_REG_KEYSEARCH_9					 0x4047c
#घोषणा SRC_REG_LASTFREE0					 0x40530
#घोषणा SRC_REG_NUMBER_HASH_BITS0				 0x40400
/* [RW 1] Reset पूर्णांकernal state machines. */
#घोषणा SRC_REG_SOFT_RST					 0x4049c
/* [R 3] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा SRC_REG_SRC_INT_STS					 0x404ac
/* [RW 3] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा SRC_REG_SRC_PRTY_MASK					 0x404c8
/* [R 3] Parity रेजिस्टर #0 पढ़ो */
#घोषणा SRC_REG_SRC_PRTY_STS					 0x404bc
/* [RC 3] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा SRC_REG_SRC_PRTY_STS_CLR				 0x404c0
/* [R 4] Used to पढ़ो the value of the XX protection CAM occupancy counter. */
#घोषणा TCM_REG_CAM_OCCUP					 0x5017c
/* [RW 1] CDU AG पढ़ो Interface enable. If 0 - the request input is
   disregarded; valid output is deनिश्चितed; all other संकेतs are treated as
   usual; अगर 1 - normal activity. */
#घोषणा TCM_REG_CDU_AG_RD_IFEN					 0x50034
/* [RW 1] CDU AG ग_लिखो Interface enable. If 0 - the request and valid input
   are disregarded; all other संकेतs are treated as usual; अगर 1 - normal
   activity. */
#घोषणा TCM_REG_CDU_AG_WR_IFEN					 0x50030
/* [RW 1] CDU STORM पढ़ो Interface enable. If 0 - the request input is
   disregarded; valid output is deनिश्चितed; all other संकेतs are treated as
   usual; अगर 1 - normal activity. */
#घोषणा TCM_REG_CDU_SM_RD_IFEN					 0x5003c
/* [RW 1] CDU STORM ग_लिखो Interface enable. If 0 - the request and valid
   input is disregarded; all other संकेतs are treated as usual; अगर 1 -
   normal activity. */
#घोषणा TCM_REG_CDU_SM_WR_IFEN					 0x50038
/* [RW 4] CFC output initial credit. Max credit available - 15.Write ग_लिखोs
   the initial credit value; पढ़ो वापसs the current value of the credit
   counter. Must be initialized to 1 at start-up. */
#घोषणा TCM_REG_CFC_INIT_CRD					 0x50204
/* [RW 3] The weight of the CP input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_CP_WEIGHT					 0x500c0
/* [RW 1] Input csem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा TCM_REG_CSEM_IFEN					 0x5002c
/* [RC 1] Message length mismatch (relative to last indication) at the In#9
   पूर्णांकerface. */
#घोषणा TCM_REG_CSEM_LENGTH_MIS 				 0x50174
/* [RW 3] The weight of the input csem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_CSEM_WEIGHT					 0x500bc
/* [RW 8] The Event ID in हाल of ErrorFlg is set in the input message. */
#घोषणा TCM_REG_ERR_EVNT_ID					 0x500a0
/* [RW 28] The CM erroneous header क्रम QM and Timers क्रमmatting. */
#घोषणा TCM_REG_ERR_TCM_HDR					 0x5009c
/* [RW 8] The Event ID क्रम Timers expiration. */
#घोषणा TCM_REG_EXPR_EVNT_ID					 0x500a4
/* [RW 8] FIC0 output initial credit. Max credit available - 255.Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 64 at start-up. */
#घोषणा TCM_REG_FIC0_INIT_CRD					 0x5020c
/* [RW 8] FIC1 output initial credit. Max credit available - 255.Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 64 at start-up. */
#घोषणा TCM_REG_FIC1_INIT_CRD					 0x50210
/* [RW 1] Arbitration between Input Arbiter groups: 0 - fair Round-Robin; 1
   - strict priority defined by ~tcm_रेजिस्टरs_gr_ag_pr.gr_ag_pr;
   ~tcm_रेजिस्टरs_gr_ld0_pr.gr_ld0_pr and
   ~tcm_रेजिस्टरs_gr_ld1_pr.gr_ld1_pr. */
#घोषणा TCM_REG_GR_ARB_TYPE					 0x50114
/* [RW 2] Load (FIC0) channel group priority. The lowest priority is 0; the
   highest priority is 3. It is supposed that the Store channel is the
   complement of the other 3 groups. */
#घोषणा TCM_REG_GR_LD0_PR					 0x5011c
/* [RW 2] Load (FIC1) channel group priority. The lowest priority is 0; the
   highest priority is 3. It is supposed that the Store channel is the
   complement of the other 3 groups. */
#घोषणा TCM_REG_GR_LD1_PR					 0x50120
/* [RW 4] The number of द्विगुन REG-pairs; loaded from the STORM context and
   sent to STORM; क्रम a specअगरic connection type. The द्विगुन REG-pairs are
   used to align to STORM context row size of 128 bits. The offset of these
   data in the STORM context is always 0. Index _i stands क्रम the connection
   type (one of 16). */
#घोषणा TCM_REG_N_SM_CTX_LD_0					 0x50050
#घोषणा TCM_REG_N_SM_CTX_LD_1					 0x50054
#घोषणा TCM_REG_N_SM_CTX_LD_2					 0x50058
#घोषणा TCM_REG_N_SM_CTX_LD_3					 0x5005c
#घोषणा TCM_REG_N_SM_CTX_LD_4					 0x50060
#घोषणा TCM_REG_N_SM_CTX_LD_5					 0x50064
/* [RW 1] Input pbf Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा TCM_REG_PBF_IFEN					 0x50024
/* [RC 1] Message length mismatch (relative to last indication) at the In#7
   पूर्णांकerface. */
#घोषणा TCM_REG_PBF_LENGTH_MIS					 0x5016c
/* [RW 3] The weight of the input pbf in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_PBF_WEIGHT					 0x500b4
#घोषणा TCM_REG_PHYS_QNUM0_0					 0x500e0
#घोषणा TCM_REG_PHYS_QNUM0_1					 0x500e4
#घोषणा TCM_REG_PHYS_QNUM1_0					 0x500e8
#घोषणा TCM_REG_PHYS_QNUM1_1					 0x500ec
#घोषणा TCM_REG_PHYS_QNUM2_0					 0x500f0
#घोषणा TCM_REG_PHYS_QNUM2_1					 0x500f4
#घोषणा TCM_REG_PHYS_QNUM3_0					 0x500f8
#घोषणा TCM_REG_PHYS_QNUM3_1					 0x500fc
/* [RW 1] Input prs Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा TCM_REG_PRS_IFEN					 0x50020
/* [RC 1] Message length mismatch (relative to last indication) at the In#6
   पूर्णांकerface. */
#घोषणा TCM_REG_PRS_LENGTH_MIS					 0x50168
/* [RW 3] The weight of the input prs in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_PRS_WEIGHT					 0x500b0
/* [RW 8] The Event ID क्रम Timers क्रमmatting in हाल of stop करोne. */
#घोषणा TCM_REG_STOP_EVNT_ID					 0x500a8
/* [RC 1] Message length mismatch (relative to last indication) at the STORM
   पूर्णांकerface. */
#घोषणा TCM_REG_STORM_LENGTH_MIS				 0x50160
/* [RW 1] STORM - CM Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा TCM_REG_STORM_TCM_IFEN					 0x50010
/* [RW 3] The weight of the STORM input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_STORM_WEIGHT					 0x500ac
/* [RW 1] CM - CFC Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा TCM_REG_TCM_CFC_IFEN					 0x50040
/* [RW 11] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा TCM_REG_TCM_INT_MASK					 0x501dc
/* [R 11] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा TCM_REG_TCM_INT_STS					 0x501d0
/* [RW 27] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा TCM_REG_TCM_PRTY_MASK					 0x501ec
/* [R 27] Parity रेजिस्टर #0 पढ़ो */
#घोषणा TCM_REG_TCM_PRTY_STS					 0x501e0
/* [RC 27] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा TCM_REG_TCM_PRTY_STS_CLR				 0x501e4
/* [RW 3] The size of AG context region 0 in REG-pairs. Designates the MS
   REG-pair number (e.g. अगर region 0 is 6 REG-pairs; the value should be 5).
   Is used to determine the number of the AG context REG-pairs written back;
   when the input message Reg1WbFlg isn't set. */
#घोषणा TCM_REG_TCM_REG0_SZ					 0x500d8
/* [RW 1] CM - STORM 0 Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा TCM_REG_TCM_STORM0_IFEN 				 0x50004
/* [RW 1] CM - STORM 1 Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा TCM_REG_TCM_STORM1_IFEN 				 0x50008
/* [RW 1] CM - QM Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा TCM_REG_TCM_TQM_IFEN					 0x5000c
/* [RW 1] If set the Q index; received from the QM is inserted to event ID. */
#घोषणा TCM_REG_TCM_TQM_USE_Q					 0x500d4
/* [RW 28] The CM header क्रम Timers expiration command. */
#घोषणा TCM_REG_TM_TCM_HDR					 0x50098
/* [RW 1] Timers - CM Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा TCM_REG_TM_TCM_IFEN					 0x5001c
/* [RW 3] The weight of the Timers input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_TM_WEIGHT					 0x500d0
/* [RW 6] QM output initial credit. Max credit available - 32.Write ग_लिखोs
   the initial credit value; पढ़ो वापसs the current value of the credit
   counter. Must be initialized to 32 at start-up. */
#घोषणा TCM_REG_TQM_INIT_CRD					 0x5021c
/* [RW 3] The weight of the QM (primary) input in the WRR mechanism. 0
   stands क्रम weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_TQM_P_WEIGHT					 0x500c8
/* [RW 3] The weight of the QM (secondary) input in the WRR mechanism. 0
   stands क्रम weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_TQM_S_WEIGHT					 0x500cc
/* [RW 28] The CM header value क्रम QM request (primary). */
#घोषणा TCM_REG_TQM_TCM_HDR_P					 0x50090
/* [RW 28] The CM header value क्रम QM request (secondary). */
#घोषणा TCM_REG_TQM_TCM_HDR_S					 0x50094
/* [RW 1] QM - CM Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा TCM_REG_TQM_TCM_IFEN					 0x50014
/* [RW 1] Input SDM Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा TCM_REG_TSDM_IFEN					 0x50018
/* [RC 1] Message length mismatch (relative to last indication) at the SDM
   पूर्णांकerface. */
#घोषणा TCM_REG_TSDM_LENGTH_MIS 				 0x50164
/* [RW 3] The weight of the SDM input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_TSDM_WEIGHT					 0x500c4
/* [RW 1] Input usem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा TCM_REG_USEM_IFEN					 0x50028
/* [RC 1] Message length mismatch (relative to last indication) at the In#8
   पूर्णांकerface. */
#घोषणा TCM_REG_USEM_LENGTH_MIS 				 0x50170
/* [RW 3] The weight of the input usem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा TCM_REG_USEM_WEIGHT					 0x500b8
/* [RW 21] Indirect access to the descriptor table of the XX protection
   mechanism. The fields are: [5:0] - length of the message; 15:6] - message
   poपूर्णांकer; 20:16] - next poपूर्णांकer. */
#घोषणा TCM_REG_XX_DESCR_TABLE					 0x50280
#घोषणा TCM_REG_XX_DESCR_TABLE_SIZE				 29
/* [R 6] Use to पढ़ो the value of XX protection Free counter. */
#घोषणा TCM_REG_XX_FREE 					 0x50178
/* [RW 6] Initial value क्रम the credit counter; responsible क्रम fulfilling
   of the Input Stage XX protection buffer by the XX protection pending
   messages. Max credit available - 127.Write ग_लिखोs the initial credit
   value; पढ़ो वापसs the current value of the credit counter. Must be
   initialized to 19 at start-up. */
#घोषणा TCM_REG_XX_INIT_CRD					 0x50220
/* [RW 6] Maximum link list size (messages locked) per connection in the XX
   protection. */
#घोषणा TCM_REG_XX_MAX_LL_SZ					 0x50044
/* [RW 6] The maximum number of pending messages; which may be stored in XX
   protection. ~tcm_रेजिस्टरs_xx_मुक्त.xx_मुक्त is पढ़ो on पढ़ो. */
#घोषणा TCM_REG_XX_MSG_NUM					 0x50224
/* [RW 8] The Event ID; sent to the STORM in हाल of XX overflow. */
#घोषणा TCM_REG_XX_OVFL_EVNT_ID 				 0x50048
/* [RW 16] Indirect access to the XX table of the XX protection mechanism.
   The fields are:[4:0] - tail poपूर्णांकer; [10:5] - Link List size; 15:11] -
   header poपूर्णांकer. */
#घोषणा TCM_REG_XX_TABLE					 0x50240
/* [RW 4] Load value क्रम cfc ac credit cnt. */
#घोषणा TM_REG_CFC_AC_CRDCNT_VAL				 0x164208
/* [RW 4] Load value क्रम cfc cld credit cnt. */
#घोषणा TM_REG_CFC_CLD_CRDCNT_VAL				 0x164210
/* [RW 8] Client0 context region. */
#घोषणा TM_REG_CL0_CONT_REGION					 0x164030
/* [RW 8] Client1 context region. */
#घोषणा TM_REG_CL1_CONT_REGION					 0x164034
/* [RW 8] Client2 context region. */
#घोषणा TM_REG_CL2_CONT_REGION					 0x164038
/* [RW 2] Client in High priority client number. */
#घोषणा TM_REG_CLIN_PRIOR0_CLIENT				 0x164024
/* [RW 4] Load value क्रम clout0 cred cnt. */
#घोषणा TM_REG_CLOUT_CRDCNT0_VAL				 0x164220
/* [RW 4] Load value क्रम clout1 cred cnt. */
#घोषणा TM_REG_CLOUT_CRDCNT1_VAL				 0x164228
/* [RW 4] Load value क्रम clout2 cred cnt. */
#घोषणा TM_REG_CLOUT_CRDCNT2_VAL				 0x164230
/* [RW 1] Enable client0 input. */
#घोषणा TM_REG_EN_CL0_INPUT					 0x164008
/* [RW 1] Enable client1 input. */
#घोषणा TM_REG_EN_CL1_INPUT					 0x16400c
/* [RW 1] Enable client2 input. */
#घोषणा TM_REG_EN_CL2_INPUT					 0x164010
#घोषणा TM_REG_EN_LINEAR0_TIMER 				 0x164014
/* [RW 1] Enable real समय counter. */
#घोषणा TM_REG_EN_REAL_TIME_CNT 				 0x1640d8
/* [RW 1] Enable क्रम Timers state machines. */
#घोषणा TM_REG_EN_TIMERS					 0x164000
/* [RW 4] Load value क्रम expiration credit cnt. CFC max number of
   outstanding load requests क्रम समयrs (expiration) context loading. */
#घोषणा TM_REG_EXP_CRDCNT_VAL					 0x164238
/* [RW 32] Linear0 logic address. */
#घोषणा TM_REG_LIN0_LOGIC_ADDR					 0x164240
/* [RW 18] Linear0 Max active cid (in banks of 32 entries). */
#घोषणा TM_REG_LIN0_MAX_ACTIVE_CID				 0x164048
/* [ST 16] Linear0 Number of scans counter. */
#घोषणा TM_REG_LIN0_NUM_SCANS					 0x1640a0
/* [WB 64] Linear0 phy address. */
#घोषणा TM_REG_LIN0_PHY_ADDR					 0x164270
/* [RW 1] Linear0 physical address valid. */
#घोषणा TM_REG_LIN0_PHY_ADDR_VALID				 0x164248
#घोषणा TM_REG_LIN0_SCAN_ON					 0x1640d0
/* [RW 24] Linear0 array scan समयout. */
#घोषणा TM_REG_LIN0_SCAN_TIME					 0x16403c
#घोषणा TM_REG_LIN0_VNIC_UC					 0x164128
/* [RW 32] Linear1 logic address. */
#घोषणा TM_REG_LIN1_LOGIC_ADDR					 0x164250
/* [WB 64] Linear1 phy address. */
#घोषणा TM_REG_LIN1_PHY_ADDR					 0x164280
/* [RW 1] Linear1 physical address valid. */
#घोषणा TM_REG_LIN1_PHY_ADDR_VALID				 0x164258
/* [RW 6] Linear समयr set_clear fअगरo threshold. */
#घोषणा TM_REG_LIN_SETCLR_FIFO_ALFULL_THR			 0x164070
/* [RW 2] Load value क्रम pci arbiter credit cnt. */
#घोषणा TM_REG_PCIARB_CRDCNT_VAL				 0x164260
/* [RW 20] The amount of hardware cycles क्रम each समयr tick. */
#घोषणा TM_REG_TIMER_TICK_SIZE					 0x16401c
/* [RW 8] Timers Context region. */
#घोषणा TM_REG_TM_CONTEXT_REGION				 0x164044
/* [RW 1] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा TM_REG_TM_INT_MASK					 0x1640fc
/* [R 1] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा TM_REG_TM_INT_STS					 0x1640f0
/* [RW 7] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा TM_REG_TM_PRTY_MASK					 0x16410c
/* [R 7] Parity रेजिस्टर #0 पढ़ो */
#घोषणा TM_REG_TM_PRTY_STS					 0x164100
/* [RC 7] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा TM_REG_TM_PRTY_STS_CLR					 0x164104
/* [RW 8] The event id क्रम aggregated पूर्णांकerrupt 0 */
#घोषणा TSDM_REG_AGG_INT_EVENT_0				 0x42038
#घोषणा TSDM_REG_AGG_INT_EVENT_1				 0x4203c
#घोषणा TSDM_REG_AGG_INT_EVENT_2				 0x42040
#घोषणा TSDM_REG_AGG_INT_EVENT_3				 0x42044
#घोषणा TSDM_REG_AGG_INT_EVENT_4				 0x42048
/* [RW 1] The T bit क्रम aggregated पूर्णांकerrupt 0 */
#घोषणा TSDM_REG_AGG_INT_T_0					 0x420b8
#घोषणा TSDM_REG_AGG_INT_T_1					 0x420bc
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the cfc_rsp lcid */
#घोषणा TSDM_REG_CFC_RSP_START_ADDR				 0x42008
/* [RW 16] The maximum value of the completion counter #0 */
#घोषणा TSDM_REG_CMP_COUNTER_MAX0				 0x4201c
/* [RW 16] The maximum value of the completion counter #1 */
#घोषणा TSDM_REG_CMP_COUNTER_MAX1				 0x42020
/* [RW 16] The maximum value of the completion counter #2 */
#घोषणा TSDM_REG_CMP_COUNTER_MAX2				 0x42024
/* [RW 16] The maximum value of the completion counter #3 */
#घोषणा TSDM_REG_CMP_COUNTER_MAX3				 0x42028
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the completion
   counters. */
#घोषणा TSDM_REG_CMP_COUNTER_START_ADDR 			 0x4200c
#घोषणा TSDM_REG_ENABLE_IN1					 0x42238
#घोषणा TSDM_REG_ENABLE_IN2					 0x4223c
#घोषणा TSDM_REG_ENABLE_OUT1					 0x42240
#घोषणा TSDM_REG_ENABLE_OUT2					 0x42244
/* [RW 4] The initial number of messages that can be sent to the pxp control
   पूर्णांकerface without receiving any ACK. */
#घोषणा TSDM_REG_INIT_CREDIT_PXP_CTRL				 0x424bc
/* [ST 32] The number of ACK after placement messages received */
#घोषणा TSDM_REG_NUM_OF_ACK_AFTER_PLACE 			 0x4227c
/* [ST 32] The number of packet end messages received from the parser */
#घोषणा TSDM_REG_NUM_OF_PKT_END_MSG				 0x42274
/* [ST 32] The number of requests received from the pxp async अगर */
#घोषणा TSDM_REG_NUM_OF_PXP_ASYNC_REQ				 0x42278
/* [ST 32] The number of commands received in queue 0 */
#घोषणा TSDM_REG_NUM_OF_Q0_CMD					 0x42248
/* [ST 32] The number of commands received in queue 10 */
#घोषणा TSDM_REG_NUM_OF_Q10_CMD 				 0x4226c
/* [ST 32] The number of commands received in queue 11 */
#घोषणा TSDM_REG_NUM_OF_Q11_CMD 				 0x42270
/* [ST 32] The number of commands received in queue 1 */
#घोषणा TSDM_REG_NUM_OF_Q1_CMD					 0x4224c
/* [ST 32] The number of commands received in queue 3 */
#घोषणा TSDM_REG_NUM_OF_Q3_CMD					 0x42250
/* [ST 32] The number of commands received in queue 4 */
#घोषणा TSDM_REG_NUM_OF_Q4_CMD					 0x42254
/* [ST 32] The number of commands received in queue 5 */
#घोषणा TSDM_REG_NUM_OF_Q5_CMD					 0x42258
/* [ST 32] The number of commands received in queue 6 */
#घोषणा TSDM_REG_NUM_OF_Q6_CMD					 0x4225c
/* [ST 32] The number of commands received in queue 7 */
#घोषणा TSDM_REG_NUM_OF_Q7_CMD					 0x42260
/* [ST 32] The number of commands received in queue 8 */
#घोषणा TSDM_REG_NUM_OF_Q8_CMD					 0x42264
/* [ST 32] The number of commands received in queue 9 */
#घोषणा TSDM_REG_NUM_OF_Q9_CMD					 0x42268
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the packet end message */
#घोषणा TSDM_REG_PCK_END_MSG_START_ADDR 			 0x42014
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम queue counters */
#घोषणा TSDM_REG_Q_COUNTER_START_ADDR				 0x42010
/* [R 1] pxp_ctrl rd_data fअगरo empty in sdm_dma_rsp block */
#घोषणा TSDM_REG_RSP_PXP_CTRL_RDATA_EMPTY			 0x42548
/* [R 1] parser fअगरo empty in sdm_sync block */
#घोषणा TSDM_REG_SYNC_PARSER_EMPTY				 0x42550
/* [R 1] parser serial fअगरo empty in sdm_sync block */
#घोषणा TSDM_REG_SYNC_SYNC_EMPTY				 0x42558
/* [RW 32] Tick क्रम समयr counter. Applicable only when
   ~tsdm_रेजिस्टरs_समयr_tick_enable.समयr_tick_enable =1 */
#घोषणा TSDM_REG_TIMER_TICK					 0x42000
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा TSDM_REG_TSDM_INT_MASK_0				 0x4229c
#घोषणा TSDM_REG_TSDM_INT_MASK_1				 0x422ac
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा TSDM_REG_TSDM_INT_STS_0 				 0x42290
#घोषणा TSDM_REG_TSDM_INT_STS_1 				 0x422a0
/* [RW 11] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा TSDM_REG_TSDM_PRTY_MASK 				 0x422bc
/* [R 11] Parity रेजिस्टर #0 पढ़ो */
#घोषणा TSDM_REG_TSDM_PRTY_STS					 0x422b0
/* [RC 11] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा TSDM_REG_TSDM_PRTY_STS_CLR				 0x422b4
/* [RW 5] The number of समय_slots in the arbitration cycle */
#घोषणा TSEM_REG_ARB_CYCLE_SIZE 				 0x180034
/* [RW 3] The source that is associated with arbitration element 0. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2 */
#घोषणा TSEM_REG_ARB_ELEMENT0					 0x180020
/* [RW 3] The source that is associated with arbitration element 1. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~tsem_रेजिस्टरs_arb_element0.arb_element0 */
#घोषणा TSEM_REG_ARB_ELEMENT1					 0x180024
/* [RW 3] The source that is associated with arbitration element 2. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~tsem_रेजिस्टरs_arb_element0.arb_element0
   and ~tsem_रेजिस्टरs_arb_element1.arb_element1 */
#घोषणा TSEM_REG_ARB_ELEMENT2					 0x180028
/* [RW 3] The source that is associated with arbitration element 3. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.Could
   not be equal to रेजिस्टर ~tsem_रेजिस्टरs_arb_element0.arb_element0 and
   ~tsem_रेजिस्टरs_arb_element1.arb_element1 and
   ~tsem_रेजिस्टरs_arb_element2.arb_element2 */
#घोषणा TSEM_REG_ARB_ELEMENT3					 0x18002c
/* [RW 3] The source that is associated with arbitration element 4. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~tsem_रेजिस्टरs_arb_element0.arb_element0
   and ~tsem_रेजिस्टरs_arb_element1.arb_element1 and
   ~tsem_रेजिस्टरs_arb_element2.arb_element2 and
   ~tsem_रेजिस्टरs_arb_element3.arb_element3 */
#घोषणा TSEM_REG_ARB_ELEMENT4					 0x180030
#घोषणा TSEM_REG_ENABLE_IN					 0x1800a4
#घोषणा TSEM_REG_ENABLE_OUT					 0x1800a8
/* [RW 32] This address space contains all रेजिस्टरs and memories that are
   placed in SEM_FAST block. The SEM_FAST रेजिस्टरs are described in
   appendix B. In order to access the sem_fast रेजिस्टरs the base address
   ~fast_memory.fast_memory should be added to eachsem_fast रेजिस्टर offset. */
#घोषणा TSEM_REG_FAST_MEMORY					 0x1a0000
/* [RW 1] Disables input messages from FIC0 May be updated during run_समय
   by the microcode */
#घोषणा TSEM_REG_FIC0_DISABLE					 0x180224
/* [RW 1] Disables input messages from FIC1 May be updated during run_समय
   by the microcode */
#घोषणा TSEM_REG_FIC1_DISABLE					 0x180234
/* [RW 15] Interrupt table Read and ग_लिखो access to it is not possible in
   the middle of the work */
#घोषणा TSEM_REG_INT_TABLE					 0x180400
/* [ST 24] Statistics रेजिस्टर. The number of messages that entered through
   FIC0 */
#घोषणा TSEM_REG_MSG_NUM_FIC0					 0x180000
/* [ST 24] Statistics रेजिस्टर. The number of messages that entered through
   FIC1 */
#घोषणा TSEM_REG_MSG_NUM_FIC1					 0x180004
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC0 */
#घोषणा TSEM_REG_MSG_NUM_FOC0					 0x180008
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC1 */
#घोषणा TSEM_REG_MSG_NUM_FOC1					 0x18000c
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC2 */
#घोषणा TSEM_REG_MSG_NUM_FOC2					 0x180010
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC3 */
#घोषणा TSEM_REG_MSG_NUM_FOC3					 0x180014
/* [RW 1] Disables input messages from the passive buffer May be updated
   during run_समय by the microcode */
#घोषणा TSEM_REG_PAS_DISABLE					 0x18024c
/* [WB 128] Debug only. Passive buffer memory */
#घोषणा TSEM_REG_PASSIVE_BUFFER 				 0x181000
/* [WB 46] pram memory. B45 is parity; b[44:0] - data. */
#घोषणा TSEM_REG_PRAM						 0x1c0000
/* [R 8] Valid sleeping thपढ़ोs indication have bit per thपढ़ो */
#घोषणा TSEM_REG_SLEEP_THREADS_VALID				 0x18026c
/* [R 1] EXT_STORE FIFO is empty in sem_slow_ls_ext */
#घोषणा TSEM_REG_SLOW_EXT_STORE_EMPTY				 0x1802a0
/* [RW 8] List of मुक्त thपढ़ोs . There is a bit per thपढ़ो. */
#घोषणा TSEM_REG_THREADS_LIST					 0x1802e4
/* [RC 32] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा TSEM_REG_TSEM_PRTY_STS_CLR_0				 0x180118
#घोषणा TSEM_REG_TSEM_PRTY_STS_CLR_1				 0x180128
/* [RW 3] The arbitration scheme of समय_slot 0 */
#घोषणा TSEM_REG_TS_0_AS					 0x180038
/* [RW 3] The arbitration scheme of समय_slot 10 */
#घोषणा TSEM_REG_TS_10_AS					 0x180060
/* [RW 3] The arbitration scheme of समय_slot 11 */
#घोषणा TSEM_REG_TS_11_AS					 0x180064
/* [RW 3] The arbitration scheme of समय_slot 12 */
#घोषणा TSEM_REG_TS_12_AS					 0x180068
/* [RW 3] The arbitration scheme of समय_slot 13 */
#घोषणा TSEM_REG_TS_13_AS					 0x18006c
/* [RW 3] The arbitration scheme of समय_slot 14 */
#घोषणा TSEM_REG_TS_14_AS					 0x180070
/* [RW 3] The arbitration scheme of समय_slot 15 */
#घोषणा TSEM_REG_TS_15_AS					 0x180074
/* [RW 3] The arbitration scheme of समय_slot 16 */
#घोषणा TSEM_REG_TS_16_AS					 0x180078
/* [RW 3] The arbitration scheme of समय_slot 17 */
#घोषणा TSEM_REG_TS_17_AS					 0x18007c
/* [RW 3] The arbitration scheme of समय_slot 18 */
#घोषणा TSEM_REG_TS_18_AS					 0x180080
/* [RW 3] The arbitration scheme of समय_slot 1 */
#घोषणा TSEM_REG_TS_1_AS					 0x18003c
/* [RW 3] The arbitration scheme of समय_slot 2 */
#घोषणा TSEM_REG_TS_2_AS					 0x180040
/* [RW 3] The arbitration scheme of समय_slot 3 */
#घोषणा TSEM_REG_TS_3_AS					 0x180044
/* [RW 3] The arbitration scheme of समय_slot 4 */
#घोषणा TSEM_REG_TS_4_AS					 0x180048
/* [RW 3] The arbitration scheme of समय_slot 5 */
#घोषणा TSEM_REG_TS_5_AS					 0x18004c
/* [RW 3] The arbitration scheme of समय_slot 6 */
#घोषणा TSEM_REG_TS_6_AS					 0x180050
/* [RW 3] The arbitration scheme of समय_slot 7 */
#घोषणा TSEM_REG_TS_7_AS					 0x180054
/* [RW 3] The arbitration scheme of समय_slot 8 */
#घोषणा TSEM_REG_TS_8_AS					 0x180058
/* [RW 3] The arbitration scheme of समय_slot 9 */
#घोषणा TSEM_REG_TS_9_AS					 0x18005c
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा TSEM_REG_TSEM_INT_MASK_0				 0x180100
#घोषणा TSEM_REG_TSEM_INT_MASK_1				 0x180110
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा TSEM_REG_TSEM_INT_STS_0 				 0x1800f4
#घोषणा TSEM_REG_TSEM_INT_STS_1 				 0x180104
/* [RW 32] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा TSEM_REG_TSEM_PRTY_MASK_0				 0x180120
#घोषणा TSEM_REG_TSEM_PRTY_MASK_1				 0x180130
/* [R 32] Parity रेजिस्टर #0 पढ़ो */
#घोषणा TSEM_REG_TSEM_PRTY_STS_0				 0x180114
#घोषणा TSEM_REG_TSEM_PRTY_STS_1				 0x180124
/* [W 7] VF or PF ID क्रम reset error bit. Values 0-63 reset error bit क्रम 64
 * VF; values 64-67 reset error क्रम 4 PF; values 68-127 are not valid. */
#घोषणा TSEM_REG_VFPF_ERR_NUM					 0x180380
/* [RW 32] Indirect access to AG context with 32-bits granularity. The bits
 * [10:8] of the address should be the offset within the accessed LCID
 * context; the bits [7:0] are the accessed LCID.Example: to ग_लिखो to REG10
 * LCID100. The RBC address should be 12'ha64. */
#घोषणा UCM_REG_AG_CTX						 0xe2000
/* [R 5] Used to पढ़ो the XX protection CAM occupancy counter. */
#घोषणा UCM_REG_CAM_OCCUP					 0xe0170
/* [RW 1] CDU AG पढ़ो Interface enable. If 0 - the request input is
   disregarded; valid output is deनिश्चितed; all other संकेतs are treated as
   usual; अगर 1 - normal activity. */
#घोषणा UCM_REG_CDU_AG_RD_IFEN					 0xe0038
/* [RW 1] CDU AG ग_लिखो Interface enable. If 0 - the request and valid input
   are disregarded; all other संकेतs are treated as usual; अगर 1 - normal
   activity. */
#घोषणा UCM_REG_CDU_AG_WR_IFEN					 0xe0034
/* [RW 1] CDU STORM पढ़ो Interface enable. If 0 - the request input is
   disregarded; valid output is deनिश्चितed; all other संकेतs are treated as
   usual; अगर 1 - normal activity. */
#घोषणा UCM_REG_CDU_SM_RD_IFEN					 0xe0040
/* [RW 1] CDU STORM ग_लिखो Interface enable. If 0 - the request and valid
   input is disregarded; all other संकेतs are treated as usual; अगर 1 -
   normal activity. */
#घोषणा UCM_REG_CDU_SM_WR_IFEN					 0xe003c
/* [RW 4] CFC output initial credit. Max credit available - 15.Write ग_लिखोs
   the initial credit value; पढ़ो वापसs the current value of the credit
   counter. Must be initialized to 1 at start-up. */
#घोषणा UCM_REG_CFC_INIT_CRD					 0xe0204
/* [RW 3] The weight of the CP input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_CP_WEIGHT					 0xe00c4
/* [RW 1] Input csem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा UCM_REG_CSEM_IFEN					 0xe0028
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the csem पूर्णांकerface is detected. */
#घोषणा UCM_REG_CSEM_LENGTH_MIS 				 0xe0160
/* [RW 3] The weight of the input csem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_CSEM_WEIGHT					 0xe00b8
/* [RW 1] Input करोrq Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा UCM_REG_DORQ_IFEN					 0xe0030
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the करोrq पूर्णांकerface is detected. */
#घोषणा UCM_REG_DORQ_LENGTH_MIS 				 0xe0168
/* [RW 3] The weight of the input करोrq in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_DORQ_WEIGHT					 0xe00c0
/* [RW 8] The Event ID in हाल ErrorFlg input message bit is set. */
#घोषणा UCM_REG_ERR_EVNT_ID					 0xe00a4
/* [RW 28] The CM erroneous header क्रम QM and Timers क्रमmatting. */
#घोषणा UCM_REG_ERR_UCM_HDR					 0xe00a0
/* [RW 8] The Event ID क्रम Timers expiration. */
#घोषणा UCM_REG_EXPR_EVNT_ID					 0xe00a8
/* [RW 8] FIC0 output initial credit. Max credit available - 255.Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 64 at start-up. */
#घोषणा UCM_REG_FIC0_INIT_CRD					 0xe020c
/* [RW 8] FIC1 output initial credit. Max credit available - 255.Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 64 at start-up. */
#घोषणा UCM_REG_FIC1_INIT_CRD					 0xe0210
/* [RW 1] Arbitration between Input Arbiter groups: 0 - fair Round-Robin; 1
   - strict priority defined by ~ucm_रेजिस्टरs_gr_ag_pr.gr_ag_pr;
   ~ucm_रेजिस्टरs_gr_ld0_pr.gr_ld0_pr and
   ~ucm_रेजिस्टरs_gr_ld1_pr.gr_ld1_pr. */
#घोषणा UCM_REG_GR_ARB_TYPE					 0xe0144
/* [RW 2] Load (FIC0) channel group priority. The lowest priority is 0; the
   highest priority is 3. It is supposed that the Store channel group is
   complement to the others. */
#घोषणा UCM_REG_GR_LD0_PR					 0xe014c
/* [RW 2] Load (FIC1) channel group priority. The lowest priority is 0; the
   highest priority is 3. It is supposed that the Store channel group is
   complement to the others. */
#घोषणा UCM_REG_GR_LD1_PR					 0xe0150
/* [RW 2] The queue index क्रम invalidate counter flag decision. */
#घोषणा UCM_REG_INV_CFLG_Q					 0xe00e4
/* [RW 5] The number of द्विगुन REG-pairs; loaded from the STORM context and
   sent to STORM; क्रम a specअगरic connection type. the द्विगुन REG-pairs are
   used in order to align to STORM context row size of 128 bits. The offset
   of these data in the STORM context is always 0. Index _i stands क्रम the
   connection type (one of 16). */
#घोषणा UCM_REG_N_SM_CTX_LD_0					 0xe0054
#घोषणा UCM_REG_N_SM_CTX_LD_1					 0xe0058
#घोषणा UCM_REG_N_SM_CTX_LD_2					 0xe005c
#घोषणा UCM_REG_N_SM_CTX_LD_3					 0xe0060
#घोषणा UCM_REG_N_SM_CTX_LD_4					 0xe0064
#घोषणा UCM_REG_N_SM_CTX_LD_5					 0xe0068
#घोषणा UCM_REG_PHYS_QNUM0_0					 0xe0110
#घोषणा UCM_REG_PHYS_QNUM0_1					 0xe0114
#घोषणा UCM_REG_PHYS_QNUM1_0					 0xe0118
#घोषणा UCM_REG_PHYS_QNUM1_1					 0xe011c
#घोषणा UCM_REG_PHYS_QNUM2_0					 0xe0120
#घोषणा UCM_REG_PHYS_QNUM2_1					 0xe0124
#घोषणा UCM_REG_PHYS_QNUM3_0					 0xe0128
#घोषणा UCM_REG_PHYS_QNUM3_1					 0xe012c
/* [RW 8] The Event ID क्रम Timers क्रमmatting in हाल of stop करोne. */
#घोषणा UCM_REG_STOP_EVNT_ID					 0xe00ac
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the STORM पूर्णांकerface is detected. */
#घोषणा UCM_REG_STORM_LENGTH_MIS				 0xe0154
/* [RW 1] STORM - CM Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा UCM_REG_STORM_UCM_IFEN					 0xe0010
/* [RW 3] The weight of the STORM input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_STORM_WEIGHT					 0xe00b0
/* [RW 4] Timers output initial credit. Max credit available - 15.Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 4 at start-up. */
#घोषणा UCM_REG_TM_INIT_CRD					 0xe021c
/* [RW 28] The CM header क्रम Timers expiration command. */
#घोषणा UCM_REG_TM_UCM_HDR					 0xe009c
/* [RW 1] Timers - CM Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा UCM_REG_TM_UCM_IFEN					 0xe001c
/* [RW 3] The weight of the Timers input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_TM_WEIGHT					 0xe00d4
/* [RW 1] Input tsem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा UCM_REG_TSEM_IFEN					 0xe0024
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the tsem पूर्णांकerface is detected. */
#घोषणा UCM_REG_TSEM_LENGTH_MIS 				 0xe015c
/* [RW 3] The weight of the input tsem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_TSEM_WEIGHT					 0xe00b4
/* [RW 1] CM - CFC Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा UCM_REG_UCM_CFC_IFEN					 0xe0044
/* [RW 11] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा UCM_REG_UCM_INT_MASK					 0xe01d4
/* [R 11] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा UCM_REG_UCM_INT_STS					 0xe01c8
/* [RW 27] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा UCM_REG_UCM_PRTY_MASK					 0xe01e4
/* [R 27] Parity रेजिस्टर #0 पढ़ो */
#घोषणा UCM_REG_UCM_PRTY_STS					 0xe01d8
/* [RC 27] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा UCM_REG_UCM_PRTY_STS_CLR				 0xe01dc
/* [RW 2] The size of AG context region 0 in REG-pairs. Designates the MS
   REG-pair number (e.g. अगर region 0 is 6 REG-pairs; the value should be 5).
   Is used to determine the number of the AG context REG-pairs written back;
   when the Reg1WbFlg isn't set. */
#घोषणा UCM_REG_UCM_REG0_SZ					 0xe00dc
/* [RW 1] CM - STORM 0 Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा UCM_REG_UCM_STORM0_IFEN 				 0xe0004
/* [RW 1] CM - STORM 1 Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा UCM_REG_UCM_STORM1_IFEN 				 0xe0008
/* [RW 1] CM - Timers Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा UCM_REG_UCM_TM_IFEN					 0xe0020
/* [RW 1] CM - QM Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा UCM_REG_UCM_UQM_IFEN					 0xe000c
/* [RW 1] If set the Q index; received from the QM is inserted to event ID. */
#घोषणा UCM_REG_UCM_UQM_USE_Q					 0xe00d8
/* [RW 6] QM output initial credit. Max credit available - 32.Write ग_लिखोs
   the initial credit value; पढ़ो वापसs the current value of the credit
   counter. Must be initialized to 32 at start-up. */
#घोषणा UCM_REG_UQM_INIT_CRD					 0xe0220
/* [RW 3] The weight of the QM (primary) input in the WRR mechanism. 0
   stands क्रम weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_UQM_P_WEIGHT					 0xe00cc
/* [RW 3] The weight of the QM (secondary) input in the WRR mechanism. 0
   stands क्रम weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_UQM_S_WEIGHT					 0xe00d0
/* [RW 28] The CM header value क्रम QM request (primary). */
#घोषणा UCM_REG_UQM_UCM_HDR_P					 0xe0094
/* [RW 28] The CM header value क्रम QM request (secondary). */
#घोषणा UCM_REG_UQM_UCM_HDR_S					 0xe0098
/* [RW 1] QM - CM Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा UCM_REG_UQM_UCM_IFEN					 0xe0014
/* [RW 1] Input SDM Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा UCM_REG_USDM_IFEN					 0xe0018
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the SDM पूर्णांकerface is detected. */
#घोषणा UCM_REG_USDM_LENGTH_MIS 				 0xe0158
/* [RW 3] The weight of the SDM input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_USDM_WEIGHT					 0xe00c8
/* [RW 1] Input xsem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा UCM_REG_XSEM_IFEN					 0xe002c
/* [RC 1] Set when the message length mismatch (relative to last indication)
   at the xsem पूर्णांकerface isdetected. */
#घोषणा UCM_REG_XSEM_LENGTH_MIS 				 0xe0164
/* [RW 3] The weight of the input xsem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा UCM_REG_XSEM_WEIGHT					 0xe00bc
/* [RW 20] Indirect access to the descriptor table of the XX protection
   mechanism. The fields are:[5:0] - message length; 14:6] - message
   poपूर्णांकer; 19:15] - next poपूर्णांकer. */
#घोषणा UCM_REG_XX_DESCR_TABLE					 0xe0280
#घोषणा UCM_REG_XX_DESCR_TABLE_SIZE				 27
/* [R 6] Use to पढ़ो the XX protection Free counter. */
#घोषणा UCM_REG_XX_FREE 					 0xe016c
/* [RW 6] Initial value क्रम the credit counter; responsible क्रम fulfilling
   of the Input Stage XX protection buffer by the XX protection pending
   messages. Write ग_लिखोs the initial credit value; पढ़ो वापसs the current
   value of the credit counter. Must be initialized to 12 at start-up. */
#घोषणा UCM_REG_XX_INIT_CRD					 0xe0224
/* [RW 6] The maximum number of pending messages; which may be stored in XX
   protection. ~ucm_रेजिस्टरs_xx_मुक्त.xx_मुक्त पढ़ो on पढ़ो. */
#घोषणा UCM_REG_XX_MSG_NUM					 0xe0228
/* [RW 8] The Event ID; sent to the STORM in हाल of XX overflow. */
#घोषणा UCM_REG_XX_OVFL_EVNT_ID 				 0xe004c
/* [RW 16] Indirect access to the XX table of the XX protection mechanism.
   The fields are: [4:0] - tail poपूर्णांकer; 10:5] - Link List size; 15:11] -
   header poपूर्णांकer. */
#घोषणा UCM_REG_XX_TABLE					 0xe0300
#घोषणा UMAC_COMMAND_CONFIG_REG_HD_ENA				 (0x1<<10)
#घोषणा UMAC_COMMAND_CONFIG_REG_IGNORE_TX_PAUSE			 (0x1<<28)
#घोषणा UMAC_COMMAND_CONFIG_REG_LOOP_ENA			 (0x1<<15)
#घोषणा UMAC_COMMAND_CONFIG_REG_NO_LGTH_CHECK			 (0x1<<24)
#घोषणा UMAC_COMMAND_CONFIG_REG_PAD_EN				 (0x1<<5)
#घोषणा UMAC_COMMAND_CONFIG_REG_PAUSE_IGNORE			 (0x1<<8)
#घोषणा UMAC_COMMAND_CONFIG_REG_PROMIS_EN			 (0x1<<4)
#घोषणा UMAC_COMMAND_CONFIG_REG_RX_ENA				 (0x1<<1)
#घोषणा UMAC_COMMAND_CONFIG_REG_SW_RESET			 (0x1<<13)
#घोषणा UMAC_COMMAND_CONFIG_REG_TX_ENA				 (0x1<<0)
#घोषणा UMAC_REG_COMMAND_CONFIG					 0x8
/* [RW 16] This is the duration क्रम which MAC must रुको to go back to ACTIVE
 * state from LPI state when it receives packet क्रम transmission. The
 * decrement unit is 1 micro-second. */
#घोषणा UMAC_REG_EEE_WAKE_TIMER					 0x6c
/* [RW 32] Register Bit 0 refers to Bit 16 of the MAC address; Bit 1 refers
 * to bit 17 of the MAC address etc. */
#घोषणा UMAC_REG_MAC_ADDR0					 0xc
/* [RW 16] Register Bit 0 refers to Bit 0 of the MAC address; Register Bit 1
 * refers to Bit 1 of the MAC address etc. Bits 16 to 31 are reserved. */
#घोषणा UMAC_REG_MAC_ADDR1					 0x10
/* [RW 14] Defines a 14-Bit maximum frame length used by the MAC receive
 * logic to check frames. */
#घोषणा UMAC_REG_MAXFR						 0x14
#घोषणा UMAC_REG_UMAC_EEE_CTRL					 0x64
#घोषणा UMAC_UMAC_EEE_CTRL_REG_EEE_EN				 (0x1<<3)
/* [RW 8] The event id क्रम aggregated पूर्णांकerrupt 0 */
#घोषणा USDM_REG_AGG_INT_EVENT_0				 0xc4038
#घोषणा USDM_REG_AGG_INT_EVENT_1				 0xc403c
#घोषणा USDM_REG_AGG_INT_EVENT_2				 0xc4040
#घोषणा USDM_REG_AGG_INT_EVENT_4				 0xc4048
#घोषणा USDM_REG_AGG_INT_EVENT_5				 0xc404c
#घोषणा USDM_REG_AGG_INT_EVENT_6				 0xc4050
/* [RW 1] For each aggregated पूर्णांकerrupt index whether the mode is normal (0)
   or स्वतः-mask-mode (1) */
#घोषणा USDM_REG_AGG_INT_MODE_0 				 0xc41b8
#घोषणा USDM_REG_AGG_INT_MODE_1 				 0xc41bc
#घोषणा USDM_REG_AGG_INT_MODE_4 				 0xc41c8
#घोषणा USDM_REG_AGG_INT_MODE_5 				 0xc41cc
#घोषणा USDM_REG_AGG_INT_MODE_6 				 0xc41d0
/* [RW 1] The T bit क्रम aggregated पूर्णांकerrupt 5 */
#घोषणा USDM_REG_AGG_INT_T_5					 0xc40cc
#घोषणा USDM_REG_AGG_INT_T_6					 0xc40d0
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the cfc_rsp lcid */
#घोषणा USDM_REG_CFC_RSP_START_ADDR				 0xc4008
/* [RW 16] The maximum value of the completion counter #0 */
#घोषणा USDM_REG_CMP_COUNTER_MAX0				 0xc401c
/* [RW 16] The maximum value of the completion counter #1 */
#घोषणा USDM_REG_CMP_COUNTER_MAX1				 0xc4020
/* [RW 16] The maximum value of the completion counter #2 */
#घोषणा USDM_REG_CMP_COUNTER_MAX2				 0xc4024
/* [RW 16] The maximum value of the completion counter #3 */
#घोषणा USDM_REG_CMP_COUNTER_MAX3				 0xc4028
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the completion
   counters. */
#घोषणा USDM_REG_CMP_COUNTER_START_ADDR 			 0xc400c
#घोषणा USDM_REG_ENABLE_IN1					 0xc4238
#घोषणा USDM_REG_ENABLE_IN2					 0xc423c
#घोषणा USDM_REG_ENABLE_OUT1					 0xc4240
#घोषणा USDM_REG_ENABLE_OUT2					 0xc4244
/* [RW 4] The initial number of messages that can be sent to the pxp control
   पूर्णांकerface without receiving any ACK. */
#घोषणा USDM_REG_INIT_CREDIT_PXP_CTRL				 0xc44c0
/* [ST 32] The number of ACK after placement messages received */
#घोषणा USDM_REG_NUM_OF_ACK_AFTER_PLACE 			 0xc4280
/* [ST 32] The number of packet end messages received from the parser */
#घोषणा USDM_REG_NUM_OF_PKT_END_MSG				 0xc4278
/* [ST 32] The number of requests received from the pxp async अगर */
#घोषणा USDM_REG_NUM_OF_PXP_ASYNC_REQ				 0xc427c
/* [ST 32] The number of commands received in queue 0 */
#घोषणा USDM_REG_NUM_OF_Q0_CMD					 0xc4248
/* [ST 32] The number of commands received in queue 10 */
#घोषणा USDM_REG_NUM_OF_Q10_CMD 				 0xc4270
/* [ST 32] The number of commands received in queue 11 */
#घोषणा USDM_REG_NUM_OF_Q11_CMD 				 0xc4274
/* [ST 32] The number of commands received in queue 1 */
#घोषणा USDM_REG_NUM_OF_Q1_CMD					 0xc424c
/* [ST 32] The number of commands received in queue 2 */
#घोषणा USDM_REG_NUM_OF_Q2_CMD					 0xc4250
/* [ST 32] The number of commands received in queue 3 */
#घोषणा USDM_REG_NUM_OF_Q3_CMD					 0xc4254
/* [ST 32] The number of commands received in queue 4 */
#घोषणा USDM_REG_NUM_OF_Q4_CMD					 0xc4258
/* [ST 32] The number of commands received in queue 5 */
#घोषणा USDM_REG_NUM_OF_Q5_CMD					 0xc425c
/* [ST 32] The number of commands received in queue 6 */
#घोषणा USDM_REG_NUM_OF_Q6_CMD					 0xc4260
/* [ST 32] The number of commands received in queue 7 */
#घोषणा USDM_REG_NUM_OF_Q7_CMD					 0xc4264
/* [ST 32] The number of commands received in queue 8 */
#घोषणा USDM_REG_NUM_OF_Q8_CMD					 0xc4268
/* [ST 32] The number of commands received in queue 9 */
#घोषणा USDM_REG_NUM_OF_Q9_CMD					 0xc426c
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the packet end message */
#घोषणा USDM_REG_PCK_END_MSG_START_ADDR 			 0xc4014
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम queue counters */
#घोषणा USDM_REG_Q_COUNTER_START_ADDR				 0xc4010
/* [R 1] pxp_ctrl rd_data fअगरo empty in sdm_dma_rsp block */
#घोषणा USDM_REG_RSP_PXP_CTRL_RDATA_EMPTY			 0xc4550
/* [R 1] parser fअगरo empty in sdm_sync block */
#घोषणा USDM_REG_SYNC_PARSER_EMPTY				 0xc4558
/* [R 1] parser serial fअगरo empty in sdm_sync block */
#घोषणा USDM_REG_SYNC_SYNC_EMPTY				 0xc4560
/* [RW 32] Tick क्रम समयr counter. Applicable only when
   ~usdm_रेजिस्टरs_समयr_tick_enable.समयr_tick_enable =1 */
#घोषणा USDM_REG_TIMER_TICK					 0xc4000
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा USDM_REG_USDM_INT_MASK_0				 0xc42a0
#घोषणा USDM_REG_USDM_INT_MASK_1				 0xc42b0
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा USDM_REG_USDM_INT_STS_0 				 0xc4294
#घोषणा USDM_REG_USDM_INT_STS_1 				 0xc42a4
/* [RW 11] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा USDM_REG_USDM_PRTY_MASK 				 0xc42c0
/* [R 11] Parity रेजिस्टर #0 पढ़ो */
#घोषणा USDM_REG_USDM_PRTY_STS					 0xc42b4
/* [RC 11] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा USDM_REG_USDM_PRTY_STS_CLR				 0xc42b8
/* [RW 5] The number of समय_slots in the arbitration cycle */
#घोषणा USEM_REG_ARB_CYCLE_SIZE 				 0x300034
/* [RW 3] The source that is associated with arbitration element 0. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2 */
#घोषणा USEM_REG_ARB_ELEMENT0					 0x300020
/* [RW 3] The source that is associated with arbitration element 1. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~usem_रेजिस्टरs_arb_element0.arb_element0 */
#घोषणा USEM_REG_ARB_ELEMENT1					 0x300024
/* [RW 3] The source that is associated with arbitration element 2. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~usem_रेजिस्टरs_arb_element0.arb_element0
   and ~usem_रेजिस्टरs_arb_element1.arb_element1 */
#घोषणा USEM_REG_ARB_ELEMENT2					 0x300028
/* [RW 3] The source that is associated with arbitration element 3. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.Could
   not be equal to रेजिस्टर ~usem_रेजिस्टरs_arb_element0.arb_element0 and
   ~usem_रेजिस्टरs_arb_element1.arb_element1 and
   ~usem_रेजिस्टरs_arb_element2.arb_element2 */
#घोषणा USEM_REG_ARB_ELEMENT3					 0x30002c
/* [RW 3] The source that is associated with arbitration element 4. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~usem_रेजिस्टरs_arb_element0.arb_element0
   and ~usem_रेजिस्टरs_arb_element1.arb_element1 and
   ~usem_रेजिस्टरs_arb_element2.arb_element2 and
   ~usem_रेजिस्टरs_arb_element3.arb_element3 */
#घोषणा USEM_REG_ARB_ELEMENT4					 0x300030
#घोषणा USEM_REG_ENABLE_IN					 0x3000a4
#घोषणा USEM_REG_ENABLE_OUT					 0x3000a8
/* [RW 32] This address space contains all रेजिस्टरs and memories that are
   placed in SEM_FAST block. The SEM_FAST रेजिस्टरs are described in
   appendix B. In order to access the sem_fast रेजिस्टरs the base address
   ~fast_memory.fast_memory should be added to eachsem_fast रेजिस्टर offset. */
#घोषणा USEM_REG_FAST_MEMORY					 0x320000
/* [RW 1] Disables input messages from FIC0 May be updated during run_समय
   by the microcode */
#घोषणा USEM_REG_FIC0_DISABLE					 0x300224
/* [RW 1] Disables input messages from FIC1 May be updated during run_समय
   by the microcode */
#घोषणा USEM_REG_FIC1_DISABLE					 0x300234
/* [RW 15] Interrupt table Read and ग_लिखो access to it is not possible in
   the middle of the work */
#घोषणा USEM_REG_INT_TABLE					 0x300400
/* [ST 24] Statistics रेजिस्टर. The number of messages that entered through
   FIC0 */
#घोषणा USEM_REG_MSG_NUM_FIC0					 0x300000
/* [ST 24] Statistics रेजिस्टर. The number of messages that entered through
   FIC1 */
#घोषणा USEM_REG_MSG_NUM_FIC1					 0x300004
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC0 */
#घोषणा USEM_REG_MSG_NUM_FOC0					 0x300008
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC1 */
#घोषणा USEM_REG_MSG_NUM_FOC1					 0x30000c
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC2 */
#घोषणा USEM_REG_MSG_NUM_FOC2					 0x300010
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC3 */
#घोषणा USEM_REG_MSG_NUM_FOC3					 0x300014
/* [RW 1] Disables input messages from the passive buffer May be updated
   during run_समय by the microcode */
#घोषणा USEM_REG_PAS_DISABLE					 0x30024c
/* [WB 128] Debug only. Passive buffer memory */
#घोषणा USEM_REG_PASSIVE_BUFFER 				 0x302000
/* [WB 46] pram memory. B45 is parity; b[44:0] - data. */
#घोषणा USEM_REG_PRAM						 0x340000
/* [R 16] Valid sleeping thपढ़ोs indication have bit per thपढ़ो */
#घोषणा USEM_REG_SLEEP_THREADS_VALID				 0x30026c
/* [R 1] EXT_STORE FIFO is empty in sem_slow_ls_ext */
#घोषणा USEM_REG_SLOW_EXT_STORE_EMPTY				 0x3002a0
/* [RW 16] List of मुक्त thपढ़ोs . There is a bit per thपढ़ो. */
#घोषणा USEM_REG_THREADS_LIST					 0x3002e4
/* [RW 3] The arbitration scheme of समय_slot 0 */
#घोषणा USEM_REG_TS_0_AS					 0x300038
/* [RW 3] The arbitration scheme of समय_slot 10 */
#घोषणा USEM_REG_TS_10_AS					 0x300060
/* [RW 3] The arbitration scheme of समय_slot 11 */
#घोषणा USEM_REG_TS_11_AS					 0x300064
/* [RW 3] The arbitration scheme of समय_slot 12 */
#घोषणा USEM_REG_TS_12_AS					 0x300068
/* [RW 3] The arbitration scheme of समय_slot 13 */
#घोषणा USEM_REG_TS_13_AS					 0x30006c
/* [RW 3] The arbitration scheme of समय_slot 14 */
#घोषणा USEM_REG_TS_14_AS					 0x300070
/* [RW 3] The arbitration scheme of समय_slot 15 */
#घोषणा USEM_REG_TS_15_AS					 0x300074
/* [RW 3] The arbitration scheme of समय_slot 16 */
#घोषणा USEM_REG_TS_16_AS					 0x300078
/* [RW 3] The arbitration scheme of समय_slot 17 */
#घोषणा USEM_REG_TS_17_AS					 0x30007c
/* [RW 3] The arbitration scheme of समय_slot 18 */
#घोषणा USEM_REG_TS_18_AS					 0x300080
/* [RW 3] The arbitration scheme of समय_slot 1 */
#घोषणा USEM_REG_TS_1_AS					 0x30003c
/* [RW 3] The arbitration scheme of समय_slot 2 */
#घोषणा USEM_REG_TS_2_AS					 0x300040
/* [RW 3] The arbitration scheme of समय_slot 3 */
#घोषणा USEM_REG_TS_3_AS					 0x300044
/* [RW 3] The arbitration scheme of समय_slot 4 */
#घोषणा USEM_REG_TS_4_AS					 0x300048
/* [RW 3] The arbitration scheme of समय_slot 5 */
#घोषणा USEM_REG_TS_5_AS					 0x30004c
/* [RW 3] The arbitration scheme of समय_slot 6 */
#घोषणा USEM_REG_TS_6_AS					 0x300050
/* [RW 3] The arbitration scheme of समय_slot 7 */
#घोषणा USEM_REG_TS_7_AS					 0x300054
/* [RW 3] The arbitration scheme of समय_slot 8 */
#घोषणा USEM_REG_TS_8_AS					 0x300058
/* [RW 3] The arbitration scheme of समय_slot 9 */
#घोषणा USEM_REG_TS_9_AS					 0x30005c
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा USEM_REG_USEM_INT_MASK_0				 0x300110
#घोषणा USEM_REG_USEM_INT_MASK_1				 0x300120
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा USEM_REG_USEM_INT_STS_0 				 0x300104
#घोषणा USEM_REG_USEM_INT_STS_1 				 0x300114
/* [RW 32] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा USEM_REG_USEM_PRTY_MASK_0				 0x300130
#घोषणा USEM_REG_USEM_PRTY_MASK_1				 0x300140
/* [R 32] Parity रेजिस्टर #0 पढ़ो */
#घोषणा USEM_REG_USEM_PRTY_STS_0				 0x300124
#घोषणा USEM_REG_USEM_PRTY_STS_1				 0x300134
/* [RC 32] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा USEM_REG_USEM_PRTY_STS_CLR_0				 0x300128
#घोषणा USEM_REG_USEM_PRTY_STS_CLR_1				 0x300138
/* [W 7] VF or PF ID क्रम reset error bit. Values 0-63 reset error bit क्रम 64
 * VF; values 64-67 reset error क्रम 4 PF; values 68-127 are not valid. */
#घोषणा USEM_REG_VFPF_ERR_NUM					 0x300380
#घोषणा VFC_MEMORIES_RST_REG_CAM_RST				 (0x1<<0)
#घोषणा VFC_MEMORIES_RST_REG_RAM_RST				 (0x1<<1)
#घोषणा VFC_REG_MEMORIES_RST					 0x1943c
/* [RW 32] Indirect access to AG context with 32-bits granularity. The bits
 * [12:8] of the address should be the offset within the accessed LCID
 * context; the bits [7:0] are the accessed LCID.Example: to ग_लिखो to REG10
 * LCID100. The RBC address should be 13'ha64. */
#घोषणा XCM_REG_AG_CTX						 0x28000
/* [RW 2] The queue index क्रम registration on Aux1 counter flag. */
#घोषणा XCM_REG_AUX1_Q						 0x20134
/* [RW 2] Per each decision rule the queue index to रेजिस्टर to. */
#घोषणा XCM_REG_AUX_CNT_FLG_Q_19				 0x201b0
/* [R 5] Used to पढ़ो the XX protection CAM occupancy counter. */
#घोषणा XCM_REG_CAM_OCCUP					 0x20244
/* [RW 1] CDU AG पढ़ो Interface enable. If 0 - the request input is
   disregarded; valid output is deनिश्चितed; all other संकेतs are treated as
   usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_CDU_AG_RD_IFEN					 0x20044
/* [RW 1] CDU AG ग_लिखो Interface enable. If 0 - the request and valid input
   are disregarded; all other संकेतs are treated as usual; अगर 1 - normal
   activity. */
#घोषणा XCM_REG_CDU_AG_WR_IFEN					 0x20040
/* [RW 1] CDU STORM पढ़ो Interface enable. If 0 - the request input is
   disregarded; valid output is deनिश्चितed; all other संकेतs are treated as
   usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_CDU_SM_RD_IFEN					 0x2004c
/* [RW 1] CDU STORM ग_लिखो Interface enable. If 0 - the request and valid
   input is disregarded; all other संकेतs are treated as usual; अगर 1 -
   normal activity. */
#घोषणा XCM_REG_CDU_SM_WR_IFEN					 0x20048
/* [RW 4] CFC output initial credit. Max credit available - 15.Write ग_लिखोs
   the initial credit value; पढ़ो वापसs the current value of the credit
   counter. Must be initialized to 1 at start-up. */
#घोषणा XCM_REG_CFC_INIT_CRD					 0x20404
/* [RW 3] The weight of the CP input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_CP_WEIGHT					 0x200dc
/* [RW 1] Input csem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_CSEM_IFEN					 0x20028
/* [RC 1] Set at message length mismatch (relative to last indication) at
   the csem पूर्णांकerface. */
#घोषणा XCM_REG_CSEM_LENGTH_MIS 				 0x20228
/* [RW 3] The weight of the input csem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_CSEM_WEIGHT					 0x200c4
/* [RW 1] Input करोrq Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_DORQ_IFEN					 0x20030
/* [RC 1] Set at message length mismatch (relative to last indication) at
   the करोrq पूर्णांकerface. */
#घोषणा XCM_REG_DORQ_LENGTH_MIS 				 0x20230
/* [RW 3] The weight of the input करोrq in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_DORQ_WEIGHT					 0x200cc
/* [RW 8] The Event ID in हाल the ErrorFlg input message bit is set. */
#घोषणा XCM_REG_ERR_EVNT_ID					 0x200b0
/* [RW 28] The CM erroneous header क्रम QM and Timers क्रमmatting. */
#घोषणा XCM_REG_ERR_XCM_HDR					 0x200ac
/* [RW 8] The Event ID क्रम Timers expiration. */
#घोषणा XCM_REG_EXPR_EVNT_ID					 0x200b4
/* [RW 8] FIC0 output initial credit. Max credit available - 255.Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 64 at start-up. */
#घोषणा XCM_REG_FIC0_INIT_CRD					 0x2040c
/* [RW 8] FIC1 output initial credit. Max credit available - 255.Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 64 at start-up. */
#घोषणा XCM_REG_FIC1_INIT_CRD					 0x20410
#घोषणा XCM_REG_GLB_DEL_ACK_MAX_CNT_0				 0x20118
#घोषणा XCM_REG_GLB_DEL_ACK_MAX_CNT_1				 0x2011c
#घोषणा XCM_REG_GLB_DEL_ACK_TMR_VAL_0				 0x20108
#घोषणा XCM_REG_GLB_DEL_ACK_TMR_VAL_1				 0x2010c
/* [RW 1] Arbitratiojn between Input Arbiter groups: 0 - fair Round-Robin; 1
   - strict priority defined by ~xcm_रेजिस्टरs_gr_ag_pr.gr_ag_pr;
   ~xcm_रेजिस्टरs_gr_ld0_pr.gr_ld0_pr and
   ~xcm_रेजिस्टरs_gr_ld1_pr.gr_ld1_pr. */
#घोषणा XCM_REG_GR_ARB_TYPE					 0x2020c
/* [RW 2] Load (FIC0) channel group priority. The lowest priority is 0; the
   highest priority is 3. It is supposed that the Channel group is the
   complement of the other 3 groups. */
#घोषणा XCM_REG_GR_LD0_PR					 0x20214
/* [RW 2] Load (FIC1) channel group priority. The lowest priority is 0; the
   highest priority is 3. It is supposed that the Channel group is the
   complement of the other 3 groups. */
#घोषणा XCM_REG_GR_LD1_PR					 0x20218
/* [RW 1] Input nig0 Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_NIG0_IFEN					 0x20038
/* [RC 1] Set at message length mismatch (relative to last indication) at
   the nig0 पूर्णांकerface. */
#घोषणा XCM_REG_NIG0_LENGTH_MIS 				 0x20238
/* [RW 3] The weight of the input nig0 in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_NIG0_WEIGHT					 0x200d4
/* [RW 1] Input nig1 Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_NIG1_IFEN					 0x2003c
/* [RC 1] Set at message length mismatch (relative to last indication) at
   the nig1 पूर्णांकerface. */
#घोषणा XCM_REG_NIG1_LENGTH_MIS 				 0x2023c
/* [RW 5] The number of द्विगुन REG-pairs; loaded from the STORM context and
   sent to STORM; क्रम a specअगरic connection type. The द्विगुन REG-pairs are
   used in order to align to STORM context row size of 128 bits. The offset
   of these data in the STORM context is always 0. Index _i stands क्रम the
   connection type (one of 16). */
#घोषणा XCM_REG_N_SM_CTX_LD_0					 0x20060
#घोषणा XCM_REG_N_SM_CTX_LD_1					 0x20064
#घोषणा XCM_REG_N_SM_CTX_LD_2					 0x20068
#घोषणा XCM_REG_N_SM_CTX_LD_3					 0x2006c
#घोषणा XCM_REG_N_SM_CTX_LD_4					 0x20070
#घोषणा XCM_REG_N_SM_CTX_LD_5					 0x20074
/* [RW 1] Input pbf Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा XCM_REG_PBF_IFEN					 0x20034
/* [RC 1] Set at message length mismatch (relative to last indication) at
   the pbf पूर्णांकerface. */
#घोषणा XCM_REG_PBF_LENGTH_MIS					 0x20234
/* [RW 3] The weight of the input pbf in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_PBF_WEIGHT					 0x200d0
#घोषणा XCM_REG_PHYS_QNUM3_0					 0x20100
#घोषणा XCM_REG_PHYS_QNUM3_1					 0x20104
/* [RW 8] The Event ID क्रम Timers क्रमmatting in हाल of stop करोne. */
#घोषणा XCM_REG_STOP_EVNT_ID					 0x200b8
/* [RC 1] Set at message length mismatch (relative to last indication) at
   the STORM पूर्णांकerface. */
#घोषणा XCM_REG_STORM_LENGTH_MIS				 0x2021c
/* [RW 3] The weight of the STORM input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_STORM_WEIGHT					 0x200bc
/* [RW 1] STORM - CM Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_STORM_XCM_IFEN					 0x20010
/* [RW 4] Timers output initial credit. Max credit available - 15.Write
   ग_लिखोs the initial credit value; पढ़ो वापसs the current value of the
   credit counter. Must be initialized to 4 at start-up. */
#घोषणा XCM_REG_TM_INIT_CRD					 0x2041c
/* [RW 3] The weight of the Timers input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_TM_WEIGHT					 0x200ec
/* [RW 28] The CM header क्रम Timers expiration command. */
#घोषणा XCM_REG_TM_XCM_HDR					 0x200a8
/* [RW 1] Timers - CM Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_TM_XCM_IFEN					 0x2001c
/* [RW 1] Input tsem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_TSEM_IFEN					 0x20024
/* [RC 1] Set at message length mismatch (relative to last indication) at
   the tsem पूर्णांकerface. */
#घोषणा XCM_REG_TSEM_LENGTH_MIS 				 0x20224
/* [RW 3] The weight of the input tsem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_TSEM_WEIGHT					 0x200c0
/* [RW 2] The queue index क्रम registration on UNA greater NXT decision rule. */
#घोषणा XCM_REG_UNA_GT_NXT_Q					 0x20120
/* [RW 1] Input usem Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_USEM_IFEN					 0x2002c
/* [RC 1] Message length mismatch (relative to last indication) at the usem
   पूर्णांकerface. */
#घोषणा XCM_REG_USEM_LENGTH_MIS 				 0x2022c
/* [RW 3] The weight of the input usem in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_USEM_WEIGHT					 0x200c8
#घोषणा XCM_REG_WU_DA_CNT_CMD00 				 0x201d4
#घोषणा XCM_REG_WU_DA_CNT_CMD01 				 0x201d8
#घोषणा XCM_REG_WU_DA_CNT_CMD10 				 0x201dc
#घोषणा XCM_REG_WU_DA_CNT_CMD11 				 0x201e0
#घोषणा XCM_REG_WU_DA_CNT_UPD_VAL00				 0x201e4
#घोषणा XCM_REG_WU_DA_CNT_UPD_VAL01				 0x201e8
#घोषणा XCM_REG_WU_DA_CNT_UPD_VAL10				 0x201ec
#घोषणा XCM_REG_WU_DA_CNT_UPD_VAL11				 0x201f0
#घोषणा XCM_REG_WU_DA_SET_TMR_CNT_FLG_CMD00			 0x201c4
#घोषणा XCM_REG_WU_DA_SET_TMR_CNT_FLG_CMD01			 0x201c8
#घोषणा XCM_REG_WU_DA_SET_TMR_CNT_FLG_CMD10			 0x201cc
#घोषणा XCM_REG_WU_DA_SET_TMR_CNT_FLG_CMD11			 0x201d0
/* [RW 1] CM - CFC Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा XCM_REG_XCM_CFC_IFEN					 0x20050
/* [RW 14] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा XCM_REG_XCM_INT_MASK					 0x202b4
/* [R 14] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा XCM_REG_XCM_INT_STS					 0x202a8
/* [RW 30] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा XCM_REG_XCM_PRTY_MASK					 0x202c4
/* [R 30] Parity रेजिस्टर #0 पढ़ो */
#घोषणा XCM_REG_XCM_PRTY_STS					 0x202b8
/* [RC 30] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा XCM_REG_XCM_PRTY_STS_CLR				 0x202bc

/* [RW 4] The size of AG context region 0 in REG-pairs. Designates the MS
   REG-pair number (e.g. अगर region 0 is 6 REG-pairs; the value should be 5).
   Is used to determine the number of the AG context REG-pairs written back;
   when the Reg1WbFlg isn't set. */
#घोषणा XCM_REG_XCM_REG0_SZ					 0x200f4
/* [RW 1] CM - STORM 0 Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा XCM_REG_XCM_STORM0_IFEN 				 0x20004
/* [RW 1] CM - STORM 1 Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा XCM_REG_XCM_STORM1_IFEN 				 0x20008
/* [RW 1] CM - Timers Interface enable. If 0 - the valid input is
   disregarded; acknowledge output is deनिश्चितed; all other संकेतs are
   treated as usual; अगर 1 - normal activity. */
#घोषणा XCM_REG_XCM_TM_IFEN					 0x20020
/* [RW 1] CM - QM Interface enable. If 0 - the acknowledge input is
   disregarded; valid is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा XCM_REG_XCM_XQM_IFEN					 0x2000c
/* [RW 1] If set the Q index; received from the QM is inserted to event ID. */
#घोषणा XCM_REG_XCM_XQM_USE_Q					 0x200f0
/* [RW 4] The value by which CFC updates the activity counter at QM bypass. */
#घोषणा XCM_REG_XQM_BYP_ACT_UPD 				 0x200fc
/* [RW 6] QM output initial credit. Max credit available - 32.Write ग_लिखोs
   the initial credit value; पढ़ो वापसs the current value of the credit
   counter. Must be initialized to 32 at start-up. */
#घोषणा XCM_REG_XQM_INIT_CRD					 0x20420
/* [RW 3] The weight of the QM (primary) input in the WRR mechanism. 0
   stands क्रम weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_XQM_P_WEIGHT					 0x200e4
/* [RW 3] The weight of the QM (secondary) input in the WRR mechanism. 0
   stands क्रम weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_XQM_S_WEIGHT					 0x200e8
/* [RW 28] The CM header value क्रम QM request (primary). */
#घोषणा XCM_REG_XQM_XCM_HDR_P					 0x200a0
/* [RW 28] The CM header value क्रम QM request (secondary). */
#घोषणा XCM_REG_XQM_XCM_HDR_S					 0x200a4
/* [RW 1] QM - CM Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा XCM_REG_XQM_XCM_IFEN					 0x20014
/* [RW 1] Input SDM Interface enable. If 0 - the valid input is disregarded;
   acknowledge output is deनिश्चितed; all other संकेतs are treated as usual;
   अगर 1 - normal activity. */
#घोषणा XCM_REG_XSDM_IFEN					 0x20018
/* [RC 1] Set at message length mismatch (relative to last indication) at
   the SDM पूर्णांकerface. */
#घोषणा XCM_REG_XSDM_LENGTH_MIS 				 0x20220
/* [RW 3] The weight of the SDM input in the WRR mechanism. 0 stands क्रम
   weight 8 (the most prioritised); 1 stands क्रम weight 1(least
   prioritised); 2 stands क्रम weight 2; tc. */
#घोषणा XCM_REG_XSDM_WEIGHT					 0x200e0
/* [RW 17] Indirect access to the descriptor table of the XX protection
   mechanism. The fields are: [5:0] - message length; 11:6] - message
   poपूर्णांकer; 16:12] - next poपूर्णांकer. */
#घोषणा XCM_REG_XX_DESCR_TABLE					 0x20480
#घोषणा XCM_REG_XX_DESCR_TABLE_SIZE				 32
/* [R 6] Used to पढ़ो the XX protection Free counter. */
#घोषणा XCM_REG_XX_FREE 					 0x20240
/* [RW 6] Initial value क्रम the credit counter; responsible क्रम fulfilling
   of the Input Stage XX protection buffer by the XX protection pending
   messages. Max credit available - 3.Write ग_लिखोs the initial credit value;
   पढ़ो वापसs the current value of the credit counter. Must be initialized
   to 2 at start-up. */
#घोषणा XCM_REG_XX_INIT_CRD					 0x20424
/* [RW 6] The maximum number of pending messages; which may be stored in XX
   protection. ~xcm_रेजिस्टरs_xx_मुक्त.xx_मुक्त पढ़ो on पढ़ो. */
#घोषणा XCM_REG_XX_MSG_NUM					 0x20428
/* [RW 8] The Event ID; sent to the STORM in हाल of XX overflow. */
#घोषणा XCM_REG_XX_OVFL_EVNT_ID 				 0x20058
#घोषणा XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_LOCAL_FAULT_STATUS	 (0x1<<0)
#घोषणा XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_REMOTE_FAULT_STATUS	 (0x1<<1)
#घोषणा XMAC_CTRL_REG_LINE_LOCAL_LPBK				 (0x1<<2)
#घोषणा XMAC_CTRL_REG_RX_EN					 (0x1<<1)
#घोषणा XMAC_CTRL_REG_SOFT_RESET				 (0x1<<6)
#घोषणा XMAC_CTRL_REG_TX_EN					 (0x1<<0)
#घोषणा XMAC_CTRL_REG_XLGMII_ALIGN_ENB				 (0x1<<7)
#घोषणा XMAC_PAUSE_CTRL_REG_RX_PAUSE_EN				 (0x1<<18)
#घोषणा XMAC_PAUSE_CTRL_REG_TX_PAUSE_EN				 (0x1<<17)
#घोषणा XMAC_PFC_CTRL_HI_REG_FORCE_PFC_XON			 (0x1<<1)
#घोषणा XMAC_PFC_CTRL_HI_REG_PFC_REFRESH_EN			 (0x1<<0)
#घोषणा XMAC_PFC_CTRL_HI_REG_PFC_STATS_EN			 (0x1<<3)
#घोषणा XMAC_PFC_CTRL_HI_REG_RX_PFC_EN				 (0x1<<4)
#घोषणा XMAC_PFC_CTRL_HI_REG_TX_PFC_EN				 (0x1<<5)
#घोषणा XMAC_REG_CLEAR_RX_LSS_STATUS				 0x60
#घोषणा XMAC_REG_CTRL						 0
/* [RW 16] Upper 48 bits of ctrl_sa रेजिस्टर. Used as the SA in PAUSE/PFC
 * packets transmitted by the MAC */
#घोषणा XMAC_REG_CTRL_SA_HI					 0x2c
/* [RW 32] Lower 48 bits of ctrl_sa रेजिस्टर. Used as the SA in PAUSE/PFC
 * packets transmitted by the MAC */
#घोषणा XMAC_REG_CTRL_SA_LO					 0x28
#घोषणा XMAC_REG_EEE_CTRL					 0xd8
#घोषणा XMAC_REG_EEE_TIMERS_HI					 0xe4
#घोषणा XMAC_REG_PAUSE_CTRL					 0x68
#घोषणा XMAC_REG_PFC_CTRL					 0x70
#घोषणा XMAC_REG_PFC_CTRL_HI					 0x74
#घोषणा XMAC_REG_RX_LSS_CTRL					 0x50
#घोषणा XMAC_REG_RX_LSS_STATUS					 0x58
/* [RW 14] Maximum packet size in receive direction; exclusive of preamble &
 * CRC in strip mode */
#घोषणा XMAC_REG_RX_MAX_SIZE					 0x40
#घोषणा XMAC_REG_TX_CTRL					 0x20
#घोषणा XMAC_RX_LSS_CTRL_REG_LOCAL_FAULT_DISABLE		 (0x1<<0)
#घोषणा XMAC_RX_LSS_CTRL_REG_REMOTE_FAULT_DISABLE		 (0x1<<1)
/* [RW 16] Indirect access to the XX table of the XX protection mechanism.
   The fields are:[4:0] - tail poपूर्णांकer; 9:5] - Link List size; 14:10] -
   header poपूर्णांकer. */
#घोषणा XCM_REG_XX_TABLE					 0x20500
/* [RW 8] The event id क्रम aggregated पूर्णांकerrupt 0 */
#घोषणा XSDM_REG_AGG_INT_EVENT_0				 0x166038
#घोषणा XSDM_REG_AGG_INT_EVENT_1				 0x16603c
#घोषणा XSDM_REG_AGG_INT_EVENT_10				 0x166060
#घोषणा XSDM_REG_AGG_INT_EVENT_11				 0x166064
#घोषणा XSDM_REG_AGG_INT_EVENT_12				 0x166068
#घोषणा XSDM_REG_AGG_INT_EVENT_13				 0x16606c
#घोषणा XSDM_REG_AGG_INT_EVENT_14				 0x166070
#घोषणा XSDM_REG_AGG_INT_EVENT_2				 0x166040
#घोषणा XSDM_REG_AGG_INT_EVENT_3				 0x166044
#घोषणा XSDM_REG_AGG_INT_EVENT_4				 0x166048
#घोषणा XSDM_REG_AGG_INT_EVENT_5				 0x16604c
#घोषणा XSDM_REG_AGG_INT_EVENT_6				 0x166050
#घोषणा XSDM_REG_AGG_INT_EVENT_7				 0x166054
#घोषणा XSDM_REG_AGG_INT_EVENT_8				 0x166058
#घोषणा XSDM_REG_AGG_INT_EVENT_9				 0x16605c
/* [RW 1] For each aggregated पूर्णांकerrupt index whether the mode is normal (0)
   or स्वतः-mask-mode (1) */
#घोषणा XSDM_REG_AGG_INT_MODE_0 				 0x1661b8
#घोषणा XSDM_REG_AGG_INT_MODE_1 				 0x1661bc
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the cfc_rsp lcid */
#घोषणा XSDM_REG_CFC_RSP_START_ADDR				 0x166008
/* [RW 16] The maximum value of the completion counter #0 */
#घोषणा XSDM_REG_CMP_COUNTER_MAX0				 0x16601c
/* [RW 16] The maximum value of the completion counter #1 */
#घोषणा XSDM_REG_CMP_COUNTER_MAX1				 0x166020
/* [RW 16] The maximum value of the completion counter #2 */
#घोषणा XSDM_REG_CMP_COUNTER_MAX2				 0x166024
/* [RW 16] The maximum value of the completion counter #3 */
#घोषणा XSDM_REG_CMP_COUNTER_MAX3				 0x166028
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम the completion
   counters. */
#घोषणा XSDM_REG_CMP_COUNTER_START_ADDR 			 0x16600c
#घोषणा XSDM_REG_ENABLE_IN1					 0x166238
#घोषणा XSDM_REG_ENABLE_IN2					 0x16623c
#घोषणा XSDM_REG_ENABLE_OUT1					 0x166240
#घोषणा XSDM_REG_ENABLE_OUT2					 0x166244
/* [RW 4] The initial number of messages that can be sent to the pxp control
   पूर्णांकerface without receiving any ACK. */
#घोषणा XSDM_REG_INIT_CREDIT_PXP_CTRL				 0x1664bc
/* [ST 32] The number of ACK after placement messages received */
#घोषणा XSDM_REG_NUM_OF_ACK_AFTER_PLACE 			 0x16627c
/* [ST 32] The number of packet end messages received from the parser */
#घोषणा XSDM_REG_NUM_OF_PKT_END_MSG				 0x166274
/* [ST 32] The number of requests received from the pxp async अगर */
#घोषणा XSDM_REG_NUM_OF_PXP_ASYNC_REQ				 0x166278
/* [ST 32] The number of commands received in queue 0 */
#घोषणा XSDM_REG_NUM_OF_Q0_CMD					 0x166248
/* [ST 32] The number of commands received in queue 10 */
#घोषणा XSDM_REG_NUM_OF_Q10_CMD 				 0x16626c
/* [ST 32] The number of commands received in queue 11 */
#घोषणा XSDM_REG_NUM_OF_Q11_CMD 				 0x166270
/* [ST 32] The number of commands received in queue 1 */
#घोषणा XSDM_REG_NUM_OF_Q1_CMD					 0x16624c
/* [ST 32] The number of commands received in queue 3 */
#घोषणा XSDM_REG_NUM_OF_Q3_CMD					 0x166250
/* [ST 32] The number of commands received in queue 4 */
#घोषणा XSDM_REG_NUM_OF_Q4_CMD					 0x166254
/* [ST 32] The number of commands received in queue 5 */
#घोषणा XSDM_REG_NUM_OF_Q5_CMD					 0x166258
/* [ST 32] The number of commands received in queue 6 */
#घोषणा XSDM_REG_NUM_OF_Q6_CMD					 0x16625c
/* [ST 32] The number of commands received in queue 7 */
#घोषणा XSDM_REG_NUM_OF_Q7_CMD					 0x166260
/* [ST 32] The number of commands received in queue 8 */
#घोषणा XSDM_REG_NUM_OF_Q8_CMD					 0x166264
/* [ST 32] The number of commands received in queue 9 */
#घोषणा XSDM_REG_NUM_OF_Q9_CMD					 0x166268
/* [RW 13] The start address in the पूर्णांकernal RAM क्रम queue counters */
#घोषणा XSDM_REG_Q_COUNTER_START_ADDR				 0x166010
/* [W 17] Generate an operation after completion; bit-16 is
 * AggVectIdx_valid; bits 15:8 are AggVectIdx; bits 7:5 are the TRIG and
 * bits 4:0 are the T124Param[4:0] */
#घोषणा XSDM_REG_OPERATION_GEN					 0x1664c4
/* [R 1] pxp_ctrl rd_data fअगरo empty in sdm_dma_rsp block */
#घोषणा XSDM_REG_RSP_PXP_CTRL_RDATA_EMPTY			 0x166548
/* [R 1] parser fअगरo empty in sdm_sync block */
#घोषणा XSDM_REG_SYNC_PARSER_EMPTY				 0x166550
/* [R 1] parser serial fअगरo empty in sdm_sync block */
#घोषणा XSDM_REG_SYNC_SYNC_EMPTY				 0x166558
/* [RW 32] Tick क्रम समयr counter. Applicable only when
   ~xsdm_रेजिस्टरs_समयr_tick_enable.समयr_tick_enable =1 */
#घोषणा XSDM_REG_TIMER_TICK					 0x166000
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा XSDM_REG_XSDM_INT_MASK_0				 0x16629c
#घोषणा XSDM_REG_XSDM_INT_MASK_1				 0x1662ac
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा XSDM_REG_XSDM_INT_STS_0 				 0x166290
#घोषणा XSDM_REG_XSDM_INT_STS_1 				 0x1662a0
/* [RW 11] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा XSDM_REG_XSDM_PRTY_MASK 				 0x1662bc
/* [R 11] Parity रेजिस्टर #0 पढ़ो */
#घोषणा XSDM_REG_XSDM_PRTY_STS					 0x1662b0
/* [RC 11] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा XSDM_REG_XSDM_PRTY_STS_CLR				 0x1662b4
/* [RW 5] The number of समय_slots in the arbitration cycle */
#घोषणा XSEM_REG_ARB_CYCLE_SIZE 				 0x280034
/* [RW 3] The source that is associated with arbitration element 0. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2 */
#घोषणा XSEM_REG_ARB_ELEMENT0					 0x280020
/* [RW 3] The source that is associated with arbitration element 1. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~xsem_रेजिस्टरs_arb_element0.arb_element0 */
#घोषणा XSEM_REG_ARB_ELEMENT1					 0x280024
/* [RW 3] The source that is associated with arbitration element 2. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~xsem_रेजिस्टरs_arb_element0.arb_element0
   and ~xsem_रेजिस्टरs_arb_element1.arb_element1 */
#घोषणा XSEM_REG_ARB_ELEMENT2					 0x280028
/* [RW 3] The source that is associated with arbitration element 3. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.Could
   not be equal to रेजिस्टर ~xsem_रेजिस्टरs_arb_element0.arb_element0 and
   ~xsem_रेजिस्टरs_arb_element1.arb_element1 and
   ~xsem_रेजिस्टरs_arb_element2.arb_element2 */
#घोषणा XSEM_REG_ARB_ELEMENT3					 0x28002c
/* [RW 3] The source that is associated with arbitration element 4. Source
   decoding is: 0- foc0; 1-fic1; 2-sleeping thपढ़ो with priority 0; 3-
   sleeping thपढ़ो with priority 1; 4- sleeping thपढ़ो with priority 2.
   Could not be equal to रेजिस्टर ~xsem_रेजिस्टरs_arb_element0.arb_element0
   and ~xsem_रेजिस्टरs_arb_element1.arb_element1 and
   ~xsem_रेजिस्टरs_arb_element2.arb_element2 and
   ~xsem_रेजिस्टरs_arb_element3.arb_element3 */
#घोषणा XSEM_REG_ARB_ELEMENT4					 0x280030
#घोषणा XSEM_REG_ENABLE_IN					 0x2800a4
#घोषणा XSEM_REG_ENABLE_OUT					 0x2800a8
/* [RW 32] This address space contains all रेजिस्टरs and memories that are
   placed in SEM_FAST block. The SEM_FAST रेजिस्टरs are described in
   appendix B. In order to access the sem_fast रेजिस्टरs the base address
   ~fast_memory.fast_memory should be added to eachsem_fast रेजिस्टर offset. */
#घोषणा XSEM_REG_FAST_MEMORY					 0x2a0000
/* [RW 1] Disables input messages from FIC0 May be updated during run_समय
   by the microcode */
#घोषणा XSEM_REG_FIC0_DISABLE					 0x280224
/* [RW 1] Disables input messages from FIC1 May be updated during run_समय
   by the microcode */
#घोषणा XSEM_REG_FIC1_DISABLE					 0x280234
/* [RW 15] Interrupt table Read and ग_लिखो access to it is not possible in
   the middle of the work */
#घोषणा XSEM_REG_INT_TABLE					 0x280400
/* [ST 24] Statistics रेजिस्टर. The number of messages that entered through
   FIC0 */
#घोषणा XSEM_REG_MSG_NUM_FIC0					 0x280000
/* [ST 24] Statistics रेजिस्टर. The number of messages that entered through
   FIC1 */
#घोषणा XSEM_REG_MSG_NUM_FIC1					 0x280004
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC0 */
#घोषणा XSEM_REG_MSG_NUM_FOC0					 0x280008
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC1 */
#घोषणा XSEM_REG_MSG_NUM_FOC1					 0x28000c
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC2 */
#घोषणा XSEM_REG_MSG_NUM_FOC2					 0x280010
/* [ST 24] Statistics रेजिस्टर. The number of messages that were sent to
   FOC3 */
#घोषणा XSEM_REG_MSG_NUM_FOC3					 0x280014
/* [RW 1] Disables input messages from the passive buffer May be updated
   during run_समय by the microcode */
#घोषणा XSEM_REG_PAS_DISABLE					 0x28024c
/* [WB 128] Debug only. Passive buffer memory */
#घोषणा XSEM_REG_PASSIVE_BUFFER 				 0x282000
/* [WB 46] pram memory. B45 is parity; b[44:0] - data. */
#घोषणा XSEM_REG_PRAM						 0x2c0000
/* [R 16] Valid sleeping thपढ़ोs indication have bit per thपढ़ो */
#घोषणा XSEM_REG_SLEEP_THREADS_VALID				 0x28026c
/* [R 1] EXT_STORE FIFO is empty in sem_slow_ls_ext */
#घोषणा XSEM_REG_SLOW_EXT_STORE_EMPTY				 0x2802a0
/* [RW 16] List of मुक्त thपढ़ोs . There is a bit per thपढ़ो. */
#घोषणा XSEM_REG_THREADS_LIST					 0x2802e4
/* [RW 3] The arbitration scheme of समय_slot 0 */
#घोषणा XSEM_REG_TS_0_AS					 0x280038
/* [RW 3] The arbitration scheme of समय_slot 10 */
#घोषणा XSEM_REG_TS_10_AS					 0x280060
/* [RW 3] The arbitration scheme of समय_slot 11 */
#घोषणा XSEM_REG_TS_11_AS					 0x280064
/* [RW 3] The arbitration scheme of समय_slot 12 */
#घोषणा XSEM_REG_TS_12_AS					 0x280068
/* [RW 3] The arbitration scheme of समय_slot 13 */
#घोषणा XSEM_REG_TS_13_AS					 0x28006c
/* [RW 3] The arbitration scheme of समय_slot 14 */
#घोषणा XSEM_REG_TS_14_AS					 0x280070
/* [RW 3] The arbitration scheme of समय_slot 15 */
#घोषणा XSEM_REG_TS_15_AS					 0x280074
/* [RW 3] The arbitration scheme of समय_slot 16 */
#घोषणा XSEM_REG_TS_16_AS					 0x280078
/* [RW 3] The arbitration scheme of समय_slot 17 */
#घोषणा XSEM_REG_TS_17_AS					 0x28007c
/* [RW 3] The arbitration scheme of समय_slot 18 */
#घोषणा XSEM_REG_TS_18_AS					 0x280080
/* [RW 3] The arbitration scheme of समय_slot 1 */
#घोषणा XSEM_REG_TS_1_AS					 0x28003c
/* [RW 3] The arbitration scheme of समय_slot 2 */
#घोषणा XSEM_REG_TS_2_AS					 0x280040
/* [RW 3] The arbitration scheme of समय_slot 3 */
#घोषणा XSEM_REG_TS_3_AS					 0x280044
/* [RW 3] The arbitration scheme of समय_slot 4 */
#घोषणा XSEM_REG_TS_4_AS					 0x280048
/* [RW 3] The arbitration scheme of समय_slot 5 */
#घोषणा XSEM_REG_TS_5_AS					 0x28004c
/* [RW 3] The arbitration scheme of समय_slot 6 */
#घोषणा XSEM_REG_TS_6_AS					 0x280050
/* [RW 3] The arbitration scheme of समय_slot 7 */
#घोषणा XSEM_REG_TS_7_AS					 0x280054
/* [RW 3] The arbitration scheme of समय_slot 8 */
#घोषणा XSEM_REG_TS_8_AS					 0x280058
/* [RW 3] The arbitration scheme of समय_slot 9 */
#घोषणा XSEM_REG_TS_9_AS					 0x28005c
/* [W 7] VF or PF ID क्रम reset error bit. Values 0-63 reset error bit क्रम 64
 * VF; values 64-67 reset error क्रम 4 PF; values 68-127 are not valid. */
#घोषणा XSEM_REG_VFPF_ERR_NUM					 0x280380
/* [RW 32] Interrupt mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा XSEM_REG_XSEM_INT_MASK_0				 0x280110
#घोषणा XSEM_REG_XSEM_INT_MASK_1				 0x280120
/* [R 32] Interrupt रेजिस्टर #0 पढ़ो */
#घोषणा XSEM_REG_XSEM_INT_STS_0 				 0x280104
#घोषणा XSEM_REG_XSEM_INT_STS_1 				 0x280114
/* [RW 32] Parity mask रेजिस्टर #0 पढ़ो/ग_लिखो */
#घोषणा XSEM_REG_XSEM_PRTY_MASK_0				 0x280130
#घोषणा XSEM_REG_XSEM_PRTY_MASK_1				 0x280140
/* [R 32] Parity रेजिस्टर #0 पढ़ो */
#घोषणा XSEM_REG_XSEM_PRTY_STS_0				 0x280124
#घोषणा XSEM_REG_XSEM_PRTY_STS_1				 0x280134
/* [RC 32] Parity रेजिस्टर #0 पढ़ो clear */
#घोषणा XSEM_REG_XSEM_PRTY_STS_CLR_0				 0x280128
#घोषणा XSEM_REG_XSEM_PRTY_STS_CLR_1				 0x280138
#घोषणा MCPR_ACCESS_LOCK_LOCK					 (1L<<31)
#घोषणा MCPR_NVM_ACCESS_ENABLE_EN				 (1L<<0)
#घोषणा MCPR_NVM_ACCESS_ENABLE_WR_EN				 (1L<<1)
#घोषणा MCPR_NVM_ADDR_NVM_ADDR_VALUE				 (0xffffffL<<0)
#घोषणा MCPR_NVM_CFG4_FLASH_SIZE				 (0x7L<<0)
#घोषणा MCPR_NVM_COMMAND_DOIT					 (1L<<4)
#घोषणा MCPR_NVM_COMMAND_DONE					 (1L<<3)
#घोषणा MCPR_NVM_COMMAND_FIRST					 (1L<<7)
#घोषणा MCPR_NVM_COMMAND_LAST					 (1L<<8)
#घोषणा MCPR_NVM_COMMAND_WR					 (1L<<5)
#घोषणा MCPR_NVM_SW_ARB_ARB_ARB1				 (1L<<9)
#घोषणा MCPR_NVM_SW_ARB_ARB_REQ_CLR1				 (1L<<5)
#घोषणा MCPR_NVM_SW_ARB_ARB_REQ_SET1				 (1L<<1)
#घोषणा BIGMAC_REGISTER_BMAC_CONTROL				 (0x00<<3)
#घोषणा BIGMAC_REGISTER_BMAC_XGXS_CONTROL			 (0x01<<3)
#घोषणा BIGMAC_REGISTER_CNT_MAX_SIZE				 (0x05<<3)
#घोषणा BIGMAC_REGISTER_RX_CONTROL				 (0x21<<3)
#घोषणा BIGMAC_REGISTER_RX_LLFC_MSG_FLDS			 (0x46<<3)
#घोषणा BIGMAC_REGISTER_RX_LSS_STATUS				 (0x43<<3)
#घोषणा BIGMAC_REGISTER_RX_MAX_SIZE				 (0x23<<3)
#घोषणा BIGMAC_REGISTER_RX_STAT_GR64				 (0x26<<3)
#घोषणा BIGMAC_REGISTER_RX_STAT_GRIPJ				 (0x42<<3)
#घोषणा BIGMAC_REGISTER_TX_CONTROL				 (0x07<<3)
#घोषणा BIGMAC_REGISTER_TX_MAX_SIZE				 (0x09<<3)
#घोषणा BIGMAC_REGISTER_TX_PAUSE_THRESHOLD			 (0x0A<<3)
#घोषणा BIGMAC_REGISTER_TX_SOURCE_ADDR				 (0x08<<3)
#घोषणा BIGMAC_REGISTER_TX_STAT_GTBYT				 (0x20<<3)
#घोषणा BIGMAC_REGISTER_TX_STAT_GTPKT				 (0x0C<<3)
#घोषणा BIGMAC2_REGISTER_BMAC_CONTROL				 (0x00<<3)
#घोषणा BIGMAC2_REGISTER_BMAC_XGXS_CONTROL			 (0x01<<3)
#घोषणा BIGMAC2_REGISTER_CNT_MAX_SIZE				 (0x05<<3)
#घोषणा BIGMAC2_REGISTER_PFC_CONTROL				 (0x06<<3)
#घोषणा BIGMAC2_REGISTER_RX_CONTROL				 (0x3A<<3)
#घोषणा BIGMAC2_REGISTER_RX_LLFC_MSG_FLDS			 (0x62<<3)
#घोषणा BIGMAC2_REGISTER_RX_LSS_STAT				 (0x3E<<3)
#घोषणा BIGMAC2_REGISTER_RX_MAX_SIZE				 (0x3C<<3)
#घोषणा BIGMAC2_REGISTER_RX_STAT_GR64				 (0x40<<3)
#घोषणा BIGMAC2_REGISTER_RX_STAT_GRIPJ				 (0x5f<<3)
#घोषणा BIGMAC2_REGISTER_RX_STAT_GRPP				 (0x51<<3)
#घोषणा BIGMAC2_REGISTER_TX_CONTROL				 (0x1C<<3)
#घोषणा BIGMAC2_REGISTER_TX_MAX_SIZE				 (0x1E<<3)
#घोषणा BIGMAC2_REGISTER_TX_PAUSE_CONTROL			 (0x20<<3)
#घोषणा BIGMAC2_REGISTER_TX_SOURCE_ADDR			 (0x1D<<3)
#घोषणा BIGMAC2_REGISTER_TX_STAT_GTBYT				 (0x39<<3)
#घोषणा BIGMAC2_REGISTER_TX_STAT_GTPOK				 (0x22<<3)
#घोषणा BIGMAC2_REGISTER_TX_STAT_GTPP				 (0x24<<3)
#घोषणा EMAC_LED_1000MB_OVERRIDE				 (1L<<1)
#घोषणा EMAC_LED_100MB_OVERRIDE 				 (1L<<2)
#घोषणा EMAC_LED_10MB_OVERRIDE					 (1L<<3)
#घोषणा EMAC_LED_2500MB_OVERRIDE				 (1L<<12)
#घोषणा EMAC_LED_OVERRIDE					 (1L<<0)
#घोषणा EMAC_LED_TRAFFIC					 (1L<<6)
#घोषणा EMAC_MDIO_COMM_COMMAND_ADDRESS				 (0L<<26)
#घोषणा EMAC_MDIO_COMM_COMMAND_READ_22				 (2L<<26)
#घोषणा EMAC_MDIO_COMM_COMMAND_READ_45				 (3L<<26)
#घोषणा EMAC_MDIO_COMM_COMMAND_WRITE_22				 (1L<<26)
#घोषणा EMAC_MDIO_COMM_COMMAND_WRITE_45 			 (1L<<26)
#घोषणा EMAC_MDIO_COMM_DATA					 (0xffffL<<0)
#घोषणा EMAC_MDIO_COMM_START_BUSY				 (1L<<29)
#घोषणा EMAC_MDIO_MODE_AUTO_POLL				 (1L<<4)
#घोषणा EMAC_MDIO_MODE_CLAUSE_45				 (1L<<31)
#घोषणा EMAC_MDIO_MODE_CLOCK_CNT				 (0x3ffL<<16)
#घोषणा EMAC_MDIO_MODE_CLOCK_CNT_BITSHIFT			 16
#घोषणा EMAC_MDIO_STATUS_10MB					 (1L<<1)
#घोषणा EMAC_MODE_25G_MODE					 (1L<<5)
#घोषणा EMAC_MODE_HALF_DUPLEX					 (1L<<1)
#घोषणा EMAC_MODE_PORT_GMII					 (2L<<2)
#घोषणा EMAC_MODE_PORT_MII					 (1L<<2)
#घोषणा EMAC_MODE_PORT_MII_10M					 (3L<<2)
#घोषणा EMAC_MODE_RESET 					 (1L<<0)
#घोषणा EMAC_REG_EMAC_LED					 0xc
#घोषणा EMAC_REG_EMAC_MAC_MATCH 				 0x10
#घोषणा EMAC_REG_EMAC_MDIO_COMM 				 0xac
#घोषणा EMAC_REG_EMAC_MDIO_MODE 				 0xb4
#घोषणा EMAC_REG_EMAC_MDIO_STATUS				 0xb0
#घोषणा EMAC_REG_EMAC_MODE					 0x0
#घोषणा EMAC_REG_EMAC_RX_MODE					 0xc8
#घोषणा EMAC_REG_EMAC_RX_MTU_SIZE				 0x9c
#घोषणा EMAC_REG_EMAC_RX_STAT_AC				 0x180
#घोषणा EMAC_REG_EMAC_RX_STAT_AC_28				 0x1f4
#घोषणा EMAC_REG_EMAC_RX_STAT_AC_COUNT				 23
#घोषणा EMAC_REG_EMAC_TX_MODE					 0xbc
#घोषणा EMAC_REG_EMAC_TX_STAT_AC				 0x280
#घोषणा EMAC_REG_EMAC_TX_STAT_AC_COUNT				 22
#घोषणा EMAC_REG_RX_PFC_MODE					 0x320
#घोषणा EMAC_REG_RX_PFC_MODE_PRIORITIES				 (1L<<2)
#घोषणा EMAC_REG_RX_PFC_MODE_RX_EN				 (1L<<1)
#घोषणा EMAC_REG_RX_PFC_MODE_TX_EN				 (1L<<0)
#घोषणा EMAC_REG_RX_PFC_PARAM					 0x324
#घोषणा EMAC_REG_RX_PFC_PARAM_OPCODE_BITSHIFT			 0
#घोषणा EMAC_REG_RX_PFC_PARAM_PRIORITY_EN_BITSHIFT		 16
#घोषणा EMAC_REG_RX_PFC_STATS_XOFF_RCVD				 0x328
#घोषणा EMAC_REG_RX_PFC_STATS_XOFF_RCVD_COUNT			 (0xffff<<0)
#घोषणा EMAC_REG_RX_PFC_STATS_XOFF_SENT				 0x330
#घोषणा EMAC_REG_RX_PFC_STATS_XOFF_SENT_COUNT			 (0xffff<<0)
#घोषणा EMAC_REG_RX_PFC_STATS_XON_RCVD				 0x32c
#घोषणा EMAC_REG_RX_PFC_STATS_XON_RCVD_COUNT			 (0xffff<<0)
#घोषणा EMAC_REG_RX_PFC_STATS_XON_SENT				 0x334
#घोषणा EMAC_REG_RX_PFC_STATS_XON_SENT_COUNT			 (0xffff<<0)
#घोषणा EMAC_RX_MODE_FLOW_EN					 (1L<<2)
#घोषणा EMAC_RX_MODE_KEEP_MAC_CONTROL				 (1L<<3)
#घोषणा EMAC_RX_MODE_KEEP_VLAN_TAG				 (1L<<10)
#घोषणा EMAC_RX_MODE_PROMISCUOUS				 (1L<<8)
#घोषणा EMAC_RX_MODE_RESET					 (1L<<0)
#घोषणा EMAC_RX_MTU_SIZE_JUMBO_ENA				 (1L<<31)
#घोषणा EMAC_TX_MODE_EXT_PAUSE_EN				 (1L<<3)
#घोषणा EMAC_TX_MODE_FLOW_EN					 (1L<<4)
#घोषणा EMAC_TX_MODE_RESET					 (1L<<0)
#घोषणा MISC_REGISTERS_GPIO_0					 0
#घोषणा MISC_REGISTERS_GPIO_1					 1
#घोषणा MISC_REGISTERS_GPIO_2					 2
#घोषणा MISC_REGISTERS_GPIO_3					 3
#घोषणा MISC_REGISTERS_GPIO_CLR_POS				 16
#घोषणा MISC_REGISTERS_GPIO_FLOAT				 (0xffL<<24)
#घोषणा MISC_REGISTERS_GPIO_FLOAT_POS				 24
#घोषणा MISC_REGISTERS_GPIO_HIGH				 1
#घोषणा MISC_REGISTERS_GPIO_INPUT_HI_Z				 2
#घोषणा MISC_REGISTERS_GPIO_INT_CLR_POS 			 24
#घोषणा MISC_REGISTERS_GPIO_INT_OUTPUT_CLR			 0
#घोषणा MISC_REGISTERS_GPIO_INT_OUTPUT_SET			 1
#घोषणा MISC_REGISTERS_GPIO_INT_SET_POS 			 16
#घोषणा MISC_REGISTERS_GPIO_LOW 				 0
#घोषणा MISC_REGISTERS_GPIO_OUTPUT_HIGH 			 1
#घोषणा MISC_REGISTERS_GPIO_OUTPUT_LOW				 0
#घोषणा MISC_REGISTERS_GPIO_PORT_SHIFT				 4
#घोषणा MISC_REGISTERS_GPIO_SET_POS				 8
#घोषणा MISC_REGISTERS_RESET_REG_1_CLEAR			 0x588
#घोषणा MISC_REGISTERS_RESET_REG_1_RST_BRB1			 (0x1<<0)
#घोषणा MISC_REGISTERS_RESET_REG_1_RST_DORQ			 (0x1<<19)
#घोषणा MISC_REGISTERS_RESET_REG_1_RST_HC			 (0x1<<29)
#घोषणा MISC_REGISTERS_RESET_REG_1_RST_NIG			 (0x1<<7)
#घोषणा MISC_REGISTERS_RESET_REG_1_RST_PXP			 (0x1<<26)
#घोषणा MISC_REGISTERS_RESET_REG_1_RST_PXPV			 (0x1<<27)
#घोषणा MISC_REGISTERS_RESET_REG_1_RST_XSEM			 (0x1<<22)
#घोषणा MISC_REGISTERS_RESET_REG_1_SET				 0x584
#घोषणा MISC_REGISTERS_RESET_REG_2_CLEAR			 0x598
#घोषणा MISC_REGISTERS_RESET_REG_2_MSTAT0			 (0x1<<24)
#घोषणा MISC_REGISTERS_RESET_REG_2_MSTAT1			 (0x1<<25)
#घोषणा MISC_REGISTERS_RESET_REG_2_PGLC				 (0x1<<19)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_ATC			 (0x1<<17)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_BMAC0			 (0x1<<0)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_BMAC1			 (0x1<<1)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_EMAC0			 (0x1<<2)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_EMAC0_HARD_CORE		 (0x1<<14)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_EMAC1			 (0x1<<3)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_EMAC1_HARD_CORE		 (0x1<<15)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_GRC			 (0x1<<4)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_MCP_N_HARD_CORE_RST_B	 (0x1<<6)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_MCP_N_RESET_CMN_CORE	 (0x1<<8)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_MCP_N_RESET_CMN_CPU	 (0x1<<7)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_MCP_N_RESET_REG_HARD_CORE (0x1<<5)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_MDIO			 (0x1<<13)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_MISC_CORE		 (0x1<<11)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_PCI_MDIO			 (0x1<<13)
#घोषणा MISC_REGISTERS_RESET_REG_2_RST_RBCN			 (0x1<<9)
#घोषणा MISC_REGISTERS_RESET_REG_2_SET				 0x594
#घोषणा MISC_REGISTERS_RESET_REG_2_UMAC0			 (0x1<<20)
#घोषणा MISC_REGISTERS_RESET_REG_2_UMAC1			 (0x1<<21)
#घोषणा MISC_REGISTERS_RESET_REG_2_XMAC				 (0x1<<22)
#घोषणा MISC_REGISTERS_RESET_REG_2_XMAC_SOFT			 (0x1<<23)
#घोषणा MISC_REGISTERS_RESET_REG_3_CLEAR			 0x5a8
#घोषणा MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_SERDES0_IDDQ	 (0x1<<1)
#घोषणा MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_SERDES0_PWRDWN	 (0x1<<2)
#घोषणा MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_SERDES0_PWRDWN_SD (0x1<<3)
#घोषणा MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_SERDES0_RSTB_HW  (0x1<<0)
#घोषणा MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_IDDQ	 (0x1<<5)
#घोषणा MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_PWRDWN	 (0x1<<6)
#घोषणा MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_PWRDWN_SD  (0x1<<7)
#घोषणा MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_RSTB_HW	 (0x1<<4)
#घोषणा MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_TXD_FIFO_RSTB (0x1<<8)
#घोषणा MISC_REGISTERS_RESET_REG_3_SET				 0x5a4
#घोषणा MISC_REGISTERS_SPIO_4					 4
#घोषणा MISC_REGISTERS_SPIO_5					 5
#घोषणा MISC_REGISTERS_SPIO_7					 7
#घोषणा MISC_REGISTERS_SPIO_CLR_POS				 16
#घोषणा MISC_REGISTERS_SPIO_FLOAT				 (0xffL<<24)
#घोषणा MISC_REGISTERS_SPIO_FLOAT_POS				 24
#घोषणा MISC_REGISTERS_SPIO_INPUT_HI_Z				 2
#घोषणा MISC_REGISTERS_SPIO_INT_OLD_SET_POS			 16
#घोषणा MISC_REGISTERS_SPIO_OUTPUT_HIGH 			 1
#घोषणा MISC_REGISTERS_SPIO_OUTPUT_LOW				 0
#घोषणा MISC_REGISTERS_SPIO_SET_POS				 8
#घोषणा MISC_SPIO_CLR_POS					 16
#घोषणा MISC_SPIO_FLOAT					 (0xffL<<24)
#घोषणा MISC_SPIO_FLOAT_POS					 24
#घोषणा MISC_SPIO_INPUT_HI_Z					 2
#घोषणा MISC_SPIO_INT_OLD_SET_POS				 16
#घोषणा MISC_SPIO_OUTPUT_HIGH					 1
#घोषणा MISC_SPIO_OUTPUT_LOW					 0
#घोषणा MISC_SPIO_SET_POS					 8
#घोषणा MISC_SPIO_SPIO4					 0x10
#घोषणा MISC_SPIO_SPIO5					 0x20
#घोषणा HW_LOCK_MAX_RESOURCE_VALUE				 31
#घोषणा HW_LOCK_RESOURCE_DCBX_ADMIN_MIB				 13
#घोषणा HW_LOCK_RESOURCE_DRV_FLAGS				 10
#घोषणा HW_LOCK_RESOURCE_GPIO					 1
#घोषणा HW_LOCK_RESOURCE_MDIO					 0
#घोषणा HW_LOCK_RESOURCE_NVRAM					 12
#घोषणा HW_LOCK_RESOURCE_PORT0_ATT_MASK				 3
#घोषणा HW_LOCK_RESOURCE_RECOVERY_LEADER_0			 8
#घोषणा HW_LOCK_RESOURCE_RECOVERY_LEADER_1			 9
#घोषणा HW_LOCK_RESOURCE_RECOVERY_REG				 11
#घोषणा HW_LOCK_RESOURCE_RESET					 5
#घोषणा HW_LOCK_RESOURCE_SPIO					 2
#घोषणा AEU_INPUTS_ATTN_BITS_ATC_HW_INTERRUPT			 (0x1<<4)
#घोषणा AEU_INPUTS_ATTN_BITS_ATC_PARITY_ERROR			 (0x1<<5)
#घोषणा AEU_INPUTS_ATTN_BITS_BRB_HW_INTERRUPT			 (0x1<<19)
#घोषणा AEU_INPUTS_ATTN_BITS_BRB_PARITY_ERROR			 (0x1<<18)
#घोषणा AEU_INPUTS_ATTN_BITS_CCM_HW_INTERRUPT			 (0x1<<31)
#घोषणा AEU_INPUTS_ATTN_BITS_CCM_PARITY_ERROR			 (0x1<<30)
#घोषणा AEU_INPUTS_ATTN_BITS_CDU_HW_INTERRUPT			 (0x1<<9)
#घोषणा AEU_INPUTS_ATTN_BITS_CDU_PARITY_ERROR			 (0x1<<8)
#घोषणा AEU_INPUTS_ATTN_BITS_CFC_HW_INTERRUPT			 (0x1<<7)
#घोषणा AEU_INPUTS_ATTN_BITS_CFC_PARITY_ERROR			 (0x1<<6)
#घोषणा AEU_INPUTS_ATTN_BITS_CSDM_HW_INTERRUPT			 (0x1<<29)
#घोषणा AEU_INPUTS_ATTN_BITS_CSDM_PARITY_ERROR			 (0x1<<28)
#घोषणा AEU_INPUTS_ATTN_BITS_CSEMI_HW_INTERRUPT			 (0x1<<1)
#घोषणा AEU_INPUTS_ATTN_BITS_CSEMI_PARITY_ERROR			 (0x1<<0)
#घोषणा AEU_INPUTS_ATTN_BITS_DEBUG_PARITY_ERROR			 (0x1<<18)
#घोषणा AEU_INPUTS_ATTN_BITS_DMAE_HW_INTERRUPT			 (0x1<<11)
#घोषणा AEU_INPUTS_ATTN_BITS_DMAE_PARITY_ERROR			 (0x1<<10)
#घोषणा AEU_INPUTS_ATTN_BITS_DOORBELLQ_HW_INTERRUPT		 (0x1<<13)
#घोषणा AEU_INPUTS_ATTN_BITS_DOORBELLQ_PARITY_ERROR		 (0x1<<12)
#घोषणा AEU_INPUTS_ATTN_BITS_GPIO0_FUNCTION_0			 (0x1<<2)
#घोषणा AEU_INPUTS_ATTN_BITS_IGU_PARITY_ERROR			 (0x1<<12)
#घोषणा AEU_INPUTS_ATTN_BITS_MCP_LATCHED_ROM_PARITY		 (0x1<<28)
#घोषणा AEU_INPUTS_ATTN_BITS_MCP_LATCHED_SCPAD_PARITY		 (0x1<<31)
#घोषणा AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_RX_PARITY		 (0x1<<29)
#घोषणा AEU_INPUTS_ATTN_BITS_MCP_LATCHED_UMP_TX_PARITY		 (0x1<<30)
#घोषणा AEU_INPUTS_ATTN_BITS_MISC_HW_INTERRUPT			 (0x1<<15)
#घोषणा AEU_INPUTS_ATTN_BITS_MISC_PARITY_ERROR			 (0x1<<14)
#घोषणा AEU_INPUTS_ATTN_BITS_NIG_PARITY_ERROR			 (0x1<<14)
#घोषणा AEU_INPUTS_ATTN_BITS_PARSER_PARITY_ERROR		 (0x1<<20)
#घोषणा AEU_INPUTS_ATTN_BITS_PBCLIENT_HW_INTERRUPT		 (0x1<<31)
#घोषणा AEU_INPUTS_ATTN_BITS_PBCLIENT_PARITY_ERROR		 (0x1<<30)
#घोषणा AEU_INPUTS_ATTN_BITS_PBF_PARITY_ERROR			 (0x1<<0)
#घोषणा AEU_INPUTS_ATTN_BITS_PGLUE_HW_INTERRUPT			 (0x1<<2)
#घोषणा AEU_INPUTS_ATTN_BITS_PGLUE_PARITY_ERROR			 (0x1<<3)
#घोषणा AEU_INPUTS_ATTN_BITS_PXPPCICLOCKCLIENT_HW_INTERRUPT	 (0x1<<5)
#घोषणा AEU_INPUTS_ATTN_BITS_PXPPCICLOCKCLIENT_PARITY_ERROR	 (0x1<<4)
#घोषणा AEU_INPUTS_ATTN_BITS_PXP_HW_INTERRUPT			 (0x1<<3)
#घोषणा AEU_INPUTS_ATTN_BITS_PXP_PARITY_ERROR			 (0x1<<2)
#घोषणा AEU_INPUTS_ATTN_BITS_QM_HW_INTERRUPT			 (0x1<<3)
#घोषणा AEU_INPUTS_ATTN_BITS_QM_PARITY_ERROR			 (0x1<<2)
#घोषणा AEU_INPUTS_ATTN_BITS_SEARCHER_PARITY_ERROR		 (0x1<<22)
#घोषणा AEU_INPUTS_ATTN_BITS_SPIO5				 (0x1<<15)
#घोषणा AEU_INPUTS_ATTN_BITS_TCM_HW_INTERRUPT			 (0x1<<27)
#घोषणा AEU_INPUTS_ATTN_BITS_TCM_PARITY_ERROR			 (0x1<<26)
#घोषणा AEU_INPUTS_ATTN_BITS_TIMERS_HW_INTERRUPT		 (0x1<<5)
#घोषणा AEU_INPUTS_ATTN_BITS_TIMERS_PARITY_ERROR		 (0x1<<4)
#घोषणा AEU_INPUTS_ATTN_BITS_TSDM_HW_INTERRUPT			 (0x1<<25)
#घोषणा AEU_INPUTS_ATTN_BITS_TSDM_PARITY_ERROR			 (0x1<<24)
#घोषणा AEU_INPUTS_ATTN_BITS_TSEMI_HW_INTERRUPT			 (0x1<<29)
#घोषणा AEU_INPUTS_ATTN_BITS_TSEMI_PARITY_ERROR			 (0x1<<28)
#घोषणा AEU_INPUTS_ATTN_BITS_UCM_HW_INTERRUPT			 (0x1<<23)
#घोषणा AEU_INPUTS_ATTN_BITS_UCM_PARITY_ERROR			 (0x1<<22)
#घोषणा AEU_INPUTS_ATTN_BITS_UPB_HW_INTERRUPT			 (0x1<<27)
#घोषणा AEU_INPUTS_ATTN_BITS_UPB_PARITY_ERROR			 (0x1<<26)
#घोषणा AEU_INPUTS_ATTN_BITS_USDM_HW_INTERRUPT			 (0x1<<21)
#घोषणा AEU_INPUTS_ATTN_BITS_USDM_PARITY_ERROR			 (0x1<<20)
#घोषणा AEU_INPUTS_ATTN_BITS_USEMI_HW_INTERRUPT			 (0x1<<25)
#घोषणा AEU_INPUTS_ATTN_BITS_USEMI_PARITY_ERROR			 (0x1<<24)
#घोषणा AEU_INPUTS_ATTN_BITS_VAUX_PCI_CORE_PARITY_ERROR		 (0x1<<16)
#घोषणा AEU_INPUTS_ATTN_BITS_XCM_HW_INTERRUPT			 (0x1<<9)
#घोषणा AEU_INPUTS_ATTN_BITS_XCM_PARITY_ERROR			 (0x1<<8)
#घोषणा AEU_INPUTS_ATTN_BITS_XSDM_HW_INTERRUPT			 (0x1<<7)
#घोषणा AEU_INPUTS_ATTN_BITS_XSDM_PARITY_ERROR			 (0x1<<6)
#घोषणा AEU_INPUTS_ATTN_BITS_XSEMI_HW_INTERRUPT			 (0x1<<11)
#घोषणा AEU_INPUTS_ATTN_BITS_XSEMI_PARITY_ERROR			 (0x1<<10)

#घोषणा AEU_INPUTS_ATTN_BITS_GPIO3_FUNCTION_0			(0x1<<5)
#घोषणा AEU_INPUTS_ATTN_BITS_GPIO3_FUNCTION_1			(0x1<<9)

#घोषणा RESERVED_GENERAL_ATTENTION_BIT_0	0

#घोषणा EVEREST_GEN_ATTN_IN_USE_MASK		0x7ffe0
#घोषणा EVEREST_LATCHED_ATTN_IN_USE_MASK	0xffe00000

#घोषणा RESERVED_GENERAL_ATTENTION_BIT_6	6
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_7	7
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_8	8
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_9	9
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_10	10
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_11	11
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_12	12
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_13	13
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_14	14
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_15	15
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_16	16
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_17	17
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_18	18
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_19	19
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_20	20
#घोषणा RESERVED_GENERAL_ATTENTION_BIT_21	21

/* storm निश्चितs attention bits */
#घोषणा TSTORM_FATAL_ASSERT_ATTENTION_BIT     RESERVED_GENERAL_ATTENTION_BIT_7
#घोषणा USTORM_FATAL_ASSERT_ATTENTION_BIT     RESERVED_GENERAL_ATTENTION_BIT_8
#घोषणा CSTORM_FATAL_ASSERT_ATTENTION_BIT     RESERVED_GENERAL_ATTENTION_BIT_9
#घोषणा XSTORM_FATAL_ASSERT_ATTENTION_BIT     RESERVED_GENERAL_ATTENTION_BIT_10

/* mcp error attention bit */
#घोषणा MCP_FATAL_ASSERT_ATTENTION_BIT	      RESERVED_GENERAL_ATTENTION_BIT_11

/*E1H NIG status sync attention mapped to group 4-7*/
#घोषणा LINK_SYNC_ATTENTION_BIT_FUNC_0	    RESERVED_GENERAL_ATTENTION_BIT_12
#घोषणा LINK_SYNC_ATTENTION_BIT_FUNC_1	    RESERVED_GENERAL_ATTENTION_BIT_13
#घोषणा LINK_SYNC_ATTENTION_BIT_FUNC_2	    RESERVED_GENERAL_ATTENTION_BIT_14
#घोषणा LINK_SYNC_ATTENTION_BIT_FUNC_3	    RESERVED_GENERAL_ATTENTION_BIT_15
#घोषणा LINK_SYNC_ATTENTION_BIT_FUNC_4	    RESERVED_GENERAL_ATTENTION_BIT_16
#घोषणा LINK_SYNC_ATTENTION_BIT_FUNC_5	    RESERVED_GENERAL_ATTENTION_BIT_17
#घोषणा LINK_SYNC_ATTENTION_BIT_FUNC_6	    RESERVED_GENERAL_ATTENTION_BIT_18
#घोषणा LINK_SYNC_ATTENTION_BIT_FUNC_7	    RESERVED_GENERAL_ATTENTION_BIT_19


#घोषणा LATCHED_ATTN_RBCR			23
#घोषणा LATCHED_ATTN_RBCT			24
#घोषणा LATCHED_ATTN_RBCN			25
#घोषणा LATCHED_ATTN_RBCU			26
#घोषणा LATCHED_ATTN_RBCP			27
#घोषणा LATCHED_ATTN_TIMEOUT_GRC		28
#घोषणा LATCHED_ATTN_RSVD_GRC			29
#घोषणा LATCHED_ATTN_ROM_PARITY_MCP		30
#घोषणा LATCHED_ATTN_UM_RX_PARITY_MCP		31
#घोषणा LATCHED_ATTN_UM_TX_PARITY_MCP		32
#घोषणा LATCHED_ATTN_SCPAD_PARITY_MCP		33

#घोषणा GENERAL_ATTEN_WORD(atten_name)	       ((94 + atten_name) / 32)
#घोषणा GENERAL_ATTEN_OFFSET(atten_name)\
	(1UL << ((94 + atten_name) % 32))
/*
 * This file defines GRC base address क्रम every block.
 * This file is included by chipsim, यंत्र microcode and cpp microcode.
 * These values are used in Design.xml on regBase attribute
 * Use the base with the generated offsets of specअगरic रेजिस्टरs.
 */

#घोषणा GRCBASE_PXPCS		0x000000
#घोषणा GRCBASE_PCICONFIG	0x002000
#घोषणा GRCBASE_PCIREG		0x002400
#घोषणा GRCBASE_EMAC0		0x008000
#घोषणा GRCBASE_EMAC1		0x008400
#घोषणा GRCBASE_DBU		0x008800
#घोषणा GRCBASE_MISC		0x00A000
#घोषणा GRCBASE_DBG		0x00C000
#घोषणा GRCBASE_NIG		0x010000
#घोषणा GRCBASE_XCM		0x020000
#घोषणा GRCBASE_PRS		0x040000
#घोषणा GRCBASE_SRCH		0x040400
#घोषणा GRCBASE_TSDM		0x042000
#घोषणा GRCBASE_TCM		0x050000
#घोषणा GRCBASE_BRB1		0x060000
#घोषणा GRCBASE_MCP		0x080000
#घोषणा GRCBASE_UPB		0x0C1000
#घोषणा GRCBASE_CSDM		0x0C2000
#घोषणा GRCBASE_USDM		0x0C4000
#घोषणा GRCBASE_CCM		0x0D0000
#घोषणा GRCBASE_UCM		0x0E0000
#घोषणा GRCBASE_CDU		0x101000
#घोषणा GRCBASE_DMAE		0x102000
#घोषणा GRCBASE_PXP		0x103000
#घोषणा GRCBASE_CFC		0x104000
#घोषणा GRCBASE_HC		0x108000
#घोषणा GRCBASE_PXP2		0x120000
#घोषणा GRCBASE_PBF		0x140000
#घोषणा GRCBASE_UMAC0		0x160000
#घोषणा GRCBASE_UMAC1		0x160400
#घोषणा GRCBASE_XPB		0x161000
#घोषणा GRCBASE_MSTAT0	    0x162000
#घोषणा GRCBASE_MSTAT1	    0x162800
#घोषणा GRCBASE_XMAC0		0x163000
#घोषणा GRCBASE_XMAC1		0x163800
#घोषणा GRCBASE_TIMERS		0x164000
#घोषणा GRCBASE_XSDM		0x166000
#घोषणा GRCBASE_QM		0x168000
#घोषणा GRCBASE_DQ		0x170000
#घोषणा GRCBASE_TSEM		0x180000
#घोषणा GRCBASE_CSEM		0x200000
#घोषणा GRCBASE_XSEM		0x280000
#घोषणा GRCBASE_USEM		0x300000
#घोषणा GRCBASE_MISC_AEU	GRCBASE_MISC


/* offset of configuration space in the pci core रेजिस्टर */
#घोषणा PCICFG_OFFSET					0x2000
#घोषणा PCICFG_VENDOR_ID_OFFSET 			0x00
#घोषणा PCICFG_DEVICE_ID_OFFSET 			0x02
#घोषणा PCICFG_COMMAND_OFFSET				0x04
#घोषणा PCICFG_COMMAND_IO_SPACE 		(1<<0)
#घोषणा PCICFG_COMMAND_MEM_SPACE		(1<<1)
#घोषणा PCICFG_COMMAND_BUS_MASTER		(1<<2)
#घोषणा PCICFG_COMMAND_SPECIAL_CYCLES		(1<<3)
#घोषणा PCICFG_COMMAND_MWI_CYCLES		(1<<4)
#घोषणा PCICFG_COMMAND_VGA_SNOOP		(1<<5)
#घोषणा PCICFG_COMMAND_PERR_ENA 		(1<<6)
#घोषणा PCICFG_COMMAND_STEPPING 		(1<<7)
#घोषणा PCICFG_COMMAND_SERR_ENA 		(1<<8)
#घोषणा PCICFG_COMMAND_FAST_B2B 		(1<<9)
#घोषणा PCICFG_COMMAND_INT_DISABLE		(1<<10)
#घोषणा PCICFG_COMMAND_RESERVED 		(0x1f<<11)
#घोषणा PCICFG_STATUS_OFFSET				0x06
#घोषणा PCICFG_REVISION_ID_OFFSET			0x08
#घोषणा PCICFG_REVESION_ID_MASK			0xff
#घोषणा PCICFG_REVESION_ID_ERROR_VAL		0xff
#घोषणा PCICFG_CACHE_LINE_SIZE				0x0c
#घोषणा PCICFG_LATENCY_TIMER				0x0d
#घोषणा PCICFG_BAR_1_LOW				0x10
#घोषणा PCICFG_BAR_1_HIGH				0x14
#घोषणा PCICFG_BAR_2_LOW				0x18
#घोषणा PCICFG_BAR_2_HIGH				0x1c
#घोषणा PCICFG_SUBSYSTEM_VENDOR_ID_OFFSET		0x2c
#घोषणा PCICFG_SUBSYSTEM_ID_OFFSET			0x2e
#घोषणा PCICFG_INT_LINE 				0x3c
#घोषणा PCICFG_INT_PIN					0x3d
#घोषणा PCICFG_PM_CAPABILITY				0x48
#घोषणा PCICFG_PM_CAPABILITY_VERSION		(0x3<<16)
#घोषणा PCICFG_PM_CAPABILITY_CLOCK		(1<<19)
#घोषणा PCICFG_PM_CAPABILITY_RESERVED		(1<<20)
#घोषणा PCICFG_PM_CAPABILITY_DSI		(1<<21)
#घोषणा PCICFG_PM_CAPABILITY_AUX_CURRENT	(0x7<<22)
#घोषणा PCICFG_PM_CAPABILITY_D1_SUPPORT 	(1<<25)
#घोषणा PCICFG_PM_CAPABILITY_D2_SUPPORT 	(1<<26)
#घोषणा PCICFG_PM_CAPABILITY_PME_IN_D0		(1<<27)
#घोषणा PCICFG_PM_CAPABILITY_PME_IN_D1		(1<<28)
#घोषणा PCICFG_PM_CAPABILITY_PME_IN_D2		(1<<29)
#घोषणा PCICFG_PM_CAPABILITY_PME_IN_D3_HOT	(1<<30)
#घोषणा PCICFG_PM_CAPABILITY_PME_IN_D3_COLD	(1<<31)
#घोषणा PCICFG_PM_CSR_OFFSET				0x4c
#घोषणा PCICFG_PM_CSR_STATE			(0x3<<0)
#घोषणा PCICFG_PM_CSR_PME_ENABLE		(1<<8)
#घोषणा PCICFG_PM_CSR_PME_STATUS		(1<<15)
#घोषणा PCICFG_MSI_CAP_ID_OFFSET			0x58
#घोषणा PCICFG_MSI_CONTROL_ENABLE		(0x1<<16)
#घोषणा PCICFG_MSI_CONTROL_MCAP 		(0x7<<17)
#घोषणा PCICFG_MSI_CONTROL_MENA 		(0x7<<20)
#घोषणा PCICFG_MSI_CONTROL_64_BIT_ADDR_CAP	(0x1<<23)
#घोषणा PCICFG_MSI_CONTROL_MSI_PVMASK_CAPABLE	(0x1<<24)
#घोषणा PCICFG_GRC_ADDRESS				0x78
#घोषणा PCICFG_GRC_DATA				0x80
#घोषणा PCICFG_ME_REGISTER				0x98
#घोषणा PCICFG_MSIX_CAP_ID_OFFSET			0xa0
#घोषणा PCICFG_MSIX_CONTROL_TABLE_SIZE		(0x7ff<<16)
#घोषणा PCICFG_MSIX_CONTROL_RESERVED		(0x7<<27)
#घोषणा PCICFG_MSIX_CONTROL_FUNC_MASK		(0x1<<30)
#घोषणा PCICFG_MSIX_CONTROL_MSIX_ENABLE 	(0x1<<31)

#घोषणा PCICFG_DEVICE_CONTROL				0xb4
#घोषणा PCICFG_DEVICE_STATUS				0xb6
#घोषणा PCICFG_DEVICE_STATUS_CORR_ERR_DET	(1<<0)
#घोषणा PCICFG_DEVICE_STATUS_NON_FATAL_ERR_DET	(1<<1)
#घोषणा PCICFG_DEVICE_STATUS_FATAL_ERR_DET	(1<<2)
#घोषणा PCICFG_DEVICE_STATUS_UNSUP_REQ_DET	(1<<3)
#घोषणा PCICFG_DEVICE_STATUS_AUX_PWR_DET	(1<<4)
#घोषणा PCICFG_DEVICE_STATUS_NO_PEND		(1<<5)
#घोषणा PCICFG_LINK_CONTROL				0xbc


#घोषणा BAR_USTRORM_INTMEM				0x400000
#घोषणा BAR_CSTRORM_INTMEM				0x410000
#घोषणा BAR_XSTRORM_INTMEM				0x420000
#घोषणा BAR_TSTRORM_INTMEM				0x430000

/* क्रम accessing the IGU in हाल of status block ACK */
#घोषणा BAR_IGU_INTMEM					0x440000

#घोषणा BAR_DOORBELL_OFFSET				0x800000

#घोषणा BAR_ME_REGISTER 				0x450000

/* config_2 offset */
#घोषणा GRC_CONFIG_2_SIZE_REG				0x408
#घोषणा PCI_CONFIG_2_BAR1_SIZE			(0xfL<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_DISABLED 	(0L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_64K		(1L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_128K		(2L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_256K		(3L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_512K		(4L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_1M		(5L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_2M		(6L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_4M		(7L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_8M		(8L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_16M		(9L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_32M		(10L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_64M		(11L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_128M		(12L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_256M		(13L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_512M		(14L<<0)
#घोषणा PCI_CONFIG_2_BAR1_SIZE_1G		(15L<<0)
#घोषणा PCI_CONFIG_2_BAR1_64ENA 		(1L<<4)
#घोषणा PCI_CONFIG_2_EXP_ROM_RETRY		(1L<<5)
#घोषणा PCI_CONFIG_2_CFG_CYCLE_RETRY		(1L<<6)
#घोषणा PCI_CONFIG_2_FIRST_CFG_DONE		(1L<<7)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE		(0xffL<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_DISABLED	(0L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_2K		(1L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_4K		(2L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_8K		(3L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_16K		(4L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_32K		(5L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_64K		(6L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_128K		(7L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_256K		(8L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_512K		(9L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_1M		(10L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_2M		(11L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_4M		(12L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_8M		(13L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_16M		(14L<<8)
#घोषणा PCI_CONFIG_2_EXP_ROM_SIZE_32M		(15L<<8)
#घोषणा PCI_CONFIG_2_BAR_PREFETCH		(1L<<16)
#घोषणा PCI_CONFIG_2_RESERVED0			(0x7fffL<<17)

/* config_3 offset */
#घोषणा GRC_CONFIG_3_SIZE_REG				0x40c
#घोषणा PCI_CONFIG_3_STICKY_BYTE		(0xffL<<0)
#घोषणा PCI_CONFIG_3_FORCE_PME			(1L<<24)
#घोषणा PCI_CONFIG_3_PME_STATUS 		(1L<<25)
#घोषणा PCI_CONFIG_3_PME_ENABLE 		(1L<<26)
#घोषणा PCI_CONFIG_3_PM_STATE			(0x3L<<27)
#घोषणा PCI_CONFIG_3_VAUX_PRESET		(1L<<30)
#घोषणा PCI_CONFIG_3_PCI_POWER			(1L<<31)

#घोषणा GRC_BAR2_CONFIG 				0x4e0
#घोषणा PCI_CONFIG_2_BAR2_SIZE			(0xfL<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_DISABLED 	(0L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_64K		(1L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_128K		(2L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_256K		(3L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_512K		(4L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_1M		(5L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_2M		(6L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_4M		(7L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_8M		(8L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_16M		(9L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_32M		(10L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_64M		(11L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_128M		(12L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_256M		(13L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_512M		(14L<<0)
#घोषणा PCI_CONFIG_2_BAR2_SIZE_1G		(15L<<0)
#घोषणा PCI_CONFIG_2_BAR2_64ENA 		(1L<<4)

#घोषणा PCI_PM_DATA_A					0x410
#घोषणा PCI_PM_DATA_B					0x414
#घोषणा PCI_ID_VAL1					0x434
#घोषणा PCI_ID_VAL2					0x438
#घोषणा PCI_ID_VAL3					0x43c

#घोषणा GRC_CONFIG_REG_VF_MSIX_CONTROL		    0x61C
#घोषणा GRC_CONFIG_REG_PF_INIT_VF		0x624
#घोषणा GRC_CR_PF_INIT_VF_PF_FIRST_VF_NUM_MASK	0xf
/* First VF_NUM क्रम PF is encoded in this रेजिस्टर.
 * The number of VFs asचिन्हित to a PF is assumed to be a multiple of 8.
 * Software should program these bits based on Total Number of VFs \
 * programmed क्रम each PF.
 * Since रेजिस्टरs from 0x000-0x7ff are split across functions, each PF will
 * have the same location क्रम the same 4 bits
 */

#घोषणा PXPCS_TL_CONTROL_5		    0x814
#घोषणा PXPCS_TL_CONTROL_5_UNKNOWNTYPE_ERR_ATTN    (1 << 29) /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_BOUNDARY4K_ERR_ATTN	   (1 << 28)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_MRRS_ERR_ATTN   (1 << 27)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_MPS_ERR_ATTN    (1 << 26)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_TTX_BRIDGE_FORWARD_ERR  (1 << 25)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_TTX_TXINTF_OVERFLOW	   (1 << 24)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_PHY_ERR_ATTN    (1 << 23)   /*RO*/
#घोषणा PXPCS_TL_CONTROL_5_DL_ERR_ATTN	   (1 << 22)   /*RO*/
#घोषणा PXPCS_TL_CONTROL_5_TTX_ERR_NP_TAG_IN_USE   (1 << 21)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_TRX_ERR_UNEXP_RTAG  (1 << 20)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_PRI_SIG_TARGET_ABORT1   (1 << 19)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_UNSPPORT1   (1 << 18)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_ECRC1   (1 << 17)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_MALF_TLP1   (1 << 16)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_RX_OFLOW1   (1 << 15)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_UNEXP_CPL1  (1 << 14)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_MASTER_ABRT1    (1 << 13)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_CPL_TIMEOUT1    (1 << 12)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_FC_PRTL1    (1 << 11)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_PSND_TLP1   (1 << 10)   /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_PRI_SIG_TARGET_ABORT    (1 << 9)    /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_UNSPPORT    (1 << 8)    /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_ECRC    (1 << 7)    /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_MALF_TLP    (1 << 6)    /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_RX_OFLOW    (1 << 5)    /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_UNEXP_CPL   (1 << 4)    /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_MASTER_ABRT     (1 << 3)    /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_CPL_TIMEOUT     (1 << 2)    /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_FC_PRTL	   (1 << 1)    /*WC*/
#घोषणा PXPCS_TL_CONTROL_5_ERR_PSND_TLP    (1 << 0)    /*WC*/


#घोषणा PXPCS_TL_FUNC345_STAT	   0x854
#घोषणा PXPCS_TL_FUNC345_STAT_PRI_SIG_TARGET_ABORT4    (1 << 29)   /* WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT4\
	(1 << 28) /* Unsupported Request Error Status in function4, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_ECRC4\
	(1 << 27) /* ECRC Error TLP Status Status in function 4, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_MALF_TLP4\
	(1 << 26) /* Malक्रमmed TLP Status Status in function 4, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_RX_OFLOW4\
	(1 << 25) /* Receiver Overflow Status Status in function 4, अगर \
	set, generate pcie_err_attn output when this error is seen.. WC \
	*/
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_UNEXP_CPL4\
	(1 << 24) /* Unexpected Completion Status Status in function 4, \
	अगर set, generate pcie_err_attn output when this error is seen. WC \
	*/
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_MASTER_ABRT4\
	(1 << 23) /* Receive UR Statusin function 4. If set, generate \
	pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_CPL_TIMEOUT4\
	(1 << 22) /* Completer Timeout Status Status in function 4, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_FC_PRTL4\
	(1 << 21) /* Flow Control Protocol Error Status Status in \
	function 4, अगर set, generate pcie_err_attn output when this error \
	is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_PSND_TLP4\
	(1 << 20) /* Poisoned Error Status Status in function 4, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_PRI_SIG_TARGET_ABORT3    (1 << 19)   /* WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT3\
	(1 << 18) /* Unsupported Request Error Status in function3, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_ECRC3\
	(1 << 17) /* ECRC Error TLP Status Status in function 3, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_MALF_TLP3\
	(1 << 16) /* Malक्रमmed TLP Status Status in function 3, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_RX_OFLOW3\
	(1 << 15) /* Receiver Overflow Status Status in function 3, अगर \
	set, generate pcie_err_attn output when this error is seen.. WC \
	*/
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_UNEXP_CPL3\
	(1 << 14) /* Unexpected Completion Status Status in function 3, \
	अगर set, generate pcie_err_attn output when this error is seen. WC \
	*/
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_MASTER_ABRT3\
	(1 << 13) /* Receive UR Statusin function 3. If set, generate \
	pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_CPL_TIMEOUT3\
	(1 << 12) /* Completer Timeout Status Status in function 3, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_FC_PRTL3\
	(1 << 11) /* Flow Control Protocol Error Status Status in \
	function 3, अगर set, generate pcie_err_attn output when this error \
	is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_PSND_TLP3\
	(1 << 10) /* Poisoned Error Status Status in function 3, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_PRI_SIG_TARGET_ABORT2    (1 << 9)    /* WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT2\
	(1 << 8) /* Unsupported Request Error Status क्रम Function 2, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_ECRC2\
	(1 << 7) /* ECRC Error TLP Status Status क्रम Function 2, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_MALF_TLP2\
	(1 << 6) /* Malक्रमmed TLP Status Status क्रम Function 2, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_RX_OFLOW2\
	(1 << 5) /* Receiver Overflow Status Status क्रम Function 2, अगर \
	set, generate pcie_err_attn output when this error is seen.. WC \
	*/
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_UNEXP_CPL2\
	(1 << 4) /* Unexpected Completion Status Status क्रम Function 2, \
	अगर set, generate pcie_err_attn output when this error is seen. WC \
	*/
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_MASTER_ABRT2\
	(1 << 3) /* Receive UR Statusक्रम Function 2. If set, generate \
	pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_CPL_TIMEOUT2\
	(1 << 2) /* Completer Timeout Status Status क्रम Function 2, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_FC_PRTL2\
	(1 << 1) /* Flow Control Protocol Error Status Status क्रम \
	Function 2, अगर set, generate pcie_err_attn output when this error \
	is seen. WC */
#घोषणा PXPCS_TL_FUNC345_STAT_ERR_PSND_TLP2\
	(1 << 0) /* Poisoned Error Status Status क्रम Function 2, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */


#घोषणा PXPCS_TL_FUNC678_STAT  0x85C
#घोषणा PXPCS_TL_FUNC678_STAT_PRI_SIG_TARGET_ABORT7    (1 << 29)   /*	 WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT7\
	(1 << 28) /* Unsupported Request Error Status in function7, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_ECRC7\
	(1 << 27) /* ECRC Error TLP Status Status in function 7, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_MALF_TLP7\
	(1 << 26) /* Malक्रमmed TLP Status Status in function 7, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_RX_OFLOW7\
	(1 << 25) /* Receiver Overflow Status Status in function 7, अगर \
	set, generate pcie_err_attn output when this error is seen.. WC \
	*/
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_UNEXP_CPL7\
	(1 << 24) /* Unexpected Completion Status Status in function 7, \
	अगर set, generate pcie_err_attn output when this error is seen. WC \
	*/
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_MASTER_ABRT7\
	(1 << 23) /* Receive UR Statusin function 7. If set, generate \
	pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_CPL_TIMEOUT7\
	(1 << 22) /* Completer Timeout Status Status in function 7, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_FC_PRTL7\
	(1 << 21) /* Flow Control Protocol Error Status Status in \
	function 7, अगर set, generate pcie_err_attn output when this error \
	is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_PSND_TLP7\
	(1 << 20) /* Poisoned Error Status Status in function 7, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_PRI_SIG_TARGET_ABORT6    (1 << 19)    /*	  WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT6\
	(1 << 18) /* Unsupported Request Error Status in function6, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_ECRC6\
	(1 << 17) /* ECRC Error TLP Status Status in function 6, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_MALF_TLP6\
	(1 << 16) /* Malक्रमmed TLP Status Status in function 6, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_RX_OFLOW6\
	(1 << 15) /* Receiver Overflow Status Status in function 6, अगर \
	set, generate pcie_err_attn output when this error is seen.. WC \
	*/
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_UNEXP_CPL6\
	(1 << 14) /* Unexpected Completion Status Status in function 6, \
	अगर set, generate pcie_err_attn output when this error is seen. WC \
	*/
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_MASTER_ABRT6\
	(1 << 13) /* Receive UR Statusin function 6. If set, generate \
	pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_CPL_TIMEOUT6\
	(1 << 12) /* Completer Timeout Status Status in function 6, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_FC_PRTL6\
	(1 << 11) /* Flow Control Protocol Error Status Status in \
	function 6, अगर set, generate pcie_err_attn output when this error \
	is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_PSND_TLP6\
	(1 << 10) /* Poisoned Error Status Status in function 6, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_PRI_SIG_TARGET_ABORT5    (1 << 9) /*    WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT5\
	(1 << 8) /* Unsupported Request Error Status क्रम Function 5, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_ECRC5\
	(1 << 7) /* ECRC Error TLP Status Status क्रम Function 5, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_MALF_TLP5\
	(1 << 6) /* Malक्रमmed TLP Status Status क्रम Function 5, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_RX_OFLOW5\
	(1 << 5) /* Receiver Overflow Status Status क्रम Function 5, अगर \
	set, generate pcie_err_attn output when this error is seen.. WC \
	*/
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_UNEXP_CPL5\
	(1 << 4) /* Unexpected Completion Status Status क्रम Function 5, \
	अगर set, generate pcie_err_attn output when this error is seen. WC \
	*/
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_MASTER_ABRT5\
	(1 << 3) /* Receive UR Statusक्रम Function 5. If set, generate \
	pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_CPL_TIMEOUT5\
	(1 << 2) /* Completer Timeout Status Status क्रम Function 5, अगर \
	set, generate pcie_err_attn output when this error is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_FC_PRTL5\
	(1 << 1) /* Flow Control Protocol Error Status Status क्रम \
	Function 5, अगर set, generate pcie_err_attn output when this error \
	is seen. WC */
#घोषणा PXPCS_TL_FUNC678_STAT_ERR_PSND_TLP5\
	(1 << 0) /* Poisoned Error Status Status क्रम Function 5, अगर set, \
	generate pcie_err_attn output when this error is seen.. WC */


#घोषणा BAR_USTRORM_INTMEM				0x400000
#घोषणा BAR_CSTRORM_INTMEM				0x410000
#घोषणा BAR_XSTRORM_INTMEM				0x420000
#घोषणा BAR_TSTRORM_INTMEM				0x430000

/* क्रम accessing the IGU in हाल of status block ACK */
#घोषणा BAR_IGU_INTMEM					0x440000

#घोषणा BAR_DOORBELL_OFFSET				0x800000

#घोषणा BAR_ME_REGISTER				0x450000
#घोषणा ME_REG_PF_NUM_SHIFT		0
#घोषणा ME_REG_PF_NUM\
	(7L<<ME_REG_PF_NUM_SHIFT) /* Relative PF Num */
#घोषणा ME_REG_VF_VALID		(1<<8)
#घोषणा ME_REG_VF_NUM_SHIFT		9
#घोषणा ME_REG_VF_NUM_MASK		(0x3f<<ME_REG_VF_NUM_SHIFT)
#घोषणा ME_REG_VF_ERR			(0x1<<3)
#घोषणा ME_REG_ABS_PF_NUM_SHIFT	16
#घोषणा ME_REG_ABS_PF_NUM\
	(7L<<ME_REG_ABS_PF_NUM_SHIFT) /* Absolute PF Num */


#घोषणा PXP_VF_ADDR_IGU_START				0
#घोषणा PXP_VF_ADDR_IGU_SIZE				0x3000
#घोषणा PXP_VF_ADDR_IGU_END\
	((PXP_VF_ADDR_IGU_START) + (PXP_VF_ADDR_IGU_SIZE) - 1)

#घोषणा PXP_VF_ADDR_USDM_QUEUES_START			0x3000
#घोषणा PXP_VF_ADDR_USDM_QUEUES_SIZE\
	(PXP_VF_ADRR_NUM_QUEUES * PXP_ADDR_QUEUE_SIZE)
#घोषणा PXP_VF_ADDR_USDM_QUEUES_END\
	((PXP_VF_ADDR_USDM_QUEUES_START) + (PXP_VF_ADDR_USDM_QUEUES_SIZE) - 1)

#घोषणा PXP_VF_ADDR_CSDM_GLOBAL_START			0x7600
#घोषणा PXP_VF_ADDR_CSDM_GLOBAL_SIZE			(PXP_ADDR_REG_SIZE)
#घोषणा PXP_VF_ADDR_CSDM_GLOBAL_END\
	((PXP_VF_ADDR_CSDM_GLOBAL_START) + (PXP_VF_ADDR_CSDM_GLOBAL_SIZE) - 1)

#घोषणा PXP_VF_ADDR_DB_START				0x7c00
#घोषणा PXP_VF_ADDR_DB_SIZE				0x200
#घोषणा PXP_VF_ADDR_DB_END\
	((PXP_VF_ADDR_DB_START) + (PXP_VF_ADDR_DB_SIZE) - 1)

#घोषणा MDIO_REG_BANK_CL73_IEEEB0	0x0
#घोषणा MDIO_CL73_IEEEB0_CL73_AN_CONTROL	0x0
#घोषणा MDIO_CL73_IEEEB0_CL73_AN_CONTROL_RESTART_AN	0x0200
#घोषणा MDIO_CL73_IEEEB0_CL73_AN_CONTROL_AN_EN		0x1000
#घोषणा MDIO_CL73_IEEEB0_CL73_AN_CONTROL_MAIN_RST	0x8000

#घोषणा MDIO_REG_BANK_CL73_IEEEB1	0x10
#घोषणा MDIO_CL73_IEEEB1_AN_ADV1		0x00
#घोषणा MDIO_CL73_IEEEB1_AN_ADV1_PAUSE			0x0400
#घोषणा MDIO_CL73_IEEEB1_AN_ADV1_ASYMMETRIC		0x0800
#घोषणा MDIO_CL73_IEEEB1_AN_ADV1_PAUSE_BOTH		0x0C00
#घोषणा MDIO_CL73_IEEEB1_AN_ADV1_PAUSE_MASK		0x0C00
#घोषणा MDIO_CL73_IEEEB1_AN_ADV2		0x01
#घोषणा MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M		0x0000
#घोषणा MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX		0x0020
#घोषणा MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4		0x0040
#घोषणा MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KR		0x0080
#घोषणा MDIO_CL73_IEEEB1_AN_LP_ADV1		0x03
#घोषणा MDIO_CL73_IEEEB1_AN_LP_ADV1_PAUSE		0x0400
#घोषणा MDIO_CL73_IEEEB1_AN_LP_ADV1_ASYMMETRIC		0x0800
#घोषणा MDIO_CL73_IEEEB1_AN_LP_ADV1_PAUSE_BOTH		0x0C00
#घोषणा MDIO_CL73_IEEEB1_AN_LP_ADV1_PAUSE_MASK		0x0C00
#घोषणा MDIO_CL73_IEEEB1_AN_LP_ADV2			0x04

#घोषणा MDIO_REG_BANK_RX0				0x80b0
#घोषणा MDIO_RX0_RX_STATUS				0x10
#घोषणा MDIO_RX0_RX_STATUS_SIGDET			0x8000
#घोषणा MDIO_RX0_RX_STATUS_RX_SEQ_DONE			0x1000
#घोषणा MDIO_RX0_RX_EQ_BOOST				0x1c
#घोषणा MDIO_RX0_RX_EQ_BOOST_EQUALIZER_CTRL_MASK	0x7
#घोषणा MDIO_RX0_RX_EQ_BOOST_OFFSET_CTRL		0x10

#घोषणा MDIO_REG_BANK_RX1				0x80c0
#घोषणा MDIO_RX1_RX_EQ_BOOST				0x1c
#घोषणा MDIO_RX1_RX_EQ_BOOST_EQUALIZER_CTRL_MASK	0x7
#घोषणा MDIO_RX1_RX_EQ_BOOST_OFFSET_CTRL		0x10

#घोषणा MDIO_REG_BANK_RX2				0x80d0
#घोषणा MDIO_RX2_RX_EQ_BOOST				0x1c
#घोषणा MDIO_RX2_RX_EQ_BOOST_EQUALIZER_CTRL_MASK	0x7
#घोषणा MDIO_RX2_RX_EQ_BOOST_OFFSET_CTRL		0x10

#घोषणा MDIO_REG_BANK_RX3				0x80e0
#घोषणा MDIO_RX3_RX_EQ_BOOST				0x1c
#घोषणा MDIO_RX3_RX_EQ_BOOST_EQUALIZER_CTRL_MASK	0x7
#घोषणा MDIO_RX3_RX_EQ_BOOST_OFFSET_CTRL		0x10

#घोषणा MDIO_REG_BANK_RX_ALL				0x80f0
#घोषणा MDIO_RX_ALL_RX_EQ_BOOST 			0x1c
#घोषणा MDIO_RX_ALL_RX_EQ_BOOST_EQUALIZER_CTRL_MASK	0x7
#घोषणा MDIO_RX_ALL_RX_EQ_BOOST_OFFSET_CTRL	0x10

#घोषणा MDIO_REG_BANK_TX0				0x8060
#घोषणा MDIO_TX0_TX_DRIVER				0x17
#घोषणा MDIO_TX0_TX_DRIVER_PREEMPHASIS_MASK		0xf000
#घोषणा MDIO_TX0_TX_DRIVER_PREEMPHASIS_SHIFT		12
#घोषणा MDIO_TX0_TX_DRIVER_IDRIVER_MASK 		0x0f00
#घोषणा MDIO_TX0_TX_DRIVER_IDRIVER_SHIFT		8
#घोषणा MDIO_TX0_TX_DRIVER_IPREDRIVER_MASK		0x00f0
#घोषणा MDIO_TX0_TX_DRIVER_IPREDRIVER_SHIFT		4
#घोषणा MDIO_TX0_TX_DRIVER_IFULLSPD_MASK		0x000e
#घोषणा MDIO_TX0_TX_DRIVER_IFULLSPD_SHIFT		1
#घोषणा MDIO_TX0_TX_DRIVER_ICBUF1T			1

#घोषणा MDIO_REG_BANK_TX1				0x8070
#घोषणा MDIO_TX1_TX_DRIVER				0x17
#घोषणा MDIO_TX0_TX_DRIVER_PREEMPHASIS_MASK		0xf000
#घोषणा MDIO_TX0_TX_DRIVER_PREEMPHASIS_SHIFT		12
#घोषणा MDIO_TX0_TX_DRIVER_IDRIVER_MASK 		0x0f00
#घोषणा MDIO_TX0_TX_DRIVER_IDRIVER_SHIFT		8
#घोषणा MDIO_TX0_TX_DRIVER_IPREDRIVER_MASK		0x00f0
#घोषणा MDIO_TX0_TX_DRIVER_IPREDRIVER_SHIFT		4
#घोषणा MDIO_TX0_TX_DRIVER_IFULLSPD_MASK		0x000e
#घोषणा MDIO_TX0_TX_DRIVER_IFULLSPD_SHIFT		1
#घोषणा MDIO_TX0_TX_DRIVER_ICBUF1T			1

#घोषणा MDIO_REG_BANK_TX2				0x8080
#घोषणा MDIO_TX2_TX_DRIVER				0x17
#घोषणा MDIO_TX0_TX_DRIVER_PREEMPHASIS_MASK		0xf000
#घोषणा MDIO_TX0_TX_DRIVER_PREEMPHASIS_SHIFT		12
#घोषणा MDIO_TX0_TX_DRIVER_IDRIVER_MASK 		0x0f00
#घोषणा MDIO_TX0_TX_DRIVER_IDRIVER_SHIFT		8
#घोषणा MDIO_TX0_TX_DRIVER_IPREDRIVER_MASK		0x00f0
#घोषणा MDIO_TX0_TX_DRIVER_IPREDRIVER_SHIFT		4
#घोषणा MDIO_TX0_TX_DRIVER_IFULLSPD_MASK		0x000e
#घोषणा MDIO_TX0_TX_DRIVER_IFULLSPD_SHIFT		1
#घोषणा MDIO_TX0_TX_DRIVER_ICBUF1T			1

#घोषणा MDIO_REG_BANK_TX3				0x8090
#घोषणा MDIO_TX3_TX_DRIVER				0x17
#घोषणा MDIO_TX0_TX_DRIVER_PREEMPHASIS_MASK		0xf000
#घोषणा MDIO_TX0_TX_DRIVER_PREEMPHASIS_SHIFT		12
#घोषणा MDIO_TX0_TX_DRIVER_IDRIVER_MASK 		0x0f00
#घोषणा MDIO_TX0_TX_DRIVER_IDRIVER_SHIFT		8
#घोषणा MDIO_TX0_TX_DRIVER_IPREDRIVER_MASK		0x00f0
#घोषणा MDIO_TX0_TX_DRIVER_IPREDRIVER_SHIFT		4
#घोषणा MDIO_TX0_TX_DRIVER_IFULLSPD_MASK		0x000e
#घोषणा MDIO_TX0_TX_DRIVER_IFULLSPD_SHIFT		1
#घोषणा MDIO_TX0_TX_DRIVER_ICBUF1T			1

#घोषणा MDIO_REG_BANK_XGXS_BLOCK0			0x8000
#घोषणा MDIO_BLOCK0_XGXS_CONTROL			0x10

#घोषणा MDIO_REG_BANK_XGXS_BLOCK1			0x8010
#घोषणा MDIO_BLOCK1_LANE_CTRL0				0x15
#घोषणा MDIO_BLOCK1_LANE_CTRL1				0x16
#घोषणा MDIO_BLOCK1_LANE_CTRL2				0x17
#घोषणा MDIO_BLOCK1_LANE_PRBS				0x19

#घोषणा MDIO_REG_BANK_XGXS_BLOCK2			0x8100
#घोषणा MDIO_XGXS_BLOCK2_RX_LN_SWAP			0x10
#घोषणा MDIO_XGXS_BLOCK2_RX_LN_SWAP_ENABLE		0x8000
#घोषणा MDIO_XGXS_BLOCK2_RX_LN_SWAP_FORCE_ENABLE	0x4000
#घोषणा MDIO_XGXS_BLOCK2_TX_LN_SWAP		0x11
#घोषणा MDIO_XGXS_BLOCK2_TX_LN_SWAP_ENABLE		0x8000
#घोषणा MDIO_XGXS_BLOCK2_UNICORE_MODE_10G	0x14
#घोषणा MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_CX4_XGXS	0x0001
#घोषणा MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_HIGIG_XGXS	0x0010
#घोषणा MDIO_XGXS_BLOCK2_TEST_MODE_LANE 	0x15

#घोषणा MDIO_REG_BANK_GP_STATUS 			0x8120
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1				0x1B
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE	0x0001
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_CL37_AUTONEG_COMPLETE	0x0002
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS		0x0004
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_DUPLEX_STATUS		0x0008
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_MR_LP_NP_AN_ABLE	0x0010
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_LP_NP_BAM_ABLE	0x0020
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_PAUSE_RSOLUTION_TXSIDE	0x0040
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_PAUSE_RSOLUTION_RXSIDE	0x0080
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_MASK 	0x3f00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10M		0x0000
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_100M 	0x0100
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_1G		0x0200
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_2_5G 	0x0300
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_5G		0x0400
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_6G		0x0500
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_HIG	0x0600
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_CX4	0x0700
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_12G_HIG	0x0800
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_12_5G	0x0900
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_13G		0x0A00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_15G		0x0B00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_16G		0x0C00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_1G_KX	0x0D00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_KX4	0x0E00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_KR	0x0F00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_XFI	0x1B00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_20G_DXGXS	0x1E00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_SFI	0x1F00
#घोषणा MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_20G_KR2	0x3900


#घोषणा MDIO_REG_BANK_10G_PARALLEL_DETECT		0x8130
#घोषणा MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_STATUS		0x10
#घोषणा MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_STATUS_PD_LINK		0x8000
#घोषणा MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL		0x11
#घोषणा MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL_PARDET10G_EN	0x1
#घोषणा MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK		0x13
#घोषणा MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK_CNT		(0xb71<<1)

#घोषणा MDIO_REG_BANK_SERDES_DIGITAL			0x8300
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL1			0x10
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_FIBER_MODE 		0x0001
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_TBI_IF			0x0002
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_SIGNAL_DETECT_EN		0x0004
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_INVERT_SIGNAL_DETECT	0x0008
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET			0x0010
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_MSTR_MODE			0x0020
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL2			0x11
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_PRL_DT_EN			0x0001
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_AN_FST_TMR 		0x0040
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1			0x14
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1_SGMII			0x0001
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1_LINK			0x0002
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1_DUPLEX			0x0004
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1_SPEED_MASK			0x0018
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1_SPEED_SHIFT 		3
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1_SPEED_2_5G			0x0018
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1_SPEED_1G			0x0010
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1_SPEED_100M			0x0008
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS1_SPEED_10M			0x0000
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS2			0x15
#घोषणा MDIO_SERDES_DIGITAL_A_1000X_STATUS2_AN_DISABLED 		0x0002
#घोषणा MDIO_SERDES_DIGITAL_MISC1				0x18
#घोषणा MDIO_SERDES_DIGITAL_MISC1_REFCLK_SEL_MASK			0xE000
#घोषणा MDIO_SERDES_DIGITAL_MISC1_REFCLK_SEL_25M			0x0000
#घोषणा MDIO_SERDES_DIGITAL_MISC1_REFCLK_SEL_100M			0x2000
#घोषणा MDIO_SERDES_DIGITAL_MISC1_REFCLK_SEL_125M			0x4000
#घोषणा MDIO_SERDES_DIGITAL_MISC1_REFCLK_SEL_156_25M			0x6000
#घोषणा MDIO_SERDES_DIGITAL_MISC1_REFCLK_SEL_187_5M			0x8000
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_SEL			0x0010
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_MASK			0x000f
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_2_5G			0x0000
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_5G			0x0001
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_6G			0x0002
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_10G_HIG			0x0003
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_10G_CX4			0x0004
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_12G			0x0005
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_12_5G			0x0006
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_13G			0x0007
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_15G			0x0008
#घोषणा MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_16G			0x0009

#घोषणा MDIO_REG_BANK_OVER_1G				0x8320
#घोषणा MDIO_OVER_1G_DIGCTL_3_4 				0x14
#घोषणा MDIO_OVER_1G_DIGCTL_3_4_MP_ID_MASK				0xffe0
#घोषणा MDIO_OVER_1G_DIGCTL_3_4_MP_ID_SHIFT				5
#घोषणा MDIO_OVER_1G_UP1					0x19
#घोषणा MDIO_OVER_1G_UP1_2_5G						0x0001
#घोषणा MDIO_OVER_1G_UP1_5G						0x0002
#घोषणा MDIO_OVER_1G_UP1_6G						0x0004
#घोषणा MDIO_OVER_1G_UP1_10G						0x0010
#घोषणा MDIO_OVER_1G_UP1_10GH						0x0008
#घोषणा MDIO_OVER_1G_UP1_12G						0x0020
#घोषणा MDIO_OVER_1G_UP1_12_5G						0x0040
#घोषणा MDIO_OVER_1G_UP1_13G						0x0080
#घोषणा MDIO_OVER_1G_UP1_15G						0x0100
#घोषणा MDIO_OVER_1G_UP1_16G						0x0200
#घोषणा MDIO_OVER_1G_UP2					0x1A
#घोषणा MDIO_OVER_1G_UP2_IPREDRIVER_MASK				0x0007
#घोषणा MDIO_OVER_1G_UP2_IDRIVER_MASK					0x0038
#घोषणा MDIO_OVER_1G_UP2_PREEMPHASIS_MASK				0x03C0
#घोषणा MDIO_OVER_1G_UP3					0x1B
#घोषणा MDIO_OVER_1G_UP3_HIGIG2 					0x0001
#घोषणा MDIO_OVER_1G_LP_UP1					0x1C
#घोषणा MDIO_OVER_1G_LP_UP2					0x1D
#घोषणा MDIO_OVER_1G_LP_UP2_MR_ADV_OVER_1G_MASK 			0x03ff
#घोषणा MDIO_OVER_1G_LP_UP2_PREEMPHASIS_MASK				0x0780
#घोषणा MDIO_OVER_1G_LP_UP2_PREEMPHASIS_SHIFT				7
#घोषणा MDIO_OVER_1G_LP_UP3						0x1E

#घोषणा MDIO_REG_BANK_REMOTE_PHY			0x8330
#घोषणा MDIO_REMOTE_PHY_MISC_RX_STATUS				0x10
#घोषणा MDIO_REMOTE_PHY_MISC_RX_STATUS_CL37_FSM_RECEIVED_OVER1G_MSG	0x0010
#घोषणा MDIO_REMOTE_PHY_MISC_RX_STATUS_CL37_FSM_RECEIVED_BRCM_OUI_MSG	0x0600

#घोषणा MDIO_REG_BANK_BAM_NEXT_PAGE			0x8350
#घोषणा MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL			0x10
#घोषणा MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_BAM_MODE			0x0001
#घोषणा MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_TETON_AN			0x0002

#घोषणा MDIO_REG_BANK_CL73_USERB0		0x8370
#घोषणा MDIO_CL73_USERB0_CL73_UCTRL				0x10
#घोषणा MDIO_CL73_USERB0_CL73_UCTRL_USTAT1_MUXSEL			0x0002
#घोषणा MDIO_CL73_USERB0_CL73_USTAT1				0x11
#घोषणा MDIO_CL73_USERB0_CL73_USTAT1_LINK_STATUS_CHECK			0x0100
#घोषणा MDIO_CL73_USERB0_CL73_USTAT1_AN_GOOD_CHECK_BAM37		0x0400
#घोषणा MDIO_CL73_USERB0_CL73_BAM_CTRL1 			0x12
#घोषणा MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_EN				0x8000
#घोषणा MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_STATION_MNGR_EN		0x4000
#घोषणा MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_NP_AFTER_BP_EN		0x2000
#घोषणा MDIO_CL73_USERB0_CL73_BAM_CTRL3 			0x14
#घोषणा MDIO_CL73_USERB0_CL73_BAM_CTRL3_USE_CL73_HCD_MR 		0x0001

#घोषणा MDIO_REG_BANK_AER_BLOCK 		0xFFD0
#घोषणा MDIO_AER_BLOCK_AER_REG					0x1E

#घोषणा MDIO_REG_BANK_COMBO_IEEE0		0xFFE0
#घोषणा MDIO_COMBO_IEEE0_MII_CONTROL				0x10
#घोषणा MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_MASK			0x2040
#घोषणा MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_10			0x0000
#घोषणा MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_100			0x2000
#घोषणा MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_1000			0x0040
#घोषणा MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX 			0x0100
#घोषणा MDIO_COMBO_IEEO_MII_CONTROL_RESTART_AN				0x0200
#घोषणा MDIO_COMBO_IEEO_MII_CONTROL_AN_EN				0x1000
#घोषणा MDIO_COMBO_IEEO_MII_CONTROL_LOOPBACK				0x4000
#घोषणा MDIO_COMBO_IEEO_MII_CONTROL_RESET				0x8000
#घोषणा MDIO_COMBO_IEEE0_MII_STATUS				0x11
#घोषणा MDIO_COMBO_IEEE0_MII_STATUS_LINK_PASS				0x0004
#घोषणा MDIO_COMBO_IEEE0_MII_STATUS_AUTONEG_COMPLETE			0x0020
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_ADV				0x14
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_ADV_FULL_DUPLEX			0x0020
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_ADV_HALF_DUPLEX			0x0040
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK			0x0180
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_NONE			0x0000
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_SYMMETRIC			0x0080
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC			0x0100
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH			0x0180
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_ADV_NEXT_PAGE 			0x8000
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1 	0x15
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1_NEXT_PAGE	0x8000
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1_ACK		0x4000
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1_PAUSE_MASK	0x0180
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1_PAUSE_NONE	0x0000
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1_PAUSE_BOTH	0x0180
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1_HALF_DUP_CAP	0x0040
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1_FULL_DUP_CAP	0x0020
/*WhenthelinkpartnerisinSGMIImode(bit0=1),then
bit15=link,bit12=duplex,bits11:10=speed,bit14=acknowledge.
Theotherbitsarereservedandshouldbezero*/
#घोषणा MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1_SGMII_MODE	0x0001


#घोषणा MDIO_PMA_DEVAD			0x1
/*ieee*/
#घोषणा MDIO_PMA_REG_CTRL		0x0
#घोषणा MDIO_PMA_REG_STATUS		0x1
#घोषणा MDIO_PMA_REG_10G_CTRL2		0x7
#घोषणा MDIO_PMA_REG_TX_DISABLE		0x0009
#घोषणा MDIO_PMA_REG_RX_SD		0xa
/*bcm*/
#घोषणा MDIO_PMA_REG_BCM_CTRL		0x0096
#घोषणा MDIO_PMA_REG_FEC_CTRL		0x00ab
#घोषणा MDIO_PMA_REG_PHY_IDENTIFIER	0xc800
#घोषणा MDIO_PMA_REG_DIGITAL_CTRL	0xc808
#घोषणा MDIO_PMA_REG_DIGITAL_STATUS	0xc809
#घोषणा MDIO_PMA_REG_TX_POWER_DOWN	0xca02
#घोषणा MDIO_PMA_REG_CMU_PLL_BYPASS	0xca09
#घोषणा MDIO_PMA_REG_MISC_CTRL		0xca0a
#घोषणा MDIO_PMA_REG_GEN_CTRL		0xca10
#घोषणा MDIO_PMA_REG_GEN_CTRL_ROM_RESET_INTERNAL_MP	0x0188
#घोषणा MDIO_PMA_REG_GEN_CTRL_ROM_MICRO_RESET		0x018a
#घोषणा MDIO_PMA_REG_M8051_MSGIN_REG	0xca12
#घोषणा MDIO_PMA_REG_M8051_MSGOUT_REG	0xca13
#घोषणा MDIO_PMA_REG_ROM_VER1		0xca19
#घोषणा MDIO_PMA_REG_ROM_VER2		0xca1a
#घोषणा MDIO_PMA_REG_EDC_FFE_MAIN	0xca1b
#घोषणा MDIO_PMA_REG_PLL_BANDWIDTH	0xca1d
#घोषणा MDIO_PMA_REG_PLL_CTRL		0xca1e
#घोषणा MDIO_PMA_REG_MISC_CTRL0 	0xca23
#घोषणा MDIO_PMA_REG_LRM_MODE		0xca3f
#घोषणा MDIO_PMA_REG_CDR_BANDWIDTH	0xca46
#घोषणा MDIO_PMA_REG_MISC_CTRL1 	0xca85

#घोषणा MDIO_PMA_REG_SFP_TWO_WIRE_CTRL		0x8000
#घोषणा MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK	0x000c
#घोषणा MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_IDLE		0x0000
#घोषणा MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_COMPLETE	0x0004
#घोषणा MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_IN_PROGRESS	0x0008
#घोषणा MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_FAILED 	0x000c
#घोषणा MDIO_PMA_REG_SFP_TWO_WIRE_BYTE_CNT	0x8002
#घोषणा MDIO_PMA_REG_SFP_TWO_WIRE_MEM_ADDR	0x8003
#घोषणा MDIO_PMA_REG_8726_TWO_WIRE_DATA_BUF	0xc820
#घोषणा MDIO_PMA_REG_8726_TWO_WIRE_DATA_MASK 0xff
#घोषणा MDIO_PMA_REG_8726_TX_CTRL1		0xca01
#घोषणा MDIO_PMA_REG_8726_TX_CTRL2		0xca05

#घोषणा MDIO_PMA_REG_8727_TWO_WIRE_SLAVE_ADDR	0x8005
#घोषणा MDIO_PMA_REG_8727_TWO_WIRE_DATA_BUF	0x8007
#घोषणा MDIO_PMA_REG_8727_TWO_WIRE_DATA_MASK 0xff
#घोषणा MDIO_PMA_REG_8727_TX_CTRL1		0xca02
#घोषणा MDIO_PMA_REG_8727_TX_CTRL2		0xca05
#घोषणा MDIO_PMA_REG_8727_PCS_OPT_CTRL		0xc808
#घोषणा MDIO_PMA_REG_8727_GPIO_CTRL		0xc80e
#घोषणा MDIO_PMA_REG_8727_PCS_GP		0xc842
#घोषणा MDIO_PMA_REG_8727_OPT_CFG_REG		0xc8e4

#घोषणा MDIO_AN_REG_8727_MISC_CTRL		0x8309

#घोषणा MDIO_PMA_REG_8073_CHIP_REV			0xc801
#घोषणा MDIO_PMA_REG_8073_SPEED_LINK_STATUS		0xc820
#घोषणा MDIO_PMA_REG_8073_XAUI_WA			0xc841
#घोषणा MDIO_PMA_REG_8073_OPT_DIGITAL_CTRL		0xcd08

#घोषणा MDIO_PMA_REG_7101_RESET 	0xc000
#घोषणा MDIO_PMA_REG_7107_LED_CNTL	0xc007
#घोषणा MDIO_PMA_REG_7107_LINK_LED_CNTL 0xc009
#घोषणा MDIO_PMA_REG_7101_VER1		0xc026
#घोषणा MDIO_PMA_REG_7101_VER2		0xc027

#घोषणा MDIO_PMA_REG_8481_PMD_SIGNAL			0xa811
#घोषणा MDIO_PMA_REG_8481_LED1_MASK			0xa82c
#घोषणा MDIO_PMA_REG_8481_LED2_MASK			0xa82f
#घोषणा MDIO_PMA_REG_8481_LED3_MASK			0xa832
#घोषणा MDIO_PMA_REG_8481_LED3_BLINK			0xa834
#घोषणा MDIO_PMA_REG_8481_LED5_MASK			0xa838
#घोषणा MDIO_PMA_REG_8481_SIGNAL_MASK			0xa835
#घोषणा MDIO_PMA_REG_8481_LINK_SIGNAL			0xa83b
#घोषणा MDIO_PMA_REG_8481_LINK_SIGNAL_LED4_ENABLE_MASK	0x800
#घोषणा MDIO_PMA_REG_8481_LINK_SIGNAL_LED4_ENABLE_SHIFT 11


#घोषणा MDIO_WIS_DEVAD			0x2
/*bcm*/
#घोषणा MDIO_WIS_REG_LASI_CNTL		0x9002
#घोषणा MDIO_WIS_REG_LASI_STATUS	0x9005

#घोषणा MDIO_PCS_DEVAD			0x3
#घोषणा MDIO_PCS_REG_STATUS		0x0020
#घोषणा MDIO_PCS_REG_LASI_STATUS	0x9005
#घोषणा MDIO_PCS_REG_7101_DSP_ACCESS	0xD000
#घोषणा MDIO_PCS_REG_7101_SPI_MUX	0xD008
#घोषणा MDIO_PCS_REG_7101_SPI_CTRL_ADDR 0xE12A
#घोषणा MDIO_PCS_REG_7101_SPI_RESET_BIT (5)
#घोषणा MDIO_PCS_REG_7101_SPI_FIFO_ADDR 0xE02A
#घोषणा MDIO_PCS_REG_7101_SPI_FIFO_ADDR_WRITE_ENABLE_CMD (6)
#घोषणा MDIO_PCS_REG_7101_SPI_FIFO_ADDR_BULK_ERASE_CMD	 (0xC7)
#घोषणा MDIO_PCS_REG_7101_SPI_FIFO_ADDR_PAGE_PROGRAM_CMD (2)
#घोषणा MDIO_PCS_REG_7101_SPI_BYTES_TO_TRANSFER_ADDR 0xE028


#घोषणा MDIO_XS_DEVAD			0x4
#घोषणा MDIO_XS_PLL_SEQUENCER		0x8000
#घोषणा MDIO_XS_SFX7101_XGXS_TEST1	0xc00a

#घोषणा MDIO_XS_8706_REG_BANK_RX0	0x80bc
#घोषणा MDIO_XS_8706_REG_BANK_RX1	0x80cc
#घोषणा MDIO_XS_8706_REG_BANK_RX2	0x80dc
#घोषणा MDIO_XS_8706_REG_BANK_RX3	0x80ec
#घोषणा MDIO_XS_8706_REG_BANK_RXA	0x80fc

#घोषणा MDIO_XS_REG_8073_RX_CTRL_PCIE	0x80FA

#घोषणा MDIO_AN_DEVAD			0x7
/*ieee*/
#घोषणा MDIO_AN_REG_CTRL		0x0000
#घोषणा MDIO_AN_REG_STATUS		0x0001
#घोषणा MDIO_AN_REG_STATUS_AN_COMPLETE		0x0020
#घोषणा MDIO_AN_REG_ADV_PAUSE		0x0010
#घोषणा MDIO_AN_REG_ADV_PAUSE_PAUSE		0x0400
#घोषणा MDIO_AN_REG_ADV_PAUSE_ASYMMETRIC	0x0800
#घोषणा MDIO_AN_REG_ADV_PAUSE_BOTH		0x0C00
#घोषणा MDIO_AN_REG_ADV_PAUSE_MASK		0x0C00
#घोषणा MDIO_AN_REG_ADV 		0x0011
#घोषणा MDIO_AN_REG_ADV2		0x0012
#घोषणा MDIO_AN_REG_LP_AUTO_NEG		0x0013
#घोषणा MDIO_AN_REG_LP_AUTO_NEG2	0x0014
#घोषणा MDIO_AN_REG_MASTER_STATUS	0x0021
#घोषणा MDIO_AN_REG_EEE_ADV		0x003c
#घोषणा MDIO_AN_REG_LP_EEE_ADV		0x003d
/*bcm*/
#घोषणा MDIO_AN_REG_LINK_STATUS 	0x8304
#घोषणा MDIO_AN_REG_CL37_CL73		0x8370
#घोषणा MDIO_AN_REG_CL37_AN		0xffe0
#घोषणा MDIO_AN_REG_CL37_FC_LD		0xffe4
#घोषणा		MDIO_AN_REG_CL37_FC_LP		0xffe5
#घोषणा		MDIO_AN_REG_1000T_STATUS	0xffea

#घोषणा MDIO_AN_REG_8073_2_5G		0x8329
#घोषणा MDIO_AN_REG_8073_BAM		0x8350

#घोषणा MDIO_AN_REG_8481_10GBASE_T_AN_CTRL	0x0020
#घोषणा MDIO_AN_REG_8481_LEGACY_MII_CTRL	0xffe0
#घोषणा MDIO_AN_REG_8481_MII_CTRL_FORCE_1G	0x40
#घोषणा MDIO_AN_REG_8481_LEGACY_MII_STATUS	0xffe1
#घोषणा MDIO_AN_REG_848xx_ID_MSB		0xffe2
#घोषणा BCM84858_PHY_ID					0x600d
#घोषणा MDIO_AN_REG_848xx_ID_LSB		0xffe3
#घोषणा MDIO_AN_REG_8481_LEGACY_AN_ADV		0xffe4
#घोषणा MDIO_AN_REG_8481_LEGACY_AN_EXPANSION	0xffe6
#घोषणा MDIO_AN_REG_8481_1000T_CTRL		0xffe9
#घोषणा MDIO_AN_REG_8481_1G_100T_EXT_CTRL	0xfff0
#घोषणा MIDO_AN_REG_8481_EXT_CTRL_FORCE_LEDS_OFF	0x0008
#घोषणा MDIO_AN_REG_8481_EXPANSION_REG_RD_RW	0xfff5
#घोषणा MDIO_AN_REG_8481_EXPANSION_REG_ACCESS	0xfff7
#घोषणा MDIO_AN_REG_8481_AUX_CTRL		0xfff8
#घोषणा MDIO_AN_REG_8481_LEGACY_SHADOW		0xfffc

/* BCM84823 only */
#घोषणा MDIO_CTL_DEVAD			0x1e
#घोषणा MDIO_CTL_REG_84823_MEDIA		0x401a
#घोषणा MDIO_CTL_REG_84823_MEDIA_MAC_MASK		0x0018
	/* These pins configure the BCM84823 पूर्णांकerface to MAC after reset. */
#घोषणा MDIO_CTL_REG_84823_CTRL_MAC_XFI			0x0008
#घोषणा MDIO_CTL_REG_84823_MEDIA_MAC_XAUI_M		0x0010
	/* These pins configure the BCM84823 पूर्णांकerface to Line after reset. */
#घोषणा MDIO_CTL_REG_84823_MEDIA_LINE_MASK		0x0060
#घोषणा MDIO_CTL_REG_84823_MEDIA_LINE_XAUI_L		0x0020
#घोषणा MDIO_CTL_REG_84823_MEDIA_LINE_XFI		0x0040
	/* When this pin is active high during reset, 10GBASE-T core is घातer
	 * करोwn, When it is active low the 10GBASE-T is घातer up
	 */
#घोषणा MDIO_CTL_REG_84823_MEDIA_COPPER_CORE_DOWN	0x0080
#घोषणा MDIO_CTL_REG_84823_MEDIA_PRIORITY_MASK		0x0100
#घोषणा MDIO_CTL_REG_84823_MEDIA_PRIORITY_COPPER	0x0000
#घोषणा MDIO_CTL_REG_84823_MEDIA_PRIORITY_FIBER		0x0100
#घोषणा MDIO_CTL_REG_84823_MEDIA_FIBER_1G			0x1000
#घोषणा MDIO_CTL_REG_84823_USER_CTRL_REG			0x4005
#घोषणा MDIO_CTL_REG_84823_USER_CTRL_CMS			0x0080
#घोषणा MDIO_PMA_REG_84823_CTL_SLOW_CLK_CNT_HIGH		0xa82b
#घोषणा MDIO_PMA_REG_84823_BLINK_RATE_VAL_15P9HZ	0x2f
#घोषणा MDIO_PMA_REG_84823_CTL_LED_CTL_1			0xa8e3
#घोषणा MDIO_PMA_REG_84833_CTL_LED_CTL_1			0xa8ec
#घोषणा MDIO_PMA_REG_84823_LED3_STRETCH_EN			0x0080
/* BCM84858 only */
#घोषणा MDIO_PMA_REG_84858_ALLOW_GPHY_ACT			0x8000

/* BCM84833 only */
#घोषणा MDIO_84833_TOP_CFG_FW_REV			0x400f
#घोषणा MDIO_84833_TOP_CFG_FW_EEE		0x10b1
#घोषणा MDIO_84833_TOP_CFG_FW_NO_EEE		0x1f81
#घोषणा MDIO_84833_TOP_CFG_XGPHY_STRAP1			0x401a
#घोषणा MDIO_84833_SUPER_ISOLATE		0x8000
/* These are mailbox रेजिस्टर set used by 84833/84858. */
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG0			0x4005
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG1			0x4006
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG2			0x4007
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG3			0x4008
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG4			0x4009
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG26		0x4037
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG27		0x4038
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG28		0x4039
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG29		0x403a
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG30		0x403b
#घोषणा MDIO_848xx_TOP_CFG_SCRATCH_REG31		0x403c
#घोषणा MDIO_848xx_CMD_HDLR_COMMAND	(MDIO_848xx_TOP_CFG_SCRATCH_REG0)
#घोषणा MDIO_848xx_CMD_HDLR_STATUS	(MDIO_848xx_TOP_CFG_SCRATCH_REG26)
#घोषणा MDIO_848xx_CMD_HDLR_DATA1	(MDIO_848xx_TOP_CFG_SCRATCH_REG27)
#घोषणा MDIO_848xx_CMD_HDLR_DATA2	(MDIO_848xx_TOP_CFG_SCRATCH_REG28)
#घोषणा MDIO_848xx_CMD_HDLR_DATA3	(MDIO_848xx_TOP_CFG_SCRATCH_REG29)
#घोषणा MDIO_848xx_CMD_HDLR_DATA4	(MDIO_848xx_TOP_CFG_SCRATCH_REG30)
#घोषणा MDIO_848xx_CMD_HDLR_DATA5	(MDIO_848xx_TOP_CFG_SCRATCH_REG31)

/* Mailbox command set used by 84833/84858 */
#घोषणा PHY848xx_CMD_SET_PAIR_SWAP			0x8001
#घोषणा PHY848xx_CMD_GET_EEE_MODE			0x8008
#घोषणा PHY848xx_CMD_SET_EEE_MODE			0x8009
/* Mailbox status set used by 84833 only */
#घोषणा PHY84833_STATUS_CMD_RECEIVED			0x0001
#घोषणा PHY84833_STATUS_CMD_IN_PROGRESS			0x0002
#घोषणा PHY84833_STATUS_CMD_COMPLETE_PASS		0x0004
#घोषणा PHY84833_STATUS_CMD_COMPLETE_ERROR		0x0008
#घोषणा PHY84833_STATUS_CMD_OPEN_FOR_CMDS		0x0010
#घोषणा PHY84833_STATUS_CMD_SYSTEM_BOOT			0x0020
#घोषणा PHY84833_STATUS_CMD_NOT_OPEN_FOR_CMDS		0x0040
#घोषणा PHY84833_STATUS_CMD_CLEAR_COMPLETE		0x0080
#घोषणा PHY84833_STATUS_CMD_OPEN_OVERRIDE		0xa5a5
/* Mailbox Process */
#घोषणा PHY84833_MB_PROCESS1				1
#घोषणा PHY84833_MB_PROCESS2				2
#घोषणा PHY84833_MB_PROCESS3				3

/* Mailbox status set used by 84858 only */
#घोषणा PHY84858_STATUS_CMD_RECEIVED			0x0001
#घोषणा PHY84858_STATUS_CMD_IN_PROGRESS			0x0002
#घोषणा PHY84858_STATUS_CMD_COMPLETE_PASS		0x0004
#घोषणा PHY84858_STATUS_CMD_COMPLETE_ERROR		0x0008
#घोषणा PHY84858_STATUS_CMD_SYSTEM_BUSY			0xbbbb


/* Warpcore clause 45 addressing */
#घोषणा MDIO_WC_DEVAD					0x3
#घोषणा MDIO_WC_REG_IEEE0BLK_MIICNTL			0x0
#घोषणा MDIO_WC_REG_IEEE0BLK_AUTONEGNP			0x7
#घोषणा MDIO_WC_REG_AN_IEEE1BLK_AN_ADVERTISEMENT0	0x10
#घोषणा MDIO_WC_REG_AN_IEEE1BLK_AN_ADVERTISEMENT1	0x11
#घोषणा MDIO_WC_REG_AN_IEEE1BLK_AN_ADVERTISEMENT2	0x12
#घोषणा MDIO_WC_REG_AN_IEEE1BLK_AN_ADV2_FEC_ABILITY	0x4000
#घोषणा MDIO_WC_REG_AN_IEEE1BLK_AN_ADV2_FEC_REQ		0x8000
#घोषणा MDIO_WC_REG_PCS_STATUS2				0x0021
#घोषणा MDIO_WC_REG_PMD_KR_CONTROL			0x0096
#घोषणा MDIO_WC_REG_XGXSBLK0_XGXSCONTROL		0x8000
#घोषणा MDIO_WC_REG_XGXSBLK0_MISCCONTROL1		0x800e
#घोषणा MDIO_WC_REG_XGXSBLK1_DESKEW			0x8010
#घोषणा MDIO_WC_REG_XGXSBLK1_LANECTRL0			0x8015
#घोषणा MDIO_WC_REG_XGXSBLK1_LANECTRL1			0x8016
#घोषणा MDIO_WC_REG_XGXSBLK1_LANECTRL2			0x8017
#घोषणा MDIO_WC_REG_TX0_ANA_CTRL0			0x8061
#घोषणा MDIO_WC_REG_TX1_ANA_CTRL0			0x8071
#घोषणा MDIO_WC_REG_TX2_ANA_CTRL0			0x8081
#घोषणा MDIO_WC_REG_TX3_ANA_CTRL0			0x8091
#घोषणा MDIO_WC_REG_TX0_TX_DRIVER			0x8067
#घोषणा MDIO_WC_REG_TX0_TX_DRIVER_IFIR_OFFSET			0x01
#घोषणा MDIO_WC_REG_TX0_TX_DRIVER_IFIR_MASK				0x000e
#घोषणा MDIO_WC_REG_TX0_TX_DRIVER_IPRE_DRIVER_OFFSET		0x04
#घोषणा MDIO_WC_REG_TX0_TX_DRIVER_IPRE_DRIVER_MASK			0x00f0
#घोषणा MDIO_WC_REG_TX0_TX_DRIVER_IDRIVER_OFFSET		0x08
#घोषणा MDIO_WC_REG_TX0_TX_DRIVER_IDRIVER_MASK				0x0f00
#घोषणा MDIO_WC_REG_TX0_TX_DRIVER_POST2_COEFF_OFFSET		0x0c
#घोषणा MDIO_WC_REG_TX0_TX_DRIVER_POST2_COEFF_MASK			0x7000
#घोषणा MDIO_WC_REG_TX1_TX_DRIVER			0x8077
#घोषणा MDIO_WC_REG_TX2_TX_DRIVER			0x8087
#घोषणा MDIO_WC_REG_TX3_TX_DRIVER			0x8097
#घोषणा MDIO_WC_REG_RX0_ANARXCONTROL1G			0x80b9
#घोषणा MDIO_WC_REG_RX2_ANARXCONTROL1G			0x80d9
#घोषणा MDIO_WC_REG_RX0_PCI_CTRL			0x80ba
#घोषणा MDIO_WC_REG_RX1_PCI_CTRL			0x80ca
#घोषणा MDIO_WC_REG_RX2_PCI_CTRL			0x80da
#घोषणा MDIO_WC_REG_RX3_PCI_CTRL			0x80ea
#घोषणा MDIO_WC_REG_RXB_ANA_RX_CONTROL_PCI		0x80fa
#घोषणा MDIO_WC_REG_XGXSBLK2_UNICORE_MODE_10G		0x8104
#घोषणा MDIO_WC_REG_XGXS_STATUS3			0x8129
#घोषणा MDIO_WC_REG_PAR_DET_10G_STATUS			0x8130
#घोषणा MDIO_WC_REG_PAR_DET_10G_CTRL			0x8131
#घोषणा MDIO_WC_REG_XGXS_X2_CONTROL2			0x8141
#घोषणा MDIO_WC_REG_XGXS_X2_CONTROL3			0x8142
#घोषणा MDIO_WC_REG_XGXS_RX_LN_SWAP1			0x816B
#घोषणा MDIO_WC_REG_XGXS_TX_LN_SWAP1			0x8169
#घोषणा MDIO_WC_REG_GP2_STATUS_GP_2_0			0x81d0
#घोषणा MDIO_WC_REG_GP2_STATUS_GP_2_1			0x81d1
#घोषणा MDIO_WC_REG_GP2_STATUS_GP_2_2			0x81d2
#घोषणा MDIO_WC_REG_GP2_STATUS_GP_2_3			0x81d3
#घोषणा MDIO_WC_REG_GP2_STATUS_GP_2_4			0x81d4
#घोषणा MDIO_WC_REG_GP2_STATUS_GP_2_4_CL73_AN_CMPL 0x1000
#घोषणा MDIO_WC_REG_GP2_STATUS_GP_2_4_CL37_AN_CMPL 0x0100
#घोषणा MDIO_WC_REG_GP2_STATUS_GP_2_4_CL37_LP_AN_CAP 0x0010
#घोषणा MDIO_WC_REG_GP2_STATUS_GP_2_4_CL37_AN_CAP 0x1
#घोषणा MDIO_WC_REG_UC_INFO_B0_DEAD_TRAP		0x81EE
#घोषणा MDIO_WC_REG_UC_INFO_B1_VERSION			0x81F0
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE		0x81F2
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_LANE0_OFFSET	0x0
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_DEFAULT	    0x0
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_SFP_OPT_LR	    0x1
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_SFP_DAC	    0x2
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_SFP_XLAUI	    0x3
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_LONG_CH_6G	    0x4
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_LANE1_OFFSET	0x4
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_LANE2_OFFSET	0x8
#घोषणा MDIO_WC_REG_UC_INFO_B1_FIRMWARE_LANE3_OFFSET	0xc
#घोषणा MDIO_WC_REG_UC_INFO_B1_CRC			0x81FE
#घोषणा MDIO_WC_REG_DSC_SMC				0x8213
#घोषणा MDIO_WC_REG_DSC2B0_DSC_MISC_CTRL0		0x821e
#घोषणा MDIO_WC_REG_TX_FIR_TAP				0x82e2
#घोषणा MDIO_WC_REG_TX_FIR_TAP_PRE_TAP_OFFSET		0x00
#घोषणा MDIO_WC_REG_TX_FIR_TAP_PRE_TAP_MASK			0x000f
#घोषणा MDIO_WC_REG_TX_FIR_TAP_MAIN_TAP_OFFSET		0x04
#घोषणा MDIO_WC_REG_TX_FIR_TAP_MAIN_TAP_MASK		0x03f0
#घोषणा MDIO_WC_REG_TX_FIR_TAP_POST_TAP_OFFSET		0x0a
#घोषणा MDIO_WC_REG_TX_FIR_TAP_POST_TAP_MASK		0x7c00
#घोषणा MDIO_WC_REG_TX_FIR_TAP_ENABLE		0x8000
#घोषणा MDIO_WC_REG_CL72_USERB0_CL72_TX_FIR_TAP		0x82e2
#घोषणा MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL	0x82e3
#घोषणा MDIO_WC_REG_CL72_USERB0_CL72_OS_DEF_CTRL	0x82e6
#घोषणा MDIO_WC_REG_CL72_USERB0_CL72_BR_DEF_CTRL	0x82e7
#घोषणा MDIO_WC_REG_CL72_USERB0_CL72_2P5_DEF_CTRL	0x82e8
#घोषणा MDIO_WC_REG_CL72_USERB0_CL72_MISC4_CONTROL	0x82ec
#घोषणा MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1		0x8300
#घोषणा MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2		0x8301
#घोषणा MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X3		0x8302
#घोषणा MDIO_WC_REG_SERDESDIGITAL_STATUS1000X1		0x8304
#घोषणा MDIO_WC_REG_SERDESDIGITAL_MISC1			0x8308
#घोषणा MDIO_WC_REG_SERDESDIGITAL_MISC2			0x8309
#घोषणा MDIO_WC_REG_DIGITAL3_UP1			0x8329
#घोषणा MDIO_WC_REG_DIGITAL3_LP_UP1			 0x832c
#घोषणा MDIO_WC_REG_DIGITAL4_MISC3			0x833c
#घोषणा MDIO_WC_REG_DIGITAL4_MISC5			0x833e
#घोषणा MDIO_WC_REG_DIGITAL5_MISC6			0x8345
#घोषणा MDIO_WC_REG_DIGITAL5_MISC7			0x8349
#घोषणा MDIO_WC_REG_DIGITAL5_LINK_STATUS		0x834d
#घोषणा MDIO_WC_REG_DIGITAL5_ACTUAL_SPEED		0x834e
#घोषणा MDIO_WC_REG_DIGITAL6_MP5_NEXTPAGECTRL		0x8350
#घोषणा MDIO_WC_REG_CL49_USERB0_CTRL			0x8368
#घोषणा MDIO_WC_REG_CL73_USERB0_CTRL			0x8370
#घोषणा MDIO_WC_REG_CL73_USERB0_USTAT			0x8371
#घोषणा MDIO_WC_REG_CL73_BAM_CTRL1			0x8372
#घोषणा MDIO_WC_REG_CL73_BAM_CTRL2			0x8373
#घोषणा MDIO_WC_REG_CL73_BAM_CTRL3			0x8374
#घोषणा MDIO_WC_REG_CL73_BAM_CODE_FIELD			0x837b
#घोषणा MDIO_WC_REG_EEE_COMBO_CONTROL0			0x8390
#घोषणा MDIO_WC_REG_TX66_CONTROL			0x83b0
#घोषणा MDIO_WC_REG_RX66_CONTROL			0x83c0
#घोषणा MDIO_WC_REG_RX66_SCW0				0x83c2
#घोषणा MDIO_WC_REG_RX66_SCW1				0x83c3
#घोषणा MDIO_WC_REG_RX66_SCW2				0x83c4
#घोषणा MDIO_WC_REG_RX66_SCW3				0x83c5
#घोषणा MDIO_WC_REG_RX66_SCW0_MASK			0x83c6
#घोषणा MDIO_WC_REG_RX66_SCW1_MASK			0x83c7
#घोषणा MDIO_WC_REG_RX66_SCW2_MASK			0x83c8
#घोषणा MDIO_WC_REG_RX66_SCW3_MASK			0x83c9
#घोषणा MDIO_WC_REG_FX100_CTRL1				0x8400
#घोषणा MDIO_WC_REG_FX100_CTRL3				0x8402
#घोषणा MDIO_WC_REG_CL82_USERB1_TX_CTRL5		0x8436
#घोषणा MDIO_WC_REG_CL82_USERB1_TX_CTRL6		0x8437
#घोषणा MDIO_WC_REG_CL82_USERB1_TX_CTRL7		0x8438
#घोषणा MDIO_WC_REG_CL82_USERB1_TX_CTRL9		0x8439
#घोषणा MDIO_WC_REG_CL82_USERB1_RX_CTRL10		0x843a
#घोषणा MDIO_WC_REG_CL82_USERB1_RX_CTRL11		0x843b
#घोषणा MDIO_WC_REG_ETA_CL73_OUI1			0x8453
#घोषणा MDIO_WC_REG_ETA_CL73_OUI2			0x8454
#घोषणा MDIO_WC_REG_ETA_CL73_OUI3			0x8455
#घोषणा MDIO_WC_REG_ETA_CL73_LD_BAM_CODE		0x8456
#घोषणा MDIO_WC_REG_ETA_CL73_LD_UD_CODE			0x8457
#घोषणा MDIO_WC_REG_MICROBLK_CMD			0xffc2
#घोषणा MDIO_WC_REG_MICROBLK_DL_STATUS			0xffc5
#घोषणा MDIO_WC_REG_MICROBLK_CMD3			0xffcc

#घोषणा MDIO_WC_REG_AERBLK_AER				0xffde
#घोषणा MDIO_WC_REG_COMBO_IEEE0_MIICTRL			0xffe0
#घोषणा MDIO_WC_REG_COMBO_IEEE0_MIIISTAT		0xffe1

#घोषणा MDIO_WC0_XGXS_BLK2_LANE_RESET			0x810A
#घोषणा MDIO_WC0_XGXS_BLK2_LANE_RESET_RX_BITSHIFT	0
#घोषणा MDIO_WC0_XGXS_BLK2_LANE_RESET_TX_BITSHIFT	4

#घोषणा MDIO_WC0_XGXS_BLK6_XGXS_X2_CONTROL2		0x8141

#घोषणा DIGITAL5_ACTUAL_SPEED_TX_MASK			0x003f

/* 54618se */
#घोषणा MDIO_REG_GPHY_PHYID_LSB				0x3
#घोषणा MDIO_REG_GPHY_ID_54618SE		0x5cd5
#घोषणा MDIO_REG_GPHY_CL45_ADDR_REG			0xd
#घोषणा MDIO_REG_GPHY_CL45_DATA_REG			0xe
#घोषणा MDIO_REG_GPHY_EEE_RESOLVED		0x803e
#घोषणा MDIO_REG_GPHY_EXP_ACCESS_GATE			0x15
#घोषणा MDIO_REG_GPHY_EXP_ACCESS			0x17
#घोषणा MDIO_REG_GPHY_EXP_ACCESS_TOP		0xd00
#घोषणा MDIO_REG_GPHY_EXP_TOP_2K_BUF		0x40
#घोषणा MDIO_REG_GPHY_AUX_STATUS			0x19
#घोषणा MDIO_REG_INTR_STATUS				0x1a
#घोषणा MDIO_REG_INTR_MASK				0x1b
#घोषणा MDIO_REG_INTR_MASK_LINK_STATUS			(0x1 << 1)
#घोषणा MDIO_REG_GPHY_SHADOW				0x1c
#घोषणा MDIO_REG_GPHY_SHADOW_LED_SEL1			(0x0d << 10)
#घोषणा MDIO_REG_GPHY_SHADOW_LED_SEL2			(0x0e << 10)
#घोषणा MDIO_REG_GPHY_SHADOW_WR_ENA			(0x1 << 15)
#घोषणा MDIO_REG_GPHY_SHADOW_AUTO_DET_MED		(0x1e << 10)
#घोषणा MDIO_REG_GPHY_SHADOW_INVERT_FIB_SD		(0x1 << 8)

#घोषणा IGU_FUNC_BASE			0x0400

#घोषणा IGU_ADDR_MSIX			0x0000
#घोषणा IGU_ADDR_INT_ACK		0x0200
#घोषणा IGU_ADDR_PROD_UPD		0x0201
#घोषणा IGU_ADDR_ATTN_BITS_UPD	0x0202
#घोषणा IGU_ADDR_ATTN_BITS_SET	0x0203
#घोषणा IGU_ADDR_ATTN_BITS_CLR	0x0204
#घोषणा IGU_ADDR_COALESCE_NOW	0x0205
#घोषणा IGU_ADDR_SIMD_MASK		0x0206
#घोषणा IGU_ADDR_SIMD_NOMASK	0x0207
#घोषणा IGU_ADDR_MSI_CTL		0x0210
#घोषणा IGU_ADDR_MSI_ADDR_LO	0x0211
#घोषणा IGU_ADDR_MSI_ADDR_HI	0x0212
#घोषणा IGU_ADDR_MSI_DATA		0x0213

#घोषणा IGU_USE_REGISTER_ustorm_type_0_sb_cleanup  0
#घोषणा IGU_USE_REGISTER_ustorm_type_1_sb_cleanup  1
#घोषणा IGU_USE_REGISTER_cstorm_type_0_sb_cleanup  2
#घोषणा IGU_USE_REGISTER_cstorm_type_1_sb_cleanup  3

#घोषणा COMMAND_REG_INT_ACK	    0x0
#घोषणा COMMAND_REG_PROD_UPD	    0x4
#घोषणा COMMAND_REG_ATTN_BITS_UPD   0x8
#घोषणा COMMAND_REG_ATTN_BITS_SET   0xc
#घोषणा COMMAND_REG_ATTN_BITS_CLR   0x10
#घोषणा COMMAND_REG_COALESCE_NOW    0x14
#घोषणा COMMAND_REG_SIMD_MASK	    0x18
#घोषणा COMMAND_REG_SIMD_NOMASK     0x1c


#घोषणा IGU_MEM_BASE						0x0000

#घोषणा IGU_MEM_MSIX_BASE					0x0000
#घोषणा IGU_MEM_MSIX_UPPER					0x007f
#घोषणा IGU_MEM_MSIX_RESERVED_UPPER			0x01ff

#घोषणा IGU_MEM_PBA_MSIX_BASE				0x0200
#घोषणा IGU_MEM_PBA_MSIX_UPPER				0x0200

#घोषणा IGU_CMD_BACKWARD_COMP_PROD_UPD		0x0201
#घोषणा IGU_MEM_PBA_MSIX_RESERVED_UPPER 	0x03ff

#घोषणा IGU_CMD_INT_ACK_BASE				0x0400
#घोषणा IGU_CMD_INT_ACK_UPPER\
	(IGU_CMD_INT_ACK_BASE + MAX_SB_PER_PORT * NUM_OF_PORTS_PER_PATH - 1)
#घोषणा IGU_CMD_INT_ACK_RESERVED_UPPER		0x04ff

#घोषणा IGU_CMD_E2_PROD_UPD_BASE			0x0500
#घोषणा IGU_CMD_E2_PROD_UPD_UPPER\
	(IGU_CMD_E2_PROD_UPD_BASE + MAX_SB_PER_PORT * NUM_OF_PORTS_PER_PATH - 1)
#घोषणा IGU_CMD_E2_PROD_UPD_RESERVED_UPPER	0x059f

#घोषणा IGU_CMD_ATTN_BIT_UPD_UPPER			0x05a0
#घोषणा IGU_CMD_ATTN_BIT_SET_UPPER			0x05a1
#घोषणा IGU_CMD_ATTN_BIT_CLR_UPPER			0x05a2

#घोषणा IGU_REG_SISR_MDPC_WMASK_UPPER		0x05a3
#घोषणा IGU_REG_SISR_MDPC_WMASK_LSB_UPPER	0x05a4
#घोषणा IGU_REG_SISR_MDPC_WMASK_MSB_UPPER	0x05a5
#घोषणा IGU_REG_SISR_MDPC_WOMASK_UPPER		0x05a6

#घोषणा IGU_REG_RESERVED_UPPER				0x05ff
/* Fields of IGU PF CONFIGURATION REGISTER */
#घोषणा IGU_PF_CONF_FUNC_EN	  (0x1<<0)  /* function enable	      */
#घोषणा IGU_PF_CONF_MSI_MSIX_EN   (0x1<<1)  /* MSI/MSIX enable	      */
#घोषणा IGU_PF_CONF_INT_LINE_EN   (0x1<<2)  /* INT enable	      */
#घोषणा IGU_PF_CONF_ATTN_BIT_EN   (0x1<<3)  /* attention enable       */
#घोषणा IGU_PF_CONF_SINGLE_ISR_EN (0x1<<4)  /* single ISR mode enable */
#घोषणा IGU_PF_CONF_SIMD_MODE	  (0x1<<5)  /* simd all ones mode     */

/* Fields of IGU VF CONFIGURATION REGISTER */
#घोषणा IGU_VF_CONF_FUNC_EN	   (0x1<<0)  /* function enable        */
#घोषणा IGU_VF_CONF_MSI_MSIX_EN    (0x1<<1)  /* MSI/MSIX enable        */
#घोषणा IGU_VF_CONF_PARENT_MASK    (0x3<<2)  /* Parent PF	       */
#घोषणा IGU_VF_CONF_PARENT_SHIFT   2	     /* Parent PF	       */
#घोषणा IGU_VF_CONF_SINGLE_ISR_EN  (0x1<<4)  /* single ISR mode enable */


#घोषणा IGU_BC_DSB_NUM_SEGS    5
#घोषणा IGU_BC_NDSB_NUM_SEGS   2
#घोषणा IGU_NORM_DSB_NUM_SEGS  2
#घोषणा IGU_NORM_NDSB_NUM_SEGS 1
#घोषणा IGU_BC_BASE_DSB_PROD   128
#घोषणा IGU_NORM_BASE_DSB_PROD 136

	/* FID (अगर VF - [6] = 0; [5:0] = VF number; अगर PF - [6] = 1; \
	[5:2] = 0; [1:0] = PF number) */
#घोषणा IGU_FID_ENCODE_IS_PF	    (0x1<<6)
#घोषणा IGU_FID_ENCODE_IS_PF_SHIFT  6
#घोषणा IGU_FID_VF_NUM_MASK	    (0x3f)
#घोषणा IGU_FID_PF_NUM_MASK	    (0x7)

#घोषणा IGU_REG_MAPPING_MEMORY_VALID		(1<<0)
#घोषणा IGU_REG_MAPPING_MEMORY_VECTOR_MASK	(0x3F<<1)
#घोषणा IGU_REG_MAPPING_MEMORY_VECTOR_SHIFT	1
#घोषणा IGU_REG_MAPPING_MEMORY_FID_MASK	(0x7F<<7)
#घोषणा IGU_REG_MAPPING_MEMORY_FID_SHIFT	7


#घोषणा CDU_REGION_NUMBER_XCM_AG 2
#घोषणा CDU_REGION_NUMBER_UCM_AG 4


/* String-to-compress [31:8] = CID (all 24 bits)
 * String-to-compress [7:4] = Region
 * String-to-compress [3:0] = Type
 */
#घोषणा CDU_VALID_DATA(_cid, _region, _type)\
	(((_cid) << 8) | (((_region)&0xf)<<4) | (((_type)&0xf)))
#घोषणा CDU_CRC8(_cid, _region, _type)\
	(calc_crc8(CDU_VALID_DATA(_cid, _region, _type), 0xff))
#घोषणा CDU_RSRVD_VALUE_TYPE_A(_cid, _region, _type)\
	(0x80 | ((CDU_CRC8(_cid, _region, _type)) & 0x7f))
#घोषणा CDU_RSRVD_VALUE_TYPE_B(_crc, _type)\
	(0x80 | ((_type)&0xf << 3) | ((CDU_CRC8(_cid, _region, _type)) & 0x7))
#घोषणा CDU_RSRVD_INVALIDATE_CONTEXT_VALUE(_val) ((_val) & ~0x80)

/* IdleChk रेजिस्टरs */
#घोषणा PXP_REG_HST_VF_DISABLED_ERROR_VALID			 0x1030bc
#घोषणा PXP_REG_HST_VF_DISABLED_ERROR_DATA			 0x1030b8
#घोषणा PXP_REG_HST_PER_VIOLATION_VALID				 0x1030e0
#घोषणा PXP_REG_HST_INCORRECT_ACCESS_VALID			 0x1030cc
#घोषणा PXP2_REG_RD_CPL_ERR_DETAILS				 0x120778
#घोषणा PXP2_REG_RD_CPL_ERR_DETAILS2				 0x12077c
#घोषणा PXP2_REG_RQ_GARB					 0x120748
#घोषणा PBF_REG_DISABLE_NEW_TASK_PROC_Q0			 0x15c1bc
#घोषणा PBF_REG_DISABLE_NEW_TASK_PROC_Q1			 0x15c1c0
#घोषणा PBF_REG_DISABLE_NEW_TASK_PROC_Q2			 0x15c1c4
#घोषणा PBF_REG_DISABLE_NEW_TASK_PROC_Q3			 0x15c1c8
#घोषणा PBF_REG_DISABLE_NEW_TASK_PROC_Q4			 0x15c1cc
#घोषणा PBF_REG_DISABLE_NEW_TASK_PROC_Q5			 0x15c1d0
#घोषणा PBF_REG_CREDIT_Q2					 0x140344
#घोषणा PBF_REG_CREDIT_Q3					 0x140348
#घोषणा PBF_REG_CREDIT_Q4					 0x14034c
#घोषणा PBF_REG_CREDIT_Q5					 0x140350
#घोषणा PBF_REG_INIT_CRD_Q2					 0x15c238
#घोषणा PBF_REG_INIT_CRD_Q3					 0x15c23c
#घोषणा PBF_REG_INIT_CRD_Q4					 0x15c240
#घोषणा PBF_REG_INIT_CRD_Q5					 0x15c244
#घोषणा PBF_REG_TASK_CNT_Q0					 0x140374
#घोषणा PBF_REG_TASK_CNT_Q1					 0x140378
#घोषणा PBF_REG_TASK_CNT_Q2					 0x14037c
#घोषणा PBF_REG_TASK_CNT_Q3					 0x140380
#घोषणा PBF_REG_TASK_CNT_Q4					 0x140384
#घोषणा PBF_REG_TASK_CNT_Q5					 0x140388
#घोषणा PBF_REG_TASK_CNT_LB_Q					 0x140370
#घोषणा QM_REG_BYTECRD0						 0x16e6fc
#घोषणा QM_REG_BYTECRD1						 0x16e700
#घोषणा QM_REG_BYTECRD2						 0x16e704
#घोषणा QM_REG_BYTECRD3						 0x16e7ac
#घोषणा QM_REG_BYTECRD4						 0x16e7b0
#घोषणा QM_REG_BYTECRD5						 0x16e7b4
#घोषणा QM_REG_BYTECRD6						 0x16e7b8
#घोषणा QM_REG_BYTECRDCMDQ_0					 0x16e6e8
#घोषणा QM_REG_BYTECRDERRREG					 0x16e708
#घोषणा MISC_REG_GRC_TIMEOUT_ATTN_FULL_FID			 0xa714
#घोषणा QM_REG_VOQCREDIT_2					 0x1682d8
#घोषणा QM_REG_VOQCREDIT_3					 0x1682dc
#घोषणा QM_REG_VOQCREDIT_5					 0x1682e4
#घोषणा QM_REG_VOQCREDIT_6					 0x1682e8
#घोषणा QM_REG_VOQINITCREDIT_3					 0x16806c
#घोषणा QM_REG_VOQINITCREDIT_6					 0x168078
#घोषणा QM_REG_FWVOQ0TOHWVOQ					 0x16e7bc
#घोषणा QM_REG_FWVOQ1TOHWVOQ					 0x16e7c0
#घोषणा QM_REG_FWVOQ2TOHWVOQ					 0x16e7c4
#घोषणा QM_REG_FWVOQ3TOHWVOQ					 0x16e7c8
#घोषणा QM_REG_FWVOQ4TOHWVOQ					 0x16e7cc
#घोषणा QM_REG_FWVOQ5TOHWVOQ					 0x16e7d0
#घोषणा QM_REG_FWVOQ6TOHWVOQ					 0x16e7d4
#घोषणा QM_REG_FWVOQ7TOHWVOQ					 0x16e7d8
#घोषणा NIG_REG_INGRESS_EOP_PORT0_EMPTY				 0x104ec
#घोषणा NIG_REG_INGRESS_EOP_PORT1_EMPTY				 0x104f8
#घोषणा NIG_REG_INGRESS_RMP0_DSCR_EMPTY				 0x10530
#घोषणा NIG_REG_INGRESS_RMP1_DSCR_EMPTY				 0x10538
#घोषणा NIG_REG_INGRESS_LB_PBF_DELAY_EMPTY			 0x10508
#घोषणा NIG_REG_EGRESS_MNG0_FIFO_EMPTY				 0x10460
#घोषणा NIG_REG_EGRESS_MNG1_FIFO_EMPTY				 0x10474
#घोषणा NIG_REG_EGRESS_DEBUG_FIFO_EMPTY				 0x10418
#घोषणा NIG_REG_EGRESS_DELAY0_EMPTY				 0x10420
#घोषणा NIG_REG_EGRESS_DELAY1_EMPTY				 0x10428
#घोषणा NIG_REG_LLH0_FIFO_EMPTY					 0x10548
#घोषणा NIG_REG_LLH1_FIFO_EMPTY					 0x10558
#घोषणा NIG_REG_P0_TX_MNG_HOST_FIFO_EMPTY			 0x182a8
#घोषणा NIG_REG_P0_TLLH_FIFO_EMPTY				 0x18308
#घोषणा NIG_REG_P0_HBUF_DSCR_EMPTY				 0x18318
#घोषणा NIG_REG_P1_HBUF_DSCR_EMPTY				 0x18348
#घोषणा NIG_REG_P0_RX_MACFIFO_EMPTY				 0x18570
#घोषणा NIG_REG_P0_TX_MACFIFO_EMPTY				 0x18578
#घोषणा NIG_REG_EGRESS_DELAY2_EMPTY				 0x1862c
#घोषणा NIG_REG_EGRESS_DELAY3_EMPTY				 0x18630
#घोषणा NIG_REG_EGRESS_DELAY4_EMPTY				 0x18634
#घोषणा NIG_REG_EGRESS_DELAY5_EMPTY				 0x18638

/******************************************************************************
 * Description:
 *	   Calculates crc 8 on a word value: polynomial 0-1-2-8
 *	   Code was translated from Verilog.
 * Return:
 *****************************************************************************/
अटल अंतरभूत u8 calc_crc8(u32 data, u8 crc)
अणु
	u8 D[32];
	u8 NewCRC[8];
	u8 C[8];
	u8 crc_res;
	u8 i;

	/* split the data पूर्णांकo 31 bits */
	क्रम (i = 0; i < 32; i++) अणु
		D[i] = (u8)(data & 1);
		data = data >> 1;
	पूर्ण

	/* split the crc पूर्णांकo 8 bits */
	क्रम (i = 0; i < 8; i++) अणु
		C[i] = crc & 1;
		crc = crc >> 1;
	पूर्ण

	NewCRC[0] = D[31] ^ D[30] ^ D[28] ^ D[23] ^ D[21] ^ D[19] ^ D[18] ^
		    D[16] ^ D[14] ^ D[12] ^ D[8] ^ D[7] ^ D[6] ^ D[0] ^ C[4] ^
		    C[6] ^ C[7];
	NewCRC[1] = D[30] ^ D[29] ^ D[28] ^ D[24] ^ D[23] ^ D[22] ^ D[21] ^
		    D[20] ^ D[18] ^ D[17] ^ D[16] ^ D[15] ^ D[14] ^ D[13] ^
		    D[12] ^ D[9] ^ D[6] ^ D[1] ^ D[0] ^ C[0] ^ C[4] ^ C[5] ^
		    C[6];
	NewCRC[2] = D[29] ^ D[28] ^ D[25] ^ D[24] ^ D[22] ^ D[17] ^ D[15] ^
		    D[13] ^ D[12] ^ D[10] ^ D[8] ^ D[6] ^ D[2] ^ D[1] ^ D[0] ^
		    C[0] ^ C[1] ^ C[4] ^ C[5];
	NewCRC[3] = D[30] ^ D[29] ^ D[26] ^ D[25] ^ D[23] ^ D[18] ^ D[16] ^
		    D[14] ^ D[13] ^ D[11] ^ D[9] ^ D[7] ^ D[3] ^ D[2] ^ D[1] ^
		    C[1] ^ C[2] ^ C[5] ^ C[6];
	NewCRC[4] = D[31] ^ D[30] ^ D[27] ^ D[26] ^ D[24] ^ D[19] ^ D[17] ^
		    D[15] ^ D[14] ^ D[12] ^ D[10] ^ D[8] ^ D[4] ^ D[3] ^ D[2] ^
		    C[0] ^ C[2] ^ C[3] ^ C[6] ^ C[7];
	NewCRC[5] = D[31] ^ D[28] ^ D[27] ^ D[25] ^ D[20] ^ D[18] ^ D[16] ^
		    D[15] ^ D[13] ^ D[11] ^ D[9] ^ D[5] ^ D[4] ^ D[3] ^ C[1] ^
		    C[3] ^ C[4] ^ C[7];
	NewCRC[6] = D[29] ^ D[28] ^ D[26] ^ D[21] ^ D[19] ^ D[17] ^ D[16] ^
		    D[14] ^ D[12] ^ D[10] ^ D[6] ^ D[5] ^ D[4] ^ C[2] ^ C[4] ^
		    C[5];
	NewCRC[7] = D[30] ^ D[29] ^ D[27] ^ D[22] ^ D[20] ^ D[18] ^ D[17] ^
		    D[15] ^ D[13] ^ D[11] ^ D[7] ^ D[6] ^ D[5] ^ C[3] ^ C[5] ^
		    C[6];

	crc_res = 0;
	क्रम (i = 0; i < 8; i++)
		crc_res |= (NewCRC[i] << i);

	वापस crc_res;
पूर्ण
#पूर्ण_अगर /* BNX2X_REG_H */
