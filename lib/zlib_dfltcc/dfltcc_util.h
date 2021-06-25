<शैली गुरु>
// SPDX-License-Identअगरier: Zlib
#अगर_अघोषित DFLTCC_UTIL_H
#घोषणा DFLTCC_UTIL_H

#समावेश <linux/zutil.h>

/*
 * C wrapper क्रम the DEFLATE CONVERSION CALL inकाष्ठाion.
 */
प्रकार क्रमागत अणु
    DFLTCC_CC_OK = 0,
    DFLTCC_CC_OP1_TOO_SHORT = 1,
    DFLTCC_CC_OP2_TOO_SHORT = 2,
    DFLTCC_CC_OP2_CORRUPT = 2,
    DFLTCC_CC_AGAIN = 3,
पूर्ण dfltcc_cc;

#घोषणा DFLTCC_QAF 0
#घोषणा DFLTCC_GDHT 1
#घोषणा DFLTCC_CMPR 2
#घोषणा DFLTCC_XPND 4
#घोषणा HBT_CIRCULAR (1 << 7)
#घोषणा HB_BITS 15
#घोषणा HB_SIZE (1 << HB_BITS)

अटल अंतरभूत dfltcc_cc dfltcc(
    पूर्णांक fn,
    व्योम *param,
    Byte **op1,
    माप_प्रकार *len1,
    स्थिर Byte **op2,
    माप_प्रकार *len2,
    व्योम *hist
)
अणु
    Byte *t2 = op1 ? *op1 : शून्य;
    माप_प्रकार t3 = len1 ? *len1 : 0;
    स्थिर Byte *t4 = op2 ? *op2 : शून्य;
    माप_प्रकार t5 = len2 ? *len2 : 0;
    रेजिस्टर पूर्णांक r0 __यंत्र__("r0") = fn;
    रेजिस्टर व्योम *r1 __यंत्र__("r1") = param;
    रेजिस्टर Byte *r2 __यंत्र__("r2") = t2;
    रेजिस्टर माप_प्रकार r3 __यंत्र__("r3") = t3;
    रेजिस्टर स्थिर Byte *r4 __यंत्र__("r4") = t4;
    रेजिस्टर माप_प्रकार r5 __यंत्र__("r5") = t5;
    पूर्णांक cc;

    __यंत्र__ अस्थिर(
                     ".insn rrf,0xb9390000,%[r2],%[r4],%[hist],0\n"
                     "ipm %[cc]\n"
                     : [r2] "+r" (r2)
                     , [r3] "+r" (r3)
                     , [r4] "+r" (r4)
                     , [r5] "+r" (r5)
                     , [cc] "=r" (cc)
                     : [r0] "r" (r0)
                     , [r1] "r" (r1)
                     , [hist] "r" (hist)
                     : "cc", "memory");
    t2 = r2; t3 = r3; t4 = r4; t5 = r5;

    अगर (op1)
        *op1 = t2;
    अगर (len1)
        *len1 = t3;
    अगर (op2)
        *op2 = t4;
    अगर (len2)
        *len2 = t5;
    वापस (cc >> 28) & 3;
पूर्ण

अटल अंतरभूत पूर्णांक is_bit_set(
    स्थिर अक्षर *bits,
    पूर्णांक n
)
अणु
    वापस bits[n / 8] & (1 << (7 - (n % 8)));
पूर्ण

अटल अंतरभूत व्योम turn_bit_off(
    अक्षर *bits,
    पूर्णांक n
)
अणु
    bits[n / 8] &= ~(1 << (7 - (n % 8)));
पूर्ण

अटल अंतरभूत पूर्णांक dfltcc_are_params_ok(
    पूर्णांक level,
    uInt winकरोw_bits,
    पूर्णांक strategy,
    uLong level_mask
)
अणु
    वापस (level_mask & (1 << level)) != 0 &&
        (winकरोw_bits == HB_BITS) &&
        (strategy == Z_DEFAULT_STRATEGY);
पूर्ण

अक्षर *oesc_msg(अक्षर *buf, पूर्णांक oesc);

#पूर्ण_अगर /* DFLTCC_UTIL_H */
