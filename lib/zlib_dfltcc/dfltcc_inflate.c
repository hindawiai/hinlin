<शैली गुरु>
// SPDX-License-Identअगरier: Zlib

#समावेश "../zlib_inflate/inflate.h"
#समावेश "dfltcc_util.h"
#समावेश "dfltcc.h"
#समावेश <यंत्र/setup.h>
#समावेश <linux/export.h>
#समावेश <linux/zutil.h>

/*
 * Expand.
 */
पूर्णांक dfltcc_can_inflate(
    z_streamp strm
)
अणु
    काष्ठा inflate_state *state = (काष्ठा inflate_state *)strm->state;
    काष्ठा dfltcc_state *dfltcc_state = GET_DFLTCC_STATE(state);

    /* Check क्रम kernel dfltcc command line parameter */
    अगर (zlib_dfltcc_support == ZLIB_DFLTCC_DISABLED ||
            zlib_dfltcc_support == ZLIB_DFLTCC_DEFLATE_ONLY)
        वापस 0;

    /* Unsupported compression settings */
    अगर (state->wbits != HB_BITS)
        वापस 0;

    /* Unsupported hardware */
    वापस is_bit_set(dfltcc_state->af.fns, DFLTCC_XPND) &&
               is_bit_set(dfltcc_state->af.fmts, DFLTCC_FMT0);
पूर्ण
EXPORT_SYMBOL(dfltcc_can_inflate);

अटल पूर्णांक dfltcc_was_inflate_used(
    z_streamp strm
)
अणु
    काष्ठा inflate_state *state = (काष्ठा inflate_state *)strm->state;
    काष्ठा dfltcc_param_v0 *param = &GET_DFLTCC_STATE(state)->param;

    वापस !param->nt;
पूर्ण

अटल पूर्णांक dfltcc_inflate_disable(
    z_streamp strm
)
अणु
    काष्ठा inflate_state *state = (काष्ठा inflate_state *)strm->state;
    काष्ठा dfltcc_state *dfltcc_state = GET_DFLTCC_STATE(state);

    अगर (!dfltcc_can_inflate(strm))
        वापस 0;
    अगर (dfltcc_was_inflate_used(strm))
        /* DFLTCC has alपढ़ोy decompressed some data. Since there is not
         * enough inक्रमmation to resume decompression in software, the call
         * must fail.
         */
        वापस 1;
    /* DFLTCC was not used yet - decompress in software */
    स_रखो(&dfltcc_state->af, 0, माप(dfltcc_state->af));
    वापस 0;
पूर्ण

अटल dfltcc_cc dfltcc_xpnd(
    z_streamp strm
)
अणु
    काष्ठा inflate_state *state = (काष्ठा inflate_state *)strm->state;
    काष्ठा dfltcc_param_v0 *param = &GET_DFLTCC_STATE(state)->param;
    माप_प्रकार avail_in = strm->avail_in;
    माप_प्रकार avail_out = strm->avail_out;
    dfltcc_cc cc;

    cc = dfltcc(DFLTCC_XPND | HBT_CIRCULAR,
                param, &strm->next_out, &avail_out,
                &strm->next_in, &avail_in, state->winकरोw);
    strm->avail_in = avail_in;
    strm->avail_out = avail_out;
    वापस cc;
पूर्ण

dfltcc_inflate_action dfltcc_inflate(
    z_streamp strm,
    पूर्णांक flush,
    पूर्णांक *ret
)
अणु
    काष्ठा inflate_state *state = (काष्ठा inflate_state *)strm->state;
    काष्ठा dfltcc_state *dfltcc_state = GET_DFLTCC_STATE(state);
    काष्ठा dfltcc_param_v0 *param = &dfltcc_state->param;
    dfltcc_cc cc;

    अगर (flush == Z_BLOCK) अणु
        /* DFLTCC करोes not support stopping on block boundaries */
        अगर (dfltcc_inflate_disable(strm)) अणु
            *ret = Z_STREAM_ERROR;
            वापस DFLTCC_INFLATE_BREAK;
        पूर्ण अन्यथा
            वापस DFLTCC_INFLATE_SOFTWARE;
    पूर्ण

    अगर (state->last) अणु
        अगर (state->bits != 0) अणु
            strm->next_in++;
            strm->avail_in--;
            state->bits = 0;
        पूर्ण
        state->mode = CHECK;
        वापस DFLTCC_INFLATE_CONTINUE;
    पूर्ण

    अगर (strm->avail_in == 0 && !param->cf)
        वापस DFLTCC_INFLATE_BREAK;

    अगर (!state->winकरोw || state->wsize == 0) अणु
        state->mode = MEM;
        वापस DFLTCC_INFLATE_CONTINUE;
    पूर्ण

    /* Translate stream to parameter block */
    param->cvt = CVT_ADLER32;
    param->sbb = state->bits;
    param->hl = state->whave; /* Software and hardware history क्रमmats match */
    param->ho = (state->ग_लिखो - state->whave) & ((1 << HB_BITS) - 1);
    अगर (param->hl)
        param->nt = 0; /* Honor history क्रम the first block */
    param->cv = state->check;

    /* Inflate */
    करो अणु
        cc = dfltcc_xpnd(strm);
    पूर्ण जबतक (cc == DFLTCC_CC_AGAIN);

    /* Translate parameter block to stream */
    strm->msg = oesc_msg(dfltcc_state->msg, param->oesc);
    state->last = cc == DFLTCC_CC_OK;
    state->bits = param->sbb;
    state->whave = param->hl;
    state->ग_लिखो = (param->ho + param->hl) & ((1 << HB_BITS) - 1);
    state->check = param->cv;
    अगर (cc == DFLTCC_CC_OP2_CORRUPT && param->oesc != 0) अणु
        /* Report an error अगर stream is corrupted */
        state->mode = BAD;
        वापस DFLTCC_INFLATE_CONTINUE;
    पूर्ण
    state->mode = TYPEDO;
    /* Break अगर opeअक्रमs are exhausted, otherwise जारी looping */
    वापस (cc == DFLTCC_CC_OP1_TOO_SHORT || cc == DFLTCC_CC_OP2_TOO_SHORT) ?
        DFLTCC_INFLATE_BREAK : DFLTCC_INFLATE_CONTINUE;
पूर्ण
EXPORT_SYMBOL(dfltcc_inflate);
