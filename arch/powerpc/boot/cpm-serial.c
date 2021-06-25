<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CPM serial console support.
 *
 * Copyright 2007 Freescale Semiconductor, Inc.
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * It is assumed that the firmware (or the platक्रमm file) has alपढ़ोy set
 * up the port.
 */

#समावेश "types.h"
#समावेश "io.h"
#समावेश "ops.h"
#समावेश "page.h"

काष्ठा cpm_scc अणु
	u32 gsmrl;
	u32 gsmrh;
	u16 psmr;
	u8 res1[2];
	u16 todr;
	u16 dsr;
	u16 scce;
	u8 res2[2];
	u16 sccm;
	u8 res3;
	u8 sccs;
	u8 res4[8];
पूर्ण;

काष्ठा cpm_smc अणु
	u8 res1[2];
	u16 smcmr;
	u8 res2[2];
	u8 smce;
	u8 res3[3];
	u8 smcm;
	u8 res4[5];
पूर्ण;

काष्ठा cpm_param अणु
	u16 rbase;
	u16 tbase;
	u8 rfcr;
	u8 tfcr;
	u16 mrblr;
	u32 rstate;
	u8 res1[4];
	u16 rbptr;
	u8 res2[6];
	u32 tstate;
	u8 res3[4];
	u16 tbptr;
	u8 res4[6];
	u16 maxidl;
	u16 idlc;
	u16 brkln;
	u16 brkec;
	u16 brkcr;
	u16 rmask;
	u8 res5[4];
पूर्ण;

काष्ठा cpm_bd अणु
	u16 sc;   /* Status and Control */
	u16 len;  /* Data length in buffer */
	u8 *addr; /* Buffer address in host memory */
पूर्ण;

अटल व्योम *cpcr;
अटल काष्ठा cpm_param *param;
अटल काष्ठा cpm_smc *smc;
अटल काष्ठा cpm_scc *scc;
अटल काष्ठा cpm_bd *tbdf, *rbdf;
अटल u32 cpm_cmd;
अटल व्योम *cbd_addr;
अटल u32 cbd_offset;

अटल व्योम (*करो_cmd)(पूर्णांक op);
अटल व्योम (*enable_port)(व्योम);
अटल व्योम (*disable_port)(व्योम);

#घोषणा CPM_CMD_STOP_TX     4
#घोषणा CPM_CMD_RESTART_TX  6
#घोषणा CPM_CMD_INIT_RX_TX  0

अटल व्योम cpm1_cmd(पूर्णांक op)
अणु
	जबतक (in_be16(cpcr) & 1)
		;

	out_be16(cpcr, (op << 8) | cpm_cmd | 1);

	जबतक (in_be16(cpcr) & 1)
		;
पूर्ण

अटल व्योम cpm2_cmd(पूर्णांक op)
अणु
	जबतक (in_be32(cpcr) & 0x10000)
		;

	out_be32(cpcr, op | cpm_cmd | 0x10000);

	जबतक (in_be32(cpcr) & 0x10000)
		;
पूर्ण

अटल व्योम smc_disable_port(व्योम)
अणु
	करो_cmd(CPM_CMD_STOP_TX);
	out_be16(&smc->smcmr, in_be16(&smc->smcmr) & ~3);
पूर्ण

अटल व्योम scc_disable_port(व्योम)
अणु
	करो_cmd(CPM_CMD_STOP_TX);
	out_be32(&scc->gsmrl, in_be32(&scc->gsmrl) & ~0x30);
पूर्ण

अटल व्योम smc_enable_port(व्योम)
अणु
	out_be16(&smc->smcmr, in_be16(&smc->smcmr) | 3);
	करो_cmd(CPM_CMD_RESTART_TX);
पूर्ण

अटल व्योम scc_enable_port(व्योम)
अणु
	out_be32(&scc->gsmrl, in_be32(&scc->gsmrl) | 0x30);
	करो_cmd(CPM_CMD_RESTART_TX);
पूर्ण

अटल पूर्णांक cpm_serial_खोलो(व्योम)
अणु
	disable_port();

	out_8(&param->rfcr, 0x10);
	out_8(&param->tfcr, 0x10);
	out_be16(&param->mrblr, 1);
	out_be16(&param->maxidl, 0);
	out_be16(&param->brkec, 0);
	out_be16(&param->brkln, 0);
	out_be16(&param->brkcr, 0);

	rbdf = cbd_addr;
	rbdf->addr = (u8 *)rbdf - 1;
	rbdf->sc = 0xa000;
	rbdf->len = 1;

	tbdf = rbdf + 1;
	tbdf->addr = (u8 *)rbdf - 2;
	tbdf->sc = 0x2000;
	tbdf->len = 1;

	sync();
	out_be16(&param->rbase, cbd_offset);
	out_be16(&param->tbase, cbd_offset + माप(काष्ठा cpm_bd));

	करो_cmd(CPM_CMD_INIT_RX_TX);

	enable_port();
	वापस 0;
पूर्ण

अटल व्योम cpm_serial_अ_दो(अचिन्हित अक्षर c)
अणु
	जबतक (tbdf->sc & 0x8000)
		barrier();

	sync();

	tbdf->addr[0] = c;
	eieio();
	tbdf->sc |= 0x8000;
पूर्ण

अटल अचिन्हित अक्षर cpm_serial_tstc(व्योम)
अणु
	barrier();
	वापस !(rbdf->sc & 0x8000);
पूर्ण

अटल अचिन्हित अक्षर cpm_serial_अ_लो(व्योम)
अणु
	अचिन्हित अक्षर c;

	जबतक (!cpm_serial_tstc())
		;

	sync();
	c = rbdf->addr[0];
	eieio();
	rbdf->sc |= 0x8000;

	वापस c;
पूर्ण

पूर्णांक cpm_console_init(व्योम *devp, काष्ठा serial_console_data *scdp)
अणु
	व्योम *vreg[2];
	u32 reg[2];
	पूर्णांक is_smc = 0, is_cpm2 = 0;
	व्योम *parent, *muram;
	व्योम *muram_addr;
	अचिन्हित दीर्घ muram_offset, muram_size;

	अगर (dt_is_compatible(devp, "fsl,cpm1-smc-uart")) अणु
		is_smc = 1;
	पूर्ण अन्यथा अगर (dt_is_compatible(devp, "fsl,cpm2-scc-uart")) अणु
		is_cpm2 = 1;
	पूर्ण अन्यथा अगर (dt_is_compatible(devp, "fsl,cpm2-smc-uart")) अणु
		is_cpm2 = 1;
		is_smc = 1;
	पूर्ण

	अगर (is_smc) अणु
		enable_port = smc_enable_port;
		disable_port = smc_disable_port;
	पूर्ण अन्यथा अणु
		enable_port = scc_enable_port;
		disable_port = scc_disable_port;
	पूर्ण

	अगर (is_cpm2)
		करो_cmd = cpm2_cmd;
	अन्यथा
		करो_cmd = cpm1_cmd;

	अगर (getprop(devp, "fsl,cpm-command", &cpm_cmd, 4) < 4)
		वापस -1;

	अगर (dt_get_भव_reg(devp, vreg, 2) < 2)
		वापस -1;

	अगर (is_smc)
		smc = vreg[0];
	अन्यथा
		scc = vreg[0];

	param = vreg[1];

	parent = get_parent(devp);
	अगर (!parent)
		वापस -1;

	अगर (dt_get_भव_reg(parent, &cpcr, 1) < 1)
		वापस -1;

	muram = finddevice("/soc/cpm/muram/data");
	अगर (!muram)
		वापस -1;

	/* For bootwrapper-compatible device trees, we assume that the first
	 * entry has at least 128 bytes, and that #address-cells/#data-cells
	 * is one क्रम both parent and child.
	 */

	अगर (dt_get_भव_reg(muram, &muram_addr, 1) < 1)
		वापस -1;

	अगर (getprop(muram, "reg", reg, 8) < 8)
		वापस -1;

	muram_offset = reg[0];
	muram_size = reg[1];

	/* Store the buffer descriptors at the end of the first muram chunk.
	 * For SMC ports on CPM2-based platक्रमms, relocate the parameter RAM
	 * just beक्रमe the buffer descriptors.
	 */

	cbd_offset = muram_offset + muram_size - 2 * माप(काष्ठा cpm_bd);

	अगर (is_cpm2 && is_smc) अणु
		u16 *smc_base = (u16 *)param;
		u16 pram_offset;

		pram_offset = cbd_offset - 64;
		pram_offset = _ALIGN_DOWN(pram_offset, 64);

		disable_port();
		out_be16(smc_base, pram_offset);
		param = muram_addr - muram_offset + pram_offset;
	पूर्ण

	cbd_addr = muram_addr - muram_offset + cbd_offset;

	scdp->खोलो = cpm_serial_खोलो;
	scdp->अ_दो = cpm_serial_अ_दो;
	scdp->अ_लो = cpm_serial_अ_लो;
	scdp->tstc = cpm_serial_tstc;

	वापस 0;
पूर्ण
