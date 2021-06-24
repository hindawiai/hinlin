<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * gp8psk_fe driver
 */

#अगर_अघोषित GP8PSK_FE_H
#घोषणा GP8PSK_FE_H

#समावेश <linux/types.h>

/* gp8psk commands */

#घोषणा GET_8PSK_CONFIG                 0x80    /* in */
#घोषणा SET_8PSK_CONFIG                 0x81
#घोषणा I2C_WRITE			0x83
#घोषणा I2C_READ			0x84
#घोषणा ARM_TRANSFER                    0x85
#घोषणा TUNE_8PSK                       0x86
#घोषणा GET_SIGNAL_STRENGTH             0x87    /* in */
#घोषणा LOAD_BCM4500                    0x88
#घोषणा BOOT_8PSK                       0x89    /* in */
#घोषणा START_INTERSIL                  0x8A    /* in */
#घोषणा SET_LNB_VOLTAGE                 0x8B
#घोषणा SET_22KHZ_TONE                  0x8C
#घोषणा SEND_DISEQC_COMMAND             0x8D
#घोषणा SET_DVB_MODE                    0x8E
#घोषणा SET_DN_SWITCH                   0x8F
#घोषणा GET_SIGNAL_LOCK                 0x90    /* in */
#घोषणा GET_FW_VERS			0x92
#घोषणा GET_SERIAL_NUMBER               0x93    /* in */
#घोषणा USE_EXTRA_VOLT                  0x94
#घोषणा GET_FPGA_VERS			0x95
#घोषणा CW3K_INIT			0x9d

/* PSK_configuration bits */
#घोषणा bm8pskStarted                   0x01
#घोषणा bm8pskFW_Loaded                 0x02
#घोषणा bmIntersilOn                    0x04
#घोषणा bmDVBmode                       0x08
#घोषणा bm22kHz                         0x10
#घोषणा bmSEL18V                        0x20
#घोषणा bmDCtuned                       0x40
#घोषणा bmArmed                         0x80

/* Satellite modulation modes */
#घोषणा ADV_MOD_DVB_QPSK 0     /* DVB-S QPSK */
#घोषणा ADV_MOD_TURBO_QPSK 1   /* Turbo QPSK */
#घोषणा ADV_MOD_TURBO_8PSK 2   /* Turbo 8PSK (also used क्रम Trellis 8PSK) */
#घोषणा ADV_MOD_TURBO_16QAM 3  /* Turbo 16QAM (also used क्रम Trellis 8PSK) */

#घोषणा ADV_MOD_DCII_C_QPSK 4  /* Digicipher II Combo */
#घोषणा ADV_MOD_DCII_I_QPSK 5  /* Digicipher II I-stream */
#घोषणा ADV_MOD_DCII_Q_QPSK 6  /* Digicipher II Q-stream */
#घोषणा ADV_MOD_DCII_C_OQPSK 7 /* Digicipher II offset QPSK */
#घोषणा ADV_MOD_DSS_QPSK 8     /* DSS (सूचीECTV) QPSK */
#घोषणा ADV_MOD_DVB_BPSK 9     /* DVB-S BPSK */

/* firmware revision id's */
#घोषणा GP8PSK_FW_REV1			0x020604
#घोषणा GP8PSK_FW_REV2			0x020704
#घोषणा GP8PSK_FW_VERS(_fw_vers) \
	((_fw_vers)[2]<<0x10 | (_fw_vers)[1]<<0x08 | (_fw_vers)[0])

काष्ठा gp8psk_fe_ops अणु
	पूर्णांक (*in)(व्योम *priv, u8 req, u16 value, u16 index, u8 *b, पूर्णांक blen);
	पूर्णांक (*out)(व्योम *priv, u8 req, u16 value, u16 index, u8 *b, पूर्णांक blen);
	पूर्णांक (*reload)(व्योम *priv);
पूर्ण;

काष्ठा dvb_frontend *gp8psk_fe_attach(स्थिर काष्ठा gp8psk_fe_ops *ops,
				      व्योम *priv, bool is_rev1);

#पूर्ण_अगर
