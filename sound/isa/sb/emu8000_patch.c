<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Patch routines क्रम the emu8000 (AWE32/64)
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (C) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "emu8000_local.h"

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/moduleparam.h>

अटल पूर्णांक emu8000_reset_addr;
module_param(emu8000_reset_addr, पूर्णांक, 0444);
MODULE_PARM_DESC(emu8000_reset_addr, "reset write address at each time (makes slowdown)");


/*
 * Open up channels.
 */
अटल पूर्णांक
snd_emu8000_खोलो_dma(काष्ठा snd_emu8000 *emu, पूर्णांक ग_लिखो)
अणु
	पूर्णांक i;

	/* reserve all 30 voices क्रम loading */
	क्रम (i = 0; i < EMU8000_DRAM_VOICES; i++) अणु
		snd_emux_lock_voice(emu->emu, i);
		snd_emu8000_dma_chan(emu, i, ग_लिखो);
	पूर्ण

	/* assign voice 31 and 32 to ROM */
	EMU8000_VTFT_WRITE(emu, 30, 0);
	EMU8000_PSST_WRITE(emu, 30, 0x1d8);
	EMU8000_CSL_WRITE(emu, 30, 0x1e0);
	EMU8000_CCCA_WRITE(emu, 30, 0x1d8);
	EMU8000_VTFT_WRITE(emu, 31, 0);
	EMU8000_PSST_WRITE(emu, 31, 0x1d8);
	EMU8000_CSL_WRITE(emu, 31, 0x1e0);
	EMU8000_CCCA_WRITE(emu, 31, 0x1d8);

	वापस 0;
पूर्ण

/*
 * Close all dram channels.
 */
अटल व्योम
snd_emu8000_बंद_dma(काष्ठा snd_emu8000 *emu)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < EMU8000_DRAM_VOICES; i++) अणु
		snd_emu8000_dma_chan(emu, i, EMU8000_RAM_CLOSE);
		snd_emux_unlock_voice(emu->emu, i);
	पूर्ण
पूर्ण

/*
 */

#घोषणा BLANK_LOOP_START	4
#घोषणा BLANK_LOOP_END		8
#घोषणा BLANK_LOOP_SIZE		12
#घोषणा BLANK_HEAD_SIZE		48

/*
 * Read a word from userland, taking care of conversions from
 * 8bit samples etc.
 */
अटल अचिन्हित लघु
पढ़ो_word(स्थिर व्योम __user *buf, पूर्णांक offset, पूर्णांक mode)
अणु
	अचिन्हित लघु c;
	अगर (mode & SNDRV_SFNT_SAMPLE_8BITS) अणु
		अचिन्हित अक्षर cc;
		get_user(cc, (अचिन्हित अक्षर __user *)buf + offset);
		c = cc << 8; /* convert 8bit -> 16bit */
	पूर्ण अन्यथा अणु
#अगर_घोषित SNDRV_LITTLE_ENDIAN
		get_user(c, (अचिन्हित लघु __user *)buf + offset);
#अन्यथा
		अचिन्हित लघु cc;
		get_user(cc, (अचिन्हित लघु __user *)buf + offset);
		c = swab16(cc);
#पूर्ण_अगर
	पूर्ण
	अगर (mode & SNDRV_SFNT_SAMPLE_UNSIGNED)
		c ^= 0x8000; /* अचिन्हित -> चिन्हित */
	वापस c;
पूर्ण

/*
 */
अटल व्योम
snd_emu8000_ग_लिखो_रुको(काष्ठा snd_emu8000 *emu)
अणु
	जबतक ((EMU8000_SMALW_READ(emu) & 0x80000000) != 0) अणु
		schedule_समयout_पूर्णांकerruptible(1);
		अगर (संकेत_pending(current))
			अवरोध;
	पूर्ण
पूर्ण

/*
 * ग_लिखो sample word data
 *
 * You should not have to keep resetting the address each समय
 * as the chip is supposed to step on the next address स्वतःmatically.
 * It mostly करोes, but during ग_लिखोs of some samples at अक्रमom it
 * completely loses words (every one in 16 roughly but with no
 * obvious pattern).
 *
 * This is thereक्रमe much slower than need be, but is at least
 * working.
 */
अटल अंतरभूत व्योम
ग_लिखो_word(काष्ठा snd_emu8000 *emu, पूर्णांक *offset, अचिन्हित लघु data)
अणु
	अगर (emu8000_reset_addr) अणु
		अगर (emu8000_reset_addr > 1)
			snd_emu8000_ग_लिखो_रुको(emu);
		EMU8000_SMALW_WRITE(emu, *offset);
	पूर्ण
	EMU8000_SMLD_WRITE(emu, data);
	*offset += 1;
पूर्ण

/*
 * Write the sample to EMU800 memory.  This routine is invoked out of
 * the generic soundfont routines as a callback.
 */
पूर्णांक
snd_emu8000_sample_new(काष्ठा snd_emux *rec, काष्ठा snd_sf_sample *sp,
		       काष्ठा snd_util_memhdr *hdr,
		       स्थिर व्योम __user *data, दीर्घ count)
अणु
	पूर्णांक  i;
	पूर्णांक  rc;
	पूर्णांक  offset;
	पूर्णांक  truesize;
	पूर्णांक  dram_offset, dram_start;
	काष्ठा snd_emu8000 *emu;

	emu = rec->hw;
	अगर (snd_BUG_ON(!sp))
		वापस -EINVAL;

	अगर (sp->v.size == 0)
		वापस 0;

	/* be sure loop poपूर्णांकs start < end */
	अगर (sp->v.loopstart > sp->v.loखोलोd)
		swap(sp->v.loopstart, sp->v.loखोलोd);

	/* compute true data size to be loaded */
	truesize = sp->v.size;
	अगर (sp->v.mode_flags & (SNDRV_SFNT_SAMPLE_BIसूची_LOOP|SNDRV_SFNT_SAMPLE_REVERSE_LOOP))
		truesize += sp->v.loखोलोd - sp->v.loopstart;
	अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_NO_BLANK)
		truesize += BLANK_LOOP_SIZE;

	sp->block = snd_util_mem_alloc(hdr, truesize * 2);
	अगर (sp->block == शून्य) अणु
		/*snd_prपूर्णांकd("EMU8000: out of memory\n");*/
		/* not ENOMEM (क्रम compatibility) */
		वापस -ENOSPC;
	पूर्ण

	अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_8BITS) अणु
		अगर (!access_ok(data, sp->v.size))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (!access_ok(data, sp->v.size * 2))
			वापस -EFAULT;
	पूर्ण

	/* recalculate address offset */
	sp->v.end -= sp->v.start;
	sp->v.loopstart -= sp->v.start;
	sp->v.loखोलोd -= sp->v.start;
	sp->v.start = 0;

	/* dram position (in word) -- mem_offset is byte */
	dram_offset = EMU8000_DRAM_OFFSET + (sp->block->offset >> 1);
	dram_start = dram_offset;

	/* set the total size (store onto obsolete checksum value) */
	sp->v.truesize = truesize * 2; /* in bytes */

	snd_emux_terminate_all(emu->emu);
	अगर ((rc = snd_emu8000_खोलो_dma(emu, EMU8000_RAM_WRITE)) != 0)
		वापस rc;

	/* Set the address to start writing at */
	snd_emu8000_ग_लिखो_रुको(emu);
	EMU8000_SMALW_WRITE(emu, dram_offset);

	/*snd_emu8000_init_fm(emu);*/

#अगर 0
	/* first block - ग_लिखो 48 samples क्रम silence */
	अगर (! sp->block->offset) अणु
		क्रम (i = 0; i < BLANK_HEAD_SIZE; i++) अणु
			ग_लिखो_word(emu, &dram_offset, 0);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	offset = 0;
	क्रम (i = 0; i < sp->v.size; i++) अणु
		अचिन्हित लघु s;

		s = पढ़ो_word(data, offset, sp->v.mode_flags);
		offset++;
		ग_लिखो_word(emu, &dram_offset, s);

		/* we may take too दीर्घ समय in this loop.
		 * so give controls back to kernel अगर needed.
		 */
		cond_resched();

		अगर (i == sp->v.loखोलोd &&
		    (sp->v.mode_flags & (SNDRV_SFNT_SAMPLE_BIसूची_LOOP|SNDRV_SFNT_SAMPLE_REVERSE_LOOP)))
		अणु
			पूर्णांक looplen = sp->v.loखोलोd - sp->v.loopstart;
			पूर्णांक k;

			/* copy reverse loop */
			क्रम (k = 1; k <= looplen; k++) अणु
				s = पढ़ो_word(data, offset - k, sp->v.mode_flags);
				ग_लिखो_word(emu, &dram_offset, s);
			पूर्ण
			अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_BIसूची_LOOP) अणु
				sp->v.loखोलोd += looplen;
			पूर्ण अन्यथा अणु
				sp->v.loopstart += looplen;
				sp->v.loखोलोd += looplen;
			पूर्ण
			sp->v.end += looplen;
		पूर्ण
	पूर्ण

	/* अगर no blank loop is attached in the sample, add it */
	अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_NO_BLANK) अणु
		क्रम (i = 0; i < BLANK_LOOP_SIZE; i++) अणु
			ग_लिखो_word(emu, &dram_offset, 0);
		पूर्ण
		अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_SINGLESHOT) अणु
			sp->v.loopstart = sp->v.end + BLANK_LOOP_START;
			sp->v.loखोलोd = sp->v.end + BLANK_LOOP_END;
		पूर्ण
	पूर्ण

	/* add dram offset */
	sp->v.start += dram_start;
	sp->v.end += dram_start;
	sp->v.loopstart += dram_start;
	sp->v.loखोलोd += dram_start;

	snd_emu8000_बंद_dma(emu);
	snd_emu8000_init_fm(emu);

	वापस 0;
पूर्ण

/*
 * मुक्त a sample block
 */
पूर्णांक
snd_emu8000_sample_मुक्त(काष्ठा snd_emux *rec, काष्ठा snd_sf_sample *sp,
			काष्ठा snd_util_memhdr *hdr)
अणु
	अगर (sp->block) अणु
		snd_util_mem_मुक्त(hdr, sp->block);
		sp->block = शून्य;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * sample_reset callback - terminate voices
 */
व्योम
snd_emu8000_sample_reset(काष्ठा snd_emux *rec)
अणु
	snd_emux_terminate_all(rec);
पूर्ण
