<शैली गुरु>
/*
 * Copyright (C) 2018  Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _thm_11_0_2_SH_MASK_HEADER
#घोषणा _thm_11_0_2_SH_MASK_HEADER


//CG_MULT_THERMAL_STATUS
#घोषणा CG_MULT_THERMAL_STATUS__ASIC_MAX_TEMP__SHIFT                                                          0x0
#घोषणा CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT                                                               0x9
#घोषणा CG_MULT_THERMAL_STATUS__ASIC_MAX_TEMP_MASK                                                            0x000001FFL
#घोषणा CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK                                                                 0x0003FE00L
#घोषणा CG_FDO_CTRL2__TMIN__SHIFT                                                                             0x0
#घोषणा CG_FDO_CTRL2__TMIN_MASK                                                                               0x000000FFL
#घोषणा CG_FDO_CTRL2__FDO_PWM_MODE__SHIFT                                                                     0xb
#घोषणा CG_FDO_CTRL2__FDO_PWM_MODE_MASK                                                                       0x00003800L
#घोषणा CG_FDO_CTRL1__FMAX_DUTY100__SHIFT                                                                     0x0
#घोषणा CG_FDO_CTRL1__FMAX_DUTY100_MASK                                                                       0x000000FFL
#घोषणा CG_FDO_CTRL0__FDO_STATIC_DUTY__SHIFT                                                                  0x0
#घोषणा CG_FDO_CTRL0__FDO_STATIC_DUTY_MASK                                                                    0x000000FFL
#घोषणा CG_TACH_CTRL__TARGET_PERIOD__SHIFT                                                                    0x3
#घोषणा CG_TACH_CTRL__TARGET_PERIOD_MASK                                                                      0xFFFFFFF8L

//THM_THERMAL_INT_ENA
#घोषणा THM_THERMAL_INT_ENA__THERM_INTH_SET__SHIFT                                                            0x0
#घोषणा THM_THERMAL_INT_ENA__THERM_INTL_SET__SHIFT                                                            0x1
#घोषणा THM_THERMAL_INT_ENA__THERM_TRIGGER_SET__SHIFT                                                         0x2
#घोषणा THM_THERMAL_INT_ENA__THERM_INTH_CLR__SHIFT                                                            0x3
#घोषणा THM_THERMAL_INT_ENA__THERM_INTL_CLR__SHIFT                                                            0x4
#घोषणा THM_THERMAL_INT_ENA__THERM_TRIGGER_CLR__SHIFT                                                         0x5
#घोषणा THM_THERMAL_INT_ENA__THERM_INTH_SET_MASK                                                              0x00000001L
#घोषणा THM_THERMAL_INT_ENA__THERM_INTL_SET_MASK                                                              0x00000002L
#घोषणा THM_THERMAL_INT_ENA__THERM_TRIGGER_SET_MASK                                                           0x00000004L
#घोषणा THM_THERMAL_INT_ENA__THERM_INTH_CLR_MASK                                                              0x00000008L
#घोषणा THM_THERMAL_INT_ENA__THERM_INTL_CLR_MASK                                                              0x00000010L
#घोषणा THM_THERMAL_INT_ENA__THERM_TRIGGER_CLR_MASK                                                           0x00000020L
//THM_THERMAL_INT_CTRL
#घोषणा THM_THERMAL_INT_CTRL__DIG_THERM_INTH__SHIFT                                                           0x0
#घोषणा THM_THERMAL_INT_CTRL__DIG_THERM_INTL__SHIFT                                                           0x8
#घोषणा THM_THERMAL_INT_CTRL__TEMP_THRESHOLD__SHIFT                                                           0x10
#घोषणा THM_THERMAL_INT_CTRL__THERM_INTH_MASK__SHIFT                                                          0x18
#घोषणा THM_THERMAL_INT_CTRL__THERM_INTL_MASK__SHIFT                                                          0x19
#घोषणा THM_THERMAL_INT_CTRL__THERM_TRIGGER_MASK__SHIFT                                                       0x1a
#घोषणा THM_THERMAL_INT_CTRL__THERM_PROCHOT_MASK__SHIFT                                                       0x1b
#घोषणा THM_THERMAL_INT_CTRL__THERM_IH_HW_ENA__SHIFT                                                          0x1c
#घोषणा THM_THERMAL_INT_CTRL__MAX_IH_CREDIT__SHIFT                                                            0x1d
#घोषणा THM_THERMAL_INT_CTRL__DIG_THERM_INTH_MASK                                                             0x000000FFL
#घोषणा THM_THERMAL_INT_CTRL__DIG_THERM_INTL_MASK                                                             0x0000FF00L
#घोषणा THM_THERMAL_INT_CTRL__TEMP_THRESHOLD_MASK                                                             0x00FF0000L
#घोषणा THM_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK                                                            0x01000000L
#घोषणा THM_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK                                                            0x02000000L
#घोषणा THM_THERMAL_INT_CTRL__THERM_TRIGGER_MASK_MASK                                                         0x04000000L
#घोषणा THM_THERMAL_INT_CTRL__THERM_PROCHOT_MASK_MASK                                                         0x08000000L
#घोषणा THM_THERMAL_INT_CTRL__THERM_IH_HW_ENA_MASK                                                            0x10000000L
#घोषणा THM_THERMAL_INT_CTRL__MAX_IH_CREDIT_MASK                                                              0xE0000000L

//THM_TCON_THERM_TRIP
#घोषणा THM_TCON_THERM_TRIP__CTF_PAD_POLARITY__SHIFT                                                          0x0
#घोषणा THM_TCON_THERM_TRIP__THERM_TP__SHIFT                                                                  0x1
#घोषणा THM_TCON_THERM_TRIP__CTF_THRESHOLD_EXCEEDED__SHIFT                                                    0x2
#घोषणा THM_TCON_THERM_TRIP__THERM_TP_SENSE__SHIFT                                                            0x3
#घोषणा THM_TCON_THERM_TRIP__RSVD2__SHIFT                                                                     0x4
#घोषणा THM_TCON_THERM_TRIP__THERM_TP_EN__SHIFT                                                               0x5
#घोषणा THM_TCON_THERM_TRIP__THERM_TP_LMT__SHIFT                                                              0x6
#घोषणा THM_TCON_THERM_TRIP__RSVD3__SHIFT                                                                     0xe
#घोषणा THM_TCON_THERM_TRIP__SW_THERM_TP__SHIFT                                                               0x1f
#घोषणा THM_TCON_THERM_TRIP__CTF_PAD_POLARITY_MASK                                                            0x00000001L
#घोषणा THM_TCON_THERM_TRIP__THERM_TP_MASK                                                                    0x00000002L
#घोषणा THM_TCON_THERM_TRIP__CTF_THRESHOLD_EXCEEDED_MASK                                                      0x00000004L
#घोषणा THM_TCON_THERM_TRIP__THERM_TP_SENSE_MASK                                                              0x00000008L
#घोषणा THM_TCON_THERM_TRIP__RSVD2_MASK                                                                       0x00000010L
#घोषणा THM_TCON_THERM_TRIP__THERM_TP_EN_MASK                                                                 0x00000020L
#घोषणा THM_TCON_THERM_TRIP__THERM_TP_LMT_MASK                                                                0x00003FC0L
#घोषणा THM_TCON_THERM_TRIP__RSVD3_MASK                                                                       0x7FFFC000L
#घोषणा THM_TCON_THERM_TRIP__SW_THERM_TP_MASK                                                                 0x80000000L

#पूर्ण_अगर

