<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aic94xx SAS/SATA driver sequencer पूर्णांकerface.
 *
 * Copyright (C) 2005 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 *
 * Parts of this code adapted from David Chaw's adp94xx_seq.c.
 */

#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश "aic94xx_reg.h"
#समावेश "aic94xx_hwi.h"

#समावेश "aic94xx_seq.h"
#समावेश "aic94xx_dump.h"

/* It takes no more than 0.05 us क्रम an inकाष्ठाion
 * to complete. So रुकोing क्रम 1 us should be more than
 * plenty.
 */
#घोषणा PAUSE_DELAY 1
#घोषणा PAUSE_TRIES 1000

अटल स्थिर काष्ठा firmware *sequencer_fw;
अटल u16 cseq_vecs[CSEQ_NUM_VECS], lseq_vecs[LSEQ_NUM_VECS], mode2_task,
	cseq_idle_loop, lseq_idle_loop;
अटल स्थिर u8 *cseq_code, *lseq_code;
अटल u32 cseq_code_size, lseq_code_size;

अटल u16 first_scb_site_no = 0xFFFF;
अटल u16 last_scb_site_no;

/* ---------- Pause/Unछोड़ो CSEQ/LSEQ ---------- */

/**
 * asd_छोड़ो_cseq - छोड़ो the central sequencer
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * Return 0 on success, negative on failure.
 */
अटल पूर्णांक asd_छोड़ो_cseq(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक	count = PAUSE_TRIES;
	u32	arp2ctl;

	arp2ctl = asd_पढ़ो_reg_dword(asd_ha, CARP2CTL);
	अगर (arp2ctl & PAUSED)
		वापस 0;

	asd_ग_लिखो_reg_dword(asd_ha, CARP2CTL, arp2ctl | EPAUSE);
	करो अणु
		arp2ctl = asd_पढ़ो_reg_dword(asd_ha, CARP2CTL);
		अगर (arp2ctl & PAUSED)
			वापस 0;
		udelay(PAUSE_DELAY);
	पूर्ण जबतक (--count > 0);

	ASD_DPRINTK("couldn't pause CSEQ\n");
	वापस -1;
पूर्ण

/**
 * asd_unछोड़ो_cseq - unछोड़ो the central sequencer.
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 * Return 0 on success, negative on error.
 */
अटल पूर्णांक asd_unछोड़ो_cseq(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u32	arp2ctl;
	पूर्णांक	count = PAUSE_TRIES;

	arp2ctl = asd_पढ़ो_reg_dword(asd_ha, CARP2CTL);
	अगर (!(arp2ctl & PAUSED))
		वापस 0;

	asd_ग_लिखो_reg_dword(asd_ha, CARP2CTL, arp2ctl & ~EPAUSE);
	करो अणु
		arp2ctl = asd_पढ़ो_reg_dword(asd_ha, CARP2CTL);
		अगर (!(arp2ctl & PAUSED))
			वापस 0;
		udelay(PAUSE_DELAY);
	पूर्ण जबतक (--count > 0);

	ASD_DPRINTK("couldn't unpause the CSEQ\n");
	वापस -1;
पूर्ण

/**
 * asd_seq_छोड़ो_lseq - छोड़ो a link sequencer
 * @asd_ha: poपूर्णांकer to a host adapter काष्ठाure
 * @lseq: link sequencer of पूर्णांकerest
 *
 * Return 0 on success, negative on error.
 */
अटल पूर्णांक asd_seq_छोड़ो_lseq(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक lseq)
अणु
	u32    arp2ctl;
	पूर्णांक    count = PAUSE_TRIES;

	arp2ctl = asd_पढ़ो_reg_dword(asd_ha, LmARP2CTL(lseq));
	अगर (arp2ctl & PAUSED)
		वापस 0;

	asd_ग_लिखो_reg_dword(asd_ha, LmARP2CTL(lseq), arp2ctl | EPAUSE);
	करो अणु
		arp2ctl = asd_पढ़ो_reg_dword(asd_ha, LmARP2CTL(lseq));
		अगर (arp2ctl & PAUSED)
			वापस 0;
		udelay(PAUSE_DELAY);
	पूर्ण जबतक (--count > 0);

	ASD_DPRINTK("couldn't pause LSEQ %d\n", lseq);
	वापस -1;
पूर्ण

/**
 * asd_छोड़ो_lseq - छोड़ो the link sequencer(s)
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @lseq_mask: mask of link sequencers of पूर्णांकerest
 *
 * Return 0 on success, negative on failure.
 */
अटल पूर्णांक asd_छोड़ो_lseq(काष्ठा asd_ha_काष्ठा *asd_ha, u8 lseq_mask)
अणु
	पूर्णांक lseq;
	पूर्णांक err = 0;

	क्रम_each_sequencer(lseq_mask, lseq_mask, lseq) अणु
		err = asd_seq_छोड़ो_lseq(asd_ha, lseq);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

/**
 * asd_seq_unछोड़ो_lseq - unछोड़ो a link sequencer
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @lseq: link sequencer of पूर्णांकerest
 *
 * Return 0 on success, negative on error.
 */
अटल पूर्णांक asd_seq_unछोड़ो_lseq(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक lseq)
अणु
	u32 arp2ctl;
	पूर्णांक count = PAUSE_TRIES;

	arp2ctl = asd_पढ़ो_reg_dword(asd_ha, LmARP2CTL(lseq));
	अगर (!(arp2ctl & PAUSED))
		वापस 0;

	asd_ग_लिखो_reg_dword(asd_ha, LmARP2CTL(lseq), arp2ctl & ~EPAUSE);
	करो अणु
		arp2ctl = asd_पढ़ो_reg_dword(asd_ha, LmARP2CTL(lseq));
		अगर (!(arp2ctl & PAUSED))
			वापस 0;
		udelay(PAUSE_DELAY);
	पूर्ण जबतक (--count > 0);

	ASD_DPRINTK("couldn't unpause LSEQ %d\n", lseq);
	वापस 0;
पूर्ण


/* ---------- Downloading CSEQ/LSEQ microcode ---------- */

अटल पूर्णांक asd_verअगरy_cseq(काष्ठा asd_ha_काष्ठा *asd_ha, स्थिर u8 *_prog,
			   u32 size)
अणु
	u32 addr = CSEQ_RAM_REG_BASE_ADR;
	स्थिर u32 *prog = (u32 *) _prog;
	u32 i;

	क्रम (i = 0; i < size; i += 4, prog++, addr += 4) अणु
		u32 val = asd_पढ़ो_reg_dword(asd_ha, addr);

		अगर (le32_to_cpu(*prog) != val) अणु
			asd_prपूर्णांकk("%s: cseq verify failed at %u "
				   "read:0x%x, wanted:0x%x\n",
				   pci_name(asd_ha->pcidev),
				   i, val, le32_to_cpu(*prog));
			वापस -1;
		पूर्ण
	पूर्ण
	ASD_DPRINTK("verified %d bytes, passed\n", size);
	वापस 0;
पूर्ण

/**
 * asd_verअगरy_lseq - verअगरy the microcode of a link sequencer
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @_prog: poपूर्णांकer to the microcode
 * @size: size of the microcode in bytes
 * @lseq: link sequencer of पूर्णांकerest
 *
 * The link sequencer code is accessed in 4 KB pages, which are selected
 * by setting LmRAMPAGE (bits 8 and 9) of the LmBISTCTL1 रेजिस्टर.
 * The 10 KB LSEQm inकाष्ठाion code is mapped, page at a समय, at
 * LmSEQRAM address.
 */
अटल पूर्णांक asd_verअगरy_lseq(काष्ठा asd_ha_काष्ठा *asd_ha, स्थिर u8 *_prog,
			   u32 size, पूर्णांक lseq)
अणु
#घोषणा LSEQ_CODEPAGE_SIZE 4096
	पूर्णांक pages =  (size + LSEQ_CODEPAGE_SIZE - 1) / LSEQ_CODEPAGE_SIZE;
	u32 page;
	स्थिर u32 *prog = (u32 *) _prog;

	क्रम (page = 0; page < pages; page++) अणु
		u32 i;

		asd_ग_लिखो_reg_dword(asd_ha, LmBISTCTL1(lseq),
				    page << LmRAMPAGE_LSHIFT);
		क्रम (i = 0; size > 0 && i < LSEQ_CODEPAGE_SIZE;
		     i += 4, prog++, size-=4) अणु

			u32 val = asd_पढ़ो_reg_dword(asd_ha, LmSEQRAM(lseq)+i);

			अगर (le32_to_cpu(*prog) != val) अणु
				asd_prपूर्णांकk("%s: LSEQ%d verify failed "
					   "page:%d, offs:%d\n",
					   pci_name(asd_ha->pcidev),
					   lseq, page, i);
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण
	ASD_DPRINTK("LSEQ%d verified %d bytes, passed\n", lseq,
		    (पूर्णांक)((u8 *)prog-_prog));
	वापस 0;
पूर्ण

/**
 * asd_verअगरy_seq -- verअगरy CSEQ/LSEQ microcode
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @prog: poपूर्णांकer to microcode
 * @size: size of the microcode
 * @lseq_mask: अगर 0, verअगरy CSEQ microcode, अन्यथा mask of LSEQs of पूर्णांकerest
 *
 * Return 0 अगर microcode is correct, negative on mismatch.
 */
अटल पूर्णांक asd_verअगरy_seq(काष्ठा asd_ha_काष्ठा *asd_ha, स्थिर u8 *prog,
			      u32 size, u8 lseq_mask)
अणु
	अगर (lseq_mask == 0)
		वापस asd_verअगरy_cseq(asd_ha, prog, size);
	अन्यथा अणु
		पूर्णांक lseq, err;

		क्रम_each_sequencer(lseq_mask, lseq_mask, lseq) अणु
			err = asd_verअगरy_lseq(asd_ha, prog, size, lseq);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#घोषणा ASD_DMA_MODE_DOWNLOAD
#अगर_घोषित ASD_DMA_MODE_DOWNLOAD
/* This is the size of the CSEQ Mapped inकाष्ठाion page */
#घोषणा MAX_DMA_OVLY_COUNT ((1U << 14)-1)
अटल पूर्णांक asd_करोwnload_seq(काष्ठा asd_ha_काष्ठा *asd_ha,
			    स्थिर u8 * स्थिर prog, u32 size, u8 lseq_mask)
अणु
	u32 comstaten;
	u32 reg;
	पूर्णांक page;
	स्थिर पूर्णांक pages = (size + MAX_DMA_OVLY_COUNT - 1) / MAX_DMA_OVLY_COUNT;
	काष्ठा asd_dma_tok *token;
	पूर्णांक err = 0;

	अगर (size % 4) अणु
		asd_prपूर्णांकk("sequencer program not multiple of 4\n");
		वापस -1;
	पूर्ण

	asd_छोड़ो_cseq(asd_ha);
	asd_छोड़ो_lseq(asd_ha, 0xFF);

	/* save, disable and clear पूर्णांकerrupts */
	comstaten = asd_पढ़ो_reg_dword(asd_ha, COMSTATEN);
	asd_ग_लिखो_reg_dword(asd_ha, COMSTATEN, 0);
	asd_ग_लिखो_reg_dword(asd_ha, COMSTAT, COMSTAT_MASK);

	asd_ग_लिखो_reg_dword(asd_ha, CHIMINTEN, RST_CHIMINTEN);
	asd_ग_लिखो_reg_dword(asd_ha, CHIMINT, CHIMINT_MASK);

	token = asd_alloc_coherent(asd_ha, MAX_DMA_OVLY_COUNT, GFP_KERNEL);
	अगर (!token) अणु
		asd_prपूर्णांकk("out of memory for dma SEQ download\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	ASD_DPRINTK("dma-ing %d bytes\n", size);

	क्रम (page = 0; page < pages; page++) अणु
		पूर्णांक i;
		u32 left = min(size-page*MAX_DMA_OVLY_COUNT,
			       (u32)MAX_DMA_OVLY_COUNT);

		स_नकल(token->vaddr, prog + page*MAX_DMA_OVLY_COUNT, left);
		asd_ग_लिखो_reg_addr(asd_ha, OVLYDMAADR, token->dma_handle);
		asd_ग_लिखो_reg_dword(asd_ha, OVLYDMACNT, left);
		reg = !page ? RESETOVLYDMA : 0;
		reg |= (STARTOVLYDMA | OVLYHALTERR);
		reg |= (lseq_mask ? (((u32)lseq_mask) << 8) : OVLYCSEQ);
		/* Start DMA. */
		asd_ग_लिखो_reg_dword(asd_ha, OVLYDMACTL, reg);

		क्रम (i = PAUSE_TRIES*100; i > 0; i--) अणु
			u32 dmaकरोne = asd_पढ़ो_reg_dword(asd_ha, OVLYDMACTL);
			अगर (!(dmaकरोne & OVLYDMAACT))
				अवरोध;
			udelay(PAUSE_DELAY);
		पूर्ण
	पूर्ण

	reg = asd_पढ़ो_reg_dword(asd_ha, COMSTAT);
	अगर (!(reg & OVLYDMADONE) || (reg & OVLYERR)
	    || (asd_पढ़ो_reg_dword(asd_ha, CHIMINT) & DEVEXCEPT_MASK))अणु
		asd_prपूर्णांकk("%s: error DMA-ing sequencer code\n",
			   pci_name(asd_ha->pcidev));
		err = -ENODEV;
	पूर्ण

	asd_मुक्त_coherent(asd_ha, token);
 out:
	asd_ग_लिखो_reg_dword(asd_ha, COMSTATEN, comstaten);

	वापस err ? : asd_verअगरy_seq(asd_ha, prog, size, lseq_mask);
पूर्ण
#अन्यथा /* ASD_DMA_MODE_DOWNLOAD */
अटल पूर्णांक asd_करोwnload_seq(काष्ठा asd_ha_काष्ठा *asd_ha, स्थिर u8 *_prog,
			    u32 size, u8 lseq_mask)
अणु
	पूर्णांक i;
	u32 reg = 0;
	स्थिर u32 *prog = (u32 *) _prog;

	अगर (size % 4) अणु
		asd_prपूर्णांकk("sequencer program not multiple of 4\n");
		वापस -1;
	पूर्ण

	asd_छोड़ो_cseq(asd_ha);
	asd_छोड़ो_lseq(asd_ha, 0xFF);

	reg |= (lseq_mask ? (((u32)lseq_mask) << 8) : OVLYCSEQ);
	reg |= PIOCMODE;

	asd_ग_लिखो_reg_dword(asd_ha, OVLYDMACNT, size);
	asd_ग_लिखो_reg_dword(asd_ha, OVLYDMACTL, reg);

	ASD_DPRINTK("downloading %s sequencer%s in PIO mode...\n",
		    lseq_mask ? "LSEQ" : "CSEQ", lseq_mask ? "s" : "");

	क्रम (i = 0; i < size; i += 4, prog++)
		asd_ग_लिखो_reg_dword(asd_ha, SPIODATA, *prog);

	reg = (reg & ~PIOCMODE) | OVLYHALTERR;
	asd_ग_लिखो_reg_dword(asd_ha, OVLYDMACTL, reg);

	वापस asd_verअगरy_seq(asd_ha, _prog, size, lseq_mask);
पूर्ण
#पूर्ण_अगर /* ASD_DMA_MODE_DOWNLOAD */

/**
 * asd_seq_करोwnload_seqs - करोwnload the sequencer microcode
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * Download the central and link sequencer microcode.
 */
अटल पूर्णांक asd_seq_करोwnload_seqs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक 	err;

	अगर (!asd_ha->hw_prof.enabled_phys) अणु
		asd_prपूर्णांकk("%s: no enabled phys!\n", pci_name(asd_ha->pcidev));
		वापस -ENODEV;
	पूर्ण

	/* Download the CSEQ */
	ASD_DPRINTK("downloading CSEQ...\n");
	err = asd_करोwnload_seq(asd_ha, cseq_code, cseq_code_size, 0);
	अगर (err) अणु
		asd_prपूर्णांकk("CSEQ download failed:%d\n", err);
		वापस err;
	पूर्ण

	/* Download the Link Sequencers code. All of the Link Sequencers
	 * microcode can be करोwnloaded at the same समय.
	 */
	ASD_DPRINTK("downloading LSEQs...\n");
	err = asd_करोwnload_seq(asd_ha, lseq_code, lseq_code_size,
			       asd_ha->hw_prof.enabled_phys);
	अगर (err) अणु
		/* Try it one at a समय */
		u8 lseq;
		u8 lseq_mask = asd_ha->hw_prof.enabled_phys;

		क्रम_each_sequencer(lseq_mask, lseq_mask, lseq) अणु
			err = asd_करोwnload_seq(asd_ha, lseq_code,
					       lseq_code_size, 1<<lseq);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (err)
		asd_prपूर्णांकk("LSEQs download failed:%d\n", err);

	वापस err;
पूर्ण

/* ---------- Initializing the chip, chip memory, etc. ---------- */

/**
 * asd_init_cseq_mip - initialize CSEQ mode independent pages 4-7
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल व्योम asd_init_cseq_mip(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	/* CSEQ Mode Independent, page 4 setup. */
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_EXE_HEAD, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_EXE_TAIL, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_DONE_HEAD, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_DONE_TAIL, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_SEND_HEAD, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_SEND_TAIL, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_DMA2CHIM_HEAD, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_DMA2CHIM_TAIL, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_COPY_HEAD, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_COPY_TAIL, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_REG0, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_REG1, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_REG2, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_LINK_CTL_Q_MAP, 0);
	अणु
		u8 con = asd_पढ़ो_reg_byte(asd_ha, CCONEXIST);
		u8 val = hweight8(con);
		asd_ग_लिखो_reg_byte(asd_ha, CSEQ_MAX_CSEQ_MODE, (val<<4)|val);
	पूर्ण
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_FREE_LIST_HACK_COUNT, 0);

	/* CSEQ Mode independent, page 5 setup. */
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_EST_NEXUS_REQ_QUEUE, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_EST_NEXUS_REQ_QUEUE+4, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_EST_NEXUS_REQ_COUNT, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_EST_NEXUS_REQ_COUNT+4, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_EST_NEXUS_HEAD, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_EST_NEXUS_TAIL, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_NEED_EST_NEXUS_SCB, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_EST_NEXUS_REQ_HEAD, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_EST_NEXUS_REQ_TAIL, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_EST_NEXUS_SCB_OFFSET, 0);

	/* CSEQ Mode independent, page 6 setup. */
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_INT_ROUT_RET_ADDR0, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_INT_ROUT_RET_ADDR1, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_INT_ROUT_SCBPTR, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_INT_ROUT_MODE, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_ISR_SCRATCH_FLAGS, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_ISR_SAVE_SINDEX, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_ISR_SAVE_DINDEX, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_MONIRTT_HEAD, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_MONIRTT_TAIL, 0xFFFF);
	/* Calculate the मुक्त scb mask. */
	अणु
		u16 cmdctx = asd_get_cmdctx_size(asd_ha);
		cmdctx = (~((cmdctx/128)-1)) >> 8;
		asd_ग_लिखो_reg_byte(asd_ha, CSEQ_FREE_SCB_MASK, (u8)cmdctx);
	पूर्ण
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_BUILTIN_FREE_SCB_HEAD,
			   first_scb_site_no);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_BUILTIN_FREE_SCB_TAIL,
			   last_scb_site_no);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_EXTENDED_FREE_SCB_HEAD, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_EXTENDED_FREE_SCB_TAIL, 0xFFFF);

	/* CSEQ Mode independent, page 7 setup. */
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_EMPTY_REQ_QUEUE, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_EMPTY_REQ_QUEUE+4, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_EMPTY_REQ_COUNT, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_EMPTY_REQ_COUNT+4, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_EMPTY_HEAD, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_Q_EMPTY_TAIL, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_NEED_EMPTY_SCB, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_EMPTY_REQ_HEAD, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_EMPTY_REQ_TAIL, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_EMPTY_SCB_OFFSET, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_PRIMITIVE_DATA, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_TIMEOUT_CONST, 0);
पूर्ण

/**
 * asd_init_cseq_mdp - initialize CSEQ Mode dependent pages
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल व्योम asd_init_cseq_mdp(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक	i;
	पूर्णांक	moffs;

	moffs = CSEQ_PAGE_SIZE * 2;

	/* CSEQ Mode dependent, modes 0-7, page 0 setup. */
	क्रम (i = 0; i < 8; i++) अणु
		asd_ग_लिखो_reg_word(asd_ha, i*moffs+CSEQ_LRM_SAVE_SINDEX, 0);
		asd_ग_लिखो_reg_word(asd_ha, i*moffs+CSEQ_LRM_SAVE_SCBPTR, 0);
		asd_ग_लिखो_reg_word(asd_ha, i*moffs+CSEQ_Q_LINK_HEAD, 0xFFFF);
		asd_ग_लिखो_reg_word(asd_ha, i*moffs+CSEQ_Q_LINK_TAIL, 0xFFFF);
		asd_ग_लिखो_reg_byte(asd_ha, i*moffs+CSEQ_LRM_SAVE_SCRPAGE, 0);
	पूर्ण

	/* CSEQ Mode dependent, mode 0-7, page 1 and 2 shall be ignored. */

	/* CSEQ Mode dependent, mode 8, page 0 setup. */
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_RET_ADDR, 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_RET_SCBPTR, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_SAVE_SCBPTR, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_EMPTY_TRANS_CTX, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_RESP_LEN, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_TMF_SCBPTR, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_GLOBAL_PREV_SCB, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_GLOBAL_HEAD, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_CLEAR_LU_HEAD, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_TMF_OPCODE, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_SCRATCH_FLAGS, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_HSB_SITE, 0);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_FIRST_INV_SCB_SITE,
			   (u16)last_scb_site_no+1);
	asd_ग_लिखो_reg_word(asd_ha, CSEQ_FIRST_INV_DDB_SITE,
			   (u16)asd_ha->hw_prof.max_ddbs);

	/* CSEQ Mode dependent, mode 8, page 1 setup. */
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_LUN_TO_CLEAR, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_LUN_TO_CLEAR + 4, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_LUN_TO_CHECK, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_LUN_TO_CHECK + 4, 0);

	/* CSEQ Mode dependent, mode 8, page 2 setup. */
	/* Tell the sequencer the bus address of the first SCB. */
	asd_ग_लिखो_reg_addr(asd_ha, CSEQ_HQ_NEW_POINTER,
			   asd_ha->seq.next_scb.dma_handle);
	ASD_DPRINTK("First SCB dma_handle: 0x%llx\n",
		    (अचिन्हित दीर्घ दीर्घ)asd_ha->seq.next_scb.dma_handle);

	/* Tell the sequencer the first Done List entry address. */
	asd_ग_लिखो_reg_addr(asd_ha, CSEQ_HQ_DONE_BASE,
			   asd_ha->seq.actual_dl->dma_handle);

	/* Initialize the Q_DONE_POINTER with the least signअगरicant
	 * 4 bytes of the first Done List address. */
	asd_ग_लिखो_reg_dword(asd_ha, CSEQ_HQ_DONE_POINTER,
			    ASD_BUSADDR_LO(asd_ha->seq.actual_dl->dma_handle));

	asd_ग_लिखो_reg_byte(asd_ha, CSEQ_HQ_DONE_PASS, ASD_DEF_DL_TOGGLE);

	/* CSEQ Mode dependent, mode 8, page 3 shall be ignored. */
पूर्ण

/**
 * asd_init_cseq_scratch -- setup and init CSEQ
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * Setup and initialize Central sequencers. Initialize the mode
 * independent and dependent scratch page to the शेष settings.
 */
अटल व्योम asd_init_cseq_scratch(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	asd_init_cseq_mip(asd_ha);
	asd_init_cseq_mdp(asd_ha);
पूर्ण

/**
 * asd_init_lseq_mip -- initialize LSEQ Mode independent pages 0-3
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @lseq:  link sequencer
 */
अटल व्योम asd_init_lseq_mip(काष्ठा asd_ha_काष्ठा *asd_ha, u8 lseq)
अणु
	पूर्णांक i;

	/* LSEQ Mode independent page 0 setup. */
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_Q_TGTXFR_HEAD(lseq), 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_Q_TGTXFR_TAIL(lseq), 0xFFFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_LINK_NUMBER(lseq), lseq);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_SCRATCH_FLAGS(lseq),
			   ASD_NOTIFY_ENABLE_SPINUP);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_CONNECTION_STATE(lseq),0x08000000);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_CONCTL(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_CONSTAT(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_CONNECTION_MODES(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_REG1_ISR(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_REG2_ISR(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_REG3_ISR(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_REG0_ISR(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_REG0_ISR(lseq)+4, 0);

	/* LSEQ Mode independent page 1 setup. */
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_EST_NEXUS_SCBPTR0(lseq), 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_EST_NEXUS_SCBPTR1(lseq), 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_EST_NEXUS_SCBPTR2(lseq), 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_EST_NEXUS_SCBPTR3(lseq), 0xFFFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EST_NEXUS_SCB_OPCODE0(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EST_NEXUS_SCB_OPCODE1(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EST_NEXUS_SCB_OPCODE2(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EST_NEXUS_SCB_OPCODE3(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EST_NEXUS_SCB_HEAD(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EST_NEXUS_SCB_TAIL(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EST_NEXUS_BUF_AVAIL(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_TIMEOUT_CONST(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_ISR_SAVE_SINDEX(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_ISR_SAVE_DINDEX(lseq), 0);

	/* LSEQ Mode Independent page 2 setup. */
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_EMPTY_SCB_PTR0(lseq), 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_EMPTY_SCB_PTR1(lseq), 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_EMPTY_SCB_PTR2(lseq), 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_EMPTY_SCB_PTR3(lseq), 0xFFFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EMPTY_SCB_OPCD0(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EMPTY_SCB_OPCD1(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EMPTY_SCB_OPCD2(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EMPTY_SCB_OPCD3(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EMPTY_SCB_HEAD(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EMPTY_SCB_TAIL(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_EMPTY_BUFS_AVAIL(lseq), 0);
	क्रम (i = 0; i < 12; i += 4)
		asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_ATA_SCR_REGS(lseq) + i, 0);

	/* LSEQ Mode Independent page 3 setup. */

	/* Device present समयr समयout */
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_DEV_PRES_TMR_TOUT_CONST(lseq),
			    ASD_DEV_PRESENT_TIMEOUT);

	/* SATA पूर्णांकerlock समयr disabled */
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_SATA_INTERLOCK_TIMEOUT(lseq),
			    ASD_SATA_INTERLOCK_TIMEOUT);

	/* STP shutकरोwn समयr समयout स्थिरant, IGNORED by the sequencer,
	 * always 0. */
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_STP_SHUTDOWN_TIMEOUT(lseq),
			    ASD_STP_SHUTDOWN_TIMEOUT);

	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_SRST_ASSERT_TIMEOUT(lseq),
			    ASD_SRST_ASSERT_TIMEOUT);

	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_RCV_FIS_TIMEOUT(lseq),
			    ASD_RCV_FIS_TIMEOUT);

	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_ONE_MILLISEC_TIMEOUT(lseq),
			    ASD_ONE_MILLISEC_TIMEOUT);

	/* COM_INIT समयr */
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_TEN_MS_COMINIT_TIMEOUT(lseq),
			    ASD_TEN_MILLISEC_TIMEOUT);

	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_SMP_RCV_TIMEOUT(lseq),
			    ASD_SMP_RCV_TIMEOUT);
पूर्ण

/**
 * asd_init_lseq_mdp -- initialize LSEQ mode dependent pages.
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @lseq:  link sequencer
 */
अटल व्योम asd_init_lseq_mdp(काष्ठा asd_ha_काष्ठा *asd_ha,  पूर्णांक lseq)
अणु
	पूर्णांक    i;
	u32    moffs;
	u16 ret_addr[] = अणु
		0xFFFF,		  /* mode 0 */
		0xFFFF,		  /* mode 1 */
		mode2_task,	  /* mode 2 */
		0,
		0xFFFF,		  /* mode 4/5 */
		0xFFFF,		  /* mode 4/5 */
	पूर्ण;

	/*
	 * Mode 0,1,2 and 4/5 have common field on page 0 क्रम the first
	 * 14 bytes.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		moffs = i * LSEQ_MODE_SCRATCH_SIZE;
		asd_ग_लिखो_reg_word(asd_ha, LmSEQ_RET_ADDR(lseq)+moffs,
				   ret_addr[i]);
		asd_ग_लिखो_reg_word(asd_ha, LmSEQ_REG0_MODE(lseq)+moffs, 0);
		asd_ग_लिखो_reg_word(asd_ha, LmSEQ_MODE_FLAGS(lseq)+moffs, 0);
		asd_ग_लिखो_reg_word(asd_ha, LmSEQ_RET_ADDR2(lseq)+moffs,0xFFFF);
		asd_ग_लिखो_reg_word(asd_ha, LmSEQ_RET_ADDR1(lseq)+moffs,0xFFFF);
		asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_OPCODE_TO_CSEQ(lseq)+moffs,0);
		asd_ग_लिखो_reg_word(asd_ha, LmSEQ_DATA_TO_CSEQ(lseq)+moffs,0);
	पूर्ण
	/*
	 *  Mode 5 page 0 overlaps the same scratch page with Mode 0 page 3.
	 */
	asd_ग_लिखो_reg_word(asd_ha,
			 LmSEQ_RET_ADDR(lseq)+LSEQ_MODE5_PAGE0_OFFSET,
			   ret_addr[5]);
	asd_ग_लिखो_reg_word(asd_ha,
			 LmSEQ_REG0_MODE(lseq)+LSEQ_MODE5_PAGE0_OFFSET,0);
	asd_ग_लिखो_reg_word(asd_ha,
			 LmSEQ_MODE_FLAGS(lseq)+LSEQ_MODE5_PAGE0_OFFSET, 0);
	asd_ग_लिखो_reg_word(asd_ha,
			 LmSEQ_RET_ADDR2(lseq)+LSEQ_MODE5_PAGE0_OFFSET,0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha,
			 LmSEQ_RET_ADDR1(lseq)+LSEQ_MODE5_PAGE0_OFFSET,0xFFFF);
	asd_ग_लिखो_reg_byte(asd_ha,
		         LmSEQ_OPCODE_TO_CSEQ(lseq)+LSEQ_MODE5_PAGE0_OFFSET,0);
	asd_ग_लिखो_reg_word(asd_ha,
		         LmSEQ_DATA_TO_CSEQ(lseq)+LSEQ_MODE5_PAGE0_OFFSET, 0);

	/* LSEQ Mode dependent 0, page 0 setup. */
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_FIRST_INV_DDB_SITE(lseq),
			   (u16)asd_ha->hw_prof.max_ddbs);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_EMPTY_TRANS_CTX(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_RESP_LEN(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_FIRST_INV_SCB_SITE(lseq),
			   (u16)last_scb_site_no+1);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_INTEN_SAVE(lseq),
			    (u16) ((LmM0INTEN_MASK & 0xFFFF0000) >> 16));
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_INTEN_SAVE(lseq) + 2,
			    (u16) LmM0INTEN_MASK & 0xFFFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_LINK_RST_FRM_LEN(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_LINK_RST_PROTOCOL(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_RESP_STATUS(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_LAST_LOADED_SGE(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_SAVE_SCBPTR(lseq), 0);

	/* LSEQ mode dependent, mode 1, page 0 setup. */
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_Q_XMIT_HEAD(lseq), 0xFFFF);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_M1_EMPTY_TRANS_CTX(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_INI_CONN_TAG(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_FAILED_OPEN_STATUS(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_XMIT_REQUEST_TYPE(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_M1_RESP_STATUS(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_M1_LAST_LOADED_SGE(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_M1_SAVE_SCBPTR(lseq), 0);

	/* LSEQ Mode dependent mode 2, page 0 setup */
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_PORT_COUNTER(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_PM_TABLE_PTR(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_SATA_INTERLOCK_TMR_SAVE(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_IP_BITL(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_COPY_SMP_CONN_TAG(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_P0M2_OFFS1AH(lseq), 0);

	/* LSEQ Mode dependent, mode 4/5, page 0 setup. */
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_SAVED_OOB_STATUS(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_SAVED_OOB_MODE(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_Q_LINK_HEAD(lseq), 0xFFFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_LINK_RST_ERR(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_SAVED_OOB_SIGNALS(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_SAS_RESET_MODE(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_LINK_RESET_RETRY_COUNT(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_NUM_LINK_RESET_RETRIES(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_OOB_INT_ENABLES(lseq), 0);
	/*
	 * Set the desired पूर्णांकerval between transmissions of the NOTIFY
	 * (ENABLE SPINUP) primitive.  Must be initialized to val - 1.
	 */
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_NOTIFY_TIMER_TIMEOUT(lseq),
			   ASD_NOTIFY_TIMEOUT - 1);
	/* No delay क्रम the first NOTIFY to be sent to the attached target. */
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_NOTIFY_TIMER_DOWN_COUNT(lseq),
			   ASD_NOTIFY_DOWN_COUNT);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_NOTIFY_TIMER_INITIAL_COUNT(lseq),
			   ASD_NOTIFY_DOWN_COUNT);

	/* LSEQ Mode dependent, mode 0 and 1, page 1 setup. */
	क्रम (i = 0; i < 2; i++)	अणु
		पूर्णांक j;
		/* Start from Page 1 of Mode 0 and 1. */
		moffs = LSEQ_PAGE_SIZE + i*LSEQ_MODE_SCRATCH_SIZE;
		/* All the fields of page 1 can be initialized to 0. */
		क्रम (j = 0; j < LSEQ_PAGE_SIZE; j += 4)
			asd_ग_लिखो_reg_dword(asd_ha, LmSCRATCH(lseq)+moffs+j,0);
	पूर्ण

	/* LSEQ Mode dependent, mode 2, page 1 setup. */
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_INVALID_DWORD_COUNT(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_DISPARITY_ERROR_COUNT(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_LOSS_OF_SYNC_COUNT(lseq), 0);

	/* LSEQ Mode dependent, mode 4/5, page 1. */
	क्रम (i = 0; i < LSEQ_PAGE_SIZE; i+=4)
		asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_FRAME_TYPE_MASK(lseq)+i, 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_FRAME_TYPE_MASK(lseq), 0xFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_HASHED_DEST_ADDR_MASK(lseq), 0xFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_HASHED_DEST_ADDR_MASK(lseq)+1,0xFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_HASHED_DEST_ADDR_MASK(lseq)+2,0xFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_HASHED_SRC_ADDR_MASK(lseq), 0xFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_HASHED_SRC_ADDR_MASK(lseq)+1, 0xFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_HASHED_SRC_ADDR_MASK(lseq)+2, 0xFF);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_DATA_OFFSET(lseq), 0xFFFFFFFF);

	/* LSEQ Mode dependent, mode 0, page 2 setup. */
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_SMP_RCV_TIMER_TERM_TS(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_DEVICE_BITS(lseq), 0);
	asd_ग_लिखो_reg_word(asd_ha, LmSEQ_SDB_DDB(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_SDB_NUM_TAGS(lseq), 0);
	asd_ग_लिखो_reg_byte(asd_ha, LmSEQ_SDB_CURR_TAG(lseq), 0);

	/* LSEQ Mode Dependent 1, page 2 setup. */
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_TX_ID_ADDR_FRAME(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_TX_ID_ADDR_FRAME(lseq)+4, 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_OPEN_TIMER_TERM_TS(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_SRST_AS_TIMER_TERM_TS(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_LAST_LOADED_SG_EL(lseq), 0);

	/* LSEQ Mode Dependent 2, page 2 setup. */
	/* The LmSEQ_STP_SHUTDOWN_TIMER_TERM_TS is IGNORED by the sequencer,
	 * i.e. always 0. */
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_STP_SHUTDOWN_TIMER_TERM_TS(lseq),0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_CLOSE_TIMER_TERM_TS(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_BREAK_TIMER_TERM_TS(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_DWS_RESET_TIMER_TERM_TS(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha,LmSEQ_SATA_INTERLOCK_TIMER_TERM_TS(lseq),0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_MCTL_TIMER_TERM_TS(lseq), 0);

	/* LSEQ Mode Dependent 4/5, page 2 setup. */
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_COMINIT_TIMER_TERM_TS(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_RCV_ID_TIMER_TERM_TS(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_RCV_FIS_TIMER_TERM_TS(lseq), 0);
	asd_ग_लिखो_reg_dword(asd_ha, LmSEQ_DEV_PRES_TIMER_TERM_TS(lseq),	0);
पूर्ण

/**
 * asd_init_lseq_scratch -- setup and init link sequencers
 * @asd_ha: poपूर्णांकer to host adapter काष्ठा
 */
अटल व्योम asd_init_lseq_scratch(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u8 lseq;
	u8 lseq_mask;

	lseq_mask = asd_ha->hw_prof.enabled_phys;
	क्रम_each_sequencer(lseq_mask, lseq_mask, lseq) अणु
		asd_init_lseq_mip(asd_ha, lseq);
		asd_init_lseq_mdp(asd_ha, lseq);
	पूर्ण
पूर्ण

/**
 * asd_init_scb_sites -- initialize sequencer SCB sites (memory).
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * This should be करोne beक्रमe initializing common CSEQ and LSEQ
 * scratch since those areas depend on some computed values here,
 * last_scb_site_no, etc.
 */
अटल व्योम asd_init_scb_sites(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	u16	site_no;
	u16     max_scbs = 0;

	क्रम (site_no = asd_ha->hw_prof.max_scbs-1;
	     site_no != (u16) -1;
	     site_no--) अणु
		u16	i;

		/* Initialize all fields in the SCB site to 0. */
		क्रम (i = 0; i < ASD_SCB_SIZE; i += 4)
			asd_scbsite_ग_लिखो_dword(asd_ha, site_no, i, 0);

		/* Initialize SCB Site Opcode field to invalid. */
		asd_scbsite_ग_लिखो_byte(asd_ha, site_no,
				       दुरत्व(काष्ठा scb_header, opcode),
				       0xFF);

		/* Initialize SCB Site Flags field to mean a response
		 * frame has been received.  This means inadvertent
		 * frames received to be dropped. */
		asd_scbsite_ग_लिखो_byte(asd_ha, site_no, 0x49, 0x01);

		/* Workaround needed by SEQ to fix a SATA issue is to exclude
		 * certain SCB sites from the मुक्त list. */
		अगर (!SCB_SITE_VALID(site_no))
			जारी;

		अगर (last_scb_site_no == 0)
			last_scb_site_no = site_no;

		/* For every SCB site, we need to initialize the
		 * following fields: Q_NEXT, SCB_OPCODE, SCB_FLAGS,
		 * and SG Element Flag. */

		/* Q_NEXT field of the last SCB is invalidated. */
		asd_scbsite_ग_लिखो_word(asd_ha, site_no, 0, first_scb_site_no);

		first_scb_site_no = site_no;
		max_scbs++;
	पूर्ण
	asd_ha->hw_prof.max_scbs = max_scbs;
	ASD_DPRINTK("max_scbs:%d\n", asd_ha->hw_prof.max_scbs);
	ASD_DPRINTK("first_scb_site_no:0x%x\n", first_scb_site_no);
	ASD_DPRINTK("last_scb_site_no:0x%x\n", last_scb_site_no);
पूर्ण

/**
 * asd_init_cseq_cio - initialize CSEQ CIO रेजिस्टरs
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल व्योम asd_init_cseq_cio(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक i;

	asd_ग_लिखो_reg_byte(asd_ha, CSEQCOMINTEN, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQDLCTL, ASD_DL_SIZE_BITS);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQDLOFFS, 0);
	asd_ग_लिखो_reg_byte(asd_ha, CSEQDLOFFS+1, 0);
	asd_ha->seq.scbpro = 0;
	asd_ग_लिखो_reg_dword(asd_ha, SCBPRO, 0);
	asd_ग_लिखो_reg_dword(asd_ha, CSEQCON, 0);

	/* Initialize CSEQ Mode 11 Interrupt Vectors.
	 * The addresses are 16 bit wide and in dword units.
	 * The values of their macros are in byte units.
	 * Thus we have to भागide by 4. */
	asd_ग_लिखो_reg_word(asd_ha, CM11INTVEC0, cseq_vecs[0]);
	asd_ग_लिखो_reg_word(asd_ha, CM11INTVEC1, cseq_vecs[1]);
	asd_ग_लिखो_reg_word(asd_ha, CM11INTVEC2, cseq_vecs[2]);

	/* Enable ARP2HALTC (ARP2 Halted from Halt Code Write). */
	asd_ग_लिखो_reg_byte(asd_ha, CARP2INTEN, EN_ARP2HALTC);

	/* Initialize CSEQ Scratch Page to 0x04. */
	asd_ग_लिखो_reg_byte(asd_ha, CSCRATCHPAGE, 0x04);

	/* Initialize CSEQ Mode[0-8] Dependent रेजिस्टरs. */
	/* Initialize Scratch Page to 0. */
	क्रम (i = 0; i < 9; i++)
		asd_ग_लिखो_reg_byte(asd_ha, CMnSCRATCHPAGE(i), 0);

	/* Reset the ARP2 Program Count. */
	asd_ग_लिखो_reg_word(asd_ha, CPRGMCNT, cseq_idle_loop);

	क्रम (i = 0; i < 8; i++) अणु
		/* Initialize Mode n Link m Interrupt Enable. */
		asd_ग_लिखो_reg_dword(asd_ha, CMnINTEN(i), EN_CMnRSPMBXF);
		/* Initialize Mode n Request Mailbox. */
		asd_ग_लिखो_reg_dword(asd_ha, CMnREQMBX(i), 0);
	पूर्ण
पूर्ण

/**
 * asd_init_lseq_cio -- initialize LmSEQ CIO रेजिस्टरs
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @lseq:  link sequencer
 */
अटल व्योम asd_init_lseq_cio(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक lseq)
अणु
	u8  *sas_addr;
	पूर्णांक  i;

	/* Enable ARP2HALTC (ARP2 Halted from Halt Code Write). */
	asd_ग_लिखो_reg_dword(asd_ha, LmARP2INTEN(lseq), EN_ARP2HALTC);

	asd_ग_लिखो_reg_byte(asd_ha, LmSCRATCHPAGE(lseq), 0);

	/* Initialize Mode 0,1, and 2 SCRATCHPAGE to 0. */
	क्रम (i = 0; i < 3; i++)
		asd_ग_लिखो_reg_byte(asd_ha, LmMnSCRATCHPAGE(lseq, i), 0);

	/* Initialize Mode 5 SCRATCHPAGE to 0. */
	asd_ग_लिखो_reg_byte(asd_ha, LmMnSCRATCHPAGE(lseq, 5), 0);

	asd_ग_लिखो_reg_dword(asd_ha, LmRSPMBX(lseq), 0);
	/* Initialize Mode 0,1,2 and 5 Interrupt Enable and
	 * Interrupt रेजिस्टरs. */
	asd_ग_लिखो_reg_dword(asd_ha, LmMnINTEN(lseq, 0), LmM0INTEN_MASK);
	asd_ग_लिखो_reg_dword(asd_ha, LmMnINT(lseq, 0), 0xFFFFFFFF);
	/* Mode 1 */
	asd_ग_लिखो_reg_dword(asd_ha, LmMnINTEN(lseq, 1), LmM1INTEN_MASK);
	asd_ग_लिखो_reg_dword(asd_ha, LmMnINT(lseq, 1), 0xFFFFFFFF);
	/* Mode 2 */
	asd_ग_लिखो_reg_dword(asd_ha, LmMnINTEN(lseq, 2), LmM2INTEN_MASK);
	asd_ग_लिखो_reg_dword(asd_ha, LmMnINT(lseq, 2), 0xFFFFFFFF);
	/* Mode 5 */
	asd_ग_लिखो_reg_dword(asd_ha, LmMnINTEN(lseq, 5), LmM5INTEN_MASK);
	asd_ग_लिखो_reg_dword(asd_ha, LmMnINT(lseq, 5), 0xFFFFFFFF);

	/* Enable HW Timer status. */
	asd_ग_लिखो_reg_byte(asd_ha, LmHWTSTATEN(lseq), LmHWTSTATEN_MASK);

	/* Enable Primitive Status 0 and 1. */
	asd_ग_लिखो_reg_dword(asd_ha, LmPRIMSTAT0EN(lseq), LmPRIMSTAT0EN_MASK);
	asd_ग_लिखो_reg_dword(asd_ha, LmPRIMSTAT1EN(lseq), LmPRIMSTAT1EN_MASK);

	/* Enable Frame Error. */
	asd_ग_लिखो_reg_dword(asd_ha, LmFRMERREN(lseq), LmFRMERREN_MASK);
	asd_ग_लिखो_reg_byte(asd_ha, LmMnHOLDLVL(lseq, 0), 0x50);

	/* Initialize Mode 0 Transfer Level to 512. */
	asd_ग_लिखो_reg_byte(asd_ha,  LmMnXFRLVL(lseq, 0), LmMnXFRLVL_512);
	/* Initialize Mode 1 Transfer Level to 256. */
	asd_ग_लिखो_reg_byte(asd_ha, LmMnXFRLVL(lseq, 1), LmMnXFRLVL_256);

	/* Initialize Program Count. */
	asd_ग_लिखो_reg_word(asd_ha, LmPRGMCNT(lseq), lseq_idle_loop);

	/* Enable Blind SG Move. */
	asd_ग_लिखो_reg_dword(asd_ha, LmMODECTL(lseq), LmBLIND48);
	asd_ग_लिखो_reg_word(asd_ha, LmM3SATATIMER(lseq),
			   ASD_SATA_INTERLOCK_TIMEOUT);

	(व्योम) asd_पढ़ो_reg_dword(asd_ha, LmREQMBX(lseq));

	/* Clear Primitive Status 0 and 1. */
	asd_ग_लिखो_reg_dword(asd_ha, LmPRMSTAT0(lseq), 0xFFFFFFFF);
	asd_ग_लिखो_reg_dword(asd_ha, LmPRMSTAT1(lseq), 0xFFFFFFFF);

	/* Clear HW Timer status. */
	asd_ग_लिखो_reg_byte(asd_ha, LmHWTSTAT(lseq), 0xFF);

	/* Clear DMA Errors क्रम Mode 0 and 1. */
	asd_ग_लिखो_reg_byte(asd_ha, LmMnDMAERRS(lseq, 0), 0xFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmMnDMAERRS(lseq, 1), 0xFF);

	/* Clear SG DMA Errors क्रम Mode 0 and 1. */
	asd_ग_लिखो_reg_byte(asd_ha, LmMnSGDMAERRS(lseq, 0), 0xFF);
	asd_ग_लिखो_reg_byte(asd_ha, LmMnSGDMAERRS(lseq, 1), 0xFF);

	/* Clear Mode 0 Buffer Parity Error. */
	asd_ग_लिखो_reg_byte(asd_ha, LmMnBUFSTAT(lseq, 0), LmMnBUFPERR);

	/* Clear Mode 0 Frame Error रेजिस्टर. */
	asd_ग_लिखो_reg_dword(asd_ha, LmMnFRMERR(lseq, 0), 0xFFFFFFFF);

	/* Reset LSEQ बाह्यal पूर्णांकerrupt arbiter. */
	asd_ग_लिखो_reg_byte(asd_ha, LmARP2INTCTL(lseq), RSTINTCTL);

	/* Set the Phy SAS क्रम the LmSEQ WWN. */
	sas_addr = asd_ha->phys[lseq].phy_desc->sas_addr;
	क्रम (i = 0; i < SAS_ADDR_SIZE; i++)
		asd_ग_लिखो_reg_byte(asd_ha, LmWWN(lseq) + i, sas_addr[i]);

	/* Set the Transmit Size to 1024 bytes, 0 = 256 Dwords. */
	asd_ग_लिखो_reg_byte(asd_ha, LmMnXMTSIZE(lseq, 1), 0);

	/* Set the Bus Inactivity Time Limit Timer. */
	asd_ग_लिखो_reg_word(asd_ha, LmBITL_TIMER(lseq), 9);

	/* Enable SATA Port Multiplier. */
	asd_ग_लिखो_reg_byte(asd_ha, LmMnSATAFS(lseq, 1), 0x80);

	/* Initialize Interrupt Vector[0-10] address in Mode 3.
	 * See the comment on CSEQ_INT_* */
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC0(lseq), lseq_vecs[0]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC1(lseq), lseq_vecs[1]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC2(lseq), lseq_vecs[2]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC3(lseq), lseq_vecs[3]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC4(lseq), lseq_vecs[4]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC5(lseq), lseq_vecs[5]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC6(lseq), lseq_vecs[6]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC7(lseq), lseq_vecs[7]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC8(lseq), lseq_vecs[8]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC9(lseq), lseq_vecs[9]);
	asd_ग_लिखो_reg_word(asd_ha, LmM3INTVEC10(lseq), lseq_vecs[10]);
	/*
	 * Program the Link LED control, applicable only क्रम
	 * Chip Rev. B or later.
	 */
	asd_ग_लिखो_reg_dword(asd_ha, LmCONTROL(lseq),
			    (LEDTIMER | LEDMODE_TXRX | LEDTIMERS_100ms));

	/* Set the Align Rate क्रम SAS and STP mode. */
	asd_ग_लिखो_reg_byte(asd_ha, LmM1SASALIGN(lseq), SAS_ALIGN_DEFAULT);
	asd_ग_लिखो_reg_byte(asd_ha, LmM1STPALIGN(lseq), STP_ALIGN_DEFAULT);
पूर्ण


/**
 * asd_post_init_cseq -- clear CSEQ Mode n Int. status and Response mailbox
 * @asd_ha: poपूर्णांकer to host adapter काष्ठा
 */
अटल व्योम asd_post_init_cseq(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		asd_ग_लिखो_reg_dword(asd_ha, CMnINT(i), 0xFFFFFFFF);
	क्रम (i = 0; i < 8; i++)
		asd_पढ़ो_reg_dword(asd_ha, CMnRSPMBX(i));
	/* Reset the बाह्यal पूर्णांकerrupt arbiter. */
	asd_ग_लिखो_reg_byte(asd_ha, CARP2INTCTL, RSTINTCTL);
पूर्ण

/**
 * asd_init_ddb_0 -- initialize DDB 0
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 *
 * Initialize DDB site 0 which is used पूर्णांकernally by the sequencer.
 */
अटल व्योम asd_init_ddb_0(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक	i;

	/* Zero out the DDB explicitly */
	क्रम (i = 0; i < माप(काष्ठा asd_ddb_seq_shared); i+=4)
		asd_ddbsite_ग_लिखो_dword(asd_ha, 0, i, 0);

	asd_ddbsite_ग_लिखो_word(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, q_मुक्त_ddb_head), 0);
	asd_ddbsite_ग_लिखो_word(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, q_मुक्त_ddb_tail),
			       asd_ha->hw_prof.max_ddbs-1);
	asd_ddbsite_ग_लिखो_word(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, q_मुक्त_ddb_cnt), 0);
	asd_ddbsite_ग_लिखो_word(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, q_used_ddb_head), 0xFFFF);
	asd_ddbsite_ग_लिखो_word(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, q_used_ddb_tail), 0xFFFF);
	asd_ddbsite_ग_लिखो_word(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, shared_mem_lock), 0);
	asd_ddbsite_ग_लिखो_word(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, smp_conn_tag), 0);
	asd_ddbsite_ग_लिखो_word(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, est_nexus_buf_cnt), 0);
	asd_ddbsite_ग_लिखो_word(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, est_nexus_buf_thresh),
			       asd_ha->hw_prof.num_phys * 2);
	asd_ddbsite_ग_लिखो_byte(asd_ha, 0,
		 दुरत्व(काष्ठा asd_ddb_seq_shared, settable_max_contexts),0);
	asd_ddbsite_ग_लिखो_byte(asd_ha, 0,
	       दुरत्व(काष्ठा asd_ddb_seq_shared, conn_not_active), 0xFF);
	asd_ddbsite_ग_लिखो_byte(asd_ha, 0,
	       दुरत्व(काष्ठा asd_ddb_seq_shared, phy_is_up), 0x00);
	/* DDB 0 is reserved */
	set_bit(0, asd_ha->hw_prof.ddb_biपंचांगap);
पूर्ण

अटल व्योम asd_seq_init_ddb_sites(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक ddb_site;

	क्रम (ddb_site = 0 ; ddb_site < ASD_MAX_DDBS; ddb_site++)
		क्रम (i = 0; i < माप(काष्ठा asd_ddb_ssp_smp_target_port); i+= 4)
			asd_ddbsite_ग_लिखो_dword(asd_ha, ddb_site, i, 0);
पूर्ण

/**
 * asd_seq_setup_seqs -- setup and initialize central and link sequencers
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल व्योम asd_seq_setup_seqs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक 		lseq;
	u8		lseq_mask;

	/* Initialize DDB sites */
	asd_seq_init_ddb_sites(asd_ha);

	/* Initialize SCB sites. Done first to compute some values which
	 * the rest of the init code depends on. */
	asd_init_scb_sites(asd_ha);

	/* Initialize CSEQ Scratch RAM रेजिस्टरs. */
	asd_init_cseq_scratch(asd_ha);

	/* Initialize LmSEQ Scratch RAM रेजिस्टरs. */
	asd_init_lseq_scratch(asd_ha);

	/* Initialize CSEQ CIO रेजिस्टरs. */
	asd_init_cseq_cio(asd_ha);

	asd_init_ddb_0(asd_ha);

	/* Initialize LmSEQ CIO रेजिस्टरs. */
	lseq_mask = asd_ha->hw_prof.enabled_phys;
	क्रम_each_sequencer(lseq_mask, lseq_mask, lseq)
		asd_init_lseq_cio(asd_ha, lseq);
	asd_post_init_cseq(asd_ha);
पूर्ण


/**
 * asd_seq_start_cseq -- start the central sequencer, CSEQ
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 */
अटल पूर्णांक asd_seq_start_cseq(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	/* Reset the ARP2 inकाष्ठाion to location zero. */
	asd_ग_लिखो_reg_word(asd_ha, CPRGMCNT, cseq_idle_loop);

	/* Unछोड़ो the CSEQ  */
	वापस asd_unछोड़ो_cseq(asd_ha);
पूर्ण

/**
 * asd_seq_start_lseq -- start a link sequencer
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @lseq: the link sequencer of पूर्णांकerest
 */
अटल पूर्णांक asd_seq_start_lseq(काष्ठा asd_ha_काष्ठा *asd_ha, पूर्णांक lseq)
अणु
	/* Reset the ARP2 inकाष्ठाion to location zero. */
	asd_ग_लिखो_reg_word(asd_ha, LmPRGMCNT(lseq), lseq_idle_loop);

	/* Unछोड़ो the LmSEQ  */
	वापस asd_seq_unछोड़ो_lseq(asd_ha, lseq);
पूर्ण

पूर्णांक asd_release_firmware(व्योम)
अणु
	release_firmware(sequencer_fw);
	वापस 0;
पूर्ण

अटल पूर्णांक asd_request_firmware(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err, i;
	काष्ठा sequencer_file_header header;
	स्थिर काष्ठा sequencer_file_header *hdr_ptr;
	u32 csum = 0;
	u16 *ptr_cseq_vecs, *ptr_lseq_vecs;

	अगर (sequencer_fw)
		/* alपढ़ोy loaded */
		वापस 0;

	err = request_firmware(&sequencer_fw,
			       SAS_RAZOR_SEQUENCER_FW_खाता,
			       &asd_ha->pcidev->dev);
	अगर (err)
		वापस err;

	hdr_ptr = (स्थिर काष्ठा sequencer_file_header *)sequencer_fw->data;

	header.csum = le32_to_cpu(hdr_ptr->csum);
	header.major = le32_to_cpu(hdr_ptr->major);
	header.minor = le32_to_cpu(hdr_ptr->minor);
	header.cseq_table_offset = le32_to_cpu(hdr_ptr->cseq_table_offset);
	header.cseq_table_size = le32_to_cpu(hdr_ptr->cseq_table_size);
	header.lseq_table_offset = le32_to_cpu(hdr_ptr->lseq_table_offset);
	header.lseq_table_size = le32_to_cpu(hdr_ptr->lseq_table_size);
	header.cseq_code_offset = le32_to_cpu(hdr_ptr->cseq_code_offset);
	header.cseq_code_size = le32_to_cpu(hdr_ptr->cseq_code_size);
	header.lseq_code_offset = le32_to_cpu(hdr_ptr->lseq_code_offset);
	header.lseq_code_size = le32_to_cpu(hdr_ptr->lseq_code_size);
	header.mode2_task = le16_to_cpu(hdr_ptr->mode2_task);
	header.cseq_idle_loop = le16_to_cpu(hdr_ptr->cseq_idle_loop);
	header.lseq_idle_loop = le16_to_cpu(hdr_ptr->lseq_idle_loop);

	क्रम (i = माप(header.csum); i < sequencer_fw->size; i++)
		csum += sequencer_fw->data[i];

	अगर (csum != header.csum) अणु
		asd_prपूर्णांकk("Firmware file checksum mismatch\n");
		वापस -EINVAL;
	पूर्ण

	अगर (header.cseq_table_size != CSEQ_NUM_VECS ||
	    header.lseq_table_size != LSEQ_NUM_VECS) अणु
		asd_prपूर्णांकk("Firmware file table size mismatch\n");
		वापस -EINVAL;
	पूर्ण

	asd_prपूर्णांकk("Found sequencer Firmware version %d.%d (%s)\n",
		   header.major, header.minor, hdr_ptr->version);

	अगर (header.major != SAS_RAZOR_SEQUENCER_FW_MAJOR) अणु
		asd_prपूर्णांकk("Firmware Major Version Mismatch;"
			   "driver requires version %d.X",
			   SAS_RAZOR_SEQUENCER_FW_MAJOR);
		वापस -EINVAL;
	पूर्ण

	ptr_cseq_vecs = (u16 *)&sequencer_fw->data[header.cseq_table_offset];
	ptr_lseq_vecs = (u16 *)&sequencer_fw->data[header.lseq_table_offset];
	mode2_task = header.mode2_task;
	cseq_idle_loop = header.cseq_idle_loop;
	lseq_idle_loop = header.lseq_idle_loop;

	क्रम (i = 0; i < CSEQ_NUM_VECS; i++)
		cseq_vecs[i] = le16_to_cpu(ptr_cseq_vecs[i]);

	क्रम (i = 0; i < LSEQ_NUM_VECS; i++)
		lseq_vecs[i] = le16_to_cpu(ptr_lseq_vecs[i]);

	cseq_code = &sequencer_fw->data[header.cseq_code_offset];
	cseq_code_size = header.cseq_code_size;
	lseq_code = &sequencer_fw->data[header.lseq_code_offset];
	lseq_code_size = header.lseq_code_size;

	वापस 0;
पूर्ण

पूर्णांक asd_init_seqs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;

	err = asd_request_firmware(asd_ha);

	अगर (err) अणु
		asd_prपूर्णांकk("Failed to load sequencer firmware file %s, error %d\n",
			   SAS_RAZOR_SEQUENCER_FW_खाता, err);
		वापस err;
	पूर्ण

	err = asd_seq_करोwnload_seqs(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't download sequencers for %s\n",
			   pci_name(asd_ha->pcidev));
		वापस err;
	पूर्ण

	asd_seq_setup_seqs(asd_ha);

	वापस 0;
पूर्ण

पूर्णांक asd_start_seqs(काष्ठा asd_ha_काष्ठा *asd_ha)
अणु
	पूर्णांक err;
	u8  lseq_mask;
	पूर्णांक lseq;

	err = asd_seq_start_cseq(asd_ha);
	अगर (err) अणु
		asd_prपूर्णांकk("couldn't start CSEQ for %s\n",
			   pci_name(asd_ha->pcidev));
		वापस err;
	पूर्ण

	lseq_mask = asd_ha->hw_prof.enabled_phys;
	क्रम_each_sequencer(lseq_mask, lseq_mask, lseq) अणु
		err = asd_seq_start_lseq(asd_ha, lseq);
		अगर (err) अणु
			asd_prपूर्णांकk("couldn't start LSEQ %d for %s\n", lseq,
				   pci_name(asd_ha->pcidev));
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * asd_update_port_links -- update port_map_by_links and phy_is_up
 * @asd_ha: poपूर्णांकer to host adapter काष्ठाure
 * @phy: poपूर्णांकer to the phy which has been added to a port
 *
 * 1) When a link reset has completed and we got BYTES DMAED with a
 * valid frame we call this function क्रम that phy, to indicate that
 * the phy is up, i.e. we update the phy_is_up in DDB 0.  The
 * sequencer checks phy_is_up when pending SCBs are to be sent, and
 * when an खोलो address frame has been received.
 *
 * 2) When we know of ports, we call this function to update the map
 * of phys participaing in that port, i.e. we update the
 * port_map_by_links in DDB 0.  When a HARD_RESET primitive has been
 * received, the sequencer disables all phys in that port.
 * port_map_by_links is also used as the conn_mask byte in the
 * initiator/target port DDB.
 */
व्योम asd_update_port_links(काष्ठा asd_ha_काष्ठा *asd_ha, काष्ठा asd_phy *phy)
अणु
	स्थिर u8 phy_mask = (u8) phy->asd_port->phy_mask;
	u8  phy_is_up;
	u8  mask;
	पूर्णांक i, err;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&asd_ha->hw_prof.ddb_lock, flags);
	क्रम_each_phy(phy_mask, mask, i)
		asd_ddbsite_ग_लिखो_byte(asd_ha, 0,
				       दुरत्व(काष्ठा asd_ddb_seq_shared,
						port_map_by_links)+i,phy_mask);

	क्रम (i = 0; i < 12; i++) अणु
		phy_is_up = asd_ddbsite_पढ़ो_byte(asd_ha, 0,
			  दुरत्व(काष्ठा asd_ddb_seq_shared, phy_is_up));
		err = asd_ddbsite_update_byte(asd_ha, 0,
				दुरत्व(काष्ठा asd_ddb_seq_shared, phy_is_up),
				phy_is_up,
				phy_is_up | phy_mask);
		अगर (!err)
			अवरोध;
		अन्यथा अगर (err == -EFAULT) अणु
			asd_prपूर्णांकk("phy_is_up: parity error in DDB 0\n");
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&asd_ha->hw_prof.ddb_lock, flags);

	अगर (err)
		asd_prपूर्णांकk("couldn't update DDB 0:error:%d\n", err);
पूर्ण

MODULE_FIRMWARE(SAS_RAZOR_SEQUENCER_FW_खाता);
