<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram pcxhr compatible soundcards
 *
 * low level पूर्णांकerface with पूर्णांकerrupt and message handling implementation
 *
 * Copyright (c) 2004 by Digigram <alsa@digigram.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश "pcxhr.h"
#समावेश "pcxhr_mixer.h"
#समावेश "pcxhr_hwdep.h"
#समावेश "pcxhr_core.h"


/* रेजिस्टरs used on the PLX (port 1) */
#घोषणा PCXHR_PLX_OFFSET_MIN	0x40
#घोषणा PCXHR_PLX_MBOX0		0x40
#घोषणा PCXHR_PLX_MBOX1		0x44
#घोषणा PCXHR_PLX_MBOX2		0x48
#घोषणा PCXHR_PLX_MBOX3		0x4C
#घोषणा PCXHR_PLX_MBOX4		0x50
#घोषणा PCXHR_PLX_MBOX5		0x54
#घोषणा PCXHR_PLX_MBOX6		0x58
#घोषणा PCXHR_PLX_MBOX7		0x5C
#घोषणा PCXHR_PLX_L2PCIDB	0x64
#घोषणा PCXHR_PLX_IRQCS		0x68
#घोषणा PCXHR_PLX_CHIPSC	0x6C

/* रेजिस्टरs used on the DSP (port 2) */
#घोषणा PCXHR_DSP_ICR		0x00
#घोषणा PCXHR_DSP_CVR		0x04
#घोषणा PCXHR_DSP_ISR		0x08
#घोषणा PCXHR_DSP_IVR		0x0C
#घोषणा PCXHR_DSP_RXH		0x14
#घोषणा PCXHR_DSP_TXH		0x14
#घोषणा PCXHR_DSP_RXM		0x18
#घोषणा PCXHR_DSP_TXM		0x18
#घोषणा PCXHR_DSP_RXL		0x1C
#घोषणा PCXHR_DSP_TXL		0x1C
#घोषणा PCXHR_DSP_RESET		0x20
#घोषणा PCXHR_DSP_OFFSET_MAX	0x20

/* access to the card */
#घोषणा PCXHR_PLX 1
#घोषणा PCXHR_DSP 2

#अगर (PCXHR_DSP_OFFSET_MAX > PCXHR_PLX_OFFSET_MIN)
#अघोषित  PCXHR_REG_TO_PORT(x)
#अन्यथा
#घोषणा PCXHR_REG_TO_PORT(x)	((x)>PCXHR_DSP_OFFSET_MAX ? PCXHR_PLX : PCXHR_DSP)
#पूर्ण_अगर
#घोषणा PCXHR_INPB(mgr,x)	inb((mgr)->port[PCXHR_REG_TO_PORT(x)] + (x))
#घोषणा PCXHR_INPL(mgr,x)	inl((mgr)->port[PCXHR_REG_TO_PORT(x)] + (x))
#घोषणा PCXHR_OUTPB(mgr,x,data)	outb((data), (mgr)->port[PCXHR_REG_TO_PORT(x)] + (x))
#घोषणा PCXHR_OUTPL(mgr,x,data)	outl((data), (mgr)->port[PCXHR_REG_TO_PORT(x)] + (x))
/* attention : access the PCXHR_DSP_* रेजिस्टरs with inb and outb only ! */

/* params used with PCXHR_PLX_MBOX0 */
#घोषणा PCXHR_MBOX0_HF5			(1 << 0)
#घोषणा PCXHR_MBOX0_HF4			(1 << 1)
#घोषणा PCXHR_MBOX0_BOOT_HERE		(1 << 23)
/* params used with PCXHR_PLX_IRQCS */
#घोषणा PCXHR_IRQCS_ENABLE_PCIIRQ	(1 << 8)
#घोषणा PCXHR_IRQCS_ENABLE_PCIDB	(1 << 9)
#घोषणा PCXHR_IRQCS_ACTIVE_PCIDB	(1 << 13)
/* params used with PCXHR_PLX_CHIPSC */
#घोषणा PCXHR_CHIPSC_INIT_VALUE		0x100D767E
#घोषणा PCXHR_CHIPSC_RESET_XILINX	(1 << 16)
#घोषणा PCXHR_CHIPSC_GPI_USERI		(1 << 17)
#घोषणा PCXHR_CHIPSC_DATA_CLK		(1 << 24)
#घोषणा PCXHR_CHIPSC_DATA_IN		(1 << 26)

/* params used with PCXHR_DSP_ICR */
#घोषणा PCXHR_ICR_HI08_RREQ		0x01
#घोषणा PCXHR_ICR_HI08_TREQ		0x02
#घोषणा PCXHR_ICR_HI08_HDRQ		0x04
#घोषणा PCXHR_ICR_HI08_HF0		0x08
#घोषणा PCXHR_ICR_HI08_HF1		0x10
#घोषणा PCXHR_ICR_HI08_HLEND		0x20
#घोषणा PCXHR_ICR_HI08_INIT		0x80
/* params used with PCXHR_DSP_CVR */
#घोषणा PCXHR_CVR_HI08_HC		0x80
/* params used with PCXHR_DSP_ISR */
#घोषणा PCXHR_ISR_HI08_RXDF		0x01
#घोषणा PCXHR_ISR_HI08_TXDE		0x02
#घोषणा PCXHR_ISR_HI08_TRDY		0x04
#घोषणा PCXHR_ISR_HI08_ERR		0x08
#घोषणा PCXHR_ISR_HI08_CHK		0x10
#घोषणा PCXHR_ISR_HI08_HREQ		0x80


/* स्थिरants used क्रम delay in msec */
#घोषणा PCXHR_WAIT_DEFAULT		2
#घोषणा PCXHR_WAIT_IT			25
#घोषणा PCXHR_WAIT_IT_EXTRA		65

/*
 * pcxhr_check_reg_bit - रुको क्रम the specअगरied bit is set/reset on a रेजिस्टर
 * @reg: रेजिस्टर to check
 * @mask: bit mask
 * @bit: resultant bit to be checked
 * @समय: समय-out of loop in msec
 *
 * वापसs zero अगर a bit matches, or a negative error code.
 */
अटल पूर्णांक pcxhr_check_reg_bit(काष्ठा pcxhr_mgr *mgr, अचिन्हित पूर्णांक reg,
			       अचिन्हित अक्षर mask, अचिन्हित अक्षर bit, पूर्णांक समय,
			       अचिन्हित अक्षर* पढ़ो)
अणु
	पूर्णांक i = 0;
	अचिन्हित दीर्घ end_समय = jअगरfies + (समय * HZ + 999) / 1000;
	करो अणु
		*पढ़ो = PCXHR_INPB(mgr, reg);
		अगर ((*पढ़ो & mask) == bit) अणु
			अगर (i > 100)
				dev_dbg(&mgr->pci->dev,
					"ATTENTION! check_reg(%x) loopcount=%d\n",
					    reg, i);
			वापस 0;
		पूर्ण
		i++;
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
	dev_err(&mgr->pci->dev,
		   "pcxhr_check_reg_bit: timeout, reg=%x, mask=0x%x, val=%x\n",
		   reg, mask, *पढ़ो);
	वापस -EIO;
पूर्ण

/* स्थिरants used with pcxhr_check_reg_bit() */
#घोषणा PCXHR_TIMEOUT_DSP		200


#घोषणा PCXHR_MASK_EXTRA_INFO		0x0000FE
#घोषणा PCXHR_MASK_IT_HF0		0x000100
#घोषणा PCXHR_MASK_IT_HF1		0x000200
#घोषणा PCXHR_MASK_IT_NO_HF0_HF1	0x000400
#घोषणा PCXHR_MASK_IT_MANAGE_HF5	0x000800
#घोषणा PCXHR_MASK_IT_WAIT		0x010000
#घोषणा PCXHR_MASK_IT_WAIT_EXTRA	0x020000

#घोषणा PCXHR_IT_SEND_BYTE_XILINX	(0x0000003C | PCXHR_MASK_IT_HF0)
#घोषणा PCXHR_IT_TEST_XILINX		(0x0000003C | PCXHR_MASK_IT_HF1 | \
					 PCXHR_MASK_IT_MANAGE_HF5)
#घोषणा PCXHR_IT_DOWNLOAD_BOOT		(0x0000000C | PCXHR_MASK_IT_HF1 | \
					 PCXHR_MASK_IT_MANAGE_HF5 | \
					 PCXHR_MASK_IT_WAIT)
#घोषणा PCXHR_IT_RESET_BOARD_FUNC	(0x0000000C | PCXHR_MASK_IT_HF0 | \
					 PCXHR_MASK_IT_MANAGE_HF5 | \
					 PCXHR_MASK_IT_WAIT_EXTRA)
#घोषणा PCXHR_IT_DOWNLOAD_DSP		(0x0000000C | \
					 PCXHR_MASK_IT_MANAGE_HF5 | \
					 PCXHR_MASK_IT_WAIT)
#घोषणा PCXHR_IT_DEBUG			(0x0000005A | PCXHR_MASK_IT_NO_HF0_HF1)
#घोषणा PCXHR_IT_RESET_SEMAPHORE	(0x0000005C | PCXHR_MASK_IT_NO_HF0_HF1)
#घोषणा PCXHR_IT_MESSAGE		(0x00000074 | PCXHR_MASK_IT_NO_HF0_HF1)
#घोषणा PCXHR_IT_RESET_CHK		(0x00000076 | PCXHR_MASK_IT_NO_HF0_HF1)
#घोषणा PCXHR_IT_UPDATE_RBUFFER		(0x00000078 | PCXHR_MASK_IT_NO_HF0_HF1)

अटल पूर्णांक pcxhr_send_it_dsp(काष्ठा pcxhr_mgr *mgr,
			     अचिन्हित पूर्णांक itdsp, पूर्णांक atomic)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर reg;

	अगर (itdsp & PCXHR_MASK_IT_MANAGE_HF5) अणु
		/* clear hf5 bit */
		PCXHR_OUTPL(mgr, PCXHR_PLX_MBOX0,
			    PCXHR_INPL(mgr, PCXHR_PLX_MBOX0) &
			    ~PCXHR_MBOX0_HF5);
	पूर्ण
	अगर ((itdsp & PCXHR_MASK_IT_NO_HF0_HF1) == 0) अणु
		reg = (PCXHR_ICR_HI08_RREQ |
		       PCXHR_ICR_HI08_TREQ |
		       PCXHR_ICR_HI08_HDRQ);
		अगर (itdsp & PCXHR_MASK_IT_HF0)
			reg |= PCXHR_ICR_HI08_HF0;
		अगर (itdsp & PCXHR_MASK_IT_HF1)
			reg |= PCXHR_ICR_HI08_HF1;
		PCXHR_OUTPB(mgr, PCXHR_DSP_ICR, reg);
	पूर्ण
	reg = (अचिन्हित अक्षर)(((itdsp & PCXHR_MASK_EXTRA_INFO) >> 1) |
			      PCXHR_CVR_HI08_HC);
	PCXHR_OUTPB(mgr, PCXHR_DSP_CVR, reg);
	अगर (itdsp & PCXHR_MASK_IT_WAIT) अणु
		अगर (atomic)
			mdelay(PCXHR_WAIT_IT);
		अन्यथा
			msleep(PCXHR_WAIT_IT);
	पूर्ण
	अगर (itdsp & PCXHR_MASK_IT_WAIT_EXTRA) अणु
		अगर (atomic)
			mdelay(PCXHR_WAIT_IT_EXTRA);
		अन्यथा
			msleep(PCXHR_WAIT_IT);
	पूर्ण
	/* रुको क्रम CVR_HI08_HC == 0 */
	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_CVR,  PCXHR_CVR_HI08_HC, 0,
				  PCXHR_TIMEOUT_DSP, &reg);
	अगर (err) अणु
		dev_err(&mgr->pci->dev, "pcxhr_send_it_dsp : TIMEOUT CVR\n");
		वापस err;
	पूर्ण
	अगर (itdsp & PCXHR_MASK_IT_MANAGE_HF5) अणु
		/* रुको क्रम hf5 bit */
		err = pcxhr_check_reg_bit(mgr, PCXHR_PLX_MBOX0,
					  PCXHR_MBOX0_HF5,
					  PCXHR_MBOX0_HF5,
					  PCXHR_TIMEOUT_DSP,
					  &reg);
		अगर (err) अणु
			dev_err(&mgr->pci->dev,
				   "pcxhr_send_it_dsp : TIMEOUT HF5\n");
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0; /* retry not handled here */
पूर्ण

व्योम pcxhr_reset_xilinx_com(काष्ठा pcxhr_mgr *mgr)
अणु
	/* reset second xilinx */
	PCXHR_OUTPL(mgr, PCXHR_PLX_CHIPSC,
		    PCXHR_CHIPSC_INIT_VALUE & ~PCXHR_CHIPSC_RESET_XILINX);
पूर्ण

अटल व्योम pcxhr_enable_irq(काष्ठा pcxhr_mgr *mgr, पूर्णांक enable)
अणु
	अचिन्हित पूर्णांक reg = PCXHR_INPL(mgr, PCXHR_PLX_IRQCS);
	/* enable/disable पूर्णांकerrupts */
	अगर (enable)
		reg |=  (PCXHR_IRQCS_ENABLE_PCIIRQ | PCXHR_IRQCS_ENABLE_PCIDB);
	अन्यथा
		reg &= ~(PCXHR_IRQCS_ENABLE_PCIIRQ | PCXHR_IRQCS_ENABLE_PCIDB);
	PCXHR_OUTPL(mgr, PCXHR_PLX_IRQCS, reg);
पूर्ण

व्योम pcxhr_reset_dsp(काष्ठा pcxhr_mgr *mgr)
अणु
	/* disable पूर्णांकerrupts */
	pcxhr_enable_irq(mgr, 0);

	/* let's reset the DSP */
	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET, 0);
	msleep( PCXHR_WAIT_DEFAULT ); /* रुको 2 msec */
	PCXHR_OUTPB(mgr, PCXHR_DSP_RESET, 3);
	msleep( PCXHR_WAIT_DEFAULT ); /* रुको 2 msec */

	/* reset mailbox */
	PCXHR_OUTPL(mgr, PCXHR_PLX_MBOX0, 0);
पूर्ण

व्योम pcxhr_enable_dsp(काष्ठा pcxhr_mgr *mgr)
अणु
	/* enable पूर्णांकerrupts */
	pcxhr_enable_irq(mgr, 1);
पूर्ण

/*
 * load the xilinx image
 */
पूर्णांक pcxhr_load_xilinx_binary(काष्ठा pcxhr_mgr *mgr,
			     स्थिर काष्ठा firmware *xilinx, पूर्णांक second)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक chipsc;
	अचिन्हित अक्षर data;
	अचिन्हित अक्षर mask;
	स्थिर अचिन्हित अक्षर *image;

	/* test first xilinx */
	chipsc = PCXHR_INPL(mgr, PCXHR_PLX_CHIPSC);
	/* REV01 cards करो not support the PCXHR_CHIPSC_GPI_USERI bit anymore */
	/* this bit will always be 1;
	 * no possibility to test presence of first xilinx
	 */
	अगर(second) अणु
		अगर ((chipsc & PCXHR_CHIPSC_GPI_USERI) == 0) अणु
			dev_err(&mgr->pci->dev, "error loading first xilinx\n");
			वापस -EINVAL;
		पूर्ण
		/* activate second xilinx */
		chipsc |= PCXHR_CHIPSC_RESET_XILINX;
		PCXHR_OUTPL(mgr, PCXHR_PLX_CHIPSC, chipsc);
		msleep( PCXHR_WAIT_DEFAULT ); /* रुको 2 msec */
	पूर्ण
	image = xilinx->data;
	क्रम (i = 0; i < xilinx->size; i++, image++) अणु
		data = *image;
		mask = 0x80;
		जबतक (mask) अणु
			chipsc &= ~(PCXHR_CHIPSC_DATA_CLK |
				    PCXHR_CHIPSC_DATA_IN);
			अगर (data & mask)
				chipsc |= PCXHR_CHIPSC_DATA_IN;
			PCXHR_OUTPL(mgr, PCXHR_PLX_CHIPSC, chipsc);
			chipsc |= PCXHR_CHIPSC_DATA_CLK;
			PCXHR_OUTPL(mgr, PCXHR_PLX_CHIPSC, chipsc);
			mask >>= 1;
		पूर्ण
		/* करोn't take too much समय in this loop... */
		cond_resched();
	पूर्ण
	chipsc &= ~(PCXHR_CHIPSC_DATA_CLK | PCXHR_CHIPSC_DATA_IN);
	PCXHR_OUTPL(mgr, PCXHR_PLX_CHIPSC, chipsc);
	/* रुको 2 msec (समय to boot the xilinx beक्रमe any access) */
	msleep( PCXHR_WAIT_DEFAULT );
	वापस 0;
पूर्ण

/*
 * send an executable file to the DSP
 */
अटल पूर्णांक pcxhr_करोwnload_dsp(काष्ठा pcxhr_mgr *mgr, स्थिर काष्ठा firmware *dsp)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक len;
	स्थिर अचिन्हित अक्षर *data;
	अचिन्हित अक्षर dummy;
	/* check the length of boot image */
	अगर (dsp->size <= 0)
		वापस -EINVAL;
	अगर (dsp->size % 3)
		वापस -EINVAL;
	अगर (snd_BUG_ON(!dsp->data))
		वापस -EINVAL;
	/* transfert data buffer from PC to DSP */
	क्रम (i = 0; i < dsp->size; i += 3) अणु
		data = dsp->data + i;
		अगर (i == 0) अणु
			/* test data header consistency */
			len = (अचिन्हित पूर्णांक)((data[0]<<16) +
					     (data[1]<<8) +
					     data[2]);
			अगर (len && (dsp->size != (len + 2) * 3))
				वापस -EINVAL;
		पूर्ण
		/* रुको DSP पढ़ोy क्रम new transfer */
		err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
					  PCXHR_ISR_HI08_TRDY,
					  PCXHR_ISR_HI08_TRDY,
					  PCXHR_TIMEOUT_DSP, &dummy);
		अगर (err) अणु
			dev_err(&mgr->pci->dev,
				   "dsp loading error at position %d\n", i);
			वापस err;
		पूर्ण
		/* send host data */
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXH, data[0]);
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXM, data[1]);
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXL, data[2]);

		/* करोn't take too much समय in this loop... */
		cond_resched();
	पूर्ण
	/* give some समय to boot the DSP */
	msleep(PCXHR_WAIT_DEFAULT);
	वापस 0;
पूर्ण

/*
 * load the eeprom image
 */
पूर्णांक pcxhr_load_eeprom_binary(काष्ठा pcxhr_mgr *mgr,
			     स्थिर काष्ठा firmware *eeprom)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर reg;

	/* init value of the ICR रेजिस्टर */
	reg = PCXHR_ICR_HI08_RREQ | PCXHR_ICR_HI08_TREQ | PCXHR_ICR_HI08_HDRQ;
	अगर (PCXHR_INPL(mgr, PCXHR_PLX_MBOX0) & PCXHR_MBOX0_BOOT_HERE) अणु
		/* no need to load the eeprom binary,
		 * but init the HI08 पूर्णांकerface
		 */
		PCXHR_OUTPB(mgr, PCXHR_DSP_ICR, reg | PCXHR_ICR_HI08_INIT);
		msleep(PCXHR_WAIT_DEFAULT);
		PCXHR_OUTPB(mgr, PCXHR_DSP_ICR, reg);
		msleep(PCXHR_WAIT_DEFAULT);
		dev_dbg(&mgr->pci->dev, "no need to load eeprom boot\n");
		वापस 0;
	पूर्ण
	PCXHR_OUTPB(mgr, PCXHR_DSP_ICR, reg);

	err = pcxhr_करोwnload_dsp(mgr, eeprom);
	अगर (err)
		वापस err;
	/* रुको क्रम chk bit */
	वापस pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR, PCXHR_ISR_HI08_CHK,
				   PCXHR_ISR_HI08_CHK, PCXHR_TIMEOUT_DSP, &reg);
पूर्ण

/*
 * load the boot image
 */
पूर्णांक pcxhr_load_boot_binary(काष्ठा pcxhr_mgr *mgr, स्थिर काष्ठा firmware *boot)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक physaddr = mgr->hostport.addr;
	अचिन्हित अक्षर dummy;

	/* send the hostport address to the DSP (only the upper 24 bit !) */
	अगर (snd_BUG_ON(physaddr & 0xff))
		वापस -EINVAL;
	PCXHR_OUTPL(mgr, PCXHR_PLX_MBOX1, (physaddr >> 8));

	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_DOWNLOAD_BOOT, 0);
	अगर (err)
		वापस err;
	/* clear hf5 bit */
	PCXHR_OUTPL(mgr, PCXHR_PLX_MBOX0,
		    PCXHR_INPL(mgr, PCXHR_PLX_MBOX0) & ~PCXHR_MBOX0_HF5);

	err = pcxhr_करोwnload_dsp(mgr, boot);
	अगर (err)
		वापस err;
	/* रुको क्रम hf5 bit */
	वापस pcxhr_check_reg_bit(mgr, PCXHR_PLX_MBOX0, PCXHR_MBOX0_HF5,
				   PCXHR_MBOX0_HF5, PCXHR_TIMEOUT_DSP, &dummy);
पूर्ण

/*
 * load the final dsp image
 */
पूर्णांक pcxhr_load_dsp_binary(काष्ठा pcxhr_mgr *mgr, स्थिर काष्ठा firmware *dsp)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर dummy;
	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_RESET_BOARD_FUNC, 0);
	अगर (err)
		वापस err;
	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_DOWNLOAD_DSP, 0);
	अगर (err)
		वापस err;
	err = pcxhr_करोwnload_dsp(mgr, dsp);
	अगर (err)
		वापस err;
	/* रुको क्रम chk bit */
	वापस pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
				   PCXHR_ISR_HI08_CHK,
				   PCXHR_ISR_HI08_CHK,
				   PCXHR_TIMEOUT_DSP, &dummy);
पूर्ण


काष्ठा pcxhr_cmd_info अणु
	u32 opcode;		/* command word */
	u16 st_length;		/* status length */
	u16 st_type;		/* status type (RMH_SSIZE_XXX) */
पूर्ण;

/* RMH status type */
क्रमागत अणु
	RMH_SSIZE_FIXED = 0,	/* status size fix (st_length = 0..x) */
	RMH_SSIZE_ARG = 1,	/* status size given in the LSB byte */
	RMH_SSIZE_MASK = 2,	/* status size given in biपंचांगask */
पूर्ण;

/*
 * Array of DSP commands
 */
अटल स्थिर काष्ठा pcxhr_cmd_info pcxhr_dsp_cmds[] = अणु
[CMD_VERSION] =				अणु 0x010000, 1, RMH_SSIZE_FIXED पूर्ण,
[CMD_SUPPORTED] =			अणु 0x020000, 4, RMH_SSIZE_FIXED पूर्ण,
[CMD_TEST_IT] =				अणु 0x040000, 1, RMH_SSIZE_FIXED पूर्ण,
[CMD_SEND_IRQA] =			अणु 0x070001, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_ACCESS_IO_WRITE] =			अणु 0x090000, 1, RMH_SSIZE_ARG पूर्ण,
[CMD_ACCESS_IO_READ] =			अणु 0x094000, 1, RMH_SSIZE_ARG पूर्ण,
[CMD_ASYNC] =				अणु 0x0a0000, 1, RMH_SSIZE_ARG पूर्ण,
[CMD_MODIFY_CLOCK] =			अणु 0x0d0000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_RESYNC_AUDIO_INPUTS] =		अणु 0x0e0000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_GET_DSP_RESOURCES] =		अणु 0x100000, 4, RMH_SSIZE_FIXED पूर्ण,
[CMD_SET_TIMER_INTERRUPT] =		अणु 0x110000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_RES_PIPE] =			अणु 0x400000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_FREE_PIPE] =			अणु 0x410000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_CONF_PIPE] =			अणु 0x422101, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_STOP_PIPE] =			अणु 0x470004, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_PIPE_SAMPLE_COUNT] =		अणु 0x49a000, 2, RMH_SSIZE_FIXED पूर्ण,
[CMD_CAN_START_PIPE] =			अणु 0x4b0000, 1, RMH_SSIZE_FIXED पूर्ण,
[CMD_START_STREAM] =			अणु 0x802000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_STREAM_OUT_LEVEL_ADJUST] =		अणु 0x822000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_STOP_STREAM] =			अणु 0x832000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_UPDATE_R_BUFFERS] =		अणु 0x840000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_FORMAT_STREAM_OUT] =		अणु 0x860000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_FORMAT_STREAM_IN] =		अणु 0x870000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_STREAM_SAMPLE_COUNT] =		अणु 0x902000, 2, RMH_SSIZE_FIXED पूर्ण,
[CMD_AUDIO_LEVEL_ADJUST] =		अणु 0xc22000, 0, RMH_SSIZE_FIXED पूर्ण,
[CMD_GET_TIME_CODE] =			अणु 0x060000, 5, RMH_SSIZE_FIXED पूर्ण,
[CMD_MANAGE_SIGNAL] =			अणु 0x0f0000, 0, RMH_SSIZE_FIXED पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
अटल स्थिर अक्षर * स्थिर cmd_names[] = अणु
[CMD_VERSION] =				"CMD_VERSION",
[CMD_SUPPORTED] =			"CMD_SUPPORTED",
[CMD_TEST_IT] =				"CMD_TEST_IT",
[CMD_SEND_IRQA] =			"CMD_SEND_IRQA",
[CMD_ACCESS_IO_WRITE] =			"CMD_ACCESS_IO_WRITE",
[CMD_ACCESS_IO_READ] =			"CMD_ACCESS_IO_READ",
[CMD_ASYNC] =				"CMD_ASYNC",
[CMD_MODIFY_CLOCK] =			"CMD_MODIFY_CLOCK",
[CMD_RESYNC_AUDIO_INPUTS] =		"CMD_RESYNC_AUDIO_INPUTS",
[CMD_GET_DSP_RESOURCES] =		"CMD_GET_DSP_RESOURCES",
[CMD_SET_TIMER_INTERRUPT] =		"CMD_SET_TIMER_INTERRUPT",
[CMD_RES_PIPE] =			"CMD_RES_PIPE",
[CMD_FREE_PIPE] =			"CMD_FREE_PIPE",
[CMD_CONF_PIPE] =			"CMD_CONF_PIPE",
[CMD_STOP_PIPE] =			"CMD_STOP_PIPE",
[CMD_PIPE_SAMPLE_COUNT] =		"CMD_PIPE_SAMPLE_COUNT",
[CMD_CAN_START_PIPE] =			"CMD_CAN_START_PIPE",
[CMD_START_STREAM] =			"CMD_START_STREAM",
[CMD_STREAM_OUT_LEVEL_ADJUST] =		"CMD_STREAM_OUT_LEVEL_ADJUST",
[CMD_STOP_STREAM] =			"CMD_STOP_STREAM",
[CMD_UPDATE_R_BUFFERS] =		"CMD_UPDATE_R_BUFFERS",
[CMD_FORMAT_STREAM_OUT] =		"CMD_FORMAT_STREAM_OUT",
[CMD_FORMAT_STREAM_IN] =		"CMD_FORMAT_STREAM_IN",
[CMD_STREAM_SAMPLE_COUNT] =		"CMD_STREAM_SAMPLE_COUNT",
[CMD_AUDIO_LEVEL_ADJUST] =		"CMD_AUDIO_LEVEL_ADJUST",
[CMD_GET_TIME_CODE] =			"CMD_GET_TIME_CODE",
[CMD_MANAGE_SIGNAL] =			"CMD_MANAGE_SIGNAL",
पूर्ण;
#पूर्ण_अगर


अटल पूर्णांक pcxhr_पढ़ो_rmh_status(काष्ठा pcxhr_mgr *mgr, काष्ठा pcxhr_rmh *rmh)
अणु
	पूर्णांक err;
	पूर्णांक i;
	u32 data;
	u32 size_mask;
	अचिन्हित अक्षर reg;
	पूर्णांक max_stat_len;

	अगर (rmh->stat_len < PCXHR_SIZE_MAX_STATUS)
		max_stat_len = PCXHR_SIZE_MAX_STATUS;
	अन्यथा	max_stat_len = rmh->stat_len;

	क्रम (i = 0; i < rmh->stat_len; i++) अणु
		/* रुको क्रम receiver full */
		err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
					  PCXHR_ISR_HI08_RXDF,
					  PCXHR_ISR_HI08_RXDF,
					  PCXHR_TIMEOUT_DSP, &reg);
		अगर (err) अणु
			dev_err(&mgr->pci->dev,
				"ERROR RMH stat: ISR:RXDF=1 (ISR = %x; i=%d )\n",
				reg, i);
			वापस err;
		पूर्ण
		/* पढ़ो data */
		data  = PCXHR_INPB(mgr, PCXHR_DSP_TXH) << 16;
		data |= PCXHR_INPB(mgr, PCXHR_DSP_TXM) << 8;
		data |= PCXHR_INPB(mgr, PCXHR_DSP_TXL);

		/* need to update rmh->stat_len on the fly ?? */
		अगर (!i) अणु
			अगर (rmh->dsp_stat != RMH_SSIZE_FIXED) अणु
				अगर (rmh->dsp_stat == RMH_SSIZE_ARG) अणु
					rmh->stat_len = (data & 0x0000ff) + 1;
					data &= 0xffff00;
				पूर्ण अन्यथा अणु
					/* rmh->dsp_stat == RMH_SSIZE_MASK */
					rmh->stat_len = 1;
					size_mask = data;
					जबतक (size_mask) अणु
						अगर (size_mask & 1)
							rmh->stat_len++;
						size_mask >>= 1;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
		अगर (rmh->cmd_idx < CMD_LAST_INDEX)
			dev_dbg(&mgr->pci->dev, "    stat[%d]=%x\n", i, data);
#पूर्ण_अगर
		अगर (i < max_stat_len)
			rmh->stat[i] = data;
	पूर्ण
	अगर (rmh->stat_len > max_stat_len) अणु
		dev_dbg(&mgr->pci->dev, "PCXHR : rmh->stat_len=%x too big\n",
			    rmh->stat_len);
		rmh->stat_len = max_stat_len;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_send_msg_nolock(काष्ठा pcxhr_mgr *mgr, काष्ठा pcxhr_rmh *rmh)
अणु
	पूर्णांक err;
	पूर्णांक i;
	u32 data;
	अचिन्हित अक्षर reg;

	अगर (snd_BUG_ON(rmh->cmd_len >= PCXHR_SIZE_MAX_CMD))
		वापस -EINVAL;
	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_MESSAGE, 1);
	अगर (err) अणु
		dev_err(&mgr->pci->dev,
			"pcxhr_send_message : ED_DSP_CRASHED\n");
		वापस err;
	पूर्ण
	/* रुको क्रम chk bit */
	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR, PCXHR_ISR_HI08_CHK,
				  PCXHR_ISR_HI08_CHK, PCXHR_TIMEOUT_DSP, &reg);
	अगर (err)
		वापस err;
	/* reset irq chk */
	err = pcxhr_send_it_dsp(mgr, PCXHR_IT_RESET_CHK, 1);
	अगर (err)
		वापस err;
	/* रुको क्रम chk bit == 0*/
	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR, PCXHR_ISR_HI08_CHK, 0,
				  PCXHR_TIMEOUT_DSP, &reg);
	अगर (err)
		वापस err;

	data = rmh->cmd[0];

	अगर (rmh->cmd_len > 1)
		data |= 0x008000;	/* MASK_MORE_THAN_1_WORD_COMMAND */
	अन्यथा
		data &= 0xff7fff;	/* MASK_1_WORD_COMMAND */
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	अगर (rmh->cmd_idx < CMD_LAST_INDEX)
		dev_dbg(&mgr->pci->dev, "MSG cmd[0]=%x (%s)\n",
			    data, cmd_names[rmh->cmd_idx]);
#पूर्ण_अगर

	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR, PCXHR_ISR_HI08_TRDY,
				  PCXHR_ISR_HI08_TRDY, PCXHR_TIMEOUT_DSP, &reg);
	अगर (err)
		वापस err;
	PCXHR_OUTPB(mgr, PCXHR_DSP_TXH, (data>>16)&0xFF);
	PCXHR_OUTPB(mgr, PCXHR_DSP_TXM, (data>>8)&0xFF);
	PCXHR_OUTPB(mgr, PCXHR_DSP_TXL, (data&0xFF));

	अगर (rmh->cmd_len > 1) अणु
		/* send length */
		data = rmh->cmd_len - 1;
		err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
					  PCXHR_ISR_HI08_TRDY,
					  PCXHR_ISR_HI08_TRDY,
					  PCXHR_TIMEOUT_DSP, &reg);
		अगर (err)
			वापस err;
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXH, (data>>16)&0xFF);
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXM, (data>>8)&0xFF);
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXL, (data&0xFF));

		क्रम (i=1; i < rmh->cmd_len; i++) अणु
			/* send other words */
			data = rmh->cmd[i];
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
			अगर (rmh->cmd_idx < CMD_LAST_INDEX)
				dev_dbg(&mgr->pci->dev,
					"    cmd[%d]=%x\n", i, data);
#पूर्ण_अगर
			err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
						  PCXHR_ISR_HI08_TRDY,
						  PCXHR_ISR_HI08_TRDY,
						  PCXHR_TIMEOUT_DSP, &reg);
			अगर (err)
				वापस err;
			PCXHR_OUTPB(mgr, PCXHR_DSP_TXH, (data>>16)&0xFF);
			PCXHR_OUTPB(mgr, PCXHR_DSP_TXM, (data>>8)&0xFF);
			PCXHR_OUTPB(mgr, PCXHR_DSP_TXL, (data&0xFF));
		पूर्ण
	पूर्ण
	/* रुको क्रम chk bit */
	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR, PCXHR_ISR_HI08_CHK,
				  PCXHR_ISR_HI08_CHK, PCXHR_TIMEOUT_DSP, &reg);
	अगर (err)
		वापस err;
	/* test status ISR */
	अगर (reg & PCXHR_ISR_HI08_ERR) अणु
		/* ERROR, रुको क्रम receiver full */
		err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
					  PCXHR_ISR_HI08_RXDF,
					  PCXHR_ISR_HI08_RXDF,
					  PCXHR_TIMEOUT_DSP, &reg);
		अगर (err) अणु
			dev_err(&mgr->pci->dev,
				"ERROR RMH: ISR:RXDF=1 (ISR = %x)\n", reg);
			वापस err;
		पूर्ण
		/* पढ़ो error code */
		data  = PCXHR_INPB(mgr, PCXHR_DSP_TXH) << 16;
		data |= PCXHR_INPB(mgr, PCXHR_DSP_TXM) << 8;
		data |= PCXHR_INPB(mgr, PCXHR_DSP_TXL);
		dev_err(&mgr->pci->dev, "ERROR RMH(%d): 0x%x\n",
			   rmh->cmd_idx, data);
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		/* पढ़ो the response data */
		err = pcxhr_पढ़ो_rmh_status(mgr, rmh);
	पूर्ण
	/* reset semaphore */
	अगर (pcxhr_send_it_dsp(mgr, PCXHR_IT_RESET_SEMAPHORE, 1) < 0)
		वापस -EIO;
	वापस err;
पूर्ण


/**
 * pcxhr_init_rmh - initialize the RMH instance
 * @rmh: the rmh poपूर्णांकer to be initialized
 * @cmd: the rmh command to be set
 */
व्योम pcxhr_init_rmh(काष्ठा pcxhr_rmh *rmh, पूर्णांक cmd)
अणु
	अगर (snd_BUG_ON(cmd >= CMD_LAST_INDEX))
		वापस;
	rmh->cmd[0] = pcxhr_dsp_cmds[cmd].opcode;
	rmh->cmd_len = 1;
	rmh->stat_len = pcxhr_dsp_cmds[cmd].st_length;
	rmh->dsp_stat = pcxhr_dsp_cmds[cmd].st_type;
	rmh->cmd_idx = cmd;
पूर्ण


व्योम pcxhr_set_pipe_cmd_params(काष्ठा pcxhr_rmh *rmh, पूर्णांक capture,
			       अचिन्हित पूर्णांक param1, अचिन्हित पूर्णांक param2,
			       अचिन्हित पूर्णांक param3)
अणु
	snd_BUG_ON(param1 > MASK_FIRST_FIELD);
	अगर (capture)
		rmh->cmd[0] |= 0x800;		/* COMMAND_RECORD_MASK */
	अगर (param1)
		rmh->cmd[0] |= (param1 << FIELD_SIZE);
	अगर (param2) अणु
		snd_BUG_ON(param2 > MASK_FIRST_FIELD);
		rmh->cmd[0] |= param2;
	पूर्ण
	अगर(param3) अणु
		snd_BUG_ON(param3 > MASK_DSP_WORD);
		rmh->cmd[1] = param3;
		rmh->cmd_len = 2;
	पूर्ण
पूर्ण

/*
 * pcxhr_send_msg - send a DSP message with spinlock
 * @rmh: the rmh record to send and receive
 *
 * वापसs 0 अगर successful, or a negative error code.
 */
पूर्णांक pcxhr_send_msg(काष्ठा pcxhr_mgr *mgr, काष्ठा pcxhr_rmh *rmh)
अणु
	पूर्णांक err;

	mutex_lock(&mgr->msg_lock);
	err = pcxhr_send_msg_nolock(mgr, rmh);
	mutex_unlock(&mgr->msg_lock);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक pcxhr_pipes_running(काष्ठा pcxhr_mgr *mgr)
अणु
	पूर्णांक start_mask = PCXHR_INPL(mgr, PCXHR_PLX_MBOX2);
	/* least segnअगरicant 12 bits are the pipe states
	 * क्रम the playback audios
	 * next 12 bits are the pipe states क्रम the capture audios
	 * (PCXHR_PIPE_STATE_CAPTURE_OFFSET)
	 */
	start_mask &= 0xffffff;
	dev_dbg(&mgr->pci->dev, "CMD_PIPE_STATE MBOX2=0x%06x\n", start_mask);
	वापस start_mask;
पूर्ण

#घोषणा PCXHR_PIPE_STATE_CAPTURE_OFFSET		12
#घोषणा MAX_WAIT_FOR_DSP			20

अटल पूर्णांक pcxhr_prepair_pipe_start(काष्ठा pcxhr_mgr *mgr,
				    पूर्णांक audio_mask, पूर्णांक *retry)
अणु
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err;
	पूर्णांक audio = 0;

	*retry = 0;
	जबतक (audio_mask) अणु
		अगर (audio_mask & 1) अणु
			pcxhr_init_rmh(&rmh, CMD_CAN_START_PIPE);
			अगर (audio < PCXHR_PIPE_STATE_CAPTURE_OFFSET) अणु
				/* can start playback pipe */
				pcxhr_set_pipe_cmd_params(&rmh, 0, audio, 0, 0);
			पूर्ण अन्यथा अणु
				/* can start capture pipe */
				pcxhr_set_pipe_cmd_params(&rmh, 1, audio -
						PCXHR_PIPE_STATE_CAPTURE_OFFSET,
						0, 0);
			पूर्ण
			err = pcxhr_send_msg(mgr, &rmh);
			अगर (err) अणु
				dev_err(&mgr->pci->dev,
					   "error pipe start "
					   "(CMD_CAN_START_PIPE) err=%x!\n",
					   err);
				वापस err;
			पूर्ण
			/* अगर the pipe couldn't be prepaired क्रम start,
			 * retry it later
			 */
			अगर (rmh.stat[0] == 0)
				*retry |= (1<<audio);
		पूर्ण
		audio_mask>>=1;
		audio++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_stop_pipes(काष्ठा pcxhr_mgr *mgr, पूर्णांक audio_mask)
अणु
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err;
	पूर्णांक audio = 0;

	जबतक (audio_mask) अणु
		अगर (audio_mask & 1) अणु
			pcxhr_init_rmh(&rmh, CMD_STOP_PIPE);
			अगर (audio < PCXHR_PIPE_STATE_CAPTURE_OFFSET) अणु
				/* stop playback pipe */
				pcxhr_set_pipe_cmd_params(&rmh, 0, audio, 0, 0);
			पूर्ण अन्यथा अणु
				/* stop capture pipe */
				pcxhr_set_pipe_cmd_params(&rmh, 1, audio -
						PCXHR_PIPE_STATE_CAPTURE_OFFSET,
						0, 0);
			पूर्ण
			err = pcxhr_send_msg(mgr, &rmh);
			अगर (err) अणु
				dev_err(&mgr->pci->dev,
					   "error pipe stop "
					   "(CMD_STOP_PIPE) err=%x!\n", err);
				वापस err;
			पूर्ण
		पूर्ण
		audio_mask>>=1;
		audio++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_toggle_pipes(काष्ठा pcxhr_mgr *mgr, पूर्णांक audio_mask)
अणु
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err;
	पूर्णांक audio = 0;

	जबतक (audio_mask) अणु
		अगर (audio_mask & 1) अणु
			pcxhr_init_rmh(&rmh, CMD_CONF_PIPE);
			अगर (audio < PCXHR_PIPE_STATE_CAPTURE_OFFSET)
				pcxhr_set_pipe_cmd_params(&rmh, 0, 0, 0,
							  1 << audio);
			अन्यथा
				pcxhr_set_pipe_cmd_params(&rmh, 1, 0, 0,
							  1 << (audio - PCXHR_PIPE_STATE_CAPTURE_OFFSET));
			err = pcxhr_send_msg(mgr, &rmh);
			अगर (err) अणु
				dev_err(&mgr->pci->dev,
					   "error pipe start "
					   "(CMD_CONF_PIPE) err=%x!\n", err);
				वापस err;
			पूर्ण
		पूर्ण
		audio_mask>>=1;
		audio++;
	पूर्ण
	/* now fire the पूर्णांकerrupt on the card */
	pcxhr_init_rmh(&rmh, CMD_SEND_IRQA);
	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err) अणु
		dev_err(&mgr->pci->dev,
			   "error pipe start (CMD_SEND_IRQA) err=%x!\n",
			   err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण



पूर्णांक pcxhr_set_pipe_state(काष्ठा pcxhr_mgr *mgr, पूर्णांक playback_mask,
			 पूर्णांक capture_mask, पूर्णांक start)
अणु
	पूर्णांक state, i, err;
	पूर्णांक audio_mask;

#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	kसमय_प्रकार start_समय, stop_समय, dअगरf_समय;

	start_समय = kसमय_get();
#पूर्ण_अगर
	audio_mask = (playback_mask |
		      (capture_mask << PCXHR_PIPE_STATE_CAPTURE_OFFSET));
	/* current pipe state (playback + record) */
	state = pcxhr_pipes_running(mgr);
	dev_dbg(&mgr->pci->dev,
		"pcxhr_set_pipe_state %s (mask %x current %x)\n",
		    start ? "START" : "STOP", audio_mask, state);
	अगर (start) अणु
		/* start only pipes that are not yet started */
		audio_mask &= ~state;
		state = audio_mask;
		क्रम (i = 0; i < MAX_WAIT_FOR_DSP; i++) अणु
			err = pcxhr_prepair_pipe_start(mgr, state, &state);
			अगर (err)
				वापस err;
			अगर (state == 0)
				अवरोध;	/* success, all pipes prepaired */
			mdelay(1);	/* रुको 1 millisecond and retry */
		पूर्ण
	पूर्ण अन्यथा अणु
		audio_mask &= state;	/* stop only pipes that are started */
	पूर्ण
	अगर (audio_mask == 0)
		वापस 0;

	err = pcxhr_toggle_pipes(mgr, audio_mask);
	अगर (err)
		वापस err;

	i = 0;
	जबतक (1) अणु
		state = pcxhr_pipes_running(mgr);
		/* have all pipes the new state ? */
		अगर ((state & audio_mask) == (start ? audio_mask : 0))
			अवरोध;
		अगर (++i >= MAX_WAIT_FOR_DSP * 100) अणु
			dev_err(&mgr->pci->dev, "error pipe start/stop\n");
			वापस -EBUSY;
		पूर्ण
		udelay(10);			/* रुको 10 microseconds */
	पूर्ण
	अगर (!start) अणु
		err = pcxhr_stop_pipes(mgr, audio_mask);
		अगर (err)
			वापस err;
	पूर्ण
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	stop_समय = kसमय_get();
	dअगरf_समय = kसमय_sub(stop_समय, start_समय);
	dev_dbg(&mgr->pci->dev, "***SET PIPE STATE*** TIME = %ld (err = %x)\n",
			(दीर्घ)(kसमय_प्रकारo_ns(dअगरf_समय)), err);
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक pcxhr_ग_लिखो_io_num_reg_cont(काष्ठा pcxhr_mgr *mgr, अचिन्हित पूर्णांक mask,
				अचिन्हित पूर्णांक value, पूर्णांक *changed)
अणु
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err;

	mutex_lock(&mgr->msg_lock);
	अगर ((mgr->io_num_reg_cont & mask) == value) अणु
		dev_dbg(&mgr->pci->dev,
			"IO_NUM_REG_CONT mask %x already is set to %x\n",
			    mask, value);
		अगर (changed)
			*changed = 0;
		mutex_unlock(&mgr->msg_lock);
		वापस 0;	/* alपढ़ोy programmed */
	पूर्ण
	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
	rmh.cmd[0] |= IO_NUM_REG_CONT;
	rmh.cmd[1]  = mask;
	rmh.cmd[2]  = value;
	rmh.cmd_len = 3;
	err = pcxhr_send_msg_nolock(mgr, &rmh);
	अगर (err == 0) अणु
		mgr->io_num_reg_cont &= ~mask;
		mgr->io_num_reg_cont |= value;
		अगर (changed)
			*changed = 1;
	पूर्ण
	mutex_unlock(&mgr->msg_lock);
	वापस err;
पूर्ण

#घोषणा PCXHR_IRQ_TIMER		0x000300
#घोषणा PCXHR_IRQ_FREQ_CHANGE	0x000800
#घोषणा PCXHR_IRQ_TIME_CODE	0x001000
#घोषणा PCXHR_IRQ_NOTIFY	0x002000
#घोषणा PCXHR_IRQ_ASYNC		0x008000
#घोषणा PCXHR_IRQ_MASK		0x00bb00
#घोषणा PCXHR_FATAL_DSP_ERR	0xff0000

क्रमागत pcxhr_async_err_src अणु
	PCXHR_ERR_PIPE,
	PCXHR_ERR_STREAM,
	PCXHR_ERR_AUDIO
पूर्ण;

अटल पूर्णांक pcxhr_handle_async_err(काष्ठा pcxhr_mgr *mgr, u32 err,
				  क्रमागत pcxhr_async_err_src err_src, पूर्णांक pipe,
				  पूर्णांक is_capture)
अणु
	अटल स्थिर अक्षर * स्थिर err_src_name[] = अणु
		[PCXHR_ERR_PIPE]	= "Pipe",
		[PCXHR_ERR_STREAM]	= "Stream",
		[PCXHR_ERR_AUDIO]	= "Audio"
	पूर्ण;

	अगर (err & 0xfff)
		err &= 0xfff;
	अन्यथा
		err = ((err >> 12) & 0xfff);
	अगर (!err)
		वापस 0;
	dev_dbg(&mgr->pci->dev, "CMD_ASYNC : Error %s %s Pipe %d err=%x\n",
		    err_src_name[err_src],
		    is_capture ? "Record" : "Play", pipe, err);
	अगर (err == 0xe01)
		mgr->async_err_stream_xrun++;
	अन्यथा अगर (err == 0xe10)
		mgr->async_err_pipe_xrun++;
	अन्यथा
		mgr->async_err_other_last = (पूर्णांक)err;
	वापस 1;
पूर्ण


अटल व्योम pcxhr_msg_thपढ़ो(काष्ठा pcxhr_mgr *mgr)
अणु
	काष्ठा pcxhr_rmh *prmh = mgr->prmh;
	पूर्णांक err;
	पूर्णांक i, j;

	अगर (mgr->src_it_dsp & PCXHR_IRQ_FREQ_CHANGE)
		dev_dbg(&mgr->pci->dev,
			"PCXHR_IRQ_FREQ_CHANGE event occurred\n");
	अगर (mgr->src_it_dsp & PCXHR_IRQ_TIME_CODE)
		dev_dbg(&mgr->pci->dev,
			"PCXHR_IRQ_TIME_CODE event occurred\n");
	अगर (mgr->src_it_dsp & PCXHR_IRQ_NOTIFY)
		dev_dbg(&mgr->pci->dev,
			"PCXHR_IRQ_NOTIFY event occurred\n");
	अगर (mgr->src_it_dsp & (PCXHR_IRQ_FREQ_CHANGE | PCXHR_IRQ_TIME_CODE)) अणु
		/* clear events FREQ_CHANGE and TIME_CODE */
		pcxhr_init_rmh(prmh, CMD_TEST_IT);
		err = pcxhr_send_msg(mgr, prmh);
		dev_dbg(&mgr->pci->dev, "CMD_TEST_IT : err=%x, stat=%x\n",
			    err, prmh->stat[0]);
	पूर्ण
	अगर (mgr->src_it_dsp & PCXHR_IRQ_ASYNC) अणु
		dev_dbg(&mgr->pci->dev,
			"PCXHR_IRQ_ASYNC event occurred\n");

		pcxhr_init_rmh(prmh, CMD_ASYNC);
		prmh->cmd[0] |= 1;	/* add SEL_ASYNC_EVENTS */
		/* this is the only one extra दीर्घ response command */
		prmh->stat_len = PCXHR_SIZE_MAX_LONG_STATUS;
		err = pcxhr_send_msg(mgr, prmh);
		अगर (err)
			dev_err(&mgr->pci->dev, "ERROR pcxhr_msg_thread=%x;\n",
				   err);
		i = 1;
		जबतक (i < prmh->stat_len) अणु
			पूर्णांक nb_audio = ((prmh->stat[i] >> FIELD_SIZE) &
					MASK_FIRST_FIELD);
			पूर्णांक nb_stream = ((prmh->stat[i] >> (2*FIELD_SIZE)) &
					 MASK_FIRST_FIELD);
			पूर्णांक pipe = prmh->stat[i] & MASK_FIRST_FIELD;
			पूर्णांक is_capture = prmh->stat[i] & 0x400000;
			u32 err2;

			अगर (prmh->stat[i] & 0x800000) अणु	/* अगर BIT_END */
				dev_dbg(&mgr->pci->dev,
					"TASKLET : End%sPipe %d\n",
					    is_capture ? "Record" : "Play",
					    pipe);
			पूर्ण
			i++;
			err2 = prmh->stat[i] ? prmh->stat[i] : prmh->stat[i+1];
			अगर (err2)
				pcxhr_handle_async_err(mgr, err2,
						       PCXHR_ERR_PIPE,
						       pipe, is_capture);
			i += 2;
			क्रम (j = 0; j < nb_stream; j++) अणु
				err2 = prmh->stat[i] ?
					prmh->stat[i] : prmh->stat[i+1];
				अगर (err2)
					pcxhr_handle_async_err(mgr, err2,
							       PCXHR_ERR_STREAM,
							       pipe,
							       is_capture);
				i += 2;
			पूर्ण
			क्रम (j = 0; j < nb_audio; j++) अणु
				err2 = prmh->stat[i] ?
					prmh->stat[i] : prmh->stat[i+1];
				अगर (err2)
					pcxhr_handle_async_err(mgr, err2,
							       PCXHR_ERR_AUDIO,
							       pipe,
							       is_capture);
				i += 2;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल u_पूर्णांक64_t pcxhr_stream_पढ़ो_position(काष्ठा pcxhr_mgr *mgr,
					    काष्ठा pcxhr_stream *stream)
अणु
	u_पूर्णांक64_t hw_sample_count;
	काष्ठा pcxhr_rmh rmh;
	पूर्णांक err, stream_mask;

	stream_mask = stream->pipe->is_capture ? 1 : 1<<stream->substream->number;

	/* get sample count क्रम one stream */
	pcxhr_init_rmh(&rmh, CMD_STREAM_SAMPLE_COUNT);
	pcxhr_set_pipe_cmd_params(&rmh, stream->pipe->is_capture,
				  stream->pipe->first_audio, 0, stream_mask);
	/* rmh.stat_len = 2; */	/* 2 resp data क्रम each stream of the pipe */

	err = pcxhr_send_msg(mgr, &rmh);
	अगर (err)
		वापस 0;

	hw_sample_count = ((u_पूर्णांक64_t)rmh.stat[0]) << 24;
	hw_sample_count += (u_पूर्णांक64_t)rmh.stat[1];

	dev_dbg(&mgr->pci->dev,
		"stream %c%d : abs samples real(%llu) timer(%llu)\n",
		    stream->pipe->is_capture ? 'C' : 'P',
		    stream->substream->number,
		    hw_sample_count,
		    stream->समयr_असल_periods + stream->समयr_period_frag +
						mgr->granularity);
	वापस hw_sample_count;
पूर्ण

अटल व्योम pcxhr_update_समयr_pos(काष्ठा pcxhr_mgr *mgr,
				   काष्ठा pcxhr_stream *stream,
				   पूर्णांक samples_to_add)
अणु
	अगर (stream->substream &&
	    (stream->status == PCXHR_STREAM_STATUS_RUNNING)) अणु
		u_पूर्णांक64_t new_sample_count;
		पूर्णांक elapsed = 0;
		पूर्णांक hardware_पढ़ो = 0;
		काष्ठा snd_pcm_runसमय *runसमय = stream->substream->runसमय;

		अगर (samples_to_add < 0) अणु
			stream->समयr_is_synced = 0;
			/* add शेष अगर no hardware_पढ़ो possible */
			samples_to_add = mgr->granularity;
		पूर्ण

		अगर (!stream->समयr_is_synced) अणु
			अगर ((stream->समयr_असल_periods != 0) ||
			    ((stream->समयr_period_frag + samples_to_add) >=
			    runसमय->period_size)) अणु
				new_sample_count =
				  pcxhr_stream_पढ़ो_position(mgr, stream);
				hardware_पढ़ो = 1;
				अगर (new_sample_count >= mgr->granularity) अणु
					/* sub security offset because of
					 * jitter and finer granularity of
					 * dsp समय (MBOX4)
					 */
					new_sample_count -= mgr->granularity;
					stream->समयr_is_synced = 1;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!hardware_पढ़ो) अणु
			/* अगर we didn't try to sync the position, increment it
			 * by PCXHR_GRANULARITY every समयr पूर्णांकerrupt
			 */
			new_sample_count = stream->समयr_असल_periods +
				stream->समयr_period_frag + samples_to_add;
		पूर्ण
		जबतक (1) अणु
			u_पूर्णांक64_t new_elapse_pos = stream->समयr_असल_periods +
				runसमय->period_size;
			अगर (new_elapse_pos > new_sample_count)
				अवरोध;
			elapsed = 1;
			stream->समयr_buf_periods++;
			अगर (stream->समयr_buf_periods >= runसमय->periods)
				stream->समयr_buf_periods = 0;
			stream->समयr_असल_periods = new_elapse_pos;
		पूर्ण
		अगर (new_sample_count >= stream->समयr_असल_periods) अणु
			stream->समयr_period_frag =
				(u_पूर्णांक32_t)(new_sample_count -
					    stream->समयr_असल_periods);
		पूर्ण अन्यथा अणु
			dev_err(&mgr->pci->dev,
				   "ERROR new_sample_count too small ??? %ld\n",
				   (दीर्घ अचिन्हित पूर्णांक)new_sample_count);
		पूर्ण

		अगर (elapsed) अणु
			mutex_unlock(&mgr->lock);
			snd_pcm_period_elapsed(stream->substream);
			mutex_lock(&mgr->lock);
		पूर्ण
	पूर्ण
पूर्ण

irqवापस_t pcxhr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pcxhr_mgr *mgr = dev_id;
	अचिन्हित पूर्णांक reg;
	bool wake_thपढ़ो = false;

	reg = PCXHR_INPL(mgr, PCXHR_PLX_IRQCS);
	अगर (! (reg & PCXHR_IRQCS_ACTIVE_PCIDB)) अणु
		/* this device did not cause the पूर्णांकerrupt */
		वापस IRQ_NONE;
	पूर्ण

	/* clear पूर्णांकerrupt */
	reg = PCXHR_INPL(mgr, PCXHR_PLX_L2PCIDB);
	PCXHR_OUTPL(mgr, PCXHR_PLX_L2PCIDB, reg);

	/* समयr irq occurred */
	अगर (reg & PCXHR_IRQ_TIMER) अणु
		पूर्णांक समयr_toggle = reg & PCXHR_IRQ_TIMER;
		अगर (समयr_toggle == mgr->समयr_toggle) अणु
			dev_dbg(&mgr->pci->dev, "ERROR TIMER TOGGLE\n");
			mgr->dsp_समय_err++;
		पूर्ण

		mgr->समयr_toggle = समयr_toggle;
		mgr->src_it_dsp = reg;
		wake_thपढ़ो = true;
	पूर्ण

	/* other irq's handled in the thपढ़ो */
	अगर (reg & PCXHR_IRQ_MASK) अणु
		अगर (reg & PCXHR_IRQ_ASYNC) अणु
			/* as we didn't request any async notअगरications,
			 * some kind of xrun error will probably occurred
			 */
			/* better resynchronize all streams next पूर्णांकerrupt : */
			mgr->dsp_समय_last = PCXHR_DSP_TIME_INVALID;
		पूर्ण
		mgr->src_it_dsp = reg;
		wake_thपढ़ो = true;
	पूर्ण
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
	अगर (reg & PCXHR_FATAL_DSP_ERR)
		dev_dbg(&mgr->pci->dev, "FATAL DSP ERROR : %x\n", reg);
#पूर्ण_अगर

	वापस wake_thपढ़ो ? IRQ_WAKE_THREAD : IRQ_HANDLED;
पूर्ण

irqवापस_t pcxhr_thपढ़ोed_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pcxhr_mgr *mgr = dev_id;
	पूर्णांक i, j;
	काष्ठा snd_pcxhr *chip;

	mutex_lock(&mgr->lock);
	अगर (mgr->src_it_dsp & PCXHR_IRQ_TIMER) अणु
		/* is a 24 bit counter */
		पूर्णांक dsp_समय_new =
			PCXHR_INPL(mgr, PCXHR_PLX_MBOX4) & PCXHR_DSP_TIME_MASK;
		पूर्णांक dsp_समय_dअगरf = dsp_समय_new - mgr->dsp_समय_last;

		अगर ((dsp_समय_dअगरf < 0) &&
		    (mgr->dsp_समय_last != PCXHR_DSP_TIME_INVALID)) अणु
			/* handle dsp counter wraparound without resync */
			पूर्णांक पंचांगp_dअगरf = dsp_समय_dअगरf + PCXHR_DSP_TIME_MASK + 1;
			dev_dbg(&mgr->pci->dev,
				"WARNING DSP timestamp old(%d) new(%d)",
				    mgr->dsp_समय_last, dsp_समय_new);
			अगर (पंचांगp_dअगरf > 0 && पंचांगp_dअगरf <= (2*mgr->granularity)) अणु
				dev_dbg(&mgr->pci->dev,
					"-> timestamp wraparound OK: "
					    "diff=%d\n", पंचांगp_dअगरf);
				dsp_समय_dअगरf = पंचांगp_dअगरf;
			पूर्ण अन्यथा अणु
				dev_dbg(&mgr->pci->dev,
					"-> resynchronize all streams\n");
				mgr->dsp_समय_err++;
			पूर्ण
		पूर्ण
#अगर_घोषित CONFIG_SND_DEBUG_VERBOSE
		अगर (dsp_समय_dअगरf == 0)
			dev_dbg(&mgr->pci->dev,
				"ERROR DSP TIME NO DIFF time(%d)\n",
				    dsp_समय_new);
		अन्यथा अगर (dsp_समय_dअगरf >= (2*mgr->granularity))
			dev_dbg(&mgr->pci->dev,
				"ERROR DSP TIME TOO BIG old(%d) add(%d)\n",
				    mgr->dsp_समय_last,
				    dsp_समय_new - mgr->dsp_समय_last);
		अन्यथा अगर (dsp_समय_dअगरf % mgr->granularity)
			dev_dbg(&mgr->pci->dev,
				"ERROR DSP TIME increased by %d\n",
				    dsp_समय_dअगरf);
#पूर्ण_अगर
		mgr->dsp_समय_last = dsp_समय_new;

		क्रम (i = 0; i < mgr->num_cards; i++) अणु
			chip = mgr->chip[i];
			क्रम (j = 0; j < chip->nb_streams_capt; j++)
				pcxhr_update_समयr_pos(mgr,
						&chip->capture_stream[j],
						dsp_समय_dअगरf);
		पूर्ण
		क्रम (i = 0; i < mgr->num_cards; i++) अणु
			chip = mgr->chip[i];
			क्रम (j = 0; j < chip->nb_streams_play; j++)
				pcxhr_update_समयr_pos(mgr,
						&chip->playback_stream[j],
						dsp_समय_dअगरf);
		पूर्ण
	पूर्ण

	pcxhr_msg_thपढ़ो(mgr);
	mutex_unlock(&mgr->lock);
	वापस IRQ_HANDLED;
पूर्ण
