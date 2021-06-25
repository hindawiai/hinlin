<शैली गुरु>
/*
 * ndis.h
 *
 * ntddndis.h modअगरied by Benedikt Spranger <b.spranger@pengutronix.de>
 *
 * Thanks to the cygwin development team,
 * espacially to Casper S. Hornstrup <chorns@users.sourceक्रमge.net>
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered क्रम use in the खुला करोमुख्य. You may
 * use, modअगरy or distribute it मुक्तly.
 */

#अगर_अघोषित _LINUX_NDIS_H
#घोषणा _LINUX_NDIS_H

क्रमागत NDIS_DEVICE_POWER_STATE अणु
	NdisDeviceStateUnspecअगरied = 0,
	NdisDeviceStateD0,
	NdisDeviceStateD1,
	NdisDeviceStateD2,
	NdisDeviceStateD3,
	NdisDeviceStateMaximum
पूर्ण;

काष्ठा NDIS_PM_WAKE_UP_CAPABILITIES अणु
	क्रमागत NDIS_DEVICE_POWER_STATE  MinMagicPacketWakeUp;
	क्रमागत NDIS_DEVICE_POWER_STATE  MinPatternWakeUp;
	क्रमागत NDIS_DEVICE_POWER_STATE  MinLinkChangeWakeUp;
पूर्ण;

काष्ठा NDIS_PNP_CAPABILITIES अणु
	__le32					Flags;
	काष्ठा NDIS_PM_WAKE_UP_CAPABILITIES	WakeUpCapabilities;
पूर्ण;

काष्ठा NDIS_PM_PACKET_PATTERN अणु
	__le32	Priority;
	__le32	Reserved;
	__le32	MaskSize;
	__le32	PatternOffset;
	__le32	PatternSize;
	__le32	PatternFlags;
पूर्ण;

#पूर्ण_अगर /* _LINUX_NDIS_H */
