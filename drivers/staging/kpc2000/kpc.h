<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित KPC_H_
#घोषणा KPC_H_

/* *****  Driver Names  ***** */
#घोषणा KP_DRIVER_NAME_KP2000           "kp2000"
#घोषणा KP_DRIVER_NAME_INVALID          "kpc_invalid"
#घोषणा KP_DRIVER_NAME_DMA_CONTROLLER   "kpc_nwl_dma"
#घोषणा KP_DRIVER_NAME_UIO              "uio_pdrv_genirq"
#घोषणा KP_DRIVER_NAME_I2C              "kpc_i2c"
#घोषणा KP_DRIVER_NAME_SPI              "kpc_spi"

काष्ठा kpc_core_device_platdata अणु
	u32 card_id;
	u32 build_version;
	u32 hardware_revision;
	u64 ssid;
	u64 ddna;
पूर्ण;

#घोषणा PCI_DEVICE_ID_DAKTRONICS_KADOKA_P2KR0           0x4b03

#पूर्ण_अगर /* KPC_H_ */
