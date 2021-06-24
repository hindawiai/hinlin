<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * File:	m54xxgpt.h
 * Purpose:	Register and bit definitions क्रम the MCF54XX
 *
 * Notes:
 *
 */

#अगर_अघोषित m54xxgpt_h
#घोषणा m54xxgpt_h

/*********************************************************************
*
* General Purpose Timers (GPT)
*
*********************************************************************/

/* Register पढ़ो/ग_लिखो macros */
#घोषणा MCF_GPT_GMS0       (MCF_MBAR + 0x000800)
#घोषणा MCF_GPT_GCIR0      (MCF_MBAR + 0x000804)
#घोषणा MCF_GPT_GPWM0      (MCF_MBAR + 0x000808)
#घोषणा MCF_GPT_GSR0       (MCF_MBAR + 0x00080C)
#घोषणा MCF_GPT_GMS1       (MCF_MBAR + 0x000810)
#घोषणा MCF_GPT_GCIR1      (MCF_MBAR + 0x000814)
#घोषणा MCF_GPT_GPWM1      (MCF_MBAR + 0x000818)
#घोषणा MCF_GPT_GSR1       (MCF_MBAR + 0x00081C)
#घोषणा MCF_GPT_GMS2       (MCF_MBAR + 0x000820)
#घोषणा MCF_GPT_GCIR2      (MCF_MBAR + 0x000824)
#घोषणा MCF_GPT_GPWM2      (MCF_MBAR + 0x000828)
#घोषणा MCF_GPT_GSR2       (MCF_MBAR + 0x00082C)
#घोषणा MCF_GPT_GMS3       (MCF_MBAR + 0x000830)
#घोषणा MCF_GPT_GCIR3      (MCF_MBAR + 0x000834)
#घोषणा MCF_GPT_GPWM3      (MCF_MBAR + 0x000838)
#घोषणा MCF_GPT_GSR3       (MCF_MBAR + 0x00083C)
#घोषणा MCF_GPT_GMS(x)     (MCF_MBAR + 0x000800 + ((x) * 0x010))
#घोषणा MCF_GPT_GCIR(x)    (MCF_MBAR + 0x000804 + ((x) * 0x010))
#घोषणा MCF_GPT_GPWM(x)    (MCF_MBAR + 0x000808 + ((x) * 0x010))
#घोषणा MCF_GPT_GSR(x)     (MCF_MBAR + 0x00080C + ((x) * 0x010))

/* Bit definitions and macros क्रम MCF_GPT_GMS */
#घोषणा MCF_GPT_GMS_TMS(x)         (((x)&0x00000007)<<0)
#घोषणा MCF_GPT_GMS_GPIO(x)        (((x)&0x00000003)<<4)
#घोषणा MCF_GPT_GMS_IEN            (0x00000100)
#घोषणा MCF_GPT_GMS_OD             (0x00000200)
#घोषणा MCF_GPT_GMS_SC             (0x00000400)
#घोषणा MCF_GPT_GMS_CE             (0x00001000)
#घोषणा MCF_GPT_GMS_WDEN           (0x00008000)
#घोषणा MCF_GPT_GMS_ICT(x)         (((x)&0x00000003)<<16)
#घोषणा MCF_GPT_GMS_OCT(x)         (((x)&0x00000003)<<20)
#घोषणा MCF_GPT_GMS_OCPW(x)        (((x)&0x000000FF)<<24)
#घोषणा MCF_GPT_GMS_OCT_FRCLOW     (0x00000000)
#घोषणा MCF_GPT_GMS_OCT_PULSEHI    (0x00100000)
#घोषणा MCF_GPT_GMS_OCT_PULSELO    (0x00200000)
#घोषणा MCF_GPT_GMS_OCT_TOGGLE     (0x00300000)
#घोषणा MCF_GPT_GMS_ICT_ANY        (0x00000000)
#घोषणा MCF_GPT_GMS_ICT_RISE       (0x00010000)
#घोषणा MCF_GPT_GMS_ICT_FALL       (0x00020000)
#घोषणा MCF_GPT_GMS_ICT_PULSE      (0x00030000)
#घोषणा MCF_GPT_GMS_GPIO_INPUT     (0x00000000)
#घोषणा MCF_GPT_GMS_GPIO_OUTLO     (0x00000020)
#घोषणा MCF_GPT_GMS_GPIO_OUTHI     (0x00000030)
#घोषणा MCF_GPT_GMS_GPIO_MASK      (0x00000030)
#घोषणा MCF_GPT_GMS_TMS_DISABLE    (0x00000000)
#घोषणा MCF_GPT_GMS_TMS_INCAPT     (0x00000001)
#घोषणा MCF_GPT_GMS_TMS_OUTCAPT    (0x00000002)
#घोषणा MCF_GPT_GMS_TMS_PWM        (0x00000003)
#घोषणा MCF_GPT_GMS_TMS_GPIO       (0x00000004)
#घोषणा MCF_GPT_GMS_TMS_MASK       (0x00000007)

/* Bit definitions and macros क्रम MCF_GPT_GCIR */
#घोषणा MCF_GPT_GCIR_CNT(x)        (((x)&0x0000FFFF)<<0)
#घोषणा MCF_GPT_GCIR_PRE(x)        (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros क्रम MCF_GPT_GPWM */
#घोषणा MCF_GPT_GPWM_LOAD          (0x00000001)
#घोषणा MCF_GPT_GPWM_PWMOP         (0x00000100)
#घोषणा MCF_GPT_GPWM_WIDTH(x)      (((x)&0x0000FFFF)<<16)

/* Bit definitions and macros क्रम MCF_GPT_GSR */
#घोषणा MCF_GPT_GSR_CAPT           (0x00000001)
#घोषणा MCF_GPT_GSR_COMP           (0x00000002)
#घोषणा MCF_GPT_GSR_PWMP           (0x00000004)
#घोषणा MCF_GPT_GSR_TEXP           (0x00000008)
#घोषणा MCF_GPT_GSR_PIN            (0x00000100)
#घोषणा MCF_GPT_GSR_OVF(x)         (((x)&0x00000007)<<12)
#घोषणा MCF_GPT_GSR_CAPTURE(x)     (((x)&0x0000FFFF)<<16)

/********************************************************************/

#पूर्ण_अगर /* m54xxgpt_h */
