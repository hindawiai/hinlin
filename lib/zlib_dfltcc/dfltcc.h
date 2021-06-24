<शैली गुरु>
// SPDX-License-Identअगरier: Zlib
#अगर_अघोषित DFLTCC_H
#घोषणा DFLTCC_H

#समावेश "../zlib_deflate/defutil.h"
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/setup.h>

/*
 * Tuning parameters.
 */
#घोषणा DFLTCC_LEVEL_MASK 0x2 /* DFLTCC compression क्रम level 1 only */
#घोषणा DFLTCC_LEVEL_MASK_DEBUG 0x3fe /* DFLTCC compression क्रम all levels */
#घोषणा DFLTCC_BLOCK_SIZE 1048576
#घोषणा DFLTCC_FIRST_FHT_BLOCK_SIZE 4096
#घोषणा DFLTCC_DHT_MIN_SAMPLE_SIZE 4096
#घोषणा DFLTCC_RIBM 0

#घोषणा DFLTCC_FACILITY 151

/*
 * Parameter Block क्रम Query Available Functions.
 */
काष्ठा dfltcc_qaf_param अणु
    अक्षर fns[16];
    अक्षर reserved1[8];
    अक्षर fmts[2];
    अक्षर reserved2[6];
पूर्ण;

अटल_निश्चित(माप(काष्ठा dfltcc_qaf_param) == 32);

#घोषणा DFLTCC_FMT0 0

/*
 * Parameter Block क्रम Generate Dynamic-Huffman Table, Compress and Expand.
 */
काष्ठा dfltcc_param_v0 अणु
    uपूर्णांक16_t pbvn;                     /* Parameter-Block-Version Number */
    uपूर्णांक8_t mvn;                       /* Model-Version Number */
    uपूर्णांक8_t ribm;                      /* Reserved क्रम IBM use */
    अचिन्हित reserved32 : 31;
    अचिन्हित cf : 1;                   /* Continuation Flag */
    uपूर्णांक8_t reserved64[8];
    अचिन्हित nt : 1;                   /* New Task */
    अचिन्हित reserved129 : 1;
    अचिन्हित cvt : 1;                  /* Check Value Type */
    अचिन्हित reserved131 : 1;
    अचिन्हित htt : 1;                  /* Huffman-Table Type */
    अचिन्हित bcf : 1;                  /* Block-Continuation Flag */
    अचिन्हित bcc : 1;                  /* Block Closing Control */
    अचिन्हित bhf : 1;                  /* Block Header Final */
    अचिन्हित reserved136 : 1;
    अचिन्हित reserved137 : 1;
    अचिन्हित dhtgc : 1;                /* DHT Generation Control */
    अचिन्हित reserved139 : 5;
    अचिन्हित reserved144 : 5;
    अचिन्हित sbb : 3;                  /* Sub-Byte Boundary */
    uपूर्णांक8_t oesc;                      /* Operation-Ending-Supplemental Code */
    अचिन्हित reserved160 : 12;
    अचिन्हित अगरs : 4;                  /* Incomplete-Function Status */
    uपूर्णांक16_t अगरl;                      /* Incomplete-Function Length */
    uपूर्णांक8_t reserved192[8];
    uपूर्णांक8_t reserved256[8];
    uपूर्णांक8_t reserved320[4];
    uपूर्णांक16_t hl;                       /* History Length */
    अचिन्हित reserved368 : 1;
    uपूर्णांक16_t ho : 15;                  /* History Offset */
    uपूर्णांक32_t cv;                       /* Check Value */
    अचिन्हित eobs : 15;                /* End-of-block Symbol */
    अचिन्हित reserved431: 1;
    uपूर्णांक8_t eobl : 4;                  /* End-of-block Length */
    अचिन्हित reserved436 : 12;
    अचिन्हित reserved448 : 4;
    uपूर्णांक16_t cdhtl : 12;               /* Compressed-Dynamic-Huffman Table
                                          Length */
    uपूर्णांक8_t reserved464[6];
    uपूर्णांक8_t cdht[288];
    uपूर्णांक8_t reserved[32];
    uपूर्णांक8_t csb[1152];
पूर्ण;

अटल_निश्चित(माप(काष्ठा dfltcc_param_v0) == 1536);

#घोषणा CVT_CRC32 0
#घोषणा CVT_ADLER32 1
#घोषणा HTT_FIXED 0
#घोषणा HTT_DYNAMIC 1

/*
 *  Extension of inflate_state and deflate_state क्रम DFLTCC.
 */
काष्ठा dfltcc_state अणु
    काष्ठा dfltcc_param_v0 param;      /* Parameter block */
    काष्ठा dfltcc_qaf_param af;        /* Available functions */
    uLong level_mask;                  /* Levels on which to use DFLTCC */
    uLong block_size;                  /* New block each X bytes */
    uLong block_threshold;             /* New block after total_in > X */
    uLong dht_threshold;               /* New block only अगर avail_in >= X */
    अक्षर msg[64];                      /* Buffer क्रम strm->msg */
पूर्ण;

/* Resides right after inflate_state or deflate_state */
#घोषणा GET_DFLTCC_STATE(state) ((काष्ठा dfltcc_state *)((state) + 1))

/* External functions */
पूर्णांक dfltcc_can_deflate(z_streamp strm);
पूर्णांक dfltcc_deflate(z_streamp strm,
                   पूर्णांक flush,
                   block_state *result);
व्योम dfltcc_reset(z_streamp strm, uInt size);
पूर्णांक dfltcc_can_inflate(z_streamp strm);
प्रकार क्रमागत अणु
    DFLTCC_INFLATE_CONTINUE,
    DFLTCC_INFLATE_BREAK,
    DFLTCC_INFLATE_SOFTWARE,
पूर्ण dfltcc_inflate_action;
dfltcc_inflate_action dfltcc_inflate(z_streamp strm,
                                     पूर्णांक flush, पूर्णांक *ret);
अटल अंतरभूत पूर्णांक is_dfltcc_enabled(व्योम)
अणु
वापस (zlib_dfltcc_support != ZLIB_DFLTCC_DISABLED &&
        test_facility(DFLTCC_FACILITY));
पूर्ण

#घोषणा DEFLATE_RESET_HOOK(strm) \
    dfltcc_reset((strm), माप(deflate_state))

#घोषणा DEFLATE_HOOK dfltcc_deflate

#घोषणा DEFLATE_NEED_CHECKSUM(strm) (!dfltcc_can_deflate((strm)))

#घोषणा DEFLATE_DFLTCC_ENABLED() is_dfltcc_enabled()

#घोषणा INFLATE_RESET_HOOK(strm) \
    dfltcc_reset((strm), माप(काष्ठा inflate_state))

#घोषणा INFLATE_TYPEDO_HOOK(strm, flush) \
    अगर (dfltcc_can_inflate((strm))) अणु \
        dfltcc_inflate_action action; \
\
        RESTORE(); \
        action = dfltcc_inflate((strm), (flush), &ret); \
        LOAD(); \
        अगर (action == DFLTCC_INFLATE_CONTINUE) \
            अवरोध; \
        अन्यथा अगर (action == DFLTCC_INFLATE_BREAK) \
            जाओ inf_leave; \
    पूर्ण

#घोषणा INFLATE_NEED_CHECKSUM(strm) (!dfltcc_can_inflate((strm)))

#घोषणा INFLATE_NEED_UPDATEWINDOW(strm) (!dfltcc_can_inflate((strm)))

#पूर्ण_अगर /* DFLTCC_H */
