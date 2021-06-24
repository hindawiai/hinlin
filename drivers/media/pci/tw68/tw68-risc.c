<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  tw68_risc.c
 *  Part of the device driver क्रम Techwell 68xx based cards
 *
 *  Much of this code is derived from the cx88 and sa7134 drivers, which
 *  were in turn derived from the bt87x driver.  The original work was by
 *  Gerd Knorr; more recently the code was enhanced by Mauro Carvalho Chehab,
 *  Hans Verkuil, Andy Walls and many others.  Their work is gratefully
 *  acknowledged.  Full credit goes to them - any problems within this code
 *  are mine.
 *
 *  Copyright (C) 2009  William M. Brack
 *
 *  Refactored and updated to the latest v4l core frameworks:
 *
 *  Copyright (C) 2014 Hans Verkuil <hverkuil@xs4all.nl>
 */

#समावेश "tw68.h"

/**
 * tw68_risc_field
 *  @rp:	poपूर्णांकer to current risc program position
 *  @sglist:	poपूर्णांकer to "scatter-gather list" of buffer poपूर्णांकers
 *  @offset:	offset to target memory buffer
 *  @sync_line:	0 -> no sync, 1 -> odd sync, 2 -> even sync
 *  @bpl:	number of bytes per scan line
 *  @padding:	number of bytes of padding to add
 *  @lines:	number of lines in field
 *  @jump:	insert a jump at the start
 */
अटल __le32 *tw68_risc_field(__le32 *rp, काष्ठा scatterlist *sglist,
			    अचिन्हित पूर्णांक offset, u32 sync_line,
			    अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक padding,
			    अचिन्हित पूर्णांक lines, bool jump)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक line, toकरो, करोne;

	अगर (jump) अणु
		*(rp++) = cpu_to_le32(RISC_JUMP);
		*(rp++) = 0;
	पूर्ण

	/* sync inकाष्ठाion */
	अगर (sync_line == 1)
		*(rp++) = cpu_to_le32(RISC_SYNCO);
	अन्यथा
		*(rp++) = cpu_to_le32(RISC_SYNCE);
	*(rp++) = 0;

	/* scan lines */
	sg = sglist;
	क्रम (line = 0; line < lines; line++) अणु
		/* calculate next starting position */
		जबतक (offset && offset >= sg_dma_len(sg)) अणु
			offset -= sg_dma_len(sg);
			sg = sg_next(sg);
		पूर्ण
		अगर (bpl <= sg_dma_len(sg) - offset) अणु
			/* fits पूर्णांकo current chunk */
			*(rp++) = cpu_to_le32(RISC_LINESTART |
					      /* (offset<<12) |*/  bpl);
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			offset += bpl;
		पूर्ण अन्यथा अणु
			/*
			 * scanline needs to be split.  Put the start in
			 * whatever memory reमुख्यs using RISC_LINESTART,
			 * then the reमुख्यder पूर्णांकo following addresses
			 * given by the scatter-gather list.
			 */
			toकरो = bpl;	/* one full line to be करोne */
			/* first fragment */
			करोne = (sg_dma_len(sg) - offset);
			*(rp++) = cpu_to_le32(RISC_LINESTART |
						(7 << 24) |
						करोne);
			*(rp++) = cpu_to_le32(sg_dma_address(sg) + offset);
			toकरो -= करोne;
			sg = sg_next(sg);
			/* succeeding fragments have no offset */
			जबतक (toकरो > sg_dma_len(sg)) अणु
				*(rp++) = cpu_to_le32(RISC_INLINE |
						(करोne << 12) |
						sg_dma_len(sg));
				*(rp++) = cpu_to_le32(sg_dma_address(sg));
				toकरो -= sg_dma_len(sg);
				sg = sg_next(sg);
				करोne += sg_dma_len(sg);
			पूर्ण
			अगर (toकरो) अणु
				/* final chunk - offset 0, count 'todo' */
				*(rp++) = cpu_to_le32(RISC_INLINE |
							(करोne << 12) |
							toकरो);
				*(rp++) = cpu_to_le32(sg_dma_address(sg));
			पूर्ण
			offset = toकरो;
		पूर्ण
		offset += padding;
	पूर्ण

	वापस rp;
पूर्ण

/**
 * tw68_risc_buffer
 *
 *	This routine is called by tw68-video.  It allocates
 *	memory क्रम the dma controller "program" and then fills in that
 *	memory with the appropriate "instructions".
 *
 *	@pci:		काष्ठाure with info about the pci
 *			slot which our device is in.
 *	@buf:		काष्ठाure with info about the memory
 *			used क्रम our controller program.
 *	@sglist:	scatter-gather list entry
 *	@top_offset:	offset within the risc program area क्रम the
 *			first odd frame line
 *	@bottom_offset:	offset within the risc program area क्रम the
 *			first even frame line
 *	@bpl:		number of data bytes per scan line
 *	@padding:	number of extra bytes to add at end of line
 *	@lines:		number of scan lines
 */
पूर्णांक tw68_risc_buffer(काष्ठा pci_dev *pci,
			काष्ठा tw68_buf *buf,
			काष्ठा scatterlist *sglist,
			अचिन्हित पूर्णांक top_offset,
			अचिन्हित पूर्णांक bottom_offset,
			अचिन्हित पूर्णांक bpl,
			अचिन्हित पूर्णांक padding,
			अचिन्हित पूर्णांक lines)
अणु
	u32 inकाष्ठाions, fields;
	__le32 *rp;

	fields = 0;
	अगर (UNSET != top_offset)
		fields++;
	अगर (UNSET != bottom_offset)
		fields++;
	/*
	 * estimate risc mem: worst हाल is one ग_लिखो per page border +
	 * one ग_लिखो per scan line + syncs + 2 jumps (all 2 dwords).
	 * Padding can cause next bpl to start बंद to a page border.
	 * First DMA region may be smaller than PAGE_SIZE
	 */
	inकाष्ठाions  = fields * (1 + (((bpl + padding) * lines) /
			 PAGE_SIZE) + lines) + 4;
	buf->size = inकाष्ठाions * 8;
	buf->cpu = dma_alloc_coherent(&pci->dev, buf->size, &buf->dma,
				      GFP_KERNEL);
	अगर (buf->cpu == शून्य)
		वापस -ENOMEM;

	/* ग_लिखो risc inकाष्ठाions */
	rp = buf->cpu;
	अगर (UNSET != top_offset)	/* generates SYNCO */
		rp = tw68_risc_field(rp, sglist, top_offset, 1,
				     bpl, padding, lines, true);
	अगर (UNSET != bottom_offset)	/* generates SYNCE */
		rp = tw68_risc_field(rp, sglist, bottom_offset, 2,
				     bpl, padding, lines, top_offset == UNSET);

	/* save poपूर्णांकer to jmp inकाष्ठाion address */
	buf->jmp = rp;
	buf->cpu[1] = cpu_to_le32(buf->dma + 8);
	/* assure risc buffer hasn't overflowed */
	BUG_ON((buf->jmp - buf->cpu + 2) * माप(buf->cpu[0]) > buf->size);
	वापस 0;
पूर्ण

#अगर 0
/* ------------------------------------------------------------------ */
/* debug helper code                                                  */

अटल व्योम tw68_risc_decode(u32 risc, u32 addr)
अणु
#घोषणा	RISC_OP(reg)	(((reg) >> 28) & 7)
	अटल काष्ठा instr_details अणु
		अक्षर *name;
		u8 has_data_type;
		u8 has_byte_info;
		u8 has_addr;
	पूर्ण instr[8] = अणु
		[RISC_OP(RISC_SYNCO)]	  = अणु"syncOdd", 0, 0, 0पूर्ण,
		[RISC_OP(RISC_SYNCE)]	  = अणु"syncEven", 0, 0, 0पूर्ण,
		[RISC_OP(RISC_JUMP)]	  = अणु"jump", 0, 0, 1पूर्ण,
		[RISC_OP(RISC_LINESTART)] = अणु"lineStart", 1, 1, 1पूर्ण,
		[RISC_OP(RISC_INLINE)]	  = अणु"inline", 1, 1, 1पूर्ण,
	पूर्ण;
	u32 p;

	p = RISC_OP(risc);
	अगर (!(risc & 0x80000000) || !instr[p].name) अणु
		pr_debug("0x%08x [ INVALID ]\n", risc);
		वापस;
	पूर्ण
	pr_debug("0x%08x %-9s IRQ=%d",
		risc, instr[p].name, (risc >> 27) & 1);
	अगर (instr[p].has_data_type)
		pr_debug(" Type=%d", (risc >> 24) & 7);
	अगर (instr[p].has_byte_info)
		pr_debug(" Start=0x%03x Count=%03u",
			(risc >> 12) & 0xfff, risc & 0xfff);
	अगर (instr[p].has_addr)
		pr_debug(" StartAddr=0x%08x", addr);
	pr_debug("\n");
पूर्ण

व्योम tw68_risc_program_dump(काष्ठा tw68_core *core, काष्ठा tw68_buf *buf)
अणु
	स्थिर __le32 *addr;

	pr_debug("%s: risc_program_dump: risc=%p, buf->cpu=0x%p, buf->jmp=0x%p\n",
		  core->name, buf, buf->cpu, buf->jmp);
	क्रम (addr = buf->cpu; addr <= buf->jmp; addr += 2)
		tw68_risc_decode(*addr, *(addr+1));
पूर्ण
#पूर्ण_अगर
