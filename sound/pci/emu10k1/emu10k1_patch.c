<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Patch transfer callback क्रम Emu10k1
 *
 *  Copyright (C) 2000 Takashi iwai <tiwai@suse.de>
 */
/*
 * All the code क्रम loading in a patch.  There is very little that is
 * chip specअगरic here.  Just the actual writing to the board.
 */

#समावेश "emu10k1_synth_local.h"

/*
 */
#घोषणा BLANK_LOOP_START	4
#घोषणा BLANK_LOOP_END		8
#घोषणा BLANK_LOOP_SIZE		12
#घोषणा BLANK_HEAD_SIZE		32

/*
 * allocate a sample block and copy data from userspace
 */
पूर्णांक
snd_emu10k1_sample_new(काष्ठा snd_emux *rec, काष्ठा snd_sf_sample *sp,
		       काष्ठा snd_util_memhdr *hdr,
		       स्थिर व्योम __user *data, दीर्घ count)
अणु
	पूर्णांक offset;
	पूर्णांक truesize, size, blocksize;
	__maybe_unused पूर्णांक loopsize;
	पूर्णांक loखोलोd, sampleend;
	अचिन्हित पूर्णांक start_addr;
	काष्ठा snd_emu10k1 *emu;

	emu = rec->hw;
	अगर (snd_BUG_ON(!sp || !hdr))
		वापस -EINVAL;

	अगर (sp->v.size == 0) अणु
		dev_dbg(emu->card->dev,
			"emu: rom font for sample %d\n", sp->v.sample);
		वापस 0;
	पूर्ण

	/* recalculate address offset */
	sp->v.end -= sp->v.start;
	sp->v.loopstart -= sp->v.start;
	sp->v.loखोलोd -= sp->v.start;
	sp->v.start = 0;

	/* some samples have invalid data.  the addresses are corrected in voice info */
	sampleend = sp->v.end;
	अगर (sampleend > sp->v.size)
		sampleend = sp->v.size;
	loखोलोd = sp->v.loखोलोd;
	अगर (loखोलोd > sampleend)
		loखोलोd = sampleend;

	/* be sure loop poपूर्णांकs start < end */
	अगर (sp->v.loopstart >= sp->v.loखोलोd)
		swap(sp->v.loopstart, sp->v.loखोलोd);

	/* compute true data size to be loaded */
	truesize = sp->v.size + BLANK_HEAD_SIZE;
	loopsize = 0;
#अगर 0 /* not supported */
	अगर (sp->v.mode_flags & (SNDRV_SFNT_SAMPLE_BIसूची_LOOP|SNDRV_SFNT_SAMPLE_REVERSE_LOOP))
		loopsize = sp->v.loखोलोd - sp->v.loopstart;
	truesize += loopsize;
#पूर्ण_अगर
	अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_NO_BLANK)
		truesize += BLANK_LOOP_SIZE;

	/* try to allocate a memory block */
	blocksize = truesize;
	अगर (! (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_8BITS))
		blocksize *= 2;
	sp->block = snd_emu10k1_synth_alloc(emu, blocksize);
	अगर (sp->block == शून्य) अणु
		dev_dbg(emu->card->dev,
			"synth malloc failed (size=%d)\n", blocksize);
		/* not ENOMEM (क्रम compatibility with OSS) */
		वापस -ENOSPC;
	पूर्ण
	/* set the total size */
	sp->v.truesize = blocksize;

	/* ग_लिखो blank samples at head */
	offset = 0;
	size = BLANK_HEAD_SIZE;
	अगर (! (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_8BITS))
		size *= 2;
	अगर (offset + size > blocksize)
		वापस -EINVAL;
	snd_emu10k1_synth_bzero(emu, sp->block, offset, size);
	offset += size;

	/* copy start->loखोलोd */
	size = loखोलोd;
	अगर (! (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_8BITS))
		size *= 2;
	अगर (offset + size > blocksize)
		वापस -EINVAL;
	अगर (snd_emu10k1_synth_copy_from_user(emu, sp->block, offset, data, size)) अणु
		snd_emu10k1_synth_मुक्त(emu, sp->block);
		sp->block = शून्य;
		वापस -EFAULT;
	पूर्ण
	offset += size;
	data += size;

#अगर 0 /* not supported yet */
	/* handle reverse (or bidirectional) loop */
	अगर (sp->v.mode_flags & (SNDRV_SFNT_SAMPLE_BIसूची_LOOP|SNDRV_SFNT_SAMPLE_REVERSE_LOOP)) अणु
		/* copy loop in reverse */
		अगर (! (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_8BITS)) अणु
			पूर्णांक woffset;
			अचिन्हित लघु *wblock = (अचिन्हित लघु*)block;
			woffset = offset / 2;
			अगर (offset + loopsize * 2 > blocksize)
				वापस -EINVAL;
			क्रम (i = 0; i < loopsize; i++)
				wblock[woffset + i] = wblock[woffset - i -1];
			offset += loopsize * 2;
		पूर्ण अन्यथा अणु
			अगर (offset + loopsize > blocksize)
				वापस -EINVAL;
			क्रम (i = 0; i < loopsize; i++)
				block[offset + i] = block[offset - i -1];
			offset += loopsize;
		पूर्ण

		/* modअगरy loop poपूर्णांकers */
		अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_BIसूची_LOOP) अणु
			sp->v.loखोलोd += loopsize;
		पूर्ण अन्यथा अणु
			sp->v.loopstart += loopsize;
			sp->v.loखोलोd += loopsize;
		पूर्ण
		/* add sample poपूर्णांकer */
		sp->v.end += loopsize;
	पूर्ण
#पूर्ण_अगर

	/* loखोलोd -> sample end */
	size = sp->v.size - loखोलोd;
	अगर (size < 0)
		वापस -EINVAL;
	अगर (! (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_8BITS))
		size *= 2;
	अगर (snd_emu10k1_synth_copy_from_user(emu, sp->block, offset, data, size)) अणु
		snd_emu10k1_synth_मुक्त(emu, sp->block);
		sp->block = शून्य;
		वापस -EFAULT;
	पूर्ण
	offset += size;

	/* clear rest of samples (अगर any) */
	अगर (offset < blocksize)
		snd_emu10k1_synth_bzero(emu, sp->block, offset, blocksize - offset);

	अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_NO_BLANK) अणु
		/* अगर no blank loop is attached in the sample, add it */
		अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_SINGLESHOT) अणु
			sp->v.loopstart = sp->v.end + BLANK_LOOP_START;
			sp->v.loखोलोd = sp->v.end + BLANK_LOOP_END;
		पूर्ण
	पूर्ण

#अगर 0 /* not supported yet */
	अगर (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_UNSIGNED) अणु
		/* अचिन्हित -> चिन्हित */
		अगर (! (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_8BITS)) अणु
			अचिन्हित लघु *wblock = (अचिन्हित लघु*)block;
			क्रम (i = 0; i < truesize; i++)
				wblock[i] ^= 0x8000;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < truesize; i++)
				block[i] ^= 0x80;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* recalculate offset */
	start_addr = BLANK_HEAD_SIZE * 2;
	अगर (! (sp->v.mode_flags & SNDRV_SFNT_SAMPLE_8BITS))
		start_addr >>= 1;
	sp->v.start += start_addr;
	sp->v.end += start_addr;
	sp->v.loopstart += start_addr;
	sp->v.loखोलोd += start_addr;

	वापस 0;
पूर्ण

/*
 * मुक्त a sample block
 */
पूर्णांक
snd_emu10k1_sample_मुक्त(काष्ठा snd_emux *rec, काष्ठा snd_sf_sample *sp,
			काष्ठा snd_util_memhdr *hdr)
अणु
	काष्ठा snd_emu10k1 *emu;

	emu = rec->hw;
	अगर (snd_BUG_ON(!sp || !hdr))
		वापस -EINVAL;

	अगर (sp->block) अणु
		snd_emu10k1_synth_मुक्त(emu, sp->block);
		sp->block = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

