<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */

#समावेश "phy_qmath.h"

/*
 * Description: This function make 16 bit अचिन्हित multiplication.
 * To fit the output पूर्णांकo 16 bits the 32 bit multiplication result is right
 * shअगरted by 16 bits.
 */
u16 qm_mulu16(u16 op1, u16 op2)
अणु
	वापस (u16) (((u32) op1 * (u32) op2) >> 16);
पूर्ण

/*
 * Description: This function make 16 bit multiplication and वापस the result
 * in 16 bits. To fit the multiplication result पूर्णांकo 16 bits the multiplication
 * result is right shअगरted by 15 bits. Right shअगरting 15 bits instead of 16 bits
 * is करोne to हटाओ the extra sign bit क्रमmed due to the multiplication.
 * When both the 16bit inमाला_दो are 0x8000 then the output is saturated to
 * 0x7fffffff.
 */
s16 qm_muls16(s16 op1, s16 op2)
अणु
	s32 result;
	अगर (op1 == (s16) 0x8000 && op2 == (s16) 0x8000)
		result = 0x7fffffff;
	अन्यथा
		result = ((s32) (op1) * (s32) (op2));

	वापस (s16) (result >> 15);
पूर्ण

/*
 * Description: This function add two 32 bit numbers and वापस the 32bit
 * result. If the result overflow 32 bits, the output will be saturated to
 * 32bits.
 */
s32 qm_add32(s32 op1, s32 op2)
अणु
	s32 result;
	result = op1 + op2;
	अगर (op1 < 0 && op2 < 0 && result > 0)
		result = 0x80000000;
	अन्यथा अगर (op1 > 0 && op2 > 0 && result < 0)
		result = 0x7fffffff;

	वापस result;
पूर्ण

/*
 * Description: This function add two 16 bit numbers and वापस the 16bit
 * result. If the result overflow 16 bits, the output will be saturated to
 * 16bits.
 */
s16 qm_add16(s16 op1, s16 op2)
अणु
	s16 result;
	s32 temp = (s32) op1 + (s32) op2;
	अगर (temp > (s32) 0x7fff)
		result = (s16) 0x7fff;
	अन्यथा अगर (temp < (s32) 0xffff8000)
		result = (s16) 0xffff8000;
	अन्यथा
		result = (s16) temp;

	वापस result;
पूर्ण

/*
 * Description: This function make 16 bit subtraction and वापस the 16bit
 * result. If the result overflow 16 bits, the output will be saturated to
 * 16bits.
 */
s16 qm_sub16(s16 op1, s16 op2)
अणु
	s16 result;
	s32 temp = (s32) op1 - (s32) op2;
	अगर (temp > (s32) 0x7fff)
		result = (s16) 0x7fff;
	अन्यथा अगर (temp < (s32) 0xffff8000)
		result = (s16) 0xffff8000;
	अन्यथा
		result = (s16) temp;

	वापस result;
पूर्ण

/*
 * Description: This function make a 32 bit saturated left shअगरt when the
 * specअगरied shअगरt is +ve. This function will make a 32 bit right shअगरt when
 * the specअगरied shअगरt is -ve. This function वापस the result after shअगरting
 * operation.
 */
s32 qm_shl32(s32 op, पूर्णांक shअगरt)
अणु
	पूर्णांक i;
	s32 result;
	result = op;
	अगर (shअगरt > 31)
		shअगरt = 31;
	अन्यथा अगर (shअगरt < -31)
		shअगरt = -31;
	अगर (shअगरt >= 0) अणु
		क्रम (i = 0; i < shअगरt; i++)
			result = qm_add32(result, result);
	पूर्ण अन्यथा अणु
		result = result >> (-shअगरt);
	पूर्ण

	वापस result;
पूर्ण

/*
 * Description: This function make a 16 bit saturated left shअगरt when the
 * specअगरied shअगरt is +ve. This function will make a 16 bit right shअगरt when
 * the specअगरied shअगरt is -ve. This function वापस the result after shअगरting
 * operation.
 */
s16 qm_shl16(s16 op, पूर्णांक shअगरt)
अणु
	पूर्णांक i;
	s16 result;
	result = op;
	अगर (shअगरt > 15)
		shअगरt = 15;
	अन्यथा अगर (shअगरt < -15)
		shअगरt = -15;
	अगर (shअगरt > 0) अणु
		क्रम (i = 0; i < shअगरt; i++)
			result = qm_add16(result, result);
	पूर्ण अन्यथा अणु
		result = result >> (-shअगरt);
	पूर्ण

	वापस result;
पूर्ण

/*
 * Description: This function make a 16 bit right shअगरt when shअगरt is +ve.
 * This function make a 16 bit saturated left shअगरt when shअगरt is -ve. This
 * function वापस the result of the shअगरt operation.
 */
s16 qm_shr16(s16 op, पूर्णांक shअगरt)
अणु
	वापस qm_shl16(op, -shअगरt);
पूर्ण

/*
 * Description: This function वापस the number of redundant sign bits in a
 * 32 bit number. Example: qm_norm32(0x00000080) = 23
 */
s16 qm_norm32(s32 op)
अणु
	u16 u16extraSignBits;
	अगर (op == 0) अणु
		वापस 31;
	पूर्ण अन्यथा अणु
		u16extraSignBits = 0;
		जबतक ((op >> 31) == (op >> 30)) अणु
			u16extraSignBits++;
			op = op << 1;
		पूर्ण
	पूर्ण
	वापस u16extraSignBits;
पूर्ण

/* This table is log2(1+(i/32)) where i=[0:1:32], in q.15 क्रमmat */
अटल स्थिर s16 log_table[] = अणु
	0,
	1455,
	2866,
	4236,
	5568,
	6863,
	8124,
	9352,
	10549,
	11716,
	12855,
	13968,
	15055,
	16117,
	17156,
	18173,
	19168,
	20143,
	21098,
	22034,
	22952,
	23852,
	24736,
	25604,
	26455,
	27292,
	28114,
	28922,
	29717,
	30498,
	31267,
	32024,
	32767
पूर्ण;

#घोषणा LOG_TABLE_SIZE 32       /* log_table size */
#घोषणा LOG2_LOG_TABLE_SIZE 5   /* log2(log_table size) */
#घोषणा Q_LOG_TABLE 15          /* qक्रमmat of log_table */
#घोषणा LOG10_2         19728   /* log10(2) in q.16 */

/*
 * Description:
 * This routine takes the input number N and its q क्रमmat qN and compute
 * the log10(N). This routine first normalizes the input no N.	Then N is in
 * mag*(2^x) क्रमmat. mag is any number in the range 2^30-(2^31 - 1).
 * Then log2(mag * 2^x) = log2(mag) + x is computed. From that
 * log10(mag * 2^x) = log2(mag * 2^x) * log10(2) is computed.
 * This routine looks the log2 value in the table considering
 * LOG2_LOG_TABLE_SIZE+1 MSBs. As the MSB is always 1, only next
 * LOG2_OF_LOG_TABLE_SIZE MSBs are used क्रम table lookup. Next 16 MSBs are used
 * क्रम पूर्णांकerpolation.
 * Inमाला_दो:
 * N - number to which log10 has to be found.
 * qN - q क्रमmat of N
 * log10N - address where log10(N) will be written.
 * qLog10N - address where log10N qक्रमmat will be written.
 * Note/Problem:
 * For accurate results input should be in normalized or near normalized क्रमm.
 */
व्योम qm_log10(s32 N, s16 qN, s16 *log10N, s16 *qLog10N)
अणु
	s16 s16norm, s16tableIndex, s16errorApproximation;
	u16 u16offset;
	s32 s32log;

	/* normalize the N. */
	s16norm = qm_norm32(N);
	N = N << s16norm;

	/* The qक्रमmat of N after normalization.
	 * -30 is added to treat the no as between 1.0 to 2.0
	 * i.e. after adding the -30 to the qक्रमmat the decimal poपूर्णांक will be
	 * just rigtht of the MSB. (i.e. after sign bit and 1st MSB). i.e.
	 * at the right side of 30th bit.
	 */
	qN = qN + s16norm - 30;

	/* take the table index as the LOG2_OF_LOG_TABLE_SIZE bits right of the
	 * MSB */
	s16tableIndex = (s16) (N >> (32 - (2 + LOG2_LOG_TABLE_SIZE)));

	/* हटाओ the MSB. the MSB is always 1 after normalization. */
	s16tableIndex =
		s16tableIndex & (s16) ((1 << LOG2_LOG_TABLE_SIZE) - 1);

	/* हटाओ the (1+LOG2_OF_LOG_TABLE_SIZE) MSBs in the N. */
	N = N & ((1 << (32 - (2 + LOG2_LOG_TABLE_SIZE))) - 1);

	/* take the offset as the 16 MSBS after table index.
	 */
	u16offset = (u16) (N >> (32 - (2 + LOG2_LOG_TABLE_SIZE + 16)));

	/* look the log value in the table. */
	s32log = log_table[s16tableIndex];      /* q.15 क्रमmat */

	/* पूर्णांकerpolate using the offset. q.15 क्रमmat. */
	s16errorApproximation = (s16) qm_mulu16(u16offset,
				(u16) (log_table[s16tableIndex + 1] -
				       log_table[s16tableIndex]));

	 /* q.15 क्रमmat */
	s32log = qm_add16((s16) s32log, s16errorApproximation);

	/* adjust क्रम the qक्रमmat of the N as
	 * log2(mag * 2^x) = log2(mag) + x
	 */
	s32log = qm_add32(s32log, ((s32) -qN) << 15);   /* q.15 क्रमmat */

	/* normalize the result. */
	s16norm = qm_norm32(s32log);

	/* bring all the important bits पूर्णांकo lower 16 bits */
	/* q.15+s16norm-16 क्रमmat */
	s32log = qm_shl32(s32log, s16norm - 16);

	/* compute the log10(N) by multiplying log2(N) with log10(2).
	 * as log10(mag * 2^x) = log2(mag * 2^x) * log10(2)
	 * log10N in q.15+s16norm-16+1 (LOG10_2 is in q.16)
	 */
	*log10N = qm_muls16((s16) s32log, (s16) LOG10_2);

	/* ग_लिखो the q क्रमmat of the result. */
	*qLog10N = 15 + s16norm - 16 + 1;

	वापस;
पूर्ण
