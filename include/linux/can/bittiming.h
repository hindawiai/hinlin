<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2020 Pengutronix, Marc Kleine-Budde <kernel@pengutronix.de>
 * Copyright (c) 2021 Vincent Mailhol <mailhol.vincent@wanaकरोo.fr>
 */

#अगर_अघोषित _CAN_BITTIMING_H
#घोषणा _CAN_BITTIMING_H

#समावेश <linux/netdevice.h>
#समावेश <linux/can/netlink.h>

#घोषणा CAN_SYNC_SEG 1


/* Kilobits and Megabits per second */
#घोषणा CAN_KBPS 1000UL
#घोषणा CAN_MBPS 1000000UL

/* Megahertz */
#घोषणा CAN_MHZ 1000000UL

/*
 * काष्ठा can_tdc - CAN FD Transmission Delay Compensation parameters
 *
 * At high bit rates, the propagation delay from the TX pin to the RX
 * pin of the transceiver causes measurement errors: the sample poपूर्णांक
 * on the RX pin might occur on the previous bit.
 *
 * To solve this issue, ISO 11898-1 पूर्णांकroduces in section 11.3.3
 * "Transmitter delay compensation" a SSP (Secondary Sample Poपूर्णांक)
 * equal to the distance, in समय quanta, from the start of the bit
 * समय on the TX pin to the actual measurement on the RX pin.
 *
 * This काष्ठाure contains the parameters to calculate that SSP.
 *
 * @tdcv: Transmitter Delay Compensation Value. Distance, in समय
 *	quanta, from when the bit is sent on the TX pin to when it is
 *	received on the RX pin of the transmitter. Possible options:
 *
 *	  O: स्वतःmatic mode. The controller dynamically measure @tdcv
 *	  क्रम each transmitted CAN FD frame.
 *
 *	  Other values: manual mode. Use the fixed provided value.
 *
 * @tdco: Transmitter Delay Compensation Offset. Offset value, in समय
 *	quanta, defining the distance between the start of the bit
 *	reception on the RX pin of the transceiver and the SSP
 *	position such as SSP = @tdcv + @tdco.
 *
 *	If @tdco is zero, then TDC is disabled and both @tdcv and
 *	@tdcf should be ignored.
 *
 * @tdcf: Transmitter Delay Compensation Filter winकरोw. Defines the
 *	minimum value क्रम the SSP position in समय quanta. If SSP is
 *	less than @tdcf, then no delay compensations occur and the
 *	normal sampling poपूर्णांक is used instead. The feature is enabled
 *	अगर and only अगर @tdcv is set to zero (स्वतःmatic mode) and @tdcf
 *	is configured to a value greater than @tdco.
 */
काष्ठा can_tdc अणु
	u32 tdcv;
	u32 tdco;
	u32 tdcf;
पूर्ण;

/*
 * काष्ठा can_tdc_स्थिर - CAN hardware-dependent स्थिरant क्रम
 *	Transmission Delay Compensation
 *
 * @tdcv_max: Transmitter Delay Compensation Value maximum value.
 *	Should be set to zero अगर the controller करोes not support
 *	manual mode क्रम tdcv.
 * @tdco_max: Transmitter Delay Compensation Offset maximum value.
 *	Should not be zero. If the controller करोes not support TDC,
 *	then the poपूर्णांकer to this काष्ठाure should be शून्य.
 * @tdcf_max: Transmitter Delay Compensation Filter winकरोw maximum
 *	value. Should be set to zero अगर the controller करोes not
 *	support this feature.
 */
काष्ठा can_tdc_स्थिर अणु
	u32 tdcv_max;
	u32 tdco_max;
	u32 tdcf_max;
पूर्ण;

#अगर_घोषित CONFIG_CAN_CALC_BITTIMING
पूर्णांक can_calc_bittiming(काष्ठा net_device *dev, काष्ठा can_bittiming *bt,
		       स्थिर काष्ठा can_bittiming_स्थिर *btc);

व्योम can_calc_tdco(काष्ठा net_device *dev);
#अन्यथा /* !CONFIG_CAN_CALC_BITTIMING */
अटल अंतरभूत पूर्णांक
can_calc_bittiming(काष्ठा net_device *dev, काष्ठा can_bittiming *bt,
		   स्थिर काष्ठा can_bittiming_स्थिर *btc)
अणु
	netdev_err(dev, "bit-timing calculation not available\n");
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम can_calc_tdco(काष्ठा net_device *dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_CAN_CALC_BITTIMING */

पूर्णांक can_get_bittiming(काष्ठा net_device *dev, काष्ठा can_bittiming *bt,
		      स्थिर काष्ठा can_bittiming_स्थिर *btc,
		      स्थिर u32 *bitrate_स्थिर,
		      स्थिर अचिन्हित पूर्णांक bitrate_स्थिर_cnt);

/*
 * can_bit_समय() - Duration of one bit
 *
 * Please refer to ISO 11898-1:2015, section 11.3.1.1 "Bit time" क्रम
 * additional inक्रमmation.
 *
 * Return: the number of समय quanta in one bit.
 */
अटल अंतरभूत अचिन्हित पूर्णांक can_bit_समय(स्थिर काष्ठा can_bittiming *bt)
अणु
	वापस CAN_SYNC_SEG + bt->prop_seg + bt->phase_seg1 + bt->phase_seg2;
पूर्ण

#पूर्ण_अगर /* !_CAN_BITTIMING_H */
