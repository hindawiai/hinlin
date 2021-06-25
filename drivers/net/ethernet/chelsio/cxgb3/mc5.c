<शैली गुरु>
/*
 * Copyright (c) 2003-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश "common.h"
#समावेश "regs.h"

क्रमागत अणु
	IDT75P52100 = 4,
	IDT75N43102 = 5
पूर्ण;

/* DBGI command mode */
क्रमागत अणु
	DBGI_MODE_MBUS = 0,
	DBGI_MODE_IDT52100 = 5
पूर्ण;

/* IDT 75P52100 commands */
#घोषणा IDT_CMD_READ   0
#घोषणा IDT_CMD_WRITE  1
#घोषणा IDT_CMD_SEARCH 2
#घोषणा IDT_CMD_LEARN  3

/* IDT LAR रेजिस्टर address and value क्रम 144-bit mode (low 32 bits) */
#घोषणा IDT_LAR_ADR0   	0x180006
#घोषणा IDT_LAR_MODE144	0xffff0000

/* IDT SCR and SSR addresses (low 32 bits) */
#घोषणा IDT_SCR_ADR0  0x180000
#घोषणा IDT_SSR0_ADR0 0x180002
#घोषणा IDT_SSR1_ADR0 0x180004

/* IDT GMR base address (low 32 bits) */
#घोषणा IDT_GMR_BASE_ADR0 0x180020

/* IDT data and mask array base addresses (low 32 bits) */
#घोषणा IDT_DATARY_BASE_ADR0 0
#घोषणा IDT_MSKARY_BASE_ADR0 0x80000

/* IDT 75N43102 commands */
#घोषणा IDT4_CMD_SEARCH144 3
#घोषणा IDT4_CMD_WRITE     4
#घोषणा IDT4_CMD_READ      5

/* IDT 75N43102 SCR address (low 32 bits) */
#घोषणा IDT4_SCR_ADR0  0x3

/* IDT 75N43102 GMR base addresses (low 32 bits) */
#घोषणा IDT4_GMR_BASE0 0x10
#घोषणा IDT4_GMR_BASE1 0x20
#घोषणा IDT4_GMR_BASE2 0x30

/* IDT 75N43102 data and mask array base addresses (low 32 bits) */
#घोषणा IDT4_DATARY_BASE_ADR0 0x1000000
#घोषणा IDT4_MSKARY_BASE_ADR0 0x2000000

#घोषणा MAX_WRITE_ATTEMPTS 5

#घोषणा MAX_ROUTES 2048

/*
 * Issue a command to the TCAM and रुको क्रम its completion.  The address and
 * any data required by the command must have been setup by the caller.
 */
अटल पूर्णांक mc5_cmd_ग_लिखो(काष्ठा adapter *adapter, u32 cmd)
अणु
	t3_ग_लिखो_reg(adapter, A_MC5_DB_DBGI_REQ_CMD, cmd);
	वापस t3_रुको_op_करोne(adapter, A_MC5_DB_DBGI_RSP_STATUS,
			       F_DBGIRSPVALID, 1, MAX_WRITE_ATTEMPTS, 1);
पूर्ण

अटल अंतरभूत व्योम dbgi_wr_data3(काष्ठा adapter *adapter, u32 v1, u32 v2,
				 u32 v3)
अणु
	t3_ग_लिखो_reg(adapter, A_MC5_DB_DBGI_REQ_DATA0, v1);
	t3_ग_लिखो_reg(adapter, A_MC5_DB_DBGI_REQ_DATA1, v2);
	t3_ग_लिखो_reg(adapter, A_MC5_DB_DBGI_REQ_DATA2, v3);
पूर्ण

/*
 * Write data to the TCAM रेजिस्टर at address (0, 0, addr_lo) using the TCAM
 * command cmd.  The data to be written must have been set up by the caller.
 * Returns -1 on failure, 0 on success.
 */
अटल पूर्णांक mc5_ग_लिखो(काष्ठा adapter *adapter, u32 addr_lo, u32 cmd)
अणु
	t3_ग_लिखो_reg(adapter, A_MC5_DB_DBGI_REQ_ADDR0, addr_lo);
	अगर (mc5_cmd_ग_लिखो(adapter, cmd) == 0)
		वापस 0;
	CH_ERR(adapter, "MC5 timeout writing to TCAM address 0x%x\n",
	       addr_lo);
	वापस -1;
पूर्ण

अटल पूर्णांक init_mask_data_array(काष्ठा mc5 *mc5, u32 mask_array_base,
				u32 data_array_base, u32 ग_लिखो_cmd,
				पूर्णांक addr_shअगरt)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा adapter *adap = mc5->adapter;

	/*
	 * We need the size of the TCAM data and mask arrays in terms of
	 * 72-bit entries.
	 */
	अचिन्हित पूर्णांक size72 = mc5->tcam_size;
	अचिन्हित पूर्णांक server_base = t3_पढ़ो_reg(adap, A_MC5_DB_SERVER_INDEX);

	अगर (mc5->mode == MC5_MODE_144_BIT) अणु
		size72 *= 2;	/* 1 144-bit entry is 2 72-bit entries */
		server_base *= 2;
	पूर्ण

	/* Clear the data array */
	dbgi_wr_data3(adap, 0, 0, 0);
	क्रम (i = 0; i < size72; i++)
		अगर (mc5_ग_लिखो(adap, data_array_base + (i << addr_shअगरt),
			      ग_लिखो_cmd))
			वापस -1;

	/* Initialize the mask array. */
	dbgi_wr_data3(adap, 0xffffffff, 0xffffffff, 0xff);
	क्रम (i = 0; i < size72; i++) अणु
		अगर (i == server_base)	/* entering server or routing region */
			t3_ग_लिखो_reg(adap, A_MC5_DB_DBGI_REQ_DATA0,
				     mc5->mode == MC5_MODE_144_BIT ?
				     0xfffffff9 : 0xfffffffd);
		अगर (mc5_ग_लिखो(adap, mask_array_base + (i << addr_shअगरt),
			      ग_लिखो_cmd))
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक init_idt52100(काष्ठा mc5 *mc5)
अणु
	पूर्णांक i;
	काष्ठा adapter *adap = mc5->adapter;

	t3_ग_लिखो_reg(adap, A_MC5_DB_RSP_LATENCY,
		     V_RDLAT(0x15) | V_LRNLAT(0x15) | V_SRCHLAT(0x15));
	t3_ग_लिखो_reg(adap, A_MC5_DB_PART_ID_INDEX, 2);

	/*
	 * Use GMRs 14-15 क्रम ELOOKUP, GMRs 12-13 क्रम SYN lookups, and
	 * GMRs 8-9 क्रम ACK- and AOPEN searches.
	 */
	t3_ग_लिखो_reg(adap, A_MC5_DB_POPEN_DATA_WR_CMD, IDT_CMD_WRITE);
	t3_ग_लिखो_reg(adap, A_MC5_DB_POPEN_MASK_WR_CMD, IDT_CMD_WRITE);
	t3_ग_लिखो_reg(adap, A_MC5_DB_AOPEN_SRCH_CMD, IDT_CMD_SEARCH);
	t3_ग_लिखो_reg(adap, A_MC5_DB_AOPEN_LRN_CMD, IDT_CMD_LEARN);
	t3_ग_लिखो_reg(adap, A_MC5_DB_SYN_SRCH_CMD, IDT_CMD_SEARCH | 0x6000);
	t3_ग_लिखो_reg(adap, A_MC5_DB_SYN_LRN_CMD, IDT_CMD_LEARN);
	t3_ग_लिखो_reg(adap, A_MC5_DB_ACK_SRCH_CMD, IDT_CMD_SEARCH);
	t3_ग_लिखो_reg(adap, A_MC5_DB_ACK_LRN_CMD, IDT_CMD_LEARN);
	t3_ग_लिखो_reg(adap, A_MC5_DB_ILOOKUP_CMD, IDT_CMD_SEARCH);
	t3_ग_लिखो_reg(adap, A_MC5_DB_ELOOKUP_CMD, IDT_CMD_SEARCH | 0x7000);
	t3_ग_लिखो_reg(adap, A_MC5_DB_DATA_WRITE_CMD, IDT_CMD_WRITE);
	t3_ग_लिखो_reg(adap, A_MC5_DB_DATA_READ_CMD, IDT_CMD_READ);

	/* Set DBGI command mode क्रम IDT TCAM. */
	t3_ग_लिखो_reg(adap, A_MC5_DB_DBGI_CONFIG, DBGI_MODE_IDT52100);

	/* Set up LAR */
	dbgi_wr_data3(adap, IDT_LAR_MODE144, 0, 0);
	अगर (mc5_ग_लिखो(adap, IDT_LAR_ADR0, IDT_CMD_WRITE))
		जाओ err;

	/* Set up SSRs */
	dbgi_wr_data3(adap, 0xffffffff, 0xffffffff, 0);
	अगर (mc5_ग_लिखो(adap, IDT_SSR0_ADR0, IDT_CMD_WRITE) ||
	    mc5_ग_लिखो(adap, IDT_SSR1_ADR0, IDT_CMD_WRITE))
		जाओ err;

	/* Set up GMRs */
	क्रम (i = 0; i < 32; ++i) अणु
		अगर (i >= 12 && i < 15)
			dbgi_wr_data3(adap, 0xfffffff9, 0xffffffff, 0xff);
		अन्यथा अगर (i == 15)
			dbgi_wr_data3(adap, 0xfffffff9, 0xffff8007, 0xff);
		अन्यथा
			dbgi_wr_data3(adap, 0xffffffff, 0xffffffff, 0xff);

		अगर (mc5_ग_लिखो(adap, IDT_GMR_BASE_ADR0 + i, IDT_CMD_WRITE))
			जाओ err;
	पूर्ण

	/* Set up SCR */
	dbgi_wr_data3(adap, 1, 0, 0);
	अगर (mc5_ग_लिखो(adap, IDT_SCR_ADR0, IDT_CMD_WRITE))
		जाओ err;

	वापस init_mask_data_array(mc5, IDT_MSKARY_BASE_ADR0,
				    IDT_DATARY_BASE_ADR0, IDT_CMD_WRITE, 0);
err:
	वापस -EIO;
पूर्ण

अटल पूर्णांक init_idt43102(काष्ठा mc5 *mc5)
अणु
	पूर्णांक i;
	काष्ठा adapter *adap = mc5->adapter;

	t3_ग_लिखो_reg(adap, A_MC5_DB_RSP_LATENCY,
		     adap->params.rev == 0 ? V_RDLAT(0xd) | V_SRCHLAT(0x11) :
		     V_RDLAT(0xd) | V_SRCHLAT(0x12));

	/*
	 * Use GMRs 24-25 क्रम ELOOKUP, GMRs 20-21 क्रम SYN lookups, and no mask
	 * क्रम ACK- and AOPEN searches.
	 */
	t3_ग_लिखो_reg(adap, A_MC5_DB_POPEN_DATA_WR_CMD, IDT4_CMD_WRITE);
	t3_ग_लिखो_reg(adap, A_MC5_DB_POPEN_MASK_WR_CMD, IDT4_CMD_WRITE);
	t3_ग_लिखो_reg(adap, A_MC5_DB_AOPEN_SRCH_CMD,
		     IDT4_CMD_SEARCH144 | 0x3800);
	t3_ग_लिखो_reg(adap, A_MC5_DB_SYN_SRCH_CMD, IDT4_CMD_SEARCH144);
	t3_ग_लिखो_reg(adap, A_MC5_DB_ACK_SRCH_CMD, IDT4_CMD_SEARCH144 | 0x3800);
	t3_ग_लिखो_reg(adap, A_MC5_DB_ILOOKUP_CMD, IDT4_CMD_SEARCH144 | 0x3800);
	t3_ग_लिखो_reg(adap, A_MC5_DB_ELOOKUP_CMD, IDT4_CMD_SEARCH144 | 0x800);
	t3_ग_लिखो_reg(adap, A_MC5_DB_DATA_WRITE_CMD, IDT4_CMD_WRITE);
	t3_ग_लिखो_reg(adap, A_MC5_DB_DATA_READ_CMD, IDT4_CMD_READ);

	t3_ग_लिखो_reg(adap, A_MC5_DB_PART_ID_INDEX, 3);

	/* Set DBGI command mode क्रम IDT TCAM. */
	t3_ग_लिखो_reg(adap, A_MC5_DB_DBGI_CONFIG, DBGI_MODE_IDT52100);

	/* Set up GMRs */
	dbgi_wr_data3(adap, 0xffffffff, 0xffffffff, 0xff);
	क्रम (i = 0; i < 7; ++i)
		अगर (mc5_ग_लिखो(adap, IDT4_GMR_BASE0 + i, IDT4_CMD_WRITE))
			जाओ err;

	क्रम (i = 0; i < 4; ++i)
		अगर (mc5_ग_लिखो(adap, IDT4_GMR_BASE2 + i, IDT4_CMD_WRITE))
			जाओ err;

	dbgi_wr_data3(adap, 0xfffffff9, 0xffffffff, 0xff);
	अगर (mc5_ग_लिखो(adap, IDT4_GMR_BASE1, IDT4_CMD_WRITE) ||
	    mc5_ग_लिखो(adap, IDT4_GMR_BASE1 + 1, IDT4_CMD_WRITE) ||
	    mc5_ग_लिखो(adap, IDT4_GMR_BASE1 + 4, IDT4_CMD_WRITE))
		जाओ err;

	dbgi_wr_data3(adap, 0xfffffff9, 0xffff8007, 0xff);
	अगर (mc5_ग_लिखो(adap, IDT4_GMR_BASE1 + 5, IDT4_CMD_WRITE))
		जाओ err;

	/* Set up SCR */
	dbgi_wr_data3(adap, 0xf0000000, 0, 0);
	अगर (mc5_ग_लिखो(adap, IDT4_SCR_ADR0, IDT4_CMD_WRITE))
		जाओ err;

	वापस init_mask_data_array(mc5, IDT4_MSKARY_BASE_ADR0,
				    IDT4_DATARY_BASE_ADR0, IDT4_CMD_WRITE, 1);
err:
	वापस -EIO;
पूर्ण

/* Put MC5 in DBGI mode. */
अटल अंतरभूत व्योम mc5_dbgi_mode_enable(स्थिर काष्ठा mc5 *mc5)
अणु
	t3_ग_लिखो_reg(mc5->adapter, A_MC5_DB_CONFIG,
		     V_TMMODE(mc5->mode == MC5_MODE_72_BIT) | F_DBGIEN);
पूर्ण

/* Put MC5 in M-Bus mode. */
अटल व्योम mc5_dbgi_mode_disable(स्थिर काष्ठा mc5 *mc5)
अणु
	t3_ग_लिखो_reg(mc5->adapter, A_MC5_DB_CONFIG,
		     V_TMMODE(mc5->mode == MC5_MODE_72_BIT) |
		     V_COMPEN(mc5->mode == MC5_MODE_72_BIT) |
		     V_PRTYEN(mc5->parity_enabled) | F_MBUSEN);
पूर्ण

/*
 * Initialization that requires the OS and protocol layers to alपढ़ोy
 * be initialized goes here.
 */
पूर्णांक t3_mc5_init(काष्ठा mc5 *mc5, अचिन्हित पूर्णांक nservers, अचिन्हित पूर्णांक nfilters,
		अचिन्हित पूर्णांक nroutes)
अणु
	u32 cfg;
	पूर्णांक err;
	अचिन्हित पूर्णांक tcam_size = mc5->tcam_size;
	काष्ठा adapter *adap = mc5->adapter;

	अगर (!tcam_size)
		वापस 0;

	अगर (nroutes > MAX_ROUTES || nroutes + nservers + nfilters > tcam_size)
		वापस -EINVAL;

	/* Reset the TCAM */
	cfg = t3_पढ़ो_reg(adap, A_MC5_DB_CONFIG) & ~F_TMMODE;
	cfg |= V_TMMODE(mc5->mode == MC5_MODE_72_BIT) | F_TMRST;
	t3_ग_लिखो_reg(adap, A_MC5_DB_CONFIG, cfg);
	अगर (t3_रुको_op_करोne(adap, A_MC5_DB_CONFIG, F_TMRDY, 1, 500, 0)) अणु
		CH_ERR(adap, "TCAM reset timed out\n");
		वापस -1;
	पूर्ण

	t3_ग_लिखो_reg(adap, A_MC5_DB_ROUTING_TABLE_INDEX, tcam_size - nroutes);
	t3_ग_लिखो_reg(adap, A_MC5_DB_FILTER_TABLE,
		     tcam_size - nroutes - nfilters);
	t3_ग_लिखो_reg(adap, A_MC5_DB_SERVER_INDEX,
		     tcam_size - nroutes - nfilters - nservers);

	mc5->parity_enabled = 1;

	/* All the TCAM addresses we access have only the low 32 bits non 0 */
	t3_ग_लिखो_reg(adap, A_MC5_DB_DBGI_REQ_ADDR1, 0);
	t3_ग_लिखो_reg(adap, A_MC5_DB_DBGI_REQ_ADDR2, 0);

	mc5_dbgi_mode_enable(mc5);

	चयन (mc5->part_type) अणु
	हाल IDT75P52100:
		err = init_idt52100(mc5);
		अवरोध;
	हाल IDT75N43102:
		err = init_idt43102(mc5);
		अवरोध;
	शेष:
		CH_ERR(adap, "Unsupported TCAM type %d\n", mc5->part_type);
		err = -EINVAL;
		अवरोध;
	पूर्ण

	mc5_dbgi_mode_disable(mc5);
	वापस err;
पूर्ण


#घोषणा MC5_INT_FATAL (F_PARITYERR | F_REQQPARERR | F_DISPQPARERR)

/*
 * MC5 पूर्णांकerrupt handler
 */
व्योम t3_mc5_पूर्णांकr_handler(काष्ठा mc5 *mc5)
अणु
	काष्ठा adapter *adap = mc5->adapter;
	u32 cause = t3_पढ़ो_reg(adap, A_MC5_DB_INT_CAUSE);

	अगर ((cause & F_PARITYERR) && mc5->parity_enabled) अणु
		CH_ALERT(adap, "MC5 parity error\n");
		mc5->stats.parity_err++;
	पूर्ण

	अगर (cause & F_REQQPARERR) अणु
		CH_ALERT(adap, "MC5 request queue parity error\n");
		mc5->stats.reqq_parity_err++;
	पूर्ण

	अगर (cause & F_DISPQPARERR) अणु
		CH_ALERT(adap, "MC5 dispatch queue parity error\n");
		mc5->stats.dispq_parity_err++;
	पूर्ण

	अगर (cause & F_ACTRGNFULL)
		mc5->stats.active_rgn_full++;
	अगर (cause & F_NFASRCHFAIL)
		mc5->stats.nfa_srch_err++;
	अगर (cause & F_UNKNOWNCMD)
		mc5->stats.unknown_cmd++;
	अगर (cause & F_DELACTEMPTY)
		mc5->stats.del_act_empty++;
	अगर (cause & MC5_INT_FATAL)
		t3_fatal_err(adap);

	t3_ग_लिखो_reg(adap, A_MC5_DB_INT_CAUSE, cause);
पूर्ण

व्योम t3_mc5_prep(काष्ठा adapter *adapter, काष्ठा mc5 *mc5, पूर्णांक mode)
अणु
#घोषणा K * 1024

	अटल अचिन्हित पूर्णांक tcam_part_size[] = अणु	/* in K 72-bit entries */
		64 K, 128 K, 256 K, 32 K
	पूर्ण;

#अघोषित K

	u32 cfg = t3_पढ़ो_reg(adapter, A_MC5_DB_CONFIG);

	mc5->adapter = adapter;
	mc5->mode = (अचिन्हित अक्षर)mode;
	mc5->part_type = (अचिन्हित अक्षर)G_TMTYPE(cfg);
	अगर (cfg & F_TMTYPEHI)
		mc5->part_type |= 4;

	mc5->tcam_size = tcam_part_size[G_TMPARTSIZE(cfg)];
	अगर (mode == MC5_MODE_144_BIT)
		mc5->tcam_size /= 2;
पूर्ण
