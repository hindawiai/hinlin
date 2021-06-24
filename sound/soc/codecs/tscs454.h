<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// tscs454.h -- TSCS454 ALSA SoC Audio driver
// Copyright 2018 Tempo Semiconductor, Inc.
// Author: Steven Eckhoff <steven.eckhoff.खोलोsource@gmail.com>

#अगर_अघोषित __REDWOODPUBLIC_H__
#घोषणा __REDWOODPUBLIC_H__

#घोषणा VIRT_BASE 0x00
#घोषणा PAGE_LEN 0x100
#घोषणा VIRT_PAGE_BASE(page) (VIRT_BASE + (PAGE_LEN * page))
#घोषणा VIRT_ADDR(page, address) (VIRT_PAGE_BASE(page) + address)
#घोषणा ADDR(page, virt_address) (virt_address - VIRT_PAGE_BASE(page))

#घोषणा R_PAGESEL                       0x0
#घोषणा R_RESET                         VIRT_ADDR(0x0, 0x1)
#घोषणा R_IRQEN                         VIRT_ADDR(0x0, 0x2)
#घोषणा R_IRQMASK                       VIRT_ADDR(0x0, 0x3)
#घोषणा R_IRQSTAT                       VIRT_ADDR(0x0, 0x4)
#घोषणा R_DEVADD0                       VIRT_ADDR(0x0, 0x6)
#घोषणा R_DEVID                         VIRT_ADDR(0x0, 0x8)
#घोषणा R_DEVREV                        VIRT_ADDR(0x0, 0x9)
#घोषणा R_PLLSTAT                       VIRT_ADDR(0x0, 0x0A)
#घोषणा R_PLL1CTL                       VIRT_ADDR(0x0, 0x0B)
#घोषणा R_PLL1RDIV                      VIRT_ADDR(0x0, 0x0C)
#घोषणा R_PLL1ODIV                      VIRT_ADDR(0x0, 0x0D)
#घोषणा R_PLL1FDIVL                     VIRT_ADDR(0x0, 0x0E)
#घोषणा R_PLL1FDIVH                     VIRT_ADDR(0x0, 0x0F)
#घोषणा R_PLL2CTL                       VIRT_ADDR(0x0, 0x10)
#घोषणा R_PLL2RDIV                      VIRT_ADDR(0x0, 0x11)
#घोषणा R_PLL2ODIV                      VIRT_ADDR(0x0, 0x12)
#घोषणा R_PLL2FDIVL                     VIRT_ADDR(0x0, 0x13)
#घोषणा R_PLL2FDIVH                     VIRT_ADDR(0x0, 0x14)
#घोषणा R_PLLCTL                        VIRT_ADDR(0x0, 0x15)
#घोषणा R_ISRC                          VIRT_ADDR(0x0, 0x16)
#घोषणा R_SCLKCTL                       VIRT_ADDR(0x0, 0x18)
#घोषणा R_TIMEBASE                      VIRT_ADDR(0x0, 0x19)
#घोषणा R_I2SP1CTL                      VIRT_ADDR(0x0, 0x1A)
#घोषणा R_I2SP2CTL                      VIRT_ADDR(0x0, 0x1B)
#घोषणा R_I2SP3CTL                      VIRT_ADDR(0x0, 0x1C)
#घोषणा R_I2S1MRATE                     VIRT_ADDR(0x0, 0x1D)
#घोषणा R_I2S2MRATE                     VIRT_ADDR(0x0, 0x1E)
#घोषणा R_I2S3MRATE                     VIRT_ADDR(0x0, 0x1F)
#घोषणा R_I2SCMC                        VIRT_ADDR(0x0, 0x20)
#घोषणा R_MCLK2PINC                     VIRT_ADDR(0x0, 0x21)
#घोषणा R_I2SPINC0                      VIRT_ADDR(0x0, 0x22)
#घोषणा R_I2SPINC1                      VIRT_ADDR(0x0, 0x23)
#घोषणा R_I2SPINC2                      VIRT_ADDR(0x0, 0x24)
#घोषणा R_GPIOCTL0                      VIRT_ADDR(0x0, 0x25)
#घोषणा R_GPIOCTL1                      VIRT_ADDR(0x0, 0x26)
#घोषणा R_ASRC                          VIRT_ADDR(0x0, 0x28)
#घोषणा R_TDMCTL0                       VIRT_ADDR(0x0, 0x2D)
#घोषणा R_TDMCTL1                       VIRT_ADDR(0x0, 0x2E)
#घोषणा R_PCMP2CTL0                     VIRT_ADDR(0x0, 0x2F)
#घोषणा R_PCMP2CTL1                     VIRT_ADDR(0x0, 0x30)
#घोषणा R_PCMP3CTL0                     VIRT_ADDR(0x0, 0x31)
#घोषणा R_PCMP3CTL1                     VIRT_ADDR(0x0, 0x32)
#घोषणा R_PWRM0                         VIRT_ADDR(0x0, 0x33)
#घोषणा R_PWRM1                         VIRT_ADDR(0x0, 0x34)
#घोषणा R_PWRM2                         VIRT_ADDR(0x0, 0x35)
#घोषणा R_PWRM3                         VIRT_ADDR(0x0, 0x36)
#घोषणा R_PWRM4                         VIRT_ADDR(0x0, 0x37)
#घोषणा R_I2SIDCTL                      VIRT_ADDR(0x0, 0x38)
#घोषणा R_I2SODCTL                      VIRT_ADDR(0x0, 0x39)
#घोषणा R_AUDIOMUX1                     VIRT_ADDR(0x0, 0x3A)
#घोषणा R_AUDIOMUX2                     VIRT_ADDR(0x0, 0x3B)
#घोषणा R_AUDIOMUX3                     VIRT_ADDR(0x0, 0x3C)
#घोषणा R_HSDCTL1                       VIRT_ADDR(0x1, 0x1)
#घोषणा R_HSDCTL2                       VIRT_ADDR(0x1, 0x2)
#घोषणा R_HSDSTAT                       VIRT_ADDR(0x1, 0x3)
#घोषणा R_HSDDELAY                      VIRT_ADDR(0x1, 0x4)
#घोषणा R_BUTCTL                        VIRT_ADDR(0x1, 0x5)
#घोषणा R_CH0AIC                        VIRT_ADDR(0x1, 0x6)
#घोषणा R_CH1AIC                        VIRT_ADDR(0x1, 0x7)
#घोषणा R_CH2AIC                        VIRT_ADDR(0x1, 0x8)
#घोषणा R_CH3AIC                        VIRT_ADDR(0x1, 0x9)
#घोषणा R_ICTL0                         VIRT_ADDR(0x1, 0x0A)
#घोषणा R_ICTL1                         VIRT_ADDR(0x1, 0x0B)
#घोषणा R_MICBIAS                       VIRT_ADDR(0x1, 0x0C)
#घोषणा R_PGACTL0                       VIRT_ADDR(0x1, 0x0D)
#घोषणा R_PGACTL1                       VIRT_ADDR(0x1, 0x0E)
#घोषणा R_PGACTL2                       VIRT_ADDR(0x1, 0x0F)
#घोषणा R_PGACTL3                       VIRT_ADDR(0x1, 0x10)
#घोषणा R_PGAZ                          VIRT_ADDR(0x1, 0x11)
#घोषणा R_ICH0VOL                       VIRT_ADDR(0x1, 0x12)
#घोषणा R_ICH1VOL                       VIRT_ADDR(0x1, 0x13)
#घोषणा R_ICH2VOL                       VIRT_ADDR(0x1, 0x14)
#घोषणा R_ICH3VOL                       VIRT_ADDR(0x1, 0x15)
#घोषणा R_ASRCILVOL                     VIRT_ADDR(0x1, 0x16)
#घोषणा R_ASRCIRVOL                     VIRT_ADDR(0x1, 0x17)
#घोषणा R_ASRCOLVOL                     VIRT_ADDR(0x1, 0x18)
#घोषणा R_ASRCORVOL                     VIRT_ADDR(0x1, 0x19)
#घोषणा R_IVOLCTLU                      VIRT_ADDR(0x1, 0x1C)
#घोषणा R_ALCCTL0                       VIRT_ADDR(0x1, 0x1D)
#घोषणा R_ALCCTL1                       VIRT_ADDR(0x1, 0x1E)
#घोषणा R_ALCCTL2                       VIRT_ADDR(0x1, 0x1F)
#घोषणा R_ALCCTL3                       VIRT_ADDR(0x1, 0x20)
#घोषणा R_NGATE                         VIRT_ADDR(0x1, 0x21)
#घोषणा R_DMICCTL                       VIRT_ADDR(0x1, 0x22)
#घोषणा R_DACCTL                        VIRT_ADDR(0x2, 0x1)
#घोषणा R_SPKCTL                        VIRT_ADDR(0x2, 0x2)
#घोषणा R_SUBCTL                        VIRT_ADDR(0x2, 0x3)
#घोषणा R_DCCTL                         VIRT_ADDR(0x2, 0x4)
#घोषणा R_OVOLCTLU                      VIRT_ADDR(0x2, 0x6)
#घोषणा R_MUTEC                         VIRT_ADDR(0x2, 0x7)
#घोषणा R_MVOLL                         VIRT_ADDR(0x2, 0x8)
#घोषणा R_MVOLR                         VIRT_ADDR(0x2, 0x9)
#घोषणा R_HPVOLL                        VIRT_ADDR(0x2, 0x0A)
#घोषणा R_HPVOLR                        VIRT_ADDR(0x2, 0x0B)
#घोषणा R_SPKVOLL                       VIRT_ADDR(0x2, 0x0C)
#घोषणा R_SPKVOLR                       VIRT_ADDR(0x2, 0x0D)
#घोषणा R_SUBVOL                        VIRT_ADDR(0x2, 0x10)
#घोषणा R_COP0                          VIRT_ADDR(0x2, 0x11)
#घोषणा R_COP1                          VIRT_ADDR(0x2, 0x12)
#घोषणा R_COPSTAT                       VIRT_ADDR(0x2, 0x13)
#घोषणा R_PWM0                          VIRT_ADDR(0x2, 0x14)
#घोषणा R_PWM1                          VIRT_ADDR(0x2, 0x15)
#घोषणा R_PWM2                          VIRT_ADDR(0x2, 0x16)
#घोषणा R_PWM3                          VIRT_ADDR(0x2, 0x17)
#घोषणा R_HPSW                          VIRT_ADDR(0x2, 0x18)
#घोषणा R_THERMTS                       VIRT_ADDR(0x2, 0x19)
#घोषणा R_THERMSPK1                     VIRT_ADDR(0x2, 0x1A)
#घोषणा R_THERMSTAT                     VIRT_ADDR(0x2, 0x1B)
#घोषणा R_SCSTAT                        VIRT_ADDR(0x2, 0x1C)
#घोषणा R_SDMON                         VIRT_ADDR(0x2, 0x1D)
#घोषणा R_SPKEQFILT                     VIRT_ADDR(0x3, 0x1)
#घोषणा R_SPKCRWDL                      VIRT_ADDR(0x3, 0x2)
#घोषणा R_SPKCRWDM                      VIRT_ADDR(0x3, 0x3)
#घोषणा R_SPKCRWDH                      VIRT_ADDR(0x3, 0x4)
#घोषणा R_SPKCRRDL                      VIRT_ADDR(0x3, 0x5)
#घोषणा R_SPKCRRDM                      VIRT_ADDR(0x3, 0x6)
#घोषणा R_SPKCRRDH                      VIRT_ADDR(0x3, 0x7)
#घोषणा R_SPKCRADD                      VIRT_ADDR(0x3, 0x8)
#घोषणा R_SPKCRS                        VIRT_ADDR(0x3, 0x9)
#घोषणा R_SPKMBCEN                      VIRT_ADDR(0x3, 0x0A)
#घोषणा R_SPKMBCCTL                     VIRT_ADDR(0x3, 0x0B)
#घोषणा R_SPKMBCMUG1                    VIRT_ADDR(0x3, 0x0C)
#घोषणा R_SPKMBCTHR1                    VIRT_ADDR(0x3, 0x0D)
#घोषणा R_SPKMBCRAT1                    VIRT_ADDR(0x3, 0x0E)
#घोषणा R_SPKMBCATK1L                   VIRT_ADDR(0x3, 0x0F)
#घोषणा R_SPKMBCATK1H                   VIRT_ADDR(0x3, 0x10)
#घोषणा R_SPKMBCREL1L                   VIRT_ADDR(0x3, 0x11)
#घोषणा R_SPKMBCREL1H                   VIRT_ADDR(0x3, 0x12)
#घोषणा R_SPKMBCMUG2                    VIRT_ADDR(0x3, 0x13)
#घोषणा R_SPKMBCTHR2                    VIRT_ADDR(0x3, 0x14)
#घोषणा R_SPKMBCRAT2                    VIRT_ADDR(0x3, 0x15)
#घोषणा R_SPKMBCATK2L                   VIRT_ADDR(0x3, 0x16)
#घोषणा R_SPKMBCATK2H                   VIRT_ADDR(0x3, 0x17)
#घोषणा R_SPKMBCREL2L                   VIRT_ADDR(0x3, 0x18)
#घोषणा R_SPKMBCREL2H                   VIRT_ADDR(0x3, 0x19)
#घोषणा R_SPKMBCMUG3                    VIRT_ADDR(0x3, 0x1A)
#घोषणा R_SPKMBCTHR3                    VIRT_ADDR(0x3, 0x1B)
#घोषणा R_SPKMBCRAT3                    VIRT_ADDR(0x3, 0x1C)
#घोषणा R_SPKMBCATK3L                   VIRT_ADDR(0x3, 0x1D)
#घोषणा R_SPKMBCATK3H                   VIRT_ADDR(0x3, 0x1E)
#घोषणा R_SPKMBCREL3L                   VIRT_ADDR(0x3, 0x1F)
#घोषणा R_SPKMBCREL3H                   VIRT_ADDR(0x3, 0x20)
#घोषणा R_SPKCLECTL                     VIRT_ADDR(0x3, 0x21)
#घोषणा R_SPKCLEMUG                     VIRT_ADDR(0x3, 0x22)
#घोषणा R_SPKCOMPTHR                    VIRT_ADDR(0x3, 0x23)
#घोषणा R_SPKCOMPRAT                    VIRT_ADDR(0x3, 0x24)
#घोषणा R_SPKCOMPATKL                   VIRT_ADDR(0x3, 0x25)
#घोषणा R_SPKCOMPATKH                   VIRT_ADDR(0x3, 0x26)
#घोषणा R_SPKCOMPRELL                   VIRT_ADDR(0x3, 0x27)
#घोषणा R_SPKCOMPRELH                   VIRT_ADDR(0x3, 0x28)
#घोषणा R_SPKLIMTHR                     VIRT_ADDR(0x3, 0x29)
#घोषणा R_SPKLIMTGT                     VIRT_ADDR(0x3, 0x2A)
#घोषणा R_SPKLIMATKL                    VIRT_ADDR(0x3, 0x2B)
#घोषणा R_SPKLIMATKH                    VIRT_ADDR(0x3, 0x2C)
#घोषणा R_SPKLIMRELL                    VIRT_ADDR(0x3, 0x2D)
#घोषणा R_SPKLIMRELH                    VIRT_ADDR(0x3, 0x2E)
#घोषणा R_SPKEXPTHR                     VIRT_ADDR(0x3, 0x2F)
#घोषणा R_SPKEXPRAT                     VIRT_ADDR(0x3, 0x30)
#घोषणा R_SPKEXPATKL                    VIRT_ADDR(0x3, 0x31)
#घोषणा R_SPKEXPATKH                    VIRT_ADDR(0x3, 0x32)
#घोषणा R_SPKEXPRELL                    VIRT_ADDR(0x3, 0x33)
#घोषणा R_SPKEXPRELH                    VIRT_ADDR(0x3, 0x34)
#घोषणा R_SPKFXCTL                      VIRT_ADDR(0x3, 0x35)
#घोषणा R_DACEQFILT                     VIRT_ADDR(0x4, 0x1)
#घोषणा R_DACCRWDL                      VIRT_ADDR(0x4, 0x2)
#घोषणा R_DACCRWDM                      VIRT_ADDR(0x4, 0x3)
#घोषणा R_DACCRWDH                      VIRT_ADDR(0x4, 0x4)
#घोषणा R_DACCRRDL                      VIRT_ADDR(0x4, 0x5)
#घोषणा R_DACCRRDM                      VIRT_ADDR(0x4, 0x6)
#घोषणा R_DACCRRDH                      VIRT_ADDR(0x4, 0x7)
#घोषणा R_DACCRADD                      VIRT_ADDR(0x4, 0x8)
#घोषणा R_DACCRS                        VIRT_ADDR(0x4, 0x9)
#घोषणा R_DACMBCEN                      VIRT_ADDR(0x4, 0x0A)
#घोषणा R_DACMBCCTL                     VIRT_ADDR(0x4, 0x0B)
#घोषणा R_DACMBCMUG1                    VIRT_ADDR(0x4, 0x0C)
#घोषणा R_DACMBCTHR1                    VIRT_ADDR(0x4, 0x0D)
#घोषणा R_DACMBCRAT1                    VIRT_ADDR(0x4, 0x0E)
#घोषणा R_DACMBCATK1L                   VIRT_ADDR(0x4, 0x0F)
#घोषणा R_DACMBCATK1H                   VIRT_ADDR(0x4, 0x10)
#घोषणा R_DACMBCREL1L                   VIRT_ADDR(0x4, 0x11)
#घोषणा R_DACMBCREL1H                   VIRT_ADDR(0x4, 0x12)
#घोषणा R_DACMBCMUG2                    VIRT_ADDR(0x4, 0x13)
#घोषणा R_DACMBCTHR2                    VIRT_ADDR(0x4, 0x14)
#घोषणा R_DACMBCRAT2                    VIRT_ADDR(0x4, 0x15)
#घोषणा R_DACMBCATK2L                   VIRT_ADDR(0x4, 0x16)
#घोषणा R_DACMBCATK2H                   VIRT_ADDR(0x4, 0x17)
#घोषणा R_DACMBCREL2L                   VIRT_ADDR(0x4, 0x18)
#घोषणा R_DACMBCREL2H                   VIRT_ADDR(0x4, 0x19)
#घोषणा R_DACMBCMUG3                    VIRT_ADDR(0x4, 0x1A)
#घोषणा R_DACMBCTHR3                    VIRT_ADDR(0x4, 0x1B)
#घोषणा R_DACMBCRAT3                    VIRT_ADDR(0x4, 0x1C)
#घोषणा R_DACMBCATK3L                   VIRT_ADDR(0x4, 0x1D)
#घोषणा R_DACMBCATK3H                   VIRT_ADDR(0x4, 0x1E)
#घोषणा R_DACMBCREL3L                   VIRT_ADDR(0x4, 0x1F)
#घोषणा R_DACMBCREL3H                   VIRT_ADDR(0x4, 0x20)
#घोषणा R_DACCLECTL                     VIRT_ADDR(0x4, 0x21)
#घोषणा R_DACCLEMUG                     VIRT_ADDR(0x4, 0x22)
#घोषणा R_DACCOMPTHR                    VIRT_ADDR(0x4, 0x23)
#घोषणा R_DACCOMPRAT                    VIRT_ADDR(0x4, 0x24)
#घोषणा R_DACCOMPATKL                   VIRT_ADDR(0x4, 0x25)
#घोषणा R_DACCOMPATKH                   VIRT_ADDR(0x4, 0x26)
#घोषणा R_DACCOMPRELL                   VIRT_ADDR(0x4, 0x27)
#घोषणा R_DACCOMPRELH                   VIRT_ADDR(0x4, 0x28)
#घोषणा R_DACLIMTHR                     VIRT_ADDR(0x4, 0x29)
#घोषणा R_DACLIMTGT                     VIRT_ADDR(0x4, 0x2A)
#घोषणा R_DACLIMATKL                    VIRT_ADDR(0x4, 0x2B)
#घोषणा R_DACLIMATKH                    VIRT_ADDR(0x4, 0x2C)
#घोषणा R_DACLIMRELL                    VIRT_ADDR(0x4, 0x2D)
#घोषणा R_DACLIMRELH                    VIRT_ADDR(0x4, 0x2E)
#घोषणा R_DACEXPTHR                     VIRT_ADDR(0x4, 0x2F)
#घोषणा R_DACEXPRAT                     VIRT_ADDR(0x4, 0x30)
#घोषणा R_DACEXPATKL                    VIRT_ADDR(0x4, 0x31)
#घोषणा R_DACEXPATKH                    VIRT_ADDR(0x4, 0x32)
#घोषणा R_DACEXPRELL                    VIRT_ADDR(0x4, 0x33)
#घोषणा R_DACEXPRELH                    VIRT_ADDR(0x4, 0x34)
#घोषणा R_DACFXCTL                      VIRT_ADDR(0x4, 0x35)
#घोषणा R_SUBEQFILT                     VIRT_ADDR(0x5, 0x1)
#घोषणा R_SUBCRWDL                      VIRT_ADDR(0x5, 0x2)
#घोषणा R_SUBCRWDM                      VIRT_ADDR(0x5, 0x3)
#घोषणा R_SUBCRWDH                      VIRT_ADDR(0x5, 0x4)
#घोषणा R_SUBCRRDL                      VIRT_ADDR(0x5, 0x5)
#घोषणा R_SUBCRRDM                      VIRT_ADDR(0x5, 0x6)
#घोषणा R_SUBCRRDH                      VIRT_ADDR(0x5, 0x7)
#घोषणा R_SUBCRADD                      VIRT_ADDR(0x5, 0x8)
#घोषणा R_SUBCRS                        VIRT_ADDR(0x5, 0x9)
#घोषणा R_SUBMBCEN                      VIRT_ADDR(0x5, 0x0A)
#घोषणा R_SUBMBCCTL                     VIRT_ADDR(0x5, 0x0B)
#घोषणा R_SUBMBCMUG1                    VIRT_ADDR(0x5, 0x0C)
#घोषणा R_SUBMBCTHR1                    VIRT_ADDR(0x5, 0x0D)
#घोषणा R_SUBMBCRAT1                    VIRT_ADDR(0x5, 0x0E)
#घोषणा R_SUBMBCATK1L                   VIRT_ADDR(0x5, 0x0F)
#घोषणा R_SUBMBCATK1H                   VIRT_ADDR(0x5, 0x10)
#घोषणा R_SUBMBCREL1L                   VIRT_ADDR(0x5, 0x11)
#घोषणा R_SUBMBCREL1H                   VIRT_ADDR(0x5, 0x12)
#घोषणा R_SUBMBCMUG2                    VIRT_ADDR(0x5, 0x13)
#घोषणा R_SUBMBCTHR2                    VIRT_ADDR(0x5, 0x14)
#घोषणा R_SUBMBCRAT2                    VIRT_ADDR(0x5, 0x15)
#घोषणा R_SUBMBCATK2L                   VIRT_ADDR(0x5, 0x16)
#घोषणा R_SUBMBCATK2H                   VIRT_ADDR(0x5, 0x17)
#घोषणा R_SUBMBCREL2L                   VIRT_ADDR(0x5, 0x18)
#घोषणा R_SUBMBCREL2H                   VIRT_ADDR(0x5, 0x19)
#घोषणा R_SUBMBCMUG3                    VIRT_ADDR(0x5, 0x1A)
#घोषणा R_SUBMBCTHR3                    VIRT_ADDR(0x5, 0x1B)
#घोषणा R_SUBMBCRAT3                    VIRT_ADDR(0x5, 0x1C)
#घोषणा R_SUBMBCATK3L                   VIRT_ADDR(0x5, 0x1D)
#घोषणा R_SUBMBCATK3H                   VIRT_ADDR(0x5, 0x1E)
#घोषणा R_SUBMBCREL3L                   VIRT_ADDR(0x5, 0x1F)
#घोषणा R_SUBMBCREL3H                   VIRT_ADDR(0x5, 0x20)
#घोषणा R_SUBCLECTL                     VIRT_ADDR(0x5, 0x21)
#घोषणा R_SUBCLEMUG                     VIRT_ADDR(0x5, 0x22)
#घोषणा R_SUBCOMPTHR                    VIRT_ADDR(0x5, 0x23)
#घोषणा R_SUBCOMPRAT                    VIRT_ADDR(0x5, 0x24)
#घोषणा R_SUBCOMPATKL                   VIRT_ADDR(0x5, 0x25)
#घोषणा R_SUBCOMPATKH                   VIRT_ADDR(0x5, 0x26)
#घोषणा R_SUBCOMPRELL                   VIRT_ADDR(0x5, 0x27)
#घोषणा R_SUBCOMPRELH                   VIRT_ADDR(0x5, 0x28)
#घोषणा R_SUBLIMTHR                     VIRT_ADDR(0x5, 0x29)
#घोषणा R_SUBLIMTGT                     VIRT_ADDR(0x5, 0x2A)
#घोषणा R_SUBLIMATKL                    VIRT_ADDR(0x5, 0x2B)
#घोषणा R_SUBLIMATKH                    VIRT_ADDR(0x5, 0x2C)
#घोषणा R_SUBLIMRELL                    VIRT_ADDR(0x5, 0x2D)
#घोषणा R_SUBLIMRELH                    VIRT_ADDR(0x5, 0x2E)
#घोषणा R_SUBEXPTHR                     VIRT_ADDR(0x5, 0x2F)
#घोषणा R_SUBEXPRAT                     VIRT_ADDR(0x5, 0x30)
#घोषणा R_SUBEXPATKL                    VIRT_ADDR(0x5, 0x31)
#घोषणा R_SUBEXPATKH                    VIRT_ADDR(0x5, 0x32)
#घोषणा R_SUBEXPRELL                    VIRT_ADDR(0x5, 0x33)
#घोषणा R_SUBEXPRELH                    VIRT_ADDR(0x5, 0x34)
#घोषणा R_SUBFXCTL                      VIRT_ADDR(0x5, 0x35)

// *** PLLCTL ***
#घोषणा FB_PLLCTL_VCCI_PLL                                  6
#घोषणा FM_PLLCTL_VCCI_PLL                                  0xC0

#घोषणा FB_PLLCTL_RZ_PLL                                    3
#घोषणा FM_PLLCTL_RZ_PLL                                    0x38

#घोषणा FB_PLLCTL_CP_PLL                                    0
#घोषणा FM_PLLCTL_CP_PLL                                    0x7

// *** PLLRDIV ***
#घोषणा FB_PLLRDIV_REFDIV_PLL                               0
#घोषणा FM_PLLRDIV_REFDIV_PLL                               0xFF

// *** PLLODIV ***
#घोषणा FB_PLLODIV_OUTDIV_PLL                               0
#घोषणा FM_PLLODIV_OUTDIV_PLL                               0xFF

// *** PLLFDIVL ***
#घोषणा FB_PLLFDIVL_FBDIVL_PLL                              0
#घोषणा FM_PLLFDIVL_FBDIVL_PLL                              0xFF

// *** PLLFDIVH ***
#घोषणा FB_PLLFDIVH_FBDIVH_PLL                              0
#घोषणा FM_PLLFDIVH_FBDIVH_PLL                              0xF

// *** I2SPCTL ***
#घोषणा FB_I2SPCTL_BCLKSTAT                                 7
#घोषणा FM_I2SPCTL_BCLKSTAT                                 0x80
#घोषणा FV_BCLKSTAT_LOST                                    0x80
#घोषणा FV_BCLKSTAT_NOT_LOST                                0x0

#घोषणा FB_I2SPCTL_BCLKP                                    6
#घोषणा FM_I2SPCTL_BCLKP                                    0x40
#घोषणा FV_BCLKP_NOT_INVERTED                               0x0
#घोषणा FV_BCLKP_INVERTED                                   0x40

#घोषणा FB_I2SPCTL_PORTMS                                   5
#घोषणा FM_I2SPCTL_PORTMS                                   0x20
#घोषणा FV_PORTMS_SLAVE                                     0x0
#घोषणा FV_PORTMS_MASTER                                    0x20

#घोषणा FB_I2SPCTL_LRCLKP                                   4
#घोषणा FM_I2SPCTL_LRCLKP                                   0x10
#घोषणा FV_LRCLKP_NOT_INVERTED                              0x0
#घोषणा FV_LRCLKP_INVERTED                                  0x10

#घोषणा FB_I2SPCTL_WL                                       2
#घोषणा FM_I2SPCTL_WL                                       0xC
#घोषणा FV_WL_16                                            0x0
#घोषणा FV_WL_20                                            0x4
#घोषणा FV_WL_24                                            0x8
#घोषणा FV_WL_32                                            0xC

#घोषणा FB_I2SPCTL_FORMAT                                   0
#घोषणा FM_I2SPCTL_FORMAT                                   0x3
#घोषणा FV_FORMAT_RIGHT                                     0x0
#घोषणा FV_FORMAT_LEFT                                      0x1
#घोषणा FV_FORMAT_I2S                                       0x2
#घोषणा FV_FORMAT_TDM                                       0x3

// *** I2SMRATE ***
#घोषणा FB_I2SMRATE_I2SMCLKHALF                             7
#घोषणा FM_I2SMRATE_I2SMCLKHALF                             0x80
#घोषणा FV_I2SMCLKHALF_I2S1MCLKDIV_DIV_2                    0x0
#घोषणा FV_I2SMCLKHALF_I2S1MCLKDIV_ONLY                     0x80

#घोषणा FB_I2SMRATE_I2SMCLKDIV                              5
#घोषणा FM_I2SMRATE_I2SMCLKDIV                              0x60
#घोषणा FV_I2SMCLKDIV_125                                   0x0
#घोषणा FV_I2SMCLKDIV_128                                   0x20
#घोषणा FV_I2SMCLKDIV_136                                   0x40
#घोषणा FV_I2SMCLKDIV_192                                   0x60

#घोषणा FB_I2SMRATE_I2SMBR                                  3
#घोषणा FM_I2SMRATE_I2SMBR                                  0x18
#घोषणा FV_I2SMBR_32                                        0x0
#घोषणा FV_I2SMBR_44PT1                                     0x8
#घोषणा FV_I2SMBR_48                                        0x10
#घोषणा FV_I2SMBR_MCLK_MODE                                 0x18

#घोषणा FB_I2SMRATE_I2SMBM                                  0
#घोषणा FM_I2SMRATE_I2SMBM                                  0x3
#घोषणा FV_I2SMBM_0PT25                                     0x0
#घोषणा FV_I2SMBM_0PT5                                      0x1
#घोषणा FV_I2SMBM_1                                         0x2
#घोषणा FV_I2SMBM_2                                         0x3

// *** PCMPCTL0 ***
#घोषणा FB_PCMPCTL0_PCMFLENP                                2
#घोषणा FM_PCMPCTL0_PCMFLENP                                0x4
#घोषणा FV_PCMFLENP_128                                     0x0
#घोषणा FV_PCMFLENP_256                                     0x4

#घोषणा FB_PCMPCTL0_SLSYNCP                                 1
#घोषणा FM_PCMPCTL0_SLSYNCP                                 0x2
#घोषणा FV_SLSYNCP_SHORT                                    0x0
#घोषणा FV_SLSYNCP_LONG                                     0x2

#घोषणा FB_PCMPCTL0_BDELAYP                                 0
#घोषणा FM_PCMPCTL0_BDELAYP                                 0x1
#घोषणा FV_BDELAYP_NO_DELAY                                 0x0
#घोषणा FV_BDELAYP_1BCLK_DELAY                              0x1

// *** PCMPCTL1 ***
#घोषणा FB_PCMPCTL1_PCMMOMP                                 6
#घोषणा FM_PCMPCTL1_PCMMOMP                                 0x40

#घोषणा FB_PCMPCTL1_PCMSOP                                  5
#घोषणा FM_PCMPCTL1_PCMSOP                                  0x20
#घोषणा FV_PCMSOP_1                                         0x0
#घोषणा FV_PCMSOP_2                                         0x20

#घोषणा FB_PCMPCTL1_PCMDSSP                                 3
#घोषणा FM_PCMPCTL1_PCMDSSP                                 0x18
#घोषणा FV_PCMDSSP_16                                       0x0
#घोषणा FV_PCMDSSP_24                                       0x8
#घोषणा FV_PCMDSSP_32                                       0x10

#घोषणा FB_PCMPCTL1_PCMMIMP                                 1
#घोषणा FM_PCMPCTL1_PCMMIMP                                 0x2

#घोषणा FB_PCMPCTL1_PCMSIP                                  0
#घोषणा FM_PCMPCTL1_PCMSIP                                  0x1
#घोषणा FV_PCMSIP_1                                         0x0
#घोषणा FV_PCMSIP_2                                         0x1

// *** CHAIC ***
#घोषणा FB_CHAIC_MICBST                                     4
#घोषणा FM_CHAIC_MICBST                                     0x30

// *** PGACTL ***
#घोषणा FB_PGACTL_PGAMUTE                                   7
#घोषणा FM_PGACTL_PGAMUTE                                   0x80

#घोषणा FB_PGACTL_PGAVOL                                    0
#घोषणा FM_PGACTL_PGAVOL                                    0x3F

// *** ICHVOL ***
#घोषणा FB_ICHVOL_ICHVOL                                    0
#घोषणा FM_ICHVOL_ICHVOL                                    0xFF

// *** SPKMBCMUG ***
#घोषणा FB_SPKMBCMUG_PHASE                                  5
#घोषणा FM_SPKMBCMUG_PHASE                                  0x20

#घोषणा FB_SPKMBCMUG_MUGAIN                                 0
#घोषणा FM_SPKMBCMUG_MUGAIN                                 0x1F

// *** SPKMBCTHR ***
#घोषणा FB_SPKMBCTHR_THRESH                                 0
#घोषणा FM_SPKMBCTHR_THRESH                                 0xFF

// *** SPKMBCRAT ***
#घोषणा FB_SPKMBCRAT_RATIO                                  0
#घोषणा FM_SPKMBCRAT_RATIO                                  0x1F

// *** SPKMBCATKL ***
#घोषणा FB_SPKMBCATKL_TCATKL                                0
#घोषणा FM_SPKMBCATKL_TCATKL                                0xFF

// *** SPKMBCATKH ***
#घोषणा FB_SPKMBCATKH_TCATKH                                0
#घोषणा FM_SPKMBCATKH_TCATKH                                0xFF

// *** SPKMBCRELL ***
#घोषणा FB_SPKMBCRELL_TCRELL                                0
#घोषणा FM_SPKMBCRELL_TCRELL                                0xFF

// *** SPKMBCRELH ***
#घोषणा FB_SPKMBCRELH_TCRELH                                0
#घोषणा FM_SPKMBCRELH_TCRELH                                0xFF

// *** DACMBCMUG ***
#घोषणा FB_DACMBCMUG_PHASE                                  5
#घोषणा FM_DACMBCMUG_PHASE                                  0x20

#घोषणा FB_DACMBCMUG_MUGAIN                                 0
#घोषणा FM_DACMBCMUG_MUGAIN                                 0x1F

// *** DACMBCTHR ***
#घोषणा FB_DACMBCTHR_THRESH                                 0
#घोषणा FM_DACMBCTHR_THRESH                                 0xFF

// *** DACMBCRAT ***
#घोषणा FB_DACMBCRAT_RATIO                                  0
#घोषणा FM_DACMBCRAT_RATIO                                  0x1F

// *** DACMBCATKL ***
#घोषणा FB_DACMBCATKL_TCATKL                                0
#घोषणा FM_DACMBCATKL_TCATKL                                0xFF

// *** DACMBCATKH ***
#घोषणा FB_DACMBCATKH_TCATKH                                0
#घोषणा FM_DACMBCATKH_TCATKH                                0xFF

// *** DACMBCRELL ***
#घोषणा FB_DACMBCRELL_TCRELL                                0
#घोषणा FM_DACMBCRELL_TCRELL                                0xFF

// *** DACMBCRELH ***
#घोषणा FB_DACMBCRELH_TCRELH                                0
#घोषणा FM_DACMBCRELH_TCRELH                                0xFF

// *** SUBMBCMUG ***
#घोषणा FB_SUBMBCMUG_PHASE                                  5
#घोषणा FM_SUBMBCMUG_PHASE                                  0x20

#घोषणा FB_SUBMBCMUG_MUGAIN                                 0
#घोषणा FM_SUBMBCMUG_MUGAIN                                 0x1F

// *** SUBMBCTHR ***
#घोषणा FB_SUBMBCTHR_THRESH                                 0
#घोषणा FM_SUBMBCTHR_THRESH                                 0xFF

// *** SUBMBCRAT ***
#घोषणा FB_SUBMBCRAT_RATIO                                  0
#घोषणा FM_SUBMBCRAT_RATIO                                  0x1F

// *** SUBMBCATKL ***
#घोषणा FB_SUBMBCATKL_TCATKL                                0
#घोषणा FM_SUBMBCATKL_TCATKL                                0xFF

// *** SUBMBCATKH ***
#घोषणा FB_SUBMBCATKH_TCATKH                                0
#घोषणा FM_SUBMBCATKH_TCATKH                                0xFF

// *** SUBMBCRELL ***
#घोषणा FB_SUBMBCRELL_TCRELL                                0
#घोषणा FM_SUBMBCRELL_TCRELL                                0xFF

// *** SUBMBCRELH ***
#घोषणा FB_SUBMBCRELH_TCRELH                                0
#घोषणा FM_SUBMBCRELH_TCRELH                                0xFF

// *** PAGESEL ***
#घोषणा FB_PAGESEL_PAGESEL                                  0
#घोषणा FM_PAGESEL_PAGESEL                                  0xFF

// *** RESET ***
#घोषणा FB_RESET_RESET                                      0
#घोषणा FM_RESET_RESET                                      0xFF
#घोषणा FV_RESET_PWR_ON_DEFAULTS                            0x85

// *** IRQEN ***
#घोषणा FB_IRQEN_THRMINTEN                                  6
#घोषणा FM_IRQEN_THRMINTEN                                  0x40
#घोषणा FV_THRMINTEN_ENABLED                                0x40
#घोषणा FV_THRMINTEN_DISABLED                               0x0

#घोषणा FB_IRQEN_HBPINTEN                                   5
#घोषणा FM_IRQEN_HBPINTEN                                   0x20
#घोषणा FV_HBPINTEN_ENABLED                                 0x20
#घोषणा FV_HBPINTEN_DISABLED                                0x0

#घोषणा FB_IRQEN_HSDINTEN                                   4
#घोषणा FM_IRQEN_HSDINTEN                                   0x10
#घोषणा FV_HSDINTEN_ENABLED                                 0x10
#घोषणा FV_HSDINTEN_DISABLED                                0x0

#घोषणा FB_IRQEN_HPDINTEN                                   3
#घोषणा FM_IRQEN_HPDINTEN                                   0x8
#घोषणा FV_HPDINTEN_ENABLED                                 0x8
#घोषणा FV_HPDINTEN_DISABLED                                0x0

#घोषणा FB_IRQEN_GPIO3INTEN                                 1
#घोषणा FM_IRQEN_GPIO3INTEN                                 0x2
#घोषणा FV_GPIO3INTEN_ENABLED                               0x2
#घोषणा FV_GPIO3INTEN_DISABLED                              0x0

#घोषणा FB_IRQEN_GPIO2INTEN                                 0
#घोषणा FM_IRQEN_GPIO2INTEN                                 0x1
#घोषणा FV_GPIO2INTEN_ENABLED                               0x1
#घोषणा FV_GPIO2INTEN_DISABLED                              0x0

#घोषणा IRQEN_GPIOINTEN_ENABLED                             0x1
#घोषणा IRQEN_GPIOINTEN_DISABLED                            0x0

// *** IRQMASK ***
#घोषणा FB_IRQMASK_THRMIM                                   6
#घोषणा FM_IRQMASK_THRMIM                                   0x40
#घोषणा FV_THRMIM_MASKED                                    0x0
#घोषणा FV_THRMIM_NOT_MASKED                                0x40

#घोषणा FB_IRQMASK_HBPIM                                    5
#घोषणा FM_IRQMASK_HBPIM                                    0x20
#घोषणा FV_HBPIM_MASKED                                     0x0
#घोषणा FV_HBPIM_NOT_MASKED                                 0x20

#घोषणा FB_IRQMASK_HSDIM                                    4
#घोषणा FM_IRQMASK_HSDIM                                    0x10
#घोषणा FV_HSDIM_MASKED                                     0x0
#घोषणा FV_HSDIM_NOT_MASKED                                 0x10

#घोषणा FB_IRQMASK_HPDIM                                    3
#घोषणा FM_IRQMASK_HPDIM                                    0x8
#घोषणा FV_HPDIM_MASKED                                     0x0
#घोषणा FV_HPDIM_NOT_MASKED                                 0x8

#घोषणा FB_IRQMASK_GPIO3M                                   1
#घोषणा FM_IRQMASK_GPIO3M                                   0x2
#घोषणा FV_GPIO3M_MASKED                                    0x0
#घोषणा FV_GPIO3M_NOT_MASKED                                0x2

#घोषणा FB_IRQMASK_GPIO2M                                   0
#घोषणा FM_IRQMASK_GPIO2M                                   0x1
#घोषणा FV_GPIO2M_MASKED                                    0x0
#घोषणा FV_GPIO2M_NOT_MASKED                                0x1

#घोषणा IRQMASK_GPIOM_MASKED                                0x0
#घोषणा IRQMASK_GPIOM_NOT_MASKED                            0x1

// *** IRQSTAT ***
#घोषणा FB_IRQSTAT_THRMINT                                  6
#घोषणा FM_IRQSTAT_THRMINT                                  0x40
#घोषणा FV_THRMINT_INTERRUPTED                              0x40
#घोषणा FV_THRMINT_NOT_INTERRUPTED                          0x0

#घोषणा FB_IRQSTAT_HBPINT                                   5
#घोषणा FM_IRQSTAT_HBPINT                                   0x20
#घोषणा FV_HBPINT_INTERRUPTED                               0x20
#घोषणा FV_HBPINT_NOT_INTERRUPTED                           0x0

#घोषणा FB_IRQSTAT_HSDINT                                   4
#घोषणा FM_IRQSTAT_HSDINT                                   0x10
#घोषणा FV_HSDINT_INTERRUPTED                               0x10
#घोषणा FV_HSDINT_NOT_INTERRUPTED                           0x0

#घोषणा FB_IRQSTAT_HPDINT                                   3
#घोषणा FM_IRQSTAT_HPDINT                                   0x8
#घोषणा FV_HPDINT_INTERRUPTED                               0x8
#घोषणा FV_HPDINT_NOT_INTERRUPTED                           0x0

#घोषणा FB_IRQSTAT_GPIO3INT                                 1
#घोषणा FM_IRQSTAT_GPIO3INT                                 0x2
#घोषणा FV_GPIO3INT_INTERRUPTED                             0x2
#घोषणा FV_GPIO3INT_NOT_INTERRUPTED                         0x0

#घोषणा FB_IRQSTAT_GPIO2INT                                 0
#घोषणा FM_IRQSTAT_GPIO2INT                                 0x1
#घोषणा FV_GPIO2INT_INTERRUPTED                             0x1
#घोषणा FV_GPIO2INT_NOT_INTERRUPTED                         0x0

#घोषणा IRQSTAT_GPIOINT_INTERRUPTED                         0x1
#घोषणा IRQSTAT_GPIOINT_NOT_INTERRUPTED                     0x0

// *** DEVADD0 ***
#घोषणा FB_DEVADD0_DEVADD0                                  1
#घोषणा FM_DEVADD0_DEVADD0                                  0xFE

#घोषणा FB_DEVADD0_I2C_ADDRLK                               0
#घोषणा FM_DEVADD0_I2C_ADDRLK                               0x1
#घोषणा FV_I2C_ADDRLK_LOCK                                  0x1

// *** DEVID ***
#घोषणा FB_DEVID_DEV_ID                                     0
#घोषणा FM_DEVID_DEV_ID                                     0xFF

// *** DEVREV ***
#घोषणा FB_DEVREV_MAJ_REV                                   4
#घोषणा FM_DEVREV_MAJ_REV                                   0xF0

#घोषणा FB_DEVREV_MIN_REV                                   0
#घोषणा FM_DEVREV_MIN_REV                                   0xF

// *** PLLSTAT ***
#घोषणा FB_PLLSTAT_PLL2LK                                   1
#घोषणा FM_PLLSTAT_PLL2LK                                   0x2
#घोषणा FV_PLL2LK_LOCKED                                    0x2
#घोषणा FV_PLL2LK_UNLOCKED                                  0x0

#घोषणा FB_PLLSTAT_PLL1LK                                   0
#घोषणा FM_PLLSTAT_PLL1LK                                   0x1
#घोषणा FV_PLL1LK_LOCKED                                    0x1
#घोषणा FV_PLL1LK_UNLOCKED                                  0x0

#घोषणा PLLSTAT_PLLLK_LOCKED                                0x1
#घोषणा PLLSTAT_PLLLK_UNLOCKED                              0x0

// *** PLLCTL ***
#घोषणा FB_PLLCTL_PU_PLL2                                   7
#घोषणा FM_PLLCTL_PU_PLL2                                   0x80
#घोषणा FV_PU_PLL2_PWR_UP                                   0x80
#घोषणा FV_PU_PLL2_PWR_DWN                                  0x0

#घोषणा FB_PLLCTL_PU_PLL1                                   6
#घोषणा FM_PLLCTL_PU_PLL1                                   0x40
#घोषणा FV_PU_PLL1_PWR_UP                                   0x40
#घोषणा FV_PU_PLL1_PWR_DWN                                  0x0

#घोषणा FB_PLLCTL_PLL2CLKEN                                 5
#घोषणा FM_PLLCTL_PLL2CLKEN                                 0x20
#घोषणा FV_PLL2CLKEN_ENABLE                                 0x20
#घोषणा FV_PLL2CLKEN_DISABLE                                0x0

#घोषणा FB_PLLCTL_PLL1CLKEN                                 4
#घोषणा FM_PLLCTL_PLL1CLKEN                                 0x10
#घोषणा FV_PLL1CLKEN_ENABLE                                 0x10
#घोषणा FV_PLL1CLKEN_DISABLE                                0x0

#घोषणा FB_PLLCTL_BCLKSEL                                   2
#घोषणा FM_PLLCTL_BCLKSEL                                   0xC
#घोषणा FV_BCLKSEL_BCLK1                                    0x0
#घोषणा FV_BCLKSEL_BCLK2                                    0x4
#घोषणा FV_BCLKSEL_BCLK3                                    0x8

#घोषणा FB_PLLCTL_PLLISEL                                   0
#घोषणा FM_PLLCTL_PLLISEL                                   0x3
#घोषणा FV_PLLISEL_XTAL                                     0x0
#घोषणा FV_PLLISEL_MCLK1                                    0x1
#घोषणा FV_PLLISEL_MCLK2                                    0x2
#घोषणा FV_PLLISEL_BCLK                                     0x3

#घोषणा PLLCTL_PU_PLL_PWR_UP                                0x1
#घोषणा PLLCTL_PU_PLL_PWR_DWN                               0x0
#घोषणा PLLCTL_PLLCLKEN_ENABLE                              0x1
#घोषणा PLLCTL_PLLCLKEN_DISABLE                             0x0

// *** ISRC ***
#घोषणा FB_ISRC_IBR                                         2
#घोषणा FM_ISRC_IBR                                         0x4
#घोषणा FV_IBR_44PT1                                        0x0
#घोषणा FV_IBR_48                                           0x4

#घोषणा FB_ISRC_IBM                                         0
#घोषणा FM_ISRC_IBM                                         0x3
#घोषणा FV_IBM_0PT25                                        0x0
#घोषणा FV_IBM_0PT5                                         0x1
#घोषणा FV_IBM_1                                            0x2
#घोषणा FV_IBM_2                                            0x3

// *** SCLKCTL ***
#घोषणा FB_SCLKCTL_ASDM                                     6
#घोषणा FM_SCLKCTL_ASDM                                     0xC0
#घोषणा FV_ASDM_HALF                                        0x40
#घोषणा FV_ASDM_FULL                                        0x80
#घोषणा FV_ASDM_AUTO                                        0xC0

#घोषणा FB_SCLKCTL_DSDM                                     4
#घोषणा FM_SCLKCTL_DSDM                                     0x30
#घोषणा FV_DSDM_HALF                                        0x10
#घोषणा FV_DSDM_FULL                                        0x20
#घोषणा FV_DSDM_AUTO                                        0x30

// *** TIMEBASE ***
#घोषणा FB_TIMEBASE_TIMEBASE                                0
#घोषणा FM_TIMEBASE_TIMEBASE                                0xFF

// *** I2SCMC ***
#घोषणा FB_I2SCMC_BCMP3                                     4
#घोषणा FM_I2SCMC_BCMP3                                     0x30
#घोषणा FV_BCMP3_AUTO                                       0x0
#घोषणा FV_BCMP3_32X                                        0x10
#घोषणा FV_BCMP3_40X                                        0x20
#घोषणा FV_BCMP3_64X                                        0x30

#घोषणा FB_I2SCMC_BCMP2                                     2
#घोषणा FM_I2SCMC_BCMP2                                     0xC
#घोषणा FV_BCMP2_AUTO                                       0x0
#घोषणा FV_BCMP2_32X                                        0x4
#घोषणा FV_BCMP2_40X                                        0x8
#घोषणा FV_BCMP2_64X                                        0xC

#घोषणा FB_I2SCMC_BCMP1                                     0
#घोषणा FM_I2SCMC_BCMP1                                     0x3
#घोषणा FV_BCMP1_AUTO                                       0x0
#घोषणा FV_BCMP1_32X                                        0x1
#घोषणा FV_BCMP1_40X                                        0x2
#घोषणा FV_BCMP1_64X                                        0x3

#घोषणा I2SCMC_BCMP_AUTO                                    0x0
#घोषणा I2SCMC_BCMP_32X                                     0x1
#घोषणा I2SCMC_BCMP_40X                                     0x2
#घोषणा I2SCMC_BCMP_64X                                     0x3

// *** MCLK2PINC ***
#घोषणा FB_MCLK2PINC_SLEWOUT                                4
#घोषणा FM_MCLK2PINC_SLEWOUT                                0xF0

#घोषणा FB_MCLK2PINC_MCLK2IO                                2
#घोषणा FM_MCLK2PINC_MCLK2IO                                0x4
#घोषणा FV_MCLK2IO_INPUT                                    0x0
#घोषणा FV_MCLK2IO_OUTPUT                                   0x4

#घोषणा FB_MCLK2PINC_MCLK2OS                                0
#घोषणा FM_MCLK2PINC_MCLK2OS                                0x3
#घोषणा FV_MCLK2OS_24PT576                                  0x0
#घोषणा FV_MCLK2OS_22PT5792                                 0x1
#घोषणा FV_MCLK2OS_PLL2                                     0x2

// *** I2SPINC0 ***
#घोषणा FB_I2SPINC0_SDO3TRI                                 7
#घोषणा FM_I2SPINC0_SDO3TRI                                 0x80

#घोषणा FB_I2SPINC0_SDO2TRI                                 6
#घोषणा FM_I2SPINC0_SDO2TRI                                 0x40

#घोषणा FB_I2SPINC0_SDO1TRI                                 5
#घोषणा FM_I2SPINC0_SDO1TRI                                 0x20

#घोषणा FB_I2SPINC0_PCM3TRI                                 2
#घोषणा FM_I2SPINC0_PCM3TRI                                 0x4

#घोषणा FB_I2SPINC0_PCM2TRI                                 1
#घोषणा FM_I2SPINC0_PCM2TRI                                 0x2

#घोषणा FB_I2SPINC0_PCM1TRI                                 0
#घोषणा FM_I2SPINC0_PCM1TRI                                 0x1

// *** I2SPINC1 ***
#घोषणा FB_I2SPINC1_SDO3PDD                                 2
#घोषणा FM_I2SPINC1_SDO3PDD                                 0x4

#घोषणा FB_I2SPINC1_SDO2PDD                                 1
#घोषणा FM_I2SPINC1_SDO2PDD                                 0x2

#घोषणा FB_I2SPINC1_SDO1PDD                                 0
#घोषणा FM_I2SPINC1_SDO1PDD                                 0x1

// *** I2SPINC2 ***
#घोषणा FB_I2SPINC2_LR3PDD                                  5
#घोषणा FM_I2SPINC2_LR3PDD                                  0x20

#घोषणा FB_I2SPINC2_BC3PDD                                  4
#घोषणा FM_I2SPINC2_BC3PDD                                  0x10

#घोषणा FB_I2SPINC2_LR2PDD                                  3
#घोषणा FM_I2SPINC2_LR2PDD                                  0x8

#घोषणा FB_I2SPINC2_BC2PDD                                  2
#घोषणा FM_I2SPINC2_BC2PDD                                  0x4

#घोषणा FB_I2SPINC2_LR1PDD                                  1
#घोषणा FM_I2SPINC2_LR1PDD                                  0x2

#घोषणा FB_I2SPINC2_BC1PDD                                  0
#घोषणा FM_I2SPINC2_BC1PDD                                  0x1

// *** GPIOCTL0 ***
#घोषणा FB_GPIOCTL0_GPIO3INTP                               7
#घोषणा FM_GPIOCTL0_GPIO3INTP                               0x80

#घोषणा FB_GPIOCTL0_GPIO2INTP                               6
#घोषणा FM_GPIOCTL0_GPIO2INTP                               0x40

#घोषणा FB_GPIOCTL0_GPIO3CFG                                5
#घोषणा FM_GPIOCTL0_GPIO3CFG                                0x20

#घोषणा FB_GPIOCTL0_GPIO2CFG                                4
#घोषणा FM_GPIOCTL0_GPIO2CFG                                0x10

#घोषणा FB_GPIOCTL0_GPIO3IO                                 3
#घोषणा FM_GPIOCTL0_GPIO3IO                                 0x8

#घोषणा FB_GPIOCTL0_GPIO2IO                                 2
#घोषणा FM_GPIOCTL0_GPIO2IO                                 0x4

#घोषणा FB_GPIOCTL0_GPIO1IO                                 1
#घोषणा FM_GPIOCTL0_GPIO1IO                                 0x2

#घोषणा FB_GPIOCTL0_GPIO0IO                                 0
#घोषणा FM_GPIOCTL0_GPIO0IO                                 0x1

// *** GPIOCTL1 ***
#घोषणा FB_GPIOCTL1_GPIO3                                   7
#घोषणा FM_GPIOCTL1_GPIO3                                   0x80

#घोषणा FB_GPIOCTL1_GPIO2                                   6
#घोषणा FM_GPIOCTL1_GPIO2                                   0x40

#घोषणा FB_GPIOCTL1_GPIO1                                   5
#घोषणा FM_GPIOCTL1_GPIO1                                   0x20

#घोषणा FB_GPIOCTL1_GPIO0                                   4
#घोषणा FM_GPIOCTL1_GPIO0                                   0x10

#घोषणा FB_GPIOCTL1_GPIO3RD                                 3
#घोषणा FM_GPIOCTL1_GPIO3RD                                 0x8

#घोषणा FB_GPIOCTL1_GPIO2RD                                 2
#घोषणा FM_GPIOCTL1_GPIO2RD                                 0x4

#घोषणा FB_GPIOCTL1_GPIO1RD                                 1
#घोषणा FM_GPIOCTL1_GPIO1RD                                 0x2

#घोषणा FB_GPIOCTL1_GPIO0RD                                 0
#घोषणा FM_GPIOCTL1_GPIO0RD                                 0x1

// *** ASRC ***
#घोषणा FB_ASRC_ASRCOBW                                     7
#घोषणा FM_ASRC_ASRCOBW                                     0x80

#घोषणा FB_ASRC_ASRCIBW                                     6
#घोषणा FM_ASRC_ASRCIBW                                     0x40

#घोषणा FB_ASRC_ASRCOB                                      5
#घोषणा FM_ASRC_ASRCOB                                      0x20
#घोषणा FV_ASRCOB_ACTIVE                                    0x0
#घोषणा FV_ASRCOB_BYPASSED                                  0x20

#घोषणा FB_ASRC_ASRCIB                                      4
#घोषणा FM_ASRC_ASRCIB                                      0x10
#घोषणा FV_ASRCIB_ACTIVE                                    0x0
#घोषणा FV_ASRCIB_BYPASSED                                  0x10

#घोषणा FB_ASRC_ASRCOL                                      3
#घोषणा FM_ASRC_ASRCOL                                      0x8

#घोषणा FB_ASRC_ASRCIL                                      2
#घोषणा FM_ASRC_ASRCIL                                      0x4

// *** TDMCTL0 ***
#घोषणा FB_TDMCTL0_TDMMD                                    2
#घोषणा FM_TDMCTL0_TDMMD                                    0x4
#घोषणा FV_TDMMD_200                                        0x0
#घोषणा FV_TDMMD_256                                        0x4

#घोषणा FB_TDMCTL0_SLSYNC                                   1
#घोषणा FM_TDMCTL0_SLSYNC                                   0x2
#घोषणा FV_SLSYNC_SHORT                                     0x0
#घोषणा FV_SLSYNC_LONG                                      0x2

#घोषणा FB_TDMCTL0_BDELAY                                   0
#घोषणा FM_TDMCTL0_BDELAY                                   0x1
#घोषणा FV_BDELAY_NO_DELAY                                  0x0
#घोषणा FV_BDELAY_1BCLK_DELAY                               0x1

// *** TDMCTL1 ***
#घोषणा FB_TDMCTL1_TDMSO                                    5
#घोषणा FM_TDMCTL1_TDMSO                                    0x60
#घोषणा FV_TDMSO_2                                          0x0
#घोषणा FV_TDMSO_4                                          0x20
#घोषणा FV_TDMSO_6                                          0x40

#घोषणा FB_TDMCTL1_TDMDSS                                   3
#घोषणा FM_TDMCTL1_TDMDSS                                   0x18
#घोषणा FV_TDMDSS_16                                        0x0
#घोषणा FV_TDMDSS_24                                        0x10
#घोषणा FV_TDMDSS_32                                        0x18

#घोषणा FB_TDMCTL1_TDMSI                                    0
#घोषणा FM_TDMCTL1_TDMSI                                    0x3
#घोषणा FV_TDMSI_2                                          0x0
#घोषणा FV_TDMSI_4                                          0x1
#घोषणा FV_TDMSI_6                                          0x2

// *** PWRM0 ***
#घोषणा FB_PWRM0_INPROC3PU                                  6
#घोषणा FM_PWRM0_INPROC3PU                                  0x40

#घोषणा FB_PWRM0_INPROC2PU                                  5
#घोषणा FM_PWRM0_INPROC2PU                                  0x20

#घोषणा FB_PWRM0_INPROC1PU                                  4
#घोषणा FM_PWRM0_INPROC1PU                                  0x10

#घोषणा FB_PWRM0_INPROC0PU                                  3
#घोषणा FM_PWRM0_INPROC0PU                                  0x8

#घोषणा FB_PWRM0_MICB2PU                                    2
#घोषणा FM_PWRM0_MICB2PU                                    0x4

#घोषणा FB_PWRM0_MICB1PU                                    1
#घोषणा FM_PWRM0_MICB1PU                                    0x2

#घोषणा FB_PWRM0_MCLKPEN                                    0
#घोषणा FM_PWRM0_MCLKPEN                                    0x1

// *** PWRM1 ***
#घोषणा FB_PWRM1_SUBPU                                      7
#घोषणा FM_PWRM1_SUBPU                                      0x80

#घोषणा FB_PWRM1_HPLPU                                      6
#घोषणा FM_PWRM1_HPLPU                                      0x40

#घोषणा FB_PWRM1_HPRPU                                      5
#घोषणा FM_PWRM1_HPRPU                                      0x20

#घोषणा FB_PWRM1_SPKLPU                                     4
#घोषणा FM_PWRM1_SPKLPU                                     0x10

#घोषणा FB_PWRM1_SPKRPU                                     3
#घोषणा FM_PWRM1_SPKRPU                                     0x8

#घोषणा FB_PWRM1_D2S2PU                                     2
#घोषणा FM_PWRM1_D2S2PU                                     0x4

#घोषणा FB_PWRM1_D2S1PU                                     1
#घोषणा FM_PWRM1_D2S1PU                                     0x2

#घोषणा FB_PWRM1_VREFPU                                     0
#घोषणा FM_PWRM1_VREFPU                                     0x1

// *** PWRM2 ***
#घोषणा FB_PWRM2_I2S3OPU                                    5
#घोषणा FM_PWRM2_I2S3OPU                                    0x20
#घोषणा FV_I2S3OPU_PWR_DOWN                                 0x0
#घोषणा FV_I2S3OPU_PWR_UP                                   0x20

#घोषणा FB_PWRM2_I2S2OPU                                    4
#घोषणा FM_PWRM2_I2S2OPU                                    0x10
#घोषणा FV_I2S2OPU_PWR_DOWN                                 0x0
#घोषणा FV_I2S2OPU_PWR_UP                                   0x10

#घोषणा FB_PWRM2_I2S1OPU                                    3
#घोषणा FM_PWRM2_I2S1OPU                                    0x8
#घोषणा FV_I2S1OPU_PWR_DOWN                                 0x0
#घोषणा FV_I2S1OPU_PWR_UP                                   0x8

#घोषणा FB_PWRM2_I2S3IPU                                    2
#घोषणा FM_PWRM2_I2S3IPU                                    0x4
#घोषणा FV_I2S3IPU_PWR_DOWN                                 0x0
#घोषणा FV_I2S3IPU_PWR_UP                                   0x4

#घोषणा FB_PWRM2_I2S2IPU                                    1
#घोषणा FM_PWRM2_I2S2IPU                                    0x2
#घोषणा FV_I2S2IPU_PWR_DOWN                                 0x0
#घोषणा FV_I2S2IPU_PWR_UP                                   0x2

#घोषणा FB_PWRM2_I2S1IPU                                    0
#घोषणा FM_PWRM2_I2S1IPU                                    0x1
#घोषणा FV_I2S1IPU_PWR_DOWN                                 0x0
#घोषणा FV_I2S1IPU_PWR_UP                                   0x1

#घोषणा PWRM2_I2SOPU_PWR_DOWN                               0x0
#घोषणा PWRM2_I2SOPU_PWR_UP                                 0x1
#घोषणा PWRM2_I2SIPU_PWR_DOWN                               0x0
#घोषणा PWRM2_I2SIPU_PWR_UP                                 0x1

// *** PWRM3 ***
#घोषणा FB_PWRM3_BGSBUP                                     6
#घोषणा FM_PWRM3_BGSBUP                                     0x40
#घोषणा FV_BGSBUP_ON                                        0x0
#घोषणा FV_BGSBUP_OFF                                       0x40

#घोषणा FB_PWRM3_VGBAPU                                     5
#घोषणा FM_PWRM3_VGBAPU                                     0x20
#घोषणा FV_VGBAPU_ON                                        0x0
#घोषणा FV_VGBAPU_OFF                                       0x20

#घोषणा FB_PWRM3_LLINEPU                                    4
#घोषणा FM_PWRM3_LLINEPU                                    0x10

#घोषणा FB_PWRM3_RLINEPU                                    3
#घोषणा FM_PWRM3_RLINEPU                                    0x8

// *** PWRM4 ***
#घोषणा FB_PWRM4_OPSUBPU                                    4
#घोषणा FM_PWRM4_OPSUBPU                                    0x10

#घोषणा FB_PWRM4_OPDACLPU                                   3
#घोषणा FM_PWRM4_OPDACLPU                                   0x8

#घोषणा FB_PWRM4_OPDACRPU                                   2
#घोषणा FM_PWRM4_OPDACRPU                                   0x4

#घोषणा FB_PWRM4_OPSPKLPU                                   1
#घोषणा FM_PWRM4_OPSPKLPU                                   0x2

#घोषणा FB_PWRM4_OPSPKRPU                                   0
#घोषणा FM_PWRM4_OPSPKRPU                                   0x1

// *** I2SIDCTL ***
#घोषणा FB_I2SIDCTL_I2SI3DCTL                               4
#घोषणा FM_I2SIDCTL_I2SI3DCTL                               0x30

#घोषणा FB_I2SIDCTL_I2SI2DCTL                               2
#घोषणा FM_I2SIDCTL_I2SI2DCTL                               0xC

#घोषणा FB_I2SIDCTL_I2SI1DCTL                               0
#घोषणा FM_I2SIDCTL_I2SI1DCTL                               0x3

// *** I2SODCTL ***
#घोषणा FB_I2SODCTL_I2SO3DCTL                               4
#घोषणा FM_I2SODCTL_I2SO3DCTL                               0x30

#घोषणा FB_I2SODCTL_I2SO2DCTL                               2
#घोषणा FM_I2SODCTL_I2SO2DCTL                               0xC

#घोषणा FB_I2SODCTL_I2SO1DCTL                               0
#घोषणा FM_I2SODCTL_I2SO1DCTL                               0x3

// *** AUDIOMUX1 ***
#घोषणा FB_AUDIOMUX1_ASRCIMUX                               6
#घोषणा FM_AUDIOMUX1_ASRCIMUX                               0xC0
#घोषणा FV_ASRCIMUX_NONE                                    0x0
#घोषणा FV_ASRCIMUX_I2S1                                    0x40
#घोषणा FV_ASRCIMUX_I2S2                                    0x80
#घोषणा FV_ASRCIMUX_I2S3                                    0xC0

#घोषणा FB_AUDIOMUX1_I2S2MUX                                3
#घोषणा FM_AUDIOMUX1_I2S2MUX                                0x38
#घोषणा FV_I2S2MUX_I2S1                                     0x0
#घोषणा FV_I2S2MUX_I2S2                                     0x8
#घोषणा FV_I2S2MUX_I2S3                                     0x10
#घोषणा FV_I2S2MUX_ADC_DMIC                                 0x18
#घोषणा FV_I2S2MUX_DMIC2                                    0x20
#घोषणा FV_I2S2MUX_CLASSD_DSP                               0x28
#घोषणा FV_I2S2MUX_DAC_DSP                                  0x30
#घोषणा FV_I2S2MUX_SUB_DSP                                  0x38

#घोषणा FB_AUDIOMUX1_I2S1MUX                                0
#घोषणा FM_AUDIOMUX1_I2S1MUX                                0x7
#घोषणा FV_I2S1MUX_I2S1                                     0x0
#घोषणा FV_I2S1MUX_I2S2                                     0x1
#घोषणा FV_I2S1MUX_I2S3                                     0x2
#घोषणा FV_I2S1MUX_ADC_DMIC                                 0x3
#घोषणा FV_I2S1MUX_DMIC2                                    0x4
#घोषणा FV_I2S1MUX_CLASSD_DSP                               0x5
#घोषणा FV_I2S1MUX_DAC_DSP                                  0x6
#घोषणा FV_I2S1MUX_SUB_DSP                                  0x7

#घोषणा AUDIOMUX1_I2SMUX_I2S1                               0x0
#घोषणा AUDIOMUX1_I2SMUX_I2S2                               0x1
#घोषणा AUDIOMUX1_I2SMUX_I2S3                               0x2
#घोषणा AUDIOMUX1_I2SMUX_ADC_DMIC                           0x3
#घोषणा AUDIOMUX1_I2SMUX_DMIC2                              0x4
#घोषणा AUDIOMUX1_I2SMUX_CLASSD_DSP                         0x5
#घोषणा AUDIOMUX1_I2SMUX_DAC_DSP                            0x6
#घोषणा AUDIOMUX1_I2SMUX_SUB_DSP                            0x7

// *** AUDIOMUX2 ***
#घोषणा FB_AUDIOMUX2_ASRCOMUX                               6
#घोषणा FM_AUDIOMUX2_ASRCOMUX                               0xC0
#घोषणा FV_ASRCOMUX_NONE                                    0x0
#घोषणा FV_ASRCOMUX_I2S1                                    0x40
#घोषणा FV_ASRCOMUX_I2S2                                    0x80
#घोषणा FV_ASRCOMUX_I2S3                                    0xC0

#घोषणा FB_AUDIOMUX2_DACMUX                                 3
#घोषणा FM_AUDIOMUX2_DACMUX                                 0x38
#घोषणा FV_DACMUX_I2S1                                      0x0
#घोषणा FV_DACMUX_I2S2                                      0x8
#घोषणा FV_DACMUX_I2S3                                      0x10
#घोषणा FV_DACMUX_ADC_DMIC                                  0x18
#घोषणा FV_DACMUX_DMIC2                                     0x20
#घोषणा FV_DACMUX_CLASSD_DSP                                0x28
#घोषणा FV_DACMUX_DAC_DSP                                   0x30
#घोषणा FV_DACMUX_SUB_DSP                                   0x38

#घोषणा FB_AUDIOMUX2_I2S3MUX                                0
#घोषणा FM_AUDIOMUX2_I2S3MUX                                0x7
#घोषणा FV_I2S3MUX_I2S1                                     0x0
#घोषणा FV_I2S3MUX_I2S2                                     0x1
#घोषणा FV_I2S3MUX_I2S3                                     0x2
#घोषणा FV_I2S3MUX_ADC_DMIC                                 0x3
#घोषणा FV_I2S3MUX_DMIC2                                    0x4
#घोषणा FV_I2S3MUX_CLASSD_DSP                               0x5
#घोषणा FV_I2S3MUX_DAC_DSP                                  0x6
#घोषणा FV_I2S3MUX_SUB_DSP                                  0x7

// *** AUDIOMUX3 ***
#घोषणा FB_AUDIOMUX3_SUBMUX                                 3
#घोषणा FM_AUDIOMUX3_SUBMUX                                 0xF8
#घोषणा FV_SUBMUX_I2S1_L                                    0x0
#घोषणा FV_SUBMUX_I2S1_R                                    0x8
#घोषणा FV_SUBMUX_I2S1_LR                                   0x10
#घोषणा FV_SUBMUX_I2S2_L                                    0x18
#घोषणा FV_SUBMUX_I2S2_R                                    0x20
#घोषणा FV_SUBMUX_I2S2_LR                                   0x28
#घोषणा FV_SUBMUX_I2S3_L                                    0x30
#घोषणा FV_SUBMUX_I2S3_R                                    0x38
#घोषणा FV_SUBMUX_I2S3_LR                                   0x40
#घोषणा FV_SUBMUX_ADC_DMIC_L                                0x48
#घोषणा FV_SUBMUX_ADC_DMIC_R                                0x50
#घोषणा FV_SUBMUX_ADC_DMIC_LR                               0x58
#घोषणा FV_SUBMUX_DMIC_L                                    0x60
#घोषणा FV_SUBMUX_DMIC_R                                    0x68
#घोषणा FV_SUBMUX_DMIC_LR                                   0x70
#घोषणा FV_SUBMUX_CLASSD_DSP_L                              0x78
#घोषणा FV_SUBMUX_CLASSD_DSP_R                              0x80
#घोषणा FV_SUBMUX_CLASSD_DSP_LR                             0x88

#घोषणा FB_AUDIOMUX3_CLSSDMUX                               0
#घोषणा FM_AUDIOMUX3_CLSSDMUX                               0x7
#घोषणा FV_CLSSDMUX_I2S1                                    0x0
#घोषणा FV_CLSSDMUX_I2S2                                    0x1
#घोषणा FV_CLSSDMUX_I2S3                                    0x2
#घोषणा FV_CLSSDMUX_ADC_DMIC                                0x3
#घोषणा FV_CLSSDMUX_DMIC2                                   0x4
#घोषणा FV_CLSSDMUX_CLASSD_DSP                              0x5
#घोषणा FV_CLSSDMUX_DAC_DSP                                 0x6
#घोषणा FV_CLSSDMUX_SUB_DSP                                 0x7

// *** HSDCTL1 ***
#घोषणा FB_HSDCTL1_HPJKTYPE                                 7
#घोषणा FM_HSDCTL1_HPJKTYPE                                 0x80

#घोषणा FB_HSDCTL1_CON_DET_PWD                              6
#घोषणा FM_HSDCTL1_CON_DET_PWD                              0x40

#घोषणा FB_HSDCTL1_DETCYC                                   4
#घोषणा FM_HSDCTL1_DETCYC                                   0x30

#घोषणा FB_HSDCTL1_HPDLYBYP                                 3
#घोषणा FM_HSDCTL1_HPDLYBYP                                 0x8

#घोषणा FB_HSDCTL1_HSDETPOL                                 2
#घोषणा FM_HSDCTL1_HSDETPOL                                 0x4

#घोषणा FB_HSDCTL1_HPID_EN                                  1
#घोषणा FM_HSDCTL1_HPID_EN                                  0x2

#घोषणा FB_HSDCTL1_GBLHS_EN                                 0
#घोषणा FM_HSDCTL1_GBLHS_EN                                 0x1

// *** HSDCTL2 ***
#घोषणा FB_HSDCTL2_FMICBIAS1                                6
#घोषणा FM_HSDCTL2_FMICBIAS1                                0xC0

#घोषणा FB_HSDCTL2_MB1MODE                                  5
#घोषणा FM_HSDCTL2_MB1MODE                                  0x20
#घोषणा FV_MB1MODE_AUTO                                     0x0
#घोषणा FV_MB1MODE_MANUAL                                   0x20

#घोषणा FB_HSDCTL2_FORCETRG                                 4
#घोषणा FM_HSDCTL2_FORCETRG                                 0x10

#घोषणा FB_HSDCTL2_SWMODE                                   3
#घोषणा FM_HSDCTL2_SWMODE                                   0x8

#घोषणा FB_HSDCTL2_GHSHIZ                                   2
#घोषणा FM_HSDCTL2_GHSHIZ                                   0x4

#घोषणा FB_HSDCTL2_FPLUGTYPE                                0
#घोषणा FM_HSDCTL2_FPLUGTYPE                                0x3

// *** HSDSTAT ***
#घोषणा FB_HSDSTAT_MBIAS1DRV                                5
#घोषणा FM_HSDSTAT_MBIAS1DRV                                0x60

#घोषणा FB_HSDSTAT_HSDETSTAT                                3
#घोषणा FM_HSDSTAT_HSDETSTAT                                0x8

#घोषणा FB_HSDSTAT_PLUGTYPE                                 1
#घोषणा FM_HSDSTAT_PLUGTYPE                                 0x6

#घोषणा FB_HSDSTAT_HSDETDONE                                0
#घोषणा FM_HSDSTAT_HSDETDONE                                0x1

// *** HSDDELAY ***
#घोषणा FB_HSDDELAY_T_STABLE                                0
#घोषणा FM_HSDDELAY_T_STABLE                                0x7

// *** BUTCTL ***
#घोषणा FB_BUTCTL_BPUSHSTAT                                 7
#घोषणा FM_BUTCTL_BPUSHSTAT                                 0x80

#घोषणा FB_BUTCTL_BPUSHDET                                  6
#घोषणा FM_BUTCTL_BPUSHDET                                  0x40

#घोषणा FB_BUTCTL_BPUSHEN                                   5
#घोषणा FM_BUTCTL_BPUSHEN                                   0x20

#घोषणा FB_BUTCTL_BSTABLE_L                                 3
#घोषणा FM_BUTCTL_BSTABLE_L                                 0x18

#घोषणा FB_BUTCTL_BSTABLE_S                                 0
#घोषणा FM_BUTCTL_BSTABLE_S                                 0x7

// *** CH0AIC ***
#घोषणा FB_CH0AIC_INSELL                                    6
#घोषणा FM_CH0AIC_INSELL                                    0xC0

#घोषणा FB_CH0AIC_MICBST0                                   4
#घोषणा FM_CH0AIC_MICBST0                                   0x30

#घोषणा FB_CH0AIC_LADCIN                                    2
#घोषणा FM_CH0AIC_LADCIN                                    0xC

#घोषणा FB_CH0AIC_IN_BYPS_L_SEL                             1
#घोषणा FM_CH0AIC_IN_BYPS_L_SEL                             0x2

#घोषणा FB_CH0AIC_IPCH0S                                    0
#घोषणा FM_CH0AIC_IPCH0S                                    0x1

// *** CH1AIC ***
#घोषणा FB_CH1AIC_INSELR                                    6
#घोषणा FM_CH1AIC_INSELR                                    0xC0

#घोषणा FB_CH1AIC_MICBST1                                   4
#घोषणा FM_CH1AIC_MICBST1                                   0x30

#घोषणा FB_CH1AIC_RADCIN                                    2
#घोषणा FM_CH1AIC_RADCIN                                    0xC

#घोषणा FB_CH1AIC_IN_BYPS_R_SEL                             1
#घोषणा FM_CH1AIC_IN_BYPS_R_SEL                             0x2

#घोषणा FB_CH1AIC_IPCH1S                                    0
#घोषणा FM_CH1AIC_IPCH1S                                    0x1

// *** ICTL0 ***
#घोषणा FB_ICTL0_IN1POL                                     7
#घोषणा FM_ICTL0_IN1POL                                     0x80

#घोषणा FB_ICTL0_IN0POL                                     6
#घोषणा FM_ICTL0_IN0POL                                     0x40

#घोषणा FB_ICTL0_INPCH10SEL                                 4
#घोषणा FM_ICTL0_INPCH10SEL                                 0x30

#घोषणा FB_ICTL0_IN1MUTE                                    3
#घोषणा FM_ICTL0_IN1MUTE                                    0x8

#घोषणा FB_ICTL0_IN0MUTE                                    2
#घोषणा FM_ICTL0_IN0MUTE                                    0x4

#घोषणा FB_ICTL0_IN1HP                                      1
#घोषणा FM_ICTL0_IN1HP                                      0x2

#घोषणा FB_ICTL0_IN0HP                                      0
#घोषणा FM_ICTL0_IN0HP                                      0x1

// *** ICTL1 ***
#घोषणा FB_ICTL1_IN3POL                                     7
#घोषणा FM_ICTL1_IN3POL                                     0x80

#घोषणा FB_ICTL1_IN2POL                                     6
#घोषणा FM_ICTL1_IN2POL                                     0x40

#घोषणा FB_ICTL1_INPCH32SEL                                 4
#घोषणा FM_ICTL1_INPCH32SEL                                 0x30

#घोषणा FB_ICTL1_IN3MUTE                                    3
#घोषणा FM_ICTL1_IN3MUTE                                    0x8

#घोषणा FB_ICTL1_IN2MUTE                                    2
#घोषणा FM_ICTL1_IN2MUTE                                    0x4

#घोषणा FB_ICTL1_IN3HP                                      1
#घोषणा FM_ICTL1_IN3HP                                      0x2

#घोषणा FB_ICTL1_IN2HP                                      0
#घोषणा FM_ICTL1_IN2HP                                      0x1

// *** MICBIAS ***
#घोषणा FB_MICBIAS_MICBOV2                                  4
#घोषणा FM_MICBIAS_MICBOV2                                  0x30

#घोषणा FB_MICBIAS_MICBOV1                                  6
#घोषणा FM_MICBIAS_MICBOV1                                  0xC0

#घोषणा FB_MICBIAS_SPARE1                                   2
#घोषणा FM_MICBIAS_SPARE1                                   0xC

#घोषणा FB_MICBIAS_SPARE2                                   0
#घोषणा FM_MICBIAS_SPARE2                                   0x3

// *** PGAZ ***
#घोषणा FB_PGAZ_INHPOR                                      1
#घोषणा FM_PGAZ_INHPOR                                      0x2

#घोषणा FB_PGAZ_TOEN                                        0
#घोषणा FM_PGAZ_TOEN                                        0x1

// *** ASRCILVOL ***
#घोषणा FB_ASRCILVOL_ASRCILVOL                              0
#घोषणा FM_ASRCILVOL_ASRCILVOL                              0xFF

// *** ASRCIRVOL ***
#घोषणा FB_ASRCIRVOL_ASRCIRVOL                              0
#घोषणा FM_ASRCIRVOL_ASRCIRVOL                              0xFF

// *** ASRCOLVOL ***
#घोषणा FB_ASRCOLVOL_ASRCOLVOL                              0
#घोषणा FM_ASRCOLVOL_ASRCOLVOL                              0xFF

// *** ASRCORVOL ***
#घोषणा FB_ASRCORVOL_ASRCOLVOL                              0
#घोषणा FM_ASRCORVOL_ASRCOLVOL                              0xFF

// *** IVOLCTLU ***
#घोषणा FB_IVOLCTLU_IFADE                                   3
#घोषणा FM_IVOLCTLU_IFADE                                   0x8

#घोषणा FB_IVOLCTLU_INPVOLU                                 2
#घोषणा FM_IVOLCTLU_INPVOLU                                 0x4

#घोषणा FB_IVOLCTLU_PGAVOLU                                 1
#घोषणा FM_IVOLCTLU_PGAVOLU                                 0x2

#घोषणा FB_IVOLCTLU_ASRCVOLU                                0
#घोषणा FM_IVOLCTLU_ASRCVOLU                                0x1

// *** ALCCTL0 ***
#घोषणा FB_ALCCTL0_ALCMODE                                  7
#घोषणा FM_ALCCTL0_ALCMODE                                  0x80

#घोषणा FB_ALCCTL0_ALCREF                                   4
#घोषणा FM_ALCCTL0_ALCREF                                   0x70

#घोषणा FB_ALCCTL0_ALCEN3                                   3
#घोषणा FM_ALCCTL0_ALCEN3                                   0x8

#घोषणा FB_ALCCTL0_ALCEN2                                   2
#घोषणा FM_ALCCTL0_ALCEN2                                   0x4

#घोषणा FB_ALCCTL0_ALCEN1                                   1
#घोषणा FM_ALCCTL0_ALCEN1                                   0x2

#घोषणा FB_ALCCTL0_ALCEN0                                   0
#घोषणा FM_ALCCTL0_ALCEN0                                   0x1

// *** ALCCTL1 ***
#घोषणा FB_ALCCTL1_MAXGAIN                                  4
#घोषणा FM_ALCCTL1_MAXGAIN                                  0x70

#घोषणा FB_ALCCTL1_ALCL                                     0
#घोषणा FM_ALCCTL1_ALCL                                     0xF

// *** ALCCTL2 ***
#घोषणा FB_ALCCTL2_ALCZC                                    7
#घोषणा FM_ALCCTL2_ALCZC                                    0x80

#घोषणा FB_ALCCTL2_MINGAIN                                  4
#घोषणा FM_ALCCTL2_MINGAIN                                  0x70

#घोषणा FB_ALCCTL2_HLD                                      0
#घोषणा FM_ALCCTL2_HLD                                      0xF

// *** ALCCTL3 ***
#घोषणा FB_ALCCTL3_DCY                                      4
#घोषणा FM_ALCCTL3_DCY                                      0xF0

#घोषणा FB_ALCCTL3_ATK                                      0
#घोषणा FM_ALCCTL3_ATK                                      0xF

// *** NGATE ***
#घोषणा FB_NGATE_NGTH                                       3
#घोषणा FM_NGATE_NGTH                                       0xF8

#घोषणा FB_NGATE_NGG                                        1
#घोषणा FM_NGATE_NGG                                        0x6

#घोषणा FB_NGATE_NGAT                                       0
#घोषणा FM_NGATE_NGAT                                       0x1

// *** DMICCTL ***
#घोषणा FB_DMICCTL_DMIC2EN                                  7
#घोषणा FM_DMICCTL_DMIC2EN                                  0x80

#घोषणा FB_DMICCTL_DMIC1EN                                  6
#घोषणा FM_DMICCTL_DMIC1EN                                  0x40

#घोषणा FB_DMICCTL_DMONO                                    4
#घोषणा FM_DMICCTL_DMONO                                    0x10

#घोषणा FB_DMICCTL_DMDCLK                                   2
#घोषणा FM_DMICCTL_DMDCLK                                   0xC

#घोषणा FB_DMICCTL_DMRATE                                   0
#घोषणा FM_DMICCTL_DMRATE                                   0x3

// *** DACCTL ***
#घोषणा FB_DACCTL_DACPOLR                                   7
#घोषणा FM_DACCTL_DACPOLR                                   0x80
#घोषणा FV_DACPOLR_NORMAL                                   0x0
#घोषणा FV_DACPOLR_INVERTED                                 0x80

#घोषणा FB_DACCTL_DACPOLL                                   6
#घोषणा FM_DACCTL_DACPOLL                                   0x40
#घोषणा FV_DACPOLL_NORMAL                                   0x0
#घोषणा FV_DACPOLL_INVERTED                                 0x40

#घोषणा FB_DACCTL_DACDITH                                   4
#घोषणा FM_DACCTL_DACDITH                                   0x30
#घोषणा FV_DACDITH_DYNAMIC_HALF                             0x0
#घोषणा FV_DACDITH_DYNAMIC_FULL                             0x10
#घोषणा FV_DACDITH_DISABLED                                 0x20
#घोषणा FV_DACDITH_STATIC                                   0x30

#घोषणा FB_DACCTL_DACMUTE                                   3
#घोषणा FM_DACCTL_DACMUTE                                   0x8
#घोषणा FV_DACMUTE_ENABLE                                   0x8
#घोषणा FV_DACMUTE_DISABLE                                  0x0

#घोषणा FB_DACCTL_DACDEM                                    2
#घोषणा FM_DACCTL_DACDEM                                    0x4
#घोषणा FV_DACDEM_ENABLE                                    0x4
#घोषणा FV_DACDEM_DISABLE                                   0x0

#घोषणा FB_DACCTL_ABYPASS                                   0
#घोषणा FM_DACCTL_ABYPASS                                   0x1

// *** SPKCTL ***
#घोषणा FB_SPKCTL_SPKPOLR                                   7
#घोषणा FM_SPKCTL_SPKPOLR                                   0x80
#घोषणा FV_SPKPOLR_NORMAL                                   0x0
#घोषणा FV_SPKPOLR_INVERTED                                 0x80

#घोषणा FB_SPKCTL_SPKPOLL                                   6
#घोषणा FM_SPKCTL_SPKPOLL                                   0x40
#घोषणा FV_SPKPOLL_NORMAL                                   0x0
#घोषणा FV_SPKPOLL_INVERTED                                 0x40

#घोषणा FB_SPKCTL_SPKMUTE                                   3
#घोषणा FM_SPKCTL_SPKMUTE                                   0x8
#घोषणा FV_SPKMUTE_ENABLE                                   0x8
#घोषणा FV_SPKMUTE_DISABLE                                  0x0

#घोषणा FB_SPKCTL_SPKDEM                                    2
#घोषणा FM_SPKCTL_SPKDEM                                    0x4
#घोषणा FV_SPKDEM_ENABLE                                    0x4
#घोषणा FV_SPKDEM_DISABLE                                   0x0

// *** SUBCTL ***
#घोषणा FB_SUBCTL_SUBPOL                                    7
#घोषणा FM_SUBCTL_SUBPOL                                    0x80

#घोषणा FB_SUBCTL_SUBMUTE                                   3
#घोषणा FM_SUBCTL_SUBMUTE                                   0x8

#घोषणा FB_SUBCTL_SUBDEM                                    2
#घोषणा FM_SUBCTL_SUBDEM                                    0x4

#घोषणा FB_SUBCTL_SUBMUX                                    1
#घोषणा FM_SUBCTL_SUBMUX                                    0x2

#घोषणा FB_SUBCTL_SUBILMDIS                                 0
#घोषणा FM_SUBCTL_SUBILMDIS                                 0x1

// *** DCCTL ***
#घोषणा FB_DCCTL_SUBDCBYP                                   7
#घोषणा FM_DCCTL_SUBDCBYP                                   0x80

#घोषणा FB_DCCTL_DACDCBYP                                   6
#घोषणा FM_DCCTL_DACDCBYP                                   0x40

#घोषणा FB_DCCTL_SPKDCBYP                                   5
#घोषणा FM_DCCTL_SPKDCBYP                                   0x20

#घोषणा FB_DCCTL_DCCOEFSEL                                  0
#घोषणा FM_DCCTL_DCCOEFSEL                                  0x7

// *** OVOLCTLU ***
#घोषणा FB_OVOLCTLU_OFADE                                   4
#घोषणा FM_OVOLCTLU_OFADE                                   0x10

#घोषणा FB_OVOLCTLU_SUBVOLU                                 3
#घोषणा FM_OVOLCTLU_SUBVOLU                                 0x8

#घोषणा FB_OVOLCTLU_MVOLU                                   2
#घोषणा FM_OVOLCTLU_MVOLU                                   0x4

#घोषणा FB_OVOLCTLU_SPKVOLU                                 1
#घोषणा FM_OVOLCTLU_SPKVOLU                                 0x2

#घोषणा FB_OVOLCTLU_HPVOLU                                  0
#घोषणा FM_OVOLCTLU_HPVOLU                                  0x1

// *** MUTEC ***
#घोषणा FB_MUTEC_ZDSTAT                                     7
#घोषणा FM_MUTEC_ZDSTAT                                     0x80

#घोषणा FB_MUTEC_ZDLEN                                      4
#घोषणा FM_MUTEC_ZDLEN                                      0x30

#घोषणा FB_MUTEC_APWD                                       3
#घोषणा FM_MUTEC_APWD                                       0x8

#घोषणा FB_MUTEC_AMUTE                                      2
#घोषणा FM_MUTEC_AMUTE                                      0x4

// *** MVOLL ***
#घोषणा FB_MVOLL_MVOL_L                                     0
#घोषणा FM_MVOLL_MVOL_L                                     0xFF

// *** MVOLR ***
#घोषणा FB_MVOLR_MVOL_R                                     0
#घोषणा FM_MVOLR_MVOL_R                                     0xFF

// *** HPVOLL ***
#घोषणा FB_HPVOLL_HPVOL_L                                   0
#घोषणा FM_HPVOLL_HPVOL_L                                   0x7F

// *** HPVOLR ***
#घोषणा FB_HPVOLR_HPVOL_R                                   0
#घोषणा FM_HPVOLR_HPVOL_R                                   0x7F

// *** SPKVOLL ***
#घोषणा FB_SPKVOLL_SPKVOL_L                                 0
#घोषणा FM_SPKVOLL_SPKVOL_L                                 0x7F

// *** SPKVOLR ***
#घोषणा FB_SPKVOLR_SPKVOL_R                                 0
#घोषणा FM_SPKVOLR_SPKVOL_R                                 0x7F

// *** SUBVOL ***
#घोषणा FB_SUBVOL_SUBVOL                                    0
#घोषणा FM_SUBVOL_SUBVOL                                    0x7F

// *** COP0 ***
#घोषणा FB_COP0_COPATTEN                                    7
#घोषणा FM_COP0_COPATTEN                                    0x80

#घोषणा FB_COP0_COPGAIN                                     6
#घोषणा FM_COP0_COPGAIN                                     0x40

#घोषणा FB_COP0_HDELTAEN                                    5
#घोषणा FM_COP0_HDELTAEN                                    0x20

#घोषणा FB_COP0_COPTARGET                                   0
#घोषणा FM_COP0_COPTARGET                                   0x1F

// *** COP1 ***
#घोषणा FB_COP1_HDCOMPMODE                                  6
#घोषणा FM_COP1_HDCOMPMODE                                  0x40

#घोषणा FB_COP1_AVGLENGTH                                   2
#घोषणा FM_COP1_AVGLENGTH                                   0x3C

#घोषणा FB_COP1_MONRATE                                     0
#घोषणा FM_COP1_MONRATE                                     0x3

// *** COPSTAT ***
#घोषणा FB_COPSTAT_HDELTADET                                7
#घोषणा FM_COPSTAT_HDELTADET                                0x80

#घोषणा FB_COPSTAT_UV                                       6
#घोषणा FM_COPSTAT_UV                                       0x40

#घोषणा FB_COPSTAT_COPADJ                                   0
#घोषणा FM_COPSTAT_COPADJ                                   0x3F

// *** PWM0 ***
#घोषणा FB_PWM0_SCTO                                        6
#घोषणा FM_PWM0_SCTO                                        0xC0

#घोषणा FB_PWM0_UVLO                                        5
#घोषणा FM_PWM0_UVLO                                        0x20

#घोषणा FB_PWM0_BFDIS                                       3
#घोषणा FM_PWM0_BFDIS                                       0x8

#घोषणा FB_PWM0_PWMMODE                                     2
#घोषणा FM_PWM0_PWMMODE                                     0x4

#घोषणा FB_PWM0_NOOFFSET                                    0
#घोषणा FM_PWM0_NOOFFSET                                    0x1

// *** PWM1 ***
#घोषणा FB_PWM1_DITHPOS                                     4
#घोषणा FM_PWM1_DITHPOS                                     0x70

#घोषणा FB_PWM1_DYNDITH                                     1
#घोषणा FM_PWM1_DYNDITH                                     0x2

#घोषणा FB_PWM1_DITHDIS                                     0
#घोषणा FM_PWM1_DITHDIS                                     0x1

// *** PWM2 ***
// *** PWM3 ***
#घोषणा FB_PWM3_PWMMUX                                      6
#घोषणा FM_PWM3_PWMMUX                                      0xC0

#घोषणा FB_PWM3_CVALUE                                      0
#घोषणा FM_PWM3_CVALUE                                      0x7

// *** HPSW ***
#घोषणा FB_HPSW_HPDETSTATE                                  4
#घोषणा FM_HPSW_HPDETSTATE                                  0x10

#घोषणा FB_HPSW_HPSWEN                                      2
#घोषणा FM_HPSW_HPSWEN                                      0xC

#घोषणा FB_HPSW_HPSWPOL                                     1
#घोषणा FM_HPSW_HPSWPOL                                     0x2

#घोषणा FB_HPSW_TSDEN                                       0
#घोषणा FM_HPSW_TSDEN                                       0x1

// *** THERMTS ***
#घोषणा FB_THERMTS_TRIPHS                                   7
#घोषणा FM_THERMTS_TRIPHS                                   0x80

#घोषणा FB_THERMTS_TRIPLS                                   6
#घोषणा FM_THERMTS_TRIPLS                                   0x40

#घोषणा FB_THERMTS_TRIPSPLIT                                4
#घोषणा FM_THERMTS_TRIPSPLIT                                0x30

#घोषणा FB_THERMTS_TRIPSHIFT                                2
#घोषणा FM_THERMTS_TRIPSHIFT                                0xC

#घोषणा FB_THERMTS_TSPOLL                                   0
#घोषणा FM_THERMTS_TSPOLL                                   0x3

// *** THERMSPK1 ***
#घोषणा FB_THERMSPK1_FORCEPWD                               7
#घोषणा FM_THERMSPK1_FORCEPWD                               0x80

#घोषणा FB_THERMSPK1_INSTCUTMODE                            6
#घोषणा FM_THERMSPK1_INSTCUTMODE                            0x40

#घोषणा FB_THERMSPK1_INCRATIO                               4
#घोषणा FM_THERMSPK1_INCRATIO                               0x30

#घोषणा FB_THERMSPK1_INCSTEP                                2
#घोषणा FM_THERMSPK1_INCSTEP                                0xC

#घोषणा FB_THERMSPK1_DECSTEP                                0
#घोषणा FM_THERMSPK1_DECSTEP                                0x3

// *** THERMSTAT ***
#घोषणा FB_THERMSTAT_FPWDS                                  7
#घोषणा FM_THERMSTAT_FPWDS                                  0x80

#घोषणा FB_THERMSTAT_VOLSTAT                                0
#घोषणा FM_THERMSTAT_VOLSTAT                                0x7F

// *** SCSTAT ***
#घोषणा FB_SCSTAT_ESDF                                      3
#घोषणा FM_SCSTAT_ESDF                                      0x18

#घोषणा FB_SCSTAT_CPF                                       2
#घोषणा FM_SCSTAT_CPF                                       0x4

#घोषणा FB_SCSTAT_CLSDF                                     0
#घोषणा FM_SCSTAT_CLSDF                                     0x3

// *** SDMON ***
#घोषणा FB_SDMON_SDFORCE                                    7
#घोषणा FM_SDMON_SDFORCE                                    0x80

#घोषणा FB_SDMON_SDVALUE                                    0
#घोषणा FM_SDMON_SDVALUE                                    0x1F

// *** SPKEQFILT ***
#घोषणा FB_SPKEQFILT_EQ2EN                                  7
#घोषणा FM_SPKEQFILT_EQ2EN                                  0x80
#घोषणा FV_EQ2EN_ENABLE                                     0x80
#घोषणा FV_EQ2EN_DISABLE                                    0x0

#घोषणा FB_SPKEQFILT_EQ2BE                                  4
#घोषणा FM_SPKEQFILT_EQ2BE                                  0x70

#घोषणा FB_SPKEQFILT_EQ1EN                                  3
#घोषणा FM_SPKEQFILT_EQ1EN                                  0x8
#घोषणा FV_EQ1EN_ENABLE                                     0x8
#घोषणा FV_EQ1EN_DISABLE                                    0x0

#घोषणा FB_SPKEQFILT_EQ1BE                                  0
#घोषणा FM_SPKEQFILT_EQ1BE                                  0x7

#घोषणा SPKEQFILT_EQEN_ENABLE                               0x1
#घोषणा SPKEQFILT_EQEN_DISABLE                              0x0

// *** SPKCRWDL ***
#घोषणा FB_SPKCRWDL_WDATA_L                                 0
#घोषणा FM_SPKCRWDL_WDATA_L                                 0xFF

// *** SPKCRWDM ***
#घोषणा FB_SPKCRWDM_WDATA_M                                 0
#घोषणा FM_SPKCRWDM_WDATA_M                                 0xFF

// *** SPKCRWDH ***
#घोषणा FB_SPKCRWDH_WDATA_H                                 0
#घोषणा FM_SPKCRWDH_WDATA_H                                 0xFF

// *** SPKCRRDL ***
#घोषणा FB_SPKCRRDL_RDATA_L                                 0
#घोषणा FM_SPKCRRDL_RDATA_L                                 0xFF

// *** SPKCRRDM ***
#घोषणा FB_SPKCRRDM_RDATA_M                                 0
#घोषणा FM_SPKCRRDM_RDATA_M                                 0xFF

// *** SPKCRRDH ***
#घोषणा FB_SPKCRRDH_RDATA_H                                 0
#घोषणा FM_SPKCRRDH_RDATA_H                                 0xFF

// *** SPKCRADD ***
#घोषणा FB_SPKCRADD_ADDRESS                                 0
#घोषणा FM_SPKCRADD_ADDRESS                                 0xFF

// *** SPKCRS ***
#घोषणा FB_SPKCRS_ACCSTAT                                   7
#घोषणा FM_SPKCRS_ACCSTAT                                   0x80

// *** SPKMBCEN ***
#घोषणा FB_SPKMBCEN_MBCEN3                                  2
#घोषणा FM_SPKMBCEN_MBCEN3                                  0x4
#घोषणा FV_MBCEN3_ENABLE                                    0x4
#घोषणा FV_MBCEN3_DISABLE                                   0x0

#घोषणा FB_SPKMBCEN_MBCEN2                                  1
#घोषणा FM_SPKMBCEN_MBCEN2                                  0x2
#घोषणा FV_MBCEN2_ENABLE                                    0x2
#घोषणा FV_MBCEN2_DISABLE                                   0x0

#घोषणा FB_SPKMBCEN_MBCEN1                                  0
#घोषणा FM_SPKMBCEN_MBCEN1                                  0x1
#घोषणा FV_MBCEN1_ENABLE                                    0x1
#घोषणा FV_MBCEN1_DISABLE                                   0x0

#घोषणा SPKMBCEN_MBCEN_ENABLE                               0x1
#घोषणा SPKMBCEN_MBCEN_DISABLE                              0x0

// *** SPKMBCCTL ***
#घोषणा FB_SPKMBCCTL_LVLMODE3                               5
#घोषणा FM_SPKMBCCTL_LVLMODE3                               0x20

#घोषणा FB_SPKMBCCTL_WINSEL3                                4
#घोषणा FM_SPKMBCCTL_WINSEL3                                0x10

#घोषणा FB_SPKMBCCTL_LVLMODE2                               3
#घोषणा FM_SPKMBCCTL_LVLMODE2                               0x8

#घोषणा FB_SPKMBCCTL_WINSEL2                                2
#घोषणा FM_SPKMBCCTL_WINSEL2                                0x4

#घोषणा FB_SPKMBCCTL_LVLMODE1                               1
#घोषणा FM_SPKMBCCTL_LVLMODE1                               0x2

#घोषणा FB_SPKMBCCTL_WINSEL1                                0
#घोषणा FM_SPKMBCCTL_WINSEL1                                0x1

// *** SPKCLECTL ***
#घोषणा FB_SPKCLECTL_LVLMODE                                4
#घोषणा FM_SPKCLECTL_LVLMODE                                0x10

#घोषणा FB_SPKCLECTL_WINSEL                                 3
#घोषणा FM_SPKCLECTL_WINSEL                                 0x8

#घोषणा FB_SPKCLECTL_EXPEN                                  2
#घोषणा FM_SPKCLECTL_EXPEN                                  0x4
#घोषणा FV_EXPEN_ENABLE                                     0x4
#घोषणा FV_EXPEN_DISABLE                                    0x0

#घोषणा FB_SPKCLECTL_LIMEN                                  1
#घोषणा FM_SPKCLECTL_LIMEN                                  0x2
#घोषणा FV_LIMEN_ENABLE                                     0x2
#घोषणा FV_LIMEN_DISABLE                                    0x0

#घोषणा FB_SPKCLECTL_COMPEN                                 0
#घोषणा FM_SPKCLECTL_COMPEN                                 0x1
#घोषणा FV_COMPEN_ENABLE                                    0x1
#घोषणा FV_COMPEN_DISABLE                                   0x0

// *** SPKCLEMUG ***
#घोषणा FB_SPKCLEMUG_MUGAIN                                 0
#घोषणा FM_SPKCLEMUG_MUGAIN                                 0x1F

// *** SPKCOMPTHR ***
#घोषणा FB_SPKCOMPTHR_THRESH                                0
#घोषणा FM_SPKCOMPTHR_THRESH                                0xFF

// *** SPKCOMPRAT ***
#घोषणा FB_SPKCOMPRAT_RATIO                                 0
#घोषणा FM_SPKCOMPRAT_RATIO                                 0x1F

// *** SPKCOMPATKL ***
#घोषणा FB_SPKCOMPATKL_TCATKL                               0
#घोषणा FM_SPKCOMPATKL_TCATKL                               0xFF

// *** SPKCOMPATKH ***
#घोषणा FB_SPKCOMPATKH_TCATKH                               0
#घोषणा FM_SPKCOMPATKH_TCATKH                               0xFF

// *** SPKCOMPRELL ***
#घोषणा FB_SPKCOMPRELL_TCRELL                               0
#घोषणा FM_SPKCOMPRELL_TCRELL                               0xFF

// *** SPKCOMPRELH ***
#घोषणा FB_SPKCOMPRELH_TCRELH                               0
#घोषणा FM_SPKCOMPRELH_TCRELH                               0xFF

// *** SPKLIMTHR ***
#घोषणा FB_SPKLIMTHR_THRESH                                 0
#घोषणा FM_SPKLIMTHR_THRESH                                 0xFF

// *** SPKLIMTGT ***
#घोषणा FB_SPKLIMTGT_TARGET                                 0
#घोषणा FM_SPKLIMTGT_TARGET                                 0xFF

// *** SPKLIMATKL ***
#घोषणा FB_SPKLIMATKL_TCATKL                                0
#घोषणा FM_SPKLIMATKL_TCATKL                                0xFF

// *** SPKLIMATKH ***
#घोषणा FB_SPKLIMATKH_TCATKH                                0
#घोषणा FM_SPKLIMATKH_TCATKH                                0xFF

// *** SPKLIMRELL ***
#घोषणा FB_SPKLIMRELL_TCRELL                                0
#घोषणा FM_SPKLIMRELL_TCRELL                                0xFF

// *** SPKLIMRELH ***
#घोषणा FB_SPKLIMRELH_TCRELH                                0
#घोषणा FM_SPKLIMRELH_TCRELH                                0xFF

// *** SPKEXPTHR ***
#घोषणा FB_SPKEXPTHR_THRESH                                 0
#घोषणा FM_SPKEXPTHR_THRESH                                 0xFF

// *** SPKEXPRAT ***
#घोषणा FB_SPKEXPRAT_RATIO                                  0
#घोषणा FM_SPKEXPRAT_RATIO                                  0x7

// *** SPKEXPATKL ***
#घोषणा FB_SPKEXPATKL_TCATKL                                0
#घोषणा FM_SPKEXPATKL_TCATKL                                0xFF

// *** SPKEXPATKH ***
#घोषणा FB_SPKEXPATKH_TCATKH                                0
#घोषणा FM_SPKEXPATKH_TCATKH                                0xFF

// *** SPKEXPRELL ***
#घोषणा FB_SPKEXPRELL_TCRELL                                0
#घोषणा FM_SPKEXPRELL_TCRELL                                0xFF

// *** SPKEXPRELH ***
#घोषणा FB_SPKEXPRELH_TCRELH                                0
#घोषणा FM_SPKEXPRELH_TCRELH                                0xFF

// *** SPKFXCTL ***
#घोषणा FB_SPKFXCTL_3DEN                                    4
#घोषणा FM_SPKFXCTL_3DEN                                    0x10

#घोषणा FB_SPKFXCTL_TEEN                                    3
#घोषणा FM_SPKFXCTL_TEEN                                    0x8

#घोषणा FB_SPKFXCTL_TNLFBYP                                 2
#घोषणा FM_SPKFXCTL_TNLFBYP                                 0x4

#घोषणा FB_SPKFXCTL_BEEN                                    1
#घोषणा FM_SPKFXCTL_BEEN                                    0x2

#घोषणा FB_SPKFXCTL_BNLFBYP                                 0
#घोषणा FM_SPKFXCTL_BNLFBYP                                 0x1

// *** DACEQFILT ***
#घोषणा FB_DACEQFILT_EQ2EN                                  7
#घोषणा FM_DACEQFILT_EQ2EN                                  0x80
#घोषणा FV_EQ2EN_ENABLE                                     0x80
#घोषणा FV_EQ2EN_DISABLE                                    0x0

#घोषणा FB_DACEQFILT_EQ2BE                                  4
#घोषणा FM_DACEQFILT_EQ2BE                                  0x70

#घोषणा FB_DACEQFILT_EQ1EN                                  3
#घोषणा FM_DACEQFILT_EQ1EN                                  0x8
#घोषणा FV_EQ1EN_ENABLE                                     0x8
#घोषणा FV_EQ1EN_DISABLE                                    0x0

#घोषणा FB_DACEQFILT_EQ1BE                                  0
#घोषणा FM_DACEQFILT_EQ1BE                                  0x7

#घोषणा DACEQFILT_EQEN_ENABLE                               0x1
#घोषणा DACEQFILT_EQEN_DISABLE                              0x0

// *** DACCRWDL ***
#घोषणा FB_DACCRWDL_WDATA_L                                 0
#घोषणा FM_DACCRWDL_WDATA_L                                 0xFF

// *** DACCRWDM ***
#घोषणा FB_DACCRWDM_WDATA_M                                 0
#घोषणा FM_DACCRWDM_WDATA_M                                 0xFF

// *** DACCRWDH ***
#घोषणा FB_DACCRWDH_WDATA_H                                 0
#घोषणा FM_DACCRWDH_WDATA_H                                 0xFF

// *** DACCRRDL ***
#घोषणा FB_DACCRRDL_RDATA_L                                 0
#घोषणा FM_DACCRRDL_RDATA_L                                 0xFF

// *** DACCRRDM ***
#घोषणा FB_DACCRRDM_RDATA_M                                 0
#घोषणा FM_DACCRRDM_RDATA_M                                 0xFF

// *** DACCRRDH ***
#घोषणा FB_DACCRRDH_RDATA_H                                 0
#घोषणा FM_DACCRRDH_RDATA_H                                 0xFF

// *** DACCRADD ***
#घोषणा FB_DACCRADD_ADDRESS                                 0
#घोषणा FM_DACCRADD_ADDRESS                                 0xFF

// *** DACCRS ***
#घोषणा FB_DACCRS_ACCSTAT                                   7
#घोषणा FM_DACCRS_ACCSTAT                                   0x80

// *** DACMBCEN ***
#घोषणा FB_DACMBCEN_MBCEN3                                  2
#घोषणा FM_DACMBCEN_MBCEN3                                  0x4
#घोषणा FV_MBCEN3_ENABLE                                    0x4
#घोषणा FV_MBCEN3_DISABLE                                   0x0

#घोषणा FB_DACMBCEN_MBCEN2                                  1
#घोषणा FM_DACMBCEN_MBCEN2                                  0x2
#घोषणा FV_MBCEN2_ENABLE                                    0x2
#घोषणा FV_MBCEN2_DISABLE                                   0x0

#घोषणा FB_DACMBCEN_MBCEN1                                  0
#घोषणा FM_DACMBCEN_MBCEN1                                  0x1
#घोषणा FV_MBCEN1_ENABLE                                    0x1
#घोषणा FV_MBCEN1_DISABLE                                   0x0

#घोषणा DACMBCEN_MBCEN_ENABLE                               0x1
#घोषणा DACMBCEN_MBCEN_DISABLE                              0x0

// *** DACMBCCTL ***
#घोषणा FB_DACMBCCTL_LVLMODE3                               5
#घोषणा FM_DACMBCCTL_LVLMODE3                               0x20

#घोषणा FB_DACMBCCTL_WINSEL3                                4
#घोषणा FM_DACMBCCTL_WINSEL3                                0x10

#घोषणा FB_DACMBCCTL_LVLMODE2                               3
#घोषणा FM_DACMBCCTL_LVLMODE2                               0x8

#घोषणा FB_DACMBCCTL_WINSEL2                                2
#घोषणा FM_DACMBCCTL_WINSEL2                                0x4

#घोषणा FB_DACMBCCTL_LVLMODE1                               1
#घोषणा FM_DACMBCCTL_LVLMODE1                               0x2

#घोषणा FB_DACMBCCTL_WINSEL1                                0
#घोषणा FM_DACMBCCTL_WINSEL1                                0x1

// *** DACCLECTL ***
#घोषणा FB_DACCLECTL_LVLMODE                                4
#घोषणा FM_DACCLECTL_LVLMODE                                0x10

#घोषणा FB_DACCLECTL_WINSEL                                 3
#घोषणा FM_DACCLECTL_WINSEL                                 0x8

#घोषणा FB_DACCLECTL_EXPEN                                  2
#घोषणा FM_DACCLECTL_EXPEN                                  0x4
#घोषणा FV_EXPEN_ENABLE                                     0x4
#घोषणा FV_EXPEN_DISABLE                                    0x0

#घोषणा FB_DACCLECTL_LIMEN                                  1
#घोषणा FM_DACCLECTL_LIMEN                                  0x2
#घोषणा FV_LIMEN_ENABLE                                     0x2
#घोषणा FV_LIMEN_DISABLE                                    0x0

#घोषणा FB_DACCLECTL_COMPEN                                 0
#घोषणा FM_DACCLECTL_COMPEN                                 0x1
#घोषणा FV_COMPEN_ENABLE                                    0x1
#घोषणा FV_COMPEN_DISABLE                                   0x0

// *** DACCLEMUG ***
#घोषणा FB_DACCLEMUG_MUGAIN                                 0
#घोषणा FM_DACCLEMUG_MUGAIN                                 0x1F

// *** DACCOMPTHR ***
#घोषणा FB_DACCOMPTHR_THRESH                                0
#घोषणा FM_DACCOMPTHR_THRESH                                0xFF

// *** DACCOMPRAT ***
#घोषणा FB_DACCOMPRAT_RATIO                                 0
#घोषणा FM_DACCOMPRAT_RATIO                                 0x1F

// *** DACCOMPATKL ***
#घोषणा FB_DACCOMPATKL_TCATKL                               0
#घोषणा FM_DACCOMPATKL_TCATKL                               0xFF

// *** DACCOMPATKH ***
#घोषणा FB_DACCOMPATKH_TCATKH                               0
#घोषणा FM_DACCOMPATKH_TCATKH                               0xFF

// *** DACCOMPRELL ***
#घोषणा FB_DACCOMPRELL_TCRELL                               0
#घोषणा FM_DACCOMPRELL_TCRELL                               0xFF

// *** DACCOMPRELH ***
#घोषणा FB_DACCOMPRELH_TCRELH                               0
#घोषणा FM_DACCOMPRELH_TCRELH                               0xFF

// *** DACLIMTHR ***
#घोषणा FB_DACLIMTHR_THRESH                                 0
#घोषणा FM_DACLIMTHR_THRESH                                 0xFF

// *** DACLIMTGT ***
#घोषणा FB_DACLIMTGT_TARGET                                 0
#घोषणा FM_DACLIMTGT_TARGET                                 0xFF

// *** DACLIMATKL ***
#घोषणा FB_DACLIMATKL_TCATKL                                0
#घोषणा FM_DACLIMATKL_TCATKL                                0xFF

// *** DACLIMATKH ***
#घोषणा FB_DACLIMATKH_TCATKH                                0
#घोषणा FM_DACLIMATKH_TCATKH                                0xFF

// *** DACLIMRELL ***
#घोषणा FB_DACLIMRELL_TCRELL                                0
#घोषणा FM_DACLIMRELL_TCRELL                                0xFF

// *** DACLIMRELH ***
#घोषणा FB_DACLIMRELH_TCRELH                                0
#घोषणा FM_DACLIMRELH_TCRELH                                0xFF

// *** DACEXPTHR ***
#घोषणा FB_DACEXPTHR_THRESH                                 0
#घोषणा FM_DACEXPTHR_THRESH                                 0xFF

// *** DACEXPRAT ***
#घोषणा FB_DACEXPRAT_RATIO                                  0
#घोषणा FM_DACEXPRAT_RATIO                                  0x7

// *** DACEXPATKL ***
#घोषणा FB_DACEXPATKL_TCATKL                                0
#घोषणा FM_DACEXPATKL_TCATKL                                0xFF

// *** DACEXPATKH ***
#घोषणा FB_DACEXPATKH_TCATKH                                0
#घोषणा FM_DACEXPATKH_TCATKH                                0xFF

// *** DACEXPRELL ***
#घोषणा FB_DACEXPRELL_TCRELL                                0
#घोषणा FM_DACEXPRELL_TCRELL                                0xFF

// *** DACEXPRELH ***
#घोषणा FB_DACEXPRELH_TCRELH                                0
#घोषणा FM_DACEXPRELH_TCRELH                                0xFF

// *** DACFXCTL ***
#घोषणा FB_DACFXCTL_3DEN                                    4
#घोषणा FM_DACFXCTL_3DEN                                    0x10

#घोषणा FB_DACFXCTL_TEEN                                    3
#घोषणा FM_DACFXCTL_TEEN                                    0x8

#घोषणा FB_DACFXCTL_TNLFBYP                                 2
#घोषणा FM_DACFXCTL_TNLFBYP                                 0x4

#घोषणा FB_DACFXCTL_BEEN                                    1
#घोषणा FM_DACFXCTL_BEEN                                    0x2

#घोषणा FB_DACFXCTL_BNLFBYP                                 0
#घोषणा FM_DACFXCTL_BNLFBYP                                 0x1

// *** SUBEQFILT ***
#घोषणा FB_SUBEQFILT_EQ2EN                                  7
#घोषणा FM_SUBEQFILT_EQ2EN                                  0x80
#घोषणा FV_EQ2EN_ENABLE                                     0x80
#घोषणा FV_EQ2EN_DISABLE                                    0x0

#घोषणा FB_SUBEQFILT_EQ2BE                                  4
#घोषणा FM_SUBEQFILT_EQ2BE                                  0x70

#घोषणा FB_SUBEQFILT_EQ1EN                                  3
#घोषणा FM_SUBEQFILT_EQ1EN                                  0x8
#घोषणा FV_EQ1EN_ENABLE                                     0x8
#घोषणा FV_EQ1EN_DISABLE                                    0x0

#घोषणा FB_SUBEQFILT_EQ1BE                                  0
#घोषणा FM_SUBEQFILT_EQ1BE                                  0x7

#घोषणा SUBEQFILT_EQEN_ENABLE                               0x1
#घोषणा SUBEQFILT_EQEN_DISABLE                              0x0

// *** SUBCRWDL ***
#घोषणा FB_SUBCRWDL_WDATA_L                                 0
#घोषणा FM_SUBCRWDL_WDATA_L                                 0xFF

// *** SUBCRWDM ***
#घोषणा FB_SUBCRWDM_WDATA_M                                 0
#घोषणा FM_SUBCRWDM_WDATA_M                                 0xFF

// *** SUBCRWDH ***
#घोषणा FB_SUBCRWDH_WDATA_H                                 0
#घोषणा FM_SUBCRWDH_WDATA_H                                 0xFF

// *** SUBCRRDL ***
#घोषणा FB_SUBCRRDL_RDATA_L                                 0
#घोषणा FM_SUBCRRDL_RDATA_L                                 0xFF

// *** SUBCRRDM ***
#घोषणा FB_SUBCRRDM_RDATA_M                                 0
#घोषणा FM_SUBCRRDM_RDATA_M                                 0xFF

// *** SUBCRRDH ***
#घोषणा FB_SUBCRRDH_RDATA_H                                 0
#घोषणा FM_SUBCRRDH_RDATA_H                                 0xFF

// *** SUBCRADD ***
#घोषणा FB_SUBCRADD_ADDRESS                                 0
#घोषणा FM_SUBCRADD_ADDRESS                                 0xFF

// *** SUBCRS ***
#घोषणा FB_SUBCRS_ACCSTAT                                   7
#घोषणा FM_SUBCRS_ACCSTAT                                   0x80

// *** SUBMBCEN ***
#घोषणा FB_SUBMBCEN_MBCEN3                                  2
#घोषणा FM_SUBMBCEN_MBCEN3                                  0x4
#घोषणा FV_MBCEN3_ENABLE                                    0x4
#घोषणा FV_MBCEN3_DISABLE                                   0x0

#घोषणा FB_SUBMBCEN_MBCEN2                                  1
#घोषणा FM_SUBMBCEN_MBCEN2                                  0x2
#घोषणा FV_MBCEN2_ENABLE                                    0x2
#घोषणा FV_MBCEN2_DISABLE                                   0x0

#घोषणा FB_SUBMBCEN_MBCEN1                                  0
#घोषणा FM_SUBMBCEN_MBCEN1                                  0x1
#घोषणा FV_MBCEN1_ENABLE                                    0x1
#घोषणा FV_MBCEN1_DISABLE                                   0x0

#घोषणा SUBMBCEN_MBCEN_ENABLE                               0x1
#घोषणा SUBMBCEN_MBCEN_DISABLE                              0x0

// *** SUBMBCCTL ***
#घोषणा FB_SUBMBCCTL_LVLMODE3                               5
#घोषणा FM_SUBMBCCTL_LVLMODE3                               0x20

#घोषणा FB_SUBMBCCTL_WINSEL3                                4
#घोषणा FM_SUBMBCCTL_WINSEL3                                0x10

#घोषणा FB_SUBMBCCTL_LVLMODE2                               3
#घोषणा FM_SUBMBCCTL_LVLMODE2                               0x8

#घोषणा FB_SUBMBCCTL_WINSEL2                                2
#घोषणा FM_SUBMBCCTL_WINSEL2                                0x4

#घोषणा FB_SUBMBCCTL_LVLMODE1                               1
#घोषणा FM_SUBMBCCTL_LVLMODE1                               0x2

#घोषणा FB_SUBMBCCTL_WINSEL1                                0
#घोषणा FM_SUBMBCCTL_WINSEL1                                0x1

// *** SUBCLECTL ***
#घोषणा FB_SUBCLECTL_LVLMODE                                4
#घोषणा FM_SUBCLECTL_LVLMODE                                0x10

#घोषणा FB_SUBCLECTL_WINSEL                                 3
#घोषणा FM_SUBCLECTL_WINSEL                                 0x8

#घोषणा FB_SUBCLECTL_EXPEN                                  2
#घोषणा FM_SUBCLECTL_EXPEN                                  0x4
#घोषणा FV_EXPEN_ENABLE                                     0x4
#घोषणा FV_EXPEN_DISABLE                                    0x0

#घोषणा FB_SUBCLECTL_LIMEN                                  1
#घोषणा FM_SUBCLECTL_LIMEN                                  0x2
#घोषणा FV_LIMEN_ENABLE                                     0x2
#घोषणा FV_LIMEN_DISABLE                                    0x0

#घोषणा FB_SUBCLECTL_COMPEN                                 0
#घोषणा FM_SUBCLECTL_COMPEN                                 0x1
#घोषणा FV_COMPEN_ENABLE                                    0x1
#घोषणा FV_COMPEN_DISABLE                                   0x0

// *** SUBCLEMUG ***
#घोषणा FB_SUBCLEMUG_MUGAIN                                 0
#घोषणा FM_SUBCLEMUG_MUGAIN                                 0x1F

// *** SUBCOMPTHR ***
#घोषणा FB_SUBCOMPTHR_THRESH                                0
#घोषणा FM_SUBCOMPTHR_THRESH                                0xFF

// *** SUBCOMPRAT ***
#घोषणा FB_SUBCOMPRAT_RATIO                                 0
#घोषणा FM_SUBCOMPRAT_RATIO                                 0x1F

// *** SUBCOMPATKL ***
#घोषणा FB_SUBCOMPATKL_TCATKL                               0
#घोषणा FM_SUBCOMPATKL_TCATKL                               0xFF

// *** SUBCOMPATKH ***
#घोषणा FB_SUBCOMPATKH_TCATKH                               0
#घोषणा FM_SUBCOMPATKH_TCATKH                               0xFF

// *** SUBCOMPRELL ***
#घोषणा FB_SUBCOMPRELL_TCRELL                               0
#घोषणा FM_SUBCOMPRELL_TCRELL                               0xFF

// *** SUBCOMPRELH ***
#घोषणा FB_SUBCOMPRELH_TCRELH                               0
#घोषणा FM_SUBCOMPRELH_TCRELH                               0xFF

// *** SUBLIMTHR ***
#घोषणा FB_SUBLIMTHR_THRESH                                 0
#घोषणा FM_SUBLIMTHR_THRESH                                 0xFF

// *** SUBLIMTGT ***
#घोषणा FB_SUBLIMTGT_TARGET                                 0
#घोषणा FM_SUBLIMTGT_TARGET                                 0xFF

// *** SUBLIMATKL ***
#घोषणा FB_SUBLIMATKL_TCATKL                                0
#घोषणा FM_SUBLIMATKL_TCATKL                                0xFF

// *** SUBLIMATKH ***
#घोषणा FB_SUBLIMATKH_TCATKH                                0
#घोषणा FM_SUBLIMATKH_TCATKH                                0xFF

// *** SUBLIMRELL ***
#घोषणा FB_SUBLIMRELL_TCRELL                                0
#घोषणा FM_SUBLIMRELL_TCRELL                                0xFF

// *** SUBLIMRELH ***
#घोषणा FB_SUBLIMRELH_TCRELH                                0
#घोषणा FM_SUBLIMRELH_TCRELH                                0xFF

// *** SUBEXPTHR ***
#घोषणा FB_SUBEXPTHR_THRESH                                 0
#घोषणा FM_SUBEXPTHR_THRESH                                 0xFF

// *** SUBEXPRAT ***
#घोषणा FB_SUBEXPRAT_RATIO                                  0
#घोषणा FM_SUBEXPRAT_RATIO                                  0x7

// *** SUBEXPATKL ***
#घोषणा FB_SUBEXPATKL_TCATKL                                0
#घोषणा FM_SUBEXPATKL_TCATKL                                0xFF

// *** SUBEXPATKH ***
#घोषणा FB_SUBEXPATKH_TCATKH                                0
#घोषणा FM_SUBEXPATKH_TCATKH                                0xFF

// *** SUBEXPRELL ***
#घोषणा FB_SUBEXPRELL_TCRELL                                0
#घोषणा FM_SUBEXPRELL_TCRELL                                0xFF

// *** SUBEXPRELH ***
#घोषणा FB_SUBEXPRELH_TCRELH                                0
#घोषणा FM_SUBEXPRELH_TCRELH                                0xFF

// *** SUBFXCTL ***
#घोषणा FB_SUBFXCTL_TEEN                                    3
#घोषणा FM_SUBFXCTL_TEEN                                    0x8

#घोषणा FB_SUBFXCTL_TNLFBYP                                 2
#घोषणा FM_SUBFXCTL_TNLFBYP                                 0x4

#घोषणा FB_SUBFXCTL_BEEN                                    1
#घोषणा FM_SUBFXCTL_BEEN                                    0x2

#घोषणा FB_SUBFXCTL_BNLFBYP                                 0
#घोषणा FM_SUBFXCTL_BNLFBYP                                 0x1

#पूर्ण_अगर /* __REDWOODPUBLIC_H__ */
