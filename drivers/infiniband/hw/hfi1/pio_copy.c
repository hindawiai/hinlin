<शैली गुरु>
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश "hfi.h"

/* additive distance between non-SOP and SOP space */
#घोषणा SOP_DISTANCE (TXE_PIO_SIZE / 2)
#घोषणा PIO_BLOCK_MASK (PIO_BLOCK_SIZE - 1)
/* number of QUADWORDs in a block */
#घोषणा PIO_BLOCK_QWS (PIO_BLOCK_SIZE / माप(u64))

/**
 * pio_copy - copy data block to MMIO space
 * @dd: hfi1 dev data
 * @pbuf: a number of blocks allocated within a PIO send context
 * @pbc: PBC to send
 * @from: source, must be 8 byte aligned
 * @count: number of DWORD (32-bit) quantities to copy from source
 *
 * Copy data from source to PIO Send Buffer memory, 8 bytes at a समय.
 * Must always ग_लिखो full BLOCK_SIZE bytes blocks.  The first block must
 * be written to the corresponding SOP=1 address.
 *
 * Known:
 * o pbuf->start always starts on a block boundary
 * o pbuf can wrap only at a block boundary
 */
व्योम pio_copy(काष्ठा hfi1_devdata *dd, काष्ठा pio_buf *pbuf, u64 pbc,
	      स्थिर व्योम *from, माप_प्रकार count)
अणु
	व्योम __iomem *dest = pbuf->start + SOP_DISTANCE;
	व्योम __iomem *send = dest + PIO_BLOCK_SIZE;
	व्योम __iomem *dend;			/* 8-byte data end */

	/* ग_लिखो the PBC */
	ग_लिखोq(pbc, dest);
	dest += माप(u64);

	/* calculate where the QWORD data ends - in SOP=1 space */
	dend = dest + ((count >> 1) * माप(u64));

	अगर (dend < send) अणु
		/*
		 * all QWORD data is within the SOP block, करोes *not*
		 * reach the end of the SOP block
		 */

		जबतक (dest < dend) अणु
			ग_लिखोq(*(u64 *)from, dest);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण
		/*
		 * No boundary checks are needed here:
		 * 0. We're not on the SOP block boundary
		 * 1. The possible DWORD dangle will still be within
		 *    the SOP block
		 * 2. We cannot wrap except on a block boundary.
		 */
	पूर्ण अन्यथा अणु
		/* QWORD data extends _to_ or beyond the SOP block */

		/* ग_लिखो 8-byte SOP chunk data */
		जबतक (dest < send) अणु
			ग_लिखोq(*(u64 *)from, dest);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण
		/* drop out of the SOP range */
		dest -= SOP_DISTANCE;
		dend -= SOP_DISTANCE;

		/*
		 * If the wrap comes beक्रमe or matches the data end,
		 * copy until until the wrap, then wrap.
		 *
		 * If the data ends at the end of the SOP above and
		 * the buffer wraps, then pbuf->end == dend == dest
		 * and nothing will get written, but we will wrap in
		 * हाल there is a dangling DWORD.
		 */
		अगर (pbuf->end <= dend) अणु
			जबतक (dest < pbuf->end) अणु
				ग_लिखोq(*(u64 *)from, dest);
				from += माप(u64);
				dest += माप(u64);
			पूर्ण

			dest -= pbuf->sc->size;
			dend -= pbuf->sc->size;
		पूर्ण

		/* ग_लिखो 8-byte non-SOP, non-wrap chunk data */
		जबतक (dest < dend) अणु
			ग_लिखोq(*(u64 *)from, dest);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण
	पूर्ण
	/* at this poपूर्णांक we have wrapped अगर we are going to wrap */

	/* ग_लिखो dangling u32, अगर any */
	अगर (count & 1) अणु
		जोड़ mix val;

		val.val64 = 0;
		val.val32[0] = *(u32 *)from;
		ग_लिखोq(val.val64, dest);
		dest += माप(u64);
	पूर्ण
	/*
	 * fill in rest of block, no need to check pbuf->end
	 * as we only wrap on a block boundary
	 */
	जबतक (((अचिन्हित दीर्घ)dest & PIO_BLOCK_MASK) != 0) अणु
		ग_लिखोq(0, dest);
		dest += माप(u64);
	पूर्ण

	/* finished with this buffer */
	this_cpu_dec(*pbuf->sc->buffers_allocated);
	preempt_enable();
पूर्ण

/*
 * Handle carry bytes using shअगरts and masks.
 *
 * NOTE: the value the unused portion of carry is expected to always be zero.
 */

/*
 * "zero" shअगरt - bit shअगरt used to zero out upper bytes.  Input is
 * the count of LSB bytes to preserve.
 */
#घोषणा zshअगरt(x) (8 * (8 - (x)))

/*
 * "merge" shअगरt - bit shअगरt used to merge with carry bytes.  Input is
 * the LSB byte count to move beyond.
 */
#घोषणा mshअगरt(x) (8 * (x))

/*
 * Jump copy - no-loop copy क्रम < 8 bytes.
 */
अटल अंतरभूत व्योम jcopy(u8 *dest, स्थिर u8 *src, u32 n)
अणु
	चयन (n) अणु
	हाल 7:
		*dest++ = *src++;
		fallthrough;
	हाल 6:
		*dest++ = *src++;
		fallthrough;
	हाल 5:
		*dest++ = *src++;
		fallthrough;
	हाल 4:
		*dest++ = *src++;
		fallthrough;
	हाल 3:
		*dest++ = *src++;
		fallthrough;
	हाल 2:
		*dest++ = *src++;
		fallthrough;
	हाल 1:
		*dest++ = *src++;
	पूर्ण
पूर्ण

/*
 * Read nbytes from "from" and and place them in the low bytes
 * of pbuf->carry.  Other bytes are left as-is.  Any previous
 * value in pbuf->carry is lost.
 *
 * NOTES:
 * o करो not पढ़ो from from अगर nbytes is zero
 * o from may _not_ be u64 aligned.
 */
अटल अंतरभूत व्योम पढ़ो_low_bytes(काष्ठा pio_buf *pbuf, स्थिर व्योम *from,
				  अचिन्हित पूर्णांक nbytes)
अणु
	pbuf->carry.val64 = 0;
	jcopy(&pbuf->carry.val8[0], from, nbytes);
	pbuf->carry_bytes = nbytes;
पूर्ण

/*
 * Read nbytes bytes from "from" and put them at the end of pbuf->carry.
 * It is expected that the extra पढ़ो करोes not overfill carry.
 *
 * NOTES:
 * o from may _not_ be u64 aligned
 * o nbytes may span a QW boundary
 */
अटल अंतरभूत व्योम पढ़ो_extra_bytes(काष्ठा pio_buf *pbuf,
				    स्थिर व्योम *from, अचिन्हित पूर्णांक nbytes)
अणु
	jcopy(&pbuf->carry.val8[pbuf->carry_bytes], from, nbytes);
	pbuf->carry_bytes += nbytes;
पूर्ण

/*
 * Write a quad word using parts of pbuf->carry and the next 8 bytes of src.
 * Put the unused part of the next 8 bytes of src पूर्णांकo the LSB bytes of
 * pbuf->carry with the upper bytes zeroed..
 *
 * NOTES:
 * o result must keep unused bytes zeroed
 * o src must be u64 aligned
 */
अटल अंतरभूत व्योम merge_ग_लिखो8(
	काष्ठा pio_buf *pbuf,
	व्योम __iomem *dest,
	स्थिर व्योम *src)
अणु
	u64 new, temp;

	new = *(u64 *)src;
	temp = pbuf->carry.val64 | (new << mshअगरt(pbuf->carry_bytes));
	ग_लिखोq(temp, dest);
	pbuf->carry.val64 = new >> zshअगरt(pbuf->carry_bytes);
पूर्ण

/*
 * Write a quad word using all bytes of carry.
 */
अटल अंतरभूत व्योम carry8_ग_लिखो8(जोड़ mix carry, व्योम __iomem *dest)
अणु
	ग_लिखोq(carry.val64, dest);
पूर्ण

/*
 * Write a quad word using all the valid bytes of carry.  If carry
 * has zero valid bytes, nothing is written.
 * Returns 0 on nothing written, non-zero on quad word written.
 */
अटल अंतरभूत पूर्णांक carry_ग_लिखो8(काष्ठा pio_buf *pbuf, व्योम __iomem *dest)
अणु
	अगर (pbuf->carry_bytes) अणु
		/* unused bytes are always kept zeroed, so just ग_लिखो */
		ग_लिखोq(pbuf->carry.val64, dest);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Segmented PIO Copy - start
 *
 * Start a PIO copy.
 *
 * @pbuf: destination buffer
 * @pbc: the PBC क्रम the PIO buffer
 * @from: data source, QWORD aligned
 * @nbytes: bytes to copy
 */
व्योम seg_pio_copy_start(काष्ठा pio_buf *pbuf, u64 pbc,
			स्थिर व्योम *from, माप_प्रकार nbytes)
अणु
	व्योम __iomem *dest = pbuf->start + SOP_DISTANCE;
	व्योम __iomem *send = dest + PIO_BLOCK_SIZE;
	व्योम __iomem *dend;			/* 8-byte data end */

	ग_लिखोq(pbc, dest);
	dest += माप(u64);

	/* calculate where the QWORD data ends - in SOP=1 space */
	dend = dest + ((nbytes >> 3) * माप(u64));

	अगर (dend < send) अणु
		/*
		 * all QWORD data is within the SOP block, करोes *not*
		 * reach the end of the SOP block
		 */

		जबतक (dest < dend) अणु
			ग_लिखोq(*(u64 *)from, dest);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण
		/*
		 * No boundary checks are needed here:
		 * 0. We're not on the SOP block boundary
		 * 1. The possible DWORD dangle will still be within
		 *    the SOP block
		 * 2. We cannot wrap except on a block boundary.
		 */
	पूर्ण अन्यथा अणु
		/* QWORD data extends _to_ or beyond the SOP block */

		/* ग_लिखो 8-byte SOP chunk data */
		जबतक (dest < send) अणु
			ग_लिखोq(*(u64 *)from, dest);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण
		/* drop out of the SOP range */
		dest -= SOP_DISTANCE;
		dend -= SOP_DISTANCE;

		/*
		 * If the wrap comes beक्रमe or matches the data end,
		 * copy until until the wrap, then wrap.
		 *
		 * If the data ends at the end of the SOP above and
		 * the buffer wraps, then pbuf->end == dend == dest
		 * and nothing will get written, but we will wrap in
		 * हाल there is a dangling DWORD.
		 */
		अगर (pbuf->end <= dend) अणु
			जबतक (dest < pbuf->end) अणु
				ग_लिखोq(*(u64 *)from, dest);
				from += माप(u64);
				dest += माप(u64);
			पूर्ण

			dest -= pbuf->sc->size;
			dend -= pbuf->sc->size;
		पूर्ण

		/* ग_लिखो 8-byte non-SOP, non-wrap chunk data */
		जबतक (dest < dend) अणु
			ग_लिखोq(*(u64 *)from, dest);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण
	पूर्ण
	/* at this poपूर्णांक we have wrapped अगर we are going to wrap */

	/* ...but it करोesn't matter as we're करोne writing */

	/* save dangling bytes, अगर any */
	पढ़ो_low_bytes(pbuf, from, nbytes & 0x7);

	pbuf->qw_written = 1 /*PBC*/ + (nbytes >> 3);
पूर्ण

/*
 * Mid copy helper, "mixed case" - source is 64-bit aligned but carry
 * bytes are non-zero.
 *
 * Whole u64s must be written to the chip, so bytes must be manually merged.
 *
 * @pbuf: destination buffer
 * @from: data source, is QWORD aligned.
 * @nbytes: bytes to copy
 *
 * Must handle nbytes < 8.
 */
अटल व्योम mid_copy_mix(काष्ठा pio_buf *pbuf, स्थिर व्योम *from, माप_प्रकार nbytes)
अणु
	व्योम __iomem *dest = pbuf->start + (pbuf->qw_written * माप(u64));
	व्योम __iomem *dend;			/* 8-byte data end */
	अचिन्हित दीर्घ qw_to_ग_लिखो = nbytes >> 3;
	अचिन्हित दीर्घ bytes_left = nbytes & 0x7;

	/* calculate 8-byte data end */
	dend = dest + (qw_to_ग_लिखो * माप(u64));

	अगर (pbuf->qw_written < PIO_BLOCK_QWS) अणु
		/*
		 * Still within SOP block.  We करोn't need to check क्रम
		 * wrap because we are still in the first block and
		 * can only wrap on block boundaries.
		 */
		व्योम __iomem *send;		/* SOP end */
		व्योम __iomem *xend;

		/*
		 * calculate the end of data or end of block, whichever
		 * comes first
		 */
		send = pbuf->start + PIO_BLOCK_SIZE;
		xend = min(send, dend);

		/* shअगरt up to SOP=1 space */
		dest += SOP_DISTANCE;
		xend += SOP_DISTANCE;

		/* ग_लिखो 8-byte chunk data */
		जबतक (dest < xend) अणु
			merge_ग_लिखो8(pbuf, dest, from);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण

		/* shअगरt करोwn to SOP=0 space */
		dest -= SOP_DISTANCE;
	पूर्ण
	/*
	 * At this poपूर्णांक dest could be (either, both, or neither):
	 * - at dend
	 * - at the wrap
	 */

	/*
	 * If the wrap comes beक्रमe or matches the data end,
	 * copy until until the wrap, then wrap.
	 *
	 * If dest is at the wrap, we will fall पूर्णांकo the अगर,
	 * not करो the loop, when wrap.
	 *
	 * If the data ends at the end of the SOP above and
	 * the buffer wraps, then pbuf->end == dend == dest
	 * and nothing will get written.
	 */
	अगर (pbuf->end <= dend) अणु
		जबतक (dest < pbuf->end) अणु
			merge_ग_लिखो8(pbuf, dest, from);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण

		dest -= pbuf->sc->size;
		dend -= pbuf->sc->size;
	पूर्ण

	/* ग_लिखो 8-byte non-SOP, non-wrap chunk data */
	जबतक (dest < dend) अणु
		merge_ग_लिखो8(pbuf, dest, from);
		from += माप(u64);
		dest += माप(u64);
	पूर्ण

	pbuf->qw_written += qw_to_ग_लिखो;

	/* handle carry and left-over bytes */
	अगर (pbuf->carry_bytes + bytes_left >= 8) अणु
		अचिन्हित दीर्घ nपढ़ो;

		/* there is enough to fill another qw - fill carry */
		nपढ़ो = 8 - pbuf->carry_bytes;
		पढ़ो_extra_bytes(pbuf, from, nपढ़ो);

		/*
		 * One more ग_लिखो - but need to make sure dest is correct.
		 * Check क्रम wrap and the possibility the ग_लिखो
		 * should be in SOP space.
		 *
		 * The two checks immediately below cannot both be true, hence
		 * the अन्यथा. If we have wrapped, we cannot still be within the
		 * first block. Conversely, अगर we are still in the first block,
		 * we cannot have wrapped. We करो the wrap check first as that
		 * is more likely.
		 */
		/* adjust अगर we have wrapped */
		अगर (dest >= pbuf->end)
			dest -= pbuf->sc->size;
		/* jump to the SOP range अगर within the first block */
		अन्यथा अगर (pbuf->qw_written < PIO_BLOCK_QWS)
			dest += SOP_DISTANCE;

		/* flush out full carry */
		carry8_ग_लिखो8(pbuf->carry, dest);
		pbuf->qw_written++;

		/* now adjust and पढ़ो the rest of the bytes पूर्णांकo carry */
		bytes_left -= nपढ़ो;
		from += nपढ़ो; /* from is now not aligned */
		पढ़ो_low_bytes(pbuf, from, bytes_left);
	पूर्ण अन्यथा अणु
		/* not enough to fill another qw, append the rest to carry */
		पढ़ो_extra_bytes(pbuf, from, bytes_left);
	पूर्ण
पूर्ण

/*
 * Mid copy helper, "straight case" - source poपूर्णांकer is 64-bit aligned
 * with no carry bytes.
 *
 * @pbuf: destination buffer
 * @from: data source, is QWORD aligned
 * @nbytes: bytes to copy
 *
 * Must handle nbytes < 8.
 */
अटल व्योम mid_copy_straight(काष्ठा pio_buf *pbuf,
			      स्थिर व्योम *from, माप_प्रकार nbytes)
अणु
	व्योम __iomem *dest = pbuf->start + (pbuf->qw_written * माप(u64));
	व्योम __iomem *dend;			/* 8-byte data end */

	/* calculate 8-byte data end */
	dend = dest + ((nbytes >> 3) * माप(u64));

	अगर (pbuf->qw_written < PIO_BLOCK_QWS) अणु
		/*
		 * Still within SOP block.  We करोn't need to check क्रम
		 * wrap because we are still in the first block and
		 * can only wrap on block boundaries.
		 */
		व्योम __iomem *send;		/* SOP end */
		व्योम __iomem *xend;

		/*
		 * calculate the end of data or end of block, whichever
		 * comes first
		 */
		send = pbuf->start + PIO_BLOCK_SIZE;
		xend = min(send, dend);

		/* shअगरt up to SOP=1 space */
		dest += SOP_DISTANCE;
		xend += SOP_DISTANCE;

		/* ग_लिखो 8-byte chunk data */
		जबतक (dest < xend) अणु
			ग_लिखोq(*(u64 *)from, dest);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण

		/* shअगरt करोwn to SOP=0 space */
		dest -= SOP_DISTANCE;
	पूर्ण
	/*
	 * At this poपूर्णांक dest could be (either, both, or neither):
	 * - at dend
	 * - at the wrap
	 */

	/*
	 * If the wrap comes beक्रमe or matches the data end,
	 * copy until until the wrap, then wrap.
	 *
	 * If dest is at the wrap, we will fall पूर्णांकo the अगर,
	 * not करो the loop, when wrap.
	 *
	 * If the data ends at the end of the SOP above and
	 * the buffer wraps, then pbuf->end == dend == dest
	 * and nothing will get written.
	 */
	अगर (pbuf->end <= dend) अणु
		जबतक (dest < pbuf->end) अणु
			ग_लिखोq(*(u64 *)from, dest);
			from += माप(u64);
			dest += माप(u64);
		पूर्ण

		dest -= pbuf->sc->size;
		dend -= pbuf->sc->size;
	पूर्ण

	/* ग_लिखो 8-byte non-SOP, non-wrap chunk data */
	जबतक (dest < dend) अणु
		ग_लिखोq(*(u64 *)from, dest);
		from += माप(u64);
		dest += माप(u64);
	पूर्ण

	/* we know carry_bytes was zero on entry to this routine */
	पढ़ो_low_bytes(pbuf, from, nbytes & 0x7);

	pbuf->qw_written += nbytes >> 3;
पूर्ण

/*
 * Segmented PIO Copy - middle
 *
 * Must handle any aligned tail and any aligned source with any byte count.
 *
 * @pbuf: a number of blocks allocated within a PIO send context
 * @from: data source
 * @nbytes: number of bytes to copy
 */
व्योम seg_pio_copy_mid(काष्ठा pio_buf *pbuf, स्थिर व्योम *from, माप_प्रकार nbytes)
अणु
	अचिन्हित दीर्घ from_align = (अचिन्हित दीर्घ)from & 0x7;

	अगर (pbuf->carry_bytes + nbytes < 8) अणु
		/* not enough bytes to fill a QW */
		पढ़ो_extra_bytes(pbuf, from, nbytes);
		वापस;
	पूर्ण

	अगर (from_align) अणु
		/* misaligned source poपूर्णांकer - align it */
		अचिन्हित दीर्घ to_align;

		/* bytes to पढ़ो to align "from" */
		to_align = 8 - from_align;

		/*
		 * In the advance-to-alignment logic below, we करो not need
		 * to check अगर we are using more than nbytes.  This is because
		 * अगर we are here, we alपढ़ोy know that carry+nbytes will
		 * fill at least one QW.
		 */
		अगर (pbuf->carry_bytes + to_align < 8) अणु
			/* not enough align bytes to fill a QW */
			पढ़ो_extra_bytes(pbuf, from, to_align);
			from += to_align;
			nbytes -= to_align;
		पूर्ण अन्यथा अणु
			/* bytes to fill carry */
			अचिन्हित दीर्घ to_fill = 8 - pbuf->carry_bytes;
			/* bytes left over to be पढ़ो */
			अचिन्हित दीर्घ extra = to_align - to_fill;
			व्योम __iomem *dest;

			/* fill carry... */
			पढ़ो_extra_bytes(pbuf, from, to_fill);
			from += to_fill;
			nbytes -= to_fill;
			/* may not be enough valid bytes left to align */
			अगर (extra > nbytes)
				extra = nbytes;

			/* ...now ग_लिखो carry */
			dest = pbuf->start + (pbuf->qw_written * माप(u64));

			/*
			 * The two checks immediately below cannot both be
			 * true, hence the अन्यथा.  If we have wrapped, we
			 * cannot still be within the first block.
			 * Conversely, अगर we are still in the first block, we
			 * cannot have wrapped.  We करो the wrap check first
			 * as that is more likely.
			 */
			/* adjust अगर we've wrapped */
			अगर (dest >= pbuf->end)
				dest -= pbuf->sc->size;
			/* jump to SOP range अगर within the first block */
			अन्यथा अगर (pbuf->qw_written < PIO_BLOCK_QWS)
				dest += SOP_DISTANCE;

			carry8_ग_लिखो8(pbuf->carry, dest);
			pbuf->qw_written++;

			/* पढ़ो any extra bytes to करो final alignment */
			/* this will overग_लिखो anything in pbuf->carry */
			पढ़ो_low_bytes(pbuf, from, extra);
			from += extra;
			nbytes -= extra;
			/*
			 * If no bytes are left, वापस early - we are करोne.
			 * NOTE: This लघु-circuit is *required* because
			 * "extra" may have been reduced in size and "from"
			 * is not aligned, as required when leaving this
			 * अगर block.
			 */
			अगर (nbytes == 0)
				वापस;
		पूर्ण

		/* at this poपूर्णांक, from is QW aligned */
	पूर्ण

	अगर (pbuf->carry_bytes)
		mid_copy_mix(pbuf, from, nbytes);
	अन्यथा
		mid_copy_straight(pbuf, from, nbytes);
पूर्ण

/*
 * Segmented PIO Copy - end
 *
 * Write any reमुख्यder (in pbuf->carry) and finish writing the whole block.
 *
 * @pbuf: a number of blocks allocated within a PIO send context
 */
व्योम seg_pio_copy_end(काष्ठा pio_buf *pbuf)
अणु
	व्योम __iomem *dest = pbuf->start + (pbuf->qw_written * माप(u64));

	/*
	 * The two checks immediately below cannot both be true, hence the
	 * अन्यथा.  If we have wrapped, we cannot still be within the first
	 * block.  Conversely, अगर we are still in the first block, we
	 * cannot have wrapped.  We करो the wrap check first as that is
	 * more likely.
	 */
	/* adjust अगर we have wrapped */
	अगर (dest >= pbuf->end)
		dest -= pbuf->sc->size;
	/* jump to the SOP range अगर within the first block */
	अन्यथा अगर (pbuf->qw_written < PIO_BLOCK_QWS)
		dest += SOP_DISTANCE;

	/* ग_लिखो final bytes, अगर any */
	अगर (carry_ग_लिखो8(pbuf, dest)) अणु
		dest += माप(u64);
		/*
		 * NOTE: We करो not need to recalculate whether dest needs
		 * SOP_DISTANCE or not.
		 *
		 * If we are in the first block and the dangle ग_लिखो
		 * keeps us in the same block, dest will need
		 * to retain SOP_DISTANCE in the loop below.
		 *
		 * If we are in the first block and the dangle ग_लिखो pushes
		 * us to the next block, then loop below will not run
		 * and dest is not used.  Hence we करो not need to update
		 * it.
		 *
		 * If we are past the first block, then SOP_DISTANCE
		 * was never added, so there is nothing to करो.
		 */
	पूर्ण

	/* fill in rest of block */
	जबतक (((अचिन्हित दीर्घ)dest & PIO_BLOCK_MASK) != 0) अणु
		ग_लिखोq(0, dest);
		dest += माप(u64);
	पूर्ण

	/* finished with this buffer */
	this_cpu_dec(*pbuf->sc->buffers_allocated);
	preempt_enable();
पूर्ण
