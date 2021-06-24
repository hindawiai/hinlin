<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Public Include File क्रम DRV6000 users
 * (ie. NxtWave Communications - NXT6000 demodulator driver)
 *
 * Copyright (C) 2001 NxtWave Communications, Inc.
 *
 */

/*  Nxt6000 Register Addresses and Bit Masks */

/* Maximum Register Number */
#घोषणा MAXNXT6000REG          (0x9A)

/* 0x1B A_VIT_BER_0  aka 0x3A */
#घोषणा A_VIT_BER_0            (0x1B)

/* 0x1D A_VIT_BER_TIMER_0 aka 0x38 */
#घोषणा A_VIT_BER_TIMER_0      (0x1D)

/* 0x21 RS_COR_STAT */
#घोषणा RS_COR_STAT            (0x21)
#घोषणा RSCORESTATUS           (0x03)

/* 0x22 RS_COR_INTEN */
#घोषणा RS_COR_INTEN           (0x22)

/* 0x23 RS_COR_INSTAT */
#घोषणा RS_COR_INSTAT          (0x23)
#घोषणा INSTAT_ERROR           (0x04)
#घोषणा LOCK_LOSS_BITS         (0x03)

/* 0x24 RS_COR_SYNC_PARAM */
#घोषणा RS_COR_SYNC_PARAM      (0x24)
#घोषणा SYNC_PARAM             (0x03)

/* 0x25 BER_CTRL */
#घोषणा BER_CTRL               (0x25)
#घोषणा BER_ENABLE             (0x02)
#घोषणा BER_RESET              (0x01)

/* 0x26 BER_PAY */
#घोषणा BER_PAY                (0x26)

/* 0x27 BER_PKT_L */
#घोषणा BER_PKT_L              (0x27)
#घोषणा BER_PKTOVERFLOW        (0x80)

/* 0x30 VIT_COR_CTL */
#घोषणा VIT_COR_CTL            (0x30)
#घोषणा BER_CONTROL            (0x02)
#घोषणा VIT_COR_MASK           (0x82)
#घोषणा VIT_COR_RESYNC         (0x80)


/* 0x32 VIT_SYNC_STATUS */
#घोषणा VIT_SYNC_STATUS        (0x32)
#घोषणा VITINSYNC              (0x80)

/* 0x33 VIT_COR_INTEN */
#घोषणा VIT_COR_INTEN          (0x33)
#घोषणा GLOBAL_ENABLE          (0x80)

/* 0x34 VIT_COR_INTSTAT */
#घोषणा VIT_COR_INTSTAT        (0x34)
#घोषणा BER_DONE               (0x08)
#घोषणा BER_OVERFLOW           (0x10)

/* 0x38 VIT_BERTIME_2 */
#घोषणा VIT_BERTIME_2      (0x38)

/* 0x39 VIT_BERTIME_1 */
#घोषणा VIT_BERTIME_1      (0x39)

/* 0x3A VIT_BERTIME_0 */
#घोषणा VIT_BERTIME_0      (0x3a)

			     /* 0x38 OFDM_BERTimer *//* Use the alias रेजिस्टरs */
#घोषणा A_VIT_BER_TIMER_0      (0x1D)

			     /* 0x3A VIT_BER_TIMER_0 *//* Use the alias रेजिस्टरs */
#घोषणा A_VIT_BER_0            (0x1B)

/* 0x3B VIT_BER_1 */
#घोषणा VIT_BER_1              (0x3b)

/* 0x3C VIT_BER_0 */
#घोषणा VIT_BER_0              (0x3c)

/* 0x40 OFDM_COR_CTL */
#घोषणा OFDM_COR_CTL           (0x40)
#घोषणा COREACT                (0x20)
#घोषणा HOLDSM                 (0x10)
#घोषणा WAIT_AGC               (0x02)
#घोषणा WAIT_SYR               (0x03)

/* 0x41 OFDM_COR_STAT */
#घोषणा OFDM_COR_STAT          (0x41)
#घोषणा COR_STATUS             (0x0F)
#घोषणा MONITOR_TPS            (0x06)
#घोषणा TPSLOCKED              (0x40)
#घोषणा AGCLOCKED              (0x10)

/* 0x42 OFDM_COR_INTEN */
#घोषणा OFDM_COR_INTEN         (0x42)
#घोषणा TPSRCVBAD              (0x04)
#घोषणा TPSRCVCHANGED         (0x02)
#घोषणा TPSRCVUPDATE           (0x01)

/* 0x43 OFDM_COR_INSTAT */
#घोषणा OFDM_COR_INSTAT        (0x43)

/* 0x44 OFDM_COR_MODEGUARD */
#घोषणा OFDM_COR_MODEGUARD     (0x44)
#घोषणा FORCEMODE              (0x08)
#घोषणा FORCEMODE8K			   (0x04)

/* 0x45 OFDM_AGC_CTL */
#घोषणा OFDM_AGC_CTL           (0x45)
#घोषणा INITIAL_AGC_BW		   (0x08)
#घोषणा AGCNEG                 (0x02)
#घोषणा AGCLAST				   (0x10)

/* 0x48 OFDM_AGC_TARGET */
#घोषणा OFDM_AGC_TARGET		   (0x48)
#घोषणा OFDM_AGC_TARGET_DEFAULT (0x28)
#घोषणा OFDM_AGC_TARGET_IMPULSE (0x38)

/* 0x49 OFDM_AGC_GAIN_1 */
#घोषणा OFDM_AGC_GAIN_1        (0x49)

/* 0x4B OFDM_ITB_CTL */
#घोषणा OFDM_ITB_CTL           (0x4B)
#घोषणा ITBINV                 (0x01)

/* 0x49 AGC_GAIN_1 */
#घोषणा AGC_GAIN_1             (0x49)

/* 0x4A AGC_GAIN_2 */
#घोषणा AGC_GAIN_2             (0x4A)

/* 0x4C OFDM_ITB_FREQ_1 */
#घोषणा OFDM_ITB_FREQ_1        (0x4C)

/* 0x4D OFDM_ITB_FREQ_2 */
#घोषणा OFDM_ITB_FREQ_2        (0x4D)

/* 0x4E  OFDM_CAS_CTL */
#घोषणा OFDM_CAS_CTL           (0x4E)
#घोषणा ACSDIS                 (0x40)
#घोषणा CCSEN                  (0x80)

/* 0x4F CAS_FREQ */
#घोषणा CAS_FREQ               (0x4F)

/* 0x51 OFDM_SYR_CTL */
#घोषणा OFDM_SYR_CTL           (0x51)
#घोषणा SIXTH_ENABLE           (0x80)
#घोषणा SYR_TRACKING_DISABLE   (0x01)

/* 0x52 OFDM_SYR_STAT */
#घोषणा OFDM_SYR_STAT		   (0x52)
#घोषणा GI14_2K_SYR_LOCK	   (0x13)
#घोषणा GI14_8K_SYR_LOCK	   (0x17)
#घोषणा GI14_SYR_LOCK		   (0x10)

/* 0x55 OFDM_SYR_OFFSET_1 */
#घोषणा OFDM_SYR_OFFSET_1      (0x55)

/* 0x56 OFDM_SYR_OFFSET_2 */
#घोषणा OFDM_SYR_OFFSET_2      (0x56)

/* 0x58 OFDM_SCR_CTL */
#घोषणा OFDM_SCR_CTL           (0x58)
#घोषणा SYR_ADJ_DECAY_MASK     (0x70)
#घोषणा SYR_ADJ_DECAY          (0x30)

/* 0x59 OFDM_PPM_CTL_1 */
#घोषणा OFDM_PPM_CTL_1         (0x59)
#घोषणा PPMMAX_MASK            (0x30)
#घोषणा PPM256				   (0x30)

/* 0x5B OFDM_TRL_NOMINALRATE_1 */
#घोषणा OFDM_TRL_NOMINALRATE_1 (0x5B)

/* 0x5C OFDM_TRL_NOMINALRATE_2 */
#घोषणा OFDM_TRL_NOMINALRATE_2 (0x5C)

/* 0x5D OFDM_TRL_TIME_1 */
#घोषणा OFDM_TRL_TIME_1        (0x5D)

/* 0x60 OFDM_CRL_FREQ_1 */
#घोषणा OFDM_CRL_FREQ_1        (0x60)

/* 0x63 OFDM_CHC_CTL_1 */
#घोषणा OFDM_CHC_CTL_1         (0x63)
#घोषणा MANMEAN1               (0xF0);
#घोषणा CHCFIR                 (0x01)

/* 0x64 OFDM_CHC_SNR */
#घोषणा OFDM_CHC_SNR           (0x64)

/* 0x65 OFDM_BDI_CTL */
#घोषणा OFDM_BDI_CTL           (0x65)
#घोषणा LP_SELECT              (0x02)

/* 0x67 OFDM_TPS_RCVD_1 */
#घोषणा OFDM_TPS_RCVD_1        (0x67)
#घोषणा TPSFRAME               (0x03)

/* 0x68 OFDM_TPS_RCVD_2 */
#घोषणा OFDM_TPS_RCVD_2        (0x68)

/* 0x69 OFDM_TPS_RCVD_3 */
#घोषणा OFDM_TPS_RCVD_3        (0x69)

/* 0x6A OFDM_TPS_RCVD_4 */
#घोषणा OFDM_TPS_RCVD_4        (0x6A)

/* 0x6B OFDM_TPS_RESERVED_1 */
#घोषणा OFDM_TPS_RESERVED_1    (0x6B)

/* 0x6C OFDM_TPS_RESERVED_2 */
#घोषणा OFDM_TPS_RESERVED_2    (0x6C)

/* 0x73 OFDM_MSC_REV */
#घोषणा OFDM_MSC_REV           (0x73)

/* 0x76 OFDM_SNR_CARRIER_2 */
#घोषणा OFDM_SNR_CARRIER_2     (0x76)
#घोषणा MEAN_MASK              (0x80)
#घोषणा MEANBIT                (0x80)

/* 0x80 ANALOG_CONTROL_0 */
#घोषणा ANALOG_CONTROL_0       (0x80)
#घोषणा POWER_DOWN_ADC         (0x40)

/* 0x81 ENABLE_TUNER_IIC */
#घोषणा ENABLE_TUNER_IIC       (0x81)
#घोषणा ENABLE_TUNER_BIT       (0x01)

/* 0x82 EN_DMD_RACQ */
#घोषणा EN_DMD_RACQ            (0x82)
#घोषणा EN_DMD_RACQ_REG_VAL    (0x81)
#घोषणा EN_DMD_RACQ_REG_VAL_14 (0x01)

/* 0x84 SNR_COMMAND */
#घोषणा SNR_COMMAND            (0x84)
#घोषणा SNRStat                (0x80)

/* 0x85 SNRCARRIERNUMBER_LSB */
#घोषणा SNRCARRIERNUMBER_LSB   (0x85)

/* 0x87 SNRMINTHRESHOLD_LSB */
#घोषणा SNRMINTHRESHOLD_LSB    (0x87)

/* 0x89 SNR_PER_CARRIER_LSB */
#घोषणा SNR_PER_CARRIER_LSB    (0x89)

/* 0x8B SNRBELOWTHRESHOLD_LSB */
#घोषणा SNRBELOWTHRESHOLD_LSB  (0x8B)

/* 0x91 RF_AGC_VAL_1 */
#घोषणा RF_AGC_VAL_1           (0x91)

/* 0x92 RF_AGC_STATUS */
#घोषणा RF_AGC_STATUS          (0x92)

/* 0x98 DIAG_CONFIG */
#घोषणा DIAG_CONFIG            (0x98)
#घोषणा DIAG_MASK              (0x70)
#घोषणा TB_SET                 (0x10)
#घोषणा TRAN_SELECT            (0x07)
#घोषणा SERIAL_SELECT          (0x01)

/* 0x99 SUB_DIAG_MODE_SEL */
#घोषणा SUB_DIAG_MODE_SEL      (0x99)
#घोषणा CLKINVERSION           (0x01)

/* 0x9A TS_FORMAT */
#घोषणा TS_FORMAT              (0x9A)
#घोषणा ERROR_SENSE            (0x08)
#घोषणा VALID_SENSE            (0x04)
#घोषणा SYNC_SENSE             (0x02)
#घोषणा GATED_CLOCK            (0x01)

#घोषणा NXT6000ASICDEVICE      (0x0b)
