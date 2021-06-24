<शैली गुरु>
// SPDX-License-Identअगरier: Zlib

#समावेश "../zlib_deflate/defutil.h"
#समावेश "dfltcc_util.h"
#समावेश "dfltcc.h"
#समावेश <यंत्र/setup.h>
#समावेश <linux/export.h>
#समावेश <linux/zutil.h>

/*
 * Compress.
 */
पूर्णांक dfltcc_can_deflate(
    z_streamp strm
)
अणु
    deflate_state *state = (deflate_state *)strm->state;
    काष्ठा dfltcc_state *dfltcc_state = GET_DFLTCC_STATE(state);

    /* Check क्रम kernel dfltcc command line parameter */
    अगर (zlib_dfltcc_support == ZLIB_DFLTCC_DISABLED ||
            zlib_dfltcc_support == ZLIB_DFLTCC_INFLATE_ONLY)
        वापस 0;

    /* Unsupported compression settings */
    अगर (!dfltcc_are_params_ok(state->level, state->w_bits, state->strategy,
                              dfltcc_state->level_mask))
        वापस 0;

    /* Unsupported hardware */
    अगर (!is_bit_set(dfltcc_state->af.fns, DFLTCC_GDHT) ||
            !is_bit_set(dfltcc_state->af.fns, DFLTCC_CMPR) ||
            !is_bit_set(dfltcc_state->af.fmts, DFLTCC_FMT0))
        वापस 0;

    वापस 1;
पूर्ण
EXPORT_SYMBOL(dfltcc_can_deflate);

अटल व्योम dfltcc_gdht(
    z_streamp strm
)
अणु
    deflate_state *state = (deflate_state *)strm->state;
    काष्ठा dfltcc_param_v0 *param = &GET_DFLTCC_STATE(state)->param;
    माप_प्रकार avail_in = avail_in = strm->avail_in;

    dfltcc(DFLTCC_GDHT,
           param, शून्य, शून्य,
           &strm->next_in, &avail_in, शून्य);
पूर्ण

अटल dfltcc_cc dfltcc_cmpr(
    z_streamp strm
)
अणु
    deflate_state *state = (deflate_state *)strm->state;
    काष्ठा dfltcc_param_v0 *param = &GET_DFLTCC_STATE(state)->param;
    माप_प्रकार avail_in = strm->avail_in;
    माप_प्रकार avail_out = strm->avail_out;
    dfltcc_cc cc;

    cc = dfltcc(DFLTCC_CMPR | HBT_CIRCULAR,
                param, &strm->next_out, &avail_out,
                &strm->next_in, &avail_in, state->winकरोw);
    strm->total_in += (strm->avail_in - avail_in);
    strm->total_out += (strm->avail_out - avail_out);
    strm->avail_in = avail_in;
    strm->avail_out = avail_out;
    वापस cc;
पूर्ण

अटल व्योम send_eobs(
    z_streamp strm,
    स्थिर काष्ठा dfltcc_param_v0 *param
)
अणु
    deflate_state *state = (deflate_state *)strm->state;

    zlib_tr_send_bits(
          state,
          bi_reverse(param->eobs >> (15 - param->eobl), param->eobl),
          param->eobl);
    flush_pending(strm);
    अगर (state->pending != 0) अणु
        /* The reमुख्यing data is located in pending_out[0:pending]. If someone
         * calls put_byte() - this might happen in deflate() - the byte will be
         * placed पूर्णांकo pending_buf[pending], which is incorrect. Move the
         * reमुख्यing data to the beginning of pending_buf so that put_byte() is
         * usable again.
         */
        स_हटाओ(state->pending_buf, state->pending_out, state->pending);
        state->pending_out = state->pending_buf;
    पूर्ण
#अगर_घोषित ZLIB_DEBUG
    state->compressed_len += param->eobl;
#पूर्ण_अगर
पूर्ण

पूर्णांक dfltcc_deflate(
    z_streamp strm,
    पूर्णांक flush,
    block_state *result
)
अणु
    deflate_state *state = (deflate_state *)strm->state;
    काष्ठा dfltcc_state *dfltcc_state = GET_DFLTCC_STATE(state);
    काष्ठा dfltcc_param_v0 *param = &dfltcc_state->param;
    uInt masked_avail_in;
    dfltcc_cc cc;
    पूर्णांक need_empty_block;
    पूर्णांक soft_bcc;
    पूर्णांक no_flush;

    अगर (!dfltcc_can_deflate(strm))
        वापस 0;

again:
    masked_avail_in = 0;
    soft_bcc = 0;
    no_flush = flush == Z_NO_FLUSH;

    /* Trailing empty block. Switch to software, except when Continuation Flag
     * is set, which means that DFLTCC has buffered some output in the
     * parameter block and needs to be called again in order to flush it.
     */
    अगर (flush == Z_FINISH && strm->avail_in == 0 && !param->cf) अणु
        अगर (param->bcf) अणु
            /* A block is still खोलो, and the hardware करोes not support closing
             * blocks without adding data. Thus, बंद it manually.
             */
            send_eobs(strm, param);
            param->bcf = 0;
        पूर्ण
        वापस 0;
    पूर्ण

    अगर (strm->avail_in == 0 && !param->cf) अणु
        *result = need_more;
        वापस 1;
    पूर्ण

    /* There is an खोलो non-BFINAL block, we are not going to बंद it just
     * yet, we have compressed more than DFLTCC_BLOCK_SIZE bytes and we see
     * more than DFLTCC_DHT_MIN_SAMPLE_SIZE bytes. Open a new block with a new
     * DHT in order to adapt to a possibly changed input data distribution.
     */
    अगर (param->bcf && no_flush &&
            strm->total_in > dfltcc_state->block_threshold &&
            strm->avail_in >= dfltcc_state->dht_threshold) अणु
        अगर (param->cf) अणु
            /* We need to flush the DFLTCC buffer beक्रमe writing the
             * End-of-block Symbol. Mask the input data and proceed as usual.
             */
            masked_avail_in += strm->avail_in;
            strm->avail_in = 0;
            no_flush = 0;
        पूर्ण अन्यथा अणु
            /* DFLTCC buffer is empty, so we can manually ग_लिखो the
             * End-of-block Symbol right away.
             */
            send_eobs(strm, param);
            param->bcf = 0;
            dfltcc_state->block_threshold =
                strm->total_in + dfltcc_state->block_size;
            अगर (strm->avail_out == 0) अणु
                *result = need_more;
                वापस 1;
            पूर्ण
        पूर्ण
    पूर्ण

    /* The caller gave us too much data. Pass only one block worth of
     * uncompressed data to DFLTCC and mask the rest, so that on the next
     * iteration we start a new block.
     */
    अगर (no_flush && strm->avail_in > dfltcc_state->block_size) अणु
        masked_avail_in += (strm->avail_in - dfltcc_state->block_size);
        strm->avail_in = dfltcc_state->block_size;
    पूर्ण

    /* When we have an खोलो non-BFINAL deflate block and caller indicates that
     * the stream is ending, we need to बंद an खोलो deflate block and खोलो a
     * BFINAL one.
     */
    need_empty_block = flush == Z_FINISH && param->bcf && !param->bhf;

    /* Translate stream to parameter block */
    param->cvt = CVT_ADLER32;
    अगर (!no_flush)
        /* We need to बंद a block. Always करो this in software - when there is
         * no input data, the hardware will not nohor BCC. */
        soft_bcc = 1;
    अगर (flush == Z_FINISH && !param->bcf)
        /* We are about to खोलो a BFINAL block, set Block Header Final bit
         * until the stream ends.
         */
        param->bhf = 1;
    /* DFLTCC-CMPR will ग_लिखो to next_out, so make sure that buffers with
     * higher precedence are empty.
     */
    Assert(state->pending == 0, "There must be no pending bytes");
    Assert(state->bi_valid < 8, "There must be less than 8 pending bits");
    param->sbb = (अचिन्हित पूर्णांक)state->bi_valid;
    अगर (param->sbb > 0)
        *strm->next_out = (Byte)state->bi_buf;
    अगर (param->hl)
        param->nt = 0; /* Honor history */
    param->cv = strm->adler;

    /* When खोलोing a block, choose a Huffman-Table Type */
    अगर (!param->bcf) अणु
        अगर (strm->total_in == 0 && dfltcc_state->block_threshold > 0) अणु
            param->htt = HTT_FIXED;
        पूर्ण
        अन्यथा अणु
            param->htt = HTT_DYNAMIC;
            dfltcc_gdht(strm);
        पूर्ण
    पूर्ण

    /* Deflate */
    करो अणु
        cc = dfltcc_cmpr(strm);
        अगर (strm->avail_in < 4096 && masked_avail_in > 0)
            /* We are about to call DFLTCC with a small input buffer, which is
             * inefficient. Since there is masked data, there will be at least
             * one more DFLTCC call, so skip the current one and make the next
             * one handle more data.
             */
            अवरोध;
    पूर्ण जबतक (cc == DFLTCC_CC_AGAIN);

    /* Translate parameter block to stream */
    strm->msg = oesc_msg(dfltcc_state->msg, param->oesc);
    state->bi_valid = param->sbb;
    अगर (state->bi_valid == 0)
        state->bi_buf = 0; /* Aव्योम accessing next_out */
    अन्यथा
        state->bi_buf = *strm->next_out & ((1 << state->bi_valid) - 1);
    strm->adler = param->cv;

    /* Unmask the input data */
    strm->avail_in += masked_avail_in;
    masked_avail_in = 0;

    /* If we encounter an error, it means there is a bug in DFLTCC call */
    Assert(cc != DFLTCC_CC_OP2_CORRUPT || param->oesc == 0, "BUG");

    /* Update Block-Continuation Flag. It will be used to check whether to call
     * GDHT the next समय.
     */
    अगर (cc == DFLTCC_CC_OK) अणु
        अगर (soft_bcc) अणु
            send_eobs(strm, param);
            param->bcf = 0;
            dfltcc_state->block_threshold =
                strm->total_in + dfltcc_state->block_size;
        पूर्ण अन्यथा
            param->bcf = 1;
        अगर (flush == Z_FINISH) अणु
            अगर (need_empty_block)
                /* Make the current deflate() call also बंद the stream */
                वापस 0;
            अन्यथा अणु
                bi_windup(state);
                *result = finish_करोne;
            पूर्ण
        पूर्ण अन्यथा अणु
            अगर (flush == Z_FULL_FLUSH)
                param->hl = 0; /* Clear history */
            *result = flush == Z_NO_FLUSH ? need_more : block_करोne;
        पूर्ण
    पूर्ण अन्यथा अणु
        param->bcf = 1;
        *result = need_more;
    पूर्ण
    अगर (strm->avail_in != 0 && strm->avail_out != 0)
        जाओ again; /* deflate() must use all input or all output */
    वापस 1;
पूर्ण
EXPORT_SYMBOL(dfltcc_deflate);
