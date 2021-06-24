<शैली गुरु>
// SPDX-License-Identअगरier: Zlib
/* dfltcc.c - SystemZ DEFLATE CONVERSION CALL support. */

#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश "dfltcc_util.h"
#समावेश "dfltcc.h"

अक्षर *oesc_msg(
    अक्षर *buf,
    पूर्णांक oesc
)
अणु
    अगर (oesc == 0x00)
        वापस शून्य; /* Successful completion */
    अन्यथा अणु
#अगर_घोषित STATIC
        वापस शून्य; /* Ignore क्रम pre-boot decompressor */
#अन्यथा
        प्र_लिखो(buf, "Operation-Ending-Supplemental Code is 0x%.2X", oesc);
        वापस buf;
#पूर्ण_अगर
    पूर्ण
पूर्ण

व्योम dfltcc_reset(
    z_streamp strm,
    uInt size
)
अणु
    काष्ठा dfltcc_state *dfltcc_state =
        (काष्ठा dfltcc_state *)((अक्षर *)strm->state + size);
    काष्ठा dfltcc_qaf_param *param =
        (काष्ठा dfltcc_qaf_param *)&dfltcc_state->param;

    /* Initialize available functions */
    अगर (is_dfltcc_enabled()) अणु
        dfltcc(DFLTCC_QAF, param, शून्य, शून्य, शून्य, शून्य, शून्य);
        स_हटाओ(&dfltcc_state->af, param, माप(dfltcc_state->af));
    पूर्ण अन्यथा
        स_रखो(&dfltcc_state->af, 0, माप(dfltcc_state->af));

    /* Initialize parameter block */
    स_रखो(&dfltcc_state->param, 0, माप(dfltcc_state->param));
    dfltcc_state->param.nt = 1;

    /* Initialize tuning parameters */
    अगर (zlib_dfltcc_support == ZLIB_DFLTCC_FULL_DEBUG)
        dfltcc_state->level_mask = DFLTCC_LEVEL_MASK_DEBUG;
    अन्यथा
        dfltcc_state->level_mask = DFLTCC_LEVEL_MASK;
    dfltcc_state->block_size = DFLTCC_BLOCK_SIZE;
    dfltcc_state->block_threshold = DFLTCC_FIRST_FHT_BLOCK_SIZE;
    dfltcc_state->dht_threshold = DFLTCC_DHT_MIN_SAMPLE_SIZE;
    dfltcc_state->param.ribm = DFLTCC_RIBM;
पूर्ण
EXPORT_SYMBOL(dfltcc_reset);

MODULE_LICENSE("GPL");
