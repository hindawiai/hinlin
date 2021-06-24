<शैली गुरु>
/*	Small bzip2 deflate implementation, by Rob Landley (rob@landley.net).

	Based on bzip2 decompression code by Julian R Seward (jseward@acm.org),
	which also acknowledges contributions by Mike Burrows, David Wheeler,
	Peter Fenwick, Alistair Moffat, Radक्रमd Neal, Ian H. Witten,
	Robert Sedgewick, and Jon L. Bentley.

	This code is licensed under the LGPLv2:
		LGPL (http://www.gnu.org/copyleft/lgpl.hपंचांगl
*/

/*
	Size and speed optimizations by Manuel Novoa III  (mjn3@codepoet.org).

	More efficient पढ़ोing of Huffman codes, a streamlined पढ़ो_bunzip()
	function, and various other tweaks.  In (limited) tests, approximately
	20% faster than bzcat on x86 and about 10% faster on arm.

	Note that about 2/3 of the समय is spent in पढ़ो_unzip() reversing
	the Burrows-Wheeler transक्रमmation.  Much of that समय is delay
	resulting from cache misses.

	I would ask that anyone benefiting from this work, especially those
	using it in commercial products, consider making a करोnation to my local
	non-profit hospice organization in the name of the woman I loved, who
	passed away Feb. 12, 2003.

		In memory of Toni W. Hagan

		Hospice of Acadiana, Inc.
		2600 Johnston St., Suite 200
		Lafayette, LA 70503-3240

		Phone (337) 232-1234 or 1-800-738-2226
		Fax   (337) 232-1297

		https://www.hospiceacadiana.com/

	Manuel
 */

/*
	Made it fit क्रम running in Linux Kernel by Alain Knaff (alain@knaff.lu)
*/


#अगर_घोषित STATIC
#घोषणा PREBOOT
#अन्यथा
#समावेश <linux/decompress/bunzip2.h>
#पूर्ण_अगर /* STATIC */

#समावेश <linux/decompress/mm.h>
#समावेश <linux/crc32poly.h>

#अगर_अघोषित पूर्णांक_उच्च
#घोषणा पूर्णांक_उच्च 0x7fffffff
#पूर्ण_अगर

/* Constants क्रम Huffman coding */
#घोषणा MAX_GROUPS		6
#घोषणा GROUP_SIZE   		50	/* 64 would have been more efficient */
#घोषणा MAX_HUFCODE_BITS 	20	/* Longest Huffman code allowed */
#घोषणा MAX_SYMBOLS 		258	/* 256 literals + RUNA + RUNB */
#घोषणा SYMBOL_RUNA		0
#घोषणा SYMBOL_RUNB		1

/* Status वापस values */
#घोषणा RETVAL_OK			0
#घोषणा RETVAL_LAST_BLOCK		(-1)
#घोषणा RETVAL_NOT_BZIP_DATA		(-2)
#घोषणा RETVAL_UNEXPECTED_INPUT_खातापूर्ण	(-3)
#घोषणा RETVAL_UNEXPECTED_OUTPUT_खातापूर्ण	(-4)
#घोषणा RETVAL_DATA_ERROR		(-5)
#घोषणा RETVAL_OUT_OF_MEMORY		(-6)
#घोषणा RETVAL_OBSOLETE_INPUT		(-7)

/* Other housekeeping स्थिरants */
#घोषणा BZIP2_IOBUF_SIZE		4096

/* This is what we know about each Huffman coding group */
काष्ठा group_data अणु
	/* We have an extra slot at the end of limit[] क्रम a sentinal value. */
	पूर्णांक limit[MAX_HUFCODE_BITS+1];
	पूर्णांक base[MAX_HUFCODE_BITS];
	पूर्णांक permute[MAX_SYMBOLS];
	पूर्णांक minLen, maxLen;
पूर्ण;

/* Structure holding all the housekeeping data, including IO buffers and
   memory that persists between calls to bunzip */
काष्ठा bunzip_data अणु
	/* State क्रम पूर्णांकerrupting output loop */
	पूर्णांक ग_लिखोCopies, ग_लिखोPos, ग_लिखोRunCountकरोwn, ग_लिखोCount, ग_लिखोCurrent;
	/* I/O tracking data (file handles, buffers, positions, etc.) */
	दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ);
	दीर्घ inbufCount, inbufPos /*, outbufPos*/;
	अचिन्हित अक्षर *inbuf /*,*outbuf*/;
	अचिन्हित पूर्णांक inbufBitCount, inbufBits;
	/* The CRC values stored in the block header and calculated from the
	data */
	अचिन्हित पूर्णांक crc32Table[256], headerCRC, totalCRC, ग_लिखोCRC;
	/* Intermediate buffer and its size (in bytes) */
	अचिन्हित पूर्णांक *dbuf, dbufSize;
	/* These things are a bit too big to go on the stack */
	अचिन्हित अक्षर selectors[32768];		/* nSelectors = 15 bits */
	काष्ठा group_data groups[MAX_GROUPS];	/* Huffman coding tables */
	पूर्णांक io_error;			/* non-zero अगर we have IO error */
	पूर्णांक byteCount[256];
	अचिन्हित अक्षर symToByte[256], mtfSymbol[256];
पूर्ण;


/* Return the next nnn bits of input.  All पढ़ोs from the compressed input
   are करोne through this function.  All पढ़ोs are big endian */
अटल अचिन्हित पूर्णांक INIT get_bits(काष्ठा bunzip_data *bd, अक्षर bits_wanted)
अणु
	अचिन्हित पूर्णांक bits = 0;

	/* If we need to get more data from the byte buffer, करो so.
	   (Loop getting one byte at a समय to enक्रमce endianness and aव्योम
	   unaligned access.) */
	जबतक (bd->inbufBitCount < bits_wanted) अणु
		/* If we need to पढ़ो more data from file पूर्णांकo byte buffer, करो
		   so */
		अगर (bd->inbufPos == bd->inbufCount) अणु
			अगर (bd->io_error)
				वापस 0;
			bd->inbufCount = bd->fill(bd->inbuf, BZIP2_IOBUF_SIZE);
			अगर (bd->inbufCount <= 0) अणु
				bd->io_error = RETVAL_UNEXPECTED_INPUT_खातापूर्ण;
				वापस 0;
			पूर्ण
			bd->inbufPos = 0;
		पूर्ण
		/* Aव्योम 32-bit overflow (dump bit buffer to top of output) */
		अगर (bd->inbufBitCount >= 24) अणु
			bits = bd->inbufBits&((1 << bd->inbufBitCount)-1);
			bits_wanted -= bd->inbufBitCount;
			bits <<= bits_wanted;
			bd->inbufBitCount = 0;
		पूर्ण
		/* Grab next 8 bits of input from buffer. */
		bd->inbufBits = (bd->inbufBits << 8)|bd->inbuf[bd->inbufPos++];
		bd->inbufBitCount += 8;
	पूर्ण
	/* Calculate result */
	bd->inbufBitCount -= bits_wanted;
	bits |= (bd->inbufBits >> bd->inbufBitCount)&((1 << bits_wanted)-1);

	वापस bits;
पूर्ण

/* Unpacks the next block and sets up क्रम the inverse burrows-wheeler step. */

अटल पूर्णांक INIT get_next_block(काष्ठा bunzip_data *bd)
अणु
	काष्ठा group_data *hufGroup = शून्य;
	पूर्णांक *base = शून्य;
	पूर्णांक *limit = शून्य;
	पूर्णांक dbufCount, nextSym, dbufSize, groupCount, selector,
		i, j, k, t, runPos, symCount, symTotal, nSelectors, *byteCount;
	अचिन्हित अक्षर uc, *symToByte, *mtfSymbol, *selectors;
	अचिन्हित पूर्णांक *dbuf, origPtr;

	dbuf = bd->dbuf;
	dbufSize = bd->dbufSize;
	selectors = bd->selectors;
	byteCount = bd->byteCount;
	symToByte = bd->symToByte;
	mtfSymbol = bd->mtfSymbol;

	/* Read in header signature and CRC, then validate signature.
	   (last block signature means CRC is क्रम whole file, वापस now) */
	i = get_bits(bd, 24);
	j = get_bits(bd, 24);
	bd->headerCRC = get_bits(bd, 32);
	अगर ((i == 0x177245) && (j == 0x385090))
		वापस RETVAL_LAST_BLOCK;
	अगर ((i != 0x314159) || (j != 0x265359))
		वापस RETVAL_NOT_BZIP_DATA;
	/* We can add support क्रम blockRanकरोmised अगर anybody complains.
	   There was some code क्रम this in busybox 1.0.0-pre3, but nobody ever
	   noticed that it didn't actually work. */
	अगर (get_bits(bd, 1))
		वापस RETVAL_OBSOLETE_INPUT;
	origPtr = get_bits(bd, 24);
	अगर (origPtr >= dbufSize)
		वापस RETVAL_DATA_ERROR;
	/* mapping table: अगर some byte values are never used (encoding things
	   like ascii text), the compression code हटाओs the gaps to have fewer
	   symbols to deal with, and ग_लिखोs a sparse bitfield indicating which
	   values were present.  We make a translation table to convert the
	   symbols back to the corresponding bytes. */
	t = get_bits(bd, 16);
	symTotal = 0;
	क्रम (i = 0; i < 16; i++) अणु
		अगर (t&(1 << (15-i))) अणु
			k = get_bits(bd, 16);
			क्रम (j = 0; j < 16; j++)
				अगर (k&(1 << (15-j)))
					symToByte[symTotal++] = (16*i)+j;
		पूर्ण
	पूर्ण
	/* How many dअगरferent Huffman coding groups करोes this block use? */
	groupCount = get_bits(bd, 3);
	अगर (groupCount < 2 || groupCount > MAX_GROUPS)
		वापस RETVAL_DATA_ERROR;
	/* nSelectors: Every GROUP_SIZE many symbols we select a new
	   Huffman coding group.  Read in the group selector list,
	   which is stored as MTF encoded bit runs.  (MTF = Move To
	   Front, as each value is used it's moved to the start of the
	   list.) */
	nSelectors = get_bits(bd, 15);
	अगर (!nSelectors)
		वापस RETVAL_DATA_ERROR;
	क्रम (i = 0; i < groupCount; i++)
		mtfSymbol[i] = i;
	क्रम (i = 0; i < nSelectors; i++) अणु
		/* Get next value */
		क्रम (j = 0; get_bits(bd, 1); j++)
			अगर (j >= groupCount)
				वापस RETVAL_DATA_ERROR;
		/* Decode MTF to get the next selector */
		uc = mtfSymbol[j];
		क्रम (; j; j--)
			mtfSymbol[j] = mtfSymbol[j-1];
		mtfSymbol[0] = selectors[i] = uc;
	पूर्ण
	/* Read the Huffman coding tables क्रम each group, which code
	   क्रम symTotal literal symbols, plus two run symbols (RUNA,
	   RUNB) */
	symCount = symTotal+2;
	क्रम (j = 0; j < groupCount; j++) अणु
		अचिन्हित अक्षर length[MAX_SYMBOLS], temp[MAX_HUFCODE_BITS+1];
		पूर्णांक	minLen,	maxLen, pp;
		/* Read Huffman code lengths क्रम each symbol.  They're
		   stored in a way similar to mtf; record a starting
		   value क्रम the first symbol, and an offset from the
		   previous value क्रम everys symbol after that.
		   (Subtracting 1 beक्रमe the loop and then adding it
		   back at the end is an optimization that makes the
		   test inside the loop simpler: symbol length 0
		   becomes negative, so an अचिन्हित inequality catches
		   it.) */
		t = get_bits(bd, 5)-1;
		क्रम (i = 0; i < symCount; i++) अणु
			क्रम (;;) अणु
				अगर (((अचिन्हित)t) > (MAX_HUFCODE_BITS-1))
					वापस RETVAL_DATA_ERROR;

				/* If first bit is 0, stop.  Else
				   second bit indicates whether to
				   increment or decrement the value.
				   Optimization: grab 2 bits and unget
				   the second अगर the first was 0. */

				k = get_bits(bd, 2);
				अगर (k < 2) अणु
					bd->inbufBitCount++;
					अवरोध;
				पूर्ण
				/* Add one अगर second bit 1, अन्यथा
				 * subtract 1.  Aव्योमs अगर/अन्यथा */
				t += (((k+1)&2)-1);
			पूर्ण
			/* Correct क्रम the initial -1, to get the
			 * final symbol length */
			length[i] = t+1;
		पूर्ण
		/* Find largest and smallest lengths in this group */
		minLen = maxLen = length[0];

		क्रम (i = 1; i < symCount; i++) अणु
			अगर (length[i] > maxLen)
				maxLen = length[i];
			अन्यथा अगर (length[i] < minLen)
				minLen = length[i];
		पूर्ण

		/* Calculate permute[], base[], and limit[] tables from
		 * length[].
		 *
		 * permute[] is the lookup table क्रम converting
		 * Huffman coded symbols पूर्णांकo decoded symbols.  base[]
		 * is the amount to subtract from the value of a
		 * Huffman symbol of a given length when using
		 * permute[].
		 *
		 * limit[] indicates the largest numerical value a
		 * symbol with a given number of bits can have.  This
		 * is how the Huffman codes can vary in length: each
		 * code with a value > limit[length] needs another
		 * bit.
		 */
		hufGroup = bd->groups+j;
		hufGroup->minLen = minLen;
		hufGroup->maxLen = maxLen;
		/* Note that minLen can't be smaller than 1, so we
		   adjust the base and limit array poपूर्णांकers so we're
		   not always wasting the first entry.  We करो this
		   again when using them (during symbol decoding).*/
		base = hufGroup->base-1;
		limit = hufGroup->limit-1;
		/* Calculate permute[].  Concurrently, initialize
		 * temp[] and limit[]. */
		pp = 0;
		क्रम (i = minLen; i <= maxLen; i++) अणु
			temp[i] = limit[i] = 0;
			क्रम (t = 0; t < symCount; t++)
				अगर (length[t] == i)
					hufGroup->permute[pp++] = t;
		पूर्ण
		/* Count symbols coded क्रम at each bit length */
		क्रम (i = 0; i < symCount; i++)
			temp[length[i]]++;
		/* Calculate limit[] (the largest symbol-coding value
		 *at each bit length, which is (previous limit <<
		 *1)+symbols at this level), and base[] (number of
		 *symbols to ignore at each bit length, which is limit
		 *minus the cumulative count of symbols coded क्रम
		 *alपढ़ोy). */
		pp = t = 0;
		क्रम (i = minLen; i < maxLen; i++) अणु
			pp += temp[i];
			/* We पढ़ो the largest possible symbol size
			   and then unget bits after determining how
			   many we need, and those extra bits could be
			   set to anything.  (They're noise from
			   future symbols.)  At each level we're
			   really only पूर्णांकerested in the first few
			   bits, so here we set all the trailing
			   to-be-ignored bits to 1 so they करोn't
			   affect the value > limit[length]
			   comparison. */
			limit[i] = (pp << (maxLen - i)) - 1;
			pp <<= 1;
			base[i+1] = pp-(t += temp[i]);
		पूर्ण
		limit[maxLen+1] = पूर्णांक_उच्च; /* Sentinal value क्रम
					    * पढ़ोing next sym. */
		limit[maxLen] = pp+temp[maxLen]-1;
		base[minLen] = 0;
	पूर्ण
	/* We've finished पढ़ोing and digesting the block header.  Now
	   पढ़ो this block's Huffman coded symbols from the file and
	   unकरो the Huffman coding and run length encoding, saving the
	   result पूर्णांकo dbuf[dbufCount++] = uc */

	/* Initialize symbol occurrence counters and symbol Move To
	 * Front table */
	क्रम (i = 0; i < 256; i++) अणु
		byteCount[i] = 0;
		mtfSymbol[i] = (अचिन्हित अक्षर)i;
	पूर्ण
	/* Loop through compressed symbols. */
	runPos = dbufCount = symCount = selector = 0;
	क्रम (;;) अणु
		/* Determine which Huffman coding group to use. */
		अगर (!(symCount--)) अणु
			symCount = GROUP_SIZE-1;
			अगर (selector >= nSelectors)
				वापस RETVAL_DATA_ERROR;
			hufGroup = bd->groups+selectors[selector++];
			base = hufGroup->base-1;
			limit = hufGroup->limit-1;
		पूर्ण
		/* Read next Huffman-coded symbol. */
		/* Note: It is far cheaper to पढ़ो maxLen bits and
		   back up than it is to पढ़ो minLen bits and then an
		   additional bit at a समय, testing as we go.
		   Because there is a trailing last block (with file
		   CRC), there is no danger of the overपढ़ो causing an
		   unexpected खातापूर्ण क्रम a valid compressed file.  As a
		   further optimization, we करो the पढ़ो अंतरभूत
		   (falling back to a call to get_bits अगर the buffer
		   runs dry).  The following (up to got_huff_bits:) is
		   equivalent to j = get_bits(bd, hufGroup->maxLen);
		 */
		जबतक (bd->inbufBitCount < hufGroup->maxLen) अणु
			अगर (bd->inbufPos == bd->inbufCount) अणु
				j = get_bits(bd, hufGroup->maxLen);
				जाओ got_huff_bits;
			पूर्ण
			bd->inbufBits =
				(bd->inbufBits << 8)|bd->inbuf[bd->inbufPos++];
			bd->inbufBitCount += 8;
		पूर्ण;
		bd->inbufBitCount -= hufGroup->maxLen;
		j = (bd->inbufBits >> bd->inbufBitCount)&
			((1 << hufGroup->maxLen)-1);
got_huff_bits:
		/* Figure how many bits are in next symbol and
		 * unget extras */
		i = hufGroup->minLen;
		जबतक (j > limit[i])
			++i;
		bd->inbufBitCount += (hufGroup->maxLen - i);
		/* Huffman decode value to get nextSym (with bounds checking) */
		अगर ((i > hufGroup->maxLen)
			|| (((अचिन्हित)(j = (j>>(hufGroup->maxLen-i))-base[i]))
				>= MAX_SYMBOLS))
			वापस RETVAL_DATA_ERROR;
		nextSym = hufGroup->permute[j];
		/* We have now decoded the symbol, which indicates
		   either a new literal byte, or a repeated run of the
		   most recent literal byte.  First, check अगर nextSym
		   indicates a repeated run, and अगर so loop collecting
		   how many बार to repeat the last literal. */
		अगर (((अचिन्हित)nextSym) <= SYMBOL_RUNB) अणु /* RUNA or RUNB */
			/* If this is the start of a new run, zero out
			 * counter */
			अगर (!runPos) अणु
				runPos = 1;
				t = 0;
			पूर्ण
			/* Neat trick that saves 1 symbol: instead of
			   or-ing 0 or 1 at each bit position, add 1
			   or 2 instead.  For example, 1011 is 1 << 0
			   + 1 << 1 + 2 << 2.  1010 is 2 << 0 + 2 << 1
			   + 1 << 2.  You can make any bit pattern
			   that way using 1 less symbol than the basic
			   or 0/1 method (except all bits 0, which
			   would use no symbols, but a run of length 0
			   करोesn't mean anything in this context).
			   Thus space is saved. */
			t += (runPos << nextSym);
			/* +runPos अगर RUNA; +2*runPos अगर RUNB */

			runPos <<= 1;
			जारी;
		पूर्ण
		/* When we hit the first non-run symbol after a run,
		   we now know how many बार to repeat the last
		   literal, so append that many copies to our buffer
		   of decoded symbols (dbuf) now.  (The last literal
		   used is the one at the head of the mtfSymbol
		   array.) */
		अगर (runPos) अणु
			runPos = 0;
			अगर (dbufCount+t >= dbufSize)
				वापस RETVAL_DATA_ERROR;

			uc = symToByte[mtfSymbol[0]];
			byteCount[uc] += t;
			जबतक (t--)
				dbuf[dbufCount++] = uc;
		पूर्ण
		/* Is this the terminating symbol? */
		अगर (nextSym > symTotal)
			अवरोध;
		/* At this poपूर्णांक, nextSym indicates a new literal
		   अक्षरacter.  Subtract one to get the position in the
		   MTF array at which this literal is currently to be
		   found.  (Note that the result can't be -1 or 0,
		   because 0 and 1 are RUNA and RUNB.  But another
		   instance of the first symbol in the mtf array,
		   position 0, would have been handled as part of a
		   run above.  Thereक्रमe 1 unused mtf position minus 2
		   non-literal nextSym values equals -1.) */
		अगर (dbufCount >= dbufSize)
			वापस RETVAL_DATA_ERROR;
		i = nextSym - 1;
		uc = mtfSymbol[i];
		/* Adjust the MTF array.  Since we typically expect to
		 *move only a small number of symbols, and are bound
		 *by 256 in any हाल, using स_हटाओ here would
		 *typically be bigger and slower due to function call
		 *overhead and other assorted setup costs. */
		करो अणु
			mtfSymbol[i] = mtfSymbol[i-1];
		पूर्ण जबतक (--i);
		mtfSymbol[0] = uc;
		uc = symToByte[uc];
		/* We have our literal byte.  Save it पूर्णांकo dbuf. */
		byteCount[uc]++;
		dbuf[dbufCount++] = (अचिन्हित पूर्णांक)uc;
	पूर्ण
	/* At this poपूर्णांक, we've पढ़ो all the Huffman-coded symbols
	   (and repeated runs) क्रम this block from the input stream,
	   and decoded them पूर्णांकo the पूर्णांकermediate buffer.  There are
	   dbufCount many decoded bytes in dbuf[].  Now unकरो the
	   Burrows-Wheeler transक्रमm on dbuf.  See
	   http://करोgma.net/markn/articles/bwt/bwt.hपंचांग
	 */
	/* Turn byteCount पूर्णांकo cumulative occurrence counts of 0 to n-1. */
	j = 0;
	क्रम (i = 0; i < 256; i++) अणु
		k = j+byteCount[i];
		byteCount[i] = j;
		j = k;
	पूर्ण
	/* Figure out what order dbuf would be in अगर we sorted it. */
	क्रम (i = 0; i < dbufCount; i++) अणु
		uc = (अचिन्हित अक्षर)(dbuf[i] & 0xff);
		dbuf[byteCount[uc]] |= (i << 8);
		byteCount[uc]++;
	पूर्ण
	/* Decode first byte by hand to initialize "previous" byte.
	   Note that it करोesn't get output, and अगर the first three
	   अक्षरacters are identical it करोesn't qualअगरy as a run (hence
	   ग_लिखोRunCountकरोwn = 5). */
	अगर (dbufCount) अणु
		अगर (origPtr >= dbufCount)
			वापस RETVAL_DATA_ERROR;
		bd->ग_लिखोPos = dbuf[origPtr];
		bd->ग_लिखोCurrent = (अचिन्हित अक्षर)(bd->ग_लिखोPos&0xff);
		bd->ग_लिखोPos >>= 8;
		bd->ग_लिखोRunCountकरोwn = 5;
	पूर्ण
	bd->ग_लिखोCount = dbufCount;

	वापस RETVAL_OK;
पूर्ण

/* Unकरो burrows-wheeler transक्रमm on पूर्णांकermediate buffer to produce output.
   If start_bunzip was initialized with out_fd =-1, then up to len bytes of
   data are written to outbuf.  Return value is number of bytes written or
   error (all errors are negative numbers).  If out_fd!=-1, outbuf and len
   are ignored, data is written to out_fd and वापस is RETVAL_OK or error.
*/

अटल पूर्णांक INIT पढ़ो_bunzip(काष्ठा bunzip_data *bd, अक्षर *outbuf, पूर्णांक len)
अणु
	स्थिर अचिन्हित पूर्णांक *dbuf;
	पूर्णांक pos, xcurrent, previous, gotcount;

	/* If last पढ़ो was लघु due to end of file, वापस last block now */
	अगर (bd->ग_लिखोCount < 0)
		वापस bd->ग_लिखोCount;

	gotcount = 0;
	dbuf = bd->dbuf;
	pos = bd->ग_लिखोPos;
	xcurrent = bd->ग_लिखोCurrent;

	/* We will always have pending decoded data to ग_लिखो पूर्णांकo the output
	   buffer unless this is the very first call (in which हाल we haven't
	   Huffman-decoded a block पूर्णांकo the पूर्णांकermediate buffer yet). */

	अगर (bd->ग_लिखोCopies) अणु
		/* Inside the loop, ग_लिखोCopies means extra copies (beyond 1) */
		--bd->ग_लिखोCopies;
		/* Loop outputting bytes */
		क्रम (;;) अणु
			/* If the output buffer is full, snapshot
			 * state and वापस */
			अगर (gotcount >= len) अणु
				bd->ग_लिखोPos = pos;
				bd->ग_लिखोCurrent = xcurrent;
				bd->ग_लिखोCopies++;
				वापस len;
			पूर्ण
			/* Write next byte पूर्णांकo output buffer, updating CRC */
			outbuf[gotcount++] = xcurrent;
			bd->ग_लिखोCRC = (((bd->ग_लिखोCRC) << 8)
				^bd->crc32Table[((bd->ग_लिखोCRC) >> 24)
				^xcurrent]);
			/* Loop now अगर we're outputting multiple
			 * copies of this byte */
			अगर (bd->ग_लिखोCopies) अणु
				--bd->ग_लिखोCopies;
				जारी;
			पूर्ण
decode_next_byte:
			अगर (!bd->ग_लिखोCount--)
				अवरोध;
			/* Follow sequence vector to unकरो
			 * Burrows-Wheeler transक्रमm */
			previous = xcurrent;
			pos = dbuf[pos];
			xcurrent = pos&0xff;
			pos >>= 8;
			/* After 3 consecutive copies of the same
			   byte, the 4th is a repeat count.  We count
			   करोwn from 4 instead *of counting up because
			   testing क्रम non-zero is faster */
			अगर (--bd->ग_लिखोRunCountकरोwn) अणु
				अगर (xcurrent != previous)
					bd->ग_लिखोRunCountकरोwn = 4;
			पूर्ण अन्यथा अणु
				/* We have a repeated run, this byte
				 * indicates the count */
				bd->ग_लिखोCopies = xcurrent;
				xcurrent = previous;
				bd->ग_लिखोRunCountकरोwn = 5;
				/* Someबार there are just 3 bytes
				 * (run length 0) */
				अगर (!bd->ग_लिखोCopies)
					जाओ decode_next_byte;
				/* Subtract the 1 copy we'd output
				 * anyway to get extras */
				--bd->ग_लिखोCopies;
			पूर्ण
		पूर्ण
		/* Decompression of this block completed successfully */
		bd->ग_लिखोCRC = ~bd->ग_लिखोCRC;
		bd->totalCRC = ((bd->totalCRC << 1) |
				(bd->totalCRC >> 31)) ^ bd->ग_लिखोCRC;
		/* If this block had a CRC error, क्रमce file level CRC error. */
		अगर (bd->ग_लिखोCRC != bd->headerCRC) अणु
			bd->totalCRC = bd->headerCRC+1;
			वापस RETVAL_LAST_BLOCK;
		पूर्ण
	पूर्ण

	/* Refill the पूर्णांकermediate buffer by Huffman-decoding next
	 * block of input */
	/* (previous is just a convenient unused temp variable here) */
	previous = get_next_block(bd);
	अगर (previous) अणु
		bd->ग_लिखोCount = previous;
		वापस (previous != RETVAL_LAST_BLOCK) ? previous : gotcount;
	पूर्ण
	bd->ग_लिखोCRC = 0xffffffffUL;
	pos = bd->ग_लिखोPos;
	xcurrent = bd->ग_लिखोCurrent;
	जाओ decode_next_byte;
पूर्ण

अटल दीर्घ INIT nofill(व्योम *buf, अचिन्हित दीर्घ len)
अणु
	वापस -1;
पूर्ण

/* Allocate the काष्ठाure, पढ़ो file header.  If in_fd ==-1, inbuf must contain
   a complete bunzip file (len bytes दीर्घ).  If in_fd!=-1, inbuf and len are
   ignored, and data is पढ़ो from file handle पूर्णांकo temporary buffer. */
अटल पूर्णांक INIT start_bunzip(काष्ठा bunzip_data **bdp, व्योम *inbuf, दीर्घ len,
			     दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ))
अणु
	काष्ठा bunzip_data *bd;
	अचिन्हित पूर्णांक i, j, c;
	स्थिर अचिन्हित पूर्णांक BZh0 =
		(((अचिन्हित पूर्णांक)'B') << 24)+(((unsigned int)'Z') << 16)
		+(((अचिन्हित पूर्णांक)'h') << 8)+(unsigned int)'0';

	/* Figure out how much data to allocate */
	i = माप(काष्ठा bunzip_data);

	/* Allocate bunzip_data.  Most fields initialize to zero. */
	bd = *bdp = दो_स्मृति(i);
	अगर (!bd)
		वापस RETVAL_OUT_OF_MEMORY;
	स_रखो(bd, 0, माप(काष्ठा bunzip_data));
	/* Setup input buffer */
	bd->inbuf = inbuf;
	bd->inbufCount = len;
	अगर (fill != शून्य)
		bd->fill = fill;
	अन्यथा
		bd->fill = nofill;

	/* Init the CRC32 table (big endian) */
	क्रम (i = 0; i < 256; i++) अणु
		c = i << 24;
		क्रम (j = 8; j; j--)
			c = c&0x80000000 ? (c << 1)^(CRC32_POLY_BE) : (c << 1);
		bd->crc32Table[i] = c;
	पूर्ण

	/* Ensure that file starts with "BZh['1'-'9']." */
	i = get_bits(bd, 32);
	अगर (((अचिन्हित पूर्णांक)(i-BZh0-1)) >= 9)
		वापस RETVAL_NOT_BZIP_DATA;

	/* Fourth byte (ascii '1'-'9'), indicates block size in units of 100k of
	   uncompressed data.  Allocate पूर्णांकermediate buffer क्रम block. */
	bd->dbufSize = 100000*(i-BZh0);

	bd->dbuf = large_दो_स्मृति(bd->dbufSize * माप(पूर्णांक));
	अगर (!bd->dbuf)
		वापस RETVAL_OUT_OF_MEMORY;
	वापस RETVAL_OK;
पूर्ण

/* Example usage: decompress src_fd to dst_fd.  (Stops at end of bzip2 data,
   not end of file.) */
STATIC पूर्णांक INIT bunzip2(अचिन्हित अक्षर *buf, दीर्घ len,
			दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			अचिन्हित अक्षर *outbuf,
			दीर्घ *pos,
			व्योम(*error)(अक्षर *x))
अणु
	काष्ठा bunzip_data *bd;
	पूर्णांक i = -1;
	अचिन्हित अक्षर *inbuf;

	अगर (flush)
		outbuf = दो_स्मृति(BZIP2_IOBUF_SIZE);

	अगर (!outbuf) अणु
		error("Could not allocate output buffer");
		वापस RETVAL_OUT_OF_MEMORY;
	पूर्ण
	अगर (buf)
		inbuf = buf;
	अन्यथा
		inbuf = दो_स्मृति(BZIP2_IOBUF_SIZE);
	अगर (!inbuf) अणु
		error("Could not allocate input buffer");
		i = RETVAL_OUT_OF_MEMORY;
		जाओ निकास_0;
	पूर्ण
	i = start_bunzip(&bd, inbuf, len, fill);
	अगर (!i) अणु
		क्रम (;;) अणु
			i = पढ़ो_bunzip(bd, outbuf, BZIP2_IOBUF_SIZE);
			अगर (i <= 0)
				अवरोध;
			अगर (!flush)
				outbuf += i;
			अन्यथा
				अगर (i != flush(outbuf, i)) अणु
					i = RETVAL_UNEXPECTED_OUTPUT_खातापूर्ण;
					अवरोध;
				पूर्ण
		पूर्ण
	पूर्ण
	/* Check CRC and release memory */
	अगर (i == RETVAL_LAST_BLOCK) अणु
		अगर (bd->headerCRC != bd->totalCRC)
			error("Data integrity error when decompressing.");
		अन्यथा
			i = RETVAL_OK;
	पूर्ण अन्यथा अगर (i == RETVAL_UNEXPECTED_OUTPUT_खातापूर्ण) अणु
		error("Compressed file ends unexpectedly");
	पूर्ण
	अगर (!bd)
		जाओ निकास_1;
	अगर (bd->dbuf)
		large_मुक्त(bd->dbuf);
	अगर (pos)
		*pos = bd->inbufPos;
	मुक्त(bd);
निकास_1:
	अगर (!buf)
		मुक्त(inbuf);
निकास_0:
	अगर (flush)
		मुक्त(outbuf);
	वापस i;
पूर्ण

#अगर_घोषित PREBOOT
STATIC पूर्णांक INIT __decompress(अचिन्हित अक्षर *buf, दीर्घ len,
			दीर्घ (*fill)(व्योम*, अचिन्हित दीर्घ),
			दीर्घ (*flush)(व्योम*, अचिन्हित दीर्घ),
			अचिन्हित अक्षर *outbuf, दीर्घ olen,
			दीर्घ *pos,
			व्योम (*error)(अक्षर *x))
अणु
	वापस bunzip2(buf, len - 4, fill, flush, outbuf, pos, error);
पूर्ण
#पूर्ण_अगर
