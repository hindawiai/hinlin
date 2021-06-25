<शैली गुरु>
/*
 * atari_scsi.c -- Device dependent functions क्रम the Atari generic SCSI port
 *
 * Copyright 1994 Roman Hodek <Roman.Hodek@inक्रमmatik.uni-erlangen.de>
 *
 *   Loosely based on the work of Robert De Vries' team and added:
 *    - working real DMA
 *    - Falcon support (untested yet!)   ++bjoern fixed and now it works
 *    - lots of extensions and bug fixes.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 */

/*
 * Notes क्रम Falcon SCSI DMA
 *
 * The 5380 device is one of several that all share the DMA chip. Hence
 * "locking" and "unlocking" access to this chip is required.
 *
 * Two possible schemes क्रम ST DMA acquisition by atari_scsi are:
 * 1) The lock is taken क्रम each command separately (i.e. can_queue == 1).
 * 2) The lock is taken when the first command arrives and released
 * when the last command is finished (i.e. can_queue > 1).
 *
 * The first alternative limits SCSI bus utilization, since पूर्णांकerleaving
 * commands is not possible. The second gives better perक्रमmance but is
 * unfair to other drivers needing to use the ST DMA chip. In order to
 * allow the IDE and floppy drivers equal access to the ST DMA chip
 * the शेष is can_queue == 1.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/nvram.h>
#समावेश <linux/bitops.h>
#समावेश <linux/रुको.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atari_stdma.h>
#समावेश <यंत्र/atari_stram.h>
#समावेश <यंत्र/पन.स>

#समावेश <scsi/scsi_host.h>

#घोषणा DMA_MIN_SIZE                    32

/* Definitions क्रम the core NCR5380 driver. */

#घोषणा NCR5380_implementation_fields   /* none */

अटल u8 (*atari_scsi_reg_पढ़ो)(अचिन्हित पूर्णांक);
अटल व्योम (*atari_scsi_reg_ग_लिखो)(अचिन्हित पूर्णांक, u8);

#घोषणा NCR5380_पढ़ो(reg)               atari_scsi_reg_पढ़ो(reg)
#घोषणा NCR5380_ग_लिखो(reg, value)       atari_scsi_reg_ग_लिखो(reg, value)

#घोषणा NCR5380_queue_command           atari_scsi_queue_command
#घोषणा NCR5380_पात                   atari_scsi_पात
#घोषणा NCR5380_info                    atari_scsi_info

#घोषणा NCR5380_dma_xfer_len            atari_scsi_dma_xfer_len
#घोषणा NCR5380_dma_recv_setup          atari_scsi_dma_recv_setup
#घोषणा NCR5380_dma_send_setup          atari_scsi_dma_send_setup
#घोषणा NCR5380_dma_residual            atari_scsi_dma_residual

#घोषणा NCR5380_acquire_dma_irq(instance)      falcon_get_lock(instance)
#घोषणा NCR5380_release_dma_irq(instance)      falcon_release_lock()

#समावेश "NCR5380.h"


#घोषणा	IS_A_TT()	ATARIHW_PRESENT(TT_SCSI)

#घोषणा	SCSI_DMA_WRITE_P(elt,val)				\
	करो अणु							\
		अचिन्हित दीर्घ v = val;				\
		tt_scsi_dma.elt##_lo = v & 0xff;		\
		v >>= 8;					\
		tt_scsi_dma.elt##_lmd = v & 0xff;		\
		v >>= 8;					\
		tt_scsi_dma.elt##_hmd = v & 0xff;		\
		v >>= 8;					\
		tt_scsi_dma.elt##_hi = v & 0xff;		\
	पूर्ण जबतक(0)

#घोषणा	SCSI_DMA_READ_P(elt)					\
	(((((((अचिन्हित दीर्घ)tt_scsi_dma.elt##_hi << 8) |	\
	     (अचिन्हित दीर्घ)tt_scsi_dma.elt##_hmd) << 8) |	\
	   (अचिन्हित दीर्घ)tt_scsi_dma.elt##_lmd) << 8) |	\
	 (अचिन्हित दीर्घ)tt_scsi_dma.elt##_lo)


अटल अंतरभूत व्योम SCSI_DMA_SETADR(अचिन्हित दीर्घ adr)
अणु
	st_dma.dma_lo = (अचिन्हित अक्षर)adr;
	MFPDELAY();
	adr >>= 8;
	st_dma.dma_md = (अचिन्हित अक्षर)adr;
	MFPDELAY();
	adr >>= 8;
	st_dma.dma_hi = (अचिन्हित अक्षर)adr;
	MFPDELAY();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ SCSI_DMA_GETADR(व्योम)
अणु
	अचिन्हित दीर्घ adr;
	adr = st_dma.dma_lo;
	MFPDELAY();
	adr |= (st_dma.dma_md & 0xff) << 8;
	MFPDELAY();
	adr |= (st_dma.dma_hi & 0xff) << 16;
	MFPDELAY();
	वापस adr;
पूर्ण

अटल व्योम atari_scsi_fetch_restbytes(व्योम);

अटल अचिन्हित दीर्घ	atari_dma_residual, atari_dma_startaddr;
अटल लघु		atari_dma_active;
/* poपूर्णांकer to the dribble buffer */
अटल अक्षर		*atari_dma_buffer;
/* precalculated physical address of the dribble buffer */
अटल अचिन्हित दीर्घ	atari_dma_phys_buffer;
/* != 0 tells the Falcon पूर्णांक handler to copy data from the dribble buffer */
अटल अक्षर		*atari_dma_orig_addr;
/* size of the dribble buffer; 4k seems enough, since the Falcon cannot use
 * scatter-gather anyway, so most transfers are 1024 byte only. In the rare
 * हालs where requests to physical contiguous buffers have been merged, this
 * request is <= 4k (one page). So I करोn't think we have to split transfers
 * just due to this buffer size...
 */
#घोषणा	STRAM_BUFFER_SIZE	(4096)
/* mask क्रम address bits that can't be used with the ST-DMA */
अटल अचिन्हित दीर्घ	atari_dma_stram_mask;
#घोषणा STRAM_ADDR(a)	(((a) & atari_dma_stram_mask) == 0)

अटल पूर्णांक setup_can_queue = -1;
module_param(setup_can_queue, पूर्णांक, 0);
अटल पूर्णांक setup_cmd_per_lun = -1;
module_param(setup_cmd_per_lun, पूर्णांक, 0);
अटल पूर्णांक setup_sg_tablesize = -1;
module_param(setup_sg_tablesize, पूर्णांक, 0);
अटल पूर्णांक setup_hostid = -1;
module_param(setup_hostid, पूर्णांक, 0);
अटल पूर्णांक setup_toshiba_delay = -1;
module_param(setup_toshiba_delay, पूर्णांक, 0);


अटल पूर्णांक scsi_dma_is_ignored_buserr(अचिन्हित अक्षर dma_stat)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ addr = SCSI_DMA_READ_P(dma_addr), end_addr;

	अगर (dma_stat & 0x01) अणु

		/* A bus error happens when DMA-ing from the last page of a
		 * physical memory chunk (DMA prefetch!), but that करोesn't hurt.
		 * Check क्रम this हाल:
		 */

		क्रम (i = 0; i < m68k_num_memory; ++i) अणु
			end_addr = m68k_memory[i].addr + m68k_memory[i].size;
			अगर (end_addr <= addr && addr <= end_addr + 4)
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल irqवापस_t scsi_tt_पूर्णांकr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा Scsi_Host *instance = dev;
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	पूर्णांक dma_stat;

	dma_stat = tt_scsi_dma.dma_ctrl;

	dsprपूर्णांकk(न_संशोधन_INTR, instance, "NCR5380 interrupt, DMA status = %02x\n",
	         dma_stat & 0xff);

	/* Look अगर it was the DMA that has पूर्णांकerrupted: First possibility
	 * is that a bus error occurred...
	 */
	अगर (dma_stat & 0x80) अणु
		अगर (!scsi_dma_is_ignored_buserr(dma_stat)) अणु
			prपूर्णांकk(KERN_ERR "SCSI DMA caused bus error near 0x%08lx\n",
			       SCSI_DMA_READ_P(dma_addr));
			prपूर्णांकk(KERN_CRIT "SCSI DMA bus error -- bad DMA programming!");
		पूर्ण
	पूर्ण

	/* If the DMA is active but not finished, we have the हाल
	 * that some other 5380 पूर्णांकerrupt occurred within the DMA transfer.
	 * This means we have residual bytes, अगर the desired end address
	 * is not yet reached. Maybe we have to fetch some bytes from the
	 * rest data रेजिस्टर, too. The residual must be calculated from
	 * the address poपूर्णांकer, not the counter रेजिस्टर, because only the
	 * addr reg counts bytes not yet written and pending in the rest
	 * data reg!
	 */
	अगर ((dma_stat & 0x02) && !(dma_stat & 0x40)) अणु
		atari_dma_residual = hostdata->dma_len -
			(SCSI_DMA_READ_P(dma_addr) - atari_dma_startaddr);

		dprपूर्णांकk(न_संशोधन_DMA, "SCSI DMA: There are %ld residual bytes.\n",
			   atari_dma_residual);

		अगर ((चिन्हित पूर्णांक)atari_dma_residual < 0)
			atari_dma_residual = 0;
		अगर ((dma_stat & 1) == 0) अणु
			/*
			 * After पढ़ो operations, we maybe have to
			 * transport some rest bytes
			 */
			atari_scsi_fetch_restbytes();
		पूर्ण अन्यथा अणु
			/*
			 * There seems to be a nasty bug in some SCSI-DMA/NCR
			 * combinations: If a target disconnects जबतक a ग_लिखो
			 * operation is going on, the address रेजिस्टर of the
			 * DMA may be a few bytes farer than it actually पढ़ो.
			 * This is probably due to DMA prefetching and a delay
			 * between DMA and NCR.  Experiments showed that the
			 * dma_addr is 9 bytes to high, but this could vary.
			 * The problem is, that the residual is thus calculated
			 * wrong and the next transfer will start behind where
			 * it should.  So we round up the residual to the next
			 * multiple of a sector size, अगर it isn't alपढ़ोy a
			 * multiple and the originally expected transfer size
			 * was.  The latter condition is there to ensure that
			 * the correction is taken only क्रम "real" data
			 * transfers and not क्रम, e.g., the parameters of some
			 * other command.  These shouldn't disconnect anyway.
			 */
			अगर (atari_dma_residual & 0x1ff) अणु
				dprपूर्णांकk(न_संशोधन_DMA, "SCSI DMA: DMA bug corrected, "
					   "difference %ld bytes\n",
					   512 - (atari_dma_residual & 0x1ff));
				atari_dma_residual = (atari_dma_residual + 511) & ~0x1ff;
			पूर्ण
		पूर्ण
		tt_scsi_dma.dma_ctrl = 0;
	पूर्ण

	/* If the DMA is finished, fetch the rest bytes and turn it off */
	अगर (dma_stat & 0x40) अणु
		atari_dma_residual = 0;
		अगर ((dma_stat & 1) == 0)
			atari_scsi_fetch_restbytes();
		tt_scsi_dma.dma_ctrl = 0;
	पूर्ण

	NCR5380_पूर्णांकr(irq, dev);

	वापस IRQ_HANDLED;
पूर्ण


अटल irqवापस_t scsi_falcon_पूर्णांकr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा Scsi_Host *instance = dev;
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	पूर्णांक dma_stat;

	/* Turn off DMA and select sector counter रेजिस्टर beक्रमe
	 * accessing the status रेजिस्टर (Atari recommendation!)
	 */
	st_dma.dma_mode_status = 0x90;
	dma_stat = st_dma.dma_mode_status;

	/* Bit 0 indicates some error in the DMA process... करोn't know
	 * what happened exactly (no further करोcu).
	 */
	अगर (!(dma_stat & 0x01)) अणु
		/* DMA error */
		prपूर्णांकk(KERN_CRIT "SCSI DMA error near 0x%08lx!\n", SCSI_DMA_GETADR());
	पूर्ण

	/* If the DMA was active, but now bit 1 is not clear, it is some
	 * other 5380 पूर्णांकerrupt that finishes the DMA transfer. We have to
	 * calculate the number of residual bytes and give a warning अगर
	 * bytes are stuck in the ST-DMA fअगरo (there's no way to reach them!)
	 */
	अगर (atari_dma_active && (dma_stat & 0x02)) अणु
		अचिन्हित दीर्घ transferred;

		transferred = SCSI_DMA_GETADR() - atari_dma_startaddr;
		/* The ST-DMA address is incremented in 2-byte steps, but the
		 * data are written only in 16-byte chunks. If the number of
		 * transferred bytes is not भागisible by 16, the reमुख्यder is
		 * lost somewhere in outer space.
		 */
		अगर (transferred & 15)
			prपूर्णांकk(KERN_ERR "SCSI DMA error: %ld bytes lost in "
			       "ST-DMA fifo\n", transferred & 15);

		atari_dma_residual = hostdata->dma_len - transferred;
		dprपूर्णांकk(न_संशोधन_DMA, "SCSI DMA: There are %ld residual bytes.\n",
			   atari_dma_residual);
	पूर्ण अन्यथा
		atari_dma_residual = 0;
	atari_dma_active = 0;

	अगर (atari_dma_orig_addr) अणु
		/* If the dribble buffer was used on a पढ़ो operation, copy the DMA-ed
		 * data to the original destination address.
		 */
		स_नकल(atari_dma_orig_addr, phys_to_virt(atari_dma_startaddr),
		       hostdata->dma_len - atari_dma_residual);
		atari_dma_orig_addr = शून्य;
	पूर्ण

	NCR5380_पूर्णांकr(irq, dev);

	वापस IRQ_HANDLED;
पूर्ण


अटल व्योम atari_scsi_fetch_restbytes(व्योम)
अणु
	पूर्णांक nr;
	अक्षर *src, *dst;
	अचिन्हित दीर्घ phys_dst;

	/* fetch rest bytes in the DMA रेजिस्टर */
	phys_dst = SCSI_DMA_READ_P(dma_addr);
	nr = phys_dst & 3;
	अगर (nr) अणु
		/* there are 'nr' bytes left क्रम the last दीर्घ address
		   beक्रमe the DMA poपूर्णांकer */
		phys_dst ^= nr;
		dprपूर्णांकk(न_संशोधन_DMA, "SCSI DMA: there are %d rest bytes for phys addr 0x%08lx",
			   nr, phys_dst);
		/* The content of the DMA poपूर्णांकer is a physical address!  */
		dst = phys_to_virt(phys_dst);
		dprपूर्णांकk(न_संशोधन_DMA, " = virt addr %p\n", dst);
		क्रम (src = (अक्षर *)&tt_scsi_dma.dma_restdata; nr != 0; --nr)
			*dst++ = *src++;
	पूर्ण
पूर्ण


/* This function releases the lock on the DMA chip अगर there is no
 * connected command and the disconnected queue is empty.
 */

अटल व्योम falcon_release_lock(व्योम)
अणु
	अगर (IS_A_TT())
		वापस;

	अगर (stdma_is_locked_by(scsi_falcon_पूर्णांकr))
		stdma_release();
पूर्ण

/* This function manages the locking of the ST-DMA.
 * If the DMA isn't locked alपढ़ोy क्रम SCSI, it tries to lock it by
 * calling stdma_lock(). But अगर the DMA is locked by the SCSI code and
 * there are other drivers रुकोing क्रम the chip, we करो not issue the
 * command immediately but tell the SCSI mid-layer to defer.
 */

अटल पूर्णांक falcon_get_lock(काष्ठा Scsi_Host *instance)
अणु
	अगर (IS_A_TT())
		वापस 1;

	अगर (stdma_is_locked_by(scsi_falcon_पूर्णांकr))
		वापस 1;

	/* stdma_lock() may sleep which means it can't be used here */
	वापस stdma_try_lock(scsi_falcon_पूर्णांकr, instance);
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init atari_scsi_setup(अक्षर *str)
अणु
	/* Format of atascsi parameter is:
	 *   atascsi=<can_queue>,<cmd_per_lun>,<sg_tablesize>,<hostid>,<use_tags>
	 * Defaults depend on TT or Falcon, determined at run समय.
	 * Negative values mean करोn't change.
	 */
	पूर्णांक पूर्णांकs[8];

	get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	अगर (पूर्णांकs[0] < 1) अणु
		prपूर्णांकk("atari_scsi_setup: no arguments!\n");
		वापस 0;
	पूर्ण
	अगर (पूर्णांकs[0] >= 1)
		setup_can_queue = पूर्णांकs[1];
	अगर (पूर्णांकs[0] >= 2)
		setup_cmd_per_lun = पूर्णांकs[2];
	अगर (पूर्णांकs[0] >= 3)
		setup_sg_tablesize = पूर्णांकs[3];
	अगर (पूर्णांकs[0] >= 4)
		setup_hostid = पूर्णांकs[4];
	/* पूर्णांकs[5] (use_tagged_queuing) is ignored */
	/* पूर्णांकs[6] (use_pdma) is ignored */
	अगर (पूर्णांकs[0] >= 7)
		setup_toshiba_delay = पूर्णांकs[7];

	वापस 1;
पूर्ण

__setup("atascsi=", atari_scsi_setup);
#पूर्ण_अगर /* !MODULE */

अटल अचिन्हित दीर्घ atari_scsi_dma_setup(काष्ठा NCR5380_hostdata *hostdata,
					  व्योम *data, अचिन्हित दीर्घ count,
					  पूर्णांक dir)
अणु
	अचिन्हित दीर्घ addr = virt_to_phys(data);

	dprपूर्णांकk(न_संशोधन_DMA, "scsi%d: setting up dma, data = %p, phys = %lx, count = %ld, dir = %d\n",
	        hostdata->host->host_no, data, addr, count, dir);

	अगर (!IS_A_TT() && !STRAM_ADDR(addr)) अणु
		/* If we have a non-DMAable address on a Falcon, use the dribble
		 * buffer; 'orig_addr' != 0 in the पढ़ो हाल tells the पूर्णांकerrupt
		 * handler to copy data from the dribble buffer to the originally
		 * wanted address.
		 */
		अगर (dir)
			स_नकल(atari_dma_buffer, data, count);
		अन्यथा
			atari_dma_orig_addr = data;
		addr = atari_dma_phys_buffer;
	पूर्ण

	atari_dma_startaddr = addr;	/* Needed क्रम calculating residual later. */

	/* Cache cleanup stuff: On ग_लिखोs, push any dirty cache out beक्रमe sending
	 * it to the peripheral. (Must be करोne beक्रमe DMA setup, since at least
	 * the ST-DMA begins to fill पूर्णांकernal buffers right after setup. For
	 * पढ़ोs, invalidate any cache, may be altered after DMA without CPU
	 * knowledge.
	 *
	 * ++roman: For the Medusa, there's no need at all क्रम that cache stuff,
	 * because the hardware करोes bus snooping (fine!).
	 */
	dma_cache_मुख्यtenance(addr, count, dir);

	अगर (IS_A_TT()) अणु
		tt_scsi_dma.dma_ctrl = dir;
		SCSI_DMA_WRITE_P(dma_addr, addr);
		SCSI_DMA_WRITE_P(dma_cnt, count);
		tt_scsi_dma.dma_ctrl = dir | 2;
	पूर्ण अन्यथा अणु /* ! IS_A_TT */

		/* set address */
		SCSI_DMA_SETADR(addr);

		/* toggle direction bit to clear FIFO and set DMA direction */
		dir <<= 8;
		st_dma.dma_mode_status = 0x90 | dir;
		st_dma.dma_mode_status = 0x90 | (dir ^ 0x100);
		st_dma.dma_mode_status = 0x90 | dir;
		udelay(40);
		/* On ग_लिखोs, round up the transfer length to the next multiple of 512
		 * (see also comment at atari_dma_xfer_len()). */
		st_dma.fdc_acces_seccount = (count + (dir ? 511 : 0)) >> 9;
		udelay(40);
		st_dma.dma_mode_status = 0x10 | dir;
		udelay(40);
		/* need not restore value of dir, only boolean value is tested */
		atari_dma_active = 1;
	पूर्ण

	वापस count;
पूर्ण

अटल अंतरभूत पूर्णांक atari_scsi_dma_recv_setup(काष्ठा NCR5380_hostdata *hostdata,
                                            अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	वापस atari_scsi_dma_setup(hostdata, data, count, 0);
पूर्ण

अटल अंतरभूत पूर्णांक atari_scsi_dma_send_setup(काष्ठा NCR5380_hostdata *hostdata,
                                            अचिन्हित अक्षर *data, पूर्णांक count)
अणु
	वापस atari_scsi_dma_setup(hostdata, data, count, 1);
पूर्ण

अटल पूर्णांक atari_scsi_dma_residual(काष्ठा NCR5380_hostdata *hostdata)
अणु
	वापस atari_dma_residual;
पूर्ण


#घोषणा	CMD_SURELY_BLOCK_MODE	0
#घोषणा	CMD_SURELY_BYTE_MODE	1
#घोषणा	CMD_MODE_UNKNOWN		2

अटल पूर्णांक falcon_classअगरy_cmd(काष्ठा scsi_cmnd *cmd)
अणु
	अचिन्हित अक्षर opcode = cmd->cmnd[0];

	अगर (opcode == READ_DEFECT_DATA || opcode == READ_LONG ||
	    opcode == READ_BUFFER)
		वापस CMD_SURELY_BYTE_MODE;
	अन्यथा अगर (opcode == READ_6 || opcode == READ_10 ||
		 opcode == 0xa8 /* READ_12 */ || opcode == READ_REVERSE ||
		 opcode == RECOVER_BUFFERED_DATA) अणु
		/* In हाल of a sequential-access target (tape), special care is
		 * needed here: The transfer is block-mode only अगर the 'fixed' bit is
		 * set! */
		अगर (cmd->device->type == TYPE_TAPE && !(cmd->cmnd[1] & 1))
			वापस CMD_SURELY_BYTE_MODE;
		अन्यथा
			वापस CMD_SURELY_BLOCK_MODE;
	पूर्ण अन्यथा
		वापस CMD_MODE_UNKNOWN;
पूर्ण


/* This function calculates the number of bytes that can be transferred via
 * DMA. On the TT, this is arbitrary, but on the Falcon we have to use the
 * ST-DMA chip. There are only multiples of 512 bytes possible and max.
 * 255*512 bytes :-( This means also, that defining READ_OVERRUNS is not
 * possible on the Falcon, since that would require to program the DMA क्रम
 * n*512 - atari_पढ़ो_overrun bytes. But it seems that the Falcon करोesn't have
 * the overrun problem, so this question is academic :-)
 */

अटल पूर्णांक atari_scsi_dma_xfer_len(काष्ठा NCR5380_hostdata *hostdata,
                                   काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक wanted_len = cmd->SCp.this_residual;
	पूर्णांक possible_len, limit;

	अगर (wanted_len < DMA_MIN_SIZE)
		वापस 0;

	अगर (IS_A_TT())
		/* TT SCSI DMA can transfer arbitrary #bytes */
		वापस wanted_len;

	/* ST DMA chip is stupid -- only multiples of 512 bytes! (and max.
	 * 255*512 bytes, but this should be enough)
	 *
	 * ++roman: Aaargl! Another Falcon-SCSI problem... There are some commands
	 * that वापस a number of bytes which cannot be known beक्रमehand. In this
	 * हाल, the given transfer length is an "allocation length". Now it
	 * can happen that this allocation length is a multiple of 512 bytes and
	 * the DMA is used. But अगर not n*512 bytes really arrive, some input data
	 * will be lost in the ST-DMA's FIFO :-( Thus, we have to distinguish
	 * between commands that करो block transfers and those that करो byte
	 * transfers. But this isn't easy... there are lots of venकरोr specअगरic
	 * commands, and the user can issue any command via the
	 * SCSI_IOCTL_SEND_COMMAND.
	 *
	 * The solution: We classअगरy SCSI commands in 1) surely block-mode cmd.s,
	 * 2) surely byte-mode cmd.s and 3) cmd.s with unknown mode. In हाल 1)
	 * and 3), the thing to करो is obvious: allow any number of blocks via DMA
	 * or none. In हाल 2), we apply some heuristic: Byte mode is assumed अगर
	 * the transfer (allocation) length is < 1024, hoping that no cmd. not
	 * explicitly known as byte mode have such big allocation lengths...
	 * BTW, all the discussion above applies only to पढ़ोs. DMA ग_लिखोs are
	 * unproblematic anyways, since the tarमाला_लो पातs the transfer after
	 * receiving a sufficient number of bytes.
	 *
	 * Another poपूर्णांक: If the transfer is from/to an non-ST-RAM address, we
	 * use the dribble buffer and thus can करो only STRAM_BUFFER_SIZE bytes.
	 */

	अगर (cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		/* Write operation can always use the DMA, but the transfer size must
		 * be rounded up to the next multiple of 512 (atari_dma_setup() करोes
		 * this).
		 */
		possible_len = wanted_len;
	पूर्ण अन्यथा अणु
		/* Read operations: अगर the wanted transfer length is not a multiple of
		 * 512, we cannot use DMA, since the ST-DMA cannot split transfers
		 * (no पूर्णांकerrupt on DMA finished!)
		 */
		अगर (wanted_len & 0x1ff)
			possible_len = 0;
		अन्यथा अणु
			/* Now classअगरy the command (see above) and decide whether it is
			 * allowed to करो DMA at all */
			चयन (falcon_classअगरy_cmd(cmd)) अणु
			हाल CMD_SURELY_BLOCK_MODE:
				possible_len = wanted_len;
				अवरोध;
			हाल CMD_SURELY_BYTE_MODE:
				possible_len = 0; /* DMA prohibited */
				अवरोध;
			हाल CMD_MODE_UNKNOWN:
			शेष:
				/* For unknown commands assume block transfers अगर the transfer
				 * size/allocation length is >= 1024 */
				possible_len = (wanted_len < 1024) ? 0 : wanted_len;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Last step: apply the hard limit on DMA transfers */
	limit = (atari_dma_buffer && !STRAM_ADDR(virt_to_phys(cmd->SCp.ptr))) ?
		    STRAM_BUFFER_SIZE : 255*512;
	अगर (possible_len > limit)
		possible_len = limit;

	अगर (possible_len != wanted_len)
		dprपूर्णांकk(न_संशोधन_DMA, "DMA transfer now %d bytes instead of %d\n",
		        possible_len, wanted_len);

	वापस possible_len;
पूर्ण


/* NCR5380 रेजिस्टर access functions
 *
 * There are separate functions क्रम TT and Falcon, because the access
 * methods are quite dअगरferent. The calling macros NCR5380_पढ़ो and
 * NCR5380_ग_लिखो call these functions via function poपूर्णांकers.
 */

अटल u8 atari_scsi_tt_reg_पढ़ो(अचिन्हित पूर्णांक reg)
अणु
	वापस tt_scsi_regp[reg * 2];
पूर्ण

अटल व्योम atari_scsi_tt_reg_ग_लिखो(अचिन्हित पूर्णांक reg, u8 value)
अणु
	tt_scsi_regp[reg * 2] = value;
पूर्ण

अटल u8 atari_scsi_falcon_reg_पढ़ो(अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;
	u8 result;

	reg += 0x88;
	local_irq_save(flags);
	dma_wd.dma_mode_status = (u_लघु)reg;
	result = (u8)dma_wd.fdc_acces_seccount;
	local_irq_restore(flags);
	वापस result;
पूर्ण

अटल व्योम atari_scsi_falcon_reg_ग_लिखो(अचिन्हित पूर्णांक reg, u8 value)
अणु
	अचिन्हित दीर्घ flags;

	reg += 0x88;
	local_irq_save(flags);
	dma_wd.dma_mode_status = (u_लघु)reg;
	dma_wd.fdc_acces_seccount = (u_लघु)value;
	local_irq_restore(flags);
पूर्ण


#समावेश "NCR5380.c"

अटल पूर्णांक atari_scsi_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक rv;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* Abort a maybe active DMA transfer */
	अगर (IS_A_TT()) अणु
		tt_scsi_dma.dma_ctrl = 0;
	पूर्ण अन्यथा अणु
		अगर (stdma_is_locked_by(scsi_falcon_पूर्णांकr))
			st_dma.dma_mode_status = 0x90;
		atari_dma_active = 0;
		atari_dma_orig_addr = शून्य;
	पूर्ण

	rv = NCR5380_host_reset(cmd);

	/* The 5380 उठाओs its IRQ line जबतक _RST is active but the ST DMA
	 * "lock" has been released so this पूर्णांकerrupt may end up handled by
	 * floppy or IDE driver (अगर one of them holds the lock). The NCR5380
	 * पूर्णांकerrupt flag has been cleared alपढ़ोy.
	 */

	local_irq_restore(flags);

	वापस rv;
पूर्ण

#घोषणा DRV_MODULE_NAME         "atari_scsi"
#घोषणा PFX                     DRV_MODULE_NAME ": "

अटल काष्ठा scsi_host_ढाँचा atari_scsi_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= DRV_MODULE_NAME,
	.name			= "Atari native SCSI",
	.info			= atari_scsi_info,
	.queuecommand		= atari_scsi_queue_command,
	.eh_पात_handler	= atari_scsi_पात,
	.eh_host_reset_handler	= atari_scsi_host_reset,
	.this_id		= 7,
	.cmd_per_lun		= 2,
	.dma_boundary		= PAGE_SIZE - 1,
	.cmd_size		= NCR5380_CMD_SIZE,
पूर्ण;

अटल पूर्णांक __init atari_scsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा Scsi_Host *instance;
	पूर्णांक error;
	काष्ठा resource *irq;
	पूर्णांक host_flags = 0;

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!irq)
		वापस -ENODEV;

	अगर (ATARIHW_PRESENT(TT_SCSI)) अणु
		atari_scsi_reg_पढ़ो  = atari_scsi_tt_reg_पढ़ो;
		atari_scsi_reg_ग_लिखो = atari_scsi_tt_reg_ग_लिखो;
	पूर्ण अन्यथा अणु
		atari_scsi_reg_पढ़ो  = atari_scsi_falcon_reg_पढ़ो;
		atari_scsi_reg_ग_लिखो = atari_scsi_falcon_reg_ग_लिखो;
	पूर्ण

	अगर (ATARIHW_PRESENT(TT_SCSI)) अणु
		atari_scsi_ढाँचा.can_queue    = 16;
		atari_scsi_ढाँचा.sg_tablesize = SG_ALL;
	पूर्ण अन्यथा अणु
		atari_scsi_ढाँचा.can_queue    = 1;
		atari_scsi_ढाँचा.sg_tablesize = 1;
	पूर्ण

	अगर (setup_can_queue > 0)
		atari_scsi_ढाँचा.can_queue = setup_can_queue;

	अगर (setup_cmd_per_lun > 0)
		atari_scsi_ढाँचा.cmd_per_lun = setup_cmd_per_lun;

	/* Don't increase sg_tablesize on Falcon! */
	अगर (ATARIHW_PRESENT(TT_SCSI) && setup_sg_tablesize > 0)
		atari_scsi_ढाँचा.sg_tablesize = setup_sg_tablesize;

	अगर (setup_hostid >= 0) अणु
		atari_scsi_ढाँचा.this_id = setup_hostid & 7;
	पूर्ण अन्यथा अगर (IS_REACHABLE(CONFIG_NVRAM)) अणु
		/* Test अगर a host id is set in the NVRam */
		अगर (ATARIHW_PRESENT(TT_CLK)) अणु
			अचिन्हित अक्षर b;
			loff_t offset = 16;
			sमाप_प्रकार count = nvram_पढ़ो(&b, 1, &offset);

			/* Arbitration enabled? (क्रम TOS)
			 * If yes, use configured host ID
			 */
			अगर ((count == 1) && (b & 0x80))
				atari_scsi_ढाँचा.this_id = b & 7;
		पूर्ण
	पूर्ण

	/* If running on a Falcon and अगर there's TT-Ram (i.e., more than one
	 * memory block, since there's always ST-Ram in a Falcon), then
	 * allocate a STRAM_BUFFER_SIZE byte dribble buffer क्रम transfers
	 * from/to alternative Ram.
	 */
	अगर (ATARIHW_PRESENT(ST_SCSI) && !ATARIHW_PRESENT(EXTD_DMA) &&
	    m68k_realnum_memory > 1) अणु
		atari_dma_buffer = atari_stram_alloc(STRAM_BUFFER_SIZE, "SCSI");
		अगर (!atari_dma_buffer) अणु
			pr_err(PFX "can't allocate ST-RAM double buffer\n");
			वापस -ENOMEM;
		पूर्ण
		atari_dma_phys_buffer = atari_stram_to_phys(atari_dma_buffer);
		atari_dma_orig_addr = शून्य;
	पूर्ण

	instance = scsi_host_alloc(&atari_scsi_ढाँचा,
	                           माप(काष्ठा NCR5380_hostdata));
	अगर (!instance) अणु
		error = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	instance->irq = irq->start;

	host_flags |= IS_A_TT() ? 0 : FLAG_LATE_DMA_SETUP;
	host_flags |= setup_toshiba_delay > 0 ? FLAG_TOSHIBA_DELAY : 0;

	error = NCR5380_init(instance, host_flags);
	अगर (error)
		जाओ fail_init;

	अगर (IS_A_TT()) अणु
		error = request_irq(instance->irq, scsi_tt_पूर्णांकr, 0,
		                    "NCR5380", instance);
		अगर (error) अणु
			pr_err(PFX "request irq %d failed, aborting\n",
			       instance->irq);
			जाओ fail_irq;
		पूर्ण
		tt_mfp.active_edge |= 0x80;	/* SCSI पूर्णांक on L->H */

		tt_scsi_dma.dma_ctrl = 0;
		atari_dma_residual = 0;

		/* While the पढ़ो overruns (described by Drew Eckhardt in
		 * NCR5380.c) never happened on TTs, they करो in fact on the
		 * Medusa (This was the cause why SCSI didn't work right क्रम
		 * so दीर्घ there.) Since handling the overruns slows करोwn
		 * a bit, I turned the #अगर_घोषित's पूर्णांकo a runसमय condition.
		 *
		 * In principle it should be sufficient to करो max. 1 byte with
		 * PIO, but there is another problem on the Medusa with the DMA
		 * rest data रेजिस्टर. So पढ़ो_overruns is currently set
		 * to 4 to aव्योम having transfers that aren't a multiple of 4.
		 * If the rest data bug is fixed, this can be lowered to 1.
		 */
		अगर (MACH_IS_MEDUSA) अणु
			काष्ठा NCR5380_hostdata *hostdata =
				shost_priv(instance);

			hostdata->पढ़ो_overruns = 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Nothing to करो क्रम the पूर्णांकerrupt: the ST-DMA is initialized
		 * alपढ़ोy.
		 */
		atari_dma_residual = 0;
		atari_dma_active = 0;
		atari_dma_stram_mask = (ATARIHW_PRESENT(EXTD_DMA) ? 0x00000000
					: 0xff000000);
	पूर्ण

	NCR5380_maybe_reset_bus(instance);

	error = scsi_add_host(instance, शून्य);
	अगर (error)
		जाओ fail_host;

	platक्रमm_set_drvdata(pdev, instance);

	scsi_scan_host(instance);
	वापस 0;

fail_host:
	अगर (IS_A_TT())
		मुक्त_irq(instance->irq, instance);
fail_irq:
	NCR5380_निकास(instance);
fail_init:
	scsi_host_put(instance);
fail_alloc:
	अगर (atari_dma_buffer)
		atari_stram_मुक्त(atari_dma_buffer);
	वापस error;
पूर्ण

अटल पूर्णांक __निकास atari_scsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा Scsi_Host *instance = platक्रमm_get_drvdata(pdev);

	scsi_हटाओ_host(instance);
	अगर (IS_A_TT())
		मुक्त_irq(instance->irq, instance);
	NCR5380_निकास(instance);
	scsi_host_put(instance);
	अगर (atari_dma_buffer)
		atari_stram_मुक्त(atari_dma_buffer);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver atari_scsi_driver = अणु
	.हटाओ = __निकास_p(atari_scsi_हटाओ),
	.driver = अणु
		.name	= DRV_MODULE_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(atari_scsi_driver, atari_scsi_probe);

MODULE_ALIAS("platform:" DRV_MODULE_NAME);
MODULE_LICENSE("GPL");
