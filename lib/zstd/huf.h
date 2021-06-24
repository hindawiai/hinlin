<शैली गुरु>
/*
 * Huffman coder, part of New Generation Entropy library
 * header file
 * Copyright (C) 2013-2016, Yann Collet.
 *
 * BSD 2-Clause License (http://www.खोलोsource.org/licenses/bsd-license.php)
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the करोcumentation and/or other materials provided with the
 * distribution.
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
 * This program is मुक्त software; you can redistribute it and/or modअगरy it under
 * the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation. This program is dual-licensed; you may select
 * either version 2 of the GNU General Public License ("GPL") or BSD license
 * ("BSD").
 *
 * You can contact the author at :
 * - Source repository : https://github.com/Cyan4973/FiniteStateEntropy
 */
#अगर_अघोषित HUF_H_298734234
#घोषणा HUF_H_298734234

/* *** Dependencies *** */
#समावेश <linux/types.h> /* माप_प्रकार */

/* ***   Tool functions *** */
#घोषणा HUF_BLOCKSIZE_MAX (128 * 1024) /**< maximum input size क्रम a single block compressed with HUF_compress */
माप_प्रकार HUF_compressBound(माप_प्रकार size); /**< maximum compressed size (worst हाल) */

/* Error Management */
अचिन्हित HUF_isError(माप_प्रकार code); /**< tells अगर a वापस value is an error code */

/* ***   Advanced function   *** */

/** HUF_compress4X_wksp() :
*   Same as HUF_compress2(), but uses बाह्यally allocated `workSpace`, which must be a table of >= 1024 अचिन्हित */
माप_प्रकार HUF_compress4X_wksp(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित tableLog, व्योम *workSpace,
			   माप_प्रकार wkspSize); /**< `workSpace` must be a table of at least HUF_COMPRESS_WORKSPACE_SIZE_U32 अचिन्हित */

/* *** Dependencies *** */
#समावेश "mem.h" /* U32 */

/* *** Constants *** */
#घोषणा HUF_TABLELOG_MAX 12     /* max configured tableLog (क्रम अटल allocation); can be modअगरied up to HUF_ABSOLUTEMAX_TABLELOG */
#घोषणा HUF_TABLELOG_DEFAULT 11 /* tableLog by शेष, when not specअगरied */
#घोषणा HUF_SYMBOLVALUE_MAX 255

#घोषणा HUF_TABLELOG_ABSOLUTEMAX 15 /* असलolute limit of HUF_MAX_TABLELOG. Beyond that value, code करोes not work */
#अगर (HUF_TABLELOG_MAX > HUF_TABLELOG_ABSOLUTEMAX)
#त्रुटि "HUF_TABLELOG_MAX is too large !"
#पूर्ण_अगर

/* ****************************************
*  Static allocation
******************************************/
/* HUF buffer bounds */
#घोषणा HUF_CTABLEBOUND 129
#घोषणा HUF_BLOCKBOUND(size) (size + (size >> 8) + 8)			 /* only true अगर incompressible pre-filtered with fast heuristic */
#घोषणा HUF_COMPRESSBOUND(size) (HUF_CTABLEBOUND + HUF_BLOCKBOUND(size)) /* Macro version, useful क्रम अटल allocation */

/* अटल allocation of HUF's Compression Table */
#घोषणा HUF_CREATE_STATIC_CTABLE(name, maxSymbolValue) \
	U32 name##hb[maxSymbolValue + 1];              \
	व्योम *name##hv = &(name##hb);                  \
	HUF_CElt *name = (HUF_CElt *)(name##hv) /* no final ; */

/* अटल allocation of HUF's DTable */
प्रकार U32 HUF_DTable;
#घोषणा HUF_DTABLE_SIZE(maxTableLog) (1 + (1 << (maxTableLog)))
#घोषणा HUF_CREATE_STATIC_DTABLEX2(DTable, maxTableLog) HUF_DTable DTable[HUF_DTABLE_SIZE((maxTableLog)-1)] = अणु((U32)((maxTableLog)-1) * 0x01000001)पूर्ण
#घोषणा HUF_CREATE_STATIC_DTABLEX4(DTable, maxTableLog) HUF_DTable DTable[HUF_DTABLE_SIZE(maxTableLog)] = अणु((U32)(maxTableLog)*0x01000001)पूर्ण

/* The workspace must have alignment at least 4 and be at least this large */
#घोषणा HUF_COMPRESS_WORKSPACE_SIZE (6 << 10)
#घोषणा HUF_COMPRESS_WORKSPACE_SIZE_U32 (HUF_COMPRESS_WORKSPACE_SIZE / माप(U32))

/* The workspace must have alignment at least 4 and be at least this large */
#घोषणा HUF_DECOMPRESS_WORKSPACE_SIZE (3 << 10)
#घोषणा HUF_DECOMPRESS_WORKSPACE_SIZE_U32 (HUF_DECOMPRESS_WORKSPACE_SIZE / माप(U32))

/* ****************************************
*  Advanced decompression functions
******************************************/
माप_प्रकार HUF_decompress4X_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace, माप_प्रकार workspaceSize); /**< decodes RLE and uncompressed */
माप_प्रकार HUF_decompress4X_hufOnly_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace,
				माप_प्रकार workspaceSize);							       /**< considers RLE and uncompressed as errors */
माप_प्रकार HUF_decompress4X2_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace,
				   माप_प्रकार workspaceSize); /**< single-symbol decoder */
माप_प्रकार HUF_decompress4X4_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace,
				   माप_प्रकार workspaceSize); /**< द्विगुन-symbols decoder */

/* ****************************************
*  HUF detailed API
******************************************/
/*!
HUF_compress() करोes the following:
1. count symbol occurrence from source[] पूर्णांकo table count[] using FSE_count()
2. (optional) refine tableLog using HUF_optimalTableLog()
3. build Huffman table from count using HUF_buildCTable()
4. save Huffman table to memory buffer using HUF_ग_लिखोCTable_wksp()
5. encode the data stream using HUF_compress4X_usingCTable()

The following API allows targeting specअगरic sub-functions क्रम advanced tasks.
For example, it's possible to compress several blocks using the same 'CTable',
or to save and regenerate 'CTable' using बाह्यal methods.
*/
/* FSE_count() : find it within "fse.h" */
अचिन्हित HUF_optimalTableLog(अचिन्हित maxTableLog, माप_प्रकार srcSize, अचिन्हित maxSymbolValue);
प्रकार काष्ठा HUF_CElt_s HUF_CElt; /* incomplete type */
माप_प्रकार HUF_ग_लिखोCTable_wksp(व्योम *dst, माप_प्रकार maxDstSize, स्थिर HUF_CElt *CTable, अचिन्हित maxSymbolValue, अचिन्हित huffLog, व्योम *workspace, माप_प्रकार workspaceSize);
माप_प्रकार HUF_compress4X_usingCTable(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर HUF_CElt *CTable);

प्रकार क्रमागत अणु
	HUF_repeat_none,  /**< Cannot use the previous table */
	HUF_repeat_check, /**< Can use the previous table but it must be checked. Note : The previous table must have been स्थिरructed by HUF_compressअणु1,
			     4पूर्णX_repeat */
	HUF_repeat_valid  /**< Can use the previous table and it is asumed to be valid */
पूर्ण HUF_repeat;
/** HUF_compress4X_repeat() :
*   Same as HUF_compress4X_wksp(), but considers using hufTable अगर *repeat != HUF_repeat_none.
*   If it uses hufTable it करोes not modअगरy hufTable or repeat.
*   If it करोesn't, it sets *repeat = HUF_repeat_none, and it sets hufTable to the table used.
*   If preferRepeat then the old table will always be used अगर valid. */
माप_प्रकार HUF_compress4X_repeat(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित tableLog, व्योम *workSpace,
			     माप_प्रकार wkspSize, HUF_CElt *hufTable, HUF_repeat *repeat,
			     पूर्णांक preferRepeat); /**< `workSpace` must be a table of at least HUF_COMPRESS_WORKSPACE_SIZE_U32 अचिन्हित */

/** HUF_buildCTable_wksp() :
 *  Same as HUF_buildCTable(), but using बाह्यally allocated scratch buffer.
 *  `workSpace` must be aligned on 4-bytes boundaries, and be at least as large as a table of 1024 अचिन्हित.
 */
माप_प्रकार HUF_buildCTable_wksp(HUF_CElt *tree, स्थिर U32 *count, U32 maxSymbolValue, U32 maxNbBits, व्योम *workSpace, माप_प्रकार wkspSize);

/*! HUF_पढ़ोStats() :
	Read compact Huffman tree, saved by HUF_ग_लिखोCTable().
	`huffWeight` is destination buffer.
	@वापस : size पढ़ो from `src` , or an error Code .
	Note : Needed by HUF_पढ़ोCTable() and HUF_पढ़ोDTableXn() . */
माप_प्रकार HUF_पढ़ोStats_wksp(BYTE *huffWeight, माप_प्रकार hwSize, U32 *rankStats, U32 *nbSymbolsPtr, U32 *tableLogPtr, स्थिर व्योम *src, माप_प्रकार srcSize,
			  व्योम *workspace, माप_प्रकार workspaceSize);

/** HUF_पढ़ोCTable() :
*   Loading a CTable saved with HUF_ग_लिखोCTable() */
माप_प्रकार HUF_पढ़ोCTable_wksp(HUF_CElt *CTable, अचिन्हित maxSymbolValue, स्थिर व्योम *src, माप_प्रकार srcSize, व्योम *workspace, माप_प्रकार workspaceSize);

/*
HUF_decompress() करोes the following:
1. select the decompression algorithm (X2, X4) based on pre-computed heuristics
2. build Huffman table from save, using HUF_पढ़ोDTableXn()
3. decode 1 or 4 segments in parallel using HUF_decompressSXn_usingDTable
*/

/** HUF_selectDecoder() :
*   Tells which decoder is likely to decode faster,
*   based on a set of pre-determined metrics.
*   @वापस : 0==HUF_decompress4X2, 1==HUF_decompress4X4 .
*   Assumption : 0 < cSrcSize < dstSize <= 128 KB */
U32 HUF_selectDecoder(माप_प्रकार dstSize, माप_प्रकार cSrcSize);

माप_प्रकार HUF_पढ़ोDTableX2_wksp(HUF_DTable *DTable, स्थिर व्योम *src, माप_प्रकार srcSize, व्योम *workspace, माप_प्रकार workspaceSize);
माप_प्रकार HUF_पढ़ोDTableX4_wksp(HUF_DTable *DTable, स्थिर व्योम *src, माप_प्रकार srcSize, व्योम *workspace, माप_प्रकार workspaceSize);

माप_प्रकार HUF_decompress4X_usingDTable(व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable);
माप_प्रकार HUF_decompress4X2_usingDTable(व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable);
माप_प्रकार HUF_decompress4X4_usingDTable(व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable);

/* single stream variants */

माप_प्रकार HUF_compress1X_wksp(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित tableLog, व्योम *workSpace,
			   माप_प्रकार wkspSize); /**< `workSpace` must be a table of at least HUF_COMPRESS_WORKSPACE_SIZE_U32 अचिन्हित */
माप_प्रकार HUF_compress1X_usingCTable(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, स्थिर HUF_CElt *CTable);
/** HUF_compress1X_repeat() :
*   Same as HUF_compress1X_wksp(), but considers using hufTable अगर *repeat != HUF_repeat_none.
*   If it uses hufTable it करोes not modअगरy hufTable or repeat.
*   If it करोesn't, it sets *repeat = HUF_repeat_none, and it sets hufTable to the table used.
*   If preferRepeat then the old table will always be used अगर valid. */
माप_प्रकार HUF_compress1X_repeat(व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *src, माप_प्रकार srcSize, अचिन्हित maxSymbolValue, अचिन्हित tableLog, व्योम *workSpace,
			     माप_प्रकार wkspSize, HUF_CElt *hufTable, HUF_repeat *repeat,
			     पूर्णांक preferRepeat); /**< `workSpace` must be a table of at least HUF_COMPRESS_WORKSPACE_SIZE_U32 अचिन्हित */

माप_प्रकार HUF_decompress1X_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace, माप_प्रकार workspaceSize);
माप_प्रकार HUF_decompress1X2_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace,
				   माप_प्रकार workspaceSize); /**< single-symbol decoder */
माप_प्रकार HUF_decompress1X4_DCtx_wksp(HUF_DTable *dctx, व्योम *dst, माप_प्रकार dstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, व्योम *workspace,
				   माप_प्रकार workspaceSize); /**< द्विगुन-symbols decoder */

माप_प्रकार HUF_decompress1X_usingDTable(व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize,
				    स्थिर HUF_DTable *DTable); /**< स्वतःmatic selection of sing or द्विगुन symbol decoder, based on DTable */
माप_प्रकार HUF_decompress1X2_usingDTable(व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable);
माप_प्रकार HUF_decompress1X4_usingDTable(व्योम *dst, माप_प्रकार maxDstSize, स्थिर व्योम *cSrc, माप_प्रकार cSrcSize, स्थिर HUF_DTable *DTable);

#पूर्ण_अगर /* HUF_H_298734234 */
